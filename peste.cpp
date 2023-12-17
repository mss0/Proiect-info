#include <fstream>

using namespace std;

ifstream cin("peste.in");
ofstream cout("peste.out");

const int NMAX = 25, TMAX = 192;
int f[NMAX + 1], d[NMAX + 1], t[NMAX + 1], dp[NMAX + 1][TMAX + 1], stayed[NMAX + 1][TMAX + 1];

bool solve() {

	int n;
	cin >> n;

	if (n == 0)
		return false;

	int h;
	cin >> h;

	h *= 12;

	for (int i = 1; i <= n; i++)
		cin >> f[i];
	for (int i = 1; i <= n; i++)
		cin >> d[i];
	for (int i = 1; i <= n - 1; i++)
		cin >> t[i];

	int fishes = 0, decrement = 0;
	for (int j = h - 1; j >= 0; j--) {

		int catched = f[n] - decrement;

		if (catched < 0)
			catched = 0;

		fishes += catched;
		dp[n][j] = fishes;
		stayed[n][j] = h - j;
		decrement += d[n];
	}

	for (int i = n - 1; i >= 1; i--) {

		for (int j = h - 1; j >= 0; j--) {

			fishes = decrement = 0;
			dp[i][j] = -1;

			int temp = -1;
			for (int k = 0; k <= h - j; k++) {

				if (j + k + t[i] < h)
					temp = dp[i + 1][j + k + t[i]] + fishes;
				else
					temp = fishes;

				if (temp >= dp[i][j]) {

					dp[i][j] = temp;
					stayed[i][j] = k;
				}

				int catched = f[i] - decrement;
				if (catched < 0)
					catched = 0;

				fishes += catched;
				decrement += d[i];
			}
		}
	}

	cout << dp[1][0] << "\n";

	int i = 1, j = 0;
	while (j < h) {

		cout << stayed[i][j] * 5 << " ";
		j += stayed[i][j] + t[i++];
	}
	for (i; i <= n; i++)
		cout << "0 ";
	cout << "\n";

	return true;
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	while (solve()) {}
}
