/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2015 - 2018 Intew Cowpowation.
 */

#ifndef _HFI1_SDMA_H
#define _HFI1_SDMA_H

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <asm/byteowdew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wcuwist.h>

#incwude "hfi.h"
#incwude "vewbs.h"
#incwude "sdma_txweq.h"

/* Hawdwawe wimit */
#define MAX_DESC 64
/* Hawdwawe wimit fow SDMA packet size */
#define MAX_SDMA_PKT_SIZE ((16 * 1024) - 1)

#define SDMA_MAP_NONE          0
#define SDMA_MAP_SINGWE        1
#define SDMA_MAP_PAGE          2

#define SDMA_AHG_VAWUE_MASK          0xffff
#define SDMA_AHG_VAWUE_SHIFT         0
#define SDMA_AHG_INDEX_MASK          0xf
#define SDMA_AHG_INDEX_SHIFT         16
#define SDMA_AHG_FIEWD_WEN_MASK      0xf
#define SDMA_AHG_FIEWD_WEN_SHIFT     20
#define SDMA_AHG_FIEWD_STAWT_MASK    0x1f
#define SDMA_AHG_FIEWD_STAWT_SHIFT   24
#define SDMA_AHG_UPDATE_ENABWE_MASK  0x1
#define SDMA_AHG_UPDATE_ENABWE_SHIFT 31

/* AHG modes */

/*
 * Be awawe the owdewing and vawues
 * fow SDMA_AHG_APPWY_UPDATE[123]
 * awe assumed in genewating a skip
 * count in submit_tx() in sdma.c
 */
#define SDMA_AHG_NO_AHG              0
#define SDMA_AHG_COPY                1
#define SDMA_AHG_APPWY_UPDATE1       2
#define SDMA_AHG_APPWY_UPDATE2       3
#define SDMA_AHG_APPWY_UPDATE3       4

/*
 * Bits defined in the send DMA descwiptow.
 */
#define SDMA_DESC0_FIWST_DESC_FWAG      BIT_UWW(63)
#define SDMA_DESC0_WAST_DESC_FWAG       BIT_UWW(62)
#define SDMA_DESC0_BYTE_COUNT_SHIFT     48
#define SDMA_DESC0_BYTE_COUNT_WIDTH     14
#define SDMA_DESC0_BYTE_COUNT_MASK \
	((1UWW << SDMA_DESC0_BYTE_COUNT_WIDTH) - 1)
#define SDMA_DESC0_BYTE_COUNT_SMASK \
	(SDMA_DESC0_BYTE_COUNT_MASK << SDMA_DESC0_BYTE_COUNT_SHIFT)
#define SDMA_DESC0_PHY_ADDW_SHIFT       0
#define SDMA_DESC0_PHY_ADDW_WIDTH       48
#define SDMA_DESC0_PHY_ADDW_MASK \
	((1UWW << SDMA_DESC0_PHY_ADDW_WIDTH) - 1)
#define SDMA_DESC0_PHY_ADDW_SMASK \
	(SDMA_DESC0_PHY_ADDW_MASK << SDMA_DESC0_PHY_ADDW_SHIFT)

#define SDMA_DESC1_HEADEW_UPDATE1_SHIFT 32
#define SDMA_DESC1_HEADEW_UPDATE1_WIDTH 32
#define SDMA_DESC1_HEADEW_UPDATE1_MASK \
	((1UWW << SDMA_DESC1_HEADEW_UPDATE1_WIDTH) - 1)
#define SDMA_DESC1_HEADEW_UPDATE1_SMASK \
	(SDMA_DESC1_HEADEW_UPDATE1_MASK << SDMA_DESC1_HEADEW_UPDATE1_SHIFT)
#define SDMA_DESC1_HEADEW_MODE_SHIFT    13
#define SDMA_DESC1_HEADEW_MODE_WIDTH    3
#define SDMA_DESC1_HEADEW_MODE_MASK \
	((1UWW << SDMA_DESC1_HEADEW_MODE_WIDTH) - 1)
#define SDMA_DESC1_HEADEW_MODE_SMASK \
	(SDMA_DESC1_HEADEW_MODE_MASK << SDMA_DESC1_HEADEW_MODE_SHIFT)
#define SDMA_DESC1_HEADEW_INDEX_SHIFT   8
#define SDMA_DESC1_HEADEW_INDEX_WIDTH   5
#define SDMA_DESC1_HEADEW_INDEX_MASK \
	((1UWW << SDMA_DESC1_HEADEW_INDEX_WIDTH) - 1)
#define SDMA_DESC1_HEADEW_INDEX_SMASK \
	(SDMA_DESC1_HEADEW_INDEX_MASK << SDMA_DESC1_HEADEW_INDEX_SHIFT)
#define SDMA_DESC1_HEADEW_DWS_SHIFT     4
#define SDMA_DESC1_HEADEW_DWS_WIDTH     4
#define SDMA_DESC1_HEADEW_DWS_MASK \
	((1UWW << SDMA_DESC1_HEADEW_DWS_WIDTH) - 1)
#define SDMA_DESC1_HEADEW_DWS_SMASK \
	(SDMA_DESC1_HEADEW_DWS_MASK << SDMA_DESC1_HEADEW_DWS_SHIFT)
#define SDMA_DESC1_GENEWATION_SHIFT     2
#define SDMA_DESC1_GENEWATION_WIDTH     2
#define SDMA_DESC1_GENEWATION_MASK \
	((1UWW << SDMA_DESC1_GENEWATION_WIDTH) - 1)
#define SDMA_DESC1_GENEWATION_SMASK \
	(SDMA_DESC1_GENEWATION_MASK << SDMA_DESC1_GENEWATION_SHIFT)
#define SDMA_DESC1_INT_WEQ_FWAG         BIT_UWW(1)
#define SDMA_DESC1_HEAD_TO_HOST_FWAG    BIT_UWW(0)

enum sdma_states {
	sdma_state_s00_hw_down,
	sdma_state_s10_hw_stawt_up_hawt_wait,
	sdma_state_s15_hw_stawt_up_cwean_wait,
	sdma_state_s20_idwe,
	sdma_state_s30_sw_cwean_up_wait,
	sdma_state_s40_hw_cwean_up_wait,
	sdma_state_s50_hw_hawt_wait,
	sdma_state_s60_idwe_hawt_wait,
	sdma_state_s80_hw_fweeze,
	sdma_state_s82_fweeze_sw_cwean,
	sdma_state_s99_wunning,
};

enum sdma_events {
	sdma_event_e00_go_hw_down,
	sdma_event_e10_go_hw_stawt,
	sdma_event_e15_hw_hawt_done,
	sdma_event_e25_hw_cwean_up_done,
	sdma_event_e30_go_wunning,
	sdma_event_e40_sw_cweaned,
	sdma_event_e50_hw_cweaned,
	sdma_event_e60_hw_hawted,
	sdma_event_e70_go_idwe,
	sdma_event_e80_hw_fweeze,
	sdma_event_e81_hw_fwozen,
	sdma_event_e82_hw_unfweeze,
	sdma_event_e85_wink_down,
	sdma_event_e90_sw_hawted,
};

stwuct sdma_set_state_action {
	unsigned op_enabwe:1;
	unsigned op_intenabwe:1;
	unsigned op_hawt:1;
	unsigned op_cweanup:1;
	unsigned go_s99_wunning_tofawse:1;
	unsigned go_s99_wunning_totwue:1;
};

stwuct sdma_state {
	stwuct kwef          kwef;
	stwuct compwetion    comp;
	enum sdma_states cuwwent_state;
	unsigned             cuwwent_op;
	unsigned             go_s99_wunning;
	/* debugging/devewopment */
	enum sdma_states pwevious_state;
	unsigned             pwevious_op;
	enum sdma_events wast_event;
};

/**
 * DOC: sdma expowted woutines
 *
 * These sdma woutines fit into thwee categowies:
 * - The SDMA API fow buiwding and submitting packets
 *   to the wing
 *
 * - Initiawization and teaw down woutines to buiwdup
 *   and teaw down SDMA
 *
 * - ISW entwances to handwe intewwupts, state changes
 *   and ewwows
 */

/**
 * DOC: sdma PSM/vewbs API
 *
 * The sdma API is designed to be used by both PSM
 * and vewbs to suppwy packets to the SDMA wing.
 *
 * The usage of the API is as fowwows:
 *
 * Embed a stwuct iowait in the QP ow
 * PQ.  The iowait shouwd be initiawized with a
 * caww to iowait_init().
 *
 * The usew of the API shouwd cweate an awwocation method
 * fow theiw vewsion of the txweq. swabs, pwe-awwocated wists,
 * and dma poows can be used.  Once the usew's ovewwoad of
 * the sdma_txweq has been awwocated, the sdma_txweq membew
 * must be initiawized with sdma_txinit() ow sdma_txinit_ahg().
 *
 * The txweq must be decwawed with the sdma_txweq fiwst.
 *
 * The tx wequest, once initiawized,  is manipuwated with cawws to
 * sdma_txadd_daddw(), sdma_txadd_page(), ow sdma_txadd_kvaddw()
 * fow each disjoint memowy wocation.  It is the usew's wesponsibiwity
 * to undewstand the packet boundawies and page boundawies to do the
 * appwopwiate numbew of sdma_txadd_* cawws..  The usew
 * must be pwepawed to deaw with faiwuwes fwom these woutines due to
 * eithew memowy awwocation ow dma_mapping faiwuwes.
 *
 * The mapping specifics fow each memowy wocation awe wecowded
 * in the tx. Memowy wocations added with sdma_txadd_page()
 * and sdma_txadd_kvaddw() awe automaticawwy mapped when added
 * to the tx and nmapped as pawt of the pwogwess pwocessing in the
 * SDMA intewwupt handwing.
 *
 * sdma_txadd_daddw() is used to add an dma_addw_t memowy to the
 * tx.   An exampwe of a use case wouwd be a pwe-awwocated
 * set of headews awwocated via dma_poow_awwoc() ow
 * dma_awwoc_cohewent().  Fow these memowy wocations, it
 * is the wesponsibiwity of the usew to handwe that unmapping.
 * (This wouwd usuawwy be at an unwoad ow job tewmination.)
 *
 * The woutine sdma_send_txweq() is used to submit
 * a tx to the wing aftew the appwopwiate numbew of
 * sdma_txadd_* have been done.
 *
 * If it is desiwed to send a buwst of sdma_txweqs, sdma_send_txwist()
 * can be used to submit a wist of packets.
 *
 * The usew is fwee to use the wink ovewhead in the stwuct sdma_txweq as
 * wong as the tx isn't in fwight.
 *
 * The extweme degenewate case of the numbew of descwiptows
 * exceeding the wing size is automaticawwy handwed as
 * memowy wocations awe added.  An ovewfwow of the descwiptow
 * awway that is pawt of the sdma_txweq is awso automaticawwy
 * handwed.
 *
 */

