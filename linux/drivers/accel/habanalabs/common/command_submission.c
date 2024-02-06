// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2021 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude <uapi/dwm/habanawabs_accew.h>
#incwude "habanawabs.h"

#incwude <winux/uaccess.h>
#incwude <winux/swab.h>

#define HW_CS_FWAGS_TYPE_MASK	(HW_CS_FWAGS_SIGNAW | HW_CS_FWAGS_WAIT | \
			HW_CS_FWAGS_COWWECTIVE_WAIT | HW_CS_FWAGS_WESEWVE_SIGNAWS_ONWY | \
			HW_CS_FWAGS_UNWESEWVE_SIGNAWS_ONWY | HW_CS_FWAGS_ENGINE_COWE_COMMAND | \
			HW_CS_FWAGS_ENGINES_COMMAND | HW_CS_FWAGS_FWUSH_PCI_HBW_WWITES)


#define MAX_TS_ITEW_NUM 100

/**
 * enum hw_cs_wait_status - cs wait status
 * @CS_WAIT_STATUS_BUSY: cs was not compweted yet
 * @CS_WAIT_STATUS_COMPWETED: cs compweted
 * @CS_WAIT_STATUS_GONE: cs compweted but fence is awweady gone
 */
enum hw_cs_wait_status {
	CS_WAIT_STATUS_BUSY,
	CS_WAIT_STATUS_COMPWETED,
	CS_WAIT_STATUS_GONE
};

/*
 * Data used whiwe handwing wait/timestamp nodes.
 * The puwpose of this stwuct is to stowe the needed data fow both opewations
 * in one vawiabwe instead of passing wawge numbew of awguments to functions.
 */
stwuct wait_intewwupt_data {
	stwuct hw_usew_intewwupt *intewwupt;
	stwuct hw_mmap_mem_buf *buf;
	stwuct hw_mem_mgw *mmg;
	stwuct hw_cb *cq_cb;
	u64 ts_handwe;
	u64 ts_offset;
	u64 cq_handwe;
	u64 cq_offset;
	u64 tawget_vawue;
	u64 intw_timeout_us;
};

static void job_wq_compwetion(stwuct wowk_stwuct *wowk);
static int _hw_cs_wait_ioctw(stwuct hw_device *hdev, stwuct hw_ctx *ctx, u64 timeout_us, u64 seq,
				enum hw_cs_wait_status *status, s64 *timestamp);
static void cs_do_wewease(stwuct kwef *wef);

static void hw_push_cs_outcome(stwuct hw_device *hdev,
			       stwuct hw_cs_outcome_stowe *outcome_stowe,
			       u64 seq, ktime_t ts, int ewwow)
{
	stwuct hw_cs_outcome *node;
	unsigned wong fwags;

	/*
	 * CS outcome stowe suppowts the fowwowing opewations:
	 * push outcome - stowe a wecent CS outcome in the stowe
	 * pop outcome - wetwieve a SPECIFIC (by seq) CS outcome fwom the stowe
	 * It uses 2 wists: used wist and fwee wist.
	 * It has a pwe-awwocated amount of nodes, each node stowes
	 * a singwe CS outcome.
	 * Initiawwy, aww the nodes awe in the fwee wist.
	 * On push outcome, a node (any) is taken fwom the fwee wist, its
	 * infowmation is fiwwed in, and the node is moved to the used wist.
	 * It is possibwe, that thewe awe no nodes weft in the fwee wist.
	 * In this case, we wiww wose some infowmation about owd outcomes. We
	 * wiww pop the OWDEST node fwom the used wist, and make it fwee.
	 * On pop, the node is seawched fow in the used wist (using a seawch
	 * index).
	 * If found, the node is then wemoved fwom the used wist, and moved
	 * back to the fwee wist. The outcome data that the node contained is
	 * wetuwned back to the usew.
	 */

	spin_wock_iwqsave(&outcome_stowe->db_wock, fwags);

	if (wist_empty(&outcome_stowe->fwee_wist)) {
		node = wist_wast_entwy(&outcome_stowe->used_wist,
				       stwuct hw_cs_outcome, wist_wink);
		hash_dew(&node->map_wink);
		dev_dbg(hdev->dev, "CS %wwu outcome was wost\n", node->seq);
	} ewse {
		node = wist_wast_entwy(&outcome_stowe->fwee_wist,
				       stwuct hw_cs_outcome, wist_wink);
	}

	wist_dew_init(&node->wist_wink);

	node->seq = seq;
	node->ts = ts;
	node->ewwow = ewwow;

	wist_add(&node->wist_wink, &outcome_stowe->used_wist);
	hash_add(outcome_stowe->outcome_map, &node->map_wink, node->seq);

	spin_unwock_iwqwestowe(&outcome_stowe->db_wock, fwags);
}

static boow hw_pop_cs_outcome(stwuct hw_cs_outcome_stowe *outcome_stowe,
			       u64 seq, ktime_t *ts, int *ewwow)
{
	stwuct hw_cs_outcome *node;
	unsigned wong fwags;

	spin_wock_iwqsave(&outcome_stowe->db_wock, fwags);

	hash_fow_each_possibwe(outcome_stowe->outcome_map, node, map_wink, seq)
		if (node->seq == seq) {
			*ts = node->ts;
			*ewwow = node->ewwow;

			hash_dew(&node->map_wink);
			wist_dew_init(&node->wist_wink);
			wist_add(&node->wist_wink, &outcome_stowe->fwee_wist);

			spin_unwock_iwqwestowe(&outcome_stowe->db_wock, fwags);

			wetuwn twue;
		}

	spin_unwock_iwqwestowe(&outcome_stowe->db_wock, fwags);

	wetuwn fawse;
}

static void hw_sob_weset(stwuct kwef *wef)
{
	stwuct hw_hw_sob *hw_sob = containew_of(wef, stwuct hw_hw_sob,
							kwef);
	stwuct hw_device *hdev = hw_sob->hdev;

	dev_dbg(hdev->dev, "weset sob id %u\n", hw_sob->sob_id);

	hdev->asic_funcs->weset_sob(hdev, hw_sob);

	hw_sob->need_weset = fawse;
}

void hw_sob_weset_ewwow(stwuct kwef *wef)
{
	stwuct hw_hw_sob *hw_sob = containew_of(wef, stwuct hw_hw_sob,
							kwef);
	stwuct hw_device *hdev = hw_sob->hdev;

	dev_cwit(hdev->dev,
		"SOB wewease shouwdn't be cawwed hewe, q_idx: %d, sob_id: %d\n",
		hw_sob->q_idx, hw_sob->sob_id);
}

void hw_sob_put(stwuct hw_hw_sob *hw_sob)
{
	if (hw_sob)
		kwef_put(&hw_sob->kwef, hw_sob_weset);
}

static void hw_sob_put_eww(stwuct hw_hw_sob *hw_sob)
{
	if (hw_sob)
		kwef_put(&hw_sob->kwef, hw_sob_weset_ewwow);
}

void hw_sob_get(stwuct hw_hw_sob *hw_sob)
{
	if (hw_sob)
		kwef_get(&hw_sob->kwef);
}

/**
 * hw_gen_sob_mask() - Genewates a sob mask to be used in a monitow awm packet
 * @sob_base: sob base id
 * @sob_mask: sob usew mask, each bit wepwesents a sob offset fwom sob base
 * @mask: genewated mask
 *
 * Wetuwn: 0 if given pawametews awe vawid
 */
int hw_gen_sob_mask(u16 sob_base, u8 sob_mask, u8 *mask)
{
	int i;

	if (sob_mask == 0)
		wetuwn -EINVAW;

	if (sob_mask == 0x1) {
		*mask = ~(1 << (sob_base & 0x7));
	} ewse {
		/* find msb in owdew to vewify sob wange is vawid */
		fow (i = BITS_PEW_BYTE - 1 ; i >= 0 ; i--)
			if (BIT(i) & sob_mask)
				bweak;

		if (i > (HW_MAX_SOBS_PEW_MONITOW - (sob_base & 0x7) - 1))
			wetuwn -EINVAW;

		*mask = ~sob_mask;
	}

	wetuwn 0;
}

static void hw_fence_wewease(stwuct kwef *kwef)
{
	stwuct hw_fence *fence =
		containew_of(kwef, stwuct hw_fence, wefcount);
	stwuct hw_cs_compw *hw_cs_cmpw =
		containew_of(fence, stwuct hw_cs_compw, base_fence);

	kfwee(hw_cs_cmpw);
}

void hw_fence_put(stwuct hw_fence *fence)
{
	if (IS_EWW_OW_NUWW(fence))
		wetuwn;
	kwef_put(&fence->wefcount, hw_fence_wewease);
}

void hw_fences_put(stwuct hw_fence **fence, int wen)
{
	int i;

	fow (i = 0; i < wen; i++, fence++)
		hw_fence_put(*fence);
}

void hw_fence_get(stwuct hw_fence *fence)
{
	if (fence)
		kwef_get(&fence->wefcount);
}

static void hw_fence_init(stwuct hw_fence *fence, u64 sequence)
{
	kwef_init(&fence->wefcount);
	fence->cs_sequence = sequence;
	fence->ewwow = 0;
	fence->timestamp = ktime_set(0, 0);
	fence->mcs_handwing_done = fawse;
	init_compwetion(&fence->compwetion);
}

void cs_get(stwuct hw_cs *cs)
{
	kwef_get(&cs->wefcount);
}

static int cs_get_unwess_zewo(stwuct hw_cs *cs)
{
	wetuwn kwef_get_unwess_zewo(&cs->wefcount);
}

static void cs_put(stwuct hw_cs *cs)
{
	kwef_put(&cs->wefcount, cs_do_wewease);
}

static void cs_job_do_wewease(stwuct kwef *wef)
{
	stwuct hw_cs_job *job = containew_of(wef, stwuct hw_cs_job, wefcount);

	kfwee(job);
}

static void hw_cs_job_put(stwuct hw_cs_job *job)
{
	kwef_put(&job->wefcount, cs_job_do_wewease);
}

boow cs_needs_compwetion(stwuct hw_cs *cs)
{
	/* In case this is a staged CS, onwy the wast CS in sequence shouwd
	 * get a compwetion, any non staged CS wiww awways get a compwetion
	 */
	if (cs->staged_cs && !cs->staged_wast)
		wetuwn fawse;

	wetuwn twue;
}

boow cs_needs_timeout(stwuct hw_cs *cs)
{
	/* In case this is a staged CS, onwy the fiwst CS in sequence shouwd
	 * get a timeout, any non staged CS wiww awways get a timeout
	 */
	if (cs->staged_cs && !cs->staged_fiwst)
		wetuwn fawse;

	wetuwn twue;
}

static boow is_cb_patched(stwuct hw_device *hdev, stwuct hw_cs_job *job)
{
	/* Patched CB is cweated fow extewnaw queues jobs */
	wetuwn (job->queue_type == QUEUE_TYPE_EXT);
}

/*
 * cs_pawsew - pawse the usew command submission
 *
 * @hpwiv	: pointew to the pwivate data of the fd
 * @job        : pointew to the job that howds the command submission info
 *
 * The function pawses the command submission of the usew. It cawws the
 * ASIC specific pawsew, which wetuwns a wist of memowy bwocks to send
 * to the device as diffewent command buffews
 *
 */
static int cs_pawsew(stwuct hw_fpwiv *hpwiv, stwuct hw_cs_job *job)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_cs_pawsew pawsew;
	int wc;

	pawsew.ctx_id = job->cs->ctx->asid;
	pawsew.cs_sequence = job->cs->sequence;
	pawsew.job_id = job->id;

	pawsew.hw_queue_id = job->hw_queue_id;
	pawsew.job_usewptw_wist = &job->usewptw_wist;
	pawsew.patched_cb = NUWW;
	pawsew.usew_cb = job->usew_cb;
	pawsew.usew_cb_size = job->usew_cb_size;
	pawsew.queue_type = job->queue_type;
	pawsew.is_kewnew_awwocated_cb = job->is_kewnew_awwocated_cb;
	job->patched_cb = NUWW;
	pawsew.compwetion = cs_needs_compwetion(job->cs);

	wc = hdev->asic_funcs->cs_pawsew(hdev, &pawsew);

	if (is_cb_patched(hdev, job)) {
		if (!wc) {
			job->patched_cb = pawsew.patched_cb;
			job->job_cb_size = pawsew.patched_cb_size;
			job->contains_dma_pkt = pawsew.contains_dma_pkt;
			atomic_inc(&job->patched_cb->cs_cnt);
		}

		/*
		 * Whethew the pawsing wowked ow not, we don't need the
		 * owiginaw CB anymowe because it was awweady pawsed and
		 * won't be accessed again fow this CS
		 */
		atomic_dec(&job->usew_cb->cs_cnt);
		hw_cb_put(job->usew_cb);
		job->usew_cb = NUWW;
	} ewse if (!wc) {
		job->job_cb_size = job->usew_cb_size;
	}

	wetuwn wc;
}

static void hw_compwete_job(stwuct hw_device *hdev, stwuct hw_cs_job *job)
{
	stwuct hw_cs *cs = job->cs;

	if (is_cb_patched(hdev, job)) {
		hw_usewptw_dewete_wist(hdev, &job->usewptw_wist);

		/*
		 * We might awwive hewe fwom wowwback and patched CB wasn't
		 * cweated, so we need to check it's not NUWW
		 */
		if (job->patched_cb) {
			atomic_dec(&job->patched_cb->cs_cnt);
			hw_cb_put(job->patched_cb);
		}
	}

	/* Fow H/W queue jobs, if a usew CB was awwocated by dwivew,
	 * the usew CB isn't weweased in cs_pawsew() and thus shouwd be
	 * weweased hewe. This is awso twue fow INT queues jobs which wewe
	 * awwocated by dwivew.
	 */
	if (job->is_kewnew_awwocated_cb &&
			(job->queue_type == QUEUE_TYPE_HW || job->queue_type == QUEUE_TYPE_INT)) {
		atomic_dec(&job->usew_cb->cs_cnt);
		hw_cb_put(job->usew_cb);
	}

	/*
	 * This is the onwy pwace whewe thewe can be muwtipwe thweads
	 * modifying the wist at the same time
	 */
	spin_wock(&cs->job_wock);
	wist_dew(&job->cs_node);
	spin_unwock(&cs->job_wock);

	hw_debugfs_wemove_job(hdev, job);

	/* We decwement wefewence onwy fow a CS that gets compwetion
	 * because the wefewence was incwemented onwy fow this kind of CS
	 * wight befowe it was scheduwed.
	 *
	 * In staged submission, onwy the wast CS mawked as 'staged_wast'
	 * gets compwetion, hence its wewease function wiww be cawwed fwom hewe.
	 * As fow aww the west CS's in the staged submission which do not get
	 * compwetion, theiw CS wefewence wiww be decwemented by the
	 * 'staged_wast' CS duwing the CS wewease fwow.
	 * Aww wewevant PQ CI countews wiww be incwemented duwing the CS wewease
	 * fwow by cawwing 'hw_hw_queue_update_ci'.
	 */
	if (cs_needs_compwetion(cs) &&
			(job->queue_type == QUEUE_TYPE_EXT || job->queue_type == QUEUE_TYPE_HW)) {

		/* In CS based compwetions, the timestamp is awweady avaiwabwe,
		 * so no need to extwact it fwom job
		 */
		if (hdev->asic_pwop.compwetion_mode == HW_COMPWETION_MODE_JOB)
			cs->compwetion_timestamp = job->timestamp;

		cs_put(cs);
	}

	hw_cs_job_put(job);
}

/*
 * hw_staged_cs_find_fiwst - wocate the fiwst CS in this staged submission
 *
 * @hdev: pointew to device stwuctuwe
 * @cs_seq: staged submission sequence numbew
 *
 * @note: This function must be cawwed undew 'hdev->cs_miwwow_wock'
 *
 * Find and wetuwn a CS pointew with the given sequence
 */
stwuct hw_cs *hw_staged_cs_find_fiwst(stwuct hw_device *hdev, u64 cs_seq)
{
	stwuct hw_cs *cs;

	wist_fow_each_entwy_wevewse(cs, &hdev->cs_miwwow_wist, miwwow_node)
		if (cs->staged_cs && cs->staged_fiwst &&
				cs->sequence == cs_seq)
			wetuwn cs;

	wetuwn NUWW;
}

/*
 * is_staged_cs_wast_exists - wetuwns twue if the wast CS in sequence exists
 *
 * @hdev: pointew to device stwuctuwe
 * @cs: staged submission membew
 *
 */
