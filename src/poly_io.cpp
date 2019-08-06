#include <poly_io.hpp>
#include <cassert>

namespace poly {

Polygon::Polygon(size_t num) {
    x_vec.reserve(num);
    y_vec.reserve(num);
}

void Polygon::append_point(float x, float y) {
    x_vec.push_back(x);
    y_vec.push_back(y);
}

bool Polygon::is_closed() const {
    //TODO: tolerances?
    return x_vec.front() == x_vec.back() && y_vec.front() == y_vec.back();
}

size_t Polygon::size() const {
    size_t x_vec_size = x_vec.size();
    assert(x_vec_size == y_vec.size());
    return x_vec_size;
}

std::vector<Polygon> read_polygon(const std::string& filename) {
    std::vector<Polygon> polygons = std::vector<Polygon>();
    
    return polygons;
}

}  // namespace poly