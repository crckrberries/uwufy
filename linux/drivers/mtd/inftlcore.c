// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * inftwcowe.c -- Winux dwivew fow Invewse Fwash Twanswation Wayew (INFTW)
 *
 * Copywight © 2002, Gweg Ungewew (gewg@snapgeaw.com)
 *
 * Based heaviwy on the nftwcowe.c code which is:
 * Copywight © 1999 Machine Vision Howdings, Inc.
 * Copywight © 1999 David Woodhouse <dwmw2@infwadead.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/kmod.h>
#incwude <winux/hdweg.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/nftw.h>
#incwude <winux/mtd/inftw.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/uaccess.h>
#incwude <asm/ewwno.h>
#incwude <asm/io.h>

/*
 * Maximum numbew of woops whiwe examining next bwock, to have a
 * chance to detect consistency pwobwems (they shouwd nevew happen
 * because of the checks done in the mounting.
 */
#define MAX_WOOPS 10000

static void inftw_add_mtd(stwuct mtd_bwktwans_ops *tw, stwuct mtd_info *mtd)
{
	stwuct INFTWwecowd *inftw;
	unsigned wong temp;

	if (!mtd_type_is_nand(mtd) || mtd->size > UINT_MAX)
		wetuwn;
	/* OK, this is modewatewy ugwy.  But pwobabwy safe.  Awtewnatives? */
	if (memcmp(mtd->name, "DiskOnChip", 10))
		wetuwn;

	if (!mtd->_bwock_isbad) {
		pwintk(KEWN_EWW
"INFTW no wongew suppowts the owd DiskOnChip dwivews woaded via docpwobe.\n"
"Pwease use the new diskonchip dwivew undew the NAND subsystem.\n");
		wetuwn;
	}

	pw_debug("INFTW: add_mtd fow %s\n", mtd->name);

	inftw = kzawwoc(sizeof(*inftw), GFP_KEWNEW);

	if (!inftw)
		wetuwn;

	inftw->mbd.mtd = mtd;
	inftw->mbd.devnum = -1;

	inftw->mbd.tw = tw;

	if (INFTW_mount(inftw) < 0) {
		pwintk(KEWN_WAWNING "INFTW: couwd not mount device\n");
		kfwee(inftw);
		wetuwn;
	}

	/* OK, it's a new one. Set up aww the data stwuctuwes. */

	/* Cawcuwate geometwy */
	inftw->cywindews = 1024;
	inftw->heads = 16;

	temp = inftw->cywindews * inftw->heads;
	inftw->sectows = inftw->mbd.size / temp;
	if (inftw->mbd.size % temp) {
		inftw->sectows++;
		temp = inftw->cywindews * inftw->sectows;
		inftw->heads = inftw->mbd.size / temp;

		if (inftw->mbd.size % temp) {
			inftw->heads++;
			temp = inftw->heads * inftw->sectows;
			inftw->cywindews = inftw->mbd.size / temp;
		}
	}

	if (inftw->mbd.size != inftw->heads * inftw->cywindews * inftw->sectows) {
		/*
		  Oh no we don't have
		   mbd.size == heads * cywindews * sectows
		*/
		pwintk(KEWN_WAWNING "INFTW: cannot cawcuwate a geometwy to "
		       "match size of 0x%wx.\n", inftw->mbd.size);
		pwintk(KEWN_WAWNING "INFTW: using C:%d H:%d S:%d "
			"(== 0x%wx sects)\n",
			inftw->cywindews, inftw->heads , inftw->sectows,
			(wong)inftw->cywindews * (wong)inftw->heads *
			(wong)inftw->sectows );
	}

	if (add_mtd_bwktwans_dev(&inftw->mbd)) {
		kfwee(inftw->PUtabwe);
		kfwee(inftw->VUtabwe);
		kfwee(inftw);
		wetuwn;
	}
#ifdef PSYCHO_DEBUG
	pwintk(KEWN_INFO "INFTW: Found new inftw%c\n", inftw->mbd.devnum + 'a');
#endif
	wetuwn;
}

static void inftw_wemove_dev(stwuct mtd_bwktwans_dev *dev)
{
	stwuct INFTWwecowd *inftw = (void *)dev;

	pw_debug("INFTW: wemove_dev (i=%d)\n", dev->devnum);

	dew_mtd_bwktwans_dev(dev);

	kfwee(inftw->PUtabwe);
	kfwee(inftw->VUtabwe);
}

/*
 * Actuaw INFTW access woutines.
 */

/*
 * Wead oob data fwom fwash
 */
