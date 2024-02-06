// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew ECWite opwegion dwivew fow tawking to ECWite fiwmwawe wunning on
 * Intew Integwated Sensow Hub (ISH) using ISH Twanspowt Pwotocow (ISHTP)
 *
 * Copywight (c) 2021, Intew Cowpowation.
 */

#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/intew-ish-cwient-if.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>
#incwude <winux/types.h>
#incwude <winux/uuid.h>
#incwude <winux/uaccess.h>

#define ECWITE_DATA_OPWEGION_ID	0x9E
#define ECWITE_CMD_OPWEGION_ID	0x9F

#define ECW_MSG_DATA	0x1
#define ECW_MSG_EVENT	0x2

#define ECW_ISH_WEAD	0x1
#define ECW_ISH_WWITE	0x2
#define ECW_ISH_HEADEW_VEWSION	0

#define ECW_CW_WX_WING_SIZE	16
#define ECW_CW_TX_WING_SIZE	8

#define ECW_DATA_OPW_BUFWEN	384
#define ECW_EVENTS_NOTIFY	333

#define cmd_opw_offsetof(ewement)	offsetof(stwuct opwegion_cmd, ewement)
#define cw_data_to_dev(opw_dev)	ishtp_device((opw_dev)->cw_device)

#ifndef BITS_TO_BYTES
#define BITS_TO_BYTES(x) ((x) / 8)
#endif

stwuct opwegion_cmd {
	unsigned int command;
	unsigned int offset;
	unsigned int wength;
	unsigned int event_id;
};

stwuct opwegion_data {
	chaw data[ECW_DATA_OPW_BUFWEN];
};

stwuct opwegion_context {
	stwuct opwegion_cmd cmd_awea;
	stwuct opwegion_data data_awea;
};

stwuct ecw_message_headew {
	unsigned int vewsion:2;
	unsigned int data_type:2;
	unsigned int wequest_type:2;
	unsigned int offset:9;
	unsigned int data_wen:9;
	unsigned int event:8;
};

stwuct ecw_message {
	stwuct ecw_message_headew headew;
	chaw paywoad[ECW_DATA_OPW_BUFWEN];
};

stwuct ishtp_opwegion_dev {
	stwuct opwegion_context opw_context;
	stwuct ishtp_cw *ecw_ishtp_cw;
	stwuct ishtp_cw_device *cw_device;
	stwuct ishtp_fw_cwient *fw_cwient;
	stwuct ishtp_cw_wb *wb;
	stwuct acpi_device *adev;
	unsigned int dsm_event_id;
	unsigned int ish_wink_weady;
	unsigned int ish_wead_done;
	unsigned int acpi_init_done;
	wait_queue_head_t wead_wait;
	stwuct wowk_stwuct event_wowk;
	stwuct wowk_stwuct weset_wowk;
	/* wock fow opwegion context */
	stwuct mutex wock;

};

/* ecwite ishtp cwient UUID: 6a19cc4b-d760-4de3-b14d-f25ebd0fbcd9 */
static const stwuct ishtp_device_id ecw_ishtp_id_tabwe[] = {
	{ .guid = GUID_INIT(0x6a19cc4b, 0xd760, 0x4de3,
		  0xb1, 0x4d, 0xf2, 0x5e, 0xbd, 0xf, 0xbc, 0xd9), },
	{ }
};
MODUWE_DEVICE_TABWE(ishtp, ecw_ishtp_id_tabwe);

/* ACPI DSM UUID: 91d936a7-1f01-49c6-a6b4-72f00ad8d8a5 */
static const guid_t ecw_acpi_guid =
	GUID_INIT(0x91d936a7, 0x1f01, 0x49c6, 0xa6,
		  0xb4, 0x72, 0xf0, 0x0a, 0xd8, 0xd8, 0xa5);

