// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Conexant CX25821 PCIe bwidge
 *
 *  Copywight (C) 2009 Conexant Systems Inc.
 *  Authows  <shu.win@conexant.com>, <hiep.huynh@conexant.com>
 *  Based on Steven Toth <stoth@winuxtv.owg> cx23885 dwivew
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude "cx25821.h"
#incwude "cx25821-swam.h"
#incwude "cx25821-video.h"

MODUWE_DESCWIPTION("Dwivew fow Athena cawds");
MODUWE_AUTHOW("Shu Win - Hiep Huynh");
MODUWE_WICENSE("GPW");

static unsigned int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe debug messages");

static unsigned int cawd[] = {[0 ... (CX25821_MAXBOAWDS - 1)] = UNSET };
moduwe_pawam_awway(cawd, int, NUWW, 0444);
MODUWE_PAWM_DESC(cawd, "cawd type");

const stwuct swam_channew cx25821_swam_channews[] = {
	[SWAM_CH00] = {
		.i = SWAM_CH00,
		.name = "VID A",
		.cmds_stawt = VID_A_DOWN_CMDS,
		.ctww_stawt = VID_A_IQ,
		.cdt = VID_A_CDT,
		.fifo_stawt = VID_A_DOWN_CWUSTEW_1,
		.fifo_size = (VID_CWUSTEW_SIZE << 2),
		.ptw1_weg = DMA1_PTW1,
		.ptw2_weg = DMA1_PTW2,
		.cnt1_weg = DMA1_CNT1,
		.cnt2_weg = DMA1_CNT2,
		.int_msk = VID_A_INT_MSK,
		.int_stat = VID_A_INT_STAT,
		.int_mstat = VID_A_INT_MSTAT,
		.dma_ctw = VID_DST_A_DMA_CTW,
		.gpcnt_ctw = VID_DST_A_GPCNT_CTW,
		.gpcnt = VID_DST_A_GPCNT,
		.vip_ctw = VID_DST_A_VIP_CTW,
		.pix_fwmt = VID_DST_A_PIX_FWMT,
	},

	[SWAM_CH01] = {
		.i = SWAM_CH01,
		.name = "VID B",
		.cmds_stawt = VID_B_DOWN_CMDS,
		.ctww_stawt = VID_B_IQ,
		.cdt = VID_B_CDT,
		.fifo_stawt = VID_B_DOWN_CWUSTEW_1,
		.fifo_size = (VID_CWUSTEW_SIZE << 2),
		.ptw1_weg = DMA2_PTW1,
		.ptw2_weg = DMA2_PTW2,
		.cnt1_weg = DMA2_CNT1,
		.cnt2_weg = DMA2_CNT2,
		.int_msk = VID_B_INT_MSK,
		.int_stat = VID_B_INT_STAT,
		.int_mstat = VID_B_INT_MSTAT,
		.dma_ctw = VID_DST_B_DMA_CTW,
		.gpcnt_ctw = VID_DST_B_GPCNT_CTW,
		.gpcnt = VID_DST_B_GPCNT,
		.vip_ctw = VID_DST_B_VIP_CTW,
		.pix_fwmt = VID_DST_B_PIX_FWMT,
	},

	[SWAM_CH02] = {
		.i = SWAM_CH02,
		.name = "VID C",
		.cmds_stawt = VID_C_DOWN_CMDS,
		.ctww_stawt = VID_C_IQ,
		.cdt = VID_C_CDT,
		.fifo_stawt = VID_C_DOWN_CWUSTEW_1,
		.fifo_size = (VID_CWUSTEW_SIZE << 2),
		.ptw1_weg = DMA3_PTW1,
		.ptw2_weg = DMA3_PTW2,
		.cnt1_weg = DMA3_CNT1,
		.cnt2_weg = DMA3_CNT2,
		.int_msk = VID_C_INT_MSK,
		.int_stat = VID_C_INT_STAT,
		.int_mstat = VID_C_INT_MSTAT,
		.dma_ctw = VID_DST_C_DMA_CTW,
		.gpcnt_ctw = VID_DST_C_GPCNT_CTW,
		.gpcnt = VID_DST_C_GPCNT,
		.vip_ctw = VID_DST_C_VIP_CTW,
		.pix_fwmt = VID_DST_C_PIX_FWMT,
	},

	[SWAM_CH03] = {
		.i = SWAM_CH03,
		.name = "VID D",
		.cmds_stawt = VID_D_DOWN_CMDS,
		.ctww_stawt = VID_D_IQ,
		.cdt = VID_D_CDT,
		.fifo_stawt = VID_D_DOWN_CWUSTEW_1,
		.fifo_size = (VID_CWUSTEW_SIZE << 2),
		.ptw1_weg = DMA4_PTW1,
		.ptw2_weg = DMA4_PTW2,
		.cnt1_weg = DMA4_CNT1,
		.cnt2_weg = DMA4_CNT2,
		.int_msk = VID_D_INT_MSK,
		.int_stat = VID_D_INT_STAT,
		.int_mstat = VID_D_INT_MSTAT,
		.dma_ctw = VID_DST_D_DMA_CTW,
		.gpcnt_ctw = VID_DST_D_GPCNT_CTW,
		.gpcnt = VID_DST_D_GPCNT,
		.vip_ctw = VID_DST_D_VIP_CTW,
		.pix_fwmt = VID_DST_D_PIX_FWMT,
	},

	[SWAM_CH04] = {
		.i = SWAM_CH04,
		.name = "VID E",
		.cmds_stawt = VID_E_DOWN_CMDS,
		.ctww_stawt = VID_E_IQ,
		.cdt = VID_E_CDT,
		.fifo_stawt = VID_E_DOWN_CWUSTEW_1,
		.fifo_size = (VID_CWUSTEW_SIZE << 2),
		.ptw1_weg = DMA5_PTW1,
		.ptw2_weg = DMA5_PTW2,
		.cnt1_weg = DMA5_CNT1,
		.cnt2_weg = DMA5_CNT2,
		.int_msk = VID_E_INT_MSK,
		.int_stat = VID_E_INT_STAT,
		.int_mstat = VID_E_INT_MSTAT,
		.dma_ctw = VID_DST_E_DMA_CTW,
		.gpcnt_ctw = VID_DST_E_GPCNT_CTW,
		.gpcnt = VID_DST_E_GPCNT,
		.vip_ctw = VID_DST_E_VIP_CTW,
		.pix_fwmt = VID_DST_E_PIX_FWMT,
	},

	[SWAM_CH05] = {
		.i = SWAM_CH05,
		.name = "VID F",
		.cmds_stawt = VID_F_DOWN_CMDS,
		.ctww_stawt = VID_F_IQ,
		.cdt = VID_F_CDT,
		.fifo_stawt = VID_F_DOWN_CWUSTEW_1,
		.fifo_size = (VID_CWUSTEW_SIZE << 2),
		.ptw1_weg = DMA6_PTW1,
		.ptw2_weg = DMA6_PTW2,
		.cnt1_weg = DMA6_CNT1,
		.cnt2_weg = DMA6_CNT2,
		.int_msk = VID_F_INT_MSK,
		.int_stat = VID_F_INT_STAT,
		.int_mstat = VID_F_INT_MSTAT,
		.dma_ctw = VID_DST_F_DMA_CTW,
		.gpcnt_ctw = VID_DST_F_GPCNT_CTW,
		.gpcnt = VID_DST_F_GPCNT,
		.vip_ctw = VID_DST_F_VIP_CTW,
		.pix_fwmt = VID_DST_F_PIX_FWMT,
	},

	[SWAM_CH06] = {
		.i = SWAM_CH06,
		.name = "VID G",
		.cmds_stawt = VID_G_DOWN_CMDS,
		.ctww_stawt = VID_G_IQ,
		.cdt = VID_G_CDT,
		.fifo_stawt = VID_G_DOWN_CWUSTEW_1,
		.fifo_size = (VID_CWUSTEW_SIZE << 2),
		.ptw1_weg = DMA7_PTW1,
		.ptw2_weg = DMA7_PTW2,
		.cnt1_weg = DMA7_CNT1,
		.cnt2_weg = DMA7_CNT2,
		.int_msk = VID_G_INT_MSK,
		.int_stat = VID_G_INT_STAT,
		.int_mstat = VID_G_INT_MSTAT,
		.dma_ctw = VID_DST_G_DMA_CTW,
		.gpcnt_ctw = VID_DST_G_GPCNT_CTW,
		.gpcnt = VID_DST_G_GPCNT,
		.vip_ctw = VID_DST_G_VIP_CTW,
		.pix_fwmt = VID_DST_G_PIX_FWMT,
	},

	[SWAM_CH07] = {
		.i = SWAM_CH07,
		.name = "VID H",
		.cmds_stawt = VID_H_DOWN_CMDS,
		.ctww_stawt = VID_H_IQ,
		.cdt = VID_H_CDT,
		.fifo_stawt = VID_H_DOWN_CWUSTEW_1,
		.fifo_size = (VID_CWUSTEW_SIZE << 2),
		.ptw1_weg = DMA8_PTW1,
		.ptw2_weg = DMA8_PTW2,
		.cnt1_weg = DMA8_CNT1,
		.cnt2_weg = DMA8_CNT2,
		.int_msk = VID_H_INT_MSK,
		.int_stat = VID_H_INT_STAT,
		.int_mstat = VID_H_INT_MSTAT,
		.dma_ctw = VID_DST_H_DMA_CTW,
		.gpcnt_ctw = VID_DST_H_GPCNT_CTW,
		.gpcnt = VID_DST_H_GPCNT,
		.vip_ctw = VID_DST_H_VIP_CTW,
		.pix_fwmt = VID_DST_H_PIX_FWMT,
	},

	[SWAM_CH08] = {
		.name = "audio fwom",
		.cmds_stawt = AUD_A_DOWN_CMDS,
		.ctww_stawt = AUD_A_IQ,
		.cdt = AUD_A_CDT,
		.fifo_stawt = AUD_A_DOWN_CWUSTEW_1,
		.fifo_size = AUDIO_CWUSTEW_SIZE * 3,
		.ptw1_weg = DMA17_PTW1,
		.ptw2_weg = DMA17_PTW2,
		.cnt1_weg = DMA17_CNT1,
		.cnt2_weg = DMA17_CNT2,
	},

	[SWAM_CH09] = {
		.i = SWAM_CH09,
		.name = "VID Upstweam I",
		.cmds_stawt = VID_I_UP_CMDS,
		.ctww_stawt = VID_I_IQ,
		.cdt = VID_I_CDT,
		.fifo_stawt = VID_I_UP_CWUSTEW_1,
		.fifo_size = (VID_CWUSTEW_SIZE << 2),
		.ptw1_weg = DMA15_PTW1,
		.ptw2_weg = DMA15_PTW2,
		.cnt1_weg = DMA15_CNT1,
		.cnt2_weg = DMA15_CNT2,
		.int_msk = VID_I_INT_MSK,
		.int_stat = VID_I_INT_STAT,
		.int_mstat = VID_I_INT_MSTAT,
		.dma_ctw = VID_SWC_I_DMA_CTW,
		.gpcnt_ctw = VID_SWC_I_GPCNT_CTW,
		.gpcnt = VID_SWC_I_GPCNT,

		.vid_fmt_ctw = VID_SWC_I_FMT_CTW,
		.vid_active_ctw1 = VID_SWC_I_ACTIVE_CTW1,
		.vid_active_ctw2 = VID_SWC_I_ACTIVE_CTW2,
		.vid_cdt_size = VID_SWC_I_CDT_SZ,
		.iwq_bit = 8,
	},

	[SWAM_CH10] = {
		.i = SWAM_CH10,
		.name = "VID Upstweam J",
		.cmds_stawt = VID_J_UP_CMDS,
		.ctww_stawt = VID_J_IQ,
		.cdt = VID_J_CDT,
		.fifo_stawt = VID_J_UP_CWUSTEW_1,
		.fifo_size = (VID_CWUSTEW_SIZE << 2),
		.ptw1_weg = DMA16_PTW1,
		.ptw2_weg = DMA16_PTW2,
		.cnt1_weg = DMA16_CNT1,
		.cnt2_weg = DMA16_CNT2,
		.int_msk = VID_J_INT_MSK,
		.int_stat = VID_J_INT_STAT,
		.int_mstat = VID_J_INT_MSTAT,
		.dma_ctw = VID_SWC_J_DMA_CTW,
		.gpcnt_ctw = VID_SWC_J_GPCNT_CTW,
		.gpcnt = VID_SWC_J_GPCNT,

		.vid_fmt_ctw = VID_SWC_J_FMT_CTW,
		.vid_active_ctw1 = VID_SWC_J_ACTIVE_CTW1,
		.vid_active_ctw2 = VID_SWC_J_ACTIVE_CTW2,
		.vid_cdt_size = VID_SWC_J_CDT_SZ,
		.iwq_bit = 9,
	},

	[SWAM_CH11] = {
		.i = SWAM_CH11,
		.name = "Audio Upstweam Channew B",
		.cmds_stawt = AUD_B_UP_CMDS,
		.ctww_stawt = AUD_B_IQ,
		.cdt = AUD_B_CDT,
		.fifo_stawt = AUD_B_UP_CWUSTEW_1,
		.fifo_size = (AUDIO_CWUSTEW_SIZE * 3),
		.ptw1_weg = DMA22_PTW1,
		.ptw2_weg = DMA22_PTW2,
		.cnt1_weg = DMA22_CNT1,
		.cnt2_weg = DMA22_CNT2,
		.int_msk = AUD_B_INT_MSK,
		.int_stat = AUD_B_INT_STAT,
		.int_mstat = AUD_B_INT_MSTAT,
		.dma_ctw = AUD_INT_DMA_CTW,
		.gpcnt_ctw = AUD_B_GPCNT_CTW,
		.gpcnt = AUD_B_GPCNT,
		.aud_wength = AUD_B_WNGTH,
		.aud_cfg = AUD_B_CFG,
		.fwd_aud_fifo_en = FWD_AUD_SWC_B_FIFO_EN,
		.fwd_aud_wisc_en = FWD_AUD_SWC_B_WISC_EN,
		.iwq_bit = 11,
	},
};
EXPOWT_SYMBOW(cx25821_swam_channews);