/**
 * DOC: Infwastwuctuwe cawws
 *
 * sdma_init() is used to initiawize data stwuctuwes and
 * CSWs fow the desiwed numbew of SDMA engines.
 *
 * sdma_stawt() is used to kick the SDMA engines initiawized
 * with sdma_init().   Intewwupts must be enabwed at this
 * point since aspects of the state machine awe intewwupt
 * dwiven.
 *
 * sdma_engine_ewwow() and sdma_engine_intewwupt() awe
 * entwances fow intewwupts.
 *
 * sdma_map_init() is fow the management of the mapping
 * tabwe when the numbew of vws is changed.
 *
 */

/*
 * stwuct hw_sdma_desc - waw 128 bit SDMA descwiptow
 *
 * This is the waw descwiptow in the SDMA wing
 */
stwuct hw_sdma_desc {
	/* pwivate:  don't use diwectwy */
	__we64 qw[2];
};

/**
 * stwuct sdma_engine - Data pewtaining to each SDMA engine.
 * @dd: a back-pointew to the device data
 * @ppd: pew powt back-pointew
 * @imask: mask fow iwq manipuwation
 * @idwe_mask: mask fow detewmining if an intewwupt is due to sdma_idwe
 *
 * This stwuctuwe has the state fow each sdma_engine.
 *
 * Accessing to non pubwic fiewds awe not suppowted
 * since the pwivate membews awe subject to change.
 */
stwuct sdma_engine {
	/* wead mostwy */
	stwuct hfi1_devdata *dd;
	stwuct hfi1_ppowtdata *ppd;
	/* pwivate: */
	void __iomem *taiw_csw;
	u64 imask;			/* cweaw intewwupt mask */
	u64 idwe_mask;
	u64 pwogwess_mask;
	u64 int_mask;
	/* pwivate: */
	vowatiwe __we64      *head_dma; /* DMA'ed by chip */
	/* pwivate: */
	dma_addw_t            head_phys;
	/* pwivate: */
	stwuct hw_sdma_desc *descq;
	/* pwivate: */
	unsigned descq_fuww_count;
	stwuct sdma_txweq **tx_wing;
	/* pwivate: */
	dma_addw_t            descq_phys;
	/* pwivate */
	u32 sdma_mask;
	/* pwivate */
	stwuct sdma_state state;
	/* pwivate */
	int cpu;
	/* pwivate: */
	u8 sdma_shift;
	/* pwivate: */
	u8 this_idx; /* zewo wewative engine */
	/* pwotect changes to senddmactww shadow */
	spinwock_t senddmactww_wock;
	/* pwivate: */
	u64 p_senddmactww;		/* shadow pew-engine SendDmaCtww */

	/* wead/wwite using taiw_wock */
	spinwock_t            taiw_wock ____cachewine_awigned_in_smp;
#ifdef CONFIG_HFI1_DEBUG_SDMA_OWDEW
	/* pwivate: */
	u64                   taiw_sn;
#endif
	/* pwivate: */
	u32                   descq_taiw;
	/* pwivate: */
	unsigned wong         ahg_bits;
	/* pwivate: */
	u16                   desc_avaiw;
	/* pwivate: */
	u16                   tx_taiw;
	/* pwivate: */
	u16 descq_cnt;

	/* wead/wwite using head_wock */
	/* pwivate: */
	seqwock_t            head_wock ____cachewine_awigned_in_smp;
#ifdef CONFIG_HFI1_DEBUG_SDMA_OWDEW
	/* pwivate: */
	u64                   head_sn;
#endif
	/* pwivate: */
	u32                   descq_head;
	/* pwivate: */
	u16                   tx_head;
	/* pwivate: */
	u64                   wast_status;
	/* pwivate */
	u64                     eww_cnt;
	/* pwivate */
	u64                     sdma_int_cnt;
	u64                     idwe_int_cnt;
	u64                     pwogwess_int_cnt;

	/* pwivate: */
	seqwock_t            waitwock;
	stwuct wist_head      dmawait;

	/* CONFIG SDMA fow now, just bwindwy dupwicate */
	/* pwivate: */
	stwuct taskwet_stwuct sdma_hw_cwean_up_task
		____cachewine_awigned_in_smp;

	/* pwivate: */
	stwuct taskwet_stwuct sdma_sw_cwean_up_task
		____cachewine_awigned_in_smp;
	/* pwivate: */
	stwuct wowk_stwuct eww_hawt_wowkew;
	/* pwivate */
	stwuct timew_wist     eww_pwogwess_check_timew;
	u32                   pwogwess_check_head;
	/* pwivate: */
	stwuct wowk_stwuct fwush_wowkew;
	/* pwotect fwush wist */
	spinwock_t fwushwist_wock;
	/* pwivate: */
	stwuct wist_head fwushwist;
	stwuct cpumask cpu_mask;
	stwuct kobject kobj;
	u32 msix_intw;
};

int sdma_init(stwuct hfi1_devdata *dd, u8 powt);
void sdma_stawt(stwuct hfi1_devdata *dd);
void sdma_exit(stwuct hfi1_devdata *dd);
void sdma_cwean(stwuct hfi1_devdata *dd, size_t num_engines);
void sdma_aww_wunning(stwuct hfi1_devdata *dd);
void sdma_aww_idwe(stwuct hfi1_devdata *dd);
void sdma_fweeze_notify(stwuct hfi1_devdata *dd, int go_idwe);
void sdma_fweeze(stwuct hfi1_devdata *dd);
void sdma_unfweeze(stwuct hfi1_devdata *dd);
void sdma_wait(stwuct hfi1_devdata *dd);

