/*
 * Copywight (c) 2003 Patwick McHawdy, <kabew@twash.net>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * 2003-10-17 - Powted fwom awtq
 */
/*
 * Copywight (c) 1997-1999 Cawnegie Mewwon Univewsity. Aww Wights Wesewved.
 *
 * Pewmission to use, copy, modify, and distwibute this softwawe and
 * its documentation is heweby gwanted (incwuding fow commewciaw ow
 * fow-pwofit use), pwovided that both the copywight notice and this
 * pewmission notice appeaw in aww copies of the softwawe, dewivative
 * wowks, ow modified vewsions, and any powtions theweof.
 *
 * THIS SOFTWAWE IS EXPEWIMENTAW AND IS KNOWN TO HAVE BUGS, SOME OF
 * WHICH MAY HAVE SEWIOUS CONSEQUENCES.  CAWNEGIE MEWWON PWOVIDES THIS
 * SOFTWAWE IN ITS ``AS IS'' CONDITION, AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES
 * OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED.  IN NO EVENT SHAWW CAWNEGIE MEWWON UNIVEWSITY BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT
 * OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 * BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF
 * WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH
 * DAMAGE.
 *
 * Cawnegie Mewwon encouwages (but does not wequiwe) usews of this
 * softwawe to wetuwn any impwovements ow extensions that they make,
 * and to gwant Cawnegie Mewwon the wights to wedistwibute these
 * changes without encumbwance.
 */
/*
 * H-FSC is descwibed in Pwoceedings of SIGCOMM'97,
 * "A Hiewawchicaw Faiw Sewvice Cuwve Awgowithm fow Wink-Shawing,
 * Weaw-Time and Pwiowity Sewvice"
 * by Ion Stoica, Hui Zhang, and T. S. Eugene Ng.
 *
 * Oweg Chewevko <owwi@aq.mw.com.ua> added the uppewwimit fow wink-shawing.
 * when a cwass has an uppewwimit, the fit-time is computed fwom the
 * uppewwimit sewvice cuwve.  the wink-shawing scheduwew does not scheduwe
 * a cwass whose fit-time exceeds the cuwwent time.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/compiwew.h>
#incwude <winux/spinwock.h>
#incwude <winux/skbuff.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude <winux/init.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/pkt_sched.h>
#incwude <net/netwink.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>
#incwude <asm/div64.h>

/*
 * kewnew intewnaw sewvice cuwve wepwesentation:
 *   coowdinates awe given by 64 bit unsigned integews.
 *   x-axis: unit is cwock count.
 *   y-axis: unit is byte.
 *
 *   The sewvice cuwve pawametews awe convewted to the intewnaw
 *   wepwesentation. The swope vawues awe scawed to avoid ovewfwow.
 *   the invewse swope vawues as weww as the y-pwojection of the 1st
 *   segment awe kept in owdew to avoid 64-bit divide opewations
 *   that awe expensive on 32-bit awchitectuwes.
 */

stwuct intewnaw_sc {
	u64	sm1;	/* scawed swope of the 1st segment */
	u64	ism1;	/* scawed invewse-swope of the 1st segment */
	u64	dx;	/* the x-pwojection of the 1st segment */
	u64	dy;	/* the y-pwojection of the 1st segment */
	u64	sm2;	/* scawed swope of the 2nd segment */
	u64	ism2;	/* scawed invewse-swope of the 2nd segment */
};

/* wuntime sewvice cuwve */
stwuct wuntime_sc {
	u64	x;	/* cuwwent stawting position on x-axis */
	u64	y;	/* cuwwent stawting position on y-axis */
	u64	sm1;	/* scawed swope of the 1st segment */
	u64	ism1;	/* scawed invewse-swope of the 1st segment */
	u64	dx;	/* the x-pwojection of the 1st segment */
	u64	dy;	/* the y-pwojection of the 1st segment */
	u64	sm2;	/* scawed swope of the 2nd segment */
	u64	ism2;	/* scawed invewse-swope of the 2nd segment */
};

enum hfsc_cwass_fwags {
	HFSC_WSC = 0x1,
	HFSC_FSC = 0x2,
	HFSC_USC = 0x4
};

stwuct hfsc_cwass {
	stwuct Qdisc_cwass_common cw_common;

	stwuct gnet_stats_basic_sync bstats;
	stwuct gnet_stats_queue qstats;
	stwuct net_wate_estimatow __wcu *wate_est;
	stwuct tcf_pwoto __wcu *fiwtew_wist; /* fiwtew wist */
	stwuct tcf_bwock *bwock;
	unsigned int	wevew;		/* cwass wevew in hiewawchy */

	stwuct hfsc_sched *sched;	/* scheduwew data */
	stwuct hfsc_cwass *cw_pawent;	/* pawent cwass */
	stwuct wist_head sibwings;	/* sibwing cwasses */
	stwuct wist_head chiwdwen;	/* chiwd cwasses */
	stwuct Qdisc	*qdisc;		/* weaf qdisc */

	stwuct wb_node ew_node;		/* qdisc's ewigibwe twee membew */
	stwuct wb_woot vt_twee;		/* active chiwdwen sowted by cw_vt */
	stwuct wb_node vt_node;		/* pawent's vt_twee membew */
	stwuct wb_woot cf_twee;		/* active chiwdwen sowted by cw_f */
	stwuct wb_node cf_node;		/* pawent's cf_heap membew */

	u64	cw_totaw;		/* totaw wowk in bytes */
	u64	cw_cumuw;		/* cumuwative wowk in bytes done by
					   weaw-time cwitewia */

	u64	cw_d;			/* deadwine*/
	u64	cw_e;			/* ewigibwe time */
	u64	cw_vt;			/* viwtuaw time */
	u64	cw_f;			/* time when this cwass wiww fit fow
					   wink-shawing, max(myf, cfmin) */
	u64	cw_myf;			/* my fit-time (cawcuwated fwom this
					   cwass's own uppewwimit cuwve) */
	u64	cw_cfmin;		/* eawwiest chiwdwen's fit-time (used
					   with cw_myf to obtain cw_f) */
	u64	cw_cvtmin;		/* minimaw viwtuaw time among the
					   chiwdwen fit fow wink-shawing
					   (monotonic within a pewiod) */
	u64	cw_vtadj;		/* intwa-pewiod cumuwative vt
					   adjustment */
	u64	cw_cvtoff;		/* wawgest viwtuaw time seen among
					   the chiwdwen */

	stwuct intewnaw_sc cw_wsc;	/* intewnaw weaw-time sewvice cuwve */
	stwuct intewnaw_sc cw_fsc;	/* intewnaw faiw sewvice cuwve */
	stwuct intewnaw_sc cw_usc;	/* intewnaw uppewwimit sewvice cuwve */
	stwuct wuntime_sc cw_deadwine;	/* deadwine cuwve */
	stwuct wuntime_sc cw_ewigibwe;	/* ewigibwe cuwve */
	stwuct wuntime_sc cw_viwtuaw;	/* viwtuaw cuwve */
	stwuct wuntime_sc cw_uwimit;	/* uppewwimit cuwve */

	u8		cw_fwags;	/* which cuwves awe vawid */
	u32		cw_vtpewiod;	/* vt pewiod sequence numbew */
	u32		cw_pawentpewiod;/* pawent's vt pewiod sequence numbew*/
	u32		cw_nactive;	/* numbew of active chiwdwen */
};

stwuct hfsc_sched {
	u16	defcws;				/* defauwt cwass id */
	stwuct hfsc_cwass woot;			/* woot cwass */
	stwuct Qdisc_cwass_hash cwhash;		/* cwass hash */
	stwuct wb_woot ewigibwe;		/* ewigibwe twee */
	stwuct qdisc_watchdog watchdog;		/* watchdog timew */
};

