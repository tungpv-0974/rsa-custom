#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "bignumber.h"


using namespace std;

bool CheckIsPrime(InfInt num)
{
    if (num < 2)
        return false;
    InfInt i = 2;
    while (i <= num / 2)
    {
        if (num%i == 0)
            return false;
        i++;
    }
    return true;
}
InfInt Multiply(InfInt num1, InfInt num2)
{
    return num1 * num2;
}
bool CheckCoPrime(InfInt num1, InfInt num2)
{
    InfInt lowest, r, a, b;
    bool coprime;
    if (num1 > num2)
    {
        a = num1;
        b = num2;
    }
    else
    {
        a = num2;
        b = num1;
    }
    while (b != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    if (a == 1)
        coprime = true;
    else
        coprime = false;
    return coprime;
}
InfInt FindE(InfInt phi_n)
{
    InfInt e = 0;
    InfInt i = 1;
    cout << "Choose an integer number e (e must be coprime of phi_n): ";
    cin >> e;
    bool isCoPrime = CheckCoPrime(phi_n, e);
    while (!isCoPrime)
    {
        if (CheckCoPrime(phi_n, e + i))
        {
            e += i;
            isCoPrime = true;
            break;
        }
        if (CheckCoPrime(phi_n, e - i))
        {
            e -= i;
            isCoPrime = true;
            break;
        }
        i++;
    }
    cout << "\nGia tri cua e duoc chon la e = " << e << "\n";
    return e;
}
InfInt FindD(InfInt phi_n, InfInt e)
{
    InfInt a = phi_n, b = e;
    InfInt x1 = 0, x2 = 1, y1 = 1, y2 = 0, x, y, q, r;
    //long int gcd = b;
    while (b != 0)
    {
        q = a / b;
        r = a % b;
        x = x2 - x1 * q;
        y = y2 - y1 * q;
        a = b;
        b = r;
        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
    }
    if (a != 1)
    {
        cout << "Choose a suitable \"e\" value" << endl;
        e = FindE(phi_n);
        FindD(phi_n, e);
    }
    x = x2;
    y = y2;
    if (
        y < 0)
        y = phi_n + y;
    return y;
}
InfInt Encrypt_Decrypt(InfInt t, InfInt e, InfInt n)
{
    InfInt rem;
    InfInt x = 1;
    //if(e>0)x=t;
    while (e != 0)
    {
        rem = e % 2;
        e = e / 2;
        if (rem == 1)
            x = (x * t) % n;
        t = (t * t) % n;
    }
    return x;
}
void EncDecStr(InfInt e, InfInt n)
{
    // char *str = new char
    //     [100000];
    // char *str1 = new char
    //     [100000];
    string str, str1;
    cout << "\nEnter a string: ";
    cin >> str;
    cout << "Encrypting using Public Key: " << endl;
    InfInt i = 0;
    while (i != str.length())
    {
        // char temp = str[i.toInt()];
        InfInt temp = Encrypt_Decrypt(InfInt(str[i.toInt()]), e, n);
        str1[i.toInt()] = temp.toInt();
        i++;
    }
    cout << str1 << endl;
}
void EncDecNum(InfInt n1, InfInt n2)
{
    InfInt pn;
    cout << "\nEnter an integer number: ";
    cin >> pn;
    cout << Encrypt_Decrypt(pn, n1, n2) << endl;
}
void generate_key(InfInt &n, InfInt &e, InfInt &d)
{
    InfInt p, q, phi_n, pt, ct;

    cout << "Enter a prime number: ";
    cin >> p;
    InfInt i = 1;
    bool isPrime = CheckIsPrime(p);
    while (!isPrime)
    {
        if (CheckIsPrime(p + i))
        {
            p += i;
            isPrime = true;
            break;
        }
        if (CheckIsPrime(p - i))
        {
            p -= i;
            isPrime = true;
            break;
        }
        i++;
    }
    cout << "\nSo nguyen to gan so da nhap la p = " << p;

    cout << "\nEnter another prime number: ";
    cin >> q;
    isPrime = CheckIsPrime(q);
    i = 1;
    while (!isPrime)
    {
        if (CheckIsPrime(q + i))
        {
            q += i;
            isPrime = true;
            break;
        }
        if (CheckIsPrime(q - i))
        {
            q -= i;
            isPrime = true;
            break;
        }
        i++;
    }
    cout << "\nSo nguyen to gan so da nhap la q = " << q << "\n";

    n = Multiply(p, q);
    cout << "n is " << n << endl;
    phi_n = Multiply(p - 1, q - 1);
    cout << "phi_n is ";
    e = FindE(phi_n);
    cout << "e is " << e << endl;
    if (e == false)
    {
        cout << "Choose two suitable prime number" << endl;
        exit(1);
    }
    d = FindD(phi_n, e);
    cout << "d is " << d << endl;
}
int main()
{
    cout << endl
         << endl
         << "##IMPLEMENTATION OF R.S.A ALGORITHM USING C++##"
         << endl
         << endl;
    InfInt n, e = 0, d;
    generate_key(n, e, d);
    cout << "Public Key : (" << e << "," << n << ")" << endl;
    cout << "Private Key : (" << d << "," << n << ")" << endl;
    cout << endl
         << "Press 1: for encrypting numbers & 2: for encrypting string: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        EncDecNum(e, n);
        break;
    case 2:
        EncDecStr(e, n);
        break;
    default:
        cout << "Wrong choice. Try again." << endl;
        exit(1);
    }
    cout << endl
         << "Press 1: for decrypting numbers & 2: for decrypting string: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        EncDecNum(d, n);
        break;
    case 2:
        EncDecStr(d, n);
        break;
    default:
        cout << "Wrong choice. Try again." << endl;
        exit(1);
    }
    return 0;
}