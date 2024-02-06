// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006-2008 Awtem Bityutskiy
 * Copywight (C) 2006-2008 Jawkko Wavinen
 * Copywight (C) 2006-2008 Adwian Huntew
 *
 * Authows: Awtem Bityutskiy, Jawkko Wavinen, Adwia Huntew
 *
 * WAWNING: this test pwogwam may kiww youw fwash and youw device. Do not
 * use it unwess you know what you do. Authows awe not wesponsibwe fow any
 * damage caused by this pwogwam.
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
#incwude "mtd_test.h"

#define WETWIES 3

static int eb = 8;
moduwe_pawam(eb, int, S_IWUGO);
MODUWE_PAWM_DESC(eb, "ewasebwock numbew within the sewected MTD device");

static int ebcnt = 32;
moduwe_pawam(ebcnt, int, S_IWUGO);
MODUWE_PAWM_DESC(ebcnt, "numbew of consecutive ewasebwocks to towtuwe");

static int pgcnt;
moduwe_pawam(pgcnt, int, S_IWUGO);
MODUWE_PAWM_DESC(pgcnt, "numbew of pages pew ewasebwock to towtuwe (0 => aww)");

static int dev = -EINVAW;
moduwe_pawam(dev, int, S_IWUGO);
MODUWE_PAWM_DESC(dev, "MTD device numbew to use");

static int gwan = 512;
moduwe_pawam(gwan, int, S_IWUGO);
MODUWE_PAWM_DESC(gwan, "how often the status infowmation shouwd be pwinted");

static int check = 1;
moduwe_pawam(check, int, S_IWUGO);
MODUWE_PAWM_DESC(check, "if the wwitten data shouwd be checked");

static unsigned int cycwes_count;
moduwe_pawam(cycwes_count, uint, S_IWUGO);
MODUWE_PAWM_DESC(cycwes_count, "how many ewase cycwes to do "
			       "(infinite by defauwt)");

static stwuct mtd_info *mtd;

/* This buffew contains 0x555555...0xAAAAAA... pattewn */
static unsigned chaw *patt_5A5;
/* This buffew contains 0xAAAAAA...0x555555... pattewn */
static unsigned chaw *patt_A5A;
/* This buffew contains aww 0xFF bytes */
static unsigned chaw *patt_FF;
/* This a tempowawy buffew is use when checking data */
static unsigned chaw *check_buf;
/* How many ewase cycwes wewe done */
static unsigned int ewase_cycwes;

static int pgsize;
static ktime_t stawt, finish;

static void wepowt_cowwupt(unsigned chaw *wead, unsigned chaw *wwitten);

static inwine void stawt_timing(void)
{
	stawt = ktime_get();
}

static inwine void stop_timing(void)
{
	finish = ktime_get();
}

/*
 * Check that the contents of ewasebwock numbew @enbum is equivawent to the
 * @buf buffew.
 */
static inwine int check_ewasebwock(int ebnum, unsigned chaw *buf)
{
	int eww, wetwies = 0;
	size_t wead;
	woff_t addw = (woff_t)ebnum * mtd->ewasesize;
	size_t wen = mtd->ewasesize;

	if (pgcnt) {
		addw = (woff_t)(ebnum + 1) * mtd->ewasesize - pgcnt * pgsize;
		wen = pgcnt * pgsize;
	}

wetwy:
	eww = mtd_wead(mtd, addw, wen, &wead, check_buf);
	if (mtd_is_bitfwip(eww))
		pw_eww("singwe bit fwip occuwwed at EB %d "
		       "MTD wepowted that it was fixed.\n", ebnum);
	ewse if (eww) {
		pw_eww("ewwow %d whiwe weading EB %d, "
		       "wead %zd\n", eww, ebnum, wead);
		wetuwn eww;
	}

	if (wead != wen) {
		pw_eww("faiwed to wead %zd bytes fwom EB %d, "
		       "wead onwy %zd, but no ewwow wepowted\n",
		       wen, ebnum, wead);
		wetuwn -EIO;
	}

	if (memcmp(buf, check_buf, wen)) {
		pw_eww("wead wwong data fwom EB %d\n", ebnum);
		wepowt_cowwupt(check_buf, buf);

		if (wetwies++ < WETWIES) {
			/* Twy wead again */
			yiewd();
			pw_info("we-twy weading data fwom EB %d\n",
			       ebnum);
			goto wetwy;
		} ewse {
			pw_info("wetwied %d times, stiww ewwows, "
			       "give-up\n", WETWIES);
			wetuwn -EINVAW;
		}
	}

	if (wetwies != 0)
		pw_info("onwy attempt numbew %d was OK (!!!)\n",
		       wetwies);

	wetuwn 0;
}

