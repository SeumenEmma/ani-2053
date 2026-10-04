#include <iostream>
#include <string>
#include <algorithm>

int main(){
    int N;
    std::cin >> N;
    int refuses = 0;

    for(int i = 0; i < N; i++){
        std::string nom;
        int w, h;
        int px, py;
        int ox, oy;
        int sx, sy;
        int angle;

        std::cin >> nom >> w >> h >> px >> py >> ox >> oy >> sx >> sy >> angle;

        int normalized = angle % 360;
        if(normalized < 0){
            normalized += 360;
        }
        if(normalized != 0 && normalized != 90 && normalized != 180 && normalized != 270){
            std::cout << nom << " ANGLE REFUSE" << std::endl;
            ++refuses;
            continue;
        }
        int c = 0;
        int s = 0;

        if(normalized == 0){
            c = 1;
            s = 0;
        }
        else if(normalized == 90){
            c = 0;
            s = 1;
        }
        else if(normalized == 180){
            c = -1;
            s =  0;
        }
        else{
            c = 0;
            s = -1;

        }
        int corners[4][2] = {
            {0, 0},
            {w, 0},
            {w, h},
            {0, h}
        };
        int world[4][2];
        for(int j = 0; j < 4; ++j){
            int x = corners[j][0];
            int y = corners[j][1];

            int ax = (x - ox)*sx;
            int ay = (y - oy)*sy;

            int rx = ax * c - ay * s;
            int ry = ax * s + ay * c;

            world[j][0] = px + rx;
            world[j][1] = py + ry;
        }
        int minx = world[0][0];
        int maxx = world[0][0];
        int miny = world[0][1];
        int maxy = world[0][1];

        for(int j = 1; j < 4; ++j){
            minx = std::min(minx, world[j][0]);
            maxx = std::max(maxx, world[j][0]);
            miny = std::min(miny, world[j][1]);
            maxy = std::max(maxy, world[j][1]);
        }
        std::cout << nom << " COINS";

        for(int j = 0; j < 4; ++j){
            std::cout << " " << world[j][0] << " " << world[j][1];
        }

        std::cout << std::endl;
        std::cout << nom << " BOITE "
          << minx << " "
          << miny << " "
          << maxx << " "
          << maxy << std::endl;
    }
    std::cout << "REFUSES " << refuses << std::endl;
    return 0;
}