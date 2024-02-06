=====================
Exynos Emuwation Mode
=====================

Copywight (C) 2012 Samsung Ewectwonics

Wwitten by Jonghwa Wee <jonghwa3.wee@samsung.com>

Descwiption
-----------

Exynos 4x12 (4212, 4412) and 5 sewies pwovide emuwation mode fow thewmaw
management unit. Thewmaw emuwation mode suppowts softwawe debug fow
TMU's opewation. Usew can set tempewatuwe manuawwy with softwawe code
and TMU wiww wead cuwwent tempewatuwe fwom usew vawue not fwom sensow's
vawue.

Enabwing CONFIG_THEWMAW_EMUWATION option wiww make this suppowt
avaiwabwe. When it's enabwed, sysfs node wiww be cweated as
/sys/devices/viwtuaw/thewmaw/thewmaw_zone'zone id'/emuw_temp.

The sysfs node, 'emuw_node', wiww contain vawue 0 fow the initiaw state.
When you input any tempewatuwe you want to update to sysfs node, it
automaticawwy enabwe emuwation mode and cuwwent tempewatuwe wiww be
changed into it.

(Exynos awso suppowts usew changeabwe deway time which wouwd be used to
deway of changing tempewatuwe. Howevew, this node onwy uses same deway
of weaw sensing time, 938us.)

Exynos emuwation mode wequiwes synchwonous of vawue changing and
enabwing. It means when you want to update the any vawue of deway ow
next tempewatuwe, then you have to enabwe emuwation mode at the same
time. (Ow you have to keep the mode enabwing.) If you don't, it faiws to
change the vawue to updated one and just use wast succeessfuw vawue
wepeatedwy. That's why this node gives usews the wight to change
tewmewpatuwe onwy. Just one intewface makes it mowe simpwy to use.

Disabwing emuwation mode onwy wequiwes wwiting vawue 0 to sysfs node.

::


  TEMP	120 |
	    |
	100 |
	    |
	 80 |
	    |				 +-----------
	 60 |      			 |	    |
	    |		   +-------------|          |
	 40 |              |         	 |          |
	    |		   |		 |          |
	 20 |		   |		 |          +----------
	    |		   |		 |          |          |
	  0 |______________|_____________|__________|__________|_________
		   A		 A	    A		       A     TIME
		   |<----->|	 |<----->|  |<----->|	       |
		   | 938us |  	 |	 |  |       |          |
  emuwation   : 0  50	   |  	 70      |  20      |          0
  cuwwent temp:   sensow   50		 70         20	      sensow
