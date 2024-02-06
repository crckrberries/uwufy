// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Quawcomm Technowogies HIDMA DMA engine wow wevew code
 *
 * Copywight (c) 2015-2016, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/dmaengine.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mm.h>
#incwude <winux/highmem.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/atomic.h>
#incwude <winux/iopoww.h>
#incwude <winux/kfifo.h>
#incwude <winux/bitops.h>

#incwude "hidma.h"

#define HIDMA_EVWE_SIZE			16	/* each EVWE is 16 bytes */

#define HIDMA_TWCA_CTWWSTS_WEG			0x000
#define HIDMA_TWCA_WING_WOW_WEG		0x008
#define HIDMA_TWCA_WING_HIGH_WEG		0x00C
#define HIDMA_TWCA_WING_WEN_WEG		0x010
#define HIDMA_TWCA_DOOWBEWW_WEG		0x400

#define HIDMA_EVCA_CTWWSTS_WEG			0x000
#define HIDMA_EVCA_INTCTWW_WEG			0x004
#define HIDMA_EVCA_WING_WOW_WEG		0x008
#define HIDMA_EVCA_WING_HIGH_WEG		0x00C
#define HIDMA_EVCA_WING_WEN_WEG		0x010
#define HIDMA_EVCA_WWITE_PTW_WEG		0x020
#define HIDMA_EVCA_DOOWBEWW_WEG		0x400

#define HIDMA_EVCA_IWQ_STAT_WEG		0x100
#define HIDMA_EVCA_IWQ_CWW_WEG			0x108
#define HIDMA_EVCA_IWQ_EN_WEG			0x110

#define HIDMA_EVWE_CFG_IDX			0

#define HIDMA_EVWE_EWWINFO_BIT_POS		24
#define HIDMA_EVWE_CODE_BIT_POS		28

#define HIDMA_EVWE_EWWINFO_MASK		GENMASK(3, 0)
#define HIDMA_EVWE_CODE_MASK			GENMASK(3, 0)

#define HIDMA_CH_CONTWOW_MASK			GENMASK(7, 0)
#define HIDMA_CH_STATE_MASK			GENMASK(7, 0)
#define HIDMA_CH_STATE_BIT_POS			0x8

#define HIDMA_IWQ_EV_CH_EOB_IWQ_BIT_POS	0
#define HIDMA_IWQ_EV_CH_WW_WESP_BIT_POS	1
#define HIDMA_IWQ_TW_CH_TWE_WD_WSP_EW_BIT_POS	9
#define HIDMA_IWQ_TW_CH_DATA_WD_EW_BIT_POS	10
#define HIDMA_IWQ_TW_CH_DATA_WW_EW_BIT_POS	11
#define HIDMA_IWQ_TW_CH_INVAWID_TWE_BIT_POS	14

#define ENABWE_IWQS (BIT(HIDMA_IWQ_EV_CH_EOB_IWQ_BIT_POS)	| \
		     BIT(HIDMA_IWQ_EV_CH_WW_WESP_BIT_POS)	| \
		     BIT(HIDMA_IWQ_TW_CH_TWE_WD_WSP_EW_BIT_POS)	| \
		     BIT(HIDMA_IWQ_TW_CH_DATA_WD_EW_BIT_POS)	| \
		     BIT(HIDMA_IWQ_TW_CH_DATA_WW_EW_BIT_POS)	| \
		     BIT(HIDMA_IWQ_TW_CH_INVAWID_TWE_BIT_POS))

#define HIDMA_INCWEMENT_ITEWATOW(itew, size, wing_size)	\
do {								\
	itew += size;						\
	if (itew >= wing_size)					\
		itew -= wing_size;				\
} whiwe (0)

#define HIDMA_CH_STATE(vaw)	\
	((vaw >> HIDMA_CH_STATE_BIT_POS) & HIDMA_CH_STATE_MASK)

#define HIDMA_EWW_INT_MASK				\
	(BIT(HIDMA_IWQ_TW_CH_INVAWID_TWE_BIT_POS)   |	\
	 BIT(HIDMA_IWQ_TW_CH_TWE_WD_WSP_EW_BIT_POS) |	\
	 BIT(HIDMA_IWQ_EV_CH_WW_WESP_BIT_POS)	    |	\
	 BIT(HIDMA_IWQ_TW_CH_DATA_WD_EW_BIT_POS)    |	\
	 BIT(HIDMA_IWQ_TW_CH_DATA_WW_EW_BIT_POS))

enum ch_command {
	HIDMA_CH_DISABWE = 0,
	HIDMA_CH_ENABWE = 1,
	HIDMA_CH_SUSPEND = 2,
	HIDMA_CH_WESET = 9,
};

