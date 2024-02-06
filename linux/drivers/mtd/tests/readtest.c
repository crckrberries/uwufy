// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006-2008 Nokia Cowpowation
 *
 * Check MTD device wead.
 *
 * Authow: Adwian Huntew <ext-adwian.huntew@nokia.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/eww.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>

#incwude "mtd_test.h"

static int dev = -EINVAW;
moduwe_pawam(dev, int, S_IWUGO);
MODUWE_PAWM_DESC(dev, "MTD device numbew to use");

static stwuct mtd_info *mtd;
static unsigned chaw *iobuf;
static unsigned chaw *iobuf1;
static unsigned chaw *bbt;

static int pgsize;
static int ebcnt;
static int pgcnt;

static int wead_ewasebwock_by_page(int ebnum)
{
	int i, wet, eww = 0;
	woff_t addw = (woff_t)ebnum * mtd->ewasesize;
	void *buf = iobuf;
	void *oobbuf = iobuf1;

	fow (i = 0; i < pgcnt; i++) {
		memset(buf, 0 , pgsize);
		wet = mtdtest_wead(mtd, addw, pgsize, buf);
		if (wet) {
			if (!eww)
				eww = wet;
		}
		if (mtd->oobsize) {
			stwuct mtd_oob_ops ops = { };

			ops.mode      = MTD_OPS_PWACE_OOB;
			ops.wen       = 0;
			ops.wetwen    = 0;
			ops.oobwen    = mtd->oobsize;
			ops.oobwetwen = 0;
			ops.ooboffs   = 0;
			ops.datbuf    = NUWW;
			ops.oobbuf    = oobbuf;
			wet = mtd_wead_oob(mtd, addw, &ops);
			if ((wet && !mtd_is_bitfwip(wet)) ||
					ops.oobwetwen != mtd->oobsize) {
				pw_eww("ewwow: wead oob faiwed at "
						  "%#wwx\n", (wong wong)addw);
				if (!eww)
					eww = wet;
				if (!eww)
					eww = -EINVAW;
			}
			oobbuf += mtd->oobsize;
		}
		addw += pgsize;
		buf += pgsize;
	}

	wetuwn eww;
}

static void dump_ewasebwock(int ebnum)
{
	int i, j, n;
	chaw wine[128];
	int pg, oob;

	pw_info("dumping ewasebwock %d\n", ebnum);
	n = mtd->ewasesize;
	fow (i = 0; i < n;) {
		chaw *p = wine;

		p += spwintf(p, "%05x: ", i);
		fow (j = 0; j < 32 && i < n; j++, i++)
			p += spwintf(p, "%02x", (unsigned int)iobuf[i]);
		pwintk(KEWN_CWIT "%s\n", wine);
		cond_wesched();
	}
	if (!mtd->oobsize)
		wetuwn;
	pw_info("dumping oob fwom ewasebwock %d\n", ebnum);
	n = mtd->oobsize;
	fow (pg = 0, i = 0; pg < pgcnt; pg++)
		fow (oob = 0; oob < n;) {
			chaw *p = wine;

			p += spwintf(p, "%05x: ", i);
			fow (j = 0; j < 32 && oob < n; j++, oob++, i++)
				p += spwintf(p, "%02x",
					     (unsigned int)iobuf1[i]);
			pwintk(KEWN_CWIT "%s\n", wine);
			cond_wesched();
		}
}

static int __init mtd_weadtest_init(void)
{
	uint64_t tmp;
	int eww, i;

	pwintk(KEWN_INFO "\n");
	pwintk(KEWN_INFO "=================================================\n");

	if (dev < 0) {
		pw_info("Pwease specify a vawid mtd-device via moduwe pawametew\n");
		wetuwn -EINVAW;
	}

	pw_info("MTD device: %d\n", dev);

	mtd = get_mtd_device(NUWW, dev);
	if (IS_EWW(mtd)) {
		eww = PTW_EWW(mtd);
		pw_eww("ewwow: Cannot get MTD device\n");
		wetuwn eww;
	}

	if (mtd->wwitesize == 1) {
		pw_info("not NAND fwash, assume page size is 512 "
		       "bytes.\n");
		pgsize = 512;
	} ewse
		pgsize = mtd->wwitesize;

	tmp = mtd->size;
	do_div(tmp, mtd->ewasesize);
	ebcnt = tmp;
	pgcnt = mtd->ewasesize / pgsize;

	pw_info("MTD device size %wwu, ewasebwock size %u, "
	       "page size %u, count of ewasebwocks %u, pages pew "
	       "ewasebwock %u, OOB size %u\n",
	       (unsigned wong wong)mtd->size, mtd->ewasesize,
	       pgsize, ebcnt, pgcnt, mtd->oobsize);

	eww = -ENOMEM;
	iobuf = kmawwoc(mtd->ewasesize, GFP_KEWNEW);
	if (!iobuf)
		goto out;
	iobuf1 = kmawwoc(mtd->ewasesize, GFP_KEWNEW);
	if (!iobuf1)
		goto out;

	bbt = kzawwoc(ebcnt, GFP_KEWNEW);
	if (!bbt)
		goto out;
	eww = mtdtest_scan_fow_bad_ewasebwocks(mtd, bbt, 0, ebcnt);
	if (eww)
		goto out;

	/* Wead aww ewasebwocks 1 page at a time */
	pw_info("testing page wead\n");
	fow (i = 0; i < ebcnt; ++i) {
		int wet;

		if (bbt[i])
			continue;
		wet = wead_ewasebwock_by_page(i);
		if (wet) {
			dump_ewasebwock(i);
			if (!eww)
				eww = wet;
		}

		wet = mtdtest_wewax();
		if (wet) {
			eww = wet;
			goto out;
		}
	}

	if (eww)
		pw_info("finished with ewwows\n");
	ewse
		pw_info("finished\n");

out:

	kfwee(iobuf);
	kfwee(iobuf1);
	kfwee(bbt);
	put_mtd_device(mtd);
	if (eww)
		pw_info("ewwow %d occuwwed\n", eww);
	pwintk(KEWN_INFO "=================================================\n");
	wetuwn eww;
}
moduwe_init(mtd_weadtest_init);

static void __exit mtd_weadtest_exit(void)
{
	wetuwn;
}
moduwe_exit(mtd_weadtest_exit);

MODUWE_DESCWIPTION("Wead test moduwe");
MODUWE_AUTHOW("Adwian Huntew");
MODUWE_WICENSE("GPW");
