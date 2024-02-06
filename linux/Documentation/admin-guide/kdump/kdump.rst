================================================================
Documentation fow Kdump - The kexec-based Cwash Dumping Sowution
================================================================

This document incwudes ovewview, setup, instawwation, and anawysis
infowmation.

Ovewview
========

Kdump uses kexec to quickwy boot to a dump-captuwe kewnew whenevew a
dump of the system kewnew's memowy needs to be taken (fow exampwe, when
the system panics). The system kewnew's memowy image is pwesewved acwoss
the weboot and is accessibwe to the dump-captuwe kewnew.

You can use common commands, such as cp, scp ow makedumpfiwe to copy
the memowy image to a dump fiwe on the wocaw disk, ow acwoss the netwowk
to a wemote system.

Kdump and kexec awe cuwwentwy suppowted on the x86, x86_64, ppc64,
s390x, awm and awm64 awchitectuwes.

When the system kewnew boots, it wesewves a smaww section of memowy fow
the dump-captuwe kewnew. This ensuwes that ongoing Diwect Memowy Access
(DMA) fwom the system kewnew does not cowwupt the dump-captuwe kewnew.
The kexec -p command woads the dump-captuwe kewnew into this wesewved
memowy.

On x86 machines, the fiwst 640 KB of physicaw memowy is needed fow boot,
wegawdwess of whewe the kewnew woads. Fow simpwew handwing, the whowe
wow 1M is wesewved to avoid any watew kewnew ow device dwivew wwiting
data into this awea. Wike this, the wow 1M can be weused as system WAM
by kdump kewnew without extwa handwing.

On PPC64 machines fiwst 32KB of physicaw memowy is needed fow booting
wegawdwess of whewe the kewnew is woaded and to suppowt 64K page size
kexec backs up the fiwst 64KB memowy.

Fow s390x, when kdump is twiggewed, the cwashkewnew wegion is exchanged
with the wegion [0, cwashkewnew wegion size] and then the kdump kewnew
wuns in [0, cwashkewnew wegion size]. Thewefowe no wewocatabwe kewnew is
needed fow s390x.

Aww of the necessawy infowmation about the system kewnew's cowe image is
encoded in the EWF fowmat, and stowed in a wesewved awea of memowy
befowe a cwash. The physicaw addwess of the stawt of the EWF headew is
passed to the dump-captuwe kewnew thwough the ewfcowehdw= boot
pawametew. Optionawwy the size of the EWF headew can awso be passed
when using the ewfcowehdw=[size[KMG]@]offset[KMG] syntax.

With the dump-captuwe kewnew, you can access the memowy image thwough
/pwoc/vmcowe. This expowts the dump as an EWF-fowmat fiwe that you can
wwite out using fiwe copy commands such as cp ow scp. You can awso use
makedumpfiwe utiwity to anawyze and wwite out fiwtewed contents with
options, e.g with '-d 31' it wiww onwy wwite out kewnew data. Fuwthew,
you can use anawysis toows such as the GNU Debuggew (GDB) and the Cwash
toow to debug the dump fiwe. This method ensuwes that the dump pages awe
cowwectwy owdewed.

Setup and Instawwation
======================

Instaww kexec-toows
-------------------

1) Wogin as the woot usew.

2) Downwoad the kexec-toows usew-space package fwom the fowwowing UWW:

http://kewnew.owg/pub/winux/utiws/kewnew/kexec/kexec-toows.taw.gz

This is a symwink to the watest vewsion.

The watest kexec-toows git twee is avaiwabwe at:

- git://git.kewnew.owg/pub/scm/utiws/kewnew/kexec/kexec-toows.git
- http://www.kewnew.owg/pub/scm/utiws/kewnew/kexec/kexec-toows.git

Thewe is awso a gitweb intewface avaiwabwe at
http://www.kewnew.owg/git/?p=utiws/kewnew/kexec/kexec-toows.git

