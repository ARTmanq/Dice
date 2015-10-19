#include "stdafx.h"
#include "Dice.h"
#include <iostream>
using namespace std;


Dice::Dice()
{
	n = 0;
	dice = nullptr;
}

Dice::Dice(unsigned int n)
{
	unsigned int i;
	this->n = n;
	try{
		dice = new unsigned int[n];
	}
	catch(bad_alloc){
		delete[] dice;
		dice = nullptr;
		this->n = 0;
		throw(bad_alloc());
	}
	for (i = 0; i < n; i++){
		dice[i] = rand() % MAX + 1;
	}
}

Dice::Dice(unsigned int n, unsigned int d[])
{
	unsigned int i, j, m = n;
	for (i = m - 1; i > 0; i--){
		if ((d[i] < 1) || (d[i] > MAX)){
			d[i] = 0;
			m--;
		}
	}
	try{
		dice = new unsigned int[m];
	}
	catch (bad_alloc){
		delete[] dice;
		dice = nullptr;
		this->n = 0;
		throw(bad_alloc());
	}
	this->n = m;
	for (i = 0, j = 0; j < n; j++){
		if (d[j] != 0){
			dice[i] = d[j];
			i++;
		}
	}
}

Dice::Dice(const Dice &ob)
{
	unsigned int i;
	this->n = ob.n;
	this->dice = nullptr;
	if (n){
		try{
			this->dice = new unsigned int[n];
		}
		catch (bad_alloc){
			delete[] this->dice;
			this->dice = nullptr;
			this->n = 0;
			throw(bad_alloc());
		}
		for (i = 0; i < n; i++){
			this->dice[i] = ob.dice[i];
		}
	}
}

Dice::Dice(Dice &&ob)
{
	n = ob.n;
	this->dice = ob.dice;
	ob.dice = nullptr;
}

Dice & Dice::operator = (const Dice &ob)
{
	unsigned int i;
	if (this != &ob){
		delete[] dice;
		dice = nullptr;
		if ((n = ob.n) != 0){
			try{
				dice = new unsigned int[n];
			}
			catch (bad_alloc){
				delete[] dice;
				this->n = 0;
				dice = nullptr;
				throw(bad_alloc());
			}
			for (i = 0; i < n; i++){
				dice[i] = ob.dice[i];
			}
		}
	}
	return *this;
}

Dice & Dice::operator = (Dice &&ob)
{
	unsigned int tn = n;
	unsigned int *tptr = dice;
	n = ob.n;
	ob.n = tn;
	dice = ob.dice;
	ob.dice = tptr;
	return *this;
}

unsigned int Dice::getDice(unsigned int i) const
{
	if (i >= n){
		throw(out_of_range("------ This dice doesn\'t exist!!!"));
	}
	return dice[i];
}

ostream & operator << (ostream &s, const Dice &d)
{
	unsigned int i = 0, j, k, nn;
	s << endl;
	nn = d.getN();
	for (i = 0; i < nn;){
		for (k = 0; k < 3; k++){
			for (j = i; (j < (18 + i)) && (j < nn); j++){
				switch (k){
				case 0:{
					switch (d[j]){
					case 1:{
						s << "|   ";
						break;
					}
					case 2:{
						s << "|  *";
						break;
					}
					case 3:{
						s << "|  *";
						break;
					}
					case 4:{
						s << "|* *";
						break;
					}
					case 5:{
						s << "|* *";
						break;
					}
					case 6:{
						s << "|* *";
						break;
					}
					}
					break;
				}
				case 1:{
					switch (d[j]){
					case 1:{
						s << "| * ";
						break;
					}
					case 2:{
						s << "|   ";
						break;
					}
					case 3:{
						s << "| * ";
						break;
					}
					case 4:{
						s << "|   ";
						break;
					}
					case 5:{
						s << "| * ";
						break;
					}
					case 6:{
						s << "|* *";
						break;
					}
					}
					break;
				}
				case 2:{
					switch (d[j]){
					case 1:{
						s << "|   ";
						break;
					}
					case 2:{
						s << "|*  ";
						break;
					}
					case 3:{
						s << "|*  ";
						break;
					}
					case 4:{
						s << "|* *";
						break;
					}
					case 5:{
						s << "|* *";
						break;
					}
					case 6:{
						s << "|* *";
						break;
					}
					}
					break;
				}
				}
			}
			s << endl;
		}
		i += 18;
		s << endl;
	}
	return s;
}

