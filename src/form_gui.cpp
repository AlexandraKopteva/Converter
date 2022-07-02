#include "form_gui.h"
#include "ui_form_gui.h"
//std
#include<iostream>

GUIForm::GUIForm(QWidget *parent) : QWidget(parent), ui(new Ui::Form)
{
    ui->setupUi(this);
    setAcceptDrops(true);

    inButton  = new QPushButton("...", this);
    inButton->setMaximumWidth(30);

    convButton = new QPushButton(tr("Convert"), this);

    inputEdit = new QLineEdit(this);
    inputEdit->setAlignment(Qt::AlignCenter);
    inputEdit->setPlaceholderText(
                QApplication::translate("","PATH TO FILE .fb2"));
    inputEdit->setStyleSheet("background-color:#FFFFFF;");
    inputEdit->setClearButtonEnabled(true);

    QLabel* label = new QLabel(tr("Path to file:"));
    QVBoxLayout* vGlobal = new QVBoxLayout(this);
    QHBoxLayout* hor_label = new QHBoxLayout(this);
    QHBoxLayout* hor_in = new QHBoxLayout(this);

    hor_label->addWidget(label, Qt::AlignLeft);
    hor_in->addWidget(inputEdit);
    hor_in->addWidget(inButton);

    vGlobal->addLayout(hor_label);
    vGlobal->addLayout(hor_in);

    vGlobal->addWidget(convButton, Qt::AlignLeft);

    connect(inButton, SIGNAL(clicked()),
            this, SLOT(on_inButton_clicked()));
    connect(convButton, SIGNAL(clicked()),
            this, SLOT(convert()));

    setLayout(vGlobal);
}//GUIForm

GUIForm::~GUIForm()
{
    delete ui;
}//~GUIForm

void GUIForm::readFile(const QString& pathFile)
{
    try {
        QFile file(pathFile);
        if(!file.open(QIODevice::ReadOnly))
            std::cerr << "File is not open!" << std::endl;

        infoFile = file.readAll();
        file.close();
    } catch (const std::exception &exp) {
        std::cout << "Exception fuction readFile: " << exp.what() << std::endl;
    }
}//readFile

void GUIForm::writeFile(const QString& pathFile)
{
    try {
        QFile file(pathFile);
        if(!file.open(QIODevice::WriteOnly))
            std::cerr << "File is not open!" << std::endl;
        file.write(infoFile.toUtf8());
        file.close();
    } catch (const std::exception &exp) {
        std::cout << "Exception fuction readFile: " << exp.what() << std::endl;
    }
}//readFile


void GUIForm::on_inButton_clicked()
{
    pathToInFile = QFileDialog::getOpenFileName(this, tr("Open file"),nullptr,
                                                trUtf8("fb2(*.fb2)"));
    if(pathToInFile.length() > 0)
    {
        inputEdit->setText(pathToInFile);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("No path to file selected!");
        msgBox.exec();
    }
}//on_inButton_clicked

void GUIForm::convert()
{
    if(pathToInFile == "")
        pathToInFile = inputEdit->text();

    if(pathToInFile != "")
    {
        readFile(pathToInFile);
        QTextEdit* textEdit = new QTextEdit;
        textEdit->setHtml(infoFile);
        infoFile.clear();
        infoFile = textEdit->toPlainText();

        pathToOutFile = pathToInFile.toStdString();
        pathToOutFile.erase(pathToOutFile.end() - 3, pathToOutFile.end());
        pathToOutFile.append("txt");
        writeFile(QString::fromStdString(pathToOutFile));
    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("No path to file selected!");
        msgBox.exec();
    }
}//convert

void GUIForm::dragEnterEvent(QDragEnterEvent * event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}//dragEnterEvent

void GUIForm::dropEvent(QDropEvent *event)
{
    foreach (const QUrl &url, event->mimeData()->urls())
    {
        QString filename=url.toLocalFile();
        std::cout<<filename.toStdString()<<std::endl;
        inputEdit->insert(filename);
    }
}//dropEvent

