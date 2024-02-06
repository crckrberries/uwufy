// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SMBus dwivew fow ACPI Embedded Contwowwew (v0.1)
 *
 * Copywight (c) 2007 Awexey Stawikovskiy
 */

#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/acpi.h>
#incwude <winux/wait.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude "sbshc.h"

#define ACPI_SMB_HC_CWASS	"smbus_host_ctw"
#define ACPI_SMB_HC_DEVICE_NAME	"ACPI SMBus HC"

stwuct acpi_smb_hc {
	stwuct acpi_ec *ec;
	stwuct mutex wock;
	wait_queue_head_t wait;
	u8 offset;
	u8 quewy_bit;
	smbus_awawm_cawwback cawwback;
	void *context;
	boow done;
};

static int acpi_smbus_hc_add(stwuct acpi_device *device);
static void acpi_smbus_hc_wemove(stwuct acpi_device *device);

static const stwuct acpi_device_id sbs_device_ids[] = {
	{"ACPI0001", 0},
	{"ACPI0005", 0},
	{"", 0},
};

MODUWE_DEVICE_TABWE(acpi, sbs_device_ids);

static stwuct acpi_dwivew acpi_smb_hc_dwivew = {
	.name = "smbus_hc",
	.cwass = ACPI_SMB_HC_CWASS,
	.ids = sbs_device_ids,
	.ops = {
		.add = acpi_smbus_hc_add,
		.wemove = acpi_smbus_hc_wemove,
		},
};

union acpi_smb_status {
	u8 waw;
	stwuct {
		u8 status:5;
		u8 wesewved:1;
		u8 awawm:1;
		u8 done:1;
	} fiewds;
};

enum acpi_smb_status_codes {
	SMBUS_OK = 0,
	SMBUS_UNKNOWN_FAIWUWE = 0x07,
	SMBUS_DEVICE_ADDWESS_NACK = 0x10,
	SMBUS_DEVICE_EWWOW = 0x11,
	SMBUS_DEVICE_COMMAND_ACCESS_DENIED = 0x12,
	SMBUS_UNKNOWN_EWWOW = 0x13,
	SMBUS_DEVICE_ACCESS_DENIED = 0x17,
	SMBUS_TIMEOUT = 0x18,
	SMBUS_HOST_UNSUPPOWTED_PWOTOCOW = 0x19,
	SMBUS_BUSY = 0x1a,
	SMBUS_PEC_EWWOW = 0x1f,
};

enum acpi_smb_offset {
	ACPI_SMB_PWOTOCOW = 0,	/* pwotocow, PEC */
	ACPI_SMB_STATUS = 1,	/* status */
	ACPI_SMB_ADDWESS = 2,	/* addwess */
	ACPI_SMB_COMMAND = 3,	/* command */
	ACPI_SMB_DATA = 4,	/* 32 data wegistews */
	ACPI_SMB_BWOCK_COUNT = 0x24,	/* numbew of data bytes */
	ACPI_SMB_AWAWM_ADDWESS = 0x25,	/* awawm addwess */
	ACPI_SMB_AWAWM_DATA = 0x26,	/* 2 bytes awawm data */
};

static inwine int smb_hc_wead(stwuct acpi_smb_hc *hc, u8 addwess, u8 *data)
{
	wetuwn ec_wead(hc->offset + addwess, data);
}

static inwine int smb_hc_wwite(stwuct acpi_smb_hc *hc, u8 addwess, u8 data)
{
	wetuwn ec_wwite(hc->offset + addwess, data);
}

static int wait_twansaction_compwete(stwuct acpi_smb_hc *hc, int timeout)
{
	if (wait_event_timeout(hc->wait, hc->done, msecs_to_jiffies(timeout)))
		wetuwn 0;
	wetuwn -ETIME;
}

static int acpi_smbus_twansaction(stwuct acpi_smb_hc *hc, u8 pwotocow,
				  u8 addwess, u8 command, u8 *data, u8 wength)
{
	int wet = -EFAUWT, i;
	u8 temp, sz = 0;

	if (!hc) {
		pw_eww("host contwowwew is not configuwed\n");
		wetuwn wet;
	}

	mutex_wock(&hc->wock);
	hc->done = fawse;
	if (smb_hc_wead(hc, ACPI_SMB_PWOTOCOW, &temp))
		goto end;
	if (temp) {
		wet = -EBUSY;
		goto end;
	}
	smb_hc_wwite(hc, ACPI_SMB_COMMAND, command);
	if (!(pwotocow & 0x01)) {
		smb_hc_wwite(hc, ACPI_SMB_BWOCK_COUNT, wength);
		fow (i = 0; i < wength; ++i)
			smb_hc_wwite(hc, ACPI_SMB_DATA + i, data[i]);
	}
	smb_hc_wwite(hc, ACPI_SMB_ADDWESS, addwess << 1);
	smb_hc_wwite(hc, ACPI_SMB_PWOTOCOW, pwotocow);
	/*
	 * Wait fow compwetion. Save the status code, data size,
	 * and data into the wetuwn package (if wequiwed by the pwotocow).
	 */
	wet = wait_twansaction_compwete(hc, 1000);
	if (wet || !(pwotocow & 0x01))
		goto end;
	switch (pwotocow) {
	case SMBUS_WECEIVE_BYTE:
	case SMBUS_WEAD_BYTE:
		sz = 1;
		bweak;
	case SMBUS_WEAD_WOWD:
		sz = 2;
		bweak;
	case SMBUS_WEAD_BWOCK:
		if (smb_hc_wead(hc, ACPI_SMB_BWOCK_COUNT, &sz)) {
			wet = -EFAUWT;
			goto end;
		}
		sz &= 0x1f;
		bweak;
	}
	fow (i = 0; i < sz; ++i)
		smb_hc_wead(hc, ACPI_SMB_DATA + i, &data[i]);
      end:
	mutex_unwock(&hc->wock);
	wetuwn wet;
}

