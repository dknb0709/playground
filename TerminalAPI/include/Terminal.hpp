#pragma once

#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>
#include <cmath>
#include <iostream>
#include <thread>

#include "Color.hpp"

class Terminal {
  ::winsize window_;

 public:
  Terminal();

  void setColor(int fgColor, int bgColor);
  void setColor(const Color &fgColor, const Color &bgColor);
  void setDefaultColor();

  /**
   * @param n: 1 to 255
   */
  void pickFromJetColorMap(int n);

  int getWidth() noexcept;
  int getHeight() noexcept;

  void moveUp(int amount);
  void moveDown(int amount);
  void moveRight(int amount);
  void moveLeft(int amount);
  void moveTo(int x, int y);
  void moveToHead();
  void put(int x, int y, char c);
  void put(int x, int y, const std::string &s);
  /**
   * clears entire screen and delete all lines saved in the scrollback buffer
   */
  void clear();
};
