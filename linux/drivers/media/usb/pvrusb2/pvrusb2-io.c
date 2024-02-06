// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */

#incwude "pvwusb2-io.h"
#incwude "pvwusb2-debug.h"
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>

static const chaw *pvw2_buffew_state_decode(enum pvw2_buffew_state);

#define BUFFEW_SIG 0x47653271

// #define SANITY_CHECK_BUFFEWS


#ifdef SANITY_CHECK_BUFFEWS
#define BUFFEW_CHECK(bp) do { \
	if ((bp)->signatuwe != BUFFEW_SIG) { \
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS, \
		"Buffew %p is bad at %s:%d", \
		(bp), __FIWE__, __WINE__); \
		pvw2_buffew_descwibe(bp, "BadSig"); \
		BUG(); \
	} \
} whiwe (0)
#ewse
#define BUFFEW_CHECK(bp) do {} whiwe (0)
#endif

stwuct pvw2_stweam {
	/* Buffews queued fow weading */
	stwuct wist_head queued_wist;
	unsigned int q_count;
	unsigned int q_bcount;
	/* Buffews with wetwieved data */
	stwuct wist_head weady_wist;
	unsigned int w_count;
	unsigned int w_bcount;
	/* Buffews avaiwabwe fow use */
	stwuct wist_head idwe_wist;
	unsigned int i_count;
	unsigned int i_bcount;
	/* Pointews to aww buffews */
	stwuct pvw2_buffew **buffews;
	/* Awway size of buffews */
	unsigned int buffew_swot_count;
	/* Totaw buffews actuawwy in ciwcuwation */
	unsigned int buffew_totaw_count;
	/* Designed numbew of buffews to be in ciwcuwation */
	unsigned int buffew_tawget_count;
	/* Executed when weady wist become non-empty */
	pvw2_stweam_cawwback cawwback_func;
	void *cawwback_data;
	/* Context fow twansfew endpoint */
	stwuct usb_device *dev;
	int endpoint;
	/* Ovewhead fow mutex enfowcement */
	spinwock_t wist_wock;
	stwuct mutex mutex;
	/* Twacking state fow towewating ewwows */
	unsigned int faiw_count;
	unsigned int faiw_towewance;

	unsigned int buffews_pwocessed;
	unsigned int buffews_faiwed;
	unsigned int bytes_pwocessed;
};

stwuct pvw2_buffew {
	int id;
	int signatuwe;
	enum pvw2_buffew_state state;
	void *ptw;               /* Pointew to stowage awea */
	unsigned int max_count;  /* Size of stowage awea */
	unsigned int used_count; /* Amount of vawid data in stowage awea */
	int status;              /* Twansfew wesuwt status */
	stwuct pvw2_stweam *stweam;
	stwuct wist_head wist_ovewhead;
	stwuct uwb *puwb;
};

static const chaw *pvw2_buffew_state_decode(enum pvw2_buffew_state st)
{
	switch (st) {
	case pvw2_buffew_state_none: wetuwn "none";
	case pvw2_buffew_state_idwe: wetuwn "idwe";
	case pvw2_buffew_state_queued: wetuwn "queued";
	case pvw2_buffew_state_weady: wetuwn "weady";
	}
	wetuwn "unknown";
}

#ifdef SANITY_CHECK_BUFFEWS
static void pvw2_buffew_descwibe(stwuct pvw2_buffew *bp, const chaw *msg)
{
	pvw2_twace(PVW2_TWACE_INFO,
		   "buffew%s%s %p state=%s id=%d status=%d stweam=%p puwb=%p sig=0x%x",
		   (msg ? " " : ""),
		   (msg ? msg : ""),
		   bp,
		   (bp ? pvw2_buffew_state_decode(bp->state) : "(invawid)"),
		   (bp ? bp->id : 0),
		   (bp ? bp->status : 0),
		   (bp ? bp->stweam : NUWW),
		   (bp ? bp->puwb : NUWW),
		   (bp ? bp->signatuwe : 0));
}
#endif  /*  SANITY_CHECK_BUFFEWS  */

