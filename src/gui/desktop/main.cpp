#include <QApplication>

#include "mainwindow.hpp"

using namespace s21;
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow mainwindow;

  mainwindow.show();
  return a.exec();
}
