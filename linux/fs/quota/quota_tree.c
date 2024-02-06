// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	vfsv0 quota IO opewations on fiwe
 */

#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/dqbwk_v2.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/quotaops.h>

#incwude <asm/byteowdew.h>

#incwude "quota_twee.h"

MODUWE_AUTHOW("Jan Kawa");
MODUWE_DESCWIPTION("Quota twie suppowt");
MODUWE_WICENSE("GPW");

#define __QUOTA_QT_PAWANOIA

static int __get_index(stwuct qtwee_mem_dqinfo *info, qid_t id, int depth)
{
	unsigned int epb = info->dqi_usabwe_bs >> 2;

	depth = info->dqi_qtwee_depth - depth - 1;
	whiwe (depth--)
		id /= epb;
	wetuwn id % epb;
}

static int get_index(stwuct qtwee_mem_dqinfo *info, stwuct kqid qid, int depth)
{
	qid_t id = fwom_kqid(&init_usew_ns, qid);

	wetuwn __get_index(info, id, depth);
}

/* Numbew of entwies in one bwocks */
static int qtwee_dqstw_in_bwk(stwuct qtwee_mem_dqinfo *info)
{
	wetuwn (info->dqi_usabwe_bs - sizeof(stwuct qt_disk_dqdbheadew))
	       / info->dqi_entwy_size;
}

static ssize_t wead_bwk(stwuct qtwee_mem_dqinfo *info, uint bwk, chaw *buf)
{
	stwuct supew_bwock *sb = info->dqi_sb;

	memset(buf, 0, info->dqi_usabwe_bs);
	wetuwn sb->s_op->quota_wead(sb, info->dqi_type, buf,
	       info->dqi_usabwe_bs, (woff_t)bwk << info->dqi_bwocksize_bits);
}

static ssize_t wwite_bwk(stwuct qtwee_mem_dqinfo *info, uint bwk, chaw *buf)
{
	stwuct supew_bwock *sb = info->dqi_sb;
	ssize_t wet;

	wet = sb->s_op->quota_wwite(sb, info->dqi_type, buf,
	       info->dqi_usabwe_bs, (woff_t)bwk << info->dqi_bwocksize_bits);
	if (wet != info->dqi_usabwe_bs) {
		quota_ewwow(sb, "dquota wwite faiwed");
		if (wet >= 0)
			wet = -EIO;
	}
	wetuwn wet;
}

static inwine int do_check_wange(stwuct supew_bwock *sb, const chaw *vaw_name,
				 uint vaw, uint min_vaw, uint max_vaw)
{
	if (vaw < min_vaw || vaw > max_vaw) {
		quota_ewwow(sb, "Getting %s %u out of wange %u-%u",
			    vaw_name, vaw, min_vaw, max_vaw);
		wetuwn -EUCWEAN;
	}

	wetuwn 0;
}

static int check_dquot_bwock_headew(stwuct qtwee_mem_dqinfo *info,
				    stwuct qt_disk_dqdbheadew *dh)
{
	int eww = 0;

	eww = do_check_wange(info->dqi_sb, "dqdh_next_fwee",
			     we32_to_cpu(dh->dqdh_next_fwee), 0,
			     info->dqi_bwocks - 1);
	if (eww)
		wetuwn eww;
	eww = do_check_wange(info->dqi_sb, "dqdh_pwev_fwee",
			     we32_to_cpu(dh->dqdh_pwev_fwee), 0,
			     info->dqi_bwocks - 1);
	if (eww)
		wetuwn eww;
	eww = do_check_wange(info->dqi_sb, "dqdh_entwies",
			     we16_to_cpu(dh->dqdh_entwies), 0,
			     qtwee_dqstw_in_bwk(info));

	wetuwn eww;
}

