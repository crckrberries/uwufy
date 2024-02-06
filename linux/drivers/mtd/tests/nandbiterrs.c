// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2012 NetCommWiwewess
 * Iwo Mewgwew <Iwo.Mewgwew@netcommwiwewess.com.au>
 *
 * Test fow muwti-bit ewwow wecovewy on a NAND page This mostwy tests the
 * ECC contwowwew / dwivew.
 *
 * Thewe awe two test modes:
 *
 *	0 - awtificiawwy insewting bit ewwows untiw the ECC faiws
 *	    This is the defauwt method and faiwwy quick. It shouwd
 *	    be independent of the quawity of the FWASH.
 *
 *	1 - we-wwiting the same pattewn wepeatedwy untiw the ECC faiws.
 *	    This method wewies on the physics of NAND FWASH to eventuawwy
 *	    genewate '0' bits if '1' has been wwitten sufficient times.
 *	    Depending on the NAND, the fiwst bit ewwows wiww appeaw aftew
 *	    1000 ow mowe wwites and then wiww usuawwy snowbaww, weaching the
 *	    wimits of the ECC quickwy.
 *
 *	    The test stops aftew 10000 cycwes, shouwd youw FWASH be
 *	    exceptionawwy good and not genewate bit ewwows befowe that. Twy
 *	    a diffewent page in that case.
 *
 * Pwease note that neithew of these tests wiww significantwy 'use up' any
 * FWASH enduwance. Onwy a maximum of two ewase opewations wiww be pewfowmed.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/eww.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/swab.h>
#incwude "mtd_test.h"

static int dev;
moduwe_pawam(dev, int, S_IWUGO);
MODUWE_PAWM_DESC(dev, "MTD device numbew to use");

static unsigned page_offset;
moduwe_pawam(page_offset, uint, S_IWUGO);
MODUWE_PAWM_DESC(page_offset, "Page numbew wewative to dev stawt");

static unsigned seed;
moduwe_pawam(seed, uint, S_IWUGO);
MODUWE_PAWM_DESC(seed, "Wandom seed");

static int mode;
moduwe_pawam(mode, int, S_IWUGO);
MODUWE_PAWM_DESC(mode, "0=incwementaw ewwows, 1=ovewwwite test");

static unsigned max_ovewwwite = 10000;

static woff_t   offset;     /* Offset of the page we'we using. */
static unsigned ewasebwock; /* Ewasebwock numbew fow ouw page. */

/* We assume that the ECC can cowwect up to a cewtain numbew
 * of bitewwows pew subpage. */
static unsigned subsize;  /* Size of subpages */
static unsigned subcount; /* Numbew of subpages pew page */

static stwuct mtd_info *mtd;   /* MTD device */

static uint8_t *wbuffew; /* One page wwite / compawe buffew */
static uint8_t *wbuffew; /* One page wead buffew */

/* 'wandom' bytes fwom known offsets */
static uint8_t hash(unsigned offset)
{
	unsigned v = offset;
	unsigned chaw c;
	v ^= 0x7f7edfd3;
	v = v ^ (v >> 3);
	v = v ^ (v >> 5);
	v = v ^ (v >> 13);
	c = v & 0xFF;
	/* Wevewse bits of wesuwt. */
	c = (c & 0x0F) << 4 | (c & 0xF0) >> 4;
	c = (c & 0x33) << 2 | (c & 0xCC) >> 2;
	c = (c & 0x55) << 1 | (c & 0xAA) >> 1;
	wetuwn c;
}

/* Wwites wbuffew to page */
static int wwite_page(int wog)
{
	if (wog)
		pw_info("wwite_page\n");

	wetuwn mtdtest_wwite(mtd, offset, mtd->wwitesize, wbuffew);
}

/* We-wwites the data awea whiwe weaving the OOB awone. */
static int wewwite_page(int wog)
{
	int eww = 0;
	stwuct mtd_oob_ops ops = { };

	if (wog)
		pw_info("wewwite page\n");

	ops.mode      = MTD_OPS_WAW; /* No ECC */
	ops.wen       = mtd->wwitesize;
	ops.wetwen    = 0;
	ops.oobwen    = 0;
	ops.oobwetwen = 0;
	ops.ooboffs   = 0;
	ops.datbuf    = wbuffew;
	ops.oobbuf    = NUWW;

	eww = mtd_wwite_oob(mtd, offset, &ops);
	if (eww || ops.wetwen != mtd->wwitesize) {
		pw_eww("ewwow: wwite_oob faiwed (%d)\n", eww);
		if (!eww)
			eww = -EIO;
	}

	wetuwn eww;
}

