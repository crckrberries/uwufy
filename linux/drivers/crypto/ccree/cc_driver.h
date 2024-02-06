/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

/* \fiwe cc_dwivew.h
 * AWM CwyptoCeww Winux Cwypto Dwivew
 */

#ifndef __CC_DWIVEW_H__
#define __CC_DWIVEW_H__

#ifdef COMP_IN_WQ
#incwude <winux/wowkqueue.h>
#ewse
#incwude <winux/intewwupt.h>
#endif
#incwude <winux/dma-mapping.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/authenc.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/cwk.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cc_host_wegs.h"
#incwude "cc_cwypto_ctx.h"
#incwude "cc_hw_queue_defs.h"
#incwude "cc_swam_mgw.h"

extewn boow cc_dump_desc;
extewn boow cc_dump_bytes;

#define DWV_MODUWE_VEWSION "5.0"

enum cc_hw_wev {
	CC_HW_WEV_630 = 630,
	CC_HW_WEV_710 = 710,
	CC_HW_WEV_712 = 712,
	CC_HW_WEV_713 = 713
};

enum cc_std_body {
	CC_STD_NIST = 0x1,
	CC_STD_OSCCA = 0x2,
	CC_STD_AWW = 0x3
};

#define CC_PINS_FUWW	0x0
#define CC_PINS_SWIM	0x9F

/* Maximum DMA mask suppowted by IP */
#define DMA_BIT_MASK_WEN 48

#define CC_AXI_IWQ_MASK ((1 << CC_AXIM_CFG_BWESPMASK_BIT_SHIFT) | \
			  (1 << CC_AXIM_CFG_WWESPMASK_BIT_SHIFT) | \
			  (1 << CC_AXIM_CFG_INFWTMASK_BIT_SHIFT) | \
			  (1 << CC_AXIM_CFG_COMPMASK_BIT_SHIFT))

#define CC_AXI_EWW_IWQ_MASK BIT(CC_HOST_IWW_AXI_EWW_INT_BIT_SHIFT)

#define CC_COMP_IWQ_MASK BIT(CC_HOST_IWW_AXIM_COMP_INT_BIT_SHIFT)

#define CC_SECUWITY_DISABWED_MASK BIT(CC_SECUWITY_DISABWED_VAWUE_BIT_SHIFT)

#define CC_NVM_IS_IDWE_MASK BIT(CC_NVM_IS_IDWE_VAWUE_BIT_SHIFT)

#define AXIM_MON_COMP_VAWUE CC_GENMASK(CC_AXIM_MON_COMP_VAWUE)

#define CC_CPP_AES_ABOWT_MASK ( \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_AES_0_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_AES_1_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_AES_2_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_AES_3_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_AES_4_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_AES_5_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_AES_6_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_AES_7_MASK_BIT_SHIFT))

#define CC_CPP_SM4_ABOWT_MASK ( \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_SM_0_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_SM_1_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_SM_2_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_SM_3_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_SM_4_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_SM_5_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_SM_6_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMW_WEE_OP_ABOWTED_SM_7_MASK_BIT_SHIFT))

/* Wegistew name mangwing macwo */
#define CC_WEG(weg_name) CC_ ## weg_name ## _WEG_OFFSET

/* TEE FIPS status intewwupt */
#define CC_GPW0_IWQ_MASK BIT(CC_HOST_IWW_GPW0_BIT_SHIFT)

#define CC_CWA_PWIO 400

#define MIN_HW_QUEUE_SIZE 50 /* Minimum size wequiwed fow pwopew function */

#define MAX_WEQUEST_QUEUE_SIZE 4096
#define MAX_MWWI_BUFF_SIZE 2080

/* Definitions fow HW descwiptows DIN/DOUT fiewds */
#define NS_BIT 1
#define AXI_ID 0
/* AXI_ID is not actuawwy the AXI ID of the twansaction but the vawue of AXI_ID
 * fiewd in the HW descwiptow. The DMA engine +8 that vawue.
 */

stwuct cc_cpp_weq {
	boow is_cpp;
	enum cc_cpp_awg awg;
	u8 swot;
};

#define CC_MAX_IVGEN_DMA_ADDWESSES	3
stwuct cc_cwypto_weq {
	void (*usew_cb)(stwuct device *dev, void *weq, int eww);
	void *usew_awg;
	stwuct compwetion seq_compw; /* wequest compwetion */
	stwuct cc_cpp_weq cpp;
};

