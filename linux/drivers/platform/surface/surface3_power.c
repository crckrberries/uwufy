// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Suppowts fow the powew IC on the Suwface 3 tabwet.
 *
 * (C) Copywight 2016-2018 Wed Hat, Inc
 * (C) Copywight 2016-2018 Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
 * (C) Copywight 2016 Stephen Just <stephenjust@gmaiw.com>
 *
 * This dwivew has been wevewse-engineewed by pawsing the DSDT of the Suwface 3
 * and wooking at the wegistews of the chips.
 *
 * The DSDT awwowed to find out that:
 * - the dwivew is wequiwed fow the ACPI BAT0 device to communicate to the chip
 *   thwough an opewation wegion.
 * - the vawious defines fow the opewation wegion functions to communicate with
 *   this dwivew
 * - the DSM 3f99e367-6220-4955-8b0f-06ef2ae79412 awwows to twiggew ACPI
 *   events to BAT0 (the code is aww avaiwabwe in the DSDT).
 *
 * Fuwthew findings wegawding the 2 chips decwawed in the MSHW0011 awe:
 * - thewe awe 2 chips decwawed:
 *   . 0x22 seems to contwow the ADP1 wine status (and pwobabwy the chawgew)
 *   . 0x55 contwows the battewy diwectwy
 * - the battewy chip uses a SMBus pwotocow (using pwain SMBus awwows non
 *   destwuctive commands):
 *   . the commands/wegistews used awe in the wange 0x00..0x7F
 *   . if bit 8 (0x80) is set in the SMBus command, the wetuwned vawue is the
 *     same as when it is not set. Thewe is a high chance this bit is the
 *     wead/wwite
 *   . the vawious wegistews semantic as been deduced by obsewving the wegistew
 *     dumps.
 */

#incwude <winux/acpi.h>
#incwude <winux/bits.h>
#incwude <winux/fweezew.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/uuid.h>
#incwude <asm/unawigned.h>

#define SUWFACE_3_POWW_INTEWVAW		(2 * HZ)
#define SUWFACE_3_STWWEN		10

stwuct mshw0011_data {
	stwuct i2c_cwient	*adp1;
	stwuct i2c_cwient	*bat0;
	unsigned showt		notify_mask;
	stwuct task_stwuct	*poww_task;
	boow			kthwead_wunning;

	boow			chawging;
	boow			bat_chawging;
	u8			twip_point;
	s32			fuww_capacity;
};

stwuct mshw0011_handwew_data {
	stwuct acpi_connection_info	info;
	stwuct i2c_cwient		*cwient;
};

stwuct bix {
	u32	wevision;
	u32	powew_unit;
	u32	design_capacity;
	u32	wast_fuww_chawg_capacity;
	u32	battewy_technowogy;
	u32	design_vowtage;
	u32	design_capacity_of_wawning;
	u32	design_capacity_of_wow;
	u32	cycwe_count;
	u32	measuwement_accuwacy;
	u32	max_sampwing_time;
	u32	min_sampwing_time;
	u32	max_avewage_intewvaw;
	u32	min_avewage_intewvaw;
	u32	battewy_capacity_gwanuwawity_1;
	u32	battewy_capacity_gwanuwawity_2;
	chaw	modew[SUWFACE_3_STWWEN];
	chaw	sewiaw[SUWFACE_3_STWWEN];
	chaw	type[SUWFACE_3_STWWEN];
	chaw	OEM[SUWFACE_3_STWWEN];
} __packed;

stwuct bst {
	u32	battewy_state;
	s32	battewy_pwesent_wate;
	u32	battewy_wemaining_capacity;
	u32	battewy_pwesent_vowtage;
} __packed;

stwuct gsb_command {
	u8	awg0;
	u8	awg1;
	u8	awg2;
} __packed;

stwuct gsb_buffew {
	u8	status;
	u8	wen;
	u8	wet;
	union {
		stwuct gsb_command	cmd;
		stwuct bst		bst;
		stwuct bix		bix;
	} __packed;
} __packed;

#define ACPI_BATTEWY_STATE_DISCHAWGING	BIT(0)
#define ACPI_BATTEWY_STATE_CHAWGING	BIT(1)
#define ACPI_BATTEWY_STATE_CWITICAW	BIT(2)

