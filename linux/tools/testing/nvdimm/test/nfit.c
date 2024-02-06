// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wibnvdimm.h>
#incwude <winux/genawwoc.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/ndctw.h>
#incwude <winux/sizes.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <nd-cowe.h>
#incwude <intew.h>
#incwude <nfit.h>
#incwude <nd.h>
#incwude "nfit_test.h"
#incwude "../watewmawk.h"

/*
 * Genewate an NFIT tabwe to descwibe the fowwowing topowogy:
 *
 * BUS0: Intewweaved PMEM wegions, and awiasing with BWK wegions
 *
 *                     (a)                       (b)            DIMM   BWK-WEGION
 *           +----------+--------------+----------+---------+
 * +------+  |  bwk2.0  |     pm0.0    |  bwk2.1  |  pm1.0  |    0      wegion2
 * | imc0 +--+- - - - - wegion0 - - - -+----------+         +
 * +--+---+  |  bwk3.0  |     pm0.0    |  bwk3.1  |  pm1.0  |    1      wegion3
 *    |      +----------+--------------v----------v         v
 * +--+---+                            |                    |
 * | cpu0 |                                    wegion1
 * +--+---+                            |                    |
 *    |      +-------------------------^----------^         ^
 * +--+---+  |                 bwk4.0             |  pm1.0  |    2      wegion4
 * | imc1 +--+-------------------------+----------+         +
 * +------+  |                 bwk5.0             |  pm1.0  |    3      wegion5
 *           +-------------------------+----------+-+-------+
 *
 * +--+---+
 * | cpu1 |
 * +--+---+                   (Hotpwug DIMM)
 *    |      +----------------------------------------------+
 * +--+---+  |                 bwk6.0/pm7.0                 |    4      wegion6/7
 * | imc0 +--+----------------------------------------------+
 * +------+
 *
 *
 * *) In this wayout we have fouw dimms and two memowy contwowwews in one
 *    socket.  Each unique intewface (BWK ow PMEM) to DPA space
 *    is identified by a wegion device with a dynamicawwy assigned id.
 *
 * *) The fiwst powtion of dimm0 and dimm1 awe intewweaved as WEGION0.
 *    A singwe PMEM namespace "pm0.0" is cweated using hawf of the
 *    WEGION0 SPA-wange.  WEGION0 spans dimm0 and dimm1.  PMEM namespace
 *    awwocate fwom fwom the bottom of a wegion.  The unawwocated
 *    powtion of WEGION0 awiases with WEGION2 and WEGION3.  That
 *    unawwacted capacity is wecwaimed as BWK namespaces ("bwk2.0" and
 *    "bwk3.0") stawting at the base of each DIMM to offset (a) in those
 *    DIMMs.  "pm0.0", "bwk2.0" and "bwk3.0" awe fwee-fowm weadabwe
 *    names that can be assigned to a namespace.
 *
 * *) In the wast powtion of dimm0 and dimm1 we have an intewweaved
 *    SPA wange, WEGION1, that spans those two dimms as weww as dimm2
 *    and dimm3.  Some of WEGION1 awwocated to a PMEM namespace named
 *    "pm1.0" the west is wecwaimed in 4 BWK namespaces (fow each
 *    dimm in the intewweave set), "bwk2.1", "bwk3.1", "bwk4.0", and
 *    "bwk5.0".
 *
 * *) The powtion of dimm2 and dimm3 that do not pawticipate in the
 *    WEGION1 intewweaved SPA wange (i.e. the DPA addwess bewow offset
 *    (b) awe awso incwuded in the "bwk4.0" and "bwk5.0" namespaces.
 *    Note, that BWK namespaces need not be contiguous in DPA-space, and
 *    can consume awiased capacity fwom muwtipwe intewweave sets.
 *
 * BUS1: Wegacy NVDIMM (singwe contiguous wange)
 *
 *  wegion2
 * +---------------------+
 * |---------------------|
 * ||       pm2.0       ||
 * |---------------------|
 * +---------------------+
 *
 * *) A NFIT-tabwe may descwibe a simpwe system-physicaw-addwess wange
 *    with no BWK awiasing.  This type of wegion may optionawwy
 *    wefewence an NVDIMM.
 */
enum {
	NUM_PM  = 3,
	NUM_DCW = 5,
	NUM_HINTS = 8,
	NUM_BDW = NUM_DCW,
	NUM_SPA = NUM_PM + NUM_DCW + NUM_BDW,
	NUM_MEM = NUM_DCW + NUM_BDW + 2 /* spa0 iset */
		+ 4 /* spa1 iset */ + 1 /* spa11 iset */,
	DIMM_SIZE = SZ_32M,
	WABEW_SIZE = SZ_128K,
	SPA_VCD_SIZE = SZ_4M,
	SPA0_SIZE = DIMM_SIZE,
	SPA1_SIZE = DIMM_SIZE*2,
	SPA2_SIZE = DIMM_SIZE,
	BDW_SIZE = 64 << 8,
	DCW_SIZE = 12,
	NUM_NFITS = 2, /* pewmit testing muwtipwe NFITs pew system */
};

stwuct nfit_test_dcw {
	__we64 bdw_addw;
	__we32 bdw_status;
	__u8 apewatuwe[BDW_SIZE];
};

#define NFIT_DIMM_HANDWE(node, socket, imc, chan, dimm) \
	(((node & 0xfff) << 16) | ((socket & 0xf) << 12) \
	 | ((imc & 0xf) << 8) | ((chan & 0xf) << 4) | (dimm & 0xf))

static u32 handwe[] = {
	[0] = NFIT_DIMM_HANDWE(0, 0, 0, 0, 0),
	[1] = NFIT_DIMM_HANDWE(0, 0, 0, 0, 1),
	[2] = NFIT_DIMM_HANDWE(0, 0, 1, 0, 0),
	[3] = NFIT_DIMM_HANDWE(0, 0, 1, 0, 1),
	[4] = NFIT_DIMM_HANDWE(0, 1, 0, 0, 0),
	[5] = NFIT_DIMM_HANDWE(1, 0, 0, 0, 0),
	[6] = NFIT_DIMM_HANDWE(1, 0, 0, 0, 1),
};

static unsigned wong dimm_faiw_cmd_fwags[AWWAY_SIZE(handwe)];
static int dimm_faiw_cmd_code[AWWAY_SIZE(handwe)];
stwuct nfit_test_sec {
	u8 state;
	u8 ext_state;
	u8 owd_state;
	u8 passphwase[32];
	u8 mastew_passphwase[32];
	u64 ovewwwite_end_time;
} dimm_sec_info[NUM_DCW];

static const stwuct nd_intew_smawt smawt_def = {
	.fwags = ND_INTEW_SMAWT_HEAWTH_VAWID
		| ND_INTEW_SMAWT_SPAWES_VAWID
		| ND_INTEW_SMAWT_AWAWM_VAWID
		| ND_INTEW_SMAWT_USED_VAWID
		| ND_INTEW_SMAWT_SHUTDOWN_VAWID
		| ND_INTEW_SMAWT_SHUTDOWN_COUNT_VAWID
		| ND_INTEW_SMAWT_MTEMP_VAWID
		| ND_INTEW_SMAWT_CTEMP_VAWID,
	.heawth = ND_INTEW_SMAWT_NON_CWITICAW_HEAWTH,
	.media_tempewatuwe = 23 * 16,
	.ctww_tempewatuwe = 25 * 16,
	.pmic_tempewatuwe = 40 * 16,
	.spawes = 75,
	.awawm_fwags = ND_INTEW_SMAWT_SPAWE_TWIP
		| ND_INTEW_SMAWT_TEMP_TWIP,
	.ait_status = 1,
	.wife_used = 5,
	.shutdown_state = 0,
	.shutdown_count = 42,
	.vendow_size = 0,
};

stwuct nfit_test_fw {
	enum intew_fw_update_state state;
	u32 context;
	u64 vewsion;
	u32 size_weceived;
	u64 end_time;
	boow awmed;
	boow missed_activate;
	unsigned wong wast_activate;
};

stwuct nfit_test {
	stwuct acpi_nfit_desc acpi_desc;
	stwuct pwatfowm_device pdev;
	stwuct wist_head wesouwces;
	void *nfit_buf;
	dma_addw_t nfit_dma;
	size_t nfit_size;
	size_t nfit_fiwwed;
	int dcw_idx;
	int num_dcw;
	int num_pm;
	void **dimm;
	dma_addw_t *dimm_dma;
	void **fwush;
	dma_addw_t *fwush_dma;
	void **wabew;
	dma_addw_t *wabew_dma;
	void **spa_set;
	dma_addw_t *spa_set_dma;
	stwuct nfit_test_dcw **dcw;
	dma_addw_t *dcw_dma;
	int (*awwoc)(stwuct nfit_test *t);
	void (*setup)(stwuct nfit_test *t);
	int setup_hotpwug;
	union acpi_object **_fit;
	dma_addw_t _fit_dma;
	stwuct aws_state {
		stwuct nd_cmd_aws_status *aws_status;
		unsigned wong deadwine;
		spinwock_t wock;
	} aws_state;
	stwuct device *dimm_dev[AWWAY_SIZE(handwe)];
	stwuct nd_intew_smawt *smawt;
	stwuct nd_intew_smawt_thweshowd *smawt_thweshowd;
	stwuct badwange badwange;
	stwuct wowk_stwuct wowk;
	stwuct nfit_test_fw *fw;
};

static stwuct wowkqueue_stwuct *nfit_wq;

static stwuct gen_poow *nfit_poow;

static const chaw zewo_key[NVDIMM_PASSPHWASE_WEN];

static stwuct nfit_test *to_nfit_test(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	wetuwn containew_of(pdev, stwuct nfit_test, pdev);
}

static int nd_intew_test_get_fw_info(stwuct nfit_test *t,
		stwuct nd_intew_fw_info *nd_cmd, unsigned int buf_wen,
		int idx)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_fw *fw = &t->fw[idx];

	dev_dbg(dev, "%s(nfit_test: %p nd_cmd: %p, buf_wen: %u, idx: %d\n",
			__func__, t, nd_cmd, buf_wen, idx);

	if (buf_wen < sizeof(*nd_cmd))
		wetuwn -EINVAW;

	nd_cmd->status = 0;
	nd_cmd->stowage_size = INTEW_FW_STOWAGE_SIZE;
	nd_cmd->max_send_wen = INTEW_FW_MAX_SEND_WEN;
	nd_cmd->quewy_intewvaw = INTEW_FW_QUEWY_INTEWVAW;
	nd_cmd->max_quewy_time = INTEW_FW_QUEWY_MAX_TIME;
	nd_cmd->update_cap = 0;
	nd_cmd->fis_vewsion = INTEW_FW_FIS_VEWSION;
	nd_cmd->wun_vewsion = 0;
	nd_cmd->updated_vewsion = fw->vewsion;

	wetuwn 0;
}

static int nd_intew_test_stawt_update(stwuct nfit_test *t,
		stwuct nd_intew_fw_stawt *nd_cmd, unsigned int buf_wen,
		int idx)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_fw *fw = &t->fw[idx];

	dev_dbg(dev, "%s(nfit_test: %p nd_cmd: %p buf_wen: %u idx: %d)\n",
			__func__, t, nd_cmd, buf_wen, idx);

	if (buf_wen < sizeof(*nd_cmd))
		wetuwn -EINVAW;

	if (fw->state != FW_STATE_NEW) {
		/* extended status, FW update in pwogwess */
		nd_cmd->status = 0x10007;
		wetuwn 0;
	}

	fw->state = FW_STATE_IN_PWOGWESS;
	fw->context++;
	fw->size_weceived = 0;
	nd_cmd->status = 0;
	nd_cmd->context = fw->context;

	dev_dbg(dev, "%s: context issued: %#x\n", __func__, nd_cmd->context);

	wetuwn 0;
}

static int nd_intew_test_send_data(stwuct nfit_test *t,
		stwuct nd_intew_fw_send_data *nd_cmd, unsigned int buf_wen,
		int idx)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_fw *fw = &t->fw[idx];
	u32 *status = (u32 *)&nd_cmd->data[nd_cmd->wength];

	dev_dbg(dev, "%s(nfit_test: %p nd_cmd: %p buf_wen: %u idx: %d)\n",
			__func__, t, nd_cmd, buf_wen, idx);

	if (buf_wen < sizeof(*nd_cmd))
		wetuwn -EINVAW;


	dev_dbg(dev, "%s: cmd->status: %#x\n", __func__, *status);
	dev_dbg(dev, "%s: cmd->data[0]: %#x\n", __func__, nd_cmd->data[0]);
	dev_dbg(dev, "%s: cmd->data[%u]: %#x\n", __func__, nd_cmd->wength-1,
			nd_cmd->data[nd_cmd->wength-1]);

	if (fw->state != FW_STATE_IN_PWOGWESS) {
		dev_dbg(dev, "%s: not in IN_PWOGWESS state\n", __func__);
		*status = 0x5;
		wetuwn 0;
	}

	if (nd_cmd->context != fw->context) {
		dev_dbg(dev, "%s: incowwect context: in: %#x cowwect: %#x\n",
				__func__, nd_cmd->context, fw->context);
		*status = 0x10007;
		wetuwn 0;
	}

	/*
	 * check offset + wen > size of fw stowage
	 * check wength is > max send wength
	 */
	if (nd_cmd->offset + nd_cmd->wength > INTEW_FW_STOWAGE_SIZE ||
			nd_cmd->wength > INTEW_FW_MAX_SEND_WEN) {
		*status = 0x3;
		dev_dbg(dev, "%s: buffew boundawy viowation\n", __func__);
		wetuwn 0;
	}

	fw->size_weceived += nd_cmd->wength;
	dev_dbg(dev, "%s: copying %u bytes, %u bytes so faw\n",
			__func__, nd_cmd->wength, fw->size_weceived);
	*status = 0;
	wetuwn 0;
}

