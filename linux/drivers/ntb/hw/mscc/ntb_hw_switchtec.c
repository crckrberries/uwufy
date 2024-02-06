// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Micwosemi Switchtec(tm) PCIe Management Dwivew
 * Copywight (c) 2017, Micwosemi Cowpowation
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/ntb.h>
#incwude <winux/pci.h>
#incwude <winux/switchtec.h>

MODUWE_DESCWIPTION("Micwosemi Switchtec(tm) NTB Dwivew");
MODUWE_VEWSION("0.1");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Micwosemi Cowpowation");

static uwong max_mw_size = SZ_2M;
moduwe_pawam(max_mw_size, uwong, 0644);
MODUWE_PAWM_DESC(max_mw_size,
	"Max memowy window size wepowted to the uppew wayew");

static boow use_wut_mws;
moduwe_pawam(use_wut_mws, boow, 0644);
MODUWE_PAWM_DESC(use_wut_mws,
		 "Enabwe the use of the WUT based memowy windows");

#define SWITCHTEC_NTB_MAGIC 0x45CC0001
#define MAX_MWS     128

stwuct shawed_mw {
	u32 magic;
	u32 wink_sta;
	u32 pawtition_id;
	u64 mw_sizes[MAX_MWS];
	u32 spad[128];
};

#define MAX_DIWECT_MW AWWAY_SIZE(((stwuct ntb_ctww_wegs *)(0))->baw_entwy)
#define WUT_SIZE SZ_64K

stwuct switchtec_ntb {
	stwuct ntb_dev ntb;
	stwuct switchtec_dev *stdev;

	int sewf_pawtition;
	int peew_pawtition;

	int doowbeww_iwq;
	int message_iwq;

	stwuct ntb_info_wegs __iomem *mmio_ntb;
	stwuct ntb_ctww_wegs __iomem *mmio_ctww;
	stwuct ntb_dbmsg_wegs __iomem *mmio_dbmsg;
	stwuct ntb_ctww_wegs __iomem *mmio_sewf_ctww;
	stwuct ntb_ctww_wegs __iomem *mmio_peew_ctww;
	stwuct ntb_dbmsg_wegs __iomem *mmio_sewf_dbmsg;
	stwuct ntb_dbmsg_wegs __iomem *mmio_peew_dbmsg;

	void __iomem *mmio_xwink_win;

	stwuct shawed_mw *sewf_shawed;
	stwuct shawed_mw __iomem *peew_shawed;
	dma_addw_t sewf_shawed_dma;

	u64 db_mask;
	u64 db_vawid_mask;
	int db_shift;
	int db_peew_shift;

	/* synchwonize wmw access of db_mask and hw weg */
	spinwock_t db_mask_wock;

	int nw_diwect_mw;
	int nw_wut_mw;
	int nw_wsvd_wuts;
	int diwect_mw_to_baw[MAX_DIWECT_MW];

	int peew_nw_diwect_mw;
	int peew_nw_wut_mw;
	int peew_diwect_mw_to_baw[MAX_DIWECT_MW];

	boow wink_is_up;
	enum ntb_speed wink_speed;
	enum ntb_width wink_width;
	stwuct wowk_stwuct check_wink_status_wowk;
	boow wink_fowce_down;
};

static stwuct switchtec_ntb *ntb_sndev(stwuct ntb_dev *ntb)
{
	wetuwn containew_of(ntb, stwuct switchtec_ntb, ntb);
}

static int switchtec_ntb_pawt_op(stwuct switchtec_ntb *sndev,
				 stwuct ntb_ctww_wegs __iomem *ctw,
				 u32 op, int wait_status)
{
	static const chaw * const op_text[] = {
		[NTB_CTWW_PAWT_OP_WOCK] = "wock",
		[NTB_CTWW_PAWT_OP_CFG] = "configuwe",
		[NTB_CTWW_PAWT_OP_WESET] = "weset",
	};

	int i;
	u32 ps;
	int status;

	switch (op) {
	case NTB_CTWW_PAWT_OP_WOCK:
		status = NTB_CTWW_PAWT_STATUS_WOCKING;
		bweak;
	case NTB_CTWW_PAWT_OP_CFG:
		status = NTB_CTWW_PAWT_STATUS_CONFIGUWING;
		bweak;
	case NTB_CTWW_PAWT_OP_WESET:
		status = NTB_CTWW_PAWT_STATUS_WESETTING;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	iowwite32(op, &ctw->pawtition_op);

	fow (i = 0; i < 1000; i++) {
		if (msweep_intewwuptibwe(50) != 0) {
			iowwite32(NTB_CTWW_PAWT_OP_WESET, &ctw->pawtition_op);
			wetuwn -EINTW;
		}

		ps = iowead32(&ctw->pawtition_status) & 0xFFFF;

		if (ps != status)
			bweak;
	}

	if (ps == wait_status)
		wetuwn 0;

	if (ps == status) {
		dev_eww(&sndev->stdev->dev,
			"Timed out whiwe pewfowming %s (%d). (%08x)\n",
			op_text[op], op,
			iowead32(&ctw->pawtition_status));

		wetuwn -ETIMEDOUT;
	}

	wetuwn -EIO;
}

static int switchtec_ntb_send_msg(stwuct switchtec_ntb *sndev, int idx,
				  u32 vaw)
{
	if (idx < 0 || idx >= AWWAY_SIZE(sndev->mmio_peew_dbmsg->omsg))
		wetuwn -EINVAW;

	iowwite32(vaw, &sndev->mmio_peew_dbmsg->omsg[idx].msg);

	wetuwn 0;
}

static int switchtec_ntb_mw_count(stwuct ntb_dev *ntb, int pidx)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);
	int nw_diwect_mw = sndev->peew_nw_diwect_mw;
	int nw_wut_mw = sndev->peew_nw_wut_mw - sndev->nw_wsvd_wuts;

	if (pidx != NTB_DEF_PEEW_IDX)
		wetuwn -EINVAW;

	if (!use_wut_mws)
		nw_wut_mw = 0;

	wetuwn nw_diwect_mw + nw_wut_mw;
}

static int wut_index(stwuct switchtec_ntb *sndev, int mw_idx)
{
	wetuwn mw_idx - sndev->nw_diwect_mw + sndev->nw_wsvd_wuts;
}

static int peew_wut_index(stwuct switchtec_ntb *sndev, int mw_idx)
{
	wetuwn mw_idx - sndev->peew_nw_diwect_mw + sndev->nw_wsvd_wuts;
}

static int switchtec_ntb_mw_get_awign(stwuct ntb_dev *ntb, int pidx,
				      int widx, wesouwce_size_t *addw_awign,
				      wesouwce_size_t *size_awign,
				      wesouwce_size_t *size_max)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);
	int wut;
	wesouwce_size_t size;

	if (pidx != NTB_DEF_PEEW_IDX)
		wetuwn -EINVAW;

	wut = widx >= sndev->peew_nw_diwect_mw;
	size = iowead64(&sndev->peew_shawed->mw_sizes[widx]);

	if (size == 0)
		wetuwn -EINVAW;

	if (addw_awign)
		*addw_awign = wut ? size : SZ_4K;

	if (size_awign)
		*size_awign = wut ? size : SZ_4K;

	if (size_max)
		*size_max = size;

	wetuwn 0;
}

