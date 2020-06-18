#include "Form1.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace NetWork;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing::Drawing2D;
using namespace std;

int N, M;//размер массива координат узлов - размер массива ребер
int **coord;//координаты
int **net;//ребра

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

void ReadFile()//чтение входных данных из файла
{
	int i = 0;
	string line;
	ifstream in("input.txt");
	if (in.is_open())
	{
		getline(in, line);//первая строка содержит количество узлов
		N = atoi(line.c_str()); //приводим к int
		coord = new int* [N];//объявляем двумерный динамический массив
		for (int count = 0; count < N; count++)
			coord[count] = new int[2];
		while ((i<N))//пока не считаем все узлы
		{
			getline(in, line,' ');//считываем строку до пробела
			coord[i][0]= atoi(line.c_str());//координата х
			getline(in, line);//считываем оставшуюся строку
			coord[i][1] = atoi(line.c_str());//координата у
			i++;
		}
		getline(in, line);//считываем количество ребер
		M = atoi(line.c_str());//приводим к int
		net = new int*[M];//объявляем двумерный динамический массив
		for (int count = 0; count <M; count++)
			net[count] = new int[2];
		i = 0;
		while ((i < M))//пока не считаем все ребра
		{
			getline(in, line, ' ');//считываем строку до пробела
			net[i][0] = atoi(line.c_str());//откуда
			getline(in, line);//считываем оставшуюся строку
			net[i][ 1] = atoi(line.c_str());//куда
			i++;
		}
	}
	in.close();//закрываем файл
}

void PrintMap(Form1 ^F)//отображение сети на экране
{
	int r = 40;//радиус кругов
	Graphics ^g = F->map->CreateGraphics();//область рисования, рисуем на панели
	Brush ^b = gcnew SolidBrush(Color::Purple);//задаем кисть 
	Pen ^p = gcnew Pen(b, 1);//задаем карандаш с толщиной 1 для рисования кругов
	Pen ^p1 = gcnew Pen(Color::DarkBlue, 3);//задаем карандаш с толщиной 3 для рисования линий
	Font ^drawFont = gcnew Font("Arial", 16);//задаем шрифт для надписей
	SolidBrush ^drawBrush = gcnew SolidBrush(Color::Black);//кисть для надписей
	for (int i = 0; i < N; i++)
	{
		g->DrawEllipse(p, coord[i][0] - r / 2, coord[i][1] - r/2, r, r);//рисуем круг coord[i][0] - r / 2, coord[i][1] - r/2 - координаты верхнего левого угла
		g->DrawString(Convert::ToString(i), drawFont, drawBrush, coord[i][0] - 10, coord[i][1] - 10);//рисуем надпись примерно в центре круга
	}
		//Pen pen = new Pen(Color.DarkBlue, 8);
	for (int i = 0; i < M; i++)
	{
		g->DrawLine(p1, coord[net[i][0]][0], coord[net[i][0]][1], coord[net[i][1]][ 0], coord[net[i][1]][1]);//рисуем ребра
	}

}

int **arr(int **mas,int l)//матрица расстояний
{
	//mas -  содержит информацию о ребрах 
	int **MyArray = new int*[l];//объявляем двумерный массив
	for (int count = 0; count < l; count++)
		MyArray[count] = new int[l];
	int inf = 20000000;//задаем большое число и заполняем им матрицу
	//в принципе можно заполнить нулями
	//но матрицу минимальных расстояний между всеми узлами мы получали в функции matr 
	//как потом показала жизнь она не нужна
	for (int i = 0; i < l; i++)
		for (int j = 0; j < l; j++)
			MyArray[i][j] = inf;
	for (int i = 0; i < l; i++)//заполняем согласно заданных ребер
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
/*
x - первый узел который задал пользователь
y - второй узел который задал пользователь
t - текущий узел
arr - матрица расстояний
ch - массив, по которому мы проверяем были в этом узле или нет
без него рекурсия станет бесконечной
*/
bool check(int x,int y, int t,int **arr,bool *ch)
{
	if (t == x)//если мы нашли узел x возвращаем истину
		return true;
	for (int i = 0; i < N; i++)//проверяем все узлы
	{
		if (ch[i]!=true)//если мы его еще не проверяли
		if (i!=y)//если он не равен заданному вторым
		if (arr[t][i] == 1)//если расстояние от текущего до него равно 1
		{
			ch[i] = true;//побывали
			if (check(x, y, i, arr, ch))//определяем есть ли у него связь с узлом x
			{
				return true; //если да, возвращаем истину
			}
			//иначе продолжаем проверять
		}
	}
	return false; // если не найдена связь возвращаем ложь
}
/*
x - первый узел который задал пользователь
y - второй узел который задал пользователь
f - указатель на форму
*/
void calc(int x, int y, Form1 ^f)
{
	System::String ^line = "",^line1="";
	int temp=0;
	int l = 0;
	int **MyArray;//объвляем матрицу расстояний
	MyArray = arr(net, N);//получаем значения (передаем массив ребер и количество узлов)
	 f->label1->Text = "";//метку очищаем
	if (MyArray[x][y] != 1 && MyArray[x][y] != 0)//если x!=y и расстояние между ними не равно 1
	{
		for (int i = 0; i < N; i++)
		{
			if (i!=x)//если текущий не равен первому узлу
			if (MyArray[y][i] == 1)//расстояние между вторым узлом и текущим равно 1
			{
				if (check(x, y, i, MyArray, new bool[N]))//передаем первый, второй, текущий и массив bool
				{
					temp++;//увеличиваем количество узлов
					line+= " Узел № "+Convert::ToString(i) ;//записываем имя узла
				}

			}

		}
	}
	if (MyArray[y][x] != 1 && MyArray[y][x] != 0)//если x!=y и расстояние между ними не равно 1
	{
		for (int i = 0; i < N; i++)
		{
			if (i != y)//если текущий не равен второму узлу
				if (MyArray[x][i] == 1)// расстояние между первым узлом и текущим равно 1
				{
					if (check(y, x, i, MyArray, new bool[N])) // передаем  второй, первый, текущий и массив bool
					{
						l++;//увеличиваем количество узлов
						line1+= " Узел № "+Convert::ToString(i) ;//записываем имя узла
					}

				}

		}
	}
	//проверяем с какой строны путь короче
	if (temp<l) 
	f->label1->Text ="Всего: "+ Convert::ToString(temp) +line;
	else
		f->label1->Text = "Всего: " + Convert::ToString(l) + line1;

}
