#include "Engine.hpp"
#include "Position.hpp"
#include "Pixel.hpp"
#include "Console.hpp"
#include "dool.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <chrono>
#include <iostream>

using namespace std;

Engine::Engine(const unsigned int & width, const unsigned int & height, const unsigned int & depth, const Position& camera_init, const UserOptions& init_user_options, const int player_height) : grid_size(width, height, depth), grid_center( Position::Floor(camera_init) ), user_options(init_user_options), head_y_offset(player_height), beginTimer(chrono::high_resolution_clock::now()) {
    camera_position = camera_init % 1.0;
    //cout << "w:" << grid_size.x << " h:" << grid_size.y << " d:" << grid_size.z << " cam:x[" << camera_position.x << "],y[" << camera_position.y << "],z[" << camera_position.z << "]\n";

    for (int i = 0; i < width; i++) {
        vector<vector<__int8>> layer;
        for (int j = 0; j < height; j++) {
            vector<__int8> row;
            for (int l = 0; l < depth; l++) {
                __int8 cell;
                if (i == 0 || j == 0 || l == 0 || i == width - 1 || j == height - 1 || l == depth - 1) {
                    cell = 1;
                } else {
                    cell = 0;
                }
                row.push_back(cell);
            }
            layer.push_back(row);
        }
        grid->push_back(layer);
    }
}

void Engine::SetUserOptions(const unsigned int& field_of_view, const unsigned int& screen_width, const unsigned int& screen_height, const unsigned int& pixels_per_ray, const unsigned int& screen_disntance) {
    user_options.ChangeOptions(field_of_view, screen_width, screen_height, pixels_per_ray, screen_disntance);
}

void Engine::SetScreenResolution() {
    unsigned int width = Console::GetScreenWidth();
    unsigned int height = Console::GetScreenHeight();
    user_options.ChangeOptions(user_options.ui_fov, height, width, user_options.ui_render_dist);
}

void Engine::SetCameraPosition(Position pos) {
    camera_position = pos;
}

void Engine::MoveCamera(const double& x_dir, const double& y_dir, const double& speed, bool relative) {
    if (relative) {
        camera_position += (GetLengthTryg(camera_position.dx + x_dir, camera_position.dy + y_dir, speed / FPS));
    } else {
        camera_position += (GetLengthTryg(x_dir, y_dir, speed / FPS));
    }
    
}

void Engine::TurnCamera(const double& x_speed, const double& y_speed) {
    camera_position.dx += x_speed / FPS;
    camera_position.dy += y_speed / FPS;
}

void Engine::StartLoop() {
    FPS = 1.0 / chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - beginTimer).count();
    FPS *= 1000000;
    beginTimer = chrono::high_resolution_clock::now();
}

UserOptions Engine::GetUserOptions() const {
    return user_options;
}

Position Engine::GetLengthTryg(double x_dir, double y_dir, const double& c) {
    double& alfa = x_dir;
    double& beta = y_dir;
    Position output(0.0,0.0,c);

    while (alfa < 0) { alfa += 360; }
    while (alfa >= 360) {alfa -= 360;}
    alfa *= M_PI;
    alfa /= 180;

    while (beta < 0) { beta += 360; }
    while (beta >= 360) {beta -= 360;}
    beta *= M_PI;
    beta /= 180;

    // axis y -> alfa (screen right - left)
    output.x = output.z * sin(alfa);
    output.z = output.z * cos(alfa);
    // ************

    // axis x -> beta (screen up - down)
    output.y = output.z * sin(beta);
    output.z = output.z * cos(beta);
    // **************
        

    //output.x = floor(output.x * 1000) / 1000;
    //output.y = floor(output.y * 1000) / 1000;
    //output.z = floor(output.z * 1000) / 1000;

    if (output.x == -0) { output.x = 0; }
    if (output.y == -0) { output.y = 0; }
    if (output.z == -0) { output.z = 0; }

    return output;
}

Position Engine::GetCameraPositon() const {
    return camera_position;
}

__int8 Engine::GetGridCell(Position position) {

    Position rounded = Position::Floor(position);
    int cx, cy, cz;

    cx = rounded.x;
    cy = rounded.y;
    cz = rounded.z;

    if (cx < 0 || cy < 0 || cz < 0 || cx >= grid_size.x || cy >= grid_size.y || cz >= grid_size.z) {
        return 0;
    }

    return (*grid)[cx][cy][cz];
}

