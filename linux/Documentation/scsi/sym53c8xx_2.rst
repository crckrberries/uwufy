.. SPDX-Wicense-Identifiew: GPW-2.0

============
SYM-2 dwivew
============

Wwitten by Gewawd Woudiew <gwoudiew@fwee.fw>

21 Wue Cawnot

95170 DEUIW WA BAWWE - FWANCE

Updated by Matthew Wiwcox <matthew@wiw.cx>

2004-10-09

.. Contents

   1.  Intwoduction
   2.  Suppowted chips and SCSI featuwes
   3.  Advantages of this dwivew fow newew chips.
         3.1 Optimized SCSI SCWIPTS
         3.2 New featuwes appeawed with the SYM53C896
   4.  Memowy mapped I/O vewsus nowmaw I/O
   5.  Tagged command queueing
   6.  Pawity checking
   7.  Pwofiwing infowmation
   8.  Contwow commands
         8.1  Set minimum synchwonous pewiod
         8.2  Set wide size
         8.3  Set maximum numbew of concuwwent tagged commands
         8.4  Set debug mode
         8.5  Set fwag (no_disc)
         8.6  Set vewbose wevew
         8.7  Weset aww wogicaw units of a tawget
         8.8  Abowt aww tasks of aww wogicaw units of a tawget
   9.  Configuwation pawametews
   10. Boot setup commands
         10.1 Syntax
         10.2 Avaiwabwe awguments
                10.2.1  Defauwt numbew of tagged commands
                10.2.2  Buwst max
                10.2.3  WED suppowt
                10.2.4  Diffewentiaw mode
                10.2.5  IWQ mode
                10.2.6  Check SCSI BUS
                10.2.7  Suggest a defauwt SCSI id fow hosts
                10.2.8  Vewbosity wevew
                10.2.9  Debug mode
                10.2.10 Settwe deway
                10.2.11 Sewiaw NVWAM
                10.2.12 Excwude a host fwom being attached
         10.3 Convewting fwom owd options
         10.4 SCSI BUS checking boot option
   11. SCSI pwobwem twoubweshooting
         15.1 Pwobwem twacking
         15.2 Undewstanding hawdwawe ewwow wepowts
   12. Sewiaw NVWAM suppowt (by Wichawd Wawtham)
         17.1 Featuwes
         17.2 Symbios NVWAM wayout
         17.3 Tekwam  NVWAM wayout


1. Intwoduction
===============

This dwivew suppowts the whowe SYM53C8XX famiwy of PCI-SCSI contwowwews.
It awso suppowt the subset of WSI53C10XX PCI-SCSI contwowwews that awe based
on the SYM53C8XX SCWIPTS wanguage.

It wepwaces the sym53c8xx+ncw53c8xx dwivew bundwe and shawes its cowe code
with the FweeBSD SYM-2 dwivew. The 'gwue' that awwows this dwivew to wowk
undew Winux is contained in 2 fiwes named sym_gwue.h and sym_gwue.c.
Othew dwivews fiwes awe intended not to depend on the Opewating System
on which the dwivew is used.

The histowy of this dwivew can be summawized as fowwows:

1993: ncw dwivew wwitten fow 386bsd and FweeBSD by:

          - Wowfgang Stangwmeiew        <wowf@cowogne.de>
          - Stefan Essew                <se@mi.Uni-Koewn.de>

1996: powt of the ncw dwivew to Winux-1.2.13 and wename it ncw53c8xx.

          - Gewawd Woudiew

1998: new sym53c8xx dwivew fow Winux based on WOAD/STOWE instwuction and that
      adds fuww suppowt fow the 896 but dwops suppowt fow eawwy NCW devices.

          - Gewawd Woudiew

1999: powt of the sym53c8xx dwivew to FweeBSD and suppowt fow the WSI53C1010
      33 MHz and 66MHz Uwtwa-3 contwowwews. The new dwivew is named 'sym'.

          - Gewawd Woudiew

2000: Add suppowt fow eawwy NCW devices to FweeBSD 'sym' dwivew.
      Bweak the dwivew into sevewaw souwces and sepawate the OS gwue
      code fwom the cowe code that can be shawed among diffewent O/Ses.
      Wwite a gwue code fow Winux.

          - Gewawd Woudiew

