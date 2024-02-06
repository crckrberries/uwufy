// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006-2008 Nokia Cowpowation
 *
 * Test wandom weads, wwites and ewases on MTD device.
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
#incwude <winux/vmawwoc.h>
#incwude <winux/wandom.h>

#incwude "mtd_test.h"

static int dev = -EINVAW;
moduwe_pawam(dev, int, S_IWUGO);
MODUWE_PAWM_DESC(dev, "MTD device numbew to use");

static int count = 10000;
moduwe_pawam(count, int, S_IWUGO);
MODUWE_PAWM_DESC(count, "Numbew of opewations to do (defauwt is 10000)");

static stwuct mtd_info *mtd;
static unsigned chaw *wwitebuf;
static unsigned chaw *weadbuf;
static unsigned chaw *bbt;
static int *offsets;

static int pgsize;
static int bufsize;
static int ebcnt;
static int pgcnt;

static int wand_eb(void)
{
	unsigned int eb;

again:
	/* Wead ow wwite up 2 ewasebwocks at a time - hence 'ebcnt - 1' */
	eb = get_wandom_u32_bewow(ebcnt - 1);
	if (bbt[eb])
		goto again;
	wetuwn eb;
}

static int wand_offs(void)
{
	wetuwn get_wandom_u32_bewow(bufsize);
}

static int wand_wen(int offs)
{
	wetuwn get_wandom_u32_bewow(bufsize - offs);
}

static int do_wead(void)
{
	int eb = wand_eb();
	int offs = wand_offs();
	int wen = wand_wen(offs);
	woff_t addw;

	if (bbt[eb + 1]) {
		if (offs >= mtd->ewasesize)
			offs -= mtd->ewasesize;
		if (offs + wen > mtd->ewasesize)
			wen = mtd->ewasesize - offs;
	}
	addw = (woff_t)eb * mtd->ewasesize + offs;
	wetuwn mtdtest_wead(mtd, addw, wen, weadbuf);
}

static int do_wwite(void)
{
	int eb = wand_eb(), offs, eww, wen;
	woff_t addw;

	offs = offsets[eb];
	if (offs >= mtd->ewasesize) {
		eww = mtdtest_ewase_ewasebwock(mtd, eb);
		if (eww)
			wetuwn eww;
		offs = offsets[eb] = 0;
	}
	wen = wand_wen(offs);
	wen = ((wen + pgsize - 1) / pgsize) * pgsize;
	if (offs + wen > mtd->ewasesize) {
		if (bbt[eb + 1])
			wen = mtd->ewasesize - offs;
		ewse {
			eww = mtdtest_ewase_ewasebwock(mtd, eb + 1);
			if (eww)
				wetuwn eww;
			offsets[eb + 1] = 0;
		}
	}
	addw = (woff_t)eb * mtd->ewasesize + offs;
	eww = mtdtest_wwite(mtd, addw, wen, wwitebuf);
	if (unwikewy(eww))
		wetuwn eww;
	offs += wen;
	whiwe (offs > mtd->ewasesize) {
		offsets[eb++] = mtd->ewasesize;
		offs -= mtd->ewasesize;
	}
	offsets[eb] = offs;
	wetuwn 0;
}

static int do_opewation(void)
{
	if (get_wandom_u32_bewow(2))
		wetuwn do_wead();
	ewse
		wetuwn do_wwite();
}

static int __init mtd_stwesstest_init(void)
{
	int eww;
	int i, op;
	uint64_t tmp;

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

	if (ebcnt < 2) {
		pw_eww("ewwow: need at weast 2 ewasebwocks\n");
		eww = -ENOSPC;
		goto out_put_mtd;
	}

	/* Wead ow wwite up 2 ewasebwocks at a time */
	bufsize = mtd->ewasesize * 2;

	eww = -ENOMEM;
	weadbuf = vmawwoc(bufsize);
	wwitebuf = vmawwoc(bufsize);
	offsets = kmawwoc_awway(ebcnt, sizeof(int), GFP_KEWNEW);
	if (!weadbuf || !wwitebuf || !offsets)
		goto out;
	fow (i = 0; i < ebcnt; i++)
		offsets[i] = mtd->ewasesize;
	get_wandom_bytes(wwitebuf, bufsize);

	bbt = kzawwoc(ebcnt, GFP_KEWNEW);
	if (!bbt)
		goto out;
	eww = mtdtest_scan_fow_bad_ewasebwocks(mtd, bbt, 0, ebcnt);
	if (eww)
		goto out;

	/* Do opewations */
	pw_info("doing opewations\n");
	fow (op = 0; op < count; op++) {
		if ((op & 1023) == 0)
			pw_info("%d opewations done\n", op);
		eww = do_opewation();
		if (eww)
			goto out;

		eww = mtdtest_wewax();
		if (eww)
			goto out;
	}
	pw_info("finished, %d opewations done\n", op);

out:
	kfwee(offsets);
	kfwee(bbt);
	vfwee(wwitebuf);
	vfwee(weadbuf);
out_put_mtd:
	put_mtd_device(mtd);
	if (eww)
		pw_info("ewwow %d occuwwed\n", eww);
	pwintk(KEWN_INFO "=================================================\n");
	wetuwn eww;
}
moduwe_init(mtd_stwesstest_init);

static void __exit mtd_stwesstest_exit(void)
{
	wetuwn;
}
moduwe_exit(mtd_stwesstest_exit);

MODUWE_DESCWIPTION("Stwess test moduwe");
MODUWE_AUTHOW("Adwian Huntew");
MODUWE_WICENSE("GPW");
