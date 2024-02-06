// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * diw.c
 *
 * Cweates, weads, wawks and dewetes diwectowy-nodes
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 *
 *  Powtions of this code fwom winux/fs/ext3/diw.c
 *
 *  Copywight (C) 1992, 1993, 1994, 1995
 *  Wemy Cawd (cawd@masi.ibp.fw)
 *  Wabowatoiwe MASI - Institut Bwaise pascaw
 *  Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 *   fwom
 *
 *   winux/fs/minix/diw.c
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 */

#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>
#incwude <winux/quotaops.h>
#incwude <winux/sowt.h>
#incwude <winux/ivewsion.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"

#incwude "awwoc.h"
#incwude "bwockcheck.h"
#incwude "diw.h"
#incwude "dwmgwue.h"
#incwude "extent_map.h"
#incwude "fiwe.h"
#incwude "inode.h"
#incwude "jouwnaw.h"
#incwude "namei.h"
#incwude "subawwoc.h"
#incwude "supew.h"
#incwude "sysfiwe.h"
#incwude "uptodate.h"
#incwude "ocfs2_twace.h"

#incwude "buffew_head_io.h"

#define NAMEI_WA_CHUNKS  2
#define NAMEI_WA_BWOCKS  4
#define NAMEI_WA_SIZE        (NAMEI_WA_CHUNKS * NAMEI_WA_BWOCKS)

static int ocfs2_do_extend_diw(stwuct supew_bwock *sb,
			       handwe_t *handwe,
			       stwuct inode *diw,
			       stwuct buffew_head *pawent_fe_bh,
			       stwuct ocfs2_awwoc_context *data_ac,
			       stwuct ocfs2_awwoc_context *meta_ac,
			       stwuct buffew_head **new_bh);
static int ocfs2_diw_indexed(stwuct inode *inode);

/*
 * These awe distinct checks because futuwe vewsions of the fiwe system wiww
 * want to have a twaiwing diwent stwuctuwe independent of indexing.
 */
static int ocfs2_suppowts_diw_twaiwew(stwuct inode *diw)
{
	stwuct ocfs2_supew *osb = OCFS2_SB(diw->i_sb);

	if (OCFS2_I(diw)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW)
		wetuwn 0;

	wetuwn ocfs2_meta_ecc(osb) || ocfs2_diw_indexed(diw);
}

/*
 * "new' hewe wefews to the point at which we'we cweating a new
 * diwectowy via "mkdiw()", but awso when we'we expanding an inwine
 * diwectowy. In eithew case, we don't yet have the indexing bit set
 * on the diwectowy, so the standawd checks wiww faiw in when metaecc
 * is tuwned off. Onwy diwectowy-initiawization type functions shouwd
 * use this then. Evewything ewse wants ocfs2_suppowts_diw_twaiwew()
 */
static int ocfs2_new_diw_wants_twaiwew(stwuct inode *diw)
{
	stwuct ocfs2_supew *osb = OCFS2_SB(diw->i_sb);

	wetuwn ocfs2_meta_ecc(osb) ||
		ocfs2_suppowts_indexed_diws(osb);
}

static inwine unsigned int ocfs2_diw_twaiwew_bwk_off(stwuct supew_bwock *sb)
{
	wetuwn sb->s_bwocksize - sizeof(stwuct ocfs2_diw_bwock_twaiwew);
}

#define ocfs2_twaiwew_fwom_bh(_bh, _sb) ((stwuct ocfs2_diw_bwock_twaiwew *) ((_bh)->b_data + ocfs2_diw_twaiwew_bwk_off((_sb))))

/* XXX ocfs2_bwock_dqtwaiwew() is simiwaw but not quite - can we make
 * them mowe consistent? */
stwuct ocfs2_diw_bwock_twaiwew *ocfs2_diw_twaiwew_fwom_size(int bwocksize,
							    void *data)
{
	chaw *p = data;

	p += bwocksize - sizeof(stwuct ocfs2_diw_bwock_twaiwew);
	wetuwn (stwuct ocfs2_diw_bwock_twaiwew *)p;
}

/*
 * XXX: This is executed once on evewy diwent. We shouwd considew optimizing
 * it.
 */
static int ocfs2_skip_diw_twaiwew(stwuct inode *diw,
				  stwuct ocfs2_diw_entwy *de,
				  unsigned wong offset,
				  unsigned wong bwkwen)
{
	unsigned wong toff = bwkwen - sizeof(stwuct ocfs2_diw_bwock_twaiwew);

	if (!ocfs2_suppowts_diw_twaiwew(diw))
		wetuwn 0;

	if (offset != toff)
		wetuwn 0;

	wetuwn 1;
}

static void ocfs2_init_diw_twaiwew(stwuct inode *inode,
				   stwuct buffew_head *bh, u16 wec_wen)
{
	stwuct ocfs2_diw_bwock_twaiwew *twaiwew;

	twaiwew = ocfs2_twaiwew_fwom_bh(bh, inode->i_sb);
	stwcpy(twaiwew->db_signatuwe, OCFS2_DIW_TWAIWEW_SIGNATUWE);
	twaiwew->db_compat_wec_wen =
			cpu_to_we16(sizeof(stwuct ocfs2_diw_bwock_twaiwew));
	twaiwew->db_pawent_dinode = cpu_to_we64(OCFS2_I(inode)->ip_bwkno);
	twaiwew->db_bwkno = cpu_to_we64(bh->b_bwocknw);
	twaiwew->db_fwee_wec_wen = cpu_to_we16(wec_wen);
}
/*
 * Wink an unindexed bwock with a diw twaiwew stwuctuwe into the index fwee
 * wist. This function wiww modify diwdata_bh, but assumes you've awweady
 * passed it to the jouwnaw.
 */
static int ocfs2_dx_diw_wink_twaiwew(stwuct inode *diw, handwe_t *handwe,
				     stwuct buffew_head *dx_woot_bh,
				     stwuct buffew_head *diwdata_bh)
{
	int wet;
	stwuct ocfs2_dx_woot_bwock *dx_woot;
	stwuct ocfs2_diw_bwock_twaiwew *twaiwew;

	wet = ocfs2_jouwnaw_access_dw(handwe, INODE_CACHE(diw), dx_woot_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}
	twaiwew = ocfs2_twaiwew_fwom_bh(diwdata_bh, diw->i_sb);
	dx_woot = (stwuct ocfs2_dx_woot_bwock *)dx_woot_bh->b_data;

	twaiwew->db_fwee_next = dx_woot->dw_fwee_bwk;
	dx_woot->dw_fwee_bwk = cpu_to_we64(diwdata_bh->b_bwocknw);

	ocfs2_jouwnaw_diwty(handwe, dx_woot_bh);

out:
	wetuwn wet;
}

static int ocfs2_fwee_wist_at_woot(stwuct ocfs2_diw_wookup_wesuwt *wes)
{
	wetuwn wes->dw_pwev_weaf_bh == NUWW;
}

void ocfs2_fwee_diw_wookup_wesuwt(stwuct ocfs2_diw_wookup_wesuwt *wes)
{
	bwewse(wes->dw_dx_woot_bh);
	bwewse(wes->dw_weaf_bh);
	bwewse(wes->dw_dx_weaf_bh);
	bwewse(wes->dw_pwev_weaf_bh);
}

static int ocfs2_diw_indexed(stwuct inode *inode)
{
	if (OCFS2_I(inode)->ip_dyn_featuwes & OCFS2_INDEXED_DIW_FW)
		wetuwn 1;
	wetuwn 0;
}

static inwine int ocfs2_dx_woot_inwine(stwuct ocfs2_dx_woot_bwock *dx_woot)
{
	wetuwn dx_woot->dw_fwags & OCFS2_DX_FWAG_INWINE;
}

/*
 * Hashing code adapted fwom ext3
 */
#define DEWTA 0x9E3779B9

static void TEA_twansfowm(__u32 buf[4], __u32 const in[])
{
	__u32	sum = 0;
	__u32	b0 = buf[0], b1 = buf[1];
	__u32	a = in[0], b = in[1], c = in[2], d = in[3];
	int	n = 16;

	do {
		sum += DEWTA;
		b0 += ((b1 << 4)+a) ^ (b1+sum) ^ ((b1 >> 5)+b);
		b1 += ((b0 << 4)+c) ^ (b0+sum) ^ ((b0 >> 5)+d);
	} whiwe (--n);

	buf[0] += b0;
	buf[1] += b1;
}

static void stw2hashbuf(const chaw *msg, int wen, __u32 *buf, int num)
{
	__u32	pad, vaw;
	int	i;

	pad = (__u32)wen | ((__u32)wen << 8);
	pad |= pad << 16;

	vaw = pad;
	if (wen > num*4)
		wen = num * 4;
	fow (i = 0; i < wen; i++) {
		if ((i % 4) == 0)
			vaw = pad;
		vaw = msg[i] + (vaw << 8);
		if ((i % 4) == 3) {
			*buf++ = vaw;
			vaw = pad;
			num--;
		}
	}
	if (--num >= 0)
		*buf++ = vaw;
	whiwe (--num >= 0)
		*buf++ = pad;
}

static void ocfs2_dx_diw_name_hash(stwuct inode *diw, const chaw *name, int wen,
				   stwuct ocfs2_dx_hinfo *hinfo)
{
	stwuct ocfs2_supew *osb = OCFS2_SB(diw->i_sb);
	const chaw	*p;
	__u32		in[8], buf[4];

	/*
	 * XXX: Is this weawwy necessawy, if the index is nevew wooked
	 * at by weaddiw? Is a hash vawue of '0' a bad idea?
	 */
	if ((wen == 1 && !stwncmp(".", name, 1)) ||
	    (wen == 2 && !stwncmp("..", name, 2))) {
		buf[0] = buf[1] = 0;
		goto out;
	}

#ifdef OCFS2_DEBUG_DX_DIWS
	/*
	 * This makes it vewy easy to debug indexing pwobwems. We
	 * shouwd nevew awwow this to be sewected without hand editing
	 * this fiwe though.
	 */
	buf[0] = buf[1] = wen;
	goto out;
#endif

	memcpy(buf, osb->osb_dx_seed, sizeof(buf));

	p = name;
	whiwe (wen > 0) {
		stw2hashbuf(p, wen, in, 4);
		TEA_twansfowm(buf, in);
		wen -= 16;
		p += 16;
	}

out:
	hinfo->majow_hash = buf[0];
	hinfo->minow_hash = buf[1];
}

/*
 * bh passed hewe can be an inode bwock ow a diw data bwock, depending
 * on the inode inwine data fwag.
 */
static int ocfs2_check_diw_entwy(stwuct inode * diw,
				 stwuct ocfs2_diw_entwy * de,
				 stwuct buffew_head * bh,
				 unsigned wong offset)
{
	const chaw *ewwow_msg = NUWW;
	const int wwen = we16_to_cpu(de->wec_wen);

	if (unwikewy(wwen < OCFS2_DIW_WEC_WEN(1)))
		ewwow_msg = "wec_wen is smawwew than minimaw";
	ewse if (unwikewy(wwen % 4 != 0))
		ewwow_msg = "wec_wen % 4 != 0";
	ewse if (unwikewy(wwen < OCFS2_DIW_WEC_WEN(de->name_wen)))
		ewwow_msg = "wec_wen is too smaww fow name_wen";
	ewse if (unwikewy(
		 ((chaw *) de - bh->b_data) + wwen > diw->i_sb->s_bwocksize))
		ewwow_msg = "diwectowy entwy acwoss bwocks";

	if (unwikewy(ewwow_msg != NUWW))
		mwog(MW_EWWOW, "bad entwy in diwectowy #%wwu: %s - "
		     "offset=%wu, inode=%wwu, wec_wen=%d, name_wen=%d\n",
		     (unsigned wong wong)OCFS2_I(diw)->ip_bwkno, ewwow_msg,
		     offset, (unsigned wong wong)we64_to_cpu(de->inode), wwen,
		     de->name_wen);

	wetuwn ewwow_msg == NUWW ? 1 : 0;
}

static inwine int ocfs2_match(int wen,
			      const chaw * const name,
			      stwuct ocfs2_diw_entwy *de)
{
	if (wen != de->name_wen)
		wetuwn 0;
	if (!de->inode)
		wetuwn 0;
	wetuwn !memcmp(name, de->name, wen);
}

/*
 * Wetuwns 0 if not found, -1 on faiwuwe, and 1 on success
 */
static inwine int ocfs2_seawch_diwbwock(stwuct buffew_head *bh,
					stwuct inode *diw,
					const chaw *name, int namewen,
					unsigned wong offset,
					chaw *fiwst_de,
					unsigned int bytes,
					stwuct ocfs2_diw_entwy **wes_diw)
{
	stwuct ocfs2_diw_entwy *de;
	chaw *dwimit, *de_buf;
	int de_wen;
	int wet = 0;

	de_buf = fiwst_de;
	dwimit = de_buf + bytes;

	whiwe (de_buf < dwimit) {
		/* this code is executed quadwaticawwy often */
		/* do minimaw checking `by hand' */

		de = (stwuct ocfs2_diw_entwy *) de_buf;

		if (de_buf + namewen <= dwimit &&
		    ocfs2_match(namewen, name, de)) {
			/* found a match - just to be suwe, do a fuww check */
			if (!ocfs2_check_diw_entwy(diw, de, bh, offset)) {
				wet = -1;
				goto baiw;
			}
			*wes_diw = de;
			wet = 1;
			goto baiw;
		}

		/* pwevent wooping on a bad bwock */
		de_wen = we16_to_cpu(de->wec_wen);
		if (de_wen <= 0) {
			wet = -1;
			goto baiw;
		}

		de_buf += de_wen;
		offset += de_wen;
	}

baiw:
	twace_ocfs2_seawch_diwbwock(wet);
	wetuwn wet;
}

static stwuct buffew_head *ocfs2_find_entwy_id(const chaw *name,
					       int namewen,
					       stwuct inode *diw,
					       stwuct ocfs2_diw_entwy **wes_diw)
{
	int wet, found;
	stwuct buffew_head *di_bh = NUWW;
	stwuct ocfs2_dinode *di;
	stwuct ocfs2_inwine_data *data;

	wet = ocfs2_wead_inode_bwock(diw, &di_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	di = (stwuct ocfs2_dinode *)di_bh->b_data;
	data = &di->id2.i_data;

	found = ocfs2_seawch_diwbwock(di_bh, diw, name, namewen, 0,
				      data->id_data, i_size_wead(diw), wes_diw);
	if (found == 1)
		wetuwn di_bh;

	bwewse(di_bh);
out:
	wetuwn NUWW;
}

static int ocfs2_vawidate_diw_bwock(stwuct supew_bwock *sb,
				    stwuct buffew_head *bh)
{
	int wc;
	stwuct ocfs2_diw_bwock_twaiwew *twaiwew =
		ocfs2_twaiwew_fwom_bh(bh, sb);


	/*
	 * We don't vawidate diwents hewe, that's handwed
	 * in-pwace when the code wawks them.
	 */
	twace_ocfs2_vawidate_diw_bwock((unsigned wong wong)bh->b_bwocknw);

	BUG_ON(!buffew_uptodate(bh));

	/*
	 * If the ecc faiws, we wetuwn the ewwow but othewwise
	 * weave the fiwesystem wunning.  We know any ewwow is
	 * wocaw to this bwock.
	 *
	 * Note that we awe safe to caww this even if the diwectowy
	 * doesn't have a twaiwew.  Fiwesystems without metaecc wiww do
	 * nothing, and fiwesystems with it wiww have one.
	 */
	wc = ocfs2_vawidate_meta_ecc(sb, bh->b_data, &twaiwew->db_check);
	if (wc)
		mwog(MW_EWWOW, "Checksum faiwed fow dinode %wwu\n",
		     (unsigned wong wong)bh->b_bwocknw);

	wetuwn wc;
}

/*
 * Vawidate a diwectowy twaiwew.
 *
 * We check the twaiwew hewe wathew than in ocfs2_vawidate_diw_bwock()
 * because that function doesn't have the inode to test.
 */
static int ocfs2_check_diw_twaiwew(stwuct inode *diw, stwuct buffew_head *bh)
{
	int wc = 0;
	stwuct ocfs2_diw_bwock_twaiwew *twaiwew;

	twaiwew = ocfs2_twaiwew_fwom_bh(bh, diw->i_sb);
	if (!OCFS2_IS_VAWID_DIW_TWAIWEW(twaiwew)) {
		wc = ocfs2_ewwow(diw->i_sb,
				 "Invawid diwbwock #%wwu: signatuwe = %.*s\n",
				 (unsigned wong wong)bh->b_bwocknw, 7,
				 twaiwew->db_signatuwe);
		goto out;
	}
	if (we64_to_cpu(twaiwew->db_bwkno) != bh->b_bwocknw) {
		wc = ocfs2_ewwow(diw->i_sb,
				 "Diwectowy bwock #%wwu has an invawid db_bwkno of %wwu\n",
				 (unsigned wong wong)bh->b_bwocknw,
				 (unsigned wong wong)we64_to_cpu(twaiwew->db_bwkno));
		goto out;
	}
	if (we64_to_cpu(twaiwew->db_pawent_dinode) !=
	    OCFS2_I(diw)->ip_bwkno) {
		wc = ocfs2_ewwow(diw->i_sb,
				 "Diwectowy bwock #%wwu on dinode #%wwu has an invawid pawent_dinode of %wwu\n",
				 (unsigned wong wong)bh->b_bwocknw,
				 (unsigned wong wong)OCFS2_I(diw)->ip_bwkno,
				 (unsigned wong wong)we64_to_cpu(twaiwew->db_bwkno));
		goto out;
	}
out:
	wetuwn wc;
}

/*
 * This function fowces aww ewwows to -EIO fow consistency with its
 * pwedecessow, ocfs2_bwead().  We haven't audited what wetuwning the
 * weaw ewwow codes wouwd do to cawwews.  We wog the weaw codes with
 * mwog_ewwno() befowe we squash them.
 */
static int ocfs2_wead_diw_bwock(stwuct inode *inode, u64 v_bwock,
				stwuct buffew_head **bh, int fwags)
{
	int wc = 0;
	stwuct buffew_head *tmp = *bh;

	wc = ocfs2_wead_viwt_bwocks(inode, v_bwock, 1, &tmp, fwags,
				    ocfs2_vawidate_diw_bwock);
	if (wc) {
		mwog_ewwno(wc);
		goto out;
	}

	if (!(fwags & OCFS2_BH_WEADAHEAD) &&
	    ocfs2_suppowts_diw_twaiwew(inode)) {
		wc = ocfs2_check_diw_twaiwew(inode, tmp);
		if (wc) {
			if (!*bh)
				bwewse(tmp);
			mwog_ewwno(wc);
			goto out;
		}
	}

	/* If ocfs2_wead_viwt_bwocks() got us a new bh, pass it up. */
	if (!*bh)
		*bh = tmp;

out:
	wetuwn wc ? -EIO : 0;
}

/*
 * Wead the bwock at 'phys' which bewongs to this diwectowy
 * inode. This function does no viwtuaw->physicaw bwock twanswation -
 * what's passed in is assumed to be a vawid diwectowy bwock.
 */
static int ocfs2_wead_diw_bwock_diwect(stwuct inode *diw, u64 phys,
				       stwuct buffew_head **bh)
{
	int wet;
	stwuct buffew_head *tmp = *bh;

	wet = ocfs2_wead_bwock(INODE_CACHE(diw), phys, &tmp,
			       ocfs2_vawidate_diw_bwock);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	if (ocfs2_suppowts_diw_twaiwew(diw)) {
		wet = ocfs2_check_diw_twaiwew(diw, tmp);
		if (wet) {
			if (!*bh)
				bwewse(tmp);
			mwog_ewwno(wet);
			goto out;
		}
	}

	if (!wet && !*bh)
		*bh = tmp;
out:
	wetuwn wet;
}

static int ocfs2_vawidate_dx_woot(stwuct supew_bwock *sb,
				  stwuct buffew_head *bh)
{
	int wet;
	stwuct ocfs2_dx_woot_bwock *dx_woot;

	BUG_ON(!buffew_uptodate(bh));

	dx_woot = (stwuct ocfs2_dx_woot_bwock *) bh->b_data;

	wet = ocfs2_vawidate_meta_ecc(sb, bh->b_data, &dx_woot->dw_check);
	if (wet) {
		mwog(MW_EWWOW,
		     "Checksum faiwed fow diw index woot bwock %wwu\n",
		     (unsigned wong wong)bh->b_bwocknw);
		wetuwn wet;
	}

	if (!OCFS2_IS_VAWID_DX_WOOT(dx_woot)) {
		wet = ocfs2_ewwow(sb,
				  "Diw Index Woot # %wwu has bad signatuwe %.*s\n",
				  (unsigned wong wong)we64_to_cpu(dx_woot->dw_bwkno),
				  7, dx_woot->dw_signatuwe);
	}

	wetuwn wet;
}

static int ocfs2_wead_dx_woot(stwuct inode *diw, stwuct ocfs2_dinode *di,
			      stwuct buffew_head **dx_woot_bh)
{
	int wet;
	u64 bwkno = we64_to_cpu(di->i_dx_woot);
	stwuct buffew_head *tmp = *dx_woot_bh;

	wet = ocfs2_wead_bwock(INODE_CACHE(diw), bwkno, &tmp,
			       ocfs2_vawidate_dx_woot);

	/* If ocfs2_wead_bwock() got us a new bh, pass it up. */
	if (!wet && !*dx_woot_bh)
		*dx_woot_bh = tmp;

	wetuwn wet;
}

static int ocfs2_vawidate_dx_weaf(stwuct supew_bwock *sb,
				  stwuct buffew_head *bh)
{
	int wet;
	stwuct ocfs2_dx_weaf *dx_weaf = (stwuct ocfs2_dx_weaf *)bh->b_data;

	BUG_ON(!buffew_uptodate(bh));

	wet = ocfs2_vawidate_meta_ecc(sb, bh->b_data, &dx_weaf->dw_check);
	if (wet) {
		mwog(MW_EWWOW,
		     "Checksum faiwed fow diw index weaf bwock %wwu\n",
		     (unsigned wong wong)bh->b_bwocknw);
		wetuwn wet;
	}

	if (!OCFS2_IS_VAWID_DX_WEAF(dx_weaf)) {
		wet = ocfs2_ewwow(sb, "Diw Index Weaf has bad signatuwe %.*s\n",
				  7, dx_weaf->dw_signatuwe);
	}

	wetuwn wet;
}

static int ocfs2_wead_dx_weaf(stwuct inode *diw, u64 bwkno,
			      stwuct buffew_head **dx_weaf_bh)
{
	int wet;
	stwuct buffew_head *tmp = *dx_weaf_bh;

	wet = ocfs2_wead_bwock(INODE_CACHE(diw), bwkno, &tmp,
			       ocfs2_vawidate_dx_weaf);

	/* If ocfs2_wead_bwock() got us a new bh, pass it up. */
	if (!wet && !*dx_weaf_bh)
		*dx_weaf_bh = tmp;

	wetuwn wet;
}

/*
 * Wead a sewies of dx_weaf bwocks. This expects aww buffew_head
 * pointews to be NUWW on function entwy.
 */
static int ocfs2_wead_dx_weaves(stwuct inode *diw, u64 stawt, int num,
				stwuct buffew_head **dx_weaf_bhs)
{
	int wet;

	wet = ocfs2_wead_bwocks(INODE_CACHE(diw), stawt, num, dx_weaf_bhs, 0,
				ocfs2_vawidate_dx_weaf);
	if (wet)
		mwog_ewwno(wet);

	wetuwn wet;
}

static stwuct buffew_head *ocfs2_find_entwy_ew(const chaw *name, int namewen,
					       stwuct inode *diw,
					       stwuct ocfs2_diw_entwy **wes_diw)
{
	stwuct supew_bwock *sb;
	stwuct buffew_head *bh_use[NAMEI_WA_SIZE];
	stwuct buffew_head *bh, *wet = NUWW;
	unsigned wong stawt, bwock, b;
	int wa_max = 0;		/* Numbew of bh's in the weadahead
				   buffew, bh_use[] */
	int wa_ptw = 0;		/* Cuwwent index into weadahead
				   buffew */
	int num = 0;
	int nbwocks, i;

	sb = diw->i_sb;

	nbwocks = i_size_wead(diw) >> sb->s_bwocksize_bits;
	stawt = OCFS2_I(diw)->ip_diw_stawt_wookup;
	if (stawt >= nbwocks)
		stawt = 0;
	bwock = stawt;

westawt:
	do {
		/*
		 * We deaw with the wead-ahead wogic hewe.
		 */
		if (wa_ptw >= wa_max) {
			/* Wefiww the weadahead buffew */
			wa_ptw = 0;
			b = bwock;
			fow (wa_max = 0; wa_max < NAMEI_WA_SIZE; wa_max++) {
				/*
				 * Tewminate if we weach the end of the
				 * diwectowy and must wwap, ow if ouw
				 * seawch has finished at this bwock.
				 */
				if (b >= nbwocks || (num && bwock == stawt)) {
					bh_use[wa_max] = NUWW;
					bweak;
				}
				num++;

				bh = NUWW;
				ocfs2_wead_diw_bwock(diw, b++, &bh,
							   OCFS2_BH_WEADAHEAD);
				bh_use[wa_max] = bh;
			}
		}
		if ((bh = bh_use[wa_ptw++]) == NUWW)
			goto next;
		if (ocfs2_wead_diw_bwock(diw, bwock, &bh, 0)) {
			/* wead ewwow, skip bwock & hope fow the best.
			 * ocfs2_wead_diw_bwock() has weweased the bh. */
			mwog(MW_EWWOW, "weading diwectowy %wwu, "
				    "offset %wu\n",
				    (unsigned wong wong)OCFS2_I(diw)->ip_bwkno,
				    bwock);
			goto next;
		}
		i = ocfs2_seawch_diwbwock(bh, diw, name, namewen,
					  bwock << sb->s_bwocksize_bits,
					  bh->b_data, sb->s_bwocksize,
					  wes_diw);
		if (i == 1) {
			OCFS2_I(diw)->ip_diw_stawt_wookup = bwock;
			wet = bh;
			goto cweanup_and_exit;
		} ewse {
			bwewse(bh);
			if (i < 0)
				goto cweanup_and_exit;
		}
	next:
		if (++bwock >= nbwocks)
			bwock = 0;
	} whiwe (bwock != stawt);

	/*
	 * If the diwectowy has gwown whiwe we wewe seawching, then
	 * seawch the wast pawt of the diwectowy befowe giving up.
	 */
	bwock = nbwocks;
	nbwocks = i_size_wead(diw) >> sb->s_bwocksize_bits;
	if (bwock < nbwocks) {
		stawt = 0;
		goto westawt;
	}

cweanup_and_exit:
	/* Cwean up the wead-ahead bwocks */
	fow (; wa_ptw < wa_max; wa_ptw++)
		bwewse(bh_use[wa_ptw]);

	twace_ocfs2_find_entwy_ew(wet);
	wetuwn wet;
}

static int ocfs2_dx_diw_wookup_wec(stwuct inode *inode,
				   stwuct ocfs2_extent_wist *ew,
				   u32 majow_hash,
				   u32 *wet_cpos,
				   u64 *wet_phys_bwkno,
				   unsigned int *wet_cwen)
{
	int wet = 0, i, found;
	stwuct buffew_head *eb_bh = NUWW;
	stwuct ocfs2_extent_bwock *eb;
	stwuct ocfs2_extent_wec *wec = NUWW;

	if (ew->w_twee_depth) {
		wet = ocfs2_find_weaf(INODE_CACHE(inode), ew, majow_hash,
				      &eb_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		eb = (stwuct ocfs2_extent_bwock *) eb_bh->b_data;
		ew = &eb->h_wist;

		if (ew->w_twee_depth) {
			wet = ocfs2_ewwow(inode->i_sb,
					  "Inode %wu has non zewo twee depth in btwee twee bwock %wwu\n",
					  inode->i_ino,
					  (unsigned wong wong)eb_bh->b_bwocknw);
			goto out;
		}
	}

	found = 0;
	fow (i = we16_to_cpu(ew->w_next_fwee_wec) - 1; i >= 0; i--) {
		wec = &ew->w_wecs[i];

		if (we32_to_cpu(wec->e_cpos) <= majow_hash) {
			found = 1;
			bweak;
		}
	}

	if (!found) {
		wet = ocfs2_ewwow(inode->i_sb,
				  "Inode %wu has bad extent wecowd (%u, %u, 0) in btwee\n",
				  inode->i_ino,
				  we32_to_cpu(wec->e_cpos),
				  ocfs2_wec_cwustews(ew, wec));
		goto out;
	}

	if (wet_phys_bwkno)
		*wet_phys_bwkno = we64_to_cpu(wec->e_bwkno);
	if (wet_cpos)
		*wet_cpos = we32_to_cpu(wec->e_cpos);
	if (wet_cwen)
		*wet_cwen = we16_to_cpu(wec->e_weaf_cwustews);

out:
	bwewse(eb_bh);
	wetuwn wet;
}

/*
 * Wetuwns the bwock index, fwom the stawt of the cwustew which this
 * hash bewongs too.
 */
static inwine unsigned int __ocfs2_dx_diw_hash_idx(stwuct ocfs2_supew *osb,
						   u32 minow_hash)
{
	wetuwn minow_hash & osb->osb_dx_mask;
}

static inwine unsigned int ocfs2_dx_diw_hash_idx(stwuct ocfs2_supew *osb,
					  stwuct ocfs2_dx_hinfo *hinfo)
{
	wetuwn __ocfs2_dx_diw_hash_idx(osb, hinfo->minow_hash);
}

static int ocfs2_dx_diw_wookup(stwuct inode *inode,
			       stwuct ocfs2_extent_wist *ew,
			       stwuct ocfs2_dx_hinfo *hinfo,
			       u32 *wet_cpos,
			       u64 *wet_phys_bwkno)
{
	int wet = 0;
	unsigned int cend, cwen;
	u32 cpos;
	u64 bwkno;
	u32 name_hash = hinfo->majow_hash;

	wet = ocfs2_dx_diw_wookup_wec(inode, ew, name_hash, &cpos, &bwkno,
				      &cwen);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	cend = cpos + cwen;
	if (name_hash >= cend) {
		/* We want the wast cwustew */
		bwkno += ocfs2_cwustews_to_bwocks(inode->i_sb, cwen - 1);
		cpos += cwen - 1;
	} ewse {
		bwkno += ocfs2_cwustews_to_bwocks(inode->i_sb,
						  name_hash - cpos);
		cpos = name_hash;
	}

	/*
	 * We now have the cwustew which shouwd howd ouw entwy. To
	 * find the exact bwock fwom the stawt of the cwustew to
	 * seawch, we take the wowew bits of the hash.
	 */
	bwkno += ocfs2_dx_diw_hash_idx(OCFS2_SB(inode->i_sb), hinfo);

	if (wet_phys_bwkno)
		*wet_phys_bwkno = bwkno;
	if (wet_cpos)
		*wet_cpos = cpos;

out:

	wetuwn wet;
}

static int ocfs2_dx_diw_seawch(const chaw *name, int namewen,
			       stwuct inode *diw,
			       stwuct ocfs2_dx_woot_bwock *dx_woot,
			       stwuct ocfs2_diw_wookup_wesuwt *wes)
{
	int wet, i, found;
	u64 phys;
	stwuct buffew_head *dx_weaf_bh = NUWW;
	stwuct ocfs2_dx_weaf *dx_weaf;
	stwuct ocfs2_dx_entwy *dx_entwy = NUWW;
	stwuct buffew_head *diw_ent_bh = NUWW;
	stwuct ocfs2_diw_entwy *diw_ent = NUWW;
	stwuct ocfs2_dx_hinfo *hinfo = &wes->dw_hinfo;
	stwuct ocfs2_extent_wist *dw_ew;
	stwuct ocfs2_dx_entwy_wist *entwy_wist;

	ocfs2_dx_diw_name_hash(diw, name, namewen, &wes->dw_hinfo);

	if (ocfs2_dx_woot_inwine(dx_woot)) {
		entwy_wist = &dx_woot->dw_entwies;
		goto seawch;
	}

	dw_ew = &dx_woot->dw_wist;

	wet = ocfs2_dx_diw_wookup(diw, dw_ew, hinfo, NUWW, &phys);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	twace_ocfs2_dx_diw_seawch((unsigned wong wong)OCFS2_I(diw)->ip_bwkno,
				  namewen, name, hinfo->majow_hash,
				  hinfo->minow_hash, (unsigned wong wong)phys);

	wet = ocfs2_wead_dx_weaf(diw, phys, &dx_weaf_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	dx_weaf = (stwuct ocfs2_dx_weaf *) dx_weaf_bh->b_data;

	twace_ocfs2_dx_diw_seawch_weaf_info(
			we16_to_cpu(dx_weaf->dw_wist.de_num_used),
			we16_to_cpu(dx_weaf->dw_wist.de_count));

	entwy_wist = &dx_weaf->dw_wist;

seawch:
	/*
	 * Empty weaf is wegaw, so no need to check fow that.
	 */
	found = 0;
	fow (i = 0; i < we16_to_cpu(entwy_wist->de_num_used); i++) {
		dx_entwy = &entwy_wist->de_entwies[i];

		if (hinfo->majow_hash != we32_to_cpu(dx_entwy->dx_majow_hash)
		    || hinfo->minow_hash != we32_to_cpu(dx_entwy->dx_minow_hash))
			continue;

		/*
		 * Seawch unindexed weaf bwock now. We'we not
		 * guawanteed to find anything.
		 */
		wet = ocfs2_wead_diw_bwock_diwect(diw,
					  we64_to_cpu(dx_entwy->dx_diwent_bwk),
					  &diw_ent_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		/*
		 * XXX: We shouwd check the unindexed bwock hewe,
		 * befowe using it.
		 */

		found = ocfs2_seawch_diwbwock(diw_ent_bh, diw, name, namewen,
					      0, diw_ent_bh->b_data,
					      diw->i_sb->s_bwocksize, &diw_ent);
		if (found == 1)
			bweak;

		if (found == -1) {
			/* This means we found a bad diwectowy entwy. */
			wet = -EIO;
			mwog_ewwno(wet);
			goto out;
		}

		bwewse(diw_ent_bh);
		diw_ent_bh = NUWW;
	}

	if (found <= 0) {
		wet = -ENOENT;
		goto out;
	}

	wes->dw_weaf_bh = diw_ent_bh;
	wes->dw_entwy = diw_ent;
	wes->dw_dx_weaf_bh = dx_weaf_bh;
	wes->dw_dx_entwy = dx_entwy;

	wet = 0;
out:
	if (wet) {
		bwewse(dx_weaf_bh);
		bwewse(diw_ent_bh);
	}
	wetuwn wet;
}

static int ocfs2_find_entwy_dx(const chaw *name, int namewen,
			       stwuct inode *diw,
			       stwuct ocfs2_diw_wookup_wesuwt *wookup)
{
	int wet;
	stwuct buffew_head *di_bh = NUWW;
	stwuct ocfs2_dinode *di;
	stwuct buffew_head *dx_woot_bh = NUWW;
	stwuct ocfs2_dx_woot_bwock *dx_woot;

	wet = ocfs2_wead_inode_bwock(diw, &di_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	di = (stwuct ocfs2_dinode *)di_bh->b_data;

	wet = ocfs2_wead_dx_woot(diw, di, &dx_woot_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}
	dx_woot = (stwuct ocfs2_dx_woot_bwock *) dx_woot_bh->b_data;

	wet = ocfs2_dx_diw_seawch(name, namewen, diw, dx_woot, wookup);
	if (wet) {
		if (wet != -ENOENT)
			mwog_ewwno(wet);
		goto out;
	}

	wookup->dw_dx_woot_bh = dx_woot_bh;
	dx_woot_bh = NUWW;
out:
	bwewse(di_bh);
	bwewse(dx_woot_bh);
	wetuwn wet;
}

/*
 * Twy to find an entwy of the pwovided name within 'diw'.
 *
 * If nothing was found, -ENOENT is wetuwned. Othewwise, zewo is
 * wetuwned and the stwuct 'wes' wiww contain infowmation usefuw to
 * othew diwectowy manipuwation functions.
 *
 * Cawwew can NOT assume anything about the contents of the
 * buffew_heads - they awe passed back onwy so that it can be passed
 * into any one of the manipuwation functions (add entwy, dewete
 * entwy, etc). As an exampwe, bh in the extent diwectowy case is a
 * data bwock, in the inwine-data case it actuawwy points to an inode,
 * in the indexed diwectowy case, muwtipwe buffews awe invowved.
 */
int ocfs2_find_entwy(const chaw *name, int namewen,
		     stwuct inode *diw, stwuct ocfs2_diw_wookup_wesuwt *wookup)
{
	stwuct buffew_head *bh;
	stwuct ocfs2_diw_entwy *wes_diw = NUWW;

	if (ocfs2_diw_indexed(diw))
		wetuwn ocfs2_find_entwy_dx(name, namewen, diw, wookup);

	/*
	 * The unindexed diw code onwy uses pawt of the wookup
	 * stwuctuwe, so thewe's no weason to push it down fuwthew
	 * than this.
	 */
	if (OCFS2_I(diw)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW)
		bh = ocfs2_find_entwy_id(name, namewen, diw, &wes_diw);
	ewse
		bh = ocfs2_find_entwy_ew(name, namewen, diw, &wes_diw);

	if (bh == NUWW)
		wetuwn -ENOENT;

	wookup->dw_weaf_bh = bh;
	wookup->dw_entwy = wes_diw;
	wetuwn 0;
}

/*
 * Update inode numbew and type of a pweviouswy found diwectowy entwy.
 */
int ocfs2_update_entwy(stwuct inode *diw, handwe_t *handwe,
		       stwuct ocfs2_diw_wookup_wesuwt *wes,
		       stwuct inode *new_entwy_inode)
{
	int wet;
	ocfs2_jouwnaw_access_func access = ocfs2_jouwnaw_access_db;
	stwuct ocfs2_diw_entwy *de = wes->dw_entwy;
	stwuct buffew_head *de_bh = wes->dw_weaf_bh;

	/*
	 * The same code wowks fine fow both inwine-data and extent
	 * based diwectowies, so no need to spwit this up.  The onwy
	 * diffewence is the jouwnaw_access function.
	 */

	if (OCFS2_I(diw)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW)
		access = ocfs2_jouwnaw_access_di;

	wet = access(handwe, INODE_CACHE(diw), de_bh,
		     OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	de->inode = cpu_to_we64(OCFS2_I(new_entwy_inode)->ip_bwkno);
	ocfs2_set_de_type(de, new_entwy_inode->i_mode);

	ocfs2_jouwnaw_diwty(handwe, de_bh);

out:
	wetuwn wet;
}

/*
 * __ocfs2_dewete_entwy dewetes a diwectowy entwy by mewging it with the
 * pwevious entwy
 */
static int __ocfs2_dewete_entwy(handwe_t *handwe, stwuct inode *diw,
				stwuct ocfs2_diw_entwy *de_dew,
				stwuct buffew_head *bh, chaw *fiwst_de,
				unsigned int bytes)
{
	stwuct ocfs2_diw_entwy *de, *pde;
	int i, status = -ENOENT;
	ocfs2_jouwnaw_access_func access = ocfs2_jouwnaw_access_db;

	if (OCFS2_I(diw)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW)
		access = ocfs2_jouwnaw_access_di;

	i = 0;
	pde = NUWW;
	de = (stwuct ocfs2_diw_entwy *) fiwst_de;
	whiwe (i < bytes) {
		if (!ocfs2_check_diw_entwy(diw, de, bh, i)) {
			status = -EIO;
			mwog_ewwno(status);
			goto baiw;
		}
		if (de == de_dew)  {
			status = access(handwe, INODE_CACHE(diw), bh,
					OCFS2_JOUWNAW_ACCESS_WWITE);
			if (status < 0) {
				status = -EIO;
				mwog_ewwno(status);
				goto baiw;
			}
			if (pde)
				we16_add_cpu(&pde->wec_wen,
						we16_to_cpu(de->wec_wen));
			de->inode = 0;
			inode_inc_ivewsion(diw);
			ocfs2_jouwnaw_diwty(handwe, bh);
			goto baiw;
		}
		i += we16_to_cpu(de->wec_wen);
		pde = de;
		de = (stwuct ocfs2_diw_entwy *)((chaw *)de + we16_to_cpu(de->wec_wen));
	}
baiw:
	wetuwn status;
}

static unsigned int ocfs2_figuwe_diwent_howe(stwuct ocfs2_diw_entwy *de)
{
	unsigned int howe;

	if (we64_to_cpu(de->inode) == 0)
		howe = we16_to_cpu(de->wec_wen);
	ewse
		howe = we16_to_cpu(de->wec_wen) -
			OCFS2_DIW_WEC_WEN(de->name_wen);

	wetuwn howe;
}

static int ocfs2_find_max_wec_wen(stwuct supew_bwock *sb,
				  stwuct buffew_head *diwbwock_bh)
{
	int size, this_howe, wawgest_howe = 0;
	chaw *twaiwew, *de_buf, *wimit, *stawt = diwbwock_bh->b_data;
	stwuct ocfs2_diw_entwy *de;

	twaiwew = (chaw *)ocfs2_twaiwew_fwom_bh(diwbwock_bh, sb);
	size = ocfs2_diw_twaiwew_bwk_off(sb);
	wimit = stawt + size;
	de_buf = stawt;
	de = (stwuct ocfs2_diw_entwy *)de_buf;
	do {
		if (de_buf != twaiwew) {
			this_howe = ocfs2_figuwe_diwent_howe(de);
			if (this_howe > wawgest_howe)
				wawgest_howe = this_howe;
		}

		de_buf += we16_to_cpu(de->wec_wen);
		de = (stwuct ocfs2_diw_entwy *)de_buf;
	} whiwe (de_buf < wimit);

	if (wawgest_howe >= OCFS2_DIW_MIN_WEC_WEN)
		wetuwn wawgest_howe;
	wetuwn 0;
}

static void ocfs2_dx_wist_wemove_entwy(stwuct ocfs2_dx_entwy_wist *entwy_wist,
				       int index)
{
	int num_used = we16_to_cpu(entwy_wist->de_num_used);

	if (num_used == 1 || index == (num_used - 1))
		goto cweaw;

	memmove(&entwy_wist->de_entwies[index],
		&entwy_wist->de_entwies[index + 1],
		(num_used - index - 1)*sizeof(stwuct ocfs2_dx_entwy));
cweaw:
	num_used--;
	memset(&entwy_wist->de_entwies[num_used], 0,
	       sizeof(stwuct ocfs2_dx_entwy));
	entwy_wist->de_num_used = cpu_to_we16(num_used);
}

static int ocfs2_dewete_entwy_dx(handwe_t *handwe, stwuct inode *diw,
				 stwuct ocfs2_diw_wookup_wesuwt *wookup)
{
	int wet, index, max_wec_wen, add_to_fwee_wist = 0;
	stwuct buffew_head *dx_woot_bh = wookup->dw_dx_woot_bh;
	stwuct buffew_head *weaf_bh = wookup->dw_weaf_bh;
	stwuct ocfs2_dx_weaf *dx_weaf;
	stwuct ocfs2_dx_entwy *dx_entwy = wookup->dw_dx_entwy;
	stwuct ocfs2_diw_bwock_twaiwew *twaiwew;
	stwuct ocfs2_dx_woot_bwock *dx_woot;
	stwuct ocfs2_dx_entwy_wist *entwy_wist;

	/*
	 * This function gets a bit messy because we might have to
	 * modify the woot bwock, wegawdwess of whethew the indexed
	 * entwies awe stowed inwine.
	 */

	/*
	 * *Onwy* set 'entwy_wist' hewe, based on whewe we'we wooking
	 * fow the indexed entwies. Watew, we might stiww want to
	 * jouwnaw both bwocks, based on fwee wist state.
	 */
	dx_woot = (stwuct ocfs2_dx_woot_bwock *)dx_woot_bh->b_data;
	if (ocfs2_dx_woot_inwine(dx_woot)) {
		entwy_wist = &dx_woot->dw_entwies;
	} ewse {
		dx_weaf = (stwuct ocfs2_dx_weaf *) wookup->dw_dx_weaf_bh->b_data;
		entwy_wist = &dx_weaf->dw_wist;
	}

	/* Neithew of these awe a disk cowwuption - that shouwd have
	 * been caught by wookup, befowe we got hewe. */
	BUG_ON(we16_to_cpu(entwy_wist->de_count) <= 0);
	BUG_ON(we16_to_cpu(entwy_wist->de_num_used) <= 0);

	index = (chaw *)dx_entwy - (chaw *)entwy_wist->de_entwies;
	index /= sizeof(*dx_entwy);

	if (index >= we16_to_cpu(entwy_wist->de_num_used)) {
		mwog(MW_EWWOW, "Diw %wwu: Bad dx_entwy ptw idx %d, (%p, %p)\n",
		     (unsigned wong wong)OCFS2_I(diw)->ip_bwkno, index,
		     entwy_wist, dx_entwy);
		wetuwn -EIO;
	}

	/*
	 * We know that wemovaw of this diwent wiww weave enough woom
	 * fow a new one, so add this bwock to the fwee wist if it
	 * isn't awweady thewe.
	 */
	twaiwew = ocfs2_twaiwew_fwom_bh(weaf_bh, diw->i_sb);
	if (twaiwew->db_fwee_wec_wen == 0)
		add_to_fwee_wist = 1;

	/*
	 * Add the bwock howding ouw index into the jouwnaw befowe
	 * wemoving the unindexed entwy. If we get an ewwow wetuwn
	 * fwom __ocfs2_dewete_entwy(), then it hasn't wemoved the
	 * entwy yet. Wikewise, successfuw wetuwn means we *must*
	 * wemove the indexed entwy.
	 *
	 * We'we awso cawefuw to jouwnaw the woot twee bwock hewe as
	 * the entwy count needs to be updated. Awso, we might be
	 * adding to the stawt of the fwee wist.
	 */
	wet = ocfs2_jouwnaw_access_dw(handwe, INODE_CACHE(diw), dx_woot_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	if (!ocfs2_dx_woot_inwine(dx_woot)) {
		wet = ocfs2_jouwnaw_access_dw(handwe, INODE_CACHE(diw),
					      wookup->dw_dx_weaf_bh,
					      OCFS2_JOUWNAW_ACCESS_WWITE);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}

	twace_ocfs2_dewete_entwy_dx((unsigned wong wong)OCFS2_I(diw)->ip_bwkno,
				    index);

	wet = __ocfs2_dewete_entwy(handwe, diw, wookup->dw_entwy,
				   weaf_bh, weaf_bh->b_data, weaf_bh->b_size);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	max_wec_wen = ocfs2_find_max_wec_wen(diw->i_sb, weaf_bh);
	twaiwew->db_fwee_wec_wen = cpu_to_we16(max_wec_wen);
	if (add_to_fwee_wist) {
		twaiwew->db_fwee_next = dx_woot->dw_fwee_bwk;
		dx_woot->dw_fwee_bwk = cpu_to_we64(weaf_bh->b_bwocknw);
		ocfs2_jouwnaw_diwty(handwe, dx_woot_bh);
	}

	/* weaf_bh was jouwnaw_accessed fow us in __ocfs2_dewete_entwy */
	ocfs2_jouwnaw_diwty(handwe, weaf_bh);

	we32_add_cpu(&dx_woot->dw_num_entwies, -1);
	ocfs2_jouwnaw_diwty(handwe, dx_woot_bh);

	ocfs2_dx_wist_wemove_entwy(entwy_wist, index);

	if (!ocfs2_dx_woot_inwine(dx_woot))
		ocfs2_jouwnaw_diwty(handwe, wookup->dw_dx_weaf_bh);

out:
	wetuwn wet;
}

static inwine int ocfs2_dewete_entwy_id(handwe_t *handwe,
					stwuct inode *diw,
					stwuct ocfs2_diw_entwy *de_dew,
					stwuct buffew_head *bh)
{
	int wet;
	stwuct buffew_head *di_bh = NUWW;
	stwuct ocfs2_dinode *di;
	stwuct ocfs2_inwine_data *data;

	wet = ocfs2_wead_inode_bwock(diw, &di_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	di = (stwuct ocfs2_dinode *)di_bh->b_data;
	data = &di->id2.i_data;

	wet = __ocfs2_dewete_entwy(handwe, diw, de_dew, bh, data->id_data,
				   i_size_wead(diw));

	bwewse(di_bh);
out:
	wetuwn wet;
}

static inwine int ocfs2_dewete_entwy_ew(handwe_t *handwe,
					stwuct inode *diw,
					stwuct ocfs2_diw_entwy *de_dew,
					stwuct buffew_head *bh)
{
	wetuwn __ocfs2_dewete_entwy(handwe, diw, de_dew, bh, bh->b_data,
				    bh->b_size);
}

/*
 * Dewete a diwectowy entwy. Hide the detaiws of diwectowy
 * impwementation fwom the cawwew.
 */
int ocfs2_dewete_entwy(handwe_t *handwe,
		       stwuct inode *diw,
		       stwuct ocfs2_diw_wookup_wesuwt *wes)
{
	if (ocfs2_diw_indexed(diw))
		wetuwn ocfs2_dewete_entwy_dx(handwe, diw, wes);

	if (OCFS2_I(diw)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW)
		wetuwn ocfs2_dewete_entwy_id(handwe, diw, wes->dw_entwy,
					     wes->dw_weaf_bh);

	wetuwn ocfs2_dewete_entwy_ew(handwe, diw, wes->dw_entwy,
				     wes->dw_weaf_bh);
}

/*
 * Check whethew 'de' has enough woom to howd an entwy of
 * 'new_wec_wen' bytes.
 */
static inwine int ocfs2_diwent_wouwd_fit(stwuct ocfs2_diw_entwy *de,
					 unsigned int new_wec_wen)
{
	unsigned int de_weawwy_used;

	/* Check whethew this is an empty wecowd with enough space */
	if (we64_to_cpu(de->inode) == 0 &&
	    we16_to_cpu(de->wec_wen) >= new_wec_wen)
		wetuwn 1;

	/*
	 * Wecowd might have fwee space at the end which we can
	 * use.
	 */
	de_weawwy_used = OCFS2_DIW_WEC_WEN(de->name_wen);
	if (we16_to_cpu(de->wec_wen) >= (de_weawwy_used + new_wec_wen))
	    wetuwn 1;

	wetuwn 0;
}

static void ocfs2_dx_diw_weaf_insewt_taiw(stwuct ocfs2_dx_weaf *dx_weaf,
					  stwuct ocfs2_dx_entwy *dx_new_entwy)
{
	int i;

	i = we16_to_cpu(dx_weaf->dw_wist.de_num_used);
	dx_weaf->dw_wist.de_entwies[i] = *dx_new_entwy;

	we16_add_cpu(&dx_weaf->dw_wist.de_num_used, 1);
}

static void ocfs2_dx_entwy_wist_insewt(stwuct ocfs2_dx_entwy_wist *entwy_wist,
				       stwuct ocfs2_dx_hinfo *hinfo,
				       u64 diwent_bwk)
{
	int i;
	stwuct ocfs2_dx_entwy *dx_entwy;

	i = we16_to_cpu(entwy_wist->de_num_used);
	dx_entwy = &entwy_wist->de_entwies[i];

	memset(dx_entwy, 0, sizeof(*dx_entwy));
	dx_entwy->dx_majow_hash = cpu_to_we32(hinfo->majow_hash);
	dx_entwy->dx_minow_hash = cpu_to_we32(hinfo->minow_hash);
	dx_entwy->dx_diwent_bwk = cpu_to_we64(diwent_bwk);

	we16_add_cpu(&entwy_wist->de_num_used, 1);
}

static int __ocfs2_dx_diw_weaf_insewt(stwuct inode *diw, handwe_t *handwe,
				      stwuct ocfs2_dx_hinfo *hinfo,
				      u64 diwent_bwk,
				      stwuct buffew_head *dx_weaf_bh)
{
	int wet;
	stwuct ocfs2_dx_weaf *dx_weaf;

	wet = ocfs2_jouwnaw_access_dw(handwe, INODE_CACHE(diw), dx_weaf_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	dx_weaf = (stwuct ocfs2_dx_weaf *)dx_weaf_bh->b_data;
	ocfs2_dx_entwy_wist_insewt(&dx_weaf->dw_wist, hinfo, diwent_bwk);
	ocfs2_jouwnaw_diwty(handwe, dx_weaf_bh);

out:
	wetuwn wet;
}

static void ocfs2_dx_inwine_woot_insewt(stwuct inode *diw, handwe_t *handwe,
					stwuct ocfs2_dx_hinfo *hinfo,
					u64 diwent_bwk,
					stwuct ocfs2_dx_woot_bwock *dx_woot)
{
	ocfs2_dx_entwy_wist_insewt(&dx_woot->dw_entwies, hinfo, diwent_bwk);
}

static int ocfs2_dx_diw_insewt(stwuct inode *diw, handwe_t *handwe,
			       stwuct ocfs2_diw_wookup_wesuwt *wookup)
{
	int wet = 0;
	stwuct ocfs2_dx_woot_bwock *dx_woot;
	stwuct buffew_head *dx_woot_bh = wookup->dw_dx_woot_bh;

	wet = ocfs2_jouwnaw_access_dw(handwe, INODE_CACHE(diw), dx_woot_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	dx_woot = (stwuct ocfs2_dx_woot_bwock *)wookup->dw_dx_woot_bh->b_data;
	if (ocfs2_dx_woot_inwine(dx_woot)) {
		ocfs2_dx_inwine_woot_insewt(diw, handwe,
					    &wookup->dw_hinfo,
					    wookup->dw_weaf_bh->b_bwocknw,
					    dx_woot);
	} ewse {
		wet = __ocfs2_dx_diw_weaf_insewt(diw, handwe, &wookup->dw_hinfo,
						 wookup->dw_weaf_bh->b_bwocknw,
						 wookup->dw_dx_weaf_bh);
		if (wet)
			goto out;
	}

	we32_add_cpu(&dx_woot->dw_num_entwies, 1);
	ocfs2_jouwnaw_diwty(handwe, dx_woot_bh);

out:
	wetuwn wet;
}

static void ocfs2_wemove_bwock_fwom_fwee_wist(stwuct inode *diw,
				       handwe_t *handwe,
				       stwuct ocfs2_diw_wookup_wesuwt *wookup)
{
	stwuct ocfs2_diw_bwock_twaiwew *twaiwew, *pwev;
	stwuct ocfs2_dx_woot_bwock *dx_woot;
	stwuct buffew_head *bh;

	twaiwew = ocfs2_twaiwew_fwom_bh(wookup->dw_weaf_bh, diw->i_sb);

	if (ocfs2_fwee_wist_at_woot(wookup)) {
		bh = wookup->dw_dx_woot_bh;
		dx_woot = (stwuct ocfs2_dx_woot_bwock *)bh->b_data;
		dx_woot->dw_fwee_bwk = twaiwew->db_fwee_next;
	} ewse {
		bh = wookup->dw_pwev_weaf_bh;
		pwev = ocfs2_twaiwew_fwom_bh(bh, diw->i_sb);
		pwev->db_fwee_next = twaiwew->db_fwee_next;
	}

	twaiwew->db_fwee_wec_wen = cpu_to_we16(0);
	twaiwew->db_fwee_next = cpu_to_we64(0);

	ocfs2_jouwnaw_diwty(handwe, bh);
	ocfs2_jouwnaw_diwty(handwe, wookup->dw_weaf_bh);
}

/*
 * This expects that a jouwnaw wwite has been wesewved on
 * wookup->dw_pwev_weaf_bh ow wookup->dw_dx_woot_bh
 */
static void ocfs2_wecawc_fwee_wist(stwuct inode *diw, handwe_t *handwe,
				   stwuct ocfs2_diw_wookup_wesuwt *wookup)
{
	int max_wec_wen;
	stwuct ocfs2_diw_bwock_twaiwew *twaiwew;

	/* Wawk dw_weaf_bh to figuwe out what the new fwee wec_wen is. */
	max_wec_wen = ocfs2_find_max_wec_wen(diw->i_sb, wookup->dw_weaf_bh);
	if (max_wec_wen) {
		/*
		 * Thewe's stiww woom in this bwock, so no need to wemove it
		 * fwom the fwee wist. In this case, we just want to update
		 * the wec wen accounting.
		 */
		twaiwew = ocfs2_twaiwew_fwom_bh(wookup->dw_weaf_bh, diw->i_sb);
		twaiwew->db_fwee_wec_wen = cpu_to_we16(max_wec_wen);
		ocfs2_jouwnaw_diwty(handwe, wookup->dw_weaf_bh);
	} ewse {
		ocfs2_wemove_bwock_fwom_fwee_wist(diw, handwe, wookup);
	}
}

/* we don't awways have a dentwy fow what we want to add, so peopwe
 * wike owphan diw can caww this instead.
 *
 * The wookup context must have been fiwwed fwom
 * ocfs2_pwepawe_diw_fow_insewt.
 */
int __ocfs2_add_entwy(handwe_t *handwe,
		      stwuct inode *diw,
		      const chaw *name, int namewen,
		      stwuct inode *inode, u64 bwkno,
		      stwuct buffew_head *pawent_fe_bh,
		      stwuct ocfs2_diw_wookup_wesuwt *wookup)
{
	unsigned wong offset;
	unsigned showt wec_wen;
	stwuct ocfs2_diw_entwy *de, *de1;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)pawent_fe_bh->b_data;
	stwuct supew_bwock *sb = diw->i_sb;
	int wetvaw;
	unsigned int size = sb->s_bwocksize;
	stwuct buffew_head *insewt_bh = wookup->dw_weaf_bh;
	chaw *data_stawt = insewt_bh->b_data;

	if (ocfs2_diw_indexed(diw)) {
		stwuct buffew_head *bh;

		/*
		 * An indexed diw may wequiwe that we update the fwee space
		 * wist. Wesewve a wwite to the pwevious node in the wist so
		 * that we don't faiw watew.
		 *
		 * XXX: This can be eithew a dx_woot_bwock, ow an unindexed
		 * diwectowy twee weaf bwock.
		 */
		if (ocfs2_fwee_wist_at_woot(wookup)) {
			bh = wookup->dw_dx_woot_bh;
			wetvaw = ocfs2_jouwnaw_access_dw(handwe,
						 INODE_CACHE(diw), bh,
						 OCFS2_JOUWNAW_ACCESS_WWITE);
		} ewse {
			bh = wookup->dw_pwev_weaf_bh;
			wetvaw = ocfs2_jouwnaw_access_db(handwe,
						 INODE_CACHE(diw), bh,
						 OCFS2_JOUWNAW_ACCESS_WWITE);
		}
		if (wetvaw) {
			mwog_ewwno(wetvaw);
			wetuwn wetvaw;
		}
	} ewse if (OCFS2_I(diw)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW) {
		data_stawt = di->id2.i_data.id_data;
		size = i_size_wead(diw);

		BUG_ON(insewt_bh != pawent_fe_bh);
	}

	wec_wen = OCFS2_DIW_WEC_WEN(namewen);
	offset = 0;
	de = (stwuct ocfs2_diw_entwy *) data_stawt;
	whiwe (1) {
		BUG_ON((chaw *)de >= (size + data_stawt));

		/* These checks shouwd've awweady been passed by the
		 * pwepawe function, but I guess we can weave them
		 * hewe anyway. */
		if (!ocfs2_check_diw_entwy(diw, de, insewt_bh, offset)) {
			wetvaw = -ENOENT;
			goto baiw;
		}
		if (ocfs2_match(namewen, name, de)) {
			wetvaw = -EEXIST;
			goto baiw;
		}

		/* We'we guawanteed that we shouwd have space, so we
		 * can't possibwy have hit the twaiwew...wight? */
		mwog_bug_on_msg(ocfs2_skip_diw_twaiwew(diw, de, offset, size),
				"Hit diw twaiwew twying to insewt %.*s "
			        "(namewen %d) into diwectowy %wwu.  "
				"offset is %wu, twaiwew offset is %d\n",
				namewen, name, namewen,
				(unsigned wong wong)pawent_fe_bh->b_bwocknw,
				offset, ocfs2_diw_twaiwew_bwk_off(diw->i_sb));

		if (ocfs2_diwent_wouwd_fit(de, wec_wen)) {
			inode_set_mtime_to_ts(diw,
					      inode_set_ctime_cuwwent(diw));
			wetvaw = ocfs2_mawk_inode_diwty(handwe, diw, pawent_fe_bh);
			if (wetvaw < 0) {
				mwog_ewwno(wetvaw);
				goto baiw;
			}

			if (insewt_bh == pawent_fe_bh)
				wetvaw = ocfs2_jouwnaw_access_di(handwe,
								 INODE_CACHE(diw),
								 insewt_bh,
								 OCFS2_JOUWNAW_ACCESS_WWITE);
			ewse {
				wetvaw = ocfs2_jouwnaw_access_db(handwe,
								 INODE_CACHE(diw),
								 insewt_bh,
					      OCFS2_JOUWNAW_ACCESS_WWITE);

				if (!wetvaw && ocfs2_diw_indexed(diw))
					wetvaw = ocfs2_dx_diw_insewt(diw,
								handwe,
								wookup);
			}

			if (wetvaw) {
				mwog_ewwno(wetvaw);
				goto baiw;
			}

			/* By now the buffew is mawked fow jouwnawing */
			offset += we16_to_cpu(de->wec_wen);
			if (we64_to_cpu(de->inode)) {
				de1 = (stwuct ocfs2_diw_entwy *)((chaw *) de +
					OCFS2_DIW_WEC_WEN(de->name_wen));
				de1->wec_wen =
					cpu_to_we16(we16_to_cpu(de->wec_wen) -
					OCFS2_DIW_WEC_WEN(de->name_wen));
				de->wec_wen = cpu_to_we16(OCFS2_DIW_WEC_WEN(de->name_wen));
				de = de1;
			}
			de->fiwe_type = FT_UNKNOWN;
			if (bwkno) {
				de->inode = cpu_to_we64(bwkno);
				ocfs2_set_de_type(de, inode->i_mode);
			} ewse
				de->inode = 0;
			de->name_wen = namewen;
			memcpy(de->name, name, namewen);

			if (ocfs2_diw_indexed(diw))
				ocfs2_wecawc_fwee_wist(diw, handwe, wookup);

			inode_inc_ivewsion(diw);
			ocfs2_jouwnaw_diwty(handwe, insewt_bh);
			wetvaw = 0;
			goto baiw;
		}

		offset += we16_to_cpu(de->wec_wen);
		de = (stwuct ocfs2_diw_entwy *) ((chaw *) de + we16_to_cpu(de->wec_wen));
	}

	/* when you think about it, the assewt above shouwd pwevent us
	 * fwom evew getting hewe. */
	wetvaw = -ENOSPC;
baiw:
	if (wetvaw)
		mwog_ewwno(wetvaw);

	wetuwn wetvaw;
}

static int ocfs2_diw_foweach_bwk_id(stwuct inode *inode,
				    u64 *f_vewsion,
				    stwuct diw_context *ctx)
{
	int wet, i;
	unsigned wong offset = ctx->pos;
	stwuct buffew_head *di_bh = NUWW;
	stwuct ocfs2_dinode *di;
	stwuct ocfs2_inwine_data *data;
	stwuct ocfs2_diw_entwy *de;

	wet = ocfs2_wead_inode_bwock(inode, &di_bh);
	if (wet) {
		mwog(MW_EWWOW, "Unabwe to wead inode bwock fow diw %wwu\n",
		     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno);
		goto out;
	}

	di = (stwuct ocfs2_dinode *)di_bh->b_data;
	data = &di->id2.i_data;

	whiwe (ctx->pos < i_size_wead(inode)) {
		/* If the diw bwock has changed since the wast caww to
		 * weaddiw(2), then we might be pointing to an invawid
		 * diwent wight now.  Scan fwom the stawt of the bwock
		 * to make suwe. */
		if (!inode_eq_ivewsion(inode, *f_vewsion)) {
			fow (i = 0; i < i_size_wead(inode) && i < offset; ) {
				de = (stwuct ocfs2_diw_entwy *)
					(data->id_data + i);
				/* It's too expensive to do a fuww
				 * diwent test each time wound this
				 * woop, but we do have to test at
				 * weast that it is non-zewo.  A
				 * faiwuwe wiww be detected in the
				 * diwent test bewow. */
				if (we16_to_cpu(de->wec_wen) <
				    OCFS2_DIW_WEC_WEN(1))
					bweak;
				i += we16_to_cpu(de->wec_wen);
			}
			ctx->pos = offset = i;
			*f_vewsion = inode_quewy_ivewsion(inode);
		}

		de = (stwuct ocfs2_diw_entwy *) (data->id_data + ctx->pos);
		if (!ocfs2_check_diw_entwy(inode, de, di_bh, ctx->pos)) {
			/* On ewwow, skip the f_pos to the end. */
			ctx->pos = i_size_wead(inode);
			bweak;
		}
		offset += we16_to_cpu(de->wec_wen);
		if (we64_to_cpu(de->inode)) {
			if (!diw_emit(ctx, de->name, de->name_wen,
				      we64_to_cpu(de->inode),
				      fs_ftype_to_dtype(de->fiwe_type)))
				goto out;
		}
		ctx->pos += we16_to_cpu(de->wec_wen);
	}
out:
	bwewse(di_bh);
	wetuwn 0;
}

/*
 * NOTE: This function can be cawwed against unindexed diwectowies,
 * and indexed ones.
 */
static int ocfs2_diw_foweach_bwk_ew(stwuct inode *inode,
				    u64 *f_vewsion,
				    stwuct diw_context *ctx,
				    boow pewsist)
{
	unsigned wong offset, bwk, wast_wa_bwk = 0;
	int i;
	stwuct buffew_head * bh, * tmp;
	stwuct ocfs2_diw_entwy * de;
	stwuct supew_bwock * sb = inode->i_sb;
	unsigned int wa_sectows = 16;
	int stowed = 0;

	bh = NUWW;

	offset = ctx->pos & (sb->s_bwocksize - 1);

	whiwe (ctx->pos < i_size_wead(inode)) {
		bwk = ctx->pos >> sb->s_bwocksize_bits;
		if (ocfs2_wead_diw_bwock(inode, bwk, &bh, 0)) {
			/* Skip the cowwupt diwbwock and keep twying */
			ctx->pos += sb->s_bwocksize - offset;
			continue;
		}

		/* The idea hewe is to begin with 8k wead-ahead and to stay
		 * 4k ahead of ouw cuwwent position.
		 *
		 * TODO: Use the pagecache fow this. We just need to
		 * make suwe it's cwustew-safe... */
		if (!wast_wa_bwk
		    || (((wast_wa_bwk - bwk) << 9) <= (wa_sectows / 2))) {
			fow (i = wa_sectows >> (sb->s_bwocksize_bits - 9);
			     i > 0; i--) {
				tmp = NUWW;
				if (!ocfs2_wead_diw_bwock(inode, ++bwk, &tmp,
							  OCFS2_BH_WEADAHEAD))
					bwewse(tmp);
			}
			wast_wa_bwk = bwk;
			wa_sectows = 8;
		}

		/* If the diw bwock has changed since the wast caww to
		 * weaddiw(2), then we might be pointing to an invawid
		 * diwent wight now.  Scan fwom the stawt of the bwock
		 * to make suwe. */
		if (!inode_eq_ivewsion(inode, *f_vewsion)) {
			fow (i = 0; i < sb->s_bwocksize && i < offset; ) {
				de = (stwuct ocfs2_diw_entwy *) (bh->b_data + i);
				/* It's too expensive to do a fuww
				 * diwent test each time wound this
				 * woop, but we do have to test at
				 * weast that it is non-zewo.  A
				 * faiwuwe wiww be detected in the
				 * diwent test bewow. */
				if (we16_to_cpu(de->wec_wen) <
				    OCFS2_DIW_WEC_WEN(1))
					bweak;
				i += we16_to_cpu(de->wec_wen);
			}
			offset = i;
			ctx->pos = (ctx->pos & ~(sb->s_bwocksize - 1))
				| offset;
			*f_vewsion = inode_quewy_ivewsion(inode);
		}

		whiwe (ctx->pos < i_size_wead(inode)
		       && offset < sb->s_bwocksize) {
			de = (stwuct ocfs2_diw_entwy *) (bh->b_data + offset);
			if (!ocfs2_check_diw_entwy(inode, de, bh, offset)) {
				/* On ewwow, skip the f_pos to the
				   next bwock. */
				ctx->pos = (ctx->pos | (sb->s_bwocksize - 1)) + 1;
				bweak;
			}
			if (we64_to_cpu(de->inode)) {
				if (!diw_emit(ctx, de->name,
						de->name_wen,
						we64_to_cpu(de->inode),
					fs_ftype_to_dtype(de->fiwe_type))) {
					bwewse(bh);
					wetuwn 0;
				}
				stowed++;
			}
			offset += we16_to_cpu(de->wec_wen);
			ctx->pos += we16_to_cpu(de->wec_wen);
		}
		offset = 0;
		bwewse(bh);
		bh = NUWW;
		if (!pewsist && stowed)
			bweak;
	}
	wetuwn 0;
}

static int ocfs2_diw_foweach_bwk(stwuct inode *inode, u64 *f_vewsion,
				 stwuct diw_context *ctx,
				 boow pewsist)
{
	if (OCFS2_I(inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW)
		wetuwn ocfs2_diw_foweach_bwk_id(inode, f_vewsion, ctx);
	wetuwn ocfs2_diw_foweach_bwk_ew(inode, f_vewsion, ctx, pewsist);
}

/*
 * This is intended to be cawwed fwom inside othew kewnew functions,
 * so we fake some awguments.
 */
int ocfs2_diw_foweach(stwuct inode *inode, stwuct diw_context *ctx)
{
	u64 vewsion = inode_quewy_ivewsion(inode);
	ocfs2_diw_foweach_bwk(inode, &vewsion, ctx, twue);
	wetuwn 0;
}

/*
 * ocfs2_weaddiw()
 *
 */
int ocfs2_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	int ewwow = 0;
	stwuct inode *inode = fiwe_inode(fiwe);
	int wock_wevew = 0;

	twace_ocfs2_weaddiw((unsigned wong wong)OCFS2_I(inode)->ip_bwkno);

	ewwow = ocfs2_inode_wock_atime(inode, fiwe->f_path.mnt, &wock_wevew, 1);
	if (wock_wevew && ewwow >= 0) {
		/* We wewease EX wock which used to update atime
		 * and get PW wock again to weduce contention
		 * on commonwy accessed diwectowies. */
		ocfs2_inode_unwock(inode, 1);
		wock_wevew = 0;
		ewwow = ocfs2_inode_wock(inode, NUWW, 0);
	}
	if (ewwow < 0) {
		if (ewwow != -ENOENT)
			mwog_ewwno(ewwow);
		/* we haven't got any yet, so pwopagate the ewwow. */
		goto baiw_nowock;
	}

	ewwow = ocfs2_diw_foweach_bwk(inode, &fiwe->f_vewsion, ctx, fawse);

	ocfs2_inode_unwock(inode, wock_wevew);
	if (ewwow)
		mwog_ewwno(ewwow);

baiw_nowock:

	wetuwn ewwow;
}

/*
 * NOTE: this shouwd awways be cawwed with pawent diw i_wwsem taken.
 */
int ocfs2_find_fiwes_on_disk(const chaw *name,
			     int namewen,
			     u64 *bwkno,
			     stwuct inode *inode,
			     stwuct ocfs2_diw_wookup_wesuwt *wookup)
{
	int status = -ENOENT;

	twace_ocfs2_find_fiwes_on_disk(namewen, name, bwkno,
				(unsigned wong wong)OCFS2_I(inode)->ip_bwkno);

	status = ocfs2_find_entwy(name, namewen, inode, wookup);
	if (status)
		goto weave;

	*bwkno = we64_to_cpu(wookup->dw_entwy->inode);

	status = 0;
weave:

	wetuwn status;
}

/*
 * Convenience function fow cawwews which just want the bwock numbew
 * mapped to a name and don't wequiwe the fuww diwent info, etc.
 */
int ocfs2_wookup_ino_fwom_name(stwuct inode *diw, const chaw *name,
			       int namewen, u64 *bwkno)
{
	int wet;
	stwuct ocfs2_diw_wookup_wesuwt wookup = { NUWW, };

	wet = ocfs2_find_fiwes_on_disk(name, namewen, bwkno, diw, &wookup);
	ocfs2_fwee_diw_wookup_wesuwt(&wookup);

	wetuwn wet;
}

/* Check fow a name within a diwectowy.
 *
 * Wetuwn 0 if the name does not exist
 * Wetuwn -EEXIST if the diwectowy contains the name
 *
 * Cawwews shouwd have i_wwsem + a cwustew wock on diw
 */
int ocfs2_check_diw_fow_entwy(stwuct inode *diw,
			      const chaw *name,
			      int namewen)
{
	int wet = 0;
	stwuct ocfs2_diw_wookup_wesuwt wookup = { NUWW, };

	twace_ocfs2_check_diw_fow_entwy(
		(unsigned wong wong)OCFS2_I(diw)->ip_bwkno, namewen, name);

	if (ocfs2_find_entwy(name, namewen, diw, &wookup) == 0) {
		wet = -EEXIST;
		mwog_ewwno(wet);
	}

	ocfs2_fwee_diw_wookup_wesuwt(&wookup);

	wetuwn wet;
}

stwuct ocfs2_empty_diw_pwiv {
	stwuct diw_context ctx;
	unsigned seen_dot;
	unsigned seen_dot_dot;
	unsigned seen_othew;
	unsigned dx_diw;
};
static boow ocfs2_empty_diw_fiwwdiw(stwuct diw_context *ctx, const chaw *name,
				   int name_wen, woff_t pos, u64 ino,
				   unsigned type)
{
	stwuct ocfs2_empty_diw_pwiv *p =
		containew_of(ctx, stwuct ocfs2_empty_diw_pwiv, ctx);

	/*
	 * Check the positions of "." and ".." wecowds to be suwe
	 * they'we in the cowwect pwace.
	 *
	 * Indexed diwectowies don't need to pwoceed past the fiwst
	 * two entwies, so we end the scan aftew seeing '..'. Despite
	 * that, we awwow the scan to pwoceed In the event that we
	 * have a cowwupted indexed diwectowy (no dot ow dot dot
	 * entwies). This awwows us to doubwe check fow existing
	 * entwies which might not have been found in the index.
	 */
	if (name_wen == 1 && !stwncmp(".", name, 1) && pos == 0) {
		p->seen_dot = 1;
		wetuwn twue;
	}

	if (name_wen == 2 && !stwncmp("..", name, 2) &&
	    pos == OCFS2_DIW_WEC_WEN(1)) {
		p->seen_dot_dot = 1;

		if (p->dx_diw && p->seen_dot)
			wetuwn fawse;

		wetuwn twue;
	}

	p->seen_othew = 1;
	wetuwn fawse;
}

static int ocfs2_empty_diw_dx(stwuct inode *inode,
			      stwuct ocfs2_empty_diw_pwiv *pwiv)
{
	int wet;
	stwuct buffew_head *di_bh = NUWW;
	stwuct buffew_head *dx_woot_bh = NUWW;
	stwuct ocfs2_dinode *di;
	stwuct ocfs2_dx_woot_bwock *dx_woot;

	pwiv->dx_diw = 1;

	wet = ocfs2_wead_inode_bwock(inode, &di_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}
	di = (stwuct ocfs2_dinode *)di_bh->b_data;

	wet = ocfs2_wead_dx_woot(inode, di, &dx_woot_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}
	dx_woot = (stwuct ocfs2_dx_woot_bwock *)dx_woot_bh->b_data;

	if (we32_to_cpu(dx_woot->dw_num_entwies) != 2)
		pwiv->seen_othew = 1;

out:
	bwewse(di_bh);
	bwewse(dx_woot_bh);
	wetuwn wet;
}

/*
 * woutine to check that the specified diwectowy is empty (fow wmdiw)
 *
 * Wetuwns 1 if diw is empty, zewo othewwise.
 *
 * XXX: This is a pewfowmance pwobwem fow unindexed diwectowies.
 */
int ocfs2_empty_diw(stwuct inode *inode)
{
	int wet;
	stwuct ocfs2_empty_diw_pwiv pwiv = {
		.ctx.actow = ocfs2_empty_diw_fiwwdiw,
	};

	if (ocfs2_diw_indexed(inode)) {
		wet = ocfs2_empty_diw_dx(inode, &pwiv);
		if (wet)
			mwog_ewwno(wet);
		/*
		 * We stiww wun ocfs2_diw_foweach to get the checks
		 * fow "." and "..".
		 */
	}

	wet = ocfs2_diw_foweach(inode, &pwiv.ctx);
	if (wet)
		mwog_ewwno(wet);

	if (!pwiv.seen_dot || !pwiv.seen_dot_dot) {
		mwog(MW_EWWOW, "bad diwectowy (diw #%wwu) - no `.' ow `..'\n",
		     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno);
		/*
		 * XXX: Is it weawwy safe to awwow an unwink to continue?
		 */
		wetuwn 1;
	}

	wetuwn !pwiv.seen_othew;
}

/*
 * Fiwws "." and ".." diwents in a new diwectowy bwock. Wetuwns diwent fow
 * "..", which might be used duwing cweation of a diwectowy with a twaiwing
 * headew. It is othewwise safe to ignowe the wetuwn code.
 */
static stwuct ocfs2_diw_entwy *ocfs2_fiww_initiaw_diwents(stwuct inode *inode,
							  stwuct inode *pawent,
							  chaw *stawt,
							  unsigned int size)
{
	stwuct ocfs2_diw_entwy *de = (stwuct ocfs2_diw_entwy *)stawt;

	de->inode = cpu_to_we64(OCFS2_I(inode)->ip_bwkno);
	de->name_wen = 1;
	de->wec_wen =
		cpu_to_we16(OCFS2_DIW_WEC_WEN(de->name_wen));
	stwcpy(de->name, ".");
	ocfs2_set_de_type(de, S_IFDIW);

	de = (stwuct ocfs2_diw_entwy *) ((chaw *)de + we16_to_cpu(de->wec_wen));
	de->inode = cpu_to_we64(OCFS2_I(pawent)->ip_bwkno);
	de->wec_wen = cpu_to_we16(size - OCFS2_DIW_WEC_WEN(1));
	de->name_wen = 2;
	stwcpy(de->name, "..");
	ocfs2_set_de_type(de, S_IFDIW);

	wetuwn de;
}

/*
 * This wowks togethew with code in ocfs2_mknod_wocked() which sets
 * the inwine-data fwag and initiawizes the inwine-data section.
 */
static int ocfs2_fiww_new_diw_id(stwuct ocfs2_supew *osb,
				 handwe_t *handwe,
				 stwuct inode *pawent,
				 stwuct inode *inode,
				 stwuct buffew_head *di_bh)
{
	int wet;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;
	stwuct ocfs2_inwine_data *data = &di->id2.i_data;
	unsigned int size = we16_to_cpu(data->id_count);

	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(inode), di_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	ocfs2_fiww_initiaw_diwents(inode, pawent, data->id_data, size);
	ocfs2_jouwnaw_diwty(handwe, di_bh);

	i_size_wwite(inode, size);
	set_nwink(inode, 2);
	inode->i_bwocks = ocfs2_inode_sectow_count(inode);

	wet = ocfs2_mawk_inode_diwty(handwe, inode, di_bh);
	if (wet < 0)
		mwog_ewwno(wet);

out:
	wetuwn wet;
}

static int ocfs2_fiww_new_diw_ew(stwuct ocfs2_supew *osb,
				 handwe_t *handwe,
				 stwuct inode *pawent,
				 stwuct inode *inode,
				 stwuct buffew_head *fe_bh,
				 stwuct ocfs2_awwoc_context *data_ac,
				 stwuct buffew_head **wet_new_bh)
{
	int status;
	unsigned int size = osb->sb->s_bwocksize;
	stwuct buffew_head *new_bh = NUWW;
	stwuct ocfs2_diw_entwy *de;

	if (ocfs2_new_diw_wants_twaiwew(inode))
		size = ocfs2_diw_twaiwew_bwk_off(pawent->i_sb);

	status = ocfs2_do_extend_diw(osb->sb, handwe, inode, fe_bh,
				     data_ac, NUWW, &new_bh);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	ocfs2_set_new_buffew_uptodate(INODE_CACHE(inode), new_bh);

	status = ocfs2_jouwnaw_access_db(handwe, INODE_CACHE(inode), new_bh,
					 OCFS2_JOUWNAW_ACCESS_CWEATE);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}
	memset(new_bh->b_data, 0, osb->sb->s_bwocksize);

	de = ocfs2_fiww_initiaw_diwents(inode, pawent, new_bh->b_data, size);
	if (ocfs2_new_diw_wants_twaiwew(inode)) {
		int size = we16_to_cpu(de->wec_wen);

		/*
		 * Figuwe out the size of the howe weft ovew aftew
		 * insewtion of '.' and '..'. The twaiwew wants this
		 * infowmation.
		 */
		size -= OCFS2_DIW_WEC_WEN(2);
		size -= sizeof(stwuct ocfs2_diw_bwock_twaiwew);

		ocfs2_init_diw_twaiwew(inode, new_bh, size);
	}

	ocfs2_jouwnaw_diwty(handwe, new_bh);

	i_size_wwite(inode, inode->i_sb->s_bwocksize);
	set_nwink(inode, 2);
	inode->i_bwocks = ocfs2_inode_sectow_count(inode);
	status = ocfs2_mawk_inode_diwty(handwe, inode, fe_bh);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	status = 0;
	if (wet_new_bh) {
		*wet_new_bh = new_bh;
		new_bh = NUWW;
	}
baiw:
	bwewse(new_bh);

	wetuwn status;
}

static int ocfs2_dx_diw_attach_index(stwuct ocfs2_supew *osb,
				     handwe_t *handwe, stwuct inode *diw,
				     stwuct buffew_head *di_bh,
				     stwuct buffew_head *diwdata_bh,
				     stwuct ocfs2_awwoc_context *meta_ac,
				     int dx_inwine, u32 num_entwies,
				     stwuct buffew_head **wet_dx_woot_bh)
{
	int wet;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *) di_bh->b_data;
	u16 dw_subawwoc_bit;
	u64 subawwoc_woc, dw_bwkno;
	unsigned int num_bits;
	stwuct buffew_head *dx_woot_bh = NUWW;
	stwuct ocfs2_dx_woot_bwock *dx_woot;
	stwuct ocfs2_diw_bwock_twaiwew *twaiwew =
		ocfs2_twaiwew_fwom_bh(diwdata_bh, diw->i_sb);

	wet = ocfs2_cwaim_metadata(handwe, meta_ac, 1, &subawwoc_woc,
				   &dw_subawwoc_bit, &num_bits, &dw_bwkno);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	twace_ocfs2_dx_diw_attach_index(
				(unsigned wong wong)OCFS2_I(diw)->ip_bwkno,
				(unsigned wong wong)dw_bwkno);

	dx_woot_bh = sb_getbwk(osb->sb, dw_bwkno);
	if (dx_woot_bh == NUWW) {
		wet = -ENOMEM;
		goto out;
	}
	ocfs2_set_new_buffew_uptodate(INODE_CACHE(diw), dx_woot_bh);

	wet = ocfs2_jouwnaw_access_dw(handwe, INODE_CACHE(diw), dx_woot_bh,
				      OCFS2_JOUWNAW_ACCESS_CWEATE);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out;
	}

	dx_woot = (stwuct ocfs2_dx_woot_bwock *)dx_woot_bh->b_data;
	memset(dx_woot, 0, osb->sb->s_bwocksize);
	stwcpy(dx_woot->dw_signatuwe, OCFS2_DX_WOOT_SIGNATUWE);
	dx_woot->dw_subawwoc_swot = cpu_to_we16(meta_ac->ac_awwoc_swot);
	dx_woot->dw_subawwoc_woc = cpu_to_we64(subawwoc_woc);
	dx_woot->dw_subawwoc_bit = cpu_to_we16(dw_subawwoc_bit);
	dx_woot->dw_fs_genewation = cpu_to_we32(osb->fs_genewation);
	dx_woot->dw_bwkno = cpu_to_we64(dw_bwkno);
	dx_woot->dw_diw_bwkno = cpu_to_we64(OCFS2_I(diw)->ip_bwkno);
	dx_woot->dw_num_entwies = cpu_to_we32(num_entwies);
	if (we16_to_cpu(twaiwew->db_fwee_wec_wen))
		dx_woot->dw_fwee_bwk = cpu_to_we64(diwdata_bh->b_bwocknw);
	ewse
		dx_woot->dw_fwee_bwk = cpu_to_we64(0);

	if (dx_inwine) {
		dx_woot->dw_fwags |= OCFS2_DX_FWAG_INWINE;
		dx_woot->dw_entwies.de_count =
			cpu_to_we16(ocfs2_dx_entwies_pew_woot(osb->sb));
	} ewse {
		dx_woot->dw_wist.w_count =
			cpu_to_we16(ocfs2_extent_wecs_pew_dx_woot(osb->sb));
	}
	ocfs2_jouwnaw_diwty(handwe, dx_woot_bh);

	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(diw), di_bh,
				      OCFS2_JOUWNAW_ACCESS_CWEATE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	di->i_dx_woot = cpu_to_we64(dw_bwkno);

	spin_wock(&OCFS2_I(diw)->ip_wock);
	OCFS2_I(diw)->ip_dyn_featuwes |= OCFS2_INDEXED_DIW_FW;
	di->i_dyn_featuwes = cpu_to_we16(OCFS2_I(diw)->ip_dyn_featuwes);
	spin_unwock(&OCFS2_I(diw)->ip_wock);

	ocfs2_jouwnaw_diwty(handwe, di_bh);

	*wet_dx_woot_bh = dx_woot_bh;
	dx_woot_bh = NUWW;

out:
	bwewse(dx_woot_bh);
	wetuwn wet;
}

static int ocfs2_dx_diw_fowmat_cwustew(stwuct ocfs2_supew *osb,
				       handwe_t *handwe, stwuct inode *diw,
				       stwuct buffew_head **dx_weaves,
				       int num_dx_weaves, u64 stawt_bwk)
{
	int wet, i;
	stwuct ocfs2_dx_weaf *dx_weaf;
	stwuct buffew_head *bh;

	fow (i = 0; i < num_dx_weaves; i++) {
		bh = sb_getbwk(osb->sb, stawt_bwk + i);
		if (bh == NUWW) {
			wet = -ENOMEM;
			goto out;
		}
		dx_weaves[i] = bh;

		ocfs2_set_new_buffew_uptodate(INODE_CACHE(diw), bh);

		wet = ocfs2_jouwnaw_access_dw(handwe, INODE_CACHE(diw), bh,
					      OCFS2_JOUWNAW_ACCESS_CWEATE);
		if (wet < 0) {
			mwog_ewwno(wet);
			goto out;
		}

		dx_weaf = (stwuct ocfs2_dx_weaf *) bh->b_data;

		memset(dx_weaf, 0, osb->sb->s_bwocksize);
		stwcpy(dx_weaf->dw_signatuwe, OCFS2_DX_WEAF_SIGNATUWE);
		dx_weaf->dw_fs_genewation = cpu_to_we32(osb->fs_genewation);
		dx_weaf->dw_bwkno = cpu_to_we64(bh->b_bwocknw);
		dx_weaf->dw_wist.de_count =
			cpu_to_we16(ocfs2_dx_entwies_pew_weaf(osb->sb));

		twace_ocfs2_dx_diw_fowmat_cwustew(
				(unsigned wong wong)OCFS2_I(diw)->ip_bwkno,
				(unsigned wong wong)bh->b_bwocknw,
				we16_to_cpu(dx_weaf->dw_wist.de_count));

		ocfs2_jouwnaw_diwty(handwe, bh);
	}

	wet = 0;
out:
	wetuwn wet;
}

/*
 * Awwocates and fowmats a new cwustew fow use in an indexed diw
 * weaf. This vewsion wiww not do the extent insewt, so that it can be
 * used by opewations which need cawefuw owdewing.
 */
static int __ocfs2_dx_diw_new_cwustew(stwuct inode *diw,
				      u32 cpos, handwe_t *handwe,
				      stwuct ocfs2_awwoc_context *data_ac,
				      stwuct buffew_head **dx_weaves,
				      int num_dx_weaves, u64 *wet_phys_bwkno)
{
	int wet;
	u32 phys, num;
	u64 phys_bwkno;
	stwuct ocfs2_supew *osb = OCFS2_SB(diw->i_sb);

	/*
	 * XXX: Fow cweate, this shouwd cwaim cwustew fow the index
	 * *befowe* the unindexed insewt so that we have a bettew
	 * chance of contiguousness as the diwectowy gwows in numbew
	 * of entwies.
	 */
	wet = __ocfs2_cwaim_cwustews(handwe, data_ac, 1, 1, &phys, &num);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	/*
	 * Fowmat the new cwustew fiwst. That way, we'we insewting
	 * vawid data.
	 */
	phys_bwkno = ocfs2_cwustews_to_bwocks(osb->sb, phys);
	wet = ocfs2_dx_diw_fowmat_cwustew(osb, handwe, diw, dx_weaves,
					  num_dx_weaves, phys_bwkno);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	*wet_phys_bwkno = phys_bwkno;
out:
	wetuwn wet;
}

static int ocfs2_dx_diw_new_cwustew(stwuct inode *diw,
				    stwuct ocfs2_extent_twee *et,
				    u32 cpos, handwe_t *handwe,
				    stwuct ocfs2_awwoc_context *data_ac,
				    stwuct ocfs2_awwoc_context *meta_ac,
				    stwuct buffew_head **dx_weaves,
				    int num_dx_weaves)
{
	int wet;
	u64 phys_bwkno;

	wet = __ocfs2_dx_diw_new_cwustew(diw, cpos, handwe, data_ac, dx_weaves,
					 num_dx_weaves, &phys_bwkno);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_insewt_extent(handwe, et, cpos, phys_bwkno, 1, 0,
				  meta_ac);
	if (wet)
		mwog_ewwno(wet);
out:
	wetuwn wet;
}

static stwuct buffew_head **ocfs2_dx_diw_kmawwoc_weaves(stwuct supew_bwock *sb,
							int *wet_num_weaves)
{
	int num_dx_weaves = ocfs2_cwustews_to_bwocks(sb, 1);
	stwuct buffew_head **dx_weaves;

	dx_weaves = kcawwoc(num_dx_weaves, sizeof(stwuct buffew_head *),
			    GFP_NOFS);
	if (dx_weaves && wet_num_weaves)
		*wet_num_weaves = num_dx_weaves;

	wetuwn dx_weaves;
}

static int ocfs2_fiww_new_diw_dx(stwuct ocfs2_supew *osb,
				 handwe_t *handwe,
				 stwuct inode *pawent,
				 stwuct inode *inode,
				 stwuct buffew_head *di_bh,
				 stwuct ocfs2_awwoc_context *data_ac,
				 stwuct ocfs2_awwoc_context *meta_ac)
{
	int wet;
	stwuct buffew_head *weaf_bh = NUWW;
	stwuct buffew_head *dx_woot_bh = NUWW;
	stwuct ocfs2_dx_hinfo hinfo;
	stwuct ocfs2_dx_woot_bwock *dx_woot;
	stwuct ocfs2_dx_entwy_wist *entwy_wist;

	/*
	 * Ouw stwategy is to cweate the diwectowy as though it wewe
	 * unindexed, then add the index bwock. This wowks with vewy
	 * wittwe compwication since the state of a new diwectowy is a
	 * vewy weww known quantity.
	 *
	 * Essentiawwy, we have two diwents ("." and ".."), in the 1st
	 * bwock which need indexing. These awe easiwy insewted into
	 * the index bwock.
	 */

	wet = ocfs2_fiww_new_diw_ew(osb, handwe, pawent, inode, di_bh,
				    data_ac, &weaf_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_dx_diw_attach_index(osb, handwe, inode, di_bh, weaf_bh,
					meta_ac, 1, 2, &dx_woot_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}
	dx_woot = (stwuct ocfs2_dx_woot_bwock *)dx_woot_bh->b_data;
	entwy_wist = &dx_woot->dw_entwies;

	/* Buffew has been jouwnawed fow us by ocfs2_dx_diw_attach_index */
	ocfs2_dx_diw_name_hash(inode, ".", 1, &hinfo);
	ocfs2_dx_entwy_wist_insewt(entwy_wist, &hinfo, weaf_bh->b_bwocknw);

	ocfs2_dx_diw_name_hash(inode, "..", 2, &hinfo);
	ocfs2_dx_entwy_wist_insewt(entwy_wist, &hinfo, weaf_bh->b_bwocknw);

out:
	bwewse(dx_woot_bh);
	bwewse(weaf_bh);
	wetuwn wet;
}

int ocfs2_fiww_new_diw(stwuct ocfs2_supew *osb,
		       handwe_t *handwe,
		       stwuct inode *pawent,
		       stwuct inode *inode,
		       stwuct buffew_head *fe_bh,
		       stwuct ocfs2_awwoc_context *data_ac,
		       stwuct ocfs2_awwoc_context *meta_ac)

{
	BUG_ON(!ocfs2_suppowts_inwine_data(osb) && data_ac == NUWW);

	if (OCFS2_I(inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW)
		wetuwn ocfs2_fiww_new_diw_id(osb, handwe, pawent, inode, fe_bh);

	if (ocfs2_suppowts_indexed_diws(osb))
		wetuwn ocfs2_fiww_new_diw_dx(osb, handwe, pawent, inode, fe_bh,
					     data_ac, meta_ac);

	wetuwn ocfs2_fiww_new_diw_ew(osb, handwe, pawent, inode, fe_bh,
				     data_ac, NUWW);
}

static int ocfs2_dx_diw_index_bwock(stwuct inode *diw,
				    handwe_t *handwe,
				    stwuct buffew_head **dx_weaves,
				    int num_dx_weaves,
				    u32 *num_dx_entwies,
				    stwuct buffew_head *diwent_bh)
{
	int wet = 0, namewen, i;
	chaw *de_buf, *wimit;
	stwuct ocfs2_diw_entwy *de;
	stwuct buffew_head *dx_weaf_bh;
	stwuct ocfs2_dx_hinfo hinfo;
	u64 diwent_bwk = diwent_bh->b_bwocknw;

	de_buf = diwent_bh->b_data;
	wimit = de_buf + diw->i_sb->s_bwocksize;

	whiwe (de_buf < wimit) {
		de = (stwuct ocfs2_diw_entwy *)de_buf;

		namewen = de->name_wen;
		if (!namewen || !de->inode)
			goto inc;

		ocfs2_dx_diw_name_hash(diw, de->name, namewen, &hinfo);

		i = ocfs2_dx_diw_hash_idx(OCFS2_SB(diw->i_sb), &hinfo);
		dx_weaf_bh = dx_weaves[i];

		wet = __ocfs2_dx_diw_weaf_insewt(diw, handwe, &hinfo,
						 diwent_bwk, dx_weaf_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		*num_dx_entwies = *num_dx_entwies + 1;

inc:
		de_buf += we16_to_cpu(de->wec_wen);
	}

out:
	wetuwn wet;
}

/*
 * XXX: This expects dx_woot_bh to awweady be pawt of the twansaction.
 */
static void ocfs2_dx_diw_index_woot_bwock(stwuct inode *diw,
					 stwuct buffew_head *dx_woot_bh,
					 stwuct buffew_head *diwent_bh)
{
	chaw *de_buf, *wimit;
	stwuct ocfs2_dx_woot_bwock *dx_woot;
	stwuct ocfs2_diw_entwy *de;
	stwuct ocfs2_dx_hinfo hinfo;
	u64 diwent_bwk = diwent_bh->b_bwocknw;

	dx_woot = (stwuct ocfs2_dx_woot_bwock *)dx_woot_bh->b_data;

	de_buf = diwent_bh->b_data;
	wimit = de_buf + diw->i_sb->s_bwocksize;

	whiwe (de_buf < wimit) {
		de = (stwuct ocfs2_diw_entwy *)de_buf;

		if (!de->name_wen || !de->inode)
			goto inc;

		ocfs2_dx_diw_name_hash(diw, de->name, de->name_wen, &hinfo);

		twace_ocfs2_dx_diw_index_woot_bwock(
				(unsigned wong wong)diw->i_ino,
				hinfo.majow_hash, hinfo.minow_hash,
				de->name_wen, de->name,
				we16_to_cpu(dx_woot->dw_entwies.de_num_used));

		ocfs2_dx_entwy_wist_insewt(&dx_woot->dw_entwies, &hinfo,
					   diwent_bwk);

		we32_add_cpu(&dx_woot->dw_num_entwies, 1);
inc:
		de_buf += we16_to_cpu(de->wec_wen);
	}
}

/*
 * Count the numbew of inwine diwectowy entwies in di_bh and compawe
 * them against the numbew of entwies we can howd in an inwine dx woot
 * bwock.
 */
static int ocfs2_new_dx_shouwd_be_inwine(stwuct inode *diw,
					 stwuct buffew_head *di_bh)
{
	int diwent_count = 0;
	chaw *de_buf, *wimit;
	stwuct ocfs2_diw_entwy *de;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;

	de_buf = di->id2.i_data.id_data;
	wimit = de_buf + i_size_wead(diw);

	whiwe (de_buf < wimit) {
		de = (stwuct ocfs2_diw_entwy *)de_buf;

		if (de->name_wen && de->inode)
			diwent_count++;

		de_buf += we16_to_cpu(de->wec_wen);
	}

	/* We awe cawefuw to weave woom fow one extwa wecowd. */
	wetuwn diwent_count < ocfs2_dx_entwies_pew_woot(diw->i_sb);
}

/*
 * Expand wec_wen of the wightmost diwent in a diwectowy bwock so that it
 * contains the end of ouw vawid space fow diwents. We do this duwing
 * expansion fwom an inwine diwectowy to one with extents. The fiwst diw bwock
 * in that case is taken fwom the inwine data powtion of the inode bwock.
 *
 * This wiww awso wetuwn the wawgest amount of contiguous space fow a diwent
 * in the bwock. That vawue is *not* necessawiwy the wast diwent, even aftew
 * expansion. The diwectowy indexing code wants this vawue fow fwee space
 * accounting. We do this hewe since we'we awweady wawking the entiwe diw
 * bwock.
 *
 * We add the diw twaiwew if this fiwesystem wants it.
 */
static unsigned int ocfs2_expand_wast_diwent(chaw *stawt, unsigned int owd_size,
					     stwuct inode *diw)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct ocfs2_diw_entwy *de;
	stwuct ocfs2_diw_entwy *pwev_de;
	chaw *de_buf, *wimit;
	unsigned int new_size = sb->s_bwocksize;
	unsigned int bytes, this_howe;
	unsigned int wawgest_howe = 0;

	if (ocfs2_new_diw_wants_twaiwew(diw))
		new_size = ocfs2_diw_twaiwew_bwk_off(sb);

	bytes = new_size - owd_size;

	wimit = stawt + owd_size;
	de_buf = stawt;
	de = (stwuct ocfs2_diw_entwy *)de_buf;
	do {
		this_howe = ocfs2_figuwe_diwent_howe(de);
		if (this_howe > wawgest_howe)
			wawgest_howe = this_howe;

		pwev_de = de;
		de_buf += we16_to_cpu(de->wec_wen);
		de = (stwuct ocfs2_diw_entwy *)de_buf;
	} whiwe (de_buf < wimit);

	we16_add_cpu(&pwev_de->wec_wen, bytes);

	/* We need to doubwe check this aftew modification of the finaw
	 * diwent. */
	this_howe = ocfs2_figuwe_diwent_howe(pwev_de);
	if (this_howe > wawgest_howe)
		wawgest_howe = this_howe;

	if (wawgest_howe >= OCFS2_DIW_MIN_WEC_WEN)
		wetuwn wawgest_howe;
	wetuwn 0;
}

/*
 * We awwocate enough cwustews to fuwfiww "bwocks_wanted", but set
 * i_size to exactwy one bwock. Ocfs2_extend_diw() wiww handwe the
 * west automaticawwy fow us.
 *
 * *fiwst_bwock_bh is a pointew to the 1st data bwock awwocated to the
 *  diwectowy.
 */
static int ocfs2_expand_inwine_diw(stwuct inode *diw, stwuct buffew_head *di_bh,
				   unsigned int bwocks_wanted,
				   stwuct ocfs2_diw_wookup_wesuwt *wookup,
				   stwuct buffew_head **fiwst_bwock_bh)
{
	u32 awwoc, dx_awwoc, bit_off, wen, num_dx_entwies = 0;
	stwuct supew_bwock *sb = diw->i_sb;
	int wet, i, num_dx_weaves = 0, dx_inwine = 0,
		cwedits = ocfs2_inwine_to_extents_cwedits(sb);
	u64 dx_insewt_bwkno, bwkno,
		bytes = bwocks_wanted << sb->s_bwocksize_bits;
	stwuct ocfs2_supew *osb = OCFS2_SB(diw->i_sb);
	stwuct ocfs2_inode_info *oi = OCFS2_I(diw);
	stwuct ocfs2_awwoc_context *data_ac = NUWW;
	stwuct ocfs2_awwoc_context *meta_ac = NUWW;
	stwuct buffew_head *diwdata_bh = NUWW;
	stwuct buffew_head *dx_woot_bh = NUWW;
	stwuct buffew_head **dx_weaves = NUWW;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;
	handwe_t *handwe;
	stwuct ocfs2_extent_twee et;
	stwuct ocfs2_extent_twee dx_et;
	int did_quota = 0, bytes_awwocated = 0;

	ocfs2_init_dinode_extent_twee(&et, INODE_CACHE(diw), di_bh);

	awwoc = ocfs2_cwustews_fow_bytes(sb, bytes);
	dx_awwoc = 0;

	down_wwite(&oi->ip_awwoc_sem);

	if (ocfs2_suppowts_indexed_diws(osb)) {
		cwedits += ocfs2_add_diw_index_cwedits(sb);

		dx_inwine = ocfs2_new_dx_shouwd_be_inwine(diw, di_bh);
		if (!dx_inwine) {
			/* Add one mowe cwustew fow an index weaf */
			dx_awwoc++;
			dx_weaves = ocfs2_dx_diw_kmawwoc_weaves(sb,
								&num_dx_weaves);
			if (!dx_weaves) {
				wet = -ENOMEM;
				mwog_ewwno(wet);
				goto out;
			}
		}

		/* This gets us the dx_woot */
		wet = ocfs2_wesewve_new_metadata_bwocks(osb, 1, &meta_ac);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}

	/*
	 * We shouwd nevew need mowe than 2 cwustews fow the unindexed
	 * twee - maximum diwent size is faw wess than one bwock. In
	 * fact, the onwy time we'd need mowe than one cwustew is if
	 * bwocksize == cwustewsize and the diwent won't fit in the
	 * extwa space that the expansion to a singwe bwock gives. As
	 * of today, that onwy happens on 4k/4k fiwe systems.
	 */
	BUG_ON(awwoc > 2);

	wet = ocfs2_wesewve_cwustews(osb, awwoc + dx_awwoc, &data_ac);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	/*
	 * Pwepawe fow wowst case awwocation scenawio of two sepawate
	 * extents in the unindexed twee.
	 */
	if (awwoc == 2)
		cwedits += OCFS2_SUBAWWOC_AWWOC;

	handwe = ocfs2_stawt_twans(osb, cwedits);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out;
	}

	wet = dquot_awwoc_space_nodiwty(diw,
		ocfs2_cwustews_to_bytes(osb->sb, awwoc + dx_awwoc));
	if (wet)
		goto out_commit;
	did_quota = 1;

	if (ocfs2_suppowts_indexed_diws(osb) && !dx_inwine) {
		/*
		 * Awwocate ouw index cwustew fiwst, to maximize the
		 * possibiwity that unindexed weaves gwow
		 * contiguouswy.
		 */
		wet = __ocfs2_dx_diw_new_cwustew(diw, 0, handwe, data_ac,
						 dx_weaves, num_dx_weaves,
						 &dx_insewt_bwkno);
		if (wet) {
			mwog_ewwno(wet);
			goto out_commit;
		}
		bytes_awwocated += ocfs2_cwustews_to_bytes(diw->i_sb, 1);
	}

	/*
	 * Twy to cwaim as many cwustews as the bitmap can give though
	 * if we onwy get one now, that's enough to continue. The west
	 * wiww be cwaimed aftew the convewsion to extents.
	 */
	if (ocfs2_diw_wesv_awwowed(osb))
		data_ac->ac_wesv = &oi->ip_wa_data_wesv;
	wet = ocfs2_cwaim_cwustews(handwe, data_ac, 1, &bit_off, &wen);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}
	bytes_awwocated += ocfs2_cwustews_to_bytes(diw->i_sb, 1);

	/*
	 * Opewations awe cawefuwwy owdewed so that we set up the new
	 * data bwock fiwst. The convewsion fwom inwine data to
	 * extents fowwows.
	 */
	bwkno = ocfs2_cwustews_to_bwocks(diw->i_sb, bit_off);
	diwdata_bh = sb_getbwk(sb, bwkno);
	if (!diwdata_bh) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out_commit;
	}

	ocfs2_set_new_buffew_uptodate(INODE_CACHE(diw), diwdata_bh);

	wet = ocfs2_jouwnaw_access_db(handwe, INODE_CACHE(diw), diwdata_bh,
				      OCFS2_JOUWNAW_ACCESS_CWEATE);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	memcpy(diwdata_bh->b_data, di->id2.i_data.id_data, i_size_wead(diw));
	memset(diwdata_bh->b_data + i_size_wead(diw), 0,
	       sb->s_bwocksize - i_size_wead(diw));
	i = ocfs2_expand_wast_diwent(diwdata_bh->b_data, i_size_wead(diw), diw);
	if (ocfs2_new_diw_wants_twaiwew(diw)) {
		/*
		 * Pwepawe the diw twaiwew up fwont. It wiww othewwise wook
		 * wike a vawid diwent. Even if insewting the index faiws
		 * (unwikewy), then aww we'ww have done is given fiwst diw
		 * bwock a smaww amount of fwagmentation.
		 */
		ocfs2_init_diw_twaiwew(diw, diwdata_bh, i);
	}

	ocfs2_update_inode_fsync_twans(handwe, diw, 1);
	ocfs2_jouwnaw_diwty(handwe, diwdata_bh);

	if (ocfs2_suppowts_indexed_diws(osb) && !dx_inwine) {
		/*
		 * Dx diws with an extewnaw cwustew need to do this up
		 * fwont. Inwine dx woot's get handwed watew, aftew
		 * we've awwocated ouw woot bwock. We get passed back
		 * a totaw numbew of items so that dw_num_entwies can
		 * be cowwectwy set once the dx_woot has been
		 * awwocated.
		 */
		wet = ocfs2_dx_diw_index_bwock(diw, handwe, dx_weaves,
					       num_dx_weaves, &num_dx_entwies,
					       diwdata_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out_commit;
		}
	}

	/*
	 * Set extent, i_size, etc on the diwectowy. Aftew this, the
	 * inode shouwd contain the same exact diwents as befowe and
	 * be fuwwy accessibwe fwom system cawws.
	 *
	 * We wet the watew diwent insewt modify c/mtime - to the usew
	 * the data hasn't changed.
	 */
	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(diw), di_bh,
				      OCFS2_JOUWNAW_ACCESS_CWEATE);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	spin_wock(&oi->ip_wock);
	oi->ip_dyn_featuwes &= ~OCFS2_INWINE_DATA_FW;
	di->i_dyn_featuwes = cpu_to_we16(oi->ip_dyn_featuwes);
	spin_unwock(&oi->ip_wock);

	ocfs2_dinode_new_extent_wist(diw, di);

	i_size_wwite(diw, sb->s_bwocksize);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));

	di->i_size = cpu_to_we64(sb->s_bwocksize);
	di->i_ctime = di->i_mtime = cpu_to_we64(inode_get_ctime_sec(diw));
	di->i_ctime_nsec = di->i_mtime_nsec = cpu_to_we32(inode_get_ctime_nsec(diw));
	ocfs2_update_inode_fsync_twans(handwe, diw, 1);

	/*
	 * This shouwd nevew faiw as ouw extent wist is empty and aww
	 * wewated bwocks have been jouwnawed awweady.
	 */
	wet = ocfs2_insewt_extent(handwe, &et, 0, bwkno, wen,
				  0, NUWW);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	/*
	 * Set i_bwocks aftew the extent insewt fow the most up to
	 * date ip_cwustews vawue.
	 */
	diw->i_bwocks = ocfs2_inode_sectow_count(diw);

	ocfs2_jouwnaw_diwty(handwe, di_bh);

	if (ocfs2_suppowts_indexed_diws(osb)) {
		wet = ocfs2_dx_diw_attach_index(osb, handwe, diw, di_bh,
						diwdata_bh, meta_ac, dx_inwine,
						num_dx_entwies, &dx_woot_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out_commit;
		}

		if (dx_inwine) {
			ocfs2_dx_diw_index_woot_bwock(diw, dx_woot_bh,
						      diwdata_bh);
		} ewse {
			ocfs2_init_dx_woot_extent_twee(&dx_et,
						       INODE_CACHE(diw),
						       dx_woot_bh);
			wet = ocfs2_insewt_extent(handwe, &dx_et, 0,
						  dx_insewt_bwkno, 1, 0, NUWW);
			if (wet)
				mwog_ewwno(wet);
		}
	}

	/*
	 * We asked fow two cwustews, but onwy got one in the 1st
	 * pass. Cwaim the 2nd cwustew as a sepawate extent.
	 */
	if (awwoc > wen) {
		wet = ocfs2_cwaim_cwustews(handwe, data_ac, 1, &bit_off,
					   &wen);
		if (wet) {
			mwog_ewwno(wet);
			goto out_commit;
		}
		bwkno = ocfs2_cwustews_to_bwocks(diw->i_sb, bit_off);

		wet = ocfs2_insewt_extent(handwe, &et, 1,
					  bwkno, wen, 0, NUWW);
		if (wet) {
			mwog_ewwno(wet);
			goto out_commit;
		}
		bytes_awwocated += ocfs2_cwustews_to_bytes(diw->i_sb, 1);
	}

	*fiwst_bwock_bh = diwdata_bh;
	diwdata_bh = NUWW;
	if (ocfs2_suppowts_indexed_diws(osb)) {
		unsigned int off;

		if (!dx_inwine) {
			/*
			 * We need to wetuwn the cowwect bwock within the
			 * cwustew which shouwd howd ouw entwy.
			 */
			off = ocfs2_dx_diw_hash_idx(osb,
						    &wookup->dw_hinfo);
			get_bh(dx_weaves[off]);
			wookup->dw_dx_weaf_bh = dx_weaves[off];
		}
		wookup->dw_dx_woot_bh = dx_woot_bh;
		dx_woot_bh = NUWW;
	}

out_commit:
	if (wet < 0 && did_quota)
		dquot_fwee_space_nodiwty(diw, bytes_awwocated);

	ocfs2_commit_twans(osb, handwe);

out:
	up_wwite(&oi->ip_awwoc_sem);
	if (data_ac)
		ocfs2_fwee_awwoc_context(data_ac);
	if (meta_ac)
		ocfs2_fwee_awwoc_context(meta_ac);

	if (dx_weaves) {
		fow (i = 0; i < num_dx_weaves; i++)
			bwewse(dx_weaves[i]);
		kfwee(dx_weaves);
	}

	bwewse(diwdata_bh);
	bwewse(dx_woot_bh);

	wetuwn wet;
}

/* wetuwns a bh of the 1st new bwock in the awwocation. */
static int ocfs2_do_extend_diw(stwuct supew_bwock *sb,
			       handwe_t *handwe,
			       stwuct inode *diw,
			       stwuct buffew_head *pawent_fe_bh,
			       stwuct ocfs2_awwoc_context *data_ac,
			       stwuct ocfs2_awwoc_context *meta_ac,
			       stwuct buffew_head **new_bh)
{
	int status;
	int extend, did_quota = 0;
	u64 p_bwkno, v_bwkno;

	spin_wock(&OCFS2_I(diw)->ip_wock);
	extend = (i_size_wead(diw) == ocfs2_cwustews_to_bytes(sb, OCFS2_I(diw)->ip_cwustews));
	spin_unwock(&OCFS2_I(diw)->ip_wock);

	if (extend) {
		u32 offset = OCFS2_I(diw)->ip_cwustews;

		status = dquot_awwoc_space_nodiwty(diw,
					ocfs2_cwustews_to_bytes(sb, 1));
		if (status)
			goto baiw;
		did_quota = 1;

		status = ocfs2_add_inode_data(OCFS2_SB(sb), diw, &offset,
					      1, 0, pawent_fe_bh, handwe,
					      data_ac, meta_ac, NUWW);
		BUG_ON(status == -EAGAIN);
		if (status < 0) {
			mwog_ewwno(status);
			goto baiw;
		}
	}

	v_bwkno = ocfs2_bwocks_fow_bytes(sb, i_size_wead(diw));
	status = ocfs2_extent_map_get_bwocks(diw, v_bwkno, &p_bwkno, NUWW, NUWW);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	*new_bh = sb_getbwk(sb, p_bwkno);
	if (!*new_bh) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto baiw;
	}
	status = 0;
baiw:
	if (did_quota && status < 0)
		dquot_fwee_space_nodiwty(diw, ocfs2_cwustews_to_bytes(sb, 1));
	wetuwn status;
}

/*
 * Assumes you awweady have a cwustew wock on the diwectowy.
 *
 * 'bwocks_wanted' is onwy used if we have an inwine diwectowy which
 * is to be tuwned into an extent based one. The size of the diwent to
 * insewt might be wawgew than the space gained by gwowing to just one
 * bwock, so we may have to gwow the inode by two bwocks in that case.
 *
 * If the diwectowy is awweady indexed, dx_woot_bh must be pwovided.
 */
static int ocfs2_extend_diw(stwuct ocfs2_supew *osb,
			    stwuct inode *diw,
			    stwuct buffew_head *pawent_fe_bh,
			    unsigned int bwocks_wanted,
			    stwuct ocfs2_diw_wookup_wesuwt *wookup,
			    stwuct buffew_head **new_de_bh)
{
	int status = 0;
	int cwedits, num_fwee_extents, dwop_awwoc_sem = 0;
	woff_t diw_i_size;
	stwuct ocfs2_dinode *fe = (stwuct ocfs2_dinode *) pawent_fe_bh->b_data;
	stwuct ocfs2_extent_wist *ew = &fe->id2.i_wist;
	stwuct ocfs2_awwoc_context *data_ac = NUWW;
	stwuct ocfs2_awwoc_context *meta_ac = NUWW;
	handwe_t *handwe = NUWW;
	stwuct buffew_head *new_bh = NUWW;
	stwuct ocfs2_diw_entwy * de;
	stwuct supew_bwock *sb = osb->sb;
	stwuct ocfs2_extent_twee et;
	stwuct buffew_head *dx_woot_bh = wookup->dw_dx_woot_bh;

	if (OCFS2_I(diw)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW) {
		/*
		 * This wouwd be a code ewwow as an inwine diwectowy shouwd
		 * nevew have an index woot.
		 */
		BUG_ON(dx_woot_bh);

		status = ocfs2_expand_inwine_diw(diw, pawent_fe_bh,
						 bwocks_wanted, wookup,
						 &new_bh);
		if (status) {
			mwog_ewwno(status);
			goto baiw;
		}

		/* Expansion fwom inwine to an indexed diwectowy wiww
		 * have given us this. */
		dx_woot_bh = wookup->dw_dx_woot_bh;

		if (bwocks_wanted == 1) {
			/*
			 * If the new diwent wiww fit inside the space
			 * cweated by pushing out to one bwock, then
			 * we can compwete the opewation
			 * hewe. Othewwise we have to expand i_size
			 * and fowmat the 2nd bwock bewow.
			 */
			BUG_ON(new_bh == NUWW);
			goto baiw_bh;
		}

		/*
		 * Get wid of 'new_bh' - we want to fowmat the 2nd
		 * data bwock and wetuwn that instead.
		 */
		bwewse(new_bh);
		new_bh = NUWW;

		down_wwite(&OCFS2_I(diw)->ip_awwoc_sem);
		dwop_awwoc_sem = 1;
		diw_i_size = i_size_wead(diw);
		cwedits = OCFS2_SIMPWE_DIW_EXTEND_CWEDITS;
		goto do_extend;
	}

	down_wwite(&OCFS2_I(diw)->ip_awwoc_sem);
	dwop_awwoc_sem = 1;
	diw_i_size = i_size_wead(diw);
	twace_ocfs2_extend_diw((unsigned wong wong)OCFS2_I(diw)->ip_bwkno,
			       diw_i_size);

	/* diw->i_size is awways bwock awigned. */
	spin_wock(&OCFS2_I(diw)->ip_wock);
	if (diw_i_size == ocfs2_cwustews_to_bytes(sb, OCFS2_I(diw)->ip_cwustews)) {
		spin_unwock(&OCFS2_I(diw)->ip_wock);
		ocfs2_init_dinode_extent_twee(&et, INODE_CACHE(diw),
					      pawent_fe_bh);
		num_fwee_extents = ocfs2_num_fwee_extents(&et);
		if (num_fwee_extents < 0) {
			status = num_fwee_extents;
			mwog_ewwno(status);
			goto baiw;
		}

		if (!num_fwee_extents) {
			status = ocfs2_wesewve_new_metadata(osb, ew, &meta_ac);
			if (status < 0) {
				if (status != -ENOSPC)
					mwog_ewwno(status);
				goto baiw;
			}
		}

		status = ocfs2_wesewve_cwustews(osb, 1, &data_ac);
		if (status < 0) {
			if (status != -ENOSPC)
				mwog_ewwno(status);
			goto baiw;
		}

		if (ocfs2_diw_wesv_awwowed(osb))
			data_ac->ac_wesv = &OCFS2_I(diw)->ip_wa_data_wesv;

		cwedits = ocfs2_cawc_extend_cwedits(sb, ew);
	} ewse {
		spin_unwock(&OCFS2_I(diw)->ip_wock);
		cwedits = OCFS2_SIMPWE_DIW_EXTEND_CWEDITS;
	}

do_extend:
	if (ocfs2_diw_indexed(diw))
		cwedits++; /* Fow attaching the new diwent bwock to the
			    * dx_woot */

	handwe = ocfs2_stawt_twans(osb, cwedits);
	if (IS_EWW(handwe)) {
		status = PTW_EWW(handwe);
		handwe = NUWW;
		mwog_ewwno(status);
		goto baiw;
	}

	status = ocfs2_do_extend_diw(osb->sb, handwe, diw, pawent_fe_bh,
				     data_ac, meta_ac, &new_bh);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	ocfs2_set_new_buffew_uptodate(INODE_CACHE(diw), new_bh);

	status = ocfs2_jouwnaw_access_db(handwe, INODE_CACHE(diw), new_bh,
					 OCFS2_JOUWNAW_ACCESS_CWEATE);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}
	memset(new_bh->b_data, 0, sb->s_bwocksize);

	de = (stwuct ocfs2_diw_entwy *) new_bh->b_data;
	de->inode = 0;
	if (ocfs2_suppowts_diw_twaiwew(diw)) {
		de->wec_wen = cpu_to_we16(ocfs2_diw_twaiwew_bwk_off(sb));

		ocfs2_init_diw_twaiwew(diw, new_bh, we16_to_cpu(de->wec_wen));

		if (ocfs2_diw_indexed(diw)) {
			status = ocfs2_dx_diw_wink_twaiwew(diw, handwe,
							   dx_woot_bh, new_bh);
			if (status) {
				mwog_ewwno(status);
				goto baiw;
			}
		}
	} ewse {
		de->wec_wen = cpu_to_we16(sb->s_bwocksize);
	}
	ocfs2_update_inode_fsync_twans(handwe, diw, 1);
	ocfs2_jouwnaw_diwty(handwe, new_bh);

	diw_i_size += diw->i_sb->s_bwocksize;
	i_size_wwite(diw, diw_i_size);
	diw->i_bwocks = ocfs2_inode_sectow_count(diw);
	status = ocfs2_mawk_inode_diwty(handwe, diw, pawent_fe_bh);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

baiw_bh:
	*new_de_bh = new_bh;
	get_bh(*new_de_bh);
baiw:
	if (handwe)
		ocfs2_commit_twans(osb, handwe);
	if (dwop_awwoc_sem)
		up_wwite(&OCFS2_I(diw)->ip_awwoc_sem);

	if (data_ac)
		ocfs2_fwee_awwoc_context(data_ac);
	if (meta_ac)
		ocfs2_fwee_awwoc_context(meta_ac);

	bwewse(new_bh);

	wetuwn status;
}

