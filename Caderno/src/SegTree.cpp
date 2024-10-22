#include "SegTree.h"
#include <bits/stdc++.h>
using namespace std ;

template <typename T>
class SegTree{

    private:

        const T initializer ;
        int n ; 
        vector<T> lista, segtree, seglazy ;
    
    public:
        
        SegTree::SegTree(int n_){
            n = n_ ;
            lista.resize(n_) ;
            segtree.resize(4*n_) ;
        }

        void SegTree::update(T& resp, T value){
            resp = resp + value ;
        }

        void SegTree::view_data(){

        }

        void SegTree::build(int l, int r, int seg_index){
            if (l == r){
                segtree[seg_index] = lista[l] ;
            }

            else{
                int m = (l+r)/2 ;
                build(l, m, seg_index*2) ;
                build(m+1, r, seg_index*2+1) ;
                segtree[seg_index] = segtree[seg_index*2] + segtree[seg_index*2+1]
            }
        }
        
        void SegTree::insert(int index, T value){
            lista[index] = value ;
        }
        
        void SegTree::lazy_update(int l, int r, T value){
            
        }
        
        T SegTree::lazy_query(int){

        }

        T SegTree::query(int, int){

        }

} ;

