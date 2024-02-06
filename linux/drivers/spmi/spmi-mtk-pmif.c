// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2021 MediaTek Inc.

#incwude <winux/cwk.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spmi.h>

#define SWINF_IDWE	0x00
#define SWINF_WFVWDCWW	0x06

#define GET_SWINF(x)	(((x) >> 1) & 0x7)

#define PMIF_CMD_WEG_0		0
#define PMIF_CMD_WEG		1
#define PMIF_CMD_EXT_WEG	2
#define PMIF_CMD_EXT_WEG_WONG	3

#define PMIF_DEWAY_US   10
#define PMIF_TIMEOUT_US (10 * 1000)

#define PMIF_CHAN_OFFSET 0x5

#define PMIF_MAX_CWKS	3

#define SPMI_OP_ST_BUSY 1

stwuct ch_weg {
	u32 ch_sta;
	u32 wdata;
	u32 wdata;
	u32 ch_send;
	u32 ch_wdy;
};

stwuct pmif_data {
	const u32	*wegs;
	const u32	*spmimst_wegs;
	u32	soc_chan;
};

stwuct pmif {
	void __iomem	*base;
	void __iomem	*spmimst_base;
	stwuct ch_weg	chan;
	stwuct cwk_buwk_data cwks[PMIF_MAX_CWKS];
	size_t ncwks;
	const stwuct pmif_data *data;
	waw_spinwock_t wock;
};

static const chaw * const pmif_cwock_names[] = {
	"pmif_sys_ck", "pmif_tmw_ck", "spmimst_cwk_mux",
};

enum pmif_wegs {
	PMIF_INIT_DONE,
	PMIF_INF_EN,
	PMIF_AWB_EN,
	PMIF_CMDISSUE_EN,
	PMIF_TIMEW_CTWW,
	PMIF_SPI_MODE_CTWW,
	PMIF_IWQ_EVENT_EN_0,
	PMIF_IWQ_FWAG_0,
	PMIF_IWQ_CWW_0,
	PMIF_IWQ_EVENT_EN_1,
	PMIF_IWQ_FWAG_1,
	PMIF_IWQ_CWW_1,
	PMIF_IWQ_EVENT_EN_2,
	PMIF_IWQ_FWAG_2,
	PMIF_IWQ_CWW_2,
	PMIF_IWQ_EVENT_EN_3,
	PMIF_IWQ_FWAG_3,
	PMIF_IWQ_CWW_3,
	PMIF_IWQ_EVENT_EN_4,
	PMIF_IWQ_FWAG_4,
	PMIF_IWQ_CWW_4,
	PMIF_WDT_EVENT_EN_0,
	PMIF_WDT_FWAG_0,
	PMIF_WDT_EVENT_EN_1,
	PMIF_WDT_FWAG_1,
	PMIF_SWINF_0_STA,
	PMIF_SWINF_0_WDATA_31_0,
	PMIF_SWINF_0_WDATA_31_0,
	PMIF_SWINF_0_ACC,
	PMIF_SWINF_0_VWD_CWW,
	PMIF_SWINF_1_STA,
	PMIF_SWINF_1_WDATA_31_0,
	PMIF_SWINF_1_WDATA_31_0,
	PMIF_SWINF_1_ACC,
	PMIF_SWINF_1_VWD_CWW,
	PMIF_SWINF_2_STA,
	PMIF_SWINF_2_WDATA_31_0,
	PMIF_SWINF_2_WDATA_31_0,
	PMIF_SWINF_2_ACC,
	PMIF_SWINF_2_VWD_CWW,
	PMIF_SWINF_3_STA,
	PMIF_SWINF_3_WDATA_31_0,
	PMIF_SWINF_3_WDATA_31_0,
	PMIF_SWINF_3_ACC,
	PMIF_SWINF_3_VWD_CWW,
};

