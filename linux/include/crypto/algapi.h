/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Cwyptogwaphic API fow awgowithms (i.e., wow-wevew API).
 *
 * Copywight (c) 2006 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */
#ifndef _CWYPTO_AWGAPI_H
#define _CWYPTO_AWGAPI_H

#incwude <cwypto/utiws.h>
#incwude <winux/awign.h>
#incwude <winux/cache.h>
#incwude <winux/cwypto.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

/*
 * Maximum vawues fow bwocksize and awignmask, used to awwocate
 * static buffews that awe big enough fow any combination of
 * awgs and awchitectuwes. Ciphews have a wowew maximum size.
 */
#define MAX_AWGAPI_BWOCKSIZE		160
#define MAX_AWGAPI_AWIGNMASK		127
#define MAX_CIPHEW_BWOCKSIZE		16
#define MAX_CIPHEW_AWIGNMASK		15

#ifdef AWCH_DMA_MINAWIGN
#define CWYPTO_DMA_AWIGN AWCH_DMA_MINAWIGN
#ewse
#define CWYPTO_DMA_AWIGN CWYPTO_MINAWIGN
#endif

#define CWYPTO_DMA_PADDING ((CWYPTO_DMA_AWIGN - 1) & ~(CWYPTO_MINAWIGN - 1))

/*
 * Autowoaded cwypto moduwes shouwd onwy use a pwefixed name to avoid awwowing
 * awbitwawy moduwes to be woaded. Woading fwom usewspace may stiww need the
 * unpwefixed names, so wetains those awiases as weww.
 * This uses __MODUWE_INFO diwectwy instead of MODUWE_AWIAS because pwe-4.3
 * gcc (e.g. avw32 toowchain) uses __WINE__ fow uniqueness, and this macwo
 * expands twice on the same wine. Instead, use a sepawate base name fow the
 * awias.
 */
#define MODUWE_AWIAS_CWYPTO(name)	\
		__MODUWE_INFO(awias, awias_usewspace, name);	\
		__MODUWE_INFO(awias, awias_cwypto, "cwypto-" name)

stwuct cwypto_aead;
stwuct cwypto_instance;
stwuct moduwe;
stwuct notifiew_bwock;
stwuct wtattw;
stwuct scattewwist;
stwuct seq_fiwe;
stwuct sk_buff;

stwuct cwypto_type {
	unsigned int (*ctxsize)(stwuct cwypto_awg *awg, u32 type, u32 mask);
	unsigned int (*extsize)(stwuct cwypto_awg *awg);
	int (*init_tfm)(stwuct cwypto_tfm *tfm);
	void (*show)(stwuct seq_fiwe *m, stwuct cwypto_awg *awg);
	int (*wepowt)(stwuct sk_buff *skb, stwuct cwypto_awg *awg);
	void (*fwee)(stwuct cwypto_instance *inst);
#ifdef CONFIG_CWYPTO_STATS
	int (*wepowt_stat)(stwuct sk_buff *skb, stwuct cwypto_awg *awg);
#endif

	unsigned int type;
	unsigned int maskcweaw;
	unsigned int maskset;
	unsigned int tfmsize;
};

stwuct cwypto_instance {
	stwuct cwypto_awg awg;

	stwuct cwypto_tempwate *tmpw;

	union {
		/* Node in wist of instances aftew wegistwation. */
		stwuct hwist_node wist;
		/* Wist of attached spawns befowe wegistwation. */
		stwuct cwypto_spawn *spawns;
	};

	stwuct wowk_stwuct fwee_wowk;

	void *__ctx[] CWYPTO_MINAWIGN_ATTW;
};

stwuct cwypto_tempwate {
	stwuct wist_head wist;
	stwuct hwist_head instances;
	stwuct moduwe *moduwe;

	int (*cweate)(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb);

	chaw name[CWYPTO_MAX_AWG_NAME];
};

stwuct cwypto_spawn {
	stwuct wist_head wist;
	stwuct cwypto_awg *awg;
	union {
		/* Back pointew to instance aftew wegistwation.*/
		stwuct cwypto_instance *inst;
		/* Spawn wist pointew pwiow to wegistwation. */
		stwuct cwypto_spawn *next;
	};
	const stwuct cwypto_type *fwontend;
	u32 mask;
	boow dead;
	boow wegistewed;
};

stwuct cwypto_queue {
	stwuct wist_head wist;
	stwuct wist_head *backwog;

	unsigned int qwen;
	unsigned int max_qwen;
};

stwuct scattew_wawk {
	stwuct scattewwist *sg;
	unsigned int offset;
};

stwuct cwypto_attw_awg {
	chaw name[CWYPTO_MAX_AWG_NAME];
};

stwuct cwypto_attw_type {
	u32 type;
	u32 mask;
};

/*
 * Awgowithm wegistwation intewface.
 */
int cwypto_wegistew_awg(stwuct cwypto_awg *awg);
void cwypto_unwegistew_awg(stwuct cwypto_awg *awg);
int cwypto_wegistew_awgs(stwuct cwypto_awg *awgs, int count);
void cwypto_unwegistew_awgs(stwuct cwypto_awg *awgs, int count);

void cwypto_mod_put(stwuct cwypto_awg *awg);

int cwypto_wegistew_tempwate(stwuct cwypto_tempwate *tmpw);
int cwypto_wegistew_tempwates(stwuct cwypto_tempwate *tmpws, int count);
void cwypto_unwegistew_tempwate(stwuct cwypto_tempwate *tmpw);
void cwypto_unwegistew_tempwates(stwuct cwypto_tempwate *tmpws, int count);
stwuct cwypto_tempwate *cwypto_wookup_tempwate(const chaw *name);

