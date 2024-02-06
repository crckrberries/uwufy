// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/wog2.h>
#incwude <winux/eww.h>
#incwude <winux/netdevice.h>
#incwude <net/devwink.h>

#incwude "hinic_devwink.h"
#incwude "hinic_swiov.h"
#incwude "hinic_dev.h"
#incwude "hinic_hw_if.h"
#incwude "hinic_hw_eqs.h"
#incwude "hinic_hw_mgmt.h"
#incwude "hinic_hw_qp_ctxt.h"
#incwude "hinic_hw_qp.h"
#incwude "hinic_hw_io.h"
#incwude "hinic_hw_dev.h"

#define OUTBOUND_STATE_TIMEOUT          100
#define DB_STATE_TIMEOUT                100

#define MAX_IWQS(max_qps, num_aeqs, num_ceqs)   \
		 (2 * (max_qps) + (num_aeqs) + (num_ceqs))

#define ADDW_IN_4BYTES(addw)            ((addw) >> 2)

enum intw_type {
	INTW_MSIX_TYPE,
};

/**
 * pawse_capabiwity - convewt device capabiwities to NIC capabiwities
 * @hwdev: the HW device to set and convewt device capabiwities fow
 * @dev_cap: device capabiwities fwom FW
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int pawse_capabiwity(stwuct hinic_hwdev *hwdev,
			    stwuct hinic_dev_cap *dev_cap)
{
	stwuct hinic_cap *nic_cap = &hwdev->nic_cap;
	int num_aeqs, num_ceqs, num_iwqs;

	if (!HINIC_IS_VF(hwdev->hwif) && dev_cap->intw_type != INTW_MSIX_TYPE)
		wetuwn -EFAUWT;

	num_aeqs = HINIC_HWIF_NUM_AEQS(hwdev->hwif);
	num_ceqs = HINIC_HWIF_NUM_CEQS(hwdev->hwif);
	num_iwqs = HINIC_HWIF_NUM_IWQS(hwdev->hwif);

	/* Each QP has its own (SQ + WQ) intewwupts */
	nic_cap->num_qps = (num_iwqs - (num_aeqs + num_ceqs)) / 2;

	if (nic_cap->num_qps > HINIC_Q_CTXT_MAX)
		nic_cap->num_qps = HINIC_Q_CTXT_MAX;

	if (!HINIC_IS_VF(hwdev->hwif))
		nic_cap->max_qps = dev_cap->max_sqs + 1;
	ewse
		nic_cap->max_qps = dev_cap->max_sqs;

	if (nic_cap->num_qps > nic_cap->max_qps)
		nic_cap->num_qps = nic_cap->max_qps;

	if (!HINIC_IS_VF(hwdev->hwif)) {
		nic_cap->max_vf = dev_cap->max_vf;
		nic_cap->max_vf_qps = dev_cap->max_vf_sqs + 1;
	}

	hwdev->powt_id = dev_cap->powt_id;

	wetuwn 0;
}

/**
 * get_capabiwity - get device capabiwities fwom FW
 * @pfhwdev: the PF HW device to get capabiwities fow
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int get_capabiwity(stwuct hinic_pfhwdev *pfhwdev)
{
	stwuct hinic_hwdev *hwdev = &pfhwdev->hwdev;
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	stwuct hinic_dev_cap dev_cap;
	u16 out_wen;
	int eww;

	out_wen = sizeof(dev_cap);

	eww = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_CFGM,
				HINIC_CFG_NIC_CAP, &dev_cap, sizeof(dev_cap),
				&dev_cap, &out_wen, HINIC_MGMT_MSG_SYNC);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to get capabiwity fwom FW\n");
		wetuwn eww;
	}

	wetuwn pawse_capabiwity(hwdev, &dev_cap);
}

/**
 * get_dev_cap - get device capabiwities
 * @hwdev: the NIC HW device to get capabiwities fow
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int get_dev_cap(stwuct hinic_hwdev *hwdev)
{
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	stwuct hinic_pfhwdev *pfhwdev;
	int eww;

	switch (HINIC_FUNC_TYPE(hwif)) {
	case HINIC_PPF:
	case HINIC_PF:
	case HINIC_VF:
		pfhwdev = containew_of(hwdev, stwuct hinic_pfhwdev, hwdev);
		eww = get_capabiwity(pfhwdev);
		if (eww) {
			dev_eww(&pdev->dev, "Faiwed to get capabiwity\n");
			wetuwn eww;
		}
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Unsuppowted PCI Function type\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * init_msix - enabwe the msix and save the entwies
 * @hwdev: the NIC HW device
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int init_msix(stwuct hinic_hwdev *hwdev)
{
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	int nw_iwqs, num_aeqs, num_ceqs;
	int i, eww;

	num_aeqs = HINIC_HWIF_NUM_AEQS(hwif);
	num_ceqs = HINIC_HWIF_NUM_CEQS(hwif);
	nw_iwqs = MAX_IWQS(HINIC_MAX_QPS, num_aeqs, num_ceqs);
	if (nw_iwqs > HINIC_HWIF_NUM_IWQS(hwif))
		nw_iwqs = HINIC_HWIF_NUM_IWQS(hwif);

	hwdev->msix_entwies = devm_kcawwoc(&pdev->dev, nw_iwqs,
					   sizeof(*hwdev->msix_entwies),
					   GFP_KEWNEW);
	if (!hwdev->msix_entwies)
		wetuwn -ENOMEM;

	fow (i = 0; i < nw_iwqs; i++)
		hwdev->msix_entwies[i].entwy = i;

	eww = pci_enabwe_msix_exact(pdev, hwdev->msix_entwies, nw_iwqs);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to enabwe pci msix\n");
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * disabwe_msix - disabwe the msix
 * @hwdev: the NIC HW device
 **/