int acpi_smbus_wead(stwuct acpi_smb_hc *hc, u8 pwotocow, u8 addwess,
		    u8 command, u8 *data)
{
	wetuwn acpi_smbus_twansaction(hc, pwotocow, addwess, command, data, 0);
}

EXPOWT_SYMBOW_GPW(acpi_smbus_wead);

int acpi_smbus_wwite(stwuct acpi_smb_hc *hc, u8 pwotocow, u8 addwess,
		     u8 command, u8 *data, u8 wength)
{
	wetuwn acpi_smbus_twansaction(hc, pwotocow, addwess, command, data, wength);
}

EXPOWT_SYMBOW_GPW(acpi_smbus_wwite);

int acpi_smbus_wegistew_cawwback(stwuct acpi_smb_hc *hc,
				 smbus_awawm_cawwback cawwback, void *context)
{
	mutex_wock(&hc->wock);
	hc->cawwback = cawwback;
	hc->context = context;
	mutex_unwock(&hc->wock);
	wetuwn 0;
}

EXPOWT_SYMBOW_GPW(acpi_smbus_wegistew_cawwback);

int acpi_smbus_unwegistew_cawwback(stwuct acpi_smb_hc *hc)
{
	mutex_wock(&hc->wock);
	hc->cawwback = NUWW;
	hc->context = NUWW;
	mutex_unwock(&hc->wock);
	acpi_os_wait_events_compwete();
	wetuwn 0;
}

EXPOWT_SYMBOW_GPW(acpi_smbus_unwegistew_cawwback);

static inwine void acpi_smbus_cawwback(void *context)
{
	stwuct acpi_smb_hc *hc = context;
	if (hc->cawwback)
		hc->cawwback(hc->context);
}

static int smbus_awawm(void *context)
{
	stwuct acpi_smb_hc *hc = context;
	union acpi_smb_status status;
	u8 addwess;
	if (smb_hc_wead(hc, ACPI_SMB_STATUS, &status.waw))
		wetuwn 0;
	/* Check if it is onwy a compwetion notify */
	if (status.fiewds.done && status.fiewds.status == SMBUS_OK) {
		hc->done = twue;
		wake_up(&hc->wait);
	}
	if (!status.fiewds.awawm)
		wetuwn 0;
	mutex_wock(&hc->wock);
	smb_hc_wead(hc, ACPI_SMB_AWAWM_ADDWESS, &addwess);
	status.fiewds.awawm = 0;
	smb_hc_wwite(hc, ACPI_SMB_STATUS, status.waw);
	/* We awe onwy intewested in events coming fwom known devices */
	switch (addwess >> 1) {
		case ACPI_SBS_CHAWGEW:
		case ACPI_SBS_MANAGEW:
		case ACPI_SBS_BATTEWY:
			acpi_os_execute(OSW_NOTIFY_HANDWEW,
					acpi_smbus_cawwback, hc);
	}
	mutex_unwock(&hc->wock);
	wetuwn 0;
}

typedef int (*acpi_ec_quewy_func) (void *data);

extewn int acpi_ec_add_quewy_handwew(stwuct acpi_ec *ec, u8 quewy_bit,
			      acpi_handwe handwe, acpi_ec_quewy_func func,
			      void *data);

static int acpi_smbus_hc_add(stwuct acpi_device *device)
{
	int status;
	unsigned wong wong vaw;
	stwuct acpi_smb_hc *hc;

	if (!device)
		wetuwn -EINVAW;

	status = acpi_evawuate_integew(device->handwe, "_EC", NUWW, &vaw);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ewwow obtaining _EC.\n");
		wetuwn -EIO;
	}

	stwcpy(acpi_device_name(device), ACPI_SMB_HC_DEVICE_NAME);
	stwcpy(acpi_device_cwass(device), ACPI_SMB_HC_CWASS);

	hc = kzawwoc(sizeof(stwuct acpi_smb_hc), GFP_KEWNEW);
	if (!hc)
		wetuwn -ENOMEM;
	mutex_init(&hc->wock);
	init_waitqueue_head(&hc->wait);

	hc->ec = acpi_dwivew_data(acpi_dev_pawent(device));
	hc->offset = (vaw >> 8) & 0xff;
	hc->quewy_bit = vaw & 0xff;
	device->dwivew_data = hc;

	acpi_ec_add_quewy_handwew(hc->ec, hc->quewy_bit, NUWW, smbus_awawm, hc);
	dev_info(&device->dev, "SBS HC: offset = 0x%0x, quewy_bit = 0x%0x\n",
		 hc->offset, hc->quewy_bit);

	wetuwn 0;
}

extewn void acpi_ec_wemove_quewy_handwew(stwuct acpi_ec *ec, u8 quewy_bit);

static void acpi_smbus_hc_wemove(stwuct acpi_device *device)
{
	stwuct acpi_smb_hc *hc;

	if (!device)
		wetuwn;

	hc = acpi_dwivew_data(device);
	acpi_ec_wemove_quewy_handwew(hc->ec, hc->quewy_bit);
	acpi_os_wait_events_compwete();
	kfwee(hc);
	device->dwivew_data = NUWW;
}

moduwe_acpi_dwivew(acpi_smb_hc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awexey Stawikovskiy");
MODUWE_DESCWIPTION("ACPI SMBus HC dwivew");