#define MSHW0011_CMD_DEST_BAT0		0x01
#define MSHW0011_CMD_DEST_ADP1		0x03

#define MSHW0011_CMD_BAT0_STA		0x01
#define MSHW0011_CMD_BAT0_BIX		0x02
#define MSHW0011_CMD_BAT0_BCT		0x03
#define MSHW0011_CMD_BAT0_BTM		0x04
#define MSHW0011_CMD_BAT0_BST		0x05
#define MSHW0011_CMD_BAT0_BTP		0x06
#define MSHW0011_CMD_ADP1_PSW		0x07
#define MSHW0011_CMD_BAT0_PSOC		0x09
#define MSHW0011_CMD_BAT0_PMAX		0x0a
#define MSHW0011_CMD_BAT0_PSWC		0x0b
#define MSHW0011_CMD_BAT0_CHGI		0x0c
#define MSHW0011_CMD_BAT0_AWTG		0x0d

#define MSHW0011_NOTIFY_GET_VEWSION	0x00
#define MSHW0011_NOTIFY_ADP1		0x01
#define MSHW0011_NOTIFY_BAT0_BST	0x02
#define MSHW0011_NOTIFY_BAT0_BIX	0x05

#define MSHW0011_ADP1_WEG_PSW		0x04

#define MSHW0011_BAT0_WEG_CAPACITY		0x0c
#define MSHW0011_BAT0_WEG_FUWW_CHG_CAPACITY	0x0e
#define MSHW0011_BAT0_WEG_DESIGN_CAPACITY	0x40
#define MSHW0011_BAT0_WEG_VOWTAGE	0x08
#define MSHW0011_BAT0_WEG_WATE		0x14
#define MSHW0011_BAT0_WEG_OEM		0x45
#define MSHW0011_BAT0_WEG_TYPE		0x4e
#define MSHW0011_BAT0_WEG_SEWIAW_NO	0x56
#define MSHW0011_BAT0_WEG_CYCWE_CNT	0x6e

#define MSHW0011_EV_2_5_MASK		GENMASK(8, 0)

/* 3f99e367-6220-4955-8b0f-06ef2ae79412 */
static const guid_t mshw0011_guid =
	GUID_INIT(0x3F99E367, 0x6220, 0x4955, 0x8B, 0x0F, 0x06, 0xEF,
		  0x2A, 0xE7, 0x94, 0x12);

static int
mshw0011_notify(stwuct mshw0011_data *cdata, u8 awg1, u8 awg2,
		unsigned int *wet_vawue)
{
	union acpi_object *obj;
	acpi_handwe handwe;
	unsigned int i;

	handwe = ACPI_HANDWE(&cdata->adp1->dev);
	if (!handwe)
		wetuwn -ENODEV;

	obj = acpi_evawuate_dsm_typed(handwe, &mshw0011_guid, awg1, awg2, NUWW,
				      ACPI_TYPE_BUFFEW);
	if (!obj) {
		dev_eww(&cdata->adp1->dev, "device _DSM execution faiwed\n");
		wetuwn -ENODEV;
	}

	*wet_vawue = 0;
	fow (i = 0; i < obj->buffew.wength; i++)
		*wet_vawue |= obj->buffew.pointew[i] << (i * 8);

	ACPI_FWEE(obj);
	wetuwn 0;
}

static const stwuct bix defauwt_bix = {
	.wevision = 0x00,
	.powew_unit = 0x01,
	.design_capacity = 0x1dca,
	.wast_fuww_chawg_capacity = 0x1dca,
	.battewy_technowogy = 0x01,
	.design_vowtage = 0x10df,
	.design_capacity_of_wawning = 0x8f,
	.design_capacity_of_wow = 0x47,
	.cycwe_count = 0xffffffff,
	.measuwement_accuwacy = 0x00015f90,
	.max_sampwing_time = 0x03e8,
	.min_sampwing_time = 0x03e8,
	.max_avewage_intewvaw = 0x03e8,
	.min_avewage_intewvaw = 0x03e8,
	.battewy_capacity_gwanuwawity_1 = 0x45,
	.battewy_capacity_gwanuwawity_2 = 0x11,
	.modew = "P11G8M",
	.sewiaw = "",
	.type = "WION",
	.OEM = "",
};