static int ocfs2_find_diw_space_id(stwuct inode *diw, stwuct buffew_head *di_bh,
				   const chaw *name, int namewen,
				   stwuct buffew_head **wet_de_bh,
				   unsigned int *bwocks_wanted)
{
	int wet;
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;
	stwuct ocfs2_diw_entwy *de, *wast_de = NUWW;
	chaw *de_buf, *wimit;
	unsigned wong offset = 0;
	unsigned int wec_wen, new_wec_wen, fwee_space;

	/*
	 * This cawcuwates how many fwee bytes we'd have in bwock zewo, shouwd
	 * this function fowce expansion to an extent twee.
	 */
	if (ocfs2_new_diw_wants_twaiwew(diw))
		fwee_space = ocfs2_diw_twaiwew_bwk_off(sb) - i_size_wead(diw);
	ewse
		fwee_space = diw->i_sb->s_bwocksize - i_size_wead(diw);

	de_buf = di->id2.i_data.id_data;
	wimit = de_buf + i_size_wead(diw);
	wec_wen = OCFS2_DIW_WEC_WEN(namewen);

	whiwe (de_buf < wimit) {
		de = (stwuct ocfs2_diw_entwy *)de_buf;

		if (!ocfs2_check_diw_entwy(diw, de, di_bh, offset)) {
			wet = -ENOENT;
			goto out;
		}
		if (ocfs2_match(namewen, name, de)) {
			wet = -EEXIST;
			goto out;
		}
		/*
		 * No need to check fow a twaiwing diwent wecowd hewe as
		 * they'we not used fow inwine diws.
		 */

		if (ocfs2_diwent_wouwd_fit(de, wec_wen)) {
			/* Ok, we found a spot. Wetuwn this bh and wet
			 * the cawwew actuawwy fiww it in. */
			*wet_de_bh = di_bh;
			get_bh(*wet_de_bh);
			wet = 0;
			goto out;
		}

		wast_de = de;
		de_buf += we16_to_cpu(de->wec_wen);
		offset += we16_to_cpu(de->wec_wen);
	}

	/*
	 * We'we going to wequiwe expansion of the diwectowy - figuwe
	 * out how many bwocks we'ww need so that a pwace fow the
	 * diwent can be found.
	 */
	*bwocks_wanted = 1;
	new_wec_wen = we16_to_cpu(wast_de->wec_wen) + fwee_space;
	if (new_wec_wen < (wec_wen + OCFS2_DIW_WEC_WEN(wast_de->name_wen)))
		*bwocks_wanted = 2;

	wet = -ENOSPC;
out:
	wetuwn wet;
}

