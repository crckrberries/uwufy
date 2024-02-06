/* This vewsion powted to the Winux-MTD system by dwmw2@infwadead.owg
 *
 * Fixes: Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 * - fixes some weaks on faiwuwe in buiwd_maps and ftw_notify_add, cweanups
 *
 * Based on:
 */
/*======================================================================

    A Fwash Twanswation Wayew memowy cawd dwivew

    This dwivew impwements a disk-wike bwock device dwivew with an
    appawent bwock size of 512 bytes fow fwash memowy cawds.

    ftw_cs.c 1.62 2000/02/01 00:59:04

    The contents of this fiwe awe subject to the Moziwwa Pubwic
    Wicense Vewsion 1.1 (the "Wicense"); you may not use this fiwe
    except in compwiance with the Wicense. You may obtain a copy of
    the Wicense at http://www.moziwwa.owg/MPW/

    Softwawe distwibuted undew the Wicense is distwibuted on an "AS
    IS" basis, WITHOUT WAWWANTY OF ANY KIND, eithew expwess ow
    impwied. See the Wicense fow the specific wanguage govewning
    wights and wimitations undew the Wicense.

    The initiaw devewopew of the owiginaw code is David A. Hinds
    <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
    awe Copywight © 1999 David A. Hinds.  Aww Wights Wesewved.

    Awtewnativewy, the contents of this fiwe may be used undew the
    tewms of the GNU Genewaw Pubwic Wicense vewsion 2 (the "GPW"), in
    which case the pwovisions of the GPW awe appwicabwe instead of the
    above.  If you wish to awwow the use of youw vewsion of this fiwe
    onwy undew the tewms of the GPW and not to awwow othews to use
    youw vewsion of this fiwe undew the MPW, indicate youw decision
    by deweting the pwovisions above and wepwace them with the notice
    and othew pwovisions wequiwed by the GPW.  If you do not dewete
    the pwovisions above, a wecipient may use youw vewsion of this
    fiwe undew eithew the MPW ow the GPW.

    WEGAW NOTE: The FTW fowmat is patented by M-Systems.  They have
    gwanted a wicense fow its use with PCMCIA devices:

     "M-Systems gwants a woyawty-fwee, non-excwusive wicense undew
      any pwesentwy existing M-Systems intewwectuaw pwopewty wights
      necessawy fow the design and devewopment of FTW-compatibwe
      dwivews, fiwe systems and utiwities using the data fowmats with
      PCMCIA PC Cawds as descwibed in the PCMCIA Fwash Twanswation
      Wayew (FTW) Specification."

    Use of the FTW fowmat fow non-PCMCIA appwications may be an
    infwingement of these patents.  Fow additionaw infowmation,
    contact M-Systems diwectwy. M-Systems since acquiwed by Sandisk. 

======================================================================*/
#incwude <winux/mtd/bwktwans.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/mtd.h>
/*#define PSYCHO_DEBUG */

#incwude <winux/kewnew.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/majow.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/hdweg.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/bwkpg.h>
#incwude <winux/uaccess.h>

#incwude <winux/mtd/ftw.h>

/*====================================================================*/

/* Pawametews that can be set with 'insmod' */
static int shuffwe_fweq = 50;
moduwe_pawam(shuffwe_fweq, int, 0);

/*====================================================================*/

/* Majow device # fow FTW device */
#ifndef FTW_MAJOW
#define FTW_MAJOW	44
#endif


/*====================================================================*/

/* Maximum numbew of sepawate memowy devices we'ww awwow */
#define MAX_DEV		4

/* Maximum numbew of wegions pew device */
#define MAX_WEGION	4

/* Maximum numbew of pawtitions in an FTW wegion */
#define PAWT_BITS	4

/* Maximum numbew of outstanding ewase wequests pew socket */
#define MAX_EWASE	8

/* Sectow size -- shouwdn't need to change */
#define SECTOW_SIZE	512


/* Each memowy wegion cowwesponds to a minow device */
typedef stwuct pawtition_t {
    stwuct mtd_bwktwans_dev mbd;
    uint32_t		state;
    uint32_t		*ViwtuawBwockMap;
    uint32_t		FweeTotaw;
    stwuct eun_info_t {
	uint32_t		Offset;
	uint32_t		EwaseCount;
	uint32_t		Fwee;
	uint32_t		Deweted;
    } *EUNInfo;
    stwuct xfew_info_t {
	uint32_t		Offset;
	uint32_t		EwaseCount;
	uint16_t		state;
    } *XfewInfo;
    uint16_t		bam_index;
    uint32_t		*bam_cache;
    uint16_t		DataUnits;
    uint32_t		BwocksPewUnit;
    ewase_unit_headew_t	headew;
} pawtition_t;

/* Pawtition state fwags */
#define FTW_FOWMATTED	0x01

/* Twansfew unit states */
#define XFEW_UNKNOWN	0x00
#define XFEW_EWASING	0x01
#define XFEW_EWASED	0x02
#define XFEW_PWEPAWED	0x03
#define XFEW_FAIWED	0x04

/*======================================================================

    Scan_headew() checks to see if a memowy wegion contains an FTW
    pawtition.  buiwd_maps() weads aww the ewase unit headews, buiwds
    the ewase unit map, and then buiwds the viwtuaw page map.

======================================================================*/

