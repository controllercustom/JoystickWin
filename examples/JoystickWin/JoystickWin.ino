#include "JoystickWin.h"

void setup() {
#if defined(ARDUINO_ARCH_RENESAS_UNO) || defined(ARDUINO_SAM_DUE)
  Serial.begin(115200);
  while (!Serial && (millis() < 3000)) delay(10);
  Serial.print("sizeof JoystickWin_Report_t: ");
  Serial.println(sizeof(JoystickWin_Report_t));
#endif
  JoystickWin.begin();
}

void loop() {
  static uint8_t count = 0;
  if (count >= BUTTONS_MAX) {
    JoystickWin.releaseAll();
    count = 0;
  }
  JoystickWin.press(count);
  count++;

  // Go through all hat switch directions
  static uint8_t dir = 0;
  JoystickWin.hat1(dir++);
  JoystickWin.hat2(dir++);
  if (dir > 7)
    dir = 0;

  // Move axes to random positions
  JoystickWin.x(random(AXIS_MAX + 1));
  JoystickWin.y(random(AXIS_MAX + 1));
  JoystickWin.z(random(AXIS_MAX + 1));
  JoystickWin.rx(random(AXIS_MAX + 1));
  JoystickWin.ry(random(AXIS_MAX + 1));
  JoystickWin.rz(random(AXIS_MAX + 1));
  JoystickWin.rudder(random(AXIS_MAX + 1));
  JoystickWin.throttle(random(AXIS_MAX + 1));
  JoystickWin.accelerator(random(AXIS_MAX + 1));
  JoystickWin.brake(random(AXIS_MAX + 1));
  JoystickWin.steering(random(AXIS_MAX + 1));

  // The above updates values in RAM. The following
  // sends the values to the USB host.
  JoystickWin.sendReport();

  delay(100);
}
