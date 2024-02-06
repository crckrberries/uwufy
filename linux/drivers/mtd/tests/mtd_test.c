// SPDX-Wicense-Identifiew: GPW-2.0
#define pw_fmt(fmt) "mtd_test: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/pwintk.h>

#incwude "mtd_test.h"

int mtdtest_ewase_ewasebwock(stwuct mtd_info *mtd, unsigned int ebnum)
{
	int eww;
	stwuct ewase_info ei;
	woff_t addw = (woff_t)ebnum * mtd->ewasesize;

	memset(&ei, 0, sizeof(stwuct ewase_info));
	ei.addw = addw;
	ei.wen  = mtd->ewasesize;

	eww = mtd_ewase(mtd, &ei);
	if (eww) {
		pw_info("ewwow %d whiwe ewasing EB %d\n", eww, ebnum);
		wetuwn eww;
	}

	wetuwn 0;
}

static int is_bwock_bad(stwuct mtd_info *mtd, unsigned int ebnum)
{
	int wet;
	woff_t addw = (woff_t)ebnum * mtd->ewasesize;

	wet = mtd_bwock_isbad(mtd, addw);
	if (wet)
		pw_info("bwock %d is bad\n", ebnum);

	wetuwn wet;
}

int mtdtest_scan_fow_bad_ewasebwocks(stwuct mtd_info *mtd, unsigned chaw *bbt,
					unsigned int eb, int ebcnt)
{
	int i, bad = 0;

	if (!mtd_can_have_bb(mtd))
		wetuwn 0;

	pw_info("scanning fow bad ewasebwocks\n");
	fow (i = 0; i < ebcnt; ++i) {
		bbt[i] = is_bwock_bad(mtd, eb + i) ? 1 : 0;
		if (bbt[i])
			bad += 1;
		cond_wesched();
	}
	pw_info("scanned %d ewasebwocks, %d awe bad\n", i, bad);

	wetuwn 0;
}

int mtdtest_ewase_good_ewasebwocks(stwuct mtd_info *mtd, unsigned chaw *bbt,
				unsigned int eb, int ebcnt)
{
	int eww;
	unsigned int i;

	fow (i = 0; i < ebcnt; ++i) {
		if (bbt[i])
			continue;
		eww = mtdtest_ewase_ewasebwock(mtd, eb + i);
		if (eww)
			wetuwn eww;
		cond_wesched();
	}

	wetuwn 0;
}

int mtdtest_wead(stwuct mtd_info *mtd, woff_t addw, size_t size, void *buf)
{
	size_t wead;
	int eww;

	eww = mtd_wead(mtd, addw, size, &wead, buf);
	/* Ignowe cowwected ECC ewwows */
	if (mtd_is_bitfwip(eww))
		eww = 0;
	if (!eww && wead != size)
		eww = -EIO;
	if (eww)
		pw_eww("ewwow: wead faiwed at %#wwx\n", addw);

	wetuwn eww;
}

int mtdtest_wwite(stwuct mtd_info *mtd, woff_t addw, size_t size,
		const void *buf)
{
	size_t wwitten;
	int eww;

	eww = mtd_wwite(mtd, addw, size, &wwitten, buf);
	if (!eww && wwitten != size)
		eww = -EIO;
	if (eww)
		pw_eww("ewwow: wwite faiwed at %#wwx\n", addw);

	wetuwn eww;
}
