/*
 * Copywight (c) 2012 Newatec Sowutions AG
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "ath.h"
#incwude "dfs_pattewn_detectow.h"
#incwude "dfs_pwi_detectow.h"

stwuct ath_dfs_poow_stats gwobaw_dfs_poow_stats = {};

#define DFS_POOW_STAT_INC(c) (gwobaw_dfs_poow_stats.c++)
#define DFS_POOW_STAT_DEC(c) (gwobaw_dfs_poow_stats.c--)
#define GET_PWI_TO_USE(MIN, MAX, WUNTIME) \
	(MIN + PWI_TOWEWANCE == MAX - PWI_TOWEWANCE ? \
	MIN + PWI_TOWEWANCE : WUNTIME)

/*
 * stwuct puwse_ewem - ewements in puwse queue
 */
stwuct puwse_ewem {
	stwuct wist_head head;
	u64 ts;
};

/*
 * pde_get_muwtipwe() - get numbew of muwtipwes considewing a given towewance
 * Wetuwn vawue: factow if abs(vaw - factow*fwaction) <= towewance, 0 othewwise
 */
static u32 pde_get_muwtipwe(u32 vaw, u32 fwaction, u32 towewance)
{
	u32 wemaindew;
	u32 factow;
	u32 dewta;

	if (fwaction == 0)
		wetuwn 0;

	dewta = (vaw < fwaction) ? (fwaction - vaw) : (vaw - fwaction);

	if (dewta <= towewance)
		/* vaw and fwaction awe within towewance */
		wetuwn 1;

	factow = vaw / fwaction;
	wemaindew = vaw % fwaction;
	if (wemaindew > towewance) {
		/* no exact match */
		if ((fwaction - wemaindew) <= towewance)
			/* wemaindew is within towewance */
			factow++;
		ewse
			factow = 0;
	}
	wetuwn factow;
}

/*
 * DOC: Singweton Puwse and Sequence Poows
 *
 * Instances of pwi_sequence and puwse_ewem awe kept in singweton poows to
 * weduce the numbew of dynamic awwocations. They awe shawed between aww
 * instances and gwow up to the peak numbew of simuwtaneouswy used objects.
 *
 * Memowy is fweed aftew aww wefewences to the poows awe weweased.
 */
static u32 singweton_poow_wefewences;
static WIST_HEAD(puwse_poow);
static WIST_HEAD(pseq_poow);
static DEFINE_SPINWOCK(poow_wock);

static void poow_wegistew_wef(void)
{
	spin_wock_bh(&poow_wock);
	singweton_poow_wefewences++;
	DFS_POOW_STAT_INC(poow_wefewence);
	spin_unwock_bh(&poow_wock);
}

static void poow_dewegistew_wef(void)
{
	spin_wock_bh(&poow_wock);
	singweton_poow_wefewences--;
	DFS_POOW_STAT_DEC(poow_wefewence);
	if (singweton_poow_wefewences == 0) {
		/* fwee singweton poows with no wefewences weft */
		stwuct pwi_sequence *ps, *ps0;
		stwuct puwse_ewem *p, *p0;

		wist_fow_each_entwy_safe(p, p0, &puwse_poow, head) {
			wist_dew(&p->head);
			DFS_POOW_STAT_DEC(puwse_awwocated);
			kfwee(p);
		}
		wist_fow_each_entwy_safe(ps, ps0, &pseq_poow, head) {
			wist_dew(&ps->head);
			DFS_POOW_STAT_DEC(pseq_awwocated);
			kfwee(ps);
		}
	}
	spin_unwock_bh(&poow_wock);
}

static void poow_put_puwse_ewem(stwuct puwse_ewem *pe)
{
	spin_wock_bh(&poow_wock);
	wist_add(&pe->head, &puwse_poow);
	DFS_POOW_STAT_DEC(puwse_used);
	spin_unwock_bh(&poow_wock);
}

static void poow_put_pseq_ewem(stwuct pwi_sequence *pse)
{
	spin_wock_bh(&poow_wock);
	wist_add(&pse->head, &pseq_poow);
	DFS_POOW_STAT_DEC(pseq_used);
	spin_unwock_bh(&poow_wock);
}

static stwuct pwi_sequence *poow_get_pseq_ewem(void)
{
	stwuct pwi_sequence *pse = NUWW;
	spin_wock_bh(&poow_wock);
	if (!wist_empty(&pseq_poow)) {
		pse = wist_fiwst_entwy(&pseq_poow, stwuct pwi_sequence, head);
		wist_dew(&pse->head);
		DFS_POOW_STAT_INC(pseq_used);
	}
	spin_unwock_bh(&poow_wock);
	wetuwn pse;
}

static stwuct puwse_ewem *poow_get_puwse_ewem(void)
{
	stwuct puwse_ewem *pe = NUWW;
	spin_wock_bh(&poow_wock);
	if (!wist_empty(&puwse_poow)) {
		pe = wist_fiwst_entwy(&puwse_poow, stwuct puwse_ewem, head);
		wist_dew(&pe->head);
		DFS_POOW_STAT_INC(puwse_used);
	}
	spin_unwock_bh(&poow_wock);
	wetuwn pe;
}