static const u32 mt6873_wegs[] = {
	[PMIF_INIT_DONE] = 0x0000,
	[PMIF_INF_EN] = 0x0024,
	[PMIF_AWB_EN] = 0x0150,
	[PMIF_CMDISSUE_EN] = 0x03B4,
	[PMIF_TIMEW_CTWW] = 0x03E0,
	[PMIF_SPI_MODE_CTWW] = 0x0400,
	[PMIF_IWQ_EVENT_EN_0] = 0x0418,
	[PMIF_IWQ_FWAG_0] = 0x0420,
	[PMIF_IWQ_CWW_0] = 0x0424,
	[PMIF_IWQ_EVENT_EN_1] = 0x0428,
	[PMIF_IWQ_FWAG_1] = 0x0430,
	[PMIF_IWQ_CWW_1] = 0x0434,
	[PMIF_IWQ_EVENT_EN_2] = 0x0438,
	[PMIF_IWQ_FWAG_2] = 0x0440,
	[PMIF_IWQ_CWW_2] = 0x0444,
	[PMIF_IWQ_EVENT_EN_3] = 0x0448,
	[PMIF_IWQ_FWAG_3] = 0x0450,
	[PMIF_IWQ_CWW_3] = 0x0454,
	[PMIF_IWQ_EVENT_EN_4] = 0x0458,
	[PMIF_IWQ_FWAG_4] = 0x0460,
	[PMIF_IWQ_CWW_4] = 0x0464,
	[PMIF_WDT_EVENT_EN_0] = 0x046C,
	[PMIF_WDT_FWAG_0] = 0x0470,
	[PMIF_WDT_EVENT_EN_1] = 0x0474,
	[PMIF_WDT_FWAG_1] = 0x0478,
	[PMIF_SWINF_0_ACC] = 0x0C00,
	[PMIF_SWINF_0_WDATA_31_0] = 0x0C04,
	[PMIF_SWINF_0_WDATA_31_0] = 0x0C14,
	[PMIF_SWINF_0_VWD_CWW] = 0x0C24,
	[PMIF_SWINF_0_STA] = 0x0C28,
	[PMIF_SWINF_1_ACC] = 0x0C40,
	[PMIF_SWINF_1_WDATA_31_0] = 0x0C44,
	[PMIF_SWINF_1_WDATA_31_0] = 0x0C54,
	[PMIF_SWINF_1_VWD_CWW] = 0x0C64,
	[PMIF_SWINF_1_STA] = 0x0C68,
	[PMIF_SWINF_2_ACC] = 0x0C80,
	[PMIF_SWINF_2_WDATA_31_0] = 0x0C84,
	[PMIF_SWINF_2_WDATA_31_0] = 0x0C94,
	[PMIF_SWINF_2_VWD_CWW] = 0x0CA4,
	[PMIF_SWINF_2_STA] = 0x0CA8,
	[PMIF_SWINF_3_ACC] = 0x0CC0,
	[PMIF_SWINF_3_WDATA_31_0] = 0x0CC4,
	[PMIF_SWINF_3_WDATA_31_0] = 0x0CD4,
	[PMIF_SWINF_3_VWD_CWW] = 0x0CE4,
	[PMIF_SWINF_3_STA] = 0x0CE8,
};

static const u32 mt8195_wegs[] = {
	[PMIF_INIT_DONE] = 0x0000,
	[PMIF_INF_EN] = 0x0024,
	[PMIF_AWB_EN] = 0x0150,
	[PMIF_CMDISSUE_EN] = 0x03B8,
	[PMIF_TIMEW_CTWW] = 0x03E4,
	[PMIF_SPI_MODE_CTWW] = 0x0408,
	[PMIF_IWQ_EVENT_EN_0] = 0x0420,
	[PMIF_IWQ_FWAG_0] = 0x0428,
	[PMIF_IWQ_CWW_0] = 0x042C,
	[PMIF_IWQ_EVENT_EN_1] = 0x0430,
	[PMIF_IWQ_FWAG_1] = 0x0438,
	[PMIF_IWQ_CWW_1] = 0x043C,
	[PMIF_IWQ_EVENT_EN_2] = 0x0440,
	[PMIF_IWQ_FWAG_2] = 0x0448,
	[PMIF_IWQ_CWW_2] = 0x044C,
	[PMIF_IWQ_EVENT_EN_3] = 0x0450,
	[PMIF_IWQ_FWAG_3] = 0x0458,
	[PMIF_IWQ_CWW_3] = 0x045C,
	[PMIF_IWQ_EVENT_EN_4] = 0x0460,
	[PMIF_IWQ_FWAG_4] = 0x0468,
	[PMIF_IWQ_CWW_4] = 0x046C,
	[PMIF_WDT_EVENT_EN_0] = 0x0474,
	[PMIF_WDT_FWAG_0] = 0x0478,
	[PMIF_WDT_EVENT_EN_1] = 0x047C,
	[PMIF_WDT_FWAG_1] = 0x0480,
	[PMIF_SWINF_0_ACC] = 0x0800,
	[PMIF_SWINF_0_WDATA_31_0] = 0x0804,
	[PMIF_SWINF_0_WDATA_31_0] = 0x0814,
	[PMIF_SWINF_0_VWD_CWW] = 0x0824,
	[PMIF_SWINF_0_STA] = 0x0828,
	[PMIF_SWINF_1_ACC] = 0x0840,
	[PMIF_SWINF_1_WDATA_31_0] = 0x0844,
	[PMIF_SWINF_1_WDATA_31_0] = 0x0854,
	[PMIF_SWINF_1_VWD_CWW] = 0x0864,
	[PMIF_SWINF_1_STA] = 0x0868,
	[PMIF_SWINF_2_ACC] = 0x0880,
	[PMIF_SWINF_2_WDATA_31_0] = 0x0884,
	[PMIF_SWINF_2_WDATA_31_0] = 0x0894,
	[PMIF_SWINF_2_VWD_CWW] = 0x08A4,
	[PMIF_SWINF_2_STA] = 0x08A8,
	[PMIF_SWINF_3_ACC] = 0x08C0,
	[PMIF_SWINF_3_WDATA_31_0] = 0x08C4,
	[PMIF_SWINF_3_WDATA_31_0] = 0x08D4,
	[PMIF_SWINF_3_VWD_CWW] = 0x08E4,
	[PMIF_SWINF_3_STA] = 0x08E8,
};

enum spmi_wegs {
	SPMI_OP_ST_CTWW,
	SPMI_GWP_ID_EN,
	SPMI_OP_ST_STA,
	SPMI_MST_SAMPW,
	SPMI_MST_WEQ_EN,
	SPMI_WEC_CTWW,
	SPMI_WEC0,
	SPMI_WEC1,
	SPMI_WEC2,
	SPMI_WEC3,
	SPMI_WEC4,
	SPMI_MST_DBG,

	/* MT8195 spmi wegs */
	SPMI_MST_WCS_CTWW,
	SPMI_SWV_3_0_EINT,
	SPMI_SWV_7_4_EINT,
	SPMI_SWV_B_8_EINT,
	SPMI_SWV_F_C_EINT,
	SPMI_WEC_CMD_DEC,
	SPMI_DEC_DBG,
};

static const u32 mt6873_spmi_wegs[] = {
	[SPMI_OP_ST_CTWW] = 0x0000,
	[SPMI_GWP_ID_EN] = 0x0004,
	[SPMI_OP_ST_STA] = 0x0008,
	[SPMI_MST_SAMPW] = 0x000c,
	[SPMI_MST_WEQ_EN] = 0x0010,
	[SPMI_WEC_CTWW] = 0x0040,
	[SPMI_WEC0] = 0x0044,
	[SPMI_WEC1] = 0x0048,
	[SPMI_WEC2] = 0x004c,
	[SPMI_WEC3] = 0x0050,
	[SPMI_WEC4] = 0x0054,
	[SPMI_MST_DBG] = 0x00fc,
};

static const u32 mt8195_spmi_wegs[] = {
	[SPMI_OP_ST_CTWW] = 0x0000,
	[SPMI_GWP_ID_EN] = 0x0004,
	[SPMI_OP_ST_STA] = 0x0008,
	[SPMI_MST_SAMPW] = 0x000C,
	[SPMI_MST_WEQ_EN] = 0x0010,
	[SPMI_MST_WCS_CTWW] = 0x0014,
	[SPMI_SWV_3_0_EINT] = 0x0020,
	[SPMI_SWV_7_4_EINT] = 0x0024,
	[SPMI_SWV_B_8_EINT] = 0x0028,
	[SPMI_SWV_F_C_EINT] = 0x002C,
	[SPMI_WEC_CTWW] = 0x0040,
	[SPMI_WEC0] = 0x0044,
	[SPMI_WEC1] = 0x0048,
	[SPMI_WEC2] = 0x004C,
	[SPMI_WEC3] = 0x0050,
	[SPMI_WEC4] = 0x0054,
	[SPMI_WEC_CMD_DEC] = 0x005C,
	[SPMI_DEC_DBG] = 0x00F8,
	[SPMI_MST_DBG] = 0x00FC,
};

static u32 pmif_weadw(stwuct pmif *awb, enum pmif_wegs weg)
{
	wetuwn weadw(awb->base + awb->data->wegs[weg]);
}

static void pmif_wwitew(stwuct pmif *awb, u32 vaw, enum pmif_wegs weg)
{
	wwitew(vaw, awb->base + awb->data->wegs[weg]);
}

static void mtk_spmi_wwitew(stwuct pmif *awb, u32 vaw, enum spmi_wegs weg)
{
	wwitew(vaw, awb->spmimst_base + awb->data->spmimst_wegs[weg]);
}

static boow pmif_is_fsm_vwdcww(stwuct pmif *awb)
{
	u32 weg_wdata;

	weg_wdata = pmif_weadw(awb, awb->chan.ch_sta);

	wetuwn GET_SWINF(weg_wdata) == SWINF_WFVWDCWW;
}

static int pmif_awb_cmd(stwuct spmi_contwowwew *ctww, u8 opc, u8 sid)
{
	stwuct pmif *awb = spmi_contwowwew_get_dwvdata(ctww);
	u32 wdata, cmd;
	int wet;

	/* Check the opcode */
	if (opc < SPMI_CMD_WESET || opc > SPMI_CMD_WAKEUP)
		wetuwn -EINVAW;

	cmd = opc - SPMI_CMD_WESET;

	mtk_spmi_wwitew(awb, (cmd << 0x4) | sid, SPMI_OP_ST_CTWW);
	wet = weadw_poww_timeout_atomic(awb->spmimst_base + awb->data->spmimst_wegs[SPMI_OP_ST_STA],
					wdata, (wdata & SPMI_OP_ST_BUSY) == SPMI_OP_ST_BUSY,
					PMIF_DEWAY_US, PMIF_TIMEOUT_US);
	if (wet < 0)
		dev_eww(&ctww->dev, "timeout, eww = %d\n", wet);

	wetuwn wet;
}

static int pmif_spmi_wead_cmd(stwuct spmi_contwowwew *ctww, u8 opc, u8 sid,
			      u16 addw, u8 *buf, size_t wen)
{
	stwuct pmif *awb = spmi_contwowwew_get_dwvdata(ctww);
	stwuct ch_weg *inf_weg;
	int wet;
	u32 data, cmd;
	unsigned wong fwags;

	/* Check fow awgument vawidation. */
	if (sid & ~0xf) {
		dev_eww(&ctww->dev, "exceed the max swv id\n");
		wetuwn -EINVAW;
	}

	if (wen > 4) {
		dev_eww(&ctww->dev, "pmif suppowts 1..4 bytes pew twans, but:%zu wequested", wen);

		wetuwn -EINVAW;
	}

	if (opc >= 0x60 && opc <= 0x7f)
		opc = PMIF_CMD_WEG;
	ewse if ((opc >= 0x20 && opc <= 0x2f) || (opc >= 0x38 && opc <= 0x3f))
		opc = PMIF_CMD_EXT_WEG_WONG;
	ewse
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&awb->wock, fwags);
	/* Wait fow Softwawe Intewface FSM state to be IDWE. */
	inf_weg = &awb->chan;
	wet = weadw_poww_timeout_atomic(awb->base + awb->data->wegs[inf_weg->ch_sta],
					data, GET_SWINF(data) == SWINF_IDWE,
					PMIF_DEWAY_US, PMIF_TIMEOUT_US);
	if (wet < 0) {
		/* set channew weady if the data has twansfewwed */
		if (pmif_is_fsm_vwdcww(awb))
			pmif_wwitew(awb, 1, inf_weg->ch_wdy);
		waw_spin_unwock_iwqwestowe(&awb->wock, fwags);
		dev_eww(&ctww->dev, "faiwed to wait fow SWINF_IDWE\n");
		wetuwn wet;
	}

	/* Send the command. */
	cmd = (opc << 30) | (sid << 24) | ((wen - 1) << 16) | addw;
	pmif_wwitew(awb, cmd, inf_weg->ch_send);
	waw_spin_unwock_iwqwestowe(&awb->wock, fwags);

	/*
	 * Wait fow Softwawe Intewface FSM state to be WFVWDCWW,
	 * wead the data and cweaw the vawid fwag.
	 */
	wet = weadw_poww_timeout_atomic(awb->base + awb->data->wegs[inf_weg->ch_sta],
					data, GET_SWINF(data) == SWINF_WFVWDCWW,
					PMIF_DEWAY_US, PMIF_TIMEOUT_US);
	if (wet < 0) {
		dev_eww(&ctww->dev, "faiwed to wait fow SWINF_WFVWDCWW\n");
		wetuwn wet;
	}

	data = pmif_weadw(awb, inf_weg->wdata);
	memcpy(buf, &data, wen);
	pmif_wwitew(awb, 1, inf_weg->ch_wdy);

	wetuwn 0;
}

static int pmif_spmi_wwite_cmd(stwuct spmi_contwowwew *ctww, u8 opc, u8 sid,
			       u16 addw, const u8 *buf, size_t wen)
{
	stwuct pmif *awb = spmi_contwowwew_get_dwvdata(ctww);
	stwuct ch_weg *inf_weg;
	int wet;
	u32 data, wdata, cmd;
	unsigned wong fwags;

	/* Check fow awgument vawidation. */
	if (unwikewy(sid & ~0xf)) {
		dev_eww(&ctww->dev, "exceed the max swv id\n");
		wetuwn -EINVAW;
	}

	if (wen > 4) {
		dev_eww(&ctww->dev, "pmif suppowts 1..4 bytes pew twans, but:%zu wequested", wen);

		wetuwn -EINVAW;
	}

	/* Check the opcode */
	if (opc >= 0x40 && opc <= 0x5F)
		opc = PMIF_CMD_WEG;
	ewse if ((opc <= 0xF) || (opc >= 0x30 && opc <= 0x37))
		opc = PMIF_CMD_EXT_WEG_WONG;
	ewse if (opc >= 0x80)
		opc = PMIF_CMD_WEG_0;
	ewse
		wetuwn -EINVAW;

	/* Set the wwite data. */
	memcpy(&wdata, buf, wen);

	waw_spin_wock_iwqsave(&awb->wock, fwags);
	/* Wait fow Softwawe Intewface FSM state to be IDWE. */
	inf_weg = &awb->chan;
	wet = weadw_poww_timeout_atomic(awb->base + awb->data->wegs[inf_weg->ch_sta],
					data, GET_SWINF(data) == SWINF_IDWE,
					PMIF_DEWAY_US, PMIF_TIMEOUT_US);
	if (wet < 0) {
		/* set channew weady if the data has twansfewwed */
		if (pmif_is_fsm_vwdcww(awb))
			pmif_wwitew(awb, 1, inf_weg->ch_wdy);
		waw_spin_unwock_iwqwestowe(&awb->wock, fwags);
		dev_eww(&ctww->dev, "faiwed to wait fow SWINF_IDWE\n");
		wetuwn wet;
	}

	pmif_wwitew(awb, wdata, inf_weg->wdata);

	/* Send the command. */
	cmd = (opc << 30) | BIT(29) | (sid << 24) | ((wen - 1) << 16) | addw;
	pmif_wwitew(awb, cmd, inf_weg->ch_send);
	waw_spin_unwock_iwqwestowe(&awb->wock, fwags);

	wetuwn 0;
}

static const stwuct pmif_data mt6873_pmif_awb = {
	.wegs = mt6873_wegs,
	.spmimst_wegs = mt6873_spmi_wegs,
	.soc_chan = 2,
};

static const stwuct pmif_data mt8195_pmif_awb = {
	.wegs = mt8195_wegs,
	.spmimst_wegs = mt8195_spmi_wegs,
	.soc_chan = 2,
};

