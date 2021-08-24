
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

auto t1 = high_resolution_clock::now();
for (int i = 0; i < 999999; i++) {
	(int)g();
}
auto t2 = high_resolution_clock::now();
duration<double, std::milli> ms_double = t2 - t1;
std::cout << ms_double.count() << "ms" << endl;
t1 = high_resolution_clock::now();
for (int i = 0; i < 999999; i++) {
	int dir = rand() % 100 + 1;
}
t2 = high_resolution_clock::now();
ms_double = t2 - t1;
std::cout << ms_double.count() << "ms";


//gen() test
	double ar2[5] = { 0 };

	for (int i = 0; i < 100000; ++i) {
		int b = gen2();
		if (b < -75)
			ar2[0]++;
		else if (b <= -25)
			ar2[1]++;
		else if (b < 25)
			ar2[2]++;
		else if (b <= 75)
			ar2[3]++;
		else
			ar2[4]++;
	}
	for (int i = 0; i < 5; ++i) {
		cout << i << ": " << ar2[i] << endl;
	}
	system("pause");


auto start = chrono::steady_clock::now();
	totalA = 0;
	totalB = 0;
	for (int k = 0; k < 250; ++k) {
		sim(30, 50, 100);
		if (k % 25 == 0) {
			cout << k << " ";
		}
	}
	auto end = chrono::steady_clock::now();
	cout << totalA << " " << totalB << "\nElapsed time in seconds: "
		<< chrono::duration_cast<chrono::seconds>(end - start).count() << " sec";
	start = chrono::steady_clock::now();
	totalA = 0;
	totalB = 0;
	for (int k = 0; k < 250; ++k) {
		sim2(30, 50, 100);
		if (k % 25 == 0) {
			cout << k << " ";
		}
	}
	end = chrono::steady_clock::now();
	cout << totalA << " " << totalB << "\nElapsed time in seconds: "
		<< chrono::duration_cast<chrono::seconds>(end - start).count() << " sec";
