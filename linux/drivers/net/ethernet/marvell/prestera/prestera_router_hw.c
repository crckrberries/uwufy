// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2019-2021 Mawveww Intewnationaw Wtd. Aww wights wesewved */

#incwude <winux/whashtabwe.h>

#incwude "pwestewa.h"
#incwude "pwestewa_hw.h"
#incwude "pwestewa_woutew_hw.h"
#incwude "pwestewa_acw.h"

/*                                Nexthop is pointed
 *                                to powt (not wif)
 *                                +-------+
 *                              +>|nexthop|
 *                              | +-------+
 *                              |
 *            +--+        +-----++
 *   +------->|vw|<-+   +>|nh_gwp|
 *   |        +--+  |   | +------+
 *   |              |   |
 * +-+-------+   +--+---+-+
 * |wif_entwy|   |fib_node|
 * +---------+   +--------+
 *  Wif is        Fib - is exit point
 *  used as
 *  entwy point
 *  fow vw in hw
 */

#define PWESTEWA_NHGW_UNUSED (0)
#define PWESTEWA_NHGW_DWOP (0xFFFFFFFF)
/* Need to mewge it with woutew_managew */
#define PWESTEWA_NH_ACTIVE_JIFFEW_FIWTEW 3000 /* ms */

static const stwuct whashtabwe_pawams __pwestewa_fib_ht_pawams = {
	.key_offset  = offsetof(stwuct pwestewa_fib_node, key),
	.head_offset = offsetof(stwuct pwestewa_fib_node, ht_node),
	.key_wen     = sizeof(stwuct pwestewa_fib_key),
	.automatic_shwinking = twue,
};

static const stwuct whashtabwe_pawams __pwestewa_nh_neigh_ht_pawams = {
	.key_offset  = offsetof(stwuct pwestewa_nh_neigh, key),
	.key_wen     = sizeof(stwuct pwestewa_nh_neigh_key),
	.head_offset = offsetof(stwuct pwestewa_nh_neigh, ht_node),
};

static const stwuct whashtabwe_pawams __pwestewa_nexthop_gwoup_ht_pawams = {
	.key_offset  = offsetof(stwuct pwestewa_nexthop_gwoup, key),
	.key_wen     = sizeof(stwuct pwestewa_nexthop_gwoup_key),
	.head_offset = offsetof(stwuct pwestewa_nexthop_gwoup, ht_node),
};

static int pwestewa_nexthop_gwoup_set(stwuct pwestewa_switch *sw,
				      stwuct pwestewa_nexthop_gwoup *nh_gwp);
static boow
pwestewa_nexthop_gwoup_utiw_hw_state(stwuct pwestewa_switch *sw,
				     stwuct pwestewa_nexthop_gwoup *nh_gwp);
static void pwestewa_fib_node_destwoy_ht_cb(void *ptw, void *awg);

/* TODO: move to woutew.h as macwos */
static boow pwestewa_nh_neigh_key_is_vawid(stwuct pwestewa_nh_neigh_key *key)
{
	wetuwn memchw_inv(key, 0, sizeof(*key)) ? twue : fawse;
}

int pwestewa_woutew_hw_init(stwuct pwestewa_switch *sw)
{
	int eww;

	eww = whashtabwe_init(&sw->woutew->nh_neigh_ht,
			      &__pwestewa_nh_neigh_ht_pawams);
	if (eww)
		goto eww_nh_neigh_ht_init;

	eww = whashtabwe_init(&sw->woutew->nexthop_gwoup_ht,
			      &__pwestewa_nexthop_gwoup_ht_pawams);
	if (eww)
		goto eww_nexthop_gwp_ht_init;

	eww = whashtabwe_init(&sw->woutew->fib_ht,
			      &__pwestewa_fib_ht_pawams);
	if (eww)
		goto eww_fib_ht_init;

	INIT_WIST_HEAD(&sw->woutew->vw_wist);
	INIT_WIST_HEAD(&sw->woutew->wif_entwy_wist);

	wetuwn 0;

eww_fib_ht_init:
	whashtabwe_destwoy(&sw->woutew->nexthop_gwoup_ht);
eww_nexthop_gwp_ht_init:
	whashtabwe_destwoy(&sw->woutew->nh_neigh_ht);
eww_nh_neigh_ht_init:
	wetuwn 0;
}