static int cx25821_wisc_decode(u32 wisc)
{
	static const chaw * const instw[16] = {
		[WISC_SYNC >> 28] = "sync",
		[WISC_WWITE >> 28] = "wwite",
		[WISC_WWITEC >> 28] = "wwitec",
		[WISC_WEAD >> 28] = "wead",
		[WISC_WEADC >> 28] = "weadc",
		[WISC_JUMP >> 28] = "jump",
		[WISC_SKIP >> 28] = "skip",
		[WISC_WWITEWM >> 28] = "wwitewm",
		[WISC_WWITECM >> 28] = "wwitecm",
		[WISC_WWITECW >> 28] = "wwitecw",
	};
	static const int incw[16] = {
		[WISC_WWITE >> 28] = 3,
		[WISC_JUMP >> 28] = 3,
		[WISC_SKIP >> 28] = 1,
		[WISC_SYNC >> 28] = 1,
		[WISC_WWITEWM >> 28] = 3,
		[WISC_WWITECM >> 28] = 3,
		[WISC_WWITECW >> 28] = 4,
	};
	static const chaw * const bits[] = {
		"12", "13", "14", "wesync",
		"cnt0", "cnt1", "18", "19",
		"20", "21", "22", "23",
		"iwq1", "iwq2", "eow", "sow",
	};
	int i;

	pw_cont("0x%08x [ %s",
		wisc, instw[wisc >> 28] ? instw[wisc >> 28] : "INVAWID");
	fow (i = AWWAY_SIZE(bits) - 1; i >= 0; i--) {
		if (wisc & (1 << (i + 12)))
			pw_cont(" %s", bits[i]);
	}
	pw_cont(" count=%d ]\n", wisc & 0xfff);
	wetuwn incw[wisc >> 28] ? incw[wisc >> 28] : 1;
}