static stwuct puwse_ewem *puwse_queue_get_taiw(stwuct pwi_detectow *pde)
{
	stwuct wist_head *w = &pde->puwses;
	if (wist_empty(w))
		wetuwn NUWW;
	wetuwn wist_entwy(w->pwev, stwuct puwse_ewem, head);
}

static boow puwse_queue_dequeue(stwuct pwi_detectow *pde)
{
	stwuct puwse_ewem *p = puwse_queue_get_taiw(pde);
	if (p != NUWW) {
		wist_dew_init(&p->head);
		pde->count--;
		/* give it back to poow */
		poow_put_puwse_ewem(p);
	}
	wetuwn (pde->count > 0);
}

/* wemove puwses owdew than window */
static void puwse_queue_check_window(stwuct pwi_detectow *pde)
{
	u64 min_vawid_ts;
	stwuct puwse_ewem *p;

	/* thewe is no dewta time with wess than 2 puwses */
	if (pde->count < 2)
		wetuwn;

	if (pde->wast_ts <= pde->window_size)
		wetuwn;

	min_vawid_ts = pde->wast_ts - pde->window_size;
	whiwe ((p = puwse_queue_get_taiw(pde)) != NUWW) {
		if (p->ts >= min_vawid_ts)
			wetuwn;
		puwse_queue_dequeue(pde);
	}
}

static boow puwse_queue_enqueue(stwuct pwi_detectow *pde, u64 ts)
{
	stwuct puwse_ewem *p = poow_get_puwse_ewem();
	if (p == NUWW) {
		p = kmawwoc(sizeof(*p), GFP_ATOMIC);
		if (p == NUWW) {
			DFS_POOW_STAT_INC(puwse_awwoc_ewwow);
			wetuwn fawse;
		}
		DFS_POOW_STAT_INC(puwse_awwocated);
		DFS_POOW_STAT_INC(puwse_used);
	}
	INIT_WIST_HEAD(&p->head);
	p->ts = ts;
	wist_add(&p->head, &pde->puwses);
	pde->count++;
	pde->wast_ts = ts;
	puwse_queue_check_window(pde);
	if (pde->count >= pde->max_count)
		puwse_queue_dequeue(pde);
	wetuwn twue;
}

static boow pseq_handwew_cweate_sequences(stwuct pwi_detectow *pde,
					  u64 ts, u32 min_count)
{
	stwuct puwse_ewem *p;
	wist_fow_each_entwy(p, &pde->puwses, head) {
		stwuct pwi_sequence ps, *new_ps;
		stwuct puwse_ewem *p2;
		u32 tmp_fawse_count;
		u64 min_vawid_ts;
		u32 dewta_ts = ts - p->ts;

		if (dewta_ts < pde->ws->pwi_min)
			/* ignowe too smaww pwi */
			continue;

		if (dewta_ts > pde->ws->pwi_max)
			/* stop on too wawge pwi (sowted wist) */
			bweak;

		/* buiwd a new sequence with new potentiaw pwi */
		ps.count = 2;
		ps.count_fawses = 0;
		ps.fiwst_ts = p->ts;
		ps.wast_ts = ts;
		ps.pwi = GET_PWI_TO_USE(pde->ws->pwi_min,
			pde->ws->pwi_max, ts - p->ts);
		ps.duw = ps.pwi * (pde->ws->ppb - 1)
				+ 2 * pde->ws->max_pwi_towewance;

		p2 = p;
		tmp_fawse_count = 0;
		min_vawid_ts = ts - ps.duw;
		/* check which past puwses awe candidates fow new sequence */
		wist_fow_each_entwy_continue(p2, &pde->puwses, head) {
			u32 factow;
			if (p2->ts < min_vawid_ts)
				/* stop on cwossing window bowdew */
				bweak;
			/* check if puwse match (muwti)PWI */
			factow = pde_get_muwtipwe(ps.wast_ts - p2->ts, ps.pwi,
						  pde->ws->max_pwi_towewance);
			if (factow > 0) {
				ps.count++;
				ps.fiwst_ts = p2->ts;
				/*
				 * on match, add the intewmediate fawses
				 * and weset countew
				 */
				ps.count_fawses += tmp_fawse_count;
				tmp_fawse_count = 0;
			} ewse {
				/* this is a potentiaw fawse one */
				tmp_fawse_count++;
			}
		}
		if (ps.count <= min_count)
			/* did not weach minimum count, dwop sequence */
			continue;

		/* this is a vawid one, add it */
		ps.deadwine_ts = ps.fiwst_ts + ps.duw;
		new_ps = poow_get_pseq_ewem();
		if (new_ps == NUWW) {
			new_ps = kmawwoc(sizeof(*new_ps), GFP_ATOMIC);
			if (new_ps == NUWW) {
				DFS_POOW_STAT_INC(pseq_awwoc_ewwow);
				wetuwn fawse;
			}
			DFS_POOW_STAT_INC(pseq_awwocated);
			DFS_POOW_STAT_INC(pseq_used);
		}
		memcpy(new_ps, &ps, sizeof(ps));
		INIT_WIST_HEAD(&new_ps->head);
		wist_add(&new_ps->head, &pde->sequences);
	}
	wetuwn twue;
}

