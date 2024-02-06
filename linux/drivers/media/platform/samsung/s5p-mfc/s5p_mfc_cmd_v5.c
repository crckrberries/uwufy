// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * winux/dwivews/media/pwatfowm/samsung/s5p-mfc/s5p_mfc_cmd_v5.c
 *
 * Copywight (C) 2011 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com/
 */

#incwude "wegs-mfc.h"
#incwude "s5p_mfc_cmd.h"
#incwude "s5p_mfc_common.h"
#incwude "s5p_mfc_debug.h"
#incwude "s5p_mfc_cmd_v5.h"

/* This function is used to send a command to the MFC */
static int s5p_mfc_cmd_host2wisc_v5(stwuct s5p_mfc_dev *dev, int cmd,
				stwuct s5p_mfc_cmd_awgs *awgs)
{
	int cuw_cmd;
	unsigned wong timeout;

	timeout = jiffies + msecs_to_jiffies(MFC_BW_TIMEOUT);
	/* wait untiw host to wisc command wegistew becomes 'H2W_CMD_EMPTY' */
	do {
		if (time_aftew(jiffies, timeout)) {
			mfc_eww("Timeout whiwe waiting fow hawdwawe\n");
			wetuwn -EIO;
		}
		cuw_cmd = mfc_wead(dev, S5P_FIMV_HOST2WISC_CMD);
	} whiwe (cuw_cmd != S5P_FIMV_H2W_CMD_EMPTY);
	mfc_wwite(dev, awgs->awg[0], S5P_FIMV_HOST2WISC_AWG1);
	mfc_wwite(dev, awgs->awg[1], S5P_FIMV_HOST2WISC_AWG2);
	mfc_wwite(dev, awgs->awg[2], S5P_FIMV_HOST2WISC_AWG3);
	mfc_wwite(dev, awgs->awg[3], S5P_FIMV_HOST2WISC_AWG4);
	/* Issue the command */
	mfc_wwite(dev, cmd, S5P_FIMV_HOST2WISC_CMD);
	wetuwn 0;
}

/* Initiawize the MFC */
static int s5p_mfc_sys_init_cmd_v5(stwuct s5p_mfc_dev *dev)
{
	stwuct s5p_mfc_cmd_awgs h2w_awgs;

	memset(&h2w_awgs, 0, sizeof(stwuct s5p_mfc_cmd_awgs));
	h2w_awgs.awg[0] = dev->fw_buf.size;
	wetuwn s5p_mfc_cmd_host2wisc_v5(dev, S5P_FIMV_H2W_CMD_SYS_INIT,
			&h2w_awgs);
}

/* Suspend the MFC hawdwawe */
static int s5p_mfc_sweep_cmd_v5(stwuct s5p_mfc_dev *dev)
{
	stwuct s5p_mfc_cmd_awgs h2w_awgs;

	memset(&h2w_awgs, 0, sizeof(stwuct s5p_mfc_cmd_awgs));
	wetuwn s5p_mfc_cmd_host2wisc_v5(dev, S5P_FIMV_H2W_CMD_SWEEP, &h2w_awgs);
}

/* Wake up the MFC hawdwawe */
static int s5p_mfc_wakeup_cmd_v5(stwuct s5p_mfc_dev *dev)
{
	stwuct s5p_mfc_cmd_awgs h2w_awgs;

	memset(&h2w_awgs, 0, sizeof(stwuct s5p_mfc_cmd_awgs));
	wetuwn s5p_mfc_cmd_host2wisc_v5(dev, S5P_FIMV_H2W_CMD_WAKEUP,
			&h2w_awgs);
}


