#include"myList.h"
#define OPSUM 14

class calculator {
public:
	char formular[50];
	myList<char> op;
	myList<double> num_op;
	calculator();
	void start();
	void input();
	bool is_in(char,char*);
	bool illegal_check();
	bool sep_check();
	bool num_check();
	bool check();
	double get_num(int start,const char *);
	void set_formular();
	bool calculate();
	void output();
	void clear();
	int get_in_prio(char);
	int get_out_prio(char);
	int get_op_index(char, const char **);
	bool get_result();
};
double change_char(char m)
{
	return m - 48;
}

char num_dot_all[] = { '0','1','2','3','4','5','6','7','8','9','.' };
char num_all[] = { '0','1','2','3','4','5','6','7','8','9' };
char op_all[] = { '+','-','*','/','%','^','#' };
char sep_all[] = { '(', '[','{',')',']' ,'}',')' };
char sep_left[] = { '(', '[','{' };
char sep_right[] = { ']' ,'}',')' };
const char* instk_priority[] = { "(3", "[2","{1",")10","]11" ,"}10",")12","+5","-5","*7","/7","%7" ,"^9", "#0" };
const char* outstk_priority[] = { "(12", "[11","{10",")3","]2" ,"}1","3","+4","-4","*6","/6" ,"%6","^8","#0" };
char op_sep_all[] = { '+','-','*','/','%','^','#' ,  '(', '[','{',')',']' ,'}',')' };
/*    #  {       [    (     ^  *,/,%      +,-    )         ]       }
in    0  1      2    3   9    7        5       12     11     10
out  0  10  11 12   8    6         4       3        2      1  
*/

void calculator::start() {
	while (1)
	{
		this->input();
		if (this->formular[1] == '#') return;
		if (this->calculate())
		{
			this->output();
		}
		this->clear();
	}
}

// Construct
calculator::calculator() {
	for (int i = 0; i < 50; i++)
	{
		this->formular[i] = '0';
	}
}

// Input Formular And Output Result
void calculator::input() {
	cout << "Input a Formula：(End the program with #)"<<endl;
	cin >> this->formular;
	this->formular[strlen(this->formular) + 1] = '\0';
	this->formular[strlen(this->formular)] = '#';
	if (this->formular[0] == '#')
		return;
	while (!this->check())
	{
		if (this->formular[0] == '#')
			return;
		cout << "Input a Formula：(End the program with #)" << endl;
		cin >> this->formular;
		this->formular[strlen(this->formular)+1] = '\0';
		this->formular[strlen(this->formular)] = '#';
	}
}
void calculator::output() {
	double answer;
	num_op.Top(answer);
	cout << "The Answer is : " << answer << endl;
}

// Determine Char is in An Array
bool calculator::is_in(char left, char* right) {
	int index = 0;
	for (; index < strlen(right); index++)
	{
		if (left == right[index])
		{
			return true;
		}
	}
	return false;
}