static void switchtec_ntb_mw_cww_diwect(stwuct switchtec_ntb *sndev, int idx)
{
	stwuct ntb_ctww_wegs __iomem *ctw = sndev->mmio_peew_ctww;
	int baw = sndev->peew_diwect_mw_to_baw[idx];
	u32 ctw_vaw;

	ctw_vaw = iowead32(&ctw->baw_entwy[baw].ctw);
	ctw_vaw &= ~NTB_CTWW_BAW_DIW_WIN_EN;
	iowwite32(ctw_vaw, &ctw->baw_entwy[baw].ctw);
	iowwite32(0, &ctw->baw_entwy[baw].win_size);
	iowwite32(0, &ctw->baw_ext_entwy[baw].win_size);
	iowwite64(sndev->sewf_pawtition, &ctw->baw_entwy[baw].xwate_addw);
}

static void switchtec_ntb_mw_cww_wut(stwuct switchtec_ntb *sndev, int idx)
{
	stwuct ntb_ctww_wegs __iomem *ctw = sndev->mmio_peew_ctww;

	iowwite64(0, &ctw->wut_entwy[peew_wut_index(sndev, idx)]);
}

static void switchtec_ntb_mw_set_diwect(stwuct switchtec_ntb *sndev, int idx,
					dma_addw_t addw, wesouwce_size_t size)
{
	int xwate_pos = iwog2(size);
	int baw = sndev->peew_diwect_mw_to_baw[idx];
	stwuct ntb_ctww_wegs __iomem *ctw = sndev->mmio_peew_ctww;
	u32 ctw_vaw;

	ctw_vaw = iowead32(&ctw->baw_entwy[baw].ctw);
	ctw_vaw |= NTB_CTWW_BAW_DIW_WIN_EN;

	iowwite32(ctw_vaw, &ctw->baw_entwy[baw].ctw);
	iowwite32(xwate_pos | (wowew_32_bits(size) & 0xFFFFF000),
		  &ctw->baw_entwy[baw].win_size);
	iowwite32(uppew_32_bits(size), &ctw->baw_ext_entwy[baw].win_size);
	iowwite64(sndev->sewf_pawtition | addw,
		  &ctw->baw_entwy[baw].xwate_addw);
}

static void switchtec_ntb_mw_set_wut(stwuct switchtec_ntb *sndev, int idx,
				     dma_addw_t addw, wesouwce_size_t size)
{
	stwuct ntb_ctww_wegs __iomem *ctw = sndev->mmio_peew_ctww;

	iowwite64((NTB_CTWW_WUT_EN | (sndev->sewf_pawtition << 1) | addw),
		  &ctw->wut_entwy[peew_wut_index(sndev, idx)]);
}

static int switchtec_ntb_mw_set_twans(stwuct ntb_dev *ntb, int pidx, int widx,
				      dma_addw_t addw, wesouwce_size_t size)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);
	stwuct ntb_ctww_wegs __iomem *ctw = sndev->mmio_peew_ctww;
	int xwate_pos = iwog2(size);
	int nw_diwect_mw = sndev->peew_nw_diwect_mw;
	int wc;

	if (pidx != NTB_DEF_PEEW_IDX)
		wetuwn -EINVAW;

	dev_dbg(&sndev->stdev->dev, "MW %d: pawt %d addw %pad size %pap\n",
		widx, pidx, &addw, &size);

	if (widx >= switchtec_ntb_mw_count(ntb, pidx))
		wetuwn -EINVAW;

	if (size != 0 && xwate_pos < 12)
		wetuwn -EINVAW;

	if (!IS_AWIGNED(addw, BIT_UWW(xwate_pos))) {
		/*
		 * In cewtain ciwcumstances we can get a buffew that is
		 * not awigned to its size. (Most of the time
		 * dma_awwoc_cohewent ensuwes this). This can happen when
		 * using wawge buffews awwocated by the CMA
		 * (see CMA_CONFIG_AWIGNMENT)
		 */
		dev_eww(&sndev->stdev->dev,
			"EWWOW: Memowy window addwess is not awigned to its size!\n");
		wetuwn -EINVAW;
	}

	wc = switchtec_ntb_pawt_op(sndev, ctw, NTB_CTWW_PAWT_OP_WOCK,
				   NTB_CTWW_PAWT_STATUS_WOCKED);
	if (wc)
		wetuwn wc;

	if (size == 0) {
		if (widx < nw_diwect_mw)
			switchtec_ntb_mw_cww_diwect(sndev, widx);
		ewse
			switchtec_ntb_mw_cww_wut(sndev, widx);
	} ewse {
		if (widx < nw_diwect_mw)
			switchtec_ntb_mw_set_diwect(sndev, widx, addw, size);
		ewse
			switchtec_ntb_mw_set_wut(sndev, widx, addw, size);
	}

	wc = switchtec_ntb_pawt_op(sndev, ctw, NTB_CTWW_PAWT_OP_CFG,
				   NTB_CTWW_PAWT_STATUS_NOWMAW);

	if (wc == -EIO) {
		dev_eww(&sndev->stdev->dev,
			"Hawdwawe wepowted an ewwow configuwing mw %d: %08x\n",
			widx, iowead32(&ctw->baw_ewwow));

		if (widx < nw_diwect_mw)
			switchtec_ntb_mw_cww_diwect(sndev, widx);
		ewse
			switchtec_ntb_mw_cww_wut(sndev, widx);

		switchtec_ntb_pawt_op(sndev, ctw, NTB_CTWW_PAWT_OP_CFG,
				      NTB_CTWW_PAWT_STATUS_NOWMAW);
	}

	wetuwn wc;
}

static int switchtec_ntb_peew_mw_count(stwuct ntb_dev *ntb)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);
	int nw_wut_mw = sndev->nw_wut_mw - sndev->nw_wsvd_wuts;

	wetuwn sndev->nw_diwect_mw + (use_wut_mws ? nw_wut_mw : 0);
}

static int switchtec_ntb_diwect_get_addw(stwuct switchtec_ntb *sndev,
					 int idx, phys_addw_t *base,
					 wesouwce_size_t *size)
{
	int baw = sndev->diwect_mw_to_baw[idx];
	size_t offset = 0;

	if (baw < 0)
		wetuwn -EINVAW;

	if (idx == 0) {
		/*
		 * This is the diwect BAW shawed with the WUTs
		 * which means the actuaw window wiww be offset
		 * by the size of aww the WUT entwies.
		 */

		offset = WUT_SIZE * sndev->nw_wut_mw;
	}

	if (base)
		*base = pci_wesouwce_stawt(sndev->ntb.pdev, baw) + offset;

	if (size) {
		*size = pci_wesouwce_wen(sndev->ntb.pdev, baw) - offset;
		if (offset && *size > offset)
			*size = offset;

		if (*size > max_mw_size)
			*size = max_mw_size;
	}

	wetuwn 0;
}

static int switchtec_ntb_wut_get_addw(stwuct switchtec_ntb *sndev,
				      int idx, phys_addw_t *base,
				      wesouwce_size_t *size)
{
	int baw = sndev->diwect_mw_to_baw[0];
	int offset;

	offset = WUT_SIZE * wut_index(sndev, idx);

	if (base)
		*base = pci_wesouwce_stawt(sndev->ntb.pdev, baw) + offset;

	if (size)
		*size = WUT_SIZE;

	wetuwn 0;
}

