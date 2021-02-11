#pragma once
#include <string>
#include <iostream>

namespace Accs {

	template <class T>
	double getNum(T& a) {
		std::cin >> a;
		while (!std::cin.good()) {
			std::cin.clear();
			std::cout << "Invalid input, try again: \n";
			std::cin.ignore(INT_MAX, '\n'); //std::numeric_limits<std::streamsize>::max()
			std::cin.clear();
			std::cin >> a;
		}
		return a;
	}

	typedef struct date {
		int day;
		int month;
		int year;

		date(int d = 0, int m = 0, int y = 0) : day(d), month(m), year(y) {};

		friend std::ostream& operator << (std::ostream& out, const date& d) {
			out << d.day << "." << d.month << "." << d.year;
			return out;
		}

		friend std::istream& operator >> (std::istream& in, date& d) {
			std::cout << "Enter the day : " << std::endl;
			in >> d.day;
			std::cout << "Enter the month : " << std::endl;
			in >> d.month;
			std::cout << "Enter the year : " << std::endl;
			in >> d.year;

			return in;
		}

		friend bool operator <(date& a, date& d) {
			if (a.year < d.year) {
				return true;
			} if (a.year > d.year)
			{
				return false;
			}
			if (a.month < d.month) {
				return true;
			} if (a.month > d.month)
			{
				return false;
			}
			if (a.day < d.day) {
				return true;
			}
			return false;
		}

		friend bool operator == (date& a, date& d) {
			if ((a.day == d.day) && (a.month == d.month) && (a.year == d.year)) {
				return true;
			}
			return false;
		}
	};

	class Deposit {
	protected:
		double sum;
		date open_date;
		double percent;

		virtual std::ostream& getInfo(std::ostream&) const = 0;
		virtual std::istream& inputInfo(std::istream&) = 0;

	public:
		Deposit(double sum0 = 0, date open_date0 = date(), double percent0 = 0);
		// для тестов
		date get_open_date() const {
			return open_date;
		}
		double get_percent() const {
			return percent;
		}
		//
		friend std::ostream& operator<< (std::ostream&, const Deposit&);
		friend std::istream& operator>> (std::istream&, Deposit&);

		virtual date getLast() const = 0; //дата последней операции
		double getSum() const { return sum; } //получить сумму
		double income(const Deposit& dep, const date& curr_date) const;//рассчитать величину начислений 
		date getOpen() const { return open_date; } //дата открытия

		virtual Deposit* copy() const = 0;
	};

	class commonDeposit : public Deposit {
	private:
		date last_date;
	protected:
		virtual std::ostream& getInfo(std::ostream&) const;
		virtual std::istream& inputInfo(std::istream&);
	public:
		commonDeposit(double sum0 = 0, date open_date0 = date(), 
					  double percent0 = 0, date last_date0 = date());
		// для тестов
		date get_last_date() const {
			return last_date;
		}
		//
		void changeSum(const double sum0, const date& curr_date);
		void changeLast(const date& curr_date);
		virtual date getLast() const;
		virtual commonDeposit* copy() const {return new commonDeposit(*this);}
	};

	class termDeposit : public Deposit { //срочный
	private:
		int storage_term;
	protected:
		virtual std::ostream& getInfo(std::ostream&) const;
		virtual std::istream& inputInfo(std::istream&);
	public:
		int getTerm() const { return storage_term; }
		termDeposit(double sum0 = 0, date open_date0 = date(),
					double percent0 = 0, int storage_term0 = 0);

		virtual date getLast() const;
		virtual termDeposit* copy() const { return new termDeposit(*this); }
	};

	class currDeposit : public Deposit { //валютный
	private:
		int curr; //название валюты
		date last_date;
		int exchangeRate; //курс обмена
	protected:
		virtual std::ostream& getInfo(std::ostream&) const;
		virtual std::istream& inputInfo(std::istream&);
	public:
		//для тестов
		int get_curr() const {
			return curr;
		}
		double get_rate() const {
			return exchangeRate;
		}
		currDeposit(double sum0 = 0, date open_date0 = date(), 
					double percent0 = 0, int curr0 = 1, 
					date last_date0 = date(), double exchangeRate = 1.0);

		void changeSum(const double sum0, const date& curr_date);
		void changeLast(const date& curr_date);
		virtual date getLast() const;
		virtual currDeposit* copy() const { return new currDeposit(*this); }

		double convertRub();

	};
}
