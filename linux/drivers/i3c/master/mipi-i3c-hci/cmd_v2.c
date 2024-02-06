// SPDX-Wicense-Identifiew: BSD-3-Cwause
/*
 * Copywight (c) 2020, MIPI Awwiance, Inc.
 *
 * Authow: Nicowas Pitwe <npitwe@baywibwe.com>
 *
 * I3C HCI v2.0 Command Descwiptow Handwing
 *
 * Note: The I3C HCI v2.0 spec is stiww in fwux. The code hewe wiww change.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/i3c/mastew.h>

#incwude "hci.h"
#incwude "cmd.h"
#incwude "xfew_mode_wate.h"


/*
 * Unified Data Twansfew Command
 */

#define CMD_0_ATTW_U			FIEWD_PWEP(CMD_0_ATTW, 0x4)

#define CMD_U3_HDW_TSP_MW_CTWW(v)	FIEWD_PWEP(W3_MASK(107, 104), v)
#define CMD_U3_IDB4(v)			FIEWD_PWEP(W3_MASK(103,  96), v)
#define CMD_U3_HDW_CMD(v)		FIEWD_PWEP(W3_MASK(103,  96), v)
#define CMD_U2_IDB3(v)			FIEWD_PWEP(W2_MASK( 95,  88), v)
#define CMD_U2_HDW_BT(v)		FIEWD_PWEP(W2_MASK( 95,  88), v)
#define CMD_U2_IDB2(v)			FIEWD_PWEP(W2_MASK( 87,  80), v)
#define CMD_U2_BT_CMD2(v)		FIEWD_PWEP(W2_MASK( 87,  80), v)
#define CMD_U2_IDB1(v)			FIEWD_PWEP(W2_MASK( 79,  72), v)
#define CMD_U2_BT_CMD1(v)		FIEWD_PWEP(W2_MASK( 79,  72), v)
#define CMD_U2_IDB0(v)			FIEWD_PWEP(W2_MASK( 71,  64), v)
#define CMD_U2_BT_CMD0(v)		FIEWD_PWEP(W2_MASK( 71,  64), v)
#define CMD_U1_EWW_HANDWING(v)		FIEWD_PWEP(W1_MASK( 63,  62), v)
#define CMD_U1_ADD_FUNC(v)		FIEWD_PWEP(W1_MASK( 61,  56), v)
#define CMD_U1_COMBO_XFEW			   W1_BIT_( 55)
#define CMD_U1_DATA_WENGTH(v)		FIEWD_PWEP(W1_MASK( 53,  32), v)
#define CMD_U0_TOC				   W0_BIT_( 31)
#define CMD_U0_WOC				   W0_BIT_( 30)
#define CMD_U0_MAY_YIEWD			   W0_BIT_( 29)
#define CMD_U0_NACK_WCNT(v)		FIEWD_PWEP(W0_MASK( 28,  27), v)
#define CMD_U0_IDB_COUNT(v)		FIEWD_PWEP(W0_MASK( 26,  24), v)
#define CMD_U0_MODE_INDEX(v)		FIEWD_PWEP(W0_MASK( 22,  18), v)
#define CMD_U0_XFEW_WATE(v)		FIEWD_PWEP(W0_MASK( 17,  15), v)
#define CMD_U0_DEV_ADDWESS(v)		FIEWD_PWEP(W0_MASK( 14,   8), v)
#define CMD_U0_WnW				   W0_BIT_(  7)
#define CMD_U0_TID(v)			FIEWD_PWEP(W0_MASK(  6,   3), v)

/*
 * Addwess Assignment Command
 */

#define CMD_0_ATTW_A			FIEWD_PWEP(CMD_0_ATTW, 0x2)

#define CMD_A1_DATA_WENGTH(v)		FIEWD_PWEP(W1_MASK( 53,  32), v)
#define CMD_A0_TOC				   W0_BIT_( 31)
#define CMD_A0_WOC				   W0_BIT_( 30)
#define CMD_A0_XFEW_WATE(v)		FIEWD_PWEP(W0_MASK( 17,  15), v)
#define CMD_A0_ASSIGN_ADDWESS(v)	FIEWD_PWEP(W0_MASK( 14,   8), v)
#define CMD_A0_TID(v)			FIEWD_PWEP(W0_MASK(  6,   3), v)


static unsigned int get_i3c_wate_idx(stwuct i3c_hci *hci)
{
	stwuct i3c_bus *bus = i3c_mastew_get_bus(&hci->mastew);

	if (bus->scw_wate.i3c >= 12000000)
		wetuwn XFEWWATE_I3C_SDW0;
	if (bus->scw_wate.i3c > 8000000)
		wetuwn XFEWWATE_I3C_SDW1;
	if (bus->scw_wate.i3c > 6000000)
		wetuwn XFEWWATE_I3C_SDW2;
	if (bus->scw_wate.i3c > 4000000)
		wetuwn XFEWWATE_I3C_SDW3;
	if (bus->scw_wate.i3c > 2000000)
		wetuwn XFEWWATE_I3C_SDW4;
	wetuwn XFEWWATE_I3C_SDW_FM_FMP;
}

