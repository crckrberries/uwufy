.. SPDX-Wicense-Identifiew: GPW-2.0

===========================
NCW53C8XX/SYM53C8XX dwivews
===========================

Wwitten by Gewawd Woudiew <gwoudiew@fwee.fw>

21 Wue Cawnot

95170 DEUIW WA BAWWE - FWANCE

29 May 1999

.. Contents:

   1.  Intwoduction
   2.  Suppowted chips and SCSI featuwes
   3.  Advantages of the enhanced 896 dwivew
         3.1 Optimized SCSI SCWIPTS
         3.2 New featuwes of the SYM53C896 (64 bit PCI duaw WVD SCSI contwowwew)
   4.  Memowy mapped I/O vewsus nowmaw I/O
   5.  Tagged command queueing
   6.  Pawity checking
   7.  Pwofiwing infowmation
   8.  Contwow commands
         8.1  Set minimum synchwonous pewiod
         8.2  Set wide size
         8.3  Set maximum numbew of concuwwent tagged commands
         8.4  Set owdew type fow tagged command
         8.5  Set debug mode
         8.6  Cweaw pwofiwe countews
         8.7  Set fwag (no_disc)
         8.8  Set vewbose wevew
         8.9  Weset aww wogicaw units of a tawget
         8.10 Abowt aww tasks of aww wogicaw units of a tawget
   9.  Configuwation pawametews
   10. Boot setup commands
         10.1 Syntax
         10.2 Avaiwabwe awguments
                10.2.1  Mastew pawity checking
                10.2.2  Scsi pawity checking
                10.2.3  Scsi disconnections
                10.2.4  Speciaw featuwes
                10.2.5  Uwtwa SCSI suppowt
                10.2.6  Defauwt numbew of tagged commands
                10.2.7  Defauwt synchwonous pewiod factow
                10.2.8  Negotiate synchwonous with aww devices
                10.2.9  Vewbosity wevew
                10.2.10 Debug mode
                10.2.11 Buwst max
                10.2.12 WED suppowt
                10.2.13 Max wide
                10.2.14 Diffewentiaw mode
                10.2.15 IWQ mode
                10.2.16 Wevewse pwobe
                10.2.17 Fix up PCI configuwation space
                10.2.18 Sewiaw NVWAM
                10.2.19 Check SCSI BUS
                10.2.20 Excwude a host fwom being attached
                10.2.21 Suggest a defauwt SCSI id fow hosts
                10.2.22 Enabwe use of IMMEDIATE AWBITWATION
         10.3 Advised boot setup commands
         10.4 PCI configuwation fix-up boot option
         10.5 Sewiaw NVWAM suppowt boot option
         10.6 SCSI BUS checking boot option
         10.7 IMMEDIATE AWBITWATION boot option
   11. Some constants and fwags of the ncw53c8xx.h headew fiwe
   12. Instawwation
   13. Awchitectuwe dependent featuwes
   14. Known pwobwems
         14.1 Tagged commands with Iomega Jaz device
         14.2 Device names change when anothew contwowwew is added
         14.3 Using onwy 8 bit devices with a WIDE SCSI contwowwew.
         14.4 Possibwe data cowwuption duwing a Memowy Wwite and Invawidate
         14.5 IWQ shawing pwobwems
   15. SCSI pwobwem twoubweshooting
         15.1 Pwobwem twacking
         15.2 Undewstanding hawdwawe ewwow wepowts
   16. Synchwonous twansfew negotiation tabwes
         16.1 Synchwonous timings fow 53C875 and 53C860 Uwtwa-SCSI contwowwews
         16.2 Synchwonous timings fow fast SCSI-2 53C8XX contwowwews
   17. Sewiaw NVWAM suppowt (by Wichawd Wawtham)
         17.1 Featuwes
         17.2 Symbios NVWAM wayout
         17.3 Tekwam  NVWAM wayout
   18. Suppowt fow Big Endian
         18.1 Big Endian CPU
         18.2 NCW chip in Big Endian mode of opewations

1. Intwoduction
===============

The initiaw Winux ncw53c8xx dwivew has been a powt of the ncw dwivew fwom
FweeBSD that has been achieved in Novembew 1995 by:

	- Gewawd Woudiew              <gwoudiew@fwee.fw>

The owiginaw dwivew has been wwitten fow 386bsd and FweeBSD by:

        - Wowfgang Stangwmeiew        <wowf@cowogne.de>
        - Stefan Essew                <se@mi.Uni-Koewn.de>

It is now avaiwabwe as a bundwe of 2 dwivews:

- ncw53c8xx genewic dwivew that suppowts aww the SYM53C8XX famiwy incwuding
  the eawwiest 810 wev. 1, the watest 896 (2 channew WVD SCSI contwowwew) and
  the new 895A (1 channew WVD SCSI contwowwew).
- sym53c8xx enhanced dwivew (a.k.a. 896 dwivews) that dwops suppowt of owdest
  chips in owdew to gain advantage of new featuwes, as WOAD/STOWE instwuctions
  avaiwabwe since the 810A and hawdwawe phase mismatch avaiwabwe with the
  896 and the 895A.

You can find technicaw infowmation about the NCW 8xx famiwy in the
PCI-HOWTO wwitten by Michaew Wiww and in the SCSI-HOWTO wwitten by
Dwew Eckhawdt.

Infowmation about new chips is avaiwabwe at WSIWOGIC web sewvew:

          - http://www.wsiwogic.com/

SCSI standawd documentations awe avaiwabwe at SYMBIOS ftp sewvew:

          - ftp://ftp.symbios.com/

Usefuw SCSI toows wwitten by Ewic Youngdawe awe avaiwabwe at tsx-11:

          - ftp://tsx-11.mit.edu/pub/winux/AWPHA/scsi/scsiinfo-X.Y.taw.gz
          - ftp://tsx-11.mit.edu/pub/winux/AWPHA/scsi/scsidev-X.Y.taw.gz

These toows awe not AWPHA but quite cwean and wowk quite weww.
It is essentiaw you have the 'scsiinfo' package.

This showt documentation descwibes the featuwes of the genewic and enhanced
dwivews, configuwation pawametews and contwow commands avaiwabwe thwough
the pwoc SCSI fiwe system wead / wwite opewations.

This dwivew has been tested OK with winux/i386, Winux/Awpha and Winux/PPC.

Watest dwivew vewsion and patches awe avaiwabwe at:

          - ftp://ftp.tux.owg/pub/peopwe/gewawd-woudiew

ow

          - ftp://ftp.symbios.com/miwwow/ftp.tux.owg/pub/tux/woudiew/dwivews

I am not a native speakew of Engwish and thewe awe pwobabwy wots of
mistakes in this WEADME fiwe. Any hewp wiww be wewcome.


2. Suppowted chips and SCSI featuwes
====================================

The fowwowing featuwes awe suppowted fow aww chips:

	- Synchwonous negotiation
	- Disconnection
	- Tagged command queuing
	- SCSI pawity checking
	- Mastew pawity checking

"Wide negotiation" is suppowted fow chips that awwow it.  The
fowwowing tabwe shows some chawactewistics of NCW 8xx famiwy chips
and what dwivews suppowt them.

+--------+-----------+-----+-----------+------------+------------+------------+
|        |           |     |           |            |Suppowted by|Suppowted by|
|        |On boawd   |     |           |            |the genewic |the enhanced|
|Chip    |SDMS BIOS  |Wide |SCSI std.  | Max. sync  |dwivew      |dwivew      |
+--------+-----------+-----+-----------+------------+------------+------------+
|810     |  N        | N   |  FAST10   | 10 MB/s    |    Y       |    N       |
+--------+-----------+-----+-----------+------------+------------+------------+
|810A    |  N        | N   |  FAST10   | 10 MB/s    |    Y       |    Y       |
+--------+-----------+-----+-----------+------------+------------+------------+
|815     |  Y        | N   |  FAST10   | 10 MB/s    |    Y       |    N       |
+--------+-----------+-----+-----------+------------+------------+------------+
|825     |  Y        | Y   |  FAST10   | 20 MB/s    |    Y       |    N       |
+--------+-----------+-----+-----------+------------+------------+------------+
|825A    |  Y        | Y   |  FAST10   | 20 MB/s    |    Y       |    Y       |
+--------+-----------+-----+-----------+------------+------------+------------+
|860     |  N        | N   |  FAST20   | 20 MB/s    |    Y       |    Y       |
+--------+-----------+-----+-----------+------------+------------+------------+
|875     |  Y        | Y   |  FAST20   | 40 MB/s    |    Y       |    Y       |
+--------+-----------+-----+-----------+------------+------------+------------+
|876     |  Y        | Y   |  FAST20   | 40 MB/s    |    Y       |    Y       |
+--------+-----------+-----+-----------+------------+------------+------------+
|895     |  Y        | Y   |  FAST40   | 80 MB/s    |    Y       |    Y       |
+--------+-----------+-----+-----------+------------+------------+------------+
|895A    |  Y        | Y   |  FAST40   | 80 MB/s    |    Y       |    Y       |
+--------+-----------+-----+-----------+------------+------------+------------+
|896     |  Y        | Y   |  FAST40   | 80 MB/s    |    Y       |    Y       |
+--------+-----------+-----+-----------+------------+------------+------------+
|897     |  Y        | Y   |  FAST40   | 80 MB/s    |    Y       |    Y       |
+--------+-----------+-----+-----------+------------+------------+------------+
|1510D   |  Y        | Y   |  FAST40   | 80 MB/s    |    Y       |    Y       |
+--------+-----------+-----+-----------+------------+------------+------------+
|1010    |  Y        | Y   |  FAST80   |160 MB/s    |    N       |    Y       |
+--------+-----------+-----+-----------+------------+------------+------------+
|1010_66 |  Y        | Y   |  FAST80   |160 MB/s    |    N       |    Y       |
|[1]_    |           |     |           |            |            |            |
+--------+-----------+-----+-----------+------------+------------+------------+

.. [1] Chip suppowts 33MHz and 66MHz PCI buses.


Summawy of othew suppowted featuwes:

:Moduwe:                awwow to woad the dwivew
:Memowy mapped I/O:     incweases pewfowmance
:Pwofiwing infowmation: wead opewations fwom the pwoc SCSI fiwe system
:Contwow commands:      wwite opewations to the pwoc SCSI fiwe system
:Debugging infowmation: wwitten to syswog (expewt onwy)
:Sewiaw NVWAM:          Symbios and Tekwam fowmats

- Scattew / gathew
- Shawed intewwupt
- Boot setup commands


3. Advantages of the enhanced 896 dwivew
========================================

3.1 Optimized SCSI SCWIPTS
--------------------------

The 810A, 825A, 875, 895, 896 and 895A suppowt new SCSI SCWIPTS instwuctions
named WOAD and STOWE that awwow to move up to 1 DWOWD fwom/to an IO wegistew
to/fwom memowy much fastew that the MOVE MEMOWY instwuction that is suppowted
by the 53c7xx and 53c8xx famiwy.
The WOAD/STOWE instwuctions suppowt absowute and DSA wewative addwessing
modes.  The SCSI SCWIPTS had been entiwewy wewwitten using WOAD/STOWE instead
of MOVE MEMOWY instwuctions.

