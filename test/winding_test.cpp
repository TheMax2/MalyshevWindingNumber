#include <gtest/gtest.h>

#include <filesystem>  // A C++17 capable compiler is assumed here.
#include <optional>
#include <string>
#include <tuple>

#include <winding.hpp>
#include <poly_io.hpp>

namespace winding_number {

using poly::Polygon;

Polygon defaultSquare() {
    Polygon p;
    p.AppendPoint(0.0, 0.0);
    p.AppendPoint(1.0, 0.0);
    p.AppendPoint(1.0, 1.0);
    p.AppendPoint(0.0, 1.0);
    p.AppendPoint(0.0, 0.0);
    EXPECT_TRUE(p.IsClosed());
    return p;
}

Polygon reverseSquare() {
    Polygon p;
    p.AppendPoint(0.0, 0.0);
    p.AppendPoint(0.0, 1.0);
    p.AppendPoint(1.0, 1.0);
    p.AppendPoint(1.0, 0.0);
    p.AppendPoint(0.0, 0.0);
    EXPECT_TRUE(p.IsClosed());
    return p;
}

Polygon diamond() {
    Polygon p;
    p.AppendPoint(0.0, -1.0);
    p.AppendPoint(1.0, 0.0);
    p.AppendPoint(0.0, 1.0);
    p.AppendPoint(-1.0, 0.0);
    p.AppendPoint(0.0, -1.0);
    EXPECT_TRUE(p.IsClosed());
    return p;
}

Polygon cup() {
    Polygon p;
    p.AppendPoint(0.0, 0.0);
    p.AppendPoint(3.0, 0.0);
    p.AppendPoint(3.0, 3.0);
    p.AppendPoint(2.0, 3.0);
    p.AppendPoint(2.0, 1.0);
    p.AppendPoint(1.0, 1.0);
    p.AppendPoint(1.0, 3.0);
    p.AppendPoint(0.0, 3.0);
    p.AppendPoint(0.0, 0.0);
    EXPECT_TRUE(p.IsClosed());
    return p;
}

Polygon intersection() {
    Polygon p;
    p.AppendPoint(0.0, 0.0);
    p.AppendPoint(1.0, 0.0);
    p.AppendPoint(1.0, 2.0);
    p.AppendPoint(2.0, 2.0);
    p.AppendPoint(2.0, 1.0);
    p.AppendPoint(0.0, 1.0);
    p.AppendPoint(0.0, 0.0);
    EXPECT_TRUE(p.IsClosed());
    return p;
}

Polygon loop() {
    Polygon p;
    p.AppendPoint(0.0, -1.0);
    p.AppendPoint(1.0, 0.0);
    p.AppendPoint(0.0, 1.0);
    p.AppendPoint(-1.0, 0.0);
    p.AppendPoint(0.0, -1.0);
    p.AppendPoint(1.0, -1.0);
    p.AppendPoint(2.0, 0.0);
    p.AppendPoint(0.0, 2);
    p.AppendPoint(-2.0, 0.0);
    p.AppendPoint(-1.0, -1.0);
    p.AppendPoint(0.0, -1.0);
    EXPECT_TRUE(p.IsClosed());
    return p;
}


class WindingNumberTest : public ::testing::Test {
protected:
    WindingNumberTest() :
            reader_(poly::IPolygonReader::Create()),
            algorithm_(IWindingNumberAlgorithm::Create()),
            polygons_file_path_((std::filesystem::current_path() / "polygons.txt").string()),
            tolerance_(1e-6f) {
        algorithm_->tolerance(tolerance_);
    }

    void testWinding(Polygon& p, float x, float y, int expected) {
        auto winding_num = algorithm_->CalculateWindingNumber2D(x, y, p);
        ASSERT_TRUE(winding_num);
        EXPECT_EQ(expected, *winding_num);
    }

