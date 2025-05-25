#include <iostream>
#include <algorithm>
using namespace std;

class Math {
public:
    using ll = long long;

    // ---------------------------
    // Function: gcd
    // ---------------------------
    // Computes the greatest common divisor of 'a' and 'b'
    // using the Euclidean algorithm.
    static ll gcd(ll a, ll b) {
        while (b != 0) {
            a %= b;
            swap(a, b);
        }
        return a;
    }
    static ll gcdRec(ll a, ll b) {
        ll mn = min(a, b);
        ll mx = max(a, b);
        if (mn == 0) return mx;
        return gcdRec(mn, mx % mn);
    }
    
    // ---------------------------
    // Function: binaryMultiplication
    // ---------------------------
    // Multiplies two numbers 'a' and 'b' using binary (or "Russian peasant")
    // multiplication. This avoids repeated addition and works in O(log b) time.
    static ll binaryMultiplication(ll a, ll b) {
        ll result = 0;
        while (b > 0) {
            if (b & 1) {
                result += a;
            }
            a <<= 1;
            b >>= 1;
        }
        return result;
    }

    // A variant of binary multiplication that computes (a * b) mod 'mod'
    // This is especially useful when a * b might overflow a 64-bit integer.
    static ll binaryMultiplicationMod(ll a, ll b, ll mod) {
        ll result = 0;
        a %= mod;
        while (b > 0) {
            if (b & 1) {
                result = (result + a) % mod;
            }
            a = (a << 1) % mod;
            b >>= 1;
        }
        return result;
    }

    // ---------------------------
    // Function: binaryExponentiation
    // ---------------------------
    // Computes 'base' raised to the power 'exp' using exponentiation by squaring.
    // Time Complexity: O(log exp)
    static ll binaryExponentiation(ll base, ll exp) {
        ll result = 1;
        while (exp > 0) {
            if (exp & 1) {
                result *= base;
            }
            base *= base;
            exp >>= 1;
        }
        return result;
    }

    // Binary Exponentiation that computes (base^exp) mod 'mod'
    static ll binaryExponentiationMod(ll base, ll exp, ll mod) {
        ll result = 1 % mod;  // Ensures proper handling when mod == 1.
        base %= mod;
        while (exp > 0) {
            if (exp & 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    }
};

int main() {
    using ll = long long;
    ll a = 123456789, b = 987654321;
    ll num = 2, exp = 30, mod = 1000000007;
    
    cout << "GCD(" << a << ", " << b << ") = " << Math::gcd(a, b) << "\n";
    cout << "Binary Multiplication: " << a << " * " << b << " = " 
         << Math::binaryMultiplication(a, b) << "\n";
    cout << "Binary Multiplication Mod " << mod << ": " 
         << Math::binaryMultiplicationMod(a, b, mod) << "\n";
    cout << "Binary Exponentiation: " << num << "^" << exp << " = " 
         << Math::binaryExponentiation(num, exp) << "\n";
    cout << "Binary Exponentiation Mod " << mod << ": " 
         << Math::binaryExponentiationMod(num, exp, mod) << "\n";
    cout << "GCD Recursive(" << a << ", " << b << ") = "
         << Math::gcdRec(a, b) << "\n";
    
    return 0;
}