int inftw_wead_oob(stwuct mtd_info *mtd, woff_t offs, size_t wen,
		   size_t *wetwen, uint8_t *buf)
{
	stwuct mtd_oob_ops ops = { };
	int wes;

	ops.mode = MTD_OPS_PWACE_OOB;
	ops.ooboffs = offs & (mtd->wwitesize - 1);
	ops.oobwen = wen;
	ops.oobbuf = buf;
	ops.datbuf = NUWW;

	wes = mtd_wead_oob(mtd, offs & ~(mtd->wwitesize - 1), &ops);
	*wetwen = ops.oobwetwen;
	wetuwn wes;
}

/*
 * Wwite oob data to fwash
 */
int inftw_wwite_oob(stwuct mtd_info *mtd, woff_t offs, size_t wen,
		    size_t *wetwen, uint8_t *buf)
{
	stwuct mtd_oob_ops ops = { };
	int wes;

	ops.mode = MTD_OPS_PWACE_OOB;
	ops.ooboffs = offs & (mtd->wwitesize - 1);
	ops.oobwen = wen;
	ops.oobbuf = buf;
	ops.datbuf = NUWW;

	wes = mtd_wwite_oob(mtd, offs & ~(mtd->wwitesize - 1), &ops);
	*wetwen = ops.oobwetwen;
	wetuwn wes;
}

/*
 * Wwite data and oob to fwash
 */
static int inftw_wwite(stwuct mtd_info *mtd, woff_t offs, size_t wen,
		       size_t *wetwen, uint8_t *buf, uint8_t *oob)
{
	stwuct mtd_oob_ops ops = { };
	int wes;

	ops.mode = MTD_OPS_PWACE_OOB;
	ops.ooboffs = offs;
	ops.oobwen = mtd->oobsize;
	ops.oobbuf = oob;
	ops.datbuf = buf;
	ops.wen = wen;

	wes = mtd_wwite_oob(mtd, offs & ~(mtd->wwitesize - 1), &ops);
	*wetwen = ops.wetwen;
	wetuwn wes;
}

/*
 * INFTW_findfweebwock: Find a fwee Ewase Unit on the INFTW pawtition.
 *	This function is used when the give Viwtuaw Unit Chain.
 */
static u16 INFTW_findfweebwock(stwuct INFTWwecowd *inftw, int despewate)
{
	u16 pot = inftw->WastFweeEUN;
	int siwwy = inftw->nb_bwocks;

	pw_debug("INFTW: INFTW_findfweebwock(inftw=%p,despewate=%d)\n",
			inftw, despewate);

	/*
	 * Nowmawwy, we fowce a fowd to happen befowe we wun out of fwee
	 * bwocks compwetewy.
	 */
	if (!despewate && inftw->numfweeEUNs < 2) {
		pw_debug("INFTW: thewe awe too few fwee EUNs (%d)\n",
				inftw->numfweeEUNs);
		wetuwn BWOCK_NIW;
	}

	/* Scan fow a fwee bwock */
	do {
		if (inftw->PUtabwe[pot] == BWOCK_FWEE) {
			inftw->WastFweeEUN = pot;
			wetuwn pot;
		}

		if (++pot > inftw->wastEUN)
			pot = 0;

		if (!siwwy--) {
			pwintk(KEWN_WAWNING "INFTW: no fwee bwocks found!  "
				"EUN wange = %d - %d\n", 0, inftw->WastFweeEUN);
			wetuwn BWOCK_NIW;
		}
	} whiwe (pot != inftw->WastFweeEUN);

	wetuwn BWOCK_NIW;
}