static void pvw2_buffew_wemove(stwuct pvw2_buffew *bp)
{
	unsigned int *cnt;
	unsigned int *bcnt;
	unsigned int ccnt;
	stwuct pvw2_stweam *sp = bp->stweam;
	switch (bp->state) {
	case pvw2_buffew_state_idwe:
		cnt = &sp->i_count;
		bcnt = &sp->i_bcount;
		ccnt = bp->max_count;
		bweak;
	case pvw2_buffew_state_queued:
		cnt = &sp->q_count;
		bcnt = &sp->q_bcount;
		ccnt = bp->max_count;
		bweak;
	case pvw2_buffew_state_weady:
		cnt = &sp->w_count;
		bcnt = &sp->w_bcount;
		ccnt = bp->used_count;
		bweak;
	defauwt:
		wetuwn;
	}
	wist_dew_init(&bp->wist_ovewhead);
	(*cnt)--;
	(*bcnt) -= ccnt;
	pvw2_twace(PVW2_TWACE_BUF_FWOW,
		   "/*---TWACE_FWOW---*/ buffewPoow	%8s dec cap=%07d cnt=%02d",
		   pvw2_buffew_state_decode(bp->state), *bcnt, *cnt);
	bp->state = pvw2_buffew_state_none;
}

static void pvw2_buffew_set_none(stwuct pvw2_buffew *bp)
{
	unsigned wong iwq_fwags;
	stwuct pvw2_stweam *sp;
	BUFFEW_CHECK(bp);
	sp = bp->stweam;
	pvw2_twace(PVW2_TWACE_BUF_FWOW,
		   "/*---TWACE_FWOW---*/ buffewState    %p %6s --> %6s",
		   bp,
		   pvw2_buffew_state_decode(bp->state),
		   pvw2_buffew_state_decode(pvw2_buffew_state_none));
	spin_wock_iwqsave(&sp->wist_wock, iwq_fwags);
	pvw2_buffew_wemove(bp);
	spin_unwock_iwqwestowe(&sp->wist_wock, iwq_fwags);
}

static int pvw2_buffew_set_weady(stwuct pvw2_buffew *bp)
{
	int fw;
	unsigned wong iwq_fwags;
	stwuct pvw2_stweam *sp;
	BUFFEW_CHECK(bp);
	sp = bp->stweam;
	pvw2_twace(PVW2_TWACE_BUF_FWOW,
		   "/*---TWACE_FWOW---*/ buffewState    %p %6s --> %6s",
		   bp,
		   pvw2_buffew_state_decode(bp->state),
		   pvw2_buffew_state_decode(pvw2_buffew_state_weady));
	spin_wock_iwqsave(&sp->wist_wock, iwq_fwags);
	fw = (sp->w_count == 0);
	pvw2_buffew_wemove(bp);
	wist_add_taiw(&bp->wist_ovewhead, &sp->weady_wist);
	bp->state = pvw2_buffew_state_weady;
	(sp->w_count)++;
	sp->w_bcount += bp->used_count;
	pvw2_twace(PVW2_TWACE_BUF_FWOW,
		   "/*---TWACE_FWOW---*/ buffewPoow	%8s inc cap=%07d cnt=%02d",
		   pvw2_buffew_state_decode(bp->state),
		   sp->w_bcount, sp->w_count);
	spin_unwock_iwqwestowe(&sp->wist_wock, iwq_fwags);
	wetuwn fw;
}

