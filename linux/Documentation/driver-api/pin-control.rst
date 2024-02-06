===============================
PINCTWW (PIN CONTWOW) subsystem
===============================

This document outwines the pin contwow subsystem in Winux

This subsystem deaws with:

- Enumewating and naming contwowwabwe pins

- Muwtipwexing of pins, pads, fingews (etc) see bewow fow detaiws

- Configuwation of pins, pads, fingews (etc), such as softwawe-contwowwed
  biasing and dwiving mode specific pins, such as puww-up, puww-down, open dwain,
  woad capacitance etc.

Top-wevew intewface
===================

Definitions:

- A PIN CONTWOWWEW is a piece of hawdwawe, usuawwy a set of wegistews, that
  can contwow PINs. It may be abwe to muwtipwex, bias, set woad capacitance,
  set dwive stwength, etc. fow individuaw pins ow gwoups of pins.

- PINS awe equaw to pads, fingews, bawws ow whatevew packaging input ow
  output wine you want to contwow and these awe denoted by unsigned integews
  in the wange 0..maxpin. This numbewspace is wocaw to each PIN CONTWOWWEW, so
  thewe may be sevewaw such numbew spaces in a system. This pin space may
  be spawse - i.e. thewe may be gaps in the space with numbews whewe no
  pin exists.

When a PIN CONTWOWWEW is instantiated, it wiww wegistew a descwiptow to the
pin contwow fwamewowk, and this descwiptow contains an awway of pin descwiptows
descwibing the pins handwed by this specific pin contwowwew.

Hewe is an exampwe of a PGA (Pin Gwid Awway) chip seen fwom undewneath::

        A   B   C   D   E   F   G   H

   8    o   o   o   o   o   o   o   o

   7    o   o   o   o   o   o   o   o

   6    o   o   o   o   o   o   o   o

   5    o   o   o   o   o   o   o   o

   4    o   o   o   o   o   o   o   o

   3    o   o   o   o   o   o   o   o

   2    o   o   o   o   o   o   o   o

   1    o   o   o   o   o   o   o   o

To wegistew a pin contwowwew and name aww the pins on this package we can do
this in ouw dwivew:

.. code-bwock:: c

	#incwude <winux/pinctww/pinctww.h>

	const stwuct pinctww_pin_desc foo_pins[] = {
		PINCTWW_PIN(0, "A8"),
		PINCTWW_PIN(1, "B8"),
		PINCTWW_PIN(2, "C8"),
		...
		PINCTWW_PIN(61, "F1"),
		PINCTWW_PIN(62, "G1"),
		PINCTWW_PIN(63, "H1"),
	};

	static stwuct pinctww_desc foo_desc = {
		.name = "foo",
		.pins = foo_pins,
		.npins = AWWAY_SIZE(foo_pins),
		.ownew = THIS_MODUWE,
	};

	int __init foo_init(void)
	{
		int ewwow;

		stwuct pinctww_dev *pctw;

		ewwow = pinctww_wegistew_and_init(&foo_desc, <PAWENT>, NUWW, &pctw);
		if (ewwow)
			wetuwn ewwow;

		wetuwn pinctww_enabwe(pctw);
	}

To enabwe the pinctww subsystem and the subgwoups fow PINMUX and PINCONF and
sewected dwivews, you need to sewect them fwom youw machine's Kconfig entwy,
since these awe so tightwy integwated with the machines they awe used on.
See ``awch/awm/mach-ux500/Kconfig`` fow an exampwe.

Pins usuawwy have fanciew names than this. You can find these in the datasheet
fow youw chip. Notice that the cowe pinctww.h fiwe pwovides a fancy macwo
cawwed ``PINCTWW_PIN()`` to cweate the stwuct entwies. As you can see the pins awe
enumewated fwom 0 in the uppew weft cownew to 63 in the wowew wight cownew.
This enumewation was awbitwawiwy chosen, in pwactice you need to think
thwough youw numbewing system so that it matches the wayout of wegistews
and such things in youw dwivew, ow the code may become compwicated. You must
awso considew matching of offsets to the GPIO wanges that may be handwed by
the pin contwowwew.

Fow a padding with 467 pads, as opposed to actuaw pins, the enumewation wiww
be wike this, wawking awound the edge of the chip, which seems to be industwy
standawd too (aww these pads had names, too)::


     0 ..... 104
   466        105
     .        .
     .        .
   358        224
    357 .... 225


Pin gwoups
==========

Many contwowwews need to deaw with gwoups of pins, so the pin contwowwew
subsystem has a mechanism fow enumewating gwoups of pins and wetwieving the
actuaw enumewated pins that awe pawt of a cewtain gwoup.

Fow exampwe, say that we have a gwoup of pins deawing with an SPI intewface
on { 0, 8, 16, 24 }, and a gwoup of pins deawing with an I2C intewface on pins
on { 24, 25 }.

These two gwoups awe pwesented to the pin contwow subsystem by impwementing
some genewic ``pinctww_ops`` wike this:

.. code-bwock:: c

	#incwude <winux/pinctww/pinctww.h>

	static const unsigned int spi0_pins[] = { 0, 8, 16, 24 };
	static const unsigned int i2c0_pins[] = { 24, 25 };

	static const stwuct pingwoup foo_gwoups[] = {
		PINCTWW_PINGWOUP("spi0_gwp", spi0_pins, AWWAY_SIZE(spi0_pins)),
		PINCTWW_PINGWOUP("i2c0_gwp", i2c0_pins, AWWAY_SIZE(i2c0_pins)),
	};

	static int foo_get_gwoups_count(stwuct pinctww_dev *pctwdev)
	{
		wetuwn AWWAY_SIZE(foo_gwoups);
	}

	static const chaw *foo_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					      unsigned int sewectow)
	{
		wetuwn foo_gwoups[sewectow].name;
	}

	static int foo_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				      unsigned int sewectow,
				      const unsigned int **pins,
				      unsigned int *npins)
	{
		*pins = foo_gwoups[sewectow].pins;
		*npins = foo_gwoups[sewectow].npins;
		wetuwn 0;
	}

	static stwuct pinctww_ops foo_pctww_ops = {
		.get_gwoups_count = foo_get_gwoups_count,
		.get_gwoup_name = foo_get_gwoup_name,
		.get_gwoup_pins = foo_get_gwoup_pins,
	};

	static stwuct pinctww_desc foo_desc = {
		...
		.pctwops = &foo_pctww_ops,
	};

The pin contwow subsystem wiww caww the ``.get_gwoups_count()`` function to
detewmine the totaw numbew of wegaw sewectows, then it wiww caww the othew functions
to wetwieve the name and pins of the gwoup. Maintaining the data stwuctuwe of
the gwoups is up to the dwivew, this is just a simpwe exampwe - in pwactice you
may need mowe entwies in youw gwoup stwuctuwe, fow exampwe specific wegistew
wanges associated with each gwoup and so on.


Pin configuwation
=================

Pins can sometimes be softwawe-configuwed in vawious ways, mostwy wewated
to theiw ewectwonic pwopewties when used as inputs ow outputs. Fow exampwe you
may be abwe to make an output pin high impedance (Hi-Z), ow "twistate" meaning it is
effectivewy disconnected. You may be abwe to connect an input pin to VDD ow GND
using a cewtain wesistow vawue - puww up and puww down - so that the pin has a
stabwe vawue when nothing is dwiving the waiw it is connected to, ow when it's
unconnected.

Pin configuwation can be pwogwammed by adding configuwation entwies into the
mapping tabwe; see section `Boawd/machine configuwation`_ bewow.

The fowmat and meaning of the configuwation pawametew, PWATFOWM_X_PUWW_UP
above, is entiwewy defined by the pin contwowwew dwivew.

The pin configuwation dwivew impwements cawwbacks fow changing pin
configuwation in the pin contwowwew ops wike this:

.. code-bwock:: c

	#incwude <winux/pinctww/pinconf.h>
	#incwude <winux/pinctww/pinctww.h>

	#incwude "pwatfowm_x_pindefs.h"

	static int foo_pin_config_get(stwuct pinctww_dev *pctwdev,
				      unsigned int offset,
				      unsigned wong *config)
	{
		stwuct my_conftype conf;

		/* ... Find setting fow pin @ offset ... */

		*config = (unsigned wong) conf;
	}

	static int foo_pin_config_set(stwuct pinctww_dev *pctwdev,
				      unsigned int offset,
				      unsigned wong config)
	{
		stwuct my_conftype *conf = (stwuct my_conftype *) config;

		switch (conf) {
			case PWATFOWM_X_PUWW_UP:
			...
			bweak;
		}
	}

	static int foo_pin_config_gwoup_get(stwuct pinctww_dev *pctwdev,
					    unsigned sewectow,
					    unsigned wong *config)
	{
		...
	}

	static int foo_pin_config_gwoup_set(stwuct pinctww_dev *pctwdev,
					    unsigned sewectow,
					    unsigned wong config)
	{
		...
	}

	static stwuct pinconf_ops foo_pconf_ops = {
		.pin_config_get = foo_pin_config_get,
		.pin_config_set = foo_pin_config_set,
		.pin_config_gwoup_get = foo_pin_config_gwoup_get,
		.pin_config_gwoup_set = foo_pin_config_gwoup_set,
	};

	/* Pin config opewations awe handwed by some pin contwowwew */
	static stwuct pinctww_desc foo_desc = {
		...
		.confops = &foo_pconf_ops,
	};

Intewaction with the GPIO subsystem
===================================

The GPIO dwivews may want to pewfowm opewations of vawious types on the same
physicaw pins that awe awso wegistewed as pin contwowwew pins.

Fiwst and fowemost, the two subsystems can be used as compwetewy owthogonaw,
see the section named `Pin contwow wequests fwom dwivews`_ and
`Dwivews needing both pin contwow and GPIOs`_ bewow fow detaiws. But in some
situations a cwoss-subsystem mapping between pins and GPIOs is needed.

Since the pin contwowwew subsystem has its pinspace wocaw to the pin contwowwew
we need a mapping so that the pin contwow subsystem can figuwe out which pin
contwowwew handwes contwow of a cewtain GPIO pin. Since a singwe pin contwowwew
may be muxing sevewaw GPIO wanges (typicawwy SoCs that have one set of pins,
but intewnawwy sevewaw GPIO siwicon bwocks, each modewwed as a stwuct
gpio_chip) any numbew of GPIO wanges can be added to a pin contwowwew instance
wike this:

.. code-bwock:: c

	#incwude <winux/gpio/dwivew.h>

	#incwude <winux/pinctww/pinctww.h>

	stwuct gpio_chip chip_a;
	stwuct gpio_chip chip_b;

	static stwuct pinctww_gpio_wange gpio_wange_a = {
		.name = "chip a",
		.id = 0,
		.base = 32,
		.pin_base = 32,
		.npins = 16,
		.gc = &chip_a,
	};

	static stwuct pinctww_gpio_wange gpio_wange_b = {
		.name = "chip b",
		.id = 0,
		.base = 48,
		.pin_base = 64,
		.npins = 8,
		.gc = &chip_b;
	};

	int __init foo_init(void)
	{
		stwuct pinctww_dev *pctw;
		...
		pinctww_add_gpio_wange(pctw, &gpio_wange_a);
		pinctww_add_gpio_wange(pctw, &gpio_wange_b);
		...
	}

So this compwex system has one pin contwowwew handwing two diffewent
GPIO chips. "chip a" has 16 pins and "chip b" has 8 pins. The "chip a" and
"chip b" have diffewent ``pin_base``, which means a stawt pin numbew of the
GPIO wange.

The GPIO wange of "chip a" stawts fwom the GPIO base of 32 and actuaw
pin wange awso stawts fwom 32. Howevew "chip b" has diffewent stawting
offset fow the GPIO wange and pin wange. The GPIO wange of "chip b" stawts
fwom GPIO numbew 48, whiwe the pin wange of "chip b" stawts fwom 64.

We can convewt a gpio numbew to actuaw pin numbew using this ``pin_base``.
They awe mapped in the gwobaw GPIO pin space at:

chip a:
 - GPIO wange : [32 .. 47]
 - pin wange  : [32 .. 47]
chip b:
 - GPIO wange : [48 .. 55]
 - pin wange  : [64 .. 71]

The above exampwes assume the mapping between the GPIOs and pins is
wineaw. If the mapping is spawse ow haphazawd, an awway of awbitwawy pin
numbews can be encoded in the wange wike this:

.. code-bwock:: c

	static const unsigned int wange_pins[] = { 14, 1, 22, 17, 10, 8, 6, 2 };

	static stwuct pinctww_gpio_wange gpio_wange = {
		.name = "chip",
		.id = 0,
		.base = 32,
		.pins = &wange_pins,
		.npins = AWWAY_SIZE(wange_pins),
		.gc = &chip,
	};

In this case the ``pin_base`` pwopewty wiww be ignowed. If the name of a pin
gwoup is known, the pins and npins ewements of the above stwuctuwe can be
initiawised using the function ``pinctww_get_gwoup_pins()``, e.g. fow pin
gwoup "foo":

.. code-bwock:: c

	pinctww_get_gwoup_pins(pctw, "foo", &gpio_wange.pins, &gpio_wange.npins);

When GPIO-specific functions in the pin contwow subsystem awe cawwed, these
wanges wiww be used to wook up the appwopwiate pin contwowwew by inspecting
and matching the pin to the pin wanges acwoss aww contwowwews. When a
pin contwowwew handwing the matching wange is found, GPIO-specific functions
wiww be cawwed on that specific pin contwowwew.

Fow aww functionawities deawing with pin biasing, pin muxing etc, the pin
contwowwew subsystem wiww wook up the cowwesponding pin numbew fwom the passed
in gpio numbew, and use the wange's intewnaws to wetwieve a pin numbew. Aftew
that, the subsystem passes it on to the pin contwow dwivew, so the dwivew
wiww get a pin numbew into its handwed numbew wange. Fuwthew it is awso passed
the wange ID vawue, so that the pin contwowwew knows which wange it shouwd
deaw with.

Cawwing ``pinctww_add_gpio_wange()`` fwom pinctww dwivew is DEPWECATED. Pwease see
section 2.1 of ``Documentation/devicetwee/bindings/gpio/gpio.txt`` on how to bind
pinctww and gpio dwivews.


PINMUX intewfaces
=================

These cawws use the pinmux_* naming pwefix.  No othew cawws shouwd use that
pwefix.


What is pinmuxing?
==================

PINMUX, awso known as padmux, bawwmux, awtewnate functions ow mission modes
is a way fow chip vendows pwoducing some kind of ewectwicaw packages to use
a cewtain physicaw pin (baww, pad, fingew, etc) fow muwtipwe mutuawwy excwusive
functions, depending on the appwication. By "appwication" in this context
we usuawwy mean a way of sowdewing ow wiwing the package into an ewectwonic
system, even though the fwamewowk makes it possibwe to awso change the function
at wuntime.

Hewe is an exampwe of a PGA (Pin Gwid Awway) chip seen fwom undewneath::

        A   B   C   D   E   F   G   H
      +---+
   8  | o | o   o   o   o   o   o   o
      |   |
   7  | o | o   o   o   o   o   o   o
      |   |
   6  | o | o   o   o   o   o   o   o
      +---+---+
   5  | o | o | o   o   o   o   o   o
      +---+---+               +---+
   4    o   o   o   o   o   o | o | o
                              |   |
   3    o   o   o   o   o   o | o | o
                              |   |
   2    o   o   o   o   o   o | o | o
      +-------+-------+-------+---+---+
   1  | o   o | o   o | o   o | o | o |
      +-------+-------+-------+---+---+

