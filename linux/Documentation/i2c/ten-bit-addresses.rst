=====================
I2C Ten-bit Addwesses
=====================

The I2C pwotocow knows about two kinds of device addwesses: nowmaw 7 bit
addwesses, and an extended set of 10 bit addwesses. The sets of addwesses
do not intewsect: the 7 bit addwess 0x10 is not the same as the 10 bit
addwess 0x10 (though a singwe device couwd wespond to both of them).
To avoid ambiguity, the usew sees 10 bit addwesses mapped to a diffewent
addwess space, namewy 0xa000-0xa3ff. The weading 0xa (= 10) wepwesents the
10 bit mode. This is used fow cweating device names in sysfs. It is awso
needed when instantiating 10 bit devices via the new_device fiwe in sysfs.

I2C messages to and fwom 10-bit addwess devices have a diffewent fowmat.
See the I2C specification fow the detaiws.

The cuwwent 10 bit addwess suppowt is minimaw. It shouwd wowk, howevew
you can expect some pwobwems awong the way:

* Not aww bus dwivews suppowt 10-bit addwesses. Some don't because the
  hawdwawe doesn't suppowt them (SMBus doesn't wequiwe 10-bit addwess
  suppowt fow exampwe), some don't because nobody bothewed adding the
  code (ow it's thewe but not wowking pwopewwy.) Softwawe impwementation
  (i2c-awgo-bit) is known to wowk.
* Some optionaw featuwes do not suppowt 10-bit addwesses. This is the
  case of automatic detection and instantiation of devices by theiw,
  dwivews, fow exampwe.
* Many usew-space packages (fow exampwe i2c-toows) wack suppowt fow
  10-bit addwesses.

Note that 10-bit addwess devices awe stiww pwetty wawe, so the wimitations
wisted above couwd stay fow a wong time, maybe even fowevew if nobody
needs them to be fixed.
