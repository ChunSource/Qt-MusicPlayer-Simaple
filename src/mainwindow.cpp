#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->ButtonPause,&QPushButton::clicked,this,&MainWindow::SlotButtonStart);
	connect(ui->ButtonNext,&QPushButton::clicked,this,&MainWindow::SlotButtonNext);
	connect(ui->ButtonLastMusic,&QPushButton::clicked,this,&MainWindow::SlotButtonPrevious);
	init();		//初始化相关函数
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::init()
{
	PlayerList = new QMediaPlaylist;		//实例化播放器和播放列表
	Player = new QMediaPlayer;
	
	
	
	fileList = getFileNames(this->MusicPath);    //获取文件夹下的所有音乐文件
	
	//	qDebug()<<"ALL Music File: \n "<<fileList;
	
	for(int i=0;i<fileList.size();i++)   //输出所有音频文件到界面
		{
			QString fileName = fileList.at(i);
			addItem(fileName);
			PlayerList->addMedia(QUrl::fromLocalFile(MusicPath+"\\"+fileName));
		}
	PlayerList->setCurrentIndex(0);
	
	Player->setPlaylist(PlayerList);//将播放列表加载到播放器
	connect(Player,&QMediaPlayer::currentMediaChanged,this,&MainWindow::SlotShowCurrentMedia);
}

QStringList MainWindow::getFileNames(const QString &path)
{
	
	QDir dir(path);
	QStringList nameFilters;
	nameFilters << "*.mp3";
	QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
	return files;
}

void MainWindow::SlotShowCurrentMedia()
{
	int index = PlayerList->currentIndex();
	QString songName = fileList.at(index);
	ui->label->setText(songName);
}

void MainWindow::SlotButtonStart()
{
	if(!isPlay)
		{
			isPlay = true;
			ui->ButtonPause->setIcon(QIcon(":/pause.ico"));
			Player->play();
		}
	else
		{
			isPlay = false;
			ui->ButtonPause->setIcon(QIcon(":/play.ico"));
			Player->pause();
		}
}

void MainWindow::SlotButtonPrevious()
{
	PlayerList->previous();
	PlayerList->previousIndex();
}

void MainWindow::SlotButtonNext()
{
	PlayerList->next();
	PlayerList->nextIndex();
}

void MainWindow::addItem(QString name)
{
	int count = ui->tableWidget->rowCount();
	ui->tableWidget->setRowCount(count+1);
	
	QTableWidgetItem *itemName = new QTableWidgetItem(name);
	ui->tableWidget->setItem(count, 0 , itemName);
	
}
