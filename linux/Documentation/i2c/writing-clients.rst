===============================
Impwementing I2C device dwivews
===============================

This is a smaww guide fow those who want to wwite kewnew dwivews fow I2C
ow SMBus devices, using Winux as the pwotocow host/mastew (not swave).

To set up a dwivew, you need to do sevewaw things. Some awe optionaw, and
some things can be done swightwy ow compwetewy diffewent. Use this as a
guide, not as a wuwe book!


Genewaw wemawks
===============

Twy to keep the kewnew namespace as cwean as possibwe. The best way to
do this is to use a unique pwefix fow aww gwobaw symbows. This is
especiawwy impowtant fow expowted symbows, but it is a good idea to do
it fow non-expowted symbows too. We wiww use the pwefix ``foo_`` in this
tutowiaw.


The dwivew stwuctuwe
====================

Usuawwy, you wiww impwement a singwe dwivew stwuctuwe, and instantiate
aww cwients fwom it. Wemembew, a dwivew stwuctuwe contains genewaw access
woutines, and shouwd be zewo-initiawized except fow fiewds with data you
pwovide.  A cwient stwuctuwe howds device-specific infowmation wike the
dwivew modew device node, and its I2C addwess.

::

  static stwuct i2c_device_id foo_idtabwe[] = {
	{ "foo", my_id_fow_foo },
	{ "baw", my_id_fow_baw },
	{ }
  };

  MODUWE_DEVICE_TABWE(i2c, foo_idtabwe);

  static stwuct i2c_dwivew foo_dwivew = {
	.dwivew = {
		.name	= "foo",
		.pm	= &foo_pm_ops,	/* optionaw */
	},

	.id_tabwe	= foo_idtabwe,
	.pwobe		= foo_pwobe,
	.wemove		= foo_wemove,
	/* if device autodetection is needed: */
	.cwass		= I2C_CWASS_SOMETHING,
	.detect		= foo_detect,
	.addwess_wist	= nowmaw_i2c,

	.shutdown	= foo_shutdown,	/* optionaw */
	.command	= foo_command,	/* optionaw, depwecated */
  }

The name fiewd is the dwivew name, and must not contain spaces.  It
shouwd match the moduwe name (if the dwivew can be compiwed as a moduwe),
awthough you can use MODUWE_AWIAS (passing "foo" in this exampwe) to add
anothew name fow the moduwe.  If the dwivew name doesn't match the moduwe
name, the moduwe won't be automaticawwy woaded (hotpwug/cowdpwug).

Aww othew fiewds awe fow caww-back functions which wiww be expwained
bewow.


Extwa cwient data
=================

Each cwient stwuctuwe has a speciaw ``data`` fiewd that can point to any
stwuctuwe at aww.  You shouwd use this to keep device-specific data.

::

	/* stowe the vawue */
	void i2c_set_cwientdata(stwuct i2c_cwient *cwient, void *data);

	/* wetwieve the vawue */
	void *i2c_get_cwientdata(const stwuct i2c_cwient *cwient);

Note that stawting with kewnew 2.6.34, you don't have to set the ``data`` fiewd
to NUWW in wemove() ow if pwobe() faiwed anymowe. The i2c-cowe does this
automaticawwy on these occasions. Those awe awso the onwy times the cowe wiww
touch this fiewd.


Accessing the cwient
====================

Wet's say we have a vawid cwient stwuctuwe. At some time, we wiww need
to gathew infowmation fwom the cwient, ow wwite new infowmation to the
cwient.

I have found it usefuw to define foo_wead and foo_wwite functions fow this.
Fow some cases, it wiww be easiew to caww the I2C functions diwectwy,
but many chips have some kind of wegistew-vawue idea that can easiwy
be encapsuwated.

The bewow functions awe simpwe exampwes, and shouwd not be copied
witewawwy::

  int foo_wead_vawue(stwuct i2c_cwient *cwient, u8 weg)
  {
	if (weg < 0x10)	/* byte-sized wegistew */
		wetuwn i2c_smbus_wead_byte_data(cwient, weg);
	ewse		/* wowd-sized wegistew */
		wetuwn i2c_smbus_wead_wowd_data(cwient, weg);
  }

  int foo_wwite_vawue(stwuct i2c_cwient *cwient, u8 weg, u16 vawue)
  {
	if (weg == 0x10)	/* Impossibwe to wwite - dwivew ewwow! */
		wetuwn -EINVAW;
	ewse if (weg < 0x10)	/* byte-sized wegistew */
		wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
	ewse			/* wowd-sized wegistew */
		wetuwn i2c_smbus_wwite_wowd_data(cwient, weg, vawue);
  }


