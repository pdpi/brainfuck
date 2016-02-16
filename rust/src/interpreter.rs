use memory::Memory;

#[derive(PartialEq,Eq)]
pub enum Instruction {
  Add(i16),
  Seek(i16),
  Get, Put,
  JmpZ(usize), JpNZ(usize),
  NoOp, End
}

#[derive(PartialEq,Eq)]
pub struct Program {
  instrs: Vec<Instruction>
}

impl Program {
  pub fn new(instrs: Vec<Instruction>) -> Program {
    Program {
      instrs: instrs
    }
  }
  pub fn parse(s: &String) -> Program {
    let mut stack = Vec::new();
    let instrs = Vec::new();
    let mut program = Program { instrs: instrs };

    for c in s.chars() {
      match c {
        '+' => {
          program.instrs.push(Instruction::Add(1));
        }
        '-' => {
          program.instrs.push(Instruction::Add(-1));
        }
        '>' => {
          program.instrs.push(Instruction::Seek(1));
        }
        '<' => {
          program.instrs.push(Instruction::Seek(-1));
        }
        ',' => {
          program.instrs.push(Instruction::Get);
        }
        '.' => {
          program.instrs.push(Instruction::Put);
        }
        '[' => {
          stack.push(program.instrs.len());
          program.instrs.push(Instruction::NoOp);
        },
        ']' => {
          let idx = stack.pop().unwrap();
          program.instrs.push(Instruction::JpNZ(idx+1));
          program.instrs[idx] = Instruction::JmpZ(program.instrs.len());
        }
        _   => ()
      }
    }
    program.instrs.push(Instruction::End);
    program
  }

  pub fn execute(&self, mem: &mut Memory) {
    let mut counter = 0;
    while self.instrs[counter] != Instruction::End {
      match self.instrs[counter] {
        Instruction::Add(n) => mem.add(n),
        Instruction::Seek(n) => mem.seek(n),
        Instruction::Put => print!("{}",mem.read() as char),
        Instruction::Get => (), // panic!("NYI"),
        Instruction::JpNZ(idx) => if mem.read() != 0 { counter = idx - 1; },
        Instruction::JmpZ(idx) => if mem.read() == 0 { counter = idx - 1; },
        _ => ()
      }
      counter += 1;
    }
  }
}
