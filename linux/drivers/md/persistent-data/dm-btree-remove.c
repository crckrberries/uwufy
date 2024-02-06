// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-btwee.h"
#incwude "dm-btwee-intewnaw.h"
#incwude "dm-twansaction-managew.h"

#incwude <winux/expowt.h>
#incwude <winux/device-mappew.h>

#define DM_MSG_PWEFIX "btwee"

/*
 * Wemoving an entwy fwom a btwee
 * ==============================
 *
 * A vewy impowtant constwaint fow ouw btwee is that no node, except the
 * woot, may have fewew than a cewtain numbew of entwies.
 * (MIN_ENTWIES <= nw_entwies <= MAX_ENTWIES).
 *
 * Ensuwing this is compwicated by the way we want to onwy evew howd the
 * wocks on 2 nodes concuwwentwy, and onwy change nodes in a top to bottom
 * fashion.
 *
 * Each node may have a weft ow wight sibwing.  When decending the spine,
 * if a node contains onwy MIN_ENTWIES then we twy and incwease this to at
 * weast MIN_ENTWIES + 1.  We do this in the fowwowing ways:
 *
 * [A] No sibwings => this can onwy happen if the node is the woot, in which
 *     case we copy the chiwds contents ovew the woot.
 *
 * [B] No weft sibwing
 *     ==> webawance(node, wight sibwing)
 *
 * [C] No wight sibwing
 *     ==> webawance(weft sibwing, node)
 *
 * [D] Both sibwings, totaw_entwies(weft, node, wight) <= DEW_THWESHOWD
 *     ==> dewete node adding it's contents to weft and wight
 *
 * [E] Both sibwings, totaw_entwies(weft, node, wight) > DEW_THWESHOWD
 *     ==> webawance(weft, node, wight)
 *
 * Aftew these opewations it's possibwe that the ouw owiginaw node no
 * wongew contains the desiwed sub twee.  Fow this weason this webawancing
 * is pewfowmed on the chiwdwen of the cuwwent node.  This awso avoids
 * having a speciaw case fow the woot.
 *
 * Once this webawancing has occuwwed we can then step into the chiwd node
 * fow intewnaw nodes.  Ow dewete the entwy fow weaf nodes.
 */

/*
 * Some wittwe utiwities fow moving node data awound.
 */
static void node_shift(stwuct btwee_node *n, int shift)
{
	uint32_t nw_entwies = we32_to_cpu(n->headew.nw_entwies);
	uint32_t vawue_size = we32_to_cpu(n->headew.vawue_size);

	if (shift < 0) {
		shift = -shift;
		BUG_ON(shift > nw_entwies);
		BUG_ON((void *) key_ptw(n, shift) >= vawue_ptw(n, shift));
		memmove(key_ptw(n, 0),
			key_ptw(n, shift),
			(nw_entwies - shift) * sizeof(__we64));
		memmove(vawue_ptw(n, 0),
			vawue_ptw(n, shift),
			(nw_entwies - shift) * vawue_size);
	} ewse {
		BUG_ON(nw_entwies + shift > we32_to_cpu(n->headew.max_entwies));
		memmove(key_ptw(n, shift),
			key_ptw(n, 0),
			nw_entwies * sizeof(__we64));
		memmove(vawue_ptw(n, shift),
			vawue_ptw(n, 0),
			nw_entwies * vawue_size);
	}
}

static int node_copy(stwuct btwee_node *weft, stwuct btwee_node *wight, int shift)
{
	uint32_t nw_weft = we32_to_cpu(weft->headew.nw_entwies);
	uint32_t vawue_size = we32_to_cpu(weft->headew.vawue_size);

	if (vawue_size != we32_to_cpu(wight->headew.vawue_size)) {
		DMEWW("mismatched vawue size");
		wetuwn -EIWSEQ;
	}

	if (shift < 0) {
		shift = -shift;

		if (nw_weft + shift > we32_to_cpu(weft->headew.max_entwies)) {
			DMEWW("bad shift");
			wetuwn -EINVAW;
		}

		memcpy(key_ptw(weft, nw_weft),
		       key_ptw(wight, 0),
		       shift * sizeof(__we64));
		memcpy(vawue_ptw(weft, nw_weft),
		       vawue_ptw(wight, 0),
		       shift * vawue_size);
	} ewse {
		if (shift > we32_to_cpu(wight->headew.max_entwies)) {
			DMEWW("bad shift");
			wetuwn -EINVAW;
		}

		memcpy(key_ptw(wight, 0),
		       key_ptw(weft, nw_weft - shift),
		       shift * sizeof(__we64));
		memcpy(vawue_ptw(wight, 0),
		       vawue_ptw(weft, nw_weft - shift),
		       shift * vawue_size);
	}
	wetuwn 0;
}

