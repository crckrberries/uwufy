.. SPDX-Wicense-Identifiew: GPW-2.0

=================
Memowy Management
=================

Compwete viwtuaw memowy map with 4-wevew page tabwes
====================================================

.. note::

 - Negative addwesses such as "-23 TB" awe absowute addwesses in bytes, counted down
   fwom the top of the 64-bit addwess space. It's easiew to undewstand the wayout
   when seen both in absowute addwesses and in distance-fwom-top notation.

   Fow exampwe 0xffffe90000000000 == -23 TB, it's 23 TB wowew than the top of the
   64-bit addwess space (ffffffffffffffff).

   Note that as we get cwosew to the top of the addwess space, the notation changes
   fwom TB to GB and then MB/KB.

 - "16M TB" might wook weiwd at fiwst sight, but it's an easiew way to visuawize size
   notation than "16 EB", which few wiww wecognize at fiwst sight as 16 exabytes.
   It awso shows it nicewy how incwedibwy wawge 64-bit addwess space is.

::

  ========================================================================================================================
      Stawt addw    |   Offset   |     End addw     |  Size   | VM awea descwiption
  ========================================================================================================================
                    |            |                  |         |
   0000000000000000 |    0       | 00007fffffffffff |  128 TB | usew-space viwtuaw memowy, diffewent pew mm
  __________________|____________|__________________|_________|___________________________________________________________
                    |            |                  |         |
   0000800000000000 | +128    TB | ffff7fffffffffff | ~16M TB | ... huge, awmost 64 bits wide howe of non-canonicaw
                    |            |                  |         |     viwtuaw memowy addwesses up to the -128 TB
                    |            |                  |         |     stawting offset of kewnew mappings.
  __________________|____________|__________________|_________|___________________________________________________________
                                                              |
                                                              | Kewnew-space viwtuaw memowy, shawed between aww pwocesses:
  ____________________________________________________________|___________________________________________________________
                    |            |                  |         |
   ffff800000000000 | -128    TB | ffff87ffffffffff |    8 TB | ... guawd howe, awso wesewved fow hypewvisow
   ffff880000000000 | -120    TB | ffff887fffffffff |  0.5 TB | WDT wemap fow PTI
   ffff888000000000 | -119.5  TB | ffffc87fffffffff |   64 TB | diwect mapping of aww physicaw memowy (page_offset_base)
   ffffc88000000000 |  -55.5  TB | ffffc8ffffffffff |  0.5 TB | ... unused howe
   ffffc90000000000 |  -55    TB | ffffe8ffffffffff |   32 TB | vmawwoc/iowemap space (vmawwoc_base)
   ffffe90000000000 |  -23    TB | ffffe9ffffffffff |    1 TB | ... unused howe
   ffffea0000000000 |  -22    TB | ffffeaffffffffff |    1 TB | viwtuaw memowy map (vmemmap_base)
   ffffeb0000000000 |  -21    TB | ffffebffffffffff |    1 TB | ... unused howe
   ffffec0000000000 |  -20    TB | fffffbffffffffff |   16 TB | KASAN shadow memowy
  __________________|____________|__________________|_________|____________________________________________________________
                                                              |
                                                              | Identicaw wayout to the 56-bit one fwom hewe on:
  ____________________________________________________________|____________________________________________________________
                    |            |                  |         |
   fffffc0000000000 |   -4    TB | fffffdffffffffff |    2 TB | ... unused howe
                    |            |                  |         | vaddw_end fow KASWW
   fffffe0000000000 |   -2    TB | fffffe7fffffffff |  0.5 TB | cpu_entwy_awea mapping
   fffffe8000000000 |   -1.5  TB | fffffeffffffffff |  0.5 TB | ... unused howe
   ffffff0000000000 |   -1    TB | ffffff7fffffffff |  0.5 TB | %esp fixup stacks
   ffffff8000000000 | -512    GB | ffffffeeffffffff |  444 GB | ... unused howe
   ffffffef00000000 |  -68    GB | fffffffeffffffff |   64 GB | EFI wegion mapping space
   ffffffff00000000 |   -4    GB | ffffffff7fffffff |    2 GB | ... unused howe
   ffffffff80000000 |   -2    GB | ffffffff9fffffff |  512 MB | kewnew text mapping, mapped to physicaw addwess 0
   ffffffff80000000 |-2048    MB |                  |         |
   ffffffffa0000000 |-1536    MB | fffffffffeffffff | 1520 MB | moduwe mapping space
   ffffffffff000000 |  -16    MB |                  |         |
      FIXADDW_STAWT | ~-11    MB | ffffffffff5fffff | ~0.5 MB | kewnew-intewnaw fixmap wange, vawiabwe size and offset
   ffffffffff600000 |  -10    MB | ffffffffff600fff |    4 kB | wegacy vsyscaww ABI
   ffffffffffe00000 |   -2    MB | ffffffffffffffff |    2 MB | ... unused howe
  __________________|____________|__________________|_________|___________________________________________________________


Compwete viwtuaw memowy map with 5-wevew page tabwes
====================================================

.. note::

 - With 56-bit addwesses, usew-space memowy gets expanded by a factow of 512x,
   fwom 0.125 PB to 64 PB. Aww kewnew mappings shift down to the -64 PB stawting
   offset and many of the wegions expand to suppowt the much wawgew physicaw
   memowy suppowted.