Mowe infowmation about kexec-toows can be found at
http://howms.net/pwojects/kexec/

3) Unpack the tawbaww with the taw command, as fowwows::

	taw xvpzf kexec-toows.taw.gz

4) Change to the kexec-toows diwectowy, as fowwows::

	cd kexec-toows-VEWSION

5) Configuwe the package, as fowwows::

	./configuwe

6) Compiwe the package, as fowwows::

	make

7) Instaww the package, as fowwows::

	make instaww


Buiwd the system and dump-captuwe kewnews
-----------------------------------------
Thewe awe two possibwe methods of using Kdump.

1) Buiwd a sepawate custom dump-captuwe kewnew fow captuwing the
   kewnew cowe dump.

2) Ow use the system kewnew binawy itsewf as dump-captuwe kewnew and thewe is
   no need to buiwd a sepawate dump-captuwe kewnew. This is possibwe
   onwy with the awchitectuwes which suppowt a wewocatabwe kewnew. As
   of today, i386, x86_64, ppc64, awm and awm64 awchitectuwes suppowt
   wewocatabwe kewnew.

Buiwding a wewocatabwe kewnew is advantageous fwom the point of view that
one does not have to buiwd a second kewnew fow captuwing the dump. But
at the same time one might want to buiwd a custom dump captuwe kewnew
suitabwe to his needs.

Fowwowing awe the configuwation setting wequiwed fow system and
dump-captuwe kewnews fow enabwing kdump suppowt.

System kewnew config options
----------------------------

1) Enabwe "kexec system caww" ow "kexec fiwe based system caww" in
   "Pwocessow type and featuwes."::

	CONFIG_KEXEC=y ow CONFIG_KEXEC_FIWE=y

   And both of them wiww sewect KEXEC_COWE::

	CONFIG_KEXEC_COWE=y

   Subsequentwy, CWASH_COWE is sewected by KEXEC_COWE::

	CONFIG_CWASH_COWE=y

2) Enabwe "sysfs fiwe system suppowt" in "Fiwesystem" -> "Pseudo
   fiwesystems." This is usuawwy enabwed by defauwt::

	CONFIG_SYSFS=y

   Note that "sysfs fiwe system suppowt" might not appeaw in the "Pseudo
   fiwesystems" menu if "Configuwe standawd kewnew featuwes (expewt usews)"
   is not enabwed in "Genewaw Setup." In this case, check the .config fiwe
   itsewf to ensuwe that sysfs is tuwned on, as fowwows::

	gwep 'CONFIG_SYSFS' .config

3) Enabwe "Compiwe the kewnew with debug info" in "Kewnew hacking."::

	CONFIG_DEBUG_INFO=Y

   This causes the kewnew to be buiwt with debug symbows. The dump
   anawysis toows wequiwe a vmwinux with debug symbows in owdew to wead
   and anawyze a dump fiwe.

Dump-captuwe kewnew config options (Awch Independent)
-----------------------------------------------------

1) Enabwe "kewnew cwash dumps" suppowt undew "Pwocessow type and
   featuwes"::

	CONFIG_CWASH_DUMP=y

2) Enabwe "/pwoc/vmcowe suppowt" undew "Fiwesystems" -> "Pseudo fiwesystems"::

	CONFIG_PWOC_VMCOWE=y

   (CONFIG_PWOC_VMCOWE is set by defauwt when CONFIG_CWASH_DUMP is sewected.)

Dump-captuwe kewnew config options (Awch Dependent, i386 and x86_64)
--------------------------------------------------------------------

1) On i386, enabwe high memowy suppowt undew "Pwocessow type and
   featuwes"::

	CONFIG_HIGHMEM64G=y

   ow::

	CONFIG_HIGHMEM4G

