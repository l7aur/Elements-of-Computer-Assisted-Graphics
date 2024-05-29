#include "clip.h"

namespace egc {

	std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p)
	{
		int x_min = clipWindow.at(0).x;
		int x_max = clipWindow.at(1).x;
		int y_min = clipWindow.at(0).y;
		int y_max = clipWindow.at(3).y;
		int x = p.x;
		int y = p.y;
		std::vector<int> code;
		//above
		if (y < y_min)
			code.push_back(1);
		else
			code.push_back(0);
		//below
		if (y > y_max)
			code.push_back(1);
		else
			code.push_back(0);
		//right
		if (x > x_max)
			code.push_back(1);
		else
			code.push_back(0);
		//left
		if (x < x_min)
			code.push_back(1);
		else
			code.push_back(0);

		return code;
	}

	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2)
	{
		for (int i = 0; i < 4; i++)
			if (cod1.at(i) && cod2.at(i))
				return true;
		return false;
	}

	bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2)
	{
		for (int i = 0; i < 4; i++)
			if (cod1.at(i) || cod2.at(i))
				return false;
		return true;
	}

	//function returns -1 if the line segment cannot be clipped
	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		if (simpleRejection(computeCSCode(clipWindow, p1), computeCSCode(clipWindow, p2)) == true) {
			std::cout << "SIMPLE REJECTION\n";
			return -1;
		}

		int x_min = clipWindow.at(0).x;
		int x_max = clipWindow.at(1).x;
		int y_min = clipWindow.at(0).y;
		int y_max = clipWindow.at(3).y;
		bool FINISHED = false;

		while(!FINISHED) {
			std::vector<int> cod1 = computeCSCode(clipWindow, p1);
			std::vector<int> cod2 = computeCSCode(clipWindow, p2);
			if (simpleAcceptance(cod1, cod2) == true) {
				std::cout << "SIMPLE ACCEPTANCE\n";
				return 0;
			}
			else {
				if (!cod1.at(0) && !cod1.at(1) && !cod1.at(2) && !cod1.at(3)) {
					std::swap(cod1, cod2);
					std::swap(p1.x, p2.x);
					std::swap(p1.y, p2.y);
				}
				int x = p1.x, y = p1.y;
				if (cod1.at(0) && p1.y != p2.y) //above
				{
					x = p1.x + (p2.x - p1.x) * (y_min - p1.y) / (p2.y - p1.y);
					y = y_min;
				}
				else if (cod1.at(1) && p1.y != p2.y) //below
				{
					x = p1.x + (p2.x - p1.x) * (y_max - p1.y) / (p2.y - p1.y);
					y = y_max;
				}
				else if (cod1.at(2) && p1.x != p2.x) //right
				{
					y = p1.y + (p2.y - p1.y) * (x_max - p1.x) / (p2.x - p1.x);
					x = x_max;
				}
				else if (cod1.at(3) && p1.x != p2.x) //left
				{
					y = p1.y + (p2.y - p1.y) * (x_min - p1.x) / (p2.x - p1.x);
					x = x_min;
				}
				p1.x = x, p1.y = y;
			}
		}
		return 0;
	}
}

