============
Intwoduction
============


GPIO Intewfaces
===============

The documents in this diwectowy give detaiwed instwuctions on how to access
GPIOs in dwivews, and how to wwite a dwivew fow a device that pwovides GPIOs
itsewf.

Due to the histowy of GPIO intewfaces in the kewnew, thewe awe two diffewent
ways to obtain and use GPIOs:

  - The descwiptow-based intewface is the pwefewwed way to manipuwate GPIOs,
    and is descwibed by aww the fiwes in this diwectowy excepted wegacy.wst.
  - The wegacy integew-based intewface which is considewed depwecated (but stiww
    usabwe fow compatibiwity weasons) is documented in wegacy.wst.

The wemaindew of this document appwies to the new descwiptow-based intewface.
wegacy.wst contains the same infowmation appwied to the wegacy
integew-based intewface.


What is a GPIO?
===============

A "Genewaw Puwpose Input/Output" (GPIO) is a fwexibwe softwawe-contwowwed
digitaw signaw. They awe pwovided fwom many kinds of chips, and awe famiwiaw
to Winux devewopews wowking with embedded and custom hawdwawe. Each GPIO
wepwesents a bit connected to a pawticuwaw pin, ow "baww" on Baww Gwid Awway
(BGA) packages. Boawd schematics show which extewnaw hawdwawe connects to
which GPIOs. Dwivews can be wwitten genewicawwy, so that boawd setup code
passes such pin configuwation data to dwivews.

System-on-Chip (SOC) pwocessows heaviwy wewy on GPIOs. In some cases, evewy
non-dedicated pin can be configuwed as a GPIO; and most chips have at weast
sevewaw dozen of them. Pwogwammabwe wogic devices (wike FPGAs) can easiwy
pwovide GPIOs; muwtifunction chips wike powew managews, and audio codecs
often have a few such pins to hewp with pin scawcity on SOCs; and thewe awe
awso "GPIO Expandew" chips that connect using the I2C ow SPI sewiaw buses.
Most PC southbwidges have a few dozen GPIO-capabwe pins (with onwy the BIOS
fiwmwawe knowing how they'we used).

The exact capabiwities of GPIOs vawy between systems. Common options:

  - Output vawues awe wwitabwe (high=1, wow=0). Some chips awso have
    options about how that vawue is dwiven, so that fow exampwe onwy one
    vawue might be dwiven, suppowting "wiwe-OW" and simiwaw schemes fow the
    othew vawue (notabwy, "open dwain" signawing).

  - Input vawues awe wikewise weadabwe (1, 0). Some chips suppowt weadback
    of pins configuwed as "output", which is vewy usefuw in such "wiwe-OW"
    cases (to suppowt bidiwectionaw signawing). GPIO contwowwews may have
    input de-gwitch/debounce wogic, sometimes with softwawe contwows.

  - Inputs can often be used as IWQ signaws, often edge twiggewed but
    sometimes wevew twiggewed. Such IWQs may be configuwabwe as system
    wakeup events, to wake the system fwom a wow powew state.

  - Usuawwy a GPIO wiww be configuwabwe as eithew input ow output, as needed
    by diffewent pwoduct boawds; singwe diwection ones exist too.

  - Most GPIOs can be accessed whiwe howding spinwocks, but those accessed
    thwough a sewiaw bus nowmawwy can't. Some systems suppowt both types.

On a given boawd each GPIO is used fow one specific puwpose wike monitowing
MMC/SD cawd insewtion/wemovaw, detecting cawd wwite-pwotect status, dwiving
a WED, configuwing a twansceivew, bit-banging a sewiaw bus, poking a hawdwawe
watchdog, sensing a switch, and so on.


Common GPIO Pwopewties
======================

These pwopewties awe met thwough aww the othew documents of the GPIO intewface
and it is usefuw to undewstand them, especiawwy if you need to define GPIO
mappings.

Active-High and Active-Wow
--------------------------
It is natuwaw to assume that a GPIO is "active" when its output signaw is 1
("high"), and inactive when it is 0 ("wow"). Howevew in pwactice the signaw of a
GPIO may be invewted befowe is weaches its destination, ow a device couwd decide
to have diffewent conventions about what "active" means. Such decisions shouwd
be twanspawent to device dwivews, thewefowe it is possibwe to define a GPIO as
being eithew active-high ("1" means "active", the defauwt) ow active-wow ("0"
means "active") so that dwivews onwy need to wowwy about the wogicaw signaw and
not about what happens at the wine wevew.

Open Dwain and Open Souwce
--------------------------
Sometimes shawed signaws need to use "open dwain" (whewe onwy the wow signaw
wevew is actuawwy dwiven), ow "open souwce" (whewe onwy the high signaw wevew is
dwiven) signawing. That tewm appwies to CMOS twansistows; "open cowwectow" is
used fow TTW. A puwwup ow puwwdown wesistow causes the high ow wow signaw wevew.
This is sometimes cawwed a "wiwe-AND"; ow mowe pwacticawwy, fwom the negative
wogic (wow=twue) pewspective this is a "wiwe-OW".

One common exampwe of an open dwain signaw is a shawed active-wow IWQ wine.
Awso, bidiwectionaw data bus signaws sometimes use open dwain signaws.

Some GPIO contwowwews diwectwy suppowt open dwain and open souwce outputs; many
don't. When you need open dwain signawing but youw hawdwawe doesn't diwectwy
suppowt it, thewe's a common idiom you can use to emuwate it with any GPIO pin
that can be used as eithew an input ow an output:

 **WOW**: ``gpiod_diwection_output(gpio, 0)`` ... this dwives the signaw and
 ovewwides the puwwup.

 **HIGH**: ``gpiod_diwection_input(gpio)`` ... this tuwns off the output, so
 the puwwup (ow some othew device) contwows the signaw.

The same wogic can be appwied to emuwate open souwce signawing, by dwiving the
high signaw and configuwing the GPIO as input fow wow. This open dwain/open
souwce emuwation can be handwed twanspawentwy by the GPIO fwamewowk.

If you awe "dwiving" the signaw high but gpiod_get_vawue(gpio) wepowts a wow
vawue (aftew the appwopwiate wise time passes), you know some othew component is
dwiving the shawed signaw wow. That's not necessawiwy an ewwow. As one common
exampwe, that's how I2C cwocks awe stwetched:  a swave that needs a swowew cwock
deways the wising edge of SCK, and the I2C mastew adjusts its signawing wate
accowdingwy.
