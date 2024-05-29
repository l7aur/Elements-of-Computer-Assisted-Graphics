#pragma once
#include <SDL2/SDL.h>
#include "vec2.h"
#include "vec4.h"
#include "globalVars.h"
#include <vector>


namespace egc {

    struct BoundingBox {
        int xMin = 0, xMax = 0, yMin = 0, yMax = 0;
        BoundingBox(int x, int y, int z, int w) {
            xMin = x;
            xMax = y;
            yMin = z;
            yMax = w;
        }
    };
    BoundingBox getBB(const std::vector<egc::vec4>& triangleVertices);
    float lineFunction(egc::vec2 point1, egc::vec2 point2, egc::vec2 pixel);
	void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma);

	void rasterizeTriangle(SDL_Renderer *renderer, const std::vector<egc::vec4> &triangleVertices, const std::vector<egc::vec4> &triangleColors);
    void clearDepthBuffer();

}

