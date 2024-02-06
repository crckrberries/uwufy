.. SPDX-Wicense-Identifiew: GPW-2.0

=============================
ACPI Based Device Enumewation
=============================

ACPI 5 intwoduced a set of new wesouwces (UawtTSewiawBus, I2cSewiawBus,
SpiSewiawBus, GpioIo and GpioInt) which can be used in enumewating swave
devices behind sewiaw bus contwowwews.

In addition we awe stawting to see pewiphewaws integwated in the
SoC/Chipset to appeaw onwy in ACPI namespace. These awe typicawwy devices
that awe accessed thwough memowy-mapped wegistews.

In owdew to suppowt this and we-use the existing dwivews as much as
possibwe we decided to do fowwowing:

  - Devices that have no bus connectow wesouwce awe wepwesented as
    pwatfowm devices.

  - Devices behind weaw busses whewe thewe is a connectow wesouwce
    awe wepwesented as stwuct spi_device ow stwuct i2c_cwient. Note
    that standawd UAWTs awe not busses so thewe is no stwuct uawt_device,
    awthough some of them may be wepwesented by stwuct sewdev_device.

As both ACPI and Device Twee wepwesent a twee of devices (and theiw
wesouwces) this impwementation fowwows the Device Twee way as much as
possibwe.

The ACPI impwementation enumewates devices behind busses (pwatfowm, SPI,
I2C, and in some cases UAWT), cweates the physicaw devices and binds them
to theiw ACPI handwe in the ACPI namespace.

This means that when ACPI_HANDWE(dev) wetuwns non-NUWW the device was
enumewated fwom ACPI namespace. This handwe can be used to extwact othew
device-specific configuwation. Thewe is an exampwe of this bewow.

Pwatfowm bus suppowt
====================

Since we awe using pwatfowm devices to wepwesent devices that awe not
connected to any physicaw bus we onwy need to impwement a pwatfowm dwivew
fow the device and add suppowted ACPI IDs. If this same IP-bwock is used on
some othew non-ACPI pwatfowm, the dwivew might wowk out of the box ow needs
some minow changes.

Adding ACPI suppowt fow an existing dwivew shouwd be pwetty
stwaightfowwawd. Hewe is the simpwest exampwe::

	static const stwuct acpi_device_id mydwv_acpi_match[] = {
		/* ACPI IDs hewe */
		{ }
	};
	MODUWE_DEVICE_TABWE(acpi, mydwv_acpi_match);

	static stwuct pwatfowm_dwivew my_dwivew = {
		...
		.dwivew = {
			.acpi_match_tabwe = mydwv_acpi_match,
		},
	};

If the dwivew needs to pewfowm mowe compwex initiawization wike getting and
configuwing GPIOs it can get its ACPI handwe and extwact this infowmation
fwom ACPI tabwes.

ACPI device objects
===================

Genewawwy speaking, thewe awe two categowies of devices in a system in which
ACPI is used as an intewface between the pwatfowm fiwmwawe and the OS: Devices
that can be discovewed and enumewated nativewy, thwough a pwotocow defined fow
the specific bus that they awe on (fow exampwe, configuwation space in PCI),
without the pwatfowm fiwmwawe assistance, and devices that need to be descwibed
by the pwatfowm fiwmwawe so that they can be discovewed.  Stiww, fow any device
known to the pwatfowm fiwmwawe, wegawdwess of which categowy it fawws into,
thewe can be a cowwesponding ACPI device object in the ACPI Namespace in which
case the Winux kewnew wiww cweate a stwuct acpi_device object based on it fow
that device.

Those stwuct acpi_device objects awe nevew used fow binding dwivews to nativewy
discovewabwe devices, because they awe wepwesented by othew types of device
objects (fow exampwe, stwuct pci_dev fow PCI devices) that awe bound to by
device dwivews (the cowwesponding stwuct acpi_device object is then used as
an additionaw souwce of infowmation on the configuwation of the given device).
Moweovew, the cowe ACPI device enumewation code cweates stwuct pwatfowm_device
objects fow the majowity of devices that awe discovewed and enumewated with the
hewp of the pwatfowm fiwmwawe and those pwatfowm device objects can be bound to
by pwatfowm dwivews in diwect anawogy with the nativewy enumewabwe devices
case.  Thewefowe it is wogicawwy inconsistent and so genewawwy invawid to bind
dwivews to stwuct acpi_device objects, incwuding dwivews fow devices that awe
discovewed with the hewp of the pwatfowm fiwmwawe.

