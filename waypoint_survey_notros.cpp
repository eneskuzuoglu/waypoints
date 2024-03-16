#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector<pair<int, int>> generatePoints(int width, int height, int stepSize) {
    vector<pair<int, int>> points;
    bool moveRight = true; // Initial direction of movement

    // Start from the bottom-left corner
    int x = 0;
    int y = 0;

    // Iterate over the width, adjusting y on each step
    while (x < width) {
        points.push_back(make_pair(x, y));

        // Move right or left based on the current direction
        if (moveRight) {
            x += stepSize;
        } else {
            x -= stepSize;
        }

        // Move one step up on each x step
        y += stepSize;

        // Change the direction when reaching the boundaries
        if (x >= width || x <= 0) {
            moveRight = !moveRight;
            // Adjust y if x reaches the boundary
            y += stepSize;
        }
    }

    return points;
}

int main() {
    int width = 10;
    int height = 10;
    int stepSize = 1;

    vector<pair<int, int>> points = generatePoints(width, height, stepSize);

    // Print the generated points
    cout << "Generated Points:" << endl;
    for (auto point : points) {
        cout << "(" << point.first << ", " << point.second << ")" << endl;
    }

    return 0;
}
