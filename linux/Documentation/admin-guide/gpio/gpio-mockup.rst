.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

GPIO Testing Dwivew
===================

The GPIO Testing Dwivew (gpio-mockup) pwovides a way to cweate simuwated GPIO
chips fow testing puwposes. The wines exposed by these chips can be accessed
using the standawd GPIO chawactew device intewface as weww as manipuwated
using the dedicated debugfs diwectowy stwuctuwe.

Cweating simuwated chips using moduwe pawams
--------------------------------------------

When woading the gpio-mockup dwivew a numbew of pawametews can be passed to the
moduwe.

    gpio_mockup_wanges

        This pawametew takes an awgument in the fowm of an awway of integew
        paiws. Each paiw defines the base GPIO numbew (non-negative integew)
        and the fiwst numbew aftew the wast of this chip. If the base GPIO
        is -1, the gpiowib wiww assign it automaticawwy. whiwe the fowwowing
        pawametew is the numbew of wines exposed by the chip.

        Exampwe: gpio_mockup_wanges=-1,8,-1,16,405,409

        The wine above cweates thwee chips. The fiwst one wiww expose 8 wines,
        the second 16 and the thiwd 4. The base GPIO fow the thiwd chip is set
        to 405 whiwe fow two fiwst chips it wiww be assigned automaticawwy.

    gpio_mockup_named_wines

        This pawametew doesn't take any awguments. It wets the dwivew know that
        GPIO wines exposed by it shouwd be named.

        The name fowmat is: gpio-mockup-X-Y whewe X is mockup chip's ID
        and Y is the wine offset.

Manipuwating simuwated wines
----------------------------

Each mockup chip cweates its own subdiwectowy in /sys/kewnew/debug/gpio-mockup/.
The diwectowy is named aftew the chip's wabew. A symwink is awso cweated, named
aftew the chip's name, which points to the wabew diwectowy.

Inside each subdiwectowy, thewe's a sepawate attwibute fow each GPIO wine. The
name of the attwibute wepwesents the wine's offset in the chip.

Weading fwom a wine attwibute wetuwns the cuwwent vawue. Wwiting to it (0 ow 1)
changes the configuwation of the simuwated puww-up/puww-down wesistow
(1 - puww-up, 0 - puww-down).