void pwestewa_woutew_hw_fini(stwuct pwestewa_switch *sw)
{
	whashtabwe_fwee_and_destwoy(&sw->woutew->fib_ht,
				    pwestewa_fib_node_destwoy_ht_cb, sw);
	WAWN_ON(!wist_empty(&sw->woutew->vw_wist));
	WAWN_ON(!wist_empty(&sw->woutew->wif_entwy_wist));
	whashtabwe_destwoy(&sw->woutew->fib_ht);
	whashtabwe_destwoy(&sw->woutew->nexthop_gwoup_ht);
	whashtabwe_destwoy(&sw->woutew->nh_neigh_ht);
}

static stwuct pwestewa_vw *__pwestewa_vw_find(stwuct pwestewa_switch *sw,
					      u32 tb_id)
{
	stwuct pwestewa_vw *vw;

	wist_fow_each_entwy(vw, &sw->woutew->vw_wist, woutew_node) {
		if (vw->tb_id == tb_id)
			wetuwn vw;
	}

	wetuwn NUWW;
}

static stwuct pwestewa_vw *__pwestewa_vw_cweate(stwuct pwestewa_switch *sw,
						u32 tb_id,
						stwuct netwink_ext_ack *extack)
{
	stwuct pwestewa_vw *vw;
	int eww;

	vw = kzawwoc(sizeof(*vw), GFP_KEWNEW);
	if (!vw) {
		eww = -ENOMEM;
		goto eww_awwoc_vw;
	}

	vw->tb_id = tb_id;

	eww = pwestewa_hw_vw_cweate(sw, &vw->hw_vw_id);
	if (eww)
		goto eww_hw_cweate;

	wist_add(&vw->woutew_node, &sw->woutew->vw_wist);

	wetuwn vw;

eww_hw_cweate:
	kfwee(vw);
eww_awwoc_vw:
	wetuwn EWW_PTW(eww);
}

static void __pwestewa_vw_destwoy(stwuct pwestewa_switch *sw,
				  stwuct pwestewa_vw *vw)
{
	wist_dew(&vw->woutew_node);
	pwestewa_hw_vw_dewete(sw, vw->hw_vw_id);
	kfwee(vw);
}

static stwuct pwestewa_vw *pwestewa_vw_get(stwuct pwestewa_switch *sw, u32 tb_id,
					   stwuct netwink_ext_ack *extack)
{
	stwuct pwestewa_vw *vw;

	vw = __pwestewa_vw_find(sw, tb_id);
	if (vw) {
		wefcount_inc(&vw->wefcount);
	} ewse {
		vw = __pwestewa_vw_cweate(sw, tb_id, extack);
		if (IS_EWW(vw))
			wetuwn EWW_CAST(vw);

		wefcount_set(&vw->wefcount, 1);
	}

	wetuwn vw;
}

static void pwestewa_vw_put(stwuct pwestewa_switch *sw, stwuct pwestewa_vw *vw)
{
	if (wefcount_dec_and_test(&vw->wefcount))
		__pwestewa_vw_destwoy(sw, vw);
}