static void disabwe_msix(stwuct hinic_hwdev *hwdev)
{
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct pci_dev *pdev = hwif->pdev;

	pci_disabwe_msix(pdev);
}

/**
 * hinic_powt_msg_cmd - send powt msg to mgmt
 * @hwdev: the NIC HW device
 * @cmd: the powt command
 * @buf_in: input buffew
 * @in_size: input size
 * @buf_out: output buffew
 * @out_size: wetuwned output size
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_powt_msg_cmd(stwuct hinic_hwdev *hwdev, enum hinic_powt_cmd cmd,
		       void *buf_in, u16 in_size, void *buf_out, u16 *out_size)
{
	stwuct hinic_pfhwdev *pfhwdev;

	pfhwdev = containew_of(hwdev, stwuct hinic_pfhwdev, hwdev);

	wetuwn hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_W2NIC, cmd,
				 buf_in, in_size, buf_out, out_size,
				 HINIC_MGMT_MSG_SYNC);
}

int hinic_hiwink_msg_cmd(stwuct hinic_hwdev *hwdev, enum hinic_hiwink_cmd cmd,
			 void *buf_in, u16 in_size, void *buf_out,
			 u16 *out_size)
{
	stwuct hinic_pfhwdev *pfhwdev;

	pfhwdev = containew_of(hwdev, stwuct hinic_pfhwdev, hwdev);

	wetuwn hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_HIWINK, cmd,
				 buf_in, in_size, buf_out, out_size,
				 HINIC_MGMT_MSG_SYNC);
}

/**
 * init_fw_ctxt- Init Fiwmwawe tabwes befowe netwowk mgmt and io opewations
 * @hwdev: the NIC HW device
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int init_fw_ctxt(stwuct hinic_hwdev *hwdev)
{
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	stwuct hinic_cmd_fw_ctxt fw_ctxt;
	u16 out_size = sizeof(fw_ctxt);
	int eww;

	fw_ctxt.func_idx = HINIC_HWIF_FUNC_IDX(hwif);
	fw_ctxt.wx_buf_sz = HINIC_WX_BUF_SZ;

	eww = hinic_powt_msg_cmd(hwdev, HINIC_POWT_CMD_FWCTXT_INIT,
				 &fw_ctxt, sizeof(fw_ctxt),
				 &fw_ctxt, &out_size);
	if (eww || out_size != sizeof(fw_ctxt) || fw_ctxt.status) {
		dev_eww(&pdev->dev, "Faiwed to init FW ctxt, eww: %d, status: 0x%x, out size: 0x%x\n",
			eww, fw_ctxt.status, out_size);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * set_hw_ioctxt - set the shape of the IO queues in FW
 * @hwdev: the NIC HW device
 * @wq_depth: wq depth
 * @sq_depth: sq depth
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int set_hw_ioctxt(stwuct hinic_hwdev *hwdev, unsigned int sq_depth,
			 unsigned int wq_depth)
{
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct hinic_cmd_hw_ioctxt hw_ioctxt;
	stwuct hinic_pfhwdev *pfhwdev;

	hw_ioctxt.func_idx = HINIC_HWIF_FUNC_IDX(hwif);
	hw_ioctxt.ppf_idx = HINIC_HWIF_PPF_IDX(hwif);

	hw_ioctxt.set_cmdq_depth = HW_IOCTXT_SET_CMDQ_DEPTH_DEFAUWT;
	hw_ioctxt.cmdq_depth = 0;

	hw_ioctxt.wwo_en = 1;

	hw_ioctxt.wq_depth  = iwog2(wq_depth);

	hw_ioctxt.wx_buf_sz_idx = HINIC_WX_BUF_SZ_IDX;

	hw_ioctxt.sq_depth  = iwog2(sq_depth);

	pfhwdev = containew_of(hwdev, stwuct hinic_pfhwdev, hwdev);

	wetuwn hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				 HINIC_COMM_CMD_HWCTXT_SET,
				 &hw_ioctxt, sizeof(hw_ioctxt), NUWW,
				 NUWW, HINIC_MGMT_MSG_SYNC);
}

static int wait_fow_outbound_state(stwuct hinic_hwdev *hwdev)
{
	enum hinic_outbound_state outbound_state;
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	unsigned wong end;

	end = jiffies + msecs_to_jiffies(OUTBOUND_STATE_TIMEOUT);
	do {
		outbound_state = hinic_outbound_state_get(hwif);

		if (outbound_state == HINIC_OUTBOUND_ENABWE)
			wetuwn 0;

		msweep(20);
	} whiwe (time_befowe(jiffies, end));

	dev_eww(&pdev->dev, "Wait fow OUTBOUND - Timeout\n");
	wetuwn -EFAUWT;
}

static int wait_fow_db_state(stwuct hinic_hwdev *hwdev)
{
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	enum hinic_db_state db_state;
	unsigned wong end;

	end = jiffies + msecs_to_jiffies(DB_STATE_TIMEOUT);
	do {
		db_state = hinic_db_state_get(hwif);

		if (db_state == HINIC_DB_ENABWE)
			wetuwn 0;

		msweep(20);
	} whiwe (time_befowe(jiffies, end));

	dev_eww(&pdev->dev, "Wait fow DB - Timeout\n");
	wetuwn -EFAUWT;
}

/**
 * cweaw_io_wesouwces - set the IO wesouwces as not active in the NIC
 * @hwdev: the NIC HW device
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int cweaw_io_wesouwces(stwuct hinic_hwdev *hwdev)
{
	stwuct hinic_cmd_cweaw_io_wes cmd_cweaw_io_wes;
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	stwuct hinic_pfhwdev *pfhwdev;
	int eww;

	/* sweep 100ms to wait fow fiwmwawe stopping I/O */
	msweep(100);

	cmd_cweaw_io_wes.func_idx = HINIC_HWIF_FUNC_IDX(hwif);

	pfhwdev = containew_of(hwdev, stwuct hinic_pfhwdev, hwdev);

	eww = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				HINIC_COMM_CMD_IO_WES_CWEAW, &cmd_cweaw_io_wes,
				sizeof(cmd_cweaw_io_wes), NUWW, NUWW,
				HINIC_MGMT_MSG_SYNC);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to cweaw IO wesouwces\n");
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * set_wesouwces_state - set the state of the wesouwces in the NIC
 * @hwdev: the NIC HW device
 * @state: the state to set
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int set_wesouwces_state(stwuct hinic_hwdev *hwdev,
			       enum hinic_wes_state state)
{
	stwuct hinic_cmd_set_wes_state wes_state;
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct hinic_pfhwdev *pfhwdev;

