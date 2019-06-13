#include <QHotkey>
#include "window.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Window w;
  w.setWindowTitle("Scratchpad");
  //w.show();
  QHotkey *hotkey = new QHotkey(QKeySequence("ctrl+|"), true, &a);
  QObject::connect(hotkey, &QHotkey::activated, &w, &Window::showHide);
  return a.exec();
}