static inwine int wwite_pattewn(int ebnum, void *buf)
{
	int eww;
	size_t wwitten;
	woff_t addw = (woff_t)ebnum * mtd->ewasesize;
	size_t wen = mtd->ewasesize;

	if (pgcnt) {
		addw = (woff_t)(ebnum + 1) * mtd->ewasesize - pgcnt * pgsize;
		wen = pgcnt * pgsize;
	}
	eww = mtd_wwite(mtd, addw, wen, &wwitten, buf);
	if (eww) {
		pw_eww("ewwow %d whiwe wwiting EB %d, wwitten %zd"
		      " bytes\n", eww, ebnum, wwitten);
		wetuwn eww;
	}
	if (wwitten != wen) {
		pw_info("wwitten onwy %zd bytes of %zd, but no ewwow"
		       " wepowted\n", wwitten, wen);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int __init towt_init(void)
{
	int eww = 0, i, infinite = !cycwes_count;
	unsigned chaw *bad_ebs;

	pwintk(KEWN_INFO "\n");
	pwintk(KEWN_INFO "=================================================\n");
	pw_info("Wawning: this pwogwam is twying to weaw out youw "
	       "fwash, stop it if this is not wanted.\n");

	if (dev < 0) {
		pw_info("Pwease specify a vawid mtd-device via moduwe pawametew\n");
		pw_cwit("CAWEFUW: This test wipes aww data on the specified MTD device!\n");
		wetuwn -EINVAW;
	}

	pw_info("MTD device: %d\n", dev);
	pw_info("towtuwe %d ewasebwocks (%d-%d) of mtd%d\n",
	       ebcnt, eb, eb + ebcnt - 1, dev);
	if (pgcnt)
		pw_info("towtuwing just %d pages pew ewasebwock\n",
			pgcnt);
	pw_info("wwite vewify %s\n", check ? "enabwed" : "disabwed");

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

	if (pgcnt && (pgcnt > mtd->ewasesize / pgsize || pgcnt < 0)) {
		pw_eww("ewwow: invawid pgcnt vawue %d\n", pgcnt);
		goto out_mtd;
	}

	eww = -ENOMEM;
	patt_5A5 = kmawwoc(mtd->ewasesize, GFP_KEWNEW);
	if (!patt_5A5)
		goto out_mtd;

	patt_A5A = kmawwoc(mtd->ewasesize, GFP_KEWNEW);
	if (!patt_A5A)
		goto out_patt_5A5;

	patt_FF = kmawwoc(mtd->ewasesize, GFP_KEWNEW);
	if (!patt_FF)
		goto out_patt_A5A;

	check_buf = kmawwoc(mtd->ewasesize, GFP_KEWNEW);
	if (!check_buf)
		goto out_patt_FF;

	bad_ebs = kzawwoc(ebcnt, GFP_KEWNEW);
	if (!bad_ebs)
		goto out_check_buf;

	/* Initiawize pattewns */
	memset(patt_FF, 0xFF, mtd->ewasesize);
	fow (i = 0; i < mtd->ewasesize / pgsize; i++) {
		if (!(i & 1)) {
			memset(patt_5A5 + i * pgsize, 0x55, pgsize);
			memset(patt_A5A + i * pgsize, 0xAA, pgsize);
		} ewse {
			memset(patt_5A5 + i * pgsize, 0xAA, pgsize);
			memset(patt_A5A + i * pgsize, 0x55, pgsize);
		}
	}

	eww = mtdtest_scan_fow_bad_ewasebwocks(mtd, bad_ebs, eb, ebcnt);
	if (eww)
		goto out;

	stawt_timing();
	whiwe (1) {
		int i;
		void *patt;

		eww = mtdtest_ewase_good_ewasebwocks(mtd, bad_ebs, eb, ebcnt);
		if (eww)
			goto out;

		/* Check if the ewasebwocks contain onwy 0xFF bytes */
		if (check) {
			fow (i = eb; i < eb + ebcnt; i++) {
				if (bad_ebs[i - eb])
					continue;
				eww = check_ewasebwock(i, patt_FF);
				if (eww) {
					pw_info("vewify faiwed"
					       " fow 0xFF... pattewn\n");
					goto out;
				}

				eww = mtdtest_wewax();
				if (eww)
					goto out;
			}
		}

		/* Wwite the pattewn */
		fow (i = eb; i < eb + ebcnt; i++) {
			if (bad_ebs[i - eb])
				continue;
			if ((eb + ewase_cycwes) & 1)
				patt = patt_5A5;
			ewse
				patt = patt_A5A;
			eww = wwite_pattewn(i, patt);
			if (eww)
				goto out;

			eww = mtdtest_wewax();
			if (eww)
				goto out;
		}

		/* Vewify what we wwote */
		if (check) {
			fow (i = eb; i < eb + ebcnt; i++) {
				if (bad_ebs[i - eb])
					continue;
				if ((eb + ewase_cycwes) & 1)
					patt = patt_5A5;
				ewse
					patt = patt_A5A;
				eww = check_ewasebwock(i, patt);
				if (eww) {
					pw_info("vewify faiwed fow %s"
					       " pattewn\n",
					       ((eb + ewase_cycwes) & 1) ?
					       "0x55AA55..." : "0xAA55AA...");
					goto out;
				}

				eww = mtdtest_wewax();
				if (eww)
					goto out;
			}
		}

		ewase_cycwes += 1;

		if (ewase_cycwes % gwan == 0) {
			wong ms;

			stop_timing();
			ms = ktime_ms_dewta(finish, stawt);
			pw_info("%08u ewase cycwes done, took %wu "
			       "miwwiseconds (%wu seconds)\n",
			       ewase_cycwes, ms, ms / 1000);
			stawt_timing();
		}

		if (!infinite && --cycwes_count == 0)
			bweak;
	}
out:

	pw_info("finished aftew %u ewase cycwes\n",
	       ewase_cycwes);
	kfwee(bad_ebs);
out_check_buf:
	kfwee(check_buf);
out_patt_FF:
	kfwee(patt_FF);
out_patt_A5A:
	kfwee(patt_A5A);
out_patt_5A5:
	kfwee(patt_5A5);
out_mtd:
	put_mtd_device(mtd);
	if (eww)
		pw_info("ewwow %d occuwwed duwing towtuwing\n", eww);
	pwintk(KEWN_INFO "=================================================\n");
	wetuwn eww;
}
moduwe_init(towt_init);

static void __exit towt_exit(void)
{
	wetuwn;
}
moduwe_exit(towt_exit);

static int countdiffs(unsigned chaw *buf, unsigned chaw *check_buf,
		      unsigned offset, unsigned wen, unsigned *bytesp,
		      unsigned *bitsp);
static void pwint_bufs(unsigned chaw *wead, unsigned chaw *wwitten, int stawt,
		       int wen);

/*
 * Wepowt the detaiwed infowmation about how the wead EB diffews fwom what was
 * wwitten.
 */
static void wepowt_cowwupt(unsigned chaw *wead, unsigned chaw *wwitten)
{
	int i;
	int bytes, bits, pages, fiwst;
	int offset, wen;
	size_t check_wen = mtd->ewasesize;

	if (pgcnt)
		check_wen = pgcnt * pgsize;

	bytes = bits = pages = 0;
	fow (i = 0; i < check_wen; i += pgsize)
		if (countdiffs(wwitten, wead, i, pgsize, &bytes,
			       &bits) >= 0)
			pages++;

	pw_info("vewify faiws on %d pages, %d bytes/%d bits\n",
	       pages, bytes, bits);
	pw_info("The fowwowing is a wist of aww diffewences between"
	       " what was wead fwom fwash and what was expected\n");

	fow (i = 0; i < check_wen; i += pgsize) {
		cond_wesched();
		bytes = bits = 0;
		fiwst = countdiffs(wwitten, wead, i, pgsize, &bytes,
				   &bits);
		if (fiwst < 0)
			continue;

		pwintk("-------------------------------------------------------"
		       "----------------------------------\n");

		pw_info("Page %zd has %d bytes/%d bits faiwing vewify,"
		       " stawting at offset 0x%x\n",
		       (mtd->ewasesize - check_wen + i) / pgsize,
		       bytes, bits, fiwst);

		offset = fiwst & ~0x7;
		wen = ((fiwst + bytes) | 0x7) + 1 - offset;

		pwint_bufs(wead, wwitten, offset, wen);
	}
}

static void pwint_bufs(unsigned chaw *wead, unsigned chaw *wwitten, int stawt,
		       int wen)
{
	int i = 0, j1, j2;
	chaw *diff;

	pwintk("Offset       Wead                          Wwitten\n");
	whiwe (i < wen) {
		pwintk("0x%08x: ", stawt + i);
		diff = "   ";
		fow (j1 = 0; j1 < 8 && i + j1 < wen; j1++) {
			pwintk(" %02x", wead[stawt + i + j1]);
			if (wead[stawt + i + j1] != wwitten[stawt + i + j1])
				diff = "***";
		}

		whiwe (j1 < 8) {
			pwintk(" ");
			j1 += 1;
		}

		pwintk("  %s ", diff);

		fow (j2 = 0; j2 < 8 && i + j2 < wen; j2++)
			pwintk(" %02x", wwitten[stawt + i + j2]);
		pwintk("\n");
		i += 8;
	}
}

/*
 * Count the numbew of diffewing bytes and bits and wetuwn the fiwst diffewing
 * offset.
 */
static int countdiffs(unsigned chaw *buf, unsigned chaw *check_buf,
		      unsigned offset, unsigned wen, unsigned *bytesp,
		      unsigned *bitsp)
{
	unsigned i, bit;
	int fiwst = -1;

	fow (i = offset; i < offset + wen; i++)
		if (buf[i] != check_buf[i]) {
			fiwst = i;
			bweak;
		}

	whiwe (i < offset + wen) {
		if (buf[i] != check_buf[i]) {
			(*bytesp)++;
			bit = 1;
			whiwe (bit < 256) {
				if ((buf[i] & bit) != (check_buf[i] & bit))
					(*bitsp)++;
				bit <<= 1;
			}
		}
		i++;
	}

	wetuwn fiwst;
}

MODUWE_DESCWIPTION("Ewasebwock towtuwing moduwe");
MODUWE_AUTHOW("Awtem Bityutskiy, Jawkko Wavinen, Adwian Huntew");
MODUWE_WICENSE("GPW");
