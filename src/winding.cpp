#include <winding.hpp>

#include <utility>
#include <iostream>

namespace winding_number {
namespace {

struct segment {
    float x1;
    float y1;
    float x2;
    float y2;
};

class GoodWindingNumberAlgorithm : public IWindingNumberAlgorithm {
    std::optional<int> CalculateWindingNumber2D(float x, float y, poly::Polygon polygon) override {

        // Edge cases:
        // polygon is open:
        if (!polygon.IsClosed()) return std::nullopt;

        // point is on edge or vertex of polygon:
        if (PointIntersectsPolygon(x, y, polygon)) {
            // TODO: Figure out how to deal with edges.
            //       This turned out to be harder than it first seemed, and I gave up 0_o
            return 1; // should probably return nullopt
        }
        
        // returns true if point (x,y) is to the left of segment s
        auto point_is_left = [](float x, float y, segment s) {
            if ((s.y1 > y && s.y2 > y) || (s.y1 < y && s.y2 < y)) {
                return false;
            }
            if (s.x1 > x && s.x2 > x) {
                return true;
            }
            if (s.x1 == x && s.x2 == x) {
                return false;
            }
            float segment_slope = (s.x2 - s.x1) / (s.y2 - s.y1);
            float crossing_x = s.x1 + segment_slope * (y - s.y1);

            // return true if x is to the left of crossing x
            return (x < crossing_x);
        };

        float winding_number = 0;

        for (int i = 0; i < polygon.x_vec_.size() - 1; i++) {

            auto s = segment{polygon.x_vec_[i], polygon.y_vec_[i], 
                             polygon.x_vec_[i+1], polygon.y_vec_[i+1]};

            

            // if segment crosses point positive x-axis counter-clockwise
            if (point_is_left(x, y, s) && s.y1 < y && s.y2 > y) {
                winding_number++;
            }

            // if segment crosses point positive x-axis clockwise
            else if (point_is_left(x, y, s) && s.y1 > y && s.y2 < y) {
                winding_number--;
            }

            // These are cases where the polygon crosses the positive x-axis in 2 segments
            else if (point_is_left(x, y, s) && s.y1 == y && s.y2 < y) {
                winding_number -= 0.5;
            }

            else if (point_is_left(x, y, s) && s.y1 == y && s.y2 > y) {
                winding_number += 0.5;
            }
            
            else if (point_is_left(x, y, s) && s.y1 < y && s.y2 == y) {
                winding_number += 0.5;
            }

            else if (point_is_left(x, y, s) && s.y1 > y && s.y2 == y) {
                winding_number -= 0.5;
            }


        }
        return (int)winding_number;
    }

    // Not really used
    bool PointIntersectsPolygon(float x, float y, poly::Polygon polygon) {

        for (int i = 0; i < polygon.x_vec_.size() - 1; i++) {
            
            auto s = segment{polygon.x_vec_[i], polygon.y_vec_[i], 
                             polygon.x_vec_[i+1], polygon.y_vec_[i+1]};

            if (x == s.x1 && y == s.y1) {
                return true;
            }

            if (s.x1 == s.x2) {
                if (x == s.x1 && y >= std::min(s.y1, s.y2) && y <= std::max(s.y1, s.y2)) {
                    return true;
                } else {
                    continue;
                }
            }

            if (x < std::min(s.x1, s.x2) || x > std::max(s.x1, s.x2)) {
                continue;
            }

            float slope = (s.y2 - s.y1) / (s.x2 - s.x1);
            float crossing_y = s.y1 + slope * (x - s.x1);

            if (std::abs(y - crossing_y) <= tolerance()) {
                return true;
            }
        }

        return false;
    }
};



}  // namespace

std::unique_ptr<IWindingNumberAlgorithm> IWindingNumberAlgorithm::Create() {
    return std::make_unique<GoodWindingNumberAlgorithm>();
}

void IWindingNumberAlgorithm::tolerance(float tolerance) noexcept {
    tolerance_ = tolerance;
}

float IWindingNumberAlgorithm::tolerance() const noexcept {
    return tolerance_;
}

std::string IWindingNumberAlgorithm::error_message() const noexcept {
    return error_message_;
}

void IWindingNumberAlgorithm::error_message(std::string error_message) noexcept {
    error_message_ = std::move(error_message);
}

}  // namespace winding_number