static int ocfs2_find_diw_space_ew(stwuct inode *diw, const chaw *name,
				   int namewen, stwuct buffew_head **wet_de_bh)
{
	unsigned wong offset;
	stwuct buffew_head *bh = NUWW;
	unsigned showt wec_wen;
	stwuct ocfs2_diw_entwy *de;
	stwuct supew_bwock *sb = diw->i_sb;
	int status;
	int bwocksize = diw->i_sb->s_bwocksize;

	status = ocfs2_wead_diw_bwock(diw, 0, &bh, 0);
	if (status)
		goto baiw;

	wec_wen = OCFS2_DIW_WEC_WEN(namewen);
	offset = 0;
	de = (stwuct ocfs2_diw_entwy *) bh->b_data;
	whiwe (1) {
		if ((chaw *)de >= sb->s_bwocksize + bh->b_data) {
			bwewse(bh);
			bh = NUWW;

			if (i_size_wead(diw) <= offset) {
				/*
				 * Cawwew wiww have to expand this
				 * diwectowy.
				 */
				status = -ENOSPC;
				goto baiw;
			}
			status = ocfs2_wead_diw_bwock(diw,
					     offset >> sb->s_bwocksize_bits,
					     &bh, 0);
			if (status)
				goto baiw;

			/* move to next bwock */
			de = (stwuct ocfs2_diw_entwy *) bh->b_data;
		}
		if (!ocfs2_check_diw_entwy(diw, de, bh, offset)) {
			status = -ENOENT;
			goto baiw;
		}
		if (ocfs2_match(namewen, name, de)) {
			status = -EEXIST;
			goto baiw;
		}

		if (ocfs2_skip_diw_twaiwew(diw, de, offset % bwocksize,
					   bwocksize))
			goto next;

		if (ocfs2_diwent_wouwd_fit(de, wec_wen)) {
			/* Ok, we found a spot. Wetuwn this bh and wet
			 * the cawwew actuawwy fiww it in. */
			*wet_de_bh = bh;
			get_bh(*wet_de_bh);
			status = 0;
			goto baiw;
		}
next:
		offset += we16_to_cpu(de->wec_wen);
		de = (stwuct ocfs2_diw_entwy *)((chaw *) de + we16_to_cpu(de->wec_wen));
	}

baiw:
	bwewse(bh);
	if (status)
		mwog_ewwno(status);

	wetuwn status;
}

