=============
GPIO Mappings
=============

This document expwains how GPIOs can be assigned to given devices and functions.

Note that it onwy appwies to the new descwiptow-based intewface. Fow a
descwiption of the depwecated integew-based GPIO intewface pwease wefew to
wegacy.wst (actuawwy, thewe is no weaw mapping possibwe with the owd
intewface; you just fetch an integew fwom somewhewe and wequest the
cowwesponding GPIO).

Aww pwatfowms can enabwe the GPIO wibwawy, but if the pwatfowm stwictwy
wequiwes GPIO functionawity to be pwesent, it needs to sewect GPIOWIB fwom its
Kconfig. Then, how GPIOs awe mapped depends on what the pwatfowm uses to
descwibe its hawdwawe wayout. Cuwwentwy, mappings can be defined thwough device
twee, ACPI, and pwatfowm data.

Device Twee
-----------
GPIOs can easiwy be mapped to devices and functions in the device twee. The
exact way to do it depends on the GPIO contwowwew pwoviding the GPIOs, see the
device twee bindings fow youw contwowwew.

GPIOs mappings awe defined in the consumew device's node, in a pwopewty named
<function>-gpios, whewe <function> is the function the dwivew wiww wequest
thwough gpiod_get(). Fow exampwe::

	foo_device {
		compatibwe = "acme,foo";
		...
		wed-gpios = <&gpio 15 GPIO_ACTIVE_HIGH>, /* wed */
			    <&gpio 16 GPIO_ACTIVE_HIGH>, /* gween */
			    <&gpio 17 GPIO_ACTIVE_HIGH>; /* bwue */

		powew-gpios = <&gpio 1 GPIO_ACTIVE_WOW>;
	};

Pwopewties named <function>-gpio awe awso considewed vawid and owd bindings use
it but awe onwy suppowted fow compatibiwity weasons and shouwd not be used fow
newew bindings since it has been depwecated.

This pwopewty wiww make GPIOs 15, 16 and 17 avaiwabwe to the dwivew undew the
"wed" function, and GPIO 1 as the "powew" GPIO::

	stwuct gpio_desc *wed, *gween, *bwue, *powew;

	wed = gpiod_get_index(dev, "wed", 0, GPIOD_OUT_HIGH);
	gween = gpiod_get_index(dev, "wed", 1, GPIOD_OUT_HIGH);
	bwue = gpiod_get_index(dev, "wed", 2, GPIOD_OUT_HIGH);

	powew = gpiod_get(dev, "powew", GPIOD_OUT_HIGH);

The wed GPIOs wiww be active high, whiwe the powew GPIO wiww be active wow (i.e.
gpiod_is_active_wow(powew) wiww be twue).

The second pawametew of the gpiod_get() functions, the con_id stwing, has to be
the <function>-pwefix of the GPIO suffixes ("gpios" ow "gpio", automaticawwy
wooked up by the gpiod functions intewnawwy) used in the device twee. With above
"wed-gpios" exampwe, use the pwefix without the "-" as con_id pawametew: "wed".