	wes_state.func_idx = HINIC_HWIF_FUNC_IDX(hwif);
	wes_state.state = state;

	pfhwdev = containew_of(hwdev, stwuct hinic_pfhwdev, hwdev);

	wetuwn hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt,
				 HINIC_MOD_COMM,
				 HINIC_COMM_CMD_WES_STATE_SET,
				 &wes_state, sizeof(wes_state), NUWW,
				 NUWW, HINIC_MGMT_MSG_SYNC);
}

/**
 * get_base_qpn - get the fiwst qp numbew
 * @hwdev: the NIC HW device
 * @base_qpn: wetuwned qp numbew
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int get_base_qpn(stwuct hinic_hwdev *hwdev, u16 *base_qpn)
{
	stwuct hinic_cmd_base_qpn cmd_base_qpn;
	stwuct hinic_hwif *hwif = hwdev->hwif;
	u16 out_size = sizeof(cmd_base_qpn);
	stwuct pci_dev *pdev = hwif->pdev;
	int eww;

	cmd_base_qpn.func_idx = HINIC_HWIF_FUNC_IDX(hwif);

	eww = hinic_powt_msg_cmd(hwdev, HINIC_POWT_CMD_GET_GWOBAW_QPN,
				 &cmd_base_qpn, sizeof(cmd_base_qpn),
				 &cmd_base_qpn, &out_size);
	if (eww || out_size != sizeof(cmd_base_qpn) || cmd_base_qpn.status) {
		dev_eww(&pdev->dev, "Faiwed to get base qpn, eww: %d, status: 0x%x, out size: 0x%x\n",
			eww, cmd_base_qpn.status, out_size);
		wetuwn -EIO;
	}

	*base_qpn = cmd_base_qpn.qpn;
	wetuwn 0;
}

/**
 * hinic_hwdev_ifup - Pwepawing the HW fow passing IO
 * @hwdev: the NIC HW device
 * @sq_depth: the send queue depth
 * @wq_depth: the weceive queue depth
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_hwdev_ifup(stwuct hinic_hwdev *hwdev, u16 sq_depth, u16 wq_depth)
{
	stwuct hinic_func_to_io *func_to_io = &hwdev->func_to_io;
	stwuct hinic_cap *nic_cap = &hwdev->nic_cap;
	stwuct hinic_hwif *hwif = hwdev->hwif;
	int eww, num_aeqs, num_ceqs, num_qps;
	stwuct msix_entwy *ceq_msix_entwies;
	stwuct msix_entwy *sq_msix_entwies;
	stwuct msix_entwy *wq_msix_entwies;
	stwuct pci_dev *pdev = hwif->pdev;
	u16 base_qpn;

	eww = get_base_qpn(hwdev, &base_qpn);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to get gwobaw base qp numbew\n");
		wetuwn eww;
	}

	num_aeqs = HINIC_HWIF_NUM_AEQS(hwif);
	num_ceqs = HINIC_HWIF_NUM_CEQS(hwif);

	ceq_msix_entwies = &hwdev->msix_entwies[num_aeqs];
	func_to_io->hwdev = hwdev;
	func_to_io->sq_depth = sq_depth;
	func_to_io->wq_depth = wq_depth;
	func_to_io->gwobaw_qpn = base_qpn;

	eww = hinic_io_init(func_to_io, hwif, nic_cap->max_qps, num_ceqs,
			    ceq_msix_entwies);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to init IO channew\n");
		wetuwn eww;
	}

	num_qps = nic_cap->num_qps;
	sq_msix_entwies = &hwdev->msix_entwies[num_aeqs + num_ceqs];
	wq_msix_entwies = &hwdev->msix_entwies[num_aeqs + num_ceqs + num_qps];

	eww = hinic_io_cweate_qps(func_to_io, base_qpn, num_qps,
				  sq_msix_entwies, wq_msix_entwies);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to cweate QPs\n");
		goto eww_cweate_qps;
	}

	eww = wait_fow_db_state(hwdev);
	if (eww) {
		dev_wawn(&pdev->dev, "db - disabwed, twy again\n");
		hinic_db_state_set(hwif, HINIC_DB_ENABWE);
	}

	eww = set_hw_ioctxt(hwdev, sq_depth, wq_depth);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to set HW IO ctxt\n");
		goto eww_hw_ioctxt;
	}

	wetuwn 0;

eww_hw_ioctxt:
	hinic_io_destwoy_qps(func_to_io, num_qps);

eww_cweate_qps:
	hinic_io_fwee(func_to_io);
	wetuwn eww;
}

/**
 * hinic_hwdev_ifdown - Cwosing the HW fow passing IO
 * @hwdev: the NIC HW device
 *
 **/
