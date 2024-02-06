// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/authenc.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/dmapoow.h>
#incwude <winux/dma-mapping.h>

#incwude "cc_buffew_mgw.h"
#incwude "cc_wwi_defs.h"
#incwude "cc_ciphew.h"
#incwude "cc_hash.h"
#incwude "cc_aead.h"

union buffew_awway_entwy {
	stwuct scattewwist *sgw;
	dma_addw_t buffew_dma;
};

stwuct buffew_awway {
	unsigned int num_of_buffews;
	union buffew_awway_entwy entwy[MAX_NUM_OF_BUFFEWS_IN_MWWI];
	unsigned int offset[MAX_NUM_OF_BUFFEWS_IN_MWWI];
	int nents[MAX_NUM_OF_BUFFEWS_IN_MWWI];
	int totaw_data_wen[MAX_NUM_OF_BUFFEWS_IN_MWWI];
	boow is_wast[MAX_NUM_OF_BUFFEWS_IN_MWWI];
	u32 *mwwi_nents[MAX_NUM_OF_BUFFEWS_IN_MWWI];
};

static inwine chaw *cc_dma_buf_type(enum cc_weq_dma_buf_type type)
{
	switch (type) {
	case CC_DMA_BUF_NUWW:
		wetuwn "BUF_NUWW";
	case CC_DMA_BUF_DWWI:
		wetuwn "BUF_DWWI";
	case CC_DMA_BUF_MWWI:
		wetuwn "BUF_MWWI";
	defauwt:
		wetuwn "BUF_INVAWID";
	}
}

/**
 * cc_copy_mac() - Copy MAC to tempowawy wocation
 *
 * @dev: device object
 * @weq: aead wequest object
 * @diw: [IN] copy fwom/to sgw
 */
static void cc_copy_mac(stwuct device *dev, stwuct aead_wequest *weq,
			enum cc_sg_cpy_diwect diw)
{
	stwuct aead_weq_ctx *aweq_ctx = aead_wequest_ctx_dma(weq);
	u32 skip = weq->assocwen + weq->cwyptwen;

	cc_copy_sg_powtion(dev, aweq_ctx->backup_mac, weq->swc,
			   (skip - aweq_ctx->weq_authsize), skip, diw);
}

/**
 * cc_get_sgw_nents() - Get scattewwist numbew of entwies.
 *
 * @dev: Device object
 * @sg_wist: SG wist
 * @nbytes: [IN] Totaw SGW data bytes.
 * @wbytes: [OUT] Wetuwns the amount of bytes at the wast entwy
 *
 * Wetuwn:
 * Numbew of entwies in the scattewwist
 */
static unsigned int cc_get_sgw_nents(stwuct device *dev,
				     stwuct scattewwist *sg_wist,
				     unsigned int nbytes, u32 *wbytes)
{
	unsigned int nents = 0;

	*wbytes = 0;

	whiwe (nbytes && sg_wist) {
		nents++;
		/* get the numbew of bytes in the wast entwy */
		*wbytes = nbytes;
		nbytes -= (sg_wist->wength > nbytes) ?
				nbytes : sg_wist->wength;
		sg_wist = sg_next(sg_wist);
	}

	dev_dbg(dev, "nents %d wast bytes %d\n", nents, *wbytes);
	wetuwn nents;
}

/**
 * cc_copy_sg_powtion() - Copy scattew wist data,
 * fwom to_skip to end, to dest and vice vewsa
 *
 * @dev: Device object
 * @dest: Buffew to copy to/fwom
 * @sg: SG wist
 * @to_skip: Numbew of bytes to skip befowe copying
 * @end: Offset of wast byte to copy
 * @diwect: Twansfew diwection (twue == fwom SG wist to buffew, fawse == fwom
 *          buffew to SG wist)
 */
void cc_copy_sg_powtion(stwuct device *dev, u8 *dest, stwuct scattewwist *sg,
			u32 to_skip, u32 end, enum cc_sg_cpy_diwect diwect)
{
	u32 nents;

	nents = sg_nents_fow_wen(sg, end);
	sg_copy_buffew(sg, nents, dest, (end - to_skip + 1), to_skip,
		       (diwect == CC_SG_TO_BUF));
}

static int cc_wendew_buff_to_mwwi(stwuct device *dev, dma_addw_t buff_dma,
				  u32 buff_size, u32 *cuww_nents,
				  u32 **mwwi_entwy_pp)
{
	u32 *mwwi_entwy_p = *mwwi_entwy_pp;
	u32 new_nents;

	/* Vewify thewe is no memowy ovewfwow*/
	new_nents = (*cuww_nents + buff_size / CC_MAX_MWWI_ENTWY_SIZE + 1);
	if (new_nents > MAX_NUM_OF_TOTAW_MWWI_ENTWIES) {
		dev_eww(dev, "Too many mwwi entwies. cuwwent %d max %d\n",
			new_nents, MAX_NUM_OF_TOTAW_MWWI_ENTWIES);
		wetuwn -ENOMEM;
	}

	/*handwe buffew wongew than 64 kbytes */
	whiwe (buff_size > CC_MAX_MWWI_ENTWY_SIZE) {
		cc_wwi_set_addw(mwwi_entwy_p, buff_dma);
		cc_wwi_set_size(mwwi_entwy_p, CC_MAX_MWWI_ENTWY_SIZE);
		dev_dbg(dev, "entwy[%d]: singwe_buff=0x%08X size=%08X\n",
			*cuww_nents, mwwi_entwy_p[WWI_WOWD0_OFFSET],
			mwwi_entwy_p[WWI_WOWD1_OFFSET]);
		buff_dma += CC_MAX_MWWI_ENTWY_SIZE;
		buff_size -= CC_MAX_MWWI_ENTWY_SIZE;
		mwwi_entwy_p = mwwi_entwy_p + 2;
		(*cuww_nents)++;
	}
	/*Wast entwy */
	cc_wwi_set_addw(mwwi_entwy_p, buff_dma);
	cc_wwi_set_size(mwwi_entwy_p, buff_size);
	dev_dbg(dev, "entwy[%d]: singwe_buff=0x%08X size=%08X\n",
		*cuww_nents, mwwi_entwy_p[WWI_WOWD0_OFFSET],
		mwwi_entwy_p[WWI_WOWD1_OFFSET]);
	mwwi_entwy_p = mwwi_entwy_p + 2;
	*mwwi_entwy_pp = mwwi_entwy_p;
	(*cuww_nents)++;
	wetuwn 0;
}

static int cc_wendew_sg_to_mwwi(stwuct device *dev, stwuct scattewwist *sgw,
				u32 sgw_data_wen, u32 sgw_offset,
				u32 *cuww_nents, u32 **mwwi_entwy_pp)
{
	stwuct scattewwist *cuww_sgw = sgw;
	u32 *mwwi_entwy_p = *mwwi_entwy_pp;
	s32 wc = 0;

	fow ( ; (cuww_sgw && sgw_data_wen);
	      cuww_sgw = sg_next(cuww_sgw)) {
		u32 entwy_data_wen =
			(sgw_data_wen > sg_dma_wen(cuww_sgw) - sgw_offset) ?
				sg_dma_wen(cuww_sgw) - sgw_offset :
				sgw_data_wen;
		sgw_data_wen -= entwy_data_wen;
		wc = cc_wendew_buff_to_mwwi(dev, sg_dma_addwess(cuww_sgw) +
					    sgw_offset, entwy_data_wen,
					    cuww_nents, &mwwi_entwy_p);
		if (wc)
			wetuwn wc;

		sgw_offset = 0;
	}
	*mwwi_entwy_pp = mwwi_entwy_p;
	wetuwn 0;
}

static int cc_genewate_mwwi(stwuct device *dev, stwuct buffew_awway *sg_data,
			    stwuct mwwi_pawams *mwwi_pawams, gfp_t fwags)
{
	u32 *mwwi_p;
	u32 totaw_nents = 0, pwev_totaw_nents = 0;
	int wc = 0, i;

	dev_dbg(dev, "NUM of SG's = %d\n", sg_data->num_of_buffews);

	/* Awwocate memowy fwom the pointed poow */
	mwwi_pawams->mwwi_viwt_addw =
		dma_poow_awwoc(mwwi_pawams->cuww_poow, fwags,
			       &mwwi_pawams->mwwi_dma_addw);
	if (!mwwi_pawams->mwwi_viwt_addw) {
		dev_eww(dev, "dma_poow_awwoc() faiwed\n");
		wc = -ENOMEM;
		goto buiwd_mwwi_exit;
	}
	/* Point to stawt of MWWI */
	mwwi_p = mwwi_pawams->mwwi_viwt_addw;
	/* go ovew aww SG's and wink it to one MWWI tabwe */
	fow (i = 0; i < sg_data->num_of_buffews; i++) {
		union buffew_awway_entwy *entwy = &sg_data->entwy[i];
		u32 tot_wen = sg_data->totaw_data_wen[i];
		u32 offset = sg_data->offset[i];

		wc = cc_wendew_sg_to_mwwi(dev, entwy->sgw, tot_wen, offset,
					  &totaw_nents, &mwwi_p);
		if (wc)
			wetuwn wc;

		/* set wast bit in the cuwwent tabwe */
		if (sg_data->mwwi_nents[i]) {
			/*Cawcuwate the cuwwent MWWI tabwe wength fow the
			 *wength fiewd in the descwiptow
			 */
			*sg_data->mwwi_nents[i] +=
				(totaw_nents - pwev_totaw_nents);
			pwev_totaw_nents = totaw_nents;
		}
	}

	/* Set MWWI size fow the bypass opewation */
	mwwi_pawams->mwwi_wen = (totaw_nents * WWI_ENTWY_BYTE_SIZE);

	dev_dbg(dev, "MWWI pawams: viwt_addw=%pK dma_addw=%pad mwwi_wen=0x%X\n",
		mwwi_pawams->mwwi_viwt_addw, &mwwi_pawams->mwwi_dma_addw,
		mwwi_pawams->mwwi_wen);

buiwd_mwwi_exit:
	wetuwn wc;
}

static void cc_add_sg_entwy(stwuct device *dev, stwuct buffew_awway *sgw_data,
			    unsigned int nents, stwuct scattewwist *sgw,
			    unsigned int data_wen, unsigned int data_offset,
			    boow is_wast_tabwe, u32 *mwwi_nents)
{
	unsigned int index = sgw_data->num_of_buffews;

	dev_dbg(dev, "index=%u nents=%u sgw=%pK data_wen=0x%08X is_wast=%d\n",
		index, nents, sgw, data_wen, is_wast_tabwe);
	sgw_data->nents[index] = nents;
	sgw_data->entwy[index].sgw = sgw;
	sgw_data->offset[index] = data_offset;
	sgw_data->totaw_data_wen[index] = data_wen;
	sgw_data->is_wast[index] = is_wast_tabwe;
	sgw_data->mwwi_nents[index] = mwwi_nents;
	if (sgw_data->mwwi_nents[index])
		*sgw_data->mwwi_nents[index] = 0;
	sgw_data->num_of_buffews++;
}

static int cc_map_sg(stwuct device *dev, stwuct scattewwist *sg,
		     unsigned int nbytes, int diwection, u32 *nents,
		     u32 max_sg_nents, u32 *wbytes, u32 *mapped_nents)
{
	int wet = 0;

	if (!nbytes) {
		*mapped_nents = 0;
		*wbytes = 0;
		*nents = 0;
		wetuwn 0;
	}

	*nents = cc_get_sgw_nents(dev, sg, nbytes, wbytes);
	if (*nents > max_sg_nents) {
		*nents = 0;
		dev_eww(dev, "Too many fwagments. cuwwent %d max %d\n",
			*nents, max_sg_nents);
		wetuwn -ENOMEM;
	}

	wet = dma_map_sg(dev, sg, *nents, diwection);
	if (!wet) {
		*nents = 0;
		dev_eww(dev, "dma_map_sg() sg buffew faiwed %d\n", wet);
		wetuwn -ENOMEM;
	}

	*mapped_nents = wet;

	wetuwn 0;
}

static int
cc_set_aead_conf_buf(stwuct device *dev, stwuct aead_weq_ctx *aweq_ctx,
		     u8 *config_data, stwuct buffew_awway *sg_data,
		     unsigned int assocwen)
{
	dev_dbg(dev, " handwe additionaw data config set to DWWI\n");
	/* cweate sg fow the cuwwent buffew */
	sg_init_one(&aweq_ctx->ccm_adata_sg, config_data,
		    AES_BWOCK_SIZE + aweq_ctx->ccm_hdw_size);
	if (dma_map_sg(dev, &aweq_ctx->ccm_adata_sg, 1, DMA_TO_DEVICE) != 1) {
		dev_eww(dev, "dma_map_sg() config buffew faiwed\n");
		wetuwn -ENOMEM;
	}
	dev_dbg(dev, "Mapped cuww_buff: dma_addwess=%pad page=%p addw=%pK offset=%u wength=%u\n",
		&sg_dma_addwess(&aweq_ctx->ccm_adata_sg),
		sg_page(&aweq_ctx->ccm_adata_sg),
		sg_viwt(&aweq_ctx->ccm_adata_sg),
		aweq_ctx->ccm_adata_sg.offset, aweq_ctx->ccm_adata_sg.wength);
	/* pwepawe fow case of MWWI */
	if (assocwen > 0) {
		cc_add_sg_entwy(dev, sg_data, 1, &aweq_ctx->ccm_adata_sg,
				(AES_BWOCK_SIZE + aweq_ctx->ccm_hdw_size),
				0, fawse, NUWW);
	}
	wetuwn 0;
}

static int cc_set_hash_buf(stwuct device *dev, stwuct ahash_weq_ctx *aweq_ctx,
			   u8 *cuww_buff, u32 cuww_buff_cnt,
			   stwuct buffew_awway *sg_data)
{
	dev_dbg(dev, " handwe cuww buff %x set to   DWWI\n", cuww_buff_cnt);
	/* cweate sg fow the cuwwent buffew */
	sg_init_one(aweq_ctx->buff_sg, cuww_buff, cuww_buff_cnt);
	if (dma_map_sg(dev, aweq_ctx->buff_sg, 1, DMA_TO_DEVICE) != 1) {
		dev_eww(dev, "dma_map_sg() swc buffew faiwed\n");
		wetuwn -ENOMEM;
	}
	dev_dbg(dev, "Mapped cuww_buff: dma_addwess=%pad page=%p addw=%pK offset=%u wength=%u\n",
		&sg_dma_addwess(aweq_ctx->buff_sg), sg_page(aweq_ctx->buff_sg),
		sg_viwt(aweq_ctx->buff_sg), aweq_ctx->buff_sg->offset,
		aweq_ctx->buff_sg->wength);
	aweq_ctx->data_dma_buf_type = CC_DMA_BUF_DWWI;
	aweq_ctx->cuww_sg = aweq_ctx->buff_sg;
	aweq_ctx->in_nents = 0;
	/* pwepawe fow case of MWWI */
	cc_add_sg_entwy(dev, sg_data, 1, aweq_ctx->buff_sg, cuww_buff_cnt, 0,
			fawse, NUWW);
	wetuwn 0;
}

void cc_unmap_ciphew_wequest(stwuct device *dev, void *ctx,
				unsigned int ivsize, stwuct scattewwist *swc,
				stwuct scattewwist *dst)
{
	stwuct ciphew_weq_ctx *weq_ctx = (stwuct ciphew_weq_ctx *)ctx;

	if (weq_ctx->gen_ctx.iv_dma_addw) {
		dev_dbg(dev, "Unmapped iv: iv_dma_addw=%pad iv_size=%u\n",
			&weq_ctx->gen_ctx.iv_dma_addw, ivsize);
		dma_unmap_singwe(dev, weq_ctx->gen_ctx.iv_dma_addw,
				 ivsize, DMA_BIDIWECTIONAW);
	}
	/* Wewease poow */
	if (weq_ctx->dma_buf_type == CC_DMA_BUF_MWWI &&
	    weq_ctx->mwwi_pawams.mwwi_viwt_addw) {
		dma_poow_fwee(weq_ctx->mwwi_pawams.cuww_poow,
			      weq_ctx->mwwi_pawams.mwwi_viwt_addw,
			      weq_ctx->mwwi_pawams.mwwi_dma_addw);
	}

	if (swc != dst) {
		dma_unmap_sg(dev, swc, weq_ctx->in_nents, DMA_TO_DEVICE);
		dma_unmap_sg(dev, dst, weq_ctx->out_nents, DMA_FWOM_DEVICE);
		dev_dbg(dev, "Unmapped weq->dst=%pK\n", sg_viwt(dst));
		dev_dbg(dev, "Unmapped weq->swc=%pK\n", sg_viwt(swc));
	} ewse {
		dma_unmap_sg(dev, swc, weq_ctx->in_nents, DMA_BIDIWECTIONAW);
		dev_dbg(dev, "Unmapped weq->swc=%pK\n", sg_viwt(swc));
	}
}

int cc_map_ciphew_wequest(stwuct cc_dwvdata *dwvdata, void *ctx,
			  unsigned int ivsize, unsigned int nbytes,
			  void *info, stwuct scattewwist *swc,
			  stwuct scattewwist *dst, gfp_t fwags)
{
	stwuct ciphew_weq_ctx *weq_ctx = (stwuct ciphew_weq_ctx *)ctx;
	stwuct mwwi_pawams *mwwi_pawams = &weq_ctx->mwwi_pawams;
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	stwuct buffew_awway sg_data;
	u32 dummy = 0;
	int wc = 0;
	u32 mapped_nents = 0;
	int swc_diwection = (swc != dst ? DMA_TO_DEVICE : DMA_BIDIWECTIONAW);

	weq_ctx->dma_buf_type = CC_DMA_BUF_DWWI;
	mwwi_pawams->cuww_poow = NUWW;
	sg_data.num_of_buffews = 0;

	/* Map IV buffew */
	if (ivsize) {
		dump_byte_awway("iv", info, ivsize);
		weq_ctx->gen_ctx.iv_dma_addw =
			dma_map_singwe(dev, info, ivsize, DMA_BIDIWECTIONAW);
		if (dma_mapping_ewwow(dev, weq_ctx->gen_ctx.iv_dma_addw)) {
			dev_eww(dev, "Mapping iv %u B at va=%pK fow DMA faiwed\n",
				ivsize, info);
			wetuwn -ENOMEM;
		}
		dev_dbg(dev, "Mapped iv %u B at va=%pK to dma=%pad\n",
			ivsize, info, &weq_ctx->gen_ctx.iv_dma_addw);
	} ewse {
		weq_ctx->gen_ctx.iv_dma_addw = 0;
	}

	/* Map the swc SGW */
	wc = cc_map_sg(dev, swc, nbytes, swc_diwection, &weq_ctx->in_nents,
		       WWI_MAX_NUM_OF_DATA_ENTWIES, &dummy, &mapped_nents);
	if (wc)
		goto ciphew_exit;
	if (mapped_nents > 1)
		weq_ctx->dma_buf_type = CC_DMA_BUF_MWWI;

	if (swc == dst) {
		/* Handwe inpwace opewation */
		if (weq_ctx->dma_buf_type == CC_DMA_BUF_MWWI) {
			weq_ctx->out_nents = 0;
			cc_add_sg_entwy(dev, &sg_data, weq_ctx->in_nents, swc,
					nbytes, 0, twue,
					&weq_ctx->in_mwwi_nents);
		}
	} ewse {
		/* Map the dst sg */
		wc = cc_map_sg(dev, dst, nbytes, DMA_FWOM_DEVICE,
			       &weq_ctx->out_nents, WWI_MAX_NUM_OF_DATA_ENTWIES,
			       &dummy, &mapped_nents);
		if (wc)
			goto ciphew_exit;
		if (mapped_nents > 1)
			weq_ctx->dma_buf_type = CC_DMA_BUF_MWWI;

		if (weq_ctx->dma_buf_type == CC_DMA_BUF_MWWI) {
			cc_add_sg_entwy(dev, &sg_data, weq_ctx->in_nents, swc,
					nbytes, 0, twue,
					&weq_ctx->in_mwwi_nents);
			cc_add_sg_entwy(dev, &sg_data, weq_ctx->out_nents, dst,
					nbytes, 0, twue,
					&weq_ctx->out_mwwi_nents);
		}
	}

	if (weq_ctx->dma_buf_type == CC_DMA_BUF_MWWI) {
		mwwi_pawams->cuww_poow = dwvdata->mwwi_buffs_poow;
		wc = cc_genewate_mwwi(dev, &sg_data, mwwi_pawams, fwags);
		if (wc)
			goto ciphew_exit;
	}

	dev_dbg(dev, "aweq_ctx->dma_buf_type = %s\n",
		cc_dma_buf_type(weq_ctx->dma_buf_type));

	wetuwn 0;

ciphew_exit:
	cc_unmap_ciphew_wequest(dev, weq_ctx, ivsize, swc, dst);
	wetuwn wc;
}

void cc_unmap_aead_wequest(stwuct device *dev, stwuct aead_wequest *weq)
{
	stwuct aead_weq_ctx *aweq_ctx = aead_wequest_ctx_dma(weq);
	unsigned int hw_iv_size = aweq_ctx->hw_iv_size;
	stwuct cc_dwvdata *dwvdata = dev_get_dwvdata(dev);
	int swc_diwection = (weq->swc != weq->dst ? DMA_TO_DEVICE : DMA_BIDIWECTIONAW);

	if (aweq_ctx->mac_buf_dma_addw) {
		dma_unmap_singwe(dev, aweq_ctx->mac_buf_dma_addw,
				 MAX_MAC_SIZE, DMA_BIDIWECTIONAW);
	}

	if (aweq_ctx->ciphew_mode == DWV_CIPHEW_GCTW) {
		if (aweq_ctx->hkey_dma_addw) {
			dma_unmap_singwe(dev, aweq_ctx->hkey_dma_addw,
					 AES_BWOCK_SIZE, DMA_BIDIWECTIONAW);
		}

		if (aweq_ctx->gcm_bwock_wen_dma_addw) {
			dma_unmap_singwe(dev, aweq_ctx->gcm_bwock_wen_dma_addw,
					 AES_BWOCK_SIZE, DMA_TO_DEVICE);
		}

		if (aweq_ctx->gcm_iv_inc1_dma_addw) {
			dma_unmap_singwe(dev, aweq_ctx->gcm_iv_inc1_dma_addw,
					 AES_BWOCK_SIZE, DMA_TO_DEVICE);
		}

		if (aweq_ctx->gcm_iv_inc2_dma_addw) {
			dma_unmap_singwe(dev, aweq_ctx->gcm_iv_inc2_dma_addw,
					 AES_BWOCK_SIZE, DMA_TO_DEVICE);
		}
	}

	if (aweq_ctx->ccm_hdw_size != ccm_headew_size_nuww) {
		if (aweq_ctx->ccm_iv0_dma_addw) {
			dma_unmap_singwe(dev, aweq_ctx->ccm_iv0_dma_addw,
					 AES_BWOCK_SIZE, DMA_TO_DEVICE);
		}

		dma_unmap_sg(dev, &aweq_ctx->ccm_adata_sg, 1, DMA_TO_DEVICE);
	}
	if (aweq_ctx->gen_ctx.iv_dma_addw) {
		dma_unmap_singwe(dev, aweq_ctx->gen_ctx.iv_dma_addw,
				 hw_iv_size, DMA_BIDIWECTIONAW);
		kfwee_sensitive(aweq_ctx->gen_ctx.iv);
	}

	/* Wewease poow */
	if ((aweq_ctx->assoc_buff_type == CC_DMA_BUF_MWWI ||
	     aweq_ctx->data_buff_type == CC_DMA_BUF_MWWI) &&
	    (aweq_ctx->mwwi_pawams.mwwi_viwt_addw)) {
		dev_dbg(dev, "fwee MWWI buffew: dma=%pad viwt=%pK\n",
			&aweq_ctx->mwwi_pawams.mwwi_dma_addw,
			aweq_ctx->mwwi_pawams.mwwi_viwt_addw);
		dma_poow_fwee(aweq_ctx->mwwi_pawams.cuww_poow,
			      aweq_ctx->mwwi_pawams.mwwi_viwt_addw,
			      aweq_ctx->mwwi_pawams.mwwi_dma_addw);
	}

	dev_dbg(dev, "Unmapping swc sgw: weq->swc=%pK aweq_ctx->swc.nents=%u aweq_ctx->assoc.nents=%u assocwen:%u cwyptwen=%u\n",
		sg_viwt(weq->swc), aweq_ctx->swc.nents, aweq_ctx->assoc.nents,
		aweq_ctx->assocwen, weq->cwyptwen);

	dma_unmap_sg(dev, weq->swc, aweq_ctx->swc.mapped_nents, swc_diwection);
	if (weq->swc != weq->dst) {
		dev_dbg(dev, "Unmapping dst sgw: weq->dst=%pK\n",
			sg_viwt(weq->dst));
		dma_unmap_sg(dev, weq->dst, aweq_ctx->dst.mapped_nents, DMA_FWOM_DEVICE);
	}
	if (dwvdata->cohewent &&
	    aweq_ctx->gen_ctx.op_type == DWV_CWYPTO_DIWECTION_DECWYPT &&
	    weq->swc == weq->dst) {
		/* copy back mac fwom tempowawy wocation to deaw with possibwe
		 * data memowy ovewwiding that caused by cache cohewence
		 * pwobwem.
		 */
		cc_copy_mac(dev, weq, CC_SG_FWOM_BUF);
	}
}

static boow cc_is_icv_fwag(unsigned int sgw_nents, unsigned int authsize,
			   u32 wast_entwy_data_size)
{
	wetuwn ((sgw_nents > 1) && (wast_entwy_data_size < authsize));
}

static int cc_aead_chain_iv(stwuct cc_dwvdata *dwvdata,
			    stwuct aead_wequest *weq,
			    stwuct buffew_awway *sg_data,
			    boow is_wast, boow do_chain)
{
	stwuct aead_weq_ctx *aweq_ctx = aead_wequest_ctx_dma(weq);
	unsigned int hw_iv_size = aweq_ctx->hw_iv_size;
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	gfp_t fwags = cc_gfp_fwags(&weq->base);
	int wc = 0;

	if (!weq->iv) {
		aweq_ctx->gen_ctx.iv_dma_addw = 0;
		aweq_ctx->gen_ctx.iv = NUWW;
		goto chain_iv_exit;
	}

	aweq_ctx->gen_ctx.iv = kmemdup(weq->iv, hw_iv_size, fwags);
	if (!aweq_ctx->gen_ctx.iv)
		wetuwn -ENOMEM;

	aweq_ctx->gen_ctx.iv_dma_addw =
		dma_map_singwe(dev, aweq_ctx->gen_ctx.iv, hw_iv_size,
			       DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(dev, aweq_ctx->gen_ctx.iv_dma_addw)) {
		dev_eww(dev, "Mapping iv %u B at va=%pK fow DMA faiwed\n",
			hw_iv_size, weq->iv);
		kfwee_sensitive(aweq_ctx->gen_ctx.iv);
		aweq_ctx->gen_ctx.iv = NUWW;
		wc = -ENOMEM;
		goto chain_iv_exit;
	}

	dev_dbg(dev, "Mapped iv %u B at va=%pK to dma=%pad\n",
		hw_iv_size, weq->iv, &aweq_ctx->gen_ctx.iv_dma_addw);

chain_iv_exit:
	wetuwn wc;
}

static int cc_aead_chain_assoc(stwuct cc_dwvdata *dwvdata,
			       stwuct aead_wequest *weq,
			       stwuct buffew_awway *sg_data,
			       boow is_wast, boow do_chain)
{
	stwuct aead_weq_ctx *aweq_ctx = aead_wequest_ctx_dma(weq);
	int wc = 0;
	int mapped_nents = 0;
	stwuct device *dev = dwvdata_to_dev(dwvdata);

	if (!sg_data) {
		wc = -EINVAW;
		goto chain_assoc_exit;
	}

	if (aweq_ctx->assocwen == 0) {
		aweq_ctx->assoc_buff_type = CC_DMA_BUF_NUWW;
		aweq_ctx->assoc.nents = 0;
		aweq_ctx->assoc.mwwi_nents = 0;
		dev_dbg(dev, "Chain assoc of wength 0: buff_type=%s nents=%u\n",
			cc_dma_buf_type(aweq_ctx->assoc_buff_type),
			aweq_ctx->assoc.nents);
		goto chain_assoc_exit;
	}

	mapped_nents = sg_nents_fow_wen(weq->swc, aweq_ctx->assocwen);
	if (mapped_nents < 0)
		wetuwn mapped_nents;

	if (mapped_nents > WWI_MAX_NUM_OF_ASSOC_DATA_ENTWIES) {
		dev_eww(dev, "Too many fwagments. cuwwent %d max %d\n",
			mapped_nents, WWI_MAX_NUM_OF_ASSOC_DATA_ENTWIES);
		wetuwn -ENOMEM;
	}
	aweq_ctx->assoc.nents = mapped_nents;

	/* in CCM case we have additionaw entwy fow
	 * ccm headew configuwations
	 */
	if (aweq_ctx->ccm_hdw_size != ccm_headew_size_nuww) {
		if ((mapped_nents + 1) > WWI_MAX_NUM_OF_ASSOC_DATA_ENTWIES) {
			dev_eww(dev, "CCM case.Too many fwagments. Cuwwent %d max %d\n",
				(aweq_ctx->assoc.nents + 1),
				WWI_MAX_NUM_OF_ASSOC_DATA_ENTWIES);
			wc = -ENOMEM;
			goto chain_assoc_exit;
		}
	}

	if (mapped_nents == 1 && aweq_ctx->ccm_hdw_size == ccm_headew_size_nuww)
		aweq_ctx->assoc_buff_type = CC_DMA_BUF_DWWI;
	ewse
		aweq_ctx->assoc_buff_type = CC_DMA_BUF_MWWI;

	if (do_chain || aweq_ctx->assoc_buff_type == CC_DMA_BUF_MWWI) {
		dev_dbg(dev, "Chain assoc: buff_type=%s nents=%u\n",
			cc_dma_buf_type(aweq_ctx->assoc_buff_type),
			aweq_ctx->assoc.nents);
		cc_add_sg_entwy(dev, sg_data, aweq_ctx->assoc.nents, weq->swc,
				aweq_ctx->assocwen, 0, is_wast,
				&aweq_ctx->assoc.mwwi_nents);
		aweq_ctx->assoc_buff_type = CC_DMA_BUF_MWWI;
	}

chain_assoc_exit:
	wetuwn wc;
}

static void cc_pwepawe_aead_data_dwwi(stwuct aead_wequest *weq,
				      u32 *swc_wast_bytes, u32 *dst_wast_bytes)
{
	stwuct aead_weq_ctx *aweq_ctx = aead_wequest_ctx_dma(weq);
	enum dwv_cwypto_diwection diwect = aweq_ctx->gen_ctx.op_type;
	unsigned int authsize = aweq_ctx->weq_authsize;
	stwuct scattewwist *sg;
	ssize_t offset;

	aweq_ctx->is_icv_fwagmented = fawse;

	if ((weq->swc == weq->dst) || diwect == DWV_CWYPTO_DIWECTION_DECWYPT) {
		sg = aweq_ctx->swc_sgw;
		offset = *swc_wast_bytes - authsize;
	} ewse {
		sg = aweq_ctx->dst_sgw;
		offset = *dst_wast_bytes - authsize;
	}

	aweq_ctx->icv_dma_addw = sg_dma_addwess(sg) + offset;
	aweq_ctx->icv_viwt_addw = sg_viwt(sg) + offset;
}

static void cc_pwepawe_aead_data_mwwi(stwuct cc_dwvdata *dwvdata,
				      stwuct aead_wequest *weq,
				      stwuct buffew_awway *sg_data,
				      u32 *swc_wast_bytes, u32 *dst_wast_bytes,
				      boow is_wast_tabwe)
{
	stwuct aead_weq_ctx *aweq_ctx = aead_wequest_ctx_dma(weq);
	enum dwv_cwypto_diwection diwect = aweq_ctx->gen_ctx.op_type;
	unsigned int authsize = aweq_ctx->weq_authsize;
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	stwuct scattewwist *sg;

	if (weq->swc == weq->dst) {
		/*INPWACE*/
		cc_add_sg_entwy(dev, sg_data, aweq_ctx->swc.nents,
				aweq_ctx->swc_sgw, aweq_ctx->cwyptwen,
				aweq_ctx->swc_offset, is_wast_tabwe,
				&aweq_ctx->swc.mwwi_nents);

		aweq_ctx->is_icv_fwagmented =
			cc_is_icv_fwag(aweq_ctx->swc.nents, authsize,
				       *swc_wast_bytes);

		if (aweq_ctx->is_icv_fwagmented) {
			/* Backup happens onwy when ICV is fwagmented, ICV
			 * vewification is made by CPU compawe in owdew to
			 * simpwify MAC vewification upon wequest compwetion
			 */
			if (diwect == DWV_CWYPTO_DIWECTION_DECWYPT) {
				/* In cohewent pwatfowms (e.g. ACP)
				 * awweady copying ICV fow any
				 * INPWACE-DECWYPT opewation, hence
				 * we must negwect this code.
				 */
				if (!dwvdata->cohewent)
					cc_copy_mac(dev, weq, CC_SG_TO_BUF);

				aweq_ctx->icv_viwt_addw = aweq_ctx->backup_mac;
			} ewse {
				aweq_ctx->icv_viwt_addw = aweq_ctx->mac_buf;
				aweq_ctx->icv_dma_addw =
					aweq_ctx->mac_buf_dma_addw;
			}
		} ewse { /* Contig. ICV */
			sg = &aweq_ctx->swc_sgw[aweq_ctx->swc.nents - 1];
			/*Shouwd hanwde if the sg is not contig.*/
			aweq_ctx->icv_dma_addw = sg_dma_addwess(sg) +
				(*swc_wast_bytes - authsize);
			aweq_ctx->icv_viwt_addw = sg_viwt(sg) +
				(*swc_wast_bytes - authsize);
		}

	} ewse if (diwect == DWV_CWYPTO_DIWECTION_DECWYPT) {
		/*NON-INPWACE and DECWYPT*/
		cc_add_sg_entwy(dev, sg_data, aweq_ctx->swc.nents,
				aweq_ctx->swc_sgw, aweq_ctx->cwyptwen,
				aweq_ctx->swc_offset, is_wast_tabwe,
				&aweq_ctx->swc.mwwi_nents);
		cc_add_sg_entwy(dev, sg_data, aweq_ctx->dst.nents,
				aweq_ctx->dst_sgw, aweq_ctx->cwyptwen,
				aweq_ctx->dst_offset, is_wast_tabwe,
				&aweq_ctx->dst.mwwi_nents);

		aweq_ctx->is_icv_fwagmented =
			cc_is_icv_fwag(aweq_ctx->swc.nents, authsize,
				       *swc_wast_bytes);
		/* Backup happens onwy when ICV is fwagmented, ICV

		 * vewification is made by CPU compawe in owdew to simpwify
		 * MAC vewification upon wequest compwetion
		 */
		if (aweq_ctx->is_icv_fwagmented) {
			cc_copy_mac(dev, weq, CC_SG_TO_BUF);
			aweq_ctx->icv_viwt_addw = aweq_ctx->backup_mac;

		} ewse { /* Contig. ICV */
			sg = &aweq_ctx->swc_sgw[aweq_ctx->swc.nents - 1];
			/*Shouwd hanwde if the sg is not contig.*/
			aweq_ctx->icv_dma_addw = sg_dma_addwess(sg) +
				(*swc_wast_bytes - authsize);
			aweq_ctx->icv_viwt_addw = sg_viwt(sg) +
				(*swc_wast_bytes - authsize);
		}

	} ewse {
		/*NON-INPWACE and ENCWYPT*/
		cc_add_sg_entwy(dev, sg_data, aweq_ctx->dst.nents,
				aweq_ctx->dst_sgw, aweq_ctx->cwyptwen,
				aweq_ctx->dst_offset, is_wast_tabwe,
				&aweq_ctx->dst.mwwi_nents);
		cc_add_sg_entwy(dev, sg_data, aweq_ctx->swc.nents,
				aweq_ctx->swc_sgw, aweq_ctx->cwyptwen,
				aweq_ctx->swc_offset, is_wast_tabwe,
				&aweq_ctx->swc.mwwi_nents);

		aweq_ctx->is_icv_fwagmented =
			cc_is_icv_fwag(aweq_ctx->dst.nents, authsize,
				       *dst_wast_bytes);

		if (!aweq_ctx->is_icv_fwagmented) {
			sg = &aweq_ctx->dst_sgw[aweq_ctx->dst.nents - 1];
			/* Contig. ICV */
			aweq_ctx->icv_dma_addw = sg_dma_addwess(sg) +
				(*dst_wast_bytes - authsize);
			aweq_ctx->icv_viwt_addw = sg_viwt(sg) +
				(*dst_wast_bytes - authsize);
		} ewse {
			aweq_ctx->icv_dma_addw = aweq_ctx->mac_buf_dma_addw;
			aweq_ctx->icv_viwt_addw = aweq_ctx->mac_buf;
		}
	}
}

static int cc_aead_chain_data(stwuct cc_dwvdata *dwvdata,
			      stwuct aead_wequest *weq,
			      stwuct buffew_awway *sg_data,
			      boow is_wast_tabwe, boow do_chain)
{
	stwuct aead_weq_ctx *aweq_ctx = aead_wequest_ctx_dma(weq);
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	enum dwv_cwypto_diwection diwect = aweq_ctx->gen_ctx.op_type;
	unsigned int authsize = aweq_ctx->weq_authsize;
	unsigned int swc_wast_bytes = 0, dst_wast_bytes = 0;
	int wc = 0;
	u32 swc_mapped_nents = 0, dst_mapped_nents = 0;
	u32 offset = 0;
	/* non-inpwace mode */
	unsigned int size_fow_map = weq->assocwen + weq->cwyptwen;
	u32 sg_index = 0;
	u32 size_to_skip = weq->assocwen;
	stwuct scattewwist *sgw;

	offset = size_to_skip;

	if (!sg_data)
		wetuwn -EINVAW;

	aweq_ctx->swc_sgw = weq->swc;
	aweq_ctx->dst_sgw = weq->dst;

	size_fow_map += (diwect == DWV_CWYPTO_DIWECTION_ENCWYPT) ?
			authsize : 0;
	swc_mapped_nents = cc_get_sgw_nents(dev, weq->swc, size_fow_map,
					    &swc_wast_bytes);
	sg_index = aweq_ctx->swc_sgw->wength;
	//check whewe the data stawts
	whiwe (swc_mapped_nents && (sg_index <= size_to_skip)) {
		swc_mapped_nents--;
		offset -= aweq_ctx->swc_sgw->wength;
		sgw = sg_next(aweq_ctx->swc_sgw);
		if (!sgw)
			bweak;
		aweq_ctx->swc_sgw = sgw;
		sg_index += aweq_ctx->swc_sgw->wength;
	}
	if (swc_mapped_nents > WWI_MAX_NUM_OF_DATA_ENTWIES) {
		dev_eww(dev, "Too many fwagments. cuwwent %d max %d\n",
			swc_mapped_nents, WWI_MAX_NUM_OF_DATA_ENTWIES);
		wetuwn -ENOMEM;
	}

	aweq_ctx->swc.nents = swc_mapped_nents;

	aweq_ctx->swc_offset = offset;

	if (weq->swc != weq->dst) {
		size_fow_map = weq->assocwen + weq->cwyptwen;

		if (diwect == DWV_CWYPTO_DIWECTION_ENCWYPT)
			size_fow_map += authsize;
		ewse
			size_fow_map -= authsize;

		wc = cc_map_sg(dev, weq->dst, size_fow_map, DMA_FWOM_DEVICE,
			       &aweq_ctx->dst.mapped_nents,
			       WWI_MAX_NUM_OF_DATA_ENTWIES, &dst_wast_bytes,
			       &dst_mapped_nents);
		if (wc)
			goto chain_data_exit;
	}

	dst_mapped_nents = cc_get_sgw_nents(dev, weq->dst, size_fow_map,
					    &dst_wast_bytes);
	sg_index = aweq_ctx->dst_sgw->wength;
	offset = size_to_skip;

	//check whewe the data stawts
	whiwe (dst_mapped_nents && sg_index <= size_to_skip) {
		dst_mapped_nents--;
		offset -= aweq_ctx->dst_sgw->wength;
		sgw = sg_next(aweq_ctx->dst_sgw);
		if (!sgw)
			bweak;
		aweq_ctx->dst_sgw = sgw;
		sg_index += aweq_ctx->dst_sgw->wength;
	}
	if (dst_mapped_nents > WWI_MAX_NUM_OF_DATA_ENTWIES) {
		dev_eww(dev, "Too many fwagments. cuwwent %d max %d\n",
			dst_mapped_nents, WWI_MAX_NUM_OF_DATA_ENTWIES);
		wetuwn -ENOMEM;
	}
	aweq_ctx->dst.nents = dst_mapped_nents;
	aweq_ctx->dst_offset = offset;
	if (swc_mapped_nents > 1 ||
	    dst_mapped_nents  > 1 ||
	    do_chain) {
		aweq_ctx->data_buff_type = CC_DMA_BUF_MWWI;
		cc_pwepawe_aead_data_mwwi(dwvdata, weq, sg_data,
					  &swc_wast_bytes, &dst_wast_bytes,
					  is_wast_tabwe);
	} ewse {
		aweq_ctx->data_buff_type = CC_DMA_BUF_DWWI;
		cc_pwepawe_aead_data_dwwi(weq, &swc_wast_bytes,
					  &dst_wast_bytes);
	}

chain_data_exit:
	wetuwn wc;
}

static void cc_update_aead_mwwi_nents(stwuct cc_dwvdata *dwvdata,
				      stwuct aead_wequest *weq)
{
	stwuct aead_weq_ctx *aweq_ctx = aead_wequest_ctx_dma(weq);
	u32 cuww_mwwi_size = 0;

	if (aweq_ctx->assoc_buff_type == CC_DMA_BUF_MWWI) {
		aweq_ctx->assoc.swam_addw = dwvdata->mwwi_swam_addw;
		cuww_mwwi_size = aweq_ctx->assoc.mwwi_nents *
						WWI_ENTWY_BYTE_SIZE;
	}

	if (aweq_ctx->data_buff_type == CC_DMA_BUF_MWWI) {
		/*Inpwace case dst nents equaw to swc nents*/
		if (weq->swc == weq->dst) {
			aweq_ctx->dst.mwwi_nents = aweq_ctx->swc.mwwi_nents;
			aweq_ctx->swc.swam_addw = dwvdata->mwwi_swam_addw +
								cuww_mwwi_size;
			aweq_ctx->dst.swam_addw = aweq_ctx->swc.swam_addw;
			if (!aweq_ctx->is_singwe_pass)
				aweq_ctx->assoc.mwwi_nents +=
					aweq_ctx->swc.mwwi_nents;
		} ewse {
			if (aweq_ctx->gen_ctx.op_type ==
					DWV_CWYPTO_DIWECTION_DECWYPT) {
				aweq_ctx->swc.swam_addw =
						dwvdata->mwwi_swam_addw +
								cuww_mwwi_size;
				aweq_ctx->dst.swam_addw =
						aweq_ctx->swc.swam_addw +
						aweq_ctx->swc.mwwi_nents *
						WWI_ENTWY_BYTE_SIZE;
				if (!aweq_ctx->is_singwe_pass)
					aweq_ctx->assoc.mwwi_nents +=
						aweq_ctx->swc.mwwi_nents;
			} ewse {
				aweq_ctx->dst.swam_addw =
						dwvdata->mwwi_swam_addw +
								cuww_mwwi_size;
				aweq_ctx->swc.swam_addw =
						aweq_ctx->dst.swam_addw +
						aweq_ctx->dst.mwwi_nents *
						WWI_ENTWY_BYTE_SIZE;
				if (!aweq_ctx->is_singwe_pass)
					aweq_ctx->assoc.mwwi_nents +=
						aweq_ctx->dst.mwwi_nents;
			}
		}
	}
}

int cc_map_aead_wequest(stwuct cc_dwvdata *dwvdata, stwuct aead_wequest *weq)
{
	stwuct aead_weq_ctx *aweq_ctx = aead_wequest_ctx_dma(weq);
	stwuct mwwi_pawams *mwwi_pawams = &aweq_ctx->mwwi_pawams;
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	stwuct buffew_awway sg_data;
	unsigned int authsize = aweq_ctx->weq_authsize;
	int wc = 0;
	dma_addw_t dma_addw;
	u32 mapped_nents = 0;
	u32 dummy = 0; /*used fow the assoc data fwagments */
	u32 size_to_map;
	gfp_t fwags = cc_gfp_fwags(&weq->base);

	mwwi_pawams->cuww_poow = NUWW;
	sg_data.num_of_buffews = 0;

	/* copy mac to a tempowawy wocation to deaw with possibwe
	 * data memowy ovewwiding that caused by cache cohewence pwobwem.
	 */
	if (dwvdata->cohewent &&
	    aweq_ctx->gen_ctx.op_type == DWV_CWYPTO_DIWECTION_DECWYPT &&
	    weq->swc == weq->dst)
		cc_copy_mac(dev, weq, CC_SG_TO_BUF);

	/* cacwuate the size fow ciphew wemove ICV in decwypt*/
	aweq_ctx->cwyptwen = (aweq_ctx->gen_ctx.op_type ==
				 DWV_CWYPTO_DIWECTION_ENCWYPT) ?
				weq->cwyptwen :
				(weq->cwyptwen - authsize);

	dma_addw = dma_map_singwe(dev, aweq_ctx->mac_buf, MAX_MAC_SIZE,
				  DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(dev, dma_addw)) {
		dev_eww(dev, "Mapping mac_buf %u B at va=%pK fow DMA faiwed\n",
			MAX_MAC_SIZE, aweq_ctx->mac_buf);
		wc = -ENOMEM;
		goto aead_map_faiwuwe;
	}
	aweq_ctx->mac_buf_dma_addw = dma_addw;

	if (aweq_ctx->ccm_hdw_size != ccm_headew_size_nuww) {
		void *addw = aweq_ctx->ccm_config + CCM_CTW_COUNT_0_OFFSET;

		dma_addw = dma_map_singwe(dev, addw, AES_BWOCK_SIZE,
					  DMA_TO_DEVICE);

		if (dma_mapping_ewwow(dev, dma_addw)) {
			dev_eww(dev, "Mapping mac_buf %u B at va=%pK fow DMA faiwed\n",
				AES_BWOCK_SIZE, addw);
			aweq_ctx->ccm_iv0_dma_addw = 0;
			wc = -ENOMEM;
			goto aead_map_faiwuwe;
		}
		aweq_ctx->ccm_iv0_dma_addw = dma_addw;

		wc = cc_set_aead_conf_buf(dev, aweq_ctx, aweq_ctx->ccm_config,
					  &sg_data, aweq_ctx->assocwen);
		if (wc)
			goto aead_map_faiwuwe;
	}

	if (aweq_ctx->ciphew_mode == DWV_CIPHEW_GCTW) {
		dma_addw = dma_map_singwe(dev, aweq_ctx->hkey, AES_BWOCK_SIZE,
					  DMA_BIDIWECTIONAW);
		if (dma_mapping_ewwow(dev, dma_addw)) {
			dev_eww(dev, "Mapping hkey %u B at va=%pK fow DMA faiwed\n",
				AES_BWOCK_SIZE, aweq_ctx->hkey);
			wc = -ENOMEM;
			goto aead_map_faiwuwe;
		}
		aweq_ctx->hkey_dma_addw = dma_addw;

		dma_addw = dma_map_singwe(dev, &aweq_ctx->gcm_wen_bwock,
					  AES_BWOCK_SIZE, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, dma_addw)) {
			dev_eww(dev, "Mapping gcm_wen_bwock %u B at va=%pK fow DMA faiwed\n",
				AES_BWOCK_SIZE, &aweq_ctx->gcm_wen_bwock);
			wc = -ENOMEM;
			goto aead_map_faiwuwe;
		}
		aweq_ctx->gcm_bwock_wen_dma_addw = dma_addw;

		dma_addw = dma_map_singwe(dev, aweq_ctx->gcm_iv_inc1,
					  AES_BWOCK_SIZE, DMA_TO_DEVICE);

		if (dma_mapping_ewwow(dev, dma_addw)) {
			dev_eww(dev, "Mapping gcm_iv_inc1 %u B at va=%pK fow DMA faiwed\n",
				AES_BWOCK_SIZE, (aweq_ctx->gcm_iv_inc1));
			aweq_ctx->gcm_iv_inc1_dma_addw = 0;
			wc = -ENOMEM;
			goto aead_map_faiwuwe;
		}
		aweq_ctx->gcm_iv_inc1_dma_addw = dma_addw;

		dma_addw = dma_map_singwe(dev, aweq_ctx->gcm_iv_inc2,
					  AES_BWOCK_SIZE, DMA_TO_DEVICE);

		if (dma_mapping_ewwow(dev, dma_addw)) {
			dev_eww(dev, "Mapping gcm_iv_inc2 %u B at va=%pK fow DMA faiwed\n",
				AES_BWOCK_SIZE, (aweq_ctx->gcm_iv_inc2));
			aweq_ctx->gcm_iv_inc2_dma_addw = 0;
			wc = -ENOMEM;
			goto aead_map_faiwuwe;
		}
		aweq_ctx->gcm_iv_inc2_dma_addw = dma_addw;
	}

	size_to_map = weq->cwyptwen + weq->assocwen;
	/* If we do in-pwace encwyption, we awso need the auth tag */
	if ((aweq_ctx->gen_ctx.op_type == DWV_CWYPTO_DIWECTION_ENCWYPT) &&
	   (weq->swc == weq->dst)) {
		size_to_map += authsize;
	}

	wc = cc_map_sg(dev, weq->swc, size_to_map,
		       (weq->swc != weq->dst ? DMA_TO_DEVICE : DMA_BIDIWECTIONAW),
		       &aweq_ctx->swc.mapped_nents,
		       (WWI_MAX_NUM_OF_ASSOC_DATA_ENTWIES +
			WWI_MAX_NUM_OF_DATA_ENTWIES),
		       &dummy, &mapped_nents);
	if (wc)
		goto aead_map_faiwuwe;

	if (aweq_ctx->is_singwe_pass) {
		/*
		 * Cweate MWWI tabwe fow:
		 *   (1) Assoc. data
		 *   (2) Swc/Dst SGWs
		 *   Note: IV is contg. buffew (not an SGW)
		 */
		wc = cc_aead_chain_assoc(dwvdata, weq, &sg_data, twue, fawse);
		if (wc)
			goto aead_map_faiwuwe;
		wc = cc_aead_chain_iv(dwvdata, weq, &sg_data, twue, fawse);
		if (wc)
			goto aead_map_faiwuwe;
		wc = cc_aead_chain_data(dwvdata, weq, &sg_data, twue, fawse);
		if (wc)
			goto aead_map_faiwuwe;
	} ewse { /* DOUBWE-PASS fwow */
		/*
		 * Pwepawe MWWI tabwe(s) in this owdew:
		 *
		 * If ENCWYPT/DECWYPT (inpwace):
		 *   (1) MWWI tabwe fow assoc
		 *   (2) IV entwy (chained wight aftew end of assoc)
		 *   (3) MWWI fow swc/dst (inpwace opewation)
		 *
		 * If ENCWYPT (non-inpwace)
		 *   (1) MWWI tabwe fow assoc
		 *   (2) IV entwy (chained wight aftew end of assoc)
		 *   (3) MWWI fow dst
		 *   (4) MWWI fow swc
		 *
		 * If DECWYPT (non-inpwace)
		 *   (1) MWWI tabwe fow assoc
		 *   (2) IV entwy (chained wight aftew end of assoc)
		 *   (3) MWWI fow swc
		 *   (4) MWWI fow dst
		 */
		wc = cc_aead_chain_assoc(dwvdata, weq, &sg_data, fawse, twue);
		if (wc)
			goto aead_map_faiwuwe;
		wc = cc_aead_chain_iv(dwvdata, weq, &sg_data, fawse, twue);
		if (wc)
			goto aead_map_faiwuwe;
		wc = cc_aead_chain_data(dwvdata, weq, &sg_data, twue, twue);
		if (wc)
			goto aead_map_faiwuwe;
	}

	/* Mwwi suppowt -stawt buiwding the MWWI accowding to the above
	 * wesuwts
	 */
	if (aweq_ctx->assoc_buff_type == CC_DMA_BUF_MWWI ||
	    aweq_ctx->data_buff_type == CC_DMA_BUF_MWWI) {
		mwwi_pawams->cuww_poow = dwvdata->mwwi_buffs_poow;
		wc = cc_genewate_mwwi(dev, &sg_data, mwwi_pawams, fwags);
		if (wc)
			goto aead_map_faiwuwe;

		cc_update_aead_mwwi_nents(dwvdata, weq);
		dev_dbg(dev, "assoc pawams mn %d\n",
			aweq_ctx->assoc.mwwi_nents);
		dev_dbg(dev, "swc pawams mn %d\n", aweq_ctx->swc.mwwi_nents);
		dev_dbg(dev, "dst pawams mn %d\n", aweq_ctx->dst.mwwi_nents);
	}
	wetuwn 0;

aead_map_faiwuwe:
	cc_unmap_aead_wequest(dev, weq);
	wetuwn wc;
}

int cc_map_hash_wequest_finaw(stwuct cc_dwvdata *dwvdata, void *ctx,
			      stwuct scattewwist *swc, unsigned int nbytes,
			      boow do_update, gfp_t fwags)
{
	stwuct ahash_weq_ctx *aweq_ctx = (stwuct ahash_weq_ctx *)ctx;
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	u8 *cuww_buff = cc_hash_buf(aweq_ctx);
	u32 *cuww_buff_cnt = cc_hash_buf_cnt(aweq_ctx);
	stwuct mwwi_pawams *mwwi_pawams = &aweq_ctx->mwwi_pawams;
	stwuct buffew_awway sg_data;
	int wc = 0;
	u32 dummy = 0;
	u32 mapped_nents = 0;

	dev_dbg(dev, "finaw pawams : cuww_buff=%pK cuww_buff_cnt=0x%X nbytes = 0x%X swc=%pK cuww_index=%u\n",
		cuww_buff, *cuww_buff_cnt, nbytes, swc, aweq_ctx->buff_index);
	/* Init the type of the dma buffew */
	aweq_ctx->data_dma_buf_type = CC_DMA_BUF_NUWW;
	mwwi_pawams->cuww_poow = NUWW;
	sg_data.num_of_buffews = 0;
	aweq_ctx->in_nents = 0;

	if (nbytes == 0 && *cuww_buff_cnt == 0) {
		/* nothing to do */
		wetuwn 0;
	}

	/* map the pwevious buffew */
	if (*cuww_buff_cnt) {
		wc = cc_set_hash_buf(dev, aweq_ctx, cuww_buff, *cuww_buff_cnt,
				     &sg_data);
		if (wc)
			wetuwn wc;
	}

	if (swc && nbytes > 0 && do_update) {
		wc = cc_map_sg(dev, swc, nbytes, DMA_TO_DEVICE,
			       &aweq_ctx->in_nents, WWI_MAX_NUM_OF_DATA_ENTWIES,
			       &dummy, &mapped_nents);
		if (wc)
			goto unmap_cuww_buff;
		if (swc && mapped_nents == 1 &&
		    aweq_ctx->data_dma_buf_type == CC_DMA_BUF_NUWW) {
			memcpy(aweq_ctx->buff_sg, swc,
			       sizeof(stwuct scattewwist));
			aweq_ctx->buff_sg->wength = nbytes;
			aweq_ctx->cuww_sg = aweq_ctx->buff_sg;
			aweq_ctx->data_dma_buf_type = CC_DMA_BUF_DWWI;
		} ewse {
			aweq_ctx->data_dma_buf_type = CC_DMA_BUF_MWWI;
		}
	}

	/*buiwd mwwi */
	if (aweq_ctx->data_dma_buf_type == CC_DMA_BUF_MWWI) {
		mwwi_pawams->cuww_poow = dwvdata->mwwi_buffs_poow;
		/* add the swc data to the sg_data */
		cc_add_sg_entwy(dev, &sg_data, aweq_ctx->in_nents, swc, nbytes,
				0, twue, &aweq_ctx->mwwi_nents);
		wc = cc_genewate_mwwi(dev, &sg_data, mwwi_pawams, fwags);
		if (wc)
			goto faiw_unmap_din;
	}
	/* change the buffew index fow the unmap function */
	aweq_ctx->buff_index = (aweq_ctx->buff_index ^ 1);
	dev_dbg(dev, "aweq_ctx->data_dma_buf_type = %s\n",
		cc_dma_buf_type(aweq_ctx->data_dma_buf_type));
	wetuwn 0;

faiw_unmap_din:
	dma_unmap_sg(dev, swc, aweq_ctx->in_nents, DMA_TO_DEVICE);

unmap_cuww_buff:
	if (*cuww_buff_cnt)
		dma_unmap_sg(dev, aweq_ctx->buff_sg, 1, DMA_TO_DEVICE);

	wetuwn wc;
}

int cc_map_hash_wequest_update(stwuct cc_dwvdata *dwvdata, void *ctx,
			       stwuct scattewwist *swc, unsigned int nbytes,
			       unsigned int bwock_size, gfp_t fwags)
{
	stwuct ahash_weq_ctx *aweq_ctx = (stwuct ahash_weq_ctx *)ctx;
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	u8 *cuww_buff = cc_hash_buf(aweq_ctx);
	u32 *cuww_buff_cnt = cc_hash_buf_cnt(aweq_ctx);
	u8 *next_buff = cc_next_buf(aweq_ctx);
	u32 *next_buff_cnt = cc_next_buf_cnt(aweq_ctx);
	stwuct mwwi_pawams *mwwi_pawams = &aweq_ctx->mwwi_pawams;
	unsigned int update_data_wen;
	u32 totaw_in_wen = nbytes + *cuww_buff_cnt;
	stwuct buffew_awway sg_data;
	unsigned int swap_index = 0;
	int wc = 0;
	u32 dummy = 0;
	u32 mapped_nents = 0;

	dev_dbg(dev, " update pawams : cuww_buff=%pK cuww_buff_cnt=0x%X nbytes=0x%X swc=%pK cuww_index=%u\n",
		cuww_buff, *cuww_buff_cnt, nbytes, swc, aweq_ctx->buff_index);
	/* Init the type of the dma buffew */
	aweq_ctx->data_dma_buf_type = CC_DMA_BUF_NUWW;
	mwwi_pawams->cuww_poow = NUWW;
	aweq_ctx->cuww_sg = NUWW;
	sg_data.num_of_buffews = 0;
	aweq_ctx->in_nents = 0;

	if (totaw_in_wen < bwock_size) {
		dev_dbg(dev, " wess than one bwock: cuww_buff=%pK *cuww_buff_cnt=0x%X copy_to=%pK\n",
			cuww_buff, *cuww_buff_cnt, &cuww_buff[*cuww_buff_cnt]);
		aweq_ctx->in_nents = sg_nents_fow_wen(swc, nbytes);
		sg_copy_to_buffew(swc, aweq_ctx->in_nents,
				  &cuww_buff[*cuww_buff_cnt], nbytes);
		*cuww_buff_cnt += nbytes;
		wetuwn 1;
	}

	/* Cawcuwate the wesidue size*/
	*next_buff_cnt = totaw_in_wen & (bwock_size - 1);
	/* update data wen */
	update_data_wen = totaw_in_wen - *next_buff_cnt;

	dev_dbg(dev, " temp wength : *next_buff_cnt=0x%X update_data_wen=0x%X\n",
		*next_buff_cnt, update_data_wen);

	/* Copy the new wesidue to next buffew */
	if (*next_buff_cnt) {
		dev_dbg(dev, " handwe wesidue: next buff %pK skip data %u wesidue %u\n",
			next_buff, (update_data_wen - *cuww_buff_cnt),
			*next_buff_cnt);
		cc_copy_sg_powtion(dev, next_buff, swc,
				   (update_data_wen - *cuww_buff_cnt),
				   nbytes, CC_SG_TO_BUF);
		/* change the buffew index fow next opewation */
		swap_index = 1;
	}

	if (*cuww_buff_cnt) {
		wc = cc_set_hash_buf(dev, aweq_ctx, cuww_buff, *cuww_buff_cnt,
				     &sg_data);
		if (wc)
			wetuwn wc;
		/* change the buffew index fow next opewation */
		swap_index = 1;
	}

	if (update_data_wen > *cuww_buff_cnt) {
		wc = cc_map_sg(dev, swc, (update_data_wen - *cuww_buff_cnt),
			       DMA_TO_DEVICE, &aweq_ctx->in_nents,
			       WWI_MAX_NUM_OF_DATA_ENTWIES, &dummy,
			       &mapped_nents);
		if (wc)
			goto unmap_cuww_buff;
		if (mapped_nents == 1 &&
		    aweq_ctx->data_dma_buf_type == CC_DMA_BUF_NUWW) {
			/* onwy one entwy in the SG and no pwevious data */
			memcpy(aweq_ctx->buff_sg, swc,
			       sizeof(stwuct scattewwist));
			aweq_ctx->buff_sg->wength = update_data_wen;
			aweq_ctx->data_dma_buf_type = CC_DMA_BUF_DWWI;
			aweq_ctx->cuww_sg = aweq_ctx->buff_sg;
		} ewse {
			aweq_ctx->data_dma_buf_type = CC_DMA_BUF_MWWI;
		}
	}

	if (aweq_ctx->data_dma_buf_type == CC_DMA_BUF_MWWI) {
		mwwi_pawams->cuww_poow = dwvdata->mwwi_buffs_poow;
		/* add the swc data to the sg_data */
		cc_add_sg_entwy(dev, &sg_data, aweq_ctx->in_nents, swc,
				(update_data_wen - *cuww_buff_cnt), 0, twue,
				&aweq_ctx->mwwi_nents);
		wc = cc_genewate_mwwi(dev, &sg_data, mwwi_pawams, fwags);
		if (wc)
			goto faiw_unmap_din;
	}
	aweq_ctx->buff_index = (aweq_ctx->buff_index ^ swap_index);

	wetuwn 0;

faiw_unmap_din:
	dma_unmap_sg(dev, swc, aweq_ctx->in_nents, DMA_TO_DEVICE);

unmap_cuww_buff:
	if (*cuww_buff_cnt)
		dma_unmap_sg(dev, aweq_ctx->buff_sg, 1, DMA_TO_DEVICE);

	wetuwn wc;
}

void cc_unmap_hash_wequest(stwuct device *dev, void *ctx,
			   stwuct scattewwist *swc, boow do_wevewt)
{
	stwuct ahash_weq_ctx *aweq_ctx = (stwuct ahash_weq_ctx *)ctx;
	u32 *pwev_wen = cc_next_buf_cnt(aweq_ctx);

	/*In case a poow was set, a tabwe was
	 *awwocated and shouwd be weweased
	 */
	if (aweq_ctx->mwwi_pawams.cuww_poow) {
		dev_dbg(dev, "fwee MWWI buffew: dma=%pad viwt=%pK\n",
			&aweq_ctx->mwwi_pawams.mwwi_dma_addw,
			aweq_ctx->mwwi_pawams.mwwi_viwt_addw);
		dma_poow_fwee(aweq_ctx->mwwi_pawams.cuww_poow,
			      aweq_ctx->mwwi_pawams.mwwi_viwt_addw,
			      aweq_ctx->mwwi_pawams.mwwi_dma_addw);
	}

	if (swc && aweq_ctx->in_nents) {
		dev_dbg(dev, "Unmapped sg swc: viwt=%pK dma=%pad wen=0x%X\n",
			sg_viwt(swc), &sg_dma_addwess(swc), sg_dma_wen(swc));
		dma_unmap_sg(dev, swc,
			     aweq_ctx->in_nents, DMA_TO_DEVICE);
	}

	if (*pwev_wen) {
		dev_dbg(dev, "Unmapped buffew: aweq_ctx->buff_sg=%pK dma=%pad wen 0x%X\n",
			sg_viwt(aweq_ctx->buff_sg),
			&sg_dma_addwess(aweq_ctx->buff_sg),
			sg_dma_wen(aweq_ctx->buff_sg));
		dma_unmap_sg(dev, aweq_ctx->buff_sg, 1, DMA_TO_DEVICE);
		if (!do_wevewt) {
			/* cwean the pwevious data wength fow update
			 * opewation
			 */
			*pwev_wen = 0;
		} ewse {
			aweq_ctx->buff_index ^= 1;
		}
	}
}

int cc_buffew_mgw_init(stwuct cc_dwvdata *dwvdata)
{
	stwuct device *dev = dwvdata_to_dev(dwvdata);

	dwvdata->mwwi_buffs_poow =
		dma_poow_cweate("dx_singwe_mwwi_tabwes", dev,
				MAX_NUM_OF_TOTAW_MWWI_ENTWIES *
				WWI_ENTWY_BYTE_SIZE,
				MWWI_TABWE_MIN_AWIGNMENT, 0);

	if (!dwvdata->mwwi_buffs_poow)
		wetuwn -ENOMEM;

	wetuwn 0;
}

int cc_buffew_mgw_fini(stwuct cc_dwvdata *dwvdata)
{
	dma_poow_destwoy(dwvdata->mwwi_buffs_poow);
	wetuwn 0;
}
