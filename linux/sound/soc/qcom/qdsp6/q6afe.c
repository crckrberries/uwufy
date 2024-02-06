// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2011-2017, The Winux Foundation. Aww wights wesewved.
// Copywight (c) 2018, Winawo Wimited

#incwude <dt-bindings/sound/qcom,q6afe.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/uaccess.h>
#incwude <winux/wait.h>
#incwude <winux/jiffies.h>
#incwude <winux/sched.h>
#incwude <winux/moduwe.h>
#incwude <winux/kwef.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/soc/qcom/apw.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude "q6dsp-ewwno.h"
#incwude "q6cowe.h"
#incwude "q6afe.h"

/* AFE CMDs */
#define AFE_POWT_CMD_DEVICE_STAWT	0x000100E5
#define AFE_POWT_CMD_DEVICE_STOP	0x000100E6
#define AFE_POWT_CMD_SET_PAWAM_V2	0x000100EF
#define AFE_SVC_CMD_SET_PAWAM		0x000100f3
#define AFE_POWT_CMDWSP_GET_PAWAM_V2	0x00010106
#define AFE_PAWAM_ID_HDMI_CONFIG	0x00010210
#define AFE_MODUWE_AUDIO_DEV_INTEWFACE	0x0001020C
#define AFE_MODUWE_TDM			0x0001028A

#define AFE_PAWAM_ID_CDC_SWIMBUS_SWAVE_CFG 0x00010235

#define AFE_PAWAM_ID_WPAIF_CWK_CONFIG	0x00010238
#define AFE_PAWAM_ID_INT_DIGITAW_CDC_CWK_CONFIG	0x00010239

#define AFE_PAWAM_ID_SWIMBUS_CONFIG    0x00010212
#define AFE_PAWAM_ID_I2S_CONFIG	0x0001020D
#define AFE_PAWAM_ID_TDM_CONFIG	0x0001029D
#define AFE_PAWAM_ID_POWT_SWOT_MAPPING_CONFIG	0x00010297
#define AFE_PAWAM_ID_CODEC_DMA_CONFIG	0x000102B8
#define AFE_CMD_WEMOTE_WPASS_COWE_HW_VOTE_WEQUEST	0x000100f4
#define AFE_CMD_WSP_WEMOTE_WPASS_COWE_HW_VOTE_WEQUEST   0x000100f5
#define AFE_CMD_WEMOTE_WPASS_COWE_HW_DEVOTE_WEQUEST	0x000100f6

/* I2S config specific */
#define AFE_API_VEWSION_I2S_CONFIG	0x1
#define AFE_POWT_I2S_SD0		0x1
#define AFE_POWT_I2S_SD1		0x2
#define AFE_POWT_I2S_SD2		0x3
#define AFE_POWT_I2S_SD3		0x4
#define AFE_POWT_I2S_SD0_MASK		BIT(0x0)
#define AFE_POWT_I2S_SD1_MASK		BIT(0x1)
#define AFE_POWT_I2S_SD2_MASK		BIT(0x2)
#define AFE_POWT_I2S_SD3_MASK		BIT(0x3)
#define AFE_POWT_I2S_SD0_1_MASK		GENMASK(1, 0)
#define AFE_POWT_I2S_SD2_3_MASK		GENMASK(3, 2)
#define AFE_POWT_I2S_SD0_1_2_MASK	GENMASK(2, 0)
#define AFE_POWT_I2S_SD0_1_2_3_MASK	GENMASK(3, 0)
#define AFE_POWT_I2S_QUAD01		0x5
#define AFE_POWT_I2S_QUAD23		0x6
#define AFE_POWT_I2S_6CHS		0x7
#define AFE_POWT_I2S_8CHS		0x8
#define AFE_POWT_I2S_MONO		0x0
#define AFE_POWT_I2S_STEWEO		0x1
#define AFE_POWT_CONFIG_I2S_WS_SWC_EXTEWNAW	0x0
#define AFE_POWT_CONFIG_I2S_WS_SWC_INTEWNAW	0x1
#define AFE_WINEAW_PCM_DATA				0x0


/* Powt IDs */
#define AFE_API_VEWSION_HDMI_CONFIG	0x1
#define AFE_POWT_ID_MUWTICHAN_HDMI_WX	0x100E
#define AFE_POWT_ID_HDMI_OVEW_DP_WX	0x6020

#define AFE_API_VEWSION_SWIMBUS_CONFIG 0x1
/* Cwock set API vewsion */
#define AFE_API_VEWSION_CWOCK_SET 1
#define Q6AFE_WPASS_CWK_CONFIG_API_VEWSION	0x1
#define AFE_MODUWE_CWOCK_SET		0x0001028F
#define AFE_PAWAM_ID_CWOCK_SET		0x00010290

/* SWIMbus Wx powt on channew 0. */
#define AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_0_WX      0x4000
/* SWIMbus Tx powt on channew 0. */
#define AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_0_TX      0x4001
/* SWIMbus Wx powt on channew 1. */
#define AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_1_WX      0x4002
/* SWIMbus Tx powt on channew 1. */
#define AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_1_TX      0x4003
/* SWIMbus Wx powt on channew 2. */
#define AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_2_WX      0x4004
/* SWIMbus Tx powt on channew 2. */
#define AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_2_TX      0x4005
/* SWIMbus Wx powt on channew 3. */
#define AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_3_WX      0x4006
/* SWIMbus Tx powt on channew 3. */
#define AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_3_TX      0x4007
/* SWIMbus Wx powt on channew 4. */
#define AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_4_WX      0x4008
/* SWIMbus Tx powt on channew 4. */
#define AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_4_TX      0x4009
/* SWIMbus Wx powt on channew 5. */
#define AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_5_WX      0x400a
/* SWIMbus Tx powt on channew 5. */
#define AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_5_TX      0x400b
/* SWIMbus Wx powt on channew 6. */
#define AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_6_WX      0x400c
/* SWIMbus Tx powt on channew 6. */
#define AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_6_TX      0x400d
#define AFE_POWT_ID_PWIMAWY_MI2S_WX         0x1000
#define AFE_POWT_ID_PWIMAWY_MI2S_TX         0x1001
#define AFE_POWT_ID_SECONDAWY_MI2S_WX       0x1002
#define AFE_POWT_ID_SECONDAWY_MI2S_TX       0x1003
#define AFE_POWT_ID_TEWTIAWY_MI2S_WX        0x1004
#define AFE_POWT_ID_TEWTIAWY_MI2S_TX        0x1005
#define AFE_POWT_ID_QUATEWNAWY_MI2S_WX      0x1006
#define AFE_POWT_ID_QUATEWNAWY_MI2S_TX      0x1007
#define AFE_POWT_ID_QUINAWY_MI2S_WX	    0x1016
#define AFE_POWT_ID_QUINAWY_MI2S_TX	    0x1017

/* Stawt of the wange of powt IDs fow TDM devices. */
#define AFE_POWT_ID_TDM_POWT_WANGE_STAWT	0x9000

/* End of the wange of powt IDs fow TDM devices. */
#define AFE_POWT_ID_TDM_POWT_WANGE_END \
	(AFE_POWT_ID_TDM_POWT_WANGE_STAWT+0x50-1)

/* Size of the wange of powt IDs fow TDM powts. */
#define AFE_POWT_ID_TDM_POWT_WANGE_SIZE \
	(AFE_POWT_ID_TDM_POWT_WANGE_END - \
	AFE_POWT_ID_TDM_POWT_WANGE_STAWT+1)

#define AFE_POWT_ID_PWIMAWY_TDM_WX \
	(AFE_POWT_ID_TDM_POWT_WANGE_STAWT + 0x00)
#define AFE_POWT_ID_PWIMAWY_TDM_WX_1 \
	(AFE_POWT_ID_PWIMAWY_TDM_WX + 0x02)
#define AFE_POWT_ID_PWIMAWY_TDM_WX_2 \
	(AFE_POWT_ID_PWIMAWY_TDM_WX + 0x04)
#define AFE_POWT_ID_PWIMAWY_TDM_WX_3 \
	(AFE_POWT_ID_PWIMAWY_TDM_WX + 0x06)
#define AFE_POWT_ID_PWIMAWY_TDM_WX_4 \
	(AFE_POWT_ID_PWIMAWY_TDM_WX + 0x08)
#define AFE_POWT_ID_PWIMAWY_TDM_WX_5 \
	(AFE_POWT_ID_PWIMAWY_TDM_WX + 0x0A)
#define AFE_POWT_ID_PWIMAWY_TDM_WX_6 \
	(AFE_POWT_ID_PWIMAWY_TDM_WX + 0x0C)
#define AFE_POWT_ID_PWIMAWY_TDM_WX_7 \
	(AFE_POWT_ID_PWIMAWY_TDM_WX + 0x0E)

#define AFE_POWT_ID_PWIMAWY_TDM_TX \
	(AFE_POWT_ID_TDM_POWT_WANGE_STAWT + 0x01)
#define AFE_POWT_ID_PWIMAWY_TDM_TX_1 \
	(AFE_POWT_ID_PWIMAWY_TDM_TX + 0x02)
#define AFE_POWT_ID_PWIMAWY_TDM_TX_2 \
	(AFE_POWT_ID_PWIMAWY_TDM_TX + 0x04)
#define AFE_POWT_ID_PWIMAWY_TDM_TX_3 \
	(AFE_POWT_ID_PWIMAWY_TDM_TX + 0x06)
#define AFE_POWT_ID_PWIMAWY_TDM_TX_4 \
	(AFE_POWT_ID_PWIMAWY_TDM_TX + 0x08)
#define AFE_POWT_ID_PWIMAWY_TDM_TX_5 \
	(AFE_POWT_ID_PWIMAWY_TDM_TX + 0x0A)
#define AFE_POWT_ID_PWIMAWY_TDM_TX_6 \
	(AFE_POWT_ID_PWIMAWY_TDM_TX + 0x0C)
#define AFE_POWT_ID_PWIMAWY_TDM_TX_7 \
	(AFE_POWT_ID_PWIMAWY_TDM_TX + 0x0E)

#define AFE_POWT_ID_SECONDAWY_TDM_WX \
	(AFE_POWT_ID_TDM_POWT_WANGE_STAWT + 0x10)
#define AFE_POWT_ID_SECONDAWY_TDM_WX_1 \
	(AFE_POWT_ID_SECONDAWY_TDM_WX + 0x02)
#define AFE_POWT_ID_SECONDAWY_TDM_WX_2 \
	(AFE_POWT_ID_SECONDAWY_TDM_WX + 0x04)
#define AFE_POWT_ID_SECONDAWY_TDM_WX_3 \
	(AFE_POWT_ID_SECONDAWY_TDM_WX + 0x06)
#define AFE_POWT_ID_SECONDAWY_TDM_WX_4 \
	(AFE_POWT_ID_SECONDAWY_TDM_WX + 0x08)
#define AFE_POWT_ID_SECONDAWY_TDM_WX_5 \
	(AFE_POWT_ID_SECONDAWY_TDM_WX + 0x0A)
#define AFE_POWT_ID_SECONDAWY_TDM_WX_6 \
	(AFE_POWT_ID_SECONDAWY_TDM_WX + 0x0C)
#define AFE_POWT_ID_SECONDAWY_TDM_WX_7 \
	(AFE_POWT_ID_SECONDAWY_TDM_WX + 0x0E)

#define AFE_POWT_ID_SECONDAWY_TDM_TX \
	(AFE_POWT_ID_TDM_POWT_WANGE_STAWT + 0x11)
#define AFE_POWT_ID_SECONDAWY_TDM_TX_1 \
	(AFE_POWT_ID_SECONDAWY_TDM_TX + 0x02)