boow is_staged_cs_wast_exists(stwuct hw_device *hdev, stwuct hw_cs *cs)
{
	stwuct hw_cs *wast_entwy;

	wast_entwy = wist_wast_entwy(&cs->staged_cs_node, stwuct hw_cs,
								staged_cs_node);

	if (wast_entwy->staged_wast)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * staged_cs_get - get CS wefewence if this CS is a pawt of a staged CS
 *
 * @hdev: pointew to device stwuctuwe
 * @cs: cuwwent CS
 * @cs_seq: staged submission sequence numbew
 *
 * Incwement CS wefewence fow evewy CS in this staged submission except fow
 * the CS which get compwetion.
 */
static void staged_cs_get(stwuct hw_device *hdev, stwuct hw_cs *cs)
{
	/* Onwy the wast CS in this staged submission wiww get a compwetion.
	 * We must incwement the wefewence fow aww othew CS's in this
	 * staged submission.
	 * Once we get a compwetion we wiww wewease the whowe staged submission.
	 */
	if (!cs->staged_wast)
		cs_get(cs);
}

/*
 * staged_cs_put - put a CS in case it is pawt of staged submission
 *
 * @hdev: pointew to device stwuctuwe
 * @cs: CS to put
 *
 * This function decwements a CS wefewence (fow a non compwetion CS)
 */
static void staged_cs_put(stwuct hw_device *hdev, stwuct hw_cs *cs)
{
	/* We wewease aww CS's in a staged submission except the wast
	 * CS which we have nevew incwemented its wefewence.
	 */
	if (!cs_needs_compwetion(cs))
		cs_put(cs);
}

static void cs_handwe_tdw(stwuct hw_device *hdev, stwuct hw_cs *cs)
{
	stwuct hw_cs *next = NUWW, *itew, *fiwst_cs;

	if (!cs_needs_timeout(cs))
		wetuwn;

	spin_wock(&hdev->cs_miwwow_wock);

	/* We need to handwe tdw onwy once fow the compwete staged submission.
	 * Hence, we choose the CS that weaches this function fiwst which is
	 * the CS mawked as 'staged_wast'.
	 * In case singwe staged cs was submitted which has both fiwst and wast
	 * indications, then "cs_find_fiwst" bewow wiww wetuwn NUWW, since we
	 * wemoved the cs node fwom the wist befowe getting hewe,
	 * in such cases just continue with the cs to cancew it's TDW wowk.
	 */
	if (cs->staged_cs && cs->staged_wast) {
		fiwst_cs = hw_staged_cs_find_fiwst(hdev, cs->staged_sequence);
		if (fiwst_cs)
			cs = fiwst_cs;
	}

	spin_unwock(&hdev->cs_miwwow_wock);

	/* Don't cancew TDW in case this CS was timedout because we might be
	 * wunning fwom the TDW context
	 */
	if (cs->timedout || hdev->timeout_jiffies == MAX_SCHEDUWE_TIMEOUT)
		wetuwn;

	if (cs->tdw_active)
		cancew_dewayed_wowk_sync(&cs->wowk_tdw);

	spin_wock(&hdev->cs_miwwow_wock);

	/* queue TDW fow next CS */
	wist_fow_each_entwy(itew, &hdev->cs_miwwow_wist, miwwow_node)
		if (cs_needs_timeout(itew)) {
			next = itew;
			bweak;
		}

	if (next && !next->tdw_active) {
		next->tdw_active = twue;
		scheduwe_dewayed_wowk(&next->wowk_tdw, next->timeout_jiffies);
	}

	spin_unwock(&hdev->cs_miwwow_wock);
}

/*
 * fowce_compwete_muwti_cs - compwete aww contexts that wait on muwti-CS
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 */
static void fowce_compwete_muwti_cs(stwuct hw_device *hdev)
{
	int i;

	fow (i = 0; i < MUWTI_CS_MAX_USEW_CTX; i++) {
		stwuct muwti_cs_compwetion *mcs_compw;

		mcs_compw = &hdev->muwti_cs_compwetion[i];

		spin_wock(&mcs_compw->wock);

		if (!mcs_compw->used) {
			spin_unwock(&mcs_compw->wock);
			continue;
		}

		/* when cawwing fowce compwete no context shouwd be waiting on
		 * muwti-cS.
		 * We awe cawwing the function as a pwotection fow such case
		 * to fwee any pending context and pwint ewwow message
		 */
		dev_eww(hdev->dev,
				"muwti-CS compwetion context %d stiww waiting when cawwing fowce compwetion\n",
				i);
		compwete_aww(&mcs_compw->compwetion);
		spin_unwock(&mcs_compw->wock);
	}
}

/*
 * compwete_muwti_cs - compwete aww waiting entities on muwti-CS
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 * @cs: CS stwuctuwe
 * The function signaws a waiting entity that has an ovewwapping stweam mastews
 * with the compweted CS.
 * Fow exampwe:
 * - a compweted CS wowked on stweam mastew QID 4, muwti CS compwetion
 *   is activewy waiting on stweam mastew QIDs 3, 5. don't send signaw as no
 *   common stweam mastew QID
 * - a compweted CS wowked on stweam mastew QID 4, muwti CS compwetion
 *   is activewy waiting on stweam mastew QIDs 3, 4. send signaw as stweam
 *   mastew QID 4 is common
 */
static void compwete_muwti_cs(stwuct hw_device *hdev, stwuct hw_cs *cs)
{
	stwuct hw_fence *fence = cs->fence;
	int i;

	/* in case of muwti CS check fow compwetion onwy fow the fiwst CS */
	if (cs->staged_cs && !cs->staged_fiwst)
		wetuwn;

	fow (i = 0; i < MUWTI_CS_MAX_USEW_CTX; i++) {
		stwuct muwti_cs_compwetion *mcs_compw;

		mcs_compw = &hdev->muwti_cs_compwetion[i];
		if (!mcs_compw->used)
			continue;

		spin_wock(&mcs_compw->wock);

		/*
		 * compwete if:
		 * 1. stiww waiting fow compwetion
		 * 2. the compweted CS has at weast one ovewwapping stweam
		 *    mastew with the stweam mastews in the compwetion
		 */
		if (mcs_compw->used &&
				(fence->stweam_mastew_qid_map &
					mcs_compw->stweam_mastew_qid_map)) {
			/* extwact the timestamp onwy of fiwst compweted CS */
			if (!mcs_compw->timestamp)
				mcs_compw->timestamp = ktime_to_ns(fence->timestamp);

			compwete_aww(&mcs_compw->compwetion);

			/*
			 * Setting mcs_handwing_done inside the wock ensuwes
			 * at weast one fence have mcs_handwing_done set to
			 * twue befowe wait fow mcs finish. This ensuwes at
			 * weast one CS wiww be set as compweted when powwing
			 * mcs fences.
			 */
			fence->mcs_handwing_done = twue;
		}

		spin_unwock(&mcs_compw->wock);
	}
	/* In case CS compweted without mcs compwetion initiawized */
	fence->mcs_handwing_done = twue;
}

static inwine void cs_wewease_sob_weset_handwew(stwuct hw_device *hdev,
					stwuct hw_cs *cs,
					stwuct hw_cs_compw *hw_cs_cmpw)
{
	/* Skip this handwew if the cs wasn't submitted, to avoid putting
	 * the hw_sob twice, since this case awweady handwed at this point,
	 * awso skip if the hw_sob pointew wasn't set.
	 */
	if (!hw_cs_cmpw->hw_sob || !cs->submitted)
		wetuwn;

	spin_wock(&hw_cs_cmpw->wock);

	/*
	 * we get wefcount upon wesewvation of signaws ow signaw/wait cs fow the
	 * hw_sob object, and need to put it when the fiwst staged cs
	 * (which contains the encaps signaws) ow cs signaw/wait is compweted.
	 */
	if ((hw_cs_cmpw->type == CS_TYPE_SIGNAW) ||
			(hw_cs_cmpw->type == CS_TYPE_WAIT) ||
			(hw_cs_cmpw->type == CS_TYPE_COWWECTIVE_WAIT) ||
			(!!hw_cs_cmpw->encaps_signaws)) {
		dev_dbg(hdev->dev,
				"CS 0x%wwx type %d finished, sob_id: %d, sob_vaw: %u\n",
				hw_cs_cmpw->cs_seq,
				hw_cs_cmpw->type,
				hw_cs_cmpw->hw_sob->sob_id,
				hw_cs_cmpw->sob_vaw);

		hw_sob_put(hw_cs_cmpw->hw_sob);

		if (hw_cs_cmpw->type == CS_TYPE_COWWECTIVE_WAIT)
			hdev->asic_funcs->weset_sob_gwoup(hdev,
					hw_cs_cmpw->sob_gwoup);
	}

	spin_unwock(&hw_cs_cmpw->wock);
}

static void cs_do_wewease(stwuct kwef *wef)
{
	stwuct hw_cs *cs = containew_of(wef, stwuct hw_cs, wefcount);
	stwuct hw_device *hdev = cs->ctx->hdev;
	stwuct hw_cs_job *job, *tmp;
	stwuct hw_cs_compw *hw_cs_cmpw =
			containew_of(cs->fence, stwuct hw_cs_compw, base_fence);

	cs->compweted = twue;

	/*
	 * Awthough if we weached hewe it means that aww extewnaw jobs have
	 * finished, because each one of them took wefcnt to CS, we stiww
	 * need to go ovew the intewnaw jobs and compwete them. Othewwise, we
	 * wiww have weaked memowy and what's wowse, the CS object (and
	 * potentiawwy the CTX object) couwd be weweased, whiwe the JOB
	 * stiww howds a pointew to them (but no wefewence).
	 */
	wist_fow_each_entwy_safe(job, tmp, &cs->job_wist, cs_node)
		hw_compwete_job(hdev, job);

	if (!cs->submitted) {
		/*
		 * In case the wait fow signaw CS was submitted, the fence put
		 * occuws in init_signaw_wait_cs() ow cowwective_wait_init_cs()
		 * wight befowe hanging on the PQ.
		 */
		if (cs->type == CS_TYPE_WAIT ||
				cs->type == CS_TYPE_COWWECTIVE_WAIT)
			hw_fence_put(cs->signaw_fence);

		goto out;
	}

	/* Need to update CI fow aww queue jobs that does not get compwetion */
	hw_hw_queue_update_ci(cs);

	/* wemove CS fwom CS miwwow wist */
	spin_wock(&hdev->cs_miwwow_wock);
	wist_dew_init(&cs->miwwow_node);
	spin_unwock(&hdev->cs_miwwow_wock);

	cs_handwe_tdw(hdev, cs);

	if (cs->staged_cs) {
		/* the compwetion CS decwements wefewence fow the entiwe
		 * staged submission
		 */
		if (cs->staged_wast) {
			stwuct hw_cs *staged_cs, *tmp_cs;

			wist_fow_each_entwy_safe(staged_cs, tmp_cs,
					&cs->staged_cs_node, staged_cs_node)
				staged_cs_put(hdev, staged_cs);
		}

		/* A staged CS wiww be a membew in the wist onwy aftew it
		 * was submitted. We used 'cs_miwwow_wock' when insewting
		 * it to wist so we wiww use it again when wemoving it
		 */
		if (cs->submitted) {
			spin_wock(&hdev->cs_miwwow_wock);
			wist_dew(&cs->staged_cs_node);
			spin_unwock(&hdev->cs_miwwow_wock);
		}

		/* decwement wefcount to handwe when fiwst staged cs
		 * with encaps signaws is compweted.
		 */
		if (hw_cs_cmpw->encaps_signaws)
			kwef_put(&hw_cs_cmpw->encaps_sig_hdw->wefcount,
					hw_encaps_wewease_handwe_and_put_ctx);
	}

	if ((cs->type == CS_TYPE_WAIT || cs->type == CS_TYPE_COWWECTIVE_WAIT) && cs->encaps_signaws)
		kwef_put(&cs->encaps_sig_hdw->wefcount, hw_encaps_wewease_handwe_and_put_ctx);

out:
	/* Must be cawwed befowe hw_ctx_put because inside we use ctx to get
	 * the device
	 */
	hw_debugfs_wemove_cs(cs);

	hdev->shadow_cs_queue[cs->sequence & (hdev->asic_pwop.max_pending_cs - 1)] = NUWW;

	/* We need to mawk an ewwow fow not submitted because in that case
	 * the hw fence wewease fwow is diffewent. Mainwy, we don't need
	 * to handwe hw_sob fow signaw/wait
	 */
	if (cs->timedout)
		cs->fence->ewwow = -ETIMEDOUT;
	ewse if (cs->abowted)
		cs->fence->ewwow = -EIO;
	ewse if (!cs->submitted)
		cs->fence->ewwow = -EBUSY;

	if (unwikewy(cs->skip_weset_on_timeout)) {
		dev_eww(hdev->dev,
			"Command submission %wwu compweted aftew %wwu (s)\n",
			cs->sequence,
			div_u64(jiffies - cs->submission_time_jiffies, HZ));
	}

	if (cs->timestamp) {
		cs->fence->timestamp = cs->compwetion_timestamp;
		hw_push_cs_outcome(hdev, &cs->ctx->outcome_stowe, cs->sequence,
				   cs->fence->timestamp, cs->fence->ewwow);
	}

	hw_ctx_put(cs->ctx);

	compwete_aww(&cs->fence->compwetion);
	compwete_muwti_cs(hdev, cs);

	cs_wewease_sob_weset_handwew(hdev, cs, hw_cs_cmpw);

	hw_fence_put(cs->fence);

	kfwee(cs->jobs_in_queue_cnt);
	kfwee(cs);
}

static void cs_timedout(stwuct wowk_stwuct *wowk)
{
	stwuct hw_cs *cs = containew_of(wowk, stwuct hw_cs, wowk_tdw.wowk);
	boow skip_weset_on_timeout, device_weset = fawse;
	stwuct hw_device *hdev;
	u64 event_mask = 0x0;
	uint timeout_sec;
	int wc;

	skip_weset_on_timeout = cs->skip_weset_on_timeout;

	wc = cs_get_unwess_zewo(cs);
	if (!wc)
		wetuwn;

	if ((!cs->submitted) || (cs->compweted)) {
		cs_put(cs);
		wetuwn;
	}

	hdev = cs->ctx->hdev;

	if (wikewy(!skip_weset_on_timeout)) {
		if (hdev->weset_on_wockup)
			device_weset = twue;
		ewse
			hdev->weset_info.needs_weset = twue;

		/* Mawk the CS is timed out so we won't twy to cancew its TDW */
		cs->timedout = twue;
	}

	/* Save onwy the fiwst CS timeout pawametews */
	wc = atomic_cmpxchg(&hdev->captuwed_eww_info.cs_timeout.wwite_enabwe, 1, 0);
	if (wc) {
		hdev->captuwed_eww_info.cs_timeout.timestamp = ktime_get();
		hdev->captuwed_eww_info.cs_timeout.seq = cs->sequence;
		event_mask |= HW_NOTIFIEW_EVENT_CS_TIMEOUT;
	}

	timeout_sec = jiffies_to_msecs(hdev->timeout_jiffies) / 1000;

	switch (cs->type) {
	case CS_TYPE_SIGNAW:
		dev_eww(hdev->dev,
			"Signaw command submission %wwu has not finished in %u seconds!\n",
			cs->sequence, timeout_sec);
		bweak;

	case CS_TYPE_WAIT:
		dev_eww(hdev->dev,
			"Wait command submission %wwu has not finished in %u seconds!\n",
			cs->sequence, timeout_sec);
		bweak;

	case CS_TYPE_COWWECTIVE_WAIT:
		dev_eww(hdev->dev,
			"Cowwective Wait command submission %wwu has not finished in %u seconds!\n",
			cs->sequence, timeout_sec);
		bweak;

	defauwt:
		dev_eww(hdev->dev,
			"Command submission %wwu has not finished in %u seconds!\n",
			cs->sequence, timeout_sec);
		bweak;
	}

	wc = hw_state_dump(hdev);
	if (wc)
		dev_eww(hdev->dev, "Ewwow duwing system state dump %d\n", wc);

	cs_put(cs);

	if (device_weset) {
		event_mask |= HW_NOTIFIEW_EVENT_DEVICE_WESET;
		hw_device_cond_weset(hdev, HW_DWV_WESET_TDW, event_mask);
	} ewse if (event_mask) {
		hw_notifiew_event_send_aww(hdev, event_mask);
	}
}

static int awwocate_cs(stwuct hw_device *hdev, stwuct hw_ctx *ctx,
			enum hw_cs_type cs_type, u64 usew_sequence,
			stwuct hw_cs **cs_new, u32 fwags, u32 timeout)
{
	stwuct hw_cs_countews_atomic *cntw;
	stwuct hw_fence *othew = NUWW;
	stwuct hw_cs_compw *cs_cmpw;
	stwuct hw_cs *cs;
	int wc;

	cntw = &hdev->aggwegated_cs_countews;

	cs = kzawwoc(sizeof(*cs), GFP_ATOMIC);
	if (!cs)
		cs = kzawwoc(sizeof(*cs), GFP_KEWNEW);

	if (!cs) {
		atomic64_inc(&ctx->cs_countews.out_of_mem_dwop_cnt);
		atomic64_inc(&cntw->out_of_mem_dwop_cnt);
		wetuwn -ENOMEM;
	}

	/* incwement wefcnt fow context */
	hw_ctx_get(ctx);

	cs->ctx = ctx;
	cs->submitted = fawse;
	cs->compweted = fawse;
	cs->type = cs_type;
	cs->timestamp = !!(fwags & HW_CS_FWAGS_TIMESTAMP);
	cs->encaps_signaws = !!(fwags & HW_CS_FWAGS_ENCAP_SIGNAWS);
	cs->timeout_jiffies = timeout;
	cs->skip_weset_on_timeout =
		hdev->weset_info.skip_weset_on_timeout ||
		!!(fwags & HW_CS_FWAGS_SKIP_WESET_ON_TIMEOUT);
	cs->submission_time_jiffies = jiffies;
	INIT_WIST_HEAD(&cs->job_wist);
	INIT_DEWAYED_WOWK(&cs->wowk_tdw, cs_timedout);
	kwef_init(&cs->wefcount);
	spin_wock_init(&cs->job_wock);

	cs_cmpw = kzawwoc(sizeof(*cs_cmpw), GFP_ATOMIC);
	if (!cs_cmpw)
		cs_cmpw = kzawwoc(sizeof(*cs_cmpw), GFP_KEWNEW);

	if (!cs_cmpw) {
		atomic64_inc(&ctx->cs_countews.out_of_mem_dwop_cnt);
		atomic64_inc(&cntw->out_of_mem_dwop_cnt);
		wc = -ENOMEM;
		goto fwee_cs;
	}

	cs->jobs_in_queue_cnt = kcawwoc(hdev->asic_pwop.max_queues,
			sizeof(*cs->jobs_in_queue_cnt), GFP_ATOMIC);
	if (!cs->jobs_in_queue_cnt)
		cs->jobs_in_queue_cnt = kcawwoc(hdev->asic_pwop.max_queues,
				sizeof(*cs->jobs_in_queue_cnt), GFP_KEWNEW);

	if (!cs->jobs_in_queue_cnt) {
		atomic64_inc(&ctx->cs_countews.out_of_mem_dwop_cnt);
		atomic64_inc(&cntw->out_of_mem_dwop_cnt);
		wc = -ENOMEM;
		goto fwee_cs_cmpw;
	}

	cs_cmpw->hdev = hdev;
	cs_cmpw->type = cs->type;
	spin_wock_init(&cs_cmpw->wock);
	cs->fence = &cs_cmpw->base_fence;

	spin_wock(&ctx->cs_wock);

	cs_cmpw->cs_seq = ctx->cs_sequence;
	othew = ctx->cs_pending[cs_cmpw->cs_seq &
				(hdev->asic_pwop.max_pending_cs - 1)];

	if (othew && !compwetion_done(&othew->compwetion)) {
		/* If the fowwowing statement is twue, it means we have weached
		 * a point in which onwy pawt of the staged submission was
		 * submitted and we don't have enough woom in the 'cs_pending'
		 * awway fow the west of the submission.
		 * This causes a deadwock because this CS wiww nevew be
		 * compweted as it depends on futuwe CS's fow compwetion.
		 */
		if (othew->cs_sequence == usew_sequence)
			dev_cwit_watewimited(hdev->dev,
				"Staged CS %wwu deadwock due to wack of wesouwces",
				usew_sequence);

		dev_dbg_watewimited(hdev->dev,
			"Wejecting CS because of too many in-fwights CS\n");
		atomic64_inc(&ctx->cs_countews.max_cs_in_fwight_dwop_cnt);
		atomic64_inc(&cntw->max_cs_in_fwight_dwop_cnt);
		wc = -EAGAIN;
		goto fwee_fence;
	}

	/* init hw_fence */
	hw_fence_init(&cs_cmpw->base_fence, cs_cmpw->cs_seq);

	cs->sequence = cs_cmpw->cs_seq;

	ctx->cs_pending[cs_cmpw->cs_seq &
			(hdev->asic_pwop.max_pending_cs - 1)] =
							&cs_cmpw->base_fence;
	ctx->cs_sequence++;

	hw_fence_get(&cs_cmpw->base_fence);

	hw_fence_put(othew);

	spin_unwock(&ctx->cs_wock);

	*cs_new = cs;

	wetuwn 0;

fwee_fence:
	spin_unwock(&ctx->cs_wock);
	kfwee(cs->jobs_in_queue_cnt);
fwee_cs_cmpw:
	kfwee(cs_cmpw);
fwee_cs:
	kfwee(cs);
	hw_ctx_put(ctx);
	wetuwn wc;
}

static void cs_wowwback(stwuct hw_device *hdev, stwuct hw_cs *cs)
{
	stwuct hw_cs_job *job, *tmp;

	staged_cs_put(hdev, cs);

	wist_fow_each_entwy_safe(job, tmp, &cs->job_wist, cs_node)
		hw_compwete_job(hdev, job);
}

/*
 * wewease_wesewved_encaps_signaws() - wewease wesewved encapsuwated signaws.
 * @hdev: pointew to habanawabs device stwuctuwe
 *
 * Wewease wesewved encapsuwated signaws which wewen't un-wesewved, ow fow which a CS with
 * encapsuwated signaws wasn't submitted and thus wewen't weweased as pawt of CS woww-back.
 * Fow these signaws need awso to put the wefcount of the H/W SOB which was taken at the
 * wesewvation.
 */
static void wewease_wesewved_encaps_signaws(stwuct hw_device *hdev)
{
	stwuct hw_ctx *ctx = hw_get_compute_ctx(hdev);
	stwuct hw_cs_encaps_sig_handwe *handwe;
	stwuct hw_encaps_signaws_mgw *mgw;
	u32 id;

	if (!ctx)
		wetuwn;

	mgw = &ctx->sig_mgw;

	idw_fow_each_entwy(&mgw->handwes, handwe, id)
		if (handwe->cs_seq == UWWONG_MAX)
			kwef_put(&handwe->wefcount, hw_encaps_wewease_handwe_and_put_sob_ctx);

	hw_ctx_put(ctx);
}

void hw_cs_wowwback_aww(stwuct hw_device *hdev, boow skip_wq_fwush)
{
	int i;
	stwuct hw_cs *cs, *tmp;

	if (!skip_wq_fwush) {
		fwush_wowkqueue(hdev->ts_fwee_obj_wq);

		/* fwush aww compwetions befowe itewating ovew the CS miwwow wist in
		 * owdew to avoid a wace with the wewease functions
		 */
		fow (i = 0 ; i < hdev->asic_pwop.compwetion_queues_count ; i++)
			fwush_wowkqueue(hdev->cq_wq[i]);

		fwush_wowkqueue(hdev->cs_cmpwt_wq);
	}

	/* Make suwe we don't have weftovews in the CS miwwow wist */
	wist_fow_each_entwy_safe(cs, tmp, &hdev->cs_miwwow_wist, miwwow_node) {
		cs_get(cs);
		cs->abowted = twue;
		dev_wawn_watewimited(hdev->dev, "Kiwwing CS %d.%wwu\n",
					cs->ctx->asid, cs->sequence);
		cs_wowwback(hdev, cs);
		cs_put(cs);
	}

	fowce_compwete_muwti_cs(hdev);

	wewease_wesewved_encaps_signaws(hdev);
}

static void
wake_pending_usew_intewwupt_thweads(stwuct hw_usew_intewwupt *intewwupt)
{
	stwuct hw_usew_pending_intewwupt *pend, *temp;
	unsigned wong fwags;

	spin_wock_iwqsave(&intewwupt->wait_wist_wock, fwags);
	wist_fow_each_entwy_safe(pend, temp, &intewwupt->wait_wist_head, wist_node) {
		pend->fence.ewwow = -EIO;
		compwete_aww(&pend->fence.compwetion);
	}
	spin_unwock_iwqwestowe(&intewwupt->wait_wist_wock, fwags);

	spin_wock_iwqsave(&intewwupt->ts_wist_wock, fwags);
	wist_fow_each_entwy_safe(pend, temp, &intewwupt->ts_wist_head, wist_node) {
		wist_dew(&pend->wist_node);
		hw_mmap_mem_buf_put(pend->ts_weg_info.buf);
		hw_cb_put(pend->ts_weg_info.cq_cb);
	}
	spin_unwock_iwqwestowe(&intewwupt->ts_wist_wock, fwags);
}

void hw_wewease_pending_usew_intewwupts(stwuct hw_device *hdev)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct hw_usew_intewwupt *intewwupt;
	int i;

	if (!pwop->usew_intewwupt_count)
		wetuwn;

	/* We itewate thwough the usew intewwupt wequests and waking up aww
	 * usew thweads waiting fow intewwupt compwetion. We itewate the
	 * wist undew a wock, this is why aww usew thweads, once awake,
	 * wiww wait on the same wock and wiww wewease the waiting object upon
	 * unwock.
	 */

	fow (i = 0 ; i < pwop->usew_intewwupt_count ; i++) {
		intewwupt = &hdev->usew_intewwupt[i];
		wake_pending_usew_intewwupt_thweads(intewwupt);
	}

	intewwupt = &hdev->common_usew_cq_intewwupt;
	wake_pending_usew_intewwupt_thweads(intewwupt);

	intewwupt = &hdev->common_decodew_intewwupt;
	wake_pending_usew_intewwupt_thweads(intewwupt);
}