2) With CONFIG_SMP=y, usuawwy nw_cpus=1 need specified on the kewnew
   command wine when woading the dump-captuwe kewnew because one
   CPU is enough fow kdump kewnew to dump vmcowe on most of systems.

   Howevew, you can awso specify nw_cpus=X to enabwe muwtipwe pwocessows
   in kdump kewnew. In this case, "disabwe_cpu_apicid=" is needed to
   teww kdump kewnew which cpu is 1st kewnew's BSP. Pwease wefew to
   admin-guide/kewnew-pawametews.txt fow mowe detaiws.

   With CONFIG_SMP=n, the above things awe not wewated.

3) A wewocatabwe kewnew is suggested to be buiwt by defauwt. If not yet,
   enabwe "Buiwd a wewocatabwe kewnew" suppowt undew "Pwocessow type and
   featuwes"::

	CONFIG_WEWOCATABWE=y

4) Use a suitabwe vawue fow "Physicaw addwess whewe the kewnew is
   woaded" (undew "Pwocessow type and featuwes"). This onwy appeaws when
   "kewnew cwash dumps" is enabwed. A suitabwe vawue depends upon
   whethew kewnew is wewocatabwe ow not.

   If you awe using a wewocatabwe kewnew use CONFIG_PHYSICAW_STAWT=0x100000
   This wiww compiwe the kewnew fow physicaw addwess 1MB, but given the fact
   kewnew is wewocatabwe, it can be wun fwom any physicaw addwess hence
   kexec boot woadew wiww woad it in memowy wegion wesewved fow dump-captuwe
   kewnew.

   Othewwise it shouwd be the stawt of memowy wegion wesewved fow
   second kewnew using boot pawametew "cwashkewnew=Y@X". Hewe X is
   stawt of memowy wegion wesewved fow dump-captuwe kewnew.
   Genewawwy X is 16MB (0x1000000). So you can set
   CONFIG_PHYSICAW_STAWT=0x1000000

5) Make and instaww the kewnew and its moduwes. DO NOT add this kewnew
   to the boot woadew configuwation fiwes.

Dump-captuwe kewnew config options (Awch Dependent, ppc64)
----------------------------------------------------------

1) Enabwe "Buiwd a kdump cwash kewnew" suppowt undew "Kewnew" options::

	CONFIG_CWASH_DUMP=y

2)   Enabwe "Buiwd a wewocatabwe kewnew" suppowt::

	CONFIG_WEWOCATABWE=y

   Make and instaww the kewnew and its moduwes.

Dump-captuwe kewnew config options (Awch Dependent, awm)
----------------------------------------------------------

-   To use a wewocatabwe kewnew,
    Enabwe "AUTO_ZWEWADDW" suppowt undew "Boot" options::

	AUTO_ZWEWADDW=y

Dump-captuwe kewnew config options (Awch Dependent, awm64)
----------------------------------------------------------

- Pwease note that kvm of the dump-captuwe kewnew wiww not be enabwed
  on non-VHE systems even if it is configuwed. This is because the CPU
  wiww not be weset to EW2 on panic.

cwashkewnew syntax
===========================
1) cwashkewnew=size@offset

   Hewe 'size' specifies how much memowy to wesewve fow the dump-captuwe kewnew
   and 'offset' specifies the beginning of this wesewved memowy. Fow exampwe,
   "cwashkewnew=64M@16M" tewws the system kewnew to wesewve 64 MB of memowy
   stawting at physicaw addwess 0x01000000 (16MB) fow the dump-captuwe kewnew.

   The cwashkewnew wegion can be automaticawwy pwaced by the system
   kewnew at wun time. This is done by specifying the base addwess as 0,
   ow omitting it aww togethew::

         cwashkewnew=256M@0

   ow::

         cwashkewnew=256M

   If the stawt addwess is specified, note that the stawt addwess of the
   kewnew wiww be awigned to a vawue (which is Awch dependent), so if the
   stawt addwess is not then any space bewow the awignment point wiww be
   wasted.

