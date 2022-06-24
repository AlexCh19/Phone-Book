#include <iostream>
#include<regex>
#include<string>
#pragma warning(disable:4996)

using namespace std;

struct stud //база студентов
{
	char* name;
	string email;
	string phone;
};

struct sol
{
	char* name;
	string email;
	string phone;
};

//удаление по индексу
//получает массив, его размер (по ссылке), индекс удаляемого элемента
void DelIndex(stud*& group, int& size, int index)
{
	stud* temp = new stud[size - 1];//создали новый массив
	for (int i = 0; i < size; i++)//перебираем все элементы
	{
		if (i < index)//если номер текущего меньше индекса
			temp[i] = group[i];//копируем как есть
		else if (i > index)//если больше
			temp[i - 1] = group[i];//копируем со смещением
	}
	delete[] group[index].name;//зачищаем имя удаленного
	delete[] group;//удаляем старый массив
	group = temp;//укахатель получает адрес нового
	size--;//размер - 1

}

bool isCorrectEmail(stud*& group, int& size, const string& email)//проверка на правилность записи имейла
{
	regex re("(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$)");
	return regex_search(group[size].email, re);
}

bool isCorrectPhoneNumber(stud*& group, int& size, const string& phone)
{
	regex re("(^[0-9]{10})");//формат записи номера без международного значения Ex.0631111111
	//[символы, которые Вам необходимы]{общее кол-во символов}
	return regex_search(group[size].phone, re);
}


//фунция добавления студнетов в динамический массив экземпляров структур
//принимает указатель на массив и размер массива (по ссылке)
void Add(stud*& group, int& size)
{
	char t[100];//временная строка
	stud* temp = new stud[size + 1];//временный массив
	for (int i = 0; i < size; i++)//в цикле перебираем все элементы
		temp[i] = group[i];//копируем из старого массива в новый
	delete[] group;//удаляем старый массив
	group = temp;//указатель получает адрес нового
	cin.ignore();//очистка текстового буфера перед вводом текстовой информации

	cout << "Enter name\n"; cin.getline(t, 100);//запросили имя во временную строку
	group[size].name = new char[strlen(t) + 1];//выделили память под имя
	strcpy(group[size].name, t);//скопировали в эту память имя
	//имейл и номер телефона
	cout << "Enter your e-mail\n"; cin >> group[size].email;
	cout << "Enter your phone\n"; cin >> group[size].phone;
	if (isCorrectEmail(group, size, group[size].email))
		cout << "The e-mail is correct\n";
	else
		cout << "The e-mail is invalid! Please, input valid mail!\n";
	if (isCorrectPhoneNumber(group, size, group[size].phone))
		cout << "The phone number is correct\n";
	else
		cout << "The phone number is invalid! Please, input valid number!\n";
	size++;
}

void Sort_by_Alpha(stud* group, int size)//сортировка по алфавиту
{
	for (int i = 0; i < size; i++)
		for (int j = i + 1; j < size; j++)
			if (strcmp(group[i].name, group[j].name) > 0)
				swap(group[i], group[j]);
}


void Show(stud* group, int size)//вывод на экран
{
	cout << "#\tName\t\tEmail\t\t\t\tPhone Num\n";
	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << "\t" << group[i].name << "\t\t" << group[i].email << "\t\t";
		cout << group[i].phone << "\n";
	}
}

void Show_fav(sol* favorite, int s_size)//вывод на экран избранных пользователей
{
	cout << "#\tName\t\tEmail\t\t\t\tPhone Num\n";
	for (int i = 0; i < s_size; i++)
		cout << i + 1 << "\t" << favorite[i].name << "\t\t" << favorite[i].email << "\t" << favorite[i].phone << "\n";
}

