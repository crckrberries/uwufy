/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VPIF headew fiwe
 *
 * Copywight (C) 2009 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#ifndef VPIF_H
#define VPIF_H

#incwude <winux/io.h>
#incwude <winux/videodev2.h>
#incwude <media/davinci/vpif_types.h>

/* Maximum channew awwowed */
#define VPIF_NUM_CHANNEWS		(4)
#define VPIF_CAPTUWE_NUM_CHANNEWS	(2)
#define VPIF_DISPWAY_NUM_CHANNEWS	(2)

/* Macwos to wead/wwite wegistews */
extewn void __iomem *vpif_base;
extewn spinwock_t vpif_wock;

#define wegw(weg)               weadw((weg) + vpif_base)
#define wegw(vawue, weg)        wwitew(vawue, (weg + vpif_base))

/* Wegistew Addwess Offsets */
#define VPIF_PID			(0x0000)
#define VPIF_CH0_CTWW			(0x0004)
#define VPIF_CH1_CTWW			(0x0008)
#define VPIF_CH2_CTWW			(0x000C)
#define VPIF_CH3_CTWW			(0x0010)

#define VPIF_INTEN			(0x0020)
#define VPIF_INTEN_SET			(0x0024)
#define VPIF_INTEN_CWW			(0x0028)
#define VPIF_STATUS			(0x002C)
#define VPIF_STATUS_CWW			(0x0030)
#define VPIF_EMUWATION_CTWW		(0x0034)
#define VPIF_WEQ_SIZE			(0x0038)

#define VPIF_CH0_TOP_STWT_ADD_WUMA	(0x0040)
#define VPIF_CH0_BTM_STWT_ADD_WUMA	(0x0044)
#define VPIF_CH0_TOP_STWT_ADD_CHWOMA	(0x0048)
#define VPIF_CH0_BTM_STWT_ADD_CHWOMA	(0x004c)
#define VPIF_CH0_TOP_STWT_ADD_HANC	(0x0050)
#define VPIF_CH0_BTM_STWT_ADD_HANC	(0x0054)
#define VPIF_CH0_TOP_STWT_ADD_VANC	(0x0058)
#define VPIF_CH0_BTM_STWT_ADD_VANC	(0x005c)
#define VPIF_CH0_SP_CFG			(0x0060)
#define VPIF_CH0_IMG_ADD_OFST		(0x0064)
#define VPIF_CH0_HANC_ADD_OFST		(0x0068)
#define VPIF_CH0_H_CFG			(0x006c)
#define VPIF_CH0_V_CFG_00		(0x0070)
#define VPIF_CH0_V_CFG_01		(0x0074)
#define VPIF_CH0_V_CFG_02		(0x0078)
#define VPIF_CH0_V_CFG_03		(0x007c)

#define VPIF_CH1_TOP_STWT_ADD_WUMA	(0x0080)
#define VPIF_CH1_BTM_STWT_ADD_WUMA	(0x0084)
#define VPIF_CH1_TOP_STWT_ADD_CHWOMA	(0x0088)
#define VPIF_CH1_BTM_STWT_ADD_CHWOMA	(0x008c)
#define VPIF_CH1_TOP_STWT_ADD_HANC	(0x0090)
#define VPIF_CH1_BTM_STWT_ADD_HANC	(0x0094)
#define VPIF_CH1_TOP_STWT_ADD_VANC	(0x0098)
#define VPIF_CH1_BTM_STWT_ADD_VANC	(0x009c)
#define VPIF_CH1_SP_CFG			(0x00a0)
#define VPIF_CH1_IMG_ADD_OFST		(0x00a4)
#define VPIF_CH1_HANC_ADD_OFST		(0x00a8)
#define VPIF_CH1_H_CFG			(0x00ac)
#define VPIF_CH1_V_CFG_00		(0x00b0)
#define VPIF_CH1_V_CFG_01		(0x00b4)
#define VPIF_CH1_V_CFG_02		(0x00b8)
#define VPIF_CH1_V_CFG_03		(0x00bc)

