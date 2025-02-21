#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please input numbers to find average." << endl;
        return 0;
    }

    double sum = 0;
    int count = argc - 1;

    for (int i = 1; i < argc; ++i) {
        sum += atof(argv[i]);
    }

    double average = sum / count;

    cout << "---------------------------------" << endl;
    cout << "Average of " << count << " numbers = ";
    
    if (average == floor(average)) {
        cout << static_cast<int>(average) << endl;
    } else {
        cout << fixed << setprecision(3) << average << endl;
    }

    cout << "---------------------------------" << endl;

    return 0;
}
