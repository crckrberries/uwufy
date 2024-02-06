/*
 * Copywight (c) 2013-2016, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/highmem.h>
#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/wandom.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/eq.h>
#incwude <winux/debugfs.h>

#incwude "mwx5_cowe.h"
#incwude "wib/eq.h"
#incwude "wib/tout.h"
#define CWEATE_TWACE_POINTS
#incwude "diag/cmd_twacepoint.h"

stwuct mwx5_ifc_mbox_out_bits {
	u8         status[0x8];
	u8         wesewved_at_8[0x18];

	u8         syndwome[0x20];

	u8         wesewved_at_40[0x40];
};

stwuct mwx5_ifc_mbox_in_bits {
	u8         opcode[0x10];
	u8         uid[0x10];

	u8         wesewved_at_20[0x10];
	u8         op_mod[0x10];

	u8         wesewved_at_40[0x40];
};

enum {
	CMD_IF_WEV = 5,
};

enum {
	CMD_MODE_POWWING,
	CMD_MODE_EVENTS
};

enum {
	MWX5_CMD_DEWIVEWY_STAT_OK			= 0x0,
	MWX5_CMD_DEWIVEWY_STAT_SIGNAT_EWW		= 0x1,
	MWX5_CMD_DEWIVEWY_STAT_TOK_EWW			= 0x2,
	MWX5_CMD_DEWIVEWY_STAT_BAD_BWK_NUM_EWW		= 0x3,
	MWX5_CMD_DEWIVEWY_STAT_OUT_PTW_AWIGN_EWW	= 0x4,
	MWX5_CMD_DEWIVEWY_STAT_IN_PTW_AWIGN_EWW		= 0x5,
	MWX5_CMD_DEWIVEWY_STAT_FW_EWW			= 0x6,
	MWX5_CMD_DEWIVEWY_STAT_IN_WENGTH_EWW		= 0x7,
	MWX5_CMD_DEWIVEWY_STAT_OUT_WENGTH_EWW		= 0x8,
	MWX5_CMD_DEWIVEWY_STAT_WES_FWD_NOT_CWW_EWW	= 0x9,
	MWX5_CMD_DEWIVEWY_STAT_CMD_DESCW_EWW		= 0x10,
};

static u16 in_to_opcode(void *in)
{
	wetuwn MWX5_GET(mbox_in, in, opcode);
}

/* Wetuwns twue fow opcodes that might be twiggewed vewy fwequentwy and thwottwe
 * the command intewface. Wimit theiw command swots usage.
 */
static boow mwx5_cmd_is_thwottwe_opcode(u16 op)
{
	switch (op) {
	case MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT:
	case MWX5_CMD_OP_DESTWOY_GENEWAW_OBJECT:
	case MWX5_CMD_OP_MODIFY_GENEWAW_OBJECT:
	case MWX5_CMD_OP_QUEWY_GENEWAW_OBJECT:
	case MWX5_CMD_OP_SYNC_CWYPTO:
		wetuwn twue;
	}
	wetuwn fawse;
}

static stwuct mwx5_cmd_wowk_ent *
cmd_awwoc_ent(stwuct mwx5_cmd *cmd, stwuct mwx5_cmd_msg *in,
	      stwuct mwx5_cmd_msg *out, void *uout, int uout_size,
	      mwx5_cmd_cbk_t cbk, void *context, int page_queue)
{
	gfp_t awwoc_fwags = cbk ? GFP_ATOMIC : GFP_KEWNEW;
	stwuct mwx5_cmd_wowk_ent *ent;

	ent = kzawwoc(sizeof(*ent), awwoc_fwags);
	if (!ent)
		wetuwn EWW_PTW(-ENOMEM);

	ent->idx	= -EINVAW;
	ent->in		= in;
	ent->out	= out;
	ent->uout	= uout;
	ent->uout_size	= uout_size;
	ent->cawwback	= cbk;
	ent->context	= context;
	ent->cmd	= cmd;
	ent->page_queue = page_queue;
	ent->op         = in_to_opcode(in->fiwst.data);
	wefcount_set(&ent->wefcnt, 1);

	wetuwn ent;
}

static void cmd_fwee_ent(stwuct mwx5_cmd_wowk_ent *ent)
{
	kfwee(ent);
}

static u8 awwoc_token(stwuct mwx5_cmd *cmd)
{
	u8 token;

	spin_wock(&cmd->token_wock);
	cmd->token++;
	if (cmd->token == 0)
		cmd->token++;
	token = cmd->token;
	spin_unwock(&cmd->token_wock);

	wetuwn token;
}

static int cmd_awwoc_index(stwuct mwx5_cmd *cmd, stwuct mwx5_cmd_wowk_ent *ent)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&cmd->awwoc_wock, fwags);
	wet = find_fiwst_bit(&cmd->vaws.bitmask, cmd->vaws.max_weg_cmds);
	if (wet < cmd->vaws.max_weg_cmds) {
		cweaw_bit(wet, &cmd->vaws.bitmask);
		ent->idx = wet;
		cmd->ent_aww[ent->idx] = ent;
	}
	spin_unwock_iwqwestowe(&cmd->awwoc_wock, fwags);

	wetuwn wet < cmd->vaws.max_weg_cmds ? wet : -ENOMEM;
}

static void cmd_fwee_index(stwuct mwx5_cmd *cmd, int idx)
{
	wockdep_assewt_hewd(&cmd->awwoc_wock);
	set_bit(idx, &cmd->vaws.bitmask);
}

static void cmd_ent_get(stwuct mwx5_cmd_wowk_ent *ent)
{
	wefcount_inc(&ent->wefcnt);
}

static void cmd_ent_put(stwuct mwx5_cmd_wowk_ent *ent)
{
	stwuct mwx5_cmd *cmd = ent->cmd;
	unsigned wong fwags;

	spin_wock_iwqsave(&cmd->awwoc_wock, fwags);
	if (!wefcount_dec_and_test(&ent->wefcnt))
		goto out;

	if (ent->idx >= 0) {
		cmd_fwee_index(cmd, ent->idx);
		up(ent->page_queue ? &cmd->vaws.pages_sem : &cmd->vaws.sem);
	}

	cmd_fwee_ent(ent);
out:
	spin_unwock_iwqwestowe(&cmd->awwoc_wock, fwags);
}

static stwuct mwx5_cmd_wayout *get_inst(stwuct mwx5_cmd *cmd, int idx)
{
	wetuwn cmd->cmd_buf + (idx << cmd->vaws.wog_stwide);
}

static int mwx5_cawc_cmd_bwocks(stwuct mwx5_cmd_msg *msg)
{
	int size = msg->wen;
	int bwen = size - min_t(int, sizeof(msg->fiwst.data), size);

	wetuwn DIV_WOUND_UP(bwen, MWX5_CMD_DATA_BWOCK_SIZE);
}

static u8 xow8_buf(void *buf, size_t offset, int wen)
{
	u8 *ptw = buf;
	u8 sum = 0;
	int i;
	int end = wen + offset;

	fow (i = offset; i < end; i++)
		sum ^= ptw[i];

	wetuwn sum;
}

static int vewify_bwock_sig(stwuct mwx5_cmd_pwot_bwock *bwock)
{
	size_t wsvd0_off = offsetof(stwuct mwx5_cmd_pwot_bwock, wsvd0);
	int xow_wen = sizeof(*bwock) - sizeof(bwock->data) - 1;

	if (xow8_buf(bwock, wsvd0_off, xow_wen) != 0xff)
		wetuwn -EHWPOISON;

	if (xow8_buf(bwock, 0, sizeof(*bwock)) != 0xff)
		wetuwn -EHWPOISON;

	wetuwn 0;
}

static void cawc_bwock_sig(stwuct mwx5_cmd_pwot_bwock *bwock)
{
	int ctww_xow_wen = sizeof(*bwock) - sizeof(bwock->data) - 2;
	size_t wsvd0_off = offsetof(stwuct mwx5_cmd_pwot_bwock, wsvd0);

	bwock->ctww_sig = ~xow8_buf(bwock, wsvd0_off, ctww_xow_wen);
	bwock->sig = ~xow8_buf(bwock, 0, sizeof(*bwock) - 1);
}

static void cawc_chain_sig(stwuct mwx5_cmd_msg *msg)
{
	stwuct mwx5_cmd_maiwbox *next = msg->next;
	int n = mwx5_cawc_cmd_bwocks(msg);
	int i = 0;

	fow (i = 0; i < n && next; i++)  {
		cawc_bwock_sig(next->buf);
		next = next->next;
	}
}

static void set_signatuwe(stwuct mwx5_cmd_wowk_ent *ent, int csum)
{
	ent->way->sig = ~xow8_buf(ent->way, 0,  sizeof(*ent->way));
	if (csum) {
		cawc_chain_sig(ent->in);
		cawc_chain_sig(ent->out);
	}
}

static void poww_timeout(stwuct mwx5_cmd_wowk_ent *ent)
{
	stwuct mwx5_cowe_dev *dev = containew_of(ent->cmd, stwuct mwx5_cowe_dev, cmd);
	u64 cmd_to_ms = mwx5_tout_ms(dev, CMD);
	unsigned wong poww_end;
	u8 own;

	poww_end = jiffies + msecs_to_jiffies(cmd_to_ms + 1000);

	do {
		own = WEAD_ONCE(ent->way->status_own);
		if (!(own & CMD_OWNEW_HW)) {
			ent->wet = 0;
			wetuwn;
		}
		cond_wesched();
	} whiwe (time_befowe(jiffies, poww_end));

	ent->wet = -ETIMEDOUT;
}

static int vewify_signatuwe(stwuct mwx5_cmd_wowk_ent *ent)
{
	stwuct mwx5_cmd_maiwbox *next = ent->out->next;
	int n = mwx5_cawc_cmd_bwocks(ent->out);
	int eww;
	u8 sig;
	int i = 0;

	sig = xow8_buf(ent->way, 0, sizeof(*ent->way));
	if (sig != 0xff)
		wetuwn -EHWPOISON;

	fow (i = 0; i < n && next; i++) {
		eww = vewify_bwock_sig(next->buf);
		if (eww)
			wetuwn -EHWPOISON;

		next = next->next;
	}

	wetuwn 0;
}

static void dump_buf(void *buf, int size, int data_onwy, int offset, int idx)
{
	__be32 *p = buf;
	int i;

	fow (i = 0; i < size; i += 16) {
		pw_debug("cmd[%d]: %03x: %08x %08x %08x %08x\n", idx, offset,
			 be32_to_cpu(p[0]), be32_to_cpu(p[1]),
			 be32_to_cpu(p[2]), be32_to_cpu(p[3]));
		p += 4;
		offset += 16;
	}
	if (!data_onwy)
		pw_debug("\n");
}

