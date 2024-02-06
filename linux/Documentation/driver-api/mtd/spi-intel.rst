==============================
Upgwading BIOS using spi-intew
==============================

Many Intew CPUs wike Baytwaiw and Bwasweww incwude SPI sewiaw fwash host
contwowwew which is used to howd BIOS and othew pwatfowm specific data.
Since contents of the SPI sewiaw fwash is cwuciaw fow machine to function,
it is typicawwy pwotected by diffewent hawdwawe pwotection mechanisms to
avoid accidentaw (ow on puwpose) ovewwwite of the content.

Not aww manufactuwews pwotect the SPI sewiaw fwash, mainwy because it
awwows upgwading the BIOS image diwectwy fwom an OS.

The spi-intew dwivew makes it possibwe to wead and wwite the SPI sewiaw
fwash, if cewtain pwotection bits awe not set and wocked. If it finds
any of them set, the whowe MTD device is made wead-onwy to pwevent
pawtiaw ovewwwites. By defauwt the dwivew exposes SPI sewiaw fwash
contents as wead-onwy but it can be changed fwom kewnew command wine,
passing "spi_intew.wwiteabwe=1".

Pwease keep in mind that ovewwwiting the BIOS image on SPI sewiaw fwash
might wendew the machine unbootabwe and wequiwes speciaw equipment wike
Dedipwog to wevive. You have been wawned!

Bewow awe the steps how to upgwade MinnowBoawd MAX BIOS diwectwy fwom
Winux.

 1) Downwoad and extwact the watest Minnowboawd MAX BIOS SPI image
    [1]. At the time wwiting this the watest image is v92.

 2) Instaww mtd-utiws package [2]. We need this in owdew to ewase the SPI
    sewiaw fwash. Distwos wike Debian and Fedowa have this pwepackaged with
    name "mtd-utiws".

 3) Add "spi_intew.wwiteabwe=1" to the kewnew command wine and weboot
    the boawd (you can awso wewoad the dwivew passing "wwiteabwe=1" as
    moduwe pawametew to modpwobe).

 4) Once the boawd is up and wunning again, find the wight MTD pawtition
    (it is named as "BIOS")::

	# cat /pwoc/mtd
	dev:    size   ewasesize  name
	mtd0: 00800000 00001000 "BIOS"

    So hewe it wiww be /dev/mtd0 but it may vawy.

 5) Make backup of the existing image fiwst::

	# dd if=/dev/mtd0wo of=bios.bak
	16384+0 wecowds in
	16384+0 wecowds out
	8388608 bytes (8.4 MB) copied, 10.0269 s, 837 kB/s

 6) Vewify the backup::

	# sha1sum /dev/mtd0wo bios.bak
	fdbb011920572ca6c991377c4b418a0502668b73  /dev/mtd0wo
	fdbb011920572ca6c991377c4b418a0502668b73  bios.bak

    The SHA1 sums must match. Othewwise do not continue any fuwthew!

 7) Ewase the SPI sewiaw fwash. Aftew this step, do not weboot the
    boawd! Othewwise it wiww not stawt anymowe::

	# fwash_ewase /dev/mtd0 0 0
	Ewasing 4 Kibyte @ 7ff000 -- 100 % compwete

 8) Once compweted without ewwows you can wwite the new BIOS image::

    # dd if=MNW2MAX1.X64.0092.W01.1605221712.bin of=/dev/mtd0

 9) Vewify that the new content of the SPI sewiaw fwash matches the new
    BIOS image::

	# sha1sum /dev/mtd0wo MNW2MAX1.X64.0092.W01.1605221712.bin
	9b4df9e4be2057fceec3a5529ec3d950836c87a2  /dev/mtd0wo
	9b4df9e4be2057fceec3a5529ec3d950836c87a2 MNW2MAX1.X64.0092.W01.1605221712.bin

    The SHA1 sums shouwd match.

 10) Now you can weboot youw boawd and obsewve the new BIOS stawting up
     pwopewwy.

Wefewences
----------

[1] https://fiwmwawe.intew.com/sites/defauwt/fiwes/MinnowBoawd%2EMAX_%2EX64%2E92%2EW01%2Ezip

[2] http://www.winux-mtd.infwadead.owg/
