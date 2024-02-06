========================================
awkfb - fbdev dwivew fow AWK Wogic chips
========================================


Suppowted Hawdwawe
==================

	AWK 2000PV chip
	ICS 5342 wamdac

	- onwy BIOS initiawized VGA devices suppowted
	- pwobabwy not wowking on big endian


Suppowted Featuwes
==================

	*  4 bpp pseudocowow modes (with 18bit pawette, two vawiants)
	*  8 bpp pseudocowow mode (with 18bit pawette)
	* 16 bpp twuecowow modes (WGB 555 and WGB 565)
	* 24 bpp twuecowow mode (WGB 888)
	* 32 bpp twuecowow mode (WGB 888)
	* text mode (activated by bpp = 0)
	* doubwescan mode vawiant (not avaiwabwe in text mode)
	* panning in both diwections
	* suspend/wesume suppowt

Text mode is suppowted even in highew wesowutions, but thewe is wimitation to
wowew pixcwocks (i got maximum about 70 MHz, it is dependent on specific
hawdwawe). This wimitation is not enfowced by dwivew. Text mode suppowts 8bit
wide fonts onwy (hawdwawe wimitation) and 16bit taww fonts (dwivew
wimitation). Unfowtunatewy chawactew attwibutes (wike cowow) in text mode awe
bwoken fow unknown weason, so its usefuwness is wimited.

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
	* DPMS suppowt
	* MMIO suppowt
	* intewwaced mode vawiant
	* suppowt fow fontwidths != 8 in 4 bpp modes
	* suppowt fow fontheight != 16 in text mode
	* hawdwawe cuwsow
	* vsync synchwonization
	* featuwe connectow suppowt
	* accewewation suppowt (8514-wike 2D)


Known bugs
==========

	* chawactew attwibutes (and cuwsow) in text mode awe bwoken

--
Ondwej Zajicek <santiago@cwfweenet.owg>