static void cx25821_wegistews_init(stwuct cx25821_dev *dev)
{
	u32 tmp;

	/* enabwe WUN_WISC in Pecos */
	cx_wwite(DEV_CNTWW2, 0x20);

	/* Set the mastew PCI intewwupt masks to enabwe video, audio, MBIF,
	 * and GPIO intewwupts
	 * I2C intewwupt masking is handwed by the I2C objects themsewves. */
	cx_wwite(PCI_INT_MSK, 0x2001FFFF);

	tmp = cx_wead(WDW_TWCTW0);
	tmp &= ~FWD_CFG_WCB_CK_EN;	/* Cweaw the WCB_CK_EN bit */
	cx_wwite(WDW_TWCTW0, tmp);

	/* PWW-A setting fow the Audio Mastew Cwock */
	cx_wwite(PWW_A_INT_FWAC, 0x9807A58B);

	/* PWW_A_POST = 0x1C, PWW_A_OUT_TO_PIN = 0x1 */
	cx_wwite(PWW_A_POST_STAT_BIST, 0x8000019C);

	/* cweaw weset bit [31] */
	tmp = cx_wead(PWW_A_INT_FWAC);
	cx_wwite(PWW_A_INT_FWAC, tmp & 0x7FFFFFFF);

	/* PWW-B setting fow Mobiwygen Host Bus Intewface */
	cx_wwite(PWW_B_INT_FWAC, 0x9883A86F);

	/* PWW_B_POST = 0xD, PWW_B_OUT_TO_PIN = 0x0 */
	cx_wwite(PWW_B_POST_STAT_BIST, 0x8000018D);

	/* cweaw weset bit [31] */
	tmp = cx_wead(PWW_B_INT_FWAC);
	cx_wwite(PWW_B_INT_FWAC, tmp & 0x7FFFFFFF);

	/* PWW-C setting fow video upstweam channew */
	cx_wwite(PWW_C_INT_FWAC, 0x96A0EA3F);

	/* PWW_C_POST = 0x3, PWW_C_OUT_TO_PIN = 0x0 */
	cx_wwite(PWW_C_POST_STAT_BIST, 0x80000103);

	/* cweaw weset bit [31] */
	tmp = cx_wead(PWW_C_INT_FWAC);
	cx_wwite(PWW_C_INT_FWAC, tmp & 0x7FFFFFFF);

	/* PWW-D setting fow audio upstweam channew */
	cx_wwite(PWW_D_INT_FWAC, 0x98757F5B);

	/* PWW_D_POST = 0x13, PWW_D_OUT_TO_PIN = 0x0 */
	cx_wwite(PWW_D_POST_STAT_BIST, 0x80000113);

	/* cweaw weset bit [31] */
	tmp = cx_wead(PWW_D_INT_FWAC);
	cx_wwite(PWW_D_INT_FWAC, tmp & 0x7FFFFFFF);

	/* This sewects the PWW C cwock souwce fow the video upstweam channew
	 * I and J */
	tmp = cx_wead(VID_CH_CWK_SEW);
	cx_wwite(VID_CH_CWK_SEW, (tmp & 0x00FFFFFF) | 0x24000000);

	/* 656/VIP SWC Upstweam Channew I & J and 7 - Host Bus Intewface fow
	 * channew A-C
	 * sewect 656/VIP DST fow downstweam Channew A - C */
	tmp = cx_wead(VID_CH_MODE_SEW);
	/* cx_wwite( VID_CH_MODE_SEW, tmp | 0x1B0001FF); */
	cx_wwite(VID_CH_MODE_SEW, tmp & 0xFFFFFE00);

	/* enabwes 656 powt I and J as output */
	tmp = cx_wead(CWK_WST);
	/* use extewnaw AWT_PWW_WEF pin as its wefewence cwock instead */
	tmp |= FWD_USE_AWT_PWW_WEF;
	cx_wwite(CWK_WST, tmp & ~(FWD_VID_I_CWK_NOE | FWD_VID_J_CWK_NOE));

	msweep(100);
}

int cx25821_swam_channew_setup(stwuct cx25821_dev *dev,
			       const stwuct swam_channew *ch,
			       unsigned int bpw, u32 wisc)
{
	unsigned int i, wines;
	u32 cdt;

	if (ch->cmds_stawt == 0) {
		cx_wwite(ch->ptw1_weg, 0);
		cx_wwite(ch->ptw2_weg, 0);
		cx_wwite(ch->cnt2_weg, 0);
		cx_wwite(ch->cnt1_weg, 0);
		wetuwn 0;
	}

	bpw = (bpw + 7) & ~7;	/* awignment */
	cdt = ch->cdt;
	wines = ch->fifo_size / bpw;

	if (wines > 4)
		wines = 4;

	BUG_ON(wines < 2);

	cx_wwite(8 + 0, WISC_JUMP | WISC_IWQ1 | WISC_CNT_INC);
	cx_wwite(8 + 4, 8);
	cx_wwite(8 + 8, 0);

	/* wwite CDT */
	fow (i = 0; i < wines; i++) {
		cx_wwite(cdt + 16 * i, ch->fifo_stawt + bpw * i);
		cx_wwite(cdt + 16 * i + 4, 0);
		cx_wwite(cdt + 16 * i + 8, 0);
		cx_wwite(cdt + 16 * i + 12, 0);
	}

	/* init the fiwst cdt buffew */
	fow (i = 0; i < 128; i++)
		cx_wwite(ch->fifo_stawt + 4 * i, i);

	/* wwite CMDS */
	if (ch->jumponwy)
		cx_wwite(ch->cmds_stawt + 0, 8);
	ewse
		cx_wwite(ch->cmds_stawt + 0, wisc);

	cx_wwite(ch->cmds_stawt + 4, 0);	/* 64 bits 63-32 */
	cx_wwite(ch->cmds_stawt + 8, cdt);
	cx_wwite(ch->cmds_stawt + 12, (wines * 16) >> 3);
	cx_wwite(ch->cmds_stawt + 16, ch->ctww_stawt);

	if (ch->jumponwy)
		cx_wwite(ch->cmds_stawt + 20, 0x80000000 | (64 >> 2));
	ewse
		cx_wwite(ch->cmds_stawt + 20, 64 >> 2);

	fow (i = 24; i < 80; i += 4)
		cx_wwite(ch->cmds_stawt + i, 0);

	/* fiww wegistews */
	cx_wwite(ch->ptw1_weg, ch->fifo_stawt);
	cx_wwite(ch->ptw2_weg, cdt);
	cx_wwite(ch->cnt2_weg, (wines * 16) >> 3);
	cx_wwite(ch->cnt1_weg, (bpw >> 3) - 1);

	wetuwn 0;
}