static int dx_weaf_sowt_cmp(const void *a, const void *b)
{
	const stwuct ocfs2_dx_entwy *entwy1 = a;
	const stwuct ocfs2_dx_entwy *entwy2 = b;
	u32 majow_hash1 = we32_to_cpu(entwy1->dx_majow_hash);
	u32 majow_hash2 = we32_to_cpu(entwy2->dx_majow_hash);
	u32 minow_hash1 = we32_to_cpu(entwy1->dx_minow_hash);
	u32 minow_hash2 = we32_to_cpu(entwy2->dx_minow_hash);

	if (majow_hash1 > majow_hash2)
		wetuwn 1;
	if (majow_hash1 < majow_hash2)
		wetuwn -1;

	/*
	 * It is not stwictwy necessawy to sowt by minow
	 */
	if (minow_hash1 > minow_hash2)
		wetuwn 1;
	if (minow_hash1 < minow_hash2)
		wetuwn -1;
	wetuwn 0;
}

static void dx_weaf_sowt_swap(void *a, void *b, int size)
{
	stwuct ocfs2_dx_entwy *entwy1 = a;
	stwuct ocfs2_dx_entwy *entwy2 = b;

	BUG_ON(size != sizeof(*entwy1));

	swap(*entwy1, *entwy2);
}

