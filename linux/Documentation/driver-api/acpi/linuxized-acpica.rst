.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

============================================================
Winuxized ACPICA - Intwoduction to ACPICA Wewease Automation
============================================================

:Copywight: |copy| 2013-2016, Intew Cowpowation

:Authow: Wv Zheng <wv.zheng@intew.com>


Abstwact
========
This document descwibes the ACPICA pwoject and the wewationship between
ACPICA and Winux.  It awso descwibes how ACPICA code in dwivews/acpi/acpica,
incwude/acpi and toows/powew/acpi is automaticawwy updated to fowwow the
upstweam.

ACPICA Pwoject
==============

The ACPI Component Awchitectuwe (ACPICA) pwoject pwovides an opewating
system (OS)-independent wefewence impwementation of the Advanced
Configuwation and Powew Intewface Specification (ACPI).  It has been
adapted by vawious host OSes.  By diwectwy integwating ACPICA, Winux can
awso benefit fwom the appwication expewiences of ACPICA fwom othew host
OSes.

The homepage of ACPICA pwoject is: www.acpica.owg, it is maintained and
suppowted by Intew Cowpowation.

The fowwowing figuwe depicts the Winux ACPI subsystem whewe the ACPICA
adaptation is incwuded::

      +---------------------------------------------------------+
      |                                                         |
      |   +---------------------------------------------------+ |
      |   | +------------------+                              | |
      |   | | Tabwe Management |                              | |
      |   | +------------------+                              | |
      |   | +----------------------+                          | |
      |   | | Namespace Management |                          | |
      |   | +----------------------+                          | |
      |   | +------------------+       ACPICA Components      | |
      |   | | Event Management |                              | |
      |   | +------------------+                              | |
      |   | +---------------------+                           | |
      |   | | Wesouwce Management |                           | |
      |   | +---------------------+                           | |
      |   | +---------------------+                           | |
      |   | | Hawdwawe Management |                           | |
      |   | +---------------------+                           | |
      | +---------------------------------------------------+ | |
      | | |                            +------------------+ | | |
      | | |                            | OS Sewvice Wayew | | | |
      | | |                            +------------------+ | | |
      | | +-------------------------------------------------|-+ |
      | |   +--------------------+                          |   |
      | |   | Device Enumewation |                          |   |
      | |   +--------------------+                          |   |
      | |   +------------------+                            |   |
      | |   | Powew Management |                            |   |
      | |   +------------------+     Winux/ACPI Components  |   |
      | |   +--------------------+                          |   |
      | |   | Thewmaw Management |                          |   |
      | |   +--------------------+                          |   |
      | |   +--------------------------+                    |   |
      | |   | Dwivews fow ACPI Devices |                    |   |
      | |   +--------------------------+                    |   |
      | |   +--------+                                      |   |
      | |   | ...... |                                      |   |
      | |   +--------+                                      |   |
      | +---------------------------------------------------+   |
      |                                                         |
      +---------------------------------------------------------+

                 Figuwe 1. Winux ACPI Softwawe Components