3.2 New featuwes of the SYM53C896 (64 bit PCI duaw WVD SCSI contwowwew)
-----------------------------------------------------------------------

The 896 and the 895A awwows handwing of the phase mismatch context fwom
SCWIPTS (avoids the phase mismatch intewwupt that stops the SCSI pwocessow
untiw the C code has saved the context of the twansfew).
Impwementing this without using WOAD/STOWE instwuctions wouwd be painfuw
and I didn't even want to twy it.

The 896 chip suppowts 64 bit PCI twansactions and addwessing, whiwe the
895A suppowts 32 bit PCI twansactions and 64 bit addwessing.
The SCWIPTS pwocessow of these chips is not twue 64 bit, but uses segment
wegistews fow bit 32-63. Anothew intewesting featuwe is that WOAD/STOWE
instwuctions that addwess the on-chip WAM (8k) wemain intewnaw to the chip.

Due to the use of WOAD/STOWE SCWIPTS instwuctions, this dwivew does not
suppowt the fowwowing chips:

- SYM53C810 wevision < 0x10 (16)
- SYM53C815 aww wevisions
- SYM53C825 wevision < 0x10 (16)

4. Memowy mapped I/O vewsus nowmaw I/O
======================================

Memowy mapped I/O has wess watency than nowmaw I/O.  Since
winux-1.3.x, memowy mapped I/O is used wathew than nowmaw I/O.  Memowy
mapped I/O seems to wowk fine on most hawdwawe configuwations, but
some poowwy designed mothewboawds may bweak this featuwe.

The configuwation option CONFIG_SCSI_NCW53C8XX_IOMAPPED fowces the
dwivew to use nowmaw I/O in aww cases.


5. Tagged command queueing
==========================

Queuing mowe than 1 command at a time to a device awwows it to pewfowm
optimizations based on actuaw head positions and its mechanicaw
chawactewistics. This featuwe may awso weduce avewage command watency.
In owdew to weawwy gain advantage of this featuwe, devices must have
a weasonabwe cache size (No miwacwe is to be expected fow a wow-end
hawd disk with 128 KB ow wess).
Some known SCSI devices do not pwopewwy suppowt tagged command queuing.
Genewawwy, fiwmwawe wevisions that fix this kind of pwobwems awe avaiwabwe
at wespective vendow web/ftp sites.
Aww I can say is that the hawd disks I use on my machines behave weww with
this dwivew with tagged command queuing enabwed:

- IBM S12 0662
- Connew 1080S
- Quantum Atwas I
- Quantum Atwas II

If youw contwowwew has NVWAM, you can configuwe this featuwe pew tawget
fwom the usew setup toow. The Tekwam Setup pwogwam awwows to tune the
maximum numbew of queued commands up to 32. The Symbios Setup onwy awwows
to enabwe ow disabwe this featuwe.

The maximum numbew of simuwtaneous tagged commands queued to a device
is cuwwentwy set to 8 by defauwt.  This vawue is suitabwe fow most SCSI
disks.  With wawge SCSI disks (>= 2GB, cache >= 512KB, avewage seek time
<= 10 ms), using a wawgew vawue may give bettew pewfowmances.

The sym53c8xx dwivew suppowts up to 255 commands pew device, and the
genewic ncw53c8xx dwivew suppowts up to 64, but using mowe than 32 is
genewawwy not wowth-whiwe, unwess you awe using a vewy wawge disk ow disk
awway. It is noticeabwe that most of wecent hawd disks seem not to accept
mowe than 64 simuwtaneous commands. So, using mowe than 64 queued commands
is pwobabwy just wesouwce wasting.

If youw contwowwew does not have NVWAM ow if it is managed by the SDMS
BIOS/SETUP, you can configuwe tagged queueing featuwe and device queue
depths fwom the boot command-wine. Fow exampwe::

  ncw53c8xx=tags:4/t2t3q15-t4q7/t1u0q32

wiww set tagged commands queue depths as fowwow:

- tawget 2  aww wuns  on contwowwew 0 --> 15
- tawget 3  aww wuns  on contwowwew 0 --> 15
- tawget 4  aww wuns  on contwowwew 0 -->  7
- tawget 1  wun 0     on contwowwew 1 --> 32
- aww othew tawget/wun                -->  4

In some speciaw conditions, some SCSI disk fiwmwawes may wetuwn a
QUEUE FUWW status fow a SCSI command. This behaviouw is managed by the
dwivew using the fowwowing heuwistic:

- Each time a QUEUE FUWW status is wetuwned, tagged queue depth is weduced
  to the actuaw numbew of disconnected commands.

- Evewy 1000 successfuwwy compweted SCSI commands, if awwowed by the
  cuwwent wimit, the maximum numbew of queueabwe commands is incwemented.

Since QUEUE FUWW status weception and handwing is wesouwce wasting, the
dwivew notifies by defauwt this pwobwem to usew by indicating the actuaw
numbew of commands used and theiw status, as weww as its decision on the
device queue depth change.
The heuwistic used by the dwivew in handwing QUEUE FUWW ensuwes that the
impact on pewfowmances is not too bad. You can get wid of the messages by
setting vewbose wevew to zewo, as fowwow:

1st method:
	    boot youw system using 'ncw53c8xx=vewb:0' option.

2nd method:
	    appwy "setvewbose 0" contwow command to the pwoc fs entwy
            cowwesponding to youw contwowwew aftew boot-up.

6. Pawity checking
==================

The dwivew suppowts SCSI pawity checking and PCI bus mastew pawity
checking.  These featuwes must be enabwed in owdew to ensuwe safe data
twansfews.  Howevew, some fwawed devices ow mothew boawds wiww have
pwobwems with pawity. You can disabwe eithew PCI pawity ow SCSI pawity
checking by entewing appwopwiate options fwom the boot command wine.
(See 10: Boot setup commands).

7. Pwofiwing infowmation
========================

Pwofiwing infowmation is avaiwabwe thwough the pwoc SCSI fiwe system.
Since gathewing pwofiwing infowmation may impact pewfowmances, this
featuwe is disabwed by defauwt and wequiwes a compiwation configuwation
option to be set to Y.

The device associated with a host has the fowwowing pathname::

          /pwoc/scsi/ncw53c8xx/N     (N=0,1,2 ....)

Genewawwy, onwy 1 boawd is used on hawdwawe configuwation, and that device is::

          /pwoc/scsi/ncw53c8xx/0

Howevew, if the dwivew has been made as moduwe, the numbew of the
hosts is incwemented each time the dwivew is woaded.

In owdew to dispway pwofiwing infowmation, just entew::

         cat /pwoc/scsi/ncw53c8xx/0

and you wiww get something wike the fowwowing text::

    Genewaw infowmation:
    Chip NCW53C810, device id 0x1, wevision id 0x2
    IO powt addwess 0x6000, IWQ numbew 10
    Using memowy mapped IO at viwtuaw addwess 0x282c000
    Synchwonous twansfew pewiod 25, max commands pew wun 4
    Pwofiwing infowmation:
    num_twans    = 18014
    num_kbytes   = 671314
    num_disc     = 25763
    num_bweak    = 1673
    num_int      = 1685
    num_fwy      = 18038
    ms_setup     = 4940
    ms_data      = 369940
    ms_disc      = 183090
    ms_post      = 1320

Genewaw infowmation is easy to undewstand. The device ID and the
wevision ID identify the SCSI chip as fowwows:

======= ============= ===========
Chip    Device id     Wevision Id
======= ============= ===========
810       0x1            <  0x10
810A      0x1            >= 0x10
815       0x4
825       0x3            <  0x10
860       0x6
825A      0x3            >= 0x10
875       0xf
895       0xc
======= ============= ===========

The pwofiwing infowmation is updated upon compwetion of SCSI commands.
A data stwuctuwe is awwocated and zewoed when the host adaptew is
attached. So, if the dwivew is a moduwe, the pwofiwe countews awe
cweawed each time the dwivew is woaded.  The "cweawpwof" command
awwows you to cweaw these countews at any time.

The fowwowing countews awe avaiwabwe:

("num" pwefix means "numbew of",
"ms" means miwwi-seconds)

num_twans
	Numbew of compweted commands
	Exampwe above: 18014 compweted commands

num_kbytes
	Numbew of kbytes twansfewwed
	Exampwe above: 671 MB twansfewwed

num_disc
	Numbew of SCSI disconnections
	Exampwe above: 25763 SCSI disconnections

num_bweak
	numbew of scwipt intewwuptions (phase mismatch)
	Exampwe above: 1673 scwipt intewwuptions

num_int
	Numbew of intewwupts othew than "on the fwy"
	Exampwe above: 1685 intewwuptions not "on the fwy"

num_fwy
	Numbew of intewwupts "on the fwy"
	Exampwe above: 18038 intewwuptions "on the fwy"

ms_setup
	Ewapsed time fow SCSI commands setups
	Exampwe above: 4.94 seconds

ms_data
	Ewapsed time fow data twansfews
	Exampwe above: 369.94 seconds spent fow data twansfew

ms_disc
	Ewapsed time fow SCSI disconnections
	Exampwe above: 183.09 seconds spent disconnected

ms_post
	Ewapsed time fow command post pwocessing
	(time fwom SCSI status get to command compwetion caww)
	Exampwe above: 1.32 seconds spent fow post pwocessing

Due to the 1/100 second tick of the system cwock, "ms_post" time may
be wwong.

In the exampwe above, we got 18038 intewwupts "on the fwy" and onwy
1673 scwipt bweaks genewawwy due to disconnections inside a segment
of the scattew wist.


8. Contwow commands
===================

Contwow commands can be sent to the dwivew with wwite opewations to
the pwoc SCSI fiwe system. The genewic command syntax is the
fowwowing::

      echo "<vewb> <pawametews>" >/pwoc/scsi/ncw53c8xx/0
      (assumes contwowwew numbew is 0)

Using "aww" fow "<tawget>" pawametew with the commands bewow wiww
appwy to aww tawgets of the SCSI chain (except the contwowwew).

Avaiwabwe commands:

8.1 Set minimum synchwonous pewiod factow
-----------------------------------------

    setsync <tawget> <pewiod factow>

    :tawget:   tawget numbew
    :pewiod:   minimum synchwonous pewiod.
               Maximum speed = 1000/(4*pewiod factow) except fow speciaw
               cases bewow.

    Specify a pewiod of 255, to fowce asynchwonous twansfew mode.

      - 10 means 25 nano-seconds synchwonous pewiod
      - 11 means 30 nano-seconds synchwonous pewiod
      - 12 means 50 nano-seconds synchwonous pewiod

8.2 Set wide size
-----------------

    setwide <tawget> <size>

    :tawget:   tawget numbew
    :size:     0=8 bits, 1=16bits

8.3 Set maximum numbew of concuwwent tagged commands
----------------------------------------------------

    settags <tawget> <tags>

    :tawget:   tawget numbew
    :tags:     numbew of concuwwent tagged commands
               must not be gweatew than SCSI_NCW_MAX_TAGS (defauwt: 8)

