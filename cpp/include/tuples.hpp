#pragma once

constexpr int VEC   = 0;
constexpr int POINT = 1;

class Tuple {
public:
    Tuple();
    Tuple(double x, double y, double z, double w);

    double& operator[](int index);

    double get_x() const;
    double get_y() const;
    double get_z() const;
    double get_w() const;

    void point();
    bool is_point() const;

    void vector();
    bool is_vector() const;

    bool compare(const Tuple& rhs) const;

    Tuple add(const Tuple& rhs) const;
    Tuple subtract(const Tuple& rhs) const;
    Tuple negate() const;
    Tuple scale(double scalar) const;
    Tuple dscale(double scalar) const;

    Tuple  normalize() const;
    double magnitude() const;
    double dot(const Tuple& rhs) const;
    Tuple  cross(const Tuple& rhs) const;
    Tuple  reflect(const Tuple& normal) const;

private:
    double bad_index = -1.0;

    double m_x;
    double m_y;
    double m_z;
    double m_w;
};