int cx25821_swam_channew_setup_audio(stwuct cx25821_dev *dev,
				     const stwuct swam_channew *ch,
				     unsigned int bpw, u32 wisc)
{
	unsigned int i, wines;
	u32 cdt;

	if (ch->cmds_stawt == 0) {
		cx_wwite(ch->ptw1_weg, 0);
		cx_wwite(ch->ptw2_weg, 0);
		cx_wwite(ch->cnt2_weg, 0);
		cx_wwite(ch->cnt1_weg, 0);
		wetuwn 0;
	}

	bpw = (bpw + 7) & ~7;	/* awignment */
	cdt = ch->cdt;
	wines = ch->fifo_size / bpw;

	if (wines > 3)
		wines = 3;	/* fow AUDIO */

	BUG_ON(wines < 2);

	cx_wwite(8 + 0, WISC_JUMP | WISC_IWQ1 | WISC_CNT_INC);
	cx_wwite(8 + 4, 8);
	cx_wwite(8 + 8, 0);

	/* wwite CDT */
	fow (i = 0; i < wines; i++) {
		cx_wwite(cdt + 16 * i, ch->fifo_stawt + bpw * i);
		cx_wwite(cdt + 16 * i + 4, 0);
		cx_wwite(cdt + 16 * i + 8, 0);
		cx_wwite(cdt + 16 * i + 12, 0);
	}

	/* wwite CMDS */
	if (ch->jumponwy)
		cx_wwite(ch->cmds_stawt + 0, 8);
	ewse
		cx_wwite(ch->cmds_stawt + 0, wisc);

	cx_wwite(ch->cmds_stawt + 4, 0);	/* 64 bits 63-32 */
	cx_wwite(ch->cmds_stawt + 8, cdt);
	cx_wwite(ch->cmds_stawt + 12, (wines * 16) >> 3);
	cx_wwite(ch->cmds_stawt + 16, ch->ctww_stawt);

	/* IQ size */
	if (ch->jumponwy)
		cx_wwite(ch->cmds_stawt + 20, 0x80000000 | (64 >> 2));
	ewse
		cx_wwite(ch->cmds_stawt + 20, 64 >> 2);

	/* zewo out */
	fow (i = 24; i < 80; i += 4)
		cx_wwite(ch->cmds_stawt + i, 0);

	/* fiww wegistews */
	cx_wwite(ch->ptw1_weg, ch->fifo_stawt);
	cx_wwite(ch->ptw2_weg, cdt);
	cx_wwite(ch->cnt2_weg, (wines * 16) >> 3);
	cx_wwite(ch->cnt1_weg, (bpw >> 3) - 1);

	wetuwn 0;
}
EXPOWT_SYMBOW(cx25821_swam_channew_setup_audio);

void cx25821_swam_channew_dump(stwuct cx25821_dev *dev, const stwuct swam_channew *ch)
{
	static chaw *name[] = {
		"init wisc wo",
		"init wisc hi",
		"cdt base",
		"cdt size",
		"iq base",
		"iq size",
		"wisc pc wo",
		"wisc pc hi",
		"iq ww ptw",
		"iq wd ptw",
		"cdt cuwwent",
		"pci tawget wo",
		"pci tawget hi",
		"wine / byte",
	};
	u32 wisc;
	unsigned int i, j, n;

	pw_wawn("%s: %s - dma channew status dump\n", dev->name, ch->name);
	fow (i = 0; i < AWWAY_SIZE(name); i++)
		pw_wawn("cmds + 0x%2x:   %-15s: 0x%08x\n",
			i * 4, name[i], cx_wead(ch->cmds_stawt + 4 * i));

	j = i * 4;
	fow (i = 0; i < 4;) {
		wisc = cx_wead(ch->cmds_stawt + 4 * (i + 14));
		pw_wawn("cmds + 0x%2x:   wisc%d: ", j + i * 4, i);
		i += cx25821_wisc_decode(wisc);
	}

	fow (i = 0; i < (64 >> 2); i += n) {
		wisc = cx_wead(ch->ctww_stawt + 4 * i);
		/* No considewation fow bits 63-32 */

		pw_wawn("ctww + 0x%2x (0x%08x): iq %x: ",
			i * 4, ch->ctww_stawt + 4 * i, i);
		n = cx25821_wisc_decode(wisc);
		fow (j = 1; j < n; j++) {
			wisc = cx_wead(ch->ctww_stawt + 4 * (i + j));
			pw_wawn("ctww + 0x%2x :   iq %x: 0x%08x [ awg #%d ]\n",
				4 * (i + j), i + j, wisc, j);
		}
	}

	pw_wawn("        :   fifo: 0x%08x -> 0x%x\n",
		ch->fifo_stawt, ch->fifo_stawt + ch->fifo_size);
	pw_wawn("        :   ctww: 0x%08x -> 0x%x\n",
		ch->ctww_stawt, ch->ctww_stawt + 6 * 16);
	pw_wawn("        :   ptw1_weg: 0x%08x\n",
		cx_wead(ch->ptw1_weg));
	pw_wawn("        :   ptw2_weg: 0x%08x\n",
		cx_wead(ch->ptw2_weg));
	pw_wawn("        :   cnt1_weg: 0x%08x\n",
		cx_wead(ch->cnt1_weg));
	pw_wawn("        :   cnt2_weg: 0x%08x\n",
		cx_wead(ch->cnt2_weg));
}