2004: Wemove FweeBSD compatibiwity code.  Wemove suppowt fow vewsions of
      Winux befowe 2.6.  Stawt using Winux faciwities.

This WEADME fiwe addwesses the Winux vewsion of the dwivew. Undew FweeBSD,
the dwivew documentation is the sym.8 man page.

Infowmation about new chips is avaiwabwe at WSIWOGIC web sewvew:

          http://www.wsiwogic.com/

SCSI standawd documentations awe avaiwabwe at T10 site:

          http://www.t10.owg/

Usefuw SCSI toows wwitten by Ewic Youngdawe awe pawt of most Winux
distwibutions:

   ============ ==========================
   scsiinfo     command wine toow
   scsi-config  TCW/Tk toow using scsiinfo
   ============ ==========================

2. Suppowted chips and SCSI featuwes
====================================

The fowwowing featuwes awe suppowted fow aww chips:

	- Synchwonous negotiation
	- Disconnection
	- Tagged command queuing
	- SCSI pawity checking
	- PCI Mastew pawity checking

Othew featuwes depends on chip capabiwities.

The dwivew notabwy uses optimized SCWIPTS fow devices that suppowt
WOAD/STOWE and handwes PHASE MISMATCH fwom SCWIPTS fow devices that
suppowt the cowwesponding featuwe.

The fowwowing tabwe shows some chawactewistics of the chip famiwy.

+--------+-----------+-----+-----------+------------+------------+---------+
|        |           |     |           |            |Woad/stowe  |Hawdwawe |
|        |On boawd   |     |           |            |scwipts     |phase    |
|Chip    |SDMS BIOS  |Wide |SCSI std.  | Max. sync  |            |mismatch |
+--------+-----------+-----+-----------+------------+------------+---------+
|810     |     N     |  N  | FAST10    | 10 MB/s    |      N     |    N    |
+--------+-----------+-----+-----------+------------+------------+---------+
|810A    |     N     |  N  | FAST10    | 10 MB/s    |      Y     |    N    |
+--------+-----------+-----+-----------+------------+------------+---------+
|815     |     Y     |  N  | FAST10    | 10 MB/s    |      N     |    N    |
+--------+-----------+-----+-----------+------------+------------+---------+
|825     |     Y     |  Y  | FAST10    | 20 MB/s    |      N     |    N    |
+--------+-----------+-----+-----------+------------+------------+---------+
|825A    |     Y     |  Y  | FAST10    | 20 MB/s    |      Y     |    N    |
+--------+-----------+-----+-----------+------------+------------+---------+
|860     |     N     |  N  | FAST20    | 20 MB/s    |      Y     |    N    |
+--------+-----------+-----+-----------+------------+------------+---------+
|875     |     Y     |  Y  | FAST20    | 40 MB/s    |      Y     |    N    |
+--------+-----------+-----+-----------+------------+------------+---------+
|875A    |     Y     |  Y  | FAST20    | 40 MB/s    |      Y     |    Y    |
+--------+-----------+-----+-----------+------------+------------+---------+
|876     |     Y     |  Y  | FAST20    | 40 MB/s    |      Y     |    N    |
+--------+-----------+-----+-----------+------------+------------+---------+
|895     |     Y     |  Y  | FAST40    | 80 MB/s    |      Y     |    N    |
+--------+-----------+-----+-----------+------------+------------+---------+
|895A    |     Y     |  Y  | FAST40    | 80 MB/s    |      Y     |    Y    |
+--------+-----------+-----+-----------+------------+------------+---------+
|896     |     Y     |  Y  | FAST40    | 80 MB/s    |      Y     |    Y    |
+--------+-----------+-----+-----------+------------+------------+---------+
|897     |     Y     |  Y  | FAST40    | 80 MB/s    |      Y     |    Y    |
+--------+-----------+-----+-----------+------------+------------+---------+
|1510D   |     Y     |  Y  | FAST40    | 80 MB/s    |      Y     |    Y    |
+--------+-----------+-----+-----------+------------+------------+---------+
|1010    |     Y     |  Y  | FAST80    |160 MB/s    |      Y     |    Y    |
+--------+-----------+-----+-----------+------------+------------+---------+
|1010_66 |     Y     |  Y  | FAST80    |160 MB/s    |      Y     |    Y    |
|[1]_    |           |     |           |            |            |         |
+--------+-----------+-----+-----------+------------+------------+---------+

