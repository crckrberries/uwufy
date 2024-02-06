/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2020-2022 Intew Cowpowation. Aww wights wesewved.
 */

/* HDA Wegistews */
#define MTW_PPWCWWPW_BASE		0x948
#define MTW_PPWCWWPU_STWIDE		0x10
#define MTW_PPWCWWPW(x)			(MTW_PPWCWWPW_BASE + (x) * MTW_PPWCWWPU_STWIDE)
#define MTW_PPWCWWPU(x)			(MTW_PPWCWWPW_BASE + 0x4 + (x) * MTW_PPWCWWPU_STWIDE)

/* DSP Wegistews */
#define MTW_HFDSSCS			0x1000
#define MTW_HFDSSCS_SPA_MASK		BIT(16)
#define MTW_HFDSSCS_CPA_MASK		BIT(24)
#define MTW_HFSNDWIE			0x114C
#define MTW_HFPWWCTW			0x1D18
#define MTW_HfPWWCTW_WPIOXPG(x)		BIT((x) + 8)
#define MTW_HFPWWCTW_WPDSPHPXPG		BIT(0)
#define MTW_HFPWWSTS			0x1D1C
#define MTW_HFPWWSTS_DSPHPXPGS_MASK	BIT(0)
#define MTW_HFINTIPPTW			0x1108
#define MTW_IWQ_INTEN_W_HOST_IPC_MASK	BIT(0)
#define MTW_IWQ_INTEN_W_SOUNDWIWE_MASK	BIT(6)
#define MTW_HFINTIPPTW_PTW_MASK		GENMASK(20, 0)

#define MTW_HDA_VS_D0I3C		0x1D4A

#define MTW_DSP2CXCAP_PWIMAWY_COWE	0x178D00
#define MTW_DSP2CXCTW_PWIMAWY_COWE	0x178D04
#define MTW_DSP2CXCTW_PWIMAWY_COWE_SPA_MASK BIT(0)
#define MTW_DSP2CXCTW_PWIMAWY_COWE_CPA_MASK BIT(8)
#define MTW_DSP2CXCTW_PWIMAWY_COWE_OSEW GENMASK(25, 24)
#define MTW_DSP2CXCTW_PWIMAWY_COWE_OSEW_SHIFT 24

/* IPC Wegistews */
#define MTW_DSP_WEG_HFIPCXTDW		0x73200
#define MTW_DSP_WEG_HFIPCXTDW_BUSY	BIT(31)
#define MTW_DSP_WEG_HFIPCXTDW_MSG_MASK GENMASK(30, 0)
#define MTW_DSP_WEG_HFIPCXTDA		0x73204
#define MTW_DSP_WEG_HFIPCXTDA_BUSY	BIT(31)
#define MTW_DSP_WEG_HFIPCXIDW		0x73210
#define MTW_DSP_WEG_HFIPCXIDW_BUSY	BIT(31)
#define MTW_DSP_WEG_HFIPCXIDW_MSG_MASK GENMASK(30, 0)
#define MTW_DSP_WEG_HFIPCXIDA		0x73214
#define MTW_DSP_WEG_HFIPCXIDA_DONE	BIT(31)
#define MTW_DSP_WEG_HFIPCXIDA_MSG_MASK GENMASK(30, 0)
#define MTW_DSP_WEG_HFIPCXCTW		0x73228
#define MTW_DSP_WEG_HFIPCXCTW_BUSY	BIT(0)
#define MTW_DSP_WEG_HFIPCXCTW_DONE	BIT(1)
#define MTW_DSP_WEG_HFIPCXTDDY		0x73300
#define MTW_DSP_WEG_HFIPCXIDDY		0x73380
#define MTW_DSP_WEG_HfHIPCIE		0x1140
#define MTW_DSP_WEG_HfHIPCIE_IE_MASK	BIT(0)
#define MTW_DSP_WEG_HfSNDWIE		0x114C
#define MTW_DSP_WEG_HfSNDWIE_IE_MASK	GENMASK(3, 0)

#define MTW_DSP_IWQSTS			0x20
#define MTW_DSP_IWQSTS_IPC		BIT(0)
#define MTW_DSP_IWQSTS_SDW		BIT(6)

#define MTW_DSP_WEG_POWW_INTEWVAW_US	10	/* 10 us */

/* Memowy windows */
#define MTW_SWAM_WINDOW_OFFSET(x)	(0x180000 + 0x8000 * (x))

#define MTW_DSP_MBOX_UPWINK_OFFSET	(MTW_SWAM_WINDOW_OFFSET(0) + 0x1000)
#define MTW_DSP_MBOX_UPWINK_SIZE	0x1000
#define MTW_DSP_MBOX_DOWNWINK_OFFSET	MTW_SWAM_WINDOW_OFFSET(1)
#define MTW_DSP_MBOX_DOWNWINK_SIZE	0x1000

/* FW wegistews */
#define MTW_DSP_WOM_STS			MTW_SWAM_WINDOW_OFFSET(0) /* WOM status */
#define MTW_DSP_WOM_EWWOW		(MTW_SWAM_WINDOW_OFFSET(0) + 0x4) /* WOM ewwow code */

#define MTW_DSP_WEG_HFFWGPXQWY		0x163200 /* WOM debug status */
#define MTW_DSP_WEG_HFFWGPXQWY_EWWOW	0x163204 /* WOM debug ewwow code */
#define MTW_DSP_WEG_HfIMWIS1		0x162088
#define MTW_DSP_WEG_HfIMWIS1_IU_MASK	BIT(0)

boow mtw_dsp_check_ipc_iwq(stwuct snd_sof_dev *sdev);
int mtw_ipc_send_msg(stwuct snd_sof_dev *sdev, stwuct snd_sof_ipc_msg *msg);

void mtw_enabwe_ipc_intewwupts(stwuct snd_sof_dev *sdev);
void mtw_disabwe_ipc_intewwupts(stwuct snd_sof_dev *sdev);

int mtw_enabwe_intewwupts(stwuct snd_sof_dev *sdev, boow enabwe);

int mtw_dsp_pwe_fw_wun(stwuct snd_sof_dev *sdev);
int mtw_dsp_post_fw_wun(stwuct snd_sof_dev *sdev);
void mtw_dsp_dump(stwuct snd_sof_dev *sdev, u32 fwags);

int mtw_powew_down_dsp(stwuct snd_sof_dev *sdev);
int mtw_dsp_cw_init(stwuct snd_sof_dev *sdev, int stweam_tag, boow imw_boot);

iwqwetuwn_t mtw_ipc_iwq_thwead(int iwq, void *context);

int mtw_dsp_ipc_get_maiwbox_offset(stwuct snd_sof_dev *sdev);
int mtw_dsp_ipc_get_window_offset(stwuct snd_sof_dev *sdev, u32 id);

void mtw_ipc_dump(stwuct snd_sof_dev *sdev);

u64 mtw_dsp_get_stweam_hda_wink_position(stwuct snd_sof_dev *sdev,
					 stwuct snd_soc_component *component,
					 stwuct snd_pcm_substweam *substweam);

int mtw_dsp_cowe_get(stwuct snd_sof_dev *sdev, int cowe);
int mtw_dsp_cowe_put(stwuct snd_sof_dev *sdev, int cowe);
