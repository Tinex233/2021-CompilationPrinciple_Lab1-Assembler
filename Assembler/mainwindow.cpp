#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lesals.h"

lesals alz=lesals();
vector<string> ans;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("词法分析器");
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_transbtn_clicked()
{
    ans.clear();

        if(ui->inputtxt->document()->isEmpty())//判空
            QMessageBox::information(this,"提示","文本为空！",QMessageBox::Ok);
        else
        {
            ui->outputtxt->clear();
            //按行读取
            QString line;
            int lc=ui->inputtxt->document()->lineCount();

            for(int i=0;i<lc;i++)
            {
                line = ui->inputtxt->document()->findBlockByLineNumber(i).text();
                //qDebug()<<line;
                string str=line.toStdString();
                alz.analysis(ans,str);
            }
        }

    for(auto i:ans)
    {
        ui->outputtxt->append(QString::fromStdString(i));
    }
}

void MainWindow::on_savebtn_clicked()
{
    QFileDialog dlg(this);

    //获取内容的保存路径
    QString fileName = dlg.getSaveFileName(this, tr("保存为"), "./", tr("Text File(*.txt)"));

    if( fileName == "" )
        return;

    //内容保存到路径文件
    QFile file(fileName);

    //以文本方式打开
    if( file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        QTextStream out(&file); //IO设备对象的地址对其进行初始化

        out << ui->outputtxt->toPlainText(); //输出

        QMessageBox::warning(this, tr("提示"), tr("保存文件成功！"));

        file.close();
    }
    else
    {
        QMessageBox::warning(this, tr("错误"), tr("打开文件失败！"));
    }
}

void MainWindow::on_clrresbtn_clicked()
{
    ui->outputtxt->clear();
}

void MainWindow::on_clrbtn_clicked()
{
    ui->inputtxt->clear();
}

void MainWindow::on_importbtn_clicked()
{
    //打开并读取文件
    QFileDialog* f = new QFileDialog(this);
    f->setWindowTitle("选择txt文件*.txt");
    f->setNameFilter("*.txt");
    f->setViewMode(QFileDialog::Detail);

    QString filePath;
    if(f->exec() == QDialog::Accepted)
        filePath = f->selectedFiles()[0];

    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream readStream(&file);
        readStream.setCodec("UTF-8");//设置文件流编码方式

        ui->inputtxt->clear();

        while(!readStream.atEnd())
        {
            ui->inputtxt->append(readStream.readLine());
        }
    }
    else
    {
        QMessageBox::warning(this, tr("提示"), tr("未打开文件或文件打开失败！"));
        return;
    }
}