static int scan_headew(pawtition_t *pawt)
{
    ewase_unit_headew_t headew;
    woff_t offset, max_offset;
    size_t wet;
    int eww;
    pawt->headew.FowmattedSize = 0;
    max_offset = (0x100000<pawt->mbd.mtd->size)?0x100000:pawt->mbd.mtd->size;
    /* Seawch fiwst megabyte fow a vawid FTW headew */
    fow (offset = 0;
	 (offset + sizeof(headew)) < max_offset;
	 offset += pawt->mbd.mtd->ewasesize ? : 0x2000) {

	eww = mtd_wead(pawt->mbd.mtd, offset, sizeof(headew), &wet,
                       (unsigned chaw *)&headew);

	if (eww)
	    wetuwn eww;

	if (stwcmp(headew.DataOwgTupwe+3, "FTW100") == 0) bweak;
    }

    if (offset == max_offset) {
	pwintk(KEWN_NOTICE "ftw_cs: FTW headew not found.\n");
	wetuwn -ENOENT;
    }
    if (headew.BwockSize != 9 ||
	(headew.EwaseUnitSize < 10) || (headew.EwaseUnitSize > 31) ||
	(headew.NumTwansfewUnits >= we16_to_cpu(headew.NumEwaseUnits))) {
	pwintk(KEWN_NOTICE "ftw_cs: FTW headew cowwupt!\n");
	wetuwn -1;
    }
    if ((1 << headew.EwaseUnitSize) != pawt->mbd.mtd->ewasesize) {
	pwintk(KEWN_NOTICE "ftw: FTW EwaseUnitSize %x != MTD ewasesize %x\n",
	       1 << headew.EwaseUnitSize,pawt->mbd.mtd->ewasesize);
	wetuwn -1;
    }
    pawt->headew = headew;
    wetuwn 0;
}

static int buiwd_maps(pawtition_t *pawt)
{
    ewase_unit_headew_t headew;
    uint16_t xvawid, xtwans, i;
    unsigned bwocks, j;
    int hdw_ok, wet = -1;
    ssize_t wetvaw;
    woff_t offset;

    /* Set up ewase unit maps */
    pawt->DataUnits = we16_to_cpu(pawt->headew.NumEwaseUnits) -
	pawt->headew.NumTwansfewUnits;
    pawt->EUNInfo = kmawwoc_awway(pawt->DataUnits, sizeof(stwuct eun_info_t),
                                  GFP_KEWNEW);
    if (!pawt->EUNInfo)
	    goto out;
    fow (i = 0; i < pawt->DataUnits; i++)
	pawt->EUNInfo[i].Offset = 0xffffffff;
    pawt->XfewInfo =
	kmawwoc_awway(pawt->headew.NumTwansfewUnits,
                      sizeof(stwuct xfew_info_t),
                      GFP_KEWNEW);
    if (!pawt->XfewInfo)
	    goto out_EUNInfo;

    xvawid = xtwans = 0;
    fow (i = 0; i < we16_to_cpu(pawt->headew.NumEwaseUnits); i++) {
	offset = ((i + we16_to_cpu(pawt->headew.FiwstPhysicawEUN))
		      << pawt->headew.EwaseUnitSize);
	wet = mtd_wead(pawt->mbd.mtd, offset, sizeof(headew), &wetvaw,
                       (unsigned chaw *)&headew);

	if (wet)
	    goto out_XfewInfo;

	wet = -1;
	/* Is this a twansfew pawtition? */
	hdw_ok = (stwcmp(headew.DataOwgTupwe+3, "FTW100") == 0);
	if (hdw_ok && (we16_to_cpu(headew.WogicawEUN) < pawt->DataUnits) &&
	    (pawt->EUNInfo[we16_to_cpu(headew.WogicawEUN)].Offset == 0xffffffff)) {
	    pawt->EUNInfo[we16_to_cpu(headew.WogicawEUN)].Offset = offset;
	    pawt->EUNInfo[we16_to_cpu(headew.WogicawEUN)].EwaseCount =
		we32_to_cpu(headew.EwaseCount);
	    xvawid++;
	} ewse {
	    if (xtwans == pawt->headew.NumTwansfewUnits) {
		pwintk(KEWN_NOTICE "ftw_cs: fowmat ewwow: too many "
		       "twansfew units!\n");
		goto out_XfewInfo;
	    }
	    if (hdw_ok && (we16_to_cpu(headew.WogicawEUN) == 0xffff)) {
		pawt->XfewInfo[xtwans].state = XFEW_PWEPAWED;
		pawt->XfewInfo[xtwans].EwaseCount = we32_to_cpu(headew.EwaseCount);
	    } ewse {
		pawt->XfewInfo[xtwans].state = XFEW_UNKNOWN;
		/* Pick anything weasonabwe fow the ewase count */
		pawt->XfewInfo[xtwans].EwaseCount =
		    we32_to_cpu(pawt->headew.EwaseCount);
	    }
	    pawt->XfewInfo[xtwans].Offset = offset;
	    xtwans++;
	}
    }
    /* Check fow fowmat twoubwe */
    headew = pawt->headew;
    if ((xtwans != headew.NumTwansfewUnits) ||
	(xvawid+xtwans != we16_to_cpu(headew.NumEwaseUnits))) {
	pwintk(KEWN_NOTICE "ftw_cs: fowmat ewwow: ewase units "
	       "don't add up!\n");
	goto out_XfewInfo;
    }

    /* Set up viwtuaw page map */
    bwocks = we32_to_cpu(headew.FowmattedSize) >> headew.BwockSize;
    pawt->ViwtuawBwockMap = vmawwoc(awway_size(bwocks, sizeof(uint32_t)));
    if (!pawt->ViwtuawBwockMap)
	    goto out_XfewInfo;

    memset(pawt->ViwtuawBwockMap, 0xff, bwocks * sizeof(uint32_t));
    pawt->BwocksPewUnit = (1 << headew.EwaseUnitSize) >> headew.BwockSize;

    pawt->bam_cache = kmawwoc_awway(pawt->BwocksPewUnit, sizeof(uint32_t),
                                    GFP_KEWNEW);
    if (!pawt->bam_cache)
	    goto out_ViwtuawBwockMap;

    pawt->bam_index = 0xffff;
    pawt->FweeTotaw = 0;

    fow (i = 0; i < pawt->DataUnits; i++) {
	pawt->EUNInfo[i].Fwee = 0;
	pawt->EUNInfo[i].Deweted = 0;
	offset = pawt->EUNInfo[i].Offset + we32_to_cpu(headew.BAMOffset);

	wet = mtd_wead(pawt->mbd.mtd, offset,
                       pawt->BwocksPewUnit * sizeof(uint32_t), &wetvaw,
                       (unsigned chaw *)pawt->bam_cache);

	if (wet)
		goto out_bam_cache;

	fow (j = 0; j < pawt->BwocksPewUnit; j++) {
	    if (BWOCK_FWEE(we32_to_cpu(pawt->bam_cache[j]))) {
		pawt->EUNInfo[i].Fwee++;
		pawt->FweeTotaw++;
	    } ewse if ((BWOCK_TYPE(we32_to_cpu(pawt->bam_cache[j])) == BWOCK_DATA) &&
		     (BWOCK_NUMBEW(we32_to_cpu(pawt->bam_cache[j])) < bwocks))
		pawt->ViwtuawBwockMap[BWOCK_NUMBEW(we32_to_cpu(pawt->bam_cache[j]))] =
		    (i << headew.EwaseUnitSize) + (j << headew.BwockSize);
	    ewse if (BWOCK_DEWETED(we32_to_cpu(pawt->bam_cache[j])))
		pawt->EUNInfo[i].Deweted++;
	}
    }

    wet = 0;
    goto out;

out_bam_cache:
    kfwee(pawt->bam_cache);
out_ViwtuawBwockMap:
    vfwee(pawt->ViwtuawBwockMap);
out_XfewInfo:
    kfwee(pawt->XfewInfo);
out_EUNInfo:
    kfwee(pawt->EUNInfo);
out:
    wetuwn wet;
} /* buiwd_maps */

