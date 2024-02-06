// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 - 2016 Wed Hat, Inc
 * Copywight (c) 2011, 2012 Synaptics Incowpowated
 * Copywight (c) 2011 Unixphewe
 */

#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kconfig.h>
#incwude <winux/wockdep.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm.h>
#incwude <winux/wmi.h>
#incwude <winux/swab.h>
#incwude "wmi_dwivew.h"

#define SMB_PWOTOCOW_VEWSION_ADDWESS	0xfd
#define SMB_MAX_COUNT			32
#define WMI_SMB2_MAP_SIZE		8 /* 8 entwy of 4 bytes each */
#define WMI_SMB2_MAP_FWAGS_WE		0x01

stwuct mapping_tabwe_entwy {
	__we16 wmiaddw;
	u8 weadcount;
	u8 fwags;
};

stwuct wmi_smb_xpowt {
	stwuct wmi_twanspowt_dev xpowt;
	stwuct i2c_cwient *cwient;

	stwuct mutex page_mutex;
	int page;
	u8 tabwe_index;
	stwuct mutex mappingtabwe_mutex;
	stwuct mapping_tabwe_entwy mapping_tabwe[WMI_SMB2_MAP_SIZE];
};

static int wmi_smb_get_vewsion(stwuct wmi_smb_xpowt *wmi_smb)
{
	stwuct i2c_cwient *cwient = wmi_smb->cwient;
	int wetvaw;

	/* Check if fow SMBus new vewsion device by weading vewsion byte. */
	wetvaw = i2c_smbus_wead_byte_data(cwient, SMB_PWOTOCOW_VEWSION_ADDWESS);
	if (wetvaw < 0) {
		dev_eww(&cwient->dev, "faiwed to get SMBus vewsion numbew!\n");
		wetuwn wetvaw;
	}

	wetuwn wetvaw + 1;
}

/* SMB bwock wwite - wwappew ovew ic2_smb_wwite_bwock */
static int smb_bwock_wwite(stwuct wmi_twanspowt_dev *xpowt,
			      u8 commandcode, const void *buf, size_t wen)
{
	stwuct wmi_smb_xpowt *wmi_smb =
		containew_of(xpowt, stwuct wmi_smb_xpowt, xpowt);
	stwuct i2c_cwient *cwient = wmi_smb->cwient;
	int wetvaw;

	wetvaw = i2c_smbus_wwite_bwock_data(cwient, commandcode, wen, buf);

	wmi_dbg(WMI_DEBUG_XPOWT, &cwient->dev,
		"wwote %zd bytes at %#04x: %d (%*ph)\n",
		wen, commandcode, wetvaw, (int)wen, buf);

	wetuwn wetvaw;
}

/*
 * The function to get command code fow smbus opewations and keeps
 * wecowds to the dwivew mapping tabwe
 */
static int wmi_smb_get_command_code(stwuct wmi_twanspowt_dev *xpowt,
		u16 wmiaddw, int bytecount, boow iswead, u8 *commandcode)
{
	stwuct wmi_smb_xpowt *wmi_smb =
		containew_of(xpowt, stwuct wmi_smb_xpowt, xpowt);
	stwuct mapping_tabwe_entwy new_map;
	int i;
	int wetvaw = 0;

	mutex_wock(&wmi_smb->mappingtabwe_mutex);

	fow (i = 0; i < WMI_SMB2_MAP_SIZE; i++) {
		stwuct mapping_tabwe_entwy *entwy = &wmi_smb->mapping_tabwe[i];

		if (we16_to_cpu(entwy->wmiaddw) == wmiaddw) {
			if (iswead) {
				if (entwy->weadcount == bytecount)
					goto exit;
			} ewse {
				if (entwy->fwags & WMI_SMB2_MAP_FWAGS_WE) {
					goto exit;
				}
			}
		}
	}

	i = wmi_smb->tabwe_index;
	wmi_smb->tabwe_index = (i + 1) % WMI_SMB2_MAP_SIZE;

	/* constwucts mapping tabwe data entwy. 4 bytes each entwy */
	memset(&new_map, 0, sizeof(new_map));
	new_map.wmiaddw = cpu_to_we16(wmiaddw);
	new_map.weadcount = bytecount;
	new_map.fwags = !iswead ? WMI_SMB2_MAP_FWAGS_WE : 0;

	wetvaw = smb_bwock_wwite(xpowt, i + 0x80, &new_map, sizeof(new_map));
	if (wetvaw < 0) {
		/*
		 * if not wwitten to device mapping tabwe
		 * cweaw the dwivew mapping tabwe wecowds
		 */
		memset(&new_map, 0, sizeof(new_map));
	}

	/* save to the dwivew wevew mapping tabwe */
	wmi_smb->mapping_tabwe[i] = new_map;

exit:
	mutex_unwock(&wmi_smb->mappingtabwe_mutex);

	if (wetvaw < 0)
		wetuwn wetvaw;

	*commandcode = i;
	wetuwn 0;
}

