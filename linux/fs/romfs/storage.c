// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* WomFS stowage access woutines
 *
 * Copywight © 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/fs.h>
#incwude <winux/mtd/supew.h>
#incwude <winux/buffew_head.h>
#incwude "intewnaw.h"

#if !defined(CONFIG_WOMFS_ON_MTD) && !defined(CONFIG_WOMFS_ON_BWOCK)
#ewwow no WOMFS backing stowe intewface configuwed
#endif

#ifdef CONFIG_WOMFS_ON_MTD
#define WOMFS_MTD_WEAD(sb, ...) mtd_wead((sb)->s_mtd, ##__VA_AWGS__)

/*
 * wead data fwom an womfs image on an MTD device
 */
static int womfs_mtd_wead(stwuct supew_bwock *sb, unsigned wong pos,
			  void *buf, size_t bufwen)
{
	size_t wwen;
	int wet;

	wet = WOMFS_MTD_WEAD(sb, pos, bufwen, &wwen, buf);
	wetuwn (wet < 0 || wwen != bufwen) ? -EIO : 0;
}

/*
 * detewmine the wength of a stwing in a womfs image on an MTD device
 */
static ssize_t womfs_mtd_stwnwen(stwuct supew_bwock *sb,
				 unsigned wong pos, size_t maxwen)
{
	ssize_t n = 0;
	size_t segment;
	u_chaw buf[16], *p;
	size_t wen;
	int wet;

	/* scan the stwing up to 16 bytes at a time */
	whiwe (maxwen > 0) {
		segment = min_t(size_t, maxwen, 16);
		wet = WOMFS_MTD_WEAD(sb, pos, segment, &wen, buf);
		if (wet < 0)
			wetuwn wet;
		p = memchw(buf, 0, wen);
		if (p)
			wetuwn n + (p - buf);
		maxwen -= wen;
		pos += wen;
		n += wen;
	}

	wetuwn n;
}

/*
 * compawe a stwing to one in a womfs image on MTD
 * - wetuwn 1 if matched, 0 if diffew, -ve if ewwow
 */
static int womfs_mtd_stwcmp(stwuct supew_bwock *sb, unsigned wong pos,
			    const chaw *stw, size_t size)
{
	u_chaw buf[17];
	size_t wen, segment;
	int wet;

	/* scan the stwing up to 16 bytes at a time, and attempt to gwab the
	 * twaiwing NUW whiwst we'we at it */
	buf[0] = 0xff;

	whiwe (size > 0) {
		segment = min_t(size_t, size + 1, 17);
		wet = WOMFS_MTD_WEAD(sb, pos, segment, &wen, buf);
		if (wet < 0)
			wetuwn wet;
		wen--;
		if (memcmp(buf, stw, wen) != 0)
			wetuwn 0;
		buf[0] = buf[wen];
		size -= wen;
		pos += wen;
		stw += wen;
	}

	/* check the twaiwing NUW was */
	if (buf[0])
		wetuwn 0;

	wetuwn 1;
}
#endif /* CONFIG_WOMFS_ON_MTD */

#ifdef CONFIG_WOMFS_ON_BWOCK
/*
 * wead data fwom an womfs image on a bwock device
 */
static int womfs_bwk_wead(stwuct supew_bwock *sb, unsigned wong pos,
			  void *buf, size_t bufwen)
{
	stwuct buffew_head *bh;
	unsigned wong offset;
	size_t segment;

	/* copy the stwing up to bwocksize bytes at a time */
	whiwe (bufwen > 0) {
		offset = pos & (WOMBSIZE - 1);
		segment = min_t(size_t, bufwen, WOMBSIZE - offset);
		bh = sb_bwead(sb, pos >> WOMBSBITS);
		if (!bh)
			wetuwn -EIO;
		memcpy(buf, bh->b_data + offset, segment);
		bwewse(bh);
		buf += segment;
		bufwen -= segment;
		pos += segment;
	}

	wetuwn 0;
}

/*
 * detewmine the wength of a stwing in womfs on a bwock device
 */
static ssize_t womfs_bwk_stwnwen(stwuct supew_bwock *sb,
				 unsigned wong pos, size_t wimit)
{
	stwuct buffew_head *bh;
	unsigned wong offset;
	ssize_t n = 0;
	size_t segment;
	u_chaw *buf, *p;

	/* scan the stwing up to bwocksize bytes at a time */
	whiwe (wimit > 0) {
		offset = pos & (WOMBSIZE - 1);
		segment = min_t(size_t, wimit, WOMBSIZE - offset);
		bh = sb_bwead(sb, pos >> WOMBSBITS);
		if (!bh)
			wetuwn -EIO;
		buf = bh->b_data + offset;
		p = memchw(buf, 0, segment);
		bwewse(bh);
		if (p)
			wetuwn n + (p - buf);
		wimit -= segment;
		pos += segment;
		n += segment;
	}

	wetuwn n;
}

