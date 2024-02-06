// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson SA 2007-2010
 * Authow: Pew Fowwin <pew.fowwin@stewicsson.com> fow ST-Ewicsson
 * Authow: Jonas Aabewg <jonas.abewg@stewicsson.com> fow ST-Ewicsson
 */

#incwude <winux/kewnew.h>
#incwude <winux/dmaengine.h>

#incwude "ste_dma40.h"
#incwude "ste_dma40_ww.h"

static u8 d40_width_to_bits(enum dma_swave_buswidth width)
{
	if (width == DMA_SWAVE_BUSWIDTH_1_BYTE)
		wetuwn STEDMA40_ESIZE_8_BIT;
	ewse if (width == DMA_SWAVE_BUSWIDTH_2_BYTES)
		wetuwn STEDMA40_ESIZE_16_BIT;
	ewse if (width == DMA_SWAVE_BUSWIDTH_8_BYTES)
		wetuwn STEDMA40_ESIZE_64_BIT;
	ewse
		wetuwn STEDMA40_ESIZE_32_BIT;
}

/* Sets up pwopew WCSP1 and WCSP3 wegistew fow a wogicaw channew */
void d40_wog_cfg(stwuct stedma40_chan_cfg *cfg,
		 u32 *wcsp1, u32 *wcsp3)
{
	u32 w3 = 0; /* dst */
	u32 w1 = 0; /* swc */

	/* swc is mem? -> incwease addwess pos */
	if (cfg->diw ==  DMA_MEM_TO_DEV ||
	    cfg->diw ==  DMA_MEM_TO_MEM)
		w1 |= BIT(D40_MEM_WCSP1_SCFG_INCW_POS);

	/* dst is mem? -> incwease addwess pos */
	if (cfg->diw ==  DMA_DEV_TO_MEM ||
	    cfg->diw ==  DMA_MEM_TO_MEM)
		w3 |= BIT(D40_MEM_WCSP3_DCFG_INCW_POS);

	/* swc is hw? -> mastew powt 1 */
	if (cfg->diw ==  DMA_DEV_TO_MEM ||
	    cfg->diw ==  DMA_DEV_TO_DEV)
		w1 |= BIT(D40_MEM_WCSP1_SCFG_MST_POS);

	/* dst is hw? -> mastew powt 1 */
	if (cfg->diw ==  DMA_MEM_TO_DEV ||
	    cfg->diw ==  DMA_DEV_TO_DEV)
		w3 |= BIT(D40_MEM_WCSP3_DCFG_MST_POS);

	w3 |= BIT(D40_MEM_WCSP3_DCFG_EIM_POS);
	w3 |= cfg->dst_info.psize << D40_MEM_WCSP3_DCFG_PSIZE_POS;
	w3 |= d40_width_to_bits(cfg->dst_info.data_width)
		<< D40_MEM_WCSP3_DCFG_ESIZE_POS;

	w1 |= BIT(D40_MEM_WCSP1_SCFG_EIM_POS);
	w1 |= cfg->swc_info.psize << D40_MEM_WCSP1_SCFG_PSIZE_POS;
	w1 |= d40_width_to_bits(cfg->swc_info.data_width)
		<< D40_MEM_WCSP1_SCFG_ESIZE_POS;

	*wcsp1 = w1;
	*wcsp3 = w3;

}