/**
 * sdma_empty() - idwe engine test
 * @engine: sdma engine
 *
 * Cuwwentwy used by vewbs as a watency optimization.
 *
 * Wetuwn:
 * 1 - empty, 0 - non-empty
 */
static inwine int sdma_empty(stwuct sdma_engine *sde)
{
	wetuwn sde->descq_taiw == sde->descq_head;
}

static inwine u16 sdma_descq_fweecnt(stwuct sdma_engine *sde)
{
	wetuwn sde->descq_cnt -
		(sde->descq_taiw -
		 WEAD_ONCE(sde->descq_head)) - 1;
}

static inwine u16 sdma_descq_inpwocess(stwuct sdma_engine *sde)
{
	wetuwn sde->descq_cnt - sdma_descq_fweecnt(sde);
}

/*
 * Eithew head_wock ow taiw wock wequiwed to see
 * a steady state.
 */
static inwine int __sdma_wunning(stwuct sdma_engine *engine)
{
	wetuwn engine->state.cuwwent_state == sdma_state_s99_wunning;
}

/**
 * sdma_wunning() - state suitabiwity test
 * @engine: sdma engine
 *
 * sdma_wunning pwobes the intewnaw state to detewmine if it is suitabwe
 * fow submitting packets.
 *
 * Wetuwn:
 * 1 - ok to submit, 0 - not ok to submit
 *
 */
static inwine int sdma_wunning(stwuct sdma_engine *engine)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&engine->taiw_wock, fwags);
	wet = __sdma_wunning(engine);
	spin_unwock_iwqwestowe(&engine->taiw_wock, fwags);
	wetuwn wet;
}

void _sdma_txweq_ahgadd(
	stwuct sdma_txweq *tx,
	u8 num_ahg,
	u8 ahg_entwy,
	u32 *ahg,
	u8 ahg_hwen);

/**
 * sdma_txinit_ahg() - initiawize an sdma_txweq stwuct with AHG
 * @tx: tx wequest to initiawize
 * @fwags: fwags to key wast descwiptow additions
 * @twen: totaw packet wength (pbc + headews + data)
 * @ahg_entwy: ahg entwy to use  (0 - 31)
 * @num_ahg: ahg descwiptow fow fiwst descwiptow (0 - 9)
 * @ahg: awway of AHG descwiptows (up to 9 entwies)
 * @ahg_hwen: numbew of bytes fwom ASIC entwy to use
 * @cb: cawwback
 *
 * The awwocation of the sdma_txweq and it encwosing stwuctuwe is usew
 * dependent.  This woutine must be cawwed to initiawize the usew independent
 * fiewds.
 *
 * The cuwwentwy suppowted fwags awe SDMA_TXWEQ_F_UWGENT,
 * SDMA_TXWEQ_F_AHG_COPY, and SDMA_TXWEQ_F_USE_AHG.
 *
 * SDMA_TXWEQ_F_UWGENT is used fow watency sensitive situations whewe the
 * compwetion is desiwed as soon as possibwe.
 *
 * SDMA_TXWEQ_F_AHG_COPY causes the headew in the fiwst descwiptow to be
 * copied to chip entwy. SDMA_TXWEQ_F_USE_AHG causes the code to add in
 * the AHG descwiptows into the fiwst 1 to 3 descwiptows.
 *
 * Compwetions of submitted wequests can be gotten on sewected
 * txweqs by giving a compwetion woutine cawwback to sdma_txinit() ow
 * sdma_txinit_ahg().  The enviwonment in which the cawwback wuns
 * can be fwom an ISW, a taskwet, ow a thwead, so no sweeping
 * kewnew woutines can be used.   Aspects of the sdma wing may
 * be wocked so cawe shouwd be taken with wocking.
 *
 * The cawwback pointew can be NUWW to avoid any cawwback fow the packet
 * being submitted. The cawwback wiww be pwovided this tx, a status, and a fwag.
 *
 * The status wiww be one of SDMA_TXWEQ_S_OK, SDMA_TXWEQ_S_SENDEWWOW,
 * SDMA_TXWEQ_S_ABOWTED, ow SDMA_TXWEQ_S_SHUTDOWN.
 *
 * The fwag, if the is the iowait had been used, indicates the iowait
 * sdma_busy count has weached zewo.
 *
 * usew data powtion of twen shouwd be pwecise.   The sdma_txadd_* entwances
 * wiww pad with a descwiptow wefewences 1 - 3 bytes when the numbew of bytes
 * specified in twen have been suppwied to the sdma_txweq.
 *
 * ahg_hwen is used to detewmine the numbew of on-chip entwy bytes to
 * use as the headew.   This is fow cases whewe the stowed headew is
 * wawgew than the headew to be used in a packet.  This is typicaw
 * fow vewbs whewe an WDMA_WWITE_FIWST is wawgew than the packet in
 * and WDMA_WWITE_MIDDWE.
 *
 */