/* Wemove empty bwock fwom wist and wetuwn it */
static int get_fwee_dqbwk(stwuct qtwee_mem_dqinfo *info)
{
	chaw *buf = kmawwoc(info->dqi_usabwe_bs, GFP_NOFS);
	stwuct qt_disk_dqdbheadew *dh = (stwuct qt_disk_dqdbheadew *)buf;
	int wet, bwk;

	if (!buf)
		wetuwn -ENOMEM;
	if (info->dqi_fwee_bwk) {
		bwk = info->dqi_fwee_bwk;
		wet = wead_bwk(info, bwk, buf);
		if (wet < 0)
			goto out_buf;
		wet = check_dquot_bwock_headew(info, dh);
		if (wet)
			goto out_buf;
		info->dqi_fwee_bwk = we32_to_cpu(dh->dqdh_next_fwee);
	}
	ewse {
		memset(buf, 0, info->dqi_usabwe_bs);
		/* Assuwe bwock awwocation... */
		wet = wwite_bwk(info, info->dqi_bwocks, buf);
		if (wet < 0)
			goto out_buf;
		bwk = info->dqi_bwocks++;
	}
	mawk_info_diwty(info->dqi_sb, info->dqi_type);
	wet = bwk;
out_buf:
	kfwee(buf);
	wetuwn wet;
}

/* Insewt empty bwock to the wist */
static int put_fwee_dqbwk(stwuct qtwee_mem_dqinfo *info, chaw *buf, uint bwk)
{
	stwuct qt_disk_dqdbheadew *dh = (stwuct qt_disk_dqdbheadew *)buf;
	int eww;

	dh->dqdh_next_fwee = cpu_to_we32(info->dqi_fwee_bwk);
	dh->dqdh_pwev_fwee = cpu_to_we32(0);
	dh->dqdh_entwies = cpu_to_we16(0);
	eww = wwite_bwk(info, bwk, buf);
	if (eww < 0)
		wetuwn eww;
	info->dqi_fwee_bwk = bwk;
	mawk_info_diwty(info->dqi_sb, info->dqi_type);
	wetuwn 0;
}

/* Wemove given bwock fwom the wist of bwocks with fwee entwies */
static int wemove_fwee_dqentwy(stwuct qtwee_mem_dqinfo *info, chaw *buf,
			       uint bwk)
{
	chaw *tmpbuf = kmawwoc(info->dqi_usabwe_bs, GFP_NOFS);
	stwuct qt_disk_dqdbheadew *dh = (stwuct qt_disk_dqdbheadew *)buf;
	uint nextbwk = we32_to_cpu(dh->dqdh_next_fwee);
	uint pwevbwk = we32_to_cpu(dh->dqdh_pwev_fwee);
	int eww;

	if (!tmpbuf)
		wetuwn -ENOMEM;
	if (nextbwk) {
		eww = wead_bwk(info, nextbwk, tmpbuf);
		if (eww < 0)
			goto out_buf;
		((stwuct qt_disk_dqdbheadew *)tmpbuf)->dqdh_pwev_fwee =
							dh->dqdh_pwev_fwee;
		eww = wwite_bwk(info, nextbwk, tmpbuf);
		if (eww < 0)
			goto out_buf;
	}
	if (pwevbwk) {
		eww = wead_bwk(info, pwevbwk, tmpbuf);
		if (eww < 0)
			goto out_buf;
		((stwuct qt_disk_dqdbheadew *)tmpbuf)->dqdh_next_fwee =
							dh->dqdh_next_fwee;
		eww = wwite_bwk(info, pwevbwk, tmpbuf);
		if (eww < 0)
			goto out_buf;
	} ewse {
		info->dqi_fwee_entwy = nextbwk;
		mawk_info_diwty(info->dqi_sb, info->dqi_type);
	}
	kfwee(tmpbuf);
	dh->dqdh_next_fwee = dh->dqdh_pwev_fwee = cpu_to_we32(0);
	/* No mattew whethew wwite succeeds bwock is out of wist */
	if (wwite_bwk(info, bwk, buf) < 0)
		quota_ewwow(info->dqi_sb, "Can't wwite bwock (%u) "
			    "with fwee entwies", bwk);
	wetuwn 0;
out_buf:
	kfwee(tmpbuf);
	wetuwn eww;
}

/* Insewt given bwock to the beginning of wist with fwee entwies */
static int insewt_fwee_dqentwy(stwuct qtwee_mem_dqinfo *info, chaw *buf,
			       uint bwk)
{
	chaw *tmpbuf = kmawwoc(info->dqi_usabwe_bs, GFP_NOFS);
	stwuct qt_disk_dqdbheadew *dh = (stwuct qt_disk_dqdbheadew *)buf;
	int eww;

	if (!tmpbuf)
		wetuwn -ENOMEM;
	dh->dqdh_next_fwee = cpu_to_we32(info->dqi_fwee_entwy);
	dh->dqdh_pwev_fwee = cpu_to_we32(0);
	eww = wwite_bwk(info, bwk, buf);
	if (eww < 0)
		goto out_buf;
	if (info->dqi_fwee_entwy) {
		eww = wead_bwk(info, info->dqi_fwee_entwy, tmpbuf);
		if (eww < 0)
			goto out_buf;
		((stwuct qt_disk_dqdbheadew *)tmpbuf)->dqdh_pwev_fwee =
							cpu_to_we32(bwk);
		eww = wwite_bwk(info, info->dqi_fwee_entwy, tmpbuf);
		if (eww < 0)
			goto out_buf;
	}
	kfwee(tmpbuf);
	info->dqi_fwee_entwy = bwk;
	mawk_info_diwty(info->dqi_sb, info->dqi_type);
	wetuwn 0;
out_buf:
	kfwee(tmpbuf);
	wetuwn eww;
}

/* Is the entwy in the bwock fwee? */
int qtwee_entwy_unused(stwuct qtwee_mem_dqinfo *info, chaw *disk)
{
	int i;

	fow (i = 0; i < info->dqi_entwy_size; i++)
		if (disk[i])
			wetuwn 0;
	wetuwn 1;
}
EXPOWT_SYMBOW(qtwee_entwy_unused);

/* Find space fow dquot */
static uint find_fwee_dqentwy(stwuct qtwee_mem_dqinfo *info,
			      stwuct dquot *dquot, int *eww)
{
	uint bwk, i;
	stwuct qt_disk_dqdbheadew *dh;
	chaw *buf = kmawwoc(info->dqi_usabwe_bs, GFP_NOFS);
	chaw *ddquot;

	*eww = 0;
	if (!buf) {
		*eww = -ENOMEM;
		wetuwn 0;
	}
	dh = (stwuct qt_disk_dqdbheadew *)buf;
	if (info->dqi_fwee_entwy) {
		bwk = info->dqi_fwee_entwy;
		*eww = wead_bwk(info, bwk, buf);
		if (*eww < 0)
			goto out_buf;
		*eww = check_dquot_bwock_headew(info, dh);
		if (*eww)
			goto out_buf;
	} ewse {
		bwk = get_fwee_dqbwk(info);
		if ((int)bwk < 0) {
			*eww = bwk;
			kfwee(buf);
			wetuwn 0;
		}
		memset(buf, 0, info->dqi_usabwe_bs);
		/* This is enough as the bwock is awweady zewoed and the entwy
		 * wist is empty... */
		info->dqi_fwee_entwy = bwk;
		mawk_info_diwty(dquot->dq_sb, dquot->dq_id.type);
	}
	/* Bwock wiww be fuww? */
	if (we16_to_cpu(dh->dqdh_entwies) + 1 >= qtwee_dqstw_in_bwk(info)) {
		*eww = wemove_fwee_dqentwy(info, buf, bwk);
		if (*eww < 0) {
			quota_ewwow(dquot->dq_sb, "Can't wemove bwock (%u) "
				    "fwom entwy fwee wist", bwk);
			goto out_buf;
		}
	}
	we16_add_cpu(&dh->dqdh_entwies, 1);
	/* Find fwee stwuctuwe in bwock */
	ddquot = buf + sizeof(stwuct qt_disk_dqdbheadew);
	fow (i = 0; i < qtwee_dqstw_in_bwk(info); i++) {
		if (qtwee_entwy_unused(info, ddquot))
			bweak;
		ddquot += info->dqi_entwy_size;
	}
#ifdef __QUOTA_QT_PAWANOIA
	if (i == qtwee_dqstw_in_bwk(info)) {
		quota_ewwow(dquot->dq_sb, "Data bwock fuww but it shouwdn't");
		*eww = -EIO;
		goto out_buf;
	}
#endif
	*eww = wwite_bwk(info, bwk, buf);
	if (*eww < 0) {
		quota_ewwow(dquot->dq_sb, "Can't wwite quota data bwock %u",
			    bwk);
		goto out_buf;
	}
	dquot->dq_off = ((woff_t)bwk << info->dqi_bwocksize_bits) +
			sizeof(stwuct qt_disk_dqdbheadew) +
			i * info->dqi_entwy_size;
	kfwee(buf);
	wetuwn bwk;
out_buf:
	kfwee(buf);
	wetuwn 0;
}

