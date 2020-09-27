#include <iostream>
#include <vector>
#include <cmath>

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

std::vector<int> transformToVector(const std::string& str)
{
    std::vector<int> vec;
    vec.reserve(str.size());

    for (char c : str)
    {
        vec.push_back(charToInt(c));
    }

    return vec;
}

std::string restoreFromVector(const std::vector<int>& vec)
{
    std::string str;

    int startPos = 0;
    while (vec[startPos] == 0)  //a что если вектор окажется полностью из нулей? здесь мы упадем
    {    //лучше использовать  std::find_if с последующей проверкой итератора

        startPos++;
    }

    for (int i = startPos; i < vec.size(); i++)
    {
        str.push_back(intToChar(vec[i]));
    }

    return str;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Wrong number of parameters!" << std::endl;
        return -1;
    }

    std::cout << "Your input: 0x" << argv[1] << ", 0x" << argv[2] << std::endl;

    std::string bigNumber = argv[1];
    std::string smallNumber = argv[2];

    if (bigNumber.size() < smallNumber.size())
    {
        std::swap(bigNumber, smallNumber);
    }

    try
    {
        // Task 1: sum of 2 hex numbers

        std::vector<int> vecBigNumber = transformToVector(bigNumber);
        std::vector<int> vecSmallNumber = transformToVector(smallNumber);

        std::vector<int> resultVector;
        resultVector.resize(vecBigNumber.size() + 1);

        int maxLength = std::max(vecBigNumber.size(), vecSmallNumber.size());

        for (int i = 0; i < maxLength; i++)
        {
            int posVecBigNumber = vecBigNumber.size() - i - 1;
            int posVecSmallNumber = vecSmallNumber.size() - i - 1;
            int posResultVector = resultVector.size() - i - 1;

            int vecBigNumberValue = vecBigNumber[posVecBigNumber];
            int vecSmallNumberValue = (posVecSmallNumber >= 0) ? vecSmallNumber[posVecSmallNumber] : 0;

            resultVector[posResultVector] = vecBigNumberValue + vecSmallNumberValue;
        }

        for (int i = resultVector.size() - 1; i > 0; i--)
        {
            resultVector[i - 1] += resultVector[i] / 16;
            resultVector[i] %= 16;
        }

        std::string result = restoreFromVector(resultVector);

        std::cout << "Hexadecimal representation of the sum is: 0x" << result << std::endl;


        // Task 2: dec representation of hex number

        std::vector<int> vecNumber = transformToVector(result);

        int power = 0;
        int sum = 0;
        for (int i = vecNumber.size() - 1; i >= 0; i--)
        {
            sum += vecNumber[i] * pow(16, power++);
        }

        std::cout << "Decimal representation of the sum is: " << sum << std::endl;
    }
    catch (int i)
    {
        std::cout << "Conversion intToChar failed with param " << i << std::endl;
        return -1;
    }
    catch (char c)
    {
        std::cout << "Conversion charToInt failed with param " << c << std::endl;
        return -1;
    }

    return 0;
}