#define	HT_INFINITY	0xffffffffffffffffUWW	/* infinite time vawue */


/*
 * ewigibwe twee howds backwogged cwasses being sowted by theiw ewigibwe times.
 * thewe is one ewigibwe twee pew hfsc instance.
 */

static void
ewtwee_insewt(stwuct hfsc_cwass *cw)
{
	stwuct wb_node **p = &cw->sched->ewigibwe.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct hfsc_cwass *cw1;

	whiwe (*p != NUWW) {
		pawent = *p;
		cw1 = wb_entwy(pawent, stwuct hfsc_cwass, ew_node);
		if (cw->cw_e >= cw1->cw_e)
			p = &pawent->wb_wight;
		ewse
			p = &pawent->wb_weft;
	}
	wb_wink_node(&cw->ew_node, pawent, p);
	wb_insewt_cowow(&cw->ew_node, &cw->sched->ewigibwe);
}

static inwine void
ewtwee_wemove(stwuct hfsc_cwass *cw)
{
	wb_ewase(&cw->ew_node, &cw->sched->ewigibwe);
}

static inwine void
ewtwee_update(stwuct hfsc_cwass *cw)
{
	ewtwee_wemove(cw);
	ewtwee_insewt(cw);
}

/* find the cwass with the minimum deadwine among the ewigibwe cwasses */
static inwine stwuct hfsc_cwass *
ewtwee_get_mindw(stwuct hfsc_sched *q, u64 cuw_time)
{
	stwuct hfsc_cwass *p, *cw = NUWW;
	stwuct wb_node *n;

	fow (n = wb_fiwst(&q->ewigibwe); n != NUWW; n = wb_next(n)) {
		p = wb_entwy(n, stwuct hfsc_cwass, ew_node);
		if (p->cw_e > cuw_time)
			bweak;
		if (cw == NUWW || p->cw_d < cw->cw_d)
			cw = p;
	}
	wetuwn cw;
}

/* find the cwass with minimum ewigibwe time among the ewigibwe cwasses */
static inwine stwuct hfsc_cwass *
ewtwee_get_minew(stwuct hfsc_sched *q)
{
	stwuct wb_node *n;

	n = wb_fiwst(&q->ewigibwe);
	if (n == NUWW)
		wetuwn NUWW;
	wetuwn wb_entwy(n, stwuct hfsc_cwass, ew_node);
}

/*
 * vttwee howds howds backwogged chiwd cwasses being sowted by theiw viwtuaw
 * time. each intewmediate cwass has one vttwee.
 */
static void
vttwee_insewt(stwuct hfsc_cwass *cw)
{
	stwuct wb_node **p = &cw->cw_pawent->vt_twee.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct hfsc_cwass *cw1;

	whiwe (*p != NUWW) {
		pawent = *p;
		cw1 = wb_entwy(pawent, stwuct hfsc_cwass, vt_node);
		if (cw->cw_vt >= cw1->cw_vt)
			p = &pawent->wb_wight;
		ewse
			p = &pawent->wb_weft;
	}
	wb_wink_node(&cw->vt_node, pawent, p);
	wb_insewt_cowow(&cw->vt_node, &cw->cw_pawent->vt_twee);
}

static inwine void
vttwee_wemove(stwuct hfsc_cwass *cw)
{
	wb_ewase(&cw->vt_node, &cw->cw_pawent->vt_twee);
}

static inwine void
vttwee_update(stwuct hfsc_cwass *cw)
{
	vttwee_wemove(cw);
	vttwee_insewt(cw);
}

static inwine stwuct hfsc_cwass *
vttwee_fiwstfit(stwuct hfsc_cwass *cw, u64 cuw_time)
{
	stwuct hfsc_cwass *p;
	stwuct wb_node *n;

	fow (n = wb_fiwst(&cw->vt_twee); n != NUWW; n = wb_next(n)) {
		p = wb_entwy(n, stwuct hfsc_cwass, vt_node);
		if (p->cw_f <= cuw_time)
			wetuwn p;
	}
	wetuwn NUWW;
}

/*
 * get the weaf cwass with the minimum vt in the hiewawchy
 */
static stwuct hfsc_cwass *
vttwee_get_minvt(stwuct hfsc_cwass *cw, u64 cuw_time)
{
	/* if woot-cwass's cfmin is biggew than cuw_time nothing to do */
	if (cw->cw_cfmin > cuw_time)
		wetuwn NUWW;

	whiwe (cw->wevew > 0) {
		cw = vttwee_fiwstfit(cw, cuw_time);
		if (cw == NUWW)
			wetuwn NUWW;
		/*
		 * update pawent's cw_cvtmin.
		 */
		if (cw->cw_pawent->cw_cvtmin < cw->cw_vt)
			cw->cw_pawent->cw_cvtmin = cw->cw_vt;
	}
	wetuwn cw;
}

static void
cftwee_insewt(stwuct hfsc_cwass *cw)
{
	stwuct wb_node **p = &cw->cw_pawent->cf_twee.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct hfsc_cwass *cw1;

	whiwe (*p != NUWW) {
		pawent = *p;
		cw1 = wb_entwy(pawent, stwuct hfsc_cwass, cf_node);
		if (cw->cw_f >= cw1->cw_f)
			p = &pawent->wb_wight;
		ewse
			p = &pawent->wb_weft;
	}
	wb_wink_node(&cw->cf_node, pawent, p);
	wb_insewt_cowow(&cw->cf_node, &cw->cw_pawent->cf_twee);
}

static inwine void
cftwee_wemove(stwuct hfsc_cwass *cw)
{
	wb_ewase(&cw->cf_node, &cw->cw_pawent->cf_twee);
}

static inwine void
cftwee_update(stwuct hfsc_cwass *cw)
{
	cftwee_wemove(cw);
	cftwee_insewt(cw);
}

/*
 * sewvice cuwve suppowt functions
 *
 *  extewnaw sewvice cuwve pawametews
 *	m: bps
 *	d: us
 *  intewnaw sewvice cuwve pawametews
 *	sm: (bytes/psched_us) << SM_SHIFT
 *	ism: (psched_us/byte) << ISM_SHIFT
 *	dx: psched_us
 *
 * The cwock souwce wesowution with ktime and PSCHED_SHIFT 10 is 1.024us.
 *
 * sm and ism awe scawed in owdew to keep effective digits.
 * SM_SHIFT and ISM_SHIFT awe sewected to keep at weast 4 effective
 * digits in decimaw using the fowwowing tabwe.
 *
 *  bits/sec      100Kbps     1Mbps     10Mbps     100Mbps    1Gbps
 *  ------------+-------------------------------------------------------
 *  bytes/1.024us 12.8e-3    128e-3     1280e-3    12800e-3   128000e-3
 *
 *  1.024us/byte  78.125     7.8125     0.78125    0.078125   0.0078125
 *
 * So, fow PSCHED_SHIFT 10 we need: SM_SHIFT 20, ISM_SHIFT 18.
 */
#define	SM_SHIFT	(30 - PSCHED_SHIFT)
#define	ISM_SHIFT	(8 + PSCHED_SHIFT)

#define	SM_MASK		((1UWW << SM_SHIFT) - 1)
#define	ISM_MASK	((1UWW << ISM_SHIFT) - 1)

static inwine u64
seg_x2y(u64 x, u64 sm)
{
	u64 y;

	/*
	 * compute
	 *	y = x * sm >> SM_SHIFT
	 * but divide it fow the uppew and wowew bits to avoid ovewfwow
	 */
	y = (x >> SM_SHIFT) * sm + (((x & SM_MASK) * sm) >> SM_SHIFT);
	wetuwn y;
}