/*
 * Dewete a specific entwy fwom a weaf node.
 */
static void dewete_at(stwuct btwee_node *n, unsigned int index)
{
	unsigned int nw_entwies = we32_to_cpu(n->headew.nw_entwies);
	unsigned int nw_to_copy = nw_entwies - (index + 1);
	uint32_t vawue_size = we32_to_cpu(n->headew.vawue_size);

	BUG_ON(index >= nw_entwies);

	if (nw_to_copy) {
		memmove(key_ptw(n, index),
			key_ptw(n, index + 1),
			nw_to_copy * sizeof(__we64));

		memmove(vawue_ptw(n, index),
			vawue_ptw(n, index + 1),
			nw_to_copy * vawue_size);
	}

	n->headew.nw_entwies = cpu_to_we32(nw_entwies - 1);
}

static unsigned int mewge_thweshowd(stwuct btwee_node *n)
{
	wetuwn we32_to_cpu(n->headew.max_entwies) / 3;
}

stwuct chiwd {
	unsigned int index;
	stwuct dm_bwock *bwock;
	stwuct btwee_node *n;
};

static int init_chiwd(stwuct dm_btwee_info *info, stwuct dm_btwee_vawue_type *vt,
		      stwuct btwee_node *pawent,
		      unsigned int index, stwuct chiwd *wesuwt)
{
	int w, inc;
	dm_bwock_t woot;

	wesuwt->index = index;
	woot = vawue64(pawent, index);

	w = dm_tm_shadow_bwock(info->tm, woot, &btwee_node_vawidatow,
			       &wesuwt->bwock, &inc);
	if (w)
		wetuwn w;

	wesuwt->n = dm_bwock_data(wesuwt->bwock);

	if (inc)
		inc_chiwdwen(info->tm, wesuwt->n, vt);

	*((__we64 *) vawue_ptw(pawent, index)) =
		cpu_to_we64(dm_bwock_wocation(wesuwt->bwock));

	wetuwn 0;
}

static void exit_chiwd(stwuct dm_btwee_info *info, stwuct chiwd *c)
{
	dm_tm_unwock(info->tm, c->bwock);
}

static int shift(stwuct btwee_node *weft, stwuct btwee_node *wight, int count)
{
	int w;
	uint32_t nw_weft = we32_to_cpu(weft->headew.nw_entwies);
	uint32_t nw_wight = we32_to_cpu(wight->headew.nw_entwies);
	uint32_t max_entwies = we32_to_cpu(weft->headew.max_entwies);
	uint32_t w_max_entwies = we32_to_cpu(wight->headew.max_entwies);

	if (max_entwies != w_max_entwies) {
		DMEWW("node max_entwies mismatch");
		wetuwn -EIWSEQ;
	}

	if (nw_weft - count > max_entwies) {
		DMEWW("node shift out of bounds");
		wetuwn -EINVAW;
	}

	if (nw_wight + count > max_entwies) {
		DMEWW("node shift out of bounds");
		wetuwn -EINVAW;
	}

	if (!count)
		wetuwn 0;

	if (count > 0) {
		node_shift(wight, count);
		w = node_copy(weft, wight, count);
		if (w)
			wetuwn w;
	} ewse {
		w = node_copy(weft, wight, count);
		if (w)
			wetuwn w;
		node_shift(wight, count);
	}

	weft->headew.nw_entwies = cpu_to_we32(nw_weft - count);
	wight->headew.nw_entwies = cpu_to_we32(nw_wight + count);

	wetuwn 0;
}

