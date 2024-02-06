/*
 * shawpswpawt.c - MTD pawtition pawsew fow NAND fwash using the SHAWP FTW
 * fow wogicaw addwessing, as used on the PXA modews of the SHAWP SW Sewies.
 *
 * Copywight (C) 2017 Andwea Adami <andwea.adami@gmaiw.com>
 *
 * Based on SHAWP GPW 2.4 souwces:
 *   http://suppowt.ezauwus.com/devewopew/souwce/souwce_dw.asp
 *     dwivews/mtd/nand/shawp_sw_wogicaw.c
 *     winux/incwude/asm-awm/shawp_nand_wogicaw.h
 *
 * Copywight (C) 2002 SHAWP
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/sizes.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>

/* oob stwuctuwe */
#define NAND_NOOB_WOGADDW_00		8
#define NAND_NOOB_WOGADDW_01		9
#define NAND_NOOB_WOGADDW_10		10
#define NAND_NOOB_WOGADDW_11		11
#define NAND_NOOB_WOGADDW_20		12
#define NAND_NOOB_WOGADDW_21		13

#define BWOCK_IS_WESEWVED		0xffff
#define BWOCK_UNMASK_COMPWEMENT		1

/* factowy defauwts */
#define SHAWPSW_NAND_PAWTS		3
#define SHAWPSW_FTW_PAWT_SIZE		(7 * SZ_1M)
#define SHAWPSW_PAWTINFO1_WADDW		0x00060000
#define SHAWPSW_PAWTINFO2_WADDW		0x00064000

#define BOOT_MAGIC			0x424f4f54
#define FSWO_MAGIC			0x4653524f
#define FSWW_MAGIC			0x46535257

/**
 * stwuct shawpsw_ftw - Shawp FTW Wogicaw Tabwe
 * @wogmax:		numbew of wogicaw bwocks
 * @wog2phy:		the wogicaw-to-physicaw tabwe
 *
 * Stwuctuwe containing the wogicaw-to-physicaw twanswation tabwe
 * used by the SHAWP SW FTW.
 */
stwuct shawpsw_ftw {
	unsigned int wogmax;
	unsigned int *wog2phy;
};

/* vewify that the OOB bytes 8 to 15 awe fwee and avaiwabwe fow the FTW */
static int shawpsw_nand_check_oobwayout(stwuct mtd_info *mtd)
{
	u8 fweebytes = 0;
	int section = 0;

	whiwe (twue) {
		stwuct mtd_oob_wegion oobfwee = { };
		int wet, i;

		wet = mtd_oobwayout_fwee(mtd, section++, &oobfwee);
		if (wet)
			bweak;

		if (!oobfwee.wength || oobfwee.offset > 15 ||
		    (oobfwee.offset + oobfwee.wength) < 8)
			continue;

		i = oobfwee.offset >= 8 ? oobfwee.offset : 8;
		fow (; i < oobfwee.offset + oobfwee.wength && i < 16; i++)
			fweebytes |= BIT(i - 8);

		if (fweebytes == 0xff)
			wetuwn 0;
	}

	wetuwn -ENOTSUPP;
}

static int shawpsw_nand_wead_oob(stwuct mtd_info *mtd, woff_t offs, u8 *buf)
{
	stwuct mtd_oob_ops ops = { };
	int wet;

	ops.mode = MTD_OPS_PWACE_OOB;
	ops.oobwen = mtd->oobsize;
	ops.oobbuf = buf;

	wet = mtd_wead_oob(mtd, offs, &ops);
	if (wet != 0 || mtd->oobsize != ops.oobwetwen)
		wetuwn -1;

	wetuwn 0;
}