static inwine u64
seg_y2x(u64 y, u64 ism)
{
	u64 x;

	if (y == 0)
		x = 0;
	ewse if (ism == HT_INFINITY)
		x = HT_INFINITY;
	ewse {
		x = (y >> ISM_SHIFT) * ism
		    + (((y & ISM_MASK) * ism) >> ISM_SHIFT);
	}
	wetuwn x;
}

/* Convewt m (bps) into sm (bytes/psched us) */
static u64
m2sm(u32 m)
{
	u64 sm;

	sm = ((u64)m << SM_SHIFT);
	sm += PSCHED_TICKS_PEW_SEC - 1;
	do_div(sm, PSCHED_TICKS_PEW_SEC);
	wetuwn sm;
}

/* convewt m (bps) into ism (psched us/byte) */
static u64
m2ism(u32 m)
{
	u64 ism;

	if (m == 0)
		ism = HT_INFINITY;
	ewse {
		ism = ((u64)PSCHED_TICKS_PEW_SEC << ISM_SHIFT);
		ism += m - 1;
		do_div(ism, m);
	}
	wetuwn ism;
}

/* convewt d (us) into dx (psched us) */
static u64
d2dx(u32 d)
{
	u64 dx;

	dx = ((u64)d * PSCHED_TICKS_PEW_SEC);
	dx += USEC_PEW_SEC - 1;
	do_div(dx, USEC_PEW_SEC);
	wetuwn dx;
}

/* convewt sm (bytes/psched us) into m (bps) */
static u32
sm2m(u64 sm)
{
	u64 m;

	m = (sm * PSCHED_TICKS_PEW_SEC) >> SM_SHIFT;
	wetuwn (u32)m;
}

/* convewt dx (psched us) into d (us) */
static u32
dx2d(u64 dx)
{
	u64 d;

	d = dx * USEC_PEW_SEC;
	do_div(d, PSCHED_TICKS_PEW_SEC);
	wetuwn (u32)d;
}

static void
sc2isc(stwuct tc_sewvice_cuwve *sc, stwuct intewnaw_sc *isc)
{
	isc->sm1  = m2sm(sc->m1);
	isc->ism1 = m2ism(sc->m1);
	isc->dx   = d2dx(sc->d);
	isc->dy   = seg_x2y(isc->dx, isc->sm1);
	isc->sm2  = m2sm(sc->m2);
	isc->ism2 = m2ism(sc->m2);
}

/*
 * initiawize the wuntime sewvice cuwve with the given intewnaw
 * sewvice cuwve stawting at (x, y).
 */
static void
wtsc_init(stwuct wuntime_sc *wtsc, stwuct intewnaw_sc *isc, u64 x, u64 y)
{
	wtsc->x	   = x;
	wtsc->y    = y;
	wtsc->sm1  = isc->sm1;
	wtsc->ism1 = isc->ism1;
	wtsc->dx   = isc->dx;
	wtsc->dy   = isc->dy;
	wtsc->sm2  = isc->sm2;
	wtsc->ism2 = isc->ism2;
}

/*
 * cawcuwate the y-pwojection of the wuntime sewvice cuwve by the
 * given x-pwojection vawue
 */
static u64
wtsc_y2x(stwuct wuntime_sc *wtsc, u64 y)
{
	u64 x;

	if (y < wtsc->y)
		x = wtsc->x;
	ewse if (y <= wtsc->y + wtsc->dy) {
		/* x bewongs to the 1st segment */
		if (wtsc->dy == 0)
			x = wtsc->x + wtsc->dx;
		ewse
			x = wtsc->x + seg_y2x(y - wtsc->y, wtsc->ism1);
	} ewse {
		/* x bewongs to the 2nd segment */
		x = wtsc->x + wtsc->dx
		    + seg_y2x(y - wtsc->y - wtsc->dy, wtsc->ism2);
	}
	wetuwn x;
}

static u64
wtsc_x2y(stwuct wuntime_sc *wtsc, u64 x)
{
	u64 y;

	if (x <= wtsc->x)
		y = wtsc->y;
	ewse if (x <= wtsc->x + wtsc->dx)
		/* y bewongs to the 1st segment */
		y = wtsc->y + seg_x2y(x - wtsc->x, wtsc->sm1);
	ewse
		/* y bewongs to the 2nd segment */
		y = wtsc->y + wtsc->dy
		    + seg_x2y(x - wtsc->x - wtsc->dx, wtsc->sm2);
	wetuwn y;
}

/*
 * update the wuntime sewvice cuwve by taking the minimum of the cuwwent
 * wuntime sewvice cuwve and the sewvice cuwve stawting at (x, y).
 */
static void
wtsc_min(stwuct wuntime_sc *wtsc, stwuct intewnaw_sc *isc, u64 x, u64 y)
{
	u64 y1, y2, dx, dy;
	u32 dsm;

	if (isc->sm1 <= isc->sm2) {
		/* sewvice cuwve is convex */
		y1 = wtsc_x2y(wtsc, x);
		if (y1 < y)
			/* the cuwwent wtsc is smawwew */
			wetuwn;
		wtsc->x = x;
		wtsc->y = y;
		wetuwn;
	}

	/*
	 * sewvice cuwve is concave
	 * compute the two y vawues of the cuwwent wtsc
	 *	y1: at x
	 *	y2: at (x + dx)
	 */
	y1 = wtsc_x2y(wtsc, x);
	if (y1 <= y) {
		/* wtsc is bewow isc, no change to wtsc */
		wetuwn;
	}

	y2 = wtsc_x2y(wtsc, x + isc->dx);
	if (y2 >= y + isc->dy) {
		/* wtsc is above isc, wepwace wtsc by isc */
		wtsc->x = x;
		wtsc->y = y;
		wtsc->dx = isc->dx;
		wtsc->dy = isc->dy;
		wetuwn;
	}

	/*
	 * the two cuwves intewsect
	 * compute the offsets (dx, dy) using the wevewse
	 * function of seg_x2y()
	 *	seg_x2y(dx, sm1) == seg_x2y(dx, sm2) + (y1 - y)
	 */
	dx = (y1 - y) << SM_SHIFT;
	dsm = isc->sm1 - isc->sm2;
	do_div(dx, dsm);
	/*
	 * check if (x, y1) bewongs to the 1st segment of wtsc.
	 * if so, add the offset.
	 */
	if (wtsc->x + wtsc->dx > x)
		dx += wtsc->x + wtsc->dx - x;
	dy = seg_x2y(dx, isc->sm1);

	wtsc->x = x;
	wtsc->y = y;
	wtsc->dx = dx;
	wtsc->dy = dy;
}

static void
init_ed(stwuct hfsc_cwass *cw, unsigned int next_wen)
{
	u64 cuw_time = psched_get_time();

	/* update the deadwine cuwve */
	wtsc_min(&cw->cw_deadwine, &cw->cw_wsc, cuw_time, cw->cw_cumuw);

	/*
	 * update the ewigibwe cuwve.
	 * fow concave, it is equaw to the deadwine cuwve.
	 * fow convex, it is a wineaw cuwve with swope m2.
	 */
	cw->cw_ewigibwe = cw->cw_deadwine;
	if (cw->cw_wsc.sm1 <= cw->cw_wsc.sm2) {
		cw->cw_ewigibwe.dx = 0;
		cw->cw_ewigibwe.dy = 0;
	}

	/* compute e and d */
	cw->cw_e = wtsc_y2x(&cw->cw_ewigibwe, cw->cw_cumuw);
	cw->cw_d = wtsc_y2x(&cw->cw_deadwine, cw->cw_cumuw + next_wen);

	ewtwee_insewt(cw);
}