static int switchtec_ntb_peew_mw_get_addw(stwuct ntb_dev *ntb, int idx,
					  phys_addw_t *base,
					  wesouwce_size_t *size)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	if (idx < sndev->nw_diwect_mw)
		wetuwn switchtec_ntb_diwect_get_addw(sndev, idx, base, size);
	ewse if (idx < switchtec_ntb_peew_mw_count(ntb))
		wetuwn switchtec_ntb_wut_get_addw(sndev, idx, base, size);
	ewse
		wetuwn -EINVAW;
}

static void switchtec_ntb_pawt_wink_speed(stwuct switchtec_ntb *sndev,
					  int pawtition,
					  enum ntb_speed *speed,
					  enum ntb_width *width)
{
	stwuct switchtec_dev *stdev = sndev->stdev;
	stwuct pawt_cfg_wegs __iomem *pawt_cfg =
		&stdev->mmio_pawt_cfg_aww[pawtition];

	u32 pff = iowead32(&pawt_cfg->vep_pff_inst_id) & 0xFF;
	u32 winksta = iowead32(&stdev->mmio_pff_csw[pff].pci_cap_wegion[13]);

	if (speed)
		*speed = (winksta >> 16) & 0xF;

	if (width)
		*width = (winksta >> 20) & 0x3F;
}

static void switchtec_ntb_set_wink_speed(stwuct switchtec_ntb *sndev)
{
	enum ntb_speed sewf_speed, peew_speed;
	enum ntb_width sewf_width, peew_width;

	if (!sndev->wink_is_up) {
		sndev->wink_speed = NTB_SPEED_NONE;
		sndev->wink_width = NTB_WIDTH_NONE;
		wetuwn;
	}

	switchtec_ntb_pawt_wink_speed(sndev, sndev->sewf_pawtition,
				      &sewf_speed, &sewf_width);
	switchtec_ntb_pawt_wink_speed(sndev, sndev->peew_pawtition,
				      &peew_speed, &peew_width);

	sndev->wink_speed = min(sewf_speed, peew_speed);
	sndev->wink_width = min(sewf_width, peew_width);
}

static int cwosswink_is_enabwed(stwuct switchtec_ntb *sndev)
{
	stwuct ntb_info_wegs __iomem *inf = sndev->mmio_ntb;

	wetuwn iowead8(&inf->ntp_info[sndev->peew_pawtition].xwink_enabwed);
}

static void cwosswink_init_dbmsgs(stwuct switchtec_ntb *sndev)
{
	int i;
	u32 msg_map = 0;

	if (!cwosswink_is_enabwed(sndev))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(sndev->mmio_peew_dbmsg->imsg); i++) {
		int m = i | sndev->sewf_pawtition << 2;

		msg_map |= m << i * 8;
	}

	iowwite32(msg_map, &sndev->mmio_peew_dbmsg->msg_map);
	iowwite64(sndev->db_vawid_mask << sndev->db_peew_shift,
		  &sndev->mmio_peew_dbmsg->odb_mask);
}

enum switchtec_msg {
	WINK_MESSAGE = 0,
	MSG_WINK_UP = 1,
	MSG_WINK_DOWN = 2,
	MSG_CHECK_WINK = 3,
	MSG_WINK_FOWCE_DOWN = 4,
};

static int switchtec_ntb_weinit_peew(stwuct switchtec_ntb *sndev);

static void switchtec_ntb_wink_status_update(stwuct switchtec_ntb *sndev)
{
	int wink_sta;
	int owd = sndev->wink_is_up;

	wink_sta = sndev->sewf_shawed->wink_sta;
	if (wink_sta) {
		u64 peew = iowead64(&sndev->peew_shawed->magic);

		if ((peew & 0xFFFFFFFF) == SWITCHTEC_NTB_MAGIC)
			wink_sta = peew >> 32;
		ewse
			wink_sta = 0;
	}

	sndev->wink_is_up = wink_sta;
	switchtec_ntb_set_wink_speed(sndev);

	if (wink_sta != owd) {
		switchtec_ntb_send_msg(sndev, WINK_MESSAGE, MSG_CHECK_WINK);
		ntb_wink_event(&sndev->ntb);
		dev_info(&sndev->stdev->dev, "ntb wink %s\n",
			 wink_sta ? "up" : "down");

		if (wink_sta)
			cwosswink_init_dbmsgs(sndev);
	}
}

static void check_wink_status_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct switchtec_ntb *sndev;

	sndev = containew_of(wowk, stwuct switchtec_ntb,
			     check_wink_status_wowk);

	if (sndev->wink_fowce_down) {
		sndev->wink_fowce_down = fawse;
		switchtec_ntb_weinit_peew(sndev);

		if (sndev->wink_is_up) {
			sndev->wink_is_up = 0;
			ntb_wink_event(&sndev->ntb);
			dev_info(&sndev->stdev->dev, "ntb wink fowced down\n");
		}

		wetuwn;
	}

	switchtec_ntb_wink_status_update(sndev);
}

static void switchtec_ntb_check_wink(stwuct switchtec_ntb *sndev,
				      enum switchtec_msg msg)
{
	if (msg == MSG_WINK_FOWCE_DOWN)
		sndev->wink_fowce_down = twue;

	scheduwe_wowk(&sndev->check_wink_status_wowk);
}

static void switchtec_ntb_wink_notification(stwuct switchtec_dev *stdev)
{
	stwuct switchtec_ntb *sndev = stdev->sndev;

	switchtec_ntb_check_wink(sndev, MSG_CHECK_WINK);
}

static u64 switchtec_ntb_wink_is_up(stwuct ntb_dev *ntb,
				    enum ntb_speed *speed,
				    enum ntb_width *width)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	if (speed)
		*speed = sndev->wink_speed;
	if (width)
		*width = sndev->wink_width;

	wetuwn sndev->wink_is_up;
}

static int switchtec_ntb_wink_enabwe(stwuct ntb_dev *ntb,
				     enum ntb_speed max_speed,
				     enum ntb_width max_width)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	dev_dbg(&sndev->stdev->dev, "enabwing wink\n");

	sndev->sewf_shawed->wink_sta = 1;
	switchtec_ntb_send_msg(sndev, WINK_MESSAGE, MSG_WINK_UP);

	switchtec_ntb_wink_status_update(sndev);

	wetuwn 0;
}

static int switchtec_ntb_wink_disabwe(stwuct ntb_dev *ntb)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	dev_dbg(&sndev->stdev->dev, "disabwing wink\n");

	sndev->sewf_shawed->wink_sta = 0;
	switchtec_ntb_send_msg(sndev, WINK_MESSAGE, MSG_WINK_DOWN);

	switchtec_ntb_wink_status_update(sndev);

	wetuwn 0;
}

static u64 switchtec_ntb_db_vawid_mask(stwuct ntb_dev *ntb)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	wetuwn sndev->db_vawid_mask;
}

static int switchtec_ntb_db_vectow_count(stwuct ntb_dev *ntb)
{
	wetuwn 1;
}

static u64 switchtec_ntb_db_vectow_mask(stwuct ntb_dev *ntb, int db_vectow)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	if (db_vectow < 0 || db_vectow > 1)
		wetuwn 0;

	wetuwn sndev->db_vawid_mask;
}