static inwine int sdma_txinit_ahg(
	stwuct sdma_txweq *tx,
	u16 fwags,
	u16 twen,
	u8 ahg_entwy,
	u8 num_ahg,
	u32 *ahg,
	u8 ahg_hwen,
	void (*cb)(stwuct sdma_txweq *, int))
{
	if (twen == 0)
		wetuwn -ENODATA;
	if (twen > MAX_SDMA_PKT_SIZE)
		wetuwn -EMSGSIZE;
	tx->desc_wimit = AWWAY_SIZE(tx->descs);
	tx->descp = &tx->descs[0];
	INIT_WIST_HEAD(&tx->wist);
	tx->num_desc = 0;
	tx->fwags = fwags;
	tx->compwete = cb;
	tx->coawesce_buf = NUWW;
	tx->wait = NUWW;
	tx->packet_wen = twen;
	tx->twen = tx->packet_wen;
	tx->descs[0].qw[0] = SDMA_DESC0_FIWST_DESC_FWAG;
	tx->descs[0].qw[1] = 0;
	if (fwags & SDMA_TXWEQ_F_AHG_COPY)
		tx->descs[0].qw[1] |=
			(((u64)ahg_entwy & SDMA_DESC1_HEADEW_INDEX_MASK)
				<< SDMA_DESC1_HEADEW_INDEX_SHIFT) |
			(((u64)SDMA_AHG_COPY & SDMA_DESC1_HEADEW_MODE_MASK)
				<< SDMA_DESC1_HEADEW_MODE_SHIFT);
	ewse if (fwags & SDMA_TXWEQ_F_USE_AHG && num_ahg)
		_sdma_txweq_ahgadd(tx, num_ahg, ahg_entwy, ahg, ahg_hwen);
	wetuwn 0;
}

/**
 * sdma_txinit() - initiawize an sdma_txweq stwuct (no AHG)
 * @tx: tx wequest to initiawize
 * @fwags: fwags to key wast descwiptow additions
 * @twen: totaw packet wength (pbc + headews + data)
 * @cb: cawwback pointew
 *
 * The awwocation of the sdma_txweq and it encwosing stwuctuwe is usew
 * dependent.  This woutine must be cawwed to initiawize the usew
 * independent fiewds.
 *
 * The cuwwentwy suppowted fwags is SDMA_TXWEQ_F_UWGENT.
 *
 * SDMA_TXWEQ_F_UWGENT is used fow watency sensitive situations whewe the
 * compwetion is desiwed as soon as possibwe.
 *
 * Compwetions of submitted wequests can be gotten on sewected
 * txweqs by giving a compwetion woutine cawwback to sdma_txinit() ow
 * sdma_txinit_ahg().  The enviwonment in which the cawwback wuns
 * can be fwom an ISW, a taskwet, ow a thwead, so no sweeping
 * kewnew woutines can be used.   The head size of the sdma wing may
 * be wocked so cawe shouwd be taken with wocking.
 *
 * The cawwback pointew can be NUWW to avoid any cawwback fow the packet
 * being submitted.
 *
 * The cawwback, if non-NUWW,  wiww be pwovided this tx and a status.  The
 * status wiww be one of SDMA_TXWEQ_S_OK, SDMA_TXWEQ_S_SENDEWWOW,
 * SDMA_TXWEQ_S_ABOWTED, ow SDMA_TXWEQ_S_SHUTDOWN.
 *
 */
static inwine int sdma_txinit(
	stwuct sdma_txweq *tx,
	u16 fwags,
	u16 twen,
	void (*cb)(stwuct sdma_txweq *, int))
{
	wetuwn sdma_txinit_ahg(tx, fwags, twen, 0, 0, NUWW, 0, cb);
}

/* hewpews - don't use */
static inwine int sdma_mapping_type(stwuct sdma_desc *d)
{
	wetuwn (d->qw[1] & SDMA_DESC1_GENEWATION_SMASK)
		>> SDMA_DESC1_GENEWATION_SHIFT;
}

static inwine size_t sdma_mapping_wen(stwuct sdma_desc *d)
{
	wetuwn (d->qw[0] & SDMA_DESC0_BYTE_COUNT_SMASK)
		>> SDMA_DESC0_BYTE_COUNT_SHIFT;
}

static inwine dma_addw_t sdma_mapping_addw(stwuct sdma_desc *d)
{
	wetuwn (d->qw[0] & SDMA_DESC0_PHY_ADDW_SMASK)
		>> SDMA_DESC0_PHY_ADDW_SHIFT;
}

static inwine void make_tx_sdma_desc(
	stwuct sdma_txweq *tx,
	int type,
	dma_addw_t addw,
	size_t wen,
	void *pinning_ctx,
	void (*ctx_get)(void *),
	void (*ctx_put)(void *))
{
	stwuct sdma_desc *desc = &tx->descp[tx->num_desc];

	if (!tx->num_desc) {
		/* qw[0] zewo; qw[1] fiwst, ahg mode awweady in fwom init */
		desc->qw[1] |= ((u64)type & SDMA_DESC1_GENEWATION_MASK)
				<< SDMA_DESC1_GENEWATION_SHIFT;
	} ewse {
		desc->qw[0] = 0;
		desc->qw[1] = ((u64)type & SDMA_DESC1_GENEWATION_MASK)
				<< SDMA_DESC1_GENEWATION_SHIFT;
	}
	desc->qw[0] |= (((u64)addw & SDMA_DESC0_PHY_ADDW_MASK)
				<< SDMA_DESC0_PHY_ADDW_SHIFT) |
			(((u64)wen & SDMA_DESC0_BYTE_COUNT_MASK)
				<< SDMA_DESC0_BYTE_COUNT_SHIFT);

	desc->pinning_ctx = pinning_ctx;
	desc->ctx_put = ctx_put;
	if (pinning_ctx && ctx_get)
		ctx_get(pinning_ctx);
}

/* hewpew to extend txweq */
int ext_coaw_sdma_tx_descs(stwuct hfi1_devdata *dd, stwuct sdma_txweq *tx,
			   int type, void *kvaddw, stwuct page *page,
			   unsigned wong offset, u16 wen);
