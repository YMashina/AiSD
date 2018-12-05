#include <iostream> 
#include <fstream> 
#include <cstdlib> 
#include <locale.h> 
#include "Queue.cpp"

using namespace std;
void menu()//����
{
	cout << "============================================" << endl;
	cout << "Davkaeva Valentina 7382 lab3 variant 5v" << endl;
	cout << "====================MENU====================" << endl;
	cout << "============================================" << endl;
	cout << "1.Read the string from file." << endl;
	cout << "2.End the program." << endl;
	cout << "============================================" << endl;
	cout << "Your choice:";
}
void call_error(Queue & Q3, int num) // �������,������������ ����� ������ 
{
	switch (num)
	{
	case 1:
	{	cout << "------------------------------------Error-----------------------------------------" << endl;
	cout << "The last read element doesn't satisfy the definition of the text.Expected symbol or curcle close bracket." << endl;
	break;
	}
	case 2:
	{	cout << "------------------------------------Error-----------------------------------------" << endl;
	cout << "The last read element doesn't satisfy the definition of the text.Expected symbol or square close bracket." << endl;
	break;
	}
	case 3:
	{
		cout << "------------------------------------Error-----------------------------------------" << endl;
		cout << "The last read element doesn't satisfy the definition of the text.Expected symbol or figure close bracket." << endl;
		break;
	}
	case 4:
	{
		cout << "------------------------------------Error-----------------------------------------" << endl;
		cout << "The last read element doesn't satisfy the definition of the text.Expected symbol or open bracket of any tipe." << endl;
		break;
	}
	case 5:
	{
		cout << "------------------------------------Error-----------------------------------------" << endl;
		cout << "Not enough for the text.Expected symbol or circle close bracket." << endl;
		break;
	}
	case 6:
	{
		cout << "------------------------------------Error-----------------------------------------" << endl;
		cout << "Not enough for the text.Expected symbol or figure close bracket." << endl;
		break;
	}
	case 7:
	{
		cout << "------------------------------------Error-----------------------------------------" << endl;
		cout << "Not enough for the text.Expected symbol or square close bracket." << endl;
		break;
	}
	}
	cout << "This isn't a text!" << endl;
	cout << "Part of the string, which can be completed to the text: ";//����� ������, ������� �������� �������� � ����� ���� ���������. 
	while (Q3.can_pop())//���� ������� ����� �����
		cout << Q3.pop() << " ";//������ ����������� ��������� �������
	cout << "\nEnd of analyzing! " << endl;//��������� ����� ���������. 
	system("pause");
	exit(1);
}
bool cur_brckt_o(char symb) // �������� ������� �������� ������ 
{
	if (symb == '(')
		return true;
	else
		return false;
}
bool cur_brckt_c(char symb) // �������� ������� �������� ������ 
{
	if (symb == ')')
		return true;
	else
		return false;
}
bool sq_brckt_o(char symb) // �������� ���������� �������� ������ 
{
	if (symb == '[')
		return true;
	else
		return false;
}
bool sq_brckt_c(char symb) // �������� ���������� �������� ������
{
	if (symb == ']')
		return true;
	else
		return false;
}
bool fig_brckt_o(char symb) // �������� �������� �������� ������ 
{
	if (symb == '{')
		return true;
	else
		return false;
}
bool fig_brckt_c(char symb) // �������� �������� �������� ������
{
	if (symb == '}')
		return true;
	else
		return false;
}