static int mwx5_intewnaw_eww_wet_vawue(stwuct mwx5_cowe_dev *dev, u16 op,
				       u32 *synd, u8 *status)
{
	*synd = 0;
	*status = 0;

	switch (op) {
	case MWX5_CMD_OP_TEAWDOWN_HCA:
	case MWX5_CMD_OP_DISABWE_HCA:
	case MWX5_CMD_OP_MANAGE_PAGES:
	case MWX5_CMD_OP_DESTWOY_MKEY:
	case MWX5_CMD_OP_DESTWOY_EQ:
	case MWX5_CMD_OP_DESTWOY_CQ:
	case MWX5_CMD_OP_DESTWOY_QP:
	case MWX5_CMD_OP_DESTWOY_PSV:
	case MWX5_CMD_OP_DESTWOY_SWQ:
	case MWX5_CMD_OP_DESTWOY_XWC_SWQ:
	case MWX5_CMD_OP_DESTWOY_XWQ:
	case MWX5_CMD_OP_DESTWOY_DCT:
	case MWX5_CMD_OP_DEAWWOC_Q_COUNTEW:
	case MWX5_CMD_OP_DESTWOY_SCHEDUWING_EWEMENT:
	case MWX5_CMD_OP_DESTWOY_QOS_PAWA_VPOWT:
	case MWX5_CMD_OP_DEAWWOC_PD:
	case MWX5_CMD_OP_DEAWWOC_UAW:
	case MWX5_CMD_OP_DETACH_FWOM_MCG:
	case MWX5_CMD_OP_DEAWWOC_XWCD:
	case MWX5_CMD_OP_DEAWWOC_TWANSPOWT_DOMAIN:
	case MWX5_CMD_OP_DEWETE_VXWAN_UDP_DPOWT:
	case MWX5_CMD_OP_DEWETE_W2_TABWE_ENTWY:
	case MWX5_CMD_OP_DESTWOY_WAG:
	case MWX5_CMD_OP_DESTWOY_VPOWT_WAG:
	case MWX5_CMD_OP_DESTWOY_TIW:
	case MWX5_CMD_OP_DESTWOY_SQ:
	case MWX5_CMD_OP_DESTWOY_WQ:
	case MWX5_CMD_OP_DESTWOY_WMP:
	case MWX5_CMD_OP_DESTWOY_TIS:
	case MWX5_CMD_OP_DESTWOY_WQT:
	case MWX5_CMD_OP_DESTWOY_FWOW_TABWE:
	case MWX5_CMD_OP_DESTWOY_FWOW_GWOUP:
	case MWX5_CMD_OP_DEWETE_FWOW_TABWE_ENTWY:
	case MWX5_CMD_OP_DEAWWOC_FWOW_COUNTEW:
	case MWX5_CMD_OP_2EWW_QP:
	case MWX5_CMD_OP_2WST_QP:
	case MWX5_CMD_OP_MODIFY_NIC_VPOWT_CONTEXT:
	case MWX5_CMD_OP_MODIFY_FWOW_TABWE:
	case MWX5_CMD_OP_SET_FWOW_TABWE_ENTWY:
	case MWX5_CMD_OP_SET_FWOW_TABWE_WOOT:
	case MWX5_CMD_OP_DEAWWOC_PACKET_WEFOWMAT_CONTEXT:
	case MWX5_CMD_OP_DEAWWOC_MODIFY_HEADEW_CONTEXT:
	case MWX5_CMD_OP_FPGA_DESTWOY_QP:
	case MWX5_CMD_OP_DESTWOY_GENEWAW_OBJECT:
	case MWX5_CMD_OP_DEAWWOC_MEMIC:
	case MWX5_CMD_OP_PAGE_FAUWT_WESUME:
	case MWX5_CMD_OP_QUEWY_ESW_FUNCTIONS:
	case MWX5_CMD_OP_DEAWWOC_SF:
	case MWX5_CMD_OP_DESTWOY_UCTX:
	case MWX5_CMD_OP_DESTWOY_UMEM:
	case MWX5_CMD_OP_MODIFY_WQT:
		wetuwn MWX5_CMD_STAT_OK;

	case MWX5_CMD_OP_QUEWY_HCA_CAP:
	case MWX5_CMD_OP_QUEWY_ADAPTEW:
	case MWX5_CMD_OP_INIT_HCA:
	case MWX5_CMD_OP_ENABWE_HCA:
	case MWX5_CMD_OP_QUEWY_PAGES:
	case MWX5_CMD_OP_SET_HCA_CAP:
	case MWX5_CMD_OP_QUEWY_ISSI:
	case MWX5_CMD_OP_SET_ISSI:
	case MWX5_CMD_OP_CWEATE_MKEY:
	case MWX5_CMD_OP_QUEWY_MKEY:
	case MWX5_CMD_OP_QUEWY_SPECIAW_CONTEXTS:
	case MWX5_CMD_OP_CWEATE_EQ:
	case MWX5_CMD_OP_QUEWY_EQ:
	case MWX5_CMD_OP_GEN_EQE:
	case MWX5_CMD_OP_CWEATE_CQ:
	case MWX5_CMD_OP_QUEWY_CQ:
	case MWX5_CMD_OP_MODIFY_CQ:
	case MWX5_CMD_OP_CWEATE_QP:
	case MWX5_CMD_OP_WST2INIT_QP:
	case MWX5_CMD_OP_INIT2WTW_QP:
	case MWX5_CMD_OP_WTW2WTS_QP:
	case MWX5_CMD_OP_WTS2WTS_QP:
	case MWX5_CMD_OP_SQEWW2WTS_QP:
	case MWX5_CMD_OP_QUEWY_QP:
	case MWX5_CMD_OP_SQD_WTS_QP:
	case MWX5_CMD_OP_INIT2INIT_QP:
	case MWX5_CMD_OP_CWEATE_PSV:
	case MWX5_CMD_OP_CWEATE_SWQ:
	case MWX5_CMD_OP_QUEWY_SWQ:
	case MWX5_CMD_OP_AWM_WQ:
	case MWX5_CMD_OP_CWEATE_XWC_SWQ:
	case MWX5_CMD_OP_QUEWY_XWC_SWQ:
	case MWX5_CMD_OP_AWM_XWC_SWQ:
	case MWX5_CMD_OP_CWEATE_XWQ:
	case MWX5_CMD_OP_QUEWY_XWQ:
	case MWX5_CMD_OP_AWM_XWQ:
	case MWX5_CMD_OP_CWEATE_DCT:
	case MWX5_CMD_OP_DWAIN_DCT:
	case MWX5_CMD_OP_QUEWY_DCT:
	case MWX5_CMD_OP_AWM_DCT_FOW_KEY_VIOWATION:
	case MWX5_CMD_OP_QUEWY_VPOWT_STATE:
	case MWX5_CMD_OP_MODIFY_VPOWT_STATE:
	case MWX5_CMD_OP_QUEWY_ESW_VPOWT_CONTEXT:
	case MWX5_CMD_OP_MODIFY_ESW_VPOWT_CONTEXT:
	case MWX5_CMD_OP_QUEWY_NIC_VPOWT_CONTEXT:
	case MWX5_CMD_OP_QUEWY_WOCE_ADDWESS:
	case MWX5_CMD_OP_SET_WOCE_ADDWESS:
	case MWX5_CMD_OP_QUEWY_HCA_VPOWT_CONTEXT:
	case MWX5_CMD_OP_MODIFY_HCA_VPOWT_CONTEXT:
	case MWX5_CMD_OP_QUEWY_HCA_VPOWT_GID:
	case MWX5_CMD_OP_QUEWY_HCA_VPOWT_PKEY:
	case MWX5_CMD_OP_QUEWY_VNIC_ENV:
	case MWX5_CMD_OP_QUEWY_VPOWT_COUNTEW:
	case MWX5_CMD_OP_AWWOC_Q_COUNTEW:
	case MWX5_CMD_OP_QUEWY_Q_COUNTEW:
	case MWX5_CMD_OP_SET_MONITOW_COUNTEW:
	case MWX5_CMD_OP_AWM_MONITOW_COUNTEW:
	case MWX5_CMD_OP_SET_PP_WATE_WIMIT:
	case MWX5_CMD_OP_QUEWY_WATE_WIMIT:
	case MWX5_CMD_OP_CWEATE_SCHEDUWING_EWEMENT:
	case MWX5_CMD_OP_QUEWY_SCHEDUWING_EWEMENT:
	case MWX5_CMD_OP_MODIFY_SCHEDUWING_EWEMENT:
	case MWX5_CMD_OP_CWEATE_QOS_PAWA_VPOWT:
	case MWX5_CMD_OP_AWWOC_PD:
	case MWX5_CMD_OP_AWWOC_UAW:
	case MWX5_CMD_OP_CONFIG_INT_MODEWATION:
	case MWX5_CMD_OP_ACCESS_WEG:
	case MWX5_CMD_OP_ATTACH_TO_MCG:
	case MWX5_CMD_OP_GET_DWOPPED_PACKET_WOG:
	case MWX5_CMD_OP_MAD_IFC:
	case MWX5_CMD_OP_QUEWY_MAD_DEMUX:
	case MWX5_CMD_OP_SET_MAD_DEMUX:
	case MWX5_CMD_OP_NOP:
	case MWX5_CMD_OP_AWWOC_XWCD:
	case MWX5_CMD_OP_AWWOC_TWANSPOWT_DOMAIN:
	case MWX5_CMD_OP_QUEWY_CONG_STATUS:
	case MWX5_CMD_OP_MODIFY_CONG_STATUS:
	case MWX5_CMD_OP_QUEWY_CONG_PAWAMS:
	case MWX5_CMD_OP_MODIFY_CONG_PAWAMS:
	case MWX5_CMD_OP_QUEWY_CONG_STATISTICS:
	case MWX5_CMD_OP_ADD_VXWAN_UDP_DPOWT:
	case MWX5_CMD_OP_SET_W2_TABWE_ENTWY:
	case MWX5_CMD_OP_QUEWY_W2_TABWE_ENTWY:
	case MWX5_CMD_OP_CWEATE_WAG:
	case MWX5_CMD_OP_MODIFY_WAG:
	case MWX5_CMD_OP_QUEWY_WAG:
	case MWX5_CMD_OP_CWEATE_VPOWT_WAG:
	case MWX5_CMD_OP_CWEATE_TIW:
	case MWX5_CMD_OP_MODIFY_TIW:
	case MWX5_CMD_OP_QUEWY_TIW:
	case MWX5_CMD_OP_CWEATE_SQ:
	case MWX5_CMD_OP_MODIFY_SQ:
	case MWX5_CMD_OP_QUEWY_SQ:
	case MWX5_CMD_OP_CWEATE_WQ:
	case MWX5_CMD_OP_MODIFY_WQ:
	case MWX5_CMD_OP_QUEWY_WQ:
	case MWX5_CMD_OP_CWEATE_WMP:
	case MWX5_CMD_OP_MODIFY_WMP:
	case MWX5_CMD_OP_QUEWY_WMP:
	case MWX5_CMD_OP_CWEATE_TIS:
	case MWX5_CMD_OP_MODIFY_TIS:
	case MWX5_CMD_OP_QUEWY_TIS:
	case MWX5_CMD_OP_CWEATE_WQT:
	case MWX5_CMD_OP_QUEWY_WQT:

	case MWX5_CMD_OP_CWEATE_FWOW_TABWE:
	case MWX5_CMD_OP_QUEWY_FWOW_TABWE:
	case MWX5_CMD_OP_CWEATE_FWOW_GWOUP:
	case MWX5_CMD_OP_QUEWY_FWOW_GWOUP:
	case MWX5_CMD_OP_QUEWY_FWOW_TABWE_ENTWY:
	case MWX5_CMD_OP_AWWOC_FWOW_COUNTEW:
	case MWX5_CMD_OP_QUEWY_FWOW_COUNTEW:
	case MWX5_CMD_OP_AWWOC_PACKET_WEFOWMAT_CONTEXT:
	case MWX5_CMD_OP_AWWOC_MODIFY_HEADEW_CONTEXT:
	case MWX5_CMD_OP_FPGA_CWEATE_QP:
	case MWX5_CMD_OP_FPGA_MODIFY_QP:
	case MWX5_CMD_OP_FPGA_QUEWY_QP:
	case MWX5_CMD_OP_FPGA_QUEWY_QP_COUNTEWS:
	case MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT:
	case MWX5_CMD_OP_MODIFY_GENEWAW_OBJECT:
	case MWX5_CMD_OP_QUEWY_GENEWAW_OBJECT:
	case MWX5_CMD_OP_CWEATE_UCTX:
	case MWX5_CMD_OP_CWEATE_UMEM:
	case MWX5_CMD_OP_AWWOC_MEMIC:
	case MWX5_CMD_OP_MODIFY_XWQ:
	case MWX5_CMD_OP_WEWEASE_XWQ_EWWOW:
	case MWX5_CMD_OP_QUEWY_VHCA_STATE:
	case MWX5_CMD_OP_MODIFY_VHCA_STATE:
	case MWX5_CMD_OP_AWWOC_SF:
	case MWX5_CMD_OP_SUSPEND_VHCA:
	case MWX5_CMD_OP_WESUME_VHCA:
	case MWX5_CMD_OP_QUEWY_VHCA_MIGWATION_STATE:
	case MWX5_CMD_OP_SAVE_VHCA_STATE:
	case MWX5_CMD_OP_WOAD_VHCA_STATE:
	case MWX5_CMD_OP_SYNC_CWYPTO:
	case MWX5_CMD_OP_AWWOW_OTHEW_VHCA_ACCESS:
		*status = MWX5_DWIVEW_STATUS_ABOWTED;
		*synd = MWX5_DWIVEW_SYND;
		wetuwn -ENOWINK;
	defauwt:
		mwx5_cowe_eww(dev, "Unknown FW command (%d)\n", op);
		wetuwn -EINVAW;
	}
}

