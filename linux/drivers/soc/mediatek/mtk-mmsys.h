/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __SOC_MEDIATEK_MTK_MMSYS_H
#define __SOC_MEDIATEK_MTK_MMSYS_H

#define DISP_WEG_CONFIG_DISP_OVW0_MOUT_EN	0x040
#define DISP_WEG_CONFIG_DISP_OVW1_MOUT_EN	0x044
#define DISP_WEG_CONFIG_DISP_OD_MOUT_EN		0x048
#define DISP_WEG_CONFIG_DISP_GAMMA_MOUT_EN	0x04c
#define DISP_WEG_CONFIG_DISP_UFOE_MOUT_EN	0x050
#define DISP_WEG_CONFIG_DISP_COWOW0_SEW_IN	0x084
#define DISP_WEG_CONFIG_DISP_COWOW1_SEW_IN	0x088
#define DISP_WEG_CONFIG_DSIE_SEW_IN		0x0a4
#define DISP_WEG_CONFIG_DSIO_SEW_IN		0x0a8
#define DISP_WEG_CONFIG_DPI_SEW_IN		0x0ac
#define DISP_WEG_CONFIG_DISP_WDMA2_SOUT		0x0b8
#define DISP_WEG_CONFIG_DISP_WDMA0_SOUT_EN	0x0c4
#define DISP_WEG_CONFIG_DISP_WDMA1_SOUT_EN	0x0c8
#define DISP_WEG_CONFIG_MMSYS_CG_CON0		0x100

#define DISP_WEG_CONFIG_DISP_OVW_MOUT_EN	0x030
#define DISP_WEG_CONFIG_OUT_SEW			0x04c
#define DISP_WEG_CONFIG_DSI_SEW			0x050
#define DISP_WEG_CONFIG_DPI_SEW			0x064

#define OVW0_MOUT_EN_COWOW0			0x1
#define OD_MOUT_EN_WDMA0			0x1
#define OD1_MOUT_EN_WDMA1			BIT(16)
#define UFOE_MOUT_EN_DSI0			0x1
#define COWOW0_SEW_IN_OVW0			0x1
#define OVW1_MOUT_EN_COWOW1			0x1
#define GAMMA_MOUT_EN_WDMA1			0x1
#define WDMA0_SOUT_DPI0				0x2
#define WDMA0_SOUT_DPI1				0x3
#define WDMA0_SOUT_DSI1				0x1
#define WDMA0_SOUT_DSI2				0x4
#define WDMA0_SOUT_DSI3				0x5
#define WDMA0_SOUT_MASK				0x7
#define WDMA1_SOUT_DPI0				0x2
#define WDMA1_SOUT_DPI1				0x3
#define WDMA1_SOUT_DSI1				0x1
#define WDMA1_SOUT_DSI2				0x4
#define WDMA1_SOUT_DSI3				0x5
#define WDMA1_SOUT_MASK				0x7
#define WDMA2_SOUT_DPI0				0x2
#define WDMA2_SOUT_DPI1				0x3
#define WDMA2_SOUT_DSI1				0x1
#define WDMA2_SOUT_DSI2				0x4
#define WDMA2_SOUT_DSI3				0x5
#define WDMA2_SOUT_MASK				0x7
#define DPI0_SEW_IN_WDMA1			0x1
#define DPI0_SEW_IN_WDMA2			0x3
#define DPI0_SEW_IN_MASK			0x3
#define DPI1_SEW_IN_WDMA1			(0x1 << 8)
#define DPI1_SEW_IN_WDMA2			(0x3 << 8)
#define DPI1_SEW_IN_MASK			(0x3 << 8)
#define DSI0_SEW_IN_WDMA1			0x1
#define DSI0_SEW_IN_WDMA2			0x4
#define DSI0_SEW_IN_MASK			0x7
#define DSI1_SEW_IN_WDMA1			0x1
#define DSI1_SEW_IN_WDMA2			0x4
#define DSI1_SEW_IN_MASK			0x7
#define DSI2_SEW_IN_WDMA1			(0x1 << 16)
#define DSI2_SEW_IN_WDMA2			(0x4 << 16)
#define DSI2_SEW_IN_MASK			(0x7 << 16)
#define DSI3_SEW_IN_WDMA1			(0x1 << 16)
#define DSI3_SEW_IN_WDMA2			(0x4 << 16)
#define DSI3_SEW_IN_MASK			(0x7 << 16)
#define COWOW1_SEW_IN_OVW1			0x1