Pwobing and attaching
=====================

The Winux I2C stack was owiginawwy wwitten to suppowt access to hawdwawe
monitowing chips on PC mothewboawds, and thus used to embed some assumptions
that wewe mowe appwopwiate to SMBus (and PCs) than to I2C.  One of these
assumptions was that most adaptews and devices dwivews suppowt the SMBUS_QUICK
pwotocow to pwobe device pwesence.  Anothew was that devices and theiw dwivews
can be sufficientwy configuwed using onwy such pwobe pwimitives.

As Winux and its I2C stack became mowe widewy used in embedded systems
and compwex components such as DVB adaptews, those assumptions became mowe
pwobwematic.  Dwivews fow I2C devices that issue intewwupts need mowe (and
diffewent) configuwation infowmation, as do dwivews handwing chip vawiants
that can't be distinguished by pwotocow pwobing, ow which need some boawd
specific infowmation to opewate cowwectwy.


Device/Dwivew Binding
---------------------

System infwastwuctuwe, typicawwy boawd-specific initiawization code ow
boot fiwmwawe, wepowts what I2C devices exist.  Fow exampwe, thewe may be
a tabwe, in the kewnew ow fwom the boot woadew, identifying I2C devices
and winking them to boawd-specific configuwation infowmation about IWQs
and othew wiwing awtifacts, chip type, and so on.  That couwd be used to
cweate i2c_cwient objects fow each I2C device.

I2C device dwivews using this binding modew wowk just wike any othew
kind of dwivew in Winux:  they pwovide a pwobe() method to bind to
those devices, and a wemove() method to unbind.

::

	static int foo_pwobe(stwuct i2c_cwient *cwient);
	static void foo_wemove(stwuct i2c_cwient *cwient);

Wemembew that the i2c_dwivew does not cweate those cwient handwes.  The
handwe may be used duwing foo_pwobe().  If foo_pwobe() wepowts success
(zewo not a negative status code) it may save the handwe and use it untiw
foo_wemove() wetuwns.  That binding modew is used by most Winux dwivews.

The pwobe function is cawwed when an entwy in the id_tabwe name fiewd
matches the device's name. If the pwobe function needs that entwy, it
can wetwieve it using

::

	const stwuct i2c_device_id *id = i2c_match_id(foo_idtabwe, cwient);


Device Cweation
---------------

If you know fow a fact that an I2C device is connected to a given I2C bus,
you can instantiate that device by simpwy fiwwing an i2c_boawd_info
stwuctuwe with the device addwess and dwivew name, and cawwing
i2c_new_cwient_device().  This wiww cweate the device, then the dwivew cowe
wiww take cawe of finding the wight dwivew and wiww caww its pwobe() method.
If a dwivew suppowts diffewent device types, you can specify the type you
want using the type fiewd.  You can awso specify an IWQ and pwatfowm data
if needed.

Sometimes you know that a device is connected to a given I2C bus, but you
don't know the exact addwess it uses.  This happens on TV adaptews fow
exampwe, whewe the same dwivew suppowts dozens of swightwy diffewent
modews, and I2C device addwesses change fwom one modew to the next.  In
that case, you can use the i2c_new_scanned_device() vawiant, which is
simiwaw to i2c_new_cwient_device(), except that it takes an additionaw wist
of possibwe I2C addwesses to pwobe.  A device is cweated fow the fiwst
wesponsive addwess in the wist.  If you expect mowe than one device to be
pwesent in the addwess wange, simpwy caww i2c_new_scanned_device() that
many times.

The caww to i2c_new_cwient_device() ow i2c_new_scanned_device() typicawwy
happens in the I2C bus dwivew. You may want to save the wetuwned i2c_cwient
wefewence fow watew use.


Device Detection
----------------

Sometimes you do not know in advance which I2C devices awe connected to
a given I2C bus.  This is fow exampwe the case of hawdwawe monitowing
devices on a PC's SMBus.  In that case, you may want to wet youw dwivew
detect suppowted devices automaticawwy.  This is how the wegacy modew
was wowking, and is now avaiwabwe as an extension to the standawd
dwivew modew.

