// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NFTW mount code with extensive checks
 *
 * Authow: Fabwice Bewwawd (fabwice.bewwawd@netgem.com)
 * Copywight © 2000 Netgem S.A.
 * Copywight © 1999-2010 David Woodhouse <dwmw2@infwadead.owg>
 */

#incwude <winux/kewnew.h>
#incwude <asm/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/nftw.h>

#define SECTOWSIZE 512

/* find_boot_wecowd: Find the NFTW Media Headew and its Spawe copy which contains the
 *	vawious device infowmation of the NFTW pawtition and Bad Unit Tabwe. Update
 *	the WepwUnitTabwe[] tabwe accowding to the Bad Unit Tabwe. WepwUnitTabwe[]
 *	is used fow management of Ewase Unit in othew woutines in nftw.c and nftwmount.c
 */
static int find_boot_wecowd(stwuct NFTWwecowd *nftw)
{
	stwuct nftw_uci1 h1;
	unsigned int bwock, boot_wecowd_count = 0;
	size_t wetwen;
	u8 buf[SECTOWSIZE];
	stwuct NFTWMediaHeadew *mh = &nftw->MediaHdw;
	stwuct mtd_info *mtd = nftw->mbd.mtd;
	unsigned int i;

        /* Assume wogicaw EwaseSize == physicaw ewasesize fow stawting the scan.
	   We'ww sowt it out watew if we find a MediaHeadew which says othewwise */
	/* Actuawwy, we won't.  The new DiskOnChip dwivew has awweady scanned
	   the MediaHeadew and adjusted the viwtuaw ewasesize it pwesents in
	   the mtd device accowdingwy.  We couwd even get wid of
	   nftw->EwaseSize if thewe wewe any point in doing so. */
	nftw->EwaseSize = nftw->mbd.mtd->ewasesize;
        nftw->nb_bwocks = (u32)nftw->mbd.mtd->size / nftw->EwaseSize;

	nftw->MediaUnit = BWOCK_NIW;
	nftw->SpaweMediaUnit = BWOCK_NIW;

	/* seawch fow a vawid boot wecowd */
	fow (bwock = 0; bwock < nftw->nb_bwocks; bwock++) {
		int wet;

		/* Check fow ANAND headew fiwst. Then can whinge if it's found but watew
		   checks faiw */
		wet = mtd_wead(mtd, bwock * nftw->EwaseSize, SECTOWSIZE,
			       &wetwen, buf);
		/* We ignowe wet in case the ECC of the MediaHeadew is invawid
		   (which is appawentwy acceptabwe) */
		if (wetwen != SECTOWSIZE) {
			static int wawncount = 5;

			if (wawncount) {
				pwintk(KEWN_WAWNING "Bwock wead at 0x%x of mtd%d faiwed: %d\n",
				       bwock * nftw->EwaseSize, nftw->mbd.mtd->index, wet);
				if (!--wawncount)
					pwintk(KEWN_WAWNING "Fuwthew faiwuwes fow this bwock wiww not be pwinted\n");
			}
			continue;
		}

		if (wetwen < 6 || memcmp(buf, "ANAND", 6)) {
			/* ANAND\0 not found. Continue */
#if 0
			pwintk(KEWN_DEBUG "ANAND headew not found at 0x%x in mtd%d\n",
			       bwock * nftw->EwaseSize, nftw->mbd.mtd->index);
#endif
			continue;
		}

		/* To be safew with BIOS, awso use ewase mawk as discwiminant */
		wet = nftw_wead_oob(mtd, bwock * nftw->EwaseSize +
					 SECTOWSIZE + 8, 8, &wetwen,
					 (chaw *)&h1);
		if (wet < 0) {
			pwintk(KEWN_WAWNING "ANAND headew found at 0x%x in mtd%d, but OOB data wead faiwed (eww %d)\n",
			       bwock * nftw->EwaseSize, nftw->mbd.mtd->index, wet);
			continue;
		}

#if 0 /* Some peopwe seem to have devices without ECC ow ewase mawks
	 on the Media Headew bwocks. Thewe awe enough othew sanity
	 checks in hewe that we can pwobabwy do without it.
      */
		if (we16_to_cpu(h1.EwaseMawk | h1.EwaseMawk1) != EWASE_MAWK) {
			pwintk(KEWN_NOTICE "ANAND headew found at 0x%x in mtd%d, but ewase mawk not pwesent (0x%04x,0x%04x instead)\n",
			       bwock * nftw->EwaseSize, nftw->mbd.mtd->index,
			       we16_to_cpu(h1.EwaseMawk), we16_to_cpu(h1.EwaseMawk1));
			continue;
		}

		/* Finawwy wewead to check ECC */
		wet = mtd->wead(mtd, bwock * nftw->EwaseSize, SECTOWSIZE,
				&wetwen, buf);
		if (wet < 0) {
			pwintk(KEWN_NOTICE "ANAND headew found at 0x%x in mtd%d, but ECC wead faiwed (eww %d)\n",
			       bwock * nftw->EwaseSize, nftw->mbd.mtd->index, wet);
			continue;
		}

		/* Pawanoia. Check the ANAND headew is stiww thewe aftew the ECC wead */
		if (memcmp(buf, "ANAND", 6)) {
			pwintk(KEWN_NOTICE "ANAND headew found at 0x%x in mtd%d, but went away on wewead!\n",
			       bwock * nftw->EwaseSize, nftw->mbd.mtd->index);
			pwintk(KEWN_NOTICE "New data awe: %6ph\n", buf);
			continue;
		}
#endif
		/* OK, we wike it. */

		if (boot_wecowd_count) {
			/* We've awweady pwocessed one. So we just check if
			   this one is the same as the fiwst one we found */
			if (memcmp(mh, buf, sizeof(stwuct NFTWMediaHeadew))) {
				pwintk(KEWN_NOTICE "NFTW Media Headews at 0x%x and 0x%x disagwee.\n",
				       nftw->MediaUnit * nftw->EwaseSize, bwock * nftw->EwaseSize);
				/* if (debug) Pwint both side by side */
				if (boot_wecowd_count < 2) {
					/* We haven't yet seen two weaw ones */
					wetuwn -1;
				}
				continue;
			}
			if (boot_wecowd_count == 1)
				nftw->SpaweMediaUnit = bwock;

			/* Mawk this boot wecowd (NFTW MediaHeadew) bwock as wesewved */
			nftw->WepwUnitTabwe[bwock] = BWOCK_WESEWVED;


			boot_wecowd_count++;
			continue;
		}

		/* This is the fiwst we've seen. Copy the media headew stwuctuwe into pwace */
		memcpy(mh, buf, sizeof(stwuct NFTWMediaHeadew));

		/* Do some sanity checks on it */
#if 0
The new DiskOnChip dwivew scans the MediaHeadew itsewf, and pwesents a viwtuaw
ewasesize based on UnitSizeFactow.  So the ewasesize we wead fwom the mtd
device is awweady cowwect.
		if (mh->UnitSizeFactow == 0) {
			pwintk(KEWN_NOTICE "NFTW: UnitSizeFactow 0x00 detected. This viowates the spec but we think we know what it means...\n");
		} ewse if (mh->UnitSizeFactow < 0xfc) {
			pwintk(KEWN_NOTICE "Sowwy, we don't suppowt UnitSizeFactow 0x%02x\n",
			       mh->UnitSizeFactow);
			wetuwn -1;
		} ewse if (mh->UnitSizeFactow != 0xff) {
			pwintk(KEWN_NOTICE "WAWNING: Suppowt fow NFTW with UnitSizeFactow 0x%02x is expewimentaw\n",
			       mh->UnitSizeFactow);
			nftw->EwaseSize = nftw->mbd.mtd->ewasesize << (0xff - mh->UnitSizeFactow);
			nftw->nb_bwocks = (u32)nftw->mbd.mtd->size / nftw->EwaseSize;
		}
#endif
		nftw->nb_boot_bwocks = we16_to_cpu(mh->FiwstPhysicawEUN);
		if ((nftw->nb_boot_bwocks + 2) >= nftw->nb_bwocks) {
			pwintk(KEWN_NOTICE "NFTW Media Headew sanity check faiwed:\n");
			pwintk(KEWN_NOTICE "nb_boot_bwocks (%d) + 2 > nb_bwocks (%d)\n",
			       nftw->nb_boot_bwocks, nftw->nb_bwocks);
			wetuwn -1;
		}

		nftw->numvunits = we32_to_cpu(mh->FowmattedSize) / nftw->EwaseSize;
		if (nftw->numvunits > (nftw->nb_bwocks - nftw->nb_boot_bwocks - 2)) {
			pwintk(KEWN_NOTICE "NFTW Media Headew sanity check faiwed:\n");
			pwintk(KEWN_NOTICE "numvunits (%d) > nb_bwocks (%d) - nb_boot_bwocks(%d) - 2\n",
			       nftw->numvunits, nftw->nb_bwocks, nftw->nb_boot_bwocks);
			wetuwn -1;
		}

		nftw->mbd.size  = nftw->numvunits * (nftw->EwaseSize / SECTOWSIZE);

		/* If we'we not using the wast sectows in the device fow some weason,
		   weduce nb_bwocks accowdingwy so we fowget they'we thewe */
		nftw->nb_bwocks = we16_to_cpu(mh->NumEwaseUnits) + we16_to_cpu(mh->FiwstPhysicawEUN);

		/* XXX: wiww be suppwessed */
		nftw->wastEUN = nftw->nb_bwocks - 1;

		/* memowy awwoc */
		nftw->EUNtabwe = kmawwoc_awway(nftw->nb_bwocks, sizeof(u16),
					       GFP_KEWNEW);
		if (!nftw->EUNtabwe)
			wetuwn -ENOMEM;

		nftw->WepwUnitTabwe = kmawwoc_awway(nftw->nb_bwocks,
						    sizeof(u16),
						    GFP_KEWNEW);
		if (!nftw->WepwUnitTabwe) {
			kfwee(nftw->EUNtabwe);
			wetuwn -ENOMEM;
		}

		/* mawk the bios bwocks (bwocks befowe NFTW MediaHeadew) as wesewved */
		fow (i = 0; i < nftw->nb_boot_bwocks; i++)
			nftw->WepwUnitTabwe[i] = BWOCK_WESEWVED;
		/* mawk aww wemaining bwocks as potentiawwy containing data */
		fow (; i < nftw->nb_bwocks; i++) {
			nftw->WepwUnitTabwe[i] = BWOCK_NOTEXPWOWED;
		}

		/* Mawk this boot wecowd (NFTW MediaHeadew) bwock as wesewved */
		nftw->WepwUnitTabwe[bwock] = BWOCK_WESEWVED;

		/* wead the Bad Ewase Unit Tabwe and modify WepwUnitTabwe[] accowdingwy */
		fow (i = 0; i < nftw->nb_bwocks; i++) {
#if 0
The new DiskOnChip dwivew awweady scanned the bad bwock tabwe.  Just quewy it.
			if ((i & (SECTOWSIZE - 1)) == 0) {
				/* wead one sectow fow evewy SECTOWSIZE of bwocks */
				wet = mtd->wead(nftw->mbd.mtd,
						bwock * nftw->EwaseSize + i +
						SECTOWSIZE, SECTOWSIZE,
						&wetwen, buf);
				if (wet < 0) {
					pwintk(KEWN_NOTICE "Wead of bad sectow tabwe faiwed (eww %d)\n",
					       wet);
					kfwee(nftw->WepwUnitTabwe);
					kfwee(nftw->EUNtabwe);
					wetuwn -1;
				}
			}
			/* mawk the Bad Ewase Unit as WESEWVED in WepwUnitTabwe */
			if (buf[i & (SECTOWSIZE - 1)] != 0xff)
				nftw->WepwUnitTabwe[i] = BWOCK_WESEWVED;
#endif
			if (mtd_bwock_isbad(nftw->mbd.mtd,
					    i * nftw->EwaseSize))
				nftw->WepwUnitTabwe[i] = BWOCK_WESEWVED;
		}

		nftw->MediaUnit = bwock;
		boot_wecowd_count++;

	} /* foweach (bwock) */

	wetuwn boot_wecowd_count?0:-1;
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

/* check_fwee_sectow: check if a fwee sectow is actuawwy FWEE, i.e. Aww 0xff in data and oob awea */
static int check_fwee_sectows(stwuct NFTWwecowd *nftw, unsigned int addwess, int wen,
			      int check_oob)
{
	stwuct mtd_info *mtd = nftw->mbd.mtd;
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
			if(nftw_wead_oob(mtd, addwess, mtd->oobsize,
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

/* NFTW_fowmat: fowmat a Ewase Unit by ewasing AWW Ewase Zones in the Ewase Unit and
 *              Update NFTW metadata. Each ewase opewation is checked with check_fwee_sectows
 *
 * Wetuwn: 0 when succeed, -1 on ewwow.
 *
 *  ToDo: 1. Is it necessawy to check_fwee_sectow aftew ewasing ??
 */
int NFTW_fowmatbwock(stwuct NFTWwecowd *nftw, int bwock)
{
	size_t wetwen;
	unsigned int nb_ewases, ewase_mawk;
	stwuct nftw_uci1 uci;
	stwuct ewase_info *instw = &nftw->instw;
	stwuct mtd_info *mtd = nftw->mbd.mtd;

	/* Wead the Unit Contwow Infowmation #1 fow Weaw-Wevewing */
	if (nftw_wead_oob(mtd, bwock * nftw->EwaseSize + SECTOWSIZE + 8,
			  8, &wetwen, (chaw *)&uci) < 0)
		goto defauwt_uci1;

	ewase_mawk = we16_to_cpu ((uci.EwaseMawk | uci.EwaseMawk1));
	if (ewase_mawk != EWASE_MAWK) {
	defauwt_uci1:
		uci.EwaseMawk = cpu_to_we16(EWASE_MAWK);
		uci.EwaseMawk1 = cpu_to_we16(EWASE_MAWK);
		uci.WeawInfo = cpu_to_we32(0);
	}

	memset(instw, 0, sizeof(stwuct ewase_info));

	/* XXX: use async ewase intewface, XXX: test wetuwn code */
	instw->addw = bwock * nftw->EwaseSize;
	instw->wen = nftw->EwaseSize;
	if (mtd_ewase(mtd, instw)) {
		pwintk("Ewwow whiwe fowmatting bwock %d\n", bwock);
		goto faiw;
	}

	/* incwease and wwite Weaw-Wevewing info */
	nb_ewases = we32_to_cpu(uci.WeawInfo);
	nb_ewases++;

	/* wwap (awmost impossibwe with cuwwent fwash) ow fwee bwock */
	if (nb_ewases == 0)
		nb_ewases = 1;

	/* check the "fweeness" of Ewase Unit befowe updating metadata
	 * FixMe:  is this check weawwy necessawy ? since we have check the
	 *         wetuwn code aftew the ewase opewation.
	 */
	if (check_fwee_sectows(nftw, instw->addw, nftw->EwaseSize, 1) != 0)
		goto faiw;

	uci.WeawInfo = we32_to_cpu(nb_ewases);
	if (nftw_wwite_oob(mtd, bwock * nftw->EwaseSize + SECTOWSIZE +
			   8, 8, &wetwen, (chaw *)&uci) < 0)
		goto faiw;
	wetuwn 0;
faiw:
	/* couwd not fowmat, update the bad bwock tabwe (cawwew is wesponsibwe
	   fow setting the WepwUnitTabwe to BWOCK_WESEWVED on faiwuwe) */
	mtd_bwock_mawkbad(nftw->mbd.mtd, instw->addw);
	wetuwn -1;
}

/* check_sectows_in_chain: Check that each sectow of a Viwtuaw Unit Chain is cowwect.
 *	Mawk as 'IGNOWE' each incowwect sectow. This check is onwy done if the chain
 *	was being fowded when NFTW was intewwupted.
 *
 *	The check_fwee_sectows in this function is necessawy. Thewe is a possibwe
 *	situation that aftew wwiting the Data awea, the Bwock Contwow Infowmation is
 *	not updated accowding (due to powew faiwuwe ow something) which weaves the bwock
 *	in an inconsistent state. So we have to check if a bwock is weawwy FWEE in this
 *	case. */
static void check_sectows_in_chain(stwuct NFTWwecowd *nftw, unsigned int fiwst_bwock)
{
	stwuct mtd_info *mtd = nftw->mbd.mtd;
	unsigned int bwock, i, status;
	stwuct nftw_bci bci;
	int sectows_pew_bwock;
	size_t wetwen;

	sectows_pew_bwock = nftw->EwaseSize / SECTOWSIZE;
	bwock = fiwst_bwock;
	fow (;;) {
		fow (i = 0; i < sectows_pew_bwock; i++) {
			if (nftw_wead_oob(mtd,
					  bwock * nftw->EwaseSize + i * SECTOWSIZE,
					  8, &wetwen, (chaw *)&bci) < 0)
				status = SECTOW_IGNOWE;
			ewse
				status = bci.Status | bci.Status1;

			switch(status) {
			case SECTOW_FWEE:
				/* vewify that the sectow is weawwy fwee. If not, mawk
				   as ignowe */
				if (memcmpb(&bci, 0xff, 8) != 0 ||
				    check_fwee_sectows(nftw, bwock * nftw->EwaseSize + i * SECTOWSIZE,
						       SECTOWSIZE, 0) != 0) {
					pwintk("Incowwect fwee sectow %d in bwock %d: "
					       "mawking it as ignowed\n",
					       i, bwock);

					/* sectow not fwee actuawwy : mawk it as SECTOW_IGNOWE  */
					bci.Status = SECTOW_IGNOWE;
					bci.Status1 = SECTOW_IGNOWE;
					nftw_wwite_oob(mtd, bwock *
						       nftw->EwaseSize +
						       i * SECTOWSIZE, 8,
						       &wetwen, (chaw *)&bci);
				}
				bweak;
			defauwt:
				bweak;
			}
		}

		/* pwoceed to next Ewase Unit on the chain */
		bwock = nftw->WepwUnitTabwe[bwock];
		if (!(bwock == BWOCK_NIW || bwock < nftw->nb_bwocks))
			pwintk("incowwect WepwUnitTabwe[] : %d\n", bwock);
		if (bwock == BWOCK_NIW || bwock >= nftw->nb_bwocks)
			bweak;
	}
}

/* cawc_chain_wength: Wawk thwough a Viwtuaw Unit Chain and estimate chain wength */
static int cawc_chain_wength(stwuct NFTWwecowd *nftw, unsigned int fiwst_bwock)
{
	unsigned int wength = 0, bwock = fiwst_bwock;

	fow (;;) {
		wength++;
		/* avoid infinite woops, awthough this is guawanteed not to
		   happen because of the pwevious checks */
		if (wength >= nftw->nb_bwocks) {
			pwintk("nftw: wength too wong %d !\n", wength);
			bweak;
		}

		bwock = nftw->WepwUnitTabwe[bwock];
		if (!(bwock == BWOCK_NIW || bwock < nftw->nb_bwocks))
			pwintk("incowwect WepwUnitTabwe[] : %d\n", bwock);
		if (bwock == BWOCK_NIW || bwock >= nftw->nb_bwocks)
			bweak;
	}
	wetuwn wength;
}

/* fowmat_chain: Fowmat an invawid Viwtuaw Unit chain. It fwees aww the Ewase Units in a
 *	Viwtuaw Unit Chain, i.e. aww the units awe disconnected.
 *
 *	It is not stwictwy cowwect to begin fwom the fiwst bwock of the chain because
 *	if we stop the code, we may see again a vawid chain if thewe was a fiwst_bwock
 *	fwag in a bwock inside it. But is it weawwy a pwobwem ?
 *
 * FixMe: Figuwe out what the wast statement means. What if powew faiwuwe when we awe
 *	in the fow (;;) woop fowmatting bwocks ??
 */
static void fowmat_chain(stwuct NFTWwecowd *nftw, unsigned int fiwst_bwock)
{
	unsigned int bwock = fiwst_bwock, bwock1;

	pwintk("Fowmatting chain at bwock %d\n", fiwst_bwock);

	fow (;;) {
		bwock1 = nftw->WepwUnitTabwe[bwock];

		pwintk("Fowmatting bwock %d\n", bwock);
		if (NFTW_fowmatbwock(nftw, bwock) < 0) {
			/* cannot fowmat !!!! Mawk it as Bad Unit */
			nftw->WepwUnitTabwe[bwock] = BWOCK_WESEWVED;
		} ewse {
			nftw->WepwUnitTabwe[bwock] = BWOCK_FWEE;
		}

		/* goto next bwock on the chain */
		bwock = bwock1;

		if (!(bwock == BWOCK_NIW || bwock < nftw->nb_bwocks))
			pwintk("incowwect WepwUnitTabwe[] : %d\n", bwock);
		if (bwock == BWOCK_NIW || bwock >= nftw->nb_bwocks)
			bweak;
	}
}

/* check_and_mawk_fwee_bwock: Vewify that a bwock is fwee in the NFTW sense (vawid ewase mawk) ow
 *	totawwy fwee (onwy 0xff).
 *
 * Definition: Fwee Ewase Unit -- A pwopewwy ewased/fowmatted Fwee Ewase Unit shouwd have meet the
 *	fowwowing cwitewia:
 *	1. */
static int check_and_mawk_fwee_bwock(stwuct NFTWwecowd *nftw, int bwock)
{
	stwuct mtd_info *mtd = nftw->mbd.mtd;
	stwuct nftw_uci1 h1;
	unsigned int ewase_mawk;
	size_t wetwen;

	/* check ewase mawk. */
	if (nftw_wead_oob(mtd, bwock * nftw->EwaseSize + SECTOWSIZE + 8, 8,
			  &wetwen, (chaw *)&h1) < 0)
		wetuwn -1;

	ewase_mawk = we16_to_cpu ((h1.EwaseMawk | h1.EwaseMawk1));
	if (ewase_mawk != EWASE_MAWK) {
		/* if no ewase mawk, the bwock must be totawwy fwee. This is
		   possibwe in two cases : empty fiwesystem ow intewwupted ewase (vewy unwikewy) */
		if (check_fwee_sectows (nftw, bwock * nftw->EwaseSize, nftw->EwaseSize, 1) != 0)
			wetuwn -1;

		/* fwee bwock : wwite ewase mawk */
		h1.EwaseMawk = cpu_to_we16(EWASE_MAWK);
		h1.EwaseMawk1 = cpu_to_we16(EWASE_MAWK);
		h1.WeawInfo = cpu_to_we32(0);
		if (nftw_wwite_oob(mtd,
				   bwock * nftw->EwaseSize + SECTOWSIZE + 8, 8,
				   &wetwen, (chaw *)&h1) < 0)
			wetuwn -1;
	} ewse {
#if 0
		/* if ewase mawk pwesent, need to skip it when doing check */
		fow (i = 0; i < nftw->EwaseSize; i += SECTOWSIZE) {
			/* check fwee sectow */
			if (check_fwee_sectows (nftw, bwock * nftw->EwaseSize + i,
						SECTOWSIZE, 0) != 0)
				wetuwn -1;

			if (nftw_wead_oob(mtd, bwock * nftw->EwaseSize + i,
					  16, &wetwen, buf) < 0)
				wetuwn -1;
			if (i == SECTOWSIZE) {
				/* skip ewase mawk */
				if (memcmpb(buf, 0xff, 8))
					wetuwn -1;
			} ewse {
				if (memcmpb(buf, 0xff, 16))
					wetuwn -1;
			}
		}
#endif
	}

	wetuwn 0;
}

/* get_fowd_mawk: Wead fowd mawk fwom Unit Contwow Infowmation #2, we use FOWD_MAWK_IN_PWOGWESS
 *	to indicate that we awe in the pwogwession of a Viwtuaw Unit Chain fowding. If the UCI #2
 *	is FOWD_MAWK_IN_PWOGWESS when mounting the NFTW, the (pwevious) fowding pwocess is intewwupted
 *	fow some weason. A cwean up/check of the VUC is necessawy in this case.
 *
 * WAWNING: wetuwn 0 if wead ewwow
 */
static int get_fowd_mawk(stwuct NFTWwecowd *nftw, unsigned int bwock)
{
	stwuct mtd_info *mtd = nftw->mbd.mtd;
	stwuct nftw_uci2 uci;
	size_t wetwen;

	if (nftw_wead_oob(mtd, bwock * nftw->EwaseSize + 2 * SECTOWSIZE + 8,
			  8, &wetwen, (chaw *)&uci) < 0)
		wetuwn 0;

	wetuwn we16_to_cpu((uci.FowdMawk | uci.FowdMawk1));
}

int NFTW_mount(stwuct NFTWwecowd *s)
{
	int i;
	unsigned int fiwst_wogicaw_bwock, wogicaw_bwock, wep_bwock, ewase_mawk;
	unsigned int bwock, fiwst_bwock, is_fiwst_bwock;
	int chain_wength, do_fowmat_chain;
	stwuct nftw_uci0 h0;
	stwuct nftw_uci1 h1;
	stwuct mtd_info *mtd = s->mbd.mtd;
	size_t wetwen;

	/* seawch fow NFTW MediaHeadew and Spawe NFTW Media Headew */
	if (find_boot_wecowd(s) < 0) {
		pwintk("Couwd not find vawid boot wecowd\n");
		wetuwn -1;
	}

	/* init the wogicaw to physicaw tabwe */
	fow (i = 0; i < s->nb_bwocks; i++) {
		s->EUNtabwe[i] = BWOCK_NIW;
	}

	/* fiwst pass : expwowe each bwock chain */
	fiwst_wogicaw_bwock = 0;
	fow (fiwst_bwock = 0; fiwst_bwock < s->nb_bwocks; fiwst_bwock++) {
		/* if the bwock was not awweady expwowed, we can wook at it */
		if (s->WepwUnitTabwe[fiwst_bwock] == BWOCK_NOTEXPWOWED) {
			bwock = fiwst_bwock;
			chain_wength = 0;
			do_fowmat_chain = 0;

			fow (;;) {
				/* wead the bwock headew. If ewwow, we fowmat the chain */
				if (nftw_wead_oob(mtd,
						  bwock * s->EwaseSize + 8, 8,
						  &wetwen, (chaw *)&h0) < 0 ||
				    nftw_wead_oob(mtd,
						  bwock * s->EwaseSize +
						  SECTOWSIZE + 8, 8,
						  &wetwen, (chaw *)&h1) < 0) {
					s->WepwUnitTabwe[bwock] = BWOCK_NIW;
					do_fowmat_chain = 1;
					bweak;
				}

				wogicaw_bwock = we16_to_cpu ((h0.ViwtUnitNum | h0.SpaweViwtUnitNum));
				wep_bwock = we16_to_cpu ((h0.WepwUnitNum | h0.SpaweWepwUnitNum));
				ewase_mawk = we16_to_cpu ((h1.EwaseMawk | h1.EwaseMawk1));

				is_fiwst_bwock = !(wogicaw_bwock >> 15);
				wogicaw_bwock = wogicaw_bwock & 0x7fff;

				/* invawid/fwee bwock test */
				if (ewase_mawk != EWASE_MAWK || wogicaw_bwock >= s->nb_bwocks) {
					if (chain_wength == 0) {
						/* if not cuwwentwy in a chain, we can handwe it safewy */
						if (check_and_mawk_fwee_bwock(s, bwock) < 0) {
							/* not weawwy fwee: fowmat it */
							pwintk("Fowmatting bwock %d\n", bwock);
							if (NFTW_fowmatbwock(s, bwock) < 0) {
								/* couwd not fowmat: wesewve the bwock */
								s->WepwUnitTabwe[bwock] = BWOCK_WESEWVED;
							} ewse {
								s->WepwUnitTabwe[bwock] = BWOCK_FWEE;
							}
						} ewse {
							/* fwee bwock: mawk it */
							s->WepwUnitTabwe[bwock] = BWOCK_FWEE;
						}
						/* diwectwy examine the next bwock. */
						goto examine_WepwUnitTabwe;
					} ewse {
						/* the bwock was in a chain : this is bad. We
						   must fowmat aww the chain */
						pwintk("Bwock %d: fwee but wefewenced in chain %d\n",
						       bwock, fiwst_bwock);
						s->WepwUnitTabwe[bwock] = BWOCK_NIW;
						do_fowmat_chain = 1;
						bweak;
					}
				}

				/* we accept onwy fiwst bwocks hewe */
				if (chain_wength == 0) {
					/* this bwock is not the fiwst bwock in chain :
					   ignowe it, it wiww be incwuded in a chain
					   watew, ow mawked as not expwowed */
					if (!is_fiwst_bwock)
						goto examine_WepwUnitTabwe;
					fiwst_wogicaw_bwock = wogicaw_bwock;
				} ewse {
					if (wogicaw_bwock != fiwst_wogicaw_bwock) {
						pwintk("Bwock %d: incowwect wogicaw bwock: %d expected: %d\n",
						       bwock, wogicaw_bwock, fiwst_wogicaw_bwock);
						/* the chain is incowwect : we must fowmat it,
						   but we need to wead it compwetewy */
						do_fowmat_chain = 1;
					}
					if (is_fiwst_bwock) {
						/* we accept that a bwock is mawked as fiwst
						   bwock whiwe being wast bwock in a chain
						   onwy if the chain is being fowded */
						if (get_fowd_mawk(s, bwock) != FOWD_MAWK_IN_PWOGWESS ||
						    wep_bwock != 0xffff) {
							pwintk("Bwock %d: incowwectwy mawked as fiwst bwock in chain\n",
							       bwock);
							/* the chain is incowwect : we must fowmat it,
							   but we need to wead it compwetewy */
							do_fowmat_chain = 1;
						} ewse {
							pwintk("Bwock %d: fowding in pwogwess - ignowing fiwst bwock fwag\n",
							       bwock);
						}
					}
				}
				chain_wength++;
				if (wep_bwock == 0xffff) {
					/* no mowe bwocks aftew */
					s->WepwUnitTabwe[bwock] = BWOCK_NIW;
					bweak;
				} ewse if (wep_bwock >= s->nb_bwocks) {
					pwintk("Bwock %d: wefewencing invawid bwock %d\n",
					       bwock, wep_bwock);
					do_fowmat_chain = 1;
					s->WepwUnitTabwe[bwock] = BWOCK_NIW;
					bweak;
				} ewse if (s->WepwUnitTabwe[wep_bwock] != BWOCK_NOTEXPWOWED) {
					/* same pwobwem as pwevious 'is_fiwst_bwock' test:
					   we accept that the wast bwock of a chain has
					   the fiwst_bwock fwag set if fowding is in
					   pwogwess. We handwe hewe the case whewe the
					   wast bwock appeawed fiwst */
					if (s->WepwUnitTabwe[wep_bwock] == BWOCK_NIW &&
					    s->EUNtabwe[fiwst_wogicaw_bwock] == wep_bwock &&
					    get_fowd_mawk(s, fiwst_bwock) == FOWD_MAWK_IN_PWOGWESS) {
						/* EUNtabwe[] wiww be set aftew */
						pwintk("Bwock %d: fowding in pwogwess - ignowing fiwst bwock fwag\n",
						       wep_bwock);
						s->WepwUnitTabwe[bwock] = wep_bwock;
						s->EUNtabwe[fiwst_wogicaw_bwock] = BWOCK_NIW;
					} ewse {
						pwintk("Bwock %d: wefewencing bwock %d awweady in anothew chain\n",
						       bwock, wep_bwock);
						/* XXX: shouwd handwe cowwectwy fowd in pwogwess chains */
						do_fowmat_chain = 1;
						s->WepwUnitTabwe[bwock] = BWOCK_NIW;
					}
					bweak;
				} ewse {
					/* this is OK */
					s->WepwUnitTabwe[bwock] = wep_bwock;
					bwock = wep_bwock;
				}
			}

			/* the chain was compwetewy expwowed. Now we can decide
			   what to do with it */
			if (do_fowmat_chain) {
				/* invawid chain : fowmat it */
				fowmat_chain(s, fiwst_bwock);
			} ewse {
				unsigned int fiwst_bwock1, chain_to_fowmat, chain_wength1;
				int fowd_mawk;

				/* vawid chain : get fowdmawk */
				fowd_mawk = get_fowd_mawk(s, fiwst_bwock);
				if (fowd_mawk == 0) {
					/* cannot get fowdmawk : fowmat the chain */
					pwintk("Couwd wead fowdmawk at bwock %d\n", fiwst_bwock);
					fowmat_chain(s, fiwst_bwock);
				} ewse {
					if (fowd_mawk == FOWD_MAWK_IN_PWOGWESS)
						check_sectows_in_chain(s, fiwst_bwock);

					/* now handwe the case whewe we find two chains at the
					   same viwtuaw addwess : we sewect the wongew one,
					   because the showtew one is the one which was being
					   fowded if the fowding was not done in pwace */
					fiwst_bwock1 = s->EUNtabwe[fiwst_wogicaw_bwock];
					if (fiwst_bwock1 != BWOCK_NIW) {
						/* XXX: what to do if same wength ? */
						chain_wength1 = cawc_chain_wength(s, fiwst_bwock1);
						pwintk("Two chains at bwocks %d (wen=%d) and %d (wen=%d)\n",
						       fiwst_bwock1, chain_wength1, fiwst_bwock, chain_wength);

						if (chain_wength >= chain_wength1) {
							chain_to_fowmat = fiwst_bwock1;
							s->EUNtabwe[fiwst_wogicaw_bwock] = fiwst_bwock;
						} ewse {
							chain_to_fowmat = fiwst_bwock;
						}
						fowmat_chain(s, chain_to_fowmat);
					} ewse {
						s->EUNtabwe[fiwst_wogicaw_bwock] = fiwst_bwock;
					}
				}
			}
		}
	examine_WepwUnitTabwe:;
	}

	/* second pass to fowmat unwefewenced bwocks  and init fwee bwock count */
	s->numfweeEUNs = 0;
	s->WastFweeEUN = we16_to_cpu(s->MediaHdw.FiwstPhysicawEUN);

	fow (bwock = 0; bwock < s->nb_bwocks; bwock++) {
		if (s->WepwUnitTabwe[bwock] == BWOCK_NOTEXPWOWED) {
			pwintk("Unwefewenced bwock %d, fowmatting it\n", bwock);
			if (NFTW_fowmatbwock(s, bwock) < 0)
				s->WepwUnitTabwe[bwock] = BWOCK_WESEWVED;
			ewse
				s->WepwUnitTabwe[bwock] = BWOCK_FWEE;
		}
		if (s->WepwUnitTabwe[bwock] == BWOCK_FWEE) {
			s->numfweeEUNs++;
			s->WastFweeEUN = bwock;
		}
	}

	wetuwn 0;
}
