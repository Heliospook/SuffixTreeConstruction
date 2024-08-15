#include <bits/stdc++.h>
using namespace std;

#ifndef SUFFIXTREE
#define SUFFIXTREE
// Heavily inspired by the implementation provided by adamant in https://codeforces.com/blog/entry/16780

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}

#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

int inf = 1e9, maxn = 1e6;
class SuffixTree{
    private : 
    string s;
    int sz, n, node, pos;

    struct Node{
        map<int, int> to;
        int link, fpos, len;
        Node() : link(maxn), fpos(maxn), len(maxn){}
        Node(int pos, int len) : fpos(pos), len(len), link(maxn){}
    };
    vector<Node> tree;

    int createNode(int pos, int len){
        Node node = Node(pos, len);
        tree[sz] = node;
        return sz++;
    }

    void go_edge(){
        while(pos > tree[tree[node].to[s[n - pos]]].len){
            node = tree[node].to[s[n - pos]];
            pos -= tree[node].len;
        }
    }
    void extend(int c){
        s[n++] = c; pos++; int last = 0;
        while(pos > 0){
            go_edge();
            int edge = s[n - pos];
            int &v = tree[node].to[edge];
            int t = s[tree[v].fpos + pos - 1];
            if(v == 0){
                v = createNode(n - pos, inf);
                tree[last].link = node; 
                last = 0;
            }else if(t == c){
                tree[last].link = node; return;
            }else{
                int u = createNode(tree[v].fpos, pos - 1);
                tree[u].to[c] = createNode(n - 1, inf);
                tree[u].to[t] = v;
                tree[v].fpos += pos - 1;
                tree[v].len -= pos - 1;
                v = u;
                tree[last].link = u; 
                last = u;
            }
            if(node == 0) pos--;
            else node = tree[node].link;
        }
    }

    public :
    SuffixTree(string text) : sz(1), n(0), node(0), pos(0){
        s = string(maxn, ' ');
        tree = vector<Node>(maxn, Node());

        tree[0].len = inf;
        for(int i = 0; i < text.size(); i++){
            extend(text[i]);
        }
    }

    bool search(string pattern){
        int i = 0;
        int currNode = 0;
        if(pattern.size() > n){
            return false;
        }

        while(i < pattern.size()){
            char patchar = pattern[i];
            if(tree[currNode].to[patchar] == 0){
                return false;
            }
            int nextNode = tree[currNode].to[patchar];
            int edgeLen = min(tree[nextNode].len, n - tree[nextNode].fpos);
            int remLen = pattern.size() - i;
            int compLen = min(edgeLen, remLen);
            if(s.substr(tree[nextNode].fpos, compLen) != pattern.substr(i, compLen)){
                return false;
            }
            i += compLen;
            currNode = nextNode;
        }
        return true;
    }
    
};

#endif