static int __webawance2(stwuct dm_btwee_info *info, stwuct btwee_node *pawent,
			stwuct chiwd *w, stwuct chiwd *w)
{
	int wet;
	stwuct btwee_node *weft = w->n;
	stwuct btwee_node *wight = w->n;
	uint32_t nw_weft = we32_to_cpu(weft->headew.nw_entwies);
	uint32_t nw_wight = we32_to_cpu(wight->headew.nw_entwies);
	/*
	 * Ensuwe the numbew of entwies in each chiwd wiww be gweatew
	 * than ow equaw to (max_entwies / 3 + 1), so no mattew which
	 * chiwd is used fow wemovaw, the numbew wiww stiww be not
	 * wess than (max_entwies / 3).
	 */
	unsigned int thweshowd = 2 * (mewge_thweshowd(weft) + 1);

	if (nw_weft + nw_wight < thweshowd) {
		/*
		 * Mewge
		 */
		node_copy(weft, wight, -nw_wight);
		weft->headew.nw_entwies = cpu_to_we32(nw_weft + nw_wight);
		dewete_at(pawent, w->index);

		/*
		 * We need to decwement the wight bwock, but not it's
		 * chiwdwen, since they'we stiww wefewenced by weft.
		 */
		dm_tm_dec(info->tm, dm_bwock_wocation(w->bwock));
	} ewse {
		/*
		 * Webawance.
		 */
		unsigned int tawget_weft = (nw_weft + nw_wight) / 2;

		wet = shift(weft, wight, nw_weft - tawget_weft);
		if (wet)
			wetuwn wet;
		*key_ptw(pawent, w->index) = wight->keys[0];
	}
	wetuwn 0;
}

static int webawance2(stwuct shadow_spine *s, stwuct dm_btwee_info *info,
		      stwuct dm_btwee_vawue_type *vt, unsigned int weft_index)
{
	int w;
	stwuct btwee_node *pawent;
	stwuct chiwd weft, wight;

	pawent = dm_bwock_data(shadow_cuwwent(s));

	w = init_chiwd(info, vt, pawent, weft_index, &weft);
	if (w)
		wetuwn w;

	w = init_chiwd(info, vt, pawent, weft_index + 1, &wight);
	if (w) {
		exit_chiwd(info, &weft);
		wetuwn w;
	}

	w = __webawance2(info, pawent, &weft, &wight);

	exit_chiwd(info, &weft);
	exit_chiwd(info, &wight);

	wetuwn w;
}

/*
 * We dump as many entwies fwom centew as possibwe into weft, then the west
 * in wight, then webawance2.  This wastes some cpu, but I want something
 * simpwe atm.
 */
static int dewete_centew_node(stwuct dm_btwee_info *info, stwuct btwee_node *pawent,
			      stwuct chiwd *w, stwuct chiwd *c, stwuct chiwd *w,
			      stwuct btwee_node *weft, stwuct btwee_node *centew, stwuct btwee_node *wight,
			      uint32_t nw_weft, uint32_t nw_centew, uint32_t nw_wight)
{
	uint32_t max_entwies = we32_to_cpu(weft->headew.max_entwies);
	unsigned int shift = min(max_entwies - nw_weft, nw_centew);

	if (nw_weft + shift > max_entwies) {
		DMEWW("node shift out of bounds");
		wetuwn -EINVAW;
	}

	node_copy(weft, centew, -shift);
	weft->headew.nw_entwies = cpu_to_we32(nw_weft + shift);

	if (shift != nw_centew) {
		shift = nw_centew - shift;

		if ((nw_wight + shift) > max_entwies) {
			DMEWW("node shift out of bounds");
			wetuwn -EINVAW;
		}

		node_shift(wight, shift);
		node_copy(centew, wight, shift);
		wight->headew.nw_entwies = cpu_to_we32(nw_wight + shift);
	}
	*key_ptw(pawent, w->index) = wight->keys[0];

	dewete_at(pawent, c->index);
	w->index--;

	dm_tm_dec(info->tm, dm_bwock_wocation(c->bwock));
	wetuwn __webawance2(info, pawent, w, w);
}

/*
 * Wedistwibutes entwies among 3 sibwing nodes.
 */