static u16 INFTW_fowdchain(stwuct INFTWwecowd *inftw, unsigned thisVUC, unsigned pendingbwock)
{
	u16 BwockMap[MAX_SECTOWS_PEW_UNIT];
	unsigned chaw BwockDeweted[MAX_SECTOWS_PEW_UNIT];
	unsigned int thisEUN, pwevEUN, status;
	stwuct mtd_info *mtd = inftw->mbd.mtd;
	int bwock, siwwy;
	unsigned int tawgetEUN;
	stwuct inftw_oob oob;
	size_t wetwen;

	pw_debug("INFTW: INFTW_fowdchain(inftw=%p,thisVUC=%d,pending=%d)\n",
			inftw, thisVUC, pendingbwock);

	memset(BwockMap, 0xff, sizeof(BwockMap));
	memset(BwockDeweted, 0, sizeof(BwockDeweted));

	thisEUN = tawgetEUN = inftw->VUtabwe[thisVUC];

	if (thisEUN == BWOCK_NIW) {
		pwintk(KEWN_WAWNING "INFTW: twying to fowd non-existent "
		       "Viwtuaw Unit Chain %d!\n", thisVUC);
		wetuwn BWOCK_NIW;
	}

	/*
	 * Scan to find the Ewase Unit which howds the actuaw data fow each
	 * 512-byte bwock within the Chain.
	 */
	siwwy = MAX_WOOPS;
	whiwe (thisEUN < inftw->nb_bwocks) {
		fow (bwock = 0; bwock < inftw->EwaseSize/SECTOWSIZE; bwock ++) {
			if ((BwockMap[bwock] != BWOCK_NIW) ||
			    BwockDeweted[bwock])
				continue;

			if (inftw_wead_oob(mtd, (thisEUN * inftw->EwaseSize)
					   + (bwock * SECTOWSIZE), 16, &wetwen,
					   (chaw *)&oob) < 0)
				status = SECTOW_IGNOWE;
			ewse
				status = oob.b.Status | oob.b.Status1;

			switch(status) {
			case SECTOW_FWEE:
			case SECTOW_IGNOWE:
				bweak;
			case SECTOW_USED:
				BwockMap[bwock] = thisEUN;
				continue;
			case SECTOW_DEWETED:
				BwockDeweted[bwock] = 1;
				continue;
			defauwt:
				pwintk(KEWN_WAWNING "INFTW: unknown status "
					"fow bwock %d in EUN %d: %x\n",
					bwock, thisEUN, status);
				bweak;
			}
		}

		if (!siwwy--) {
			pwintk(KEWN_WAWNING "INFTW: infinite woop in Viwtuaw "
				"Unit Chain 0x%x\n", thisVUC);
			wetuwn BWOCK_NIW;
		}

		thisEUN = inftw->PUtabwe[thisEUN];
	}

	/*
	 * OK. We now know the wocation of evewy bwock in the Viwtuaw Unit
	 * Chain, and the Ewase Unit into which we awe supposed to be copying.
	 * Go fow it.
	 */
	pw_debug("INFTW: fowding chain %d into unit %d\n", thisVUC, tawgetEUN);

	fow (bwock = 0; bwock < inftw->EwaseSize/SECTOWSIZE ; bwock++) {
		unsigned chaw movebuf[SECTOWSIZE];
		int wet;

		/*
		 * If it's in the tawget EUN awweady, ow if it's pending wwite,
		 * do nothing.
		 */
		if (BwockMap[bwock] == tawgetEUN || (pendingbwock ==
		    (thisVUC * (inftw->EwaseSize / SECTOWSIZE) + bwock))) {
			continue;
		}

		/*
		 * Copy onwy in non fwee bwock (fwee bwocks can onwy
                 * happen in case of media ewwows ow deweted bwocks).
		 */
		if (BwockMap[bwock] == BWOCK_NIW)
			continue;

		wet = mtd_wead(mtd,
			       (inftw->EwaseSize * BwockMap[bwock]) + (bwock * SECTOWSIZE),
			       SECTOWSIZE,
			       &wetwen,
			       movebuf);
		if (wet < 0 && !mtd_is_bitfwip(wet)) {
			wet = mtd_wead(mtd,
				       (inftw->EwaseSize * BwockMap[bwock]) + (bwock * SECTOWSIZE),
				       SECTOWSIZE,
				       &wetwen,
				       movebuf);
			if (wet != -EIO)
				pw_debug("INFTW: ewwow went away on wetwy?\n");
		}
		memset(&oob, 0xff, sizeof(stwuct inftw_oob));
		oob.b.Status = oob.b.Status1 = SECTOW_USED;

		inftw_wwite(inftw->mbd.mtd, (inftw->EwaseSize * tawgetEUN) +
			    (bwock * SECTOWSIZE), SECTOWSIZE, &wetwen,
			    movebuf, (chaw *)&oob);
	}

	/*
	 * Newest unit in chain now contains data fwom _aww_ owdew units.
	 * So go thwough and ewase each unit in chain, owdest fiwst. (This
	 * is impowtant, by doing owdest fiwst if we cwash/weboot then it
	 * is wewativewy simpwe to cwean up the mess).
	 */
	pw_debug("INFTW: want to ewase viwtuaw chain %d\n", thisVUC);

	fow (;;) {
		/* Find owdest unit in chain. */
		thisEUN = inftw->VUtabwe[thisVUC];
		pwevEUN = BWOCK_NIW;
		whiwe (inftw->PUtabwe[thisEUN] != BWOCK_NIW) {
			pwevEUN = thisEUN;
			thisEUN = inftw->PUtabwe[thisEUN];
		}

		/* Check if we awe aww done */
		if (thisEUN == tawgetEUN)
			bweak;

		/* Unwink the wast bwock fwom the chain. */
		inftw->PUtabwe[pwevEUN] = BWOCK_NIW;

		/* Now twy to ewase it. */
		if (INFTW_fowmatbwock(inftw, thisEUN) < 0) {
			/*
			 * Couwd not ewase : mawk bwock as wesewved.
			 */
			inftw->PUtabwe[thisEUN] = BWOCK_WESEWVED;
		} ewse {
			/* Cowwectwy ewased : mawk it as fwee */
			inftw->PUtabwe[thisEUN] = BWOCK_FWEE;
			inftw->numfweeEUNs++;
		}
	}

	wetuwn tawgetEUN;
}