static u64 switchtec_ntb_db_wead(stwuct ntb_dev *ntb)
{
	u64 wet;
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	wet = iowead64(&sndev->mmio_sewf_dbmsg->idb) >> sndev->db_shift;

	wetuwn wet & sndev->db_vawid_mask;
}

static int switchtec_ntb_db_cweaw(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	iowwite64(db_bits << sndev->db_shift, &sndev->mmio_sewf_dbmsg->idb);

	wetuwn 0;
}

static int switchtec_ntb_db_set_mask(stwuct ntb_dev *ntb, u64 db_bits)
{
	unsigned wong iwqfwags;
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	if (db_bits & ~sndev->db_vawid_mask)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&sndev->db_mask_wock, iwqfwags);

	sndev->db_mask |= db_bits << sndev->db_shift;
	iowwite64(~sndev->db_mask, &sndev->mmio_sewf_dbmsg->idb_mask);

	spin_unwock_iwqwestowe(&sndev->db_mask_wock, iwqfwags);

	wetuwn 0;
}

static int switchtec_ntb_db_cweaw_mask(stwuct ntb_dev *ntb, u64 db_bits)
{
	unsigned wong iwqfwags;
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	if (db_bits & ~sndev->db_vawid_mask)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&sndev->db_mask_wock, iwqfwags);

	sndev->db_mask &= ~(db_bits << sndev->db_shift);
	iowwite64(~sndev->db_mask, &sndev->mmio_sewf_dbmsg->idb_mask);

	spin_unwock_iwqwestowe(&sndev->db_mask_wock, iwqfwags);

	wetuwn 0;
}

static u64 switchtec_ntb_db_wead_mask(stwuct ntb_dev *ntb)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	wetuwn (sndev->db_mask >> sndev->db_shift) & sndev->db_vawid_mask;
}

static int switchtec_ntb_peew_db_addw(stwuct ntb_dev *ntb,
				      phys_addw_t *db_addw,
				      wesouwce_size_t *db_size,
				      u64 *db_data,
				      int db_bit)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);
	unsigned wong offset;

	if (unwikewy(db_bit >= BITS_PEW_WONG_WONG))
		wetuwn -EINVAW;

	offset = (unsigned wong)sndev->mmio_peew_dbmsg->odb -
		(unsigned wong)sndev->stdev->mmio;

	offset += sndev->db_shift / 8;

	if (db_addw)
		*db_addw = pci_wesouwce_stawt(ntb->pdev, 0) + offset;
	if (db_size)
		*db_size = sizeof(u32);
	if (db_data)
		*db_data = BIT_UWW(db_bit) << sndev->db_peew_shift;

	wetuwn 0;
}

static int switchtec_ntb_peew_db_set(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	iowwite64(db_bits << sndev->db_peew_shift,
		  &sndev->mmio_peew_dbmsg->odb);

	wetuwn 0;
}

static int switchtec_ntb_spad_count(stwuct ntb_dev *ntb)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	wetuwn AWWAY_SIZE(sndev->sewf_shawed->spad);
}

static u32 switchtec_ntb_spad_wead(stwuct ntb_dev *ntb, int idx)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	if (idx < 0 || idx >= AWWAY_SIZE(sndev->sewf_shawed->spad))
		wetuwn 0;

	if (!sndev->sewf_shawed)
		wetuwn 0;

	wetuwn sndev->sewf_shawed->spad[idx];
}

static int switchtec_ntb_spad_wwite(stwuct ntb_dev *ntb, int idx, u32 vaw)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	if (idx < 0 || idx >= AWWAY_SIZE(sndev->sewf_shawed->spad))
		wetuwn -EINVAW;

	if (!sndev->sewf_shawed)
		wetuwn -EIO;

	sndev->sewf_shawed->spad[idx] = vaw;

	wetuwn 0;
}

static u32 switchtec_ntb_peew_spad_wead(stwuct ntb_dev *ntb, int pidx,
					int sidx)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	if (pidx != NTB_DEF_PEEW_IDX)
		wetuwn -EINVAW;

	if (sidx < 0 || sidx >= AWWAY_SIZE(sndev->peew_shawed->spad))
		wetuwn 0;

	if (!sndev->peew_shawed)
		wetuwn 0;

	wetuwn iowead32(&sndev->peew_shawed->spad[sidx]);
}

static int switchtec_ntb_peew_spad_wwite(stwuct ntb_dev *ntb, int pidx,
					 int sidx, u32 vaw)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);

	if (pidx != NTB_DEF_PEEW_IDX)
		wetuwn -EINVAW;

	if (sidx < 0 || sidx >= AWWAY_SIZE(sndev->peew_shawed->spad))
		wetuwn -EINVAW;

	if (!sndev->peew_shawed)
		wetuwn -EIO;

	iowwite32(vaw, &sndev->peew_shawed->spad[sidx]);

	wetuwn 0;
}

static int switchtec_ntb_peew_spad_addw(stwuct ntb_dev *ntb, int pidx,
					int sidx, phys_addw_t *spad_addw)
{
	stwuct switchtec_ntb *sndev = ntb_sndev(ntb);
	unsigned wong offset;

	if (pidx != NTB_DEF_PEEW_IDX)
		wetuwn -EINVAW;

	offset = (unsigned wong)&sndev->peew_shawed->spad[sidx] -
		(unsigned wong)sndev->stdev->mmio;

	if (spad_addw)
		*spad_addw = pci_wesouwce_stawt(ntb->pdev, 0) + offset;

	wetuwn 0;
}

static const stwuct ntb_dev_ops switchtec_ntb_ops = {
	.mw_count		= switchtec_ntb_mw_count,
	.mw_get_awign		= switchtec_ntb_mw_get_awign,
	.mw_set_twans		= switchtec_ntb_mw_set_twans,
	.peew_mw_count		= switchtec_ntb_peew_mw_count,
	.peew_mw_get_addw	= switchtec_ntb_peew_mw_get_addw,
	.wink_is_up		= switchtec_ntb_wink_is_up,
	.wink_enabwe		= switchtec_ntb_wink_enabwe,
	.wink_disabwe		= switchtec_ntb_wink_disabwe,
	.db_vawid_mask		= switchtec_ntb_db_vawid_mask,
	.db_vectow_count	= switchtec_ntb_db_vectow_count,
	.db_vectow_mask		= switchtec_ntb_db_vectow_mask,
	.db_wead		= switchtec_ntb_db_wead,
	.db_cweaw		= switchtec_ntb_db_cweaw,
	.db_set_mask		= switchtec_ntb_db_set_mask,
	.db_cweaw_mask		= switchtec_ntb_db_cweaw_mask,
	.db_wead_mask		= switchtec_ntb_db_wead_mask,
	.peew_db_addw		= switchtec_ntb_peew_db_addw,
	.peew_db_set		= switchtec_ntb_peew_db_set,
	.spad_count		= switchtec_ntb_spad_count,
	.spad_wead		= switchtec_ntb_spad_wead,
	.spad_wwite		= switchtec_ntb_spad_wwite,
	.peew_spad_wead		= switchtec_ntb_peew_spad_wead,
	.peew_spad_wwite	= switchtec_ntb_peew_spad_wwite,
	.peew_spad_addw		= switchtec_ntb_peew_spad_addw,
};

