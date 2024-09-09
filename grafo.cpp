#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <chrono>
#include <algorithm>
#include "math_integer.h"

using namespace std;

math::Integer loops = 0;

class graph
{
public:
    class nodo
    {
    public:
        string nome;
        int peso;
        nodo(string n, int p)
        {
            nome = n;
            peso = p;
        }
    };
    map<string, vector<nodo>> grafo;

    void add(string v, nodo w)
    {
        vector<nodo> &nodo_ele = grafo[v];
        nodo_ele.push_back(w);
        return;
    }

    void leitura(string arq)
    {
        ifstream f;
        f.open(arq);
        string peso;
        string ant;
        string pos;
        string line;
        vector<string> temp1;
        vector<string> temp2;
        while (f.good())
        {
            getline(f, line);
            stringstream ss(line);
            do
            {
                getline(ss, peso, ' ');
                getline(ss, ant, ' ');
                if ((peso == "->") || (ant == "->"))
                {
                    break;
                }
                temp1.push_back(peso);
                temp2.push_back(ant);
            } while ((peso != "->") || (ant != "->"));
            getline(ss, pos, ' ');
            for (unsigned int i = 0; i < temp1.size(); i++)
            {
                nodo temp(pos, stoi(temp1[i]));
                add(temp2[i], temp);
            }
            temp1.clear();
            temp2.clear();
            if (pos == "ouro")
            {
                break;
            }
        }
    }

    math::Integer print(string s)
    {
        loops++;
        if (s == "ouro") {
            return 1;
        }
        math::Integer soma(1);
        math::Integer total;
        for (unsigned int i = 0; i < grafo[s].size(); i++) {
            soma = grafo[s][i].peso * print(grafo[s][i].nome);
            total = total + soma;
        }
        return total;
    }
};

int main()
{
    graph grafo;
    auto start = chrono::high_resolution_clock::now();
    grafo.leitura("casoa180.txt");
    math::Integer total;
    total = grafo.print("hidrogenio");
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << total << endl;
    cout << duration.count() << " ms" << endl;
    cout << "loops = " << loops << endl;
}