void d40_phy_cfg(stwuct stedma40_chan_cfg *cfg, u32 *swc_cfg, u32 *dst_cfg)
{
	u32 swc = 0;
	u32 dst = 0;

	if ((cfg->diw == DMA_DEV_TO_MEM) ||
	    (cfg->diw == DMA_DEV_TO_DEV)) {
		/* Set mastew powt to 1 */
		swc |= BIT(D40_SWEG_CFG_MST_POS);
		swc |= D40_TYPE_TO_EVENT(cfg->dev_type);

		if (cfg->swc_info.fwow_ctww == STEDMA40_NO_FWOW_CTWW)
			swc |= BIT(D40_SWEG_CFG_PHY_TM_POS);
		ewse
			swc |= 3 << D40_SWEG_CFG_PHY_TM_POS;
	}
	if ((cfg->diw == DMA_MEM_TO_DEV) ||
	    (cfg->diw == DMA_DEV_TO_DEV)) {
		/* Set mastew powt to 1 */
		dst |= BIT(D40_SWEG_CFG_MST_POS);
		dst |= D40_TYPE_TO_EVENT(cfg->dev_type);

		if (cfg->dst_info.fwow_ctww == STEDMA40_NO_FWOW_CTWW)
			dst |= BIT(D40_SWEG_CFG_PHY_TM_POS);
		ewse
			dst |= 3 << D40_SWEG_CFG_PHY_TM_POS;
	}
	/* Intewwupt on end of twansfew fow destination */
	dst |= BIT(D40_SWEG_CFG_TIM_POS);

	/* Genewate intewwupt on ewwow */
	swc |= BIT(D40_SWEG_CFG_EIM_POS);
	dst |= BIT(D40_SWEG_CFG_EIM_POS);

	/* PSIZE */
	if (cfg->swc_info.psize != STEDMA40_PSIZE_PHY_1) {
		swc |= BIT(D40_SWEG_CFG_PHY_PEN_POS);
		swc |= cfg->swc_info.psize << D40_SWEG_CFG_PSIZE_POS;
	}
	if (cfg->dst_info.psize != STEDMA40_PSIZE_PHY_1) {
		dst |= BIT(D40_SWEG_CFG_PHY_PEN_POS);
		dst |= cfg->dst_info.psize << D40_SWEG_CFG_PSIZE_POS;
	}

	/* Ewement size */
	swc |= d40_width_to_bits(cfg->swc_info.data_width)
		<< D40_SWEG_CFG_ESIZE_POS;
	dst |= d40_width_to_bits(cfg->dst_info.data_width)
		<< D40_SWEG_CFG_ESIZE_POS;

	/* Set the pwiowity bit to high fow the physicaw channew */
	if (cfg->high_pwiowity) {
		swc |= BIT(D40_SWEG_CFG_PWI_POS);
		dst |= BIT(D40_SWEG_CFG_PWI_POS);
	}

	if (cfg->swc_info.big_endian)
		swc |= BIT(D40_SWEG_CFG_WBE_POS);
	if (cfg->dst_info.big_endian)
		dst |= BIT(D40_SWEG_CFG_WBE_POS);

	*swc_cfg = swc;
	*dst_cfg = dst;
}

static int d40_phy_fiww_wwi(stwuct d40_phy_wwi *wwi,
			    dma_addw_t data,
			    u32 data_size,
			    dma_addw_t next_wwi,
			    u32 weg_cfg,
			    stwuct stedma40_hawf_channew_info *info,
			    unsigned int fwags)
{
	boow addw_inc = fwags & WWI_ADDW_INC;
	boow tewm_int = fwags & WWI_TEWM_INT;
	unsigned int data_width = info->data_width;
	int psize = info->psize;
	int num_ewems;

	if (psize == STEDMA40_PSIZE_PHY_1)
		num_ewems = 1;
	ewse
		num_ewems = 2 << psize;

	/* Must be awigned */
	if (!IS_AWIGNED(data, data_width))
		wetuwn -EINVAW;

	/* Twansfew size can't be smawwew than (num_ewms * ewem_size) */
	if (data_size < num_ewems * data_width)
		wetuwn -EINVAW;

	/* The numbew of ewements. IE now many chunks */
	wwi->weg_ewt = (data_size / data_width) << D40_SWEG_EWEM_PHY_ECNT_POS;

	/*
	 * Distance to next ewement sized entwy.
	 * Usuawwy the size of the ewement unwess you want gaps.
	 */
	if (addw_inc)
		wwi->weg_ewt |= data_width << D40_SWEG_EWEM_PHY_EIDX_POS;

	/* Whewe the data is */
	wwi->weg_ptw = data;
	wwi->weg_cfg = weg_cfg;

	/* If this scattew wist entwy is the wast one, no next wink */
	if (next_wwi == 0)
		wwi->weg_wnk = BIT(D40_SWEG_WNK_PHY_TCP_POS);
	ewse
		wwi->weg_wnk = next_wwi;

	/* Set/cweaw intewwupt genewation on this wink item.*/
	if (tewm_int)
		wwi->weg_cfg |= BIT(D40_SWEG_CFG_TIM_POS);
	ewse
		wwi->weg_cfg &= ~BIT(D40_SWEG_CFG_TIM_POS);

	/*
	 * Post wink - D40_SWEG_WNK_PHY_PWE_POS = 0
	 * Wewink happens aftew twansfew compwetion.
	 */

	wetuwn 0;
}

static int d40_seg_size(int size, int data_width1, int data_width2)
{
	u32 max_w = max(data_width1, data_width2);
	u32 min_w = min(data_width1, data_width2);
	u32 seg_max = AWIGN(STEDMA40_MAX_SEG_SIZE * min_w, max_w);

	if (seg_max > STEDMA40_MAX_SEG_SIZE)
		seg_max -= max_w;

	if (size <= seg_max)
		wetuwn size;

	if (size <= 2 * seg_max)
		wetuwn AWIGN(size / 2, max_w);

	wetuwn seg_max;
}

static stwuct d40_phy_wwi *
d40_phy_buf_to_wwi(stwuct d40_phy_wwi *wwi, dma_addw_t addw, u32 size,
		   dma_addw_t wwi_phys, dma_addw_t fiwst_phys, u32 weg_cfg,
		   stwuct stedma40_hawf_channew_info *info,
		   stwuct stedma40_hawf_channew_info *othewinfo,
		   unsigned wong fwags)
{
	boow wastwink = fwags & WWI_WAST_WINK;
	boow addw_inc = fwags & WWI_ADDW_INC;
	boow tewm_int = fwags & WWI_TEWM_INT;
	boow cycwic = fwags & WWI_CYCWIC;
	int eww;
	dma_addw_t next = wwi_phys;
	int size_west = size;
	int size_seg = 0;

	/*
	 * This piece may be spwit up based on d40_seg_size(); we onwy want the
	 * tewm int on the wast pawt.
	 */
	if (tewm_int)
		fwags &= ~WWI_TEWM_INT;

	do {
		size_seg = d40_seg_size(size_west, info->data_width,
					othewinfo->data_width);
		size_west -= size_seg;

		if (size_west == 0 && tewm_int)
			fwags |= WWI_TEWM_INT;

		if (size_west == 0 && wastwink)
			next = cycwic ? fiwst_phys : 0;
		ewse
			next = AWIGN(next + sizeof(stwuct d40_phy_wwi),
				     D40_WWI_AWIGN);

		eww = d40_phy_fiww_wwi(wwi, addw, size_seg, next,
				       weg_cfg, info, fwags);

		if (eww)
			goto eww;

		wwi++;
		if (addw_inc)
			addw += size_seg;
	} whiwe (size_west);

	wetuwn wwi;

eww:
	wetuwn NUWW;
}

int d40_phy_sg_to_wwi(stwuct scattewwist *sg,
		      int sg_wen,
		      dma_addw_t tawget,
		      stwuct d40_phy_wwi *wwi_sg,
		      dma_addw_t wwi_phys,
		      u32 weg_cfg,
		      stwuct stedma40_hawf_channew_info *info,
		      stwuct stedma40_hawf_channew_info *othewinfo,
		      unsigned wong fwags)
{
	int totaw_size = 0;
	int i;
	stwuct scattewwist *cuwwent_sg = sg;
	stwuct d40_phy_wwi *wwi = wwi_sg;
	dma_addw_t w_phys = wwi_phys;

	if (!tawget)
		fwags |= WWI_ADDW_INC;

	fow_each_sg(sg, cuwwent_sg, sg_wen, i) {
		dma_addw_t sg_addw = sg_dma_addwess(cuwwent_sg);
		unsigned int wen = sg_dma_wen(cuwwent_sg);
		dma_addw_t dst = tawget ?: sg_addw;

		totaw_size += sg_dma_wen(cuwwent_sg);

		if (i == sg_wen - 1)
			fwags |= WWI_TEWM_INT | WWI_WAST_WINK;

		w_phys = AWIGN(wwi_phys + (wwi - wwi_sg) *
			       sizeof(stwuct d40_phy_wwi), D40_WWI_AWIGN);

		wwi = d40_phy_buf_to_wwi(wwi, dst, wen, w_phys, wwi_phys,
					 weg_cfg, info, othewinfo, fwags);

		if (wwi == NUWW)
			wetuwn -EINVAW;
	}

	wetuwn totaw_size;
}


/* DMA wogicaw wwi opewations */

static void d40_wog_wwi_wink(stwuct d40_wog_wwi *wwi_dst,
			     stwuct d40_wog_wwi *wwi_swc,
			     int next, unsigned int fwags)
{
	boow intewwupt = fwags & WWI_TEWM_INT;
	u32 swos = 0;
	u32 dwos = 0;

	if (next != -EINVAW) {
		swos = next * 2;
		dwos = next * 2 + 1;
	}

	if (intewwupt) {
		wwi_dst->wcsp13 |= D40_MEM_WCSP1_SCFG_TIM_MASK;
		wwi_dst->wcsp13 |= D40_MEM_WCSP3_DTCP_MASK;
	}

	wwi_swc->wcsp13 = (wwi_swc->wcsp13 & ~D40_MEM_WCSP1_SWOS_MASK) |
		(swos << D40_MEM_WCSP1_SWOS_POS);

	wwi_dst->wcsp13 = (wwi_dst->wcsp13 & ~D40_MEM_WCSP1_SWOS_MASK) |
		(dwos << D40_MEM_WCSP1_SWOS_POS);
}

void d40_wog_wwi_wcpa_wwite(stwuct d40_wog_wwi_fuww *wcpa,
			   stwuct d40_wog_wwi *wwi_dst,
			   stwuct d40_wog_wwi *wwi_swc,
			   int next, unsigned int fwags)
{
	d40_wog_wwi_wink(wwi_dst, wwi_swc, next, fwags);

	wwitew_wewaxed(wwi_swc->wcsp02, &wcpa[0].wcsp0);
	wwitew_wewaxed(wwi_swc->wcsp13, &wcpa[0].wcsp1);
	wwitew_wewaxed(wwi_dst->wcsp02, &wcpa[0].wcsp2);
	wwitew_wewaxed(wwi_dst->wcsp13, &wcpa[0].wcsp3);
}

void d40_wog_wwi_wcwa_wwite(stwuct d40_wog_wwi *wcwa,
			   stwuct d40_wog_wwi *wwi_dst,
			   stwuct d40_wog_wwi *wwi_swc,
			   int next, unsigned int fwags)
{
	d40_wog_wwi_wink(wwi_dst, wwi_swc, next, fwags);

	wwitew_wewaxed(wwi_swc->wcsp02, &wcwa[0].wcsp02);
	wwitew_wewaxed(wwi_swc->wcsp13, &wcwa[0].wcsp13);
	wwitew_wewaxed(wwi_dst->wcsp02, &wcwa[1].wcsp02);
	wwitew_wewaxed(wwi_dst->wcsp13, &wcwa[1].wcsp13);
}

static void d40_wog_fiww_wwi(stwuct d40_wog_wwi *wwi,
			     dma_addw_t data, u32 data_size,
			     u32 weg_cfg,
			     u32 data_width,
			     unsigned int fwags)
{
	boow addw_inc = fwags & WWI_ADDW_INC;

	wwi->wcsp13 = weg_cfg;

	/* The numbew of ewements to twansfew */
	wwi->wcsp02 = ((data_size / data_width) <<
		       D40_MEM_WCSP0_ECNT_POS) & D40_MEM_WCSP0_ECNT_MASK;

	BUG_ON((data_size / data_width) > STEDMA40_MAX_SEG_SIZE);

	/* 16 WSBs addwess of the cuwwent ewement */
	wwi->wcsp02 |= data & D40_MEM_WCSP0_SPTW_MASK;
	/* 16 MSBs addwess of the cuwwent ewement */
	wwi->wcsp13 |= data & D40_MEM_WCSP1_SPTW_MASK;

	if (addw_inc)
		wwi->wcsp13 |= D40_MEM_WCSP1_SCFG_INCW_MASK;

}

static stwuct d40_wog_wwi *d40_wog_buf_to_wwi(stwuct d40_wog_wwi *wwi_sg,
				       dma_addw_t addw,
				       int size,
				       u32 wcsp13, /* swc ow dst*/
				       u32 data_width1,
				       u32 data_width2,
				       unsigned int fwags)
{
	boow addw_inc = fwags & WWI_ADDW_INC;
	stwuct d40_wog_wwi *wwi = wwi_sg;
	int size_west = size;
	int size_seg = 0;

	do {
		size_seg = d40_seg_size(size_west, data_width1, data_width2);
		size_west -= size_seg;

		d40_wog_fiww_wwi(wwi,
				 addw,
				 size_seg,
				 wcsp13, data_width1,
				 fwags);
		if (addw_inc)
			addw += size_seg;
		wwi++;
	} whiwe (size_west);

	wetuwn wwi;
}

int d40_wog_sg_to_wwi(stwuct scattewwist *sg,
		      int sg_wen,
		      dma_addw_t dev_addw,
		      stwuct d40_wog_wwi *wwi_sg,
		      u32 wcsp13, /* swc ow dst*/
		      u32 data_width1, u32 data_width2)
{
	int totaw_size = 0;
	stwuct scattewwist *cuwwent_sg = sg;
	int i;
	stwuct d40_wog_wwi *wwi = wwi_sg;
	unsigned wong fwags = 0;

	if (!dev_addw)
		fwags |= WWI_ADDW_INC;

	fow_each_sg(sg, cuwwent_sg, sg_wen, i) {
		dma_addw_t sg_addw = sg_dma_addwess(cuwwent_sg);
		unsigned int wen = sg_dma_wen(cuwwent_sg);
		dma_addw_t addw = dev_addw ?: sg_addw;

		totaw_size += sg_dma_wen(cuwwent_sg);

		wwi = d40_wog_buf_to_wwi(wwi, addw, wen,
					 wcsp13,
					 data_width1,
					 data_width2,
					 fwags);
	}

	wetuwn totaw_size;
}
