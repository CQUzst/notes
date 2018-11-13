#include "calculator.h"
#pragma execution_character_set("utf-8")
using namespace std;

int Change(const char *S, char OPS[], int &len);
int EXchange(char B[], int len, double &result, bool &flag);

calculator::calculator(QWidget *parent) : QMainWindow(parent)
{
    QWidget *widget = new QWidget; //构建一个QWidget布局将设置的布局添加进这个QWidget
    this->setCentralWidget(widget);

    QShortcut *key1=new QShortcut(QKeySequence(Qt::Key_1),this);
    QShortcut *key2=new QShortcut(QKeySequence(Qt::Key_2),this);
    QShortcut *key3=new QShortcut(QKeySequence(Qt::Key_3),this);
    QShortcut *key4=new QShortcut(QKeySequence(Qt::Key_4),this);
    QShortcut *key5=new QShortcut(QKeySequence(Qt::Key_5),this);
    QShortcut *key6=new QShortcut(QKeySequence(Qt::Key_6),this);
    QShortcut *key7=new QShortcut(QKeySequence(Qt::Key_7),this);
    QShortcut *key8=new QShortcut(QKeySequence(Qt::Key_8),this);
    QShortcut *key9=new QShortcut(QKeySequence(Qt::Key_9),this);
    QShortcut *key0=new QShortcut(QKeySequence(Qt::Key_0),this);
    QShortcut *key_add=new QShortcut(QKeySequence(Qt::Key_P),this);
    QShortcut *key_min=new QShortcut(QKeySequence(Qt::Key_Minus),this);
    QShortcut *key_mul=new QShortcut(QKeySequence(Qt::Key_Asterisk),this);
    QShortcut *key_div=new QShortcut(QKeySequence(Qt::Key_Slash),this);
    QShortcut *key_equ=new QShortcut(QKeySequence(Qt::Key_Equal),this);
    QShortcut *key_back=new QShortcut(QKeySequence(Qt::Key_Backspace),this);

    connect(key1,SIGNAL(activated()),this,SLOT(buttonOneClicked()));
    connect(key2,SIGNAL(activated()),this,SLOT(buttonTwoClicked()));
    connect(key3,SIGNAL(activated()),this,SLOT(buttonThreeClicked()));
    connect(key4,SIGNAL(activated()),this,SLOT(buttonFourClicked()));
    connect(key5,SIGNAL(activated()),this,SLOT(buttonFiveClicked()));
    connect(key6,SIGNAL(activated()),this,SLOT(buttonSixClicked()));
    connect(key7,SIGNAL(activated()),this,SLOT(buttonSevenClicked()));
    connect(key8,SIGNAL(activated()),this,SLOT(buttonEightClicked()));
    connect(key9,SIGNAL(activated()),this,SLOT(buttonNineClicked()));
    connect(key0,SIGNAL(activated()),this,SLOT(buttonZeroClicked()));
    connect(key_add,SIGNAL(activated()),this,SLOT(buttonAddClicked()));
    connect(key_min,SIGNAL(activated()),this,SLOT(buttonSubClicked()));
    connect(key_equ,SIGNAL(activated()),this,SLOT(buttonEquClicked()));
    connect(key_div,SIGNAL(activated()),this,SLOT(buttonDivClicked()));
    connect(key_mul,SIGNAL(activated()),this,SLOT(buttonMulClicked()));
    connect(key_back,SIGNAL(activated()),this,SLOT(buttonACClicked()));

    inputLine = new QLineEdit;
    inputLine->setText(input);

    zeroButton = new QPushButton("0");
    oneButton = new QPushButton("1");
    twoButton = new QPushButton("2");
    threeButton = new QPushButton("3");
    fourButton = new QPushButton("4");
    fiveButton = new QPushButton("5");
    sixButton = new QPushButton("6");
    sevenButton = new QPushButton("7");
    eightButton = new QPushButton("8");
    nineButton = new QPushButton("9");
    decButton = new QPushButton(".");

    botButton = new QPushButton("±");
    timButton = new QPushButton("Time");
    addButton = new QPushButton("+");
    subButton = new QPushButton("-");
    mulButton = new QPushButton("*");
    divButton = new QPushButton("/");
    equButton = new QPushButton("=");

    lefButton = new QPushButton("(");
    rigButton = new QPushButton(")");
    CEButton = new QPushButton("CE");
    ACButton = new QPushButton("AC");

    QGridLayout *H = new QGridLayout(this); //声明了一个网格布局

    inputLine->setFixedHeight(25); //调整第一行大小
    CEButton->setFixedHeight(25);
    ACButton->setFixedHeight(25);

    H->addWidget(inputLine,0,0,1,3);
    H->setRowStretch(0,100);
    H->addWidget(CEButton,0,3);
    H->addWidget(ACButton,0,4);

    H->addWidget(oneButton,1,0);
    H->addWidget(twoButton,1,1);
    H->addWidget(threeButton,1,2);
    H->addWidget(botButton,1,3);
    H->addWidget(timButton,1,4);

    H->addWidget(fourButton,2,0);
    H->addWidget(fiveButton,2,1);
    H->addWidget(sixButton,2,2);
    H->addWidget(addButton,2,3);
    H->addWidget(subButton,2,4);

    H->addWidget(sevenButton,3,0);
    H->addWidget(eightButton,3,1);
    H->addWidget(nineButton,3,2);
    H->addWidget(mulButton,3,3);
    H->addWidget(divButton,3,4);

    H->addWidget(zeroButton,4,0);
    H->addWidget(decButton,4,1);
    H->addWidget(lefButton,4,2);
    H->addWidget(rigButton,4,3);
    H->addWidget(equButton,4,4);

    H->addWidget(Label,5,0,1,3);

    widget->setLayout(H);

    connect(zeroButton, SIGNAL(clicked()), this, SLOT(buttonZeroClicked()));
    connect(oneButton, SIGNAL(clicked()), this, SLOT(buttonOneClicked()));
    connect(twoButton, SIGNAL(clicked()), this, SLOT(buttonTwoClicked()));
    connect(threeButton, SIGNAL(clicked()), this, SLOT(buttonThreeClicked()));
    connect(fourButton, SIGNAL(clicked()), this, SLOT(buttonFourClicked()));
    connect(fiveButton, SIGNAL(clicked()), this, SLOT(buttonFiveClicked()));
    connect(sixButton, SIGNAL(clicked()), this, SLOT(buttonSixClicked()));
    connect(sevenButton, SIGNAL(clicked()), this, SLOT(buttonSevenClicked()));
    connect(eightButton, SIGNAL(clicked()), this, SLOT(buttonEightClicked()));
    connect(nineButton, SIGNAL(clicked()), this, SLOT(buttonNineClicked()));

    connect(addButton, SIGNAL(clicked()), this, SLOT(buttonAddClicked()));
    connect(subButton, SIGNAL(clicked()), this, SLOT(buttonSubClicked()));
    connect(mulButton, SIGNAL(clicked()), this, SLOT(buttonMulClicked()));
    connect(divButton, SIGNAL(clicked()), this, SLOT(buttonDivClicked()));

    connect(botButton, SIGNAL(clicked(bool)), this, SLOT(buttonBotClicked()));//正负号
    connect(timButton, SIGNAL(clicked(bool)), this, SLOT(buttonTimClicked()));//时间

    connect(timer,SIGNAL(timeout()),this,SLOT(buttonTimClicked()));
    timer->start(1000);

    connect(decButton, SIGNAL(clicked(bool)), this, SLOT(buttonDecClicked()));//点号

    connect(lefButton, SIGNAL(clicked(bool)), this, SLOT(buttonLefClicked()));//左括号
    connect(rigButton, SIGNAL(clicked(bool)), this, SLOT(buttonRigClicked()));//右括号

    connect(CEButton, SIGNAL(clicked()), this, SLOT(buttonCEClicked()));
    connect(ACButton, SIGNAL(clicked()), this, SLOT(buttonACClicked()));

    connect(equButton, SIGNAL(clicked()), this, SLOT(buttonEquClicked())); //等于号*/

}

