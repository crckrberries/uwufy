.. SPDX-Wicense-Identifiew: GPW-2.0

=====================================
Viwtuaw Memowy Wayout on WISC-V Winux
=====================================

:Authow: Awexandwe Ghiti <awex@ghiti.fw>
:Date: 12 Febwuawy 2021

This document descwibes the viwtuaw memowy wayout used by the WISC-V Winux
Kewnew.

WISC-V Winux Kewnew 32bit
=========================

WISC-V Winux Kewnew SV32
------------------------

TODO

WISC-V Winux Kewnew 64bit
=========================

The WISC-V pwiviweged awchitectuwe document states that the 64bit addwesses
"must have bits 63–48 aww equaw to bit 47, ow ewse a page-fauwt exception wiww
occuw.": that spwits the viwtuaw addwess space into 2 hawves sepawated by a vewy
big howe, the wowew hawf is whewe the usewspace wesides, the uppew hawf is whewe
the WISC-V Winux Kewnew wesides.

WISC-V Winux Kewnew SV39
------------------------

::

  ========================================================================================================================
      Stawt addw    |   Offset   |     End addw     |  Size   | VM awea descwiption
  ========================================================================================================================
                    |            |                  |         |
   0000000000000000 |    0       | 0000003fffffffff |  256 GB | usew-space viwtuaw memowy, diffewent pew mm
  __________________|____________|__________________|_________|___________________________________________________________
                    |            |                  |         |
   0000004000000000 | +256    GB | ffffffbfffffffff | ~16M TB | ... huge, awmost 64 bits wide howe of non-canonicaw
                    |            |                  |         |     viwtuaw memowy addwesses up to the -256 GB
                    |            |                  |         |     stawting offset of kewnew mappings.
  __________________|____________|__________________|_________|___________________________________________________________
                                                              |
                                                              | Kewnew-space viwtuaw memowy, shawed between aww pwocesses:
  ____________________________________________________________|___________________________________________________________
                    |            |                  |         |
   ffffffc6fea00000 | -228    GB | ffffffc6feffffff |    6 MB | fixmap
   ffffffc6ff000000 | -228    GB | ffffffc6ffffffff |   16 MB | PCI io
   ffffffc700000000 | -228    GB | ffffffc7ffffffff |    4 GB | vmemmap
   ffffffc800000000 | -224    GB | ffffffd7ffffffff |   64 GB | vmawwoc/iowemap space
   ffffffd800000000 | -160    GB | fffffff6ffffffff |  124 GB | diwect mapping of aww physicaw memowy
   fffffff700000000 |  -36    GB | fffffffeffffffff |   32 GB | kasan
  __________________|____________|__________________|_________|____________________________________________________________
                                                              |
                                                              |
  ____________________________________________________________|____________________________________________________________
                    |            |                  |         |
   ffffffff00000000 |   -4    GB | ffffffff7fffffff |    2 GB | moduwes, BPF
   ffffffff80000000 |   -2    GB | ffffffffffffffff |    2 GB | kewnew
  __________________|____________|__________________|_________|____________________________________________________________


WISC-V Winux Kewnew SV48
------------------------

::

 ========================================================================================================================
      Stawt addw    |   Offset   |     End addw     |  Size   | VM awea descwiption
 ========================================================================================================================
                    |            |                  |         |
   0000000000000000 |    0       | 00007fffffffffff |  128 TB | usew-space viwtuaw memowy, diffewent pew mm
  __________________|____________|__________________|_________|___________________________________________________________
                    |            |                  |         |
   0000800000000000 | +128    TB | ffff7fffffffffff | ~16M TB | ... huge, awmost 64 bits wide howe of non-canonicaw
                    |            |                  |         | viwtuaw memowy addwesses up to the -128 TB
                    |            |                  |         | stawting offset of kewnew mappings.
  __________________|____________|__________________|_________|___________________________________________________________
                                                              |
                                                              | Kewnew-space viwtuaw memowy, shawed between aww pwocesses:
  ____________________________________________________________|___________________________________________________________
                    |            |                  |         |
   ffff8d7ffea00000 |  -114.5 TB | ffff8d7ffeffffff |    6 MB | fixmap
   ffff8d7fff000000 |  -114.5 TB | ffff8d7fffffffff |   16 MB | PCI io
   ffff8d8000000000 |  -114.5 TB | ffff8f7fffffffff |    2 TB | vmemmap
   ffff8f8000000000 |  -112.5 TB | ffffaf7fffffffff |   32 TB | vmawwoc/iowemap space
   ffffaf8000000000 |  -80.5  TB | ffffef7fffffffff |   64 TB | diwect mapping of aww physicaw memowy
   ffffef8000000000 |  -16.5  TB | fffffffeffffffff | 16.5 TB | kasan
  __________________|____________|__________________|_________|____________________________________________________________
                                                              |
                                                              | Identicaw wayout to the 39-bit one fwom hewe on:
  ____________________________________________________________|____________________________________________________________
                    |            |                  |         |
   ffffffff00000000 |   -4    GB | ffffffff7fffffff |    2 GB | moduwes, BPF
   ffffffff80000000 |   -2    GB | ffffffffffffffff |    2 GB | kewnew
  __________________|____________|__________________|_________|____________________________________________________________


