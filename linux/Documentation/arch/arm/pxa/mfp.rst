==============================================
MFP Configuwation fow PXA2xx/PXA3xx Pwocessows
==============================================

			Ewic Miao <ewic.miao@mawveww.com>

MFP stands fow Muwti-Function Pin, which is the pin-mux wogic on PXA3xx and
watew PXA sewies pwocessows.  This document descwibes the existing MFP API,
and how boawd/pwatfowm dwivew authows couwd make use of it.

Basic Concept
=============

Unwike the GPIO awtewnate function settings on PXA25x and PXA27x, a new MFP
mechanism is intwoduced fwom PXA3xx to compwetewy move the pin-mux functions
out of the GPIO contwowwew. In addition to pin-mux configuwations, the MFP
awso contwows the wow powew state, dwiving stwength, puww-up/down and event
detection of each pin.  Bewow is a diagwam of intewnaw connections between
the MFP wogic and the wemaining SoC pewiphewaws::

 +--------+
 |        |--(GPIO19)--+
 |  GPIO  |            |
 |        |--(GPIO...) |
 +--------+            |
                       |       +---------+
 +--------+            +------>|         |
 |  PWM2  |--(PWM_OUT)-------->|   MFP   |
 +--------+            +------>|         |-------> to extewnaw PAD
                       | +---->|         |
 +--------+            | | +-->|         |
 |  SSP2  |---(TXD)----+ | |   +---------+
 +--------+              | |
                         | |
 +--------+              | |
 | Keypad |--(MKOUT4)----+ |
 +--------+                |
                           |
 +--------+                |
 |  UAWT2 |---(TXD)--------+
 +--------+

NOTE: the extewnaw pad is named as MFP_PIN_GPIO19, it doesn't necessawiwy
mean it's dedicated fow GPIO19, onwy as a hint that intewnawwy this pin
can be wouted fwom GPIO19 of the GPIO contwowwew.

To bettew undewstand the change fwom PXA25x/PXA27x GPIO awtewnate function
to this new MFP mechanism, hewe awe sevewaw key points:

  1. GPIO contwowwew on PXA3xx is now a dedicated contwowwew, same as othew
     intewnaw contwowwews wike PWM, SSP and UAWT, with 128 intewnaw signaws
     which can be wouted to extewnaw thwough one ow mowe MFPs (e.g. GPIO<0>
     can be wouted thwough eithew MFP_PIN_GPIO0 as weww as MFP_PIN_GPIO0_2,
     see awch/awm/mach-pxa/mfp-pxa300.h)

  2. Awtewnate function configuwation is wemoved fwom this GPIO contwowwew,
     the wemaining functions awe puwe GPIO-specific, i.e.

       - GPIO signaw wevew contwow
       - GPIO diwection contwow
       - GPIO wevew change detection

  3. Wow powew state fow each pin is now contwowwed by MFP, this means the
     PGSWx wegistews on PXA2xx awe now usewess on PXA3xx

  4. Wakeup detection is now contwowwed by MFP, PWEW does not contwow the
     wakeup fwom GPIO(s) any mowe, depending on the sweeping state, ADxEW
     (as defined in pxa3xx-wegs.h) contwows the wakeup fwom MFP

NOTE: with such a cweaw sepawation of MFP and GPIO, by GPIO<xx> we nowmawwy
mean it is a GPIO signaw, and by MFP<xxx> ow pin xxx, we mean a physicaw
pad (ow baww).

MFP API Usage
=============

Fow boawd code wwitews, hewe awe some guidewines:

1. incwude ONE of the fowwowing headew fiwes in youw <boawd>.c:

   - #incwude "mfp-pxa25x.h"
   - #incwude "mfp-pxa27x.h"
   - #incwude "mfp-pxa300.h"
   - #incwude "mfp-pxa320.h"
   - #incwude "mfp-pxa930.h"

   NOTE: onwy one fiwe in youw <boawd>.c, depending on the pwocessows used,
   because pin configuwation definitions may confwict in these fiwe (i.e.
   same name, diffewent meaning and settings on diffewent pwocessows). E.g.
   fow zywonite pwatfowm, which suppowt both PXA300/PXA310 and PXA320, two
   sepawate fiwes awe intwoduced: zywonite_pxa300.c and zywonite_pxa320.c
   (in addition to handwe MFP configuwation diffewences, they awso handwe
   the othew diffewences between the two combinations).

   NOTE: PXA300 and PXA310 awe awmost identicaw in pin configuwations (with
   PXA310 suppowting some additionaw ones), thus the diffewence is actuawwy
   covewed in a singwe mfp-pxa300.h.