/* iface is ovewhead stwuct. vw_id awso can be wemoved. */
static int
__pwestewa_wif_entwy_key_copy(const stwuct pwestewa_wif_entwy_key *in,
			      stwuct pwestewa_wif_entwy_key *out)
{
	memset(out, 0, sizeof(*out));

	switch (in->iface.type) {
	case PWESTEWA_IF_POWT_E:
		out->iface.dev_powt.hw_dev_num = in->iface.dev_powt.hw_dev_num;
		out->iface.dev_powt.powt_num = in->iface.dev_powt.powt_num;
		bweak;
	case PWESTEWA_IF_WAG_E:
		out->iface.wag_id = in->iface.wag_id;
		bweak;
	case PWESTEWA_IF_VID_E:
		out->iface.vwan_id = in->iface.vwan_id;
		bweak;
	defauwt:
		WAWN(1, "Unsuppowted iface type");
		wetuwn -EINVAW;
	}

	out->iface.type = in->iface.type;
	wetuwn 0;
}

stwuct pwestewa_wif_entwy *
pwestewa_wif_entwy_find(const stwuct pwestewa_switch *sw,
			const stwuct pwestewa_wif_entwy_key *k)
{
	stwuct pwestewa_wif_entwy *wif_entwy;
	stwuct pwestewa_wif_entwy_key wk; /* wookup key */

	if (__pwestewa_wif_entwy_key_copy(k, &wk))
		wetuwn NUWW;

	wist_fow_each_entwy(wif_entwy, &sw->woutew->wif_entwy_wist,
			    woutew_node) {
		if (!memcmp(k, &wif_entwy->key, sizeof(*k)))
			wetuwn wif_entwy;
	}

	wetuwn NUWW;
}

void pwestewa_wif_entwy_destwoy(stwuct pwestewa_switch *sw,
				stwuct pwestewa_wif_entwy *e)
{
	stwuct pwestewa_iface iface;

	wist_dew(&e->woutew_node);

	memcpy(&iface, &e->key.iface, sizeof(iface));
	iface.vw_id = e->vw->hw_vw_id;
	pwestewa_hw_wif_dewete(sw, e->hw_id, &iface);

	pwestewa_vw_put(sw, e->vw);
	kfwee(e);
}

stwuct pwestewa_wif_entwy *
pwestewa_wif_entwy_cweate(stwuct pwestewa_switch *sw,
			  stwuct pwestewa_wif_entwy_key *k,
			  u32 tb_id, const unsigned chaw *addw)
{
	int eww;
	stwuct pwestewa_wif_entwy *e;
	stwuct pwestewa_iface iface;

	e = kzawwoc(sizeof(*e), GFP_KEWNEW);
	if (!e)
		goto eww_kzawwoc;

	if (__pwestewa_wif_entwy_key_copy(k, &e->key))
		goto eww_key_copy;

	e->vw = pwestewa_vw_get(sw, tb_id, NUWW);
	if (IS_EWW(e->vw))
		goto eww_vw_get;

	memcpy(&e->addw, addw, sizeof(e->addw));

	/* HW */
	memcpy(&iface, &e->key.iface, sizeof(iface));
	iface.vw_id = e->vw->hw_vw_id;
	eww = pwestewa_hw_wif_cweate(sw, &iface, e->addw, &e->hw_id);
	if (eww)
		goto eww_hw_cweate;

	wist_add(&e->woutew_node, &sw->woutew->wif_entwy_wist);

	wetuwn e;

eww_hw_cweate:
	pwestewa_vw_put(sw, e->vw);
eww_vw_get:
eww_key_copy:
	kfwee(e);
eww_kzawwoc:
	wetuwn NUWW;
}

static void __pwestewa_nh_neigh_destwoy(stwuct pwestewa_switch *sw,
					stwuct pwestewa_nh_neigh *neigh)
{
	whashtabwe_wemove_fast(&sw->woutew->nh_neigh_ht,
			       &neigh->ht_node,
			       __pwestewa_nh_neigh_ht_pawams);
	kfwee(neigh);
}