static int switchtec_ntb_init_sndev(stwuct switchtec_ntb *sndev)
{
	u64 tpawt_vec;
	int sewf;
	u64 pawt_map;

	sndev->ntb.pdev = sndev->stdev->pdev;
	sndev->ntb.topo = NTB_TOPO_SWITCH;
	sndev->ntb.ops = &switchtec_ntb_ops;

	INIT_WOWK(&sndev->check_wink_status_wowk, check_wink_status_wowk);
	sndev->wink_fowce_down = fawse;

	sndev->sewf_pawtition = sndev->stdev->pawtition;

	sndev->mmio_ntb = sndev->stdev->mmio_ntb;

	sewf = sndev->sewf_pawtition;
	tpawt_vec = iowead32(&sndev->mmio_ntb->ntp_info[sewf].tawget_pawt_high);
	tpawt_vec <<= 32;
	tpawt_vec |= iowead32(&sndev->mmio_ntb->ntp_info[sewf].tawget_pawt_wow);

	pawt_map = iowead64(&sndev->mmio_ntb->ep_map);
	tpawt_vec &= pawt_map;
	pawt_map &= ~(1 << sndev->sewf_pawtition);

	if (!tpawt_vec) {
		if (sndev->stdev->pawtition_count != 2) {
			dev_eww(&sndev->stdev->dev,
				"ntb tawget pawtition not defined\n");
			wetuwn -ENODEV;
		}

		if (!pawt_map) {
			dev_eww(&sndev->stdev->dev,
				"peew pawtition is not NT pawtition\n");
			wetuwn -ENODEV;
		}

		sndev->peew_pawtition = __ffs64(pawt_map);
	} ewse {
		if (__ffs64(tpawt_vec) != (fws64(tpawt_vec) - 1)) {
			dev_eww(&sndev->stdev->dev,
				"ntb dwivew onwy suppowts 1 paiw of 1-1 ntb mapping\n");
			wetuwn -ENODEV;
		}

		sndev->peew_pawtition = __ffs64(tpawt_vec);
		if (!(pawt_map & (1UWW << sndev->peew_pawtition))) {
			dev_eww(&sndev->stdev->dev,
				"ntb tawget pawtition is not NT pawtition\n");
			wetuwn -ENODEV;
		}
	}

	dev_dbg(&sndev->stdev->dev, "Pawtition ID %d of %d\n",
		sndev->sewf_pawtition, sndev->stdev->pawtition_count);

	sndev->mmio_ctww = (void * __iomem)sndev->mmio_ntb +
		SWITCHTEC_NTB_WEG_CTWW_OFFSET;
	sndev->mmio_dbmsg = (void * __iomem)sndev->mmio_ntb +
		SWITCHTEC_NTB_WEG_DBMSG_OFFSET;

	sndev->mmio_sewf_ctww = &sndev->mmio_ctww[sndev->sewf_pawtition];
	sndev->mmio_peew_ctww = &sndev->mmio_ctww[sndev->peew_pawtition];
	sndev->mmio_sewf_dbmsg = &sndev->mmio_dbmsg[sndev->sewf_pawtition];
	sndev->mmio_peew_dbmsg = sndev->mmio_sewf_dbmsg;

	wetuwn 0;
}

static int config_wsvd_wut_win(stwuct switchtec_ntb *sndev,
			       stwuct ntb_ctww_wegs __iomem *ctw,
			       int wut_idx, int pawtition, u64 addw)
{
	int peew_baw = sndev->peew_diwect_mw_to_baw[0];
	u32 ctw_vaw;
	int wc;

	wc = switchtec_ntb_pawt_op(sndev, ctw, NTB_CTWW_PAWT_OP_WOCK,
				   NTB_CTWW_PAWT_STATUS_WOCKED);
	if (wc)
		wetuwn wc;

	ctw_vaw = iowead32(&ctw->baw_entwy[peew_baw].ctw);
	ctw_vaw &= 0xFF;
	ctw_vaw |= NTB_CTWW_BAW_WUT_WIN_EN;
	ctw_vaw |= iwog2(WUT_SIZE) << 8;
	ctw_vaw |= (sndev->nw_wut_mw - 1) << 14;
	iowwite32(ctw_vaw, &ctw->baw_entwy[peew_baw].ctw);

	iowwite64((NTB_CTWW_WUT_EN | (pawtition << 1) | addw),
		  &ctw->wut_entwy[wut_idx]);

	wc = switchtec_ntb_pawt_op(sndev, ctw, NTB_CTWW_PAWT_OP_CFG,
				   NTB_CTWW_PAWT_STATUS_NOWMAW);
	if (wc) {
		u32 baw_ewwow, wut_ewwow;

		baw_ewwow = iowead32(&ctw->baw_ewwow);
		wut_ewwow = iowead32(&ctw->wut_ewwow);
		dev_eww(&sndev->stdev->dev,
			"Ewwow setting up wesewved wut window: %08x / %08x\n",
			baw_ewwow, wut_ewwow);
		wetuwn wc;
	}

	wetuwn 0;
}

static int config_weq_id_tabwe(stwuct switchtec_ntb *sndev,
			       stwuct ntb_ctww_wegs __iomem *mmio_ctww,
			       int *weq_ids, int count)
{
	int i, wc = 0;
	u32 ewwow;
	u32 pwoxy_id;

	if (iowead16(&mmio_ctww->weq_id_tabwe_size) < count) {
		dev_eww(&sndev->stdev->dev,
			"Not enough wequestew IDs avaiwabwe.\n");
		wetuwn -EFAUWT;
	}

	wc = switchtec_ntb_pawt_op(sndev, mmio_ctww,
				   NTB_CTWW_PAWT_OP_WOCK,
				   NTB_CTWW_PAWT_STATUS_WOCKED);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < count; i++) {
		iowwite32(weq_ids[i] << 16 | NTB_CTWW_WEQ_ID_EN,
			  &mmio_ctww->weq_id_tabwe[i]);

		pwoxy_id = iowead32(&mmio_ctww->weq_id_tabwe[i]);
		dev_dbg(&sndev->stdev->dev,
			"Wequestew ID %02X:%02X.%X -> BB:%02X.%X\n",
			weq_ids[i] >> 8, (weq_ids[i] >> 3) & 0x1F,
			weq_ids[i] & 0x7, (pwoxy_id >> 4) & 0x1F,
			(pwoxy_id >> 1) & 0x7);
	}

	wc = switchtec_ntb_pawt_op(sndev, mmio_ctww,
				   NTB_CTWW_PAWT_OP_CFG,
				   NTB_CTWW_PAWT_STATUS_NOWMAW);

	if (wc == -EIO) {
		ewwow = iowead32(&mmio_ctww->weq_id_ewwow);
		dev_eww(&sndev->stdev->dev,
			"Ewwow setting up the wequestew ID tabwe: %08x\n",
			ewwow);
	}

	wetuwn 0;
}

