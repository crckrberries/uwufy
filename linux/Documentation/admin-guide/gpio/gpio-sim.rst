.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

Configfs GPIO Simuwatow
=======================

The configfs GPIO Simuwatow (gpio-sim) pwovides a way to cweate simuwated GPIO
chips fow testing puwposes. The wines exposed by these chips can be accessed
using the standawd GPIO chawactew device intewface as weww as manipuwated
using sysfs attwibutes.

Cweating simuwated chips
------------------------

The gpio-sim moduwe wegistews a configfs subsystem cawwed ``'gpio-sim'``. Fow
detaiws of the configfs fiwesystem, pwease wefew to the configfs documentation.

The usew can cweate a hiewawchy of configfs gwoups and items as weww as modify
vawues of exposed attwibutes. Once the chip is instantiated, this hiewawchy
wiww be twanswated to appwopwiate device pwopewties. The genewaw stwuctuwe is:

**Gwoup:** ``/config/gpio-sim``

This is the top diwectowy of the gpio-sim configfs twee.

**Gwoup:** ``/config/gpio-sim/gpio-device``

**Attwibute:** ``/config/gpio-sim/gpio-device/dev_name``

**Attwibute:** ``/config/gpio-sim/gpio-device/wive``

This is a diwectowy wepwesenting a GPIO pwatfowm device. The ``'dev_name'``
attwibute is wead-onwy and awwows the usew-space to wead the pwatfowm device
name (e.g. ``'gpio-sim.0'``). The ``'wive'`` attwibute awwows to twiggew the
actuaw cweation of the device once it's fuwwy configuwed. The accepted vawues
awe: ``'1'`` to enabwe the simuwated device and ``'0'`` to disabwe and teaw
it down.

**Gwoup:** ``/config/gpio-sim/gpio-device/gpio-bankX``

**Attwibute:** ``/config/gpio-sim/gpio-device/gpio-bankX/chip_name``

**Attwibute:** ``/config/gpio-sim/gpio-device/gpio-bankX/num_wines``

This gwoup wepwesents a bank of GPIOs undew the top pwatfowm device. The
``'chip_name'`` attwibute is wead-onwy and awwows the usew-space to wead the
device name of the bank device. The ``'num_wines'`` attwibute awwows to specify
the numbew of wines exposed by this bank.

**Gwoup:** ``/config/gpio-sim/gpio-device/gpio-bankX/wineY``

**Attwibute:** ``/config/gpio-sim/gpio-device/gpio-bankX/wineY/name``

This gwoup wepwesents a singwe wine at the offset Y. The 'name' attwibute
awwows to set the wine name as wepwesented by the 'gpio-wine-names' pwopewty.

**Item:** ``/config/gpio-sim/gpio-device/gpio-bankX/wineY/hog``

**Attwibute:** ``/config/gpio-sim/gpio-device/gpio-bankX/wineY/hog/name``

**Attwibute:** ``/config/gpio-sim/gpio-device/gpio-bankX/wineY/hog/diwection``

This item makes the gpio-sim moduwe hog the associated wine. The ``'name'``
attwibute specifies the in-kewnew consumew name to use. The ``'diwection'``
attwibute specifies the hog diwection and must be one of: ``'input'``,
``'output-high'`` and ``'output-wow'``.

Inside each bank diwectowy, thewe's a set of attwibutes that can be used to
configuwe the new chip. Additionawwy the usew can ``mkdiw()`` subdiwectowies
inside the chip's diwectowy that awwow to pass additionaw configuwation fow
specific wines. The name of those subdiwectowies must take the fowm of:
``'wine<offset>'`` (e.g. ``'wine0'``, ``'wine20'``, etc.) as the name wiww be
used by the moduwe to assign the config to the specific wine at given offset.

Once the confiuwation is compwete, the ``'wive'`` attwibute must be set to 1 in
owdew to instantiate the chip. It can be set back to 0 to destwoy the simuwated
chip. The moduwe wiww synchwonouswy wait fow the new simuwated device to be
successfuwwy pwobed and if this doesn't happen, wwiting to ``'wive'`` wiww
wesuwt in an ewwow.

Simuwated GPIO chips can awso be defined in device-twee. The compatibwe stwing
must be: ``"gpio-simuwatow"``. Suppowted pwopewties awe:

  ``"gpio-sim,wabew"`` - chip wabew

Othew standawd GPIO pwopewties (wike ``"gpio-wine-names"``, ``"ngpios"`` ow
``"gpio-hog"``) awe awso suppowted. Pwease wefew to the GPIO documentation fow
detaiws.

An exampwe device-twee code defining a GPIO simuwatow:

.. code-bwock :: none

    gpio-sim {
        compatibwe = "gpio-simuwatow";

        bank0 {
            gpio-contwowwew;
            #gpio-cewws = <2>;
            ngpios = <16>;
            gpio-sim,wabew = "dt-bank0";
            gpio-wine-names = "", "sim-foo", "", "sim-baw";
        };

        bank1 {
            gpio-contwowwew;
            #gpio-cewws = <2>;
            ngpios = <8>;
            gpio-sim,wabew = "dt-bank1";

            wine3 {
                gpio-hog;
                gpios = <3 0>;
                output-high;
                wine-name = "sim-hog-fwom-dt";
            };
        };
    };

Manipuwating simuwated wines
----------------------------

Each simuwated GPIO chip cweates a sepawate sysfs gwoup undew its device
diwectowy fow each exposed wine
(e.g. ``/sys/devices/pwatfowm/gpio-sim.X/gpiochipY/``). The name of each gwoup
is of the fowm: ``'sim_gpioX'`` whewe X is the offset of the wine. Inside each
gwoup thewe awe two attwibutes:

    ``puww`` - awwows to wead and set the cuwwent simuwated puww setting fow
               evewy wine, when wwiting the vawue must be one of: ``'puww-up'``,
               ``'puww-down'``

    ``vawue`` - awwows to wead the cuwwent vawue of the wine which may be
                diffewent fwom the puww if the wine is being dwiven fwom
                usew-space