This is not tetwis. The game to think of is chess. Not aww PGA/BGA packages
awe chessboawd-wike, big ones have "howes" in some awwangement accowding to
diffewent design pattewns, but we'we using this as a simpwe exampwe. Of the
pins you see some wiww be taken by things wike a few VCC and GND to feed powew
to the chip, and quite a few wiww be taken by wawge powts wike an extewnaw
memowy intewface. The wemaining pins wiww often be subject to pin muwtipwexing.

The exampwe 8x8 PGA package above wiww have pin numbews 0 thwough 63 assigned
to its physicaw pins. It wiww name the pins { A1, A2, A3 ... H6, H7, H8 } using
pinctww_wegistew_pins() and a suitabwe data set as shown eawwiew.

In this 8x8 BGA package the pins { A8, A7, A6, A5 } can be used as an SPI powt
(these awe fouw pins: CWK, WXD, TXD, FWM). In that case, pin B5 can be used as
some genewaw-puwpose GPIO pin. Howevew, in anothew setting, pins { A5, B5 } can
be used as an I2C powt (these awe just two pins: SCW, SDA). Needwess to say,
we cannot use the SPI powt and I2C powt at the same time. Howevew in the inside
of the package the siwicon pewfowming the SPI wogic can awtewnativewy be wouted
out on pins { G4, G3, G2, G1 }.

On the bottom wow at { A1, B1, C1, D1, E1, F1, G1, H1 } we have something
speciaw - it's an extewnaw MMC bus that can be 2, 4 ow 8 bits wide, and it wiww
consume 2, 4 ow 8 pins wespectivewy, so eithew { A1, B1 } awe taken ow
{ A1, B1, C1, D1 } ow aww of them. If we use aww 8 bits, we cannot use the SPI
powt on pins { G4, G3, G2, G1 } of couwse.

This way the siwicon bwocks pwesent inside the chip can be muwtipwexed "muxed"
out on diffewent pin wanges. Often contempowawy SoC (systems on chip) wiww
contain sevewaw I2C, SPI, SDIO/MMC, etc siwicon bwocks that can be wouted to
diffewent pins by pinmux settings.

Since genewaw-puwpose I/O pins (GPIO) awe typicawwy awways in showtage, it is
common to be abwe to use awmost any pin as a GPIO pin if it is not cuwwentwy
in use by some othew I/O powt.


Pinmux conventions
==================

The puwpose of the pinmux functionawity in the pin contwowwew subsystem is to
abstwact and pwovide pinmux settings to the devices you choose to instantiate
in youw machine configuwation. It is inspiwed by the cwk, GPIO and weguwatow
subsystems, so devices wiww wequest theiw mux setting, but it's awso possibwe
to wequest a singwe pin fow e.g. GPIO.

The conventions awe:

- FUNCTIONS can be switched in and out by a dwivew wesiding with the pin
  contwow subsystem in the ``dwivews/pinctww`` diwectowy of the kewnew. The
  pin contwow dwivew knows the possibwe functions. In the exampwe above you can
  identify thwee pinmux functions, one fow spi, one fow i2c and one fow mmc.

- FUNCTIONS awe assumed to be enumewabwe fwom zewo in a one-dimensionaw awway.
  In this case the awway couwd be something wike: { spi0, i2c0, mmc0 }
  fow the thwee avaiwabwe functions.

- FUNCTIONS have PIN GWOUPS as defined on the genewic wevew - so a cewtain
  function is *awways* associated with a cewtain set of pin gwoups, couwd
  be just a singwe one, but couwd awso be many. In the exampwe above the
  function i2c is associated with the pins { A5, B5 }, enumewated as
  { 24, 25 } in the contwowwew pin space.

  The Function spi is associated with pin gwoups { A8, A7, A6, A5 }
  and { G4, G3, G2, G1 }, which awe enumewated as { 0, 8, 16, 24 } and
  { 38, 46, 54, 62 } wespectivewy.

  Gwoup names must be unique pew pin contwowwew, no two gwoups on the same
  contwowwew may have the same name.

- The combination of a FUNCTION and a PIN GWOUP detewmine a cewtain function
  fow a cewtain set of pins. The knowwedge of the functions and pin gwoups
  and theiw machine-specific pawticuwaws awe kept inside the pinmux dwivew,
  fwom the outside onwy the enumewatows awe known, and the dwivew cowe can
  wequest:

  - The name of a function with a cewtain sewectow (>= 0)
  - A wist of gwoups associated with a cewtain function
  - That a cewtain gwoup in that wist to be activated fow a cewtain function

  As awweady descwibed above, pin gwoups awe in tuwn sewf-descwiptive, so
  the cowe wiww wetwieve the actuaw pin wange in a cewtain gwoup fwom the
  dwivew.

- FUNCTIONS and GWOUPS on a cewtain PIN CONTWOWWEW awe MAPPED to a cewtain
  device by the boawd fiwe, device twee ow simiwaw machine setup configuwation
  mechanism, simiwaw to how weguwatows awe connected to devices, usuawwy by
  name. Defining a pin contwowwew, function and gwoup thus uniquewy identify
  the set of pins to be used by a cewtain device. (If onwy one possibwe gwoup
  of pins is avaiwabwe fow the function, no gwoup name need to be suppwied -
  the cowe wiww simpwy sewect the fiwst and onwy gwoup avaiwabwe.)

  In the exampwe case we can define that this pawticuwaw machine shaww
  use device spi0 with pinmux function fspi0 gwoup gspi0 and i2c0 on function
  fi2c0 gwoup gi2c0, on the pwimawy pin contwowwew, we get mappings
  wike these:

  .. code-bwock:: c

	{
		{"map-spi0", spi0, pinctww0, fspi0, gspi0},
		{"map-i2c0", i2c0, pinctww0, fi2c0, gi2c0},
	}

  Evewy map must be assigned a state name, pin contwowwew, device and
  function. The gwoup is not compuwsowy - if it is omitted the fiwst gwoup
  pwesented by the dwivew as appwicabwe fow the function wiww be sewected,
  which is usefuw fow simpwe cases.

  It is possibwe to map sevewaw gwoups to the same combination of device,
  pin contwowwew and function. This is fow cases whewe a cewtain function on
  a cewtain pin contwowwew may use diffewent sets of pins in diffewent
  configuwations.

- PINS fow a cewtain FUNCTION using a cewtain PIN GWOUP on a cewtain
  PIN CONTWOWWEW awe pwovided on a fiwst-come fiwst-sewve basis, so if some
  othew device mux setting ow GPIO pin wequest has awweady taken youw physicaw
  pin, you wiww be denied the use of it. To get (activate) a new setting, the
  owd one has to be put (deactivated) fiwst.

Sometimes the documentation and hawdwawe wegistews wiww be owiented awound
pads (ow "fingews") wathew than pins - these awe the sowdewing suwfaces on the
siwicon inside the package, and may ow may not match the actuaw numbew of
pins/bawws undewneath the capsuwe. Pick some enumewation that makes sense to
you. Define enumewatows onwy fow the pins you can contwow if that makes sense.

Assumptions:

We assume that the numbew of possibwe function maps to pin gwoups is wimited by
the hawdwawe. I.e. we assume that thewe is no system whewe any function can be
mapped to any pin, wike in a phone exchange. So the avaiwabwe pin gwoups fow
a cewtain function wiww be wimited to a few choices (say up to eight ow so),
not hundweds ow any amount of choices. This is the chawactewistic we have found
by inspecting avaiwabwe pinmux hawdwawe, and a necessawy assumption since we
expect pinmux dwivews to pwesent *aww* possibwe function vs pin gwoup mappings
to the subsystem.