//поиск по имени. Ввозвращает индекс найденного элемемнта или -1, если такого нет
int Search(stud* group, int size)
{
	char temp[100];//временная строка
	cin.ignore();//очистили буфер
	//запросили имя
	cout << "Enter name for search\n"; cin.getline(temp, 100);
	for (int i = 0; i < size; i++)//перебираем все элемемнты массива
	{
		//если есть совпадения по имени
		if (!strcmp(group[i].name, temp))
			return i;//возвращаем номер
	}
	//если мы дошли до этой строки - значит такого элемемнта нет
	return -1;//вернемм - 1
}

//удаление по имени
void DelName(stud*& group, int& size)
{
	//запишем в индекс результат, который вернет функция поиска по имени
	int index = Search(group, size);
	if (index == -1)//если индекс = -1
		cout << "I cant find it\n";//скажем, что не можем найти
	else//иначе - передаим масси, размер и индекс в функцию удаления по индексу
		DelIndex(group, size, index);
}

//функция редактирования
void Edit(stud* group, int size)
{
	int index, field;//индекс редактируемого и поле
	char temp[100];//временная строка
	//запросили индекс
	cout << "Enter name's index to edit\n";
	cin >> index;
	index--;//приведи его в нормальное состония
	if (index < 0 || index > size - 1)//если индекс неправильный
		cout << "Wrong index\n";//выведем сообщение
	else//иначе
	{
		//запросим поле для редактирования
		cout << "Enter field for edit\n1-Name\n2-Email\n3-Phone number\n";
		cin >> field;
		//если поле - неправильное 
		if (field < 1 || field > 3)
			cout << "Wrong field\n";//выведем сообщение
		else
		{
			//иначе
			switch (field)
			{
			case 1:
				cin.ignore();//очистка буфера
				//запросили имя во временную строку
				cout << "Enter new name\n"; cin.getline(temp, 100);
				delete[] group[index].name;//удаляем старое имя
				group[index].name = new char[strlen(temp) + 1];//выделяем место под новое
				strcpy(group[index].name, temp);//копируем новое имя
				break;
				//меняем имейл и телефон
			case 2:cout << "Enter new email\n"; cin >> group[index].email; break;
			case 3:cout << "Enter new phone number\n"; cin >> group[index].phone; break;
			}
		}
	}
}

//функция, которая перебирает всех людей и по выбору админа(или другого чел-ка) сортирует в избранных
//получает массив людей, его размер
//все - по ссылке
void Favorite(stud*& group, int& size, sol*& favorite, int& s_size)
{
	int index = Search(group, size);
	if (index == -1)//если индекс = -1
		cout << "I cant find it\n";//скажем, что не можем найти
	else {
		s_size++;
	}

	favorite = new sol[s_size];

	int k = 0;

	if (index == -1) {
		cout << "!\n";
	}
	else {
		favorite[k].name = new char[strlen(group[index].name) + 1];
		strcpy(favorite[k].name, group[index].name);
		favorite[k].email = group[index].email;
		favorite[k].phone = group[index].phone;
		DelIndex(group, size, index);
		k++;
	}
}

void Write(stud*& group, int size, char* filename, int mode)
{
	FILE* file;//создали поток для записи
	char buff[100];//временная строка
	//если режим записи == 1
	if (mode == 1) file = fopen(filename, "w");//открываем поток для записи
	else file = fopen(filename, "a");//если 2 - открываем поток для дозаписи

	//перебираем все элементы массива
	for (int i = 0; i < size; i++)
	{
		fputs(group[i].name, file);//имя запишем просто так
		fputc(';', file);//поставим разделитель
		sprintf(buff, "%s", group[i].email);//преобразуем в строку email
		fputs(buff, file);//запишем в файл
		fputc(';', file);//поставим разделитель
		sprintf(buff, "%s", group[i].phone);//преобразуем в строку phone number
		fputs(buff, file);//запишем в файл
		fputc('\n', file);//поставим разделитель 
	}
	fclose(file);//закрываем поток
}