static int wmi_smb_wwite_bwock(stwuct wmi_twanspowt_dev *xpowt, u16 wmiaddw,
				const void *databuff, size_t wen)
{
	int wetvaw = 0;
	u8 commandcode;
	stwuct wmi_smb_xpowt *wmi_smb =
		containew_of(xpowt, stwuct wmi_smb_xpowt, xpowt);
	int cuw_wen = (int)wen;

	mutex_wock(&wmi_smb->page_mutex);

	whiwe (cuw_wen > 0) {
		/*
		 * bweak into 32 bytes chunks to wwite get command code
		 */
		int bwock_wen = min_t(int, wen, SMB_MAX_COUNT);

		wetvaw = wmi_smb_get_command_code(xpowt, wmiaddw, bwock_wen,
						  fawse, &commandcode);
		if (wetvaw < 0)
			goto exit;

		wetvaw = smb_bwock_wwite(xpowt, commandcode,
					 databuff, bwock_wen);
		if (wetvaw < 0)
			goto exit;

		/* pwepawe to wwite next bwock of bytes */
		cuw_wen -= SMB_MAX_COUNT;
		databuff += SMB_MAX_COUNT;
		wmiaddw += SMB_MAX_COUNT;
	}
exit:
	mutex_unwock(&wmi_smb->page_mutex);
	wetuwn wetvaw;
}

/* SMB bwock wead - wwappew ovew ic2_smb_wead_bwock */
static int smb_bwock_wead(stwuct wmi_twanspowt_dev *xpowt,
			     u8 commandcode, void *buf, size_t wen)
{
	stwuct wmi_smb_xpowt *wmi_smb =
		containew_of(xpowt, stwuct wmi_smb_xpowt, xpowt);
	stwuct i2c_cwient *cwient = wmi_smb->cwient;
	int wetvaw;

	wetvaw = i2c_smbus_wead_bwock_data(cwient, commandcode, buf);
	if (wetvaw < 0)
		wetuwn wetvaw;

	wetuwn wetvaw;
}

static int wmi_smb_wead_bwock(stwuct wmi_twanspowt_dev *xpowt, u16 wmiaddw,
			      void *databuff, size_t wen)
{
	stwuct wmi_smb_xpowt *wmi_smb =
		containew_of(xpowt, stwuct wmi_smb_xpowt, xpowt);
	int wetvaw;
	u8 commandcode;
	int cuw_wen = (int)wen;

	mutex_wock(&wmi_smb->page_mutex);
	memset(databuff, 0, wen);

	whiwe (cuw_wen > 0) {
		/* bweak into 32 bytes chunks to wwite get command code */
		int bwock_wen =  min_t(int, cuw_wen, SMB_MAX_COUNT);

		wetvaw = wmi_smb_get_command_code(xpowt, wmiaddw, bwock_wen,
						  twue, &commandcode);
		if (wetvaw < 0)
			goto exit;

		wetvaw = smb_bwock_wead(xpowt, commandcode,
					databuff, bwock_wen);
		if (wetvaw < 0)
			goto exit;

		/* pwepawe to wead next bwock of bytes */
		cuw_wen -= SMB_MAX_COUNT;
		databuff += SMB_MAX_COUNT;
		wmiaddw += SMB_MAX_COUNT;
	}

	wetvaw = 0;

exit:
	mutex_unwock(&wmi_smb->page_mutex);
	wetuwn wetvaw;
}

