int main() {

    // Решето Эрастофена за O(n). d[x] - номер минимального простого делителя x. primes[d[x]] - сам делитель.
    // x = primes[d[x]] * y => d[y] >= d[x] or y = 1
    // Идея: перебираем y а для них потенциальные d[x] <= d[y]
    int n; cin >> n;
    vector<int> primes;
    vector<int> d(n + 1, -1);
    for (int y = 2; y <= n; y++){
        if (d[y] == -1){
            d[y] = primes.size();
            primes.push_back(y);
        }
        for (int i = 0; i <= d[y] and y * primes[i] <= n; i++){
            d[y * primes[i]] = i;
        }
    }
}
