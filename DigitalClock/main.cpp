#include <cmath>
#include <iostream>
#include <thread>

#include <Terminal.hpp>

std::string getTimeString() {
  std::time_t t = std::time(nullptr);
  char mbstr[100];
  std::strftime(mbstr, sizeof(mbstr), "%H%M%S", std::localtime(&t));
  return mbstr;
}

constexpr int ctoi(const char c) { return c - '0'; }

struct Vec2 {
  int x, y;
};

class SevenSegmentDisplay {
  Terminal c;
  bool segment[7];

  using Segment = bool[7];
  const Segment number[10]{{1, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 0, 0, 0, 0},
                           {1, 1, 0, 1, 1, 0, 1}, {1, 1, 1, 1, 0, 0, 1},
                           {0, 1, 1, 0, 0, 1, 1}, {1, 0, 1, 1, 0, 1, 1},
                           {1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 0, 0, 0, 0},
                           {1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 0, 1, 1}};

 public:
  SevenSegmentDisplay(Terminal &c_) : c{c_} { setNumber(number[0]); }
  void setNumber(int n) { setNumber(number[n]); }
  void putNumber(int x, int y, int scale) {
    putSegmentA(x, y, scale);
    putSegmentB(x, y, scale);
    putSegmentC(x, y, scale);
    putSegmentD(x, y, scale);
    putSegmentE(x, y, scale);
    putSegmentF(x, y, scale);
    putSegmentG(x, y, scale);
  }
  inline void putColon(int x, int y, int scale) {
    sweepY(x + scale + 1, y + 1, scale - 1);
    sweepY(x + scale + 1, y + scale + 2, scale - 1);
  }

 private:
  void sweepX(int x, int y, int length) {
    for (int i = x; i <= x + length; ++i) {
      c.put(i, y, " ");
    }
  }
  void sweepY(int x, int y, int length) {
    for (int i = y; i <= y + length; ++i) {
      c.put(x, i, " ");
    }
  }
  void setNumber(const bool data[7]) {
    for (int i = 0; i < 7; ++i) {
      segment[i] = data[i];
    }
  }
  inline void putSegmentA(int x, int y, int scale) {
    if (!segment[0]) return;
    sweepX(x, y, scale + 1);
  }
  inline void putSegmentB(int x, int y, int scale) {
    if (!segment[1]) return;
    sweepY(x + scale + 1, y, scale + 1);
  }
  inline void putSegmentC(int x, int y, int scale) {
    if (!segment[2]) return;
    sweepY(x + scale + 1, y + scale + 1, scale + 1);
  }
  inline void putSegmentD(int x, int y, int scale) {
    if (!segment[3]) return;
    sweepX(x, y + 2 * (scale + 1), scale + 1);
  }
  inline void putSegmentE(int x, int y, int scale) {
    if (!segment[4]) return;
    sweepY(x, y + scale + 1, scale + 1);
  }
  inline void putSegmentF(int x, int y, int scale) {
    if (!segment[5]) return;
    sweepY(x, y, scale + 1);
  }
  inline void putSegmentG(int x, int y, int scale) {
    if (!segment[6]) return;
    sweepX(x, y + scale + 1, scale + 1);
  }
};

class DigitalClock {
  Terminal c;
  SevenSegmentDisplay seg[6] = {c, c, c, c, c, c};
  Vec2 pos;
  int scale;

 public:
  DigitalClock(Terminal &c_) : c{c_} {
    pos.x = 1;
    pos.y = 1;
    scale = 2;
  }
  void setPosition(int x, int y) { pos = {x, y}; }
  int getX() { return pos.x; }
  int getY() { return pos.y; }
  void setScale(int scale) { this->scale = scale; }
  void put() {
    int posX = pos.x, posY = pos.y;
    for (int i = 0; i < 6; ++i) {
      seg[i].putNumber(posX, posY, scale);
      posX += (scale + 2) + 1;
      if (i % 2 != 0 && i != 5) {
        seg[i].putColon(posX, posY, scale);
        posX += (scale + 2) + 1;
      }
    }
    c.moveToHead();
  }
  void setTime(int d1, int d2, int d3, int d4, int d5, int d6) {
    seg[0].setNumber(d1);
    seg[1].setNumber(d2);
    seg[2].setNumber(d3);
    seg[3].setNumber(d4);
    seg[4].setNumber(d5);
    seg[5].setNumber(d6);
  }
  void erasePrevious() {
    c.setDefaultColor();
    for (int i = 0; i < 6; ++i) {
      seg[i].setNumber(8);
    }
    put();
  }
};

int main() {
  Terminal c;
  DigitalClock clock(c);
  const int SCALE = 2;
  const int NUM_SEGMENTS = 8;
  const int WIDTH = (SCALE + 3) * NUM_SEGMENTS - 1;
  const int HEIGHT = SCALE * 2 + 3;
  clock.setScale(SCALE);
  Vec2 velocity{2, 1};
  uint32_t i = 0u;

  while (true) {
    c.clear();

    std::string timeStr = getTimeString();
    int d1 = ctoi(timeStr[0]);
    int d2 = ctoi(timeStr[1]);
    int d3 = ctoi(timeStr[2]);
    int d4 = ctoi(timeStr[3]);
    int d5 = ctoi(timeStr[4]);
    int d6 = ctoi(timeStr[5]);

    clock.erasePrevious();

    int x = clock.getX();
    int y = clock.getY();

    int newX = x + velocity.x;
    int newY = y + velocity.y;

    if (newX <= 1 || newX + WIDTH >= c.getWidth() + 1) {
      velocity.x *= -1;
    }
    if (newY <= 1 || newY + HEIGHT >= c.getHeight() + 1) {
      velocity.y *= -1;
    }

    clock.setPosition(newX, newY);
    clock.setTime(d1, d2, d3, d4, d5, d6);
    c.pickFromJetColorMap(i++);
    clock.put();
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
  }
}