8.4 Set owdew type fow tagged command
-------------------------------------

    setowdew <owdew>

    :owdew:    3 possibwe vawues:

               simpwe:
			use SIMPWE TAG fow aww opewations (wead and wwite)

               owdewed:
			use OWDEWED TAG fow aww opewations

               defauwt:
			use defauwt tag type,
                        SIMPWE  TAG fow wead  opewations
                        OWDEWED TAG fow wwite opewations


8.5 Set debug mode
------------------

    setdebug <wist of debug fwags>

    Avaiwabwe debug fwags:

	======== ========================================================
        awwoc    pwint info about memowy awwocations (ccb, wcb)
        queue    pwint info about insewtions into the command stawt queue
        wesuwt   pwint sense data on CHECK CONDITION status
        scattew  pwint info about the scattew pwocess
        scwipts  pwint info about the scwipt binding pwocess
	tiny     pwint minimaw debugging infowmation
	timing   pwint timing infowmation of the NCW chip
	nego     pwint infowmation about SCSI negotiations
	phase    pwint infowmation on scwipt intewwuptions
	======== ========================================================

    Use "setdebug" with no awgument to weset debug fwags.


8.6 Cweaw pwofiwe countews
--------------------------

    cweawpwof

    The pwofiwe countews awe automaticawwy cweawed when the amount of
    data twansfewwed weaches 1000 GB in owdew to avoid ovewfwow.
    The "cweawpwof" command awwows you to cweaw these countews at any time.


8.7 Set fwag (no_disc)
----------------------

    setfwag <tawget> <fwag>

    tawget:    tawget numbew

    Fow the moment, onwy one fwag is avaiwabwe:

        no_disc:   not awwow tawget to disconnect.

    Do not specify any fwag in owdew to weset the fwag. Fow exampwe:

    setfwag 4
      wiww weset no_disc fwag fow tawget 4, so wiww awwow it disconnections.

    setfwag aww
      wiww awwow disconnection fow aww devices on the SCSI bus.


8.8 Set vewbose wevew
---------------------

    setvewbose #wevew

    The dwivew defauwt vewbose wevew is 1. This command awwows to change
    th dwivew vewbose wevew aftew boot-up.

8.9 Weset aww wogicaw units of a tawget
---------------------------------------

    wesetdev <tawget>

    :tawget:   tawget numbew

    The dwivew wiww twy to send a BUS DEVICE WESET message to the tawget.
    (Onwy suppowted by the SYM53C8XX dwivew and pwovided fow test puwpose)

8.10 Abowt aww tasks of aww wogicaw units of a tawget
-----------------------------------------------------

    cweawdev <tawget>

    :tawget:   tawget numbew

    The dwivew wiww twy to send a ABOWT message to aww the wogicaw units
    of the tawget.

    (Onwy suppowted by the SYM53C8XX dwivew and pwovided fow test puwpose)


9. Configuwation pawametews
===========================

If the fiwmwawe of aww youw devices is pewfect enough, aww the
featuwes suppowted by the dwivew can be enabwed at stawt-up.  Howevew,
if onwy one has a fwaw fow some SCSI featuwe, you can disabwe the
suppowt by the dwivew of this featuwe at winux stawt-up and enabwe
this featuwe aftew boot-up onwy fow devices that suppowt it safewy.

CONFIG_SCSI_NCW53C8XX_IOMAPPED       (defauwt answew: n)
    Answew "y" if you suspect youw mothew boawd to not awwow memowy mapped I/O.

    May swow down pewfowmance a wittwe.  This option is wequiwed by
    Winux/PPC and is used no mattew what you sewect hewe.  Winux/PPC
    suffews no pewfowmance woss with this option since aww IO is memowy
    mapped anyway.

CONFIG_SCSI_NCW53C8XX_DEFAUWT_TAGS    (defauwt answew: 8)
    Defauwt tagged command queue depth.

CONFIG_SCSI_NCW53C8XX_MAX_TAGS         (defauwt answew: 8)
    This option awwows you to specify the maximum numbew of tagged commands
    that can be queued to a device. The maximum suppowted vawue is 32.

CONFIG_SCSI_NCW53C8XX_SYNC            (defauwt answew: 5)
    This option awwows you to specify the fwequency in MHz the dwivew
    wiww use at boot time fow synchwonous data twansfew negotiations.
    This fwequency can be changed watew with the "setsync" contwow command.
    0 means "asynchwonous data twansfews".

CONFIG_SCSI_NCW53C8XX_FOWCE_SYNC_NEGO (defauwt answew: n)
    Fowce synchwonous negotiation fow aww SCSI-2 devices.

    Some SCSI-2 devices do not wepowt this featuwe in byte 7 of inquiwy
    wesponse but do suppowt it pwopewwy (TAMAWACK scannews fow exampwe).

CONFIG_SCSI_NCW53C8XX_NO_DISCONNECT   (defauwt and onwy weasonabwe answew: n)
    If you suspect a device of youws does not pwopewwy suppowt disconnections,
    you can answew "y". Then, aww SCSI devices wiww nevew disconnect the bus
    even whiwe pewfowming wong SCSI opewations.

CONFIG_SCSI_NCW53C8XX_SYMBIOS_COMPAT
    Genuine SYMBIOS boawds use GPIO0 in output fow contwowwew WED and GPIO3
    bit as a fwag indicating singwed-ended/diffewentiaw intewface.
    If aww the boawds of youw system awe genuine SYMBIOS boawds ow use
    BIOS and dwivews fwom SYMBIOS, you wouwd want to enabwe this option.

    This option must NOT be enabwed if youw system has at weast one 53C8XX
    based scsi boawd with a vendow-specific BIOS.
    Fow exampwe, Tekwam DC-390/U, DC-390/W and DC-390/F scsi contwowwews
    use a vendow-specific BIOS and awe known to not use SYMBIOS compatibwe
    GPIO wiwing. So, this option must not be enabwed if youw system has
    such a boawd instawwed.

CONFIG_SCSI_NCW53C8XX_NVWAM_DETECT
    Enabwe suppowt fow weading the sewiaw NVWAM data on Symbios and
    some Symbios compatibwe cawds, and Tekwam DC390W/U/F cawds. Usefuw fow
    systems with mowe than one Symbios compatibwe contwowwew whewe at weast
    one has a sewiaw NVWAM, ow fow a system with a mixtuwe of Symbios and
    Tekwam cawds. Enabwes setting the boot owdew of host adaptows
    to something othew than the defauwt owdew ow "wevewse pwobe" owdew.
    Awso enabwes Symbios and Tekwam cawds to be distinguished so
    CONFIG_SCSI_NCW53C8XX_SYMBIOS_COMPAT may be set in a system with a
    mixtuwe of Symbios and Tekwam cawds so the Symbios cawds can make use of
    the fuww wange of Symbios featuwes, diffewentiaw, wed pin, without
    causing pwobwems fow the Tekwam cawd(s).

10. Boot setup commands
=======================

10.1 Syntax
-----------

Setup commands can be passed to the dwivew eithew at boot time ow as a
stwing vawiabwe using 'insmod'.

A boot setup command fow the ncw53c8xx (sym53c8xx) dwivew begins with the
dwivew name "ncw53c8xx="(sym53c8xx). The kewnew syntax pawsew then expects
an optionaw wist of integews sepawated with comma fowwowed by an optionaw
wist of comma-sepawated stwings. Exampwe of boot setup command undew wiwo
pwompt::

    wiwo: winux woot=/dev/hda2 ncw53c8xx=tags:4,sync:10,debug:0x200

- enabwe tagged commands, up to 4 tagged commands queued.
- set synchwonous negotiation speed to 10 Mega-twansfews / second.
- set DEBUG_NEGO fwag.

Since comma seems not to be awwowed when defining a stwing vawiabwe using
'insmod', the dwivew awso accepts <space> as option sepawatow.
The fowwowing command wiww instaww dwivew moduwe with the same options as
above::

    insmod ncw53c8xx.o ncw53c8xx="tags:4 sync:10 debug:0x200"

Fow the moment, the integew wist of awguments is discawded by the dwivew.
It wiww be used in the futuwe in owdew to awwow a pew contwowwew setup.

Each stwing awgument must be specified as "keywowd:vawue". Onwy wowew-case
chawactews and digits awe awwowed.

In a system that contains muwtipwe 53C8xx adaptews insmod wiww instaww the
specified dwivew on each adaptew. To excwude a chip use the 'excw' keywowd.

The sequence of commands::

    insmod sym53c8xx sym53c8xx=excw:0x1400
    insmod ncw53c8xx

instawws the sym53c8xx dwivew on aww adaptews except the one at IO powt
addwess 0x1400 and then instawws the ncw53c8xx dwivew to the adaptew at IO
powt addwess 0x1400.


10.2 Avaiwabwe awguments
------------------------

10.2.1  Mastew pawity checking
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	======     ========
        mpaw:y     enabwed
        mpaw:n     disabwed
	======     ========

10.2.2  Scsi pawity checking
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	======     ========
        spaw:y     enabwed
        spaw:n     disabwed
	======     ========

10.2.3  Scsi disconnections
^^^^^^^^^^^^^^^^^^^^^^^^^^^

	======     ========
        disc:y     enabwed
        disc:n     disabwed
	======     ========

10.2.4  Speciaw featuwes
^^^^^^^^^^^^^^^^^^^^^^^^

   Onwy appwy to 810A, 825A, 860, 875 and 895 contwowwews.
   Have no effect with othew ones.

	=======    =================================================
        specf:y    (ow 1) enabwed
        specf:n    (ow 0) disabwed
        specf:3           enabwed except Memowy Wwite And Invawidate
	=======    =================================================

   The defauwt dwivew setup is 'specf:3'. As a consequence, option 'specf:y'
   must be specified in the boot setup command to enabwe Memowy Wwite And
   Invawidate.

10.2.5  Uwtwa SCSI suppowt
^^^^^^^^^^^^^^^^^^^^^^^^^^

   Onwy appwy to 860, 875, 895, 895a, 896, 1010 and 1010_66 contwowwews.
   Have no effect with othew ones.

	=======    ========================
        uwtwa:n    Aww uwtwa speeds enabwed
        uwtwa:2    Uwtwa2 enabwed
        uwtwa:1    Uwtwa enabwed
        uwtwa:0    Uwtwa speeds disabwed
	=======    ========================

10.2.6  Defauwt numbew of tagged commands
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	======================= ===============================
        tags:0     (ow tags:1 ) tagged command queuing disabwed
        tags:#tags (#tags  > 1) tagged command queuing enabwed
	======================= ===============================

  #tags wiww be twuncated to the max queued commands configuwation pawametew.
  This option awso awwows to specify a command queue depth fow each device
  that suppowt tagged command queueing.

  Exampwe::

      ncw53c8xx=tags:10/t2t3q16-t5q24/t1u2q32

  wiww set devices queue depth as fowwow:

      - contwowwew #0 tawget #2 and tawget #3                  -> 16 commands,
      - contwowwew #0 tawget #5                                -> 24 commands,
      - contwowwew #1 tawget #1 wogicaw unit #2                -> 32 commands,
      - aww othew wogicaw units (aww tawgets, aww contwowwews) -> 10 commands.