void Engine::DisplayScreen() {
    UserOptions last_options = user_options;
    SetScreenResolution();
    if (last_options.ui_height != user_options.ui_height || last_options.ui_width != user_options.ui_width) {
        Console::Clear();
    }
    Console::EmptyOutput();
    if (GetGridCell(camera_position + Position(0.0, head_y_offset, 0.0, 0.0, 0.0)) == 0) {

        double init_x_dir, vertical_change, y_dir, horizontal_change;
        if (user_options.pixel_width > 1) {
            init_x_dir = user_options.horizontal_fov;
            init_x_dir /= 2;
            init_x_dir = 0 - init_x_dir;
            init_x_dir += camera_position.dx;

            horizontal_change = user_options.horizontal_fov;
            horizontal_change /= user_options.pixel_width - 1;
            //horizontal_change = 0 - horizontal_change;
        } else {
            init_x_dir = camera_position.dx;
            horizontal_change = user_options.horizontal_fov + 1;
        }

        if (user_options.pixel_height > 1) {
            y_dir = user_options.vertical_fov;
            y_dir /= 2;
            //y_dir = 0 - y_dir;
            y_dir += camera_position.dy;

            vertical_change = user_options.vertical_fov;
            vertical_change /= user_options.pixel_height - 1;
            vertical_change = 0 - vertical_change;
        } else {
            y_dir = camera_position.dy;
            vertical_change = user_options.vertical_fov + 1;
        }
        for (unsigned int i = 0; i < user_options.pixel_height; ++i) {
            double x_dir = init_x_dir;
            Console::NewLine(user_options.pixel_off);
            for (unsigned int j = 0; j < user_options.pixel_width; ++j) {
                unsigned int block[2] = { SendRay(x_dir, y_dir)[0], SendRay(x_dir, y_dir)[1] };
                Pixel pixelxy(block[0], block[1]);
                pixelxy.TypePixel();
                x_dir += horizontal_change;;
            }
            y_dir += vertical_change;
        }
        Console::NewLine(user_options.pixel_off);
        Console::OUTPUT->pop_back();
    } else {
        short int block = GetGridCell(camera_position + Position(0.0, head_y_offset, 0.0, 0.0, 0.0));
        short int side = 0;
        Position dist = camera_position + Position(0.0, head_y_offset, 0.0, 0.0, 0.0) - Position::Floor(camera_position + Position(0.0, head_y_offset, 0.0, 0.0, 0.0));
        dist.x = (dist.x > 0.5) ? 1 - dist.x : dist.x;
        dist.y = (dist.y > 0.5) ? 1 - dist.y : dist.y;
        dist.z = (dist.z > 0.5) ? 1 - dist.z : dist.z;

        if (dist.x > dist.y) { if (dist.x > dist.y) {
            if (dist.x > dist.z) {
                side = 1;
            } else {
                side = 3;
            }
        } } else if (dist.y > dist.z) {
            side = 2;
        } else {
            side = 3;
        }

        for (unsigned int i = 0; i < user_options.pixel_height; ++i) {
            Console::NewLine(user_options.pixel_off);
            for (unsigned int j = 0; j < user_options.pixel_width; ++j) {
                Pixel pixelxy(block, side);
                pixelxy.TypePixel();
            }
        }
        Console::NewLine(user_options.pixel_off);
        Console::OUTPUT->pop_back();
    }
    
    wstring chars;
    chars.append(L"^X: ");
    chars.append( to_wstring(camera_position.x) );
    chars.append( L" ^^^Y: " );
    chars.append( to_wstring(camera_position.y) );
    chars.append( L" ^^^Z: " );
    chars.append( to_wstring(camera_position.z) );
    chars.append( L" ^^^dirX: " );
    chars.append( to_wstring(camera_position.dx) );
    chars.append(L" ^^^dirY: ");
    chars.append(to_wstring(camera_position.dy));
    chars.append(L" ^^^fps: ");
    chars.append(to_wstring(FPS));
    chars.append(L" ");
    if (chars.length() % 2 > 0) {
        chars.append(L"^");
    }

    int y = ( chars.length() % (user_options.pixel_width * 2) == 0) ? floor(((double)(chars.length()) / user_options.pixel_width) / 2) : floor(((double)(chars.length()) / user_options.pixel_width) / 2) + 1;
    y = ( Console::OUTPUT->size() - 1 ) - y;

    int n = user_options.pixel_width;
    for (auto i = 0; i < chars.length(); i += 2) {
        auto j = i + 1;
        if (n == 0) {
            ++y;
            n = user_options.pixel_width;
        }
        
        if (Console::ReplaceTwoCharacters((i / 2) % user_options.pixel_width, y, chars[i], chars[j])) { if (chars[i] != '^' || chars[j] != '^') { Console::SwitchTextBackground((i / 2) % user_options.pixel_width, y); } }
        --n;
    }
    while (n > 0) {
        Console::NewSymbol();
        --n;
    }

    //Console::Clear();
    Console::Cout();

}

