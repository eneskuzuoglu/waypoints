#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Definition of Waypoint struct
struct Waypoint {
    double x, y, z;
};

// Read waypoints from CSV file
std::vector<Waypoint> readWaypointsFromCSV(const std::string& filePath, bool readAllValues) {
    std::vector<Waypoint> waypoints;
    std::ifstream file(filePath);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
            Waypoint wp;
            int count = 0;
            // Read CSV file delimited by comma
            while (std::getline(iss, token, ',')) {
                if (token.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
                    std::istringstream tokenStream(token);
                    if (count == 0) {
                        tokenStream >> wp.x;
                    }
                    else if (count == 1) {
                        tokenStream >> wp.y;
                    }
                    else if (count == 2 && readAllValues) {
                        tokenStream >> wp.z;
                    }
                    count++;
                }
            }
            waypoints.push_back(wp);
        }
        file.close();
    }
    else {
        std::cerr << "File not found: " << filePath << std::endl;
    }

    return waypoints;
}

int main(int argc, char* argv[]) {
    // Argument check
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " file_path read_all_values(0 or 1)" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    bool readAllValues = (std::stoi(argv[2]) == 1);

    // Read waypoints from CSV file
    std::vector<Waypoint> waypoints = readWaypointsFromCSV(filePath, readAllValues);

    if (waypoints.empty()) {
        std::cerr << "No waypoints found." << std::endl;
        return 1;
    }

    // Print waypoints to console
    std::cout << "Read Waypoints:" << std::endl;
    for (const auto& wp : waypoints) {
        if (readAllValues) {
            std::cout << "X: " << wp.x << ", Y: " << wp.y << ", Z: " << wp.z << std::endl;
        }
        else {
            std::cout << "X: " << wp.x << ", Y: " << wp.y << std::endl;
        }
    }

    return 0;
}