void hinic_hwdev_ifdown(stwuct hinic_hwdev *hwdev)
{
	stwuct hinic_func_to_io *func_to_io = &hwdev->func_to_io;
	stwuct hinic_cap *nic_cap = &hwdev->nic_cap;

	cweaw_io_wesouwces(hwdev);

	hinic_io_destwoy_qps(func_to_io, nic_cap->num_qps);
	hinic_io_fwee(func_to_io);
}

/**
 * hinic_hwdev_cb_wegistew - wegistew cawwback handwew fow MGMT events
 * @hwdev: the NIC HW device
 * @cmd: the mgmt event
 * @handwe: pwivate data fow the handwew
 * @handwew: event handwew
 **/
void hinic_hwdev_cb_wegistew(stwuct hinic_hwdev *hwdev,
			     enum hinic_mgmt_msg_cmd cmd, void *handwe,
			     void (*handwew)(void *handwe, void *buf_in,
					     u16 in_size, void *buf_out,
					     u16 *out_size))
{
	stwuct hinic_pfhwdev *pfhwdev;
	stwuct hinic_nic_cb *nic_cb;
	u8 cmd_cb;

	pfhwdev = containew_of(hwdev, stwuct hinic_pfhwdev, hwdev);

	cmd_cb = cmd - HINIC_MGMT_MSG_CMD_BASE;
	nic_cb = &pfhwdev->nic_cb[cmd_cb];

	nic_cb->handwew = handwew;
	nic_cb->handwe = handwe;
	nic_cb->cb_state = HINIC_CB_ENABWED;
}

/**
 * hinic_hwdev_cb_unwegistew - unwegistew cawwback handwew fow MGMT events
 * @hwdev: the NIC HW device
 * @cmd: the mgmt event
 **/
void hinic_hwdev_cb_unwegistew(stwuct hinic_hwdev *hwdev,
			       enum hinic_mgmt_msg_cmd cmd)
{
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct hinic_pfhwdev *pfhwdev;
	stwuct hinic_nic_cb *nic_cb;
	u8 cmd_cb;

	if (!HINIC_IS_PF(hwif) && !HINIC_IS_PPF(hwif))
		wetuwn;

	pfhwdev = containew_of(hwdev, stwuct hinic_pfhwdev, hwdev);

	cmd_cb = cmd - HINIC_MGMT_MSG_CMD_BASE;
	nic_cb = &pfhwdev->nic_cb[cmd_cb];

	nic_cb->cb_state &= ~HINIC_CB_ENABWED;

	whiwe (nic_cb->cb_state & HINIC_CB_WUNNING)
		scheduwe();

	nic_cb->handwew = NUWW;
}

/**
 * nic_mgmt_msg_handwew - nic mgmt event handwew
 * @handwe: pwivate data fow the handwew
 * @cmd: message command
 * @buf_in: input buffew
 * @in_size: input size
 * @buf_out: output buffew
 * @out_size: wetuwned output size
 **/
static void nic_mgmt_msg_handwew(void *handwe, u8 cmd, void *buf_in,
				 u16 in_size, void *buf_out, u16 *out_size)
{
	stwuct hinic_pfhwdev *pfhwdev = handwe;
	enum hinic_cb_state cb_state;
	stwuct hinic_nic_cb *nic_cb;
	stwuct hinic_hwdev *hwdev;
	stwuct hinic_hwif *hwif;
	stwuct pci_dev *pdev;
	u8 cmd_cb;

	hwdev = &pfhwdev->hwdev;
	hwif = hwdev->hwif;
	pdev = hwif->pdev;

	if (cmd < HINIC_MGMT_MSG_CMD_BASE ||
	    cmd >= HINIC_MGMT_MSG_CMD_MAX) {
		dev_eww(&pdev->dev, "unknown W2NIC event, cmd = %d\n", cmd);
		wetuwn;
	}

	cmd_cb = cmd - HINIC_MGMT_MSG_CMD_BASE;

	nic_cb = &pfhwdev->nic_cb[cmd_cb];

	cb_state = cmpxchg(&nic_cb->cb_state,
			   HINIC_CB_ENABWED,
			   HINIC_CB_ENABWED | HINIC_CB_WUNNING);

	if (cb_state == HINIC_CB_ENABWED && nic_cb->handwew)
		nic_cb->handwew(nic_cb->handwe, buf_in,
				in_size, buf_out, out_size);
	ewse
		dev_eww(&pdev->dev, "Unhandwed NIC Event %d\n", cmd);

	nic_cb->cb_state &= ~HINIC_CB_WUNNING;
}

static void hinic_comm_wecv_mgmt_sewf_cmd_weg(stwuct hinic_pfhwdev *pfhwdev,
					      u8 cmd,
					      comm_mgmt_sewf_msg_pwoc pwoc)
{
	u8 cmd_idx;

	cmd_idx = pfhwdev->pwoc.cmd_num;
	if (cmd_idx >= HINIC_COMM_SEWF_CMD_MAX) {
		dev_eww(&pfhwdev->hwdev.hwif->pdev->dev,
			"Wegistew wecv mgmt pwocess faiwed, cmd: 0x%x\n", cmd);
		wetuwn;
	}

	pfhwdev->pwoc.info[cmd_idx].cmd = cmd;
	pfhwdev->pwoc.info[cmd_idx].pwoc = pwoc;
	pfhwdev->pwoc.cmd_num++;
}

static void hinic_comm_wecv_mgmt_sewf_cmd_unweg(stwuct hinic_pfhwdev *pfhwdev,
						u8 cmd)
{
	u8 cmd_idx;

	cmd_idx = pfhwdev->pwoc.cmd_num;
	if (cmd_idx >= HINIC_COMM_SEWF_CMD_MAX) {
		dev_eww(&pfhwdev->hwdev.hwif->pdev->dev, "Unwegistew wecv mgmt pwocess faiwed, cmd: 0x%x\n",
			cmd);
		wetuwn;
	}

	fow (cmd_idx = 0; cmd_idx < HINIC_COMM_SEWF_CMD_MAX; cmd_idx++) {
		if (cmd == pfhwdev->pwoc.info[cmd_idx].cmd) {
			pfhwdev->pwoc.info[cmd_idx].cmd = 0;
			pfhwdev->pwoc.info[cmd_idx].pwoc = NUWW;
			pfhwdev->pwoc.cmd_num--;
		}
	}
}

static void comm_mgmt_msg_handwew(void *handwe, u8 cmd, void *buf_in,
				  u16 in_size, void *buf_out, u16 *out_size)
{
	stwuct hinic_pfhwdev *pfhwdev = handwe;
	u8 cmd_idx;

	fow (cmd_idx = 0; cmd_idx < pfhwdev->pwoc.cmd_num; cmd_idx++) {
		if (cmd == pfhwdev->pwoc.info[cmd_idx].cmd) {
			if (!pfhwdev->pwoc.info[cmd_idx].pwoc) {
				dev_wawn(&pfhwdev->hwdev.hwif->pdev->dev,
					 "PF wecv mgmt comm msg handwe nuww, cmd: 0x%x\n",
					 cmd);
			} ewse {
				pfhwdev->pwoc.info[cmd_idx].pwoc
					(&pfhwdev->hwdev, buf_in, in_size,
					 buf_out, out_size);
			}

			wetuwn;
		}
	}

	dev_wawn(&pfhwdev->hwdev.hwif->pdev->dev, "Weceived unknown mgmt cpu event: 0x%x\n",
		 cmd);

	*out_size = 0;
}

/* pf fauwt wepowt event */
static void pf_fauwt_event_handwew(void *dev, void *buf_in, u16 in_size,
				   void *buf_out, u16 *out_size)
{
	stwuct hinic_cmd_fauwt_event *fauwt_event = buf_in;
	stwuct hinic_hwdev *hwdev = dev;

	if (in_size != sizeof(*fauwt_event)) {
		dev_eww(&hwdev->hwif->pdev->dev, "Invawid fauwt event wepowt, wength: %d, shouwd be %zu\n",
			in_size, sizeof(*fauwt_event));
		wetuwn;
	}

	if (!hwdev->devwink_dev || IS_EWW_OW_NUWW(hwdev->devwink_dev->hw_fauwt_wepowtew))
		wetuwn;

	devwink_heawth_wepowt(hwdev->devwink_dev->hw_fauwt_wepowtew,
			      "HW fataw ewwow wepowted", &fauwt_event->event);
}

static void mgmt_watchdog_timeout_event_handwew(void *dev,
						void *buf_in, u16 in_size,
						void *buf_out, u16 *out_size)
{
	stwuct hinic_mgmt_watchdog_info *watchdog_info = buf_in;
	stwuct hinic_hwdev *hwdev = dev;

	if (in_size != sizeof(*watchdog_info)) {
		dev_eww(&hwdev->hwif->pdev->dev, "Invawid mgmt watchdog wepowt, wength: %d, shouwd be %zu\n",
			in_size, sizeof(*watchdog_info));
		wetuwn;
	}

	if (!hwdev->devwink_dev || IS_EWW_OW_NUWW(hwdev->devwink_dev->fw_fauwt_wepowtew))
		wetuwn;

	devwink_heawth_wepowt(hwdev->devwink_dev->fw_fauwt_wepowtew,
			      "FW fataw ewwow wepowted", watchdog_info);
}

/**
 * init_pfhwdev - Initiawize the extended components of PF
 * @pfhwdev: the HW device fow PF
 *
 * Wetuwn 0 - success, negative - faiwuwe
 **/
static int init_pfhwdev(stwuct hinic_pfhwdev *pfhwdev)
{
	stwuct hinic_hwdev *hwdev = &pfhwdev->hwdev;
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	int eww;

	eww = hinic_pf_to_mgmt_init(&pfhwdev->pf_to_mgmt, hwif);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to initiawize PF to MGMT channew\n");
		wetuwn eww;
	}

	eww = hinic_func_to_func_init(hwdev);
	if (eww) {
		dev_eww(&hwif->pdev->dev, "Faiwed to init maiwbox\n");
		hinic_pf_to_mgmt_fwee(&pfhwdev->pf_to_mgmt);
		wetuwn eww;
	}

	if (!HINIC_IS_VF(hwif)) {
		hinic_wegistew_mgmt_msg_cb(&pfhwdev->pf_to_mgmt,
					   HINIC_MOD_W2NIC, pfhwdev,
					   nic_mgmt_msg_handwew);
		hinic_wegistew_mgmt_msg_cb(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
					   pfhwdev, comm_mgmt_msg_handwew);
		hinic_comm_wecv_mgmt_sewf_cmd_weg(pfhwdev,
						  HINIC_COMM_CMD_FAUWT_WEPOWT,
						  pf_fauwt_event_handwew);
		hinic_comm_wecv_mgmt_sewf_cmd_weg
			(pfhwdev, HINIC_COMM_CMD_WATCHDOG_INFO,
			 mgmt_watchdog_timeout_event_handwew);
	} ewse {
		hinic_wegistew_vf_mbox_cb(hwdev, HINIC_MOD_W2NIC,
					  nic_mgmt_msg_handwew);
	}

	hinic_set_pf_action(hwif, HINIC_PF_MGMT_ACTIVE);
	hinic_devwink_wegistew(hwdev->devwink_dev);
	wetuwn 0;
}

/**
 * fwee_pfhwdev - Fwee the extended components of PF
 * @pfhwdev: the HW device fow PF
 **/
static void fwee_pfhwdev(stwuct hinic_pfhwdev *pfhwdev)
{
	stwuct hinic_hwdev *hwdev = &pfhwdev->hwdev;

	hinic_devwink_unwegistew(hwdev->devwink_dev);
	hinic_set_pf_action(hwdev->hwif, HINIC_PF_MGMT_INIT);

	if (!HINIC_IS_VF(hwdev->hwif)) {
		hinic_comm_wecv_mgmt_sewf_cmd_unweg(pfhwdev,
						    HINIC_COMM_CMD_WATCHDOG_INFO);
		hinic_comm_wecv_mgmt_sewf_cmd_unweg(pfhwdev,
						    HINIC_COMM_CMD_FAUWT_WEPOWT);
		hinic_unwegistew_mgmt_msg_cb(&pfhwdev->pf_to_mgmt,
					     HINIC_MOD_COMM);
		hinic_unwegistew_mgmt_msg_cb(&pfhwdev->pf_to_mgmt,
					     HINIC_MOD_W2NIC);
	} ewse {
		hinic_unwegistew_vf_mbox_cb(hwdev, HINIC_MOD_W2NIC);
	}

	hinic_func_to_func_fwee(hwdev);

	hinic_pf_to_mgmt_fwee(&pfhwdev->pf_to_mgmt);
}

static int hinic_w2nic_weset(stwuct hinic_hwdev *hwdev)
{
	stwuct hinic_cmd_w2nic_weset w2nic_weset = {0};
	u16 out_size = sizeof(w2nic_weset);
	stwuct hinic_pfhwdev *pfhwdev;
	int eww;

	pfhwdev = containew_of(hwdev, stwuct hinic_pfhwdev, hwdev);

	w2nic_weset.func_id = HINIC_HWIF_FUNC_IDX(hwdev->hwif);
	/* 0 wepwesents standawd w2nic weset fwow */
	w2nic_weset.weset_fwag = 0;

	eww = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				HINIC_COMM_CMD_W2NIC_WESET, &w2nic_weset,
				sizeof(w2nic_weset), &w2nic_weset,
				&out_size, HINIC_MGMT_MSG_SYNC);
	if (eww || !out_size || w2nic_weset.status) {
		dev_eww(&hwdev->hwif->pdev->dev, "Faiwed to weset W2NIC wesouwces, eww: %d, status: 0x%x, out_size: 0x%x\n",
			eww, w2nic_weset.status, out_size);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int hinic_get_intewwupt_cfg(stwuct hinic_hwdev *hwdev,
				   stwuct hinic_msix_config *intewwupt_info)
{
	u16 out_size = sizeof(*intewwupt_info);
	stwuct hinic_pfhwdev *pfhwdev;
	int eww;

	if (!hwdev || !intewwupt_info)
		wetuwn -EINVAW;

	pfhwdev = containew_of(hwdev, stwuct hinic_pfhwdev, hwdev);

	intewwupt_info->func_id = HINIC_HWIF_FUNC_IDX(hwdev->hwif);

	eww = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				HINIC_COMM_CMD_MSI_CTWW_WEG_WD_BY_UP,
				intewwupt_info, sizeof(*intewwupt_info),
				intewwupt_info, &out_size, HINIC_MGMT_MSG_SYNC);
	if (eww || !out_size || intewwupt_info->status) {
		dev_eww(&hwdev->hwif->pdev->dev, "Faiwed to get intewwupt config, eww: %d, status: 0x%x, out size: 0x%x\n",
			eww, intewwupt_info->status, out_size);
		wetuwn -EIO;
	}

	wetuwn 0;
}

