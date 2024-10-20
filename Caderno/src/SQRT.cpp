#include "SQRT.h"
#include <bits/stdc++.h>
using namespace std ;

template <typename T>
class SQRT{

    private:

        const T initializer=0 ; // definir caso a caso
        int n , q , b , b_ , k ; 
        vector<T> lista , blocos_resp , lista_lazy , blocos_resp_lazy ;
        vector<vector<T>> blocos ;

    public:

        SQRT::SQRT(int n_){
            n = n_ ;
            lista.resize(n_,initializer)
        }

        void SQRT::update(T& resp, T value){ // definir caso a caso
            resp = resp+value ;
        }
                
        void SQRT::view_data(){
            cout << n << " "  << b << " " << b_ << " " << k << endl ;

            for(int i=0 ; i<k ; i++){
                for(int j=0 ; j<b ; j++){
                    cout << blocos[i][j] << " " ;
                }
                cout << endl ;
            }

            for(int i=0 ; i<k ; i++) cout << blocos_resp[i] << " " ;
            cout << endl ;
        }

        void SQRT::build(){
            k = (int) sqrt(n) ; // verificar precisao depois
            b = n/k ;
            b_ = n%k ;
            if(b_) k++ ;

            blocos.resize(k,vector<T>(b,initializer)) ;
            blocos_resp.resize(k,initializer) ;

            int linha=0 ; T resp=initializer ;
            for(int i=0 ; i<n ; i++){
                
                blocos[linha][i%b] = lista[i] ;
                update(resp,lista[i]) ;
                
                if(!(i+1)%b){
                    blocos_resp[linha] = resp ;
                    linha++ ;
                    resp=initializer ;
                }
            
            }
        }

        void SQRT::insert(int index, T value){
            lista[index] = value ;
        }

        void SQRT::lazy_update(int l, int r, T value){
            l-- ; r--;
            int bloco_esq=-1 , bloco_dir=-1 , extra_esq=-1 , extra_dir=-1 ;
            
            bloco_esq = l/b ;
            bloco_dir = r/b ;
            extra_esq=l ;
            extra_dir = r ;

            if(l%b) bloco_esq++ ; 
            if((r+1)%b) bloco_dir-- ;

            if(l==r){ 
                update(lista[l], value) ; 
                return ;
            }

            if(extra_dir-extra_esq<=b){
                for(int i=extra_esq ; i<=extra_dir ; i++) update(lista[i], value) ;
                return ;
            }

            if (extra_esq < bloco_esq*b) for(int i=extra_esq ; i<bloco_esq*b ; i++) update(lista[i], value) ;
            
            for(int i=bloco_esq ; i<=bloco_dir ; i++) update(blocos_resp[i], value) ;
            
            if (extra_dir > bloco_dir*b) for(int i=(bloco_dir+1)*b ; i<=extra_dir ; i++) update(lista[i], value) ;

        }

        T SQRT::query(int index){
            index-- ;
            return lista[index] + blocos_resp[index/b]  ;
        }

        T SQRT::query(int l, int r){
            l-- ; r--;
            int bloco_esq=-1 , bloco_dir=-1 , extra_esq=-1 , extra_dir=-1 ;
            
            bloco_esq = l/b ;
            bloco_dir = r/b ;
            extra_esq=l ;
            extra_dir = r ;

            if(l%b) bloco_esq++ ; 
            if((r+1)%b) bloco_dir-- ;
            
            T asw=initializer ;

            if(l==r) return lista[l] ;

            if(extra_dir-extra_esq<=b){
                for(int i=extra_esq ; i<=extra_dir ; i++) update(asw,lista[i]) ;
                return asw ;
            }

            if (extra_esq < bloco_esq*b) for(int i=extra_esq ; i<bloco_esq*b ; i++) update(asw,lista[i]) ;
            for(int i=bloco_esq ; i<=bloco_dir ; i++) update(asw,blocos_resp[i]) ;
            if (extra_dir > bloco_dir*b) for(int i=(bloco_dir+1)*b ; i<=extra_dir ; i++) update(asw,lista[i]) ;

            return asw ;
        }

} ;