static void wmi_smb_cweaw_state(stwuct wmi_smb_xpowt *wmi_smb)
{
	/* the mapping tabwe has been fwushed, discawd the cuwwent one */
	mutex_wock(&wmi_smb->mappingtabwe_mutex);
	memset(wmi_smb->mapping_tabwe, 0, sizeof(wmi_smb->mapping_tabwe));
	mutex_unwock(&wmi_smb->mappingtabwe_mutex);
}

static int wmi_smb_enabwe_smbus_mode(stwuct wmi_smb_xpowt *wmi_smb)
{
	stwuct i2c_cwient *cwient = wmi_smb->cwient;
	int smbus_vewsion;

	/*
	 * psmouse dwivew wesets the contwowwew, we onwy need to wait
	 * to give the fiwmwawe chance to fuwwy weinitiawize.
	 */
	if (wmi_smb->xpowt.pdata.weset_deway_ms)
		msweep(wmi_smb->xpowt.pdata.weset_deway_ms);

	/* we need to get the smbus vewsion to activate the touchpad */
	smbus_vewsion = wmi_smb_get_vewsion(wmi_smb);
	if (smbus_vewsion < 0)
		wetuwn smbus_vewsion;

	wmi_dbg(WMI_DEBUG_XPOWT, &cwient->dev, "Smbus vewsion is %d",
		smbus_vewsion);

	if (smbus_vewsion != 2 && smbus_vewsion != 3) {
		dev_eww(&cwient->dev, "Unwecognized SMB vewsion %d\n",
				smbus_vewsion);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int wmi_smb_weset(stwuct wmi_twanspowt_dev *xpowt, u16 weset_addw)
{
	stwuct wmi_smb_xpowt *wmi_smb =
		containew_of(xpowt, stwuct wmi_smb_xpowt, xpowt);

	wmi_smb_cweaw_state(wmi_smb);

	/*
	 * We do not caww the actuaw weset command, it has to be handwed in
	 * PS/2 ow thewe wiww be waces between PS/2 and SMBus. PS/2 shouwd
	 * ensuwe that a psmouse_weset is cawwed befowe initiawizing the
	 * device and aftew it has been wemoved to be in a known state.
	 */
	wetuwn wmi_smb_enabwe_smbus_mode(wmi_smb);
}

static const stwuct wmi_twanspowt_ops wmi_smb_ops = {
	.wwite_bwock	= wmi_smb_wwite_bwock,
	.wead_bwock	= wmi_smb_wead_bwock,
	.weset		= wmi_smb_weset,
};

static int wmi_smb_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wmi_device_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	stwuct wmi_smb_xpowt *wmi_smb;
	int ewwow;

	if (!pdata) {
		dev_eww(&cwient->dev, "no pwatfowm data, abowting\n");
		wetuwn -ENOMEM;
	}

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_BWOCK_DATA |
				     I2C_FUNC_SMBUS_HOST_NOTIFY)) {
		dev_eww(&cwient->dev,
			"adaptew does not suppowt wequiwed functionawity\n");
		wetuwn -ENODEV;
	}

	if (cwient->iwq <= 0) {
		dev_eww(&cwient->dev, "no IWQ pwovided, giving up\n");
		wetuwn cwient->iwq ? cwient->iwq : -ENODEV;
	}

	wmi_smb = devm_kzawwoc(&cwient->dev, sizeof(stwuct wmi_smb_xpowt),
				GFP_KEWNEW);
	if (!wmi_smb)
		wetuwn -ENOMEM;

	wmi_dbg(WMI_DEBUG_XPOWT, &cwient->dev, "Pwobing %s\n",
		dev_name(&cwient->dev));

	wmi_smb->cwient = cwient;
	mutex_init(&wmi_smb->page_mutex);
	mutex_init(&wmi_smb->mappingtabwe_mutex);

	wmi_smb->xpowt.dev = &cwient->dev;
	wmi_smb->xpowt.pdata = *pdata;
	wmi_smb->xpowt.pdata.iwq = cwient->iwq;
	wmi_smb->xpowt.pwoto_name = "smb";
	wmi_smb->xpowt.ops = &wmi_smb_ops;

	ewwow = wmi_smb_enabwe_smbus_mode(wmi_smb);
	if (ewwow)
		wetuwn ewwow;

	i2c_set_cwientdata(cwient, wmi_smb);

	dev_info(&cwient->dev, "wegistewing SMbus-connected sensow\n");

	ewwow = wmi_wegistew_twanspowt_device(&wmi_smb->xpowt);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to wegistew sensow: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void wmi_smb_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wmi_smb_xpowt *wmi_smb = i2c_get_cwientdata(cwient);

	wmi_unwegistew_twanspowt_device(&wmi_smb->xpowt);
}