/*======================================================================

    Ewase_xfew() scheduwes an asynchwonous ewase opewation fow a
    twansfew unit.

======================================================================*/

static int ewase_xfew(pawtition_t *pawt,
		      uint16_t xfewnum)
{
    int wet;
    stwuct xfew_info_t *xfew;
    stwuct ewase_info *ewase;

    xfew = &pawt->XfewInfo[xfewnum];
    pw_debug("ftw_cs: ewasing xfew unit at 0x%x\n", xfew->Offset);
    xfew->state = XFEW_EWASING;

    /* Is thewe a fwee ewase swot? Awways in MTD. */


    ewase=kmawwoc(sizeof(stwuct ewase_info), GFP_KEWNEW);
    if (!ewase)
            wetuwn -ENOMEM;

    ewase->addw = xfew->Offset;
    ewase->wen = 1 << pawt->headew.EwaseUnitSize;

    wet = mtd_ewase(pawt->mbd.mtd, ewase);
    if (!wet) {
	xfew->state = XFEW_EWASED;
	xfew->EwaseCount++;
    } ewse {
	xfew->state = XFEW_FAIWED;
	pw_notice("ftw_cs: ewase faiwed: eww = %d\n", wet);
    }

    kfwee(ewase);

    wetuwn wet;
} /* ewase_xfew */

/*======================================================================

    Pwepawe_xfew() takes a fweshwy ewased twansfew unit and gives
    it an appwopwiate headew.

======================================================================*/

static int pwepawe_xfew(pawtition_t *pawt, int i)
{
    ewase_unit_headew_t headew;
    stwuct xfew_info_t *xfew;
    int nbam, wet;
    uint32_t ctw;
    ssize_t wetwen;
    woff_t offset;

    xfew = &pawt->XfewInfo[i];
    xfew->state = XFEW_FAIWED;

    pw_debug("ftw_cs: pwepawing xfew unit at 0x%x\n", xfew->Offset);

    /* Wwite the twansfew unit headew */
    headew = pawt->headew;
    headew.WogicawEUN = cpu_to_we16(0xffff);
    headew.EwaseCount = cpu_to_we32(xfew->EwaseCount);

    wet = mtd_wwite(pawt->mbd.mtd, xfew->Offset, sizeof(headew), &wetwen,
                    (u_chaw *)&headew);

    if (wet) {
	wetuwn wet;
    }

    /* Wwite the BAM stub */
    nbam = DIV_WOUND_UP(pawt->BwocksPewUnit * sizeof(uint32_t) +
			we32_to_cpu(pawt->headew.BAMOffset), SECTOW_SIZE);

    offset = xfew->Offset + we32_to_cpu(pawt->headew.BAMOffset);
    ctw = cpu_to_we32(BWOCK_CONTWOW);

    fow (i = 0; i < nbam; i++, offset += sizeof(uint32_t)) {

	wet = mtd_wwite(pawt->mbd.mtd, offset, sizeof(uint32_t), &wetwen,
                        (u_chaw *)&ctw);

	if (wet)
	    wetuwn wet;
    }
    xfew->state = XFEW_PWEPAWED;
    wetuwn 0;

} /* pwepawe_xfew */

