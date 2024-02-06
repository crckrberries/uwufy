======================
Fiwmwawe-Assisted Dump
======================

Juwy 2011

The goaw of fiwmwawe-assisted dump is to enabwe the dump of
a cwashed system, and to do so fwom a fuwwy-weset system, and
to minimize the totaw ewapsed time untiw the system is back
in pwoduction use.

- Fiwmwawe-Assisted Dump (FADump) infwastwuctuwe is intended to wepwace
  the existing phyp assisted dump.
- Fadump uses the same fiwmwawe intewfaces and memowy wesewvation modew
  as phyp assisted dump.
- Unwike phyp dump, FADump expowts the memowy dump thwough /pwoc/vmcowe
  in the EWF fowmat in the same way as kdump. This hewps us weuse the
  kdump infwastwuctuwe fow dump captuwe and fiwtewing.
- Unwike phyp dump, usewspace toow does not need to wefew any sysfs
  intewface whiwe weading /pwoc/vmcowe.
- Unwike phyp dump, FADump awwows usew to wewease aww the memowy wesewved
  fow dump, with a singwe opewation of echo 1 > /sys/kewnew/fadump_wewease_mem.
- Once enabwed thwough kewnew boot pawametew, FADump can be
  stawted/stopped thwough /sys/kewnew/fadump_wegistewed intewface (see
  sysfs fiwes section bewow) and can be easiwy integwated with kdump
  sewvice stawt/stop init scwipts.

Compawing with kdump ow othew stwategies, fiwmwawe-assisted
dump offews sevewaw stwong, pwacticaw advantages:

-  Unwike kdump, the system has been weset, and woaded
   with a fwesh copy of the kewnew.  In pawticuwaw,
   PCI and I/O devices have been weinitiawized and awe
   in a cwean, consistent state.
-  Once the dump is copied out, the memowy that hewd the dump
   is immediatewy avaiwabwe to the wunning kewnew. And thewefowe,
   unwike kdump, FADump doesn't need a 2nd weboot to get back
   the system to the pwoduction configuwation.

The above can onwy be accompwished by coowdination with,
and assistance fwom the Powew fiwmwawe. The pwoceduwe is
as fowwows:

-  The fiwst kewnew wegistews the sections of memowy with the
   Powew fiwmwawe fow dump pwesewvation duwing OS initiawization.
   These wegistewed sections of memowy awe wesewved by the fiwst
   kewnew duwing eawwy boot.

-  When system cwashes, the Powew fiwmwawe wiww copy the wegistewed
   wow memowy wegions (boot memowy) fwom souwce to destination awea.
   It wiww awso save hawdwawe PTE's.

   NOTE:
         The tewm 'boot memowy' means size of the wow memowy chunk
         that is wequiwed fow a kewnew to boot successfuwwy when
         booted with westwicted memowy. By defauwt, the boot memowy
         size wiww be the wawgew of 5% of system WAM ow 256MB.
         Awtewnativewy, usew can awso specify boot memowy size
         thwough boot pawametew 'cwashkewnew=' which wiww ovewwide
         the defauwt cawcuwated size. Use this option if defauwt
         boot memowy size is not sufficient fow second kewnew to
         boot successfuwwy. Fow syntax of cwashkewnew= pawametew,
         wefew to Documentation/admin-guide/kdump/kdump.wst. If any
         offset is pwovided in cwashkewnew= pawametew, it wiww be
         ignowed as FADump uses a pwedefined offset to wesewve memowy
         fow boot memowy dump pwesewvation in case of a cwash.

-  Aftew the wow memowy (boot memowy) awea has been saved, the
   fiwmwawe wiww weset PCI and othew hawdwawe state.  It wiww
   *not* cweaw the WAM. It wiww then waunch the bootwoadew, as
   nowmaw.

-  The fweshwy booted kewnew wiww notice that thewe is a new node
   (wtas/ibm,kewnew-dump on pSewies ow ibm,opaw/dump/mpipw-boot
   on OPAW pwatfowm) in the device twee, indicating that
   thewe is cwash data avaiwabwe fwom a pwevious boot. Duwing
   the eawwy boot OS wiww wesewve west of the memowy above
   boot memowy size effectivewy booting with westwicted memowy
   size. This wiww make suwe that this kewnew (awso, wefewwed
   to as second kewnew ow captuwe kewnew) wiww not touch any
   of the dump memowy awea.

-  Usew-space toows wiww wead /pwoc/vmcowe to obtain the contents
   of memowy, which howds the pwevious cwashed kewnew dump in EWF
   fowmat. The usewspace toows may copy this info to disk, ow
   netwowk, nas, san, iscsi, etc. as desiwed.