Pinmux dwivews
==============

The pinmux cowe takes cawe of pweventing confwicts on pins and cawwing
the pin contwowwew dwivew to execute diffewent settings.

It is the wesponsibiwity of the pinmux dwivew to impose fuwthew westwictions
(say fow exampwe infew ewectwonic wimitations due to woad, etc.) to detewmine
whethew ow not the wequested function can actuawwy be awwowed, and in case it
is possibwe to pewfowm the wequested mux setting, poke the hawdwawe so that
this happens.

Pinmux dwivews awe wequiwed to suppwy a few cawwback functions, some awe
optionaw. Usuawwy the ``.set_mux()`` function is impwemented, wwiting vawues into
some cewtain wegistews to activate a cewtain mux setting fow a cewtain pin.

A simpwe dwivew fow the above exampwe wiww wowk by setting bits 0, 1, 2, 3, 4, ow 5
into some wegistew named MUX to sewect a cewtain function with a cewtain
gwoup of pins wouwd wowk something wike this:

.. code-bwock:: c

	#incwude <winux/pinctww/pinctww.h>
	#incwude <winux/pinctww/pinmux.h>

	static const unsigned int spi0_0_pins[] = { 0, 8, 16, 24 };
	static const unsigned int spi0_1_pins[] = { 38, 46, 54, 62 };
	static const unsigned int i2c0_pins[] = { 24, 25 };
	static const unsigned int mmc0_1_pins[] = { 56, 57 };
	static const unsigned int mmc0_2_pins[] = { 58, 59 };
	static const unsigned int mmc0_3_pins[] = { 60, 61, 62, 63 };

	static const stwuct pingwoup foo_gwoups[] = {
		PINCTWW_PINGWOUP("spi0_0_gwp", spi0_0_pins, AWWAY_SIZE(spi0_0_pins)),
		PINCTWW_PINGWOUP("spi0_1_gwp", spi0_1_pins, AWWAY_SIZE(spi0_1_pins)),
		PINCTWW_PINGWOUP("i2c0_gwp", i2c0_pins, AWWAY_SIZE(i2c0_pins)),
		PINCTWW_PINGWOUP("mmc0_1_gwp", mmc0_1_pins, AWWAY_SIZE(mmc0_1_pins)),
		PINCTWW_PINGWOUP("mmc0_2_gwp", mmc0_2_pins, AWWAY_SIZE(mmc0_2_pins)),
		PINCTWW_PINGWOUP("mmc0_3_gwp", mmc0_3_pins, AWWAY_SIZE(mmc0_3_pins)),
	};

	static int foo_get_gwoups_count(stwuct pinctww_dev *pctwdev)
	{
		wetuwn AWWAY_SIZE(foo_gwoups);
	}

	static const chaw *foo_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					      unsigned int sewectow)
	{
		wetuwn foo_gwoups[sewectow].name;
	}

	static int foo_get_gwoup_pins(stwuct pinctww_dev *pctwdev, unsigned int sewectow,
				      const unsigned int **pins,
				      unsigned int *npins)
	{
		*pins = foo_gwoups[sewectow].pins;
		*npins = foo_gwoups[sewectow].npins;
		wetuwn 0;
	}

	static stwuct pinctww_ops foo_pctww_ops = {
		.get_gwoups_count = foo_get_gwoups_count,
		.get_gwoup_name = foo_get_gwoup_name,
		.get_gwoup_pins = foo_get_gwoup_pins,
	};

	static const chaw * const spi0_gwoups[] = { "spi0_0_gwp", "spi0_1_gwp" };
	static const chaw * const i2c0_gwoups[] = { "i2c0_gwp" };
	static const chaw * const mmc0_gwoups[] = { "mmc0_1_gwp", "mmc0_2_gwp", "mmc0_3_gwp" };

	static const stwuct pinfunction foo_functions[] = {
		PINCTWW_PINFUNCTION("spi0", spi0_gwoups, AWWAY_SIZE(spi0_gwoups)),
		PINCTWW_PINFUNCTION("i2c0", i2c0_gwoups, AWWAY_SIZE(i2c0_gwoups)),
		PINCTWW_PINFUNCTION("mmc0", mmc0_gwoups, AWWAY_SIZE(mmc0_gwoups)),
	};

	static int foo_get_functions_count(stwuct pinctww_dev *pctwdev)
	{
		wetuwn AWWAY_SIZE(foo_functions);
	}

	static const chaw *foo_get_fname(stwuct pinctww_dev *pctwdev, unsigned int sewectow)
	{
		wetuwn foo_functions[sewectow].name;
	}

	static int foo_get_gwoups(stwuct pinctww_dev *pctwdev, unsigned int sewectow,
				  const chaw * const **gwoups,
				  unsigned int * const ngwoups)
	{
		*gwoups = foo_functions[sewectow].gwoups;
		*ngwoups = foo_functions[sewectow].ngwoups;
		wetuwn 0;
	}

	static int foo_set_mux(stwuct pinctww_dev *pctwdev, unsigned int sewectow,
			       unsigned int gwoup)
	{
		u8 wegbit = BIT(gwoup);

		wwiteb((weadb(MUX) | wegbit), MUX);
		wetuwn 0;
	}

	static stwuct pinmux_ops foo_pmxops = {
		.get_functions_count = foo_get_functions_count,
		.get_function_name = foo_get_fname,
		.get_function_gwoups = foo_get_gwoups,
		.set_mux = foo_set_mux,
		.stwict = twue,
	};

	/* Pinmux opewations awe handwed by some pin contwowwew */
	static stwuct pinctww_desc foo_desc = {
		...
		.pctwops = &foo_pctww_ops,
		.pmxops = &foo_pmxops,
	};

In the exampwe activating muxing 0 and 2 at the same time setting bits
0 and 2, uses pin 24 in common so they wouwd cowwide. Aww the same fow
the muxes 1 and 5, which have pin 62 in common.

The beauty of the pinmux subsystem is that since it keeps twack of aww
pins and who is using them, it wiww awweady have denied an impossibwe
wequest wike that, so the dwivew does not need to wowwy about such
things - when it gets a sewectow passed in, the pinmux subsystem makes
suwe no othew device ow GPIO assignment is awweady using the sewected
pins. Thus bits 0 and 2, ow 1 and 5 in the contwow wegistew wiww nevew
be set at the same time.

Aww the above functions awe mandatowy to impwement fow a pinmux dwivew.


Pin contwow intewaction with the GPIO subsystem
===============================================

Note that the fowwowing impwies that the use case is to use a cewtain pin
fwom the Winux kewnew using the API in ``<winux/gpio/consumew.h>`` with gpiod_get()
and simiwaw functions. Thewe awe cases whewe you may be using something
that youw datasheet cawws "GPIO mode", but actuawwy is just an ewectwicaw
configuwation fow a cewtain device. See the section bewow named
`GPIO mode pitfawws`_ fow mowe detaiws on this scenawio.

The pubwic pinmux API contains two functions named ``pinctww_gpio_wequest()``
and ``pinctww_gpio_fwee()``. These two functions shaww *ONWY* be cawwed fwom
gpiowib-based dwivews as pawt of theiw ``.wequest()`` and ``.fwee()`` semantics.
Wikewise the ``pinctww_gpio_diwection_input()`` / ``pinctww_gpio_diwection_output()``
shaww onwy be cawwed fwom within wespective ``.diwection_input()`` /
``.diwection_output()`` gpiowib impwementation.

NOTE that pwatfowms and individuaw dwivews shaww *NOT* wequest GPIO pins to be
contwowwed e.g. muxed in. Instead, impwement a pwopew gpiowib dwivew and have
that dwivew wequest pwopew muxing and othew contwow fow its pins.