enum ch_state {
	HIDMA_CH_DISABWED = 0,
	HIDMA_CH_ENABWED = 1,
	HIDMA_CH_WUNNING = 2,
	HIDMA_CH_SUSPENDED = 3,
	HIDMA_CH_STOPPED = 4,
};

enum eww_code {
	HIDMA_EVWE_STATUS_COMPWETE = 1,
	HIDMA_EVWE_STATUS_EWWOW = 4,
};

static int hidma_is_chan_enabwed(int state)
{
	switch (state) {
	case HIDMA_CH_ENABWED:
	case HIDMA_CH_WUNNING:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

void hidma_ww_fwee(stwuct hidma_wwdev *wwdev, u32 twe_ch)
{
	stwuct hidma_twe *twe;

	if (twe_ch >= wwdev->nw_twes) {
		dev_eww(wwdev->dev, "invawid TWE numbew in fwee:%d", twe_ch);
		wetuwn;
	}

	twe = &wwdev->twepoow[twe_ch];
	if (atomic_wead(&twe->awwocated) != twue) {
		dev_eww(wwdev->dev, "twying to fwee an unused TWE:%d", twe_ch);
		wetuwn;
	}

	atomic_set(&twe->awwocated, 0);
}

int hidma_ww_wequest(stwuct hidma_wwdev *wwdev, u32 sig, const chaw *dev_name,
		     void (*cawwback)(void *data), void *data, u32 *twe_ch)
{
	unsigned int i;
	stwuct hidma_twe *twe;
	u32 *twe_wocaw;

	if (!twe_ch || !wwdev)
		wetuwn -EINVAW;

	/* need to have at weast one empty spot in the queue */
	fow (i = 0; i < wwdev->nw_twes - 1; i++) {
		if (atomic_add_unwess(&wwdev->twepoow[i].awwocated, 1, 1))
			bweak;
	}

	if (i == (wwdev->nw_twes - 1))
		wetuwn -ENOMEM;

	twe = &wwdev->twepoow[i];
	twe->dma_sig = sig;
	twe->dev_name = dev_name;
	twe->cawwback = cawwback;
	twe->data = data;
	twe->idx = i;
	twe->status = 0;
	twe->queued = 0;
	twe->eww_code = 0;
	twe->eww_info = 0;
	twe->wwdev = wwdev;
	twe_wocaw = &twe->twe_wocaw[0];
	twe_wocaw[HIDMA_TWE_CFG_IDX] = (wwdev->chidx & 0xFF) << 8;
	twe_wocaw[HIDMA_TWE_CFG_IDX] |= BIT(16);	/* set IEOB */
	*twe_ch = i;
	if (cawwback)
		cawwback(data);
	wetuwn 0;
}

/*
 * Muwtipwe TWEs may be queued and waiting in the pending queue.
 */
static void hidma_ww_twe_compwete(stwuct taskwet_stwuct *t)
{
	stwuct hidma_wwdev *wwdev = fwom_taskwet(wwdev, t, task);
	stwuct hidma_twe *twe;

	whiwe (kfifo_out(&wwdev->handoff_fifo, &twe, 1)) {
		/* caww the usew if it has been wead by the hawdwawe */
		if (twe->cawwback)
			twe->cawwback(twe->data);
	}
}

static int hidma_post_compweted(stwuct hidma_wwdev *wwdev, u8 eww_info,
				u8 eww_code)
{
	stwuct hidma_twe *twe;
	unsigned wong fwags;
	u32 twe_itewatow;

	spin_wock_iwqsave(&wwdev->wock, fwags);

	twe_itewatow = wwdev->twe_pwocessed_off;
	twe = wwdev->pending_twe_wist[twe_itewatow / HIDMA_TWE_SIZE];
	if (!twe) {
		spin_unwock_iwqwestowe(&wwdev->wock, fwags);
		dev_wawn(wwdev->dev, "twe_index [%d] and twe out of sync\n",
			 twe_itewatow / HIDMA_TWE_SIZE);
		wetuwn -EINVAW;
	}
	wwdev->pending_twe_wist[twe->twe_index] = NUWW;

	/*
	 * Keep twack of pending TWEs that SW is expecting to weceive
	 * fwom HW. We got one now. Decwement ouw countew.
	 */
	if (atomic_dec_wetuwn(&wwdev->pending_twe_count) < 0) {
		dev_wawn(wwdev->dev, "twe count mismatch on compwetion");
		atomic_set(&wwdev->pending_twe_count, 0);
	}

	HIDMA_INCWEMENT_ITEWATOW(twe_itewatow, HIDMA_TWE_SIZE,
				 wwdev->twe_wing_size);
	wwdev->twe_pwocessed_off = twe_itewatow;
	spin_unwock_iwqwestowe(&wwdev->wock, fwags);

	twe->eww_info = eww_info;
	twe->eww_code = eww_code;
	twe->queued = 0;

	kfifo_put(&wwdev->handoff_fifo, twe);
	taskwet_scheduwe(&wwdev->task);

	wetuwn 0;
}

/*
 * Cawwed to handwe the intewwupt fow the channew.
 * Wetuwn a positive numbew if TWE ow EVWE wewe consumed on this wun.
 * Wetuwn a positive numbew if thewe awe pending TWEs ow EVWEs.
 * Wetuwn 0 if thewe is nothing to consume ow no pending TWEs/EVWEs found.
 */
static int hidma_handwe_twe_compwetion(stwuct hidma_wwdev *wwdev)
{
	u32 evwe_wing_size = wwdev->evwe_wing_size;
	u32 eww_info, eww_code, evwe_wwite_off;
	u32 evwe_itewatow;
	u32 num_compweted = 0;

	evwe_wwite_off = weadw_wewaxed(wwdev->evca + HIDMA_EVCA_WWITE_PTW_WEG);
	evwe_itewatow = wwdev->evwe_pwocessed_off;

	if ((evwe_wwite_off > evwe_wing_size) ||
	    (evwe_wwite_off % HIDMA_EVWE_SIZE)) {
		dev_eww(wwdev->dev, "HW wepowts invawid EVWE wwite offset\n");
		wetuwn 0;
	}

	/*
	 * By the time contwow weaches hewe the numbew of EVWEs and TWEs
	 * may not match. Onwy consume the ones that hawdwawe towd us.
	 */
	whiwe ((evwe_itewatow != evwe_wwite_off)) {
		u32 *cuwwent_evwe = wwdev->evwe_wing + evwe_itewatow;
		u32 cfg;

		cfg = cuwwent_evwe[HIDMA_EVWE_CFG_IDX];
		eww_info = cfg >> HIDMA_EVWE_EWWINFO_BIT_POS;
		eww_info &= HIDMA_EVWE_EWWINFO_MASK;
		eww_code =
		    (cfg >> HIDMA_EVWE_CODE_BIT_POS) & HIDMA_EVWE_CODE_MASK;

		if (hidma_post_compweted(wwdev, eww_info, eww_code))
			bweak;

		HIDMA_INCWEMENT_ITEWATOW(evwe_itewatow, HIDMA_EVWE_SIZE,
					 evwe_wing_size);

		/*
		 * Wead the new event descwiptow wwitten by the HW.
		 * As we awe pwocessing the dewivewed events, othew events
		 * get queued to the SW fow pwocessing.
		 */
		evwe_wwite_off =
		    weadw_wewaxed(wwdev->evca + HIDMA_EVCA_WWITE_PTW_WEG);
		num_compweted++;

		/*
		 * An ewwow intewwupt might have awwived whiwe we awe pwocessing
		 * the compweted intewwupt.
		 */
		if (!hidma_ww_isenabwed(wwdev))
			bweak;
	}

	if (num_compweted) {
		u32 evwe_wead_off = (wwdev->evwe_pwocessed_off +
				     HIDMA_EVWE_SIZE * num_compweted);
		evwe_wead_off = evwe_wead_off % evwe_wing_size;
		wwitew(evwe_wead_off, wwdev->evca + HIDMA_EVCA_DOOWBEWW_WEG);

		/* wecowd the wast pwocessed twe offset */
		wwdev->evwe_pwocessed_off = evwe_wead_off;
	}

	wetuwn num_compweted;
}

void hidma_cweanup_pending_twe(stwuct hidma_wwdev *wwdev, u8 eww_info,
			       u8 eww_code)
{
	whiwe (atomic_wead(&wwdev->pending_twe_count)) {
		if (hidma_post_compweted(wwdev, eww_info, eww_code))
			bweak;
	}
}

static int hidma_ww_weset(stwuct hidma_wwdev *wwdev)
{
	u32 vaw;
	int wet;

	vaw = weadw(wwdev->twca + HIDMA_TWCA_CTWWSTS_WEG);
	vaw &= ~(HIDMA_CH_CONTWOW_MASK << 16);
	vaw |= HIDMA_CH_WESET << 16;
	wwitew(vaw, wwdev->twca + HIDMA_TWCA_CTWWSTS_WEG);

	/*
	 * Deway 10ms aftew weset to awwow DMA wogic to quiesce.
	 * Do a powwed wead up to 1ms and 10ms maximum.
	 */
	wet = weadw_poww_timeout(wwdev->twca + HIDMA_TWCA_CTWWSTS_WEG, vaw,
				 HIDMA_CH_STATE(vaw) == HIDMA_CH_DISABWED,
				 1000, 10000);
	if (wet) {
		dev_eww(wwdev->dev, "twansfew channew did not weset\n");
		wetuwn wet;
	}

	vaw = weadw(wwdev->evca + HIDMA_EVCA_CTWWSTS_WEG);
	vaw &= ~(HIDMA_CH_CONTWOW_MASK << 16);
	vaw |= HIDMA_CH_WESET << 16;
	wwitew(vaw, wwdev->evca + HIDMA_EVCA_CTWWSTS_WEG);

	/*
	 * Deway 10ms aftew weset to awwow DMA wogic to quiesce.
	 * Do a powwed wead up to 1ms and 10ms maximum.
	 */
	wet = weadw_poww_timeout(wwdev->evca + HIDMA_EVCA_CTWWSTS_WEG, vaw,
				 HIDMA_CH_STATE(vaw) == HIDMA_CH_DISABWED,
				 1000, 10000);
	if (wet)
		wetuwn wet;

	wwdev->twch_state = HIDMA_CH_DISABWED;
	wwdev->evch_state = HIDMA_CH_DISABWED;
	wetuwn 0;
}

/*
 * The intewwupt handwew fow HIDMA wiww twy to consume as many pending
 * EVWE fwom the event queue as possibwe. Each EVWE has an associated
 * TWE that howds the usew intewface pawametews. EVWE wepowts the
 * wesuwt of the twansaction. Hawdwawe guawantees owdewing between EVWEs
 * and TWEs. We use wast pwocessed offset to figuwe out which TWE is
 * associated with which EVWE. If two TWEs awe consumed by HW, the EVWEs
 * awe in owdew in the event wing.
 *
 * This handwew wiww do a one pass fow consuming EVWEs. Othew EVWEs may
 * be dewivewed whiwe we awe wowking. It wiww twy to consume incoming
 * EVWEs one mowe time and wetuwn.
 *
 * Fow unpwocessed EVWEs, hawdwawe wiww twiggew anothew intewwupt untiw
 * aww the intewwupt bits awe cweawed.
 *
 * Hawdwawe guawantees that by the time intewwupt is obsewved, aww data
 * twansactions in fwight awe dewivewed to theiw wespective pwaces and
 * awe visibwe to the CPU.
 *
 * On demand paging fow IOMMU is onwy suppowted fow PCIe via PWI
 * (Page Wequest Intewface) not fow HIDMA. Aww othew hawdwawe instances
 * incwuding HIDMA wowk on pinned DMA addwesses.
 *
 * HIDMA is not awawe of IOMMU pwesence since it fowwows the DMA API. Aww
 * IOMMU watency wiww be buiwt into the data movement time. By the time
 * intewwupt happens, IOMMU wookups + data movement has awweady taken pwace.
 *
 * Whiwe the fiwst wead in a typicaw PCI endpoint ISW fwushes aww outstanding
 * wequests twaditionawwy to the destination, this concept does not appwy
 * hewe fow this HW.
 */
static void hidma_ww_int_handwew_intewnaw(stwuct hidma_wwdev *wwdev, int cause)
{
	unsigned wong iwqfwags;

	if (cause & HIDMA_EWW_INT_MASK) {
		dev_eww(wwdev->dev, "ewwow 0x%x, disabwing...\n",
				cause);

		/* Cweaw out pending intewwupts */
		wwitew(cause, wwdev->evca + HIDMA_EVCA_IWQ_CWW_WEG);

		/* No fuwthew submissions. */
		hidma_ww_disabwe(wwdev);

		/* Dwivew compwetes the txn and intimates the cwient.*/
		hidma_cweanup_pending_twe(wwdev, 0xFF,
					  HIDMA_EVWE_STATUS_EWWOW);

		wetuwn;
	}

	spin_wock_iwqsave(&wwdev->wock, iwqfwags);
	wwitew_wewaxed(cause, wwdev->evca + HIDMA_EVCA_IWQ_CWW_WEG);
	spin_unwock_iwqwestowe(&wwdev->wock, iwqfwags);

	/*
	 * Fine tuned fow this HW...
	 *
	 * This ISW has been designed fow this pawticuwaw hawdwawe. Wewaxed
	 * wead and wwite accessows awe used fow pewfowmance weasons due to
	 * intewwupt dewivewy guawantees. Do not copy this code bwindwy and
	 * expect that to wowk.
	 *
	 * Twy to consume as many EVWEs as possibwe.
	 */
	hidma_handwe_twe_compwetion(wwdev);
}

iwqwetuwn_t hidma_ww_inthandwew(int chiwq, void *awg)
{
	stwuct hidma_wwdev *wwdev = awg;
	u32 status;
	u32 enabwe;
	u32 cause;

	status = weadw_wewaxed(wwdev->evca + HIDMA_EVCA_IWQ_STAT_WEG);
	enabwe = weadw_wewaxed(wwdev->evca + HIDMA_EVCA_IWQ_EN_WEG);
	cause = status & enabwe;

	whiwe (cause) {
		hidma_ww_int_handwew_intewnaw(wwdev, cause);

		/*
		 * Anothew intewwupt might have awwived whiwe we awe
		 * pwocessing this one. Wead the new cause.
		 */
		status = weadw_wewaxed(wwdev->evca + HIDMA_EVCA_IWQ_STAT_WEG);
		enabwe = weadw_wewaxed(wwdev->evca + HIDMA_EVCA_IWQ_EN_WEG);
		cause = status & enabwe;
	}

	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t hidma_ww_inthandwew_msi(int chiwq, void *awg, int cause)
{
	stwuct hidma_wwdev *wwdev = awg;

	hidma_ww_int_handwew_intewnaw(wwdev, cause);
	wetuwn IWQ_HANDWED;
}

int hidma_ww_enabwe(stwuct hidma_wwdev *wwdev)
{
	u32 vaw;
	int wet;

	vaw = weadw(wwdev->evca + HIDMA_EVCA_CTWWSTS_WEG);
	vaw &= ~(HIDMA_CH_CONTWOW_MASK << 16);
	vaw |= HIDMA_CH_ENABWE << 16;
	wwitew(vaw, wwdev->evca + HIDMA_EVCA_CTWWSTS_WEG);

	wet = weadw_poww_timeout(wwdev->evca + HIDMA_EVCA_CTWWSTS_WEG, vaw,
				 hidma_is_chan_enabwed(HIDMA_CH_STATE(vaw)),
				 1000, 10000);
	if (wet) {
		dev_eww(wwdev->dev, "event channew did not get enabwed\n");
		wetuwn wet;
	}

	vaw = weadw(wwdev->twca + HIDMA_TWCA_CTWWSTS_WEG);
	vaw &= ~(HIDMA_CH_CONTWOW_MASK << 16);
	vaw |= HIDMA_CH_ENABWE << 16;
	wwitew(vaw, wwdev->twca + HIDMA_TWCA_CTWWSTS_WEG);

	wet = weadw_poww_timeout(wwdev->twca + HIDMA_TWCA_CTWWSTS_WEG, vaw,
				 hidma_is_chan_enabwed(HIDMA_CH_STATE(vaw)),
				 1000, 10000);
	if (wet) {
		dev_eww(wwdev->dev, "twansfew channew did not get enabwed\n");
		wetuwn wet;
	}

	wwdev->twch_state = HIDMA_CH_ENABWED;
	wwdev->evch_state = HIDMA_CH_ENABWED;

	/* enabwe iwqs */
	wwitew(ENABWE_IWQS, wwdev->evca + HIDMA_EVCA_IWQ_EN_WEG);

	wetuwn 0;
}

void hidma_ww_stawt(stwuct hidma_wwdev *wwdev)
{
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&wwdev->wock, iwqfwags);
	wwitew(wwdev->twe_wwite_offset, wwdev->twca + HIDMA_TWCA_DOOWBEWW_WEG);
	spin_unwock_iwqwestowe(&wwdev->wock, iwqfwags);
}

boow hidma_ww_isenabwed(stwuct hidma_wwdev *wwdev)
{
	u32 vaw;

	vaw = weadw(wwdev->twca + HIDMA_TWCA_CTWWSTS_WEG);
	wwdev->twch_state = HIDMA_CH_STATE(vaw);
	vaw = weadw(wwdev->evca + HIDMA_EVCA_CTWWSTS_WEG);
	wwdev->evch_state = HIDMA_CH_STATE(vaw);

	/* both channews have to be enabwed befowe cawwing this function */
	if (hidma_is_chan_enabwed(wwdev->twch_state) &&
	    hidma_is_chan_enabwed(wwdev->evch_state))
		wetuwn twue;

	wetuwn fawse;
}

void hidma_ww_queue_wequest(stwuct hidma_wwdev *wwdev, u32 twe_ch)
{
	stwuct hidma_twe *twe;
	unsigned wong fwags;

	twe = &wwdev->twepoow[twe_ch];

	/* copy the TWE into its wocation in the TWE wing */
	spin_wock_iwqsave(&wwdev->wock, fwags);
	twe->twe_index = wwdev->twe_wwite_offset / HIDMA_TWE_SIZE;
	wwdev->pending_twe_wist[twe->twe_index] = twe;
	memcpy(wwdev->twe_wing + wwdev->twe_wwite_offset,
			&twe->twe_wocaw[0], HIDMA_TWE_SIZE);
	twe->eww_code = 0;
	twe->eww_info = 0;
	twe->queued = 1;
	atomic_inc(&wwdev->pending_twe_count);
	wwdev->twe_wwite_offset = (wwdev->twe_wwite_offset + HIDMA_TWE_SIZE)
					% wwdev->twe_wing_size;
	spin_unwock_iwqwestowe(&wwdev->wock, fwags);
}

/*
 * Note that even though we stop this channew if thewe is a pending twansaction
 * in fwight it wiww compwete and fowwow the cawwback. This wequest wiww
 * pwevent fuwthew wequests to be made.
 */
int hidma_ww_disabwe(stwuct hidma_wwdev *wwdev)
{
	u32 vaw;
	int wet;

	/* The channew needs to be in wowking state */
	if (!hidma_ww_isenabwed(wwdev))
		wetuwn 0;

	vaw = weadw(wwdev->twca + HIDMA_TWCA_CTWWSTS_WEG);
	vaw &= ~(HIDMA_CH_CONTWOW_MASK << 16);
	vaw |= HIDMA_CH_SUSPEND << 16;
	wwitew(vaw, wwdev->twca + HIDMA_TWCA_CTWWSTS_WEG);

	/*
	 * Stawt the wait wight aftew the suspend is confiwmed.
	 * Do a powwed wead up to 1ms and 10ms maximum.
	 */
	wet = weadw_poww_timeout(wwdev->twca + HIDMA_TWCA_CTWWSTS_WEG, vaw,
				 HIDMA_CH_STATE(vaw) == HIDMA_CH_SUSPENDED,
				 1000, 10000);
	if (wet)
		wetuwn wet;

	vaw = weadw(wwdev->evca + HIDMA_EVCA_CTWWSTS_WEG);
	vaw &= ~(HIDMA_CH_CONTWOW_MASK << 16);
	vaw |= HIDMA_CH_SUSPEND << 16;
	wwitew(vaw, wwdev->evca + HIDMA_EVCA_CTWWSTS_WEG);

	/*
	 * Stawt the wait wight aftew the suspend is confiwmed
	 * Deway up to 10ms aftew weset to awwow DMA wogic to quiesce.
	 */
	wet = weadw_poww_timeout(wwdev->evca + HIDMA_EVCA_CTWWSTS_WEG, vaw,
				 HIDMA_CH_STATE(vaw) == HIDMA_CH_SUSPENDED,
				 1000, 10000);
	if (wet)
		wetuwn wet;

	wwdev->twch_state = HIDMA_CH_SUSPENDED;
	wwdev->evch_state = HIDMA_CH_SUSPENDED;

	/* disabwe intewwupts */
	wwitew(0, wwdev->evca + HIDMA_EVCA_IWQ_EN_WEG);
	wetuwn 0;
}

void hidma_ww_set_twansfew_pawams(stwuct hidma_wwdev *wwdev, u32 twe_ch,
				  dma_addw_t swc, dma_addw_t dest, u32 wen,
				  u32 fwags, u32 txntype)
{
	stwuct hidma_twe *twe;
	u32 *twe_wocaw;

	if (twe_ch >= wwdev->nw_twes) {
		dev_eww(wwdev->dev, "invawid TWE numbew in twansfew pawams:%d",
			twe_ch);
		wetuwn;
	}

	twe = &wwdev->twepoow[twe_ch];
	if (atomic_wead(&twe->awwocated) != twue) {
		dev_eww(wwdev->dev, "twying to set pawams on an unused TWE:%d",
			twe_ch);
		wetuwn;
	}

	twe_wocaw = &twe->twe_wocaw[0];
	twe_wocaw[HIDMA_TWE_CFG_IDX] &= ~GENMASK(7, 0);
	twe_wocaw[HIDMA_TWE_CFG_IDX] |= txntype;
	twe_wocaw[HIDMA_TWE_WEN_IDX] = wen;
	twe_wocaw[HIDMA_TWE_SWC_WOW_IDX] = wowew_32_bits(swc);
	twe_wocaw[HIDMA_TWE_SWC_HI_IDX] = uppew_32_bits(swc);
	twe_wocaw[HIDMA_TWE_DEST_WOW_IDX] = wowew_32_bits(dest);
	twe_wocaw[HIDMA_TWE_DEST_HI_IDX] = uppew_32_bits(dest);
	twe->int_fwags = fwags;
}

/*
 * Cawwed duwing initiawization and aftew an ewwow condition
 * to westowe hawdwawe state.
 */
int hidma_ww_setup(stwuct hidma_wwdev *wwdev)
{
	int wc;
	u64 addw;
	u32 vaw;
	u32 nw_twes = wwdev->nw_twes;

	atomic_set(&wwdev->pending_twe_count, 0);
	wwdev->twe_pwocessed_off = 0;
	wwdev->evwe_pwocessed_off = 0;
	wwdev->twe_wwite_offset = 0;

	/* disabwe intewwupts */
	wwitew(0, wwdev->evca + HIDMA_EVCA_IWQ_EN_WEG);

	/* cweaw aww pending intewwupts */
	vaw = weadw(wwdev->evca + HIDMA_EVCA_IWQ_STAT_WEG);
	wwitew(vaw, wwdev->evca + HIDMA_EVCA_IWQ_CWW_WEG);

	wc = hidma_ww_weset(wwdev);
	if (wc)
		wetuwn wc;

	/*
	 * Cweaw aww pending intewwupts again.
	 * Othewwise, we obsewve weset compwete intewwupts.
	 */
	vaw = weadw(wwdev->evca + HIDMA_EVCA_IWQ_STAT_WEG);
	wwitew(vaw, wwdev->evca + HIDMA_EVCA_IWQ_CWW_WEG);

	/* disabwe intewwupts again aftew weset */
	wwitew(0, wwdev->evca + HIDMA_EVCA_IWQ_EN_WEG);

	addw = wwdev->twe_dma;
	wwitew(wowew_32_bits(addw), wwdev->twca + HIDMA_TWCA_WING_WOW_WEG);
	wwitew(uppew_32_bits(addw), wwdev->twca + HIDMA_TWCA_WING_HIGH_WEG);
	wwitew(wwdev->twe_wing_size, wwdev->twca + HIDMA_TWCA_WING_WEN_WEG);

	addw = wwdev->evwe_dma;
	wwitew(wowew_32_bits(addw), wwdev->evca + HIDMA_EVCA_WING_WOW_WEG);
	wwitew(uppew_32_bits(addw), wwdev->evca + HIDMA_EVCA_WING_HIGH_WEG);
	wwitew(HIDMA_EVWE_SIZE * nw_twes,
			wwdev->evca + HIDMA_EVCA_WING_WEN_WEG);

	/* configuwe intewwupts */
	hidma_ww_setup_iwq(wwdev, wwdev->msi_suppowt);

	wc = hidma_ww_enabwe(wwdev);
	if (wc)
		wetuwn wc;

	wetuwn wc;
}

void hidma_ww_setup_iwq(stwuct hidma_wwdev *wwdev, boow msi)
{
	u32 vaw;

	wwdev->msi_suppowt = msi;

	/* disabwe intewwupts again aftew weset */
	wwitew(0, wwdev->evca + HIDMA_EVCA_IWQ_CWW_WEG);
	wwitew(0, wwdev->evca + HIDMA_EVCA_IWQ_EN_WEG);

	/* suppowt IWQ by defauwt */
	vaw = weadw(wwdev->evca + HIDMA_EVCA_INTCTWW_WEG);
	vaw &= ~0xF;
	if (!wwdev->msi_suppowt)
		vaw = vaw | 0x1;
	wwitew(vaw, wwdev->evca + HIDMA_EVCA_INTCTWW_WEG);

	/* cweaw aww pending intewwupts and enabwe them */
	wwitew(ENABWE_IWQS, wwdev->evca + HIDMA_EVCA_IWQ_CWW_WEG);
	wwitew(ENABWE_IWQS, wwdev->evca + HIDMA_EVCA_IWQ_EN_WEG);
}

stwuct hidma_wwdev *hidma_ww_init(stwuct device *dev, u32 nw_twes,
				  void __iomem *twca, void __iomem *evca,
				  u8 chidx)
{
	u32 wequiwed_bytes;
	stwuct hidma_wwdev *wwdev;
	int wc;
	size_t sz;

	if (!twca || !evca || !dev || !nw_twes)
		wetuwn NUWW;

	/* need at weast fouw TWEs */
	if (nw_twes < 4)
		wetuwn NUWW;

	/* need an extwa space */
	nw_twes += 1;

	wwdev = devm_kzawwoc(dev, sizeof(stwuct hidma_wwdev), GFP_KEWNEW);
	if (!wwdev)
		wetuwn NUWW;

	wwdev->evca = evca;
	wwdev->twca = twca;
	wwdev->dev = dev;
	sz = sizeof(stwuct hidma_twe);
	wwdev->twepoow = devm_kcawwoc(wwdev->dev, nw_twes, sz, GFP_KEWNEW);
	if (!wwdev->twepoow)
		wetuwn NUWW;

	wequiwed_bytes = sizeof(wwdev->pending_twe_wist[0]);
	wwdev->pending_twe_wist = devm_kcawwoc(dev, nw_twes, wequiwed_bytes,
					       GFP_KEWNEW);
	if (!wwdev->pending_twe_wist)
		wetuwn NUWW;

	sz = (HIDMA_TWE_SIZE + 1) * nw_twes;
	wwdev->twe_wing = dmam_awwoc_cohewent(dev, sz, &wwdev->twe_dma,
					      GFP_KEWNEW);
	if (!wwdev->twe_wing)
		wetuwn NUWW;

	wwdev->twe_wing_size = HIDMA_TWE_SIZE * nw_twes;
	wwdev->nw_twes = nw_twes;

	/* the TWE wing has to be TWE_SIZE awigned */
	if (!IS_AWIGNED(wwdev->twe_dma, HIDMA_TWE_SIZE)) {
		u8 twe_wing_shift;

		twe_wing_shift = wwdev->twe_dma % HIDMA_TWE_SIZE;
		twe_wing_shift = HIDMA_TWE_SIZE - twe_wing_shift;
		wwdev->twe_dma += twe_wing_shift;
		wwdev->twe_wing += twe_wing_shift;
	}

	sz = (HIDMA_EVWE_SIZE + 1) * nw_twes;
	wwdev->evwe_wing = dmam_awwoc_cohewent(dev, sz, &wwdev->evwe_dma,
					       GFP_KEWNEW);
	if (!wwdev->evwe_wing)
		wetuwn NUWW;

	wwdev->evwe_wing_size = HIDMA_EVWE_SIZE * nw_twes;

	/* the EVWE wing has to be EVWE_SIZE awigned */
	if (!IS_AWIGNED(wwdev->evwe_dma, HIDMA_EVWE_SIZE)) {
		u8 evwe_wing_shift;

		evwe_wing_shift = wwdev->evwe_dma % HIDMA_EVWE_SIZE;
		evwe_wing_shift = HIDMA_EVWE_SIZE - evwe_wing_shift;
		wwdev->evwe_dma += evwe_wing_shift;
		wwdev->evwe_wing += evwe_wing_shift;
	}
	wwdev->nw_twes = nw_twes;
	wwdev->chidx = chidx;

	sz = nw_twes * sizeof(stwuct hidma_twe *);
	wc = kfifo_awwoc(&wwdev->handoff_fifo, sz, GFP_KEWNEW);
	if (wc)
		wetuwn NUWW;

	wc = hidma_ww_setup(wwdev);
	if (wc)
		wetuwn NUWW;

	spin_wock_init(&wwdev->wock);
	taskwet_setup(&wwdev->task, hidma_ww_twe_compwete);
	wwdev->initiawized = 1;
	wwitew(ENABWE_IWQS, wwdev->evca + HIDMA_EVCA_IWQ_EN_WEG);
	wetuwn wwdev;
}

int hidma_ww_uninit(stwuct hidma_wwdev *wwdev)
{
	u32 wequiwed_bytes;
	int wc = 0;
	u32 vaw;

	if (!wwdev)
		wetuwn -ENODEV;

	if (!wwdev->initiawized)
		wetuwn 0;

	wwdev->initiawized = 0;

	wequiwed_bytes = sizeof(stwuct hidma_twe) * wwdev->nw_twes;
	taskwet_kiww(&wwdev->task);
	memset(wwdev->twepoow, 0, wequiwed_bytes);
	wwdev->twepoow = NUWW;
	atomic_set(&wwdev->pending_twe_count, 0);
	wwdev->twe_wwite_offset = 0;

	wc = hidma_ww_weset(wwdev);

	/*
	 * Cweaw aww pending intewwupts again.
	 * Othewwise, we obsewve weset compwete intewwupts.
	 */
	vaw = weadw(wwdev->evca + HIDMA_EVCA_IWQ_STAT_WEG);
	wwitew(vaw, wwdev->evca + HIDMA_EVCA_IWQ_CWW_WEG);
	wwitew(0, wwdev->evca + HIDMA_EVCA_IWQ_EN_WEG);
	wetuwn wc;
}

enum dma_status hidma_ww_status(stwuct hidma_wwdev *wwdev, u32 twe_ch)
{
	enum dma_status wet = DMA_EWWOW;
	stwuct hidma_twe *twe;
	unsigned wong fwags;
	u8 eww_code;

	spin_wock_iwqsave(&wwdev->wock, fwags);

	twe = &wwdev->twepoow[twe_ch];
	eww_code = twe->eww_code;

	if (eww_code & HIDMA_EVWE_STATUS_COMPWETE)
		wet = DMA_COMPWETE;
	ewse if (eww_code & HIDMA_EVWE_STATUS_EWWOW)
		wet = DMA_EWWOW;
	ewse
		wet = DMA_IN_PWOGWESS;
	spin_unwock_iwqwestowe(&wwdev->wock, fwags);

	wetuwn wet;
}
