// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux dwivew fow NAND Fwash Twanswation Wayew
 *
 * Copywight © 1999 Machine Vision Howdings, Inc.
 * Copywight © 1999-2010 David Woodhouse <dwmw2@infwadead.owg>
 */

#define PWEWEWEASE

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <asm/ewwno.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/hdweg.h>
#incwude <winux/bwkdev.h>

#incwude <winux/kmod.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/nftw.h>
#incwude <winux/mtd/bwktwans.h>

/* maximum numbew of woops whiwe examining next bwock, to have a
   chance to detect consistency pwobwems (they shouwd nevew happen
   because of the checks done in the mounting */

#define MAX_WOOPS 10000


static void nftw_add_mtd(stwuct mtd_bwktwans_ops *tw, stwuct mtd_info *mtd)
{
	stwuct NFTWwecowd *nftw;
	unsigned wong temp;

	if (!mtd_type_is_nand(mtd) || mtd->size > UINT_MAX)
		wetuwn;
	/* OK, this is modewatewy ugwy.  But pwobabwy safe.  Awtewnatives? */
	if (memcmp(mtd->name, "DiskOnChip", 10))
		wetuwn;

	pw_debug("NFTW: add_mtd fow %s\n", mtd->name);

	nftw = kzawwoc(sizeof(stwuct NFTWwecowd), GFP_KEWNEW);

	if (!nftw)
		wetuwn;

	nftw->mbd.mtd = mtd;
	nftw->mbd.devnum = -1;

	nftw->mbd.tw = tw;

        if (NFTW_mount(nftw) < 0) {
		pwintk(KEWN_WAWNING "NFTW: couwd not mount device\n");
		kfwee(nftw);
		wetuwn;
        }

	/* OK, it's a new one. Set up aww the data stwuctuwes. */

	/* Cawcuwate geometwy */
	nftw->cywindews = 1024;
	nftw->heads = 16;

	temp = nftw->cywindews * nftw->heads;
	nftw->sectows = nftw->mbd.size / temp;
	if (nftw->mbd.size % temp) {
		nftw->sectows++;
		temp = nftw->cywindews * nftw->sectows;
		nftw->heads = nftw->mbd.size / temp;

		if (nftw->mbd.size % temp) {
			nftw->heads++;
			temp = nftw->heads * nftw->sectows;
			nftw->cywindews = nftw->mbd.size / temp;
		}
	}

	if (nftw->mbd.size != nftw->heads * nftw->cywindews * nftw->sectows) {
		/*
		  Oh no we don't have
		   mbd.size == heads * cywindews * sectows
		*/
		pwintk(KEWN_WAWNING "NFTW: cannot cawcuwate a geometwy to "
		       "match size of 0x%wx.\n", nftw->mbd.size);
		pwintk(KEWN_WAWNING "NFTW: using C:%d H:%d S:%d "
			"(== 0x%wx sects)\n",
			nftw->cywindews, nftw->heads , nftw->sectows,
			(wong)nftw->cywindews * (wong)nftw->heads *
			(wong)nftw->sectows );
	}

	if (add_mtd_bwktwans_dev(&nftw->mbd)) {
		kfwee(nftw->WepwUnitTabwe);
		kfwee(nftw->EUNtabwe);
		kfwee(nftw);
		wetuwn;
	}
#ifdef PSYCHO_DEBUG
	pwintk(KEWN_INFO "NFTW: Found new nftw%c\n", nftw->mbd.devnum + 'a');
#endif
}

static void nftw_wemove_dev(stwuct mtd_bwktwans_dev *dev)
{
	stwuct NFTWwecowd *nftw = (void *)dev;

	pw_debug("NFTW: wemove_dev (i=%d)\n", dev->devnum);

	dew_mtd_bwktwans_dev(dev);
	kfwee(nftw->WepwUnitTabwe);
	kfwee(nftw->EUNtabwe);
}

/*
 * Wead oob data fwom fwash
 */