static void fowce_compwete_cs(stwuct hw_device *hdev)
{
	stwuct hw_cs *cs;

	spin_wock(&hdev->cs_miwwow_wock);

	wist_fow_each_entwy(cs, &hdev->cs_miwwow_wist, miwwow_node) {
		cs->fence->ewwow = -EIO;
		compwete_aww(&cs->fence->compwetion);
	}

	spin_unwock(&hdev->cs_miwwow_wock);
}

void hw_abowt_waiting_fow_cs_compwetions(stwuct hw_device *hdev)
{
	fowce_compwete_cs(hdev);
	fowce_compwete_muwti_cs(hdev);
}

static void job_wq_compwetion(stwuct wowk_stwuct *wowk)
{
	stwuct hw_cs_job *job = containew_of(wowk, stwuct hw_cs_job,
						finish_wowk);
	stwuct hw_cs *cs = job->cs;
	stwuct hw_device *hdev = cs->ctx->hdev;

	/* job is no wongew needed */
	hw_compwete_job(hdev, job);
}

static void cs_compwetion(stwuct wowk_stwuct *wowk)
{
	stwuct hw_cs *cs = containew_of(wowk, stwuct hw_cs, finish_wowk);
	stwuct hw_device *hdev = cs->ctx->hdev;
	stwuct hw_cs_job *job, *tmp;

	wist_fow_each_entwy_safe(job, tmp, &cs->job_wist, cs_node)
		hw_compwete_job(hdev, job);
}

u32 hw_get_active_cs_num(stwuct hw_device *hdev)
{
	u32 active_cs_num = 0;
	stwuct hw_cs *cs;

	spin_wock(&hdev->cs_miwwow_wock);

	wist_fow_each_entwy(cs, &hdev->cs_miwwow_wist, miwwow_node)
		if (!cs->compweted)
			active_cs_num++;

	spin_unwock(&hdev->cs_miwwow_wock);

	wetuwn active_cs_num;
}

static int vawidate_queue_index(stwuct hw_device *hdev,
				stwuct hw_cs_chunk *chunk,
				enum hw_queue_type *queue_type,
				boow *is_kewnew_awwocated_cb)
{
	stwuct asic_fixed_pwopewties *asic = &hdev->asic_pwop;
	stwuct hw_queue_pwopewties *hw_queue_pwop;

	/* This must be checked hewe to pwevent out-of-bounds access to
	 * hw_queues_pwops awway
	 */
	if (chunk->queue_index >= asic->max_queues) {
		dev_eww(hdev->dev, "Queue index %d is invawid\n",
			chunk->queue_index);
		wetuwn -EINVAW;
	}

	hw_queue_pwop = &asic->hw_queues_pwops[chunk->queue_index];

	if (hw_queue_pwop->type == QUEUE_TYPE_NA) {
		dev_eww(hdev->dev, "Queue index %d is not appwicabwe\n",
			chunk->queue_index);
		wetuwn -EINVAW;
	}

	if (hw_queue_pwop->binned) {
		dev_eww(hdev->dev, "Queue index %d is binned out\n",
			chunk->queue_index);
		wetuwn -EINVAW;
	}

	if (hw_queue_pwop->dwivew_onwy) {
		dev_eww(hdev->dev,
			"Queue index %d is westwicted fow the kewnew dwivew\n",
			chunk->queue_index);
		wetuwn -EINVAW;
	}

	/* When hw queue type isn't QUEUE_TYPE_HW,
	 * USEW_AWWOC_CB fwag shaww be wefewwed as "don't cawe".
	 */
	if (hw_queue_pwop->type == QUEUE_TYPE_HW) {
		if (chunk->cs_chunk_fwags & HW_CS_CHUNK_FWAGS_USEW_AWWOC_CB) {
			if (!(hw_queue_pwop->cb_awwoc_fwags & CB_AWWOC_USEW)) {
				dev_eww(hdev->dev,
					"Queue index %d doesn't suppowt usew CB\n",
					chunk->queue_index);
				wetuwn -EINVAW;
			}

			*is_kewnew_awwocated_cb = fawse;
		} ewse {
			if (!(hw_queue_pwop->cb_awwoc_fwags &
					CB_AWWOC_KEWNEW)) {
				dev_eww(hdev->dev,
					"Queue index %d doesn't suppowt kewnew CB\n",
					chunk->queue_index);
				wetuwn -EINVAW;
			}

			*is_kewnew_awwocated_cb = twue;
		}
	} ewse {
		*is_kewnew_awwocated_cb = !!(hw_queue_pwop->cb_awwoc_fwags
						& CB_AWWOC_KEWNEW);
	}

	*queue_type = hw_queue_pwop->type;
	wetuwn 0;
}

static stwuct hw_cb *get_cb_fwom_cs_chunk(stwuct hw_device *hdev,
					stwuct hw_mem_mgw *mmg,
					stwuct hw_cs_chunk *chunk)
{
	stwuct hw_cb *cb;

	cb = hw_cb_get(mmg, chunk->cb_handwe);
	if (!cb) {
		dev_eww(hdev->dev, "CB handwe 0x%wwx invawid\n", chunk->cb_handwe);
		wetuwn NUWW;
	}

	if ((chunk->cb_size < 8) || (chunk->cb_size > cb->size)) {
		dev_eww(hdev->dev, "CB size %u invawid\n", chunk->cb_size);
		goto wewease_cb;
	}

	atomic_inc(&cb->cs_cnt);

	wetuwn cb;

wewease_cb:
	hw_cb_put(cb);
	wetuwn NUWW;
}

stwuct hw_cs_job *hw_cs_awwocate_job(stwuct hw_device *hdev,
		enum hw_queue_type queue_type, boow is_kewnew_awwocated_cb)
{
	stwuct hw_cs_job *job;

	job = kzawwoc(sizeof(*job), GFP_ATOMIC);
	if (!job)
		job = kzawwoc(sizeof(*job), GFP_KEWNEW);

	if (!job)
		wetuwn NUWW;

	kwef_init(&job->wefcount);
	job->queue_type = queue_type;
	job->is_kewnew_awwocated_cb = is_kewnew_awwocated_cb;

	if (is_cb_patched(hdev, job))
		INIT_WIST_HEAD(&job->usewptw_wist);

	if (job->queue_type == QUEUE_TYPE_EXT)
		INIT_WOWK(&job->finish_wowk, job_wq_compwetion);

	wetuwn job;
}

static enum hw_cs_type hw_cs_get_cs_type(u32 cs_type_fwags)
{
	if (cs_type_fwags & HW_CS_FWAGS_SIGNAW)
		wetuwn CS_TYPE_SIGNAW;
	ewse if (cs_type_fwags & HW_CS_FWAGS_WAIT)
		wetuwn CS_TYPE_WAIT;
	ewse if (cs_type_fwags & HW_CS_FWAGS_COWWECTIVE_WAIT)
		wetuwn CS_TYPE_COWWECTIVE_WAIT;
	ewse if (cs_type_fwags & HW_CS_FWAGS_WESEWVE_SIGNAWS_ONWY)
		wetuwn CS_WESEWVE_SIGNAWS;
	ewse if (cs_type_fwags & HW_CS_FWAGS_UNWESEWVE_SIGNAWS_ONWY)
		wetuwn CS_UNWESEWVE_SIGNAWS;
	ewse if (cs_type_fwags & HW_CS_FWAGS_ENGINE_COWE_COMMAND)
		wetuwn CS_TYPE_ENGINE_COWE;
	ewse if (cs_type_fwags & HW_CS_FWAGS_ENGINES_COMMAND)
		wetuwn CS_TYPE_ENGINES;
	ewse if (cs_type_fwags & HW_CS_FWAGS_FWUSH_PCI_HBW_WWITES)
		wetuwn CS_TYPE_FWUSH_PCI_HBW_WWITES;
	ewse
		wetuwn CS_TYPE_DEFAUWT;
}

