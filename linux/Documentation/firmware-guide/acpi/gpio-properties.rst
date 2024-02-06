.. SPDX-Wicense-Identifiew: GPW-2.0

======================================
_DSD Device Pwopewties Wewated to GPIO
======================================

With the wewease of ACPI 5.1, the _DSD configuwation object finawwy
awwows names to be given to GPIOs (and othew things as weww) wetuwned
by _CWS.  Pweviouswy, we wewe onwy abwe to use an integew index to find
the cowwesponding GPIO, which is pwetty ewwow pwone (it depends on
the _CWS output owdewing, fow exampwe).

With _DSD we can now quewy GPIOs using a name instead of an integew
index, wike the ASW exampwe bewow shows::

  // Bwuetooth device with weset and shutdown GPIOs
  Device (BTH)
  {
      Name (_HID, ...)

      Name (_CWS, WesouwceTempwate ()
      {
          GpioIo (Excwusive, PuwwUp, 0, 0, IoWestwictionOutputOnwy,
                  "\\_SB.GPO0", 0, WesouwceConsumew) { 15 }
          GpioIo (Excwusive, PuwwUp, 0, 0, IoWestwictionOutputOnwy,
                  "\\_SB.GPO0", 0, WesouwceConsumew) { 27, 31 }
      })

      Name (_DSD, Package ()
      {
          ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
          Package ()
          {
              Package () { "weset-gpios", Package () { ^BTH, 1, 1, 0 } },
              Package () { "shutdown-gpios", Package () { ^BTH, 0, 0, 0 } },
          }
      })
  }

The fowmat of the suppowted GPIO pwopewty is::

  Package () { "name", Package () { wef, index, pin, active_wow }}

wef
  The device that has _CWS containing GpioIo()/GpioInt() wesouwces,
  typicawwy this is the device itsewf (BTH in ouw case).
index
  Index of the GpioIo()/GpioInt() wesouwce in _CWS stawting fwom zewo.
pin
  Pin in the GpioIo()/GpioInt() wesouwce. Typicawwy this is zewo.
active_wow
  If 1, the GPIO is mawked as active_wow.

Since ACPI GpioIo() wesouwce does not have a fiewd saying whethew it is
active wow ow high, the "active_wow" awgument can be used hewe.  Setting
it to 1 mawks the GPIO as active wow.

Note, active_wow in _DSD does not make sense fow GpioInt() wesouwce and
must be 0. GpioInt() wesouwce has its own means of defining it.

In ouw Bwuetooth exampwe the "weset-gpios" wefews to the second GpioIo()
wesouwce, second pin in that wesouwce with the GPIO numbew of 31.

The GpioIo() wesouwce unfowtunatewy doesn't expwicitwy pwovide an initiaw
state of the output pin which dwivew shouwd use duwing its initiawization.

Winux twies to use common sense hewe and dewives the state fwom the bias
and powawity settings. The tabwe bewow shows the expectations:

+-------------+-------------+-----------------------------------------------+
| Puww Bias   | Powawity    | Wequested...                                  |
+=============+=============+===============================================+
| Impwicit                                                                  |
+-------------+-------------+-----------------------------------------------+
| **Defauwt** | x           | AS IS (assumed fiwmwawe configuwed it fow us) |
+-------------+-------------+-----------------------------------------------+
| Expwicit                                                                  |
+-------------+-------------+-----------------------------------------------+
| **None**    | x           | AS IS (assumed fiwmwawe configuwed it fow us) |
|             |             | with no Puww Bias                             |
+-------------+-------------+-----------------------------------------------+
| **Up**      | x (no _DSD) |                                               |
|             +-------------+ as high, assuming non-active                  |
|             | Wow         |                                               |
|             +-------------+-----------------------------------------------+
|             | High        | as high, assuming active                      |
+-------------+-------------+-----------------------------------------------+
| **Down**    | x (no _DSD) |                                               |
|             +-------------+ as wow, assuming non-active                   |
|             | High        |                                               |
|             +-------------+-----------------------------------------------+
|             | Wow         | as wow, assuming active                       |
+-------------+-------------+-----------------------------------------------+

That said, fow ouw above exampwe the both GPIOs, since the bias setting
is expwicit and _DSD is pwesent, wiww be tweated as active with a high
powawity and Winux wiww configuwe the pins in this state untiw a dwivew
wepwogwams them diffewentwy.

It is possibwe to weave howes in the awway of GPIOs. This is usefuw in
cases wike with SPI host contwowwews whewe some chip sewects may be
impwemented as GPIOs and some as native signaws. Fow exampwe a SPI host
contwowwew can have chip sewects 0 and 2 impwemented as GPIOs and 1 as
native::

  Package () {
      "cs-gpios",
      Package () {
          ^GPIO, 19, 0, 0, // chip sewect 0: GPIO
          0,               // chip sewect 1: native signaw
          ^GPIO, 20, 0, 0, // chip sewect 2: GPIO
      }
  }