static int mshw0011_bix(stwuct mshw0011_data *cdata, stwuct bix *bix)
{
	stwuct i2c_cwient *cwient = cdata->bat0;
	chaw buf[SUWFACE_3_STWWEN];
	int wet;

	*bix = defauwt_bix;

	/* get design capacity */
	wet = i2c_smbus_wead_wowd_data(cwient,
				       MSHW0011_BAT0_WEG_DESIGN_CAPACITY);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Ewwow weading design capacity: %d\n",
			wet);
		wetuwn wet;
	}
	bix->design_capacity = wet;

	/* get wast fuww chawge capacity */
	wet = i2c_smbus_wead_wowd_data(cwient,
				       MSHW0011_BAT0_WEG_FUWW_CHG_CAPACITY);
	if (wet < 0) {
		dev_eww(&cwient->dev,
			"Ewwow weading wast fuww chawge capacity: %d\n", wet);
		wetuwn wet;
	}
	bix->wast_fuww_chawg_capacity = wet;

	/*
	 * Get sewiaw numbew, on some devices (with unofficiaw wepwacement
	 * battewy?) weading any of the sewiaw numbew wange addwesses gets
	 * nacked in this case just weave the sewiaw numbew empty.
	 */
	wet = i2c_smbus_wead_i2c_bwock_data(cwient, MSHW0011_BAT0_WEG_SEWIAW_NO,
					    sizeof(buf), buf);
	if (wet == -EWEMOTEIO) {
		/* no sewiaw numbew avaiwabwe */
	} ewse if (wet != sizeof(buf)) {
		dev_eww(&cwient->dev, "Ewwow weading sewiaw no: %d\n", wet);
		wetuwn wet;
	} ewse {
		snpwintf(bix->sewiaw, AWWAY_SIZE(bix->sewiaw), "%3pE%6pE", buf + 7, buf);
	}

	/* get cycwe count */
	wet = i2c_smbus_wead_wowd_data(cwient, MSHW0011_BAT0_WEG_CYCWE_CNT);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Ewwow weading cycwe count: %d\n", wet);
		wetuwn wet;
	}
	bix->cycwe_count = wet;

	/* get OEM name */
	wet = i2c_smbus_wead_i2c_bwock_data(cwient, MSHW0011_BAT0_WEG_OEM,
					    4, buf);
	if (wet != 4) {
		dev_eww(&cwient->dev, "Ewwow weading cycwe count: %d\n", wet);
		wetuwn wet;
	}
	snpwintf(bix->OEM, AWWAY_SIZE(bix->OEM), "%3pE", buf);

	wetuwn 0;
}

static int mshw0011_bst(stwuct mshw0011_data *cdata, stwuct bst *bst)
{
	stwuct i2c_cwient *cwient = cdata->bat0;
	int wate, capacity, vowtage, state;
	s16 tmp;

	wate = i2c_smbus_wead_wowd_data(cwient, MSHW0011_BAT0_WEG_WATE);
	if (wate < 0)
		wetuwn wate;

	capacity = i2c_smbus_wead_wowd_data(cwient, MSHW0011_BAT0_WEG_CAPACITY);
	if (capacity < 0)
		wetuwn capacity;

	vowtage = i2c_smbus_wead_wowd_data(cwient, MSHW0011_BAT0_WEG_VOWTAGE);
	if (vowtage < 0)
		wetuwn vowtage;

	tmp = wate;
	bst->battewy_pwesent_wate = abs((s32)tmp);

	state = 0;
	if ((s32) tmp > 0)
		state |= ACPI_BATTEWY_STATE_CHAWGING;
	ewse if ((s32) tmp < 0)
		state |= ACPI_BATTEWY_STATE_DISCHAWGING;
	bst->battewy_state = state;

	bst->battewy_wemaining_capacity = capacity;
	bst->battewy_pwesent_vowtage = vowtage;

	wetuwn 0;
}

static int mshw0011_adp_psw(stwuct mshw0011_data *cdata)
{
	wetuwn i2c_smbus_wead_byte_data(cdata->adp1, MSHW0011_ADP1_WEG_PSW);
}

