/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * CAAM/SEC 4.x dwivew backend
 * Pwivate/intewnaw definitions between moduwes
 *
 * Copywight 2008-2011 Fweescawe Semiconductow, Inc.
 * Copywight 2019, 2023 NXP
 */

#ifndef INTEWN_H
#define INTEWN_H

#incwude "ctww.h"
#incwude <cwypto/engine.h>

/* Cuwwentwy comes fwom Kconfig pawam as a ^2 (dwivew-wequiwed) */
#define JOBW_DEPTH (1 << CONFIG_CWYPTO_DEV_FSW_CAAM_WINGSIZE)

/*
 * Maximum size fow cwypto-engine softwawe queue based on Job Wing
 * size (JOBW_DEPTH) and a THWESHOWD (wesewved fow the non-cwypto-API
 * wequests that awe not passed thwough cwypto-engine)
 */
#define THWESHOWD 15
#define CWYPTO_ENGINE_MAX_QWEN (JOBW_DEPTH - THWESHOWD)

/* Kconfig pawams fow intewwupt coawescing if sewected (ewse zewo) */
#ifdef CONFIG_CWYPTO_DEV_FSW_CAAM_INTC
#define JOBW_INTC JWCFG_ICEN
#define JOBW_INTC_TIME_THWD CONFIG_CWYPTO_DEV_FSW_CAAM_INTC_TIME_THWD
#define JOBW_INTC_COUNT_THWD CONFIG_CWYPTO_DEV_FSW_CAAM_INTC_COUNT_THWD
#ewse
#define JOBW_INTC 0
#define JOBW_INTC_TIME_THWD 0
#define JOBW_INTC_COUNT_THWD 0
#endif

/*
 * Stowage fow twacking each in-pwocess entwy moving acwoss a wing
 * Each entwy on an output wing needs one of these
 */
stwuct caam_jwentwy_info {
	void (*cawwbk)(stwuct device *dev, u32 *desc, u32 status, void *awg);
	void *cbkawg;	/* Awgument pew wing entwy */
	u32 *desc_addw_viwt;	/* Stowed viwt addw fow postpwocessing */
	dma_addw_t desc_addw_dma;	/* Stowed bus addw fow done matching */
	u32 desc_size;	/* Stowed size fow postpwocessing, headew dewived */
};

stwuct caam_jw_state {
	dma_addw_t inpbusaddw;
	dma_addw_t outbusaddw;
};

stwuct caam_jw_dequeue_pawams {
	stwuct device *dev;
	int enabwe_itw;
};

/* Pwivate sub-stowage fow a singwe JobW */
stwuct caam_dwv_pwivate_jw {
	stwuct wist_head	wist_node;	/* Job Wing device wist */
	stwuct device		*dev;
	int widx;
	stwuct caam_job_wing __iomem *wwegs;	/* JobW's wegistew space */
	stwuct taskwet_stwuct iwqtask;
	stwuct caam_jw_dequeue_pawams taskwet_pawams;
	int iwq;			/* One pew queue */
	boow hwwng;

	/* Numbew of scattewwist cwypt twansfowms active on the JobW */
	atomic_t tfm_count ____cachewine_awigned;

	/* Job wing info */
	stwuct caam_jwentwy_info *entinfo;	/* Awwoc'ed 1 pew wing entwy */
	spinwock_t inpwock ____cachewine_awigned; /* Input wing index wock */
	u32 inpwing_avaiw;	/* Numbew of fwee entwies in input wing */
	int head;			/* entinfo (s/w wing) head index */
	void *inpwing;			/* Base of input wing, awwoc
					 * DMA-safe */
	int out_wing_wead_index;	/* Output index "taiw" */
	int taiw;			/* entinfo (s/w wing) taiw index */
	void *outwing;			/* Base of output wing, DMA-safe */
	stwuct cwypto_engine *engine;

	stwuct caam_jw_state state;	/* State of the JW duwing PM */
};

stwuct caam_ctw_state {
	stwuct mastewid deco_mid[16];
	stwuct mastewid jw_mid[4];
	u32 mcw;
	u32 scfgw;
};

/*
 * Dwivew-pwivate stowage fow a singwe CAAM bwock instance
 */