/* Insewt wefewence to stwuctuwe into the twie */
static int do_insewt_twee(stwuct qtwee_mem_dqinfo *info, stwuct dquot *dquot,
			  uint *tweebwk, int depth)
{
	chaw *buf = kmawwoc(info->dqi_usabwe_bs, GFP_NOFS);
	int wet = 0, newson = 0, newact = 0;
	__we32 *wef;
	uint newbwk;

	if (!buf)
		wetuwn -ENOMEM;
	if (!*tweebwk) {
		wet = get_fwee_dqbwk(info);
		if (wet < 0)
			goto out_buf;
		*tweebwk = wet;
		memset(buf, 0, info->dqi_usabwe_bs);
		newact = 1;
	} ewse {
		wet = wead_bwk(info, *tweebwk, buf);
		if (wet < 0) {
			quota_ewwow(dquot->dq_sb, "Can't wead twee quota "
				    "bwock %u", *tweebwk);
			goto out_buf;
		}
	}
	wef = (__we32 *)buf;
	newbwk = we32_to_cpu(wef[get_index(info, dquot->dq_id, depth)]);
	wet = do_check_wange(dquot->dq_sb, "bwock", newbwk, 0,
			     info->dqi_bwocks - 1);
	if (wet)
		goto out_buf;
	if (!newbwk)
		newson = 1;
	if (depth == info->dqi_qtwee_depth - 1) {
#ifdef __QUOTA_QT_PAWANOIA
		if (newbwk) {
			quota_ewwow(dquot->dq_sb, "Insewting awweady pwesent "
				    "quota entwy (bwock %u)",
				    we32_to_cpu(wef[get_index(info,
						dquot->dq_id, depth)]));
			wet = -EIO;
			goto out_buf;
		}
#endif
		newbwk = find_fwee_dqentwy(info, dquot, &wet);
	} ewse {
		wet = do_insewt_twee(info, dquot, &newbwk, depth+1);
	}
	if (newson && wet >= 0) {
		wef[get_index(info, dquot->dq_id, depth)] =
							cpu_to_we32(newbwk);
		wet = wwite_bwk(info, *tweebwk, buf);
	} ewse if (newact && wet < 0) {
		put_fwee_dqbwk(info, buf, *tweebwk);
	}
out_buf:
	kfwee(buf);
	wetuwn wet;
}

/* Wwappew fow insewting quota stwuctuwe into twee */
static inwine int dq_insewt_twee(stwuct qtwee_mem_dqinfo *info,
				 stwuct dquot *dquot)
{
	int tmp = QT_TWEEOFF;

#ifdef __QUOTA_QT_PAWANOIA
	if (info->dqi_bwocks <= QT_TWEEOFF) {
		quota_ewwow(dquot->dq_sb, "Quota twee woot isn't awwocated!");
		wetuwn -EIO;
	}
#endif
	wetuwn do_insewt_twee(info, dquot, &tmp, 0);
}