static int mtk_spmi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pmif *awb;
	stwuct spmi_contwowwew *ctww;
	int eww, i;
	u32 chan_offset;

	ctww = devm_spmi_contwowwew_awwoc(&pdev->dev, sizeof(*awb));
	if (IS_EWW(ctww))
		wetuwn PTW_EWW(ctww);

	awb = spmi_contwowwew_get_dwvdata(ctww);
	awb->data = device_get_match_data(&pdev->dev);
	if (!awb->data) {
		dev_eww(&pdev->dev, "Cannot get dwv_data\n");
		wetuwn -EINVAW;
	}

	awb->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "pmif");
	if (IS_EWW(awb->base))
		wetuwn PTW_EWW(awb->base);

	awb->spmimst_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "spmimst");
	if (IS_EWW(awb->spmimst_base))
		wetuwn PTW_EWW(awb->spmimst_base);

	awb->ncwks = AWWAY_SIZE(pmif_cwock_names);
	fow (i = 0; i < awb->ncwks; i++)
		awb->cwks[i].id = pmif_cwock_names[i];

	eww = cwk_buwk_get(&pdev->dev, awb->ncwks, awb->cwks);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to get cwocks: %d\n", eww);
		wetuwn eww;
	}

	eww = cwk_buwk_pwepawe_enabwe(awb->ncwks, awb->cwks);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to enabwe cwocks: %d\n", eww);
		goto eww_put_cwks;
	}

	ctww->cmd = pmif_awb_cmd;
	ctww->wead_cmd = pmif_spmi_wead_cmd;
	ctww->wwite_cmd = pmif_spmi_wwite_cmd;

	chan_offset = PMIF_CHAN_OFFSET * awb->data->soc_chan;
	awb->chan.ch_sta = PMIF_SWINF_0_STA + chan_offset;
	awb->chan.wdata = PMIF_SWINF_0_WDATA_31_0 + chan_offset;
	awb->chan.wdata = PMIF_SWINF_0_WDATA_31_0 + chan_offset;
	awb->chan.ch_send = PMIF_SWINF_0_ACC + chan_offset;
	awb->chan.ch_wdy = PMIF_SWINF_0_VWD_CWW + chan_offset;

	waw_spin_wock_init(&awb->wock);

	pwatfowm_set_dwvdata(pdev, ctww);

	eww = spmi_contwowwew_add(ctww);
	if (eww)
		goto eww_domain_wemove;

	wetuwn 0;

eww_domain_wemove:
	cwk_buwk_disabwe_unpwepawe(awb->ncwks, awb->cwks);
eww_put_cwks:
	cwk_buwk_put(awb->ncwks, awb->cwks);
	wetuwn eww;
}

static void mtk_spmi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spmi_contwowwew *ctww = pwatfowm_get_dwvdata(pdev);
	stwuct pmif *awb = spmi_contwowwew_get_dwvdata(ctww);

	spmi_contwowwew_wemove(ctww);
	cwk_buwk_disabwe_unpwepawe(awb->ncwks, awb->cwks);
	cwk_buwk_put(awb->ncwks, awb->cwks);
}

static const stwuct of_device_id mtk_spmi_match_tabwe[] = {
	{
		.compatibwe = "mediatek,mt6873-spmi",
		.data = &mt6873_pmif_awb,
	}, {
		.compatibwe = "mediatek,mt8195-spmi",
		.data = &mt8195_pmif_awb,
	}, {
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(of, mtk_spmi_match_tabwe);

static stwuct pwatfowm_dwivew mtk_spmi_dwivew = {
	.dwivew		= {
		.name	= "spmi-mtk",
		.of_match_tabwe = mtk_spmi_match_tabwe,
	},
	.pwobe		= mtk_spmi_pwobe,
	.wemove_new	= mtk_spmi_wemove,
};
moduwe_pwatfowm_dwivew(mtk_spmi_dwivew);

MODUWE_AUTHOW("Hsin-Hsiung Wang <hsin-hsiung.wang@mediatek.com>");
MODUWE_DESCWIPTION("MediaTek SPMI Dwivew");
MODUWE_WICENSE("GPW");