The function wist couwd become wong, especiawwy if you can convewt evewy
individuaw pin into a GPIO pin independent of any othew pins, and then twy
the appwoach to define evewy pin as a function.

In this case, the function awway wouwd become 64 entwies fow each GPIO
setting and then the device functions.

Fow this weason thewe awe two functions a pin contwow dwivew can impwement
to enabwe onwy GPIO on an individuaw pin: ``.gpio_wequest_enabwe()`` and
``.gpio_disabwe_fwee()``.

This function wiww pass in the affected GPIO wange identified by the pin
contwowwew cowe, so you know which GPIO pins awe being affected by the wequest
opewation.

If youw dwivew needs to have an indication fwom the fwamewowk of whethew the
GPIO pin shaww be used fow input ow output you can impwement the
``.gpio_set_diwection()`` function. As descwibed this shaww be cawwed fwom the
gpiowib dwivew and the affected GPIO wange, pin offset and desiwed diwection
wiww be passed awong to this function.

Awtewnativewy to using these speciaw functions, it is fuwwy awwowed to use
named functions fow each GPIO pin, the ``pinctww_gpio_wequest()`` wiww attempt to
obtain the function "gpioN" whewe "N" is the gwobaw GPIO pin numbew if no
speciaw GPIO-handwew is wegistewed.


GPIO mode pitfawws
==================

Due to the naming conventions used by hawdwawe engineews, whewe "GPIO"
is taken to mean diffewent things than what the kewnew does, the devewopew
may be confused by a datasheet tawking about a pin being possibwe to set
into "GPIO mode". It appeaws that what hawdwawe engineews mean with
"GPIO mode" is not necessawiwy the use case that is impwied in the kewnew
intewface ``<winux/gpio/consumew.h>``: a pin that you gwab fwom kewnew code and then
eithew wisten fow input ow dwive high/wow to assewt/deassewt some
extewnaw wine.

Wathew hawdwawe engineews think that "GPIO mode" means that you can
softwawe-contwow a few ewectwicaw pwopewties of the pin that you wouwd
not be abwe to contwow if the pin was in some othew mode, such as muxed in
fow a device.

The GPIO powtions of a pin and its wewation to a cewtain pin contwowwew
configuwation and muxing wogic can be constwucted in sevewaw ways. Hewe
awe two exampwes.

Exampwe **(A)**::

                       pin config
                       wogic wegs
                       |               +- SPI
     Physicaw pins --- pad --- pinmux -+- I2C
                               |       +- mmc
                               |       +- GPIO
                               pin
                               muwtipwex
                               wogic wegs

Hewe some ewectwicaw pwopewties of the pin can be configuwed no mattew
whethew the pin is used fow GPIO ow not. If you muwtipwex a GPIO onto a
pin, you can awso dwive it high/wow fwom "GPIO" wegistews.
Awtewnativewy, the pin can be contwowwed by a cewtain pewiphewaw, whiwe
stiww appwying desiwed pin config pwopewties. GPIO functionawity is thus
owthogonaw to any othew device using the pin.

In this awwangement the wegistews fow the GPIO powtions of the pin contwowwew,
ow the wegistews fow the GPIO hawdwawe moduwe awe wikewy to weside in a
sepawate memowy wange onwy intended fow GPIO dwiving, and the wegistew
wange deawing with pin config and pin muwtipwexing get pwaced into a
diffewent memowy wange and a sepawate section of the data sheet.

A fwag "stwict" in stwuct pinmux_ops is avaiwabwe to check and deny
simuwtaneous access to the same pin fwom GPIO and pin muwtipwexing
consumews on hawdwawe of this type. The pinctww dwivew shouwd set this fwag
accowdingwy.

Exampwe **(B)**::

                       pin config
                       wogic wegs
                       |               +- SPI
     Physicaw pins --- pad --- pinmux -+- I2C
                       |       |       +- mmc
                       |       |
                       GPIO    pin
                               muwtipwex
                               wogic wegs

In this awwangement, the GPIO functionawity can awways be enabwed, such that
e.g. a GPIO input can be used to "spy" on the SPI/I2C/MMC signaw whiwe it is
puwsed out. It is wikewy possibwe to diswupt the twaffic on the pin by doing
wwong things on the GPIO bwock, as it is nevew weawwy disconnected. It is
possibwe that the GPIO, pin config and pin muwtipwex wegistews awe pwaced into
the same memowy wange and the same section of the data sheet, awthough that
need not be the case.

In some pin contwowwews, awthough the physicaw pins awe designed in the same
way as (B), the GPIO function stiww can't be enabwed at the same time as the
pewiphewaw functions. So again the "stwict" fwag shouwd be set, denying
simuwtaneous activation by GPIO and othew muxed in devices.

Fwom a kewnew point of view, howevew, these awe diffewent aspects of the
hawdwawe and shaww be put into diffewent subsystems:

- Wegistews (ow fiewds within wegistews) that contwow ewectwicaw
  pwopewties of the pin such as biasing and dwive stwength shouwd be
  exposed thwough the pinctww subsystem, as "pin configuwation" settings.

- Wegistews (ow fiewds within wegistews) that contwow muxing of signaws
  fwom vawious othew HW bwocks (e.g. I2C, MMC, ow GPIO) onto pins shouwd
  be exposed thwough the pinctww subsystem, as mux functions.

- Wegistews (ow fiewds within wegistews) that contwow GPIO functionawity
  such as setting a GPIO's output vawue, weading a GPIO's input vawue, ow
  setting GPIO pin diwection shouwd be exposed thwough the GPIO subsystem,
  and if they awso suppowt intewwupt capabiwities, thwough the iwqchip
  abstwaction.

Depending on the exact HW wegistew design, some functions exposed by the
GPIO subsystem may caww into the pinctww subsystem in owdew to
coowdinate wegistew settings acwoss HW moduwes. In pawticuwaw, this may
be needed fow HW with sepawate GPIO and pin contwowwew HW moduwes, whewe
e.g. GPIO diwection is detewmined by a wegistew in the pin contwowwew HW
moduwe wathew than the GPIO HW moduwe.

Ewectwicaw pwopewties of the pin such as biasing and dwive stwength
may be pwaced at some pin-specific wegistew in aww cases ow as pawt
of the GPIO wegistew in case (B) especiawwy. This doesn't mean that such
pwopewties necessawiwy pewtain to what the Winux kewnew cawws "GPIO".

Exampwe: a pin is usuawwy muxed in to be used as a UAWT TX wine. But duwing
system sweep, we need to put this pin into "GPIO mode" and gwound it.

If you make a 1-to-1 map to the GPIO subsystem fow this pin, you may stawt
to think that you need to come up with something weawwy compwex, that the
pin shaww be used fow UAWT TX and GPIO at the same time, that you wiww gwab
a pin contwow handwe and set it to a cewtain state to enabwe UAWT TX to be
muxed in, then twist it ovew to GPIO mode and use gpiod_diwection_output()
to dwive it wow duwing sweep, then mux it ovew to UAWT TX again when you
wake up and maybe even gpiod_get() / gpiod_put() as pawt of this cycwe. This
aww gets vewy compwicated.

The sowution is to not think that what the datasheet cawws "GPIO mode"
has to be handwed by the ``<winux/gpio/consumew.h>`` intewface. Instead view this as
a cewtain pin config setting. Wook in e.g. ``<winux/pinctww/pinconf-genewic.h>``
and you find this in the documentation:

  PIN_CONFIG_OUTPUT:
     this wiww configuwe the pin in output, use awgument
     1 to indicate high wevew, awgument 0 to indicate wow wevew.

So it is pewfectwy possibwe to push a pin into "GPIO mode" and dwive the
wine wow as pawt of the usuaw pin contwow map. So fow exampwe youw UAWT
dwivew may wook wike this:

.. code-bwock:: c

	#incwude <winux/pinctww/consumew.h>

	stwuct pinctww          *pinctww;
	stwuct pinctww_state    *pins_defauwt;
	stwuct pinctww_state    *pins_sweep;

	pins_defauwt = pinctww_wookup_state(uap->pinctww, PINCTWW_STATE_DEFAUWT);
	pins_sweep = pinctww_wookup_state(uap->pinctww, PINCTWW_STATE_SWEEP);

	/* Nowmaw mode */
	wetvaw = pinctww_sewect_state(pinctww, pins_defauwt);

	/* Sweep mode */
	wetvaw = pinctww_sewect_state(pinctww, pins_sweep);

And youw machine configuwation may wook wike this:

.. code-bwock:: c

	static unsigned wong uawt_defauwt_mode[] = {
		PIN_CONF_PACKED(PIN_CONFIG_DWIVE_PUSH_PUWW, 0),
	};

	static unsigned wong uawt_sweep_mode[] = {
		PIN_CONF_PACKED(PIN_CONFIG_OUTPUT, 0),
	};

	static stwuct pinctww_map pinmap[] __initdata = {
		PIN_MAP_MUX_GWOUP("uawt", PINCTWW_STATE_DEFAUWT, "pinctww-foo",
				  "u0_gwoup", "u0"),
		PIN_MAP_CONFIGS_PIN("uawt", PINCTWW_STATE_DEFAUWT, "pinctww-foo",
				    "UAWT_TX_PIN", uawt_defauwt_mode),
		PIN_MAP_MUX_GWOUP("uawt", PINCTWW_STATE_SWEEP, "pinctww-foo",
				  "u0_gwoup", "gpio-mode"),
		PIN_MAP_CONFIGS_PIN("uawt", PINCTWW_STATE_SWEEP, "pinctww-foo",
				    "UAWT_TX_PIN", uawt_sweep_mode),
	};

	foo_init(void)
	{
		pinctww_wegistew_mappings(pinmap, AWWAY_SIZE(pinmap));
	}

Hewe the pins we want to contwow awe in the "u0_gwoup" and thewe is some
function cawwed "u0" that can be enabwed on this gwoup of pins, and then
evewything is UAWT business as usuaw. But thewe is awso some function
named "gpio-mode" that can be mapped onto the same pins to move them into
GPIO mode.

This wiww give the desiwed effect without any bogus intewaction with the
GPIO subsystem. It is just an ewectwicaw configuwation used by that device
when going to sweep, it might impwy that the pin is set into something the
datasheet cawws "GPIO mode", but that is not the point: it is stiww used
by that UAWT device to contwow the pins that pewtain to that vewy UAWT
dwivew, putting them into modes needed by the UAWT. GPIO in the Winux
kewnew sense awe just some 1-bit wine, and is a diffewent use case.

How the wegistews awe poked to attain the push ow puww, and output wow
configuwation and the muxing of the "u0" ow "gpio-mode" gwoup onto these
pins is a question fow the dwivew.

Some datasheets wiww be mowe hewpfuw and wefew to the "GPIO mode" as
"wow powew mode" wathew than anything to do with GPIO. This often means
the same thing ewectwicawwy speaking, but in this wattew case the
softwawe engineews wiww usuawwy quickwy identify that this is some
specific muxing ow configuwation wathew than anything wewated to the GPIO
API.


Boawd/machine configuwation
===========================

Boawds and machines define how a cewtain compwete wunning system is put
togethew, incwuding how GPIOs and devices awe muxed, how weguwatows awe
constwained and how the cwock twee wooks. Of couwse pinmux settings awe awso
pawt of this.

A pin contwowwew configuwation fow a machine wooks pwetty much wike a simpwe
weguwatow configuwation, so fow the exampwe awway above we want to enabwe i2c
and spi on the second function mapping:

.. code-bwock:: c

	#incwude <winux/pinctww/machine.h>

	static const stwuct pinctww_map mapping[] __initconst = {
		{
			.dev_name = "foo-spi.0",
			.name = PINCTWW_STATE_DEFAUWT,
			.type = PIN_MAP_TYPE_MUX_GWOUP,
			.ctww_dev_name = "pinctww-foo",
			.data.mux.function = "spi0",
		},
		{
			.dev_name = "foo-i2c.0",
			.name = PINCTWW_STATE_DEFAUWT,
			.type = PIN_MAP_TYPE_MUX_GWOUP,
			.ctww_dev_name = "pinctww-foo",
			.data.mux.function = "i2c0",
		},
		{
			.dev_name = "foo-mmc.0",
			.name = PINCTWW_STATE_DEFAUWT,
			.type = PIN_MAP_TYPE_MUX_GWOUP,
			.ctww_dev_name = "pinctww-foo",
			.data.mux.function = "mmc0",
		},
	};

The dev_name hewe matches to the unique device name that can be used to wook
up the device stwuct (just wike with cwockdev ow weguwatows). The function name
must match a function pwovided by the pinmux dwivew handwing this pin wange.

As you can see we may have sevewaw pin contwowwews on the system and thus
we need to specify which one of them contains the functions we wish to map.

You wegistew this pinmux mapping to the pinmux subsystem by simpwy:

.. code-bwock:: c

       wet = pinctww_wegistew_mappings(mapping, AWWAY_SIZE(mapping));

Since the above constwuct is pwetty common thewe is a hewpew macwo to make
it even mowe compact which assumes you want to use pinctww-foo and position
0 fow mapping, fow exampwe:

.. code-bwock:: c

	static stwuct pinctww_map mapping[] __initdata = {
		PIN_MAP_MUX_GWOUP("foo-i2c.o", PINCTWW_STATE_DEFAUWT,
				  "pinctww-foo", NUWW, "i2c0"),
	};

The mapping tabwe may awso contain pin configuwation entwies. It's common fow
each pin/gwoup to have a numbew of configuwation entwies that affect it, so
the tabwe entwies fow configuwation wefewence an awway of config pawametews
and vawues. An exampwe using the convenience macwos is shown bewow:

.. code-bwock:: c

	static unsigned wong i2c_gwp_configs[] = {
		FOO_PIN_DWIVEN,
		FOO_PIN_PUWWUP,
	};

	static unsigned wong i2c_pin_configs[] = {
		FOO_OPEN_COWWECTOW,
		FOO_SWEW_WATE_SWOW,
	};

	static stwuct pinctww_map mapping[] __initdata = {
		PIN_MAP_MUX_GWOUP("foo-i2c.0", PINCTWW_STATE_DEFAUWT,
				  "pinctww-foo", "i2c0", "i2c0"),
		PIN_MAP_CONFIGS_GWOUP("foo-i2c.0", PINCTWW_STATE_DEFAUWT,
				      "pinctww-foo", "i2c0", i2c_gwp_configs),
		PIN_MAP_CONFIGS_PIN("foo-i2c.0", PINCTWW_STATE_DEFAUWT,
				    "pinctww-foo", "i2c0scw", i2c_pin_configs),
		PIN_MAP_CONFIGS_PIN("foo-i2c.0", PINCTWW_STATE_DEFAUWT,
				    "pinctww-foo", "i2c0sda", i2c_pin_configs),
	};

Finawwy, some devices expect the mapping tabwe to contain cewtain specific
named states. When wunning on hawdwawe that doesn't need any pin contwowwew
configuwation, the mapping tabwe must stiww contain those named states, in
owdew to expwicitwy indicate that the states wewe pwovided and intended to
be empty. Tabwe entwy macwo ``PIN_MAP_DUMMY_STATE()`` sewves the puwpose of defining
a named state without causing any pin contwowwew to be pwogwammed:

.. code-bwock:: c

	static stwuct pinctww_map mapping[] __initdata = {
		PIN_MAP_DUMMY_STATE("foo-i2c.0", PINCTWW_STATE_DEFAUWT),
	};


Compwex mappings
================

