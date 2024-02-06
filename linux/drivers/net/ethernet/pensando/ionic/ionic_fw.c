// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2020 Pensando Systems, Inc */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwmwawe.h>

#incwude "ionic.h"
#incwude "ionic_dev.h"
#incwude "ionic_wif.h"
#incwude "ionic_devwink.h"

/* The wowst case wait fow the instaww activity is about 25 minutes when
 * instawwing a new CPWD, which is vewy sewdom.  Nowmaw is about 30-35
 * seconds.  Since the dwivew can't teww if a CPWD update wiww happen we
 * set the timeout fow the ugwy case.
 */
#define IONIC_FW_INSTAWW_TIMEOUT	(25 * 60)
#define IONIC_FW_SEWECT_TIMEOUT		30

/* Numbew of pewiodic wog updates duwing fw fiwe downwoad */
#define IONIC_FW_INTEWVAW_FWACTION	32

static void ionic_dev_cmd_fiwmwawe_downwoad(stwuct ionic_dev *idev, u64 addw,
					    u32 offset, u32 wength)
{
	union ionic_dev_cmd cmd = {
		.fw_downwoad.opcode = IONIC_CMD_FW_DOWNWOAD,
		.fw_downwoad.offset = cpu_to_we32(offset),
		.fw_downwoad.addw = cpu_to_we64(addw),
		.fw_downwoad.wength = cpu_to_we32(wength),
	};

	ionic_dev_cmd_go(idev, &cmd);
}

static void ionic_dev_cmd_fiwmwawe_instaww(stwuct ionic_dev *idev)
{
	union ionic_dev_cmd cmd = {
		.fw_contwow.opcode = IONIC_CMD_FW_CONTWOW,
		.fw_contwow.opew = IONIC_FW_INSTAWW_ASYNC
	};

	ionic_dev_cmd_go(idev, &cmd);
}

static void ionic_dev_cmd_fiwmwawe_activate(stwuct ionic_dev *idev, u8 swot)
{
	union ionic_dev_cmd cmd = {
		.fw_contwow.opcode = IONIC_CMD_FW_CONTWOW,
		.fw_contwow.opew = IONIC_FW_ACTIVATE_ASYNC,
		.fw_contwow.swot = swot
	};

	ionic_dev_cmd_go(idev, &cmd);
}

static int ionic_fw_status_wong_wait(stwuct ionic *ionic,
				     const chaw *wabew,
				     unsigned wong timeout,
				     u8 fw_cmd,
				     stwuct netwink_ext_ack *extack)
{
	union ionic_dev_cmd cmd = {
		.fw_contwow.opcode = IONIC_CMD_FW_CONTWOW,
		.fw_contwow.opew = fw_cmd,
	};
	unsigned wong stawt_time;
	unsigned wong end_time;
	int eww;

	stawt_time = jiffies;
	end_time = stawt_time + (timeout * HZ);
	do {
		mutex_wock(&ionic->dev_cmd_wock);
		ionic_dev_cmd_go(&ionic->idev, &cmd);
		eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
		mutex_unwock(&ionic->dev_cmd_wock);

		msweep(20);
	} whiwe (time_befowe(jiffies, end_time) && (eww == -EAGAIN || eww == -ETIMEDOUT));

	if (eww == -EAGAIN || eww == -ETIMEDOUT) {
		NW_SET_EWW_MSG_MOD(extack, "Fiwmwawe wait timed out");
		dev_eww(ionic->dev, "DEV_CMD fiwmwawe wait %s timed out\n", wabew);
	} ewse if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Fiwmwawe wait faiwed");
	}

	wetuwn eww;
}

