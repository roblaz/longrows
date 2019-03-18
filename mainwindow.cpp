#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#include <fstream>
#include <strings.h>
#include <list>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool compare(const string & a, const string & b)
{
    // если строки разной длины,то возвращается логический результат сравнения длин строк,
    // иначе возвращает логическое значение посимвольного сравнения слов
    if (a.length()!=b.length())return a.length() < b.length();
    else return strcmp(a.c_str(),b.c_str());
}

void MainWindow::on_sortButton_clicked()
{
    ui->Rows->clear();
    QString path = ui->pathEdit->text();

    if (path!="")
    {
            //Список строк
            list<string> strings;
            //Итератор списка
            list<string>::iterator itr;
            string line;
            string  file_name;
            // Создание потока для чтения  файла
            ifstream file(path.toStdString());

            //Цикл чтения строки из файла
            while(getline(file, line))
            {
                // Добавление строки в список
                strings.push_back(line);
            }
            file.close();
            // Сортировка списка
            strings.sort(compare);
            // Разворот списка, так как он отсортирован по возрастанию
            strings.reverse();
            // Вывод  первых 5 значений списка
            int count=0;
            ofstream f(".\\output.txt");
            if(strings.size()<5)
            {
                for(itr=strings.begin();itr!=strings.end();itr++)
                {
                    ui->Rows->append(QString((*itr).c_str()));
                    f<<*itr<<endl;
                }
            }
            else
            {
                int rep=0;
                string str =*strings.begin();
                int cur_len=str.length();
                for(itr=strings.begin();itr!=strings.end() && count<5;itr++)
                {
                    str=*itr;
                    if (str.length()==cur_len && rep<2)
                    {
                        f<<str<<endl;
                        ui->Rows->append(QString(str.c_str()));
                        ++rep;++count;
                    }
                    else if (str.length()<cur_len)
                    {
                        cur_len = str.length();
                        f<<str<<endl;
                        ui->Rows->append(QString(str.c_str()));
                        rep=1;
                        ++count;
                    }
                }
            }
            f.close();
    }
}

void MainWindow::on_SelectFileButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("TXT (*.txt)"));
    ui->pathEdit->setText(QFileDialog::getOpenFileName());
}
