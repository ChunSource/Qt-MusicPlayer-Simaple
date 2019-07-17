#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QStringList>
#include <QDir>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	
private:
	Ui::MainWindow *ui;
	
	bool isPlay = false;
	QString MusicPath = "D:\\CloudMusic";
	
	QStringList fileList;  //文件名称
	QMediaPlaylist *PlayerList;
	QMediaPlayer *Player;
private slots:
	void init();
	void addItem(QString name);		//添加tableWidget
	QStringList getFileNames(const QString &path);	//获取路径下所有需要的文件类型文件 
	
	void SlotShowCurrentMedia();
	void SlotButtonStart();
	void SlotButtonPrevious();
	void SlotButtonNext();
};

#endif // MAINWINDOW_H
