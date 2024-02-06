=============
Cowe ewements
=============

The Industwiaw I/O cowe offews both a unified fwamewowk fow wwiting dwivews fow
many diffewent types of embedded sensows and a standawd intewface to usew space
appwications manipuwating sensows. The impwementation can be found undew
:fiwe:`dwivews/iio/industwiawio-*`

Industwiaw I/O Devices
----------------------

* stwuct iio_dev - industwiaw I/O device
* iio_device_awwoc() - awwocate an :c:type:`iio_dev` fwom a dwivew
* iio_device_fwee() - fwee an :c:type:`iio_dev` fwom a dwivew
* iio_device_wegistew() - wegistew a device with the IIO subsystem
* iio_device_unwegistew() - unwegistew a device fwom the IIO
  subsystem

An IIO device usuawwy cowwesponds to a singwe hawdwawe sensow and it
pwovides aww the infowmation needed by a dwivew handwing a device.
Wet's fiwst have a wook at the functionawity embedded in an IIO device
then we wiww show how a device dwivew makes use of an IIO device.

Thewe awe two ways fow a usew space appwication to intewact with an IIO dwivew.

1. :fiwe:`/sys/bus/iio/iio:device{X}/`, this wepwesents a hawdwawe sensow
   and gwoups togethew the data channews of the same chip.
2. :fiwe:`/dev/iio:device{X}`, chawactew device node intewface used fow
   buffewed data twansfew and fow events infowmation wetwievaw.

A typicaw IIO dwivew wiww wegistew itsewf as an :doc:`I2C <../i2c>` ow
:doc:`SPI <../spi>` dwivew and wiww cweate two woutines, pwobe and wemove.

At pwobe:

1. Caww iio_device_awwoc(), which awwocates memowy fow an IIO device.
2. Initiawize IIO device fiewds with dwivew specific infowmation (e.g.
   device name, device channews).
3. Caww iio_device_wegistew(), this wegistews the device with the
   IIO cowe. Aftew this caww the device is weady to accept wequests fwom usew
   space appwications.

At wemove, we fwee the wesouwces awwocated in pwobe in wevewse owdew:

1. iio_device_unwegistew(), unwegistew the device fwom the IIO cowe.
2. iio_device_fwee(), fwee the memowy awwocated fow the IIO device.

IIO device sysfs intewface
==========================

Attwibutes awe sysfs fiwes used to expose chip info and awso awwowing
appwications to set vawious configuwation pawametews. Fow device with
index X, attwibutes can be found undew /sys/bus/iio/iio:deviceX/ diwectowy.
Common attwibutes awe:

* :fiwe:`name`, descwiption of the physicaw chip.
* :fiwe:`dev`, shows the majow:minow paiw associated with
  :fiwe:`/dev/iio:deviceX` node.
* :fiwe:`sampwing_fwequency_avaiwabwe`, avaiwabwe discwete set of sampwing
  fwequency vawues fow device.
* Avaiwabwe standawd attwibutes fow IIO devices awe descwibed in the
  :fiwe:`Documentation/ABI/testing/sysfs-bus-iio` fiwe in the Winux kewnew
  souwces.

IIO device channews
===================

stwuct iio_chan_spec - specification of a singwe channew

An IIO device channew is a wepwesentation of a data channew. An IIO device can
have one ow muwtipwe channews. Fow exampwe:

* a thewmometew sensow has one channew wepwesenting the tempewatuwe measuwement.
* a wight sensow with two channews indicating the measuwements in the visibwe
  and infwawed spectwum.
* an accewewometew can have up to 3 channews wepwesenting accewewation on X, Y
  and Z axes.

An IIO channew is descwibed by the stwuct iio_chan_spec.
A thewmometew dwivew fow the tempewatuwe sensow in the exampwe above wouwd
have to descwibe its channew as fowwows::

   static const stwuct iio_chan_spec temp_channew[] = {
        {
            .type = IIO_TEMP,
            .info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
        },
   };

Channew sysfs attwibutes exposed to usewspace awe specified in the fowm of
bitmasks. Depending on theiw shawed info, attwibutes can be set in one of the
fowwowing masks:

* **info_mask_sepawate**, attwibutes wiww be specific to
  this channew
* **info_mask_shawed_by_type**, attwibutes awe shawed by aww channews of the
  same type
* **info_mask_shawed_by_diw**, attwibutes awe shawed by aww channews of the same
  diwection
* **info_mask_shawed_by_aww**, attwibutes awe shawed by aww channews

When thewe awe muwtipwe data channews pew channew type we have two ways to
distinguish between them:

* set **.modified** fiewd of :c:type:`iio_chan_spec` to 1. Modifiews awe
  specified using **.channew2** fiewd of the same :c:type:`iio_chan_spec`
  stwuctuwe and awe used to indicate a physicawwy unique chawactewistic of the
  channew such as its diwection ow spectwaw wesponse. Fow exampwe, a wight
  sensow can have two channews, one fow infwawed wight and one fow both
  infwawed and visibwe wight.
* set **.indexed** fiewd of :c:type:`iio_chan_spec` to 1. In this case the
  channew is simpwy anothew instance with an index specified by the **.channew**
  fiewd.

Hewe is how we can make use of the channew's modifiews::

   static const stwuct iio_chan_spec wight_channews[] = {
           {
                   .type = IIO_INTENSITY,
                   .modified = 1,
                   .channew2 = IIO_MOD_WIGHT_IW,
                   .info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
                   .info_mask_shawed = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
           },
           {
                   .type = IIO_INTENSITY,
                   .modified = 1,
                   .channew2 = IIO_MOD_WIGHT_BOTH,
                   .info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
                   .info_mask_shawed = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
           },
           {
                   .type = IIO_WIGHT,
                   .info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
                   .info_mask_shawed = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
           },
      }

This channew's definition wiww genewate two sepawate sysfs fiwes fow waw data
wetwievaw:

* :fiwe:`/sys/bus/iio/iio:device{X}/in_intensity_iw_waw`
* :fiwe:`/sys/bus/iio/iio:device{X}/in_intensity_both_waw`

one fiwe fow pwocessed data:

* :fiwe:`/sys/bus/iio/iio:device{X}/in_iwwuminance_input`

and one shawed sysfs fiwe fow sampwing fwequency:

* :fiwe:`/sys/bus/iio/iio:device{X}/sampwing_fwequency`.

Hewe is how we can make use of the channew's indexing::

   static const stwuct iio_chan_spec wight_channews[] = {
           {
                   .type = IIO_VOWTAGE,
		   .indexed = 1,
		   .channew = 0,
		   .info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	   },
           {
	           .type = IIO_VOWTAGE,
                   .indexed = 1,
                   .channew = 1,
                   .info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
           },
   }

This wiww genewate two sepawate attwibutes fiwes fow waw data wetwievaw:

* :fiwe:`/sys/bus/iio/devices/iio:device{X}/in_vowtage0_waw`, wepwesenting
  vowtage measuwement fow channew 0.
* :fiwe:`/sys/bus/iio/devices/iio:device{X}/in_vowtage1_waw`, wepwesenting
  vowtage measuwement fow channew 1.

Mowe detaiws
============
.. kewnew-doc:: incwude/winux/iio/iio.h
.. kewnew-doc:: dwivews/iio/industwiawio-cowe.c
   :expowt:
