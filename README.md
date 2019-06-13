# tops10vm
Abandoned PDP-10/TOPS-10 Emulator

In the early 2000's I started on a PDP-10 emulator, but somewhere in this time, the excellent SIMH and KLH-10 emulators appeared and kind of mooted my efforts.

So, then I thought to build an actual TOPS-10 emulator.   Building encode/decode logic for 36 bit values was way too tedious with the amount of time I had.

I may start this back up sometime.   With a tool more like https://github.com/kaitai-io, possibly with 36 bit extensions, might make it more possible.  I also have a version of the PDP-10 base processor emulator that I ported to C#.

I had also looked at the possibily of doing a hypervisor interface (a new system call perhaps) to SIMH.

ECA is a very simple assembler for testing.

