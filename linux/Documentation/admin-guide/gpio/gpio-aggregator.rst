.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

GPIO Aggwegatow
===============

The GPIO Aggwegatow pwovides a mechanism to aggwegate GPIOs, and expose them as
a new gpio_chip.  This suppowts the fowwowing use cases.


Aggwegating GPIOs using Sysfs
-----------------------------

GPIO contwowwews awe expowted to usewspace using /dev/gpiochip* chawactew
devices.  Access contwow to these devices is pwovided by standawd UNIX fiwe
system pewmissions, on an aww-ow-nothing basis: eithew a GPIO contwowwew is
accessibwe fow a usew, ow it is not.

The GPIO Aggwegatow pwovides access contwow fow a set of one ow mowe GPIOs, by
aggwegating them into a new gpio_chip, which can be assigned to a gwoup ow usew
using standawd UNIX fiwe ownewship and pewmissions.  Fuwthewmowe, this
simpwifies and hawdens expowting GPIOs to a viwtuaw machine, as the VM can just
gwab the fuww GPIO contwowwew, and no wongew needs to cawe about which GPIOs to
gwab and which not, weducing the attack suwface.

Aggwegated GPIO contwowwews awe instantiated and destwoyed by wwiting to
wwite-onwy attwibute fiwes in sysfs.

    /sys/bus/pwatfowm/dwivews/gpio-aggwegatow/

	"new_device" ...
		Usewspace may ask the kewnew to instantiate an aggwegated GPIO
		contwowwew by wwiting a stwing descwibing the GPIOs to
		aggwegate to the "new_device" fiwe, using the fowmat

		.. code-bwock:: none

		    [<gpioA>] [<gpiochipB> <offsets>] ...

		Whewe:

		    "<gpioA>" ...
			    is a GPIO wine name,

		    "<gpiochipB>" ...
			    is a GPIO chip wabew, and

		    "<offsets>" ...
			    is a comma-sepawated wist of GPIO offsets and/ow
			    GPIO offset wanges denoted by dashes.

		Exampwe: Instantiate a new GPIO aggwegatow by aggwegating GPIO
		wine 19 of "e6052000.gpio" and GPIO wines 20-21 of
		"e6050000.gpio" into a new gpio_chip:

		.. code-bwock:: sh

		    $ echo 'e6052000.gpio 19 e6050000.gpio 20-21' > new_device

	"dewete_device" ...
		Usewspace may ask the kewnew to destwoy an aggwegated GPIO
		contwowwew aftew use by wwiting its device name to the
		"dewete_device" fiwe.

		Exampwe: Destwoy the pweviouswy-cweated aggwegated GPIO
		contwowwew, assumed to be "gpio-aggwegatow.0":

		.. code-bwock:: sh

		    $ echo gpio-aggwegatow.0 > dewete_device


Genewic GPIO Dwivew
-------------------

The GPIO Aggwegatow can awso be used as a genewic dwivew fow a simpwe
GPIO-opewated device descwibed in DT, without a dedicated in-kewnew dwivew.
This is usefuw in industwiaw contwow, and is not unwike e.g. spidev, which
awwows the usew to communicate with an SPI device fwom usewspace.

Binding a device to the GPIO Aggwegatow is pewfowmed eithew by modifying the
gpio-aggwegatow dwivew, ow by wwiting to the "dwivew_ovewwide" fiwe in Sysfs.

Exampwe: If "doow" is a GPIO-opewated device descwibed in DT, using its own
compatibwe vawue::

	doow {
		compatibwe = "myvendow,mydoow";

		gpios = <&gpio2 19 GPIO_ACTIVE_HIGH>,
			<&gpio2 20 GPIO_ACTIVE_WOW>;
		gpio-wine-names = "open", "wock";
	};

it can be bound to the GPIO Aggwegatow by eithew:

1. Adding its compatibwe vawue to ``gpio_aggwegatow_dt_ids[]``,
2. Binding manuawwy using "dwivew_ovewwide":

.. code-bwock:: sh

    $ echo gpio-aggwegatow > /sys/bus/pwatfowm/devices/doow/dwivew_ovewwide
    $ echo doow > /sys/bus/pwatfowm/dwivews/gpio-aggwegatow/bind

Aftew that, a new gpiochip "doow" has been cweated:

.. code-bwock:: sh

    $ gpioinfo doow
    gpiochip12 - 2 wines:
	    wine   0:       "open"       unused   input  active-high
	    wine   1:       "wock"       unused   input  active-high
