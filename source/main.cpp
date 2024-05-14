#include "Engine.hpp"
#include "Position.hpp"
#include "Console.hpp"
#include "Symbol.hpp"
#include "MySql.hpp"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

//*/
int main() {

    /*
    Position p1 = { 1.2,2.0,3.1 };
    Position p2 = { 0.9,1.7,2.9 };
    Position pa = Position::Add(p1, p2);
    Position ps = Position::Div(pa, { 2,2,2 });

    cout << 'x' << ':' << ' ' << p1.x << ',' << ' ' << 'y' << ':' << ' ' << p1.y << ',' << ' ' << 'z' << ':' << ' ' << p1.z;
    cout << '\n' << 'x' << ':' << ' ' << p2.x << ',' << ' ' << 'y' << ':' << ' ' << p2.y << ',' << ' ' << 'z' << ':' << ' ' << p2.z;
    cout << '\n' << 'x' << ':' << ' ' << pa.x << ',' << ' ' << 'y' << ':' << ' ' << pa.y << ',' << ' ' << 'z' << ':' << ' ' << pa.z;
    cout << '\n' << 'x' << ':' << ' ' << ps.x << ',' << ' ' << 'y' << ':' << ' ' << ps.y << ',' << ' ' << 'z' << ':' << ' ' << ps.z;
    //*/
    //*
    MYSQL_RES* res;
    MYSQL_ROW row;

    MySql my_sql("uju.h.filess.io", "TerminalGame1_fedsilence", "499620e6764204928596e4206b1f8028234578f2", "TerminalGame1_fedsilence",3305);

    res = my_sql.RunQuery("SELECT * FROM Users");
    cout << "Table:\n";
    //Position player;
    while (row = mysql_fetch_row(res)) {
        for (size_t i = 0; i < 7; i++) {
            cout << row[i] << " | ";
        }
        cout << '\n';
    }
    mysql_free_result(res);
    //*/
    
    //*
    vector<vector<Symbol>> texts;
    Console::OUT_TYPE = 0;
    Console::OUTPUT = &texts;

    Position player = { 5.0,5.0,5.0,0.0,0.0 };

    Engine engine1(10, 10, 10, Position(0.0, 0.0, 0.0, 0.0, 0.0), UserOptions::UserOptions(140, 20, 10, 14, 1));
    engine1.SetCameraPosition(player);
    bool update = true;
    while (true) {
        engine1.StartLoop();
        
        char action;
        action = Console::GetKey();
        
        update = true;
        if (action == 'w') {
            engine1.MoveCamera(0, 0, 10);
        }
        if (action == 's') {
            engine1.MoveCamera(180, 0, 10);
        }
        if (action == 'a') {
            engine1.MoveCamera(-90, 0, 10);
        }
        if (action == 'd') {
            engine1.MoveCamera(90, 0, 10);
        }
        if (action == 'q') {
            engine1.MoveCamera(0, -90, 10,false);
        }
        if (action == ' ') {
            engine1.MoveCamera(0, 90, 10,false);
        }
        if (action == 'j') {
            engine1.TurnCamera(-20, 0);
        }
        if (action == 'l') {
            engine1.TurnCamera(20, 0);
        }
        if (action == 'i') {
            engine1.TurnCamera(0, 20);
        }
        if (action == 'k') {
            engine1.TurnCamera(0, -20);
        }

        //*
        string command = "UPDATE Users\nSET posX = " + to_string(engine1.GetCameraPositon().x) + ", posY = " + to_string(engine1.GetCameraPositon().y) + ", posZ = " + to_string(engine1.GetCameraPositon().z) + ", dirX = " + to_string(engine1.GetCameraPositon().dx) + ", dirY = " + to_string(engine1.GetCameraPositon().dy) + "\nWHERE ID = " + to_string(my_sql.player_id);
        res = my_sql.RunQuery(command.c_str());
        mysql_free_result(res);
        //*/
        //*
        engine1.DisplayScreen();
    }
    //*/

    return 0;
}