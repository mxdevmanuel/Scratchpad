#ifndef WINDOW_H
#define WINDOW_H

#include <QAction>
#include <QFile>
#include <QMenu>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QTextStream>
#include <QTimer>
#include <QWidget>

namespace Ui {
class Window;
}

class Window : public QWidget {
  Q_OBJECT

public:
  explicit Window(QWidget *parent = nullptr);
  void showHide();
  ~Window();

private:
  Ui::Window *ui;
  QTimer *timer;
  QFile file;
  QString original, current;
  QMenu *trayIconMenu;
  QAction *toggle, *close;
  QSystemTrayIcon *trayIcon;
  void createTrayIcon();
  void autoSave();
};

#endif // WINDOW_H