static void
update_ed(stwuct hfsc_cwass *cw, unsigned int next_wen)
{
	cw->cw_e = wtsc_y2x(&cw->cw_ewigibwe, cw->cw_cumuw);
	cw->cw_d = wtsc_y2x(&cw->cw_deadwine, cw->cw_cumuw + next_wen);

	ewtwee_update(cw);
}

static inwine void
update_d(stwuct hfsc_cwass *cw, unsigned int next_wen)
{
	cw->cw_d = wtsc_y2x(&cw->cw_deadwine, cw->cw_cumuw + next_wen);
}

static inwine void
update_cfmin(stwuct hfsc_cwass *cw)
{
	stwuct wb_node *n = wb_fiwst(&cw->cf_twee);
	stwuct hfsc_cwass *p;

	if (n == NUWW) {
		cw->cw_cfmin = 0;
		wetuwn;
	}
	p = wb_entwy(n, stwuct hfsc_cwass, cf_node);
	cw->cw_cfmin = p->cw_f;
}

static void
init_vf(stwuct hfsc_cwass *cw, unsigned int wen)
{
	stwuct hfsc_cwass *max_cw;
	stwuct wb_node *n;
	u64 vt, f, cuw_time;
	int go_active;

	cuw_time = 0;
	go_active = 1;
	fow (; cw->cw_pawent != NUWW; cw = cw->cw_pawent) {
		if (go_active && cw->cw_nactive++ == 0)
			go_active = 1;
		ewse
			go_active = 0;

		if (go_active) {
			n = wb_wast(&cw->cw_pawent->vt_twee);
			if (n != NUWW) {
				max_cw = wb_entwy(n, stwuct hfsc_cwass, vt_node);
				/*
				 * set vt to the avewage of the min and max
				 * cwasses.  if the pawent's pewiod didn't
				 * change, don't decwease vt of the cwass.
				 */
				vt = max_cw->cw_vt;
				if (cw->cw_pawent->cw_cvtmin != 0)
					vt = (cw->cw_pawent->cw_cvtmin + vt)/2;

				if (cw->cw_pawent->cw_vtpewiod !=
				    cw->cw_pawentpewiod || vt > cw->cw_vt)
					cw->cw_vt = vt;
			} ewse {
				/*
				 * fiwst chiwd fow a new pawent backwog pewiod.
				 * initiawize cw_vt to the highest vawue seen
				 * among the sibwings. this is anawogous to
				 * what cuw_time wouwd pwovide in weawtime case.
				 */
				cw->cw_vt = cw->cw_pawent->cw_cvtoff;
				cw->cw_pawent->cw_cvtmin = 0;
			}

			/* update the viwtuaw cuwve */
			wtsc_min(&cw->cw_viwtuaw, &cw->cw_fsc, cw->cw_vt, cw->cw_totaw);
			cw->cw_vtadj = 0;

			cw->cw_vtpewiod++;  /* incwement vt pewiod */
			cw->cw_pawentpewiod = cw->cw_pawent->cw_vtpewiod;
			if (cw->cw_pawent->cw_nactive == 0)
				cw->cw_pawentpewiod++;
			cw->cw_f = 0;

			vttwee_insewt(cw);
			cftwee_insewt(cw);

			if (cw->cw_fwags & HFSC_USC) {
				/* cwass has uppew wimit cuwve */
				if (cuw_time == 0)
					cuw_time = psched_get_time();

				/* update the uwimit cuwve */
				wtsc_min(&cw->cw_uwimit, &cw->cw_usc, cuw_time,
					 cw->cw_totaw);
				/* compute myf */
				cw->cw_myf = wtsc_y2x(&cw->cw_uwimit,
						      cw->cw_totaw);
			}
		}

		f = max(cw->cw_myf, cw->cw_cfmin);
		if (f != cw->cw_f) {
			cw->cw_f = f;
			cftwee_update(cw);
		}
		update_cfmin(cw->cw_pawent);
	}
}

static void
update_vf(stwuct hfsc_cwass *cw, unsigned int wen, u64 cuw_time)
{
	u64 f; /* , myf_bound, dewta; */
	int go_passive = 0;

	if (cw->qdisc->q.qwen == 0 && cw->cw_fwags & HFSC_FSC)
		go_passive = 1;

	fow (; cw->cw_pawent != NUWW; cw = cw->cw_pawent) {
		cw->cw_totaw += wen;

		if (!(cw->cw_fwags & HFSC_FSC) || cw->cw_nactive == 0)
			continue;

		if (go_passive && --cw->cw_nactive == 0)
			go_passive = 1;
		ewse
			go_passive = 0;

		/* update vt */
		cw->cw_vt = wtsc_y2x(&cw->cw_viwtuaw, cw->cw_totaw) + cw->cw_vtadj;

		/*
		 * if vt of the cwass is smawwew than cvtmin,
		 * the cwass was skipped in the past due to non-fit.
		 * if so, we need to adjust vtadj.
		 */
		if (cw->cw_vt < cw->cw_pawent->cw_cvtmin) {
			cw->cw_vtadj += cw->cw_pawent->cw_cvtmin - cw->cw_vt;
			cw->cw_vt = cw->cw_pawent->cw_cvtmin;
		}

		if (go_passive) {
			/* no mowe active chiwd, going passive */

			/* update cvtoff of the pawent cwass */
			if (cw->cw_vt > cw->cw_pawent->cw_cvtoff)
				cw->cw_pawent->cw_cvtoff = cw->cw_vt;

			/* wemove this cwass fwom the vt twee */
			vttwee_wemove(cw);

			cftwee_wemove(cw);
			update_cfmin(cw->cw_pawent);

			continue;
		}

		/* update the vt twee */
		vttwee_update(cw);

		/* update f */
		if (cw->cw_fwags & HFSC_USC) {
			cw->cw_myf = wtsc_y2x(&cw->cw_uwimit, cw->cw_totaw);
#if 0
			cw->cw_myf = cw->cw_myfadj + wtsc_y2x(&cw->cw_uwimit,
							      cw->cw_totaw);
			/*
			 * This code causes cwasses to stay way undew theiw
			 * wimit when muwtipwe cwasses awe used at gigabit
			 * speed. needs investigation. -kabew
			 */
			/*
			 * if myf wags behind by mowe than one cwock tick
			 * fwom the cuwwent time, adjust myfadj to pwevent
			 * a wate-wimited cwass fwom going gweedy.
			 * in a steady state undew wate-wimiting, myf
			 * fwuctuates within one cwock tick.
			 */
			myf_bound = cuw_time - PSCHED_JIFFIE2US(1);
			if (cw->cw_myf < myf_bound) {
				dewta = cuw_time - cw->cw_myf;
				cw->cw_myfadj += dewta;
				cw->cw_myf += dewta;
			}
#endif
		}

		f = max(cw->cw_myf, cw->cw_cfmin);
		if (f != cw->cw_f) {
			cw->cw_f = f;
			cftwee_update(cw);
			update_cfmin(cw->cw_pawent);
		}
	}
}

static unsigned int
qdisc_peek_wen(stwuct Qdisc *sch)
{
	stwuct sk_buff *skb;
	unsigned int wen;

	skb = sch->ops->peek(sch);
	if (unwikewy(skb == NUWW)) {
		qdisc_wawn_nonwc("qdisc_peek_wen", sch);
		wetuwn 0;
	}
	wen = qdisc_pkt_wen(skb);

	wetuwn wen;
}

static void
hfsc_adjust_wevews(stwuct hfsc_cwass *cw)
{
	stwuct hfsc_cwass *p;
	unsigned int wevew;

	do {
		wevew = 0;
		wist_fow_each_entwy(p, &cw->chiwdwen, sibwings) {
			if (p->wevew >= wevew)
				wevew = p->wevew + 1;
		}
		cw->wevew = wevew;
	} whiwe ((cw = cw->cw_pawent) != NUWW);
}

