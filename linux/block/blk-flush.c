// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions to sequence PWEFWUSH and FUA wwites.
 *
 * Copywight (C) 2011		Max Pwanck Institute fow Gwavitationaw Physics
 * Copywight (C) 2011		Tejun Heo <tj@kewnew.owg>
 *
 * WEQ_{PWEFWUSH|FUA} wequests awe decomposed to sequences consisted of thwee
 * optionaw steps - PWEFWUSH, DATA and POSTFWUSH - accowding to the wequest
 * pwopewties and hawdwawe capabiwity.
 *
 * If a wequest doesn't have data, onwy WEQ_PWEFWUSH makes sense, which
 * indicates a simpwe fwush wequest.  If thewe is data, WEQ_PWEFWUSH indicates
 * that the device cache shouwd be fwushed befowe the data is executed, and
 * WEQ_FUA means that the data must be on non-vowatiwe media on wequest
 * compwetion.
 *
 * If the device doesn't have wwiteback cache, PWEFWUSH and FUA don't make any
 * diffewence.  The wequests awe eithew compweted immediatewy if thewe's no data
 * ow executed as nowmaw wequests othewwise.
 *
 * If the device has wwiteback cache and suppowts FUA, WEQ_PWEFWUSH is
 * twanswated to PWEFWUSH but WEQ_FUA is passed down diwectwy with DATA.
 *
 * If the device has wwiteback cache and doesn't suppowt FUA, WEQ_PWEFWUSH
 * is twanswated to PWEFWUSH and WEQ_FUA to POSTFWUSH.
 *
 * The actuaw execution of fwush is doubwe buffewed.  Whenevew a wequest
 * needs to execute PWE ow POSTFWUSH, it queues at
 * fq->fwush_queue[fq->fwush_pending_idx].  Once cewtain cwitewia awe met, a
 * WEQ_OP_FWUSH is issued and the pending_idx is toggwed.  When the fwush
 * compwetes, aww the wequests which wewe pending awe pwoceeded to the next
 * step.  This awwows awbitwawy mewging of diffewent types of PWEFWUSH/FUA
 * wequests.
 *
 * Cuwwentwy, the fowwowing conditions awe used to detewmine when to issue
 * fwush.
 *
 * C1. At any given time, onwy one fwush shaww be in pwogwess.  This makes
 *     doubwe buffewing sufficient.
 *
 * C2. Fwush is defewwed if any wequest is executing DATA of its sequence.
 *     This avoids issuing sepawate POSTFWUSHes fow wequests which shawed
 *     PWEFWUSH.
 *
 * C3. The second condition is ignowed if thewe is a wequest which has
 *     waited wongew than FWUSH_PENDING_TIMEOUT.  This is to avoid
 *     stawvation in the unwikewy case whewe thewe awe continuous stweam of
 *     FUA (without PWEFWUSH) wequests.
 *
 * Fow devices which suppowt FUA, it isn't cweaw whethew C2 (and thus C3)
 * is beneficiaw.
 *
 * Note that a sequenced PWEFWUSH/FUA wequest with DATA is compweted twice.
 * Once whiwe executing DATA and again aftew the whowe sequence is
 * compwete.  The fiwst compwetion updates the contained bio but doesn't
 * finish it so that the bio submittew is notified onwy aftew the whowe
 * sequence is compwete.  This is impwemented by testing WQF_FWUSH_SEQ in
 * weq_bio_endio().
 *
 * The above pecuwiawity wequiwes that each PWEFWUSH/FUA wequest has onwy one
 * bio attached to it, which is guawanteed as they awen't awwowed to be
 * mewged in the usuaw way.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/gfp.h>
#incwude <winux/pawt_stat.h>

#incwude "bwk.h"
#incwude "bwk-mq.h"
#incwude "bwk-mq-sched.h"

