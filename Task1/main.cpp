#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int charToInt(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - 48;
    }
    if (c >= 'A' && c <= 'F')
    {
        return c - 64 + 9;
    }

    throw c;
}

char intToChar(int i)
{
    if (i >= 0 && i <= 9)
    {
        return i + 48;
    }
    if (i >= 10 && i <= 16)
    {
        return i + 64 - 9;
    }

    throw i;
}

vector<int> transformToVector(string str)
{
    vector<int> vec;

    for (char c : str)
    {
        vec.push_back(charToInt(c));
    }

    return vec;
}

string restoreFromVector(vector<int> vec)
{
    string str;

    for (int i : vec)
    {
        str.push_back(intToChar(i));
    }

    return str;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        cout << "Wrong number of parameters!" << endl;
        return -1;
    }

    string bigNumber = argv[1];
    string smallNumber = argv[2];

    if (bigNumber < smallNumber)
    {
        swap(bigNumber, smallNumber);
    }

    try
    {
        // Task 1: sum of 2 hex numbers

        vector<int> vecBigNumber = transformToVector(bigNumber);
        vector<int> vecSmallNumber = transformToVector(smallNumber);

        int minLength = min(vecBigNumber.size(), vecSmallNumber.size());
        int maxLength = max(vecBigNumber.size(), vecSmallNumber.size());

        for (int i = 0; i < minLength; i++)
        {
            int posVecBigNumber = vecBigNumber.size() - i - 1;
            int posVecSmallNumber = vecSmallNumber.size() - i - 1;

            int sum = vecBigNumber[posVecBigNumber] + vecSmallNumber[posVecSmallNumber];
            vecBigNumber[posVecBigNumber] = sum % 16;
            vecBigNumber[posVecBigNumber - 1] += sum / 16;
        }

        int remainder = 0;
        string remainderString;

        if (vecBigNumber[0] >= 16)
        {
            remainder = vecBigNumber[0] / 16;
            vecBigNumber[0] %= 16;
            remainderString = string(1, intToChar(remainder));
        }

        string result = remainderString + restoreFromVector(vecBigNumber);

        cout << result << endl;


        // Task 2: dec representation of hex number

        vector<int> vecNumber = transformToVector(result);

        int power = 0;
        int sum = 0;
        for (int i = vecNumber.size() - 1; i >= 0; i--)
        {
            sum += vecNumber[i] * pow(16, power++);
        }

        cout << sum << endl;
    }
    catch (int i)
    {
        cout << "Conversion intToChar failed with param " << i << endl;
        return -1;
    }
    catch (char c)
    {
        cout << "Conversion charToInt failed with param " << c << endl;
        return -1;
    }

    return 0;
}