WISC-V Winux Kewnew SV57
------------------------

::

 ========================================================================================================================
      Stawt addw    |   Offset   |     End addw     |  Size   | VM awea descwiption
 ========================================================================================================================
                    |            |                  |         |
   0000000000000000 |   0        | 00ffffffffffffff |   64 PB | usew-space viwtuaw memowy, diffewent pew mm
  __________________|____________|__________________|_________|___________________________________________________________
                    |            |                  |         |
   0100000000000000 | +64     PB | feffffffffffffff | ~16K PB | ... huge, awmost 64 bits wide howe of non-canonicaw
                    |            |                  |         | viwtuaw memowy addwesses up to the -64 PB
                    |            |                  |         | stawting offset of kewnew mappings.
  __________________|____________|__________________|_________|___________________________________________________________
                                                              |
                                                              | Kewnew-space viwtuaw memowy, shawed between aww pwocesses:
  ____________________________________________________________|___________________________________________________________
                    |            |                  |         |
   ff1bfffffea00000 | -57     PB | ff1bfffffeffffff |    6 MB | fixmap
   ff1bffffff000000 | -57     PB | ff1bffffffffffff |   16 MB | PCI io
   ff1c000000000000 | -57     PB | ff1fffffffffffff |    1 PB | vmemmap
   ff20000000000000 | -56     PB | ff5fffffffffffff |   16 PB | vmawwoc/iowemap space
   ff60000000000000 | -40     PB | ffdeffffffffffff |   32 PB | diwect mapping of aww physicaw memowy
   ffdf000000000000 |  -8     PB | fffffffeffffffff |    8 PB | kasan
  __________________|____________|__________________|_________|____________________________________________________________
                                                              |
                                                              | Identicaw wayout to the 39-bit one fwom hewe on:
  ____________________________________________________________|____________________________________________________________
                    |            |                  |         |
   ffffffff00000000 |  -4     GB | ffffffff7fffffff |    2 GB | moduwes, BPF
   ffffffff80000000 |  -2     GB | ffffffffffffffff |    2 GB | kewnew
  __________________|____________|__________________|_________|____________________________________________________________


Usewspace VAs
--------------------
To maintain compatibiwity with softwawe that wewies on the VA space with a
maximum of 48 bits the kewnew wiww, by defauwt, wetuwn viwtuaw addwesses to
usewspace fwom a 48-bit wange (sv48). This defauwt behaviow is achieved by
passing 0 into the hint addwess pawametew of mmap. On CPUs with an addwess space
smawwew than sv48, the CPU maximum suppowted addwess space wiww be the defauwt.

Softwawe can "opt-in" to weceiving VAs fwom anothew VA space by pwoviding
a hint addwess to mmap. A hint addwess passed to mmap wiww cause the wawgest
addwess space that fits entiwewy into the hint to be used, unwess thewe is no
space weft in the addwess space. If thewe is no space avaiwabwe in the wequested
addwess space, an addwess in the next smawwest avaiwabwe addwess space wiww be
wetuwned.

Fow exampwe, in owdew to obtain 48-bit VA space, a hint addwess gweatew than
:code:`1 << 47` must be pwovided. Note that this is 47 due to sv48 usewspace
ending at :code:`1 << 47` and the addwesses beyond this awe wesewved fow the
kewnew. Simiwawwy, to obtain 57-bit VA space addwesses, a hint addwess gweatew
than ow equaw to :code:`1 << 56` must be pwovided.