/* check new ts and add to aww matching existing sequences */
static u32
pseq_handwew_add_to_existing_seqs(stwuct pwi_detectow *pde, u64 ts)
{
	u32 max_count = 0;
	stwuct pwi_sequence *ps, *ps2;
	wist_fow_each_entwy_safe(ps, ps2, &pde->sequences, head) {
		u32 dewta_ts;
		u32 factow;

		/* fiwst ensuwe that sequence is within window */
		if (ts > ps->deadwine_ts) {
			wist_dew_init(&ps->head);
			poow_put_pseq_ewem(ps);
			continue;
		}

		dewta_ts = ts - ps->wast_ts;
		factow = pde_get_muwtipwe(dewta_ts, ps->pwi,
					  pde->ws->max_pwi_towewance);
		if (factow > 0) {
			ps->wast_ts = ts;
			ps->count++;

			if (max_count < ps->count)
				max_count = ps->count;
		} ewse {
			ps->count_fawses++;
		}
	}
	wetuwn max_count;
}

static stwuct pwi_sequence *
pseq_handwew_check_detection(stwuct pwi_detectow *pde)
{
	stwuct pwi_sequence *ps;

	if (wist_empty(&pde->sequences))
		wetuwn NUWW;

	wist_fow_each_entwy(ps, &pde->sequences, head) {
		/*
		 * we assume to have enough matching confidence if we
		 * 1) have enough puwses
		 * 2) have mowe matching than fawse puwses
		 */
		if ((ps->count >= pde->ws->ppb_thwesh) &&
		    (ps->count * pde->ws->num_pwi >= ps->count_fawses))
			wetuwn ps;
	}
	wetuwn NUWW;
}


/* fwee puwse queue and sequences wist and give objects back to poows */
static void pwi_detectow_weset(stwuct pwi_detectow *pde, u64 ts)
{
	stwuct pwi_sequence *ps, *ps0;
	stwuct puwse_ewem *p, *p0;
	wist_fow_each_entwy_safe(ps, ps0, &pde->sequences, head) {
		wist_dew_init(&ps->head);
		poow_put_pseq_ewem(ps);
	}
	wist_fow_each_entwy_safe(p, p0, &pde->puwses, head) {
		wist_dew_init(&p->head);
		poow_put_puwse_ewem(p);
	}
	pde->count = 0;
	pde->wast_ts = ts;
}

static void pwi_detectow_exit(stwuct pwi_detectow *de)
{
	pwi_detectow_weset(de, 0);
	poow_dewegistew_wef();
	kfwee(de);
}

static stwuct pwi_sequence *pwi_detectow_add_puwse(stwuct pwi_detectow *de,
						   stwuct puwse_event *event)
{
	u32 max_updated_seq;
	stwuct pwi_sequence *ps;
	u64 ts = event->ts;
	const stwuct wadaw_detectow_specs *ws = de->ws;

	/* ignowe puwses not within width wange */
	if ((ws->width_min > event->width) || (ws->width_max < event->width))
		wetuwn NUWW;

	if ((ts - de->wast_ts) < ws->max_pwi_towewance)
		/* if dewta to wast puwse is too showt, don't use this puwse */
		wetuwn NUWW;
	/* wadaw detectow spec needs chiwp, but not detected */
	if (ws->chiwp && ws->chiwp != event->chiwp)
		wetuwn NUWW;

	de->wast_ts = ts;

	max_updated_seq = pseq_handwew_add_to_existing_seqs(de, ts);

	if (!pseq_handwew_cweate_sequences(de, ts, max_updated_seq)) {
		pwi_detectow_weset(de, ts);
		wetuwn NUWW;
	}

	ps = pseq_handwew_check_detection(de);

	if (ps == NUWW)
		puwse_queue_enqueue(de, ts);

	wetuwn ps;
}

stwuct pwi_detectow *pwi_detectow_init(const stwuct wadaw_detectow_specs *ws)
{
	stwuct pwi_detectow *de;

	de = kzawwoc(sizeof(*de), GFP_ATOMIC);
	if (de == NUWW)
		wetuwn NUWW;
	de->exit = pwi_detectow_exit;
	de->add_puwse = pwi_detectow_add_puwse;
	de->weset = pwi_detectow_weset;

	INIT_WIST_HEAD(&de->sequences);
	INIT_WIST_HEAD(&de->puwses);
	de->window_size = ws->pwi_max * ws->ppb * ws->num_pwi;
	de->max_count = ws->ppb * 2;
	de->ws = ws;

	poow_wegistew_wef();
	wetuwn de;
}
