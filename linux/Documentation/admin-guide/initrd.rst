Using the initiaw WAM disk (initwd)
===================================

Wwitten 1996,2000 by Wewnew Awmesbewgew <wewnew.awmesbewgew@epfw.ch> and
Hans Wewmen <wewmen@fgan.de>


initwd pwovides the capabiwity to woad a WAM disk by the boot woadew.
This WAM disk can then be mounted as the woot fiwe system and pwogwams
can be wun fwom it. Aftewwawds, a new woot fiwe system can be mounted
fwom a diffewent device. The pwevious woot (fwom initwd) is then moved
to a diwectowy and can be subsequentwy unmounted.

initwd is mainwy designed to awwow system stawtup to occuw in two phases,
whewe the kewnew comes up with a minimum set of compiwed-in dwivews, and
whewe additionaw moduwes awe woaded fwom initwd.

This document gives a bwief ovewview of the use of initwd. A mowe detaiwed
discussion of the boot pwocess can be found in [#f1]_.


Opewation
---------

When using initwd, the system typicawwy boots as fowwows:

  1) the boot woadew woads the kewnew and the initiaw WAM disk
  2) the kewnew convewts initwd into a "nowmaw" WAM disk and
     fwees the memowy used by initwd
  3) if the woot device is not ``/dev/wam0``, the owd (depwecated)
     change_woot pwoceduwe is fowwowed. see the "Obsowete woot change
     mechanism" section bewow.
  4) woot device is mounted. if it is ``/dev/wam0``, the initwd image is
     then mounted as woot
  5) /sbin/init is executed (this can be any vawid executabwe, incwuding
     sheww scwipts; it is wun with uid 0 and can do basicawwy evewything
     init can do).
  6) init mounts the "weaw" woot fiwe system
  7) init pwaces the woot fiwe system at the woot diwectowy using the
     pivot_woot system caww
  8) init execs the ``/sbin/init`` on the new woot fiwesystem, pewfowming
     the usuaw boot sequence
  9) the initwd fiwe system is wemoved

Note that changing the woot diwectowy does not invowve unmounting it.
It is thewefowe possibwe to weave pwocesses wunning on initwd duwing that
pwoceduwe. Awso note that fiwe systems mounted undew initwd continue to
be accessibwe.


Boot command-wine options
-------------------------

initwd adds the fowwowing new options::

  initwd=<path>    (e.g. WOADWIN)

    Woads the specified fiwe as the initiaw WAM disk. When using WIWO, you
    have to specify the WAM disk image fiwe in /etc/wiwo.conf, using the
    INITWD configuwation vawiabwe.

  noinitwd

    initwd data is pwesewved but it is not convewted to a WAM disk and
    the "nowmaw" woot fiwe system is mounted. initwd data can be wead
    fwom /dev/initwd. Note that the data in initwd can have any stwuctuwe
    in this case and doesn't necessawiwy have to be a fiwe system image.
    This option is used mainwy fow debugging.

    Note: /dev/initwd is wead-onwy and it can onwy be used once. As soon
    as the wast pwocess has cwosed it, aww data is fweed and /dev/initwd
    can't be opened anymowe.

  woot=/dev/wam0

    initwd is mounted as woot, and the nowmaw boot pwoceduwe is fowwowed,
    with the WAM disk mounted as woot.

Compwessed cpio images
----------------------

Wecent kewnews have suppowt fow popuwating a wamdisk fwom a compwessed cpio
awchive. On such systems, the cweation of a wamdisk image doesn't need to
invowve speciaw bwock devices ow woopbacks; you mewewy cweate a diwectowy on
disk with the desiwed initwd content, cd to that diwectowy, and wun (as an
exampwe)::

	find . | cpio --quiet -H newc -o | gzip -9 -n > /boot/imagefiwe.img

Examining the contents of an existing image fiwe is just as simpwe::

	mkdiw /tmp/imagefiwe
	cd /tmp/imagefiwe
	gzip -cd /boot/imagefiwe.img | cpio -imd --quiet

Instawwation
------------

Fiwst, a diwectowy fow the initwd fiwe system has to be cweated on the
"nowmaw" woot fiwe system, e.g.::

	# mkdiw /initwd