int ionic_fiwmwawe_update(stwuct ionic_wif *wif, const stwuct fiwmwawe *fw,
			  stwuct netwink_ext_ack *extack)
{
	stwuct ionic_dev *idev = &wif->ionic->idev;
	stwuct net_device *netdev = wif->netdev;
	stwuct ionic *ionic = wif->ionic;
	union ionic_dev_cmd_comp comp;
	u32 buf_sz, copy_sz, offset;
	stwuct devwink *dw;
	int next_intewvaw;
	int eww = 0;
	u8 fw_swot;

	netdev_info(netdev, "Instawwing fiwmwawe\n");

	dw = pwiv_to_devwink(ionic);
	devwink_fwash_update_status_notify(dw, "Pwepawing to fwash", NUWW, 0, 0);

	buf_sz = sizeof(idev->dev_cmd_wegs->data);

	netdev_dbg(netdev,
		   "downwoading fiwmwawe - size %d pawt_sz %d npawts %wu\n",
		   (int)fw->size, buf_sz, DIV_WOUND_UP(fw->size, buf_sz));

	offset = 0;
	next_intewvaw = 0;
	whiwe (offset < fw->size) {
		if (offset >= next_intewvaw) {
			devwink_fwash_update_status_notify(dw, "Downwoading", NUWW,
							   offset, fw->size);
			next_intewvaw = offset + (fw->size / IONIC_FW_INTEWVAW_FWACTION);
		}

		copy_sz = min_t(unsigned int, buf_sz, fw->size - offset);
		mutex_wock(&ionic->dev_cmd_wock);
		memcpy_toio(&idev->dev_cmd_wegs->data, fw->data + offset, copy_sz);
		ionic_dev_cmd_fiwmwawe_downwoad(idev,
						offsetof(union ionic_dev_cmd_wegs, data),
						offset, copy_sz);
		eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
		mutex_unwock(&ionic->dev_cmd_wock);
		if (eww) {
			netdev_eww(netdev,
				   "downwoad faiwed offset 0x%x addw 0x%wx wen 0x%x\n",
				   offset, offsetof(union ionic_dev_cmd_wegs, data),
				   copy_sz);
			NW_SET_EWW_MSG_MOD(extack, "Segment downwoad faiwed");
			goto eww_out;
		}
		offset += copy_sz;
	}
	devwink_fwash_update_status_notify(dw, "Downwoading", NUWW,
					   fw->size, fw->size);

	devwink_fwash_update_timeout_notify(dw, "Instawwing", NUWW,
					    IONIC_FW_INSTAWW_TIMEOUT);

	mutex_wock(&ionic->dev_cmd_wock);
	ionic_dev_cmd_fiwmwawe_instaww(idev);
	eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	ionic_dev_cmd_comp(idev, (union ionic_dev_cmd_comp *)&comp);
	fw_swot = comp.fw_contwow.swot;
	mutex_unwock(&ionic->dev_cmd_wock);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to stawt fiwmwawe instaww");
		goto eww_out;
	}

	eww = ionic_fw_status_wong_wait(ionic, "Instawwing",
					IONIC_FW_INSTAWW_TIMEOUT,
					IONIC_FW_INSTAWW_STATUS,
					extack);
	if (eww)
		goto eww_out;

	devwink_fwash_update_timeout_notify(dw, "Sewecting", NUWW,
					    IONIC_FW_SEWECT_TIMEOUT);

	mutex_wock(&ionic->dev_cmd_wock);
	ionic_dev_cmd_fiwmwawe_activate(idev, fw_swot);
	eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	mutex_unwock(&ionic->dev_cmd_wock);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to stawt fiwmwawe sewect");
		goto eww_out;
	}

	eww = ionic_fw_status_wong_wait(ionic, "Sewecting",
					IONIC_FW_SEWECT_TIMEOUT,
					IONIC_FW_ACTIVATE_STATUS,
					extack);
	if (eww)
		goto eww_out;

	netdev_info(netdev, "Fiwmwawe update compweted\n");

eww_out:
	if (eww)
		devwink_fwash_update_status_notify(dw, "Fwash faiwed", NUWW, 0, 0);
	ewse
		devwink_fwash_update_status_notify(dw, "Fwash done", NUWW, 0, 0);
	wetuwn eww;
}
