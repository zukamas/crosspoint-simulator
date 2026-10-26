#pragma once

#include <cstdint>

// Touch TROS-m3 and CrossPoint share this surface on the simulator host.
class InputManager {
 public:
  InputManager() = default;

  void begin();
  void beginAsync(uint8_t taskPriority = 2, uint32_t pollMs = 15, uint8_t queueLen = 32);
  void update();

  bool isPressed(uint8_t buttonIndex) const;
  bool wasPressed(uint8_t buttonIndex) const;
  bool wasAnyPressed() const;
  bool wasReleased(uint8_t buttonIndex) const;
  bool wasAnyReleased() const;
  bool isDebouncePending() const;

  unsigned long getHeldTime() const;
  unsigned long getPowerButtonHeldTime() const;
  bool isPowerButtonPressed() const;
  bool isPowerButtonPhysicallyPressed() const;

  static constexpr uint8_t BTN_BACK = 0;
  static constexpr uint8_t BTN_CONFIRM = 1;
  static constexpr uint8_t BTN_LEFT = 2;
  static constexpr uint8_t BTN_RIGHT = 3;
  static constexpr uint8_t BTN_UP = 4;
  static constexpr uint8_t BTN_DOWN = 5;
  static constexpr uint8_t BTN_POWER = 6;

  static constexpr int POWER_BUTTON_PIN = -1;

  bool isTouchPressed() const;
  bool wasTouchReleased() const;
  bool wasTouchPressedAt(float& nx, float& ny) const;
  bool isTouchHeldAt(float& nx, float& ny) const;
  void suppressTouchContact();

  bool popTouchTap(float& nx, float& ny);
  bool popTouchDown(float& nx, float& ny);
  bool popTouchRelease();
  bool popSwipe(float& nxStart, float& nyStart, float& nxEnd, float& nyEnd);
  bool popMultiTouchSwipe(uint8_t& contactCount, float& nxStart, float& nyStart, float& nxEnd, float& nyEnd,
                          unsigned long& durationMs);
  bool popMultiTouchRotation(float& degrees, float& nxCenter, float& nyCenter, unsigned long& durationMs);
  bool popMultiTouchPinch(float& scale, float& nxCenter, float& nyCenter, unsigned long& durationMs);
  bool popMultiTouchTap(uint8_t& contactCount, float& nx, float& ny, unsigned long& durationMs);
  bool hasTouch() const;

  bool popPress(uint8_t& button);
  bool popHomeKey(uint8_t& kind);
  bool homeKeyEventsQueued() const;
  bool wasHomeKeyTapped() const;
  bool wasHomeKeyLongPressed() const;
  bool popTouchLongHoldRelease(unsigned long& heldMs);

  static const char* getButtonName(uint8_t buttonIndex);
};
