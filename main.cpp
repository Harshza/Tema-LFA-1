#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <cstring>

using namespace std;
ifstream fin("date.in");

int F[302], v[302], k, m, n, q0, l; // in F sunt starile finale, v este un vector de aparitie,iar restul variabilelor sunt din enunt
unordered_map<char, vector<int>> M[302]; //  map-ul / dictionarul este functia de tranzitie
queue<int> Q1, Q2; // in Q1 vom tine toate starile unde putem ajunge fara sa folosim o litera(fara litere sau $)
// in Q2 vom tine starile in care putem ajunge din starile din Q1 folosind caracterul curent

bool evaluate(char s[])
{
    int lung = strlen(s);
    Q1.push(q0); 
    v[q0] = 1; //incepem cu starea initiala,o punem in coada si vizitam
    for(int i = 0; i < lung; i++)
    {
        int j = i+1;
        if(Q1.empty())
            return false; // daca am ramas fara stari,cuvantul este respins(nu s-a putut ajunge in nicio stare)
        while(!Q1.empty())
        {
            int x = Q1.front();
            Q1.pop();
            Q2.push(x); //punem tot ce este in Q1 in Q2(putem ajunge din starea q in starea q fara litere)
            for(int y : M[x]['$'])
                if(v[y] != j)
                {
                    v[y] = j;
                    Q1.push(y); //punem toate starile in care punem ajunge cu $ si le vizitam
                }
        }
        while(!Q2.empty())
        {
            int x = Q2.front();
            Q2.pop();
            for(int y : M[x][s[i]])
                if(v[y] != j + 1)
                {
                    v[y] = j + 1;
                    Q1.push(y); //folosind caracterul curent,punem in Q1 toate starile in care putem ajunge si le vizitam pentru pasul urmator
                }
        }
    }
    while(!Q1.empty()) // dupa ce am terminat cuvantul,inca putem folosi $,deci mai trecem odata prin Q1
    {
        int x = Q1.front();
        Q1.pop();
        Q2.push(x);
        for(int y : M[x]['$'])
            if(v[y] != lung + 1)
            {
                v[y] = lung + 1;
                Q1.push(y);
            }
    }
    while(!Q2.empty()) // verificam daca vreuna din starile cu care am terminat este stare finala
    {
        int x = Q2.front();
        Q2.pop();
        for(int i = 0; i < k; i++)
            if(x == F[i])
                return true;
    }
    return false;
}
int main()
{
    char s[302],alf[302]; // s este cuvantul,alf este alfabetul
    fin >> n;
    fin >> m;
    for(int i = 0; i < m; i++)
        fin >> alf[i];

    alf[m] = '$';
    alf[m+1] = '\0';

    fin >> q0;
    fin >> k;
    for(int i = 0; i < k; i++)
        fin >> F[i];
    fin >> l;
    for(int i = 1; i <= l; i++)
    {
        int x, y;
        char a;
        fin >> x >> a >> y;
        M[x][a].push_back(y);
    }
    fin >> s;

    bool ok = evaluate(s);

    if(ok)
        cout << "Cuvantul citit este acceptat de automat.\n";
    else
        cout << "Cuvantul citit NU este acceptat de automat.\n";

    return 0;
}