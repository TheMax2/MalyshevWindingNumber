#include <winding.hpp>

#include <utility>

namespace winding_number {
namespace {

class BadWindingNumberAlgorithm : public IWindingNumberAlgorithm {
    std::optional<int> CalculateWindingNumber2D(float x, float y, poly::Polygon polygon) override {
        // Clearly we can do better...
        error_message("Unimplemented algorithm.");
        return std::nullopt;
    }
};

}  // namespace

std::unique_ptr<IWindingNumberAlgorithm> IWindingNumberAlgorithm::Create() {
    return std::make_unique<BadWindingNumberAlgorithm>();
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