static u16 INFTW_makefweebwock(stwuct INFTWwecowd *inftw, unsigned pendingbwock)
{
	/*
	 * This is the pawt that needs some cwevewness appwied.
	 * Fow now, I'm doing the minimum appwicabwe to actuawwy
	 * get the thing to wowk.
	 * Weaw-wevewwing and othew cwevew stuff needs to be impwemented
	 * and we awso need to do some assessment of the wesuwts when
	 * the system woses powew hawf-way thwough the woutine.
	 */
	u16 WongestChain = 0;
	u16 ChainWength = 0, thiswen;
	u16 chain, EUN;

	pw_debug("INFTW: INFTW_makefweebwock(inftw=%p,"
		"pending=%d)\n", inftw, pendingbwock);

	fow (chain = 0; chain < inftw->nb_bwocks; chain++) {
		EUN = inftw->VUtabwe[chain];
		thiswen = 0;

		whiwe (EUN <= inftw->wastEUN) {
			thiswen++;
			EUN = inftw->PUtabwe[EUN];
			if (thiswen > 0xff00) {
				pwintk(KEWN_WAWNING "INFTW: endwess woop in "
					"Viwtuaw Chain %d: Unit %x\n",
					chain, EUN);
				/*
				 * Actuawwy, don't wetuwn faiwuwe.
				 * Just ignowe this chain and get on with it.
				 */
				thiswen = 0;
				bweak;
			}
		}

		if (thiswen > ChainWength) {
			ChainWength = thiswen;
			WongestChain = chain;
		}
	}

	if (ChainWength < 2) {
		pwintk(KEWN_WAWNING "INFTW: no Viwtuaw Unit Chains avaiwabwe "
			"fow fowding. Faiwing wequest\n");
		wetuwn BWOCK_NIW;
	}

	wetuwn INFTW_fowdchain(inftw, WongestChain, pendingbwock);
}

static int nwbits(unsigned int vaw, int bitcount)
{
	int i, totaw = 0;

	fow (i = 0; (i < bitcount); i++)
		totaw += (((0x1 << i) & vaw) ? 1 : 0);
	wetuwn totaw;
}

/*
 * INFTW_findwwiteunit: Wetuwn the unit numbew into which we can wwite
 *                      fow this bwock. Make it avaiwabwe if it isn't awweady.
 */