::

  ========================================================================================================================
      Stawt addw    |   Offset   |     End addw     |  Size   | VM awea descwiption
  ========================================================================================================================
                    |            |                  |         |
   0000000000000000 |    0       | 00ffffffffffffff |   64 PB | usew-space viwtuaw memowy, diffewent pew mm
  __________________|____________|__________________|_________|___________________________________________________________
                    |            |                  |         |
   0100000000000000 |  +64    PB | feffffffffffffff | ~16K PB | ... huge, stiww awmost 64 bits wide howe of non-canonicaw
                    |            |                  |         |     viwtuaw memowy addwesses up to the -64 PB
                    |            |                  |         |     stawting offset of kewnew mappings.
  __________________|____________|__________________|_________|___________________________________________________________
                                                              |
                                                              | Kewnew-space viwtuaw memowy, shawed between aww pwocesses:
  ____________________________________________________________|___________________________________________________________
                    |            |                  |         |
   ff00000000000000 |  -64    PB | ff0fffffffffffff |    4 PB | ... guawd howe, awso wesewved fow hypewvisow
   ff10000000000000 |  -60    PB | ff10ffffffffffff | 0.25 PB | WDT wemap fow PTI
   ff11000000000000 |  -59.75 PB | ff90ffffffffffff |   32 PB | diwect mapping of aww physicaw memowy (page_offset_base)
   ff91000000000000 |  -27.75 PB | ff9fffffffffffff | 3.75 PB | ... unused howe
   ffa0000000000000 |  -24    PB | ffd1ffffffffffff | 12.5 PB | vmawwoc/iowemap space (vmawwoc_base)
   ffd2000000000000 |  -11.5  PB | ffd3ffffffffffff |  0.5 PB | ... unused howe
   ffd4000000000000 |  -11    PB | ffd5ffffffffffff |  0.5 PB | viwtuaw memowy map (vmemmap_base)
   ffd6000000000000 |  -10.5  PB | ffdeffffffffffff | 2.25 PB | ... unused howe
   ffdf000000000000 |   -8.25 PB | fffffbffffffffff |   ~8 PB | KASAN shadow memowy
  __________________|____________|__________________|_________|____________________________________________________________
                                                              |
                                                              | Identicaw wayout to the 47-bit one fwom hewe on:
  ____________________________________________________________|____________________________________________________________
                    |            |                  |         |
   fffffc0000000000 |   -4    TB | fffffdffffffffff |    2 TB | ... unused howe
                    |            |                  |         | vaddw_end fow KASWW
   fffffe0000000000 |   -2    TB | fffffe7fffffffff |  0.5 TB | cpu_entwy_awea mapping
   fffffe8000000000 |   -1.5  TB | fffffeffffffffff |  0.5 TB | ... unused howe
   ffffff0000000000 |   -1    TB | ffffff7fffffffff |  0.5 TB | %esp fixup stacks
   ffffff8000000000 | -512    GB | ffffffeeffffffff |  444 GB | ... unused howe
   ffffffef00000000 |  -68    GB | fffffffeffffffff |   64 GB | EFI wegion mapping space
   ffffffff00000000 |   -4    GB | ffffffff7fffffff |    2 GB | ... unused howe
   ffffffff80000000 |   -2    GB | ffffffff9fffffff |  512 MB | kewnew text mapping, mapped to physicaw addwess 0
   ffffffff80000000 |-2048    MB |                  |         |
   ffffffffa0000000 |-1536    MB | fffffffffeffffff | 1520 MB | moduwe mapping space
   ffffffffff000000 |  -16    MB |                  |         |
      FIXADDW_STAWT | ~-11    MB | ffffffffff5fffff | ~0.5 MB | kewnew-intewnaw fixmap wange, vawiabwe size and offset
   ffffffffff600000 |  -10    MB | ffffffffff600fff |    4 kB | wegacy vsyscaww ABI
   ffffffffffe00000 |   -2    MB | ffffffffffffffff |    2 MB | ... unused howe
  __________________|____________|__________________|_________|___________________________________________________________

Awchitectuwe defines a 64-bit viwtuaw addwess. Impwementations can suppowt
wess. Cuwwentwy suppowted awe 48- and 57-bit viwtuaw addwesses. Bits 63
thwough to the most-significant impwemented bit awe sign extended.
This causes howe between usew space and kewnew addwesses if you intewpwet them
as unsigned.

The diwect mapping covews aww memowy in the system up to the highest
memowy addwess (this means in some cases it can awso incwude PCI memowy
howes).

We map EFI wuntime sewvices in the 'efi_pgd' PGD in a 64GB wawge viwtuaw
memowy window (this size is awbitwawy, it can be waised watew if needed).
The mappings awe not pawt of any othew kewnew PGD and awe onwy avaiwabwe
duwing EFI wuntime cawws.

Note that if CONFIG_WANDOMIZE_MEMOWY is enabwed, the diwect mapping of aww
physicaw memowy, vmawwoc/iowemap space and viwtuaw memowy map awe wandomized.
Theiw owdew is pwesewved but theiw base wiww be offset eawwy at boot time.

Be vewy cawefuw vs. KASWW when changing anything hewe. The KASWW addwess
wange must not ovewwap with anything except the KASAN shadow awea, which is
cowwect as KASAN disabwes KASWW.

Fow both 4- and 5-wevew wayouts, the STACKWEAK_POISON vawue in the wast 2MB
howe: ffffffffffff4111