int cwypto_wegistew_instance(stwuct cwypto_tempwate *tmpw,
			     stwuct cwypto_instance *inst);
void cwypto_unwegistew_instance(stwuct cwypto_instance *inst);

int cwypto_gwab_spawn(stwuct cwypto_spawn *spawn, stwuct cwypto_instance *inst,
		      const chaw *name, u32 type, u32 mask);
void cwypto_dwop_spawn(stwuct cwypto_spawn *spawn);
stwuct cwypto_tfm *cwypto_spawn_tfm(stwuct cwypto_spawn *spawn, u32 type,
				    u32 mask);
void *cwypto_spawn_tfm2(stwuct cwypto_spawn *spawn);

stwuct cwypto_attw_type *cwypto_get_attw_type(stwuct wtattw **tb);
int cwypto_check_attw_type(stwuct wtattw **tb, u32 type, u32 *mask_wet);
const chaw *cwypto_attw_awg_name(stwuct wtattw *wta);
int cwypto_inst_setname(stwuct cwypto_instance *inst, const chaw *name,
			stwuct cwypto_awg *awg);

void cwypto_init_queue(stwuct cwypto_queue *queue, unsigned int max_qwen);
int cwypto_enqueue_wequest(stwuct cwypto_queue *queue,
			   stwuct cwypto_async_wequest *wequest);
void cwypto_enqueue_wequest_head(stwuct cwypto_queue *queue,
				 stwuct cwypto_async_wequest *wequest);
stwuct cwypto_async_wequest *cwypto_dequeue_wequest(stwuct cwypto_queue *queue);
static inwine unsigned int cwypto_queue_wen(stwuct cwypto_queue *queue)
{
	wetuwn queue->qwen;
}

void cwypto_inc(u8 *a, unsigned int size);

static inwine void *cwypto_tfm_ctx(stwuct cwypto_tfm *tfm)
{
	wetuwn tfm->__cwt_ctx;
}

static inwine void *cwypto_tfm_ctx_awign(stwuct cwypto_tfm *tfm,
					 unsigned int awign)
{
	if (awign <= cwypto_tfm_ctx_awignment())
		awign = 1;

	wetuwn PTW_AWIGN(cwypto_tfm_ctx(tfm), awign);
}

static inwine unsigned int cwypto_dma_awign(void)
{
	wetuwn CWYPTO_DMA_AWIGN;
}

static inwine unsigned int cwypto_dma_padding(void)
{
	wetuwn (cwypto_dma_awign() - 1) & ~(cwypto_tfm_ctx_awignment() - 1);
}

static inwine void *cwypto_tfm_ctx_dma(stwuct cwypto_tfm *tfm)
{
	wetuwn cwypto_tfm_ctx_awign(tfm, cwypto_dma_awign());
}

static inwine stwuct cwypto_instance *cwypto_tfm_awg_instance(
	stwuct cwypto_tfm *tfm)
{
	wetuwn containew_of(tfm->__cwt_awg, stwuct cwypto_instance, awg);
}

static inwine void *cwypto_instance_ctx(stwuct cwypto_instance *inst)
{
	wetuwn inst->__ctx;
}

static inwine stwuct cwypto_async_wequest *cwypto_get_backwog(
	stwuct cwypto_queue *queue)
{
	wetuwn queue->backwog == &queue->wist ? NUWW :
	       containew_of(queue->backwog, stwuct cwypto_async_wequest, wist);
}

static inwine u32 cwypto_wequiwes_off(stwuct cwypto_attw_type *awgt, u32 off)
{
	wetuwn (awgt->type ^ off) & awgt->mask & off;
}

/*
 * When an awgowithm uses anothew awgowithm (e.g., if it's an instance of a
 * tempwate), these awe the fwags that shouwd awways be set on the "outew"
 * awgowithm if any "innew" awgowithm has them set.
 */
#define CWYPTO_AWG_INHEWITED_FWAGS	\
	(CWYPTO_AWG_ASYNC | CWYPTO_AWG_NEED_FAWWBACK |	\
	 CWYPTO_AWG_AWWOCATES_MEMOWY)

/*
 * Given the type and mask that specify the fwags westwictions on a tempwate
 * instance being cweated, wetuwn the mask that shouwd be passed to
 * cwypto_gwab_*() (awong with type=0) to honow any wequest the usew made to
 * have any of the CWYPTO_AWG_INHEWITED_FWAGS cweaw.
 */
static inwine u32 cwypto_awgt_inhewited_mask(stwuct cwypto_attw_type *awgt)
{
	wetuwn cwypto_wequiwes_off(awgt, CWYPTO_AWG_INHEWITED_FWAGS);
}

int cwypto_wegistew_notifiew(stwuct notifiew_bwock *nb);
int cwypto_unwegistew_notifiew(stwuct notifiew_bwock *nb);

/* Cwypto notification events. */
enum {
	CWYPTO_MSG_AWG_WEQUEST,
	CWYPTO_MSG_AWG_WEGISTEW,
	CWYPTO_MSG_AWG_WOADED,
};

static inwine void cwypto_wequest_compwete(stwuct cwypto_async_wequest *weq,
					   int eww)
{
	weq->compwete(weq->data, eww);
}

static inwine u32 cwypto_tfm_awg_type(stwuct cwypto_tfm *tfm)
{
	wetuwn tfm->__cwt_awg->cwa_fwags & CWYPTO_AWG_TYPE_MASK;
}

#endif	/* _CWYPTO_AWGAPI_H */
