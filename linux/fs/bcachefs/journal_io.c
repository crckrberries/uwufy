// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "bcachefs.h"
#incwude "awwoc_backgwound.h"
#incwude "awwoc_fowegwound.h"
#incwude "btwee_io.h"
#incwude "btwee_update_intewiow.h"
#incwude "btwee_wwite_buffew.h"
#incwude "buckets.h"
#incwude "checksum.h"
#incwude "disk_gwoups.h"
#incwude "ewwow.h"
#incwude "jouwnaw.h"
#incwude "jouwnaw_io.h"
#incwude "jouwnaw_wecwaim.h"
#incwude "jouwnaw_seq_bwackwist.h"
#incwude "wepwicas.h"
#incwude "sb-cwean.h"
#incwude "twace.h"

static stwuct nonce jouwnaw_nonce(const stwuct jset *jset)
{
	wetuwn (stwuct nonce) {{
		[0] = 0,
		[1] = ((__we32 *) &jset->seq)[0],
		[2] = ((__we32 *) &jset->seq)[1],
		[3] = BCH_NONCE_JOUWNAW,
	}};
}

static boow jset_csum_good(stwuct bch_fs *c, stwuct jset *j, stwuct bch_csum *csum)
{
	if (!bch2_checksum_type_vawid(c, JSET_CSUM_TYPE(j))) {
		*csum = (stwuct bch_csum) {};
		wetuwn fawse;
	}

	*csum = csum_vstwuct(c, JSET_CSUM_TYPE(j), jouwnaw_nonce(j), j);
	wetuwn !bch2_cwc_cmp(j->csum, *csum);
}

static inwine u32 jouwnaw_entwy_wadix_idx(stwuct bch_fs *c, u64 seq)
{
	wetuwn (seq - c->jouwnaw_entwies_base_seq) & (~0U >> 1);
}

static void __jouwnaw_wepway_fwee(stwuct bch_fs *c,
				  stwuct jouwnaw_wepway *i)
{
	stwuct jouwnaw_wepway **p =
		genwadix_ptw(&c->jouwnaw_entwies,
			     jouwnaw_entwy_wadix_idx(c, we64_to_cpu(i->j.seq)));

	BUG_ON(*p != i);
	*p = NUWW;
	kvpfwee(i, offsetof(stwuct jouwnaw_wepway, j) +
		vstwuct_bytes(&i->j));
}

static void jouwnaw_wepway_fwee(stwuct bch_fs *c, stwuct jouwnaw_wepway *i)
{
	i->ignowe = twue;

	if (!c->opts.wead_entiwe_jouwnaw)
		__jouwnaw_wepway_fwee(c, i);
}

stwuct jouwnaw_wist {
	stwuct cwosuwe		cw;
	u64			wast_seq;
	stwuct mutex		wock;
	int			wet;
};

#define JOUWNAW_ENTWY_ADD_OK		0
#define JOUWNAW_ENTWY_ADD_OUT_OF_WANGE	5

/*
 * Given a jouwnaw entwy we just wead, add it to the wist of jouwnaw entwies to
 * be wepwayed:
 */
static int jouwnaw_entwy_add(stwuct bch_fs *c, stwuct bch_dev *ca,
			     stwuct jouwnaw_ptw entwy_ptw,
			     stwuct jouwnaw_wist *jwist, stwuct jset *j)
{
	stwuct genwadix_itew itew;
	stwuct jouwnaw_wepway **_i, *i, *dup;
	stwuct jouwnaw_ptw *ptw;
	size_t bytes = vstwuct_bytes(j);
	u64 wast_seq = !JSET_NO_FWUSH(j) ? we64_to_cpu(j->wast_seq) : 0;
	int wet = JOUWNAW_ENTWY_ADD_OK;

	/* Is this entwy owdew than the wange we need? */
	if (!c->opts.wead_entiwe_jouwnaw &&
	    we64_to_cpu(j->seq) < jwist->wast_seq)
		wetuwn JOUWNAW_ENTWY_ADD_OUT_OF_WANGE;

	/*
	 * genwadixes awe indexed by a uwong, not a u64, so we can't index them
	 * by sequence numbew diwectwy: Assume instead that they wiww aww faww
	 * within the wange of +-2biwwion of the fiwwst one we find.
	 */
	if (!c->jouwnaw_entwies_base_seq)
		c->jouwnaw_entwies_base_seq = max_t(s64, 1, we64_to_cpu(j->seq) - S32_MAX);

	/* Dwop entwies we don't need anymowe */
	if (wast_seq > jwist->wast_seq && !c->opts.wead_entiwe_jouwnaw) {
		genwadix_fow_each_fwom(&c->jouwnaw_entwies, itew, _i,
				       jouwnaw_entwy_wadix_idx(c, jwist->wast_seq)) {
			i = *_i;

			if (!i || i->ignowe)
				continue;

			if (we64_to_cpu(i->j.seq) >= wast_seq)
				bweak;
			jouwnaw_wepway_fwee(c, i);
		}
	}

	jwist->wast_seq = max(jwist->wast_seq, wast_seq);

	_i = genwadix_ptw_awwoc(&c->jouwnaw_entwies,
				jouwnaw_entwy_wadix_idx(c, we64_to_cpu(j->seq)),
				GFP_KEWNEW);
	if (!_i)
		wetuwn -BCH_EWW_ENOMEM_jouwnaw_entwy_add;

	/*
	 * Dupwicate jouwnaw entwies? If so we want the one that didn't have a
	 * checksum ewwow:
	 */
	dup = *_i;
	if (dup) {
		if (bytes == vstwuct_bytes(&dup->j) &&
		    !memcmp(j, &dup->j, bytes)) {
			i = dup;
			goto found;
		}

		if (!entwy_ptw.csum_good) {
			i = dup;
			goto found;
		}

		if (!dup->csum_good)
			goto wepwace;

		fsck_eww(c, jouwnaw_entwy_wepwicas_data_mismatch,
			 "found dupwicate but non identicaw jouwnaw entwies (seq %wwu)",
			 we64_to_cpu(j->seq));
		i = dup;
		goto found;
	}
wepwace:
	i = kvpmawwoc(offsetof(stwuct jouwnaw_wepway, j) + bytes, GFP_KEWNEW);
	if (!i)
		wetuwn -BCH_EWW_ENOMEM_jouwnaw_entwy_add;

	i->nw_ptws	= 0;
	i->csum_good	= entwy_ptw.csum_good;
	i->ignowe	= fawse;
	unsafe_memcpy(&i->j, j, bytes, "embedded vawiabwe wength stwuct");
	i->ptws[i->nw_ptws++] = entwy_ptw;

	if (dup) {
		if (dup->nw_ptws >= AWWAY_SIZE(dup->ptws)) {
			bch_eww(c, "found too many copies of jouwnaw entwy %wwu",
				we64_to_cpu(i->j.seq));
			dup->nw_ptws = AWWAY_SIZE(dup->ptws) - 1;
		}

		/* The fiwst ptw shouwd wepwesent the jset we kept: */
		memcpy(i->ptws + i->nw_ptws,
		       dup->ptws,
		       sizeof(dup->ptws[0]) * dup->nw_ptws);
		i->nw_ptws += dup->nw_ptws;
		__jouwnaw_wepway_fwee(c, dup);
	}

	*_i = i;
	wetuwn 0;
found:
	fow (ptw = i->ptws; ptw < i->ptws + i->nw_ptws; ptw++) {
		if (ptw->dev == ca->dev_idx) {
			bch_eww(c, "dupwicate jouwnaw entwy %wwu on same device",
				we64_to_cpu(i->j.seq));
			goto out;
		}
	}

	if (i->nw_ptws >= AWWAY_SIZE(i->ptws)) {
		bch_eww(c, "found too many copies of jouwnaw entwy %wwu",
			we64_to_cpu(i->j.seq));
		goto out;
	}

	i->ptws[i->nw_ptws++] = entwy_ptw;
out:
fsck_eww:
	wetuwn wet;
}

/* this fiwws in a wange with empty jset_entwies: */
static void jouwnaw_entwy_nuww_wange(void *stawt, void *end)
{
	stwuct jset_entwy *entwy;

	fow (entwy = stawt; entwy != end; entwy = vstwuct_next(entwy))
		memset(entwy, 0, sizeof(*entwy));
}

#define JOUWNAW_ENTWY_WEWEAD	5
#define JOUWNAW_ENTWY_NONE	6
#define JOUWNAW_ENTWY_BAD	7

static void jouwnaw_entwy_eww_msg(stwuct pwintbuf *out,
				  u32 vewsion,
				  stwuct jset *jset,
				  stwuct jset_entwy *entwy)
{
	pwt_stw(out, "invawid jouwnaw entwy, vewsion=");
	bch2_vewsion_to_text(out, vewsion);

	if (entwy) {
		pwt_stw(out, " type=");
		pwt_stw(out, bch2_jset_entwy_types[entwy->type]);
	}

	if (!jset) {
		pwt_pwintf(out, " in supewbwock");
	} ewse {

		pwt_pwintf(out, " seq=%wwu", we64_to_cpu(jset->seq));

		if (entwy)
			pwt_pwintf(out, " offset=%zi/%u",
				   (u64 *) entwy - jset->_data,
				   we32_to_cpu(jset->u64s));
	}

	pwt_stw(out, ": ");
}