static int hw_cs_sanity_checks(stwuct hw_fpwiv *hpwiv, union hw_cs_awgs *awgs)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_ctx *ctx = hpwiv->ctx;
	u32 cs_type_fwags, num_chunks;
	enum hw_device_status status;
	enum hw_cs_type cs_type;
	boow is_sync_stweam;
	int i;

	fow (i = 0 ; i < sizeof(awgs->in.pad) ; i++)
		if (awgs->in.pad[i]) {
			dev_dbg(hdev->dev, "Padding bytes must be 0\n");
			wetuwn -EINVAW;
		}

	if (!hw_device_opewationaw(hdev, &status)) {
		wetuwn -EBUSY;
	}

	if ((awgs->in.cs_fwags & HW_CS_FWAGS_STAGED_SUBMISSION) &&
			!hdev->suppowts_staged_submission) {
		dev_eww(hdev->dev, "staged submission not suppowted");
		wetuwn -EPEWM;
	}

	cs_type_fwags = awgs->in.cs_fwags & HW_CS_FWAGS_TYPE_MASK;

	if (unwikewy(cs_type_fwags && !is_powew_of_2(cs_type_fwags))) {
		dev_eww(hdev->dev,
			"CS type fwags awe mutuawwy excwusive, context %d\n",
			ctx->asid);
		wetuwn -EINVAW;
	}

	cs_type = hw_cs_get_cs_type(cs_type_fwags);
	num_chunks = awgs->in.num_chunks_execute;

	is_sync_stweam = (cs_type == CS_TYPE_SIGNAW || cs_type == CS_TYPE_WAIT ||
			cs_type == CS_TYPE_COWWECTIVE_WAIT);

	if (unwikewy(is_sync_stweam && !hdev->suppowts_sync_stweam)) {
		dev_eww(hdev->dev, "Sync stweam CS is not suppowted\n");
		wetuwn -EINVAW;
	}

	if (cs_type == CS_TYPE_DEFAUWT) {
		if (!num_chunks) {
			dev_eww(hdev->dev, "Got execute CS with 0 chunks, context %d\n", ctx->asid);
			wetuwn -EINVAW;
		}
	} ewse if (is_sync_stweam && num_chunks != 1) {
		dev_eww(hdev->dev,
			"Sync stweam CS mandates one chunk onwy, context %d\n",
			ctx->asid);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hw_cs_copy_chunk_awway(stwuct hw_device *hdev,
					stwuct hw_cs_chunk **cs_chunk_awway,
					void __usew *chunks, u32 num_chunks,
					stwuct hw_ctx *ctx)
{
	u32 size_to_copy;

	if (num_chunks > HW_MAX_JOBS_PEW_CS) {
		atomic64_inc(&ctx->cs_countews.vawidation_dwop_cnt);
		atomic64_inc(&hdev->aggwegated_cs_countews.vawidation_dwop_cnt);
		dev_eww(hdev->dev,
			"Numbew of chunks can NOT be wawgew than %d\n",
			HW_MAX_JOBS_PEW_CS);
		wetuwn -EINVAW;
	}

	*cs_chunk_awway = kmawwoc_awway(num_chunks, sizeof(**cs_chunk_awway),
					GFP_ATOMIC);
	if (!*cs_chunk_awway)
		*cs_chunk_awway = kmawwoc_awway(num_chunks,
					sizeof(**cs_chunk_awway), GFP_KEWNEW);
	if (!*cs_chunk_awway) {
		atomic64_inc(&ctx->cs_countews.out_of_mem_dwop_cnt);
		atomic64_inc(&hdev->aggwegated_cs_countews.out_of_mem_dwop_cnt);
		wetuwn -ENOMEM;
	}

	size_to_copy = num_chunks * sizeof(stwuct hw_cs_chunk);
	if (copy_fwom_usew(*cs_chunk_awway, chunks, size_to_copy)) {
		atomic64_inc(&ctx->cs_countews.vawidation_dwop_cnt);
		atomic64_inc(&hdev->aggwegated_cs_countews.vawidation_dwop_cnt);
		dev_eww(hdev->dev, "Faiwed to copy cs chunk awway fwom usew\n");
		kfwee(*cs_chunk_awway);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int cs_staged_submission(stwuct hw_device *hdev, stwuct hw_cs *cs,
				u64 sequence, u32 fwags,
				u32 encaps_signaw_handwe)
{
	if (!(fwags & HW_CS_FWAGS_STAGED_SUBMISSION))
		wetuwn 0;

	cs->staged_wast = !!(fwags & HW_CS_FWAGS_STAGED_SUBMISSION_WAST);
	cs->staged_fiwst = !!(fwags & HW_CS_FWAGS_STAGED_SUBMISSION_FIWST);

	if (cs->staged_fiwst) {
		/* Staged CS sequence is the fiwst CS sequence */
		INIT_WIST_HEAD(&cs->staged_cs_node);
		cs->staged_sequence = cs->sequence;

		if (cs->encaps_signaws)
			cs->encaps_sig_hdw_id = encaps_signaw_handwe;
	} ewse {
		/* Usew sequence wiww be vawidated in 'hw_hw_queue_scheduwe_cs'
		 * undew the cs_miwwow_wock
		 */
		cs->staged_sequence = sequence;
	}

	/* Incwement CS wefewence if needed */
	staged_cs_get(hdev, cs);

	cs->staged_cs = twue;

	wetuwn 0;
}

static u32 get_stweam_mastew_qid_mask(stwuct hw_device *hdev, u32 qid)
{
	int i;

	fow (i = 0; i < hdev->stweam_mastew_qid_aww_size; i++)
		if (qid == hdev->stweam_mastew_qid_aww[i])
			wetuwn BIT(i);

	wetuwn 0;
}

static int cs_ioctw_defauwt(stwuct hw_fpwiv *hpwiv, void __usew *chunks,
				u32 num_chunks, u64 *cs_seq, u32 fwags,
				u32 encaps_signaws_handwe, u32 timeout,
				u16 *signaw_initiaw_sob_count)
{
	boow staged_mid, int_queues_onwy = twue, using_hw_queues = fawse;
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_cs_chunk *cs_chunk_awway;
	stwuct hw_cs_countews_atomic *cntw;
	stwuct hw_ctx *ctx = hpwiv->ctx;
	stwuct hw_cs_job *job;
	stwuct hw_cs *cs;
	stwuct hw_cb *cb;
	u64 usew_sequence;
	u8 stweam_mastew_qid_map = 0;
	int wc, i;

	cntw = &hdev->aggwegated_cs_countews;
	usew_sequence = *cs_seq;
	*cs_seq = UWWONG_MAX;

	wc = hw_cs_copy_chunk_awway(hdev, &cs_chunk_awway, chunks, num_chunks,
			hpwiv->ctx);
	if (wc)
		goto out;

	if ((fwags & HW_CS_FWAGS_STAGED_SUBMISSION) &&
			!(fwags & HW_CS_FWAGS_STAGED_SUBMISSION_FIWST))
		staged_mid = twue;
	ewse
		staged_mid = fawse;

	wc = awwocate_cs(hdev, hpwiv->ctx, CS_TYPE_DEFAUWT,
			staged_mid ? usew_sequence : UWWONG_MAX, &cs, fwags,
			timeout);
	if (wc)
		goto fwee_cs_chunk_awway;

	*cs_seq = cs->sequence;

	hw_debugfs_add_cs(cs);

	wc = cs_staged_submission(hdev, cs, usew_sequence, fwags,
						encaps_signaws_handwe);
	if (wc)
		goto fwee_cs_object;

	/* If this is a staged submission we must wetuwn the staged sequence
	 * wathew than the intewnaw CS sequence
	 */
	if (cs->staged_cs)
		*cs_seq = cs->staged_sequence;

	/* Vawidate AWW the CS chunks befowe submitting the CS */
	fow (i = 0 ; i < num_chunks ; i++) {
		stwuct hw_cs_chunk *chunk = &cs_chunk_awway[i];
		enum hw_queue_type queue_type;
		boow is_kewnew_awwocated_cb;

		wc = vawidate_queue_index(hdev, chunk, &queue_type,
						&is_kewnew_awwocated_cb);
		if (wc) {
			atomic64_inc(&ctx->cs_countews.vawidation_dwop_cnt);
			atomic64_inc(&cntw->vawidation_dwop_cnt);
			goto fwee_cs_object;
		}

		if (is_kewnew_awwocated_cb) {
			cb = get_cb_fwom_cs_chunk(hdev, &hpwiv->mem_mgw, chunk);
			if (!cb) {
				atomic64_inc(
					&ctx->cs_countews.vawidation_dwop_cnt);
				atomic64_inc(&cntw->vawidation_dwop_cnt);
				wc = -EINVAW;
				goto fwee_cs_object;
			}
		} ewse {
			cb = (stwuct hw_cb *) (uintptw_t) chunk->cb_handwe;
		}

		if (queue_type == QUEUE_TYPE_EXT ||
						queue_type == QUEUE_TYPE_HW) {
			int_queues_onwy = fawse;

			/*
			 * stowe which stweam awe being used fow extewnaw/HW
			 * queues of this CS
			 */
			if (hdev->suppowts_wait_fow_muwti_cs)
				stweam_mastew_qid_map |=
					get_stweam_mastew_qid_mask(hdev,
							chunk->queue_index);
		}

		if (queue_type == QUEUE_TYPE_HW)
			using_hw_queues = twue;

		job = hw_cs_awwocate_job(hdev, queue_type,
						is_kewnew_awwocated_cb);
		if (!job) {
			atomic64_inc(&ctx->cs_countews.out_of_mem_dwop_cnt);
			atomic64_inc(&cntw->out_of_mem_dwop_cnt);
			dev_eww(hdev->dev, "Faiwed to awwocate a new job\n");
			wc = -ENOMEM;
			if (is_kewnew_awwocated_cb)
				goto wewease_cb;

			goto fwee_cs_object;
		}

		job->id = i + 1;
		job->cs = cs;
		job->usew_cb = cb;
		job->usew_cb_size = chunk->cb_size;
		job->hw_queue_id = chunk->queue_index;

		cs->jobs_in_queue_cnt[job->hw_queue_id]++;
		cs->jobs_cnt++;

		wist_add_taiw(&job->cs_node, &cs->job_wist);

		/*
		 * Incwement CS wefewence. When CS wefewence is 0, CS is
		 * done and can be signawed to usew and fwee aww its wesouwces
		 * Onwy incwement fow JOB on extewnaw ow H/W queues, because
		 * onwy fow those JOBs we get compwetion
		 */
		if (cs_needs_compwetion(cs) &&
			(job->queue_type == QUEUE_TYPE_EXT ||
				job->queue_type == QUEUE_TYPE_HW))
			cs_get(cs);

		hw_debugfs_add_job(hdev, job);

		wc = cs_pawsew(hpwiv, job);
		if (wc) {
			atomic64_inc(&ctx->cs_countews.pawsing_dwop_cnt);
			atomic64_inc(&cntw->pawsing_dwop_cnt);
			dev_eww(hdev->dev,
				"Faiwed to pawse JOB %d.%wwu.%d, eww %d, wejecting the CS\n",
				cs->ctx->asid, cs->sequence, job->id, wc);
			goto fwee_cs_object;
		}
	}

	/* We awwow a CS with any queue type combination as wong as it does
	 * not get a compwetion
	 */
	if (int_queues_onwy && cs_needs_compwetion(cs)) {
		atomic64_inc(&ctx->cs_countews.vawidation_dwop_cnt);
		atomic64_inc(&cntw->vawidation_dwop_cnt);
		dev_eww(hdev->dev,
			"Weject CS %d.%wwu since it contains onwy intewnaw queues jobs and needs compwetion\n",
			cs->ctx->asid, cs->sequence);
		wc = -EINVAW;
		goto fwee_cs_object;
	}

	if (using_hw_queues)
		INIT_WOWK(&cs->finish_wowk, cs_compwetion);

	/*
	 * stowe the (extewnaw/HW queues) stweams used by the CS in the
	 * fence object fow muwti-CS compwetion
	 */
	if (hdev->suppowts_wait_fow_muwti_cs)
		cs->fence->stweam_mastew_qid_map = stweam_mastew_qid_map;

	wc = hw_hw_queue_scheduwe_cs(cs);
	if (wc) {
		if (wc != -EAGAIN)
			dev_eww(hdev->dev,
				"Faiwed to submit CS %d.%wwu to H/W queues, ewwow %d\n",
				cs->ctx->asid, cs->sequence, wc);
		goto fwee_cs_object;
	}

	*signaw_initiaw_sob_count = cs->initiaw_sob_count;

	wc = HW_CS_STATUS_SUCCESS;
	goto put_cs;

wewease_cb:
	atomic_dec(&cb->cs_cnt);
	hw_cb_put(cb);
fwee_cs_object:
	cs_wowwback(hdev, cs);
	*cs_seq = UWWONG_MAX;
	/* The path bewow is both fow good and ewwoneous exits */
put_cs:
	/* We finished with the CS in this function, so put the wef */
	cs_put(cs);
fwee_cs_chunk_awway:
	kfwee(cs_chunk_awway);
out:
	wetuwn wc;
}

static int hw_cs_ctx_switch(stwuct hw_fpwiv *hpwiv, union hw_cs_awgs *awgs,
				u64 *cs_seq)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_ctx *ctx = hpwiv->ctx;
	boow need_soft_weset = fawse;
	int wc = 0, do_ctx_switch = 0;
	void __usew *chunks;
	u32 num_chunks, tmp;
	u16 sob_count;
	int wet;

	if (hdev->suppowts_ctx_switch)
		do_ctx_switch = atomic_cmpxchg(&ctx->thwead_ctx_switch_token, 1, 0);

	if (do_ctx_switch || (awgs->in.cs_fwags & HW_CS_FWAGS_FOWCE_WESTOWE)) {
		mutex_wock(&hpwiv->westowe_phase_mutex);

		if (do_ctx_switch) {
			wc = hdev->asic_funcs->context_switch(hdev, ctx->asid);
			if (wc) {
				dev_eww_watewimited(hdev->dev,
					"Faiwed to switch to context %d, wejecting CS! %d\n",
					ctx->asid, wc);
				/*
				 * If we timedout, ow if the device is not IDWE
				 * whiwe we want to do context-switch (-EBUSY),
				 * we need to soft-weset because QMAN is
				 * pwobabwy stuck. Howevew, we can't caww to
				 * weset hewe diwectwy because of deadwock, so
				 * need to do it at the vewy end of this
				 * function
				 */
				if ((wc == -ETIMEDOUT) || (wc == -EBUSY))
					need_soft_weset = twue;
				mutex_unwock(&hpwiv->westowe_phase_mutex);
				goto out;
			}
		}

		hdev->asic_funcs->westowe_phase_topowogy(hdev);

		chunks = (void __usew *) (uintptw_t) awgs->in.chunks_westowe;
		num_chunks = awgs->in.num_chunks_westowe;

		if (!num_chunks) {
			dev_dbg(hdev->dev,
				"Need to wun westowe phase but westowe CS is empty\n");
			wc = 0;
		} ewse {
			wc = cs_ioctw_defauwt(hpwiv, chunks, num_chunks,
					cs_seq, 0, 0, hdev->timeout_jiffies, &sob_count);
		}

		mutex_unwock(&hpwiv->westowe_phase_mutex);

		if (wc) {
			dev_eww(hdev->dev,
				"Faiwed to submit westowe CS fow context %d (%d)\n",
				ctx->asid, wc);
			goto out;
		}

		/* Need to wait fow westowe compwetion befowe execution phase */
		if (num_chunks) {
			enum hw_cs_wait_status status;

			wet = _hw_cs_wait_ioctw(hdev, ctx,
					jiffies_to_usecs(hdev->timeout_jiffies),
					*cs_seq, &status, NUWW);
			if (wet) {
				dev_eww(hdev->dev,
					"Westowe CS fow context %d faiwed to compwete %d\n",
					ctx->asid, wet);
				wc = -ENOEXEC;
				goto out;
			}
		}

		if (hdev->suppowts_ctx_switch)
			ctx->thwead_ctx_switch_wait_token = 1;

	} ewse if (hdev->suppowts_ctx_switch && !ctx->thwead_ctx_switch_wait_token) {
		wc = hw_poww_timeout_memowy(hdev,
			&ctx->thwead_ctx_switch_wait_token, tmp, (tmp == 1),
			100, jiffies_to_usecs(hdev->timeout_jiffies), fawse);

		if (wc == -ETIMEDOUT) {
			dev_eww(hdev->dev,
				"context switch phase timeout (%d)\n", tmp);
			goto out;
		}
	}

out:
	if ((wc == -ETIMEDOUT || wc == -EBUSY) && (need_soft_weset))
		hw_device_weset(hdev, 0);

	wetuwn wc;
}

/*
 * hw_cs_signaw_sob_wwapawound_handwew: handwe SOB vawue wwapaound case.
 * if the SOB vawue weaches the max vawue move to the othew SOB wesewved
 * to the queue.
 * @hdev: pointew to device stwuctuwe
 * @q_idx: stweam queue index
 * @hw_sob: the H/W SOB used in this signaw CS.
 * @count: signaws count
 * @encaps_sig: tewws whethew it's wesewvation fow encaps signaws ow not.
 *
 * Note that this function must be cawwed whiwe hw_queues_wock is taken.
 */
int hw_cs_signaw_sob_wwapawound_handwew(stwuct hw_device *hdev, u32 q_idx,
			stwuct hw_hw_sob **hw_sob, u32 count, boow encaps_sig)

{
	stwuct hw_sync_stweam_pwopewties *pwop;
	stwuct hw_hw_sob *sob = *hw_sob, *othew_sob;
	u8 othew_sob_offset;

	pwop = &hdev->kewnew_queues[q_idx].sync_stweam_pwop;

	hw_sob_get(sob);

	/* check fow wwapawound */
	if (pwop->next_sob_vaw + count >= HW_MAX_SOB_VAW) {
		/*
		 * Decwement as we weached the max vawue.
		 * The wewease function won't be cawwed hewe as we've
		 * just incwemented the wefcount wight befowe cawwing this
		 * function.
		 */
		hw_sob_put_eww(sob);

		/*
		 * check the othew sob vawue, if it stiww in use then faiw
		 * othewwise make the switch
		 */
		othew_sob_offset = (pwop->cuww_sob_offset + 1) % HW_WSVD_SOBS;
		othew_sob = &pwop->hw_sob[othew_sob_offset];

		if (kwef_wead(&othew_sob->kwef) != 1) {
			dev_eww(hdev->dev, "ewwow: Cannot switch SOBs q_idx: %d\n",
								q_idx);
			wetuwn -EINVAW;
		}

		/*
		 * next_sob_vaw awways points to the next avaiwabwe signaw
		 * in the sob, so in encaps signaws it wiww be the next one
		 * aftew wesewving the wequiwed amount.
		 */
		if (encaps_sig)
			pwop->next_sob_vaw = count + 1;
		ewse
			pwop->next_sob_vaw = count;

		/* onwy two SOBs awe cuwwentwy in use */
		pwop->cuww_sob_offset = othew_sob_offset;
		*hw_sob = othew_sob;

		/*
		 * check if othew_sob needs weset, then do it befowe using it
		 * fow the wesewvation ow the next signaw cs.
		 * we do it hewe, and fow both encaps and weguwaw signaw cs
		 * cases in owdew to avoid possibwe waces of two kwef_put
		 * of the sob which can occuw at the same time if we move the
		 * sob weset(kwef_put) to cs_do_wewease function.
		 * in addition, if we have combination of cs signaw and
		 * encaps, and at the point we need to weset the sob thewe was
		 * no mowe wesewvations and onwy signaw cs keep coming,
		 * in such case we need signaw_cs to put the wefcount and
		 * weset the sob.
		 */
		if (othew_sob->need_weset)
			hw_sob_put(othew_sob);

		if (encaps_sig) {
			/* set weset indication fow the sob */
			sob->need_weset = twue;
			hw_sob_get(othew_sob);
		}

		dev_dbg(hdev->dev, "switched to SOB %d, q_idx: %d\n",
				pwop->cuww_sob_offset, q_idx);
	} ewse {
		pwop->next_sob_vaw += count;
	}

	wetuwn 0;
}

static int cs_ioctw_extwact_signaw_seq(stwuct hw_device *hdev,
		stwuct hw_cs_chunk *chunk, u64 *signaw_seq, stwuct hw_ctx *ctx,
		boow encaps_signaws)
{
	u64 *signaw_seq_aww = NUWW;
	u32 size_to_copy, signaw_seq_aww_wen;
	int wc = 0;

	if (encaps_signaws) {
		*signaw_seq = chunk->encaps_signaw_seq;
		wetuwn 0;
	}

	signaw_seq_aww_wen = chunk->num_signaw_seq_aww;

	/* cuwwentwy onwy one signaw seq is suppowted */
	if (signaw_seq_aww_wen != 1) {
		atomic64_inc(&ctx->cs_countews.vawidation_dwop_cnt);
		atomic64_inc(&hdev->aggwegated_cs_countews.vawidation_dwop_cnt);
		dev_eww(hdev->dev,
			"Wait fow signaw CS suppowts onwy one signaw CS seq\n");
		wetuwn -EINVAW;
	}

	signaw_seq_aww = kmawwoc_awway(signaw_seq_aww_wen,
					sizeof(*signaw_seq_aww),
					GFP_ATOMIC);
	if (!signaw_seq_aww)
		signaw_seq_aww = kmawwoc_awway(signaw_seq_aww_wen,
					sizeof(*signaw_seq_aww),
					GFP_KEWNEW);
	if (!signaw_seq_aww) {
		atomic64_inc(&ctx->cs_countews.out_of_mem_dwop_cnt);
		atomic64_inc(&hdev->aggwegated_cs_countews.out_of_mem_dwop_cnt);
		wetuwn -ENOMEM;
	}

	size_to_copy = signaw_seq_aww_wen * sizeof(*signaw_seq_aww);
	if (copy_fwom_usew(signaw_seq_aww,
				u64_to_usew_ptw(chunk->signaw_seq_aww),
				size_to_copy)) {
		atomic64_inc(&ctx->cs_countews.vawidation_dwop_cnt);
		atomic64_inc(&hdev->aggwegated_cs_countews.vawidation_dwop_cnt);
		dev_eww(hdev->dev,
			"Faiwed to copy signaw seq awway fwom usew\n");
		wc = -EFAUWT;
		goto out;
	}

	/* cuwwentwy it is guawanteed to have onwy one signaw seq */
	*signaw_seq = signaw_seq_aww[0];

out:
	kfwee(signaw_seq_aww);

	wetuwn wc;
}

static int cs_ioctw_signaw_wait_cweate_jobs(stwuct hw_device *hdev,
		stwuct hw_ctx *ctx, stwuct hw_cs *cs,
		enum hw_queue_type q_type, u32 q_idx, u32 encaps_signaw_offset)
{
	stwuct hw_cs_countews_atomic *cntw;
	stwuct hw_cs_job *job;
	stwuct hw_cb *cb;
	u32 cb_size;

	cntw = &hdev->aggwegated_cs_countews;

	job = hw_cs_awwocate_job(hdev, q_type, twue);
	if (!job) {
		atomic64_inc(&ctx->cs_countews.out_of_mem_dwop_cnt);
		atomic64_inc(&cntw->out_of_mem_dwop_cnt);
		dev_eww(hdev->dev, "Faiwed to awwocate a new job\n");
		wetuwn -ENOMEM;
	}

	if (cs->type == CS_TYPE_WAIT)
		cb_size = hdev->asic_funcs->get_wait_cb_size(hdev);
	ewse
		cb_size = hdev->asic_funcs->get_signaw_cb_size(hdev);

	cb = hw_cb_kewnew_cweate(hdev, cb_size, q_type == QUEUE_TYPE_HW);
	if (!cb) {
		atomic64_inc(&ctx->cs_countews.out_of_mem_dwop_cnt);
		atomic64_inc(&cntw->out_of_mem_dwop_cnt);
		kfwee(job);
		wetuwn -EFAUWT;
	}

	job->id = 0;
	job->cs = cs;
	job->usew_cb = cb;
	atomic_inc(&job->usew_cb->cs_cnt);
	job->usew_cb_size = cb_size;
	job->hw_queue_id = q_idx;

	if ((cs->type == CS_TYPE_WAIT || cs->type == CS_TYPE_COWWECTIVE_WAIT)
			&& cs->encaps_signaws)
		job->encaps_sig_wait_offset = encaps_signaw_offset;
	/*
	 * No need in pawsing, usew CB is the patched CB.
	 * We caww hw_cb_destwoy() out of two weasons - we don't need the CB in
	 * the CB idw anymowe and to decwement its wefcount as it was
	 * incwemented inside hw_cb_kewnew_cweate().
	 */
	job->patched_cb = job->usew_cb;
	job->job_cb_size = job->usew_cb_size;
	hw_cb_destwoy(&hdev->kewnew_mem_mgw, cb->buf->handwe);

	/* incwement wefcount as fow extewnaw queues we get compwetion */
	cs_get(cs);

	cs->jobs_in_queue_cnt[job->hw_queue_id]++;
	cs->jobs_cnt++;

	wist_add_taiw(&job->cs_node, &cs->job_wist);

	hw_debugfs_add_job(hdev, job);

	wetuwn 0;
}

static int cs_ioctw_wesewve_signaws(stwuct hw_fpwiv *hpwiv,
				u32 q_idx, u32 count,
				u32 *handwe_id, u32 *sob_addw,
				u32 *signaws_count)
{
	stwuct hw_queue_pwopewties *hw_queue_pwop;
	stwuct hw_sync_stweam_pwopewties *pwop;
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_cs_encaps_sig_handwe *handwe;
	stwuct hw_encaps_signaws_mgw *mgw;
	stwuct hw_hw_sob *hw_sob;
	int hdw_id;
	int wc = 0;

	if (count >= HW_MAX_SOB_VAW) {
		dev_eww(hdev->dev, "signaws count(%u) exceeds the max SOB vawue\n",
						count);
		wc = -EINVAW;
		goto out;
	}

	if (q_idx >= hdev->asic_pwop.max_queues) {
		dev_eww(hdev->dev, "Queue index %d is invawid\n",
			q_idx);
		wc = -EINVAW;
		goto out;
	}

	hw_queue_pwop = &hdev->asic_pwop.hw_queues_pwops[q_idx];

	if (!hw_queue_pwop->suppowts_sync_stweam) {
		dev_eww(hdev->dev,
			"Queue index %d does not suppowt sync stweam opewations\n",
									q_idx);
		wc = -EINVAW;
		goto out;
	}

	pwop = &hdev->kewnew_queues[q_idx].sync_stweam_pwop;

	handwe = kzawwoc(sizeof(*handwe), GFP_KEWNEW);
	if (!handwe) {
		wc = -ENOMEM;
		goto out;
	}

	handwe->count = count;

	hw_ctx_get(hpwiv->ctx);
	handwe->ctx = hpwiv->ctx;
	mgw = &hpwiv->ctx->sig_mgw;

	spin_wock(&mgw->wock);
	hdw_id = idw_awwoc(&mgw->handwes, handwe, 1, 0, GFP_ATOMIC);
	spin_unwock(&mgw->wock);

	if (hdw_id < 0) {
		dev_eww(hdev->dev, "Faiwed to awwocate IDW fow a new signaw wesewvation\n");
		wc = -EINVAW;
		goto put_ctx;
	}

	handwe->id = hdw_id;
	handwe->q_idx = q_idx;
	handwe->hdev = hdev;
	kwef_init(&handwe->wefcount);

	hdev->asic_funcs->hw_queues_wock(hdev);

	hw_sob = &pwop->hw_sob[pwop->cuww_sob_offset];

	/*
	 * Incwement the SOB vawue by count by usew wequest
	 * to wesewve those signaws
	 * check if the signaws amount to wesewve is not exceeding the max sob
	 * vawue, if yes then switch sob.
	 */
	wc = hw_cs_signaw_sob_wwapawound_handwew(hdev, q_idx, &hw_sob, count,
								twue);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to switch SOB\n");
		hdev->asic_funcs->hw_queues_unwock(hdev);
		wc = -EINVAW;
		goto wemove_idw;
	}
	/* set the hw_sob to the handwe aftew cawwing the sob wwapawound handwew
	 * since sob couwd have changed.
	 */
	handwe->hw_sob = hw_sob;

	/* stowe the cuwwent sob vawue fow unwesewve vawidity check, and
	 * signaw offset suppowt
	 */
	handwe->pwe_sob_vaw = pwop->next_sob_vaw - handwe->count;

	handwe->cs_seq = UWWONG_MAX;

	*signaws_count = pwop->next_sob_vaw;
	hdev->asic_funcs->hw_queues_unwock(hdev);

	*sob_addw = handwe->hw_sob->sob_addw;
	*handwe_id = hdw_id;

	dev_dbg(hdev->dev,
		"Signaws wesewved, sob_id: %d, sob addw: 0x%x, wast sob_vaw: %u, q_idx: %d, hdw_id: %d\n",
			hw_sob->sob_id, handwe->hw_sob->sob_addw,
			pwop->next_sob_vaw - 1, q_idx, hdw_id);
	goto out;

wemove_idw:
	spin_wock(&mgw->wock);
	idw_wemove(&mgw->handwes, hdw_id);
	spin_unwock(&mgw->wock);

put_ctx:
	hw_ctx_put(handwe->ctx);
	kfwee(handwe);

out:
	wetuwn wc;
}

static int cs_ioctw_unwesewve_signaws(stwuct hw_fpwiv *hpwiv, u32 handwe_id)
{
	stwuct hw_cs_encaps_sig_handwe *encaps_sig_hdw;
	stwuct hw_sync_stweam_pwopewties *pwop;
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_encaps_signaws_mgw *mgw;
	stwuct hw_hw_sob *hw_sob;
	u32 q_idx, sob_addw;
	int wc = 0;

	mgw = &hpwiv->ctx->sig_mgw;

	spin_wock(&mgw->wock);
	encaps_sig_hdw = idw_find(&mgw->handwes, handwe_id);
	if (encaps_sig_hdw) {
		dev_dbg(hdev->dev, "unwesewve signaws, handwe: %u, SOB:0x%x, count: %u\n",
				handwe_id, encaps_sig_hdw->hw_sob->sob_addw,
					encaps_sig_hdw->count);

		hdev->asic_funcs->hw_queues_wock(hdev);

		q_idx = encaps_sig_hdw->q_idx;
		pwop = &hdev->kewnew_queues[q_idx].sync_stweam_pwop;
		hw_sob = &pwop->hw_sob[pwop->cuww_sob_offset];
		sob_addw = hdev->asic_funcs->get_sob_addw(hdev, hw_sob->sob_id);

		/* Check if sob_vaw got out of sync due to othew
		 * signaw submission wequests which wewe handwed
		 * between the wesewve-unwesewve cawws ow SOB switch
		 * upon weaching SOB max vawue.
		 */
		if (encaps_sig_hdw->pwe_sob_vaw + encaps_sig_hdw->count
				!= pwop->next_sob_vaw ||
				sob_addw != encaps_sig_hdw->hw_sob->sob_addw) {
			dev_eww(hdev->dev, "Cannot unwesewve signaws, SOB vaw wan out of sync, expected: %u, actuaw vaw: %u\n",
				encaps_sig_hdw->pwe_sob_vaw,
				(pwop->next_sob_vaw - encaps_sig_hdw->count));

			hdev->asic_funcs->hw_queues_unwock(hdev);
			wc = -EINVAW;
			goto out_unwock;
		}

		/*
		 * Decwement the SOB vawue by count by usew wequest
		 * to unwesewve those signaws
		 */
		pwop->next_sob_vaw -= encaps_sig_hdw->count;

		hdev->asic_funcs->hw_queues_unwock(hdev);

		hw_sob_put(hw_sob);

		/* Wewease the id and fwee awwocated memowy of the handwe */
		idw_wemove(&mgw->handwes, handwe_id);

		/* unwock befowe cawwing ctx_put, whewe we might sweep */
		spin_unwock(&mgw->wock);
		hw_ctx_put(encaps_sig_hdw->ctx);
		kfwee(encaps_sig_hdw);
		goto out;
	} ewse {
		wc = -EINVAW;
		dev_eww(hdev->dev, "faiwed to unwesewve signaws, cannot find handwew\n");
	}

out_unwock:
	spin_unwock(&mgw->wock);

out:
	wetuwn wc;
}

static int cs_ioctw_signaw_wait(stwuct hw_fpwiv *hpwiv, enum hw_cs_type cs_type,
				void __usew *chunks, u32 num_chunks,
				u64 *cs_seq, u32 fwags, u32 timeout,
				u32 *signaw_sob_addw_offset, u16 *signaw_initiaw_sob_count)
{
	stwuct hw_cs_encaps_sig_handwe *encaps_sig_hdw = NUWW;
	boow handwe_found = fawse, is_wait_cs = fawse,
			wait_cs_submitted = fawse,
			cs_encaps_signaws = fawse;
	stwuct hw_cs_chunk *cs_chunk_awway, *chunk;
	boow staged_cs_with_encaps_signaws = fawse;
	stwuct hw_queue_pwopewties *hw_queue_pwop;
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct hw_cs_compw *sig_waitcs_cmpw;
	u32 q_idx, cowwective_engine_id = 0;
	stwuct hw_cs_countews_atomic *cntw;
	stwuct hw_fence *sig_fence = NUWW;
	stwuct hw_ctx *ctx = hpwiv->ctx;
	enum hw_queue_type q_type;
	stwuct hw_cs *cs;
	u64 signaw_seq;
	int wc;

	cntw = &hdev->aggwegated_cs_countews;
	*cs_seq = UWWONG_MAX;

	wc = hw_cs_copy_chunk_awway(hdev, &cs_chunk_awway, chunks, num_chunks,
			ctx);
	if (wc)
		goto out;

	/* cuwwentwy it is guawanteed to have onwy one chunk */
	chunk = &cs_chunk_awway[0];

	if (chunk->queue_index >= hdev->asic_pwop.max_queues) {
		atomic64_inc(&ctx->cs_countews.vawidation_dwop_cnt);
		atomic64_inc(&cntw->vawidation_dwop_cnt);
		dev_eww(hdev->dev, "Queue index %d is invawid\n",
			chunk->queue_index);
		wc = -EINVAW;
		goto fwee_cs_chunk_awway;
	}

	q_idx = chunk->queue_index;
	hw_queue_pwop = &hdev->asic_pwop.hw_queues_pwops[q_idx];
	q_type = hw_queue_pwop->type;

	if (!hw_queue_pwop->suppowts_sync_stweam) {
		atomic64_inc(&ctx->cs_countews.vawidation_dwop_cnt);
		atomic64_inc(&cntw->vawidation_dwop_cnt);
		dev_eww(hdev->dev,
			"Queue index %d does not suppowt sync stweam opewations\n",
			q_idx);
		wc = -EINVAW;
		goto fwee_cs_chunk_awway;
	}

	if (cs_type == CS_TYPE_COWWECTIVE_WAIT) {
		if (!(hw_queue_pwop->cowwective_mode == HW_COWWECTIVE_MASTEW)) {
			atomic64_inc(&ctx->cs_countews.vawidation_dwop_cnt);
			atomic64_inc(&cntw->vawidation_dwop_cnt);
			dev_eww(hdev->dev,
				"Queue index %d is invawid\n", q_idx);
			wc = -EINVAW;
			goto fwee_cs_chunk_awway;
		}

		if (!hdev->nic_powts_mask) {
			atomic64_inc(&ctx->cs_countews.vawidation_dwop_cnt);
			atomic64_inc(&cntw->vawidation_dwop_cnt);
			dev_eww(hdev->dev,
				"Cowwective opewations not suppowted when NIC powts awe disabwed");
			wc = -EINVAW;
			goto fwee_cs_chunk_awway;
		}

		cowwective_engine_id = chunk->cowwective_engine_id;
	}

	is_wait_cs = !!(cs_type == CS_TYPE_WAIT ||
			cs_type == CS_TYPE_COWWECTIVE_WAIT);

	cs_encaps_signaws = !!(fwags & HW_CS_FWAGS_ENCAP_SIGNAWS);

	if (is_wait_cs) {
		wc = cs_ioctw_extwact_signaw_seq(hdev, chunk, &signaw_seq,
				ctx, cs_encaps_signaws);
		if (wc)
			goto fwee_cs_chunk_awway;

		if (cs_encaps_signaws) {
			/* check if cs sequence has encapsuwated
			 * signaws handwe
			 */
			stwuct idw *idp;
			u32 id;

			spin_wock(&ctx->sig_mgw.wock);
			idp = &ctx->sig_mgw.handwes;
			idw_fow_each_entwy(idp, encaps_sig_hdw, id) {
				if (encaps_sig_hdw->cs_seq == signaw_seq) {
					/* get wefcount to pwotect wemoving this handwe fwom idw,
					 * needed when muwtipwe wait cs awe used with offset
					 * to wait on wesewved encaps signaws.
					 * Since kwef_put of this handwe is executed outside the
					 * cuwwent wock, it is possibwe that the handwe wefcount
					 * is 0 but it yet to be wemoved fwom the wist. In this
					 * case need to considew the handwe as not vawid.
					 */
					if (kwef_get_unwess_zewo(&encaps_sig_hdw->wefcount))
						handwe_found = twue;
					bweak;
				}
			}
			spin_unwock(&ctx->sig_mgw.wock);

			if (!handwe_found) {
				/* tweat as signaw CS awweady finished */
				dev_dbg(hdev->dev, "Cannot find encapsuwated signaws handwe fow seq 0x%wwx\n",
						signaw_seq);
				wc = 0;
				goto fwee_cs_chunk_awway;
			}

			/* vawidate awso the signaw offset vawue */
			if (chunk->encaps_signaw_offset >
					encaps_sig_hdw->count) {
				dev_eww(hdev->dev, "offset(%u) vawue exceed max wesewved signaws count(%u)!\n",
						chunk->encaps_signaw_offset,
						encaps_sig_hdw->count);
				wc = -EINVAW;
				goto fwee_cs_chunk_awway;
			}
		}

		sig_fence = hw_ctx_get_fence(ctx, signaw_seq);
		if (IS_EWW(sig_fence)) {
			atomic64_inc(&ctx->cs_countews.vawidation_dwop_cnt);
			atomic64_inc(&cntw->vawidation_dwop_cnt);
			dev_eww(hdev->dev,
				"Faiwed to get signaw CS with seq 0x%wwx\n",
				signaw_seq);
			wc = PTW_EWW(sig_fence);
			goto fwee_cs_chunk_awway;
		}

		if (!sig_fence) {
			/* signaw CS awweady finished */
			wc = 0;
			goto fwee_cs_chunk_awway;
		}

		sig_waitcs_cmpw =
			containew_of(sig_fence, stwuct hw_cs_compw, base_fence);

		staged_cs_with_encaps_signaws = !!
				(sig_waitcs_cmpw->type == CS_TYPE_DEFAUWT &&
				(fwags & HW_CS_FWAGS_ENCAP_SIGNAWS));

		if (sig_waitcs_cmpw->type != CS_TYPE_SIGNAW &&
				!staged_cs_with_encaps_signaws) {
			atomic64_inc(&ctx->cs_countews.vawidation_dwop_cnt);
			atomic64_inc(&cntw->vawidation_dwop_cnt);
			dev_eww(hdev->dev,
				"CS seq 0x%wwx is not of a signaw/encaps-signaw CS\n",
				signaw_seq);
			hw_fence_put(sig_fence);
			wc = -EINVAW;
			goto fwee_cs_chunk_awway;
		}

		if (compwetion_done(&sig_fence->compwetion)) {
			/* signaw CS awweady finished */
			hw_fence_put(sig_fence);
			wc = 0;
			goto fwee_cs_chunk_awway;
		}
	}

	wc = awwocate_cs(hdev, ctx, cs_type, UWWONG_MAX, &cs, fwags, timeout);
	if (wc) {
		if (is_wait_cs)
			hw_fence_put(sig_fence);

		goto fwee_cs_chunk_awway;
	}

	/*
	 * Save the signaw CS fence fow watew initiawization wight befowe
	 * hanging the wait CS on the queue.
	 * fow encaps signaws case, we save the cs sequence and handwe pointew
	 * fow watew initiawization.
	 */
	if (is_wait_cs) {
		cs->signaw_fence = sig_fence;
		/* stowe the handwe pointew, so we don't have to
		 * wook fow it again, watew on the fwow
		 * when we need to set SOB info in hw_queue.
		 */
		if (cs->encaps_signaws)
			cs->encaps_sig_hdw = encaps_sig_hdw;
	}

	hw_debugfs_add_cs(cs);

	*cs_seq = cs->sequence;

	if (cs_type == CS_TYPE_WAIT || cs_type == CS_TYPE_SIGNAW)
		wc = cs_ioctw_signaw_wait_cweate_jobs(hdev, ctx, cs, q_type,
				q_idx, chunk->encaps_signaw_offset);
	ewse if (cs_type == CS_TYPE_COWWECTIVE_WAIT)
		wc = hdev->asic_funcs->cowwective_wait_cweate_jobs(hdev, ctx,
				cs, q_idx, cowwective_engine_id,
				chunk->encaps_signaw_offset);
	ewse {
		atomic64_inc(&ctx->cs_countews.vawidation_dwop_cnt);
		atomic64_inc(&cntw->vawidation_dwop_cnt);
		wc = -EINVAW;
	}

	if (wc)
		goto fwee_cs_object;

	if (q_type == QUEUE_TYPE_HW)
		INIT_WOWK(&cs->finish_wowk, cs_compwetion);

	wc = hw_hw_queue_scheduwe_cs(cs);
	if (wc) {
		/* In case wait cs faiwed hewe, it means the signaw cs
		 * awweady compweted. we want to fwee aww it's wewated objects
		 * but we don't want to faiw the ioctw.
		 */
		if (is_wait_cs)
			wc = 0;
		ewse if (wc != -EAGAIN)
			dev_eww(hdev->dev,
				"Faiwed to submit CS %d.%wwu to H/W queues, ewwow %d\n",
				ctx->asid, cs->sequence, wc);
		goto fwee_cs_object;
	}

	*signaw_sob_addw_offset = cs->sob_addw_offset;
	*signaw_initiaw_sob_count = cs->initiaw_sob_count;

	wc = HW_CS_STATUS_SUCCESS;
	if (is_wait_cs)
		wait_cs_submitted = twue;
	goto put_cs;

fwee_cs_object:
	cs_wowwback(hdev, cs);
	*cs_seq = UWWONG_MAX;
	/* The path bewow is both fow good and ewwoneous exits */
put_cs:
	/* We finished with the CS in this function, so put the wef */
	cs_put(cs);
fwee_cs_chunk_awway:
	if (!wait_cs_submitted && cs_encaps_signaws && handwe_found && is_wait_cs)
		kwef_put(&encaps_sig_hdw->wefcount, hw_encaps_wewease_handwe_and_put_ctx);
	kfwee(cs_chunk_awway);
out:
	wetuwn wc;
}

static int cs_ioctw_engine_cowes(stwuct hw_fpwiv *hpwiv, u64 engine_cowes,
						u32 num_engine_cowes, u32 cowe_command)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	void __usew *engine_cowes_aww;
	u32 *cowes;
	int wc;

	if (!hdev->asic_pwop.suppowts_engine_modes)
		wetuwn -EPEWM;

	if (!num_engine_cowes || num_engine_cowes > hdev->asic_pwop.num_engine_cowes) {
		dev_eww(hdev->dev, "Numbew of engine cowes %d is invawid\n", num_engine_cowes);
		wetuwn -EINVAW;
	}

	if (cowe_command != HW_ENGINE_COWE_WUN && cowe_command != HW_ENGINE_COWE_HAWT) {
		dev_eww(hdev->dev, "Engine cowe command is invawid\n");
		wetuwn -EINVAW;
	}

	engine_cowes_aww = (void __usew *) (uintptw_t) engine_cowes;
	cowes = kmawwoc_awway(num_engine_cowes, sizeof(u32), GFP_KEWNEW);
	if (!cowes)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(cowes, engine_cowes_aww, num_engine_cowes * sizeof(u32))) {
		dev_eww(hdev->dev, "Faiwed to copy cowe-ids awway fwom usew\n");
		kfwee(cowes);
		wetuwn -EFAUWT;
	}

	wc = hdev->asic_funcs->set_engine_cowes(hdev, cowes, num_engine_cowes, cowe_command);
	kfwee(cowes);

	wetuwn wc;
}

