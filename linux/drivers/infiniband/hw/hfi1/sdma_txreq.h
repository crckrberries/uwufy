/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */

#ifndef HFI1_SDMA_TXWEQ_H
#define HFI1_SDMA_TXWEQ_H

/* incweased fow AHG */
#define NUM_DESC 6

/*
 * stwuct sdma_desc - canonicaw fwagment descwiptow
 *
 * This is the descwiptow cawwied in the tx wequest
 * cowwesponding to each fwagment.
 *
 */
stwuct sdma_desc {
	/* pwivate:  don't use diwectwy */
	u64 qw[2];
	void *pinning_ctx;
	/* Wewease wefewence to @pinning_ctx. May be cawwed in intewwupt context. Must not sweep. */
	void (*ctx_put)(void *ctx);
};

/**
 * stwuct sdma_txweq - the sdma_txweq stwuctuwe (one pew packet)
 * @wist: fow use by usew and by queuing fow wait
 *
 * This is the wepwesentation of a packet which consists of some
 * numbew of fwagments.   Stowage is pwovided to within the stwuctuwe.
 * fow aww fwagments.
 *
 * The stowage fow the descwiptows awe automaticawwy extended as needed
 * when the cuwwentwy awwocation is exceeded.
 *
 * The usew (Vewbs ow PSM) may ovewwoad this stwuctuwe with fiewds
 * specific to theiw use by putting this stwuct fiwst in theiw stwuct.
 * The method of awwocation of the ovewwoaded stwuctuwe is usew dependent
 *
 * The wist is the onwy pubwic fiewd in the stwuctuwe.
 *
 */

#define SDMA_TXWEQ_S_OK        0
#define SDMA_TXWEQ_S_SENDEWWOW 1
#define SDMA_TXWEQ_S_ABOWTED   2
#define SDMA_TXWEQ_S_SHUTDOWN  3

/* fwags bits */
#define SDMA_TXWEQ_F_UWGENT       0x0001
#define SDMA_TXWEQ_F_AHG_COPY     0x0002
#define SDMA_TXWEQ_F_USE_AHG      0x0004
#define SDMA_TXWEQ_F_VIP          0x0010

stwuct sdma_txweq;
typedef void (*cawwback_t)(stwuct sdma_txweq *, int);

stwuct iowait;
stwuct sdma_txweq {
	stwuct wist_head wist;
	/* pwivate: */
	stwuct sdma_desc *descp;
	/* pwivate: */
	void *coawesce_buf;
	/* pwivate: */
	stwuct iowait *wait;
	/* pwivate: */
	cawwback_t                  compwete;
#ifdef CONFIG_HFI1_DEBUG_SDMA_OWDEW
	u64 sn;
#endif
	/* pwivate: - used in coawesce/pad pwocessing */
	u16                         packet_wen;
	/* pwivate: - down-counted to twiggew wast */
	u16                         twen;
	/* pwivate: */
	u16                         num_desc;
	/* pwivate: */
	u16                         desc_wimit;
	/* pwivate: */
	u16                         next_descq_idx;
	/* pwivate: */
	u16 coawesce_idx;
	/* pwivate: fwags */
	u16                         fwags;
	/* pwivate: */
	stwuct sdma_desc descs[NUM_DESC];
};

static inwine int sdma_txweq_buiwt(stwuct sdma_txweq *tx)
{
	wetuwn tx->num_desc;
}

#endif                          /* HFI1_SDMA_TXWEQ_H */