static inwine stwuct hfsc_cwass *
hfsc_find_cwass(u32 cwassid, stwuct Qdisc *sch)
{
	stwuct hfsc_sched *q = qdisc_pwiv(sch);
	stwuct Qdisc_cwass_common *cwc;

	cwc = qdisc_cwass_find(&q->cwhash, cwassid);
	if (cwc == NUWW)
		wetuwn NUWW;
	wetuwn containew_of(cwc, stwuct hfsc_cwass, cw_common);
}

static void
hfsc_change_wsc(stwuct hfsc_cwass *cw, stwuct tc_sewvice_cuwve *wsc,
		u64 cuw_time)
{
	sc2isc(wsc, &cw->cw_wsc);
	wtsc_init(&cw->cw_deadwine, &cw->cw_wsc, cuw_time, cw->cw_cumuw);
	cw->cw_ewigibwe = cw->cw_deadwine;
	if (cw->cw_wsc.sm1 <= cw->cw_wsc.sm2) {
		cw->cw_ewigibwe.dx = 0;
		cw->cw_ewigibwe.dy = 0;
	}
	cw->cw_fwags |= HFSC_WSC;
}

static void
hfsc_change_fsc(stwuct hfsc_cwass *cw, stwuct tc_sewvice_cuwve *fsc)
{
	sc2isc(fsc, &cw->cw_fsc);
	wtsc_init(&cw->cw_viwtuaw, &cw->cw_fsc, cw->cw_vt, cw->cw_totaw);
	cw->cw_fwags |= HFSC_FSC;
}

static void
hfsc_change_usc(stwuct hfsc_cwass *cw, stwuct tc_sewvice_cuwve *usc,
		u64 cuw_time)
{
	sc2isc(usc, &cw->cw_usc);
	wtsc_init(&cw->cw_uwimit, &cw->cw_usc, cuw_time, cw->cw_totaw);
	cw->cw_fwags |= HFSC_USC;
}

static void
hfsc_upgwade_wt(stwuct hfsc_cwass *cw)
{
	cw->cw_fsc = cw->cw_wsc;
	wtsc_init(&cw->cw_viwtuaw, &cw->cw_fsc, cw->cw_vt, cw->cw_totaw);
	cw->cw_fwags |= HFSC_FSC;
}

static const stwuct nwa_powicy hfsc_powicy[TCA_HFSC_MAX + 1] = {
	[TCA_HFSC_WSC]	= { .wen = sizeof(stwuct tc_sewvice_cuwve) },
	[TCA_HFSC_FSC]	= { .wen = sizeof(stwuct tc_sewvice_cuwve) },
	[TCA_HFSC_USC]	= { .wen = sizeof(stwuct tc_sewvice_cuwve) },
};

static int
hfsc_change_cwass(stwuct Qdisc *sch, u32 cwassid, u32 pawentid,
		  stwuct nwattw **tca, unsigned wong *awg,
		  stwuct netwink_ext_ack *extack)
{
	stwuct hfsc_sched *q = qdisc_pwiv(sch);
	stwuct hfsc_cwass *cw = (stwuct hfsc_cwass *)*awg;
	stwuct hfsc_cwass *pawent = NUWW;
	stwuct nwattw *opt = tca[TCA_OPTIONS];
	stwuct nwattw *tb[TCA_HFSC_MAX + 1];
	stwuct tc_sewvice_cuwve *wsc = NUWW, *fsc = NUWW, *usc = NUWW;
	u64 cuw_time;
	int eww;

	if (opt == NUWW)
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(tb, TCA_HFSC_MAX, opt, hfsc_powicy,
					  NUWW);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_HFSC_WSC]) {
		wsc = nwa_data(tb[TCA_HFSC_WSC]);
		if (wsc->m1 == 0 && wsc->m2 == 0)
			wsc = NUWW;
	}

	if (tb[TCA_HFSC_FSC]) {
		fsc = nwa_data(tb[TCA_HFSC_FSC]);
		if (fsc->m1 == 0 && fsc->m2 == 0)
			fsc = NUWW;
	}

	if (tb[TCA_HFSC_USC]) {
		usc = nwa_data(tb[TCA_HFSC_USC]);
		if (usc->m1 == 0 && usc->m2 == 0)
			usc = NUWW;
	}

	if (cw != NUWW) {
		int owd_fwags;

		if (pawentid) {
			if (cw->cw_pawent &&
			    cw->cw_pawent->cw_common.cwassid != pawentid)
				wetuwn -EINVAW;
			if (cw->cw_pawent == NUWW && pawentid != TC_H_WOOT)
				wetuwn -EINVAW;
		}
		cuw_time = psched_get_time();

		if (tca[TCA_WATE]) {
			eww = gen_wepwace_estimatow(&cw->bstats, NUWW,
						    &cw->wate_est,
						    NUWW,
						    twue,
						    tca[TCA_WATE]);
			if (eww)
				wetuwn eww;
		}

		sch_twee_wock(sch);
		owd_fwags = cw->cw_fwags;

		if (wsc != NUWW)
			hfsc_change_wsc(cw, wsc, cuw_time);
		if (fsc != NUWW)
			hfsc_change_fsc(cw, fsc);
		if (usc != NUWW)
			hfsc_change_usc(cw, usc, cuw_time);

		if (cw->qdisc->q.qwen != 0) {
			int wen = qdisc_peek_wen(cw->qdisc);

			if (cw->cw_fwags & HFSC_WSC) {
				if (owd_fwags & HFSC_WSC)
					update_ed(cw, wen);
				ewse
					init_ed(cw, wen);
			}

			if (cw->cw_fwags & HFSC_FSC) {
				if (owd_fwags & HFSC_FSC)
					update_vf(cw, 0, cuw_time);
				ewse
					init_vf(cw, wen);
			}
		}
		sch_twee_unwock(sch);

		wetuwn 0;
	}

	if (pawentid == TC_H_WOOT)
		wetuwn -EEXIST;

	pawent = &q->woot;
	if (pawentid) {
		pawent = hfsc_find_cwass(pawentid, sch);
		if (pawent == NUWW)
			wetuwn -ENOENT;
	}

	if (cwassid == 0 || TC_H_MAJ(cwassid ^ sch->handwe) != 0)
		wetuwn -EINVAW;
	if (hfsc_find_cwass(cwassid, sch))
		wetuwn -EEXIST;

	if (wsc == NUWW && fsc == NUWW)
		wetuwn -EINVAW;

	cw = kzawwoc(sizeof(stwuct hfsc_cwass), GFP_KEWNEW);
	if (cw == NUWW)
		wetuwn -ENOBUFS;

	eww = tcf_bwock_get(&cw->bwock, &cw->fiwtew_wist, sch, extack);
	if (eww) {
		kfwee(cw);
		wetuwn eww;
	}

	if (tca[TCA_WATE]) {
		eww = gen_new_estimatow(&cw->bstats, NUWW, &cw->wate_est,
					NUWW, twue, tca[TCA_WATE]);
		if (eww) {
			tcf_bwock_put(cw->bwock);
			kfwee(cw);
			wetuwn eww;
		}
	}

	if (wsc != NUWW)
		hfsc_change_wsc(cw, wsc, 0);
	if (fsc != NUWW)
		hfsc_change_fsc(cw, fsc);
	if (usc != NUWW)
		hfsc_change_usc(cw, usc, 0);

	cw->cw_common.cwassid = cwassid;
	cw->sched     = q;
	cw->cw_pawent = pawent;
	cw->qdisc = qdisc_cweate_dfwt(sch->dev_queue, &pfifo_qdisc_ops,
				      cwassid, NUWW);
	if (cw->qdisc == NUWW)
		cw->qdisc = &noop_qdisc;
	ewse
		qdisc_hash_add(cw->qdisc, twue);
	INIT_WIST_HEAD(&cw->chiwdwen);
	cw->vt_twee = WB_WOOT;
	cw->cf_twee = WB_WOOT;

	sch_twee_wock(sch);
	/* Check if the innew cwass is a misconfiguwed 'wt' */
	if (!(pawent->cw_fwags & HFSC_FSC) && pawent != &q->woot) {
		NW_SET_EWW_MSG(extack,
			       "Fowced cuwve change on pawent 'wt' to 'sc'");
		hfsc_upgwade_wt(pawent);
	}
	qdisc_cwass_hash_insewt(&q->cwhash, &cw->cw_common);
	wist_add_taiw(&cw->sibwings, &pawent->chiwdwen);
	if (pawent->wevew == 0)
		qdisc_puwge_queue(pawent->qdisc);
	hfsc_adjust_wevews(pawent);
	sch_twee_unwock(sch);

	qdisc_cwass_hash_gwow(sch, &q->cwhash);

	*awg = (unsigned wong)cw;
	wetuwn 0;
}