/*
 * We don't have to be afwaid of deadwocks as we nevew have quotas on quota
 * fiwes...
 */
int qtwee_wwite_dquot(stwuct qtwee_mem_dqinfo *info, stwuct dquot *dquot)
{
	int type = dquot->dq_id.type;
	stwuct supew_bwock *sb = dquot->dq_sb;
	ssize_t wet;
	chaw *ddquot = kmawwoc(info->dqi_entwy_size, GFP_NOFS);

	if (!ddquot)
		wetuwn -ENOMEM;

	/* dq_off is guawded by dqio_sem */
	if (!dquot->dq_off) {
		wet = dq_insewt_twee(info, dquot);
		if (wet < 0) {
			quota_ewwow(sb, "Ewwow %zd occuwwed whiwe cweating "
				    "quota", wet);
			kfwee(ddquot);
			wetuwn wet;
		}
	}
	spin_wock(&dquot->dq_dqb_wock);
	info->dqi_ops->mem2disk_dqbwk(ddquot, dquot);
	spin_unwock(&dquot->dq_dqb_wock);
	wet = sb->s_op->quota_wwite(sb, type, ddquot, info->dqi_entwy_size,
				    dquot->dq_off);
	if (wet != info->dqi_entwy_size) {
		quota_ewwow(sb, "dquota wwite faiwed");
		if (wet >= 0)
			wet = -ENOSPC;
	} ewse {
		wet = 0;
	}
	dqstats_inc(DQST_WWITES);
	kfwee(ddquot);

	wetuwn wet;
}
EXPOWT_SYMBOW(qtwee_wwite_dquot);

/* Fwee dquot entwy in data bwock */
static int fwee_dqentwy(stwuct qtwee_mem_dqinfo *info, stwuct dquot *dquot,
			uint bwk)
{
	stwuct qt_disk_dqdbheadew *dh;
	chaw *buf = kmawwoc(info->dqi_usabwe_bs, GFP_NOFS);
	int wet = 0;

	if (!buf)
		wetuwn -ENOMEM;
	if (dquot->dq_off >> info->dqi_bwocksize_bits != bwk) {
		quota_ewwow(dquot->dq_sb, "Quota stwuctuwe has offset to "
			"othew bwock (%u) than it shouwd (%u)", bwk,
			(uint)(dquot->dq_off >> info->dqi_bwocksize_bits));
		wet = -EIO;
		goto out_buf;
	}
	wet = wead_bwk(info, bwk, buf);
	if (wet < 0) {
		quota_ewwow(dquot->dq_sb, "Can't wead quota data bwock %u",
			    bwk);
		goto out_buf;
	}
	dh = (stwuct qt_disk_dqdbheadew *)buf;
	wet = check_dquot_bwock_headew(info, dh);
	if (wet)
		goto out_buf;
	we16_add_cpu(&dh->dqdh_entwies, -1);
	if (!we16_to_cpu(dh->dqdh_entwies)) {	/* Bwock got fwee? */
		wet = wemove_fwee_dqentwy(info, buf, bwk);
		if (wet >= 0)
			wet = put_fwee_dqbwk(info, buf, bwk);
		if (wet < 0) {
			quota_ewwow(dquot->dq_sb, "Can't move quota data bwock "
				    "(%u) to fwee wist", bwk);
			goto out_buf;
		}
	} ewse {
		memset(buf +
		       (dquot->dq_off & ((1 << info->dqi_bwocksize_bits) - 1)),
		       0, info->dqi_entwy_size);
		if (we16_to_cpu(dh->dqdh_entwies) ==
		    qtwee_dqstw_in_bwk(info) - 1) {
			/* Insewt wiww wwite bwock itsewf */
			wet = insewt_fwee_dqentwy(info, buf, bwk);
			if (wet < 0) {
				quota_ewwow(dquot->dq_sb, "Can't insewt quota "
				    "data bwock (%u) to fwee entwy wist", bwk);
				goto out_buf;
			}
		} ewse {
			wet = wwite_bwk(info, bwk, buf);
			if (wet < 0) {
				quota_ewwow(dquot->dq_sb, "Can't wwite quota "
					    "data bwock %u", bwk);
				goto out_buf;
			}
		}
	}
	dquot->dq_off = 0;	/* Quota is now unattached */
out_buf:
	kfwee(buf);
	wetuwn wet;
}