// Check Input
bool calculator::illegal_check() {
	int index = 0;
	int wrong_flag = 0;
	for (; index < strlen(this->formular); index++)
	{
		if (this->is_in(this->formular[index], num_dot_all))
		{
			continue;
		}
		else if (this->is_in(this->formular[index], op_all))
		{
			continue;
		}
		else if (this->is_in(this->formular[index], sep_all))
		{
			continue;
		}
		else
		{
			cout << "Unknown Char At：" << index+1 << endl;
			wrong_flag = 1;
		}
	}
	if(wrong_flag) return false;
	return true;
}
bool calculator::num_check() {
	int index = 0,flag = 1,dot_flag = 0;
	/*
	10+()
	10+(14)
	10+(14()
	*/
	for (; index < strlen(this->formular); index++)
	{
		if (index == 0)
		{
			if (this->is_in(this->formular[index], sep_all))
			{
				dot_flag = 0;
				continue;
			}
			else if (this->is_in(this->formular[index], op_all))
			{
				dot_flag = 0;
				cout << "Wrong Operator At: " << index + 1 << endl;
				flag = 0;
				continue;
			}
			else
			{
				if (this->formular[index] == '.')
				{
					cout << "Wrong dot At: " << index + 1 << endl;
					flag = 0;
				}
				else
				{
					flag = 1;
				}
				continue;
			}
		}
		else
		{
			if (this->is_in(this->formular[index], sep_left))
			{
				dot_flag = 0;
				if (this->is_in(this->formular[index - 1], num_dot_all))
				{
					cout << "Wrong Separator At: " << index + 1 << endl;
					flag = 0;
				}
				if (this->is_in(this->formular[index - 1], sep_right))
				{
					cout<< "Wrong Separator At: " << index + 1 << endl;
					flag = 0;
				}
				continue;
			}
			else if (this->is_in(this->formular[index], op_all))
			{
				dot_flag = 0;
				if (this->is_in(this->formular[index - 1], num_dot_all)||this->is_in(this->formular[index-1],sep_right))
				{
					continue;
				}
				else
				{
					cout << "Operator At: " << index << " is Wrong" << endl;
					flag = 0;
					continue;
				}
			}
			else if(this->is_in(this->formular[index], sep_right))
			{
				dot_flag = 0;
				if (this->is_in(this->formular[index-1],num_dot_all)|| this->is_in(this->formular[index-1],sep_right))
				{
					continue;
				}
				else
				{
					cout << "Wrong Separator At: " << index + 1 << endl;
					flag = 0;
					continue;
				}
			}
			else
			{
				if (this->is_in(this->formular[index - 1], sep_right))
				{
					cout << "Lack Operator At: " << index + 1 << endl;
					flag = 0;
				}
				else if (this->formular[index] == '.'&&!this->is_in(this->formular[index - 1],num_all))
				{
					cout << "Wrong dot At: " << index + 1<<endl;
					flag = 0;
				}
				else if (this->formular[index] == '.')
				{
					dot_flag++;
					if (dot_flag > 1)
					{
						cout << "Wrong dot At: " << index + 1 << endl;
						flag = 0;
					}
				}
				else
				{
					continue;
				}
			}
		}
	}
	return flag ? true : false;
}
bool calculator::sep_check() {
	myList<char> sepStack;
	char temp;
	int counter = 0;
	int flag = 1;
	for (;counter<strlen(this->formular);counter++)
	{
		if (this->is_in(this->formular[counter], sep_left))
		{
			sepStack.Push(this->formular[counter]);
		}
		else if(this->is_in(this->formular[counter],sep_right))
		{
			if(!sepStack.Empty())
				sepStack.Top(temp);
			if (temp == '(' && this->formular[counter] == ')')
			{
			}
			else if (temp == '['&& this->formular[counter] == ']')
			{
			}
			else if (temp == '{'&& this->formular[counter] == '}')
			{
			}
			else
			{
				cout << "Wrong Separator At: " << counter + 1 << endl;
				flag = 0;
			}
			if(!sepStack.Empty())
				sepStack.Pop();
		}
	}
	if (!sepStack.Empty())
	{
		cout << "UnMatched Separator: " << sepStack << endl;
		flag = 0;
	}
	return flag ? true : false;
}
bool calculator::check() {
	bool f1 = this->illegal_check(), f2 = this->num_check(), f3 = this->sep_check();
	return f1&& f2 && f3? true : false;
}

// Transfer Char to Double
double calculator::get_num(int start, const char *head) {
	int sum = 0, double_flag = 1,dot_flag = 0;
	double temp = 0;
	int tenth = 1;
	for (;(this->is_in(head[start + sum], num_dot_all)); sum++)
	{
		if (head[start + sum] == '.')
		{
			double_flag = 0;
			dot_flag = sum;
		}
	}
	if (double_flag)
	{
		for (sum--; sum >= 0; sum--)
		{
			temp += change_char(head[start + sum])*tenth;
			tenth *= 10;
		}
	}
	else
	{
		for (double_flag = dot_flag-1;double_flag>=0;double_flag--)
		{
			temp += change_char(head[start + double_flag])*tenth;
			tenth *= 10;
		}
		for (double_flag = dot_flag + 1, tenth = 10; double_flag <= sum-1; double_flag++)
		{
			temp += change_char(head[double_flag+start]) / tenth;
			tenth *= 10;
		}
	}
	return temp;
}

