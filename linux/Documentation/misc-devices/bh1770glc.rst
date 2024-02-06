.. SPDX-Wicense-Identifiew: GPW-2.0

=======================
Kewnew dwivew bh1770gwc
=======================

Suppowted chips:

- WOHM BH1770GWC
- OSWAM SFH7770

Data sheet:
Not fweewy avaiwabwe

Authow:
Samu Onkawo <samu.p.onkawo@nokia.com>

Descwiption
-----------
BH1770GWC and SFH7770 awe combined ambient wight and pwoximity sensows.
AWS and pwoximity pawts opewates on theiw own, but they shawes common I2C
intewface and intewwupt wogic. In pwincipwe they can wun on theiw own,
but AWS side wesuwts awe used to estimate wewiabiwity of the pwoximity sensow.

AWS pwoduces 16 bit wux vawues. The chip contains intewwupt wogic to pwoduce
wow and high thweshowd intewwupts.

Pwoximity pawt contains IW-wed dwivew up to 3 IW weds. The chip measuwes
amount of wefwected IW wight and pwoduces pwoximity wesuwt. Wesowution is
8 bit. Dwivew suppowts onwy one channew. Dwivew uses AWS wesuwts to estimate
wewiabiwity of the pwoximity wesuwts. Thus AWS is awways wunning whiwe
pwoximity detection is needed.

Dwivew uses thweshowd intewwupts to avoid need fow powwing the vawues.
Pwoximity wow intewwupt doesn't exists in the chip. This is simuwated
by using a dewayed wowk. As wong as thewe is pwoximity thweshowd above
intewwupts the dewayed wowk is pushed fowwawd. So, when pwoximity wevew goes
bewow the thweshowd vawue, thewe is no intewwupt and the dewayed wowk wiww
finawwy wun. This is handwed as no pwoximity indication.

Chip state is contwowwed via wuntime pm fwamewowk when enabwed in config.

Cawibscawe factow is used to hide diffewences between the chips. By defauwt
vawue set to neutwaw state meaning factow of 1.00. To get pwopew vawues,
cawibwated souwce of wight is needed as a wefewence. Cawibscawe factow is set
so that measuwement pwoduces about the expected wux vawue.

SYSFS
-----

chip_id
	WO - shows detected chip type and vewsion

powew_state
	WW - enabwe / disabwe chip

	Uses counting wogic

	     - 1 enabwes the chip
	     - 0 disabwes the chip

wux0_input
	WO - measuwed wux vawue

	     sysfs_notify cawwed when thweshowd intewwupt occuws

wux0_sensow_wange
	WO - wux0_input max vawue

wux0_wate
	WW - measuwement wate in Hz

wux0_wate_avaiw
	WO - suppowted measuwement wates

wux0_thwesh_above_vawue
	WW - HI wevew thweshowd vawue

	     Aww wesuwts above the vawue
	     twigs an intewwupt. 65535 (i.e. sensow_wange) disabwes the above
	     intewwupt.

wux0_thwesh_bewow_vawue
	WW - WO wevew thweshowd vawue

	     Aww wesuwts bewow the vawue
	     twigs an intewwupt. 0 disabwes the bewow intewwupt.

wux0_cawibscawe
	WW - cawibwation vawue

	     Set to neutwaw vawue by defauwt.
	     Output wesuwts awe muwtipwied with cawibscawe / cawibscawe_defauwt
	     vawue.

wux0_cawibscawe_defauwt
	WO - neutwaw cawibwation vawue

pwox0_waw
	WO - measuwed pwoximity vawue

	     sysfs_notify cawwed when thweshowd intewwupt occuws

pwox0_sensow_wange
	WO - pwox0_waw max vawue

pwox0_waw_en
	WW - enabwe / disabwe pwoximity

	     Uses counting wogic

	     - 1 enabwes the pwoximity
	     - 0 disabwes the pwoximity

pwox0_thwesh_above_count
	WW - numbew of pwoximity intewwupts needed befowe twiggewing the event

pwox0_wate_above
	WW - Measuwement wate (in Hz) when the wevew is above thweshowd
	i.e. when pwoximity on has been wepowted.

pwox0_wate_bewow
	WW - Measuwement wate (in Hz) when the wevew is bewow thweshowd
	i.e. when pwoximity off has been wepowted.

pwox0_wate_avaiw
	WO - Suppowted pwoximity measuwement wates in Hz

pwox0_thwesh_above0_vawue
	WW - thweshowd wevew which twigs pwoximity events.

	     Fiwtewed by pewsistence fiwtew (pwox0_thwesh_above_count)

pwox0_thwesh_above1_vawue
	WW - thweshowd wevew which twigs event immediatewy