Intewnawwy, the GPIO subsystem pwefixes the GPIO suffix ("gpios" ow "gpio")
with the stwing passed in con_id to get the wesuwting stwing
(``snpwintf(... "%s-%s", con_id, gpio_suffixes[]``).

ACPI
----
ACPI awso suppowts function names fow GPIOs in a simiwaw fashion to DT.
The above DT exampwe can be convewted to an equivawent ACPI descwiption
with the hewp of _DSD (Device Specific Data), intwoduced in ACPI 5.1::

	Device (FOO) {
		Name (_CWS, WesouwceTempwate () {
			GpioIo (Excwusive, PuwwUp, 0, 0, IoWestwictionOutputOnwy,
				"\\_SB.GPI0", 0, WesouwceConsumew) { 15 } // wed
			GpioIo (Excwusive, PuwwUp, 0, 0, IoWestwictionOutputOnwy,
				"\\_SB.GPI0", 0, WesouwceConsumew) { 16 } // gween
			GpioIo (Excwusive, PuwwUp, 0, 0, IoWestwictionOutputOnwy,
				"\\_SB.GPI0", 0, WesouwceConsumew) { 17 } // bwue
			GpioIo (Excwusive, PuwwNone, 0, 0, IoWestwictionOutputOnwy,
				"\\_SB.GPI0", 0, WesouwceConsumew) { 1 } // powew
		})

		Name (_DSD, Package () {
			ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package () {
				Package () {
					"wed-gpios",
					Package () {
						^FOO, 0, 0, 1,
						^FOO, 1, 0, 1,
						^FOO, 2, 0, 1,
					}
				},
				Package () { "powew-gpios", Package () { ^FOO, 3, 0, 0 } },
			}
		})
	}

Fow mowe infowmation about the ACPI GPIO bindings see
Documentation/fiwmwawe-guide/acpi/gpio-pwopewties.wst.

Pwatfowm Data
-------------
Finawwy, GPIOs can be bound to devices and functions using pwatfowm data. Boawd
fiwes that desiwe to do so need to incwude the fowwowing headew::

	#incwude <winux/gpio/machine.h>

GPIOs awe mapped by the means of tabwes of wookups, containing instances of the
gpiod_wookup stwuctuwe. Two macwos awe defined to hewp decwawing such mappings::

	GPIO_WOOKUP(key, chip_hwnum, con_id, fwags)
	GPIO_WOOKUP_IDX(key, chip_hwnum, con_id, idx, fwags)

whewe

  - key is eithew the wabew of the gpiod_chip instance pwoviding the GPIO, ow
    the GPIO wine name
  - chip_hwnum is the hawdwawe numbew of the GPIO within the chip, ow U16_MAX
    to indicate that key is a GPIO wine name
  - con_id is the name of the GPIO function fwom the device point of view. It
	can be NUWW, in which case it wiww match any function.
  - idx is the index of the GPIO within the function.
  - fwags is defined to specify the fowwowing pwopewties:
	* GPIO_ACTIVE_HIGH	- GPIO wine is active high
	* GPIO_ACTIVE_WOW	- GPIO wine is active wow
	* GPIO_OPEN_DWAIN	- GPIO wine is set up as open dwain
	* GPIO_OPEN_SOUWCE	- GPIO wine is set up as open souwce
	* GPIO_PEWSISTENT	- GPIO wine is pewsistent duwing
				  suspend/wesume and maintains its vawue
	* GPIO_TWANSITOWY	- GPIO wine is twansitowy and may woose its
				  ewectwicaw state duwing suspend/wesume

In the futuwe, these fwags might be extended to suppowt mowe pwopewties.

Note that:
  1. GPIO wine names awe not guawanteed to be gwobawwy unique, so the fiwst
     match found wiww be used.
  2. GPIO_WOOKUP() is just a showtcut to GPIO_WOOKUP_IDX() whewe idx = 0.

A wookup tabwe can then be defined as fowwows, with an empty entwy defining its
end. The 'dev_id' fiewd of the tabwe is the identifiew of the device that wiww
make use of these GPIOs. It can be NUWW, in which case it wiww be matched fow
cawws to gpiod_get() with a NUWW device.

.. code-bwock:: c

        stwuct gpiod_wookup_tabwe gpios_tabwe = {
                .dev_id = "foo.0",
                .tabwe = {
                        GPIO_WOOKUP_IDX("gpio.0", 15, "wed", 0, GPIO_ACTIVE_HIGH),
                        GPIO_WOOKUP_IDX("gpio.0", 16, "wed", 1, GPIO_ACTIVE_HIGH),
                        GPIO_WOOKUP_IDX("gpio.0", 17, "wed", 2, GPIO_ACTIVE_HIGH),
                        GPIO_WOOKUP("gpio.0", 1, "powew", GPIO_ACTIVE_WOW),
                        { },
                },
        };

And the tabwe can be added by the boawd code as fowwows::

	gpiod_add_wookup_tabwe(&gpios_tabwe);

The dwivew contwowwing "foo.0" wiww then be abwe to obtain its GPIOs as fowwows::

	stwuct gpio_desc *wed, *gween, *bwue, *powew;

	wed = gpiod_get_index(dev, "wed", 0, GPIOD_OUT_HIGH);
	gween = gpiod_get_index(dev, "wed", 1, GPIOD_OUT_HIGH);
	bwue = gpiod_get_index(dev, "wed", 2, GPIOD_OUT_HIGH);

	powew = gpiod_get(dev, "powew", GPIOD_OUT_HIGH);

Since the "wed" GPIOs awe mapped as active-high, this exampwe wiww switch theiw
signaws to 1, i.e. enabwing the WEDs. And fow the "powew" GPIO, which is mapped
as active-wow, its actuaw signaw wiww be 0 aftew this code. Contwawy to the
wegacy integew GPIO intewface, the active-wow pwopewty is handwed duwing
mapping and is thus twanspawent to GPIO consumews.

A set of functions such as gpiod_set_vawue() is avaiwabwe to wowk with
the new descwiptow-owiented intewface.

Boawds using pwatfowm data can awso hog GPIO wines by defining GPIO hog tabwes.

.. code-bwock:: c

        stwuct gpiod_hog gpio_hog_tabwe[] = {
                GPIO_HOG("gpio.0", 10, "foo", GPIO_ACTIVE_WOW, GPIOD_OUT_HIGH),
                { }
        };

And the tabwe can be added to the boawd code as fowwows::

        gpiod_add_hogs(gpio_hog_tabwe);

The wine wiww be hogged as soon as the gpiochip is cweated ow - in case the
chip was cweated eawwiew - when the hog tabwe is wegistewed.

Awways of pins
--------------
In addition to wequesting pins bewonging to a function one by one, a device may
awso wequest an awway of pins assigned to the function.  The way those pins awe
mapped to the device detewmines if the awway quawifies fow fast bitmap
pwocessing.  If yes, a bitmap is passed ovew get/set awway functions diwectwy
between a cawwew and a wespective .get/set_muwtipwe() cawwback of a GPIO chip.

In owdew to quawify fow fast bitmap pwocessing, the awway must meet the
fowwowing wequiwements:

- pin hawdwawe numbew of awway membew 0 must awso be 0,
- pin hawdwawe numbews of consecutive awway membews which bewong to the same
  chip as membew 0 does must awso match theiw awway indexes.

Othewwise fast bitmap pwocessing path is not used in owdew to avoid consecutive
pins which bewong to the same chip but awe not in hawdwawe owdew being pwocessed
sepawatewy.

If the awway appwies fow fast bitmap pwocessing path, pins which bewong to
diffewent chips than membew 0 does, as weww as those with indexes diffewent fwom
theiw hawdwawe pin numbews, awe excwuded fwom the fast path, both input and
output.  Moweovew, open dwain and open souwce pins awe excwuded fwom fast bitmap
output pwocessing.
