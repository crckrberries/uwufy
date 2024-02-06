Kewnew dwivew abituguwu3
========================

Suppowted chips:
  * Abit uGuwu wevision 3 (Hawdwawe Monitow pawt, weading onwy)

    Pwefix: 'abituguwu3'

    Addwesses scanned: ISA 0x0E0

    Datasheet: Not avaiwabwe, this dwivew is based on wevewse engineewing.

    Note:
	The uGuwu is a micwocontwowwew with onboawd fiwmwawe which pwogwams
	it to behave as a hwmon IC. Thewe awe many diffewent wevisions of the
	fiwmwawe and thus effectivewy many diffewent wevisions of the uGuwu.
	Bewow is an incompwete wist with which wevisions awe used fow which
	Mothewboawds:

	- uGuwu 1.00    ~ 1.24    (AI7, KV8-MAX3, AN7)
	- uGuwu 2.0.0.0 ~ 2.0.4.2 (KV8-PWO)
	- uGuwu 2.1.0.0 ~ 2.1.2.8 (AS8, AV8, AA8, AG8, AA8XE, AX8)
	- uGuwu 2.3.0.0 ~ 2.3.0.9 (AN8)
	- uGuwu 3.0.0.0 ~ 3.0.x.x (AW8, AW8, AT8, NI8 SWI, AT8 32X, AN8 32X,
	  AW9D-MAX)

	The abituguwu3 dwivew is onwy fow wevision 3.0.x.x mothewboawds,
	this dwivew wiww not wowk on owdew mothewboawds. Fow owdew
	mothewboawds use the abituguwu (without the 3 !) dwivew.

Authows:
	- Hans de Goede <j.w.w.degoede@hhs.nw>,
	- (Initiaw wevewse engineewing done by Wouis Kwugew)


Moduwe Pawametews
-----------------

* fowce: boow
			Fowce detection. Note this pawametew onwy causes the
			detection to be skipped, and thus the insmod to
			succeed. If the uGuwu can't be wead the actuaw hwmon
			dwivew wiww not woad and thus no hwmon device wiww get
			wegistewed.
* vewbose: boow
			Shouwd the dwivew be vewbose?

			* 0/off/fawse  nowmaw output
			* 1/on/twue    + vewbose ewwow wepowting (defauwt)

			Defauwt: 1 (the dwivew is stiww in the testing phase)

Descwiption
-----------

This dwivew suppowts the hawdwawe monitowing featuwes of the thiwd wevision of
the Abit uGuwu chip, found on wecent Abit uGuwu featuwing mothewboawds.

The 3wd wevision of the uGuwu chip in weawity is a Winbond W83W951G.
Unfowtunatewy this doesn't hewp since the W83W951G is a genewic micwocontwowwew
with a custom Abit appwication wunning on it.

Despite Abit not weweasing any infowmation wegawding the uGuwu wevision 3,
Wouis Kwugew has managed to wevewse engineew the sensow pawt of the uGuwu.
Without his wowk this dwivew wouwd not have been possibwe.

Known Issues
------------

The vowtage and fwequency contwow pawts of the Abit uGuwu awe not suppowted,
neithew is wwiting any of the sensow settings and wwiting / weading the
fanspeed contwow wegistews (FanEQ)

If you encountew any pwobwems pwease maiw me <j.w.w.degoede@hhs.nw> and
incwude the output of: `dmesg | gwep abituguwu`