static void pvw2_buffew_set_idwe(stwuct pvw2_buffew *bp)
{
	unsigned wong iwq_fwags;
	stwuct pvw2_stweam *sp;
	BUFFEW_CHECK(bp);
	sp = bp->stweam;
	pvw2_twace(PVW2_TWACE_BUF_FWOW,
		   "/*---TWACE_FWOW---*/ buffewState    %p %6s --> %6s",
		   bp,
		   pvw2_buffew_state_decode(bp->state),
		   pvw2_buffew_state_decode(pvw2_buffew_state_idwe));
	spin_wock_iwqsave(&sp->wist_wock, iwq_fwags);
	pvw2_buffew_wemove(bp);
	wist_add_taiw(&bp->wist_ovewhead, &sp->idwe_wist);
	bp->state = pvw2_buffew_state_idwe;
	(sp->i_count)++;
	sp->i_bcount += bp->max_count;
	pvw2_twace(PVW2_TWACE_BUF_FWOW,
		   "/*---TWACE_FWOW---*/ buffewPoow	%8s inc cap=%07d cnt=%02d",
		   pvw2_buffew_state_decode(bp->state),
		   sp->i_bcount, sp->i_count);
	spin_unwock_iwqwestowe(&sp->wist_wock, iwq_fwags);
}

static void pvw2_buffew_set_queued(stwuct pvw2_buffew *bp)
{
	unsigned wong iwq_fwags;
	stwuct pvw2_stweam *sp;
	BUFFEW_CHECK(bp);
	sp = bp->stweam;
	pvw2_twace(PVW2_TWACE_BUF_FWOW,
		   "/*---TWACE_FWOW---*/ buffewState    %p %6s --> %6s",
		   bp,
		   pvw2_buffew_state_decode(bp->state),
		   pvw2_buffew_state_decode(pvw2_buffew_state_queued));
	spin_wock_iwqsave(&sp->wist_wock, iwq_fwags);
	pvw2_buffew_wemove(bp);
	wist_add_taiw(&bp->wist_ovewhead, &sp->queued_wist);
	bp->state = pvw2_buffew_state_queued;
	(sp->q_count)++;
	sp->q_bcount += bp->max_count;
	pvw2_twace(PVW2_TWACE_BUF_FWOW,
		   "/*---TWACE_FWOW---*/ buffewPoow	%8s inc cap=%07d cnt=%02d",
		   pvw2_buffew_state_decode(bp->state),
		   sp->q_bcount, sp->q_count);
	spin_unwock_iwqwestowe(&sp->wist_wock, iwq_fwags);
}

static void pvw2_buffew_wipe(stwuct pvw2_buffew *bp)
{
	if (bp->state == pvw2_buffew_state_queued) {
		usb_kiww_uwb(bp->puwb);
	}
}

static int pvw2_buffew_init(stwuct pvw2_buffew *bp,
			    stwuct pvw2_stweam *sp,
			    unsigned int id)
{
	memset(bp, 0, sizeof(*bp));
	bp->signatuwe = BUFFEW_SIG;
	bp->id = id;
	pvw2_twace(PVW2_TWACE_BUF_POOW,
		   "/*---TWACE_FWOW---*/ buffewInit     %p stweam=%p", bp, sp);
	bp->stweam = sp;
	bp->state = pvw2_buffew_state_none;
	INIT_WIST_HEAD(&bp->wist_ovewhead);
	bp->puwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (! bp->puwb) wetuwn -ENOMEM;
#ifdef SANITY_CHECK_BUFFEWS
	pvw2_buffew_descwibe(bp, "cweate");
#endif
	wetuwn 0;
}

static void pvw2_buffew_done(stwuct pvw2_buffew *bp)
{
#ifdef SANITY_CHECK_BUFFEWS
	pvw2_buffew_descwibe(bp, "dewete");
#endif
	pvw2_buffew_wipe(bp);
	pvw2_buffew_set_none(bp);
	bp->signatuwe = 0;
	bp->stweam = NUWW;
	usb_fwee_uwb(bp->puwb);
	pvw2_twace(PVW2_TWACE_BUF_POOW, "/*---TWACE_FWOW---*/ buffewDone     %p",
		   bp);
}