void Read(stud*& group, int& size, char* filename)
{
	char buff[100];//временная строка
	int counter = 0;//счетчик строк в файле
	char* t;//временный указатель на часть стоки
	FILE* file = fopen(filename, "r");//создаем поток, привязываем к файлу
	if (!file) cout << "File not open\n";//если поток не создан-выводим сообщение
	else//иначе
	{
		//считываем из файла строку за строкой
		while (fgets(buff, 100, file))
			counter++;//счетчик строк + 1
		rewind(file);//возвращаем курсор в начало файла
		//создаем новый массив размером существующий массив + кол-во
		//строк в файле
		stud* temp = new stud[size + counter];
		//в цикле перебираем все строки в существующем массиве
		for (int i = 0; i < size; i++)
			temp[i] = group[i];//копируем их в новый массив
		delete[] group;//удаляем старый массив
		group = temp;//указатель получает адрес нового массива

		//дозаполняем массив из файла
		for (int i = size; i < size + counter; i++)
		{
			fgets(buff, 100, file);//вычитываем строку
			t = strtok(buff, ";");//в указатель запишем слово до разделитель(имя)
			group[i].name = new char[strlen(t) + 1];//выделяем под имя место
			strcpy(group[i].name, t);//копируем имя в эту память
			t = strtok(NULL, ";");//запишем в указатель следующее слово до
			//разделителя (возраст)
			group[i].email = t;//запишем данные в поле возраст 
			//с предварительным преобразование к целому
			t = strtok(NULL, ";");//вычитаем следующее слово до разделителя (вес)
			group[i].phone = t;//запишем в поле с предвартельным преобразованием
			//к float
		}
		size += counter;//изменим размер массива
		fclose(file);//закроем поток
	}
}

int main()
{
	stud* group = nullptr;
	int size = 0;
	sol* favorite = nullptr;
	int s_size = 0;
	int choice;
	bool job = 1;
	char filename[100];
	int mode;
	int index;
	while (job)
	{
		if (size == 0)
		{
			cout << "Enter choice\n1-Add\n2-Read\n0-Exit\n";
			cin >> choice;
			if (choice == 1)Add(group, size);
			else if (choice == 0)job = 0;
			else if (choice == 2) {
				cin.ignore();
				cout << "Enter filename\n"; cin.getline(filename, 100);
				Read(group, size, filename);
			}
			else cout << "Wrong choice\n";
		}
		else
		{
			cout << "Enter choice\n1-Add\n2-Show\n3-Sort by Alphabet\n";
			cout << "4-Search\n5-DelName\n6-Edit\n7-Sort favorites\n8-Show_fav\n9-Write\n10-Read\n";
			cout << "0-Exit\n";
			cin >> choice;
			switch (choice)
			{
			case 1: Add(group, size); break;
			case 2: Show(group, size); break;
			case 3:Sort_by_Alpha(group, size); break;
				cout << "Enter index\n"; cin >> index;
				index--;
				if (index < 0 || index > size - 1)
					cout << "Wrong index\n";
				else
					DelIndex(group, size, index);
				break;
			case 4:
				//в индекс записываем результат работы функции поиска
				index = Search(group, size);
				if (index == -1)//если он равен - 1
					cout << "I cant find it\n";//выведем сообщение
				else
					//иначе выведем номер в списке найденного человека 
					cout << "I find it in " << index + 1 << " position\n";
				break;
			case 5: DelName(group, size); break;
			case 6: Edit(group, size); break;
			case 7: Favorite(group, size, favorite, s_size); break;
			case 8: Show_fav(favorite, s_size); break;
			case 9:
				cin.ignore();
				cout << "Enter filename\n"; cin.getline(filename, 100);
				cout << "Enter write mode\n1-Write\n2-Add\n"; cin >> mode;
				if (mode < 1 || mode > 2) cout << "Wrong mode\n";
				else Write(group, size, filename, mode);
				break;
			case 10:
				cin.ignore();
				cout << "Enter filename\n"; cin.getline(filename, 100);
				Read(group, size, filename); break;
			case 0: job = 0; break;
			default:cout << "Wrong choice\n"; break;
			}
		}
	}

	for (int i = 0; i < size; i++)
		delete[] group[i].name;
	for (int i = 0; i < s_size; i++)
		delete[] favorite[i].name;
}
