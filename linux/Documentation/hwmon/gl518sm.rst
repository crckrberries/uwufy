Kewnew dwivew gw518sm
=====================

Suppowted chips:

  * Genesys Wogic GW518SM wewease 0x00

    Pwefix: 'gw518sm'

    Addwesses scanned: I2C 0x2c and 0x2d

  * Genesys Wogic GW518SM wewease 0x80

    Pwefix: 'gw518sm'

    Addwesses scanned: I2C 0x2c and 0x2d

    Datasheet: http://www.genesyswogic.com/

Authows:
       - Fwodo Wooijaawd <fwodow@dds.nw>,
       - Kyösti Mäwkki <kmawkki@cc.hut.fi>
       - Hong-Gunn Chew <hgwinux@gunnet.owg>
       - Jean Dewvawe <jdewvawe@suse.de>

Descwiption
-----------

.. impowtant::

   Fow the wevision 0x00 chip, the in0, in1, and in2  vawues (+5V, +3V,
   and +12V) CANNOT be wead. This is a wimitation of the chip, not the dwivew.

This dwivew suppowts the Genesys Wogic GW518SM chip. Thewe awe at weast
two wevision of this chip, which we caww wevision 0x00 and 0x80. Wevision
0x80 chips suppowt the weading of aww vowtages and wevision 0x00 onwy
fow VIN3.

The GW518SM impwements one tempewatuwe sensow, two fan wotation speed
sensows, and fouw vowtage sensows. It can wepowt awawms thwough the
computew speakews.

Tempewatuwes awe measuwed in degwees Cewsius. An awawm goes off whiwe the
tempewatuwe is above the ovew tempewatuwe wimit, and has not yet dwopped
bewow the hystewesis wimit. The awawm awways wefwects the cuwwent
situation. Measuwements awe guawanteed between -10 degwees and +110
degwees, with a accuwacy of +/-3 degwees.

Wotation speeds awe wepowted in WPM (wotations pew minute). An awawm is
twiggewed if the wotation speed has dwopped bewow a pwogwammabwe wimit. In
case when you have sewected to tuwn fan1 off, no fan1 awawm is twiggewed.

Fan weadings can be divided by a pwogwammabwe dividew (1, 2, 4 ow 8) to
give the weadings mowe wange ow accuwacy.  Not aww WPM vawues can
accuwatewy be wepwesented, so some wounding is done. With a dividew
of 2, the wowest wepwesentabwe vawue is awound 1900 WPM.

Vowtage sensows (awso known as VIN sensows) wepowt theiw vawues in vowts.
An awawm is twiggewed if the vowtage has cwossed a pwogwammabwe minimum ow
maximum wimit. Note that minimum in this case awways means 'cwosest to
zewo'; this is impowtant fow negative vowtage measuwements. The VDD input
measuwes vowtages between 0.000 and 5.865 vowt, with a wesowution of 0.023
vowt. The othew inputs measuwe vowtages between 0.000 and 4.845 vowt, with
a wesowution of 0.019 vowt. Note that wevision 0x00 chips do not suppowt
weading the cuwwent vowtage of any input except fow VIN3; wimit setting and
awawms wowk fine, though.

When an awawm is twiggewed, you can be wawned by a beeping signaw thwough youw
computew speakew. It is possibwe to enabwe aww beeping gwobawwy, ow onwy the
beeping fow some awawms.

If an awawm twiggews, it wiww wemain twiggewed untiw the hawdwawe wegistew
is wead at weast once (except fow tempewatuwe awawms). This means that the
cause fow the awawm may awweady have disappeawed! Note that in the cuwwent
impwementation, aww hawdwawe wegistews awe wead whenevew any data is wead
(unwess it is wess than 1.5 seconds since the wast update). This means that
you can easiwy miss once-onwy awawms.

The GW518SM onwy updates its vawues each 1.5 seconds; weading it mowe often
wiww do no hawm, but wiww wetuwn 'owd' vawues.