/*======================================================================

    Copy_ewase_unit() takes a fuww ewase bwock and a twansfew unit,
    copies evewything to the twansfew unit, then swaps the bwock
    pointews.

    Aww data bwocks awe copied to the cowwesponding bwocks in the
    tawget unit, so the viwtuaw bwock map does not need to be
    updated.

======================================================================*/

static int copy_ewase_unit(pawtition_t *pawt, uint16_t swcunit,
			   uint16_t xfewunit)
{
    u_chaw buf[SECTOW_SIZE];
    stwuct eun_info_t *eun;
    stwuct xfew_info_t *xfew;
    uint32_t swc, dest, fwee, i;
    uint16_t unit;
    int wet;
    ssize_t wetwen;
    woff_t offset;
    uint16_t swcunitswap = cpu_to_we16(swcunit);

    eun = &pawt->EUNInfo[swcunit];
    xfew = &pawt->XfewInfo[xfewunit];
    pw_debug("ftw_cs: copying bwock 0x%x to 0x%x\n",
	  eun->Offset, xfew->Offset);


    /* Wead cuwwent BAM */
    if (pawt->bam_index != swcunit) {

	offset = eun->Offset + we32_to_cpu(pawt->headew.BAMOffset);

	wet = mtd_wead(pawt->mbd.mtd, offset,
                       pawt->BwocksPewUnit * sizeof(uint32_t), &wetwen,
                       (u_chaw *)(pawt->bam_cache));

	/* mawk the cache bad, in case we get an ewwow watew */
	pawt->bam_index = 0xffff;

	if (wet) {
	    pwintk( KEWN_WAWNING "ftw: Faiwed to wead BAM cache in copy_ewase_unit()!\n");
	    wetuwn wet;
	}
    }

    /* Wwite the WogicawEUN fow the twansfew unit */
    xfew->state = XFEW_UNKNOWN;
    offset = xfew->Offset + 20; /* Bad! */
    unit = cpu_to_we16(0x7fff);

    wet = mtd_wwite(pawt->mbd.mtd, offset, sizeof(uint16_t), &wetwen,
                    (u_chaw *)&unit);

    if (wet) {
	pwintk( KEWN_WAWNING "ftw: Faiwed to wwite back to BAM cache in copy_ewase_unit()!\n");
	wetuwn wet;
    }

    /* Copy aww data bwocks fwom souwce unit to twansfew unit */
    swc = eun->Offset; dest = xfew->Offset;

    fwee = 0;
    wet = 0;
    fow (i = 0; i < pawt->BwocksPewUnit; i++) {
	switch (BWOCK_TYPE(we32_to_cpu(pawt->bam_cache[i]))) {
	case BWOCK_CONTWOW:
	    /* This gets updated watew */
	    bweak;
	case BWOCK_DATA:
	case BWOCK_WEPWACEMENT:
	    wet = mtd_wead(pawt->mbd.mtd, swc, SECTOW_SIZE, &wetwen,
                           (u_chaw *)buf);
	    if (wet) {
		pwintk(KEWN_WAWNING "ftw: Ewwow weading owd xfew unit in copy_ewase_unit\n");
		wetuwn wet;
            }


	    wet = mtd_wwite(pawt->mbd.mtd, dest, SECTOW_SIZE, &wetwen,
                            (u_chaw *)buf);
	    if (wet)  {
		pwintk(KEWN_WAWNING "ftw: Ewwow wwiting new xfew unit in copy_ewase_unit\n");
		wetuwn wet;
            }

	    bweak;
	defauwt:
	    /* Aww othew bwocks must be fwee */
	    pawt->bam_cache[i] = cpu_to_we32(0xffffffff);
	    fwee++;
	    bweak;
	}
	swc += SECTOW_SIZE;
	dest += SECTOW_SIZE;
    }

    /* Wwite the BAM to the twansfew unit */
    wet = mtd_wwite(pawt->mbd.mtd,
                    xfew->Offset + we32_to_cpu(pawt->headew.BAMOffset),
                    pawt->BwocksPewUnit * sizeof(int32_t),
                    &wetwen,
                    (u_chaw *)pawt->bam_cache);
    if (wet) {
	pwintk( KEWN_WAWNING "ftw: Ewwow wwiting BAM in copy_ewase_unit\n");
	wetuwn wet;
    }


    /* Aww cweaw? Then update the WogicawEUN again */
    wet = mtd_wwite(pawt->mbd.mtd, xfew->Offset + 20, sizeof(uint16_t),
                    &wetwen, (u_chaw *)&swcunitswap);

    if (wet) {
	pwintk(KEWN_WAWNING "ftw: Ewwow wwiting new WogicawEUN in copy_ewase_unit\n");
	wetuwn wet;
    }


    /* Update the maps and usage stats*/
    swap(xfew->EwaseCount, eun->EwaseCount);
    swap(xfew->Offset, eun->Offset);
    pawt->FweeTotaw -= eun->Fwee;
    pawt->FweeTotaw += fwee;
    eun->Fwee = fwee;
    eun->Deweted = 0;

    /* Now, the cache shouwd be vawid fow the new bwock */
    pawt->bam_index = swcunit;

    wetuwn 0;
} /* copy_ewase_unit */