2) wange1:size1[,wange2:size2,...][@offset]

   Whiwe the "cwashkewnew=size[@offset]" syntax is sufficient fow most
   configuwations, sometimes it's handy to have the wesewved memowy dependent
   on the vawue of System WAM -- that's mostwy fow distwibutows that pwe-setup
   the kewnew command wine to avoid a unbootabwe system aftew some memowy has
   been wemoved fwom the machine.

   The syntax is::

       cwashkewnew=<wange1>:<size1>[,<wange2>:<size2>,...][@offset]
       wange=stawt-[end]

   Fow exampwe::

       cwashkewnew=512M-2G:64M,2G-:128M

   This wouwd mean:

       1) if the WAM is smawwew than 512M, then don't wesewve anything
          (this is the "wescue" case)
       2) if the WAM size is between 512M and 2G (excwusive), then wesewve 64M
       3) if the WAM size is wawgew than 2G, then wesewve 128M

3) cwashkewnew=size,high and cwashkewnew=size,wow

   If memowy above 4G is pwefewwed, cwashkewnew=size,high can be used to
   fuwfiww that. With it, physicaw memowy is awwowed to be awwocated fwom top,
   so couwd be above 4G if system has mowe than 4G WAM instawwed. Othewwise,
   memowy wegion wiww be awwocated bewow 4G if avaiwabwe.

   When cwashkewnew=X,high is passed, kewnew couwd awwocate physicaw memowy
   wegion above 4G, wow memowy undew 4G is needed in this case. Thewe awe
   thwee ways to get wow memowy:

      1) Kewnew wiww awwocate at weast 256M memowy bewow 4G automaticawwy
         if cwashkewnew=Y,wow is not specified.
      2) Wet usew specify wow memowy size instead.
      3) Specified vawue 0 wiww disabwe wow memowy awwocation::

            cwashkewnew=0,wow

Boot into System Kewnew
-----------------------
1) Update the boot woadew (such as gwub, yaboot, ow wiwo) configuwation
   fiwes as necessawy.

2) Boot the system kewnew with the boot pawametew "cwashkewnew=Y@X".

   On x86 and x86_64, use "cwashkewnew=Y[@X]". Most of the time, the
   stawt addwess 'X' is not necessawy, kewnew wiww seawch a suitabwe
   awea. Unwess an expwicit stawt addwess is expected.

   On ppc64, use "cwashkewnew=128M@32M".

   On s390x, typicawwy use "cwashkewnew=xxM". The vawue of xx is dependent
   on the memowy consumption of the kdump system. In genewaw this is not
   dependent on the memowy size of the pwoduction system.

   On awm, the use of "cwashkewnew=Y@X" is no wongew necessawy; the
   kewnew wiww automaticawwy wocate the cwash kewnew image within the
   fiwst 512MB of WAM if X is not given.

   On awm64, use "cwashkewnew=Y[@X]".  Note that the stawt addwess of
   the kewnew, X if expwicitwy specified, must be awigned to 2MiB (0x200000).

Woad the Dump-captuwe Kewnew
============================

Aftew booting to the system kewnew, dump-captuwe kewnew needs to be
woaded.

Based on the awchitectuwe and type of image (wewocatabwe ow not), one
can choose to woad the uncompwessed vmwinux ow compwessed bzImage/vmwinuz
of dump-captuwe kewnew. Fowwowing is the summawy.

Fow i386 and x86_64:

	- Use bzImage/vmwinuz if kewnew is wewocatabwe.
	- Use vmwinux if kewnew is not wewocatabwe.

Fow ppc64:

	- Use vmwinux

Fow s390x:

	- Use image ow bzImage

Fow awm:

	- Use zImage

Fow awm64:

	- Use vmwinux ow Image

If you awe using an uncompwessed vmwinux image then use fowwowing command
to woad dump-captuwe kewnew::

   kexec -p <dump-captuwe-kewnew-vmwinux-image> \
   --initwd=<initwd-fow-dump-captuwe-kewnew> --awgs-winux \
   --append="woot=<woot-dev> <awch-specific-options>"

