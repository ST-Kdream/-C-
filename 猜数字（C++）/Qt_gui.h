#pragma once
#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QTextEdit>
#include <QObject>
#include <QIntValidator>
#include <QInputDialog>
#include<QDialog>
#include <QSpinBox>    
#include <QDialogButtonBox>
#include "record.h"
#include "gameway.h"
#include "V_update.h"

extern bool is_win,endless;
extern int difficulty, attempts, max_num, chance, level, EP, episode, update_EP, sum_EP;
extern std::string rank_name;
extern int mode;

class Mainwindow;

class CheckVwin :public QWidget
{
	Q_OBJECT

public:
	explicit CheckVwin(Mainwindow* mainwindow=nullptr,QWidget* parent = nullptr);

private:
	Mainwindow* mainwindow;
	QTextEdit* vresult;
	void initmain();

private slots:
	void entermainwin();
};

class Player_infor_win;
class GameWin;
class RuleWin;

class Mainwindow :public QWidget
{
	Q_OBJECT

public:
	explicit Mainwindow(CheckVwin* checkVwin, QWidget* parent = nullptr);
	~Mainwindow() noexcept override = default;

private:
	CheckVwin* checkVwin;
	Player_infor_win* player_infor_win;
	GameWin* gamewin;
	RuleWin* rulewin;
	QPushButton* btn1;
	QPushButton* btn2;
	QPushButton* btn3;

	void initconnect();

private slots:
	void go_player_information();
	void go_game();
	void go_show_rules();
};


class Player_infor_win :public QWidget
{
	Q_OBJECT
;
public:
	explicit Player_infor_win(Mainwindow* mainwindow, QWidget* parent = nullptr);

private:
	Mainwindow* mainwindow;
	QTextEdit* playerinfotext;
	QPushButton* goback;

private slots:
	void gomain();
};


class Diffwin;
class Levelwin;
class Guesswin;

class GameWin :public QWidget
{
	Q_OBJECT

public:
	explicit GameWin(Mainwindow* mainwindow, QWidget* parent = nullptr);
	
private:
	Mainwindow* mainwindow;
	GameWin* gamewin;
	Diffwin* diffwin;
	Levelwin* levelwin;
	Guesswin* guesswin;
	QPushButton* btn1;
	QPushButton* btn2;
	QPushButton* btn3;
	QPushButton* backbtn;

	void initmode();

private slots:
	void go_normal();
	void go_challenge();;
	void selectendless();
	void goback();
};


class RuleWin :public QWidget
{
	Q_OBJECT

public:
	explicit RuleWin(Mainwindow* mainwindow, QWidget* parent = nullptr);

private:
	Mainwindow* mainwindow;
	QTextEdit* ruletext;
	QPushButton* goback;

private slots:
	void gomain();
};


class Diffwin :public QWidget
{
	Q_OBJECT

public:
	explicit Diffwin(GameWin* gamewin, QWidget* parent = nullptr);

private:
	GameWin* gamewin;
	Guesswin* guesswin;
	QPushButton* btn1;
	QPushButton* btn2;
	QPushButton* btn3;
	QPushButton* btn4;
	QPushButton* btn5;
	QPushButton* btn6;

	QPushButton* backbtn;

	void initdiff();

private slots:
	void selecteasy();
	void selectnormal();
	void selectdiff();
	void selectnightmare();
	void selecthell();
	void selectself();
	void goback();
	
	void getsettings();
};

class Levelwin :public QWidget
{
	Q_OBJECT

public:
	explicit Levelwin(GameWin* gamewin, QWidget* parent = nullptr);

private:
	GameWin* gamewin;
	Guesswin* guesswin;
	QPushButton* btn1;
	QPushButton* btn2;
	QPushButton* btn3;
	QPushButton* btn4;
	QPushButton* btn5;
	QPushButton* btn6;
	QPushButton* btn7;
	QPushButton* btn8;
	QPushButton* btn9;
	QPushButton* backbtn;

	void initlevel();

private slots:
	void selectlevel1();
	void selectlevel2();
	void selectlevel3();
	void selectlevel4();
	void selectlevel5();
	void selectlevel6();
	void selectlevel7();
	void selectlevel8();
	void selectlevel9();
	void goback();

	void getsettings();
};


class Guesswin :public QWidget
{
	Q_OBJECT

public:
	explicit Guesswin(GameWin* gamewin, QWidget* prewin);
	~Guesswin() noexcept override = default;
	void setgame(int max_num,int chance, int EP);
	void setendlessgame(int episode, int max_num,int chance, int EP);
	void getendlesssettings(int& episode, int& max_num, int& chance, int& EP);
	void startnewgame();

private:
	GameWin* gamewin;    
	QWidget* prewin;       
	
	QLineEdit* guessinput;   
	QTextEdit* historytext;  
	QLabel* statuslabel;
	QLabel* infortext;
	QString historyentry;
	QPushButton* conform;
	QPushButton* backbtn;
	QPushButton* newbtn;

	int answer;

	void setupUI();
	void nextepisode();
	
private slots:
	void guessway();
	void goback();
	void nextgame();
};