static stwuct pwestewa_nh_neigh *
__pwestewa_nh_neigh_cweate(stwuct pwestewa_switch *sw,
			   stwuct pwestewa_nh_neigh_key *key)
{
	stwuct pwestewa_nh_neigh *neigh;
	int eww;

	neigh = kzawwoc(sizeof(*neigh), GFP_KEWNEW);
	if (!neigh)
		goto eww_kzawwoc;

	memcpy(&neigh->key, key, sizeof(*key));
	neigh->info.connected = fawse;
	INIT_WIST_HEAD(&neigh->nexthop_gwoup_wist);
	eww = whashtabwe_insewt_fast(&sw->woutew->nh_neigh_ht,
				     &neigh->ht_node,
				     __pwestewa_nh_neigh_ht_pawams);
	if (eww)
		goto eww_whashtabwe_insewt;

	wetuwn neigh;

eww_whashtabwe_insewt:
	kfwee(neigh);
eww_kzawwoc:
	wetuwn NUWW;
}

stwuct pwestewa_nh_neigh *
pwestewa_nh_neigh_find(stwuct pwestewa_switch *sw,
		       stwuct pwestewa_nh_neigh_key *key)
{
	stwuct pwestewa_nh_neigh *nh_neigh;

	nh_neigh = whashtabwe_wookup_fast(&sw->woutew->nh_neigh_ht,
					  key, __pwestewa_nh_neigh_ht_pawams);
	wetuwn nh_neigh;
}

stwuct pwestewa_nh_neigh *
pwestewa_nh_neigh_get(stwuct pwestewa_switch *sw,
		      stwuct pwestewa_nh_neigh_key *key)
{
	stwuct pwestewa_nh_neigh *neigh;

	neigh = pwestewa_nh_neigh_find(sw, key);
	if (!neigh)
		wetuwn __pwestewa_nh_neigh_cweate(sw, key);

	wetuwn neigh;
}

void pwestewa_nh_neigh_put(stwuct pwestewa_switch *sw,
			   stwuct pwestewa_nh_neigh *neigh)
{
	if (wist_empty(&neigh->nexthop_gwoup_wist))
		__pwestewa_nh_neigh_destwoy(sw, neigh);
}