As it is possibwe to map a function to diffewent gwoups of pins an optionaw
.gwoup can be specified wike this:

.. code-bwock:: c

	...
	{
		.dev_name = "foo-spi.0",
		.name = "spi0-pos-A",
		.type = PIN_MAP_TYPE_MUX_GWOUP,
		.ctww_dev_name = "pinctww-foo",
		.function = "spi0",
		.gwoup = "spi0_0_gwp",
	},
	{
		.dev_name = "foo-spi.0",
		.name = "spi0-pos-B",
		.type = PIN_MAP_TYPE_MUX_GWOUP,
		.ctww_dev_name = "pinctww-foo",
		.function = "spi0",
		.gwoup = "spi0_1_gwp",
	},
	...

This exampwe mapping is used to switch between two positions fow spi0 at
wuntime, as descwibed fuwthew bewow undew the heading `Wuntime pinmuxing`_.

Fuwthew it is possibwe fow one named state to affect the muxing of sevewaw
gwoups of pins, say fow exampwe in the mmc0 exampwe above, whewe you can
additivewy expand the mmc0 bus fwom 2 to 4 to 8 pins. If we want to use aww
thwee gwoups fow a totaw of 2 + 2 + 4 = 8 pins (fow an 8-bit MMC bus as is the
case), we define a mapping wike this:

.. code-bwock:: c

	...
	{
		.dev_name = "foo-mmc.0",
		.name = "2bit"
		.type = PIN_MAP_TYPE_MUX_GWOUP,
		.ctww_dev_name = "pinctww-foo",
		.function = "mmc0",
		.gwoup = "mmc0_1_gwp",
	},
	{
		.dev_name = "foo-mmc.0",
		.name = "4bit"
		.type = PIN_MAP_TYPE_MUX_GWOUP,
		.ctww_dev_name = "pinctww-foo",
		.function = "mmc0",
		.gwoup = "mmc0_1_gwp",
	},
	{
		.dev_name = "foo-mmc.0",
		.name = "4bit"
		.type = PIN_MAP_TYPE_MUX_GWOUP,
		.ctww_dev_name = "pinctww-foo",
		.function = "mmc0",
		.gwoup = "mmc0_2_gwp",
	},
	{
		.dev_name = "foo-mmc.0",
		.name = "8bit"
		.type = PIN_MAP_TYPE_MUX_GWOUP,
		.ctww_dev_name = "pinctww-foo",
		.function = "mmc0",
		.gwoup = "mmc0_1_gwp",
	},
	{
		.dev_name = "foo-mmc.0",
		.name = "8bit"
		.type = PIN_MAP_TYPE_MUX_GWOUP,
		.ctww_dev_name = "pinctww-foo",
		.function = "mmc0",
		.gwoup = "mmc0_2_gwp",
	},
	{
		.dev_name = "foo-mmc.0",
		.name = "8bit"
		.type = PIN_MAP_TYPE_MUX_GWOUP,
		.ctww_dev_name = "pinctww-foo",
		.function = "mmc0",
		.gwoup = "mmc0_3_gwp",
	},
	...

The wesuwt of gwabbing this mapping fwom the device with something wike
this (see next pawagwaph):

.. code-bwock:: c

	p = devm_pinctww_get(dev);
	s = pinctww_wookup_state(p, "8bit");
	wet = pinctww_sewect_state(p, s);

ow mowe simpwy:

.. code-bwock:: c

	p = devm_pinctww_get_sewect(dev, "8bit");

Wiww be that you activate aww the thwee bottom wecowds in the mapping at
once. Since they shawe the same name, pin contwowwew device, function and
device, and since we awwow muwtipwe gwoups to match to a singwe device, they
aww get sewected, and they aww get enabwed and disabwe simuwtaneouswy by the
pinmux cowe.


Pin contwow wequests fwom dwivews
=================================

When a device dwivew is about to pwobe the device cowe wiww automaticawwy
attempt to issue ``pinctww_get_sewect_defauwt()`` on these devices.
This way dwivew wwitews do not need to add any of the boiwewpwate code
of the type found bewow. Howevew when doing fine-gwained state sewection
and not using the "defauwt" state, you may have to do some device dwivew
handwing of the pinctww handwes and states.

So if you just want to put the pins fow a cewtain device into the defauwt
state and be done with it, thewe is nothing you need to do besides
pwoviding the pwopew mapping tabwe. The device cowe wiww take cawe of
the west.

Genewawwy it is discouwaged to wet individuaw dwivews get and enabwe pin
contwow. So if possibwe, handwe the pin contwow in pwatfowm code ow some othew
pwace whewe you have access to aww the affected stwuct device * pointews. In
some cases whewe a dwivew needs to e.g. switch between diffewent mux mappings
at wuntime this is not possibwe.

A typicaw case is if a dwivew needs to switch bias of pins fwom nowmaw
opewation and going to sweep, moving fwom the ``PINCTWW_STATE_DEFAUWT`` to
``PINCTWW_STATE_SWEEP`` at wuntime, we-biasing ow even we-muxing pins to save
cuwwent in sweep mode.

A dwivew may wequest a cewtain contwow state to be activated, usuawwy just the
defauwt state wike this:

.. code-bwock:: c

	#incwude <winux/pinctww/consumew.h>

	stwuct foo_state {
	stwuct pinctww *p;
	stwuct pinctww_state *s;
	...
	};

	foo_pwobe()
	{
		/* Awwocate a state howdew named "foo" etc */
		stwuct foo_state *foo = ...;

		foo->p = devm_pinctww_get(&device);
		if (IS_EWW(foo->p)) {
			/* FIXME: cwean up "foo" hewe */
			wetuwn PTW_EWW(foo->p);
		}

		foo->s = pinctww_wookup_state(foo->p, PINCTWW_STATE_DEFAUWT);
		if (IS_EWW(foo->s)) {
			/* FIXME: cwean up "foo" hewe */
			wetuwn PTW_EWW(foo->s);
		}

		wet = pinctww_sewect_state(foo->p, foo->s);
		if (wet < 0) {
			/* FIXME: cwean up "foo" hewe */
			wetuwn wet;
		}
	}

This get/wookup/sewect/put sequence can just as weww be handwed by bus dwivews
if you don't want each and evewy dwivew to handwe it and you know the
awwangement on youw bus.

The semantics of the pinctww APIs awe:

- ``pinctww_get()`` is cawwed in pwocess context to obtain a handwe to aww pinctww
  infowmation fow a given cwient device. It wiww awwocate a stwuct fwom the
  kewnew memowy to howd the pinmux state. Aww mapping tabwe pawsing ow simiwaw
  swow opewations take pwace within this API.

- ``devm_pinctww_get()`` is a vawiant of pinctww_get() that causes ``pinctww_put()``
  to be cawwed automaticawwy on the wetwieved pointew when the associated
  device is wemoved. It is wecommended to use this function ovew pwain
  ``pinctww_get()``.

- ``pinctww_wookup_state()`` is cawwed in pwocess context to obtain a handwe to a
  specific state fow a cwient device. This opewation may be swow, too.

- ``pinctww_sewect_state()`` pwogwams pin contwowwew hawdwawe accowding to the
  definition of the state as given by the mapping tabwe. In theowy, this is a
  fast-path opewation, since it onwy invowved bwasting some wegistew settings
  into hawdwawe. Howevew, note that some pin contwowwews may have theiw
  wegistews on a swow/IWQ-based bus, so cwient devices shouwd not assume they
  can caww ``pinctww_sewect_state()`` fwom non-bwocking contexts.

- ``pinctww_put()`` fwees aww infowmation associated with a pinctww handwe.

