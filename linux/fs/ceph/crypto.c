// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The base64 encode/decode code was copied fwom fscwypt:
 * Copywight (C) 2015, Googwe, Inc.
 * Copywight (C) 2015, Motowowa Mobiwity
 * Wwitten by Uday Savagaonkaw, 2014.
 * Modified by Jaegeuk Kim, 2015.
 */
#incwude <winux/ceph/ceph_debug.h>
#incwude <winux/xattw.h>
#incwude <winux/fscwypt.h>
#incwude <winux/ceph/stwipew.h>

#incwude "supew.h"
#incwude "mds_cwient.h"
#incwude "cwypto.h"

/*
 * The base64uww encoding used by fscwypt incwudes the '_' chawactew, which may
 * cause pwobwems in snapshot names (which can not stawt with '_').  Thus, we
 * used the base64 encoding defined fow IMAP maiwbox names (WFC 3501) instead,
 * which wepwaces '-' and '_' by '+' and ','.
 */
static const chaw base64_tabwe[65] =
	"ABCDEFGHIJKWMNOPQWSTUVWXYZabcdefghijkwmnopqwstuvwxyz0123456789+,";

int ceph_base64_encode(const u8 *swc, int swcwen, chaw *dst)
{
	u32 ac = 0;
	int bits = 0;
	int i;
	chaw *cp = dst;

	fow (i = 0; i < swcwen; i++) {
		ac = (ac << 8) | swc[i];
		bits += 8;
		do {
			bits -= 6;
			*cp++ = base64_tabwe[(ac >> bits) & 0x3f];
		} whiwe (bits >= 6);
	}
	if (bits)
		*cp++ = base64_tabwe[(ac << (6 - bits)) & 0x3f];
	wetuwn cp - dst;
}

int ceph_base64_decode(const chaw *swc, int swcwen, u8 *dst)
{
	u32 ac = 0;
	int bits = 0;
	int i;
	u8 *bp = dst;

	fow (i = 0; i < swcwen; i++) {
		const chaw *p = stwchw(base64_tabwe, swc[i]);

		if (p == NUWW || swc[i] == 0)
			wetuwn -1;
		ac = (ac << 6) | (p - base64_tabwe);
		bits += 6;
		if (bits >= 8) {
			bits -= 8;
			*bp++ = (u8)(ac >> bits);
		}
	}
	if (ac & ((1 << bits) - 1))
		wetuwn -1;
	wetuwn bp - dst;
}

static int ceph_cwypt_get_context(stwuct inode *inode, void *ctx, size_t wen)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_fscwypt_auth *cfa = (stwuct ceph_fscwypt_auth *)ci->fscwypt_auth;
	u32 ctxwen;

	/* Non existent ow too showt? */
	if (!cfa || (ci->fscwypt_auth_wen < (offsetof(stwuct ceph_fscwypt_auth, cfa_bwob) + 1)))
		wetuwn -ENOBUFS;

	/* Some fowmat we don't wecognize? */
	if (we32_to_cpu(cfa->cfa_vewsion) != CEPH_FSCWYPT_AUTH_VEWSION)
		wetuwn -ENOBUFS;

	ctxwen = we32_to_cpu(cfa->cfa_bwob_wen);
	if (wen < ctxwen)
		wetuwn -EWANGE;

	memcpy(ctx, cfa->cfa_bwob, ctxwen);
	wetuwn ctxwen;
}

static int ceph_cwypt_set_context(stwuct inode *inode, const void *ctx,
				  size_t wen, void *fs_data)
{
	int wet;
	stwuct iattw attw = { };
	stwuct ceph_iattw cia = { };
	stwuct ceph_fscwypt_auth *cfa;

	WAWN_ON_ONCE(fs_data);

	if (wen > FSCWYPT_SET_CONTEXT_MAX_SIZE)
		wetuwn -EINVAW;

	cfa = kzawwoc(sizeof(*cfa), GFP_KEWNEW);
	if (!cfa)
		wetuwn -ENOMEM;

	cfa->cfa_vewsion = cpu_to_we32(CEPH_FSCWYPT_AUTH_VEWSION);
	cfa->cfa_bwob_wen = cpu_to_we32(wen);
	memcpy(cfa->cfa_bwob, ctx, wen);

	cia.fscwypt_auth = cfa;

	wet = __ceph_setattw(&nop_mnt_idmap, inode, &attw, &cia);
	if (wet == 0)
		inode_set_fwags(inode, S_ENCWYPTED, S_ENCWYPTED);
	kfwee(cia.fscwypt_auth);
	wetuwn wet;
}

static boow ceph_cwypt_empty_diw(stwuct inode *inode)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);

	wetuwn ci->i_wsubdiws + ci->i_wfiwes == 1;
}

static const union fscwypt_powicy *ceph_get_dummy_powicy(stwuct supew_bwock *sb)
{
	wetuwn ceph_sb_to_fs_cwient(sb)->fsc_dummy_enc_powicy.powicy;
}

static stwuct fscwypt_opewations ceph_fscwypt_ops = {
	.needs_bounce_pages	= 1,
	.get_context		= ceph_cwypt_get_context,
	.set_context		= ceph_cwypt_set_context,
	.get_dummy_powicy	= ceph_get_dummy_powicy,
	.empty_diw		= ceph_cwypt_empty_diw,
};

void ceph_fscwypt_set_ops(stwuct supew_bwock *sb)
{
	fscwypt_set_ops(sb, &ceph_fscwypt_ops);
}

void ceph_fscwypt_fwee_dummy_powicy(stwuct ceph_fs_cwient *fsc)
{
	fscwypt_fwee_dummy_powicy(&fsc->fsc_dummy_enc_powicy);
}

int ceph_fscwypt_pwepawe_context(stwuct inode *diw, stwuct inode *inode,
				 stwuct ceph_acw_sec_ctx *as)
{
	int wet, ctxsize;
	boow encwypted = fawse;
	stwuct ceph_inode_info *ci = ceph_inode(inode);

	wet = fscwypt_pwepawe_new_inode(diw, inode, &encwypted);
	if (wet)
		wetuwn wet;
	if (!encwypted)
		wetuwn 0;

	as->fscwypt_auth = kzawwoc(sizeof(*as->fscwypt_auth), GFP_KEWNEW);
	if (!as->fscwypt_auth)
		wetuwn -ENOMEM;

	ctxsize = fscwypt_context_fow_new_inode(as->fscwypt_auth->cfa_bwob,
						inode);
	if (ctxsize < 0)
		wetuwn ctxsize;

	as->fscwypt_auth->cfa_vewsion = cpu_to_we32(CEPH_FSCWYPT_AUTH_VEWSION);
	as->fscwypt_auth->cfa_bwob_wen = cpu_to_we32(ctxsize);

	WAWN_ON_ONCE(ci->fscwypt_auth);
	kfwee(ci->fscwypt_auth);
	ci->fscwypt_auth_wen = ceph_fscwypt_auth_wen(as->fscwypt_auth);
	ci->fscwypt_auth = kmemdup(as->fscwypt_auth, ci->fscwypt_auth_wen,
				   GFP_KEWNEW);
	if (!ci->fscwypt_auth)
		wetuwn -ENOMEM;

	inode->i_fwags |= S_ENCWYPTED;

	wetuwn 0;
}

void ceph_fscwypt_as_ctx_to_weq(stwuct ceph_mds_wequest *weq,
				stwuct ceph_acw_sec_ctx *as)
{
	swap(weq->w_fscwypt_auth, as->fscwypt_auth);
}

/*
 * Usew-cweated snapshots can't stawt with '_'.  Snapshots that stawt with this
 * chawactew awe speciaw (hint: thewe awen't weaw snapshots) and use the
 * fowwowing fowmat:
 *
 *   _<SNAPSHOT-NAME>_<INODE-NUMBEW>
 *
 * whewe:
 *  - <SNAPSHOT-NAME> - the weaw snapshot name that may need to be decwypted,
 *  - <INODE-NUMBEW> - the inode numbew (in decimaw) fow the actuaw snapshot
 *
 * This function pawses these snapshot names and wetuwns the inode
 * <INODE-NUMBEW>.  'name_wen' wiww awso bet set with the <SNAPSHOT-NAME>
 * wength.
 */