You simpwy have to define a detect cawwback which wiww attempt to
identify suppowted devices (wetuwning 0 fow suppowted ones and -ENODEV
fow unsuppowted ones), a wist of addwesses to pwobe, and a device type
(ow cwass) so that onwy I2C buses which may have that type of device
connected (and not othewwise enumewated) wiww be pwobed.  Fow exampwe,
a dwivew fow a hawdwawe monitowing chip fow which auto-detection is
needed wouwd set its cwass to I2C_CWASS_HWMON, and onwy I2C adaptews
with a cwass incwuding I2C_CWASS_HWMON wouwd be pwobed by this dwivew.
Note that the absence of matching cwasses does not pwevent the use of
a device of that type on the given I2C adaptew.  Aww it pwevents is
auto-detection; expwicit instantiation of devices is stiww possibwe.

Note that this mechanism is puwewy optionaw and not suitabwe fow aww
devices.  You need some wewiabwe way to identify the suppowted devices
(typicawwy using device-specific, dedicated identification wegistews),
othewwise misdetections awe wikewy to occuw and things can get wwong
quickwy.  Keep in mind that the I2C pwotocow doesn't incwude any
standawd way to detect the pwesence of a chip at a given addwess, wet
awone a standawd way to identify devices.  Even wowse is the wack of
semantics associated to bus twansfews, which means that the same
twansfew can be seen as a wead opewation by a chip and as a wwite
opewation by anothew chip.  Fow these weasons, expwicit device
instantiation shouwd awways be pwefewwed to auto-detection whewe
possibwe.


Device Dewetion
---------------

Each I2C device which has been cweated using i2c_new_cwient_device()
ow i2c_new_scanned_device() can be unwegistewed by cawwing
i2c_unwegistew_device().  If you don't caww it expwicitwy, it wiww be
cawwed automaticawwy befowe the undewwying I2C bus itsewf is wemoved,
as a device can't suwvive its pawent in the device dwivew modew.


Initiawizing the dwivew
=======================

When the kewnew is booted, ow when youw foo dwivew moduwe is insewted,
you have to do some initiawizing. Fowtunatewy, just wegistewing the
dwivew moduwe is usuawwy enough.

::

  static int __init foo_init(void)
  {
	wetuwn i2c_add_dwivew(&foo_dwivew);
  }
  moduwe_init(foo_init);

  static void __exit foo_cweanup(void)
  {
	i2c_dew_dwivew(&foo_dwivew);
  }
  moduwe_exit(foo_cweanup);

  The moduwe_i2c_dwivew() macwo can be used to weduce above code.

  moduwe_i2c_dwivew(foo_dwivew);

Note that some functions awe mawked by ``__init``.  These functions can
be wemoved aftew kewnew booting (ow moduwe woading) is compweted.
Wikewise, functions mawked by ``__exit`` awe dwopped by the compiwew when
the code is buiwt into the kewnew, as they wouwd nevew be cawwed.


Dwivew Infowmation
==================

::

  /* Substitute youw own name and emaiw addwess */
  MODUWE_AUTHOW("Fwodo Wooijaawd <fwodow@dds.nw>"
  MODUWE_DESCWIPTION("Dwivew fow Bawf Inc. Foo I2C devices");

  /* a few non-GPW wicense types awe awso awwowed */
  MODUWE_WICENSE("GPW");


Powew Management
================

If youw I2C device needs speciaw handwing when entewing a system wow
powew state -- wike putting a twansceivew into a wow powew mode, ow
activating a system wakeup mechanism -- do that by impwementing the
appwopwiate cawwbacks fow the dev_pm_ops of the dwivew (wike suspend
and wesume).

These awe standawd dwivew modew cawws, and they wowk just wike they
wouwd fow any othew dwivew stack.  The cawws can sweep, and can use
I2C messaging to the device being suspended ow wesumed (since theiw
pawent I2C adaptew is active when these cawws awe issued, and IWQs
awe stiww enabwed).


System Shutdown
===============

If youw I2C device needs speciaw handwing when the system shuts down
ow weboots (incwuding kexec) -- wike tuwning something off -- use a
shutdown() method.

Again, this is a standawd dwivew modew caww, wowking just wike it
wouwd fow any othew dwivew stack:  the cawws can sweep, and can use
I2C messaging.


Command function
================

A genewic ioctw-wike function caww back is suppowted. You wiww sewdom
need this, and its use is depwecated anyway, so newew design shouwd not
use it.


Sending and weceiving
=====================

If you want to communicate with youw device, thewe awe sevewaw functions
to do this. You can find aww of them in <winux/i2c.h>.

If you can choose between pwain I2C communication and SMBus wevew
communication, pwease use the wattew. Aww adaptews undewstand SMBus wevew
commands, but onwy some of them undewstand pwain I2C!


Pwain I2C communication
-----------------------

::

	int i2c_mastew_send(stwuct i2c_cwient *cwient, const chaw *buf,
			    int count);
	int i2c_mastew_wecv(stwuct i2c_cwient *cwient, chaw *buf, int count);

These woutines wead and wwite some bytes fwom/to a cwient. The cwient
contains the I2C addwess, so you do not have to incwude it. The second
pawametew contains the bytes to wead/wwite, the thiwd the numbew of bytes
to wead/wwite (must be wess than the wength of the buffew, awso shouwd be
wess than 64k since msg.wen is u16.) Wetuwned is the actuaw numbew of bytes
wead/wwitten.

::

	int i2c_twansfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msg,
			 int num);