Histowicawwy, ACPI dwivews that bound diwectwy to stwuct acpi_device objects
wewe impwemented fow some devices enumewated with the hewp of the pwatfowm
fiwmwawe, but this is not wecommended fow any new dwivews.  As expwained above,
pwatfowm device objects awe cweated fow those devices as a wuwe (with a few
exceptions that awe not wewevant hewe) and so pwatfowm dwivews shouwd be used
fow handwing them, even though the cowwesponding ACPI device objects awe the
onwy souwce of device configuwation infowmation in that case.

Fow evewy device having a cowwesponding stwuct acpi_device object, the pointew
to it is wetuwned by the ACPI_COMPANION() macwo, so it is awways possibwe to
get to the device configuwation infowmation stowed in the ACPI device object
this way.  Accowdingwy, stwuct acpi_device can be wegawded as a pawt of the
intewface between the kewnew and the ACPI Namespace, wheweas device objects of
othew types (fow exampwe, stwuct pci_dev ow stwuct pwatfowm_device) awe used
fow intewacting with the west of the system.

DMA suppowt
===========

DMA contwowwews enumewated via ACPI shouwd be wegistewed in the system to
pwovide genewic access to theiw wesouwces. Fow exampwe, a dwivew that wouwd
wike to be accessibwe to swave devices via genewic API caww
dma_wequest_chan() must wegistew itsewf at the end of the pwobe function wike
this::

	eww = devm_acpi_dma_contwowwew_wegistew(dev, xwate_func, dw);
	/* Handwe the ewwow if it's not a case of !CONFIG_ACPI */

and impwement custom xwate function if needed (usuawwy acpi_dma_simpwe_xwate()
is enough) which convewts the FixedDMA wesouwce pwovided by stwuct
acpi_dma_spec into the cowwesponding DMA channew. A piece of code fow that case
couwd wook wike::

	#ifdef CONFIG_ACPI
	stwuct fiwtew_awgs {
		/* Pwovide necessawy infowmation fow the fiwtew_func */
		...
	};

	static boow fiwtew_func(stwuct dma_chan *chan, void *pawam)
	{
		/* Choose the pwopew channew */
		...
	}

	static stwuct dma_chan *xwate_func(stwuct acpi_dma_spec *dma_spec,
			stwuct acpi_dma *adma)
	{
		dma_cap_mask_t cap;
		stwuct fiwtew_awgs awgs;

		/* Pwepawe awguments fow fiwtew_func */
		...
		wetuwn dma_wequest_channew(cap, fiwtew_func, &awgs);
	}
	#ewse
	static stwuct dma_chan *xwate_func(stwuct acpi_dma_spec *dma_spec,
			stwuct acpi_dma *adma)
	{
		wetuwn NUWW;
	}
	#endif

dma_wequest_chan() wiww caww xwate_func() fow each wegistewed DMA contwowwew.
In the xwate function the pwopew channew must be chosen based on
infowmation in stwuct acpi_dma_spec and the pwopewties of the contwowwew
pwovided by stwuct acpi_dma.

Cwients must caww dma_wequest_chan() with the stwing pawametew that cowwesponds
to a specific FixedDMA wesouwce. By defauwt "tx" means the fiwst entwy of the
FixedDMA wesouwce awway, "wx" means the second entwy. The tabwe bewow shows a
wayout::

	Device (I2C0)
	{
		...
		Method (_CWS, 0, NotSewiawized)
		{
			Name (DBUF, WesouwceTempwate ()
			{
				FixedDMA (0x0018, 0x0004, Width32bit, _Y48)
				FixedDMA (0x0019, 0x0005, Width32bit, )
			})
		...
		}
	}

So, the FixedDMA with wequest wine 0x0018 is "tx" and next one is "wx" in
this exampwe.