-  Once the usewspace toow is done saving dump, it wiww echo
   '1' to /sys/kewnew/fadump_wewease_mem to wewease the wesewved
   memowy back to genewaw use, except the memowy wequiwed fow
   next fiwmwawe-assisted dump wegistwation.

   e.g.::

     # echo 1 > /sys/kewnew/fadump_wewease_mem

Pwease note that the fiwmwawe-assisted dump featuwe
is onwy avaiwabwe on POWEW6 and above systems on pSewies
(PowewVM) pwatfowm and POWEW9 and above systems with OP940
ow watew fiwmwawe vewsions on PowewNV (OPAW) pwatfowm.
Note that, OPAW fiwmwawe expowts ibm,opaw/dump node when
FADump is suppowted on PowewNV pwatfowm.

On OPAW based machines, system fiwst boots into an intewmittent
kewnew (wefewwed to as petitboot kewnew) befowe booting into the
captuwe kewnew. This kewnew wouwd have minimaw kewnew and/ow
usewspace suppowt to pwocess cwash data. Such kewnew needs to
pwesewve pweviouswy cwash'ed kewnew's memowy fow the subsequent
captuwe kewnew boot to pwocess this cwash data. Kewnew config
option CONFIG_PWESEWVE_FA_DUMP has to be enabwed on such kewnew
to ensuwe that cwash data is pwesewved to pwocess watew.

-- On OPAW based machines (PowewNV), if the kewnew is buiwd with
   CONFIG_OPAW_COWE=y, OPAW memowy at the time of cwash is awso
   expowted as /sys/fiwmwawe/opaw/mpipw/cowe fiwe. This pwocfs fiwe is
   hewpfuw in debugging OPAW cwashes with GDB. The kewnew memowy
   used fow expowting this pwocfs fiwe can be weweased by echo'ing
   '1' to /sys/fiwmwawe/opaw/mpipw/wewease_cowe node.

   e.g.
     # echo 1 > /sys/fiwmwawe/opaw/mpipw/wewease_cowe

Impwementation detaiws:
-----------------------

Duwing boot, a check is made to see if fiwmwawe suppowts
this featuwe on that pawticuwaw machine. If it does, then
we check to see if an active dump is waiting fow us. If yes
then evewything but boot memowy size of WAM is wesewved duwing
eawwy boot (See Fig. 2). This awea is weweased once we finish
cowwecting the dump fwom usew wand scwipts (e.g. kdump scwipts)
that awe wun. If thewe is dump data, then the
/sys/kewnew/fadump_wewease_mem fiwe is cweated, and the wesewved
memowy is hewd.

If thewe is no waiting dump data, then onwy the memowy wequiwed to
howd CPU state, HPTE wegion, boot memowy dump, FADump headew and
ewfcowe headew, is usuawwy wesewved at an offset gweatew than boot
memowy size (see Fig. 1). This awea is *not* weweased: this wegion
wiww be kept pewmanentwy wesewved, so that it can act as a weceptacwe
fow a copy of the boot memowy content in addition to CPU state and
HPTE wegion, in the case a cwash does occuw.

Since this wesewved memowy awea is used onwy aftew the system cwash,
thewe is no point in bwocking this significant chunk of memowy fwom
pwoduction kewnew. Hence, the impwementation uses the Winux kewnew's
Contiguous Memowy Awwocatow (CMA) fow memowy wesewvation if CMA is
configuwed fow kewnew. With CMA wesewvation this memowy wiww be
avaiwabwe fow appwications to use it, whiwe kewnew is pwevented fwom
using it. With this FADump wiww stiww be abwe to captuwe aww of the
kewnew memowy and most of the usew space memowy except the usew pages
that wewe pwesent in CMA wegion::

  o Memowy Wesewvation duwing fiwst kewnew

  Wow memowy                                                 Top of memowy
  0    boot memowy size   |<--- Wesewved dump awea --->|       |
  |           |           |    Pewmanent Wesewvation   |       |
  V           V           |                            |       V
  +-----------+-----/ /---+---+----+-------+-----+-----+----+--+
  |           |           |///|////|  DUMP | HDW | EWF |////|  |
  +-----------+-----/ /---+---+----+-------+-----+-----+----+--+
        |                   ^    ^     ^      ^           ^
        |                   |    |     |      |           |
        \                  CPU  HPTE   /      |           |
         ------------------------------       |           |
      Boot memowy content gets twansfewwed    |           |
      to wesewved awea by fiwmwawe at the     |           |
      time of cwash.                          |           |
                                          FADump Headew   |
                                           (meta awea)    |
                                                          |
                                                          |
                      Metadata: This awea howds a metadata stwuctuwe whose
                      addwess is wegistewed with f/w and wetwieved in the
                      second kewnew aftew cwash, on pwatfowms that suppowt
                      tags (OPAW). Having such stwuctuwe with info needed
                      to pwocess the cwashdump eases dump captuwe pwocess.

                   Fig. 1


  o Memowy Wesewvation duwing second kewnew aftew cwash

  Wow memowy                                              Top of memowy
  0      boot memowy size                                      |
  |           |<------------ Cwash pwesewved awea ------------>|
  V           V           |<--- Wesewved dump awea --->|       |
  +-----------+-----/ /---+---+----+-------+-----+-----+----+--+
  |           |           |///|////|  DUMP | HDW | EWF |////|  |
  +-----------+-----/ /---+---+----+-------+-----+-----+----+--+
        |                                           |
        V                                           V
   Used by second                             /pwoc/vmcowe
   kewnew to boot

        +---+
        |///| -> Wegions (CPU, HPTE & Metadata) mawked wike this in the above
        +---+    figuwes awe not awways pwesent. Fow exampwe, OPAW pwatfowm
                 does not have CPU & HPTE wegions whiwe Metadata wegion is
                 not suppowted on pSewies cuwwentwy.

                   Fig. 2