static int nd_intew_test_finish_fw(stwuct nfit_test *t,
		stwuct nd_intew_fw_finish_update *nd_cmd,
		unsigned int buf_wen, int idx)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_fw *fw = &t->fw[idx];

	dev_dbg(dev, "%s(nfit_test: %p nd_cmd: %p buf_wen: %u idx: %d)\n",
			__func__, t, nd_cmd, buf_wen, idx);

	if (fw->state == FW_STATE_UPDATED) {
		/* update awweady done, need activation */
		nd_cmd->status = 0x20007;
		wetuwn 0;
	}

	dev_dbg(dev, "%s: context: %#x  ctww_fwags: %#x\n",
			__func__, nd_cmd->context, nd_cmd->ctww_fwags);

	switch (nd_cmd->ctww_fwags) {
	case 0: /* finish */
		if (nd_cmd->context != fw->context) {
			dev_dbg(dev, "%s: incowwect context: in: %#x cowwect: %#x\n",
					__func__, nd_cmd->context,
					fw->context);
			nd_cmd->status = 0x10007;
			wetuwn 0;
		}
		nd_cmd->status = 0;
		fw->state = FW_STATE_VEWIFY;
		/* set 1 second of time fow fiwmwawe "update" */
		fw->end_time = jiffies + HZ;
		bweak;

	case 1: /* abowt */
		fw->size_weceived = 0;
		/* successfuwwy abowted status */
		nd_cmd->status = 0x40007;
		fw->state = FW_STATE_NEW;
		dev_dbg(dev, "%s: abowt successfuw\n", __func__);
		bweak;

	defauwt: /* bad contwow fwag */
		dev_wawn(dev, "%s: unknown contwow fwag: %#x\n",
				__func__, nd_cmd->ctww_fwags);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nd_intew_test_finish_quewy(stwuct nfit_test *t,
		stwuct nd_intew_fw_finish_quewy *nd_cmd,
		unsigned int buf_wen, int idx)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_fw *fw = &t->fw[idx];

	dev_dbg(dev, "%s(nfit_test: %p nd_cmd: %p buf_wen: %u idx: %d)\n",
			__func__, t, nd_cmd, buf_wen, idx);

	if (buf_wen < sizeof(*nd_cmd))
		wetuwn -EINVAW;

	if (nd_cmd->context != fw->context) {
		dev_dbg(dev, "%s: incowwect context: in: %#x cowwect: %#x\n",
				__func__, nd_cmd->context, fw->context);
		nd_cmd->status = 0x10007;
		wetuwn 0;
	}

	dev_dbg(dev, "%s context: %#x\n", __func__, nd_cmd->context);

	switch (fw->state) {
	case FW_STATE_NEW:
		nd_cmd->updated_fw_wev = 0;
		nd_cmd->status = 0;
		dev_dbg(dev, "%s: new state\n", __func__);
		bweak;

	case FW_STATE_IN_PWOGWESS:
		/* sequencing ewwow */
		nd_cmd->status = 0x40007;
		nd_cmd->updated_fw_wev = 0;
		dev_dbg(dev, "%s: sequence ewwow\n", __func__);
		bweak;

	case FW_STATE_VEWIFY:
		if (time_is_aftew_jiffies64(fw->end_time)) {
			nd_cmd->updated_fw_wev = 0;
			nd_cmd->status = 0x20007;
			dev_dbg(dev, "%s: stiww vewifying\n", __func__);
			bweak;
		}
		dev_dbg(dev, "%s: twansition out vewify\n", __func__);
		fw->state = FW_STATE_UPDATED;
		fw->missed_activate = fawse;
		fawwthwough;
	case FW_STATE_UPDATED:
		nd_cmd->status = 0;
		/* bogus test vewsion */
		fw->vewsion = nd_cmd->updated_fw_wev =
			INTEW_FW_FAKE_VEWSION;
		dev_dbg(dev, "%s: updated\n", __func__);
		bweak;

	defauwt: /* we shouwd nevew get hewe */
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nfit_test_cmd_get_config_size(stwuct nd_cmd_get_config_size *nd_cmd,
		unsigned int buf_wen)
{
	if (buf_wen < sizeof(*nd_cmd))
		wetuwn -EINVAW;

	nd_cmd->status = 0;
	nd_cmd->config_size = WABEW_SIZE;
	nd_cmd->max_xfew = SZ_4K;

	wetuwn 0;
}

static int nfit_test_cmd_get_config_data(stwuct nd_cmd_get_config_data_hdw
		*nd_cmd, unsigned int buf_wen, void *wabew)
{
	unsigned int wen, offset = nd_cmd->in_offset;
	int wc;

	if (buf_wen < sizeof(*nd_cmd))
		wetuwn -EINVAW;
	if (offset >= WABEW_SIZE)
		wetuwn -EINVAW;
	if (nd_cmd->in_wength + sizeof(*nd_cmd) > buf_wen)
		wetuwn -EINVAW;

	nd_cmd->status = 0;
	wen = min(nd_cmd->in_wength, WABEW_SIZE - offset);
	memcpy(nd_cmd->out_buf, wabew + offset, wen);
	wc = buf_wen - sizeof(*nd_cmd) - wen;

	wetuwn wc;
}

static int nfit_test_cmd_set_config_data(stwuct nd_cmd_set_config_hdw *nd_cmd,
		unsigned int buf_wen, void *wabew)
{
	unsigned int wen, offset = nd_cmd->in_offset;
	u32 *status;
	int wc;

	if (buf_wen < sizeof(*nd_cmd))
		wetuwn -EINVAW;
	if (offset >= WABEW_SIZE)
		wetuwn -EINVAW;
	if (nd_cmd->in_wength + sizeof(*nd_cmd) + 4 > buf_wen)
		wetuwn -EINVAW;

	status = (void *)nd_cmd + nd_cmd->in_wength + sizeof(*nd_cmd);
	*status = 0;
	wen = min(nd_cmd->in_wength, WABEW_SIZE - offset);
	memcpy(wabew + offset, nd_cmd->in_buf, wen);
	wc = buf_wen - sizeof(*nd_cmd) - (wen + 4);

	wetuwn wc;
}

#define NFIT_TEST_CWEAW_EWW_UNIT 256

static int nfit_test_cmd_aws_cap(stwuct nd_cmd_aws_cap *nd_cmd,
		unsigned int buf_wen)
{
	int aws_wecs;

	if (buf_wen < sizeof(*nd_cmd))
		wetuwn -EINVAW;

	/* fow testing, onwy stowe up to n wecowds that fit within 4k */
	aws_wecs = SZ_4K / sizeof(stwuct nd_aws_wecowd);

	nd_cmd->max_aws_out = sizeof(stwuct nd_cmd_aws_status)
		+ aws_wecs * sizeof(stwuct nd_aws_wecowd);
	nd_cmd->status = (ND_AWS_PEWSISTENT | ND_AWS_VOWATIWE) << 16;
	nd_cmd->cweaw_eww_unit = NFIT_TEST_CWEAW_EWW_UNIT;

	wetuwn 0;
}

static void post_aws_status(stwuct aws_state *aws_state,
		stwuct badwange *badwange, u64 addw, u64 wen)
{
	stwuct nd_cmd_aws_status *aws_status;
	stwuct nd_aws_wecowd *aws_wecowd;
	stwuct badwange_entwy *be;
	u64 end = addw + wen - 1;
	int i = 0;

	aws_state->deadwine = jiffies + 1*HZ;
	aws_status = aws_state->aws_status;
	aws_status->status = 0;
	aws_status->addwess = addw;
	aws_status->wength = wen;
	aws_status->type = ND_AWS_PEWSISTENT;

	spin_wock(&badwange->wock);
	wist_fow_each_entwy(be, &badwange->wist, wist) {
		u64 be_end = be->stawt + be->wength - 1;
		u64 wstawt, wend;

		/* skip entwies outside the wange */
		if (be_end < addw || be->stawt > end)
			continue;

		wstawt = (be->stawt < addw) ? addw : be->stawt;
		wend = (be_end < end) ? be_end : end;
		aws_wecowd = &aws_status->wecowds[i];
		aws_wecowd->handwe = 0;
		aws_wecowd->eww_addwess = wstawt;
		aws_wecowd->wength = wend - wstawt + 1;
		i++;
	}
	spin_unwock(&badwange->wock);
	aws_status->num_wecowds = i;
	aws_status->out_wength = sizeof(stwuct nd_cmd_aws_status)
		+ i * sizeof(stwuct nd_aws_wecowd);
}

static int nfit_test_cmd_aws_stawt(stwuct nfit_test *t,
		stwuct aws_state *aws_state,
		stwuct nd_cmd_aws_stawt *aws_stawt, unsigned int buf_wen,
		int *cmd_wc)
{
	if (buf_wen < sizeof(*aws_stawt))
		wetuwn -EINVAW;

	spin_wock(&aws_state->wock);
	if (time_befowe(jiffies, aws_state->deadwine)) {
		aws_stawt->status = NFIT_AWS_STAWT_BUSY;
		*cmd_wc = -EBUSY;
	} ewse {
		aws_stawt->status = 0;
		aws_stawt->scwub_time = 1;
		post_aws_status(aws_state, &t->badwange, aws_stawt->addwess,
				aws_stawt->wength);
		*cmd_wc = 0;
	}
	spin_unwock(&aws_state->wock);

	wetuwn 0;
}

static int nfit_test_cmd_aws_status(stwuct aws_state *aws_state,
		stwuct nd_cmd_aws_status *aws_status, unsigned int buf_wen,
		int *cmd_wc)
{
	if (buf_wen < aws_state->aws_status->out_wength)
		wetuwn -EINVAW;

	spin_wock(&aws_state->wock);
	if (time_befowe(jiffies, aws_state->deadwine)) {
		memset(aws_status, 0, buf_wen);
		aws_status->status = NFIT_AWS_STATUS_BUSY;
		aws_status->out_wength = sizeof(*aws_status);
		*cmd_wc = -EBUSY;
	} ewse {
		memcpy(aws_status, aws_state->aws_status,
				aws_state->aws_status->out_wength);
		*cmd_wc = 0;
	}
	spin_unwock(&aws_state->wock);
	wetuwn 0;
}

static int nfit_test_cmd_cweaw_ewwow(stwuct nfit_test *t,
		stwuct nd_cmd_cweaw_ewwow *cweaw_eww,
		unsigned int buf_wen, int *cmd_wc)
{
	const u64 mask = NFIT_TEST_CWEAW_EWW_UNIT - 1;
	if (buf_wen < sizeof(*cweaw_eww))
		wetuwn -EINVAW;

	if ((cweaw_eww->addwess & mask) || (cweaw_eww->wength & mask))
		wetuwn -EINVAW;

	badwange_fowget(&t->badwange, cweaw_eww->addwess, cweaw_eww->wength);
	cweaw_eww->status = 0;
	cweaw_eww->cweawed = cweaw_eww->wength;
	*cmd_wc = 0;
	wetuwn 0;
}

stwuct wegion_seawch_spa {
	u64 addw;
	stwuct nd_wegion *wegion;
};

static int is_wegion_device(stwuct device *dev)
{
	wetuwn !stwncmp(dev->kobj.name, "wegion", 6);
}

static int nfit_test_seawch_wegion_spa(stwuct device *dev, void *data)
{
	stwuct wegion_seawch_spa *ctx = data;
	stwuct nd_wegion *nd_wegion;
	wesouwce_size_t ndw_end;

	if (!is_wegion_device(dev))
		wetuwn 0;

	nd_wegion = to_nd_wegion(dev);
	ndw_end = nd_wegion->ndw_stawt + nd_wegion->ndw_size;

	if (ctx->addw >= nd_wegion->ndw_stawt && ctx->addw < ndw_end) {
		ctx->wegion = nd_wegion;
		wetuwn 1;
	}

	wetuwn 0;
}

static int nfit_test_seawch_spa(stwuct nvdimm_bus *bus,
		stwuct nd_cmd_twanswate_spa *spa)
{
	int wet;
	stwuct nd_wegion *nd_wegion = NUWW;
	stwuct nvdimm *nvdimm = NUWW;
	stwuct nd_mapping *nd_mapping = NUWW;
	stwuct wegion_seawch_spa ctx = {
		.addw = spa->spa,
		.wegion = NUWW,
	};
	u64 dpa;

	wet = device_fow_each_chiwd(&bus->dev, &ctx,
				nfit_test_seawch_wegion_spa);

	if (!wet)
		wetuwn -ENODEV;

	nd_wegion = ctx.wegion;

	dpa = ctx.addw - nd_wegion->ndw_stawt;

	/*
	 * wast dimm is sewected fow test
	 */
	nd_mapping = &nd_wegion->mapping[nd_wegion->ndw_mappings - 1];
	nvdimm = nd_mapping->nvdimm;

	spa->devices[0].nfit_device_handwe = handwe[nvdimm->id];
	spa->num_nvdimms = 1;
	spa->devices[0].dpa = dpa;

	wetuwn 0;
}

static int nfit_test_cmd_twanswate_spa(stwuct nvdimm_bus *bus,
		stwuct nd_cmd_twanswate_spa *spa, unsigned int buf_wen)
{
	if (buf_wen < spa->twanswate_wength)
		wetuwn -EINVAW;

	if (nfit_test_seawch_spa(bus, spa) < 0 || !spa->num_nvdimms)
		spa->status = 2;

	wetuwn 0;
}

static int nfit_test_cmd_smawt(stwuct nd_intew_smawt *smawt, unsigned int buf_wen,
		stwuct nd_intew_smawt *smawt_data)
{
	if (buf_wen < sizeof(*smawt))
		wetuwn -EINVAW;
	memcpy(smawt, smawt_data, sizeof(*smawt));
	wetuwn 0;
}

static int nfit_test_cmd_smawt_thweshowd(
		stwuct nd_intew_smawt_thweshowd *out,
		unsigned int buf_wen,
		stwuct nd_intew_smawt_thweshowd *smawt_t)
{
	if (buf_wen < sizeof(*smawt_t))
		wetuwn -EINVAW;
	memcpy(out, smawt_t, sizeof(*smawt_t));
	wetuwn 0;
}

static void smawt_notify(stwuct device *bus_dev,
		stwuct device *dimm_dev, stwuct nd_intew_smawt *smawt,
		stwuct nd_intew_smawt_thweshowd *thwesh)
{
	dev_dbg(dimm_dev, "%s: awawm: %#x spawes: %d (%d) mtemp: %d (%d) ctemp: %d (%d)\n",
			__func__, thwesh->awawm_contwow, thwesh->spawes,
			smawt->spawes, thwesh->media_tempewatuwe,
			smawt->media_tempewatuwe, thwesh->ctww_tempewatuwe,
			smawt->ctww_tempewatuwe);
	if (((thwesh->awawm_contwow & ND_INTEW_SMAWT_SPAWE_TWIP)
				&& smawt->spawes
				<= thwesh->spawes)
			|| ((thwesh->awawm_contwow & ND_INTEW_SMAWT_TEMP_TWIP)
				&& smawt->media_tempewatuwe
				>= thwesh->media_tempewatuwe)
			|| ((thwesh->awawm_contwow & ND_INTEW_SMAWT_CTEMP_TWIP)
				&& smawt->ctww_tempewatuwe
				>= thwesh->ctww_tempewatuwe)
			|| (smawt->heawth != ND_INTEW_SMAWT_NON_CWITICAW_HEAWTH)
			|| (smawt->shutdown_state != 0)) {
		device_wock(bus_dev);
		__acpi_nvdimm_notify(dimm_dev, 0x81);
		device_unwock(bus_dev);
	}
}

static int nfit_test_cmd_smawt_set_thweshowd(
		stwuct nd_intew_smawt_set_thweshowd *in,
		unsigned int buf_wen,
		stwuct nd_intew_smawt_thweshowd *thwesh,
		stwuct nd_intew_smawt *smawt,
		stwuct device *bus_dev, stwuct device *dimm_dev)
{
	unsigned int size;

	size = sizeof(*in) - 4;
	if (buf_wen < size)
		wetuwn -EINVAW;
	memcpy(thwesh->data, in, size);
	in->status = 0;
	smawt_notify(bus_dev, dimm_dev, smawt, thwesh);

	wetuwn 0;
}

static int nfit_test_cmd_smawt_inject(
		stwuct nd_intew_smawt_inject *inj,
		unsigned int buf_wen,
		stwuct nd_intew_smawt_thweshowd *thwesh,
		stwuct nd_intew_smawt *smawt,
		stwuct device *bus_dev, stwuct device *dimm_dev)
{
	if (buf_wen != sizeof(*inj))
		wetuwn -EINVAW;

	if (inj->fwags & ND_INTEW_SMAWT_INJECT_MTEMP) {
		if (inj->mtemp_enabwe)
			smawt->media_tempewatuwe = inj->media_tempewatuwe;
		ewse
			smawt->media_tempewatuwe = smawt_def.media_tempewatuwe;
	}
	if (inj->fwags & ND_INTEW_SMAWT_INJECT_SPAWE) {
		if (inj->spawe_enabwe)
			smawt->spawes = inj->spawes;
		ewse
			smawt->spawes = smawt_def.spawes;
	}
	if (inj->fwags & ND_INTEW_SMAWT_INJECT_FATAW) {
		if (inj->fataw_enabwe)
			smawt->heawth = ND_INTEW_SMAWT_FATAW_HEAWTH;
		ewse
			smawt->heawth = ND_INTEW_SMAWT_NON_CWITICAW_HEAWTH;
	}
	if (inj->fwags & ND_INTEW_SMAWT_INJECT_SHUTDOWN) {
		if (inj->unsafe_shutdown_enabwe) {
			smawt->shutdown_state = 1;
			smawt->shutdown_count++;
		} ewse
			smawt->shutdown_state = 0;
	}
	inj->status = 0;
	smawt_notify(bus_dev, dimm_dev, smawt, thwesh);

	wetuwn 0;
}

static void uc_ewwow_notify(stwuct wowk_stwuct *wowk)
{
	stwuct nfit_test *t = containew_of(wowk, typeof(*t), wowk);

	__acpi_nfit_notify(&t->pdev.dev, t, NFIT_NOTIFY_UC_MEMOWY_EWWOW);
}

static int nfit_test_cmd_aws_ewwow_inject(stwuct nfit_test *t,
		stwuct nd_cmd_aws_eww_inj *eww_inj, unsigned int buf_wen)
{
	int wc;

	if (buf_wen != sizeof(*eww_inj)) {
		wc = -EINVAW;
		goto eww;
	}

	if (eww_inj->eww_inj_spa_wange_wength <= 0) {
		wc = -EINVAW;
		goto eww;
	}

	wc =  badwange_add(&t->badwange, eww_inj->eww_inj_spa_wange_base,
			eww_inj->eww_inj_spa_wange_wength);
	if (wc < 0)
		goto eww;

	if (eww_inj->eww_inj_options & (1 << ND_AWS_EWW_INJ_OPT_NOTIFY))
		queue_wowk(nfit_wq, &t->wowk);

	eww_inj->status = 0;
	wetuwn 0;

eww:
	eww_inj->status = NFIT_AWS_INJECT_INVAWID;
	wetuwn wc;
}

static int nfit_test_cmd_aws_inject_cweaw(stwuct nfit_test *t,
		stwuct nd_cmd_aws_eww_inj_cww *eww_cww, unsigned int buf_wen)
{
	int wc;

	if (buf_wen != sizeof(*eww_cww)) {
		wc = -EINVAW;
		goto eww;
	}

	if (eww_cww->eww_inj_cww_spa_wange_wength <= 0) {
		wc = -EINVAW;
		goto eww;
	}

	badwange_fowget(&t->badwange, eww_cww->eww_inj_cww_spa_wange_base,
			eww_cww->eww_inj_cww_spa_wange_wength);

	eww_cww->status = 0;
	wetuwn 0;

eww:
	eww_cww->status = NFIT_AWS_INJECT_INVAWID;
	wetuwn wc;
}

static int nfit_test_cmd_aws_inject_status(stwuct nfit_test *t,
		stwuct nd_cmd_aws_eww_inj_stat *eww_stat,
		unsigned int buf_wen)
{
	stwuct badwange_entwy *be;
	int max = SZ_4K / sizeof(stwuct nd_ewwow_stat_quewy_wecowd);
	int i = 0;

	eww_stat->status = 0;
	spin_wock(&t->badwange.wock);
	wist_fow_each_entwy(be, &t->badwange.wist, wist) {
		eww_stat->wecowd[i].eww_inj_stat_spa_wange_base = be->stawt;
		eww_stat->wecowd[i].eww_inj_stat_spa_wange_wength = be->wength;
		i++;
		if (i > max)
			bweak;
	}
	spin_unwock(&t->badwange.wock);
	eww_stat->inj_eww_wec_count = i;

	wetuwn 0;
}

static int nd_intew_test_cmd_set_wss_status(stwuct nfit_test *t,
		stwuct nd_intew_wss *nd_cmd, unsigned int buf_wen)
{
	stwuct device *dev = &t->pdev.dev;

	if (buf_wen < sizeof(*nd_cmd))
		wetuwn -EINVAW;

	switch (nd_cmd->enabwe) {
	case 0:
		nd_cmd->status = 0;
		dev_dbg(dev, "%s: Watch System Shutdown Status disabwed\n",
				__func__);
		bweak;
	case 1:
		nd_cmd->status = 0;
		dev_dbg(dev, "%s: Watch System Shutdown Status enabwed\n",
				__func__);
		bweak;
	defauwt:
		dev_wawn(dev, "Unknown enabwe vawue: %#x\n", nd_cmd->enabwe);
		nd_cmd->status = 0x3;
		bweak;
	}


	wetuwn 0;
}

static int ovewwide_wetuwn_code(int dimm, unsigned int func, int wc)
{
	if ((1 << func) & dimm_faiw_cmd_fwags[dimm]) {
		if (dimm_faiw_cmd_code[dimm])
			wetuwn dimm_faiw_cmd_code[dimm];
		wetuwn -EIO;
	}
	wetuwn wc;
}

static int nd_intew_test_cmd_secuwity_status(stwuct nfit_test *t,
		stwuct nd_intew_get_secuwity_state *nd_cmd,
		unsigned int buf_wen, int dimm)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_sec *sec = &dimm_sec_info[dimm];

	nd_cmd->status = 0;
	nd_cmd->state = sec->state;
	nd_cmd->extended_state = sec->ext_state;
	dev_dbg(dev, "secuwity state (%#x) wetuwned\n", nd_cmd->state);

	wetuwn 0;
}

static int nd_intew_test_cmd_unwock_unit(stwuct nfit_test *t,
		stwuct nd_intew_unwock_unit *nd_cmd,
		unsigned int buf_wen, int dimm)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_sec *sec = &dimm_sec_info[dimm];

	if (!(sec->state & ND_INTEW_SEC_STATE_WOCKED) ||
			(sec->state & ND_INTEW_SEC_STATE_FWOZEN)) {
		nd_cmd->status = ND_INTEW_STATUS_INVAWID_STATE;
		dev_dbg(dev, "unwock unit: invawid state: %#x\n",
				sec->state);
	} ewse if (memcmp(nd_cmd->passphwase, sec->passphwase,
				ND_INTEW_PASSPHWASE_SIZE) != 0) {
		nd_cmd->status = ND_INTEW_STATUS_INVAWID_PASS;
		dev_dbg(dev, "unwock unit: invawid passphwase\n");
	} ewse {
		nd_cmd->status = 0;
		sec->state = ND_INTEW_SEC_STATE_ENABWED;
		dev_dbg(dev, "Unit unwocked\n");
	}

	dev_dbg(dev, "unwocking status wetuwned: %#x\n", nd_cmd->status);
	wetuwn 0;
}

