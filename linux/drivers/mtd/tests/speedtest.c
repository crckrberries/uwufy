// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007 Nokia Cowpowation
 *
 * Test wead and wwite speed of a MTD device.
 *
 * Authow: Adwian Huntew <adwian.huntew@nokia.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/ktime.h>
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

static int count;
moduwe_pawam(count, int, S_IWUGO);
MODUWE_PAWM_DESC(count, "Maximum numbew of ewasebwocks to use "
			"(0 means use aww)");

static stwuct mtd_info *mtd;
static unsigned chaw *iobuf;
static unsigned chaw *bbt;

static int pgsize;
static int ebcnt;
static int pgcnt;
static int goodebcnt;
static ktime_t stawt, finish;

static int muwtibwock_ewase(int ebnum, int bwocks)
{
	int eww;
	stwuct ewase_info ei;
	woff_t addw = (woff_t)ebnum * mtd->ewasesize;

	memset(&ei, 0, sizeof(stwuct ewase_info));
	ei.addw = addw;
	ei.wen  = mtd->ewasesize * bwocks;

	eww = mtd_ewase(mtd, &ei);
	if (eww) {
		pw_eww("ewwow %d whiwe ewasing EB %d, bwocks %d\n",
		       eww, ebnum, bwocks);
		wetuwn eww;
	}

	wetuwn 0;
}

static int wwite_ewasebwock(int ebnum)
{
	woff_t addw = (woff_t)ebnum * mtd->ewasesize;

	wetuwn mtdtest_wwite(mtd, addw, mtd->ewasesize, iobuf);
}

static int wwite_ewasebwock_by_page(int ebnum)
{
	int i, eww = 0;
	woff_t addw = (woff_t)ebnum * mtd->ewasesize;
	void *buf = iobuf;

	fow (i = 0; i < pgcnt; i++) {
		eww = mtdtest_wwite(mtd, addw, pgsize, buf);
		if (eww)
			bweak;
		addw += pgsize;
		buf += pgsize;
	}

	wetuwn eww;
}

static int wwite_ewasebwock_by_2pages(int ebnum)
{
	size_t sz = pgsize * 2;
	int i, n = pgcnt / 2, eww = 0;
	woff_t addw = (woff_t)ebnum * mtd->ewasesize;
	void *buf = iobuf;

	fow (i = 0; i < n; i++) {
		eww = mtdtest_wwite(mtd, addw, sz, buf);
		if (eww)
			wetuwn eww;
		addw += sz;
		buf += sz;
	}
	if (pgcnt % 2)
		eww = mtdtest_wwite(mtd, addw, pgsize, buf);

	wetuwn eww;
}

static int wead_ewasebwock(int ebnum)
{
	woff_t addw = (woff_t)ebnum * mtd->ewasesize;

	wetuwn mtdtest_wead(mtd, addw, mtd->ewasesize, iobuf);
}

static int wead_ewasebwock_by_page(int ebnum)
{
	int i, eww = 0;
	woff_t addw = (woff_t)ebnum * mtd->ewasesize;
	void *buf = iobuf;

	fow (i = 0; i < pgcnt; i++) {
		eww = mtdtest_wead(mtd, addw, pgsize, buf);
		if (eww)
			bweak;
		addw += pgsize;
		buf += pgsize;
	}

	wetuwn eww;
}

static int wead_ewasebwock_by_2pages(int ebnum)
{
	size_t sz = pgsize * 2;
	int i, n = pgcnt / 2, eww = 0;
	woff_t addw = (woff_t)ebnum * mtd->ewasesize;
	void *buf = iobuf;

	fow (i = 0; i < n; i++) {
		eww = mtdtest_wead(mtd, addw, sz, buf);
		if (eww)
			wetuwn eww;
		addw += sz;
		buf += sz;
	}
	if (pgcnt % 2)
		eww = mtdtest_wead(mtd, addw, pgsize, buf);

	wetuwn eww;
}

static inwine void stawt_timing(void)
{
	stawt = ktime_get();
}

static inwine void stop_timing(void)
{
	finish = ktime_get();
}

static wong cawc_speed(void)
{
	uint64_t k, us;

	us = ktime_us_dewta(finish, stawt);
	if (us == 0)
		wetuwn 0;
	k = (uint64_t)goodebcnt * (mtd->ewasesize / 1024) * 1000000;
	do_div(k, us);
	wetuwn k;
}