void Dice::RollTheDice()
{
	unsigned int i;
	for (i = 0; i < n; i++){
		dice[i] = rand() % MAX + 1;
	}
}

Dice & Dice::operator += (unsigned int a)
{
	unsigned int *ptr, i;
	if ((a < 0) || (a > MAX)){
		throw(invalid_argument("------ Dice cannot have this value!!!"));
	}
	try{
		ptr = new unsigned int[n + 1];
	}
	catch(bad_alloc){
		delete[] ptr;
		ptr = nullptr;
		throw(bad_alloc());
	}
	for (i = 0; i < n; i++){
		ptr[i] = dice[i];
	}
	delete[] dice;
	ptr[n] = a;
	n++;
	dice = ptr;
	ptr = nullptr;
	return *this;
}

Dice & Dice::operator += (const Dice &c)
{
	unsigned int i, j, *ptr;
	try{
		ptr = new unsigned int[this->n + c.n];
	}
	catch (bad_alloc){
		delete[] ptr;
		ptr = nullptr;
		throw(bad_alloc());
	}
	for (i = 0; i < this->n; i++){
		ptr[i] = this->dice[i];
	}
	delete[] this->dice;
	for (i = this->n, j = 0; i < (this->n + c.n), j < c.n; i++, j++){
		ptr[i] = c.dice[j];
	}
	this->n = this->n + c.n;
	dice = ptr;
	ptr = nullptr;
	return *this;
}

Dice & Dice::operator -= (unsigned int a)
{
	unsigned int i, *ptr;
	if (a == 100){
		delete[] dice;
		dice = nullptr;
		n = 0;
	}
	else{
		if (a >= n){
			throw(invalid_argument("------ Dice with this number doesn\'t exist!!!"));
		}
		dice[a] = dice[n - 1];
		--n;
		try{
			ptr = new unsigned int[n];
		}
		catch (bad_alloc){
			delete[] ptr;
			ptr = nullptr;
			throw(bad_alloc());
		}
		for (i = 0; i < n; i++){
			ptr[i] = dice[i];
		}
		delete[] dice;
		dice = ptr;
		ptr = nullptr;
	}
	return *this;
}

Dice & Dice::operator -= (const Dice &c)
{
	int i, j;
	unsigned int *ptr;
	for (i = c.n - 1; i >= 0; i--){
		for (j = this->n - 1; j >= 0; j--){
			if (this->dice[j] == c[i]){
				this->dice[j] = this->dice[this->n - 1];
				this->dice[this->n - 1] = 0;
				this->n--;
				break;
			}
		}
	}
	try{
		ptr = new unsigned int[this->n];
	}
	catch (bad_alloc){
		delete[] ptr;
		ptr = nullptr;
		throw(bad_alloc());
	}
	for (i = 0; i < this->n; i++){
		ptr[i] = this->dice[i];
	}
	delete[] dice;
	dice = ptr;
	ptr = nullptr;
	return *this;
}

unsigned int Dice::operator [] (unsigned int a) const
{
	if (a >= n){
		throw(invalid_argument("------ Dice with this number doesn\'t exist!!!"));
	}
	return dice[a];
}

unsigned int & Dice::operator [] (unsigned int a)
{
	if (a >= n){
		throw(invalid_argument("------ Dice with this number doesn\'t exist!!!"));
	}
	return dice[a];
}

int Dice::sum() const
{
	unsigned int i, s = 0;
	for (i = 0; i < n; i++){
		s += dice[i];
	}
	return s;
}

int Dice::coincidence() const
{
	unsigned int i, j;
	if (n > MAX){
		return 1;
	}
	else{
		for (i = 0; i < n; i++){
			for (j = i + 1; j < n; j++){
				if ((dice[i] == dice[j]) && (i != j)){
					return 1;
				}
			}
		}
	}
	return 0;
}