// Set Formular & Clear
void calculator::set_formular() {
	cout << "Input a Formular: (End the program with #)" << endl;
	cin >> this->formular;
}
void calculator::clear(){
	char temp = '#';
	this->op.Clear();
	this->num_op.Clear();
	for (int i = 0; i < 50; i++)
	{
		this->formular[i] = '0';
	}
	this->op.Push(temp);
}

// Calculate
bool calculator::calculate() {
	this->op.Push('#');
	int index_formular = 0, temp;
	char opt_instk;
	double answer;
	double operand;
	for (;!this->op.Empty();index_formular++)
	{
		//是运算符的话
		if (this->is_in(this->formular[index_formular],op_sep_all))
		{
			this->op.Top(opt_instk);
			//栈外比站内优先级高
			if (this->get_out_prio(this->formular[index_formular]) > this->get_in_prio(opt_instk))
			{
				this->op.Push(this->formular[index_formular]);
			}
			else if(this->get_out_prio(this->formular[index_formular]) < this->get_in_prio(opt_instk))
			{
				if (this->get_result())
				{
					if (this->is_in(this->formular[index_formular], sep_right))
					{
						index_formular--;
					}
					else if(this->formular[index_formular] != '#')
					{
						this->op.Push(this->formular[index_formular]);
					}
					else
					{
						index_formular--;
					}
				}
				else
				{
					cout << "Calculating Stop"<<endl;
					return false;
				}
			}
			else 
			{
				this->op.Pop();
			}
		}
		else if (this->is_in(this->formular[index_formular], num_dot_all))
		{
			this->num_op.Push(this->get_num(index_formular, this->formular));
			for (temp = 0; this->is_in(this->formular[temp + index_formular], num_dot_all); temp++)
			{

			}
			index_formular = index_formular + temp - 1;
		}
	}
	return true;
}

// Get Priority
int calculator::get_in_prio(char op) {
	int op_index;
	op_index = this->get_op_index(op, instk_priority);
	return int(this->get_num(1, instk_priority[op_index]));
}
int calculator::get_out_prio(char op) {
	int op_index;
	op_index = this->get_op_index(op, outstk_priority);
	return int(this->get_num(1, outstk_priority[op_index]));
}
int calculator::get_op_index(char op,const char **lst) {
	for (int index = 0; index < OPSUM; index++)
	{
		if (lst[index][0] == op)
			return index;
	}
	return -1;
}

// Get One Calculate Result
bool calculator::get_result() {
	char temp_operator;
	double right_opd, left_opd;
	this->num_op.Top(right_opd);
	this->num_op.Pop();
	this->num_op.Top(left_opd);
	this->num_op.Pop();
	this->op.Top(temp_operator);
	this->op.Pop();
	switch (temp_operator)
	{
	case '+': 
		this->num_op.Push(left_opd + right_opd);
		break;
	case '-':
		this->num_op.Push(left_opd - right_opd);
		break;
	case '*':
		this->num_op.Push(left_opd* right_opd);
		break;
	case '/':
		if (right_opd)
		{
			this->num_op.Push(left_opd / right_opd);
			break;
		}
		else
		{
			cout << "Division By Zero" << endl;
			return false;
		}
	case '%':
		if (right_opd)
		{
			this->num_op.Push(int(left_opd) % int(right_opd));
			break;
		}
		else
		{
			cout << "Division By Zero" << endl;
			return false;
		}
	case '^':
		this->num_op.Push(pow(left_opd,right_opd));
		break;
	default:
		return false;
	}
	this->output();
	return true;
}
//1+2-[3*3-4*5)]
//1+2-[3*3-4*5)
//1+2-[3*(3-4*5]