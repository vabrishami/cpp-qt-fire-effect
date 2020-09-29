# Fire effect C++ code

A C++ code to generate a fire effect and show it graphically using QT. The GUI has controls as the following:
 
  - Start button: To start the fire when it is paused.
  - Pause button: To pause the fire. 
  - Increase/Decrease decay button: To adjust the speed of fire fade.
  - East/West wind button: To add lateral effect to the fire.
  - Choose random color button: By clicking the button, each time a different color is assigned to fire.

# Prerequisites 
You need to have QT 5+ installed on your system to compile the code (tested with QMake version 3.1 and Qt version 5.9.).

# Compiling the code

```sh
https://github.com/vabrishami/cpp-qt-fire-effect.git
cd cpp-qt-fire-effect
qmake fire_flame_prg.pro
make
```
