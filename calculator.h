#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void on_btnTekSil_clicked();

    void on_btnC_clicked();

    void on_btnCE_clicked();

    void on_btnEsit_clicked();

    void digit_pressed();

    void binary_operator_pressed();

    void unary_operator_pressed();

    void on_btnVirgul_clicked();

    void on_btnPozNeg_clicked();

private:
    Ui::Calculator *ui;
    double firstNum;
    bool userIsTypingSecondNumber;
};
#endif // CALCULATOR_H
