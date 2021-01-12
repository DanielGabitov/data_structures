const int N;

int p[N];
int rang[N];

class SNM {
public:
    SNM(int n) {
        for (int i = 1; i <= n; i++) {
            p[i] = i;
            rang[i] = 0;
        }
    }
    int get(int i) {
        return (p[i] == i) ? i : (p[i] = get(p[i]));
    }
    void join(int a, int b) {
        a = get(a);
        b = get(b);
        if (rang[a] > rang[b]) {
            swap(a, b);
        }
        if (rang[a] == rang[b]) {
            rang[b] ++;
        }
        p[a] = b;
    }
    bool ask(int a, int b) {
        return get(a) == get(b);
    }
};
