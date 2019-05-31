package com.hardlymundane.bf

object AST {

  type Program = List[Instruction]

  sealed trait Instruction

  case object Next extends Instruction

  case object Prev extends Instruction

  case object Print extends Instruction

  case object Read extends Instruction

  case class Add(val i: Int) extends Instruction

  case class Loop(val body: Program) extends Instruction

}