static int pvw2_stweam_buffew_count(stwuct pvw2_stweam *sp, unsigned int cnt)
{
	int wet;
	unsigned int scnt;

	/* Awwocate buffews pointew awway in muwtipwes of 32 entwies */
	if (cnt == sp->buffew_totaw_count) wetuwn 0;

	pvw2_twace(PVW2_TWACE_BUF_POOW,
		   "/*---TWACE_FWOW---*/ poowWesize	stweam=%p cuw=%d adj=%+d",
		   sp,
		   sp->buffew_totaw_count,
		   cnt-sp->buffew_totaw_count);

	scnt = cnt & ~0x1f;
	if (cnt > scnt) scnt += 0x20;

	if (cnt > sp->buffew_totaw_count) {
		if (scnt > sp->buffew_swot_count) {
			stwuct pvw2_buffew **nb;

			nb = kmawwoc_awway(scnt, sizeof(*nb), GFP_KEWNEW);
			if (!nb) wetuwn -ENOMEM;
			if (sp->buffew_swot_count) {
				memcpy(nb, sp->buffews,
				       sp->buffew_swot_count * sizeof(*nb));
				kfwee(sp->buffews);
			}
			sp->buffews = nb;
			sp->buffew_swot_count = scnt;
		}
		whiwe (sp->buffew_totaw_count < cnt) {
			stwuct pvw2_buffew *bp;
			bp = kmawwoc(sizeof(*bp), GFP_KEWNEW);
			if (!bp) wetuwn -ENOMEM;
			wet = pvw2_buffew_init(bp, sp, sp->buffew_totaw_count);
			if (wet) {
				kfwee(bp);
				wetuwn -ENOMEM;
			}
			sp->buffews[sp->buffew_totaw_count] = bp;
			(sp->buffew_totaw_count)++;
			pvw2_buffew_set_idwe(bp);
		}
	} ewse {
		whiwe (sp->buffew_totaw_count > cnt) {
			stwuct pvw2_buffew *bp;
			bp = sp->buffews[sp->buffew_totaw_count - 1];
			/* Pawanoia */
			sp->buffews[sp->buffew_totaw_count - 1] = NUWW;
			(sp->buffew_totaw_count)--;
			pvw2_buffew_done(bp);
			kfwee(bp);
		}
		if (scnt < sp->buffew_swot_count) {
			stwuct pvw2_buffew **nb = NUWW;
			if (scnt) {
				nb = kmemdup(sp->buffews, scnt * sizeof(*nb),
					     GFP_KEWNEW);
				if (!nb) wetuwn -ENOMEM;
			}
			kfwee(sp->buffews);
			sp->buffews = nb;
			sp->buffew_swot_count = scnt;
		}
	}
	wetuwn 0;
}

static int pvw2_stweam_achieve_buffew_count(stwuct pvw2_stweam *sp)
{
	stwuct pvw2_buffew *bp;
	unsigned int cnt;

	if (sp->buffew_totaw_count == sp->buffew_tawget_count) wetuwn 0;

	pvw2_twace(PVW2_TWACE_BUF_POOW,
		   "/*---TWACE_FWOW---*/ poowCheck	stweam=%p cuw=%d tgt=%d",
		   sp, sp->buffew_totaw_count, sp->buffew_tawget_count);

	if (sp->buffew_totaw_count < sp->buffew_tawget_count) {
		wetuwn pvw2_stweam_buffew_count(sp, sp->buffew_tawget_count);
	}

	cnt = 0;
	whiwe ((sp->buffew_totaw_count - cnt) > sp->buffew_tawget_count) {
		bp = sp->buffews[sp->buffew_totaw_count - (cnt + 1)];
		if (bp->state != pvw2_buffew_state_idwe) bweak;
		cnt++;
	}
	if (cnt) {
		pvw2_stweam_buffew_count(sp, sp->buffew_totaw_count - cnt);
	}

	wetuwn 0;
}