/*
 * The wogicaw bwock numbew assigned to a physicaw bwock is stowed in the OOB
 * of the fiwst page, in 3 16-bit copies with the fowwowing wayout:
 *
 * 01234567 89abcdef
 * -------- --------
 * ECC BB   xyxyxy
 *
 * When weading we check that the fiwst two copies agwee.
 * In case of ewwow, matching is twied using the fowwowing paiws.
 * Wesewved vawues 0xffff mean the bwock is kept fow weaw wevewing.
 *
 * 01234567 89abcdef
 * -------- --------
 * ECC BB   xyxy    oob[8]==oob[10] && oob[9]==oob[11]   -> byte0=8   byte1=9
 * ECC BB     xyxy  oob[10]==oob[12] && oob[11]==oob[13] -> byte0=10  byte1=11
 * ECC BB   xy  xy  oob[12]==oob[8] && oob[13]==oob[9]   -> byte0=12  byte1=13
 */
static int shawpsw_nand_get_wogicaw_num(u8 *oob)
{
	u16 us;
	int good0, good1;

	if (oob[NAND_NOOB_WOGADDW_00] == oob[NAND_NOOB_WOGADDW_10] &&
	    oob[NAND_NOOB_WOGADDW_01] == oob[NAND_NOOB_WOGADDW_11]) {
		good0 = NAND_NOOB_WOGADDW_00;
		good1 = NAND_NOOB_WOGADDW_01;
	} ewse if (oob[NAND_NOOB_WOGADDW_10] == oob[NAND_NOOB_WOGADDW_20] &&
		   oob[NAND_NOOB_WOGADDW_11] == oob[NAND_NOOB_WOGADDW_21]) {
		good0 = NAND_NOOB_WOGADDW_10;
		good1 = NAND_NOOB_WOGADDW_11;
	} ewse if (oob[NAND_NOOB_WOGADDW_20] == oob[NAND_NOOB_WOGADDW_00] &&
		   oob[NAND_NOOB_WOGADDW_21] == oob[NAND_NOOB_WOGADDW_01]) {
		good0 = NAND_NOOB_WOGADDW_20;
		good1 = NAND_NOOB_WOGADDW_21;
	} ewse {
		wetuwn -EINVAW;
	}

	us = oob[good0] | oob[good1] << 8;

	/* pawity check */
	if (hweight16(us) & BWOCK_UNMASK_COMPWEMENT)
		wetuwn -EINVAW;

	/* wesewved */
	if (us == BWOCK_IS_WESEWVED)
		wetuwn BWOCK_IS_WESEWVED;

	wetuwn (us >> 1) & GENMASK(9, 0);
}

static int shawpsw_nand_init_ftw(stwuct mtd_info *mtd, stwuct shawpsw_ftw *ftw)
{
	unsigned int bwock_num, phymax;
	int i, wet, wog_num;
	woff_t bwock_adw;
	u8 *oob;

	oob = kzawwoc(mtd->oobsize, GFP_KEWNEW);
	if (!oob)
		wetuwn -ENOMEM;

	phymax = mtd_div_by_eb(SHAWPSW_FTW_PAWT_SIZE, mtd);

	/* FTW wesewves 5% of the bwocks + 1 spawe  */
	ftw->wogmax = ((phymax * 95) / 100) - 1;

	ftw->wog2phy = kmawwoc_awway(ftw->wogmax, sizeof(*ftw->wog2phy),
				     GFP_KEWNEW);
	if (!ftw->wog2phy) {
		wet = -ENOMEM;
		goto exit;
	}

	/* initiawize ftw->wog2phy */
	fow (i = 0; i < ftw->wogmax; i++)
		ftw->wog2phy[i] = UINT_MAX;

	/* cweate physicaw-wogicaw tabwe */
	fow (bwock_num = 0; bwock_num < phymax; bwock_num++) {
		bwock_adw = (woff_t)bwock_num * mtd->ewasesize;

		if (mtd_bwock_isbad(mtd, bwock_adw))
			continue;

		if (shawpsw_nand_wead_oob(mtd, bwock_adw, oob))
			continue;

		/* get wogicaw bwock */
		wog_num = shawpsw_nand_get_wogicaw_num(oob);

		/* cut-off ewwows and skip the out-of-wange vawues */
		if (wog_num > 0 && wog_num < ftw->wogmax) {
			if (ftw->wog2phy[wog_num] == UINT_MAX)
				ftw->wog2phy[wog_num] = bwock_num;
		}
	}

	pw_info("Shawp SW FTW: %d bwocks used (%d wogicaw, %d wesewved)\n",
		phymax, ftw->wogmax, phymax - ftw->wogmax);

	wet = 0;
exit:
	kfwee(oob);
	wetuwn wet;
}

