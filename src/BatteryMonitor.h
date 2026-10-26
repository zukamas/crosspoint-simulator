#pragma once

#include <cstdint>

// Host stub aligned with freeink-sdk BatteryMonitor (Touch chrome / About).
class BatteryMonitor {
 public:
  static constexpr int8_t PIN_NONE = -1;

  struct Status {
    bool supported = true;
    bool percentageKnown = true;
    bool millivoltsKnown = true;
    bool chargingKnown = false;
    bool externalPowerKnown = false;
    uint16_t percentage = 100;
    uint16_t millivolts = 4200;
    bool charging = false;
    bool externalPower = false;
    int32_t pm1VinMv = -1;
    int32_t pm1VinOutMv = -1;
    int16_t pm1PowerSource = -1;
  };

  BatteryMonitor() : _adcPin(PIN_NONE), _dividerMultiplier(2.0f), _chargeStatusPin(PIN_NONE) {}

  explicit BatteryMonitor(int8_t adcPin, float dividerMultiplier = 2.0f, int8_t chargeStatusPin = PIN_NONE)
      : _adcPin(adcPin), _dividerMultiplier(dividerMultiplier), _chargeStatusPin(chargeStatusPin) {}

  uint16_t readPercentage() const { return 100; }
  bool readPercentageChecked(uint16_t& out) const {
    out = 100;
    return true;
  }
  Status readStatus() const { return Status{}; }
  uint16_t readMillivolts() const { return 4200; }
  double readVolts() const { return 4.2; }
  bool isCharging() const { return false; }

  static uint16_t percentageFromMillivolts(uint16_t millivolts) {
    if (millivolts == 0) return 0;
    if (millivolts >= 4100) return 100;
    if (millivolts <= 3300) return 0;
    return static_cast<uint16_t>(((millivolts - 3300) * 100) / 800 / 10 * 10);
  }

  static uint16_t percentageFromMillivolts(uint16_t millivolts, uint16_t previousPercent) {
    const uint16_t next = percentageFromMillivolts(millivolts);
    if (previousPercent > 100) return next;
    if (next == previousPercent) return next;
    const int delta = next > previousPercent ? next - previousPercent : previousPercent - next;
    return delta <= 10 ? previousPercent : next;
  }

 private:
  int8_t _adcPin;
  float _dividerMultiplier;
  int8_t _chargeStatusPin;
};