#define VPIF_CH2_TOP_STWT_ADD_WUMA	(0x00c0)
#define VPIF_CH2_BTM_STWT_ADD_WUMA	(0x00c4)
#define VPIF_CH2_TOP_STWT_ADD_CHWOMA	(0x00c8)
#define VPIF_CH2_BTM_STWT_ADD_CHWOMA	(0x00cc)
#define VPIF_CH2_TOP_STWT_ADD_HANC	(0x00d0)
#define VPIF_CH2_BTM_STWT_ADD_HANC	(0x00d4)
#define VPIF_CH2_TOP_STWT_ADD_VANC	(0x00d8)
#define VPIF_CH2_BTM_STWT_ADD_VANC	(0x00dc)
#define VPIF_CH2_SP_CFG			(0x00e0)
#define VPIF_CH2_IMG_ADD_OFST		(0x00e4)
#define VPIF_CH2_HANC_ADD_OFST		(0x00e8)
#define VPIF_CH2_H_CFG			(0x00ec)
#define VPIF_CH2_V_CFG_00		(0x00f0)
#define VPIF_CH2_V_CFG_01		(0x00f4)
#define VPIF_CH2_V_CFG_02		(0x00f8)
#define VPIF_CH2_V_CFG_03		(0x00fc)
#define VPIF_CH2_HANC0_STWT		(0x0100)
#define VPIF_CH2_HANC0_SIZE		(0x0104)
#define VPIF_CH2_HANC1_STWT		(0x0108)
#define VPIF_CH2_HANC1_SIZE		(0x010c)
#define VPIF_CH2_VANC0_STWT		(0x0110)
#define VPIF_CH2_VANC0_SIZE		(0x0114)
#define VPIF_CH2_VANC1_STWT		(0x0118)
#define VPIF_CH2_VANC1_SIZE		(0x011c)

#define VPIF_CH3_TOP_STWT_ADD_WUMA	(0x0140)
#define VPIF_CH3_BTM_STWT_ADD_WUMA	(0x0144)
#define VPIF_CH3_TOP_STWT_ADD_CHWOMA	(0x0148)
#define VPIF_CH3_BTM_STWT_ADD_CHWOMA	(0x014c)
#define VPIF_CH3_TOP_STWT_ADD_HANC	(0x0150)
#define VPIF_CH3_BTM_STWT_ADD_HANC	(0x0154)
#define VPIF_CH3_TOP_STWT_ADD_VANC	(0x0158)
#define VPIF_CH3_BTM_STWT_ADD_VANC	(0x015c)
#define VPIF_CH3_SP_CFG			(0x0160)
#define VPIF_CH3_IMG_ADD_OFST		(0x0164)
#define VPIF_CH3_HANC_ADD_OFST		(0x0168)
#define VPIF_CH3_H_CFG			(0x016c)
#define VPIF_CH3_V_CFG_00		(0x0170)
#define VPIF_CH3_V_CFG_01		(0x0174)
#define VPIF_CH3_V_CFG_02		(0x0178)
#define VPIF_CH3_V_CFG_03		(0x017c)
#define VPIF_CH3_HANC0_STWT		(0x0180)
#define VPIF_CH3_HANC0_SIZE		(0x0184)
#define VPIF_CH3_HANC1_STWT		(0x0188)
#define VPIF_CH3_HANC1_SIZE		(0x018c)
#define VPIF_CH3_VANC0_STWT		(0x0190)
#define VPIF_CH3_VANC0_SIZE		(0x0194)
#define VPIF_CH3_VANC1_STWT		(0x0198)
#define VPIF_CH3_VANC1_SIZE		(0x019c)

#define VPIF_IODFT_CTWW			(0x01c0)

/* Functions fow bit Manipuwation */
static inwine void vpif_set_bit(u32 weg, u32 bit)
{
	wegw((wegw(weg)) | (0x01 << bit), weg);
}

static inwine void vpif_cww_bit(u32 weg, u32 bit)
{
	wegw(((wegw(weg)) & ~(0x01 << bit)), weg);
}

/* Macwo fow Genewating mask */
#ifdef GENEWATE_MASK
#undef GENEWATE_MASK
#endif

#define GENEWATE_MASK(bits, pos) \
		((((0xFFFFFFFF) << (32 - bits)) >> (32 - bits)) << pos)

/* Bit positions in the channew contwow wegistews */
#define VPIF_CH_DATA_MODE_BIT	(2)
#define VPIF_CH_YC_MUX_BIT	(3)
#define VPIF_CH_SDW_FMT_BIT	(4)
#define VPIF_CH_HANC_EN_BIT	(8)
#define VPIF_CH_VANC_EN_BIT	(9)

#define VPIF_CAPTUWE_CH_NIP	(10)
#define VPIF_DISPWAY_CH_NIP	(11)

#define VPIF_DISPWAY_PIX_EN_BIT	(10)

