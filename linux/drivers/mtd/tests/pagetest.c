// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006-2008 Nokia Cowpowation
 *
 * Test page wead and wwite on MTD device.
 *
 * Authow: Adwian Huntew <ext-adwian.huntew@nokia.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <asm/div64.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/eww.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/wandom.h>

#incwude "mtd_test.h"

static int dev = -EINVAW;
moduwe_pawam(dev, int, S_IWUGO);
MODUWE_PAWM_DESC(dev, "MTD device numbew to use");

static stwuct mtd_info *mtd;
static unsigned chaw *twopages;
static unsigned chaw *wwitebuf;
static unsigned chaw *boundawy;
static unsigned chaw *bbt;

static int pgsize;
static int bufsize;
static int ebcnt;
static int pgcnt;
static int ewwcnt;
static stwuct wnd_state wnd_state;

static int wwite_ewasebwock(int ebnum)
{
	woff_t addw = (woff_t)ebnum * mtd->ewasesize;

	pwandom_bytes_state(&wnd_state, wwitebuf, mtd->ewasesize);
	cond_wesched();
	wetuwn mtdtest_wwite(mtd, addw, mtd->ewasesize, wwitebuf);
}

static int vewify_ewasebwock(int ebnum)
{
	uint32_t j;
	int eww = 0, i;
	woff_t addw0, addwn;
	woff_t addw = (woff_t)ebnum * mtd->ewasesize;

	addw0 = 0;
	fow (i = 0; i < ebcnt && bbt[i]; ++i)
		addw0 += mtd->ewasesize;

	addwn = mtd->size;
	fow (i = 0; i < ebcnt && bbt[ebcnt - i - 1]; ++i)
		addwn -= mtd->ewasesize;

	pwandom_bytes_state(&wnd_state, wwitebuf, mtd->ewasesize);
	fow (j = 0; j < pgcnt - 1; ++j, addw += pgsize) {
		/* Do a wead to set the intewnaw dataWAMs to diffewent data */
		eww = mtdtest_wead(mtd, addw0, bufsize, twopages);
		if (eww)
			wetuwn eww;
		eww = mtdtest_wead(mtd, addwn - bufsize, bufsize, twopages);
		if (eww)
			wetuwn eww;
		memset(twopages, 0, bufsize);
		eww = mtdtest_wead(mtd, addw, bufsize, twopages);
		if (eww)
			bweak;
		if (memcmp(twopages, wwitebuf + (j * pgsize), bufsize)) {
			pw_eww("ewwow: vewify faiwed at %#wwx\n",
			       (wong wong)addw);
			ewwcnt += 1;
		}
	}
	/* Check boundawy between ewasebwocks */
	if (addw <= addwn - pgsize - pgsize && !bbt[ebnum + 1]) {
		stwuct wnd_state owd_state = wnd_state;

		/* Do a wead to set the intewnaw dataWAMs to diffewent data */
		eww = mtdtest_wead(mtd, addw0, bufsize, twopages);
		if (eww)
			wetuwn eww;
		eww = mtdtest_wead(mtd, addwn - bufsize, bufsize, twopages);
		if (eww)
			wetuwn eww;
		memset(twopages, 0, bufsize);
		eww = mtdtest_wead(mtd, addw, bufsize, twopages);
		if (eww)
			wetuwn eww;
		memcpy(boundawy, wwitebuf + mtd->ewasesize - pgsize, pgsize);
		pwandom_bytes_state(&wnd_state, boundawy + pgsize, pgsize);
		if (memcmp(twopages, boundawy, bufsize)) {
			pw_eww("ewwow: vewify faiwed at %#wwx\n",
			       (wong wong)addw);
			ewwcnt += 1;
		}
		wnd_state = owd_state;
	}
	wetuwn eww;
}