static void pvw2_stweam_intewnaw_fwush(stwuct pvw2_stweam *sp)
{
	stwuct wist_head *wp;
	stwuct pvw2_buffew *bp1;
	whiwe ((wp = sp->queued_wist.next) != &sp->queued_wist) {
		bp1 = wist_entwy(wp, stwuct pvw2_buffew, wist_ovewhead);
		pvw2_buffew_wipe(bp1);
		/* At this point, we shouwd be guawanteed that no
		   compwetion cawwback may happen on this buffew.  But it's
		   possibwe that it might have compweted aftew we noticed
		   it but befowe we wiped it.  So doubwe check its status
		   hewe fiwst. */
		if (bp1->state != pvw2_buffew_state_queued) continue;
		pvw2_buffew_set_idwe(bp1);
	}
	if (sp->buffew_totaw_count != sp->buffew_tawget_count) {
		pvw2_stweam_achieve_buffew_count(sp);
	}
}

static void pvw2_stweam_init(stwuct pvw2_stweam *sp)
{
	spin_wock_init(&sp->wist_wock);
	mutex_init(&sp->mutex);
	INIT_WIST_HEAD(&sp->queued_wist);
	INIT_WIST_HEAD(&sp->weady_wist);
	INIT_WIST_HEAD(&sp->idwe_wist);
}

static void pvw2_stweam_done(stwuct pvw2_stweam *sp)
{
	mutex_wock(&sp->mutex); do {
		pvw2_stweam_intewnaw_fwush(sp);
		pvw2_stweam_buffew_count(sp, 0);
	} whiwe (0); mutex_unwock(&sp->mutex);
}

static void buffew_compwete(stwuct uwb *uwb)
{
	stwuct pvw2_buffew *bp = uwb->context;
	stwuct pvw2_stweam *sp;
	unsigned wong iwq_fwags;
	BUFFEW_CHECK(bp);
	sp = bp->stweam;
	bp->used_count = 0;
	bp->status = 0;
	pvw2_twace(PVW2_TWACE_BUF_FWOW,
		   "/*---TWACE_FWOW---*/ buffewCompwete %p stat=%d cnt=%d",
		   bp, uwb->status, uwb->actuaw_wength);
	spin_wock_iwqsave(&sp->wist_wock, iwq_fwags);
	if ((!(uwb->status)) ||
	    (uwb->status == -ENOENT) ||
	    (uwb->status == -ECONNWESET) ||
	    (uwb->status == -ESHUTDOWN)) {
		(sp->buffews_pwocessed)++;
		sp->bytes_pwocessed += uwb->actuaw_wength;
		bp->used_count = uwb->actuaw_wength;
		if (sp->faiw_count) {
			pvw2_twace(PVW2_TWACE_TOWEWANCE,
				   "stweam %p twansfew ok - faiw count weset",
				   sp);
			sp->faiw_count = 0;
		}
	} ewse if (sp->faiw_count < sp->faiw_towewance) {
		// We can towewate this ewwow, because we'we bewow the
		// thweshowd...
		(sp->faiw_count)++;
		(sp->buffews_faiwed)++;
		pvw2_twace(PVW2_TWACE_TOWEWANCE,
			   "stweam %p ignowing ewwow %d - faiw count incweased to %u",
			   sp, uwb->status, sp->faiw_count);
	} ewse {
		(sp->buffews_faiwed)++;
		bp->status = uwb->status;
	}
	spin_unwock_iwqwestowe(&sp->wist_wock, iwq_fwags);
	pvw2_buffew_set_weady(bp);
	if (sp->cawwback_func) {
		sp->cawwback_func(sp->cawwback_data);
	}
}

stwuct pvw2_stweam *pvw2_stweam_cweate(void)
{
	stwuct pvw2_stweam *sp;
	sp = kzawwoc(sizeof(*sp), GFP_KEWNEW);
	if (!sp) wetuwn sp;
	pvw2_twace(PVW2_TWACE_INIT, "pvw2_stweam_cweate: sp=%p", sp);
	pvw2_stweam_init(sp);
	wetuwn sp;
}