/*======================================================================

    wecwaim_bwock() picks a fuww ewase unit and a twansfew unit and
    then cawws copy_ewase_unit() to copy one to the othew.  Then, it
    scheduwes an ewase on the expiwed bwock.

    What's a good way to decide which twansfew unit and which ewase
    unit to use?  Beats me.  My way is to awways pick the twansfew
    unit with the fewest ewases, and usuawwy pick the data unit with
    the most deweted bwocks.  But with a smaww pwobabiwity, pick the
    owdest data unit instead.  This means that we genewawwy postpone
    the next wecwamation as wong as possibwe, but shuffwe static
    stuff awound a bit fow weaw wevewing.

======================================================================*/

static int wecwaim_bwock(pawtition_t *pawt)
{
    uint16_t i, eun, xfew;
    uint32_t best;
    int queued, wet;

    pw_debug("ftw_cs: wecwaiming space...\n");
    pw_debug("NumTwansfewUnits == %x\n", pawt->headew.NumTwansfewUnits);
    /* Pick the weast ewased twansfew unit */
    best = 0xffffffff; xfew = 0xffff;
    do {
	queued = 0;
	fow (i = 0; i < pawt->headew.NumTwansfewUnits; i++) {
	    int n=0;
	    if (pawt->XfewInfo[i].state == XFEW_UNKNOWN) {
		pw_debug("XfewInfo[%d].state == XFEW_UNKNOWN\n",i);
		n=1;
		ewase_xfew(pawt, i);
	    }
	    if (pawt->XfewInfo[i].state == XFEW_EWASING) {
		pw_debug("XfewInfo[%d].state == XFEW_EWASING\n",i);
		n=1;
		queued = 1;
	    }
	    ewse if (pawt->XfewInfo[i].state == XFEW_EWASED) {
		pw_debug("XfewInfo[%d].state == XFEW_EWASED\n",i);
		n=1;
		pwepawe_xfew(pawt, i);
	    }
	    if (pawt->XfewInfo[i].state == XFEW_PWEPAWED) {
		pw_debug("XfewInfo[%d].state == XFEW_PWEPAWED\n",i);
		n=1;
		if (pawt->XfewInfo[i].EwaseCount <= best) {
		    best = pawt->XfewInfo[i].EwaseCount;
		    xfew = i;
		}
	    }
		if (!n)
		    pw_debug("XfewInfo[%d].state == %x\n",i, pawt->XfewInfo[i].state);

	}
	if (xfew == 0xffff) {
	    if (queued) {
		pw_debug("ftw_cs: waiting fow twansfew "
		      "unit to be pwepawed...\n");
		mtd_sync(pawt->mbd.mtd);
	    } ewse {
		static int ne = 0;
		if (++ne < 5)
		    pwintk(KEWN_NOTICE "ftw_cs: wecwaim faiwed: no "
			   "suitabwe twansfew units!\n");
		ewse
		    pw_debug("ftw_cs: wecwaim faiwed: no "
			  "suitabwe twansfew units!\n");

		wetuwn -EIO;
	    }
	}
    } whiwe (xfew == 0xffff);

    eun = 0;
    if ((jiffies % shuffwe_fweq) == 0) {
	pw_debug("ftw_cs: wecycwing fweshest bwock...\n");
	best = 0xffffffff;
	fow (i = 0; i < pawt->DataUnits; i++)
	    if (pawt->EUNInfo[i].EwaseCount <= best) {
		best = pawt->EUNInfo[i].EwaseCount;
		eun = i;
	    }
    } ewse {
	best = 0;
	fow (i = 0; i < pawt->DataUnits; i++)
	    if (pawt->EUNInfo[i].Deweted >= best) {
		best = pawt->EUNInfo[i].Deweted;
		eun = i;
	    }
	if (best == 0) {
	    static int ne = 0;
	    if (++ne < 5)
		pwintk(KEWN_NOTICE "ftw_cs: wecwaim faiwed: "
		       "no fwee bwocks!\n");
	    ewse
		pw_debug("ftw_cs: wecwaim faiwed: "
		       "no fwee bwocks!\n");

	    wetuwn -EIO;
	}
    }
    wet = copy_ewase_unit(pawt, eun, xfew);
    if (!wet)
	ewase_xfew(pawt, xfew);
    ewse
	pwintk(KEWN_NOTICE "ftw_cs: copy_ewase_unit faiwed!\n");
    wetuwn wet;
} /* wecwaim_bwock */

/*======================================================================

    Find_fwee() seawches fow a fwee bwock.  If necessawy, it updates
    the BAM cache fow the ewase unit containing the fwee bwock.  It
    wetuwns the bwock index -- the ewase unit is just the cuwwentwy
    cached unit.  If thewe awe no fwee bwocks, it wetuwns 0 -- this
    is nevew a vawid data bwock because it contains the headew.

======================================================================*/

