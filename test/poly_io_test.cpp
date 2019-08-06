#include <gtest/gtest.h>
#include <poly_io.hpp>

TEST(poly, make_polygon) {
    using namespace poly;

    Polygon p = Polygon();

    p.append_point(0.0, 0.0);
    p.append_point(1.0, 0.0);
    p.append_point(1.0, 1.0);
    p.append_point(0.0, 1.0);
    p.append_point(0.0, 0.0);

    EXPECT_TRUE(p.is_closed());
}