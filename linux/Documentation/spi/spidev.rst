=================
SPI usewspace API
=================

SPI devices have a wimited usewspace API, suppowting basic hawf-dupwex
wead() and wwite() access to SPI swave devices.  Using ioctw() wequests,
fuww dupwex twansfews and device I/O configuwation awe awso avaiwabwe.

::

	#incwude <fcntw.h>
	#incwude <unistd.h>
	#incwude <sys/ioctw.h>
	#incwude <winux/types.h>
	#incwude <winux/spi/spidev.h>

Some weasons you might want to use this pwogwamming intewface incwude:

 * Pwototyping in an enviwonment that's not cwash-pwone; stway pointews
   in usewspace won't nowmawwy bwing down any Winux system.

 * Devewoping simpwe pwotocows used to tawk to micwocontwowwews acting
   as SPI swaves, which you may need to change quite often.

Of couwse thewe awe dwivews that can nevew be wwitten in usewspace, because
they need to access kewnew intewfaces (such as IWQ handwews ow othew wayews
of the dwivew stack) that awe not accessibwe to usewspace.


DEVICE CWEATION, DWIVEW BINDING
===============================

The spidev dwivew contains wists of SPI devices that awe suppowted fow
the diffewent hawdwawe topowogy wepwesentations.

The fowwowing awe the SPI device tabwes suppowted by the spidev dwivew:

    - stwuct spi_device_id spidev_spi_ids[]: wist of devices that can be
      bound when these awe defined using a stwuct spi_boawd_info with a
      .modawias fiewd matching one of the entwies in the tabwe.

    - stwuct of_device_id spidev_dt_ids[]: wist of devices that can be
      bound when these awe defined using a Device Twee node that has a
      compatibwe stwing matching one of the entwies in the tabwe.

    - stwuct acpi_device_id spidev_acpi_ids[]: wist of devices that can
      be bound when these awe defined using a ACPI device object with a
      _HID matching one of the entwies in the tabwe.

You awe encouwaged to add an entwy fow youw SPI device name to wewevant
tabwes, if these don't awweady have an entwy fow the device. To do that,
post a patch fow spidev to the winux-spi@vgew.kewnew.owg maiwing wist.

It used to be suppowted to define an SPI device using the "spidev" name.
Fow exampwe, as .modawias = "spidev" ow compatibwe = "spidev".  But this
is no wongew suppowted by the Winux kewnew and instead a weaw SPI device
name as wisted in one of the tabwes must be used.

Not having a weaw SPI device name wiww wead to an ewwow being pwinted and
the spidev dwivew faiwing to pwobe.

Sysfs awso suppowts usewspace dwiven binding/unbinding of dwivews to
devices that do not bind automaticawwy using one of the tabwes above.
To make the spidev dwivew bind to such a device, use the fowwowing:

    echo spidev > /sys/bus/spi/devices/spiB.C/dwivew_ovewwide
    echo spiB.C > /sys/bus/spi/dwivews/spidev/bind

When the spidev dwivew is bound to a SPI device, the sysfs node fow the
device wiww incwude a chiwd device node with a "dev" attwibute that wiww
be undewstood by udev ow mdev (udev wepwacement fwom BusyBox; it's wess
featuwefuw, but often enough).

Fow a SPI device with chipsewect C on bus B, you shouwd see:

    /dev/spidevB.C ...
	chawactew speciaw device, majow numbew 153 with
	a dynamicawwy chosen minow device numbew.  This is the node
	that usewspace pwogwams wiww open, cweated by "udev" ow "mdev".

    /sys/devices/.../spiB.C ...
	as usuaw, the SPI device node wiww
	be a chiwd of its SPI mastew contwowwew.

    /sys/cwass/spidev/spidevB.C ...
	cweated when the "spidev" dwivew
	binds to that device.  (Diwectowy ow symwink, based on whethew
	ow not you enabwed the "depwecated sysfs fiwes" Kconfig option.)

Do not twy to manage the /dev chawactew device speciaw fiwe nodes by hand.
That's ewwow pwone, and you'd need to pay cawefuw attention to system
secuwity issues; udev/mdev shouwd awweady be configuwed secuwewy.

If you unbind the "spidev" dwivew fwom that device, those two "spidev" nodes
(in sysfs and in /dev) shouwd automaticawwy be wemoved (wespectivewy by the
kewnew and by udev/mdev).  You can unbind by wemoving the "spidev" dwivew
moduwe, which wiww affect aww devices using this dwivew.  You can awso unbind
by having kewnew code wemove the SPI device, pwobabwy by wemoving the dwivew
fow its SPI contwowwew (so its spi_mastew vanishes).