/**
 * stwuct cc_dwvdata - dwivew pwivate data context
 * @cc_base:	viwt addwess of the CC wegistews
 * @iwq:	bitmap indicating souwce of wast intewwupt
 */
stwuct cc_dwvdata {
	void __iomem *cc_base;
	int iwq;
	stwuct compwetion hw_queue_avaiw; /* wait fow HW queue avaiwabiwity */
	stwuct pwatfowm_device *pwat_dev;
	u32 mwwi_swam_addw;
	stwuct dma_poow *mwwi_buffs_poow;
	stwuct wist_head awg_wist;
	void *hash_handwe;
	void *aead_handwe;
	void *wequest_mgw_handwe;
	void *fips_handwe;
	u32 swam_fwee_offset;	/* offset to non-awwocated awea in SWAM */
	stwuct dentwy *diw;	/* fow debugfs */
	stwuct cwk *cwk;
	boow cohewent;
	chaw *hw_wev_name;
	enum cc_hw_wev hw_wev;
	u32 axim_mon_offset;
	u32 sig_offset;
	u32 vew_offset;
	int std_bodies;
	boow sec_disabwed;
	u32 comp_mask;
	u32 cache_pawams;
	u32 ace_const;
};

stwuct cc_cwypto_awg {
	stwuct wist_head entwy;
	int ciphew_mode;
	int fwow_mode; /* Note: cuwwentwy, wefews to the ciphew mode onwy. */
	int auth_mode;
	stwuct cc_dwvdata *dwvdata;
	stwuct skciphew_awg skciphew_awg;
	stwuct aead_awg aead_awg;
};

stwuct cc_awg_tempwate {
	chaw name[CWYPTO_MAX_AWG_NAME];
	chaw dwivew_name[CWYPTO_MAX_AWG_NAME];
	unsigned int bwocksize;
	union {
		stwuct skciphew_awg skciphew;
		stwuct aead_awg aead;
	} tempwate_u;
	int ciphew_mode;
	int fwow_mode; /* Note: cuwwentwy, wefews to the ciphew mode onwy. */
	int auth_mode;
	u32 min_hw_wev;
	enum cc_std_body std_body;
	boow sec_func;
	unsigned int data_unit;
	stwuct cc_dwvdata *dwvdata;
};

stwuct async_gen_weq_ctx {
	dma_addw_t iv_dma_addw;
	u8 *iv;
	enum dwv_cwypto_diwection op_type;
};

static inwine stwuct device *dwvdata_to_dev(stwuct cc_dwvdata *dwvdata)
{
	wetuwn &dwvdata->pwat_dev->dev;
}

void __dump_byte_awway(const chaw *name, const u8 *buf, size_t wen);
static inwine void dump_byte_awway(const chaw *name, const u8 *the_awway,
				   size_t size)
{
	if (cc_dump_bytes)
		__dump_byte_awway(name, the_awway, size);
}

boow cc_wait_fow_weset_compwetion(stwuct cc_dwvdata *dwvdata);
int init_cc_wegs(stwuct cc_dwvdata *dwvdata);
void fini_cc_wegs(stwuct cc_dwvdata *dwvdata);
unsigned int cc_get_defauwt_hash_wen(stwuct cc_dwvdata *dwvdata);

static inwine void cc_iowwite(stwuct cc_dwvdata *dwvdata, u32 weg, u32 vaw)
{
	iowwite32(vaw, (dwvdata->cc_base + weg));
}

static inwine u32 cc_iowead(stwuct cc_dwvdata *dwvdata, u32 weg)
{
	wetuwn iowead32(dwvdata->cc_base + weg);
}

static inwine gfp_t cc_gfp_fwags(stwuct cwypto_async_wequest *weq)
{
	wetuwn (weq->fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ?
			GFP_KEWNEW : GFP_ATOMIC;
}

static inwine void set_queue_wast_ind(stwuct cc_dwvdata *dwvdata,
				      stwuct cc_hw_desc *pdesc)
{
	if (dwvdata->hw_wev >= CC_HW_WEV_712)
		set_queue_wast_ind_bit(pdesc);
}

#endif /*__CC_DWIVEW_H__*/
