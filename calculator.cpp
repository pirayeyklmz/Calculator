#include "calculator.h"
#include "ui_calculator.h"

#include <QMessageBox>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    firstNum =0;
    userIsTypingSecondNumber=false;

    connect(ui->btnSifir,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btnBir, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btnIki,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btnUc,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btnDort,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btnBes,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btnAlti,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btnYedi,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btnSekiz,SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btnDokuz,SIGNAL(released()), this, SLOT(digit_pressed()));

    connect(ui->btnYuzde,SIGNAL(released()), this, SLOT(unary_operator_pressed()));

    connect(ui->btnBol, SIGNAL(released()),this, SLOT(binary_operator_pressed()));
    connect(ui->btnTop, SIGNAL(released()),this, SLOT(binary_operator_pressed()));
    connect(ui->btnCikar, SIGNAL(released()),this, SLOT(binary_operator_pressed()));
    connect(ui->btnCarp, SIGNAL(released()),this, SLOT(binary_operator_pressed()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::digit_pressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString newLabel;

    // Eğer ekranda "0" varsa ya da ikinci sayı yazılmaya yeni başlayacaksa
    if ((ui->txtScreen->toPlainText() == "0") || (userIsTypingSecondNumber))
    {
        newLabel = button->text();        // basılan rakamla başlangıç yap
        userIsTypingSecondNumber = false; // artık ikinci sayıyı yazmaya başladık
    }
    else
    {
        newLabel = ui->txtScreen->toPlainText() + button->text();// mevcut metne rakam ekle
    }

    ui->txtScreen->setPlainText(newLabel);// ekranı güncelle
}

void Calculator::unary_operator_pressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender()); // % butonu
    QString op = button->text();
    double value = ui->txtScreen->toPlainText().toDouble(); // ekrandaki değeri double'a çevir

    if (op == "%")
        value *= 0.01; // yüzde: değeri 100'e böl

    ui->txtScreen->setPlainText(QString::number(value, 'g', 15));
}

void Calculator::binary_operator_pressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender()); // +, -, *, / butonlarından biri
    firstNum = ui->txtScreen->toPlainText().toDouble();
    button->setChecked(true);  // bu operatörü "seçili" işaretle (buton checkable olmalı)
    userIsTypingSecondNumber = true; // sıradaki giriş ikinci sayı olacak
}

void Calculator::on_btnCE_clicked()
{
    ui->txtScreen->setPlainText("0"); //ilgili sayıyı sil
}

void Calculator::on_btnC_clicked() //tüm işlemi siler
{
    firstNum = 0.0;
    userIsTypingSecondNumber = false;
    ui->txtScreen->setPlainText("0");
}

void Calculator::on_btnEsit_clicked()
{
    double secondNum = ui->txtScreen->toPlainText().toDouble();
    double result = 0.0;

    if (ui->btnTop->isChecked()) {
        result = firstNum + secondNum;  // + seçiliyse ilk sayı ve ikinci sayıyı topla
        ui->btnTop->setChecked(false);
    }
    else if (ui->btnCikar->isChecked()) {
        result = firstNum - secondNum;   // - seçiliyse ilk sayıdan ile ikinci sayıyı çıkar
        ui->btnCikar->setChecked(false); //seçimi kaldır
    }
    else if (ui->btnCarp->isChecked()) {
        result = firstNum * secondNum;  // x seçiliyse ilk sayı ile ikinci sayıyı çarp
        ui->btnCarp->setChecked(false);
    }
    else if (ui->btnBol->isChecked())
    {
        if (secondNum != 0.0) {
            result = firstNum / secondNum;
        } else {
            QMessageBox::warning(this, "Hata", "Sıfıra bölme yapılamaz!");
        }
        ui->btnBol->setChecked(false);
        return; // İşlemi durdur

    }

    ui->txtScreen->setPlainText(QString::number(result, 'g', 15));
    userIsTypingSecondNumber = false;
}

void Calculator::on_btnVirgul_clicked()
{
    QString text = ui->txtScreen->toPlainText();
    if (!text.contains('.')) // nokta yoksa
        text += '.';         // ondalık ayırıcı olarak '.' ekle (TL locale'de virgül beklenir)
    ui->txtScreen->setPlainText(text);
}

void Calculator:: on_btnTekSil_clicked()
{
    QString text = ui->txtScreen->toPlainText();
    text.chop(1);   // sondan 1 karakter sil (backspace)
    if (text.isEmpty())   // hepsi silindiyse
        text = "0";       // 0'a sabitle
    ui->txtScreen->setPlainText(text);
}

void Calculator::on_btnPozNeg_clicked()
{
    double value = ui->txtScreen->toPlainText().toDouble();
    value *= -1; // İşareti tersine çevir
    ui->txtScreen->setPlainText(QString::number(value, 'g', 15));
}
