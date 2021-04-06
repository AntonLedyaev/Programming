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
	cout << "������� �������� ������������ �����: ";
	cin >> filename;

	ifstream in(filename);
	if (!in)
	{
		cout << ">>> ���������� ������� ����.";
		return 0;
	}


	int size;
	in >> size;

	vector <double> height(size);
	vector <double> weight(size);

	for (int i = 0; i < size; i++)
		in >> height[i] >> weight[i];

	in.close();


	cout << "������� �������� ������������� �����: ";
	cin >> filename;

	ofstream out(filename);
	if (!out)
	{
		cout << ">>> ���������� ������� ����.";
		return 0;
	}


	double Mx = expected_value(height),
		My = expected_value(weight),
		Sx = standart_deviation(height),
		Sy = standart_deviation(weight),
		R = correlation_coefficient(height, weight);


	cout << "\n��������� �������� X = " << Mx << endl <<
		"��������� �������� Y = " << My << endl <<
		"����������� ���������� X = " << Sx << endl <<
		"����������� ���������� Y = " << Sy << endl <<
		"����������� ���������� = " << R << endl;

	out << "��������� �������� X = " << Mx << endl <<
		"��������� �������� Y = " << My << endl <<
		"����������� ���������� X = " << Sx << endl <<
		"����������� ���������� Y = " << Sy << endl <<
		"����������� ���������� = " << R << endl;


	if (R < 0.5)
	{
		cout << ">>> ��� �������� �����������.";
		out << ">>> ��� �������� �����������.";
	}
	else
	{
		vector <double> coefs = linear_regression(height, weight);
		double a = coefs[0], b = coefs[1];

		cout << "\n��������� ���������: y = " << a << " * x + " << b << endl;
		out << "��������� ���������: y = " << a << " * x + " << b;


		char choice;
		double value;

		while (1)
		{
			cout << "\n\����� :\n1) ���� => ���\n2) ��� => ����\n3) �����\n��� ����� : ";
			cin >> choice;

			if (choice == '1')
			{
				cout << "\n������� ����:  ";
				cin >> value;
				cout << "��� = " << a * value + b;
			}

			else if (choice == '2')
			{
				cout << "\n������� ���:  ";
				cin >> value;
				cout << "���� = " << (value - b) / a;
			}

			else if (choice == '3')
				break;

			else
				cout << ">>> ������. ���������� ��� ���\n";
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


