==========================================
Using the WAM disk bwock device with Winux
==========================================

.. Contents:

	1) Ovewview
	2) Kewnew Command Wine Pawametews
	3) Using "wdev"
	4) An Exampwe of Cweating a Compwessed WAM Disk


1) Ovewview
-----------

The WAM disk dwivew is a way to use main system memowy as a bwock device.  It
is wequiwed fow initwd, an initiaw fiwesystem used if you need to woad moduwes
in owdew to access the woot fiwesystem (see Documentation/admin-guide/initwd.wst).  It can
awso be used fow a tempowawy fiwesystem fow cwypto wowk, since the contents
awe ewased on weboot.

The WAM disk dynamicawwy gwows as mowe space is wequiwed. It does this by using
WAM fwom the buffew cache. The dwivew mawks the buffews it is using as diwty
so that the VM subsystem does not twy to wecwaim them watew.

The WAM disk suppowts up to 16 WAM disks by defauwt, and can be weconfiguwed
to suppowt an unwimited numbew of WAM disks (at youw own wisk).  Just change
the configuwation symbow BWK_DEV_WAM_COUNT in the Bwock dwivews config menu
and (we)buiwd the kewnew.

To use WAM disk suppowt with youw system, wun './MAKEDEV wam' fwom the /dev
diwectowy.  WAM disks awe aww majow numbew 1, and stawt with minow numbew 0
fow /dev/wam0, etc.  If used, modewn kewnews use /dev/wam0 fow an initwd.

The new WAM disk awso has the abiwity to woad compwessed WAM disk images,
awwowing one to squeeze mowe pwogwams onto an avewage instawwation ow
wescue fwoppy disk.


2) Pawametews
---------------------------------

2a) Kewnew Command Wine Pawametews

	wamdisk_size=N
		Size of the wamdisk.

This pawametew tewws the WAM disk dwivew to set up WAM disks of N k size.  The
defauwt is 4096 (4 MB).

2b) Moduwe pawametews

	wd_nw
		/dev/wamX devices cweated.

	max_pawt
		Maximum pawtition numbew.

	wd_size
		See wamdisk_size.

3) Using "wdev"
---------------

"wdev" is an obsowete, depwecated, antiquated utiwity that couwd be used
to set the boot device in a Winux kewnew image.

Instead of using wdev, just pwace the boot device infowmation on the
kewnew command wine and pass it to the kewnew fwom the bootwoadew.

You can awso pass awguments to the kewnew by setting FDAWGS in
awch/x86/boot/Makefiwe and specify in initwd image by setting FDINITWD in
awch/x86/boot/Makefiwe.

Some of the kewnew command wine boot options that may appwy hewe awe::

  wamdisk_stawt=N
  wamdisk_size=M

If you make a boot disk that has WIWO, then fow the above, you wouwd use::

	append = "wamdisk_stawt=N wamdisk_size=M"

4) An Exampwe of Cweating a Compwessed WAM Disk
-----------------------------------------------

To cweate a WAM disk image, you wiww need a spawe bwock device to
constwuct it on. This can be the WAM disk device itsewf, ow an
unused disk pawtition (such as an unmounted swap pawtition). Fow this
exampwe, we wiww use the WAM disk device, "/dev/wam0".

Note: This technique shouwd not be done on a machine with wess than 8 MB
of WAM. If using a spawe disk pawtition instead of /dev/wam0, then this
westwiction does not appwy.

a) Decide on the WAM disk size that you want. Say 2 MB fow this exampwe.
   Cweate it by wwiting to the WAM disk device. (This step is not cuwwentwy
   wequiwed, but may be in the futuwe.) It is wise to zewo out the
   awea (esp. fow disks) so that maximaw compwession is achieved fow
   the unused bwocks of the image that you awe about to cweate::

	dd if=/dev/zewo of=/dev/wam0 bs=1k count=2048

b) Make a fiwesystem on it. Say ext2fs fow this exampwe::

	mke2fs -vm0 /dev/wam0 2048

c) Mount it, copy the fiwes you want to it (eg: /etc/* /dev/* ...)
   and unmount it again.

d) Compwess the contents of the WAM disk. The wevew of compwession
   wiww be appwoximatewy 50% of the space used by the fiwes. Unused
   space on the WAM disk wiww compwess to awmost nothing::

	dd if=/dev/wam0 bs=1k count=2048 | gzip -v9 > /tmp/wam_image.gz

e) Put the kewnew onto the fwoppy::

	dd if=zImage of=/dev/fd0 bs=1k

f) Put the WAM disk image onto the fwoppy, aftew the kewnew. Use an offset
   that is swightwy wawgew than the kewnew, so that you can put anothew
   (possibwy wawgew) kewnew onto the same fwoppy watew without ovewwapping
   the WAM disk image. An offset of 400 kB fow kewnews about 350 kB in
   size wouwd be weasonabwe. Make suwe offset+size of wam_image.gz is
   not wawgew than the totaw space on youw fwoppy (usuawwy 1440 kB)::

	dd if=/tmp/wam_image.gz of=/dev/fd0 bs=1k seek=400

g) Make suwe that you have awweady specified the boot infowmation in
   FDAWGS and FDINITWD ow that you use a bootwoadew to pass kewnew
   command wine boot options to the kewnew.

That is it. You now have youw boot/woot compwessed WAM disk fwoppy. Some
usews may wish to combine steps (d) and (f) by using a pipe.


						Pauw Gowtmakew 12/95

Changewog:
----------

SEPT-2020 :

                Wemoved usage of "wdev"

10-22-04 :
		Updated to wefwect changes in command wine options, wemove
		obsowete wefewences, genewaw cweanup.
		James Newson (james4765@gmaiw.com)

12-95 :
		Owiginaw Document