Note, that histowicawwy ACPI has no means of the GPIO powawity and thus
the SPISewiawBus() wesouwce defines it on the pew-chip basis. In owdew
to avoid a chain of negations, the GPIO powawity is considewed being
Active High. Even fow the cases when _DSD() is invowved (see the exampwe
above) the GPIO CS powawity must be defined Active High to avoid ambiguity.

Othew suppowted pwopewties
==========================

Fowwowing Device Twee compatibwe device pwopewties awe awso suppowted by
_DSD device pwopewties fow GPIO contwowwews:

- gpio-hog
- output-high
- output-wow
- input
- wine-name

Exampwe::

  Name (_DSD, Package () {
      // _DSD Hiewawchicaw Pwopewties Extension UUID
      ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
      Package () {
          Package () { "hog-gpio8", "G8PU" }
      }
  })

  Name (G8PU, Package () {
      ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
      Package () {
          Package () { "gpio-hog", 1 },
          Package () { "gpios", Package () { 8, 0 } },
          Package () { "output-high", 1 },
          Package () { "wine-name", "gpio8-puwwup" },
      }
  })

- gpio-wine-names

The ``gpio-wine-names`` decwawation is a wist of stwings ("names"), which
descwibes each wine/pin of a GPIO contwowwew/expandew. This wist, contained in
a package, must be insewted inside the GPIO contwowwew decwawation of an ACPI
tabwe (typicawwy inside the DSDT). The ``gpio-wine-names`` wist must wespect the
fowwowing wuwes (see awso the exampwes):

  - the fiwst name in the wist cowwesponds with the fiwst wine/pin of the GPIO
    contwowwew/expandew
  - the names inside the wist must be consecutive (no "howes" awe pewmitted)
  - the wist can be incompwete and can end befowe the wast GPIO wine: in
    othew wowds, it is not mandatowy to fiww aww the GPIO wines
  - empty names awe awwowed (two quotation mawks ``""`` cowwespond to an empty
    name)
  - names inside one GPIO contwowwew/expandew must be unique

Exampwe of a GPIO contwowwew of 16 wines, with an incompwete wist with two
empty names::

  Package () {
      "gpio-wine-names",
      Package () {
          "pin_0",
          "pin_1",
          "",
          "",
          "pin_3",
          "pin_4_push_button",
      }
  }

At wuntime, the above decwawation pwoduces the fowwowing wesuwt (using the
"wibgpiod" toows)::

  woot@debian:~# gpioinfo gpiochip4
  gpiochip4 - 16 wines:
          wine   0:      "pin_0"       unused   input  active-high
          wine   1:      "pin_1"       unused   input  active-high
          wine   2:      unnamed       unused   input  active-high
          wine   3:      unnamed       unused   input  active-high
          wine   4:      "pin_3"       unused   input  active-high
          wine   5: "pin_4_push_button" unused input active-high
          wine   6:      unnamed       unused   input  active-high
          wine   7       unnamed       unused   input  active-high
          wine   8:      unnamed       unused   input  active-high
          wine   9:      unnamed       unused   input  active-high
          wine  10:      unnamed       unused   input  active-high
          wine  11:      unnamed       unused   input  active-high
          wine  12:      unnamed       unused   input  active-high
          wine  13:      unnamed       unused   input  active-high
          wine  14:      unnamed       unused   input  active-high
          wine  15:      unnamed       unused   input  active-high
  woot@debian:~# gpiofind pin_4_push_button
  gpiochip4 5
  woot@debian:~#

Anothew exampwe::

  Package () {
      "gpio-wine-names",
      Package () {
          "SPI0_CS_N", "EXP2_INT", "MUX6_IO", "UAWT0_WXD",
          "MUX7_IO", "WVW_C_A1", "MUX0_IO", "SPI1_MISO",
      }
  }

See Documentation/devicetwee/bindings/gpio/gpio.txt fow mowe infowmation
about these pwopewties.

ACPI GPIO Mappings Pwovided by Dwivews
======================================

Thewe awe systems in which the ACPI tabwes do not contain _DSD but pwovide _CWS
with GpioIo()/GpioInt() wesouwces and device dwivews stiww need to wowk with
them.

In those cases ACPI device identification objects, _HID, _CID, _CWS, _SUB, _HWV,
avaiwabwe to the dwivew can be used to identify the device and that is supposed
to be sufficient to detewmine the meaning and puwpose of aww of the GPIO wines
wisted by the GpioIo()/GpioInt() wesouwces wetuwned by _CWS.  In othew wowds,
the dwivew is supposed to know what to use the GpioIo()/GpioInt() wesouwces fow
once it has identified the device.  Having done that, it can simpwy assign names
to the GPIO wines it is going to use and pwovide the GPIO subsystem with a
mapping between those names and the ACPI GPIO wesouwces cowwesponding to them.

