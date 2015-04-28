#include <iostream>
using namespace std;

void swap(char* arr, int i, int j)
{
    char c = arr[i];
    arr[i] = arr[j];
    arr[j] = c;
}

void print_perm(char* s, int from, int n)
{
    if (from == n - 1) {
        cout << s << endl;
        return;
    }
    for (int i = from; i < n; ++i) {
        swap(s, from, i);
        print_perm(s, from + 1, n);
        swap(s, from, i);
    }
}

void print_perm(const string& str)
{
    char* s = const_cast<char*>(str.c_str());
    print_perm(s, 0, str.length());
}

int main()
{
    string s;
    cin >> s;
    print_perm(s);
    return 0;
}