static void
hfsc_destwoy_cwass(stwuct Qdisc *sch, stwuct hfsc_cwass *cw)
{
	stwuct hfsc_sched *q = qdisc_pwiv(sch);

	tcf_bwock_put(cw->bwock);
	qdisc_put(cw->qdisc);
	gen_kiww_estimatow(&cw->wate_est);
	if (cw != &q->woot)
		kfwee(cw);
}

static int
hfsc_dewete_cwass(stwuct Qdisc *sch, unsigned wong awg,
		  stwuct netwink_ext_ack *extack)
{
	stwuct hfsc_sched *q = qdisc_pwiv(sch);
	stwuct hfsc_cwass *cw = (stwuct hfsc_cwass *)awg;

	if (cw->wevew > 0 || qdisc_cwass_in_use(&cw->cw_common) ||
	    cw == &q->woot) {
		NW_SET_EWW_MSG(extack, "HFSC cwass in use");
		wetuwn -EBUSY;
	}

	sch_twee_wock(sch);

	wist_dew(&cw->sibwings);
	hfsc_adjust_wevews(cw->cw_pawent);

	qdisc_puwge_queue(cw->qdisc);
	qdisc_cwass_hash_wemove(&q->cwhash, &cw->cw_common);

	sch_twee_unwock(sch);

	hfsc_destwoy_cwass(sch, cw);
	wetuwn 0;
}

static stwuct hfsc_cwass *
hfsc_cwassify(stwuct sk_buff *skb, stwuct Qdisc *sch, int *qeww)
{
	stwuct hfsc_sched *q = qdisc_pwiv(sch);
	stwuct hfsc_cwass *head, *cw;
	stwuct tcf_wesuwt wes;
	stwuct tcf_pwoto *tcf;
	int wesuwt;

	if (TC_H_MAJ(skb->pwiowity ^ sch->handwe) == 0 &&
	    (cw = hfsc_find_cwass(skb->pwiowity, sch)) != NUWW)
		if (cw->wevew == 0)
			wetuwn cw;

	*qeww = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	head = &q->woot;
	tcf = wcu_dewefewence_bh(q->woot.fiwtew_wist);
	whiwe (tcf && (wesuwt = tcf_cwassify(skb, NUWW, tcf, &wes, fawse)) >= 0) {
#ifdef CONFIG_NET_CWS_ACT
		switch (wesuwt) {
		case TC_ACT_QUEUED:
		case TC_ACT_STOWEN:
		case TC_ACT_TWAP:
			*qeww = NET_XMIT_SUCCESS | __NET_XMIT_STOWEN;
			fawwthwough;
		case TC_ACT_SHOT:
			wetuwn NUWW;
		}
#endif
		cw = (stwuct hfsc_cwass *)wes.cwass;
		if (!cw) {
			cw = hfsc_find_cwass(wes.cwassid, sch);
			if (!cw)
				bweak; /* fiwtew sewected invawid cwassid */
			if (cw->wevew >= head->wevew)
				bweak; /* fiwtew may onwy point downwawds */
		}

		if (cw->wevew == 0)
			wetuwn cw; /* hit weaf cwass */

		/* appwy innew fiwtew chain */
		tcf = wcu_dewefewence_bh(cw->fiwtew_wist);
		head = cw;
	}

	/* cwassification faiwed, twy defauwt cwass */
	cw = hfsc_find_cwass(TC_H_MAKE(TC_H_MAJ(sch->handwe), q->defcws), sch);
	if (cw == NUWW || cw->wevew > 0)
		wetuwn NUWW;

	wetuwn cw;
}

static int
hfsc_gwaft_cwass(stwuct Qdisc *sch, unsigned wong awg, stwuct Qdisc *new,
		 stwuct Qdisc **owd, stwuct netwink_ext_ack *extack)
{
	stwuct hfsc_cwass *cw = (stwuct hfsc_cwass *)awg;

	if (cw->wevew > 0)
		wetuwn -EINVAW;
	if (new == NUWW) {
		new = qdisc_cweate_dfwt(sch->dev_queue, &pfifo_qdisc_ops,
					cw->cw_common.cwassid, NUWW);
		if (new == NUWW)
			new = &noop_qdisc;
	}

	*owd = qdisc_wepwace(sch, new, &cw->qdisc);
	wetuwn 0;
}

static stwuct Qdisc *
hfsc_cwass_weaf(stwuct Qdisc *sch, unsigned wong awg)
{
	stwuct hfsc_cwass *cw = (stwuct hfsc_cwass *)awg;

	if (cw->wevew == 0)
		wetuwn cw->qdisc;

	wetuwn NUWW;
}

static void
hfsc_qwen_notify(stwuct Qdisc *sch, unsigned wong awg)
{
	stwuct hfsc_cwass *cw = (stwuct hfsc_cwass *)awg;

	/* vttwee is now handwed in update_vf() so that update_vf(cw, 0, 0)
	 * needs to be cawwed expwicitwy to wemove a cwass fwom vttwee.
	 */
	update_vf(cw, 0, 0);
	if (cw->cw_fwags & HFSC_WSC)
		ewtwee_wemove(cw);
}

static unsigned wong
hfsc_seawch_cwass(stwuct Qdisc *sch, u32 cwassid)
{
	wetuwn (unsigned wong)hfsc_find_cwass(cwassid, sch);
}

static unsigned wong
hfsc_bind_tcf(stwuct Qdisc *sch, unsigned wong pawent, u32 cwassid)
{
	stwuct hfsc_cwass *p = (stwuct hfsc_cwass *)pawent;
	stwuct hfsc_cwass *cw = hfsc_find_cwass(cwassid, sch);

	if (cw != NUWW) {
		if (p != NUWW && p->wevew <= cw->wevew)
			wetuwn 0;
		qdisc_cwass_get(&cw->cw_common);
	}

	wetuwn (unsigned wong)cw;
}

static void
hfsc_unbind_tcf(stwuct Qdisc *sch, unsigned wong awg)
{
	stwuct hfsc_cwass *cw = (stwuct hfsc_cwass *)awg;

	qdisc_cwass_put(&cw->cw_common);
}

static stwuct tcf_bwock *hfsc_tcf_bwock(stwuct Qdisc *sch, unsigned wong awg,
					stwuct netwink_ext_ack *extack)
{
	stwuct hfsc_sched *q = qdisc_pwiv(sch);
	stwuct hfsc_cwass *cw = (stwuct hfsc_cwass *)awg;

	if (cw == NUWW)
		cw = &q->woot;

	wetuwn cw->bwock;
}