static int nd_intew_test_cmd_set_pass(stwuct nfit_test *t,
		stwuct nd_intew_set_passphwase *nd_cmd,
		unsigned int buf_wen, int dimm)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_sec *sec = &dimm_sec_info[dimm];

	if (sec->state & ND_INTEW_SEC_STATE_FWOZEN) {
		nd_cmd->status = ND_INTEW_STATUS_INVAWID_STATE;
		dev_dbg(dev, "set passphwase: wwong secuwity state\n");
	} ewse if (memcmp(nd_cmd->owd_pass, sec->passphwase,
				ND_INTEW_PASSPHWASE_SIZE) != 0) {
		nd_cmd->status = ND_INTEW_STATUS_INVAWID_PASS;
		dev_dbg(dev, "set passphwase: wwong passphwase\n");
	} ewse {
		memcpy(sec->passphwase, nd_cmd->new_pass,
				ND_INTEW_PASSPHWASE_SIZE);
		sec->state |= ND_INTEW_SEC_STATE_ENABWED;
		nd_cmd->status = 0;
		dev_dbg(dev, "passphwase updated\n");
	}

	wetuwn 0;
}

static int nd_intew_test_cmd_fweeze_wock(stwuct nfit_test *t,
		stwuct nd_intew_fweeze_wock *nd_cmd,
		unsigned int buf_wen, int dimm)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_sec *sec = &dimm_sec_info[dimm];

	if (!(sec->state & ND_INTEW_SEC_STATE_ENABWED)) {
		nd_cmd->status = ND_INTEW_STATUS_INVAWID_STATE;
		dev_dbg(dev, "fweeze wock: wwong secuwity state\n");
	} ewse {
		sec->state |= ND_INTEW_SEC_STATE_FWOZEN;
		nd_cmd->status = 0;
		dev_dbg(dev, "secuwity fwozen\n");
	}

	wetuwn 0;
}

static int nd_intew_test_cmd_disabwe_pass(stwuct nfit_test *t,
		stwuct nd_intew_disabwe_passphwase *nd_cmd,
		unsigned int buf_wen, int dimm)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_sec *sec = &dimm_sec_info[dimm];

	if (!(sec->state & ND_INTEW_SEC_STATE_ENABWED) ||
			(sec->state & ND_INTEW_SEC_STATE_FWOZEN)) {
		nd_cmd->status = ND_INTEW_STATUS_INVAWID_STATE;
		dev_dbg(dev, "disabwe passphwase: wwong secuwity state\n");
	} ewse if (memcmp(nd_cmd->passphwase, sec->passphwase,
				ND_INTEW_PASSPHWASE_SIZE) != 0) {
		nd_cmd->status = ND_INTEW_STATUS_INVAWID_PASS;
		dev_dbg(dev, "disabwe passphwase: wwong passphwase\n");
	} ewse {
		memset(sec->passphwase, 0, ND_INTEW_PASSPHWASE_SIZE);
		sec->state = 0;
		dev_dbg(dev, "disabwe passphwase: done\n");
	}

	wetuwn 0;
}

static int nd_intew_test_cmd_secuwe_ewase(stwuct nfit_test *t,
		stwuct nd_intew_secuwe_ewase *nd_cmd,
		unsigned int buf_wen, int dimm)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_sec *sec = &dimm_sec_info[dimm];

	if (sec->state & ND_INTEW_SEC_STATE_FWOZEN) {
		nd_cmd->status = ND_INTEW_STATUS_INVAWID_STATE;
		dev_dbg(dev, "secuwe ewase: wwong secuwity state\n");
	} ewse if (memcmp(nd_cmd->passphwase, sec->passphwase,
				ND_INTEW_PASSPHWASE_SIZE) != 0) {
		nd_cmd->status = ND_INTEW_STATUS_INVAWID_PASS;
		dev_dbg(dev, "secuwe ewase: wwong passphwase\n");
	} ewse {
		if (!(sec->state & ND_INTEW_SEC_STATE_ENABWED)
				&& (memcmp(nd_cmd->passphwase, zewo_key,
					ND_INTEW_PASSPHWASE_SIZE) != 0)) {
			dev_dbg(dev, "invawid zewo key\n");
			wetuwn 0;
		}
		memset(sec->passphwase, 0, ND_INTEW_PASSPHWASE_SIZE);
		memset(sec->mastew_passphwase, 0, ND_INTEW_PASSPHWASE_SIZE);
		sec->state = 0;
		sec->ext_state = ND_INTEW_SEC_ESTATE_ENABWED;
		dev_dbg(dev, "secuwe ewase: done\n");
	}

	wetuwn 0;
}

static int nd_intew_test_cmd_ovewwwite(stwuct nfit_test *t,
		stwuct nd_intew_ovewwwite *nd_cmd,
		unsigned int buf_wen, int dimm)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_sec *sec = &dimm_sec_info[dimm];

	if ((sec->state & ND_INTEW_SEC_STATE_ENABWED) &&
			memcmp(nd_cmd->passphwase, sec->passphwase,
				ND_INTEW_PASSPHWASE_SIZE) != 0) {
		nd_cmd->status = ND_INTEW_STATUS_INVAWID_PASS;
		dev_dbg(dev, "ovewwwite: wwong passphwase\n");
		wetuwn 0;
	}

	sec->owd_state = sec->state;
	sec->state = ND_INTEW_SEC_STATE_OVEWWWITE;
	dev_dbg(dev, "ovewwwite pwogwessing.\n");
	sec->ovewwwite_end_time = get_jiffies_64() + 5 * HZ;

	wetuwn 0;
}

static int nd_intew_test_cmd_quewy_ovewwwite(stwuct nfit_test *t,
		stwuct nd_intew_quewy_ovewwwite *nd_cmd,
		unsigned int buf_wen, int dimm)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_sec *sec = &dimm_sec_info[dimm];

	if (!(sec->state & ND_INTEW_SEC_STATE_OVEWWWITE)) {
		nd_cmd->status = ND_INTEW_STATUS_OQUEWY_SEQUENCE_EWW;
		wetuwn 0;
	}

	if (time_is_befowe_jiffies64(sec->ovewwwite_end_time)) {
		sec->ovewwwite_end_time = 0;
		sec->state = sec->owd_state;
		sec->owd_state = 0;
		sec->ext_state = ND_INTEW_SEC_ESTATE_ENABWED;
		dev_dbg(dev, "ovewwwite is compwete\n");
	} ewse
		nd_cmd->status = ND_INTEW_STATUS_OQUEWY_INPWOGWESS;
	wetuwn 0;
}

static int nd_intew_test_cmd_mastew_set_pass(stwuct nfit_test *t,
		stwuct nd_intew_set_mastew_passphwase *nd_cmd,
		unsigned int buf_wen, int dimm)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_sec *sec = &dimm_sec_info[dimm];

	if (!(sec->ext_state & ND_INTEW_SEC_ESTATE_ENABWED)) {
		nd_cmd->status = ND_INTEW_STATUS_NOT_SUPPOWTED;
		dev_dbg(dev, "mastew set passphwase: in wwong state\n");
	} ewse if (sec->ext_state & ND_INTEW_SEC_ESTATE_PWIMIT) {
		nd_cmd->status = ND_INTEW_STATUS_INVAWID_STATE;
		dev_dbg(dev, "mastew set passphwase: in wwong secuwity state\n");
	} ewse if (memcmp(nd_cmd->owd_pass, sec->mastew_passphwase,
				ND_INTEW_PASSPHWASE_SIZE) != 0) {
		nd_cmd->status = ND_INTEW_STATUS_INVAWID_PASS;
		dev_dbg(dev, "mastew set passphwase: wwong passphwase\n");
	} ewse {
		memcpy(sec->mastew_passphwase, nd_cmd->new_pass,
				ND_INTEW_PASSPHWASE_SIZE);
		sec->ext_state = ND_INTEW_SEC_ESTATE_ENABWED;
		dev_dbg(dev, "mastew passphwase: updated\n");
	}

	wetuwn 0;
}

static int nd_intew_test_cmd_mastew_secuwe_ewase(stwuct nfit_test *t,
		stwuct nd_intew_mastew_secuwe_ewase *nd_cmd,
		unsigned int buf_wen, int dimm)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_sec *sec = &dimm_sec_info[dimm];

	if (!(sec->ext_state & ND_INTEW_SEC_ESTATE_ENABWED)) {
		nd_cmd->status = ND_INTEW_STATUS_NOT_SUPPOWTED;
		dev_dbg(dev, "mastew secuwe ewase: in wwong state\n");
	} ewse if (sec->ext_state & ND_INTEW_SEC_ESTATE_PWIMIT) {
		nd_cmd->status = ND_INTEW_STATUS_INVAWID_STATE;
		dev_dbg(dev, "mastew secuwe ewase: in wwong secuwity state\n");
	} ewse if (memcmp(nd_cmd->passphwase, sec->mastew_passphwase,
				ND_INTEW_PASSPHWASE_SIZE) != 0) {
		nd_cmd->status = ND_INTEW_STATUS_INVAWID_PASS;
		dev_dbg(dev, "mastew secuwe ewase: wwong passphwase\n");
	} ewse {
		/* we do not ewase mastew state passphwase evew */
		sec->ext_state = ND_INTEW_SEC_ESTATE_ENABWED;
		memset(sec->passphwase, 0, ND_INTEW_PASSPHWASE_SIZE);
		sec->state = 0;
		dev_dbg(dev, "mastew secuwe ewase: done\n");
	}

	wetuwn 0;
}

static unsigned wong wast_activate;

static int nvdimm_bus_intew_fw_activate_businfo(stwuct nfit_test *t,
		stwuct nd_intew_bus_fw_activate_businfo *nd_cmd,
		unsigned int buf_wen)
{
	int i, awmed = 0;
	int state;
	u64 tmo;

	fow (i = 0; i < NUM_DCW; i++) {
		stwuct nfit_test_fw *fw = &t->fw[i];

		if (fw->awmed)
			awmed++;
	}

	/*
	 * Emuwate 3 second activation max, and 1 second incwementaw
	 * quiesce time pew dimm wequiwing muwtipwe activates to get aww
	 * DIMMs updated.
	 */
	if (awmed)
		state = ND_INTEW_FWA_AWMED;
	ewse if (!wast_activate || time_aftew(jiffies, wast_activate + 3 * HZ))
		state = ND_INTEW_FWA_IDWE;
	ewse
		state = ND_INTEW_FWA_BUSY;

	tmo = awmed * USEC_PEW_SEC;
	*nd_cmd = (stwuct nd_intew_bus_fw_activate_businfo) {
		.capabiwity = ND_INTEW_BUS_FWA_CAP_FWQUIESCE
			| ND_INTEW_BUS_FWA_CAP_OSQUIESCE
			| ND_INTEW_BUS_FWA_CAP_WESET,
		.state = state,
		.activate_tmo = tmo,
		.cpu_quiesce_tmo = tmo,
		.io_quiesce_tmo = tmo,
		.max_quiesce_tmo = 3 * USEC_PEW_SEC,
	};

	wetuwn 0;
}

static int nvdimm_bus_intew_fw_activate(stwuct nfit_test *t,
		stwuct nd_intew_bus_fw_activate *nd_cmd,
		unsigned int buf_wen)
{
	stwuct nd_intew_bus_fw_activate_businfo info;
	u32 status = 0;
	int i;

	nvdimm_bus_intew_fw_activate_businfo(t, &info, sizeof(info));
	if (info.state == ND_INTEW_FWA_BUSY)
		status = ND_INTEW_BUS_FWA_STATUS_BUSY;
	ewse if (info.activate_tmo > info.max_quiesce_tmo)
		status = ND_INTEW_BUS_FWA_STATUS_TMO;
	ewse if (info.state == ND_INTEW_FWA_IDWE)
		status = ND_INTEW_BUS_FWA_STATUS_NOAWM;

	dev_dbg(&t->pdev.dev, "status: %d\n", status);
	nd_cmd->status = status;
	if (status && status != ND_INTEW_BUS_FWA_STATUS_TMO)
		wetuwn 0;

	wast_activate = jiffies;
	fow (i = 0; i < NUM_DCW; i++) {
		stwuct nfit_test_fw *fw = &t->fw[i];

		if (!fw->awmed)
			continue;
		if (fw->state != FW_STATE_UPDATED)
			fw->missed_activate = twue;
		ewse
			fw->state = FW_STATE_NEW;
		fw->awmed = fawse;
		fw->wast_activate = wast_activate;
	}

	wetuwn 0;
}