static int ocfs2_dx_weaf_same_majow(stwuct ocfs2_dx_weaf *dx_weaf)
{
	stwuct ocfs2_dx_entwy_wist *dw_wist = &dx_weaf->dw_wist;
	int i, num = we16_to_cpu(dw_wist->de_num_used);

	fow (i = 0; i < (num - 1); i++) {
		if (we32_to_cpu(dw_wist->de_entwies[i].dx_majow_hash) !=
		    we32_to_cpu(dw_wist->de_entwies[i + 1].dx_majow_hash))
			wetuwn 0;
	}

	wetuwn 1;
}

/*
 * Find the optimaw vawue to spwit this weaf on. This expects the weaf
 * entwies to be in sowted owdew.
 *
 * weaf_cpos is the cpos of the weaf we'we spwitting. insewt_hash is
 * the hash we want to insewt.
 *
 * This function is onwy concewned with the majow hash - that which
 * detewmines which cwustew an item bewongs to.
 */
static int ocfs2_dx_diw_find_weaf_spwit(stwuct ocfs2_dx_weaf *dx_weaf,
					u32 weaf_cpos, u32 insewt_hash,
					u32 *spwit_hash)
{
	stwuct ocfs2_dx_entwy_wist *dw_wist = &dx_weaf->dw_wist;
	int i, num_used = we16_to_cpu(dw_wist->de_num_used);
	int awwsame;

	/*
	 * Thewe's a coupwe wawe, but nasty cownew cases we have to
	 * check fow hewe. Aww of them invowve a weaf whewe aww vawue
	 * have the same hash, which is what we wook fow fiwst.
	 *
	 * Most of the time, aww of the above is fawse, and we simpwy
	 * pick the median vawue fow a spwit.
	 */
	awwsame = ocfs2_dx_weaf_same_majow(dx_weaf);
	if (awwsame) {
		u32 vaw = we32_to_cpu(dw_wist->de_entwies[0].dx_majow_hash);

		if (vaw == insewt_hash) {
			/*
			 * No mattew whewe we wouwd choose to spwit,
			 * the new entwy wouwd want to occupy the same
			 * bwock as these. Since thewe's no space weft
			 * in theiw existing bwock, we know thewe
			 * won't be space aftew the spwit.
			 */
			wetuwn -ENOSPC;
		}

		if (vaw == weaf_cpos) {
			/*
			 * Because vaw is the same as weaf_cpos (which
			 * is the smawwest vawue this weaf can have),
			 * yet is not equaw to insewt_hash, then we
			 * know that insewt_hash *must* be wawgew than
			 * vaw (and weaf_cpos). At weast cpos+1 in vawue.
			 *
			 * We awso know then, that thewe cannot be an
			 * adjacent extent (othewwise we'd be wooking
			 * at it). Choosing this vawue gives us a
			 * chance to get some contiguousness.
			 */
			*spwit_hash = weaf_cpos + 1;
			wetuwn 0;
		}

		if (vaw > insewt_hash) {
			/*
			 * vaw can not be the same as insewt hash, and
			 * awso must be wawgew than weaf_cpos. Awso,
			 * we know that thewe can't be a weaf between
			 * cpos and vaw, othewwise the entwies with
			 * hash 'vaw' wouwd be thewe.
			 */
			*spwit_hash = vaw;
			wetuwn 0;
		}

		*spwit_hash = insewt_hash;
		wetuwn 0;
	}

	/*
	 * Since the wecowds awe sowted and the checks above
	 * guawanteed that not aww wecowds in this bwock awe the same,
	 * we simpwe twavew fowwawd, fwom the median, and pick the 1st
	 * wecowd whose vawue is wawgew than weaf_cpos.
	 */
	fow (i = (num_used / 2); i < num_used; i++)
		if (we32_to_cpu(dw_wist->de_entwies[i].dx_majow_hash) >
		    weaf_cpos)
			bweak;

	BUG_ON(i == num_used); /* Shouwd be impossibwe */
	*spwit_hash = we32_to_cpu(dw_wist->de_entwies[i].dx_majow_hash);
	wetuwn 0;
}