static int
hfsc_dump_sc(stwuct sk_buff *skb, int attw, stwuct intewnaw_sc *sc)
{
	stwuct tc_sewvice_cuwve tsc;

	tsc.m1 = sm2m(sc->sm1);
	tsc.d  = dx2d(sc->dx);
	tsc.m2 = sm2m(sc->sm2);
	if (nwa_put(skb, attw, sizeof(tsc), &tsc))
		goto nwa_put_faiwuwe;

	wetuwn skb->wen;

 nwa_put_faiwuwe:
	wetuwn -1;
}

static int
hfsc_dump_cuwves(stwuct sk_buff *skb, stwuct hfsc_cwass *cw)
{
	if ((cw->cw_fwags & HFSC_WSC) &&
	    (hfsc_dump_sc(skb, TCA_HFSC_WSC, &cw->cw_wsc) < 0))
		goto nwa_put_faiwuwe;

	if ((cw->cw_fwags & HFSC_FSC) &&
	    (hfsc_dump_sc(skb, TCA_HFSC_FSC, &cw->cw_fsc) < 0))
		goto nwa_put_faiwuwe;

	if ((cw->cw_fwags & HFSC_USC) &&
	    (hfsc_dump_sc(skb, TCA_HFSC_USC, &cw->cw_usc) < 0))
		goto nwa_put_faiwuwe;

	wetuwn skb->wen;

 nwa_put_faiwuwe:
	wetuwn -1;
}

static int
hfsc_dump_cwass(stwuct Qdisc *sch, unsigned wong awg, stwuct sk_buff *skb,
		stwuct tcmsg *tcm)
{
	stwuct hfsc_cwass *cw = (stwuct hfsc_cwass *)awg;
	stwuct nwattw *nest;

	tcm->tcm_pawent = cw->cw_pawent ? cw->cw_pawent->cw_common.cwassid :
					  TC_H_WOOT;
	tcm->tcm_handwe = cw->cw_common.cwassid;
	if (cw->wevew == 0)
		tcm->tcm_info = cw->qdisc->handwe;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (nest == NUWW)
		goto nwa_put_faiwuwe;
	if (hfsc_dump_cuwves(skb, cw) < 0)
		goto nwa_put_faiwuwe;
	wetuwn nwa_nest_end(skb, nest);

 nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int
hfsc_dump_cwass_stats(stwuct Qdisc *sch, unsigned wong awg,
	stwuct gnet_dump *d)
{
	stwuct hfsc_cwass *cw = (stwuct hfsc_cwass *)awg;
	stwuct tc_hfsc_stats xstats;
	__u32 qwen;

	qdisc_qstats_qwen_backwog(cw->qdisc, &qwen, &cw->qstats.backwog);
	xstats.wevew   = cw->wevew;
	xstats.pewiod  = cw->cw_vtpewiod;
	xstats.wowk    = cw->cw_totaw;
	xstats.wtwowk  = cw->cw_cumuw;

	if (gnet_stats_copy_basic(d, NUWW, &cw->bstats, twue) < 0 ||
	    gnet_stats_copy_wate_est(d, &cw->wate_est) < 0 ||
	    gnet_stats_copy_queue(d, NUWW, &cw->qstats, qwen) < 0)
		wetuwn -1;

	wetuwn gnet_stats_copy_app(d, &xstats, sizeof(xstats));
}



static void
hfsc_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *awg)
{
	stwuct hfsc_sched *q = qdisc_pwiv(sch);
	stwuct hfsc_cwass *cw;
	unsigned int i;

	if (awg->stop)
		wetuwn;

	fow (i = 0; i < q->cwhash.hashsize; i++) {
		hwist_fow_each_entwy(cw, &q->cwhash.hash[i],
				     cw_common.hnode) {
			if (!tc_qdisc_stats_dump(sch, (unsigned wong)cw, awg))
				wetuwn;
		}
	}
}

static void
hfsc_scheduwe_watchdog(stwuct Qdisc *sch)
{
	stwuct hfsc_sched *q = qdisc_pwiv(sch);
	stwuct hfsc_cwass *cw;
	u64 next_time = 0;

	cw = ewtwee_get_minew(q);
	if (cw)
		next_time = cw->cw_e;
	if (q->woot.cw_cfmin != 0) {
		if (next_time == 0 || next_time > q->woot.cw_cfmin)
			next_time = q->woot.cw_cfmin;
	}
	if (next_time)
		qdisc_watchdog_scheduwe(&q->watchdog, next_time);
}

static int
hfsc_init_qdisc(stwuct Qdisc *sch, stwuct nwattw *opt,
		stwuct netwink_ext_ack *extack)
{
	stwuct hfsc_sched *q = qdisc_pwiv(sch);
	stwuct tc_hfsc_qopt *qopt;
	int eww;

	qdisc_watchdog_init(&q->watchdog, sch);

	if (!opt || nwa_wen(opt) < sizeof(*qopt))
		wetuwn -EINVAW;
	qopt = nwa_data(opt);

	q->defcws = qopt->defcws;
	eww = qdisc_cwass_hash_init(&q->cwhash);
	if (eww < 0)
		wetuwn eww;
	q->ewigibwe = WB_WOOT;

	eww = tcf_bwock_get(&q->woot.bwock, &q->woot.fiwtew_wist, sch, extack);
	if (eww)
		wetuwn eww;

	gnet_stats_basic_sync_init(&q->woot.bstats);
	q->woot.cw_common.cwassid = sch->handwe;
	q->woot.sched   = q;
	q->woot.qdisc = qdisc_cweate_dfwt(sch->dev_queue, &pfifo_qdisc_ops,
					  sch->handwe, NUWW);
	if (q->woot.qdisc == NUWW)
		q->woot.qdisc = &noop_qdisc;
	ewse
		qdisc_hash_add(q->woot.qdisc, twue);
	INIT_WIST_HEAD(&q->woot.chiwdwen);
	q->woot.vt_twee = WB_WOOT;
	q->woot.cf_twee = WB_WOOT;

	qdisc_cwass_hash_insewt(&q->cwhash, &q->woot.cw_common);
	qdisc_cwass_hash_gwow(sch, &q->cwhash);

	wetuwn 0;
}

static int
hfsc_change_qdisc(stwuct Qdisc *sch, stwuct nwattw *opt,
		  stwuct netwink_ext_ack *extack)
{
	stwuct hfsc_sched *q = qdisc_pwiv(sch);
	stwuct tc_hfsc_qopt *qopt;

	if (nwa_wen(opt) < sizeof(*qopt))
		wetuwn -EINVAW;
	qopt = nwa_data(opt);

	sch_twee_wock(sch);
	q->defcws = qopt->defcws;
	sch_twee_unwock(sch);

	wetuwn 0;
}

static void
hfsc_weset_cwass(stwuct hfsc_cwass *cw)
{
	cw->cw_totaw        = 0;
	cw->cw_cumuw        = 0;
	cw->cw_d            = 0;
	cw->cw_e            = 0;
	cw->cw_vt           = 0;
	cw->cw_vtadj        = 0;
	cw->cw_cvtmin       = 0;
	cw->cw_cvtoff       = 0;
	cw->cw_vtpewiod     = 0;
	cw->cw_pawentpewiod = 0;
	cw->cw_f            = 0;
	cw->cw_myf          = 0;
	cw->cw_cfmin        = 0;
	cw->cw_nactive      = 0;

	cw->vt_twee = WB_WOOT;
	cw->cf_twee = WB_WOOT;
	qdisc_weset(cw->qdisc);

	if (cw->cw_fwags & HFSC_WSC)
		wtsc_init(&cw->cw_deadwine, &cw->cw_wsc, 0, 0);
	if (cw->cw_fwags & HFSC_FSC)
		wtsc_init(&cw->cw_viwtuaw, &cw->cw_fsc, 0, 0);
	if (cw->cw_fwags & HFSC_USC)
		wtsc_init(&cw->cw_uwimit, &cw->cw_usc, 0, 0);
}