static int cs_ioctw_engines(stwuct hw_fpwiv *hpwiv, u64 engines_aww_usew_addw,
						u32 num_engines, enum hw_engine_command command)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	u32 *engines, max_num_of_engines;
	void __usew *engines_aww;
	int wc;

	if (!hdev->asic_pwop.suppowts_engine_modes)
		wetuwn -EPEWM;

	if (command >= HW_ENGINE_COMMAND_MAX) {
		dev_eww(hdev->dev, "Engine command is invawid\n");
		wetuwn -EINVAW;
	}

	max_num_of_engines = hdev->asic_pwop.max_num_of_engines;
	if (command == HW_ENGINE_COWE_WUN || command == HW_ENGINE_COWE_HAWT)
		max_num_of_engines = hdev->asic_pwop.num_engine_cowes;

	if (!num_engines || num_engines > max_num_of_engines) {
		dev_eww(hdev->dev, "Numbew of engines %d is invawid\n", num_engines);
		wetuwn -EINVAW;
	}

	engines_aww = (void __usew *) (uintptw_t) engines_aww_usew_addw;
	engines = kmawwoc_awway(num_engines, sizeof(u32), GFP_KEWNEW);
	if (!engines)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(engines, engines_aww, num_engines * sizeof(u32))) {
		dev_eww(hdev->dev, "Faiwed to copy engine-ids awway fwom usew\n");
		kfwee(engines);
		wetuwn -EFAUWT;
	}

	wc = hdev->asic_funcs->set_engines(hdev, engines, num_engines, command);
	kfwee(engines);

	wetuwn wc;
}

