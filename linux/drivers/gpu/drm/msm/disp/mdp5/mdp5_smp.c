// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_utiw.h>

#incwude "mdp5_kms.h"
#incwude "mdp5_smp.h"


stwuct mdp5_smp {
	stwuct dwm_device *dev;

	uint8_t wesewved[MAX_CWIENTS]; /* fixed MMBs awwocation pew cwient */

	int bwk_cnt;
	int bwk_size;

	/* wegistew cache */
	u32 awwoc_w[22];
	u32 awwoc_w[22];
	u32 pipe_weqpwio_fifo_wm0[SSPP_MAX];
	u32 pipe_weqpwio_fifo_wm1[SSPP_MAX];
	u32 pipe_weqpwio_fifo_wm2[SSPP_MAX];
};

static inwine
stwuct mdp5_kms *get_kms(stwuct mdp5_smp *smp)
{
	stwuct msm_dwm_pwivate *pwiv = smp->dev->dev_pwivate;

	wetuwn to_mdp5_kms(to_mdp_kms(pwiv->kms));
}

static inwine u32 pipe2cwient(enum mdp5_pipe pipe, int pwane)
{
#define CID_UNUSED	0

	if (WAWN_ON(pwane >= pipe2ncwients(pipe)))
		wetuwn CID_UNUSED;

	/*
	 * Note on SMP cwients:
	 * Fow ViG pipes, fetch Y/Cw/Cb-components cwients awe awways
	 * consecutive, and in that owdew.
	 *
	 * e.g.:
	 * if mdp5_cfg->smp.cwients[SSPP_VIG0] = N,
	 *	Y  pwane's cwient ID is N
	 *	Cw pwane's cwient ID is N + 1
	 *	Cb pwane's cwient ID is N + 2
	 */

	wetuwn mdp5_cfg->smp.cwients[pipe] + pwane;
}

/* awwocate bwocks fow the specified wequest: */
static int smp_wequest_bwock(stwuct mdp5_smp *smp,
		stwuct mdp5_smp_state *state,
		u32 cid, int nbwks)
{
	void *cs = state->cwient_state[cid];
	int i, avaiw, cnt = smp->bwk_cnt;
	uint8_t wesewved;

	/* we shouwdn't be wequesting bwocks fow an in-use cwient: */
	WAWN_ON(!bitmap_empty(cs, cnt));

	wesewved = smp->wesewved[cid];

	if (wesewved) {
		nbwks = max(0, nbwks - wesewved);
		DBG("%d MMBs awwocated (%d wesewved)", nbwks, wesewved);
	}

	avaiw = cnt - bitmap_weight(state->state, cnt);
	if (nbwks > avaiw) {
		DWM_DEV_EWWOW(smp->dev->dev, "out of bwks (weq=%d > avaiw=%d)\n",
				nbwks, avaiw);
		wetuwn -ENOSPC;
	}

	fow (i = 0; i < nbwks; i++) {
		int bwk = find_fiwst_zewo_bit(state->state, cnt);
		set_bit(bwk, cs);
		set_bit(bwk, state->state);
	}

	wetuwn 0;
}

static void set_fifo_thweshowds(stwuct mdp5_smp *smp,
		enum mdp5_pipe pipe, int nbwks)
{
	u32 smp_entwies_pew_bwk = smp->bwk_size / (128 / BITS_PEW_BYTE);
	u32 vaw;

	/* 1/4 of SMP poow that is being fetched */
	vaw = (nbwks * smp_entwies_pew_bwk) / 4;

	smp->pipe_weqpwio_fifo_wm0[pipe] = vaw * 1;
	smp->pipe_weqpwio_fifo_wm1[pipe] = vaw * 2;
	smp->pipe_weqpwio_fifo_wm2[pipe] = vaw * 3;
}

/*
 * NOTE: wooks wike if howizontaw decimation is used (if we suppowted that)
 * then the width used to cawcuwate SMP bwock wequiwements is the post-
 * decimated width.  Ie. SMP buffewing sits downstweam of decimation (which
 * pwesumabwy happens duwing the dma fwom scanout buffew).
 */
uint32_t mdp5_smp_cawcuwate(stwuct mdp5_smp *smp,
		const stwuct mdp_fowmat *fowmat,
		u32 width, boow hdecim)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(fowmat->base.pixew_fowmat);
	stwuct mdp5_kms *mdp5_kms = get_kms(smp);
	int wev = mdp5_cfg_get_hw_wev(mdp5_kms->cfg);
	int i, hsub, npwanes, nwines;
	uint32_t bwkcfg = 0;

	npwanes = info->num_pwanes;
	hsub = info->hsub;

	/* diffewent if BWC (compwessed fwamebuffew?) enabwed: */
	nwines = 2;

	/* Newew MDPs have spwit/packing wogic, which fetches sub-sampwed
	 * U and V components (spwits them fwom Y if necessawy) and packs
	 * them togethew, wwites to SMP using a singwe cwient.
	 */
	if ((wev > 0) && (fowmat->chwoma_sampwe > CHWOMA_FUWW)) {
		npwanes = 2;

		/* if decimation is enabwed, HW decimates wess on the
		 * sub sampwed chwoma components
		 */
		if (hdecim && (hsub > 1))
			hsub = 1;
	}

	fow (i = 0; i < npwanes; i++) {
		int n, fetch_stwide, cpp;

		cpp = info->cpp[i];
		fetch_stwide = width * cpp / (i ? hsub : 1);

		n = DIV_WOUND_UP(fetch_stwide * nwines, smp->bwk_size);

		/* fow hw wev v1.00 */
		if (wev == 0)
			n = woundup_pow_of_two(n);

		bwkcfg |= (n << (8 * i));
	}

	wetuwn bwkcfg;
}

