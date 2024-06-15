#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include "tuples.hpp"
#include "utils.hpp"

Tuple::Tuple() : m_x(0), m_y(0), m_z(0), m_w(0) {}

Tuple::Tuple(double x, double y, double z, double w) : m_x(x), m_y(y), m_z(z), m_w(w) {}

double& Tuple::operator[](int index) {
    switch (index) {
        case 0:
            return m_x;
        case 1:
            return m_y;
        case 2:
            return m_z;
        case 3:
            return m_w;
    }

    return bad_index;
}

double Tuple::get_x() const {
    return m_x;
}

double Tuple::get_y() const {
    return m_y;
}

double Tuple::get_z() const {
    return m_z;
}

double Tuple::get_w() const {
    return m_w;
}

void Tuple::point() {
    m_w = POINT;
}

bool Tuple::is_point() const {
    return m_w == POINT;
}

void Tuple::vector() {
    m_w = VEC;
}

bool Tuple::is_vector() const {
    return m_w == VEC;
}

bool Tuple::compare(const Tuple& rhs) const {
    if (!equals(m_x, rhs.m_x)) {
        return 0;
    }
    if (!equals(m_y, rhs.m_y)) {
        return 0;
    }
    if (!equals(m_z, rhs.m_z)) {
        return 0;
    }
    if (!equals(m_w, rhs.m_w)) {
        return 0;
    }
    return 1;
}

Tuple Tuple::add(const Tuple& rhs) const {
    Tuple out;
    out.m_x = m_x + rhs.m_x;
    out.m_y = m_y + rhs.m_y;
    out.m_z = m_z + rhs.m_z;
    out.m_w = m_w + rhs.m_w;
    return out;
}

Tuple Tuple::subtract(const Tuple& rhs) const {
    Tuple out;
    out.m_x = m_x - rhs.m_x;
    out.m_y = m_y - rhs.m_y;
    out.m_z = m_z - rhs.m_z;
    out.m_w = m_w - rhs.m_w;
    return out;
}

Tuple Tuple::negate() const {
    Tuple zt = { 0, 0, 0, 0 };
    return zt.subtract(*this);
}

Tuple Tuple::scale(double scalar) const {
    Tuple out;
    out.m_x = m_x * scalar;
    out.m_y = m_y * scalar;
    out.m_z = m_z * scalar;
    out.m_w = m_w;
    return out;
}

Tuple Tuple::dscale(double scalar) const {
    Tuple out;
    out.m_x = m_x / scalar;
    out.m_y = m_y / scalar;
    out.m_z = m_z / scalar;
    out.m_w = m_w;
    return out;
}

Tuple Tuple::normalize() const {
    Tuple  out;
    double m = magnitude();
    out.m_x  = m_x / m;
    out.m_y  = m_y / m;
    out.m_z  = m_z / m;
    out.m_w  = m_w;
    return out;
}

double Tuple::magnitude() const {
    double m = pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2) + pow(m_w, 2);
    return sqrt(m);
}

double Tuple::dot(const Tuple& rhs) const {
    double sum = 0;
    sum += m_x * rhs.m_x;
    sum += m_y * rhs.m_y;
    sum += m_z * rhs.m_z;
    sum += m_w * rhs.m_w;
    return sum;
}

Tuple Tuple::cross(const Tuple& rhs) const {
    Tuple out;
    out.m_x = (m_y * rhs.m_z) - (m_z * rhs.m_y);
    out.m_y = (m_z * rhs.m_x) - (m_x * rhs.m_z);
    out.m_z = (m_x * rhs.m_y) - (m_y * rhs.m_x);
    out.m_w = rhs.m_w;
    return out;
}

Tuple Tuple::reflect(const Tuple& normal) const {
    Tuple tmp = normal.scale(2);

    double d    = dot(normal);
    Tuple  tmp2 = tmp.scale(d);

    return subtract(tmp2);
}