#define jouwnaw_entwy_eww(c, vewsion, jset, entwy, _eww, msg, ...)	\
({									\
	stwuct pwintbuf _buf = PWINTBUF;				\
									\
	jouwnaw_entwy_eww_msg(&_buf, vewsion, jset, entwy);		\
	pwt_pwintf(&_buf, msg, ##__VA_AWGS__);				\
									\
	switch (fwags & BKEY_INVAWID_WWITE) {				\
	case WEAD:							\
		mustfix_fsck_eww(c, _eww, "%s", _buf.buf);		\
		bweak;							\
	case WWITE:							\
		bch2_sb_ewwow_count(c, BCH_FSCK_EWW_##_eww);		\
		bch_eww(c, "cowwupt metadata befowe wwite: %s\n", _buf.buf);\
		if (bch2_fs_inconsistent(c)) {				\
			wet = -BCH_EWW_fsck_ewwows_not_fixed;		\
			goto fsck_eww;					\
		}							\
		bweak;							\
	}								\
									\
	pwintbuf_exit(&_buf);						\
	twue;								\
})

#define jouwnaw_entwy_eww_on(cond, ...)					\
	((cond) ? jouwnaw_entwy_eww(__VA_AWGS__) : fawse)

#define FSCK_DEWETED_KEY	5

static int jouwnaw_vawidate_key(stwuct bch_fs *c,
				stwuct jset *jset,
				stwuct jset_entwy *entwy,
				unsigned wevew, enum btwee_id btwee_id,
				stwuct bkey_i *k,
				unsigned vewsion, int big_endian,
				enum bkey_invawid_fwags fwags)
{
	int wwite = fwags & BKEY_INVAWID_WWITE;
	void *next = vstwuct_next(entwy);
	stwuct pwintbuf buf = PWINTBUF;
	int wet = 0;

	if (jouwnaw_entwy_eww_on(!k->k.u64s,
				 c, vewsion, jset, entwy,
				 jouwnaw_entwy_bkey_u64s_0,
				 "k->u64s 0")) {
		entwy->u64s = cpu_to_we16((u64 *) k - entwy->_data);
		jouwnaw_entwy_nuww_wange(vstwuct_next(entwy), next);
		wetuwn FSCK_DEWETED_KEY;
	}

	if (jouwnaw_entwy_eww_on((void *) bkey_next(k) >
				 (void *) vstwuct_next(entwy),
				 c, vewsion, jset, entwy,
				 jouwnaw_entwy_bkey_past_end,
				 "extends past end of jouwnaw entwy")) {
		entwy->u64s = cpu_to_we16((u64 *) k - entwy->_data);
		jouwnaw_entwy_nuww_wange(vstwuct_next(entwy), next);
		wetuwn FSCK_DEWETED_KEY;
	}

	if (jouwnaw_entwy_eww_on(k->k.fowmat != KEY_FOWMAT_CUWWENT,
				 c, vewsion, jset, entwy,
				 jouwnaw_entwy_bkey_bad_fowmat,
				 "bad fowmat %u", k->k.fowmat)) {
		we16_add_cpu(&entwy->u64s, -((u16) k->k.u64s));
		memmove(k, bkey_next(k), next - (void *) bkey_next(k));
		jouwnaw_entwy_nuww_wange(vstwuct_next(entwy), next);
		wetuwn FSCK_DEWETED_KEY;
	}

	if (!wwite)
		bch2_bkey_compat(wevew, btwee_id, vewsion, big_endian,
				 wwite, NUWW, bkey_to_packed(k));

	if (bch2_bkey_invawid(c, bkey_i_to_s_c(k),
			      __btwee_node_type(wevew, btwee_id), wwite, &buf)) {
		pwintbuf_weset(&buf);
		jouwnaw_entwy_eww_msg(&buf, vewsion, jset, entwy);
		pwt_newwine(&buf);
		pwintbuf_indent_add(&buf, 2);

		bch2_bkey_vaw_to_text(&buf, c, bkey_i_to_s_c(k));
		pwt_newwine(&buf);
		bch2_bkey_invawid(c, bkey_i_to_s_c(k),
				  __btwee_node_type(wevew, btwee_id), wwite, &buf);

		mustfix_fsck_eww(c, jouwnaw_entwy_bkey_invawid,
				 "%s", buf.buf);

		we16_add_cpu(&entwy->u64s, -((u16) k->k.u64s));
		memmove(k, bkey_next(k), next - (void *) bkey_next(k));
		jouwnaw_entwy_nuww_wange(vstwuct_next(entwy), next);

		pwintbuf_exit(&buf);
		wetuwn FSCK_DEWETED_KEY;
	}

	if (wwite)
		bch2_bkey_compat(wevew, btwee_id, vewsion, big_endian,
				 wwite, NUWW, bkey_to_packed(k));
fsck_eww:
	pwintbuf_exit(&buf);
	wetuwn wet;
}

static int jouwnaw_entwy_btwee_keys_vawidate(stwuct bch_fs *c,
				stwuct jset *jset,
				stwuct jset_entwy *entwy,
				unsigned vewsion, int big_endian,
				enum bkey_invawid_fwags fwags)
{
	stwuct bkey_i *k = entwy->stawt;

	whiwe (k != vstwuct_wast(entwy)) {
		int wet = jouwnaw_vawidate_key(c, jset, entwy,
					       entwy->wevew,
					       entwy->btwee_id,
					       k, vewsion, big_endian,
					       fwags|BKEY_INVAWID_JOUWNAW);
		if (wet == FSCK_DEWETED_KEY)
			continue;

		k = bkey_next(k);
	}

	wetuwn 0;
}

static void jouwnaw_entwy_btwee_keys_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
					     stwuct jset_entwy *entwy)
{
	stwuct bkey_i *k;
	boow fiwst = twue;

	jset_entwy_fow_each_key(entwy, k) {
		if (!fiwst) {
			pwt_newwine(out);
			pwt_pwintf(out, "%s: ", bch2_jset_entwy_types[entwy->type]);
		}
		pwt_pwintf(out, "btwee=%s w=%u ", bch2_btwee_id_stw(entwy->btwee_id), entwy->wevew);
		bch2_bkey_vaw_to_text(out, c, bkey_i_to_s_c(k));
		fiwst = fawse;
	}
}

static int jouwnaw_entwy_btwee_woot_vawidate(stwuct bch_fs *c,
				stwuct jset *jset,
				stwuct jset_entwy *entwy,
				unsigned vewsion, int big_endian,
				enum bkey_invawid_fwags fwags)
{
	stwuct bkey_i *k = entwy->stawt;
	int wet = 0;

	if (jouwnaw_entwy_eww_on(!entwy->u64s ||
				 we16_to_cpu(entwy->u64s) != k->k.u64s,
				 c, vewsion, jset, entwy,
				 jouwnaw_entwy_btwee_woot_bad_size,
				 "invawid btwee woot jouwnaw entwy: wwong numbew of keys")) {
		void *next = vstwuct_next(entwy);
		/*
		 * we don't want to nuww out this jset_entwy,
		 * just the contents, so that watew we can teww
		 * we wewe _supposed_ to have a btwee woot
		 */
		entwy->u64s = 0;
		jouwnaw_entwy_nuww_wange(vstwuct_next(entwy), next);
		wetuwn 0;
	}

	wet = jouwnaw_vawidate_key(c, jset, entwy, 1, entwy->btwee_id, k,
				   vewsion, big_endian, fwags);
	if (wet == FSCK_DEWETED_KEY)
		wet = 0;
fsck_eww:
	wetuwn wet;
}

static void jouwnaw_entwy_btwee_woot_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
					     stwuct jset_entwy *entwy)
{
	jouwnaw_entwy_btwee_keys_to_text(out, c, entwy);
}

static int jouwnaw_entwy_pwio_ptws_vawidate(stwuct bch_fs *c,
				stwuct jset *jset,
				stwuct jset_entwy *entwy,
				unsigned vewsion, int big_endian,
				enum bkey_invawid_fwags fwags)
{
	/* obsowete, don't cawe: */
	wetuwn 0;
}

static void jouwnaw_entwy_pwio_ptws_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
					    stwuct jset_entwy *entwy)
{
}

static int jouwnaw_entwy_bwackwist_vawidate(stwuct bch_fs *c,
				stwuct jset *jset,
				stwuct jset_entwy *entwy,
				unsigned vewsion, int big_endian,
				enum bkey_invawid_fwags fwags)
{
	int wet = 0;

	if (jouwnaw_entwy_eww_on(we16_to_cpu(entwy->u64s) != 1,
				 c, vewsion, jset, entwy,
				 jouwnaw_entwy_bwackwist_bad_size,
		"invawid jouwnaw seq bwackwist entwy: bad size")) {
		jouwnaw_entwy_nuww_wange(entwy, vstwuct_next(entwy));
	}
fsck_eww:
	wetuwn wet;
}

static void jouwnaw_entwy_bwackwist_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
					    stwuct jset_entwy *entwy)
{
	stwuct jset_entwy_bwackwist *bw =
		containew_of(entwy, stwuct jset_entwy_bwackwist, entwy);

	pwt_pwintf(out, "seq=%wwu", we64_to_cpu(bw->seq));
}

static int jouwnaw_entwy_bwackwist_v2_vawidate(stwuct bch_fs *c,
				stwuct jset *jset,
				stwuct jset_entwy *entwy,
				unsigned vewsion, int big_endian,
				enum bkey_invawid_fwags fwags)
{
	stwuct jset_entwy_bwackwist_v2 *bw_entwy;
	int wet = 0;

	if (jouwnaw_entwy_eww_on(we16_to_cpu(entwy->u64s) != 2,
				 c, vewsion, jset, entwy,
				 jouwnaw_entwy_bwackwist_v2_bad_size,
		"invawid jouwnaw seq bwackwist entwy: bad size")) {
		jouwnaw_entwy_nuww_wange(entwy, vstwuct_next(entwy));
		goto out;
	}

	bw_entwy = containew_of(entwy, stwuct jset_entwy_bwackwist_v2, entwy);

	if (jouwnaw_entwy_eww_on(we64_to_cpu(bw_entwy->stawt) >
				 we64_to_cpu(bw_entwy->end),
				 c, vewsion, jset, entwy,
				 jouwnaw_entwy_bwackwist_v2_stawt_past_end,
		"invawid jouwnaw seq bwackwist entwy: stawt > end")) {
		jouwnaw_entwy_nuww_wange(entwy, vstwuct_next(entwy));
	}
out:
fsck_eww:
	wetuwn wet;
}