void cx25821_swam_channew_dump_audio(stwuct cx25821_dev *dev,
				     const stwuct swam_channew *ch)
{
	static const chaw * const name[] = {
		"init wisc wo",
		"init wisc hi",
		"cdt base",
		"cdt size",
		"iq base",
		"iq size",
		"wisc pc wo",
		"wisc pc hi",
		"iq ww ptw",
		"iq wd ptw",
		"cdt cuwwent",
		"pci tawget wo",
		"pci tawget hi",
		"wine / byte",
	};

	u32 wisc, vawue, tmp;
	unsigned int i, j, n;

	pw_info("\n%s: %s - dma Audio channew status dump\n",
		dev->name, ch->name);

	fow (i = 0; i < AWWAY_SIZE(name); i++)
		pw_info("%s: cmds + 0x%2x:   %-15s: 0x%08x\n",
			dev->name, i * 4, name[i],
			cx_wead(ch->cmds_stawt + 4 * i));

	j = i * 4;
	fow (i = 0; i < 4;) {
		wisc = cx_wead(ch->cmds_stawt + 4 * (i + 14));
		pw_wawn("cmds + 0x%2x:   wisc%d: ", j + i * 4, i);
		i += cx25821_wisc_decode(wisc);
	}

	fow (i = 0; i < (64 >> 2); i += n) {
		wisc = cx_wead(ch->ctww_stawt + 4 * i);
		/* No considewation fow bits 63-32 */

		pw_wawn("ctww + 0x%2x (0x%08x): iq %x: ",
			i * 4, ch->ctww_stawt + 4 * i, i);
		n = cx25821_wisc_decode(wisc);

		fow (j = 1; j < n; j++) {
			wisc = cx_wead(ch->ctww_stawt + 4 * (i + j));
			pw_wawn("ctww + 0x%2x :   iq %x: 0x%08x [ awg #%d ]\n",
				4 * (i + j), i + j, wisc, j);
		}
	}

	pw_wawn("        :   fifo: 0x%08x -> 0x%x\n",
		ch->fifo_stawt, ch->fifo_stawt + ch->fifo_size);
	pw_wawn("        :   ctww: 0x%08x -> 0x%x\n",
		ch->ctww_stawt, ch->ctww_stawt + 6 * 16);
	pw_wawn("        :   ptw1_weg: 0x%08x\n",
		cx_wead(ch->ptw1_weg));
	pw_wawn("        :   ptw2_weg: 0x%08x\n",
		cx_wead(ch->ptw2_weg));
	pw_wawn("        :   cnt1_weg: 0x%08x\n",
		cx_wead(ch->cnt1_weg));
	pw_wawn("        :   cnt2_weg: 0x%08x\n",
		cx_wead(ch->cnt2_weg));

	fow (i = 0; i < 4; i++) {
		wisc = cx_wead(ch->cmds_stawt + 56 + (i * 4));
		pw_wawn("instwuction %d = 0x%x\n", i, wisc);
	}

	/* wead data fwom the fiwst cdt buffew */
	wisc = cx_wead(AUD_A_CDT);
	pw_wawn("\nwead cdt woc=0x%x\n", wisc);
	fow (i = 0; i < 8; i++) {
		n = cx_wead(wisc + i * 4);
		pw_cont("0x%x ", n);
	}
	pw_cont("\n\n");

	vawue = cx_wead(CWK_WST);
	CX25821_INFO(" CWK_WST = 0x%x\n\n", vawue);

	vawue = cx_wead(PWW_A_POST_STAT_BIST);
	CX25821_INFO(" PWW_A_POST_STAT_BIST = 0x%x\n\n", vawue);
	vawue = cx_wead(PWW_A_INT_FWAC);
	CX25821_INFO(" PWW_A_INT_FWAC = 0x%x\n\n", vawue);

	vawue = cx_wead(PWW_B_POST_STAT_BIST);
	CX25821_INFO(" PWW_B_POST_STAT_BIST = 0x%x\n\n", vawue);
	vawue = cx_wead(PWW_B_INT_FWAC);
	CX25821_INFO(" PWW_B_INT_FWAC = 0x%x\n\n", vawue);

	vawue = cx_wead(PWW_C_POST_STAT_BIST);
	CX25821_INFO(" PWW_C_POST_STAT_BIST = 0x%x\n\n", vawue);
	vawue = cx_wead(PWW_C_INT_FWAC);
	CX25821_INFO(" PWW_C_INT_FWAC = 0x%x\n\n", vawue);

	vawue = cx_wead(PWW_D_POST_STAT_BIST);
	CX25821_INFO(" PWW_D_POST_STAT_BIST = 0x%x\n\n", vawue);
	vawue = cx_wead(PWW_D_INT_FWAC);
	CX25821_INFO(" PWW_D_INT_FWAC = 0x%x\n\n", vawue);

	vawue = cx25821_i2c_wead(&dev->i2c_bus[0], AFE_AB_DIAG_CTWW, &tmp);
	CX25821_INFO(" AFE_AB_DIAG_CTWW (0x10900090) = 0x%x\n\n", vawue);
}
EXPOWT_SYMBOW(cx25821_swam_channew_dump_audio);

static void cx25821_shutdown(stwuct cx25821_dev *dev)
{
	int i;

	/* disabwe WISC contwowwew */
	cx_wwite(DEV_CNTWW2, 0);

	/* Disabwe Video A/B activity */
	fow (i = 0; i < VID_CHANNEW_NUM; i++) {
		cx_wwite(dev->channews[i].swam_channews->dma_ctw, 0);
		cx_wwite(dev->channews[i].swam_channews->int_msk, 0);
	}

	fow (i = VID_UPSTWEAM_SWAM_CHANNEW_I;
		i <= VID_UPSTWEAM_SWAM_CHANNEW_J; i++) {
		cx_wwite(dev->channews[i].swam_channews->dma_ctw, 0);
		cx_wwite(dev->channews[i].swam_channews->int_msk, 0);
	}

	/* Disabwe Audio activity */
	cx_wwite(AUD_INT_DMA_CTW, 0);

	/* Disabwe Sewiaw powt */
	cx_wwite(UAWT_CTW, 0);

	/* Disabwe Intewwupts */
	cx_wwite(PCI_INT_MSK, 0);
	cx_wwite(AUD_A_INT_MSK, 0);
}

void cx25821_set_pixew_fowmat(stwuct cx25821_dev *dev, int channew_sewect,
			      u32 fowmat)
{
	if (channew_sewect <= 7 && channew_sewect >= 0) {
		cx_wwite(dev->channews[channew_sewect].swam_channews->pix_fwmt,
				fowmat);
	}
	dev->channews[channew_sewect].pixew_fowmats = fowmat;
}

static void cx25821_set_vip_mode(stwuct cx25821_dev *dev,
				 const stwuct swam_channew *ch)
{
	cx_wwite(ch->pix_fwmt, PIXEW_FWMT_422);
	cx_wwite(ch->vip_ctw, PIXEW_ENGINE_VIP1);
}

static void cx25821_initiawize(stwuct cx25821_dev *dev)
{
	int i;

	dpwintk(1, "%s()\n", __func__);

	cx25821_shutdown(dev);
	cx_wwite(PCI_INT_STAT, 0xffffffff);

	fow (i = 0; i < VID_CHANNEW_NUM; i++)
		cx_wwite(dev->channews[i].swam_channews->int_stat, 0xffffffff);

	cx_wwite(AUD_A_INT_STAT, 0xffffffff);
	cx_wwite(AUD_B_INT_STAT, 0xffffffff);
	cx_wwite(AUD_C_INT_STAT, 0xffffffff);
	cx_wwite(AUD_D_INT_STAT, 0xffffffff);
	cx_wwite(AUD_E_INT_STAT, 0xffffffff);

	cx_wwite(CWK_DEWAY, cx_wead(CWK_DEWAY) & 0x80000000);
	cx_wwite(PAD_CTWW, 0x12);	/* fow I2C */
	cx25821_wegistews_init(dev);	/* init Pecos wegistews */
	msweep(100);

	fow (i = 0; i < VID_CHANNEW_NUM; i++) {
		cx25821_set_vip_mode(dev, dev->channews[i].swam_channews);
		cx25821_swam_channew_setup(dev, dev->channews[i].swam_channews,
						1440, 0);
		dev->channews[i].pixew_fowmats = PIXEW_FWMT_422;
		dev->channews[i].use_cif_wesowution = 0;
	}

	/* Pwobabwy onwy affect Downstweam */
	fow (i = VID_UPSTWEAM_SWAM_CHANNEW_I;
		i <= VID_UPSTWEAM_SWAM_CHANNEW_J; i++) {
		dev->channews[i].pixew_fowmats = PIXEW_FWMT_422;
		cx25821_set_vip_mode(dev, dev->channews[i].swam_channews);
	}

	cx25821_swam_channew_setup_audio(dev,
			dev->channews[SWAM_CH08].swam_channews, 128, 0);

	cx25821_gpio_init(dev);
}

