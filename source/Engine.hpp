#pragma once

#include "Position.hpp"
#include "UserOptions.hpp"
#include "dool.hpp"

#include <vector>
#include <chrono>

class Engine {
public:
    Engine(const unsigned int & width = 10, const unsigned int & height = 6, const unsigned int & depth = 10, const Position & camera_init = Position(0.0,0.0,0.0,0.0), const UserOptions & init_user_options = UserOptions::UserOptions(), const int player_height = 1.8);
    void SetUserOptions(const unsigned int& field_of_view = 70, const unsigned int& screen_height = 30, const unsigned int& screen_width = 50, const unsigned int& pixels_per_ray = 1, const unsigned int& screen_distance = 10);
    UserOptions GetUserOptions() const;
    Position GetCameraPositon() const;
    void DisplayScreen();
    void SetScreenResolution();
    void SetCameraPosition(Position pos = Position(0.0,0.0,0.0,0.0,0.0));
    void MoveCamera(const double& x_dir, const double& y_dir, const double& speed, bool relative = true);
    void TurnCamera(const double& x_speed, const double& y_speed);
    void StartLoop();
private:
    std::chrono::time_point<std::chrono::steady_clock> beginTimer;
    double FPS;
    const int head_y_offset;
    unsigned int* SendRay(double x_dir, double y_dir);
    std::pair<__int8,__int8> BinSearch(const Position& pos1, const Position& pos2, bool* dirs = new bool[3]{false}, const long double& max_dif = 0.0001);
    std::pair<Position, bool> TrueBinarySearch(const Position& pos1, const Position& pos2, const dool& axes, const double& goto_val, const long double& max_dif);
    __int8 GetGridCell(Position position);
    static Position GetLengthTryg(double x_dir, double y_dir, const double& n = 1.0);
    static bool PointInTriangle(Position corner1, Position corner2, Position corner3, Position point);
    static bool PointInSquare(Position corner1, Position corner2, Position point);
    static __int8 RayOnSide(const Position& ray);
    UserOptions user_options;
    const Position grid_size;
    const Position grid_center;
    Position camera_position;
    std::vector<std::vector<std::vector<__int8>>> * grid = new std::vector<std::vector<std::vector<__int8>>>;
};