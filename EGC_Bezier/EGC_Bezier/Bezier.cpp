#include "Bezier.h"
#include "math.h"
#include <vector>

//Return the value of P(t), where t is in [0,1]
vec2 getParametricPoint(float t, vec2 p0, vec2 p1) {
	//P(t) = (1 - t)*P0 + t*P1
	vec2 point;
	point = p0 * (1 - t) + p1 * t;
	return point;
}

//Paint the pixels that are on the line P0P1
void drawParametricLinePoints(vec2 p0, vec2 p1, SDL_Renderer* renderer) {
	//Hint: To paint a single pixel, you can use the function: SDL_RenderDrawPoint(renderer, x, y)
	for (float t = 0.0; t <= 1.0; t += 0.00005) {
		vec2 point = getParametricPoint(t, p0, p1);
		SDL_RenderDrawPoint(renderer, point.x, point.y);
	}
}

//Return the value of B(t), where t is in [0,1]. The value of B(t) is computed by taking into account all the 
//controll points contained within the input vector

int combNumber(int n, int i) {
	int rez = 1;
	if (n < i)
		exit(-1);
	for (int k = n - i + 1; k <= n; k++)
		rez *= k;
	for (int k = 2; k <= i; k++)
		rez /= k;
	return rez;
}

vec2 getBezierPoint(std::vector<vec2> controlPoints, float t) {
	vec2 point(0.0,0.0);
	int n = controlPoints.size() - 1;
	for (int i = 0; i <= n; i++) {
		point += controlPoints.at(i) * combNumber(n, i) * pow(1 - t, n - i) * pow(t, i);
	}
	return point;
}

//Paint the pixels that are on the Bezier curve defined by the given control points
void drawBezierPoints(std::vector<vec2> controlPoints, SDL_Renderer* renderer) {
	for (float t = 0.0; t <= 1.0; t += 0.00005) {
		vec2 bezierPoint = getBezierPoint(controlPoints, t);
		SDL_RenderDrawPoint(renderer, bezierPoint.x, bezierPoint.y);
	}
}