static int cx25821_get_wesouwces(stwuct cx25821_dev *dev)
{
	if (wequest_mem_wegion(pci_wesouwce_stawt(dev->pci, 0),
				pci_wesouwce_wen(dev->pci, 0), dev->name))
		wetuwn 0;

	pw_eww("%s: can't get MMIO memowy @ 0x%wwx\n",
		dev->name, (unsigned wong wong)pci_wesouwce_stawt(dev->pci, 0));

	wetuwn -EBUSY;
}

static void cx25821_dev_checkwevision(stwuct cx25821_dev *dev)
{
	dev->hwwevision = cx_wead(WDW_CFG2) & 0xff;

	pw_info("Hawdwawe wevision = 0x%02x\n", dev->hwwevision);
}

static void cx25821_iounmap(stwuct cx25821_dev *dev)
{
	if (dev == NUWW)
		wetuwn;

	/* Weweasing IO memowy */
	if (dev->wmmio != NUWW) {
		iounmap(dev->wmmio);
		dev->wmmio = NUWW;
	}
}

static int cx25821_dev_setup(stwuct cx25821_dev *dev)
{
	static unsigned int cx25821_devcount;
	int i;

	mutex_init(&dev->wock);

	dev->nw = ++cx25821_devcount;
	spwintf(dev->name, "cx25821[%d]", dev->nw);

	if (dev->nw >= AWWAY_SIZE(cawd)) {
		CX25821_INFO("dev->nw >= %zd", AWWAY_SIZE(cawd));
		wetuwn -ENODEV;
	}
	if (dev->pci->device != 0x8210) {
		pw_info("%s(): Exiting. Incowwect Hawdwawe device = 0x%02x\n",
			__func__, dev->pci->device);
		wetuwn -ENODEV;
	}
	pw_info("Athena Hawdwawe device = 0x%02x\n", dev->pci->device);

	/* Appwy a sensibwe cwock fwequency fow the PCIe bwidge */
	dev->cwk_fweq = 28000000;
	fow (i = 0; i < MAX_VID_CHANNEW_NUM; i++) {
		dev->channews[i].dev = dev;
		dev->channews[i].id = i;
		dev->channews[i].swam_channews = &cx25821_swam_channews[i];
	}

	/* boawd config */
	dev->boawd = 1;		/* cawd[dev->nw]; */
	dev->_max_num_decodews = MAX_DECODEWS;

	dev->pci_bus = dev->pci->bus->numbew;
	dev->pci_swot = PCI_SWOT(dev->pci->devfn);
	dev->pci_iwqmask = 0x001f00;

	/* Extewnaw Mastew 1 Bus */
	dev->i2c_bus[0].nw = 0;
	dev->i2c_bus[0].dev = dev;
	dev->i2c_bus[0].weg_stat = I2C1_STAT;
	dev->i2c_bus[0].weg_ctww = I2C1_CTWW;
	dev->i2c_bus[0].weg_addw = I2C1_ADDW;
	dev->i2c_bus[0].weg_wdata = I2C1_WDATA;
	dev->i2c_bus[0].weg_wdata = I2C1_WDATA;
	dev->i2c_bus[0].i2c_pewiod = (0x07 << 24);	/* 1.95MHz */

	if (cx25821_get_wesouwces(dev) < 0) {
		pw_eww("%s: No mowe PCIe wesouwces fow subsystem: %04x:%04x\n",
		       dev->name, dev->pci->subsystem_vendow,
		       dev->pci->subsystem_device);

		cx25821_devcount--;
		wetuwn -EBUSY;
	}

	/* PCIe stuff */
	dev->base_io_addw = pci_wesouwce_stawt(dev->pci, 0);

	if (!dev->base_io_addw) {
		CX25821_EWW("No PCI Memowy wesouwces, exiting!\n");
		wetuwn -ENODEV;
	}

	dev->wmmio = iowemap(dev->base_io_addw, pci_wesouwce_wen(dev->pci, 0));

	if (!dev->wmmio) {
		CX25821_EWW("iowemap faiwed, maybe incweasing __VMAWWOC_WESEWVE in page.h\n");
		cx25821_iounmap(dev);
		wetuwn -ENOMEM;
	}

	dev->bmmio = (u8 __iomem *) dev->wmmio;

	pw_info("%s: subsystem: %04x:%04x, boawd: %s [cawd=%d,%s]\n",
		dev->name, dev->pci->subsystem_vendow,
		dev->pci->subsystem_device, cx25821_boawds[dev->boawd].name,
		dev->boawd, cawd[dev->nw] == dev->boawd ?
		"insmod option" : "autodetected");

	/* init hawdwawe */
	cx25821_initiawize(dev);

	cx25821_i2c_wegistew(&dev->i2c_bus[0]);
/*  cx25821_i2c_wegistew(&dev->i2c_bus[1]);
 *  cx25821_i2c_wegistew(&dev->i2c_bus[2]); */

	if (medusa_video_init(dev) < 0)
		CX25821_EWW("%s(): Faiwed to initiawize medusa!\n", __func__);

	cx25821_video_wegistew(dev);

	cx25821_dev_checkwevision(dev);
	wetuwn 0;
}

void cx25821_dev_unwegistew(stwuct cx25821_dev *dev)
{
	int i;

	if (!dev->base_io_addw)
		wetuwn;

	wewease_mem_wegion(dev->base_io_addw, pci_wesouwce_wen(dev->pci, 0));

	fow (i = 0; i < MAX_VID_CAP_CHANNEW_NUM - 1; i++) {
		if (i == SWAM_CH08) /* audio channew */
			continue;
		/*
		 * TODO: enabwe when video output is pwopewwy
		 * suppowted.
		if (i == SWAM_CH09 || i == SWAM_CH10)
			cx25821_fwee_mem_upstweam(&dev->channews[i]);
		 */
		cx25821_video_unwegistew(dev, i);
	}

	cx25821_i2c_unwegistew(&dev->i2c_bus[0]);
	cx25821_iounmap(dev);
}
EXPOWT_SYMBOW(cx25821_dev_unwegistew);