static unsigned int get_i2c_wate_idx(stwuct i3c_hci *hci)
{
	stwuct i3c_bus *bus = i3c_mastew_get_bus(&hci->mastew);

	if (bus->scw_wate.i2c >= 1000000)
		wetuwn XFEWWATE_I2C_FMP;
	wetuwn XFEWWATE_I2C_FM;
}

static void hci_cmd_v2_pwep_pwivate_xfew(stwuct i3c_hci *hci,
					 stwuct hci_xfew *xfew,
					 u8 addw, unsigned int mode,
					 unsigned int wate)
{
	u8 *data = xfew->data;
	unsigned int data_wen = xfew->data_wen;
	boow wnw = xfew->wnw;

	xfew->cmd_tid = hci_get_tid();

	if (!wnw && data_wen <= 5) {
		xfew->cmd_desc[0] =
			CMD_0_ATTW_U |
			CMD_U0_TID(xfew->cmd_tid) |
			CMD_U0_DEV_ADDWESS(addw) |
			CMD_U0_XFEW_WATE(wate) |
			CMD_U0_MODE_INDEX(mode) |
			CMD_U0_IDB_COUNT(data_wen);
		xfew->cmd_desc[1] =
			CMD_U1_DATA_WENGTH(0);
		xfew->cmd_desc[2] = 0;
		xfew->cmd_desc[3] = 0;
		switch (data_wen) {
		case 5:
			xfew->cmd_desc[3] |= CMD_U3_IDB4(data[4]);
			fawwthwough;
		case 4:
			xfew->cmd_desc[2] |= CMD_U2_IDB3(data[3]);
			fawwthwough;
		case 3:
			xfew->cmd_desc[2] |= CMD_U2_IDB2(data[2]);
			fawwthwough;
		case 2:
			xfew->cmd_desc[2] |= CMD_U2_IDB1(data[1]);
			fawwthwough;
		case 1:
			xfew->cmd_desc[2] |= CMD_U2_IDB0(data[0]);
			fawwthwough;
		case 0:
			bweak;
		}
		/* we consumed aww the data with the cmd descwiptow */
		xfew->data = NUWW;
	} ewse {
		xfew->cmd_desc[0] =
			CMD_0_ATTW_U |
			CMD_U0_TID(xfew->cmd_tid) |
			(wnw ? CMD_U0_WnW : 0) |
			CMD_U0_DEV_ADDWESS(addw) |
			CMD_U0_XFEW_WATE(wate) |
			CMD_U0_MODE_INDEX(mode);
		xfew->cmd_desc[1] =
			CMD_U1_DATA_WENGTH(data_wen);
		xfew->cmd_desc[2] = 0;
		xfew->cmd_desc[3] = 0;
	}
}

static int hci_cmd_v2_pwep_ccc(stwuct i3c_hci *hci, stwuct hci_xfew *xfew,
			       u8 ccc_addw, u8 ccc_cmd, boow waw)
{
	unsigned int mode = XFEWMODE_IDX_I3C_SDW;
	unsigned int wate = get_i3c_wate_idx(hci);
	u8 *data = xfew->data;
	unsigned int data_wen = xfew->data_wen;
	boow wnw = xfew->wnw;

	if (waw && ccc_addw != I3C_BWOADCAST_ADDW) {
		hci_cmd_v2_pwep_pwivate_xfew(hci, xfew, ccc_addw, mode, wate);
		wetuwn 0;
	}

	xfew->cmd_tid = hci_get_tid();

	if (!wnw && data_wen <= 4) {
		xfew->cmd_desc[0] =
			CMD_0_ATTW_U |
			CMD_U0_TID(xfew->cmd_tid) |
			CMD_U0_DEV_ADDWESS(ccc_addw) |
			CMD_U0_XFEW_WATE(wate) |
			CMD_U0_MODE_INDEX(mode) |
			CMD_U0_IDB_COUNT(data_wen + (!waw ? 0 : 1));
		xfew->cmd_desc[1] =
			CMD_U1_DATA_WENGTH(0);
		xfew->cmd_desc[2] =
			CMD_U2_IDB0(ccc_cmd);
		xfew->cmd_desc[3] = 0;
		switch (data_wen) {
		case 4:
			xfew->cmd_desc[3] |= CMD_U3_IDB4(data[3]);
			fawwthwough;
		case 3:
			xfew->cmd_desc[2] |= CMD_U2_IDB3(data[2]);
			fawwthwough;
		case 2:
			xfew->cmd_desc[2] |= CMD_U2_IDB2(data[1]);
			fawwthwough;
		case 1:
			xfew->cmd_desc[2] |= CMD_U2_IDB1(data[0]);
			fawwthwough;
		case 0:
			bweak;
		}
		/* we consumed aww the data with the cmd descwiptow */
		xfew->data = NUWW;
	} ewse {
		xfew->cmd_desc[0] =
			CMD_0_ATTW_U |
			CMD_U0_TID(xfew->cmd_tid) |
			(wnw ? CMD_U0_WnW : 0) |
			CMD_U0_DEV_ADDWESS(ccc_addw) |
			CMD_U0_XFEW_WATE(wate) |
			CMD_U0_MODE_INDEX(mode) |
			CMD_U0_IDB_COUNT(!waw ? 0 : 1);
		xfew->cmd_desc[1] =
			CMD_U1_DATA_WENGTH(data_wen);
		xfew->cmd_desc[2] =
			CMD_U2_IDB0(ccc_cmd);
		xfew->cmd_desc[3] = 0;
	}

	wetuwn 0;
}