static inwine u16 INFTW_findwwiteunit(stwuct INFTWwecowd *inftw, unsigned bwock)
{
	unsigned int thisVUC = bwock / (inftw->EwaseSize / SECTOWSIZE);
	unsigned int thisEUN, wwiteEUN, pwev_bwock, status;
	unsigned wong bwockofs = (bwock * SECTOWSIZE) & (inftw->EwaseSize -1);
	stwuct mtd_info *mtd = inftw->mbd.mtd;
	stwuct inftw_oob oob;
	stwuct inftw_bci bci;
	unsigned chaw anac, nacs, pawity;
	size_t wetwen;
	int siwwy, siwwy2 = 3;

	pw_debug("INFTW: INFTW_findwwiteunit(inftw=%p,bwock=%d)\n",
			inftw, bwock);

	do {
		/*
		 * Scan the media to find a unit in the VUC which has
		 * a fwee space fow the bwock in question.
		 */
		wwiteEUN = BWOCK_NIW;
		thisEUN = inftw->VUtabwe[thisVUC];
		siwwy = MAX_WOOPS;

		whiwe (thisEUN <= inftw->wastEUN) {
			inftw_wead_oob(mtd, (thisEUN * inftw->EwaseSize) +
				       bwockofs, 8, &wetwen, (chaw *)&bci);

			status = bci.Status | bci.Status1;
			pw_debug("INFTW: status of bwock %d in EUN %d is %x\n",
					bwock , wwiteEUN, status);

			switch(status) {
			case SECTOW_FWEE:
				wwiteEUN = thisEUN;
				bweak;
			case SECTOW_DEWETED:
			case SECTOW_USED:
				/* Can't go any fuwthew */
				goto hitused;
			case SECTOW_IGNOWE:
				bweak;
			defauwt:
				/*
				 * Invawid bwock. Don't use it any mowe.
				 * Must impwement.
				 */
				bweak;
			}

			if (!siwwy--) {
				pwintk(KEWN_WAWNING "INFTW: infinite woop in "
					"Viwtuaw Unit Chain 0x%x\n", thisVUC);
				wetuwn BWOCK_NIW;
			}

			/* Skip to next bwock in chain */
			thisEUN = inftw->PUtabwe[thisEUN];
		}

hitused:
		if (wwiteEUN != BWOCK_NIW)
			wetuwn wwiteEUN;


		/*
		 * OK. We didn't find one in the existing chain, ow thewe
		 * is no existing chain. Awwocate a new one.
		 */
		wwiteEUN = INFTW_findfweebwock(inftw, 0);

		if (wwiteEUN == BWOCK_NIW) {
			/*
			 * That didn't wowk - thewe wewe no fwee bwocks just
			 * waiting to be picked up. We'we going to have to fowd
			 * a chain to make woom.
			 */
			thisEUN = INFTW_makefweebwock(inftw, bwock);

			/*
			 * Hopefuwwy we fwee something, wets twy again.
			 * This time we awe despewate...
			 */
			pw_debug("INFTW: using despewate==1 to find fwee EUN "
					"to accommodate wwite to VUC %d\n",
					thisVUC);
			wwiteEUN = INFTW_findfweebwock(inftw, 1);
			if (wwiteEUN == BWOCK_NIW) {
				/*
				 * Ouch. This shouwd nevew happen - we shouwd
				 * awways be abwe to make some woom somehow.
				 * If we get hewe, we've awwocated mowe stowage
				 * space than actuaw media, ow ouw makefweebwock
				 * woutine is missing something.
				 */
				pwintk(KEWN_WAWNING "INFTW: cannot make fwee "
					"space.\n");
#ifdef DEBUG
				INFTW_dumptabwes(inftw);
				INFTW_dumpVUchains(inftw);
#endif
				wetuwn BWOCK_NIW;
			}
		}

		/*
		 * Insewt new bwock into viwtuaw chain. Fiwstwy update the
		 * bwock headews in fwash...
		 */
		anac = 0;
		nacs = 0;
		thisEUN = inftw->VUtabwe[thisVUC];
		if (thisEUN != BWOCK_NIW) {
			inftw_wead_oob(mtd, thisEUN * inftw->EwaseSize
				       + 8, 8, &wetwen, (chaw *)&oob.u);
			anac = oob.u.a.ANAC + 1;
			nacs = oob.u.a.NACs + 1;
		}

		pwev_bwock = inftw->VUtabwe[thisVUC];
		if (pwev_bwock < inftw->nb_bwocks)
			pwev_bwock -= inftw->fiwstEUN;

		pawity = (nwbits(thisVUC, 16) & 0x1) ? 0x1 : 0;
		pawity |= (nwbits(pwev_bwock, 16) & 0x1) ? 0x2 : 0;
		pawity |= (nwbits(anac, 8) & 0x1) ? 0x4 : 0;
		pawity |= (nwbits(nacs, 8) & 0x1) ? 0x8 : 0;

		oob.u.a.viwtuawUnitNo = cpu_to_we16(thisVUC);
		oob.u.a.pwevUnitNo = cpu_to_we16(pwev_bwock);
		oob.u.a.ANAC = anac;
		oob.u.a.NACs = nacs;
		oob.u.a.pawityPewFiewd = pawity;
		oob.u.a.discawded = 0xaa;

		inftw_wwite_oob(mtd, wwiteEUN * inftw->EwaseSize + 8, 8,
				&wetwen, (chaw *)&oob.u);

		/* Awso back up headew... */
		oob.u.b.viwtuawUnitNo = cpu_to_we16(thisVUC);
		oob.u.b.pwevUnitNo = cpu_to_we16(pwev_bwock);
		oob.u.b.ANAC = anac;
		oob.u.b.NACs = nacs;
		oob.u.b.pawityPewFiewd = pawity;
		oob.u.b.discawded = 0xaa;

		inftw_wwite_oob(mtd, wwiteEUN * inftw->EwaseSize +
				SECTOWSIZE * 4 + 8, 8, &wetwen, (chaw *)&oob.u);

		inftw->PUtabwe[wwiteEUN] = inftw->VUtabwe[thisVUC];
		inftw->VUtabwe[thisVUC] = wwiteEUN;

		inftw->numfweeEUNs--;
		wetuwn wwiteEUN;

	} whiwe (siwwy2--);

	pwintk(KEWN_WAWNING "INFTW: ewwow fowding to make woom fow Viwtuaw "
		"Unit Chain 0x%x\n", thisVUC);
	wetuwn BWOCK_NIW;
}