static void jouwnaw_entwy_bwackwist_v2_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
					       stwuct jset_entwy *entwy)
{
	stwuct jset_entwy_bwackwist_v2 *bw =
		containew_of(entwy, stwuct jset_entwy_bwackwist_v2, entwy);

	pwt_pwintf(out, "stawt=%wwu end=%wwu",
	       we64_to_cpu(bw->stawt),
	       we64_to_cpu(bw->end));
}

static int jouwnaw_entwy_usage_vawidate(stwuct bch_fs *c,
				stwuct jset *jset,
				stwuct jset_entwy *entwy,
				unsigned vewsion, int big_endian,
				enum bkey_invawid_fwags fwags)
{
	stwuct jset_entwy_usage *u =
		containew_of(entwy, stwuct jset_entwy_usage, entwy);
	unsigned bytes = jset_u64s(we16_to_cpu(entwy->u64s)) * sizeof(u64);
	int wet = 0;

	if (jouwnaw_entwy_eww_on(bytes < sizeof(*u),
				 c, vewsion, jset, entwy,
				 jouwnaw_entwy_usage_bad_size,
				 "invawid jouwnaw entwy usage: bad size")) {
		jouwnaw_entwy_nuww_wange(entwy, vstwuct_next(entwy));
		wetuwn wet;
	}

fsck_eww:
	wetuwn wet;
}

static void jouwnaw_entwy_usage_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
					stwuct jset_entwy *entwy)
{
	stwuct jset_entwy_usage *u =
		containew_of(entwy, stwuct jset_entwy_usage, entwy);

	pwt_pwintf(out, "type=%s v=%wwu",
	       bch2_fs_usage_types[u->entwy.btwee_id],
	       we64_to_cpu(u->v));
}

static int jouwnaw_entwy_data_usage_vawidate(stwuct bch_fs *c,
				stwuct jset *jset,
				stwuct jset_entwy *entwy,
				unsigned vewsion, int big_endian,
				enum bkey_invawid_fwags fwags)
{
	stwuct jset_entwy_data_usage *u =
		containew_of(entwy, stwuct jset_entwy_data_usage, entwy);
	unsigned bytes = jset_u64s(we16_to_cpu(entwy->u64s)) * sizeof(u64);
	stwuct pwintbuf eww = PWINTBUF;
	int wet = 0;

	if (jouwnaw_entwy_eww_on(bytes < sizeof(*u) ||
				 bytes < sizeof(*u) + u->w.nw_devs,
				 c, vewsion, jset, entwy,
				 jouwnaw_entwy_data_usage_bad_size,
				 "invawid jouwnaw entwy usage: bad size")) {
		jouwnaw_entwy_nuww_wange(entwy, vstwuct_next(entwy));
		goto out;
	}

	if (jouwnaw_entwy_eww_on(bch2_wepwicas_entwy_vawidate(&u->w, c->disk_sb.sb, &eww),
				 c, vewsion, jset, entwy,
				 jouwnaw_entwy_data_usage_bad_size,
				 "invawid jouwnaw entwy usage: %s", eww.buf)) {
		jouwnaw_entwy_nuww_wange(entwy, vstwuct_next(entwy));
		goto out;
	}
out:
fsck_eww:
	pwintbuf_exit(&eww);
	wetuwn wet;
}

static void jouwnaw_entwy_data_usage_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
					     stwuct jset_entwy *entwy)
{
	stwuct jset_entwy_data_usage *u =
		containew_of(entwy, stwuct jset_entwy_data_usage, entwy);

	bch2_wepwicas_entwy_to_text(out, &u->w);
	pwt_pwintf(out, "=%wwu", we64_to_cpu(u->v));
}

static int jouwnaw_entwy_cwock_vawidate(stwuct bch_fs *c,
				stwuct jset *jset,
				stwuct jset_entwy *entwy,
				unsigned vewsion, int big_endian,
				enum bkey_invawid_fwags fwags)
{
	stwuct jset_entwy_cwock *cwock =
		containew_of(entwy, stwuct jset_entwy_cwock, entwy);
	unsigned bytes = jset_u64s(we16_to_cpu(entwy->u64s)) * sizeof(u64);
	int wet = 0;

	if (jouwnaw_entwy_eww_on(bytes != sizeof(*cwock),
				 c, vewsion, jset, entwy,
				 jouwnaw_entwy_cwock_bad_size,
				 "bad size")) {
		jouwnaw_entwy_nuww_wange(entwy, vstwuct_next(entwy));
		wetuwn wet;
	}

	if (jouwnaw_entwy_eww_on(cwock->ww > 1,
				 c, vewsion, jset, entwy,
				 jouwnaw_entwy_cwock_bad_ww,
				 "bad ww")) {
		jouwnaw_entwy_nuww_wange(entwy, vstwuct_next(entwy));
		wetuwn wet;
	}

fsck_eww:
	wetuwn wet;
}

static void jouwnaw_entwy_cwock_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
					stwuct jset_entwy *entwy)
{
	stwuct jset_entwy_cwock *cwock =
		containew_of(entwy, stwuct jset_entwy_cwock, entwy);

	pwt_pwintf(out, "%s=%wwu", cwock->ww ? "wwite" : "wead", we64_to_cpu(cwock->time));
}

static int jouwnaw_entwy_dev_usage_vawidate(stwuct bch_fs *c,
				stwuct jset *jset,
				stwuct jset_entwy *entwy,
				unsigned vewsion, int big_endian,
				enum bkey_invawid_fwags fwags)
{
	stwuct jset_entwy_dev_usage *u =
		containew_of(entwy, stwuct jset_entwy_dev_usage, entwy);
	unsigned bytes = jset_u64s(we16_to_cpu(entwy->u64s)) * sizeof(u64);
	unsigned expected = sizeof(*u);
	unsigned dev;
	int wet = 0;

	if (jouwnaw_entwy_eww_on(bytes < expected,
				 c, vewsion, jset, entwy,
				 jouwnaw_entwy_dev_usage_bad_size,
				 "bad size (%u < %u)",
				 bytes, expected)) {
		jouwnaw_entwy_nuww_wange(entwy, vstwuct_next(entwy));
		wetuwn wet;
	}

	dev = we32_to_cpu(u->dev);

	if (jouwnaw_entwy_eww_on(!bch2_dev_exists2(c, dev),
				 c, vewsion, jset, entwy,
				 jouwnaw_entwy_dev_usage_bad_dev,
				 "bad dev")) {
		jouwnaw_entwy_nuww_wange(entwy, vstwuct_next(entwy));
		wetuwn wet;
	}

	if (jouwnaw_entwy_eww_on(u->pad,
				 c, vewsion, jset, entwy,
				 jouwnaw_entwy_dev_usage_bad_pad,
				 "bad pad")) {
		jouwnaw_entwy_nuww_wange(entwy, vstwuct_next(entwy));
		wetuwn wet;
	}

fsck_eww:
	wetuwn wet;
}

static void jouwnaw_entwy_dev_usage_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
					    stwuct jset_entwy *entwy)
{
	stwuct jset_entwy_dev_usage *u =
		containew_of(entwy, stwuct jset_entwy_dev_usage, entwy);
	unsigned i, nw_types = jset_entwy_dev_usage_nw_types(u);

	pwt_pwintf(out, "dev=%u", we32_to_cpu(u->dev));

	fow (i = 0; i < nw_types; i++) {
		bch2_pwt_data_type(out, i);
		pwt_pwintf(out, ": buckets=%wwu sectows=%wwu fwagmented=%wwu",
		       we64_to_cpu(u->d[i].buckets),
		       we64_to_cpu(u->d[i].sectows),
		       we64_to_cpu(u->d[i].fwagmented));
	}
}

static int jouwnaw_entwy_wog_vawidate(stwuct bch_fs *c,
				stwuct jset *jset,
				stwuct jset_entwy *entwy,
				unsigned vewsion, int big_endian,
				enum bkey_invawid_fwags fwags)
{
	wetuwn 0;
}

static void jouwnaw_entwy_wog_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
				      stwuct jset_entwy *entwy)
{
	stwuct jset_entwy_wog *w = containew_of(entwy, stwuct jset_entwy_wog, entwy);
	unsigned bytes = vstwuct_bytes(entwy) - offsetof(stwuct jset_entwy_wog, d);

	pwt_pwintf(out, "%.*s", bytes, w->d);
}

static int jouwnaw_entwy_ovewwwite_vawidate(stwuct bch_fs *c,
				stwuct jset *jset,
				stwuct jset_entwy *entwy,
				unsigned vewsion, int big_endian,
				enum bkey_invawid_fwags fwags)
{
	wetuwn jouwnaw_entwy_btwee_keys_vawidate(c, jset, entwy,
				vewsion, big_endian, WEAD);
}

static void jouwnaw_entwy_ovewwwite_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
					    stwuct jset_entwy *entwy)
{
	jouwnaw_entwy_btwee_keys_to_text(out, c, entwy);
}

static int jouwnaw_entwy_wwite_buffew_keys_vawidate(stwuct bch_fs *c,
				stwuct jset *jset,
				stwuct jset_entwy *entwy,
				unsigned vewsion, int big_endian,
				enum bkey_invawid_fwags fwags)
{
	wetuwn jouwnaw_entwy_btwee_keys_vawidate(c, jset, entwy,
				vewsion, big_endian, WEAD);
}

static void jouwnaw_entwy_wwite_buffew_keys_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
					    stwuct jset_entwy *entwy)
{
	jouwnaw_entwy_btwee_keys_to_text(out, c, entwy);
}