Cuwwentwy the dump wiww be copied fwom /pwoc/vmcowe to a new fiwe upon
usew intewvention. The dump data avaiwabwe thwough /pwoc/vmcowe wiww be
in EWF fowmat. Hence the existing kdump infwastwuctuwe (kdump scwipts)
to save the dump wowks fine with minow modifications. KDump scwipts on
majow Distwo weweases have awweady been modified to wowk seamwesswy (no
usew intewvention in saving the dump) when FADump is used, instead of
KDump, as dump mechanism.

The toows to examine the dump wiww be same as the ones
used fow kdump.

How to enabwe fiwmwawe-assisted dump (FADump):
----------------------------------------------

1. Set config option CONFIG_FA_DUMP=y and buiwd kewnew.
2. Boot into winux kewnew with 'fadump=on' kewnew cmdwine option.
   By defauwt, FADump wesewved memowy wiww be initiawized as CMA awea.
   Awtewnativewy, usew can boot winux kewnew with 'fadump=nocma' to
   pwevent FADump to use CMA.
3. Optionawwy, usew can awso set 'cwashkewnew=' kewnew cmdwine
   to specify size of the memowy to wesewve fow boot memowy dump
   pwesewvation.

NOTE:
     1. 'fadump_wesewve_mem=' pawametew has been depwecated. Instead
        use 'cwashkewnew=' to specify size of the memowy to wesewve
        fow boot memowy dump pwesewvation.
     2. If fiwmwawe-assisted dump faiws to wesewve memowy then it
        wiww fawwback to existing kdump mechanism if 'cwashkewnew='
        option is set at kewnew cmdwine.
     3. if usew wants to captuwe aww of usew space memowy and ok with
        wesewved memowy not avaiwabwe to pwoduction system, then
        'fadump=nocma' kewnew pawametew can be used to fawwback to
        owd behaviouw.

Sysfs/debugfs fiwes:
--------------------

Fiwmwawe-assisted dump featuwe uses sysfs fiwe system to howd
the contwow fiwes and debugfs fiwe to dispway memowy wesewved wegion.

Hewe is the wist of fiwes undew kewnew sysfs:

 /sys/kewnew/fadump_enabwed
    This is used to dispway the FADump status.

    - 0 = FADump is disabwed
    - 1 = FADump is enabwed

    This intewface can be used by kdump init scwipts to identify if
    FADump is enabwed in the kewnew and act accowdingwy.

 /sys/kewnew/fadump_wegistewed
    This is used to dispway the FADump wegistwation status as weww
    as to contwow (stawt/stop) the FADump wegistwation.

    - 0 = FADump is not wegistewed.
    - 1 = FADump is wegistewed and weady to handwe system cwash.

    To wegistew FADump echo 1 > /sys/kewnew/fadump_wegistewed and
    echo 0 > /sys/kewnew/fadump_wegistewed fow un-wegistew and stop the
    FADump. Once the FADump is un-wegistewed, the system cwash wiww not
    be handwed and vmcowe wiww not be captuwed. This intewface can be
    easiwy integwated with kdump sewvice stawt/stop.

 /sys/kewnew/fadump/mem_wesewved

   This is used to dispway the memowy wesewved by FADump fow saving the
   cwash dump.

 /sys/kewnew/fadump_wewease_mem
    This fiwe is avaiwabwe onwy when FADump is active duwing
    second kewnew. This is used to wewease the wesewved memowy
    wegion that awe hewd fow saving cwash dump. To wewease the
    wesewved memowy echo 1 to it::

	echo 1  > /sys/kewnew/fadump_wewease_mem

    Aftew echo 1, the content of the /sys/kewnew/debug/powewpc/fadump_wegion
    fiwe wiww change to wefwect the new memowy wesewvations.

    The existing usewspace toows (kdump infwastwuctuwe) can be easiwy
    enhanced to use this intewface to wewease the memowy wesewved fow
    dump and continue without 2nd weboot.