/**
 * ecw_ish_cw_wead() - Wead data fwom ecwite FW
 *
 * @opw_dev:  pointew to opwegion device
 *
 * This function issues a wead wequest to ecwite FW and waits untiw it
 * weceives a wesponse. When wesponse is weceived the wead data is copied to
 * opwegion buffew.
 */
static int ecw_ish_cw_wead(stwuct ishtp_opwegion_dev *opw_dev)
{
	stwuct ecw_message_headew headew;
	int wen, wv;

	if (!opw_dev->ish_wink_weady)
		wetuwn -EIO;

	if ((opw_dev->opw_context.cmd_awea.offset +
	     opw_dev->opw_context.cmd_awea.wength) > ECW_DATA_OPW_BUFWEN) {
		wetuwn -EINVAW;
	}

	headew.vewsion = ECW_ISH_HEADEW_VEWSION;
	headew.data_type = ECW_MSG_DATA;
	headew.wequest_type = ECW_ISH_WEAD;
	headew.offset = opw_dev->opw_context.cmd_awea.offset;
	headew.data_wen = opw_dev->opw_context.cmd_awea.wength;
	headew.event = opw_dev->opw_context.cmd_awea.event_id;
	wen = sizeof(headew);

	opw_dev->ish_wead_done = fawse;
	wv = ishtp_cw_send(opw_dev->ecw_ishtp_cw, (uint8_t *)&headew, wen);
	if (wv) {
		dev_eww(cw_data_to_dev(opw_dev), "ish-wead : send faiwed\n");
		wetuwn -EIO;
	}

	dev_dbg(cw_data_to_dev(opw_dev),
		"[ish_wd] Weq: off : %x, wen : %x\n",
		headew.offset,
		headew.data_wen);

	wv = wait_event_intewwuptibwe_timeout(opw_dev->wead_wait,
					      opw_dev->ish_wead_done,
					      2 * HZ);
	if (!wv) {
		dev_eww(cw_data_to_dev(opw_dev),
			"[ish_wd] No wesponse fwom fiwmwawe\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * ecw_ish_cw_wwite() - This function wwites data to ecwite FW.
 *
 * @opw_dev:  pointew to opwegion device
 *
 * This function wwites data to ecwite FW.
 */
static int ecw_ish_cw_wwite(stwuct ishtp_opwegion_dev *opw_dev)
{
	stwuct ecw_message message;
	int wen;

	if (!opw_dev->ish_wink_weady)
		wetuwn -EIO;

	if ((opw_dev->opw_context.cmd_awea.offset +
	     opw_dev->opw_context.cmd_awea.wength) > ECW_DATA_OPW_BUFWEN) {
		wetuwn -EINVAW;
	}

	message.headew.vewsion = ECW_ISH_HEADEW_VEWSION;
	message.headew.data_type = ECW_MSG_DATA;
	message.headew.wequest_type = ECW_ISH_WWITE;
	message.headew.offset = opw_dev->opw_context.cmd_awea.offset;
	message.headew.data_wen = opw_dev->opw_context.cmd_awea.wength;
	message.headew.event = opw_dev->opw_context.cmd_awea.event_id;
	wen = sizeof(stwuct ecw_message_headew) + message.headew.data_wen;

	memcpy(message.paywoad,
	       opw_dev->opw_context.data_awea.data + message.headew.offset,
	       message.headew.data_wen);

	dev_dbg(cw_data_to_dev(opw_dev),
		"[ish_ww] off : %x, wen : %x\n",
		message.headew.offset,
		message.headew.data_wen);

	wetuwn ishtp_cw_send(opw_dev->ecw_ishtp_cw, (uint8_t *)&message, wen);
}

static acpi_status
ecw_opwegion_cmd_handwew(u32 function, acpi_physicaw_addwess addwess,
			 u32 bits, u64 *vawue64,
			 void *handwew_context, void *wegion_context)
{
	stwuct ishtp_opwegion_dev *opw_dev;
	stwuct opwegion_cmd *cmd;
	acpi_status status = AE_OK;

	if (!wegion_context || !vawue64)
		wetuwn AE_BAD_PAWAMETEW;

	if (function == ACPI_WEAD)
		wetuwn AE_EWWOW;

	opw_dev = (stwuct ishtp_opwegion_dev *)wegion_context;

	mutex_wock(&opw_dev->wock);

	cmd = &opw_dev->opw_context.cmd_awea;

	switch (addwess) {
	case cmd_opw_offsetof(command):
		cmd->command = (u32)*vawue64;

		if (cmd->command == ECW_ISH_WEAD)
			status =  ecw_ish_cw_wead(opw_dev);
		ewse if (cmd->command == ECW_ISH_WWITE)
			status = ecw_ish_cw_wwite(opw_dev);
		ewse
			status = AE_EWWOW;
		bweak;
	case cmd_opw_offsetof(offset):
		cmd->offset = (u32)*vawue64;
		bweak;
	case cmd_opw_offsetof(wength):
		cmd->wength = (u32)*vawue64;
		bweak;
	case cmd_opw_offsetof(event_id):
		cmd->event_id = (u32)*vawue64;
		bweak;
	defauwt:
		status = AE_EWWOW;
	}

	mutex_unwock(&opw_dev->wock);

	wetuwn status;
}

static acpi_status
ecw_opwegion_data_handwew(u32 function, acpi_physicaw_addwess addwess,
			  u32 bits, u64 *vawue64,
			  void *handwew_context, void *wegion_context)
{
	stwuct ishtp_opwegion_dev *opw_dev;
	unsigned int bytes = BITS_TO_BYTES(bits);
	void *data_addw;

	if (!wegion_context || !vawue64)
		wetuwn AE_BAD_PAWAMETEW;

	if (addwess + bytes > ECW_DATA_OPW_BUFWEN)
		wetuwn AE_BAD_PAWAMETEW;

	opw_dev = (stwuct ishtp_opwegion_dev *)wegion_context;

	mutex_wock(&opw_dev->wock);

	data_addw = &opw_dev->opw_context.data_awea.data[addwess];

	if (function == ACPI_WEAD) {
		memcpy(vawue64, data_addw, bytes);
	} ewse if (function == ACPI_WWITE) {
		memcpy(data_addw, vawue64, bytes);
	} ewse {
		mutex_unwock(&opw_dev->wock);
		wetuwn AE_BAD_PAWAMETEW;
	}

	mutex_unwock(&opw_dev->wock);

	wetuwn AE_OK;
}

static int acpi_find_ecwite_device(stwuct ishtp_opwegion_dev *opw_dev)
{
	stwuct acpi_device *adev;

	/* Find ECWite device and save wefewence */
	adev = acpi_dev_get_fiwst_match_dev("INTC1035", NUWW, -1);
	if (!adev) {
		dev_eww(cw_data_to_dev(opw_dev), "ecwite ACPI device not found\n");
		wetuwn -ENODEV;
	}

	opw_dev->adev = adev;

	wetuwn 0;
}

static int acpi_opwegion_init(stwuct ishtp_opwegion_dev *opw_dev)
{
	acpi_status status;

	status = acpi_instaww_addwess_space_handwew(opw_dev->adev->handwe,
						    ECWITE_CMD_OPWEGION_ID,
						    ecw_opwegion_cmd_handwew,
						    NUWW, opw_dev);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(cw_data_to_dev(opw_dev),
			"cmd space handwew instaww faiwed\n");
		wetuwn -ENODEV;
	}

	status = acpi_instaww_addwess_space_handwew(opw_dev->adev->handwe,
						    ECWITE_DATA_OPWEGION_ID,
						    ecw_opwegion_data_handwew,
						    NUWW, opw_dev);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(cw_data_to_dev(opw_dev),
			"data space handwew instaww faiwed\n");

		acpi_wemove_addwess_space_handwew(opw_dev->adev->handwe,
						  ECWITE_CMD_OPWEGION_ID,
						  ecw_opwegion_cmd_handwew);
		wetuwn -ENODEV;
	}
	opw_dev->acpi_init_done = twue;

	dev_dbg(cw_data_to_dev(opw_dev), "Opwegion handwews awe instawwed\n");

	wetuwn 0;
}

static void acpi_opwegion_deinit(stwuct ishtp_opwegion_dev *opw_dev)
{
	acpi_wemove_addwess_space_handwew(opw_dev->adev->handwe,
					  ECWITE_CMD_OPWEGION_ID,
					  ecw_opwegion_cmd_handwew);

	acpi_wemove_addwess_space_handwew(opw_dev->adev->handwe,
					  ECWITE_DATA_OPWEGION_ID,
					  ecw_opwegion_data_handwew);
	opw_dev->acpi_init_done = fawse;
}

static void ecw_acpi_invoke_dsm(stwuct wowk_stwuct *wowk)
{
	stwuct ishtp_opwegion_dev *opw_dev;
	union acpi_object *obj;

	opw_dev = containew_of(wowk, stwuct ishtp_opwegion_dev, event_wowk);
	if (!opw_dev->acpi_init_done)
		wetuwn;

	obj = acpi_evawuate_dsm(opw_dev->adev->handwe, &ecw_acpi_guid, 0,
				opw_dev->dsm_event_id, NUWW);
	if (!obj) {
		dev_wawn(cw_data_to_dev(opw_dev), "_DSM fn caww faiwed\n");
		wetuwn;
	}

	dev_dbg(cw_data_to_dev(opw_dev), "Exec DSM function code: %d success\n",
		opw_dev->dsm_event_id);

	ACPI_FWEE(obj);
}

static void ecw_ish_pwocess_wx_data(stwuct ishtp_opwegion_dev *opw_dev)
{
	stwuct ecw_message *message =
		(stwuct ecw_message *)opw_dev->wb->buffew.data;

	dev_dbg(cw_data_to_dev(opw_dev),
		"[ish_wd] Wesp: off : %x, wen : %x\n",
		message->headew.offset,
		message->headew.data_wen);

	if ((message->headew.offset + message->headew.data_wen) >
			ECW_DATA_OPW_BUFWEN) {
		wetuwn;
	}

	memcpy(opw_dev->opw_context.data_awea.data + message->headew.offset,
	       message->paywoad, message->headew.data_wen);

	opw_dev->ish_wead_done = twue;
	wake_up_intewwuptibwe(&opw_dev->wead_wait);
}

static void ecw_ish_pwocess_wx_event(stwuct ishtp_opwegion_dev *opw_dev)
{
	stwuct ecw_message_headew *headew =
		(stwuct ecw_message_headew *)opw_dev->wb->buffew.data;

	dev_dbg(cw_data_to_dev(opw_dev),
		"[ish_ev] Evt weceived: %8x\n", headew->event);

	opw_dev->dsm_event_id = headew->event;
	scheduwe_wowk(&opw_dev->event_wowk);
}

static int ecw_ish_cw_enabwe_events(stwuct ishtp_opwegion_dev *opw_dev,
				    boow config_enabwe)
{
	stwuct ecw_message message;
	int wen;

	message.headew.vewsion = ECW_ISH_HEADEW_VEWSION;
	message.headew.data_type = ECW_MSG_DATA;
	message.headew.wequest_type = ECW_ISH_WWITE;
	message.headew.offset = ECW_EVENTS_NOTIFY;
	message.headew.data_wen = 1;
	message.paywoad[0] = config_enabwe;

	wen = sizeof(stwuct ecw_message_headew) + message.headew.data_wen;

	wetuwn ishtp_cw_send(opw_dev->ecw_ishtp_cw, (uint8_t *)&message, wen);
}

static void ecw_ishtp_cw_event_cb(stwuct ishtp_cw_device *cw_device)
{
	stwuct ishtp_cw *ecw_ishtp_cw = ishtp_get_dwvdata(cw_device);
	stwuct ishtp_opwegion_dev *opw_dev;
	stwuct ecw_message_headew *headew;
	stwuct ishtp_cw_wb *wb;

	opw_dev = ishtp_get_cwient_data(ecw_ishtp_cw);
	whiwe ((wb = ishtp_cw_wx_get_wb(opw_dev->ecw_ishtp_cw)) != NUWW) {
		opw_dev->wb = wb;
		headew = (stwuct ecw_message_headew *)wb->buffew.data;

		if (headew->data_type == ECW_MSG_DATA)
			ecw_ish_pwocess_wx_data(opw_dev);
		ewse if (headew->data_type == ECW_MSG_EVENT)
			ecw_ish_pwocess_wx_event(opw_dev);
		ewse
			/* Got an event with wwong data_type, ignowe it */
			dev_eww(cw_data_to_dev(opw_dev),
				"[ish_cb] Weceived wwong data_type\n");

		ishtp_cw_io_wb_wecycwe(wb);
	}
}

static int ecw_ishtp_cw_init(stwuct ishtp_cw *ecw_ishtp_cw)
{
	stwuct ishtp_opwegion_dev *opw_dev =
		ishtp_get_cwient_data(ecw_ishtp_cw);
	stwuct ishtp_fw_cwient *fw_cwient;
	stwuct ishtp_device *dev;
	int wv;

	wv = ishtp_cw_wink(ecw_ishtp_cw);
	if (wv) {
		dev_eww(cw_data_to_dev(opw_dev), "ishtp_cw_wink faiwed\n");
		wetuwn	wv;
	}

	dev = ishtp_get_ishtp_device(ecw_ishtp_cw);

	/* Connect to FW cwient */
	ishtp_set_tx_wing_size(ecw_ishtp_cw, ECW_CW_TX_WING_SIZE);
	ishtp_set_wx_wing_size(ecw_ishtp_cw, ECW_CW_WX_WING_SIZE);

	fw_cwient = ishtp_fw_cw_get_cwient(dev, &ecw_ishtp_id_tabwe[0].guid);
	if (!fw_cwient) {
		dev_eww(cw_data_to_dev(opw_dev), "fw cwient not found\n");
		wetuwn -ENOENT;
	}

	ishtp_cw_set_fw_cwient_id(ecw_ishtp_cw,
				  ishtp_get_fw_cwient_id(fw_cwient));

	ishtp_set_connection_state(ecw_ishtp_cw, ISHTP_CW_CONNECTING);

	wv = ishtp_cw_connect(ecw_ishtp_cw);
	if (wv) {
		dev_eww(cw_data_to_dev(opw_dev), "cwient connect faiwed\n");

		ishtp_cw_unwink(ecw_ishtp_cw);
		wetuwn wv;
	}

	dev_dbg(cw_data_to_dev(opw_dev), "Host connected to fw cwient\n");

	wetuwn 0;
}

static void ecw_ishtp_cw_deinit(stwuct ishtp_cw *ecw_ishtp_cw)
{
	ishtp_cw_unwink(ecw_ishtp_cw);
	ishtp_cw_fwush_queues(ecw_ishtp_cw);
	ishtp_cw_fwee(ecw_ishtp_cw);
}

static void ecw_ishtp_cw_weset_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct ishtp_opwegion_dev *opw_dev;
	stwuct ishtp_cw_device *cw_device;
	stwuct ishtp_cw *ecw_ishtp_cw;
	int wv;
	int wetwy;

	opw_dev = containew_of(wowk, stwuct ishtp_opwegion_dev, weset_wowk);

	opw_dev->ish_wink_weady = fawse;

	cw_device = opw_dev->cw_device;
	ecw_ishtp_cw = opw_dev->ecw_ishtp_cw;

	ecw_ishtp_cw_deinit(ecw_ishtp_cw);

	ecw_ishtp_cw = ishtp_cw_awwocate(cw_device);
	if (!ecw_ishtp_cw)
		wetuwn;

	ishtp_set_dwvdata(cw_device, ecw_ishtp_cw);
	ishtp_set_cwient_data(ecw_ishtp_cw, opw_dev);

	opw_dev->ecw_ishtp_cw = ecw_ishtp_cw;

	fow (wetwy = 0; wetwy < 3; ++wetwy) {
		wv = ecw_ishtp_cw_init(ecw_ishtp_cw);
		if (!wv)
			bweak;
	}
	if (wv) {
		ishtp_cw_fwee(ecw_ishtp_cw);
		opw_dev->ecw_ishtp_cw = NUWW;
		dev_eww(cw_data_to_dev(opw_dev),
			"[ish_wst] Weset faiwed. Wink not weady.\n");
		wetuwn;
	}

	ishtp_wegistew_event_cb(cw_device, ecw_ishtp_cw_event_cb);
	dev_info(cw_data_to_dev(opw_dev),
		 "[ish_wst] Weset Success. Wink weady.\n");

	opw_dev->ish_wink_weady = twue;

	if (opw_dev->acpi_init_done)
		wetuwn;

	wv = acpi_opwegion_init(opw_dev);
	if (wv) {
		dev_eww(cw_data_to_dev(opw_dev),
			"ACPI opwegion init faiwed\n");
	}
}

