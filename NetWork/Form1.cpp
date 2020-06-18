#include "Form1.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace NetWork;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing::Drawing2D;
using namespace std;

int N, M;
int **coord;
int **net;

[STAThread]
void main(cli::array<System::String^>^ arg) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Form1 form; 
	Application::Run(%form);
}
void PrintMap(Form1 ^F);
void ReadFile();
void calc(int x, int y, Form1 ^F);
void Form1::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	ReadFile();
	PrintMap(this);
	button2->Visible = true;
	textBox1->Visible = true;
	textBox2->Visible = true;
}
void Form1::button2_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (textBox1->Text!=""&&textBox2->Text!="")
	calc(Convert::ToInt32(textBox1->Text), Convert::ToInt32(textBox2->Text),this);
	else MessageBox::Show("Заполнить поля!");
}

void ReadFile()
{
	int i = 0;
	string line;
	ifstream in("input.txt");
	if (in.is_open())
	{
		getline(in, line);
		N = atoi(line.c_str());
		coord = new int* [N];
		for (int count = 0; count < N; count++)
			coord[count] = new int[2];
		while ((i<N))
		{
			getline(in, line,' ');
			coord[i][0]= atoi(line.c_str());
			getline(in, line);
			coord[i][1] = atoi(line.c_str());
			i++;
		}
		getline(in, line);
		M = atoi(line.c_str());
		net = new int*[M];
		for (int count = 0; count <M; count++)
			net[count] = new int[2];
		i = 0;
		while ((i < M))
		{
			getline(in, line, ' ');
			net[i][0] = atoi(line.c_str());
			getline(in, line);
			net[i][ 1] = atoi(line.c_str());
			i++;
		}
	}
	in.close();
}

void PrintMap(Form1 ^F)
{
	int r = 40;
	Graphics ^g = F->map->CreateGraphics();
	Brush ^b = gcnew SolidBrush(Color::Purple);
	Pen ^p = gcnew Pen(b, 1);
	Pen ^p1 = gcnew Pen(Color::DarkBlue, 3);
	Font ^drawFont = gcnew Font("Arial", 16);
	SolidBrush ^drawBrush = gcnew SolidBrush(Color::Black);
	for (int i = 0; i < N; i++)
	{
		g->DrawEllipse(p, coord[i][0] - r / 2, coord[i][1] - r/2, r, r);
		g->DrawString(Convert::ToString(i), drawFont, drawBrush, coord[i][0] - 10, coord[i][1] - 10);
	}
		//Pen pen = new Pen(Color.DarkBlue, 8);
	for (int i = 0; i < M; i++)
	{
		g->DrawLine(p1, coord[net[i][0]][0], coord[net[i][0]][1], coord[net[i][1]][ 0], coord[net[i][1]][1]);
	}

}

int **arr(int **mas,int l)
{
	int **MyArray = new int*[l];
	for (int count = 0; count < l; count++)
		MyArray[count] = new int[l];
	int inf = 20000000;
	for (int i = 0; i < l; i++)
		for (int j = 0; j < l; j++)
			MyArray[i][j] = inf;
	for (int i = 0; i < l; i++)
	{
		MyArray[mas[i][0]][mas[i][1]] = 1;
		MyArray[mas[i][1]][mas[i][0]] = 1;
	}
	return MyArray;
}
//void matr(int l, int **MyArray, Form1 ^f)
//{
//	for (int k = 0;k < l;k++)
//		for (int i = 0; i < l; i++)
//			for (int j = 0; j < l; j++)
//			{
//				if (i == j) MyArray[i][j] = 0;
//				else
//					MyArray[i][j] = Math::Min(MyArray[i][j], MyArray[i][k] + MyArray[k][j]);
//			}
//
//	for (int i = 0; i < l; i++)
//		for (int j = 0; j < l; j++)
//		{
//			if (MyArray[i][j]== 20000000) MyArray[i][j] = 0;
//		}
//	f->dataGridView1->Columns->Clear();
//	f->dataGridView1->Rows->Clear();
//	for (int k = 0;k <l;k++)
//		f->dataGridView1->Columns->Add(Convert::ToString(k), Convert::ToString(k));
//	for (int k = 0;k <l;k++)
//		f->dataGridView1->Rows->Add();
//	for (int i = 0; (i <= (f->dataGridView1->Rows->Count - 1)); i++)
//	{
//		f->dataGridView1->Rows[i]->HeaderCell->Value = Convert::ToString(i);
//	}
//	for (int i = 0; i < l; i++)
//	{
//
//		for (int j = 0; j < l; j++)
//		{
//			f->dataGridView1->Rows[j]->Cells[i]->Value = Convert::ToString(MyArray[i][j]);
//		}
//	}
//}
//int **delrowcol(int x,int l,int **mas, int **net_t)
//{
//	int c = 0,j=0;	
//	for (int i = 0;i < l;i++)
//	{
//		if (mas[i][0] == x || mas[i][1] == x)
//			c++;
//	}
//	net_t = new int*[l];
//	for (int count = 0; count < l ; count++)
//		net_t[count] = new int[2];
//	for (int i = 0;i < l;i++)
//	{
//		if (mas[i][0] != x && mas[i][1] != x)
//		{
//			if (mas[i][0]>x)
//			net_t[j][0] = mas[i][0]-1;
//			else
//				net_t[j][0] = mas[i][0];
//			if (mas[i][1] > x)
//			net_t[j][1] = mas[i][1]-1;
//			else
//				net_t[j][1] = mas[i][1];
//			j++;
//		}
//	}
//	for (int i = j;i < l;i++)
//	{
//		net_t[i][0] = 0;
//		net_t[i][1] = 0;
//	}
//	return net_t;
//}
bool check(int x,int y, int t,int **arr,bool *ch)
{
	if (t == x)
		return true;
	for (int i = 0; i < M; i++)
	{
		if (ch[i]!=true)
		if (i!=y)
		if (arr[t][i] == 1)
		{
			ch[i] = true;
			if (check(x, y, i, arr, ch))
			{
				return true;
			}
		}
	}
	return false;
}
void calc(int x, int y, Form1 ^f)
{
	System::String ^line = "",^line1="";
	int temp=0;
	int l = 0;
	int **MyArray;
	MyArray = arr(net, M);
	 f->label1->Text = "";
	if (MyArray[x][y] != 1 || MyArray[x][y] != 0)
	{
		for (int i = 0; i < M; i++)
		{
			if (i!=x)
			if (MyArray[y][i] == 1)
			{
				if (check(x, y, i, MyArray, new bool[M]))
				{
					temp++;
					line+= " Вершина № "+Convert::ToString(i) ;
				}

			}

		}
	}
	if (MyArray[y][x] != 1 || MyArray[y][x] != 0)
	{
		for (int i = 0; i < M; i++)
		{
			if (i != y)
				if (MyArray[x][i] == 1)
				{
					if (check(y, x, i, MyArray, new bool[M]))
					{
						l++;
						line1+= " Вершина № "+Convert::ToString(i) ;
					}

				}

		}
	}
	if (temp<l)
	f->label1->Text ="Всего: "+ Convert::ToString(temp) +line;
	else
		f->label1->Text = "Всего: " + Convert::ToString(l) + line1;

}