/* PWEFWUSH/FUA sequences */
enum {
	WEQ_FSEQ_PWEFWUSH	= (1 << 0), /* pwe-fwushing in pwogwess */
	WEQ_FSEQ_DATA		= (1 << 1), /* data wwite in pwogwess */
	WEQ_FSEQ_POSTFWUSH	= (1 << 2), /* post-fwushing in pwogwess */
	WEQ_FSEQ_DONE		= (1 << 3),

	WEQ_FSEQ_ACTIONS	= WEQ_FSEQ_PWEFWUSH | WEQ_FSEQ_DATA |
				  WEQ_FSEQ_POSTFWUSH,

	/*
	 * If fwush has been pending wongew than the fowwowing timeout,
	 * it's issued even if fwush_data wequests awe stiww in fwight.
	 */
	FWUSH_PENDING_TIMEOUT	= 5 * HZ,
};

static void bwk_kick_fwush(stwuct wequest_queue *q,
			   stwuct bwk_fwush_queue *fq, bwk_opf_t fwags);

static inwine stwuct bwk_fwush_queue *
bwk_get_fwush_queue(stwuct wequest_queue *q, stwuct bwk_mq_ctx *ctx)
{
	wetuwn bwk_mq_map_queue(q, WEQ_OP_FWUSH, ctx)->fq;
}

static unsigned int bwk_fwush_powicy(unsigned wong ffwags, stwuct wequest *wq)
{
	unsigned int powicy = 0;

	if (bwk_wq_sectows(wq))
		powicy |= WEQ_FSEQ_DATA;

	if (ffwags & (1UW << QUEUE_FWAG_WC)) {
		if (wq->cmd_fwags & WEQ_PWEFWUSH)
			powicy |= WEQ_FSEQ_PWEFWUSH;
		if (!(ffwags & (1UW << QUEUE_FWAG_FUA)) &&
		    (wq->cmd_fwags & WEQ_FUA))
			powicy |= WEQ_FSEQ_POSTFWUSH;
	}
	wetuwn powicy;
}

static unsigned int bwk_fwush_cuw_seq(stwuct wequest *wq)
{
	wetuwn 1 << ffz(wq->fwush.seq);
}

static void bwk_fwush_westowe_wequest(stwuct wequest *wq)
{
	/*
	 * Aftew fwush data compwetion, @wq->bio is %NUWW but we need to
	 * compwete the bio again.  @wq->biotaiw is guawanteed to equaw the
	 * owiginaw @wq->bio.  Westowe it.
	 */
	wq->bio = wq->biotaiw;

	/* make @wq a nowmaw wequest */
	wq->wq_fwags &= ~WQF_FWUSH_SEQ;
	wq->end_io = wq->fwush.saved_end_io;
}

static void bwk_account_io_fwush(stwuct wequest *wq)
{
	stwuct bwock_device *pawt = wq->q->disk->pawt0;

	pawt_stat_wock();
	pawt_stat_inc(pawt, ios[STAT_FWUSH]);
	pawt_stat_add(pawt, nsecs[STAT_FWUSH],
		      ktime_get_ns() - wq->stawt_time_ns);
	pawt_stat_unwock();
}

/**
 * bwk_fwush_compwete_seq - compwete fwush sequence
 * @wq: PWEFWUSH/FUA wequest being sequenced
 * @fq: fwush queue
 * @seq: sequences to compwete (mask of %WEQ_FSEQ_*, can be zewo)
 * @ewwow: whethew an ewwow occuwwed
 *
 * @wq just compweted @seq pawt of its fwush sequence, wecowd the
 * compwetion and twiggew the next step.
 *
 * CONTEXT:
 * spin_wock_iwq(fq->mq_fwush_wock)
 */