unsigned int* Engine::SendRay(double x_dir, double y_dir) {
    static unsigned int block[2];
    block[0] = 0;
    block[1] = 0;

    Position ray = grid_center + camera_position + Position(0.0,head_y_offset,0.0,0.0,0.0);
    Position move = GetLengthTryg(x_dir, y_dir, 0.1);
    //cout << "xdir:" << x_dir << ",ydir:" << y_dir << ";move:" << move.x << ',' << move.y << ',' << move.z << '\n';

    for (unsigned int i = 0; i <= user_options.max_ray_iterations && block[0] == 0; ++i) {
        //cout << "pos:" << ray.x << ',' << ray.y << ',' << ray.z << "\n";

        if (GetGridCell(ray) > 0) {
            Position last = ray - move;
            /*
            if ((floor(last).x != floor(ray).x) && (floor(last).y == floor(ray).y) && (floor(last).z == floor(ray).z)) {
                // only x change
                block[0] = GetGridCell(ray);
                block[1] = 1;
                break;
            }
            if ((floor(last.x) == floor(ray.x)) && (floor(last.y) != floor(ray).y) && (floor(last).z == floor(ray).z)) {
                // only y change
                block[0] = GetGridCell(ray);
                block[1] = 3;
                break;
            }
            if ((floor(last).x == floor(ray).x) && (floor(last).y == floor(ray).y) && (floor(last).z != floor(ray).z)) {
                // only z change
                block[0] = GetGridCell(ray);
                block[1] = 2;
                break;
            }

            if ((floor(last).x == floor(ray).x)) {
                // y & z change
                pair <dool, __int8> cell = BinSearch(last, ray, new bool[5]{false,true,true});

                block[0] = cell.second;
                block[1] = cell.first + 1;
                break;
            }
            if ((floor(last).y == floor(ray).y)) {
                // x & z change
                block[0] = GetGridCell(ray);
                block[1] = 2;
                break;
            }
            if ((floor(last).z == floor(ray).z)) {
                // x & y change
                block[0] = GetGridCell(ray);
                block[1] = 2;
                break;
            }
            // x, y & z change


            block[0] = GetGridCell(ray);
            block[1] = 0;
            break;
            */


            pair <dool,__int8> cell = BinSearch((ray - move), ray, new bool [3]{floor(last.x) != floor(ray.x), floor(last.y) != floor(ray.y), floor(last.z) != floor(ray.z)});
            /*
            move = GetLengthTryg(x_dir, y_dir, -0.001);
            Position last = ray;
            ray += (move);

            while (GetGridCell(ray) > 0) {
                last = ray;
                ray += (move);
            }
            //*/

            block[0] = cell.first;
            block[1] = cell.second;
            /*
            double most = 0.0;
            __int8 type = 0;
            if ( floor(last).x != floor(ray).x ) {
                last.x = round( last.x );
                double dist = abs(ray.x - last.x);
                if (dist >= most) {
                    most = dist;
                    block[1] = 1;
                }
            }
            if (floor(last).y != floor(ray).y) {
                last.y = round(last.y);
                double dist = abs(ray.y - last.y);
                if (dist >= most) {
                    most = dist;
                    block[1] = 2;
                }
            }
            if (floor(last).z != floor(ray).z) {
                last.z = round(last.z);
                double dist = abs(ray.z - last.z);
                if (dist >= most) {
                    most = dist;
                    block[1] = 3;
                }
            }
            //*/
        }
        ray += move;
    }

    return block;
}