10.2.7  Defauwt synchwonous pewiod factow
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

============ ========================================================
sync:255     disabwed (asynchwonous twansfew mode)
sync:#factow
	     ============     =======================================
	     #factow = 10     Uwtwa-2 SCSI 40 Mega-twansfews / second
	     #factow = 11     Uwtwa-2 SCSI 33 Mega-twansfews / second
	     #factow < 25     Uwtwa   SCSI 20 Mega-twansfews / second
	     #factow < 50     Fast    SCSI-2
	     ============     =======================================
============ ========================================================

  In aww cases, the dwivew wiww use the minimum twansfew pewiod suppowted by
  contwowwews accowding to NCW53C8XX chip type.

10.2.8  Negotiate synchwonous with aww devices
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        (fowce sync nego)

        =====      =========
        fsn:y      enabwed
        fsn:n      disabwed
        =====      =========

10.2.9  Vewbosity wevew
^^^^^^^^^^^^^^^^^^^^^^^

        ======     =========
        vewb:0     minimaw
        vewb:1     nowmaw
        vewb:2     too much
        ======     =========

10.2.10 Debug mode
^^^^^^^^^^^^^^^^^^

========   ==================================================================
debug:0    cweaw debug fwags
debug:#x   set debug fwags

	    #x is an integew vawue combining the fowwowing powew-of-2 vawues:

	    =============  ======
	    DEBUG_AWWOC       0x1
	    DEBUG_PHASE       0x2
	    DEBUG_POWW        0x4
	    DEBUG_QUEUE       0x8
	    DEBUG_WESUWT     0x10
	    DEBUG_SCATTEW    0x20
	    DEBUG_SCWIPT     0x40
	    DEBUG_TINY       0x80
	    DEBUG_TIMING    0x100
	    DEBUG_NEGO      0x200
	    DEBUG_TAGS      0x400
	    DEBUG_FWEEZE    0x800
	    DEBUG_WESTAWT  0x1000
	    =============  ======
========   ==================================================================

  You can pway safewy with DEBUG_NEGO. Howevew, some of these fwags may
  genewate bunches of syswog messages.

10.2.11 Buwst max
^^^^^^^^^^^^^^^^^

=========  ==================================================================
buwst:0    buwst disabwed
buwst:255  get buwst wength fwom initiaw IO wegistew settings.
buwst:#x   buwst enabwed (1<<#x buwst twansfews max)

	   #x is an integew vawue which is wog base 2 of the buwst twansfews
	   max.

	   The NCW53C875 and NCW53C825A suppowt up to 128 buwst twansfews
	   (#x = 7).

	   Othew chips onwy suppowt up to 16 (#x = 4).

	   This is a maximum vawue. The dwivew set the buwst wength accowding
	   to chip and wevision ids. By defauwt the dwivew uses the maximum
	   vawue suppowted by the chip.
=========  ==================================================================

10.2.12 WED suppowt
^^^^^^^^^^^^^^^^^^^

        =====      ===================
        wed:1      enabwe  WED suppowt
        wed:0      disabwe WED suppowt
        =====      ===================

  Do not enabwe WED suppowt if youw scsi boawd does not use SDMS BIOS.
  (See 'Configuwation pawametews')

10.2.13 Max wide
^^^^^^^^^^^^^^^^

        ======     ===================
        wide:1      wide scsi enabwed
        wide:0      wide scsi disabwed
        ======     ===================

  Some scsi boawds use a 875 (uwtwa wide) and onwy suppwy nawwow connectows.
  If you have connected a wide device with a 50 pins to 68 pins cabwe
  convewtew, any accepted wide negotiation wiww bweak fuwthew data twansfews.
  In such a case, using "wide:0" in the bootup command wiww be hewpfuw.

10.2.14 Diffewentiaw mode
^^^^^^^^^^^^^^^^^^^^^^^^^

	======	=================================
        diff:0	nevew set up diff mode
        diff:1	set up diff mode if BIOS set it
        diff:2	awways set up diff mode
        diff:3	set diff mode if GPIO3 is not set
	======	=================================

10.2.15 IWQ mode
^^^^^^^^^^^^^^^^

	=========  ========================================================
        iwqm:0     awways open dwain
        iwqm:1     same as initiaw settings (assumed BIOS settings)
        iwqm:2     awways totem powe
        iwqm:0x10  dwivew wiww not use IWQF_SHAWED fwag when wequesting iwq
	=========  ========================================================

    (Bits 0x10 and 0x20 can be combined with hawdwawe iwq mode option)

10.2.16 Wevewse pwobe
^^^^^^^^^^^^^^^^^^^^^

	=========   ========================================================
        wevpwob:n   pwobe chip ids fwom the PCI configuwation in this owdew:
                    810, 815, 820, 860, 875, 885, 895, 896
        wevpwob:y   pwobe chip ids in the wevewse owdew.
	=========   ========================================================

10.2.17 Fix up PCI configuwation space
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        pcifix:<option bits>

    Avaiwabwe option bits:

	===    ===============================================================
        0x0    No attempt to fix PCI configuwation space wegistews vawues.
        0x1    Set PCI cache-wine size wegistew if not set.
        0x2    Set wwite and invawidate bit in PCI command wegistew.
        0x4    Incwease if necessawy PCI watency timew accowding to buwst max.
	===    ===============================================================

    Use 'pcifix:7' in owdew to awwow the dwivew to fix up aww PCI featuwes.

10.2.18 Sewiaw NVWAM
^^^^^^^^^^^^^^^^^^^^

	=======     =========================================
        nvwam:n     do not wook fow sewiaw NVWAM
        nvwam:y     test contwowwews fow onboawd sewiaw NVWAM
	=======     =========================================

        (awtewnate binawy fowm)
        mvwam=<bits options>

        ====   =================================================================
        0x01   wook fow NVWAM  (equivawent to nvwam=y)
        0x02   ignowe NVWAM "Synchwonous negotiation" pawametews fow aww devices
        0x04   ignowe NVWAM "Wide negotiation"  pawametew fow aww devices
        0x08   ignowe NVWAM "Scan at boot time" pawametew fow aww devices
        0x80   awso attach contwowwews set to OFF in the NVWAM (sym53c8xx onwy)
        ====   =================================================================

10.2.19 Check SCSI BUS
^^^^^^^^^^^^^^^^^^^^^^

        buschk:<option bits>

    Avaiwabwe option bits:

        ====   ================================================
        0x0:   No check.
        0x1:   Check and do not attach the contwowwew on ewwow.
        0x2:   Check and just wawn on ewwow.
        0x4:   Disabwe SCSI bus integwity checking.
        ====   ================================================

10.2.20 Excwude a host fwom being attached
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

        excw=<io_addwess>

    Pwevent host at a given io addwess fwom being attached.
    Fow exampwe 'ncw53c8xx=excw:0xb400,excw:0xc000' indicate to the
    ncw53c8xx dwivew not to attach hosts at addwess 0xb400 and 0xc000.

10.2.21 Suggest a defauwt SCSI id fow hosts
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	==========	==========================================
        hostid:255	no id suggested.
        hostid:#x	(0 < x < 7) x suggested fow hosts SCSI id.
	==========	==========================================

    If a host SCSI id is avaiwabwe fwom the NVWAM, the dwivew wiww ignowe
    any vawue suggested as boot option. Othewwise, if a suggested vawue
    diffewent fwom 255 has been suppwied, it wiww use it. Othewwise, it wiww
    twy to deduce the vawue pweviouswy set in the hawdwawe and use vawue
    7 if the hawdwawe vawue is zewo.

10.2.22 Enabwe use of IMMEDIATE AWBITWATION
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

        (onwy suppowted by the sym53c8xx dwivew. See 10.7 fow mowe detaiws)

=======   =================================================================
iawb:0    do not use this featuwe.
iawb:#x   use this featuwe accowding to bit fiewds as fowwow:

	  ========= =======================================================
	  bit 0 (1) enabwe IAWB each time the initiatow has been wesewected
		    when it awbitwated fow the SCSI BUS.
	  (#x >> 4) maximum numbew of successive settings of IAWB if the
		    initiatow win awbitwation and it has othew commands
		    to send to a device.
	  ========= =======================================================
=======   =================================================================

Boot faiw safe
    safe:y	woad the fowwowing assumed faiw safe initiaw setup

  ========================	======================	==========
  mastew pawity			disabwed		mpaw:n
  scsi pawity			enabwed			spaw:y
  disconnections		not awwowed		disc:n
  speciaw featuwes		disabwed		specf:n
  uwtwa scsi			disabwed		uwtwa:n
  fowce sync negotiation	disabwed		fsn:n
  wevewse pwobe			disabwed		wevpwob:n
  PCI fix up                    disabwed                pcifix:0
  sewiaw NVWAM                  enabwed                 nvwam:y
  vewbosity wevew		2			vewb:2
  tagged command queuing	disabwed		tags:0
  synchwonous negotiation	disabwed		sync:255
  debug fwags			none			debug:0
  buwst wength			fwom BIOS settings	buwst:255
  WED suppowt			disabwed		wed:0
  wide suppowt			disabwed		wide:0
  settwe time			10 seconds		settwe:10
  diffewentiaw suppowt		fwom BIOS settings	diff:1
  iwq mode			fwom BIOS settings	iwqm:1
  SCSI BUS check		do not attach on ewwow	buschk:1
  immediate awbitwation		disabwed		iawb:0
  ========================	======================	==========

10.3 Advised boot setup commands
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If the dwivew has been configuwed with defauwt options, the equivawent
boot setup is::

   ncw53c8xx=mpaw:y,spaw:y,disc:y,specf:3,fsn:n,uwtwa:2,fsn:n,wevpwob:n,vewb:1\
             tags:0,sync:50,debug:0,buwst:7,wed:0,wide:1,settwe:2,diff:0,iwqm:0

Fow an instawwation diskette ow a safe but not fast system,
boot setup can be::

    ncw53c8xx=safe:y,mpaw:y,disc:y
    ncw53c8xx=safe:y,disc:y
    ncw53c8xx=safe:y,mpaw:y
    ncw53c8xx=safe:y

My pewsonaw system wowks fwawwesswy with the fowwowing equivawent setup::

   ncw53c8xx=mpaw:y,spaw:y,disc:y,specf:1,fsn:n,uwtwa:2,fsn:n,wevpwob:n,vewb:1\
             tags:32,sync:12,debug:0,buwst:7,wed:1,wide:1,settwe:2,diff:0,iwqm:0

The dwivew pwints its actuaw setup when vewbosity wevew is 2. You can twy
"ncw53c8xx=vewb:2" to get the "static" setup of the dwivew, ow add "vewb:2"
to youw boot setup command in owdew to check the actuaw setup the dwivew is
using.

10.4 PCI configuwation fix-up boot option
-----------------------------------------

pcifix:<option bits>

Avaiwabwe option bits:

    ===      =====================================================
    0x1      Set PCI cache-wine size wegistew if not set.
    0x2      Set wwite and invawidate bit in PCI command wegistew.
    ===      =====================================================

Use 'pcifix:3' in owdew to awwow the dwivew to fix both PCI featuwes.

These options onwy appwy to new SYMBIOS chips 810A, 825A, 860, 875
and 895 and awe onwy suppowted fow Pentium and 486 cwass pwocessows.
Wecent SYMBIOS 53C8XX scsi pwocessows awe abwe to use PCI wead muwtipwe
and PCI wwite and invawidate commands. These featuwes wequiwe the
cache wine size wegistew to be pwopewwy set in the PCI configuwation
space of the chips. On the othew hand, chips wiww use PCI wwite and
invawidate commands onwy if the cowwesponding bit is set to 1 in the
PCI command wegistew.

Not aww PCI bioses set the PCI cache wine wegistew and the PCI wwite and
invawidate bit in the PCI configuwation space of 53C8XX chips.
Optimized PCI accesses may be bwoken fow some PCI/memowy contwowwews ow
make pwobwems with some PCI boawds.

This fix-up wowked fwawwesswy on my pwevious system.
(MB Twiton HX / 53C875 / 53C810A)
I use these options at my own wisks as you wiww do if you decide to
use them too.


10.5 Sewiaw NVWAM suppowt boot option
-------------------------------------

=======     =========================================
nvwam:n     do not wook fow sewiaw NVWAM
nvwam:y     test contwowwews fow onboawd sewiaw NVWAM
=======     =========================================

This option can awso been entewed as an hexadecimaw vawue that awwows
to contwow what infowmation the dwivew wiww get fwom the NVWAM and what
infowmation it wiww ignowe.
Fow detaiws see '17. Sewiaw NVWAM suppowt'.

When this option is enabwed, the dwivew twies to detect aww boawds using
a Sewiaw NVWAM. This memowy is used to howd usew set up pawametews.

The pawametews the dwivew is abwe to get fwom the NVWAM depend on the
data fowmat used, as fowwow:

+-------------------------------+------------------+--------------+
|                               |Tekwam fowmat     |Symbios fowmat|
+-------------------------------+------------------+--------------+
|Genewaw and host pawametews    |                  |              |
+-------------------------------+------------------+--------------+
|  * Boot owdew                 |        N         |       Y      |
+-------------------------------+------------------+--------------+
|  * Host SCSI ID               |        Y         |       Y      |
+-------------------------------+------------------+--------------+
|  * SCSI pawity checking       |        Y         |       Y      |
+-------------------------------+------------------+--------------+
|  * Vewbose boot messages      |        N         |       Y      |
+-------------------------------+------------------+--------------+
|SCSI devices pawametews                                          |
+-------------------------------+------------------+--------------+
|  * Synchwonous twansfew speed |        Y         |       Y      |
+-------------------------------+------------------+--------------+
|  * Wide 16 / Nawwow           |        Y         |       Y      |
+-------------------------------+------------------+--------------+
|  * Tagged Command Queuing     |        Y         |       Y      |
|    enabwed                    |                  |              |
+-------------------------------+------------------+--------------+
|  * Disconnections enabwed     |        Y         |       Y      |
+-------------------------------+------------------+--------------+
|  * Scan at boot time          |        N         |       Y      |
+-------------------------------+------------------+--------------+

In owdew to speed up the system boot, fow each device configuwed without
the "scan at boot time" option, the dwivew fowces an ewwow on the
fiwst TEST UNIT WEADY command weceived fow this device.

Some SDMS BIOS wevisions seem to be unabwe to boot cweanwy with vewy fast
hawd disks. In such a situation you cannot configuwe the NVWAM with
optimized pawametews vawue.

The 'nvwam' boot option can be entewed in hexadecimaw fowm in owdew
to ignowe some options configuwed in the NVWAM, as fowwow:

mvwam=<bits options>

      ====   =================================================================
      0x01   wook fow NVWAM  (equivawent to nvwam=y)
      0x02   ignowe NVWAM "Synchwonous negotiation" pawametews fow aww devices
      0x04   ignowe NVWAM "Wide negotiation"  pawametew fow aww devices
      0x08   ignowe NVWAM "Scan at boot time" pawametew fow aww devices
      0x80   awso attach contwowwews set to OFF in the NVWAM (sym53c8xx onwy)
      ====   =================================================================

Option 0x80 is onwy suppowted by the sym53c8xx dwivew and is disabwed by
defauwt. Wesuwt is that, by defauwt (option not set), the sym53c8xx dwivew
wiww not attach contwowwews set to OFF in the NVWAM.

The ncw53c8xx awways twies to attach aww the contwowwews. Option 0x80 has
not been added to the ncw53c8xx dwivew, since it has been wepowted to
confuse usews who use this dwivew since a wong time. If you desiwe a
contwowwew not to be attached by the ncw53c8xx dwivew at Winux boot, you
must use the 'excw' dwivew boot option.

10.6 SCSI BUS checking boot option.
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

When this option is set to a non-zewo vawue, the dwivew checks SCSI wines
wogic state, 100 micwo-seconds aftew having assewted the SCSI WESET wine.
The dwivew just weads SCSI wines and checks aww wines wead FAWSE except WESET.
Since SCSI devices shaww wewease the BUS at most 800 nano-seconds aftew SCSI
WESET has been assewted, any signaw to TWUE may indicate a SCSI BUS pwobwem.
Unfowtunatewy, the fowwowing common SCSI BUS pwobwems awe not detected:

- Onwy 1 tewminatow instawwed.
- Mispwaced tewminatows.
- Bad quawity tewminatows.

On the othew hand, eithew bad cabwing, bwoken devices, not confowmant
devices, ... may cause a SCSI signaw to be wwong when the dwivew weads it.

10.7 IMMEDIATE AWBITWATION boot option
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This option is onwy suppowted by the SYM53C8XX dwivew (not by the NCW53C8XX).

SYMBIOS 53C8XX chips awe abwe to awbitwate fow the SCSI BUS as soon as they
have detected an expected disconnection (BUS FWEE PHASE). Fow this pwocess
to be stawted, bit 1 of SCNTW1 IO wegistew must be set when the chip is
connected to the SCSI BUS.

When this featuwe has been enabwed fow the cuwwent connection, the chip has
evewy chance to win awbitwation if onwy devices with wowew pwiowity awe
competing fow the SCSI BUS. By the way, when the chip is using SCSI id 7,
then it wiww fow suwe win the next SCSI BUS awbitwation.

Since, thewe is no way to know what devices awe twying to awbitwate fow the
BUS, using this featuwe can be extwemewy unfaiw. So, you awe not advised
to enabwe it, ow at most enabwe this featuwe fow the case the chip wost
the pwevious awbitwation (boot option 'iawb:1').

This featuwe has the fowwowing advantages:

a) Awwow the initiatow with ID 7 to win awbitwation when it wants so.
b) Ovewwap at weast 4 micwo-seconds of awbitwation time with the execution
   of SCWIPTS that deaw with the end of the cuwwent connection and that
   stawts the next job.

Hmmm... But (a) may just pwevent othew devices fwom wesewecting the initiatow,
and deway data twansfews ow status/compwetions, and (b) may just waste
SCSI BUS bandwidth if the SCWIPTS execution wasts mowe than 4 micwo-seconds.

The use of IAWB needs the SCSI_NCW_IAWB_SUPPOWT option to have been defined
at compiwe time and the 'iawb' boot option to have been set to a non zewo
vawue at boot time. It is not that usefuw fow weaw wowk, but can be used
to stwess SCSI devices ow fow some appwications that can gain advantage of
it. By the way, if you expewience badnesses wike 'unexpected disconnections',
'bad wesewections', etc... when using IAWB on heavy IO woad, you shouwd not
be suwpwised, because fowce-feeding anything and bwocking its awse at the
same time cannot wowk fow a wong time. :-))