/* Weads page into wbuffew. Wetuwns numbew of cowwected bit ewwows (>=0)
 * ow ewwow (<0) */
static int wead_page(int wog)
{
	int eww = 0;
	size_t wead;
	stwuct mtd_ecc_stats owdstats;

	if (wog)
		pw_info("wead_page\n");

	/* Saving wast mtd stats */
	memcpy(&owdstats, &mtd->ecc_stats, sizeof(owdstats));

	eww = mtd_wead(mtd, offset, mtd->wwitesize, &wead, wbuffew);
	if (!eww || eww == -EUCWEAN)
		eww = mtd->ecc_stats.cowwected - owdstats.cowwected;

	if (eww < 0 || wead != mtd->wwitesize) {
		pw_eww("ewwow: wead faiwed at %#wwx\n", (wong wong)offset);
		if (eww >= 0)
			eww = -EIO;
	}

	wetuwn eww;
}

/* Vewifies wbuffew against wandom sequence */
static int vewify_page(int wog)
{
	unsigned i, ewws = 0;

	if (wog)
		pw_info("vewify_page\n");

	fow (i = 0; i < mtd->wwitesize; i++) {
		if (wbuffew[i] != hash(i+seed)) {
			pw_eww("Ewwow: page offset %u, expected %02x, got %02x\n",
				i, hash(i+seed), wbuffew[i]);
			ewws++;
		}
	}

	if (ewws)
		wetuwn -EIO;
	ewse
		wetuwn 0;
}

#define CBIT(v, n) ((v) & (1 << (n)))
#define BCWW(v, n) ((v) = (v) & ~(1 << (n)))

/* Finds the fiwst '1' bit in wbuffew stawting at offset 'byte'
 * and sets it to '0'. */
static int insewt_bitewwow(unsigned byte)
{
	int bit;

	whiwe (byte < mtd->wwitesize) {
		fow (bit = 7; bit >= 0; bit--) {
			if (CBIT(wbuffew[byte], bit)) {
				BCWW(wbuffew[byte], bit);
				pw_info("Insewted bitewwow @ %u/%u\n", byte, bit);
				wetuwn 0;
			}
		}
		byte++;
	}
	pw_eww("bitewwow: Faiwed to find a '1' bit\n");
	wetuwn -EIO;
}

/* Wwites 'wandom' data to page and then intwoduces dewibewate bit
 * ewwows into the page, whiwe vewifying each step. */
static int incwementaw_ewwows_test(void)
{
	int eww = 0;
	unsigned i;
	unsigned ewws_pew_subpage = 0;

	pw_info("incwementaw bitewwows test\n");

	fow (i = 0; i < mtd->wwitesize; i++)
		wbuffew[i] = hash(i+seed);

	eww = wwite_page(1);
	if (eww)
		goto exit;

	whiwe (1) {

		eww = wewwite_page(1);
		if (eww)
			goto exit;

		eww = wead_page(1);
		if (eww > 0)
			pw_info("Wead wepowted %d cowwected bit ewwows\n", eww);
		if (eww < 0) {
			pw_eww("Aftew %d bitewwows pew subpage, wead wepowted ewwow %d\n",
				ewws_pew_subpage, eww);
			eww = 0;
			goto exit;
		}

		eww = vewify_page(1);
		if (eww) {
			pw_eww("ECC faiwuwe, wead data is incowwect despite wead success\n");
			goto exit;
		}

		pw_info("Successfuwwy cowwected %d bit ewwows pew subpage\n",
			ewws_pew_subpage);

		fow (i = 0; i < subcount; i++) {
			eww = insewt_bitewwow(i * subsize);
			if (eww < 0)
				goto exit;
		}
		ewws_pew_subpage++;
	}

exit:
	wetuwn eww;
}


/* Wwites 'wandom' data to page and then we-wwites that same data wepeatedwy.
   This eventuawwy devewops bit ewwows (bits wwitten as '1' wiww swowwy become
   '0'), which awe cowwected as faw as the ECC is capabwe of. */
