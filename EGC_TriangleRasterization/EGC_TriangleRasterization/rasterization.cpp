#include "rasterization.h"

namespace egc {

	float f_ab(const std::vector<egc::vec4>& triangleVertices, float x, float y) {
		vec4 A = triangleVertices.at(0);
		vec4 B = triangleVertices.at(1);
		float a = A.y - B.y;
		float b = B.x - A.x;
		float c = A.x * B.y - B.x * A.y;
		return x * a + y * b + c;
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

	void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma) 
	{
		//TO DO - Compute alfa, beta and gamma => we use the function's input parameters as the return mechanism
		//Store the final results in the input parameters

		vec4 A = triangleVertices.at(0);
		vec4 B = triangleVertices.at(1);
		vec4 C = triangleVertices.at(2);

		alpha = f_bc(triangleVertices, pixel.x, pixel.y) / f_bc(triangleVertices, triangleVertices.at(0).x, triangleVertices.at(0).y);
		beta = f_ca(triangleVertices, pixel.x, pixel.y) / f_ca(triangleVertices, triangleVertices.at(1).x, triangleVertices.at(1).y);
		gamma = 1 - alpha - beta;
	}

	void rasterizeTriangle(SDL_Renderer *renderer, const std::vector<egc::vec4> &triangleVertices, const std::vector<egc::vec4> &triangleColors) {
		//TO DO - Implement the triangle rasterization algorithm
		int x_min = 1000000 , x_max = 0;
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

		for (int i = x_min; i <= x_max; i++)
			for (int j = y_min; j <= y_max; j++) {
				float alpha, beta, gamma;
				alpha = beta = gamma = 0.0f;
				computeAlphaBetaGamma(triangleVertices, vec2(i, j), alpha, beta, gamma);
				if ((0 < alpha && alpha < 1) && (0 < beta && beta < 1) && (0 < gamma && gamma < 1)) {
					vec4 final_color = triangleColors.at(0) * alpha + triangleColors.at(1) * beta + triangleColors.at(2) * gamma;
					SDL_SetRenderDrawColor(renderer, final_color.x, final_color.y, final_color.z, 255);
					SDL_RenderDrawPoint(renderer, i, j);
				}
			}
	}

}