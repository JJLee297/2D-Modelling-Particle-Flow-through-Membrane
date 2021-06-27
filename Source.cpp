#include <iostream>

using namespace std;

int main() {
	int arr[1000][1000];
	for (int x = 0; x < 1000; ++x) {
		for (int y = 0; y < 1000; ++y) {
			arr[x][y] = 0;
		}
	}
	for (int x = 0; x < 1000; ++x) {
		for (int y = 0; y < 1000; ++y) {
			cout << arr[x][y] << " ";
		}
		cout << endl;
	}
	system("pause");
}