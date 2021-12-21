#include <iostream>
#include <string>
#include <exception>

// Задание 1:
class DivistionByZero : public std::exception {
	std::string m_what;
public:
	DivistionByZero(std::string what) noexcept
		: std::exception()
		, m_what(std::move(what))
	{}

	const char* what() const noexcept {
		return m_what.c_str();
	}
};

template<typename T, typename U>
auto divide(T&& nominator, U&& denominator) {
	if (denominator == 0)
		throw DivistionByZero("Divistion by Zero");
	return nominator / denominator;
}

// Задание 2:

class Ex
{
private:
	double m_x;
public:
	Ex(double x)
		:m_x(x)
	{

	}
	double getErr()
	{
		return m_x;
	}

};

class Bar
{
private:
	double m_y;
public:
	Bar(double y = 0)
	{

	}

	void set(double a)
	{
		if (m_y + a > 100) throw Ex(a * m_y);
		m_y = a;
	}

};

// Задание 3:

class OffTheField
{
public:
	OffTheField()
	{

	}

	std::string getErr()
	{
		std::string err = "The robot left the field!";
		return err;
	}

};

class IllegalCommand
{
public:
	IllegalCommand()
	{

	}

	std::string getErr()
	{
		std::string err = "Illegal command!";
		return err;
	}

};

class Robot
{
private:
	int m_x;
	int m_y;

	void checkCoordinates()
	{
		if (m_x < 1 || m_x > 10 || m_y < 1 || m_y > 10)
		{
			throw OffTheField();
		}
	}

public:
	Robot(int x = 1, int y = 1)
		:m_x(x), m_y(y)
	{
		checkCoordinates();
	}

	int getX()
	{
		return m_x;
	}

	int getY()
	{
		return m_y;
	}

	void move(char command)
	{

		switch (command)
		{
		case 'l':
			m_x--;
			break;

		case 'r':
			m_x++;
			break;

		case 'u':
			m_y++;
			break;

		case 'd':
			m_y--;
			break;

		default:
			throw IllegalCommand();
		}
		checkCoordinates();
	}

	friend std::ostream& operator<< (std::ostream& out, const Robot& r);
};

std::ostream& operator<<(std::ostream& out, const Robot& r)
{
	out << "X = " << r.m_x << ", Y = " << r.m_y;
	return out;
}

int main(int argc, char const* argv[])
{
	// Задание 1:

	std::cout << "Task 1." << std::endl;

	try {
		volatile int a = 2;
		int b = 3;
		std::cout << divide(a, b) << std::endl;

		std::cout << divide(std::move(a), b) << std::endl;

		std::cout << divide(3, 2) << std::endl;
		std::cout << divide(3.0, 2.0) << std::endl;
		std::cout << divide(1.0, 0.0) << std::endl;
	}
	catch (const DivistionByZero& e) {
		std::cerr << e.what() << std::endl;
	}

	std::cout << "--------------------------" << std::endl;

	// Задание 2:

	std::cout << "Task 2." << std::endl;

	double test;
	Bar bar;
	while (true)
	{
		try
		{
			std::cout << "Enter int: " << std::endl;
			std::cin >> test;
			if (test == 0) break;
			bar.set(test);
		}
		catch (Ex& err)
		{
			std::cout << "Exception: " << err.getErr() << std::endl;
			break;
		}
	}

	std::cout << "--------------------------" << std::endl;

	// Task 3

	std::cout << "Task 3." << std::endl;

	Robot robin;
	char command;
	while (command != 'q')
	{
		std::cout << "Coordinates of the robot: " << robin << std::endl;
		std::cout << "Enter the command: (l - left, r - right, u - up, d - down, q - exit)" << std::endl;
		std::cin >> command;
		try
		{
			robin.move(command);
		}
		catch (IllegalCommand& errCommand)
		{
			std::cout << errCommand.getErr() << std::endl;
			break;
		}

		catch (OffTheField& errField)
		{
			std::cout << errField.getErr() << std::endl;
			break;
		}
	}
	return 0;
}