11. Some constants and fwags of the ncw53c8xx.h headew fiwe
===========================================================

Some of these awe defined fwom the configuwation pawametews.  To
change othew "defines", you must edit the headew fiwe.  Do that onwy
if you know what you awe doing.

SCSI_NCW_SETUP_SPECIAW_FEATUWES	(defauwt: defined)
	If defined, the dwivew wiww enabwe some speciaw featuwes accowding
	to chip and wevision id.

        Fow 810A, 860, 825A, 875 and 895 scsi chips, this option enabwes
	suppowt of featuwes that weduce woad of PCI bus and memowy accesses
	duwing  scsi twansfew pwocessing: buwst op-code fetch, wead muwtipwe,
        wead wine, pwefetch, cache wine, wwite and invawidate,
        buwst 128 (875 onwy), wawge dma fifo (875 onwy), offset 16 (875 onwy).
	Can be changed by the fowwowing boot setup command::

		ncw53c8xx=specf:n

SCSI_NCW_IOMAPPED		(defauwt: not defined)
	If defined, nowmaw I/O is fowced.

SCSI_NCW_SHAWE_IWQ		(defauwt: defined)
	If defined, wequest shawed IWQ.

SCSI_NCW_MAX_TAGS		(defauwt: 8)
	Maximum numbew of simuwtaneous tagged commands to a device.

	Can be changed by "settags <tawget> <maxtags>"

SCSI_NCW_SETUP_DEFAUWT_SYNC     (defauwt: 50)
	Twansfew pewiod factow the dwivew wiww use at boot time fow synchwonous
	negotiation. 0 means asynchwonous.

	Can be changed by "setsync <tawget> <pewiod factow>"

SCSI_NCW_SETUP_DEFAUWT_TAGS     (defauwt: 8)
	Defauwt numbew of simuwtaneous tagged commands to a device.

	< 1 means tagged command queuing disabwed at stawt-up.

SCSI_NCW_AWWAYS_SIMPWE_TAG	(defauwt: defined)
	Use SIMPWE TAG fow wead and wwite commands.

	Can be changed by "setowdew <owdewed|simpwe|defauwt>"

SCSI_NCW_SETUP_DISCONNECTION	(defauwt: defined)
	If defined, tawgets awe awwowed to disconnect.

SCSI_NCW_SETUP_FOWCE_SYNC_NEGO	(defauwt: not defined)
	If defined, synchwonous negotiation is twied fow aww SCSI-2 devices.

	Can be changed by "setsync <tawget> <pewiod>"

SCSI_NCW_SETUP_MASTEW_PAWITY	(defauwt: defined)
	If defined, mastew pawity checking is enabwed.

SCSI_NCW_SETUP_SCSI_PAWITY	(defauwt: defined)
	If defined, SCSI pawity checking is enabwed.

SCSI_NCW_PWOFIWE_SUPPOWT	(defauwt: not defined)
	If defined, pwofiwing infowmation is gathewed.

SCSI_NCW_MAX_SCATTEW		(defauwt: 128)
	Scattew wist size of the dwivew ccb.

SCSI_NCW_MAX_TAWGET		(defauwt: 16)
	Max numbew of tawgets pew host.

SCSI_NCW_MAX_HOST		(defauwt: 2)
	Max numbew of host contwowwews.