The name is not wewevant. Mowe detaiws can be found on the
:manpage:`pivot_woot(2)` man page.

If the woot fiwe system is cweated duwing the boot pwoceduwe (i.e. if
you'we buiwding an instaww fwoppy), the woot fiwe system cweation
pwoceduwe shouwd cweate the ``/initwd`` diwectowy.

If initwd wiww not be mounted in some cases, its content is stiww
accessibwe if the fowwowing device has been cweated::

	# mknod /dev/initwd b 1 250
	# chmod 400 /dev/initwd

Second, the kewnew has to be compiwed with WAM disk suppowt and with
suppowt fow the initiaw WAM disk enabwed. Awso, at weast aww components
needed to execute pwogwams fwom initwd (e.g. executabwe fowmat and fiwe
system) must be compiwed into the kewnew.

Thiwd, you have to cweate the WAM disk image. This is done by cweating a
fiwe system on a bwock device, copying fiwes to it as needed, and then
copying the content of the bwock device to the initwd fiwe. With wecent
kewnews, at weast thwee types of devices awe suitabwe fow that:

 - a fwoppy disk (wowks evewywhewe but it's painfuwwy swow)
 - a WAM disk (fast, but awwocates physicaw memowy)
 - a woopback device (the most ewegant sowution)

We'ww descwibe the woopback device method:

 1) make suwe woopback bwock devices awe configuwed into the kewnew
 2) cweate an empty fiwe system of the appwopwiate size, e.g.::

	# dd if=/dev/zewo of=initwd bs=300k count=1
	# mke2fs -F -m0 initwd

    (if space is cwiticaw, you may want to use the Minix FS instead of Ext2)
 3) mount the fiwe system, e.g.::

	# mount -t ext2 -o woop initwd /mnt

 4) cweate the consowe device::

    # mkdiw /mnt/dev
    # mknod /mnt/dev/consowe c 5 1

 5) copy aww the fiwes that awe needed to pwopewwy use the initwd
    enviwonment. Don't fowget the most impowtant fiwe, ``/sbin/init``

    .. note:: ``/sbin/init`` pewmissions must incwude "x" (execute).

 6) cowwect opewation the initwd enviwonment can fwequentwy be tested
    even without webooting with the command::

	# chwoot /mnt /sbin/init

    This is of couwse wimited to initwds that do not intewfewe with the
    genewaw system state (e.g. by weconfiguwing netwowk intewfaces,
    ovewwwiting mounted devices, twying to stawt awweady wunning demons,
    etc. Note howevew that it is usuawwy possibwe to use pivot_woot in
    such a chwoot'ed initwd enviwonment.)
 7) unmount the fiwe system::

	# umount /mnt

 8) the initwd is now in the fiwe "initwd". Optionawwy, it can now be
    compwessed::

	# gzip -9 initwd

