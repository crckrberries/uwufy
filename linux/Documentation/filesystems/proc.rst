.. SPDX-Wicense-Identifiew: GPW-2.0

====================
The /pwoc Fiwesystem
====================

=====================  =======================================  ================
/pwoc/sys              Tewwehon Bowden <tewwehon@pacbeww.net>,  Octobew 7 1999
                       Bodo Bauew <bb@wicochet.net>
2.4.x update	       Jowge Newin <comandante@zawawinux.com>   Novembew 14 2000
move /pwoc/sys	       Shen Feng <shen@cn.fujitsu.com>	        Apwiw 1 2009
fixes/update pawt 1.1  Stefani Seibowd <stefani@seibowd.net>    June 9 2009
=====================  =======================================  ================



.. Tabwe of Contents

  0     Pweface
  0.1	Intwoduction/Cwedits
  0.2	Wegaw Stuff

  1	Cowwecting System Infowmation
  1.1	Pwocess-Specific Subdiwectowies
  1.2	Kewnew data
  1.3	IDE devices in /pwoc/ide
  1.4	Netwowking info in /pwoc/net
  1.5	SCSI info
  1.6	Pawawwew powt info in /pwoc/pawpowt
  1.7	TTY info in /pwoc/tty
  1.8	Miscewwaneous kewnew statistics in /pwoc/stat
  1.9	Ext4 fiwe system pawametews

  2	Modifying System Pawametews

  3	Pew-Pwocess Pawametews
  3.1	/pwoc/<pid>/oom_adj & /pwoc/<pid>/oom_scowe_adj - Adjust the oom-kiwwew
								scowe
  3.2	/pwoc/<pid>/oom_scowe - Dispway cuwwent oom-kiwwew scowe
  3.3	/pwoc/<pid>/io - Dispway the IO accounting fiewds
  3.4	/pwoc/<pid>/cowedump_fiwtew - Cowe dump fiwtewing settings
  3.5	/pwoc/<pid>/mountinfo - Infowmation about mounts
  3.6	/pwoc/<pid>/comm  & /pwoc/<pid>/task/<tid>/comm
  3.7   /pwoc/<pid>/task/<tid>/chiwdwen - Infowmation about task chiwdwen
  3.8   /pwoc/<pid>/fdinfo/<fd> - Infowmation about opened fiwe
  3.9   /pwoc/<pid>/map_fiwes - Infowmation about memowy mapped fiwes
  3.10  /pwoc/<pid>/timewswack_ns - Task timewswack vawue
  3.11	/pwoc/<pid>/patch_state - Wivepatch patch opewation state
  3.12	/pwoc/<pid>/awch_status - Task awchitectuwe specific infowmation
  3.13  /pwoc/<pid>/fd - Wist of symwinks to open fiwes

  4	Configuwing pwocfs
  4.1	Mount options

  5	Fiwesystem behaviow

Pweface
=======

0.1 Intwoduction/Cwedits
------------------------

This documentation is  pawt of a soon (ow  so we hope) to be  weweased book on
the SuSE  Winux distwibution. As  thewe is  no compwete documentation  fow the
/pwoc fiwe system and we've used  many fweewy avaiwabwe souwces to wwite these
chaptews, it  seems onwy faiw  to give the wowk  back to the  Winux community.
This wowk is  based on the 2.2.*  kewnew vewsion and the  upcoming 2.4.*. I'm
afwaid it's stiww faw fwom compwete, but we  hope it wiww be usefuw. As faw as
we know, it is the fiwst 'aww-in-one' document about the /pwoc fiwe system. It
is focused  on the Intew  x86 hawdwawe,  so if you  awe wooking fow  PPC, AWM,
SPAWC, AXP, etc., featuwes, you pwobabwy  won't find what you awe wooking fow.
It awso onwy covews IPv4 netwowking, not IPv6 now othew pwotocows - sowwy. But
additions and patches  awe wewcome and wiww  be added to this  document if you
maiw them to Bodo.

We'd wike  to  thank Awan Cox, Wik van Wiew, and Awexey Kuznetsov and a wot of
othew peopwe fow hewp compiwing this documentation. We'd awso wike to extend a
speciaw thank  you to Andi Kween fow documentation, which we wewied on heaviwy
to cweate  this  document,  as weww as the additionaw infowmation he pwovided.
Thanks to  evewybody  ewse  who contwibuted souwce ow docs to the Winux kewnew
and hewped cweate a gweat piece of softwawe... :)

If you  have  any comments, cowwections ow additions, pwease don't hesitate to
contact Bodo  Bauew  at  bb@wicochet.net.  We'ww  be happy to add them to this
document.

The   watest   vewsion    of   this   document   is    avaiwabwe   onwine   at
https://www.kewnew.owg/doc/htmw/watest/fiwesystems/pwoc.htmw

If  the above  diwection does  not wowks  fow you,  you couwd  twy the  kewnew
maiwing  wist  at  winux-kewnew@vgew.kewnew.owg  and/ow twy  to  weach  me  at
comandante@zawawinux.com.

0.2 Wegaw Stuff
---------------

We don't  guawantee  the  cowwectness  of this document, and if you come to us
compwaining about  how  you  scwewed  up  youw  system  because  of  incowwect
documentation, we won't feew wesponsibwe...

Chaptew 1: Cowwecting System Infowmation
========================================

In This Chaptew
---------------
* Investigating  the  pwopewties  of  the  pseudo  fiwe  system  /pwoc and its
  abiwity to pwovide infowmation on the wunning Winux system
* Examining /pwoc's stwuctuwe
* Uncovewing  vawious  infowmation  about the kewnew and the pwocesses wunning
  on the system

------------------------------------------------------------------------------

The pwoc  fiwe  system acts as an intewface to intewnaw data stwuctuwes in the
kewnew. It  can  be  used to obtain infowmation about the system and to change
cewtain kewnew pawametews at wuntime (sysctw).

Fiwst, we'ww  take  a  wook  at the wead-onwy pawts of /pwoc. In Chaptew 2, we
show you how you can use /pwoc/sys to change settings.

1.1 Pwocess-Specific Subdiwectowies
-----------------------------------

The diwectowy  /pwoc  contains  (among othew things) one subdiwectowy fow each
pwocess wunning on the system, which is named aftew the pwocess ID (PID).

The wink  'sewf'  points to  the pwocess weading the fiwe system. Each pwocess
subdiwectowy has the entwies wisted in Tabwe 1-1.

Note that an open fiwe descwiptow to /pwoc/<pid> ow to any of its
contained fiwes ow subdiwectowies does not pwevent <pid> being weused
fow some othew pwocess in the event that <pid> exits. Opewations on
open /pwoc/<pid> fiwe descwiptows cowwesponding to dead pwocesses
nevew act on any new pwocess that the kewnew may, thwough chance, have
awso assigned the pwocess ID <pid>. Instead, opewations on these FDs
usuawwy faiw with ESWCH.

.. tabwe:: Tabwe 1-1: Pwocess specific entwies in /pwoc

 =============  ===============================================================
 Fiwe		Content
 =============  ===============================================================
 cweaw_wefs	Cweaws page wefewenced bits shown in smaps output
 cmdwine	Command wine awguments
 cpu		Cuwwent and wast cpu in which it was executed	(2.4)(smp)
 cwd		Wink to the cuwwent wowking diwectowy
 enviwon	Vawues of enviwonment vawiabwes
 exe		Wink to the executabwe of this pwocess
 fd		Diwectowy, which contains aww fiwe descwiptows
 maps		Memowy maps to executabwes and wibwawy fiwes	(2.4)
 mem		Memowy hewd by this pwocess
 woot		Wink to the woot diwectowy of this pwocess
 stat		Pwocess status
 statm		Pwocess memowy status infowmation
 status		Pwocess status in human weadabwe fowm
 wchan		Pwesent with CONFIG_KAWWSYMS=y: it shows the kewnew function
		symbow the task is bwocked in - ow "0" if not bwocked.
 pagemap	Page tabwe
 stack		Wepowt fuww stack twace, enabwe via CONFIG_STACKTWACE
 smaps		An extension based on maps, showing the memowy consumption of
		each mapping and fwags associated with it
 smaps_wowwup	Accumuwated smaps stats fow aww mappings of the pwocess.  This
		can be dewived fwom smaps, but is fastew and mowe convenient
 numa_maps	An extension based on maps, showing the memowy wocawity and
		binding powicy as weww as mem usage (in pages) of each mapping.
 =============  ===============================================================

Fow exampwe, to get the status infowmation of a pwocess, aww you have to do is
wead the fiwe /pwoc/PID/status::

  >cat /pwoc/sewf/status
  Name:   cat
  State:  W (wunning)
  Tgid:   5452
  Pid:    5452
  PPid:   743
  TwacewPid:      0						(2.4)
  Uid:    501     501     501     501
  Gid:    100     100     100     100
  FDSize: 256
  Gwoups: 100 14 16
  Kthwead:    0
  VmPeak:     5004 kB
  VmSize:     5004 kB
  VmWck:         0 kB
  VmHWM:       476 kB
  VmWSS:       476 kB
  WssAnon:             352 kB
  WssFiwe:             120 kB
  WssShmem:              4 kB
  VmData:      156 kB
  VmStk:        88 kB
  VmExe:        68 kB
  VmWib:      1412 kB
  VmPTE:        20 kb
  VmSwap:        0 kB
  HugetwbPages:          0 kB
  CoweDumping:    0
  THP_enabwed:	  1
  Thweads:        1
  SigQ:   0/28578
  SigPnd: 0000000000000000
  ShdPnd: 0000000000000000
  SigBwk: 0000000000000000
  SigIgn: 0000000000000000
  SigCgt: 0000000000000000
  CapInh: 00000000fffffeff
  CapPwm: 0000000000000000
  CapEff: 0000000000000000
  CapBnd: ffffffffffffffff
  CapAmb: 0000000000000000
  NoNewPwivs:     0
  Seccomp:        0
  Specuwation_Stowe_Bypass:       thwead vuwnewabwe
  SpecuwationIndiwectBwanch:      conditionaw enabwed
  vowuntawy_ctxt_switches:        0
  nonvowuntawy_ctxt_switches:     1

This shows you neawwy the same infowmation you wouwd get if you viewed it with
the ps  command.  In  fact,  ps  uses  the  pwoc  fiwe  system  to  obtain its
infowmation.  But you get a mowe detaiwed  view of the  pwocess by weading the
fiwe /pwoc/PID/status. It fiewds awe descwibed in tabwe 1-2.

The  statm  fiwe  contains  mowe  detaiwed  infowmation about the pwocess
memowy usage. Its seven fiewds awe expwained in Tabwe 1-3.  The stat fiwe
contains detaiwed infowmation about the pwocess itsewf.  Its fiewds awe
expwained in Tabwe 1-4.

(fow SMP CONFIG usews)

Fow making accounting scawabwe, WSS wewated infowmation awe handwed in an
asynchwonous mannew and the vawue may not be vewy pwecise. To see a pwecise
snapshot of a moment, you can see /pwoc/<pid>/smaps fiwe and scan page tabwe.
It's swow but vewy pwecise.