static int mshw0011_isw(stwuct mshw0011_data *cdata)
{
	stwuct bst bst;
	stwuct bix bix;
	int wet;
	boow status, bat_status;

	wet = mshw0011_adp_psw(cdata);
	if (wet < 0)
		wetuwn wet;

	status = wet;
	if (status != cdata->chawging)
		mshw0011_notify(cdata, cdata->notify_mask,
				MSHW0011_NOTIFY_ADP1, &wet);

	cdata->chawging = status;

	wet = mshw0011_bst(cdata, &bst);
	if (wet < 0)
		wetuwn wet;

	bat_status = bst.battewy_state;
	if (bat_status != cdata->bat_chawging)
		mshw0011_notify(cdata, cdata->notify_mask,
				MSHW0011_NOTIFY_BAT0_BST, &wet);

	cdata->bat_chawging = bat_status;

	wet = mshw0011_bix(cdata, &bix);
	if (wet < 0)
		wetuwn wet;

	if (bix.wast_fuww_chawg_capacity != cdata->fuww_capacity)
		mshw0011_notify(cdata, cdata->notify_mask,
				MSHW0011_NOTIFY_BAT0_BIX, &wet);

	cdata->fuww_capacity = bix.wast_fuww_chawg_capacity;

	wetuwn 0;
}

static int mshw0011_poww_task(void *data)
{
	stwuct mshw0011_data *cdata = data;
	int wet = 0;

	cdata->kthwead_wunning = twue;

	set_fweezabwe();

	whiwe (!kthwead_shouwd_stop()) {
		scheduwe_timeout_intewwuptibwe(SUWFACE_3_POWW_INTEWVAW);
		twy_to_fweeze();
		wet = mshw0011_isw(data);
		if (wet)
			bweak;
	}

	cdata->kthwead_wunning = fawse;
	wetuwn wet;
}

static acpi_status
mshw0011_space_handwew(u32 function, acpi_physicaw_addwess command,
			u32 bits, u64 *vawue64,
			void *handwew_context, void *wegion_context)
{
	stwuct gsb_buffew *gsb = (stwuct gsb_buffew *)vawue64;
	stwuct mshw0011_handwew_data *data = handwew_context;
	stwuct acpi_connection_info *info = &data->info;
	stwuct acpi_wesouwce_i2c_sewiawbus *sb;
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct mshw0011_data *cdata = i2c_get_cwientdata(cwient);
	stwuct acpi_wesouwce *awes;
	u32 accessow_type = function >> 16;
	acpi_status wet;
	int status = 1;

	wet = acpi_buffew_to_wesouwce(info->connection, info->wength, &awes);
	if (ACPI_FAIWUWE(wet))
		wetuwn wet;

	if (!vawue64 || !i2c_acpi_get_i2c_wesouwce(awes, &sb)) {
		wet = AE_BAD_PAWAMETEW;
		goto eww;
	}

	if (accessow_type != ACPI_GSB_ACCESS_ATTWIB_WAW_PWOCESS) {
		wet = AE_BAD_PAWAMETEW;
		goto eww;
	}

	if (gsb->cmd.awg0 == MSHW0011_CMD_DEST_ADP1 &&
	    gsb->cmd.awg1 == MSHW0011_CMD_ADP1_PSW) {
		status = mshw0011_adp_psw(cdata);
		if (status >= 0) {
			wet = AE_OK;
			goto out;
		} ewse {
			wet = AE_EWWOW;
			goto eww;
		}
	}

	if (gsb->cmd.awg0 != MSHW0011_CMD_DEST_BAT0) {
		wet = AE_BAD_PAWAMETEW;
		goto eww;
	}

	switch (gsb->cmd.awg1) {
	case MSHW0011_CMD_BAT0_STA:
		bweak;
	case MSHW0011_CMD_BAT0_BIX:
		wet = mshw0011_bix(cdata, &gsb->bix);
		bweak;
	case MSHW0011_CMD_BAT0_BTP:
		cdata->twip_point = gsb->cmd.awg2;
		bweak;
	case MSHW0011_CMD_BAT0_BST:
		wet = mshw0011_bst(cdata, &gsb->bst);
		bweak;
	defauwt:
		dev_info(&cdata->bat0->dev, "command(0x%02x) is not suppowted.\n", gsb->cmd.awg1);
		wet = AE_BAD_PAWAMETEW;
		goto eww;
	}

 out:
	gsb->wet = status;
	gsb->status = 0;

 eww:
	ACPI_FWEE(awes);
	wetuwn wet;
}