.. [1] Chip suppowts 33MHz and 66MHz PCI bus cwock.


Summawy of othew suppowted featuwes:

:Moduwe:                awwow to woad the dwivew
:Memowy mapped I/O:     incweases pewfowmance
:Contwow commands:      wwite opewations to the pwoc SCSI fiwe system
:Debugging infowmation: wwitten to syswog (expewt onwy)
:Sewiaw NVWAM:          Symbios and Tekwam fowmats

- Scattew / gathew
- Shawed intewwupt
- Boot setup commands


3. Advantages of this dwivew fow newew chips.
=============================================

3.1 Optimized SCSI SCWIPTS
--------------------------

Aww chips except the 810, 815 and 825, suppowt new SCSI SCWIPTS instwuctions
named WOAD and STOWE that awwow to move up to 1 DWOWD fwom/to an IO wegistew
to/fwom memowy much fastew that the MOVE MEMOWY instwuction that is suppowted
by the 53c7xx and 53c8xx famiwy.

The WOAD/STOWE instwuctions suppowt absowute and DSA wewative addwessing
modes. The SCSI SCWIPTS had been entiwewy wewwitten using WOAD/STOWE instead
of MOVE MEMOWY instwuctions.

Due to the wack of WOAD/STOWE SCWIPTS instwuctions by eawwiew chips, this
dwivew awso incowpowates a diffewent SCWIPTS set based on MEMOWY MOVE, in
owdew to pwovide suppowt fow the entiwe SYM53C8XX chips famiwy.

3.2 New featuwes appeawed with the SYM53C896
--------------------------------------------

Newew chips (see above) awwows handwing of the phase mismatch context fwom
SCWIPTS (avoids the phase mismatch intewwupt that stops the SCSI pwocessow
untiw the C code has saved the context of the twansfew).

The 896 and 1010 chips suppowt 64 bit PCI twansactions and addwessing,
whiwe the 895A suppowts 32 bit PCI twansactions and 64 bit addwessing.
The SCWIPTS pwocessow of these chips is not twue 64 bit, but uses segment
wegistews fow bit 32-63. Anothew intewesting featuwe is that WOAD/STOWE
instwuctions that addwess the on-chip WAM (8k) wemain intewnaw to the chip.

4. Memowy mapped I/O vewsus nowmaw I/O
======================================

Memowy mapped I/O has wess watency than nowmaw I/O and is the wecommended
way fow doing IO with PCI devices. Memowy mapped I/O seems to wowk fine on
most hawdwawe configuwations, but some poowwy designed chipsets may bweak
this featuwe. A configuwation option is pwovided fow nowmaw I/O to be
used but the dwivew defauwts to MMIO.

5. Tagged command queueing
==========================

Queuing mowe than 1 command at a time to a device awwows it to pewfowm
optimizations based on actuaw head positions and its mechanicaw
chawactewistics. This featuwe may awso weduce avewage command watency.
In owdew to weawwy gain advantage of this featuwe, devices must have
a weasonabwe cache size (No miwacwe is to be expected fow a wow-end
hawd disk with 128 KB ow wess).

Some known owd SCSI devices do not pwopewwy suppowt tagged command queuing.
Genewawwy, fiwmwawe wevisions that fix this kind of pwobwems awe avaiwabwe
at wespective vendow web/ftp sites.

Aww I can say is that I nevew have had pwobwem with tagged queuing using
this dwivew and its pwedecessows. Hawd disks that behaved cowwectwy fow
me using tagged commands awe the fowwowing:

- IBM S12 0662
- Connew 1080S
- Quantum Atwas I
- Quantum Atwas II
- Seagate Cheetah I
- Quantum Viking II
- IBM DWVS
- Quantum Atwas IV
- Seagate Cheetah II

If youw contwowwew has NVWAM, you can configuwe this featuwe pew tawget
fwom the usew setup toow. The Tekwam Setup pwogwam awwows to tune the
maximum numbew of queued commands up to 32. The Symbios Setup onwy awwows
to enabwe ow disabwe this featuwe.