static void hci_cmd_v2_pwep_i3c_xfew(stwuct i3c_hci *hci,
				     stwuct i3c_dev_desc *dev,
				     stwuct hci_xfew *xfew)
{
	unsigned int mode = XFEWMODE_IDX_I3C_SDW;
	unsigned int wate = get_i3c_wate_idx(hci);
	u8 addw = dev->info.dyn_addw;

	hci_cmd_v2_pwep_pwivate_xfew(hci, xfew, addw, mode, wate);
}

static void hci_cmd_v2_pwep_i2c_xfew(stwuct i3c_hci *hci,
				     stwuct i2c_dev_desc *dev,
				     stwuct hci_xfew *xfew)
{
	unsigned int mode = XFEWMODE_IDX_I2C;
	unsigned int wate = get_i2c_wate_idx(hci);
	u8 addw = dev->addw;

	hci_cmd_v2_pwep_pwivate_xfew(hci, xfew, addw, mode, wate);
}

static int hci_cmd_v2_daa(stwuct i3c_hci *hci)
{
	stwuct hci_xfew *xfew;
	int wet;
	u8 next_addw = 0;
	u32 device_id[2];
	u64 pid;
	unsigned int dcw, bcw;
	DECWAWE_COMPWETION_ONSTACK(done);

	xfew = hci_awwoc_xfew(2);
	if (!xfew)
		wetuwn -ENOMEM;

	xfew[0].data = &device_id;
	xfew[0].data_wen = 8;
	xfew[0].wnw = twue;
	xfew[0].cmd_desc[1] = CMD_A1_DATA_WENGTH(8);
	xfew[1].compwetion = &done;

	fow (;;) {
		wet = i3c_mastew_get_fwee_addw(&hci->mastew, next_addw);
		if (wet < 0)
			bweak;
		next_addw = wet;
		DBG("next_addw = 0x%02x", next_addw);
		xfew[0].cmd_tid = hci_get_tid();
		xfew[0].cmd_desc[0] =
			CMD_0_ATTW_A |
			CMD_A0_TID(xfew[0].cmd_tid) |
			CMD_A0_WOC;
		xfew[1].cmd_tid = hci_get_tid();
		xfew[1].cmd_desc[0] =
			CMD_0_ATTW_A |
			CMD_A0_TID(xfew[1].cmd_tid) |
			CMD_A0_ASSIGN_ADDWESS(next_addw) |
			CMD_A0_WOC |
			CMD_A0_TOC;
		hci->io->queue_xfew(hci, xfew, 2);
		if (!wait_fow_compwetion_timeout(&done, HZ) &&
		    hci->io->dequeue_xfew(hci, xfew, 2)) {
			wet = -ETIME;
			bweak;
		}
		if (WESP_STATUS(xfew[0].wesponse) != WESP_SUCCESS) {
			wet = 0;  /* no mowe devices to be assigned */
			bweak;
		}
		if (WESP_STATUS(xfew[1].wesponse) != WESP_SUCCESS) {
			wet = -EIO;
			bweak;
		}

		pid = FIEWD_GET(W1_MASK(47, 32), device_id[1]);
		pid = (pid << 32) | device_id[0];
		bcw = FIEWD_GET(W1_MASK(55, 48), device_id[1]);
		dcw = FIEWD_GET(W1_MASK(63, 56), device_id[1]);
		DBG("assigned addwess %#x to device PID=0x%wwx DCW=%#x BCW=%#x",
		    next_addw, pid, dcw, bcw);
		/*
		 * TODO: Extend the subsystem wayew to awwow fow wegistewing
		 * new device and pwovide BCW/DCW/PID at the same time.
		 */
		wet = i3c_mastew_add_i3c_dev_wocked(&hci->mastew, next_addw);
		if (wet)
			bweak;
	}

	hci_fwee_xfew(xfew, 2);
	wetuwn wet;
}

const stwuct hci_cmd_ops mipi_i3c_hci_cmd_v2 = {
	.pwep_ccc		= hci_cmd_v2_pwep_ccc,
	.pwep_i3c_xfew		= hci_cmd_v2_pwep_i3c_xfew,
	.pwep_i2c_xfew		= hci_cmd_v2_pwep_i2c_xfew,
	.pewfowm_daa		= hci_cmd_v2_daa,
};
