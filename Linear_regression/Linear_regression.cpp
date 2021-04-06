#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;


double expected_value(const vector<double>&);
double standart_deviation(const vector<double>&);
double correlation_coefficient(const vector<double>&, const vector<double>&);
vector<double> linear_regression(const vector<double>&, const vector<double>&);


int main()
{
    setlocale(LC_ALL, "Russian");
	string filename;
	cout << "Введите название считываемого файла: ";
	cin >> filename;

	ifstream in(filename);
	if (!in)
	{
		cout << ">>> Невозможно открыть файл.";
		return 0;
	}


	int size;
	in >> size;

	vector <double> height(size);
	vector <double> weight(size);

	for (int i = 0; i < size; i++)
		in >> height[i] >> weight[i];

	in.close();


	cout << "Введите название записываемого файла: ";
	cin >> filename;

	ofstream out(filename);
	if (!out)
	{
		cout << ">>> Невозможно открыть файл.";
		return 0;
	}


	double Mx = expected_value(height),
		My = expected_value(weight),
		Sx = standart_deviation(height),
		Sy = standart_deviation(weight),
		R = correlation_coefficient(height, weight);


	cout << "\nОжидаемое значение X = " << Mx << endl <<
		"Ожидаемое значение Y = " << My << endl <<
		"Стандартное отклонение X = " << Sx << endl <<
		"Стандартное отклонение Y = " << Sy << endl <<
		"Коэффициент корреляции = " << R << endl;

	out << "Ожидаемое значение X = " << Mx << endl <<
		"Ожидаемое значение Y = " << My << endl <<
		"Стандартное отклонение X = " << Sx << endl <<
		"Стандартное отклонение Y = " << Sy << endl <<
		"Коэффициент корреляции = " << R << endl;


	if (R < 0.5)
	{
		cout << ">>> Нет линейной зависимости.";
		out << ">>> Нет линейной зависимости.";
	}
	else
	{
		vector <double> coefs = linear_regression(height, weight);
		double a = coefs[0], b = coefs[1];

		cout << "\nУравнение регрессии: y = " << a << " * x + " << b << endl;
		out << "Уравнение регрессии: y = " << a << " * x + " << b;


		char choice;
		double value;

		while (1)
		{
			cout << "\n\Опции :\n1) Рост => Вес\n2) Вес => Рост\n3) Выход\nВаш выбор : ";
			cin >> choice;

			if (choice == '1')
			{
				cout << "\nВведите рост:  ";
				cin >> value;
				cout << "Вес = " << a * value + b;
			}

			else if (choice == '2')
			{
				cout << "\nВведите вес:  ";
				cin >> value;
				cout << "Рост = " << (value - b) / a;
			}

			else if (choice == '3')
				break;

			else
				cout << ">>> Ошибка. Попробуйте еще раз\n";
		}
	}

	out.close();
	return 0;
}

double expected_value(const vector<double>& arr)
{
	double sum = 0;
	for (unsigned int i = 0; i < arr.size(); i++)
		sum += arr[i];
	return sum / arr.size();
}


double standart_deviation(const vector<double>& arr)
{
	double sum = 0, M = expected_value(arr);
	for (unsigned int i = 0; i < arr.size(); i++)
		sum += (arr[i] - M) * (arr[i] - M);

	return sqrt(sum / arr.size());
}


double correlation_coefficient(const vector<double>& X, const vector<double>& Y)
{
	double sum = 0,
		Mx = expected_value(X),
		My = expected_value(Y),
		Sx = standart_deviation(X),
		Sy = standart_deviation(Y);

	for (unsigned int i = 0; i < X.size(); i++)
		sum += (X[i] - Mx) * (Y[i] - My);

	return sum / (X.size() * Sx * Sy);
}


vector <double> linear_regression(const vector<double>& X, const vector<double>& Y)
{
	double
		Mx = expected_value(X),
		My = expected_value(Y),
		Sx = standart_deviation(X),
		Sy = standart_deviation(Y),
		R = correlation_coefficient(X, Y);

	return vector <double> {Sy / Sx * R, My - Sy / Sx * R * Mx};
}