bool symb_f(char symb) //�������� �� ������� ������ 
{
	if (symb == '(' || symb == '{' || symb == '[' || symb == ')' || symb == '}' || symb == ']')
		return false;
	else
		return true;
}
void is_it_txt(Stack Q1, Queue & Q3) //������������� �������
{
	char symb;
	Stack pos;//����,�������� ��� �������� ������� � ���� ������
	bool bracket_c_cur, bracket_c_sq, bracket_c_fig;
	int n;
	bracket_c_cur = bracket_c_sq = bracket_c_fig = false;//������� �� ��������� �������� ������ ������ ���� 
	while (Q1.can_pop())//���� ���� �� ����
	{
		symb = Q1.pop();//������ ��������
		cout << "   From the stack, the element is extracted [" << symb << "] ";//�� ����� �������� ������� [ 
		if (symb_f(symb))// ���� ������
		{
			cout << ",which is the symbol " << endl;//������� �������� ���������.
			if (pos.can_pop()) {//���� ��� ���� �������� ������ ������ ����
				n = pos.pop();//������,������ ����
				if (n == 1) {//������� ������
					bracket_c_cur = true;//����� ��������� �����������-��  ������� ������
					bracket_c_sq = bracket_c_fig = false;//��������� ���� ������������� ������ ���������
				}
				if (n == 2) {//�������� ������
					bracket_c_fig = true;//����� ��������� �����������-�� �������� ������
					bracket_c_sq = bracket_c_cur = false;//��������� ���� ������������� ������ ���������

				}
				if (n == 3) {//���������� ������
					bracket_c_sq = true;//����� ��������� �������������  ���������� ������
					bracket_c_cur = bracket_c_fig = false;//��������� ���� ������������� ������ ���������
				}
				pos.push(n);//���������� ����������� ������� � ����

			}
			else bracket_c_cur = bracket_c_sq = bracket_c_fig = false;//���� ���,�� ��������� �������������
			Q3.push(symb);//������� � ������� ��������������� �������
		}

		if (cur_brckt_o(symb))//������� ����������� ������
		{
			cout << ",which is a curcle open bracket " << endl;
			bracket_c_cur = true;//����� ��������� �������������  ������� ������
			bracket_c_sq = bracket_c_fig = false;//��������� ���� ������������� ���-��� ���������
			pos.push(1);//������� � ���� ����� ������,������� �� ��������� ����� ������ ���� �������
			Q3.push(symb);//������� � ������� ��������������� �������
		}
		if (cur_brckt_c(symb))//������� ����������� ������
		{
			cout << ",which is a curcle close bracket" << endl;
			if (!bracket_c_cur&&bracket_c_fig) call_error(Q3, 3);//���� �� ������ ���� �� ������ ������ ������������� ������� ������,� ������ ������ ��������,�� ������ ����-���������� ������
			if (!bracket_c_cur&&bracket_c_sq) call_error(Q3, 2);//���� �� ������ ���� �� ������ ������ ������������� ������� ������,� ������ ������ ����������,�� ������ ����-���������� ������
			if (pos.can_pop()) {//���� ��� ���� �������� ������ ������ ����
				n = pos.pop();//������,������ ����
				if (n == 1) {//���� ��� �������
					if (pos.can_pop()) {//���������,���� ��� �������� ������
						n = pos.pop();//������ ������ ���� ����� ������ ������
						if (n == 1) {//������� ������
							bracket_c_cur = true;//����� ��������� ��-�����������  ������� ������
							bracket_c_sq = bracket_c_fig = false;//��������� ���� ������������� ������ ���������
						}
						if (n == 2) {//�������� ������
							bracket_c_fig = true;//����� ��������� ��-����������� �������� ������
							bracket_c_sq = bracket_c_cur = false;//��������� ���� ������������� ������ ���������

						}
						if (n == 3) {//���������� ������
							bracket_c_sq = true;//����� ��������� ��-�����������  ���������� ������
							bracket_c_cur = bracket_c_fig = false;//��������� ���� ������������� ������ ���������
						}
						pos.push(n);//���������� ����������� ������� � ����
						Q3.push(symb);//������� � ������� ��������������� �������
					}
					else Q3.push(symb);//������� � ������� ��������������� �������
				}
			}
			else call_error(Q3, 4);//���� ���,�� �������� ��������������� ������

		}
		if (fig_brckt_o(symb))//�������� ����������� ������
		{
			cout << ",which is a figure open bracket " << endl;
			bracket_c_fig = true;//����� ��������� ������������� �������� ������
			bracket_c_sq = bracket_c_cur = false;//��������� ���� ������������� ���-��� ���������
			pos.push(2);//������� � ���� ����� ������,������� �� ��������� ����� ������ ���� �������
			Q3.push(symb);//������� � ������� ��������������� �������
		}
		if (fig_brckt_c(symb))//�������� ����������� ������
		{
			cout << ",which is a figure close bracket" << endl;
			if (!bracket_c_fig&&bracket_c_cur) call_error(Q3, 1);//���� �� ������ ���� �� ������ ������ ������������� �������� ������,� ������ ������ �������,�� ������ ����-���������� ������
			if (!bracket_c_fig&&bracket_c_sq) call_error(Q3, 2);//���� �� ������ ���� �� ������ ������ ������������� �������� ������,� ������ ������ ����������,�� ������ ��-������������ �����
			if (pos.can_pop()) {//���� ��� ���� �������� ������ ������ ����
				n = pos.pop();//������,������ ����
				if (n == 2) {//���� ��������
					if (pos.can_pop()) {//���������,���� ��� �������� ������
						n = pos.pop();//������ ������ ���� ����� ������ ������
						if (n == 1) {//������� ������
							bracket_c_cur = true;//����� ��������� ��-�����������  ������� ������
							bracket_c_sq = bracket_c_fig = false;//��������� ���� ������������� ������ ���������
						}
						if (n == 2) {//�������� ������
							bracket_c_fig = true;//����� ��������� ��-����������� �������� ������
							bracket_c_sq = bracket_c_cur = false;//��������� ���� ������������� ������ ���������
						}
						if (n == 3) {//���������� ������
							bracket_c_sq = true;//����� ��������� ��-�����������  ���������� ������
							bracket_c_cur = bracket_c_fig = false;//��������� ���� ������������� ������ ���������
						}
						pos.push(n);//���������� ����������� ������� � ����
						Q3.push(symb);//������� � ������� ��������������� �������
					}
					else Q3.push(symb);//������� � ������� ��������������� �������
				}
			}
			else call_error(Q3, 4);//���� ���,�� �������� ��������������� ������

		}
		if (sq_brckt_o(symb))//���������� ����������� ������
		{
			cout << ",which is a square open bracket " << endl;
			bracket_c_sq = true;//����� ��������� �������������  ���������� ������
			bracket_c_cur = bracket_c_fig = false;//��������� ���� ������������� ������ ���������
			pos.push(3);//������� � ���� ����� ������,������� �� ��������� ����� ������ ���� �������
			Q3.push(symb);//������� � ������� ��������������� �������
		}
		if (sq_brckt_c(symb))//���������� ����������� ������
		{
			cout << ",which is a square close bracket" << endl;
			if (!bracket_c_sq&&bracket_c_fig) call_error(Q3, 3);//���� �� ������ ���� �� ������ ������ ������������� ���������� ������,� ������ ������ ��������,�� ������ ��-������������ ������
			if (!bracket_c_sq&&bracket_c_cur) call_error(Q3, 1);//���� �� ������ ���� �� ������ ������ ������������� ���������� ������,� ������ ������ �������,�� ������ ����-���������� �����
			if (pos.can_pop()) {//���� ��� ���� �������� ������ ������ ����
				n = pos.pop();//������,������ ����
				if (n == 3) {//���� ����������
					if (pos.can_pop()) {//���������,���� ��� �������� ������
						n = pos.pop();//������ ������ ���� ����� ������ ������
						if (n == 1) {//������� ������
							bracket_c_cur = true;//����� ��������� ��-�����������  ������� ������
							bracket_c_sq = bracket_c_fig = false;//��������� ���� ������������� ������ ���������
						}
						if (n == 2) {//�������� ������
							bracket_c_fig = true;//����� ��������� ��-����������� �������� ������
							bracket_c_sq = bracket_c_cur = false;//��������� ���� ������������� ������ ���������
						}
						if (n == 3) {//���������� ������
							bracket_c_sq = true;//����� ��������� ��-�����������  ���������� ������
							bracket_c_cur = bracket_c_fig = false;//��������� ���� ������������� ������ ���������
						}
						pos.push(n);//���������� ����������� ������� � ����
						Q3.push(symb);//������� � ������� ��������������� �������
					}
					else Q3.push(symb);//������� � ������� ��������������� �������
				}
			}
			else call_error(Q3, 4);//���� ���,�� �������� ��������������� ������

		}
	}
	if (pos.can_pop()) {//���� ���� ��� ������������� ������
		n = pos.pop();//������� �������
		if (n == 1) call_error(Q3, 5);//���� �������,�� ������� ��������������� ������
		if (n == 2) call_error(Q3, 6);//���� ��������,�� ������� ��������������� ������
		if (n == 3) call_error(Q3, 7);//���� ����������,�� ������� ��������������� ������
	}

}

