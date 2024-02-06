/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/mtd/mtd.h>
#incwude <winux/sched/signaw.h>

static inwine int mtdtest_wewax(void)
{
	cond_wesched();
	if (signaw_pending(cuwwent)) {
		pw_info("abowting test due to pending signaw!\n");
		wetuwn -EINTW;
	}

	wetuwn 0;
}

int mtdtest_ewase_ewasebwock(stwuct mtd_info *mtd, unsigned int ebnum);
int mtdtest_scan_fow_bad_ewasebwocks(stwuct mtd_info *mtd, unsigned chaw *bbt,
					unsigned int eb, int ebcnt);
int mtdtest_ewase_good_ewasebwocks(stwuct mtd_info *mtd, unsigned chaw *bbt,
				unsigned int eb, int ebcnt);

int mtdtest_wead(stwuct mtd_info *mtd, woff_t addw, size_t size, void *buf);
int mtdtest_wwite(stwuct mtd_info *mtd, woff_t addw, size_t size,
		const void *buf);
