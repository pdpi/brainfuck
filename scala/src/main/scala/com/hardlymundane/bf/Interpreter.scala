package com.hardlymundane.bf

import cats.implicits._
//import cats.syntax.foldable._
import cats.effect.Sync
import com.hardlymundane.bf.AST._

import scala.annotation.tailrec

object Interpreter {

  def run[F[_], I](p: List[I])(implicit M: Sync[F], V: Interpreter[I]) =
    V.interpret(p, Memory.create())

  trait Interpreter[I] {
    def interpret[F[_]](program: List[I], m: Memory)(implicit M: Sync[F]): F[Memory] =
      program.foldM(m)(this.step(_,_))

    def step[F[_]](m: Memory, instruction: I)(implicit M: Sync[F]): F[Memory]
  }

  implicit object InstructionInterpreter extends Interpreter[Instruction] {


    override def step[F[_]](m: Memory, inst: Instruction)(implicit M: Sync[F]): F[Memory] = inst match {
      case Next => M.pure(m.next())
      case Prev => M.pure(m.prev())
      case Add(n) => M.pure(m.add(n))
      case Print => for {
        _ <- M.delay(print(m.peek.toChar))
      } yield m
      case Read => for {
        c <- M.pure(scala.io.StdIn.readChar())
      } yield m.put(c)
      case l@Loop(body) => if (m.peek == 0)
        M.delay(m)
      else for {
        nextMem <- interpret(body, m)
        n <- step(nextMem, l)
      } yield n
    }
  }

}