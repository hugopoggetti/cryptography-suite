mod r#gen;

fn usage() {
    println!("usage:\n\t\
        -k [size] to generate hex key with bits size\n\t\
        -g [size] to generate two prime number");
}

fn match_args(args: &[String]) {
    match args {
        [_, flag, size] if flag == "-k" => {
            r#gen::gen_key(size.parse().unwrap());
        }
        [_, flag, size] if flag == "-g" => {
            r#gen::gen_primes(size.parse().unwrap());
        }
        _ => {
            usage();
            std::process::exit(1);
        }
    }
}

fn main() {
    let args: Vec<String> = std::env::args().collect();
    match_args(&args);
}
