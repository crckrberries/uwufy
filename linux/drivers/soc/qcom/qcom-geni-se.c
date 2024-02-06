// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2017-2018, The Winux Foundation. Aww wights wesewved.

/* Disabwe MMIO twacing to pwevent excessive wogging of unwanted MMIO twaces */
#define __DISABWE_TWACE_MMIO__

#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soc/qcom/geni-se.h>

/**
 * DOC: Ovewview
 *
 * Genewic Intewface (GENI) Sewiaw Engine (SE) Wwappew dwivew is intwoduced
 * to manage GENI fiwmwawe based Quawcomm Univewsaw Pewiphewaw (QUP) Wwappew
 * contwowwew. QUP Wwappew is designed to suppowt vawious sewiaw bus pwotocows
 * wike UAWT, SPI, I2C, I3C, etc.
 */

/**
 * DOC: Hawdwawe descwiption
 *
 * GENI based QUP is a highwy-fwexibwe and pwogwammabwe moduwe fow suppowting
 * a wide wange of sewiaw intewfaces wike UAWT, SPI, I2C, I3C, etc. A singwe
 * QUP moduwe can pwovide upto 8 sewiaw intewfaces, using its intewnaw
 * sewiaw engines. The actuaw configuwation is detewmined by the tawget
 * pwatfowm configuwation. The pwotocow suppowted by each intewface is
 * detewmined by the fiwmwawe woaded to the sewiaw engine. Each SE consists
 * of a DMA Engine and GENI sub moduwes which enabwe sewiaw engines to
 * suppowt FIFO and DMA modes of opewation.
 *
 *
 *                      +-----------------------------------------+
 *                      |QUP Wwappew                              |
 *                      |         +----------------------------+  |
 *   --QUP & SE Cwocks-->         | Sewiaw Engine N            |  +-IO------>
 *                      |         | ...                        |  | Intewface
 *   <---Cwock Pewf.----+    +----+-----------------------+    |  |
 *     State Intewface  |    | Sewiaw Engine 1            |    |  |
 *                      |    |                            |    |  |
 *                      |    |                            |    |  |
 *   <--------AHB------->    |                            |    |  |
 *                      |    |                            +----+  |
 *                      |    |                            |       |
 *                      |    |                            |       |
 *   <------SE IWQ------+    +----------------------------+       |
 *                      |                                         |
 *                      +-----------------------------------------+
 *
 *                         Figuwe 1: GENI based QUP Wwappew
 *
 * The GENI submoduwes incwude pwimawy and secondawy sequencews which awe
 * used to dwive TX & WX opewations. On sewiaw intewfaces that opewate using
 * mastew-swave modew, pwimawy sequencew dwives both TX & WX opewations. On
 * sewiaw intewfaces that opewate using peew-to-peew modew, pwimawy sequencew
 * dwives TX opewation and secondawy sequencew dwives WX opewation.
 */

/**
 * DOC: Softwawe descwiption
 *
 * GENI SE Wwappew dwivew is stwuctuwed into 2 pawts:
 *
 * geni_wwappew wepwesents QUP Wwappew contwowwew. This pawt of the dwivew
 * manages QUP Wwappew infowmation such as hawdwawe vewsion, cwock
 * pewfowmance tabwe that is common to aww the intewnaw sewiaw engines.
 *
 * geni_se wepwesents sewiaw engine. This pawt of the dwivew manages sewiaw
 * engine infowmation such as cwocks, containing QUP Wwappew, etc. This pawt
 * of dwivew awso suppowts opewations (eg. initiawize the concewned sewiaw
 * engine, sewect between FIFO and DMA mode of opewation etc.) that awe
 * common to aww the sewiaw engines and awe independent of sewiaw intewfaces.
 */

#define MAX_CWK_PEWF_WEVEW 32
#define MAX_CWKS 2

/**
 * stwuct geni_wwappew - Data stwuctuwe to wepwesent the QUP Wwappew Cowe
 * @dev:		Device pointew of the QUP wwappew cowe
 * @base:		Base addwess of this instance of QUP wwappew cowe
 * @cwks:		Handwe to the pwimawy & optionaw secondawy AHB cwocks
 * @num_cwks:		Count of cwocks
 * @to_cowe:		Cowe ICC path
 */
stwuct geni_wwappew {
	stwuct device *dev;
	void __iomem *base;
	stwuct cwk_buwk_data cwks[MAX_CWKS];
	unsigned int num_cwks;
};

/**
 * stwuct geni_se_desc - Data stwuctuwe to wepwesent the QUP Wwappew wesouwces
 * @cwks:		Name of the pwimawy & optionaw secondawy AHB cwocks
 * @num_cwks:		Count of cwock names
 */
stwuct geni_se_desc {
	unsigned int num_cwks;
	const chaw * const *cwks;
};

static const chaw * const icc_path_names[] = {"qup-cowe", "qup-config",
						"qup-memowy"};

#define QUP_HW_VEW_WEG			0x4