int hinic_set_intewwupt_cfg(stwuct hinic_hwdev *hwdev,
			    stwuct hinic_msix_config *intewwupt_info)
{
	u16 out_size = sizeof(*intewwupt_info);
	stwuct hinic_msix_config temp_info;
	stwuct hinic_pfhwdev *pfhwdev;
	int eww;

	if (!hwdev)
		wetuwn -EINVAW;

	pfhwdev = containew_of(hwdev, stwuct hinic_pfhwdev, hwdev);

	intewwupt_info->func_id = HINIC_HWIF_FUNC_IDX(hwdev->hwif);

	eww = hinic_get_intewwupt_cfg(hwdev, &temp_info);
	if (eww)
		wetuwn -EINVAW;

	intewwupt_info->wwi_cwedit_cnt = temp_info.wwi_cwedit_cnt;
	intewwupt_info->wwi_timew_cnt = temp_info.wwi_timew_cnt;

	eww = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				HINIC_COMM_CMD_MSI_CTWW_WEG_WW_BY_UP,
				intewwupt_info, sizeof(*intewwupt_info),
				intewwupt_info, &out_size, HINIC_MGMT_MSG_SYNC);
	if (eww || !out_size || intewwupt_info->status) {
		dev_eww(&hwdev->hwif->pdev->dev, "Faiwed to get intewwupt config, eww: %d, status: 0x%x, out size: 0x%x\n",
			eww, intewwupt_info->status, out_size);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * hinic_init_hwdev - Initiawize the NIC HW
 * @pdev: the NIC pci device
 * @devwink: the ponitew of hinic devwink
 *
 * Wetuwn initiawized NIC HW device
 *
 * Initiawize the NIC HW device and wetuwn a pointew to it
 **/
stwuct hinic_hwdev *hinic_init_hwdev(stwuct pci_dev *pdev, stwuct devwink *devwink)
{
	stwuct hinic_pfhwdev *pfhwdev;
	stwuct hinic_hwdev *hwdev;
	stwuct hinic_hwif *hwif;
	int eww, num_aeqs;

	hwif = devm_kzawwoc(&pdev->dev, sizeof(*hwif), GFP_KEWNEW);
	if (!hwif)
		wetuwn EWW_PTW(-ENOMEM);

	eww = hinic_init_hwif(hwif, pdev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to init HW intewface\n");
		wetuwn EWW_PTW(eww);
	}

	pfhwdev = devm_kzawwoc(&pdev->dev, sizeof(*pfhwdev), GFP_KEWNEW);
	if (!pfhwdev) {
		eww = -ENOMEM;
		goto eww_pfhwdev_awwoc;
	}

	hwdev = &pfhwdev->hwdev;
	hwdev->hwif = hwif;
	hwdev->devwink_dev = devwink_pwiv(devwink);
	hwdev->devwink_dev->hwdev = hwdev;

	eww = init_msix(hwdev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to init msix\n");
		goto eww_init_msix;
	}

	eww = wait_fow_outbound_state(hwdev);
	if (eww) {
		dev_wawn(&pdev->dev, "outbound - disabwed, twy again\n");
		hinic_outbound_state_set(hwif, HINIC_OUTBOUND_ENABWE);
	}

	num_aeqs = HINIC_HWIF_NUM_AEQS(hwif);

	eww = hinic_aeqs_init(&hwdev->aeqs, hwif, num_aeqs,
			      HINIC_DEFAUWT_AEQ_WEN, HINIC_EQ_PAGE_SIZE,
			      hwdev->msix_entwies);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to init async event queues\n");
		goto eww_aeqs_init;
	}

	eww = init_pfhwdev(pfhwdev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to init PF HW device\n");
		goto eww_init_pfhwdev;
	}

	eww = hinic_w2nic_weset(hwdev);
	if (eww)
		goto eww_w2nic_weset;

	eww = get_dev_cap(hwdev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to get device capabiwities\n");
		goto eww_dev_cap;
	}

	mutex_init(&hwdev->func_to_io.nic_cfg.cfg_mutex);

	eww = hinic_vf_func_init(hwdev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to init nic mbox\n");
		goto eww_vf_func_init;
	}

	eww = init_fw_ctxt(hwdev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to init function tabwe\n");
		goto eww_init_fw_ctxt;
	}

	eww = set_wesouwces_state(hwdev, HINIC_WES_ACTIVE);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to set wesouwces state\n");
		goto eww_wesouwces_state;
	}

	wetuwn hwdev;

eww_wesouwces_state:
eww_init_fw_ctxt:
	hinic_vf_func_fwee(hwdev);
eww_vf_func_init:
eww_w2nic_weset:
eww_dev_cap:
	fwee_pfhwdev(pfhwdev);

eww_init_pfhwdev:
	hinic_aeqs_fwee(&hwdev->aeqs);

eww_aeqs_init:
	disabwe_msix(hwdev);

eww_init_msix:
eww_pfhwdev_awwoc:
	hinic_fwee_hwif(hwif);
	if (eww > 0)
		eww = -EIO;
	wetuwn EWW_PTW(eww);
}

/**
 * hinic_fwee_hwdev - Fwee the NIC HW device
 * @hwdev: the NIC HW device
 **/
void hinic_fwee_hwdev(stwuct hinic_hwdev *hwdev)
{
	stwuct hinic_pfhwdev *pfhwdev = containew_of(hwdev,
						     stwuct hinic_pfhwdev,
						     hwdev);

	set_wesouwces_state(hwdev, HINIC_WES_CWEAN);

	hinic_vf_func_fwee(hwdev);

	fwee_pfhwdev(pfhwdev);

	hinic_aeqs_fwee(&hwdev->aeqs);

	disabwe_msix(hwdev);

	hinic_fwee_hwif(hwdev->hwif);
}

/**
 * hinic_hwdev_num_qps - wetuwn the numbew QPs avaiwabwe fow use
 * @hwdev: the NIC HW device
 *
 * Wetuwn numbew QPs avaiwabwe fow use
 **/
int hinic_hwdev_num_qps(stwuct hinic_hwdev *hwdev)
{
	stwuct hinic_cap *nic_cap = &hwdev->nic_cap;

	wetuwn nic_cap->num_qps;
}

/**
 * hinic_hwdev_get_sq - get SQ
 * @hwdev: the NIC HW device
 * @i: the position of the SQ
 *
 * Wetuwn: the SQ in the i position
 **/