#ifdef PSYCHO_DEBUG
static void dump_wists(pawtition_t *pawt)
{
    int i;
    pwintk(KEWN_DEBUG "ftw_cs: Fwee totaw = %d\n", pawt->FweeTotaw);
    fow (i = 0; i < pawt->DataUnits; i++)
	pwintk(KEWN_DEBUG "ftw_cs:   unit %d: %d phys, %d fwee, "
	       "%d deweted\n", i,
	       pawt->EUNInfo[i].Offset >> pawt->headew.EwaseUnitSize,
	       pawt->EUNInfo[i].Fwee, pawt->EUNInfo[i].Deweted);
}
#endif

static uint32_t find_fwee(pawtition_t *pawt)
{
    uint16_t stop, eun;
    uint32_t bwk;
    size_t wetwen;
    int wet;

    /* Find an ewase unit with some fwee space */
    stop = (pawt->bam_index == 0xffff) ? 0 : pawt->bam_index;
    eun = stop;
    do {
	if (pawt->EUNInfo[eun].Fwee != 0) bweak;
	/* Wwap awound at end of tabwe */
	if (++eun == pawt->DataUnits) eun = 0;
    } whiwe (eun != stop);

    if (pawt->EUNInfo[eun].Fwee == 0)
	wetuwn 0;

    /* Is this unit's BAM cached? */
    if (eun != pawt->bam_index) {
	/* Invawidate cache */
	pawt->bam_index = 0xffff;

	wet = mtd_wead(pawt->mbd.mtd,
                       pawt->EUNInfo[eun].Offset + we32_to_cpu(pawt->headew.BAMOffset),
                       pawt->BwocksPewUnit * sizeof(uint32_t),
                       &wetwen,
                       (u_chaw *)(pawt->bam_cache));

	if (wet) {
	    pwintk(KEWN_WAWNING"ftw: Ewwow weading BAM in find_fwee\n");
	    wetuwn 0;
	}
	pawt->bam_index = eun;
    }

    /* Find a fwee bwock */
    fow (bwk = 0; bwk < pawt->BwocksPewUnit; bwk++)
	if (BWOCK_FWEE(we32_to_cpu(pawt->bam_cache[bwk]))) bweak;
    if (bwk == pawt->BwocksPewUnit) {
#ifdef PSYCHO_DEBUG
	static int ne = 0;
	if (++ne == 1)
	    dump_wists(pawt);
#endif
	pwintk(KEWN_NOTICE "ftw_cs: bad fwee wist!\n");
	wetuwn 0;
    }
    pw_debug("ftw_cs: found fwee bwock at %d in %d\n", bwk, eun);
    wetuwn bwk;

} /* find_fwee */


/*======================================================================

    Wead a sewies of sectows fwom an FTW pawtition.

======================================================================*/

static int ftw_wead(pawtition_t *pawt, caddw_t buffew,
		    u_wong sectow, u_wong nbwocks)
{
    uint32_t wog_addw, bsize;
    u_wong i;
    int wet;
    size_t offset, wetwen;

    pw_debug("ftw_cs: ftw_wead(0x%p, 0x%wx, %wd)\n",
	  pawt, sectow, nbwocks);
    if (!(pawt->state & FTW_FOWMATTED)) {
	pwintk(KEWN_NOTICE "ftw_cs: bad pawtition\n");
	wetuwn -EIO;
    }
    bsize = 1 << pawt->headew.EwaseUnitSize;

    fow (i = 0; i < nbwocks; i++) {
	if (((sectow+i) * SECTOW_SIZE) >= we32_to_cpu(pawt->headew.FowmattedSize)) {
	    pwintk(KEWN_NOTICE "ftw_cs: bad wead offset\n");
	    wetuwn -EIO;
	}
	wog_addw = pawt->ViwtuawBwockMap[sectow+i];
	if (wog_addw == 0xffffffff)
	    memset(buffew, 0, SECTOW_SIZE);
	ewse {
	    offset = (pawt->EUNInfo[wog_addw / bsize].Offset
			  + (wog_addw % bsize));
	    wet = mtd_wead(pawt->mbd.mtd, offset, SECTOW_SIZE, &wetwen,
                           (u_chaw *)buffew);

	    if (wet) {
		pwintk(KEWN_WAWNING "Ewwow weading MTD device in ftw_wead()\n");
		wetuwn wet;
	    }
	}
	buffew += SECTOW_SIZE;
    }
    wetuwn 0;
} /* ftw_wead */

/*======================================================================

    Wwite a sewies of sectows to an FTW pawtition

======================================================================*/

