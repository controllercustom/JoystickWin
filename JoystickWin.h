/*
  JoystickWin.h
*/

#ifndef JOYSTICKWIN_H_
#define JOYSTICKWIN_H_

#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

#define AXIS_MIN  (0)
#define AXIS_MID  (AXIS_MAX / 2)
#define AXIS_MAX  (0xFFFFUL)
#define BUTTONS_MAX (32)

//================================================================================
//================================================================================
//  JoystickWin

// This overlays the data format specified by the HID report descriptor in
// JoystickWin.cpp
typedef struct __attribute__((__packed__)) {
  uint32_t buttons;
  uint8_t  hat1:4;
  uint8_t  hat2:4;
  uint16_t x;
  uint16_t y;
  uint16_t z;
  uint16_t rx;
  uint16_t ry;
  uint16_t rz;
  uint16_t rudder;
  uint16_t throttle;
  uint16_t accelerator;
  uint16_t brake;
  uint16_t steering;
} JoystickWin_Report_t;

class JoystickWin_ {
private:
  JoystickWin_Report_t _hid_report;
public:
  JoystickWin_(void);
  void begin(void);
  void end(void);
  void press(int b);
  void release(int b);
  void releaseAll();
  bool isPressed(int b);
  void hat1(int d);
  void hat2(int d);
  void x(uint16_t a) { _hid_report.x = a; }
  void y(uint16_t a) { _hid_report.y = a; }
  void z(uint16_t a) { _hid_report.z = a; }
  void rx(uint16_t a) { _hid_report.rx = a; }
  void ry(uint16_t a) { _hid_report.ry = a; }
  void rz(uint16_t a) { _hid_report.rz = a; }
  void rudder(uint16_t a) { _hid_report.rudder = a; }
  void throttle(uint16_t a) { _hid_report.throttle = a; }
  void accelerator(uint16_t a) { _hid_report.accelerator = a; }
  void brake(uint16_t a) { _hid_report.brake = a; }
  void steering(uint16_t a) { _hid_report.steering = a; }
  void sendReport();
};
extern JoystickWin_ JoystickWin;

#endif
#endif  // JOYSTICKWIN_H_
