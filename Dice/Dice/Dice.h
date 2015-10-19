#include <iostream>
using namespace std;

class Dice
{
private:
	static const int MAX = 6;
	unsigned int n;
	unsigned int *dice;
public:
	Dice();
	Dice(unsigned int);
	Dice(unsigned int, unsigned int []);
	Dice(const Dice &);
	Dice(Dice &&);
	virtual ~Dice() { delete[] dice; };
	Dice & operator = (const Dice &);
	Dice & operator = (Dice &&);
	unsigned int getN() const { return n; }
	unsigned int getDice(unsigned int i) const;
	friend ostream & operator << (ostream &, const Dice &);
	void RollTheDice();
	Dice & operator += (unsigned int);
	Dice & operator += (const Dice &);
	Dice & operator -= (unsigned int);
	Dice & operator -= (const Dice &);
	unsigned int operator [] (unsigned int) const;
	unsigned int & operator [] (unsigned int);
	int sum() const;
	int coincidence() const;
};