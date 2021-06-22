#include<iostream>


class numberTheory {
	
	public:
		
		numberTheory() {}
		
		
		~numberTheory() {}
		
		
		
		
		/* 
		 * 
		 * Assumption. All parameters are <= 10^9. 
		 *
		*/
		
		
		
		
		static int GCD(int a, int b){ // one number is positive, another one is non-negative
			int tmp;
			
			while( b ){
				tmp = a % b;
				a = b;
				b = tmp;
			}
			
			return a;
		}
		
		
		static int multiplyModulo(int a, int b, int m){ // a*b (mod m); a,b >= 0, m > 0
			int res = 0;
			
			while ( b > 0 ){
				if( b % 2 == 1 ){
					res = ( res + a ) % m;
				}
				
				a = ( a+a ) % m;
				
				b /= 2;
			}
			
			return res % m;
		}
		
		
		static int fastPowerModulo(int a, int k, int m){ // a^k (mod m); k >= 0; a,m > 0
			int res = 1;
			
			while ( k > 0 ){
				if( k % 2 == 1 ){
					res = multiplyModulo(res, a, m);
				}
				
				a = multiplyModulo(a, a, m);
				
				k /= 2;
			}
			
			return res % m; 
		}
		
		
		static int reverseModuloP(int a, int p){ // a and p are relatively prime, p - prime
			return fastPowerModulo(a, p-2, p);
		}


		static int floorSqrt(int x){ // x >= 0
			int start = 0, end = 32000, result, medium;
			
			while( start <= end ){
				
				medium = ( start + end ) / 2;
				
				if( medium * medium <= x ){
					result = medium;
					
					start = medium + 1;
				}
				else{
					end = medium - 1;
				}
			}
			
			return result;
		}
		
};


int main(){
	
	numberTheory numTh;
	
	int A = numberTheory::GCD(19,551000);
	int B = numberTheory::fastPowerModulo(2,15,3);
	int C = numberTheory::reverseModuloP(7,47);
	int D = numberTheory::floorSqrt(200406070+556778);
	
	std::cout << A << std::endl << B << std::endl << C << std::endl << D << std::endl;
	
	return 0;
}