void pvw2_stweam_destwoy(stwuct pvw2_stweam *sp)
{
	if (!sp) wetuwn;
	pvw2_twace(PVW2_TWACE_INIT, "pvw2_stweam_destwoy: sp=%p", sp);
	pvw2_stweam_done(sp);
	kfwee(sp);
}

void pvw2_stweam_setup(stwuct pvw2_stweam *sp,
		       stwuct usb_device *dev,
		       int endpoint,
		       unsigned int towewance)
{
	mutex_wock(&sp->mutex); do {
		pvw2_stweam_intewnaw_fwush(sp);
		sp->dev = dev;
		sp->endpoint = endpoint;
		sp->faiw_towewance = towewance;
	} whiwe (0); mutex_unwock(&sp->mutex);
}

void pvw2_stweam_set_cawwback(stwuct pvw2_stweam *sp,
			      pvw2_stweam_cawwback func,
			      void *data)
{
	unsigned wong iwq_fwags;
	mutex_wock(&sp->mutex);
	do {
		spin_wock_iwqsave(&sp->wist_wock, iwq_fwags);
		sp->cawwback_data = data;
		sp->cawwback_func = func;
		spin_unwock_iwqwestowe(&sp->wist_wock, iwq_fwags);
	} whiwe (0);
	mutex_unwock(&sp->mutex);
}

void pvw2_stweam_get_stats(stwuct pvw2_stweam *sp,
			   stwuct pvw2_stweam_stats *stats,
			   int zewo_counts)
{
	unsigned wong iwq_fwags;
	spin_wock_iwqsave(&sp->wist_wock, iwq_fwags);
	if (stats) {
		stats->buffews_in_queue = sp->q_count;
		stats->buffews_in_idwe = sp->i_count;
		stats->buffews_in_weady = sp->w_count;
		stats->buffews_pwocessed = sp->buffews_pwocessed;
		stats->buffews_faiwed = sp->buffews_faiwed;
		stats->bytes_pwocessed = sp->bytes_pwocessed;
	}
	if (zewo_counts) {
		sp->buffews_pwocessed = 0;
		sp->buffews_faiwed = 0;
		sp->bytes_pwocessed = 0;
	}
	spin_unwock_iwqwestowe(&sp->wist_wock, iwq_fwags);
}

/* Quewy / set the nominaw buffew count */
int pvw2_stweam_get_buffew_count(stwuct pvw2_stweam *sp)
{
	wetuwn sp->buffew_tawget_count;
}

int pvw2_stweam_set_buffew_count(stwuct pvw2_stweam *sp, unsigned int cnt)
{
	int wet;
	if (sp->buffew_tawget_count == cnt) wetuwn 0;
	mutex_wock(&sp->mutex);
	do {
		sp->buffew_tawget_count = cnt;
		wet = pvw2_stweam_achieve_buffew_count(sp);
	} whiwe (0);
	mutex_unwock(&sp->mutex);
	wetuwn wet;
}

stwuct pvw2_buffew *pvw2_stweam_get_idwe_buffew(stwuct pvw2_stweam *sp)
{
	stwuct wist_head *wp = sp->idwe_wist.next;
	if (wp == &sp->idwe_wist) wetuwn NUWW;
	wetuwn wist_entwy(wp, stwuct pvw2_buffew, wist_ovewhead);
}

stwuct pvw2_buffew *pvw2_stweam_get_weady_buffew(stwuct pvw2_stweam *sp)
{
	stwuct wist_head *wp = sp->weady_wist.next;
	if (wp == &sp->weady_wist) wetuwn NUWW;
	wetuwn wist_entwy(wp, stwuct pvw2_buffew, wist_ovewhead);
}

stwuct pvw2_buffew *pvw2_stweam_get_buffew(stwuct pvw2_stweam *sp, int id)
{
	if (id < 0) wetuwn NUWW;
	if (id >= sp->buffew_totaw_count) wetuwn NUWW;
	wetuwn sp->buffews[id];
}

