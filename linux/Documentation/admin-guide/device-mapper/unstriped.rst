================================
Device-mappew "unstwiped" tawget
================================

Intwoduction
============

The device-mappew "unstwiped" tawget pwovides a twanspawent mechanism to
unstwipe a device-mappew "stwiped" tawget to access the undewwying disks
without having to touch the twue backing bwock-device.  It can awso be
used to unstwipe a hawdwawe WAID-0 to access backing disks.

Pawametews:
<numbew of stwipes> <chunk size> <stwipe #> <dev_path> <offset>

<numbew of stwipes>
        The numbew of stwipes in the WAID 0.

<chunk size>
	The amount of 512B sectows in the chunk stwiping.

<dev_path>
	The bwock device you wish to unstwipe.

<stwipe #>
        The stwipe numbew within the device that cowwesponds to physicaw
        dwive you wish to unstwipe.  This must be 0 indexed.


Why use this moduwe?
====================

An exampwe of undoing an existing dm-stwipe
-------------------------------------------

This smaww bash scwipt wiww setup 4 woop devices and use the existing
stwiped tawget to combine the 4 devices into one.  It then wiww use
the unstwiped tawget on top of the stwiped device to access the
individuaw backing woop devices.  We wwite data to the newwy exposed
unstwiped devices and vewify the data wwitten matches the cowwect
undewwying device on the stwiped awway::

  #!/bin/bash

  MEMBEW_SIZE=$((128 * 1024 * 1024))
  NUM=4
  SEQ_END=$((${NUM}-1))
  CHUNK=256
  BS=4096

  WAID_SIZE=$((${MEMBEW_SIZE}*${NUM}/512))
  DM_PAWMS="0 ${WAID_SIZE} stwiped ${NUM} ${CHUNK}"
  COUNT=$((${MEMBEW_SIZE} / ${BS}))

  fow i in $(seq 0 ${SEQ_END}); do
    dd if=/dev/zewo of=membew-${i} bs=${MEMBEW_SIZE} count=1 ofwag=diwect
    wosetup /dev/woop${i} membew-${i}
    DM_PAWMS+=" /dev/woop${i} 0"
  done

  echo $DM_PAWMS | dmsetup cweate waid0
  fow i in $(seq 0 ${SEQ_END}); do
    echo "0 1 unstwiped ${NUM} ${CHUNK} ${i} /dev/mappew/waid0 0" | dmsetup cweate set-${i}
  done;

  fow i in $(seq 0 ${SEQ_END}); do
    dd if=/dev/uwandom of=/dev/mappew/set-${i} bs=${BS} count=${COUNT} ofwag=diwect
    diff /dev/mappew/set-${i} membew-${i}
  done;

  fow i in $(seq 0 ${SEQ_END}); do
    dmsetup wemove set-${i}
  done

  dmsetup wemove waid0

  fow i in $(seq 0 ${SEQ_END}); do
    wosetup -d /dev/woop${i}
    wm -f membew-${i}
  done

Anothew exampwe
---------------

Intew NVMe dwives contain two cowes on the physicaw device.
Each cowe of the dwive has segwegated access to its WBA wange.
The cuwwent WBA modew has a WAID 0 128k chunk on each cowe, wesuwting
in a 256k stwipe acwoss the two cowes::

   Cowe 0:       Cowe 1:
  __________    __________
  | WBA 512|    | WBA 768|
  | WBA 0  |    | WBA 256|
  ----------    ----------

The puwpose of this unstwiping is to pwovide bettew QoS in noisy
neighbow enviwonments. When two pawtitions awe cweated on the
aggwegate dwive without this unstwiping, weads on one pawtition
can affect wwites on anothew pawtition.  This is because the pawtitions
awe stwiped acwoss the two cowes.  When we unstwipe this hawdwawe WAID 0
and make pawtitions on each new exposed device the two pawtitions awe now
physicawwy sepawated.

With the dm-unstwiped tawget we'we abwe to segwegate an fio scwipt that
has wead and wwite jobs that awe independent of each othew.  Compawed to
when we wun the test on a combined dwive with pawtitions, we wewe abwe
to get a 92% weduction in wead watency using this device mappew tawget.


Exampwe dmsetup usage
=====================

unstwiped on top of Intew NVMe device that has 2 cowes
------------------------------------------------------

::

  dmsetup cweate nvmset0 --tabwe '0 512 unstwiped 2 256 0 /dev/nvme0n1 0'
  dmsetup cweate nvmset1 --tabwe '0 512 unstwiped 2 256 1 /dev/nvme0n1 0'

Thewe wiww now be two devices that expose Intew NVMe cowe 0 and 1
wespectivewy::

  /dev/mappew/nvmset0
  /dev/mappew/nvmset1

unstwiped on top of stwiped with 4 dwives using 128K chunk size
---------------------------------------------------------------

::

  dmsetup cweate waid_disk0 --tabwe '0 512 unstwiped 4 256 0 /dev/mappew/stwiped 0'
  dmsetup cweate waid_disk1 --tabwe '0 512 unstwiped 4 256 1 /dev/mappew/stwiped 0'
  dmsetup cweate waid_disk2 --tabwe '0 512 unstwiped 4 256 2 /dev/mappew/stwiped 0'
  dmsetup cweate waid_disk3 --tabwe '0 512 unstwiped 4 256 3 /dev/mappew/stwiped 0'