void print_f(Queue & Q3) // ������� ����� 
{
	while (Q3.can_pop())
	{
		cout << Q3.pop();
	}
}
void main_txt(istream &fin, Stack & Q2) // �������,� ������� ���������� �������, �������� �� ������� ��������� ������� 
{
	Queue Q3;//������� ��� ������ ������
	char symb;
	fin >> symb;

	while (!(fin.eof())) {//���� �� ������ ����� �����
		Q2.push(symb);//��������� � ����
		Q3.push(symb);//��������� � �������
		fin >> symb;
	}
	Stack Q1;//������������� ���� ��� ������ � ������ �������
	cout << "Put the elements of the string on the stack:" << endl;//������� �������� ������ � ����: 
	while (Q2.can_pop())//���� ����� ����� �� �����
	{
		char a = Q2.pop();//����� �������
		cout << "   An item is placed on the stack [" << a << "]." << endl;//� ���� ������� ������� [" << a << "]. 
		Q1.push(a);//�������������� � ������ ����

	}
	cout << "The string read from the file: ";//��������� �� ����� ������ 
	print_f(Q3);//������� ������
	cout << endl;
	is_it_txt(Q1, Q3);//��������� �� �����
	cout << "This is the text!" << endl;//��� �����
	cout << "Source text: ";//�� ��� 
	print_f(Q3);//������� ������
}
int main()
{
	setlocale(0, "RUS");
	int answer;
	Stack Q2;
	menu();
	cin >> answer;
	switch (answer)
	{
	case 1:
	{
		char name[20];
		cout << "Enter the name of file" << endl;
		cin >> name;
		ifstream fin(name);
		system("cls");
		main_txt(fin, Q2);
		fin.close();
		break;
	}
	case 2:
	{
		system("cls");
		cout << "End of program!" << endl;
		system("pause");
		return 0;

	}

	default:
		system("cls");
		cout << "Incorrect input.Try again.";
		break;
	}
	cout << endl;
	system("pause");
}