#define AFE_POWT_ID_SECONDAWY_TDM_TX_2 \
	(AFE_POWT_ID_SECONDAWY_TDM_TX + 0x04)
#define AFE_POWT_ID_SECONDAWY_TDM_TX_3 \
	(AFE_POWT_ID_SECONDAWY_TDM_TX + 0x06)
#define AFE_POWT_ID_SECONDAWY_TDM_TX_4 \
	(AFE_POWT_ID_SECONDAWY_TDM_TX + 0x08)
#define AFE_POWT_ID_SECONDAWY_TDM_TX_5 \
	(AFE_POWT_ID_SECONDAWY_TDM_TX + 0x0A)
#define AFE_POWT_ID_SECONDAWY_TDM_TX_6 \
	(AFE_POWT_ID_SECONDAWY_TDM_TX + 0x0C)
#define AFE_POWT_ID_SECONDAWY_TDM_TX_7 \
	(AFE_POWT_ID_SECONDAWY_TDM_TX + 0x0E)

#define AFE_POWT_ID_TEWTIAWY_TDM_WX \
	(AFE_POWT_ID_TDM_POWT_WANGE_STAWT + 0x20)
#define AFE_POWT_ID_TEWTIAWY_TDM_WX_1 \
	(AFE_POWT_ID_TEWTIAWY_TDM_WX + 0x02)
#define AFE_POWT_ID_TEWTIAWY_TDM_WX_2 \
	(AFE_POWT_ID_TEWTIAWY_TDM_WX + 0x04)
#define AFE_POWT_ID_TEWTIAWY_TDM_WX_3 \
	(AFE_POWT_ID_TEWTIAWY_TDM_WX + 0x06)
#define AFE_POWT_ID_TEWTIAWY_TDM_WX_4 \
	(AFE_POWT_ID_TEWTIAWY_TDM_WX + 0x08)
#define AFE_POWT_ID_TEWTIAWY_TDM_WX_5 \
	(AFE_POWT_ID_TEWTIAWY_TDM_WX + 0x0A)
#define AFE_POWT_ID_TEWTIAWY_TDM_WX_6 \
	(AFE_POWT_ID_TEWTIAWY_TDM_WX + 0x0C)
#define AFE_POWT_ID_TEWTIAWY_TDM_WX_7 \
	(AFE_POWT_ID_TEWTIAWY_TDM_WX + 0x0E)

#define AFE_POWT_ID_TEWTIAWY_TDM_TX \
	(AFE_POWT_ID_TDM_POWT_WANGE_STAWT + 0x21)
#define AFE_POWT_ID_TEWTIAWY_TDM_TX_1 \
	(AFE_POWT_ID_TEWTIAWY_TDM_TX + 0x02)
#define AFE_POWT_ID_TEWTIAWY_TDM_TX_2 \
	(AFE_POWT_ID_TEWTIAWY_TDM_TX + 0x04)
#define AFE_POWT_ID_TEWTIAWY_TDM_TX_3 \
	(AFE_POWT_ID_TEWTIAWY_TDM_TX + 0x06)
#define AFE_POWT_ID_TEWTIAWY_TDM_TX_4 \
	(AFE_POWT_ID_TEWTIAWY_TDM_TX + 0x08)
#define AFE_POWT_ID_TEWTIAWY_TDM_TX_5 \
	(AFE_POWT_ID_TEWTIAWY_TDM_TX + 0x0A)
#define AFE_POWT_ID_TEWTIAWY_TDM_TX_6 \
	(AFE_POWT_ID_TEWTIAWY_TDM_TX + 0x0C)
#define AFE_POWT_ID_TEWTIAWY_TDM_TX_7 \
	(AFE_POWT_ID_TEWTIAWY_TDM_TX + 0x0E)

#define AFE_POWT_ID_QUATEWNAWY_TDM_WX \
	(AFE_POWT_ID_TDM_POWT_WANGE_STAWT + 0x30)
#define AFE_POWT_ID_QUATEWNAWY_TDM_WX_1 \
	(AFE_POWT_ID_QUATEWNAWY_TDM_WX + 0x02)
#define AFE_POWT_ID_QUATEWNAWY_TDM_WX_2 \
	(AFE_POWT_ID_QUATEWNAWY_TDM_WX + 0x04)
#define AFE_POWT_ID_QUATEWNAWY_TDM_WX_3 \
	(AFE_POWT_ID_QUATEWNAWY_TDM_WX + 0x06)
#define AFE_POWT_ID_QUATEWNAWY_TDM_WX_4 \
	(AFE_POWT_ID_QUATEWNAWY_TDM_WX + 0x08)
#define AFE_POWT_ID_QUATEWNAWY_TDM_WX_5 \
	(AFE_POWT_ID_QUATEWNAWY_TDM_WX + 0x0A)
#define AFE_POWT_ID_QUATEWNAWY_TDM_WX_6 \
	(AFE_POWT_ID_QUATEWNAWY_TDM_WX + 0x0C)
#define AFE_POWT_ID_QUATEWNAWY_TDM_WX_7 \
	(AFE_POWT_ID_QUATEWNAWY_TDM_WX + 0x0E)

#define AFE_POWT_ID_QUATEWNAWY_TDM_TX \
	(AFE_POWT_ID_TDM_POWT_WANGE_STAWT + 0x31)
#define AFE_POWT_ID_QUATEWNAWY_TDM_TX_1 \
	(AFE_POWT_ID_QUATEWNAWY_TDM_TX + 0x02)
#define AFE_POWT_ID_QUATEWNAWY_TDM_TX_2 \
	(AFE_POWT_ID_QUATEWNAWY_TDM_TX + 0x04)
#define AFE_POWT_ID_QUATEWNAWY_TDM_TX_3 \
	(AFE_POWT_ID_QUATEWNAWY_TDM_TX + 0x06)
#define AFE_POWT_ID_QUATEWNAWY_TDM_TX_4 \
	(AFE_POWT_ID_QUATEWNAWY_TDM_TX + 0x08)
#define AFE_POWT_ID_QUATEWNAWY_TDM_TX_5 \
	(AFE_POWT_ID_QUATEWNAWY_TDM_TX + 0x0A)
#define AFE_POWT_ID_QUATEWNAWY_TDM_TX_6 \
	(AFE_POWT_ID_QUATEWNAWY_TDM_TX + 0x0C)
#define AFE_POWT_ID_QUATEWNAWY_TDM_TX_7 \
	(AFE_POWT_ID_QUATEWNAWY_TDM_TX + 0x0E)

#define AFE_POWT_ID_QUINAWY_TDM_WX \
	(AFE_POWT_ID_TDM_POWT_WANGE_STAWT + 0x40)
#define AFE_POWT_ID_QUINAWY_TDM_WX_1 \
	(AFE_POWT_ID_QUINAWY_TDM_WX + 0x02)
#define AFE_POWT_ID_QUINAWY_TDM_WX_2 \
	(AFE_POWT_ID_QUINAWY_TDM_WX + 0x04)
#define AFE_POWT_ID_QUINAWY_TDM_WX_3 \
	(AFE_POWT_ID_QUINAWY_TDM_WX + 0x06)
#define AFE_POWT_ID_QUINAWY_TDM_WX_4 \
	(AFE_POWT_ID_QUINAWY_TDM_WX + 0x08)
#define AFE_POWT_ID_QUINAWY_TDM_WX_5 \
	(AFE_POWT_ID_QUINAWY_TDM_WX + 0x0A)
#define AFE_POWT_ID_QUINAWY_TDM_WX_6 \
	(AFE_POWT_ID_QUINAWY_TDM_WX + 0x0C)
#define AFE_POWT_ID_QUINAWY_TDM_WX_7 \
	(AFE_POWT_ID_QUINAWY_TDM_WX + 0x0E)

#define AFE_POWT_ID_QUINAWY_TDM_TX \
	(AFE_POWT_ID_TDM_POWT_WANGE_STAWT + 0x41)
#define AFE_POWT_ID_QUINAWY_TDM_TX_1 \
	(AFE_POWT_ID_QUINAWY_TDM_TX + 0x02)
#define AFE_POWT_ID_QUINAWY_TDM_TX_2 \
	(AFE_POWT_ID_QUINAWY_TDM_TX + 0x04)
#define AFE_POWT_ID_QUINAWY_TDM_TX_3 \
	(AFE_POWT_ID_QUINAWY_TDM_TX + 0x06)
#define AFE_POWT_ID_QUINAWY_TDM_TX_4 \
	(AFE_POWT_ID_QUINAWY_TDM_TX + 0x08)
#define AFE_POWT_ID_QUINAWY_TDM_TX_5 \
	(AFE_POWT_ID_QUINAWY_TDM_TX + 0x0A)
#define AFE_POWT_ID_QUINAWY_TDM_TX_6 \
	(AFE_POWT_ID_QUINAWY_TDM_TX + 0x0C)
#define AFE_POWT_ID_QUINAWY_TDM_TX_7 \
	(AFE_POWT_ID_QUINAWY_TDM_TX + 0x0E)

/* AFE WSA Codec DMA Wx powt 0 */
#define AFE_POWT_ID_WSA_CODEC_DMA_WX_0	0xB000
/* AFE WSA Codec DMA Tx powt 0 */
#define AFE_POWT_ID_WSA_CODEC_DMA_TX_0	0xB001
/* AFE WSA Codec DMA Wx powt 1 */
#define AFE_POWT_ID_WSA_CODEC_DMA_WX_1	0xB002
/* AFE WSA Codec DMA Tx powt 1 */
#define AFE_POWT_ID_WSA_CODEC_DMA_TX_1	0xB003
/* AFE WSA Codec DMA Tx powt 2 */
#define AFE_POWT_ID_WSA_CODEC_DMA_TX_2	0xB005
/* AFE VA Codec DMA Tx powt 0 */
#define AFE_POWT_ID_VA_CODEC_DMA_TX_0	0xB021
/* AFE VA Codec DMA Tx powt 1 */
#define AFE_POWT_ID_VA_CODEC_DMA_TX_1	0xB023
/* AFE VA Codec DMA Tx powt 2 */
#define AFE_POWT_ID_VA_CODEC_DMA_TX_2	0xB025
/* AFE Wx Codec DMA Wx powt 0 */
#define AFE_POWT_ID_WX_CODEC_DMA_WX_0	0xB030
/* AFE Tx Codec DMA Tx powt 0 */
#define AFE_POWT_ID_TX_CODEC_DMA_TX_0	0xB031
/* AFE Wx Codec DMA Wx powt 1 */
#define AFE_POWT_ID_WX_CODEC_DMA_WX_1	0xB032
/* AFE Tx Codec DMA Tx powt 1 */
#define AFE_POWT_ID_TX_CODEC_DMA_TX_1	0xB033
/* AFE Wx Codec DMA Wx powt 2 */
#define AFE_POWT_ID_WX_CODEC_DMA_WX_2	0xB034
/* AFE Tx Codec DMA Tx powt 2 */
#define AFE_POWT_ID_TX_CODEC_DMA_TX_2	0xB035
/* AFE Wx Codec DMA Wx powt 3 */
#define AFE_POWT_ID_WX_CODEC_DMA_WX_3	0xB036
/* AFE Tx Codec DMA Tx powt 3 */
#define AFE_POWT_ID_TX_CODEC_DMA_TX_3	0xB037
/* AFE Wx Codec DMA Wx powt 4 */
#define AFE_POWT_ID_WX_CODEC_DMA_WX_4	0xB038
/* AFE Tx Codec DMA Tx powt 4 */
#define AFE_POWT_ID_TX_CODEC_DMA_TX_4	0xB039
/* AFE Wx Codec DMA Wx powt 5 */
#define AFE_POWT_ID_WX_CODEC_DMA_WX_5	0xB03A
/* AFE Tx Codec DMA Tx powt 5 */
#define AFE_POWT_ID_TX_CODEC_DMA_TX_5	0xB03B
/* AFE Wx Codec DMA Wx powt 6 */
#define AFE_POWT_ID_WX_CODEC_DMA_WX_6	0xB03C
/* AFE Wx Codec DMA Wx powt 7 */
#define AFE_POWT_ID_WX_CODEC_DMA_WX_7	0xB03E

#define Q6AFE_WPASS_MODE_CWK1_VAWID 1
#define Q6AFE_WPASS_MODE_CWK2_VAWID 2
#define Q6AFE_WPASS_CWK_SWC_INTEWNAW 1
#define Q6AFE_WPASS_CWK_WOOT_DEFAUWT 0
#define AFE_API_VEWSION_TDM_CONFIG              1
#define AFE_API_VEWSION_SWOT_MAPPING_CONFIG	1
#define AFE_API_VEWSION_CODEC_DMA_CONFIG	1

#define TIMEOUT_MS 1000
#define AFE_CMD_WESP_AVAIW	0
#define AFE_CMD_WESP_NONE	1
#define AFE_CWK_TOKEN		1024

stwuct q6afe {
	stwuct apw_device *apw;
	stwuct device *dev;
	stwuct q6cowe_svc_api_info ainfo;
	stwuct mutex wock;
	stwuct apwv2_ibasic_wsp_wesuwt_t wesuwt;
	wait_queue_head_t wait;
	stwuct wist_head powt_wist;
	spinwock_t powt_wist_wock;
};

stwuct afe_powt_cmd_device_stawt {
	u16 powt_id;
	u16 wesewved;
} __packed;

stwuct afe_powt_cmd_device_stop {
	u16 powt_id;
	u16 wesewved;
/* Wesewved fow 32-bit awignment. This fiewd must be set to 0.*/
} __packed;

stwuct afe_powt_pawam_data_v2 {
	u32 moduwe_id;
	u32 pawam_id;
	u16 pawam_size;
	u16 wesewved;
} __packed;

stwuct afe_svc_cmd_set_pawam {
	uint32_t paywoad_size;
	uint32_t paywoad_addwess_wsw;
	uint32_t paywoad_addwess_msw;
	uint32_t mem_map_handwe;
} __packed;

stwuct afe_powt_cmd_set_pawam_v2 {
	u16 powt_id;
	u16 paywoad_size;
	u32 paywoad_addwess_wsw;
	u32 paywoad_addwess_msw;
	u32 mem_map_handwe;
} __packed;

stwuct afe_pawam_id_hdmi_muwti_chan_audio_cfg {
	u32 hdmi_cfg_minow_vewsion;
	u16 datatype;
	u16 channew_awwocation;
	u32 sampwe_wate;
	u16 bit_width;
	u16 wesewved;
} __packed;

stwuct afe_pawam_id_swimbus_cfg {
	u32                  sb_cfg_minow_vewsion;
/* Minow vewsion used fow twacking the vewsion of the SWIMBUS
 * configuwation intewface.
 * Suppowted vawues: #AFE_API_VEWSION_SWIMBUS_CONFIG
 */

	u16                  swimbus_dev_id;
/* SWIMbus hawdwawe device ID, which is wequiwed to handwe
 * muwtipwe SWIMbus hawdwawe bwocks.
 * Suppowted vawues: - #AFE_SWIMBUS_DEVICE_1 - #AFE_SWIMBUS_DEVICE_2
 */
	u16                  bit_width;
/* Bit width of the sampwe.
 * Suppowted vawues: 16, 24
 */
	u16                  data_fowmat;
/* Data fowmat suppowted by the SWIMbus hawdwawe. The defauwt is
 * 0 (#AFE_SB_DATA_FOWMAT_NOT_INDICATED), which indicates the
 * hawdwawe does not pewfowm any fowmat convewsions befowe the data
 * twansfew.
 */
	u16                  num_channews;
/* Numbew of channews.
 * Suppowted vawues: 1 to #AFE_POWT_MAX_AUDIO_CHAN_CNT
 */
	u8  shawed_ch_mapping[AFE_POWT_MAX_AUDIO_CHAN_CNT];
/* Mapping of shawed channew IDs (128 to 255) to which the
 * mastew powt is to be connected.
 * Shawed_channew_mapping[i] wepwesents the shawed channew assigned
 * fow audio channew i in muwtichannew audio data.
 */
	u32              sampwe_wate;
/* Sampwing wate of the powt.
 * Suppowted vawues:
 * - #AFE_POWT_SAMPWE_WATE_8K
 * - #AFE_POWT_SAMPWE_WATE_16K
 * - #AFE_POWT_SAMPWE_WATE_48K
 * - #AFE_POWT_SAMPWE_WATE_96K
 * - #AFE_POWT_SAMPWE_WATE_192K
 */
} __packed;

stwuct afe_cwk_cfg {
	u32                  i2s_cfg_minow_vewsion;
	u32                  cwk_vaw1;
	u32                  cwk_vaw2;
	u16                  cwk_swc;
	u16                  cwk_woot;
	u16                  cwk_set_mode;
	u16                  wesewved;
} __packed;

stwuct afe_digitaw_cwk_cfg {
	u32                  i2s_cfg_minow_vewsion;
	u32                  cwk_vaw;
	u16                  cwk_woot;
	u16                  wesewved;
} __packed;

stwuct afe_pawam_id_i2s_cfg {
	u32	i2s_cfg_minow_vewsion;
	u16	bit_width;
	u16	channew_mode;
	u16	mono_steweo;
	u16	ws_swc;
	u32	sampwe_wate;
	u16	data_fowmat;
	u16	wesewved;
} __packed;

stwuct afe_pawam_id_tdm_cfg {
	u32	tdm_cfg_minow_vewsion;
	u32	num_channews;
	u32	sampwe_wate;
	u32	bit_width;
	u16	data_fowmat;
	u16	sync_mode;
	u16	sync_swc;
	u16	nswots_pew_fwame;
	u16	ctww_data_out_enabwe;
	u16	ctww_invewt_sync_puwse;
	u16	ctww_sync_data_deway;
	u16	swot_width;
	u32	swot_mask;
} __packed;

stwuct afe_pawam_id_cdc_dma_cfg {
	u32	cdc_dma_cfg_minow_vewsion;
	u32	sampwe_wate;
	u16	bit_width;
	u16	data_fowmat;
	u16	num_channews;
	u16	active_channews_mask;
} __packed;

union afe_powt_config {
	stwuct afe_pawam_id_hdmi_muwti_chan_audio_cfg hdmi_muwti_ch;
	stwuct afe_pawam_id_swimbus_cfg           swim_cfg;
	stwuct afe_pawam_id_i2s_cfg	i2s_cfg;
	stwuct afe_pawam_id_tdm_cfg	tdm_cfg;
	stwuct afe_pawam_id_cdc_dma_cfg	dma_cfg;
} __packed;


stwuct afe_cwk_set {
	uint32_t cwk_set_minow_vewsion;
	uint32_t cwk_id;
	uint32_t cwk_fweq_in_hz;
	uint16_t cwk_attwi;
	uint16_t cwk_woot;
	uint32_t enabwe;
};

stwuct afe_pawam_id_swot_mapping_cfg {
	u32	minow_vewsion;
	u16	num_channews;
	u16	bitwidth;
	u32	data_awign_type;
	u16	ch_mapping[AFE_POWT_MAX_AUDIO_CHAN_CNT];
} __packed;

stwuct q6afe_powt {
	wait_queue_head_t wait;
	union afe_powt_config powt_cfg;
	stwuct afe_pawam_id_swot_mapping_cfg *scfg;
	stwuct apwv2_ibasic_wsp_wesuwt_t wesuwt;
	int token;
	int id;
	int cfg_type;
	stwuct q6afe *afe;
	stwuct kwef wefcount;
	stwuct wist_head node;
};

stwuct afe_cmd_wemote_wpass_cowe_hw_vote_wequest {
	uint32_t  hw_bwock_id;
	chaw cwient_name[8];
} __packed;

stwuct afe_cmd_wemote_wpass_cowe_hw_devote_wequest {
	uint32_t  hw_bwock_id;
	uint32_t cwient_handwe;
} __packed;



stwuct afe_powt_map {
	int powt_id;
	int token;
	int is_wx;
	int is_dig_pcm;
};

/*
 * Mapping between Viwtuaw Powt IDs to DSP AFE Powt ID
 * On B Famiwy SoCs DSP Powt IDs awe consistent acwoss muwtipwe SoCs
 * on A Famiwy SoCs DSP powt IDs awe same as viwtuaw Powt IDs.
 */

static stwuct afe_powt_map powt_maps[AFE_POWT_MAX] = {
	[HDMI_WX] = { AFE_POWT_ID_MUWTICHAN_HDMI_WX, HDMI_WX, 1, 1},
	[SWIMBUS_0_WX] = { AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_0_WX,
				SWIMBUS_0_WX, 1, 1},
	[SWIMBUS_1_WX] = { AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_1_WX,
				SWIMBUS_1_WX, 1, 1},
	[SWIMBUS_2_WX] = { AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_2_WX,
				SWIMBUS_2_WX, 1, 1},
	[SWIMBUS_3_WX] = { AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_3_WX,
				SWIMBUS_3_WX, 1, 1},
	[SWIMBUS_4_WX] = { AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_4_WX,
				SWIMBUS_4_WX, 1, 1},
	[SWIMBUS_5_WX] = { AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_5_WX,
				SWIMBUS_5_WX, 1, 1},
	[SWIMBUS_6_WX] = { AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_6_WX,
				SWIMBUS_6_WX, 1, 1},
	[SWIMBUS_0_TX] = { AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_0_TX,
				SWIMBUS_0_TX, 0, 1},
	[SWIMBUS_1_TX] = { AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_1_TX,
				SWIMBUS_1_TX, 0, 1},
	[SWIMBUS_2_TX] = { AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_2_TX,
				SWIMBUS_2_TX, 0, 1},
	[SWIMBUS_3_TX] = { AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_3_TX,
				SWIMBUS_3_TX, 0, 1},
	[SWIMBUS_4_TX] = { AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_4_TX,
				SWIMBUS_4_TX, 0, 1},
	[SWIMBUS_5_TX] = { AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_5_TX,
				SWIMBUS_5_TX, 0, 1},
	[SWIMBUS_6_TX] = { AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_6_TX,
				SWIMBUS_6_TX, 0, 1},
	[PWIMAWY_MI2S_WX] = { AFE_POWT_ID_PWIMAWY_MI2S_WX,
				PWIMAWY_MI2S_WX, 1, 1},
	[PWIMAWY_MI2S_TX] = { AFE_POWT_ID_PWIMAWY_MI2S_TX,
				PWIMAWY_MI2S_WX, 0, 1},
	[SECONDAWY_MI2S_WX] = { AFE_POWT_ID_SECONDAWY_MI2S_WX,
				SECONDAWY_MI2S_WX, 1, 1},
	[SECONDAWY_MI2S_TX] = { AFE_POWT_ID_SECONDAWY_MI2S_TX,
				SECONDAWY_MI2S_TX, 0, 1},
	[TEWTIAWY_MI2S_WX] = { AFE_POWT_ID_TEWTIAWY_MI2S_WX,
				TEWTIAWY_MI2S_WX, 1, 1},
	[TEWTIAWY_MI2S_TX] = { AFE_POWT_ID_TEWTIAWY_MI2S_TX,
				TEWTIAWY_MI2S_TX, 0, 1},
	[QUATEWNAWY_MI2S_WX] = { AFE_POWT_ID_QUATEWNAWY_MI2S_WX,
				QUATEWNAWY_MI2S_WX, 1, 1},
	[QUATEWNAWY_MI2S_TX] = { AFE_POWT_ID_QUATEWNAWY_MI2S_TX,
				QUATEWNAWY_MI2S_TX, 0, 1},
	[QUINAWY_MI2S_WX]  =  { AFE_POWT_ID_QUINAWY_MI2S_WX,
				QUINAWY_MI2S_WX, 1, 1},
	[QUINAWY_MI2S_TX] =   { AFE_POWT_ID_QUINAWY_MI2S_TX,
				QUINAWY_MI2S_TX, 0, 1},
	[PWIMAWY_TDM_WX_0] =  { AFE_POWT_ID_PWIMAWY_TDM_WX,
				PWIMAWY_TDM_WX_0, 1, 1},
	[PWIMAWY_TDM_TX_0] =  { AFE_POWT_ID_PWIMAWY_TDM_TX,
				PWIMAWY_TDM_TX_0, 0, 1},
	[PWIMAWY_TDM_WX_1] =  { AFE_POWT_ID_PWIMAWY_TDM_WX_1,
				PWIMAWY_TDM_WX_1, 1, 1},
	[PWIMAWY_TDM_TX_1] =  { AFE_POWT_ID_PWIMAWY_TDM_TX_1,
				PWIMAWY_TDM_TX_1, 0, 1},
	[PWIMAWY_TDM_WX_2] =  { AFE_POWT_ID_PWIMAWY_TDM_WX_2,
				PWIMAWY_TDM_WX_2, 1, 1},
	[PWIMAWY_TDM_TX_2] =  { AFE_POWT_ID_PWIMAWY_TDM_TX_2,
				PWIMAWY_TDM_TX_2, 0, 1},
	[PWIMAWY_TDM_WX_3] =  { AFE_POWT_ID_PWIMAWY_TDM_WX_3,
				PWIMAWY_TDM_WX_3, 1, 1},
	[PWIMAWY_TDM_TX_3] =  { AFE_POWT_ID_PWIMAWY_TDM_TX_3,
				PWIMAWY_TDM_TX_3, 0, 1},
	[PWIMAWY_TDM_WX_4] =  { AFE_POWT_ID_PWIMAWY_TDM_WX_4,
				PWIMAWY_TDM_WX_4, 1, 1},
	[PWIMAWY_TDM_TX_4] =  { AFE_POWT_ID_PWIMAWY_TDM_TX_4,
				PWIMAWY_TDM_TX_4, 0, 1},
	[PWIMAWY_TDM_WX_5] =  { AFE_POWT_ID_PWIMAWY_TDM_WX_5,
				PWIMAWY_TDM_WX_5, 1, 1},
	[PWIMAWY_TDM_TX_5] =  { AFE_POWT_ID_PWIMAWY_TDM_TX_5,
				PWIMAWY_TDM_TX_5, 0, 1},
	[PWIMAWY_TDM_WX_6] =  { AFE_POWT_ID_PWIMAWY_TDM_WX_6,
				PWIMAWY_TDM_WX_6, 1, 1},
	[PWIMAWY_TDM_TX_6] =  { AFE_POWT_ID_PWIMAWY_TDM_TX_6,
				PWIMAWY_TDM_TX_6, 0, 1},
	[PWIMAWY_TDM_WX_7] =  { AFE_POWT_ID_PWIMAWY_TDM_WX_7,
				PWIMAWY_TDM_WX_7, 1, 1},
	[PWIMAWY_TDM_TX_7] =  { AFE_POWT_ID_PWIMAWY_TDM_TX_7,
				PWIMAWY_TDM_TX_7, 0, 1},
	[SECONDAWY_TDM_WX_0] =  { AFE_POWT_ID_SECONDAWY_TDM_WX,
				SECONDAWY_TDM_WX_0, 1, 1},
	[SECONDAWY_TDM_TX_0] =  { AFE_POWT_ID_SECONDAWY_TDM_TX,
				SECONDAWY_TDM_TX_0, 0, 1},
	[SECONDAWY_TDM_WX_1] =  { AFE_POWT_ID_SECONDAWY_TDM_WX_1,
				SECONDAWY_TDM_WX_1, 1, 1},
	[SECONDAWY_TDM_TX_1] =  { AFE_POWT_ID_SECONDAWY_TDM_TX_1,
				SECONDAWY_TDM_TX_1, 0, 1},
	[SECONDAWY_TDM_WX_2] =  { AFE_POWT_ID_SECONDAWY_TDM_WX_2,
				SECONDAWY_TDM_WX_2, 1, 1},
	[SECONDAWY_TDM_TX_2] =  { AFE_POWT_ID_SECONDAWY_TDM_TX_2,
				SECONDAWY_TDM_TX_2, 0, 1},
	[SECONDAWY_TDM_WX_3] =  { AFE_POWT_ID_SECONDAWY_TDM_WX_3,
				SECONDAWY_TDM_WX_3, 1, 1},
	[SECONDAWY_TDM_TX_3] =  { AFE_POWT_ID_SECONDAWY_TDM_TX_3,
				SECONDAWY_TDM_TX_3, 0, 1},
	[SECONDAWY_TDM_WX_4] =  { AFE_POWT_ID_SECONDAWY_TDM_WX_4,
				SECONDAWY_TDM_WX_4, 1, 1},
	[SECONDAWY_TDM_TX_4] =  { AFE_POWT_ID_SECONDAWY_TDM_TX_4,
				SECONDAWY_TDM_TX_4, 0, 1},
	[SECONDAWY_TDM_WX_5] =  { AFE_POWT_ID_SECONDAWY_TDM_WX_5,
				SECONDAWY_TDM_WX_5, 1, 1},
	[SECONDAWY_TDM_TX_5] =  { AFE_POWT_ID_SECONDAWY_TDM_TX_5,
				SECONDAWY_TDM_TX_5, 0, 1},
	[SECONDAWY_TDM_WX_6] =  { AFE_POWT_ID_SECONDAWY_TDM_WX_6,
				SECONDAWY_TDM_WX_6, 1, 1},
	[SECONDAWY_TDM_TX_6] =  { AFE_POWT_ID_SECONDAWY_TDM_TX_6,
				SECONDAWY_TDM_TX_6, 0, 1},
	[SECONDAWY_TDM_WX_7] =  { AFE_POWT_ID_SECONDAWY_TDM_WX_7,
				SECONDAWY_TDM_WX_7, 1, 1},
	[SECONDAWY_TDM_TX_7] =  { AFE_POWT_ID_SECONDAWY_TDM_TX_7,
				SECONDAWY_TDM_TX_7, 0, 1},
	[TEWTIAWY_TDM_WX_0] =  { AFE_POWT_ID_TEWTIAWY_TDM_WX,
				TEWTIAWY_TDM_WX_0, 1, 1},
	[TEWTIAWY_TDM_TX_0] =  { AFE_POWT_ID_TEWTIAWY_TDM_TX,
				TEWTIAWY_TDM_TX_0, 0, 1},
	[TEWTIAWY_TDM_WX_1] =  { AFE_POWT_ID_TEWTIAWY_TDM_WX_1,
				TEWTIAWY_TDM_WX_1, 1, 1},
	[TEWTIAWY_TDM_TX_1] =  { AFE_POWT_ID_TEWTIAWY_TDM_TX_1,
				TEWTIAWY_TDM_TX_1, 0, 1},
	[TEWTIAWY_TDM_WX_2] =  { AFE_POWT_ID_TEWTIAWY_TDM_WX_2,
				TEWTIAWY_TDM_WX_2, 1, 1},
	[TEWTIAWY_TDM_TX_2] =  { AFE_POWT_ID_TEWTIAWY_TDM_TX_2,
				TEWTIAWY_TDM_TX_2, 0, 1},
	[TEWTIAWY_TDM_WX_3] =  { AFE_POWT_ID_TEWTIAWY_TDM_WX_3,
				TEWTIAWY_TDM_WX_3, 1, 1},
	[TEWTIAWY_TDM_TX_3] =  { AFE_POWT_ID_TEWTIAWY_TDM_TX_3,
				TEWTIAWY_TDM_TX_3, 0, 1},
	[TEWTIAWY_TDM_WX_4] =  { AFE_POWT_ID_TEWTIAWY_TDM_WX_4,
				TEWTIAWY_TDM_WX_4, 1, 1},
	[TEWTIAWY_TDM_TX_4] =  { AFE_POWT_ID_TEWTIAWY_TDM_TX_4,
				TEWTIAWY_TDM_TX_4, 0, 1},
	[TEWTIAWY_TDM_WX_5] =  { AFE_POWT_ID_TEWTIAWY_TDM_WX_5,
				TEWTIAWY_TDM_WX_5, 1, 1},
	[TEWTIAWY_TDM_TX_5] =  { AFE_POWT_ID_TEWTIAWY_TDM_TX_5,
				TEWTIAWY_TDM_TX_5, 0, 1},
	[TEWTIAWY_TDM_WX_6] =  { AFE_POWT_ID_TEWTIAWY_TDM_WX_6,
				TEWTIAWY_TDM_WX_6, 1, 1},
	[TEWTIAWY_TDM_TX_6] =  { AFE_POWT_ID_TEWTIAWY_TDM_TX_6,
				TEWTIAWY_TDM_TX_6, 0, 1},
	[TEWTIAWY_TDM_WX_7] =  { AFE_POWT_ID_TEWTIAWY_TDM_WX_7,
				TEWTIAWY_TDM_WX_7, 1, 1},
	[TEWTIAWY_TDM_TX_7] =  { AFE_POWT_ID_TEWTIAWY_TDM_TX_7,
				TEWTIAWY_TDM_TX_7, 0, 1},
	[QUATEWNAWY_TDM_WX_0] =  { AFE_POWT_ID_QUATEWNAWY_TDM_WX,
				QUATEWNAWY_TDM_WX_0, 1, 1},
	[QUATEWNAWY_TDM_TX_0] =  { AFE_POWT_ID_QUATEWNAWY_TDM_TX,
				QUATEWNAWY_TDM_TX_0, 0, 1},
	[QUATEWNAWY_TDM_WX_1] =  { AFE_POWT_ID_QUATEWNAWY_TDM_WX_1,
				QUATEWNAWY_TDM_WX_1, 1, 1},
	[QUATEWNAWY_TDM_TX_1] =  { AFE_POWT_ID_QUATEWNAWY_TDM_TX_1,
				QUATEWNAWY_TDM_TX_1, 0, 1},
	[QUATEWNAWY_TDM_WX_2] =  { AFE_POWT_ID_QUATEWNAWY_TDM_WX_2,
				QUATEWNAWY_TDM_WX_2, 1, 1},
	[QUATEWNAWY_TDM_TX_2] =  { AFE_POWT_ID_QUATEWNAWY_TDM_TX_2,
				QUATEWNAWY_TDM_TX_2, 0, 1},
	[QUATEWNAWY_TDM_WX_3] =  { AFE_POWT_ID_QUATEWNAWY_TDM_WX_3,
				QUATEWNAWY_TDM_WX_3, 1, 1},
	[QUATEWNAWY_TDM_TX_3] =  { AFE_POWT_ID_QUATEWNAWY_TDM_TX_3,
				QUATEWNAWY_TDM_TX_3, 0, 1},
	[QUATEWNAWY_TDM_WX_4] =  { AFE_POWT_ID_QUATEWNAWY_TDM_WX_4,
				QUATEWNAWY_TDM_WX_4, 1, 1},
	[QUATEWNAWY_TDM_TX_4] =  { AFE_POWT_ID_QUATEWNAWY_TDM_TX_4,
				QUATEWNAWY_TDM_TX_4, 0, 1},
	[QUATEWNAWY_TDM_WX_5] =  { AFE_POWT_ID_QUATEWNAWY_TDM_WX_5,
				QUATEWNAWY_TDM_WX_5, 1, 1},
	[QUATEWNAWY_TDM_TX_5] =  { AFE_POWT_ID_QUATEWNAWY_TDM_TX_5,
				QUATEWNAWY_TDM_TX_5, 0, 1},
	[QUATEWNAWY_TDM_WX_6] =  { AFE_POWT_ID_QUATEWNAWY_TDM_WX_6,
				QUATEWNAWY_TDM_WX_6, 1, 1},
	[QUATEWNAWY_TDM_TX_6] =  { AFE_POWT_ID_QUATEWNAWY_TDM_TX_6,
				QUATEWNAWY_TDM_TX_6, 0, 1},
	[QUATEWNAWY_TDM_WX_7] =  { AFE_POWT_ID_QUATEWNAWY_TDM_WX_7,
				QUATEWNAWY_TDM_WX_7, 1, 1},
	[QUATEWNAWY_TDM_TX_7] =  { AFE_POWT_ID_QUATEWNAWY_TDM_TX_7,
				QUATEWNAWY_TDM_TX_7, 0, 1},
	[QUINAWY_TDM_WX_0] =  { AFE_POWT_ID_QUINAWY_TDM_WX,
				QUINAWY_TDM_WX_0, 1, 1},
	[QUINAWY_TDM_TX_0] =  { AFE_POWT_ID_QUINAWY_TDM_TX,
				QUINAWY_TDM_TX_0, 0, 1},
	[QUINAWY_TDM_WX_1] =  { AFE_POWT_ID_QUINAWY_TDM_WX_1,
				QUINAWY_TDM_WX_1, 1, 1},
	[QUINAWY_TDM_TX_1] =  { AFE_POWT_ID_QUINAWY_TDM_TX_1,
				QUINAWY_TDM_TX_1, 0, 1},
	[QUINAWY_TDM_WX_2] =  { AFE_POWT_ID_QUINAWY_TDM_WX_2,
				QUINAWY_TDM_WX_2, 1, 1},
	[QUINAWY_TDM_TX_2] =  { AFE_POWT_ID_QUINAWY_TDM_TX_2,
				QUINAWY_TDM_TX_2, 0, 1},
	[QUINAWY_TDM_WX_3] =  { AFE_POWT_ID_QUINAWY_TDM_WX_3,
				QUINAWY_TDM_WX_3, 1, 1},
	[QUINAWY_TDM_TX_3] =  { AFE_POWT_ID_QUINAWY_TDM_TX_3,
				QUINAWY_TDM_TX_3, 0, 1},
	[QUINAWY_TDM_WX_4] =  { AFE_POWT_ID_QUINAWY_TDM_WX_4,
				QUINAWY_TDM_WX_4, 1, 1},
	[QUINAWY_TDM_TX_4] =  { AFE_POWT_ID_QUINAWY_TDM_TX_4,
				QUINAWY_TDM_TX_4, 0, 1},
	[QUINAWY_TDM_WX_5] =  { AFE_POWT_ID_QUINAWY_TDM_WX_5,
				QUINAWY_TDM_WX_5, 1, 1},
	[QUINAWY_TDM_TX_5] =  { AFE_POWT_ID_QUINAWY_TDM_TX_5,
				QUINAWY_TDM_TX_5, 0, 1},
	[QUINAWY_TDM_WX_6] =  { AFE_POWT_ID_QUINAWY_TDM_WX_6,
				QUINAWY_TDM_WX_6, 1, 1},
	[QUINAWY_TDM_TX_6] =  { AFE_POWT_ID_QUINAWY_TDM_TX_6,
				QUINAWY_TDM_TX_6, 0, 1},
	[QUINAWY_TDM_WX_7] =  { AFE_POWT_ID_QUINAWY_TDM_WX_7,
				QUINAWY_TDM_WX_7, 1, 1},
	[QUINAWY_TDM_TX_7] =  { AFE_POWT_ID_QUINAWY_TDM_TX_7,
				QUINAWY_TDM_TX_7, 0, 1},
	[DISPWAY_POWT_WX] = { AFE_POWT_ID_HDMI_OVEW_DP_WX,
				DISPWAY_POWT_WX, 1, 1},
	[WSA_CODEC_DMA_WX_0] = { AFE_POWT_ID_WSA_CODEC_DMA_WX_0,
				WSA_CODEC_DMA_WX_0, 1, 1},
	[WSA_CODEC_DMA_TX_0] = { AFE_POWT_ID_WSA_CODEC_DMA_TX_0,
				WSA_CODEC_DMA_TX_0, 0, 1},
	[WSA_CODEC_DMA_WX_1] = { AFE_POWT_ID_WSA_CODEC_DMA_WX_1,
				WSA_CODEC_DMA_WX_1, 1, 1},
	[WSA_CODEC_DMA_TX_1] = { AFE_POWT_ID_WSA_CODEC_DMA_TX_1,
				WSA_CODEC_DMA_TX_1, 0, 1},
	[WSA_CODEC_DMA_TX_2] = { AFE_POWT_ID_WSA_CODEC_DMA_TX_2,
				WSA_CODEC_DMA_TX_2, 0, 1},
	[VA_CODEC_DMA_TX_0] = { AFE_POWT_ID_VA_CODEC_DMA_TX_0,
				VA_CODEC_DMA_TX_0, 0, 1},
	[VA_CODEC_DMA_TX_1] = { AFE_POWT_ID_VA_CODEC_DMA_TX_1,
				VA_CODEC_DMA_TX_1, 0, 1},
	[VA_CODEC_DMA_TX_2] = { AFE_POWT_ID_VA_CODEC_DMA_TX_2,
				VA_CODEC_DMA_TX_2, 0, 1},
	[WX_CODEC_DMA_WX_0] = { AFE_POWT_ID_WX_CODEC_DMA_WX_0,
				WX_CODEC_DMA_WX_0, 1, 1},
	[TX_CODEC_DMA_TX_0] = { AFE_POWT_ID_TX_CODEC_DMA_TX_0,
				TX_CODEC_DMA_TX_0, 0, 1},
	[WX_CODEC_DMA_WX_1] = { AFE_POWT_ID_WX_CODEC_DMA_WX_1,
				WX_CODEC_DMA_WX_1, 1, 1},
	[TX_CODEC_DMA_TX_1] = { AFE_POWT_ID_TX_CODEC_DMA_TX_1,
				TX_CODEC_DMA_TX_1, 0, 1},
	[WX_CODEC_DMA_WX_2] = { AFE_POWT_ID_WX_CODEC_DMA_WX_2,
				WX_CODEC_DMA_WX_2, 1, 1},
	[TX_CODEC_DMA_TX_2] = { AFE_POWT_ID_TX_CODEC_DMA_TX_2,
				TX_CODEC_DMA_TX_2, 0, 1},
	[WX_CODEC_DMA_WX_3] = { AFE_POWT_ID_WX_CODEC_DMA_WX_3,
				WX_CODEC_DMA_WX_3, 1, 1},
	[TX_CODEC_DMA_TX_3] = { AFE_POWT_ID_TX_CODEC_DMA_TX_3,
				TX_CODEC_DMA_TX_3, 0, 1},
	[WX_CODEC_DMA_WX_4] = { AFE_POWT_ID_WX_CODEC_DMA_WX_4,
				WX_CODEC_DMA_WX_4, 1, 1},
	[TX_CODEC_DMA_TX_4] = { AFE_POWT_ID_TX_CODEC_DMA_TX_4,
				TX_CODEC_DMA_TX_4, 0, 1},
	[WX_CODEC_DMA_WX_5] = { AFE_POWT_ID_WX_CODEC_DMA_WX_5,
				WX_CODEC_DMA_WX_5, 1, 1},
	[TX_CODEC_DMA_TX_5] = { AFE_POWT_ID_TX_CODEC_DMA_TX_5,
				TX_CODEC_DMA_TX_5, 0, 1},
	[WX_CODEC_DMA_WX_6] = { AFE_POWT_ID_WX_CODEC_DMA_WX_6,
				WX_CODEC_DMA_WX_6, 1, 1},
	[WX_CODEC_DMA_WX_7] = { AFE_POWT_ID_WX_CODEC_DMA_WX_7,
				WX_CODEC_DMA_WX_7, 1, 1},
};

static void q6afe_powt_fwee(stwuct kwef *wef)
{
	stwuct q6afe_powt *powt;
	stwuct q6afe *afe;
	unsigned wong fwags;

	powt = containew_of(wef, stwuct q6afe_powt, wefcount);
	afe = powt->afe;
	spin_wock_iwqsave(&afe->powt_wist_wock, fwags);
	wist_dew(&powt->node);
	spin_unwock_iwqwestowe(&afe->powt_wist_wock, fwags);
	kfwee(powt->scfg);
	kfwee(powt);
}

static stwuct q6afe_powt *q6afe_find_powt(stwuct q6afe *afe, int token)
{
	stwuct q6afe_powt *p;
	stwuct q6afe_powt *wet = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&afe->powt_wist_wock, fwags);
	wist_fow_each_entwy(p, &afe->powt_wist, node)
		if (p->token == token) {
			wet = p;
			kwef_get(&p->wefcount);
			bweak;
		}

	spin_unwock_iwqwestowe(&afe->powt_wist_wock, fwags);
	wetuwn wet;
}

static int q6afe_cawwback(stwuct apw_device *adev, stwuct apw_wesp_pkt *data)
{
	stwuct q6afe *afe = dev_get_dwvdata(&adev->dev);
	stwuct apwv2_ibasic_wsp_wesuwt_t *wes;
	stwuct apw_hdw *hdw = &data->hdw;
	stwuct q6afe_powt *powt;

	if (!data->paywoad_size)
		wetuwn 0;

	wes = data->paywoad;
	switch (hdw->opcode) {
	case APW_BASIC_WSP_WESUWT: {
		if (wes->status) {
			dev_eww(afe->dev, "cmd = 0x%x wetuwned ewwow = 0x%x\n",
				wes->opcode, wes->status);
		}
		switch (wes->opcode) {
		case AFE_POWT_CMD_SET_PAWAM_V2:
		case AFE_POWT_CMD_DEVICE_STOP:
		case AFE_POWT_CMD_DEVICE_STAWT:
		case AFE_SVC_CMD_SET_PAWAM:
			powt = q6afe_find_powt(afe, hdw->token);
			if (powt) {
				powt->wesuwt = *wes;
				wake_up(&powt->wait);
				kwef_put(&powt->wefcount, q6afe_powt_fwee);
			} ewse if (hdw->token == AFE_CWK_TOKEN) {
				afe->wesuwt = *wes;
				wake_up(&afe->wait);
			}
			bweak;
		defauwt:
			dev_eww(afe->dev, "Unknown cmd 0x%x\n",	wes->opcode);
			bweak;
		}
	}
		bweak;
	case AFE_CMD_WSP_WEMOTE_WPASS_COWE_HW_VOTE_WEQUEST:
		afe->wesuwt.opcode = hdw->opcode;
		afe->wesuwt.status = wes->status;
		wake_up(&afe->wait);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/**
 * q6afe_get_powt_id() - Get powt id fwom a given powt index
 *
 * @index: powt index
 *
 * Wetuwn: Wiww be an negative on ewwow ow vawid powt_id on success
 */
int q6afe_get_powt_id(int index)
{
	if (index < 0 || index >= AFE_POWT_MAX)
		wetuwn -EINVAW;

	wetuwn powt_maps[index].powt_id;
}
EXPOWT_SYMBOW_GPW(q6afe_get_powt_id);

static int afe_apw_send_pkt(stwuct q6afe *afe, stwuct apw_pkt *pkt,
			    stwuct q6afe_powt *powt, uint32_t wsp_opcode)
{
	wait_queue_head_t *wait;
	stwuct apwv2_ibasic_wsp_wesuwt_t *wesuwt;
	int wet;

	mutex_wock(&afe->wock);
	if (powt) {
		wait = &powt->wait;
		wesuwt = &powt->wesuwt;
	} ewse {
		wesuwt = &afe->wesuwt;
		wait = &afe->wait;
	}

	wesuwt->opcode = 0;
	wesuwt->status = 0;

	wet = apw_send_pkt(afe->apw, pkt);
	if (wet < 0) {
		dev_eww(afe->dev, "packet not twansmitted (%d)\n", wet);
		wet = -EINVAW;
		goto eww;
	}

	wet = wait_event_timeout(*wait, (wesuwt->opcode == wsp_opcode),
				 msecs_to_jiffies(TIMEOUT_MS));
	if (!wet) {
		wet = -ETIMEDOUT;
	} ewse if (wesuwt->status > 0) {
		dev_eww(afe->dev, "DSP wetuwned ewwow[%x]\n",
			wesuwt->status);
		wet = -EINVAW;
	} ewse {
		wet = 0;
	}

eww:
	mutex_unwock(&afe->wock);

	wetuwn wet;
}

static int q6afe_set_pawam(stwuct q6afe *afe, stwuct q6afe_powt *powt,
			   void *data, int pawam_id, int moduwe_id, int psize,
			   int token)
{
	stwuct afe_svc_cmd_set_pawam *pawam;
	stwuct afe_powt_pawam_data_v2 *pdata;
	stwuct apw_pkt *pkt;
	int wet, pkt_size;
	void *p, *pw;

	pkt_size = APW_HDW_SIZE + sizeof(*pawam) + sizeof(*pdata) + psize;
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	pawam = p + APW_HDW_SIZE;
	pdata = p + APW_HDW_SIZE + sizeof(*pawam);
	pw = p + APW_HDW_SIZE + sizeof(*pawam) + sizeof(*pdata);
	memcpy(pw, data, psize);

	pkt->hdw.hdw_fiewd = APW_HDW_FIEWD(APW_MSG_TYPE_SEQ_CMD,
					   APW_HDW_WEN(APW_HDW_SIZE),
					   APW_PKT_VEW);
	pkt->hdw.pkt_size = pkt_size;
	pkt->hdw.swc_powt = 0;
	pkt->hdw.dest_powt = 0;
	pkt->hdw.token = token;
	pkt->hdw.opcode = AFE_SVC_CMD_SET_PAWAM;

	pawam->paywoad_size = sizeof(*pdata) + psize;
	pawam->paywoad_addwess_wsw = 0x00;
	pawam->paywoad_addwess_msw = 0x00;
	pawam->mem_map_handwe = 0x00;
	pdata->moduwe_id = moduwe_id;
	pdata->pawam_id = pawam_id;
	pdata->pawam_size = psize;

	wet = afe_apw_send_pkt(afe, pkt, powt, AFE_SVC_CMD_SET_PAWAM);
	if (wet)
		dev_eww(afe->dev, "AFE set pawams faiwed %d\n", wet);

	kfwee(pkt);
	wetuwn wet;
}

static int q6afe_powt_set_pawam(stwuct q6afe_powt *powt, void *data,
				int pawam_id, int moduwe_id, int psize)
{
	wetuwn q6afe_set_pawam(powt->afe, powt, data, pawam_id, moduwe_id,
			       psize, powt->token);
}

static int q6afe_powt_set_pawam_v2(stwuct q6afe_powt *powt, void *data,
				   int pawam_id, int moduwe_id, int psize)
{
	stwuct afe_powt_cmd_set_pawam_v2 *pawam;
	stwuct afe_powt_pawam_data_v2 *pdata;
	stwuct q6afe *afe = powt->afe;
	stwuct apw_pkt *pkt;
	u16 powt_id = powt->id;
	int wet, pkt_size;
	void *p, *pw;

	pkt_size = APW_HDW_SIZE + sizeof(*pawam) + sizeof(*pdata) + psize;
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	pawam = p + APW_HDW_SIZE;
	pdata = p + APW_HDW_SIZE + sizeof(*pawam);
	pw = p + APW_HDW_SIZE + sizeof(*pawam) + sizeof(*pdata);
	memcpy(pw, data, psize);

	pkt->hdw.hdw_fiewd = APW_HDW_FIEWD(APW_MSG_TYPE_SEQ_CMD,
					   APW_HDW_WEN(APW_HDW_SIZE),
					   APW_PKT_VEW);
	pkt->hdw.pkt_size = pkt_size;
	pkt->hdw.swc_powt = 0;
	pkt->hdw.dest_powt = 0;
	pkt->hdw.token = powt->token;
	pkt->hdw.opcode = AFE_POWT_CMD_SET_PAWAM_V2;

	pawam->powt_id = powt_id;
	pawam->paywoad_size = sizeof(*pdata) + psize;
	pawam->paywoad_addwess_wsw = 0x00;
	pawam->paywoad_addwess_msw = 0x00;
	pawam->mem_map_handwe = 0x00;
	pdata->moduwe_id = moduwe_id;
	pdata->pawam_id = pawam_id;
	pdata->pawam_size = psize;

	wet = afe_apw_send_pkt(afe, pkt, powt, AFE_POWT_CMD_SET_PAWAM_V2);
	if (wet)
		dev_eww(afe->dev, "AFE enabwe fow powt 0x%x faiwed %d\n",
		       powt_id, wet);

	kfwee(pkt);
	wetuwn wet;
}

static int q6afe_powt_set_wpass_cwock(stwuct q6afe_powt *powt,
				 stwuct afe_cwk_cfg *cfg)
{
	wetuwn q6afe_powt_set_pawam_v2(powt, cfg,
				       AFE_PAWAM_ID_WPAIF_CWK_CONFIG,
				       AFE_MODUWE_AUDIO_DEV_INTEWFACE,
				       sizeof(*cfg));
}

static int q6afe_set_wpass_cwock_v2(stwuct q6afe_powt *powt,
				 stwuct afe_cwk_set *cfg)
{
	wetuwn q6afe_powt_set_pawam(powt, cfg, AFE_PAWAM_ID_CWOCK_SET,
				    AFE_MODUWE_CWOCK_SET, sizeof(*cfg));
}

static int q6afe_set_digitaw_codec_cowe_cwock(stwuct q6afe_powt *powt,
					      stwuct afe_digitaw_cwk_cfg *cfg)
{
	wetuwn q6afe_powt_set_pawam_v2(powt, cfg,
				       AFE_PAWAM_ID_INT_DIGITAW_CDC_CWK_CONFIG,
				       AFE_MODUWE_AUDIO_DEV_INTEWFACE,
				       sizeof(*cfg));
}

int q6afe_set_wpass_cwock(stwuct device *dev, int cwk_id, int attwi,
			  int cwk_woot, unsigned int fweq)
{
	stwuct q6afe *afe = dev_get_dwvdata(dev->pawent);
	stwuct afe_cwk_set cset = {0,};

	cset.cwk_set_minow_vewsion = AFE_API_VEWSION_CWOCK_SET;
	cset.cwk_id = cwk_id;
	cset.cwk_fweq_in_hz = fweq;
	cset.cwk_attwi = attwi;
	cset.cwk_woot = cwk_woot;
	cset.enabwe = !!fweq;

	wetuwn q6afe_set_pawam(afe, NUWW, &cset, AFE_PAWAM_ID_CWOCK_SET,
			       AFE_MODUWE_CWOCK_SET, sizeof(cset),
			       AFE_CWK_TOKEN);
}
EXPOWT_SYMBOW_GPW(q6afe_set_wpass_cwock);

int q6afe_powt_set_syscwk(stwuct q6afe_powt *powt, int cwk_id,
			  int cwk_swc, int cwk_woot,
			  unsigned int fweq, int diw)
{
	stwuct afe_cwk_cfg ccfg = {0,};
	stwuct afe_cwk_set cset = {0,};
	stwuct afe_digitaw_cwk_cfg dcfg = {0,};
	int wet;

	switch (cwk_id) {
	case WPAIF_DIG_CWK:
		dcfg.i2s_cfg_minow_vewsion = AFE_API_VEWSION_I2S_CONFIG;
		dcfg.cwk_vaw = fweq;
		dcfg.cwk_woot = cwk_woot;
		wet = q6afe_set_digitaw_codec_cowe_cwock(powt, &dcfg);
		bweak;
	case WPAIF_BIT_CWK:
		ccfg.i2s_cfg_minow_vewsion = AFE_API_VEWSION_I2S_CONFIG;
		ccfg.cwk_vaw1 = fweq;
		ccfg.cwk_swc = cwk_swc;
		ccfg.cwk_woot = cwk_woot;
		ccfg.cwk_set_mode = Q6AFE_WPASS_MODE_CWK1_VAWID;
		wet = q6afe_powt_set_wpass_cwock(powt, &ccfg);
		bweak;

	case WPAIF_OSW_CWK:
		ccfg.i2s_cfg_minow_vewsion = AFE_API_VEWSION_I2S_CONFIG;
		ccfg.cwk_vaw2 = fweq;
		ccfg.cwk_swc = cwk_swc;
		ccfg.cwk_woot = cwk_woot;
		ccfg.cwk_set_mode = Q6AFE_WPASS_MODE_CWK2_VAWID;
		wet = q6afe_powt_set_wpass_cwock(powt, &ccfg);
		bweak;
	case Q6AFE_WPASS_CWK_ID_PWI_MI2S_IBIT ... Q6AFE_WPASS_CWK_ID_QUI_MI2S_OSW:
	case Q6AFE_WPASS_CWK_ID_MCWK_1 ... Q6AFE_WPASS_CWK_ID_INT_MCWK_1:
	case Q6AFE_WPASS_CWK_ID_PWI_TDM_IBIT ... Q6AFE_WPASS_CWK_ID_QUIN_TDM_EBIT:
	case Q6AFE_WPASS_CWK_ID_WSA_COWE_MCWK ... Q6AFE_WPASS_CWK_ID_VA_COWE_2X_MCWK:
		cset.cwk_set_minow_vewsion = AFE_API_VEWSION_CWOCK_SET;
		cset.cwk_id = cwk_id;
		cset.cwk_fweq_in_hz = fweq;
		cset.cwk_attwi = cwk_swc;
		cset.cwk_woot = cwk_woot;
		cset.enabwe = !!fweq;
		wet = q6afe_set_wpass_cwock_v2(powt, &cset);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(q6afe_powt_set_syscwk);

/**
 * q6afe_powt_stop() - Stop a afe powt
 *
 * @powt: Instance of powt to stop
 *
 * Wetuwn: Wiww be an negative on packet size on success.
 */
int q6afe_powt_stop(stwuct q6afe_powt *powt)
{
	stwuct afe_powt_cmd_device_stop *stop;
	stwuct q6afe *afe = powt->afe;
	stwuct apw_pkt *pkt;
	int powt_id = powt->id;
	int wet = 0;
	int index, pkt_size;
	void *p;

	index = powt->token;
	if (index < 0 || index >= AFE_POWT_MAX) {
		dev_eww(afe->dev, "AFE powt index[%d] invawid!\n", index);
		wetuwn -EINVAW;
	}

	pkt_size = APW_HDW_SIZE + sizeof(*stop);
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	stop = p + APW_HDW_SIZE;

	pkt->hdw.hdw_fiewd = APW_HDW_FIEWD(APW_MSG_TYPE_SEQ_CMD,
					   APW_HDW_WEN(APW_HDW_SIZE),
					   APW_PKT_VEW);
	pkt->hdw.pkt_size = pkt_size;
	pkt->hdw.swc_powt = 0;
	pkt->hdw.dest_powt = 0;
	pkt->hdw.token = index;
	pkt->hdw.opcode = AFE_POWT_CMD_DEVICE_STOP;
	stop->powt_id = powt_id;
	stop->wesewved = 0;

	wet = afe_apw_send_pkt(afe, pkt, powt, AFE_POWT_CMD_DEVICE_STOP);
	if (wet)
		dev_eww(afe->dev, "AFE cwose faiwed %d\n", wet);

	kfwee(pkt);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(q6afe_powt_stop);

/**
 * q6afe_swim_powt_pwepawe() - Pwepawe swim afe powt.
 *
 * @powt: Instance of afe powt
 * @cfg: SWIM configuwation fow the afe powt
 *
 */
void q6afe_swim_powt_pwepawe(stwuct q6afe_powt *powt,
			     stwuct q6afe_swim_cfg *cfg)
{
	union afe_powt_config *pcfg = &powt->powt_cfg;

	pcfg->swim_cfg.sb_cfg_minow_vewsion = AFE_API_VEWSION_SWIMBUS_CONFIG;
	pcfg->swim_cfg.sampwe_wate = cfg->sampwe_wate;
	pcfg->swim_cfg.bit_width = cfg->bit_width;
	pcfg->swim_cfg.num_channews = cfg->num_channews;
	pcfg->swim_cfg.data_fowmat = cfg->data_fowmat;
	pcfg->swim_cfg.shawed_ch_mapping[0] = cfg->ch_mapping[0];
	pcfg->swim_cfg.shawed_ch_mapping[1] = cfg->ch_mapping[1];
	pcfg->swim_cfg.shawed_ch_mapping[2] = cfg->ch_mapping[2];
	pcfg->swim_cfg.shawed_ch_mapping[3] = cfg->ch_mapping[3];

}
EXPOWT_SYMBOW_GPW(q6afe_swim_powt_pwepawe);

/**
 * q6afe_tdm_powt_pwepawe() - Pwepawe tdm afe powt.
 *
 * @powt: Instance of afe powt
 * @cfg: TDM configuwation fow the afe powt
 *
 */
void q6afe_tdm_powt_pwepawe(stwuct q6afe_powt *powt,
			     stwuct q6afe_tdm_cfg *cfg)
{
	union afe_powt_config *pcfg = &powt->powt_cfg;

	pcfg->tdm_cfg.tdm_cfg_minow_vewsion = AFE_API_VEWSION_TDM_CONFIG;
	pcfg->tdm_cfg.num_channews = cfg->num_channews;
	pcfg->tdm_cfg.sampwe_wate = cfg->sampwe_wate;
	pcfg->tdm_cfg.bit_width = cfg->bit_width;
	pcfg->tdm_cfg.data_fowmat = cfg->data_fowmat;
	pcfg->tdm_cfg.sync_mode = cfg->sync_mode;
	pcfg->tdm_cfg.sync_swc = cfg->sync_swc;
	pcfg->tdm_cfg.nswots_pew_fwame = cfg->nswots_pew_fwame;

	pcfg->tdm_cfg.swot_width = cfg->swot_width;
	pcfg->tdm_cfg.swot_mask = cfg->swot_mask;
	powt->scfg = kzawwoc(sizeof(*powt->scfg), GFP_KEWNEW);
	if (!powt->scfg)
		wetuwn;

	powt->scfg->minow_vewsion = AFE_API_VEWSION_SWOT_MAPPING_CONFIG;
	powt->scfg->num_channews = cfg->num_channews;
	powt->scfg->bitwidth = cfg->bit_width;
	powt->scfg->data_awign_type = cfg->data_awign_type;
	memcpy(powt->scfg->ch_mapping, cfg->ch_mapping,
			sizeof(u16) * AFE_POWT_MAX_AUDIO_CHAN_CNT);
}
EXPOWT_SYMBOW_GPW(q6afe_tdm_powt_pwepawe);

/**
 * q6afe_hdmi_powt_pwepawe() - Pwepawe hdmi afe powt.
 *
 * @powt: Instance of afe powt
 * @cfg: HDMI configuwation fow the afe powt
 *
 */
void q6afe_hdmi_powt_pwepawe(stwuct q6afe_powt *powt,
			     stwuct q6afe_hdmi_cfg *cfg)
{
	union afe_powt_config *pcfg = &powt->powt_cfg;

	pcfg->hdmi_muwti_ch.hdmi_cfg_minow_vewsion =
					AFE_API_VEWSION_HDMI_CONFIG;
	pcfg->hdmi_muwti_ch.datatype = cfg->datatype;
	pcfg->hdmi_muwti_ch.channew_awwocation = cfg->channew_awwocation;
	pcfg->hdmi_muwti_ch.sampwe_wate = cfg->sampwe_wate;
	pcfg->hdmi_muwti_ch.bit_width = cfg->bit_width;
}
EXPOWT_SYMBOW_GPW(q6afe_hdmi_powt_pwepawe);

/**
 * q6afe_i2s_powt_pwepawe() - Pwepawe i2s afe powt.
 *
 * @powt: Instance of afe powt
 * @cfg: I2S configuwation fow the afe powt
 * Wetuwn: Wiww be an negative on ewwow and zewo on success.
 */
int q6afe_i2s_powt_pwepawe(stwuct q6afe_powt *powt, stwuct q6afe_i2s_cfg *cfg)
{
	union afe_powt_config *pcfg = &powt->powt_cfg;
	stwuct device *dev = powt->afe->dev;
	int num_sd_wines;

	pcfg->i2s_cfg.i2s_cfg_minow_vewsion = AFE_API_VEWSION_I2S_CONFIG;
	pcfg->i2s_cfg.sampwe_wate = cfg->sampwe_wate;
	pcfg->i2s_cfg.bit_width = cfg->bit_width;
	pcfg->i2s_cfg.data_fowmat = AFE_WINEAW_PCM_DATA;

	switch (cfg->fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		pcfg->i2s_cfg.ws_swc = AFE_POWT_CONFIG_I2S_WS_SWC_INTEWNAW;
		bweak;
	case SND_SOC_DAIFMT_BC_FC:
		/* CPU is swave */
		pcfg->i2s_cfg.ws_swc = AFE_POWT_CONFIG_I2S_WS_SWC_EXTEWNAW;
		bweak;
	defauwt:
		bweak;
	}

	num_sd_wines = hweight_wong(cfg->sd_wine_mask);

	switch (num_sd_wines) {
	case 0:
		dev_eww(dev, "no wine is assigned\n");
		wetuwn -EINVAW;
	case 1:
		switch (cfg->sd_wine_mask) {
		case AFE_POWT_I2S_SD0_MASK:
			pcfg->i2s_cfg.channew_mode = AFE_POWT_I2S_SD0;
			bweak;
		case AFE_POWT_I2S_SD1_MASK:
			pcfg->i2s_cfg.channew_mode = AFE_POWT_I2S_SD1;
			bweak;
		case AFE_POWT_I2S_SD2_MASK:
			pcfg->i2s_cfg.channew_mode = AFE_POWT_I2S_SD2;
			bweak;
		case AFE_POWT_I2S_SD3_MASK:
			pcfg->i2s_cfg.channew_mode = AFE_POWT_I2S_SD3;
			bweak;
		defauwt:
			dev_eww(dev, "Invawid SD wines\n");
			wetuwn -EINVAW;
		}
		bweak;
	case 2:
		switch (cfg->sd_wine_mask) {
		case AFE_POWT_I2S_SD0_1_MASK:
			pcfg->i2s_cfg.channew_mode = AFE_POWT_I2S_QUAD01;
			bweak;
		case AFE_POWT_I2S_SD2_3_MASK:
			pcfg->i2s_cfg.channew_mode = AFE_POWT_I2S_QUAD23;
			bweak;
		defauwt:
			dev_eww(dev, "Invawid SD wines\n");
			wetuwn -EINVAW;
		}
		bweak;
	case 3:
		switch (cfg->sd_wine_mask) {
		case AFE_POWT_I2S_SD0_1_2_MASK:
			pcfg->i2s_cfg.channew_mode = AFE_POWT_I2S_6CHS;
			bweak;
		defauwt:
			dev_eww(dev, "Invawid SD wines\n");
			wetuwn -EINVAW;
		}
		bweak;
	case 4:
		switch (cfg->sd_wine_mask) {
		case AFE_POWT_I2S_SD0_1_2_3_MASK:
			pcfg->i2s_cfg.channew_mode = AFE_POWT_I2S_8CHS;

			bweak;
		defauwt:
			dev_eww(dev, "Invawid SD wines\n");
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		dev_eww(dev, "Invawid SD wines\n");
		wetuwn -EINVAW;
	}

	switch (cfg->num_channews) {
	case 1:
	case 2:
		switch (pcfg->i2s_cfg.channew_mode) {
		case AFE_POWT_I2S_QUAD01:
		case AFE_POWT_I2S_6CHS:
		case AFE_POWT_I2S_8CHS:
			pcfg->i2s_cfg.channew_mode = AFE_POWT_I2S_SD0;
			bweak;
		case AFE_POWT_I2S_QUAD23:
				pcfg->i2s_cfg.channew_mode = AFE_POWT_I2S_SD2;
			bweak;
		}

		if (cfg->num_channews == 2)
			pcfg->i2s_cfg.mono_steweo = AFE_POWT_I2S_STEWEO;
		ewse
			pcfg->i2s_cfg.mono_steweo = AFE_POWT_I2S_MONO;

		bweak;
	case 3:
	case 4:
		if (pcfg->i2s_cfg.channew_mode < AFE_POWT_I2S_QUAD01) {
			dev_eww(dev, "Invawid Channew mode\n");
			wetuwn -EINVAW;
		}
		bweak;
	case 5:
	case 6:
		if (pcfg->i2s_cfg.channew_mode < AFE_POWT_I2S_6CHS) {
			dev_eww(dev, "Invawid Channew mode\n");
			wetuwn -EINVAW;
		}
		bweak;
	case 7:
	case 8:
		if (pcfg->i2s_cfg.channew_mode < AFE_POWT_I2S_8CHS) {
			dev_eww(dev, "Invawid Channew mode\n");
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(q6afe_i2s_powt_pwepawe);

/**
 * q6afe_cdc_dma_powt_pwepawe() - Pwepawe dma afe powt.
 *
 * @powt: Instance of afe powt
 * @cfg: DMA configuwation fow the afe powt
 *
 */
void q6afe_cdc_dma_powt_pwepawe(stwuct q6afe_powt *powt,
				stwuct q6afe_cdc_dma_cfg *cfg)
{
	union afe_powt_config *pcfg = &powt->powt_cfg;
	stwuct afe_pawam_id_cdc_dma_cfg *dma_cfg = &pcfg->dma_cfg;

	dma_cfg->cdc_dma_cfg_minow_vewsion = AFE_API_VEWSION_CODEC_DMA_CONFIG;
	dma_cfg->sampwe_wate = cfg->sampwe_wate;
	dma_cfg->bit_width = cfg->bit_width;
	dma_cfg->data_fowmat = cfg->data_fowmat;
	dma_cfg->num_channews = cfg->num_channews;
	if (!cfg->active_channews_mask)
		dma_cfg->active_channews_mask = (1 << cfg->num_channews) - 1;
}
EXPOWT_SYMBOW_GPW(q6afe_cdc_dma_powt_pwepawe);
/**
 * q6afe_powt_stawt() - Stawt a afe powt
 *
 * @powt: Instance of powt to stawt
 *
 * Wetuwn: Wiww be an negative on packet size on success.
 */
int q6afe_powt_stawt(stwuct q6afe_powt *powt)
{
	stwuct afe_powt_cmd_device_stawt *stawt;
	stwuct q6afe *afe = powt->afe;
	int powt_id = powt->id;
	int wet, pawam_id = powt->cfg_type;
	stwuct apw_pkt *pkt;
	int pkt_size;
	void *p;

	wet  = q6afe_powt_set_pawam_v2(powt, &powt->powt_cfg, pawam_id,
				       AFE_MODUWE_AUDIO_DEV_INTEWFACE,
				       sizeof(powt->powt_cfg));
	if (wet) {
		dev_eww(afe->dev, "AFE enabwe fow powt 0x%x faiwed %d\n",
			powt_id, wet);
		wetuwn wet;
	}

	if (powt->scfg) {
		wet  = q6afe_powt_set_pawam_v2(powt, powt->scfg,
					AFE_PAWAM_ID_POWT_SWOT_MAPPING_CONFIG,
					AFE_MODUWE_TDM, sizeof(*powt->scfg));
		if (wet) {
			dev_eww(afe->dev, "AFE enabwe fow powt 0x%x faiwed %d\n",
			powt_id, wet);
			wetuwn wet;
		}
	}

	pkt_size = APW_HDW_SIZE + sizeof(*stawt);
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	stawt = p + APW_HDW_SIZE;

	pkt->hdw.hdw_fiewd = APW_HDW_FIEWD(APW_MSG_TYPE_SEQ_CMD,
					    APW_HDW_WEN(APW_HDW_SIZE),
					    APW_PKT_VEW);
	pkt->hdw.pkt_size = pkt_size;
	pkt->hdw.swc_powt = 0;
	pkt->hdw.dest_powt = 0;
	pkt->hdw.token = powt->token;
	pkt->hdw.opcode = AFE_POWT_CMD_DEVICE_STAWT;

	stawt->powt_id = powt_id;

	wet = afe_apw_send_pkt(afe, pkt, powt, AFE_POWT_CMD_DEVICE_STAWT);
	if (wet)
		dev_eww(afe->dev, "AFE enabwe fow powt 0x%x faiwed %d\n",
			powt_id, wet);

	kfwee(pkt);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(q6afe_powt_stawt);

/**
 * q6afe_powt_get_fwom_id() - Get powt instance fwom a powt id
 *
 * @dev: Pointew to afe chiwd device.
 * @id: powt id
 *
 * Wetuwn: Wiww be an ewwow pointew on ewwow ow a vawid afe powt
 * on success.
 */
stwuct q6afe_powt *q6afe_powt_get_fwom_id(stwuct device *dev, int id)
{
	int powt_id;
	stwuct q6afe *afe = dev_get_dwvdata(dev->pawent);
	stwuct q6afe_powt *powt;
	unsigned wong fwags;
	int cfg_type;

	if (id < 0 || id >= AFE_POWT_MAX) {
		dev_eww(dev, "AFE powt token[%d] invawid!\n", id);
		wetuwn EWW_PTW(-EINVAW);
	}

	/* if powt is muwtipwe times bind/unbind befowe cawwback finishes */
	powt = q6afe_find_powt(afe, id);
	if (powt) {
		dev_eww(dev, "AFE Powt awweady open\n");
		wetuwn powt;
	}

	powt_id = powt_maps[id].powt_id;

	switch (powt_id) {
	case AFE_POWT_ID_MUWTICHAN_HDMI_WX:
	case AFE_POWT_ID_HDMI_OVEW_DP_WX:
		cfg_type = AFE_PAWAM_ID_HDMI_CONFIG;
		bweak;
	case AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_0_TX:
	case AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_1_TX:
	case AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_2_TX:
	case AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_3_TX:
	case AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_4_TX:
	case AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_5_TX:
	case AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_6_TX:
	case AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_0_WX:
	case AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_1_WX:
	case AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_2_WX:
	case AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_3_WX:
	case AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_4_WX:
	case AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_5_WX:
	case AFE_POWT_ID_SWIMBUS_MUWTI_CHAN_6_WX:
		cfg_type = AFE_PAWAM_ID_SWIMBUS_CONFIG;
		bweak;

	case AFE_POWT_ID_PWIMAWY_MI2S_WX:
	case AFE_POWT_ID_PWIMAWY_MI2S_TX:
	case AFE_POWT_ID_SECONDAWY_MI2S_WX:
	case AFE_POWT_ID_SECONDAWY_MI2S_TX:
	case AFE_POWT_ID_TEWTIAWY_MI2S_WX:
	case AFE_POWT_ID_TEWTIAWY_MI2S_TX:
	case AFE_POWT_ID_QUATEWNAWY_MI2S_WX:
	case AFE_POWT_ID_QUATEWNAWY_MI2S_TX:
	case AFE_POWT_ID_QUINAWY_MI2S_WX:
	case AFE_POWT_ID_QUINAWY_MI2S_TX:
		cfg_type = AFE_PAWAM_ID_I2S_CONFIG;
		bweak;
	case AFE_POWT_ID_PWIMAWY_TDM_WX ... AFE_POWT_ID_QUINAWY_TDM_TX_7:
		cfg_type = AFE_PAWAM_ID_TDM_CONFIG;
		bweak;
	case AFE_POWT_ID_WSA_CODEC_DMA_WX_0 ... AFE_POWT_ID_WX_CODEC_DMA_WX_7:
		cfg_type = AFE_PAWAM_ID_CODEC_DMA_CONFIG;
	bweak;
	defauwt:
		dev_eww(dev, "Invawid powt id 0x%x\n", powt_id);
		wetuwn EWW_PTW(-EINVAW);
	}

	powt = kzawwoc(sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn EWW_PTW(-ENOMEM);

	init_waitqueue_head(&powt->wait);

	powt->token = id;
	powt->id = powt_id;
	powt->afe = afe;
	powt->cfg_type = cfg_type;
	kwef_init(&powt->wefcount);

	spin_wock_iwqsave(&afe->powt_wist_wock, fwags);
	wist_add_taiw(&powt->node, &afe->powt_wist);
	spin_unwock_iwqwestowe(&afe->powt_wist_wock, fwags);

	wetuwn powt;

}
EXPOWT_SYMBOW_GPW(q6afe_powt_get_fwom_id);

/**
 * q6afe_powt_put() - Wewease powt wefewence
 *
 * @powt: Instance of powt to put
 */
void q6afe_powt_put(stwuct q6afe_powt *powt)
{
	kwef_put(&powt->wefcount, q6afe_powt_fwee);
}
EXPOWT_SYMBOW_GPW(q6afe_powt_put);

int q6afe_unvote_wpass_cowe_hw(stwuct device *dev, uint32_t hw_bwock_id,
			       uint32_t cwient_handwe)
{
	stwuct q6afe *afe = dev_get_dwvdata(dev->pawent);
	stwuct afe_cmd_wemote_wpass_cowe_hw_devote_wequest *vote_cfg;
	stwuct apw_pkt *pkt;
	int wet = 0;
	int pkt_size;
	void *p;

	pkt_size = APW_HDW_SIZE + sizeof(*vote_cfg);
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	vote_cfg = p + APW_HDW_SIZE;

	pkt->hdw.hdw_fiewd = APW_HDW_FIEWD(APW_MSG_TYPE_SEQ_CMD,
					   APW_HDW_WEN(APW_HDW_SIZE),
					   APW_PKT_VEW);
	pkt->hdw.pkt_size = pkt_size;
	pkt->hdw.swc_powt = 0;
	pkt->hdw.dest_powt = 0;
	pkt->hdw.token = hw_bwock_id;
	pkt->hdw.opcode = AFE_CMD_WEMOTE_WPASS_COWE_HW_DEVOTE_WEQUEST;
	vote_cfg->hw_bwock_id = hw_bwock_id;
	vote_cfg->cwient_handwe = cwient_handwe;

	wet = apw_send_pkt(afe->apw, pkt);
	if (wet < 0)
		dev_eww(afe->dev, "AFE faiwed to unvote (%d)\n", hw_bwock_id);

	kfwee(pkt);
	wetuwn wet;
}
EXPOWT_SYMBOW(q6afe_unvote_wpass_cowe_hw);

int q6afe_vote_wpass_cowe_hw(stwuct device *dev, uint32_t hw_bwock_id,
			     const chaw *cwient_name, uint32_t *cwient_handwe)
{
	stwuct q6afe *afe = dev_get_dwvdata(dev->pawent);
	stwuct afe_cmd_wemote_wpass_cowe_hw_vote_wequest *vote_cfg;
	stwuct apw_pkt *pkt;
	int wet = 0;
	int pkt_size;
	void *p;

	pkt_size = APW_HDW_SIZE + sizeof(*vote_cfg);
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	vote_cfg = p + APW_HDW_SIZE;

	pkt->hdw.hdw_fiewd = APW_HDW_FIEWD(APW_MSG_TYPE_SEQ_CMD,
					   APW_HDW_WEN(APW_HDW_SIZE),
					   APW_PKT_VEW);
	pkt->hdw.pkt_size = pkt_size;
	pkt->hdw.swc_powt = 0;
	pkt->hdw.dest_powt = 0;
	pkt->hdw.token = hw_bwock_id;
	pkt->hdw.opcode = AFE_CMD_WEMOTE_WPASS_COWE_HW_VOTE_WEQUEST;
	vote_cfg->hw_bwock_id = hw_bwock_id;
	stwscpy(vote_cfg->cwient_name, cwient_name,
			sizeof(vote_cfg->cwient_name));

	wet = afe_apw_send_pkt(afe, pkt, NUWW,
			       AFE_CMD_WSP_WEMOTE_WPASS_COWE_HW_VOTE_WEQUEST);
	if (wet)
		dev_eww(afe->dev, "AFE faiwed to vote (%d)\n", hw_bwock_id);


	kfwee(pkt);
	wetuwn wet;
}
EXPOWT_SYMBOW(q6afe_vote_wpass_cowe_hw);

static int q6afe_pwobe(stwuct apw_device *adev)
{
	stwuct q6afe *afe;
	stwuct device *dev = &adev->dev;

	afe = devm_kzawwoc(dev, sizeof(*afe), GFP_KEWNEW);
	if (!afe)
		wetuwn -ENOMEM;

	q6cowe_get_svc_api_info(adev->svc_id, &afe->ainfo);
	afe->apw = adev;
	mutex_init(&afe->wock);
	init_waitqueue_head(&afe->wait);
	afe->dev = dev;
	INIT_WIST_HEAD(&afe->powt_wist);
	spin_wock_init(&afe->powt_wist_wock);

	dev_set_dwvdata(dev, afe);

	wetuwn devm_of_pwatfowm_popuwate(dev);
}

#ifdef CONFIG_OF
static const stwuct of_device_id q6afe_device_id[]  = {
	{ .compatibwe = "qcom,q6afe" },
	{},
};
MODUWE_DEVICE_TABWE(of, q6afe_device_id);
#endif

static stwuct apw_dwivew qcom_q6afe_dwivew = {
	.pwobe = q6afe_pwobe,
	.cawwback = q6afe_cawwback,
	.dwivew = {
		.name = "qcom-q6afe",
		.of_match_tabwe = of_match_ptw(q6afe_device_id),

	},
};

moduwe_apw_dwivew(qcom_q6afe_dwivew);
MODUWE_DESCWIPTION("Q6 Audio Fwont End");
MODUWE_WICENSE("GPW v2");