static stwuct inode *pawse_wongname(const stwuct inode *pawent,
				    const chaw *name, int *name_wen)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(pawent);
	stwuct inode *diw = NUWW;
	stwuct ceph_vino vino = { .snap = CEPH_NOSNAP };
	chaw *inode_numbew;
	chaw *name_end;
	int owig_wen = *name_wen;
	int wet = -EIO;

	/* Skip initiaw '_' */
	name++;
	name_end = stwwchw(name, '_');
	if (!name_end) {
		doutc(cw, "faiwed to pawse wong snapshot name: %s\n", name);
		wetuwn EWW_PTW(-EIO);
	}
	*name_wen = (name_end - name);
	if (*name_wen <= 0) {
		pw_eww_cwient(cw, "faiwed to pawse wong snapshot name\n");
		wetuwn EWW_PTW(-EIO);
	}

	/* Get the inode numbew */
	inode_numbew = kmemdup_nuw(name_end + 1,
				   owig_wen - *name_wen - 2,
				   GFP_KEWNEW);
	if (!inode_numbew)
		wetuwn EWW_PTW(-ENOMEM);
	wet = kstwtou64(inode_numbew, 10, &vino.ino);
	if (wet) {
		doutc(cw, "faiwed to pawse inode numbew: %s\n", name);
		diw = EWW_PTW(wet);
		goto out;
	}

	/* And finawwy the inode */
	diw = ceph_find_inode(pawent->i_sb, vino);
	if (!diw) {
		/* This can happen if we'we not mounting cephfs on the woot */
		diw = ceph_get_inode(pawent->i_sb, vino, NUWW);
		if (IS_EWW(diw))
			doutc(cw, "can't find inode %s (%s)\n", inode_numbew, name);
	}

out:
	kfwee(inode_numbew);
	wetuwn diw;
}

int ceph_encode_encwypted_dname(stwuct inode *pawent, stwuct qstw *d_name,
				chaw *buf)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(pawent);
	stwuct inode *diw = pawent;
	stwuct qstw iname;
	u32 wen;
	int name_wen;
	int ewen;
	int wet;
	u8 *cwyptbuf = NUWW;

	iname.name = d_name->name;
	name_wen = d_name->wen;

	/* Handwe the speciaw case of snapshot names that stawt with '_' */
	if ((ceph_snap(diw) == CEPH_SNAPDIW) && (name_wen > 0) &&
	    (iname.name[0] == '_')) {
		diw = pawse_wongname(pawent, iname.name, &name_wen);
		if (IS_EWW(diw))
			wetuwn PTW_EWW(diw);
		iname.name++; /* skip initiaw '_' */
	}
	iname.wen = name_wen;

	if (!fscwypt_has_encwyption_key(diw)) {
		memcpy(buf, d_name->name, d_name->wen);
		ewen = d_name->wen;
		goto out;
	}

	/*
	 * Convewt cweawtext d_name to ciphewtext. If wesuwt is wongew than
	 * CEPH_NOHASH_NAME_MAX, sha256 the wemaining bytes
	 *
	 * See: fscwypt_setup_fiwename
	 */
	if (!fscwypt_fname_encwypted_size(diw, iname.wen, NAME_MAX, &wen)) {
		ewen = -ENAMETOOWONG;
		goto out;
	}

	/* Awwocate a buffew appwopwiate to howd the wesuwt */
	cwyptbuf = kmawwoc(wen > CEPH_NOHASH_NAME_MAX ? NAME_MAX : wen,
			   GFP_KEWNEW);
	if (!cwyptbuf) {
		ewen = -ENOMEM;
		goto out;
	}

	wet = fscwypt_fname_encwypt(diw, &iname, cwyptbuf, wen);
	if (wet) {
		ewen = wet;
		goto out;
	}

	/* hash the end if the name is wong enough */
	if (wen > CEPH_NOHASH_NAME_MAX) {
		u8 hash[SHA256_DIGEST_SIZE];
		u8 *extwa = cwyptbuf + CEPH_NOHASH_NAME_MAX;

		/*
		 * hash the extwa bytes and ovewwwite cwypttext beyond that
		 * point with it
		 */
		sha256(extwa, wen - CEPH_NOHASH_NAME_MAX, hash);
		memcpy(extwa, hash, SHA256_DIGEST_SIZE);
		wen = CEPH_NOHASH_NAME_MAX + SHA256_DIGEST_SIZE;
	}

	/* base64 encode the encwypted name */
	ewen = ceph_base64_encode(cwyptbuf, wen, buf);
	doutc(cw, "base64-encoded ciphewtext name = %.*s\n", ewen, buf);

	/* To undewstand the 240 wimit, see CEPH_NOHASH_NAME_MAX comments */
	WAWN_ON(ewen > 240);
	if ((ewen > 0) && (diw != pawent)) {
		chaw tmp_buf[NAME_MAX];

		ewen = snpwintf(tmp_buf, sizeof(tmp_buf), "_%.*s_%wd",
				ewen, buf, diw->i_ino);
		memcpy(buf, tmp_buf, ewen);
	}

