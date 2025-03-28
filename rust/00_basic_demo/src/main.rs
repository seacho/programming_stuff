fn main() {
    //scalar type
    let a: i8 = 0;
    let a: i16 = 0;
    let a: i32 = 0;
    let a: i64 = 0;
    let a: i128 = 0;
    let a: u8 = 0;
    let a: u16 = 0;
    let a: u32 = 0;
    let a: u64 = 0;
    let a: u128 = 0;
    let a: isize = 0;
    let a: usize = 0;
    let a = 0; //i32

    // float

    let x = 2.0; // f64
    let y: f32 = 3.0; // f32

    //char type
    let c = 'z';
    let z: char = 'ℤ'; // with explicit type annotation
    let heart_eyed_cat = '😻';

    //tuple type
    let tup: (i32, f64, u8) = (500, 6.4, 1);

    //
    let tup = (500, 6.4, 1);

    let (x, y, z) = tup;

    let x: (i32, f64, u8) = (500, 6.4, 1);

    let five_hundred = x.0;

    let six_point_four = x.1;

    let one = x.2;

    //array type
    let a = [1, 2, 3, 4, 5];

    let a: [i32; 5] = [1, 2, 3, 4, 5];

    //control flow
    if c == 'x' {
    } else {
    }

    loop {
        break;
    }

    for i in a {
        break;
    }

    while c == 'z' {
        break;
    }

    //ENUM

    let home = IpAddr {
        kind: IpAddrKind::V4,
        address: String::from("127.0.0.1"),
    };

    let loopback = IpAddr {
        kind: IpAddrKind::V6,
        address: String::from("::1"),
    };

    let b = Box::new(5);
    println!("b = {b}");

    //closures
    fn add_one_v1(x: u32) -> u32 {
        x + 1
    }

    let add_one_v2 = |x: u32| -> u32 { x + 1 };
    let add_one_v3 = |x: u32| x + 1;
    let add_one_v4 = |x: u32| x + 1;

    //thread

    use std::thread;
    use std::time::Duration;

    //example 1
    thread::spawn(|| {
        for i in 1..10 {
            println!("hi number {i} from the spawned thread!");
            thread::sleep(Duration::from_millis(1));
        }
    });

    for i in 1..5 {
        println!("hi number {i} from the main thread!");
        thread::sleep(Duration::from_millis(1));
    }

    //example 2
    let handle = thread::spawn(|| {
        for i in 1..10 {
            println!("hi number {i} from the spawned thread!");
            thread::sleep(Duration::from_millis(1));
        }
    });

    for i in 1..5 {
        println!("hi number {i} from the main thread!");
        thread::sleep(Duration::from_millis(1));
    }

    handle.join().unwrap();


    let v = vec![1, 2, 3];

    let handle = thread::spawn(move || {
        println!("Here's a vector: {v:?}");
    });

    //drop(v); // oh no!

    handle.join().unwrap();
}

//OOP
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.height
    }
}

//enum
enum IpAddrKind {
    V4,
    V6,
}

struct IpAddr {
    kind: IpAddrKind,
    address: String,
}
//match
enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter,
}

fn value_in_cents(coin: Coin) -> u8 {
    match coin {
        Coin::Penny => 1,
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter => 25,
    }
}

pub struct NewsArticle {
    pub headline: String,
    pub location: String,
    pub author: String,
    pub content: String,
}

//trait
pub trait Summary {
    fn summarize(&self) -> String;
}
impl Summary for NewsArticle {
    fn summarize(&self) -> String {
        format!("{}, by {} ({})", self.headline, self.author, self.location)
    }
}

pub struct Tweet {
    pub username: String,
    pub content: String,
    pub reply: bool,
    pub retweet: bool,
}

impl Summary for Tweet {
    fn summarize(&self) -> String {
        format!("{}: {}", self.username, self.content)
    }
}

//advance function
fn returns_closure() -> impl Fn(i32) -> i32 {
    |x| x + 1
}
