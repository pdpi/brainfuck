
pub struct Memory {
  // implemented as i16 but manually wrapped to u8!
  pos: Vec<i16>,
  neg: Vec<i16>,
  idx: i32
}

impl Memory {



  pub fn new() -> Memory {
    Memory {
      pos: vec![0],
      neg: vec![0],
      idx: 0
    }
  }

  pub fn read(&self) -> u8 {
    if self.idx < 0 {
      let idx = (-1 - self.idx) as usize;
      self.neg[idx] as u8
    } else {
      self.pos[self.idx as usize] as u8
    }
  }

  pub fn write(&mut self, v: u8) {
    if self.idx < 0 {
      let idx = (-1 - self.idx) as usize;
      self.neg[idx] = v as i16; 
    } else {
      self.pos[self.idx as usize] = v as i16;
    }
  }

  pub fn add(&mut self, val: i16) {
    if self.idx < 0 {
      let idx = (-1 - self.idx) as usize;
      self.neg[idx] += val;
      self.neg[idx] = (self.neg[idx] + 256) % 256;
    } else {
      let idx = self.idx as usize;
      self.pos[idx] += val;
      self.pos[idx] = (self.pos[idx] + 256) % 256;
    }
  }

  pub fn seek(&mut self, n: i16) {
    self.idx += n as i32;
    if self.idx >= 0 && self.pos.len() < self.idx as usize + 1 { self.pos.push(0); }
    if self.idx < 0 && self.neg.len() < (-1 - self.idx) as usize { self.neg.push(0); }
  }
}