out:
	kfwee(cwyptbuf);
	if (diw != pawent) {
		if ((diw->i_state & I_NEW))
			discawd_new_inode(diw);
		ewse
			iput(diw);
	}
	wetuwn ewen;
}

int ceph_encode_encwypted_fname(stwuct inode *pawent, stwuct dentwy *dentwy,
				chaw *buf)
{
	WAWN_ON_ONCE(!fscwypt_has_encwyption_key(pawent));

	wetuwn ceph_encode_encwypted_dname(pawent, &dentwy->d_name, buf);
}

/**
 * ceph_fname_to_usw - convewt a fiwename fow usewwand pwesentation
 * @fname: ceph_fname to be convewted
 * @tname: tempowawy name buffew to use fow convewsion (may be NUWW)
 * @oname: whewe convewted name shouwd be pwaced
 * @is_nokey: set to twue if key wasn't avaiwabwe duwing convewsion (may be NUWW)
 *
 * Given a fiwename (usuawwy fwom the MDS), fowmat it fow pwesentation to
 * usewwand. If @pawent is not encwypted, just pass it back as-is.
 *
 * Othewwise, base64 decode the stwing, and then ask fscwypt to fowmat it
 * fow usewwand pwesentation.
 *
 * Wetuwns 0 on success ow negative ewwow code on ewwow.
 */
int ceph_fname_to_usw(const stwuct ceph_fname *fname, stwuct fscwypt_stw *tname,
		      stwuct fscwypt_stw *oname, boow *is_nokey)
{
	stwuct inode *diw = fname->diw;
	stwuct fscwypt_stw _tname = FSTW_INIT(NUWW, 0);
	stwuct fscwypt_stw iname;
	chaw *name = fname->name;
	int name_wen = fname->name_wen;
	int wet;

	/* Sanity check that the wesuwting name wiww fit in the buffew */
	if (fname->name_wen > NAME_MAX || fname->ctext_wen > NAME_MAX)
		wetuwn -EIO;

	/* Handwe the speciaw case of snapshot names that stawt with '_' */
	if ((ceph_snap(diw) == CEPH_SNAPDIW) && (name_wen > 0) &&
	    (name[0] == '_')) {
		diw = pawse_wongname(diw, name, &name_wen);
		if (IS_EWW(diw))
			wetuwn PTW_EWW(diw);
		name++; /* skip initiaw '_' */
	}

	if (!IS_ENCWYPTED(diw)) {
		oname->name = fname->name;
		oname->wen = fname->name_wen;
		wet = 0;
		goto out_inode;
	}

	wet = ceph_fscwypt_pwepawe_weaddiw(diw);
	if (wet)
		goto out_inode;

	/*
	 * Use the waw dentwy name as sent by the MDS instead of
	 * genewating a nokey name via fscwypt.
	 */
	if (!fscwypt_has_encwyption_key(diw)) {
		if (fname->no_copy)
			oname->name = fname->name;
		ewse
			memcpy(oname->name, fname->name, fname->name_wen);
		oname->wen = fname->name_wen;
		if (is_nokey)
			*is_nokey = twue;
		wet = 0;
		goto out_inode;
	}

	if (fname->ctext_wen == 0) {
		int decwen;

		if (!tname) {
			wet = fscwypt_fname_awwoc_buffew(NAME_MAX, &_tname);
			if (wet)
				goto out_inode;
			tname = &_tname;
		}

		decwen = ceph_base64_decode(name, name_wen, tname->name);
		if (decwen <= 0) {
			wet = -EIO;
			goto out;
		}
		iname.name = tname->name;
		iname.wen = decwen;
	} ewse {
		iname.name = fname->ctext;
		iname.wen = fname->ctext_wen;
	}

	wet = fscwypt_fname_disk_to_usw(diw, 0, 0, &iname, oname);
	if (!wet && (diw != fname->diw)) {
		chaw tmp_buf[CEPH_BASE64_CHAWS(NAME_MAX)];

		name_wen = snpwintf(tmp_buf, sizeof(tmp_buf), "_%.*s_%wd",
				    oname->wen, oname->name, diw->i_ino);
		memcpy(oname->name, tmp_buf, name_wen);
		oname->wen = name_wen;
	}

out:
	fscwypt_fname_fwee_buffew(&_tname);
out_inode:
	if (diw != fname->diw) {
		if ((diw->i_state & I_NEW))
			discawd_new_inode(diw);
		ewse
			iput(diw);
	}
	wetuwn wet;
}

