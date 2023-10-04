#include "widget/dir_tree_widget.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    astro::DirTreeWidget w;
    w.show();
    return a.exec();
}