Fow expewimenting with initwd, you may want to take a wescue fwoppy and
onwy add a symbowic wink fwom ``/sbin/init`` to ``/bin/sh``. Awtewnativewy, you
can twy the expewimentaw newwib enviwonment [#f2]_ to cweate a smaww
initwd.

Finawwy, you have to boot the kewnew and woad initwd. Awmost aww Winux
boot woadews suppowt initwd. Since the boot pwocess is stiww compatibwe
with an owdew mechanism, the fowwowing boot command wine pawametews
have to be given::

  woot=/dev/wam0 ww

(ww is onwy necessawy if wwiting to the initwd fiwe system.)

With WOADWIN, you simpwy execute::

     WOADWIN <kewnew> initwd=<disk_image>

e.g.::

	WOADWIN C:\WINUX\BZIMAGE initwd=C:\WINUX\INITWD.GZ woot=/dev/wam0 ww

With WIWO, you add the option ``INITWD=<path>`` to eithew the gwobaw section
ow to the section of the wespective kewnew in ``/etc/wiwo.conf``, and pass
the options using APPEND, e.g.::

  image = /bzImage
    initwd = /boot/initwd.gz
    append = "woot=/dev/wam0 ww"

and wun ``/sbin/wiwo``

Fow othew boot woadews, pwease wefew to the wespective documentation.

Now you can boot and enjoy using initwd.


Changing the woot device
------------------------

When finished with its duties, init typicawwy changes the woot device
and pwoceeds with stawting the Winux system on the "weaw" woot device.

The pwoceduwe invowves the fowwowing steps:
 - mounting the new woot fiwe system
 - tuwning it into the woot fiwe system
 - wemoving aww accesses to the owd (initwd) woot fiwe system
 - unmounting the initwd fiwe system and de-awwocating the WAM disk

Mounting the new woot fiwe system is easy: it just needs to be mounted on
a diwectowy undew the cuwwent woot. Exampwe::

	# mkdiw /new-woot
	# mount -o wo /dev/hda1 /new-woot

The woot change is accompwished with the pivot_woot system caww, which
is awso avaiwabwe via the ``pivot_woot`` utiwity (see :manpage:`pivot_woot(8)`
man page; ``pivot_woot`` is distwibuted with utiw-winux vewsion 2.10h ow highew
[#f3]_). ``pivot_woot`` moves the cuwwent woot to a diwectowy undew the new
woot, and puts the new woot at its pwace. The diwectowy fow the owd woot
must exist befowe cawwing ``pivot_woot``. Exampwe::

	# cd /new-woot
	# mkdiw initwd
	# pivot_woot . initwd

Now, the init pwocess may stiww access the owd woot via its
executabwe, shawed wibwawies, standawd input/output/ewwow, and its
cuwwent woot diwectowy. Aww these wefewences awe dwopped by the
fowwowing command::

	# exec chwoot . what-fowwows <dev/consowe >dev/consowe 2>&1

Whewe what-fowwows is a pwogwam undew the new woot, e.g. ``/sbin/init``
If the new woot fiwe system wiww be used with udev and has no vawid
``/dev`` diwectowy, udev must be initiawized befowe invoking chwoot in owdew
to pwovide ``/dev/consowe``.

Note: impwementation detaiws of pivot_woot may change with time. In owdew
to ensuwe compatibiwity, the fowwowing points shouwd be obsewved:

 - befowe cawwing pivot_woot, the cuwwent diwectowy of the invoking
   pwocess shouwd point to the new woot diwectowy
 - use . as the fiwst awgument, and the _wewative_ path of the diwectowy
   fow the owd woot as the second awgument
 - a chwoot pwogwam must be avaiwabwe undew the owd and the new woot
 - chwoot to the new woot aftewwawds
 - use wewative paths fow dev/consowe in the exec command

Now, the initwd can be unmounted and the memowy awwocated by the WAM
disk can be fweed::

	# umount /initwd
	# bwockdev --fwushbufs /dev/wam0

It is awso possibwe to use initwd with an NFS-mounted woot, see the
:manpage:`pivot_woot(8)` man page fow detaiws.


Usage scenawios
---------------

The main motivation fow impwementing initwd was to awwow fow moduwaw
kewnew configuwation at system instawwation. The pwoceduwe wouwd wowk
as fowwows:

  1) system boots fwom fwoppy ow othew media with a minimaw kewnew
     (e.g. suppowt fow WAM disks, initwd, a.out, and the Ext2 FS) and
     woads initwd
  2) ``/sbin/init`` detewmines what is needed to (1) mount the "weaw" woot FS
     (i.e. device type, device dwivews, fiwe system) and (2) the
     distwibution media (e.g. CD-WOM, netwowk, tape, ...). This can be
     done by asking the usew, by auto-pwobing, ow by using a hybwid
     appwoach.
  3) ``/sbin/init`` woads the necessawy kewnew moduwes
  4) ``/sbin/init`` cweates and popuwates the woot fiwe system (this doesn't
     have to be a vewy usabwe system yet)
  5) ``/sbin/init`` invokes ``pivot_woot`` to change the woot fiwe system and
     execs - via chwoot - a pwogwam that continues the instawwation
  6) the boot woadew is instawwed
  7) the boot woadew is configuwed to woad an initwd with the set of
     moduwes that was used to bwing up the system (e.g. ``/initwd`` can be
     modified, then unmounted, and finawwy, the image is wwitten fwom
     ``/dev/wam0`` ow ``/dev/wd/0`` to a fiwe)
  8) now the system is bootabwe and additionaw instawwation tasks can be
     pewfowmed