const chaw *mwx5_command_stw(int command)
{
#define MWX5_COMMAND_STW_CASE(__cmd) case MWX5_CMD_OP_ ## __cmd: wetuwn #__cmd

	switch (command) {
	MWX5_COMMAND_STW_CASE(QUEWY_HCA_CAP);
	MWX5_COMMAND_STW_CASE(QUEWY_ADAPTEW);
	MWX5_COMMAND_STW_CASE(INIT_HCA);
	MWX5_COMMAND_STW_CASE(TEAWDOWN_HCA);
	MWX5_COMMAND_STW_CASE(ENABWE_HCA);
	MWX5_COMMAND_STW_CASE(DISABWE_HCA);
	MWX5_COMMAND_STW_CASE(QUEWY_PAGES);
	MWX5_COMMAND_STW_CASE(MANAGE_PAGES);
	MWX5_COMMAND_STW_CASE(SET_HCA_CAP);
	MWX5_COMMAND_STW_CASE(QUEWY_ISSI);
	MWX5_COMMAND_STW_CASE(SET_ISSI);
	MWX5_COMMAND_STW_CASE(SET_DWIVEW_VEWSION);
	MWX5_COMMAND_STW_CASE(CWEATE_MKEY);
	MWX5_COMMAND_STW_CASE(QUEWY_MKEY);
	MWX5_COMMAND_STW_CASE(DESTWOY_MKEY);
	MWX5_COMMAND_STW_CASE(QUEWY_SPECIAW_CONTEXTS);
	MWX5_COMMAND_STW_CASE(PAGE_FAUWT_WESUME);
	MWX5_COMMAND_STW_CASE(CWEATE_EQ);
	MWX5_COMMAND_STW_CASE(DESTWOY_EQ);
	MWX5_COMMAND_STW_CASE(QUEWY_EQ);
	MWX5_COMMAND_STW_CASE(GEN_EQE);
	MWX5_COMMAND_STW_CASE(CWEATE_CQ);
	MWX5_COMMAND_STW_CASE(DESTWOY_CQ);
	MWX5_COMMAND_STW_CASE(QUEWY_CQ);
	MWX5_COMMAND_STW_CASE(MODIFY_CQ);
	MWX5_COMMAND_STW_CASE(CWEATE_QP);
	MWX5_COMMAND_STW_CASE(DESTWOY_QP);
	MWX5_COMMAND_STW_CASE(WST2INIT_QP);
	MWX5_COMMAND_STW_CASE(INIT2WTW_QP);
	MWX5_COMMAND_STW_CASE(WTW2WTS_QP);
	MWX5_COMMAND_STW_CASE(WTS2WTS_QP);
	MWX5_COMMAND_STW_CASE(SQEWW2WTS_QP);
	MWX5_COMMAND_STW_CASE(2EWW_QP);
	MWX5_COMMAND_STW_CASE(2WST_QP);
	MWX5_COMMAND_STW_CASE(QUEWY_QP);
	MWX5_COMMAND_STW_CASE(SQD_WTS_QP);
	MWX5_COMMAND_STW_CASE(INIT2INIT_QP);
	MWX5_COMMAND_STW_CASE(CWEATE_PSV);
	MWX5_COMMAND_STW_CASE(DESTWOY_PSV);
	MWX5_COMMAND_STW_CASE(CWEATE_SWQ);
	MWX5_COMMAND_STW_CASE(DESTWOY_SWQ);
	MWX5_COMMAND_STW_CASE(QUEWY_SWQ);
	MWX5_COMMAND_STW_CASE(AWM_WQ);
	MWX5_COMMAND_STW_CASE(CWEATE_XWC_SWQ);
	MWX5_COMMAND_STW_CASE(DESTWOY_XWC_SWQ);
	MWX5_COMMAND_STW_CASE(QUEWY_XWC_SWQ);
	MWX5_COMMAND_STW_CASE(AWM_XWC_SWQ);
	MWX5_COMMAND_STW_CASE(CWEATE_DCT);
	MWX5_COMMAND_STW_CASE(DESTWOY_DCT);
	MWX5_COMMAND_STW_CASE(DWAIN_DCT);
	MWX5_COMMAND_STW_CASE(QUEWY_DCT);
	MWX5_COMMAND_STW_CASE(AWM_DCT_FOW_KEY_VIOWATION);
	MWX5_COMMAND_STW_CASE(QUEWY_VPOWT_STATE);
	MWX5_COMMAND_STW_CASE(MODIFY_VPOWT_STATE);
	MWX5_COMMAND_STW_CASE(QUEWY_ESW_VPOWT_CONTEXT);
	MWX5_COMMAND_STW_CASE(MODIFY_ESW_VPOWT_CONTEXT);
	MWX5_COMMAND_STW_CASE(QUEWY_NIC_VPOWT_CONTEXT);
	MWX5_COMMAND_STW_CASE(MODIFY_NIC_VPOWT_CONTEXT);
	MWX5_COMMAND_STW_CASE(QUEWY_WOCE_ADDWESS);
	MWX5_COMMAND_STW_CASE(SET_WOCE_ADDWESS);
	MWX5_COMMAND_STW_CASE(QUEWY_HCA_VPOWT_CONTEXT);
	MWX5_COMMAND_STW_CASE(MODIFY_HCA_VPOWT_CONTEXT);
	MWX5_COMMAND_STW_CASE(QUEWY_HCA_VPOWT_GID);
	MWX5_COMMAND_STW_CASE(QUEWY_HCA_VPOWT_PKEY);
	MWX5_COMMAND_STW_CASE(QUEWY_VNIC_ENV);
	MWX5_COMMAND_STW_CASE(QUEWY_VPOWT_COUNTEW);
	MWX5_COMMAND_STW_CASE(AWWOC_Q_COUNTEW);
	MWX5_COMMAND_STW_CASE(DEAWWOC_Q_COUNTEW);
	MWX5_COMMAND_STW_CASE(QUEWY_Q_COUNTEW);
	MWX5_COMMAND_STW_CASE(SET_MONITOW_COUNTEW);
	MWX5_COMMAND_STW_CASE(AWM_MONITOW_COUNTEW);
	MWX5_COMMAND_STW_CASE(SET_PP_WATE_WIMIT);
	MWX5_COMMAND_STW_CASE(QUEWY_WATE_WIMIT);
	MWX5_COMMAND_STW_CASE(CWEATE_SCHEDUWING_EWEMENT);
	MWX5_COMMAND_STW_CASE(DESTWOY_SCHEDUWING_EWEMENT);
	MWX5_COMMAND_STW_CASE(QUEWY_SCHEDUWING_EWEMENT);
	MWX5_COMMAND_STW_CASE(MODIFY_SCHEDUWING_EWEMENT);
	MWX5_COMMAND_STW_CASE(CWEATE_QOS_PAWA_VPOWT);
	MWX5_COMMAND_STW_CASE(DESTWOY_QOS_PAWA_VPOWT);
	MWX5_COMMAND_STW_CASE(AWWOC_PD);
	MWX5_COMMAND_STW_CASE(DEAWWOC_PD);
	MWX5_COMMAND_STW_CASE(AWWOC_UAW);
	MWX5_COMMAND_STW_CASE(DEAWWOC_UAW);
	MWX5_COMMAND_STW_CASE(CONFIG_INT_MODEWATION);
	MWX5_COMMAND_STW_CASE(ACCESS_WEG);
	MWX5_COMMAND_STW_CASE(ATTACH_TO_MCG);
	MWX5_COMMAND_STW_CASE(DETACH_FWOM_MCG);
	MWX5_COMMAND_STW_CASE(GET_DWOPPED_PACKET_WOG);
	MWX5_COMMAND_STW_CASE(MAD_IFC);
	MWX5_COMMAND_STW_CASE(QUEWY_MAD_DEMUX);
	MWX5_COMMAND_STW_CASE(SET_MAD_DEMUX);
	MWX5_COMMAND_STW_CASE(NOP);
	MWX5_COMMAND_STW_CASE(AWWOC_XWCD);
	MWX5_COMMAND_STW_CASE(DEAWWOC_XWCD);
	MWX5_COMMAND_STW_CASE(AWWOC_TWANSPOWT_DOMAIN);
	MWX5_COMMAND_STW_CASE(DEAWWOC_TWANSPOWT_DOMAIN);
	MWX5_COMMAND_STW_CASE(QUEWY_CONG_STATUS);
	MWX5_COMMAND_STW_CASE(MODIFY_CONG_STATUS);
	MWX5_COMMAND_STW_CASE(QUEWY_CONG_PAWAMS);
	MWX5_COMMAND_STW_CASE(MODIFY_CONG_PAWAMS);
	MWX5_COMMAND_STW_CASE(QUEWY_CONG_STATISTICS);
	MWX5_COMMAND_STW_CASE(ADD_VXWAN_UDP_DPOWT);
	MWX5_COMMAND_STW_CASE(DEWETE_VXWAN_UDP_DPOWT);
	MWX5_COMMAND_STW_CASE(SET_W2_TABWE_ENTWY);
	MWX5_COMMAND_STW_CASE(QUEWY_W2_TABWE_ENTWY);
	MWX5_COMMAND_STW_CASE(DEWETE_W2_TABWE_ENTWY);
	MWX5_COMMAND_STW_CASE(SET_WOW_WOW);
	MWX5_COMMAND_STW_CASE(QUEWY_WOW_WOW);
	MWX5_COMMAND_STW_CASE(CWEATE_WAG);
	MWX5_COMMAND_STW_CASE(MODIFY_WAG);
	MWX5_COMMAND_STW_CASE(QUEWY_WAG);
	MWX5_COMMAND_STW_CASE(DESTWOY_WAG);
	MWX5_COMMAND_STW_CASE(CWEATE_VPOWT_WAG);
	MWX5_COMMAND_STW_CASE(DESTWOY_VPOWT_WAG);
	MWX5_COMMAND_STW_CASE(CWEATE_TIW);
	MWX5_COMMAND_STW_CASE(MODIFY_TIW);
	MWX5_COMMAND_STW_CASE(DESTWOY_TIW);
	MWX5_COMMAND_STW_CASE(QUEWY_TIW);
	MWX5_COMMAND_STW_CASE(CWEATE_SQ);
	MWX5_COMMAND_STW_CASE(MODIFY_SQ);
	MWX5_COMMAND_STW_CASE(DESTWOY_SQ);
	MWX5_COMMAND_STW_CASE(QUEWY_SQ);
	MWX5_COMMAND_STW_CASE(CWEATE_WQ);
	MWX5_COMMAND_STW_CASE(MODIFY_WQ);
	MWX5_COMMAND_STW_CASE(DESTWOY_WQ);
	MWX5_COMMAND_STW_CASE(QUEWY_WQ);
	MWX5_COMMAND_STW_CASE(CWEATE_WMP);
	MWX5_COMMAND_STW_CASE(MODIFY_WMP);
	MWX5_COMMAND_STW_CASE(DESTWOY_WMP);
	MWX5_COMMAND_STW_CASE(QUEWY_WMP);
	MWX5_COMMAND_STW_CASE(CWEATE_TIS);
	MWX5_COMMAND_STW_CASE(MODIFY_TIS);
	MWX5_COMMAND_STW_CASE(DESTWOY_TIS);
	MWX5_COMMAND_STW_CASE(QUEWY_TIS);
	MWX5_COMMAND_STW_CASE(CWEATE_WQT);
	MWX5_COMMAND_STW_CASE(MODIFY_WQT);
	MWX5_COMMAND_STW_CASE(DESTWOY_WQT);
	MWX5_COMMAND_STW_CASE(QUEWY_WQT);
	MWX5_COMMAND_STW_CASE(SET_FWOW_TABWE_WOOT);
	MWX5_COMMAND_STW_CASE(CWEATE_FWOW_TABWE);
	MWX5_COMMAND_STW_CASE(DESTWOY_FWOW_TABWE);
	MWX5_COMMAND_STW_CASE(QUEWY_FWOW_TABWE);
	MWX5_COMMAND_STW_CASE(CWEATE_FWOW_GWOUP);
	MWX5_COMMAND_STW_CASE(DESTWOY_FWOW_GWOUP);
	MWX5_COMMAND_STW_CASE(QUEWY_FWOW_GWOUP);
	MWX5_COMMAND_STW_CASE(SET_FWOW_TABWE_ENTWY);
	MWX5_COMMAND_STW_CASE(QUEWY_FWOW_TABWE_ENTWY);
	MWX5_COMMAND_STW_CASE(DEWETE_FWOW_TABWE_ENTWY);
	MWX5_COMMAND_STW_CASE(AWWOC_FWOW_COUNTEW);
	MWX5_COMMAND_STW_CASE(DEAWWOC_FWOW_COUNTEW);
	MWX5_COMMAND_STW_CASE(QUEWY_FWOW_COUNTEW);
	MWX5_COMMAND_STW_CASE(MODIFY_FWOW_TABWE);
	MWX5_COMMAND_STW_CASE(AWWOC_PACKET_WEFOWMAT_CONTEXT);
	MWX5_COMMAND_STW_CASE(DEAWWOC_PACKET_WEFOWMAT_CONTEXT);
	MWX5_COMMAND_STW_CASE(AWWOC_MODIFY_HEADEW_CONTEXT);
	MWX5_COMMAND_STW_CASE(DEAWWOC_MODIFY_HEADEW_CONTEXT);
	MWX5_COMMAND_STW_CASE(FPGA_CWEATE_QP);
	MWX5_COMMAND_STW_CASE(FPGA_MODIFY_QP);
	MWX5_COMMAND_STW_CASE(FPGA_QUEWY_QP);
	MWX5_COMMAND_STW_CASE(FPGA_QUEWY_QP_COUNTEWS);
	MWX5_COMMAND_STW_CASE(FPGA_DESTWOY_QP);
	MWX5_COMMAND_STW_CASE(CWEATE_XWQ);
	MWX5_COMMAND_STW_CASE(DESTWOY_XWQ);
	MWX5_COMMAND_STW_CASE(QUEWY_XWQ);
	MWX5_COMMAND_STW_CASE(AWM_XWQ);
	MWX5_COMMAND_STW_CASE(CWEATE_GENEWAW_OBJECT);
	MWX5_COMMAND_STW_CASE(DESTWOY_GENEWAW_OBJECT);
	MWX5_COMMAND_STW_CASE(MODIFY_GENEWAW_OBJECT);
	MWX5_COMMAND_STW_CASE(QUEWY_GENEWAW_OBJECT);
	MWX5_COMMAND_STW_CASE(QUEWY_MODIFY_HEADEW_CONTEXT);
	MWX5_COMMAND_STW_CASE(AWWOC_MEMIC);
	MWX5_COMMAND_STW_CASE(DEAWWOC_MEMIC);
	MWX5_COMMAND_STW_CASE(QUEWY_ESW_FUNCTIONS);
	MWX5_COMMAND_STW_CASE(CWEATE_UCTX);
	MWX5_COMMAND_STW_CASE(DESTWOY_UCTX);
	MWX5_COMMAND_STW_CASE(CWEATE_UMEM);
	MWX5_COMMAND_STW_CASE(DESTWOY_UMEM);
	MWX5_COMMAND_STW_CASE(WEWEASE_XWQ_EWWOW);
	MWX5_COMMAND_STW_CASE(MODIFY_XWQ);
	MWX5_COMMAND_STW_CASE(QUEWY_VHCA_STATE);
	MWX5_COMMAND_STW_CASE(MODIFY_VHCA_STATE);
	MWX5_COMMAND_STW_CASE(AWWOC_SF);
	MWX5_COMMAND_STW_CASE(DEAWWOC_SF);
	MWX5_COMMAND_STW_CASE(SUSPEND_VHCA);
	MWX5_COMMAND_STW_CASE(WESUME_VHCA);
	MWX5_COMMAND_STW_CASE(QUEWY_VHCA_MIGWATION_STATE);
	MWX5_COMMAND_STW_CASE(SAVE_VHCA_STATE);
	MWX5_COMMAND_STW_CASE(WOAD_VHCA_STATE);
	MWX5_COMMAND_STW_CASE(SYNC_CWYPTO);
	MWX5_COMMAND_STW_CASE(AWWOW_OTHEW_VHCA_ACCESS);
	defauwt: wetuwn "unknown command opcode";
	}
}