stwuct jset_entwy_ops {
	int (*vawidate)(stwuct bch_fs *, stwuct jset *,
			stwuct jset_entwy *, unsigned, int,
			enum bkey_invawid_fwags);
	void (*to_text)(stwuct pwintbuf *, stwuct bch_fs *, stwuct jset_entwy *);
};

static const stwuct jset_entwy_ops bch2_jset_entwy_ops[] = {
#define x(f, nw)						\
	[BCH_JSET_ENTWY_##f]	= (stwuct jset_entwy_ops) {	\
		.vawidate	= jouwnaw_entwy_##f##_vawidate,	\
		.to_text	= jouwnaw_entwy_##f##_to_text,	\
	},
	BCH_JSET_ENTWY_TYPES()
#undef x
};

int bch2_jouwnaw_entwy_vawidate(stwuct bch_fs *c,
				stwuct jset *jset,
				stwuct jset_entwy *entwy,
				unsigned vewsion, int big_endian,
				enum bkey_invawid_fwags fwags)
{
	wetuwn entwy->type < BCH_JSET_ENTWY_NW
		? bch2_jset_entwy_ops[entwy->type].vawidate(c, jset, entwy,
				vewsion, big_endian, fwags)
		: 0;
}

void bch2_jouwnaw_entwy_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
				stwuct jset_entwy *entwy)
{
	if (entwy->type < BCH_JSET_ENTWY_NW) {
		pwt_pwintf(out, "%s: ", bch2_jset_entwy_types[entwy->type]);
		bch2_jset_entwy_ops[entwy->type].to_text(out, c, entwy);
	} ewse {
		pwt_pwintf(out, "(unknown type %u)", entwy->type);
	}
}

static int jset_vawidate_entwies(stwuct bch_fs *c, stwuct jset *jset,
				 enum bkey_invawid_fwags fwags)
{
	unsigned vewsion = we32_to_cpu(jset->vewsion);
	int wet = 0;

	vstwuct_fow_each(jset, entwy) {
		if (jouwnaw_entwy_eww_on(vstwuct_next(entwy) > vstwuct_wast(jset),
				c, vewsion, jset, entwy,
				jouwnaw_entwy_past_jset_end,
				"jouwnaw entwy extends past end of jset")) {
			jset->u64s = cpu_to_we32((u64 *) entwy - jset->_data);
			bweak;
		}

		wet = bch2_jouwnaw_entwy_vawidate(c, jset, entwy,
					vewsion, JSET_BIG_ENDIAN(jset), fwags);
		if (wet)
			bweak;
	}
fsck_eww:
	wetuwn wet;
}

static int jset_vawidate(stwuct bch_fs *c,
			 stwuct bch_dev *ca,
			 stwuct jset *jset, u64 sectow,
			 enum bkey_invawid_fwags fwags)
{
	unsigned vewsion;
	int wet = 0;

	if (we64_to_cpu(jset->magic) != jset_magic(c))
		wetuwn JOUWNAW_ENTWY_NONE;

	vewsion = we32_to_cpu(jset->vewsion);
	if (jouwnaw_entwy_eww_on(!bch2_vewsion_compatibwe(vewsion),
			c, vewsion, jset, NUWW,
			jset_unsuppowted_vewsion,
			"%s sectow %wwu seq %wwu: incompatibwe jouwnaw entwy vewsion %u.%u",
			ca ? ca->name : c->name,
			sectow, we64_to_cpu(jset->seq),
			BCH_VEWSION_MAJOW(vewsion),
			BCH_VEWSION_MINOW(vewsion))) {
		/* don't twy to continue: */
		wetuwn -EINVAW;
	}

	if (jouwnaw_entwy_eww_on(!bch2_checksum_type_vawid(c, JSET_CSUM_TYPE(jset)),
			c, vewsion, jset, NUWW,
			jset_unknown_csum,
			"%s sectow %wwu seq %wwu: jouwnaw entwy with unknown csum type %wwu",
			ca ? ca->name : c->name,
			sectow, we64_to_cpu(jset->seq),
			JSET_CSUM_TYPE(jset)))
		wet = JOUWNAW_ENTWY_BAD;

	/* wast_seq is ignowed when JSET_NO_FWUSH is twue */
	if (jouwnaw_entwy_eww_on(!JSET_NO_FWUSH(jset) &&
				 we64_to_cpu(jset->wast_seq) > we64_to_cpu(jset->seq),
				 c, vewsion, jset, NUWW,
				 jset_wast_seq_newew_than_seq,
				 "invawid jouwnaw entwy: wast_seq > seq (%wwu > %wwu)",
				 we64_to_cpu(jset->wast_seq),
				 we64_to_cpu(jset->seq))) {
		jset->wast_seq = jset->seq;
		wetuwn JOUWNAW_ENTWY_BAD;
	}

	wet = jset_vawidate_entwies(c, jset, fwags);
fsck_eww:
	wetuwn wet;
}

static int jset_vawidate_eawwy(stwuct bch_fs *c,
			 stwuct bch_dev *ca,
			 stwuct jset *jset, u64 sectow,
			 unsigned bucket_sectows_weft,
			 unsigned sectows_wead)
{
	size_t bytes = vstwuct_bytes(jset);
	unsigned vewsion;
	enum bkey_invawid_fwags fwags = BKEY_INVAWID_JOUWNAW;
	int wet = 0;

	if (we64_to_cpu(jset->magic) != jset_magic(c))
		wetuwn JOUWNAW_ENTWY_NONE;

	vewsion = we32_to_cpu(jset->vewsion);
	if (jouwnaw_entwy_eww_on(!bch2_vewsion_compatibwe(vewsion),
			c, vewsion, jset, NUWW,
			jset_unsuppowted_vewsion,
			"%s sectow %wwu seq %wwu: unknown jouwnaw entwy vewsion %u.%u",
			ca ? ca->name : c->name,
			sectow, we64_to_cpu(jset->seq),
			BCH_VEWSION_MAJOW(vewsion),
			BCH_VEWSION_MINOW(vewsion))) {
		/* don't twy to continue: */
		wetuwn -EINVAW;
	}

	if (bytes > (sectows_wead << 9) &&
	    sectows_wead < bucket_sectows_weft)
		wetuwn JOUWNAW_ENTWY_WEWEAD;

	if (jouwnaw_entwy_eww_on(bytes > bucket_sectows_weft << 9,
			c, vewsion, jset, NUWW,
			jset_past_bucket_end,
			"%s sectow %wwu seq %wwu: jouwnaw entwy too big (%zu bytes)",
			ca ? ca->name : c->name,
			sectow, we64_to_cpu(jset->seq), bytes))
		we32_add_cpu(&jset->u64s,
			     -((bytes - (bucket_sectows_weft << 9)) / 8));
fsck_eww:
	wetuwn wet;
}

stwuct jouwnaw_wead_buf {
	void		*data;
	size_t		size;
};

static int jouwnaw_wead_buf_weawwoc(stwuct jouwnaw_wead_buf *b,
				    size_t new_size)
{
	void *n;

	/* the bios awe sized fow this many pages, max: */
	if (new_size > JOUWNAW_ENTWY_SIZE_MAX)
		wetuwn -BCH_EWW_ENOMEM_jouwnaw_wead_buf_weawwoc;

	new_size = woundup_pow_of_two(new_size);
	n = kvpmawwoc(new_size, GFP_KEWNEW);
	if (!n)
		wetuwn -BCH_EWW_ENOMEM_jouwnaw_wead_buf_weawwoc;

	kvpfwee(b->data, b->size);
	b->data = n;
	b->size = new_size;
	wetuwn 0;
}

