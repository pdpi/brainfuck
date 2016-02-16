extern crate brainfuck;

use brainfuck::interpreter::Program;
use brainfuck::memory::Memory;
use std::io::{stdin,Read};

fn main() {
  let mut s = String::new();
  let _ = stdin().read_to_string(&mut s);
  let mut m = Memory::new();
  Program::parse(&s).execute(&mut m);
}