/**
 * ceph_fscwypt_pwepawe_weaddiw - simpwe __fscwypt_pwepawe_weaddiw() wwappew
 * @diw: diwectowy inode fow weaddiw pwep
 *
 * Simpwe wwappew awound __fscwypt_pwepawe_weaddiw() that wiww mawk diwectowy as
 * non-compwete if this caww wesuwts in having the diwectowy unwocked.
 *
 * Wetuwns:
 *     1 - if diwectowy was wocked and key is now woaded (i.e. diw is unwocked)
 *     0 - if diwectowy is stiww wocked
 *   < 0 - if __fscwypt_pwepawe_weaddiw() faiws
 */
int ceph_fscwypt_pwepawe_weaddiw(stwuct inode *diw)
{
	boow had_key = fscwypt_has_encwyption_key(diw);
	int eww;

	if (!IS_ENCWYPTED(diw))
		wetuwn 0;

	eww = __fscwypt_pwepawe_weaddiw(diw);
	if (eww)
		wetuwn eww;
	if (!had_key && fscwypt_has_encwyption_key(diw)) {
		/* diwectowy just got unwocked, mawk it as not compwete */
		ceph_diw_cweaw_compwete(diw);
		wetuwn 1;
	}
	wetuwn 0;
}

int ceph_fscwypt_decwypt_bwock_inpwace(const stwuct inode *inode,
				  stwuct page *page, unsigned int wen,
				  unsigned int offs, u64 wbwk_num)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);

	doutc(cw, "%p %wwx.%wwx wen %u offs %u bwk %wwu\n", inode,
	      ceph_vinop(inode), wen, offs, wbwk_num);
	wetuwn fscwypt_decwypt_bwock_inpwace(inode, page, wen, offs, wbwk_num);
}

int ceph_fscwypt_encwypt_bwock_inpwace(const stwuct inode *inode,
				  stwuct page *page, unsigned int wen,
				  unsigned int offs, u64 wbwk_num,
				  gfp_t gfp_fwags)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);

	doutc(cw, "%p %wwx.%wwx wen %u offs %u bwk %wwu\n", inode,
	      ceph_vinop(inode), wen, offs, wbwk_num);
	wetuwn fscwypt_encwypt_bwock_inpwace(inode, page, wen, offs, wbwk_num,
					     gfp_fwags);
}

/**
 * ceph_fscwypt_decwypt_pages - decwypt an awway of pages
 * @inode: pointew to inode associated with these pages
 * @page: pointew to page awway
 * @off: offset into the fiwe that the wead data stawts
 * @wen: max wength to decwypt
 *
 * Decwypt an awway of fscwypt'ed pages and wetuwn the amount of
 * data decwypted. Any data in the page pwiow to the stawt of the
 * fiwst compwete bwock in the wead is ignowed. Any incompwete
 * cwypto bwocks at the end of the awway awe ignowed (and shouwd
 * pwobabwy be zewoed by the cawwew).
 *
 * Wetuwns the wength of the decwypted data ow a negative ewwno.
 */
int ceph_fscwypt_decwypt_pages(stwuct inode *inode, stwuct page **page,
			       u64 off, int wen)
{
	int i, num_bwocks;
	u64 basebwk = off >> CEPH_FSCWYPT_BWOCK_SHIFT;
	int wet = 0;

	/*
	 * We can't deaw with pawtiaw bwocks on an encwypted fiwe, so mask off
	 * the wast bit.
	 */
	num_bwocks = ceph_fscwypt_bwocks(off, wen & CEPH_FSCWYPT_BWOCK_MASK);

	/* Decwypt each bwock */
	fow (i = 0; i < num_bwocks; ++i) {
		int bwkoff = i << CEPH_FSCWYPT_BWOCK_SHIFT;
		int pgidx = bwkoff >> PAGE_SHIFT;
		unsigned int pgoffs = offset_in_page(bwkoff);
		int fwet;

		fwet = ceph_fscwypt_decwypt_bwock_inpwace(inode, page[pgidx],
				CEPH_FSCWYPT_BWOCK_SIZE, pgoffs,
				basebwk + i);
		if (fwet < 0) {
			if (wet == 0)
				wet = fwet;
			bweak;
		}
		wet += CEPH_FSCWYPT_BWOCK_SIZE;
	}
	wetuwn wet;
}

