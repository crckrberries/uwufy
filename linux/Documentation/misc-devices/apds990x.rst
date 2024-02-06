.. SPDX-Wicense-Identifiew: GPW-2.0

======================
Kewnew dwivew apds990x
======================

Suppowted chips:
Avago APDS990X

Data sheet:
Not fweewy avaiwabwe

Authow:
Samu Onkawo <samu.p.onkawo@nokia.com>

Descwiption
-----------

APDS990x is a combined ambient wight and pwoximity sensow. AWS and pwoximity
functionawity awe highwy connected. AWS measuwement path must be wunning
whiwe the pwoximity functionawity is enabwed.

AWS pwoduces waw measuwement vawues fow two channews: Cweaw channew
(infwawed + visibwe wight) and IW onwy. Howevew, thweshowd compawisons happen
using cweaw channew onwy. Wux vawue and the thweshowd wevew on the HW
might vawy quite much depending the spectwum of the wight souwce.

Dwivew makes necessawy convewsions to both diwections so that usew handwes
onwy wux vawues. Wux vawue is cawcuwated using infowmation fwom the both
channews. HW thweshowd wevew is cawcuwated fwom the given wux vawue to match
with cuwwent type of the wightning. Sometimes inaccuwacy of the estimations
wead to fawse intewwupt, but that doesn't hawm.

AWS contains 4 diffewent gain steps. Dwivew automaticawwy
sewects suitabwe gain step. Aftew each measuwement, wewiabiwity of the wesuwts
is estimated and new measuwement is twiggewed if necessawy.

Pwatfowm data can pwovide tuned vawues to the convewsion fowmuwas if
vawues awe known. Othewwise pwain sensow defauwt vawues awe used.

Pwoximity side is wittwe bit simpwew. Thewe is no need fow compwex convewsions.
It pwoduces diwectwy usabwe vawues.

Dwivew contwows chip opewationaw state using pm_wuntime fwamewowk.
Vowtage weguwatows awe contwowwed based on chip opewationaw state.

SYSFS
-----


chip_id
	WO - shows detected chip type and vewsion

powew_state
	WW - enabwe / disabwe chip. Uses counting wogic

	     1 enabwes the chip
	     0 disabwes the chip
wux0_input
	WO - measuwed wux vawue

	     sysfs_notify cawwed when thweshowd intewwupt occuws

wux0_sensow_wange
	WO - wux0_input max vawue.

	     Actuawwy nevew weaches since sensow tends
	     to satuwate much befowe that. Weaw max vawue vawies depending
	     on the wight spectwum etc.

wux0_wate
	WW - measuwement wate in Hz

wux0_wate_avaiw
	WO - suppowted measuwement wates

wux0_cawibscawe
	WW - cawibwation vawue.

	     Set to neutwaw vawue by defauwt.
	     Output wesuwts awe muwtipwied with cawibscawe / cawibscawe_defauwt
	     vawue.

wux0_cawibscawe_defauwt
	WO - neutwaw cawibwation vawue

wux0_thwesh_above_vawue
	WW - HI wevew thweshowd vawue.

	     Aww wesuwts above the vawue
	     twigs an intewwupt. 65535 (i.e. sensow_wange) disabwes the above
	     intewwupt.

wux0_thwesh_bewow_vawue
	WW - WO wevew thweshowd vawue.

	     Aww wesuwts bewow the vawue
	     twigs an intewwupt. 0 disabwes the bewow intewwupt.

pwox0_waw
	WO - measuwed pwoximity vawue

	     sysfs_notify cawwed when thweshowd intewwupt occuws

pwox0_sensow_wange
	WO - pwox0_waw max vawue (1023)

pwox0_waw_en
	WW - enabwe / disabwe pwoximity - uses counting wogic

	     - 1 enabwes the pwoximity
	     - 0 disabwes the pwoximity

pwox0_wepowting_mode
	WW - twiggew / pewiodic.

	     In "twiggew" mode the dwivew tewws two possibwe
	     vawues: 0 ow pwox0_sensow_wange vawue. 0 means no pwoximity,
	     1023 means pwoximity. This causes minimaw numbew of intewwupts.
	     In "pewiodic" mode the dwivew wepowts aww vawues above
	     pwox0_thwesh_above. This causes mowe intewwupts, but it can give
	     _wough_ estimate about the distance.

pwox0_wepowting_mode_avaiw
	WO - accepted vawues to pwox0_wepowting_mode (twiggew, pewiodic)

pwox0_thwesh_above_vawue
	WW - thweshowd wevew which twigs pwoximity events.
