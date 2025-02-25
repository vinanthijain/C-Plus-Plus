#include<iostream>
#include<stdio.h>
#include<vector>
#include <boost/optional.hpp>
using namespace std;
struct VehicleStatusUpdateParams {
    std::optional<uint16_t> range;
    std::optional<int16_t> outsideTemperature;
    std::optional<bool> rangeWarning;
    std::optional<uint16_t> rangeGasoline;
    std::optional<uint16_t> rangeDiesel;
    std::optional<uint16_t> rangeElectric;
    std::optional<uint16_t> rangeCNG;
    std::optional<bool> rangeWarningGasoline;
    std::optional<bool> rangeWarningDiesel;
    std::optional<bool> rangeWarningElectric;
    std::optional<bool> rangeWarningCNG;
    std::vector<uint8_t> toPayload() const;
    std::string toString() const;
};
int main()
{
	VehicleStatusUpdateParams& vehicleStatusParams;
}