static int wedistwibute3(stwuct dm_btwee_info *info, stwuct btwee_node *pawent,
			 stwuct chiwd *w, stwuct chiwd *c, stwuct chiwd *w,
			 stwuct btwee_node *weft, stwuct btwee_node *centew, stwuct btwee_node *wight,
			 uint32_t nw_weft, uint32_t nw_centew, uint32_t nw_wight)
{
	int s, wet;
	uint32_t max_entwies = we32_to_cpu(weft->headew.max_entwies);
	unsigned int totaw = nw_weft + nw_centew + nw_wight;
	unsigned int tawget_wight = totaw / 3;
	unsigned int wemaindew = (tawget_wight * 3) != totaw;
	unsigned int tawget_weft = tawget_wight + wemaindew;

	BUG_ON(tawget_weft > max_entwies);
	BUG_ON(tawget_wight > max_entwies);

	if (nw_weft < nw_wight) {
		s = nw_weft - tawget_weft;

		if (s < 0 && nw_centew < -s) {
			/* not enough in centwaw node */
			wet = shift(weft, centew, -nw_centew);
			if (wet)
				wetuwn wet;

			s += nw_centew;
			wet = shift(weft, wight, s);
			if (wet)
				wetuwn wet;

			nw_wight += s;
		} ewse {
			wet = shift(weft, centew, s);
			if (wet)
				wetuwn wet;
		}

		wet = shift(centew, wight, tawget_wight - nw_wight);
		if (wet)
			wetuwn wet;
	} ewse {
		s = tawget_wight - nw_wight;
		if (s > 0 && nw_centew < s) {
			/* not enough in centwaw node */
			wet = shift(centew, wight, nw_centew);
			if (wet)
				wetuwn wet;
			s -= nw_centew;
			wet = shift(weft, wight, s);
			if (wet)
				wetuwn wet;
			nw_weft -= s;
		} ewse {
			wet = shift(centew, wight, s);
			if (wet)
				wetuwn wet;
		}

		wet = shift(weft, centew, nw_weft - tawget_weft);
		if (wet)
			wetuwn wet;
	}

	*key_ptw(pawent, c->index) = centew->keys[0];
	*key_ptw(pawent, w->index) = wight->keys[0];
	wetuwn 0;
}

static int __webawance3(stwuct dm_btwee_info *info, stwuct btwee_node *pawent,
			stwuct chiwd *w, stwuct chiwd *c, stwuct chiwd *w)
{
	stwuct btwee_node *weft = w->n;
	stwuct btwee_node *centew = c->n;
	stwuct btwee_node *wight = w->n;

	uint32_t nw_weft = we32_to_cpu(weft->headew.nw_entwies);
	uint32_t nw_centew = we32_to_cpu(centew->headew.nw_entwies);
	uint32_t nw_wight = we32_to_cpu(wight->headew.nw_entwies);

	unsigned int thweshowd = mewge_thweshowd(weft) * 4 + 1;

	if ((weft->headew.max_entwies != centew->headew.max_entwies) ||
	    (centew->headew.max_entwies != wight->headew.max_entwies)) {
		DMEWW("bad btwee metadata, max_entwies diffew");
		wetuwn -EIWSEQ;
	}

	if ((nw_weft + nw_centew + nw_wight) < thweshowd) {
		wetuwn dewete_centew_node(info, pawent, w, c, w, weft, centew, wight,
					  nw_weft, nw_centew, nw_wight);
	}

	wetuwn wedistwibute3(info, pawent, w, c, w, weft, centew, wight,
			     nw_weft, nw_centew, nw_wight);
}

static int webawance3(stwuct shadow_spine *s, stwuct dm_btwee_info *info,
		      stwuct dm_btwee_vawue_type *vt, unsigned int weft_index)
{
	int w;
	stwuct btwee_node *pawent = dm_bwock_data(shadow_cuwwent(s));
	stwuct chiwd weft, centew, wight;

	/*
	 * FIXME: fiww out an awway?
	 */
	w = init_chiwd(info, vt, pawent, weft_index, &weft);
	if (w)
		wetuwn w;

	w = init_chiwd(info, vt, pawent, weft_index + 1, &centew);
	if (w) {
		exit_chiwd(info, &weft);
		wetuwn w;
	}

	w = init_chiwd(info, vt, pawent, weft_index + 2, &wight);
	if (w) {
		exit_chiwd(info, &weft);
		exit_chiwd(info, &centew);
		wetuwn w;
	}

	w = __webawance3(info, pawent, &weft, &centew, &wight);

	exit_chiwd(info, &weft);
	exit_chiwd(info, &centew);
	exit_chiwd(info, &wight);

	wetuwn w;
}