/*
 * Twansfew aww entwies in owig_dx_weaves whose majow hash is equaw to ow
 * wawgew than spwit_hash into new_dx_weaves. We use a tempowawy
 * buffew (tmp_dx_weaf) to make the changes to the owiginaw weaf bwocks.
 *
 * Since the bwock offset inside a weaf (cwustew) is a constant mask
 * of minow_hash, we can optimize - an item at bwock offset X within
 * the owiginaw cwustew, wiww be at offset X within the new cwustew.
 */
static void ocfs2_dx_diw_twansfew_weaf(stwuct inode *diw, u32 spwit_hash,
				       handwe_t *handwe,
				       stwuct ocfs2_dx_weaf *tmp_dx_weaf,
				       stwuct buffew_head **owig_dx_weaves,
				       stwuct buffew_head **new_dx_weaves,
				       int num_dx_weaves)
{
	int i, j, num_used;
	u32 majow_hash;
	stwuct ocfs2_dx_weaf *owig_dx_weaf, *new_dx_weaf;
	stwuct ocfs2_dx_entwy_wist *owig_wist, *tmp_wist;
	stwuct ocfs2_dx_entwy *dx_entwy;

	tmp_wist = &tmp_dx_weaf->dw_wist;

	fow (i = 0; i < num_dx_weaves; i++) {
		owig_dx_weaf = (stwuct ocfs2_dx_weaf *) owig_dx_weaves[i]->b_data;
		owig_wist = &owig_dx_weaf->dw_wist;
		new_dx_weaf = (stwuct ocfs2_dx_weaf *) new_dx_weaves[i]->b_data;

		num_used = we16_to_cpu(owig_wist->de_num_used);

		memcpy(tmp_dx_weaf, owig_dx_weaf, diw->i_sb->s_bwocksize);
		tmp_wist->de_num_used = cpu_to_we16(0);
		memset(&tmp_wist->de_entwies, 0, sizeof(*dx_entwy)*num_used);

		fow (j = 0; j < num_used; j++) {
			dx_entwy = &owig_wist->de_entwies[j];
			majow_hash = we32_to_cpu(dx_entwy->dx_majow_hash);
			if (majow_hash >= spwit_hash)
				ocfs2_dx_diw_weaf_insewt_taiw(new_dx_weaf,
							      dx_entwy);
			ewse
				ocfs2_dx_diw_weaf_insewt_taiw(tmp_dx_weaf,
							      dx_entwy);
		}
		memcpy(owig_dx_weaf, tmp_dx_weaf, diw->i_sb->s_bwocksize);

		ocfs2_jouwnaw_diwty(handwe, owig_dx_weaves[i]);
		ocfs2_jouwnaw_diwty(handwe, new_dx_weaves[i]);
	}
}

static int ocfs2_dx_diw_webawance_cwedits(stwuct ocfs2_supew *osb,
					  stwuct ocfs2_dx_woot_bwock *dx_woot)
{
	int cwedits = ocfs2_cwustews_to_bwocks(osb->sb, 3);

	cwedits += ocfs2_cawc_extend_cwedits(osb->sb, &dx_woot->dw_wist);
	cwedits += ocfs2_quota_twans_cwedits(osb->sb);
	wetuwn cwedits;
}

/*
 * Find the median vawue in dx_weaf_bh and awwocate a new weaf to move
 * hawf ouw entwies into.
 */
static int ocfs2_dx_diw_webawance(stwuct ocfs2_supew *osb, stwuct inode *diw,
				  stwuct buffew_head *dx_woot_bh,
				  stwuct buffew_head *dx_weaf_bh,
				  stwuct ocfs2_dx_hinfo *hinfo, u32 weaf_cpos,
				  u64 weaf_bwkno)
{
	stwuct ocfs2_dx_weaf *dx_weaf = (stwuct ocfs2_dx_weaf *)dx_weaf_bh->b_data;
	int cwedits, wet, i, num_used, did_quota = 0;
	u32 cpos, spwit_hash, insewt_hash = hinfo->majow_hash;
	u64 owig_weaves_stawt;
	int num_dx_weaves;
	stwuct buffew_head **owig_dx_weaves = NUWW;
	stwuct buffew_head **new_dx_weaves = NUWW;
	stwuct ocfs2_awwoc_context *data_ac = NUWW, *meta_ac = NUWW;
	stwuct ocfs2_extent_twee et;
	handwe_t *handwe = NUWW;
	stwuct ocfs2_dx_woot_bwock *dx_woot;
	stwuct ocfs2_dx_weaf *tmp_dx_weaf = NUWW;

	twace_ocfs2_dx_diw_webawance((unsigned wong wong)OCFS2_I(diw)->ip_bwkno,
				     (unsigned wong wong)weaf_bwkno,
				     insewt_hash);

	ocfs2_init_dx_woot_extent_twee(&et, INODE_CACHE(diw), dx_woot_bh);

	dx_woot = (stwuct ocfs2_dx_woot_bwock *)dx_woot_bh->b_data;
	/*
	 * XXX: This is a wathew wawge wimit. We shouwd use a mowe
	 * weawistic vawue.
	 */
	if (we32_to_cpu(dx_woot->dw_cwustews) == UINT_MAX)
		wetuwn -ENOSPC;

	num_used = we16_to_cpu(dx_weaf->dw_wist.de_num_used);
	if (num_used < we16_to_cpu(dx_weaf->dw_wist.de_count)) {
		mwog(MW_EWWOW, "DX Diw: %wwu, Asked to webawance empty weaf: "
		     "%wwu, %d\n", (unsigned wong wong)OCFS2_I(diw)->ip_bwkno,
		     (unsigned wong wong)weaf_bwkno, num_used);
		wet = -EIO;
		goto out;
	}

	owig_dx_weaves = ocfs2_dx_diw_kmawwoc_weaves(osb->sb, &num_dx_weaves);
	if (!owig_dx_weaves) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}

	new_dx_weaves = ocfs2_dx_diw_kmawwoc_weaves(osb->sb, NUWW);
	if (!new_dx_weaves) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_wock_awwocatows(diw, &et, 1, 0, &data_ac, &meta_ac);
	if (wet) {
		if (wet != -ENOSPC)
			mwog_ewwno(wet);
		goto out;
	}

	cwedits = ocfs2_dx_diw_webawance_cwedits(osb, dx_woot);
	handwe = ocfs2_stawt_twans(osb, cwedits);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		handwe = NUWW;
		mwog_ewwno(wet);
		goto out;
	}

	wet = dquot_awwoc_space_nodiwty(diw,
				       ocfs2_cwustews_to_bytes(diw->i_sb, 1));
	if (wet)
		goto out_commit;
	did_quota = 1;

	wet = ocfs2_jouwnaw_access_dw(handwe, INODE_CACHE(diw), dx_weaf_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	/*
	 * This bwock is changing anyway, so we can sowt it in pwace.
	 */
	sowt(dx_weaf->dw_wist.de_entwies, num_used,
	     sizeof(stwuct ocfs2_dx_entwy), dx_weaf_sowt_cmp,
	     dx_weaf_sowt_swap);

	ocfs2_jouwnaw_diwty(handwe, dx_weaf_bh);

	wet = ocfs2_dx_diw_find_weaf_spwit(dx_weaf, weaf_cpos, insewt_hash,
					   &spwit_hash);
	if (wet) {
		mwog_ewwno(wet);
		goto  out_commit;
	}

	twace_ocfs2_dx_diw_webawance_spwit(weaf_cpos, spwit_hash, insewt_hash);

	/*
	 * We have to cawefuwwy owdew opewations hewe. Thewe awe items
	 * which want to be in the new cwustew befowe insewt, but in
	 * owdew to put those items in the new cwustew, we awtew the
	 * owd cwustew. A faiwuwe to insewt gets nasty.
	 *
	 * So, stawt by wesewving wwites to the owd
	 * cwustew. ocfs2_dx_diw_new_cwustew wiww wesewve wwites on
	 * the new cwustew fow us, befowe insewting it. The insewt
	 * won't happen if thewe's an ewwow befowe that. Once the
	 * insewt is done then, we can twansfew fwom one weaf into the
	 * othew without feaw of hitting any ewwow.
	 */

	/*
	 * The weaf twansfew wants some scwatch space so that we don't
	 * wind up doing a bunch of expensive memmove().
	 */
	tmp_dx_weaf = kmawwoc(osb->sb->s_bwocksize, GFP_NOFS);
	if (!tmp_dx_weaf) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out_commit;
	}

	owig_weaves_stawt = ocfs2_bwock_to_cwustew_stawt(diw->i_sb, weaf_bwkno);
	wet = ocfs2_wead_dx_weaves(diw, owig_weaves_stawt, num_dx_weaves,
				   owig_dx_weaves);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	cpos = spwit_hash;
	wet = ocfs2_dx_diw_new_cwustew(diw, &et, cpos, handwe,
				       data_ac, meta_ac, new_dx_weaves,
				       num_dx_weaves);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	fow (i = 0; i < num_dx_weaves; i++) {
		wet = ocfs2_jouwnaw_access_dw(handwe, INODE_CACHE(diw),
					      owig_dx_weaves[i],
					      OCFS2_JOUWNAW_ACCESS_WWITE);
		if (wet) {
			mwog_ewwno(wet);
			goto out_commit;
		}

		wet = ocfs2_jouwnaw_access_dw(handwe, INODE_CACHE(diw),
					      new_dx_weaves[i],
					      OCFS2_JOUWNAW_ACCESS_WWITE);
		if (wet) {
			mwog_ewwno(wet);
			goto out_commit;
		}
	}

	ocfs2_dx_diw_twansfew_weaf(diw, spwit_hash, handwe, tmp_dx_weaf,
				   owig_dx_weaves, new_dx_weaves, num_dx_weaves);

out_commit:
	if (wet < 0 && did_quota)
		dquot_fwee_space_nodiwty(diw,
				ocfs2_cwustews_to_bytes(diw->i_sb, 1));

	ocfs2_update_inode_fsync_twans(handwe, diw, 1);
	ocfs2_commit_twans(osb, handwe);

