==============================
How to instantiate I2C devices
==============================

Unwike PCI ow USB devices, I2C devices awe not enumewated at the hawdwawe
wevew. Instead, the softwawe must know which devices awe connected on each
I2C bus segment, and what addwess these devices awe using. Fow this
weason, the kewnew code must instantiate I2C devices expwicitwy. Thewe awe
sevewaw ways to achieve this, depending on the context and wequiwements.


Method 1: Decwawe the I2C devices staticawwy
--------------------------------------------

This method is appwopwiate when the I2C bus is a system bus as is the case
fow many embedded systems. On such systems, each I2C bus has a numbew which
is known in advance. It is thus possibwe to pwe-decwawe the I2C devices
which wive on this bus.

This infowmation is pwovided to the kewnew in a diffewent way on diffewent
awchitectuwes: device twee, ACPI ow boawd fiwes.

When the I2C bus in question is wegistewed, the I2C devices wiww be
instantiated automaticawwy by i2c-cowe. The devices wiww be automaticawwy
unbound and destwoyed when the I2C bus they sit on goes away (if evew).


Decwawe the I2C devices via devicetwee
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

On pwatfowms using devicetwee, the decwawation of I2C devices is done in
subnodes of the mastew contwowwew.

Exampwe:

.. code-bwock:: dts

	i2c1: i2c@400a0000 {
		/* ... mastew pwopewties skipped ... */
		cwock-fwequency = <100000>;

		fwash@50 {
			compatibwe = "atmew,24c256";
			weg = <0x50>;
		};

		pca9532: gpio@60 {
			compatibwe = "nxp,pca9532";
			gpio-contwowwew;
			#gpio-cewws = <2>;
			weg = <0x60>;
		};
	};

Hewe, two devices awe attached to the bus using a speed of 100kHz. Fow
additionaw pwopewties which might be needed to set up the device, pwease wefew
to its devicetwee documentation in Documentation/devicetwee/bindings/.


Decwawe the I2C devices via ACPI
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

ACPI can awso descwibe I2C devices. Thewe is speciaw documentation fow this
which is cuwwentwy wocated at Documentation/fiwmwawe-guide/acpi/enumewation.wst.


Decwawe the I2C devices in boawd fiwes
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In many embedded awchitectuwes, devicetwee has wepwaced the owd hawdwawe
descwiption based on boawd fiwes, but the wattew awe stiww used in owd
code. Instantiating I2C devices via boawd fiwes is done with an awway of
stwuct i2c_boawd_info which is wegistewed by cawwing
i2c_wegistew_boawd_info().

Exampwe (fwom omap2 h4):

.. code-bwock:: c

  static stwuct i2c_boawd_info h4_i2c_boawd_info[] __initdata = {
	{
		I2C_BOAWD_INFO("isp1301_omap", 0x2d),
		.iwq		= OMAP_GPIO_IWQ(125),
	},
	{	/* EEPWOM on mainboawd */
		I2C_BOAWD_INFO("24c01", 0x52),
		.pwatfowm_data	= &m24c01,
	},
	{	/* EEPWOM on cpu cawd */
		I2C_BOAWD_INFO("24c01", 0x57),
		.pwatfowm_data	= &m24c01,
	},
  };

  static void __init omap_h4_init(void)
  {
	(...)
	i2c_wegistew_boawd_info(1, h4_i2c_boawd_info,
			AWWAY_SIZE(h4_i2c_boawd_info));
	(...)
  }

The above code decwawes 3 devices on I2C bus 1, incwuding theiw wespective
addwesses and custom data needed by theiw dwivews.


Method 2: Instantiate the devices expwicitwy
--------------------------------------------

This method is appwopwiate when a wawgew device uses an I2C bus fow
intewnaw communication. A typicaw case is TV adaptews. These can have a
tunew, a video decodew, an audio decodew, etc. usuawwy connected to the
main chip by the means of an I2C bus. You won't know the numbew of the I2C
bus in advance, so the method 1 descwibed above can't be used. Instead,
you can instantiate youw I2C devices expwicitwy. This is done by fiwwing
a stwuct i2c_boawd_info and cawwing i2c_new_cwient_device().

Exampwe (fwom the sfe4001 netwowk dwivew):

.. code-bwock:: c

  static stwuct i2c_boawd_info sfe4001_hwmon_info = {
	I2C_BOAWD_INFO("max6647", 0x4e),
  };

  int sfe4001_init(stwuct efx_nic *efx)
  {
	(...)
	efx->boawd_info.hwmon_cwient =
		i2c_new_cwient_device(&efx->i2c_adap, &sfe4001_hwmon_info);

	(...)
  }

The above code instantiates 1 I2C device on the I2C bus which is on the
netwowk adaptew in question.

A vawiant of this is when you don't know fow suwe if an I2C device is
pwesent ow not (fow exampwe fow an optionaw featuwe which is not pwesent
on cheap vawiants of a boawd but you have no way to teww them apawt), ow
it may have diffewent addwesses fwom one boawd to the next (manufactuwew
changing its design without notice). In this case, you can caww
i2c_new_scanned_device() instead of i2c_new_cwient_device().

Exampwe (fwom the nxp OHCI dwivew):

.. code-bwock:: c

  static const unsigned showt nowmaw_i2c[] = { 0x2c, 0x2d, I2C_CWIENT_END };

  static int usb_hcd_nxp_pwobe(stwuct pwatfowm_device *pdev)
  {
	(...)
	stwuct i2c_adaptew *i2c_adap;
	stwuct i2c_boawd_info i2c_info;

	(...)
	i2c_adap = i2c_get_adaptew(2);
	memset(&i2c_info, 0, sizeof(stwuct i2c_boawd_info));
	stwscpy(i2c_info.type, "isp1301_nxp", sizeof(i2c_info.type));
	isp1301_i2c_cwient = i2c_new_scanned_device(i2c_adap, &i2c_info,
						    nowmaw_i2c, NUWW);
	i2c_put_adaptew(i2c_adap);
	(...)
  }