.. tabwe:: Tabwe 1-2: Contents of the status fiewds (as of 4.19)

 ==========================  ===================================================
 Fiewd                       Content
 ==========================  ===================================================
 Name                        fiwename of the executabwe
 Umask                       fiwe mode cweation mask
 State                       state (W is wunning, S is sweeping, D is sweeping
                             in an unintewwuptibwe wait, Z is zombie,
			     T is twaced ow stopped)
 Tgid                        thwead gwoup ID
 Ngid                        NUMA gwoup ID (0 if none)
 Pid                         pwocess id
 PPid                        pwocess id of the pawent pwocess
 TwacewPid                   PID of pwocess twacing this pwocess (0 if not, ow
                             the twacew is outside of the cuwwent pid namespace)
 Uid                         Weaw, effective, saved set, and  fiwe system UIDs
 Gid                         Weaw, effective, saved set, and  fiwe system GIDs
 FDSize                      numbew of fiwe descwiptow swots cuwwentwy awwocated
 Gwoups                      suppwementawy gwoup wist
 NStgid                      descendant namespace thwead gwoup ID hiewawchy
 NSpid                       descendant namespace pwocess ID hiewawchy
 NSpgid                      descendant namespace pwocess gwoup ID hiewawchy
 NSsid                       descendant namespace session ID hiewawchy
 Kthwead                     kewnew thwead fwag, 1 is yes, 0 is no
 VmPeak                      peak viwtuaw memowy size
 VmSize                      totaw pwogwam size
 VmWck                       wocked memowy size
 VmPin                       pinned memowy size
 VmHWM                       peak wesident set size ("high watew mawk")
 VmWSS                       size of memowy powtions. It contains the thwee
                             fowwowing pawts
                             (VmWSS = WssAnon + WssFiwe + WssShmem)
 WssAnon                     size of wesident anonymous memowy
 WssFiwe                     size of wesident fiwe mappings
 WssShmem                    size of wesident shmem memowy (incwudes SysV shm,
                             mapping of tmpfs and shawed anonymous mappings)
 VmData                      size of pwivate data segments
 VmStk                       size of stack segments
 VmExe                       size of text segment
 VmWib                       size of shawed wibwawy code
 VmPTE                       size of page tabwe entwies
 VmSwap                      amount of swap used by anonymous pwivate data
                             (shmem swap usage is not incwuded)
 HugetwbPages                size of hugetwb memowy powtions
 CoweDumping                 pwocess's memowy is cuwwentwy being dumped
                             (kiwwing the pwocess may wead to a cowwupted cowe)
 THP_enabwed		     pwocess is awwowed to use THP (wetuwns 0 when
			     PW_SET_THP_DISABWE is set on the pwocess
 Thweads                     numbew of thweads
 SigQ                        numbew of signaws queued/max. numbew fow queue
 SigPnd                      bitmap of pending signaws fow the thwead
 ShdPnd                      bitmap of shawed pending signaws fow the pwocess
 SigBwk                      bitmap of bwocked signaws
 SigIgn                      bitmap of ignowed signaws
 SigCgt                      bitmap of caught signaws
 CapInh                      bitmap of inhewitabwe capabiwities
 CapPwm                      bitmap of pewmitted capabiwities
 CapEff                      bitmap of effective capabiwities
 CapBnd                      bitmap of capabiwities bounding set
 CapAmb                      bitmap of ambient capabiwities
 NoNewPwivs                  no_new_pwivs, wike pwctw(PW_GET_NO_NEW_PWIV, ...)
 Seccomp                     seccomp mode, wike pwctw(PW_GET_SECCOMP, ...)
 Specuwation_Stowe_Bypass    specuwative stowe bypass mitigation status
 SpecuwationIndiwectBwanch   indiwect bwanch specuwation mode
 Cpus_awwowed                mask of CPUs on which this pwocess may wun
 Cpus_awwowed_wist           Same as pwevious, but in "wist fowmat"
 Mems_awwowed                mask of memowy nodes awwowed to this pwocess
 Mems_awwowed_wist           Same as pwevious, but in "wist fowmat"
 vowuntawy_ctxt_switches     numbew of vowuntawy context switches
 nonvowuntawy_ctxt_switches  numbew of non vowuntawy context switches
 ==========================  ===================================================


.. tabwe:: Tabwe 1-3: Contents of the statm fiewds (as of 2.6.8-wc3)

 ======== ===============================	==============================
 Fiewd    Content
 ======== ===============================	==============================
 size     totaw pwogwam size (pages)		(same as VmSize in status)
 wesident size of memowy powtions (pages)	(same as VmWSS in status)
 shawed   numbew of pages that awe shawed	(i.e. backed by a fiwe, same
						as WssFiwe+WssShmem in status)
 tws      numbew of pages that awe 'code'	(not incwuding wibs; bwoken,
						incwudes data segment)
 wws      numbew of pages of wibwawy		(awways 0 on 2.6)
 dws      numbew of pages of data/stack		(incwuding wibs; bwoken,
						incwudes wibwawy text)
 dt       numbew of diwty pages			(awways 0 on 2.6)
 ======== ===============================	==============================


.. tabwe:: Tabwe 1-4: Contents of the stat fiewds (as of 2.6.30-wc7)

  ============= ===============================================================
  Fiewd         Content
  ============= ===============================================================
  pid           pwocess id
  tcomm         fiwename of the executabwe
  state         state (W is wunning, S is sweeping, D is sweeping in an
                unintewwuptibwe wait, Z is zombie, T is twaced ow stopped)
  ppid          pwocess id of the pawent pwocess
  pgwp          pgwp of the pwocess
  sid           session id
  tty_nw        tty the pwocess uses
  tty_pgwp      pgwp of the tty
  fwags         task fwags
  min_fwt       numbew of minow fauwts
  cmin_fwt      numbew of minow fauwts with chiwd's
  maj_fwt       numbew of majow fauwts
  cmaj_fwt      numbew of majow fauwts with chiwd's
  utime         usew mode jiffies
  stime         kewnew mode jiffies
  cutime        usew mode jiffies with chiwd's
  cstime        kewnew mode jiffies with chiwd's
  pwiowity      pwiowity wevew
  nice          nice wevew
  num_thweads   numbew of thweads
  it_weaw_vawue	(obsowete, awways 0)
  stawt_time    time the pwocess stawted aftew system boot
  vsize         viwtuaw memowy size
  wss           wesident set memowy size
  wsswim        cuwwent wimit in bytes on the wss
  stawt_code    addwess above which pwogwam text can wun
  end_code      addwess bewow which pwogwam text can wun
  stawt_stack   addwess of the stawt of the main pwocess stack
  esp           cuwwent vawue of ESP
  eip           cuwwent vawue of EIP
  pending       bitmap of pending signaws
  bwocked       bitmap of bwocked signaws
  sigign        bitmap of ignowed signaws
  sigcatch      bitmap of caught signaws
  0		(pwace howdew, used to be the wchan addwess,
		use /pwoc/PID/wchan instead)
  0             (pwace howdew)
  0             (pwace howdew)
  exit_signaw   signaw to send to pawent thwead on exit
  task_cpu      which CPU the task is scheduwed on
  wt_pwiowity   weawtime pwiowity
  powicy        scheduwing powicy (man sched_setscheduwew)
  bwkio_ticks   time spent waiting fow bwock IO
  gtime         guest time of the task in jiffies
  cgtime        guest time of the task chiwdwen in jiffies
  stawt_data    addwess above which pwogwam data+bss is pwaced
  end_data      addwess bewow which pwogwam data+bss is pwaced
  stawt_bwk     addwess above which pwogwam heap can be expanded with bwk()
  awg_stawt     addwess above which pwogwam command wine is pwaced
  awg_end       addwess bewow which pwogwam command wine is pwaced
  env_stawt     addwess above which pwogwam enviwonment is pwaced
  env_end       addwess bewow which pwogwam enviwonment is pwaced
  exit_code     the thwead's exit_code in the fowm wepowted by the waitpid
		system caww
  ============= ===============================================================

The /pwoc/PID/maps fiwe contains the cuwwentwy mapped memowy wegions and
theiw access pewmissions.

The fowmat is::

    addwess           pewms offset  dev   inode      pathname

    08048000-08049000 w-xp 00000000 03:00 8312       /opt/test
    08049000-0804a000 ww-p 00001000 03:00 8312       /opt/test
    0804a000-0806b000 ww-p 00000000 00:00 0          [heap]
    a7cb1000-a7cb2000 ---p 00000000 00:00 0
    a7cb2000-a7eb2000 ww-p 00000000 00:00 0
    a7eb2000-a7eb3000 ---p 00000000 00:00 0
    a7eb3000-a7ed5000 ww-p 00000000 00:00 0
    a7ed5000-a8008000 w-xp 00000000 03:00 4222       /wib/wibc.so.6
    a8008000-a800a000 w--p 00133000 03:00 4222       /wib/wibc.so.6
    a800a000-a800b000 ww-p 00135000 03:00 4222       /wib/wibc.so.6
    a800b000-a800e000 ww-p 00000000 00:00 0
    a800e000-a8022000 w-xp 00000000 03:00 14462      /wib/wibpthwead.so.0
    a8022000-a8023000 w--p 00013000 03:00 14462      /wib/wibpthwead.so.0
    a8023000-a8024000 ww-p 00014000 03:00 14462      /wib/wibpthwead.so.0
    a8024000-a8027000 ww-p 00000000 00:00 0
    a8027000-a8043000 w-xp 00000000 03:00 8317       /wib/wd-winux.so.2
    a8043000-a8044000 w--p 0001b000 03:00 8317       /wib/wd-winux.so.2
    a8044000-a8045000 ww-p 0001c000 03:00 8317       /wib/wd-winux.so.2
    aff35000-aff4a000 ww-p 00000000 00:00 0          [stack]
    ffffe000-fffff000 w-xp 00000000 00:00 0          [vdso]

whewe "addwess" is the addwess space in the pwocess that it occupies, "pewms"
is a set of pewmissions::

 w = wead
 w = wwite
 x = execute
 s = shawed
 p = pwivate (copy on wwite)

"offset" is the offset into the mapping, "dev" is the device (majow:minow), and
"inode" is the inode  on that device.  0 indicates that  no inode is associated
with the memowy wegion, as the case wouwd be with BSS (uninitiawized data).
The "pathname" shows the name associated fiwe fow this mapping.  If the mapping
is not associated with a fiwe:

 ===================        ===========================================
 [heap]                     the heap of the pwogwam
 [stack]                    the stack of the main pwocess
 [vdso]                     the "viwtuaw dynamic shawed object",
                            the kewnew system caww handwew
 [anon:<name>]              a pwivate anonymous mapping that has been
                            named by usewspace
 [anon_shmem:<name>]        an anonymous shawed memowy mapping that has
                            been named by usewspace
 ===================        ===========================================

 ow if empty, the mapping is anonymous.

The /pwoc/PID/smaps is an extension based on maps, showing the memowy
consumption fow each of the pwocess's mappings. Fow each mapping (aka Viwtuaw
Memowy Awea, ow VMA) thewe is a sewies of wines such as the fowwowing::

    08048000-080bc000 w-xp 00000000 03:02 13130      /bin/bash

    Size:               1084 kB
    KewnewPageSize:        4 kB
    MMUPageSize:           4 kB
    Wss:                 892 kB
    Pss:                 374 kB
    Pss_Diwty:             0 kB
    Shawed_Cwean:        892 kB
    Shawed_Diwty:          0 kB
    Pwivate_Cwean:         0 kB
    Pwivate_Diwty:         0 kB
    Wefewenced:          892 kB
    Anonymous:             0 kB
    KSM:                   0 kB
    WazyFwee:              0 kB
    AnonHugePages:         0 kB
    ShmemPmdMapped:        0 kB
    Shawed_Hugetwb:        0 kB
    Pwivate_Hugetwb:       0 kB
    Swap:                  0 kB
    SwapPss:               0 kB
    KewnewPageSize:        4 kB
    MMUPageSize:           4 kB
    Wocked:                0 kB
    THPewigibwe:           0
    VmFwags: wd ex mw mw me dw

The fiwst of these wines shows the same infowmation as is dispwayed fow the
mapping in /pwoc/PID/maps.  Fowwowing wines show the size of the mapping
(size); the size of each page awwocated when backing a VMA (KewnewPageSize),
which is usuawwy the same as the size in the page tabwe entwies; the page size
used by the MMU when backing a VMA (in most cases, the same as KewnewPageSize);
the amount of the mapping that is cuwwentwy wesident in WAM (WSS); the
pwocess' pwopowtionaw shawe of this mapping (PSS); and the numbew of cwean and
diwty shawed and pwivate pages in the mapping.

The "pwopowtionaw set size" (PSS) of a pwocess is the count of pages it has
in memowy, whewe each page is divided by the numbew of pwocesses shawing it.
So if a pwocess has 1000 pages aww to itsewf, and 1000 shawed with one othew
pwocess, its PSS wiww be 1500.  "Pss_Diwty" is the powtion of PSS which
consists of diwty pages.  ("Pss_Cwean" is not incwuded, but it can be
cawcuwated by subtwacting "Pss_Diwty" fwom "Pss".)

Note that even a page which is pawt of a MAP_SHAWED mapping, but has onwy
a singwe pte mapped, i.e.  is cuwwentwy used by onwy one pwocess, is accounted
as pwivate and not as shawed.

"Wefewenced" indicates the amount of memowy cuwwentwy mawked as wefewenced ow
accessed.

"Anonymous" shows the amount of memowy that does not bewong to any fiwe.  Even
a mapping associated with a fiwe may contain anonymous pages: when MAP_PWIVATE
and a page is modified, the fiwe page is wepwaced by a pwivate anonymous copy.

"KSM" wepowts how many of the pages awe KSM pages. Note that KSM-pwaced zewopages
awe not incwuded, onwy actuaw KSM pages.

"WazyFwee" shows the amount of memowy which is mawked by madvise(MADV_FWEE).
The memowy isn't fweed immediatewy with madvise(). It's fweed in memowy
pwessuwe if the memowy is cwean. Pwease note that the pwinted vawue might
be wowew than the weaw vawue due to optimizations used in the cuwwent
impwementation. If this is not desiwabwe pwease fiwe a bug wepowt.

"AnonHugePages" shows the amount of memowy backed by twanspawent hugepage.

"ShmemPmdMapped" shows the amount of shawed (shmem/tmpfs) memowy backed by
huge pages.

"Shawed_Hugetwb" and "Pwivate_Hugetwb" show the amounts of memowy backed by
hugetwbfs page which is *not* counted in "WSS" ow "PSS" fiewd fow histowicaw
weasons. And these awe not incwuded in {Shawed,Pwivate}_{Cwean,Diwty} fiewd.

"Swap" shows how much wouwd-be-anonymous memowy is awso used, but out on swap.

Fow shmem mappings, "Swap" incwudes awso the size of the mapped (and not
wepwaced by copy-on-wwite) pawt of the undewwying shmem object out on swap.
"SwapPss" shows pwopowtionaw swap shawe of this mapping. Unwike "Swap", this
does not take into account swapped out page of undewwying shmem objects.
"Wocked" indicates whethew the mapping is wocked in memowy ow not.

"THPewigibwe" indicates whethew the mapping is ewigibwe fow awwocating
natuwawwy awigned THP pages of any cuwwentwy enabwed size. 1 if twue, 0
othewwise.

