#include <Terminal.hpp>

Terminal::Terminal() { ::ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_); }

void Terminal::setColor(int fgColor, int bgColor) {
  std::cout << "\033[38;5;" << fgColor << "m";
  std::cout << "\033[48;5;" << bgColor << "m";
}
void Terminal::setColor(const Color &fgColor, const Color &bgColor) {
  std::cout << "\033[48;2;" << fgColor.r << ";" << fgColor.g << ";" << fgColor.b
            << "m";
  std::cout << "\033[38;2;" << bgColor.r << ";" << bgColor.g << ";" << bgColor.b
            << "m";
}
void Terminal::setDefaultColor() {
  std::cout << "\033[39m" << std::flush;
  std::cout << "\033[49m" << std::flush;
}

/**
 * @param n: 1 to 255
 */
void Terminal::pickFromJetColorMap(int n) {
  int r = (int)(128 - 127 * ::cosf(n * 0.01227 * 1));
  int g = (int)(128 - 127 * ::cosf(n * 0.01227 * 3));
  int b = (int)(128 - 127 * ::cosf(n * 0.01227 * 5));
  setColor({r, g, b}, {255 - r, 255 - g, 255 - b});
}

int Terminal::getWidth() noexcept { return window_.ws_col; }
int Terminal::getHeight() noexcept { return window_.ws_row; }

void Terminal::moveUp(int amount) {
  std::cout << "\033[" << amount << "A" << std::flush;
}
void Terminal::moveDown(int amount) {
  std::cout << "\033[" << amount << "B" << std::flush;
}
void Terminal::moveRight(int amount) {
  std::cout << "\033[" << amount << "C" << std::flush;
}
void Terminal::moveLeft(int amount) {
  std::cout << "\033[" << amount << "D" << std::flush;
}
void Terminal::moveTo(int x, int y) {
  std::cout << "\033[" << y << ";" << x << "H" << std::flush;
}
void Terminal::moveToHead() { moveTo(1, 1); }
void Terminal::put(int x, int y, char c) {
  moveTo(x, y);
  std::cout << c << std::flush;
}
void Terminal::put(int x, int y, const std::string &s) {
  moveTo(x, y);
  std::cout << s << std::flush;
}
/**
 * clears entire screen and delete all lines saved in the scrollback buffer
 */
void Terminal::clear() { std::cout << "\033[3J" << std::flush; }