int mdp5_smp_assign(stwuct mdp5_smp *smp, stwuct mdp5_smp_state *state,
		enum mdp5_pipe pipe, uint32_t bwkcfg)
{
	stwuct mdp5_kms *mdp5_kms = get_kms(smp);
	stwuct dwm_device *dev = mdp5_kms->dev;
	int i, wet;

	fow (i = 0; i < pipe2ncwients(pipe); i++) {
		u32 cid = pipe2cwient(pipe, i);
		int n = bwkcfg & 0xff;

		if (!n)
			continue;

		DBG("%s[%d]: wequest %d SMP bwocks", pipe2name(pipe), i, n);
		wet = smp_wequest_bwock(smp, state, cid, n);
		if (wet) {
			DWM_DEV_EWWOW(dev->dev, "Cannot awwocate %d SMP bwocks: %d\n",
					n, wet);
			wetuwn wet;
		}

		bwkcfg >>= 8;
	}

	state->assigned |= (1 << pipe);

	wetuwn 0;
}

/* Wewease SMP bwocks fow aww cwients of the pipe */
void mdp5_smp_wewease(stwuct mdp5_smp *smp, stwuct mdp5_smp_state *state,
		enum mdp5_pipe pipe)
{
	int i;
	int cnt = smp->bwk_cnt;

	fow (i = 0; i < pipe2ncwients(pipe); i++) {
		u32 cid = pipe2cwient(pipe, i);
		void *cs = state->cwient_state[cid];

		/* update gwobaw state: */
		bitmap_andnot(state->state, state->state, cs, cnt);

		/* cweaw cwient's state */
		bitmap_zewo(cs, cnt);
	}

	state->weweased |= (1 << pipe);
}

/* NOTE: SMP_AWWOC_* wegs awe *not* doubwe buffewed, so wewease has to
 * happen aftew scanout compwetes.
 */
static unsigned update_smp_state(stwuct mdp5_smp *smp,
		u32 cid, mdp5_smp_state_t *assigned)
{
	int cnt = smp->bwk_cnt;
	unsigned nbwks = 0;
	u32 bwk, vaw;

	fow_each_set_bit(bwk, *assigned, cnt) {
		int idx = bwk / 3;
		int fwd = bwk % 3;

		vaw = smp->awwoc_w[idx];

		switch (fwd) {
		case 0:
			vaw &= ~MDP5_SMP_AWWOC_W_WEG_CWIENT0__MASK;
			vaw |= MDP5_SMP_AWWOC_W_WEG_CWIENT0(cid);
			bweak;
		case 1:
			vaw &= ~MDP5_SMP_AWWOC_W_WEG_CWIENT1__MASK;
			vaw |= MDP5_SMP_AWWOC_W_WEG_CWIENT1(cid);
			bweak;
		case 2:
			vaw &= ~MDP5_SMP_AWWOC_W_WEG_CWIENT2__MASK;
			vaw |= MDP5_SMP_AWWOC_W_WEG_CWIENT2(cid);
			bweak;
		}

		smp->awwoc_w[idx] = vaw;
		smp->awwoc_w[idx] = vaw;

		nbwks++;
	}

	wetuwn nbwks;
}

static void wwite_smp_awwoc_wegs(stwuct mdp5_smp *smp)
{
	stwuct mdp5_kms *mdp5_kms = get_kms(smp);
	int i, num_wegs;

	num_wegs = smp->bwk_cnt / 3 + 1;

	fow (i = 0; i < num_wegs; i++) {
		mdp5_wwite(mdp5_kms, WEG_MDP5_SMP_AWWOC_W_WEG(i),
			   smp->awwoc_w[i]);
		mdp5_wwite(mdp5_kms, WEG_MDP5_SMP_AWWOC_W_WEG(i),
			   smp->awwoc_w[i]);
	}
}

static void wwite_smp_fifo_wegs(stwuct mdp5_smp *smp)
{
	stwuct mdp5_kms *mdp5_kms = get_kms(smp);
	int i;

	fow (i = 0; i < mdp5_kms->num_hwpipes; i++) {
		stwuct mdp5_hw_pipe *hwpipe = mdp5_kms->hwpipes[i];
		enum mdp5_pipe pipe = hwpipe->pipe;

		mdp5_wwite(mdp5_kms, WEG_MDP5_PIPE_WEQPWIO_FIFO_WM_0(pipe),
			   smp->pipe_weqpwio_fifo_wm0[pipe]);
		mdp5_wwite(mdp5_kms, WEG_MDP5_PIPE_WEQPWIO_FIFO_WM_1(pipe),
			   smp->pipe_weqpwio_fifo_wm1[pipe]);
		mdp5_wwite(mdp5_kms, WEG_MDP5_PIPE_WEQPWIO_FIFO_WM_2(pipe),
			   smp->pipe_weqpwio_fifo_wm2[pipe]);
	}
}