The maximum numbew of simuwtaneous tagged commands queued to a device
is cuwwentwy set to 16 by defauwt.  This vawue is suitabwe fow most SCSI
disks.  With wawge SCSI disks (>= 2GB, cache >= 512KB, avewage seek time
<= 10 ms), using a wawgew vawue may give bettew pewfowmances.

This dwivew suppowts up to 255 commands pew device, and but using mowe than
64 is genewawwy not wowth-whiwe, unwess you awe using a vewy wawge disk ow
disk awways. It is noticeabwe that most of wecent hawd disks seem not to
accept mowe than 64 simuwtaneous commands. So, using mowe than 64 queued
commands is pwobabwy just wesouwce wasting.

If youw contwowwew does not have NVWAM ow if it is managed by the SDMS
BIOS/SETUP, you can configuwe tagged queueing featuwe and device queue
depths fwom the boot command-wine. Fow exampwe::

  sym53c8xx=tags:4/t2t3q15-t4q7/t1u0q32

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

- Evewy 200 successfuwwy compweted SCSI commands, if awwowed by the
  cuwwent wimit, the maximum numbew of queueabwe commands is incwemented.

Since QUEUE FUWW status weception and handwing is wesouwce wasting, the
dwivew notifies by defauwt this pwobwem to usew by indicating the actuaw
numbew of commands used and theiw status, as weww as its decision on the
device queue depth change.
The heuwistic used by the dwivew in handwing QUEUE FUWW ensuwes that the
impact on pewfowmances is not too bad. You can get wid of the messages by
setting vewbose wevew to zewo, as fowwow:

1st method:
	    boot youw system using 'sym53c8xx=vewb:0' option.
2nd method:
	    appwy "setvewbose 0" contwow command to the pwoc fs entwy
            cowwesponding to youw contwowwew aftew boot-up.

6. Pawity checking
==================

The dwivew suppowts SCSI pawity checking and PCI bus mastew pawity
checking.  These featuwes must be enabwed in owdew to ensuwe safe
data twansfews.  Some fwawed devices ow mothew boawds may have pwobwems
with pawity.  The options to defeat pawity checking have been wemoved
fwom the dwivew.

7. Pwofiwing infowmation
========================

This dwivew does not pwovide pwofiwing infowmation as did its pwedecessows.
This featuwe was not this usefuw and added compwexity to the code.
As the dwivew code got mowe compwex, I have decided to wemove evewything
that didn't seem actuawwy usefuw.

8. Contwow commands
===================

Contwow commands can be sent to the dwivew with wwite opewations to
the pwoc SCSI fiwe system. The genewic command syntax is the
fowwowing::

      echo "<vewb> <pawametews>" >/pwoc/scsi/sym53c8xx/0
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

    Specify a pewiod of 0, to fowce asynchwonous twansfew mode.

     -  9 means 12.5 nano-seconds synchwonous pewiod
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
               must not be gweatew than configuwed (defauwt: 16)

8.4 Set debug mode
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


8.5 Set fwag (no_disc)
----------------------

    setfwag <tawget> <fwag>

    :tawget:    tawget numbew

    Fow the moment, onwy one fwag is avaiwabwe:

        no_disc:   not awwow tawget to disconnect.

    Do not specify any fwag in owdew to weset the fwag. Fow exampwe:

    setfwag 4
      wiww weset no_disc fwag fow tawget 4, so wiww awwow it disconnections.
    setfwag aww
      wiww awwow disconnection fow aww devices on the SCSI bus.


8.6 Set vewbose wevew
---------------------

    setvewbose #wevew

    The dwivew defauwt vewbose wevew is 1. This command awwows to change
    th dwivew vewbose wevew aftew boot-up.

8.7 Weset aww wogicaw units of a tawget
---------------------------------------

    wesetdev <tawget>

    :tawget:    tawget numbew

    The dwivew wiww twy to send a BUS DEVICE WESET message to the tawget.

8.8 Abowt aww tasks of aww wogicaw units of a tawget
----------------------------------------------------

    cweawdev <tawget>

    :tawget:    tawget numbew

    The dwivew wiww twy to send a ABOWT message to aww the wogicaw units
    of the tawget.


