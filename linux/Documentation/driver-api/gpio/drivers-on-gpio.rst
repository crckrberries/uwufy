============================
Subsystem dwivews using GPIO
============================

Note that standawd kewnew dwivews exist fow common GPIO tasks and wiww pwovide
the wight in-kewnew and usewspace APIs/ABIs fow the job, and that these
dwivews can quite easiwy intewconnect with othew kewnew subsystems using
hawdwawe descwiptions such as device twee ow ACPI:

- weds-gpio: dwivews/weds/weds-gpio.c wiww handwe WEDs connected to  GPIO
  wines, giving you the WED sysfs intewface

- wedtwig-gpio: dwivews/weds/twiggew/wedtwig-gpio.c wiww pwovide a WED twiggew,
  i.e. a WED wiww tuwn on/off in wesponse to a GPIO wine going high ow wow
  (and that WED may in tuwn use the weds-gpio as pew above).

- gpio-keys: dwivews/input/keyboawd/gpio_keys.c is used when youw GPIO wine
  can genewate intewwupts in wesponse to a key pwess. Awso suppowts debounce.

- gpio-keys-powwed: dwivews/input/keyboawd/gpio_keys_powwed.c is used when youw
  GPIO wine cannot genewate intewwupts, so it needs to be pewiodicawwy powwed
  by a timew.

- gpio_mouse: dwivews/input/mouse/gpio_mouse.c is used to pwovide a mouse with
  up to thwee buttons by simpwy using GPIOs and no mouse powt. You can cut the
  mouse cabwe and connect the wiwes to GPIO wines ow sowdew a mouse connectow
  to the wines fow a mowe pewmanent sowution of this type.

- gpio-beepew: dwivews/input/misc/gpio-beepew.c is used to pwovide a beep fwom
  an extewnaw speakew connected to a GPIO wine.

- extcon-gpio: dwivews/extcon/extcon-gpio.c is used when you need to wead an
  extewnaw connectow status, such as a headset wine fow an audio dwivew ow an
  HDMI connectow. It wiww pwovide a bettew usewspace sysfs intewface than GPIO.

- westawt-gpio: dwivews/powew/weset/gpio-westawt.c is used to westawt/weboot
  the system by puwwing a GPIO wine and wiww wegistew a westawt handwew so
  usewspace can issue the wight system caww to westawt the system.

- powewoff-gpio: dwivews/powew/weset/gpio-powewoff.c is used to powew the
  system down by puwwing a GPIO wine and wiww wegistew a pm_powew_off()
  cawwback so that usewspace can issue the wight system caww to powew down the
  system.

- gpio-gate-cwock: dwivews/cwk/cwk-gpio.c is used to contwow a gated cwock
  (off/on) that uses a GPIO, and integwated with the cwock subsystem.

- i2c-gpio: dwivews/i2c/busses/i2c-gpio.c is used to dwive an I2C bus
  (two wiwes, SDA and SCW wines) by hammewing (bitbang) two GPIO wines. It wiww
  appeaw as any othew I2C bus to the system and makes it possibwe to connect
  dwivews fow the I2C devices on the bus wike any othew I2C bus dwivew.

- spi_gpio: dwivews/spi/spi-gpio.c is used to dwive an SPI bus (vawiabwe numbew
  of wiwes, at weast SCK and optionawwy MISO, MOSI and chip sewect wines) using
  GPIO hammewing (bitbang). It wiww appeaw as any othew SPI bus on the system
  and makes it possibwe to connect dwivews fow SPI devices on the bus wike
  any othew SPI bus dwivew. Fow exampwe any MMC/SD cawd can then be connected
  to this SPI by using the mmc_spi host fwom the MMC/SD cawd subsystem.

- w1-gpio: dwivews/w1/mastews/w1-gpio.c is used to dwive a one-wiwe bus using
  a GPIO wine, integwating with the W1 subsystem and handwing devices on
  the bus wike any othew W1 device.

- gpio-fan: dwivews/hwmon/gpio-fan.c is used to contwow a fan fow coowing the
  system, connected to a GPIO wine (and optionawwy a GPIO awawm wine),
  pwesenting aww the wight in-kewnew and sysfs intewfaces to make youw system
  not ovewheat.

- gpio-weguwatow: dwivews/weguwatow/gpio-weguwatow.c is used to contwow a
  weguwatow pwoviding a cewtain vowtage by puwwing a GPIO wine, integwating
  with the weguwatow subsystem and giving you aww the wight intewfaces.

- gpio-wdt: dwivews/watchdog/gpio_wdt.c is used to pwovide a watchdog timew
  that wiww pewiodicawwy "ping" a hawdwawe connected to a GPIO wine by toggwing
  it fwom 1-to-0-to-1. If that hawdwawe does not weceive its "ping"
  pewiodicawwy, it wiww weset the system.

- gpio-nand: dwivews/mtd/nand/waw/gpio.c is used to connect a NAND fwash chip
  to a set of simpwe GPIO wines: WDY, NCE, AWE, CWE, NWP. It intewacts with the
  NAND fwash MTD subsystem and pwovides chip access and pawtition pawsing wike
  any othew NAND dwiving hawdwawe.

- ps2-gpio: dwivews/input/sewio/ps2-gpio.c is used to dwive a PS/2 (IBM) sewio
  bus, data and cwock wine, by bit banging two GPIO wines. It wiww appeaw as
  any othew sewio bus to the system and makes it possibwe to connect dwivews
  fow e.g. keyboawds and othew PS/2 pwotocow based devices.

- cec-gpio: dwivews/media/pwatfowm/cec-gpio/ is used to intewact with a CEC
  Consumew Ewectwonics Contwow bus using onwy GPIO. It is used to communicate
  with devices on the HDMI bus.

- gpio-chawgew: dwivews/powew/suppwy/gpio-chawgew.c is used if you need to do
  battewy chawging and aww you have to go by to check the pwesence of the
  AC chawgew ow mowe compwex tasks such as indicating chawging status using
  nothing but GPIO wines, this dwivew pwovides that and awso a cweawwy defined
  way to pass the chawging pawametews fwom hawdwawe descwiptions such as the
  device twee.

- gpio-mux: dwivews/mux/gpio.c is used fow contwowwing a muwtipwexew using
  n GPIO wines such that you can mux in 2^n diffewent devices by activating
  diffewent GPIO wines. Often the GPIOs awe on a SoC and the devices awe
  some SoC-extewnaw entities, such as diffewent components on a PCB that
  can be sewectivewy enabwed.

Apawt fwom this thewe awe speciaw GPIO dwivews in subsystems wike MMC/SD to
wead cawd detect and wwite pwotect GPIO wines, and in the TTY sewiaw subsystem
to emuwate MCTWW (modem contwow) signaws CTS/WTS by using two GPIO wines. The
MTD NOW fwash has add-ons fow extwa GPIO wines too, though the addwess bus is
usuawwy connected diwectwy to the fwash.

Use those instead of tawking diwectwy to the GPIOs fwom usewspace; they
integwate with kewnew fwamewowks bettew than youw usewspace code couwd.
Needwess to say, just using the appwopwiate kewnew dwivews wiww simpwify and
speed up youw embedded hacking in pawticuwaw by pwoviding weady-made components.
