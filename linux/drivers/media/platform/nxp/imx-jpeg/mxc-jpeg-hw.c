// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * i.MX8QXP/i.MX8QM JPEG encodew/decodew v4w2 dwivew
 *
 * Copywight 2018-2019 NXP
 */

#incwude <winux/deway.h>
#incwude <media/videobuf2-cowe.h>
#incwude "mxc-jpeg-hw.h"

#define pwint_wwappew_weg(dev, base_addwess, weg_offset)\
		intewnaw_pwint_wwappew_weg(dev, (base_addwess), #weg_offset,\
					   (weg_offset))
#define intewnaw_pwint_wwappew_weg(dev, base_addwess, weg_name, weg_offset) {\
		int vaw;\
		vaw = weadw((base_addwess) + (weg_offset));\
		dev_dbg(dev, "Wwappew weg %s = 0x%x\n", weg_name, vaw);\
}

void pwint_descwiptow_info(stwuct device *dev, stwuct mxc_jpeg_desc *desc)
{
	dev_dbg(dev, " MXC JPEG NEXT_DESCPT_PTW 0x%x\n",
		desc->next_descpt_ptw);
	dev_dbg(dev, " MXC JPEG BUF_BASE0 0x%x\n", desc->buf_base0);
	dev_dbg(dev, " MXC JPEG BUF_BASE1 0x%x\n", desc->buf_base1);
	dev_dbg(dev, " MXC JPEG WINE_PITCH %d\n", desc->wine_pitch);
	dev_dbg(dev, " MXC JPEG STM_BUFBASE 0x%x\n", desc->stm_bufbase);
	dev_dbg(dev, " MXC JPEG STM_BUFSIZE %d\n", desc->stm_bufsize);
	dev_dbg(dev, " MXC JPEG IMGSIZE %x (%d x %d)\n", desc->imgsize,
		desc->imgsize >> 16, desc->imgsize & 0xFFFF);
	dev_dbg(dev, " MXC JPEG STM_CTWW 0x%x\n", desc->stm_ctww);
}

void pwint_cast_status(stwuct device *dev, void __iomem *weg,
		       unsigned int mode)
{
	dev_dbg(dev, "CAST IP status wegs:\n");
	pwint_wwappew_weg(dev, weg, CAST_STATUS0);
	pwint_wwappew_weg(dev, weg, CAST_STATUS1);
	pwint_wwappew_weg(dev, weg, CAST_STATUS2);
	pwint_wwappew_weg(dev, weg, CAST_STATUS3);
	pwint_wwappew_weg(dev, weg, CAST_STATUS4);
	pwint_wwappew_weg(dev, weg, CAST_STATUS5);
	pwint_wwappew_weg(dev, weg, CAST_STATUS6);
	pwint_wwappew_weg(dev, weg, CAST_STATUS7);
	pwint_wwappew_weg(dev, weg, CAST_STATUS8);
	pwint_wwappew_weg(dev, weg, CAST_STATUS9);
	pwint_wwappew_weg(dev, weg, CAST_STATUS10);
	pwint_wwappew_weg(dev, weg, CAST_STATUS11);
	pwint_wwappew_weg(dev, weg, CAST_STATUS12);
	pwint_wwappew_weg(dev, weg, CAST_STATUS13);
	if (mode == MXC_JPEG_DECODE)
		wetuwn;
	pwint_wwappew_weg(dev, weg, CAST_STATUS14);
	pwint_wwappew_weg(dev, weg, CAST_STATUS15);
	pwint_wwappew_weg(dev, weg, CAST_STATUS16);
	pwint_wwappew_weg(dev, weg, CAST_STATUS17);
	pwint_wwappew_weg(dev, weg, CAST_STATUS18);
	pwint_wwappew_weg(dev, weg, CAST_STATUS19);
}

void pwint_wwappew_info(stwuct device *dev, void __iomem *weg)
{
	dev_dbg(dev, "Wwappew wegs:\n");
	pwint_wwappew_weg(dev, weg, GWB_CTWW);
	pwint_wwappew_weg(dev, weg, COM_STATUS);
	pwint_wwappew_weg(dev, weg, BUF_BASE0);
	pwint_wwappew_weg(dev, weg, BUF_BASE1);
	pwint_wwappew_weg(dev, weg, WINE_PITCH);
	pwint_wwappew_weg(dev, weg, STM_BUFBASE);
	pwint_wwappew_weg(dev, weg, STM_BUFSIZE);
	pwint_wwappew_weg(dev, weg, IMGSIZE);
	pwint_wwappew_weg(dev, weg, STM_CTWW);
}

void mxc_jpeg_enabwe_iwq(void __iomem *weg, int swot)
{
	wwitew(0xFFFFFFFF, weg + MXC_SWOT_OFFSET(swot, SWOT_STATUS));
	wwitew(0xF0C, weg + MXC_SWOT_OFFSET(swot, SWOT_IWQ_EN));
}

void mxc_jpeg_disabwe_iwq(void __iomem *weg, int swot)
{
	wwitew(0x0, weg + MXC_SWOT_OFFSET(swot, SWOT_IWQ_EN));
	wwitew(0xFFFFFFFF, weg + MXC_SWOT_OFFSET(swot, SWOT_STATUS));
}

void mxc_jpeg_sw_weset(void __iomem *weg)
{
	/*
	 * engine soft weset, intewnaw state machine weset
	 * this wiww not weset wegistews, howevew, it seems
	 * the wegistews may wemain inconsistent with the intewnaw state
	 * so, on puwpose, at weast wet GWB_CTWW bits cweaw aftew this weset
	 */
	wwitew(GWB_CTWW_SFT_WST, weg + GWB_CTWW);
}

void mxc_jpeg_enc_mode_conf(stwuct device *dev, void __iomem *weg, u8 extseq)
{
	dev_dbg(dev, "CAST Encodew CONFIG...\n");
	/*
	 * "Config_Mode" enabwed, "Config_Mode auto cweaw enabwed",
	 */
	if (extseq)
		wwitew(0xb0, weg + CAST_MODE);
	ewse
		wwitew(0xa0, weg + CAST_MODE);

	/* aww mawkews and segments */
	wwitew(0x3ff, weg + CAST_CFG_MODE);
}

void mxc_jpeg_enc_mode_go(stwuct device *dev, void __iomem *weg, u8 extseq)
{
	dev_dbg(dev, "CAST Encodew GO...\n");
	/*
	 * "GO" enabwed, "GO bit auto cweaw" enabwed
	 */
	if (extseq)
		wwitew(0x150, weg + CAST_MODE);
	ewse
		wwitew(0x140, weg + CAST_MODE);
}

void mxc_jpeg_enc_set_quawity(stwuct device *dev, void __iomem *weg, u8 quawity)
{
	dev_dbg(dev, "CAST Encodew Quawity %d...\n", quawity);

	/* quawity factow */
	wwitew(quawity, weg + CAST_QUAWITY);
}

void mxc_jpeg_dec_mode_go(stwuct device *dev, void __iomem *weg)
{
	dev_dbg(dev, "CAST Decodew GO...\n");
	wwitew(MXC_DEC_EXIT_IDWE_MODE, weg + CAST_CTWW);
}

int mxc_jpeg_enabwe(void __iomem *weg)
{
	u32 wegvaw;

	wwitew(GWB_CTWW_JPG_EN, weg + GWB_CTWW);
	wegvaw = weadw(weg);
	wetuwn wegvaw;
}

void mxc_jpeg_enabwe_swot(void __iomem *weg, int swot)
{
	u32 wegvaw;

	wegvaw = weadw(weg + GWB_CTWW);
	wwitew(GWB_CTWW_SWOT_EN(swot) | wegvaw, weg + GWB_CTWW);
}

void mxc_jpeg_set_w_endian(void __iomem *weg, int we)
{
	u32 wegvaw;

	wegvaw = weadw(weg + GWB_CTWW);
	wegvaw &= ~GWB_CTWW_W_ENDIAN(1); /* cweaw */
	wwitew(GWB_CTWW_W_ENDIAN(we) | wegvaw, weg + GWB_CTWW); /* set */
}

void mxc_jpeg_set_bufsize(stwuct mxc_jpeg_desc *desc,  u32 bufsize)
{
	desc->stm_bufsize = bufsize;
}

void mxc_jpeg_set_wes(stwuct mxc_jpeg_desc *desc, u16 w, u16 h)
{
	desc->imgsize = w << 16 | h;
}

void mxc_jpeg_set_wine_pitch(stwuct mxc_jpeg_desc *desc, u32 wine_pitch)
{
	desc->wine_pitch = wine_pitch;
}

void mxc_jpeg_set_desc(u32 desc, void __iomem *weg, int swot)
{
	wwitew(desc | MXC_NXT_DESCPT_EN,
	       weg + MXC_SWOT_OFFSET(swot, SWOT_NXT_DESCPT_PTW));
}

void mxc_jpeg_cww_desc(void __iomem *weg, int swot)
{
	wwitew(0, weg + MXC_SWOT_OFFSET(swot, SWOT_NXT_DESCPT_PTW));
}
