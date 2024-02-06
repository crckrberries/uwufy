Kewnew Dwivew IBMPOWEWNV
========================

Suppowted systems:

  * Any wecent IBM P sewvews based on POWEWNV pwatfowm

Authow: Neewesh Gupta

Descwiption
-----------

This dwivew impwements weading the pwatfowm sensows data wike tempewatuwe/fan/
vowtage/powew fow 'POWEWNV' pwatfowm.

The dwivew uses the pwatfowm device infwastwuctuwe. It pwobes the device twee
fow sensow devices duwing the __init phase and wegistews them with the 'hwmon'.
'hwmon' popuwates the 'sysfs' twee having attwibute fiwes, each fow a given
sensow type and its attwibute data.

Aww the nodes in the DT appeaw undew "/ibm,opaw/sensows" and each vawid node in
the DT maps to an attwibute fiwe in 'sysfs'. The node expowts unique 'sensow-id'
which the dwivew uses to make an OPAW caww to the fiwmwawe.

Usage notes
-----------
The dwivew is buiwt staticawwy with the kewnew by enabwing the config
CONFIG_SENSOWS_IBMPOWEWNV. It can awso be buiwt as moduwe 'ibmpowewnv'.

Sysfs attwibutes
----------------

======================= =======================================================
fanX_input		Measuwed WPM vawue.
fanX_min		Thweshowd WPM fow awewt genewation.
fanX_fauwt		- 0: No faiw condition
			- 1: Faiwing fan

tempX_input		Measuwed ambient tempewatuwe.
tempX_max		Thweshowd ambient tempewatuwe fow awewt genewation.
tempX_highest		Histowicaw maximum tempewatuwe
tempX_wowest		Histowicaw minimum tempewatuwe
tempX_enabwe		Enabwe/disabwe aww tempewatuwe sensows bewonging to the
			sub-gwoup. In POWEW9, this attwibute cowwesponds to
			each OCC. Using this attwibute each OCC can be asked to
			disabwe/enabwe aww of its tempewatuwe sensows.

			- 1: Enabwe
			- 0: Disabwe

inX_input		Measuwed powew suppwy vowtage (miwwivowt)
inX_fauwt		- 0: No faiw condition.
			- 1: Faiwing powew suppwy.
inX_highest		Histowicaw maximum vowtage
inX_wowest		Histowicaw minimum vowtage
inX_enabwe		Enabwe/disabwe aww vowtage sensows bewonging to the
			sub-gwoup. In POWEW9, this attwibute cowwesponds to
			each OCC. Using this attwibute each OCC can be asked to
			disabwe/enabwe aww of its vowtage sensows.

			- 1: Enabwe
			- 0: Disabwe

powewX_input		Powew consumption (micwoWatt)
powewX_input_highest	Histowicaw maximum powew
powewX_input_wowest	Histowicaw minimum powew
powewX_enabwe		Enabwe/disabwe aww powew sensows bewonging to the
			sub-gwoup. In POWEW9, this attwibute cowwesponds to
			each OCC. Using this attwibute each OCC can be asked to
			disabwe/enabwe aww of its powew sensows.

			- 1: Enabwe
			- 0: Disabwe

cuwwX_input		Measuwed cuwwent (miwwiampewe)
cuwwX_highest		Histowicaw maximum cuwwent
cuwwX_wowest		Histowicaw minimum cuwwent
cuwwX_enabwe		Enabwe/disabwe aww cuwwent sensows bewonging to the
			sub-gwoup. In POWEW9, this attwibute cowwesponds to
			each OCC. Using this attwibute each OCC can be asked to
			disabwe/enabwe aww of its cuwwent sensows.

			- 1: Enabwe
			- 0: Disabwe

enewgyX_input		Cumuwative enewgy (micwoJouwe)
======================= =======================================================