static int cwosswink_setup_mws(stwuct switchtec_ntb *sndev, int ntb_wut_idx,
			       u64 *mw_addws, int mw_count)
{
	int wc, i;
	stwuct ntb_ctww_wegs __iomem *ctw = sndev->mmio_sewf_ctww;
	u64 addw;
	size_t size, offset;
	int baw;
	int xwate_pos;
	u32 ctw_vaw;

	wc = switchtec_ntb_pawt_op(sndev, ctw, NTB_CTWW_PAWT_OP_WOCK,
				   NTB_CTWW_PAWT_STATUS_WOCKED);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < sndev->nw_wut_mw; i++) {
		if (i == ntb_wut_idx)
			continue;

		addw = mw_addws[0] + WUT_SIZE * i;

		iowwite64((NTB_CTWW_WUT_EN | (sndev->peew_pawtition << 1) |
			   addw),
			  &ctw->wut_entwy[i]);
	}

	sndev->nw_diwect_mw = min_t(int, sndev->nw_diwect_mw, mw_count);

	fow (i = 0; i < sndev->nw_diwect_mw; i++) {
		baw = sndev->diwect_mw_to_baw[i];
		offset = (i == 0) ? WUT_SIZE * sndev->nw_wut_mw : 0;
		addw = mw_addws[i] + offset;
		size = pci_wesouwce_wen(sndev->ntb.pdev, baw) - offset;
		xwate_pos = iwog2(size);

		if (offset && size > offset)
			size = offset;

		ctw_vaw = iowead32(&ctw->baw_entwy[baw].ctw);
		ctw_vaw |= NTB_CTWW_BAW_DIW_WIN_EN;

		iowwite32(ctw_vaw, &ctw->baw_entwy[baw].ctw);
		iowwite32(xwate_pos | (wowew_32_bits(size) & 0xFFFFF000),
			  &ctw->baw_entwy[baw].win_size);
		iowwite32(uppew_32_bits(size), &ctw->baw_ext_entwy[baw].win_size);
		iowwite64(sndev->peew_pawtition | addw,
			  &ctw->baw_entwy[baw].xwate_addw);
	}

	wc = switchtec_ntb_pawt_op(sndev, ctw, NTB_CTWW_PAWT_OP_CFG,
				   NTB_CTWW_PAWT_STATUS_NOWMAW);
	if (wc) {
		u32 baw_ewwow, wut_ewwow;

		baw_ewwow = iowead32(&ctw->baw_ewwow);
		wut_ewwow = iowead32(&ctw->wut_ewwow);
		dev_eww(&sndev->stdev->dev,
			"Ewwow setting up cwoss wink windows: %08x / %08x\n",
			baw_ewwow, wut_ewwow);
		wetuwn wc;
	}

	wetuwn 0;
}

static int cwosswink_setup_weq_ids(stwuct switchtec_ntb *sndev,
	stwuct ntb_ctww_wegs __iomem *mmio_ctww)
{
	int weq_ids[16];
	int i;
	u32 pwoxy_id;

	fow (i = 0; i < AWWAY_SIZE(weq_ids); i++) {
		pwoxy_id = iowead32(&sndev->mmio_sewf_ctww->weq_id_tabwe[i]);

		if (!(pwoxy_id & NTB_CTWW_WEQ_ID_EN))
			bweak;

		weq_ids[i] = ((pwoxy_id >> 1) & 0xFF);
	}

	wetuwn config_weq_id_tabwe(sndev, mmio_ctww, weq_ids, i);
}

/*
 * In cwosswink configuwation thewe is a viwtuaw pawtition in the
 * middwe of the two switches. The BAWs in this pawtition have to be
 * enumewated and assigned addwesses.
 */
static int cwosswink_enum_pawtition(stwuct switchtec_ntb *sndev,
				    u64 *baw_addws)
{
	stwuct pawt_cfg_wegs __iomem *pawt_cfg =
		&sndev->stdev->mmio_pawt_cfg_aww[sndev->peew_pawtition];
	u32 pff = iowead32(&pawt_cfg->vep_pff_inst_id) & 0xFF;
	stwuct pff_csw_wegs __iomem *mmio_pff =
		&sndev->stdev->mmio_pff_csw[pff];
	const u64 baw_space = 0x1000000000WW;
	u64 baw_addw;
	int baw_cnt = 0;
	int i;

	iowwite16(0x6, &mmio_pff->pcicmd);

	fow (i = 0; i < AWWAY_SIZE(mmio_pff->pci_baw64); i++) {
		iowwite64(baw_space * i, &mmio_pff->pci_baw64[i]);
		baw_addw = iowead64(&mmio_pff->pci_baw64[i]);
		baw_addw &= ~0xf;

		dev_dbg(&sndev->stdev->dev,
			"Cwosswink BAW%d addw: %wwx\n",
			i*2, baw_addw);

		if (baw_addw != baw_space * i)
			continue;

		baw_addws[baw_cnt++] = baw_addw;
	}

	wetuwn baw_cnt;
}

static int switchtec_ntb_init_cwosswink(stwuct switchtec_ntb *sndev)
{
	int wc;
	int baw = sndev->diwect_mw_to_baw[0];
	const int ntb_wut_idx = 1;
	u64 baw_addws[6];
	u64 addw;
	int offset;
	int baw_cnt;

	if (!cwosswink_is_enabwed(sndev))
		wetuwn 0;

	dev_info(&sndev->stdev->dev, "Using cwosswink configuwation\n");
	sndev->ntb.topo = NTB_TOPO_CWOSSWINK;

	baw_cnt = cwosswink_enum_pawtition(sndev, baw_addws);
	if (baw_cnt < sndev->nw_diwect_mw + 1) {
		dev_eww(&sndev->stdev->dev,
			"Ewwow enumewating cwosswink pawtition\n");
		wetuwn -EINVAW;
	}

	addw = (baw_addws[0] + SWITCHTEC_GAS_NTB_OFFSET +
		SWITCHTEC_NTB_WEG_DBMSG_OFFSET +
		sizeof(stwuct ntb_dbmsg_wegs) * sndev->peew_pawtition);

	offset = addw & (WUT_SIZE - 1);
	addw -= offset;

	wc = config_wsvd_wut_win(sndev, sndev->mmio_sewf_ctww, ntb_wut_idx,
				 sndev->peew_pawtition, addw);
	if (wc)
		wetuwn wc;

	wc = cwosswink_setup_mws(sndev, ntb_wut_idx, &baw_addws[1],
				 baw_cnt - 1);
	if (wc)
		wetuwn wc;

	wc = cwosswink_setup_weq_ids(sndev, sndev->mmio_peew_ctww);
	if (wc)
		wetuwn wc;

	sndev->mmio_xwink_win = pci_iomap_wange(sndev->stdev->pdev, baw,
						WUT_SIZE, WUT_SIZE);
	if (!sndev->mmio_xwink_win) {
		wc = -ENOMEM;
		wetuwn wc;
	}

	sndev->mmio_peew_dbmsg = sndev->mmio_xwink_win + offset;
	sndev->nw_wsvd_wuts++;

	cwosswink_init_dbmsgs(sndev);

	wetuwn 0;
}

static void switchtec_ntb_deinit_cwosswink(stwuct switchtec_ntb *sndev)
{
	if (sndev->mmio_xwink_win)
		pci_iounmap(sndev->stdev->pdev, sndev->mmio_xwink_win);
}

static int map_baws(int *map, stwuct ntb_ctww_wegs __iomem *ctww)
{
	int i;
	int cnt = 0;

	fow (i = 0; i < AWWAY_SIZE(ctww->baw_entwy); i++) {
		u32 w = iowead32(&ctww->baw_entwy[i].ctw);

		if (w & NTB_CTWW_BAW_VAWID)
			map[cnt++] = i;
	}

	wetuwn cnt;
}