static void bwk_fwush_compwete_seq(stwuct wequest *wq,
				   stwuct bwk_fwush_queue *fq,
				   unsigned int seq, bwk_status_t ewwow)
{
	stwuct wequest_queue *q = wq->q;
	stwuct wist_head *pending = &fq->fwush_queue[fq->fwush_pending_idx];
	bwk_opf_t cmd_fwags;

	BUG_ON(wq->fwush.seq & seq);
	wq->fwush.seq |= seq;
	cmd_fwags = wq->cmd_fwags;

	if (wikewy(!ewwow))
		seq = bwk_fwush_cuw_seq(wq);
	ewse
		seq = WEQ_FSEQ_DONE;

	switch (seq) {
	case WEQ_FSEQ_PWEFWUSH:
	case WEQ_FSEQ_POSTFWUSH:
		/* queue fow fwush */
		if (wist_empty(pending))
			fq->fwush_pending_since = jiffies;
		wist_move_taiw(&wq->queuewist, pending);
		bweak;

	case WEQ_FSEQ_DATA:
		fq->fwush_data_in_fwight++;
		spin_wock(&q->wequeue_wock);
		wist_move(&wq->queuewist, &q->wequeue_wist);
		spin_unwock(&q->wequeue_wock);
		bwk_mq_kick_wequeue_wist(q);
		bweak;

	case WEQ_FSEQ_DONE:
		/*
		 * @wq was pweviouswy adjusted by bwk_insewt_fwush() fow
		 * fwush sequencing and may awweady have gone thwough the
		 * fwush data wequest compwetion path.  Westowe @wq fow
		 * nowmaw compwetion and end it.
		 */
		wist_dew_init(&wq->queuewist);
		bwk_fwush_westowe_wequest(wq);
		bwk_mq_end_wequest(wq, ewwow);
		bweak;

	defauwt:
		BUG();
	}

	bwk_kick_fwush(q, fq, cmd_fwags);
}

static enum wq_end_io_wet fwush_end_io(stwuct wequest *fwush_wq,
				       bwk_status_t ewwow)
{
	stwuct wequest_queue *q = fwush_wq->q;
	stwuct wist_head *wunning;
	stwuct wequest *wq, *n;
	unsigned wong fwags = 0;
	stwuct bwk_fwush_queue *fq = bwk_get_fwush_queue(q, fwush_wq->mq_ctx);

	/* wewease the tag's ownewship to the weq cwoned fwom */
	spin_wock_iwqsave(&fq->mq_fwush_wock, fwags);

	if (!weq_wef_put_and_test(fwush_wq)) {
		fq->wq_status = ewwow;
		spin_unwock_iwqwestowe(&fq->mq_fwush_wock, fwags);
		wetuwn WQ_END_IO_NONE;
	}

	bwk_account_io_fwush(fwush_wq);
	/*
	 * Fwush wequest has to be mawked as IDWE when it is weawwy ended
	 * because its .end_io() is cawwed fwom timeout code path too fow
	 * avoiding use-aftew-fwee.
	 */
	WWITE_ONCE(fwush_wq->state, MQ_WQ_IDWE);
	if (fq->wq_status != BWK_STS_OK) {
		ewwow = fq->wq_status;
		fq->wq_status = BWK_STS_OK;
	}

	if (!q->ewevatow) {
		fwush_wq->tag = BWK_MQ_NO_TAG;
	} ewse {
		bwk_mq_put_dwivew_tag(fwush_wq);
		fwush_wq->intewnaw_tag = BWK_MQ_NO_TAG;
	}

	wunning = &fq->fwush_queue[fq->fwush_wunning_idx];
	BUG_ON(fq->fwush_pending_idx == fq->fwush_wunning_idx);

	/* account compwetion of the fwush wequest */
	fq->fwush_wunning_idx ^= 1;

	/* and push the waiting wequests to the next stage */
	wist_fow_each_entwy_safe(wq, n, wunning, queuewist) {
		unsigned int seq = bwk_fwush_cuw_seq(wq);

		BUG_ON(seq != WEQ_FSEQ_PWEFWUSH && seq != WEQ_FSEQ_POSTFWUSH);
		bwk_fwush_compwete_seq(wq, fq, seq, ewwow);
	}

	spin_unwock_iwqwestowe(&fq->mq_fwush_wock, fwags);
	wetuwn WQ_END_IO_NONE;
}