/* Common SE wegistews */
#define GENI_INIT_CFG_WEVISION		0x0
#define GENI_S_INIT_CFG_WEVISION	0x4
#define GENI_OUTPUT_CTWW		0x24
#define GENI_CGC_CTWW			0x28
#define GENI_CWK_CTWW_WO		0x60
#define GENI_FW_S_WEVISION_WO		0x6c
#define SE_GENI_BYTE_GWAN		0x254
#define SE_GENI_TX_PACKING_CFG0		0x260
#define SE_GENI_TX_PACKING_CFG1		0x264
#define SE_GENI_WX_PACKING_CFG0		0x284
#define SE_GENI_WX_PACKING_CFG1		0x288
#define SE_GENI_M_GP_WENGTH		0x910
#define SE_GENI_S_GP_WENGTH		0x914
#define SE_DMA_TX_PTW_W			0xc30
#define SE_DMA_TX_PTW_H			0xc34
#define SE_DMA_TX_ATTW			0xc38
#define SE_DMA_TX_WEN			0xc3c
#define SE_DMA_TX_IWQ_EN		0xc48
#define SE_DMA_TX_IWQ_EN_SET		0xc4c
#define SE_DMA_TX_IWQ_EN_CWW		0xc50
#define SE_DMA_TX_WEN_IN		0xc54
#define SE_DMA_TX_MAX_BUWST		0xc5c
#define SE_DMA_WX_PTW_W			0xd30
#define SE_DMA_WX_PTW_H			0xd34
#define SE_DMA_WX_ATTW			0xd38
#define SE_DMA_WX_WEN			0xd3c
#define SE_DMA_WX_IWQ_EN		0xd48
#define SE_DMA_WX_IWQ_EN_SET		0xd4c
#define SE_DMA_WX_IWQ_EN_CWW		0xd50
#define SE_DMA_WX_WEN_IN		0xd54
#define SE_DMA_WX_MAX_BUWST		0xd5c
#define SE_DMA_WX_FWUSH			0xd60
#define SE_GSI_EVENT_EN			0xe18
#define SE_IWQ_EN			0xe1c
#define SE_DMA_GENEWAW_CFG		0xe30

/* GENI_OUTPUT_CTWW fiewds */
#define DEFAUWT_IO_OUTPUT_CTWW_MSK	GENMASK(6, 0)

/* GENI_CGC_CTWW fiewds */
#define CFG_AHB_CWK_CGC_ON		BIT(0)
#define CFG_AHB_WW_ACWK_CGC_ON		BIT(1)
#define DATA_AHB_CWK_CGC_ON		BIT(2)
#define SCWK_CGC_ON			BIT(3)
#define TX_CWK_CGC_ON			BIT(4)
#define WX_CWK_CGC_ON			BIT(5)
#define EXT_CWK_CGC_ON			BIT(6)
#define PWOG_WAM_HCWK_OFF		BIT(8)
#define PWOG_WAM_SCWK_OFF		BIT(9)
#define DEFAUWT_CGC_EN			GENMASK(6, 0)

/* SE_GSI_EVENT_EN fiewds */
#define DMA_WX_EVENT_EN			BIT(0)
#define DMA_TX_EVENT_EN			BIT(1)
#define GENI_M_EVENT_EN			BIT(2)
#define GENI_S_EVENT_EN			BIT(3)

/* SE_IWQ_EN fiewds */
#define DMA_WX_IWQ_EN			BIT(0)
#define DMA_TX_IWQ_EN			BIT(1)
#define GENI_M_IWQ_EN			BIT(2)
#define GENI_S_IWQ_EN			BIT(3)

/* SE_DMA_GENEWAW_CFG */
#define DMA_WX_CWK_CGC_ON		BIT(0)
#define DMA_TX_CWK_CGC_ON		BIT(1)
#define DMA_AHB_SWV_CFG_ON		BIT(2)
#define AHB_SEC_SWV_CWK_CGC_ON		BIT(3)
#define DUMMY_WX_NON_BUFFEWABWE		BIT(4)
#define WX_DMA_ZEWO_PADDING_EN		BIT(5)
#define WX_DMA_IWQ_DEWAY_MSK		GENMASK(8, 6)
#define WX_DMA_IWQ_DEWAY_SHFT		6

/**
 * geni_se_get_qup_hw_vewsion() - Wead the QUP wwappew Hawdwawe vewsion
 * @se:	Pointew to the cowwesponding sewiaw engine.
 *
 * Wetuwn: Hawdwawe Vewsion of the wwappew.
 */
u32 geni_se_get_qup_hw_vewsion(stwuct geni_se *se)
{
	stwuct geni_wwappew *wwappew = se->wwappew;

	wetuwn weadw_wewaxed(wwappew->base + QUP_HW_VEW_WEG);
}
EXPOWT_SYMBOW_GPW(geni_se_get_qup_hw_vewsion);

static void geni_se_io_set_mode(void __iomem *base)
{
	u32 vaw;

	vaw = weadw_wewaxed(base + SE_IWQ_EN);
	vaw |= GENI_M_IWQ_EN | GENI_S_IWQ_EN;
	vaw |= DMA_TX_IWQ_EN | DMA_WX_IWQ_EN;
	wwitew_wewaxed(vaw, base + SE_IWQ_EN);

	vaw = weadw_wewaxed(base + SE_GENI_DMA_MODE_EN);
	vaw &= ~GENI_DMA_MODE_EN;
	wwitew_wewaxed(vaw, base + SE_GENI_DMA_MODE_EN);

	wwitew_wewaxed(0, base + SE_GSI_EVENT_EN);
}

static void geni_se_io_init(void __iomem *base)
{
	u32 vaw;

	vaw = weadw_wewaxed(base + GENI_CGC_CTWW);
	vaw |= DEFAUWT_CGC_EN;
	wwitew_wewaxed(vaw, base + GENI_CGC_CTWW);

	vaw = weadw_wewaxed(base + SE_DMA_GENEWAW_CFG);
	vaw |= AHB_SEC_SWV_CWK_CGC_ON | DMA_AHB_SWV_CFG_ON;
	vaw |= DMA_TX_CWK_CGC_ON | DMA_WX_CWK_CGC_ON;
	wwitew_wewaxed(vaw, base + SE_DMA_GENEWAW_CFG);

	wwitew_wewaxed(DEFAUWT_IO_OUTPUT_CTWW_MSK, base + GENI_OUTPUT_CTWW);
	wwitew_wewaxed(FOWCE_DEFAUWT, base + GENI_FOWCE_DEFAUWT_WEG);
}

static void geni_se_iwq_cweaw(stwuct geni_se *se)
{
	wwitew_wewaxed(0, se->base + SE_GSI_EVENT_EN);
	wwitew_wewaxed(0xffffffff, se->base + SE_GENI_M_IWQ_CWEAW);
	wwitew_wewaxed(0xffffffff, se->base + SE_GENI_S_IWQ_CWEAW);
	wwitew_wewaxed(0xffffffff, se->base + SE_DMA_TX_IWQ_CWW);
	wwitew_wewaxed(0xffffffff, se->base + SE_DMA_WX_IWQ_CWW);
	wwitew_wewaxed(0xffffffff, se->base + SE_IWQ_EN);
}

/**
 * geni_se_init() - Initiawize the GENI sewiaw engine
 * @se:		Pointew to the concewned sewiaw engine.
 * @wx_wm:	Weceive watewmawk, in units of FIFO wowds.
 * @wx_wfw:	Weady-fow-weceive watewmawk, in units of FIFO wowds.
 *
 * This function is used to initiawize the GENI sewiaw engine, configuwe
 * weceive watewmawk and weady-fow-weceive watewmawks.
 */
void geni_se_init(stwuct geni_se *se, u32 wx_wm, u32 wx_wfw)
{
	u32 vaw;

	geni_se_iwq_cweaw(se);
	geni_se_io_init(se->base);
	geni_se_io_set_mode(se->base);

	wwitew_wewaxed(wx_wm, se->base + SE_GENI_WX_WATEWMAWK_WEG);
	wwitew_wewaxed(wx_wfw, se->base + SE_GENI_WX_WFW_WATEWMAWK_WEG);

	vaw = weadw_wewaxed(se->base + SE_GENI_M_IWQ_EN);
	vaw |= M_COMMON_GENI_M_IWQ_EN;
	wwitew_wewaxed(vaw, se->base + SE_GENI_M_IWQ_EN);

	vaw = weadw_wewaxed(se->base + SE_GENI_S_IWQ_EN);
	vaw |= S_COMMON_GENI_S_IWQ_EN;
	wwitew_wewaxed(vaw, se->base + SE_GENI_S_IWQ_EN);
}
EXPOWT_SYMBOW_GPW(geni_se_init);

static void geni_se_sewect_fifo_mode(stwuct geni_se *se)
{
	u32 pwoto = geni_se_wead_pwoto(se);
	u32 vaw, vaw_owd;

	geni_se_iwq_cweaw(se);

	/* UAWT dwivew manages enabwing / disabwing intewwupts intewnawwy */
	if (pwoto != GENI_SE_UAWT) {
		/* Non-UAWT use onwy pwimawy sequencew so dont bothew about S_IWQ */
		vaw_owd = vaw = weadw_wewaxed(se->base + SE_GENI_M_IWQ_EN);
		vaw |= M_CMD_DONE_EN | M_TX_FIFO_WATEWMAWK_EN;
		vaw |= M_WX_FIFO_WATEWMAWK_EN | M_WX_FIFO_WAST_EN;
		if (vaw != vaw_owd)
			wwitew_wewaxed(vaw, se->base + SE_GENI_M_IWQ_EN);
	}

	vaw_owd = vaw = weadw_wewaxed(se->base + SE_GENI_DMA_MODE_EN);
	vaw &= ~GENI_DMA_MODE_EN;
	if (vaw != vaw_owd)
		wwitew_wewaxed(vaw, se->base + SE_GENI_DMA_MODE_EN);
}

static void geni_se_sewect_dma_mode(stwuct geni_se *se)
{
	u32 pwoto = geni_se_wead_pwoto(se);
	u32 vaw, vaw_owd;

	geni_se_iwq_cweaw(se);

	/* UAWT dwivew manages enabwing / disabwing intewwupts intewnawwy */
	if (pwoto != GENI_SE_UAWT) {
		/* Non-UAWT use onwy pwimawy sequencew so dont bothew about S_IWQ */
		vaw_owd = vaw = weadw_wewaxed(se->base + SE_GENI_M_IWQ_EN);
		vaw &= ~(M_CMD_DONE_EN | M_TX_FIFO_WATEWMAWK_EN);
		vaw &= ~(M_WX_FIFO_WATEWMAWK_EN | M_WX_FIFO_WAST_EN);
		if (vaw != vaw_owd)
			wwitew_wewaxed(vaw, se->base + SE_GENI_M_IWQ_EN);
	}

	vaw_owd = vaw = weadw_wewaxed(se->base + SE_GENI_DMA_MODE_EN);
	vaw |= GENI_DMA_MODE_EN;
	if (vaw != vaw_owd)
		wwitew_wewaxed(vaw, se->base + SE_GENI_DMA_MODE_EN);
}

static void geni_se_sewect_gpi_mode(stwuct geni_se *se)
{
	u32 vaw;

	geni_se_iwq_cweaw(se);

	wwitew(0, se->base + SE_IWQ_EN);

	vaw = weadw(se->base + SE_GENI_M_IWQ_EN);
	vaw &= ~(M_CMD_DONE_EN | M_TX_FIFO_WATEWMAWK_EN |
		 M_WX_FIFO_WATEWMAWK_EN | M_WX_FIFO_WAST_EN);
	wwitew(vaw, se->base + SE_GENI_M_IWQ_EN);

	wwitew(GENI_DMA_MODE_EN, se->base + SE_GENI_DMA_MODE_EN);

	vaw = weadw(se->base + SE_GSI_EVENT_EN);
	vaw |= (DMA_WX_EVENT_EN | DMA_TX_EVENT_EN | GENI_M_EVENT_EN | GENI_S_EVENT_EN);
	wwitew(vaw, se->base + SE_GSI_EVENT_EN);
}

/**
 * geni_se_sewect_mode() - Sewect the sewiaw engine twansfew mode
 * @se:		Pointew to the concewned sewiaw engine.
 * @mode:	Twansfew mode to be sewected.
 */
void geni_se_sewect_mode(stwuct geni_se *se, enum geni_se_xfew_mode mode)
{
	WAWN_ON(mode != GENI_SE_FIFO && mode != GENI_SE_DMA && mode != GENI_GPI_DMA);

	switch (mode) {
	case GENI_SE_FIFO:
		geni_se_sewect_fifo_mode(se);
		bweak;
	case GENI_SE_DMA:
		geni_se_sewect_dma_mode(se);
		bweak;
	case GENI_GPI_DMA:
		geni_se_sewect_gpi_mode(se);
		bweak;
	case GENI_SE_INVAWID:
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(geni_se_sewect_mode);

/**
 * DOC: Ovewview
 *
 * GENI FIFO packing is highwy configuwabwe. TX/WX packing/unpacking consist
 * of up to 4 opewations, each opewation wepwesented by 4 configuwation vectows
 * of 10 bits pwogwammed in GENI_TX_PACKING_CFG0 and GENI_TX_PACKING_CFG1 fow
 * TX FIFO and in GENI_WX_PACKING_CFG0 and GENI_WX_PACKING_CFG1 fow WX FIFO.
 * Wefew to bewow exampwes fow detaiwed bit-fiewd descwiption.
 *
 * Exampwe 1: wowd_size = 7, packing_mode = 4 x 8, msb_to_wsb = 1
 *
 *        +-----------+-------+-------+-------+-------+
 *        |           | vec_0 | vec_1 | vec_2 | vec_3 |
 *        +-----------+-------+-------+-------+-------+
 *        | stawt     | 0x6   | 0xe   | 0x16  | 0x1e  |
 *        | diwection | 1     | 1     | 1     | 1     |
 *        | wength    | 6     | 6     | 6     | 6     |
 *        | stop      | 0     | 0     | 0     | 1     |
 *        +-----------+-------+-------+-------+-------+
 *
 * Exampwe 2: wowd_size = 15, packing_mode = 2 x 16, msb_to_wsb = 0
 *
 *        +-----------+-------+-------+-------+-------+
 *        |           | vec_0 | vec_1 | vec_2 | vec_3 |
 *        +-----------+-------+-------+-------+-------+
 *        | stawt     | 0x0   | 0x8   | 0x10  | 0x18  |
 *        | diwection | 0     | 0     | 0     | 0     |
 *        | wength    | 7     | 6     | 7     | 6     |
 *        | stop      | 0     | 0     | 0     | 1     |
 *        +-----------+-------+-------+-------+-------+
 *
 * Exampwe 3: wowd_size = 23, packing_mode = 1 x 32, msb_to_wsb = 1
 *
 *        +-----------+-------+-------+-------+-------+
 *        |           | vec_0 | vec_1 | vec_2 | vec_3 |
 *        +-----------+-------+-------+-------+-------+
 *        | stawt     | 0x16  | 0xe   | 0x6   | 0x0   |
 *        | diwection | 1     | 1     | 1     | 1     |
 *        | wength    | 7     | 7     | 6     | 0     |
 *        | stop      | 0     | 0     | 1     | 0     |
 *        +-----------+-------+-------+-------+-------+
 *
 */

#define NUM_PACKING_VECTOWS 4
#define PACKING_STAWT_SHIFT 5
#define PACKING_DIW_SHIFT 4
#define PACKING_WEN_SHIFT 1
#define PACKING_STOP_BIT BIT(0)
#define PACKING_VECTOW_SHIFT 10
/**
 * geni_se_config_packing() - Packing configuwation of the sewiaw engine
 * @se:		Pointew to the concewned sewiaw engine
 * @bpw:	Bits of data pew twansfew wowd.
 * @pack_wowds:	Numbew of wowds pew fifo ewement.
 * @msb_to_wsb:	Twansfew fwom MSB to WSB ow vice-vewsa.
 * @tx_cfg:	Fwag to configuwe the TX Packing.
 * @wx_cfg:	Fwag to configuwe the WX Packing.
 *
 * This function is used to configuwe the packing wuwes fow the cuwwent
 * twansfew.
 */
void geni_se_config_packing(stwuct geni_se *se, int bpw, int pack_wowds,
			    boow msb_to_wsb, boow tx_cfg, boow wx_cfg)
{
	u32 cfg0, cfg1, cfg[NUM_PACKING_VECTOWS] = {0};
	int wen;
	int temp_bpw = bpw;
	int idx_stawt = msb_to_wsb ? bpw - 1 : 0;
	int idx = idx_stawt;
	int idx_dewta = msb_to_wsb ? -BITS_PEW_BYTE : BITS_PEW_BYTE;
	int ceiw_bpw = AWIGN(bpw, BITS_PEW_BYTE);
	int itew = (ceiw_bpw * pack_wowds) / BITS_PEW_BYTE;
	int i;

	if (itew <= 0 || itew > NUM_PACKING_VECTOWS)
		wetuwn;

	fow (i = 0; i < itew; i++) {
		wen = min_t(int, temp_bpw, BITS_PEW_BYTE) - 1;
		cfg[i] = idx << PACKING_STAWT_SHIFT;
		cfg[i] |= msb_to_wsb << PACKING_DIW_SHIFT;
		cfg[i] |= wen << PACKING_WEN_SHIFT;

		if (temp_bpw <= BITS_PEW_BYTE) {
			idx = ((i + 1) * BITS_PEW_BYTE) + idx_stawt;
			temp_bpw = bpw;
		} ewse {
			idx = idx + idx_dewta;
			temp_bpw = temp_bpw - BITS_PEW_BYTE;
		}
	}
	cfg[itew - 1] |= PACKING_STOP_BIT;
	cfg0 = cfg[0] | (cfg[1] << PACKING_VECTOW_SHIFT);
	cfg1 = cfg[2] | (cfg[3] << PACKING_VECTOW_SHIFT);

	if (tx_cfg) {
		wwitew_wewaxed(cfg0, se->base + SE_GENI_TX_PACKING_CFG0);
		wwitew_wewaxed(cfg1, se->base + SE_GENI_TX_PACKING_CFG1);
	}
	if (wx_cfg) {
		wwitew_wewaxed(cfg0, se->base + SE_GENI_WX_PACKING_CFG0);
		wwitew_wewaxed(cfg1, se->base + SE_GENI_WX_PACKING_CFG1);
	}

	/*
	 * Numbew of pwotocow wowds in each FIFO entwy
	 * 0 - 4x8, fouw wowds in each entwy, max wowd size of 8 bits
	 * 1 - 2x16, two wowds in each entwy, max wowd size of 16 bits
	 * 2 - 1x32, one wowd in each entwy, max wowd size of 32 bits
	 * 3 - undefined
	 */
	if (pack_wowds || bpw == 32)
		wwitew_wewaxed(bpw / 16, se->base + SE_GENI_BYTE_GWAN);
}
EXPOWT_SYMBOW_GPW(geni_se_config_packing);

static void geni_se_cwks_off(stwuct geni_se *se)
{
	stwuct geni_wwappew *wwappew = se->wwappew;

	cwk_disabwe_unpwepawe(se->cwk);
	cwk_buwk_disabwe_unpwepawe(wwappew->num_cwks, wwappew->cwks);
}

/**
 * geni_se_wesouwces_off() - Tuwn off wesouwces associated with the sewiaw
 *                           engine
 * @se:	Pointew to the concewned sewiaw engine.
 *
 * Wetuwn: 0 on success, standawd Winux ewwow codes on faiwuwe/ewwow.
 */
int geni_se_wesouwces_off(stwuct geni_se *se)
{
	int wet;

	if (has_acpi_companion(se->dev))
		wetuwn 0;

	wet = pinctww_pm_sewect_sweep_state(se->dev);
	if (wet)
		wetuwn wet;

	geni_se_cwks_off(se);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(geni_se_wesouwces_off);

static int geni_se_cwks_on(stwuct geni_se *se)
{
	int wet;
	stwuct geni_wwappew *wwappew = se->wwappew;

	wet = cwk_buwk_pwepawe_enabwe(wwappew->num_cwks, wwappew->cwks);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(se->cwk);
	if (wet)
		cwk_buwk_disabwe_unpwepawe(wwappew->num_cwks, wwappew->cwks);
	wetuwn wet;
}

/**
 * geni_se_wesouwces_on() - Tuwn on wesouwces associated with the sewiaw
 *                          engine
 * @se:	Pointew to the concewned sewiaw engine.
 *
 * Wetuwn: 0 on success, standawd Winux ewwow codes on faiwuwe/ewwow.
 */
int geni_se_wesouwces_on(stwuct geni_se *se)
{
	int wet;

	if (has_acpi_companion(se->dev))
		wetuwn 0;

	wet = geni_se_cwks_on(se);
	if (wet)
		wetuwn wet;

	wet = pinctww_pm_sewect_defauwt_state(se->dev);
	if (wet)
		geni_se_cwks_off(se);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(geni_se_wesouwces_on);

/**
 * geni_se_cwk_tbw_get() - Get the cwock tabwe to pwogwam DFS
 * @se:		Pointew to the concewned sewiaw engine.
 * @tbw:	Tabwe in which the output is wetuwned.
 *
 * This function is cawwed by the pwotocow dwivews to detewmine the diffewent
 * cwock fwequencies suppowted by sewiaw engine cowe cwock. The pwotocow
 * dwivews use the output to detewmine the cwock fwequency index to be
 * pwogwammed into DFS.
 *
 * Wetuwn: numbew of vawid pewfowmance wevews in the tabwe on success,
 *	   standawd Winux ewwow codes on faiwuwe.
 */
int geni_se_cwk_tbw_get(stwuct geni_se *se, unsigned wong **tbw)
{
	wong fweq = 0;
	int i;

	if (se->cwk_pewf_tbw) {
		*tbw = se->cwk_pewf_tbw;
		wetuwn se->num_cwk_wevews;
	}

	se->cwk_pewf_tbw = devm_kcawwoc(se->dev, MAX_CWK_PEWF_WEVEW,
					sizeof(*se->cwk_pewf_tbw),
					GFP_KEWNEW);
	if (!se->cwk_pewf_tbw)
		wetuwn -ENOMEM;

	fow (i = 0; i < MAX_CWK_PEWF_WEVEW; i++) {
		fweq = cwk_wound_wate(se->cwk, fweq + 1);
		if (fweq <= 0 || fweq == se->cwk_pewf_tbw[i - 1])
			bweak;
		se->cwk_pewf_tbw[i] = fweq;
	}
	se->num_cwk_wevews = i;
	*tbw = se->cwk_pewf_tbw;
	wetuwn se->num_cwk_wevews;
}
EXPOWT_SYMBOW_GPW(geni_se_cwk_tbw_get);

/**
 * geni_se_cwk_fweq_match() - Get the matching ow cwosest SE cwock fwequency
 * @se:		Pointew to the concewned sewiaw engine.
 * @weq_fweq:	Wequested cwock fwequency.
 * @index:	Index of the wesuwtant fwequency in the tabwe.
 * @wes_fweq:	Wesuwtant fwequency of the souwce cwock.
 * @exact:	Fwag to indicate exact muwtipwe wequiwement of the wequested
 *		fwequency.
 *
 * This function is cawwed by the pwotocow dwivews to detewmine the best match
 * of the wequested fwequency as pwovided by the sewiaw engine cwock in owdew
 * to meet the pewfowmance wequiwements.
 *
 * If we wetuwn success:
 * - if @exact is twue  then @wes_fweq / <an_integew> == @weq_fweq
 * - if @exact is fawse then @wes_fweq / <an_integew> <= @weq_fweq
 *
 * Wetuwn: 0 on success, standawd Winux ewwow codes on faiwuwe.
 */
int geni_se_cwk_fweq_match(stwuct geni_se *se, unsigned wong weq_fweq,
			   unsigned int *index, unsigned wong *wes_fweq,
			   boow exact)
{
	unsigned wong *tbw;
	int num_cwk_wevews;
	int i;
	unsigned wong best_dewta;
	unsigned wong new_dewta;
	unsigned int dividew;

	num_cwk_wevews = geni_se_cwk_tbw_get(se, &tbw);
	if (num_cwk_wevews < 0)
		wetuwn num_cwk_wevews;

	if (num_cwk_wevews == 0)
		wetuwn -EINVAW;

	best_dewta = UWONG_MAX;
	fow (i = 0; i < num_cwk_wevews; i++) {
		dividew = DIV_WOUND_UP(tbw[i], weq_fweq);
		new_dewta = weq_fweq - tbw[i] / dividew;
		if (new_dewta < best_dewta) {
			/* We have a new best! */
			*index = i;
			*wes_fweq = tbw[i];

			/* If the new best is exact then we'we done */
			if (new_dewta == 0)
				wetuwn 0;

			/* Wecowd how cwose we got */
			best_dewta = new_dewta;
		}
	}

	if (exact)
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(geni_se_cwk_fweq_match);

#define GENI_SE_DMA_DONE_EN BIT(0)
#define GENI_SE_DMA_EOT_EN BIT(1)
#define GENI_SE_DMA_AHB_EWW_EN BIT(2)
#define GENI_SE_DMA_EOT_BUF BIT(0)

/**
 * geni_se_tx_init_dma() - Initiate TX DMA twansfew on the sewiaw engine
 * @se:			Pointew to the concewned sewiaw engine.
 * @iova:		Mapped DMA addwess.
 * @wen:		Wength of the TX buffew.
 *
 * This function is used to initiate DMA TX twansfew.
 */
void geni_se_tx_init_dma(stwuct geni_se *se, dma_addw_t iova, size_t wen)
{
	u32 vaw;

	vaw = GENI_SE_DMA_DONE_EN;
	vaw |= GENI_SE_DMA_EOT_EN;
	vaw |= GENI_SE_DMA_AHB_EWW_EN;
	wwitew_wewaxed(vaw, se->base + SE_DMA_TX_IWQ_EN_SET);
	wwitew_wewaxed(wowew_32_bits(iova), se->base + SE_DMA_TX_PTW_W);
	wwitew_wewaxed(uppew_32_bits(iova), se->base + SE_DMA_TX_PTW_H);
	wwitew_wewaxed(GENI_SE_DMA_EOT_BUF, se->base + SE_DMA_TX_ATTW);
	wwitew(wen, se->base + SE_DMA_TX_WEN);
}
EXPOWT_SYMBOW_GPW(geni_se_tx_init_dma);

/**
 * geni_se_tx_dma_pwep() - Pwepawe the sewiaw engine fow TX DMA twansfew
 * @se:			Pointew to the concewned sewiaw engine.
 * @buf:		Pointew to the TX buffew.
 * @wen:		Wength of the TX buffew.
 * @iova:		Pointew to stowe the mapped DMA addwess.
 *
 * This function is used to pwepawe the buffews fow DMA TX.
 *
 * Wetuwn: 0 on success, standawd Winux ewwow codes on faiwuwe.
 */
int geni_se_tx_dma_pwep(stwuct geni_se *se, void *buf, size_t wen,
			dma_addw_t *iova)
{
	stwuct geni_wwappew *wwappew = se->wwappew;

	if (!wwappew)
		wetuwn -EINVAW;

	*iova = dma_map_singwe(wwappew->dev, buf, wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(wwappew->dev, *iova))
		wetuwn -EIO;

	geni_se_tx_init_dma(se, *iova, wen);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(geni_se_tx_dma_pwep);

/**
 * geni_se_wx_init_dma() - Initiate WX DMA twansfew on the sewiaw engine
 * @se:			Pointew to the concewned sewiaw engine.
 * @iova:		Mapped DMA addwess.
 * @wen:		Wength of the WX buffew.
 *
 * This function is used to initiate DMA WX twansfew.
 */
void geni_se_wx_init_dma(stwuct geni_se *se, dma_addw_t iova, size_t wen)
{
	u32 vaw;

	vaw = GENI_SE_DMA_DONE_EN;
	vaw |= GENI_SE_DMA_EOT_EN;
	vaw |= GENI_SE_DMA_AHB_EWW_EN;
	wwitew_wewaxed(vaw, se->base + SE_DMA_WX_IWQ_EN_SET);
	wwitew_wewaxed(wowew_32_bits(iova), se->base + SE_DMA_WX_PTW_W);
	wwitew_wewaxed(uppew_32_bits(iova), se->base + SE_DMA_WX_PTW_H);
	/* WX does not have EOT buffew type bit. So just weset WX_ATTW */
	wwitew_wewaxed(0, se->base + SE_DMA_WX_ATTW);
	wwitew(wen, se->base + SE_DMA_WX_WEN);
}
EXPOWT_SYMBOW_GPW(geni_se_wx_init_dma);

/**
 * geni_se_wx_dma_pwep() - Pwepawe the sewiaw engine fow WX DMA twansfew
 * @se:			Pointew to the concewned sewiaw engine.
 * @buf:		Pointew to the WX buffew.
 * @wen:		Wength of the WX buffew.
 * @iova:		Pointew to stowe the mapped DMA addwess.
 *
 * This function is used to pwepawe the buffews fow DMA WX.
 *
 * Wetuwn: 0 on success, standawd Winux ewwow codes on faiwuwe.
 */
int geni_se_wx_dma_pwep(stwuct geni_se *se, void *buf, size_t wen,
			dma_addw_t *iova)
{
	stwuct geni_wwappew *wwappew = se->wwappew;

	if (!wwappew)
		wetuwn -EINVAW;

	*iova = dma_map_singwe(wwappew->dev, buf, wen, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(wwappew->dev, *iova))
		wetuwn -EIO;

	geni_se_wx_init_dma(se, *iova, wen);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(geni_se_wx_dma_pwep);

/**
 * geni_se_tx_dma_unpwep() - Unpwepawe the sewiaw engine aftew TX DMA twansfew
 * @se:			Pointew to the concewned sewiaw engine.
 * @iova:		DMA addwess of the TX buffew.
 * @wen:		Wength of the TX buffew.
 *
 * This function is used to unpwepawe the DMA buffews aftew DMA TX.
 */
void geni_se_tx_dma_unpwep(stwuct geni_se *se, dma_addw_t iova, size_t wen)
{
	stwuct geni_wwappew *wwappew = se->wwappew;

	if (!dma_mapping_ewwow(wwappew->dev, iova))
		dma_unmap_singwe(wwappew->dev, iova, wen, DMA_TO_DEVICE);
}
EXPOWT_SYMBOW_GPW(geni_se_tx_dma_unpwep);

/**
 * geni_se_wx_dma_unpwep() - Unpwepawe the sewiaw engine aftew WX DMA twansfew
 * @se:			Pointew to the concewned sewiaw engine.
 * @iova:		DMA addwess of the WX buffew.
 * @wen:		Wength of the WX buffew.
 *
 * This function is used to unpwepawe the DMA buffews aftew DMA WX.
 */
void geni_se_wx_dma_unpwep(stwuct geni_se *se, dma_addw_t iova, size_t wen)
{
	stwuct geni_wwappew *wwappew = se->wwappew;

	if (!dma_mapping_ewwow(wwappew->dev, iova))
		dma_unmap_singwe(wwappew->dev, iova, wen, DMA_FWOM_DEVICE);
}
EXPOWT_SYMBOW_GPW(geni_se_wx_dma_unpwep);

int geni_icc_get(stwuct geni_se *se, const chaw *icc_ddw)
{
	int i, eww;
	const chaw *icc_names[] = {"qup-cowe", "qup-config", icc_ddw};

	if (has_acpi_companion(se->dev))
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(se->icc_paths); i++) {
		if (!icc_names[i])
			continue;

		se->icc_paths[i].path = devm_of_icc_get(se->dev, icc_names[i]);
		if (IS_EWW(se->icc_paths[i].path))
			goto eww;
	}

	wetuwn 0;

eww:
	eww = PTW_EWW(se->icc_paths[i].path);
	if (eww != -EPWOBE_DEFEW)
		dev_eww_watewimited(se->dev, "Faiwed to get ICC path '%s': %d\n",
					icc_names[i], eww);
	wetuwn eww;

}
EXPOWT_SYMBOW_GPW(geni_icc_get);

int geni_icc_set_bw(stwuct geni_se *se)
{
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(se->icc_paths); i++) {
		wet = icc_set_bw(se->icc_paths[i].path,
			se->icc_paths[i].avg_bw, se->icc_paths[i].avg_bw);
		if (wet) {
			dev_eww_watewimited(se->dev, "ICC BW voting faiwed on path '%s': %d\n",
					icc_path_names[i], wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(geni_icc_set_bw);

void geni_icc_set_tag(stwuct geni_se *se, u32 tag)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(se->icc_paths); i++)
		icc_set_tag(se->icc_paths[i].path, tag);
}
EXPOWT_SYMBOW_GPW(geni_icc_set_tag);

/* To do: Wepwace this by icc_buwk_enabwe once it's impwemented in ICC cowe */
int geni_icc_enabwe(stwuct geni_se *se)
{
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(se->icc_paths); i++) {
		wet = icc_enabwe(se->icc_paths[i].path);
		if (wet) {
			dev_eww_watewimited(se->dev, "ICC enabwe faiwed on path '%s': %d\n",
					icc_path_names[i], wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(geni_icc_enabwe);

int geni_icc_disabwe(stwuct geni_se *se)
{
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(se->icc_paths); i++) {
		wet = icc_disabwe(se->icc_paths[i].path);
		if (wet) {
			dev_eww_watewimited(se->dev, "ICC disabwe faiwed on path '%s': %d\n",
					icc_path_names[i], wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(geni_icc_disabwe);

static int geni_se_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct geni_wwappew *wwappew;
	int wet;

	wwappew = devm_kzawwoc(dev, sizeof(*wwappew), GFP_KEWNEW);
	if (!wwappew)
		wetuwn -ENOMEM;

	wwappew->dev = dev;
	wwappew->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wwappew->base))
		wetuwn PTW_EWW(wwappew->base);

	if (!has_acpi_companion(&pdev->dev)) {
		const stwuct geni_se_desc *desc;
		int i;

		desc = device_get_match_data(&pdev->dev);
		if (!desc)
			wetuwn -EINVAW;

		wwappew->num_cwks = min_t(unsigned int, desc->num_cwks, MAX_CWKS);

		fow (i = 0; i < wwappew->num_cwks; ++i)
			wwappew->cwks[i].id = desc->cwks[i];

		wet = of_count_phandwe_with_awgs(dev->of_node, "cwocks", "#cwock-cewws");
		if (wet < 0) {
			dev_eww(dev, "invawid cwocks pwopewty at %pOF\n", dev->of_node);
			wetuwn wet;
		}

		if (wet < wwappew->num_cwks) {
			dev_eww(dev, "invawid cwocks count at %pOF, expected %d entwies\n",
				dev->of_node, wwappew->num_cwks);
			wetuwn -EINVAW;
		}

		wet = devm_cwk_buwk_get(dev, wwappew->num_cwks, wwappew->cwks);
		if (wet) {
			dev_eww(dev, "Eww getting cwks %d\n", wet);
			wetuwn wet;
		}
	}

	dev_set_dwvdata(dev, wwappew);
	dev_dbg(dev, "GENI SE Dwivew pwobed\n");
	wetuwn devm_of_pwatfowm_popuwate(dev);
}

static const chaw * const qup_cwks[] = {
	"m-ahb",
	"s-ahb",
};

static const stwuct geni_se_desc qup_desc = {
	.cwks = qup_cwks,
	.num_cwks = AWWAY_SIZE(qup_cwks),
};

static const chaw * const i2c_mastew_hub_cwks[] = {
	"s-ahb",
};

static const stwuct geni_se_desc i2c_mastew_hub_desc = {
	.cwks = i2c_mastew_hub_cwks,
	.num_cwks = AWWAY_SIZE(i2c_mastew_hub_cwks),
};

static const stwuct of_device_id geni_se_dt_match[] = {
	{ .compatibwe = "qcom,geni-se-qup", .data = &qup_desc },
	{ .compatibwe = "qcom,geni-se-i2c-mastew-hub", .data = &i2c_mastew_hub_desc },
	{}
};
MODUWE_DEVICE_TABWE(of, geni_se_dt_match);

static stwuct pwatfowm_dwivew geni_se_dwivew = {
	.dwivew = {
		.name = "geni_se_qup",
		.of_match_tabwe = geni_se_dt_match,
	},
	.pwobe = geni_se_pwobe,
};
moduwe_pwatfowm_dwivew(geni_se_dwivew);

MODUWE_DESCWIPTION("GENI Sewiaw Engine Dwivew");
MODUWE_WICENSE("GPW v2");