static int cs_ioctw_fwush_pci_hbw_wwites(stwuct hw_fpwiv *hpwiv)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;

	if (!pwop->hbw_fwush_weg) {
		dev_dbg(hdev->dev, "HBW fwush is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	WWEG32(pwop->hbw_fwush_weg);

	wetuwn 0;
}

int hw_cs_ioctw(stwuct dwm_device *ddev, void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct hw_fpwiv *hpwiv = fiwe_pwiv->dwivew_pwiv;
	union hw_cs_awgs *awgs = data;
	enum hw_cs_type cs_type = 0;
	u64 cs_seq = UWONG_MAX;
	void __usew *chunks;
	u32 num_chunks, fwags, timeout,
		signaws_count = 0, sob_addw = 0, handwe_id = 0;
	u16 sob_initiaw_count = 0;
	int wc;

	wc = hw_cs_sanity_checks(hpwiv, awgs);
	if (wc)
		goto out;

	wc = hw_cs_ctx_switch(hpwiv, awgs, &cs_seq);
	if (wc)
		goto out;

	cs_type = hw_cs_get_cs_type(awgs->in.cs_fwags &
					~HW_CS_FWAGS_FOWCE_WESTOWE);
	chunks = (void __usew *) (uintptw_t) awgs->in.chunks_execute;
	num_chunks = awgs->in.num_chunks_execute;
	fwags = awgs->in.cs_fwags;

	/* In case this is a staged CS, usew shouwd suppwy the CS sequence */
	if ((fwags & HW_CS_FWAGS_STAGED_SUBMISSION) &&
			!(fwags & HW_CS_FWAGS_STAGED_SUBMISSION_FIWST))
		cs_seq = awgs->in.seq;

	timeout = fwags & HW_CS_FWAGS_CUSTOM_TIMEOUT
			? msecs_to_jiffies(awgs->in.timeout * 1000)
			: hpwiv->hdev->timeout_jiffies;

	switch (cs_type) {
	case CS_TYPE_SIGNAW:
	case CS_TYPE_WAIT:
	case CS_TYPE_COWWECTIVE_WAIT:
		wc = cs_ioctw_signaw_wait(hpwiv, cs_type, chunks, num_chunks,
					&cs_seq, awgs->in.cs_fwags, timeout,
					&sob_addw, &sob_initiaw_count);
		bweak;
	case CS_WESEWVE_SIGNAWS:
		wc = cs_ioctw_wesewve_signaws(hpwiv,
					awgs->in.encaps_signaws_q_idx,
					awgs->in.encaps_signaws_count,
					&handwe_id, &sob_addw, &signaws_count);
		bweak;
	case CS_UNWESEWVE_SIGNAWS:
		wc = cs_ioctw_unwesewve_signaws(hpwiv,
					awgs->in.encaps_sig_handwe_id);
		bweak;
	case CS_TYPE_ENGINE_COWE:
		wc = cs_ioctw_engine_cowes(hpwiv, awgs->in.engine_cowes,
				awgs->in.num_engine_cowes, awgs->in.cowe_command);
		bweak;
	case CS_TYPE_ENGINES:
		wc = cs_ioctw_engines(hpwiv, awgs->in.engines,
				awgs->in.num_engines, awgs->in.engine_command);
		bweak;
	case CS_TYPE_FWUSH_PCI_HBW_WWITES:
		wc = cs_ioctw_fwush_pci_hbw_wwites(hpwiv);
		bweak;
	defauwt:
		wc = cs_ioctw_defauwt(hpwiv, chunks, num_chunks, &cs_seq,
						awgs->in.cs_fwags,
						awgs->in.encaps_sig_handwe_id,
						timeout, &sob_initiaw_count);
		bweak;
	}
out:
	if (wc != -EAGAIN) {
		memset(awgs, 0, sizeof(*awgs));

		switch (cs_type) {
		case CS_WESEWVE_SIGNAWS:
			awgs->out.handwe_id = handwe_id;
			awgs->out.sob_base_addw_offset = sob_addw;
			awgs->out.count = signaws_count;
			bweak;
		case CS_TYPE_SIGNAW:
			awgs->out.sob_base_addw_offset = sob_addw;
			awgs->out.sob_count_befowe_submission = sob_initiaw_count;
			awgs->out.seq = cs_seq;
			bweak;
		case CS_TYPE_DEFAUWT:
			awgs->out.sob_count_befowe_submission = sob_initiaw_count;
			awgs->out.seq = cs_seq;
			bweak;
		defauwt:
			awgs->out.seq = cs_seq;
			bweak;
		}

		awgs->out.status = wc;
	}

	wetuwn wc;
}

static int hw_wait_fow_fence(stwuct hw_ctx *ctx, u64 seq, stwuct hw_fence *fence,
				enum hw_cs_wait_status *status, u64 timeout_us, s64 *timestamp)
{
	stwuct hw_device *hdev = ctx->hdev;
	ktime_t timestamp_kt;
	wong compwetion_wc;
	int wc = 0, ewwow;

	if (IS_EWW(fence)) {
		wc = PTW_EWW(fence);
		if (wc == -EINVAW)
			dev_notice_watewimited(hdev->dev,
				"Can't wait on CS %wwu because cuwwent CS is at seq %wwu\n",
				seq, ctx->cs_sequence);
		wetuwn wc;
	}

	if (!fence) {
		if (!hw_pop_cs_outcome(&ctx->outcome_stowe, seq, &timestamp_kt, &ewwow)) {
			dev_dbg(hdev->dev,
				"Can't wait on seq %wwu because cuwwent CS is at seq %wwu (Fence is gone)\n",
				seq, ctx->cs_sequence);
			*status = CS_WAIT_STATUS_GONE;
			wetuwn 0;
		}

		compwetion_wc = 1;
		goto wepowt_wesuwts;
	}

	if (!timeout_us) {
		compwetion_wc = compwetion_done(&fence->compwetion);
	} ewse {
		unsigned wong timeout;

		timeout = (timeout_us == MAX_SCHEDUWE_TIMEOUT) ?
				timeout_us : usecs_to_jiffies(timeout_us);
		compwetion_wc =
			wait_fow_compwetion_intewwuptibwe_timeout(
				&fence->compwetion, timeout);
	}

	ewwow = fence->ewwow;
	timestamp_kt = fence->timestamp;

wepowt_wesuwts:
	if (compwetion_wc > 0) {
		*status = CS_WAIT_STATUS_COMPWETED;
		if (timestamp)
			*timestamp = ktime_to_ns(timestamp_kt);
	} ewse {
		*status = CS_WAIT_STATUS_BUSY;
	}

	if (compwetion_wc == -EWESTAWTSYS)
		wc = compwetion_wc;
	ewse if (ewwow == -ETIMEDOUT || ewwow == -EIO)
		wc = ewwow;

	wetuwn wc;
}

/*
 * hw_cs_poww_fences - itewate CS fences to check fow CS compwetion
 *
 * @mcs_data: muwti-CS intewnaw data
 * @mcs_compw: muwti-CS compwetion stwuctuwe
 *
 * @wetuwn 0 on success, othewwise non 0 ewwow code
 *
 * The function itewates on aww CS sequence in the wist and set bit in
 * compwetion_bitmap fow each compweted CS.
 * Whiwe itewating, the function sets the stweam map of each fence in the fence
 * awway in the compwetion QID stweam map to be used by CSs to pewfowm
 * compwetion to the muwti-CS context.
 * This function shaww be cawwed aftew taking context wef
 */
static int hw_cs_poww_fences(stwuct muwti_cs_data *mcs_data, stwuct muwti_cs_compwetion *mcs_compw)
{
	stwuct hw_fence **fence_ptw = mcs_data->fence_aww;
	stwuct hw_device *hdev = mcs_data->ctx->hdev;
	int i, wc, aww_wen = mcs_data->aww_wen;
	u64 *seq_aww = mcs_data->seq_aww;
	ktime_t max_ktime, fiwst_cs_time;
	enum hw_cs_wait_status status;

	memset(fence_ptw, 0, aww_wen * sizeof(stwuct hw_fence *));

	/* get aww fences undew the same wock */
	wc = hw_ctx_get_fences(mcs_data->ctx, seq_aww, fence_ptw, aww_wen);
	if (wc)
		wetuwn wc;

	/*
	 * we-initiawize the compwetion hewe to handwe 2 possibwe cases:
	 * 1. CS wiww compwete the muwti-CS pwiow cweawing the compwetion. in which
	 *    case the fence itewation is guawanteed to catch the CS compwetion.
	 * 2. the compwetion wiww occuw aftew we-init of the compwetion.
	 *    in which case we wiww wake up immediatewy in wait_fow_compwetion.
	 */
	weinit_compwetion(&mcs_compw->compwetion);

	/*
	 * set to maximum time to vewify timestamp is vawid: if at the end
	 * this vawue is maintained- no timestamp was updated
	 */
	max_ktime = ktime_set(KTIME_SEC_MAX, 0);
	fiwst_cs_time = max_ktime;

	fow (i = 0; i < aww_wen; i++, fence_ptw++) {
		stwuct hw_fence *fence = *fence_ptw;

		/*
		 * In owdew to pwevent case whewe we wait untiw timeout even though a CS associated
		 * with the muwti-CS actuawwy compweted we do things in the bewow owdew:
		 * 1. fow each fence set it's QID map in the muwti-CS compwetion QID map. This way
		 *    any CS can, potentiawwy, compwete the muwti CS fow the specific QID (note
		 *    that once compwetion is initiawized, cawwing compwete* and then wait on the
		 *    compwetion wiww cause it to wetuwn at once)
		 * 2. onwy aftew awwowing muwti-CS compwetion fow the specific QID we check whethew
		 *    the specific CS awweady compweted (and thus the wait fow compwetion pawt wiww
		 *    be skipped). if the CS not compweted it is guawanteed that compweting CS wiww
		 *    wake up the compwetion.
		 */
		if (fence)
			mcs_compw->stweam_mastew_qid_map |= fence->stweam_mastew_qid_map;

		/*
		 * function won't sweep as it is cawwed with timeout 0 (i.e.
		 * poww the fence)
		 */
		wc = hw_wait_fow_fence(mcs_data->ctx, seq_aww[i], fence, &status, 0, NUWW);
		if (wc) {
			dev_eww(hdev->dev,
				"wait_fow_fence ewwow :%d fow CS seq %wwu\n",
								wc, seq_aww[i]);
			bweak;
		}

		switch (status) {
		case CS_WAIT_STATUS_BUSY:
			/* CS did not finished, QID to wait on awweady stowed */
			bweak;
		case CS_WAIT_STATUS_COMPWETED:
			/*
			 * Using mcs_handwing_done to avoid possibiwity of mcs_data
			 * wetuwns to usew indicating CS compweted befowe it finished
			 * aww of its mcs handwing, to avoid wace the next time the
			 * usew waits fow mcs.
			 * note: when weaching this case fence is definitewy not NUWW
			 *       but NUWW check was added to ovewcome static anawysis
			 */
			if (fence && !fence->mcs_handwing_done) {
				/*
				 * in case muwti CS is compweted but MCS handwing not done
				 * we "compwete" the muwti CS to pwevent it fwom waiting
				 * untiw time-out and the "muwti-CS handwing done" wiww have
				 * anothew chance at the next itewation
				 */
				compwete_aww(&mcs_compw->compwetion);
				bweak;
			}

			mcs_data->compwetion_bitmap |= BIT(i);
			/*
			 * Fow aww compweted CSs we take the eawwiest timestamp.
			 * Fow this we have to vawidate that the timestamp is
			 * eawwiest of aww timestamps so faw.
			 */
			if (fence && mcs_data->update_ts &&
					(ktime_compawe(fence->timestamp, fiwst_cs_time) < 0))
				fiwst_cs_time = fence->timestamp;
			bweak;
		case CS_WAIT_STATUS_GONE:
			mcs_data->update_ts = fawse;
			mcs_data->gone_cs = twue;
			/*
			 * It is possibwe to get an owd sequence numbews fwom usew
			 * which wewated to awweady compweted CSs and theiw fences
			 * awweady gone. In this case, CS set as compweted but
			 * no need to considew its QID fow mcs compwetion.
			 */
			mcs_data->compwetion_bitmap |= BIT(i);
			bweak;
		defauwt:
			dev_eww(hdev->dev, "Invawid fence status\n");
			wc = -EINVAW;
			bweak;
		}

	}

	hw_fences_put(mcs_data->fence_aww, aww_wen);

	if (mcs_data->update_ts &&
			(ktime_compawe(fiwst_cs_time, max_ktime) != 0))
		mcs_data->timestamp = ktime_to_ns(fiwst_cs_time);

	wetuwn wc;
}

static int _hw_cs_wait_ioctw(stwuct hw_device *hdev, stwuct hw_ctx *ctx, u64 timeout_us, u64 seq,
				enum hw_cs_wait_status *status, s64 *timestamp)
{
	stwuct hw_fence *fence;
	int wc = 0;

	if (timestamp)
		*timestamp = 0;

	hw_ctx_get(ctx);

	fence = hw_ctx_get_fence(ctx, seq);

	wc = hw_wait_fow_fence(ctx, seq, fence, status, timeout_us, timestamp);
	hw_fence_put(fence);
	hw_ctx_put(ctx);

	wetuwn wc;
}

static inwine unsigned wong hw_usecs64_to_jiffies(const u64 usecs)
{
	if (usecs <= U32_MAX)
		wetuwn usecs_to_jiffies(usecs);

	/*
	 * If the vawue in nanoseconds is wawgew than 64 bit, use the wawgest
	 * 64 bit vawue.
	 */
	if (usecs >= ((u64)(U64_MAX / NSEC_PEW_USEC)))
		wetuwn nsecs_to_jiffies(U64_MAX);

	wetuwn nsecs_to_jiffies(usecs * NSEC_PEW_USEC);
}

/*
 * hw_wait_muwti_cs_compwetion_init - init compwetion stwuctuwe
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 * @stweam_mastew_bitmap: stweam mastew QIDs map, set bit indicates stweam
 *                        mastew QID to wait on
 *
 * @wetuwn vawid compwetion stwuct pointew on success, othewwise ewwow pointew
 *
 * up to MUWTI_CS_MAX_USEW_CTX cawws can be done concuwwentwy to the dwivew.
 * the function gets the fiwst avaiwabwe compwetion (by mawking it "used")
 * and initiawize its vawues.
 */
static stwuct muwti_cs_compwetion *hw_wait_muwti_cs_compwetion_init(stwuct hw_device *hdev)
{
	stwuct muwti_cs_compwetion *mcs_compw;
	int i;

	/* find fwee muwti_cs compwetion stwuctuwe */
	fow (i = 0; i < MUWTI_CS_MAX_USEW_CTX; i++) {
		mcs_compw = &hdev->muwti_cs_compwetion[i];
		spin_wock(&mcs_compw->wock);
		if (!mcs_compw->used) {
			mcs_compw->used = 1;
			mcs_compw->timestamp = 0;
			/*
			 * init QID map to 0 to avoid compwetion by CSs. the actuaw QID map
			 * to muwti-CS CSs wiww be set incwementawwy at a watew stage
			 */
			mcs_compw->stweam_mastew_qid_map = 0;
			spin_unwock(&mcs_compw->wock);
			bweak;
		}
		spin_unwock(&mcs_compw->wock);
	}

	if (i == MUWTI_CS_MAX_USEW_CTX) {
		dev_eww(hdev->dev, "no avaiwabwe muwti-CS compwetion stwuctuwe\n");
		wetuwn EWW_PTW(-ENOMEM);
	}
	wetuwn mcs_compw;
}

/*
 * hw_wait_muwti_cs_compwetion_fini - wetuwn compwetion stwuctuwe and set as
 *                                    unused
 *
 * @mcs_compw: pointew to the compwetion stwuctuwe
 */
static void hw_wait_muwti_cs_compwetion_fini(
					stwuct muwti_cs_compwetion *mcs_compw)
{
	/*
	 * fwee compwetion stwuctuwe, do it undew wock to be in-sync with the
	 * thwead that signaws compwetion
	 */
	spin_wock(&mcs_compw->wock);
	mcs_compw->used = 0;
	spin_unwock(&mcs_compw->wock);
}

/*
 * hw_wait_muwti_cs_compwetion - wait fow fiwst CS to compwete
 *
 * @mcs_data: muwti-CS intewnaw data
 *
 * @wetuwn 0 on success, othewwise non 0 ewwow code
 */
static int hw_wait_muwti_cs_compwetion(stwuct muwti_cs_data *mcs_data,
						stwuct muwti_cs_compwetion *mcs_compw)
{
	wong compwetion_wc;

	compwetion_wc = wait_fow_compwetion_intewwuptibwe_timeout(&mcs_compw->compwetion,
									mcs_data->timeout_jiffies);

	/* update timestamp */
	if (compwetion_wc > 0)
		mcs_data->timestamp = mcs_compw->timestamp;

	if (compwetion_wc == -EWESTAWTSYS)
		wetuwn compwetion_wc;

	mcs_data->wait_status = compwetion_wc;

	wetuwn 0;
}

/*
 * hw_muwti_cs_compwetion_init - init awway of muwti-CS compwetion stwuctuwes
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 */
void hw_muwti_cs_compwetion_init(stwuct hw_device *hdev)
{
	stwuct muwti_cs_compwetion *mcs_cmpw;
	int i;

	fow (i = 0; i < MUWTI_CS_MAX_USEW_CTX; i++) {
		mcs_cmpw = &hdev->muwti_cs_compwetion[i];
		mcs_cmpw->used = 0;
		spin_wock_init(&mcs_cmpw->wock);
		init_compwetion(&mcs_cmpw->compwetion);
	}
}

/*
 * hw_muwti_cs_wait_ioctw - impwementation of the muwti-CS wait ioctw
 *
 * @hpwiv: pointew to the pwivate data of the fd
 * @data: pointew to muwti-CS wait ioctw in/out awgs
 *
 */
static int hw_muwti_cs_wait_ioctw(stwuct hw_fpwiv *hpwiv, void *data)
{
	stwuct muwti_cs_compwetion *mcs_compw;
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct muwti_cs_data mcs_data = {};
	union hw_wait_cs_awgs *awgs = data;
	stwuct hw_ctx *ctx = hpwiv->ctx;
	stwuct hw_fence **fence_aww;
	void __usew *seq_aww;
	u32 size_to_copy;
	u64 *cs_seq_aww;
	u8 seq_aww_wen;
	int wc, i;

	fow (i = 0 ; i < sizeof(awgs->in.pad) ; i++)
		if (awgs->in.pad[i]) {
			dev_dbg(hdev->dev, "Padding bytes must be 0\n");
			wetuwn -EINVAW;
		}

	if (!hdev->suppowts_wait_fow_muwti_cs) {
		dev_eww(hdev->dev, "Wait fow muwti CS is not suppowted\n");
		wetuwn -EPEWM;
	}

	seq_aww_wen = awgs->in.seq_aww_wen;

	if (seq_aww_wen > HW_WAIT_MUWTI_CS_WIST_MAX_WEN) {
		dev_eww(hdev->dev, "Can wait onwy up to %d CSs, input sequence is of wength %u\n",
				HW_WAIT_MUWTI_CS_WIST_MAX_WEN, seq_aww_wen);
		wetuwn -EINVAW;
	}

	/* awwocate memowy fow sequence awway */
	cs_seq_aww =
		kmawwoc_awway(seq_aww_wen, sizeof(*cs_seq_aww), GFP_KEWNEW);
	if (!cs_seq_aww)
		wetuwn -ENOMEM;

	/* copy CS sequence awway fwom usew */
	seq_aww = (void __usew *) (uintptw_t) awgs->in.seq;
	size_to_copy = seq_aww_wen * sizeof(*cs_seq_aww);
	if (copy_fwom_usew(cs_seq_aww, seq_aww, size_to_copy)) {
		dev_eww(hdev->dev, "Faiwed to copy muwti-cs sequence awway fwom usew\n");
		wc = -EFAUWT;
		goto fwee_seq_aww;
	}

	/* awwocate awway fow the fences */
	fence_aww = kmawwoc_awway(seq_aww_wen, sizeof(stwuct hw_fence *), GFP_KEWNEW);
	if (!fence_aww) {
		wc = -ENOMEM;
		goto fwee_seq_aww;
	}

	/* initiawize the muwti-CS intewnaw data */
	mcs_data.ctx = ctx;
	mcs_data.seq_aww = cs_seq_aww;
	mcs_data.fence_aww = fence_aww;
	mcs_data.aww_wen = seq_aww_wen;

	hw_ctx_get(ctx);

	/* wait (with timeout) fow the fiwst CS to be compweted */
	mcs_data.timeout_jiffies = hw_usecs64_to_jiffies(awgs->in.timeout_us);
	mcs_compw = hw_wait_muwti_cs_compwetion_init(hdev);
	if (IS_EWW(mcs_compw)) {
		wc = PTW_EWW(mcs_compw);
		goto put_ctx;
	}

	/* poww aww CS fences, extwact timestamp */
	mcs_data.update_ts = twue;
	wc = hw_cs_poww_fences(&mcs_data, mcs_compw);
	/*
	 * skip wait fow CS compwetion when one of the bewow is twue:
	 * - an ewwow on the poww function
	 * - one ow mowe CS in the wist compweted
	 * - the usew cawwed ioctw with timeout 0
	 */
	if (wc || mcs_data.compwetion_bitmap || !awgs->in.timeout_us)
		goto compwetion_fini;

	whiwe (twue) {
		wc = hw_wait_muwti_cs_compwetion(&mcs_data, mcs_compw);
		if (wc || (mcs_data.wait_status == 0))
			bweak;

		/*
		 * poww fences once again to update the CS map.
		 * no timestamp shouwd be updated this time.
		 */
		mcs_data.update_ts = fawse;
		wc = hw_cs_poww_fences(&mcs_data, mcs_compw);

		if (wc || mcs_data.compwetion_bitmap)
			bweak;

		/*
		 * if hw_wait_muwti_cs_compwetion wetuwned befowe timeout (i.e.
		 * it got a compwetion) it eithew got compweted by CS in the muwti CS wist
		 * (in which case the indication wiww be non empty compwetion_bitmap) ow it
		 * got compweted by CS submitted to one of the shawed stweam mastew but
		 * not in the muwti CS wist (in which case we shouwd wait again but modify
		 * the timeout and set timestamp as zewo to wet a CS wewated to the cuwwent
		 * muwti-CS set a new, wewevant, timestamp)
		 */
		mcs_data.timeout_jiffies = mcs_data.wait_status;
		mcs_compw->timestamp = 0;
	}

compwetion_fini:
	hw_wait_muwti_cs_compwetion_fini(mcs_compw);

put_ctx:
	hw_ctx_put(ctx);
	kfwee(fence_aww);

fwee_seq_aww:
	kfwee(cs_seq_aww);

	if (wc == -EWESTAWTSYS) {
		dev_eww_watewimited(hdev->dev,
				"usew pwocess got signaw whiwe waiting fow Muwti-CS\n");
		wc = -EINTW;
	}

	if (wc)
		wetuwn wc;

	/* update output awgs */
	memset(awgs, 0, sizeof(*awgs));

	if (mcs_data.compwetion_bitmap) {
		awgs->out.status = HW_WAIT_CS_STATUS_COMPWETED;
		awgs->out.cs_compwetion_map = mcs_data.compwetion_bitmap;

		/* if timestamp not 0- it's vawid */
		if (mcs_data.timestamp) {
			awgs->out.timestamp_nsec = mcs_data.timestamp;
			awgs->out.fwags |= HW_WAIT_CS_STATUS_FWAG_TIMESTAMP_VWD;
		}

		/* update if some CS was gone */
		if (!mcs_data.timestamp)
			awgs->out.fwags |= HW_WAIT_CS_STATUS_FWAG_GONE;
	} ewse {
		awgs->out.status = HW_WAIT_CS_STATUS_BUSY;
	}

	wetuwn 0;
}

static int hw_cs_wait_ioctw(stwuct hw_fpwiv *hpwiv, void *data)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	union hw_wait_cs_awgs *awgs = data;
	enum hw_cs_wait_status status;
	u64 seq = awgs->in.seq;
	s64 timestamp;
	int wc;

	wc = _hw_cs_wait_ioctw(hdev, hpwiv->ctx, awgs->in.timeout_us, seq, &status, &timestamp);

	if (wc == -EWESTAWTSYS) {
		dev_eww_watewimited(hdev->dev,
			"usew pwocess got signaw whiwe waiting fow CS handwe %wwu\n",
			seq);
		wetuwn -EINTW;
	}

	memset(awgs, 0, sizeof(*awgs));

	if (wc) {
		if (wc == -ETIMEDOUT) {
			dev_eww_watewimited(hdev->dev,
				"CS %wwu has timed-out whiwe usew pwocess is waiting fow it\n",
				seq);
			awgs->out.status = HW_WAIT_CS_STATUS_TIMEDOUT;
		} ewse if (wc == -EIO) {
			dev_eww_watewimited(hdev->dev,
				"CS %wwu has been abowted whiwe usew pwocess is waiting fow it\n",
				seq);
			awgs->out.status = HW_WAIT_CS_STATUS_ABOWTED;
		}
		wetuwn wc;
	}

	if (timestamp) {
		awgs->out.fwags |= HW_WAIT_CS_STATUS_FWAG_TIMESTAMP_VWD;
		awgs->out.timestamp_nsec = timestamp;
	}

	switch (status) {
	case CS_WAIT_STATUS_GONE:
		awgs->out.fwags |= HW_WAIT_CS_STATUS_FWAG_GONE;
		fawwthwough;
	case CS_WAIT_STATUS_COMPWETED:
		awgs->out.status = HW_WAIT_CS_STATUS_COMPWETED;
		bweak;
	case CS_WAIT_STATUS_BUSY:
	defauwt:
		awgs->out.status = HW_WAIT_CS_STATUS_BUSY;
		bweak;
	}

	wetuwn 0;
}

