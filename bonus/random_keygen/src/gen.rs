use num_bigint::{BigUint, RandBigInt};
use num_traits::{One, Zero};
use rand::thread_rng;
use std::usize;

// https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
fn is_prime(n: &BigUint, k: u32) -> bool {
    if n % 2u32 == BigUint::zero() { return false; }

    let one = BigUint::one();
    let two = BigUint::from(2u32);
    let n_minus_one = n - &one;
    let mut d = n_minus_one.clone();
    let mut r = 0u32;

    while &d % &two == BigUint::zero() {
        d /= &two;
        r += 1;
    }
    let mut rng = thread_rng();
    'witness_loop: for _ in 0..k {
        let a = rng.gen_biguint_range(&two, &(n - &two));
        let mut x = a.modpow(&d, n);
        if x == one || x == n_minus_one {
            continue;
        }
        for _ in 0..r-1 {
            x = x.modpow(&two, n);
            if x == n_minus_one {
                continue 'witness_loop;
            }
        }
        return false;
    }
    true
}

pub fn gen_primes(bits: usize) {
    let mut rng = thread_rng();
    let mut primes: Vec<BigUint> = vec![]; 

    while primes.len() < 2 {
        let n: BigUint = rng.gen_biguint(bits as u64);
        if is_prime(&n, 10) {
            primes.push(n);
        }
    }
    let p = BigUint::to_bytes_le(&primes[0]);
    let q = BigUint::to_bytes_le(&primes[1]);
    println!("p: {:x}\nq: {:x}", BigUint::from_bytes_le(&p), BigUint::from_bytes_le(&q));
}

pub fn gen_key(bits: usize) {
    let mut rng = thread_rng();
    let key: BigUint = rng.gen_biguint(bits as u64);

    println!("hex key of size {bits}: {:x}", key);
}