void calculator::buttonZeroClicked()  //以下是实现相应的槽函数
{
    if (input == "0")
        input = '0';
    else input = input + '0';
    inputLine->setText(input);
}

void calculator::buttonOneClicked()
{
    if (input == "0")
        input = '1';
    else input = input + '1';
    inputLine->setText(input);
}

void calculator::buttonTwoClicked()
{
    if (input == "0")
        input = '2';
    else input = input + '2';
    inputLine->setText(input);
}

void calculator::buttonThreeClicked()
{
    if (input == "0")
        input = '3';
    else input = input + '3';
    inputLine->setText(input);
}

void calculator::buttonFourClicked()
{
    if (input == "0")
        input = '4';
    else input = input + '4';
    inputLine->setText(input);
}

void calculator::buttonFiveClicked()
{
    if (input == "0")
        input = '5';
    else input = input + '5';
    inputLine->setText(input);
}

void calculator::buttonSixClicked()
{
    if (input == "0")
        input = '6';
    else input = input + '6';
    inputLine->setText(input);
}

void calculator::buttonSevenClicked()
{
    if (input == "0")
        input = '7';
    else input = input + '7';
    inputLine->setText(input);
}

void calculator::buttonEightClicked()
{
    if (input == "0")
        input = '8';
    else input = input + '8';
    inputLine->setText(input);
}