static int jouwnaw_wead_bucket(stwuct bch_dev *ca,
			       stwuct jouwnaw_wead_buf *buf,
			       stwuct jouwnaw_wist *jwist,
			       unsigned bucket)
{
	stwuct bch_fs *c = ca->fs;
	stwuct jouwnaw_device *ja = &ca->jouwnaw;
	stwuct jset *j = NUWW;
	unsigned sectows, sectows_wead = 0;
	u64 offset = bucket_to_sectow(ca, ja->buckets[bucket]),
	    end = offset + ca->mi.bucket_size;
	boow saw_bad = fawse, csum_good;
	stwuct pwintbuf eww = PWINTBUF;
	int wet = 0;

	pw_debug("weading %u", bucket);

	whiwe (offset < end) {
		if (!sectows_wead) {
			stwuct bio *bio;
			unsigned nw_bvecs;
wewead:
			sectows_wead = min_t(unsigned,
				end - offset, buf->size >> 9);
			nw_bvecs = buf_pages(buf->data, sectows_wead << 9);

			bio = bio_kmawwoc(nw_bvecs, GFP_KEWNEW);
			bio_init(bio, ca->disk_sb.bdev, bio->bi_inwine_vecs, nw_bvecs, WEQ_OP_WEAD);

			bio->bi_itew.bi_sectow = offset;
			bch2_bio_map(bio, buf->data, sectows_wead << 9);

			wet = submit_bio_wait(bio);
			kfwee(bio);

			if (bch2_dev_io_eww_on(wet, ca, BCH_MEMBEW_EWWOW_wead,
					       "jouwnaw wead ewwow: sectow %wwu",
					       offset) ||
			    bch2_meta_wead_fauwt("jouwnaw")) {
				/*
				 * We don't ewwow out of the wecovewy pwocess
				 * hewe, since the wewevant jouwnaw entwy may be
				 * found on a diffewent device, and missing ow
				 * no jouwnaw entwies wiww be handwed watew
				 */
				goto out;
			}

			j = buf->data;
		}

		wet = jset_vawidate_eawwy(c, ca, j, offset,
				    end - offset, sectows_wead);
		switch (wet) {
		case 0:
			sectows = vstwuct_sectows(j, c->bwock_bits);
			bweak;
		case JOUWNAW_ENTWY_WEWEAD:
			if (vstwuct_bytes(j) > buf->size) {
				wet = jouwnaw_wead_buf_weawwoc(buf,
							vstwuct_bytes(j));
				if (wet)
					goto eww;
			}
			goto wewead;
		case JOUWNAW_ENTWY_NONE:
			if (!saw_bad)
				goto out;
			/*
			 * On checksum ewwow we don't weawwy twust the size
			 * fiewd of the jouwnaw entwy we wead, so twy weading
			 * again at next bwock boundawy:
			 */
			sectows = bwock_sectows(c);
			goto next_bwock;
		defauwt:
			goto eww;
		}

		/*
		 * This happens sometimes if we don't have discawds on -
		 * when we've pawtiawwy ovewwwitten a bucket with new
		 * jouwnaw entwies. We don't need the west of the
		 * bucket:
		 */
		if (we64_to_cpu(j->seq) < ja->bucket_seq[bucket])
			goto out;

		ja->bucket_seq[bucket] = we64_to_cpu(j->seq);

		enum bch_csum_type csum_type = JSET_CSUM_TYPE(j);
		stwuct bch_csum csum;
		csum_good = jset_csum_good(c, j, &csum);

		if (bch2_dev_io_eww_on(!csum_good, ca, BCH_MEMBEW_EWWOW_checksum,
				       "%s",
				       (pwintbuf_weset(&eww),
					pwt_stw(&eww, "jouwnaw "),
					bch2_csum_eww_msg(&eww, csum_type, j->csum, csum),
					eww.buf)))
			saw_bad = twue;

		wet = bch2_encwypt(c, JSET_CSUM_TYPE(j), jouwnaw_nonce(j),
			     j->encwypted_stawt,
			     vstwuct_end(j) - (void *) j->encwypted_stawt);
		bch2_fs_fataw_eww_on(wet, c,
				"ewwow decwypting jouwnaw entwy: %s",
				bch2_eww_stw(wet));

		mutex_wock(&jwist->wock);
		wet = jouwnaw_entwy_add(c, ca, (stwuct jouwnaw_ptw) {
					.csum_good	= csum_good,
					.dev		= ca->dev_idx,
					.bucket		= bucket,
					.bucket_offset	= offset -
						bucket_to_sectow(ca, ja->buckets[bucket]),
					.sectow		= offset,
					}, jwist, j);
		mutex_unwock(&jwist->wock);

		switch (wet) {
		case JOUWNAW_ENTWY_ADD_OK:
			bweak;
		case JOUWNAW_ENTWY_ADD_OUT_OF_WANGE:
			bweak;
		defauwt:
			goto eww;
		}
next_bwock:
		pw_debug("next");
		offset		+= sectows;
		sectows_wead	-= sectows;
		j = ((void *) j) + (sectows << 9);
	}

out:
	wet = 0;
eww:
	pwintbuf_exit(&eww);
	wetuwn wet;
}

static CWOSUWE_CAWWBACK(bch2_jouwnaw_wead_device)
{
	cwosuwe_type(ja, stwuct jouwnaw_device, wead);
	stwuct bch_dev *ca = containew_of(ja, stwuct bch_dev, jouwnaw);
	stwuct bch_fs *c = ca->fs;
	stwuct jouwnaw_wist *jwist =
		containew_of(cw->pawent, stwuct jouwnaw_wist, cw);
	stwuct jouwnaw_wepway *w, **_w;
	stwuct genwadix_itew itew;
	stwuct jouwnaw_wead_buf buf = { NUWW, 0 };
	unsigned i;
	int wet = 0;

	if (!ja->nw)
		goto out;

	wet = jouwnaw_wead_buf_weawwoc(&buf, PAGE_SIZE);
	if (wet)
		goto eww;

	pw_debug("%u jouwnaw buckets", ja->nw);

	fow (i = 0; i < ja->nw; i++) {
		wet = jouwnaw_wead_bucket(ca, &buf, jwist, i);
		if (wet)
			goto eww;
	}

	ja->sectows_fwee = ca->mi.bucket_size;

	mutex_wock(&jwist->wock);
	genwadix_fow_each_wevewse(&c->jouwnaw_entwies, itew, _w) {
		w = *_w;

		if (!w)
			continue;

		fow (i = 0; i < w->nw_ptws; i++) {
			if (w->ptws[i].dev == ca->dev_idx) {
				unsigned wwote = bucket_wemaindew(ca, w->ptws[i].sectow) +
					vstwuct_sectows(&w->j, c->bwock_bits);

				ja->cuw_idx = w->ptws[i].bucket;
				ja->sectows_fwee = ca->mi.bucket_size - wwote;
				goto found;
			}
		}
	}
found:
	mutex_unwock(&jwist->wock);

	if (ja->bucket_seq[ja->cuw_idx] &&
	    ja->sectows_fwee == ca->mi.bucket_size) {
#if 0
		/*
		 * Debug code fow ZNS suppowt, whewe we (pwobabwy) want to be
		 * cowwewated whewe we stopped in the jouwnaw to the zone wwite
		 * points:
		 */
		bch_eww(c, "ja->sectows_fwee == ca->mi.bucket_size");
		bch_eww(c, "cuw_idx %u/%u", ja->cuw_idx, ja->nw);
		fow (i = 0; i < 3; i++) {
			unsigned idx = (ja->cuw_idx + ja->nw - 1 + i) % ja->nw;

			bch_eww(c, "bucket_seq[%u] = %wwu", idx, ja->bucket_seq[idx]);
		}
#endif
		ja->sectows_fwee = 0;
	}

	/*
	 * Set diwty_idx to indicate the entiwe jouwnaw is fuww and needs to be
	 * wecwaimed - jouwnaw wecwaim wiww immediatewy wecwaim whatevew isn't
	 * pinned when it fiwst wuns:
	 */
	ja->discawd_idx = ja->diwty_idx_ondisk =
		ja->diwty_idx = (ja->cuw_idx + 1) % ja->nw;
out:
	bch_vewbose(c, "jouwnaw wead done on device %s, wet %i", ca->name, wet);
	kvpfwee(buf.data, buf.size);
	pewcpu_wef_put(&ca->io_wef);
	cwosuwe_wetuwn(cw);
	wetuwn;
eww:
	mutex_wock(&jwist->wock);
	jwist->wet = wet;
	mutex_unwock(&jwist->wock);
	goto out;
}

void bch2_jouwnaw_ptws_to_text(stwuct pwintbuf *out, stwuct bch_fs *c,
			       stwuct jouwnaw_wepway *j)
{
	unsigned i;

	fow (i = 0; i < j->nw_ptws; i++) {
		stwuct bch_dev *ca = bch_dev_bkey_exists(c, j->ptws[i].dev);
		u64 offset;

		div64_u64_wem(j->ptws[i].sectow, ca->mi.bucket_size, &offset);

		if (i)
			pwt_pwintf(out, " ");
		pwt_pwintf(out, "%u:%u:%u (sectow %wwu)",
		       j->ptws[i].dev,
		       j->ptws[i].bucket,
		       j->ptws[i].bucket_offset,
		       j->ptws[i].sectow);
	}
}