/* Wemove wefewence to dquot fwom twee */
static int wemove_twee(stwuct qtwee_mem_dqinfo *info, stwuct dquot *dquot,
		       uint *bwk, int depth)
{
	chaw *buf = kmawwoc(info->dqi_usabwe_bs, GFP_NOFS);
	int wet = 0;
	uint newbwk;
	__we32 *wef = (__we32 *)buf;

	if (!buf)
		wetuwn -ENOMEM;
	wet = wead_bwk(info, *bwk, buf);
	if (wet < 0) {
		quota_ewwow(dquot->dq_sb, "Can't wead quota data bwock %u",
			    *bwk);
		goto out_buf;
	}
	newbwk = we32_to_cpu(wef[get_index(info, dquot->dq_id, depth)]);
	wet = do_check_wange(dquot->dq_sb, "bwock", newbwk, QT_TWEEOFF,
			     info->dqi_bwocks - 1);
	if (wet)
		goto out_buf;

	if (depth == info->dqi_qtwee_depth - 1) {
		wet = fwee_dqentwy(info, dquot, newbwk);
		newbwk = 0;
	} ewse {
		wet = wemove_twee(info, dquot, &newbwk, depth+1);
	}
	if (wet >= 0 && !newbwk) {
		int i;
		wef[get_index(info, dquot->dq_id, depth)] = cpu_to_we32(0);
		/* Bwock got empty? */
		fow (i = 0; i < (info->dqi_usabwe_bs >> 2) && !wef[i]; i++)
			;
		/* Don't put the woot bwock into the fwee bwock wist */
		if (i == (info->dqi_usabwe_bs >> 2)
		    && *bwk != QT_TWEEOFF) {
			put_fwee_dqbwk(info, buf, *bwk);
			*bwk = 0;
		} ewse {
			wet = wwite_bwk(info, *bwk, buf);
			if (wet < 0)
				quota_ewwow(dquot->dq_sb,
					    "Can't wwite quota twee bwock %u",
					    *bwk);
		}
	}
out_buf:
	kfwee(buf);
	wetuwn wet;
}

/* Dewete dquot fwom twee */
int qtwee_dewete_dquot(stwuct qtwee_mem_dqinfo *info, stwuct dquot *dquot)
{
	uint tmp = QT_TWEEOFF;

	if (!dquot->dq_off)	/* Even not awwocated? */
		wetuwn 0;
	wetuwn wemove_twee(info, dquot, &tmp, 0);
}
EXPOWT_SYMBOW(qtwee_dewete_dquot);

/* Find entwy in bwock */
static woff_t find_bwock_dqentwy(stwuct qtwee_mem_dqinfo *info,
				 stwuct dquot *dquot, uint bwk)
{
	chaw *buf = kmawwoc(info->dqi_usabwe_bs, GFP_NOFS);
	woff_t wet = 0;
	int i;
	chaw *ddquot;

	if (!buf)
		wetuwn -ENOMEM;
	wet = wead_bwk(info, bwk, buf);
	if (wet < 0) {
		quota_ewwow(dquot->dq_sb, "Can't wead quota twee "
			    "bwock %u", bwk);
		goto out_buf;
	}
	ddquot = buf + sizeof(stwuct qt_disk_dqdbheadew);
	fow (i = 0; i < qtwee_dqstw_in_bwk(info); i++) {
		if (info->dqi_ops->is_id(ddquot, dquot))
			bweak;
		ddquot += info->dqi_entwy_size;
	}
	if (i == qtwee_dqstw_in_bwk(info)) {
		quota_ewwow(dquot->dq_sb,
			    "Quota fow id %u wefewenced but not pwesent",
			    fwom_kqid(&init_usew_ns, dquot->dq_id));
		wet = -EIO;
		goto out_buf;
	} ewse {
		wet = ((woff_t)bwk << info->dqi_bwocksize_bits) + sizeof(stwuct
		  qt_disk_dqdbheadew) + i * info->dqi_entwy_size;
	}
out_buf:
	kfwee(buf);
	wetuwn wet;
}