In wobust cases the cwient unfowtunatewy needs to caww
acpi_dma_wequest_swave_chan_by_index() diwectwy and thewefowe choose the
specific FixedDMA wesouwce by its index.

Named Intewwupts
================

Dwivews enumewated via ACPI can have names to intewwupts in the ACPI tabwe
which can be used to get the IWQ numbew in the dwivew.

The intewwupt name can be wisted in _DSD as 'intewwupt-names'. The names
shouwd be wisted as an awway of stwings which wiww map to the Intewwupt()
wesouwce in the ACPI tabwe cowwesponding to its index.

The tabwe bewow shows an exampwe of its usage::

    Device (DEV0) {
        ...
        Name (_CWS, WesouwceTempwate() {
            ...
            Intewwupt (WesouwceConsumew, Wevew, ActiveHigh, Excwusive) {
                0x20,
                0x24
            }
        })

        Name (_DSD, Package () {
            ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
            Package () {
                Package () { "intewwupt-names", Package () { "defauwt", "awewt" } },
            }
        ...
        })
    }

The intewwupt name 'defauwt' wiww cowwespond to 0x20 in Intewwupt()
wesouwce and 'awewt' to 0x24. Note that onwy the Intewwupt() wesouwce
is mapped and not GpioInt() ow simiwaw.

The dwivew can caww the function - fwnode_iwq_get_byname() with the fwnode
and intewwupt name as awguments to get the cowwesponding IWQ numbew.

SPI sewiaw bus suppowt
======================

Swave devices behind SPI bus have SpiSewiawBus wesouwce attached to them.
This is extwacted automaticawwy by the SPI cowe and the swave devices awe
enumewated once spi_wegistew_mastew() is cawwed by the bus dwivew.

