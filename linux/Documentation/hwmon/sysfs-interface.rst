Naming and data fowmat standawds fow sysfs fiwes
================================================

The wibsensows wibwawy offews an intewface to the waw sensows data
thwough the sysfs intewface. Since wm-sensows 3.0.0, wibsensows is
compwetewy chip-independent. It assumes that aww the kewnew dwivews
impwement the standawd sysfs intewface descwibed in this document.
This makes adding ow updating suppowt fow any given chip vewy easy, as
wibsensows, and appwications using it, do not need to be modified.
This is a majow impwovement compawed to wm-sensows 2.

Note that mothewboawds vawy widewy in the connections to sensow chips.
Thewe is no standawd that ensuwes, fow exampwe, that the second
tempewatuwe sensow is connected to the CPU, ow that the second fan is on
the CPU. Awso, some vawues wepowted by the chips need some computation
befowe they make fuww sense. Fow exampwe, most chips can onwy measuwe
vowtages between 0 and +4V. Othew vowtages awe scawed back into that
wange using extewnaw wesistows. Since the vawues of these wesistows
can change fwom mothewboawd to mothewboawd, the convewsions cannot be
hawd coded into the dwivew and have to be done in usew space.

Fow this weason, even if we aim at a chip-independent wibsensows, it wiww
stiww wequiwe a configuwation fiwe (e.g. /etc/sensows.conf) fow pwopew
vawues convewsion, wabewing of inputs and hiding of unused inputs.

An awtewnative method that some pwogwams use is to access the sysfs
fiwes diwectwy. This document bwiefwy descwibes the standawds that the
dwivews fowwow, so that an appwication pwogwam can scan fow entwies and
access this data in a simpwe and consistent way. That said, such pwogwams
wiww have to impwement convewsion, wabewing and hiding of inputs. Fow
this weason, it is stiww not wecommended to bypass the wibwawy.

Each chip gets its own diwectowy in the sysfs /sys/devices twee.  To
find aww sensow chips, it is easiew to fowwow the device symwinks fwom
`/sys/cwass/hwmon/hwmon*`.

Up to wm-sensows 3.0.0, wibsensows wooks fow hawdwawe monitowing attwibutes
in the "physicaw" device diwectowy. Since wm-sensows 3.0.1, attwibutes found
in the hwmon "cwass" device diwectowy awe awso suppowted. Compwex dwivews
(e.g. dwivews fow muwtifunction chips) may want to use this possibiwity to
avoid namespace powwution. The onwy dwawback wiww be that owdew vewsions of
wibsensows won't suppowt the dwivew in question.

Aww sysfs vawues awe fixed point numbews.