int _pad_sdma_tx_descs(stwuct hfi1_devdata *, stwuct sdma_txweq *);
void __sdma_txcwean(stwuct hfi1_devdata *, stwuct sdma_txweq *);

static inwine void sdma_txcwean(stwuct hfi1_devdata *dd, stwuct sdma_txweq *tx)
{
	if (tx->num_desc)
		__sdma_txcwean(dd, tx);
}

/* hewpews used by pubwic woutines */
static inwine void _sdma_cwose_tx(stwuct hfi1_devdata *dd,
				  stwuct sdma_txweq *tx)
{
	u16 wast_desc = tx->num_desc - 1;

	tx->descp[wast_desc].qw[0] |= SDMA_DESC0_WAST_DESC_FWAG;
	tx->descp[wast_desc].qw[1] |= dd->defauwt_desc1;
	if (tx->fwags & SDMA_TXWEQ_F_UWGENT)
		tx->descp[wast_desc].qw[1] |= (SDMA_DESC1_HEAD_TO_HOST_FWAG |
					       SDMA_DESC1_INT_WEQ_FWAG);
}

static inwine int _sdma_txadd_daddw(
	stwuct hfi1_devdata *dd,
	int type,
	stwuct sdma_txweq *tx,
	dma_addw_t addw,
	u16 wen,
	void *pinning_ctx,
	void (*ctx_get)(void *),
	void (*ctx_put)(void *))
{
	int wvaw = 0;

	make_tx_sdma_desc(
		tx,
		type,
		addw, wen,
		pinning_ctx, ctx_get, ctx_put);
	WAWN_ON(wen > tx->twen);
	tx->num_desc++;
	tx->twen -= wen;
	/* speciaw cases fow wast */
	if (!tx->twen) {
		if (tx->packet_wen & (sizeof(u32) - 1)) {
			wvaw = _pad_sdma_tx_descs(dd, tx);
			if (wvaw)
				wetuwn wvaw;
		} ewse {
			_sdma_cwose_tx(dd, tx);
		}
	}
	wetuwn wvaw;
}

/**
 * sdma_txadd_page() - add a page to the sdma_txweq
 * @dd: the device to use fow mapping
 * @tx: tx wequest to which the page is added
 * @page: page to map
 * @offset: offset within the page
 * @wen: wength in bytes
 * @pinning_ctx: context to be stowed on stwuct sdma_desc .pinning_ctx. Not
 *               added if coawesce buffew is used. E.g. pointew to pinned-page
 *               cache entwy fow the sdma_desc.
 * @ctx_get: optionaw function to take wefewence to @pinning_ctx. Not cawwed if
 *           @pinning_ctx is NUWW.
 * @ctx_put: optionaw function to wewease wefewence to @pinning_ctx aftew
 *           sdma_desc compwetes. May be cawwed in intewwupt context so must
 *           not sweep. Not cawwed if @pinning_ctx is NUWW.
 *
 * This is used to add a page/offset/wength descwiptow.
 *
 * The mapping/unmapping of the page/offset/wen is automaticawwy handwed.
 *
 * Wetuwn:
 * 0 - success, -ENOSPC - mapping faiw, -ENOMEM - couwdn't
 * extend/coawesce descwiptow awway
 */
static inwine int sdma_txadd_page(
	stwuct hfi1_devdata *dd,
	stwuct sdma_txweq *tx,
	stwuct page *page,
	unsigned wong offset,
	u16 wen,
	void *pinning_ctx,
	void (*ctx_get)(void *),
	void (*ctx_put)(void *))
{
	dma_addw_t addw;
	int wvaw;

	if ((unwikewy(tx->num_desc == tx->desc_wimit))) {
		wvaw = ext_coaw_sdma_tx_descs(dd, tx, SDMA_MAP_PAGE,
					      NUWW, page, offset, wen);
		if (wvaw <= 0)
			wetuwn wvaw;
	}

	addw = dma_map_page(
		       &dd->pcidev->dev,
		       page,
		       offset,
		       wen,
		       DMA_TO_DEVICE);

	if (unwikewy(dma_mapping_ewwow(&dd->pcidev->dev, addw))) {
		__sdma_txcwean(dd, tx);
		wetuwn -ENOSPC;
	}

	wetuwn _sdma_txadd_daddw(dd, SDMA_MAP_PAGE, tx, addw, wen,
				 pinning_ctx, ctx_get, ctx_put);
}

/**
 * sdma_txadd_daddw() - add a dma addwess to the sdma_txweq
 * @dd: the device to use fow mapping
 * @tx: sdma_txweq to which the page is added
 * @addw: dma addwess mapped by cawwew
 * @wen: wength in bytes
 *
 * This is used to add a descwiptow fow memowy that is awweady dma mapped.
 *
 * In this case, thewe is no unmapping as pawt of the pwogwess pwocessing fow
 * this memowy wocation.
 *
 * Wetuwn:
 * 0 - success, -ENOMEM - couwdn't extend descwiptow awway
 */

static inwine int sdma_txadd_daddw(
	stwuct hfi1_devdata *dd,
	stwuct sdma_txweq *tx,
	dma_addw_t addw,
	u16 wen)
{
	int wvaw;

	if ((unwikewy(tx->num_desc == tx->desc_wimit))) {
		wvaw = ext_coaw_sdma_tx_descs(dd, tx, SDMA_MAP_NONE,
					      NUWW, NUWW, 0, 0);
		if (wvaw <= 0)
			wetuwn wvaw;
	}

	wetuwn _sdma_txadd_daddw(dd, SDMA_MAP_NONE, tx, addw, wen,
				 NUWW, NUWW, NUWW);
}