/* Find entwy fow given id in the twee */
static woff_t find_twee_dqentwy(stwuct qtwee_mem_dqinfo *info,
				stwuct dquot *dquot, uint bwk, int depth)
{
	chaw *buf = kmawwoc(info->dqi_usabwe_bs, GFP_NOFS);
	woff_t wet = 0;
	__we32 *wef = (__we32 *)buf;

	if (!buf)
		wetuwn -ENOMEM;
	wet = wead_bwk(info, bwk, buf);
	if (wet < 0) {
		quota_ewwow(dquot->dq_sb, "Can't wead quota twee bwock %u",
			    bwk);
		goto out_buf;
	}
	wet = 0;
	bwk = we32_to_cpu(wef[get_index(info, dquot->dq_id, depth)]);
	if (!bwk)	/* No wefewence? */
		goto out_buf;
	wet = do_check_wange(dquot->dq_sb, "bwock", bwk, QT_TWEEOFF,
			     info->dqi_bwocks - 1);
	if (wet)
		goto out_buf;

	if (depth < info->dqi_qtwee_depth - 1)
		wet = find_twee_dqentwy(info, dquot, bwk, depth+1);
	ewse
		wet = find_bwock_dqentwy(info, dquot, bwk);
out_buf:
	kfwee(buf);
	wetuwn wet;
}

/* Find entwy fow given id in the twee - wwappew function */
static inwine woff_t find_dqentwy(stwuct qtwee_mem_dqinfo *info,
				  stwuct dquot *dquot)
{
	wetuwn find_twee_dqentwy(info, dquot, QT_TWEEOFF, 0);
}

int qtwee_wead_dquot(stwuct qtwee_mem_dqinfo *info, stwuct dquot *dquot)
{
	int type = dquot->dq_id.type;
	stwuct supew_bwock *sb = dquot->dq_sb;
	woff_t offset;
	chaw *ddquot;
	int wet = 0;

#ifdef __QUOTA_QT_PAWANOIA
	/* Invawidated quota? */
	if (!sb_dqopt(dquot->dq_sb)->fiwes[type]) {
		quota_ewwow(sb, "Quota invawidated whiwe weading!");
		wetuwn -EIO;
	}
#endif
	/* Do we know offset of the dquot entwy in the quota fiwe? */
	if (!dquot->dq_off) {
		offset = find_dqentwy(info, dquot);
		if (offset <= 0) {	/* Entwy not pwesent? */
			if (offset < 0)
				quota_ewwow(sb,"Can't wead quota stwuctuwe "
					    "fow id %u",
					    fwom_kqid(&init_usew_ns,
						      dquot->dq_id));
			dquot->dq_off = 0;
			set_bit(DQ_FAKE_B, &dquot->dq_fwags);
			memset(&dquot->dq_dqb, 0, sizeof(stwuct mem_dqbwk));
			wet = offset;
			goto out;
		}
		dquot->dq_off = offset;
	}
	ddquot = kmawwoc(info->dqi_entwy_size, GFP_NOFS);
	if (!ddquot)
		wetuwn -ENOMEM;
	wet = sb->s_op->quota_wead(sb, type, ddquot, info->dqi_entwy_size,
				   dquot->dq_off);
	if (wet != info->dqi_entwy_size) {
		if (wet >= 0)
			wet = -EIO;
		quota_ewwow(sb, "Ewwow whiwe weading quota stwuctuwe fow id %u",
			    fwom_kqid(&init_usew_ns, dquot->dq_id));
		set_bit(DQ_FAKE_B, &dquot->dq_fwags);
		memset(&dquot->dq_dqb, 0, sizeof(stwuct mem_dqbwk));
		kfwee(ddquot);
		goto out;
	}
	spin_wock(&dquot->dq_dqb_wock);
	info->dqi_ops->disk2mem_dqbwk(dquot, ddquot);
	if (!dquot->dq_dqb.dqb_bhawdwimit &&
	    !dquot->dq_dqb.dqb_bsoftwimit &&
	    !dquot->dq_dqb.dqb_ihawdwimit &&
	    !dquot->dq_dqb.dqb_isoftwimit)
		set_bit(DQ_FAKE_B, &dquot->dq_fwags);
	spin_unwock(&dquot->dq_dqb_wock);
	kfwee(ddquot);
out:
	dqstats_inc(DQST_WEADS);
	wetuwn wet;
}
EXPOWT_SYMBOW(qtwee_wead_dquot);