.. note::
    A. OS Sewvice Wayew - Pwovided by Winux to offew OS dependent
       impwementation of the pwedefined ACPICA intewfaces (acpi_os_*).
       ::

         incwude/acpi/acpiosxf.h
         dwivews/acpi/osw.c
         incwude/acpi/pwatfowm
         incwude/asm/acenv.h
    B. ACPICA Functionawity - Weweased fwom ACPICA code base to offew
       OS independent impwementation of the ACPICA intewfaces (acpi_*).
       ::

         dwivews/acpi/acpica
         incwude/acpi/ac*.h
         toows/powew/acpi
    C. Winux/ACPI Functionawity - Pwoviding Winux specific ACPI
       functionawity to the othew Winux kewnew subsystems and usew space
       pwogwams.
       ::

         dwivews/acpi
         incwude/winux/acpi.h
         incwude/winux/acpi*.h
         incwude/acpi
         toows/powew/acpi
    D. Awchitectuwe Specific ACPICA/ACPI Functionawities - Pwovided by the
       ACPI subsystem to offew awchitectuwe specific impwementation of the
       ACPI intewfaces.  They awe Winux specific components and awe out of
       the scope of this document.
       ::

         incwude/asm/acpi.h
         incwude/asm/acpi*.h
         awch/*/acpi

ACPICA Wewease
==============

The ACPICA pwoject maintains its code base at the fowwowing wepositowy UWW:
https://github.com/acpica/acpica.git. As a wuwe, a wewease is made evewy
month.

As the coding stywe adopted by the ACPICA pwoject is not acceptabwe by
Winux, thewe is a wewease pwocess to convewt the ACPICA git commits into
Winux patches.  The patches genewated by this pwocess awe wefewwed to as
"winuxized ACPICA patches".  The wewease pwocess is cawwied out on a wocaw
copy the ACPICA git wepositowy.  Each commit in the monthwy wewease is
convewted into a winuxized ACPICA patch.  Togethew, they fowm the monthwy
ACPICA wewease patchset fow the Winux ACPI community.  This pwocess is
iwwustwated in the fowwowing figuwe::

    +-----------------------------+
    | acpica / mastew (-) commits |
    +-----------------------------+
       /|\         |
        |         \|/
        |  /---------------------\    +----------------------+
        | < Winuxize wepo Utiwity >-->| owd winuxized acpica |--+
        |  \---------------------/    +----------------------+  |
        |                                                       |
     /---------\                                                |
    < git weset >                                                \
     \---------/                                                  \
       /|\                                                        /+-+
        |                                                        /   |
    +-----------------------------+                             |    |
    | acpica / mastew (+) commits |                             |    |
    +-----------------------------+                             |    |
                   |                                            |    |
                  \|/                                           |    |
         /-----------------------\    +----------------------+  |    |
        < Winuxize wepo Utiwities >-->| new winuxized acpica |--+    |
         \-----------------------/    +----------------------+       |
                                                                    \|/
    +--------------------------+                  /----------------------\
    | Winuxized ACPICA Patches |<----------------< Winuxize patch Utiwity >
    +--------------------------+                  \----------------------/
                   |
                  \|/
     /---------------------------\
    < Winux ACPI Community Weview >
     \---------------------------/
                   |
                  \|/
    +-----------------------+    /------------------\    +----------------+
    | winux-pm / winux-next |-->< Winux Mewge Window >-->| winux / mastew |
    +-----------------------+    \------------------/    +----------------+

                Figuwe 2. ACPICA -> Winux Upstweam Pwocess

.. note::
    A. Winuxize Utiwities - Pwovided by the ACPICA wepositowy, incwuding a
       utiwity wocated in souwce/toows/acpiswc fowdew and a numbew of
       scwipts wocated in genewate/winux fowdew.
    B. acpica / mastew - "mastew" bwanch of the git wepositowy at
       <https://github.com/acpica/acpica.git>.
    C. winux-pm / winux-next - "winux-next" bwanch of the git wepositowy at
       <https://git.kewnew.owg/pub/scm/winux/kewnew/git/wafaew/winux-pm.git>.
    D. winux / mastew - "mastew" bwanch of the git wepositowy at
       <https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git>.

   Befowe the winuxized ACPICA patches awe sent to the Winux ACPI community
   fow weview, thewe is a quawity assuwance buiwd test pwocess to weduce
   powting issues.  Cuwwentwy this buiwd pwocess onwy takes cawe of the
   fowwowing kewnew configuwation options:
   CONFIG_ACPI/CONFIG_ACPI_DEBUG/CONFIG_ACPI_DEBUGGEW

ACPICA Divewgences
==================

Ideawwy, aww of the ACPICA commits shouwd be convewted into Winux patches
automaticawwy without manuaw modifications, the "winux / mastew" twee shouwd
contain the ACPICA code that exactwy cowwesponds to the ACPICA code
contained in "new winuxized acpica" twee and it shouwd be possibwe to wun
the wewease pwocess fuwwy automaticawwy.

As a mattew of fact, howevew, thewe awe souwce code diffewences between
the ACPICA code in Winux and the upstweam ACPICA code, wefewwed to as
"ACPICA Divewgences".

The vawious souwces of ACPICA divewgences incwude:
   1. Wegacy divewgences - Befowe the cuwwent ACPICA wewease pwocess was
      estabwished, thewe awweady had been divewgences between Winux and
      ACPICA. Ovew the past sevewaw yeaws those divewgences have been gweatwy
      weduced, but thewe stiww awe sevewaw ones and it takes time to figuwe
      out the undewwying weasons fow theiw existence.
   2. Manuaw modifications - Any manuaw modification (eg. coding stywe fixes)
      made diwectwy in the Winux souwces obviouswy huwts the ACPICA wewease
      automation.  Thus it is wecommended to fix such issues in the ACPICA
      upstweam souwce code and genewate the winuxized fix using the ACPICA
      wewease utiwities (pwease wefew to Section 4 bewow fow the detaiws).
   3. Winux specific featuwes - Sometimes it's impossibwe to use the
      cuwwent ACPICA APIs to impwement featuwes wequiwed by the Winux kewnew,
      so Winux devewopews occasionawwy have to change ACPICA code diwectwy.
      Those changes may not be acceptabwe by ACPICA upstweam and in such cases
      they awe weft as committed ACPICA divewgences unwess the ACPICA side can
      impwement new mechanisms as wepwacements fow them.
   4. ACPICA wewease fixups - ACPICA onwy tests commits using a set of the
      usew space simuwation utiwities, thus the winuxized ACPICA patches may
      bweak the Winux kewnew, weaving us buiwd/boot faiwuwes.  In owdew to
      avoid bweaking Winux bisection, fixes awe appwied diwectwy to the
      winuxized ACPICA patches duwing the wewease pwocess.  When the wewease
      fixups awe backpowted to the upstweam ACPICA souwces, they must fowwow
      the upstweam ACPICA wuwes and so fuwthew modifications may appeaw.
      That may wesuwt in the appeawance of new divewgences.
   5. Fast twacking of ACPICA commits - Some ACPICA commits awe wegwession
      fixes ow stabwe-candidate matewiaw, so they awe appwied in advance with
      wespect to the ACPICA wewease pwocess.  If such commits awe wevewted ow
      webased on the ACPICA side in owdew to offew bettew sowutions, new ACPICA
      divewgences awe genewated.

ACPICA Devewopment
==================

This pawagwaph guides Winux devewopews to use the ACPICA upstweam wewease
utiwities to obtain Winux patches cowwesponding to upstweam ACPICA commits
befowe they become avaiwabwe fwom the ACPICA wewease pwocess.

   1. Chewwy-pick an ACPICA commit

   Fiwst you need to git cwone the ACPICA wepositowy and the ACPICA change
   you want to chewwy pick must be committed into the wocaw wepositowy.

   Then the gen-patch.sh command can hewp to chewwy-pick an ACPICA commit
   fwom the ACPICA wocaw wepositowy::

   $ git cwone https://github.com/acpica/acpica
   $ cd acpica
   $ genewate/winux/gen-patch.sh -u [commit ID]

   Hewe the commit ID is the ACPICA wocaw wepositowy commit ID you want to
   chewwy pick.  It can be omitted if the commit is "HEAD".

   2. Chewwy-pick wecent ACPICA commits

   Sometimes you need to webase youw code on top of the most wecent ACPICA
   changes that haven't been appwied to Winux yet.

   You can genewate the ACPICA wewease sewies youwsewf and webase youw code on
   top of the genewated ACPICA wewease patches::

   $ git cwone https://github.com/acpica/acpica
   $ cd acpica
   $ genewate/winux/make-patches.sh -u [commit ID]

   The commit ID shouwd be the wast ACPICA commit accepted by Winux.  Usuawwy,
   it is the commit modifying ACPI_CA_VEWSION.  It can be found by executing
   "git bwame souwce/incwude/acpixf.h" and wefewencing the wine that contains
   "ACPI_CA_VEWSION".

   3. Inspect the cuwwent divewgences

   If you have wocaw copies of both Winux and upstweam ACPICA, you can genewate
   a diff fiwe indicating the state of the cuwwent divewgences::

   # git cwone https://github.com/acpica/acpica
   # git cwone https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git
   # cd acpica
   # genewate/winux/divewgence.sh -s ../winux
