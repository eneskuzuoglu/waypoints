#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Waypoint struct tanımı
struct Waypoint {
    double x, y, z;
};

// Dosyadan waypoint'leri oku
std::vector<Waypoint> readWaypointsFromFile(const std::string& filePath) {
    std::vector<Waypoint> waypoints;
    std::ifstream file(filePath);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Waypoint wp;
            if (iss >> wp.x >> wp.y >> wp.z) {
                waypoints.push_back(wp);
            }
        }
        file.close();
    }
    else {
        std::cerr << "Dosya bulunamadı: " << filePath << std::endl;
    }

    return waypoints;
}

int main() {
    // Dosyadan waypoint'leri oku
    std::vector<Waypoint> waypoints = readWaypointsFromFile("waypoints.txt");

    if (waypoints.empty()) {
        std::cerr << "Waypoint'ler bulunamadı." << std::endl;
        return 1;
    }

    // Waypoint'leri ekrana yazdır
    std::cout << "Okunan Waypoint'ler:" << std::endl;
    for (const auto& wp : waypoints) {
        std::cout << "X: " << wp.x << ", Y: " << wp.y << ", Z: " << wp.z << std::endl;
    }

    return 0;
}