    std::unique_ptr<poly::IPolygonReader> reader_;
    std::unique_ptr<IWindingNumberAlgorithm> algorithm_;
    const std::string polygons_file_path_;
    const float tolerance_;
};



TEST_F(WindingNumberTest, FailsWithUnclosedPolygon) {
    Polygon p;
    p.AppendPoint(0.0, 0.0);
    p.AppendPoint(1.0, 0.0);
    p.AppendPoint(1.0, 1.0);
    EXPECT_FALSE(p.IsClosed());
    auto winding_algo = IWindingNumberAlgorithm::Create();
    auto winding_num = winding_algo->CalculateWindingNumber2D(0.0, 0.0, std::move(p));
    // Either this is due to an unimplemented algorithm or it should be std::nullopt -- as it does not make sense to
    // make this call with unclosed polygons.
    EXPECT_FALSE(winding_num);
}

// TODO: Add more expected_winding_numbers to this test, based on results from the polygons.txt file.
TEST_F(WindingNumberTest, CanGetWindingNumbersForPolygonsFromFile) {
    std::vector<std::optional<int>> expected_winding_numbers = {1, -1, 1, std::nullopt, 1};
    auto points_and_polygons = reader_->ReadPointsAndPolygonsFromFile(polygons_file_path_);
    ASSERT_GE(points_and_polygons.size(), expected_winding_numbers.size());
    for (size_t i = 0; i < expected_winding_numbers.size(); ++i) {
        const auto& p = points_and_polygons[i];
        if (expected_winding_numbers[i]) {
            // Only a point and a closed polygon should expect any sort of winding number.
            EXPECT_TRUE(std::get<2>(p).IsClosed(tolerance_));
        }
        auto winding_num = algorithm_->CalculateWindingNumber2D(std::get<0>(p), std::get<1>(p), std::get<2>(p));
        if (winding_num) {
            ASSERT_TRUE(expected_winding_numbers[i]) << "Have a winding number for expected_winding_number[" << i
                                                     << "], which is expected to be missing.";
            EXPECT_EQ(expected_winding_numbers[i], *winding_num);
        } else {
            ASSERT_FALSE(expected_winding_numbers[i]) << "Missing a winding number for expected_winding_number[" << i
                                                      << "], which is expected to exist.";
        }
    }
}


TEST_F(WindingNumberTest, PointOnOriginSquare) {
    Polygon p = defaultSquare();
    testWinding(p, 0.0, 0.0, 1);
}
TEST_F(WindingNumberTest, PointOnCornerSquare) {
    Polygon p = defaultSquare();
    testWinding(p, 1.0, 1.0, 1);
}
TEST_F(WindingNumberTest, PointOnEdgeSquare) {
    Polygon p = defaultSquare();
    testWinding(p, 0.5, 1.0, 1);
}
TEST_F(WindingNumberTest, PointInsideSquare) {
    Polygon p = defaultSquare();
    testWinding(p, 0.5, 0.5, 1);
}


TEST_F(WindingNumberTest, PointOnOriginRvSquare) {
    Polygon p = reverseSquare();
    testWinding(p, 0.0, 0.0, -1);
}
TEST_F(WindingNumberTest, PointOnCornerRvSquare) {
    Polygon p = reverseSquare();
   testWinding(p, 1.0, 1.0, -1);
}
TEST_F(WindingNumberTest, PointOnEdgeRvSquare) {
    Polygon p = reverseSquare();
    testWinding(p, 0.5, 1.0, -1);
}
TEST_F(WindingNumberTest, PointInsideRvSquare) {
    Polygon p = reverseSquare();
    testWinding(p, 0.5, 0.5, -1);
}



TEST_F(WindingNumberTest, PointOnCornerDiamond) {
    Polygon p = diamond();
    testWinding(p, 0.0, 1.0, 1);
}
TEST_F(WindingNumberTest, PointOnEdgeDiamond) {
    Polygon p = diamond();
    testWinding(p, 0.5, 0.5, 1);
}
TEST_F(WindingNumberTest, PointInsideDiamond) {
    Polygon p = diamond();
    testWinding(p, 0.0, 0.0, 1);
}
TEST_F(WindingNumberTest, PointOutsideDiamond) {
    Polygon p = diamond();
    testWinding(p, 1.0, 1.0, 0);
}
TEST_F(WindingNumberTest, PointSlightlyInsideDiamond) {
    Polygon p = diamond();
    testWinding(p, 0.0, -0.9, 1);
    testWinding(p, 0.1, -0.8, 1);
    testWinding(p, 0.9, 0.0, 1);
    testWinding(p, 0.8, 0.1, 1);
}
TEST_F(WindingNumberTest, PointSlightlyOutsideDiamond) {
    Polygon p = diamond();
    testWinding(p, 0.0, -1.1, 0);
    testWinding(p, 0.1, -1.0, 0);
    testWinding(p, 1.1, 0.0, 0);
    testWinding(p, 1.0, 0.1, 0);
}


TEST_F(WindingNumberTest, PointInsideCup) {
    Polygon p = cup();
    testWinding(p, 0.5, 0.5, 1);
    testWinding(p, 0.5, 1.0, 1);
    testWinding(p, 0.5, 1.5, 1);
    testWinding(p, 1.5, 0.5, 1);
    testWinding(p, 2.5, 0.5, 1);
    testWinding(p, 2.5, 1.0, 1);
    testWinding(p, 2.5, 1.5, 1);
}
TEST_F(WindingNumberTest, PointOnEdgeCup) {
    Polygon p = cup();
    testWinding(p, 0.0, 0.0, 1);
    testWinding(p, 1.5, 0.0, 1);
    testWinding(p, 0.0, 1.0, 1);
    testWinding(p, 0.0, 2.0, 1);
    testWinding(p, 0.0, 3.0, 1);
    testWinding(p, 0.5, 3.0, 1);
    testWinding(p, 1.0, 3.0, 1);
    testWinding(p, 1.0, 1.5, 1);
    testWinding(p, 1.5, 1.0, 1);
    testWinding(p, 2.0, 2.0, 1);
    testWinding(p, 2.9, 3.0, 1);
    testWinding(p, 3.0, 3.0, 1);
    testWinding(p, 3.0, 1.0, 1);
    testWinding(p, 3.0, 0.0, 1);
}
TEST_F(WindingNumberTest, PointInsideButActuallyNotInsideCup) {
    Polygon p = cup();
    testWinding(p, 1.5, 1.5, 0);
    testWinding(p, 1.5, 2.0, 0);
    testWinding(p, 1.5, 3.0, 0);
}
TEST_F(WindingNumberTest, PointOutsideCup) {
    Polygon p = cup();
    testWinding(p, -1.0, 0.0, 0);
    testWinding(p, -1.0, 0.5, 0);
    testWinding(p, -1.0, 1.0, 0);
    testWinding(p, -1.0, 2.0, 0);
    testWinding(p, -1.0, 3.0, 0);
    testWinding(p, -1.0, 4.0, 0);
    testWinding(p,  4.0, 0.0, 0);
    testWinding(p,  4.0, 4.0, 0);
    testWinding(p, 1.5, -3.0, 0);
    testWinding(p,  1.5, 10.0, 0);
}


TEST_F(WindingNumberTest, PointInsideIntersection) {
    Polygon p = intersection();
    testWinding(p, 0.5, 0.5, 1);
    testWinding(p, 1.5, 1.5, -1);
}
TEST_F(WindingNumberTest, PointOutsideIntersection) {
    Polygon p = intersection();
    testWinding(p, 0.5, 1.5, 0);
    testWinding(p, 1.5, 0.5, 0);
}


}  // namespace winding_number