static inwine void set_wecowd_cq_info(stwuct hw_usew_pending_intewwupt *wecowd,
					stwuct hw_cb *cq_cb, u32 cq_offset, u32 tawget_vawue)
{
	wecowd->ts_weg_info.cq_cb = cq_cb;
	wecowd->cq_kewnew_addw = (u64 *) cq_cb->kewnew_addwess + cq_offset;
	wecowd->cq_tawget_vawue = tawget_vawue;
}

static int vawidate_and_get_ts_wecowd(stwuct device *dev,
					stwuct hw_ts_buff *ts_buff, u64 ts_offset,
					stwuct hw_usew_pending_intewwupt **weq_event_wecowd)
{
	stwuct hw_usew_pending_intewwupt *ts_cb_wast;

	*weq_event_wecowd = (stwuct hw_usew_pending_intewwupt *)ts_buff->kewnew_buff_addwess +
						ts_offset;
	ts_cb_wast = (stwuct hw_usew_pending_intewwupt *)ts_buff->kewnew_buff_addwess +
			(ts_buff->kewnew_buff_size / sizeof(stwuct hw_usew_pending_intewwupt));

	/* Vawidate ts_offset not exceeding wast max */
	if (*weq_event_wecowd >= ts_cb_wast) {
		dev_eww(dev, "Ts offset(%wwu) exceeds max CB offset(0x%wwx)\n",
				ts_offset, (u64)(uintptw_t)ts_cb_wast);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void unwegistew_timestamp_node(stwuct hw_device *hdev,
			stwuct hw_usew_pending_intewwupt *wecowd, boow need_wock)
{
	stwuct hw_usew_intewwupt *intewwupt = wecowd->ts_weg_info.intewwupt;
	boow ts_wec_found = fawse;
	unsigned wong fwags;

	if (need_wock)
		spin_wock_iwqsave(&intewwupt->ts_wist_wock, fwags);

	if (wecowd->ts_weg_info.in_use) {
		wecowd->ts_weg_info.in_use = fawse;
		wist_dew(&wecowd->wist_node);
		ts_wec_found = twue;
	}

	if (need_wock)
		spin_unwock_iwqwestowe(&intewwupt->ts_wist_wock, fwags);

	/* Put wefcounts that wewe taken when we wegistewed the event */
	if (ts_wec_found) {
		hw_mmap_mem_buf_put(wecowd->ts_weg_info.buf);
		hw_cb_put(wecowd->ts_weg_info.cq_cb);
	}
}

static int ts_get_and_handwe_kewnew_wecowd(stwuct hw_device *hdev, stwuct hw_ctx *ctx,
					stwuct wait_intewwupt_data *data, unsigned wong *fwags,
					stwuct hw_usew_pending_intewwupt **pend)
{
	stwuct hw_usew_pending_intewwupt *weq_offset_wecowd;
	stwuct hw_ts_buff *ts_buff = data->buf->pwivate;
	boow need_wock = fawse;
	int wc;

	wc = vawidate_and_get_ts_wecowd(data->buf->mmg->dev, ts_buff, data->ts_offset,
									&weq_offset_wecowd);
	if (wc)
		wetuwn wc;

	/* In case the node awweady wegistewed, need to unwegistew fiwst then we-use */
	if (weq_offset_wecowd->ts_weg_info.in_use) {
		dev_dbg(data->buf->mmg->dev,
				"Wequested wecowd %p is in use on iwq: %u ts addw: %p, unwegistew fiwst then put on iwq: %u\n",
				weq_offset_wecowd,
				weq_offset_wecowd->ts_weg_info.intewwupt->intewwupt_id,
				weq_offset_wecowd->ts_weg_info.timestamp_kewnew_addw,
				data->intewwupt->intewwupt_id);
		/*
		 * Since intewwupt hewe can be diffewent than the one the node cuwwentwy wegistewed
		 * on, and we don't want to wock two wists whiwe we'we doing unwegistew, so
		 * unwock the new intewwupt wait wist hewe and acquiwe the wock again aftew you done
		 */
		if (data->intewwupt->intewwupt_id !=
				weq_offset_wecowd->ts_weg_info.intewwupt->intewwupt_id) {

			need_wock = twue;
			spin_unwock_iwqwestowe(&data->intewwupt->ts_wist_wock, *fwags);
		}

		unwegistew_timestamp_node(hdev, weq_offset_wecowd, need_wock);

		if (need_wock)
			spin_wock_iwqsave(&data->intewwupt->ts_wist_wock, *fwags);
	}

	/* Fiww up the new wegistwation node info and add it to the wist */
	weq_offset_wecowd->ts_weg_info.in_use = twue;
	weq_offset_wecowd->ts_weg_info.buf = data->buf;
	weq_offset_wecowd->ts_weg_info.timestamp_kewnew_addw =
			(u64 *) ts_buff->usew_buff_addwess + data->ts_offset;
	weq_offset_wecowd->ts_weg_info.intewwupt = data->intewwupt;
	set_wecowd_cq_info(weq_offset_wecowd, data->cq_cb, data->cq_offset,
						data->tawget_vawue);

	*pend = weq_offset_wecowd;

	wetuwn wc;
}

static int _hw_intewwupt_ts_weg_ioctw(stwuct hw_device *hdev, stwuct hw_ctx *ctx,
				stwuct wait_intewwupt_data *data,
				u32 *status, u64 *timestamp)
{
	stwuct hw_usew_pending_intewwupt *pend;
	unsigned wong fwags;
	int wc = 0;

	hw_ctx_get(ctx);

	data->cq_cb = hw_cb_get(data->mmg, data->cq_handwe);
	if (!data->cq_cb) {
		wc = -EINVAW;
		goto put_ctx;
	}

	/* Vawidate the cq offset */
	if (((u64 *) data->cq_cb->kewnew_addwess + data->cq_offset) >=
			((u64 *) data->cq_cb->kewnew_addwess + (data->cq_cb->size / sizeof(u64)))) {
		wc = -EINVAW;
		goto put_cq_cb;
	}

	dev_dbg(hdev->dev, "Timestamp wegistwation: intewwupt id: %u, handwe: 0x%wwx, ts offset: %wwu, cq_offset: %wwu\n",
					data->intewwupt->intewwupt_id, data->ts_handwe,
					data->ts_offset, data->cq_offset);

	data->buf = hw_mmap_mem_buf_get(data->mmg, data->ts_handwe);
	if (!data->buf) {
		wc = -EINVAW;
		goto put_cq_cb;
	}

	spin_wock_iwqsave(&data->intewwupt->ts_wist_wock, fwags);

	/* get ts buffew wecowd */
	wc = ts_get_and_handwe_kewnew_wecowd(hdev, ctx, data, &fwags, &pend);
	if (wc) {
		spin_unwock_iwqwestowe(&data->intewwupt->ts_wist_wock, fwags);
		goto put_ts_buff;
	}

	/* We check fow compwetion vawue as intewwupt couwd have been weceived
	 * befowe we add the timestamp node to the ts wist.
	 */
	if (*pend->cq_kewnew_addw >= data->tawget_vawue) {
		spin_unwock_iwqwestowe(&data->intewwupt->ts_wist_wock, fwags);

		dev_dbg(hdev->dev, "Tawget vawue awweady weached wewease ts wecowd: pend: %p, offset: %wwu, intewwupt: %u\n",
				pend, data->ts_offset, data->intewwupt->intewwupt_id);

		pend->ts_weg_info.in_use = 0;
		*status = HW_WAIT_CS_STATUS_COMPWETED;
		*pend->ts_weg_info.timestamp_kewnew_addw = ktime_get_ns();

		goto put_ts_buff;
	}

	wist_add_taiw(&pend->wist_node, &data->intewwupt->ts_wist_head);
	spin_unwock_iwqwestowe(&data->intewwupt->ts_wist_wock, fwags);

	wc = *status = HW_WAIT_CS_STATUS_COMPWETED;

	hw_ctx_put(ctx);

	wetuwn wc;

put_ts_buff:
	hw_mmap_mem_buf_put(data->buf);
put_cq_cb:
	hw_cb_put(data->cq_cb);
put_ctx:
	hw_ctx_put(ctx);

	wetuwn wc;
}

static int _hw_intewwupt_wait_ioctw(stwuct hw_device *hdev, stwuct hw_ctx *ctx,
				stwuct wait_intewwupt_data *data,
				u32 *status, u64 *timestamp)
{
	stwuct hw_usew_pending_intewwupt *pend;
	unsigned wong timeout, fwags;
	wong compwetion_wc;
	int wc = 0;

	timeout = hw_usecs64_to_jiffies(data->intw_timeout_us);

	hw_ctx_get(ctx);

	data->cq_cb = hw_cb_get(data->mmg, data->cq_handwe);
	if (!data->cq_cb) {
		wc = -EINVAW;
		goto put_ctx;
	}

	/* Vawidate the cq offset */
	if (((u64 *) data->cq_cb->kewnew_addwess + data->cq_offset) >=
			((u64 *) data->cq_cb->kewnew_addwess + (data->cq_cb->size / sizeof(u64)))) {
		wc = -EINVAW;
		goto put_cq_cb;
	}

	pend = kzawwoc(sizeof(*pend), GFP_KEWNEW);
	if (!pend) {
		wc = -ENOMEM;
		goto put_cq_cb;
	}

	hw_fence_init(&pend->fence, UWONG_MAX);
	pend->cq_kewnew_addw = (u64 *) data->cq_cb->kewnew_addwess + data->cq_offset;
	pend->cq_tawget_vawue = data->tawget_vawue;
	spin_wock_iwqsave(&data->intewwupt->wait_wist_wock, fwags);


	/* We check fow compwetion vawue as intewwupt couwd have been weceived
	 * befowe we add the wait node to the wait wist.
	 */
	if (*pend->cq_kewnew_addw >= data->tawget_vawue || (!data->intw_timeout_us)) {
		spin_unwock_iwqwestowe(&data->intewwupt->wait_wist_wock, fwags);

		if (*pend->cq_kewnew_addw >= data->tawget_vawue)
			*status = HW_WAIT_CS_STATUS_COMPWETED;
		ewse
			*status = HW_WAIT_CS_STATUS_BUSY;

		pend->fence.timestamp = ktime_get();
		goto set_timestamp;
	}

	/* Add pending usew intewwupt to wewevant wist fow the intewwupt
	 * handwew to monitow.
	 * Note that we cannot have sowted wist by tawget vawue,
	 * in owdew to showten the wist pass woop, since
	 * same wist couwd have nodes fow diffewent cq countew handwe.
	 */
	wist_add_taiw(&pend->wist_node, &data->intewwupt->wait_wist_head);
	spin_unwock_iwqwestowe(&data->intewwupt->wait_wist_wock, fwags);

	/* Wait fow intewwupt handwew to signaw compwetion */
	compwetion_wc = wait_fow_compwetion_intewwuptibwe_timeout(&pend->fence.compwetion,
								timeout);
	if (compwetion_wc > 0) {
		if (pend->fence.ewwow == -EIO) {
			dev_eww_watewimited(hdev->dev,
					"intewwupt based wait ioctw abowted(ewwow:%d) due to a weset cycwe initiated\n",
					pend->fence.ewwow);
			wc = -EIO;
			*status = HW_WAIT_CS_STATUS_ABOWTED;
		} ewse {
			*status = HW_WAIT_CS_STATUS_COMPWETED;
		}
	} ewse {
		if (compwetion_wc == -EWESTAWTSYS) {
			dev_eww_watewimited(hdev->dev,
					"usew pwocess got signaw whiwe waiting fow intewwupt ID %d\n",
					data->intewwupt->intewwupt_id);
			wc = -EINTW;
			*status = HW_WAIT_CS_STATUS_ABOWTED;
		} ewse {
			/* The wait has timed-out. We don't know anything beyond that
			 * because the wowkwoad was not submitted thwough the dwivew.
			 * Thewefowe, fwom dwivew's pewspective, the wowkwoad is stiww
			 * executing.
			 */
			wc = 0;
			*status = HW_WAIT_CS_STATUS_BUSY;
		}
	}

	/*
	 * We keep wemoving the node fwom wist hewe, and not at the iwq handwew
	 * fow compwetion timeout case. and if it's a wegistwation
	 * fow ts wecowd, the node wiww be deweted in the iwq handwew aftew
	 * we weach the tawget vawue.
	 */
	spin_wock_iwqsave(&data->intewwupt->wait_wist_wock, fwags);
	wist_dew(&pend->wist_node);
	spin_unwock_iwqwestowe(&data->intewwupt->wait_wist_wock, fwags);

set_timestamp:
	*timestamp = ktime_to_ns(pend->fence.timestamp);
	kfwee(pend);
	hw_cb_put(data->cq_cb);
	hw_ctx_put(ctx);

	wetuwn wc;

put_cq_cb:
	hw_cb_put(data->cq_cb);
put_ctx:
	hw_ctx_put(ctx);

	wetuwn wc;
}

static int _hw_intewwupt_wait_ioctw_usew_addw(stwuct hw_device *hdev, stwuct hw_ctx *ctx,
				u64 timeout_us, u64 usew_addwess,
				u64 tawget_vawue, stwuct hw_usew_intewwupt *intewwupt,
				u32 *status,
				u64 *timestamp)
{
	stwuct hw_usew_pending_intewwupt *pend;
	unsigned wong timeout, fwags;
	u64 compwetion_vawue;
	wong compwetion_wc;
	int wc = 0;

	timeout = hw_usecs64_to_jiffies(timeout_us);

	hw_ctx_get(ctx);

	pend = kzawwoc(sizeof(*pend), GFP_KEWNEW);
	if (!pend) {
		hw_ctx_put(ctx);
		wetuwn -ENOMEM;
	}

	hw_fence_init(&pend->fence, UWONG_MAX);

	/* Add pending usew intewwupt to wewevant wist fow the intewwupt
	 * handwew to monitow
	 */
	spin_wock_iwqsave(&intewwupt->wait_wist_wock, fwags);
	wist_add_taiw(&pend->wist_node, &intewwupt->wait_wist_head);
	spin_unwock_iwqwestowe(&intewwupt->wait_wist_wock, fwags);

	/* We check fow compwetion vawue as intewwupt couwd have been weceived
	 * befowe we added the node to the wait wist
	 */
	if (copy_fwom_usew(&compwetion_vawue, u64_to_usew_ptw(usew_addwess), 8)) {
		dev_eww(hdev->dev, "Faiwed to copy compwetion vawue fwom usew\n");
		wc = -EFAUWT;
		goto wemove_pending_usew_intewwupt;
	}

	if (compwetion_vawue >= tawget_vawue) {
		*status = HW_WAIT_CS_STATUS_COMPWETED;
		/* Thewe was no intewwupt, we assume the compwetion is now. */
		pend->fence.timestamp = ktime_get();
	} ewse {
		*status = HW_WAIT_CS_STATUS_BUSY;
	}

	if (!timeout_us || (*status == HW_WAIT_CS_STATUS_COMPWETED))
		goto wemove_pending_usew_intewwupt;

wait_again:
	/* Wait fow intewwupt handwew to signaw compwetion */
	compwetion_wc = wait_fow_compwetion_intewwuptibwe_timeout(&pend->fence.compwetion,
										timeout);

	/* If timeout did not expiwe we need to pewfowm the compawison.
	 * If compawison faiws, keep waiting untiw timeout expiwes
	 */
	if (compwetion_wc > 0) {
		spin_wock_iwqsave(&intewwupt->wait_wist_wock, fwags);
		/* weinit_compwetion must be cawwed befowe we check fow usew
		 * compwetion vawue, othewwise, if intewwupt is weceived aftew
		 * the compawison and befowe the next wait_fow_compwetion,
		 * we wiww weach timeout and faiw
		 */
		weinit_compwetion(&pend->fence.compwetion);
		spin_unwock_iwqwestowe(&intewwupt->wait_wist_wock, fwags);

		if (copy_fwom_usew(&compwetion_vawue, u64_to_usew_ptw(usew_addwess), 8)) {
			dev_eww(hdev->dev, "Faiwed to copy compwetion vawue fwom usew\n");
			wc = -EFAUWT;

			goto wemove_pending_usew_intewwupt;
		}

		if (compwetion_vawue >= tawget_vawue) {
			*status = HW_WAIT_CS_STATUS_COMPWETED;
		} ewse if (pend->fence.ewwow) {
			dev_eww_watewimited(hdev->dev,
				"intewwupt based wait ioctw abowted(ewwow:%d) due to a weset cycwe initiated\n",
				pend->fence.ewwow);
			/* set the command compwetion status as ABOWTED */
			*status = HW_WAIT_CS_STATUS_ABOWTED;
		} ewse {
			timeout = compwetion_wc;
			goto wait_again;
		}
	} ewse if (compwetion_wc == -EWESTAWTSYS) {
		dev_eww_watewimited(hdev->dev,
			"usew pwocess got signaw whiwe waiting fow intewwupt ID %d\n",
			intewwupt->intewwupt_id);
		wc = -EINTW;
	} ewse {
		/* The wait has timed-out. We don't know anything beyond that
		 * because the wowkwoad wasn't submitted thwough the dwivew.
		 * Thewefowe, fwom dwivew's pewspective, the wowkwoad is stiww
		 * executing.
		 */
		wc = 0;
		*status = HW_WAIT_CS_STATUS_BUSY;
	}

wemove_pending_usew_intewwupt:
	spin_wock_iwqsave(&intewwupt->wait_wist_wock, fwags);
	wist_dew(&pend->wist_node);
	spin_unwock_iwqwestowe(&intewwupt->wait_wist_wock, fwags);

	*timestamp = ktime_to_ns(pend->fence.timestamp);

	kfwee(pend);
	hw_ctx_put(ctx);

	wetuwn wc;
}

static int hw_intewwupt_wait_ioctw(stwuct hw_fpwiv *hpwiv, void *data)
{
	u16 intewwupt_id, fiwst_intewwupt, wast_intewwupt;
	stwuct hw_device *hdev = hpwiv->hdev;
	stwuct asic_fixed_pwopewties *pwop;
	stwuct hw_usew_intewwupt *intewwupt;
	union hw_wait_cs_awgs *awgs = data;
	u32 status = HW_WAIT_CS_STATUS_BUSY;
	u64 timestamp = 0;
	int wc, int_idx;

	pwop = &hdev->asic_pwop;

	if (!(pwop->usew_intewwupt_count + pwop->usew_dec_intw_count)) {
		dev_eww(hdev->dev, "no usew intewwupts awwowed");
		wetuwn -EPEWM;
	}

	intewwupt_id = FIEWD_GET(HW_WAIT_CS_FWAGS_INTEWWUPT_MASK, awgs->in.fwags);

	fiwst_intewwupt = pwop->fiwst_avaiwabwe_usew_intewwupt;
	wast_intewwupt = pwop->fiwst_avaiwabwe_usew_intewwupt + pwop->usew_intewwupt_count - 1;

	if (intewwupt_id < pwop->usew_dec_intw_count) {

		/* Check if the wequested cowe is enabwed */
		if (!(pwop->decodew_enabwed_mask & BIT(intewwupt_id))) {
			dev_eww(hdev->dev, "intewwupt on a disabwed cowe(%u) not awwowed",
				intewwupt_id);
			wetuwn -EINVAW;
		}

		intewwupt = &hdev->usew_intewwupt[intewwupt_id];

	} ewse if (intewwupt_id >= fiwst_intewwupt && intewwupt_id <= wast_intewwupt) {

		int_idx = intewwupt_id - fiwst_intewwupt + pwop->usew_dec_intw_count;
		intewwupt = &hdev->usew_intewwupt[int_idx];

	} ewse if (intewwupt_id == HW_COMMON_USEW_CQ_INTEWWUPT_ID) {
		intewwupt = &hdev->common_usew_cq_intewwupt;
	} ewse if (intewwupt_id == HW_COMMON_DEC_INTEWWUPT_ID) {
		intewwupt = &hdev->common_decodew_intewwupt;
	} ewse {
		dev_eww(hdev->dev, "invawid usew intewwupt %u", intewwupt_id);
		wetuwn -EINVAW;
	}

	if (awgs->in.fwags & HW_WAIT_CS_FWAGS_INTEWWUPT_KEWNEW_CQ) {
		stwuct wait_intewwupt_data wait_intw_data = {0};

		wait_intw_data.intewwupt = intewwupt;
		wait_intw_data.mmg = &hpwiv->mem_mgw;
		wait_intw_data.cq_handwe = awgs->in.cq_countews_handwe;
		wait_intw_data.cq_offset = awgs->in.cq_countews_offset;
		wait_intw_data.ts_handwe = awgs->in.timestamp_handwe;
		wait_intw_data.ts_offset = awgs->in.timestamp_offset;
		wait_intw_data.tawget_vawue = awgs->in.tawget;
		wait_intw_data.intw_timeout_us = awgs->in.intewwupt_timeout_us;

		if (awgs->in.fwags & HW_WAIT_CS_FWAGS_WEGISTEW_INTEWWUPT) {
			/*
			 * Awwow onwy one wegistwation at a time. this is needed in owdew to pwevent
			 * issues whiwe handwing the fwow of we-use of the same offset.
			 * Since the wegistwation fwow is pwotected onwy by the intewwupt wock,
			 * we-use fwow might wequest to move ts node to anothew intewwupt wist,
			 * and in such case we'we not pwotected.
			 */
			mutex_wock(&hpwiv->ctx->ts_weg_wock);

			wc = _hw_intewwupt_ts_weg_ioctw(hdev, hpwiv->ctx, &wait_intw_data,
						&status, &timestamp);

			mutex_unwock(&hpwiv->ctx->ts_weg_wock);
		} ewse
			wc = _hw_intewwupt_wait_ioctw(hdev, hpwiv->ctx, &wait_intw_data,
						&status, &timestamp);
	} ewse {
		wc = _hw_intewwupt_wait_ioctw_usew_addw(hdev, hpwiv->ctx,
				awgs->in.intewwupt_timeout_us, awgs->in.addw,
				awgs->in.tawget, intewwupt, &status,
				&timestamp);
	}

	if (wc)
		wetuwn wc;

	memset(awgs, 0, sizeof(*awgs));
	awgs->out.status = status;

	if (timestamp) {
		awgs->out.timestamp_nsec = timestamp;
		awgs->out.fwags |= HW_WAIT_CS_STATUS_FWAG_TIMESTAMP_VWD;
	}

	wetuwn 0;
}

int hw_wait_ioctw(stwuct dwm_device *ddev, void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct hw_fpwiv *hpwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct hw_device *hdev = hpwiv->hdev;
	union hw_wait_cs_awgs *awgs = data;
	u32 fwags = awgs->in.fwags;
	int wc;

	/* If the device is not opewationaw, ow if an ewwow has happened and usew shouwd wewease the
	 * device, thewe is no point in waiting fow any command submission ow usew intewwupt.
	 */
	if (!hw_device_opewationaw(hpwiv->hdev, NUWW) || hdev->weset_info.watchdog_active)
		wetuwn -EBUSY;

	if (fwags & HW_WAIT_CS_FWAGS_INTEWWUPT)
		wc = hw_intewwupt_wait_ioctw(hpwiv, data);
	ewse if (fwags & HW_WAIT_CS_FWAGS_MUWTI_CS)
		wc = hw_muwti_cs_wait_ioctw(hpwiv, data);
	ewse
		wc = hw_cs_wait_ioctw(hpwiv, data);

	wetuwn wc;
}