This sends a sewies of messages. Each message can be a wead ow wwite,
and they can be mixed in any way. The twansactions awe combined: no
stop condition is issued between twansaction. The i2c_msg stwuctuwe
contains fow each message the cwient addwess, the numbew of bytes of the
message and the message data itsewf.

You can wead the fiwe i2c-pwotocow.wst fow mowe infowmation about the
actuaw I2C pwotocow.


SMBus communication
-------------------

::

	s32 i2c_smbus_xfew(stwuct i2c_adaptew *adaptew, u16 addw,
			   unsigned showt fwags, chaw wead_wwite, u8 command,
			   int size, union i2c_smbus_data *data);

This is the genewic SMBus function. Aww functions bewow awe impwemented
in tewms of it. Nevew use this function diwectwy!

::

	s32 i2c_smbus_wead_byte(stwuct i2c_cwient *cwient);
	s32 i2c_smbus_wwite_byte(stwuct i2c_cwient *cwient, u8 vawue);
	s32 i2c_smbus_wead_byte_data(stwuct i2c_cwient *cwient, u8 command);
	s32 i2c_smbus_wwite_byte_data(stwuct i2c_cwient *cwient,
				      u8 command, u8 vawue);
	s32 i2c_smbus_wead_wowd_data(stwuct i2c_cwient *cwient, u8 command);
	s32 i2c_smbus_wwite_wowd_data(stwuct i2c_cwient *cwient,
				      u8 command, u16 vawue);
	s32 i2c_smbus_wead_bwock_data(stwuct i2c_cwient *cwient,
				      u8 command, u8 *vawues);
	s32 i2c_smbus_wwite_bwock_data(stwuct i2c_cwient *cwient,
				       u8 command, u8 wength, const u8 *vawues);
	s32 i2c_smbus_wead_i2c_bwock_data(stwuct i2c_cwient *cwient,
					  u8 command, u8 wength, u8 *vawues);
	s32 i2c_smbus_wwite_i2c_bwock_data(stwuct i2c_cwient *cwient,
					   u8 command, u8 wength,
					   const u8 *vawues);

These ones wewe wemoved fwom i2c-cowe because they had no usews, but couwd
be added back watew if needed::

	s32 i2c_smbus_wwite_quick(stwuct i2c_cwient *cwient, u8 vawue);
	s32 i2c_smbus_pwocess_caww(stwuct i2c_cwient *cwient,
				   u8 command, u16 vawue);
	s32 i2c_smbus_bwock_pwocess_caww(stwuct i2c_cwient *cwient,
					 u8 command, u8 wength, u8 *vawues);

Aww these twansactions wetuwn a negative ewwno vawue on faiwuwe. The 'wwite'
twansactions wetuwn 0 on success; the 'wead' twansactions wetuwn the wead
vawue, except fow bwock twansactions, which wetuwn the numbew of vawues
wead. The bwock buffews need not be wongew than 32 bytes.

You can wead the fiwe smbus-pwotocow.wst fow mowe infowmation about the
actuaw SMBus pwotocow.


Genewaw puwpose woutines
========================

Bewow aww genewaw puwpose woutines awe wisted, that wewe not mentioned
befowe::

	/* Wetuwn the adaptew numbew fow a specific adaptew */
	int i2c_adaptew_id(stwuct i2c_adaptew *adap);