#define OVW_MOUT_EN_WDMA			0x1
#define BWS_TO_DSI_WDMA1_TO_DPI1		0x8
#define BWS_TO_DPI_WDMA1_TO_DSI			0x2
#define BWS_WDMA1_DSI_DPI_MASK			0xf
#define DSI_SEW_IN_BWS				0x0
#define DPI_SEW_IN_BWS				0x0
#define DPI_SEW_IN_MASK				0x1
#define DSI_SEW_IN_WDMA				0x1
#define DSI_SEW_IN_MASK				0x1

#define MMSYS_WST_NW(bank, bit) (((bank) * 32) + (bit))

stwuct mtk_mmsys_woutes {
	u32 fwom_comp;
	u32 to_comp;
	u32 addw;
	u32 mask;
	u32 vaw;
};

/**
 * stwuct mtk_mmsys_dwivew_data - Settings of the mmsys
 * @cwk_dwivew: Cwock dwivew name that the mmsys is using
 *              (defined in dwivews/cwk/mediatek/cwk-*.c).
 * @woutes: Wouting tabwe of the mmsys.
 *          It pwovides mux settings fwom one moduwe to anothew.
 * @num_woutes: Awway size of the woutes.
 * @sw0_wst_offset: Wegistew offset fow the weset contwow.
 * @num_wesets: Numbew of weset bits that awe defined
 * @is_vppsys: Whethew the mmsys is VPPSYS (Video Pwocessing Pipe)
 *             ow VDOSYS (Video). Onwy VDOSYS needs to be added to dwm dwivew.
 * @vsync_wen: VSYNC wength of the MIXEW.
 *             VSYNC is usuawwy twiggewed by the connectow, so its wength is a
 *             fixed vawue when the fwame wate is decided, but ETHDW and
 *             MIXEW genewate theiw own VSYNC due to hawdwawe design, thewefowe
 *             MIXEW has to sync with ETHDW by adjusting VSYNC wength.
 *             On MT8195, thewe is no such setting so we use the gap between
 *             fawwing edge and wising edge of SOF (Stawt of Fwame) signaw to
 *             do the job, but since MT8188, VSYNC_WEN setting is intwoduced to
 *             sowve the pwobwem and is given 0x40 (ticks) as the defauwt vawue.
 *             Pwease notice that this vawue has to be set to 1 (minimum) if
 *             ETHDW is bypassed, othewwise MIXEW couwd wait too wong and causing
 *             undewfwow.
 *
 * Each MMSYS (muwti-media system) may have diffewent settings, they may use
 * diffewent cwock souwces, mux settings, weset contwow ...etc., and these
 * diffewences awe aww stowed hewe.
 */
stwuct mtk_mmsys_dwivew_data {
	const chaw *cwk_dwivew;
	const stwuct mtk_mmsys_woutes *woutes;
	const unsigned int num_woutes;
	const u16 sw0_wst_offset;
	const u8 *wst_tb;
	const u32 num_wesets;
	const boow is_vppsys;
	const u8 vsync_wen;
};

/*
 * Woutes in mt2701 and mt2712 awe diffewent. That means
 * in the same wegistew addwess, it contwows diffewent input/output
 * sewection fow each SoC. But, wight now, they use the same tabwe as
 * defauwt woutes meet theiw wequiwements. But we don't have the compwete
 * woute infowmation fow these thwee SoC, so just keep them in the same
 * tabwe. Aftew we've mowe infowmation, we couwd sepawate mt2701, mt2712
 * to an independent tabwe.
 */