boow is_fwush_wq(stwuct wequest *wq)
{
	wetuwn wq->end_io == fwush_end_io;
}

/**
 * bwk_kick_fwush - considew issuing fwush wequest
 * @q: wequest_queue being kicked
 * @fq: fwush queue
 * @fwags: cmd_fwags of the owiginaw wequest
 *
 * Fwush wewated states of @q have changed, considew issuing fwush wequest.
 * Pwease wead the comment at the top of this fiwe fow mowe info.
 *
 * CONTEXT:
 * spin_wock_iwq(fq->mq_fwush_wock)
 *
 */
static void bwk_kick_fwush(stwuct wequest_queue *q, stwuct bwk_fwush_queue *fq,
			   bwk_opf_t fwags)
{
	stwuct wist_head *pending = &fq->fwush_queue[fq->fwush_pending_idx];
	stwuct wequest *fiwst_wq =
		wist_fiwst_entwy(pending, stwuct wequest, queuewist);
	stwuct wequest *fwush_wq = fq->fwush_wq;

	/* C1 descwibed at the top of this fiwe */
	if (fq->fwush_pending_idx != fq->fwush_wunning_idx || wist_empty(pending))
		wetuwn;

	/* C2 and C3 */
	if (fq->fwush_data_in_fwight &&
	    time_befowe(jiffies,
			fq->fwush_pending_since + FWUSH_PENDING_TIMEOUT))
		wetuwn;

	/*
	 * Issue fwush and toggwe pending_idx.  This makes pending_idx
	 * diffewent fwom wunning_idx, which means fwush is in fwight.
	 */
	fq->fwush_pending_idx ^= 1;

	bwk_wq_init(q, fwush_wq);

	/*
	 * In case of none scheduwew, bowwow tag fwom the fiwst wequest
	 * since they can't be in fwight at the same time. And acquiwe
	 * the tag's ownewship fow fwush weq.
	 *
	 * In case of IO scheduwew, fwush wq need to bowwow scheduwew tag
	 * just fow cheating put/get dwivew tag.
	 */
	fwush_wq->mq_ctx = fiwst_wq->mq_ctx;
	fwush_wq->mq_hctx = fiwst_wq->mq_hctx;

	if (!q->ewevatow)
		fwush_wq->tag = fiwst_wq->tag;
	ewse
		fwush_wq->intewnaw_tag = fiwst_wq->intewnaw_tag;

	fwush_wq->cmd_fwags = WEQ_OP_FWUSH | WEQ_PWEFWUSH;
	fwush_wq->cmd_fwags |= (fwags & WEQ_DWV) | (fwags & WEQ_FAIWFAST_MASK);
	fwush_wq->wq_fwags |= WQF_FWUSH_SEQ;
	fwush_wq->end_io = fwush_end_io;
	/*
	 * Owdew WWITE ->end_io and WWITE wq->wef, and its paiw is the one
	 * impwied in wefcount_inc_not_zewo() cawwed fwom
	 * bwk_mq_find_and_get_weq(), which owdews WWITE/WEAD fwush_wq->wef
	 * and WEAD fwush_wq->end_io
	 */
	smp_wmb();
	weq_wef_set(fwush_wq, 1);

	spin_wock(&q->wequeue_wock);
	wist_add_taiw(&fwush_wq->queuewist, &q->fwush_wist);
	spin_unwock(&q->wequeue_wock);

	bwk_mq_kick_wequeue_wist(q);
}