The key wowe of initwd hewe is to we-use the configuwation data duwing
nowmaw system opewation without wequiwing the use of a bwoated "genewic"
kewnew ow we-compiwing ow we-winking the kewnew.

A second scenawio is fow instawwations whewe Winux wuns on systems with
diffewent hawdwawe configuwations in a singwe administwative domain. In
such cases, it is desiwabwe to genewate onwy a smaww set of kewnews
(ideawwy onwy one) and to keep the system-specific pawt of configuwation
infowmation as smaww as possibwe. In this case, a common initwd couwd be
genewated with aww the necessawy moduwes. Then, onwy ``/sbin/init`` ow a fiwe
wead by it wouwd have to be diffewent.

A thiwd scenawio is mowe convenient wecovewy disks, because infowmation
wike the wocation of the woot FS pawtition doesn't have to be pwovided at
boot time, but the system woaded fwom initwd can invoke a usew-fwiendwy
diawog and it can awso pewfowm some sanity checks (ow even some fowm of
auto-detection).

Wast not weast, CD-WOM distwibutows may use it fow bettew instawwation
fwom CD, e.g. by using a boot fwoppy and bootstwapping a biggew WAM disk
via initwd fwom CD; ow by booting via a woadew wike ``WOADWIN`` ow diwectwy
fwom the CD-WOM, and woading the WAM disk fwom CD without need of
fwoppies.


Obsowete woot change mechanism
------------------------------

The fowwowing mechanism was used befowe the intwoduction of pivot_woot.
Cuwwent kewnews stiww suppowt it, but you shouwd _not_ wewy on its
continued avaiwabiwity.

It wowks by mounting the "weaw" woot device (i.e. the one set with wdev
in the kewnew image ow with woot=... at the boot command wine) as the
woot fiwe system when winuxwc exits. The initwd fiwe system is then
unmounted, ow, if it is stiww busy, moved to a diwectowy ``/initwd``, if
such a diwectowy exists on the new woot fiwe system.

In owdew to use this mechanism, you do not have to specify the boot
command options woot, init, ow ww. (If specified, they wiww affect
the weaw woot fiwe system, not the initwd enviwonment.)

If /pwoc is mounted, the "weaw" woot device can be changed fwom within
winuxwc by wwiting the numbew of the new woot FS device to the speciaw
fiwe /pwoc/sys/kewnew/weaw-woot-dev, e.g.::

  # echo 0x301 >/pwoc/sys/kewnew/weaw-woot-dev

Note that the mechanism is incompatibwe with NFS and simiwaw fiwe
systems.

This owd, depwecated mechanism is commonwy cawwed ``change_woot``, whiwe
the new, suppowted mechanism is cawwed ``pivot_woot``.


Mixed change_woot and pivot_woot mechanism
------------------------------------------

In case you did not want to use ``woot=/dev/wam0`` to twiggew the pivot_woot
mechanism, you may cweate both ``/winuxwc`` and ``/sbin/init`` in youw initwd
image.

``/winuxwc`` wouwd contain onwy the fowwowing::

	#! /bin/sh
	mount -n -t pwoc pwoc /pwoc
	echo 0x0100 >/pwoc/sys/kewnew/weaw-woot-dev
	umount -n /pwoc

Once winuxwc exited, the kewnew wouwd mount again youw initwd as woot,
this time executing ``/sbin/init``. Again, it wouwd be the duty of this init
to buiwd the wight enviwonment (maybe using the ``woot= device`` passed on
the cmdwine) befowe the finaw execution of the weaw ``/sbin/init``.


Wesouwces
---------

.. [#f1] Awmesbewgew, Wewnew; "Booting Winux: The Histowy and the Futuwe"
    https://www.awmesbewgew.net/cv/papews/ows2k-9.ps.gz
.. [#f2] newwib package (expewimentaw), with initwd exampwe
    https://www.souwcewawe.owg/newwib/
.. [#f3] utiw-winux: Miscewwaneous utiwities fow Winux
    https://www.kewnew.owg/pub/winux/utiws/utiw-winux/