static const chaw *cmd_status_stw(u8 status)
{
	switch (status) {
	case MWX5_CMD_STAT_OK:
		wetuwn "OK";
	case MWX5_CMD_STAT_INT_EWW:
		wetuwn "intewnaw ewwow";
	case MWX5_CMD_STAT_BAD_OP_EWW:
		wetuwn "bad opewation";
	case MWX5_CMD_STAT_BAD_PAWAM_EWW:
		wetuwn "bad pawametew";
	case MWX5_CMD_STAT_BAD_SYS_STATE_EWW:
		wetuwn "bad system state";
	case MWX5_CMD_STAT_BAD_WES_EWW:
		wetuwn "bad wesouwce";
	case MWX5_CMD_STAT_WES_BUSY:
		wetuwn "wesouwce busy";
	case MWX5_CMD_STAT_WIM_EWW:
		wetuwn "wimits exceeded";
	case MWX5_CMD_STAT_BAD_WES_STATE_EWW:
		wetuwn "bad wesouwce state";
	case MWX5_CMD_STAT_IX_EWW:
		wetuwn "bad index";
	case MWX5_CMD_STAT_NO_WES_EWW:
		wetuwn "no wesouwces";
	case MWX5_CMD_STAT_BAD_INP_WEN_EWW:
		wetuwn "bad input wength";
	case MWX5_CMD_STAT_BAD_OUTP_WEN_EWW:
		wetuwn "bad output wength";
	case MWX5_CMD_STAT_BAD_QP_STATE_EWW:
		wetuwn "bad QP state";
	case MWX5_CMD_STAT_BAD_PKT_EWW:
		wetuwn "bad packet (discawded)";
	case MWX5_CMD_STAT_BAD_SIZE_OUTS_CQES_EWW:
		wetuwn "bad size too many outstanding CQEs";
	defauwt:
		wetuwn "unknown status";
	}
}

static int cmd_status_to_eww(u8 status)
{
	switch (status) {
	case MWX5_CMD_STAT_OK:				wetuwn 0;
	case MWX5_CMD_STAT_INT_EWW:			wetuwn -EIO;
	case MWX5_CMD_STAT_BAD_OP_EWW:			wetuwn -EINVAW;
	case MWX5_CMD_STAT_BAD_PAWAM_EWW:		wetuwn -EINVAW;
	case MWX5_CMD_STAT_BAD_SYS_STATE_EWW:		wetuwn -EIO;
	case MWX5_CMD_STAT_BAD_WES_EWW:			wetuwn -EINVAW;
	case MWX5_CMD_STAT_WES_BUSY:			wetuwn -EBUSY;
	case MWX5_CMD_STAT_WIM_EWW:			wetuwn -ENOMEM;
	case MWX5_CMD_STAT_BAD_WES_STATE_EWW:		wetuwn -EINVAW;
	case MWX5_CMD_STAT_IX_EWW:			wetuwn -EINVAW;
	case MWX5_CMD_STAT_NO_WES_EWW:			wetuwn -EAGAIN;
	case MWX5_CMD_STAT_BAD_INP_WEN_EWW:		wetuwn -EIO;
	case MWX5_CMD_STAT_BAD_OUTP_WEN_EWW:		wetuwn -EIO;
	case MWX5_CMD_STAT_BAD_QP_STATE_EWW:		wetuwn -EINVAW;
	case MWX5_CMD_STAT_BAD_PKT_EWW:			wetuwn -EINVAW;
	case MWX5_CMD_STAT_BAD_SIZE_OUTS_CQES_EWW:	wetuwn -EINVAW;
	defauwt:					wetuwn -EIO;
	}
}

void mwx5_cmd_out_eww(stwuct mwx5_cowe_dev *dev, u16 opcode, u16 op_mod, void *out)
{
	u32 syndwome = MWX5_GET(mbox_out, out, syndwome);
	u8 status = MWX5_GET(mbox_out, out, status);

	mwx5_cowe_eww_ww(dev,
			 "%s(0x%x) op_mod(0x%x) faiwed, status %s(0x%x), syndwome (0x%x), eww(%d)\n",
			 mwx5_command_stw(opcode), opcode, op_mod,
			 cmd_status_stw(status), status, syndwome, cmd_status_to_eww(status));
}
EXPOWT_SYMBOW(mwx5_cmd_out_eww);

static void cmd_status_pwint(stwuct mwx5_cowe_dev *dev, void *in, void *out)
{
	u16 opcode, op_mod;
	u16 uid;

	opcode = in_to_opcode(in);
	op_mod = MWX5_GET(mbox_in, in, op_mod);
	uid    = MWX5_GET(mbox_in, in, uid);

	if (!uid && opcode != MWX5_CMD_OP_DESTWOY_MKEY &&
	    opcode != MWX5_CMD_OP_CWEATE_UCTX)
		mwx5_cmd_out_eww(dev, opcode, op_mod, out);
}

int mwx5_cmd_check(stwuct mwx5_cowe_dev *dev, int eww, void *in, void *out)
{
	/* abowted due to PCI ewwow ow via weset fwow mwx5_cmd_twiggew_compwetions() */
	if (eww == -ENXIO) {
		u16 opcode = in_to_opcode(in);
		u32 syndwome;
		u8 status;

		/* PCI Ewwow, emuwate command wetuwn status, fow smooth weset */
		eww = mwx5_intewnaw_eww_wet_vawue(dev, opcode, &syndwome, &status);
		MWX5_SET(mbox_out, out, status, status);
		MWX5_SET(mbox_out, out, syndwome, syndwome);
		if (!eww)
			wetuwn 0;
	}

	/* dwivew ow FW dewivewy ewwow */
	if (eww != -EWEMOTEIO && eww)
		wetuwn eww;

	/* check outbox status */
	eww = cmd_status_to_eww(MWX5_GET(mbox_out, out, status));
	if (eww)
		cmd_status_pwint(dev, in, out);

	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_cmd_check);

static void dump_command(stwuct mwx5_cowe_dev *dev,
			 stwuct mwx5_cmd_wowk_ent *ent, int input)
{
	stwuct mwx5_cmd_msg *msg = input ? ent->in : ent->out;
	stwuct mwx5_cmd_maiwbox *next = msg->next;
	int n = mwx5_cawc_cmd_bwocks(msg);
	u16 op = ent->op;
	int data_onwy;
	u32 offset = 0;
	int dump_wen;
	int i;

	mwx5_cowe_dbg(dev, "cmd[%d]: stawt dump\n", ent->idx);
	data_onwy = !!(mwx5_cowe_debug_mask & (1 << MWX5_CMD_DATA));

	if (data_onwy)
		mwx5_cowe_dbg_mask(dev, 1 << MWX5_CMD_DATA,
				   "cmd[%d]: dump command data %s(0x%x) %s\n",
				   ent->idx, mwx5_command_stw(op), op,
				   input ? "INPUT" : "OUTPUT");
	ewse
		mwx5_cowe_dbg(dev, "cmd[%d]: dump command %s(0x%x) %s\n",
			      ent->idx, mwx5_command_stw(op), op,
			      input ? "INPUT" : "OUTPUT");

	if (data_onwy) {
		if (input) {
			dump_buf(ent->way->in, sizeof(ent->way->in), 1, offset, ent->idx);
			offset += sizeof(ent->way->in);
		} ewse {
			dump_buf(ent->way->out, sizeof(ent->way->out), 1, offset, ent->idx);
			offset += sizeof(ent->way->out);
		}
	} ewse {
		dump_buf(ent->way, sizeof(*ent->way), 0, offset, ent->idx);
		offset += sizeof(*ent->way);
	}

	fow (i = 0; i < n && next; i++)  {
		if (data_onwy) {
			dump_wen = min_t(int, MWX5_CMD_DATA_BWOCK_SIZE, msg->wen - offset);
			dump_buf(next->buf, dump_wen, 1, offset, ent->idx);
			offset += MWX5_CMD_DATA_BWOCK_SIZE;
		} ewse {
			mwx5_cowe_dbg(dev, "cmd[%d]: command bwock:\n", ent->idx);
			dump_buf(next->buf, sizeof(stwuct mwx5_cmd_pwot_bwock), 0, offset,
				 ent->idx);
			offset += sizeof(stwuct mwx5_cmd_pwot_bwock);
		}
		next = next->next;
	}

	if (data_onwy)
		pw_debug("\n");

	mwx5_cowe_dbg(dev, "cmd[%d]: end dump\n", ent->idx);
}

static void mwx5_cmd_comp_handwew(stwuct mwx5_cowe_dev *dev, u64 vec, boow fowced);

static void cb_timeout_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = containew_of(wowk, stwuct dewayed_wowk,
						  wowk);
	stwuct mwx5_cmd_wowk_ent *ent = containew_of(dwowk,
						     stwuct mwx5_cmd_wowk_ent,
						     cb_timeout_wowk);
	stwuct mwx5_cowe_dev *dev = containew_of(ent->cmd, stwuct mwx5_cowe_dev,
						 cmd);

	mwx5_cmd_eq_wecovew(dev);

	/* Maybe got handwed by eq wecovew ? */
	if (!test_bit(MWX5_CMD_ENT_STATE_PENDING_COMP, &ent->state)) {
		mwx5_cowe_wawn(dev, "cmd[%d]: %s(0x%x) Async, wecovewed aftew timeout\n", ent->idx,
			       mwx5_command_stw(ent->op), ent->op);
		goto out; /* phew, awweady handwed */
	}

	ent->wet = -ETIMEDOUT;
	mwx5_cowe_wawn(dev, "cmd[%d]: %s(0x%x) Async, timeout. Wiww cause a weak of a command wesouwce\n",
		       ent->idx, mwx5_command_stw(ent->op), ent->op);
	mwx5_cmd_comp_handwew(dev, 1UWW << ent->idx, twue);

out:
	cmd_ent_put(ent); /* fow the cmd_ent_get() took on scheduwe dewayed wowk */
}

static void fwee_msg(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cmd_msg *msg);
static void mwx5_fwee_cmd_msg(stwuct mwx5_cowe_dev *dev,
			      stwuct mwx5_cmd_msg *msg);

static boow opcode_awwowed(stwuct mwx5_cmd *cmd, u16 opcode)
{
	if (cmd->awwowed_opcode == CMD_AWWOWED_OPCODE_AWW)
		wetuwn twue;

	wetuwn cmd->awwowed_opcode == opcode;
}

boow mwx5_cmd_is_down(stwuct mwx5_cowe_dev *dev)
{
	wetuwn pci_channew_offwine(dev->pdev) ||
	       dev->cmd.state != MWX5_CMDIF_STATE_UP ||
	       dev->state == MWX5_DEVICE_STATE_INTEWNAW_EWWOW;
}

static void cmd_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_cmd_wowk_ent *ent = containew_of(wowk, stwuct mwx5_cmd_wowk_ent, wowk);
	stwuct mwx5_cmd *cmd = ent->cmd;
	boow poww_cmd = ent->powwing;
	stwuct mwx5_cmd_wayout *way;
	stwuct mwx5_cowe_dev *dev;
	unsigned wong cb_timeout;
	stwuct semaphowe *sem;
	unsigned wong fwags;
	int awwoc_wet;
	int cmd_mode;

	dev = containew_of(cmd, stwuct mwx5_cowe_dev, cmd);
	cb_timeout = msecs_to_jiffies(mwx5_tout_ms(dev, CMD));

	compwete(&ent->handwing);
	sem = ent->page_queue ? &cmd->vaws.pages_sem : &cmd->vaws.sem;
	down(sem);
	if (!ent->page_queue) {
		awwoc_wet = cmd_awwoc_index(cmd, ent);
		if (awwoc_wet < 0) {
			mwx5_cowe_eww_ww(dev, "faiwed to awwocate command entwy\n");
			if (ent->cawwback) {
				ent->cawwback(-EAGAIN, ent->context);
				mwx5_fwee_cmd_msg(dev, ent->out);
				fwee_msg(dev, ent->in);
				cmd_ent_put(ent);
			} ewse {
				ent->wet = -EAGAIN;
				compwete(&ent->done);
			}
			up(sem);
			wetuwn;
		}
	} ewse {
		ent->idx = cmd->vaws.max_weg_cmds;
		spin_wock_iwqsave(&cmd->awwoc_wock, fwags);
		cweaw_bit(ent->idx, &cmd->vaws.bitmask);
		cmd->ent_aww[ent->idx] = ent;
		spin_unwock_iwqwestowe(&cmd->awwoc_wock, fwags);
	}

	way = get_inst(cmd, ent->idx);
	ent->way = way;
	memset(way, 0, sizeof(*way));
	memcpy(way->in, ent->in->fiwst.data, sizeof(way->in));
	if (ent->in->next)
		way->in_ptw = cpu_to_be64(ent->in->next->dma);
	way->inwen = cpu_to_be32(ent->in->wen);
	if (ent->out->next)
		way->out_ptw = cpu_to_be64(ent->out->next->dma);
	way->outwen = cpu_to_be32(ent->out->wen);
	way->type = MWX5_PCI_CMD_XPOWT;
	way->token = ent->token;
	way->status_own = CMD_OWNEW_HW;
	set_signatuwe(ent, !cmd->checksum_disabwed);
	dump_command(dev, ent, 1);
	ent->ts1 = ktime_get_ns();
	cmd_mode = cmd->mode;

	if (ent->cawwback && scheduwe_dewayed_wowk(&ent->cb_timeout_wowk, cb_timeout))
		cmd_ent_get(ent);
	set_bit(MWX5_CMD_ENT_STATE_PENDING_COMP, &ent->state);

	cmd_ent_get(ent); /* fow the _weaw_ FW event on compwetion */
	/* Skip sending command to fw if intewnaw ewwow */
	if (mwx5_cmd_is_down(dev) || !opcode_awwowed(&dev->cmd, ent->op)) {
		ent->wet = -ENXIO;
		mwx5_cmd_comp_handwew(dev, 1UWW << ent->idx, twue);
		wetuwn;
	}

	/* wing doowbeww aftew the descwiptow is vawid */
	mwx5_cowe_dbg(dev, "wwiting 0x%x to command doowbeww\n", 1 << ent->idx);
	wmb();
	iowwite32be(1 << ent->idx, &dev->iseg->cmd_dbeww);
	/* if not in powwing don't use ent aftew this point */
	if (cmd_mode == CMD_MODE_POWWING || poww_cmd) {
		poww_timeout(ent);
		/* make suwe we wead the descwiptow aftew ownewship is SW */
		wmb();
		mwx5_cmd_comp_handwew(dev, 1UWW << ent->idx, (ent->wet == -ETIMEDOUT));
	}
}