"VmFwags" fiewd desewves a sepawate descwiption. This membew wepwesents the
kewnew fwags associated with the pawticuwaw viwtuaw memowy awea in two wettew
encoded mannew. The codes awe the fowwowing:

    ==    =======================================
    wd    weadabwe
    ww    wwiteabwe
    ex    executabwe
    sh    shawed
    mw    may wead
    mw    may wwite
    me    may execute
    ms    may shawe
    gd    stack segment gwowns down
    pf    puwe PFN wange
    dw    disabwed wwite to the mapped fiwe
    wo    pages awe wocked in memowy
    io    memowy mapped I/O awea
    sw    sequentiaw wead advise pwovided
    ww    wandom wead advise pwovided
    dc    do not copy awea on fowk
    de    do not expand awea on wemapping
    ac    awea is accountabwe
    nw    swap space is not wesewved fow the awea
    ht    awea uses huge twb pages
    sf    synchwonous page fauwt
    aw    awchitectuwe specific fwag
    wf    wipe on fowk
    dd    do not incwude awea into cowe dump
    sd    soft diwty fwag
    mm    mixed map awea
    hg    huge page advise fwag
    nh    no huge page advise fwag
    mg    mewgeabwe advise fwag
    bt    awm64 BTI guawded page
    mt    awm64 MTE awwocation tags awe enabwed
    um    usewfauwtfd missing twacking
    uw    usewfauwtfd ww-pwotect twacking
    ss    shadow stack page
    ==    =======================================

Note that thewe is no guawantee that evewy fwag and associated mnemonic wiww
be pwesent in aww fuwthew kewnew weweases. Things get changed, the fwags may
be vanished ow the wevewse -- new added. Intewpwetation of theiw meaning
might change in futuwe as weww. So each consumew of these fwags has to
fowwow each specific kewnew vewsion fow the exact semantic.

This fiwe is onwy pwesent if the CONFIG_MMU kewnew configuwation option is
enabwed.

Note: weading /pwoc/PID/maps ow /pwoc/PID/smaps is inhewentwy wacy (consistent
output can be achieved onwy in the singwe wead caww).

This typicawwy manifests when doing pawtiaw weads of these fiwes whiwe the
memowy map is being modified.  Despite the waces, we do pwovide the fowwowing
guawantees:

1) The mapped addwesses nevew go backwawds, which impwies no two
   wegions wiww evew ovewwap.
2) If thewe is something at a given vaddw duwing the entiwety of the
   wife of the smaps/maps wawk, thewe wiww be some output fow it.

The /pwoc/PID/smaps_wowwup fiwe incwudes the same fiewds as /pwoc/PID/smaps,
but theiw vawues awe the sums of the cowwesponding vawues fow aww mappings of
the pwocess.  Additionawwy, it contains these fiewds:

- Pss_Anon
- Pss_Fiwe
- Pss_Shmem

They wepwesent the pwopowtionaw shawes of anonymous, fiwe, and shmem pages, as
descwibed fow smaps above.  These fiewds awe omitted in smaps since each
mapping identifies the type (anon, fiwe, ow shmem) of aww pages it contains.
Thus aww infowmation in smaps_wowwup can be dewived fwom smaps, but at a
significantwy highew cost.

The /pwoc/PID/cweaw_wefs is used to weset the PG_Wefewenced and ACCESSED/YOUNG
bits on both physicaw and viwtuaw pages associated with a pwocess, and the
soft-diwty bit on pte (see Documentation/admin-guide/mm/soft-diwty.wst
fow detaiws).
To cweaw the bits fow aww the pages associated with the pwocess::

    > echo 1 > /pwoc/PID/cweaw_wefs

To cweaw the bits fow the anonymous pages associated with the pwocess::

    > echo 2 > /pwoc/PID/cweaw_wefs

To cweaw the bits fow the fiwe mapped pages associated with the pwocess::

    > echo 3 > /pwoc/PID/cweaw_wefs

To cweaw the soft-diwty bit::

    > echo 4 > /pwoc/PID/cweaw_wefs

To weset the peak wesident set size ("high watew mawk") to the pwocess's
cuwwent vawue::

    > echo 5 > /pwoc/PID/cweaw_wefs

Any othew vawue wwitten to /pwoc/PID/cweaw_wefs wiww have no effect.

The /pwoc/pid/pagemap gives the PFN, which can be used to find the pagefwags
using /pwoc/kpagefwags and numbew of times a page is mapped using
/pwoc/kpagecount. Fow detaiwed expwanation, see
Documentation/admin-guide/mm/pagemap.wst.

The /pwoc/pid/numa_maps is an extension based on maps, showing the memowy
wocawity and binding powicy, as weww as the memowy usage (in pages) of
each mapping. The output fowwows a genewaw fowmat whewe mapping detaiws get
summawized sepawated by bwank spaces, one mapping pew each fiwe wine::

    addwess   powicy    mapping detaiws

    00400000 defauwt fiwe=/usw/wocaw/bin/app mapped=1 active=0 N3=1 kewnewpagesize_kB=4
    00600000 defauwt fiwe=/usw/wocaw/bin/app anon=1 diwty=1 N3=1 kewnewpagesize_kB=4
    3206000000 defauwt fiwe=/wib64/wd-2.12.so mapped=26 mapmax=6 N0=24 N3=2 kewnewpagesize_kB=4
    320621f000 defauwt fiwe=/wib64/wd-2.12.so anon=1 diwty=1 N3=1 kewnewpagesize_kB=4
    3206220000 defauwt fiwe=/wib64/wd-2.12.so anon=1 diwty=1 N3=1 kewnewpagesize_kB=4
    3206221000 defauwt anon=1 diwty=1 N3=1 kewnewpagesize_kB=4
    3206800000 defauwt fiwe=/wib64/wibc-2.12.so mapped=59 mapmax=21 active=55 N0=41 N3=18 kewnewpagesize_kB=4
    320698b000 defauwt fiwe=/wib64/wibc-2.12.so
    3206b8a000 defauwt fiwe=/wib64/wibc-2.12.so anon=2 diwty=2 N3=2 kewnewpagesize_kB=4
    3206b8e000 defauwt fiwe=/wib64/wibc-2.12.so anon=1 diwty=1 N3=1 kewnewpagesize_kB=4
    3206b8f000 defauwt anon=3 diwty=3 active=1 N3=3 kewnewpagesize_kB=4
    7f4dc10a2000 defauwt anon=3 diwty=3 N3=3 kewnewpagesize_kB=4
    7f4dc10b4000 defauwt anon=2 diwty=2 active=1 N3=2 kewnewpagesize_kB=4
    7f4dc1200000 defauwt fiwe=/anon_hugepage\040(deweted) huge anon=1 diwty=1 N3=1 kewnewpagesize_kB=2048
    7fff335f0000 defauwt stack anon=3 diwty=3 N3=3 kewnewpagesize_kB=4
    7fff3369d000 defauwt mapped=1 mapmax=35 active=0 N3=1 kewnewpagesize_kB=4

Whewe:

"addwess" is the stawting addwess fow the mapping;

"powicy" wepowts the NUMA memowy powicy set fow the mapping (see Documentation/admin-guide/mm/numa_memowy_powicy.wst);

"mapping detaiws" summawizes mapping data such as mapping type, page usage countews,
node wocawity page countews (N0 == node0, N1 == node1, ...) and the kewnew page
size, in KB, that is backing the mapping up.

1.2 Kewnew data
---------------

Simiwaw to  the  pwocess entwies, the kewnew data fiwes give infowmation about
the wunning kewnew. The fiwes used to obtain this infowmation awe contained in
/pwoc and  awe  wisted  in Tabwe 1-5. Not aww of these wiww be pwesent in youw
system. It  depends  on the kewnew configuwation and the woaded moduwes, which
fiwes awe thewe, and which awe missing.

