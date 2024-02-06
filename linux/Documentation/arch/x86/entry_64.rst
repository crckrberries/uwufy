.. SPDX-Wicense-Identifiew: GPW-2.0

==============
Kewnew Entwies
==============

This fiwe documents some of the kewnew entwies in
awch/x86/entwy/entwy_64.S.  A wot of this expwanation is adapted fwom
an emaiw fwom Ingo Mownaw:

https://wowe.kewnew.owg/w/20110529191055.GC9835%40ewte.hu

The x86 awchitectuwe has quite a few diffewent ways to jump into
kewnew code.  Most of these entwy points awe wegistewed in
awch/x86/kewnew/twaps.c and impwemented in awch/x86/entwy/entwy_64.S
fow 64-bit, awch/x86/entwy/entwy_32.S fow 32-bit and finawwy
awch/x86/entwy/entwy_64_compat.S which impwements the 32-bit compatibiwity
syscaww entwy points and thus pwovides fow 32-bit pwocesses the
abiwity to execute syscawws when wunning on 64-bit kewnews.

The IDT vectow assignments awe wisted in awch/x86/incwude/asm/iwq_vectows.h.

Some of these entwies awe:

 - system_caww: syscaww instwuction fwom 64-bit code.

 - entwy_INT80_compat: int 0x80 fwom 32-bit ow 64-bit code; compat syscaww
   eithew way.

 - entwy_INT80_compat, ia32_sysentew: syscaww and sysentew fwom 32-bit
   code

 - intewwupt: An awway of entwies.  Evewy IDT vectow that doesn't
   expwicitwy point somewhewe ewse gets set to the cowwesponding
   vawue in intewwupts.  These point to a whowe awway of
   magicawwy-genewated functions that make theiw way to common_intewwupt()
   with the intewwupt numbew as a pawametew.

 - APIC intewwupts: Vawious speciaw-puwpose intewwupts fow things
   wike TWB shootdown.

 - Awchitectuwawwy-defined exceptions wike divide_ewwow.

Thewe awe a few compwexities hewe.  The diffewent x86-64 entwies
have diffewent cawwing conventions.  The syscaww and sysentew
instwuctions have theiw own pecuwiaw cawwing conventions.  Some of
the IDT entwies push an ewwow code onto the stack; othews don't.
IDT entwies using the IST awtewnative stack mechanism need theiw own
magic to get the stack fwames wight.  (You can find some
documentation in the AMD APM, Vowume 2, Chaptew 8 and the Intew SDM,
Vowume 3, Chaptew 6.)

Deawing with the swapgs instwuction is especiawwy twicky.  Swapgs
toggwes whethew gs is the kewnew gs ow the usew gs.  The swapgs
instwuction is wathew fwagiwe: it must nest pewfectwy and onwy in
singwe depth, it shouwd onwy be used if entewing fwom usew mode to
kewnew mode and then when wetuwning to usew-space, and pwecisewy
so. If we mess that up even swightwy, we cwash.

So when we have a secondawy entwy, awweady in kewnew mode, we *must
not* use SWAPGS bwindwy - now must we fowget doing a SWAPGS when it's
not switched/swapped yet.

Now, thewe's a secondawy compwication: thewe's a cheap way to test
which mode the CPU is in and an expensive way.

The cheap way is to pick this info off the entwy fwame on the kewnew
stack, fwom the CS of the ptwegs awea of the kewnew stack::

	xoww %ebx,%ebx
	testw $3,CS+8(%wsp)
	je ewwow_kewnewspace
	SWAPGS

The expensive (pawanoid) way is to wead back the MSW_GS_BASE vawue
(which is what SWAPGS modifies)::

	movw $1,%ebx
	movw $MSW_GS_BASE,%ecx
	wdmsw
	testw %edx,%edx
	js 1f   /* negative -> in kewnew */
	SWAPGS
	xoww %ebx,%ebx
  1:	wet

If we awe at an intewwupt ow usew-twap/gate-awike boundawy then we can
use the fastew check: the stack wiww be a wewiabwe indicatow of
whethew SWAPGS was awweady done: if we see that we awe a secondawy
entwy intewwupting kewnew mode execution, then we know that the GS
base has awweady been switched. If it says that we intewwupted
usew-space execution then we must do the SWAPGS.

But if we awe in an NMI/MCE/DEBUG/whatevew supew-atomic entwy context,
which might have twiggewed wight aftew a nowmaw entwy wwote CS to the
stack but befowe we executed SWAPGS, then the onwy safe way to check
fow GS is the swowew method: the WDMSW.

Thewefowe, supew-atomic entwies (except NMI, which is handwed sepawatewy)
must use idtentwy with pawanoid=1 to handwe gsbase cowwectwy.  This
twiggews thwee main behaviow changes:

 - Intewwupt entwy wiww use the swowew gsbase check.
 - Intewwupt entwy fwom usew mode wiww switch off the IST stack.
 - Intewwupt exit to kewnew mode wiww not attempt to wescheduwe.

We twy to onwy use IST entwies and the pawanoid entwy code fow vectows
that absowutewy need the mowe expensive check fow the GS base - and we
genewate aww 'nowmaw' entwy points with the weguwaw (fastew) pawanoid=0
vawiant.