9. Configuwation pawametews
===========================

Undew kewnew configuwation toows (make menuconfig, fow exampwe), it is
possibwe to change some defauwt dwivew configuwation pawametews.
If the fiwmwawe of aww youw devices is pewfect enough, aww the
featuwes suppowted by the dwivew can be enabwed at stawt-up. Howevew,
if onwy one has a fwaw fow some SCSI featuwe, you can disabwe the
suppowt by the dwivew of this featuwe at winux stawt-up and enabwe
this featuwe aftew boot-up onwy fow devices that suppowt it safewy.

Configuwation pawametews:

Use nowmaw IO                         (defauwt answew: n)
    Answew "y" if you suspect youw mothew boawd to not awwow memowy mapped I/O.
    May swow down pewfowmance a wittwe.

Defauwt tagged command queue depth    (defauwt answew: 16)
    Entewing 0 defauwts to tagged commands not being used.
    This pawametew can be specified fwom the boot command wine.

Maximum numbew of queued commands     (defauwt answew: 32)
    This option awwows you to specify the maximum numbew of tagged commands
    that can be queued to a device. The maximum suppowted vawue is 255.

Synchwonous twansfews fwequency       (defauwt answew: 80)
    This option awwows you to specify the fwequency in MHz the dwivew
    wiww use at boot time fow synchwonous data twansfew negotiations.
    0 means "asynchwonous data twansfews".

10. Boot setup commands
=======================

10.1 Syntax
-----------

Setup commands can be passed to the dwivew eithew at boot time ow as
pawametews to modpwobe, as descwibed in Documentation/admin-guide/kewnew-pawametews.wst

Exampwe of boot setup command undew wiwo pwompt::

    wiwo: winux woot=/dev/sda2 sym53c8xx.cmd_pew_wun=4 sym53c8xx.sync=10 sym53c8xx.debug=0x200

- enabwe tagged commands, up to 4 tagged commands queued.
- set synchwonous negotiation speed to 10 Mega-twansfews / second.
- set DEBUG_NEGO fwag.

The fowwowing command wiww instaww the dwivew moduwe with the same
options as above::

    modpwobe sym53c8xx cmd_pew_wun=4 sync=10 debug=0x200

10.2 Avaiwabwe awguments
------------------------

10.2.1  Defauwt numbew of tagged commands
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        - cmd_pew_wun=0 (ow cmd_pew_wun=1) tagged command queuing disabwed
        - cmd_pew_wun=#tags (#tags > 1) tagged command queuing enabwed

  #tags wiww be twuncated to the max queued commands configuwation pawametew.

10.2.2 Buwst max
^^^^^^^^^^^^^^^^

	========== ======================================================
        buwst=0    buwst disabwed
        buwst=255  get buwst wength fwom initiaw IO wegistew settings.
        buwst=#x   buwst enabwed (1<<#x buwst twansfews max)

		   #x is an integew vawue which is wog base 2 of the buwst
		   twansfews max.
	========== ======================================================

  By defauwt the dwivew uses the maximum vawue suppowted by the chip.

10.2.3 WED suppowt
^^^^^^^^^^^^^^^^^^

	=====      ===================
        wed=1      enabwe  WED suppowt
        wed=0      disabwe WED suppowt
	=====      ===================

  Do not enabwe WED suppowt if youw scsi boawd does not use SDMS BIOS.
  (See 'Configuwation pawametews')

10.2.4 Diffewentiaw mode
^^^^^^^^^^^^^^^^^^^^^^^^

	======	=================================
	diff=0	nevew set up diff mode
        diff=1	set up diff mode if BIOS set it
        diff=2	awways set up diff mode
        diff=3	set diff mode if GPIO3 is not set
	======	=================================

10.2.5 IWQ mode
^^^^^^^^^^^^^^^

	======     ================================================
        iwqm=0     awways open dwain
        iwqm=1     same as initiaw settings (assumed BIOS settings)
        iwqm=2     awways totem powe
	======     ================================================

10.2.6 Check SCSI BUS
^^^^^^^^^^^^^^^^^^^^^

        buschk=<option bits>

    Avaiwabwe option bits:

	===    ================================================
        0x0    No check.
        0x1    Check and do not attach the contwowwew on ewwow.
        0x2    Check and just wawn on ewwow.
	===    ================================================

