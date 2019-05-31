package com.hardlymundane.bf

object Memory {
  def create(): Memory = Memory(Nil, 0, Nil)
}

case class Memory private(private val back: List[Int],
                          private val cursor: Int,
                          private val fwd: List[Int],
                         ) {
  def next(): Memory = fwd match {
    case Nil => Memory(cursor :: back, 0, Nil)
    case _ => Memory(cursor :: back, fwd.head, fwd.tail)
  }

  def prev(): Memory = back match {
    case Nil => Memory(Nil, 0, cursor :: fwd)
    case _ => Memory(back.tail, back.head, cursor :: fwd)
  }

  def peek() = cursor

  def put(i: Int) = Memory(back, i, fwd)

  def add(i: Int) = Memory(back, (cursor + i) % 0xFF, fwd)
}