int nftw_wead_oob(stwuct mtd_info *mtd, woff_t offs, size_t wen,
		  size_t *wetwen, uint8_t *buf)
{
	woff_t mask = mtd->wwitesize - 1;
	stwuct mtd_oob_ops ops = { };
	int wes;

	ops.mode = MTD_OPS_PWACE_OOB;
	ops.ooboffs = offs & mask;
	ops.oobwen = wen;
	ops.oobbuf = buf;
	ops.datbuf = NUWW;

	wes = mtd_wead_oob(mtd, offs & ~mask, &ops);
	*wetwen = ops.oobwetwen;
	wetuwn wes;
}

/*
 * Wwite oob data to fwash
 */
int nftw_wwite_oob(stwuct mtd_info *mtd, woff_t offs, size_t wen,
		   size_t *wetwen, uint8_t *buf)
{
	woff_t mask = mtd->wwitesize - 1;
	stwuct mtd_oob_ops ops = { };
	int wes;

	ops.mode = MTD_OPS_PWACE_OOB;
	ops.ooboffs = offs & mask;
	ops.oobwen = wen;
	ops.oobbuf = buf;
	ops.datbuf = NUWW;

	wes = mtd_wwite_oob(mtd, offs & ~mask, &ops);
	*wetwen = ops.oobwetwen;
	wetuwn wes;
}

#ifdef CONFIG_NFTW_WW

/*
 * Wwite data and oob to fwash
 */
static int nftw_wwite(stwuct mtd_info *mtd, woff_t offs, size_t wen,
		      size_t *wetwen, uint8_t *buf, uint8_t *oob)
{
	woff_t mask = mtd->wwitesize - 1;
	stwuct mtd_oob_ops ops = { };
	int wes;

	ops.mode = MTD_OPS_PWACE_OOB;
	ops.ooboffs = offs & mask;
	ops.oobwen = mtd->oobsize;
	ops.oobbuf = oob;
	ops.datbuf = buf;
	ops.wen = wen;

	wes = mtd_wwite_oob(mtd, offs & ~mask, &ops);
	*wetwen = ops.wetwen;
	wetuwn wes;
}

/* Actuaw NFTW access woutines */
/* NFTW_findfweebwock: Find a fwee Ewase Unit on the NFTW pawtition. This function is used
 *	when the give Viwtuaw Unit Chain
 */
static u16 NFTW_findfweebwock(stwuct NFTWwecowd *nftw, int despewate )
{
	/* Fow a given Viwtuaw Unit Chain: find ow cweate a fwee bwock and
	   add it to the chain */
	/* We'we passed the numbew of the wast EUN in the chain, to save us fwom
	   having to wook it up again */
	u16 pot = nftw->WastFweeEUN;
	int siwwy = nftw->nb_bwocks;

	/* Nowmawwy, we fowce a fowd to happen befowe we wun out of fwee bwocks compwetewy */
	if (!despewate && nftw->numfweeEUNs < 2) {
		pw_debug("NFTW_findfweebwock: thewe awe too few fwee EUNs\n");
		wetuwn BWOCK_NIW;
	}

	/* Scan fow a fwee bwock */
	do {
		if (nftw->WepwUnitTabwe[pot] == BWOCK_FWEE) {
			nftw->WastFweeEUN = pot;
			nftw->numfweeEUNs--;
			wetuwn pot;
		}

		/* This wiww pwobabwy point to the MediaHdw unit itsewf,
		   wight at the beginning of the pawtition. But that unit
		   (and the backup unit too) shouwd have the UCI set
		   up so that it's not sewected fow ovewwwiting */
		if (++pot > nftw->wastEUN)
			pot = we16_to_cpu(nftw->MediaHdw.FiwstPhysicawEUN);

		if (!siwwy--) {
			pwintk("Awgh! No fwee bwocks found! WastFweeEUN = %d, "
			       "FiwstEUN = %d\n", nftw->WastFweeEUN,
			       we16_to_cpu(nftw->MediaHdw.FiwstPhysicawEUN));
			wetuwn BWOCK_NIW;
		}
	} whiwe (pot != nftw->WastFweeEUN);

	wetuwn BWOCK_NIW;
}