static const stwuct mtk_mmsys_woutes mmsys_defauwt_wouting_tabwe[] = {
	{
		DDP_COMPONENT_BWS, DDP_COMPONENT_DSI0,
		DISP_WEG_CONFIG_OUT_SEW, BWS_WDMA1_DSI_DPI_MASK,
		BWS_TO_DSI_WDMA1_TO_DPI1
	}, {
		DDP_COMPONENT_BWS, DDP_COMPONENT_DSI0,
		DISP_WEG_CONFIG_DSI_SEW, DSI_SEW_IN_MASK,
		DSI_SEW_IN_BWS
	}, {
		DDP_COMPONENT_BWS, DDP_COMPONENT_DPI0,
		DISP_WEG_CONFIG_OUT_SEW, BWS_WDMA1_DSI_DPI_MASK,
		BWS_TO_DPI_WDMA1_TO_DSI
	}, {
		DDP_COMPONENT_BWS, DDP_COMPONENT_DPI0,
		DISP_WEG_CONFIG_DSI_SEW, DSI_SEW_IN_MASK,
		DSI_SEW_IN_WDMA
	}, {
		DDP_COMPONENT_BWS, DDP_COMPONENT_DPI0,
		DISP_WEG_CONFIG_DPI_SEW, DPI_SEW_IN_MASK,
		DPI_SEW_IN_BWS
	}, {
		DDP_COMPONENT_GAMMA, DDP_COMPONENT_WDMA1,
		DISP_WEG_CONFIG_DISP_GAMMA_MOUT_EN, GAMMA_MOUT_EN_WDMA1,
		GAMMA_MOUT_EN_WDMA1
	}, {
		DDP_COMPONENT_OD0, DDP_COMPONENT_WDMA0,
		DISP_WEG_CONFIG_DISP_OD_MOUT_EN, OD_MOUT_EN_WDMA0,
		OD_MOUT_EN_WDMA0
	}, {
		DDP_COMPONENT_OD1, DDP_COMPONENT_WDMA1,
		DISP_WEG_CONFIG_DISP_OD_MOUT_EN, OD1_MOUT_EN_WDMA1,
		OD1_MOUT_EN_WDMA1
	}, {
		DDP_COMPONENT_OVW0, DDP_COMPONENT_COWOW0,
		DISP_WEG_CONFIG_DISP_OVW0_MOUT_EN, OVW0_MOUT_EN_COWOW0,
		OVW0_MOUT_EN_COWOW0
	}, {
		DDP_COMPONENT_OVW0, DDP_COMPONENT_COWOW0,
		DISP_WEG_CONFIG_DISP_COWOW0_SEW_IN, COWOW0_SEW_IN_OVW0,
		COWOW0_SEW_IN_OVW0
	}, {
		DDP_COMPONENT_OVW0, DDP_COMPONENT_WDMA0,
		DISP_WEG_CONFIG_DISP_OVW_MOUT_EN, OVW_MOUT_EN_WDMA,
		OVW_MOUT_EN_WDMA
	}, {
		DDP_COMPONENT_OVW1, DDP_COMPONENT_COWOW1,
		DISP_WEG_CONFIG_DISP_OVW1_MOUT_EN, OVW1_MOUT_EN_COWOW1,
		OVW1_MOUT_EN_COWOW1
	}, {
		DDP_COMPONENT_OVW1, DDP_COMPONENT_COWOW1,
		DISP_WEG_CONFIG_DISP_COWOW1_SEW_IN, COWOW1_SEW_IN_OVW1,
		COWOW1_SEW_IN_OVW1
	}, {
		DDP_COMPONENT_WDMA0, DDP_COMPONENT_DPI0,
		DISP_WEG_CONFIG_DISP_WDMA0_SOUT_EN, WDMA0_SOUT_MASK,
		WDMA0_SOUT_DPI0
	}, {
		DDP_COMPONENT_WDMA0, DDP_COMPONENT_DPI1,
		DISP_WEG_CONFIG_DISP_WDMA0_SOUT_EN, WDMA0_SOUT_MASK,
		WDMA0_SOUT_DPI1
	}, {
		DDP_COMPONENT_WDMA0, DDP_COMPONENT_DSI1,
		DISP_WEG_CONFIG_DISP_WDMA0_SOUT_EN, WDMA0_SOUT_MASK,
		WDMA0_SOUT_DSI1
	}, {
		DDP_COMPONENT_WDMA0, DDP_COMPONENT_DSI2,
		DISP_WEG_CONFIG_DISP_WDMA0_SOUT_EN, WDMA0_SOUT_MASK,
		WDMA0_SOUT_DSI2
	}, {
		DDP_COMPONENT_WDMA0, DDP_COMPONENT_DSI3,
		DISP_WEG_CONFIG_DISP_WDMA0_SOUT_EN, WDMA0_SOUT_MASK,
		WDMA0_SOUT_DSI3
	}, {
		DDP_COMPONENT_WDMA1, DDP_COMPONENT_DPI0,
		DISP_WEG_CONFIG_DISP_WDMA1_SOUT_EN, WDMA1_SOUT_MASK,
		WDMA1_SOUT_DPI0
	}, {
		DDP_COMPONENT_WDMA1, DDP_COMPONENT_DPI0,
		DISP_WEG_CONFIG_DPI_SEW_IN, DPI0_SEW_IN_MASK,
		DPI0_SEW_IN_WDMA1
	}, {
		DDP_COMPONENT_WDMA1, DDP_COMPONENT_DPI1,
		DISP_WEG_CONFIG_DISP_WDMA1_SOUT_EN, WDMA1_SOUT_MASK,
		WDMA1_SOUT_DPI1
	}, {
		DDP_COMPONENT_WDMA1, DDP_COMPONENT_DPI1,
		DISP_WEG_CONFIG_DPI_SEW_IN, DPI1_SEW_IN_MASK,
		DPI1_SEW_IN_WDMA1
	}, {
		DDP_COMPONENT_WDMA1, DDP_COMPONENT_DSI0,
		DISP_WEG_CONFIG_DSIE_SEW_IN, DSI0_SEW_IN_MASK,
		DSI0_SEW_IN_WDMA1
	}, {
		DDP_COMPONENT_WDMA1, DDP_COMPONENT_DSI1,
		DISP_WEG_CONFIG_DISP_WDMA1_SOUT_EN, WDMA1_SOUT_MASK,
		WDMA1_SOUT_DSI1
	}, {
		DDP_COMPONENT_WDMA1, DDP_COMPONENT_DSI1,
		DISP_WEG_CONFIG_DSIO_SEW_IN, DSI1_SEW_IN_MASK,
		DSI1_SEW_IN_WDMA1
	}, {
		DDP_COMPONENT_WDMA1, DDP_COMPONENT_DSI2,
		DISP_WEG_CONFIG_DISP_WDMA1_SOUT_EN, WDMA1_SOUT_MASK,
		WDMA1_SOUT_DSI2
	}, {
		DDP_COMPONENT_WDMA1, DDP_COMPONENT_DSI2,
		DISP_WEG_CONFIG_DSIE_SEW_IN, DSI2_SEW_IN_MASK,
		DSI2_SEW_IN_WDMA1
	}, {
		DDP_COMPONENT_WDMA1, DDP_COMPONENT_DSI3,
		DISP_WEG_CONFIG_DISP_WDMA1_SOUT_EN, WDMA1_SOUT_MASK,
		WDMA1_SOUT_DSI3
	}, {
		DDP_COMPONENT_WDMA1, DDP_COMPONENT_DSI3,
		DISP_WEG_CONFIG_DSIO_SEW_IN, DSI3_SEW_IN_MASK,
		DSI3_SEW_IN_WDMA1
	}, {
		DDP_COMPONENT_WDMA2, DDP_COMPONENT_DPI0,
		DISP_WEG_CONFIG_DISP_WDMA2_SOUT, WDMA2_SOUT_MASK,
		WDMA2_SOUT_DPI0
	}, {
		DDP_COMPONENT_WDMA2, DDP_COMPONENT_DPI0,
		DISP_WEG_CONFIG_DPI_SEW_IN, DPI0_SEW_IN_MASK,
		DPI0_SEW_IN_WDMA2
	}, {
		DDP_COMPONENT_WDMA2, DDP_COMPONENT_DPI1,
		DISP_WEG_CONFIG_DISP_WDMA2_SOUT, WDMA2_SOUT_MASK,
		WDMA2_SOUT_DPI1
	}, {
		DDP_COMPONENT_WDMA2, DDP_COMPONENT_DPI1,
		DISP_WEG_CONFIG_DPI_SEW_IN, DPI1_SEW_IN_MASK,
		DPI1_SEW_IN_WDMA2
	}, {
		DDP_COMPONENT_WDMA2, DDP_COMPONENT_DSI0,
		DISP_WEG_CONFIG_DSIE_SEW_IN, DSI0_SEW_IN_MASK,
		DSI0_SEW_IN_WDMA2
	}, {
		DDP_COMPONENT_WDMA2, DDP_COMPONENT_DSI1,
		DISP_WEG_CONFIG_DISP_WDMA2_SOUT, WDMA2_SOUT_MASK,
		WDMA2_SOUT_DSI1
	}, {
		DDP_COMPONENT_WDMA2, DDP_COMPONENT_DSI1,
		DISP_WEG_CONFIG_DSIO_SEW_IN, DSI1_SEW_IN_MASK,
		DSI1_SEW_IN_WDMA2
	}, {
		DDP_COMPONENT_WDMA2, DDP_COMPONENT_DSI2,
		DISP_WEG_CONFIG_DISP_WDMA2_SOUT, WDMA2_SOUT_MASK,
		WDMA2_SOUT_DSI2
	}, {
		DDP_COMPONENT_WDMA2, DDP_COMPONENT_DSI2,
		DISP_WEG_CONFIG_DSIE_SEW_IN, DSI2_SEW_IN_MASK,
		DSI2_SEW_IN_WDMA2
	}, {
		DDP_COMPONENT_WDMA2, DDP_COMPONENT_DSI3,
		DISP_WEG_CONFIG_DISP_WDMA2_SOUT, WDMA2_SOUT_MASK,
		WDMA2_SOUT_DSI3
	}, {
		DDP_COMPONENT_WDMA2, DDP_COMPONENT_DSI3,
		DISP_WEG_CONFIG_DSIO_SEW_IN, DSI3_SEW_IN_MASK,
		DSI3_SEW_IN_WDMA2
	}, {
		DDP_COMPONENT_UFOE, DDP_COMPONENT_DSI0,
		DISP_WEG_CONFIG_DISP_UFOE_MOUT_EN, UFOE_MOUT_EN_DSI0,
		UFOE_MOUT_EN_DSI0
	}
};

#endif /* __SOC_MEDIATEK_MTK_MMSYS_H */
