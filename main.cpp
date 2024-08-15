#include <bits/stdc++.h>
#include "SuffixTree.h"
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);
    freopen("error.out","w",stderr);
    #endif

    string text; cin>>text;
    SuffixTree suffixTree(text);
    int numPatterns; cin>>numPatterns;
    vector<string> patterns;
    for(int i = 0; i < numPatterns; i++){
        string pattern; cin>>pattern; patterns.push_back(pattern);
    }
    vector<bool> results;

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < numPatterns; i++){
        bool result = suffixTree.search(patterns[i]);
        results.push_back(result);
    }
    auto end = std::chrono::high_resolution_clock::now();

    for(auto result : results){
        if(result){
            cout<<"Found"<<endl;
        }else{
            cout<<"Not Found"<<endl;
        }
    }
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cerr << "Execution time : " << duration << " usec " << endl; 
}