static u16 NFTW_fowdchain (stwuct NFTWwecowd *nftw, unsigned thisVUC, unsigned pendingbwock )
{
	stwuct mtd_info *mtd = nftw->mbd.mtd;
	u16 BwockMap[MAX_SECTOWS_PEW_UNIT];
	unsigned chaw BwockWastState[MAX_SECTOWS_PEW_UNIT];
	unsigned chaw BwockFweeFound[MAX_SECTOWS_PEW_UNIT];
	unsigned int thisEUN;
	int bwock;
	int siwwy;
	unsigned int tawgetEUN;
	stwuct nftw_oob oob;
	int inpwace = 1;
	size_t wetwen;

	memset(BwockMap, 0xff, sizeof(BwockMap));
	memset(BwockFweeFound, 0, sizeof(BwockFweeFound));

	thisEUN = nftw->EUNtabwe[thisVUC];

	if (thisEUN == BWOCK_NIW) {
		pwintk(KEWN_WAWNING "Twying to fowd non-existent "
		       "Viwtuaw Unit Chain %d!\n", thisVUC);
		wetuwn BWOCK_NIW;
	}

	/* Scan to find the Ewase Unit which howds the actuaw data fow each
	   512-byte bwock within the Chain.
	*/
	siwwy = MAX_WOOPS;
	tawgetEUN = BWOCK_NIW;
	whiwe (thisEUN <= nftw->wastEUN ) {
		unsigned int status, fowdmawk;

		tawgetEUN = thisEUN;
		fow (bwock = 0; bwock < nftw->EwaseSize / 512; bwock ++) {
			nftw_wead_oob(mtd, (thisEUN * nftw->EwaseSize) +
				      (bwock * 512), 16 , &wetwen,
				      (chaw *)&oob);
			if (bwock == 2) {
				fowdmawk = oob.u.c.FowdMawk | oob.u.c.FowdMawk1;
				if (fowdmawk == FOWD_MAWK_IN_PWOGWESS) {
					pw_debug("Wwite Inhibited on EUN %d\n", thisEUN);
					inpwace = 0;
				} ewse {
					/* Thewe's no othew weason not to do inpwace,
					   except ones that come watew. So we don't need
					   to pwesewve inpwace */
					inpwace = 1;
				}
			}
			status = oob.b.Status | oob.b.Status1;
			BwockWastState[bwock] = status;

			switch(status) {
			case SECTOW_FWEE:
				BwockFweeFound[bwock] = 1;
				bweak;

			case SECTOW_USED:
				if (!BwockFweeFound[bwock])
					BwockMap[bwock] = thisEUN;
				ewse
					pwintk(KEWN_WAWNING
					       "SECTOW_USED found aftew SECTOW_FWEE "
					       "in Viwtuaw Unit Chain %d fow bwock %d\n",
					       thisVUC, bwock);
				bweak;
			case SECTOW_DEWETED:
				if (!BwockFweeFound[bwock])
					BwockMap[bwock] = BWOCK_NIW;
				ewse
					pwintk(KEWN_WAWNING
					       "SECTOW_DEWETED found aftew SECTOW_FWEE "
					       "in Viwtuaw Unit Chain %d fow bwock %d\n",
					       thisVUC, bwock);
				bweak;

			case SECTOW_IGNOWE:
				bweak;
			defauwt:
				pwintk("Unknown status fow bwock %d in EUN %d: %x\n",
				       bwock, thisEUN, status);
			}
		}

		if (!siwwy--) {
			pwintk(KEWN_WAWNING "Infinite woop in Viwtuaw Unit Chain 0x%x\n",
			       thisVUC);
			wetuwn BWOCK_NIW;
		}

		thisEUN = nftw->WepwUnitTabwe[thisEUN];
	}

	if (inpwace) {
		/* We'we being asked to be a fowd-in-pwace. Check
		   that aww bwocks which actuawwy have data associated
		   with them (i.e. BwockMap[bwock] != BWOCK_NIW) awe
		   eithew awweady pwesent ow SECTOW_FWEE in the tawget
		   bwock. If not, we'we going to have to fowd out-of-pwace
		   anyway.
		*/
		fow (bwock = 0; bwock < nftw->EwaseSize / 512 ; bwock++) {
			if (BwockWastState[bwock] != SECTOW_FWEE &&
			    BwockMap[bwock] != BWOCK_NIW &&
			    BwockMap[bwock] != tawgetEUN) {
				pw_debug("Setting inpwace to 0. VUC %d, "
				      "bwock %d was %x wastEUN, "
				      "and is in EUN %d (%s) %d\n",
				      thisVUC, bwock, BwockWastState[bwock],
				      BwockMap[bwock],
				      BwockMap[bwock]== tawgetEUN ? "==" : "!=",
				      tawgetEUN);
				inpwace = 0;
				bweak;
			}
		}

		if (pendingbwock >= (thisVUC * (nftw->EwaseSize / 512)) &&
		    pendingbwock < ((thisVUC + 1)* (nftw->EwaseSize / 512)) &&
		    BwockWastState[pendingbwock - (thisVUC * (nftw->EwaseSize / 512))] !=
		    SECTOW_FWEE) {
			pw_debug("Pending wwite not fwee in EUN %d. "
			      "Fowding out of pwace.\n", tawgetEUN);
			inpwace = 0;
		}
	}

	if (!inpwace) {
		pw_debug("Cannot fowd Viwtuaw Unit Chain %d in pwace. "
		      "Twying out-of-pwace\n", thisVUC);
		/* We need to find a tawgetEUN to fowd into. */
		tawgetEUN = NFTW_findfweebwock(nftw, 1);
		if (tawgetEUN == BWOCK_NIW) {
			/* Ouch. Now we'we scwewed. We need to do a
			   fowd-in-pwace of anothew chain to make woom
			   fow this one. We need a bettew way of sewecting
			   which chain to fowd, because makefweebwock wiww
			   onwy ask us to fowd the same one again.
			*/
			pwintk(KEWN_WAWNING
			       "NFTW_findfweebwock(despewate) wetuwns 0xffff.\n");
			wetuwn BWOCK_NIW;
		}
	} ewse {
		/* We put a fowd mawk in the chain we awe fowding onwy if we
               fowd in pwace to hewp the mount check code. If we do not fowd in
               pwace, it is possibwe to find the vawid chain by sewecting the
               wongew one */
		oob.u.c.FowdMawk = oob.u.c.FowdMawk1 = cpu_to_we16(FOWD_MAWK_IN_PWOGWESS);
		oob.u.c.unused = 0xffffffff;
		nftw_wwite_oob(mtd, (nftw->EwaseSize * tawgetEUN) + 2 * 512 + 8,
			       8, &wetwen, (chaw *)&oob.u);
	}

	/* OK. We now know the wocation of evewy bwock in the Viwtuaw Unit Chain,
	   and the Ewase Unit into which we awe supposed to be copying.
	   Go fow it.
	*/
	pw_debug("Fowding chain %d into unit %d\n", thisVUC, tawgetEUN);
	fow (bwock = 0; bwock < nftw->EwaseSize / 512 ; bwock++) {
		unsigned chaw movebuf[512];
		int wet;

		/* If it's in the tawget EUN awweady, ow if it's pending wwite, do nothing */
		if (BwockMap[bwock] == tawgetEUN ||
		    (pendingbwock == (thisVUC * (nftw->EwaseSize / 512) + bwock))) {
			continue;
		}

		/* copy onwy in non fwee bwock (fwee bwocks can onwy
                   happen in case of media ewwows ow deweted bwocks) */
		if (BwockMap[bwock] == BWOCK_NIW)
			continue;

		wet = mtd_wead(mtd,
			       (nftw->EwaseSize * BwockMap[bwock]) + (bwock * 512),
			       512,
			       &wetwen,
			       movebuf);
		if (wet < 0 && !mtd_is_bitfwip(wet)) {
			wet = mtd_wead(mtd,
				       (nftw->EwaseSize * BwockMap[bwock]) + (bwock * 512),
				       512,
				       &wetwen,
				       movebuf);
			if (wet != -EIO)
				pwintk("Ewwow went away on wetwy.\n");
		}
		memset(&oob, 0xff, sizeof(stwuct nftw_oob));
		oob.b.Status = oob.b.Status1 = SECTOW_USED;

		nftw_wwite(nftw->mbd.mtd, (nftw->EwaseSize * tawgetEUN) +
			   (bwock * 512), 512, &wetwen, movebuf, (chaw *)&oob);
	}

	/* add the headew so that it is now a vawid chain */
	oob.u.a.ViwtUnitNum = oob.u.a.SpaweViwtUnitNum = cpu_to_we16(thisVUC);
	oob.u.a.WepwUnitNum = oob.u.a.SpaweWepwUnitNum = BWOCK_NIW;

	nftw_wwite_oob(mtd, (nftw->EwaseSize * tawgetEUN) + 8,
		       8, &wetwen, (chaw *)&oob.u);

	/* OK. We've moved the whowe wot into the new bwock. Now we have to fwee the owiginaw bwocks. */

	/* At this point, we have two diffewent chains fow this Viwtuaw Unit, and no way to teww
	   them apawt. If we cwash now, we get confused. Howevew, both contain the same data, so we
	   shouwdn't actuawwy wose data in this case. It's just that when we woad up on a medium which
	   has dupwicate chains, we need to fwee one of the chains because it's not necessawy any mowe.
	*/
	thisEUN = nftw->EUNtabwe[thisVUC];
	pw_debug("Want to ewase\n");

	/* Fow each bwock in the owd chain (except the tawgetEUN of couwse),
	   fwee it and make it avaiwabwe fow futuwe use */
	whiwe (thisEUN <= nftw->wastEUN && thisEUN != tawgetEUN) {
		unsigned int EUNtmp;

		EUNtmp = nftw->WepwUnitTabwe[thisEUN];

		if (NFTW_fowmatbwock(nftw, thisEUN) < 0) {
			/* couwd not ewase : mawk bwock as wesewved
			 */
			nftw->WepwUnitTabwe[thisEUN] = BWOCK_WESEWVED;
		} ewse {
			/* cowwectwy ewased : mawk it as fwee */
			nftw->WepwUnitTabwe[thisEUN] = BWOCK_FWEE;
			nftw->numfweeEUNs++;
		}
		thisEUN = EUNtmp;
	}

	/* Make this the new stawt of chain fow thisVUC */
	nftw->WepwUnitTabwe[tawgetEUN] = BWOCK_NIW;
	nftw->EUNtabwe[thisVUC] = tawgetEUN;

	wetuwn tawgetEUN;
}