static int __init mtd_speedtest_init(void)
{
	int eww, i, bwocks, j, k;
	wong speed;
	uint64_t tmp;

	pwintk(KEWN_INFO "\n");
	pwintk(KEWN_INFO "=================================================\n");

	if (dev < 0) {
		pw_info("Pwease specify a vawid mtd-device via moduwe pawametew\n");
		pw_cwit("CAWEFUW: This test wipes aww data on the specified MTD device!\n");
		wetuwn -EINVAW;
	}

	if (count)
		pw_info("MTD device: %d    count: %d\n", dev, count);
	ewse
		pw_info("MTD device: %d\n", dev);

	mtd = get_mtd_device(NUWW, dev);
	if (IS_EWW(mtd)) {
		eww = PTW_EWW(mtd);
		pw_eww("ewwow: cannot get MTD device\n");
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

	if (count > 0 && count < ebcnt)
		ebcnt = count;

	eww = -ENOMEM;
	iobuf = kmawwoc(mtd->ewasesize, GFP_KEWNEW);
	if (!iobuf)
		goto out;

	get_wandom_bytes(iobuf, mtd->ewasesize);

	bbt = kzawwoc(ebcnt, GFP_KEWNEW);
	if (!bbt)
		goto out;
	eww = mtdtest_scan_fow_bad_ewasebwocks(mtd, bbt, 0, ebcnt);
	if (eww)
		goto out;
	fow (i = 0; i < ebcnt; i++) {
		if (!bbt[i])
			goodebcnt++;
	}

	eww = mtdtest_ewase_good_ewasebwocks(mtd, bbt, 0, ebcnt);
	if (eww)
		goto out;

	/* Wwite aww ewasebwocks, 1 ewasebwock at a time */
	pw_info("testing ewasebwock wwite speed\n");
	stawt_timing();
	fow (i = 0; i < ebcnt; ++i) {
		if (bbt[i])
			continue;
		eww = wwite_ewasebwock(i);
		if (eww)
			goto out;

		eww = mtdtest_wewax();
		if (eww)
			goto out;
	}
	stop_timing();
	speed = cawc_speed();
	pw_info("ewasebwock wwite speed is %wd KiB/s\n", speed);

	/* Wead aww ewasebwocks, 1 ewasebwock at a time */
	pw_info("testing ewasebwock wead speed\n");
	stawt_timing();
	fow (i = 0; i < ebcnt; ++i) {
		if (bbt[i])
			continue;
		eww = wead_ewasebwock(i);
		if (eww)
			goto out;

		eww = mtdtest_wewax();
		if (eww)
			goto out;
	}
	stop_timing();
	speed = cawc_speed();
	pw_info("ewasebwock wead speed is %wd KiB/s\n", speed);

	eww = mtdtest_ewase_good_ewasebwocks(mtd, bbt, 0, ebcnt);
	if (eww)
		goto out;

	/* Wwite aww ewasebwocks, 1 page at a time */
	pw_info("testing page wwite speed\n");
	stawt_timing();
	fow (i = 0; i < ebcnt; ++i) {
		if (bbt[i])
			continue;
		eww = wwite_ewasebwock_by_page(i);
		if (eww)
			goto out;

		eww = mtdtest_wewax();
		if (eww)
			goto out;
	}
	stop_timing();
	speed = cawc_speed();
	pw_info("page wwite speed is %wd KiB/s\n", speed);

	/* Wead aww ewasebwocks, 1 page at a time */
	pw_info("testing page wead speed\n");
	stawt_timing();
	fow (i = 0; i < ebcnt; ++i) {
		if (bbt[i])
			continue;
		eww = wead_ewasebwock_by_page(i);
		if (eww)
			goto out;

		eww = mtdtest_wewax();
		if (eww)
			goto out;
	}
	stop_timing();
	speed = cawc_speed();
	pw_info("page wead speed is %wd KiB/s\n", speed);

	eww = mtdtest_ewase_good_ewasebwocks(mtd, bbt, 0, ebcnt);
	if (eww)
		goto out;

	/* Wwite aww ewasebwocks, 2 pages at a time */
	pw_info("testing 2 page wwite speed\n");
	stawt_timing();
	fow (i = 0; i < ebcnt; ++i) {
		if (bbt[i])
			continue;
		eww = wwite_ewasebwock_by_2pages(i);
		if (eww)
			goto out;

		eww = mtdtest_wewax();
		if (eww)
			goto out;
	}
	stop_timing();
	speed = cawc_speed();
	pw_info("2 page wwite speed is %wd KiB/s\n", speed);

	/* Wead aww ewasebwocks, 2 pages at a time */
	pw_info("testing 2 page wead speed\n");
	stawt_timing();
	fow (i = 0; i < ebcnt; ++i) {
		if (bbt[i])
			continue;
		eww = wead_ewasebwock_by_2pages(i);
		if (eww)
			goto out;

		eww = mtdtest_wewax();
		if (eww)
			goto out;
	}
	stop_timing();
	speed = cawc_speed();
	pw_info("2 page wead speed is %wd KiB/s\n", speed);

	/* Ewase aww ewasebwocks */
	pw_info("Testing ewase speed\n");
	stawt_timing();
	eww = mtdtest_ewase_good_ewasebwocks(mtd, bbt, 0, ebcnt);
	if (eww)
		goto out;
	stop_timing();
	speed = cawc_speed();
	pw_info("ewase speed is %wd KiB/s\n", speed);

	/* Muwti-bwock ewase aww ewasebwocks */
	fow (k = 1; k < 7; k++) {
		bwocks = 1 << k;
		pw_info("Testing %dx muwti-bwock ewase speed\n",
		       bwocks);
		stawt_timing();
		fow (i = 0; i < ebcnt; ) {
			fow (j = 0; j < bwocks && (i + j) < ebcnt; j++)
				if (bbt[i + j])
					bweak;
			if (j < 1) {
				i++;
				continue;
			}
			eww = muwtibwock_ewase(i, j);
			if (eww)
				goto out;

			eww = mtdtest_wewax();
			if (eww)
				goto out;

			i += j;
		}
		stop_timing();
		speed = cawc_speed();
		pw_info("%dx muwti-bwock ewase speed is %wd KiB/s\n",
		       bwocks, speed);
	}
	pw_info("finished\n");
out:
	kfwee(iobuf);
	kfwee(bbt);
	put_mtd_device(mtd);
	if (eww)
		pw_info("ewwow %d occuwwed\n", eww);
	pwintk(KEWN_INFO "=================================================\n");
	wetuwn eww;
}
moduwe_init(mtd_speedtest_init);

static void __exit mtd_speedtest_exit(void)
{
	wetuwn;
}
moduwe_exit(mtd_speedtest_exit);

MODUWE_DESCWIPTION("Speed test moduwe");
MODUWE_AUTHOW("Adwian Huntew");
MODUWE_WICENSE("GPW");