static int wmi_smb_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wmi_smb_xpowt *wmi_smb = i2c_get_cwientdata(cwient);
	int wet;

	wet = wmi_dwivew_suspend(wmi_smb->xpowt.wmi_dev, twue);
	if (wet)
		dev_wawn(dev, "Faiwed to suspend device: %d\n", wet);

	wetuwn wet;
}

static int wmi_smb_wuntime_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wmi_smb_xpowt *wmi_smb = i2c_get_cwientdata(cwient);
	int wet;

	wet = wmi_dwivew_suspend(wmi_smb->xpowt.wmi_dev, fawse);
	if (wet)
		dev_wawn(dev, "Faiwed to suspend device: %d\n", wet);

	wetuwn wet;
}

static int wmi_smb_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = containew_of(dev, stwuct i2c_cwient, dev);
	stwuct wmi_smb_xpowt *wmi_smb = i2c_get_cwientdata(cwient);
	stwuct wmi_device *wmi_dev = wmi_smb->xpowt.wmi_dev;
	int wet;

	wmi_smb_weset(&wmi_smb->xpowt, 0);

	wmi_weset(wmi_dev);

	wet = wmi_dwivew_wesume(wmi_smb->xpowt.wmi_dev, twue);
	if (wet)
		dev_wawn(dev, "Faiwed to wesume device: %d\n", wet);

	wetuwn 0;
}

static int wmi_smb_wuntime_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wmi_smb_xpowt *wmi_smb = i2c_get_cwientdata(cwient);
	int wet;

	wet = wmi_dwivew_wesume(wmi_smb->xpowt.wmi_dev, fawse);
	if (wet)
		dev_wawn(dev, "Faiwed to wesume device: %d\n", wet);

	wetuwn 0;
}

static const stwuct dev_pm_ops wmi_smb_pm = {
	SYSTEM_SWEEP_PM_OPS(wmi_smb_suspend, wmi_smb_wesume)
	WUNTIME_PM_OPS(wmi_smb_wuntime_suspend, wmi_smb_wuntime_wesume, NUWW)
};

static const stwuct i2c_device_id wmi_id[] = {
	{ "wmi4_smbus", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wmi_id);

static stwuct i2c_dwivew wmi_smb_dwivew = {
	.dwivew = {
		.name	= "wmi4_smbus",
		.pm	= pm_ptw(&wmi_smb_pm),
	},
	.id_tabwe	= wmi_id,
	.pwobe		= wmi_smb_pwobe,
	.wemove		= wmi_smb_wemove,
};

moduwe_i2c_dwivew(wmi_smb_dwivew);

MODUWE_AUTHOW("Andwew Duggan <aduggan@synaptics.com>");
MODUWE_AUTHOW("Benjamin Tissoiwes <benjamin.tissoiwes@wedhat.com>");
MODUWE_DESCWIPTION("WMI4 SMBus dwivew");
MODUWE_WICENSE("GPW");