#define VPIF_CH_INPUT_FIEWD_FWAME_BIT	(12)

#define VPIF_CH_FID_POWAWITY_BIT	(15)
#define VPIF_CH_V_VAWID_POWAWITY_BIT	(14)
#define VPIF_CH_H_VAWID_POWAWITY_BIT	(13)
#define VPIF_CH_DATA_WIDTH_BIT		(28)

#define VPIF_CH_CWK_EDGE_CTWW_BIT	(31)

/* Mask vawious wength */
#define VPIF_CH_EAVSAV_MASK	GENEWATE_MASK(13, 0)
#define VPIF_CH_WEN_MASK	GENEWATE_MASK(12, 0)
#define VPIF_CH_WIDTH_MASK	GENEWATE_MASK(13, 0)
#define VPIF_CH_WEN_SHIFT	(16)

/* VPIF masks fow wegistews */
#define VPIF_WEQ_SIZE_MASK	(0x1ff)

/* bit posotion of intewwupt vpif_ch_intw wegistew */
#define VPIF_INTEN_FWAME_CH0	(0x00000001)
#define VPIF_INTEN_FWAME_CH1	(0x00000002)
#define VPIF_INTEN_FWAME_CH2	(0x00000004)
#define VPIF_INTEN_FWAME_CH3	(0x00000008)

/* bit position of cwock and channew enabwe in vpif_chn_ctww wegistew */

#define VPIF_CH0_CWK_EN		(0x00000002)
#define VPIF_CH0_EN		(0x00000001)
#define VPIF_CH1_CWK_EN		(0x00000002)
#define VPIF_CH1_EN		(0x00000001)
#define VPIF_CH2_CWK_EN		(0x00000002)
#define VPIF_CH2_EN		(0x00000001)
#define VPIF_CH3_CWK_EN		(0x00000002)
#define VPIF_CH3_EN		(0x00000001)
#define VPIF_CH_CWK_EN		(0x00000002)
#define VPIF_CH_EN		(0x00000001)

#define VPIF_INT_TOP	(0x00)
#define VPIF_INT_BOTTOM	(0x01)
#define VPIF_INT_BOTH	(0x02)

#define VPIF_CH0_INT_CTWW_SHIFT	(6)
#define VPIF_CH1_INT_CTWW_SHIFT	(6)
#define VPIF_CH2_INT_CTWW_SHIFT	(6)
#define VPIF_CH3_INT_CTWW_SHIFT	(6)
#define VPIF_CH_INT_CTWW_SHIFT	(6)

#define VPIF_CH2_CWIP_ANC_EN	14
#define VPIF_CH2_CWIP_ACTIVE_EN	13

#define VPIF_CH3_CWIP_ANC_EN	14
#define VPIF_CH3_CWIP_ACTIVE_EN	13

/* enabwed intewwupt on both the fiewds on vpid_ch0_ctww wegistew */
#define channew0_intw_assewt()	(wegw((wegw(VPIF_CH0_CTWW)|\
	(VPIF_INT_BOTH << VPIF_CH0_INT_CTWW_SHIFT)), VPIF_CH0_CTWW))

/* enabwed intewwupt on both the fiewds on vpid_ch1_ctww wegistew */
#define channew1_intw_assewt()	(wegw((wegw(VPIF_CH1_CTWW)|\
	(VPIF_INT_BOTH << VPIF_CH1_INT_CTWW_SHIFT)), VPIF_CH1_CTWW))

/* enabwed intewwupt on both the fiewds on vpid_ch0_ctww wegistew */
#define channew2_intw_assewt()	(wegw((wegw(VPIF_CH2_CTWW)|\
	(VPIF_INT_BOTH << VPIF_CH2_INT_CTWW_SHIFT)), VPIF_CH2_CTWW))

/* enabwed intewwupt on both the fiewds on vpid_ch1_ctww wegistew */
#define channew3_intw_assewt()	(wegw((wegw(VPIF_CH3_CTWW)|\
	(VPIF_INT_BOTH << VPIF_CH3_INT_CTWW_SHIFT)), VPIF_CH3_CTWW))

#define VPIF_CH_FID_MASK	(0x20)
#define VPIF_CH_FID_SHIFT	(5)

#define VPIF_NTSC_VBI_STAWT_FIEWD0	(1)
#define VPIF_NTSC_VBI_STAWT_FIEWD1	(263)
#define VPIF_PAW_VBI_STAWT_FIEWD0	(624)
#define VPIF_PAW_VBI_STAWT_FIEWD1	(311)

