#include "window.h"
#include "ui_window.h"
#include <QDebug>
Window::Window(QWidget *parent) : QWidget(parent), ui(new Ui::Window) {
  ui->setupUi(this);
  createTrayIcon();
  timer = new QTimer(this);
  file.setFileName(".scratchpad");
  if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
    QMessageBox::information(this, tr("Unable to open file"),
                             file.errorString());
    QApplication::exit(1);
  }
  QTextStream in(&file);
  original = in.readAll();
  ui->plainTextEdit->setPlainText(original);
  file.close();
  connect(timer, &QTimer::timeout, this, &Window::autoSave);
}

void Window::createTrayIcon(){
    trayIconMenu = new QMenu(this);
    toggle = new QAction(tr("Show/Hide"), this);
    connect(toggle, &QAction::triggered, this, &Window::showHide);
    trayIconMenu->addAction(toggle);
    close = new QAction(tr("Close"), this);
    connect(close, &QAction::triggered, qApp, &QApplication::exit);
    trayIconMenu->addAction(close);
    trayIcon = new QSystemTrayIcon(this);
    QIcon icon(":/icon/icon.png");
    trayIcon->setIcon(icon);
    trayIcon->setContextMenu(trayIconMenu);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &Window::showHide);
    trayIcon->show();
}

void Window::showHide(){
    setVisible(!isVisible());
}

void Window::autoSave() {
  qDebug() << "hello";
  current = ui->plainTextEdit->toPlainText();
  if (QString::compare(original, current) != 0) {

    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate |
                   QIODevice::Text)) {
      QMessageBox::information(this, tr("Unable to open file"),
                               file.errorString());
      QApplication::exit(1);
    }
    QTextStream out(&file);
    out << ui->plainTextEdit->toPlainText();
    file.close();
  }
}

Window::~Window() {
  autoSave();
  delete ui;
}