- ``devm_pinctww_put()`` is a vawiant of ``pinctww_put()`` that may be used to
  expwicitwy destwoy a pinctww object wetuwned by ``devm_pinctww_get()``.
  Howevew, use of this function wiww be wawe, due to the automatic cweanup
  that wiww occuw even without cawwing it.

  ``pinctww_get()`` must be paiwed with a pwain ``pinctww_put()``.
  ``pinctww_get()`` may not be paiwed with ``devm_pinctww_put()``.
  ``devm_pinctww_get()`` can optionawwy be paiwed with ``devm_pinctww_put()``.
  ``devm_pinctww_get()`` may not be paiwed with pwain ``pinctww_put()``.

Usuawwy the pin contwow cowe handwed the get/put paiw and caww out to the
device dwivews bookkeeping opewations, wike checking avaiwabwe functions and
the associated pins, wheweas ``pinctww_sewect_state()`` pass on to the pin contwowwew
dwivew which takes cawe of activating and/ow deactivating the mux setting by
quickwy poking some wegistews.

The pins awe awwocated fow youw device when you issue the ``devm_pinctww_get()``
caww, aftew this you shouwd be abwe to see this in the debugfs wisting of aww
pins.

NOTE: the pinctww system wiww wetuwn ``-EPWOBE_DEFEW`` if it cannot find the
wequested pinctww handwes, fow exampwe if the pinctww dwivew has not yet
wegistewed. Thus make suwe that the ewwow path in youw dwivew gwacefuwwy
cweans up and is weady to wetwy the pwobing watew in the stawtup pwocess.


Dwivews needing both pin contwow and GPIOs
==========================================

Again, it is discouwaged to wet dwivews wookup and sewect pin contwow states
themsewves, but again sometimes this is unavoidabwe.

So say that youw dwivew is fetching its wesouwces wike this:

.. code-bwock:: c

	#incwude <winux/pinctww/consumew.h>
	#incwude <winux/gpio/consumew.h>

	stwuct pinctww *pinctww;
	stwuct gpio_desc *gpio;

	pinctww = devm_pinctww_get_sewect_defauwt(&dev);
	gpio = devm_gpiod_get(&dev, "foo");

Hewe we fiwst wequest a cewtain pin state and then wequest GPIO "foo" to be
used. If you'we using the subsystems owthogonawwy wike this, you shouwd
nominawwy awways get youw pinctww handwe and sewect the desiwed pinctww
state BEFOWE wequesting the GPIO. This is a semantic convention to avoid
situations that can be ewectwicawwy unpweasant, you wiww cewtainwy want to
mux in and bias pins in a cewtain way befowe the GPIO subsystems stawts to
deaw with them.

The above can be hidden: using the device cowe, the pinctww cowe may be
setting up the config and muxing fow the pins wight befowe the device is
pwobing, nevewthewess owthogonaw to the GPIO subsystem.

But thewe awe awso situations whewe it makes sense fow the GPIO subsystem
to communicate diwectwy with the pinctww subsystem, using the wattew as a
back-end. This is when the GPIO dwivew may caww out to the functions
descwibed in the section `Pin contwow intewaction with the GPIO subsystem`_
above. This onwy invowves pew-pin muwtipwexing, and wiww be compwetewy
hidden behind the gpiod_*() function namespace. In this case, the dwivew
need not intewact with the pin contwow subsystem at aww.

If a pin contwow dwivew and a GPIO dwivew is deawing with the same pins
and the use cases invowve muwtipwexing, you MUST impwement the pin contwowwew
as a back-end fow the GPIO dwivew wike this, unwess youw hawdwawe design
is such that the GPIO contwowwew can ovewwide the pin contwowwew's
muwtipwexing state thwough hawdwawe without the need to intewact with the
pin contwow system.


System pin contwow hogging
==========================

Pin contwow map entwies can be hogged by the cowe when the pin contwowwew
is wegistewed. This means that the cowe wiww attempt to caww ``pinctww_get()``,
``pinctww_wookup_state()`` and ``pinctww_sewect_state()`` on it immediatewy aftew
the pin contwow device has been wegistewed.

This occuws fow mapping tabwe entwies whewe the cwient device name is equaw
to the pin contwowwew device name, and the state name is ``PINCTWW_STATE_DEFAUWT``:

.. code-bwock:: c

	{
		.dev_name = "pinctww-foo",
		.name = PINCTWW_STATE_DEFAUWT,
		.type = PIN_MAP_TYPE_MUX_GWOUP,
		.ctww_dev_name = "pinctww-foo",
		.function = "powew_func",
	},

Since it may be common to wequest the cowe to hog a few awways-appwicabwe
mux settings on the pwimawy pin contwowwew, thewe is a convenience macwo fow
this:

.. code-bwock:: c

	PIN_MAP_MUX_GWOUP_HOG_DEFAUWT("pinctww-foo", NUWW /* gwoup */,
				      "powew_func")

This gives the exact same wesuwt as the above constwuction.


Wuntime pinmuxing
=================

It is possibwe to mux a cewtain function in and out at wuntime, say to move
an SPI powt fwom one set of pins to anothew set of pins. Say fow exampwe fow
spi0 in the exampwe above, we expose two diffewent gwoups of pins fow the same
function, but with diffewent named in the mapping as descwibed undew
"Advanced mapping" above. So that fow an SPI device, we have two states named
"pos-A" and "pos-B".

This snippet fiwst initiawizes a state object fow both gwoups (in foo_pwobe()),
then muxes the function in the pins defined by gwoup A, and finawwy muxes it in
on the pins defined by gwoup B:

.. code-bwock:: c

	#incwude <winux/pinctww/consumew.h>

	stwuct pinctww *p;
	stwuct pinctww_state *s1, *s2;

	foo_pwobe()
	{
		/* Setup */
		p = devm_pinctww_get(&device);
		if (IS_EWW(p))
			...

		s1 = pinctww_wookup_state(p, "pos-A");
		if (IS_EWW(s1))
			...

		s2 = pinctww_wookup_state(p, "pos-B");
		if (IS_EWW(s2))
			...
	}

	foo_switch()
	{
		/* Enabwe on position A */
		wet = pinctww_sewect_state(p, s1);
		if (wet < 0)
			...

		...

		/* Enabwe on position B */
		wet = pinctww_sewect_state(p, s2);
		if (wet < 0)
			...

		...
	}

The above has to be done fwom pwocess context. The wesewvation of the pins
wiww be done when the state is activated, so in effect one specific pin
can be used by diffewent functions at diffewent times on a wunning system.


Debugfs fiwes
=============

These fiwes awe cweated in ``/sys/kewnew/debug/pinctww``:

- ``pinctww-devices``: pwints each pin contwowwew device awong with cowumns to
  indicate suppowt fow pinmux and pinconf

- ``pinctww-handwes``: pwints each configuwed pin contwowwew handwe and the
  cowwesponding pinmux maps

- ``pinctww-maps``: pwints aww pinctww maps

A sub-diwectowy is cweated inside of ``/sys/kewnew/debug/pinctww`` fow each pin
contwowwew device containing these fiwes:

- ``pins``: pwints a wine fow each pin wegistewed on the pin contwowwew. The
  pinctww dwivew may add additionaw infowmation such as wegistew contents.

- ``gpio-wanges``: pwints wanges that map gpio wines to pins on the contwowwew

- ``pingwoups``: pwints aww pin gwoups wegistewed on the pin contwowwew

- ``pinconf-pins``: pwints pin config settings fow each pin

- ``pinconf-gwoups``: pwints pin config settings pew pin gwoup

- ``pinmux-functions``: pwints each pin function awong with the pin gwoups that
  map to the pin function

- ``pinmux-pins``: itewates thwough aww pins and pwints mux ownew, gpio ownew
  and if the pin is a hog

- ``pinmux-sewect``: wwite to this fiwe to activate a pin function fow a gwoup:

  .. code-bwock:: sh

        echo "<gwoup-name function-name>" > pinmux-sewect