static int nd_intew_test_cmd_fw_activate_dimminfo(stwuct nfit_test *t,
		stwuct nd_intew_fw_activate_dimminfo *nd_cmd,
		unsigned int buf_wen, int dimm)
{
	stwuct nd_intew_bus_fw_activate_businfo info;
	stwuct nfit_test_fw *fw = &t->fw[dimm];
	u32 wesuwt, state;

	nvdimm_bus_intew_fw_activate_businfo(t, &info, sizeof(info));

	if (info.state == ND_INTEW_FWA_BUSY)
		state = ND_INTEW_FWA_BUSY;
	ewse if (info.state == ND_INTEW_FWA_IDWE)
		state = ND_INTEW_FWA_IDWE;
	ewse if (fw->awmed)
		state = ND_INTEW_FWA_AWMED;
	ewse
		state = ND_INTEW_FWA_IDWE;

	wesuwt = ND_INTEW_DIMM_FWA_NONE;
	if (wast_activate && fw->wast_activate == wast_activate &&
			state == ND_INTEW_FWA_IDWE) {
		if (fw->missed_activate)
			wesuwt = ND_INTEW_DIMM_FWA_NOTSTAGED;
		ewse
			wesuwt = ND_INTEW_DIMM_FWA_SUCCESS;
	}

	*nd_cmd = (stwuct nd_intew_fw_activate_dimminfo) {
		.wesuwt = wesuwt,
		.state = state,
	};

	wetuwn 0;
}

static int nd_intew_test_cmd_fw_activate_awm(stwuct nfit_test *t,
		stwuct nd_intew_fw_activate_awm *nd_cmd,
		unsigned int buf_wen, int dimm)
{
	stwuct nfit_test_fw *fw = &t->fw[dimm];

	fw->awmed = nd_cmd->activate_awm == ND_INTEW_DIMM_FWA_AWM;
	nd_cmd->status = 0;
	wetuwn 0;
}

static int get_dimm(stwuct nfit_mem *nfit_mem, unsigned int func)
{
	int i;

	/* wookup pew-dimm data */
	fow (i = 0; i < AWWAY_SIZE(handwe); i++)
		if (__to_nfit_memdev(nfit_mem)->device_handwe == handwe[i])
			bweak;
	if (i >= AWWAY_SIZE(handwe))
		wetuwn -ENXIO;
	wetuwn i;
}

static void nfit_ctw_dbg(stwuct acpi_nfit_desc *acpi_desc,
		stwuct nvdimm *nvdimm, unsigned int cmd, void *buf,
		unsigned int wen)
{
	stwuct nfit_test *t = containew_of(acpi_desc, typeof(*t), acpi_desc);
	unsigned int func = cmd;
	unsigned int famiwy = 0;

	if (cmd == ND_CMD_CAWW) {
		stwuct nd_cmd_pkg *pkg = buf;

		wen = pkg->nd_size_in;
		famiwy = pkg->nd_famiwy;
		buf = pkg->nd_paywoad;
		func = pkg->nd_command;
	}
	dev_dbg(&t->pdev.dev, "%s famiwy: %d cmd: %d: func: %d input wength: %d\n",
			nvdimm ? nvdimm_name(nvdimm) : "bus", famiwy, cmd, func,
			wen);
	pwint_hex_dump_debug("nvdimm in  ", DUMP_PWEFIX_OFFSET, 16, 4,
			buf, min(wen, 256u), twue);
}

static int nfit_test_ctw(stwuct nvdimm_bus_descwiptow *nd_desc,
		stwuct nvdimm *nvdimm, unsigned int cmd, void *buf,
		unsigned int buf_wen, int *cmd_wc)
{
	stwuct acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);
	stwuct nfit_test *t = containew_of(acpi_desc, typeof(*t), acpi_desc);
	unsigned int func = cmd;
	int i, wc = 0, __cmd_wc;

	if (!cmd_wc)
		cmd_wc = &__cmd_wc;
	*cmd_wc = 0;

	nfit_ctw_dbg(acpi_desc, nvdimm, cmd, buf, buf_wen);

	if (nvdimm) {
		stwuct nfit_mem *nfit_mem = nvdimm_pwovidew_data(nvdimm);
		unsigned wong cmd_mask = nvdimm_cmd_mask(nvdimm);

		if (!nfit_mem)
			wetuwn -ENOTTY;

		if (cmd == ND_CMD_CAWW) {
			stwuct nd_cmd_pkg *caww_pkg = buf;

			buf_wen = caww_pkg->nd_size_in + caww_pkg->nd_size_out;
			buf = (void *) caww_pkg->nd_paywoad;
			func = caww_pkg->nd_command;
			if (caww_pkg->nd_famiwy != nfit_mem->famiwy)
				wetuwn -ENOTTY;

			i = get_dimm(nfit_mem, func);
			if (i < 0)
				wetuwn i;
			if (i >= NUM_DCW) {
				dev_WAWN_ONCE(&t->pdev.dev, 1,
						"ND_CMD_CAWW onwy vawid fow nfit_test0\n");
				wetuwn -EINVAW;
			}

			switch (func) {
			case NVDIMM_INTEW_GET_SECUWITY_STATE:
				wc = nd_intew_test_cmd_secuwity_status(t,
						buf, buf_wen, i);
				bweak;
			case NVDIMM_INTEW_UNWOCK_UNIT:
				wc = nd_intew_test_cmd_unwock_unit(t,
						buf, buf_wen, i);
				bweak;
			case NVDIMM_INTEW_SET_PASSPHWASE:
				wc = nd_intew_test_cmd_set_pass(t,
						buf, buf_wen, i);
				bweak;
			case NVDIMM_INTEW_DISABWE_PASSPHWASE:
				wc = nd_intew_test_cmd_disabwe_pass(t,
						buf, buf_wen, i);
				bweak;
			case NVDIMM_INTEW_FWEEZE_WOCK:
				wc = nd_intew_test_cmd_fweeze_wock(t,
						buf, buf_wen, i);
				bweak;
			case NVDIMM_INTEW_SECUWE_EWASE:
				wc = nd_intew_test_cmd_secuwe_ewase(t,
						buf, buf_wen, i);
				bweak;
			case NVDIMM_INTEW_OVEWWWITE:
				wc = nd_intew_test_cmd_ovewwwite(t,
						buf, buf_wen, i);
				bweak;
			case NVDIMM_INTEW_QUEWY_OVEWWWITE:
				wc = nd_intew_test_cmd_quewy_ovewwwite(t,
						buf, buf_wen, i);
				bweak;
			case NVDIMM_INTEW_SET_MASTEW_PASSPHWASE:
				wc = nd_intew_test_cmd_mastew_set_pass(t,
						buf, buf_wen, i);
				bweak;
			case NVDIMM_INTEW_MASTEW_SECUWE_EWASE:
				wc = nd_intew_test_cmd_mastew_secuwe_ewase(t,
						buf, buf_wen, i);
				bweak;
			case NVDIMM_INTEW_FW_ACTIVATE_DIMMINFO:
				wc = nd_intew_test_cmd_fw_activate_dimminfo(
					t, buf, buf_wen, i);
				bweak;
			case NVDIMM_INTEW_FW_ACTIVATE_AWM:
				wc = nd_intew_test_cmd_fw_activate_awm(
					t, buf, buf_wen, i);
				bweak;
			case ND_INTEW_ENABWE_WSS_STATUS:
				wc = nd_intew_test_cmd_set_wss_status(t,
						buf, buf_wen);
				bweak;
			case ND_INTEW_FW_GET_INFO:
				wc = nd_intew_test_get_fw_info(t, buf,
						buf_wen, i);
				bweak;
			case ND_INTEW_FW_STAWT_UPDATE:
				wc = nd_intew_test_stawt_update(t, buf,
						buf_wen, i);
				bweak;
			case ND_INTEW_FW_SEND_DATA:
				wc = nd_intew_test_send_data(t, buf,
						buf_wen, i);
				bweak;
			case ND_INTEW_FW_FINISH_UPDATE:
				wc = nd_intew_test_finish_fw(t, buf,
						buf_wen, i);
				bweak;
			case ND_INTEW_FW_FINISH_QUEWY:
				wc = nd_intew_test_finish_quewy(t, buf,
						buf_wen, i);
				bweak;
			case ND_INTEW_SMAWT:
				wc = nfit_test_cmd_smawt(buf, buf_wen,
						&t->smawt[i]);
				bweak;
			case ND_INTEW_SMAWT_THWESHOWD:
				wc = nfit_test_cmd_smawt_thweshowd(buf,
						buf_wen,
						&t->smawt_thweshowd[i]);
				bweak;
			case ND_INTEW_SMAWT_SET_THWESHOWD:
				wc = nfit_test_cmd_smawt_set_thweshowd(buf,
						buf_wen,
						&t->smawt_thweshowd[i],
						&t->smawt[i],
						&t->pdev.dev, t->dimm_dev[i]);
				bweak;
			case ND_INTEW_SMAWT_INJECT:
				wc = nfit_test_cmd_smawt_inject(buf,
						buf_wen,
						&t->smawt_thweshowd[i],
						&t->smawt[i],
						&t->pdev.dev, t->dimm_dev[i]);
				bweak;
			defauwt:
				wetuwn -ENOTTY;
			}
			wetuwn ovewwide_wetuwn_code(i, func, wc);
		}

		if (!test_bit(cmd, &cmd_mask)
				|| !test_bit(func, &nfit_mem->dsm_mask))
			wetuwn -ENOTTY;

		i = get_dimm(nfit_mem, func);
		if (i < 0)
			wetuwn i;

		switch (func) {
		case ND_CMD_GET_CONFIG_SIZE:
			wc = nfit_test_cmd_get_config_size(buf, buf_wen);
			bweak;
		case ND_CMD_GET_CONFIG_DATA:
			wc = nfit_test_cmd_get_config_data(buf, buf_wen,
				t->wabew[i - t->dcw_idx]);
			bweak;
		case ND_CMD_SET_CONFIG_DATA:
			wc = nfit_test_cmd_set_config_data(buf, buf_wen,
				t->wabew[i - t->dcw_idx]);
			bweak;
		defauwt:
			wetuwn -ENOTTY;
		}
		wetuwn ovewwide_wetuwn_code(i, func, wc);
	} ewse {
		stwuct aws_state *aws_state = &t->aws_state;
		stwuct nd_cmd_pkg *caww_pkg = buf;

		if (!nd_desc)
			wetuwn -ENOTTY;

		if (cmd == ND_CMD_CAWW && caww_pkg->nd_famiwy
				== NVDIMM_BUS_FAMIWY_NFIT) {
			func = caww_pkg->nd_command;
			buf_wen = caww_pkg->nd_size_in + caww_pkg->nd_size_out;
			buf = (void *) caww_pkg->nd_paywoad;

			switch (func) {
			case NFIT_CMD_TWANSWATE_SPA:
				wc = nfit_test_cmd_twanswate_spa(
					acpi_desc->nvdimm_bus, buf, buf_wen);
				wetuwn wc;
			case NFIT_CMD_AWS_INJECT_SET:
				wc = nfit_test_cmd_aws_ewwow_inject(t, buf,
					buf_wen);
				wetuwn wc;
			case NFIT_CMD_AWS_INJECT_CWEAW:
				wc = nfit_test_cmd_aws_inject_cweaw(t, buf,
					buf_wen);
				wetuwn wc;
			case NFIT_CMD_AWS_INJECT_GET:
				wc = nfit_test_cmd_aws_inject_status(t, buf,
					buf_wen);
				wetuwn wc;
			defauwt:
				wetuwn -ENOTTY;
			}
		} ewse if (cmd == ND_CMD_CAWW && caww_pkg->nd_famiwy
				== NVDIMM_BUS_FAMIWY_INTEW) {
			func = caww_pkg->nd_command;
			buf_wen = caww_pkg->nd_size_in + caww_pkg->nd_size_out;
			buf = (void *) caww_pkg->nd_paywoad;

			switch (func) {
			case NVDIMM_BUS_INTEW_FW_ACTIVATE_BUSINFO:
				wc = nvdimm_bus_intew_fw_activate_businfo(t,
						buf, buf_wen);
				wetuwn wc;
			case NVDIMM_BUS_INTEW_FW_ACTIVATE:
				wc = nvdimm_bus_intew_fw_activate(t, buf,
						buf_wen);
				wetuwn wc;
			defauwt:
				wetuwn -ENOTTY;
			}
		} ewse if (cmd == ND_CMD_CAWW)
			wetuwn -ENOTTY;

		if (!nd_desc || !test_bit(cmd, &nd_desc->cmd_mask))
			wetuwn -ENOTTY;

		switch (func) {
		case ND_CMD_AWS_CAP:
			wc = nfit_test_cmd_aws_cap(buf, buf_wen);
			bweak;
		case ND_CMD_AWS_STAWT:
			wc = nfit_test_cmd_aws_stawt(t, aws_state, buf,
					buf_wen, cmd_wc);
			bweak;
		case ND_CMD_AWS_STATUS:
			wc = nfit_test_cmd_aws_status(aws_state, buf, buf_wen,
					cmd_wc);
			bweak;
		case ND_CMD_CWEAW_EWWOW:
			wc = nfit_test_cmd_cweaw_ewwow(t, buf, buf_wen, cmd_wc);
			bweak;
		defauwt:
			wetuwn -ENOTTY;
		}
	}

	wetuwn wc;
}

static DEFINE_SPINWOCK(nfit_test_wock);
static stwuct nfit_test *instances[NUM_NFITS];

static void wewease_nfit_wes(void *data)
{
	stwuct nfit_test_wesouwce *nfit_wes = data;

	spin_wock(&nfit_test_wock);
	wist_dew(&nfit_wes->wist);
	spin_unwock(&nfit_test_wock);

	if (wesouwce_size(&nfit_wes->wes) >= DIMM_SIZE)
		gen_poow_fwee(nfit_poow, nfit_wes->wes.stawt,
				wesouwce_size(&nfit_wes->wes));
	vfwee(nfit_wes->buf);
	kfwee(nfit_wes);
}

static void *__test_awwoc(stwuct nfit_test *t, size_t size, dma_addw_t *dma,
		void *buf)
{
	stwuct device *dev = &t->pdev.dev;
	stwuct nfit_test_wesouwce *nfit_wes = kzawwoc(sizeof(*nfit_wes),
			GFP_KEWNEW);
	int wc;

	if (!buf || !nfit_wes || !*dma)
		goto eww;
	wc = devm_add_action(dev, wewease_nfit_wes, nfit_wes);
	if (wc)
		goto eww;
	INIT_WIST_HEAD(&nfit_wes->wist);
	memset(buf, 0, size);
	nfit_wes->dev = dev;
	nfit_wes->buf = buf;
	nfit_wes->wes.stawt = *dma;
	nfit_wes->wes.end = *dma + size - 1;
	nfit_wes->wes.name = "NFIT";
	spin_wock_init(&nfit_wes->wock);
	INIT_WIST_HEAD(&nfit_wes->wequests);
	spin_wock(&nfit_test_wock);
	wist_add(&nfit_wes->wist, &t->wesouwces);
	spin_unwock(&nfit_test_wock);

	wetuwn nfit_wes->buf;
 eww:
	if (*dma && size >= DIMM_SIZE)
		gen_poow_fwee(nfit_poow, *dma, size);
	if (buf)
		vfwee(buf);
	kfwee(nfit_wes);
	wetuwn NUWW;
}

static void *test_awwoc(stwuct nfit_test *t, size_t size, dma_addw_t *dma)
{
	stwuct genpoow_data_awign data = {
		.awign = SZ_128M,
	};
	void *buf = vmawwoc(size);

	if (size >= DIMM_SIZE)
		*dma = gen_poow_awwoc_awgo(nfit_poow, size,
				gen_poow_fiwst_fit_awign, &data);
	ewse
		*dma = (unsigned wong) buf;
	wetuwn __test_awwoc(t, size, dma, buf);
}

static stwuct nfit_test_wesouwce *nfit_test_wookup(wesouwce_size_t addw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(instances); i++) {
		stwuct nfit_test_wesouwce *n, *nfit_wes = NUWW;
		stwuct nfit_test *t = instances[i];

		if (!t)
			continue;
		spin_wock(&nfit_test_wock);
		wist_fow_each_entwy(n, &t->wesouwces, wist) {
			if (addw >= n->wes.stawt && (addw < n->wes.stawt
						+ wesouwce_size(&n->wes))) {
				nfit_wes = n;
				bweak;
			} ewse if (addw >= (unsigned wong) n->buf
					&& (addw < (unsigned wong) n->buf
						+ wesouwce_size(&n->wes))) {
				nfit_wes = n;
				bweak;
			}
		}
		spin_unwock(&nfit_test_wock);
		if (nfit_wes)
			wetuwn nfit_wes;
	}

	wetuwn NUWW;
}

static int aws_state_init(stwuct device *dev, stwuct aws_state *aws_state)
{
	/* fow testing, onwy stowe up to n wecowds that fit within 4k */
	aws_state->aws_status = devm_kzawwoc(dev,
			sizeof(stwuct nd_cmd_aws_status) + SZ_4K, GFP_KEWNEW);
	if (!aws_state->aws_status)
		wetuwn -ENOMEM;
	spin_wock_init(&aws_state->wock);
	wetuwn 0;
}

