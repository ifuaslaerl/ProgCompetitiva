#include <bits/stdc++.h>
using namespace std;

// g++ -Dlocal main.cpp -o main

#ifdef local
    #include "debug.h"
    #define pr(...) debug(#__VA_ARGS__, __VA_ARGS__)
    #define prs(...) debug_nameless(__VA_ARGS__)
#else
    #define pr(...) 69
    #define prs(...) 69
#endif

#define fastio ios_base::sync_with_stdio(NULL); cin.tie(nullptr)

const long long int INF = 2e18 ;

template <class T> 
class SegTree{

    private:

        int n ;
        T neutral = 0 ;
        vector<T> lista , seg, lazy ;

        T merge(T val1, T val2){
            return val1 + val2 ;
        }

        T merge_in_range(int l, int r, T seg_value , T lazy_value ){
            return seg_value + (r-l+1)*lazy_value ;
        }

        void unlazy(int index, int l, int r){
            if(lazy[index] != neutral){
                seg[index] = merge_in_range(l,r,seg[index],lazy[index]) ;
                if(l!=r){
                    lazy[2*index]+=lazy[index] ;
                    lazy[2*index+1]+=lazy[index] ;
                }
                lazy[index] = neutral ;
            }
        }

        T search_query(int l, int r, int l0, int r0, int index){
            unlazy(index,l,r) ;
            if(l>r0 || r<l0){ // se ele ta fora do intervalo dado, nao entra.
                return neutral ;
            }

            if(l>=l0 && r<=r0){ // se ele ta completamente dentro do intervalo dado, entra. Nao existe sobreposicao de intervalos
                unlazy(index,l,r) ;
                return seg[index] ;
            }

            int mid = (l+r)/2 ; // se contem o intervalo
            return merge( search_query(l, mid, l0, r0, index*2) , search_query(mid+1, r, l0, r0, index*2+1) ) ;
        }   

        void seg_single_update(int l, int r, int pos, T value, int index){
            int mid = (l+r)/2 ;
            if(l==r){
                lista[pos] = value ;
                seg[index] = value ;
                return ;
            }
            if(pos>mid){
                seg_single_update(mid+1, r, pos, value, index*2+1) ;  
            }
            else{
                seg_single_update(l, mid, pos, value, index*2) ;
            }
            seg[index] = merge(seg[index*2+1] , seg[index*2]) ;
        }

        void lazy_propagation(int l, int r, int l0, int r0, T value, int index){
            unlazy(index,l,r) ;
            if( l>r0 || r<l0){
                return ;
            }

            if(l>=l0 && r<=r0){
                lazy[index] = value ;
                unlazy(index,l,r) ;
                return ;
            }

            int mid = (l+r)/2 ;
            lazy_propagation(l,mid,l0,r0,value,2*index) ;
            lazy_propagation(mid+1,r,l0,r0,value,2*index+1) ;

            seg[index] = merge(seg[index*2], seg[index*2+1]) ;
            return ;
        }

    public:

        SegTree(vector<T>& lista_){
            lista = lista_ ;
            n = lista.size() ;
            seg.resize(4*n,neutral) ;
            lazy.resize(4*n,neutral) ;
            build(0,n-1,1) ;
        }

        void build(int l, int r, int index){
            if(l==r){
                seg[index] = lista[l] ;
                return ;
            }
            int meio = (l+r)/2 ;
            build(l,meio,index*2) ;
            build(meio+1,r,index*2+1) ;        
            seg[index] = merge(seg[index*2], seg[index*2+1]) ; 
        }

        T query(int l, int r){
            return search_query(0,n-1,l,r,1) ;
        }

        void single_update(int pos, T value){
            seg_single_update(0,n-1,pos,value,1) ;
        }

        void range_update(int l, int r, T value){
            lazy_propagation(0,n-1,l,r,value,1) ;
        }

} ;

int main(){
    fastio ;

    int n , q ;
    vector<long long> lista ;
    
    cin >> n >> q ;

    lista.resize(n) ;
    for(int i=0 ; i<n ; i++){
        cin >> lista[i] ;
    }

    SegTree seg(lista) ;

    for(int i=0 ; i<q ; i++){
        int type ;
        cin >> type ;
        if(type==1){
            int a , b , u ;
            cin >> a >> b >> u ;
            seg.range_update(a-1,b-1,u) ;
        }
        else if(type==2){
            int a ;
            cin >> a ;
            cout << seg.query(a-1,a-1) << "\n" ;
        }
    }

    return 0;
}