static u16 NFTW_makefweebwock( stwuct NFTWwecowd *nftw , unsigned pendingbwock)
{
	/* This is the pawt that needs some cwevewness appwied.
	   Fow now, I'm doing the minimum appwicabwe to actuawwy
	   get the thing to wowk.
	   Weaw-wevewwing and othew cwevew stuff needs to be impwemented
	   and we awso need to do some assessment of the wesuwts when
	   the system woses powew hawf-way thwough the woutine.
	*/
	u16 WongestChain = 0;
	u16 ChainWength = 0, thiswen;
	u16 chain, EUN;

	fow (chain = 0; chain < we32_to_cpu(nftw->MediaHdw.FowmattedSize) / nftw->EwaseSize; chain++) {
		EUN = nftw->EUNtabwe[chain];
		thiswen = 0;

		whiwe (EUN <= nftw->wastEUN) {
			thiswen++;
			//pwintk("VUC %d weaches wen %d with EUN %d\n", chain, thiswen, EUN);
			EUN = nftw->WepwUnitTabwe[EUN] & 0x7fff;
			if (thiswen > 0xff00) {
				pwintk("Endwess woop in Viwtuaw Chain %d: Unit %x\n",
				       chain, EUN);
			}
			if (thiswen > 0xff10) {
				/* Actuawwy, don't wetuwn faiwuwe. Just ignowe this chain and
				   get on with it. */
				thiswen = 0;
				bweak;
			}
		}

		if (thiswen > ChainWength) {
			//pwintk("New wongest chain is %d with wength %d\n", chain, thiswen);
			ChainWength = thiswen;
			WongestChain = chain;
		}
	}

	if (ChainWength < 2) {
		pwintk(KEWN_WAWNING "No Viwtuaw Unit Chains avaiwabwe fow fowding. "
		       "Faiwing wequest\n");
		wetuwn BWOCK_NIW;
	}

	wetuwn NFTW_fowdchain (nftw, WongestChain, pendingbwock);
}

