#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <codecvt>

const int MAXN = 100;

using namespace std;

vector<int> g[MAXN];
int match[MAXN], p[MAXN], base[MAXN], q[MAXN];
bool used[MAXN], blossom[MAXN];

int lca(int a, int b) {
	bool used[MAXN] = {0};
	for (;;) {
		a = base[a];
		used[a] = true;
		if (match[a] == -1) {
			break;
		}
		a = p[match[a]];
	}
	for (;;) {
		b = base[b];
		if (used[b]) {
			return b;
		}
		b = p[match[b]];
	}
}

void mark_path(int v, int b, int children) {
	while (base[v] != b) {
		blossom[base[v]] = blossom[base[match[v]]] = true;
		p[v] = children;
		children = match[v];
		v = p[match[v]];
	}
}

int find_path(int root, int n) {
	memset (used, 0, sizeof(used));
	memset (p, -1, sizeof(p));
	for (int i=0; i< n; ++i) {
		base[i] = i;
    }
	used[root] = true;
	int qh=0, qt=0;
	q[qt++] = root;
	while (qh < qt) {
		int v = q[qh++];
		for (int i=0; i<g[v].size(); ++i) {
			int to = g[v][i];
			if (base[v] == base[to] || match[v] == to) {
				continue;
			}
			if (to == root || match[to] != -1 && p[match[to]] != -1) {
				int curbase = lca (v, to);
				memset (blossom, 0, sizeof(blossom));
				mark_path (v, curbase, to);
				mark_path (to, curbase, v);
				for (int i=0; i<n; ++i) {
					if (blossom[base[i]]) {
						base[i] = curbase;
						if (!used[i]) {
							used[i] = true;
							q[qt++] = i;
						}
					}
                }
			}
			else if (p[to] == -1) {
				p[to] = v;
				if (match[to] == -1)
					return to;
				to = match[to];
				used[to] = true;
				q[qt++] = to;
			}
		}
	}
	return -1;
}

int main(int argc, char* argv[])
{
    // Input:    
    ifstream in(argv[1]);
    int size = 0, i, j;
    in >> size;
    int** matrix = new int* [size];
    for (i = 0; i < size; i++)
    {
        matrix[i] = new int[size];
        for (j = 0; j < size; j++)
            in >> matrix[i][j];
    }
    in.close();
    
    // My code:
    int new_size = size;

    for (int i = 0; i < new_size; ++i) {
        for (int j = 0; j < new_size; ++j) {
            if (matrix[i][j] == 1) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    memset(match, -1, sizeof(match));

    for (int i = 0; i < new_size; ++i) {
        if (match[i] == -1) {
            for (int j=0; j<g[i].size(); ++j) {
                if (match[g[i][j]] == -1) {
                    match[g[i][j]] = i;
                    match[i] = g[i][j];
                    break;
                }
            }
        }
    }

    for (int i = 0; i < new_size; ++i) {
        if (match[i] == -1) {
            int v = find_path(i, new_size);
            while (v != -1) {
				int pv = p[v],  ppv = match[pv];
				match[v] = pv,  match[pv] = v;
				v = ppv;
			}
        }
    }

    for (int i = 0; i < new_size; ++i) {
		for (int j = 0; j < new_size; ++j) {
			matrix[i][j] = 0;
		}
	}

    for (int i = 0; i < new_size; ++i) {
		if (match[i] != -1) {
			matrix[i][match[i]] = 1;
			matrix[match[i]][i] = 1;
		}
	}

	vector<vector<int>> vec(new_size); 
	for (int i = 0; i < new_size; ++i) {
		for (int j = 0; j < new_size; ++j) {
			vec[i].push_back(matrix[i][j]);
		}
	}

	for (int i = 0; i < vec.size(); ++i) {
		int count = 0;
		for (int j = 0; j < vec[i].size(); ++j) {
			if (vec[i][j] == 0) {
				++count;
			}
		}
		if (count == new_size) {
			vec.erase(vec.begin() + i);
			for (int j = 0; j < vec.size(); ++j) {
				vec[j].erase(vec[j].begin() + i);
			}
			--new_size;
		}
	}

	int** ans = new int* [vec.size()];
	for (int i = 0; i < vec.size(); ++i) {
		ans[i] = new int[vec.size()];
		for (int j = 0; j < vec.size(); ++j) {
			ans[i][j] = vec[i][j];
		}
	}
    // Output:
    std::wofstream out;
    out.open(argv[1]);
    out << new_size << endl;
    for (i = 0; i < new_size; i++) {
        for (j = 0; j < new_size; j++)
        {
            out << ans[i][j];
            if (j != new_size - 1)
                out << ' ';
        }
        out << endl;
    }
	
    out.close();
    
    delete[] matrix;
	delete[] ans;

    return 0;
}