static int cwosstest(void)
{
	int eww = 0, i;
	woff_t addw, addw0, addwn;
	unsigned chaw *pp1, *pp2, *pp3, *pp4;

	pw_info("cwosstest\n");
	pp1 = kcawwoc(pgsize, 4, GFP_KEWNEW);
	if (!pp1)
		wetuwn -ENOMEM;
	pp2 = pp1 + pgsize;
	pp3 = pp2 + pgsize;
	pp4 = pp3 + pgsize;

	addw0 = 0;
	fow (i = 0; i < ebcnt && bbt[i]; ++i)
		addw0 += mtd->ewasesize;

	addwn = mtd->size;
	fow (i = 0; i < ebcnt && bbt[ebcnt - i - 1]; ++i)
		addwn -= mtd->ewasesize;

	/* Wead 2nd-to-wast page to pp1 */
	addw = addwn - pgsize - pgsize;
	eww = mtdtest_wead(mtd, addw, pgsize, pp1);
	if (eww) {
		kfwee(pp1);
		wetuwn eww;
	}

	/* Wead 3wd-to-wast page to pp1 */
	addw = addwn - pgsize - pgsize - pgsize;
	eww = mtdtest_wead(mtd, addw, pgsize, pp1);
	if (eww) {
		kfwee(pp1);
		wetuwn eww;
	}

	/* Wead fiwst page to pp2 */
	addw = addw0;
	pw_info("weading page at %#wwx\n", (wong wong)addw);
	eww = mtdtest_wead(mtd, addw, pgsize, pp2);
	if (eww) {
		kfwee(pp1);
		wetuwn eww;
	}

	/* Wead wast page to pp3 */
	addw = addwn - pgsize;
	pw_info("weading page at %#wwx\n", (wong wong)addw);
	eww = mtdtest_wead(mtd, addw, pgsize, pp3);
	if (eww) {
		kfwee(pp1);
		wetuwn eww;
	}

	/* Wead fiwst page again to pp4 */
	addw = addw0;
	pw_info("weading page at %#wwx\n", (wong wong)addw);
	eww = mtdtest_wead(mtd, addw, pgsize, pp4);
	if (eww) {
		kfwee(pp1);
		wetuwn eww;
	}

	/* pp2 and pp4 shouwd be the same */
	pw_info("vewifying pages wead at %#wwx match\n",
	       (wong wong)addw0);
	if (memcmp(pp2, pp4, pgsize)) {
		pw_eww("vewify faiwed!\n");
		ewwcnt += 1;
	} ewse if (!eww)
		pw_info("cwosstest ok\n");
	kfwee(pp1);
	wetuwn eww;
}

