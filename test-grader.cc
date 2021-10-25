/**
 *   @file: test-grader.cc
 * @author: Brody Reynolds
 *   @date: 10/23/2021
 *  @brief: A program that returns a students grade and average grade
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cctype>

using namespace std;

///function prototypes

/**
 * getGrade - finds and returns the letter grade from the students grade value
 * @param grade - the value is to be used to find its letter value
 * @return character - the grades letter value
 */
char getGrade(double grade);

/**
 * printreport - finds and returns the students grade, overall average student grade, and prints out student report
 * @param IOStreams - uses the inStream and outStream files. Uses a files information to make another
 * @return none - The function is a void but it prints out the students report
 */
void printreport (ifstream &inStream, ofstream &outStream);

int main(int argc, char *argv[])
{

	if (argc != 3)
	{
		cout << " Type in terminal: .\a.exe tests.txt output.txt" << endl; // Reminder if code inserted was invalid
		exit(0);
	}

	ifstream inStream;
	inStream.open(argv[1]); // Opens the tests.txt file

	if (inStream.fail())
	{
		cout << "Error: file was not located";
		exit(0);
	}

	ofstream outStream;
	outStream.open(argv[2]); // Opens a new file called output.txt

	if (outStream.fail())
	{
		cout << "Error: file was not created";
		exit(0);
	}

	printreport(inStream, outStream);

	cout << endl;
	// Closes opened files
	inStream.close(); 
	outStream.close();

	cout << "Finished" << endl; // Verifies if the code was executed up to the end

	return 0;
} /// main

char getGrade(double grade) // Checks grade based upon calculated grade
{
	if (grade >= 90)
	{
		return 'A';
	}
	else if (grade >= 80)
	{
		return 'B';
	}
	else if (grade >= 70)
	{
		return 'C';
	}
	else if (grade >= 60)
	{
		return 'D';
	}
	else
	{
		return 'F';
	}
}

void printreport (ifstream &inStream, ofstream &outStream)
{
	string answers, studentAnswers, firstname, lastname;

	inStream >> answers; // Grabs first line as the correct values
	outStream << setprecision(1) << fixed; // Fixes the outStream values one decimal place 
	int total = 0;
	double classgrade = 0.0;

	while (!inStream.eof())
	{
		inStream >> firstname >> lastname; // Grabs the names of the students
		getline(inStream, studentAnswers); // Grabs the the students answers

		outStream << firstname << ", " << lastname << endl;
		outStream << "---------------------------------------------------" << endl;
		outStream << "Answers, correct answer in parenthesis" << endl;
		outStream << endl;

		int count = 0; // Starting point for the amount of correct answers
		for (int i = 1; i <= answers.length(); i++)
		{
			char sA, a;
			sA = studentAnswers[i];
			a = answers[i - 1]; // Keeps the first correct character than starting with the second correct character 

			if (studentAnswers[i] == ' ')
			{
				outStream << setw(3) << i << ": -(" << (char)tolower(a) << ")"; // Makes the uppercase values to lowercase values
			}
			else
			{
				outStream << setw(3) << i << ": " << (char)tolower(sA) << "(" << (char)tolower(a) << ")";
			}

			if ((char)tolower(a) == (char)tolower(sA))
			{
				count++;
			}

			if (i % 5 == 0)
			{
				outStream << endl; // Every five printed answers, it will start a new line
			}
		}

		outStream << endl;

		double grade = ((double)count / answers.length()) * 100; // Calculates the students grade

		total++;

		classgrade += grade; // Adds the current students grade to the previous students 

		classgrade /= total; // Average grade value of all the students grades

		outStream << "Score: " << grade << "% " << getGrade(grade) << endl;
		outStream << "---------------------------------------------------" << endl;
		outStream << "Class Average: " << classgrade << " " << getGrade(classgrade) << endl;
		outStream << endl;
	}
}