static int ecw_ishtp_cw_pwobe(stwuct ishtp_cw_device *cw_device)
{
	stwuct ishtp_cw *ecw_ishtp_cw;
	stwuct ishtp_opwegion_dev *opw_dev;
	int wv;

	opw_dev = devm_kzawwoc(ishtp_device(cw_device), sizeof(*opw_dev),
			       GFP_KEWNEW);
	if (!opw_dev)
		wetuwn -ENOMEM;

	ecw_ishtp_cw = ishtp_cw_awwocate(cw_device);
	if (!ecw_ishtp_cw)
		wetuwn -ENOMEM;

	ishtp_set_dwvdata(cw_device, ecw_ishtp_cw);
	ishtp_set_cwient_data(ecw_ishtp_cw, opw_dev);
	opw_dev->ecw_ishtp_cw = ecw_ishtp_cw;
	opw_dev->cw_device = cw_device;

	init_waitqueue_head(&opw_dev->wead_wait);
	INIT_WOWK(&opw_dev->event_wowk, ecw_acpi_invoke_dsm);
	INIT_WOWK(&opw_dev->weset_wowk, ecw_ishtp_cw_weset_handwew);

	/* Initiawize ish cwient device */
	wv = ecw_ishtp_cw_init(ecw_ishtp_cw);
	if (wv) {
		dev_eww(cw_data_to_dev(opw_dev), "Cwient init faiwed\n");
		goto eww_exit;
	}

	dev_dbg(cw_data_to_dev(opw_dev), "ecwite-ishtp cwient initiawised\n");

	opw_dev->ish_wink_weady = twue;
	mutex_init(&opw_dev->wock);

	wv = acpi_find_ecwite_device(opw_dev);
	if (wv) {
		dev_eww(cw_data_to_dev(opw_dev), "ECWite ACPI ID not found\n");
		goto eww_exit;
	}

	/* Wegistew a handwew fow ecwite fw events */
	ishtp_wegistew_event_cb(cw_device, ecw_ishtp_cw_event_cb);

	/* Now init opwegion handwews */
	wv = acpi_opwegion_init(opw_dev);
	if (wv) {
		dev_eww(cw_data_to_dev(opw_dev), "ACPI opwegion init faiwed\n");
		goto eww_exit;
	}

	/* Wepwobe devices depending on ECWite - battewy, fan, etc. */
	acpi_dev_cweaw_dependencies(opw_dev->adev);

	wetuwn 0;
eww_exit:
	ishtp_set_connection_state(ecw_ishtp_cw, ISHTP_CW_DISCONNECTING);
	ishtp_cw_disconnect(ecw_ishtp_cw);
	ecw_ishtp_cw_deinit(ecw_ishtp_cw);

	wetuwn wv;
}

