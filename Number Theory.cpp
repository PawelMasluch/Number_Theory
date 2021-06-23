#include<iostream>
#include<ctime>
#include<vector>


typedef long long LL;


#define REP(i,a,b) for(int i=a; i<=b; ++i)


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
		
		
		static LL multiplyModulo(LL a, LL b, LL m){ // a*b (mod m); a,b >= 0, m > 0
			
			a %= m;
			b %= m;
			
			LL res = 0;
			
			while ( b > 0 ){
				if( b % 2 == 1 ){
					res = ( res + a ) % m;
				}
				
				a = ( a+a ) % m;
				
				b /= 2;
			}
			
			return res % m;
		}
		
		
		static LL fastPowerModulo(LL a, LL k, LL m){ // a^k (mod m); k >= 0; a,m > 0
			
			a %= m;
			
			LL res = 1;
			
			while ( k > 0 ){
				if( k % 2 == 1 ){
					res = multiplyModulo(res, a, m);
				}
				
				a = multiplyModulo(a, a, m);
				
				k /= 2;
			}
			
			return res % m; 
		}
		
		
		static LL reverseModuloP(LL a, LL p){ // a and p are relatively prime, p - prime
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
		
		
		// Miller-Rabin primality test + additional base cases.
		// 0 <= n <= 9*10^18 - an integer to be checked
		// k - number of tests (by default, k=50)
		static bool isPrimeMillerRabin(LL n, int k=50){
			
			/* Additional cases. */
			
			if( n == 0 || n == 1 ) {
				return false;
			}
			
			if( n == 2 ){
				return true;
			}
			
			if( n % 2 == 0  &&  n > 2 ){
				return false;
			}
			
			
			// ---------------------------------
			
			
			/* A main part of the algorithm - Miller-Rabin primality test. */
			
			// Sources:
			// https://pl.wikipedia.org/wiki/Test_Millera-Rabina (main source)
			// https://primes.utm.edu/prove/prove2_3.html
			// https://www.ams.org/journals/mcom/1993-61-204/S0025-5718-1993-1192971-8/S0025-5718-1993-1192971-8.pdf
			
			
			LL d = n-1;
			int s = 0;
			
			while( d % 2 == 0 ){
				d /= 2;
				++s;
			} // n-1 = 2^s * d
			
			
			srand( time(NULL) );
			
			
			if( n < (LL)4759123141 ){
				std::vector <int> a = {2,7,61};
				int noNumbers_a = a.size();
				
				
				REP(l,0,noNumbers_a-1){ // for each test
				
					bool isSingleTestResultIsComposite = true;
					
					int val = fastPowerModulo(a[l], d, n); // a[l]^d (mod n)
					
					isSingleTestResultIsComposite = isSingleTestResultIsComposite & ( val != 1 ) & ( val != n-1 );
					
					if( isSingleTestResultIsComposite == false ){
						continue;
					}
					
					
					REP(j,1,s-1){
						val = fastPowerModulo(val, 2, n); // val^2 (mod n)
						isSingleTestResultIsComposite &= ( val != n-1 );
						
						if( isSingleTestResultIsComposite == false ){
							break;
						}
					}
					
					if( isSingleTestResultIsComposite == true ){
						return false; // n - composite
					}
				}
			
				return true; // n - probably prime	
			}
			
			
			
			if( n < (LL)341550071728321 ){
				std::vector <int> a = {2,3,5,7,11,13,17};
				int noNumbers_a = a.size();
				
				
				REP(l,0,noNumbers_a-1){ // for each test
				
					bool isSingleTestResultIsComposite = true;
					
					int val = fastPowerModulo(a[l], d, n); // a[l]^d (mod n)
					
					isSingleTestResultIsComposite = isSingleTestResultIsComposite & ( val != 1 ) & ( val != n-1 );
					
					if( isSingleTestResultIsComposite == false ){
						continue;
					}
					
					
					REP(j,1,s-1){
						val = fastPowerModulo(val, 2, n); // val^2 (mod n)
						isSingleTestResultIsComposite &= ( val != n-1 );
						
						if( isSingleTestResultIsComposite == false ){
							break;
						}
					}
					
					if( isSingleTestResultIsComposite == true ){
						return false; // n - composite
					}
				}
			
				return true; // n - probably prime
			}
			
			
			REP(i,1,k){ // for each test
				
				bool isSingleTestResultIsComposite = true;
				
				int a = 1 + rand() % (n-1); // a in {1, ..., n-1}
				
				int val = fastPowerModulo(a, d, n); // a^d (mod n)
				
				isSingleTestResultIsComposite = isSingleTestResultIsComposite & ( val != 1 ) & ( val != n-1 );
				
				if( isSingleTestResultIsComposite == false ){
					continue;
				}
				
				
				REP(j,1,s-1){
					val = fastPowerModulo(val, 2, n); // val^2 (mod n)
					isSingleTestResultIsComposite &= ( val != n-1 );
					
					if( isSingleTestResultIsComposite == false ){
						break;
					}
				}
				
				if( isSingleTestResultIsComposite == true ){
					return false; // n - composite
				}
			}
			
			return true; // n - probably prime
		}
		
};


int main(){
	
	numberTheory numTh;
	
	int A = numberTheory::GCD(19,551000);
	int B = numberTheory::fastPowerModulo(2,15,3);
	int C = numberTheory::reverseModuloP(7,47);
	int D = numberTheory::floorSqrt(200406070+556778);
	
	std::cout << A << std::endl << B << std::endl << C << std::endl << D << std::endl;
	
	
	// ----------------
	
	
	REP(n,0,100){
		if( numberTheory::isPrimeMillerRabin(n) == true ){
			std::cout << "Liczba " << n << " jest prawdopodobnie pierwsza\n";
		}
		else{
			std::cout << "Liczba " << n << " nie jest pierwsza\n";
		}
	}
	
	return 0;
}