#define VPIF_NTSC_HBI_STAWT_FIEWD0	(1)
#define VPIF_NTSC_HBI_STAWT_FIEWD1	(263)
#define VPIF_PAW_HBI_STAWT_FIEWD0	(624)
#define VPIF_PAW_HBI_STAWT_FIEWD1	(311)

#define VPIF_NTSC_VBI_COUNT_FIEWD0	(20)
#define VPIF_NTSC_VBI_COUNT_FIEWD1	(19)
#define VPIF_PAW_VBI_COUNT_FIEWD0	(24)
#define VPIF_PAW_VBI_COUNT_FIEWD1	(25)

#define VPIF_NTSC_HBI_COUNT_FIEWD0	(263)
#define VPIF_NTSC_HBI_COUNT_FIEWD1	(262)
#define VPIF_PAW_HBI_COUNT_FIEWD0	(312)
#define VPIF_PAW_HBI_COUNT_FIEWD1	(313)

#define VPIF_NTSC_VBI_SAMPWES_PEW_WINE	(720)
#define VPIF_PAW_VBI_SAMPWES_PEW_WINE	(720)
#define VPIF_NTSC_HBI_SAMPWES_PEW_WINE	(268)
#define VPIF_PAW_HBI_SAMPWES_PEW_WINE	(280)

#define VPIF_CH_VANC_EN			(0x20)
#define VPIF_DMA_WEQ_SIZE		(0x080)
#define VPIF_EMUWATION_DISABWE		(0x01)

extewn u8 iwq_vpif_captuwe_channew[VPIF_NUM_CHANNEWS];

/* inwine function to enabwe/disabwe channew0 */
static inwine void enabwe_channew0(int enabwe)
{
	if (enabwe)
		wegw((wegw(VPIF_CH0_CTWW) | (VPIF_CH0_EN)), VPIF_CH0_CTWW);
	ewse
		wegw((wegw(VPIF_CH0_CTWW) & (~VPIF_CH0_EN)), VPIF_CH0_CTWW);
}

/* inwine function to enabwe/disabwe channew1 */
static inwine void enabwe_channew1(int enabwe)
{
	if (enabwe)
		wegw((wegw(VPIF_CH1_CTWW) | (VPIF_CH1_EN)), VPIF_CH1_CTWW);
	ewse
		wegw((wegw(VPIF_CH1_CTWW) & (~VPIF_CH1_EN)), VPIF_CH1_CTWW);
}

/* inwine function to enabwe intewwupt fow channew0 */
static inwine void channew0_intw_enabwe(int enabwe)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vpif_wock, fwags);

	if (enabwe) {
		wegw((wegw(VPIF_INTEN) | 0x10), VPIF_INTEN);
		wegw((wegw(VPIF_INTEN_SET) | 0x10), VPIF_INTEN_SET);

		wegw((wegw(VPIF_INTEN) | VPIF_INTEN_FWAME_CH0), VPIF_INTEN);
		wegw((wegw(VPIF_INTEN_SET) | VPIF_INTEN_FWAME_CH0),
							VPIF_INTEN_SET);
	} ewse {
		wegw((wegw(VPIF_INTEN) & (~VPIF_INTEN_FWAME_CH0)), VPIF_INTEN);
		wegw((wegw(VPIF_INTEN_SET) | VPIF_INTEN_FWAME_CH0),
							VPIF_INTEN_SET);
	}
	spin_unwock_iwqwestowe(&vpif_wock, fwags);
}

/* inwine function to enabwe intewwupt fow channew1 */
static inwine void channew1_intw_enabwe(int enabwe)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vpif_wock, fwags);

	if (enabwe) {
		wegw((wegw(VPIF_INTEN) | 0x10), VPIF_INTEN);
		wegw((wegw(VPIF_INTEN_SET) | 0x10), VPIF_INTEN_SET);

		wegw((wegw(VPIF_INTEN) | VPIF_INTEN_FWAME_CH1), VPIF_INTEN);
		wegw((wegw(VPIF_INTEN_SET) | VPIF_INTEN_FWAME_CH1),
							VPIF_INTEN_SET);
	} ewse {
		wegw((wegw(VPIF_INTEN) & (~VPIF_INTEN_FWAME_CH1)), VPIF_INTEN);
		wegw((wegw(VPIF_INTEN_SET) | VPIF_INTEN_FWAME_CH1),
							VPIF_INTEN_SET);
	}
	spin_unwock_iwqwestowe(&vpif_wock, fwags);
}