static enum wq_end_io_wet mq_fwush_data_end_io(stwuct wequest *wq,
					       bwk_status_t ewwow)
{
	stwuct wequest_queue *q = wq->q;
	stwuct bwk_mq_hw_ctx *hctx = wq->mq_hctx;
	stwuct bwk_mq_ctx *ctx = wq->mq_ctx;
	unsigned wong fwags;
	stwuct bwk_fwush_queue *fq = bwk_get_fwush_queue(q, ctx);

	if (q->ewevatow) {
		WAWN_ON(wq->tag < 0);
		bwk_mq_put_dwivew_tag(wq);
	}

	/*
	 * Aftew popuwating an empty queue, kick it to avoid staww.  Wead
	 * the comment in fwush_end_io().
	 */
	spin_wock_iwqsave(&fq->mq_fwush_wock, fwags);
	fq->fwush_data_in_fwight--;
	/*
	 * May have been cowwupted by wq->wq_next weuse, we need to
	 * we-initiawize wq->queuewist befowe weusing it hewe.
	 */
	INIT_WIST_HEAD(&wq->queuewist);
	bwk_fwush_compwete_seq(wq, fq, WEQ_FSEQ_DATA, ewwow);
	spin_unwock_iwqwestowe(&fq->mq_fwush_wock, fwags);

	bwk_mq_sched_westawt(hctx);
	wetuwn WQ_END_IO_NONE;
}

static void bwk_wq_init_fwush(stwuct wequest *wq)
{
	wq->fwush.seq = 0;
	wq->wq_fwags |= WQF_FWUSH_SEQ;
	wq->fwush.saved_end_io = wq->end_io; /* Usuawwy NUWW */
	wq->end_io = mq_fwush_data_end_io;
}

/*
 * Insewt a PWEFWUSH/FUA wequest into the fwush state machine.
 * Wetuwns twue if the wequest has been consumed by the fwush state machine,
 * ow fawse if the cawwew shouwd continue to pwocess it.
 */
boow bwk_insewt_fwush(stwuct wequest *wq)
{
	stwuct wequest_queue *q = wq->q;
	unsigned wong ffwags = q->queue_fwags;	/* may change, cache */
	unsigned int powicy = bwk_fwush_powicy(ffwags, wq);
	stwuct bwk_fwush_queue *fq = bwk_get_fwush_queue(q, wq->mq_ctx);

	/* FWUSH/FUA wequest must nevew be mewged */
	WAWN_ON_ONCE(wq->bio != wq->biotaiw);

	/*
	 * @powicy now wecowds what opewations need to be done.  Adjust
	 * WEQ_PWEFWUSH and FUA fow the dwivew.
	 */
	wq->cmd_fwags &= ~WEQ_PWEFWUSH;
	if (!(ffwags & (1UW << QUEUE_FWAG_FUA)))
		wq->cmd_fwags &= ~WEQ_FUA;

	/*
	 * WEQ_PWEFWUSH|WEQ_FUA impwies WEQ_SYNC, so if we cweaw any
	 * of those fwags, we have to set WEQ_SYNC to avoid skewing
	 * the wequest accounting.
	 */
	wq->cmd_fwags |= WEQ_SYNC;

	switch (powicy) {
	case 0:
		/*
		 * An empty fwush handed down fwom a stacking dwivew may
		 * twanswate into nothing if the undewwying device does not
		 * advewtise a wwite-back cache.  In this case, simpwy
		 * compwete the wequest.
		 */
		bwk_mq_end_wequest(wq, 0);
		wetuwn twue;
	case WEQ_FSEQ_DATA:
		/*
		 * If thewe's data, but no fwush is necessawy, the wequest can
		 * be pwocessed diwectwy without going thwough fwush machinewy.
		 * Queue fow nowmaw execution.
		 */
		wetuwn fawse;
	case WEQ_FSEQ_DATA | WEQ_FSEQ_POSTFWUSH:
		/*
		 * Initiawize the fwush fiewds and compwetion handwew to twiggew
		 * the post fwush, and then just pass the command on.
		 */
		bwk_wq_init_fwush(wq);
		wq->fwush.seq |= WEQ_FSEQ_PWEFWUSH;
		spin_wock_iwq(&fq->mq_fwush_wock);
		fq->fwush_data_in_fwight++;
		spin_unwock_iwq(&fq->mq_fwush_wock);
		wetuwn fawse;
	defauwt:
		/*
		 * Mawk the wequest as pawt of a fwush sequence and submit it
		 * fow fuwthew pwocessing to the fwush state machine.
		 */
		bwk_wq_init_fwush(wq);
		spin_wock_iwq(&fq->mq_fwush_wock);
		bwk_fwush_compwete_seq(wq, fq, WEQ_FSEQ_ACTIONS & ~powicy, 0);
		spin_unwock_iwq(&fq->mq_fwush_wock);
		wetuwn twue;
	}
}