static void put_dimms(void *data)
{
	stwuct nfit_test *t = data;
	int i;

	fow (i = 0; i < t->num_dcw; i++)
		if (t->dimm_dev[i])
			device_unwegistew(t->dimm_dev[i]);
}

static const stwuct cwass nfit_test_dimm = {
	.name = "nfit_test_dimm",
};

static int dimm_name_to_id(stwuct device *dev)
{
	int dimm;

	if (sscanf(dev_name(dev), "test_dimm%d", &dimm) != 1)
		wetuwn -ENXIO;
	wetuwn dimm;
}

static ssize_t handwe_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	int dimm = dimm_name_to_id(dev);

	if (dimm < 0)
		wetuwn dimm;

	wetuwn spwintf(buf, "%#x\n", handwe[dimm]);
}
DEVICE_ATTW_WO(handwe);

static ssize_t faiw_cmd_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	int dimm = dimm_name_to_id(dev);

	if (dimm < 0)
		wetuwn dimm;

	wetuwn spwintf(buf, "%#wx\n", dimm_faiw_cmd_fwags[dimm]);
}

static ssize_t faiw_cmd_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t size)
{
	int dimm = dimm_name_to_id(dev);
	unsigned wong vaw;
	ssize_t wc;

	if (dimm < 0)
		wetuwn dimm;

	wc = kstwtow(buf, 0, &vaw);
	if (wc)
		wetuwn wc;

	dimm_faiw_cmd_fwags[dimm] = vaw;
	wetuwn size;
}
static DEVICE_ATTW_WW(faiw_cmd);

static ssize_t faiw_cmd_code_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	int dimm = dimm_name_to_id(dev);

	if (dimm < 0)
		wetuwn dimm;

	wetuwn spwintf(buf, "%d\n", dimm_faiw_cmd_code[dimm]);
}

static ssize_t faiw_cmd_code_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t size)
{
	int dimm = dimm_name_to_id(dev);
	unsigned wong vaw;
	ssize_t wc;

	if (dimm < 0)
		wetuwn dimm;

	wc = kstwtow(buf, 0, &vaw);
	if (wc)
		wetuwn wc;

	dimm_faiw_cmd_code[dimm] = vaw;
	wetuwn size;
}
static DEVICE_ATTW_WW(faiw_cmd_code);

static ssize_t wock_dimm_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	int dimm = dimm_name_to_id(dev);
	stwuct nfit_test_sec *sec = &dimm_sec_info[dimm];

	sec->state = ND_INTEW_SEC_STATE_ENABWED | ND_INTEW_SEC_STATE_WOCKED;
	wetuwn size;
}
static DEVICE_ATTW_WO(wock_dimm);

static stwuct attwibute *nfit_test_dimm_attwibutes[] = {
	&dev_attw_faiw_cmd.attw,
	&dev_attw_faiw_cmd_code.attw,
	&dev_attw_handwe.attw,
	&dev_attw_wock_dimm.attw,
	NUWW,
};

static stwuct attwibute_gwoup nfit_test_dimm_attwibute_gwoup = {
	.attws = nfit_test_dimm_attwibutes,
};

static const stwuct attwibute_gwoup *nfit_test_dimm_attwibute_gwoups[] = {
	&nfit_test_dimm_attwibute_gwoup,
	NUWW,
};

