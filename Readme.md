# HWOpenBuilder

A project that is trying to make a framework for working on the developing of digital hardware simulation/emulation.
Imagine a toolkit to develop your own NES/GameBoy/... emulator

## Problem explanation

There are good solutions to this problem like using Verilator, by coding in verilog you can write the hardware you want to mimic and then you can simulate this hardware by transpiling it to multithread c++. This is a good solution for people that are familiar with hardware languages but not for programmers.

What if you could use a fast and friendly scripting language like Lua to create the hardware you want and connect it with an intuitive UI. This is what HWOpenBuilder is trying to achieve. 

![ui example with nodes and connections](./assets/ui.png)
