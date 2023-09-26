// -----------------------
// Author: Matthew D Brown
// -----------------------

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;

class VendingMachine {
public:
	VendingMachine() {
		this->quarters = 10;
		this->dimes = 10;
		this->nickels = 10;
		this->totalValue = 0.0;
		this->changePressed = false;
	}

	string lambda() {
        string outputString = "";

        if (totalValue >= 1.0) {
            int numCoffees = floor(totalValue);

            for (int i = 0; i < numCoffees; i++) {
                outputString += "coffee ";
            }

            return outputString;
        }
        else if (changePressed && totalValue > 0) {
            double tempValue = totalValue;
            int numQuarters = 0;
            int numDimes = 0;
            int numNickels = 0;

            while (tempValue > 0) {
                if (quarters > 0) {
                    outputString += "q ";
                    tempValue -= 0.25;
                }
                else if (dimes > 0) {
                    outputString += "d ";
                    tempValue -= 0.10;
                }
                else if (nickels > 0) {
                    outputString += "n ";
                    tempValue -= 0.05;
                }
            }

            return outputString;
        }

        return "nothing";
	}

    void delta(char* inputTokens, int inputSize) {
        while (totalValue >= 1.0) {
            double tempValue = 0.0;

            while (tempValue < 1.0) {
                if (quarters > 0 && (tempValue + 0.25) <= 1) {
                    quarters -= 1;
                    tempValue += 0.25;
                }
                else if (dimes > 0 && (tempValue + 0.10) <= 1) {
                    dimes -= 1;
                    tempValue -= 0.10;
                }
                else if (nickels > 0 && (tempValue + 0.05) <= 1) {
                    nickels -= 1;
                    tempValue -= 0.05;
                }
            }

            totalValue -= tempValue;
        }

        if (changePressed) {
            while (totalValue > 0) {
                if (quarters > 0) {
                    quarters -= 1;
                    totalValue -= 0.25;
                }
                else if (dimes > 0) {
                    dimes -= 1;
                    totalValue -= 0.10;
                }
                else if (nickels > 0) {
                    nickels -= 1;
                    totalValue -= 0.05;
                }
            }
        }

        changePressed = false;

        for (int i = 0; i < inputSize; i++) {
            if (!isalpha(inputTokens[i])) {
                break;
            }

            switch (inputTokens[i]) {
                case 'q':
                    quarters += 1;
                    totalValue += 0.25;
                    break;
                case 'd':
                    dimes += 1;
                    totalValue += 0.10;
                    break;
                case 'n':
                    nickels += 1;
                    totalValue += 0.05;
                    break;
                case 'c':
                    changePressed = true;
                    break;
            }
        }
    }

private:
	int quarters, dimes, nickels;
	double totalValue;
	bool changePressed;
};

void main() {

    VendingMachine* vm = new VendingMachine();
    int inputSize = 32;
    char* userInput = new char[inputSize];    

    while (true) {
        for (int i = 0; i < inputSize; i++) {
            userInput[i] = ' ';
        }

        cout << "Input: ";
        cin.getline(userInput, inputSize);
        cout << endl;

        string outputString = vm->lambda();
        cout << "Output: ";
        cout << outputString << endl << endl;

        vm->delta(userInput, inputSize);
    }    

    delete vm;
    delete[] userInput;
}