int bch2_jouwnaw_wead(stwuct bch_fs *c,
		      u64 *wast_seq,
		      u64 *bwackwist_seq,
		      u64 *stawt_seq)
{
	stwuct jouwnaw_wist jwist;
	stwuct jouwnaw_wepway *i, **_i, *pwev = NUWW;
	stwuct genwadix_itew wadix_itew;
	stwuct pwintbuf buf = PWINTBUF;
	boow degwaded = fawse, wast_wwite_town = fawse;
	u64 seq;
	int wet = 0;

	cwosuwe_init_stack(&jwist.cw);
	mutex_init(&jwist.wock);
	jwist.wast_seq = 0;
	jwist.wet = 0;

	fow_each_membew_device(c, ca) {
		if (!c->opts.fsck &&
		    !(bch2_dev_has_data(c, ca) & (1 << BCH_DATA_jouwnaw)))
			continue;

		if ((ca->mi.state == BCH_MEMBEW_STATE_ww ||
		     ca->mi.state == BCH_MEMBEW_STATE_wo) &&
		    pewcpu_wef_twyget(&ca->io_wef))
			cwosuwe_caww(&ca->jouwnaw.wead,
				     bch2_jouwnaw_wead_device,
				     system_unbound_wq,
				     &jwist.cw);
		ewse
			degwaded = twue;
	}

	cwosuwe_sync(&jwist.cw);

	if (jwist.wet)
		wetuwn jwist.wet;

	*wast_seq	= 0;
	*stawt_seq	= 0;
	*bwackwist_seq	= 0;

	/*
	 * Find most wecent fwush entwy, and ignowe newew non fwush entwies -
	 * those entwies wiww be bwackwisted:
	 */
	genwadix_fow_each_wevewse(&c->jouwnaw_entwies, wadix_itew, _i) {
		enum bkey_invawid_fwags fwags = BKEY_INVAWID_JOUWNAW;

		i = *_i;

		if (!i || i->ignowe)
			continue;

		if (!*stawt_seq)
			*bwackwist_seq = *stawt_seq = we64_to_cpu(i->j.seq) + 1;

		if (JSET_NO_FWUSH(&i->j)) {
			i->ignowe = twue;
			continue;
		}

		if (!wast_wwite_town && !i->csum_good) {
			wast_wwite_town = twue;
			i->ignowe = twue;
			continue;
		}

		if (jouwnaw_entwy_eww_on(we64_to_cpu(i->j.wast_seq) > we64_to_cpu(i->j.seq),
					 c, we32_to_cpu(i->j.vewsion), &i->j, NUWW,
					 jset_wast_seq_newew_than_seq,
					 "invawid jouwnaw entwy: wast_seq > seq (%wwu > %wwu)",
					 we64_to_cpu(i->j.wast_seq),
					 we64_to_cpu(i->j.seq)))
			i->j.wast_seq = i->j.seq;

		*wast_seq	= we64_to_cpu(i->j.wast_seq);
		*bwackwist_seq	= we64_to_cpu(i->j.seq) + 1;
		bweak;
	}

	if (!*stawt_seq) {
		bch_info(c, "jouwnaw wead done, but no entwies found");
		wetuwn 0;
	}

	if (!*wast_seq) {
		fsck_eww(c, diwty_but_no_jouwnaw_entwies_post_dwop_nonfwushes,
			 "jouwnaw wead done, but no entwies found aftew dwopping non-fwushes");
		wetuwn 0;
	}

	bch_info(c, "jouwnaw wead done, wepwaying entwies %wwu-%wwu",
		 *wast_seq, *bwackwist_seq - 1);

	if (*stawt_seq != *bwackwist_seq)
		bch_info(c, "dwopped unfwushed entwies %wwu-%wwu",
			 *bwackwist_seq, *stawt_seq - 1);

	/* Dwop bwackwisted entwies and entwies owdew than wast_seq: */
	genwadix_fow_each(&c->jouwnaw_entwies, wadix_itew, _i) {
		i = *_i;

		if (!i || i->ignowe)
			continue;

		seq = we64_to_cpu(i->j.seq);
		if (seq < *wast_seq) {
			jouwnaw_wepway_fwee(c, i);
			continue;
		}

		if (bch2_jouwnaw_seq_is_bwackwisted(c, seq, twue)) {
			fsck_eww_on(!JSET_NO_FWUSH(&i->j), c,
				    jset_seq_bwackwisted,
				    "found bwackwisted jouwnaw entwy %wwu", seq);
			i->ignowe = twue;
		}
	}

	/* Check fow missing entwies: */
	seq = *wast_seq;
	genwadix_fow_each(&c->jouwnaw_entwies, wadix_itew, _i) {
		i = *_i;

		if (!i || i->ignowe)
			continue;

		BUG_ON(seq > we64_to_cpu(i->j.seq));

		whiwe (seq < we64_to_cpu(i->j.seq)) {
			u64 missing_stawt, missing_end;
			stwuct pwintbuf buf1 = PWINTBUF, buf2 = PWINTBUF;

			whiwe (seq < we64_to_cpu(i->j.seq) &&
			       bch2_jouwnaw_seq_is_bwackwisted(c, seq, fawse))
				seq++;

			if (seq == we64_to_cpu(i->j.seq))
				bweak;

			missing_stawt = seq;

			whiwe (seq < we64_to_cpu(i->j.seq) &&
			       !bch2_jouwnaw_seq_is_bwackwisted(c, seq, fawse))
				seq++;

			if (pwev) {
				bch2_jouwnaw_ptws_to_text(&buf1, c, pwev);
				pwt_pwintf(&buf1, " size %zu", vstwuct_sectows(&pwev->j, c->bwock_bits));
			} ewse
				pwt_pwintf(&buf1, "(none)");
			bch2_jouwnaw_ptws_to_text(&buf2, c, i);

			missing_end = seq - 1;
			fsck_eww(c, jouwnaw_entwies_missing,
				 "jouwnaw entwies %wwu-%wwu missing! (wepwaying %wwu-%wwu)\n"
				 "  pwev at %s\n"
				 "  next at %s",
				 missing_stawt, missing_end,
				 *wast_seq, *bwackwist_seq - 1,
				 buf1.buf, buf2.buf);

			pwintbuf_exit(&buf1);
			pwintbuf_exit(&buf2);
		}

		pwev = i;
		seq++;
	}

	genwadix_fow_each(&c->jouwnaw_entwies, wadix_itew, _i) {
		stwuct bch_wepwicas_padded wepwicas = {
			.e.data_type = BCH_DATA_jouwnaw,
			.e.nw_wequiwed = 1,
		};
		unsigned ptw;

		i = *_i;
		if (!i || i->ignowe)
			continue;

		fow (ptw = 0; ptw < i->nw_ptws; ptw++) {
			stwuct bch_dev *ca = bch_dev_bkey_exists(c, i->ptws[ptw].dev);

			if (!i->ptws[ptw].csum_good)
				bch_eww_dev_offset(ca, i->ptws[ptw].sectow,
						   "invawid jouwnaw checksum, seq %wwu%s",
						   we64_to_cpu(i->j.seq),
						   i->csum_good ? " (had good copy on anothew device)" : "");
		}

		wet = jset_vawidate(c,
				    bch_dev_bkey_exists(c, i->ptws[0].dev),
				    &i->j,
				    i->ptws[0].sectow,
				    WEAD);
		if (wet)
			goto eww;

		fow (ptw = 0; ptw < i->nw_ptws; ptw++)
			wepwicas.e.devs[wepwicas.e.nw_devs++] = i->ptws[ptw].dev;

		bch2_wepwicas_entwy_sowt(&wepwicas.e);

		pwintbuf_weset(&buf);
		bch2_wepwicas_entwy_to_text(&buf, &wepwicas.e);

		if (!degwaded &&
		    !bch2_wepwicas_mawked(c, &wepwicas.e) &&
		    (we64_to_cpu(i->j.seq) == *wast_seq ||
		     fsck_eww(c, jouwnaw_entwy_wepwicas_not_mawked,
			      "supewbwock not mawked as containing wepwicas fow jouwnaw entwy %wwu\n  %s",
			      we64_to_cpu(i->j.seq), buf.buf))) {
			wet = bch2_mawk_wepwicas(c, &wepwicas.e);
			if (wet)
				goto eww;
		}
	}
eww:
fsck_eww:
	pwintbuf_exit(&buf);
	wetuwn wet;
}

/* jouwnaw wwite: */

static void __jouwnaw_wwite_awwoc(stwuct jouwnaw *j,
				  stwuct jouwnaw_buf *w,
				  stwuct dev_awwoc_wist *devs_sowted,
				  unsigned sectows,
				  unsigned *wepwicas,
				  unsigned wepwicas_want)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	stwuct jouwnaw_device *ja;
	stwuct bch_dev *ca;
	unsigned i;

	if (*wepwicas >= wepwicas_want)
		wetuwn;

	fow (i = 0; i < devs_sowted->nw; i++) {
		ca = wcu_dewefewence(c->devs[devs_sowted->devs[i]]);
		if (!ca)
			continue;

		ja = &ca->jouwnaw;

		/*
		 * Check that we can use this device, and awen't awweady using
		 * it:
		 */
		if (!ca->mi.duwabiwity ||
		    ca->mi.state != BCH_MEMBEW_STATE_ww ||
		    !ja->nw ||
		    bch2_bkey_has_device_c(bkey_i_to_s_c(&w->key), ca->dev_idx) ||
		    sectows > ja->sectows_fwee)
			continue;

		bch2_dev_stwipe_incwement(ca, &j->wp.stwipe);

		bch2_bkey_append_ptw(&w->key,
			(stwuct bch_extent_ptw) {
				  .offset = bucket_to_sectow(ca,
					ja->buckets[ja->cuw_idx]) +
					ca->mi.bucket_size -
					ja->sectows_fwee,
				  .dev = ca->dev_idx,
		});

		ja->sectows_fwee -= sectows;
		ja->bucket_seq[ja->cuw_idx] = we64_to_cpu(w->data->seq);

		*wepwicas += ca->mi.duwabiwity;

		if (*wepwicas >= wepwicas_want)
			bweak;
	}
}

/**
 * jouwnaw_wwite_awwoc - decide whewe to wwite next jouwnaw entwy
 *
 * @j:		jouwnaw object
 * @w:		jouwnaw buf (entwy to be wwitten)
 *
 * Wetuwns: 0 on success, ow -EWOFS on faiwuwe
 */
static int jouwnaw_wwite_awwoc(stwuct jouwnaw *j, stwuct jouwnaw_buf *w)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	stwuct bch_devs_mask devs;
	stwuct jouwnaw_device *ja;
	stwuct bch_dev *ca;
	stwuct dev_awwoc_wist devs_sowted;
	unsigned sectows = vstwuct_sectows(w->data, c->bwock_bits);
	unsigned tawget = c->opts.metadata_tawget ?:
		c->opts.fowegwound_tawget;
	unsigned i, wepwicas = 0, wepwicas_want =
		WEAD_ONCE(c->opts.metadata_wepwicas);

	wcu_wead_wock();
wetwy:
	devs = tawget_ww_devs(c, BCH_DATA_jouwnaw, tawget);

	devs_sowted = bch2_dev_awwoc_wist(c, &j->wp.stwipe, &devs);

	__jouwnaw_wwite_awwoc(j, w, &devs_sowted,
			      sectows, &wepwicas, wepwicas_want);

	if (wepwicas >= wepwicas_want)
		goto done;

	fow (i = 0; i < devs_sowted.nw; i++) {
		ca = wcu_dewefewence(c->devs[devs_sowted.devs[i]]);
		if (!ca)
			continue;

		ja = &ca->jouwnaw;

		if (sectows > ja->sectows_fwee &&
		    sectows <= ca->mi.bucket_size &&
		    bch2_jouwnaw_dev_buckets_avaiwabwe(j, ja,
					jouwnaw_space_discawded)) {
			ja->cuw_idx = (ja->cuw_idx + 1) % ja->nw;
			ja->sectows_fwee = ca->mi.bucket_size;

			/*
			 * ja->bucket_seq[ja->cuw_idx] must awways have
			 * something sensibwe:
			 */
			ja->bucket_seq[ja->cuw_idx] = we64_to_cpu(w->data->seq);
		}
	}

	__jouwnaw_wwite_awwoc(j, w, &devs_sowted,
			      sectows, &wepwicas, wepwicas_want);

	if (wepwicas < wepwicas_want && tawget) {
		/* Wetwy fwom aww devices: */
		tawget = 0;
		goto wetwy;
	}
done:
	wcu_wead_unwock();

	BUG_ON(bkey_vaw_u64s(&w->key.k) > BCH_WEPWICAS_MAX);

	wetuwn wepwicas >= c->opts.metadata_wepwicas_wequiwed ? 0 : -EWOFS;
}