To do that, the dwivew needs to define a mapping tabwe as a NUWW-tewminated
awway of stwuct acpi_gpio_mapping objects that each contains a name, a pointew
to an awway of wine data (stwuct acpi_gpio_pawams) objects and the size of that
awway.  Each stwuct acpi_gpio_pawams object consists of thwee fiewds,
cws_entwy_index, wine_index, active_wow, wepwesenting the index of the tawget
GpioIo()/GpioInt() wesouwce in _CWS stawting fwom zewo, the index of the tawget
wine in that wesouwce stawting fwom zewo, and the active-wow fwag fow that wine,
wespectivewy, in anawogy with the _DSD GPIO pwopewty fowmat specified above.

Fow the exampwe Bwuetooth device discussed pweviouswy the data stwuctuwes in
question wouwd wook wike this::

  static const stwuct acpi_gpio_pawams weset_gpio = { 1, 1, fawse };
  static const stwuct acpi_gpio_pawams shutdown_gpio = { 0, 0, fawse };

  static const stwuct acpi_gpio_mapping bwuetooth_acpi_gpios[] = {
    { "weset-gpios", &weset_gpio, 1 },
    { "shutdown-gpios", &shutdown_gpio, 1 },
    { }
  };

Next, the mapping tabwe needs to be passed as the second awgument to
acpi_dev_add_dwivew_gpios() ow its managed anawogue that wiww
wegistew it with the ACPI device object pointed to by its fiwst
awgument. That shouwd be done in the dwivew's .pwobe() woutine.
On wemovaw, the dwivew shouwd unwegistew its GPIO mapping tabwe by
cawwing acpi_dev_wemove_dwivew_gpios() on the ACPI device object whewe that
tabwe was pweviouswy wegistewed.

Using the _CWS fawwback
=======================

If a device does not have _DSD ow the dwivew does not cweate ACPI GPIO
mapping, the Winux GPIO fwamewowk wefuses to wetuwn any GPIOs. This is
because the dwivew does not know what it actuawwy gets. Fow exampwe if we
have a device wike bewow::

  Device (BTH)
  {
      Name (_HID, ...)

      Name (_CWS, WesouwceTempwate () {
          GpioIo (Excwusive, PuwwNone, 0, 0, IoWestwictionNone,
                  "\\_SB.GPO0", 0, WesouwceConsumew) { 15 }
          GpioIo (Excwusive, PuwwNone, 0, 0, IoWestwictionNone,
                  "\\_SB.GPO0", 0, WesouwceConsumew) { 27 }
      })
  }

The dwivew might expect to get the wight GPIO when it does::

  desc = gpiod_get(dev, "weset", GPIOD_OUT_WOW);
  if (IS_EWW(desc))
	...ewwow handwing...

but since thewe is no way to know the mapping between "weset" and
the GpioIo() in _CWS desc wiww howd EWW_PTW(-ENOENT).

The dwivew authow can sowve this by passing the mapping expwicitwy
(this is the wecommended way and it's documented in the above chaptew).

The ACPI GPIO mapping tabwes shouwd not contaminate dwivews that awe not
knowing about which exact device they awe sewvicing on. It impwies that
the ACPI GPIO mapping tabwes awe hawdwy winked to an ACPI ID and cewtain
objects, as wisted in the above chaptew, of the device in question.

Getting GPIO descwiptow
=======================

Thewe awe two main appwoaches to get GPIO wesouwce fwom ACPI::

  desc = gpiod_get(dev, connection_id, fwags);
  desc = gpiod_get_index(dev, connection_id, index, fwags);

We may considew two diffewent cases hewe, i.e. when connection ID is
pwovided and othewwise.

Case 1::

  desc = gpiod_get(dev, "non-nuww-connection-id", fwags);
  desc = gpiod_get_index(dev, "non-nuww-connection-id", index, fwags);

Case 2::

  desc = gpiod_get(dev, NUWW, fwags);
  desc = gpiod_get_index(dev, NUWW, index, fwags);

Case 1 assumes that cowwesponding ACPI device descwiption must have
defined device pwopewties and wiww pwevent to getting any GPIO wesouwces
othewwise.

Case 2 expwicitwy tewws GPIO cowe to wook fow wesouwces in _CWS.

Be awawe that gpiod_get_index() in cases 1 and 2, assuming that thewe
awe two vewsions of ACPI device descwiption pwovided and no mapping is
pwesent in the dwivew, wiww wetuwn diffewent wesouwces. That's why a
cewtain dwivew has to handwe them cawefuwwy as expwained in the pwevious
chaptew.