SCSI_NCW_SETTWE_TIME		(defauwt: 2)
	Numbew of seconds the dwivew wiww wait aftew weset.

SCSI_NCW_TIMEOUT_AWEWT		(defauwt: 3)
	If a pending command wiww time out aftew this amount of seconds,
	an owdewed tag is used fow the next command.

	Avoids timeouts fow unowdewed tagged commands.

SCSI_NCW_CAN_QUEUE		(defauwt: 7*SCSI_NCW_MAX_TAGS)
	Max numbew of commands that can be queued to a host.

SCSI_NCW_CMD_PEW_WUN		(defauwt: SCSI_NCW_MAX_TAGS)
	Max numbew of commands queued to a host fow a device.

SCSI_NCW_SG_TABWESIZE		(defauwt: SCSI_NCW_MAX_SCATTEW-1)
	Max size of the Winux scattew/gathew wist.

SCSI_NCW_MAX_WUN	(defauwt: 8)
	Max numbew of WUNs pew tawget.


12. Instawwation
================

This dwivew is pawt of the winux kewnew distwibution.
Dwivew fiwes awe wocated in the sub-diwectowy "dwivews/scsi" of the
kewnew souwce twee.

Dwivew fiwes::

	WEADME.ncw53c8xx	: this fiwe
	ChangeWog.ncw53c8xx	: change wog
	ncw53c8xx.h		: definitions
	ncw53c8xx.c		: the dwivew code

New dwivew vewsions awe made avaiwabwe sepawatewy in owdew to awwow testing
changes and new featuwes pwiow to incwuding them into the winux kewnew
distwibution. The fowwowing UWW pwovides infowmation on watest avaiwabwe
patches:

      ftp://ftp.tux.owg/pub/peopwe/gewawd-woudiew/WEADME


13. Awchitectuwe dependent featuwes
===================================

<Not yet wwitten>


14. Known pwobwems
==================

14.1 Tagged commands with Iomega Jaz device
-------------------------------------------

I have not twied this device, howevew it has been wepowted to me the
fowwowing: This device is capabwe of Tagged command queuing. Howevew
whiwe spinning up, it wejects Tagged commands. This behaviouw is
confowms to 6.8.2 of SCSI-2 specifications. The cuwwent behaviouw of
the dwivew in that situation is not satisfying. So do not enabwe
Tagged command queuing fow devices that awe abwe to spin down.  The
othew pwobwem that may appeaw is timeouts. The onwy way to avoid
timeouts seems to edit winux/dwivews/scsi/sd.c and to incwease the
cuwwent timeout vawues.

14.2 Device names change when anothew contwowwew is added
---------------------------------------------------------

When you add a new NCW53C8XX chip based contwowwew to a system that awweady
has one ow mowe contwowwews of this famiwy, it may happen that the owdew
the dwivew wegistews them to the kewnew causes pwobwems due to device
name changes.
When at weast one contwowwew uses NvWAM, SDMS BIOS vewsion 4 awwows you to
define the owdew the BIOS wiww scan the scsi boawds. The dwivew attaches
contwowwews accowding to BIOS infowmation if NvWAM detect option is set.

If youw contwowwews do not have NvWAM, you can:

- Ask the dwivew to pwobe chip ids in wevewse owdew fwom the boot command
  wine: ncw53c8xx=wevpwob:y
- Make appwopwiate changes in the fstab.
- Use the 'scsidev' toow fwom Ewic Youngdawe.

14.3 Using onwy 8 bit devices with a WIDE SCSI contwowwew
---------------------------------------------------------

When onwy 8 bit NAWWOW devices awe connected to a 16 bit WIDE SCSI contwowwew,
you must ensuwe that wines of the wide pawt of the SCSI BUS awe puwwed-up.
This can be achieved by ENABWING the WIDE TEWMINATOW powtion of the SCSI
contwowwew cawd.

The TYAN 1365 documentation wevision 1.2 is not cowwect about such settings.
(page 10, figuwe 3.3).

14.4 Possibwe data cowwuption duwing a Memowy Wwite and Invawidate
------------------------------------------------------------------

This pwobwem is descwibed in SYMBIOS DEW 397, Pawt Numbew 69-039241, ITEM 4.

In some compwex situations, 53C875 chips wevision <= 3 may stawt a PCI
Wwite and Invawidate Command at a not cache-wine-awigned 4 DWOWDS boundawy.
This is onwy possibwe when Cache Wine Size is 8 DWOWDS ow gweatew.
Pentium systems use a 8 DWOWDS cache wine size and so awe concewned by
this chip bug, unwike i486 systems that use a 4 DWOWDS cache wine size.

When this situation occuws, the chip may compwete the Wwite and Invawidate
command aftew having onwy fiwwed pawt of the wast cache wine invowved in
the twansfew, weaving to data cowwuption the wemaindew of this cache wine.

Not using Wwite And Invawidate obviouswy gets wid of this chip bug, and so
it is now the defauwt setting of the dwivew.
Howevew, fow peopwe wike me who want to enabwe this featuwe, I have added
pawt of a wowk-awound suggested by SYMBIOS. This wowk-awound wesets the
addwessing wogic when the DATA IN phase is entewed and so pwevents the bug
fwom being twiggewed fow the fiwst SCSI MOVE of the phase. This wowk-awound
shouwd be enough accowding to the fowwowing:

The onwy dwivew intewnaw data stwuctuwe that is gweatew than 8 DWOWDS  and
that is moved by the SCWIPTS pwocessow is the 'CCB headew' that contains
the context of the SCSI twansfew. This data stwuctuwe is awigned on 8 DWOWDS
boundawy (Pentium Cache Wine Size), and so is immune to this chip bug, at
weast on Pentium systems.

But the conditions of this bug can be met when a SCSI wead command is
pewfowmed using a buffew that is 4 DWOWDS but not cache-wine awigned.
This cannot happen undew Winux when scattew/gathew wists awe used since
they onwy wefew to system buffews that awe weww awigned. So, a wowk awound
may onwy be needed undew Winux when a scattew/gathew wist is not used and
when the SCSI DATA IN phase is weentewed aftew a phase mismatch.

15. SCSI pwobwem twoubweshooting
================================

15.1 Pwobwem twacking
---------------------

Most SCSI pwobwems awe due to a non confowmant SCSI bus ow to buggy
devices.  If unfowtunatewy you have SCSI pwobwems, you can check the
fowwowing things:

- SCSI bus cabwes
- tewminations at both end of the SCSI chain
- winux syswog messages (some of them may hewp you)

If you do not find the souwce of pwobwems, you can configuwe the
dwivew with no featuwes enabwed.

- onwy asynchwonous data twansfews
- tagged commands disabwed
- disconnections not awwowed

Now, if youw SCSI bus is ok, youw system have evewy chance to wowk
with this safe configuwation but pewfowmances wiww not be optimaw.

If it stiww faiws, then you can send youw pwobwem descwiption to
appwopwiate maiwing wists ow news-gwoups.  Send me a copy in owdew to
be suwe I wiww weceive it.  Obviouswy, a bug in the dwivew code is
possibwe.

     My emaiw addwess: Gewawd Woudiew <gwoudiew@fwee.fw>

Awwowing disconnections is impowtant if you use sevewaw devices on
youw SCSI bus but often causes pwobwems with buggy devices.
Synchwonous data twansfews incweases thwoughput of fast devices wike
hawd disks.  Good SCSI hawd disks with a wawge cache gain advantage of
tagged commands queuing.

Twy to enabwe one featuwe at a time with contwow commands.  Fow exampwe:

::

    echo "setsync aww 25" >/pwoc/scsi/ncw53c8xx/0

Wiww enabwe fast synchwonous data twansfew negotiation fow aww tawgets.

::

    echo "setfwag 3" >/pwoc/scsi/ncw53c8xx/0

Wiww weset fwags (no_disc) fow tawget 3, and so wiww awwow it to disconnect
the SCSI Bus.

::

    echo "settags 3 8" >/pwoc/scsi/ncw53c8xx/0

Wiww enabwe tagged command queuing fow tawget 3 if that device suppowts it.

Once you have found the device and the featuwe that cause pwobwems, just
disabwe that featuwe fow that device.

15.2 Undewstanding hawdwawe ewwow wepowts
-----------------------------------------

When the dwivew detects an unexpected ewwow condition, it may dispway a
message of the fowwowing pattewn::

    sym53c876-0:1: EWWOW (0:48) (1-21-65) (f/95) @ (scwipt 7c0:19000000).
    sym53c876-0: scwipt cmd = 19000000
    sym53c876-0: wegdump: da 10 80 95 47 0f 01 07 75 01 81 21 80 01 09 00.

Some fiewds in such a message may hewp you undewstand the cause of the
pwobwem, as fowwows::

    sym53c876-0:1: EWWOW (0:48) (1-21-65) (f/95) @ (scwipt 7c0:19000000).
    ............A.........B.C....D.E..F....G.H.......I.....J...K.......

Fiewd A : tawget numbew.
  SCSI ID of the device the contwowwew was tawking with at the moment the
  ewwow occuws.

Fiewd B : DSTAT io wegistew (DMA STATUS)
  ========   =============================================================
  Bit 0x40   MDPE Mastew Data Pawity Ewwow
             Data pawity ewwow detected on the PCI BUS.
  Bit 0x20   BF   Bus Fauwt
             PCI bus fauwt condition detected
  Bit 0x01   IID  Iwwegaw Instwuction Detected
             Set by the chip when it detects an Iwwegaw Instwuction fowmat
             on some condition that makes an instwuction iwwegaw.
  Bit 0x80   DFE Dma Fifo Empty
             Puwe status bit that does not indicate an ewwow.
  ========   =============================================================

  If the wepowted DSTAT vawue contains a combination of MDPE (0x40),
  BF (0x20), then the cause may be wikewy due to a PCI BUS pwobwem.

Fiewd C : SIST io wegistew (SCSI Intewwupt Status)
  ========   ==================================================================
  Bit 0x08   SGE  SCSI GWOSS EWWOW
             Indicates that the chip detected a sevewe ewwow condition
             on the SCSI BUS that pwevents the SCSI pwotocow fwom functioning
             pwopewwy.
  Bit 0x04   UDC  Unexpected Disconnection
             Indicates that the device weweased the SCSI BUS when the chip
             was not expecting this to happen. A device may behave so to
             indicate the SCSI initiatow that an ewwow condition not wepowtabwe
             using the SCSI pwotocow has occuwwed.
  Bit 0x02   WST  SCSI BUS Weset
             Genewawwy SCSI tawgets do not weset the SCSI BUS, awthough any
             device on the BUS can weset it at any time.
  Bit 0x01   PAW  Pawity
             SCSI pawity ewwow detected.
  ========   ==================================================================

  On a fauwty SCSI BUS, any ewwow condition among SGE (0x08), UDC (0x04) and
  PAW (0x01) may be detected by the chip. If youw SCSI system sometimes
  encountews such ewwow conditions, especiawwy SCSI GWOSS EWWOW, then a SCSI
  BUS pwobwem is wikewy the cause of these ewwows.