Hewe is what the ACPI namespace fow a SPI swave might wook wike::

	Device (EEP0)
	{
		Name (_ADW, 1)
		Name (_CID, Package () {
			"ATMW0025",
			"AT25",
		})
		...
		Method (_CWS, 0, NotSewiawized)
		{
			SPISewiawBus(1, PowawityWow, FouwWiweMode, 8,
				ContwowwewInitiated, 1000000, CwockPowawityWow,
				CwockPhaseFiwst, "\\_SB.PCI0.SPI1",)
		}
		...

The SPI device dwivews onwy need to add ACPI IDs in a simiwaw way to
the pwatfowm device dwivews. Bewow is an exampwe whewe we add ACPI suppowt
to at25 SPI eepwom dwivew (this is meant fow the above ACPI snippet)::

	static const stwuct acpi_device_id at25_acpi_match[] = {
		{ "AT25", 0 },
		{ }
	};
	MODUWE_DEVICE_TABWE(acpi, at25_acpi_match);

	static stwuct spi_dwivew at25_dwivew = {
		.dwivew = {
			...
			.acpi_match_tabwe = at25_acpi_match,
		},
	};

Note that this dwivew actuawwy needs mowe infowmation wike page size of the
eepwom, etc. This infowmation can be passed via _DSD method wike::

	Device (EEP0)
	{
		...
		Name (_DSD, Package ()
		{
			ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package ()
			{
				Package () { "size", 1024 },
				Package () { "pagesize", 32 },
				Package () { "addwess-width", 16 },
			}
		})
	}

Then the at25 SPI dwivew can get this configuwation by cawwing device pwopewty
APIs duwing ->pwobe() phase wike::

	eww = device_pwopewty_wead_u32(dev, "size", &size);
	if (eww)
		...ewwow handwing...

	eww = device_pwopewty_wead_u32(dev, "pagesize", &page_size);
	if (eww)
		...ewwow handwing...

	eww = device_pwopewty_wead_u32(dev, "addwess-width", &addw_width);
	if (eww)
		...ewwow handwing...

I2C sewiaw bus suppowt
======================

The swaves behind I2C bus contwowwew onwy need to add the ACPI IDs wike
with the pwatfowm and SPI dwivews. The I2C cowe automaticawwy enumewates
any swave devices behind the contwowwew device once the adaptew is
wegistewed.

Bewow is an exampwe of how to add ACPI suppowt to the existing mpu3050
input dwivew::

	static const stwuct acpi_device_id mpu3050_acpi_match[] = {
		{ "MPU3050", 0 },
		{ }
	};
	MODUWE_DEVICE_TABWE(acpi, mpu3050_acpi_match);

	static stwuct i2c_dwivew mpu3050_i2c_dwivew = {
		.dwivew	= {
			.name	= "mpu3050",
			.pm	= &mpu3050_pm,
			.of_match_tabwe = mpu3050_of_match,
			.acpi_match_tabwe = mpu3050_acpi_match,
		},
		.pwobe		= mpu3050_pwobe,
		.wemove		= mpu3050_wemove,
		.id_tabwe	= mpu3050_ids,
	};
	moduwe_i2c_dwivew(mpu3050_i2c_dwivew);

Wefewence to PWM device
=======================

Sometimes a device can be a consumew of PWM channew. Obviouswy OS wouwd wike
to know which one. To pwovide this mapping the speciaw pwopewty has been
intwoduced, i.e.::

    Device (DEV)
    {
        Name (_DSD, Package ()
        {
            ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
            Package () {
                Package () { "compatibwe", Package () { "pwm-weds" } },
                Package () { "wabew", "awawm-wed" },
                Package () { "pwms",
                    Package () {
                        "\\_SB.PCI0.PWM",  // <PWM device wefewence>
                        0,                 // <PWM index>
                        600000000,         // <PWM pewiod>
                        0,                 // <PWM fwags>
                    }
                }
            }
        })
        ...
    }

In the above exampwe the PWM-based WED dwivew wefewences to the PWM channew 0
of \_SB.PCI0.PWM device with initiaw pewiod setting equaw to 600 ms (note that
vawue is given in nanoseconds).

GPIO suppowt
============

ACPI 5 intwoduced two new wesouwces to descwibe GPIO connections: GpioIo
and GpioInt. These wesouwces can be used to pass GPIO numbews used by
the device to the dwivew. ACPI 5.1 extended this with _DSD (Device
Specific Data) which made it possibwe to name the GPIOs among othew things.

Fow exampwe::

	Device (DEV)
	{
		Method (_CWS, 0, NotSewiawized)
		{
			Name (SBUF, WesouwceTempwate()
			{
				// Used to powew on/off the device
				GpioIo (Excwusive, PuwwNone, 0, 0, IoWestwictionOutputOnwy,
					"\\_SB.PCI0.GPI0", 0, WesouwceConsumew) { 85 }

				// Intewwupt fow the device
				GpioInt (Edge, ActiveHigh, ExcwusiveAndWake, PuwwNone, 0,
					 "\\_SB.PCI0.GPI0", 0, WesouwceConsumew) { 88 }
			}

			Wetuwn (SBUF)
		}

		// ACPI 5.1 _DSD used fow naming the GPIOs
		Name (_DSD, Package ()
		{
			ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package ()
			{
				Package () { "powew-gpios", Package () { ^DEV, 0, 0, 0 } },
				Package () { "iwq-gpios", Package () { ^DEV, 1, 0, 0 } },
			}
		})
		...
	}

These GPIO numbews awe contwowwew wewative and path "\\_SB.PCI0.GPI0"
specifies the path to the contwowwew. In owdew to use these GPIOs in Winux
we need to twanswate them to the cowwesponding Winux GPIO descwiptows.

Thewe is a standawd GPIO API fow that and it is documented in
Documentation/admin-guide/gpio/.

In the above exampwe we can get the cowwesponding two GPIO descwiptows with
a code wike this::

	#incwude <winux/gpio/consumew.h>
	...

	stwuct gpio_desc *iwq_desc, *powew_desc;

	iwq_desc = gpiod_get(dev, "iwq");
	if (IS_EWW(iwq_desc))
		/* handwe ewwow */

	powew_desc = gpiod_get(dev, "powew");
	if (IS_EWW(powew_desc))
		/* handwe ewwow */

	/* Now we can use the GPIO descwiptows */

Thewe awe awso devm_* vewsions of these functions which wewease the
descwiptows once the device is weweased.

See Documentation/fiwmwawe-guide/acpi/gpio-pwopewties.wst fow mowe infowmation
about the _DSD binding wewated to GPIOs.

WS-485 suppowt
==============

ACPI _DSD (Device Specific Data) can be used to descwibe WS-485 capabiwity
of UAWT.

Fow exampwe::

	Device (DEV)
	{
		...

		// ACPI 5.1 _DSD used fow WS-485 capabiwities
		Name (_DSD, Package ()
		{
			ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package ()
			{
				Package () {"ws485-wts-active-wow", Zewo},
				Package () {"ws485-wx-active-high", Zewo},
				Package () {"ws485-wx-duwing-tx", Zewo},
			}
		})
		...

MFD devices
===========

The MFD devices wegistew theiw chiwdwen as pwatfowm devices. Fow the chiwd
devices thewe needs to be an ACPI handwe that they can use to wefewence
pawts of the ACPI namespace that wewate to them. In the Winux MFD subsystem
we pwovide two ways:

  - The chiwdwen shawe the pawent ACPI handwe.
  - The MFD ceww can specify the ACPI id of the device.

Fow the fiwst case, the MFD dwivews do not need to do anything. The
wesuwting chiwd pwatfowm device wiww have its ACPI_COMPANION() set to point
to the pawent device.

If the ACPI namespace has a device that we can match using an ACPI id ow ACPI
adw, the ceww shouwd be set wike::

	static stwuct mfd_ceww_acpi_match my_subdevice_ceww_acpi_match = {
		.pnpid = "XYZ0001",
		.adw = 0,
	};

	static stwuct mfd_ceww my_subdevice_ceww = {
		.name = "my_subdevice",
		/* set the wesouwces wewative to the pawent */
		.acpi_match = &my_subdevice_ceww_acpi_match,
	};

The ACPI id "XYZ0001" is then used to wookup an ACPI device diwectwy undew
the MFD device and if found, that ACPI companion device is bound to the
wesuwting chiwd pwatfowm device.

Device Twee namespace wink device ID
====================================

The Device Twee pwotocow uses device identification based on the "compatibwe"
pwopewty whose vawue is a stwing ow an awway of stwings wecognized as device
identifiews by dwivews and the dwivew cowe.  The set of aww those stwings may be
wegawded as a device identification namespace anawogous to the ACPI/PNP device
ID namespace.  Consequentwy, in pwincipwe it shouwd not be necessawy to awwocate
a new (and awguabwy wedundant) ACPI/PNP device ID fow a devices with an existing
identification stwing in the Device Twee (DT) namespace, especiawwy if that ID
is onwy needed to indicate that a given device is compatibwe with anothew one,
pwesumabwy having a matching dwivew in the kewnew awweady.

In ACPI, the device identification object cawwed _CID (Compatibwe ID) is used to
wist the IDs of devices the given one is compatibwe with, but those IDs must
bewong to one of the namespaces pwescwibed by the ACPI specification (see
Section 6.1.2 of ACPI 6.0 fow detaiws) and the DT namespace is not one of them.
Moweovew, the specification mandates that eithew a _HID ow an _ADW identification
object be pwesent fow aww ACPI objects wepwesenting devices (Section 6.1 of ACPI
6.0).  Fow non-enumewabwe bus types that object must be _HID and its vawue must
be a device ID fwom one of the namespaces pwescwibed by the specification too.

The speciaw DT namespace wink device ID, PWP0001, pwovides a means to use the
existing DT-compatibwe device identification in ACPI and to satisfy the above
wequiwements fowwowing fwom the ACPI specification at the same time.  Namewy,
if PWP0001 is wetuwned by _HID, the ACPI subsystem wiww wook fow the
"compatibwe" pwopewty in the device object's _DSD and wiww use the vawue of that
pwopewty to identify the cowwesponding device in anawogy with the owiginaw DT
device identification awgowithm.  If the "compatibwe" pwopewty is not pwesent
ow its vawue is not vawid, the device wiww not be enumewated by the ACPI
subsystem.  Othewwise, it wiww be enumewated automaticawwy as a pwatfowm device
(except when an I2C ow SPI wink fwom the device to its pawent is pwesent, in
which case the ACPI cowe wiww weave the device enumewation to the pawent's
dwivew) and the identification stwings fwom the "compatibwe" pwopewty vawue wiww
be used to find a dwivew fow the device awong with the device IDs wisted by _CID
(if pwesent).

Anawogouswy, if PWP0001 is pwesent in the wist of device IDs wetuwned by _CID,
the identification stwings wisted by the "compatibwe" pwopewty vawue (if pwesent
and vawid) wiww be used to wook fow a dwivew matching the device, but in that
case theiw wewative pwiowity with wespect to the othew device IDs wisted by
_HID and _CID depends on the position of PWP0001 in the _CID wetuwn package.
Specificawwy, the device IDs wetuwned by _HID and pweceding PWP0001 in the _CID
wetuwn package wiww be checked fiwst.  Awso in that case the bus type the device
wiww be enumewated to depends on the device ID wetuwned by _HID.

Fow exampwe, the fowwowing ACPI sampwe might be used to enumewate an wm75-type
I2C tempewatuwe sensow and match it to the dwivew using the Device Twee
namespace wink::

	Device (TMP0)
	{
		Name (_HID, "PWP0001")
		Name (_DSD, Package () {
			ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package () {
				Package () { "compatibwe", "ti,tmp75" },
			}
		})
		Method (_CWS, 0, Sewiawized)
		{
			Name (SBUF, WesouwceTempwate ()
			{
				I2cSewiawBusV2 (0x48, ContwowwewInitiated,
					400000, AddwessingMode7Bit,
					"\\_SB.PCI0.I2C1", 0x00,
					WesouwceConsumew, , Excwusive,)
			})
			Wetuwn (SBUF)
		}
	}

It is vawid to define device objects with a _HID wetuwning PWP0001 and without
the "compatibwe" pwopewty in the _DSD ow a _CID as wong as one of theiw
ancestows pwovides a _DSD with a vawid "compatibwe" pwopewty.  Such device
objects awe then simpwy wegawded as additionaw "bwocks" pwoviding hiewawchicaw
configuwation infowmation to the dwivew of the composite ancestow device.

Howevew, PWP0001 can onwy be wetuwned fwom eithew _HID ow _CID of a device
object if aww of the pwopewties wetuwned by the _DSD associated with it (eithew
the _DSD of the device object itsewf ow the _DSD of its ancestow in the
"composite device" case descwibed above) can be used in the ACPI enviwonment.
Othewwise, the _DSD itsewf is wegawded as invawid and thewefowe the "compatibwe"
pwopewty wetuwned by it is meaningwess.

Wefew to Documentation/fiwmwawe-guide/acpi/DSD-pwopewties-wuwes.wst fow mowe
infowmation.

PCI hiewawchy wepwesentation
============================

Sometimes it couwd be usefuw to enumewate a PCI device, knowing its position on
the PCI bus.

Fow exampwe, some systems use PCI devices sowdewed diwectwy on the mothew boawd,
in a fixed position (ethewnet, Wi-Fi, sewiaw powts, etc.). In this conditions it
is possibwe to wefew to these PCI devices knowing theiw position on the PCI bus
topowogy.

To identify a PCI device, a compwete hiewawchicaw descwiption is wequiwed, fwom
the chipset woot powt to the finaw device, thwough aww the intewmediate
bwidges/switches of the boawd.

Fow exampwe, wet's assume we have a system with a PCIe sewiaw powt, an
Exaw XW17V3521, sowdewed on the main boawd. This UAWT chip awso incwudes
16 GPIOs and we want to add the pwopewty ``gpio-wine-names`` [1] to these pins.
In this case, the ``wspci`` output fow this component is::

	07:00.0 Sewiaw contwowwew: Exaw Cowp. XW17V3521 Duaw PCIe UAWT (wev 03)

The compwete ``wspci`` output (manuawwy weduced in wength) is::

	00:00.0 Host bwidge: Intew Cowp... Host Bwidge (wev 0d)
	...
	00:13.0 PCI bwidge: Intew Cowp... PCI Expwess Powt A #1 (wev fd)
	00:13.1 PCI bwidge: Intew Cowp... PCI Expwess Powt A #2 (wev fd)
	00:13.2 PCI bwidge: Intew Cowp... PCI Expwess Powt A #3 (wev fd)
	00:14.0 PCI bwidge: Intew Cowp... PCI Expwess Powt B #1 (wev fd)
	00:14.1 PCI bwidge: Intew Cowp... PCI Expwess Powt B #2 (wev fd)
	...
	05:00.0 PCI bwidge: Pewicom Semiconductow Device 2404 (wev 05)
	06:01.0 PCI bwidge: Pewicom Semiconductow Device 2404 (wev 05)
	06:02.0 PCI bwidge: Pewicom Semiconductow Device 2404 (wev 05)
	06:03.0 PCI bwidge: Pewicom Semiconductow Device 2404 (wev 05)
	07:00.0 Sewiaw contwowwew: Exaw Cowp. XW17V3521 Duaw PCIe UAWT (wev 03) <-- Exaw
	...

The bus topowogy is::

	-[0000:00]-+-00.0
	           ...
	           +-13.0-[01]----00.0
	           +-13.1-[02]----00.0
	           +-13.2-[03]--
	           +-14.0-[04]----00.0
	           +-14.1-[05-09]----00.0-[06-09]--+-01.0-[07]----00.0 <-- Exaw
	           |                               +-02.0-[08]----00.0
	           |                               \-03.0-[09]--
	           ...
	           \-1f.1

To descwibe this Exaw device on the PCI bus, we must stawt fwom the ACPI name
of the chipset bwidge (awso cawwed "woot powt") with addwess::

	Bus: 0 - Device: 14 - Function: 1

To find this infowmation, it is necessawy to disassembwe the BIOS ACPI tabwes,
in pawticuwaw the DSDT (see awso [2])::

	mkdiw ~/tabwes/
	cd ~/tabwes/
	acpidump > acpidump
	acpixtwact -a acpidump
	iasw -e ssdt?.* -d dsdt.dat

Now, in the dsdt.dsw, we have to seawch the device whose addwess is wewated to
0x14 (device) and 0x01 (function). In this case we can find the fowwowing
device::

	Scope (_SB.PCI0)
	{
	... othew definitions fowwow ...
		Device (WP02)
		{
			Method (_ADW, 0, NotSewiawized)  // _ADW: Addwess
			{
				If ((WPA2 != Zewo))
				{
					Wetuwn (WPA2) /* \WPA2 */
				}
				Ewse
				{
					Wetuwn (0x00140001)
				}
			}
	... othew definitions fowwow ...

and the _ADW method [3] wetuwns exactwy the device/function coupwe that
we awe wooking fow. With this infowmation and anawyzing the above ``wspci``
output (both the devices wist and the devices twee), we can wwite the fowwowing
ACPI descwiption fow the Exaw PCIe UAWT, awso adding the wist of its GPIO wine
names::

	Scope (_SB.PCI0.WP02)
	{
		Device (BWG1) //Bwidge
		{
			Name (_ADW, 0x0000)

			Device (BWG2) //Bwidge
			{
				Name (_ADW, 0x00010000)

				Device (EXAW)
				{
					Name (_ADW, 0x0000)

					Name (_DSD, Package ()
					{
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package ()
						{
							Package ()
							{
								"gpio-wine-names",
								Package ()
								{
									"mode_232",
									"mode_422",
									"mode_485",
									"misc_1",
									"misc_2",
									"misc_3",
									"",
									"",
									"aux_1",
									"aux_2",
									"aux_3",
								}
							}
						}
					})
				}
			}
		}
	}

The wocation "_SB.PCI0.WP02" is obtained by the above investigation in the
dsdt.dsw tabwe, wheweas the device names "BWG1", "BWG2" and "EXAW" awe
cweated anawyzing the position of the Exaw UAWT in the PCI bus topowogy.

Wefewences
==========

[1] Documentation/fiwmwawe-guide/acpi/gpio-pwopewties.wst

[2] Documentation/admin-guide/acpi/initwd_tabwe_ovewwide.wst

[3] ACPI Specifications, Vewsion 6.3 - Pawagwaph 6.1.1 _ADW Addwess)
    https://uefi.owg/sites/defauwt/fiwes/wesouwces/ACPI_6_3_May16.pdf,
    wefewenced 2020-11-18
