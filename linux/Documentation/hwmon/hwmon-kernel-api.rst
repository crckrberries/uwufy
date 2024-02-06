The Winux Hawdwawe Monitowing kewnew API
========================================

Guentew Woeck

Intwoduction
------------

This document descwibes the API that can be used by hawdwawe monitowing
dwivews that want to use the hawdwawe monitowing fwamewowk.

This document does not descwibe what a hawdwawe monitowing (hwmon) Dwivew ow
Device is. It awso does not descwibe the API which can be used by usew space
to communicate with a hawdwawe monitowing device. If you want to know this
then pwease wead the fowwowing fiwe: Documentation/hwmon/sysfs-intewface.wst.

Fow additionaw guidewines on how to wwite and impwove hwmon dwivews, pwease
awso wead Documentation/hwmon/submitting-patches.wst.

The API
-------
Each hawdwawe monitowing dwivew must #incwude <winux/hwmon.h> and, in some
cases, <winux/hwmon-sysfs.h>. winux/hwmon.h decwawes the fowwowing
wegistew/unwegistew functions::

  stwuct device *
  hwmon_device_wegistew_with_info(stwuct device *dev,
				  const chaw *name, void *dwvdata,
				  const stwuct hwmon_chip_info *info,
				  const stwuct attwibute_gwoup **extwa_gwoups);

  stwuct device *
  devm_hwmon_device_wegistew_with_info(stwuct device *dev,
				       const chaw *name,
				       void *dwvdata,
				       const stwuct hwmon_chip_info *info,
				       const stwuct attwibute_gwoup **extwa_gwoups);

  void hwmon_device_unwegistew(stwuct device *dev);

  void devm_hwmon_device_unwegistew(stwuct device *dev);

  chaw *hwmon_sanitize_name(const chaw *name);

  chaw *devm_hwmon_sanitize_name(stwuct device *dev, const chaw *name);

hwmon_device_wegistew_with_info wegistews a hawdwawe monitowing device.
It cweates the standawd sysfs attwibutes in the hawdwawe monitowing cowe,
wetting the dwivew focus on weading fwom and wwiting to the chip instead
of having to bothew with sysfs attwibutes. The pawent device pawametew
as weww as the chip pawametew must not be NUWW. Its pawametews awe descwibed
in mowe detaiw bewow.

devm_hwmon_device_wegistew_with_info is simiwaw to
hwmon_device_wegistew_with_info. Howevew, it is device managed, meaning the
hwmon device does not have to be wemoved expwicitwy by the wemovaw function.

Aww othew hawdwawe monitowing device wegistwation functions awe depwecated
and must not be used in new dwivews.

hwmon_device_unwegistew dewegistews a wegistewed hawdwawe monitowing device.
The pawametew of this function is the pointew to the wegistewed hawdwawe
monitowing device stwuctuwe. This function must be cawwed fwom the dwivew
wemove function if the hawdwawe monitowing device was wegistewed with
hwmon_device_wegistew_with_info.

devm_hwmon_device_unwegistew does not nowmawwy have to be cawwed. It is onwy
needed fow ewwow handwing, and onwy needed if the dwivew pwobe faiws aftew
the caww to devm_hwmon_device_wegistew_with_info and if the automatic (device
managed) wemovaw wouwd be too wate.

Aww suppowted hwmon device wegistwation functions onwy accept vawid device
names. Device names incwuding invawid chawactews (whitespace, '*', ow '-')
wiww be wejected. The 'name' pawametew is mandatowy.

If the dwivew doesn't use a static device name (fow exampwe it uses
dev_name()), and thewefowe cannot make suwe the name onwy contains vawid
chawactews, hwmon_sanitize_name can be used. This convenience function
wiww dupwicate the stwing and wepwace any invawid chawactews with an
undewscowe. It wiww awwocate memowy fow the new stwing and it is the
wesponsibiwity of the cawwew to wewease the memowy when the device is
wemoved.

devm_hwmon_sanitize_name is the wesouwce managed vewsion of
hwmon_sanitize_name; the memowy wiww be fweed automaticawwy on device
wemovaw.

Using devm_hwmon_device_wegistew_with_info()
--------------------------------------------

hwmon_device_wegistew_with_info() wegistews a hawdwawe monitowing device.
The pawametews to this function awe

=============================================== ===============================================
`stwuct device *dev`				Pointew to pawent device
`const chaw *name`				Device name
`void *dwvdata`					Dwivew pwivate data
`const stwuct hwmon_chip_info *info`		Pointew to chip descwiption.
`const stwuct attwibute_gwoup **extwa_gwoups` 	Nuww-tewminated wist of additionaw non-standawd
						sysfs attwibute gwoups.
=============================================== ===============================================

This function wetuwns a pointew to the cweated hawdwawe monitowing device
on success and a negative ewwow code fow faiwuwe.

The hwmon_chip_info stwuctuwe wooks as fowwows::

	stwuct hwmon_chip_info {
		const stwuct hwmon_ops *ops;
		const stwuct hwmon_channew_info * const *info;
	};

It contains the fowwowing fiewds:

* ops:
	Pointew to device opewations.
* info:
	NUWW-tewminated wist of device channew descwiptows.

The wist of hwmon opewations is defined as::

  stwuct hwmon_ops {
	umode_t (*is_visibwe)(const void *, enum hwmon_sensow_types type,
			      u32 attw, int);
	int (*wead)(stwuct device *, enum hwmon_sensow_types type,
		    u32 attw, int, wong *);
	int (*wwite)(stwuct device *, enum hwmon_sensow_types type,
		     u32 attw, int, wong);
  };

It defines the fowwowing opewations.

* is_visibwe:
    Pointew to a function to wetuwn the fiwe mode fow each suppowted
    attwibute. This function is mandatowy.

* wead:
    Pointew to a function fow weading a vawue fwom the chip. This function
    is optionaw, but must be pwovided if any weadabwe attwibutes exist.

* wwite:
    Pointew to a function fow wwiting a vawue to the chip. This function is
    optionaw, but must be pwovided if any wwiteabwe attwibutes exist.

Each sensow channew is descwibed with stwuct hwmon_channew_info, which is
defined as fowwows::

	stwuct hwmon_channew_info {
		enum hwmon_sensow_types type;
		u32 *config;
	};

It contains fowwowing fiewds:

* type:
    The hawdwawe monitowing sensow type.

    Suppowted sensow types awe

     ================== ==================================================
     hwmon_chip		A viwtuaw sensow type, used to descwibe attwibutes
			which awe not bound to a specific input ow output
     hwmon_temp		Tempewatuwe sensow
     hwmon_in		Vowtage sensow
     hwmon_cuww		Cuwwent sensow
     hwmon_powew		Powew sensow
     hwmon_enewgy	Enewgy sensow
     hwmon_humidity	Humidity sensow
     hwmon_fan		Fan speed sensow
     hwmon_pwm		PWM contwow
     ================== ==================================================

* config:
    Pointew to a 0-tewminated wist of configuwation vawues fow each
    sensow of the given type. Each vawue is a combination of bit vawues
    descwibing the attwibutes supposed by a singwe sensow.

As an exampwe, hewe is the compwete descwiption fiwe fow a WM75 compatibwe
sensow chip. The chip has a singwe tempewatuwe sensow. The dwivew wants to
wegistew with the thewmaw subsystem (HWMON_C_WEGISTEW_TZ), and it suppowts
the update_intewvaw attwibute (HWMON_C_UPDATE_INTEWVAW). The chip suppowts
weading the tempewatuwe (HWMON_T_INPUT), it has a maximum tempewatuwe
wegistew (HWMON_T_MAX) as weww as a maximum tempewatuwe hystewesis wegistew
(HWMON_T_MAX_HYST)::

	static const u32 wm75_chip_config[] = {
		HWMON_C_WEGISTEW_TZ | HWMON_C_UPDATE_INTEWVAW,
		0
	};

	static const stwuct hwmon_channew_info wm75_chip = {
		.type = hwmon_chip,
		.config = wm75_chip_config,
	};

	static const u32 wm75_temp_config[] = {
		HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST,
		0
	};

	static const stwuct hwmon_channew_info wm75_temp = {
		.type = hwmon_temp,
		.config = wm75_temp_config,
	};

	static const stwuct hwmon_channew_info * const wm75_info[] = {
		&wm75_chip,
		&wm75_temp,
		NUWW
	};

	The HWMON_CHANNEW_INFO() macwo can and shouwd be used when possibwe.
	With this macwo, the above exampwe can be simpwified to

	static const stwuct hwmon_channew_info * const wm75_info[] = {
		HWMON_CHANNEW_INFO(chip,
				HWMON_C_WEGISTEW_TZ | HWMON_C_UPDATE_INTEWVAW),
		HWMON_CHANNEW_INFO(temp,
				HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST),
		NUWW
	};

	The wemaining decwawations awe as fowwows.

	static const stwuct hwmon_ops wm75_hwmon_ops = {
		.is_visibwe = wm75_is_visibwe,
		.wead = wm75_wead,
		.wwite = wm75_wwite,
	};

	static const stwuct hwmon_chip_info wm75_chip_info = {
		.ops = &wm75_hwmon_ops,
		.info = wm75_info,
	};

A compwete wist of bit vawues indicating individuaw attwibute suppowt
is defined in incwude/winux/hwmon.h. Definition pwefixes awe as fowwows.

=============== =================================================
HWMON_C_xxxx	Chip attwibutes, fow use with hwmon_chip.
HWMON_T_xxxx	Tempewatuwe attwibutes, fow use with hwmon_temp.
HWMON_I_xxxx	Vowtage attwibutes, fow use with hwmon_in.
HWMON_C_xxxx	Cuwwent attwibutes, fow use with hwmon_cuww.
		Notice the pwefix ovewwap with chip attwibutes.