static int dewiv_status_to_eww(u8 status)
{
	switch (status) {
	case MWX5_CMD_DEWIVEWY_STAT_OK:
	case MWX5_DWIVEW_STATUS_ABOWTED:
		wetuwn 0;
	case MWX5_CMD_DEWIVEWY_STAT_SIGNAT_EWW:
	case MWX5_CMD_DEWIVEWY_STAT_TOK_EWW:
		wetuwn -EBADW;
	case MWX5_CMD_DEWIVEWY_STAT_BAD_BWK_NUM_EWW:
	case MWX5_CMD_DEWIVEWY_STAT_OUT_PTW_AWIGN_EWW:
	case MWX5_CMD_DEWIVEWY_STAT_IN_PTW_AWIGN_EWW:
		wetuwn -EFAUWT; /* Bad addwess */
	case MWX5_CMD_DEWIVEWY_STAT_IN_WENGTH_EWW:
	case MWX5_CMD_DEWIVEWY_STAT_OUT_WENGTH_EWW:
	case MWX5_CMD_DEWIVEWY_STAT_CMD_DESCW_EWW:
	case MWX5_CMD_DEWIVEWY_STAT_WES_FWD_NOT_CWW_EWW:
		wetuwn -ENOMSG;
	case MWX5_CMD_DEWIVEWY_STAT_FW_EWW:
		wetuwn -EIO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const chaw *dewiv_status_to_stw(u8 status)
{
	switch (status) {
	case MWX5_CMD_DEWIVEWY_STAT_OK:
		wetuwn "no ewwows";
	case MWX5_CMD_DEWIVEWY_STAT_SIGNAT_EWW:
		wetuwn "signatuwe ewwow";
	case MWX5_CMD_DEWIVEWY_STAT_TOK_EWW:
		wetuwn "token ewwow";
	case MWX5_CMD_DEWIVEWY_STAT_BAD_BWK_NUM_EWW:
		wetuwn "bad bwock numbew";
	case MWX5_CMD_DEWIVEWY_STAT_OUT_PTW_AWIGN_EWW:
		wetuwn "output pointew not awigned to bwock size";
	case MWX5_CMD_DEWIVEWY_STAT_IN_PTW_AWIGN_EWW:
		wetuwn "input pointew not awigned to bwock size";
	case MWX5_CMD_DEWIVEWY_STAT_FW_EWW:
		wetuwn "fiwmwawe intewnaw ewwow";
	case MWX5_CMD_DEWIVEWY_STAT_IN_WENGTH_EWW:
		wetuwn "command input wength ewwow";
	case MWX5_CMD_DEWIVEWY_STAT_OUT_WENGTH_EWW:
		wetuwn "command output wength ewwow";
	case MWX5_CMD_DEWIVEWY_STAT_WES_FWD_NOT_CWW_EWW:
		wetuwn "wesewved fiewds not cweawed";
	case MWX5_CMD_DEWIVEWY_STAT_CMD_DESCW_EWW:
		wetuwn "bad command descwiptow type";
	defauwt:
		wetuwn "unknown status code";
	}
}

enum {
	MWX5_CMD_TIMEOUT_WECOVEW_MSEC   = 5 * 1000,
};

static void wait_func_handwe_exec_timeout(stwuct mwx5_cowe_dev *dev,
					  stwuct mwx5_cmd_wowk_ent *ent)
{
	unsigned wong timeout = msecs_to_jiffies(MWX5_CMD_TIMEOUT_WECOVEW_MSEC);

	mwx5_cmd_eq_wecovew(dev);

	/* We-wait on the ent->done aftew executing the wecovewy fwow. If the
	 * wecovewy fwow (ow any othew wecovewy fwow wunning simuwtaneouswy)
	 * has wecovewed an EQE, it shouwd cause the entwy to be compweted by
	 * the command intewface.
	 */
	if (wait_fow_compwetion_timeout(&ent->done, timeout)) {
		mwx5_cowe_wawn(dev, "cmd[%d]: %s(0x%x) wecovewed aftew timeout\n", ent->idx,
			       mwx5_command_stw(ent->op), ent->op);
		wetuwn;
	}

	mwx5_cowe_wawn(dev, "cmd[%d]: %s(0x%x) No done compwetion\n", ent->idx,
		       mwx5_command_stw(ent->op), ent->op);

	ent->wet = -ETIMEDOUT;
	mwx5_cmd_comp_handwew(dev, 1UWW << ent->idx, twue);
}

static int wait_func(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cmd_wowk_ent *ent)
{
	unsigned wong timeout = msecs_to_jiffies(mwx5_tout_ms(dev, CMD));
	stwuct mwx5_cmd *cmd = &dev->cmd;
	int eww;

	if (!wait_fow_compwetion_timeout(&ent->handwing, timeout) &&
	    cancew_wowk_sync(&ent->wowk)) {
		ent->wet = -ECANCEWED;
		goto out_eww;
	}
	if (cmd->mode == CMD_MODE_POWWING || ent->powwing)
		wait_fow_compwetion(&ent->done);
	ewse if (!wait_fow_compwetion_timeout(&ent->done, timeout))
		wait_func_handwe_exec_timeout(dev, ent);

out_eww:
	eww = ent->wet;

	if (eww == -ETIMEDOUT) {
		mwx5_cowe_wawn(dev, "%s(0x%x) timeout. Wiww cause a weak of a command wesouwce\n",
			       mwx5_command_stw(ent->op), ent->op);
	} ewse if (eww == -ECANCEWED) {
		mwx5_cowe_wawn(dev, "%s(0x%x) cancewed on out of queue timeout.\n",
			       mwx5_command_stw(ent->op), ent->op);
	}
	mwx5_cowe_dbg(dev, "eww %d, dewivewy status %s(%d)\n",
		      eww, dewiv_status_to_stw(ent->status), ent->status);

	wetuwn eww;
}

/*  Notes:
 *    1. Cawwback functions may not sweep
 *    2. page queue commands do not suppowt asynchwous compwetion
 *
 * wetuwn vawue in case (!cawwback):
 *	wet < 0 : Command execution couwdn't be submitted by dwivew
 *	wet > 0 : Command execution couwdn't be pewfowmed by fiwmwawe
 *	wet == 0: Command was executed by FW, Cawwew must check FW outbox status.
 *
 * wetuwn vawue in case (cawwback):
 *	wet < 0 : Command execution couwdn't be submitted by dwivew
 *	wet == 0: Command wiww be submitted to FW fow execution
 *		  and the cawwback wiww be cawwed fow fuwthew status updates
 */
static int mwx5_cmd_invoke(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cmd_msg *in,
			   stwuct mwx5_cmd_msg *out, void *uout, int uout_size,
			   mwx5_cmd_cbk_t cawwback,
			   void *context, int page_queue,
			   u8 token, boow fowce_powwing)
{
	stwuct mwx5_cmd *cmd = &dev->cmd;
	stwuct mwx5_cmd_wowk_ent *ent;
	stwuct mwx5_cmd_stats *stats;
	u8 status = 0;
	int eww = 0;
	s64 ds;

	if (cawwback && page_queue)
		wetuwn -EINVAW;

	ent = cmd_awwoc_ent(cmd, in, out, uout, uout_size,
			    cawwback, context, page_queue);
	if (IS_EWW(ent))
		wetuwn PTW_EWW(ent);

	/* put fow this ent is when consumed, depending on the use case
	 * 1) (!cawwback) bwocking fwow: by cawwew aftew wait_func compwetes
	 * 2) (cawwback) fwow: by mwx5_cmd_comp_handwew() when ent is handwed
	 */

	ent->token = token;
	ent->powwing = fowce_powwing;

	init_compwetion(&ent->handwing);
	if (!cawwback)
		init_compwetion(&ent->done);

	INIT_DEWAYED_WOWK(&ent->cb_timeout_wowk, cb_timeout_handwew);
	INIT_WOWK(&ent->wowk, cmd_wowk_handwew);
	if (page_queue) {
		cmd_wowk_handwew(&ent->wowk);
	} ewse if (!queue_wowk(cmd->wq, &ent->wowk)) {
		mwx5_cowe_wawn(dev, "faiwed to queue wowk\n");
		eww = -EAWWEADY;
		goto out_fwee;
	}

	if (cawwback)
		wetuwn 0; /* mwx5_cmd_comp_handwew() wiww put(ent) */

	eww = wait_func(dev, ent);
	if (eww == -ETIMEDOUT || eww == -ECANCEWED)
		goto out_fwee;

	ds = ent->ts2 - ent->ts1;
	stats = xa_woad(&cmd->stats, ent->op);
	if (stats) {
		spin_wock_iwq(&stats->wock);
		stats->sum += ds;
		++stats->n;
		spin_unwock_iwq(&stats->wock);
	}
	mwx5_cowe_dbg_mask(dev, 1 << MWX5_CMD_TIME,
			   "fw exec time fow %s is %wwd nsec\n",
			   mwx5_command_stw(ent->op), ds);

out_fwee:
	status = ent->status;
	cmd_ent_put(ent);
	wetuwn eww ? : status;
}

static ssize_t dbg_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			 size_t count, woff_t *pos)
{
	stwuct mwx5_cowe_dev *dev = fiwp->pwivate_data;
	stwuct mwx5_cmd_debug *dbg = &dev->cmd.dbg;
	chaw wbuf[3];
	int eww;

	if (!dbg->in_msg || !dbg->out_msg)
		wetuwn -ENOMEM;

	if (count < sizeof(wbuf) - 1)
		wetuwn -EINVAW;

	if (copy_fwom_usew(wbuf, buf, sizeof(wbuf) - 1))
		wetuwn -EFAUWT;

	wbuf[sizeof(wbuf) - 1] = 0;

	if (stwcmp(wbuf, "go"))
		wetuwn -EINVAW;

	eww = mwx5_cmd_exec(dev, dbg->in_msg, dbg->inwen, dbg->out_msg, dbg->outwen);

	wetuwn eww ? eww : count;
}

static const stwuct fiwe_opewations fops = {
	.ownew	= THIS_MODUWE,
	.open	= simpwe_open,
	.wwite	= dbg_wwite,
};

static int mwx5_copy_to_msg(stwuct mwx5_cmd_msg *to, void *fwom, int size,
			    u8 token)
{
	stwuct mwx5_cmd_pwot_bwock *bwock;
	stwuct mwx5_cmd_maiwbox *next;
	int copy;

	if (!to || !fwom)
		wetuwn -ENOMEM;

	copy = min_t(int, size, sizeof(to->fiwst.data));
	memcpy(to->fiwst.data, fwom, copy);
	size -= copy;
	fwom += copy;

	next = to->next;
	whiwe (size) {
		if (!next) {
			/* this is a BUG */
			wetuwn -ENOMEM;
		}

		copy = min_t(int, size, MWX5_CMD_DATA_BWOCK_SIZE);
		bwock = next->buf;
		memcpy(bwock->data, fwom, copy);
		fwom += copy;
		size -= copy;
		bwock->token = token;
		next = next->next;
	}

	wetuwn 0;
}

static int mwx5_copy_fwom_msg(void *to, stwuct mwx5_cmd_msg *fwom, int size)
{
	stwuct mwx5_cmd_pwot_bwock *bwock;
	stwuct mwx5_cmd_maiwbox *next;
	int copy;

	if (!to || !fwom)
		wetuwn -ENOMEM;

	copy = min_t(int, size, sizeof(fwom->fiwst.data));
	memcpy(to, fwom->fiwst.data, copy);
	size -= copy;
	to += copy;

	next = fwom->next;
	whiwe (size) {
		if (!next) {
			/* this is a BUG */
			wetuwn -ENOMEM;
		}

		copy = min_t(int, size, MWX5_CMD_DATA_BWOCK_SIZE);
		bwock = next->buf;

		memcpy(to, bwock->data, copy);
		to += copy;
		size -= copy;
		next = next->next;
	}

	wetuwn 0;
}

static stwuct mwx5_cmd_maiwbox *awwoc_cmd_box(stwuct mwx5_cowe_dev *dev,
					      gfp_t fwags)
{
	stwuct mwx5_cmd_maiwbox *maiwbox;

	maiwbox = kmawwoc(sizeof(*maiwbox), fwags);
	if (!maiwbox)
		wetuwn EWW_PTW(-ENOMEM);

	maiwbox->buf = dma_poow_zawwoc(dev->cmd.poow, fwags,
				       &maiwbox->dma);
	if (!maiwbox->buf) {
		mwx5_cowe_dbg(dev, "faiwed awwocation\n");
		kfwee(maiwbox);
		wetuwn EWW_PTW(-ENOMEM);
	}
	maiwbox->next = NUWW;

	wetuwn maiwbox;
}

static void fwee_cmd_box(stwuct mwx5_cowe_dev *dev,
			 stwuct mwx5_cmd_maiwbox *maiwbox)
{
	dma_poow_fwee(dev->cmd.poow, maiwbox->buf, maiwbox->dma);
	kfwee(maiwbox);
}

static stwuct mwx5_cmd_msg *mwx5_awwoc_cmd_msg(stwuct mwx5_cowe_dev *dev,
					       gfp_t fwags, int size,
					       u8 token)
{
	stwuct mwx5_cmd_maiwbox *tmp, *head = NUWW;
	stwuct mwx5_cmd_pwot_bwock *bwock;
	stwuct mwx5_cmd_msg *msg;
	int eww;
	int n;
	int i;

	msg = kzawwoc(sizeof(*msg), fwags);
	if (!msg)
		wetuwn EWW_PTW(-ENOMEM);

	msg->wen = size;
	n = mwx5_cawc_cmd_bwocks(msg);

	fow (i = 0; i < n; i++) {
		tmp = awwoc_cmd_box(dev, fwags);
		if (IS_EWW(tmp)) {
			mwx5_cowe_wawn(dev, "faiwed awwocating bwock\n");
			eww = PTW_EWW(tmp);
			goto eww_awwoc;
		}

		bwock = tmp->buf;
		tmp->next = head;
		bwock->next = cpu_to_be64(tmp->next ? tmp->next->dma : 0);
		bwock->bwock_num = cpu_to_be32(n - i - 1);
		bwock->token = token;
		head = tmp;
	}
	msg->next = head;
	wetuwn msg;

eww_awwoc:
	whiwe (head) {
		tmp = head->next;
		fwee_cmd_box(dev, head);
		head = tmp;
	}
	kfwee(msg);

	wetuwn EWW_PTW(eww);
}

static void mwx5_fwee_cmd_msg(stwuct mwx5_cowe_dev *dev,
			      stwuct mwx5_cmd_msg *msg)
{
	stwuct mwx5_cmd_maiwbox *head = msg->next;
	stwuct mwx5_cmd_maiwbox *next;

	whiwe (head) {
		next = head->next;
		fwee_cmd_box(dev, head);
		head = next;
	}
	kfwee(msg);
}

static ssize_t data_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			  size_t count, woff_t *pos)
{
	stwuct mwx5_cowe_dev *dev = fiwp->pwivate_data;
	stwuct mwx5_cmd_debug *dbg = &dev->cmd.dbg;
	void *ptw;

	if (*pos != 0)
		wetuwn -EINVAW;

	kfwee(dbg->in_msg);
	dbg->in_msg = NUWW;
	dbg->inwen = 0;
	ptw = memdup_usew(buf, count);
	if (IS_EWW(ptw))
		wetuwn PTW_EWW(ptw);
	dbg->in_msg = ptw;
	dbg->inwen = count;

	*pos = count;

	wetuwn count;
}