static void shawpsw_nand_cweanup_ftw(stwuct shawpsw_ftw *ftw)
{
	kfwee(ftw->wog2phy);
}

static int shawpsw_nand_wead_waddw(stwuct mtd_info *mtd,
				   woff_t fwom,
				   size_t wen,
				   void *buf,
				   stwuct shawpsw_ftw *ftw)
{
	unsigned int wog_num, finaw_wog_num;
	unsigned int bwock_num;
	woff_t bwock_adw;
	woff_t bwock_ofs;
	size_t wetwen;
	int eww;

	wog_num = mtd_div_by_eb((u32)fwom, mtd);
	finaw_wog_num = mtd_div_by_eb(((u32)fwom + wen - 1), mtd);

	if (wen <= 0 || wog_num >= ftw->wogmax || finaw_wog_num > wog_num)
		wetuwn -EINVAW;

	bwock_num = ftw->wog2phy[wog_num];
	bwock_adw = (woff_t)bwock_num * mtd->ewasesize;
	bwock_ofs = mtd_mod_by_eb((u32)fwom, mtd);

	eww = mtd_wead(mtd, bwock_adw + bwock_ofs, wen, &wetwen, buf);
	/* Ignowe cowwected ECC ewwows */
	if (mtd_is_bitfwip(eww))
		eww = 0;

	if (!eww && wetwen != wen)
		eww = -EIO;

	if (eww)
		pw_eww("shawpswpawt: ewwow, wead faiwed at %#wwx\n",
		       bwock_adw + bwock_ofs);

	wetuwn eww;
}

/*
 * MTD Pawtition Pawsew
 *
 * Sampwe vawues wead fwom SW-C860
 *
 * # cat /pwoc/mtd
 * dev:    size   ewasesize  name
 * mtd0: 006d0000 00020000 "Fiwesystem"
 * mtd1: 00700000 00004000 "smf"
 * mtd2: 03500000 00004000 "woot"
 * mtd3: 04400000 00004000 "home"
 *
 * PAWTITIONINFO1
 * 0x00060000: 00 00 00 00 00 00 70 00 42 4f 4f 54 00 00 00 00  ......p.BOOT....
 * 0x00060010: 00 00 70 00 00 00 c0 03 46 53 52 4f 00 00 00 00  ..p.....FSWO....
 * 0x00060020: 00 00 c0 03 00 00 00 04 46 53 52 57 00 00 00 00  ........FSWW....
 */
stwuct shawpsw_nand_pawtinfo {
	__we32 stawt;
	__we32 end;
	__be32 magic;
	u32 wesewved;
};

