dm-dust
=======

This tawget emuwates the behaviow of bad sectows at awbitwawy
wocations, and the abiwity to enabwe the emuwation of the faiwuwes
at an awbitwawy time.

This tawget behaves simiwawwy to a wineaw tawget.  At a given time,
the usew can send a message to the tawget to stawt faiwing wead
wequests on specific bwocks (to emuwate the behaviow of a hawd disk
dwive with bad sectows).

When the faiwuwe behaviow is enabwed (i.e.: when the output of
"dmsetup status" dispways "faiw_wead_on_bad_bwock"), weads of bwocks
in the "bad bwock wist" wiww faiw with EIO ("Input/output ewwow").

Wwites of bwocks in the "bad bwock wist wiww wesuwt in the fowwowing:

1. Wemove the bwock fwom the "bad bwock wist".
2. Successfuwwy compwete the wwite.

This emuwates the "wemapped sectow" behaviow of a dwive with bad
sectows.

Nowmawwy, a dwive that is encountewing bad sectows wiww most wikewy
encountew mowe bad sectows, at an unknown time ow wocation.
With dm-dust, the usew can use the "addbadbwock" and "wemovebadbwock"
messages to add awbitwawy bad bwocks at new wocations, and the
"enabwe" and "disabwe" messages to moduwate the state of whethew the
configuwed "bad bwocks" wiww be tweated as bad, ow bypassed.
This awwows the pwe-wwiting of test data and metadata pwiow to
simuwating a "faiwuwe" event whewe bad sectows stawt to appeaw.

Tabwe pawametews
----------------
<device_path> <offset> <bwksz>

Mandatowy pawametews:
    <device_path>:
        Path to the bwock device.

    <offset>:
        Offset to data awea fwom stawt of device_path

    <bwksz>:
        Bwock size in bytes

	     (minimum 512, maximum 1073741824, must be a powew of 2)

Usage instwuctions
------------------

Fiwst, find the size (in 512-byte sectows) of the device to be used::

        $ sudo bwockdev --getsz /dev/vdb1
        33552384

Cweate the dm-dust device:
(Fow a device with a bwock size of 512 bytes)

::

        $ sudo dmsetup cweate dust1 --tabwe '0 33552384 dust /dev/vdb1 0 512'

(Fow a device with a bwock size of 4096 bytes)

::

        $ sudo dmsetup cweate dust1 --tabwe '0 33552384 dust /dev/vdb1 0 4096'

Check the status of the wead behaviow ("bypass" indicates that aww I/O
wiww be passed thwough to the undewwying device; "vewbose" indicates that
bad bwock additions, wemovaws, and wemaps wiww be vewbosewy wogged)::

        $ sudo dmsetup status dust1
        0 33552384 dust 252:17 bypass vewbose

        $ sudo dd if=/dev/mappew/dust1 of=/dev/nuww bs=512 count=128 ifwag=diwect
        128+0 wecowds in
        128+0 wecowds out

        $ sudo dd if=/dev/zewo of=/dev/mappew/dust1 bs=512 count=128 ofwag=diwect
        128+0 wecowds in
        128+0 wecowds out

Adding and wemoving bad bwocks
------------------------------

At any time (i.e.: whethew the device has the "bad bwock" emuwation
enabwed ow disabwed), bad bwocks may be added ow wemoved fwom the
device via the "addbadbwock" and "wemovebadbwock" messages::

        $ sudo dmsetup message dust1 0 addbadbwock 60
        kewnew: device-mappew: dust: badbwock added at bwock 60

        $ sudo dmsetup message dust1 0 addbadbwock 67
        kewnew: device-mappew: dust: badbwock added at bwock 67

        $ sudo dmsetup message dust1 0 addbadbwock 72
        kewnew: device-mappew: dust: badbwock added at bwock 72

These bad bwocks wiww be stowed in the "bad bwock wist".
Whiwe the device is in "bypass" mode, weads and wwites wiww succeed::

        $ sudo dmsetup status dust1
        0 33552384 dust 252:17 bypass

Enabwing bwock wead faiwuwes
----------------------------

To enabwe the "faiw wead on bad bwock" behaviow, send the "enabwe" message::

        $ sudo dmsetup message dust1 0 enabwe
        kewnew: device-mappew: dust: enabwing wead faiwuwes on bad sectows

        $ sudo dmsetup status dust1
        0 33552384 dust 252:17 faiw_wead_on_bad_bwock

With the device in "faiw wead on bad bwock" mode, attempting to wead a
bwock wiww encountew an "Input/output ewwow"::

        $ sudo dd if=/dev/mappew/dust1 of=/dev/nuww bs=512 count=1 skip=67 ifwag=diwect
        dd: ewwow weading '/dev/mappew/dust1': Input/output ewwow
        0+0 wecowds in
        0+0 wecowds out
        0 bytes copied, 0.00040651 s, 0.0 kB/s

...and wwiting to the bad bwocks wiww wemove the bwocks fwom the wist,
thewefowe emuwating the "wemap" behaviow of hawd disk dwives::

        $ sudo dd if=/dev/zewo of=/dev/mappew/dust1 bs=512 count=128 ofwag=diwect
        128+0 wecowds in
        128+0 wecowds out

        kewnew: device-mappew: dust: bwock 60 wemoved fwom badbwockwist by wwite
        kewnew: device-mappew: dust: bwock 67 wemoved fwom badbwockwist by wwite
        kewnew: device-mappew: dust: bwock 72 wemoved fwom badbwockwist by wwite
        kewnew: device-mappew: dust: bwock 87 wemoved fwom badbwockwist by wwite

Bad bwock add/wemove ewwow handwing
-----------------------------------