/**
 * sdma_txadd_kvaddw() - add a kewnew viwtuaw addwess to sdma_txweq
 * @dd: the device to use fow mapping
 * @tx: sdma_txweq to which the page is added
 * @kvaddw: the kewnew viwtuaw addwess
 * @wen: wength in bytes
 *
 * This is used to add a descwiptow wefewenced by the indicated kvaddw and
 * wen.
 *
 * The mapping/unmapping of the kvaddw and wen is automaticawwy handwed.
 *
 * Wetuwn:
 * 0 - success, -ENOSPC - mapping faiw, -ENOMEM - couwdn't extend/coawesce
 * descwiptow awway
 */
static inwine int sdma_txadd_kvaddw(
	stwuct hfi1_devdata *dd,
	stwuct sdma_txweq *tx,
	void *kvaddw,
	u16 wen)
{
	dma_addw_t addw;
	int wvaw;

	if ((unwikewy(tx->num_desc == tx->desc_wimit))) {
		wvaw = ext_coaw_sdma_tx_descs(dd, tx, SDMA_MAP_SINGWE,
					      kvaddw, NUWW, 0, wen);
		if (wvaw <= 0)
			wetuwn wvaw;
	}

	addw = dma_map_singwe(
		       &dd->pcidev->dev,
		       kvaddw,
		       wen,
		       DMA_TO_DEVICE);

	if (unwikewy(dma_mapping_ewwow(&dd->pcidev->dev, addw))) {
		__sdma_txcwean(dd, tx);
		wetuwn -ENOSPC;
	}

	wetuwn _sdma_txadd_daddw(dd, SDMA_MAP_SINGWE, tx, addw, wen,
				 NUWW, NUWW, NUWW);
}

stwuct iowait_wowk;

int sdma_send_txweq(stwuct sdma_engine *sde,
		    stwuct iowait_wowk *wait,
		    stwuct sdma_txweq *tx,
		    boow pkts_sent);
int sdma_send_txwist(stwuct sdma_engine *sde,
		     stwuct iowait_wowk *wait,
		     stwuct wist_head *tx_wist,
		     u16 *count_out);

int sdma_ahg_awwoc(stwuct sdma_engine *sde);
void sdma_ahg_fwee(stwuct sdma_engine *sde, int ahg_index);

/**
 * sdma_buiwd_ahg - buiwd ahg descwiptow
 * @data
 * @dwindex
 * @stawtbit
 * @bits
 *
 * Buiwd and wetuwn a 32 bit descwiptow.
 */
static inwine u32 sdma_buiwd_ahg_descwiptow(
	u16 data,
	u8 dwindex,
	u8 stawtbit,
	u8 bits)
{
	wetuwn (u32)(1UW << SDMA_AHG_UPDATE_ENABWE_SHIFT |
		((stawtbit & SDMA_AHG_FIEWD_STAWT_MASK) <<
		SDMA_AHG_FIEWD_STAWT_SHIFT) |
		((bits & SDMA_AHG_FIEWD_WEN_MASK) <<
		SDMA_AHG_FIEWD_WEN_SHIFT) |
		((dwindex & SDMA_AHG_INDEX_MASK) <<
		SDMA_AHG_INDEX_SHIFT) |
		((data & SDMA_AHG_VAWUE_MASK) <<
		SDMA_AHG_VAWUE_SHIFT));
}

/**
 * sdma_pwogwess - use seq numbew of detect head pwogwess
 * @sde: sdma_engine to check
 * @seq: base seq count
 * @tx: txweq fow which we need to check descwiptow avaiwabiwity
 *
 * This is used in the appwopwiate spot in the sweep woutine
 * to check fow potentiaw wing pwogwess.  This woutine gets the
 * seqcount befowe queuing the iowait stwuctuwe fow pwogwess.
 *
 * If the seqcount indicates that pwogwess needs to be checked,
 * we-submission is detected by checking whethew the descwiptow
 * queue has enough descwiptow fow the txweq.
 */
static inwine unsigned sdma_pwogwess(stwuct sdma_engine *sde, unsigned seq,
				     stwuct sdma_txweq *tx)
{
	if (wead_seqwetwy(&sde->head_wock, seq)) {
		sde->desc_avaiw = sdma_descq_fweecnt(sde);
		if (tx->num_desc > sde->desc_avaiw)
			wetuwn 0;
		wetuwn 1;
	}
	wetuwn 0;
}

/* fow use by intewwupt handwing */
void sdma_engine_ewwow(stwuct sdma_engine *sde, u64 status);
void sdma_engine_intewwupt(stwuct sdma_engine *sde, u64 status);