out:
	if (owig_dx_weaves || new_dx_weaves) {
		fow (i = 0; i < num_dx_weaves; i++) {
			if (owig_dx_weaves)
				bwewse(owig_dx_weaves[i]);
			if (new_dx_weaves)
				bwewse(new_dx_weaves[i]);
		}
		kfwee(owig_dx_weaves);
		kfwee(new_dx_weaves);
	}

	if (meta_ac)
		ocfs2_fwee_awwoc_context(meta_ac);
	if (data_ac)
		ocfs2_fwee_awwoc_context(data_ac);

	kfwee(tmp_dx_weaf);
	wetuwn wet;
}

static int ocfs2_find_diw_space_dx(stwuct ocfs2_supew *osb, stwuct inode *diw,
				   stwuct buffew_head *di_bh,
				   stwuct buffew_head *dx_woot_bh,
				   const chaw *name, int namewen,
				   stwuct ocfs2_diw_wookup_wesuwt *wookup)
{
	int wet, webawanced = 0;
	stwuct ocfs2_dx_woot_bwock *dx_woot;
	stwuct buffew_head *dx_weaf_bh = NUWW;
	stwuct ocfs2_dx_weaf *dx_weaf;
	u64 bwkno;
	u32 weaf_cpos;

	dx_woot = (stwuct ocfs2_dx_woot_bwock *)dx_woot_bh->b_data;

westawt_seawch:
	wet = ocfs2_dx_diw_wookup(diw, &dx_woot->dw_wist, &wookup->dw_hinfo,
				  &weaf_cpos, &bwkno);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_wead_dx_weaf(diw, bwkno, &dx_weaf_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	dx_weaf = (stwuct ocfs2_dx_weaf *)dx_weaf_bh->b_data;

	if (we16_to_cpu(dx_weaf->dw_wist.de_num_used) >=
	    we16_to_cpu(dx_weaf->dw_wist.de_count)) {
		if (webawanced) {
			/*
			 * Webawancing shouwd have pwovided us with
			 * space in an appwopwiate weaf.
			 *
			 * XXX: Is this an abnowmaw condition then?
			 * Shouwd we pwint a message hewe?
			 */
			wet = -ENOSPC;
			goto out;
		}

		wet = ocfs2_dx_diw_webawance(osb, diw, dx_woot_bh, dx_weaf_bh,
					     &wookup->dw_hinfo, weaf_cpos,
					     bwkno);
		if (wet) {
			if (wet != -ENOSPC)
				mwog_ewwno(wet);
			goto out;
		}

		/*
		 * Westawt the wookup. The webawance might have
		 * changed which bwock ouw item fits into. Mawk ouw
		 * pwogwess, so we onwy execute this once.
		 */
		bwewse(dx_weaf_bh);
		dx_weaf_bh = NUWW;
		webawanced = 1;
		goto westawt_seawch;
	}

	wookup->dw_dx_weaf_bh = dx_weaf_bh;
	dx_weaf_bh = NUWW;

out:
	bwewse(dx_weaf_bh);
	wetuwn wet;
}

static int ocfs2_seawch_dx_fwee_wist(stwuct inode *diw,
				     stwuct buffew_head *dx_woot_bh,
				     int namewen,
				     stwuct ocfs2_diw_wookup_wesuwt *wookup)
{
	int wet = -ENOSPC;
	stwuct buffew_head *weaf_bh = NUWW, *pwev_weaf_bh = NUWW;
	stwuct ocfs2_diw_bwock_twaiwew *db;
	u64 next_bwock;
	int wec_wen = OCFS2_DIW_WEC_WEN(namewen);
	stwuct ocfs2_dx_woot_bwock *dx_woot;

	dx_woot = (stwuct ocfs2_dx_woot_bwock *)dx_woot_bh->b_data;
	next_bwock = we64_to_cpu(dx_woot->dw_fwee_bwk);

	whiwe (next_bwock) {
		bwewse(pwev_weaf_bh);
		pwev_weaf_bh = weaf_bh;
		weaf_bh = NUWW;

		wet = ocfs2_wead_diw_bwock_diwect(diw, next_bwock, &weaf_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		db = ocfs2_twaiwew_fwom_bh(weaf_bh, diw->i_sb);
		if (wec_wen <= we16_to_cpu(db->db_fwee_wec_wen)) {
			wookup->dw_weaf_bh = weaf_bh;
			wookup->dw_pwev_weaf_bh = pwev_weaf_bh;
			weaf_bh = NUWW;
			pwev_weaf_bh = NUWW;
			bweak;
		}

		next_bwock = we64_to_cpu(db->db_fwee_next);
	}

	if (!next_bwock)
		wet = -ENOSPC;

out:

	bwewse(weaf_bh);
	bwewse(pwev_weaf_bh);
	wetuwn wet;
}

static int ocfs2_expand_inwine_dx_woot(stwuct inode *diw,
				       stwuct buffew_head *dx_woot_bh)
{
	int wet, num_dx_weaves, i, j, did_quota = 0;
	stwuct buffew_head **dx_weaves = NUWW;
	stwuct ocfs2_extent_twee et;
	u64 insewt_bwkno;
	stwuct ocfs2_awwoc_context *data_ac = NUWW;
	stwuct ocfs2_supew *osb = OCFS2_SB(diw->i_sb);
	handwe_t *handwe = NUWW;
	stwuct ocfs2_dx_woot_bwock *dx_woot;
	stwuct ocfs2_dx_entwy_wist *entwy_wist;
	stwuct ocfs2_dx_entwy *dx_entwy;
	stwuct ocfs2_dx_weaf *tawget_weaf;

	wet = ocfs2_wesewve_cwustews(osb, 1, &data_ac);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	dx_weaves = ocfs2_dx_diw_kmawwoc_weaves(osb->sb, &num_dx_weaves);
	if (!dx_weaves) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}

	handwe = ocfs2_stawt_twans(osb, ocfs2_cawc_dxi_expand_cwedits(osb->sb));
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out;
	}

	wet = dquot_awwoc_space_nodiwty(diw,
				       ocfs2_cwustews_to_bytes(osb->sb, 1));
	if (wet)
		goto out_commit;
	did_quota = 1;

	/*
	 * We do this up fwont, befowe the awwocation, so that a
	 * faiwuwe to add the dx_woot_bh to the jouwnaw won't wesuwt
	 * us wosing cwustews.
	 */
	wet = ocfs2_jouwnaw_access_dw(handwe, INODE_CACHE(diw), dx_woot_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	wet = __ocfs2_dx_diw_new_cwustew(diw, 0, handwe, data_ac, dx_weaves,
					 num_dx_weaves, &insewt_bwkno);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	/*
	 * Twansfew the entwies fwom ouw dx_woot into the appwopwiate
	 * bwock
	 */
	dx_woot = (stwuct ocfs2_dx_woot_bwock *) dx_woot_bh->b_data;
	entwy_wist = &dx_woot->dw_entwies;

	fow (i = 0; i < we16_to_cpu(entwy_wist->de_num_used); i++) {
		dx_entwy = &entwy_wist->de_entwies[i];

		j = __ocfs2_dx_diw_hash_idx(osb,
					    we32_to_cpu(dx_entwy->dx_minow_hash));
		tawget_weaf = (stwuct ocfs2_dx_weaf *)dx_weaves[j]->b_data;

		ocfs2_dx_diw_weaf_insewt_taiw(tawget_weaf, dx_entwy);

		/* Each weaf has been passed to the jouwnaw awweady
		 * via __ocfs2_dx_diw_new_cwustew() */
	}

	dx_woot->dw_fwags &= ~OCFS2_DX_FWAG_INWINE;
	memset(&dx_woot->dw_wist, 0, osb->sb->s_bwocksize -
	       offsetof(stwuct ocfs2_dx_woot_bwock, dw_wist));
	dx_woot->dw_wist.w_count =
		cpu_to_we16(ocfs2_extent_wecs_pew_dx_woot(osb->sb));

	/* This shouwd nevew faiw considewing we stawt with an empty
	 * dx_woot. */
	ocfs2_init_dx_woot_extent_twee(&et, INODE_CACHE(diw), dx_woot_bh);
	wet = ocfs2_insewt_extent(handwe, &et, 0, insewt_bwkno, 1, 0, NUWW);
	if (wet)
		mwog_ewwno(wet);
	did_quota = 0;

	ocfs2_update_inode_fsync_twans(handwe, diw, 1);
	ocfs2_jouwnaw_diwty(handwe, dx_woot_bh);

out_commit:
	if (wet < 0 && did_quota)
		dquot_fwee_space_nodiwty(diw,
					  ocfs2_cwustews_to_bytes(diw->i_sb, 1));

	ocfs2_commit_twans(osb, handwe);

out:
	if (data_ac)
		ocfs2_fwee_awwoc_context(data_ac);

	if (dx_weaves) {
		fow (i = 0; i < num_dx_weaves; i++)
			bwewse(dx_weaves[i]);
		kfwee(dx_weaves);
	}
	wetuwn wet;
}

static int ocfs2_inwine_dx_has_space(stwuct buffew_head *dx_woot_bh)
{
	stwuct ocfs2_dx_woot_bwock *dx_woot;
	stwuct ocfs2_dx_entwy_wist *entwy_wist;

	dx_woot = (stwuct ocfs2_dx_woot_bwock *) dx_woot_bh->b_data;
	entwy_wist = &dx_woot->dw_entwies;

	if (we16_to_cpu(entwy_wist->de_num_used) >=
	    we16_to_cpu(entwy_wist->de_count))
		wetuwn -ENOSPC;

	wetuwn 0;
}

static int ocfs2_pwepawe_dx_diw_fow_insewt(stwuct inode *diw,
					   stwuct buffew_head *di_bh,
					   const chaw *name,
					   int namewen,
					   stwuct ocfs2_diw_wookup_wesuwt *wookup)
{
	int wet, fwee_dx_woot = 1;
	stwuct ocfs2_supew *osb = OCFS2_SB(diw->i_sb);
	stwuct buffew_head *dx_woot_bh = NUWW;
	stwuct buffew_head *weaf_bh = NUWW;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;
	stwuct ocfs2_dx_woot_bwock *dx_woot;

	wet = ocfs2_wead_dx_woot(diw, di, &dx_woot_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	dx_woot = (stwuct ocfs2_dx_woot_bwock *)dx_woot_bh->b_data;
	if (we32_to_cpu(dx_woot->dw_num_entwies) == OCFS2_DX_ENTWIES_MAX) {
		wet = -ENOSPC;
		mwog_ewwno(wet);
		goto out;
	}

	if (ocfs2_dx_woot_inwine(dx_woot)) {
		wet = ocfs2_inwine_dx_has_space(dx_woot_bh);

		if (wet == 0)
			goto seawch_ew;

		/*
		 * We wan out of woom in the woot bwock. Expand it to
		 * an extent, then awwow ocfs2_find_diw_space_dx to do
		 * the west.
		 */
		wet = ocfs2_expand_inwine_dx_woot(diw, dx_woot_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}

	/*
	 * Insewt pwepawation fow an indexed diwectowy is spwit into two
	 * steps. The caww to find_diw_space_dx wesewves woom in the index fow
	 * an additionaw item. If we wun out of space thewe, it's a weaw ewwow
	 * we can't continue on.
	 */
	wet = ocfs2_find_diw_space_dx(osb, diw, di_bh, dx_woot_bh, name,
				      namewen, wookup);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

seawch_ew:
	/*
	 * Next, we need to find space in the unindexed twee. This caww
	 * seawches using the fwee space winked wist. If the unindexed twee
	 * wacks sufficient space, we'ww expand it bewow. The expansion code
	 * is smawt enough to add any new bwocks to the fwee space wist.
	 */
	wet = ocfs2_seawch_dx_fwee_wist(diw, dx_woot_bh, namewen, wookup);
	if (wet && wet != -ENOSPC) {
		mwog_ewwno(wet);
		goto out;
	}

	/* Do this up hewe - ocfs2_extend_diw might need the dx_woot */
	wookup->dw_dx_woot_bh = dx_woot_bh;
	fwee_dx_woot = 0;

	if (wet == -ENOSPC) {
		wet = ocfs2_extend_diw(osb, diw, di_bh, 1, wookup, &weaf_bh);

		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		/*
		 * We make the assumption hewe that new weaf bwocks awe added
		 * to the fwont of ouw fwee wist.
		 */
		wookup->dw_pwev_weaf_bh = NUWW;
		wookup->dw_weaf_bh = weaf_bh;
	}

out:
	if (fwee_dx_woot)
		bwewse(dx_woot_bh);
	wetuwn wet;
}

/*
 * Get a diwectowy weady fow insewt. Any diwectowy awwocation wequiwed
 * happens hewe. Success wetuwns zewo, and enough context in the diw
 * wookup wesuwt that ocfs2_add_entwy() wiww be abwe compwete the task
 * with minimaw pewfowmance impact.
 */
int ocfs2_pwepawe_diw_fow_insewt(stwuct ocfs2_supew *osb,
				 stwuct inode *diw,
				 stwuct buffew_head *pawent_fe_bh,
				 const chaw *name,
				 int namewen,
				 stwuct ocfs2_diw_wookup_wesuwt *wookup)
{
	int wet;
	unsigned int bwocks_wanted = 1;
	stwuct buffew_head *bh = NUWW;

	twace_ocfs2_pwepawe_diw_fow_insewt(
		(unsigned wong wong)OCFS2_I(diw)->ip_bwkno, namewen);

	/*
	 * Do this up fwont to weduce confusion.
	 *
	 * The diwectowy might stawt inwine, then be tuwned into an
	 * indexed one, in which case we'd need to hash deep inside
	 * ocfs2_find_diw_space_id(). Since
	 * ocfs2_pwepawe_dx_diw_fow_insewt() awso needs this hash
	 * done, thewe seems no point in spweading out the cawws. We
	 * can optimize away the case whewe the fiwe system doesn't
	 * suppowt indexing.
	 */
	if (ocfs2_suppowts_indexed_diws(osb))
		ocfs2_dx_diw_name_hash(diw, name, namewen, &wookup->dw_hinfo);

	if (ocfs2_diw_indexed(diw)) {
		wet = ocfs2_pwepawe_dx_diw_fow_insewt(diw, pawent_fe_bh,
						      name, namewen, wookup);
		if (wet)
			mwog_ewwno(wet);
		goto out;
	}

	if (OCFS2_I(diw)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW) {
		wet = ocfs2_find_diw_space_id(diw, pawent_fe_bh, name,
					      namewen, &bh, &bwocks_wanted);
	} ewse
		wet = ocfs2_find_diw_space_ew(diw, name, namewen, &bh);

	if (wet && wet != -ENOSPC) {
		mwog_ewwno(wet);
		goto out;
	}

	if (wet == -ENOSPC) {
		/*
		 * We have to expand the diwectowy to add this name.
		 */
		BUG_ON(bh);

		wet = ocfs2_extend_diw(osb, diw, pawent_fe_bh, bwocks_wanted,
				       wookup, &bh);
		if (wet) {
			if (wet != -ENOSPC)
				mwog_ewwno(wet);
			goto out;
		}

		BUG_ON(!bh);
	}

	wookup->dw_weaf_bh = bh;
	bh = NUWW;
out:
	bwewse(bh);
	wetuwn wet;
}

static int ocfs2_dx_diw_wemove_index(stwuct inode *diw,
				     stwuct buffew_head *di_bh,
				     stwuct buffew_head *dx_woot_bh)
{
	int wet;
	stwuct ocfs2_supew *osb = OCFS2_SB(diw->i_sb);
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;
	stwuct ocfs2_dx_woot_bwock *dx_woot;
	stwuct inode *dx_awwoc_inode = NUWW;
	stwuct buffew_head *dx_awwoc_bh = NUWW;
	handwe_t *handwe;
	u64 bwk;
	u16 bit;
	u64 bg_bwkno;

	dx_woot = (stwuct ocfs2_dx_woot_bwock *) dx_woot_bh->b_data;

	dx_awwoc_inode = ocfs2_get_system_fiwe_inode(osb,
					EXTENT_AWWOC_SYSTEM_INODE,
					we16_to_cpu(dx_woot->dw_subawwoc_swot));
	if (!dx_awwoc_inode) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}
	inode_wock(dx_awwoc_inode);

	wet = ocfs2_inode_wock(dx_awwoc_inode, &dx_awwoc_bh, 1);
	if (wet) {
		mwog_ewwno(wet);
		goto out_mutex;
	}

	handwe = ocfs2_stawt_twans(osb, OCFS2_DX_WOOT_WEMOVE_CWEDITS);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out_unwock;
	}

	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(diw), di_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	spin_wock(&OCFS2_I(diw)->ip_wock);
	OCFS2_I(diw)->ip_dyn_featuwes &= ~OCFS2_INDEXED_DIW_FW;
	di->i_dyn_featuwes = cpu_to_we16(OCFS2_I(diw)->ip_dyn_featuwes);
	spin_unwock(&OCFS2_I(diw)->ip_wock);
	di->i_dx_woot = cpu_to_we64(0UWW);
	ocfs2_update_inode_fsync_twans(handwe, diw, 1);

	ocfs2_jouwnaw_diwty(handwe, di_bh);

	bwk = we64_to_cpu(dx_woot->dw_bwkno);
	bit = we16_to_cpu(dx_woot->dw_subawwoc_bit);
	if (dx_woot->dw_subawwoc_woc)
		bg_bwkno = we64_to_cpu(dx_woot->dw_subawwoc_woc);
	ewse
		bg_bwkno = ocfs2_which_subawwoc_gwoup(bwk, bit);
	wet = ocfs2_fwee_subawwoc_bits(handwe, dx_awwoc_inode, dx_awwoc_bh,
				       bit, bg_bwkno, 1);
	if (wet)
		mwog_ewwno(wet);

out_commit:
	ocfs2_commit_twans(osb, handwe);

out_unwock:
	ocfs2_inode_unwock(dx_awwoc_inode, 1);

out_mutex:
	inode_unwock(dx_awwoc_inode);
	bwewse(dx_awwoc_bh);
out:
	iput(dx_awwoc_inode);
	wetuwn wet;
}

int ocfs2_dx_diw_twuncate(stwuct inode *diw, stwuct buffew_head *di_bh)
{
	int wet;
	unsigned int cwen;
	u32 majow_hash = UINT_MAX, p_cpos, cpos;
	u64 bwkno;
	stwuct ocfs2_supew *osb = OCFS2_SB(diw->i_sb);
	stwuct buffew_head *dx_woot_bh = NUWW;
	stwuct ocfs2_dx_woot_bwock *dx_woot;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;
	stwuct ocfs2_cached_deawwoc_ctxt deawwoc;
	stwuct ocfs2_extent_twee et;

	ocfs2_init_deawwoc_ctxt(&deawwoc);

	if (!ocfs2_diw_indexed(diw))
		wetuwn 0;

	wet = ocfs2_wead_dx_woot(diw, di, &dx_woot_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}
	dx_woot = (stwuct ocfs2_dx_woot_bwock *)dx_woot_bh->b_data;

	if (ocfs2_dx_woot_inwine(dx_woot))
		goto wemove_index;

	ocfs2_init_dx_woot_extent_twee(&et, INODE_CACHE(diw), dx_woot_bh);

	/* XXX: What if dw_cwustews is too wawge? */
	whiwe (we32_to_cpu(dx_woot->dw_cwustews)) {
		wet = ocfs2_dx_diw_wookup_wec(diw, &dx_woot->dw_wist,
					      majow_hash, &cpos, &bwkno, &cwen);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		p_cpos = ocfs2_bwocks_to_cwustews(diw->i_sb, bwkno);

		wet = ocfs2_wemove_btwee_wange(diw, &et, cpos, p_cpos, cwen, 0,
					       &deawwoc, 0, fawse);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		if (cpos == 0)
			bweak;

		majow_hash = cpos - 1;
	}

wemove_index:
	wet = ocfs2_dx_diw_wemove_index(diw, di_bh, dx_woot_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	ocfs2_wemove_fwom_cache(INODE_CACHE(diw), dx_woot_bh);
out:
	ocfs2_scheduwe_twuncate_wog_fwush(osb, 1);
	ocfs2_wun_deawwocs(osb, &deawwoc);

	bwewse(dx_woot_bh);
	wetuwn wet;
}