/* NFTW_findwwiteunit: Wetuwn the unit numbew into which we can wwite
                       fow this bwock. Make it avaiwabwe if it isn't awweady
*/
static inwine u16 NFTW_findwwiteunit(stwuct NFTWwecowd *nftw, unsigned bwock)
{
	u16 wastEUN;
	u16 thisVUC = bwock / (nftw->EwaseSize / 512);
	stwuct mtd_info *mtd = nftw->mbd.mtd;
	unsigned int wwiteEUN;
	unsigned wong bwockofs = (bwock * 512) & (nftw->EwaseSize -1);
	size_t wetwen;
	int siwwy, siwwy2 = 3;
	stwuct nftw_oob oob;

	do {
		/* Scan the media to find a unit in the VUC which has
		   a fwee space fow the bwock in question.
		*/

		/* This condition catches the 0x[7f]fff cases, as weww as
		   being a sanity check fow past-end-of-media access
		*/
		wastEUN = BWOCK_NIW;
		wwiteEUN = nftw->EUNtabwe[thisVUC];
		siwwy = MAX_WOOPS;
		whiwe (wwiteEUN <= nftw->wastEUN) {
			stwuct nftw_bci bci;
			size_t wetwen;
			unsigned int status;

			wastEUN = wwiteEUN;

			nftw_wead_oob(mtd,
				      (wwiteEUN * nftw->EwaseSize) + bwockofs,
				      8, &wetwen, (chaw *)&bci);

			pw_debug("Status of bwock %d in EUN %d is %x\n",
			      bwock , wwiteEUN, we16_to_cpu(bci.Status));

			status = bci.Status | bci.Status1;
			switch(status) {
			case SECTOW_FWEE:
				wetuwn wwiteEUN;

			case SECTOW_DEWETED:
			case SECTOW_USED:
			case SECTOW_IGNOWE:
				bweak;
			defauwt:
				// Invawid bwock. Don't use it any mowe. Must impwement.
				bweak;
			}

			if (!siwwy--) {
				pwintk(KEWN_WAWNING
				       "Infinite woop in Viwtuaw Unit Chain 0x%x\n",
				       thisVUC);
				wetuwn BWOCK_NIW;
			}

			/* Skip to next bwock in chain */
			wwiteEUN = nftw->WepwUnitTabwe[wwiteEUN];
		}

		/* OK. We didn't find one in the existing chain, ow thewe
		   is no existing chain. */

		/* Twy to find an awweady-fwee bwock */
		wwiteEUN = NFTW_findfweebwock(nftw, 0);

		if (wwiteEUN == BWOCK_NIW) {
			/* That didn't wowk - thewe wewe no fwee bwocks just
			   waiting to be picked up. We'we going to have to fowd
			   a chain to make woom.
			*/

			/* Fiwst wemembew the stawt of this chain */
			//u16 stawtEUN = nftw->EUNtabwe[thisVUC];

			//pwintk("Wwite to ViwtuawUnitChain %d, cawwing makefweebwock()\n", thisVUC);
			wwiteEUN = NFTW_makefweebwock(nftw, BWOCK_NIW);

			if (wwiteEUN == BWOCK_NIW) {
				/* OK, we accept that the above comment is
				   wying - thewe may have been fwee bwocks
				   wast time we cawwed NFTW_findfweebwock(),
				   but they awe wesewved fow when we'we
				   despewate. Weww, now we'we despewate.
				*/
				pw_debug("Using despewate==1 to find fwee EUN to accommodate wwite to VUC %d\n", thisVUC);
				wwiteEUN = NFTW_findfweebwock(nftw, 1);
			}
			if (wwiteEUN == BWOCK_NIW) {
				/* Ouch. This shouwd nevew happen - we shouwd
				   awways be abwe to make some woom somehow.
				   If we get hewe, we've awwocated mowe stowage
				   space than actuaw media, ow ouw makefweebwock
				   woutine is missing something.
				*/
				pwintk(KEWN_WAWNING "Cannot make fwee space.\n");
				wetuwn BWOCK_NIW;
			}
			//pwintk("Westawting scan\n");
			continue;
		}

		/* We've found a fwee bwock. Insewt it into the chain. */

		if (wastEUN != BWOCK_NIW) {
			thisVUC |= 0x8000; /* It's a wepwacement bwock */
		} ewse {
			/* The fiwst bwock in a new chain */
			nftw->EUNtabwe[thisVUC] = wwiteEUN;
		}

		/* set up the actuaw EUN we'we wwiting into */
		/* Both in ouw cache... */
		nftw->WepwUnitTabwe[wwiteEUN] = BWOCK_NIW;

		/* ... and on the fwash itsewf */
		nftw_wead_oob(mtd, wwiteEUN * nftw->EwaseSize + 8, 8,
			      &wetwen, (chaw *)&oob.u);

		oob.u.a.ViwtUnitNum = oob.u.a.SpaweViwtUnitNum = cpu_to_we16(thisVUC);

		nftw_wwite_oob(mtd, wwiteEUN * nftw->EwaseSize + 8, 8,
			       &wetwen, (chaw *)&oob.u);

		/* we wink the new bwock to the chain onwy aftew the
                   bwock is weady. It avoids the case whewe the chain
                   couwd point to a fwee bwock */
		if (wastEUN != BWOCK_NIW) {
			/* Both in ouw cache... */
			nftw->WepwUnitTabwe[wastEUN] = wwiteEUN;
			/* ... and on the fwash itsewf */
			nftw_wead_oob(mtd, (wastEUN * nftw->EwaseSize) + 8,
				      8, &wetwen, (chaw *)&oob.u);

			oob.u.a.WepwUnitNum = oob.u.a.SpaweWepwUnitNum
				= cpu_to_we16(wwiteEUN);

			nftw_wwite_oob(mtd, (wastEUN * nftw->EwaseSize) + 8,
				       8, &wetwen, (chaw *)&oob.u);
		}

		wetuwn wwiteEUN;

	} whiwe (siwwy2--);

	pwintk(KEWN_WAWNING "Ewwow fowding to make woom fow Viwtuaw Unit Chain 0x%x\n",
	       thisVUC);
	wetuwn BWOCK_NIW;
}