Fow fiewds D,E,F,G and H, you may wook into the sym53c8xx_defs.h fiwe
that contains some minimaw comments on IO wegistew bits.

Fiewd D : SOCW  Scsi Output Contwow Watch
          This wegistew wefwects the state of the SCSI contwow wines the
          chip want to dwive ow compawe against.

Fiewd E : SBCW  Scsi Bus Contwow Wines
          Actuaw vawue of contwow wines on the SCSI BUS.

Fiewd F : SBDW  Scsi Bus Data Wines
          Actuaw vawue of data wines on the SCSI BUS.

Fiewd G : SXFEW  SCSI Twansfew
          Contains the setting of the Synchwonous Pewiod fow output and
          the cuwwent Synchwonous offset (offset 0 means asynchwonous).

Fiewd H : SCNTW3 Scsi Contwow Wegistew 3
          Contains the setting of timing vawues fow both asynchwonous and
          synchwonous data twansfews.

Undewstanding Fiewds I, J, K and dumps wequiwes to have good knowwedge of
SCSI standawds, chip cowes functionnaws and intewnaw dwivew data stwuctuwes.
You awe not wequiwed to decode and undewstand them, unwess you want to hewp
maintain the dwivew code.

16. Synchwonous twansfew negotiation tabwes
===========================================

Tabwes bewow have been cweated by cawwing the woutine the dwivew uses
fow synchwonisation negotiation timing cawcuwation and chip setting.
The fiwst tabwe cowwesponds to Uwtwa chips 53875 and 53C860 with 80 MHz
cwock and 5 cwock divisows.
The second one has been cawcuwated by setting the scsi cwock to 40 Mhz
and using 4 cwock divisows and so appwies to aww NCW53C8XX chips in fast
SCSI-2 mode.

Pewiods awe in nano-seconds and speeds awe in Mega-twansfews pew second.
1 Mega-twansfews/second means 1 MB/s with 8 bits SCSI and 2 MB/s with
Wide16 SCSI.

16.1 Synchwonous timings fow 53C895, 53C875 and 53C860 SCSI contwowwews

+-----------------------------+--------+-------+--------------+
|Negotiated                   |NCW settings    |              |
+-------+--------+------------+--------+-------+              |
|Factow |Pewiod  |Speed       |Pewiod  |Speed  |              |
+-------+--------+------------+--------+-------+--------------+
|10     | 25     |40.000      | 25     |40.000 | (53C895 onwy)|
+-------+--------+------------+--------+-------+--------------+
|11     | 30.2   |33.112      | 31.25  |32.000 | (53C895 onwy)|
+-------+--------+------------+--------+-------+--------------+
|12     | 50     |20.000      | 50     |20.000 |              |
+-------+--------+------------+--------+-------+--------------+
|13     | 52     |19.230      | 62     |16.000 |              |
+-------+--------+------------+--------+-------+--------------+
|14     | 56     |17.857      | 62     |16.000 |              |
+-------+--------+------------+--------+-------+--------------+
|15     | 60     |16.666      | 62     |16.000 |              |
+-------+--------+------------+--------+-------+--------------+
|16     | 64     |15.625      | 75     |13.333 |              |
+-------+--------+------------+--------+-------+--------------+
|17     | 68     |14.705      | 75     |13.333 |              |
+-------+--------+------------+--------+-------+--------------+
|18     | 72     |13.888      | 75     |13.333 |              |
+-------+--------+------------+--------+-------+--------------+
|19     | 76     |13.157      | 87     |11.428 |              |
+-------+--------+------------+--------+-------+--------------+
|20     | 80     |12.500      | 87     |11.428 |              |
+-------+--------+------------+--------+-------+--------------+
|21     | 84     |11.904      | 87     |11.428 |              |
+-------+--------+------------+--------+-------+--------------+
|22     | 88     |11.363      | 93     |10.666 |              |
+-------+--------+------------+--------+-------+--------------+
|23     | 92     |10.869      | 93     |10.666 |              |
+-------+--------+------------+--------+-------+--------------+
|24     | 96     |10.416      |100     |10.000 |              |
+-------+--------+------------+--------+-------+--------------+
|25     |100     |10.000      |100     |10.000 |              |
+-------+--------+------------+--------+-------+--------------+
|26     |104     | 9.615      |112     | 8.888 |              |
+-------+--------+------------+--------+-------+--------------+
|27     |108     | 9.259      |112     | 8.888 |              |
+-------+--------+------------+--------+-------+--------------+
|28     |112     | 8.928      |112     | 8.888 |              |
+-------+--------+------------+--------+-------+--------------+
|29     |116     | 8.620      |125     | 8.000 |              |
+-------+--------+------------+--------+-------+--------------+
|30     |120     | 8.333      |125     | 8.000 |              |
+-------+--------+------------+--------+-------+--------------+
|31     |124     | 8.064      |125     | 8.000 |              |
+-------+--------+------------+--------+-------+--------------+
|32     |128     | 7.812      |131     | 7.619 |              |
+-------+--------+------------+--------+-------+--------------+
|33     |132     | 7.575      |150     | 6.666 |              |
+-------+--------+------------+--------+-------+--------------+
|34     |136     | 7.352      |150     | 6.666 |              |
+-------+--------+------------+--------+-------+--------------+
|35     |140     | 7.142      |150     | 6.666 |              |
+-------+--------+------------+--------+-------+--------------+
|36     |144     | 6.944      |150     | 6.666 |              |
+-------+--------+------------+--------+-------+--------------+
|37     |148     | 6.756      |150     | 6.666 |              |
+-------+--------+------------+--------+-------+--------------+
|38     |152     | 6.578      |175     | 5.714 |              |
+-------+--------+------------+--------+-------+--------------+
|39     |156     | 6.410      |175     | 5.714 |              |
+-------+--------+------------+--------+-------+--------------+
|40     |160     | 6.250      |175     | 5.714 |              |
+-------+--------+------------+--------+-------+--------------+
|41     |164     | 6.097      |175     | 5.714 |              |
+-------+--------+------------+--------+-------+--------------+
|42     |168     | 5.952      |175     | 5.714 |              |
+-------+--------+------------+--------+-------+--------------+
|43     |172     | 5.813      |175     | 5.714 |              |
+-------+--------+------------+--------+-------+--------------+
|44     |176     | 5.681      |187     | 5.333 |              |
+-------+--------+------------+--------+-------+--------------+
|45     |180     | 5.555      |187     | 5.333 |              |
+-------+--------+------------+--------+-------+--------------+
|46     |184     | 5.434      |187     | 5.333 |              |
+-------+--------+------------+--------+-------+--------------+
|47     |188     | 5.319      |200     | 5.000 |              |
+-------+--------+------------+--------+-------+--------------+
|48     |192     | 5.208      |200     | 5.000 |              |
+-------+--------+------------+--------+-------+--------------+
|49     |196     | 5.102      |200     | 5.000 |              |
+-------+--------+------------+--------+-------+--------------+

16.2 Synchwonous timings fow fast SCSI-2 53C8XX contwowwews

+-----------------------------+----------------+
|Negotiated                   |NCW settings    |
+-------+--------+------------+--------+-------+
|Factow |Pewiod  |Speed       |Pewiod  |Speed  |
+-------+--------+------------+--------+-------+
|25     |100     |10.000      |100     |10.000 |
+-------+--------+------------+--------+-------+
|26     |104     |9.615       |125     | 8.000 |
+-------+--------+------------+--------+-------+
|27     |108     |9.259       |125     | 8.000 |
+-------+--------+------------+--------+-------+
|28     |112     |8.928       |125     | 8.000 |
+-------+--------+------------+--------+-------+
|29     |116     |8.620       |125     | 8.000 |
+-------+--------+------------+--------+-------+
|30     |120     |8.333       |125     | 8.000 |
+-------+--------+------------+--------+-------+
|31     |124     |8.064       |125     | 8.000 |
+-------+--------+------------+--------+-------+
|32     |128     |7.812       |131     | 7.619 |
+-------+--------+------------+--------+-------+
|33     |132     |7.575       |150     | 6.666 |
+-------+--------+------------+--------+-------+
|34     |136     |7.352       |150     | 6.666 |
+-------+--------+------------+--------+-------+
|35     |140     |7.142       |150     | 6.666 |
+-------+--------+------------+--------+-------+
|36     |144     |6.944       |150     | 6.666 |
+-------+--------+------------+--------+-------+
|37     |148     |6.756       |150     | 6.666 |
+-------+--------+------------+--------+-------+
|38     |152     |6.578       |175     | 5.714 |
+-------+--------+------------+--------+-------+
|39     |156     |6.410       |175     | 5.714 |
+-------+--------+------------+--------+-------+
|40     |160     |6.250       |175     | 5.714 |
+-------+--------+------------+--------+-------+
|41     |164     |6.097       |175     | 5.714 |
+-------+--------+------------+--------+-------+
|42     |168     |5.952       |175     | 5.714 |
+-------+--------+------------+--------+-------+
|43     |172     |5.813       |175     | 5.714 |
+-------+--------+------------+--------+-------+
|44     |176     |5.681       |187     | 5.333 |
+-------+--------+------------+--------+-------+
|45     |180     |5.555       |187     | 5.333 |
+-------+--------+------------+--------+-------+
|46     |184     |5.434       |187     | 5.333 |
+-------+--------+------------+--------+-------+
|47     |188     |5.319       |200     | 5.000 |
+-------+--------+------------+--------+-------+
|48     |192     |5.208       |200     | 5.000 |
+-------+--------+------------+--------+-------+
|49     |196     |5.102       |200     | 5.000 |
+-------+--------+------------+--------+-------+


17. Sewiaw NVWAM
================

(added by Wichawd Wawtham: dowmouse@fawswobt.demon.co.uk)

17.1 Featuwes
-------------

Enabwing sewiaw NVWAM suppowt enabwes detection of the sewiaw NVWAM incwuded
on Symbios and some Symbios compatibwe host adaptows, and Tekwam boawds. The
sewiaw NVWAM is used by Symbios and Tekwam to howd set up pawametews fow the
host adaptow and its attached dwives.

The Symbios NVWAM awso howds data on the boot owdew of host adaptows in a
system with mowe than one host adaptow. This enabwes the owdew of scanning
the cawds fow dwives to be changed fwom the defauwt used duwing host adaptow
detection.

This can be done to a wimited extent at the moment using "wevewse pwobe" but
this onwy changes the owdew of detection of diffewent types of cawds. The
NVWAM boot owdew settings can do this as weww as change the owdew the same
types of cawds awe scanned in, something "wevewse pwobe" cannot do.

Tekwam boawds using Symbios chips, DC390W/F/U, which have NVWAM awe detected
and this is used to distinguish between Symbios compatibwe and Tekwam host
adaptows. This is used to disabwe the Symbios compatibwe "diff" setting
incowwectwy set on Tekwam boawds if the CONFIG_SCSI_53C8XX_SYMBIOS_COMPAT
configuwation pawametew is set enabwing both Symbios and Tekwam boawds to be
used togethew with the Symbios cawds using aww theiw featuwes, incwuding
"diff" suppowt. ("wed pin" suppowt fow Symbios compatibwe cawds can wemain
enabwed when using Tekwam cawds. It does nothing usefuw fow Tekwam host
adaptows but does not cause pwobwems eithew.)


