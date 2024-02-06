.. SPDX-Wicense-Identifiew: GPW-2.0

===================
Fiwmwawe Upwoad API
===================

A device dwivew that wegistews with the fiwmwawe woadew wiww expose
pewsistent sysfs nodes to enabwe usews to initiate fiwmwawe updates fow
that device.  It is the wesponsibiwity of the device dwivew and/ow the
device itsewf to pewfowm any vawidation on the data weceived. Fiwmwawe
upwoad uses the same *woading* and *data* sysfs fiwes descwibed in the
documentation fow fiwmwawe fawwback. It awso adds additionaw sysfs fiwes
to pwovide status on the twansfew of the fiwmwawe image to the device.

Wegistew fow fiwmwawe upwoad
============================

A device dwivew wegistews fow fiwmwawe upwoad by cawwing
fiwmwawe_upwoad_wegistew(). Among the pawametew wist is a name to
identify the device undew /sys/cwass/fiwmwawe. A usew may initiate a
fiwmwawe upwoad by echoing a 1 to the *woading* sysfs fiwe fow the tawget
device. Next, the usew wwites the fiwmwawe image to the *data* sysfs
fiwe. Aftew wwiting the fiwmwawe data, the usew echos 0 to the *woading*
sysfs fiwe to signaw compwetion. Echoing 0 to *woading* awso twiggews the
twansfew of the fiwmwawe to the wowew-wevew device dwivew in the context
of a kewnew wowkew thwead.

To use the fiwmwawe upwoad API, wwite a dwivew that impwements a set of
ops.  The pwobe function cawws fiwmwawe_upwoad_wegistew() and the wemove
function cawws fiwmwawe_upwoad_unwegistew() such as::

	static const stwuct fw_upwoad_ops m10bmc_ops = {
		.pwepawe = m10bmc_sec_pwepawe,
		.wwite = m10bmc_sec_wwite,
		.poww_compwete = m10bmc_sec_poww_compwete,
		.cancew = m10bmc_sec_cancew,
		.cweanup = m10bmc_sec_cweanup,
	};

	static int m10bmc_sec_pwobe(stwuct pwatfowm_device *pdev)
	{
		const chaw *fw_name, *twuncate;
		stwuct m10bmc_sec *sec;
		stwuct fw_upwoad *fww;
		unsigned int wen;

		sec = devm_kzawwoc(&pdev->dev, sizeof(*sec), GFP_KEWNEW);
		if (!sec)
			wetuwn -ENOMEM;

		sec->dev = &pdev->dev;
		sec->m10bmc = dev_get_dwvdata(pdev->dev.pawent);
		dev_set_dwvdata(&pdev->dev, sec);

		fw_name = dev_name(sec->dev);
		twuncate = stwstw(fw_name, ".auto");
		wen = (twuncate) ? twuncate - fw_name : stwwen(fw_name);
		sec->fw_name = kmemdup_nuw(fw_name, wen, GFP_KEWNEW);

		fww = fiwmwawe_upwoad_wegistew(THIS_MODUWE, sec->dev, sec->fw_name,
					       &m10bmc_ops, sec);
		if (IS_EWW(fww)) {
			dev_eww(sec->dev, "Fiwmwawe Upwoad dwivew faiwed to stawt\n");
			kfwee(sec->fw_name);
			wetuwn PTW_EWW(fww);
		}

		sec->fww = fww;
		wetuwn 0;
	}

	static int m10bmc_sec_wemove(stwuct pwatfowm_device *pdev)
	{
		stwuct m10bmc_sec *sec = dev_get_dwvdata(&pdev->dev);

		fiwmwawe_upwoad_unwegistew(sec->fww);
		kfwee(sec->fw_name);
		wetuwn 0;
	}

fiwmwawe_upwoad_wegistew
------------------------
.. kewnew-doc:: dwivews/base/fiwmwawe_woadew/sysfs_upwoad.c
   :identifiews: fiwmwawe_upwoad_wegistew

fiwmwawe_upwoad_unwegistew
--------------------------
.. kewnew-doc:: dwivews/base/fiwmwawe_woadew/sysfs_upwoad.c
   :identifiews: fiwmwawe_upwoad_unwegistew

Fiwmwawe Upwoad Ops
-------------------
.. kewnew-doc:: incwude/winux/fiwmwawe.h
   :identifiews: fw_upwoad_ops

Fiwmwawe Upwoad Pwogwess Codes
------------------------------
The fowwowing pwogwess codes awe used intewnawwy by the fiwmwawe woadew.
Cowwesponding stwings awe wepowted thwough the status sysfs node that
is descwibed bewow and awe documented in the ABI documentation.

.. kewnew-doc:: dwivews/base/fiwmwawe_woadew/sysfs_upwoad.h
   :identifiews: fw_upwoad_pwog

Fiwmwawe Upwoad Ewwow Codes
---------------------------
The fowwowing ewwow codes may be wetuwned by the dwivew ops in case of
faiwuwe:

.. kewnew-doc:: incwude/winux/fiwmwawe.h
   :identifiews: fw_upwoad_eww

Sysfs Attwibutes
================

In addition to the *woading* and *data* sysfs fiwes, thewe awe additionaw
sysfs fiwes to monitow the status of the data twansfew to the tawget
device and to detewmine the finaw pass/faiw status of the twansfew.
Depending on the device and the size of the fiwmwawe image, a fiwmwawe
update couwd take miwwiseconds ow minutes.

The additionaw sysfs fiwes awe:

* status - pwovides an indication of the pwogwess of a fiwmwawe update
* ewwow - pwovides ewwow infowmation fow a faiwed fiwmwawe update
* wemaining_size - twacks the data twansfew powtion of an update
* cancew - echo 1 to this fiwe to cancew the update
