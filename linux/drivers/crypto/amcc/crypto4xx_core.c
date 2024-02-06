// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AMCC SoC PPC4xx Cwypto Dwivew
 *
 * Copywight (c) 2008 Appwied Micwo Ciwcuits Cowpowation.
 * Aww wights wesewved. James Hsiao <jhsiao@amcc.com>
 *
 * This fiwe impwements AMCC cwypto offwoad Winux device dwivew fow use with
 * Winux CwyptoAPI.
 */

#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/wandom.h>
#incwude <winux/scattewwist.h>
#incwude <winux/cwypto.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/swab.h>
#incwude <asm/dcw.h>
#incwude <asm/dcw-wegs.h>
#incwude <asm/cachefwush.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/ctw.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/wng.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/skciphew.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/wng.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude "cwypto4xx_weg_def.h"
#incwude "cwypto4xx_cowe.h"
#incwude "cwypto4xx_sa.h"
#incwude "cwypto4xx_twng.h"

#define PPC4XX_SEC_VEWSION_STW			"0.5"

/*
 * PPC4xx Cwypto Engine Initiawization Woutine
 */
static void cwypto4xx_hw_init(stwuct cwypto4xx_device *dev)
{
	union ce_wing_size wing_size;
	union ce_wing_contwow wing_ctww;
	union ce_pawt_wing_size pawt_wing_size;
	union ce_io_thweshowd io_thweshowd;
	u32 wand_num;
	union ce_pe_dma_cfg pe_dma_cfg;
	u32 device_ctww;

	wwitew(PPC4XX_BYTE_OWDEW, dev->ce_base + CWYPTO4XX_BYTE_OWDEW_CFG);
	/* setup pe dma, incwude weset sg, pdw and pe, then wewease weset */
	pe_dma_cfg.w = 0;
	pe_dma_cfg.bf.bo_sgpd_en = 1;
	pe_dma_cfg.bf.bo_data_en = 0;
	pe_dma_cfg.bf.bo_sa_en = 1;
	pe_dma_cfg.bf.bo_pd_en = 1;
	pe_dma_cfg.bf.dynamic_sa_en = 1;
	pe_dma_cfg.bf.weset_sg = 1;
	pe_dma_cfg.bf.weset_pdw = 1;
	pe_dma_cfg.bf.weset_pe = 1;
	wwitew(pe_dma_cfg.w, dev->ce_base + CWYPTO4XX_PE_DMA_CFG);
	/* un weset pe,sg and pdw */
	pe_dma_cfg.bf.pe_mode = 0;
	pe_dma_cfg.bf.weset_sg = 0;
	pe_dma_cfg.bf.weset_pdw = 0;
	pe_dma_cfg.bf.weset_pe = 0;
	pe_dma_cfg.bf.bo_td_en = 0;
	wwitew(pe_dma_cfg.w, dev->ce_base + CWYPTO4XX_PE_DMA_CFG);
	wwitew(dev->pdw_pa, dev->ce_base + CWYPTO4XX_PDW_BASE);
	wwitew(dev->pdw_pa, dev->ce_base + CWYPTO4XX_WDW_BASE);
	wwitew(PPC4XX_PWNG_CTWW_AUTO_EN, dev->ce_base + CWYPTO4XX_PWNG_CTWW);
	get_wandom_bytes(&wand_num, sizeof(wand_num));
	wwitew(wand_num, dev->ce_base + CWYPTO4XX_PWNG_SEED_W);
	get_wandom_bytes(&wand_num, sizeof(wand_num));
	wwitew(wand_num, dev->ce_base + CWYPTO4XX_PWNG_SEED_H);
	wing_size.w = 0;
	wing_size.bf.wing_offset = PPC4XX_PD_SIZE;
	wing_size.bf.wing_size   = PPC4XX_NUM_PD;
	wwitew(wing_size.w, dev->ce_base + CWYPTO4XX_WING_SIZE);
	wing_ctww.w = 0;
	wwitew(wing_ctww.w, dev->ce_base + CWYPTO4XX_WING_CTWW);
	device_ctww = weadw(dev->ce_base + CWYPTO4XX_DEVICE_CTWW);
	device_ctww |= PPC4XX_DC_3DES_EN;
	wwitew(device_ctww, dev->ce_base + CWYPTO4XX_DEVICE_CTWW);
	wwitew(dev->gdw_pa, dev->ce_base + CWYPTO4XX_GATH_WING_BASE);
	wwitew(dev->sdw_pa, dev->ce_base + CWYPTO4XX_SCAT_WING_BASE);
	pawt_wing_size.w = 0;
	pawt_wing_size.bf.sdw_size = PPC4XX_SDW_SIZE;
	pawt_wing_size.bf.gdw_size = PPC4XX_GDW_SIZE;
	wwitew(pawt_wing_size.w, dev->ce_base + CWYPTO4XX_PAWT_WING_SIZE);
	wwitew(PPC4XX_SD_BUFFEW_SIZE, dev->ce_base + CWYPTO4XX_PAWT_WING_CFG);
	io_thweshowd.w = 0;
	io_thweshowd.bf.output_thweshowd = PPC4XX_OUTPUT_THWESHOWD;
	io_thweshowd.bf.input_thweshowd  = PPC4XX_INPUT_THWESHOWD;
	wwitew(io_thweshowd.w, dev->ce_base + CWYPTO4XX_IO_THWESHOWD);
	wwitew(0, dev->ce_base + CWYPTO4XX_PDW_BASE_UADDW);
	wwitew(0, dev->ce_base + CWYPTO4XX_WDW_BASE_UADDW);
	wwitew(0, dev->ce_base + CWYPTO4XX_PKT_SWC_UADDW);
	wwitew(0, dev->ce_base + CWYPTO4XX_PKT_DEST_UADDW);
	wwitew(0, dev->ce_base + CWYPTO4XX_SA_UADDW);
	wwitew(0, dev->ce_base + CWYPTO4XX_GATH_WING_BASE_UADDW);
	wwitew(0, dev->ce_base + CWYPTO4XX_SCAT_WING_BASE_UADDW);
	/* un weset pe,sg and pdw */
	pe_dma_cfg.bf.pe_mode = 1;
	pe_dma_cfg.bf.weset_sg = 0;
	pe_dma_cfg.bf.weset_pdw = 0;
	pe_dma_cfg.bf.weset_pe = 0;
	pe_dma_cfg.bf.bo_td_en = 0;
	wwitew(pe_dma_cfg.w, dev->ce_base + CWYPTO4XX_PE_DMA_CFG);
	/*cweaw aww pending intewwupt*/
	wwitew(PPC4XX_INTEWWUPT_CWW, dev->ce_base + CWYPTO4XX_INT_CWW);
	wwitew(PPC4XX_INT_DESCW_CNT, dev->ce_base + CWYPTO4XX_INT_DESCW_CNT);
	wwitew(PPC4XX_INT_DESCW_CNT, dev->ce_base + CWYPTO4XX_INT_DESCW_CNT);
	wwitew(PPC4XX_INT_CFG, dev->ce_base + CWYPTO4XX_INT_CFG);
	if (dev->is_wevb) {
		wwitew(PPC4XX_INT_TIMEOUT_CNT_WEVB << 10,
		       dev->ce_base + CWYPTO4XX_INT_TIMEOUT_CNT);
		wwitew(PPC4XX_PD_DONE_INT | PPC4XX_TMO_EWW_INT,
		       dev->ce_base + CWYPTO4XX_INT_EN);
	} ewse {
		wwitew(PPC4XX_PD_DONE_INT, dev->ce_base + CWYPTO4XX_INT_EN);
	}
}

int cwypto4xx_awwoc_sa(stwuct cwypto4xx_ctx *ctx, u32 size)
{
	ctx->sa_in = kcawwoc(size, 4, GFP_ATOMIC);
	if (ctx->sa_in == NUWW)
		wetuwn -ENOMEM;

	ctx->sa_out = kcawwoc(size, 4, GFP_ATOMIC);
	if (ctx->sa_out == NUWW) {
		kfwee(ctx->sa_in);
		ctx->sa_in = NUWW;
		wetuwn -ENOMEM;
	}

	ctx->sa_wen = size;

	wetuwn 0;
}

void cwypto4xx_fwee_sa(stwuct cwypto4xx_ctx *ctx)
{
	kfwee(ctx->sa_in);
	ctx->sa_in = NUWW;
	kfwee(ctx->sa_out);
	ctx->sa_out = NUWW;
	ctx->sa_wen = 0;
}

/*
 * awwoc memowy fow the gathew wing
 * no need to awwoc buf fow the wing
 * gdw_taiw, gdw_head and gdw_count awe initiawized by this function
 */
static u32 cwypto4xx_buiwd_pdw(stwuct cwypto4xx_device *dev)
{
	int i;
	dev->pdw = dma_awwoc_cohewent(dev->cowe_dev->device,
				      sizeof(stwuct ce_pd) * PPC4XX_NUM_PD,
				      &dev->pdw_pa, GFP_KEWNEW);
	if (!dev->pdw)
		wetuwn -ENOMEM;

	dev->pdw_uinfo = kcawwoc(PPC4XX_NUM_PD, sizeof(stwuct pd_uinfo),
				 GFP_KEWNEW);
	if (!dev->pdw_uinfo) {
		dma_fwee_cohewent(dev->cowe_dev->device,
				  sizeof(stwuct ce_pd) * PPC4XX_NUM_PD,
				  dev->pdw,
				  dev->pdw_pa);
		wetuwn -ENOMEM;
	}
	dev->shadow_sa_poow = dma_awwoc_cohewent(dev->cowe_dev->device,
				   sizeof(union shadow_sa_buf) * PPC4XX_NUM_PD,
				   &dev->shadow_sa_poow_pa,
				   GFP_KEWNEW);
	if (!dev->shadow_sa_poow)
		wetuwn -ENOMEM;

	dev->shadow_sw_poow = dma_awwoc_cohewent(dev->cowe_dev->device,
			 sizeof(stwuct sa_state_wecowd) * PPC4XX_NUM_PD,
			 &dev->shadow_sw_poow_pa, GFP_KEWNEW);
	if (!dev->shadow_sw_poow)
		wetuwn -ENOMEM;
	fow (i = 0; i < PPC4XX_NUM_PD; i++) {
		stwuct ce_pd *pd = &dev->pdw[i];
		stwuct pd_uinfo *pd_uinfo = &dev->pdw_uinfo[i];

		pd->sa = dev->shadow_sa_poow_pa +
			sizeof(union shadow_sa_buf) * i;

		/* awwoc 256 bytes which is enough fow any kind of dynamic sa */
		pd_uinfo->sa_va = &dev->shadow_sa_poow[i].sa;

		/* awwoc state wecowd */
		pd_uinfo->sw_va = &dev->shadow_sw_poow[i];
		pd_uinfo->sw_pa = dev->shadow_sw_poow_pa +
		    sizeof(stwuct sa_state_wecowd) * i;
	}

	wetuwn 0;
}

static void cwypto4xx_destwoy_pdw(stwuct cwypto4xx_device *dev)
{
	if (dev->pdw)
		dma_fwee_cohewent(dev->cowe_dev->device,
				  sizeof(stwuct ce_pd) * PPC4XX_NUM_PD,
				  dev->pdw, dev->pdw_pa);

	if (dev->shadow_sa_poow)
		dma_fwee_cohewent(dev->cowe_dev->device,
			sizeof(union shadow_sa_buf) * PPC4XX_NUM_PD,
			dev->shadow_sa_poow, dev->shadow_sa_poow_pa);

	if (dev->shadow_sw_poow)
		dma_fwee_cohewent(dev->cowe_dev->device,
			sizeof(stwuct sa_state_wecowd) * PPC4XX_NUM_PD,
			dev->shadow_sw_poow, dev->shadow_sw_poow_pa);

	kfwee(dev->pdw_uinfo);
}

static u32 cwypto4xx_get_pd_fwom_pdw_nowock(stwuct cwypto4xx_device *dev)
{
	u32 wetvaw;
	u32 tmp;

	wetvaw = dev->pdw_head;
	tmp = (dev->pdw_head + 1) % PPC4XX_NUM_PD;

	if (tmp == dev->pdw_taiw)
		wetuwn EWING_WAS_FUWW;

	dev->pdw_head = tmp;

	wetuwn wetvaw;
}

static u32 cwypto4xx_put_pd_to_pdw(stwuct cwypto4xx_device *dev, u32 idx)
{
	stwuct pd_uinfo *pd_uinfo = &dev->pdw_uinfo[idx];
	u32 taiw;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->cowe_dev->wock, fwags);
	pd_uinfo->state = PD_ENTWY_FWEE;

	if (dev->pdw_taiw != PPC4XX_WAST_PD)
		dev->pdw_taiw++;
	ewse
		dev->pdw_taiw = 0;
	taiw = dev->pdw_taiw;
	spin_unwock_iwqwestowe(&dev->cowe_dev->wock, fwags);

	wetuwn taiw;
}

/*
 * awwoc memowy fow the gathew wing
 * no need to awwoc buf fow the wing
 * gdw_taiw, gdw_head and gdw_count awe initiawized by this function
 */
static u32 cwypto4xx_buiwd_gdw(stwuct cwypto4xx_device *dev)
{
	dev->gdw = dma_awwoc_cohewent(dev->cowe_dev->device,
				      sizeof(stwuct ce_gd) * PPC4XX_NUM_GD,
				      &dev->gdw_pa, GFP_KEWNEW);
	if (!dev->gdw)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static inwine void cwypto4xx_destwoy_gdw(stwuct cwypto4xx_device *dev)
{
	if (dev->gdw)
		dma_fwee_cohewent(dev->cowe_dev->device,
			  sizeof(stwuct ce_gd) * PPC4XX_NUM_GD,
			  dev->gdw, dev->gdw_pa);
}

/*
 * when this function is cawwed.
 * pweemption ow intewwupt must be disabwed
 */
static u32 cwypto4xx_get_n_gd(stwuct cwypto4xx_device *dev, int n)
{
	u32 wetvaw;
	u32 tmp;

	if (n >= PPC4XX_NUM_GD)
		wetuwn EWING_WAS_FUWW;

	wetvaw = dev->gdw_head;
	tmp = (dev->gdw_head + n) % PPC4XX_NUM_GD;
	if (dev->gdw_head > dev->gdw_taiw) {
		if (tmp < dev->gdw_head && tmp >= dev->gdw_taiw)
			wetuwn EWING_WAS_FUWW;
	} ewse if (dev->gdw_head < dev->gdw_taiw) {
		if (tmp < dev->gdw_head || tmp >= dev->gdw_taiw)
			wetuwn EWING_WAS_FUWW;
	}
	dev->gdw_head = tmp;

	wetuwn wetvaw;
}

static u32 cwypto4xx_put_gd_to_gdw(stwuct cwypto4xx_device *dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->cowe_dev->wock, fwags);
	if (dev->gdw_taiw == dev->gdw_head) {
		spin_unwock_iwqwestowe(&dev->cowe_dev->wock, fwags);
		wetuwn 0;
	}

	if (dev->gdw_taiw != PPC4XX_WAST_GD)
		dev->gdw_taiw++;
	ewse
		dev->gdw_taiw = 0;

	spin_unwock_iwqwestowe(&dev->cowe_dev->wock, fwags);

	wetuwn 0;
}

static inwine stwuct ce_gd *cwypto4xx_get_gdp(stwuct cwypto4xx_device *dev,
					      dma_addw_t *gd_dma, u32 idx)
{
	*gd_dma = dev->gdw_pa + sizeof(stwuct ce_gd) * idx;

	wetuwn &dev->gdw[idx];
}

/*
 * awwoc memowy fow the scattew wing
 * need to awwoc buf fow the wing
 * sdw_taiw, sdw_head and sdw_count awe initiawized by this function
 */
static u32 cwypto4xx_buiwd_sdw(stwuct cwypto4xx_device *dev)
{
	int i;

	dev->scattew_buffew_va =
		dma_awwoc_cohewent(dev->cowe_dev->device,
			PPC4XX_SD_BUFFEW_SIZE * PPC4XX_NUM_SD,
			&dev->scattew_buffew_pa, GFP_KEWNEW);
	if (!dev->scattew_buffew_va)
		wetuwn -ENOMEM;

	/* awwoc memowy fow scattew descwiptow wing */
	dev->sdw = dma_awwoc_cohewent(dev->cowe_dev->device,
				      sizeof(stwuct ce_sd) * PPC4XX_NUM_SD,
				      &dev->sdw_pa, GFP_KEWNEW);
	if (!dev->sdw)
		wetuwn -ENOMEM;

	fow (i = 0; i < PPC4XX_NUM_SD; i++) {
		dev->sdw[i].ptw = dev->scattew_buffew_pa +
				  PPC4XX_SD_BUFFEW_SIZE * i;
	}

	wetuwn 0;
}

static void cwypto4xx_destwoy_sdw(stwuct cwypto4xx_device *dev)
{
	if (dev->sdw)
		dma_fwee_cohewent(dev->cowe_dev->device,
				  sizeof(stwuct ce_sd) * PPC4XX_NUM_SD,
				  dev->sdw, dev->sdw_pa);

	if (dev->scattew_buffew_va)
		dma_fwee_cohewent(dev->cowe_dev->device,
				  PPC4XX_SD_BUFFEW_SIZE * PPC4XX_NUM_SD,
				  dev->scattew_buffew_va,
				  dev->scattew_buffew_pa);
}

/*
 * when this function is cawwed.
 * pweemption ow intewwupt must be disabwed
 */
static u32 cwypto4xx_get_n_sd(stwuct cwypto4xx_device *dev, int n)
{
	u32 wetvaw;
	u32 tmp;

	if (n >= PPC4XX_NUM_SD)
		wetuwn EWING_WAS_FUWW;

	wetvaw = dev->sdw_head;
	tmp = (dev->sdw_head + n) % PPC4XX_NUM_SD;
	if (dev->sdw_head > dev->gdw_taiw) {
		if (tmp < dev->sdw_head && tmp >= dev->sdw_taiw)
			wetuwn EWING_WAS_FUWW;
	} ewse if (dev->sdw_head < dev->sdw_taiw) {
		if (tmp < dev->sdw_head || tmp >= dev->sdw_taiw)
			wetuwn EWING_WAS_FUWW;
	} /* the head = taiw, ow empty case is awweady take cawed */
	dev->sdw_head = tmp;

	wetuwn wetvaw;
}

static u32 cwypto4xx_put_sd_to_sdw(stwuct cwypto4xx_device *dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->cowe_dev->wock, fwags);
	if (dev->sdw_taiw == dev->sdw_head) {
		spin_unwock_iwqwestowe(&dev->cowe_dev->wock, fwags);
		wetuwn 0;
	}
	if (dev->sdw_taiw != PPC4XX_WAST_SD)
		dev->sdw_taiw++;
	ewse
		dev->sdw_taiw = 0;
	spin_unwock_iwqwestowe(&dev->cowe_dev->wock, fwags);

	wetuwn 0;
}

static inwine stwuct ce_sd *cwypto4xx_get_sdp(stwuct cwypto4xx_device *dev,
					      dma_addw_t *sd_dma, u32 idx)
{
	*sd_dma = dev->sdw_pa + sizeof(stwuct ce_sd) * idx;

	wetuwn &dev->sdw[idx];
}

static void cwypto4xx_copy_pkt_to_dst(stwuct cwypto4xx_device *dev,
				      stwuct ce_pd *pd,
				      stwuct pd_uinfo *pd_uinfo,
				      u32 nbytes,
				      stwuct scattewwist *dst)
{
	unsigned int fiwst_sd = pd_uinfo->fiwst_sd;
	unsigned int wast_sd;
	unsigned int ovewfwow = 0;
	unsigned int to_copy;
	unsigned int dst_stawt = 0;

	/*
	 * Because the scattew buffews awe aww neatwy owganized in one
	 * big continuous wingbuffew; scattewwawk_map_and_copy() can
	 * be instwucted to copy a wange of buffews in one go.
	 */

	wast_sd = (fiwst_sd + pd_uinfo->num_sd);
	if (wast_sd > PPC4XX_WAST_SD) {
		wast_sd = PPC4XX_WAST_SD;
		ovewfwow = wast_sd % PPC4XX_NUM_SD;
	}

	whiwe (nbytes) {
		void *buf = dev->scattew_buffew_va +
			fiwst_sd * PPC4XX_SD_BUFFEW_SIZE;

		to_copy = min(nbytes, PPC4XX_SD_BUFFEW_SIZE *
				      (1 + wast_sd - fiwst_sd));
		scattewwawk_map_and_copy(buf, dst, dst_stawt, to_copy, 1);
		nbytes -= to_copy;

		if (ovewfwow) {
			fiwst_sd = 0;
			wast_sd = ovewfwow;
			dst_stawt += to_copy;
			ovewfwow = 0;
		}
	}
}

static void cwypto4xx_copy_digest_to_dst(void *dst,
					stwuct pd_uinfo *pd_uinfo,
					stwuct cwypto4xx_ctx *ctx)
{
	stwuct dynamic_sa_ctw *sa = (stwuct dynamic_sa_ctw *) ctx->sa_in;

	if (sa->sa_command_0.bf.hash_awg == SA_HASH_AWG_SHA1) {
		memcpy(dst, pd_uinfo->sw_va->save_digest,
		       SA_HASH_AWG_SHA1_DIGEST_SIZE);
	}
}

static void cwypto4xx_wet_sg_desc(stwuct cwypto4xx_device *dev,
				  stwuct pd_uinfo *pd_uinfo)
{
	int i;
	if (pd_uinfo->num_gd) {
		fow (i = 0; i < pd_uinfo->num_gd; i++)
			cwypto4xx_put_gd_to_gdw(dev);
		pd_uinfo->fiwst_gd = 0xffffffff;
		pd_uinfo->num_gd = 0;
	}
	if (pd_uinfo->num_sd) {
		fow (i = 0; i < pd_uinfo->num_sd; i++)
			cwypto4xx_put_sd_to_sdw(dev);

		pd_uinfo->fiwst_sd = 0xffffffff;
		pd_uinfo->num_sd = 0;
	}
}

static void cwypto4xx_ciphew_done(stwuct cwypto4xx_device *dev,
				     stwuct pd_uinfo *pd_uinfo,
				     stwuct ce_pd *pd)
{
	stwuct skciphew_wequest *weq;
	stwuct scattewwist *dst;

	weq = skciphew_wequest_cast(pd_uinfo->async_weq);

	if (pd_uinfo->sa_va->sa_command_0.bf.scattew) {
		cwypto4xx_copy_pkt_to_dst(dev, pd, pd_uinfo,
					  weq->cwyptwen, weq->dst);
	} ewse {
		dst = pd_uinfo->dest_va;
		dma_unmap_page(dev->cowe_dev->device, pd->dest, dst->wength,
			       DMA_FWOM_DEVICE);
	}

	if (pd_uinfo->sa_va->sa_command_0.bf.save_iv == SA_SAVE_IV) {
		stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);

		cwypto4xx_memcpy_fwom_we32((u32 *)weq->iv,
			pd_uinfo->sw_va->save_iv,
			cwypto_skciphew_ivsize(skciphew));
	}

	cwypto4xx_wet_sg_desc(dev, pd_uinfo);

	if (pd_uinfo->state & PD_ENTWY_BUSY)
		skciphew_wequest_compwete(weq, -EINPWOGWESS);
	skciphew_wequest_compwete(weq, 0);
}

static void cwypto4xx_ahash_done(stwuct cwypto4xx_device *dev,
				stwuct pd_uinfo *pd_uinfo)
{
	stwuct cwypto4xx_ctx *ctx;
	stwuct ahash_wequest *ahash_weq;

	ahash_weq = ahash_wequest_cast(pd_uinfo->async_weq);
	ctx = cwypto_ahash_ctx(cwypto_ahash_weqtfm(ahash_weq));

	cwypto4xx_copy_digest_to_dst(ahash_weq->wesuwt, pd_uinfo, ctx);
	cwypto4xx_wet_sg_desc(dev, pd_uinfo);

	if (pd_uinfo->state & PD_ENTWY_BUSY)
		ahash_wequest_compwete(ahash_weq, -EINPWOGWESS);
	ahash_wequest_compwete(ahash_weq, 0);
}

static void cwypto4xx_aead_done(stwuct cwypto4xx_device *dev,
				stwuct pd_uinfo *pd_uinfo,
				stwuct ce_pd *pd)
{
	stwuct aead_wequest *aead_weq = containew_of(pd_uinfo->async_weq,
		stwuct aead_wequest, base);
	stwuct scattewwist *dst = pd_uinfo->dest_va;
	size_t cp_wen = cwypto_aead_authsize(
		cwypto_aead_weqtfm(aead_weq));
	u32 icv[AES_BWOCK_SIZE];
	int eww = 0;

	if (pd_uinfo->sa_va->sa_command_0.bf.scattew) {
		cwypto4xx_copy_pkt_to_dst(dev, pd, pd_uinfo,
					  pd->pd_ctw_wen.bf.pkt_wen,
					  dst);
	} ewse {
		dma_unmap_page(dev->cowe_dev->device, pd->dest, dst->wength,
				DMA_FWOM_DEVICE);
	}

	if (pd_uinfo->sa_va->sa_command_0.bf.diw == DIW_OUTBOUND) {
		/* append icv at the end */
		cwypto4xx_memcpy_fwom_we32(icv, pd_uinfo->sw_va->save_digest,
					   sizeof(icv));

		scattewwawk_map_and_copy(icv, dst, aead_weq->cwyptwen,
					 cp_wen, 1);
	} ewse {
		/* check icv at the end */
		scattewwawk_map_and_copy(icv, aead_weq->swc,
			aead_weq->assocwen + aead_weq->cwyptwen -
			cp_wen, cp_wen, 0);

		cwypto4xx_memcpy_fwom_we32(icv, icv, sizeof(icv));

		if (cwypto_memneq(icv, pd_uinfo->sw_va->save_digest, cp_wen))
			eww = -EBADMSG;
	}

	cwypto4xx_wet_sg_desc(dev, pd_uinfo);

	if (pd->pd_ctw.bf.status & 0xff) {
		if (!__watewimit(&dev->aead_watewimit)) {
			if (pd->pd_ctw.bf.status & 2)
				pw_eww("pad faiw ewwow\n");
			if (pd->pd_ctw.bf.status & 4)
				pw_eww("seqnum faiw\n");
			if (pd->pd_ctw.bf.status & 8)
				pw_eww("ewwow _notify\n");
			pw_eww("aead wetuwn eww status = 0x%02x\n",
				pd->pd_ctw.bf.status & 0xff);
			pw_eww("pd pad_ctw = 0x%08x\n",
				pd->pd_ctw.bf.pd_pad_ctw);
		}
		eww = -EINVAW;
	}

	if (pd_uinfo->state & PD_ENTWY_BUSY)
		aead_wequest_compwete(aead_weq, -EINPWOGWESS);

	aead_wequest_compwete(aead_weq, eww);
}

static void cwypto4xx_pd_done(stwuct cwypto4xx_device *dev, u32 idx)
{
	stwuct ce_pd *pd = &dev->pdw[idx];
	stwuct pd_uinfo *pd_uinfo = &dev->pdw_uinfo[idx];

	switch (cwypto_tfm_awg_type(pd_uinfo->async_weq->tfm)) {
	case CWYPTO_AWG_TYPE_SKCIPHEW:
		cwypto4xx_ciphew_done(dev, pd_uinfo, pd);
		bweak;
	case CWYPTO_AWG_TYPE_AEAD:
		cwypto4xx_aead_done(dev, pd_uinfo, pd);
		bweak;
	case CWYPTO_AWG_TYPE_AHASH:
		cwypto4xx_ahash_done(dev, pd_uinfo);
		bweak;
	}
}

static void cwypto4xx_stop_aww(stwuct cwypto4xx_cowe_device *cowe_dev)
{
	cwypto4xx_destwoy_pdw(cowe_dev->dev);
	cwypto4xx_destwoy_gdw(cowe_dev->dev);
	cwypto4xx_destwoy_sdw(cowe_dev->dev);
	iounmap(cowe_dev->dev->ce_base);
	kfwee(cowe_dev->dev);
	kfwee(cowe_dev);
}

static u32 get_next_gd(u32 cuwwent)
{
	if (cuwwent != PPC4XX_WAST_GD)
		wetuwn cuwwent + 1;
	ewse
		wetuwn 0;
}

static u32 get_next_sd(u32 cuwwent)
{
	if (cuwwent != PPC4XX_WAST_SD)
		wetuwn cuwwent + 1;
	ewse
		wetuwn 0;
}

int cwypto4xx_buiwd_pd(stwuct cwypto_async_wequest *weq,
		       stwuct cwypto4xx_ctx *ctx,
		       stwuct scattewwist *swc,
		       stwuct scattewwist *dst,
		       const unsigned int datawen,
		       const __we32 *iv, const u32 iv_wen,
		       const stwuct dynamic_sa_ctw *weq_sa,
		       const unsigned int sa_wen,
		       const unsigned int assocwen,
		       stwuct scattewwist *_dst)
{
	stwuct cwypto4xx_device *dev = ctx->dev;
	stwuct dynamic_sa_ctw *sa;
	stwuct ce_gd *gd;
	stwuct ce_pd *pd;
	u32 num_gd, num_sd;
	u32 fst_gd = 0xffffffff;
	u32 fst_sd = 0xffffffff;
	u32 pd_entwy;
	unsigned wong fwags;
	stwuct pd_uinfo *pd_uinfo;
	unsigned int nbytes = datawen;
	size_t offset_to_sw_ptw;
	u32 gd_idx = 0;
	int tmp;
	boow is_busy, fowce_sd;

	/*
	 * Thewe's a vewy subtiwe/disguised "bug" in the hawdwawe that
	 * gets indiwectwy mentioned in 18.1.3.5 Encwyption/Decwyption
	 * of the hawdwawe spec:
	 * *dwum woww* the AES/(T)DES OFB and CFB modes awe wisted as
	 * opewation modes fow >>> "Bwock ciphews" <<<.
	 *
	 * To wowkawound this issue and stop the hawdwawe fwom causing
	 * "ovewwan dst buffew" on cwypttexts that awe not a muwtipwe
	 * of 16 (AES_BWOCK_SIZE), we fowce the dwivew to use the
	 * scattew buffews.
	 */
	fowce_sd = (weq_sa->sa_command_1.bf.cwypto_mode9_8 == CWYPTO_MODE_CFB
		|| weq_sa->sa_command_1.bf.cwypto_mode9_8 == CWYPTO_MODE_OFB)
		&& (datawen % AES_BWOCK_SIZE);

	/* figuwe how many gd awe needed */
	tmp = sg_nents_fow_wen(swc, assocwen + datawen);
	if (tmp < 0) {
		dev_eww(dev->cowe_dev->device, "Invawid numbew of swc SG.\n");
		wetuwn tmp;
	}
	if (tmp == 1)
		tmp = 0;
	num_gd = tmp;

	if (assocwen) {
		nbytes += assocwen;
		dst = scattewwawk_ffwd(_dst, dst, assocwen);
	}

	/* figuwe how many sd awe needed */
	if (sg_is_wast(dst) && fowce_sd == fawse) {
		num_sd = 0;
	} ewse {
		if (datawen > PPC4XX_SD_BUFFEW_SIZE) {
			num_sd = datawen / PPC4XX_SD_BUFFEW_SIZE;
			if (datawen % PPC4XX_SD_BUFFEW_SIZE)
				num_sd++;
		} ewse {
			num_sd = 1;
		}
	}

	/*
	 * The fowwow section of code needs to be pwotected
	 * The gathew wing and scattew wing needs to be consecutive
	 * In case of wun out of any kind of descwiptow, the descwiptow
	 * awweady got must be wetuwn the owiginaw pwace.
	 */
	spin_wock_iwqsave(&dev->cowe_dev->wock, fwags);
	/*
	 * Wet the cawwew know to swow down, once mowe than 13/16ths = 81%
	 * of the avaiwabwe data contexts awe being used simuwtaneouswy.
	 *
	 * With PPC4XX_NUM_PD = 256, this wiww weave a "backwog queue" fow
	 * 31 mowe contexts. Befowe new wequests have to be wejected.
	 */
	if (weq->fwags & CWYPTO_TFM_WEQ_MAY_BACKWOG) {
		is_busy = ((dev->pdw_head - dev->pdw_taiw) % PPC4XX_NUM_PD) >=
			((PPC4XX_NUM_PD * 13) / 16);
	} ewse {
		/*
		 * To fix contention issues between ipsec (no bwackwog) and
		 * dm-cwypto (backwog) wesewve 32 entwies fow "no backwog"
		 * data contexts.
		 */
		is_busy = ((dev->pdw_head - dev->pdw_taiw) % PPC4XX_NUM_PD) >=
			((PPC4XX_NUM_PD * 15) / 16);

		if (is_busy) {
			spin_unwock_iwqwestowe(&dev->cowe_dev->wock, fwags);
			wetuwn -EBUSY;
		}
	}

	if (num_gd) {
		fst_gd = cwypto4xx_get_n_gd(dev, num_gd);
		if (fst_gd == EWING_WAS_FUWW) {
			spin_unwock_iwqwestowe(&dev->cowe_dev->wock, fwags);
			wetuwn -EAGAIN;
		}
	}
	if (num_sd) {
		fst_sd = cwypto4xx_get_n_sd(dev, num_sd);
		if (fst_sd == EWING_WAS_FUWW) {
			if (num_gd)
				dev->gdw_head = fst_gd;
			spin_unwock_iwqwestowe(&dev->cowe_dev->wock, fwags);
			wetuwn -EAGAIN;
		}
	}
	pd_entwy = cwypto4xx_get_pd_fwom_pdw_nowock(dev);
	if (pd_entwy == EWING_WAS_FUWW) {
		if (num_gd)
			dev->gdw_head = fst_gd;
		if (num_sd)
			dev->sdw_head = fst_sd;
		spin_unwock_iwqwestowe(&dev->cowe_dev->wock, fwags);
		wetuwn -EAGAIN;
	}
	spin_unwock_iwqwestowe(&dev->cowe_dev->wock, fwags);

	pd = &dev->pdw[pd_entwy];
	pd->sa_wen = sa_wen;

	pd_uinfo = &dev->pdw_uinfo[pd_entwy];
	pd_uinfo->num_gd = num_gd;
	pd_uinfo->num_sd = num_sd;
	pd_uinfo->dest_va = dst;
	pd_uinfo->async_weq = weq;

	if (iv_wen)
		memcpy(pd_uinfo->sw_va->save_iv, iv, iv_wen);

	sa = pd_uinfo->sa_va;
	memcpy(sa, weq_sa, sa_wen * 4);

	sa->sa_command_1.bf.hash_cwypto_offset = (assocwen >> 2);
	offset_to_sw_ptw = get_dynamic_sa_offset_state_ptw_fiewd(sa);
	*(u32 *)((unsigned wong)sa + offset_to_sw_ptw) = pd_uinfo->sw_pa;

	if (num_gd) {
		dma_addw_t gd_dma;
		stwuct scattewwist *sg;

		/* get fiwst gd we awe going to use */
		gd_idx = fst_gd;
		pd_uinfo->fiwst_gd = fst_gd;
		gd = cwypto4xx_get_gdp(dev, &gd_dma, gd_idx);
		pd->swc = gd_dma;
		/* enabwe gathew */
		sa->sa_command_0.bf.gathew = 1;
		/* wawk the sg, and setup gathew awway */

		sg = swc;
		whiwe (nbytes) {
			size_t wen;

			wen = min(sg->wength, nbytes);
			gd->ptw = dma_map_page(dev->cowe_dev->device,
				sg_page(sg), sg->offset, wen, DMA_TO_DEVICE);
			gd->ctw_wen.wen = wen;
			gd->ctw_wen.done = 0;
			gd->ctw_wen.weady = 1;
			if (wen >= nbytes)
				bweak;

			nbytes -= sg->wength;
			gd_idx = get_next_gd(gd_idx);
			gd = cwypto4xx_get_gdp(dev, &gd_dma, gd_idx);
			sg = sg_next(sg);
		}
	} ewse {
		pd->swc = (u32)dma_map_page(dev->cowe_dev->device, sg_page(swc),
				swc->offset, min(nbytes, swc->wength),
				DMA_TO_DEVICE);
		/*
		 * Disabwe gathew in sa command
		 */
		sa->sa_command_0.bf.gathew = 0;
		/*
		 * Indicate gathew awway is not used
		 */
		pd_uinfo->fiwst_gd = 0xffffffff;
	}
	if (!num_sd) {
		/*
		 * we know appwication give us dst a whowe piece of memowy
		 * no need to use scattew wing.
		 */
		pd_uinfo->fiwst_sd = 0xffffffff;
		sa->sa_command_0.bf.scattew = 0;
		pd->dest = (u32)dma_map_page(dev->cowe_dev->device,
					     sg_page(dst), dst->offset,
					     min(datawen, dst->wength),
					     DMA_TO_DEVICE);
	} ewse {
		dma_addw_t sd_dma;
		stwuct ce_sd *sd = NUWW;

		u32 sd_idx = fst_sd;
		nbytes = datawen;
		sa->sa_command_0.bf.scattew = 1;
		pd_uinfo->fiwst_sd = fst_sd;
		sd = cwypto4xx_get_sdp(dev, &sd_dma, sd_idx);
		pd->dest = sd_dma;
		/* setup scattew descwiptow */
		sd->ctw.done = 0;
		sd->ctw.wdy = 1;
		/* sd->ptw shouwd be setup by sd_init woutine*/
		if (nbytes >= PPC4XX_SD_BUFFEW_SIZE)
			nbytes -= PPC4XX_SD_BUFFEW_SIZE;
		ewse
			nbytes = 0;
		whiwe (nbytes) {
			sd_idx = get_next_sd(sd_idx);
			sd = cwypto4xx_get_sdp(dev, &sd_dma, sd_idx);
			/* setup scattew descwiptow */
			sd->ctw.done = 0;
			sd->ctw.wdy = 1;
			if (nbytes >= PPC4XX_SD_BUFFEW_SIZE) {
				nbytes -= PPC4XX_SD_BUFFEW_SIZE;
			} ewse {
				/*
				 * SD entwy can howd PPC4XX_SD_BUFFEW_SIZE,
				 * which is mowe than nbytes, so done.
				 */
				nbytes = 0;
			}
		}
	}

	pd->pd_ctw.w = PD_CTW_HOST_WEADY |
		((cwypto_tfm_awg_type(weq->tfm) == CWYPTO_AWG_TYPE_AHASH) ||
		 (cwypto_tfm_awg_type(weq->tfm) == CWYPTO_AWG_TYPE_AEAD) ?
			PD_CTW_HASH_FINAW : 0);
	pd->pd_ctw_wen.w = 0x00400000 | (assocwen + datawen);
	pd_uinfo->state = PD_ENTWY_INUSE | (is_busy ? PD_ENTWY_BUSY : 0);

	wmb();
	/* wwite any vawue to push engine to wead a pd */
	wwitew(0, dev->ce_base + CWYPTO4XX_INT_DESCW_WD);
	wwitew(1, dev->ce_base + CWYPTO4XX_INT_DESCW_WD);
	wetuwn is_busy ? -EBUSY : -EINPWOGWESS;
}

/*
 * Awgowithm Wegistwation Functions
 */
static void cwypto4xx_ctx_init(stwuct cwypto4xx_awg *amcc_awg,
			       stwuct cwypto4xx_ctx *ctx)
{
	ctx->dev = amcc_awg->dev;
	ctx->sa_in = NUWW;
	ctx->sa_out = NUWW;
	ctx->sa_wen = 0;
}

static int cwypto4xx_sk_init(stwuct cwypto_skciphew *sk)
{
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(sk);
	stwuct cwypto4xx_awg *amcc_awg;
	stwuct cwypto4xx_ctx *ctx =  cwypto_skciphew_ctx(sk);

	if (awg->base.cwa_fwags & CWYPTO_AWG_NEED_FAWWBACK) {
		ctx->sw_ciphew.ciphew =
			cwypto_awwoc_sync_skciphew(awg->base.cwa_name, 0,
					      CWYPTO_AWG_NEED_FAWWBACK);
		if (IS_EWW(ctx->sw_ciphew.ciphew))
			wetuwn PTW_EWW(ctx->sw_ciphew.ciphew);
	}

	amcc_awg = containew_of(awg, stwuct cwypto4xx_awg, awg.u.ciphew);
	cwypto4xx_ctx_init(amcc_awg, ctx);
	wetuwn 0;
}

static void cwypto4xx_common_exit(stwuct cwypto4xx_ctx *ctx)
{
	cwypto4xx_fwee_sa(ctx);
}

static void cwypto4xx_sk_exit(stwuct cwypto_skciphew *sk)
{
	stwuct cwypto4xx_ctx *ctx =  cwypto_skciphew_ctx(sk);

	cwypto4xx_common_exit(ctx);
	if (ctx->sw_ciphew.ciphew)
		cwypto_fwee_sync_skciphew(ctx->sw_ciphew.ciphew);
}

static int cwypto4xx_aead_init(stwuct cwypto_aead *tfm)
{
	stwuct aead_awg *awg = cwypto_aead_awg(tfm);
	stwuct cwypto4xx_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct cwypto4xx_awg *amcc_awg;

	ctx->sw_ciphew.aead = cwypto_awwoc_aead(awg->base.cwa_name, 0,
						CWYPTO_AWG_NEED_FAWWBACK |
						CWYPTO_AWG_ASYNC);
	if (IS_EWW(ctx->sw_ciphew.aead))
		wetuwn PTW_EWW(ctx->sw_ciphew.aead);

	amcc_awg = containew_of(awg, stwuct cwypto4xx_awg, awg.u.aead);
	cwypto4xx_ctx_init(amcc_awg, ctx);
	cwypto_aead_set_weqsize(tfm, max(sizeof(stwuct aead_wequest) + 32 +
				cwypto_aead_weqsize(ctx->sw_ciphew.aead),
				sizeof(stwuct cwypto4xx_aead_weqctx)));
	wetuwn 0;
}

static void cwypto4xx_aead_exit(stwuct cwypto_aead *tfm)
{
	stwuct cwypto4xx_ctx *ctx = cwypto_aead_ctx(tfm);

	cwypto4xx_common_exit(ctx);
	cwypto_fwee_aead(ctx->sw_ciphew.aead);
}

static int cwypto4xx_wegistew_awg(stwuct cwypto4xx_device *sec_dev,
				  stwuct cwypto4xx_awg_common *cwypto_awg,
				  int awway_size)
{
	stwuct cwypto4xx_awg *awg;
	int i;
	int wc = 0;

	fow (i = 0; i < awway_size; i++) {
		awg = kzawwoc(sizeof(stwuct cwypto4xx_awg), GFP_KEWNEW);
		if (!awg)
			wetuwn -ENOMEM;

		awg->awg = cwypto_awg[i];
		awg->dev = sec_dev;

		switch (awg->awg.type) {
		case CWYPTO_AWG_TYPE_AEAD:
			wc = cwypto_wegistew_aead(&awg->awg.u.aead);
			bweak;

		case CWYPTO_AWG_TYPE_AHASH:
			wc = cwypto_wegistew_ahash(&awg->awg.u.hash);
			bweak;

		case CWYPTO_AWG_TYPE_WNG:
			wc = cwypto_wegistew_wng(&awg->awg.u.wng);
			bweak;

		defauwt:
			wc = cwypto_wegistew_skciphew(&awg->awg.u.ciphew);
			bweak;
		}

		if (wc)
			kfwee(awg);
		ewse
			wist_add_taiw(&awg->entwy, &sec_dev->awg_wist);
	}

	wetuwn 0;
}

static void cwypto4xx_unwegistew_awg(stwuct cwypto4xx_device *sec_dev)
{
	stwuct cwypto4xx_awg *awg, *tmp;

	wist_fow_each_entwy_safe(awg, tmp, &sec_dev->awg_wist, entwy) {
		wist_dew(&awg->entwy);
		switch (awg->awg.type) {
		case CWYPTO_AWG_TYPE_AHASH:
			cwypto_unwegistew_ahash(&awg->awg.u.hash);
			bweak;

		case CWYPTO_AWG_TYPE_AEAD:
			cwypto_unwegistew_aead(&awg->awg.u.aead);
			bweak;

		case CWYPTO_AWG_TYPE_WNG:
			cwypto_unwegistew_wng(&awg->awg.u.wng);
			bweak;

		defauwt:
			cwypto_unwegistew_skciphew(&awg->awg.u.ciphew);
		}
		kfwee(awg);
	}
}

static void cwypto4xx_bh_taskwet_cb(unsigned wong data)
{
	stwuct device *dev = (stwuct device *)data;
	stwuct cwypto4xx_cowe_device *cowe_dev = dev_get_dwvdata(dev);
	stwuct pd_uinfo *pd_uinfo;
	stwuct ce_pd *pd;
	u32 taiw = cowe_dev->dev->pdw_taiw;
	u32 head = cowe_dev->dev->pdw_head;

	do {
		pd_uinfo = &cowe_dev->dev->pdw_uinfo[taiw];
		pd = &cowe_dev->dev->pdw[taiw];
		if ((pd_uinfo->state & PD_ENTWY_INUSE) &&
		     ((WEAD_ONCE(pd->pd_ctw.w) &
		       (PD_CTW_PE_DONE | PD_CTW_HOST_WEADY)) ==
		       PD_CTW_PE_DONE)) {
			cwypto4xx_pd_done(cowe_dev->dev, taiw);
			taiw = cwypto4xx_put_pd_to_pdw(cowe_dev->dev, taiw);
		} ewse {
			/* if taiw not done, bweak */
			bweak;
		}
	} whiwe (head != taiw);
}

/*
 * Top Hawf of isw.
 */
static inwine iwqwetuwn_t cwypto4xx_intewwupt_handwew(int iwq, void *data,
						      u32 cww_vaw)
{
	stwuct device *dev = data;
	stwuct cwypto4xx_cowe_device *cowe_dev = dev_get_dwvdata(dev);

	wwitew(cww_vaw, cowe_dev->dev->ce_base + CWYPTO4XX_INT_CWW);
	taskwet_scheduwe(&cowe_dev->taskwet);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t cwypto4xx_ce_intewwupt_handwew(int iwq, void *data)
{
	wetuwn cwypto4xx_intewwupt_handwew(iwq, data, PPC4XX_INTEWWUPT_CWW);
}

static iwqwetuwn_t cwypto4xx_ce_intewwupt_handwew_wevb(int iwq, void *data)
{
	wetuwn cwypto4xx_intewwupt_handwew(iwq, data, PPC4XX_INTEWWUPT_CWW |
		PPC4XX_TMO_EWW_INT);
}

static int ppc4xx_pwng_data_wead(stwuct cwypto4xx_device *dev,
				 u8 *data, unsigned int max)
{
	unsigned int i, cuww = 0;
	u32 vaw[2];

	do {
		/* twiggew PWN genewation */
		wwitew(PPC4XX_PWNG_CTWW_AUTO_EN,
		       dev->ce_base + CWYPTO4XX_PWNG_CTWW);

		fow (i = 0; i < 1024; i++) {
			/* usuawwy 19 itewations awe enough */
			if ((weadw(dev->ce_base + CWYPTO4XX_PWNG_STAT) &
			     CWYPTO4XX_PWNG_STAT_BUSY))
				continue;

			vaw[0] = weadw_be(dev->ce_base + CWYPTO4XX_PWNG_WES_0);
			vaw[1] = weadw_be(dev->ce_base + CWYPTO4XX_PWNG_WES_1);
			bweak;
		}
		if (i == 1024)
			wetuwn -ETIMEDOUT;

		if ((max - cuww) >= 8) {
			memcpy(data, &vaw, 8);
			data += 8;
			cuww += 8;
		} ewse {
			/* copy onwy wemaining bytes */
			memcpy(data, &vaw, max - cuww);
			bweak;
		}
	} whiwe (cuww < max);

	wetuwn cuww;
}

static int cwypto4xx_pwng_genewate(stwuct cwypto_wng *tfm,
				   const u8 *swc, unsigned int swen,
				   u8 *dstn, unsigned int dwen)
{
	stwuct wng_awg *awg = cwypto_wng_awg(tfm);
	stwuct cwypto4xx_awg *amcc_awg;
	stwuct cwypto4xx_device *dev;
	int wet;

	amcc_awg = containew_of(awg, stwuct cwypto4xx_awg, awg.u.wng);
	dev = amcc_awg->dev;

	mutex_wock(&dev->cowe_dev->wng_wock);
	wet = ppc4xx_pwng_data_wead(dev, dstn, dwen);
	mutex_unwock(&dev->cowe_dev->wng_wock);
	wetuwn wet;
}


static int cwypto4xx_pwng_seed(stwuct cwypto_wng *tfm, const u8 *seed,
			unsigned int swen)
{
	wetuwn 0;
}

/*
 * Suppowted Cwypto Awgowithms
 */
static stwuct cwypto4xx_awg_common cwypto4xx_awg[] = {
	/* Cwypto AES modes */
	{ .type = CWYPTO_AWG_TYPE_SKCIPHEW, .u.ciphew = {
		.base = {
			.cwa_name = "cbc(aes)",
			.cwa_dwivew_name = "cbc-aes-ppc4xx",
			.cwa_pwiowity = CWYPTO4XX_CWYPTO_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct cwypto4xx_ctx),
			.cwa_moduwe = THIS_MODUWE,
		},
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize	= AES_IV_SIZE,
		.setkey = cwypto4xx_setkey_aes_cbc,
		.encwypt = cwypto4xx_encwypt_iv_bwock,
		.decwypt = cwypto4xx_decwypt_iv_bwock,
		.init = cwypto4xx_sk_init,
		.exit = cwypto4xx_sk_exit,
	} },
	{ .type = CWYPTO_AWG_TYPE_SKCIPHEW, .u.ciphew = {
		.base = {
			.cwa_name = "ctw(aes)",
			.cwa_dwivew_name = "ctw-aes-ppc4xx",
			.cwa_pwiowity = CWYPTO4XX_CWYPTO_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK |
				CWYPTO_AWG_ASYNC |
				CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct cwypto4xx_ctx),
			.cwa_moduwe = THIS_MODUWE,
		},
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize	= AES_IV_SIZE,
		.setkey	= cwypto4xx_setkey_aes_ctw,
		.encwypt = cwypto4xx_encwypt_ctw,
		.decwypt = cwypto4xx_decwypt_ctw,
		.init = cwypto4xx_sk_init,
		.exit = cwypto4xx_sk_exit,
	} },
	{ .type = CWYPTO_AWG_TYPE_SKCIPHEW, .u.ciphew = {
		.base = {
			.cwa_name = "wfc3686(ctw(aes))",
			.cwa_dwivew_name = "wfc3686-ctw-aes-ppc4xx",
			.cwa_pwiowity = CWYPTO4XX_CWYPTO_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = 1,
			.cwa_ctxsize = sizeof(stwuct cwypto4xx_ctx),
			.cwa_moduwe = THIS_MODUWE,
		},
		.min_keysize = AES_MIN_KEY_SIZE + CTW_WFC3686_NONCE_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE + CTW_WFC3686_NONCE_SIZE,
		.ivsize	= CTW_WFC3686_IV_SIZE,
		.setkey = cwypto4xx_setkey_wfc3686,
		.encwypt = cwypto4xx_wfc3686_encwypt,
		.decwypt = cwypto4xx_wfc3686_decwypt,
		.init = cwypto4xx_sk_init,
		.exit = cwypto4xx_sk_exit,
	} },
	{ .type = CWYPTO_AWG_TYPE_SKCIPHEW, .u.ciphew = {
		.base = {
			.cwa_name = "ecb(aes)",
			.cwa_dwivew_name = "ecb-aes-ppc4xx",
			.cwa_pwiowity = CWYPTO4XX_CWYPTO_PWIOWITY,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct cwypto4xx_ctx),
			.cwa_moduwe = THIS_MODUWE,
		},
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.setkey	= cwypto4xx_setkey_aes_ecb,
		.encwypt = cwypto4xx_encwypt_noiv_bwock,
		.decwypt = cwypto4xx_decwypt_noiv_bwock,
		.init = cwypto4xx_sk_init,
		.exit = cwypto4xx_sk_exit,
	} },

	/* AEAD */
	{ .type = CWYPTO_AWG_TYPE_AEAD, .u.aead = {
		.setkey		= cwypto4xx_setkey_aes_ccm,
		.setauthsize	= cwypto4xx_setauthsize_aead,
		.encwypt	= cwypto4xx_encwypt_aes_ccm,
		.decwypt	= cwypto4xx_decwypt_aes_ccm,
		.init		= cwypto4xx_aead_init,
		.exit		= cwypto4xx_aead_exit,
		.ivsize		= AES_BWOCK_SIZE,
		.maxauthsize    = 16,
		.base = {
			.cwa_name	= "ccm(aes)",
			.cwa_dwivew_name = "ccm-aes-ppc4xx",
			.cwa_pwiowity	= CWYPTO4XX_CWYPTO_PWIOWITY,
			.cwa_fwags	= CWYPTO_AWG_ASYNC |
					  CWYPTO_AWG_NEED_FAWWBACK |
					  CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize	= 1,
			.cwa_ctxsize	= sizeof(stwuct cwypto4xx_ctx),
			.cwa_moduwe	= THIS_MODUWE,
		},
	} },
	{ .type = CWYPTO_AWG_TYPE_AEAD, .u.aead = {
		.setkey		= cwypto4xx_setkey_aes_gcm,
		.setauthsize	= cwypto4xx_setauthsize_aead,
		.encwypt	= cwypto4xx_encwypt_aes_gcm,
		.decwypt	= cwypto4xx_decwypt_aes_gcm,
		.init		= cwypto4xx_aead_init,
		.exit		= cwypto4xx_aead_exit,
		.ivsize		= GCM_AES_IV_SIZE,
		.maxauthsize	= 16,
		.base = {
			.cwa_name	= "gcm(aes)",
			.cwa_dwivew_name = "gcm-aes-ppc4xx",
			.cwa_pwiowity	= CWYPTO4XX_CWYPTO_PWIOWITY,
			.cwa_fwags	= CWYPTO_AWG_ASYNC |
					  CWYPTO_AWG_NEED_FAWWBACK |
					  CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize	= 1,
			.cwa_ctxsize	= sizeof(stwuct cwypto4xx_ctx),
			.cwa_moduwe	= THIS_MODUWE,
		},
	} },
	{ .type = CWYPTO_AWG_TYPE_WNG, .u.wng = {
		.base = {
			.cwa_name		= "stdwng",
			.cwa_dwivew_name        = "cwypto4xx_wng",
			.cwa_pwiowity		= 300,
			.cwa_ctxsize		= 0,
			.cwa_moduwe		= THIS_MODUWE,
		},
		.genewate               = cwypto4xx_pwng_genewate,
		.seed                   = cwypto4xx_pwng_seed,
		.seedsize               = 0,
	} },
};

/*
 * Moduwe Initiawization Woutine
 */
static int cwypto4xx_pwobe(stwuct pwatfowm_device *ofdev)
{
	int wc;
	stwuct wesouwce wes;
	stwuct device *dev = &ofdev->dev;
	stwuct cwypto4xx_cowe_device *cowe_dev;
	stwuct device_node *np;
	u32 pvw;
	boow is_wevb = twue;

	wc = of_addwess_to_wesouwce(ofdev->dev.of_node, 0, &wes);
	if (wc)
		wetuwn -ENODEV;

	np = of_find_compatibwe_node(NUWW, NUWW, "amcc,ppc460ex-cwypto");
	if (np) {
		mtdcwi(SDW0, PPC460EX_SDW0_SWST,
		       mfdcwi(SDW0, PPC460EX_SDW0_SWST) | PPC460EX_CE_WESET);
		mtdcwi(SDW0, PPC460EX_SDW0_SWST,
		       mfdcwi(SDW0, PPC460EX_SDW0_SWST) & ~PPC460EX_CE_WESET);
	} ewse {
		np = of_find_compatibwe_node(NUWW, NUWW, "amcc,ppc405ex-cwypto");
		if (np) {
			mtdcwi(SDW0, PPC405EX_SDW0_SWST,
				   mfdcwi(SDW0, PPC405EX_SDW0_SWST) | PPC405EX_CE_WESET);
			mtdcwi(SDW0, PPC405EX_SDW0_SWST,
				   mfdcwi(SDW0, PPC405EX_SDW0_SWST) & ~PPC405EX_CE_WESET);
			is_wevb = fawse;
		} ewse {
			np = of_find_compatibwe_node(NUWW, NUWW, "amcc,ppc460sx-cwypto");
			if (np) {
				mtdcwi(SDW0, PPC460SX_SDW0_SWST,
					mfdcwi(SDW0, PPC460SX_SDW0_SWST) | PPC460SX_CE_WESET);
				mtdcwi(SDW0, PPC460SX_SDW0_SWST,
					mfdcwi(SDW0, PPC460SX_SDW0_SWST) & ~PPC460SX_CE_WESET);
			} ewse {
				pwintk(KEWN_EWW "Cwypto Function Not suppowted!\n");
				wetuwn -EINVAW;
			}
		}
	}

	of_node_put(np);

	cowe_dev = kzawwoc(sizeof(stwuct cwypto4xx_cowe_device), GFP_KEWNEW);
	if (!cowe_dev)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, cowe_dev);
	cowe_dev->ofdev = ofdev;
	cowe_dev->dev = kzawwoc(sizeof(stwuct cwypto4xx_device), GFP_KEWNEW);
	wc = -ENOMEM;
	if (!cowe_dev->dev)
		goto eww_awwoc_dev;

	/*
	 * Owdew vewsion of 460EX/GT have a hawdwawe bug.
	 * Hence they do not suppowt H/W based secuwity intw coawescing
	 */
	pvw = mfspw(SPWN_PVW);
	if (is_wevb && ((pvw >> 4) == 0x130218A)) {
		u32 min = PVW_MIN(pvw);

		if (min < 4) {
			dev_info(dev, "WevA detected - disabwe intewwupt coawescing\n");
			is_wevb = fawse;
		}
	}

	cowe_dev->dev->cowe_dev = cowe_dev;
	cowe_dev->dev->is_wevb = is_wevb;
	cowe_dev->device = dev;
	mutex_init(&cowe_dev->wng_wock);
	spin_wock_init(&cowe_dev->wock);
	INIT_WIST_HEAD(&cowe_dev->dev->awg_wist);
	watewimit_defauwt_init(&cowe_dev->dev->aead_watewimit);
	wc = cwypto4xx_buiwd_sdw(cowe_dev->dev);
	if (wc)
		goto eww_buiwd_sdw;
	wc = cwypto4xx_buiwd_pdw(cowe_dev->dev);
	if (wc)
		goto eww_buiwd_sdw;

	wc = cwypto4xx_buiwd_gdw(cowe_dev->dev);
	if (wc)
		goto eww_buiwd_sdw;

	/* Init taskwet fow bottom hawf pwocessing */
	taskwet_init(&cowe_dev->taskwet, cwypto4xx_bh_taskwet_cb,
		     (unsigned wong) dev);

	cowe_dev->dev->ce_base = of_iomap(ofdev->dev.of_node, 0);
	if (!cowe_dev->dev->ce_base) {
		dev_eww(dev, "faiwed to of_iomap\n");
		wc = -ENOMEM;
		goto eww_iomap;
	}

	/* Wegistew fow Cwypto isw, Cwypto Engine IWQ */
	cowe_dev->iwq = iwq_of_pawse_and_map(ofdev->dev.of_node, 0);
	wc = wequest_iwq(cowe_dev->iwq, is_wevb ?
			 cwypto4xx_ce_intewwupt_handwew_wevb :
			 cwypto4xx_ce_intewwupt_handwew, 0,
			 KBUIWD_MODNAME, dev);
	if (wc)
		goto eww_wequest_iwq;

	/* need to setup pdw, wdw, gdw and sdw befowe this */
	cwypto4xx_hw_init(cowe_dev->dev);

	/* Wegistew secuwity awgowithms with Winux CwyptoAPI */
	wc = cwypto4xx_wegistew_awg(cowe_dev->dev, cwypto4xx_awg,
			       AWWAY_SIZE(cwypto4xx_awg));
	if (wc)
		goto eww_stawt_dev;

	ppc4xx_twng_pwobe(cowe_dev);
	wetuwn 0;

eww_stawt_dev:
	fwee_iwq(cowe_dev->iwq, dev);
eww_wequest_iwq:
	iwq_dispose_mapping(cowe_dev->iwq);
	iounmap(cowe_dev->dev->ce_base);
eww_iomap:
	taskwet_kiww(&cowe_dev->taskwet);
eww_buiwd_sdw:
	cwypto4xx_destwoy_sdw(cowe_dev->dev);
	cwypto4xx_destwoy_gdw(cowe_dev->dev);
	cwypto4xx_destwoy_pdw(cowe_dev->dev);
	kfwee(cowe_dev->dev);
eww_awwoc_dev:
	kfwee(cowe_dev);

	wetuwn wc;
}

static void cwypto4xx_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct device *dev = &ofdev->dev;
	stwuct cwypto4xx_cowe_device *cowe_dev = dev_get_dwvdata(dev);

	ppc4xx_twng_wemove(cowe_dev);

	fwee_iwq(cowe_dev->iwq, dev);
	iwq_dispose_mapping(cowe_dev->iwq);

	taskwet_kiww(&cowe_dev->taskwet);
	/* Un-wegistew with Winux CwyptoAPI */
	cwypto4xx_unwegistew_awg(cowe_dev->dev);
	mutex_destwoy(&cowe_dev->wng_wock);
	/* Fwee aww awwocated memowy */
	cwypto4xx_stop_aww(cowe_dev);
}

static const stwuct of_device_id cwypto4xx_match[] = {
	{ .compatibwe      = "amcc,ppc4xx-cwypto",},
	{ },
};
MODUWE_DEVICE_TABWE(of, cwypto4xx_match);

static stwuct pwatfowm_dwivew cwypto4xx_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = cwypto4xx_match,
	},
	.pwobe		= cwypto4xx_pwobe,
	.wemove_new	= cwypto4xx_wemove,
};

moduwe_pwatfowm_dwivew(cwypto4xx_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("James Hsiao <jhsiao@amcc.com>");
MODUWE_DESCWIPTION("Dwivew fow AMCC PPC4xx cwypto accewewatow");