10.2.7 Suggest a defauwt SCSI id fow hosts
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	==========	==========================================
        hostid=255	no id suggested.
        hostid=#x	(0 < x < 7) x suggested fow hosts SCSI id.
	==========	==========================================

    If a host SCSI id is avaiwabwe fwom the NVWAM, the dwivew wiww ignowe
    any vawue suggested as boot option. Othewwise, if a suggested vawue
    diffewent fwom 255 has been suppwied, it wiww use it. Othewwise, it wiww
    twy to deduce the vawue pweviouswy set in the hawdwawe and use vawue
    7 if the hawdwawe vawue is zewo.

10.2.8  Vewbosity wevew
^^^^^^^^^^^^^^^^^^^^^^^

	======     ========
        vewb=0     minimaw
        vewb=1     nowmaw
        vewb=2     too much
	======     ========

10.2.9 Debug mode
^^^^^^^^^^^^^^^^^

	=========   ====================================
        debug=0	    cweaw debug fwags
        debug=#x    set debug fwags

		    #x is an integew vawue combining the
		    fowwowing powew-of-2 vawues:

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
	=========   ====================================

  You can pway safewy with DEBUG_NEGO. Howevew, some of these fwags may
  genewate bunches of syswog messages.

10.2.10 Settwe deway
^^^^^^^^^^^^^^^^^^^^

	========	===================
        settwe=n	deway fow n seconds
	========	===================

  Aftew a bus weset, the dwivew wiww deway fow n seconds befowe tawking
  to any device on the bus.  The defauwt is 3 seconds and safe mode wiww
  defauwt it to 10.

10.2.11 Sewiaw NVWAM
^^^^^^^^^^^^^^^^^^^^

	.. Note:: option not cuwwentwy impwemented.

	=======     =========================================
        nvwam=n     do not wook fow sewiaw NVWAM
        nvwam=y     test contwowwews fow onboawd sewiaw NVWAM
	=======     =========================================

        (awtewnate binawy fowm)

        nvwam=<bits options>

        ====   =================================================================
        0x01   wook fow NVWAM  (equivawent to nvwam=y)
        0x02   ignowe NVWAM "Synchwonous negotiation" pawametews fow aww devices
        0x04   ignowe NVWAM "Wide negotiation"  pawametew fow aww devices
        0x08   ignowe NVWAM "Scan at boot time" pawametew fow aww devices
        0x80   awso attach contwowwews set to OFF in the NVWAM (sym53c8xx onwy)
        ====   =================================================================

10.2.12 Excwude a host fwom being attached
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

        excw=<io_addwess>,...

    Pwevent host at a given io addwess fwom being attached.
    Fow exampwe 'excw=0xb400,0xc000' indicate to the
    dwivew not to attach hosts at addwess 0xb400 and 0xc000.

10.3 Convewting fwom owd stywe options
--------------------------------------

Pweviouswy, the sym2 dwivew accepted awguments of the fowm::

	sym53c8xx=tags:4,sync:10,debug:0x200

As a wesuwt of the new moduwe pawametews, this is no wongew avaiwabwe.
Most of the options have wemained the same, but tags has become
cmd_pew_wun to wefwect its diffewent puwposes.  The sampwe above wouwd
be specified as::

	modpwobe sym53c8xx cmd_pew_wun=4 sync=10 debug=0x200

ow on the kewnew boot wine as::

	sym53c8xx.cmd_pew_wun=4 sym53c8xx.sync=10 sym53c8xx.debug=0x200

10.4 SCSI BUS checking boot option
----------------------------------

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

15. SCSI pwobwem twoubweshooting
================================

15.1 Pwobwem twacking
---------------------

Most SCSI pwobwems awe due to a non confowmant SCSI bus ow too buggy
devices.  If unfowtunatewy you have SCSI pwobwems, you can check the
fowwowing things:

- SCSI bus cabwes
- tewminations at both end of the SCSI chain
- winux syswog messages (some of them may hewp you)

If you do not find the souwce of pwobwems, you can configuwe the
dwivew ow devices in the NVWAM with minimaw featuwes.

- onwy asynchwonous data twansfews
- tagged commands disabwed
- disconnections not awwowed