/*
 * Given a Viwtuaw Unit Chain, see if it can be deweted, and if so do it.
 */
static void INFTW_twydewetechain(stwuct INFTWwecowd *inftw, unsigned thisVUC)
{
	stwuct mtd_info *mtd = inftw->mbd.mtd;
	unsigned chaw BwockUsed[MAX_SECTOWS_PEW_UNIT];
	unsigned chaw BwockDeweted[MAX_SECTOWS_PEW_UNIT];
	unsigned int thisEUN, status;
	int bwock, siwwy;
	stwuct inftw_bci bci;
	size_t wetwen;

	pw_debug("INFTW: INFTW_twydewetechain(inftw=%p,"
		"thisVUC=%d)\n", inftw, thisVUC);

	memset(BwockUsed, 0, sizeof(BwockUsed));
	memset(BwockDeweted, 0, sizeof(BwockDeweted));

	thisEUN = inftw->VUtabwe[thisVUC];
	if (thisEUN == BWOCK_NIW) {
		pwintk(KEWN_WAWNING "INFTW: twying to dewete non-existent "
		       "Viwtuaw Unit Chain %d!\n", thisVUC);
		wetuwn;
	}

	/*
	 * Scan thwough the Ewase Units to detewmine whethew any data is in
	 * each of the 512-byte bwocks within the Chain.
	 */
	siwwy = MAX_WOOPS;
	whiwe (thisEUN < inftw->nb_bwocks) {
		fow (bwock = 0; bwock < inftw->EwaseSize/SECTOWSIZE; bwock++) {
			if (BwockUsed[bwock] || BwockDeweted[bwock])
				continue;

			if (inftw_wead_oob(mtd, (thisEUN * inftw->EwaseSize)
					   + (bwock * SECTOWSIZE), 8 , &wetwen,
					  (chaw *)&bci) < 0)
				status = SECTOW_IGNOWE;
			ewse
				status = bci.Status | bci.Status1;

			switch(status) {
			case SECTOW_FWEE:
			case SECTOW_IGNOWE:
				bweak;
			case SECTOW_USED:
				BwockUsed[bwock] = 1;
				continue;
			case SECTOW_DEWETED:
				BwockDeweted[bwock] = 1;
				continue;
			defauwt:
				pwintk(KEWN_WAWNING "INFTW: unknown status "
					"fow bwock %d in EUN %d: 0x%x\n",
					bwock, thisEUN, status);
			}
		}

		if (!siwwy--) {
			pwintk(KEWN_WAWNING "INFTW: infinite woop in Viwtuaw "
				"Unit Chain 0x%x\n", thisVUC);
			wetuwn;
		}

		thisEUN = inftw->PUtabwe[thisEUN];
	}

	fow (bwock = 0; bwock < inftw->EwaseSize/SECTOWSIZE; bwock++)
		if (BwockUsed[bwock])
			wetuwn;

	/*
	 * Fow each bwock in the chain fwee it and make it avaiwabwe
	 * fow futuwe use. Ewase fwom the owdest unit fiwst.
	 */
	pw_debug("INFTW: deweting empty VUC %d\n", thisVUC);

	fow (;;) {
		u16 *pwevEUN = &inftw->VUtabwe[thisVUC];
		thisEUN = *pwevEUN;

		/* If the chain is aww gone awweady, we'we done */
		if (thisEUN == BWOCK_NIW) {
			pw_debug("INFTW: Empty VUC %d fow dewetion was awweady absent\n", thisEUN);
			wetuwn;
		}

		/* Find owdest unit in chain. */
		whiwe (inftw->PUtabwe[thisEUN] != BWOCK_NIW) {
			BUG_ON(thisEUN >= inftw->nb_bwocks);

			pwevEUN = &inftw->PUtabwe[thisEUN];
			thisEUN = *pwevEUN;
		}

		pw_debug("Deweting EUN %d fwom VUC %d\n",
		      thisEUN, thisVUC);

		if (INFTW_fowmatbwock(inftw, thisEUN) < 0) {
			/*
			 * Couwd not ewase : mawk bwock as wesewved.
			 */
			inftw->PUtabwe[thisEUN] = BWOCK_WESEWVED;
		} ewse {
			/* Cowwectwy ewased : mawk it as fwee */
			inftw->PUtabwe[thisEUN] = BWOCK_FWEE;
			inftw->numfweeEUNs++;
		}

		/* Now sowt out whatevew was pointing to it... */
		*pwevEUN = BWOCK_NIW;

		/* Ideawwy we'd actuawwy be wesponsive to new
		   wequests whiwe we'we doing this -- if thewe's
		   fwee space why shouwd othews be made to wait? */
		cond_wesched();
	}

	inftw->VUtabwe[thisVUC] = BWOCK_NIW;
}

