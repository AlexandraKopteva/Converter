#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QtWidgets>

namespace Ui {
class Form;
}
/*!
* \brief GUIForm класс формы
*/
class GUIForm : public QWidget
{
    Q_OBJECT

public:
    /*!
    * \brief GUIForm Конструктор с параметром
    * \param parent указатель QWidget
    */
    explicit GUIForm(QWidget *parent = nullptr);
    /*!
    * \brief MainWindow Деструктор по умочанию.
    */
    ~GUIForm();

private:
    Ui::Form *ui;

    QPushButton *inButton;   //! кнопка открытия окна выбора пути до файла
    QPushButton *convButton; //! кнопка конвертации и записи в текстовый файл результата
    QLineEdit *inputEdit;    //! поле ввода пути до конверитруемого файла
    //
    QString pathToInFile;     //! путь входного файла
    std::string pathToOutFile;//! путь выходного файла
    QString infoFile;         //! содержимое файла
    /*!
    * \brief readFile функция чтения файла
    * \param pathFile путь к файлу
    */
    void readFile(const QString& pathFile);
    /*!
    * \brief writeFile функция чтения файла
    * \param pathFile путь к файлу
    */
    void writeFile(const QString& pathFile);

    //!< функции открывающие доступ к копированию на виджет
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent * event);

private slots:
    void on_inButton_clicked();
    void convert();
};

#endif // FORM_H
