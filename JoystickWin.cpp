/*
  JoystickWin.cpp
*/

#include "JoystickWin.h"

#if defined(_USING_HID)

static const uint8_t _hidReportDescriptor[] PROGMEM = {
  0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
  0x09, 0x04,        // Usage (Joystick)
  0xA1, 0x01,        // Collection (Application)
  0x85, 0x04,        //   Report ID (4)
  0x05, 0x09,        //   Usage Page (Button)
  0x19, 0x01,        //   Usage Minimum (0x01)
  0x29, 0x20,        //   Usage Maximum (0x20)
  0x15, 0x00,        //   Logical Minimum (0)
  0x25, 0x01,        //   Logical Maximum (1)
  0x75, 0x01,        //   Report Size (1)
  0x95, 0x20,        //   Report Count (32)
  0x55, 0x00,        //   Unit Exponent (0)
  0x65, 0x00,        //   Unit (None)
  0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x05, 0x01,        //   Usage Page (Generic Desktop Ctrls)
  0x09, 0x39,        //   Usage (Hat switch)
  0x15, 0x00,        //   Logical Minimum (0)
  0x25, 0x07,        //   Logical Maximum (7)
  0x35, 0x00,        //   Physical Minimum (0)
  0x46, 0x3B, 0x01,  //   Physical Maximum (315)
  0x65, 0x14,        //   Unit (System: English Rotation, Length: Centimeter)
  0x75, 0x04,        //   Report Size (4)
  0x95, 0x01,        //   Report Count (1)
  0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x09, 0x39,        //   Usage (Hat switch)
  0x15, 0x00,        //   Logical Minimum (0)
  0x25, 0x07,        //   Logical Maximum (7)
  0x35, 0x00,        //   Physical Minimum (0)
  0x46, 0x3B, 0x01,  //   Physical Maximum (315)
  0x65, 0x14,        //   Unit (System: English Rotation, Length: Centimeter)
  0x75, 0x04,        //   Report Size (4)
  0x95, 0x01,        //   Report Count (1)
  0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x09, 0x01,        //   Usage (Pointer)
  0x15, 0x00,        //   Logical Minimum (0)
  0x27, 0xFF, 0xFF, 0x00, 0x00,  //   Logical Maximum (65534)
  0x75, 0x10,        //   Report Size (16)
  0x95, 0x06,        //   Report Count (6)
  0xA1, 0x00,        //   Collection (Physical)
  0x09, 0x30,        //     Usage (X)
  0x09, 0x31,        //     Usage (Y)
  0x09, 0x32,        //     Usage (Z)
  0x09, 0x33,        //     Usage (Rx)
  0x09, 0x34,        //     Usage (Ry)
  0x09, 0x35,        //     Usage (Rz)
  0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0xC0,              //   End Collection
  0x05, 0x02,        //   Usage Page (Sim Ctrls)
  0x15, 0x00,        //   Logical Minimum (0)
  0x27, 0xFF, 0xFF, 0x00, 0x00,  //   Logical Maximum (65534)
  0x75, 0x10,        //   Report Size (16)
  0x95, 0x05,        //   Report Count (5)
  0xA1, 0x00,        //   Collection (Physical)
  0x09, 0xBA,        //     Usage (Rudder)
  0x09, 0xBB,        //     Usage (Throttle)
  0x09, 0xC4,        //     Usage (Accelerator)
  0x09, 0xC5,        //     Usage (Brake)
  0x09, 0xC8,        //     Usage (Steering)
  0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0xC0,              //   End Collection
  0xC0,              // End Collection
};

//================================================================================
//================================================================================
// JoystickWin

JoystickWin_::JoystickWin_(void) {
  static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
  HID().AppendDescriptor(&node);
}

void JoystickWin_::begin(void) {
  _hid_report.buttons = 0;
  _hid_report.hat1 = 8;
  _hid_report.hat2 = 8;
  _hid_report.x = AXIS_MID;
  _hid_report.y = AXIS_MID;
  _hid_report.z = AXIS_MID;
  _hid_report.rx = AXIS_MID;
  _hid_report.ry = AXIS_MID;
  _hid_report.rz = AXIS_MID;
  _hid_report.rudder = AXIS_MID;
  _hid_report.throttle = AXIS_MID;
  _hid_report.accelerator = AXIS_MID;
  _hid_report.brake = AXIS_MID;
  _hid_report.steering = AXIS_MID;
  sendReport();
}

void JoystickWin_::end(void) {
  begin();
}

void JoystickWin_::sendReport() {
  HID().SendReport(4, (void *)&_hid_report, sizeof(_hid_report));
}

void JoystickWin_::press(int b) {
  constrain(b, 0, BUTTONS_MAX - 1);
  _hid_report.buttons |= (uint32_t)(1UL << b);
}

void JoystickWin_::release(int b) {
  constrain(b, 0, BUTTONS_MAX - 1);
  _hid_report.buttons &= ~(uint32_t)(1UL << b);
}

void JoystickWin_::releaseAll() {
  _hid_report.buttons = 0;
}

bool JoystickWin_::isPressed(int b) {
  constrain(b, 0, BUTTONS_MAX - 1);
  return ((_hid_report.buttons & (uint32_t)(1UL << b)) != 0) ? true : false;
}

void JoystickWin_::hat1(int d) {
  constrain(d, 0, 15);
  _hid_report.hat1 = d;
}

void JoystickWin_::hat2(int d) {
  constrain(d, 0, 15);
  _hid_report.hat2 = d;
}

JoystickWin_ JoystickWin;

#endif