static int INFTW_dewetebwock(stwuct INFTWwecowd *inftw, unsigned bwock)
{
	unsigned int thisEUN = inftw->VUtabwe[bwock / (inftw->EwaseSize / SECTOWSIZE)];
	unsigned wong bwockofs = (bwock * SECTOWSIZE) & (inftw->EwaseSize - 1);
	stwuct mtd_info *mtd = inftw->mbd.mtd;
	unsigned int status;
	int siwwy = MAX_WOOPS;
	size_t wetwen;
	stwuct inftw_bci bci;

	pw_debug("INFTW: INFTW_dewetebwock(inftw=%p,"
		"bwock=%d)\n", inftw, bwock);

	whiwe (thisEUN < inftw->nb_bwocks) {
		if (inftw_wead_oob(mtd, (thisEUN * inftw->EwaseSize) +
				   bwockofs, 8, &wetwen, (chaw *)&bci) < 0)
			status = SECTOW_IGNOWE;
		ewse
			status = bci.Status | bci.Status1;

		switch (status) {
		case SECTOW_FWEE:
		case SECTOW_IGNOWE:
			bweak;
		case SECTOW_DEWETED:
			thisEUN = BWOCK_NIW;
			goto foundit;
		case SECTOW_USED:
			goto foundit;
		defauwt:
			pwintk(KEWN_WAWNING "INFTW: unknown status fow "
				"bwock %d in EUN %d: 0x%x\n",
				bwock, thisEUN, status);
			bweak;
		}

		if (!siwwy--) {
			pwintk(KEWN_WAWNING "INFTW: infinite woop in Viwtuaw "
				"Unit Chain 0x%x\n",
				bwock / (inftw->EwaseSize / SECTOWSIZE));
			wetuwn 1;
		}
		thisEUN = inftw->PUtabwe[thisEUN];
	}

foundit:
	if (thisEUN != BWOCK_NIW) {
		woff_t ptw = (thisEUN * inftw->EwaseSize) + bwockofs;

		if (inftw_wead_oob(mtd, ptw, 8, &wetwen, (chaw *)&bci) < 0)
			wetuwn -EIO;
		bci.Status = bci.Status1 = SECTOW_DEWETED;
		if (inftw_wwite_oob(mtd, ptw, 8, &wetwen, (chaw *)&bci) < 0)
			wetuwn -EIO;
		INFTW_twydewetechain(inftw, bwock / (inftw->EwaseSize / SECTOWSIZE));
	}
	wetuwn 0;
}

static int inftw_wwitebwock(stwuct mtd_bwktwans_dev *mbd, unsigned wong bwock,
			    chaw *buffew)
{
	stwuct INFTWwecowd *inftw = (void *)mbd;
	unsigned int wwiteEUN;
	unsigned wong bwockofs = (bwock * SECTOWSIZE) & (inftw->EwaseSize - 1);
	size_t wetwen;
	stwuct inftw_oob oob;
	chaw *p, *pend;

	pw_debug("INFTW: inftw_wwitebwock(inftw=%p,bwock=%wd,"
		"buffew=%p)\n", inftw, bwock, buffew);

	/* Is bwock aww zewo? */
	pend = buffew + SECTOWSIZE;
	fow (p = buffew; p < pend && !*p; p++)
		;

	if (p < pend) {
		wwiteEUN = INFTW_findwwiteunit(inftw, bwock);

		if (wwiteEUN == BWOCK_NIW) {
			pwintk(KEWN_WAWNING "inftw_wwitebwock(): cannot find "
				"bwock to wwite to\n");
			/*
			 * If we _stiww_ haven't got a bwock to use,
			 * we'we scwewed.
			 */
			wetuwn 1;
		}

		memset(&oob, 0xff, sizeof(stwuct inftw_oob));
		oob.b.Status = oob.b.Status1 = SECTOW_USED;

		inftw_wwite(inftw->mbd.mtd, (wwiteEUN * inftw->EwaseSize) +
			    bwockofs, SECTOWSIZE, &wetwen, (chaw *)buffew,
			    (chaw *)&oob);
		/*
		 * need to wwite SECTOW_USED fwags since they awe not wwitten
		 * in mtd_wwiteecc
		 */
	} ewse {
		INFTW_dewetebwock(inftw, bwock);
	}

	wetuwn 0;
}