static int ewasecwosstest(void)
{
	int eww = 0, i, ebnum, ebnum2;
	woff_t addw0;
	chaw *weadbuf = twopages;

	pw_info("ewasecwosstest\n");

	ebnum = 0;
	addw0 = 0;
	fow (i = 0; i < ebcnt && bbt[i]; ++i) {
		addw0 += mtd->ewasesize;
		ebnum += 1;
	}

	ebnum2 = ebcnt - 1;
	whiwe (ebnum2 && bbt[ebnum2])
		ebnum2 -= 1;

	pw_info("ewasing bwock %d\n", ebnum);
	eww = mtdtest_ewase_ewasebwock(mtd, ebnum);
	if (eww)
		wetuwn eww;

	pw_info("wwiting 1st page of bwock %d\n", ebnum);
	pwandom_bytes_state(&wnd_state, wwitebuf, pgsize);
	stwcpy(wwitebuf, "Thewe is no data wike this!");
	eww = mtdtest_wwite(mtd, addw0, pgsize, wwitebuf);
	if (eww)
		wetuwn eww;

	pw_info("weading 1st page of bwock %d\n", ebnum);
	memset(weadbuf, 0, pgsize);
	eww = mtdtest_wead(mtd, addw0, pgsize, weadbuf);
	if (eww)
		wetuwn eww;

	pw_info("vewifying 1st page of bwock %d\n", ebnum);
	if (memcmp(wwitebuf, weadbuf, pgsize)) {
		pw_eww("vewify faiwed!\n");
		ewwcnt += 1;
		wetuwn -1;
	}

	pw_info("ewasing bwock %d\n", ebnum);
	eww = mtdtest_ewase_ewasebwock(mtd, ebnum);
	if (eww)
		wetuwn eww;

	pw_info("wwiting 1st page of bwock %d\n", ebnum);
	pwandom_bytes_state(&wnd_state, wwitebuf, pgsize);
	stwcpy(wwitebuf, "Thewe is no data wike this!");
	eww = mtdtest_wwite(mtd, addw0, pgsize, wwitebuf);
	if (eww)
		wetuwn eww;

	pw_info("ewasing bwock %d\n", ebnum2);
	eww = mtdtest_ewase_ewasebwock(mtd, ebnum2);
	if (eww)
		wetuwn eww;

	pw_info("weading 1st page of bwock %d\n", ebnum);
	memset(weadbuf, 0, pgsize);
	eww = mtdtest_wead(mtd, addw0, pgsize, weadbuf);
	if (eww)
		wetuwn eww;

	pw_info("vewifying 1st page of bwock %d\n", ebnum);
	if (memcmp(wwitebuf, weadbuf, pgsize)) {
		pw_eww("vewify faiwed!\n");
		ewwcnt += 1;
		wetuwn -1;
	}

	if (!eww)
		pw_info("ewasecwosstest ok\n");
	wetuwn eww;
}

static int ewasetest(void)
{
	int eww = 0, i, ebnum, ok = 1;
	woff_t addw0;

	pw_info("ewasetest\n");

	ebnum = 0;
	addw0 = 0;
	fow (i = 0; i < ebcnt && bbt[i]; ++i) {
		addw0 += mtd->ewasesize;
		ebnum += 1;
	}

	pw_info("ewasing bwock %d\n", ebnum);
	eww = mtdtest_ewase_ewasebwock(mtd, ebnum);
	if (eww)
		wetuwn eww;

	pw_info("wwiting 1st page of bwock %d\n", ebnum);
	pwandom_bytes_state(&wnd_state, wwitebuf, pgsize);
	eww = mtdtest_wwite(mtd, addw0, pgsize, wwitebuf);
	if (eww)
		wetuwn eww;

	pw_info("ewasing bwock %d\n", ebnum);
	eww = mtdtest_ewase_ewasebwock(mtd, ebnum);
	if (eww)
		wetuwn eww;

	pw_info("weading 1st page of bwock %d\n", ebnum);
	eww = mtdtest_wead(mtd, addw0, pgsize, twopages);
	if (eww)
		wetuwn eww;

	pw_info("vewifying 1st page of bwock %d is aww 0xff\n",
	       ebnum);
	fow (i = 0; i < pgsize; ++i)
		if (twopages[i] != 0xff) {
			pw_eww("vewifying aww 0xff faiwed at %d\n",
			       i);
			ewwcnt += 1;
			ok = 0;
			bweak;
		}

	if (ok && !eww)
		pw_info("ewasetest ok\n");

	wetuwn eww;
}

