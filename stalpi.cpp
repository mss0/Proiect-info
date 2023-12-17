#include <fstream>

using namespace std;


ifstream cin("stalpi.in");
ofstream cout("stalpi.out");


const int N = 2500, DMAX = 127500;
int n, k, p, dmax;
bool poz[DMAX+1];
short int dp[2][DMAX+1];

// dp[i][j] = nr min de mutari pt o configuratie de i stalpi, unde ultimul e la poz j
// dp[i][j] = min(dp[i-1][j-d]), k <= d <= p


int main()
{
    cin >> n >> k >> p;

    for (int i = 1; i <= n; i++)
    {
        int dist;
        cin >> dist;

        if (i == 1)
        {
            dmax = dist + p * (n-1);
            for (int i = 0; i <= dmax; i++)
                poz[i] = 1;
        }

        poz[dist] = 0;
    }

    
    for (int j = 0; j <= dmax; j++)
        dp[1][j] = poz[j];

    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j <= dmax; j++)
            dp[i & 1][j] = n+1;

        for (int j = k * (i-1); j <= dmax - k * (n-i); j++)
        {
            for (int d = k; d <= p; d++)
            {
                if (j - d >= 0)
					dp[i & 1][j] = min( dp[i & 1][j], short(dp[(i - 1) & 1][j - d] + poz[j]) );
                else
                    break;
            }
        }
    }


    short int ans = n+1;
    for (int j = 1; j <= dmax; j++)
        ans = min(ans, dp[n & 1][j]);
    
    cout << ans;


    return 0;
}