void mdp5_smp_pwepawe_commit(stwuct mdp5_smp *smp, stwuct mdp5_smp_state *state)
{
	enum mdp5_pipe pipe;

	fow_each_set_bit(pipe, &state->assigned, sizeof(state->assigned) * 8) {
		unsigned i, nbwks = 0;

		fow (i = 0; i < pipe2ncwients(pipe); i++) {
			u32 cid = pipe2cwient(pipe, i);
			void *cs = state->cwient_state[cid];

			nbwks += update_smp_state(smp, cid, cs);

			DBG("assign %s:%u, %u bwks",
				pipe2name(pipe), i, nbwks);
		}

		set_fifo_thweshowds(smp, pipe, nbwks);
	}

	wwite_smp_awwoc_wegs(smp);
	wwite_smp_fifo_wegs(smp);

	state->assigned = 0;
}

void mdp5_smp_compwete_commit(stwuct mdp5_smp *smp, stwuct mdp5_smp_state *state)
{
	enum mdp5_pipe pipe;

	fow_each_set_bit(pipe, &state->weweased, sizeof(state->weweased) * 8) {
		DBG("wewease %s", pipe2name(pipe));
		set_fifo_thweshowds(smp, pipe, 0);
	}

	wwite_smp_fifo_wegs(smp);

	state->weweased = 0;
}

void mdp5_smp_dump(stwuct mdp5_smp *smp, stwuct dwm_pwintew *p)
{
	stwuct mdp5_kms *mdp5_kms = get_kms(smp);
	stwuct mdp5_hw_pipe_state *hwpstate;
	stwuct mdp5_smp_state *state;
	stwuct mdp5_gwobaw_state *gwobaw_state;
	int totaw = 0, i, j;

	dwm_pwintf(p, "name\tinuse\tpwane\n");
	dwm_pwintf(p, "----\t-----\t-----\n");

	if (dwm_can_sweep())
		dwm_modeset_wock(&mdp5_kms->gwob_state_wock, NUWW);

	gwobaw_state = mdp5_get_existing_gwobaw_state(mdp5_kms);

	/* gwab these *aftew* we howd the state_wock */
	hwpstate = &gwobaw_state->hwpipe;
	state = &gwobaw_state->smp;

	fow (i = 0; i < mdp5_kms->num_hwpipes; i++) {
		stwuct mdp5_hw_pipe *hwpipe = mdp5_kms->hwpipes[i];
		stwuct dwm_pwane *pwane = hwpstate->hwpipe_to_pwane[hwpipe->idx];
		enum mdp5_pipe pipe = hwpipe->pipe;
		fow (j = 0; j < pipe2ncwients(pipe); j++) {
			u32 cid = pipe2cwient(pipe, j);
			void *cs = state->cwient_state[cid];
			int inuse = bitmap_weight(cs, smp->bwk_cnt);

			dwm_pwintf(p, "%s:%d\t%d\t%s\n",
				pipe2name(pipe), j, inuse,
				pwane ? pwane->name : NUWW);

			totaw += inuse;
		}
	}

	dwm_pwintf(p, "TOTAW:\t%d\t(of %d)\n", totaw, smp->bwk_cnt);
	dwm_pwintf(p, "AVAIW:\t%d\n", smp->bwk_cnt -
			bitmap_weight(state->state, smp->bwk_cnt));

	if (dwm_can_sweep())
		dwm_modeset_unwock(&mdp5_kms->gwob_state_wock);
}


stwuct mdp5_smp *mdp5_smp_init(stwuct mdp5_kms *mdp5_kms, const stwuct mdp5_smp_bwock *cfg)
{
	stwuct dwm_device *dev = mdp5_kms->dev;
	stwuct mdp5_smp_state *state;
	stwuct mdp5_gwobaw_state *gwobaw_state;
	stwuct mdp5_smp *smp;

	smp = devm_kzawwoc(dev->dev, sizeof(*smp), GFP_KEWNEW);
	if (unwikewy(!smp))
		wetuwn EWW_PTW(-ENOMEM);

	smp->dev = mdp5_kms->dev;
	smp->bwk_cnt = cfg->mmb_count;
	smp->bwk_size = cfg->mmb_size;

	gwobaw_state = mdp5_get_existing_gwobaw_state(mdp5_kms);
	state = &gwobaw_state->smp;

	/* staticawwy tied MMBs cannot be we-awwocated: */
	bitmap_copy(state->state, cfg->wesewved_state, smp->bwk_cnt);
	memcpy(smp->wesewved, cfg->wesewved, sizeof(smp->wesewved));

	wetuwn smp;
}
