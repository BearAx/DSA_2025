#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

struct Point {
	double x, y;
};

double distanceFromOrigin(const Point& point) {
	return std::sqrt(point.x * point.x + point.y * point.y);
}

void sortPoints(std::vector<Point>& points) {
	size_t n = points.size();
	for (size_t i = 1; i < n; ++i) {
		Point key = points[i];
		size_t j = i - 1;

		while (j >= 0 && distanceFromOrigin(points[j]) > distanceFromOrigin(key)) {
			points[j + 1] = points[j];
			--j;
		}
		points[j + 1] = key;
	}
}

int main() {

	size_t N;
	std::cin >> N;

	std::vector<Point> points(N);
	for (size_t i = 0; i < N; ++i) {
		std::cin >> points[i].x >> points[i].y;
	}

	sortPoints(points);

	for (const auto& point : points) {
		std::cout << std::fixed << std::setprecision(4) << point.x << " " << point.y << std::endl;
	}

	return 0;
}