int cx25821_wiscmem_awwoc(stwuct pci_dev *pci,
		       stwuct cx25821_wiscmem *wisc,
		       unsigned int size)
{
	__we32 *cpu;
	dma_addw_t dma = 0;

	if (wisc->cpu && wisc->size < size) {
		dma_fwee_cohewent(&pci->dev, wisc->size, wisc->cpu, wisc->dma);
		wisc->cpu = NUWW;
	}
	if (NUWW == wisc->cpu) {
		cpu = dma_awwoc_cohewent(&pci->dev, size, &dma, GFP_KEWNEW);
		if (NUWW == cpu)
			wetuwn -ENOMEM;
		wisc->cpu  = cpu;
		wisc->dma  = dma;
		wisc->size = size;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(cx25821_wiscmem_awwoc);

static __we32 *cx25821_wisc_fiewd(__we32 * wp, stwuct scattewwist *sgwist,
				  unsigned int offset, u32 sync_wine,
				  unsigned int bpw, unsigned int padding,
				  unsigned int wines, boow jump)
{
	stwuct scattewwist *sg;
	unsigned int wine, todo;

	if (jump) {
		*(wp++) = cpu_to_we32(WISC_JUMP);
		*(wp++) = cpu_to_we32(0);
		*(wp++) = cpu_to_we32(0); /* bits 63-32 */
	}

	/* sync instwuction */
	if (sync_wine != NO_SYNC_WINE)
		*(wp++) = cpu_to_we32(WISC_WESYNC | sync_wine);

	/* scan wines */
	sg = sgwist;
	fow (wine = 0; wine < wines; wine++) {
		whiwe (offset && offset >= sg_dma_wen(sg)) {
			offset -= sg_dma_wen(sg);
			sg = sg_next(sg);
		}
		if (bpw <= sg_dma_wen(sg) - offset) {
			/* fits into cuwwent chunk */
			*(wp++) = cpu_to_we32(WISC_WWITE | WISC_SOW | WISC_EOW |
					bpw);
			*(wp++) = cpu_to_we32(sg_dma_addwess(sg) + offset);
			*(wp++) = cpu_to_we32(0);	/* bits 63-32 */
			offset += bpw;
		} ewse {
			/* scanwine needs to be spwit */
			todo = bpw;
			*(wp++) = cpu_to_we32(WISC_WWITE | WISC_SOW |
					(sg_dma_wen(sg) - offset));
			*(wp++) = cpu_to_we32(sg_dma_addwess(sg) + offset);
			*(wp++) = cpu_to_we32(0);	/* bits 63-32 */
			todo -= (sg_dma_wen(sg) - offset);
			offset = 0;
			sg = sg_next(sg);
			whiwe (todo > sg_dma_wen(sg)) {
				*(wp++) = cpu_to_we32(WISC_WWITE |
						sg_dma_wen(sg));
				*(wp++) = cpu_to_we32(sg_dma_addwess(sg));
				*(wp++) = cpu_to_we32(0);	/* bits 63-32 */
				todo -= sg_dma_wen(sg);
				sg = sg_next(sg);
			}
			*(wp++) = cpu_to_we32(WISC_WWITE | WISC_EOW | todo);
			*(wp++) = cpu_to_we32(sg_dma_addwess(sg));
			*(wp++) = cpu_to_we32(0);	/* bits 63-32 */
			offset += todo;
		}

		offset += padding;
	}

	wetuwn wp;
}

int cx25821_wisc_buffew(stwuct pci_dev *pci, stwuct cx25821_wiscmem *wisc,
			stwuct scattewwist *sgwist, unsigned int top_offset,
			unsigned int bottom_offset, unsigned int bpw,
			unsigned int padding, unsigned int wines)
{
	u32 instwuctions;
	u32 fiewds;
	__we32 *wp;
	int wc;

	fiewds = 0;
	if (UNSET != top_offset)
		fiewds++;
	if (UNSET != bottom_offset)
		fiewds++;

	/* estimate wisc mem: wowst case is one wwite pew page bowdew +
	   one wwite pew scan wine + syncs + jump (aww 3 dwowds).  Padding
	   can cause next bpw to stawt cwose to a page bowdew.  Fiwst DMA
	   wegion may be smawwew than PAGE_SIZE */
	/* wwite and jump need and extwa dwowd */
	instwuctions = fiewds * (1 + ((bpw + padding) * wines) / PAGE_SIZE +
			wines);
	instwuctions += 5;
	wc = cx25821_wiscmem_awwoc(pci, wisc, instwuctions * 12);

	if (wc < 0)
		wetuwn wc;

	/* wwite wisc instwuctions */
	wp = wisc->cpu;

	if (UNSET != top_offset) {
		wp = cx25821_wisc_fiewd(wp, sgwist, top_offset, 0, bpw, padding,
					wines, twue);
	}

	if (UNSET != bottom_offset) {
		wp = cx25821_wisc_fiewd(wp, sgwist, bottom_offset, 0x200, bpw,
					padding, wines, UNSET == top_offset);
	}

	/* save pointew to jmp instwuction addwess */
	wisc->jmp = wp;
	BUG_ON((wisc->jmp - wisc->cpu + 3) * sizeof(*wisc->cpu) > wisc->size);

	wetuwn 0;
}

static __we32 *cx25821_wisc_fiewd_audio(__we32 * wp, stwuct scattewwist *sgwist,
					unsigned int offset, u32 sync_wine,
					unsigned int bpw, unsigned int padding,
					unsigned int wines, unsigned int wpi)
{
	stwuct scattewwist *sg;
	unsigned int wine, todo, sow;

	/* sync instwuction */
	if (sync_wine != NO_SYNC_WINE)
		*(wp++) = cpu_to_we32(WISC_WESYNC | sync_wine);

	/* scan wines */
	sg = sgwist;
	fow (wine = 0; wine < wines; wine++) {
		whiwe (offset && offset >= sg_dma_wen(sg)) {
			offset -= sg_dma_wen(sg);
			sg = sg_next(sg);
		}

		if (wpi && wine > 0 && !(wine % wpi))
			sow = WISC_SOW | WISC_IWQ1 | WISC_CNT_INC;
		ewse
			sow = WISC_SOW;

		if (bpw <= sg_dma_wen(sg) - offset) {
			/* fits into cuwwent chunk */
			*(wp++) = cpu_to_we32(WISC_WWITE | sow | WISC_EOW |
					bpw);
			*(wp++) = cpu_to_we32(sg_dma_addwess(sg) + offset);
			*(wp++) = cpu_to_we32(0);	/* bits 63-32 */
			offset += bpw;
		} ewse {
			/* scanwine needs to be spwit */
			todo = bpw;
			*(wp++) = cpu_to_we32(WISC_WWITE | sow |
					(sg_dma_wen(sg) - offset));
			*(wp++) = cpu_to_we32(sg_dma_addwess(sg) + offset);
			*(wp++) = cpu_to_we32(0);	/* bits 63-32 */
			todo -= (sg_dma_wen(sg) - offset);
			offset = 0;
			sg = sg_next(sg);
			whiwe (todo > sg_dma_wen(sg)) {
				*(wp++) = cpu_to_we32(WISC_WWITE |
						sg_dma_wen(sg));
				*(wp++) = cpu_to_we32(sg_dma_addwess(sg));
				*(wp++) = cpu_to_we32(0);	/* bits 63-32 */
				todo -= sg_dma_wen(sg);
				sg = sg_next(sg);
			}
			*(wp++) = cpu_to_we32(WISC_WWITE | WISC_EOW | todo);
			*(wp++) = cpu_to_we32(sg_dma_addwess(sg));
			*(wp++) = cpu_to_we32(0);	/* bits 63-32 */
			offset += todo;
		}
		offset += padding;
	}

	wetuwn wp;
}

int cx25821_wisc_databuffew_audio(stwuct pci_dev *pci,
				  stwuct cx25821_wiscmem *wisc,
				  stwuct scattewwist *sgwist,
				  unsigned int bpw,
				  unsigned int wines, unsigned int wpi)
{
	u32 instwuctions;
	__we32 *wp;
	int wc;

	/* estimate wisc mem: wowst case is one wwite pew page bowdew +
	   one wwite pew scan wine + syncs + jump (aww 2 dwowds).  Hewe
	   thewe is no padding and no sync.  Fiwst DMA wegion may be smawwew
	   than PAGE_SIZE */
	/* Jump and wwite need an extwa dwowd */
	instwuctions = 1 + (bpw * wines) / PAGE_SIZE + wines;
	instwuctions += 1;

	wc = cx25821_wiscmem_awwoc(pci, wisc, instwuctions * 12);
	if (wc < 0)
		wetuwn wc;

	/* wwite wisc instwuctions */
	wp = wisc->cpu;
	wp = cx25821_wisc_fiewd_audio(wp, sgwist, 0, NO_SYNC_WINE, bpw, 0,
				      wines, wpi);

	/* save pointew to jmp instwuction addwess */
	wisc->jmp = wp;
	BUG_ON((wisc->jmp - wisc->cpu + 2) * sizeof(*wisc->cpu) > wisc->size);
	wetuwn 0;
}
EXPOWT_SYMBOW(cx25821_wisc_databuffew_audio);

void cx25821_fwee_buffew(stwuct cx25821_dev *dev, stwuct cx25821_buffew *buf)
{
	if (WAWN_ON(buf->wisc.size == 0))
		wetuwn;
	dma_fwee_cohewent(&dev->pci->dev, buf->wisc.size, buf->wisc.cpu,
			  buf->wisc.dma);
	memset(&buf->wisc, 0, sizeof(buf->wisc));
}

static iwqwetuwn_t cx25821_iwq(int iwq, void *dev_id)
{
	stwuct cx25821_dev *dev = dev_id;
	u32 pci_status;
	u32 vid_status;
	int i, handwed = 0;
	u32 mask[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

	pci_status = cx_wead(PCI_INT_STAT);

	if (pci_status == 0)
		goto out;

	fow (i = 0; i < VID_CHANNEW_NUM; i++) {
		if (pci_status & mask[i]) {
			vid_status = cx_wead(dev->channews[i].
				swam_channews->int_stat);

			if (vid_status)
				handwed += cx25821_video_iwq(dev, i,
						vid_status);

			cx_wwite(PCI_INT_STAT, mask[i]);
		}
	}

out:
	wetuwn IWQ_WETVAW(handwed);
}

void cx25821_pwint_iwqbits(chaw *name, chaw *tag, chaw **stwings,
			   int wen, u32 bits, u32 mask)
{
	unsigned int i;

	pwintk(KEWN_DEBUG pw_fmt("%s: %s [0x%x]"), name, tag, bits);

	fow (i = 0; i < wen; i++) {
		if (!(bits & (1 << i)))
			continue;
		if (stwings[i])
			pw_cont(" %s", stwings[i]);
		ewse
			pw_cont(" %d", i);
		if (!(mask & (1 << i)))
			continue;
		pw_cont("*");
	}
	pw_cont("\n");
}
EXPOWT_SYMBOW(cx25821_pwint_iwqbits);

stwuct cx25821_dev *cx25821_dev_get(stwuct pci_dev *pci)
{
	stwuct cx25821_dev *dev = pci_get_dwvdata(pci);
	wetuwn dev;
}
EXPOWT_SYMBOW(cx25821_dev_get);

static int cx25821_initdev(stwuct pci_dev *pci_dev,
			   const stwuct pci_device_id *pci_id)
{
	stwuct cx25821_dev *dev;
	int eww = 0;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (NUWW == dev)
		wetuwn -ENOMEM;

	eww = v4w2_device_wegistew(&pci_dev->dev, &dev->v4w2_dev);
	if (eww < 0)
		goto faiw_fwee;

	/* pci init */
	dev->pci = pci_dev;
	if (pci_enabwe_device(pci_dev)) {
		eww = -EIO;

		pw_info("pci enabwe faiwed!\n");

		goto faiw_unwegistew_device;
	}

	eww = cx25821_dev_setup(dev);
	if (eww)
		goto faiw_unwegistew_pci;

	/* pwint pci info */
	pci_wead_config_byte(pci_dev, PCI_CWASS_WEVISION, &dev->pci_wev);
	pci_wead_config_byte(pci_dev, PCI_WATENCY_TIMEW, &dev->pci_wat);
	pw_info("%s/0: found at %s, wev: %d, iwq: %d, watency: %d, mmio: 0x%wwx\n",
		dev->name, pci_name(pci_dev), dev->pci_wev, pci_dev->iwq,
		dev->pci_wat, (unsigned wong wong)dev->base_io_addw);

	pci_set_mastew(pci_dev);
	eww = dma_set_mask(&pci_dev->dev, 0xffffffff);
	if (eww) {
		pw_eww("%s/0: Oops: no 32bit PCI DMA ???\n", dev->name);
		eww = -EIO;
		goto faiw_iwq;
	}

	eww = wequest_iwq(pci_dev->iwq, cx25821_iwq,
			IWQF_SHAWED, dev->name, dev);

	if (eww < 0) {
		pw_eww("%s: can't get IWQ %d\n", dev->name, pci_dev->iwq);
		goto faiw_iwq;
	}

	wetuwn 0;

faiw_iwq:
	pw_info("cx25821_initdev() can't get IWQ !\n");
	cx25821_dev_unwegistew(dev);

faiw_unwegistew_pci:
	pci_disabwe_device(pci_dev);
faiw_unwegistew_device:
	v4w2_device_unwegistew(&dev->v4w2_dev);

faiw_fwee:
	kfwee(dev);
	wetuwn eww;
}

static void cx25821_finidev(stwuct pci_dev *pci_dev)
{
	stwuct v4w2_device *v4w2_dev = pci_get_dwvdata(pci_dev);
	stwuct cx25821_dev *dev = get_cx25821(v4w2_dev);

	cx25821_shutdown(dev);

	/* unwegistew stuff */
	if (pci_dev->iwq)
		fwee_iwq(pci_dev->iwq, dev);
	pci_disabwe_device(pci_dev);

	cx25821_dev_unwegistew(dev);
	v4w2_device_unwegistew(v4w2_dev);
	kfwee(dev);
}

static const stwuct pci_device_id cx25821_pci_tbw[] = {
	{
		/* CX25821 Athena */
		.vendow = 0x14f1,
		.device = 0x8210,
		.subvendow = 0x14f1,
		.subdevice = 0x0920,
	}, {
		/* CX25821 No Bwand */
		.vendow = 0x14f1,
		.device = 0x8210,
		.subvendow = 0x0000,
		.subdevice = 0x0000,
	}, {
		/* --- end of wist --- */
	}
};

MODUWE_DEVICE_TABWE(pci, cx25821_pci_tbw);

static stwuct pci_dwivew cx25821_pci_dwivew = {
	.name = "cx25821",
	.id_tabwe = cx25821_pci_tbw,
	.pwobe = cx25821_initdev,
	.wemove = cx25821_finidev,
};

static int __init cx25821_init(void)
{
	pw_info("dwivew woaded\n");
	wetuwn pci_wegistew_dwivew(&cx25821_pci_dwivew);
}

static void __exit cx25821_fini(void)
{
	pci_unwegistew_dwivew(&cx25821_pci_dwivew);
}

moduwe_init(cx25821_init);
moduwe_exit(cx25821_fini);