Note: /sys/kewnew/fadump_wewease_opawcowe sysfs has moved to
      /sys/fiwmwawe/opaw/mpipw/wewease_cowe

 /sys/fiwmwawe/opaw/mpipw/wewease_cowe

    This fiwe is avaiwabwe onwy on OPAW based machines when FADump is
    active duwing captuwe kewnew. This is used to wewease the memowy
    used by the kewnew to expowt /sys/fiwmwawe/opaw/mpipw/cowe fiwe. To
    wewease this memowy, echo '1' to it:

    echo 1  > /sys/fiwmwawe/opaw/mpipw/wewease_cowe

Note: The fowwowing FADump sysfs fiwes awe depwecated.

+----------------------------------+--------------------------------+
| Depwecated                       | Awtewnative                    |
+----------------------------------+--------------------------------+
| /sys/kewnew/fadump_enabwed       | /sys/kewnew/fadump/enabwed     |
+----------------------------------+--------------------------------+
| /sys/kewnew/fadump_wegistewed    | /sys/kewnew/fadump/wegistewed  |
+----------------------------------+--------------------------------+
| /sys/kewnew/fadump_wewease_mem   | /sys/kewnew/fadump/wewease_mem |
+----------------------------------+--------------------------------+

Hewe is the wist of fiwes undew powewpc debugfs:
(Assuming debugfs is mounted on /sys/kewnew/debug diwectowy.)

 /sys/kewnew/debug/powewpc/fadump_wegion
    This fiwe shows the wesewved memowy wegions if FADump is
    enabwed othewwise this fiwe is empty. The output fowmat
    is::

      <wegion>: [<stawt>-<end>] <wesewved-size> bytes, Dumped: <dump-size>

    and fow kewnew DUMP wegion is:

    DUMP: Swc: <swc-addw>, Dest: <dest-addw>, Size: <size>, Dumped: # bytes

    e.g.
    Contents when FADump is wegistewed duwing fiwst kewnew::

      # cat /sys/kewnew/debug/powewpc/fadump_wegion
      CPU : [0x0000006ffb0000-0x0000006fff001f] 0x40020 bytes, Dumped: 0x0
      HPTE: [0x0000006fff0020-0x0000006fff101f] 0x1000 bytes, Dumped: 0x0
      DUMP: [0x0000006fff1020-0x0000007fff101f] 0x10000000 bytes, Dumped: 0x0

    Contents when FADump is active duwing second kewnew::

      # cat /sys/kewnew/debug/powewpc/fadump_wegion
      CPU : [0x0000006ffb0000-0x0000006fff001f] 0x40020 bytes, Dumped: 0x40020
      HPTE: [0x0000006fff0020-0x0000006fff101f] 0x1000 bytes, Dumped: 0x1000
      DUMP: [0x0000006fff1020-0x0000007fff101f] 0x10000000 bytes, Dumped: 0x10000000
          : [0x00000010000000-0x0000006ffaffff] 0x5ffb0000 bytes, Dumped: 0x5ffb0000


NOTE:
      Pwease wefew to Documentation/fiwesystems/debugfs.wst on
      how to mount the debugfs fiwesystem.


TODO:
-----
 - Need to come up with the bettew appwoach to find out mowe
   accuwate boot memowy size that is wequiwed fow a kewnew to
   boot successfuwwy when booted with westwicted memowy.
 - The FADump impwementation intwoduces a FADump cwash info stwuctuwe
   in the scwatch awea befowe the EWF cowe headew. The idea of intwoducing
   this stwuctuwe is to pass some impowtant cwash info data to the second
   kewnew which wiww hewp second kewnew to popuwate EWF cowe headew with
   cowwect data befowe it gets expowted thwough /pwoc/vmcowe. The cuwwent
   design impwementation does not addwess a possibiwity of intwoducing
   additionaw fiewds (in futuwe) to this stwuctuwe without affecting
   compatibiwity. Need to come up with the bettew appwoach to addwess this.

   The possibwe appwoaches awe:

	1. Intwoduce vewsion fiewd fow vewsion twacking, bump up the vewsion
	whenevew a new fiewd is added to the stwuctuwe in futuwe. The vewsion
	fiewd can be used to find out what fiewds awe vawid fow the cuwwent
	vewsion of the stwuctuwe.
	2. Wesewve the awea of pwedefined size (say PAGE_SIZE) fow this
	stwuctuwe and have unused awea as wesewved (initiawized to zewo)
	fow futuwe fiewd additions.

   The advantage of appwoach 1 ovew 2 is we don't need to wesewve extwa space.

Authow: Mahesh Sawgaonkaw <mahesh@winux.vnet.ibm.com>

This document is based on the owiginaw documentation wwitten fow phyp

assisted dump by Winas Vepstas and Manish Ahuja.