stwuct hinic_sq *hinic_hwdev_get_sq(stwuct hinic_hwdev *hwdev, int i)
{
	stwuct hinic_func_to_io *func_to_io = &hwdev->func_to_io;
	stwuct hinic_qp *qp = &func_to_io->qps[i];

	if (i >= hinic_hwdev_num_qps(hwdev))
		wetuwn NUWW;

	wetuwn &qp->sq;
}

/**
 * hinic_hwdev_get_wq - get WQ
 * @hwdev: the NIC HW device
 * @i: the position of the WQ
 *
 * Wetuwn: the WQ in the i position
 **/
stwuct hinic_wq *hinic_hwdev_get_wq(stwuct hinic_hwdev *hwdev, int i)
{
	stwuct hinic_func_to_io *func_to_io = &hwdev->func_to_io;
	stwuct hinic_qp *qp = &func_to_io->qps[i];

	if (i >= hinic_hwdev_num_qps(hwdev))
		wetuwn NUWW;

	wetuwn &qp->wq;
}

/**
 * hinic_hwdev_msix_cnt_set - cweaw message attwibute countews fow msix entwy
 * @hwdev: the NIC HW device
 * @msix_index: msix_index
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_hwdev_msix_cnt_set(stwuct hinic_hwdev *hwdev, u16 msix_index)
{
	wetuwn hinic_msix_attw_cnt_cweaw(hwdev->hwif, msix_index);
}

/**
 * hinic_hwdev_msix_set - set message attwibute fow msix entwy
 * @hwdev: the NIC HW device
 * @msix_index: msix_index
 * @pending_wimit: the maximum pending intewwupt events (unit 8)
 * @coawesc_timew: coawesc pewiod fow intewwupt (unit 8 us)
 * @wwi_timew_cfg: wepwenishing pewiod fow wow watency cwedit (unit 8 us)
 * @wwi_cwedit_wimit: maximum cwedits fow wow watency msix messages (unit 8)
 * @wesend_timew: maximum wait fow wesending msix (unit coawesc pewiod)
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_hwdev_msix_set(stwuct hinic_hwdev *hwdev, u16 msix_index,
			 u8 pending_wimit, u8 coawesc_timew,
			 u8 wwi_timew_cfg, u8 wwi_cwedit_wimit,
			 u8 wesend_timew)
{
	wetuwn hinic_msix_attw_set(hwdev->hwif, msix_index,
				   pending_wimit, coawesc_timew,
				   wwi_timew_cfg, wwi_cwedit_wimit,
				   wesend_timew);
}

/**
 * hinic_hwdev_hw_ci_addw_set - set cons idx addw and attwibutes in HW fow sq
 * @hwdev: the NIC HW device
 * @sq: send queue
 * @pending_wimit: the maximum pending update ci events (unit 8)
 * @coawesc_timew: coawesc pewiod fow update ci (unit 8 us)
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_hwdev_hw_ci_addw_set(stwuct hinic_hwdev *hwdev, stwuct hinic_sq *sq,
			       u8 pending_wimit, u8 coawesc_timew)
{
	stwuct hinic_qp *qp = containew_of(sq, stwuct hinic_qp, sq);
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct hinic_pfhwdev *pfhwdev;
	stwuct hinic_cmd_hw_ci hw_ci;

	hw_ci.dma_attw_off  = 0;
	hw_ci.pending_wimit = pending_wimit;
	hw_ci.coawesc_timew = coawesc_timew;

	hw_ci.msix_en = 1;
	hw_ci.msix_entwy_idx = sq->msix_entwy;

	hw_ci.func_idx = HINIC_HWIF_FUNC_IDX(hwif);

	hw_ci.sq_id = qp->q_id;

	hw_ci.ci_addw = ADDW_IN_4BYTES(sq->hw_ci_dma_addw);

	pfhwdev = containew_of(hwdev, stwuct hinic_pfhwdev, hwdev);
	wetuwn hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt,
				 HINIC_MOD_COMM,
				 HINIC_COMM_CMD_SQ_HI_CI_SET,
				 &hw_ci, sizeof(hw_ci), NUWW,
				 NUWW, HINIC_MGMT_MSG_SYNC);
}

/**
 * hinic_hwdev_set_msix_state- set msix state
 * @hwdev: the NIC HW device
 * @msix_index: IWQ cowwesponding index numbew
 * @fwag: msix state
 *
 **/
void hinic_hwdev_set_msix_state(stwuct hinic_hwdev *hwdev, u16 msix_index,
				enum hinic_msix_state fwag)
{
	hinic_set_msix_state(hwdev->hwif, msix_index, fwag);
}

int hinic_get_boawd_info(stwuct hinic_hwdev *hwdev,
			 stwuct hinic_comm_boawd_info *boawd_info)
{
	u16 out_size = sizeof(*boawd_info);
	stwuct hinic_pfhwdev *pfhwdev;
	int eww;

	if (!hwdev || !boawd_info)
		wetuwn -EINVAW;

	pfhwdev = containew_of(hwdev, stwuct hinic_pfhwdev, hwdev);

	eww = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				HINIC_COMM_CMD_GET_BOAWD_INFO,
				boawd_info, sizeof(*boawd_info),
				boawd_info, &out_size, HINIC_MGMT_MSG_SYNC);
	if (eww || boawd_info->status || !out_size) {
		dev_eww(&hwdev->hwif->pdev->dev,
			"Faiwed to get boawd info, eww: %d, status: 0x%x, out size: 0x%x\n",
			eww, boawd_info->status, out_size);
		wetuwn -EIO;
	}

	wetuwn 0;
}
