#include "rasterization.h"

namespace egc {

	BoundingBox getBB(const std::vector<egc::vec4>& triangleVertices)
	{
		int x_min = 1000000, x_max = 0;
		int y_min = 1000000, y_max = 0;

		for (int i = 0; i < triangleVertices.size(); i++) {
			if (triangleVertices.at(i).x > x_max)
				x_max = triangleVertices.at(i).x;
			if (triangleVertices.at(i).x < x_min)
				x_min = triangleVertices.at(i).x;
			if (triangleVertices.at(i).y > y_max)
				y_max = triangleVertices.at(i).y;
			if (triangleVertices.at(i).y < y_min)
				y_min = triangleVertices.at(i).y;
		}
		return BoundingBox(x_min, x_max, y_min, y_max);
	}

	float f_bc(const std::vector<egc::vec4>& triangleVertices, float x, float y) {
		vec4 B = triangleVertices.at(1);
		vec4 C = triangleVertices.at(2);
		float a = B.y - C.y;
		float b = C.x - B.x;
		float c = B.x * C.y - C.x * B.y;
		return x * a + y * b + c;
	}

	float f_ca(const std::vector<egc::vec4>& triangleVertices, float x, float y) {
		vec4 C = triangleVertices.at(2);
		vec4 A = triangleVertices.at(0);
		float a = C.y - A.y;
		float b = A.x - C.x;
		float c = C.x * A.y - A.x * C.y;
		return x * a + y * b + c;
	}

	

	float lineFunction(egc::vec2 point1, egc::vec2 point2, egc::vec2 pixel)
	{
		float a = point1.y - point2.y;
		float b = point2.x - point1.x;
		float c = point1.x * point2.y - point2.x * point1.y;
		return pixel.x * a + pixel.y * b + c;
	}

	void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma)
	{
		vec2 A(triangleVertices.at(0).x, triangleVertices.at(0).y);
		vec2 B(triangleVertices.at(1).x, triangleVertices.at(1).y);
		vec2 C(triangleVertices.at(2).x, triangleVertices.at(2).y);

		alpha = lineFunction(B, C, pixel) / lineFunction(B, C, A);
		beta = lineFunction(C, A, pixel) / lineFunction(C, A, B);
		gamma = 1 - alpha - beta;
	}

	void rasterizeTriangle(SDL_Renderer* renderer, const std::vector<egc::vec4>& triangleVertices, const std::vector<egc::vec4>& triangleColors) {
		BoundingBox bbox = getBB(triangleVertices);

		for (int i = bbox.xMin; i <= bbox.xMax; i++)
			for (int j = bbox.yMin; j <= bbox.yMax; j++) {
				float alpha, beta, gamma;
				alpha = beta = gamma = 0.0f;
				computeAlphaBetaGamma(triangleVertices, vec2(i, j), alpha, beta, gamma);
				if ((0 <= alpha && alpha <= 1) && (0 <= beta && beta <= 1) && (0 <= gamma && gamma <= 1)) {
					float pixel_depth = triangleVertices.at(0).z * alpha + triangleVertices.at(1).z * beta + triangleVertices.at(2).z *gamma;
					
					if (depthBuffer[i][j] < pixel_depth) {
						vec4 final_color = triangleColors.at(0) * alpha + triangleColors.at(1) * beta + triangleColors.at(2) * gamma;
						SDL_SetRenderDrawColor(renderer, final_color.r, final_color.g, final_color.b, SDL_ALPHA_OPAQUE);
						SDL_RenderDrawPoint(renderer, i, j);
						depthBuffer[i][j] = pixel_depth;
					}
				}
			}
	}

	void clearDepthBuffer() {
		for (int i = 0; i < WINDOW_HEIGHT; i++)
			for (int j = 0; j < WINDOW_WIDTH; j++) {
				depthBuffer[i][j] = -1;
			}
	}

}