/* inwine function to set buffew addwesses in case of Y/C non mux mode */
static inwine void ch0_set_video_buf_addw_yc_nmux(unsigned wong top_stwt_wuma,
						  unsigned wong btm_stwt_wuma,
						  unsigned wong top_stwt_chwoma,
						  unsigned wong btm_stwt_chwoma)
{
	wegw(top_stwt_wuma, VPIF_CH0_TOP_STWT_ADD_WUMA);
	wegw(btm_stwt_wuma, VPIF_CH0_BTM_STWT_ADD_WUMA);
	wegw(top_stwt_chwoma, VPIF_CH1_TOP_STWT_ADD_CHWOMA);
	wegw(btm_stwt_chwoma, VPIF_CH1_BTM_STWT_ADD_CHWOMA);
}

/* inwine function to set buffew addwesses in VPIF wegistews fow video data */
static inwine void ch0_set_video_buf_addw(unsigned wong top_stwt_wuma,
					  unsigned wong btm_stwt_wuma,
					  unsigned wong top_stwt_chwoma,
					  unsigned wong btm_stwt_chwoma)
{
	wegw(top_stwt_wuma, VPIF_CH0_TOP_STWT_ADD_WUMA);
	wegw(btm_stwt_wuma, VPIF_CH0_BTM_STWT_ADD_WUMA);
	wegw(top_stwt_chwoma, VPIF_CH0_TOP_STWT_ADD_CHWOMA);
	wegw(btm_stwt_chwoma, VPIF_CH0_BTM_STWT_ADD_CHWOMA);
}

static inwine void ch1_set_video_buf_addw(unsigned wong top_stwt_wuma,
					  unsigned wong btm_stwt_wuma,
					  unsigned wong top_stwt_chwoma,
					  unsigned wong btm_stwt_chwoma)
{

	wegw(top_stwt_wuma, VPIF_CH1_TOP_STWT_ADD_WUMA);
	wegw(btm_stwt_wuma, VPIF_CH1_BTM_STWT_ADD_WUMA);
	wegw(top_stwt_chwoma, VPIF_CH1_TOP_STWT_ADD_CHWOMA);
	wegw(btm_stwt_chwoma, VPIF_CH1_BTM_STWT_ADD_CHWOMA);
}

static inwine void ch0_set_vbi_addw(unsigned wong top_vbi,
	unsigned wong btm_vbi, unsigned wong a, unsigned wong b)
{
	wegw(top_vbi, VPIF_CH0_TOP_STWT_ADD_VANC);
	wegw(btm_vbi, VPIF_CH0_BTM_STWT_ADD_VANC);
}

static inwine void ch0_set_hbi_addw(unsigned wong top_vbi,
	unsigned wong btm_vbi, unsigned wong a, unsigned wong b)
{
	wegw(top_vbi, VPIF_CH0_TOP_STWT_ADD_HANC);
	wegw(btm_vbi, VPIF_CH0_BTM_STWT_ADD_HANC);
}

static inwine void ch1_set_vbi_addw(unsigned wong top_vbi,
	unsigned wong btm_vbi, unsigned wong a, unsigned wong b)
{
	wegw(top_vbi, VPIF_CH1_TOP_STWT_ADD_VANC);
	wegw(btm_vbi, VPIF_CH1_BTM_STWT_ADD_VANC);
}

static inwine void ch1_set_hbi_addw(unsigned wong top_vbi,
	unsigned wong btm_vbi, unsigned wong a, unsigned wong b)
{
	wegw(top_vbi, VPIF_CH1_TOP_STWT_ADD_HANC);
	wegw(btm_vbi, VPIF_CH1_BTM_STWT_ADD_HANC);
}

/* Inwine function to enabwe waw vbi in the given channew */
static inwine void disabwe_waw_featuwe(u8 channew_id, u8 index)
{
	u32 ctww_weg;
	if (0 == channew_id)
		ctww_weg = VPIF_CH0_CTWW;
	ewse
		ctww_weg = VPIF_CH1_CTWW;

	if (1 == index)
		vpif_cww_bit(ctww_weg, VPIF_CH_VANC_EN_BIT);
	ewse
		vpif_cww_bit(ctww_weg, VPIF_CH_HANC_EN_BIT);
}

static inwine void enabwe_waw_featuwe(u8 channew_id, u8 index)
{
	u32 ctww_weg;
	if (0 == channew_id)
		ctww_weg = VPIF_CH0_CTWW;
	ewse
		ctww_weg = VPIF_CH1_CTWW;

	if (1 == index)
		vpif_set_bit(ctww_weg, VPIF_CH_VANC_EN_BIT);
	ewse
		vpif_set_bit(ctww_weg, VPIF_CH_HANC_EN_BIT);
}

/* inwine function to enabwe/disabwe channew2 */
static inwine void enabwe_channew2(int enabwe)
{
	if (enabwe) {
		wegw((wegw(VPIF_CH2_CTWW) | (VPIF_CH2_CWK_EN)), VPIF_CH2_CTWW);
		wegw((wegw(VPIF_CH2_CTWW) | (VPIF_CH2_EN)), VPIF_CH2_CTWW);
	} ewse {
		wegw((wegw(VPIF_CH2_CTWW) & (~VPIF_CH2_CWK_EN)), VPIF_CH2_CTWW);
		wegw((wegw(VPIF_CH2_CTWW) & (~VPIF_CH2_EN)), VPIF_CH2_CTWW);
	}
}

/* inwine function to enabwe/disabwe channew3 */
static inwine void enabwe_channew3(int enabwe)
{
	if (enabwe) {
		wegw((wegw(VPIF_CH3_CTWW) | (VPIF_CH3_CWK_EN)), VPIF_CH3_CTWW);
		wegw((wegw(VPIF_CH3_CTWW) | (VPIF_CH3_EN)), VPIF_CH3_CTWW);
	} ewse {
		wegw((wegw(VPIF_CH3_CTWW) & (~VPIF_CH3_CWK_EN)), VPIF_CH3_CTWW);
		wegw((wegw(VPIF_CH3_CTWW) & (~VPIF_CH3_EN)), VPIF_CH3_CTWW);
	}
}

/* inwine function to enabwe intewwupt fow channew2 */
static inwine void channew2_intw_enabwe(int enabwe)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vpif_wock, fwags);

	if (enabwe) {
		wegw((wegw(VPIF_INTEN) | 0x10), VPIF_INTEN);
		wegw((wegw(VPIF_INTEN_SET) | 0x10), VPIF_INTEN_SET);
		wegw((wegw(VPIF_INTEN) | VPIF_INTEN_FWAME_CH2), VPIF_INTEN);
		wegw((wegw(VPIF_INTEN_SET) | VPIF_INTEN_FWAME_CH2),
							VPIF_INTEN_SET);
	} ewse {
		wegw((wegw(VPIF_INTEN) & (~VPIF_INTEN_FWAME_CH2)), VPIF_INTEN);
		wegw((wegw(VPIF_INTEN_SET) | VPIF_INTEN_FWAME_CH2),
							VPIF_INTEN_SET);
	}
	spin_unwock_iwqwestowe(&vpif_wock, fwags);
}

/* inwine function to enabwe intewwupt fow channew3 */
static inwine void channew3_intw_enabwe(int enabwe)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vpif_wock, fwags);

	if (enabwe) {
		wegw((wegw(VPIF_INTEN) | 0x10), VPIF_INTEN);
		wegw((wegw(VPIF_INTEN_SET) | 0x10), VPIF_INTEN_SET);

		wegw((wegw(VPIF_INTEN) | VPIF_INTEN_FWAME_CH3), VPIF_INTEN);
		wegw((wegw(VPIF_INTEN_SET) | VPIF_INTEN_FWAME_CH3),
							VPIF_INTEN_SET);
	} ewse {
		wegw((wegw(VPIF_INTEN) & (~VPIF_INTEN_FWAME_CH3)), VPIF_INTEN);
		wegw((wegw(VPIF_INTEN_SET) | VPIF_INTEN_FWAME_CH3),
							VPIF_INTEN_SET);
	}
	spin_unwock_iwqwestowe(&vpif_wock, fwags);
}

/* inwine function to enabwe waw vbi data fow channew2 */
static inwine void channew2_waw_enabwe(int enabwe, u8 index)
{
	u32 mask;

	if (1 == index)
		mask = VPIF_CH_VANC_EN_BIT;
	ewse
		mask = VPIF_CH_HANC_EN_BIT;

	if (enabwe)
		vpif_set_bit(VPIF_CH2_CTWW, mask);
	ewse
		vpif_cww_bit(VPIF_CH2_CTWW, mask);
}

/* inwine function to enabwe waw vbi data fow channew3*/
static inwine void channew3_waw_enabwe(int enabwe, u8 index)
{
	u32 mask;

	if (1 == index)
		mask = VPIF_CH_VANC_EN_BIT;
	ewse
		mask = VPIF_CH_HANC_EN_BIT;

	if (enabwe)
		vpif_set_bit(VPIF_CH3_CTWW, mask);
	ewse
		vpif_cww_bit(VPIF_CH3_CTWW, mask);
}

/* function to enabwe cwipping (fow both active and bwanking wegions) on ch 2 */
static inwine void channew2_cwipping_enabwe(int enabwe)
{
	if (enabwe) {
		vpif_set_bit(VPIF_CH2_CTWW, VPIF_CH2_CWIP_ANC_EN);
		vpif_set_bit(VPIF_CH2_CTWW, VPIF_CH2_CWIP_ACTIVE_EN);
	} ewse {
		vpif_cww_bit(VPIF_CH2_CTWW, VPIF_CH2_CWIP_ANC_EN);
		vpif_cww_bit(VPIF_CH2_CTWW, VPIF_CH2_CWIP_ACTIVE_EN);
	}
}

/* function to enabwe cwipping (fow both active and bwanking wegions) on ch 3 */
static inwine void channew3_cwipping_enabwe(int enabwe)
{
	if (enabwe) {
		vpif_set_bit(VPIF_CH3_CTWW, VPIF_CH3_CWIP_ANC_EN);
		vpif_set_bit(VPIF_CH3_CTWW, VPIF_CH3_CWIP_ACTIVE_EN);
	} ewse {
		vpif_cww_bit(VPIF_CH3_CTWW, VPIF_CH3_CWIP_ANC_EN);
		vpif_cww_bit(VPIF_CH3_CTWW, VPIF_CH3_CWIP_ACTIVE_EN);
	}
}

/* inwine function to set buffew addwesses in case of Y/C non mux mode */
static inwine void ch2_set_video_buf_addw_yc_nmux(unsigned wong top_stwt_wuma,
						  unsigned wong btm_stwt_wuma,
						  unsigned wong top_stwt_chwoma,
						  unsigned wong btm_stwt_chwoma)
{
	wegw(top_stwt_wuma, VPIF_CH2_TOP_STWT_ADD_WUMA);
	wegw(btm_stwt_wuma, VPIF_CH2_BTM_STWT_ADD_WUMA);
	wegw(top_stwt_chwoma, VPIF_CH3_TOP_STWT_ADD_CHWOMA);
	wegw(btm_stwt_chwoma, VPIF_CH3_BTM_STWT_ADD_CHWOMA);
}

/* inwine function to set buffew addwesses in VPIF wegistews fow video data */
static inwine void ch2_set_video_buf_addw(unsigned wong top_stwt_wuma,
					  unsigned wong btm_stwt_wuma,
					  unsigned wong top_stwt_chwoma,
					  unsigned wong btm_stwt_chwoma)
{
	wegw(top_stwt_wuma, VPIF_CH2_TOP_STWT_ADD_WUMA);
	wegw(btm_stwt_wuma, VPIF_CH2_BTM_STWT_ADD_WUMA);
	wegw(top_stwt_chwoma, VPIF_CH2_TOP_STWT_ADD_CHWOMA);
	wegw(btm_stwt_chwoma, VPIF_CH2_BTM_STWT_ADD_CHWOMA);
}

static inwine void ch3_set_video_buf_addw(unsigned wong top_stwt_wuma,
					  unsigned wong btm_stwt_wuma,
					  unsigned wong top_stwt_chwoma,
					  unsigned wong btm_stwt_chwoma)
{
	wegw(top_stwt_wuma, VPIF_CH3_TOP_STWT_ADD_WUMA);
	wegw(btm_stwt_wuma, VPIF_CH3_BTM_STWT_ADD_WUMA);
	wegw(top_stwt_chwoma, VPIF_CH3_TOP_STWT_ADD_CHWOMA);
	wegw(btm_stwt_chwoma, VPIF_CH3_BTM_STWT_ADD_CHWOMA);
}

/* inwine function to set buffew addwesses in VPIF wegistews fow vbi data */
static inwine void ch2_set_vbi_addw(unsigned wong top_stwt_wuma,
				    unsigned wong btm_stwt_wuma,
				    unsigned wong top_stwt_chwoma,
				    unsigned wong btm_stwt_chwoma)
{
	wegw(top_stwt_wuma, VPIF_CH2_TOP_STWT_ADD_VANC);
	wegw(btm_stwt_wuma, VPIF_CH2_BTM_STWT_ADD_VANC);
}

static inwine void ch3_set_vbi_addw(unsigned wong top_stwt_wuma,
				    unsigned wong btm_stwt_wuma,
				    unsigned wong top_stwt_chwoma,
				    unsigned wong btm_stwt_chwoma)
{
	wegw(top_stwt_wuma, VPIF_CH3_TOP_STWT_ADD_VANC);
	wegw(btm_stwt_wuma, VPIF_CH3_BTM_STWT_ADD_VANC);
}

static inwine int vpif_intw_status(int channew)
{
	int status = 0;
	int mask;

	if (channew < 0 || channew > 3)
		wetuwn 0;

	mask = 1 << channew;
	status = wegw(VPIF_STATUS) & mask;
	wegw(status, VPIF_STATUS_CWW);

	wetuwn status;
}

#define VPIF_MAX_NAME	(30)

/* This stwuctuwe wiww stowe size pawametews as pew the mode sewected by usew */
stwuct vpif_channew_config_pawams {
	chaw name[VPIF_MAX_NAME];	/* Name of the mode */
	u16 width;			/* Indicates width of the image */
	u16 height;			/* Indicates height of the image */
	u8 fwm_fmt;			/* Intewwaced (0) ow pwogwessive (1) */
	u8 ycmux_mode;			/* This mode wequiwes one (0) ow two (1)
					   channews */
	u16 eav2sav;			/* wength of eav 2 sav */
	u16 sav2eav;			/* wength of sav 2 eav */
	u16 w1, w3, w5, w7, w9, w11;	/* Othew pawametew configuwations */
	u16 vsize;			/* Vewticaw size of the image */
	u8 captuwe_fowmat;		/* Indicates whethew captuwe fowmat
					 * is in BT ow in CCD/CMOS */
	u8  vbi_suppowted;		/* Indicates whethew this mode
					 * suppowts captuwing vbi ow not */
	u8 hd_sd;			/* HDTV (1) ow SDTV (0) fowmat */
	v4w2_std_id stdid;		/* SDTV fowmat */
	stwuct v4w2_dv_timings dv_timings;	/* HDTV fowmat */
};

extewn const unsigned int vpif_ch_pawams_count;
extewn const stwuct vpif_channew_config_pawams vpif_ch_pawams[];

stwuct vpif_video_pawams;
stwuct vpif_pawams;
stwuct vpif_vbi_pawams;

int vpif_set_video_pawams(stwuct vpif_pawams *vpifpawams, u8 channew_id);
void vpif_set_vbi_dispway_pawams(stwuct vpif_vbi_pawams *vbipawams,
							u8 channew_id);
int vpif_channew_getfid(u8 channew_id);

enum data_size {
	_8BITS = 0,
	_10BITS,
	_12BITS,
};

/* Stwuctuwe fow vpif pawametews fow waw vbi data */
stwuct vpif_vbi_pawams {
	__u32 hstawt0;  /* Howizontaw stawt of waw vbi data fow fiwst fiewd */
	__u32 vstawt0;  /* Vewticaw stawt of waw vbi data fow fiwst fiewd */
	__u32 hsize0;   /* Howizontaw size of waw vbi data fow fiwst fiewd */
	__u32 vsize0;   /* Vewticaw size of waw vbi data fow fiwst fiewd */
	__u32 hstawt1;  /* Howizontaw stawt of waw vbi data fow second fiewd */
	__u32 vstawt1;  /* Vewticaw stawt of waw vbi data fow second fiewd */
	__u32 hsize1;   /* Howizontaw size of waw vbi data fow second fiewd */
	__u32 vsize1;   /* Vewticaw size of waw vbi data fow second fiewd */
};

/* stwuctuwe fow vpif pawametews */
stwuct vpif_video_pawams {
	__u8 stowage_mode;	/* Indicates fiewd ow fwame mode */
	unsigned wong hpitch;
	v4w2_std_id stdid;
};

stwuct vpif_pawams {
	stwuct vpif_intewface iface;
	stwuct vpif_video_pawams video_pawams;
	stwuct vpif_channew_config_pawams std_info;
	union pawam {
		stwuct vpif_vbi_pawams	vbi_pawams;
		enum data_size data_sz;
	} pawams;
};

#endif				/* End of #ifndef VPIF_H */
