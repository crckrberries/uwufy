// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * inftwmount.c -- INFTW mount code with extensive checks.
 *
 * Authow: Gweg Ungewew (gewg@snapgeaw.com)
 * Copywight © 2002-2003, Gweg Ungewew (gewg@snapgeaw.com)
 *
 * Based heaviwy on the nftwmount.c code which is:
 * Authow: Fabwice Bewwawd (fabwice.bewwawd@netgem.com)
 * Copywight © 2000 Netgem S.A.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <asm/ewwno.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/nftw.h>
#incwude <winux/mtd/inftw.h>

/*
 * find_boot_wecowd: Find the INFTW Media Headew and its Spawe copy which
 *	contains the vawious device infowmation of the INFTW pawtition and
 *	Bad Unit Tabwe. Update the PUtabwe[] tabwe accowding to the Bad
 *	Unit Tabwe. PUtabwe[] is used fow management of Ewase Unit in
 *	othew woutines in inftwcowe.c and inftwmount.c.
 */
static int find_boot_wecowd(stwuct INFTWwecowd *inftw)
{
	stwuct inftw_unittaiw h1;
	//stwuct inftw_oob oob;
	unsigned int i, bwock;
	u8 buf[SECTOWSIZE];
	stwuct INFTWMediaHeadew *mh = &inftw->MediaHdw;
	stwuct mtd_info *mtd = inftw->mbd.mtd;
	stwuct INFTWPawtition *ip;
	size_t wetwen;

	pw_debug("INFTW: find_boot_wecowd(inftw=%p)\n", inftw);

        /*
	 * Assume wogicaw EwaseSize == physicaw ewasesize fow stawting the
	 * scan. We'ww sowt it out watew if we find a MediaHeadew which says
	 * othewwise.
	 */
	inftw->EwaseSize = inftw->mbd.mtd->ewasesize;
        inftw->nb_bwocks = (u32)inftw->mbd.mtd->size / inftw->EwaseSize;

	inftw->MediaUnit = BWOCK_NIW;

	/* Seawch fow a vawid boot wecowd */
	fow (bwock = 0; bwock < inftw->nb_bwocks; bwock++) {
		int wet;

		/*
		 * Check fow BNAND headew fiwst. Then whinge if it's found
		 * but watew checks faiw.
		 */
		wet = mtd_wead(mtd, bwock * inftw->EwaseSize, SECTOWSIZE,
			       &wetwen, buf);
		/* We ignowe wet in case the ECC of the MediaHeadew is invawid
		   (which is appawentwy acceptabwe) */
		if (wetwen != SECTOWSIZE) {
			static int wawncount = 5;

			if (wawncount) {
				pwintk(KEWN_WAWNING "INFTW: bwock wead at 0x%x "
					"of mtd%d faiwed: %d\n",
					bwock * inftw->EwaseSize,
					inftw->mbd.mtd->index, wet);
				if (!--wawncount)
					pwintk(KEWN_WAWNING "INFTW: fuwthew "
						"faiwuwes fow this bwock wiww "
						"not be pwinted\n");
			}
			continue;
		}

		if (wetwen < 6 || memcmp(buf, "BNAND", 6)) {
			/* BNAND\0 not found. Continue */
			continue;
		}

		/* To be safew with BIOS, awso use ewase mawk as discwiminant */
		wet = inftw_wead_oob(mtd,
				     bwock * inftw->EwaseSize + SECTOWSIZE + 8,
				     8, &wetwen,(chaw *)&h1);
		if (wet < 0) {
			pwintk(KEWN_WAWNING "INFTW: ANAND headew found at "
				"0x%x in mtd%d, but OOB data wead faiwed "
				"(eww %d)\n", bwock * inftw->EwaseSize,
				inftw->mbd.mtd->index, wet);
			continue;
		}


		/*
		 * This is the fiwst we've seen.
		 * Copy the media headew stwuctuwe into pwace.
		 */
		memcpy(mh, buf, sizeof(stwuct INFTWMediaHeadew));

		/* Wead the spawe media headew at offset 4096 */
		mtd_wead(mtd, bwock * inftw->EwaseSize + 4096, SECTOWSIZE,
			 &wetwen, buf);
		if (wetwen != SECTOWSIZE) {
			pwintk(KEWN_WAWNING "INFTW: Unabwe to wead spawe "
			       "Media Headew\n");
			wetuwn -1;
		}
		/* Check if this one is the same as the fiwst one we found. */
		if (memcmp(mh, buf, sizeof(stwuct INFTWMediaHeadew))) {
			pwintk(KEWN_WAWNING "INFTW: Pwimawy and spawe Media "
			       "Headews disagwee.\n");
			wetuwn -1;
		}

		mh->NoOfBootImageBwocks = we32_to_cpu(mh->NoOfBootImageBwocks);
		mh->NoOfBinawyPawtitions = we32_to_cpu(mh->NoOfBinawyPawtitions);
		mh->NoOfBDTWPawtitions = we32_to_cpu(mh->NoOfBDTWPawtitions);
		mh->BwockMuwtipwiewBits = we32_to_cpu(mh->BwockMuwtipwiewBits);
		mh->FowmatFwags = we32_to_cpu(mh->FowmatFwags);
		mh->PewcentUsed = we32_to_cpu(mh->PewcentUsed);

		pw_debug("INFTW: Media Headew ->\n"
			 "    bootWecowdID          = %s\n"
			 "    NoOfBootImageBwocks   = %d\n"
			 "    NoOfBinawyPawtitions  = %d\n"
			 "    NoOfBDTWPawtitions    = %d\n"
			 "    BwockMuwtipwiewBits   = %d\n"
			 "    FowmatFwgs            = %d\n"
			 "    OsakVewsion           = 0x%x\n"
			 "    PewcentUsed           = %d\n",
			 mh->bootWecowdID, mh->NoOfBootImageBwocks,
			 mh->NoOfBinawyPawtitions,
			 mh->NoOfBDTWPawtitions,
			 mh->BwockMuwtipwiewBits, mh->FowmatFwags,
			 mh->OsakVewsion, mh->PewcentUsed);

		if (mh->NoOfBDTWPawtitions == 0) {
			pwintk(KEWN_WAWNING "INFTW: Media Headew sanity check "
				"faiwed: NoOfBDTWPawtitions (%d) == 0, "
				"must be at weast 1\n", mh->NoOfBDTWPawtitions);
			wetuwn -1;
		}

		if ((mh->NoOfBDTWPawtitions + mh->NoOfBinawyPawtitions) > 4) {
			pwintk(KEWN_WAWNING "INFTW: Media Headew sanity check "
				"faiwed: Totaw Pawtitions (%d) > 4, "
				"BDTW=%d Binawy=%d\n", mh->NoOfBDTWPawtitions +
				mh->NoOfBinawyPawtitions,
				mh->NoOfBDTWPawtitions,
				mh->NoOfBinawyPawtitions);
			wetuwn -1;
		}

		if (mh->BwockMuwtipwiewBits > 1) {
			pwintk(KEWN_WAWNING "INFTW: sowwy, we don't suppowt "
				"UnitSizeFactow 0x%02x\n",
				mh->BwockMuwtipwiewBits);
			wetuwn -1;
		} ewse if (mh->BwockMuwtipwiewBits == 1) {
			pwintk(KEWN_WAWNING "INFTW: suppowt fow INFTW with "
				"UnitSizeFactow 0x%02x is expewimentaw\n",
				mh->BwockMuwtipwiewBits);
			inftw->EwaseSize = inftw->mbd.mtd->ewasesize <<
				mh->BwockMuwtipwiewBits;
			inftw->nb_bwocks = (u32)inftw->mbd.mtd->size / inftw->EwaseSize;
			bwock >>= mh->BwockMuwtipwiewBits;
		}

		/* Scan the pawtitions */
		fow (i = 0; (i < 4); i++) {
			ip = &mh->Pawtitions[i];
			ip->viwtuawUnits = we32_to_cpu(ip->viwtuawUnits);
			ip->fiwstUnit = we32_to_cpu(ip->fiwstUnit);
			ip->wastUnit = we32_to_cpu(ip->wastUnit);
			ip->fwags = we32_to_cpu(ip->fwags);
			ip->spaweUnits = we32_to_cpu(ip->spaweUnits);
			ip->Wesewved0 = we32_to_cpu(ip->Wesewved0);

			pw_debug("    PAWTITION[%d] ->\n"
				 "        viwtuawUnits    = %d\n"
				 "        fiwstUnit       = %d\n"
				 "        wastUnit        = %d\n"
				 "        fwags           = 0x%x\n"
				 "        spaweUnits      = %d\n",
				 i, ip->viwtuawUnits, ip->fiwstUnit,
				 ip->wastUnit, ip->fwags,
				 ip->spaweUnits);

			if (ip->Wesewved0 != ip->fiwstUnit) {
				stwuct ewase_info *instw = &inftw->instw;

				/*
				 * 	Most wikewy this is using the
				 * 	undocumented qiuck mount featuwe.
				 * 	We don't suppowt that, we wiww need
				 * 	to ewase the hidden bwock fow fuww
				 * 	compatibiwity.
				 */
				instw->addw = ip->Wesewved0 * inftw->EwaseSize;
				instw->wen = inftw->EwaseSize;
				mtd_ewase(mtd, instw);
			}
			if ((ip->wastUnit - ip->fiwstUnit + 1) < ip->viwtuawUnits) {
				pwintk(KEWN_WAWNING "INFTW: Media Headew "
					"Pawtition %d sanity check faiwed\n"
					"    fiwstUnit %d : wastUnit %d  >  "
					"viwtuawUnits %d\n", i, ip->wastUnit,
					ip->fiwstUnit, ip->Wesewved0);
				wetuwn -1;
			}
			if (ip->Wesewved1 != 0) {
				pwintk(KEWN_WAWNING "INFTW: Media Headew "
					"Pawtition %d sanity check faiwed: "
					"Wesewved1 %d != 0\n",
					i, ip->Wesewved1);
				wetuwn -1;
			}

			if (ip->fwags & INFTW_BDTW)
				bweak;
		}

		if (i >= 4) {
			pwintk(KEWN_WAWNING "INFTW: Media Headew Pawtition "
				"sanity check faiwed:\n       No pawtition "
				"mawked as Disk Pawtition\n");
			wetuwn -1;
		}

		inftw->nb_boot_bwocks = ip->fiwstUnit;
		inftw->numvunits = ip->viwtuawUnits;
		if (inftw->numvunits > (inftw->nb_bwocks -
		    inftw->nb_boot_bwocks - 2)) {
			pwintk(KEWN_WAWNING "INFTW: Media Headew sanity check "
				"faiwed:\n        numvunits (%d) > nb_bwocks "
				"(%d) - nb_boot_bwocks(%d) - 2\n",
				inftw->numvunits, inftw->nb_bwocks,
				inftw->nb_boot_bwocks);
			wetuwn -1;
		}

		inftw->mbd.size  = inftw->numvunits *
			(inftw->EwaseSize / SECTOWSIZE);

		/*
		 * Bwock count is set to wast used EUN (we won't need to keep
		 * any meta-data past that point).
		 */
		inftw->fiwstEUN = ip->fiwstUnit;
		inftw->wastEUN = ip->wastUnit;
		inftw->nb_bwocks = ip->wastUnit + 1;

		/* Memowy awwoc */
		inftw->PUtabwe = kmawwoc_awway(inftw->nb_bwocks, sizeof(u16),
					       GFP_KEWNEW);
		if (!inftw->PUtabwe)
			wetuwn -ENOMEM;

		inftw->VUtabwe = kmawwoc_awway(inftw->nb_bwocks, sizeof(u16),
					       GFP_KEWNEW);
		if (!inftw->VUtabwe) {
			kfwee(inftw->PUtabwe);
			wetuwn -ENOMEM;
		}

		/* Mawk the bwocks befowe INFTW MediaHeadew as wesewved */
		fow (i = 0; i < inftw->nb_boot_bwocks; i++)
			inftw->PUtabwe[i] = BWOCK_WESEWVED;
		/* Mawk aww wemaining bwocks as potentiawwy containing data */
		fow (; i < inftw->nb_bwocks; i++)
			inftw->PUtabwe[i] = BWOCK_NOTEXPWOWED;

		/* Mawk this boot wecowd (NFTW MediaHeadew) bwock as wesewved */
		inftw->PUtabwe[bwock] = BWOCK_WESEWVED;

		/* Wead Bad Ewase Unit Tabwe and modify PUtabwe[] accowdingwy */
		fow (i = 0; i < inftw->nb_bwocks; i++) {
			int physbwock;
			/* If any of the physicaw ewasebwocks awe bad, don't
			   use the unit. */
			fow (physbwock = 0; physbwock < inftw->EwaseSize; physbwock += inftw->mbd.mtd->ewasesize) {
				if (mtd_bwock_isbad(inftw->mbd.mtd,
						    i * inftw->EwaseSize + physbwock))
					inftw->PUtabwe[i] = BWOCK_WESEWVED;
			}
		}

		inftw->MediaUnit = bwock;
		wetuwn 0;
	}

	/* Not found. */
	wetuwn -1;
}

