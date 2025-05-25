#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Solution {
  public:
    #define ll long long 
    // Function to get all prime numbers in the range [l, r] using segmented sieve
    // This function returns a vector of prime numbers in the range [l, r]
    vector<ll> getPrimes(ll l, ll r) {
        vector<ll> primes;
        
        // If the range's upper bound is less than 2, there are no primes.
        if(r < 2) return primes;
        
        // Adjust the lower bound since primes start from 2.
        if(l < 2) l = 2;
        
        // Count of numbers in the range [l, r]
        ll count = r - l + 1;
        vector<bool> segSieve(count, true);
        
        // Compute primes up to sqrt(r)
        ll rootR = sqrt(r) + 1;
        vector<bool> isPrime(rootR + 1, true);
        isPrime[0] = false;
        isPrime[1] = false;
        for(ll i = 2; i * i <= rootR; i++){
            if(isPrime[i]){
                for(ll j = i * i; j <= rootR; j += i){
                    isPrime[j] = false;
                }
            }
        }
        
        // Use small primes to mark non-prime numbers in the segmented sieve
        for(ll i = 2; i <= rootR; i++){
            if(isPrime[i]){
                // Find first multiple of i within [l, r]
                ll stFactor = (l + i - 1) / i;  // ceiling division of l by i
                stFactor = max(stFactor, i);
                for(ll j = stFactor * i; j <= r; j += i){
                    segSieve[j - l] = false;
                }
            }
        }
        
        // Collect all primes from the segmented sieve
        for(ll i = 0; i < count; i++){
            if(segSieve[i]){
               primes.push_back(l + i);
            } 
        }
        return primes;
    }

    // Sieve of Eratosthenes to find all primes up to n
    vector<ll> sieveOfEratosthenes(ll n) {
        vector<bool> isPrime(n + 1, true);
        isPrime[0] = isPrime[1] = false; // 0 and 1 are not prime
        for(ll i = 2; i * i <= n; i++) {
            if(isPrime[i]) {
                for(ll j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        vector<ll> primes;
        for(ll i = 2; i <= n; i++) {
            if(isPrime[i]) {
                primes.push_back(i);
            }
        }
        return primes;
    }

    // Function to compute the smallest prime factor (SPF) for all numbers from 1 to n.
    vector<ll> smallestPrimeFactor(ll n) {
        // Initialize spf array where each number is initially assumed to be its own SPF.
        vector<ll> spf(n + 1);
        for (ll i = 1; i <= n; i++) {
            spf[i] = i;
        }
        
        // Use a sieve-like method to update spf for composite numbers.
        // Note: We start from 2 since 1 is not prime.
        for (ll i = 2; i * i <= n; i++) {
            // If i is still marked as its own smallest factor, then it is prime.
            if (spf[i] == i) {
                // Mark i as a factor for its multiples if they haven't been marked yet.
                for (ll j = i * i; j <= n; j += i) {
                    if (spf[j] == j) {
                        spf[j] = i;
                    }
                }
            }
        }
        return spf;
    }
};

int main(){
    Solution sol;
    ll L, R;
    cout << "Enter L and R: ";
    cin >> L >> R;
    
    vector<ll> primeList = sol.getPrimes(L, R);
    cout << "Primes in the range [" << L << ", " << R << "]: ";
    for(auto p : primeList)
        cout << p << " ";
    cout << "\n";
    vector<ll> allPrimes = sol.sieveOfEratosthenes(R);
    cout << "All primes up to " << R << ": ";
    for(auto p : allPrimes)
        cout << p << " ";
    cout << "\n";
    cout << "Total primes in the range: " << primeList.size() << "\n";
    cout << "Total primes up to " << R << ": " << allPrimes.size() << "\n";
    vector<ll> spf = sol.smallestPrimeFactor(R);
    cout << "Smallest prime factors up to " << R << ": ";
    for(ll i = 2; i <= R; i++) {
        cout << spf[i] << " ";
    }
    cout << "\n";
    return 0;
}
