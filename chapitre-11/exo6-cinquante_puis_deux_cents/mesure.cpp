#include "NkRef/NkRefFile.h"
#include "NKTime/NkChrono.h"

#include <cerrno>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: mesure.exe N\n";
        return 1;
    }

    char* end = nullptr;
    errno = 0;
    const long count = std::strtol(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        count <= 0 || count > 1000000)
    {
        std::cerr << "N must be a positive integer.\n";
        return 1;
    }

    nkref::NkRefBoard board;
    nkentseu::NkString emptyPath;

    for (long i = 0; i < count; ++i)
    {
        const nkentseu::float32 x =
            static_cast<nkentseu::float32>(i * 120);
        const nkentseu::float32 y =
            static_cast<nkentseu::float32>(i * 90);

        board.AddItem({x, y}, 100, 80, emptyPath);
    }

    const std::vector<nkentseu::uint8> sourceBytes(
        1000, static_cast<nkentseu::uint8>(0x5A));

    std::vector<nkref::NkRefFileImage> images(
        static_cast<std::size_t>(count));

    for (long i = 0; i < count; ++i)
    {
        images[static_cast<std::size_t>(i)] = {
            sourceBytes.data(), sourceBytes.size()
        };
    }

    nkref::NkRefView view;
    nkentseu::NkVector<nkentseu::uint8> serialized;

    nkentseu::NkChrono writeChrono;

    for (int i = 0; i < 20; ++i)
    {
        nkref::NkRefSerialize(
            serialized, board, images.data(), view, false, true);
    }

    const double writeAverage =
        writeChrono.Elapsed().ToMilliseconds() / 20.0;

    nkentseu::NkVector<nkref::NkRefLoadedItem> loadedItems;
    nkentseu::NkVector<nkref::NkRefStroke> loadedStrokes;
    nkref::NkRefView loadedView;
    bool darkTheme = false;
    bool showGrid = true;

    nkentseu::NkChrono readChrono;

    for (int i = 0; i < 20; ++i)
    {
        const bool ok = nkref::NkRefDeserialize(
            serialized.Data(),
            serialized.Size(),
            loadedItems,
            loadedStrokes,
            loadedView,
            darkTheme,
            showGrid);

        if (!ok ||
            loadedItems.Size() != static_cast<nkentseu::usize>(count))
        {
            std::cerr << "Deserialization failed.\n";
            return 1;
        }
    }

    const double readAverage =
        readChrono.Elapsed().ToMilliseconds() / 20.0;

    std::cout << std::fixed << std::setprecision(3)
              << "images : " << count
              << ", octets : " << serialized.Size()
              << ", ecrire : " << writeAverage << " ms"
              << ", relire : " << readAverage << " ms\n";

    return 0;
}