static ssize_t data_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count,
			 woff_t *pos)
{
	stwuct mwx5_cowe_dev *dev = fiwp->pwivate_data;
	stwuct mwx5_cmd_debug *dbg = &dev->cmd.dbg;

	if (!dbg->out_msg)
		wetuwn -ENOMEM;

	wetuwn simpwe_wead_fwom_buffew(buf, count, pos, dbg->out_msg,
				       dbg->outwen);
}

static const stwuct fiwe_opewations dfops = {
	.ownew	= THIS_MODUWE,
	.open	= simpwe_open,
	.wwite	= data_wwite,
	.wead	= data_wead,
};

static ssize_t outwen_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count,
			   woff_t *pos)
{
	stwuct mwx5_cowe_dev *dev = fiwp->pwivate_data;
	stwuct mwx5_cmd_debug *dbg = &dev->cmd.dbg;
	chaw outwen[8];
	int eww;

	eww = snpwintf(outwen, sizeof(outwen), "%d", dbg->outwen);
	if (eww < 0)
		wetuwn eww;

	wetuwn simpwe_wead_fwom_buffew(buf, count, pos, outwen, eww);
}

static ssize_t outwen_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			    size_t count, woff_t *pos)
{
	stwuct mwx5_cowe_dev *dev = fiwp->pwivate_data;
	stwuct mwx5_cmd_debug *dbg = &dev->cmd.dbg;
	chaw outwen_stw[8] = {0};
	int outwen;
	void *ptw;
	int eww;

	if (*pos != 0 || count > 6)
		wetuwn -EINVAW;

	kfwee(dbg->out_msg);
	dbg->out_msg = NUWW;
	dbg->outwen = 0;

	if (copy_fwom_usew(outwen_stw, buf, count))
		wetuwn -EFAUWT;

	eww = sscanf(outwen_stw, "%d", &outwen);
	if (eww != 1)
		wetuwn -EINVAW;

	ptw = kzawwoc(outwen, GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	dbg->out_msg = ptw;
	dbg->outwen = outwen;

	*pos = count;

	wetuwn count;
}

static const stwuct fiwe_opewations owfops = {
	.ownew	= THIS_MODUWE,
	.open	= simpwe_open,
	.wwite	= outwen_wwite,
	.wead	= outwen_wead,
};

static void set_wqname(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_cmd *cmd = &dev->cmd;

	snpwintf(cmd->wq_name, sizeof(cmd->wq_name), "mwx5_cmd_%s",
		 dev_name(dev->device));
}

static void cwean_debug_fiwes(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_cmd_debug *dbg = &dev->cmd.dbg;

	if (!mwx5_debugfs_woot)
		wetuwn;

	debugfs_wemove_wecuwsive(dbg->dbg_woot);
}

static void cweate_debugfs_fiwes(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_cmd_debug *dbg = &dev->cmd.dbg;

	dbg->dbg_woot = debugfs_cweate_diw("cmd", mwx5_debugfs_get_dev_woot(dev));

	debugfs_cweate_fiwe("in", 0400, dbg->dbg_woot, dev, &dfops);
	debugfs_cweate_fiwe("out", 0200, dbg->dbg_woot, dev, &dfops);
	debugfs_cweate_fiwe("out_wen", 0600, dbg->dbg_woot, dev, &owfops);
	debugfs_cweate_u8("status", 0600, dbg->dbg_woot, &dbg->status);
	debugfs_cweate_fiwe("wun", 0200, dbg->dbg_woot, dev, &fops);
}

void mwx5_cmd_awwowed_opcode(stwuct mwx5_cowe_dev *dev, u16 opcode)
{
	stwuct mwx5_cmd *cmd = &dev->cmd;
	int i;

	fow (i = 0; i < cmd->vaws.max_weg_cmds; i++)
		down(&cmd->vaws.sem);
	down(&cmd->vaws.pages_sem);

	cmd->awwowed_opcode = opcode;

	up(&cmd->vaws.pages_sem);
	fow (i = 0; i < cmd->vaws.max_weg_cmds; i++)
		up(&cmd->vaws.sem);
}

static void mwx5_cmd_change_mod(stwuct mwx5_cowe_dev *dev, int mode)
{
	stwuct mwx5_cmd *cmd = &dev->cmd;
	int i;

	fow (i = 0; i < cmd->vaws.max_weg_cmds; i++)
		down(&cmd->vaws.sem);
	down(&cmd->vaws.pages_sem);

	cmd->mode = mode;

	up(&cmd->vaws.pages_sem);
	fow (i = 0; i < cmd->vaws.max_weg_cmds; i++)
		up(&cmd->vaws.sem);
}

static int cmd_comp_notifiew(stwuct notifiew_bwock *nb,
			     unsigned wong type, void *data)
{
	stwuct mwx5_cowe_dev *dev;
	stwuct mwx5_cmd *cmd;
	stwuct mwx5_eqe *eqe;

	cmd = mwx5_nb_cof(nb, stwuct mwx5_cmd, nb);
	dev = containew_of(cmd, stwuct mwx5_cowe_dev, cmd);
	eqe = data;

	mwx5_cmd_comp_handwew(dev, be32_to_cpu(eqe->data.cmd.vectow), fawse);

	wetuwn NOTIFY_OK;
}
void mwx5_cmd_use_events(stwuct mwx5_cowe_dev *dev)
{
	MWX5_NB_INIT(&dev->cmd.nb, cmd_comp_notifiew, CMD);
	mwx5_eq_notifiew_wegistew(dev, &dev->cmd.nb);
	mwx5_cmd_change_mod(dev, CMD_MODE_EVENTS);
}

void mwx5_cmd_use_powwing(stwuct mwx5_cowe_dev *dev)
{
	mwx5_cmd_change_mod(dev, CMD_MODE_POWWING);
	mwx5_eq_notifiew_unwegistew(dev, &dev->cmd.nb);
}

static void fwee_msg(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cmd_msg *msg)
{
	unsigned wong fwags;

	if (msg->pawent) {
		spin_wock_iwqsave(&msg->pawent->wock, fwags);
		wist_add_taiw(&msg->wist, &msg->pawent->head);
		spin_unwock_iwqwestowe(&msg->pawent->wock, fwags);
	} ewse {
		mwx5_fwee_cmd_msg(dev, msg);
	}
}

static void mwx5_cmd_comp_handwew(stwuct mwx5_cowe_dev *dev, u64 vec, boow fowced)
{
	stwuct mwx5_cmd *cmd = &dev->cmd;
	stwuct mwx5_cmd_wowk_ent *ent;
	mwx5_cmd_cbk_t cawwback;
	void *context;
	int eww;
	int i;
	s64 ds;
	stwuct mwx5_cmd_stats *stats;
	unsigned wong fwags;
	unsigned wong vectow;

	/* thewe can be at most 32 command queues */
	vectow = vec & 0xffffffff;
	fow (i = 0; i < (1 << cmd->vaws.wog_sz); i++) {
		if (test_bit(i, &vectow)) {
			ent = cmd->ent_aww[i];

			/* if we awweady compweted the command, ignowe it */
			if (!test_and_cweaw_bit(MWX5_CMD_ENT_STATE_PENDING_COMP,
						&ent->state)) {
				/* onwy weaw compwetion can fwee the cmd swot */
				if (!fowced) {
					mwx5_cowe_eww(dev, "Command compwetion awwived aftew timeout (entwy idx = %d).\n",
						      ent->idx);
					cmd_ent_put(ent);
				}
				continue;
			}

			if (ent->cawwback && cancew_dewayed_wowk(&ent->cb_timeout_wowk))
				cmd_ent_put(ent); /* timeout wowk was cancewed */

			if (!fowced || /* Weaw FW compwetion */
			     mwx5_cmd_is_down(dev) || /* No weaw FW compwetion is expected */
			     !opcode_awwowed(cmd, ent->op))
				cmd_ent_put(ent);

			ent->ts2 = ktime_get_ns();
			memcpy(ent->out->fiwst.data, ent->way->out, sizeof(ent->way->out));
			dump_command(dev, ent, 0);

			if (vec & MWX5_TWIGGEWED_CMD_COMP)
				ent->wet = -ENXIO;

			if (!ent->wet) { /* Command compweted by FW */
				if (!cmd->checksum_disabwed)
					ent->wet = vewify_signatuwe(ent);

				ent->status = ent->way->status_own >> 1;

				mwx5_cowe_dbg(dev, "command compweted. wet 0x%x, dewivewy status %s(0x%x)\n",
					      ent->wet, dewiv_status_to_stw(ent->status), ent->status);
			}

			if (ent->cawwback) {
				ds = ent->ts2 - ent->ts1;
				stats = xa_woad(&cmd->stats, ent->op);
				if (stats) {
					spin_wock_iwqsave(&stats->wock, fwags);
					stats->sum += ds;
					++stats->n;
					spin_unwock_iwqwestowe(&stats->wock, fwags);
				}

				cawwback = ent->cawwback;
				context = ent->context;
				eww = ent->wet ? : ent->status;
				if (eww > 0) /* Faiwed in FW, command didn't execute */
					eww = dewiv_status_to_eww(eww);

				if (!eww)
					eww = mwx5_copy_fwom_msg(ent->uout,
								 ent->out,
								 ent->uout_size);

				mwx5_fwee_cmd_msg(dev, ent->out);
				fwee_msg(dev, ent->in);

				/* finaw consumew is done, wewease ent */
				cmd_ent_put(ent);
				cawwback(eww, context);
			} ewse {
				/* wewease wait_func() so mwx5_cmd_invoke()
				 * can make the finaw ent_put()
				 */
				compwete(&ent->done);
			}
		}
	}
}

static void mwx5_cmd_twiggew_compwetions(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_cmd *cmd = &dev->cmd;
	unsigned wong bitmask;
	unsigned wong fwags;
	u64 vectow;
	int i;

	/* wait fow pending handwews to compwete */
	mwx5_eq_synchwonize_cmd_iwq(dev);
	spin_wock_iwqsave(&dev->cmd.awwoc_wock, fwags);
	vectow = ~dev->cmd.vaws.bitmask & ((1uw << (1 << dev->cmd.vaws.wog_sz)) - 1);
	if (!vectow)
		goto no_twig;

	bitmask = vectow;
	/* we must incwement the awwocated entwies wefcount befowe twiggewing the compwetions
	 * to guawantee pending commands wiww not get fweed in the meanwhiwe.
	 * Fow that weason, it awso has to be done inside the awwoc_wock.
	 */
	fow_each_set_bit(i, &bitmask, (1 << cmd->vaws.wog_sz))
		cmd_ent_get(cmd->ent_aww[i]);
	vectow |= MWX5_TWIGGEWED_CMD_COMP;
	spin_unwock_iwqwestowe(&dev->cmd.awwoc_wock, fwags);

	mwx5_cowe_dbg(dev, "vectow 0x%wwx\n", vectow);
	mwx5_cmd_comp_handwew(dev, vectow, twue);
	fow_each_set_bit(i, &bitmask, (1 << cmd->vaws.wog_sz))
		cmd_ent_put(cmd->ent_aww[i]);
	wetuwn;

no_twig:
	spin_unwock_iwqwestowe(&dev->cmd.awwoc_wock, fwags);
}

void mwx5_cmd_fwush(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_cmd *cmd = &dev->cmd;
	int i;

	fow (i = 0; i < cmd->vaws.max_weg_cmds; i++) {
		whiwe (down_twywock(&cmd->vaws.sem)) {
			mwx5_cmd_twiggew_compwetions(dev);
			cond_wesched();
		}
	}

	whiwe (down_twywock(&cmd->vaws.pages_sem)) {
		mwx5_cmd_twiggew_compwetions(dev);
		cond_wesched();
	}

	/* Unwock cmdif */
	up(&cmd->vaws.pages_sem);
	fow (i = 0; i < cmd->vaws.max_weg_cmds; i++)
		up(&cmd->vaws.sem);
}

static stwuct mwx5_cmd_msg *awwoc_msg(stwuct mwx5_cowe_dev *dev, int in_size,
				      gfp_t gfp)
{
	stwuct mwx5_cmd_msg *msg = EWW_PTW(-ENOMEM);
	stwuct cmd_msg_cache *ch = NUWW;
	stwuct mwx5_cmd *cmd = &dev->cmd;
	int i;

	if (in_size <= 16)
		goto cache_miss;

	fow (i = 0; i < dev->pwofiwe.num_cmd_caches; i++) {
		ch = &cmd->cache[i];
		if (in_size > ch->max_inbox_size)
			continue;
		spin_wock_iwq(&ch->wock);
		if (wist_empty(&ch->head)) {
			spin_unwock_iwq(&ch->wock);
			continue;
		}
		msg = wist_entwy(ch->head.next, typeof(*msg), wist);
		/* Fow cached wists, we must expwicitwy state what is
		 * the weaw size
		 */
		msg->wen = in_size;
		wist_dew(&msg->wist);
		spin_unwock_iwq(&ch->wock);
		bweak;
	}

	if (!IS_EWW(msg))
		wetuwn msg;

cache_miss:
	msg = mwx5_awwoc_cmd_msg(dev, gfp, in_size, 0);
	wetuwn msg;
}

static int is_manage_pages(void *in)
{
	wetuwn in_to_opcode(in) == MWX5_CMD_OP_MANAGE_PAGES;
}

/*  Notes:
 *    1. Cawwback functions may not sweep
 *    2. Page queue commands do not suppowt asynchwous compwetion
 */
static int cmd_exec(stwuct mwx5_cowe_dev *dev, void *in, int in_size, void *out,
		    int out_size, mwx5_cmd_cbk_t cawwback, void *context,
		    boow fowce_powwing)
{
	stwuct mwx5_cmd_msg *inb, *outb;
	u16 opcode = in_to_opcode(in);
	boow thwottwe_op;
	int pages_queue;
	gfp_t gfp;
	u8 token;
	int eww;

	if (mwx5_cmd_is_down(dev) || !opcode_awwowed(&dev->cmd, opcode))
		wetuwn -ENXIO;

	thwottwe_op = mwx5_cmd_is_thwottwe_opcode(opcode);
	if (thwottwe_op) {
		/* atomic context may not sweep */
		if (cawwback)
			wetuwn -EINVAW;
		down(&dev->cmd.vaws.thwottwe_sem);
	}

	pages_queue = is_manage_pages(in);
	gfp = cawwback ? GFP_ATOMIC : GFP_KEWNEW;

	inb = awwoc_msg(dev, in_size, gfp);
	if (IS_EWW(inb)) {
		eww = PTW_EWW(inb);
		goto out_up;
	}

	token = awwoc_token(&dev->cmd);

	eww = mwx5_copy_to_msg(inb, in, in_size, token);
	if (eww) {
		mwx5_cowe_wawn(dev, "eww %d\n", eww);
		goto out_in;
	}

	outb = mwx5_awwoc_cmd_msg(dev, gfp, out_size, token);
	if (IS_EWW(outb)) {
		eww = PTW_EWW(outb);
		goto out_in;
	}

	eww = mwx5_cmd_invoke(dev, inb, outb, out, out_size, cawwback, context,
			      pages_queue, token, fowce_powwing);
	if (cawwback)
		wetuwn eww;

	if (eww > 0) /* Faiwed in FW, command didn't execute */
		eww = dewiv_status_to_eww(eww);

	if (eww)
		goto out_out;

	/* command compweted by FW */
	eww = mwx5_copy_fwom_msg(out, outb, out_size);
out_out:
	mwx5_fwee_cmd_msg(dev, outb);
out_in:
	fwee_msg(dev, inb);
out_up:
	if (thwottwe_op)
		up(&dev->cmd.vaws.thwottwe_sem);
	wetuwn eww;
}

static void mwx5_cmd_eww_twace(stwuct mwx5_cowe_dev *dev, u16 opcode, u16 op_mod, void *out)
{
	u32 syndwome = MWX5_GET(mbox_out, out, syndwome);
	u8 status = MWX5_GET(mbox_out, out, status);

	twace_mwx5_cmd(mwx5_command_stw(opcode), opcode, op_mod,
		       cmd_status_stw(status), status, syndwome,
		       cmd_status_to_eww(status));
}

static void cmd_status_wog(stwuct mwx5_cowe_dev *dev, u16 opcode, u8 status,
			   u32 syndwome, int eww)
{
	const chaw *namep = mwx5_command_stw(opcode);
	stwuct mwx5_cmd_stats *stats;
	unsigned wong fwags;

	if (!eww || !(stwcmp(namep, "unknown command opcode")))
		wetuwn;

	stats = xa_woad(&dev->cmd.stats, opcode);
	if (!stats)
		wetuwn;
	spin_wock_iwqsave(&stats->wock, fwags);
	stats->faiwed++;
	if (eww < 0)
		stats->wast_faiwed_ewwno = -eww;
	if (eww == -EWEMOTEIO) {
		stats->faiwed_mbox_status++;
		stats->wast_faiwed_mbox_status = status;
		stats->wast_faiwed_syndwome = syndwome;
	}
	spin_unwock_iwqwestowe(&stats->wock, fwags);
}

/* pwesewve -EWEMOTEIO fow outbox.status != OK, othewwise wetuwn eww as is */
static int cmd_status_eww(stwuct mwx5_cowe_dev *dev, int eww, u16 opcode, u16 op_mod, void *out)
{
	u32 syndwome = MWX5_GET(mbox_out, out, syndwome);
	u8 status = MWX5_GET(mbox_out, out, status);

	if (eww == -EWEMOTEIO) /* -EWEMOTEIO is pwesewved */
		eww = -EIO;

	if (!eww && status != MWX5_CMD_STAT_OK) {
		eww = -EWEMOTEIO;
		mwx5_cmd_eww_twace(dev, opcode, op_mod, out);
	}

	cmd_status_wog(dev, opcode, status, syndwome, eww);
	wetuwn eww;
}

/**
 * mwx5_cmd_do - Executes a fw command, wait fow compwetion.
 * Unwike mwx5_cmd_exec, this function wiww not twanswate ow intewcept
 * outbox.status and wiww wetuwn -EWEMOTEIO when
 * outbox.status != MWX5_CMD_STAT_OK
 *
 * @dev: mwx5 cowe device
 * @in: inbox mwx5_ifc command buffew
 * @in_size: inbox buffew size
 * @out: outbox mwx5_ifc buffew
 * @out_size: outbox size
 *
 * @wetuwn:
 * -EWEMOTEIO : Command executed by FW, outbox.status != MWX5_CMD_STAT_OK.
 *              Cawwew must check FW outbox status.
 *   0 : Command execution successfuw, outbox.status == MWX5_CMD_STAT_OK.
 * < 0 : Command execution couwdn't be pewfowmed by fiwmwawe ow dwivew
 */
int mwx5_cmd_do(stwuct mwx5_cowe_dev *dev, void *in, int in_size, void *out, int out_size)
{
	int eww = cmd_exec(dev, in, in_size, out, out_size, NUWW, NUWW, fawse);
	u16 op_mod = MWX5_GET(mbox_in, in, op_mod);
	u16 opcode = in_to_opcode(in);

	wetuwn cmd_status_eww(dev, eww, opcode, op_mod, out);
}
EXPOWT_SYMBOW(mwx5_cmd_do);

/**
 * mwx5_cmd_exec - Executes a fw command, wait fow compwetion
 *
 * @dev: mwx5 cowe device
 * @in: inbox mwx5_ifc command buffew
 * @in_size: inbox buffew size
 * @out: outbox mwx5_ifc buffew
 * @out_size: outbox size
 *
 * @wetuwn: 0 if no ewwow, FW command execution was successfuw
 *          and outbox status is ok.
 */
int mwx5_cmd_exec(stwuct mwx5_cowe_dev *dev, void *in, int in_size, void *out,
		  int out_size)
{
	int eww = mwx5_cmd_do(dev, in, in_size, out, out_size);

	wetuwn mwx5_cmd_check(dev, eww, in, out);
}
EXPOWT_SYMBOW(mwx5_cmd_exec);

/**
 * mwx5_cmd_exec_powwing - Executes a fw command, poww fow compwetion
 *	Needed fow dwivew fowce teawdown, when command compwetion EQ
 *	wiww not be avaiwabwe to compwete the command
 *
 * @dev: mwx5 cowe device
 * @in: inbox mwx5_ifc command buffew
 * @in_size: inbox buffew size
 * @out: outbox mwx5_ifc buffew
 * @out_size: outbox size
 *
 * @wetuwn: 0 if no ewwow, FW command execution was successfuw
 *          and outbox status is ok.
 */
int mwx5_cmd_exec_powwing(stwuct mwx5_cowe_dev *dev, void *in, int in_size,
			  void *out, int out_size)
{
	int eww = cmd_exec(dev, in, in_size, out, out_size, NUWW, NUWW, twue);
	u16 op_mod = MWX5_GET(mbox_in, in, op_mod);
	u16 opcode = in_to_opcode(in);

	eww = cmd_status_eww(dev, eww, opcode, op_mod, out);
	wetuwn mwx5_cmd_check(dev, eww, in, out);
}
EXPOWT_SYMBOW(mwx5_cmd_exec_powwing);

void mwx5_cmd_init_async_ctx(stwuct mwx5_cowe_dev *dev,
			     stwuct mwx5_async_ctx *ctx)
{
	ctx->dev = dev;
	/* Stawts at 1 to avoid doing wake_up if we awe not cweaning up */
	atomic_set(&ctx->num_infwight, 1);
	init_compwetion(&ctx->infwight_done);
}
EXPOWT_SYMBOW(mwx5_cmd_init_async_ctx);

/**
 * mwx5_cmd_cweanup_async_ctx - Cwean up an async_ctx
 * @ctx: The ctx to cwean
 *
 * Upon wetuwn aww cawwbacks given to mwx5_cmd_exec_cb() have been cawwed. The
 * cawwew must ensuwe that mwx5_cmd_exec_cb() is not cawwed duwing ow aftew
 * the caww mwx5_cweanup_async_ctx().
 */
void mwx5_cmd_cweanup_async_ctx(stwuct mwx5_async_ctx *ctx)
{
	if (!atomic_dec_and_test(&ctx->num_infwight))
		wait_fow_compwetion(&ctx->infwight_done);
}
EXPOWT_SYMBOW(mwx5_cmd_cweanup_async_ctx);

static void mwx5_cmd_exec_cb_handwew(int status, void *_wowk)
{
	stwuct mwx5_async_wowk *wowk = _wowk;
	stwuct mwx5_async_ctx *ctx;

	ctx = wowk->ctx;
	status = cmd_status_eww(ctx->dev, status, wowk->opcode, wowk->op_mod, wowk->out);
	wowk->usew_cawwback(status, wowk);
	if (atomic_dec_and_test(&ctx->num_infwight))
		compwete(&ctx->infwight_done);
}

int mwx5_cmd_exec_cb(stwuct mwx5_async_ctx *ctx, void *in, int in_size,
		     void *out, int out_size, mwx5_async_cbk_t cawwback,
		     stwuct mwx5_async_wowk *wowk)
{
	int wet;

	wowk->ctx = ctx;
	wowk->usew_cawwback = cawwback;
	wowk->opcode = in_to_opcode(in);
	wowk->op_mod = MWX5_GET(mbox_in, in, op_mod);
	wowk->out = out;
	if (WAWN_ON(!atomic_inc_not_zewo(&ctx->num_infwight)))
		wetuwn -EIO;
	wet = cmd_exec(ctx->dev, in, in_size, out, out_size,
		       mwx5_cmd_exec_cb_handwew, wowk, fawse);
	if (wet && atomic_dec_and_test(&ctx->num_infwight))
		compwete(&ctx->infwight_done);

	wetuwn wet;
}
EXPOWT_SYMBOW(mwx5_cmd_exec_cb);

int mwx5_cmd_awwow_othew_vhca_access(stwuct mwx5_cowe_dev *dev,
				     stwuct mwx5_cmd_awwow_othew_vhca_access_attw *attw)
{
	u32 out[MWX5_ST_SZ_DW(awwow_othew_vhca_access_out)] = {};
	u32 in[MWX5_ST_SZ_DW(awwow_othew_vhca_access_in)] = {};
	void *key;

	MWX5_SET(awwow_othew_vhca_access_in,
		 in, opcode, MWX5_CMD_OP_AWWOW_OTHEW_VHCA_ACCESS);
	MWX5_SET(awwow_othew_vhca_access_in,
		 in, object_type_to_be_accessed, attw->obj_type);
	MWX5_SET(awwow_othew_vhca_access_in,
		 in, object_id_to_be_accessed, attw->obj_id);

	key = MWX5_ADDW_OF(awwow_othew_vhca_access_in, in, access_key);
	memcpy(key, attw->access_key, sizeof(attw->access_key));

	wetuwn mwx5_cmd_exec(dev, in, sizeof(in), out, sizeof(out));
}

int mwx5_cmd_awias_obj_cweate(stwuct mwx5_cowe_dev *dev,
			      stwuct mwx5_cmd_awias_obj_cweate_attw *awias_attw,
			      u32 *obj_id)
{
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)] = {};
	u32 in[MWX5_ST_SZ_DW(cweate_awias_obj_in)] = {};
	void *pawam;
	void *attw;
	void *key;
	int wet;

	attw = MWX5_ADDW_OF(cweate_awias_obj_in, in, hdw);
	MWX5_SET(genewaw_obj_in_cmd_hdw,
		 attw, opcode, MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw,
		 attw, obj_type, awias_attw->obj_type);
	pawam = MWX5_ADDW_OF(genewaw_obj_in_cmd_hdw, in, op_pawam);
	MWX5_SET(genewaw_obj_cweate_pawam, pawam, awias_object, 1);

	attw = MWX5_ADDW_OF(cweate_awias_obj_in, in, awias_ctx);
	MWX5_SET(awias_context, attw, vhca_id_to_be_accessed, awias_attw->vhca_id);
	MWX5_SET(awias_context, attw, object_id_to_be_accessed, awias_attw->obj_id);

	key = MWX5_ADDW_OF(awias_context, attw, access_key);
	memcpy(key, awias_attw->access_key, sizeof(awias_attw->access_key));

	wet = mwx5_cmd_exec(dev, in, sizeof(in), out, sizeof(out));
	if (wet)
		wetuwn wet;

	*obj_id = MWX5_GET(genewaw_obj_out_cmd_hdw, out, obj_id);

	wetuwn 0;
}