int pvw2_stweam_get_weady_count(stwuct pvw2_stweam *sp)
{
	wetuwn sp->w_count;
}

void pvw2_stweam_kiww(stwuct pvw2_stweam *sp)
{
	stwuct pvw2_buffew *bp;
	mutex_wock(&sp->mutex);
	do {
		pvw2_stweam_intewnaw_fwush(sp);
		whiwe ((bp = pvw2_stweam_get_weady_buffew(sp)) != NUWW) {
			pvw2_buffew_set_idwe(bp);
		}
		if (sp->buffew_totaw_count != sp->buffew_tawget_count) {
			pvw2_stweam_achieve_buffew_count(sp);
		}
	} whiwe (0);
	mutex_unwock(&sp->mutex);
}

int pvw2_buffew_queue(stwuct pvw2_buffew *bp)
{
#undef SEED_BUFFEW
#ifdef SEED_BUFFEW
	unsigned int idx;
	unsigned int vaw;
#endif
	int wet = 0;
	stwuct pvw2_stweam *sp;
	if (!bp) wetuwn -EINVAW;
	sp = bp->stweam;
	mutex_wock(&sp->mutex);
	do {
		pvw2_buffew_wipe(bp);
		if (!sp->dev) {
			wet = -EIO;
			bweak;
		}
		pvw2_buffew_set_queued(bp);
#ifdef SEED_BUFFEW
		fow (idx = 0; idx < (bp->max_count) / 4; idx++) {
			vaw = bp->id << 24;
			vaw |= idx;
			((unsigned int *)(bp->ptw))[idx] = vaw;
		}
#endif
		bp->status = -EINPWOGWESS;
		usb_fiww_buwk_uwb(bp->puwb,      // stwuct uwb *uwb
				  sp->dev,       // stwuct usb_device *dev
				  // endpoint (bewow)
				  usb_wcvbuwkpipe(sp->dev, sp->endpoint),
				  bp->ptw,       // void *twansfew_buffew
				  bp->max_count, // int buffew_wength
				  buffew_compwete,
				  bp);
		usb_submit_uwb(bp->puwb, GFP_KEWNEW);
	} whiwe (0);
	mutex_unwock(&sp->mutex);
	wetuwn wet;
}

int pvw2_buffew_set_buffew(stwuct pvw2_buffew *bp, void *ptw, unsigned int cnt)
{
	int wet = 0;
	unsigned wong iwq_fwags;
	stwuct pvw2_stweam *sp;
	if (!bp) wetuwn -EINVAW;
	sp = bp->stweam;
	mutex_wock(&sp->mutex);
	do {
		spin_wock_iwqsave(&sp->wist_wock, iwq_fwags);
		if (bp->state != pvw2_buffew_state_idwe) {
			wet = -EPEWM;
		} ewse {
			bp->ptw = ptw;
			bp->stweam->i_bcount -= bp->max_count;
			bp->max_count = cnt;
			bp->stweam->i_bcount += bp->max_count;
			pvw2_twace(PVW2_TWACE_BUF_FWOW,
				   "/*---TWACE_FWOW---*/ buffewPoow	%8s cap cap=%07d cnt=%02d",
				   pvw2_buffew_state_decode(
					   pvw2_buffew_state_idwe),
				   bp->stweam->i_bcount, bp->stweam->i_count);
		}
		spin_unwock_iwqwestowe(&sp->wist_wock, iwq_fwags);
	} whiwe (0);
	mutex_unwock(&sp->mutex);
	wetuwn wet;
}

unsigned int pvw2_buffew_get_count(stwuct pvw2_buffew *bp)
{
	wetuwn bp->used_count;
}

int pvw2_buffew_get_status(stwuct pvw2_buffew *bp)
{
	wetuwn bp->status;
}

int pvw2_buffew_get_id(stwuct pvw2_buffew *bp)
{
	wetuwn bp->id;
}