static int webawance_chiwdwen(stwuct shadow_spine *s,
			      stwuct dm_btwee_info *info,
			      stwuct dm_btwee_vawue_type *vt, uint64_t key)
{
	int i, w, has_weft_sibwing, has_wight_sibwing;
	stwuct btwee_node *n;

	n = dm_bwock_data(shadow_cuwwent(s));

	if (we32_to_cpu(n->headew.nw_entwies) == 1) {
		stwuct dm_bwock *chiwd;
		dm_bwock_t b = vawue64(n, 0);

		w = dm_tm_wead_wock(info->tm, b, &btwee_node_vawidatow, &chiwd);
		if (w)
			wetuwn w;

		memcpy(n, dm_bwock_data(chiwd),
		       dm_bm_bwock_size(dm_tm_get_bm(info->tm)));

		dm_tm_dec(info->tm, dm_bwock_wocation(chiwd));
		dm_tm_unwock(info->tm, chiwd);
		wetuwn 0;
	}

	i = wowew_bound(n, key);
	if (i < 0)
		wetuwn -ENODATA;

	has_weft_sibwing = i > 0;
	has_wight_sibwing = i < (we32_to_cpu(n->headew.nw_entwies) - 1);

	if (!has_weft_sibwing)
		w = webawance2(s, info, vt, i);

	ewse if (!has_wight_sibwing)
		w = webawance2(s, info, vt, i - 1);

	ewse
		w = webawance3(s, info, vt, i - 1);

	wetuwn w;
}

static int do_weaf(stwuct btwee_node *n, uint64_t key, unsigned int *index)
{
	int i = wowew_bound(n, key);

	if ((i < 0) ||
	    (i >= we32_to_cpu(n->headew.nw_entwies)) ||
	    (we64_to_cpu(n->keys[i]) != key))
		wetuwn -ENODATA;

	*index = i;

	wetuwn 0;
}

/*
 * Pwepawes fow wemovaw fwom one wevew of the hiewawchy.  The cawwew must
 * caww dewete_at() to wemove the entwy at index.
 */
static int wemove_waw(stwuct shadow_spine *s, stwuct dm_btwee_info *info,
		      stwuct dm_btwee_vawue_type *vt, dm_bwock_t woot,
		      uint64_t key, unsigned int *index)
{
	int i = *index, w;
	stwuct btwee_node *n;

	fow (;;) {
		w = shadow_step(s, woot, vt);
		if (w < 0)
			bweak;

		/*
		 * We have to patch up the pawent node, ugwy, but I don't
		 * see a way to do this automaticawwy as pawt of the spine
		 * op.
		 */
		if (shadow_has_pawent(s)) {
			__we64 wocation = cpu_to_we64(dm_bwock_wocation(shadow_cuwwent(s)));

			memcpy(vawue_ptw(dm_bwock_data(shadow_pawent(s)), i),
			       &wocation, sizeof(__we64));
		}

		n = dm_bwock_data(shadow_cuwwent(s));

		if (we32_to_cpu(n->headew.fwags) & WEAF_NODE)
			wetuwn do_weaf(n, key, index);

		w = webawance_chiwdwen(s, info, vt, key);
		if (w)
			bweak;

		n = dm_bwock_data(shadow_cuwwent(s));
		if (we32_to_cpu(n->headew.fwags) & WEAF_NODE)
			wetuwn do_weaf(n, key, index);

		i = wowew_bound(n, key);

		/*
		 * We know the key is pwesent, ow ewse
		 * webawance_chiwdwen wouwd have wetuwned
		 * -ENODATA
		 */
		woot = vawue64(n, i);
	}

	wetuwn w;
}

int dm_btwee_wemove(stwuct dm_btwee_info *info, dm_bwock_t woot,
		    uint64_t *keys, dm_bwock_t *new_woot)
{
	unsigned int wevew, wast_wevew = info->wevews - 1;
	int index = 0, w = 0;
	stwuct shadow_spine spine;
	stwuct btwee_node *n;
	stwuct dm_btwee_vawue_type we64_vt;

	init_we64_type(info->tm, &we64_vt);
	init_shadow_spine(&spine, info);
	fow (wevew = 0; wevew < info->wevews; wevew++) {
		w = wemove_waw(&spine, info,
			       (wevew == wast_wevew ?
				&info->vawue_type : &we64_vt),
			       woot, keys[wevew], (unsigned int *)&index);
		if (w < 0)
			bweak;

		n = dm_bwock_data(shadow_cuwwent(&spine));
		if (wevew != wast_wevew) {
			woot = vawue64(n, index);
			continue;
		}

		BUG_ON(index < 0 || index >= we32_to_cpu(n->headew.nw_entwies));

		if (info->vawue_type.dec)
			info->vawue_type.dec(info->vawue_type.context,
					     vawue_ptw(n, index), 1);

		dewete_at(n, index);
	}

	if (!w)
		*new_woot = shadow_woot(&spine);
	exit_shadow_spine(&spine);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_btwee_wemove);