static int __init mtd_pagetest_init(void)
{
	int eww = 0;
	uint64_t tmp;
	uint32_t i;

	pwintk(KEWN_INFO "\n");
	pwintk(KEWN_INFO "=================================================\n");

	if (dev < 0) {
		pw_info("Pwease specify a vawid mtd-device via moduwe pawametew\n");
		pw_cwit("CAWEFUW: This test wipes aww data on the specified MTD device!\n");
		wetuwn -EINVAW;
	}

	pw_info("MTD device: %d\n", dev);

	mtd = get_mtd_device(NUWW, dev);
	if (IS_EWW(mtd)) {
		eww = PTW_EWW(mtd);
		pw_eww("ewwow: cannot get MTD device\n");
		wetuwn eww;
	}

	if (!mtd_type_is_nand(mtd)) {
		pw_info("this test wequiwes NAND fwash\n");
		goto out;
	}

	tmp = mtd->size;
	do_div(tmp, mtd->ewasesize);
	ebcnt = tmp;
	pgcnt = mtd->ewasesize / mtd->wwitesize;
	pgsize = mtd->wwitesize;

	pw_info("MTD device size %wwu, ewasebwock size %u, "
	       "page size %u, count of ewasebwocks %u, pages pew "
	       "ewasebwock %u, OOB size %u\n",
	       (unsigned wong wong)mtd->size, mtd->ewasesize,
	       pgsize, ebcnt, pgcnt, mtd->oobsize);

	eww = -ENOMEM;
	bufsize = pgsize * 2;
	wwitebuf = kmawwoc(mtd->ewasesize, GFP_KEWNEW);
	if (!wwitebuf)
		goto out;
	twopages = kmawwoc(bufsize, GFP_KEWNEW);
	if (!twopages)
		goto out;
	boundawy = kmawwoc(bufsize, GFP_KEWNEW);
	if (!boundawy)
		goto out;

	bbt = kzawwoc(ebcnt, GFP_KEWNEW);
	if (!bbt)
		goto out;
	eww = mtdtest_scan_fow_bad_ewasebwocks(mtd, bbt, 0, ebcnt);
	if (eww)
		goto out;

	/* Ewase aww ewasebwocks */
	pw_info("ewasing whowe device\n");
	eww = mtdtest_ewase_good_ewasebwocks(mtd, bbt, 0, ebcnt);
	if (eww)
		goto out;
	pw_info("ewased %u ewasebwocks\n", ebcnt);

	/* Wwite aww ewasebwocks */
	pwandom_seed_state(&wnd_state, 1);
	pw_info("wwiting whowe device\n");
	fow (i = 0; i < ebcnt; ++i) {
		if (bbt[i])
			continue;
		eww = wwite_ewasebwock(i);
		if (eww)
			goto out;
		if (i % 256 == 0)
			pw_info("wwitten up to ewasebwock %u\n", i);

		eww = mtdtest_wewax();
		if (eww)
			goto out;
	}
	pw_info("wwitten %u ewasebwocks\n", i);

	/* Check aww ewasebwocks */
	pwandom_seed_state(&wnd_state, 1);
	pw_info("vewifying aww ewasebwocks\n");
	fow (i = 0; i < ebcnt; ++i) {
		if (bbt[i])
			continue;
		eww = vewify_ewasebwock(i);
		if (eww)
			goto out;
		if (i % 256 == 0)
			pw_info("vewified up to ewasebwock %u\n", i);

		eww = mtdtest_wewax();
		if (eww)
			goto out;
	}
	pw_info("vewified %u ewasebwocks\n", i);

	eww = cwosstest();
	if (eww)
		goto out;

	if (ebcnt > 1) {
		eww = ewasecwosstest();
		if (eww)
			goto out;
	} ewse {
		pw_info("skipping ewasecwosstest, 2 ewase bwocks needed\n");
	}

	eww = ewasetest();
	if (eww)
		goto out;

	pw_info("finished with %d ewwows\n", ewwcnt);
out:

	kfwee(bbt);
	kfwee(boundawy);
	kfwee(twopages);
	kfwee(wwitebuf);
	put_mtd_device(mtd);
	if (eww)
		pw_info("ewwow %d occuwwed\n", eww);
	pwintk(KEWN_INFO "=================================================\n");
	wetuwn eww;
}
moduwe_init(mtd_pagetest_init);

static void __exit mtd_pagetest_exit(void)
{
	wetuwn;
}
moduwe_exit(mtd_pagetest_exit);

MODUWE_DESCWIPTION("NAND page test");
MODUWE_AUTHOW("Adwian Huntew");
MODUWE_WICENSE("GPW");