void calculator::buttonNineClicked()
{
    if (input == "0")
        input = '9';
    else input = input + '9';
    inputLine->setText(input);
}

void calculator::buttonAddClicked()
{
    if (input == "0")
        input = '+';
    else input = input + '+';
    inputLine->setText(input);
}

void calculator::buttonSubClicked()
{
    if (input == "0")
        input = '-';
    else input = input + '-';
    inputLine->setText(input);
}

void calculator::buttonMulClicked()
{
    if (input == "0")
        input = '*';
    else input = input + '*';
    inputLine->setText(input);
}

void calculator::buttonDivClicked()
{
    if (input == "0")
        input = '/';
    else input = input + '/';
    inputLine->setText(input);
}

void calculator::buttonTimClicked() //Time
{
    //格式化输出当前时间
    QString t = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    Label->setText(t);
}

void calculator::buttonDecClicked() //小数点
{
    if (input == "0")
        input = '.';
    else input = input + '.';
    inputLine->setText(input);
}

void calculator::buttonBotClicked() //加减号
{
    if (input == "0")
        input = '-';
    else
    {
        QString::iterator p = input.end();
        p--;
        if ('-' == *p)
        {input = input.left(input.length() - 1);
        input = input + '+';
        }
        else input = input + '-';

    }
    inputLine->setText(input);
}

void calculator::buttonLefClicked()//左括号
{
    if (input == "0")
        input = '(';
    else input = input + '(';
    inputLine->setText(input);
}

void calculator::buttonRigClicked()//右括号
{
    if (input == "0")
        input = ')';
    else input = input + ')';
    inputLine->setText(input);
}

void calculator::buttonCEClicked()
{
    input = input.left(input.length() - 1); //减去一字符
    inputLine->setText(input);
}
void calculator::buttonACClicked() //直接清空
{
    input = '0';
    inputLine->setText(input);
}