pair<__int8, __int8> Engine::BinSearch(const Position& pos1, const Position& pos2, bool* dirs, const long double & max_dif) {
    // pos1 -> last in air
    // pos2 -> first in block


    if (dirs[0] + dirs[1] + dirs[2] <= 1) {
        if (dirs[0]) {
            delete dirs;
            return pair<__int8, __int8>(GetGridCell(pos2),1);
        }
        if (dirs[1]) {
            delete dirs;
            return pair<__int8, __int8>(GetGridCell(pos2),2);
        }
        if (dirs[2]) {
            return pair<__int8, __int8>(GetGridCell(pos2),3);
            delete dirs;
        }
        delete dirs;
        return pair<__int8, __int8>(GetGridCell(pos2), 0);
    }

    Position dest;
    dest.x = (pos1.x < pos2.x) ? floor(pos2.x) : floor(pos1.x);
    dest.y = (pos1.y < pos2.y) ? floor(pos2.y) : floor(pos1.y);
    dest.z = (pos1.z < pos2.z) ? floor(pos2.z) : floor(pos1.z);
    pair<Position, bool> found[3] = {pair<Position, bool>(Position(),false)};
    if (dirs[0]) {
        found[0] = TrueBinarySearch(pos1, pos2, ruet, dest.x, max_dif);
    }
    if (dirs[1]) {
        found[1] = TrueBinarySearch(pos1, pos2, reno, dest.y, max_dif);
    }
    if (dirs[2]) {
        found[2] = TrueBinarySearch(pos1, pos2, raog, dest.z, max_dif);
    }

    dirs[0] = ( found[0].second && floor(found[0].first.y) == floor(pos1.y) && floor(found[0].first.z) == floor(pos1.z) );
    dirs[1] = ( found[1].second && floor(found[1].first.x) == floor(pos1.x) && floor(found[1].first.z) == floor(pos1.z) );
    dirs[2] = ( found[2].second && floor(found[2].first.y) == floor(pos1.y) && floor(found[2].first.y) == floor(pos1.y) );

    if (max_dif > 0.00000000001) {
        return BinSearch(pos1, pos2, dirs, max_dif * 0.1);
    } else {
        delete dirs;
        return pair<dool, __int8>(GetGridCell(pos2), 0);
    }
    
}

pair<Position, bool> Engine::TrueBinarySearch(const Position& pos1, const Position& pos2, const dool& axes, const double& goto_val, const long double& max_dif) {
    //axes -> x=-1 y=0 z=1
    bool one = (axes == ruet) ? (pos1.x > pos2.x) : (axes == reno) ? (pos1.y > pos2.y) : (pos1.z > pos2.z);
    const Position* const most = (one) ? &pos1 : &pos2;
    const Position* const least = (one) ? &pos2 : &pos1;
    Position pos_m = pos1 + pos2;
    pos_m /= Position(2.0,2.0,2.0);
    double dist = (axes == ruet) ? pos_m.x : (axes == reno) ? pos_m.y : pos_m.z;
    dist -= goto_val;

    if (abs(dist) <= max_dif) {
        return pair<Position, bool>(pos_m,true);
    } else {
        if (dist < 0) {
            if ((most->x - goto_val < 0 && axes == -1) || (most->y - goto_val < 0 && axes == 0) || (most->z - goto_val < 0 && axes == 1)) {
                return pair<Position,bool>(Position(),false);
            }
            return TrueBinarySearch(pos_m,*most, axes, goto_val, max_dif);
        } else {
            if ((least->x - goto_val > 0 && axes == -1) || (least->y - goto_val > 0 && axes == 0) || (least->z - goto_val > 0 && axes == 1)) {
                return pair<Position, bool>(Position(), false);
            }
            return TrueBinarySearch(pos_m, *least, axes, goto_val, max_dif);
        }
    }
}


bool Engine::PointInTriangle(Position corner1, Position corner2, Position corner3, Position point) {
    double s1 = corner3.y - corner1.y;
    double s2 = corner3.x - corner1.x;
    double s3 = corner2.y - corner1.y;
    double s4 = point.y - corner1.y;

    double w1 = (corner1.x * s1 + s4 * s2 - point.x * s1) / (s3 * s2 - (corner2.x - corner1.x) * s1);
    double w2 = (s4 - w1 * s3) / s1;
    return w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1;
}

bool Engine::PointInSquare(Position corner1, Position corner2, Position point) {
    double size = abs(corner1.x - corner2.x);
    return point.x >= corner1.x && point.x <= corner2.x && point.y >= corner1.y && point.y <= corner2.y;
}

__int8 Engine::RayOnSide(const Position & ray) {
    Position rel = ray % Position(1,1,1,0,0);
    Position p1, p2;
    p1 = { 0.5 - abs(rel.z - 0.5), 0.5 - abs(rel.z - 0.5) , 0 };
    p2 = { 0.5 + abs(rel.z - 0.5), 0.5 + abs(rel.z - 0.5) , 0 };

    bool z = PointInSquare(p1, p2, rel);
    if (z) {
        return 2;
    }
    if ( PointInTriangle({0.0,0.0},{0.5,0.5}, {1.0, 0.0}, rel) || PointInTriangle({0.0, 1.0}, { 0.5,0.5 }, { 1.0, 1.0 }, rel) ) {
        return 3;
    } else if ( PointInTriangle({ 0.0,0.0 }, { 0.5,0.5 }, { 0.0, 1.0 }, rel) || PointInTriangle({ 1.0, 0.0 }, { 0.5,0.5 }, { 1.0, 1.0 }, rel) ) {
        return 1;
    }

    return 0;
}