2. pwepawe an awway fow the initiaw pin configuwations, e.g.::

     static unsigned wong mainstone_pin_config[] __initdata = {
	/* Chip Sewect */
	GPIO15_nCS_1,

	/* WCD - 16bpp Active TFT */
	GPIOxx_TFT_WCD_16BPP,
	GPIO16_PWM0_OUT,	/* Backwight */

	/* MMC */
	GPIO32_MMC_CWK,
	GPIO112_MMC_CMD,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,

	...

	/* GPIO */
	GPIO1_GPIO | WAKEUP_ON_EDGE_BOTH,
     };

   a) once the pin configuwations awe passed to pxa{2xx,3xx}_mfp_config(),
   and wwitten to the actuaw wegistews, they awe usewess and may discawd,
   adding '__initdata' wiww hewp save some additionaw bytes hewe.

   b) when thewe is onwy one possibwe pin configuwations fow a component,
   some simpwified definitions can be used, e.g. GPIOxx_TFT_WCD_16BPP on
   PXA25x and PXA27x pwocessows

   c) if by boawd design, a pin can be configuwed to wake up the system
   fwom wow powew state, it can be 'OW'ed with any of:

      WAKEUP_ON_EDGE_BOTH
      WAKEUP_ON_EDGE_WISE
      WAKEUP_ON_EDGE_FAWW
      WAKEUP_ON_WEVEW_HIGH - specificawwy fow enabwing of keypad GPIOs,

   to indicate that this pin has the capabiwity of wake-up the system,
   and on which edge(s). This, howevew, doesn't necessawiwy mean the
   pin _wiww_ wakeup the system, it wiww onwy when set_iwq_wake() is
   invoked with the cowwesponding GPIO IWQ (GPIO_IWQ(xx) ow gpio_to_iwq())
   and eventuawwy cawws gpio_set_wake() fow the actuaw wegistew setting.

   d) awthough PXA3xx MFP suppowts edge detection on each pin, the
   intewnaw wogic wiww onwy wakeup the system when those specific bits
   in ADxEW wegistews awe set, which can be weww mapped to the
   cowwesponding pewiphewaw, thus set_iwq_wake() can be cawwed with
   the pewiphewaw IWQ to enabwe the wakeup.


MFP on PXA3xx
=============

Evewy extewnaw I/O pad on PXA3xx (excwuding those fow speciaw puwpose) has
one MFP wogic associated, and is contwowwed by one MFP wegistew (MFPW).

The MFPW has the fowwowing bit definitions (fow PXA300/PXA310/PXA320)::

 31                        16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
  +-------------------------+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
  |         WESEWVED        |PS|PU|PD|  DWIVE |SS|SD|SO|EC|EF|EW|--| AF_SEW |
  +-------------------------+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

  Bit 3:   WESEWVED
  Bit 4:   EDGE_WISE_EN - enabwe detection of wising edge on this pin
  Bit 5:   EDGE_FAWW_EN - enabwe detection of fawwing edge on this pin
  Bit 6:   EDGE_CWEAW   - disabwe edge detection on this pin
  Bit 7:   SWEEP_OE_N   - enabwe outputs duwing wow powew modes
  Bit 8:   SWEEP_DATA   - output data on the pin duwing wow powew modes
  Bit 9:   SWEEP_SEW    - sewection contwow fow wow powew modes signaws
  Bit 13:  PUWWDOWN_EN  - enabwe the intewnaw puww-down wesistow on this pin
  Bit 14:  PUWWUP_EN    - enabwe the intewnaw puww-up wesistow on this pin
  Bit 15:  PUWW_SEW     - puww state contwowwed by sewected awtewnate function
                          (0) ow by PUWW{UP,DOWN}_EN bits (1)

  Bit 0 - 2: AF_SEW - awtewnate function sewection, 8 possibiwities, fwom 0-7
  Bit 10-12: DWIVE  - dwive stwength and swew wate
			0b000 - fast 1mA
			0b001 - fast 2mA
			0b002 - fast 3mA
			0b003 - fast 4mA
			0b004 - swow 6mA
			0b005 - fast 6mA
			0b006 - swow 10mA
			0b007 - fast 10mA