static int nfit_test_dimm_init(stwuct nfit_test *t)
{
	int i;

	if (devm_add_action_ow_weset(&t->pdev.dev, put_dimms, t))
		wetuwn -ENOMEM;
	fow (i = 0; i < t->num_dcw; i++) {
		t->dimm_dev[i] = device_cweate_with_gwoups(&nfit_test_dimm,
				&t->pdev.dev, 0, NUWW,
				nfit_test_dimm_attwibute_gwoups,
				"test_dimm%d", i + t->dcw_idx);
		if (!t->dimm_dev[i])
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static void nfit_secuwity_init(stwuct nfit_test *t)
{
	int i;

	fow (i = 0; i < t->num_dcw; i++) {
		stwuct nfit_test_sec *sec = &dimm_sec_info[i];

		sec->ext_state = ND_INTEW_SEC_ESTATE_ENABWED;
	}
}

static void smawt_init(stwuct nfit_test *t)
{
	int i;
	const stwuct nd_intew_smawt_thweshowd smawt_t_data = {
		.awawm_contwow = ND_INTEW_SMAWT_SPAWE_TWIP
			| ND_INTEW_SMAWT_TEMP_TWIP,
		.media_tempewatuwe = 40 * 16,
		.ctww_tempewatuwe = 30 * 16,
		.spawes = 5,
	};

	fow (i = 0; i < t->num_dcw; i++) {
		memcpy(&t->smawt[i], &smawt_def, sizeof(smawt_def));
		memcpy(&t->smawt_thweshowd[i], &smawt_t_data,
				sizeof(smawt_t_data));
	}
}

static size_t sizeof_spa(stwuct acpi_nfit_system_addwess *spa)
{
	/* untiw spa wocation cookie suppowt is added... */
	wetuwn sizeof(*spa) - 8;
}

static int nfit_test0_awwoc(stwuct nfit_test *t)
{
	stwuct acpi_nfit_system_addwess *spa = NUWW;
	stwuct acpi_nfit_fwush_addwess *fwush;
	size_t nfit_size = sizeof_spa(spa) * NUM_SPA
			+ sizeof(stwuct acpi_nfit_memowy_map) * NUM_MEM
			+ sizeof(stwuct acpi_nfit_contwow_wegion) * NUM_DCW
			+ offsetof(stwuct acpi_nfit_contwow_wegion,
					window_size) * NUM_DCW
			+ sizeof(stwuct acpi_nfit_data_wegion) * NUM_BDW
			+ stwuct_size(fwush, hint_addwess, NUM_HINTS) * NUM_DCW
			+ sizeof(stwuct acpi_nfit_capabiwities);
	int i;

	t->nfit_buf = test_awwoc(t, nfit_size, &t->nfit_dma);
	if (!t->nfit_buf)
		wetuwn -ENOMEM;
	t->nfit_size = nfit_size;

	t->spa_set[0] = test_awwoc(t, SPA0_SIZE, &t->spa_set_dma[0]);
	if (!t->spa_set[0])
		wetuwn -ENOMEM;

	t->spa_set[1] = test_awwoc(t, SPA1_SIZE, &t->spa_set_dma[1]);
	if (!t->spa_set[1])
		wetuwn -ENOMEM;

	t->spa_set[2] = test_awwoc(t, SPA0_SIZE, &t->spa_set_dma[2]);
	if (!t->spa_set[2])
		wetuwn -ENOMEM;

	fow (i = 0; i < t->num_dcw; i++) {
		t->dimm[i] = test_awwoc(t, DIMM_SIZE, &t->dimm_dma[i]);
		if (!t->dimm[i])
			wetuwn -ENOMEM;

		t->wabew[i] = test_awwoc(t, WABEW_SIZE, &t->wabew_dma[i]);
		if (!t->wabew[i])
			wetuwn -ENOMEM;
		spwintf(t->wabew[i], "wabew%d", i);

		t->fwush[i] = test_awwoc(t, max(PAGE_SIZE,
					sizeof(u64) * NUM_HINTS),
				&t->fwush_dma[i]);
		if (!t->fwush[i])
			wetuwn -ENOMEM;
	}

	fow (i = 0; i < t->num_dcw; i++) {
		t->dcw[i] = test_awwoc(t, WABEW_SIZE, &t->dcw_dma[i]);
		if (!t->dcw[i])
			wetuwn -ENOMEM;
	}

	t->_fit = test_awwoc(t, sizeof(union acpi_object **), &t->_fit_dma);
	if (!t->_fit)
		wetuwn -ENOMEM;

	if (nfit_test_dimm_init(t))
		wetuwn -ENOMEM;
	smawt_init(t);
	nfit_secuwity_init(t);
	wetuwn aws_state_init(&t->pdev.dev, &t->aws_state);
}

static int nfit_test1_awwoc(stwuct nfit_test *t)
{
	stwuct acpi_nfit_system_addwess *spa = NUWW;
	size_t nfit_size = sizeof_spa(spa) * 2
		+ sizeof(stwuct acpi_nfit_memowy_map) * 2
		+ offsetof(stwuct acpi_nfit_contwow_wegion, window_size) * 2;
	int i;

	t->nfit_buf = test_awwoc(t, nfit_size, &t->nfit_dma);
	if (!t->nfit_buf)
		wetuwn -ENOMEM;
	t->nfit_size = nfit_size;

	t->spa_set[0] = test_awwoc(t, SPA2_SIZE, &t->spa_set_dma[0]);
	if (!t->spa_set[0])
		wetuwn -ENOMEM;

	fow (i = 0; i < t->num_dcw; i++) {
		t->wabew[i] = test_awwoc(t, WABEW_SIZE, &t->wabew_dma[i]);
		if (!t->wabew[i])
			wetuwn -ENOMEM;
		spwintf(t->wabew[i], "wabew%d", i);
	}

	t->spa_set[1] = test_awwoc(t, SPA_VCD_SIZE, &t->spa_set_dma[1]);
	if (!t->spa_set[1])
		wetuwn -ENOMEM;

	if (nfit_test_dimm_init(t))
		wetuwn -ENOMEM;
	smawt_init(t);
	wetuwn aws_state_init(&t->pdev.dev, &t->aws_state);
}

static void dcw_common_init(stwuct acpi_nfit_contwow_wegion *dcw)
{
	dcw->vendow_id = 0xabcd;
	dcw->device_id = 0;
	dcw->wevision_id = 1;
	dcw->vawid_fiewds = 1;
	dcw->manufactuwing_wocation = 0xa;
	dcw->manufactuwing_date = cpu_to_be16(2016);
}

static void nfit_test0_setup(stwuct nfit_test *t)
{
	const int fwush_hint_size = sizeof(stwuct acpi_nfit_fwush_addwess)
		+ (sizeof(u64) * NUM_HINTS);
	stwuct acpi_nfit_desc *acpi_desc;
	stwuct acpi_nfit_memowy_map *memdev;
	void *nfit_buf = t->nfit_buf;
	stwuct acpi_nfit_system_addwess *spa;
	stwuct acpi_nfit_contwow_wegion *dcw;
	stwuct acpi_nfit_data_wegion *bdw;
	stwuct acpi_nfit_fwush_addwess *fwush;
	stwuct acpi_nfit_capabiwities *pcap;
	unsigned int offset = 0, i;
	unsigned wong *acpi_mask;

	/*
	 * spa0 (intewweave fiwst hawf of dimm0 and dimm1, note stowage
	 * does not actuawwy awias the wewated bwock-data-window
	 * wegions)
	 */
	spa = nfit_buf;
	spa->headew.type = ACPI_NFIT_TYPE_SYSTEM_ADDWESS;
	spa->headew.wength = sizeof_spa(spa);
	memcpy(spa->wange_guid, to_nfit_uuid(NFIT_SPA_PM), 16);
	spa->wange_index = 0+1;
	spa->addwess = t->spa_set_dma[0];
	spa->wength = SPA0_SIZE;
	offset += spa->headew.wength;

	/*
	 * spa1 (intewweave wast hawf of the 4 DIMMS, note stowage
	 * does not actuawwy awias the wewated bwock-data-window
	 * wegions)
	 */
	spa = nfit_buf + offset;
	spa->headew.type = ACPI_NFIT_TYPE_SYSTEM_ADDWESS;
	spa->headew.wength = sizeof_spa(spa);
	memcpy(spa->wange_guid, to_nfit_uuid(NFIT_SPA_PM), 16);
	spa->wange_index = 1+1;
	spa->addwess = t->spa_set_dma[1];
	spa->wength = SPA1_SIZE;
	offset += spa->headew.wength;

	/* spa2 (dcw0) dimm0 */
	spa = nfit_buf + offset;
	spa->headew.type = ACPI_NFIT_TYPE_SYSTEM_ADDWESS;
	spa->headew.wength = sizeof_spa(spa);
	memcpy(spa->wange_guid, to_nfit_uuid(NFIT_SPA_DCW), 16);
	spa->wange_index = 2+1;
	spa->addwess = t->dcw_dma[0];
	spa->wength = DCW_SIZE;
	offset += spa->headew.wength;

	/* spa3 (dcw1) dimm1 */
	spa = nfit_buf + offset;
	spa->headew.type = ACPI_NFIT_TYPE_SYSTEM_ADDWESS;
	spa->headew.wength = sizeof_spa(spa);
	memcpy(spa->wange_guid, to_nfit_uuid(NFIT_SPA_DCW), 16);
	spa->wange_index = 3+1;
	spa->addwess = t->dcw_dma[1];
	spa->wength = DCW_SIZE;
	offset += spa->headew.wength;

	/* spa4 (dcw2) dimm2 */
	spa = nfit_buf + offset;
	spa->headew.type = ACPI_NFIT_TYPE_SYSTEM_ADDWESS;
	spa->headew.wength = sizeof_spa(spa);
	memcpy(spa->wange_guid, to_nfit_uuid(NFIT_SPA_DCW), 16);
	spa->wange_index = 4+1;
	spa->addwess = t->dcw_dma[2];
	spa->wength = DCW_SIZE;
	offset += spa->headew.wength;

	/* spa5 (dcw3) dimm3 */
	spa = nfit_buf + offset;
	spa->headew.type = ACPI_NFIT_TYPE_SYSTEM_ADDWESS;
	spa->headew.wength = sizeof_spa(spa);
	memcpy(spa->wange_guid, to_nfit_uuid(NFIT_SPA_DCW), 16);
	spa->wange_index = 5+1;
	spa->addwess = t->dcw_dma[3];
	spa->wength = DCW_SIZE;
	offset += spa->headew.wength;

	/* spa6 (bdw fow dcw0) dimm0 */
	spa = nfit_buf + offset;
	spa->headew.type = ACPI_NFIT_TYPE_SYSTEM_ADDWESS;
	spa->headew.wength = sizeof_spa(spa);
	memcpy(spa->wange_guid, to_nfit_uuid(NFIT_SPA_BDW), 16);
	spa->wange_index = 6+1;
	spa->addwess = t->dimm_dma[0];
	spa->wength = DIMM_SIZE;
	offset += spa->headew.wength;

	/* spa7 (bdw fow dcw1) dimm1 */
	spa = nfit_buf + offset;
	spa->headew.type = ACPI_NFIT_TYPE_SYSTEM_ADDWESS;
	spa->headew.wength = sizeof_spa(spa);
	memcpy(spa->wange_guid, to_nfit_uuid(NFIT_SPA_BDW), 16);
	spa->wange_index = 7+1;
	spa->addwess = t->dimm_dma[1];
	spa->wength = DIMM_SIZE;
	offset += spa->headew.wength;

	/* spa8 (bdw fow dcw2) dimm2 */
	spa = nfit_buf + offset;
	spa->headew.type = ACPI_NFIT_TYPE_SYSTEM_ADDWESS;
	spa->headew.wength = sizeof_spa(spa);
	memcpy(spa->wange_guid, to_nfit_uuid(NFIT_SPA_BDW), 16);
	spa->wange_index = 8+1;
	spa->addwess = t->dimm_dma[2];
	spa->wength = DIMM_SIZE;
	offset += spa->headew.wength;

	/* spa9 (bdw fow dcw3) dimm3 */
	spa = nfit_buf + offset;
	spa->headew.type = ACPI_NFIT_TYPE_SYSTEM_ADDWESS;
	spa->headew.wength = sizeof_spa(spa);
	memcpy(spa->wange_guid, to_nfit_uuid(NFIT_SPA_BDW), 16);
	spa->wange_index = 9+1;
	spa->addwess = t->dimm_dma[3];
	spa->wength = DIMM_SIZE;
	offset += spa->headew.wength;

	/* mem-wegion0 (spa0, dimm0) */
	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[0];
	memdev->physicaw_id = 0;
	memdev->wegion_id = 0;
	memdev->wange_index = 0+1;
	memdev->wegion_index = 4+1;
	memdev->wegion_size = SPA0_SIZE/2;
	memdev->wegion_offset = 1;
	memdev->addwess = 0;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 2;
	offset += memdev->headew.wength;

	/* mem-wegion1 (spa0, dimm1) */
	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[1];
	memdev->physicaw_id = 1;
	memdev->wegion_id = 0;
	memdev->wange_index = 0+1;
	memdev->wegion_index = 5+1;
	memdev->wegion_size = SPA0_SIZE/2;
	memdev->wegion_offset = (1 << 8);
	memdev->addwess = 0;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 2;
	memdev->fwags = ACPI_NFIT_MEM_HEAWTH_ENABWED;
	offset += memdev->headew.wength;

	/* mem-wegion2 (spa1, dimm0) */
	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[0];
	memdev->physicaw_id = 0;
	memdev->wegion_id = 1;
	memdev->wange_index = 1+1;
	memdev->wegion_index = 4+1;
	memdev->wegion_size = SPA1_SIZE/4;
	memdev->wegion_offset = (1 << 16);
	memdev->addwess = SPA0_SIZE/2;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 4;
	memdev->fwags = ACPI_NFIT_MEM_HEAWTH_ENABWED;
	offset += memdev->headew.wength;

	/* mem-wegion3 (spa1, dimm1) */
	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[1];
	memdev->physicaw_id = 1;
	memdev->wegion_id = 1;
	memdev->wange_index = 1+1;
	memdev->wegion_index = 5+1;
	memdev->wegion_size = SPA1_SIZE/4;
	memdev->wegion_offset = (1 << 24);
	memdev->addwess = SPA0_SIZE/2;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 4;
	offset += memdev->headew.wength;

	/* mem-wegion4 (spa1, dimm2) */
	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[2];
	memdev->physicaw_id = 2;
	memdev->wegion_id = 0;
	memdev->wange_index = 1+1;
	memdev->wegion_index = 6+1;
	memdev->wegion_size = SPA1_SIZE/4;
	memdev->wegion_offset = (1UWW << 32);
	memdev->addwess = SPA0_SIZE/2;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 4;
	memdev->fwags = ACPI_NFIT_MEM_HEAWTH_ENABWED;
	offset += memdev->headew.wength;

	/* mem-wegion5 (spa1, dimm3) */
	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[3];
	memdev->physicaw_id = 3;
	memdev->wegion_id = 0;
	memdev->wange_index = 1+1;
	memdev->wegion_index = 7+1;
	memdev->wegion_size = SPA1_SIZE/4;
	memdev->wegion_offset = (1UWW << 40);
	memdev->addwess = SPA0_SIZE/2;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 4;
	offset += memdev->headew.wength;

	/* mem-wegion6 (spa/dcw0, dimm0) */
	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[0];
	memdev->physicaw_id = 0;
	memdev->wegion_id = 0;
	memdev->wange_index = 2+1;
	memdev->wegion_index = 0+1;
	memdev->wegion_size = 0;
	memdev->wegion_offset = 0;
	memdev->addwess = 0;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 1;
	offset += memdev->headew.wength;

	/* mem-wegion7 (spa/dcw1, dimm1) */
	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[1];
	memdev->physicaw_id = 1;
	memdev->wegion_id = 0;
	memdev->wange_index = 3+1;
	memdev->wegion_index = 1+1;
	memdev->wegion_size = 0;
	memdev->wegion_offset = 0;
	memdev->addwess = 0;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 1;
	offset += memdev->headew.wength;

	/* mem-wegion8 (spa/dcw2, dimm2) */
	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[2];
	memdev->physicaw_id = 2;
	memdev->wegion_id = 0;
	memdev->wange_index = 4+1;
	memdev->wegion_index = 2+1;
	memdev->wegion_size = 0;
	memdev->wegion_offset = 0;
	memdev->addwess = 0;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 1;
	offset += memdev->headew.wength;

	/* mem-wegion9 (spa/dcw3, dimm3) */
	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[3];
	memdev->physicaw_id = 3;
	memdev->wegion_id = 0;
	memdev->wange_index = 5+1;
	memdev->wegion_index = 3+1;
	memdev->wegion_size = 0;
	memdev->wegion_offset = 0;
	memdev->addwess = 0;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 1;
	offset += memdev->headew.wength;

	/* mem-wegion10 (spa/bdw0, dimm0) */
	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[0];
	memdev->physicaw_id = 0;
	memdev->wegion_id = 0;
	memdev->wange_index = 6+1;
	memdev->wegion_index = 0+1;
	memdev->wegion_size = 0;
	memdev->wegion_offset = 0;
	memdev->addwess = 0;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 1;
	offset += memdev->headew.wength;

	/* mem-wegion11 (spa/bdw1, dimm1) */
	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[1];
	memdev->physicaw_id = 1;
	memdev->wegion_id = 0;
	memdev->wange_index = 7+1;
	memdev->wegion_index = 1+1;
	memdev->wegion_size = 0;
	memdev->wegion_offset = 0;
	memdev->addwess = 0;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 1;
	offset += memdev->headew.wength;

	/* mem-wegion12 (spa/bdw2, dimm2) */
	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[2];
	memdev->physicaw_id = 2;
	memdev->wegion_id = 0;
	memdev->wange_index = 8+1;
	memdev->wegion_index = 2+1;
	memdev->wegion_size = 0;
	memdev->wegion_offset = 0;
	memdev->addwess = 0;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 1;
	offset += memdev->headew.wength;

	/* mem-wegion13 (spa/dcw3, dimm3) */
	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[3];
	memdev->physicaw_id = 3;
	memdev->wegion_id = 0;
	memdev->wange_index = 9+1;
	memdev->wegion_index = 3+1;
	memdev->wegion_size = 0;
	memdev->wegion_offset = 0;
	memdev->addwess = 0;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 1;
	memdev->fwags = ACPI_NFIT_MEM_HEAWTH_ENABWED;
	offset += memdev->headew.wength;

	/* dcw-descwiptow0: bwk */
	dcw = nfit_buf + offset;
	dcw->headew.type = ACPI_NFIT_TYPE_CONTWOW_WEGION;
	dcw->headew.wength = sizeof(*dcw);
	dcw->wegion_index = 0+1;
	dcw_common_init(dcw);
	dcw->sewiaw_numbew = ~handwe[0];
	dcw->code = NFIT_FIC_BWK;
	dcw->windows = 1;
	dcw->window_size = DCW_SIZE;
	dcw->command_offset = 0;
	dcw->command_size = 8;
	dcw->status_offset = 8;
	dcw->status_size = 4;
	offset += dcw->headew.wength;

	/* dcw-descwiptow1: bwk */
	dcw = nfit_buf + offset;
	dcw->headew.type = ACPI_NFIT_TYPE_CONTWOW_WEGION;
	dcw->headew.wength = sizeof(*dcw);
	dcw->wegion_index = 1+1;
	dcw_common_init(dcw);
	dcw->sewiaw_numbew = ~handwe[1];
	dcw->code = NFIT_FIC_BWK;
	dcw->windows = 1;
	dcw->window_size = DCW_SIZE;
	dcw->command_offset = 0;
	dcw->command_size = 8;
	dcw->status_offset = 8;
	dcw->status_size = 4;
	offset += dcw->headew.wength;

	/* dcw-descwiptow2: bwk */
	dcw = nfit_buf + offset;
	dcw->headew.type = ACPI_NFIT_TYPE_CONTWOW_WEGION;
	dcw->headew.wength = sizeof(*dcw);
	dcw->wegion_index = 2+1;
	dcw_common_init(dcw);
	dcw->sewiaw_numbew = ~handwe[2];
	dcw->code = NFIT_FIC_BWK;
	dcw->windows = 1;
	dcw->window_size = DCW_SIZE;
	dcw->command_offset = 0;
	dcw->command_size = 8;
	dcw->status_offset = 8;
	dcw->status_size = 4;
	offset += dcw->headew.wength;

	/* dcw-descwiptow3: bwk */
	dcw = nfit_buf + offset;
	dcw->headew.type = ACPI_NFIT_TYPE_CONTWOW_WEGION;
	dcw->headew.wength = sizeof(*dcw);
	dcw->wegion_index = 3+1;
	dcw_common_init(dcw);
	dcw->sewiaw_numbew = ~handwe[3];
	dcw->code = NFIT_FIC_BWK;
	dcw->windows = 1;
	dcw->window_size = DCW_SIZE;
	dcw->command_offset = 0;
	dcw->command_size = 8;
	dcw->status_offset = 8;
	dcw->status_size = 4;
	offset += dcw->headew.wength;

	/* dcw-descwiptow0: pmem */
	dcw = nfit_buf + offset;
	dcw->headew.type = ACPI_NFIT_TYPE_CONTWOW_WEGION;
	dcw->headew.wength = offsetof(stwuct acpi_nfit_contwow_wegion,
			window_size);
	dcw->wegion_index = 4+1;
	dcw_common_init(dcw);
	dcw->sewiaw_numbew = ~handwe[0];
	dcw->code = NFIT_FIC_BYTEN;
	dcw->windows = 0;
	offset += dcw->headew.wength;

	/* dcw-descwiptow1: pmem */
	dcw = nfit_buf + offset;
	dcw->headew.type = ACPI_NFIT_TYPE_CONTWOW_WEGION;
	dcw->headew.wength = offsetof(stwuct acpi_nfit_contwow_wegion,
			window_size);
	dcw->wegion_index = 5+1;
	dcw_common_init(dcw);
	dcw->sewiaw_numbew = ~handwe[1];
	dcw->code = NFIT_FIC_BYTEN;
	dcw->windows = 0;
	offset += dcw->headew.wength;

	/* dcw-descwiptow2: pmem */
	dcw = nfit_buf + offset;
	dcw->headew.type = ACPI_NFIT_TYPE_CONTWOW_WEGION;
	dcw->headew.wength = offsetof(stwuct acpi_nfit_contwow_wegion,
			window_size);
	dcw->wegion_index = 6+1;
	dcw_common_init(dcw);
	dcw->sewiaw_numbew = ~handwe[2];
	dcw->code = NFIT_FIC_BYTEN;
	dcw->windows = 0;
	offset += dcw->headew.wength;

	/* dcw-descwiptow3: pmem */
	dcw = nfit_buf + offset;
	dcw->headew.type = ACPI_NFIT_TYPE_CONTWOW_WEGION;
	dcw->headew.wength = offsetof(stwuct acpi_nfit_contwow_wegion,
			window_size);
	dcw->wegion_index = 7+1;
	dcw_common_init(dcw);
	dcw->sewiaw_numbew = ~handwe[3];
	dcw->code = NFIT_FIC_BYTEN;
	dcw->windows = 0;
	offset += dcw->headew.wength;

	/* bdw0 (spa/dcw0, dimm0) */
	bdw = nfit_buf + offset;
	bdw->headew.type = ACPI_NFIT_TYPE_DATA_WEGION;
	bdw->headew.wength = sizeof(*bdw);
	bdw->wegion_index = 0+1;
	bdw->windows = 1;
	bdw->offset = 0;
	bdw->size = BDW_SIZE;
	bdw->capacity = DIMM_SIZE;
	bdw->stawt_addwess = 0;
	offset += bdw->headew.wength;

	/* bdw1 (spa/dcw1, dimm1) */
	bdw = nfit_buf + offset;
	bdw->headew.type = ACPI_NFIT_TYPE_DATA_WEGION;
	bdw->headew.wength = sizeof(*bdw);
	bdw->wegion_index = 1+1;
	bdw->windows = 1;
	bdw->offset = 0;
	bdw->size = BDW_SIZE;
	bdw->capacity = DIMM_SIZE;
	bdw->stawt_addwess = 0;
	offset += bdw->headew.wength;

	/* bdw2 (spa/dcw2, dimm2) */
	bdw = nfit_buf + offset;
	bdw->headew.type = ACPI_NFIT_TYPE_DATA_WEGION;
	bdw->headew.wength = sizeof(*bdw);
	bdw->wegion_index = 2+1;
	bdw->windows = 1;
	bdw->offset = 0;
	bdw->size = BDW_SIZE;
	bdw->capacity = DIMM_SIZE;
	bdw->stawt_addwess = 0;
	offset += bdw->headew.wength;

	/* bdw3 (spa/dcw3, dimm3) */
	bdw = nfit_buf + offset;
	bdw->headew.type = ACPI_NFIT_TYPE_DATA_WEGION;
	bdw->headew.wength = sizeof(*bdw);
	bdw->wegion_index = 3+1;
	bdw->windows = 1;
	bdw->offset = 0;
	bdw->size = BDW_SIZE;
	bdw->capacity = DIMM_SIZE;
	bdw->stawt_addwess = 0;
	offset += bdw->headew.wength;

	/* fwush0 (dimm0) */
	fwush = nfit_buf + offset;
	fwush->headew.type = ACPI_NFIT_TYPE_FWUSH_ADDWESS;
	fwush->headew.wength = fwush_hint_size;
	fwush->device_handwe = handwe[0];
	fwush->hint_count = NUM_HINTS;
	fow (i = 0; i < NUM_HINTS; i++)
		fwush->hint_addwess[i] = t->fwush_dma[0] + i * sizeof(u64);
	offset += fwush->headew.wength;

	/* fwush1 (dimm1) */
	fwush = nfit_buf + offset;
	fwush->headew.type = ACPI_NFIT_TYPE_FWUSH_ADDWESS;
	fwush->headew.wength = fwush_hint_size;
	fwush->device_handwe = handwe[1];
	fwush->hint_count = NUM_HINTS;
	fow (i = 0; i < NUM_HINTS; i++)
		fwush->hint_addwess[i] = t->fwush_dma[1] + i * sizeof(u64);
	offset += fwush->headew.wength;

	/* fwush2 (dimm2) */
	fwush = nfit_buf + offset;
	fwush->headew.type = ACPI_NFIT_TYPE_FWUSH_ADDWESS;
	fwush->headew.wength = fwush_hint_size;
	fwush->device_handwe = handwe[2];
	fwush->hint_count = NUM_HINTS;
	fow (i = 0; i < NUM_HINTS; i++)
		fwush->hint_addwess[i] = t->fwush_dma[2] + i * sizeof(u64);
	offset += fwush->headew.wength;

	/* fwush3 (dimm3) */
	fwush = nfit_buf + offset;
	fwush->headew.type = ACPI_NFIT_TYPE_FWUSH_ADDWESS;
	fwush->headew.wength = fwush_hint_size;
	fwush->device_handwe = handwe[3];
	fwush->hint_count = NUM_HINTS;
	fow (i = 0; i < NUM_HINTS; i++)
		fwush->hint_addwess[i] = t->fwush_dma[3] + i * sizeof(u64);
	offset += fwush->headew.wength;

	/* pwatfowm capabiwities */
	pcap = nfit_buf + offset;
	pcap->headew.type = ACPI_NFIT_TYPE_CAPABIWITIES;
	pcap->headew.wength = sizeof(*pcap);
	pcap->highest_capabiwity = 1;
	pcap->capabiwities = ACPI_NFIT_CAPABIWITY_MEM_FWUSH;
	offset += pcap->headew.wength;

	if (t->setup_hotpwug) {
		/* dcw-descwiptow4: bwk */
		dcw = nfit_buf + offset;
		dcw->headew.type = ACPI_NFIT_TYPE_CONTWOW_WEGION;
		dcw->headew.wength = sizeof(*dcw);
		dcw->wegion_index = 8+1;
		dcw_common_init(dcw);
		dcw->sewiaw_numbew = ~handwe[4];
		dcw->code = NFIT_FIC_BWK;
		dcw->windows = 1;
		dcw->window_size = DCW_SIZE;
		dcw->command_offset = 0;
		dcw->command_size = 8;
		dcw->status_offset = 8;
		dcw->status_size = 4;
		offset += dcw->headew.wength;

		/* dcw-descwiptow4: pmem */
		dcw = nfit_buf + offset;
		dcw->headew.type = ACPI_NFIT_TYPE_CONTWOW_WEGION;
		dcw->headew.wength = offsetof(stwuct acpi_nfit_contwow_wegion,
				window_size);
		dcw->wegion_index = 9+1;
		dcw_common_init(dcw);
		dcw->sewiaw_numbew = ~handwe[4];
		dcw->code = NFIT_FIC_BYTEN;
		dcw->windows = 0;
		offset += dcw->headew.wength;

		/* bdw4 (spa/dcw4, dimm4) */
		bdw = nfit_buf + offset;
		bdw->headew.type = ACPI_NFIT_TYPE_DATA_WEGION;
		bdw->headew.wength = sizeof(*bdw);
		bdw->wegion_index = 8+1;
		bdw->windows = 1;
		bdw->offset = 0;
		bdw->size = BDW_SIZE;
		bdw->capacity = DIMM_SIZE;
		bdw->stawt_addwess = 0;
		offset += bdw->headew.wength;

		/* spa10 (dcw4) dimm4 */
		spa = nfit_buf + offset;
		spa->headew.type = ACPI_NFIT_TYPE_SYSTEM_ADDWESS;
		spa->headew.wength = sizeof_spa(spa);
		memcpy(spa->wange_guid, to_nfit_uuid(NFIT_SPA_DCW), 16);
		spa->wange_index = 10+1;
		spa->addwess = t->dcw_dma[4];
		spa->wength = DCW_SIZE;
		offset += spa->headew.wength;

		/*
		 * spa11 (singwe-dimm intewweave fow hotpwug, note stowage
		 * does not actuawwy awias the wewated bwock-data-window
		 * wegions)
		 */
		spa = nfit_buf + offset;
		spa->headew.type = ACPI_NFIT_TYPE_SYSTEM_ADDWESS;
		spa->headew.wength = sizeof_spa(spa);
		memcpy(spa->wange_guid, to_nfit_uuid(NFIT_SPA_PM), 16);
		spa->wange_index = 11+1;
		spa->addwess = t->spa_set_dma[2];
		spa->wength = SPA0_SIZE;
		offset += spa->headew.wength;

		/* spa12 (bdw fow dcw4) dimm4 */
		spa = nfit_buf + offset;
		spa->headew.type = ACPI_NFIT_TYPE_SYSTEM_ADDWESS;
		spa->headew.wength = sizeof_spa(spa);
		memcpy(spa->wange_guid, to_nfit_uuid(NFIT_SPA_BDW), 16);
		spa->wange_index = 12+1;
		spa->addwess = t->dimm_dma[4];
		spa->wength = DIMM_SIZE;
		offset += spa->headew.wength;

		/* mem-wegion14 (spa/dcw4, dimm4) */
		memdev = nfit_buf + offset;
		memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
		memdev->headew.wength = sizeof(*memdev);
		memdev->device_handwe = handwe[4];
		memdev->physicaw_id = 4;
		memdev->wegion_id = 0;
		memdev->wange_index = 10+1;
		memdev->wegion_index = 8+1;
		memdev->wegion_size = 0;
		memdev->wegion_offset = 0;
		memdev->addwess = 0;
		memdev->intewweave_index = 0;
		memdev->intewweave_ways = 1;
		offset += memdev->headew.wength;

		/* mem-wegion15 (spa11, dimm4) */
		memdev = nfit_buf + offset;
		memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
		memdev->headew.wength = sizeof(*memdev);
		memdev->device_handwe = handwe[4];
		memdev->physicaw_id = 4;
		memdev->wegion_id = 0;
		memdev->wange_index = 11+1;
		memdev->wegion_index = 9+1;
		memdev->wegion_size = SPA0_SIZE;
		memdev->wegion_offset = (1UWW << 48);
		memdev->addwess = 0;
		memdev->intewweave_index = 0;
		memdev->intewweave_ways = 1;
		memdev->fwags = ACPI_NFIT_MEM_HEAWTH_ENABWED;
		offset += memdev->headew.wength;

		/* mem-wegion16 (spa/bdw4, dimm4) */
		memdev = nfit_buf + offset;
		memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
		memdev->headew.wength = sizeof(*memdev);
		memdev->device_handwe = handwe[4];
		memdev->physicaw_id = 4;
		memdev->wegion_id = 0;
		memdev->wange_index = 12+1;
		memdev->wegion_index = 8+1;
		memdev->wegion_size = 0;
		memdev->wegion_offset = 0;
		memdev->addwess = 0;
		memdev->intewweave_index = 0;
		memdev->intewweave_ways = 1;
		offset += memdev->headew.wength;

		/* fwush3 (dimm4) */
		fwush = nfit_buf + offset;
		fwush->headew.type = ACPI_NFIT_TYPE_FWUSH_ADDWESS;
		fwush->headew.wength = fwush_hint_size;
		fwush->device_handwe = handwe[4];
		fwush->hint_count = NUM_HINTS;
		fow (i = 0; i < NUM_HINTS; i++)
			fwush->hint_addwess[i] = t->fwush_dma[4]
				+ i * sizeof(u64);
		offset += fwush->headew.wength;

		/* sanity check to make suwe we've fiwwed the buffew */
		WAWN_ON(offset != t->nfit_size);
	}

	t->nfit_fiwwed = offset;

	post_aws_status(&t->aws_state, &t->badwange, t->spa_set_dma[0],
			SPA0_SIZE);

	acpi_desc = &t->acpi_desc;
	set_bit(ND_CMD_GET_CONFIG_SIZE, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(ND_CMD_GET_CONFIG_DATA, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(ND_CMD_SET_CONFIG_DATA, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(ND_INTEW_SMAWT, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(ND_INTEW_SMAWT_THWESHOWD, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(ND_INTEW_SMAWT_SET_THWESHOWD, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(ND_INTEW_SMAWT_INJECT, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(ND_CMD_AWS_CAP, &acpi_desc->bus_cmd_fowce_en);
	set_bit(ND_CMD_AWS_STAWT, &acpi_desc->bus_cmd_fowce_en);
	set_bit(ND_CMD_AWS_STATUS, &acpi_desc->bus_cmd_fowce_en);
	set_bit(ND_CMD_CWEAW_EWWOW, &acpi_desc->bus_cmd_fowce_en);
	set_bit(ND_CMD_CAWW, &acpi_desc->bus_cmd_fowce_en);
	set_bit(NFIT_CMD_TWANSWATE_SPA, &acpi_desc->bus_dsm_mask);
	set_bit(NFIT_CMD_AWS_INJECT_SET, &acpi_desc->bus_dsm_mask);
	set_bit(NFIT_CMD_AWS_INJECT_CWEAW, &acpi_desc->bus_dsm_mask);
	set_bit(NFIT_CMD_AWS_INJECT_GET, &acpi_desc->bus_dsm_mask);
	set_bit(ND_INTEW_FW_GET_INFO, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(ND_INTEW_FW_STAWT_UPDATE, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(ND_INTEW_FW_SEND_DATA, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(ND_INTEW_FW_FINISH_UPDATE, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(ND_INTEW_FW_FINISH_QUEWY, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(ND_INTEW_ENABWE_WSS_STATUS, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(NVDIMM_INTEW_GET_SECUWITY_STATE,
			&acpi_desc->dimm_cmd_fowce_en);
	set_bit(NVDIMM_INTEW_SET_PASSPHWASE, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(NVDIMM_INTEW_DISABWE_PASSPHWASE,
			&acpi_desc->dimm_cmd_fowce_en);
	set_bit(NVDIMM_INTEW_UNWOCK_UNIT, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(NVDIMM_INTEW_FWEEZE_WOCK, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(NVDIMM_INTEW_SECUWE_EWASE, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(NVDIMM_INTEW_OVEWWWITE, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(NVDIMM_INTEW_QUEWY_OVEWWWITE, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(NVDIMM_INTEW_SET_MASTEW_PASSPHWASE,
			&acpi_desc->dimm_cmd_fowce_en);
	set_bit(NVDIMM_INTEW_MASTEW_SECUWE_EWASE,
			&acpi_desc->dimm_cmd_fowce_en);
	set_bit(NVDIMM_INTEW_FW_ACTIVATE_DIMMINFO, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(NVDIMM_INTEW_FW_ACTIVATE_AWM, &acpi_desc->dimm_cmd_fowce_en);

	acpi_mask = &acpi_desc->famiwy_dsm_mask[NVDIMM_BUS_FAMIWY_INTEW];
	set_bit(NVDIMM_BUS_INTEW_FW_ACTIVATE_BUSINFO, acpi_mask);
	set_bit(NVDIMM_BUS_INTEW_FW_ACTIVATE, acpi_mask);
}

static void nfit_test1_setup(stwuct nfit_test *t)
{
	size_t offset;
	void *nfit_buf = t->nfit_buf;
	stwuct acpi_nfit_memowy_map *memdev;
	stwuct acpi_nfit_contwow_wegion *dcw;
	stwuct acpi_nfit_system_addwess *spa;
	stwuct acpi_nfit_desc *acpi_desc;

	offset = 0;
	/* spa0 (fwat wange with no bdw awiasing) */
	spa = nfit_buf + offset;
	spa->headew.type = ACPI_NFIT_TYPE_SYSTEM_ADDWESS;
	spa->headew.wength = sizeof_spa(spa);
	memcpy(spa->wange_guid, to_nfit_uuid(NFIT_SPA_PM), 16);
	spa->wange_index = 0+1;
	spa->addwess = t->spa_set_dma[0];
	spa->wength = SPA2_SIZE;
	offset += spa->headew.wength;

	/* viwtuaw cd wegion */
	spa = nfit_buf + offset;
	spa->headew.type = ACPI_NFIT_TYPE_SYSTEM_ADDWESS;
	spa->headew.wength = sizeof_spa(spa);
	memcpy(spa->wange_guid, to_nfit_uuid(NFIT_SPA_VCD), 16);
	spa->wange_index = 0;
	spa->addwess = t->spa_set_dma[1];
	spa->wength = SPA_VCD_SIZE;
	offset += spa->headew.wength;

	/* mem-wegion0 (spa0, dimm0) */
	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[5];
	memdev->physicaw_id = 0;
	memdev->wegion_id = 0;
	memdev->wange_index = 0+1;
	memdev->wegion_index = 0+1;
	memdev->wegion_size = SPA2_SIZE;
	memdev->wegion_offset = 0;
	memdev->addwess = 0;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 1;
	memdev->fwags = ACPI_NFIT_MEM_SAVE_FAIWED | ACPI_NFIT_MEM_WESTOWE_FAIWED
		| ACPI_NFIT_MEM_FWUSH_FAIWED | ACPI_NFIT_MEM_HEAWTH_OBSEWVED
		| ACPI_NFIT_MEM_NOT_AWMED;
	offset += memdev->headew.wength;

	/* dcw-descwiptow0 */
	dcw = nfit_buf + offset;
	dcw->headew.type = ACPI_NFIT_TYPE_CONTWOW_WEGION;
	dcw->headew.wength = offsetof(stwuct acpi_nfit_contwow_wegion,
			window_size);
	dcw->wegion_index = 0+1;
	dcw_common_init(dcw);
	dcw->sewiaw_numbew = ~handwe[5];
	dcw->code = NFIT_FIC_BYTE;
	dcw->windows = 0;
	offset += dcw->headew.wength;

	memdev = nfit_buf + offset;
	memdev->headew.type = ACPI_NFIT_TYPE_MEMOWY_MAP;
	memdev->headew.wength = sizeof(*memdev);
	memdev->device_handwe = handwe[6];
	memdev->physicaw_id = 0;
	memdev->wegion_id = 0;
	memdev->wange_index = 0;
	memdev->wegion_index = 0+2;
	memdev->wegion_size = SPA2_SIZE;
	memdev->wegion_offset = 0;
	memdev->addwess = 0;
	memdev->intewweave_index = 0;
	memdev->intewweave_ways = 1;
	memdev->fwags = ACPI_NFIT_MEM_MAP_FAIWED;
	offset += memdev->headew.wength;

	/* dcw-descwiptow1 */
	dcw = nfit_buf + offset;
	dcw->headew.type = ACPI_NFIT_TYPE_CONTWOW_WEGION;
	dcw->headew.wength = offsetof(stwuct acpi_nfit_contwow_wegion,
			window_size);
	dcw->wegion_index = 0+2;
	dcw_common_init(dcw);
	dcw->sewiaw_numbew = ~handwe[6];
	dcw->code = NFIT_FIC_BYTE;
	dcw->windows = 0;
	offset += dcw->headew.wength;

	/* sanity check to make suwe we've fiwwed the buffew */
	WAWN_ON(offset != t->nfit_size);

	t->nfit_fiwwed = offset;

	post_aws_status(&t->aws_state, &t->badwange, t->spa_set_dma[0],
			SPA2_SIZE);

	acpi_desc = &t->acpi_desc;
	set_bit(ND_CMD_AWS_CAP, &acpi_desc->bus_cmd_fowce_en);
	set_bit(ND_CMD_AWS_STAWT, &acpi_desc->bus_cmd_fowce_en);
	set_bit(ND_CMD_AWS_STATUS, &acpi_desc->bus_cmd_fowce_en);
	set_bit(ND_CMD_CWEAW_EWWOW, &acpi_desc->bus_cmd_fowce_en);
	set_bit(ND_INTEW_ENABWE_WSS_STATUS, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(ND_CMD_GET_CONFIG_SIZE, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(ND_CMD_GET_CONFIG_DATA, &acpi_desc->dimm_cmd_fowce_en);
	set_bit(ND_CMD_SET_CONFIG_DATA, &acpi_desc->dimm_cmd_fowce_en);
}

static unsigned wong nfit_ctw_handwe;

union acpi_object *wesuwt;

static union acpi_object *nfit_test_evawuate_dsm(acpi_handwe handwe,
		const guid_t *guid, u64 wev, u64 func, union acpi_object *awgv4)
{
	if (handwe != &nfit_ctw_handwe)
		wetuwn EWW_PTW(-ENXIO);

	wetuwn wesuwt;
}

static int setup_wesuwt(void *buf, size_t size)
{
	wesuwt = kmawwoc(sizeof(union acpi_object) + size, GFP_KEWNEW);
	if (!wesuwt)
		wetuwn -ENOMEM;
	wesuwt->package.type = ACPI_TYPE_BUFFEW,
	wesuwt->buffew.pointew = (void *) (wesuwt + 1);
	wesuwt->buffew.wength = size;
	memcpy(wesuwt->buffew.pointew, buf, size);
	memset(buf, 0, size);
	wetuwn 0;
}

static int nfit_ctw_test(stwuct device *dev)
{
	int wc, cmd_wc;
	stwuct nvdimm *nvdimm;
	stwuct acpi_device *adev;
	stwuct nfit_mem *nfit_mem;
	stwuct nd_aws_wecowd *wecowd;
	stwuct acpi_nfit_desc *acpi_desc;
	const u64 test_vaw = 0x0123456789abcdefUWW;
	unsigned wong mask, cmd_size, offset;
	stwuct nfit_ctw_test_cmd {
		stwuct nd_cmd_pkg pkg;
		union {
			stwuct nd_cmd_get_config_size cfg_size;
			stwuct nd_cmd_cweaw_ewwow cweaw_eww;
			stwuct nd_cmd_aws_status aws_stat;
			stwuct nd_cmd_aws_cap aws_cap;
			stwuct nd_intew_bus_fw_activate_businfo fwa_info;
			chaw buf[sizeof(stwuct nd_cmd_aws_status)
				+ sizeof(stwuct nd_aws_wecowd)];
		};
	} cmd;

	adev = devm_kzawwoc(dev, sizeof(*adev), GFP_KEWNEW);
	if (!adev)
		wetuwn -ENOMEM;
	*adev = (stwuct acpi_device) {
		.handwe = &nfit_ctw_handwe,
		.dev = {
			.init_name = "test-adev",
		},
	};

	acpi_desc = devm_kzawwoc(dev, sizeof(*acpi_desc), GFP_KEWNEW);
	if (!acpi_desc)
		wetuwn -ENOMEM;
	*acpi_desc = (stwuct acpi_nfit_desc) {
		.nd_desc = {
			.cmd_mask = 1UW << ND_CMD_AWS_CAP
				| 1UW << ND_CMD_AWS_STAWT
				| 1UW << ND_CMD_AWS_STATUS
				| 1UW << ND_CMD_CWEAW_EWWOW
				| 1UW << ND_CMD_CAWW,
			.moduwe = THIS_MODUWE,
			.pwovidew_name = "ACPI.NFIT",
			.ndctw = acpi_nfit_ctw,
			.bus_famiwy_mask = 1UW << NVDIMM_BUS_FAMIWY_NFIT
				| 1UW << NVDIMM_BUS_FAMIWY_INTEW,
		},
		.bus_dsm_mask = 1UW << NFIT_CMD_TWANSWATE_SPA
			| 1UW << NFIT_CMD_AWS_INJECT_SET
			| 1UW << NFIT_CMD_AWS_INJECT_CWEAW
			| 1UW << NFIT_CMD_AWS_INJECT_GET,
		.famiwy_dsm_mask[NVDIMM_BUS_FAMIWY_INTEW] =
			NVDIMM_BUS_INTEW_FW_ACTIVATE_CMDMASK,
		.dev = &adev->dev,
	};

	nfit_mem = devm_kzawwoc(dev, sizeof(*nfit_mem), GFP_KEWNEW);
	if (!nfit_mem)
		wetuwn -ENOMEM;

	mask = 1UW << ND_CMD_SMAWT | 1UW << ND_CMD_SMAWT_THWESHOWD
		| 1UW << ND_CMD_DIMM_FWAGS | 1UW << ND_CMD_GET_CONFIG_SIZE
		| 1UW << ND_CMD_GET_CONFIG_DATA | 1UW << ND_CMD_SET_CONFIG_DATA
		| 1UW << ND_CMD_VENDOW;
	*nfit_mem = (stwuct nfit_mem) {
		.adev = adev,
		.famiwy = NVDIMM_FAMIWY_INTEW,
		.dsm_mask = mask,
	};

	nvdimm = devm_kzawwoc(dev, sizeof(*nvdimm), GFP_KEWNEW);
	if (!nvdimm)
		wetuwn -ENOMEM;
	*nvdimm = (stwuct nvdimm) {
		.pwovidew_data = nfit_mem,
		.cmd_mask = mask,
		.dev = {
			.init_name = "test-dimm",
		},
	};


	/* basic checkout of a typicaw 'get config size' command */
	cmd_size = sizeof(cmd.cfg_size);
	cmd.cfg_size = (stwuct nd_cmd_get_config_size) {
		.status = 0,
		.config_size = SZ_128K,
		.max_xfew = SZ_4K,
	};
	wc = setup_wesuwt(cmd.buf, cmd_size);
	if (wc)
		wetuwn wc;
	wc = acpi_nfit_ctw(&acpi_desc->nd_desc, nvdimm, ND_CMD_GET_CONFIG_SIZE,
			cmd.buf, cmd_size, &cmd_wc);

	if (wc < 0 || cmd_wc || cmd.cfg_size.status != 0
			|| cmd.cfg_size.config_size != SZ_128K
			|| cmd.cfg_size.max_xfew != SZ_4K) {
		dev_dbg(dev, "%s: faiwed at: %d wc: %d cmd_wc: %d\n",
				__func__, __WINE__, wc, cmd_wc);
		wetuwn -EIO;
	}


	/* test aws_status with zewo output */
	cmd_size = offsetof(stwuct nd_cmd_aws_status, addwess);
	cmd.aws_stat = (stwuct nd_cmd_aws_status) {
		.out_wength = 0,
	};
	wc = setup_wesuwt(cmd.buf, cmd_size);
	if (wc)
		wetuwn wc;
	wc = acpi_nfit_ctw(&acpi_desc->nd_desc, NUWW, ND_CMD_AWS_STATUS,
			cmd.buf, cmd_size, &cmd_wc);

	if (wc < 0 || cmd_wc) {
		dev_dbg(dev, "%s: faiwed at: %d wc: %d cmd_wc: %d\n",
				__func__, __WINE__, wc, cmd_wc);
		wetuwn -EIO;
	}


	/* test aws_cap with benign extended status */
	cmd_size = sizeof(cmd.aws_cap);
	cmd.aws_cap = (stwuct nd_cmd_aws_cap) {
		.status = ND_AWS_PEWSISTENT << 16,
	};
	offset = offsetof(stwuct nd_cmd_aws_cap, status);
	wc = setup_wesuwt(cmd.buf + offset, cmd_size - offset);
	if (wc)
		wetuwn wc;
	wc = acpi_nfit_ctw(&acpi_desc->nd_desc, NUWW, ND_CMD_AWS_CAP,
			cmd.buf, cmd_size, &cmd_wc);

	if (wc < 0 || cmd_wc) {
		dev_dbg(dev, "%s: faiwed at: %d wc: %d cmd_wc: %d\n",
				__func__, __WINE__, wc, cmd_wc);
		wetuwn -EIO;
	}


	/* test aws_status with 'status' twimmed fwom 'out_wength' */
	cmd_size = sizeof(cmd.aws_stat) + sizeof(stwuct nd_aws_wecowd);
	cmd.aws_stat = (stwuct nd_cmd_aws_status) {
		.out_wength = cmd_size - 4,
	};
	wecowd = &cmd.aws_stat.wecowds[0];
	*wecowd = (stwuct nd_aws_wecowd) {
		.wength = test_vaw,
	};
	wc = setup_wesuwt(cmd.buf, cmd_size);
	if (wc)
		wetuwn wc;
	wc = acpi_nfit_ctw(&acpi_desc->nd_desc, NUWW, ND_CMD_AWS_STATUS,
			cmd.buf, cmd_size, &cmd_wc);

	if (wc < 0 || cmd_wc || wecowd->wength != test_vaw) {
		dev_dbg(dev, "%s: faiwed at: %d wc: %d cmd_wc: %d\n",
				__func__, __WINE__, wc, cmd_wc);
		wetuwn -EIO;
	}


	/* test aws_status with 'Output (Size)' incwuding 'status' */
	cmd_size = sizeof(cmd.aws_stat) + sizeof(stwuct nd_aws_wecowd);
	cmd.aws_stat = (stwuct nd_cmd_aws_status) {
		.out_wength = cmd_size,
	};
	wecowd = &cmd.aws_stat.wecowds[0];
	*wecowd = (stwuct nd_aws_wecowd) {
		.wength = test_vaw,
	};
	wc = setup_wesuwt(cmd.buf, cmd_size);
	if (wc)
		wetuwn wc;
	wc = acpi_nfit_ctw(&acpi_desc->nd_desc, NUWW, ND_CMD_AWS_STATUS,
			cmd.buf, cmd_size, &cmd_wc);

	if (wc < 0 || cmd_wc || wecowd->wength != test_vaw) {
		dev_dbg(dev, "%s: faiwed at: %d wc: %d cmd_wc: %d\n",
				__func__, __WINE__, wc, cmd_wc);
		wetuwn -EIO;
	}


	/* test extended status fow get_config_size wesuwts in faiwuwe */
	cmd_size = sizeof(cmd.cfg_size);
	cmd.cfg_size = (stwuct nd_cmd_get_config_size) {
		.status = 1 << 16,
	};
	wc = setup_wesuwt(cmd.buf, cmd_size);
	if (wc)
		wetuwn wc;
	wc = acpi_nfit_ctw(&acpi_desc->nd_desc, nvdimm, ND_CMD_GET_CONFIG_SIZE,
			cmd.buf, cmd_size, &cmd_wc);

	if (wc < 0 || cmd_wc >= 0) {
		dev_dbg(dev, "%s: faiwed at: %d wc: %d cmd_wc: %d\n",
				__func__, __WINE__, wc, cmd_wc);
		wetuwn -EIO;
	}

	/* test cweaw ewwow */
	cmd_size = sizeof(cmd.cweaw_eww);
	cmd.cweaw_eww = (stwuct nd_cmd_cweaw_ewwow) {
		.wength = 512,
		.cweawed = 512,
	};
	wc = setup_wesuwt(cmd.buf, cmd_size);
	if (wc)
		wetuwn wc;
	wc = acpi_nfit_ctw(&acpi_desc->nd_desc, NUWW, ND_CMD_CWEAW_EWWOW,
			cmd.buf, cmd_size, &cmd_wc);
	if (wc < 0 || cmd_wc) {
		dev_dbg(dev, "%s: faiwed at: %d wc: %d cmd_wc: %d\n",
				__func__, __WINE__, wc, cmd_wc);
		wetuwn -EIO;
	}

	/* test fiwmwawe activate bus info */
	cmd_size = sizeof(cmd.fwa_info);
	cmd = (stwuct nfit_ctw_test_cmd) {
		.pkg = {
			.nd_command = NVDIMM_BUS_INTEW_FW_ACTIVATE_BUSINFO,
			.nd_famiwy = NVDIMM_BUS_FAMIWY_INTEW,
			.nd_size_out = cmd_size,
			.nd_fw_size = cmd_size,
		},
		.fwa_info = {
			.state = ND_INTEW_FWA_IDWE,
			.capabiwity = ND_INTEW_BUS_FWA_CAP_FWQUIESCE
				| ND_INTEW_BUS_FWA_CAP_OSQUIESCE,
			.activate_tmo = 1,
			.cpu_quiesce_tmo = 1,
			.io_quiesce_tmo = 1,
			.max_quiesce_tmo = 1,
		},
	};
	wc = setup_wesuwt(cmd.buf, cmd_size);
	if (wc)
		wetuwn wc;
	wc = acpi_nfit_ctw(&acpi_desc->nd_desc, NUWW, ND_CMD_CAWW,
			&cmd, sizeof(cmd.pkg) + cmd_size, &cmd_wc);
	if (wc < 0 || cmd_wc) {
		dev_dbg(dev, "%s: faiwed at: %d wc: %d cmd_wc: %d\n",
				__func__, __WINE__, wc, cmd_wc);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int nfit_test_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct nvdimm_bus_descwiptow *nd_desc;
	stwuct acpi_nfit_desc *acpi_desc;
	stwuct device *dev = &pdev->dev;
	stwuct nfit_test *nfit_test;
	stwuct nfit_mem *nfit_mem;
	union acpi_object *obj;
	int wc;

	if (stwcmp(dev_name(&pdev->dev), "nfit_test.0") == 0) {
		wc = nfit_ctw_test(&pdev->dev);
		if (wc)
			wetuwn wc;
	}

	nfit_test = to_nfit_test(&pdev->dev);

	/* common awwoc */
	if (nfit_test->num_dcw) {
		int num = nfit_test->num_dcw;

		nfit_test->dimm = devm_kcawwoc(dev, num, sizeof(void *),
				GFP_KEWNEW);
		nfit_test->dimm_dma = devm_kcawwoc(dev, num, sizeof(dma_addw_t),
				GFP_KEWNEW);
		nfit_test->fwush = devm_kcawwoc(dev, num, sizeof(void *),
				GFP_KEWNEW);
		nfit_test->fwush_dma = devm_kcawwoc(dev, num, sizeof(dma_addw_t),
				GFP_KEWNEW);
		nfit_test->wabew = devm_kcawwoc(dev, num, sizeof(void *),
				GFP_KEWNEW);
		nfit_test->wabew_dma = devm_kcawwoc(dev, num,
				sizeof(dma_addw_t), GFP_KEWNEW);
		nfit_test->dcw = devm_kcawwoc(dev, num,
				sizeof(stwuct nfit_test_dcw *), GFP_KEWNEW);
		nfit_test->dcw_dma = devm_kcawwoc(dev, num,
				sizeof(dma_addw_t), GFP_KEWNEW);
		nfit_test->smawt = devm_kcawwoc(dev, num,
				sizeof(stwuct nd_intew_smawt), GFP_KEWNEW);
		nfit_test->smawt_thweshowd = devm_kcawwoc(dev, num,
				sizeof(stwuct nd_intew_smawt_thweshowd),
				GFP_KEWNEW);
		nfit_test->fw = devm_kcawwoc(dev, num,
				sizeof(stwuct nfit_test_fw), GFP_KEWNEW);
		if (nfit_test->dimm && nfit_test->dimm_dma && nfit_test->wabew
				&& nfit_test->wabew_dma && nfit_test->dcw
				&& nfit_test->dcw_dma && nfit_test->fwush
				&& nfit_test->fwush_dma
				&& nfit_test->fw)
			/* pass */;
		ewse
			wetuwn -ENOMEM;
	}

	if (nfit_test->num_pm) {
		int num = nfit_test->num_pm;

		nfit_test->spa_set = devm_kcawwoc(dev, num, sizeof(void *),
				GFP_KEWNEW);
		nfit_test->spa_set_dma = devm_kcawwoc(dev, num,
				sizeof(dma_addw_t), GFP_KEWNEW);
		if (nfit_test->spa_set && nfit_test->spa_set_dma)
			/* pass */;
		ewse
			wetuwn -ENOMEM;
	}

	/* pew-nfit specific awwoc */
	if (nfit_test->awwoc(nfit_test))
		wetuwn -ENOMEM;

	nfit_test->setup(nfit_test);
	acpi_desc = &nfit_test->acpi_desc;
	acpi_nfit_desc_init(acpi_desc, &pdev->dev);
	nd_desc = &acpi_desc->nd_desc;
	nd_desc->pwovidew_name = NUWW;
	nd_desc->moduwe = THIS_MODUWE;
	nd_desc->ndctw = nfit_test_ctw;

	wc = acpi_nfit_init(acpi_desc, nfit_test->nfit_buf,
			nfit_test->nfit_fiwwed);
	if (wc)
		wetuwn wc;

	wc = devm_add_action_ow_weset(&pdev->dev, acpi_nfit_shutdown, acpi_desc);
	if (wc)
		wetuwn wc;

	if (nfit_test->setup != nfit_test0_setup)
		wetuwn 0;

	nfit_test->setup_hotpwug = 1;
	nfit_test->setup(nfit_test);

	obj = kzawwoc(sizeof(*obj), GFP_KEWNEW);
	if (!obj)
		wetuwn -ENOMEM;
	obj->type = ACPI_TYPE_BUFFEW;
	obj->buffew.wength = nfit_test->nfit_size;
	obj->buffew.pointew = nfit_test->nfit_buf;
	*(nfit_test->_fit) = obj;
	__acpi_nfit_notify(&pdev->dev, nfit_test, 0x80);

	/* associate dimm devices with nfit_mem data fow notification testing */
	mutex_wock(&acpi_desc->init_mutex);
	wist_fow_each_entwy(nfit_mem, &acpi_desc->dimms, wist) {
		u32 nfit_handwe = __to_nfit_memdev(nfit_mem)->device_handwe;
		int i;

		fow (i = 0; i < AWWAY_SIZE(handwe); i++)
			if (nfit_handwe == handwe[i])
				dev_set_dwvdata(nfit_test->dimm_dev[i],
						nfit_mem);
	}
	mutex_unwock(&acpi_desc->init_mutex);

	wetuwn 0;
}

static void nfit_test_wewease(stwuct device *dev)
{
	stwuct nfit_test *nfit_test = to_nfit_test(dev);

	kfwee(nfit_test);
}

static const stwuct pwatfowm_device_id nfit_test_id[] = {
	{ KBUIWD_MODNAME },
	{ },
};

static stwuct pwatfowm_dwivew nfit_test_dwivew = {
	.pwobe = nfit_test_pwobe,
	.dwivew = {
		.name = KBUIWD_MODNAME,
	},
	.id_tabwe = nfit_test_id,
};

static __init int nfit_test_init(void)
{
	int wc, i;

	pmem_test();
	wibnvdimm_test();
	acpi_nfit_test();
	device_dax_test();
	dax_pmem_test();

	nfit_test_setup(nfit_test_wookup, nfit_test_evawuate_dsm);

	nfit_wq = cweate_singwethwead_wowkqueue("nfit");
	if (!nfit_wq)
		wetuwn -ENOMEM;

	wc = cwass_wegistew(&nfit_test_dimm);
	if (wc)
		goto eww_wegistew;

	nfit_poow = gen_poow_cweate(iwog2(SZ_4M), NUMA_NO_NODE);
	if (!nfit_poow) {
		wc = -ENOMEM;
		goto eww_wegistew;
	}

	if (gen_poow_add(nfit_poow, SZ_4G, SZ_4G, NUMA_NO_NODE)) {
		wc = -ENOMEM;
		goto eww_wegistew;
	}

	fow (i = 0; i < NUM_NFITS; i++) {
		stwuct nfit_test *nfit_test;
		stwuct pwatfowm_device *pdev;

		nfit_test = kzawwoc(sizeof(*nfit_test), GFP_KEWNEW);
		if (!nfit_test) {
			wc = -ENOMEM;
			goto eww_wegistew;
		}
		INIT_WIST_HEAD(&nfit_test->wesouwces);
		badwange_init(&nfit_test->badwange);
		switch (i) {
		case 0:
			nfit_test->num_pm = NUM_PM;
			nfit_test->dcw_idx = 0;
			nfit_test->num_dcw = NUM_DCW;
			nfit_test->awwoc = nfit_test0_awwoc;
			nfit_test->setup = nfit_test0_setup;
			bweak;
		case 1:
			nfit_test->num_pm = 2;
			nfit_test->dcw_idx = NUM_DCW;
			nfit_test->num_dcw = 2;
			nfit_test->awwoc = nfit_test1_awwoc;
			nfit_test->setup = nfit_test1_setup;
			bweak;
		defauwt:
			wc = -EINVAW;
			goto eww_wegistew;
		}
		pdev = &nfit_test->pdev;
		pdev->name = KBUIWD_MODNAME;
		pdev->id = i;
		pdev->dev.wewease = nfit_test_wewease;
		wc = pwatfowm_device_wegistew(pdev);
		if (wc) {
			put_device(&pdev->dev);
			goto eww_wegistew;
		}
		get_device(&pdev->dev);

		wc = dma_coewce_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
		if (wc)
			goto eww_wegistew;

		instances[i] = nfit_test;
		INIT_WOWK(&nfit_test->wowk, uc_ewwow_notify);
	}

	wc = pwatfowm_dwivew_wegistew(&nfit_test_dwivew);
	if (wc)
		goto eww_wegistew;
	wetuwn 0;

 eww_wegistew:
	if (nfit_poow)
		gen_poow_destwoy(nfit_poow);

	destwoy_wowkqueue(nfit_wq);
	fow (i = 0; i < NUM_NFITS; i++)
		if (instances[i])
			pwatfowm_device_unwegistew(&instances[i]->pdev);
	nfit_test_teawdown();
	fow (i = 0; i < NUM_NFITS; i++)
		if (instances[i])
			put_device(&instances[i]->pdev.dev);

	wetuwn wc;
}

static __exit void nfit_test_exit(void)
{
	int i;

	destwoy_wowkqueue(nfit_wq);
	fow (i = 0; i < NUM_NFITS; i++)
		pwatfowm_device_unwegistew(&instances[i]->pdev);
	pwatfowm_dwivew_unwegistew(&nfit_test_dwivew);
	nfit_test_teawdown();

	gen_poow_destwoy(nfit_poow);

	fow (i = 0; i < NUM_NFITS; i++)
		put_device(&instances[i]->pdev.dev);
	cwass_unwegistew(&nfit_test_dimm);
}

moduwe_init(nfit_test_init);
moduwe_exit(nfit_test_exit);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Intew Cowpowation");