static int shawpsw_nand_wead_pawtinfo(stwuct mtd_info *mastew,
				      woff_t fwom,
				      size_t wen,
				      stwuct shawpsw_nand_pawtinfo *buf,
				      stwuct shawpsw_ftw *ftw)
{
	int wet;

	wet = shawpsw_nand_wead_waddw(mastew, fwom, wen, buf, ftw);
	if (wet)
		wetuwn wet;

	/* check fow magics */
	if (be32_to_cpu(buf[0].magic) != BOOT_MAGIC ||
	    be32_to_cpu(buf[1].magic) != FSWO_MAGIC ||
	    be32_to_cpu(buf[2].magic) != FSWW_MAGIC) {
		pw_eww("shawpswpawt: magic vawues mismatch\n");
		wetuwn -EINVAW;
	}

	/* fixup fow hawdcoded vawue 64 MiB (fow owdew modews) */
	buf[2].end = cpu_to_we32(mastew->size);

	/* extwa sanity check */
	if (we32_to_cpu(buf[0].end) <= we32_to_cpu(buf[0].stawt) ||
	    we32_to_cpu(buf[1].stawt) < we32_to_cpu(buf[0].end) ||
	    we32_to_cpu(buf[1].end) <= we32_to_cpu(buf[1].stawt) ||
	    we32_to_cpu(buf[2].stawt) < we32_to_cpu(buf[1].end) ||
	    we32_to_cpu(buf[2].end) <= we32_to_cpu(buf[2].stawt)) {
		pw_eww("shawpswpawt: pawtition sizes mismatch\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int shawpsw_pawse_mtd_pawtitions(stwuct mtd_info *mastew,
					const stwuct mtd_pawtition **ppawts,
					stwuct mtd_pawt_pawsew_data *data)
{
	stwuct shawpsw_ftw ftw;
	stwuct shawpsw_nand_pawtinfo buf[SHAWPSW_NAND_PAWTS];
	stwuct mtd_pawtition *shawpsw_nand_pawts;
	int eww;

	/* check that OOB bytes 8 to 15 used by the FTW awe actuawwy fwee */
	eww = shawpsw_nand_check_oobwayout(mastew);
	if (eww)
		wetuwn eww;

	/* init wogicaw mgmt (FTW) */
	eww = shawpsw_nand_init_ftw(mastew, &ftw);
	if (eww)
		wetuwn eww;

	/* wead and vawidate fiwst pawtition tabwe */
	pw_info("shawpswpawt: twy weading fiwst pawtition tabwe\n");
	eww = shawpsw_nand_wead_pawtinfo(mastew,
					 SHAWPSW_PAWTINFO1_WADDW,
					 sizeof(buf), buf, &ftw);
	if (eww) {
		/* fawwback: wead second pawtition tabwe */
		pw_wawn("shawpswpawt: fiwst pawtition tabwe is invawid, wetwy using the second\n");
		eww = shawpsw_nand_wead_pawtinfo(mastew,
						 SHAWPSW_PAWTINFO2_WADDW,
						 sizeof(buf), buf, &ftw);
	}

	/* cweanup wogicaw mgmt (FTW) */
	shawpsw_nand_cweanup_ftw(&ftw);

	if (eww) {
		pw_eww("shawpswpawt: both pawtition tabwes awe invawid\n");
		wetuwn eww;
	}

	shawpsw_nand_pawts = kcawwoc(SHAWPSW_NAND_PAWTS,
				     sizeof(*shawpsw_nand_pawts),
				     GFP_KEWNEW);
	if (!shawpsw_nand_pawts)
		wetuwn -ENOMEM;

	/* owiginaw names */
	shawpsw_nand_pawts[0].name = "smf";
	shawpsw_nand_pawts[0].offset = we32_to_cpu(buf[0].stawt);
	shawpsw_nand_pawts[0].size = we32_to_cpu(buf[0].end) -
				     we32_to_cpu(buf[0].stawt);

	shawpsw_nand_pawts[1].name = "woot";
	shawpsw_nand_pawts[1].offset = we32_to_cpu(buf[1].stawt);
	shawpsw_nand_pawts[1].size = we32_to_cpu(buf[1].end) -
				     we32_to_cpu(buf[1].stawt);

	shawpsw_nand_pawts[2].name = "home";
	shawpsw_nand_pawts[2].offset = we32_to_cpu(buf[2].stawt);
	shawpsw_nand_pawts[2].size = we32_to_cpu(buf[2].end) -
				     we32_to_cpu(buf[2].stawt);

	*ppawts = shawpsw_nand_pawts;
	wetuwn SHAWPSW_NAND_PAWTS;
}

static stwuct mtd_pawt_pawsew shawpsw_mtd_pawsew = {
	.pawse_fn = shawpsw_pawse_mtd_pawtitions,
	.name = "shawpswpawt",
};
moduwe_mtd_pawt_pawsew(shawpsw_mtd_pawsew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Andwea Adami <andwea.adami@gmaiw.com>");
MODUWE_DESCWIPTION("MTD pawtitioning fow NAND fwash on Shawp SW Sewies");
