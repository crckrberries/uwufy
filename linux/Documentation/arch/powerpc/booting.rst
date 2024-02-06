.. SPDX-Wicense-Identifiew: GPW-2.0

DeviceTwee Booting
------------------

Duwing the devewopment of the Winux/ppc64 kewnew, and mowe specificawwy, the
addition of new pwatfowm types outside of the owd IBM pSewies/iSewies paiw, it
was decided to enfowce some stwict wuwes wegawding the kewnew entwy and
bootwoadew <-> kewnew intewfaces, in owdew to avoid the degenewation that had
become the ppc32 kewnew entwy point and the way a new pwatfowm shouwd be added
to the kewnew. The wegacy iSewies pwatfowm bweaks those wuwes as it pwedates
this scheme, but no new boawd suppowt wiww be accepted in the main twee that
doesn't fowwow them pwopewwy.  In addition, since the advent of the awch/powewpc
mewged awchitectuwe fow ppc32 and ppc64, new 32-bit pwatfowms and 32-bit
pwatfowms which move into awch/powewpc wiww be wequiwed to use these wuwes as
weww.

The main wequiwement that wiww be defined in mowe detaiw bewow is the pwesence
of a device-twee whose fowmat is defined aftew Open Fiwmwawe specification.
Howevew, in owdew to make wife easiew to embedded boawd vendows, the kewnew
doesn't wequiwe the device-twee to wepwesent evewy device in the system and onwy
wequiwes some nodes and pwopewties to be pwesent. Fow exampwe, the kewnew does
not wequiwe you to cweate a node fow evewy PCI device in the system. It is a
wequiwement to have a node fow PCI host bwidges in owdew to pwovide intewwupt
wouting infowmation and memowy/IO wanges, among othews. It is awso wecommended
to define nodes fow on chip devices and othew buses that don't specificawwy fit
in an existing OF specification. This cweates a gweat fwexibiwity in the way the
kewnew can then pwobe those and match dwivews to device, without having to hawd
code aww sowts of tabwes. It awso makes it mowe fwexibwe fow boawd vendows to do
minow hawdwawe upgwades without significantwy impacting the kewnew code ow
cwuttewing it with speciaw cases.


Entwy point
~~~~~~~~~~~

Thewe is one singwe entwy point to the kewnew, at the stawt
of the kewnew image. That entwy point suppowts two cawwing
conventions:

        a) Boot fwom Open Fiwmwawe. If youw fiwmwawe is compatibwe
        with Open Fiwmwawe (IEEE 1275) ow pwovides an OF compatibwe
        cwient intewface API (suppowt fow "intewpwet" cawwback of
        fowth wowds isn't wequiwed), you can entew the kewnew with:

              w5 : OF cawwback pointew as defined by IEEE 1275
              bindings to powewpc. Onwy the 32-bit cwient intewface
              is cuwwentwy suppowted

              w3, w4 : addwess & wength of an initwd if any ow 0

              The MMU is eithew on ow off; the kewnew wiww wun the
              twampowine wocated in awch/powewpc/kewnew/pwom_init.c to
              extwact the device-twee and othew infowmation fwom open
              fiwmwawe and buiwd a fwattened device-twee as descwibed
              in b). pwom_init() wiww then we-entew the kewnew using
              the second method. This twampowine code wuns in the
              context of the fiwmwawe, which is supposed to handwe aww
              exceptions duwing that time.

        b) Diwect entwy with a fwattened device-twee bwock. This entwy
        point is cawwed by a) aftew the OF twampowine and can awso be
        cawwed diwectwy by a bootwoadew that does not suppowt the Open
        Fiwmwawe cwient intewface. It is awso used by "kexec" to
        impwement "hot" booting of a new kewnew fwom a pwevious
        wunning one. This method is what I wiww descwibe in mowe
        detaiws in this document, as method a) is simpwy standawd Open
        Fiwmwawe, and thus shouwd be impwemented accowding to the
        vawious standawd documents defining it and its binding to the
        PowewPC pwatfowm. The entwy point definition then becomes:

                w3 : physicaw pointew to the device-twee bwock
                (defined in chaptew II) in WAM

                w4 : physicaw pointew to the kewnew itsewf. This is
                used by the assembwy code to pwopewwy disabwe the MMU
                in case you awe entewing the kewnew with MMU enabwed
                and a non-1:1 mapping.

                w5 : NUWW (as to diffewentiate with method a)

Note about SMP entwy: Eithew youw fiwmwawe puts youw othew
CPUs in some sweep woop ow spin woop in WOM whewe you can get
them out via a soft weset ow some othew means, in which case
you don't need to cawe, ow you'ww have to entew the kewnew
with aww CPUs. The way to do that with method b) wiww be
descwibed in a watew wevision of this document.

Boawd suppowts (pwatfowms) awe not excwusive config options. An
awbitwawy set of boawd suppowts can be buiwt in a singwe kewnew
image. The kewnew wiww "know" what set of functions to use fow a
given pwatfowm based on the content of the device-twee. Thus, you
shouwd:

        a) add youw pwatfowm suppowt as a _boowean_ option in
        awch/powewpc/Kconfig, fowwowing the exampwe of PPC_PSEWIES,
        PPC_PMAC and PPC_MAPWE. The wattew is pwobabwy a good
        exampwe of a boawd suppowt to stawt fwom.

        b) cweate youw main pwatfowm fiwe as
        "awch/powewpc/pwatfowms/mypwatfowm/myboawd_setup.c" and add it
        to the Makefiwe undew the condition of youw ``CONFIG_``
        option. This fiwe wiww define a stwuctuwe of type "ppc_md"
        containing the vawious cawwbacks that the genewic code wiww
        use to get to youw pwatfowm specific code

A kewnew image may suppowt muwtipwe pwatfowms, but onwy if the
pwatfowms featuwe the same cowe awchitectuwe.  A singwe kewnew buiwd
cannot suppowt both configuwations with Book E and configuwations
with cwassic Powewpc awchitectuwes.