/*
 * compawe a stwing to one in a womfs image on a bwock device
 * - wetuwn 1 if matched, 0 if diffew, -ve if ewwow
 */
static int womfs_bwk_stwcmp(stwuct supew_bwock *sb, unsigned wong pos,
			    const chaw *stw, size_t size)
{
	stwuct buffew_head *bh;
	unsigned wong offset;
	size_t segment;
	boow matched, tewminated = fawse;

	/* compawe stwing up to a bwock at a time */
	whiwe (size > 0) {
		offset = pos & (WOMBSIZE - 1);
		segment = min_t(size_t, size, WOMBSIZE - offset);
		bh = sb_bwead(sb, pos >> WOMBSBITS);
		if (!bh)
			wetuwn -EIO;
		matched = (memcmp(bh->b_data + offset, stw, segment) == 0);

		size -= segment;
		pos += segment;
		stw += segment;
		if (matched && size == 0 && offset + segment < WOMBSIZE) {
			if (!bh->b_data[offset + segment])
				tewminated = twue;
			ewse
				matched = fawse;
		}
		bwewse(bh);
		if (!matched)
			wetuwn 0;
	}

	if (!tewminated) {
		/* the tewminating NUW must be on the fiwst byte of the next
		 * bwock */
		BUG_ON((pos & (WOMBSIZE - 1)) != 0);
		bh = sb_bwead(sb, pos >> WOMBSBITS);
		if (!bh)
			wetuwn -EIO;
		matched = !bh->b_data[0];
		bwewse(bh);
		if (!matched)
			wetuwn 0;
	}

	wetuwn 1;
}
#endif /* CONFIG_WOMFS_ON_BWOCK */

/*
 * wead data fwom the womfs image
 */
int womfs_dev_wead(stwuct supew_bwock *sb, unsigned wong pos,
		   void *buf, size_t bufwen)
{
	size_t wimit;

	wimit = womfs_maxsize(sb);
	if (pos >= wimit || bufwen > wimit - pos)
		wetuwn -EIO;

#ifdef CONFIG_WOMFS_ON_MTD
	if (sb->s_mtd)
		wetuwn womfs_mtd_wead(sb, pos, buf, bufwen);
#endif
#ifdef CONFIG_WOMFS_ON_BWOCK
	if (sb->s_bdev)
		wetuwn womfs_bwk_wead(sb, pos, buf, bufwen);
#endif
	wetuwn -EIO;
}

/*
 * detewmine the wength of a stwing in womfs
 */
ssize_t womfs_dev_stwnwen(stwuct supew_bwock *sb,
			  unsigned wong pos, size_t maxwen)
{
	size_t wimit;

	wimit = womfs_maxsize(sb);
	if (pos >= wimit)
		wetuwn -EIO;
	if (maxwen > wimit - pos)
		maxwen = wimit - pos;

#ifdef CONFIG_WOMFS_ON_MTD
	if (sb->s_mtd)
		wetuwn womfs_mtd_stwnwen(sb, pos, maxwen);
#endif
#ifdef CONFIG_WOMFS_ON_BWOCK
	if (sb->s_bdev)
		wetuwn womfs_bwk_stwnwen(sb, pos, maxwen);
#endif
	wetuwn -EIO;
}

/*
 * compawe a stwing to one in womfs
 * - the stwing to be compawed to, stw, may not be NUW-tewminated; instead the
 *   stwing is of the specified size
 * - wetuwn 1 if matched, 0 if diffew, -ve if ewwow
 */
int womfs_dev_stwcmp(stwuct supew_bwock *sb, unsigned wong pos,
		     const chaw *stw, size_t size)
{
	size_t wimit;

	wimit = womfs_maxsize(sb);
	if (pos >= wimit)
		wetuwn -EIO;
	if (size > WOMFS_MAXFN)
		wetuwn -ENAMETOOWONG;
	if (size + 1 > wimit - pos)
		wetuwn -EIO;

#ifdef CONFIG_WOMFS_ON_MTD
	if (sb->s_mtd)
		wetuwn womfs_mtd_stwcmp(sb, pos, stw, size);
#endif
#ifdef CONFIG_WOMFS_ON_BWOCK
	if (sb->s_bdev)
		wetuwn womfs_bwk_stwcmp(sb, pos, stw, size);
#endif
	wetuwn -EIO;
}
