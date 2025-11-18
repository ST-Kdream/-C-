#include "Qt_gui.h"

CheckVwin::CheckVwin(Mainwindow* mainwindow, QWidget* parent): QWidget(parent),mainwindow(mainwindow),vresult(nullptr)
{
	setWindowTitle("猜数字");
	resize(800, 600);
	QLabel* maintitle = new QLabel("欢迎来到猜数字小游戏", this);
	maintitle->setGeometry(250, 100, 300, 100);
	maintitle->setAlignment(Qt::AlignCenter);
	maintitle->setStyleSheet(R"(color: blue; font-size: 30px; font-weight: bold;)");
	QLabel* tip = new QLabel("游戏启动，正在检查更新中...", this);
	tip->setToolTip("请稍后");
	tip->setStyleSheet(R"(color:black;font-size:20px;font-weight:bold)");
	tip->setAlignment(Qt::AlignCenter);
	tip->setGeometry(150, 300, 500, 100);

	QTextEdit* vresult = new QTextEdit(this);
	vresult->setReadOnly(true);
	this->setLayout(new QVBoxLayout);
	this->layout()->addWidget(vresult);

	std::stringstream ss;
	version_check(ss);
	vresult->setText(QString::fromStdString(ss.str()));

	initmain();
}

void CheckVwin::initmain()
{
	QPushButton* enterbtn = new QPushButton("进入游戏", this);
	enterbtn->setStyleSheet(R"(
								  QPushButton{background-color:#4CAF50;color:white;font-size:20px;padding:10px;border-radius:5px;}
								  QPushButton:hover{background-color:#45a049;}
								  QPushButton:pressed{background-color:#3d8b40;}
							  )");
	this->layout()->addWidget(enterbtn);

	connect(enterbtn, &QPushButton::clicked, this, &CheckVwin::entermainwin);
}

void CheckVwin::entermainwin()
{
	if (mainwindow)
		mainwindow->show();
	this->close();
}

Mainwindow::Mainwindow(CheckVwin* checkVwin, QWidget* parent) :QWidget(parent), checkVwin(checkVwin)
{
	setWindowTitle("欢迎来到猜数字小游戏");
	resize(800, 600);
	QLabel* maintitle = new QLabel("猜数字", this);
	maintitle->setGeometry(250, 100, 300, 100);
	maintitle->setAlignment(Qt::AlignCenter);
	maintitle->setStyleSheet(R"(color: blue; font-size: 30px; font-weight: bold;)");
	btn1 = new QPushButton("玩家信息", this);
	btn2 = new QPushButton("开始游戏", this);
	btn3 = new QPushButton("游戏规则", this);
	QString begin = R"(
						QPushButton{background-color:#E6E6E6;color:black;font-size:23px;border-radius:2px;}
						QPushButton:hover{background-color:#505050;}
						QPushButton:pressed{background-color:#6495ED;}
					  )";
	btn1->setStyleSheet(begin);
	btn1->setGeometry(300, 220, 150, 80);
	btn2->setStyleSheet(begin);
	btn2->setGeometry(300, 320, 150, 80);
	btn3->setStyleSheet(begin);
	btn3->setGeometry(300, 420, 150, 80);

	player_infor_win = new Player_infor_win(this);
	gamewin = new GameWin(this);
	rulewin = new RuleWin(this);

	initconnect();
}


void Mainwindow::initconnect()
{
	connect(btn1, &QPushButton::clicked, this, &Mainwindow::go_player_information);
	connect(btn2, &QPushButton::clicked, this, &Mainwindow::go_game);
	connect(btn3, &QPushButton::clicked, this, &Mainwindow::go_show_rules);
}

void Mainwindow::go_player_information()
{
	if (player_infor_win)
		player_infor_win->show();
	this->hide();
}

void Mainwindow::go_game()
{
	if (gamewin)
		gamewin->show();
	this->hide();
}

void Mainwindow::go_show_rules()
{
	if (rulewin)
		rulewin->show();
	this->hide();
}

Player_infor_win::Player_infor_win(Mainwindow* mainwindow, QWidget* parent) :QWidget(parent), mainwindow(mainwindow)
{
	setWindowTitle("玩家信息");
	resize(800, 600);
	playerinfotext = new QTextEdit(this);
	playerinfotext->setReadOnly(true);

	goback = new QPushButton("返回", this);
	goback->setStyleSheet(R"(
								  QPushButton{background-color:#4CAF50;color:white;font-size:20px;padding:10px;border-radius:5px;}
								  QPushButton:hover{background-color:#45a049;}
								  QPushButton:pressed{background-color:#3d8b40;}
							  )");
	
	this->setLayout(new QVBoxLayout);
	this->layout()->addWidget(playerinfotext);
	this->layout()->addWidget(goback);

	std::stringstream ss;
	if (player_information(ss))
	{
		playerinfotext->setText(QString::fromStdString(ss.str()));
	}
	else
	{
		QMessageBox::warning(this, "错误", "未找到玩家信息");

		QDialog is_newplayer(this);
		is_newplayer.setWindowTitle("询问");
		is_newplayer.resize(300, 200);

		QDialogButtonBox* btn = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &is_newplayer);

		QVBoxLayout* mainlay = new QVBoxLayout(this);
		mainlay->addWidget(new QLabel("是否初始化玩家信息"));
		mainlay->addWidget(btn);

		QObject::connect(btn, &QDialogButtonBox::accepted, &is_newplayer, &QDialog::accept);
		QObject::connect(btn, &QDialogButtonBox::rejected, &is_newplayer, &QDialog::reject);

		if (is_newplayer.exec() == QDialog::Accepted)
		{
			player_init();
		}
	}
	connect(goback, &QPushButton::clicked, this, &Player_infor_win::gomain);
}

void Player_infor_win::gomain()
{
	if (mainwindow)
		mainwindow->show();
	this->hide();
}


GameWin::GameWin(Mainwindow* mainwindow, QWidget* parent) :QWidget(parent), mainwindow(mainwindow)
{
	setWindowTitle("模式选择");
	resize(800, 600);

	QLabel* mode = new QLabel("选择游戏模式", this);
	mode->setStyleSheet(R"(font-weight:bold;font-size:30px;color:#48C9B0)");
	mode->setAlignment(Qt::AlignCenter);
	
	btn1 = new QPushButton("普通模式", this);
	btn2 = new QPushButton("挑战模式", this);
	btn3 = new QPushButton("无尽模式", this);
	backbtn = new QPushButton("返回", this);

	btn1->setObjectName("normalbtn");
	btn2->setObjectName("challengebtn");
	btn3->setObjectName("endlessbtn");

	QString stymode = R"(
						QPushButton{color: white;min-width:150px; min-height:80px;border:none;font:bold 23px;border-radius:2px;}
						#normalbtn{background-color:#4A90E2; }
						#normalbtn:hover{background-color:#5B9EF3;}
						#normalbtn:pressed{background-color:#3A80D1;}
						#challengebtn{background-color:#F57C00;}
						#challengebtn:hover{background-color:#FF9800;}
						#challengebtn:pressed{background-color:#E65100;}
						#endlessbtn{background-color: #673AB7;}
						#endlessbtn:hover{background-color:#7E57C2;}
						#endlessbtn:pressed{background-color:#5E35B1;}
						)";

	btn1->setStyleSheet(stymode);
	btn2->setStyleSheet(stymode);
	btn3->setStyleSheet(stymode);

	this->setLayout(new QVBoxLayout);
	this->layout()->addWidget(mode);
	this->layout()->addWidget(btn1);
	this->layout()->addWidget(btn2);
	this->layout()->addWidget(btn3);
	this->layout()->addWidget(backbtn);

	diffwin = new Diffwin(this);
	levelwin = new Levelwin(this);
	guesswin = new Guesswin(gamewin,this);

	initmode();
}

void GameWin::initmode()
{
	connect(btn1, &QPushButton::clicked, this, &GameWin::go_normal);
	connect(btn2, &QPushButton::clicked, this, &GameWin::go_challenge);
	connect(btn3, &QPushButton::clicked, this, &GameWin::selectendless);
	connect(backbtn, &QPushButton::clicked, this, &GameWin::goback);
}

void GameWin::go_normal()
{
	endless = false;
	mode = 1;
	if (diffwin)
		diffwin->show();
	this->hide();
}

void GameWin::go_challenge()
{
	endless = false;
	mode = 2;
	if (levelwin)
		levelwin->show();
	this->hide();
}

void GameWin::selectendless()
{
	endless = true;
	mode = 0;
	episode = 1;
	guesswin->getendlesssettings(episode,max_num, chance, EP);
	if (guesswin)
		guesswin->show();
	this->hide();
}

void GameWin::goback()
{
	if (mainwindow)
		mainwindow->show();
	this->hide();
}


RuleWin::RuleWin(Mainwindow* mainwindow, QWidget* parent) :QWidget(parent), mainwindow(mainwindow)
{
	setWindowTitle("游戏规则");
	resize(800, 600);
	ruletext = new QTextEdit(this);
	ruletext->setReadOnly(true);

	goback = new QPushButton("返回", this);
	goback->setStyleSheet(R"(
								  QPushButton{background-color:#4CAF50;color:white;font-size:20px;padding:10px;border-radius:5px;}
								  QPushButton:hover{background-color:#45a049;}
								  QPushButton:pressed{background-color:#3d8b40;}
							  )");

	this->setLayout(new QVBoxLayout);
	this->layout()->addWidget(ruletext);
	this->layout()->addWidget(goback);

	std::stringstream ss;
	show_rules(ss);
	ruletext->setText(QString::fromStdString(ss.str()));

	connect(goback, &QPushButton::clicked, this, &RuleWin::gomain);
}

void RuleWin::gomain()
{
	if (mainwindow)
		mainwindow->show();
	this->hide();
}

Diffwin::Diffwin(GameWin* gamewin, QWidget* parent) :QWidget(parent), gamewin(gamewin)
{
	setWindowTitle("难度等级");
	resize(800, 600);
	QLabel* diff = new QLabel("请选择难度等级", this);
	diff->setStyleSheet(R"(font-size:30px;font-weight:bold;color:black)");
	
	btn1 = new QPushButton("简单", this);
	btn2 = new QPushButton("普通", this);
	btn3 = new QPushButton("困难", this);
	btn4 = new QPushButton("噩梦", this);
	btn5 = new QPushButton("地狱", this);
	btn6 = new QPushButton("自定义", this);
	backbtn = new QPushButton("返回", this);

	btn1->setObjectName("easybtn");
	btn2->setObjectName("commonbtn");
	btn3->setObjectName("diffbtn");
	btn4->setObjectName("baddreambtn");
	btn5->setObjectName("nullbtn");
	btn6->setObjectName("selfdefbtn");

	QString stydiff = R"(
							QPushButton{color: white;min-width:100px; min-height:80px;border:none;font:bold 23px;border-radius:2px;}
							#easybtn{background-color: #81C784;}
							#easybtn:hover{ background-color: #9CCC65; }
							#easybtn:pressed{ background-color: #66BB6A; }
							#commonbtn{background-color: #64B5F6;}
							#commonbtn:hover{ background-color: #90CAF9; }
							#commonbtn:pressed{ background-color: #42A5F5; }
							#diffbtn{background-color: #FFB74D;}
							#diffbtn:hover{ background-color: #FFCC80;  }
							#diffbtn:pressed{ background-color: #FB8C00; }
							#baddreambtn{background-color: #FF9800;}
							#baddreambtn:hover{ background-color: #FFB74D; }
							#baddreambtn:pressed{ background-color: #F57C00; }
							#nullbtn{background-color: #EF5350;}
							#nullbtn:hover{ background-color: #FF6E40; }
							#nullbtn:pressed { background-color: #E53935; }
							#selfdefbtn{ background-color:#BA68C8;}
							#selfdefbtn:hover{ background-color: #CE93D8; }
							#selfdefbtn:pressed{ background-color: #9C27B0; }
						 )";

	btn1->setStyleSheet(stydiff);
	btn2->setStyleSheet(stydiff);
	btn3->setStyleSheet(stydiff);
	btn4->setStyleSheet(stydiff);
	btn5->setStyleSheet(stydiff);
	btn6->setStyleSheet(stydiff);

	this->setLayout(new QVBoxLayout);
	this->layout()->addWidget(diff);
	this->layout()->addWidget(btn1);
	this->layout()->addWidget(btn2);
	this->layout()->addWidget(btn3);
	this->layout()->addWidget(btn4);
	this->layout()->addWidget(btn5);
	this->layout()->addWidget(btn6);
	this->layout()->addWidget(backbtn);

	guesswin = new Guesswin(gamewin,this);

	initdiff();
}

void Diffwin::initdiff()
{
	connect(btn1, &QPushButton::clicked, this, &Diffwin::selecteasy);
	connect(btn2, &QPushButton::clicked, this, &Diffwin::selectnormal);
	connect(btn3, &QPushButton::clicked, this, &Diffwin::selectdiff);
	connect(btn4, &QPushButton::clicked, this, &Diffwin::selectnightmare);
	connect(btn5, &QPushButton::clicked, this, &Diffwin::selecthell);
	connect(btn6, &QPushButton::clicked, this, &Diffwin::selectself);
	connect(backbtn, &QPushButton::clicked, this, &Diffwin::goback);
}

void Diffwin::selecteasy()
{
	difficulty = 1;
	getsettings();
}

void Diffwin::selectnormal()
{
	difficulty = 2;
	getsettings();
}

void Diffwin::selectdiff()
{
	difficulty = 3;
	getsettings();
}

void Diffwin::selectnightmare()
{
	difficulty = 4;
	getsettings();
}

void Diffwin::selecthell()
{
	difficulty = 5;
	getsettings();
}

void Diffwin::goback()
{
	if (gamewin)
		gamewin->show();
	this->hide();
}

void Diffwin::selectself()
{
	QMessageBox::information(this, "提示", "自定义模式无法获得经验值");

	QDialog selfdiffset(this);
	selfdiffset.setWindowTitle("自定义难度");
	selfdiffset.setFixedSize(300,200);
	QVBoxLayout* dialay = new QVBoxLayout(&selfdiffset);

	QSpinBox* maxnuminput = new QSpinBox(&selfdiffset);
	maxnuminput->setRange(1, 10000000000);
	maxnuminput->setValue(100);
	QSpinBox* chanceinput = new QSpinBox(&selfdiffset);
		chanceinput->setValue(10);
	chanceinput->setRange(3, 1000000000);

	QDialogButtonBox* btn = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,&selfdiffset);
	dialay->addWidget(new QLabel("请设置难度参数"));
	dialay->addWidget(new QLabel("最大数字"));
	dialay->addWidget(maxnuminput);
	dialay->addWidget(new QLabel("最大猜测次数"));
	dialay->addWidget(chanceinput);
	dialay->addWidget(btn);

	QObject::connect(btn, &QDialogButtonBox::accepted, &selfdiffset, &QDialog::accept);
	QObject::connect(btn, &QDialogButtonBox::rejected, &selfdiffset, &QDialog::reject);

	if (selfdiffset.exec() == QDialog::Accepted)
	{
		max_num = maxnuminput->value();
		chance = chanceinput->value();
		difficulty = 6;
		getsettings();
	}
}

void Diffwin::getsettings()
{
	if (guesswin)
	{
		this->hide();
		if (difficulty != 6)
		{
			gameway_common(difficulty, max_num, chance, EP);
			guesswin->setgame(max_num, chance, EP);
		}
		else
		{
			guesswin->setgame(max_num, chance, 0);
		}
	}
	guesswin->show();
	guesswin->startnewgame();
}

Levelwin::Levelwin(GameWin* gamewin, QWidget* parent) :QWidget(parent), gamewin(gamewin)
{
	setWindowTitle("选择等级");
	resize(800, 600);
	QLabel* leveltext = new QLabel("请选择挑战等级", this);
	leveltext->setStyleSheet(R"(font-size:30px;font-weight:bold;color:black)");

	btn1 = new QPushButton("等级1", this);
	btn2 = new QPushButton("等级2", this);
	btn3 = new QPushButton("等级3", this);
	btn4 = new QPushButton("等级4", this);
	btn5 = new QPushButton("等级5", this);
	btn6 = new QPushButton("等级6", this);
	btn7 = new QPushButton("等级7", this);
	btn8 = new QPushButton("等级8", this);
	btn9 = new QPushButton("等级9", this);
	backbtn = new QPushButton("返回", this);

	btn1->setObjectName("level1btn");
	btn2->setObjectName("level2btn");
	btn3->setObjectName("level3btn");
	btn4->setObjectName("level4btn");
	btn5->setObjectName("level5btn");
	btn6->setObjectName("level6btn");
	btn7->setObjectName("level7btn");
	btn8->setObjectName("level8btn");
	btn9->setObjectName("level9btn");

	QString stylevel = R"(
							 QPushButton {min-width: 100px; min-height: 80px; font: bold 23px; border-radius: 2px;border: none;color: #FFFFFF;}
							 #level1btn { background-color: #66BB6A; }
							 #level1btn:hover { background-color: #81C784; }
							 #level1btn:pressed { background-color: #4CAF50; }
							 #level2btn { background-color: #4CAF50; }
							 #level2btn:hover { background-color: #66BB6A; }
							 #level2btn:pressed { background-color: #388E3C; }
							 #level3btn { background-color: #42A5F5; }
							 #level3btn:hover { background-color: #64B5F6; }
							 #level3btn:pressed { background-color: #2196F3; }
							 #level4btn { background-color: #26C6DA; }
							 #level4btn:hover { background-color: #4DD0E1; }
							 #level4btn:pressed { background-color: #00BCD4; }
							 #level5btn { background-color: #03A9F4; }
							 #level5btn:hover { background-color: #4FC3F7; }
							 #level5btn:pressed { background-color: #0288D1; }
							 #level6btn { background-color: #FFA726; }
							 #level6btn:hover { background-color: #FFB74D; }
							 #level6btn:pressed { background-color: #FB8C00; }
							 #level7btn { background-color: #FB8C00; }
							 #level7btn:hover { background-color: #FFB74D; }
							 #level7btn:pressed { background-color: #F57C00; }
							 #level8btn { background-color: #F57C00; }
							 #level8btn:hover { background-color: #FF9800; }
							 #level8btn:pressed { background-color: #E65100; }
							 #level9btn { background-color: #E53935; }
							 #level9btn:hover { background-color: #EF5350; }
							 #level9btn:pressed { background-color: #C62828; }
					   )";
	
	btn1->setStyleSheet(stylevel);
	btn2->setStyleSheet(stylevel);
	btn3->setStyleSheet(stylevel);
	btn4->setStyleSheet(stylevel);
	btn5->setStyleSheet(stylevel);
	btn6->setStyleSheet(stylevel);
	btn7->setStyleSheet(stylevel);
	btn8->setStyleSheet(stylevel);
	btn9->setStyleSheet(stylevel);

	QVBoxLayout* column1 = new QVBoxLayout();
	column1->addWidget(btn1);
	column1->addWidget(btn2);
	column1->addWidget(btn3);
	column1->addWidget(btn4);
	column1->addWidget(btn5);

	QVBoxLayout* column2 = new QVBoxLayout();
	column2->addWidget(btn6);
	column2->addWidget(btn7);
	column2->addWidget(btn8);
	column2->addWidget(btn9);
	column2->addWidget(backbtn);

	QHBoxLayout* mainlay = new QHBoxLayout(this);
	mainlay->addWidget(leveltext);
	mainlay->addLayout(column1);
	mainlay->addLayout(column2);

	mainlay->layout();

	initlevel();
	guesswin = new Guesswin(gamewin, this);
}

void Levelwin::initlevel()
{
	connect(btn1, &QPushButton::clicked, this, &Levelwin::selectlevel1);
	connect(btn2, &QPushButton::clicked, this, &Levelwin::selectlevel2);
	connect(btn3, &QPushButton::clicked, this, &Levelwin::selectlevel3);
	connect(btn4, &QPushButton::clicked, this, &Levelwin::selectlevel4);
	connect(btn5, &QPushButton::clicked, this, &Levelwin::selectlevel5);
	connect(btn6, &QPushButton::clicked, this, &Levelwin::selectlevel6);
	connect(btn7, &QPushButton::clicked, this, &Levelwin::selectlevel7);
	connect(btn8, &QPushButton::clicked, this, &Levelwin::selectlevel8);
	connect(btn9, &QPushButton::clicked, this, &Levelwin::selectlevel9);
	connect(backbtn, &QPushButton::clicked, this, &Levelwin::goback);
}

void Levelwin::selectlevel1()
{
	level = 1;
	getsettings();
}

void Levelwin::selectlevel2()
{
	level = 2;
	getsettings();
}

void Levelwin::selectlevel3()
{
	level = 3;
	getsettings();
}

void Levelwin::selectlevel4()
{
	level = 4;
	getsettings();
}

void Levelwin::selectlevel5()
{
	level = 5;
	getsettings();
}

void Levelwin::selectlevel6()
{
	level = 6;
	getsettings();
}

void Levelwin::selectlevel7()
{
	level = 7;
	getsettings();
}

void Levelwin::selectlevel8()
{
	level = 8;
	getsettings();
}

void Levelwin::selectlevel9()
{
	level = 9;
	getsettings();
}

void Levelwin::getsettings()
{
	
	gameway_challenge(level,max_num, chance, EP);
	guesswin->setgame(max_num, chance, EP);
	if (guesswin)
	{
		guesswin->show();
	}
	this->hide();
	guesswin->startnewgame();
}

void Levelwin::goback()
{
	if (gamewin)
		gamewin->show();
	this->hide();
}

Guesswin::Guesswin(GameWin* gamewin, QWidget* prewin) :QWidget(nullptr), gamewin(gamewin), prewin(prewin)
														
{
	setWindowTitle("猜数字游戏");
	resize(800, 600);
	infortext = new QLabel(this);
	statuslabel = new QLabel(this);
	historytext = new QTextEdit(this);
	guessinput = new QLineEdit(this);
	conform = new QPushButton("确认", this);
	newbtn = new QPushButton("新游戏", this);
	backbtn = new QPushButton("返回", this);

	setupUI();
}

void Guesswin::setgame(int maxnum, int maxatt, int ep)
{
	max_num = maxnum;
	chance = maxatt;
	EP = ep;

	infortext->setText(QString("数字范围：1-%1|最大尝试次数：%2|经验值：%3").arg(max_num).arg(chance).arg(EP));
	guessinput->setPlaceholderText("请输入1-" + QString::number(max_num) + "之间的数字：");
	guessinput->setValidator(new QIntValidator(1, max_num, this));
}

void Guesswin::setendlessgame(int episode,int max_num,int chance,int EP)
{
	infortext->setText(QString("第%1关|数字范围：1-%2|最大尝试次数：%3|经验值：%4|总经验值：%5").arg(episode).arg(max_num).arg(chance).arg(EP).arg(sum_EP));
	guessinput->setPlaceholderText("请输入1-" + QString::number(max_num) + "之间的数字：");
	guessinput->setValidator(new QIntValidator(1, max_num, this));
}

void Guesswin::startnewgame()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<>int_dis(1, max_num);

	answer = int_dis(gen);
	attempts = 0;
	update_EP = 0;

	historytext->clear();
	statuslabel->setText("新游戏开始，请输入你的猜测：");
	statuslabel->setStyleSheet("font-size: 14px; color: #1565C0;");
	guessinput->setEnabled(true);
	guessinput->clear();
	guessinput->setFocus();

	QString gameinfo = QString("游戏开始，数字范围：1-%1，最大猜测次数：%2").arg(max_num).arg(chance);
	historytext->append(gameinfo);
}


void Guesswin::setupUI()
{
	QVBoxLayout* mainlay = new QVBoxLayout(this);

	infortext->setStyleSheet("font-size: 16px; font-weight: bold; color: #2E7D32;");
	mainlay->addWidget(infortext);

	statuslabel->setText("请输入你的猜测：");
	statuslabel->setStyleSheet("font-size: 14px; color: #1565C0;");
	mainlay->addWidget(statuslabel);

	mainlay->addWidget(guessinput);
	mainlay->addWidget(new QLabel("猜测历史："));

	historytext->setMaximumHeight(200);
	historytext->setReadOnly(true);
	mainlay->addWidget(historytext);

	conform->setStyleSheet(R"(
							    QPushButton{background-color:#2196F3;color:white;font-size:16px;padding:8px 20px;border-radius:4px;}
								QPushButton:hover{background-color:#1976D2;}
							  )");

	
	backbtn->setStyleSheet("background-color:#607D8B; color:white; padding:8px;");
	newbtn->setStyleSheet("background-color:#4CAF50;color:white;padding:8px;");

	QHBoxLayout* btnlay = new QHBoxLayout();
	btnlay->addWidget(conform);
	btnlay->addWidget(newbtn);
	btnlay->addWidget(backbtn);
    mainlay->addLayout(btnlay);

	connect(conform, &QPushButton::clicked, this, &Guesswin::guessway);
	connect(guessinput, &QLineEdit::returnPressed, this, &Guesswin::guessway);
	connect(backbtn, &QPushButton::clicked, this, &Guesswin::goback);
	connect(newbtn, &QPushButton::clicked, this, &Guesswin::nextgame);
}

void Guesswin::guessway()
{
	if (guessinput->text().isEmpty())
	{
		QMessageBox::warning(this,"警告","输入错误，请重新输入");
		return;
	}

	int guess = guessinput->text().toInt();
	attempts++;
	
	std::stringstream result = gameway_judge(guess, answer, chance, attempts);
	statuslabel->setText(QString::fromStdString(result.str()));

	if (guess == answer)
	{
		statuslabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #4CAF50;");

		if (endless)
		{
			update_EP += EP;
			historyentry = QString("恭喜通过第%1关，获得%2经验值，当前总经验值：%3").arg(episode).arg(EP).arg(update_EP);
			historytext->append(historyentry);
			is_win = true;
			nextepisode();
		}

		else
		{
			historyentry = QString("恭喜你，第%1次猜测正确！获得%2经验值").arg(attempts).arg(EP);
			historytext->append(historyentry);
			QMessageBox::information(this, "游戏结束信息", "恭喜你获得胜利！");
			guessinput->setEnabled(false);
			is_win = true;
			if (mode == 1)
			{
				record_save(is_win, difficulty, attempts, max_num, chance, EP);
				update_EP = is_win ? EP : 0;
			}
			if (mode == 2)
			{
				record_save(is_win, level, attempts, max_num, chance, EP);
				update_EP = is_win ? EP : (-EP);
			}
			update_all(update_EP);
		}

	}
	else
	{
		statuslabel->setStyleSheet("font-size: 14px; color: #FF9800;");
		historyentry = QString("第%1次：%2-%3").arg(attempts).arg(guess).arg(QString::fromStdString(result.str()));
		historytext->append(historyentry);

		if (attempts >= chance)
		{
			if (endless)
			{
				guessinput->setEnabled(false);
				QMessageBox::information(this, "游戏结束",QString("很遗憾，你在第%1关失败了！\n正确答案是 %2\n最终总经验值: %3").arg(episode).arg(answer).arg(update_EP));
				record_save(is_win, episode, attempts, max_num, chance, EP);
				update_all(update_EP);
			}
			else
			{
				guessinput->setEnabled(false);
				QMessageBox::information(this, "游戏结束信息", "很遗憾，本次游戏失败！");
			}
		}
		is_win = false;
	}
	guessinput->clear();
}

void Guesswin::nextgame()
{
	if (endless)
	{
		episode = 1;
		update_EP = 0;
		getendlesssettings(episode, max_num, chance, EP);
	}
	else
	{
		startnewgame();
	}
}

void Guesswin::goback()
{
	if (prewin)
		prewin->show();
	this->hide();
}

void Guesswin::getendlesssettings(int& episode, int& max_num, int& chance, int& EP)
{
	if (episode == 1)
	{
		max_num = 100;
		chance = 10;
		update_EP = 0;
		EP = 5;
		startnewgame();
		setendlessgame(episode,max_num,chance,EP);
		return;
	}
	if (is_win == true)
	{
		attempts = 0;
	    startnewgame();
		setendlessgame(episode, max_num, chance, EP);
	}
	else
	{
		attempts = 0;
		nextgame();
		setendlessgame(episode, max_num, chance, EP);
	}
}

void Guesswin::nextepisode()
{
	episode++;
	if (episode <= 6) 
	{
		max_num += 100;
		chance += 1;
	}
	else if (episode <= 15) 
	{
		max_num += 400;
		chance += 2;
		EP = 6;
	}
	else if (episode <= 30) 
	{
		max_num += 800;
		chance += 3;
		EP = 10;
	}
	else if (episode <= 40) 
	{
		max_num += 1200;
		chance += 3;
		EP = 15;
	}
	else if (episode <= 55) 
	{
		max_num += 2000;
		chance += 4;
		EP += 2;
	}
	else if (episode <= 75)
	{
		max_num += 5000;
		chance += 4;
		EP += 5;
	}
	else if (episode <= 100) 
	{
		max_num += 15000;
		chance += 5;
		EP += 10;
	}
	else 
	{
		max_num += 50000;
		chance += 3;
		EP += 25;
	}
	QString endlessmessage = endlessgammemessage(episode);

	QMessageBox::information(this, QString("第%1关").arg(episode),QString("%1\n数字范围: 1-%2\n尝试次数: %3\n奖励经验: %4").arg(endlessmessage).arg(max_num).arg(chance).arg(EP));

	getendlesssettings(episode, max_num, chance, EP);
}