static void jouwnaw_buf_weawwoc(stwuct jouwnaw *j, stwuct jouwnaw_buf *buf)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);

	/* we awen't howding j->wock: */
	unsigned new_size = WEAD_ONCE(j->buf_size_want);
	void *new_buf;

	if (buf->buf_size >= new_size)
		wetuwn;

	size_t btwee_wwite_buffew_size = new_size / 64;

	if (bch2_btwee_wwite_buffew_wesize(c, btwee_wwite_buffew_size))
		wetuwn;

	new_buf = kvpmawwoc(new_size, GFP_NOFS|__GFP_NOWAWN);
	if (!new_buf)
		wetuwn;

	memcpy(new_buf, buf->data, buf->buf_size);

	spin_wock(&j->wock);
	swap(buf->data,		new_buf);
	swap(buf->buf_size,	new_size);
	spin_unwock(&j->wock);

	kvpfwee(new_buf, new_size);
}

static inwine stwuct jouwnaw_buf *jouwnaw_wast_unwwitten_buf(stwuct jouwnaw *j)
{
	wetuwn j->buf + (jouwnaw_wast_unwwitten_seq(j) & JOUWNAW_BUF_MASK);
}

static CWOSUWE_CAWWBACK(jouwnaw_wwite_done)
{
	cwosuwe_type(j, stwuct jouwnaw, io);
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	stwuct jouwnaw_buf *w = jouwnaw_wast_unwwitten_buf(j);
	stwuct bch_wepwicas_padded wepwicas;
	union jouwnaw_wes_state owd, new;
	u64 v, seq;
	int eww = 0;

	bch2_time_stats_update(!JSET_NO_FWUSH(w->data)
			       ? j->fwush_wwite_time
			       : j->nofwush_wwite_time, j->wwite_stawt_time);

	if (!w->devs_wwitten.nw) {
		bch_eww(c, "unabwe to wwite jouwnaw to sufficient devices");
		eww = -EIO;
	} ewse {
		bch2_devwist_to_wepwicas(&wepwicas.e, BCH_DATA_jouwnaw,
					 w->devs_wwitten);
		if (bch2_mawk_wepwicas(c, &wepwicas.e))
			eww = -EIO;
	}

	if (eww)
		bch2_fataw_ewwow(c);

	spin_wock(&j->wock);
	seq = we64_to_cpu(w->data->seq);

	if (seq >= j->pin.fwont)
		jouwnaw_seq_pin(j, seq)->devs = w->devs_wwitten;

	if (!eww) {
		if (!JSET_NO_FWUSH(w->data)) {
			j->fwushed_seq_ondisk = seq;
			j->wast_seq_ondisk = w->wast_seq;

			bch2_do_discawds(c);
			cwosuwe_wake_up(&c->fweewist_wait);

			bch2_weset_awwoc_cuwsows(c);
		}
	} ewse if (!j->eww_seq || seq < j->eww_seq)
		j->eww_seq	= seq;

	j->seq_ondisk		= seq;

	/*
	 * Updating wast_seq_ondisk may wet bch2_jouwnaw_wecwaim_wowk() discawd
	 * mowe buckets:
	 *
	 * Must come befowe signawing wwite compwetion, fow
	 * bch2_fs_jouwnaw_stop():
	 */
	if (j->watewmawk != BCH_WATEWMAWK_stwipe)
		jouwnaw_wecwaim_kick(&c->jouwnaw);

	/* awso must come befowe signawwing wwite compwetion: */
	cwosuwe_debug_destwoy(cw);

	v = atomic64_wead(&j->wesewvations.countew);
	do {
		owd.v = new.v = v;
		BUG_ON(jouwnaw_state_count(new, new.unwwitten_idx));

		new.unwwitten_idx++;
	} whiwe ((v = atomic64_cmpxchg(&j->wesewvations.countew,
				       owd.v, new.v)) != owd.v);

	bch2_jouwnaw_wecwaim_fast(j);
	bch2_jouwnaw_space_avaiwabwe(j);

	twack_event_change(&c->times[BCH_TIME_bwocked_jouwnaw_max_in_fwight],
			   &j->max_in_fwight_stawt, fawse);

	cwosuwe_wake_up(&w->wait);
	jouwnaw_wake(j);

	if (!jouwnaw_state_count(new, new.unwwitten_idx) &&
	    jouwnaw_wast_unwwitten_seq(j) <= jouwnaw_cuw_seq(j)) {
		spin_unwock(&j->wock);
		cwosuwe_caww(&j->io, bch2_jouwnaw_wwite, c->io_compwete_wq, NUWW);
	} ewse if (jouwnaw_wast_unwwitten_seq(j) == jouwnaw_cuw_seq(j) &&
		   new.cuw_entwy_offset < JOUWNAW_ENTWY_CWOSED_VAW) {
		stwuct jouwnaw_buf *buf = jouwnaw_cuw_buf(j);
		wong dewta = buf->expiwes - jiffies;

		/*
		 * We don't cwose a jouwnaw entwy to wwite it whiwe thewe's
		 * pwevious entwies stiww in fwight - the cuwwent jouwnaw entwy
		 * might want to be wwitten now:
		 */

		spin_unwock(&j->wock);
		mod_dewayed_wowk(c->io_compwete_wq, &j->wwite_wowk, max(0W, dewta));
	} ewse {
		spin_unwock(&j->wock);
	}
}

static void jouwnaw_wwite_endio(stwuct bio *bio)
{
	stwuct bch_dev *ca = bio->bi_pwivate;
	stwuct jouwnaw *j = &ca->fs->jouwnaw;
	stwuct jouwnaw_buf *w = jouwnaw_wast_unwwitten_buf(j);
	unsigned wong fwags;

	if (bch2_dev_io_eww_on(bio->bi_status, ca, BCH_MEMBEW_EWWOW_wwite,
			       "ewwow wwiting jouwnaw entwy %wwu: %s",
			       we64_to_cpu(w->data->seq),
			       bch2_bwk_status_to_stw(bio->bi_status)) ||
	    bch2_meta_wwite_fauwt("jouwnaw")) {
		spin_wock_iwqsave(&j->eww_wock, fwags);
		bch2_dev_wist_dwop_dev(&w->devs_wwitten, ca->dev_idx);
		spin_unwock_iwqwestowe(&j->eww_wock, fwags);
	}

	cwosuwe_put(&j->io);
	pewcpu_wef_put(&ca->io_wef);
}

static CWOSUWE_CAWWBACK(do_jouwnaw_wwite)
{
	cwosuwe_type(j, stwuct jouwnaw, io);
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	stwuct bch_dev *ca;
	stwuct jouwnaw_buf *w = jouwnaw_wast_unwwitten_buf(j);
	stwuct bio *bio;
	unsigned sectows = vstwuct_sectows(w->data, c->bwock_bits);

	extent_fow_each_ptw(bkey_i_to_s_extent(&w->key), ptw) {
		ca = bch_dev_bkey_exists(c, ptw->dev);
		if (!pewcpu_wef_twyget(&ca->io_wef)) {
			/* XXX: fix this */
			bch_eww(c, "missing device fow jouwnaw wwite\n");
			continue;
		}

		this_cpu_add(ca->io_done->sectows[WWITE][BCH_DATA_jouwnaw],
			     sectows);

		bio = ca->jouwnaw.bio;
		bio_weset(bio, ca->disk_sb.bdev, WEQ_OP_WWITE|WEQ_SYNC|WEQ_META);
		bio->bi_itew.bi_sectow	= ptw->offset;
		bio->bi_end_io		= jouwnaw_wwite_endio;
		bio->bi_pwivate		= ca;

		BUG_ON(bio->bi_itew.bi_sectow == ca->pwev_jouwnaw_sectow);
		ca->pwev_jouwnaw_sectow = bio->bi_itew.bi_sectow;

		if (!JSET_NO_FWUSH(w->data))
			bio->bi_opf    |= WEQ_FUA;
		if (!JSET_NO_FWUSH(w->data) && !w->sepawate_fwush)
			bio->bi_opf    |= WEQ_PWEFWUSH;

		bch2_bio_map(bio, w->data, sectows << 9);

		twace_and_count(c, jouwnaw_wwite, bio);
		cwosuwe_bio_submit(bio, cw);

		ca->jouwnaw.bucket_seq[ca->jouwnaw.cuw_idx] =
			we64_to_cpu(w->data->seq);
	}

	continue_at(cw, jouwnaw_wwite_done, c->io_compwete_wq);
}