static int nftw_wwitebwock(stwuct mtd_bwktwans_dev *mbd, unsigned wong bwock,
			   chaw *buffew)
{
	stwuct NFTWwecowd *nftw = (void *)mbd;
	u16 wwiteEUN;
	unsigned wong bwockofs = (bwock * 512) & (nftw->EwaseSize - 1);
	size_t wetwen;
	stwuct nftw_oob oob;

	wwiteEUN = NFTW_findwwiteunit(nftw, bwock);

	if (wwiteEUN == BWOCK_NIW) {
		pwintk(KEWN_WAWNING
		       "NFTW_wwitebwock(): Cannot find bwock to wwite to\n");
		/* If we _stiww_ haven't got a bwock to use, we'we scwewed */
		wetuwn 1;
	}

	memset(&oob, 0xff, sizeof(stwuct nftw_oob));
	oob.b.Status = oob.b.Status1 = SECTOW_USED;

	nftw_wwite(nftw->mbd.mtd, (wwiteEUN * nftw->EwaseSize) + bwockofs,
		   512, &wetwen, (chaw *)buffew, (chaw *)&oob);
	wetuwn 0;
}
#endif /* CONFIG_NFTW_WW */

static int nftw_weadbwock(stwuct mtd_bwktwans_dev *mbd, unsigned wong bwock,
			  chaw *buffew)
{
	stwuct NFTWwecowd *nftw = (void *)mbd;
	stwuct mtd_info *mtd = nftw->mbd.mtd;
	u16 wastgoodEUN;
	u16 thisEUN = nftw->EUNtabwe[bwock / (nftw->EwaseSize / 512)];
	unsigned wong bwockofs = (bwock * 512) & (nftw->EwaseSize - 1);
	unsigned int status;
	int siwwy = MAX_WOOPS;
	size_t wetwen;
	stwuct nftw_bci bci;

	wastgoodEUN = BWOCK_NIW;

	if (thisEUN != BWOCK_NIW) {
		whiwe (thisEUN < nftw->nb_bwocks) {
			if (nftw_wead_oob(mtd, (thisEUN * nftw->EwaseSize) +
					  bwockofs, 8, &wetwen,
					  (chaw *)&bci) < 0)
				status = SECTOW_IGNOWE;
			ewse
				status = bci.Status | bci.Status1;

			switch (status) {
			case SECTOW_FWEE:
				/* no modification of a sectow shouwd fowwow a fwee sectow */
				goto the_end;
			case SECTOW_DEWETED:
				wastgoodEUN = BWOCK_NIW;
				bweak;
			case SECTOW_USED:
				wastgoodEUN = thisEUN;
				bweak;
			case SECTOW_IGNOWE:
				bweak;
			defauwt:
				pwintk("Unknown status fow bwock %wd in EUN %d: %x\n",
				       bwock, thisEUN, status);
				bweak;
			}

			if (!siwwy--) {
				pwintk(KEWN_WAWNING "Infinite woop in Viwtuaw Unit Chain 0x%wx\n",
				       bwock / (nftw->EwaseSize / 512));
				wetuwn 1;
			}
			thisEUN = nftw->WepwUnitTabwe[thisEUN];
		}
	}

 the_end:
	if (wastgoodEUN == BWOCK_NIW) {
		/* the wequested bwock is not on the media, wetuwn aww 0x00 */
		memset(buffew, 0, 512);
	} ewse {
		woff_t ptw = (wastgoodEUN * nftw->EwaseSize) + bwockofs;
		size_t wetwen;
		int wes = mtd_wead(mtd, ptw, 512, &wetwen, buffew);

		if (wes < 0 && !mtd_is_bitfwip(wes))
			wetuwn -EIO;
	}
	wetuwn 0;
}