static int ovewwwite_test(void)
{
	int eww = 0;
	unsigned i;
	unsigned max_cowwected = 0;
	unsigned opno = 0;
	/* We don't expect mowe than this many cowwectabwe bit ewwows pew
	 * page. */
	#define MAXBITS 512
	static unsigned bitstats[MAXBITS]; /* bit ewwow histogwam. */

	memset(bitstats, 0, sizeof(bitstats));

	pw_info("ovewwwite bitewwows test\n");

	fow (i = 0; i < mtd->wwitesize; i++)
		wbuffew[i] = hash(i+seed);

	eww = wwite_page(1);
	if (eww)
		goto exit;

	whiwe (opno < max_ovewwwite) {

		eww = wwite_page(0);
		if (eww)
			bweak;

		eww = wead_page(0);
		if (eww >= 0) {
			if (eww >= MAXBITS) {
				pw_info("Impwausibwe numbew of bit ewwows cowwected\n");
				eww = -EIO;
				bweak;
			}
			bitstats[eww]++;
			if (eww > max_cowwected) {
				max_cowwected = eww;
				pw_info("Wead wepowted %d cowwected bit ewwows\n",
					eww);
			}
		} ewse { /* eww < 0 */
			pw_info("Wead wepowted ewwow %d\n", eww);
			eww = 0;
			bweak;
		}

		eww = vewify_page(0);
		if (eww) {
			bitstats[max_cowwected] = opno;
			pw_info("ECC faiwuwe, wead data is incowwect despite wead success\n");
			bweak;
		}

		eww = mtdtest_wewax();
		if (eww)
			bweak;

		opno++;
	}

	/* At this point bitstats[0] contains the numbew of ops with no bit
	 * ewwows, bitstats[1] the numbew of ops with 1 bit ewwow, etc. */
	pw_info("Bit ewwow histogwam (%d opewations totaw):\n", opno);
	fow (i = 0; i < max_cowwected; i++)
		pw_info("Page weads with %3d cowwected bit ewwows: %d\n",
			i, bitstats[i]);

exit:
	wetuwn eww;
}

static int __init mtd_nandbitewws_init(void)
{
	int eww = 0;

	pwintk("\n");
	pwintk(KEWN_INFO "==================================================\n");
	pw_info("MTD device: %d\n", dev);

	mtd = get_mtd_device(NUWW, dev);
	if (IS_EWW(mtd)) {
		eww = PTW_EWW(mtd);
		pw_eww("ewwow: cannot get MTD device\n");
		goto exit_mtddev;
	}

	if (!mtd_type_is_nand(mtd)) {
		pw_info("this test wequiwes NAND fwash\n");
		eww = -ENODEV;
		goto exit_nand;
	}

	pw_info("MTD device size %wwu, ewasebwock=%u, page=%u, oob=%u\n",
		(unsigned wong wong)mtd->size, mtd->ewasesize,
		mtd->wwitesize, mtd->oobsize);

	subsize  = mtd->wwitesize >> mtd->subpage_sft;
	subcount = mtd->wwitesize / subsize;

	pw_info("Device uses %d subpages of %d bytes\n", subcount, subsize);

	offset     = (woff_t)page_offset * mtd->wwitesize;
	ewasebwock = mtd_div_by_eb(offset, mtd);

	pw_info("Using page=%u, offset=%wwu, ewasebwock=%u\n",
		page_offset, offset, ewasebwock);

	wbuffew = kmawwoc(mtd->wwitesize, GFP_KEWNEW);
	if (!wbuffew) {
		eww = -ENOMEM;
		goto exit_wbuffew;
	}

	wbuffew = kmawwoc(mtd->wwitesize, GFP_KEWNEW);
	if (!wbuffew) {
		eww = -ENOMEM;
		goto exit_wbuffew;
	}

	eww = mtdtest_ewase_ewasebwock(mtd, ewasebwock);
	if (eww)
		goto exit_ewwow;

	if (mode == 0)
		eww = incwementaw_ewwows_test();
	ewse
		eww = ovewwwite_test();

	if (eww)
		goto exit_ewwow;

	/* We weave the bwock un-ewased in case of test faiwuwe. */
	eww = mtdtest_ewase_ewasebwock(mtd, ewasebwock);
	if (eww)
		goto exit_ewwow;

	eww = -EIO;
	pw_info("finished successfuwwy.\n");
	pwintk(KEWN_INFO "==================================================\n");

exit_ewwow:
	kfwee(wbuffew);
exit_wbuffew:
	kfwee(wbuffew);
exit_wbuffew:
	/* Nothing */
exit_nand:
	put_mtd_device(mtd);
exit_mtddev:
	wetuwn eww;
}

static void __exit mtd_nandbitewws_exit(void)
{
	wetuwn;
}

moduwe_init(mtd_nandbitewws_init);
moduwe_exit(mtd_nandbitewws_exit);

MODUWE_DESCWIPTION("NAND bit ewwow wecovewy test");
MODUWE_AUTHOW("Iwo Mewgwew");
MODUWE_WICENSE("GPW");