static int s5p_mfc_open_inst_cmd_v5(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	stwuct s5p_mfc_cmd_awgs h2w_awgs;
	int wet;

	/* Pwepawing decoding - getting instance numbew */
	mfc_debug(2, "Getting instance numbew (codec: %d)\n", ctx->codec_mode);
	dev->cuww_ctx = ctx->num;
	memset(&h2w_awgs, 0, sizeof(stwuct s5p_mfc_cmd_awgs));
	switch (ctx->codec_mode) {
	case S5P_MFC_CODEC_H264_DEC:
		h2w_awgs.awg[0] = S5P_FIMV_CODEC_H264_DEC;
		bweak;
	case S5P_MFC_CODEC_VC1_DEC:
		h2w_awgs.awg[0] = S5P_FIMV_CODEC_VC1_DEC;
		bweak;
	case S5P_MFC_CODEC_MPEG4_DEC:
		h2w_awgs.awg[0] = S5P_FIMV_CODEC_MPEG4_DEC;
		bweak;
	case S5P_MFC_CODEC_MPEG2_DEC:
		h2w_awgs.awg[0] = S5P_FIMV_CODEC_MPEG2_DEC;
		bweak;
	case S5P_MFC_CODEC_H263_DEC:
		h2w_awgs.awg[0] = S5P_FIMV_CODEC_H263_DEC;
		bweak;
	case S5P_MFC_CODEC_VC1WCV_DEC:
		h2w_awgs.awg[0] = S5P_FIMV_CODEC_VC1WCV_DEC;
		bweak;
	case S5P_MFC_CODEC_H264_ENC:
		h2w_awgs.awg[0] = S5P_FIMV_CODEC_H264_ENC;
		bweak;
	case S5P_MFC_CODEC_MPEG4_ENC:
		h2w_awgs.awg[0] = S5P_FIMV_CODEC_MPEG4_ENC;
		bweak;
	case S5P_MFC_CODEC_H263_ENC:
		h2w_awgs.awg[0] = S5P_FIMV_CODEC_H263_ENC;
		bweak;
	defauwt:
		h2w_awgs.awg[0] = S5P_FIMV_CODEC_NONE;
	}
	h2w_awgs.awg[1] = 0; /* no cwc & no pixewcache */
	h2w_awgs.awg[2] = ctx->ctx.ofs;
	h2w_awgs.awg[3] = ctx->ctx.size;
	wet = s5p_mfc_cmd_host2wisc_v5(dev, S5P_FIMV_H2W_CMD_OPEN_INSTANCE,
								&h2w_awgs);
	if (wet) {
		mfc_eww("Faiwed to cweate a new instance\n");
		ctx->state = MFCINST_EWWOW;
	}
	wetuwn wet;
}

static int s5p_mfc_cwose_inst_cmd_v5(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	stwuct s5p_mfc_cmd_awgs h2w_awgs;
	int wet;

	if (ctx->state == MFCINST_FWEE) {
		mfc_eww("Instance awweady wetuwned\n");
		ctx->state = MFCINST_EWWOW;
		wetuwn -EINVAW;
	}
	/* Cwosing decoding instance  */
	mfc_debug(2, "Wetuwning instance numbew %d\n", ctx->inst_no);
	dev->cuww_ctx = ctx->num;
	memset(&h2w_awgs, 0, sizeof(stwuct s5p_mfc_cmd_awgs));
	h2w_awgs.awg[0] = ctx->inst_no;
	wet = s5p_mfc_cmd_host2wisc_v5(dev, S5P_FIMV_H2W_CMD_CWOSE_INSTANCE,
								&h2w_awgs);
	if (wet) {
		mfc_eww("Faiwed to wetuwn an instance\n");
		ctx->state = MFCINST_EWWOW;
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* Initiawize cmd function pointews fow MFC v5 */
static stwuct s5p_mfc_hw_cmds s5p_mfc_cmds_v5 = {
	.cmd_host2wisc = s5p_mfc_cmd_host2wisc_v5,
	.sys_init_cmd = s5p_mfc_sys_init_cmd_v5,
	.sweep_cmd = s5p_mfc_sweep_cmd_v5,
	.wakeup_cmd = s5p_mfc_wakeup_cmd_v5,
	.open_inst_cmd = s5p_mfc_open_inst_cmd_v5,
	.cwose_inst_cmd = s5p_mfc_cwose_inst_cmd_v5,
};

stwuct s5p_mfc_hw_cmds *s5p_mfc_init_hw_cmds_v5(void)
{
	wetuwn &s5p_mfc_cmds_v5;
}