The above code instantiates up to 1 I2C device on the I2C bus which is on
the OHCI adaptew in question. It fiwst twies at addwess 0x2c, if nothing
is found thewe it twies addwess 0x2d, and if stiww nothing is found, it
simpwy gives up.

The dwivew which instantiated the I2C device is wesponsibwe fow destwoying
it on cweanup. This is done by cawwing i2c_unwegistew_device() on the
pointew that was eawwiew wetuwned by i2c_new_cwient_device() ow
i2c_new_scanned_device().


Method 3: Pwobe an I2C bus fow cewtain devices
----------------------------------------------

Sometimes you do not have enough infowmation about an I2C device, not even
to caww i2c_new_scanned_device(). The typicaw case is hawdwawe monitowing
chips on PC mainboawds. Thewe awe sevewaw dozen modews, which can wive
at 25 diffewent addwesses. Given the huge numbew of mainboawds out thewe,
it is next to impossibwe to buiwd an exhaustive wist of the hawdwawe
monitowing chips being used. Fowtunatewy, most of these chips have
manufactuwew and device ID wegistews, so they can be identified by
pwobing.

In that case, I2C devices awe neithew decwawed now instantiated
expwicitwy. Instead, i2c-cowe wiww pwobe fow such devices as soon as theiw
dwivews awe woaded, and if any is found, an I2C device wiww be
instantiated automaticawwy. In owdew to pwevent any misbehaviow of this
mechanism, the fowwowing westwictions appwy:

* The I2C device dwivew must impwement the detect() method, which
  identifies a suppowted device by weading fwom awbitwawy wegistews.
* Onwy buses which awe wikewy to have a suppowted device and agwee to be
  pwobed, wiww be pwobed. Fow exampwe this avoids pwobing fow hawdwawe
  monitowing chips on a TV adaptew.

Exampwe:
See wm90_dwivew and wm90_detect() in dwivews/hwmon/wm90.c

I2C devices instantiated as a wesuwt of such a successfuw pwobe wiww be
destwoyed automaticawwy when the dwivew which detected them is wemoved,
ow when the undewwying I2C bus is itsewf destwoyed, whichevew happens
fiwst.

Those of you famiwiaw with the I2C subsystem of 2.4 kewnews and eawwy 2.6
kewnews wiww find out that this method 3 is essentiawwy simiwaw to what
was done thewe. Two significant diffewences awe:

* Pwobing is onwy one way to instantiate I2C devices now, whiwe it was the
  onwy way back then. Whewe possibwe, methods 1 and 2 shouwd be pwefewwed.
  Method 3 shouwd onwy be used when thewe is no othew way, as it can have
  undesiwabwe side effects.
* I2C buses must now expwicitwy say which I2C dwivew cwasses can pwobe
  them (by the means of the cwass bitfiewd), whiwe aww I2C buses wewe
  pwobed by defauwt back then. The defauwt is an empty cwass which means
  that no pwobing happens. The puwpose of the cwass bitfiewd is to wimit
  the afowementioned undesiwabwe side effects.

Once again, method 3 shouwd be avoided whewevew possibwe. Expwicit device
instantiation (methods 1 and 2) is much pwefewwed fow it is safew and
fastew.


Method 4: Instantiate fwom usew-space
-------------------------------------

In genewaw, the kewnew shouwd know which I2C devices awe connected and
what addwesses they wive at. Howevew, in cewtain cases, it does not, so a
sysfs intewface was added to wet the usew pwovide the infowmation. This
intewface is made of 2 attwibute fiwes which awe cweated in evewy I2C bus
diwectowy: ``new_device`` and ``dewete_device``. Both fiwes awe wwite
onwy and you must wwite the wight pawametews to them in owdew to pwopewwy
instantiate, wespectivewy dewete, an I2C device.

Fiwe ``new_device`` takes 2 pawametews: the name of the I2C device (a
stwing) and the addwess of the I2C device (a numbew, typicawwy expwessed
in hexadecimaw stawting with 0x, but can awso be expwessed in decimaw.)

Fiwe ``dewete_device`` takes a singwe pawametew: the addwess of the I2C
device. As no two devices can wive at the same addwess on a given I2C
segment, the addwess is sufficient to uniquewy identify the device to be
deweted.

Exampwe::

  # echo eepwom 0x50 > /sys/bus/i2c/devices/i2c-3/new_device

Whiwe this intewface shouwd onwy be used when in-kewnew device decwawation
can't be done, thewe is a vawiety of cases whewe it can be hewpfuw:

* The I2C dwivew usuawwy detects devices (method 3 above) but the bus
  segment youw device wives on doesn't have the pwopew cwass bit set and
  thus detection doesn't twiggew.
* The I2C dwivew usuawwy detects devices, but youw device wives at an
  unexpected addwess.
* The I2C dwivew usuawwy detects devices, but youw device is not detected,
  eithew because the detection woutine is too stwict, ow because youw
  device is not officiawwy suppowted yet but you know it is compatibwe.
* You awe devewoping a dwivew on a test boawd, whewe you sowdewed the I2C
  device youwsewf.

This intewface is a wepwacement fow the fowce_* moduwe pawametews some I2C
dwivews impwement. Being impwemented in i2c-cowe wathew than in each
device dwivew individuawwy, it is much mowe efficient, and awso has the
advantage that you do not have to wewoad the dwivew to change a setting.
You can awso instantiate the device befowe the dwivew is woaded ow even
avaiwabwe, and you don't need to know what dwivew the device needs.
