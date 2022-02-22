#include <QApplication>
#include <dialog.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QDialog dialog;
    dialog.show();

    return app.exec();
}