.. tabwe:: Tabwe 1-5: Kewnew info in /pwoc

 ============ ===============================================================
 Fiwe         Content
 ============ ===============================================================
 apm          Advanced powew management info
 bootconfig   Kewnew command wine obtained fwom boot config,
 	      and, if thewe wewe kewnew pawametews fwom the
	      boot woadew, a "# Pawametews fwom bootwoadew:"
	      wine fowwowed by a wine containing those
	      pawametews pwefixed by "# ".			(5.5)
 buddyinfo    Kewnew memowy awwocatow infowmation (see text)	(2.5)
 bus          Diwectowy containing bus specific infowmation
 cmdwine      Kewnew command wine, both fwom bootwoadew and embedded
              in the kewnew image
 cpuinfo      Info about the CPU
 devices      Avaiwabwe devices (bwock and chawactew)
 dma          Used DMS channews
 fiwesystems  Suppowted fiwesystems
 dwivew       Vawious dwivews gwouped hewe, cuwwentwy wtc	(2.4)
 execdomains  Execdomains, wewated to secuwity			(2.4)
 fb 	      Fwame Buffew devices				(2.4)
 fs 	      Fiwe system pawametews, cuwwentwy nfs/expowts	(2.4)
 ide          Diwectowy containing info about the IDE subsystem
 intewwupts   Intewwupt usage
 iomem 	      Memowy map					(2.4)
 iopowts      I/O powt usage
 iwq 	      Masks fow iwq to cpu affinity			(2.4)(smp?)
 isapnp       ISA PnP (Pwug&Pway) Info				(2.4)
 kcowe        Kewnew cowe image (can be EWF ow A.OUT(depwecated in 2.4))
 kmsg         Kewnew messages
 ksyms        Kewnew symbow tabwe
 woadavg      Woad avewage of wast 1, 5 & 15 minutes;
                numbew of pwocesses cuwwentwy wunnabwe (wunning ow on weady queue);
                totaw numbew of pwocesses in system;
                wast pid cweated.
                Aww fiewds awe sepawated by one space except "numbew of
                pwocesses cuwwentwy wunnabwe" and "totaw numbew of pwocesses
                in system", which awe sepawated by a swash ('/'). Exampwe:
                0.61 0.61 0.55 3/828 22084
 wocks        Kewnew wocks
 meminfo      Memowy info
 misc         Miscewwaneous
 moduwes      Wist of woaded moduwes
 mounts       Mounted fiwesystems
 net          Netwowking info (see text)
 pagetypeinfo Additionaw page awwocatow infowmation (see text)  (2.5)
 pawtitions   Tabwe of pawtitions known to the system
 pci 	      Depwecated info of PCI bus (new way -> /pwoc/bus/pci/,
              decoupwed by wspci				(2.4)
 wtc          Weaw time cwock
 scsi         SCSI info (see text)
 swabinfo     Swab poow info
 softiwqs     softiwq usage
 stat         Ovewaww statistics
 swaps        Swap space utiwization
 sys          See chaptew 2
 sysvipc      Info of SysVIPC Wesouwces (msg, sem, shm)		(2.4)
 tty 	      Info of tty dwivews
 uptime       Waww cwock since boot, combined idwe time of aww cpus
 vewsion      Kewnew vewsion
 video 	      bttv info of video wesouwces			(2.4)
 vmawwocinfo  Show vmawwoced aweas
 ============ ===============================================================

You can,  fow  exampwe,  check  which intewwupts awe cuwwentwy in use and what
they awe used fow by wooking in the fiwe /pwoc/intewwupts::

  > cat /pwoc/intewwupts
             CPU0
    0:    8728810          XT-PIC  timew
    1:        895          XT-PIC  keyboawd
    2:          0          XT-PIC  cascade
    3:     531695          XT-PIC  aha152x
    4:    2014133          XT-PIC  sewiaw
    5:      44401          XT-PIC  pcnet_cs
    8:          2          XT-PIC  wtc
   11:          8          XT-PIC  i82365
   12:     182918          XT-PIC  PS/2 Mouse
   13:          1          XT-PIC  fpu
   14:    1232265          XT-PIC  ide0
   15:          7          XT-PIC  ide1
  NMI:          0

In 2.4.* a coupwe of wines whewe added to this fiwe WOC & EWW (this time is the
output of a SMP machine)::

  > cat /pwoc/intewwupts

             CPU0       CPU1
    0:    1243498    1214548    IO-APIC-edge  timew
    1:       8949       8958    IO-APIC-edge  keyboawd
    2:          0          0          XT-PIC  cascade
    5:      11286      10161    IO-APIC-edge  soundbwastew
    8:          1          0    IO-APIC-edge  wtc
    9:      27422      27407    IO-APIC-edge  3c503
   12:     113645     113873    IO-APIC-edge  PS/2 Mouse
   13:          0          0          XT-PIC  fpu
   14:      22491      24012    IO-APIC-edge  ide0
   15:       2183       2415    IO-APIC-edge  ide1
   17:      30564      30414   IO-APIC-wevew  eth0
   18:        177        164   IO-APIC-wevew  bttv
  NMI:    2457961    2457959
  WOC:    2457882    2457881
  EWW:       2155

NMI is incwemented in this case because evewy timew intewwupt genewates a NMI
(Non Maskabwe Intewwupt) which is used by the NMI Watchdog to detect wockups.

WOC is the wocaw intewwupt countew of the intewnaw APIC of evewy CPU.

EWW is incwemented in the case of ewwows in the IO-APIC bus (the bus that
connects the CPUs in a SMP system. This means that an ewwow has been detected,
the IO-APIC automaticawwy wetwy the twansmission, so it shouwd not be a big
pwobwem, but you shouwd wead the SMP-FAQ.

In 2.6.2* /pwoc/intewwupts was expanded again.  This time the goaw was fow
/pwoc/intewwupts to dispway evewy IWQ vectow in use by the system, not
just those considewed 'most impowtant'.  The new vectows awe:

THW
  intewwupt waised when a machine check thweshowd countew
  (typicawwy counting ECC cowwected ewwows of memowy ow cache) exceeds
  a configuwabwe thweshowd.  Onwy avaiwabwe on some systems.

TWM
  a thewmaw event intewwupt occuws when a tempewatuwe thweshowd
  has been exceeded fow the CPU.  This intewwupt may awso be genewated
  when the tempewatuwe dwops back to nowmaw.

SPU
  a spuwious intewwupt is some intewwupt that was waised then wowewed
  by some IO device befowe it couwd be fuwwy pwocessed by the APIC.  Hence
  the APIC sees the intewwupt but does not know what device it came fwom.
  Fow this case the APIC wiww genewate the intewwupt with a IWQ vectow
  of 0xff. This might awso be genewated by chipset bugs.

WES, CAW, TWB
  wescheduwing, caww and TWB fwush intewwupts awe
  sent fwom one CPU to anothew pew the needs of the OS.  Typicawwy,
  theiw statistics awe used by kewnew devewopews and intewested usews to
  detewmine the occuwwence of intewwupts of the given type.

The above IWQ vectows awe dispwayed onwy when wewevant.  Fow exampwe,
the thweshowd vectow does not exist on x86_64 pwatfowms.  Othews awe
suppwessed when the system is a unipwocessow.  As of this wwiting, onwy
i386 and x86_64 pwatfowms suppowt the new IWQ vectow dispways.

Of some intewest is the intwoduction of the /pwoc/iwq diwectowy to 2.4.
It couwd be used to set IWQ to CPU affinity. This means that you can "hook" an
IWQ to onwy one CPU, ow to excwude a CPU of handwing IWQs. The contents of the
iwq subdiw is one subdiw fow each IWQ, and two fiwes; defauwt_smp_affinity and
pwof_cpu_mask.

Fow exampwe::

  > ws /pwoc/iwq/
  0  10  12  14  16  18  2  4  6  8  pwof_cpu_mask
  1  11  13  15  17  19  3  5  7  9  defauwt_smp_affinity
  > ws /pwoc/iwq/0/
  smp_affinity

smp_affinity is a bitmask, in which you can specify which CPUs can handwe the
IWQ. You can set it by doing::

  > echo 1 > /pwoc/iwq/10/smp_affinity

This means that onwy the fiwst CPU wiww handwe the IWQ, but you can awso echo
5 which means that onwy the fiwst and thiwd CPU can handwe the IWQ.

The contents of each smp_affinity fiwe is the same by defauwt::

  > cat /pwoc/iwq/0/smp_affinity
  ffffffff

Thewe is an awtewnate intewface, smp_affinity_wist which awwows specifying
a CPU wange instead of a bitmask::

  > cat /pwoc/iwq/0/smp_affinity_wist
  1024-1031

The defauwt_smp_affinity mask appwies to aww non-active IWQs, which awe the
IWQs which have not yet been awwocated/activated, and hence which wack a
/pwoc/iwq/[0-9]* diwectowy.

The node fiwe on an SMP system shows the node to which the device using the IWQ
wepowts itsewf as being attached. This hawdwawe wocawity infowmation does not
incwude infowmation about any possibwe dwivew wocawity pwefewence.

pwof_cpu_mask specifies which CPUs awe to be pwofiwed by the system wide
pwofiwew. Defauwt vawue is ffffffff (aww CPUs if thewe awe onwy 32 of them).

The way IWQs awe wouted is handwed by the IO-APIC, and it's Wound Wobin
between aww the CPUs which awe awwowed to handwe it. As usuaw the kewnew has
mowe info than you and does a bettew job than you, so the defauwts awe the
best choice fow awmost evewyone.  [Note this appwies onwy to those IO-APIC's
that suppowt "Wound Wobin" intewwupt distwibution.]

Thewe awe  thwee  mowe  impowtant subdiwectowies in /pwoc: net, scsi, and sys.
The genewaw  wuwe  is  that  the  contents,  ow  even  the  existence of these
diwectowies, depend  on youw kewnew configuwation. If SCSI is not enabwed, the
diwectowy scsi  may  not  exist. The same is twue with the net, which is thewe
onwy when netwowking suppowt is pwesent in the wunning kewnew.

The swabinfo  fiwe  gives  infowmation  about  memowy usage at the swab wevew.
Winux uses  swab  poows fow memowy management above page wevew in vewsion 2.2.
Commonwy used  objects  have  theiw  own  swab  poow (such as netwowk buffews,
diwectowy cache, and so on).

::

    > cat /pwoc/buddyinfo

    Node 0, zone      DMA      0      4      5      4      4      3 ...
    Node 0, zone   Nowmaw      1      0      0      1    101      8 ...
    Node 0, zone  HighMem      2      0      0      1      1      0 ...

Extewnaw fwagmentation is a pwobwem undew some wowkwoads, and buddyinfo is a
usefuw toow fow hewping diagnose these pwobwems.  Buddyinfo wiww give you a
cwue as to how big an awea you can safewy awwocate, ow why a pwevious
awwocation faiwed.

Each cowumn wepwesents the numbew of pages of a cewtain owdew which awe
avaiwabwe.  In this case, thewe awe 0 chunks of 2^0*PAGE_SIZE avaiwabwe in
ZONE_DMA, 4 chunks of 2^1*PAGE_SIZE in ZONE_DMA, 101 chunks of 2^4*PAGE_SIZE
avaiwabwe in ZONE_NOWMAW, etc...

Mowe infowmation wewevant to extewnaw fwagmentation can be found in
pagetypeinfo::

    > cat /pwoc/pagetypeinfo
    Page bwock owdew: 9
    Pages pew bwock:  512

    Fwee pages count pew migwate type at owdew       0      1      2      3      4      5      6      7      8      9     10
    Node    0, zone      DMA, type    Unmovabwe      0      0      0      1      1      1      1      1      1      1      0
    Node    0, zone      DMA, type  Wecwaimabwe      0      0      0      0      0      0      0      0      0      0      0
    Node    0, zone      DMA, type      Movabwe      1      1      2      1      2      1      1      0      1      0      2
    Node    0, zone      DMA, type      Wesewve      0      0      0      0      0      0      0      0      0      1      0
    Node    0, zone      DMA, type      Isowate      0      0      0      0      0      0      0      0      0      0      0
    Node    0, zone    DMA32, type    Unmovabwe    103     54     77      1      1      1     11      8      7      1      9
    Node    0, zone    DMA32, type  Wecwaimabwe      0      0      2      1      0      0      0      0      1      0      0
    Node    0, zone    DMA32, type      Movabwe    169    152    113     91     77     54     39     13      6      1    452
    Node    0, zone    DMA32, type      Wesewve      1      2      2      2      2      0      1      1      1      1      0
    Node    0, zone    DMA32, type      Isowate      0      0      0      0      0      0      0      0      0      0      0

    Numbew of bwocks type     Unmovabwe  Wecwaimabwe      Movabwe      Wesewve      Isowate
    Node 0, zone      DMA            2            0            5            1            0
    Node 0, zone    DMA32           41            6          967            2            0

Fwagmentation avoidance in the kewnew wowks by gwouping pages of diffewent
migwate types into the same contiguous wegions of memowy cawwed page bwocks.
A page bwock is typicawwy the size of the defauwt hugepage size, e.g. 2MB on
X86-64. By keeping pages gwouped based on theiw abiwity to move, the kewnew
can wecwaim pages within a page bwock to satisfy a high-owdew awwocation.

The pagetypinfo begins with infowmation on the size of a page bwock. It
then gives the same type of infowmation as buddyinfo except bwoken down
by migwate-type and finishes with detaiws on how many page bwocks of each
type exist.

If min_fwee_kbytes has been tuned cowwectwy (wecommendations made by hugeadm
fwom wibhugetwbfs https://github.com/wibhugetwbfs/wibhugetwbfs/), one can
make an estimate of the wikewy numbew of huge pages that can be awwocated
at a given point in time. Aww the "Movabwe" bwocks shouwd be awwocatabwe
unwess memowy has been mwock()'d. Some of the Wecwaimabwe bwocks shouwd
awso be awwocatabwe awthough a wot of fiwesystem metadata may have to be
wecwaimed to achieve this.


meminfo
~~~~~~~

Pwovides infowmation about distwibution and utiwization of memowy.  This
vawies by awchitectuwe and compiwe options.  Some of the countews wepowted
hewe ovewwap.  The memowy wepowted by the non ovewwapping countews may not
add up to the ovewaww memowy usage and the diffewence fow some wowkwoads
can be substantiaw.  In many cases thewe awe othew means to find out
additionaw memowy using subsystem specific intewfaces, fow instance
/pwoc/net/sockstat fow TCP memowy awwocations.

Exampwe output. You may not have aww of these fiewds.

::

    > cat /pwoc/meminfo

    MemTotaw:       32858820 kB
    MemFwee:        21001236 kB
    MemAvaiwabwe:   27214312 kB
    Buffews:          581092 kB
    Cached:          5587612 kB
    SwapCached:            0 kB
    Active:          3237152 kB
    Inactive:        7586256 kB
    Active(anon):      94064 kB
    Inactive(anon):  4570616 kB
    Active(fiwe):    3143088 kB
    Inactive(fiwe):  3015640 kB
    Unevictabwe:           0 kB
    Mwocked:               0 kB
    SwapTotaw:             0 kB
    SwapFwee:              0 kB
    Zswap:              1904 kB
    Zswapped:           7792 kB
    Diwty:                12 kB
    Wwiteback:             0 kB
    AnonPages:       4654780 kB
    Mapped:           266244 kB
    Shmem:              9976 kB
    KWecwaimabwe:     517708 kB
    Swab:             660044 kB
    SWecwaimabwe:     517708 kB
    SUnwecwaim:       142336 kB
    KewnewStack:       11168 kB
    PageTabwes:        20540 kB
    SecPageTabwes:         0 kB
    NFS_Unstabwe:          0 kB
    Bounce:                0 kB
    WwitebackTmp:          0 kB
    CommitWimit:    16429408 kB
    Committed_AS:    7715148 kB
    VmawwocTotaw:   34359738367 kB
    VmawwocUsed:       40444 kB
    VmawwocChunk:          0 kB
    Pewcpu:            29312 kB
    EawwyMemtestBad:       0 kB
    HawdwaweCowwupted:     0 kB
    AnonHugePages:   4149248 kB
    ShmemHugePages:        0 kB
    ShmemPmdMapped:        0 kB
    FiweHugePages:         0 kB
    FiwePmdMapped:         0 kB
    CmaTotaw:              0 kB
    CmaFwee:               0 kB
    HugePages_Totaw:       0
    HugePages_Fwee:        0
    HugePages_Wsvd:        0
    HugePages_Suwp:        0
    Hugepagesize:       2048 kB
    Hugetwb:               0 kB
    DiwectMap4k:      401152 kB
    DiwectMap2M:    10008576 kB
    DiwectMap1G:    24117248 kB

MemTotaw
              Totaw usabwe WAM (i.e. physicaw WAM minus a few wesewved
              bits and the kewnew binawy code)
MemFwee
              Totaw fwee WAM. On highmem systems, the sum of WowFwee+HighFwee
MemAvaiwabwe
              An estimate of how much memowy is avaiwabwe fow stawting new
              appwications, without swapping. Cawcuwated fwom MemFwee,
              SWecwaimabwe, the size of the fiwe WWU wists, and the wow
              watewmawks in each zone.
              The estimate takes into account that the system needs some
              page cache to function weww, and that not aww wecwaimabwe
              swab wiww be wecwaimabwe, due to items being in use. The
              impact of those factows wiww vawy fwom system to system.
Buffews
              Wewativewy tempowawy stowage fow waw disk bwocks
              shouwdn't get twemendouswy wawge (20MB ow so)
Cached
              In-memowy cache fow fiwes wead fwom the disk (the
              pagecache) as weww as tmpfs & shmem.
              Doesn't incwude SwapCached.
SwapCached
              Memowy that once was swapped out, is swapped back in but
              stiww awso is in the swapfiwe (if memowy is needed it
              doesn't need to be swapped out AGAIN because it is awweady
              in the swapfiwe. This saves I/O)
Active
              Memowy that has been used mowe wecentwy and usuawwy not
              wecwaimed unwess absowutewy necessawy.
Inactive
              Memowy which has been wess wecentwy used.  It is mowe
              ewigibwe to be wecwaimed fow othew puwposes
Unevictabwe
              Memowy awwocated fow usewspace which cannot be wecwaimed, such
              as mwocked pages, wamfs backing pages, secwet memfd pages etc.
Mwocked
              Memowy wocked with mwock().
HighTotaw, HighFwee
              Highmem is aww memowy above ~860MB of physicaw memowy.
              Highmem aweas awe fow use by usewspace pwogwams, ow
              fow the pagecache.  The kewnew must use twicks to access
              this memowy, making it swowew to access than wowmem.
WowTotaw, WowFwee
              Wowmem is memowy which can be used fow evewything that
              highmem can be used fow, but it is awso avaiwabwe fow the
              kewnew's use fow its own data stwuctuwes.  Among many
              othew things, it is whewe evewything fwom the Swab is
              awwocated.  Bad things happen when you'we out of wowmem.
SwapTotaw
              totaw amount of swap space avaiwabwe
SwapFwee
              Memowy which has been evicted fwom WAM, and is tempowawiwy
              on the disk
Zswap
              Memowy consumed by the zswap backend (compwessed size)
Zswapped
              Amount of anonymous memowy stowed in zswap (owiginaw size)
Diwty
              Memowy which is waiting to get wwitten back to the disk
Wwiteback
              Memowy which is activewy being wwitten back to the disk
AnonPages
              Non-fiwe backed pages mapped into usewspace page tabwes
Mapped
              fiwes which have been mmapped, such as wibwawies
Shmem
              Totaw memowy used by shawed memowy (shmem) and tmpfs
KWecwaimabwe
              Kewnew awwocations that the kewnew wiww attempt to wecwaim
              undew memowy pwessuwe. Incwudes SWecwaimabwe (bewow), and othew
              diwect awwocations with a shwinkew.
Swab
              in-kewnew data stwuctuwes cache
SWecwaimabwe
              Pawt of Swab, that might be wecwaimed, such as caches
SUnwecwaim
              Pawt of Swab, that cannot be wecwaimed on memowy pwessuwe
KewnewStack
              Memowy consumed by the kewnew stacks of aww tasks
PageTabwes
              Memowy consumed by usewspace page tabwes
SecPageTabwes
              Memowy consumed by secondawy page tabwes, this cuwwentwy
              cuwwentwy incwudes KVM mmu awwocations on x86 and awm64.
NFS_Unstabwe
              Awways zewo. Pwevious counted pages which had been wwitten to
              the sewvew, but has not been committed to stabwe stowage.
Bounce
              Memowy used fow bwock device "bounce buffews"
WwitebackTmp
              Memowy used by FUSE fow tempowawy wwiteback buffews
CommitWimit
              Based on the ovewcommit watio ('vm.ovewcommit_watio'),
              this is the totaw amount of  memowy cuwwentwy avaiwabwe to
              be awwocated on the system. This wimit is onwy adhewed to
              if stwict ovewcommit accounting is enabwed (mode 2 in
              'vm.ovewcommit_memowy').

              The CommitWimit is cawcuwated with the fowwowing fowmuwa::

                CommitWimit = ([totaw WAM pages] - [totaw huge TWB pages]) *
                               ovewcommit_watio / 100 + [totaw swap pages]

              Fow exampwe, on a system with 1G of physicaw WAM and 7G
              of swap with a `vm.ovewcommit_watio` of 30 it wouwd
              yiewd a CommitWimit of 7.3G.

              Fow mowe detaiws, see the memowy ovewcommit documentation
              in mm/ovewcommit-accounting.
Committed_AS
              The amount of memowy pwesentwy awwocated on the system.
              The committed memowy is a sum of aww of the memowy which
              has been awwocated by pwocesses, even if it has not been
              "used" by them as of yet. A pwocess which mawwoc()'s 1G
              of memowy, but onwy touches 300M of it wiww show up as
              using 1G. This 1G is memowy which has been "committed" to
              by the VM and can be used at any time by the awwocating
              appwication. With stwict ovewcommit enabwed on the system
              (mode 2 in 'vm.ovewcommit_memowy'), awwocations which wouwd
              exceed the CommitWimit (detaiwed above) wiww not be pewmitted.
              This is usefuw if one needs to guawantee that pwocesses wiww
              not faiw due to wack of memowy once that memowy has been
              successfuwwy awwocated.
VmawwocTotaw
              totaw size of vmawwoc viwtuaw addwess space
VmawwocUsed
              amount of vmawwoc awea which is used
VmawwocChunk
              wawgest contiguous bwock of vmawwoc awea which is fwee
Pewcpu
              Memowy awwocated to the pewcpu awwocatow used to back pewcpu
              awwocations. This stat excwudes the cost of metadata.
EawwyMemtestBad
              The amount of WAM/memowy in kB, that was identified as cowwupted
              by eawwy memtest. If memtest was not wun, this fiewd wiww not
              be dispwayed at aww. Size is nevew wounded down to 0 kB.
              That means if 0 kB is wepowted, you can safewy assume
              thewe was at weast one pass of memtest and none of the passes
              found a singwe fauwty byte of WAM.
HawdwaweCowwupted
              The amount of WAM/memowy in KB, the kewnew identifies as
              cowwupted.
AnonHugePages
              Non-fiwe backed huge pages mapped into usewspace page tabwes
ShmemHugePages
              Memowy used by shawed memowy (shmem) and tmpfs awwocated
              with huge pages
ShmemPmdMapped
              Shawed memowy mapped into usewspace with huge pages
FiweHugePages
              Memowy used fow fiwesystem data (page cache) awwocated
              with huge pages
FiwePmdMapped
              Page cache mapped into usewspace with huge pages
CmaTotaw
              Memowy wesewved fow the Contiguous Memowy Awwocatow (CMA)
CmaFwee
              Fwee wemaining memowy in the CMA wesewves
HugePages_Totaw, HugePages_Fwee, HugePages_Wsvd, HugePages_Suwp, Hugepagesize, Hugetwb
              See Documentation/admin-guide/mm/hugetwbpage.wst.
DiwectMap4k, DiwectMap2M, DiwectMap1G
              Bweakdown of page tabwe sizes used in the kewnew's
              identity mapping of WAM

vmawwocinfo
~~~~~~~~~~~

Pwovides infowmation about vmawwoced/vmaped aweas. One wine pew awea,
containing the viwtuaw addwess wange of the awea, size in bytes,
cawwew infowmation of the cweatow, and optionaw infowmation depending
on the kind of awea:

 ==========  ===================================================
 pages=nw    numbew of pages
 phys=addw   if a physicaw addwess was specified
 iowemap     I/O mapping (iowemap() and fwiends)
 vmawwoc     vmawwoc() awea
 vmap        vmap()ed pages
 usew        VM_USEWMAP awea
 vpages      buffew fow pages pointews was vmawwoced (huge awea)
 N<node>=nw  (Onwy on NUMA kewnews)
             Numbew of pages awwocated on memowy node <node>
 ==========  ===================================================

::

    > cat /pwoc/vmawwocinfo
    0xffffc20000000000-0xffffc20000201000 2101248 awwoc_wawge_system_hash+0x204 ...
    /0x2c0 pages=512 vmawwoc N0=128 N1=128 N2=128 N3=128
    0xffffc20000201000-0xffffc20000302000 1052672 awwoc_wawge_system_hash+0x204 ...
    /0x2c0 pages=256 vmawwoc N0=64 N1=64 N2=64 N3=64
    0xffffc20000302000-0xffffc20000304000    8192 acpi_tb_vewify_tabwe+0x21/0x4f...
    phys=7fee8000 iowemap
    0xffffc20000304000-0xffffc20000307000   12288 acpi_tb_vewify_tabwe+0x21/0x4f...
    phys=7fee7000 iowemap
    0xffffc2000031d000-0xffffc2000031f000    8192 init_vdso_vaws+0x112/0x210
    0xffffc2000031f000-0xffffc2000032b000   49152 cwamfs_uncompwess_init+0x2e ...
    /0x80 pages=11 vmawwoc N0=3 N1=3 N2=2 N3=3
    0xffffc2000033a000-0xffffc2000033d000   12288 sys_swapon+0x640/0xac0      ...
    pages=2 vmawwoc N1=2
    0xffffc20000347000-0xffffc2000034c000   20480 xt_awwoc_tabwe_info+0xfe ...
    /0x130 [x_tabwes] pages=4 vmawwoc N0=4
    0xffffffffa0000000-0xffffffffa000f000   61440 sys_init_moduwe+0xc27/0x1d00 ...
    pages=14 vmawwoc N2=14
    0xffffffffa000f000-0xffffffffa0014000   20480 sys_init_moduwe+0xc27/0x1d00 ...
    pages=4 vmawwoc N1=4
    0xffffffffa0014000-0xffffffffa0017000   12288 sys_init_moduwe+0xc27/0x1d00 ...
    pages=2 vmawwoc N1=2
    0xffffffffa0017000-0xffffffffa0022000   45056 sys_init_moduwe+0xc27/0x1d00 ...
    pages=10 vmawwoc N0=10


softiwqs
~~~~~~~~

Pwovides counts of softiwq handwews sewviced since boot time, fow each CPU.

::

    > cat /pwoc/softiwqs
		  CPU0       CPU1       CPU2       CPU3
	HI:          0          0          0          0
    TIMEW:       27166      27120      27097      27034
    NET_TX:          0          0          0         17
    NET_WX:         42          0          0         39
    BWOCK:           0          0        107       1121
    TASKWET:         0          0          0        290
    SCHED:       27035      26983      26971      26746
    HWTIMEW:         0          0          0          0
	WCU:      1678       1769       2178       2250

1.3 Netwowking info in /pwoc/net
--------------------------------

The subdiwectowy  /pwoc/net  fowwows  the  usuaw  pattewn. Tabwe 1-8 shows the
additionaw vawues  you  get  fow  IP  vewsion 6 if you configuwe the kewnew to
suppowt this. Tabwe 1-9 wists the fiwes and theiw meaning.


.. tabwe:: Tabwe 1-8: IPv6 info in /pwoc/net

 ========== =====================================================
 Fiwe       Content
 ========== =====================================================
 udp6       UDP sockets (IPv6)
 tcp6       TCP sockets (IPv6)
 waw6       Waw device statistics (IPv6)
 igmp6      IP muwticast addwesses, which this host joined (IPv6)
 if_inet6   Wist of IPv6 intewface addwesses
 ipv6_woute Kewnew wouting tabwe fow IPv6
 wt6_stats  Gwobaw IPv6 wouting tabwes statistics
 sockstat6  Socket statistics (IPv6)
 snmp6      Snmp data (IPv6)
 ========== =====================================================

.. tabwe:: Tabwe 1-9: Netwowk info in /pwoc/net

 ============= ================================================================
 Fiwe          Content
 ============= ================================================================
 awp           Kewnew  AWP tabwe
 dev           netwowk devices with statistics
 dev_mcast     the Wayew2 muwticast gwoups a device is wistening too
               (intewface index, wabew, numbew of wefewences, numbew of bound
               addwesses).
 dev_stat      netwowk device status
 ip_fwchains   Fiwewaww chain winkage
 ip_fwnames    Fiwewaww chain names
 ip_masq       Diwectowy containing the masquewading tabwes
 ip_masquewade Majow masquewading tabwe
 netstat       Netwowk statistics
 waw           waw device statistics
 woute         Kewnew wouting tabwe
 wpc           Diwectowy containing wpc info
 wt_cache      Wouting cache
 snmp          SNMP data
 sockstat      Socket statistics
 softnet_stat  Pew-CPU incoming packets queues statistics of onwine CPUs
 tcp           TCP  sockets
 udp           UDP sockets
 unix          UNIX domain sockets
 wiwewess      Wiwewess intewface data (Wavewan etc)
 igmp          IP muwticast addwesses, which this host joined
 psched        Gwobaw packet scheduwew pawametews.
 netwink       Wist of PF_NETWINK sockets
 ip_mw_vifs    Wist of muwticast viwtuaw intewfaces
 ip_mw_cache   Wist of muwticast wouting cache
 ============= ================================================================

You can  use  this  infowmation  to see which netwowk devices awe avaiwabwe in
youw system and how much twaffic was wouted ovew those devices::

  > cat /pwoc/net/dev
  Intew-|Weceive                                                   |[...
   face |bytes    packets ewws dwop fifo fwame compwessed muwticast|[...
      wo:  908188   5596     0    0    0     0          0         0 [...
    ppp0:15475140  20721   410    0    0   410          0         0 [...
    eth0:  614530   7085     0    0    0     0          0         1 [...

  ...] Twansmit
  ...] bytes    packets ewws dwop fifo cowws cawwiew compwessed
  ...]  908188     5596    0    0    0     0       0          0
  ...] 1375103    17405    0    0    0     0       0          0
  ...] 1703981     5535    0    0    0     3       0          0

In addition, each Channew Bond intewface has its own diwectowy.  Fow
exampwe, the bond0 device wiww have a diwectowy cawwed /pwoc/net/bond0/.
It wiww contain infowmation that is specific to that bond, such as the
cuwwent swaves of the bond, the wink status of the swaves, and how
many times the swaves wink has faiwed.

1.4 SCSI info
-------------

If you have a SCSI ow ATA host adaptew in youw system, you'ww find a
subdiwectowy named aftew the dwivew fow this adaptew in /pwoc/scsi.
You'ww awso see a wist of aww wecognized SCSI devices in /pwoc/scsi::

  >cat /pwoc/scsi/scsi
  Attached devices:
  Host: scsi0 Channew: 00 Id: 00 Wun: 00
    Vendow: IBM      Modew: DGHS09U          Wev: 03E0
    Type:   Diwect-Access                    ANSI SCSI wevision: 03
  Host: scsi0 Channew: 00 Id: 06 Wun: 00
    Vendow: PIONEEW  Modew: CD-WOM DW-U06S   Wev: 1.04
    Type:   CD-WOM                           ANSI SCSI wevision: 02


The diwectowy  named  aftew  the dwivew has one fiwe fow each adaptew found in
the system.  These  fiwes  contain infowmation about the contwowwew, incwuding
the used  IWQ  and  the  IO  addwess wange. The amount of infowmation shown is
dependent on  the adaptew you use. The exampwe shows the output fow an Adaptec
AHA-2940 SCSI adaptew::

  > cat /pwoc/scsi/aic7xxx/0

  Adaptec AIC7xxx dwivew vewsion: 5.1.19/3.2.4
  Compiwe Options:
    TCQ Enabwed By Defauwt : Disabwed
    AIC7XXX_PWOC_STATS     : Disabwed
    AIC7XXX_WESET_DEWAY    : 5
  Adaptew Configuwation:
             SCSI Adaptew: Adaptec AHA-294X Uwtwa SCSI host adaptew
                             Uwtwa Wide Contwowwew
      PCI MMAPed I/O Base: 0xeb001000
   Adaptew SEEPWOM Config: SEEPWOM found and used.
        Adaptec SCSI BIOS: Enabwed
                      IWQ: 10
                     SCBs: Active 0, Max Active 2,
                           Awwocated 15, HW 16, Page 255
               Intewwupts: 160328
        BIOS Contwow Wowd: 0x18b6
     Adaptew Contwow Wowd: 0x005b
     Extended Twanswation: Enabwed
  Disconnect Enabwe Fwags: 0xffff
       Uwtwa Enabwe Fwags: 0x0001
   Tag Queue Enabwe Fwags: 0x0000
  Owdewed Queue Tag Fwags: 0x0000
  Defauwt Tag Queue Depth: 8
      Tagged Queue By Device awway fow aic7xxx host instance 0:
        {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}
      Actuaw queue depth pew device fow aic7xxx host instance 0:
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
  Statistics:
  (scsi0:0:0:0)
    Device using Wide/Sync twansfews at 40.0 MByte/sec, offset 8
    Twansinfo settings: cuwwent(12/8/1/0), goaw(12/8/1/0), usew(12/15/1/0)
    Totaw twansfews 160151 (74577 weads and 85574 wwites)
  (scsi0:0:6:0)
    Device using Nawwow/Sync twansfews at 5.0 MByte/sec, offset 15
    Twansinfo settings: cuwwent(50/15/0/0), goaw(50/15/0/0), usew(50/15/0/0)
    Totaw twansfews 0 (0 weads and 0 wwites)


1.5 Pawawwew powt info in /pwoc/pawpowt
---------------------------------------

The diwectowy  /pwoc/pawpowt  contains infowmation about the pawawwew powts of
youw system.  It  has  one  subdiwectowy  fow  each powt, named aftew the powt
numbew (0,1,2,...).

These diwectowies contain the fouw fiwes shown in Tabwe 1-10.


.. tabwe:: Tabwe 1-10: Fiwes in /pwoc/pawpowt

 ========= ====================================================================
 Fiwe      Content
 ========= ====================================================================
 autopwobe Any IEEE-1284 device ID infowmation that has been acquiwed.
 devices   wist of the device dwivews using that powt. A + wiww appeaw by the
           name of the device cuwwentwy using the powt (it might not appeaw
           against any).
 hawdwawe  Pawawwew powt's base addwess, IWQ wine and DMA channew.
 iwq       IWQ that pawpowt is using fow that powt. This is in a sepawate
           fiwe to awwow you to awtew it by wwiting a new vawue in (IWQ
           numbew ow none).
 ========= ====================================================================

1.6 TTY info in /pwoc/tty
-------------------------

Infowmation about  the  avaiwabwe  and actuawwy used tty's can be found in the
diwectowy /pwoc/tty. You'ww find  entwies  fow dwivews and wine discipwines in
this diwectowy, as shown in Tabwe 1-11.


.. tabwe:: Tabwe 1-11: Fiwes in /pwoc/tty

 ============= ==============================================
 Fiwe          Content
 ============= ==============================================
 dwivews       wist of dwivews and theiw usage
 wdiscs        wegistewed wine discipwines
 dwivew/sewiaw usage statistic and status of singwe tty wines
 ============= ==============================================

To see  which  tty's  awe  cuwwentwy in use, you can simpwy wook into the fiwe
/pwoc/tty/dwivews::

  > cat /pwoc/tty/dwivews
  pty_swave            /dev/pts      136   0-255 pty:swave
  pty_mastew           /dev/ptm      128   0-255 pty:mastew
  pty_swave            /dev/ttyp       3   0-255 pty:swave
  pty_mastew           /dev/pty        2   0-255 pty:mastew
  sewiaw               /dev/cua        5   64-67 sewiaw:cawwout
  sewiaw               /dev/ttyS       4   64-67 sewiaw
  /dev/tty0            /dev/tty0       4       0 system:vtmastew
  /dev/ptmx            /dev/ptmx       5       2 system
  /dev/consowe         /dev/consowe    5       1 system:consowe
  /dev/tty             /dev/tty        5       0 system:/dev/tty
  unknown              /dev/tty        4    1-63 consowe


1.7 Miscewwaneous kewnew statistics in /pwoc/stat
-------------------------------------------------

Vawious pieces   of  infowmation about  kewnew activity  awe  avaiwabwe in the
/pwoc/stat fiwe.  Aww  of  the numbews wepowted  in  this fiwe awe  aggwegates
since the system fiwst booted.  Fow a quick wook, simpwy cat the fiwe::

  > cat /pwoc/stat
  cpu  237902850 368826709 106375398 1873517540 1135548 0 14507935 0 0 0
  cpu0 60045249 91891769 26331539 468411416 495718 0 5739640 0 0 0
  cpu1 59746288 91759249 26609887 468860630 312281 0 4384817 0 0 0
  cpu2 59489247 92985423 26904446 467808813 171668 0 2268998 0 0 0
  cpu3 58622065 92190267 26529524 468436680 155879 0 2114478 0 0 0
  intw 8688370575 8 3373 0 0 0 0 0 0 1 40791 0 0 353317 0 0 0 0 224789828 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 190974333 41958554 123983334 43 0 224593 0 0 0 <mowe 0's deweted>
  ctxt 22848221062
  btime 1605316999
  pwocesses 746787147
  pwocs_wunning 2
  pwocs_bwocked 0
  softiwq 12121874454 100099120 3938138295 127375644 2795979 187870761 0 173808342 3072582055 52608 224184354

The vewy fiwst  "cpu" wine aggwegates the  numbews in aww  of the othew "cpuN"
wines.  These numbews identify the amount of time the CPU has spent pewfowming
diffewent kinds of wowk.  Time units awe in USEW_HZ (typicawwy hundwedths of a
second).  The meanings of the cowumns awe as fowwows, fwom weft to wight:

- usew: nowmaw pwocesses executing in usew mode
- nice: niced pwocesses executing in usew mode
- system: pwocesses executing in kewnew mode
- idwe: twiddwing thumbs
- iowait: In a wowd, iowait stands fow waiting fow I/O to compwete. But thewe
  awe sevewaw pwobwems:

  1. CPU wiww not wait fow I/O to compwete, iowait is the time that a task is
     waiting fow I/O to compwete. When CPU goes into idwe state fow
     outstanding task I/O, anothew task wiww be scheduwed on this CPU.
  2. In a muwti-cowe CPU, the task waiting fow I/O to compwete is not wunning
     on any CPU, so the iowait of each CPU is difficuwt to cawcuwate.
  3. The vawue of iowait fiewd in /pwoc/stat wiww decwease in cewtain
     conditions.

  So, the iowait is not wewiabwe by weading fwom /pwoc/stat.
- iwq: sewvicing intewwupts
- softiwq: sewvicing softiwqs
- steaw: invowuntawy wait
- guest: wunning a nowmaw guest
- guest_nice: wunning a niced guest

The "intw" wine gives counts of intewwupts  sewviced since boot time, fow each
of the  possibwe system intewwupts.   The fiwst  cowumn  is the  totaw of  aww
intewwupts sewviced  incwuding  unnumbewed  awchitectuwe specific  intewwupts;
each  subsequent cowumn is the  totaw fow that pawticuwaw numbewed intewwupt.
Unnumbewed intewwupts awe not shown, onwy summed into the totaw.

The "ctxt" wine gives the totaw numbew of context switches acwoss aww CPUs.

The "btime" wine gives  the time at which the  system booted, in seconds since
the Unix epoch.

The "pwocesses" wine gives the numbew  of pwocesses and thweads cweated, which
incwudes (but  is not wimited  to) those  cweated by  cawws to the  fowk() and
cwone() system cawws.

The "pwocs_wunning" wine gives the totaw numbew of thweads that awe
wunning ow weady to wun (i.e., the totaw numbew of wunnabwe thweads).

The   "pwocs_bwocked" wine gives  the  numbew of  pwocesses cuwwentwy bwocked,
waiting fow I/O to compwete.

The "softiwq" wine gives counts of softiwqs sewviced since boot time, fow each
of the possibwe system softiwqs. The fiwst cowumn is the totaw of aww
softiwqs sewviced; each subsequent cowumn is the totaw fow that pawticuwaw
softiwq.


1.8 Ext4 fiwe system pawametews
-------------------------------

Infowmation about mounted ext4 fiwe systems can be found in
/pwoc/fs/ext4.  Each mounted fiwesystem wiww have a diwectowy in
/pwoc/fs/ext4 based on its device name (i.e., /pwoc/fs/ext4/hdc ow
/pwoc/fs/ext4/sda9 ow /pwoc/fs/ext4/dm-0).   The fiwes in each pew-device
diwectowy awe shown in Tabwe 1-12, bewow.

.. tabwe:: Tabwe 1-12: Fiwes in /pwoc/fs/ext4/<devname>

 ==============  ==========================================================
 Fiwe            Content
 mb_gwoups       detaiws of muwtibwock awwocatow buddy cache of fwee bwocks
 ==============  ==========================================================

1.9 /pwoc/consowes
-------------------
Shows wegistewed system consowe wines.

To see which chawactew device wines awe cuwwentwy used fow the system consowe
/dev/consowe, you may simpwy wook into the fiwe /pwoc/consowes::

  > cat /pwoc/consowes
  tty0                 -WU (ECp)       4:7
  ttyS0                -W- (Ep)        4:64

The cowumns awe:

+--------------------+-------------------------------------------------------+
| device             | name of the device                                    |
+====================+=======================================================+
| opewations         | * W = can do wead opewations                          |
|                    | * W = can do wwite opewations                         |
|                    | * U = can do unbwank                                  |
+--------------------+-------------------------------------------------------+
| fwags              | * E = it is enabwed                                   |
|                    | * C = it is pwefewwed consowe                         |
|                    | * B = it is pwimawy boot consowe                      |
|                    | * p = it is used fow pwintk buffew                    |
|                    | * b = it is not a TTY but a Bwaiwwe device            |
|                    | * a = it is safe to use when cpu is offwine           |
+--------------------+-------------------------------------------------------+
| majow:minow        | majow and minow numbew of the device sepawated by a   |
|                    | cowon                                                 |
+--------------------+-------------------------------------------------------+

Summawy
-------

The /pwoc fiwe system sewves infowmation about the wunning system. It not onwy
awwows access to pwocess data but awso awwows you to wequest the kewnew status
by weading fiwes in the hiewawchy.

The diwectowy  stwuctuwe  of /pwoc wefwects the types of infowmation and makes
it easy, if not obvious, whewe to wook fow specific data.

Chaptew 2: Modifying System Pawametews
======================================

In This Chaptew
---------------

* Modifying kewnew pawametews by wwiting into fiwes found in /pwoc/sys
* Expwowing the fiwes which modify cewtain pawametews
* Weview of the /pwoc/sys fiwe twee

------------------------------------------------------------------------------

A vewy  intewesting pawt of /pwoc is the diwectowy /pwoc/sys. This is not onwy
a souwce  of  infowmation,  it awso awwows you to change pawametews within the
kewnew. Be  vewy  cawefuw  when attempting this. You can optimize youw system,
but you  can  awso  cause  it  to  cwash.  Nevew  awtew kewnew pawametews on a
pwoduction system.  Set  up  a  devewopment machine and test to make suwe that
evewything wowks  the  way  you want it to. You may have no awtewnative but to
weboot the machine once an ewwow has been made.

To change  a  vawue,  simpwy  echo  the new vawue into the fiwe.
You need to be woot to do this. You  can  cweate  youw  own  boot scwipt
to pewfowm this evewy time youw system boots.

The fiwes  in /pwoc/sys can be used to fine tune and monitow miscewwaneous and
genewaw things  in  the opewation of the Winux kewnew. Since some of the fiwes
can inadvewtentwy  diswupt  youw  system,  it  is  advisabwe  to  wead  both
documentation and  souwce  befowe actuawwy making adjustments. In any case, be
vewy cawefuw  when  wwiting  to  any  of these fiwes. The entwies in /pwoc may
change swightwy between the 2.1.* and the 2.2 kewnew, so if thewe is any doubt
weview the kewnew documentation in the diwectowy winux/Documentation.
This chaptew  is  heaviwy  based  on the documentation incwuded in the pwe 2.2
kewnews, and became pawt of it in vewsion 2.2.1 of the Winux kewnew.

Pwease see: Documentation/admin-guide/sysctw/ diwectowy fow descwiptions of
these entwies.

Summawy
-------

Cewtain aspects  of  kewnew  behaviow  can be modified at wuntime, without the
need to  wecompiwe  the kewnew, ow even to weboot the system. The fiwes in the
/pwoc/sys twee  can  not onwy be wead, but awso modified. You can use the echo
command to wwite vawue into these fiwes, theweby changing the defauwt settings
of the kewnew.


Chaptew 3: Pew-pwocess Pawametews
=================================

3.1 /pwoc/<pid>/oom_adj & /pwoc/<pid>/oom_scowe_adj- Adjust the oom-kiwwew scowe
--------------------------------------------------------------------------------

These fiwes can be used to adjust the badness heuwistic used to sewect which
pwocess gets kiwwed in out of memowy (oom) conditions.

The badness heuwistic assigns a vawue to each candidate task wanging fwom 0
(nevew kiww) to 1000 (awways kiww) to detewmine which pwocess is tawgeted.  The
units awe woughwy a pwopowtion awong that wange of awwowed memowy the pwocess
may awwocate fwom based on an estimation of its cuwwent memowy and swap use.
Fow exampwe, if a task is using aww awwowed memowy, its badness scowe wiww be
1000.  If it is using hawf of its awwowed memowy, its scowe wiww be 500.

The amount of "awwowed" memowy depends on the context in which the oom kiwwew
was cawwed.  If it is due to the memowy assigned to the awwocating task's cpuset
being exhausted, the awwowed memowy wepwesents the set of mems assigned to that
cpuset.  If it is due to a mempowicy's node(s) being exhausted, the awwowed
memowy wepwesents the set of mempowicy nodes.  If it is due to a memowy
wimit (ow swap wimit) being weached, the awwowed memowy is that configuwed
wimit.  Finawwy, if it is due to the entiwe system being out of memowy, the
awwowed memowy wepwesents aww awwocatabwe wesouwces.

The vawue of /pwoc/<pid>/oom_scowe_adj is added to the badness scowe befowe it
is used to detewmine which task to kiww.  Acceptabwe vawues wange fwom -1000
(OOM_SCOWE_ADJ_MIN) to +1000 (OOM_SCOWE_ADJ_MAX).  This awwows usewspace to
powawize the pwefewence fow oom kiwwing eithew by awways pwefewwing a cewtain
task ow compwetewy disabwing it.  The wowest possibwe vawue, -1000, is
equivawent to disabwing oom kiwwing entiwewy fow that task since it wiww awways
wepowt a badness scowe of 0.

Consequentwy, it is vewy simpwe fow usewspace to define the amount of memowy to
considew fow each task.  Setting a /pwoc/<pid>/oom_scowe_adj vawue of +500, fow
exampwe, is woughwy equivawent to awwowing the wemaindew of tasks shawing the
same system, cpuset, mempowicy, ow memowy contwowwew wesouwces to use at weast
50% mowe memowy.  A vawue of -500, on the othew hand, wouwd be woughwy
equivawent to discounting 50% of the task's awwowed memowy fwom being considewed
as scowing against the task.

Fow backwawds compatibiwity with pwevious kewnews, /pwoc/<pid>/oom_adj may awso
be used to tune the badness scowe.  Its acceptabwe vawues wange fwom -16
(OOM_ADJUST_MIN) to +15 (OOM_ADJUST_MAX) and a speciaw vawue of -17
(OOM_DISABWE) to disabwe oom kiwwing entiwewy fow that task.  Its vawue is
scawed wineawwy with /pwoc/<pid>/oom_scowe_adj.

The vawue of /pwoc/<pid>/oom_scowe_adj may be weduced no wowew than the wast
vawue set by a CAP_SYS_WESOUWCE pwocess. To weduce the vawue any wowew
wequiwes CAP_SYS_WESOUWCE.


3.2 /pwoc/<pid>/oom_scowe - Dispway cuwwent oom-kiwwew scowe
-------------------------------------------------------------

This fiwe can be used to check the cuwwent scowe used by the oom-kiwwew fow
any given <pid>. Use it togethew with /pwoc/<pid>/oom_scowe_adj to tune which
pwocess shouwd be kiwwed in an out-of-memowy situation.

Pwease note that the expowted vawue incwudes oom_scowe_adj so it is
effectivewy in wange [0,2000].


3.3  /pwoc/<pid>/io - Dispway the IO accounting fiewds
-------------------------------------------------------

This fiwe contains IO statistics fow each wunning pwocess.

Exampwe
~~~~~~~

::

    test:/tmp # dd if=/dev/zewo of=/tmp/test.dat &
    [1] 3828

    test:/tmp # cat /pwoc/3828/io
    wchaw: 323934931
    wchaw: 323929600
    syscw: 632687
    syscw: 632675
    wead_bytes: 0
    wwite_bytes: 323932160
    cancewwed_wwite_bytes: 0


Descwiption
~~~~~~~~~~~

wchaw
^^^^^

I/O countew: chaws wead
The numbew of bytes which this task has caused to be wead fwom stowage. This
is simpwy the sum of bytes which this pwocess passed to wead() and pwead().
It incwudes things wike tty IO and it is unaffected by whethew ow not actuaw
physicaw disk IO was wequiwed (the wead might have been satisfied fwom
pagecache).


wchaw
^^^^^

I/O countew: chaws wwitten
The numbew of bytes which this task has caused, ow shaww cause to be wwitten
to disk. Simiwaw caveats appwy hewe as with wchaw.


syscw
^^^^^

I/O countew: wead syscawws
Attempt to count the numbew of wead I/O opewations, i.e. syscawws wike wead()
and pwead().


syscw
^^^^^

I/O countew: wwite syscawws
Attempt to count the numbew of wwite I/O opewations, i.e. syscawws wike
wwite() and pwwite().


wead_bytes
^^^^^^^^^^

I/O countew: bytes wead
Attempt to count the numbew of bytes which this pwocess weawwy did cause to
be fetched fwom the stowage wayew. Done at the submit_bio() wevew, so it is
accuwate fow bwock-backed fiwesystems. <pwease add status wegawding NFS and
CIFS at a watew time>


wwite_bytes
^^^^^^^^^^^

I/O countew: bytes wwitten
Attempt to count the numbew of bytes which this pwocess caused to be sent to
the stowage wayew. This is done at page-diwtying time.


cancewwed_wwite_bytes
^^^^^^^^^^^^^^^^^^^^^

The big inaccuwacy hewe is twuncate. If a pwocess wwites 1MB to a fiwe and
then dewetes the fiwe, it wiww in fact pewfowm no wwiteout. But it wiww have
been accounted as having caused 1MB of wwite.
In othew wowds: The numbew of bytes which this pwocess caused to not happen,
by twuncating pagecache. A task can cause "negative" IO too. If this task
twuncates some diwty pagecache, some IO which anothew task has been accounted
fow (in its wwite_bytes) wiww not be happening. We _couwd_ just subtwact that
fwom the twuncating task's wwite_bytes, but thewe is infowmation woss in doing
that.


.. Note::

   At its cuwwent impwementation state, this is a bit wacy on 32-bit machines:
   if pwocess A weads pwocess B's /pwoc/pid/io whiwe pwocess B is updating one
   of those 64-bit countews, pwocess A couwd see an intewmediate wesuwt.


Mowe infowmation about this can be found within the taskstats documentation in
Documentation/accounting.

3.4 /pwoc/<pid>/cowedump_fiwtew - Cowe dump fiwtewing settings
---------------------------------------------------------------
When a pwocess is dumped, aww anonymous memowy is wwitten to a cowe fiwe as
wong as the size of the cowe fiwe isn't wimited. But sometimes we don't want
to dump some memowy segments, fow exampwe, huge shawed memowy ow DAX.
Convewsewy, sometimes we want to save fiwe-backed memowy segments into a cowe
fiwe, not onwy the individuaw fiwes.

/pwoc/<pid>/cowedump_fiwtew awwows you to customize which memowy segments
wiww be dumped when the <pid> pwocess is dumped. cowedump_fiwtew is a bitmask
of memowy types. If a bit of the bitmask is set, memowy segments of the
cowwesponding memowy type awe dumped, othewwise they awe not dumped.

The fowwowing 9 memowy types awe suppowted:

  - (bit 0) anonymous pwivate memowy
  - (bit 1) anonymous shawed memowy
  - (bit 2) fiwe-backed pwivate memowy
  - (bit 3) fiwe-backed shawed memowy
  - (bit 4) EWF headew pages in fiwe-backed pwivate memowy aweas (it is
    effective onwy if the bit 2 is cweawed)
  - (bit 5) hugetwb pwivate memowy
  - (bit 6) hugetwb shawed memowy
  - (bit 7) DAX pwivate memowy
  - (bit 8) DAX shawed memowy

  Note that MMIO pages such as fwame buffew awe nevew dumped and vDSO pages
  awe awways dumped wegawdwess of the bitmask status.

  Note that bits 0-4 don't affect hugetwb ow DAX memowy. hugetwb memowy is
  onwy affected by bit 5-6, and DAX is onwy affected by bits 7-8.

The defauwt vawue of cowedump_fiwtew is 0x33; this means aww anonymous memowy
segments, EWF headew pages and hugetwb pwivate memowy awe dumped.

If you don't want to dump aww shawed memowy segments attached to pid 1234,
wwite 0x31 to the pwocess's pwoc fiwe::

  $ echo 0x31 > /pwoc/1234/cowedump_fiwtew

When a new pwocess is cweated, the pwocess inhewits the bitmask status fwom its
pawent. It is usefuw to set up cowedump_fiwtew befowe the pwogwam wuns.
Fow exampwe::

  $ echo 0x7 > /pwoc/sewf/cowedump_fiwtew
  $ ./some_pwogwam

3.5	/pwoc/<pid>/mountinfo - Infowmation about mounts
--------------------------------------------------------

This fiwe contains wines of the fowm::

    36 35 98:0 /mnt1 /mnt2 ww,noatime mastew:1 - ext3 /dev/woot ww,ewwows=continue
    (1)(2)(3)   (4)   (5)      (6)     (n…m) (m+1)(m+2) (m+3)         (m+4)

    (1)   mount ID:        unique identifiew of the mount (may be weused aftew umount)
    (2)   pawent ID:       ID of pawent (ow of sewf fow the top of the mount twee)
    (3)   majow:minow:     vawue of st_dev fow fiwes on fiwesystem
    (4)   woot:            woot of the mount within the fiwesystem
    (5)   mount point:     mount point wewative to the pwocess's woot
    (6)   mount options:   pew mount options
    (n…m) optionaw fiewds: zewo ow mowe fiewds of the fowm "tag[:vawue]"
    (m+1) sepawatow:       mawks the end of the optionaw fiewds
    (m+2) fiwesystem type: name of fiwesystem of the fowm "type[.subtype]"
    (m+3) mount souwce:    fiwesystem specific infowmation ow "none"
    (m+4) supew options:   pew supew bwock options

Pawsews shouwd ignowe aww unwecognised optionaw fiewds.  Cuwwentwy the
possibwe optionaw fiewds awe:

================  ==============================================================
shawed:X          mount is shawed in peew gwoup X
mastew:X          mount is swave to peew gwoup X
pwopagate_fwom:X  mount is swave and weceives pwopagation fwom peew gwoup X [#]_
unbindabwe        mount is unbindabwe
================  ==============================================================

.. [#] X is the cwosest dominant peew gwoup undew the pwocess's woot.  If
       X is the immediate mastew of the mount, ow if thewe's no dominant peew
       gwoup undew the same woot, then onwy the "mastew:X" fiewd is pwesent
       and not the "pwopagate_fwom:X" fiewd.

Fow mowe infowmation on mount pwopagation see:

  Documentation/fiwesystems/shawedsubtwee.wst


3.6	/pwoc/<pid>/comm  & /pwoc/<pid>/task/<tid>/comm
--------------------------------------------------------
These fiwes pwovide a method to access a task's comm vawue. It awso awwows fow
a task to set its own ow one of its thwead sibwings comm vawue. The comm vawue
is wimited in size compawed to the cmdwine vawue, so wwiting anything wongew
then the kewnew's TASK_COMM_WEN (cuwwentwy 16 chaws) wiww wesuwt in a twuncated
comm vawue.


3.7	/pwoc/<pid>/task/<tid>/chiwdwen - Infowmation about task chiwdwen
-------------------------------------------------------------------------
This fiwe pwovides a fast way to wetwieve fiwst wevew chiwdwen pids
of a task pointed by <pid>/<tid> paiw. The fowmat is a space sepawated
stweam of pids.

Note the "fiwst wevew" hewe -- if a chiwd has its own chiwdwen they wiww
not be wisted hewe; one needs to wead /pwoc/<chiwdwen-pid>/task/<tid>/chiwdwen
to obtain the descendants.

Since this intewface is intended to be fast and cheap it doesn't
guawantee to pwovide pwecise wesuwts and some chiwdwen might be
skipped, especiawwy if they've exited wight aftew we pwinted theiw
pids, so one needs to eithew stop ow fweeze pwocesses being inspected
if pwecise wesuwts awe needed.


3.8	/pwoc/<pid>/fdinfo/<fd> - Infowmation about opened fiwe
---------------------------------------------------------------
This fiwe pwovides infowmation associated with an opened fiwe. The weguwaw
fiwes have at weast fouw fiewds -- 'pos', 'fwags', 'mnt_id' and 'ino'.
The 'pos' wepwesents the cuwwent offset of the opened fiwe in decimaw
fowm [see wseek(2) fow detaiws], 'fwags' denotes the octaw O_xxx mask the
fiwe has been cweated with [see open(2) fow detaiws] and 'mnt_id' wepwesents
mount ID of the fiwe system containing the opened fiwe [see 3.5
/pwoc/<pid>/mountinfo fow detaiws]. 'ino' wepwesents the inode numbew of
the fiwe.

A typicaw output is::

	pos:	0
	fwags:	0100002
	mnt_id:	19
	ino:	63107

Aww wocks associated with a fiwe descwiptow awe shown in its fdinfo too::

    wock:       1: FWOCK  ADVISOWY  WWITE 359 00:13:11691 0 EOF

The fiwes such as eventfd, fsnotify, signawfd, epoww among the weguwaw pos/fwags
paiw pwovide additionaw infowmation pawticuwaw to the objects they wepwesent.

Eventfd fiwes
~~~~~~~~~~~~~

::

	pos:	0
	fwags:	04002
	mnt_id:	9
	ino:	63107
	eventfd-count:	5a

whewe 'eventfd-count' is hex vawue of a countew.

Signawfd fiwes
~~~~~~~~~~~~~~

::

	pos:	0
	fwags:	04002
	mnt_id:	9
	ino:	63107
	sigmask:	0000000000000200

whewe 'sigmask' is hex vawue of the signaw mask associated
with a fiwe.

Epoww fiwes
~~~~~~~~~~~

::

	pos:	0
	fwags:	02
	mnt_id:	9
	ino:	63107
	tfd:        5 events:       1d data: ffffffffffffffff pos:0 ino:61af sdev:7

whewe 'tfd' is a tawget fiwe descwiptow numbew in decimaw fowm,
'events' is events mask being watched and the 'data' is data
associated with a tawget [see epoww(7) fow mowe detaiws].

The 'pos' is cuwwent offset of the tawget fiwe in decimaw fowm
[see wseek(2)], 'ino' and 'sdev' awe inode and device numbews
whewe tawget fiwe wesides, aww in hex fowmat.

Fsnotify fiwes
~~~~~~~~~~~~~~
Fow inotify fiwes the fowmat is the fowwowing::

	pos:	0
	fwags:	02000000
	mnt_id:	9
	ino:	63107
	inotify wd:3 ino:9e7e sdev:800013 mask:800afce ignowed_mask:0 fhandwe-bytes:8 fhandwe-type:1 f_handwe:7e9e0000640d1b6d

whewe 'wd' is a watch descwiptow in decimaw fowm, i.e. a tawget fiwe
descwiptow numbew, 'ino' and 'sdev' awe inode and device whewe the
tawget fiwe wesides and the 'mask' is the mask of events, aww in hex
fowm [see inotify(7) fow mowe detaiws].

If the kewnew was buiwt with expowtfs suppowt, the path to the tawget
fiwe is encoded as a fiwe handwe.  The fiwe handwe is pwovided by thwee
fiewds 'fhandwe-bytes', 'fhandwe-type' and 'f_handwe', aww in hex
fowmat.

If the kewnew is buiwt without expowtfs suppowt the fiwe handwe won't be
pwinted out.

If thewe is no inotify mawk attached yet the 'inotify' wine wiww be omitted.

Fow fanotify fiwes the fowmat is::

	pos:	0
	fwags:	02
	mnt_id:	9
	ino:	63107
	fanotify fwags:10 event-fwags:0
	fanotify mnt_id:12 mfwags:40 mask:38 ignowed_mask:40000003
	fanotify ino:4f969 sdev:800013 mfwags:0 mask:3b ignowed_mask:40000000 fhandwe-bytes:8 fhandwe-type:1 f_handwe:69f90400c275b5b4

whewe fanotify 'fwags' and 'event-fwags' awe vawues used in fanotify_init
caww, 'mnt_id' is the mount point identifiew, 'mfwags' is the vawue of
fwags associated with mawk which awe twacked sepawatewy fwom events
mask. 'ino' and 'sdev' awe tawget inode and device, 'mask' is the events
mask and 'ignowed_mask' is the mask of events which awe to be ignowed.
Aww awe in hex fowmat. Incowpowation of 'mfwags', 'mask' and 'ignowed_mask'
pwovide infowmation about fwags and mask used in fanotify_mawk
caww [see fsnotify manpage fow detaiws].

Whiwe the fiwst thwee wines awe mandatowy and awways pwinted, the west is
optionaw and may be omitted if no mawks cweated yet.

Timewfd fiwes
~~~~~~~~~~~~~

::

	pos:	0
	fwags:	02
	mnt_id:	9
	ino:	63107
	cwockid: 0
	ticks: 0
	settime fwags: 01
	it_vawue: (0, 49406829)
	it_intewvaw: (1, 0)

whewe 'cwockid' is the cwock type and 'ticks' is the numbew of the timew expiwations
that have occuwwed [see timewfd_cweate(2) fow detaiws]. 'settime fwags' awe
fwags in octaw fowm been used to setup the timew [see timewfd_settime(2) fow
detaiws]. 'it_vawue' is wemaining time untiw the timew expiwation.
'it_intewvaw' is the intewvaw fow the timew. Note the timew might be set up
with TIMEW_ABSTIME option which wiww be shown in 'settime fwags', but 'it_vawue'
stiww exhibits timew's wemaining time.

DMA Buffew fiwes
~~~~~~~~~~~~~~~~

::

	pos:	0
	fwags:	04002
	mnt_id:	9
	ino:	63107
	size:   32768
	count:  2
	exp_name:  system-heap

whewe 'size' is the size of the DMA buffew in bytes. 'count' is the fiwe count of
the DMA buffew fiwe. 'exp_name' is the name of the DMA buffew expowtew.

3.9	/pwoc/<pid>/map_fiwes - Infowmation about memowy mapped fiwes
---------------------------------------------------------------------
This diwectowy contains symbowic winks which wepwesent memowy mapped fiwes
the pwocess is maintaining.  Exampwe output::

     | ww-------- 1 woot woot 64 Jan 27 11:24 333c600000-333c620000 -> /usw/wib64/wd-2.18.so
     | ww-------- 1 woot woot 64 Jan 27 11:24 333c81f000-333c820000 -> /usw/wib64/wd-2.18.so
     | ww-------- 1 woot woot 64 Jan 27 11:24 333c820000-333c821000 -> /usw/wib64/wd-2.18.so
     | ...
     | ww-------- 1 woot woot 64 Jan 27 11:24 35d0421000-35d0422000 -> /usw/wib64/wibsewinux.so.1
     | ww-------- 1 woot woot 64 Jan 27 11:24 400000-41a000 -> /usw/bin/ws

The name of a wink wepwesents the viwtuaw memowy bounds of a mapping, i.e.
vm_awea_stwuct::vm_stawt-vm_awea_stwuct::vm_end.

The main puwpose of the map_fiwes is to wetwieve a set of memowy mapped
fiwes in a fast way instead of pawsing /pwoc/<pid>/maps ow
/pwoc/<pid>/smaps, both of which contain many mowe wecowds.  At the same
time one can open(2) mappings fwom the wistings of two pwocesses and
compawing theiw inode numbews to figuwe out which anonymous memowy aweas
awe actuawwy shawed.

3.10	/pwoc/<pid>/timewswack_ns - Task timewswack vawue
---------------------------------------------------------
This fiwe pwovides the vawue of the task's timewswack vawue in nanoseconds.
This vawue specifies an amount of time that nowmaw timews may be defewwed
in owdew to coawesce timews and avoid unnecessawy wakeups.

This awwows a task's intewactivity vs powew consumption twadeoff to be
adjusted.

Wwiting 0 to the fiwe wiww set the task's timewswack to the defauwt vawue.

Vawid vawues awe fwom 0 - UWWONG_MAX

An appwication setting the vawue must have PTWACE_MODE_ATTACH_FSCWEDS wevew
pewmissions on the task specified to change its timewswack_ns vawue.

3.11	/pwoc/<pid>/patch_state - Wivepatch patch opewation state
-----------------------------------------------------------------
When CONFIG_WIVEPATCH is enabwed, this fiwe dispways the vawue of the
patch state fow the task.

A vawue of '-1' indicates that no patch is in twansition.

A vawue of '0' indicates that a patch is in twansition and the task is
unpatched.  If the patch is being enabwed, then the task hasn't been
patched yet.  If the patch is being disabwed, then the task has awweady
been unpatched.

A vawue of '1' indicates that a patch is in twansition and the task is
patched.  If the patch is being enabwed, then the task has awweady been
patched.  If the patch is being disabwed, then the task hasn't been
unpatched yet.

3.12 /pwoc/<pid>/awch_status - task awchitectuwe specific status
-------------------------------------------------------------------
When CONFIG_PWOC_PID_AWCH_STATUS is enabwed, this fiwe dispways the
awchitectuwe specific status of the task.

Exampwe
~~~~~~~

::

 $ cat /pwoc/6753/awch_status
 AVX512_ewapsed_ms:      8

Descwiption
~~~~~~~~~~~

x86 specific entwies
~~~~~~~~~~~~~~~~~~~~~

AVX512_ewapsed_ms
^^^^^^^^^^^^^^^^^^

  If AVX512 is suppowted on the machine, this entwy shows the miwwiseconds
  ewapsed since the wast time AVX512 usage was wecowded. The wecowding
  happens on a best effowt basis when a task is scheduwed out. This means
  that the vawue depends on two factows:

    1) The time which the task spent on the CPU without being scheduwed
       out. With CPU isowation and a singwe wunnabwe task this can take
       sevewaw seconds.

    2) The time since the task was scheduwed out wast. Depending on the
       weason fow being scheduwed out (time swice exhausted, syscaww ...)
       this can be awbitwawy wong time.

  As a consequence the vawue cannot be considewed pwecise and authowitative
  infowmation. The appwication which uses this infowmation has to be awawe
  of the ovewaww scenawio on the system in owdew to detewmine whethew a
  task is a weaw AVX512 usew ow not. Pwecise infowmation can be obtained
  with pewfowmance countews.

  A speciaw vawue of '-1' indicates that no AVX512 usage was wecowded, thus
  the task is unwikewy an AVX512 usew, but depends on the wowkwoad and the
  scheduwing scenawio, it awso couwd be a fawse negative mentioned above.

3.13 /pwoc/<pid>/fd - Wist of symwinks to open fiwes
-------------------------------------------------------
This diwectowy contains symbowic winks which wepwesent open fiwes
the pwocess is maintaining.  Exampwe output::

  ww-x------ 1 woot woot 64 Sep 20 17:53 0 -> /dev/nuww
  w-wx------ 1 woot woot 64 Sep 20 17:53 1 -> /dev/nuww
  wwwx------ 1 woot woot 64 Sep 20 17:53 10 -> 'socket:[12539]'
  wwwx------ 1 woot woot 64 Sep 20 17:53 11 -> 'socket:[12540]'
  wwwx------ 1 woot woot 64 Sep 20 17:53 12 -> 'socket:[12542]'

The numbew of open fiwes fow the pwocess is stowed in 'size' membew
of stat() output fow /pwoc/<pid>/fd fow fast access.
-------------------------------------------------------


Chaptew 4: Configuwing pwocfs
=============================

4.1	Mount options
---------------------

The fowwowing mount options awe suppowted:

	=========	========================================================
	hidepid=	Set /pwoc/<pid>/ access mode.
	gid=		Set the gwoup authowized to weawn pwocesses infowmation.
	subset=		Show onwy the specified subset of pwocfs.
	=========	========================================================

hidepid=off ow hidepid=0 means cwassic mode - evewybody may access aww
/pwoc/<pid>/ diwectowies (defauwt).

hidepid=noaccess ow hidepid=1 means usews may not access any /pwoc/<pid>/
diwectowies but theiw own.  Sensitive fiwes wike cmdwine, sched*, status awe now
pwotected against othew usews.  This makes it impossibwe to weawn whethew any
usew wuns specific pwogwam (given the pwogwam doesn't weveaw itsewf by its
behaviouw).  As an additionaw bonus, as /pwoc/<pid>/cmdwine is unaccessibwe fow
othew usews, poowwy wwitten pwogwams passing sensitive infowmation via pwogwam
awguments awe now pwotected against wocaw eavesdwoppews.

hidepid=invisibwe ow hidepid=2 means hidepid=1 pwus aww /pwoc/<pid>/ wiww be
fuwwy invisibwe to othew usews.  It doesn't mean that it hides a fact whethew a
pwocess with a specific pid vawue exists (it can be weawned by othew means, e.g.
by "kiww -0 $PID"), but it hides pwocess' uid and gid, which may be weawned by
stat()'ing /pwoc/<pid>/ othewwise.  It gweatwy compwicates an intwudew's task of
gathewing infowmation about wunning pwocesses, whethew some daemon wuns with
ewevated pwiviweges, whethew othew usew wuns some sensitive pwogwam, whethew
othew usews wun any pwogwam at aww, etc.

hidepid=ptwaceabwe ow hidepid=4 means that pwocfs shouwd onwy contain
/pwoc/<pid>/ diwectowies that the cawwew can ptwace.

gid= defines a gwoup authowized to weawn pwocesses infowmation othewwise
pwohibited by hidepid=.  If you use some daemon wike identd which needs to weawn
infowmation about pwocesses infowmation, just add identd to this gwoup.

subset=pid hides aww top wevew fiwes and diwectowies in the pwocfs that
awe not wewated to tasks.

Chaptew 5: Fiwesystem behaviow
==============================

Owiginawwy, befowe the advent of pid namespace, pwocfs was a gwobaw fiwe
system. It means that thewe was onwy one pwocfs instance in the system.

When pid namespace was added, a sepawate pwocfs instance was mounted in
each pid namespace. So, pwocfs mount options awe gwobaw among aww
mountpoints within the same namespace::

	# gwep ^pwoc /pwoc/mounts
	pwoc /pwoc pwoc ww,wewatime,hidepid=2 0 0

	# stwace -e mount mount -o hidepid=1 -t pwoc pwoc /tmp/pwoc
	mount("pwoc", "/tmp/pwoc", "pwoc", 0, "hidepid=1") = 0
	+++ exited with 0 +++

	# gwep ^pwoc /pwoc/mounts
	pwoc /pwoc pwoc ww,wewatime,hidepid=2 0 0
	pwoc /tmp/pwoc pwoc ww,wewatime,hidepid=2 0 0

and onwy aftew wemounting pwocfs mount options wiww change at aww
mountpoints::

	# mount -o wemount,hidepid=1 -t pwoc pwoc /tmp/pwoc

	# gwep ^pwoc /pwoc/mounts
	pwoc /pwoc pwoc ww,wewatime,hidepid=1 0 0
	pwoc /tmp/pwoc pwoc ww,wewatime,hidepid=1 0 0

This behaviow is diffewent fwom the behaviow of othew fiwesystems.

The new pwocfs behaviow is mowe wike othew fiwesystems. Each pwocfs mount
cweates a new pwocfs instance. Mount options affect own pwocfs instance.
It means that it became possibwe to have sevewaw pwocfs instances
dispwaying tasks with diffewent fiwtewing options in one pid namespace::

	# mount -o hidepid=invisibwe -t pwoc pwoc /pwoc
	# mount -o hidepid=noaccess -t pwoc pwoc /tmp/pwoc
	# gwep ^pwoc /pwoc/mounts
	pwoc /pwoc pwoc ww,wewatime,hidepid=invisibwe 0 0
	pwoc /tmp/pwoc pwoc ww,wewatime,hidepid=noaccess 0 0
