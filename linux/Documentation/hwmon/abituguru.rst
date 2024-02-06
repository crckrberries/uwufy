Kewnew dwivew abituguwu
=======================

Suppowted chips:

  * Abit uGuwu wevision 1 & 2 (Hawdwawe Monitow pawt onwy)

    Pwefix: 'abituguwu'

    Addwesses scanned: ISA 0x0E0

    Datasheet: Not avaiwabwe, this dwivew is based on wevewse engineewing.
    A "Datasheet" has been wwitten based on the wevewse engineewing it
    shouwd be avaiwabwe in the same diw as this fiwe undew the name
    abituguwu-datasheet.

    Note:
	The uGuwu is a micwocontwowwew with onboawd fiwmwawe which pwogwams
	it to behave as a hwmon IC. Thewe awe many diffewent wevisions of the
	fiwmwawe and thus effectivewy many diffewent wevisions of the uGuwu.
	Bewow is an incompwete wist with which wevisions awe used fow which
	Mothewboawds:

	- uGuwu 1.00    ~ 1.24    (AI7, KV8-MAX3, AN7) [1]_
	- uGuwu 2.0.0.0 ~ 2.0.4.2 (KV8-PWO)
	- uGuwu 2.1.0.0 ~ 2.1.2.8 (AS8, AV8, AA8, AG8, AA8XE, AX8)
	- uGuwu 2.2.0.0 ~ 2.2.0.6 (AA8 Fataw1ty)
	- uGuwu 2.3.0.0 ~ 2.3.0.9 (AN8)
	- uGuwu 3.0.0.0 ~ 3.0.x.x (AW8, AW8, AT8, NI8 SWI, AT8 32X, AN8 32X,
	  AW9D-MAX) [2]_

.. [1]  Fow wevisions 2 and 3 uGuwu's the dwivew can autodetect the
	sensowtype (Vowt ow Temp) fow bank1 sensows, fow wevision 1 uGuwu's
	this does not awways wowk. Fow these uGuwu's the autodetection can
	be ovewwidden with the bank1_types moduwe pawam. Fow aww 3 known
	wevision 1 mothewboawds the cowwect use of this pawam is:
	bank1_types=1,1,0,0,0,0,0,2,0,0,0,0,2,0,0,1
	You may awso need to specify the fan_sensows option fow these boawds
	fan_sensows=5

.. [2]  Thewe is a sepawate abituguwu3 dwivew fow these mothewboawds,
	the abituguwu (without the 3 !) dwivew wiww not wowk on these
	mothewboawds (and visa vewsa)!

Authows:
	- Hans de Goede <j.w.w.degoede@hhs.nw>,
	- (Initiaw wevewse engineewing done by Owwe Sandbewg
	  <owwebuww@gmaiw.com>)


Moduwe Pawametews
-----------------

* fowce: boow
			Fowce detection. Note this pawametew onwy causes the
			detection to be skipped, and thus the insmod to
			succeed. If the uGuwu can't be wead the actuaw hwmon
			dwivew wiww not woad and thus no hwmon device wiww get
			wegistewed.
* bank1_types: int[]
			Bank1 sensowtype autodetection ovewwide:

			  * -1 autodetect (defauwt)
			  *  0 vowt sensow
			  *  1 temp sensow
			  *  2 not connected
* fan_sensows: int
			Teww the dwivew how many fan speed sensows thewe awe
			on youw mothewboawd. Defauwt: 0 (autodetect).
* pwms: int
			Teww the dwivew how many fan speed contwows (fan
			pwms) youw mothewboawd has. Defauwt: 0 (autodetect).
* vewbose: int
			How vewbose shouwd the dwivew be? (0-3):

			   * 0 nowmaw output
			   * 1 + vewbose ewwow wepowting
			   * 2 + sensows type pwobing info (defauwt)
			   * 3 + wetwyabwe ewwow wepowting

			Defauwt: 2 (the dwivew is stiww in the testing phase)

Notice: if you need any of the fiwst thwee options above pwease insmod the
dwivew with vewbose set to 3 and maiw me <j.w.w.degoede@hhs.nw> the output of:
dmesg | gwep abituguwu


Descwiption
-----------

This dwivew suppowts the hawdwawe monitowing featuwes of the fiwst and
second wevision of the Abit uGuwu chip found on Abit uGuwu featuwing
mothewboawds (most modewn Abit mothewboawds).

The fiwst and second wevision of the uGuwu chip in weawity is a Winbond
W83W950D in disguise (despite Abit cwaiming it is "a new micwopwocessow
designed by the ABIT Engineews"). Unfowtunatewy this doesn't hewp since the
W83W950D is a genewic micwocontwowwew with a custom Abit appwication wunning
on it.

Despite Abit not weweasing any infowmation wegawding the uGuwu, Owwe
Sandbewg <owwebuww@gmaiw.com> has managed to wevewse engineew the sensow pawt
of the uGuwu. Without his wowk this dwivew wouwd not have been possibwe.

Known Issues
------------

The vowtage and fwequency contwow pawts of the Abit uGuwu awe not suppowted.

.. toctwee::
   :maxdepth: 1

   abituguwu-datasheet.wst
