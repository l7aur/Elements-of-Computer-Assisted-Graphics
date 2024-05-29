#include "clip.h"

namespace egc {

    //Cyrus-Beck clipping algorithm
    //clipWindow specifies the vertices that define the clipping area in conterclockwise order
    //and can represent any convex polygon
    //function returns -1 if the line segment cannot be clipped
    int lineClip_CyrusBeck(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
        std::vector<vec3> normals;
        std::vector<vec3> edge_points;
        for (int i = 0; i < clipWindow.size(); i++) {
            int y = clipWindow.at((i + 1) % clipWindow.size()).x - clipWindow.at(i).x;
            int x = clipWindow.at(i).y - clipWindow.at((i + 1) % clipWindow.size()).y;
            normals.push_back(vec3(x, y, 1)); 
            edge_points.push_back(vec3((clipWindow.at(i).x + clipWindow.at((i + 1) % clipWindow.size()).x) / 2,
                (clipWindow.at(i).y + clipWindow.at((i + 1) % clipWindow.size()).y) / 2,
                1));
        }
        vec3 D = p2 - p1;

        if (p1.x == p2.x && p1.y == p2.y) {
            std::cout << "DEGENRATED LINE\n";
            return -1;
        }
        float tE = 0;
        float tL = 1;
        for (int i = 0; i < clipWindow.size(); i++) {
            float prod = dotProduct(normals.at(i), D);
            if (prod != 0) {
                float t = dotProduct(normals.at(i), (p1 - edge_points.at(i))) / (-prod);
                if (prod > 0) {
                    tL = std::min(tL, t);
                }
                if (prod < 0) {
                    tE = std::max(tE, t);
                }
            }
        }
        if (tE > tL)
            return -1;

        vec3 new_p1 = p1 + (p2 - p1) * tE;
        vec3 new_p2 = p1 + (p2 - p1) * tL;
        p1 = new_p1;
        p2 = new_p2;
        return 0;
    }
}