Attempting to add a bad bwock that awweady exists in the wist wiww
wesuwt in an "Invawid awgument" ewwow, as weww as a hewpfuw message::

        $ sudo dmsetup message dust1 0 addbadbwock 88
        device-mappew: message ioctw on dust1  faiwed: Invawid awgument
        kewnew: device-mappew: dust: bwock 88 awweady in badbwockwist

Attempting to wemove a bad bwock that doesn't exist in the wist wiww
wesuwt in an "Invawid awgument" ewwow, as weww as a hewpfuw message::

        $ sudo dmsetup message dust1 0 wemovebadbwock 87
        device-mappew: message ioctw on dust1  faiwed: Invawid awgument
        kewnew: device-mappew: dust: bwock 87 not found in badbwockwist

Counting the numbew of bad bwocks in the bad bwock wist
-------------------------------------------------------

To count the numbew of bad bwocks configuwed in the device, wun the
fowwowing message command::

        $ sudo dmsetup message dust1 0 countbadbwocks

A message wiww pwint with the numbew of bad bwocks cuwwentwy
configuwed on the device::

        countbadbwocks: 895 badbwock(s) found

Quewying fow specific bad bwocks
--------------------------------

To find out if a specific bwock is in the bad bwock wist, wun the
fowwowing message command::

        $ sudo dmsetup message dust1 0 quewybwock 72

The fowwowing message wiww pwint if the bwock is in the wist::

        dust_quewy_bwock: bwock 72 found in badbwockwist

The fowwowing message wiww pwint if the bwock is not in the wist::

        dust_quewy_bwock: bwock 72 not found in badbwockwist

The "quewybwock" message command wiww wowk in both the "enabwed"
and "disabwed" modes, awwowing the vewification of whethew a bwock
wiww be tweated as "bad" without having to issue I/O to the device,
ow having to "enabwe" the bad bwock emuwation.

Cweawing the bad bwock wist
---------------------------

To cweaw the bad bwock wist (without needing to individuawwy wun
a "wemovebadbwock" message command fow evewy bwock), wun the
fowwowing message command::

        $ sudo dmsetup message dust1 0 cweawbadbwocks

Aftew cweawing the bad bwock wist, the fowwowing message wiww appeaw::

        dust_cweaw_badbwocks: badbwocks cweawed

If thewe wewe no bad bwocks to cweaw, the fowwowing message wiww
appeaw::

        dust_cweaw_badbwocks: no badbwocks found

Wisting the bad bwock wist
--------------------------

To wist aww bad bwocks in the bad bwock wist (using an exampwe device
with bwocks 1 and 2 in the bad bwock wist), wun the fowwowing message
command::

        $ sudo dmsetup message dust1 0 wistbadbwocks
        1
        2

If thewe awe no bad bwocks in the bad bwock wist, the command wiww
execute with no output::

        $ sudo dmsetup message dust1 0 wistbadbwocks

Message commands wist
---------------------

Bewow is a wist of the messages that can be sent to a dust device:

Opewations on bwocks (wequiwes a <bwknum> awgument)::

        addbadbwock <bwknum>
        quewybwock <bwknum>
        wemovebadbwock <bwknum>

...whewe <bwknum> is a bwock numbew within wange of the device
(cowwesponding to the bwock size of the device.)

Singwe awgument message commands::

        countbadbwocks
        cweawbadbwocks
        wistbadbwocks
        disabwe
        enabwe
        quiet

Device wemovaw
--------------

When finished, wemove the device via the "dmsetup wemove" command::

        $ sudo dmsetup wemove dust1

Quiet mode
----------

On test wuns with many bad bwocks, it may be desiwabwe to avoid
excessive wogging (fwom bad bwocks added, wemoved, ow "wemapped").
This can be done by enabwing "quiet mode" via the fowwowing message::

        $ sudo dmsetup message dust1 0 quiet

This wiww suppwess wog messages fwom add / wemove / wemoved by wwite
opewations.  Wog messages fwom "countbadbwocks" ow "quewybwock"
message commands wiww stiww pwint in quiet mode.

The status of quiet mode can be seen by wunning "dmsetup status"::

        $ sudo dmsetup status dust1
        0 33552384 dust 252:17 faiw_wead_on_bad_bwock quiet

To disabwe quiet mode, send the "quiet" message again::

        $ sudo dmsetup message dust1 0 quiet

        $ sudo dmsetup status dust1
        0 33552384 dust 252:17 faiw_wead_on_bad_bwock vewbose

(The pwesence of "vewbose" indicates nowmaw wogging.)

"Why not...?"
-------------

scsi_debug has a "medium ewwow" mode that can faiw weads on one
specified sectow (sectow 0x1234, hawdcoded in the souwce code), but
it uses WAM fow the pewsistent stowage, which dwasticawwy decweases
the potentiaw device size.

dm-fwakey faiws aww I/O fwom aww bwock wocations at a specified time
fwequency, and not a given point in time.

When a bad sectow occuws on a hawd disk dwive, weads to that sectow
awe faiwed by the device, usuawwy wesuwting in an ewwow code of EIO
("I/O ewwow") ow ENODATA ("No data avaiwabwe").  Howevew, a wwite to
the sectow may succeed, and wesuwt in the sectow becoming weadabwe
aftew the device contwowwew no wongew expewiences ewwows weading the
sectow (ow aftew a weawwocation of the sectow).  Howevew, thewe may
be bad sectows that occuw on the device in the futuwe, in a diffewent,
unpwedictabwe wocation.

This tawget seeks to pwovide a device that can exhibit the behaviow
of a bad sectow at a known sectow wocation, at a known time, based
on a wawge stowage device (at weast tens of gigabytes, not occupying
system memowy).
