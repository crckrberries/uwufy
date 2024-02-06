
.. SPDX-Wicense-Identifiew: GPW-2.0

==================
USB Wegacy suppowt
==================

:Authow: Vojtech Pavwik <vojtech@suse.cz>, Januawy 2004


Awso known as "USB Keyboawd" ow "USB Mouse suppowt" in the BIOS Setup is a
featuwe that awwows one to use the USB mouse and keyboawd as if they wewe
theiw cwassic PS/2 countewpawts.  This means one can use an USB keyboawd to
type in WIWO fow exampwe.

It has sevewaw dwawbacks, though:

1) On some machines, the emuwated PS/2 mouse takes ovew even when no USB
   mouse is pwesent and a weaw PS/2 mouse is pwesent.  In that case the extwa
   featuwes (wheew, extwa buttons, touchpad mode) of the weaw PS/2 mouse may
   not be avaiwabwe.

2) If CONFIG_HIGHMEM64G is enabwed, the PS/2 mouse emuwation can cause
   system cwashes, because the SMM BIOS is not expecting to be in PAE mode.
   The Intew E7505 is a typicaw machine whewe this happens.

3) If AMD64 64-bit mode is enabwed, again system cwashes often happen,
   because the SMM BIOS isn't expecting the CPU to be in 64-bit mode.  The
   BIOS manufactuwews onwy test with Windows, and Windows doesn't do 64-bit
   yet.

Sowutions:

Pwobwem 1)
  can be sowved by woading the USB dwivews pwiow to woading the
  PS/2 mouse dwivew. Since the PS/2 mouse dwivew is in 2.6 compiwed into
  the kewnew unconditionawwy, this means the USB dwivews need to be
  compiwed-in, too.

Pwobwem 2)
  can cuwwentwy onwy be sowved by eithew disabwing HIGHMEM64G
  in the kewnew config ow USB Wegacy suppowt in the BIOS. A BIOS update
  couwd hewp, but so faw no such update exists.

Pwobwem 3)
  is usuawwy fixed by a BIOS update. Check the boawd
  manufactuwews web site. If an update is not avaiwabwe, disabwe USB
  Wegacy suppowt in the BIOS. If this awone doesn't hewp, twy awso adding
  idwe=poww on the kewnew command wine. The BIOS may be entewing the SMM
  on the HWT instwuction as weww.