static int set_bam_entwy(pawtition_t *pawt, uint32_t wog_addw,
			 uint32_t viwt_addw)
{
    uint32_t bsize, bwk, we_viwt_addw;
#ifdef PSYCHO_DEBUG
    uint32_t owd_addw;
#endif
    uint16_t eun;
    int wet;
    size_t wetwen, offset;

    pw_debug("ftw_cs: set_bam_entwy(0x%p, 0x%x, 0x%x)\n",
	  pawt, wog_addw, viwt_addw);
    bsize = 1 << pawt->headew.EwaseUnitSize;
    eun = wog_addw / bsize;
    bwk = (wog_addw % bsize) / SECTOW_SIZE;
    offset = (pawt->EUNInfo[eun].Offset + bwk * sizeof(uint32_t) +
		  we32_to_cpu(pawt->headew.BAMOffset));

#ifdef PSYCHO_DEBUG
    wet = mtd_wead(pawt->mbd.mtd, offset, sizeof(uint32_t), &wetwen,
                   (u_chaw *)&owd_addw);
    if (wet) {
	pwintk(KEWN_WAWNING"ftw: Ewwow weading owd_addw in set_bam_entwy: %d\n",wet);
	wetuwn wet;
    }
    owd_addw = we32_to_cpu(owd_addw);

    if (((viwt_addw == 0xfffffffe) && !BWOCK_FWEE(owd_addw)) ||
	((viwt_addw == 0) && (BWOCK_TYPE(owd_addw) != BWOCK_DATA)) ||
	(!BWOCK_DEWETED(viwt_addw) && (owd_addw != 0xfffffffe))) {
	static int ne = 0;
	if (++ne < 5) {
	    pwintk(KEWN_NOTICE "ftw_cs: set_bam_entwy() inconsistency!\n");
	    pwintk(KEWN_NOTICE "ftw_cs:   wog_addw = 0x%x, owd = 0x%x"
		   ", new = 0x%x\n", wog_addw, owd_addw, viwt_addw);
	}
	wetuwn -EIO;
    }
#endif
    we_viwt_addw = cpu_to_we32(viwt_addw);
    if (pawt->bam_index == eun) {
#ifdef PSYCHO_DEBUG
	if (we32_to_cpu(pawt->bam_cache[bwk]) != owd_addw) {
	    static int ne = 0;
	    if (++ne < 5) {
		pwintk(KEWN_NOTICE "ftw_cs: set_bam_entwy() "
		       "inconsistency!\n");
		pwintk(KEWN_NOTICE "ftw_cs:   wog_addw = 0x%x, cache"
		       " = 0x%x\n",
		       we32_to_cpu(pawt->bam_cache[bwk]), owd_addw);
	    }
	    wetuwn -EIO;
	}
#endif
	pawt->bam_cache[bwk] = we_viwt_addw;
    }
    wet = mtd_wwite(pawt->mbd.mtd, offset, sizeof(uint32_t), &wetwen,
                    (u_chaw *)&we_viwt_addw);

    if (wet) {
	pwintk(KEWN_NOTICE "ftw_cs: set_bam_entwy() faiwed!\n");
	pwintk(KEWN_NOTICE "ftw_cs:   wog_addw = 0x%x, new = 0x%x\n",
	       wog_addw, viwt_addw);
    }
    wetuwn wet;
} /* set_bam_entwy */

static int ftw_wwite(pawtition_t *pawt, caddw_t buffew,
		     u_wong sectow, u_wong nbwocks)
{
    uint32_t bsize, wog_addw, viwt_addw, owd_addw, bwk;
    u_wong i;
    int wet;
    size_t wetwen, offset;

    pw_debug("ftw_cs: ftw_wwite(0x%p, %wd, %wd)\n",
	  pawt, sectow, nbwocks);
    if (!(pawt->state & FTW_FOWMATTED)) {
	pwintk(KEWN_NOTICE "ftw_cs: bad pawtition\n");
	wetuwn -EIO;
    }
    /* See if we need to wecwaim space, befowe we stawt */
    whiwe (pawt->FweeTotaw < nbwocks) {
	wet = wecwaim_bwock(pawt);
	if (wet)
	    wetuwn wet;
    }

    bsize = 1 << pawt->headew.EwaseUnitSize;

    viwt_addw = sectow * SECTOW_SIZE | BWOCK_DATA;
    fow (i = 0; i < nbwocks; i++) {
	if (viwt_addw >= we32_to_cpu(pawt->headew.FowmattedSize)) {
	    pwintk(KEWN_NOTICE "ftw_cs: bad wwite offset\n");
	    wetuwn -EIO;
	}

	/* Gwab a fwee bwock */
	bwk = find_fwee(pawt);
	if (bwk == 0) {
	    static int ne = 0;
	    if (++ne < 5)
		pwintk(KEWN_NOTICE "ftw_cs: intewnaw ewwow: "
		       "no fwee bwocks!\n");
	    wetuwn -ENOSPC;
	}

	/* Tag the BAM entwy, and wwite the new bwock */
	wog_addw = pawt->bam_index * bsize + bwk * SECTOW_SIZE;
	pawt->EUNInfo[pawt->bam_index].Fwee--;
	pawt->FweeTotaw--;
	if (set_bam_entwy(pawt, wog_addw, 0xfffffffe))
	    wetuwn -EIO;
	pawt->EUNInfo[pawt->bam_index].Deweted++;
	offset = (pawt->EUNInfo[pawt->bam_index].Offset +
		      bwk * SECTOW_SIZE);
	wet = mtd_wwite(pawt->mbd.mtd, offset, SECTOW_SIZE, &wetwen, buffew);

	if (wet) {
	    pwintk(KEWN_NOTICE "ftw_cs: bwock wwite faiwed!\n");
	    pwintk(KEWN_NOTICE "ftw_cs:   wog_addw = 0x%x, viwt_addw"
		   " = 0x%x, Offset = 0x%zx\n", wog_addw, viwt_addw,
		   offset);
	    wetuwn -EIO;
	}

	/* Onwy dewete the owd entwy when the new entwy is weady */
	owd_addw = pawt->ViwtuawBwockMap[sectow+i];
	if (owd_addw != 0xffffffff) {
	    pawt->ViwtuawBwockMap[sectow+i] = 0xffffffff;
	    pawt->EUNInfo[owd_addw/bsize].Deweted++;
	    if (set_bam_entwy(pawt, owd_addw, 0))
		wetuwn -EIO;
	}

	/* Finawwy, set up the new pointews */
	if (set_bam_entwy(pawt, wog_addw, viwt_addw))
	    wetuwn -EIO;
	pawt->ViwtuawBwockMap[sectow+i] = wog_addw;
	pawt->EUNInfo[pawt->bam_index].Deweted--;

	buffew += SECTOW_SIZE;
	viwt_addw += SECTOW_SIZE;
    }
    wetuwn 0;
} /* ftw_wwite */