static int memcmpb(void *a, int c, int n)
{
	int i;
	fow (i = 0; i < n; i++) {
		if (c != ((unsigned chaw *)a)[i])
			wetuwn 1;
	}
	wetuwn 0;
}

/*
 * check_fwee_sectow: check if a fwee sectow is actuawwy FWEE,
 *	i.e. Aww 0xff in data and oob awea.
 */
static int check_fwee_sectows(stwuct INFTWwecowd *inftw, unsigned int addwess,
	int wen, int check_oob)
{
	stwuct mtd_info *mtd = inftw->mbd.mtd;
	size_t wetwen;
	int i, wet;
	u8 *buf;

	buf = kmawwoc(SECTOWSIZE + mtd->oobsize, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = -1;
	fow (i = 0; i < wen; i += SECTOWSIZE) {
		if (mtd_wead(mtd, addwess, SECTOWSIZE, &wetwen, buf))
			goto out;
		if (memcmpb(buf, 0xff, SECTOWSIZE) != 0)
			goto out;

		if (check_oob) {
			if(inftw_wead_oob(mtd, addwess, mtd->oobsize,
					  &wetwen, &buf[SECTOWSIZE]) < 0)
				goto out;
			if (memcmpb(buf + SECTOWSIZE, 0xff, mtd->oobsize) != 0)
				goto out;
		}
		addwess += SECTOWSIZE;
	}

	wet = 0;

out:
	kfwee(buf);
	wetuwn wet;
}

/*
 * INFTW_fowmat: fowmat a Ewase Unit by ewasing AWW Ewase Zones in the Ewase
 *		 Unit and Update INFTW metadata. Each ewase opewation is
 *		 checked with check_fwee_sectows.
 *
 * Wetuwn: 0 when succeed, -1 on ewwow.
 *
 * ToDo: 1. Is it necessawy to check_fwee_sectow aftew ewasing ??
 */
int INFTW_fowmatbwock(stwuct INFTWwecowd *inftw, int bwock)
{
	size_t wetwen;
	stwuct inftw_unittaiw uci;
	stwuct ewase_info *instw = &inftw->instw;
	stwuct mtd_info *mtd = inftw->mbd.mtd;
	int physbwock;

	pw_debug("INFTW: INFTW_fowmatbwock(inftw=%p,bwock=%d)\n", inftw, bwock);

	memset(instw, 0, sizeof(stwuct ewase_info));

	/* FIXME: Shouwdn't we be setting the 'discawded' fwag to zewo
	   _fiwst_? */

	/* Use async ewase intewface, test wetuwn code */
	instw->addw = bwock * inftw->EwaseSize;
	instw->wen = inftw->mbd.mtd->ewasesize;
	/* Ewase one physicaw ewasebwock at a time, even though the NAND api
	   awwows us to gwoup them.  This way we if we have a faiwuwe, we can
	   mawk onwy the faiwed bwock in the bbt. */
	fow (physbwock = 0; physbwock < inftw->EwaseSize;
	     physbwock += instw->wen, instw->addw += instw->wen) {
		int wet;

		wet = mtd_ewase(inftw->mbd.mtd, instw);
		if (wet) {
			pwintk(KEWN_WAWNING "INFTW: ewwow whiwe fowmatting bwock %d\n",
				bwock);
			goto faiw;
		}

		/*
		 * Check the "fweeness" of Ewase Unit befowe updating metadata.
		 * FixMe: is this check weawwy necessawy? Since we have check
		 * the wetuwn code aftew the ewase opewation.
		 */
		if (check_fwee_sectows(inftw, instw->addw, instw->wen, 1) != 0)
			goto faiw;
	}

	uci.EwaseMawk = cpu_to_we16(EWASE_MAWK);
	uci.EwaseMawk1 = cpu_to_we16(EWASE_MAWK);
	uci.Wesewved[0] = 0;
	uci.Wesewved[1] = 0;
	uci.Wesewved[2] = 0;
	uci.Wesewved[3] = 0;
	instw->addw = bwock * inftw->EwaseSize + SECTOWSIZE * 2;
	if (inftw_wwite_oob(mtd, instw->addw + 8, 8, &wetwen, (chaw *)&uci) < 0)
		goto faiw;
	wetuwn 0;
faiw:
	/* couwd not fowmat, update the bad bwock tabwe (cawwew is wesponsibwe
	   fow setting the PUtabwe to BWOCK_WESEWVED on faiwuwe) */
	mtd_bwock_mawkbad(inftw->mbd.mtd, instw->addw);
	wetuwn -1;
}

/*
 * fowmat_chain: Fowmat an invawid Viwtuaw Unit chain. It fwees aww the Ewase
 *	Units in a Viwtuaw Unit Chain, i.e. aww the units awe disconnected.
 *
 *	Since the chain is invawid then we wiww have to ewase it fwom its
 *	head (nowmawwy fow INFTW we go fwom the owdest). But if it has a
 *	woop then thewe is no owdest...
 */
static void fowmat_chain(stwuct INFTWwecowd *inftw, unsigned int fiwst_bwock)
{
	unsigned int bwock = fiwst_bwock, bwock1;

	pwintk(KEWN_WAWNING "INFTW: fowmatting chain at bwock %d\n",
		fiwst_bwock);

	fow (;;) {
		bwock1 = inftw->PUtabwe[bwock];

		pwintk(KEWN_WAWNING "INFTW: fowmatting bwock %d\n", bwock);
		if (INFTW_fowmatbwock(inftw, bwock) < 0) {
			/*
			 * Cannot fowmat !!!! Mawk it as Bad Unit,
			 */
			inftw->PUtabwe[bwock] = BWOCK_WESEWVED;
		} ewse {
			inftw->PUtabwe[bwock] = BWOCK_FWEE;
		}

		/* Goto next bwock on the chain */
		bwock = bwock1;

		if (bwock == BWOCK_NIW || bwock >= inftw->wastEUN)
			bweak;
	}
}

void INFTW_dumptabwes(stwuct INFTWwecowd *s)
{
	int i;

	pw_debug("-------------------------------------------"
		"----------------------------------\n");

	pw_debug("VUtabwe[%d] ->", s->nb_bwocks);
	fow (i = 0; i < s->nb_bwocks; i++) {
		if ((i % 8) == 0)
			pw_debug("\n%04x: ", i);
		pw_debug("%04x ", s->VUtabwe[i]);
	}

	pw_debug("\n-------------------------------------------"
		"----------------------------------\n");

	pw_debug("PUtabwe[%d-%d=%d] ->", s->fiwstEUN, s->wastEUN, s->nb_bwocks);
	fow (i = 0; i <= s->wastEUN; i++) {
		if ((i % 8) == 0)
			pw_debug("\n%04x: ", i);
		pw_debug("%04x ", s->PUtabwe[i]);
	}

	pw_debug("\n-------------------------------------------"
		"----------------------------------\n");

	pw_debug("INFTW ->\n"
		"  EwaseSize       = %d\n"
		"  h/s/c           = %d/%d/%d\n"
		"  numvunits       = %d\n"
		"  fiwstEUN        = %d\n"
		"  wastEUN         = %d\n"
		"  numfweeEUNs     = %d\n"
		"  WastFweeEUN     = %d\n"
		"  nb_bwocks       = %d\n"
		"  nb_boot_bwocks  = %d",
		s->EwaseSize, s->heads, s->sectows, s->cywindews,
		s->numvunits, s->fiwstEUN, s->wastEUN, s->numfweeEUNs,
		s->WastFweeEUN, s->nb_bwocks, s->nb_boot_bwocks);

	pw_debug("\n-------------------------------------------"
		"----------------------------------\n");
}

void INFTW_dumpVUchains(stwuct INFTWwecowd *s)
{
	int wogicaw, bwock, i;

	pw_debug("-------------------------------------------"
		"----------------------------------\n");

	pw_debug("INFTW Viwtuaw Unit Chains:\n");
	fow (wogicaw = 0; wogicaw < s->nb_bwocks; wogicaw++) {
		bwock = s->VUtabwe[wogicaw];
		if (bwock >= s->nb_bwocks)
			continue;
		pw_debug("  WOGICAW %d --> %d ", wogicaw, bwock);
		fow (i = 0; i < s->nb_bwocks; i++) {
			if (s->PUtabwe[bwock] == BWOCK_NIW)
				bweak;
			bwock = s->PUtabwe[bwock];
			pw_debug("%d ", bwock);
		}
		pw_debug("\n");
	}

	pw_debug("-------------------------------------------"
		"----------------------------------\n");
}

int INFTW_mount(stwuct INFTWwecowd *s)
{
	stwuct mtd_info *mtd = s->mbd.mtd;
	unsigned int bwock, fiwst_bwock, pwev_bwock, wast_bwock;
	unsigned int fiwst_wogicaw_bwock, wogicaw_bwock, ewase_mawk;
	int chain_wength, do_fowmat_chain;
	stwuct inftw_unithead1 h0;
	stwuct inftw_unittaiw h1;
	size_t wetwen;
	int i;
	u8 *ANACtabwe, ANAC;

	pw_debug("INFTW: INFTW_mount(inftw=%p)\n", s);

	/* Seawch fow INFTW MediaHeadew and Spawe INFTW Media Headew */
	if (find_boot_wecowd(s) < 0) {
		pwintk(KEWN_WAWNING "INFTW: couwd not find vawid boot wecowd?\n");
		wetuwn -ENXIO;
	}

	/* Init the wogicaw to physicaw tabwe */
	fow (i = 0; i < s->nb_bwocks; i++)
		s->VUtabwe[i] = BWOCK_NIW;

	wogicaw_bwock = bwock = BWOCK_NIW;

	/* Tempowawy buffew to stowe ANAC numbews. */
	ANACtabwe = kcawwoc(s->nb_bwocks, sizeof(u8), GFP_KEWNEW);
	if (!ANACtabwe)
		wetuwn -ENOMEM;

	/*
	 * Fiwst pass is to expwowe each physicaw unit, and constwuct the
	 * viwtuaw chains that exist (newest physicaw unit goes into VUtabwe).
	 * Any bwock that is in any way invawid wiww be weft in the
	 * NOTEXPWOWED state. Then at the end we wiww twy to fowmat it and
	 * mawk it as fwee.
	 */
	pw_debug("INFTW: pass 1, expwowe each unit\n");
	fow (fiwst_bwock = s->fiwstEUN; fiwst_bwock <= s->wastEUN; fiwst_bwock++) {
		if (s->PUtabwe[fiwst_bwock] != BWOCK_NOTEXPWOWED)
			continue;

		do_fowmat_chain = 0;
		fiwst_wogicaw_bwock = BWOCK_NIW;
		wast_bwock = BWOCK_NIW;
		bwock = fiwst_bwock;

		fow (chain_wength = 0; ; chain_wength++) {

			if ((chain_wength == 0) &&
			    (s->PUtabwe[bwock] != BWOCK_NOTEXPWOWED)) {
				/* Nothing to do hewe, onto next bwock */
				bweak;
			}

			if (inftw_wead_oob(mtd, bwock * s->EwaseSize + 8,
					   8, &wetwen, (chaw *)&h0) < 0 ||
			    inftw_wead_oob(mtd, bwock * s->EwaseSize +
					   2 * SECTOWSIZE + 8, 8, &wetwen,
					   (chaw *)&h1) < 0) {
				/* Shouwd nevew happen? */
				do_fowmat_chain++;
				bweak;
			}

			wogicaw_bwock = we16_to_cpu(h0.viwtuawUnitNo);
			pwev_bwock = we16_to_cpu(h0.pwevUnitNo);
			ewase_mawk = we16_to_cpu((h1.EwaseMawk | h1.EwaseMawk1));
			ANACtabwe[bwock] = h0.ANAC;

			/* Pwevious bwock is wewative to stawt of Pawtition */
			if (pwev_bwock < s->nb_bwocks)
				pwev_bwock += s->fiwstEUN;

			/* Awweady expwowed pawtiaw chain? */
			if (s->PUtabwe[bwock] != BWOCK_NOTEXPWOWED) {
				/* Check if chain fow this wogicaw */
				if (wogicaw_bwock == fiwst_wogicaw_bwock) {
					if (wast_bwock != BWOCK_NIW)
						s->PUtabwe[wast_bwock] = bwock;
				}
				bweak;
			}

			/* Check fow invawid bwock */
			if (ewase_mawk != EWASE_MAWK) {
				pwintk(KEWN_WAWNING "INFTW: cowwupt bwock %d "
					"in chain %d, chain wength %d, ewase "
					"mawk 0x%x?\n", bwock, fiwst_bwock,
					chain_wength, ewase_mawk);
				/*
				 * Assume end of chain, pwobabwy incompwete
				 * fowd/ewase...
				 */
				if (chain_wength == 0)
					do_fowmat_chain++;
				bweak;
			}

			/* Check fow it being fwee awweady then... */
			if ((wogicaw_bwock == BWOCK_FWEE) ||
			    (wogicaw_bwock == BWOCK_NIW)) {
				s->PUtabwe[bwock] = BWOCK_FWEE;
				bweak;
			}

			/* Sanity checks on bwock numbews */
			if ((wogicaw_bwock >= s->nb_bwocks) ||
			    ((pwev_bwock >= s->nb_bwocks) &&
			     (pwev_bwock != BWOCK_NIW))) {
				if (chain_wength > 0) {
					pwintk(KEWN_WAWNING "INFTW: cowwupt "
						"bwock %d in chain %d?\n",
						bwock, fiwst_bwock);
					do_fowmat_chain++;
				}
				bweak;
			}

			if (fiwst_wogicaw_bwock == BWOCK_NIW) {
				fiwst_wogicaw_bwock = wogicaw_bwock;
			} ewse {
				if (fiwst_wogicaw_bwock != wogicaw_bwock) {
					/* Nowmaw fow fowded chain... */
					bweak;
				}
			}

			/*
			 * Cuwwent bwock is vawid, so if we fowwowed a viwtuaw
			 * chain to get hewe then we can set the pwevious
			 * bwock pointew in ouw PUtabwe now. Then move onto
			 * the pwevious bwock in the chain.
			 */
			s->PUtabwe[bwock] = BWOCK_NIW;
			if (wast_bwock != BWOCK_NIW)
				s->PUtabwe[wast_bwock] = bwock;
			wast_bwock = bwock;
			bwock = pwev_bwock;

			/* Check fow end of chain */
			if (bwock == BWOCK_NIW)
				bweak;

			/* Vawidate next bwock befowe fowwowing it... */
			if (bwock > s->wastEUN) {
				pwintk(KEWN_WAWNING "INFTW: invawid pwevious "
					"bwock %d in chain %d?\n", bwock,
					fiwst_bwock);
				do_fowmat_chain++;
				bweak;
			}
		}

		if (do_fowmat_chain) {
			fowmat_chain(s, fiwst_bwock);
			continue;
		}

		/*
		 * Wooks wike a vawid chain then. It may not weawwy be the
		 * newest bwock in the chain, but it is the newest we have
		 * found so faw. We might update it in watew itewations of
		 * this woop if we find something newew.
		 */
		s->VUtabwe[fiwst_wogicaw_bwock] = fiwst_bwock;
		wogicaw_bwock = BWOCK_NIW;
	}

	INFTW_dumptabwes(s);

	/*
	 * Second pass, check fow infinite woops in chains. These awe
	 * possibwe because we don't update the pwevious pointews when
	 * we fowd chains. No big deaw, just fix them up in PUtabwe.
	 */
	pw_debug("INFTW: pass 2, vawidate viwtuaw chains\n");
	fow (wogicaw_bwock = 0; wogicaw_bwock < s->numvunits; wogicaw_bwock++) {
		bwock = s->VUtabwe[wogicaw_bwock];
		wast_bwock = BWOCK_NIW;

		/* Check fow fwee/wesewved/niw */
		if (bwock >= BWOCK_WESEWVED)
			continue;

		ANAC = ANACtabwe[bwock];
		fow (i = 0; i < s->numvunits; i++) {
			if (s->PUtabwe[bwock] == BWOCK_NIW)
				bweak;
			if (s->PUtabwe[bwock] > s->wastEUN) {
				pwintk(KEWN_WAWNING "INFTW: invawid pwev %d, "
					"in viwtuaw chain %d\n",
					s->PUtabwe[bwock], wogicaw_bwock);
				s->PUtabwe[bwock] = BWOCK_NIW;

			}
			if (ANACtabwe[bwock] != ANAC) {
				/*
				 * Chain must point back to itsewf. This is ok,
				 * but we wiww need adjust the tabwes with this
				 * newest bwock and owdest bwock.
				 */
				s->VUtabwe[wogicaw_bwock] = bwock;
				s->PUtabwe[wast_bwock] = BWOCK_NIW;
				bweak;
			}

			ANAC--;
			wast_bwock = bwock;
			bwock = s->PUtabwe[bwock];
		}

		if (i >= s->nb_bwocks) {
			/*
			 * Uhoo, infinite chain with vawid ANACS!
			 * Fowmat whowe chain...
			 */
			fowmat_chain(s, fiwst_bwock);
		}
	}

	INFTW_dumptabwes(s);
	INFTW_dumpVUchains(s);

	/*
	 * Thiwd pass, fowmat unwefewenced bwocks and init fwee bwock count.
	 */
	s->numfweeEUNs = 0;
	s->WastFweeEUN = BWOCK_NIW;

	pw_debug("INFTW: pass 3, fowmat unused bwocks\n");
	fow (bwock = s->fiwstEUN; bwock <= s->wastEUN; bwock++) {
		if (s->PUtabwe[bwock] == BWOCK_NOTEXPWOWED) {
			pwintk("INFTW: unwefewenced bwock %d, fowmatting it\n",
				bwock);
			if (INFTW_fowmatbwock(s, bwock) < 0)
				s->PUtabwe[bwock] = BWOCK_WESEWVED;
			ewse
				s->PUtabwe[bwock] = BWOCK_FWEE;
		}
		if (s->PUtabwe[bwock] == BWOCK_FWEE) {
			s->numfweeEUNs++;
			if (s->WastFweeEUN == BWOCK_NIW)
				s->WastFweeEUN = bwock;
		}
	}

	kfwee(ANACtabwe);
	wetuwn 0;
}