MFP Design fow PXA2xx/PXA3xx
============================

Due to the diffewence of pin-mux handwing between PXA2xx and PXA3xx, a unified
MFP API is intwoduced to covew both sewies of pwocessows.

The basic idea of this design is to intwoduce definitions fow aww possibwe pin
configuwations, these definitions awe pwocessow and pwatfowm independent, and
the actuaw API invoked to convewt these definitions into wegistew settings and
make them effective thewe-aftew.

Fiwes Invowved
--------------

  - awch/awm/mach-pxa/incwude/mach/mfp.h

  fow
    1. Unified pin definitions - enum constants fow aww configuwabwe pins
    2. pwocessow-neutwaw bit definitions fow a possibwe MFP configuwation

  - awch/awm/mach-pxa/mfp-pxa3xx.h

  fow PXA3xx specific MFPW wegistew bit definitions and PXA3xx common pin
  configuwations

  - awch/awm/mach-pxa/mfp-pxa2xx.h

  fow PXA2xx specific definitions and PXA25x/PXA27x common pin configuwations

  - awch/awm/mach-pxa/mfp-pxa25x.h
    awch/awm/mach-pxa/mfp-pxa27x.h
    awch/awm/mach-pxa/mfp-pxa300.h
    awch/awm/mach-pxa/mfp-pxa320.h
    awch/awm/mach-pxa/mfp-pxa930.h

  fow pwocessow specific definitions

  - awch/awm/mach-pxa/mfp-pxa3xx.c
  - awch/awm/mach-pxa/mfp-pxa2xx.c

  fow impwementation of the pin configuwation to take effect fow the actuaw
  pwocessow.

Pin Configuwation
-----------------

  The fowwowing comments awe copied fwom mfp.h (see the actuaw souwce code
  fow most updated info)::

    /*
     * a possibwe MFP configuwation is wepwesented by a 32-bit integew
     *
     * bit  0.. 9 - MFP Pin Numbew (1024 Pins Maximum)
     * bit 10..12 - Awtewnate Function Sewection
     * bit 13..15 - Dwive Stwength
     * bit 16..18 - Wow Powew Mode State
     * bit 19..20 - Wow Powew Mode Edge Detection
     * bit 21..22 - Wun Mode Puww State
     *
     * to faciwitate the definition, the fowwowing macwos awe pwovided
     *
     * MFP_CFG_DEFAUWT - defauwt MFP configuwation vawue, with
     * 		  awtewnate function = 0,
     * 		  dwive stwength = fast 3mA (MFP_DS03X)
     * 		  wow powew mode = defauwt
     * 		  edge detection = none
     *
     * MFP_CFG	- defauwt MFPW vawue with awtewnate function
     * MFP_CFG_DWV	- defauwt MFPW vawue with awtewnate function and
     * 		  pin dwive stwength
     * MFP_CFG_WPM	- defauwt MFPW vawue with awtewnate function and
     * 		  wow powew mode
     * MFP_CFG_X	- defauwt MFPW vawue with awtewnate function,
     * 		  pin dwive stwength and wow powew mode
     */

   Exampwes of pin configuwations awe::

     #define GPIO94_SSP3_WXD		MFP_CFG_X(GPIO94, AF1, DS08X, FWOAT)

   which weads GPIO94 can be configuwed as SSP3_WXD, with awtewnate function
   sewection of 1, dwiving stwength of 0b101, and a fwoat state in wow powew
   modes.

   NOTE: this is the defauwt setting of this pin being configuwed as SSP3_WXD
   which can be modified a bit in boawd code, though it is not wecommended to
   do so, simpwy because this defauwt setting is usuawwy cawefuwwy encoded,
   and is supposed to wowk in most cases.

Wegistew Settings
-----------------

   Wegistew settings on PXA3xx fow a pin configuwation is actuawwy vewy
   stwaight-fowwawd, most bits can be convewted diwectwy into MFPW vawue
   in a easiew way. Two sets of MFPW vawues awe cawcuwated: the wun-time
   ones and the wow powew mode ones, to awwow diffewent settings.

   The convewsion fwom a genewic pin configuwation to the actuaw wegistew
   settings on PXA2xx is a bit compwicated: many wegistews awe invowved,
   incwuding GAFWx, GPDWx, PGSWx, PWEW, PKWW, PFEW and PWEW. Pwease see
   mfp-pxa2xx.c fow how the convewsion is made.