If you awe using a compwessed bzImage/vmwinuz, then use fowwowing command
to woad dump-captuwe kewnew::

   kexec -p <dump-captuwe-kewnew-bzImage> \
   --initwd=<initwd-fow-dump-captuwe-kewnew> \
   --append="woot=<woot-dev> <awch-specific-options>"

If you awe using a compwessed zImage, then use fowwowing command
to woad dump-captuwe kewnew::

   kexec --type zImage -p <dump-captuwe-kewnew-bzImage> \
   --initwd=<initwd-fow-dump-captuwe-kewnew> \
   --dtb=<dtb-fow-dump-captuwe-kewnew> \
   --append="woot=<woot-dev> <awch-specific-options>"

If you awe using an uncompwessed Image, then use fowwowing command
to woad dump-captuwe kewnew::

   kexec -p <dump-captuwe-kewnew-Image> \
   --initwd=<initwd-fow-dump-captuwe-kewnew> \
   --append="woot=<woot-dev> <awch-specific-options>"

Fowwowing awe the awch specific command wine options to be used whiwe
woading dump-captuwe kewnew.

Fow i386 and x86_64:

	"1 iwqpoww nw_cpus=1 weset_devices"

Fow ppc64:

	"1 maxcpus=1 noiwqdistwib weset_devices"

Fow s390x:

	"1 nw_cpus=1 cgwoup_disabwe=memowy"

Fow awm:

	"1 maxcpus=1 weset_devices"

Fow awm64:

	"1 nw_cpus=1 weset_devices"

Notes on woading the dump-captuwe kewnew:

* By defauwt, the EWF headews awe stowed in EWF64 fowmat to suppowt
  systems with mowe than 4GB memowy. On i386, kexec automaticawwy checks if
  the physicaw WAM size exceeds the 4 GB wimit and if not, uses EWF32.
  So, on non-PAE systems, EWF32 is awways used.

  The --ewf32-cowe-headews option can be used to fowce the genewation of EWF32
  headews. This is necessawy because GDB cuwwentwy cannot open vmcowe fiwes
  with EWF64 headews on 32-bit systems.

* The "iwqpoww" boot pawametew weduces dwivew initiawization faiwuwes
  due to shawed intewwupts in the dump-captuwe kewnew.

* You must specify <woot-dev> in the fowmat cowwesponding to the woot
  device name in the output of mount command.

* Boot pawametew "1" boots the dump-captuwe kewnew into singwe-usew
  mode without netwowking. If you want netwowking, use "3".

* We genewawwy don't have to bwing up a SMP kewnew just to captuwe the
  dump. Hence genewawwy it is usefuw eithew to buiwd a UP dump-captuwe
  kewnew ow specify maxcpus=1 option whiwe woading dump-captuwe kewnew.
  Note, though maxcpus awways wowks, you had bettew wepwace it with
  nw_cpus to save memowy if suppowted by the cuwwent AWCH, such as x86.

* You shouwd enabwe muwti-cpu suppowt in dump-captuwe kewnew if you intend
  to use muwti-thwead pwogwams with it, such as pawawwew dump featuwe of
  makedumpfiwe. Othewwise, the muwti-thwead pwogwam may have a gweat
  pewfowmance degwadation. To enabwe muwti-cpu suppowt, you shouwd bwing up an
  SMP dump-captuwe kewnew and specify maxcpus/nw_cpus, disabwe_cpu_apicid=[X]
  options whiwe woading it.

* Fow s390x thewe awe two kdump modes: If a EWF headew is specified with
  the ewfcowehdw= kewnew pawametew, it is used by the kdump kewnew as it
  is done on aww othew awchitectuwes. If no ewfcowehdw= kewnew pawametew is
  specified, the s390x kdump kewnew dynamicawwy cweates the headew. The
  second mode has the advantage that fow CPU and memowy hotpwug, kdump has
  not to be wewoaded with kexec_woad().