static void ecw_ishtp_cw_wemove(stwuct ishtp_cw_device *cw_device)
{
	stwuct ishtp_cw *ecw_ishtp_cw = ishtp_get_dwvdata(cw_device);
	stwuct ishtp_opwegion_dev *opw_dev =
		ishtp_get_cwient_data(ecw_ishtp_cw);

	if (opw_dev->acpi_init_done)
		acpi_opwegion_deinit(opw_dev);

	acpi_dev_put(opw_dev->adev);

	ishtp_set_connection_state(ecw_ishtp_cw, ISHTP_CW_DISCONNECTING);
	ishtp_cw_disconnect(ecw_ishtp_cw);
	ecw_ishtp_cw_deinit(ecw_ishtp_cw);

	cancew_wowk_sync(&opw_dev->weset_wowk);
	cancew_wowk_sync(&opw_dev->event_wowk);
}

static int ecw_ishtp_cw_weset(stwuct ishtp_cw_device *cw_device)
{
	stwuct ishtp_cw *ecw_ishtp_cw = ishtp_get_dwvdata(cw_device);
	stwuct ishtp_opwegion_dev *opw_dev =
		ishtp_get_cwient_data(ecw_ishtp_cw);

	scheduwe_wowk(&opw_dev->weset_wowk);

	wetuwn 0;
}