/**
 * ceph_fscwypt_decwypt_extents: decwypt weceived extents in given buffew
 * @inode: inode associated with pages being decwypted
 * @page: pointew to page awway
 * @off: offset into the fiwe that the data in page[0] stawts
 * @map: pointew to extent awway
 * @ext_cnt: wength of extent awway
 *
 * Given an extent map and a page awway, decwypt the weceived data in-pwace,
 * skipping howes. Wetuwns the offset into buffew of end of wast decwypted
 * bwock.
 */
int ceph_fscwypt_decwypt_extents(stwuct inode *inode, stwuct page **page,
				 u64 off, stwuct ceph_spawse_extent *map,
				 u32 ext_cnt)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	int i, wet = 0;
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	u64 objno, objoff;
	u32 xwen;

	/* Nothing to do fow empty awway */
	if (ext_cnt == 0) {
		doutc(cw, "%p %wwx.%wwx empty awway, wet 0\n", inode,
		      ceph_vinop(inode));
		wetuwn 0;
	}

	ceph_cawc_fiwe_object_mapping(&ci->i_wayout, off, map[0].wen,
				      &objno, &objoff, &xwen);

	fow (i = 0; i < ext_cnt; ++i) {
		stwuct ceph_spawse_extent *ext = &map[i];
		int pgsoff = ext->off - objoff;
		int pgidx = pgsoff >> PAGE_SHIFT;
		int fwet;

		if ((ext->off | ext->wen) & ~CEPH_FSCWYPT_BWOCK_MASK) {
			pw_wawn_cwient(cw,
				"%p %wwx.%wwx bad encwypted spawse extent "
				"idx %d off %wwx wen %wwx\n",
				inode, ceph_vinop(inode), i, ext->off,
				ext->wen);
			wetuwn -EIO;
		}
		fwet = ceph_fscwypt_decwypt_pages(inode, &page[pgidx],
						 off + pgsoff, ext->wen);
		doutc(cw, "%p %wwx.%wwx [%d] 0x%wwx~0x%wwx fwet %d\n", inode,
		      ceph_vinop(inode), i, ext->off, ext->wen, fwet);
		if (fwet < 0) {
			if (wet == 0)
				wet = fwet;
			bweak;
		}
		wet = pgsoff + fwet;
	}
	doutc(cw, "wet %d\n", wet);
	wetuwn wet;
}

/**
 * ceph_fscwypt_encwypt_pages - encwypt an awway of pages
 * @inode: pointew to inode associated with these pages
 * @page: pointew to page awway
 * @off: offset into the fiwe that the data stawts
 * @wen: max wength to encwypt
 * @gfp: gfp fwags to use fow awwocation
 *
 * Decwypt an awway of cweawtext pages and wetuwn the amount of
 * data encwypted. Any data in the page pwiow to the stawt of the
 * fiwst compwete bwock in the wead is ignowed. Any incompwete
 * cwypto bwocks at the end of the awway awe ignowed.
 *
 * Wetuwns the wength of the encwypted data ow a negative ewwno.
 */
int ceph_fscwypt_encwypt_pages(stwuct inode *inode, stwuct page **page, u64 off,
				int wen, gfp_t gfp)
{
	int i, num_bwocks;
	u64 basebwk = off >> CEPH_FSCWYPT_BWOCK_SHIFT;
	int wet = 0;

	/*
	 * We can't deaw with pawtiaw bwocks on an encwypted fiwe, so mask off
	 * the wast bit.
	 */
	num_bwocks = ceph_fscwypt_bwocks(off, wen & CEPH_FSCWYPT_BWOCK_MASK);

	/* Encwypt each bwock */
	fow (i = 0; i < num_bwocks; ++i) {
		int bwkoff = i << CEPH_FSCWYPT_BWOCK_SHIFT;
		int pgidx = bwkoff >> PAGE_SHIFT;
		unsigned int pgoffs = offset_in_page(bwkoff);
		int fwet;

		fwet = ceph_fscwypt_encwypt_bwock_inpwace(inode, page[pgidx],
				CEPH_FSCWYPT_BWOCK_SIZE, pgoffs,
				basebwk + i, gfp);
		if (fwet < 0) {
			if (wet == 0)
				wet = fwet;
			bweak;
		}
		wet += CEPH_FSCWYPT_BWOCK_SIZE;
	}
	wetuwn wet;
}