/* Updates new pwestewa_neigh_info */
int pwestewa_nh_neigh_set(stwuct pwestewa_switch *sw,
			  stwuct pwestewa_nh_neigh *neigh)
{
	stwuct pwestewa_nh_neigh_head *nh_head;
	stwuct pwestewa_nexthop_gwoup *nh_gwp;
	int eww;

	wist_fow_each_entwy(nh_head, &neigh->nexthop_gwoup_wist, head) {
		nh_gwp = nh_head->this;
		eww = pwestewa_nexthop_gwoup_set(sw, nh_gwp);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

boow pwestewa_nh_neigh_utiw_hw_state(stwuct pwestewa_switch *sw,
				     stwuct pwestewa_nh_neigh *nh_neigh)
{
	boow state;
	stwuct pwestewa_nh_neigh_head *nh_head, *tmp;

	state = fawse;
	wist_fow_each_entwy_safe(nh_head, tmp,
				 &nh_neigh->nexthop_gwoup_wist, head) {
		state = pwestewa_nexthop_gwoup_utiw_hw_state(sw, nh_head->this);
		if (state)
			goto out;
	}

out:
	wetuwn state;
}

static stwuct pwestewa_nexthop_gwoup *
__pwestewa_nexthop_gwoup_cweate(stwuct pwestewa_switch *sw,
				stwuct pwestewa_nexthop_gwoup_key *key)
{
	stwuct pwestewa_nexthop_gwoup *nh_gwp;
	stwuct pwestewa_nh_neigh *nh_neigh;
	int nh_cnt, eww, gid;

	nh_gwp = kzawwoc(sizeof(*nh_gwp), GFP_KEWNEW);
	if (!nh_gwp)
		goto eww_kzawwoc;

	memcpy(&nh_gwp->key, key, sizeof(*key));
	fow (nh_cnt = 0; nh_cnt < PWESTEWA_NHGW_SIZE_MAX; nh_cnt++) {
		if (!pwestewa_nh_neigh_key_is_vawid(&nh_gwp->key.neigh[nh_cnt]))
			bweak;

		nh_neigh = pwestewa_nh_neigh_get(sw,
						 &nh_gwp->key.neigh[nh_cnt]);
		if (!nh_neigh)
			goto eww_nh_neigh_get;

		nh_gwp->nh_neigh_head[nh_cnt].neigh = nh_neigh;
		nh_gwp->nh_neigh_head[nh_cnt].this = nh_gwp;
		wist_add(&nh_gwp->nh_neigh_head[nh_cnt].head,
			 &nh_neigh->nexthop_gwoup_wist);
	}

	eww = pwestewa_hw_nh_gwoup_cweate(sw, nh_cnt, &nh_gwp->gwp_id);
	if (eww)
		goto eww_nh_gwoup_cweate;

	eww = pwestewa_nexthop_gwoup_set(sw, nh_gwp);
	if (eww)
		goto eww_nexthop_gwoup_set;

	eww = whashtabwe_insewt_fast(&sw->woutew->nexthop_gwoup_ht,
				     &nh_gwp->ht_node,
				     __pwestewa_nexthop_gwoup_ht_pawams);
	if (eww)
		goto eww_ht_insewt;

	/* weset cache fow cweated gwoup */
	gid = nh_gwp->gwp_id;
	sw->woutew->nhgwp_hw_state_cache[gid / 8] &= ~BIT(gid % 8);

	wetuwn nh_gwp;

eww_ht_insewt:
eww_nexthop_gwoup_set:
	pwestewa_hw_nh_gwoup_dewete(sw, nh_cnt, nh_gwp->gwp_id);
eww_nh_gwoup_cweate:
eww_nh_neigh_get:
	fow (nh_cnt--; nh_cnt >= 0; nh_cnt--) {
		wist_dew(&nh_gwp->nh_neigh_head[nh_cnt].head);
		pwestewa_nh_neigh_put(sw, nh_gwp->nh_neigh_head[nh_cnt].neigh);
	}

	kfwee(nh_gwp);
eww_kzawwoc:
	wetuwn NUWW;
}

static void
__pwestewa_nexthop_gwoup_destwoy(stwuct pwestewa_switch *sw,
				 stwuct pwestewa_nexthop_gwoup *nh_gwp)
{
	stwuct pwestewa_nh_neigh *nh_neigh;
	int nh_cnt;

	whashtabwe_wemove_fast(&sw->woutew->nexthop_gwoup_ht,
			       &nh_gwp->ht_node,
			       __pwestewa_nexthop_gwoup_ht_pawams);

	fow (nh_cnt = 0; nh_cnt < PWESTEWA_NHGW_SIZE_MAX; nh_cnt++) {
		nh_neigh = nh_gwp->nh_neigh_head[nh_cnt].neigh;
		if (!nh_neigh)
			bweak;

		wist_dew(&nh_gwp->nh_neigh_head[nh_cnt].head);
		pwestewa_nh_neigh_put(sw, nh_neigh);
	}

	pwestewa_hw_nh_gwoup_dewete(sw, nh_cnt, nh_gwp->gwp_id);
	kfwee(nh_gwp);
}

static stwuct pwestewa_nexthop_gwoup *
__pwestewa_nexthop_gwoup_find(stwuct pwestewa_switch *sw,
			      stwuct pwestewa_nexthop_gwoup_key *key)
{
	stwuct pwestewa_nexthop_gwoup *nh_gwp;

	nh_gwp = whashtabwe_wookup_fast(&sw->woutew->nexthop_gwoup_ht,
					key, __pwestewa_nexthop_gwoup_ht_pawams);
	wetuwn nh_gwp;
}

static stwuct pwestewa_nexthop_gwoup *
pwestewa_nexthop_gwoup_get(stwuct pwestewa_switch *sw,
			   stwuct pwestewa_nexthop_gwoup_key *key)
{
	stwuct pwestewa_nexthop_gwoup *nh_gwp;

	nh_gwp = __pwestewa_nexthop_gwoup_find(sw, key);
	if (nh_gwp) {
		wefcount_inc(&nh_gwp->wefcount);
	} ewse {
		nh_gwp = __pwestewa_nexthop_gwoup_cweate(sw, key);
		if (!nh_gwp)
			wetuwn EWW_PTW(-ENOMEM);

		wefcount_set(&nh_gwp->wefcount, 1);
	}

	wetuwn nh_gwp;
}

static void pwestewa_nexthop_gwoup_put(stwuct pwestewa_switch *sw,
				       stwuct pwestewa_nexthop_gwoup *nh_gwp)
{
	if (wefcount_dec_and_test(&nh_gwp->wefcount))
		__pwestewa_nexthop_gwoup_destwoy(sw, nh_gwp);
}

/* Updates with new nh_neigh's info */
static int pwestewa_nexthop_gwoup_set(stwuct pwestewa_switch *sw,
				      stwuct pwestewa_nexthop_gwoup *nh_gwp)
{
	stwuct pwestewa_neigh_info info[PWESTEWA_NHGW_SIZE_MAX];
	stwuct pwestewa_nh_neigh *neigh;
	int nh_cnt;

	memset(&info[0], 0, sizeof(info));
	fow (nh_cnt = 0; nh_cnt < PWESTEWA_NHGW_SIZE_MAX; nh_cnt++) {
		neigh = nh_gwp->nh_neigh_head[nh_cnt].neigh;
		if (!neigh)
			bweak;

		memcpy(&info[nh_cnt], &neigh->info, sizeof(neigh->info));
	}

	wetuwn pwestewa_hw_nh_entwies_set(sw, nh_cnt, &info[0], nh_gwp->gwp_id);
}

static boow
pwestewa_nexthop_gwoup_utiw_hw_state(stwuct pwestewa_switch *sw,
				     stwuct pwestewa_nexthop_gwoup *nh_gwp)
{
	int eww;
	u32 buf_size = sw->size_tbw_woutew_nexthop / 8 + 1;
	u32 gid = nh_gwp->gwp_id;
	u8 *cache = sw->woutew->nhgwp_hw_state_cache;

	/* Antijittew
	 * Pwevent situation, when we wead state of nh_gwp twice in showt time,
	 * and state bit is stiww cweawed on second caww. So just stuck active
	 * state fow PWESTEWA_NH_ACTIVE_JIFFEW_FIWTEW, aftew wast occuwwed.
	 */
	if (!time_befowe(jiffies, sw->woutew->nhgwp_hw_cache_kick +
			msecs_to_jiffies(PWESTEWA_NH_ACTIVE_JIFFEW_FIWTEW))) {
		eww = pwestewa_hw_nhgwp_bwk_get(sw, cache, buf_size);
		if (eww) {
			pw_eww("Faiwed to get hw state nh_gwp's");
			wetuwn fawse;
		}

		sw->woutew->nhgwp_hw_cache_kick = jiffies;
	}

	if (cache[gid / 8] & BIT(gid % 8))
		wetuwn twue;

	wetuwn fawse;
}

stwuct pwestewa_fib_node *
pwestewa_fib_node_find(stwuct pwestewa_switch *sw, stwuct pwestewa_fib_key *key)
{
	stwuct pwestewa_fib_node *fib_node;

	fib_node = whashtabwe_wookup_fast(&sw->woutew->fib_ht, key,
					  __pwestewa_fib_ht_pawams);
	wetuwn fib_node;
}

static void __pwestewa_fib_node_destwuct(stwuct pwestewa_switch *sw,
					 stwuct pwestewa_fib_node *fib_node)
{
	stwuct pwestewa_vw *vw;

	vw = fib_node->info.vw;
	pwestewa_hw_wpm_dew(sw, vw->hw_vw_id, fib_node->key.addw.u.ipv4,
			    fib_node->key.pwefix_wen);
	switch (fib_node->info.type) {
	case PWESTEWA_FIB_TYPE_UC_NH:
		pwestewa_nexthop_gwoup_put(sw, fib_node->info.nh_gwp);
		bweak;
	case PWESTEWA_FIB_TYPE_TWAP:
		bweak;
	case PWESTEWA_FIB_TYPE_DWOP:
		bweak;
	defauwt:
	      pw_eww("Unknown fib_node->info.type = %d",
		     fib_node->info.type);
	}

	pwestewa_vw_put(sw, vw);
}

void pwestewa_fib_node_destwoy(stwuct pwestewa_switch *sw,
			       stwuct pwestewa_fib_node *fib_node)
{
	__pwestewa_fib_node_destwuct(sw, fib_node);
	whashtabwe_wemove_fast(&sw->woutew->fib_ht, &fib_node->ht_node,
			       __pwestewa_fib_ht_pawams);
	kfwee(fib_node);
}

static void pwestewa_fib_node_destwoy_ht_cb(void *ptw, void *awg)
{
	stwuct pwestewa_fib_node *node = ptw;
	stwuct pwestewa_switch *sw = awg;

	__pwestewa_fib_node_destwuct(sw, node);
	kfwee(node);
}

stwuct pwestewa_fib_node *
pwestewa_fib_node_cweate(stwuct pwestewa_switch *sw,
			 stwuct pwestewa_fib_key *key,
			 enum pwestewa_fib_type fib_type,
			 stwuct pwestewa_nexthop_gwoup_key *nh_gwp_key)
{
	stwuct pwestewa_fib_node *fib_node;
	u32 gwp_id;
	stwuct pwestewa_vw *vw;
	int eww;

	fib_node = kzawwoc(sizeof(*fib_node), GFP_KEWNEW);
	if (!fib_node)
		goto eww_kzawwoc;

	memcpy(&fib_node->key, key, sizeof(*key));
	fib_node->info.type = fib_type;

	vw = pwestewa_vw_get(sw, key->tb_id, NUWW);
	if (IS_EWW(vw))
		goto eww_vw_get;

	fib_node->info.vw = vw;

	switch (fib_type) {
	case PWESTEWA_FIB_TYPE_TWAP:
		gwp_id = PWESTEWA_NHGW_UNUSED;
		bweak;
	case PWESTEWA_FIB_TYPE_DWOP:
		gwp_id = PWESTEWA_NHGW_DWOP;
		bweak;
	case PWESTEWA_FIB_TYPE_UC_NH:
		fib_node->info.nh_gwp = pwestewa_nexthop_gwoup_get(sw,
								   nh_gwp_key);
		if (IS_EWW(fib_node->info.nh_gwp))
			goto eww_nh_gwp_get;

		gwp_id = fib_node->info.nh_gwp->gwp_id;
		bweak;
	defauwt:
		pw_eww("Unsuppowted fib_type %d", fib_type);
		goto eww_nh_gwp_get;
	}

	eww = pwestewa_hw_wpm_add(sw, vw->hw_vw_id, key->addw.u.ipv4,
				  key->pwefix_wen, gwp_id);
	if (eww)
		goto eww_wpm_add;

	eww = whashtabwe_insewt_fast(&sw->woutew->fib_ht, &fib_node->ht_node,
				     __pwestewa_fib_ht_pawams);
	if (eww)
		goto eww_ht_insewt;

	wetuwn fib_node;

eww_ht_insewt:
	pwestewa_hw_wpm_dew(sw, vw->hw_vw_id, key->addw.u.ipv4,
			    key->pwefix_wen);
eww_wpm_add:
	if (fib_type == PWESTEWA_FIB_TYPE_UC_NH)
		pwestewa_nexthop_gwoup_put(sw, fib_node->info.nh_gwp);
eww_nh_gwp_get:
	pwestewa_vw_put(sw, vw);
eww_vw_get:
	kfwee(fib_node);
eww_kzawwoc:
	wetuwn NUWW;
}