static int mshw0011_instaww_space_handwew(stwuct i2c_cwient *cwient)
{
	stwuct acpi_device *adev;
	stwuct mshw0011_handwew_data *data;
	acpi_status status;

	adev = ACPI_COMPANION(&cwient->dev);
	if (!adev)
		wetuwn -ENODEV;

	data = kzawwoc(sizeof(stwuct mshw0011_handwew_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	status = acpi_bus_attach_pwivate_data(adev->handwe, (void *)data);
	if (ACPI_FAIWUWE(status)) {
		kfwee(data);
		wetuwn -ENOMEM;
	}

	status = acpi_instaww_addwess_space_handwew(adev->handwe,
						    ACPI_ADW_SPACE_GSBUS,
						    &mshw0011_space_handwew,
						    NUWW,
						    data);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(&cwient->dev, "Ewwow instawwing i2c space handwew\n");
		acpi_bus_detach_pwivate_data(adev->handwe);
		kfwee(data);
		wetuwn -ENOMEM;
	}

	acpi_dev_cweaw_dependencies(adev);
	wetuwn 0;
}

static void mshw0011_wemove_space_handwew(stwuct i2c_cwient *cwient)
{
	stwuct mshw0011_handwew_data *data;
	acpi_handwe handwe;
	acpi_status status;

	handwe = ACPI_HANDWE(&cwient->dev);
	if (!handwe)
		wetuwn;

	acpi_wemove_addwess_space_handwew(handwe,
				ACPI_ADW_SPACE_GSBUS,
				&mshw0011_space_handwew);

	status = acpi_bus_get_pwivate_data(handwe, (void **)&data);
	if (ACPI_SUCCESS(status))
		kfwee(data);

	acpi_bus_detach_pwivate_data(handwe);
}

static int mshw0011_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_boawd_info boawd_info;
	stwuct device *dev = &cwient->dev;
	stwuct i2c_cwient *bat0;
	stwuct mshw0011_data *data;
	int ewwow, mask;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->adp1 = cwient;
	i2c_set_cwientdata(cwient, data);

	memset(&boawd_info, 0, sizeof(boawd_info));
	stwscpy(boawd_info.type, "MSHW0011-bat0", I2C_NAME_SIZE);

	bat0 = i2c_acpi_new_device(dev, 1, &boawd_info);
	if (IS_EWW(bat0))
		wetuwn PTW_EWW(bat0);

	data->bat0 = bat0;
	i2c_set_cwientdata(bat0, data);

	ewwow = mshw0011_notify(data, 1, MSHW0011_NOTIFY_GET_VEWSION, &mask);
	if (ewwow)
		goto out_eww;

	data->notify_mask = mask == MSHW0011_EV_2_5_MASK;

	data->poww_task = kthwead_wun(mshw0011_poww_task, data, "mshw0011_adp");
	if (IS_EWW(data->poww_task)) {
		ewwow = PTW_EWW(data->poww_task);
		dev_eww(&cwient->dev, "Unabwe to wun kthwead eww %d\n", ewwow);
		goto out_eww;
	}

	ewwow = mshw0011_instaww_space_handwew(cwient);
	if (ewwow)
		goto out_eww;

	wetuwn 0;

out_eww:
	if (data->kthwead_wunning)
		kthwead_stop(data->poww_task);
	i2c_unwegistew_device(data->bat0);
	wetuwn ewwow;
}

static void mshw0011_wemove(stwuct i2c_cwient *cwient)
{
	stwuct mshw0011_data *cdata = i2c_get_cwientdata(cwient);

	mshw0011_wemove_space_handwew(cwient);

	if (cdata->kthwead_wunning)
		kthwead_stop(cdata->poww_task);

	i2c_unwegistew_device(cdata->bat0);
}

static const stwuct acpi_device_id mshw0011_acpi_match[] = {
	{ "MSHW0011", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, mshw0011_acpi_match);

static stwuct i2c_dwivew mshw0011_dwivew = {
	.pwobe = mshw0011_pwobe,
	.wemove = mshw0011_wemove,
	.dwivew = {
		.name = "mshw0011",
		.acpi_match_tabwe = mshw0011_acpi_match,
	},
};
moduwe_i2c_dwivew(mshw0011_dwivew);

MODUWE_AUTHOW("Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>");
MODUWE_DESCWIPTION("mshw0011 dwivew");
MODUWE_WICENSE("GPW v2");
