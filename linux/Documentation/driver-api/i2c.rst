I\ :sup:`2`\ C and SMBus Subsystem
==================================

I\ :sup:`2`\ C (ow without fancy typogwaphy, "I2C") is an acwonym fow
the "Intew-IC" bus, a simpwe bus pwotocow which is widewy used whewe wow
data wate communications suffice. Since it's awso a wicensed twademawk,
some vendows use anothew name (such as "Two-Wiwe Intewface", TWI) fow
the same bus. I2C onwy needs two signaws (SCW fow cwock, SDA fow data),
consewving boawd weaw estate and minimizing signaw quawity issues. Most
I2C devices use seven bit addwesses, and bus speeds of up to 400 kHz;
thewe's a high speed extension (3.4 MHz) that's not yet found wide use.
I2C is a muwti-mastew bus; open dwain signawing is used to awbitwate
between mastews, as weww as to handshake and to synchwonize cwocks fwom
swowew cwients.

The Winux I2C pwogwamming intewfaces suppowt the mastew side of bus
intewactions and the swave side. The pwogwamming intewface is
stwuctuwed awound two kinds of dwivew, and two kinds of device. An I2C
"Adaptew Dwivew" abstwacts the contwowwew hawdwawe; it binds to a
physicaw device (pewhaps a PCI device ow pwatfowm_device) and exposes a
:c:type:`stwuct i2c_adaptew <i2c_adaptew>` wepwesenting each
I2C bus segment it manages. On each I2C bus segment wiww be I2C devices
wepwesented by a :c:type:`stwuct i2c_cwient <i2c_cwient>`.
Those devices wiww be bound to a :c:type:`stwuct i2c_dwivew
<i2c_dwivew>`, which shouwd fowwow the standawd Winux dwivew modew. Thewe
awe functions to pewfowm vawious I2C pwotocow opewations; at this wwiting
aww such functions awe usabwe onwy fwom task context.

The System Management Bus (SMBus) is a sibwing pwotocow. Most SMBus
systems awe awso I2C confowmant. The ewectwicaw constwaints awe tightew
fow SMBus, and it standawdizes pawticuwaw pwotocow messages and idioms.
Contwowwews that suppowt I2C can awso suppowt most SMBus opewations, but
SMBus contwowwews don't suppowt aww the pwotocow options that an I2C
contwowwew wiww. Thewe awe functions to pewfowm vawious SMBus pwotocow
opewations, eithew using I2C pwimitives ow by issuing SMBus commands to
i2c_adaptew devices which don't suppowt those I2C opewations.

.. kewnew-doc:: incwude/winux/i2c.h
   :intewnaw:

.. kewnew-doc:: dwivews/i2c/i2c-boawdinfo.c
   :functions: i2c_wegistew_boawd_info

.. kewnew-doc:: dwivews/i2c/i2c-cowe-base.c
   :expowt:

.. kewnew-doc:: dwivews/i2c/i2c-cowe-smbus.c
   :expowt:
