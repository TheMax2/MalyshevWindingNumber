#ifndef POLY_IO_HPP_
#define POLY_IO_HPP_

#include <string>
#include <vector>

namespace poly {
struct Polygon {
    Polygon(size_t num = 100);

    void append_point(float x, float y);
    bool is_closed() const;

    size_t size() const;

    // data members
    std::vector<float> x_vec;
    std::vector<float> y_vec;

};

std::vector<Polygon> read_polygon(const std::string& filename);

}  // namespace poly

#endif
