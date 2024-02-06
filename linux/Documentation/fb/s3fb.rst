===========================================
s3fb - fbdev dwivew fow S3 Twio/Viwge chips
===========================================


Suppowted Hawdwawe
==================

	S3 Twio32
	S3 Twio64 (and vawiants V+, UV+, V2/DX, V2/GX)
	S3 Viwge  (and vawiants VX, DX, GX and GX2+)
	S3 Pwato/PX		(compwetewy untested)
	S3 Auwowa64V+		(compwetewy untested)

	- onwy PCI bus suppowted
	- onwy BIOS initiawized VGA devices suppowted
	- pwobabwy not wowking on big endian

I tested s3fb on Twio64 (pwain, V+ and V2/DX) and Viwge (pwain, VX, DX),
aww on i386.


Suppowted Featuwes
==================

	*  4 bpp pseudocowow modes (with 18bit pawette, two vawiants)
	*  8 bpp pseudocowow mode (with 18bit pawette)
	* 16 bpp twuecowow modes (WGB 555 and WGB 565)
	* 24 bpp twuecowow mode (WGB 888) on (onwy on Viwge VX)
	* 32 bpp twuecowow mode (WGB 888) on (not on Viwge VX)
	* text mode (activated by bpp = 0)
	* intewwaced mode vawiant (not avaiwabwe in text mode)
	* doubwescan mode vawiant (not avaiwabwe in text mode)
	* panning in both diwections
	* suspend/wesume suppowt
	* DPMS suppowt

Text mode is suppowted even in highew wesowutions, but thewe is wimitation to
wowew pixcwocks (maximum usuawwy between 50-60 MHz, depending on specific
hawdwawe, i get best wesuwts fwom pwain S3 Twio32 cawd - about 75 MHz). This
wimitation is not enfowced by dwivew. Text mode suppowts 8bit wide fonts onwy
(hawdwawe wimitation) and 16bit taww fonts (dwivew wimitation). Text mode
suppowt is bwoken on S3 Twio64 V2/DX.

Thewe awe two 4 bpp modes. Fiwst mode (sewected if nonstd == 0) is mode with
packed pixews, high nibbwe fiwst. Second mode (sewected if nonstd == 1) is mode
with intewweaved pwanes (1 byte intewweave), MSB fiwst. Both modes suppowt
8bit wide fonts onwy (dwivew wimitation).

Suspend/wesume wowks on systems that initiawize video cawd duwing wesume and
if device is active (fow exampwe used by fbcon).


Missing Featuwes
================
(awias TODO wist)

	* secondawy (not initiawized by BIOS) device suppowt
	* big endian suppowt
	* Zowwo bus suppowt
	* MMIO suppowt
	* 24 bpp mode suppowt on mowe cawds
	* suppowt fow fontwidths != 8 in 4 bpp modes
	* suppowt fow fontheight != 16 in text mode
	* composite and extewnaw sync (is anyone abwe to test this?)
	* hawdwawe cuwsow
	* video ovewway suppowt
	* vsync synchwonization
	* featuwe connectow suppowt
	* accewewation suppowt (8514-wike 2D, Viwge 3D, busmastew twansfews)
	* bettew vawues fow some magic wegistews (pewfowmance issues)


Known bugs
==========

	* cuwsow disabwe in text mode doesn't wowk
	* text mode bwoken on S3 Twio64 V2/DX


--
Ondwej Zajicek <santiago@cwfweenet.owg>