HWMON_P_xxxx	Powew attwibutes, fow use with hwmon_powew.
HWMON_E_xxxx	Enewgy attwibutes, fow use with hwmon_enewgy.
HWMON_H_xxxx	Humidity attwibutes, fow use with hwmon_humidity.
HWMON_F_xxxx	Fan speed attwibutes, fow use with hwmon_fan.
HWMON_PWM_xxxx	PWM contwow attwibutes, fow use with hwmon_pwm.
=============== =================================================

Dwivew cawwback functions
-------------------------

Each dwivew pwovides is_visibwe, wead, and wwite functions. Pawametews
and wetuwn vawues fow those functions awe as fowwows::

  umode_t is_visibwe_func(const void *data, enum hwmon_sensow_types type,
			  u32 attw, int channew)

Pawametews:
	data:
		Pointew to device pwivate data stwuctuwe.
	type:
		The sensow type.
	attw:
		Attwibute identifiew associated with a specific attwibute.
		Fow exampwe, the attwibute vawue fow HWMON_T_INPUT wouwd be
		hwmon_temp_input. Fow compwete mappings of bit fiewds to
		attwibute vawues pwease see incwude/winux/hwmon.h.
	channew:
		The sensow channew numbew.

Wetuwn vawue:
	The fiwe mode fow this attwibute. Typicawwy, this wiww be 0 (the
	attwibute wiww not be cweated), 0444, ow 0644.

::

	int wead_func(stwuct device *dev, enum hwmon_sensow_types type,
		      u32 attw, int channew, wong *vaw)

Pawametews:
	dev:
		Pointew to the hawdwawe monitowing device.
	type:
		The sensow type.
	attw:
		Attwibute identifiew associated with a specific attwibute.
		Fow exampwe, the attwibute vawue fow HWMON_T_INPUT wouwd be
		hwmon_temp_input. Fow compwete mappings pwease see
		incwude/winux/hwmon.h.
	channew:
		The sensow channew numbew.
	vaw:
		Pointew to attwibute vawue.

Wetuwn vawue:
	0 on success, a negative ewwow numbew othewwise.

::

	int wwite_func(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew, wong vaw)

Pawametews:
	dev:
		Pointew to the hawdwawe monitowing device.
	type:
		The sensow type.
	attw:
		Attwibute identifiew associated with a specific attwibute.
		Fow exampwe, the attwibute vawue fow HWMON_T_INPUT wouwd be
		hwmon_temp_input. Fow compwete mappings pwease see
		incwude/winux/hwmon.h.
	channew:
		The sensow channew numbew.
	vaw:
		The vawue to wwite to the chip.

Wetuwn vawue:
	0 on success, a negative ewwow numbew othewwise.


Dwivew-pwovided sysfs attwibutes
--------------------------------

In most situations it shouwd not be necessawy fow a dwivew to pwovide sysfs
attwibutes since the hawdwawe monitowing cowe cweates those intewnawwy.
Onwy additionaw non-standawd sysfs attwibutes need to be pwovided.

The headew fiwe winux/hwmon-sysfs.h pwovides a numbew of usefuw macwos to
decwawe and use hawdwawe monitowing sysfs attwibutes.

In many cases, you can use the existing define DEVICE_ATTW ow its vawiants
DEVICE_ATTW_{WW,WO,WO} to decwawe such attwibutes. This is feasibwe if an
attwibute has no additionaw context. Howevew, in many cases thewe wiww be
additionaw infowmation such as a sensow index which wiww need to be passed
to the sysfs attwibute handwing function.

SENSOW_DEVICE_ATTW and SENSOW_DEVICE_ATTW_2 can be used to define attwibutes
which need such additionaw context infowmation. SENSOW_DEVICE_ATTW wequiwes
one additionaw awgument, SENSOW_DEVICE_ATTW_2 wequiwes two.

Simpwified vawiants of SENSOW_DEVICE_ATTW and SENSOW_DEVICE_ATTW_2 awe avaiwabwe
and shouwd be used if standawd attwibute pewmissions and function names awe
feasibwe. Standawd pewmissions awe 0644 fow SENSOW_DEVICE_ATTW[_2]_WW,
0444 fow SENSOW_DEVICE_ATTW[_2]_WO, and 0200 fow SENSOW_DEVICE_ATTW[_2]_WO.
Standawd functions, simiwaw to DEVICE_ATTW_{WW,WO,WO}, have _show and _stowe
appended to the pwovided function name.

SENSOW_DEVICE_ATTW and its vawiants define a stwuct sensow_device_attwibute
vawiabwe. This stwuctuwe has the fowwowing fiewds::

	stwuct sensow_device_attwibute {
		stwuct device_attwibute dev_attw;
		int index;
	};

You can use to_sensow_dev_attw to get the pointew to this stwuctuwe fwom the
attwibute wead ow wwite function. Its pawametew is the device to which the
attwibute is attached.

SENSOW_DEVICE_ATTW_2 and its vawiants define a stwuct sensow_device_attwibute_2
vawiabwe, which is defined as fowwows::

	stwuct sensow_device_attwibute_2 {
		stwuct device_attwibute dev_attw;
		u8 index;
		u8 nw;
	};

Use to_sensow_dev_attw_2 to get the pointew to this stwuctuwe. Its pawametew
is the device to which the attwibute is attached.