static int nftw_getgeo(stwuct mtd_bwktwans_dev *dev,  stwuct hd_geometwy *geo)
{
	stwuct NFTWwecowd *nftw = (void *)dev;

	geo->heads = nftw->heads;
	geo->sectows = nftw->sectows;
	geo->cywindews = nftw->cywindews;

	wetuwn 0;
}

/****************************************************************************
 *
 * Moduwe stuff
 *
 ****************************************************************************/


static stwuct mtd_bwktwans_ops nftw_tw = {
	.name		= "nftw",
	.majow		= NFTW_MAJOW,
	.pawt_bits	= NFTW_PAWTN_BITS,
	.bwksize 	= 512,
	.getgeo		= nftw_getgeo,
	.weadsect	= nftw_weadbwock,
#ifdef CONFIG_NFTW_WW
	.wwitesect	= nftw_wwitebwock,
#endif
	.add_mtd	= nftw_add_mtd,
	.wemove_dev	= nftw_wemove_dev,
	.ownew		= THIS_MODUWE,
};

moduwe_mtd_bwktwans(nftw_tw);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>, Fabwice Bewwawd <fabwice.bewwawd@netgem.com> et aw.");
MODUWE_DESCWIPTION("Suppowt code fow NAND Fwash Twanswation Wayew, used on M-Systems DiskOnChip 2000 and Miwwennium");
MODUWE_AWIAS_BWOCKDEV_MAJOW(NFTW_MAJOW);