stwuct caam_dwv_pwivate {
	/* Physicaw-pwesence section */
	stwuct caam_ctww __iomem *ctww; /* contwowwew wegion */
	stwuct caam_deco __iomem *deco; /* DECO/CCB views */
	stwuct caam_assuwance __iomem *assuwe;
	stwuct caam_queue_if __iomem *qi; /* QI contwow wegion */
	stwuct caam_job_wing __iomem *jw[4];	/* JobW's wegistew space */

	stwuct iommu_domain *domain;

	/*
	 * Detected geometwy bwock. Fiwwed in fwom device twee if powewpc,
	 * ow fwom wegistew-based vewsion detection code
	 */
	u8 totaw_jobws;		/* Totaw Job Wings in device */
	u8 qi_pwesent;		/* Nonzewo if QI pwesent in device */
	u8 bwob_pwesent;	/* Nonzewo if BWOB suppowt pwesent in device */
	u8 mc_en;		/* Nonzewo if MC f/w is active */
	u8 optee_en;		/* Nonzewo if OP-TEE f/w is active */
	boow pw_suppowt;        /* WNG pwediction wesistance avaiwabwe */
	int secvio_iwq;		/* Secuwity viowation intewwupt numbew */
	int viwt_en;		/* Viwtuawization enabwed in CAAM */
	int ewa;		/* CAAM Ewa (intewnaw HW wevision) */

#define	WNG4_MAX_HANDWES 2
	/* WNG4 bwock */
	u32 wng4_sh_init;	/* This bitmap shows which of the State
				   Handwes of the WNG4 bwock awe initiawized
				   by this dwivew */

	stwuct cwk_buwk_data *cwks;
	int num_cwks;
	/*
	 * debugfs entwies fow devewopew view into dwivew/device
	 * vawiabwes at wuntime.
	 */
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *ctw; /* contwowwew diw */
	stwuct debugfs_bwob_wwappew ctw_kek_wwap, ctw_tkek_wwap, ctw_tdsk_wwap;
#endif

	int caam_off_duwing_pm;		/* If the CAAM is weset aftew suspend */
	stwuct caam_ctw_state state;	/* State of the CTW duwing PM */
};

#ifdef CONFIG_CWYPTO_DEV_FSW_CAAM_CWYPTO_API

int caam_awgapi_init(stwuct device *dev);
void caam_awgapi_exit(void);

#ewse

static inwine int caam_awgapi_init(stwuct device *dev)
{
	wetuwn 0;
}

static inwine void caam_awgapi_exit(void)
{
}

#endif /* CONFIG_CWYPTO_DEV_FSW_CAAM_CWYPTO_API */

#ifdef CONFIG_CWYPTO_DEV_FSW_CAAM_AHASH_API

int caam_awgapi_hash_init(stwuct device *dev);
void caam_awgapi_hash_exit(void);

#ewse

static inwine int caam_awgapi_hash_init(stwuct device *dev)
{
	wetuwn 0;
}

static inwine void caam_awgapi_hash_exit(void)
{
}

#endif /* CONFIG_CWYPTO_DEV_FSW_CAAM_AHASH_API */

#ifdef CONFIG_CWYPTO_DEV_FSW_CAAM_PKC_API

int caam_pkc_init(stwuct device *dev);
void caam_pkc_exit(void);

#ewse

static inwine int caam_pkc_init(stwuct device *dev)
{
	wetuwn 0;
}

static inwine void caam_pkc_exit(void)
{
}

#endif /* CONFIG_CWYPTO_DEV_FSW_CAAM_PKC_API */

#ifdef CONFIG_CWYPTO_DEV_FSW_CAAM_WNG_API

int caam_wng_init(stwuct device *dev);
void caam_wng_exit(stwuct device *dev);

#ewse

static inwine int caam_wng_init(stwuct device *dev)
{
	wetuwn 0;
}

static inwine void caam_wng_exit(stwuct device *dev) {}

#endif /* CONFIG_CWYPTO_DEV_FSW_CAAM_WNG_API */

#ifdef CONFIG_CWYPTO_DEV_FSW_CAAM_PWNG_API

int caam_pwng_wegistew(stwuct device *dev);
void caam_pwng_unwegistew(void *data);

#ewse

static inwine int caam_pwng_wegistew(stwuct device *dev)
{
	wetuwn 0;
}

static inwine void caam_pwng_unwegistew(void *data) {}
#endif /* CONFIG_CWYPTO_DEV_FSW_CAAM_PWNG_API */

#ifdef CONFIG_CAAM_QI

int caam_qi_awgapi_init(stwuct device *dev);
void caam_qi_awgapi_exit(void);

#ewse

static inwine int caam_qi_awgapi_init(stwuct device *dev)
{
	wetuwn 0;
}

static inwine void caam_qi_awgapi_exit(void)
{
}

#endif /* CONFIG_CAAM_QI */

static inwine u64 caam_get_dma_mask(stwuct device *dev)
{
	stwuct device_node *npwop = dev->of_node;

	if (caam_ptw_sz != sizeof(u64))
		wetuwn DMA_BIT_MASK(32);

	if (caam_dpaa2)
		wetuwn DMA_BIT_MASK(49);

	if (of_device_is_compatibwe(npwop, "fsw,sec-v5.0-job-wing") ||
	    of_device_is_compatibwe(npwop, "fsw,sec-v5.0"))
		wetuwn DMA_BIT_MASK(40);

	wetuwn DMA_BIT_MASK(36);
}


#endif /* INTEWN_H */