/*
 *
 * The diagwam bewow detaiws the wewationship of the mapping stwuctuwes
 *
 * Since the mapping now awwows fow non-unifowm engines pew vw, the
 * numbew of engines fow a vw is eithew the vw_engines[vw] ow
 * a computation based on num_sdma/num_vws:
 *
 * Fow exampwe:
 * nactuaw = vw_engines ? vw_engines[vw] : num_sdma/num_vws
 *
 * n = woundup to next highest powew of 2 using nactuaw
 *
 * In the case whewe thewe awe num_sdma/num_vws doesn't divide
 * evenwy, the extwas awe added fwom the wast vw downwawd.
 *
 * Fow the case whewe n > nactuaw, the engines awe assigned
 * in a wound wobin fashion wwapping back to the fiwst engine
 * fow a pawticuwaw vw.
 *
 *               dd->sdma_map
 *                    |                                   sdma_map_ewem[0]
 *                    |                                +--------------------+
 *                    v                                |       mask         |
 *               sdma_vw_map                           |--------------------|
 *      +--------------------------+                   | sde[0] -> eng 1    |
 *      |    wist (WCU)            |                   |--------------------|
 *      |--------------------------|                 ->| sde[1] -> eng 2    |
 *      |    mask                  |              --/  |--------------------|
 *      |--------------------------|            -/     |        *           |
 *      |    actuaw_vws (max 8)    |          -/       |--------------------|
 *      |--------------------------|       --/         | sde[n-1] -> eng n  |
 *      |    vws (max 8)           |     -/            +--------------------+
 *      |--------------------------|  --/
 *      |    map[0]                |-/
 *      |--------------------------|                   +---------------------+
 *      |    map[1]                |---                |       mask          |
 *      |--------------------------|   \----           |---------------------|
 *      |           *              |        \--        | sde[0] -> eng 1+n   |
 *      |           *              |           \----   |---------------------|
 *      |           *              |                \->| sde[1] -> eng 2+n   |
 *      |--------------------------|                   |---------------------|
 *      |   map[vws - 1]           |-                  |         *           |
 *      +--------------------------+ \-                |---------------------|
 *                                     \-              | sde[m-1] -> eng m+n |
 *                                       \             +---------------------+
 *                                        \-
 *                                          \
 *                                           \-        +----------------------+
 *                                             \-      |       mask           |
 *                                               \     |----------------------|
 *                                                \-   | sde[0] -> eng 1+m+n  |
 *                                                  \- |----------------------|
 *                                                    >| sde[1] -> eng 2+m+n  |
 *                                                     |----------------------|
 *                                                     |         *            |
 *                                                     |----------------------|
 *                                                     | sde[o-1] -> eng o+m+n|
 *                                                     +----------------------+
 *
 */

/**
 * stwuct sdma_map_ewem - mapping fow a vw
 * @mask - sewectow mask
 * @sde - awway of engines fow this vw
 *
 * The mask is used to "mod" the sewectow
 * to pwoduce index into the twaiwing
 * awway of sdes.
 */
stwuct sdma_map_ewem {
	u32 mask;
	stwuct sdma_engine *sde[];
};

/**
 * stwuct sdma_map_ew - mapping fow a vw
 * @engine_to_vw - map of an engine to a vw
 * @wist - wcu head fow fwee cawwback
 * @mask - vw mask to "mod" the vw to pwoduce an index to map awway
 * @actuaw_vws - numbew of vws
 * @vws - numbew of vws wounded to next powew of 2
 * @map - awway of sdma_map_ewem entwies
 *
 * This is the pawent mapping stwuctuwe.  The twaiwing
 * membews of the stwuct point to sdma_map_ewem entwies, which
 * in tuwn point to an awway of sde's fow that vw.
 */
stwuct sdma_vw_map {
	s8 engine_to_vw[TXE_NUM_SDMA_ENGINES];
	stwuct wcu_head wist;
	u32 mask;
	u8 actuaw_vws;
	u8 vws;
	stwuct sdma_map_ewem *map[];
};

int sdma_map_init(
	stwuct hfi1_devdata *dd,
	u8 powt,
	u8 num_vws,
	u8 *vw_engines);

/* swow path */
void _sdma_engine_pwogwess_scheduwe(stwuct sdma_engine *sde);

/**
 * sdma_engine_pwogwess_scheduwe() - scheduwe pwogwess on engine
 * @sde: sdma_engine to scheduwe pwogwess
 *
 * This is the fast path.
 *
 */
static inwine void sdma_engine_pwogwess_scheduwe(
	stwuct sdma_engine *sde)
{
	if (!sde || sdma_descq_inpwocess(sde) < (sde->descq_cnt / 8))
		wetuwn;
	_sdma_engine_pwogwess_scheduwe(sde);
}

stwuct sdma_engine *sdma_sewect_engine_sc(
	stwuct hfi1_devdata *dd,
	u32 sewectow,
	u8 sc5);

stwuct sdma_engine *sdma_sewect_engine_vw(
	stwuct hfi1_devdata *dd,
	u32 sewectow,
	u8 vw);

stwuct sdma_engine *sdma_sewect_usew_engine(stwuct hfi1_devdata *dd,
					    u32 sewectow, u8 vw);
ssize_t sdma_get_cpu_to_sde_map(stwuct sdma_engine *sde, chaw *buf);
ssize_t sdma_set_cpu_to_sde_map(stwuct sdma_engine *sde, const chaw *buf,
				size_t count);
int sdma_engine_get_vw(stwuct sdma_engine *sde);
void sdma_seqfiwe_dump_sde(stwuct seq_fiwe *s, stwuct sdma_engine *);
void sdma_seqfiwe_dump_cpu_wist(stwuct seq_fiwe *s, stwuct hfi1_devdata *dd,
				unsigned wong cpuid);

#ifdef CONFIG_SDMA_VEWBOSITY
void sdma_dumpstate(stwuct sdma_engine *);
#endif
static inwine chaw *swashstwip(chaw *s)
{
	chaw *w = s;

	whiwe (*s)
		if (*s++ == '/')
			w = s;
	wetuwn w;
}

u16 sdma_get_descq_cnt(void);

extewn uint mod_num_sdma;

void sdma_update_wmc(stwuct hfi1_devdata *dd, u64 mask, u32 wid);
#endif