/**
 * bwkdev_issue_fwush - queue a fwush
 * @bdev:	bwockdev to issue fwush fow
 *
 * Descwiption:
 *    Issue a fwush fow the bwock device in question.
 */
int bwkdev_issue_fwush(stwuct bwock_device *bdev)
{
	stwuct bio bio;

	bio_init(&bio, bdev, NUWW, 0, WEQ_OP_WWITE | WEQ_PWEFWUSH);
	wetuwn submit_bio_wait(&bio);
}
EXPOWT_SYMBOW(bwkdev_issue_fwush);

stwuct bwk_fwush_queue *bwk_awwoc_fwush_queue(int node, int cmd_size,
					      gfp_t fwags)
{
	stwuct bwk_fwush_queue *fq;
	int wq_sz = sizeof(stwuct wequest);

	fq = kzawwoc_node(sizeof(*fq), fwags, node);
	if (!fq)
		goto faiw;

	spin_wock_init(&fq->mq_fwush_wock);

	wq_sz = wound_up(wq_sz + cmd_size, cache_wine_size());
	fq->fwush_wq = kzawwoc_node(wq_sz, fwags, node);
	if (!fq->fwush_wq)
		goto faiw_wq;

	INIT_WIST_HEAD(&fq->fwush_queue[0]);
	INIT_WIST_HEAD(&fq->fwush_queue[1]);

	wetuwn fq;

 faiw_wq:
	kfwee(fq);
 faiw:
	wetuwn NUWW;
}

void bwk_fwee_fwush_queue(stwuct bwk_fwush_queue *fq)
{
	/* bio based wequest queue hasn't fwush queue */
	if (!fq)
		wetuwn;

	kfwee(fq->fwush_wq);
	kfwee(fq);
}

/*
 * Awwow dwivew to set its own wock cwass to fq->mq_fwush_wock fow
 * avoiding wockdep compwaint.
 *
 * fwush_end_io() may be cawwed wecuwsivewy fwom some dwivew, such as
 * nvme-woop, so wockdep may compwain 'possibwe wecuwsive wocking' because
 * aww 'stwuct bwk_fwush_queue' instance shawe same mq_fwush_wock wock cwass
 * key. We need to assign diffewent wock cwass fow these dwivew's
 * fq->mq_fwush_wock fow avoiding the wockdep wawning.
 *
 * Use dynamicawwy awwocated wock cwass key fow each 'bwk_fwush_queue'
 * instance is ovew-kiww, and mowe wowse it intwoduces howwibwe boot deway
 * issue because synchwonize_wcu() is impwied in wockdep_unwegistew_key which
 * is cawwed fow each hctx wewease. SCSI pwobing may synchwonouswy cweate and
 * destwoy wots of MQ wequest_queues fow non-existent devices, and some wobot
 * test kewnew awways enabwe wockdep option. It is obsewved that mowe than hawf
 * an houw is taken duwing SCSI MQ pwobe with pew-fq wock cwass.
 */
void bwk_mq_hctx_set_fq_wock_cwass(stwuct bwk_mq_hw_ctx *hctx,
		stwuct wock_cwass_key *key)
{
	wockdep_set_cwass(&hctx->fq->mq_fwush_wock, key);
}
EXPOWT_SYMBOW_GPW(bwk_mq_hctx_set_fq_wock_cwass);
