#pragma once

class Position {
    public:
        Position(const double & init_x = 0.0, const double & init_y = 0.0, const double & init_z = 0.0, const double& init_dx = 0.0, const double& init_dy = 0.0);

        static Position Floor(Position position);
        static Position Abs(Position position);
        bool operator>(Position position) const;
        bool operator<(Position position) const;
        bool operator==(Position position) const;
        bool operator!=(Position position) const;
        bool operator<=(Position position) const;
        bool operator>=(Position position) const;

        Position operator+(Position position) const;
        Position operator-(Position position) const;
        Position operator%(Position position) const;
        Position operator*(Position position) const;
        Position operator/(Position position) const;


        void operator=(Position position);
        void operator+=(Position position);
        void operator-=(Position position);
        void operator%=(Position position);
        void operator*=(Position position);
        void operator/=(Position position);

        double x;
        double y;
        double z;
        double dx;
        double dy;
};

static Position floor(Position& pos) {
    return Position::Floor(pos);
}