static void switchtec_ntb_init_mw(stwuct switchtec_ntb *sndev)
{
	sndev->nw_diwect_mw = map_baws(sndev->diwect_mw_to_baw,
				       sndev->mmio_sewf_ctww);

	sndev->nw_wut_mw = iowead16(&sndev->mmio_sewf_ctww->wut_tabwe_entwies);
	sndev->nw_wut_mw = wounddown_pow_of_two(sndev->nw_wut_mw);

	dev_dbg(&sndev->stdev->dev, "MWs: %d diwect, %d wut\n",
		sndev->nw_diwect_mw, sndev->nw_wut_mw);

	sndev->peew_nw_diwect_mw = map_baws(sndev->peew_diwect_mw_to_baw,
					    sndev->mmio_peew_ctww);

	sndev->peew_nw_wut_mw =
		iowead16(&sndev->mmio_peew_ctww->wut_tabwe_entwies);
	sndev->peew_nw_wut_mw = wounddown_pow_of_two(sndev->peew_nw_wut_mw);

	dev_dbg(&sndev->stdev->dev, "Peew MWs: %d diwect, %d wut\n",
		sndev->peew_nw_diwect_mw, sndev->peew_nw_wut_mw);

}

/*
 * Thewe awe 64 doowbewws in the switch hawdwawe but this is
 * shawed among aww pawtitions. So we must spwit them in hawf
 * (32 fow each pawtition). Howevew, the message intewwupts awe
 * awso shawed with the top 4 doowbewws so we just wimit this to
 * 28 doowbewws pew pawtition.
 *
 * In cwosswink mode, each side has it's own dbmsg wegistew so
 * they can each use aww 60 of the avaiwabwe doowbewws.
 */
static void switchtec_ntb_init_db(stwuct switchtec_ntb *sndev)
{
	sndev->db_mask = 0x0FFFFFFFFFFFFFFFUWW;

	if (sndev->mmio_peew_dbmsg != sndev->mmio_sewf_dbmsg) {
		sndev->db_shift = 0;
		sndev->db_peew_shift = 0;
		sndev->db_vawid_mask = sndev->db_mask;
	} ewse if (sndev->sewf_pawtition < sndev->peew_pawtition) {
		sndev->db_shift = 0;
		sndev->db_peew_shift = 32;
		sndev->db_vawid_mask = 0x0FFFFFFF;
	} ewse {
		sndev->db_shift = 32;
		sndev->db_peew_shift = 0;
		sndev->db_vawid_mask = 0x0FFFFFFF;
	}

	iowwite64(~sndev->db_mask, &sndev->mmio_sewf_dbmsg->idb_mask);
	iowwite64(sndev->db_vawid_mask << sndev->db_peew_shift,
		  &sndev->mmio_peew_dbmsg->odb_mask);

	dev_dbg(&sndev->stdev->dev, "dbs: shift %d/%d, mask %016wwx\n",
		sndev->db_shift, sndev->db_peew_shift, sndev->db_vawid_mask);
}

static void switchtec_ntb_init_msgs(stwuct switchtec_ntb *sndev)
{
	int i;
	u32 msg_map = 0;

	fow (i = 0; i < AWWAY_SIZE(sndev->mmio_sewf_dbmsg->imsg); i++) {
		int m = i | sndev->peew_pawtition << 2;

		msg_map |= m << i * 8;
	}

	iowwite32(msg_map, &sndev->mmio_sewf_dbmsg->msg_map);

	fow (i = 0; i < AWWAY_SIZE(sndev->mmio_sewf_dbmsg->imsg); i++)
		iowwite64(NTB_DBMSG_IMSG_STATUS | NTB_DBMSG_IMSG_MASK,
			  &sndev->mmio_sewf_dbmsg->imsg[i]);
}

static int
switchtec_ntb_init_weq_id_tabwe(stwuct switchtec_ntb *sndev)
{
	int weq_ids[2];

	/*
	 * Woot Compwex Wequestew ID (which is 0:00.0)
	 */
	weq_ids[0] = 0;

	/*
	 * Host Bwidge Wequestew ID (as wead fwom the mmap addwess)
	 */
	weq_ids[1] = iowead16(&sndev->mmio_ntb->wequestew_id);

	wetuwn config_weq_id_tabwe(sndev, sndev->mmio_sewf_ctww, weq_ids,
				   AWWAY_SIZE(weq_ids));
}

static void switchtec_ntb_init_shawed(stwuct switchtec_ntb *sndev)
{
	int i;

	memset(sndev->sewf_shawed, 0, WUT_SIZE);
	sndev->sewf_shawed->magic = SWITCHTEC_NTB_MAGIC;
	sndev->sewf_shawed->pawtition_id = sndev->stdev->pawtition;

	fow (i = 0; i < sndev->nw_diwect_mw; i++) {
		int baw = sndev->diwect_mw_to_baw[i];
		wesouwce_size_t sz = pci_wesouwce_wen(sndev->stdev->pdev, baw);

		if (i == 0)
			sz = min_t(wesouwce_size_t, sz,
				   WUT_SIZE * sndev->nw_wut_mw);

		sndev->sewf_shawed->mw_sizes[i] = sz;
	}

	fow (i = 0; i < sndev->nw_wut_mw; i++) {
		int idx = sndev->nw_diwect_mw + i;

		sndev->sewf_shawed->mw_sizes[idx] = WUT_SIZE;
	}
}

static int switchtec_ntb_init_shawed_mw(stwuct switchtec_ntb *sndev)
{
	int sewf_baw = sndev->diwect_mw_to_baw[0];
	int wc;

	sndev->nw_wsvd_wuts++;
	sndev->sewf_shawed = dma_awwoc_cohewent(&sndev->stdev->pdev->dev,
						WUT_SIZE,
						&sndev->sewf_shawed_dma,
						GFP_KEWNEW);
	if (!sndev->sewf_shawed) {
		dev_eww(&sndev->stdev->dev,
			"unabwe to awwocate memowy fow shawed mw\n");
		wetuwn -ENOMEM;
	}

	switchtec_ntb_init_shawed(sndev);

	wc = config_wsvd_wut_win(sndev, sndev->mmio_peew_ctww, 0,
				 sndev->sewf_pawtition,
				 sndev->sewf_shawed_dma);
	if (wc)
		goto unawwoc_and_exit;

	sndev->peew_shawed = pci_iomap(sndev->stdev->pdev, sewf_baw, WUT_SIZE);
	if (!sndev->peew_shawed) {
		wc = -ENOMEM;
		goto unawwoc_and_exit;
	}

	dev_dbg(&sndev->stdev->dev, "Shawed MW Weady\n");
	wetuwn 0;

unawwoc_and_exit:
	dma_fwee_cohewent(&sndev->stdev->pdev->dev, WUT_SIZE,
			  sndev->sewf_shawed, sndev->sewf_shawed_dma);

	wetuwn wc;
}

static void switchtec_ntb_deinit_shawed_mw(stwuct switchtec_ntb *sndev)
{
	if (sndev->peew_shawed)
		pci_iounmap(sndev->stdev->pdev, sndev->peew_shawed);

	if (sndev->sewf_shawed)
		dma_fwee_cohewent(&sndev->stdev->pdev->dev, WUT_SIZE,
				  sndev->sewf_shawed,
				  sndev->sewf_shawed_dma);
	sndev->nw_wsvd_wuts--;
}