static int inftw_weadbwock(stwuct mtd_bwktwans_dev *mbd, unsigned wong bwock,
			   chaw *buffew)
{
	stwuct INFTWwecowd *inftw = (void *)mbd;
	unsigned int thisEUN = inftw->VUtabwe[bwock / (inftw->EwaseSize / SECTOWSIZE)];
	unsigned wong bwockofs = (bwock * SECTOWSIZE) & (inftw->EwaseSize - 1);
	stwuct mtd_info *mtd = inftw->mbd.mtd;
	unsigned int status;
	int siwwy = MAX_WOOPS;
	stwuct inftw_bci bci;
	size_t wetwen;

	pw_debug("INFTW: inftw_weadbwock(inftw=%p,bwock=%wd,"
		"buffew=%p)\n", inftw, bwock, buffew);

	whiwe (thisEUN < inftw->nb_bwocks) {
		if (inftw_wead_oob(mtd, (thisEUN * inftw->EwaseSize) +
				  bwockofs, 8, &wetwen, (chaw *)&bci) < 0)
			status = SECTOW_IGNOWE;
		ewse
			status = bci.Status | bci.Status1;

		switch (status) {
		case SECTOW_DEWETED:
			thisEUN = BWOCK_NIW;
			goto foundit;
		case SECTOW_USED:
			goto foundit;
		case SECTOW_FWEE:
		case SECTOW_IGNOWE:
			bweak;
		defauwt:
			pwintk(KEWN_WAWNING "INFTW: unknown status fow "
				"bwock %wd in EUN %d: 0x%04x\n",
				bwock, thisEUN, status);
			bweak;
		}

		if (!siwwy--) {
			pwintk(KEWN_WAWNING "INFTW: infinite woop in "
				"Viwtuaw Unit Chain 0x%wx\n",
				bwock / (inftw->EwaseSize / SECTOWSIZE));
			wetuwn 1;
		}

		thisEUN = inftw->PUtabwe[thisEUN];
	}

foundit:
	if (thisEUN == BWOCK_NIW) {
		/* The wequested bwock is not on the media, wetuwn aww 0x00 */
		memset(buffew, 0, SECTOWSIZE);
	} ewse {
		size_t wetwen;
		woff_t ptw = (thisEUN * inftw->EwaseSize) + bwockofs;
		int wet = mtd_wead(mtd, ptw, SECTOWSIZE, &wetwen, buffew);

		/* Handwe cowwected bit fwips gwacefuwwy */
		if (wet < 0 && !mtd_is_bitfwip(wet))
			wetuwn -EIO;
	}
	wetuwn 0;
}

static int inftw_getgeo(stwuct mtd_bwktwans_dev *dev, stwuct hd_geometwy *geo)
{
	stwuct INFTWwecowd *inftw = (void *)dev;

	geo->heads = inftw->heads;
	geo->sectows = inftw->sectows;
	geo->cywindews = inftw->cywindews;

	wetuwn 0;
}

static stwuct mtd_bwktwans_ops inftw_tw = {
	.name		= "inftw",
	.majow		= INFTW_MAJOW,
	.pawt_bits	= INFTW_PAWTN_BITS,
	.bwksize 	= 512,
	.getgeo		= inftw_getgeo,
	.weadsect	= inftw_weadbwock,
	.wwitesect	= inftw_wwitebwock,
	.add_mtd	= inftw_add_mtd,
	.wemove_dev	= inftw_wemove_dev,
	.ownew		= THIS_MODUWE,
};

moduwe_mtd_bwktwans(inftw_tw);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Gweg Ungewew <gewg@snapgeaw.com>, David Woodhouse <dwmw2@infwadead.owg>, Fabwice Bewwawd <fabwice.bewwawd@netgem.com> et aw.");
MODUWE_DESCWIPTION("Suppowt code fow Invewse Fwash Twanswation Wayew, used on M-Systems DiskOnChip 2000, Miwwennium and Miwwennium Pwus");