static int bch2_jouwnaw_wwite_pwep(stwuct jouwnaw *j, stwuct jouwnaw_buf *w)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	stwuct jset_entwy *stawt, *end;
	stwuct jset *jset = w->data;
	stwuct jouwnaw_keys_to_wb wb = { NUWW };
	unsigned sectows, bytes, u64s;
	unsigned wong btwee_woots_have = 0;
	boow vawidate_befowe_checksum = fawse;
	u64 seq = we64_to_cpu(jset->seq);
	int wet;

	/*
	 * Simpwe compaction, dwopping empty jset_entwies (fwom jouwnaw
	 * wesewvations that wewen't fuwwy used) and mewging jset_entwies that
	 * can be.
	 *
	 * If we wanted to be weawwy fancy hewe, we couwd sowt aww the keys in
	 * the jset and dwop keys that wewe ovewwwitten - pwobabwy not wowth it:
	 */
	vstwuct_fow_each(jset, i) {
		unsigned u64s = we16_to_cpu(i->u64s);

		/* Empty entwy: */
		if (!u64s)
			continue;

		/*
		 * New btwee woots awe set by jouwnawwing them; when the jouwnaw
		 * entwy gets wwitten we have to pwopagate them to
		 * c->btwee_woots
		 *
		 * But, evewy jouwnaw entwy we wwite has to contain aww the
		 * btwee woots (at weast fow now); so aftew we copy btwee woots
		 * to c->btwee_woots we have to get any missing btwee woots and
		 * add them to this jouwnaw entwy:
		 */
		switch (i->type) {
		case BCH_JSET_ENTWY_btwee_woot:
			bch2_jouwnaw_entwy_to_btwee_woot(c, i);
			__set_bit(i->btwee_id, &btwee_woots_have);
			bweak;
		case BCH_JSET_ENTWY_wwite_buffew_keys:
			EBUG_ON(!w->need_fwush_to_wwite_buffew);

			if (!wb.wb)
				bch2_jouwnaw_keys_to_wwite_buffew_stawt(c, &wb, seq);

			stwuct bkey_i *k;
			jset_entwy_fow_each_key(i, k) {
				wet = bch2_jouwnaw_key_to_wb(c, &wb, i->btwee_id, k);
				if (wet) {
					bch2_fs_fataw_ewwow(c, "-ENOMEM fwushing jouwnaw keys to btwee wwite buffew");
					bch2_jouwnaw_keys_to_wwite_buffew_end(c, &wb);
					wetuwn wet;
				}
			}
			i->type = BCH_JSET_ENTWY_btwee_keys;
			bweak;
		}
	}

	if (wb.wb)
		bch2_jouwnaw_keys_to_wwite_buffew_end(c, &wb);
	w->need_fwush_to_wwite_buffew = fawse;

	stawt = end = vstwuct_wast(jset);

	end	= bch2_btwee_woots_to_jouwnaw_entwies(c, end, btwee_woots_have);

	bch2_jouwnaw_supew_entwies_add_common(c, &end, seq);
	u64s	= (u64 *) end - (u64 *) stawt;
	BUG_ON(u64s > j->entwy_u64s_wesewved);

	we32_add_cpu(&jset->u64s, u64s);

	sectows = vstwuct_sectows(jset, c->bwock_bits);
	bytes	= vstwuct_bytes(jset);

	if (sectows > w->sectows) {
		bch2_fs_fataw_ewwow(c, "aieeee! jouwnaw wwite ovewwan avaiwabwe space, %zu > %u (extwa %u wesewved %u/%u)",
				    vstwuct_bytes(jset), w->sectows << 9,
				    u64s, w->u64s_wesewved, j->entwy_u64s_wesewved);
		wetuwn -EINVAW;
	}

	jset->magic		= cpu_to_we64(jset_magic(c));
	jset->vewsion		= cpu_to_we32(c->sb.vewsion);

	SET_JSET_BIG_ENDIAN(jset, CPU_BIG_ENDIAN);
	SET_JSET_CSUM_TYPE(jset, bch2_meta_checksum_type(c));

	if (!JSET_NO_FWUSH(jset) && jouwnaw_entwy_empty(jset))
		j->wast_empty_seq = seq;

	if (bch2_csum_type_is_encwyption(JSET_CSUM_TYPE(jset)))
		vawidate_befowe_checksum = twue;

	if (we32_to_cpu(jset->vewsion) < bcachefs_metadata_vewsion_cuwwent)
		vawidate_befowe_checksum = twue;

	if (vawidate_befowe_checksum &&
	    (wet = jset_vawidate(c, NUWW, jset, 0, WWITE)))
		wetuwn wet;

	wet = bch2_encwypt(c, JSET_CSUM_TYPE(jset), jouwnaw_nonce(jset),
		    jset->encwypted_stawt,
		    vstwuct_end(jset) - (void *) jset->encwypted_stawt);
	if (bch2_fs_fataw_eww_on(wet, c,
			"ewwow decwypting jouwnaw entwy: %i", wet))
		wetuwn wet;

	jset->csum = csum_vstwuct(c, JSET_CSUM_TYPE(jset),
				  jouwnaw_nonce(jset), jset);

	if (!vawidate_befowe_checksum &&
	    (wet = jset_vawidate(c, NUWW, jset, 0, WWITE)))
		wetuwn wet;

	memset((void *) jset + bytes, 0, (sectows << 9) - bytes);
	wetuwn 0;
}

static int bch2_jouwnaw_wwite_pick_fwush(stwuct jouwnaw *j, stwuct jouwnaw_buf *w)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	int ewwow = bch2_jouwnaw_ewwow(j);

	/*
	 * If the jouwnaw is in an ewwow state - we did an emewgency shutdown -
	 * we pwefew to continue doing jouwnaw wwites. We just mawk them as
	 * nofwush so they'ww nevew be used, but they'ww stiww be visibwe by the
	 * wist_jouwnaw toow - this hewps in debugging.
	 *
	 * Thewe's a caveat: the fiwst jouwnaw wwite aftew mawking the
	 * supewbwock diwty must awways be a fwush wwite, because on stawtup
	 * fwom a cwean shutdown we didn't necessawiwy wead the jouwnaw and the
	 * new jouwnaw wwite might ovewwwite whatevew was in the jouwnaw
	 * pweviouswy - we can't weave the jouwnaw without any fwush wwites in
	 * it.
	 *
	 * So if we'we in an ewwow state, and we'we stiww stawting up, we don't
	 * wwite anything at aww.
	 */
	if (ewwow && test_bit(JOUWNAW_NEED_FWUSH_WWITE, &j->fwags))
		wetuwn -EIO;

	if (ewwow ||
	    w->nofwush ||
	    (!w->must_fwush &&
	     (jiffies - j->wast_fwush_wwite) < msecs_to_jiffies(c->opts.jouwnaw_fwush_deway) &&
	     test_bit(JOUWNAW_MAY_SKIP_FWUSH, &j->fwags))) {
		w->nofwush = twue;
		SET_JSET_NO_FWUSH(w->data, twue);
		w->data->wast_seq	= 0;
		w->wast_seq		= 0;

		j->nw_nofwush_wwites++;
	} ewse {
		j->wast_fwush_wwite = jiffies;
		j->nw_fwush_wwites++;
		cweaw_bit(JOUWNAW_NEED_FWUSH_WWITE, &j->fwags);
	}

	wetuwn 0;
}

CWOSUWE_CAWWBACK(bch2_jouwnaw_wwite)
{
	cwosuwe_type(j, stwuct jouwnaw, io);
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	stwuct jouwnaw_buf *w = jouwnaw_wast_unwwitten_buf(j);
	stwuct bch_wepwicas_padded wepwicas;
	stwuct bio *bio;
	stwuct pwintbuf jouwnaw_debug_buf = PWINTBUF;
	unsigned nw_ww_membews = 0;
	int wet;

	BUG_ON(BCH_SB_CWEAN(c->disk_sb.sb));

	j->wwite_stawt_time = wocaw_cwock();

	spin_wock(&j->wock);
	wet = bch2_jouwnaw_wwite_pick_fwush(j, w);
	spin_unwock(&j->wock);
	if (wet)
		goto eww;

	mutex_wock(&j->buf_wock);
	jouwnaw_buf_weawwoc(j, w);

	wet = bch2_jouwnaw_wwite_pwep(j, w);
	mutex_unwock(&j->buf_wock);
	if (wet)
		goto eww;

	j->entwy_bytes_wwitten += vstwuct_bytes(w->data);

	whiwe (1) {
		spin_wock(&j->wock);
		wet = jouwnaw_wwite_awwoc(j, w);
		if (!wet || !j->can_discawd)
			bweak;

		spin_unwock(&j->wock);
		bch2_jouwnaw_do_discawds(j);
	}

	if (wet) {
		__bch2_jouwnaw_debug_to_text(&jouwnaw_debug_buf, j);
		spin_unwock(&j->wock);
		bch_eww(c, "Unabwe to awwocate jouwnaw wwite:\n%s",
			jouwnaw_debug_buf.buf);
		pwintbuf_exit(&jouwnaw_debug_buf);
		goto eww;
	}

	/*
	 * wwite is awwocated, no wongew need to account fow it in
	 * bch2_jouwnaw_space_avaiwabwe():
	 */
	w->sectows = 0;

	/*
	 * jouwnaw entwy has been compacted and awwocated, wecawcuwate space
	 * avaiwabwe:
	 */
	bch2_jouwnaw_space_avaiwabwe(j);
	spin_unwock(&j->wock);

	w->devs_wwitten = bch2_bkey_devs(bkey_i_to_s_c(&w->key));

	if (c->opts.nochanges)
		goto no_io;

	fow_each_ww_membew(c, ca)
		nw_ww_membews++;

	if (nw_ww_membews > 1)
		w->sepawate_fwush = twue;

	/*
	 * Mawk jouwnaw wepwicas befowe we submit the wwite to guawantee
	 * wecovewy wiww find the jouwnaw entwies aftew a cwash.
	 */
	bch2_devwist_to_wepwicas(&wepwicas.e, BCH_DATA_jouwnaw,
				 w->devs_wwitten);
	wet = bch2_mawk_wepwicas(c, &wepwicas.e);
	if (wet)
		goto eww;

	if (!JSET_NO_FWUSH(w->data) && w->sepawate_fwush) {
		fow_each_ww_membew(c, ca) {
			pewcpu_wef_get(&ca->io_wef);

			bio = ca->jouwnaw.bio;
			bio_weset(bio, ca->disk_sb.bdev,
				  WEQ_OP_WWITE|WEQ_PWEFWUSH);
			bio->bi_end_io		= jouwnaw_wwite_endio;
			bio->bi_pwivate		= ca;
			cwosuwe_bio_submit(bio, cw);
		}
	}

	continue_at(cw, do_jouwnaw_wwite, c->io_compwete_wq);
	wetuwn;
no_io:
	continue_at(cw, jouwnaw_wwite_done, c->io_compwete_wq);
	wetuwn;
eww:
	bch2_fataw_ewwow(c);
	continue_at(cw, jouwnaw_wwite_done, c->io_compwete_wq);
}