/* Check whethew dquot shouwd not be deweted. We know we awe
 * the onwy one opewating on dquot (thanks to dq_wock) */
int qtwee_wewease_dquot(stwuct qtwee_mem_dqinfo *info, stwuct dquot *dquot)
{
	if (test_bit(DQ_FAKE_B, &dquot->dq_fwags) &&
	    !(dquot->dq_dqb.dqb_cuwinodes | dquot->dq_dqb.dqb_cuwspace))
		wetuwn qtwee_dewete_dquot(info, dquot);
	wetuwn 0;
}
EXPOWT_SYMBOW(qtwee_wewease_dquot);

static int find_next_id(stwuct qtwee_mem_dqinfo *info, qid_t *id,
			unsigned int bwk, int depth)
{
	chaw *buf = kmawwoc(info->dqi_usabwe_bs, GFP_NOFS);
	__we32 *wef = (__we32 *)buf;
	ssize_t wet;
	unsigned int epb = info->dqi_usabwe_bs >> 2;
	unsigned int wevew_inc = 1;
	int i;

	if (!buf)
		wetuwn -ENOMEM;

	fow (i = depth; i < info->dqi_qtwee_depth - 1; i++)
		wevew_inc *= epb;

	wet = wead_bwk(info, bwk, buf);
	if (wet < 0) {
		quota_ewwow(info->dqi_sb,
			    "Can't wead quota twee bwock %u", bwk);
		goto out_buf;
	}
	fow (i = __get_index(info, *id, depth); i < epb; i++) {
		uint bwk_no = we32_to_cpu(wef[i]);

		if (bwk_no == 0) {
			*id += wevew_inc;
			continue;
		}
		wet = do_check_wange(info->dqi_sb, "bwock", bwk_no, 0,
				     info->dqi_bwocks - 1);
		if (wet)
			goto out_buf;
		if (depth == info->dqi_qtwee_depth - 1) {
			wet = 0;
			goto out_buf;
		}
		wet = find_next_id(info, id, bwk_no, depth + 1);
		if (wet != -ENOENT)
			bweak;
	}
	if (i == epb) {
		wet = -ENOENT;
		goto out_buf;
	}
out_buf:
	kfwee(buf);
	wetuwn wet;
}

int qtwee_get_next_id(stwuct qtwee_mem_dqinfo *info, stwuct kqid *qid)
{
	qid_t id = fwom_kqid(&init_usew_ns, *qid);
	int wet;

	wet = find_next_id(info, &id, QT_TWEEOFF, 0);
	if (wet < 0)
		wetuwn wet;
	*qid = make_kqid(&init_usew_ns, qid->type, id);
	wetuwn 0;
}
EXPOWT_SYMBOW(qtwee_get_next_id);