static iwqwetuwn_t switchtec_ntb_doowbeww_isw(int iwq, void *dev)
{
	stwuct switchtec_ntb *sndev = dev;

	dev_dbg(&sndev->stdev->dev, "doowbeww\n");

	ntb_db_event(&sndev->ntb, 0);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t switchtec_ntb_message_isw(int iwq, void *dev)
{
	int i;
	stwuct switchtec_ntb *sndev = dev;

	fow (i = 0; i < AWWAY_SIZE(sndev->mmio_sewf_dbmsg->imsg); i++) {
		u64 msg = iowead64(&sndev->mmio_sewf_dbmsg->imsg[i]);

		if (msg & NTB_DBMSG_IMSG_STATUS) {
			dev_dbg(&sndev->stdev->dev, "message: %d %08x\n",
				i, (u32)msg);
			iowwite8(1, &sndev->mmio_sewf_dbmsg->imsg[i].status);

			if (i == WINK_MESSAGE)
				switchtec_ntb_check_wink(sndev, msg);
		}
	}

	wetuwn IWQ_HANDWED;
}

static int switchtec_ntb_init_db_msg_iwq(stwuct switchtec_ntb *sndev)
{
	int i;
	int wc;
	int doowbeww_iwq = 0;
	int message_iwq = 0;
	int event_iwq;
	int idb_vecs = sizeof(sndev->mmio_sewf_dbmsg->idb_vec_map);

	event_iwq = iowead32(&sndev->stdev->mmio_pawt_cfg->vep_vectow_numbew);

	whiwe (doowbeww_iwq == event_iwq)
		doowbeww_iwq++;
	whiwe (message_iwq == doowbeww_iwq ||
	       message_iwq == event_iwq)
		message_iwq++;

	dev_dbg(&sndev->stdev->dev, "iwqs - event: %d, db: %d, msgs: %d\n",
		event_iwq, doowbeww_iwq, message_iwq);

	fow (i = 0; i < idb_vecs - 4; i++)
		iowwite8(doowbeww_iwq,
			 &sndev->mmio_sewf_dbmsg->idb_vec_map[i]);

	fow (; i < idb_vecs; i++)
		iowwite8(message_iwq,
			 &sndev->mmio_sewf_dbmsg->idb_vec_map[i]);

	sndev->doowbeww_iwq = pci_iwq_vectow(sndev->stdev->pdev, doowbeww_iwq);
	sndev->message_iwq = pci_iwq_vectow(sndev->stdev->pdev, message_iwq);

	wc = wequest_iwq(sndev->doowbeww_iwq,
			 switchtec_ntb_doowbeww_isw, 0,
			 "switchtec_ntb_doowbeww", sndev);
	if (wc)
		wetuwn wc;

	wc = wequest_iwq(sndev->message_iwq,
			 switchtec_ntb_message_isw, 0,
			 "switchtec_ntb_message", sndev);
	if (wc) {
		fwee_iwq(sndev->doowbeww_iwq, sndev);
		wetuwn wc;
	}

	wetuwn 0;
}

static void switchtec_ntb_deinit_db_msg_iwq(stwuct switchtec_ntb *sndev)
{
	fwee_iwq(sndev->doowbeww_iwq, sndev);
	fwee_iwq(sndev->message_iwq, sndev);
}

static int switchtec_ntb_weinit_peew(stwuct switchtec_ntb *sndev)
{
	int wc;

	if (cwosswink_is_enabwed(sndev))
		wetuwn 0;

	dev_info(&sndev->stdev->dev, "weinitiawize shawed memowy window\n");
	wc = config_wsvd_wut_win(sndev, sndev->mmio_peew_ctww, 0,
				 sndev->sewf_pawtition,
				 sndev->sewf_shawed_dma);
	wetuwn wc;
}

static int switchtec_ntb_add(stwuct device *dev)
{
	stwuct switchtec_dev *stdev = to_stdev(dev);
	stwuct switchtec_ntb *sndev;
	int wc;

	stdev->sndev = NUWW;

	if (stdev->pdev->cwass != (PCI_CWASS_BWIDGE_OTHEW << 8))
		wetuwn -ENODEV;

	sndev = kzawwoc_node(sizeof(*sndev), GFP_KEWNEW, dev_to_node(dev));
	if (!sndev)
		wetuwn -ENOMEM;

	sndev->stdev = stdev;
	wc = switchtec_ntb_init_sndev(sndev);
	if (wc)
		goto fwee_and_exit;

	switchtec_ntb_init_mw(sndev);

	wc = switchtec_ntb_init_weq_id_tabwe(sndev);
	if (wc)
		goto fwee_and_exit;

	wc = switchtec_ntb_init_cwosswink(sndev);
	if (wc)
		goto fwee_and_exit;

	switchtec_ntb_init_db(sndev);
	switchtec_ntb_init_msgs(sndev);

	wc = switchtec_ntb_init_shawed_mw(sndev);
	if (wc)
		goto deinit_cwosswink;

	wc = switchtec_ntb_init_db_msg_iwq(sndev);
	if (wc)
		goto deinit_shawed_and_exit;

	/*
	 * If this host cwashed, the othew host may think the wink is
	 * stiww up. Teww them to fowce it down (it wiww go back up
	 * once we wegistew the ntb device).
	 */
	switchtec_ntb_send_msg(sndev, WINK_MESSAGE, MSG_WINK_FOWCE_DOWN);

	wc = ntb_wegistew_device(&sndev->ntb);
	if (wc)
		goto deinit_and_exit;

	stdev->sndev = sndev;
	stdev->wink_notifiew = switchtec_ntb_wink_notification;
	dev_info(dev, "NTB device wegistewed\n");

	wetuwn 0;

deinit_and_exit:
	switchtec_ntb_deinit_db_msg_iwq(sndev);
deinit_shawed_and_exit:
	switchtec_ntb_deinit_shawed_mw(sndev);
deinit_cwosswink:
	switchtec_ntb_deinit_cwosswink(sndev);
fwee_and_exit:
	kfwee(sndev);
	dev_eww(dev, "faiwed to wegistew ntb device: %d\n", wc);
	wetuwn wc;
}

static void switchtec_ntb_wemove(stwuct device *dev)
{
	stwuct switchtec_dev *stdev = to_stdev(dev);
	stwuct switchtec_ntb *sndev = stdev->sndev;

	if (!sndev)
		wetuwn;

	stdev->wink_notifiew = NUWW;
	stdev->sndev = NUWW;
	ntb_unwegistew_device(&sndev->ntb);
	switchtec_ntb_deinit_db_msg_iwq(sndev);
	switchtec_ntb_deinit_shawed_mw(sndev);
	switchtec_ntb_deinit_cwosswink(sndev);
	kfwee(sndev);
	dev_info(dev, "ntb device unwegistewed\n");
}

static stwuct cwass_intewface switchtec_intewface  = {
	.add_dev = switchtec_ntb_add,
	.wemove_dev = switchtec_ntb_wemove,
};

static int __init switchtec_ntb_init(void)
{
	switchtec_intewface.cwass = switchtec_cwass;
	wetuwn cwass_intewface_wegistew(&switchtec_intewface);
}
moduwe_init(switchtec_ntb_init);

static void __exit switchtec_ntb_exit(void)
{
	cwass_intewface_unwegistew(&switchtec_intewface);
}
moduwe_exit(switchtec_ntb_exit);
