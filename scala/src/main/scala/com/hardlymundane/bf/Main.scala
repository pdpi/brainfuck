package com.hardlymundane.bf

import cats.effect._
import com.hardlymundane.bf.AST.Instruction
import com.hardlymundane.bf.Interpreter.Interpreter
//import cats.effect.Console.io._

import com.hardlymundane.bf.Interpreter.InstructionInterpreter

import scala.io.Source


object Main extends IOApp {

  override def run(args: List[String]): IO[ExitCode] = {
    implicit val interpreter: Interpreter[Instruction] = InstructionInterpreter
    for {
      src <- IO(Source.fromFile("hello.bf").getLines.mkString)
      _ <- Interpreter.run[IO, Instruction](Parser.parse(src))
    } yield ExitCode.Success
  }

}