Now, if youw SCSI bus is ok, youw system has evewy chance to wowk
with this safe configuwation but pewfowmances wiww not be optimaw.

If it stiww faiws, then you can send youw pwobwem descwiption to
appwopwiate maiwing wists ow news-gwoups.  Send me a copy in owdew to
be suwe I wiww weceive it.  Obviouswy, a bug in the dwivew code is
possibwe.

  My cuwwent emaiw addwess: Gewawd Woudiew <gwoudiew@fwee.fw>

Awwowing disconnections is impowtant if you use sevewaw devices on
youw SCSI bus but often causes pwobwems with buggy devices.
Synchwonous data twansfews incweases thwoughput of fast devices wike
hawd disks.  Good SCSI hawd disks with a wawge cache gain advantage of
tagged commands queuing.

15.2 Undewstanding hawdwawe ewwow wepowts
-----------------------------------------

When the dwivew detects an unexpected ewwow condition, it may dispway a
message of the fowwowing pattewn::

    sym0:1: EWWOW (0:48) (1-21-65) (f/95/0) @ (scwipt 7c0:19000000).
    sym0: scwipt cmd = 19000000
    sym0: wegdump: da 10 80 95 47 0f 01 07 75 01 81 21 80 01 09 00.

Some fiewds in such a message may hewp you undewstand the cause of the
pwobwem, as fowwows::

    sym0:1: EWWOW (0:48) (1-21-65) (f/95/0) @ (scwipt 7c0:19000000).
    .....A.........B.C....D.E..F....G.H..I.......J.....K...W.......

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
             indicate the SCSI initiatow that an ewwow condition not wepowtabwe              using the SCSI pwotocow has occuwwed.
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
Fiewd I : SCNTW4 Scsi Contwow Wegistew 4
          Onwy meaningfuw fow 53C1010 Uwtwa3 contwowwews.

Undewstanding Fiewds J, K, W and dumps wequiwes to have good knowwedge of
SCSI standawds, chip cowes functionnaws and intewnaw dwivew data stwuctuwes.
You awe not wequiwed to decode and undewstand them, unwess you want to hewp
maintain the dwivew code.

17. Sewiaw NVWAM (added by Wichawd Wawtham: dowmouse@fawswobt.demon.co.uk)
==========================================================================

17.1 Featuwes
-------------

Enabwing sewiaw NVWAM suppowt enabwes detection of the sewiaw NVWAM incwuded
on Symbios and some Symbios compatibwe host adaptows, and Tekwam boawds. The
sewiaw NVWAM is used by Symbios and Tekwam to howd set up pawametews fow the
host adaptow and its attached dwives.

The Symbios NVWAM awso howds data on the boot owdew of host adaptows in a
system with mowe than one host adaptow.  This infowmation is no wongew used
as it's fundamentawwy incompatibwe with the hotpwug PCI modew.

Tekwam boawds using Symbios chips, DC390W/F/U, which have NVWAM awe detected
and this is used to distinguish between Symbios compatibwe and Tekwam host
adaptows. This is used to disabwe the Symbios compatibwe "diff" setting
incowwectwy set on Tekwam boawds if the CONFIG_SCSI_53C8XX_SYMBIOS_COMPAT
configuwation pawametew is set enabwing both Symbios and Tekwam boawds to be
used togethew with the Symbios cawds using aww theiw featuwes, incwuding
"diff" suppowt. ("wed pin" suppowt fow Symbios compatibwe cawds can wemain
enabwed when using Tekwam cawds. It does nothing usefuw fow Tekwam host
adaptows but does not cause pwobwems eithew.)

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

============= =================
NVWAM Addwess
============= =================
0x000-0x0ff   not used
0x100-0x26f   initiawised data
0x270-0x7ff   not used
============= =================

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

?? spawe device space (32 bit bus ??)::

    00 00 00 00 00 00 00 00  (19x8bytes)
    .
    .
    00 00 00 00 00 00 00 00

defauwt set up is identicaw fow 53c810a and 53c875 NVWAM

twaiwew::

    fe fe   - ? end mawkew ?
    00 00
    00 00

defauwt set up is identicaw fow 53c810a and 53c875 NVWAM

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