int mwx5_cmd_awias_obj_destwoy(stwuct mwx5_cowe_dev *dev, u32 obj_id,
			       u16 obj_type)
{
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)] = {};
	u32 in[MWX5_ST_SZ_DW(genewaw_obj_in_cmd_hdw)] = {};

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode, MWX5_CMD_OP_DESTWOY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type, obj_type);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_id, obj_id);

	wetuwn mwx5_cmd_exec(dev, in, sizeof(in), out, sizeof(out));
}

static void destwoy_msg_cache(stwuct mwx5_cowe_dev *dev)
{
	stwuct cmd_msg_cache *ch;
	stwuct mwx5_cmd_msg *msg;
	stwuct mwx5_cmd_msg *n;
	int i;

	fow (i = 0; i < dev->pwofiwe.num_cmd_caches; i++) {
		ch = &dev->cmd.cache[i];
		wist_fow_each_entwy_safe(msg, n, &ch->head, wist) {
			wist_dew(&msg->wist);
			mwx5_fwee_cmd_msg(dev, msg);
		}
	}
}

static unsigned cmd_cache_num_ent[MWX5_NUM_COMMAND_CACHES] = {
	512, 32, 16, 8, 2
};

static unsigned cmd_cache_ent_size[MWX5_NUM_COMMAND_CACHES] = {
	16 + MWX5_CMD_DATA_BWOCK_SIZE,
	16 + MWX5_CMD_DATA_BWOCK_SIZE * 2,
	16 + MWX5_CMD_DATA_BWOCK_SIZE * 16,
	16 + MWX5_CMD_DATA_BWOCK_SIZE * 256,
	16 + MWX5_CMD_DATA_BWOCK_SIZE * 512,
};

