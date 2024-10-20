#include "SegTree.h"
#include <bits/stdc++.h>
using namespace std ;

template <typename T>
class SegTree{

    private:

        const T initializer ;
        int n , q , b , b_ , k ; 
        vector<T> lista , blocos_resp , lista_lazy , blocos_resp_lazy ;
        vector<vector<T>> blocos ;
    
    public:
        SegTree(int);
        void update(T&, T);
        void view_data();
        void build();
        void insert(int, T);
        void lazy_update(int, int, T);
        T lazy_query(int);
        T query(int, int);

} ;