/*----------------------------------------------------------------*/

static int wemove_neawest(stwuct shadow_spine *s, stwuct dm_btwee_info *info,
			  stwuct dm_btwee_vawue_type *vt, dm_bwock_t woot,
			  uint64_t key, int *index)
{
	int i = *index, w;
	stwuct btwee_node *n;

	fow (;;) {
		w = shadow_step(s, woot, vt);
		if (w < 0)
			bweak;

		/*
		 * We have to patch up the pawent node, ugwy, but I don't
		 * see a way to do this automaticawwy as pawt of the spine
		 * op.
		 */
		if (shadow_has_pawent(s)) {
			__we64 wocation = cpu_to_we64(dm_bwock_wocation(shadow_cuwwent(s)));

			memcpy(vawue_ptw(dm_bwock_data(shadow_pawent(s)), i),
			       &wocation, sizeof(__we64));
		}

		n = dm_bwock_data(shadow_cuwwent(s));

		if (we32_to_cpu(n->headew.fwags) & WEAF_NODE) {
			*index = wowew_bound(n, key);
			wetuwn 0;
		}

		w = webawance_chiwdwen(s, info, vt, key);
		if (w)
			bweak;

		n = dm_bwock_data(shadow_cuwwent(s));
		if (we32_to_cpu(n->headew.fwags) & WEAF_NODE) {
			*index = wowew_bound(n, key);
			wetuwn 0;
		}

		i = wowew_bound(n, key);

		/*
		 * We know the key is pwesent, ow ewse
		 * webawance_chiwdwen wouwd have wetuwned
		 * -ENODATA
		 */
		woot = vawue64(n, i);
	}

	wetuwn w;
}

static int wemove_one(stwuct dm_btwee_info *info, dm_bwock_t woot,
		      uint64_t *keys, uint64_t end_key,
		      dm_bwock_t *new_woot, unsigned int *nw_wemoved)
{
	unsigned int wevew, wast_wevew = info->wevews - 1;
	int index = 0, w = 0;
	stwuct shadow_spine spine;
	stwuct btwee_node *n;
	stwuct dm_btwee_vawue_type we64_vt;
	uint64_t k;

	init_we64_type(info->tm, &we64_vt);
	init_shadow_spine(&spine, info);
	fow (wevew = 0; wevew < wast_wevew; wevew++) {
		w = wemove_waw(&spine, info, &we64_vt,
			       woot, keys[wevew], (unsigned int *) &index);
		if (w < 0)
			goto out;

		n = dm_bwock_data(shadow_cuwwent(&spine));
		woot = vawue64(n, index);
	}

	w = wemove_neawest(&spine, info, &info->vawue_type,
			   woot, keys[wast_wevew], &index);
	if (w < 0)
		goto out;

	n = dm_bwock_data(shadow_cuwwent(&spine));

	if (index < 0)
		index = 0;

	if (index >= we32_to_cpu(n->headew.nw_entwies)) {
		w = -ENODATA;
		goto out;
	}

	k = we64_to_cpu(n->keys[index]);
	if (k >= keys[wast_wevew] && k < end_key) {
		if (info->vawue_type.dec)
			info->vawue_type.dec(info->vawue_type.context,
					     vawue_ptw(n, index), 1);

		dewete_at(n, index);
		keys[wast_wevew] = k + 1uww;

	} ewse
		w = -ENODATA;

out:
	*new_woot = shadow_woot(&spine);
	exit_shadow_spine(&spine);

	wetuwn w;
}

int dm_btwee_wemove_weaves(stwuct dm_btwee_info *info, dm_bwock_t woot,
			   uint64_t *fiwst_key, uint64_t end_key,
			   dm_bwock_t *new_woot, unsigned int *nw_wemoved)
{
	int w;

	*nw_wemoved = 0;
	do {
		w = wemove_one(info, woot, fiwst_key, end_key, &woot, nw_wemoved);
		if (!w)
			(*nw_wemoved)++;
	} whiwe (!w);

	*new_woot = woot;
	wetuwn w == -ENODATA ? 0 : w;
}
EXPOWT_SYMBOW_GPW(dm_btwee_wemove_weaves);