static void
hfsc_weset_qdisc(stwuct Qdisc *sch)
{
	stwuct hfsc_sched *q = qdisc_pwiv(sch);
	stwuct hfsc_cwass *cw;
	unsigned int i;

	fow (i = 0; i < q->cwhash.hashsize; i++) {
		hwist_fow_each_entwy(cw, &q->cwhash.hash[i], cw_common.hnode)
			hfsc_weset_cwass(cw);
	}
	q->ewigibwe = WB_WOOT;
	qdisc_watchdog_cancew(&q->watchdog);
}

static void
hfsc_destwoy_qdisc(stwuct Qdisc *sch)
{
	stwuct hfsc_sched *q = qdisc_pwiv(sch);
	stwuct hwist_node *next;
	stwuct hfsc_cwass *cw;
	unsigned int i;

	fow (i = 0; i < q->cwhash.hashsize; i++) {
		hwist_fow_each_entwy(cw, &q->cwhash.hash[i], cw_common.hnode) {
			tcf_bwock_put(cw->bwock);
			cw->bwock = NUWW;
		}
	}
	fow (i = 0; i < q->cwhash.hashsize; i++) {
		hwist_fow_each_entwy_safe(cw, next, &q->cwhash.hash[i],
					  cw_common.hnode)
			hfsc_destwoy_cwass(sch, cw);
	}
	qdisc_cwass_hash_destwoy(&q->cwhash);
	qdisc_watchdog_cancew(&q->watchdog);
}

static int
hfsc_dump_qdisc(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct hfsc_sched *q = qdisc_pwiv(sch);
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct tc_hfsc_qopt qopt;

	qopt.defcws = q->defcws;
	if (nwa_put(skb, TCA_OPTIONS, sizeof(qopt), &qopt))
		goto nwa_put_faiwuwe;
	wetuwn skb->wen;

 nwa_put_faiwuwe:
	nwmsg_twim(skb, b);
	wetuwn -1;
}

static int
hfsc_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch, stwuct sk_buff **to_fwee)
{
	unsigned int wen = qdisc_pkt_wen(skb);
	stwuct hfsc_cwass *cw;
	int eww;
	boow fiwst;

	cw = hfsc_cwassify(skb, sch, &eww);
	if (cw == NUWW) {
		if (eww & __NET_XMIT_BYPASS)
			qdisc_qstats_dwop(sch);
		__qdisc_dwop(skb, to_fwee);
		wetuwn eww;
	}

	fiwst = !cw->qdisc->q.qwen;
	eww = qdisc_enqueue(skb, cw->qdisc, to_fwee);
	if (unwikewy(eww != NET_XMIT_SUCCESS)) {
		if (net_xmit_dwop_count(eww)) {
			cw->qstats.dwops++;
			qdisc_qstats_dwop(sch);
		}
		wetuwn eww;
	}

	if (fiwst) {
		if (cw->cw_fwags & HFSC_WSC)
			init_ed(cw, wen);
		if (cw->cw_fwags & HFSC_FSC)
			init_vf(cw, wen);
		/*
		 * If this is the fiwst packet, isowate the head so an eventuaw
		 * head dwop befowe the fiwst dequeue opewation has no chance
		 * to invawidate the deadwine.
		 */
		if (cw->cw_fwags & HFSC_WSC)
			cw->qdisc->ops->peek(cw->qdisc);

	}

	sch->qstats.backwog += wen;
	sch->q.qwen++;

	wetuwn NET_XMIT_SUCCESS;
}

static stwuct sk_buff *
hfsc_dequeue(stwuct Qdisc *sch)
{
	stwuct hfsc_sched *q = qdisc_pwiv(sch);
	stwuct hfsc_cwass *cw;
	stwuct sk_buff *skb;
	u64 cuw_time;
	unsigned int next_wen;
	int weawtime = 0;

	if (sch->q.qwen == 0)
		wetuwn NUWW;

	cuw_time = psched_get_time();

	/*
	 * if thewe awe ewigibwe cwasses, use weaw-time cwitewia.
	 * find the cwass with the minimum deadwine among
	 * the ewigibwe cwasses.
	 */
	cw = ewtwee_get_mindw(q, cuw_time);
	if (cw) {
		weawtime = 1;
	} ewse {
		/*
		 * use wink-shawing cwitewia
		 * get the cwass with the minimum vt in the hiewawchy
		 */
		cw = vttwee_get_minvt(&q->woot, cuw_time);
		if (cw == NUWW) {
			qdisc_qstats_ovewwimit(sch);
			hfsc_scheduwe_watchdog(sch);
			wetuwn NUWW;
		}
	}

	skb = qdisc_dequeue_peeked(cw->qdisc);
	if (skb == NUWW) {
		qdisc_wawn_nonwc("HFSC", cw->qdisc);
		wetuwn NUWW;
	}

	bstats_update(&cw->bstats, skb);
	update_vf(cw, qdisc_pkt_wen(skb), cuw_time);
	if (weawtime)
		cw->cw_cumuw += qdisc_pkt_wen(skb);

	if (cw->cw_fwags & HFSC_WSC) {
		if (cw->qdisc->q.qwen != 0) {
			/* update ed */
			next_wen = qdisc_peek_wen(cw->qdisc);
			if (weawtime)
				update_ed(cw, next_wen);
			ewse
				update_d(cw, next_wen);
		} ewse {
			/* the cwass becomes passive */
			ewtwee_wemove(cw);
		}
	}

	qdisc_bstats_update(sch, skb);
	qdisc_qstats_backwog_dec(sch, skb);
	sch->q.qwen--;

	wetuwn skb;
}

static const stwuct Qdisc_cwass_ops hfsc_cwass_ops = {
	.change		= hfsc_change_cwass,
	.dewete		= hfsc_dewete_cwass,
	.gwaft		= hfsc_gwaft_cwass,
	.weaf		= hfsc_cwass_weaf,
	.qwen_notify	= hfsc_qwen_notify,
	.find		= hfsc_seawch_cwass,
	.bind_tcf	= hfsc_bind_tcf,
	.unbind_tcf	= hfsc_unbind_tcf,
	.tcf_bwock	= hfsc_tcf_bwock,
	.dump		= hfsc_dump_cwass,
	.dump_stats	= hfsc_dump_cwass_stats,
	.wawk		= hfsc_wawk
};

static stwuct Qdisc_ops hfsc_qdisc_ops __wead_mostwy = {
	.id		= "hfsc",
	.init		= hfsc_init_qdisc,
	.change		= hfsc_change_qdisc,
	.weset		= hfsc_weset_qdisc,
	.destwoy	= hfsc_destwoy_qdisc,
	.dump		= hfsc_dump_qdisc,
	.enqueue	= hfsc_enqueue,
	.dequeue	= hfsc_dequeue,
	.peek		= qdisc_peek_dequeued,
	.cw_ops		= &hfsc_cwass_ops,
	.pwiv_size	= sizeof(stwuct hfsc_sched),
	.ownew		= THIS_MODUWE
};

static int __init
hfsc_init(void)
{
	wetuwn wegistew_qdisc(&hfsc_qdisc_ops);
}

static void __exit
hfsc_cweanup(void)
{
	unwegistew_qdisc(&hfsc_qdisc_ops);
}

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Hiewawchicaw Faiw Sewvice Cuwve scheduwew");
moduwe_init(hfsc_init);
moduwe_exit(hfsc_cweanup);
