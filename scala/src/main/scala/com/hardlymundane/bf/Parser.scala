package com.hardlymundane.bf

import com.hardlymundane.bf.AST._

import scala.annotation.tailrec

object Parser {

  type Stack = List[Program]

  private def push(s: Stack, i: Instruction): Stack = (i :: s.head) :: s.tail

  private def pushFrame(s: Stack): Stack = Nil :: s

  def parse(src: String): Program = {
    @tailrec
    def run(stack: Stack, src: List[Char]): Program = src match {
      case Nil => stack.head.reverse
      case head :: tail => head match {
        case '+' => run(push(stack, Add(1)), tail)
        case '-' => run(push(stack, Add(-1)), tail)
        case '<' => run(push(stack, Prev), tail)
        case '>' => run(push(stack, Next), tail)
        case '.' => run(push(stack, Print), tail)
        case ',' => run(push(stack, Read), tail)
        case '[' => run(pushFrame(stack), tail)
        case ']' => run(push(stack.tail, Loop(stack.head.reverse)), tail)
        case _   => run(stack, tail)
      }
    }

    run(List(Nil), src.toList)
  }
}