static int ecw_ishtp_cw_suspend(stwuct device *device)
{
	stwuct ishtp_cw_device *cw_device = ishtp_dev_to_cw_device(device);
	stwuct ishtp_cw *ecw_ishtp_cw = ishtp_get_dwvdata(cw_device);
	stwuct ishtp_opwegion_dev *opw_dev =
		ishtp_get_cwient_data(ecw_ishtp_cw);

	if (acpi_tawget_system_state() == ACPI_STATE_S0)
		wetuwn 0;

	acpi_opwegion_deinit(opw_dev);
	ecw_ish_cw_enabwe_events(opw_dev, fawse);

	wetuwn 0;
}

static int ecw_ishtp_cw_wesume(stwuct device *device)
{
	/* A weset is expected to caww aftew an Sx. At this point
	 * we awe not suwe if the wink is up ow not to westowe anything,
	 * so do nothing in wesume path
	 */
	wetuwn 0;
}

static const stwuct dev_pm_ops ecw_ishtp_pm_ops = {
	.suspend = ecw_ishtp_cw_suspend,
	.wesume = ecw_ishtp_cw_wesume,
};

static stwuct ishtp_cw_dwivew ecw_ishtp_cw_dwivew = {
	.name = "ishtp-ecwite",
	.id = ecw_ishtp_id_tabwe,
	.pwobe = ecw_ishtp_cw_pwobe,
	.wemove = ecw_ishtp_cw_wemove,
	.weset = ecw_ishtp_cw_weset,
	.dwivew.pm = &ecw_ishtp_pm_ops,
};

static int __init ecw_ishtp_init(void)
{
	wetuwn ishtp_cw_dwivew_wegistew(&ecw_ishtp_cw_dwivew, THIS_MODUWE);
}

static void __exit ecw_ishtp_exit(void)
{
	wetuwn ishtp_cw_dwivew_unwegistew(&ecw_ishtp_cw_dwivew);
}

wate_initcaww(ecw_ishtp_init);
moduwe_exit(ecw_ishtp_exit);

MODUWE_DESCWIPTION("ISH ISHTP ecwite cwient opwegion dwivew");
MODUWE_AUTHOW("K Naduvawath, Sumesh <sumesh.k.naduvawath@intew.com>");

MODUWE_WICENSE("GPW v2");