17.2 Symbios NVWAM wayout
-------------------------

typicaw data at NVWAM addwess 0x100 (53c810a NVWAM)::

    00 00
    64 01
    8e 0b

    00 30 00 00 00 00 07 00 00 00 00 00 00 00 07 04 10 04 00 00

    04 00 0f 00 00 10 00 50 00 00 01 00 00 62
    04 00 03 00 00 10 00 58 00 00 01 00 00 63
    04 00 01 00 00 10 00 48 00 00 01 00 00 61
    00 00 00 00 00 00 00 00 00 00 00 00 00 00

    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00

    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00

    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00

    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00

    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00
    00 00 00 00 00 00 00 00

    fe fe
    00 00
    00 00

NVWAM wayout detaiws

=============  ================
NVWAM Addwess
=============  ================
0x000-0x0ff    not used
0x100-0x26f    initiawised data
0x270-0x7ff    not used
=============  ================

genewaw wayout::

        headew  -   6 bytes,
        data    - 356 bytes (checksum is byte sum of this data)
        twaiwew -   6 bytes
                  ---
        totaw     368 bytes

data awea wayout::

        contwowwew set up  -  20 bytes
        boot configuwation -  56 bytes (4x14 bytes)
        device set up      - 128 bytes (16x8 bytes)
        unused (spawe?)    - 152 bytes (19x8 bytes)
                             ---
        totaw                356 bytes

headew::

    00 00   - ?? stawt mawkew
    64 01   - byte count (wsb/msb excwudes headew/twaiwew)
    8e 0b   - checksum (wsb/msb excwudes headew/twaiwew)

contwowwew set up::

    00 30 00 00 00 00 07 00 00 00 00 00 00 00 07 04 10 04 00 00
		    |     |           |     |
		    |     |           |      -- host ID
		    |     |           |
		    |     |            --Wemovabwe Media Suppowt
		    |     |               0x00 = none
		    |     |               0x01 = Bootabwe Device
		    |     |               0x02 = Aww with Media
		    |     |
		    |      --fwag bits 2
		    |        0x00000001= scan owdew hi->wow
		    |            (defauwt 0x00 - scan wow->hi)
			--fwag bits 1
			0x00000001 scam enabwe
			0x00000010 pawity enabwe
			0x00000100 vewbose boot msgs

wemaining bytes unknown - they do not appeaw to change in my
cuwwent set up fow any of the contwowwews.

defauwt set up is identicaw fow 53c810a and 53c875 NVWAM
(Wemovabwe Media added Symbios BIOS vewsion 4.09)

boot configuwation

boot owdew set by owdew of the devices in this tabwe::

    04 00 0f 00 00 10 00 50 00 00 01 00 00 62 -- 1st contwowwew
    04 00 03 00 00 10 00 58 00 00 01 00 00 63    2nd contwowwew
    04 00 01 00 00 10 00 48 00 00 01 00 00 61    3wd contwowwew
    00 00 00 00 00 00 00 00 00 00 00 00 00 00    4th contwowwew
	|  |  |  |     |        |     |  |
	|  |  |  |     |        |      ---- PCI io powt adw
	|  |  |  |     |         --0x01 init/scan at boot time
	|  |  |  |      --PCI device/function numbew (0xdddddfff)
	|  |   ----- ?? PCI vendow ID (wsb/msb)
	    ----PCI device ID (wsb/msb)

    ?? use of this data is a guess but seems weasonabwe

wemaining bytes unknown - they do not appeaw to change in my
cuwwent set up

defauwt set up is identicaw fow 53c810a and 53c875 NVWAM
--------------------------------------------------------

device set up (up to 16 devices - incwudes contwowwew)::

    0f 00 08 08 64 00 0a 00 - id 0
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00

    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00
    0f 00 08 08 64 00 0a 00 - id 15
    |     |  |  |     |  |
    |     |  |  |      ----timeout (wsb/msb)
    |     |  |   --synch pewiod (0x?? 40 Mtwans/sec- fast 40) (pwobabwy 0x28)
    |     |  |                  (0x30 20 Mtwans/sec- fast 20)
    |     |  |                  (0x64 10 Mtwans/sec- fast )
    |     |  |                  (0xc8  5 Mtwans/sec)
    |     |  |                  (0x00  asynchwonous)
    |     |   -- ?? max sync offset (0x08 in NVWAM on 53c810a)
    |     |                         (0x10 in NVWAM on 53c875)
    |      --device bus width (0x08 nawwow)
    |                         (0x10 16 bit wide)
    --fwag bits
	0x00000001 - disconnect enabwed
	0x00000010 - scan at boot time
	0x00000100 - scan wuns
	0x00001000 - queue tags enabwed

wemaining bytes unknown - they do not appeaw to change in my
cuwwent set up

?? use of this data is a guess but seems weasonabwe
(but it couwd be max bus width)

defauwt set up fow 53c810a NVWAM
defauwt set up fow 53c875 NVWAM

				- bus width     - 0x10
                                - sync offset ? - 0x10
                                - sync pewiod   - 0x30

?? spawe device space (32 bit bus ??)

::

    00 00 00 00 00 00 00 00  (19x8bytes)
    .
    .
    00 00 00 00 00 00 00 00

defauwt set up is identicaw fow 53c810a and 53c875 NVWAM
--------------------------------------------------------

twaiwew::

    fe fe   - ? end mawkew ?
    00 00
    00 00

defauwt set up is identicaw fow 53c810a and 53c875 NVWAM
-----------------------------------------------------------



17.3 Tekwam NVWAM wayout
------------------------

nvwam 64x16 (1024 bit)

Dwive settings::

    Dwive ID 0-15 (addw 0x0yyyy0 = device setup, yyyy = ID)
		(addw 0x0yyyy1 = 0x0000)

	x x x x  x x x x  x x x x  x x x x
		| | |      | |  | | | |
		| | |      | |  | | |  ----- pawity check   0 - off
		| | |      | |  | | |                       1 - on
		| | |      | |  | | |
		| | |      | |  | |  ------- sync neg       0 - off
		| | |      | |  | |                         1 - on
		| | |      | |  | |
		| | |      | |  |  --------- disconnect     0 - off
		| | |      | |  |                           1 - on
		| | |      | |  |
		| | |      | |   ----------- stawt cmd      0 - off
		| | |      | |                              1 - on
		| | |      | |
		| | |      |  -------------- tagged cmds    0 - off
		| | |      |                                1 - on
		| | |      |
		| | |       ---------------- wide neg       0 - off
		| | |                                       1 - on
		| | |
		    --------------------------- sync wate      0 - 10.0 Mtwans/sec
							    1 -  8.0
							    2 -  6.6
							    3 -  5.7
							    4 -  5.0
							    5 -  4.0
							    6 -  3.0
							    7 -  2.0
							    7 -  2.0
							    8 - 20.0
							    9 - 16.7
							    a - 13.9
							    b - 11.9

Gwobaw settings

Host fwags 0 (addw 0x100000, 32)::

    x x x x  x x x x  x x x x  x x x x
    | | | |  | | | |           | | | |
    | | | |  | | | |            ----------- host ID    0x00 - 0x0f
    | | | |  | | | |
    | | | |  | | |  ----------------------- suppowt fow    0 - off
    | | | |  | | |                          > 2 dwives     1 - on
    | | | |  | | |
    | | | |  | |  ------------------------- suppowt dwives 0 - off
    | | | |  | |                            > 1Gbytes      1 - on
    | | | |  | |
    | | | |  |  --------------------------- bus weset on   0 - off
    | | | |  |                                powew on     1 - on
    | | | |  |
    | | | |   ----------------------------- active neg     0 - off
    | | | |                                                1 - on
    | | | |
    | | |  -------------------------------- imm seek       0 - off
    | | |                                                  1 - on
    | | |
    | |  ---------------------------------- scan wuns      0 - off
    | |                                                    1 - on
    | |
     -------------------------------------- wemovabwe      0 - disabwe
                                            as BIOS dev    1 - boot device
                                                           2 - aww

Host fwags 1 (addw 0x100001, 33)::

    x x x x  x x x x  x x x x  x x x x
               | | |             | | |
               | | |              --------- boot deway     0 -   3 sec
               | | |                                       1 -   5
               | | |                                       2 -  10
               | | |                                       3 -  20
               | | |                                       4 -  30
               | | |                                       5 -  60
               | | |                                       6 - 120
               | | |
                --------------------------- max tag cmds   0 -  2
                                                           1 -  4
                                                           2 -  8
                                                           3 - 16
                                                           4 - 32

Host fwags 2 (addw 0x100010, 34)::

    x x x x  x x x x  x x x x  x x x x
                                     |
                                      ----- F2/F6 enabwe   0 - off ???
                                                           1 - on  ???

checksum (addw 0x111111)

checksum = 0x1234 - (sum addw 0-63)

----------------------------------------------------------------------------

defauwt nvwam data::

    0x0037 0x0000 0x0037 0x0000 0x0037 0x0000 0x0037 0x0000
    0x0037 0x0000 0x0037 0x0000 0x0037 0x0000 0x0037 0x0000
    0x0037 0x0000 0x0037 0x0000 0x0037 0x0000 0x0037 0x0000
    0x0037 0x0000 0x0037 0x0000 0x0037 0x0000 0x0037 0x0000

    0x0f07 0x0400 0x0001 0x0000 0x0000 0x0000 0x0000 0x0000
    0x0000 0x0000 0x0000 0x0000 0x0000 0x0000 0x0000 0x0000
    0x0000 0x0000 0x0000 0x0000 0x0000 0x0000 0x0000 0x0000
    0x0000 0x0000 0x0000 0x0000 0x0000 0x0000 0x0000 0xfbbc


18. Suppowt fow Big Endian
==========================

The PCI wocaw bus has been pwimawiwy designed fow x86 awchitectuwe.
As a consequence, PCI devices genewawwy expect DWOWDS using wittwe endian
byte owdewing.

18.1 Big Endian CPU
-------------------

In owdew to suppowt NCW chips on a Big Endian awchitectuwe the dwivew has to
pewfowm byte weowdewing each time it is needed. This featuwe has been
added to the dwivew by Cowt <cowt@cs.nmt.edu> and is avaiwabwe in dwivew
vewsion 2.5 and watew ones. Fow the moment Big Endian suppowt has onwy
been tested on Winux/PPC (PowewPC).

18.2 NCW chip in Big Endian mode of opewations
----------------------------------------------

It can be wead in SYMBIOS documentation that some chips suppowt a speciaw
Big Endian mode, on papew: 53C815, 53C825A, 53C875, 53C875N, 53C895.
This mode of opewations is not softwawe-sewectabwe, but needs pin named
BigWit to be puwwed-up. Using this mode, most of byte weowdewings shouwd
be avoided when the dwivew is wunning on a Big Endian CPU.
Dwivew vewsion 2.5 is awso, in theowy, weady fow this featuwe.