void calculator::buttonEquClicked()//等于号
{
    std::string str = input.toStdString();
    const char *S = str.c_str();
    char OPS[50];
    int len;
    double result;
    QString change;
    bool flag;
    Change(S, OPS, len);
    EXchange(OPS, len, result, flag);
    change = QString::number(result, 10, 6);
    input = input + "=" + change;
    inputLine->setText(input);
    while(bool(SIGNAL(clicked())==0))
    {
          inputLine->setText(input);
    }
    input = '0';
}

//string s is origin string,OPS is Operator stack
int Change(const char *S, char OPS[], int &len)
{
    QStack<char> OPE;
    int i, j = 0;
    for (i = 0; i < strlen(S); i++)
    {
        switch (S[i])
        {
        case'+':
            if (OPE.isEmpty())
                OPE.push(S[i]);
            //if top is multiply or division,move top to behind
            else if (OPE.top() == '*' || OPE.top() == '/')
            {
                OPS[j++] = OPE.pop();
                i--;//ptr to before,top of multiply or division move to behind
            }
            else
                OPE.push(S[i]);
            break;
        case'-':
            // if  - is not mean a negative number or - is not the first char
            if ('(' != S[i - 1] && 0 != i)
            {
                if (OPE.isEmpty())
                    OPE.push(S[i]);
                else if (OPE.top() == '*' || OPE.top() == '/')
                {
                    OPS[j++] = OPE.pop();
                    i--;
                }
                else
                    OPE.push(S[i]);
            }
            else//- is a negative number
            {
                while ((S[i] >= '0'&&S[i] <= '9') || S[i] == '.')
                {
                    OPS[j++] = S[i];
                    if ('-' == S[i])
                        OPS[j++] = '@';
                    i++;
                }
                i--;
                OPS[j++] = '#';  //数字中的间隔符
            }
            break;
        case'*':
        case'/':
            OPE.push(S[i]);
            break;
        case'(':
            OPE.push(S[i]);
            break;
        case')':
            while (OPE.top() != '(')
            {
                OPS[j++] = OPE.pop();
            }
            OPE.pop();
            break;
        default:
            while (S[i] >= '0'&&S[i] <= '9' || S[i] == '.' || ('-' == S[i] && S[i - 1]<'0'&&S[i - 1]>'9'))
            {

                OPS[j++] = S[i];

                i++;
            }
            i--;
            OPS[j++] = '#';  //数字中的间隔符
            break;
        }
    }
    while (!OPE.isEmpty())
    {
        OPS[j++] = OPE.pop();
    }
    len = j;
    return 0;
}

int EXchange(char B[], int len, double &result, bool &flag)
{
    int i;
    double a;
    double b;
    double c;
    QStack<double>SZ;
    for (i = 0; i < len; i++)
    {
        switch (B[i])
        {
        case'+':
        {
            a = SZ.pop();
            b = SZ.pop();
            c = b + a;
            SZ.push(c);
        }
        break;
        case'-':
        {
            if ('@' != B[i + 1])
            {
                a = SZ.pop();
                b = SZ.pop();
                c = b - a;
                SZ.push(c);
            }
            else
            {
                int jx = 0;
                double dx;
                char *stx = new char[10];
                while (B[i] != '#')
                {
                    if ('@' != B[i])
                        stx[jx++] = B[i];
                    i++;

                }
                dx = atof(stx);
                SZ.push(dx);
                delete stx;
            }
        }
        break;
        case'*':
        {
            a = SZ.pop();
            b = SZ.pop();
            c = b*a;
            SZ.push(c);
        }
        break;
        case'/':
        {
            a = SZ.pop();
            b = SZ.pop();
            if (a == 0)
            {
                flag = false;
                return 0;
            }
            c = b / a;
            SZ.push(c);
        }
        break;
        default:
            int j = 0;
            double d;
            char *st = new char[10];
            while (B[i] != '#')
            {
                st[j++] = B[i];
                i++;
            }
            d = atof(st);
            SZ.push(d);
            delete st;
            break;
        }
    }
    result = SZ.top();
    return 0;
}
calculator::~calculator()
{

}