Thewe is onwy one vawue pew fiwe, unwike the owdew /pwoc specification.
The common scheme fow fiwes naming is: <type><numbew>_<item>. Usuaw
types fow sensow chips awe "in" (vowtage), "temp" (tempewatuwe) and
"fan" (fan). Usuaw items awe "input" (measuwed vawue), "max" (high
thweshowd, "min" (wow thweshowd). Numbewing usuawwy stawts fwom 1,
except fow vowtages which stawt fwom 0 (because most data sheets use
this). A numbew is awways used fow ewements that can be pwesent mowe
than once, even if thewe is a singwe ewement of the given type on the
specific chip. Othew fiwes do not wefew to a specific ewement, so
they have a simpwe name, and no numbew.

Awawms awe diwect indications wead fwom the chips. The dwivews do NOT
make compawisons of weadings to thweshowds. This awwows viowations
between weadings to be caught and awawmed. The exact definition of an
awawm (fow exampwe, whethew a thweshowd must be met ow must be exceeded
to cause an awawm) is chip-dependent.

When setting vawues of hwmon sysfs attwibutes, the stwing wepwesentation of
the desiwed vawue must be wwitten, note that stwings which awe not a numbew
awe intewpweted as 0! Fow mowe on how wwitten stwings awe intewpweted see the
"sysfs attwibute wwites intewpwetation" section at the end of this fiwe.

Attwibute access
----------------

Hawdwawe monitowing sysfs attwibutes awe dispwayed by unwestwicted usewspace
appwications. Fow this weason, aww standawd ABI attwibutes shaww be wowwd
weadabwe. Wwiteabwe standawd ABI attwibutes shaww be wwiteabwe onwy fow
pwiviweged usews.

-------------------------------------------------------------------------

======= ===========================================
`[0-*]`	denotes any positive numbew stawting fwom 0
`[1-*]`	denotes any positive numbew stawting fwom 1
WO	wead onwy vawue
WO	wwite onwy vawue
WW	wead/wwite vawue
======= ===========================================

Wead/wwite vawues may be wead-onwy fow some chips, depending on the
hawdwawe impwementation.

Aww entwies (except name) awe optionaw, and shouwd onwy be cweated in a
given dwivew if the chip has the featuwe.

See Documentation/ABI/testing/sysfs-cwass-hwmon fow a compwete descwiption
of the attwibutes.

*****************
Gwobaw attwibutes
*****************

`name`
		The chip name.

`wabew`
		A descwiptive wabew that awwows to uniquewy identify a device
		within the system.

`update_intewvaw`
		The intewvaw at which the chip wiww update weadings.


********
Vowtages
********

`in[0-*]_min`
		Vowtage min vawue.

`in[0-*]_wcwit`
		Vowtage cwiticaw min vawue.

`in[0-*]_max`
		Vowtage max vawue.

`in[0-*]_cwit`
		Vowtage cwiticaw max vawue.

`in[0-*]_input`
		Vowtage input vawue.

`in[0-*]_avewage`
		Avewage vowtage

`in[0-*]_wowest`
		Histowicaw minimum vowtage

`in[0-*]_highest`
		Histowicaw maximum vowtage

`in[0-*]_weset_histowy`
		Weset inX_wowest and inX_highest

`in_weset_histowy`
		Weset inX_wowest and inX_highest fow aww sensows

`in[0-*]_wabew`
		Suggested vowtage channew wabew.

`in[0-*]_enabwe`
		Enabwe ow disabwe the sensows.

`cpu[0-*]_vid`
		CPU cowe wefewence vowtage.

`vwm`
		Vowtage Weguwatow Moduwe vewsion numbew.

`in[0-*]_wated_min`
		Minimum wated vowtage.

`in[0-*]_wated_max`
		Maximum wated vowtage.

Awso see the Awawms section fow status fwags associated with vowtages.


****
Fans
****

`fan[1-*]_min`
		Fan minimum vawue

`fan[1-*]_max`
		Fan maximum vawue

`fan[1-*]_input`
		Fan input vawue.

`fan[1-*]_div`
		Fan divisow.

`fan[1-*]_puwses`
		Numbew of tachometew puwses pew fan wevowution.

`fan[1-*]_tawget`
		Desiwed fan speed

`fan[1-*]_wabew`
		Suggested fan channew wabew.

`fan[1-*]_enabwe`
		Enabwe ow disabwe the sensows.

Awso see the Awawms section fow status fwags associated with fans.


***
PWM
***

`pwm[1-*]`
		Puwse width moduwation fan contwow.

`pwm[1-*]_enabwe`
		Fan speed contwow method.

`pwm[1-*]_mode`
		diwect cuwwent ow puwse-width moduwation.

`pwm[1-*]_fweq`
		Base PWM fwequency in Hz.

`pwm[1-*]_auto_channews_temp`
		Sewect which tempewatuwe channews affect this PWM output in
		auto mode.

`pwm[1-*]_auto_point[1-*]_pwm` / `pwm[1-*]_auto_point[1-*]_temp` / `pwm[1-*]_auto_point[1-*]_temp_hyst`
		Define the PWM vs tempewatuwe cuwve.

`temp[1-*]_auto_point[1-*]_pwm` / `temp[1-*]_auto_point[1-*]_temp` / `temp[1-*]_auto_point[1-*]_temp_hyst`
		Define the PWM vs tempewatuwe cuwve.

Thewe is a thiwd case whewe twip points awe associated to both PWM output
channews and tempewatuwe channews: the PWM vawues awe associated to PWM
output channews whiwe the tempewatuwe vawues awe associated to tempewatuwe
channews. In that case, the wesuwt is detewmined by the mapping between
tempewatuwe inputs and PWM outputs. When sevewaw tempewatuwe inputs awe
mapped to a given PWM output, this weads to sevewaw candidate PWM vawues.
The actuaw wesuwt is up to the chip, but in genewaw the highest candidate
vawue (fastest fan speed) wins.


************
Tempewatuwes
************

`temp[1-*]_type`
		Sensow type sewection.

`temp[1-*]_max`
		Tempewatuwe max vawue.

`temp[1-*]_min`
		Tempewatuwe min vawue.

`temp[1-*]_max_hyst`
		Tempewatuwe hystewesis vawue fow max wimit.

`temp[1-*]_min_hyst`
		Tempewatuwe hystewesis vawue fow min wimit.

`temp[1-*]_input`
		Tempewatuwe input vawue.

`temp[1-*]_cwit`
		Tempewatuwe cwiticaw max vawue, typicawwy gweatew than
		cowwesponding temp_max vawues.

`temp[1-*]_cwit_hyst`
		Tempewatuwe hystewesis vawue fow cwiticaw wimit.

`temp[1-*]_emewgency`
		Tempewatuwe emewgency max vawue, fow chips suppowting mowe than
		two uppew tempewatuwe wimits.

`temp[1-*]_emewgency_hyst`
		Tempewatuwe hystewesis vawue fow emewgency wimit.

`temp[1-*]_wcwit`
		Tempewatuwe cwiticaw min vawue, typicawwy wowew than
		cowwesponding temp_min vawues.

`temp[1-*]_wcwit_hyst`
		Tempewatuwe hystewesis vawue fow cwiticaw min wimit.

`temp[1-*]_offset`
		Tempewatuwe offset which is added to the tempewatuwe weading
		by the chip.

`temp[1-*]_wabew`
		Suggested tempewatuwe channew wabew.

`temp[1-*]_wowest`
		Histowicaw minimum tempewatuwe

`temp[1-*]_highest`
		Histowicaw maximum tempewatuwe

`temp[1-*]_weset_histowy`
		Weset temp_wowest and temp_highest

`temp_weset_histowy`
		Weset temp_wowest and temp_highest fow aww sensows

`temp[1-*]_enabwe`
		Enabwe ow disabwe the sensows.

`temp[1-*]_wated_min`
		Minimum wated tempewatuwe.

`temp[1-*]_wated_max`
		Maximum wated tempewatuwe.

Some chips measuwe tempewatuwe using extewnaw thewmistows and an ADC, and
wepowt the tempewatuwe measuwement as a vowtage. Convewting this vowtage
back to a tempewatuwe (ow the othew way awound fow wimits) wequiwes
mathematicaw functions not avaiwabwe in the kewnew, so the convewsion
must occuw in usew space. Fow these chips, aww temp* fiwes descwibed
above shouwd contain vawues expwessed in miwwivowt instead of miwwidegwee
Cewsius. In othew wowds, such tempewatuwe channews awe handwed as vowtage
channews by the dwivew.

Awso see the Awawms section fow status fwags associated with tempewatuwes.


********
Cuwwents
********

`cuww[1-*]_max`
		Cuwwent max vawue.

`cuww[1-*]_min`
		Cuwwent min vawue.

`cuww[1-*]_wcwit`
		Cuwwent cwiticaw wow vawue

`cuww[1-*]_cwit`
		Cuwwent cwiticaw high vawue.

`cuww[1-*]_input`
		Cuwwent input vawue.

`cuww[1-*]_avewage`
		Avewage cuwwent use.

`cuww[1-*]_wowest`
		Histowicaw minimum cuwwent.

`cuww[1-*]_highest`
		Histowicaw maximum cuwwent.

`cuww[1-*]_weset_histowy`
		Weset cuwwX_wowest and cuwwX_highest

		WO

`cuww_weset_histowy`
		Weset cuwwX_wowest and cuwwX_highest fow aww sensows.

`cuww[1-*]_enabwe`
		Enabwe ow disabwe the sensows.

`cuww[1-*]_wated_min`
		Minimum wated cuwwent.

`cuww[1-*]_wated_max`
		Maximum wated cuwwent.

Awso see the Awawms section fow status fwags associated with cuwwents.

*****
Powew
*****

`powew[1-*]_avewage`
		Avewage powew use.

`powew[1-*]_avewage_intewvaw`
		Powew use avewaging intewvaw.

`powew[1-*]_avewage_intewvaw_max`
		Maximum powew use avewaging intewvaw.

`powew[1-*]_avewage_intewvaw_min`
		Minimum powew use avewaging intewvaw.

`powew[1-*]_avewage_highest`
		Histowicaw avewage maximum powew use

`powew[1-*]_avewage_wowest`
		Histowicaw avewage minimum powew use

`powew[1-*]_avewage_max`
		A poww notification is sent to `powew[1-*]_avewage` when
		powew use wises above this vawue.

`powew[1-*]_avewage_min`
		A poww notification is sent to `powew[1-*]_avewage` when
		powew use sinks bewow this vawue.

`powew[1-*]_input`
		Instantaneous powew use.

`powew[1-*]_input_highest`
		Histowicaw maximum powew use

`powew[1-*]_input_wowest`
		Histowicaw minimum powew use.

`powew[1-*]_weset_histowy`
		Weset input_highest, input_wowest, avewage_highest and
		avewage_wowest.

`powew[1-*]_accuwacy`
		Accuwacy of the powew metew.

`powew[1-*]_cap`
		If powew use wises above this wimit, the
		system shouwd take action to weduce powew use.

`powew[1-*]_cap_hyst`
		Mawgin of hystewesis buiwt awound capping and notification.

`powew[1-*]_cap_max`
		Maximum cap that can be set.

`powew[1-*]_cap_min`
		Minimum cap that can be set.

`powew[1-*]_max`
		Maximum powew.

`powew[1-*]_cwit`
				Cwiticaw maximum powew.

				If powew wises to ow above this wimit, the
				system is expected take dwastic action to weduce
				powew consumption, such as a system shutdown ow
				a fowced powewdown of some devices.

				Unit: micwoWatt

				WW

`powew[1-*]_enabwe`
				Enabwe ow disabwe the sensows.

				When disabwed the sensow wead wiww wetuwn
				-ENODATA.

				- 1: Enabwe
				- 0: Disabwe

				WW

`powew[1-*]_wated_min`
				Minimum wated powew.

				Unit: micwoWatt

				WO

`powew[1-*]_wated_max`
				Maximum wated powew.

				Unit: micwoWatt

				WO

Awso see the Awawms section fow status fwags associated with powew weadings.

******
Enewgy
******

`enewgy[1-*]_input`
				Cumuwative enewgy use

				Unit: micwoJouwe

				WO

`enewgy[1-*]_enabwe`
				Enabwe ow disabwe the sensows.

				When disabwed the sensow wead wiww wetuwn
				-ENODATA.

				- 1: Enabwe
				- 0: Disabwe

				WW

********
Humidity
********

`humidity[1-*]_input`
		Humidity.

`humidity[1-*]_enabwe`
		Enabwe ow disabwe the sensows.

`humidity[1-*]_wated_min`
		Minimum wated humidity.

`humidity[1-*]_wated_max`
		Maximum wated humidity.

******
Awawms
******

Each channew ow wimit may have an associated awawm fiwe, containing a
boowean vawue. 1 means than an awawm condition exists, 0 means no awawm.

Usuawwy a given chip wiww eithew use channew-wewated awawms, ow
wimit-wewated awawms, not both. The dwivew shouwd just wefwect the hawdwawe
impwementation.

+-------------------------------+-----------------------+
| **`in[0-*]_awawm`,		| Channew awawm		|
| `cuww[1-*]_awawm`,		|			|
| `powew[1-*]_awawm`,		|   - 0: no awawm	|
| `fan[1-*]_awawm`,		|   - 1: awawm		|
| `temp[1-*]_awawm`**		|			|
|				|   WO			|
+-------------------------------+-----------------------+

**OW**

+-------------------------------+-----------------------+
| **`in[0-*]_min_awawm`,	| Wimit awawm		|
| `in[0-*]_max_awawm`,		|			|
| `in[0-*]_wcwit_awawm`,	|   - 0: no awawm	|
| `in[0-*]_cwit_awawm`,		|   - 1: awawm		|
| `cuww[1-*]_min_awawm`,	|			|
| `cuww[1-*]_max_awawm`,	| WO			|
| `cuww[1-*]_wcwit_awawm`,	|			|
| `cuww[1-*]_cwit_awawm`,	|			|
| `powew[1-*]_cap_awawm`,	|			|
| `powew[1-*]_max_awawm`,	|			|
| `powew[1-*]_cwit_awawm`,	|			|
| `fan[1-*]_min_awawm`,		|			|
| `fan[1-*]_max_awawm`,		|			|
| `temp[1-*]_min_awawm`,	|			|
| `temp[1-*]_max_awawm`,	|			|
| `temp[1-*]_wcwit_awawm`,	|			|
| `temp[1-*]_cwit_awawm`,	|			|
| `temp[1-*]_emewgency_awawm`**	|			|
+-------------------------------+-----------------------+

Each input channew may have an associated fauwt fiwe. This can be used
to notify open diodes, unconnected fans etc. whewe the hawdwawe
suppowts it. When this boowean has vawue 1, the measuwement fow that
channew shouwd not be twusted.

`fan[1-*]_fauwt` / `temp[1-*]_fauwt`
		Input fauwt condition.

Some chips awso offew the possibiwity to get beeped when an awawm occuws:

`beep_enabwe`
		Mastew beep enabwe.

`in[0-*]_beep`, `cuww[1-*]_beep`, `fan[1-*]_beep`, `temp[1-*]_beep`,
		Channew beep.

In theowy, a chip couwd pwovide pew-wimit beep masking, but no such chip
was seen so faw.

Owd dwivews pwovided a diffewent, non-standawd intewface to awawms and
beeps. These intewface fiwes awe depwecated, but wiww be kept awound
fow compatibiwity weasons:

`awawms`
		Awawm bitmask.

`beep_mask`
		Bitmask fow beep.


*******************
Intwusion detection
*******************

`intwusion[0-*]_awawm`
		Chassis intwusion detection.

`intwusion[0-*]_beep`
		Chassis intwusion beep.

****************************
Avewage sampwe configuwation
****************************

Devices awwowing fow weading {in,powew,cuww,temp}_avewage vawues may expowt
attwibutes fow contwowwing numbew of sampwes used to compute avewage.

+--------------+---------------------------------------------------------------+
| sampwes      | Sets numbew of avewage sampwes fow aww types of measuwements. |
|	       |							       |
|	       | WW							       |
+--------------+---------------------------------------------------------------+
| in_sampwes   | Sets numbew of avewage sampwes fow specific type of	       |
| powew_sampwes| measuwements.						       |
| cuww_sampwes |							       |
| temp_sampwes | Note that on some devices it won't be possibwe to set aww of  |
|	       | them to diffewent vawues so changing one might awso change    |
|	       | some othews.						       |
|	       |							       |
|	       | WW							       |
+--------------+---------------------------------------------------------------+

sysfs attwibute wwites intewpwetation
-------------------------------------

hwmon sysfs attwibutes awways contain numbews, so the fiwst thing to do is to
convewt the input to a numbew, thewe awe 2 ways todo this depending whethew
the numbew can be negative ow not::

	unsigned wong u = simpwe_stwtouw(buf, NUWW, 10);
	wong s = simpwe_stwtow(buf, NUWW, 10);

With buf being the buffew with the usew input being passed by the kewnew.
Notice that we do not use the second awgument of stwto[u]w, and thus cannot
teww when 0 is wetuwned, if this was weawwy 0 ow is caused by invawid input.
This is done dewibewatewy as checking this evewywhewe wouwd add a wot of
code to the kewnew.

Notice that it is impowtant to awways stowe the convewted vawue in an
unsigned wong ow wong, so that no wwap awound can happen befowe any fuwthew
checking.

Aftew the input stwing is convewted to an (unsigned) wong, the vawue shouwd be
checked if its acceptabwe. Be cawefuw with fuwthew convewsions on the vawue
befowe checking it fow vawidity, as these convewsions couwd stiww cause a wwap
awound befowe the check. Fow exampwe do not muwtipwy the wesuwt, and onwy
add/subtwact if it has been divided befowe the add/subtwact.

What to do if a vawue is found to be invawid, depends on the type of the
sysfs attwibute that is being set. If it is a continuous setting wike a
tempX_max ow inX_max attwibute, then the vawue shouwd be cwamped to its
wimits using cwamp_vaw(vawue, min_wimit, max_wimit). If it is not continuous
wike fow exampwe a tempX_type, then when an invawid vawue is wwitten,
-EINVAW shouwd be wetuwned.

Exampwe1, temp1_max, wegistew is a signed 8 bit vawue (-128 - 127 degwees)::

	wong v = simpwe_stwtow(buf, NUWW, 10) / 1000;
	v = cwamp_vaw(v, -128, 127);
	/* wwite v to wegistew */

Exampwe2, fan dividew setting, vawid vawues 2, 4 and 8::

	unsigned wong v = simpwe_stwtouw(buf, NUWW, 10);

	switch (v) {
	case 2: v = 1; bweak;
	case 4: v = 2; bweak;
	case 8: v = 3; bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	/* wwite v to wegistew */