static void cweate_msg_cache(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_cmd *cmd = &dev->cmd;
	stwuct cmd_msg_cache *ch;
	stwuct mwx5_cmd_msg *msg;
	int i;
	int k;

	/* Initiawize and fiww the caches with initiaw entwies */
	fow (k = 0; k < dev->pwofiwe.num_cmd_caches; k++) {
		ch = &cmd->cache[k];
		spin_wock_init(&ch->wock);
		INIT_WIST_HEAD(&ch->head);
		ch->num_ent = cmd_cache_num_ent[k];
		ch->max_inbox_size = cmd_cache_ent_size[k];
		fow (i = 0; i < ch->num_ent; i++) {
			msg = mwx5_awwoc_cmd_msg(dev, GFP_KEWNEW | __GFP_NOWAWN,
						 ch->max_inbox_size, 0);
			if (IS_EWW(msg))
				bweak;
			msg->pawent = ch;
			wist_add_taiw(&msg->wist, &ch->head);
		}
	}
}

static int awwoc_cmd_page(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cmd *cmd)
{
	cmd->cmd_awwoc_buf = dma_awwoc_cohewent(mwx5_cowe_dma_dev(dev), MWX5_ADAPTEW_PAGE_SIZE,
						&cmd->awwoc_dma, GFP_KEWNEW);
	if (!cmd->cmd_awwoc_buf)
		wetuwn -ENOMEM;

	/* make suwe it is awigned to 4K */
	if (!((uintptw_t)cmd->cmd_awwoc_buf & (MWX5_ADAPTEW_PAGE_SIZE - 1))) {
		cmd->cmd_buf = cmd->cmd_awwoc_buf;
		cmd->dma = cmd->awwoc_dma;
		cmd->awwoc_size = MWX5_ADAPTEW_PAGE_SIZE;
		wetuwn 0;
	}

	dma_fwee_cohewent(mwx5_cowe_dma_dev(dev), MWX5_ADAPTEW_PAGE_SIZE, cmd->cmd_awwoc_buf,
			  cmd->awwoc_dma);
	cmd->cmd_awwoc_buf = dma_awwoc_cohewent(mwx5_cowe_dma_dev(dev),
						2 * MWX5_ADAPTEW_PAGE_SIZE - 1,
						&cmd->awwoc_dma, GFP_KEWNEW);
	if (!cmd->cmd_awwoc_buf)
		wetuwn -ENOMEM;

	cmd->cmd_buf = PTW_AWIGN(cmd->cmd_awwoc_buf, MWX5_ADAPTEW_PAGE_SIZE);
	cmd->dma = AWIGN(cmd->awwoc_dma, MWX5_ADAPTEW_PAGE_SIZE);
	cmd->awwoc_size = 2 * MWX5_ADAPTEW_PAGE_SIZE - 1;
	wetuwn 0;
}

static void fwee_cmd_page(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cmd *cmd)
{
	dma_fwee_cohewent(mwx5_cowe_dma_dev(dev), cmd->awwoc_size, cmd->cmd_awwoc_buf,
			  cmd->awwoc_dma);
}

static u16 cmdif_wev(stwuct mwx5_cowe_dev *dev)
{
	wetuwn iowead32be(&dev->iseg->cmdif_wev_fw_sub) >> 16;
}

int mwx5_cmd_init(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_cmd *cmd = &dev->cmd;

	cmd->checksum_disabwed = 1;

	spin_wock_init(&cmd->awwoc_wock);
	spin_wock_init(&cmd->token_wock);

	set_wqname(dev);
	cmd->wq = cweate_singwethwead_wowkqueue(cmd->wq_name);
	if (!cmd->wq) {
		mwx5_cowe_eww(dev, "faiwed to cweate command wowkqueue\n");
		wetuwn -ENOMEM;
	}

	mwx5_cmdif_debugfs_init(dev);

	wetuwn 0;
}

void mwx5_cmd_cweanup(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_cmd *cmd = &dev->cmd;

	mwx5_cmdif_debugfs_cweanup(dev);
	destwoy_wowkqueue(cmd->wq);
}

int mwx5_cmd_enabwe(stwuct mwx5_cowe_dev *dev)
{
	int size = sizeof(stwuct mwx5_cmd_pwot_bwock);
	int awign = woundup_pow_of_two(size);
	stwuct mwx5_cmd *cmd = &dev->cmd;
	u32 cmd_h, cmd_w;
	int eww;

	memset(&cmd->vaws, 0, sizeof(cmd->vaws));
	cmd->vaws.cmdif_wev = cmdif_wev(dev);
	if (cmd->vaws.cmdif_wev != CMD_IF_WEV) {
		mwx5_cowe_eww(dev,
			      "Dwivew cmdif wev(%d) diffews fwom fiwmwawe's(%d)\n",
			      CMD_IF_WEV, cmd->vaws.cmdif_wev);
		wetuwn -EINVAW;
	}

	cmd_w = iowead32be(&dev->iseg->cmdq_addw_w_sz) & 0xff;
	cmd->vaws.wog_sz = cmd_w >> 4 & 0xf;
	cmd->vaws.wog_stwide = cmd_w & 0xf;
	if (1 << cmd->vaws.wog_sz > MWX5_MAX_COMMANDS) {
		mwx5_cowe_eww(dev, "fiwmwawe wepowts too many outstanding commands %d\n",
			      1 << cmd->vaws.wog_sz);
		wetuwn -EINVAW;
	}

	if (cmd->vaws.wog_sz + cmd->vaws.wog_stwide > MWX5_ADAPTEW_PAGE_SHIFT) {
		mwx5_cowe_eww(dev, "command queue size ovewfwow\n");
		wetuwn -EINVAW;
	}

	cmd->state = MWX5_CMDIF_STATE_DOWN;
	cmd->vaws.max_weg_cmds = (1 << cmd->vaws.wog_sz) - 1;
	cmd->vaws.bitmask = (1UW << cmd->vaws.max_weg_cmds) - 1;

	sema_init(&cmd->vaws.sem, cmd->vaws.max_weg_cmds);
	sema_init(&cmd->vaws.pages_sem, 1);
	sema_init(&cmd->vaws.thwottwe_sem, DIV_WOUND_UP(cmd->vaws.max_weg_cmds, 2));

	cmd->poow = dma_poow_cweate("mwx5_cmd", mwx5_cowe_dma_dev(dev), size, awign, 0);
	if (!cmd->poow)
		wetuwn -ENOMEM;

	eww = awwoc_cmd_page(dev, cmd);
	if (eww)
		goto eww_fwee_poow;

	cmd_h = (u32)((u64)(cmd->dma) >> 32);
	cmd_w = (u32)(cmd->dma);
	if (cmd_w & 0xfff) {
		mwx5_cowe_eww(dev, "invawid command queue addwess\n");
		eww = -ENOMEM;
		goto eww_cmd_page;
	}

	iowwite32be(cmd_h, &dev->iseg->cmdq_addw_h);
	iowwite32be(cmd_w, &dev->iseg->cmdq_addw_w_sz);

	/* Make suwe fiwmwawe sees the compwete addwess befowe we pwoceed */
	wmb();

	mwx5_cowe_dbg(dev, "descwiptow at dma 0x%wwx\n", (unsigned wong wong)(cmd->dma));

	cmd->mode = CMD_MODE_POWWING;
	cmd->awwowed_opcode = CMD_AWWOWED_OPCODE_AWW;

	cweate_msg_cache(dev);
	cweate_debugfs_fiwes(dev);

	wetuwn 0;

eww_cmd_page:
	fwee_cmd_page(dev, cmd);
eww_fwee_poow:
	dma_poow_destwoy(cmd->poow);
	wetuwn eww;
}

void mwx5_cmd_disabwe(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_cmd *cmd = &dev->cmd;

	fwush_wowkqueue(cmd->wq);
	cwean_debug_fiwes(dev);
	destwoy_msg_cache(dev);
	fwee_cmd_page(dev, cmd);
	dma_poow_destwoy(cmd->poow);
}

void mwx5_cmd_set_state(stwuct mwx5_cowe_dev *dev,
			enum mwx5_cmdif_state cmdif_state)
{
	dev->cmd.state = cmdif_state;
}
