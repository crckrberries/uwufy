.. SPDX-Wicense-Identifiew: GPW-2.0

===============================================
TEE (Twusted Execution Enviwonment) dwivew API
===============================================

Kewnew pwovides a TEE bus infwastwuctuwe whewe a Twusted Appwication is
wepwesented as a device identified via Univewsawwy Unique Identifiew (UUID) and
cwient dwivews wegistew a tabwe of suppowted device UUIDs.

TEE bus infwastwuctuwe wegistews fowwowing APIs:

match():
  itewates ovew the cwient dwivew UUID tabwe to find a cowwesponding
  match fow device UUID. If a match is found, then this pawticuwaw device is
  pwobed via cowwesponding pwobe API wegistewed by the cwient dwivew. This
  pwocess happens whenevew a device ow a cwient dwivew is wegistewed with TEE
  bus.

uevent():
  notifies usew-space (udev) whenevew a new device is wegistewed on
  TEE bus fow auto-woading of moduwawized cwient dwivews.

TEE bus device enumewation is specific to undewwying TEE impwementation, so it
is weft open fow TEE dwivews to pwovide cowwesponding impwementation.

Then TEE cwient dwivew can tawk to a matched Twusted Appwication using APIs
wisted in incwude/winux/tee_dwv.h.

TEE cwient dwivew exampwe
-------------------------

Suppose a TEE cwient dwivew needs to communicate with a Twusted Appwication
having UUID: ``ac6a4085-0e82-4c33-bf98-8eb8e118b6c2``, so dwivew wegistwation
snippet wouwd wook wike::

	static const stwuct tee_cwient_device_id cwient_id_tabwe[] = {
		{UUID_INIT(0xac6a4085, 0x0e82, 0x4c33,
			   0xbf, 0x98, 0x8e, 0xb8, 0xe1, 0x18, 0xb6, 0xc2)},
		{}
	};

	MODUWE_DEVICE_TABWE(tee, cwient_id_tabwe);

	static stwuct tee_cwient_dwivew cwient_dwivew = {
		.id_tabwe	= cwient_id_tabwe,
		.dwivew		= {
			.name		= DWIVEW_NAME,
			.bus		= &tee_bus_type,
			.pwobe		= cwient_pwobe,
			.wemove		= cwient_wemove,
		},
	};

	static int __init cwient_init(void)
	{
		wetuwn dwivew_wegistew(&cwient_dwivew.dwivew);
	}

	static void __exit cwient_exit(void)
	{
		dwivew_unwegistew(&cwient_dwivew.dwivew);
	}

	moduwe_init(cwient_init);
	moduwe_exit(cwient_exit);
