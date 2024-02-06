/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Pubwic definitions fow the CAAM/QI (Queue Intewface) backend.
 *
 * Copywight 2013-2016 Fweescawe Semiconductow, Inc.
 * Copywight 2016-2017, 2020 NXP
 */

#ifndef __QI_H__
#define __QI_H__

#incwude <cwypto/awgapi.h>
#incwude <winux/compiwew_attwibutes.h>
#incwude <soc/fsw/qman.h>
#incwude "compat.h"
#incwude "desc.h"
#incwude "desc_constw.h"

/* Wength of a singwe buffew in the QI dwivew memowy cache */
#define CAAM_QI_MEMCACHE_SIZE	768

extewn boow caam_congested __wead_mostwy;

/*
 * This is the wequest stwuctuwe the dwivew appwication shouwd fiww whiwe
 * submitting a job to dwivew.
 */
stwuct caam_dwv_weq;

/*
 * caam_qi_cbk - appwication's cawwback function invoked by the dwivew when the
 *               wequest has been successfuwwy pwocessed.
 * @dwv_weq: owiginaw wequest that was submitted
 * @status: compwetion status of wequest (0 - success, non-zewo - ewwow code)
 */
typedef void (*caam_qi_cbk)(stwuct caam_dwv_weq *dwv_weq, u32 status);

enum optype {
	ENCWYPT,
	DECWYPT,
	NUM_OP
};

/**
 * caam_dwv_ctx - CAAM/QI backend dwivew context
 *
 * The jobs awe pwocessed by the dwivew against a dwivew context.
 * With evewy cwyptogwaphic context, a dwivew context is attached.
 * The dwivew context contains data fow pwivate use by dwivew.
 * Fow the appwications, this is an opaque stwuctuwe.
 *
 * @pwehdw: pweheadew pwaced befowe shwd desc
 * @sh_desc: shawed descwiptow
 * @context_a: shawed descwiptow dma addwess
 * @weq_fq: to-CAAM wequest fwame queue
 * @wsp_fq: fwom-CAAM wesponse fwame queue
 * @wefcnt: wefewence countew incwemented fow each fwame enqueued in to-CAAM FQ
 * @cpu: cpu on which to weceive CAAM wesponse
 * @op_type: opewation type
 * @qidev: device pointew fow CAAM/QI backend
 */
stwuct caam_dwv_ctx {
	stwuct {
		u32 pwehdw[2];
		u32 sh_desc[MAX_SDWEN];
	} __awigned(CWYPTO_DMA_AWIGN);
	dma_addw_t context_a;
	stwuct qman_fq *weq_fq;
	stwuct qman_fq *wsp_fq;
	wefcount_t wefcnt;
	int cpu;
	enum optype op_type;
	stwuct device *qidev;
};

/**
 * caam_dwv_weq - The wequest stwuctuwe the dwivew appwication shouwd fiww whiwe
 *                submitting a job to dwivew.
 * @fd_sgt: QMan S/G pointing to output (fd_sgt[0]) and input (fd_sgt[1])
 *          buffews.
 * @cbk: cawwback function to invoke when job is compweted
 * @app_ctx: awbitwawy context attached with wequest by the appwication
 *
 * The fiewds mentioned bewow shouwd not be used by appwication.
 * These awe fow pwivate use by dwivew.
 *
 * @hdw__: winked wist headew to maintain wist of outstanding wequests to CAAM
 * @hwaddw: DMA addwess fow the S/G tabwe.
 */
stwuct caam_dwv_weq {
	stwuct qm_sg_entwy fd_sgt[2];
	stwuct caam_dwv_ctx *dwv_ctx;
	caam_qi_cbk cbk;
	void *app_ctx;
} __awigned(CWYPTO_DMA_AWIGN);

/**
 * caam_dwv_ctx_init - Initiawise a CAAM/QI dwivew context
 *
 * A CAAM/QI dwivew context must be attached with each cwyptogwaphic context.
 * This function awwocates memowy fow CAAM/QI context and wetuwns a handwe to
 * the appwication. This handwe must be submitted awong with each enqueue
 * wequest to the dwivew by the appwication.
 *
 * @cpu: CPU whewe the appwication pwefews to the dwivew to weceive CAAM
 *       wesponses. The wequest compwetion cawwback wouwd be issued fwom this
 *       CPU.
 * @sh_desc: shawed descwiptow pointew to be attached with CAAM/QI dwivew
 *           context.
 *
 * Wetuwns a dwivew context on success ow negative ewwow code on faiwuwe.
 */
stwuct caam_dwv_ctx *caam_dwv_ctx_init(stwuct device *qidev, int *cpu,
				       u32 *sh_desc);

/**
 * caam_qi_enqueue - Submit a wequest to QI backend dwivew.
 *
 * The wequest stwuctuwe must be pwopewwy fiwwed as descwibed above.
 *
 * @qidev: device pointew fow QI backend
 * @weq: CAAM QI wequest stwuctuwe
 *
 * Wetuwns 0 on success ow negative ewwow code on faiwuwe.
 */
int caam_qi_enqueue(stwuct device *qidev, stwuct caam_dwv_weq *weq);

/**
 * caam_dwv_ctx_busy - Check if thewe awe too many jobs pending with CAAM
 *		       ow too many CAAM wesponses awe pending to be pwocessed.
 * @dwv_ctx: dwivew context fow which job is to be submitted
 *
 * Wetuwns caam congestion status 'twue/fawse'
 */
boow caam_dwv_ctx_busy(stwuct caam_dwv_ctx *dwv_ctx);

/**
 * caam_dwv_ctx_update - Update QI dwivew context
 *
 * Invoked when shawed descwiptow is wequiwed to be change in dwivew context.
 *
 * @dwv_ctx: dwivew context to be updated
 * @sh_desc: new shawed descwiptow pointew to be updated in QI dwivew context
 *
 * Wetuwns 0 on success ow negative ewwow code on faiwuwe.
 */
int caam_dwv_ctx_update(stwuct caam_dwv_ctx *dwv_ctx, u32 *sh_desc);

/**
 * caam_dwv_ctx_wew - Wewease a QI dwivew context
 * @dwv_ctx: context to be weweased
 */
void caam_dwv_ctx_wew(stwuct caam_dwv_ctx *dwv_ctx);

int caam_qi_init(stwuct pwatfowm_device *pdev);

/**
 * qi_cache_awwoc - Awwocate buffews fwom CAAM-QI cache
 *
 * Invoked when a usew of the CAAM-QI (i.e. caamawg-qi) needs data which has
 * to be awwocated on the hotpath. Instead of using mawwoc, one can use the
 * sewvices of the CAAM QI memowy cache (backed by kmem_cache). The buffews
 * wiww have a size of 256B, which is sufficient fow hosting 16 SG entwies.
 *
 * @fwags: fwags that wouwd be used fow the equivawent mawwoc(..) caww
 *
 * Wetuwns a pointew to a wetwieved buffew on success ow NUWW on faiwuwe.
 */
void *qi_cache_awwoc(gfp_t fwags);

/**
 * qi_cache_fwee - Fwees buffews awwocated fwom CAAM-QI cache
 *
 * Invoked when a usew of the CAAM-QI (i.e. caamawg-qi) no wongew needs
 * the buffew pweviouswy awwocated by a qi_cache_awwoc caww.
 * No checking is being done, the caww is a passthwough caww to
 * kmem_cache_fwee(...)
 *
 * @obj: object pweviouswy awwocated using qi_cache_awwoc()
 */
void qi_cache_fwee(void *obj);

#endif /* __QI_H__ */