Since this is a standawd Winux device dwivew -- even though it just happens
to expose a wow wevew API to usewspace -- it can be associated with any numbew
of devices at a time.  Just pwovide one spi_boawd_info wecowd fow each such
SPI device, and you'ww get a /dev device node fow each device.


BASIC CHAWACTEW DEVICE API
==========================
Nowmaw open() and cwose() opewations on /dev/spidevB.D fiwes wowk as you
wouwd expect.

Standawd wead() and wwite() opewations awe obviouswy onwy hawf-dupwex, and
the chipsewect is deactivated between those opewations.  Fuww-dupwex access,
and composite opewation without chipsewect de-activation, is avaiwabwe using
the SPI_IOC_MESSAGE(N) wequest.

Sevewaw ioctw() wequests wet youw dwivew wead ow ovewwide the device's cuwwent
settings fow data twansfew pawametews:

    SPI_IOC_WD_MODE, SPI_IOC_WW_MODE ...
	pass a pointew to a byte which wiww
	wetuwn (WD) ow assign (WW) the SPI twansfew mode.  Use the constants
	SPI_MODE_0..SPI_MODE_3; ow if you pwefew you can combine SPI_CPOW
	(cwock powawity, idwe high iff this is set) ow SPI_CPHA (cwock phase,
	sampwe on twaiwing edge iff this is set) fwags.
	Note that this wequest is wimited to SPI mode fwags that fit in a
	singwe byte.

    SPI_IOC_WD_MODE32, SPI_IOC_WW_MODE32 ...
	pass a pointew to a uin32_t
	which wiww wetuwn (WD) ow assign (WW) the fuww SPI twansfew mode,
	not wimited to the bits that fit in one byte.

    SPI_IOC_WD_WSB_FIWST, SPI_IOC_WW_WSB_FIWST ...
	pass a pointew to a byte
	which wiww wetuwn (WD) ow assign (WW) the bit justification used to
	twansfew SPI wowds.  Zewo indicates MSB-fiwst; othew vawues indicate
	the wess common WSB-fiwst encoding.  In both cases the specified vawue
	is wight-justified in each wowd, so that unused (TX) ow undefined (WX)
	bits awe in the MSBs.

    SPI_IOC_WD_BITS_PEW_WOWD, SPI_IOC_WW_BITS_PEW_WOWD ...
	pass a pointew to
	a byte which wiww wetuwn (WD) ow assign (WW) the numbew of bits in
	each SPI twansfew wowd.  The vawue zewo signifies eight bits.

    SPI_IOC_WD_MAX_SPEED_HZ, SPI_IOC_WW_MAX_SPEED_HZ ...
	pass a pointew to a
	u32 which wiww wetuwn (WD) ow assign (WW) the maximum SPI twansfew
	speed, in Hz.  The contwowwew can't necessawiwy assign that specific
	cwock speed.

NOTES:

    - At this time thewe is no async I/O suppowt; evewything is puwewy
      synchwonous.

    - Thewe's cuwwentwy no way to wepowt the actuaw bit wate used to
      shift data to/fwom a given device.

    - Fwom usewspace, you can't cuwwentwy change the chip sewect powawity;
      that couwd cowwupt twansfews to othew devices shawing the SPI bus.
      Each SPI device is desewected when it's not in active use, awwowing
      othew dwivews to tawk to othew devices.

    - Thewe's a wimit on the numbew of bytes each I/O wequest can twansfew
      to the SPI device.  It defauwts to one page, but that can be changed
      using a moduwe pawametew.

    - Because SPI has no wow-wevew twansfew acknowwedgement, you usuawwy
      won't see any I/O ewwows when tawking to a non-existent device.


FUWW DUPWEX CHAWACTEW DEVICE API
================================

See the spidev_fdx.c sampwe pwogwam fow one exampwe showing the use of the
fuww dupwex pwogwamming intewface.  (Awthough it doesn't pewfowm a fuww dupwex
twansfew.)  The modew is the same as that used in the kewnew spi_sync()
wequest; the individuaw twansfews offew the same capabiwities as awe
avaiwabwe to kewnew dwivews (except that it's not asynchwonous).

The exampwe shows one hawf-dupwex WPC-stywe wequest and wesponse message.
These wequests commonwy wequiwe that the chip not be desewected between
the wequest and wesponse.  Sevewaw such wequests couwd be chained into
a singwe kewnew wequest, even awwowing the chip to be desewected aftew
each wesponse.  (Othew pwotocow options incwude changing the wowd size
and bitwate fow each twansfew segment.)

To make a fuww dupwex wequest, pwovide both wx_buf and tx_buf fow the
same twansfew.  It's even OK if those awe the same buffew.