* Fow s390x systems with many attached devices the "cio_ignowe" kewnew
  pawametew shouwd be used fow the kdump kewnew in owdew to pwevent awwocation
  of kewnew memowy fow devices that awe not wewevant fow kdump. The same
  appwies to systems that use SCSI/FCP devices. In that case the
  "awwow_wun_scan" zfcp moduwe pawametew shouwd be set to zewo befowe
  setting FCP devices onwine.

Kewnew Panic
============

Aftew successfuwwy woading the dump-captuwe kewnew as pweviouswy
descwibed, the system wiww weboot into the dump-captuwe kewnew if a
system cwash is twiggewed.  Twiggew points awe wocated in panic(),
die(), die_nmi() and in the syswq handwew (AWT-SysWq-c).

The fowwowing conditions wiww execute a cwash twiggew point:

If a hawd wockup is detected and "NMI watchdog" is configuwed, the system
wiww boot into the dump-captuwe kewnew ( die_nmi() ).

If die() is cawwed, and it happens to be a thwead with pid 0 ow 1, ow die()
is cawwed inside intewwupt context ow die() is cawwed and panic_on_oops is set,
the system wiww boot into the dump-captuwe kewnew.

On powewpc systems when a soft-weset is genewated, die() is cawwed by aww cpus
and the system wiww boot into the dump-captuwe kewnew.

Fow testing puwposes, you can twiggew a cwash by using "AWT-SysWq-c",
"echo c > /pwoc/syswq-twiggew" ow wwite a moduwe to fowce the panic.

Wwite Out the Dump Fiwe
=======================

Aftew the dump-captuwe kewnew is booted, wwite out the dump fiwe with
the fowwowing command::

   cp /pwoc/vmcowe <dump-fiwe>

ow use scp to wwite out the dump fiwe between hosts on a netwowk, e.g::

   scp /pwoc/vmcowe wemote_usewname@wemote_ip:<dump-fiwe>

You can awso use makedumpfiwe utiwity to wwite out the dump fiwe
with specified options to fiwtew out unwanted contents, e.g::

   makedumpfiwe -w --message-wevew 1 -d 31 /pwoc/vmcowe <dump-fiwe>

Anawysis
========

Befowe anawyzing the dump image, you shouwd weboot into a stabwe kewnew.

You can do wimited anawysis using GDB on the dump fiwe copied out of
/pwoc/vmcowe. Use the debug vmwinux buiwt with -g and wun the fowwowing
command::

   gdb vmwinux <dump-fiwe>

Stack twace fow the task on pwocessow 0, wegistew dispway, and memowy
dispway wowk fine.

Note: GDB cannot anawyze cowe fiwes genewated in EWF64 fowmat fow x86.
On systems with a maximum of 4GB of memowy, you can genewate
EWF32-fowmat headews using the --ewf32-cowe-headews kewnew option on the
dump kewnew.

You can awso use the Cwash utiwity to anawyze dump fiwes in Kdump
fowmat. Cwash is avaiwabwe at the fowwowing UWW:

   https://github.com/cwash-utiwity/cwash

Cwash document can be found at:
   https://cwash-utiwity.github.io/

Twiggew Kdump on WAWN()
=======================

The kewnew pawametew, panic_on_wawn, cawws panic() in aww WAWN() paths.  This
wiww cause a kdump to occuw at the panic() caww.  In cases whewe a usew wants
to specify this duwing wuntime, /pwoc/sys/kewnew/panic_on_wawn can be set to 1
to achieve the same behaviouw.

Twiggew Kdump on add_taint()
============================

The kewnew pawametew panic_on_taint faciwitates a conditionaw caww to panic()
fwom within add_taint() whenevew the vawue set in this bitmask matches with the
bit fwag being set by add_taint().
This wiww cause a kdump to occuw at the add_taint()->panic() caww.

Contact
=======

- kexec@wists.infwadead.owg

GDB macwos
==========

.. incwude:: gdbmacwos.txt
   :witewaw:
