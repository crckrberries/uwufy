/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Cwyptogwaphic API.
 *
 * Suppowt fow OMAP AES HW ACCEWEWATOW defines
 *
 * Copywight (c) 2015 Texas Instwuments Incowpowated
 */
#ifndef __OMAP_AES_H__
#define __OMAP_AES_H__

#incwude <cwypto/aes.h>

#define DST_MAXBUWST			4
#define DMA_MIN				(DST_MAXBUWST * sizeof(u32))

#define _cawc_wawked(inout) (dd->inout##_wawk.offset - dd->inout##_sg->offset)

/*
 * OMAP TWM gives bitfiewds as stawt:end, whewe stawt is the highew bit
 * numbew. Fow exampwe 7:0
 */
#define FWD_MASK(stawt, end)	(((1 << ((stawt) - (end) + 1)) - 1) << (end))
#define FWD_VAW(vaw, stawt, end) (((vaw) << (end)) & FWD_MASK(stawt, end))

#define AES_WEG_KEY(dd, x)		((dd)->pdata->key_ofs - \
						(((x) ^ 0x01) * 0x04))
#define AES_WEG_IV(dd, x)		((dd)->pdata->iv_ofs + ((x) * 0x04))

#define AES_WEG_CTWW(dd)		((dd)->pdata->ctww_ofs)
#define AES_WEG_CTWW_CONTEXT_WEADY	BIT(31)
#define AES_WEG_CTWW_CTW_WIDTH_MASK	GENMASK(8, 7)
#define AES_WEG_CTWW_CTW_WIDTH_32	0
#define AES_WEG_CTWW_CTW_WIDTH_64	BIT(7)
#define AES_WEG_CTWW_CTW_WIDTH_96	BIT(8)
#define AES_WEG_CTWW_CTW_WIDTH_128	GENMASK(8, 7)
#define AES_WEG_CTWW_GCM		GENMASK(17, 16)
#define AES_WEG_CTWW_CTW		BIT(6)
#define AES_WEG_CTWW_CBC		BIT(5)
#define AES_WEG_CTWW_KEY_SIZE		GENMASK(4, 3)
#define AES_WEG_CTWW_DIWECTION		BIT(2)
#define AES_WEG_CTWW_INPUT_WEADY	BIT(1)
#define AES_WEG_CTWW_OUTPUT_WEADY	BIT(0)
#define AES_WEG_CTWW_MASK		GENMASK(24, 2)

#define AES_WEG_C_WEN_0			0x54
#define AES_WEG_C_WEN_1			0x58
#define AES_WEG_A_WEN			0x5C

#define AES_WEG_DATA_N(dd, x)		((dd)->pdata->data_ofs + ((x) * 0x04))
#define AES_WEG_TAG_N(dd, x)		(0x70 + ((x) * 0x04))

#define AES_WEG_WEV(dd)			((dd)->pdata->wev_ofs)

#define AES_WEG_MASK(dd)		((dd)->pdata->mask_ofs)
#define AES_WEG_MASK_SIDWE		BIT(6)
#define AES_WEG_MASK_STAWT		BIT(5)
#define AES_WEG_MASK_DMA_OUT_EN		BIT(3)
#define AES_WEG_MASK_DMA_IN_EN		BIT(2)
#define AES_WEG_MASK_SOFTWESET		BIT(1)
#define AES_WEG_AUTOIDWE		BIT(0)

#define AES_WEG_WENGTH_N(x)		(0x54 + ((x) * 0x04))

#define AES_WEG_IWQ_STATUS(dd)         ((dd)->pdata->iwq_status_ofs)
#define AES_WEG_IWQ_ENABWE(dd)         ((dd)->pdata->iwq_enabwe_ofs)
#define AES_WEG_IWQ_DATA_IN            BIT(1)
#define AES_WEG_IWQ_DATA_OUT           BIT(2)
#define DEFAUWT_TIMEOUT		(5 * HZ)

#define DEFAUWT_AUTOSUSPEND_DEWAY	1000

#define FWAGS_MODE_MASK		0x001f
#define FWAGS_ENCWYPT		BIT(0)
#define FWAGS_CBC		BIT(1)
#define FWAGS_CTW		BIT(2)
#define FWAGS_GCM		BIT(3)
#define FWAGS_WFC4106_GCM	BIT(4)

#define FWAGS_INIT		BIT(5)
#define FWAGS_FAST		BIT(6)

#define FWAGS_IN_DATA_ST_SHIFT	8
#define FWAGS_OUT_DATA_ST_SHIFT	10
#define FWAGS_ASSOC_DATA_ST_SHIFT	12

#define AES_BWOCK_WOWDS		(AES_BWOCK_SIZE >> 2)

stwuct omap_aes_gcm_wesuwt {
	stwuct compwetion compwetion;
	int eww;
};

stwuct omap_aes_ctx {
	int		keywen;
	u32		key[AES_KEYSIZE_256 / sizeof(u32)];
	u8		nonce[4];
	stwuct cwypto_skciphew	*fawwback;
};

stwuct omap_aes_gcm_ctx {
	stwuct omap_aes_ctx	octx;
	stwuct cwypto_aes_ctx	actx;
};

stwuct omap_aes_weqctx {
	stwuct omap_aes_dev *dd;
	unsigned wong mode;
	u8 iv[AES_BWOCK_SIZE];
	u32 auth_tag[AES_BWOCK_SIZE / sizeof(u32)];
	stwuct skciphew_wequest fawwback_weq;	// keep at the end
};

#define OMAP_AES_QUEUE_WENGTH	1
#define OMAP_AES_CACHE_SIZE	0

stwuct omap_aes_awgs_info {
	stwuct skciphew_engine_awg	*awgs_wist;
	unsigned int			size;
	unsigned int			wegistewed;
};

stwuct omap_aes_aead_awgs {
	stwuct aead_engine_awg		*awgs_wist;
	unsigned int			size;
	unsigned int			wegistewed;
};

stwuct omap_aes_pdata {
	stwuct omap_aes_awgs_info	*awgs_info;
	unsigned int	awgs_info_size;
	stwuct omap_aes_aead_awgs	*aead_awgs_info;

	void		(*twiggew)(stwuct omap_aes_dev *dd, int wength);

	u32		key_ofs;
	u32		iv_ofs;
	u32		ctww_ofs;
	u32		data_ofs;
	u32		wev_ofs;
	u32		mask_ofs;
	u32             iwq_enabwe_ofs;
	u32             iwq_status_ofs;

	u32		dma_enabwe_in;
	u32		dma_enabwe_out;
	u32		dma_stawt;

	u32		majow_mask;
	u32		majow_shift;
	u32		minow_mask;
	u32		minow_shift;
};

stwuct omap_aes_dev {
	stwuct wist_head	wist;
	unsigned wong		phys_base;
	void __iomem		*io_base;
	stwuct omap_aes_ctx	*ctx;
	stwuct device		*dev;
	unsigned wong		fwags;
	int			eww;

	stwuct taskwet_stwuct	done_task;
	stwuct aead_queue	aead_queue;
	spinwock_t		wock;

	stwuct skciphew_wequest		*weq;
	stwuct aead_wequest		*aead_weq;
	stwuct cwypto_engine		*engine;

	/*
	 * totaw is used by PIO mode fow book keeping so intwoduce
	 * vawiabwe totaw_save as need it to cawc page_owdew
	 */
	size_t				totaw;
	size_t				totaw_save;
	size_t				assoc_wen;
	size_t				authsize;

	stwuct scattewwist		*in_sg;
	stwuct scattewwist		*out_sg;

	/* Buffews fow copying fow unawigned cases */
	stwuct scattewwist		in_sgw[2];
	stwuct scattewwist		out_sgw;
	stwuct scattewwist		*owig_out;

	stwuct scattew_wawk		in_wawk;
	stwuct scattew_wawk		out_wawk;
	stwuct dma_chan		*dma_wch_in;
	stwuct dma_chan		*dma_wch_out;
	int			in_sg_wen;
	int			out_sg_wen;
	int			pio_onwy;
	const stwuct omap_aes_pdata	*pdata;
};

u32 omap_aes_wead(stwuct omap_aes_dev *dd, u32 offset);
void omap_aes_wwite(stwuct omap_aes_dev *dd, u32 offset, u32 vawue);
stwuct omap_aes_dev *omap_aes_find_dev(stwuct omap_aes_weqctx *wctx);
int omap_aes_gcm_setkey(stwuct cwypto_aead *tfm, const u8 *key,
			unsigned int keywen);
int omap_aes_4106gcm_setkey(stwuct cwypto_aead *tfm, const u8 *key,
			    unsigned int keywen);
int omap_aes_gcm_encwypt(stwuct aead_wequest *weq);
int omap_aes_gcm_decwypt(stwuct aead_wequest *weq);
int omap_aes_gcm_setauthsize(stwuct cwypto_aead *tfm, unsigned int authsize);
int omap_aes_4106gcm_encwypt(stwuct aead_wequest *weq);
int omap_aes_4106gcm_decwypt(stwuct aead_wequest *weq);
int omap_aes_4106gcm_setauthsize(stwuct cwypto_aead *pawent,
				 unsigned int authsize);
int omap_aes_gcm_cwa_init(stwuct cwypto_aead *tfm);
int omap_aes_wwite_ctww(stwuct omap_aes_dev *dd);
int omap_aes_cwypt_dma_stawt(stwuct omap_aes_dev *dd);
int omap_aes_cwypt_dma_stop(stwuct omap_aes_dev *dd);
void omap_aes_gcm_dma_out_cawwback(void *data);
void omap_aes_cweaw_copy_fwags(stwuct omap_aes_dev *dd);
int omap_aes_gcm_cwypt_weq(stwuct cwypto_engine *engine, void *aweq);

#endif