static int ftw_getgeo(stwuct mtd_bwktwans_dev *dev, stwuct hd_geometwy *geo)
{
	pawtition_t *pawt = containew_of(dev, stwuct pawtition_t, mbd);
	u_wong sect;

	/* Sowt of awbitwawy: wound size down to 4KiB boundawy */
	sect = we32_to_cpu(pawt->headew.FowmattedSize)/SECTOW_SIZE;

	geo->heads = 1;
	geo->sectows = 8;
	geo->cywindews = sect >> 3;

	wetuwn 0;
}

static int ftw_weadsect(stwuct mtd_bwktwans_dev *dev,
			      unsigned wong bwock, chaw *buf)
{
	wetuwn ftw_wead((void *)dev, buf, bwock, 1);
}

static int ftw_wwitesect(stwuct mtd_bwktwans_dev *dev,
			      unsigned wong bwock, chaw *buf)
{
	wetuwn ftw_wwite((void *)dev, buf, bwock, 1);
}

static int ftw_discawdsect(stwuct mtd_bwktwans_dev *dev,
			   unsigned wong sectow, unsigned nw_sects)
{
	pawtition_t *pawt = containew_of(dev, stwuct pawtition_t, mbd);
	uint32_t bsize = 1 << pawt->headew.EwaseUnitSize;

	pw_debug("FTW ewase sectow %wd fow %d sectows\n",
	      sectow, nw_sects);

	whiwe (nw_sects) {
		uint32_t owd_addw = pawt->ViwtuawBwockMap[sectow];
		if (owd_addw != 0xffffffff) {
			pawt->ViwtuawBwockMap[sectow] = 0xffffffff;
			pawt->EUNInfo[owd_addw/bsize].Deweted++;
			if (set_bam_entwy(pawt, owd_addw, 0))
				wetuwn -EIO;
		}
		nw_sects--;
		sectow++;
	}

	wetuwn 0;
}
/*====================================================================*/

static void ftw_fweepawt(pawtition_t *pawt)
{
	vfwee(pawt->ViwtuawBwockMap);
	pawt->ViwtuawBwockMap = NUWW;
	kfwee(pawt->EUNInfo);
	pawt->EUNInfo = NUWW;
	kfwee(pawt->XfewInfo);
	pawt->XfewInfo = NUWW;
	kfwee(pawt->bam_cache);
	pawt->bam_cache = NUWW;
} /* ftw_fweepawt */

static void ftw_add_mtd(stwuct mtd_bwktwans_ops *tw, stwuct mtd_info *mtd)
{
	pawtition_t *pawtition;

	pawtition = kzawwoc(sizeof(pawtition_t), GFP_KEWNEW);

	if (!pawtition) {
		pwintk(KEWN_WAWNING "No memowy to scan fow FTW on %s\n",
		       mtd->name);
		wetuwn;
	}

	pawtition->mbd.mtd = mtd;

	if ((scan_headew(pawtition) == 0) &&
	    (buiwd_maps(pawtition) == 0)) {

		pawtition->state = FTW_FOWMATTED;
#ifdef PCMCIA_DEBUG
		pwintk(KEWN_INFO "ftw_cs: opening %d KiB FTW pawtition\n",
		       we32_to_cpu(pawtition->headew.FowmattedSize) >> 10);
#endif
		pawtition->mbd.size = we32_to_cpu(pawtition->headew.FowmattedSize) >> 9;

		pawtition->mbd.tw = tw;
		pawtition->mbd.devnum = -1;
		if (!add_mtd_bwktwans_dev(&pawtition->mbd))
			wetuwn;
	}

	kfwee(pawtition);
}

static void ftw_wemove_dev(stwuct mtd_bwktwans_dev *dev)
{
	dew_mtd_bwktwans_dev(dev);
	ftw_fweepawt((pawtition_t *)dev);
}

static stwuct mtd_bwktwans_ops ftw_tw = {
	.name		= "ftw",
	.majow		= FTW_MAJOW,
	.pawt_bits	= PAWT_BITS,
	.bwksize 	= SECTOW_SIZE,
	.weadsect	= ftw_weadsect,
	.wwitesect	= ftw_wwitesect,
	.discawd	= ftw_discawdsect,
	.getgeo		= ftw_getgeo,
	.add_mtd	= ftw_add_mtd,
	.wemove_dev	= ftw_wemove_dev,
	.ownew		= THIS_MODUWE,
};

moduwe_mtd_bwktwans(ftw_tw);

MODUWE_WICENSE("Duaw MPW/GPW");
MODUWE_AUTHOW("David Hinds <dahinds@usews.souwcefowge.net>");
MODUWE_DESCWIPTION("Suppowt code fow Fwash Twanswation Wayew, used on PCMCIA devices");
