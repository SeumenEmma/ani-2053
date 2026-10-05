#include <iostream>

long long arrondir(long long a, long long b)
{
    return (2 * a + b) / (2 * b);
}

int main()
{
    long long RW, RH;
    long long AW, AH;
    long long W, H;

    std::cin >> RW >> RH >> AW >> AH >> W >> H;
    if (RW == 0 || RH == 0)
    {
        std::cout << "FOLLOW_WINDOW "
                << 0 << " " << 0 << " "
                << W << " " << H << " "
                << W << " " << H << '\n';

        std::cout << "STRETCH "
                << 0 << " " << 0 << " "
                << W << " " << H << " "
                << W << " " << H << '\n';

        std::cout << "FIT_LETTERBOX "
                << 0 << " " << 0 << " "
                << W << " " << H << " "
                << W << " " << H << '\n';

        std::cout << "INTEGER_SCALE "
                << 0 << " " << 0 << " "
                << W << " " << H << " "
                << W << " " << H << '\n';

        std::cout << "FIT_CROP "
                << 0 << " " << 0 << " "
                << W << " " << H << " "
                << W << " " << H << '\n';

        std::cout << "MANUAL "
                << 0 << " " << 0 << " "
                << AW << " " << AH << " "
                << AW << " " << AH << '\n';

        int bandes = 0;

        if (AW < W || AH < H)
        {
            bandes = 1;
        }

        std::cout << "BANDES " << bandes << '\n';
        std::cout << "DEFORMATION NON\n";

        return 0;
    }
    std::cout << "FOLLOW_WINDOW "
          << 0 << " "
          << 0 << " "
          << W << " "
          << H << " "
          << W << " "
          << H << '\n';
    std::cout << "STRETCH "
          << 0 << " "
          << 0 << " "
          << W << " "
          << H << " "
          << RW << " "
          << RH << '\n';      
    long long vwLetterbox;
        long long vhLetterbox;

        if (W * RH <= H * RW)
        {
            vwLetterbox = W;
            vhLetterbox = arrondir(RH * W, RW);
        }
        else
        {
            vhLetterbox = H;
            vwLetterbox = arrondir(RW * H, RH);
        }

        long long vxLetterbox = (W - vwLetterbox) / 2;
        long long vyLetterbox = (H - vhLetterbox) / 2;
        std::cout << "FIT_LETTERBOX "
          << vxLetterbox << " "
          << vyLetterbox << " "
          << vwLetterbox << " "
          << vhLetterbox << " "
          << RW << " "
          << RH << '\n';
        
        long long vxInteger;
        long long vyInteger;
        long long vwInteger;
        long long vhInteger;

        if (W >= RW && H >= RH)
        {
            long long k = W / RW;

            if (H / RH < k)
            {
                k = H / RH;
            }

            if (k == 0)
            {
                vwInteger = vwLetterbox;
                vhInteger = vhLetterbox;
                vxInteger = vxLetterbox;
                vyInteger = vyLetterbox;
            }
            else
            {
                vwInteger = RW * k;
                vhInteger = RH * k;
                vxInteger = (W - vwInteger) / 2;
                vyInteger = (H - vhInteger) / 2;
            }
        }
        else
        {
            vwInteger = vwLetterbox;
            vhInteger = vhLetterbox;
            vxInteger = vxLetterbox;
            vyInteger = vyLetterbox;
        }
        std::cout << "INTEGER_SCALE "
          << vxInteger << " "
          << vyInteger << " "
          << vwInteger << " "
          << vhInteger << " "
          << RW << " "
          << RH << '\n';
        long long mwCrop;
        long long mhCrop;

        if (W * RH > H * RW)
        {
            mwCrop = RW;
            mhCrop = arrondir(RW * H, W);
        }
        else
        {
            mwCrop = arrondir(RH * W, H);
            mhCrop = RH;
        }
        std::cout << "FIT_CROP "
          << 0 << " "
          << 0 << " "
          << W << " "
          << H << " "
          << mwCrop << " "
          << mhCrop << '\n';
        std::cout << "MANUAL "
          << 0 << " "
          << 0 << " "
          << AW << " "
          << AH << " "
          << AW << " "
          << AH << '\n'; 
        int bandes = 0;

        if (vwLetterbox < W || vhLetterbox < H)
        {
            ++bandes;
        }

        if (vwInteger < W || vhInteger < H)
        {
            ++bandes;
        }

        if (AW < W || AH < H)
        {
            ++bandes;
        }

        std::cout << "BANDES " << bandes << '\n';
        if (RW != 0 && RH != 0 && W * RH != H * RW)
        {
            std::cout << "DEFORMATION OUI\n";
        }
        else
        {
            std::cout << "DEFORMATION NON\n";
        }   
    return 0;
}