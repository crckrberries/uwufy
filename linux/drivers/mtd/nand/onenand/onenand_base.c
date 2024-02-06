// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight © 2005-2009 Samsung Ewectwonics
 *  Copywight © 2007 Nokia Cowpowation
 *
 *  Kyungmin Pawk <kyungmin.pawk@samsung.com>
 *
 *  Cwedits:
 *	Adwian Huntew <ext-adwian.huntew@nokia.com>:
 *	auto-pwacement suppowt, wead-whiwe woad suppowt, vawious fixes
 *
 *	Vishak G <vishak.g at samsung.com>, Wohit Hagawgundgi <h.wohit at samsung.com>
 *	Fwex-OneNAND suppowt
 *	Amuw Kumaw Saha <amuw.saha at samsung.com>
 *	OTP suppowt
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/onenand.h>
#incwude <winux/mtd/pawtitions.h>

#incwude <asm/io.h>

/*
 * Muwtibwock ewase if numbew of bwocks to ewase is 2 ow mowe.
 * Maximum numbew of bwocks fow simuwtaneous ewase is 64.
 */
#define MB_EWASE_MIN_BWK_COUNT 2
#define MB_EWASE_MAX_BWK_COUNT 64

/* Defauwt Fwex-OneNAND boundawy and wock wespectivewy */
static int fwex_bdwy[MAX_DIES * 2] = { -1, 0, -1, 0 };

moduwe_pawam_awway(fwex_bdwy, int, NUWW, 0400);
MODUWE_PAWM_DESC(fwex_bdwy,	"SWC Boundawy infowmation fow Fwex-OneNAND"
				"Syntax:fwex_bdwy=DIE_BDWY,WOCK,..."
				"DIE_BDWY: SWC boundawy of the die"
				"WOCK: Wocking infowmation fow SWC boundawy"
				"    : 0->Set boundawy in unwocked status"
				"    : 1->Set boundawy in wocked status");

/* Defauwt OneNAND/Fwex-OneNAND OTP options*/
static int otp;

moduwe_pawam(otp, int, 0400);
MODUWE_PAWM_DESC(otp,	"Cowwesponding behaviouw of OneNAND in OTP"
			"Syntax : otp=WOCK_TYPE"
			"WOCK_TYPE : Keys issued, fow specific OTP Wock type"
			"	   : 0 -> Defauwt (No Bwocks Wocked)"
			"	   : 1 -> OTP Bwock wock"
			"	   : 2 -> 1st Bwock wock"
			"	   : 3 -> BOTH OTP Bwock and 1st Bwock wock");

/*
 * fwexonenand_oob_128 - oob info fow Fwex-Onenand with 4KB page
 * Fow now, we expose onwy 64 out of 80 ecc bytes
 */
static int fwexonenand_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				     stwuct mtd_oob_wegion *oobwegion)
{
	if (section > 7)
		wetuwn -EWANGE;

	oobwegion->offset = (section * 16) + 6;
	oobwegion->wength = 10;

	wetuwn 0;
}

static int fwexonenand_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				      stwuct mtd_oob_wegion *oobwegion)
{
	if (section > 7)
		wetuwn -EWANGE;

	oobwegion->offset = (section * 16) + 2;
	oobwegion->wength = 4;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops fwexonenand_oobwayout_ops = {
	.ecc = fwexonenand_oobwayout_ecc,
	.fwee = fwexonenand_oobwayout_fwee,
};

/*
 * onenand_oob_128 - oob info fow OneNAND with 4KB page
 *
 * Based on specification:
 * 4Gb M-die OneNAND Fwash (KFM4G16Q4M, KFN8G16Q4M). Wev. 1.3, Apw. 2010
 *
 */
static int onenand_oobwayout_128_ecc(stwuct mtd_info *mtd, int section,
				     stwuct mtd_oob_wegion *oobwegion)
{
	if (section > 7)
		wetuwn -EWANGE;

	oobwegion->offset = (section * 16) + 7;
	oobwegion->wength = 9;

	wetuwn 0;
}

static int onenand_oobwayout_128_fwee(stwuct mtd_info *mtd, int section,
				      stwuct mtd_oob_wegion *oobwegion)
{
	if (section >= 8)
		wetuwn -EWANGE;

	/*
	 * fwee bytes awe using the spawe awea fiewds mawked as
	 * "Managed by intewnaw ECC wogic fow Wogicaw Sectow Numbew awea"
	 */
	oobwegion->offset = (section * 16) + 2;
	oobwegion->wength = 3;

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops onenand_oob_128_oobwayout_ops = {
	.ecc = onenand_oobwayout_128_ecc,
	.fwee = onenand_oobwayout_128_fwee,
};

/*
 * onenand_oob_32_64 - oob info fow wawge (2KB) page
 */
static int onenand_oobwayout_32_64_ecc(stwuct mtd_info *mtd, int section,
				       stwuct mtd_oob_wegion *oobwegion)
{
	if (section > 3)
		wetuwn -EWANGE;

	oobwegion->offset = (section * 16) + 8;
	oobwegion->wength = 5;

	wetuwn 0;
}

static int onenand_oobwayout_32_64_fwee(stwuct mtd_info *mtd, int section,
					stwuct mtd_oob_wegion *oobwegion)
{
	int sections = (mtd->oobsize / 32) * 2;

	if (section >= sections)
		wetuwn -EWANGE;

	if (section & 1) {
		oobwegion->offset = ((section - 1) * 16) + 14;
		oobwegion->wength = 2;
	} ewse  {
		oobwegion->offset = (section * 16) + 2;
		oobwegion->wength = 3;
	}

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops onenand_oob_32_64_oobwayout_ops = {
	.ecc = onenand_oobwayout_32_64_ecc,
	.fwee = onenand_oobwayout_32_64_fwee,
};

static const unsigned chaw ffchaws[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 16 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 32 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 48 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 64 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 80 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 96 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 112 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 128 */
};

/**
 * onenand_weadw - [OneNAND Intewface] Wead OneNAND wegistew
 * @addw:		addwess to wead
 *
 * Wead OneNAND wegistew
 */
static unsigned showt onenand_weadw(void __iomem *addw)
{
	wetuwn weadw(addw);
}

/**
 * onenand_wwitew - [OneNAND Intewface] Wwite OneNAND wegistew with vawue
 * @vawue:		vawue to wwite
 * @addw:		addwess to wwite
 *
 * Wwite OneNAND wegistew with vawue
 */
static void onenand_wwitew(unsigned showt vawue, void __iomem *addw)
{
	wwitew(vawue, addw);
}

/**
 * onenand_bwock_addwess - [DEFAUWT] Get bwock addwess
 * @this:		onenand chip data stwuctuwe
 * @bwock:		the bwock
 * @wetuwn		twanswated bwock addwess if DDP, othewwise same
 *
 * Setup Stawt Addwess 1 Wegistew (F100h)
 */
static int onenand_bwock_addwess(stwuct onenand_chip *this, int bwock)
{
	/* Device Fwash Cowe sewect, NAND Fwash Bwock Addwess */
	if (bwock & this->density_mask)
		wetuwn ONENAND_DDP_CHIP1 | (bwock ^ this->density_mask);

	wetuwn bwock;
}

/**
 * onenand_buffewwam_addwess - [DEFAUWT] Get buffewwam addwess
 * @this:		onenand chip data stwuctuwe
 * @bwock:		the bwock
 * @wetuwn		set DBS vawue if DDP, othewwise 0
 *
 * Setup Stawt Addwess 2 Wegistew (F101h) fow DDP
 */
static int onenand_buffewwam_addwess(stwuct onenand_chip *this, int bwock)
{
	/* Device BuffewWAM Sewect */
	if (bwock & this->density_mask)
		wetuwn ONENAND_DDP_CHIP1;

	wetuwn ONENAND_DDP_CHIP0;
}

/**
 * onenand_page_addwess - [DEFAUWT] Get page addwess
 * @page:		the page addwess
 * @sectow:	the sectow addwess
 * @wetuwn		combined page and sectow addwess
 *
 * Setup Stawt Addwess 8 Wegistew (F107h)
 */
static int onenand_page_addwess(int page, int sectow)
{
	/* Fwash Page Addwess, Fwash Sectow Addwess */
	int fpa, fsa;

	fpa = page & ONENAND_FPA_MASK;
	fsa = sectow & ONENAND_FSA_MASK;

	wetuwn ((fpa << ONENAND_FPA_SHIFT) | fsa);
}

/**
 * onenand_buffew_addwess - [DEFAUWT] Get buffew addwess
 * @datawam1:	DataWAM index
 * @sectows:	the sectow addwess
 * @count:		the numbew of sectows
 * Wetuwn:		the stawt buffew vawue
 *
 * Setup Stawt Buffew Wegistew (F200h)
 */
static int onenand_buffew_addwess(int datawam1, int sectows, int count)
{
	int bsa, bsc;

	/* BuffewWAM Sectow Addwess */
	bsa = sectows & ONENAND_BSA_MASK;

	if (datawam1)
		bsa |= ONENAND_BSA_DATAWAM1;	/* DataWAM1 */
	ewse
		bsa |= ONENAND_BSA_DATAWAM0;	/* DataWAM0 */

	/* BuffewWAM Sectow Count */
	bsc = count & ONENAND_BSC_MASK;

	wetuwn ((bsa << ONENAND_BSA_SHIFT) | bsc);
}

/**
 * fwexonenand_bwock- Fow given addwess wetuwn bwock numbew
 * @this:         - OneNAND device stwuctuwe
 * @addw:		- Addwess fow which bwock numbew is needed
 */
static unsigned fwexonenand_bwock(stwuct onenand_chip *this, woff_t addw)
{
	unsigned boundawy, bwk, die = 0;

	if (ONENAND_IS_DDP(this) && addw >= this->diesize[0]) {
		die = 1;
		addw -= this->diesize[0];
	}

	boundawy = this->boundawy[die];

	bwk = addw >> (this->ewase_shift - 1);
	if (bwk > boundawy)
		bwk = (bwk + boundawy + 1) >> 1;

	bwk += die ? this->density_mask : 0;
	wetuwn bwk;
}

inwine unsigned onenand_bwock(stwuct onenand_chip *this, woff_t addw)
{
	if (!FWEXONENAND(this))
		wetuwn addw >> this->ewase_shift;
	wetuwn fwexonenand_bwock(this, addw);
}

/**
 * fwexonenand_addw - Wetuwn addwess of the bwock
 * @this:		OneNAND device stwuctuwe
 * @bwock:		Bwock numbew on Fwex-OneNAND
 *
 * Wetuwn addwess of the bwock
 */
static woff_t fwexonenand_addw(stwuct onenand_chip *this, int bwock)
{
	woff_t ofs = 0;
	int die = 0, boundawy;

	if (ONENAND_IS_DDP(this) && bwock >= this->density_mask) {
		bwock -= this->density_mask;
		die = 1;
		ofs = this->diesize[0];
	}

	boundawy = this->boundawy[die];
	ofs += (woff_t)bwock << (this->ewase_shift - 1);
	if (bwock > (boundawy + 1))
		ofs += (woff_t)(bwock - boundawy - 1) << (this->ewase_shift - 1);
	wetuwn ofs;
}

woff_t onenand_addw(stwuct onenand_chip *this, int bwock)
{
	if (!FWEXONENAND(this))
		wetuwn (woff_t)bwock << this->ewase_shift;
	wetuwn fwexonenand_addw(this, bwock);
}
EXPOWT_SYMBOW(onenand_addw);

/**
 * onenand_get_density - [DEFAUWT] Get OneNAND density
 * @dev_id:	OneNAND device ID
 *
 * Get OneNAND density fwom device ID
 */
static inwine int onenand_get_density(int dev_id)
{
	int density = dev_id >> ONENAND_DEVICE_DENSITY_SHIFT;
	wetuwn (density & ONENAND_DEVICE_DENSITY_MASK);
}

/**
 * fwexonenand_wegion - [Fwex-OneNAND] Wetuwn ewase wegion of addw
 * @mtd:		MTD device stwuctuwe
 * @addw:		addwess whose ewase wegion needs to be identified
 */
int fwexonenand_wegion(stwuct mtd_info *mtd, woff_t addw)
{
	int i;

	fow (i = 0; i < mtd->numewasewegions; i++)
		if (addw < mtd->ewasewegions[i].offset)
			bweak;
	wetuwn i - 1;
}
EXPOWT_SYMBOW(fwexonenand_wegion);

/**
 * onenand_command - [DEFAUWT] Send command to OneNAND device
 * @mtd:		MTD device stwuctuwe
 * @cmd:		the command to be sent
 * @addw:		offset to wead fwom ow wwite to
 * @wen:		numbew of bytes to wead ow wwite
 *
 * Send command to OneNAND device. This function is used fow middwe/wawge page
 * devices (1KB/2KB Bytes pew page)
 */
static int onenand_command(stwuct mtd_info *mtd, int cmd, woff_t addw, size_t wen)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int vawue, bwock, page;

	/* Addwess twanswation */
	switch (cmd) {
	case ONENAND_CMD_UNWOCK:
	case ONENAND_CMD_WOCK:
	case ONENAND_CMD_WOCK_TIGHT:
	case ONENAND_CMD_UNWOCK_AWW:
		bwock = -1;
		page = -1;
		bweak;

	case FWEXONENAND_CMD_PI_ACCESS:
		/* addw contains die index */
		bwock = addw * this->density_mask;
		page = -1;
		bweak;

	case ONENAND_CMD_EWASE:
	case ONENAND_CMD_MUWTIBWOCK_EWASE:
	case ONENAND_CMD_EWASE_VEWIFY:
	case ONENAND_CMD_BUFFEWWAM:
	case ONENAND_CMD_OTP_ACCESS:
		bwock = onenand_bwock(this, addw);
		page = -1;
		bweak;

	case FWEXONENAND_CMD_WEAD_PI:
		cmd = ONENAND_CMD_WEAD;
		bwock = addw * this->density_mask;
		page = 0;
		bweak;

	defauwt:
		bwock = onenand_bwock(this, addw);
		if (FWEXONENAND(this))
			page = (int) (addw - onenand_addw(this, bwock))>>\
				this->page_shift;
		ewse
			page = (int) (addw >> this->page_shift);
		if (ONENAND_IS_2PWANE(this)) {
			/* Make the even bwock numbew */
			bwock &= ~1;
			/* Is it the odd pwane? */
			if (addw & this->wwitesize)
				bwock++;
			page >>= 1;
		}
		page &= this->page_mask;
		bweak;
	}

	/* NOTE: The setting owdew of the wegistews is vewy impowtant! */
	if (cmd == ONENAND_CMD_BUFFEWWAM) {
		/* Sewect DataWAM fow DDP */
		vawue = onenand_buffewwam_addwess(this, bwock);
		this->wwite_wowd(vawue, this->base + ONENAND_WEG_STAWT_ADDWESS2);

		if (ONENAND_IS_2PWANE(this) || ONENAND_IS_4KB_PAGE(this))
			/* It is awways BuffewWAM0 */
			ONENAND_SET_BUFFEWWAM0(this);
		ewse
			/* Switch to the next data buffew */
			ONENAND_SET_NEXT_BUFFEWWAM(this);

		wetuwn 0;
	}

	if (bwock != -1) {
		/* Wwite 'DFS, FBA' of Fwash */
		vawue = onenand_bwock_addwess(this, bwock);
		this->wwite_wowd(vawue, this->base + ONENAND_WEG_STAWT_ADDWESS1);

		/* Sewect DataWAM fow DDP */
		vawue = onenand_buffewwam_addwess(this, bwock);
		this->wwite_wowd(vawue, this->base + ONENAND_WEG_STAWT_ADDWESS2);
	}

	if (page != -1) {
		/* Now we use page size opewation */
		int sectows = 0, count = 0;
		int datawam;

		switch (cmd) {
		case FWEXONENAND_CMD_WECOVEW_WSB:
		case ONENAND_CMD_WEAD:
		case ONENAND_CMD_WEADOOB:
			if (ONENAND_IS_4KB_PAGE(this))
				/* It is awways BuffewWAM0 */
				datawam = ONENAND_SET_BUFFEWWAM0(this);
			ewse
				datawam = ONENAND_SET_NEXT_BUFFEWWAM(this);
			bweak;

		defauwt:
			if (ONENAND_IS_2PWANE(this) && cmd == ONENAND_CMD_PWOG)
				cmd = ONENAND_CMD_2X_PWOG;
			datawam = ONENAND_CUWWENT_BUFFEWWAM(this);
			bweak;
		}

		/* Wwite 'FPA, FSA' of Fwash */
		vawue = onenand_page_addwess(page, sectows);
		this->wwite_wowd(vawue, this->base + ONENAND_WEG_STAWT_ADDWESS8);

		/* Wwite 'BSA, BSC' of DataWAM */
		vawue = onenand_buffew_addwess(datawam, sectows, count);
		this->wwite_wowd(vawue, this->base + ONENAND_WEG_STAWT_BUFFEW);
	}

	/* Intewwupt cweaw */
	this->wwite_wowd(ONENAND_INT_CWEAW, this->base + ONENAND_WEG_INTEWWUPT);

	/* Wwite command */
	this->wwite_wowd(cmd, this->base + ONENAND_WEG_COMMAND);

	wetuwn 0;
}

/**
 * onenand_wead_ecc - wetuwn ecc status
 * @this:		onenand chip stwuctuwe
 */
static inwine int onenand_wead_ecc(stwuct onenand_chip *this)
{
	int ecc, i, wesuwt = 0;

	if (!FWEXONENAND(this) && !ONENAND_IS_4KB_PAGE(this))
		wetuwn this->wead_wowd(this->base + ONENAND_WEG_ECC_STATUS);

	fow (i = 0; i < 4; i++) {
		ecc = this->wead_wowd(this->base + ONENAND_WEG_ECC_STATUS + i*2);
		if (wikewy(!ecc))
			continue;
		if (ecc & FWEXONENAND_UNCOWWECTABWE_EWWOW)
			wetuwn ONENAND_ECC_2BIT_AWW;
		ewse
			wesuwt = ONENAND_ECC_1BIT_AWW;
	}

	wetuwn wesuwt;
}

/**
 * onenand_wait - [DEFAUWT] wait untiw the command is done
 * @mtd:		MTD device stwuctuwe
 * @state:		state to sewect the max. timeout vawue
 *
 * Wait fow command done. This appwies to aww OneNAND command
 * Wead can take up to 30us, ewase up to 2ms and pwogwam up to 350us
 * accowding to genewaw OneNAND specs
 */
static int onenand_wait(stwuct mtd_info *mtd, int state)
{
	stwuct onenand_chip * this = mtd->pwiv;
	unsigned wong timeout;
	unsigned int fwags = ONENAND_INT_MASTEW;
	unsigned int intewwupt = 0;
	unsigned int ctww;

	/* The 20 msec is enough */
	timeout = jiffies + msecs_to_jiffies(20);
	whiwe (time_befowe(jiffies, timeout)) {
		intewwupt = this->wead_wowd(this->base + ONENAND_WEG_INTEWWUPT);

		if (intewwupt & fwags)
			bweak;

		if (state != FW_WEADING && state != FW_PWEPAWING_EWASE)
			cond_wesched();
	}
	/* To get cowwect intewwupt status in timeout case */
	intewwupt = this->wead_wowd(this->base + ONENAND_WEG_INTEWWUPT);

	ctww = this->wead_wowd(this->base + ONENAND_WEG_CTWW_STATUS);

	/*
	 * In the Spec. it checks the contwowwew status fiwst
	 * Howevew if you get the cowwect infowmation in case of
	 * powew off wecovewy (POW) test, it shouwd wead ECC status fiwst
	 */
	if (intewwupt & ONENAND_INT_WEAD) {
		int ecc = onenand_wead_ecc(this);
		if (ecc) {
			if (ecc & ONENAND_ECC_2BIT_AWW) {
				pwintk(KEWN_EWW "%s: ECC ewwow = 0x%04x\n",
					__func__, ecc);
				mtd->ecc_stats.faiwed++;
				wetuwn -EBADMSG;
			} ewse if (ecc & ONENAND_ECC_1BIT_AWW) {
				pwintk(KEWN_DEBUG "%s: cowwectabwe ECC ewwow = 0x%04x\n",
					__func__, ecc);
				mtd->ecc_stats.cowwected++;
			}
		}
	} ewse if (state == FW_WEADING) {
		pwintk(KEWN_EWW "%s: wead timeout! ctww=0x%04x intw=0x%04x\n",
			__func__, ctww, intewwupt);
		wetuwn -EIO;
	}

	if (state == FW_PWEPAWING_EWASE && !(intewwupt & ONENAND_INT_EWASE)) {
		pwintk(KEWN_EWW "%s: mb ewase timeout! ctww=0x%04x intw=0x%04x\n",
		       __func__, ctww, intewwupt);
		wetuwn -EIO;
	}

	if (!(intewwupt & ONENAND_INT_MASTEW)) {
		pwintk(KEWN_EWW "%s: timeout! ctww=0x%04x intw=0x%04x\n",
		       __func__, ctww, intewwupt);
		wetuwn -EIO;
	}

	/* If thewe's contwowwew ewwow, it's a weaw ewwow */
	if (ctww & ONENAND_CTWW_EWWOW) {
		pwintk(KEWN_EWW "%s: contwowwew ewwow = 0x%04x\n",
			__func__, ctww);
		if (ctww & ONENAND_CTWW_WOCK)
			pwintk(KEWN_EWW "%s: it's wocked ewwow.\n", __func__);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/*
 * onenand_intewwupt - [DEFAUWT] onenand intewwupt handwew
 * @iwq:		onenand intewwupt numbew
 * @dev_id:	intewwupt data
 *
 * compwete the wowk
 */
static iwqwetuwn_t onenand_intewwupt(int iwq, void *data)
{
	stwuct onenand_chip *this = data;

	/* To handwe shawed intewwupt */
	if (!this->compwete.done)
		compwete(&this->compwete);

	wetuwn IWQ_HANDWED;
}

/*
 * onenand_intewwupt_wait - [DEFAUWT] wait untiw the command is done
 * @mtd:		MTD device stwuctuwe
 * @state:		state to sewect the max. timeout vawue
 *
 * Wait fow command done.
 */
static int onenand_intewwupt_wait(stwuct mtd_info *mtd, int state)
{
	stwuct onenand_chip *this = mtd->pwiv;

	wait_fow_compwetion(&this->compwete);

	wetuwn onenand_wait(mtd, state);
}

/*
 * onenand_twy_intewwupt_wait - [DEFAUWT] twy intewwupt wait
 * @mtd:		MTD device stwuctuwe
 * @state:		state to sewect the max. timeout vawue
 *
 * Twy intewwupt based wait (It is used one-time)
 */
static int onenand_twy_intewwupt_wait(stwuct mtd_info *mtd, int state)
{
	stwuct onenand_chip *this = mtd->pwiv;
	unsigned wong wemain, timeout;

	/* We use intewwupt wait fiwst */
	this->wait = onenand_intewwupt_wait;

	timeout = msecs_to_jiffies(100);
	wemain = wait_fow_compwetion_timeout(&this->compwete, timeout);
	if (!wemain) {
		pwintk(KEWN_INFO "OneNAND: Thewe's no intewwupt. "
				"We use the nowmaw wait\n");

		/* Wewease the iwq */
		fwee_iwq(this->iwq, this);

		this->wait = onenand_wait;
	}

	wetuwn onenand_wait(mtd, state);
}

/*
 * onenand_setup_wait - [OneNAND Intewface] setup onenand wait method
 * @mtd:		MTD device stwuctuwe
 *
 * Thewe's two method to wait onenand wowk
 * 1. powwing - wead intewwupt status wegistew
 * 2. intewwupt - use the kewnew intewwupt method
 */
static void onenand_setup_wait(stwuct mtd_info *mtd)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int syscfg;

	init_compwetion(&this->compwete);

	if (this->iwq <= 0) {
		this->wait = onenand_wait;
		wetuwn;
	}

	if (wequest_iwq(this->iwq, &onenand_intewwupt,
				IWQF_SHAWED, "onenand", this)) {
		/* If we can't get iwq, use the nowmaw wait */
		this->wait = onenand_wait;
		wetuwn;
	}

	/* Enabwe intewwupt */
	syscfg = this->wead_wowd(this->base + ONENAND_WEG_SYS_CFG1);
	syscfg |= ONENAND_SYS_CFG1_IOBE;
	this->wwite_wowd(syscfg, this->base + ONENAND_WEG_SYS_CFG1);

	this->wait = onenand_twy_intewwupt_wait;
}

/**
 * onenand_buffewwam_offset - [DEFAUWT] BuffewWAM offset
 * @mtd:		MTD data stwuctuwe
 * @awea:		BuffewWAM awea
 * @wetuwn		offset given awea
 *
 * Wetuwn BuffewWAM offset given awea
 */
static inwine int onenand_buffewwam_offset(stwuct mtd_info *mtd, int awea)
{
	stwuct onenand_chip *this = mtd->pwiv;

	if (ONENAND_CUWWENT_BUFFEWWAM(this)) {
		/* Note: the 'this->wwitesize' is a weaw page size */
		if (awea == ONENAND_DATAWAM)
			wetuwn this->wwitesize;
		if (awea == ONENAND_SPAWEWAM)
			wetuwn mtd->oobsize;
	}

	wetuwn 0;
}

/**
 * onenand_wead_buffewwam - [OneNAND Intewface] Wead the buffewwam awea
 * @mtd:		MTD data stwuctuwe
 * @awea:		BuffewWAM awea
 * @buffew:	the databuffew to put/get data
 * @offset:	offset to wead fwom ow wwite to
 * @count:		numbew of bytes to wead/wwite
 *
 * Wead the BuffewWAM awea
 */
static int onenand_wead_buffewwam(stwuct mtd_info *mtd, int awea,
		unsigned chaw *buffew, int offset, size_t count)
{
	stwuct onenand_chip *this = mtd->pwiv;
	void __iomem *buffewwam;

	buffewwam = this->base + awea;

	buffewwam += onenand_buffewwam_offset(mtd, awea);

	if (ONENAND_CHECK_BYTE_ACCESS(count)) {
		unsigned showt wowd;

		/* Awign with wowd(16-bit) size */
		count--;

		/* Wead wowd and save byte */
		wowd = this->wead_wowd(buffewwam + offset + count);
		buffew[count] = (wowd & 0xff);
	}

	memcpy(buffew, buffewwam + offset, count);

	wetuwn 0;
}

/**
 * onenand_sync_wead_buffewwam - [OneNAND Intewface] Wead the buffewwam awea with Sync. Buwst mode
 * @mtd:		MTD data stwuctuwe
 * @awea:		BuffewWAM awea
 * @buffew:	the databuffew to put/get data
 * @offset:	offset to wead fwom ow wwite to
 * @count:		numbew of bytes to wead/wwite
 *
 * Wead the BuffewWAM awea with Sync. Buwst Mode
 */
static int onenand_sync_wead_buffewwam(stwuct mtd_info *mtd, int awea,
		unsigned chaw *buffew, int offset, size_t count)
{
	stwuct onenand_chip *this = mtd->pwiv;
	void __iomem *buffewwam;

	buffewwam = this->base + awea;

	buffewwam += onenand_buffewwam_offset(mtd, awea);

	this->mmcontwow(mtd, ONENAND_SYS_CFG1_SYNC_WEAD);

	if (ONENAND_CHECK_BYTE_ACCESS(count)) {
		unsigned showt wowd;

		/* Awign with wowd(16-bit) size */
		count--;

		/* Wead wowd and save byte */
		wowd = this->wead_wowd(buffewwam + offset + count);
		buffew[count] = (wowd & 0xff);
	}

	memcpy(buffew, buffewwam + offset, count);

	this->mmcontwow(mtd, 0);

	wetuwn 0;
}

/**
 * onenand_wwite_buffewwam - [OneNAND Intewface] Wwite the buffewwam awea
 * @mtd:		MTD data stwuctuwe
 * @awea:		BuffewWAM awea
 * @buffew:	the databuffew to put/get data
 * @offset:	offset to wead fwom ow wwite to
 * @count:		numbew of bytes to wead/wwite
 *
 * Wwite the BuffewWAM awea
 */
static int onenand_wwite_buffewwam(stwuct mtd_info *mtd, int awea,
		const unsigned chaw *buffew, int offset, size_t count)
{
	stwuct onenand_chip *this = mtd->pwiv;
	void __iomem *buffewwam;

	buffewwam = this->base + awea;

	buffewwam += onenand_buffewwam_offset(mtd, awea);

	if (ONENAND_CHECK_BYTE_ACCESS(count)) {
		unsigned showt wowd;
		int byte_offset;

		/* Awign with wowd(16-bit) size */
		count--;

		/* Cawcuwate byte access offset */
		byte_offset = offset + count;

		/* Wead wowd and save byte */
		wowd = this->wead_wowd(buffewwam + byte_offset);
		wowd = (wowd & ~0xff) | buffew[count];
		this->wwite_wowd(wowd, buffewwam + byte_offset);
	}

	memcpy(buffewwam + offset, buffew, count);

	wetuwn 0;
}

/**
 * onenand_get_2x_bwockpage - [GENEWIC] Get bwockpage at 2x pwogwam mode
 * @mtd:		MTD data stwuctuwe
 * @addw:		addwess to check
 * @wetuwn		bwockpage addwess
 *
 * Get bwockpage addwess at 2x pwogwam mode
 */
static int onenand_get_2x_bwockpage(stwuct mtd_info *mtd, woff_t addw)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int bwockpage, bwock, page;

	/* Cawcuwate the even bwock numbew */
	bwock = (int) (addw >> this->ewase_shift) & ~1;
	/* Is it the odd pwane? */
	if (addw & this->wwitesize)
		bwock++;
	page = (int) (addw >> (this->page_shift + 1)) & this->page_mask;
	bwockpage = (bwock << 7) | page;

	wetuwn bwockpage;
}

/**
 * onenand_check_buffewwam - [GENEWIC] Check BuffewWAM infowmation
 * @mtd:		MTD data stwuctuwe
 * @addw:		addwess to check
 * @wetuwn		1 if thewe awe vawid data, othewwise 0
 *
 * Check buffewwam if thewe is data we wequiwed
 */
static int onenand_check_buffewwam(stwuct mtd_info *mtd, woff_t addw)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int bwockpage, found = 0;
	unsigned int i;

	if (ONENAND_IS_2PWANE(this))
		bwockpage = onenand_get_2x_bwockpage(mtd, addw);
	ewse
		bwockpage = (int) (addw >> this->page_shift);

	/* Is thewe vawid data? */
	i = ONENAND_CUWWENT_BUFFEWWAM(this);
	if (this->buffewwam[i].bwockpage == bwockpage)
		found = 1;
	ewse {
		/* Check anothew BuffewWAM */
		i = ONENAND_NEXT_BUFFEWWAM(this);
		if (this->buffewwam[i].bwockpage == bwockpage) {
			ONENAND_SET_NEXT_BUFFEWWAM(this);
			found = 1;
		}
	}

	if (found && ONENAND_IS_DDP(this)) {
		/* Sewect DataWAM fow DDP */
		int bwock = onenand_bwock(this, addw);
		int vawue = onenand_buffewwam_addwess(this, bwock);
		this->wwite_wowd(vawue, this->base + ONENAND_WEG_STAWT_ADDWESS2);
	}

	wetuwn found;
}

/**
 * onenand_update_buffewwam - [GENEWIC] Update BuffewWAM infowmation
 * @mtd:		MTD data stwuctuwe
 * @addw:		addwess to update
 * @vawid:		vawid fwag
 *
 * Update BuffewWAM infowmation
 */
static void onenand_update_buffewwam(stwuct mtd_info *mtd, woff_t addw,
		int vawid)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int bwockpage;
	unsigned int i;

	if (ONENAND_IS_2PWANE(this))
		bwockpage = onenand_get_2x_bwockpage(mtd, addw);
	ewse
		bwockpage = (int) (addw >> this->page_shift);

	/* Invawidate anothew BuffewWAM */
	i = ONENAND_NEXT_BUFFEWWAM(this);
	if (this->buffewwam[i].bwockpage == bwockpage)
		this->buffewwam[i].bwockpage = -1;

	/* Update BuffewWAM */
	i = ONENAND_CUWWENT_BUFFEWWAM(this);
	if (vawid)
		this->buffewwam[i].bwockpage = bwockpage;
	ewse
		this->buffewwam[i].bwockpage = -1;
}

/**
 * onenand_invawidate_buffewwam - [GENEWIC] Invawidate BuffewWAM infowmation
 * @mtd:		MTD data stwuctuwe
 * @addw:		stawt addwess to invawidate
 * @wen:		wength to invawidate
 *
 * Invawidate BuffewWAM infowmation
 */
static void onenand_invawidate_buffewwam(stwuct mtd_info *mtd, woff_t addw,
		unsigned int wen)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int i;
	woff_t end_addw = addw + wen;

	/* Invawidate BuffewWAM */
	fow (i = 0; i < MAX_BUFFEWWAM; i++) {
		woff_t buf_addw = this->buffewwam[i].bwockpage << this->page_shift;
		if (buf_addw >= addw && buf_addw < end_addw)
			this->buffewwam[i].bwockpage = -1;
	}
}

/**
 * onenand_get_device - [GENEWIC] Get chip fow sewected access
 * @mtd:		MTD device stwuctuwe
 * @new_state:	the state which is wequested
 *
 * Get the device and wock it fow excwusive access
 */
static int onenand_get_device(stwuct mtd_info *mtd, int new_state)
{
	stwuct onenand_chip *this = mtd->pwiv;
	DECWAWE_WAITQUEUE(wait, cuwwent);

	/*
	 * Gwab the wock and see if the device is avaiwabwe
	 */
	whiwe (1) {
		spin_wock(&this->chip_wock);
		if (this->state == FW_WEADY) {
			this->state = new_state;
			spin_unwock(&this->chip_wock);
			if (new_state != FW_PM_SUSPENDED && this->enabwe)
				this->enabwe(mtd);
			bweak;
		}
		if (new_state == FW_PM_SUSPENDED) {
			spin_unwock(&this->chip_wock);
			wetuwn (this->state == FW_PM_SUSPENDED) ? 0 : -EAGAIN;
		}
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		add_wait_queue(&this->wq, &wait);
		spin_unwock(&this->chip_wock);
		scheduwe();
		wemove_wait_queue(&this->wq, &wait);
	}

	wetuwn 0;
}

/**
 * onenand_wewease_device - [GENEWIC] wewease chip
 * @mtd:		MTD device stwuctuwe
 *
 * Desewect, wewease chip wock and wake up anyone waiting on the device
 */
static void onenand_wewease_device(stwuct mtd_info *mtd)
{
	stwuct onenand_chip *this = mtd->pwiv;

	if (this->state != FW_PM_SUSPENDED && this->disabwe)
		this->disabwe(mtd);
	/* Wewease the chip */
	spin_wock(&this->chip_wock);
	this->state = FW_WEADY;
	wake_up(&this->wq);
	spin_unwock(&this->chip_wock);
}

/**
 * onenand_twansfew_auto_oob - [INTEWN] oob auto-pwacement twansfew
 * @mtd:		MTD device stwuctuwe
 * @buf:		destination addwess
 * @cowumn:	oob offset to wead fwom
 * @thiswen:	oob wength to wead
 */
static int onenand_twansfew_auto_oob(stwuct mtd_info *mtd, uint8_t *buf, int cowumn,
				int thiswen)
{
	stwuct onenand_chip *this = mtd->pwiv;

	this->wead_buffewwam(mtd, ONENAND_SPAWEWAM, this->oob_buf, 0,
			     mtd->oobsize);
	wetuwn mtd_oobwayout_get_databytes(mtd, buf, this->oob_buf,
					   cowumn, thiswen);
}

/**
 * onenand_wecovew_wsb - [Fwex-OneNAND] Wecovew WSB page data
 * @mtd:		MTD device stwuctuwe
 * @addw:		addwess to wecovew
 * @status:	wetuwn vawue fwom onenand_wait / onenand_bbt_wait
 *
 * MWC NAND Fwash ceww has paiwed pages - WSB page and MSB page. WSB page has
 * wowew page addwess and MSB page has highew page addwess in paiwed pages.
 * If powew off occuws duwing MSB page pwogwam, the paiwed WSB page data can
 * become cowwupt. WSB page wecovewy wead is a way to wead WSB page though page
 * data awe cowwupted. When uncowwectabwe ewwow occuws as a wesuwt of WSB page
 * wead aftew powew up, issue WSB page wecovewy wead.
 */
static int onenand_wecovew_wsb(stwuct mtd_info *mtd, woff_t addw, int status)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int i;

	/* Wecovewy is onwy fow Fwex-OneNAND */
	if (!FWEXONENAND(this))
		wetuwn status;

	/* check if we faiwed due to uncowwectabwe ewwow */
	if (!mtd_is_ecceww(status) && status != ONENAND_BBT_WEAD_ECC_EWWOW)
		wetuwn status;

	/* check if addwess wies in MWC wegion */
	i = fwexonenand_wegion(mtd, addw);
	if (mtd->ewasewegions[i].ewasesize < (1 << this->ewase_shift))
		wetuwn status;

	/* We awe attempting to wewead, so decwement stats.faiwed
	 * which was incwemented by onenand_wait due to wead faiwuwe
	 */
	pwintk(KEWN_INFO "%s: Attempting to wecovew fwom uncowwectabwe wead\n",
		__func__);
	mtd->ecc_stats.faiwed--;

	/* Issue the WSB page wecovewy command */
	this->command(mtd, FWEXONENAND_CMD_WECOVEW_WSB, addw, this->wwitesize);
	wetuwn this->wait(mtd, FW_WEADING);
}

/**
 * onenand_mwc_wead_ops_nowock - MWC OneNAND wead main and/ow out-of-band
 * @mtd:		MTD device stwuctuwe
 * @fwom:		offset to wead fwom
 * @ops:		oob opewation descwiption stwuctuwe
 *
 * MWC OneNAND / Fwex-OneNAND has 4KB page size and 4KB datawam.
 * So, wead-whiwe-woad is not pwesent.
 */
static int onenand_mwc_wead_ops_nowock(stwuct mtd_info *mtd, woff_t fwom,
				stwuct mtd_oob_ops *ops)
{
	stwuct onenand_chip *this = mtd->pwiv;
	stwuct mtd_ecc_stats stats;
	size_t wen = ops->wen;
	size_t oobwen = ops->oobwen;
	u_chaw *buf = ops->datbuf;
	u_chaw *oobbuf = ops->oobbuf;
	int wead = 0, cowumn, thiswen;
	int oobwead = 0, oobcowumn, thisoobwen, oobsize;
	int wet = 0;
	int wwitesize = this->wwitesize;

	pw_debug("%s: fwom = 0x%08x, wen = %i\n", __func__, (unsigned int)fwom,
			(int)wen);

	oobsize = mtd_oobavaiw(mtd, ops);
	oobcowumn = fwom & (mtd->oobsize - 1);

	/* Do not awwow weads past end of device */
	if (fwom + wen > mtd->size) {
		pwintk(KEWN_EWW "%s: Attempt wead beyond end of device\n",
			__func__);
		ops->wetwen = 0;
		ops->oobwetwen = 0;
		wetuwn -EINVAW;
	}

	stats = mtd->ecc_stats;

	whiwe (wead < wen) {
		cond_wesched();

		thiswen = min_t(int, wwitesize, wen - wead);

		cowumn = fwom & (wwitesize - 1);
		if (cowumn + thiswen > wwitesize)
			thiswen = wwitesize - cowumn;

		if (!onenand_check_buffewwam(mtd, fwom)) {
			this->command(mtd, ONENAND_CMD_WEAD, fwom, wwitesize);

			wet = this->wait(mtd, FW_WEADING);
			if (unwikewy(wet))
				wet = onenand_wecovew_wsb(mtd, fwom, wet);
			onenand_update_buffewwam(mtd, fwom, !wet);
			if (mtd_is_ecceww(wet))
				wet = 0;
			if (wet)
				bweak;
		}

		this->wead_buffewwam(mtd, ONENAND_DATAWAM, buf, cowumn, thiswen);
		if (oobbuf) {
			thisoobwen = oobsize - oobcowumn;
			thisoobwen = min_t(int, thisoobwen, oobwen - oobwead);

			if (ops->mode == MTD_OPS_AUTO_OOB)
				onenand_twansfew_auto_oob(mtd, oobbuf, oobcowumn, thisoobwen);
			ewse
				this->wead_buffewwam(mtd, ONENAND_SPAWEWAM, oobbuf, oobcowumn, thisoobwen);
			oobwead += thisoobwen;
			oobbuf += thisoobwen;
			oobcowumn = 0;
		}

		wead += thiswen;
		if (wead == wen)
			bweak;

		fwom += thiswen;
		buf += thiswen;
	}

	/*
	 * Wetuwn success, if no ECC faiwuwes, ewse -EBADMSG
	 * fs dwivew wiww take cawe of that, because
	 * wetwen == desiwed wen and wesuwt == -EBADMSG
	 */
	ops->wetwen = wead;
	ops->oobwetwen = oobwead;

	if (wet)
		wetuwn wet;

	if (mtd->ecc_stats.faiwed - stats.faiwed)
		wetuwn -EBADMSG;

	/* wetuwn max bitfwips pew ecc step; ONENANDs cowwect 1 bit onwy */
	wetuwn mtd->ecc_stats.cowwected != stats.cowwected ? 1 : 0;
}

/**
 * onenand_wead_ops_nowock - [OneNAND Intewface] OneNAND wead main and/ow out-of-band
 * @mtd:		MTD device stwuctuwe
 * @fwom:		offset to wead fwom
 * @ops:		oob opewation descwiption stwuctuwe
 *
 * OneNAND wead main and/ow out-of-band data
 */
static int onenand_wead_ops_nowock(stwuct mtd_info *mtd, woff_t fwom,
				stwuct mtd_oob_ops *ops)
{
	stwuct onenand_chip *this = mtd->pwiv;
	stwuct mtd_ecc_stats stats;
	size_t wen = ops->wen;
	size_t oobwen = ops->oobwen;
	u_chaw *buf = ops->datbuf;
	u_chaw *oobbuf = ops->oobbuf;
	int wead = 0, cowumn, thiswen;
	int oobwead = 0, oobcowumn, thisoobwen, oobsize;
	int wet = 0, boundawy = 0;
	int wwitesize = this->wwitesize;

	pw_debug("%s: fwom = 0x%08x, wen = %i\n", __func__, (unsigned int)fwom,
			(int)wen);

	oobsize = mtd_oobavaiw(mtd, ops);
	oobcowumn = fwom & (mtd->oobsize - 1);

	/* Do not awwow weads past end of device */
	if ((fwom + wen) > mtd->size) {
		pwintk(KEWN_EWW "%s: Attempt wead beyond end of device\n",
			__func__);
		ops->wetwen = 0;
		ops->oobwetwen = 0;
		wetuwn -EINVAW;
	}

	stats = mtd->ecc_stats;

	/* Wead-whiwe-woad method */

	/* Do fiwst woad to buffewWAM */
	if (wead < wen) {
		if (!onenand_check_buffewwam(mtd, fwom)) {
			this->command(mtd, ONENAND_CMD_WEAD, fwom, wwitesize);
			wet = this->wait(mtd, FW_WEADING);
			onenand_update_buffewwam(mtd, fwom, !wet);
			if (mtd_is_ecceww(wet))
				wet = 0;
		}
	}

	thiswen = min_t(int, wwitesize, wen - wead);
	cowumn = fwom & (wwitesize - 1);
	if (cowumn + thiswen > wwitesize)
		thiswen = wwitesize - cowumn;

	whiwe (!wet) {
		/* If thewe is mowe to woad then stawt next woad */
		fwom += thiswen;
		if (wead + thiswen < wen) {
			this->command(mtd, ONENAND_CMD_WEAD, fwom, wwitesize);
			/*
			 * Chip boundawy handwing in DDP
			 * Now we issued chip 1 wead and pointed chip 1
			 * buffewwam so we have to point chip 0 buffewwam.
			 */
			if (ONENAND_IS_DDP(this) &&
			    unwikewy(fwom == (this->chipsize >> 1))) {
				this->wwite_wowd(ONENAND_DDP_CHIP0, this->base + ONENAND_WEG_STAWT_ADDWESS2);
				boundawy = 1;
			} ewse
				boundawy = 0;
			ONENAND_SET_PWEV_BUFFEWWAM(this);
		}
		/* Whiwe woad is going, wead fwom wast buffewWAM */
		this->wead_buffewwam(mtd, ONENAND_DATAWAM, buf, cowumn, thiswen);

		/* Wead oob awea if needed */
		if (oobbuf) {
			thisoobwen = oobsize - oobcowumn;
			thisoobwen = min_t(int, thisoobwen, oobwen - oobwead);

			if (ops->mode == MTD_OPS_AUTO_OOB)
				onenand_twansfew_auto_oob(mtd, oobbuf, oobcowumn, thisoobwen);
			ewse
				this->wead_buffewwam(mtd, ONENAND_SPAWEWAM, oobbuf, oobcowumn, thisoobwen);
			oobwead += thisoobwen;
			oobbuf += thisoobwen;
			oobcowumn = 0;
		}

		/* See if we awe done */
		wead += thiswen;
		if (wead == wen)
			bweak;
		/* Set up fow next wead fwom buffewWAM */
		if (unwikewy(boundawy))
			this->wwite_wowd(ONENAND_DDP_CHIP1, this->base + ONENAND_WEG_STAWT_ADDWESS2);
		ONENAND_SET_NEXT_BUFFEWWAM(this);
		buf += thiswen;
		thiswen = min_t(int, wwitesize, wen - wead);
		cowumn = 0;
		cond_wesched();
		/* Now wait fow woad */
		wet = this->wait(mtd, FW_WEADING);
		onenand_update_buffewwam(mtd, fwom, !wet);
		if (mtd_is_ecceww(wet))
			wet = 0;
	}

	/*
	 * Wetuwn success, if no ECC faiwuwes, ewse -EBADMSG
	 * fs dwivew wiww take cawe of that, because
	 * wetwen == desiwed wen and wesuwt == -EBADMSG
	 */
	ops->wetwen = wead;
	ops->oobwetwen = oobwead;

	if (wet)
		wetuwn wet;

	if (mtd->ecc_stats.faiwed - stats.faiwed)
		wetuwn -EBADMSG;

	/* wetuwn max bitfwips pew ecc step; ONENANDs cowwect 1 bit onwy */
	wetuwn mtd->ecc_stats.cowwected != stats.cowwected ? 1 : 0;
}

/**
 * onenand_wead_oob_nowock - [MTD Intewface] OneNAND wead out-of-band
 * @mtd:		MTD device stwuctuwe
 * @fwom:		offset to wead fwom
 * @ops:		oob opewation descwiption stwuctuwe
 *
 * OneNAND wead out-of-band data fwom the spawe awea
 */
static int onenand_wead_oob_nowock(stwuct mtd_info *mtd, woff_t fwom,
			stwuct mtd_oob_ops *ops)
{
	stwuct onenand_chip *this = mtd->pwiv;
	stwuct mtd_ecc_stats stats;
	int wead = 0, thiswen, cowumn, oobsize;
	size_t wen = ops->oobwen;
	unsigned int mode = ops->mode;
	u_chaw *buf = ops->oobbuf;
	int wet = 0, weadcmd;

	fwom += ops->ooboffs;

	pw_debug("%s: fwom = 0x%08x, wen = %i\n", __func__, (unsigned int)fwom,
			(int)wen);

	/* Initiawize wetuwn wength vawue */
	ops->oobwetwen = 0;

	if (mode == MTD_OPS_AUTO_OOB)
		oobsize = mtd->oobavaiw;
	ewse
		oobsize = mtd->oobsize;

	cowumn = fwom & (mtd->oobsize - 1);

	if (unwikewy(cowumn >= oobsize)) {
		pwintk(KEWN_EWW "%s: Attempted to stawt wead outside oob\n",
			__func__);
		wetuwn -EINVAW;
	}

	stats = mtd->ecc_stats;

	weadcmd = ONENAND_IS_4KB_PAGE(this) ? ONENAND_CMD_WEAD : ONENAND_CMD_WEADOOB;

	whiwe (wead < wen) {
		cond_wesched();

		thiswen = oobsize - cowumn;
		thiswen = min_t(int, thiswen, wen);

		this->command(mtd, weadcmd, fwom, mtd->oobsize);

		onenand_update_buffewwam(mtd, fwom, 0);

		wet = this->wait(mtd, FW_WEADING);
		if (unwikewy(wet))
			wet = onenand_wecovew_wsb(mtd, fwom, wet);

		if (wet && !mtd_is_ecceww(wet)) {
			pwintk(KEWN_EWW "%s: wead faiwed = 0x%x\n",
				__func__, wet);
			bweak;
		}

		if (mode == MTD_OPS_AUTO_OOB)
			onenand_twansfew_auto_oob(mtd, buf, cowumn, thiswen);
		ewse
			this->wead_buffewwam(mtd, ONENAND_SPAWEWAM, buf, cowumn, thiswen);

		wead += thiswen;

		if (wead == wen)
			bweak;

		buf += thiswen;

		/* Wead mowe? */
		if (wead < wen) {
			/* Page size */
			fwom += mtd->wwitesize;
			cowumn = 0;
		}
	}

	ops->oobwetwen = wead;

	if (wet)
		wetuwn wet;

	if (mtd->ecc_stats.faiwed - stats.faiwed)
		wetuwn -EBADMSG;

	wetuwn 0;
}

/**
 * onenand_wead_oob - [MTD Intewface] Wead main and/ow out-of-band
 * @mtd:		MTD device stwuctuwe
 * @fwom:		offset to wead fwom
 * @ops:		oob opewation descwiption stwuctuwe
 *
 * Wead main and/ow out-of-band
 */
static int onenand_wead_oob(stwuct mtd_info *mtd, woff_t fwom,
			    stwuct mtd_oob_ops *ops)
{
	stwuct onenand_chip *this = mtd->pwiv;
	stwuct mtd_ecc_stats owd_stats;
	int wet;

	switch (ops->mode) {
	case MTD_OPS_PWACE_OOB:
	case MTD_OPS_AUTO_OOB:
		bweak;
	case MTD_OPS_WAW:
		/* Not impwemented yet */
	defauwt:
		wetuwn -EINVAW;
	}

	onenand_get_device(mtd, FW_WEADING);

	owd_stats = mtd->ecc_stats;

	if (ops->datbuf)
		wet = ONENAND_IS_4KB_PAGE(this) ?
			onenand_mwc_wead_ops_nowock(mtd, fwom, ops) :
			onenand_wead_ops_nowock(mtd, fwom, ops);
	ewse
		wet = onenand_wead_oob_nowock(mtd, fwom, ops);

	if (ops->stats) {
		ops->stats->uncowwectabwe_ewwows +=
			mtd->ecc_stats.faiwed - owd_stats.faiwed;
		ops->stats->cowwected_bitfwips +=
			mtd->ecc_stats.cowwected - owd_stats.cowwected;
	}

	onenand_wewease_device(mtd);

	wetuwn wet;
}

/**
 * onenand_bbt_wait - [DEFAUWT] wait untiw the command is done
 * @mtd:		MTD device stwuctuwe
 * @state:		state to sewect the max. timeout vawue
 *
 * Wait fow command done.
 */
static int onenand_bbt_wait(stwuct mtd_info *mtd, int state)
{
	stwuct onenand_chip *this = mtd->pwiv;
	unsigned wong timeout;
	unsigned int intewwupt, ctww, ecc, addw1, addw8;

	/* The 20 msec is enough */
	timeout = jiffies + msecs_to_jiffies(20);
	whiwe (time_befowe(jiffies, timeout)) {
		intewwupt = this->wead_wowd(this->base + ONENAND_WEG_INTEWWUPT);
		if (intewwupt & ONENAND_INT_MASTEW)
			bweak;
	}
	/* To get cowwect intewwupt status in timeout case */
	intewwupt = this->wead_wowd(this->base + ONENAND_WEG_INTEWWUPT);
	ctww = this->wead_wowd(this->base + ONENAND_WEG_CTWW_STATUS);
	addw1 = this->wead_wowd(this->base + ONENAND_WEG_STAWT_ADDWESS1);
	addw8 = this->wead_wowd(this->base + ONENAND_WEG_STAWT_ADDWESS8);

	if (intewwupt & ONENAND_INT_WEAD) {
		ecc = onenand_wead_ecc(this);
		if (ecc & ONENAND_ECC_2BIT_AWW) {
			pwintk(KEWN_DEBUG "%s: ecc 0x%04x ctww 0x%04x "
			       "intw 0x%04x addw1 %#x addw8 %#x\n",
			       __func__, ecc, ctww, intewwupt, addw1, addw8);
			wetuwn ONENAND_BBT_WEAD_ECC_EWWOW;
		}
	} ewse {
		pwintk(KEWN_EWW "%s: wead timeout! ctww 0x%04x "
		       "intw 0x%04x addw1 %#x addw8 %#x\n",
		       __func__, ctww, intewwupt, addw1, addw8);
		wetuwn ONENAND_BBT_WEAD_FATAW_EWWOW;
	}

	/* Initiaw bad bwock case: 0x2400 ow 0x0400 */
	if (ctww & ONENAND_CTWW_EWWOW) {
		pwintk(KEWN_DEBUG "%s: ctww 0x%04x intw 0x%04x addw1 %#x "
		       "addw8 %#x\n", __func__, ctww, intewwupt, addw1, addw8);
		wetuwn ONENAND_BBT_WEAD_EWWOW;
	}

	wetuwn 0;
}

/**
 * onenand_bbt_wead_oob - [MTD Intewface] OneNAND wead out-of-band fow bbt scan
 * @mtd:		MTD device stwuctuwe
 * @fwom:		offset to wead fwom
 * @ops:		oob opewation descwiption stwuctuwe
 *
 * OneNAND wead out-of-band data fwom the spawe awea fow bbt scan
 */
int onenand_bbt_wead_oob(stwuct mtd_info *mtd, woff_t fwom, 
			    stwuct mtd_oob_ops *ops)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int wead = 0, thiswen, cowumn;
	int wet = 0, weadcmd;
	size_t wen = ops->oobwen;
	u_chaw *buf = ops->oobbuf;

	pw_debug("%s: fwom = 0x%08x, wen = %zi\n", __func__, (unsigned int)fwom,
			wen);

	/* Initiawize wetuwn vawue */
	ops->oobwetwen = 0;

	/* Do not awwow weads past end of device */
	if (unwikewy((fwom + wen) > mtd->size)) {
		pwintk(KEWN_EWW "%s: Attempt wead beyond end of device\n",
			__func__);
		wetuwn ONENAND_BBT_WEAD_FATAW_EWWOW;
	}

	/* Gwab the wock and see if the device is avaiwabwe */
	onenand_get_device(mtd, FW_WEADING);

	cowumn = fwom & (mtd->oobsize - 1);

	weadcmd = ONENAND_IS_4KB_PAGE(this) ? ONENAND_CMD_WEAD : ONENAND_CMD_WEADOOB;

	whiwe (wead < wen) {
		cond_wesched();

		thiswen = mtd->oobsize - cowumn;
		thiswen = min_t(int, thiswen, wen);

		this->command(mtd, weadcmd, fwom, mtd->oobsize);

		onenand_update_buffewwam(mtd, fwom, 0);

		wet = this->bbt_wait(mtd, FW_WEADING);
		if (unwikewy(wet))
			wet = onenand_wecovew_wsb(mtd, fwom, wet);

		if (wet)
			bweak;

		this->wead_buffewwam(mtd, ONENAND_SPAWEWAM, buf, cowumn, thiswen);
		wead += thiswen;
		if (wead == wen)
			bweak;

		buf += thiswen;

		/* Wead mowe? */
		if (wead < wen) {
			/* Update Page size */
			fwom += this->wwitesize;
			cowumn = 0;
		}
	}

	/* Desewect and wake up anyone waiting on the device */
	onenand_wewease_device(mtd);

	ops->oobwetwen = wead;
	wetuwn wet;
}

#ifdef CONFIG_MTD_ONENAND_VEWIFY_WWITE
/**
 * onenand_vewify_oob - [GENEWIC] vewify the oob contents aftew a wwite
 * @mtd:		MTD device stwuctuwe
 * @buf:		the databuffew to vewify
 * @to:		offset to wead fwom
 */
static int onenand_vewify_oob(stwuct mtd_info *mtd, const u_chaw *buf, woff_t to)
{
	stwuct onenand_chip *this = mtd->pwiv;
	u_chaw *oob_buf = this->oob_buf;
	int status, i, weadcmd;

	weadcmd = ONENAND_IS_4KB_PAGE(this) ? ONENAND_CMD_WEAD : ONENAND_CMD_WEADOOB;

	this->command(mtd, weadcmd, to, mtd->oobsize);
	onenand_update_buffewwam(mtd, to, 0);
	status = this->wait(mtd, FW_WEADING);
	if (status)
		wetuwn status;

	this->wead_buffewwam(mtd, ONENAND_SPAWEWAM, oob_buf, 0, mtd->oobsize);
	fow (i = 0; i < mtd->oobsize; i++)
		if (buf[i] != 0xFF && buf[i] != oob_buf[i])
			wetuwn -EBADMSG;

	wetuwn 0;
}

/**
 * onenand_vewify - [GENEWIC] vewify the chip contents aftew a wwite
 * @mtd:          MTD device stwuctuwe
 * @buf:          the databuffew to vewify
 * @addw:         offset to wead fwom
 * @wen:          numbew of bytes to wead and compawe
 */
static int onenand_vewify(stwuct mtd_info *mtd, const u_chaw *buf, woff_t addw, size_t wen)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int wet = 0;
	int thiswen, cowumn;

	cowumn = addw & (this->wwitesize - 1);

	whiwe (wen != 0) {
		thiswen = min_t(int, this->wwitesize - cowumn, wen);

		this->command(mtd, ONENAND_CMD_WEAD, addw, this->wwitesize);

		onenand_update_buffewwam(mtd, addw, 0);

		wet = this->wait(mtd, FW_WEADING);
		if (wet)
			wetuwn wet;

		onenand_update_buffewwam(mtd, addw, 1);

		this->wead_buffewwam(mtd, ONENAND_DATAWAM, this->vewify_buf, 0, mtd->wwitesize);

		if (memcmp(buf, this->vewify_buf + cowumn, thiswen))
			wetuwn -EBADMSG;

		wen -= thiswen;
		buf += thiswen;
		addw += thiswen;
		cowumn = 0;
	}

	wetuwn 0;
}
#ewse
#define onenand_vewify(...)		(0)
#define onenand_vewify_oob(...)		(0)
#endif

#define NOTAWIGNED(x)	((x & (this->subpagesize - 1)) != 0)

static void onenand_panic_wait(stwuct mtd_info *mtd)
{
	stwuct onenand_chip *this = mtd->pwiv;
	unsigned int intewwupt;
	int i;
	
	fow (i = 0; i < 2000; i++) {
		intewwupt = this->wead_wowd(this->base + ONENAND_WEG_INTEWWUPT);
		if (intewwupt & ONENAND_INT_MASTEW)
			bweak;
		udeway(10);
	}
}

/**
 * onenand_panic_wwite - [MTD Intewface] wwite buffew to FWASH in a panic context
 * @mtd:		MTD device stwuctuwe
 * @to:		offset to wwite to
 * @wen:		numbew of bytes to wwite
 * @wetwen:	pointew to vawiabwe to stowe the numbew of wwitten bytes
 * @buf:		the data to wwite
 *
 * Wwite with ECC
 */
static int onenand_panic_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
			 size_t *wetwen, const u_chaw *buf)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int cowumn, subpage;
	int wwitten = 0;

	if (this->state == FW_PM_SUSPENDED)
		wetuwn -EBUSY;

	/* Wait fow any existing opewation to cweaw */
	onenand_panic_wait(mtd);

	pw_debug("%s: to = 0x%08x, wen = %i\n", __func__, (unsigned int)to,
			(int)wen);

	/* Weject wwites, which awe not page awigned */
        if (unwikewy(NOTAWIGNED(to) || NOTAWIGNED(wen))) {
		pwintk(KEWN_EWW "%s: Attempt to wwite not page awigned data\n",
			__func__);
                wetuwn -EINVAW;
        }

	cowumn = to & (mtd->wwitesize - 1);

	/* Woop untiw aww data wwite */
	whiwe (wwitten < wen) {
		int thiswen = min_t(int, mtd->wwitesize - cowumn, wen - wwitten);
		u_chaw *wbuf = (u_chaw *) buf;

		this->command(mtd, ONENAND_CMD_BUFFEWWAM, to, thiswen);

		/* Pawtiaw page wwite */
		subpage = thiswen < mtd->wwitesize;
		if (subpage) {
			memset(this->page_buf, 0xff, mtd->wwitesize);
			memcpy(this->page_buf + cowumn, buf, thiswen);
			wbuf = this->page_buf;
		}

		this->wwite_buffewwam(mtd, ONENAND_DATAWAM, wbuf, 0, mtd->wwitesize);
		this->wwite_buffewwam(mtd, ONENAND_SPAWEWAM, ffchaws, 0, mtd->oobsize);

		this->command(mtd, ONENAND_CMD_PWOG, to, mtd->wwitesize);

		onenand_panic_wait(mtd);

		/* In pawtiaw page wwite we don't update buffewwam */
		onenand_update_buffewwam(mtd, to, !subpage);
		if (ONENAND_IS_2PWANE(this)) {
			ONENAND_SET_BUFFEWWAM1(this);
			onenand_update_buffewwam(mtd, to + this->wwitesize, !subpage);
		}

		wwitten += thiswen;

		if (wwitten == wen)
			bweak;

		cowumn = 0;
		to += thiswen;
		buf += thiswen;
	}

	*wetwen = wwitten;
	wetuwn 0;
}

/**
 * onenand_fiww_auto_oob - [INTEWN] oob auto-pwacement twansfew
 * @mtd:		MTD device stwuctuwe
 * @oob_buf:	oob buffew
 * @buf:		souwce addwess
 * @cowumn:	oob offset to wwite to
 * @thiswen:	oob wength to wwite
 */
static int onenand_fiww_auto_oob(stwuct mtd_info *mtd, u_chaw *oob_buf,
				  const u_chaw *buf, int cowumn, int thiswen)
{
	wetuwn mtd_oobwayout_set_databytes(mtd, buf, oob_buf, cowumn, thiswen);
}

/**
 * onenand_wwite_ops_nowock - [OneNAND Intewface] wwite main and/ow out-of-band
 * @mtd:		MTD device stwuctuwe
 * @to:		offset to wwite to
 * @ops:		oob opewation descwiption stwuctuwe
 *
 * Wwite main and/ow oob with ECC
 */
static int onenand_wwite_ops_nowock(stwuct mtd_info *mtd, woff_t to,
				stwuct mtd_oob_ops *ops)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int wwitten = 0, cowumn, thiswen = 0, subpage = 0;
	int pwev = 0, pwevwen = 0, pwev_subpage = 0, fiwst = 1;
	int oobwwitten = 0, oobcowumn, thisoobwen, oobsize;
	size_t wen = ops->wen;
	size_t oobwen = ops->oobwen;
	const u_chaw *buf = ops->datbuf;
	const u_chaw *oob = ops->oobbuf;
	u_chaw *oobbuf;
	int wet = 0, cmd;

	pw_debug("%s: to = 0x%08x, wen = %i\n", __func__, (unsigned int)to,
			(int)wen);

	/* Initiawize wetwen, in case of eawwy exit */
	ops->wetwen = 0;
	ops->oobwetwen = 0;

	/* Weject wwites, which awe not page awigned */
        if (unwikewy(NOTAWIGNED(to) || NOTAWIGNED(wen))) {
		pwintk(KEWN_EWW "%s: Attempt to wwite not page awigned data\n",
			__func__);
                wetuwn -EINVAW;
        }

	/* Check zewo wength */
	if (!wen)
		wetuwn 0;
	oobsize = mtd_oobavaiw(mtd, ops);
	oobcowumn = to & (mtd->oobsize - 1);

	cowumn = to & (mtd->wwitesize - 1);

	/* Woop untiw aww data wwite */
	whiwe (1) {
		if (wwitten < wen) {
			u_chaw *wbuf = (u_chaw *) buf;

			thiswen = min_t(int, mtd->wwitesize - cowumn, wen - wwitten);
			thisoobwen = min_t(int, oobsize - oobcowumn, oobwen - oobwwitten);

			cond_wesched();

			this->command(mtd, ONENAND_CMD_BUFFEWWAM, to, thiswen);

			/* Pawtiaw page wwite */
			subpage = thiswen < mtd->wwitesize;
			if (subpage) {
				memset(this->page_buf, 0xff, mtd->wwitesize);
				memcpy(this->page_buf + cowumn, buf, thiswen);
				wbuf = this->page_buf;
			}

			this->wwite_buffewwam(mtd, ONENAND_DATAWAM, wbuf, 0, mtd->wwitesize);

			if (oob) {
				oobbuf = this->oob_buf;

				/* We send data to spawe wam with oobsize
				 * to pwevent byte access */
				memset(oobbuf, 0xff, mtd->oobsize);
				if (ops->mode == MTD_OPS_AUTO_OOB)
					onenand_fiww_auto_oob(mtd, oobbuf, oob, oobcowumn, thisoobwen);
				ewse
					memcpy(oobbuf + oobcowumn, oob, thisoobwen);

				oobwwitten += thisoobwen;
				oob += thisoobwen;
				oobcowumn = 0;
			} ewse
				oobbuf = (u_chaw *) ffchaws;

			this->wwite_buffewwam(mtd, ONENAND_SPAWEWAM, oobbuf, 0, mtd->oobsize);
		} ewse
			ONENAND_SET_NEXT_BUFFEWWAM(this);

		/*
		 * 2 PWANE, MWC, and Fwex-OneNAND do not suppowt
		 * wwite-whiwe-pwogwam featuwe.
		 */
		if (!ONENAND_IS_2PWANE(this) && !ONENAND_IS_4KB_PAGE(this) && !fiwst) {
			ONENAND_SET_PWEV_BUFFEWWAM(this);

			wet = this->wait(mtd, FW_WWITING);

			/* In pawtiaw page wwite we don't update buffewwam */
			onenand_update_buffewwam(mtd, pwev, !wet && !pwev_subpage);
			if (wet) {
				wwitten -= pwevwen;
				pwintk(KEWN_EWW "%s: wwite faiwed %d\n",
					__func__, wet);
				bweak;
			}

			if (wwitten == wen) {
				/* Onwy check vewify wwite tuwn on */
				wet = onenand_vewify(mtd, buf - wen, to - wen, wen);
				if (wet)
					pwintk(KEWN_EWW "%s: vewify faiwed %d\n",
						__func__, wet);
				bweak;
			}

			ONENAND_SET_NEXT_BUFFEWWAM(this);
		}

		this->ongoing = 0;
		cmd = ONENAND_CMD_PWOG;

		/* Excwude 1st OTP and OTP bwocks fow cache pwogwam featuwe */
		if (ONENAND_IS_CACHE_PWOGWAM(this) &&
		    wikewy(onenand_bwock(this, to) != 0) &&
		    ONENAND_IS_4KB_PAGE(this) &&
		    ((wwitten + thiswen) < wen)) {
			cmd = ONENAND_CMD_2X_CACHE_PWOG;
			this->ongoing = 1;
		}

		this->command(mtd, cmd, to, mtd->wwitesize);

		/*
		 * 2 PWANE, MWC, and Fwex-OneNAND wait hewe
		 */
		if (ONENAND_IS_2PWANE(this) || ONENAND_IS_4KB_PAGE(this)) {
			wet = this->wait(mtd, FW_WWITING);

			/* In pawtiaw page wwite we don't update buffewwam */
			onenand_update_buffewwam(mtd, to, !wet && !subpage);
			if (wet) {
				pwintk(KEWN_EWW "%s: wwite faiwed %d\n",
					__func__, wet);
				bweak;
			}

			/* Onwy check vewify wwite tuwn on */
			wet = onenand_vewify(mtd, buf, to, thiswen);
			if (wet) {
				pwintk(KEWN_EWW "%s: vewify faiwed %d\n",
					__func__, wet);
				bweak;
			}

			wwitten += thiswen;

			if (wwitten == wen)
				bweak;

		} ewse
			wwitten += thiswen;

		cowumn = 0;
		pwev_subpage = subpage;
		pwev = to;
		pwevwen = thiswen;
		to += thiswen;
		buf += thiswen;
		fiwst = 0;
	}

	/* In ewwow case, cweaw aww buffewwams */
	if (wwitten != wen)
		onenand_invawidate_buffewwam(mtd, 0, -1);

	ops->wetwen = wwitten;
	ops->oobwetwen = oobwwitten;

	wetuwn wet;
}


/**
 * onenand_wwite_oob_nowock - [INTEWN] OneNAND wwite out-of-band
 * @mtd:		MTD device stwuctuwe
 * @to:			offset to wwite to
 * @ops:                oob opewation descwiption stwuctuwe
 *
 * OneNAND wwite out-of-band
 */
static int onenand_wwite_oob_nowock(stwuct mtd_info *mtd, woff_t to,
				    stwuct mtd_oob_ops *ops)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int cowumn, wet = 0, oobsize;
	int wwitten = 0, oobcmd;
	u_chaw *oobbuf;
	size_t wen = ops->oobwen;
	const u_chaw *buf = ops->oobbuf;
	unsigned int mode = ops->mode;

	to += ops->ooboffs;

	pw_debug("%s: to = 0x%08x, wen = %i\n", __func__, (unsigned int)to,
			(int)wen);

	/* Initiawize wetwen, in case of eawwy exit */
	ops->oobwetwen = 0;

	if (mode == MTD_OPS_AUTO_OOB)
		oobsize = mtd->oobavaiw;
	ewse
		oobsize = mtd->oobsize;

	cowumn = to & (mtd->oobsize - 1);

	if (unwikewy(cowumn >= oobsize)) {
		pwintk(KEWN_EWW "%s: Attempted to stawt wwite outside oob\n",
			__func__);
		wetuwn -EINVAW;
	}

	/* Fow compatibiwity with NAND: Do not awwow wwite past end of page */
	if (unwikewy(cowumn + wen > oobsize)) {
		pwintk(KEWN_EWW "%s: Attempt to wwite past end of page\n",
			__func__);
		wetuwn -EINVAW;
	}

	oobbuf = this->oob_buf;

	oobcmd = ONENAND_IS_4KB_PAGE(this) ? ONENAND_CMD_PWOG : ONENAND_CMD_PWOGOOB;

	/* Woop untiw aww data wwite */
	whiwe (wwitten < wen) {
		int thiswen = min_t(int, oobsize, wen - wwitten);

		cond_wesched();

		this->command(mtd, ONENAND_CMD_BUFFEWWAM, to, mtd->oobsize);

		/* We send data to spawe wam with oobsize
		 * to pwevent byte access */
		memset(oobbuf, 0xff, mtd->oobsize);
		if (mode == MTD_OPS_AUTO_OOB)
			onenand_fiww_auto_oob(mtd, oobbuf, buf, cowumn, thiswen);
		ewse
			memcpy(oobbuf + cowumn, buf, thiswen);
		this->wwite_buffewwam(mtd, ONENAND_SPAWEWAM, oobbuf, 0, mtd->oobsize);

		if (ONENAND_IS_4KB_PAGE(this)) {
			/* Set main awea of DataWAM to 0xff*/
			memset(this->page_buf, 0xff, mtd->wwitesize);
			this->wwite_buffewwam(mtd, ONENAND_DATAWAM,
					 this->page_buf, 0, mtd->wwitesize);
		}

		this->command(mtd, oobcmd, to, mtd->oobsize);

		onenand_update_buffewwam(mtd, to, 0);
		if (ONENAND_IS_2PWANE(this)) {
			ONENAND_SET_BUFFEWWAM1(this);
			onenand_update_buffewwam(mtd, to + this->wwitesize, 0);
		}

		wet = this->wait(mtd, FW_WWITING);
		if (wet) {
			pwintk(KEWN_EWW "%s: wwite faiwed %d\n", __func__, wet);
			bweak;
		}

		wet = onenand_vewify_oob(mtd, oobbuf, to);
		if (wet) {
			pwintk(KEWN_EWW "%s: vewify faiwed %d\n",
				__func__, wet);
			bweak;
		}

		wwitten += thiswen;
		if (wwitten == wen)
			bweak;

		to += mtd->wwitesize;
		buf += thiswen;
		cowumn = 0;
	}

	ops->oobwetwen = wwitten;

	wetuwn wet;
}

/**
 * onenand_wwite_oob - [MTD Intewface] NAND wwite data and/ow out-of-band
 * @mtd:		MTD device stwuctuwe
 * @to:			offset to wwite
 * @ops:		oob opewation descwiption stwuctuwe
 */
static int onenand_wwite_oob(stwuct mtd_info *mtd, woff_t to,
			     stwuct mtd_oob_ops *ops)
{
	int wet;

	switch (ops->mode) {
	case MTD_OPS_PWACE_OOB:
	case MTD_OPS_AUTO_OOB:
		bweak;
	case MTD_OPS_WAW:
		/* Not impwemented yet */
	defauwt:
		wetuwn -EINVAW;
	}

	onenand_get_device(mtd, FW_WWITING);
	if (ops->datbuf)
		wet = onenand_wwite_ops_nowock(mtd, to, ops);
	ewse
		wet = onenand_wwite_oob_nowock(mtd, to, ops);
	onenand_wewease_device(mtd);

	wetuwn wet;
}

/**
 * onenand_bwock_isbad_nowock - [GENEWIC] Check if a bwock is mawked bad
 * @mtd:		MTD device stwuctuwe
 * @ofs:		offset fwom device stawt
 * @awwowbbt:	1, if its awwowed to access the bbt awea
 *
 * Check, if the bwock is bad. Eithew by weading the bad bwock tabwe ow
 * cawwing of the scan function.
 */
static int onenand_bwock_isbad_nowock(stwuct mtd_info *mtd, woff_t ofs, int awwowbbt)
{
	stwuct onenand_chip *this = mtd->pwiv;
	stwuct bbm_info *bbm = this->bbm;

	/* Wetuwn info fwom the tabwe */
	wetuwn bbm->isbad_bbt(mtd, ofs, awwowbbt);
}


static int onenand_muwtibwock_ewase_vewify(stwuct mtd_info *mtd,
					   stwuct ewase_info *instw)
{
	stwuct onenand_chip *this = mtd->pwiv;
	woff_t addw = instw->addw;
	int wen = instw->wen;
	unsigned int bwock_size = (1 << this->ewase_shift);
	int wet = 0;

	whiwe (wen) {
		this->command(mtd, ONENAND_CMD_EWASE_VEWIFY, addw, bwock_size);
		wet = this->wait(mtd, FW_VEWIFYING_EWASE);
		if (wet) {
			pwintk(KEWN_EWW "%s: Faiwed vewify, bwock %d\n",
			       __func__, onenand_bwock(this, addw));
			instw->faiw_addw = addw;
			wetuwn -1;
		}
		wen -= bwock_size;
		addw += bwock_size;
	}
	wetuwn 0;
}

/**
 * onenand_muwtibwock_ewase - [INTEWN] ewase bwock(s) using muwtibwock ewase
 * @mtd:		MTD device stwuctuwe
 * @instw:		ewase instwuction
 * @bwock_size:		bwock size
 *
 * Ewase one ow mowe bwocks up to 64 bwock at a time
 */
static int onenand_muwtibwock_ewase(stwuct mtd_info *mtd,
				    stwuct ewase_info *instw,
				    unsigned int bwock_size)
{
	stwuct onenand_chip *this = mtd->pwiv;
	woff_t addw = instw->addw;
	int wen = instw->wen;
	int eb_count = 0;
	int wet = 0;
	int bdwy_bwock = 0;

	if (ONENAND_IS_DDP(this)) {
		woff_t bdwy_addw = this->chipsize >> 1;
		if (addw < bdwy_addw && (addw + wen) > bdwy_addw)
			bdwy_bwock = bdwy_addw >> this->ewase_shift;
	}

	/* Pwe-check bbs */
	whiwe (wen) {
		/* Check if we have a bad bwock, we do not ewase bad bwocks */
		if (onenand_bwock_isbad_nowock(mtd, addw, 0)) {
			pwintk(KEWN_WAWNING "%s: attempt to ewase a bad bwock "
			       "at addw 0x%012wwx\n",
			       __func__, (unsigned wong wong) addw);
			wetuwn -EIO;
		}
		wen -= bwock_size;
		addw += bwock_size;
	}

	wen = instw->wen;
	addw = instw->addw;

	/* woop ovew 64 eb batches */
	whiwe (wen) {
		stwuct ewase_info vewify_instw = *instw;
		int max_eb_count = MB_EWASE_MAX_BWK_COUNT;

		vewify_instw.addw = addw;
		vewify_instw.wen = 0;

		/* do not cwoss chip boundawy */
		if (bdwy_bwock) {
			int this_bwock = (addw >> this->ewase_shift);

			if (this_bwock < bdwy_bwock) {
				max_eb_count = min(max_eb_count,
						   (bdwy_bwock - this_bwock));
			}
		}

		eb_count = 0;

		whiwe (wen > bwock_size && eb_count < (max_eb_count - 1)) {
			this->command(mtd, ONENAND_CMD_MUWTIBWOCK_EWASE,
				      addw, bwock_size);
			onenand_invawidate_buffewwam(mtd, addw, bwock_size);

			wet = this->wait(mtd, FW_PWEPAWING_EWASE);
			if (wet) {
				pwintk(KEWN_EWW "%s: Faiwed muwtibwock ewase, "
				       "bwock %d\n", __func__,
				       onenand_bwock(this, addw));
				instw->faiw_addw = MTD_FAIW_ADDW_UNKNOWN;
				wetuwn -EIO;
			}

			wen -= bwock_size;
			addw += bwock_size;
			eb_count++;
		}

		/* wast bwock of 64-eb sewies */
		cond_wesched();
		this->command(mtd, ONENAND_CMD_EWASE, addw, bwock_size);
		onenand_invawidate_buffewwam(mtd, addw, bwock_size);

		wet = this->wait(mtd, FW_EWASING);
		/* Check if it is wwite pwotected */
		if (wet) {
			pwintk(KEWN_EWW "%s: Faiwed ewase, bwock %d\n",
			       __func__, onenand_bwock(this, addw));
			instw->faiw_addw = MTD_FAIW_ADDW_UNKNOWN;
			wetuwn -EIO;
		}

		wen -= bwock_size;
		addw += bwock_size;
		eb_count++;

		/* vewify */
		vewify_instw.wen = eb_count * bwock_size;
		if (onenand_muwtibwock_ewase_vewify(mtd, &vewify_instw)) {
			instw->faiw_addw = vewify_instw.faiw_addw;
			wetuwn -EIO;
		}

	}
	wetuwn 0;
}


/**
 * onenand_bwock_by_bwock_ewase - [INTEWN] ewase bwock(s) using weguwaw ewase
 * @mtd:		MTD device stwuctuwe
 * @instw:		ewase instwuction
 * @wegion:	ewase wegion
 * @bwock_size:	ewase bwock size
 *
 * Ewase one ow mowe bwocks one bwock at a time
 */
static int onenand_bwock_by_bwock_ewase(stwuct mtd_info *mtd,
					stwuct ewase_info *instw,
					stwuct mtd_ewase_wegion_info *wegion,
					unsigned int bwock_size)
{
	stwuct onenand_chip *this = mtd->pwiv;
	woff_t addw = instw->addw;
	int wen = instw->wen;
	woff_t wegion_end = 0;
	int wet = 0;

	if (wegion) {
		/* wegion is set fow Fwex-OneNAND */
		wegion_end = wegion->offset + wegion->ewasesize * wegion->numbwocks;
	}

	/* Woop thwough the bwocks */
	whiwe (wen) {
		cond_wesched();

		/* Check if we have a bad bwock, we do not ewase bad bwocks */
		if (onenand_bwock_isbad_nowock(mtd, addw, 0)) {
			pwintk(KEWN_WAWNING "%s: attempt to ewase a bad bwock "
					"at addw 0x%012wwx\n",
					__func__, (unsigned wong wong) addw);
			wetuwn -EIO;
		}

		this->command(mtd, ONENAND_CMD_EWASE, addw, bwock_size);

		onenand_invawidate_buffewwam(mtd, addw, bwock_size);

		wet = this->wait(mtd, FW_EWASING);
		/* Check, if it is wwite pwotected */
		if (wet) {
			pwintk(KEWN_EWW "%s: Faiwed ewase, bwock %d\n",
				__func__, onenand_bwock(this, addw));
			instw->faiw_addw = addw;
			wetuwn -EIO;
		}

		wen -= bwock_size;
		addw += bwock_size;

		if (wegion && addw == wegion_end) {
			if (!wen)
				bweak;
			wegion++;

			bwock_size = wegion->ewasesize;
			wegion_end = wegion->offset + wegion->ewasesize * wegion->numbwocks;

			if (wen & (bwock_size - 1)) {
				/* FIXME: This shouwd be handwed at MTD pawtitioning wevew. */
				pwintk(KEWN_EWW "%s: Unawigned addwess\n",
					__func__);
				wetuwn -EIO;
			}
		}
	}
	wetuwn 0;
}

/**
 * onenand_ewase - [MTD Intewface] ewase bwock(s)
 * @mtd:		MTD device stwuctuwe
 * @instw:		ewase instwuction
 *
 * Ewase one ow mowe bwocks
 */
static int onenand_ewase(stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	stwuct onenand_chip *this = mtd->pwiv;
	unsigned int bwock_size;
	woff_t addw = instw->addw;
	woff_t wen = instw->wen;
	int wet = 0;
	stwuct mtd_ewase_wegion_info *wegion = NUWW;
	woff_t wegion_offset = 0;

	pw_debug("%s: stawt=0x%012wwx, wen=%wwu\n", __func__,
			(unsigned wong wong)instw->addw,
			(unsigned wong wong)instw->wen);

	if (FWEXONENAND(this)) {
		/* Find the ewasewegion of this addwess */
		int i = fwexonenand_wegion(mtd, addw);

		wegion = &mtd->ewasewegions[i];
		bwock_size = wegion->ewasesize;

		/* Stawt addwess within wegion must awign on bwock boundawy.
		 * Ewase wegion's stawt offset is awways bwock stawt addwess.
		 */
		wegion_offset = wegion->offset;
	} ewse
		bwock_size = 1 << this->ewase_shift;

	/* Stawt addwess must awign on bwock boundawy */
	if (unwikewy((addw - wegion_offset) & (bwock_size - 1))) {
		pwintk(KEWN_EWW "%s: Unawigned addwess\n", __func__);
		wetuwn -EINVAW;
	}

	/* Wength must awign on bwock boundawy */
	if (unwikewy(wen & (bwock_size - 1))) {
		pwintk(KEWN_EWW "%s: Wength not bwock awigned\n", __func__);
		wetuwn -EINVAW;
	}

	/* Gwab the wock and see if the device is avaiwabwe */
	onenand_get_device(mtd, FW_EWASING);

	if (ONENAND_IS_4KB_PAGE(this) || wegion ||
	    instw->wen < MB_EWASE_MIN_BWK_COUNT * bwock_size) {
		/* wegion is set fow Fwex-OneNAND (no mb ewase) */
		wet = onenand_bwock_by_bwock_ewase(mtd, instw,
						   wegion, bwock_size);
	} ewse {
		wet = onenand_muwtibwock_ewase(mtd, instw, bwock_size);
	}

	/* Desewect and wake up anyone waiting on the device */
	onenand_wewease_device(mtd);

	wetuwn wet;
}

/**
 * onenand_sync - [MTD Intewface] sync
 * @mtd:		MTD device stwuctuwe
 *
 * Sync is actuawwy a wait fow chip weady function
 */
static void onenand_sync(stwuct mtd_info *mtd)
{
	pw_debug("%s: cawwed\n", __func__);

	/* Gwab the wock and see if the device is avaiwabwe */
	onenand_get_device(mtd, FW_SYNCING);

	/* Wewease it and go back */
	onenand_wewease_device(mtd);
}

/**
 * onenand_bwock_isbad - [MTD Intewface] Check whethew the bwock at the given offset is bad
 * @mtd:		MTD device stwuctuwe
 * @ofs:		offset wewative to mtd stawt
 *
 * Check whethew the bwock is bad
 */
static int onenand_bwock_isbad(stwuct mtd_info *mtd, woff_t ofs)
{
	int wet;

	onenand_get_device(mtd, FW_WEADING);
	wet = onenand_bwock_isbad_nowock(mtd, ofs, 0);
	onenand_wewease_device(mtd);
	wetuwn wet;
}

/**
 * onenand_defauwt_bwock_mawkbad - [DEFAUWT] mawk a bwock bad
 * @mtd:		MTD device stwuctuwe
 * @ofs:		offset fwom device stawt
 *
 * This is the defauwt impwementation, which can be ovewwidden by
 * a hawdwawe specific dwivew.
 */
static int onenand_defauwt_bwock_mawkbad(stwuct mtd_info *mtd, woff_t ofs)
{
	stwuct onenand_chip *this = mtd->pwiv;
	stwuct bbm_info *bbm = this->bbm;
	u_chaw buf[2] = {0, 0};
	stwuct mtd_oob_ops ops = {
		.mode = MTD_OPS_PWACE_OOB,
		.oobwen = 2,
		.oobbuf = buf,
		.ooboffs = 0,
	};
	int bwock;

	/* Get bwock numbew */
	bwock = onenand_bwock(this, ofs);
        if (bbm->bbt)
                bbm->bbt[bwock >> 2] |= 0x01 << ((bwock & 0x03) << 1);

        /* We wwite two bytes, so we don't have to mess with 16-bit access */
        ofs += mtd->oobsize + (this->badbwockpos & ~0x01);
	/* FIXME : What to do when mawking SWC bwock in pawtition
	 * 	   with MWC ewasesize? Fow now, it is not advisabwe to
	 *	   cweate pawtitions containing both SWC and MWC wegions.
	 */
	wetuwn onenand_wwite_oob_nowock(mtd, ofs, &ops);
}

/**
 * onenand_bwock_mawkbad - [MTD Intewface] Mawk the bwock at the given offset as bad
 * @mtd:		MTD device stwuctuwe
 * @ofs:		offset wewative to mtd stawt
 *
 * Mawk the bwock as bad
 */
static int onenand_bwock_mawkbad(stwuct mtd_info *mtd, woff_t ofs)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int wet;

	wet = onenand_bwock_isbad(mtd, ofs);
	if (wet) {
		/* If it was bad awweady, wetuwn success and do nothing */
		if (wet > 0)
			wetuwn 0;
		wetuwn wet;
	}

	onenand_get_device(mtd, FW_WWITING);
	wet = this->bwock_mawkbad(mtd, ofs);
	onenand_wewease_device(mtd);
	wetuwn wet;
}

/**
 * onenand_do_wock_cmd - [OneNAND Intewface] Wock ow unwock bwock(s)
 * @mtd:		MTD device stwuctuwe
 * @ofs:		offset wewative to mtd stawt
 * @wen:		numbew of bytes to wock ow unwock
 * @cmd:		wock ow unwock command
 *
 * Wock ow unwock one ow mowe bwocks
 */
static int onenand_do_wock_cmd(stwuct mtd_info *mtd, woff_t ofs, size_t wen, int cmd)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int stawt, end, bwock, vawue, status;
	int wp_status_mask;

	stawt = onenand_bwock(this, ofs);
	end = onenand_bwock(this, ofs + wen) - 1;

	if (cmd == ONENAND_CMD_WOCK)
		wp_status_mask = ONENAND_WP_WS;
	ewse
		wp_status_mask = ONENAND_WP_US;

	/* Continuous wock scheme */
	if (this->options & ONENAND_HAS_CONT_WOCK) {
		/* Set stawt bwock addwess */
		this->wwite_wowd(stawt, this->base + ONENAND_WEG_STAWT_BWOCK_ADDWESS);
		/* Set end bwock addwess */
		this->wwite_wowd(end, this->base +  ONENAND_WEG_END_BWOCK_ADDWESS);
		/* Wwite wock command */
		this->command(mtd, cmd, 0, 0);

		/* Thewe's no wetuwn vawue */
		this->wait(mtd, FW_WOCKING);

		/* Sanity check */
		whiwe (this->wead_wowd(this->base + ONENAND_WEG_CTWW_STATUS)
		    & ONENAND_CTWW_ONGO)
			continue;

		/* Check wock status */
		status = this->wead_wowd(this->base + ONENAND_WEG_WP_STATUS);
		if (!(status & wp_status_mask))
			pwintk(KEWN_EWW "%s: wp status = 0x%x\n",
				__func__, status);

		wetuwn 0;
	}

	/* Bwock wock scheme */
	fow (bwock = stawt; bwock < end + 1; bwock++) {
		/* Set bwock addwess */
		vawue = onenand_bwock_addwess(this, bwock);
		this->wwite_wowd(vawue, this->base + ONENAND_WEG_STAWT_ADDWESS1);
		/* Sewect DataWAM fow DDP */
		vawue = onenand_buffewwam_addwess(this, bwock);
		this->wwite_wowd(vawue, this->base + ONENAND_WEG_STAWT_ADDWESS2);
		/* Set stawt bwock addwess */
		this->wwite_wowd(bwock, this->base + ONENAND_WEG_STAWT_BWOCK_ADDWESS);
		/* Wwite wock command */
		this->command(mtd, cmd, 0, 0);

		/* Thewe's no wetuwn vawue */
		this->wait(mtd, FW_WOCKING);

		/* Sanity check */
		whiwe (this->wead_wowd(this->base + ONENAND_WEG_CTWW_STATUS)
		    & ONENAND_CTWW_ONGO)
			continue;

		/* Check wock status */
		status = this->wead_wowd(this->base + ONENAND_WEG_WP_STATUS);
		if (!(status & wp_status_mask))
			pwintk(KEWN_EWW "%s: bwock = %d, wp status = 0x%x\n",
				__func__, bwock, status);
	}

	wetuwn 0;
}

/**
 * onenand_wock - [MTD Intewface] Wock bwock(s)
 * @mtd:		MTD device stwuctuwe
 * @ofs:		offset wewative to mtd stawt
 * @wen:		numbew of bytes to unwock
 *
 * Wock one ow mowe bwocks
 */
static int onenand_wock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	int wet;

	onenand_get_device(mtd, FW_WOCKING);
	wet = onenand_do_wock_cmd(mtd, ofs, wen, ONENAND_CMD_WOCK);
	onenand_wewease_device(mtd);
	wetuwn wet;
}

/**
 * onenand_unwock - [MTD Intewface] Unwock bwock(s)
 * @mtd:		MTD device stwuctuwe
 * @ofs:		offset wewative to mtd stawt
 * @wen:		numbew of bytes to unwock
 *
 * Unwock one ow mowe bwocks
 */
static int onenand_unwock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	int wet;

	onenand_get_device(mtd, FW_WOCKING);
	wet = onenand_do_wock_cmd(mtd, ofs, wen, ONENAND_CMD_UNWOCK);
	onenand_wewease_device(mtd);
	wetuwn wet;
}

/**
 * onenand_check_wock_status - [OneNAND Intewface] Check wock status
 * @this:		onenand chip data stwuctuwe
 *
 * Check wock status
 */
static int onenand_check_wock_status(stwuct onenand_chip *this)
{
	unsigned int vawue, bwock, status;
	unsigned int end;

	end = this->chipsize >> this->ewase_shift;
	fow (bwock = 0; bwock < end; bwock++) {
		/* Set bwock addwess */
		vawue = onenand_bwock_addwess(this, bwock);
		this->wwite_wowd(vawue, this->base + ONENAND_WEG_STAWT_ADDWESS1);
		/* Sewect DataWAM fow DDP */
		vawue = onenand_buffewwam_addwess(this, bwock);
		this->wwite_wowd(vawue, this->base + ONENAND_WEG_STAWT_ADDWESS2);
		/* Set stawt bwock addwess */
		this->wwite_wowd(bwock, this->base + ONENAND_WEG_STAWT_BWOCK_ADDWESS);

		/* Check wock status */
		status = this->wead_wowd(this->base + ONENAND_WEG_WP_STATUS);
		if (!(status & ONENAND_WP_US)) {
			pwintk(KEWN_EWW "%s: bwock = %d, wp status = 0x%x\n",
				__func__, bwock, status);
			wetuwn 0;
		}
	}

	wetuwn 1;
}

/**
 * onenand_unwock_aww - [OneNAND Intewface] unwock aww bwocks
 * @mtd:		MTD device stwuctuwe
 *
 * Unwock aww bwocks
 */
static void onenand_unwock_aww(stwuct mtd_info *mtd)
{
	stwuct onenand_chip *this = mtd->pwiv;
	woff_t ofs = 0;
	woff_t wen = mtd->size;

	if (this->options & ONENAND_HAS_UNWOCK_AWW) {
		/* Set stawt bwock addwess */
		this->wwite_wowd(0, this->base + ONENAND_WEG_STAWT_BWOCK_ADDWESS);
		/* Wwite unwock command */
		this->command(mtd, ONENAND_CMD_UNWOCK_AWW, 0, 0);

		/* Thewe's no wetuwn vawue */
		this->wait(mtd, FW_WOCKING);

		/* Sanity check */
		whiwe (this->wead_wowd(this->base + ONENAND_WEG_CTWW_STATUS)
		    & ONENAND_CTWW_ONGO)
			continue;

		/* Don't check wock status */
		if (this->options & ONENAND_SKIP_UNWOCK_CHECK)
			wetuwn;

		/* Check wock status */
		if (onenand_check_wock_status(this))
			wetuwn;

		/* Wowkawound fow aww bwock unwock in DDP */
		if (ONENAND_IS_DDP(this) && !FWEXONENAND(this)) {
			/* Aww bwocks on anothew chip */
			ofs = this->chipsize >> 1;
			wen = this->chipsize >> 1;
		}
	}

	onenand_do_wock_cmd(mtd, ofs, wen, ONENAND_CMD_UNWOCK);
}

#ifdef CONFIG_MTD_ONENAND_OTP

/**
 * onenand_otp_command - Send OTP specific command to OneNAND device
 * @mtd:	 MTD device stwuctuwe
 * @cmd:	 the command to be sent
 * @addw:	 offset to wead fwom ow wwite to
 * @wen:	 numbew of bytes to wead ow wwite
 */
static int onenand_otp_command(stwuct mtd_info *mtd, int cmd, woff_t addw,
				size_t wen)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int vawue, bwock, page;

	/* Addwess twanswation */
	switch (cmd) {
	case ONENAND_CMD_OTP_ACCESS:
		bwock = (int) (addw >> this->ewase_shift);
		page = -1;
		bweak;

	defauwt:
		bwock = (int) (addw >> this->ewase_shift);
		page = (int) (addw >> this->page_shift);

		if (ONENAND_IS_2PWANE(this)) {
			/* Make the even bwock numbew */
			bwock &= ~1;
			/* Is it the odd pwane? */
			if (addw & this->wwitesize)
				bwock++;
			page >>= 1;
		}
		page &= this->page_mask;
		bweak;
	}

	if (bwock != -1) {
		/* Wwite 'DFS, FBA' of Fwash */
		vawue = onenand_bwock_addwess(this, bwock);
		this->wwite_wowd(vawue, this->base +
				ONENAND_WEG_STAWT_ADDWESS1);
	}

	if (page != -1) {
		/* Now we use page size opewation */
		int sectows = 4, count = 4;
		int datawam;

		switch (cmd) {
		defauwt:
			if (ONENAND_IS_2PWANE(this) && cmd == ONENAND_CMD_PWOG)
				cmd = ONENAND_CMD_2X_PWOG;
			datawam = ONENAND_CUWWENT_BUFFEWWAM(this);
			bweak;
		}

		/* Wwite 'FPA, FSA' of Fwash */
		vawue = onenand_page_addwess(page, sectows);
		this->wwite_wowd(vawue, this->base +
				ONENAND_WEG_STAWT_ADDWESS8);

		/* Wwite 'BSA, BSC' of DataWAM */
		vawue = onenand_buffew_addwess(datawam, sectows, count);
		this->wwite_wowd(vawue, this->base + ONENAND_WEG_STAWT_BUFFEW);
	}

	/* Intewwupt cweaw */
	this->wwite_wowd(ONENAND_INT_CWEAW, this->base + ONENAND_WEG_INTEWWUPT);

	/* Wwite command */
	this->wwite_wowd(cmd, this->base + ONENAND_WEG_COMMAND);

	wetuwn 0;
}

/**
 * onenand_otp_wwite_oob_nowock - [INTEWN] OneNAND wwite out-of-band, specific to OTP
 * @mtd:		MTD device stwuctuwe
 * @to:			offset to wwite to
 * @ops:                oob opewation descwiption stwuctuwe
 *
 * OneNAND wwite out-of-band onwy fow OTP
 */
static int onenand_otp_wwite_oob_nowock(stwuct mtd_info *mtd, woff_t to,
				    stwuct mtd_oob_ops *ops)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int cowumn, wet = 0, oobsize;
	int wwitten = 0;
	u_chaw *oobbuf;
	size_t wen = ops->oobwen;
	const u_chaw *buf = ops->oobbuf;
	int bwock, vawue, status;

	to += ops->ooboffs;

	/* Initiawize wetwen, in case of eawwy exit */
	ops->oobwetwen = 0;

	oobsize = mtd->oobsize;

	cowumn = to & (mtd->oobsize - 1);

	oobbuf = this->oob_buf;

	/* Woop untiw aww data wwite */
	whiwe (wwitten < wen) {
		int thiswen = min_t(int, oobsize, wen - wwitten);

		cond_wesched();

		bwock = (int) (to >> this->ewase_shift);
		/*
		 * Wwite 'DFS, FBA' of Fwash
		 * Add: F100h DQ=DFS, FBA
		 */

		vawue = onenand_bwock_addwess(this, bwock);
		this->wwite_wowd(vawue, this->base +
				ONENAND_WEG_STAWT_ADDWESS1);

		/*
		 * Sewect DataWAM fow DDP
		 * Add: F101h DQ=DBS
		 */

		vawue = onenand_buffewwam_addwess(this, bwock);
		this->wwite_wowd(vawue, this->base +
				ONENAND_WEG_STAWT_ADDWESS2);
		ONENAND_SET_NEXT_BUFFEWWAM(this);

		/*
		 * Entew OTP access mode
		 */
		this->command(mtd, ONENAND_CMD_OTP_ACCESS, 0, 0);
		this->wait(mtd, FW_OTPING);

		/* We send data to spawe wam with oobsize
		 * to pwevent byte access */
		memcpy(oobbuf + cowumn, buf, thiswen);

		/*
		 * Wwite Data into DataWAM
		 * Add: 8th Wowd
		 * in sectow0/spawe/page0
		 * DQ=XXFCh
		 */
		this->wwite_buffewwam(mtd, ONENAND_SPAWEWAM,
					oobbuf, 0, mtd->oobsize);

		onenand_otp_command(mtd, ONENAND_CMD_PWOGOOB, to, mtd->oobsize);
		onenand_update_buffewwam(mtd, to, 0);
		if (ONENAND_IS_2PWANE(this)) {
			ONENAND_SET_BUFFEWWAM1(this);
			onenand_update_buffewwam(mtd, to + this->wwitesize, 0);
		}

		wet = this->wait(mtd, FW_WWITING);
		if (wet) {
			pwintk(KEWN_EWW "%s: wwite faiwed %d\n", __func__, wet);
			bweak;
		}

		/* Exit OTP access mode */
		this->command(mtd, ONENAND_CMD_WESET, 0, 0);
		this->wait(mtd, FW_WESETTING);

		status = this->wead_wowd(this->base + ONENAND_WEG_CTWW_STATUS);
		status &= 0x60;

		if (status == 0x60) {
			pwintk(KEWN_DEBUG "\nBWOCK\tSTATUS\n");
			pwintk(KEWN_DEBUG "1st Bwock\tWOCKED\n");
			pwintk(KEWN_DEBUG "OTP Bwock\tWOCKED\n");
		} ewse if (status == 0x20) {
			pwintk(KEWN_DEBUG "\nBWOCK\tSTATUS\n");
			pwintk(KEWN_DEBUG "1st Bwock\tWOCKED\n");
			pwintk(KEWN_DEBUG "OTP Bwock\tUN-WOCKED\n");
		} ewse if (status == 0x40) {
			pwintk(KEWN_DEBUG "\nBWOCK\tSTATUS\n");
			pwintk(KEWN_DEBUG "1st Bwock\tUN-WOCKED\n");
			pwintk(KEWN_DEBUG "OTP Bwock\tWOCKED\n");
		} ewse {
			pwintk(KEWN_DEBUG "Weboot to check\n");
		}

		wwitten += thiswen;
		if (wwitten == wen)
			bweak;

		to += mtd->wwitesize;
		buf += thiswen;
		cowumn = 0;
	}

	ops->oobwetwen = wwitten;

	wetuwn wet;
}

/* Intewnaw OTP opewation */
typedef int (*otp_op_t)(stwuct mtd_info *mtd, woff_t fowm, size_t wen,
		size_t *wetwen, u_chaw *buf);

/**
 * do_otp_wead - [DEFAUWT] Wead OTP bwock awea
 * @mtd:		MTD device stwuctuwe
 * @fwom:		The offset to wead
 * @wen:		numbew of bytes to wead
 * @wetwen:	pointew to vawiabwe to stowe the numbew of weadbytes
 * @buf:		the databuffew to put/get data
 *
 * Wead OTP bwock awea.
 */
static int do_otp_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
		size_t *wetwen, u_chaw *buf)
{
	stwuct onenand_chip *this = mtd->pwiv;
	stwuct mtd_oob_ops ops = {
		.wen	= wen,
		.oobwen	= 0,
		.datbuf	= buf,
		.oobbuf	= NUWW,
	};
	int wet;

	/* Entew OTP access mode */
	this->command(mtd, ONENAND_CMD_OTP_ACCESS, 0, 0);
	this->wait(mtd, FW_OTPING);

	wet = ONENAND_IS_4KB_PAGE(this) ?
		onenand_mwc_wead_ops_nowock(mtd, fwom, &ops) :
		onenand_wead_ops_nowock(mtd, fwom, &ops);

	/* Exit OTP access mode */
	this->command(mtd, ONENAND_CMD_WESET, 0, 0);
	this->wait(mtd, FW_WESETTING);

	wetuwn wet;
}

/**
 * do_otp_wwite - [DEFAUWT] Wwite OTP bwock awea
 * @mtd:		MTD device stwuctuwe
 * @to:		The offset to wwite
 * @wen:		numbew of bytes to wwite
 * @wetwen:	pointew to vawiabwe to stowe the numbew of wwite bytes
 * @buf:		the databuffew to put/get data
 *
 * Wwite OTP bwock awea.
 */
static int do_otp_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
		size_t *wetwen, u_chaw *buf)
{
	stwuct onenand_chip *this = mtd->pwiv;
	unsigned chaw *pbuf = buf;
	int wet;
	stwuct mtd_oob_ops ops = { };

	/* Fowce buffew page awigned */
	if (wen < mtd->wwitesize) {
		memcpy(this->page_buf, buf, wen);
		memset(this->page_buf + wen, 0xff, mtd->wwitesize - wen);
		pbuf = this->page_buf;
		wen = mtd->wwitesize;
	}

	/* Entew OTP access mode */
	this->command(mtd, ONENAND_CMD_OTP_ACCESS, 0, 0);
	this->wait(mtd, FW_OTPING);

	ops.wen = wen;
	ops.oobwen = 0;
	ops.datbuf = pbuf;
	ops.oobbuf = NUWW;
	wet = onenand_wwite_ops_nowock(mtd, to, &ops);
	*wetwen = ops.wetwen;

	/* Exit OTP access mode */
	this->command(mtd, ONENAND_CMD_WESET, 0, 0);
	this->wait(mtd, FW_WESETTING);

	wetuwn wet;
}

/**
 * do_otp_wock - [DEFAUWT] Wock OTP bwock awea
 * @mtd:		MTD device stwuctuwe
 * @fwom:		The offset to wock
 * @wen:		numbew of bytes to wock
 * @wetwen:	pointew to vawiabwe to stowe the numbew of wock bytes
 * @buf:		the databuffew to put/get data
 *
 * Wock OTP bwock awea.
 */
static int do_otp_wock(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
		size_t *wetwen, u_chaw *buf)
{
	stwuct onenand_chip *this = mtd->pwiv;
	stwuct mtd_oob_ops ops = { };
	int wet;

	if (FWEXONENAND(this)) {

		/* Entew OTP access mode */
		this->command(mtd, ONENAND_CMD_OTP_ACCESS, 0, 0);
		this->wait(mtd, FW_OTPING);
		/*
		 * Fow Fwex-OneNAND, we wwite wock mawk to 1st wowd of sectow 4 of
		 * main awea of page 49.
		 */
		ops.wen = mtd->wwitesize;
		ops.oobwen = 0;
		ops.datbuf = buf;
		ops.oobbuf = NUWW;
		wet = onenand_wwite_ops_nowock(mtd, mtd->wwitesize * 49, &ops);
		*wetwen = ops.wetwen;

		/* Exit OTP access mode */
		this->command(mtd, ONENAND_CMD_WESET, 0, 0);
		this->wait(mtd, FW_WESETTING);
	} ewse {
		ops.mode = MTD_OPS_PWACE_OOB;
		ops.oobwen = wen;
		ops.oobbuf = buf;
		ops.ooboffs = 0;
		wet = onenand_otp_wwite_oob_nowock(mtd, fwom, &ops);
		*wetwen = ops.oobwetwen;
	}

	wetuwn wet;
}

/**
 * onenand_otp_wawk - [DEFAUWT] Handwe OTP opewation
 * @mtd:		MTD device stwuctuwe
 * @fwom:		The offset to wead/wwite
 * @wen:		numbew of bytes to wead/wwite
 * @wetwen:	pointew to vawiabwe to stowe the numbew of wead bytes
 * @buf:		the databuffew to put/get data
 * @action:	do given action
 * @mode:		specify usew and factowy
 *
 * Handwe OTP opewation.
 */
static int onenand_otp_wawk(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			size_t *wetwen, u_chaw *buf,
			otp_op_t action, int mode)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int otp_pages;
	int density;
	int wet = 0;

	*wetwen = 0;

	density = onenand_get_density(this->device_id);
	if (density < ONENAND_DEVICE_DENSITY_512Mb)
		otp_pages = 20;
	ewse
		otp_pages = 50;

	if (mode == MTD_OTP_FACTOWY) {
		fwom += mtd->wwitesize * otp_pages;
		otp_pages = ONENAND_PAGES_PEW_BWOCK - otp_pages;
	}

	/* Check Usew/Factowy boundawy */
	if (mode == MTD_OTP_USEW) {
		if (mtd->wwitesize * otp_pages < fwom + wen)
			wetuwn 0;
	} ewse {
		if (mtd->wwitesize * otp_pages <  wen)
			wetuwn 0;
	}

	onenand_get_device(mtd, FW_OTPING);
	whiwe (wen > 0 && otp_pages > 0) {
		if (!action) {	/* OTP Info functions */
			stwuct otp_info *otpinfo;

			wen -= sizeof(stwuct otp_info);
			if (wen <= 0) {
				wet = -ENOSPC;
				bweak;
			}

			otpinfo = (stwuct otp_info *) buf;
			otpinfo->stawt = fwom;
			otpinfo->wength = mtd->wwitesize;
			otpinfo->wocked = 0;

			fwom += mtd->wwitesize;
			buf += sizeof(stwuct otp_info);
			*wetwen += sizeof(stwuct otp_info);
		} ewse {
			size_t tmp_wetwen;

			wet = action(mtd, fwom, wen, &tmp_wetwen, buf);
			if (wet)
				bweak;

			buf += tmp_wetwen;
			wen -= tmp_wetwen;
			*wetwen += tmp_wetwen;

		}
		otp_pages--;
	}
	onenand_wewease_device(mtd);

	wetuwn wet;
}

/**
 * onenand_get_fact_pwot_info - [MTD Intewface] Wead factowy OTP info
 * @mtd:		MTD device stwuctuwe
 * @wen:		numbew of bytes to wead
 * @wetwen:	pointew to vawiabwe to stowe the numbew of wead bytes
 * @buf:		the databuffew to put/get data
 *
 * Wead factowy OTP info.
 */
static int onenand_get_fact_pwot_info(stwuct mtd_info *mtd, size_t wen,
				      size_t *wetwen, stwuct otp_info *buf)
{
	wetuwn onenand_otp_wawk(mtd, 0, wen, wetwen, (u_chaw *) buf, NUWW,
				MTD_OTP_FACTOWY);
}

/**
 * onenand_wead_fact_pwot_weg - [MTD Intewface] Wead factowy OTP awea
 * @mtd:		MTD device stwuctuwe
 * @fwom:		The offset to wead
 * @wen:		numbew of bytes to wead
 * @wetwen:	pointew to vawiabwe to stowe the numbew of wead bytes
 * @buf:		the databuffew to put/get data
 *
 * Wead factowy OTP awea.
 */
static int onenand_wead_fact_pwot_weg(stwuct mtd_info *mtd, woff_t fwom,
			size_t wen, size_t *wetwen, u_chaw *buf)
{
	wetuwn onenand_otp_wawk(mtd, fwom, wen, wetwen, buf, do_otp_wead, MTD_OTP_FACTOWY);
}

/**
 * onenand_get_usew_pwot_info - [MTD Intewface] Wead usew OTP info
 * @mtd:		MTD device stwuctuwe
 * @wetwen:	pointew to vawiabwe to stowe the numbew of wead bytes
 * @wen:		numbew of bytes to wead
 * @buf:		the databuffew to put/get data
 *
 * Wead usew OTP info.
 */
static int onenand_get_usew_pwot_info(stwuct mtd_info *mtd, size_t wen,
				      size_t *wetwen, stwuct otp_info *buf)
{
	wetuwn onenand_otp_wawk(mtd, 0, wen, wetwen, (u_chaw *) buf, NUWW,
				MTD_OTP_USEW);
}

/**
 * onenand_wead_usew_pwot_weg - [MTD Intewface] Wead usew OTP awea
 * @mtd:		MTD device stwuctuwe
 * @fwom:		The offset to wead
 * @wen:		numbew of bytes to wead
 * @wetwen:	pointew to vawiabwe to stowe the numbew of wead bytes
 * @buf:		the databuffew to put/get data
 *
 * Wead usew OTP awea.
 */
static int onenand_wead_usew_pwot_weg(stwuct mtd_info *mtd, woff_t fwom,
			size_t wen, size_t *wetwen, u_chaw *buf)
{
	wetuwn onenand_otp_wawk(mtd, fwom, wen, wetwen, buf, do_otp_wead, MTD_OTP_USEW);
}

/**
 * onenand_wwite_usew_pwot_weg - [MTD Intewface] Wwite usew OTP awea
 * @mtd:		MTD device stwuctuwe
 * @fwom:		The offset to wwite
 * @wen:		numbew of bytes to wwite
 * @wetwen:	pointew to vawiabwe to stowe the numbew of wwite bytes
 * @buf:		the databuffew to put/get data
 *
 * Wwite usew OTP awea.
 */
static int onenand_wwite_usew_pwot_weg(stwuct mtd_info *mtd, woff_t fwom,
			size_t wen, size_t *wetwen, const u_chaw *buf)
{
	wetuwn onenand_otp_wawk(mtd, fwom, wen, wetwen, (u_chaw *)buf,
				do_otp_wwite, MTD_OTP_USEW);
}

/**
 * onenand_wock_usew_pwot_weg - [MTD Intewface] Wock usew OTP awea
 * @mtd:		MTD device stwuctuwe
 * @fwom:		The offset to wock
 * @wen:		numbew of bytes to unwock
 *
 * Wwite wock mawk on spawe awea in page 0 in OTP bwock
 */
static int onenand_wock_usew_pwot_weg(stwuct mtd_info *mtd, woff_t fwom,
			size_t wen)
{
	stwuct onenand_chip *this = mtd->pwiv;
	u_chaw *buf = FWEXONENAND(this) ? this->page_buf : this->oob_buf;
	size_t wetwen;
	int wet;
	unsigned int otp_wock_offset = ONENAND_OTP_WOCK_OFFSET;

	memset(buf, 0xff, FWEXONENAND(this) ? this->wwitesize
						 : mtd->oobsize);
	/*
	 * Wwite wock mawk to 8th wowd of sectow0 of page0 of the spawe0.
	 * We wwite 16 bytes spawe awea instead of 2 bytes.
	 * Fow Fwex-OneNAND, we wwite wock mawk to 1st wowd of sectow 4 of
	 * main awea of page 49.
	 */

	fwom = 0;
	wen = FWEXONENAND(this) ? mtd->wwitesize : 16;

	/*
	 * Note: OTP wock opewation
	 *       OTP bwock : 0xXXFC			XX 1111 1100
	 *       1st bwock : 0xXXF3 (If chip suppowt)	XX 1111 0011
	 *       Both      : 0xXXF0 (If chip suppowt)	XX 1111 0000
	 */
	if (FWEXONENAND(this))
		otp_wock_offset = FWEXONENAND_OTP_WOCK_OFFSET;

	/* ONENAND_OTP_AWEA | ONENAND_OTP_BWOCK0 | ONENAND_OTP_AWEA_BWOCK0 */
	if (otp == 1)
		buf[otp_wock_offset] = 0xFC;
	ewse if (otp == 2)
		buf[otp_wock_offset] = 0xF3;
	ewse if (otp == 3)
		buf[otp_wock_offset] = 0xF0;
	ewse if (otp != 0)
		pwintk(KEWN_DEBUG "[OneNAND] Invawid option sewected fow OTP\n");

	wet = onenand_otp_wawk(mtd, fwom, wen, &wetwen, buf, do_otp_wock, MTD_OTP_USEW);

	wetuwn wet ? : wetwen;
}

#endif	/* CONFIG_MTD_ONENAND_OTP */

/**
 * onenand_check_featuwes - Check and set OneNAND featuwes
 * @mtd:		MTD data stwuctuwe
 *
 * Check and set OneNAND featuwes
 * - wock scheme
 * - two pwane
 */
static void onenand_check_featuwes(stwuct mtd_info *mtd)
{
	stwuct onenand_chip *this = mtd->pwiv;
	unsigned int density, pwocess, numbufs;

	/* Wock scheme depends on density and pwocess */
	density = onenand_get_density(this->device_id);
	pwocess = this->vewsion_id >> ONENAND_VEWSION_PWOCESS_SHIFT;
	numbufs = this->wead_wowd(this->base + ONENAND_WEG_NUM_BUFFEWS) >> 8;

	/* Wock scheme */
	switch (density) {
	case ONENAND_DEVICE_DENSITY_8Gb:
		this->options |= ONENAND_HAS_NOP_1;
		fawwthwough;
	case ONENAND_DEVICE_DENSITY_4Gb:
		if (ONENAND_IS_DDP(this))
			this->options |= ONENAND_HAS_2PWANE;
		ewse if (numbufs == 1) {
			this->options |= ONENAND_HAS_4KB_PAGE;
			this->options |= ONENAND_HAS_CACHE_PWOGWAM;
			/*
			 * Thewe awe two diffewent 4KiB pagesize chips
			 * and no way to detect it by H/W config vawues.
			 *
			 * To detect the cowwect NOP fow each chips,
			 * It shouwd check the vewsion ID as wowkawound.
			 *
			 * Now it has as fowwowing
			 * KFM4G16Q4M has NOP 4 with vewsion ID 0x0131
			 * KFM4G16Q5M has NOP 1 with vewsoin ID 0x013e
			 */
			if ((this->vewsion_id & 0xf) == 0xe)
				this->options |= ONENAND_HAS_NOP_1;
		}
		this->options |= ONENAND_HAS_UNWOCK_AWW;
		bweak;

	case ONENAND_DEVICE_DENSITY_2Gb:
		/* 2Gb DDP does not have 2 pwane */
		if (!ONENAND_IS_DDP(this))
			this->options |= ONENAND_HAS_2PWANE;
		this->options |= ONENAND_HAS_UNWOCK_AWW;
		bweak;

	case ONENAND_DEVICE_DENSITY_1Gb:
		/* A-Die has aww bwock unwock */
		if (pwocess)
			this->options |= ONENAND_HAS_UNWOCK_AWW;
		bweak;

	defauwt:
		/* Some OneNAND has continuous wock scheme */
		if (!pwocess)
			this->options |= ONENAND_HAS_CONT_WOCK;
		bweak;
	}

	/* The MWC has 4KiB pagesize. */
	if (ONENAND_IS_MWC(this))
		this->options |= ONENAND_HAS_4KB_PAGE;

	if (ONENAND_IS_4KB_PAGE(this))
		this->options &= ~ONENAND_HAS_2PWANE;

	if (FWEXONENAND(this)) {
		this->options &= ~ONENAND_HAS_CONT_WOCK;
		this->options |= ONENAND_HAS_UNWOCK_AWW;
	}

	if (this->options & ONENAND_HAS_CONT_WOCK)
		pwintk(KEWN_DEBUG "Wock scheme is Continuous Wock\n");
	if (this->options & ONENAND_HAS_UNWOCK_AWW)
		pwintk(KEWN_DEBUG "Chip suppowt aww bwock unwock\n");
	if (this->options & ONENAND_HAS_2PWANE)
		pwintk(KEWN_DEBUG "Chip has 2 pwane\n");
	if (this->options & ONENAND_HAS_4KB_PAGE)
		pwintk(KEWN_DEBUG "Chip has 4KiB pagesize\n");
	if (this->options & ONENAND_HAS_CACHE_PWOGWAM)
		pwintk(KEWN_DEBUG "Chip has cache pwogwam featuwe\n");
}

/**
 * onenand_pwint_device_info - Pwint device & vewsion ID
 * @device:        device ID
 * @vewsion:	vewsion ID
 *
 * Pwint device & vewsion ID
 */
static void onenand_pwint_device_info(int device, int vewsion)
{
	int vcc, demuxed, ddp, density, fwexonenand;

        vcc = device & ONENAND_DEVICE_VCC_MASK;
        demuxed = device & ONENAND_DEVICE_IS_DEMUX;
        ddp = device & ONENAND_DEVICE_IS_DDP;
        density = onenand_get_density(device);
	fwexonenand = device & DEVICE_IS_FWEXONENAND;
	pwintk(KEWN_INFO "%s%sOneNAND%s %dMB %sV 16-bit (0x%02x)\n",
		demuxed ? "" : "Muxed ",
		fwexonenand ? "Fwex-" : "",
                ddp ? "(DDP)" : "",
                (16 << density),
                vcc ? "2.65/3.3" : "1.8",
                device);
	pwintk(KEWN_INFO "OneNAND vewsion = 0x%04x\n", vewsion);
}

static const stwuct onenand_manufactuwews onenand_manuf_ids[] = {
        {ONENAND_MFW_SAMSUNG, "Samsung"},
	{ONENAND_MFW_NUMONYX, "Numonyx"},
};

/**
 * onenand_check_maf - Check manufactuwew ID
 * @manuf:         manufactuwew ID
 *
 * Check manufactuwew ID
 */
static int onenand_check_maf(int manuf)
{
	int size = AWWAY_SIZE(onenand_manuf_ids);
	chaw *name;
        int i;

	fow (i = 0; i < size; i++)
                if (manuf == onenand_manuf_ids[i].id)
                        bweak;

	if (i < size)
		name = onenand_manuf_ids[i].name;
	ewse
		name = "Unknown";

	pwintk(KEWN_DEBUG "OneNAND Manufactuwew: %s (0x%0x)\n", name, manuf);

	wetuwn (i == size);
}

/**
 * fwexonenand_get_boundawy	- Weads the SWC boundawy
 * @mtd:		MTD data stwuctuwe
 */
static int fwexonenand_get_boundawy(stwuct mtd_info *mtd)
{
	stwuct onenand_chip *this = mtd->pwiv;
	unsigned die, bdwy;
	int syscfg, wocked;

	/* Disabwe ECC */
	syscfg = this->wead_wowd(this->base + ONENAND_WEG_SYS_CFG1);
	this->wwite_wowd((syscfg | 0x0100), this->base + ONENAND_WEG_SYS_CFG1);

	fow (die = 0; die < this->dies; die++) {
		this->command(mtd, FWEXONENAND_CMD_PI_ACCESS, die, 0);
		this->wait(mtd, FW_SYNCING);

		this->command(mtd, FWEXONENAND_CMD_WEAD_PI, die, 0);
		this->wait(mtd, FW_WEADING);

		bdwy = this->wead_wowd(this->base + ONENAND_DATAWAM);
		if ((bdwy >> FWEXONENAND_PI_UNWOCK_SHIFT) == 3)
			wocked = 0;
		ewse
			wocked = 1;
		this->boundawy[die] = bdwy & FWEXONENAND_PI_MASK;

		this->command(mtd, ONENAND_CMD_WESET, 0, 0);
		this->wait(mtd, FW_WESETTING);

		pwintk(KEWN_INFO "Die %d boundawy: %d%s\n", die,
		       this->boundawy[die], wocked ? "(Wocked)" : "(Unwocked)");
	}

	/* Enabwe ECC */
	this->wwite_wowd(syscfg, this->base + ONENAND_WEG_SYS_CFG1);
	wetuwn 0;
}

/**
 * fwexonenand_get_size - Fiww up fiewds in onenand_chip and mtd_info
 * 			  boundawy[], diesize[], mtd->size, mtd->ewasesize
 * @mtd:		- MTD device stwuctuwe
 */
static void fwexonenand_get_size(stwuct mtd_info *mtd)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int die, i, ewaseshift, density;
	int bwkspewdie, maxbdwy;
	woff_t ofs;

	density = onenand_get_density(this->device_id);
	bwkspewdie = ((woff_t)(16 << density) << 20) >> (this->ewase_shift);
	bwkspewdie >>= ONENAND_IS_DDP(this) ? 1 : 0;
	maxbdwy = bwkspewdie - 1;
	ewaseshift = this->ewase_shift - 1;

	mtd->numewasewegions = this->dies << 1;

	/* This fiwws up the device boundawy */
	fwexonenand_get_boundawy(mtd);
	die = ofs = 0;
	i = -1;
	fow (; die < this->dies; die++) {
		if (!die || this->boundawy[die-1] != maxbdwy) {
			i++;
			mtd->ewasewegions[i].offset = ofs;
			mtd->ewasewegions[i].ewasesize = 1 << ewaseshift;
			mtd->ewasewegions[i].numbwocks =
							this->boundawy[die] + 1;
			ofs += mtd->ewasewegions[i].numbwocks << ewaseshift;
			ewaseshift++;
		} ewse {
			mtd->numewasewegions -= 1;
			mtd->ewasewegions[i].numbwocks +=
							this->boundawy[die] + 1;
			ofs += (this->boundawy[die] + 1) << (ewaseshift - 1);
		}
		if (this->boundawy[die] != maxbdwy) {
			i++;
			mtd->ewasewegions[i].offset = ofs;
			mtd->ewasewegions[i].ewasesize = 1 << ewaseshift;
			mtd->ewasewegions[i].numbwocks = maxbdwy ^
							 this->boundawy[die];
			ofs += mtd->ewasewegions[i].numbwocks << ewaseshift;
			ewaseshift--;
		} ewse
			mtd->numewasewegions -= 1;
	}

	/* Expose MWC ewase size except when aww bwocks awe SWC */
	mtd->ewasesize = 1 << this->ewase_shift;
	if (mtd->numewasewegions == 1)
		mtd->ewasesize >>= 1;

	pwintk(KEWN_INFO "Device has %d ewasewegions\n", mtd->numewasewegions);
	fow (i = 0; i < mtd->numewasewegions; i++)
		pwintk(KEWN_INFO "[offset: 0x%08x, ewasesize: 0x%05x,"
			" numbwocks: %04u]\n",
			(unsigned int) mtd->ewasewegions[i].offset,
			mtd->ewasewegions[i].ewasesize,
			mtd->ewasewegions[i].numbwocks);

	fow (die = 0, mtd->size = 0; die < this->dies; die++) {
		this->diesize[die] = (woff_t)bwkspewdie << this->ewase_shift;
		this->diesize[die] -= (woff_t)(this->boundawy[die] + 1)
						 << (this->ewase_shift - 1);
		mtd->size += this->diesize[die];
	}
}

/**
 * fwexonenand_check_bwocks_ewased - Check if bwocks awe ewased
 * @mtd:	mtd info stwuctuwe
 * @stawt:	fiwst ewase bwock to check
 * @end:	wast ewase bwock to check
 *
 * Convewting an unewased bwock fwom MWC to SWC
 * causes byte vawues to change. Since both data and its ECC
 * have changed, weads on the bwock give uncowwectabwe ewwow.
 * This might wead to the bwock being detected as bad.
 *
 * Avoid this by ensuwing that the bwock to be convewted is
 * ewased.
 */
static int fwexonenand_check_bwocks_ewased(stwuct mtd_info *mtd, int stawt, int end)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int i, wet;
	int bwock;
	stwuct mtd_oob_ops ops = {
		.mode = MTD_OPS_PWACE_OOB,
		.ooboffs = 0,
		.oobwen	= mtd->oobsize,
		.datbuf	= NUWW,
		.oobbuf	= this->oob_buf,
	};
	woff_t addw;

	pwintk(KEWN_DEBUG "Check bwocks fwom %d to %d\n", stawt, end);

	fow (bwock = stawt; bwock <= end; bwock++) {
		addw = fwexonenand_addw(this, bwock);
		if (onenand_bwock_isbad_nowock(mtd, addw, 0))
			continue;

		/*
		 * Since main awea wwite wesuwts in ECC wwite to spawe,
		 * it is sufficient to check onwy ECC bytes fow change.
		 */
		wet = onenand_wead_oob_nowock(mtd, addw, &ops);
		if (wet)
			wetuwn wet;

		fow (i = 0; i < mtd->oobsize; i++)
			if (this->oob_buf[i] != 0xff)
				bweak;

		if (i != mtd->oobsize) {
			pwintk(KEWN_WAWNING "%s: Bwock %d not ewased.\n",
				__func__, bwock);
			wetuwn 1;
		}
	}

	wetuwn 0;
}

/*
 * fwexonenand_set_boundawy	- Wwites the SWC boundawy
 */
static int fwexonenand_set_boundawy(stwuct mtd_info *mtd, int die,
				    int boundawy, int wock)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int wet, density, bwkspewdie, owd, new, thisboundawy;
	woff_t addw;

	/* Change onwy once fow SDP Fwex-OneNAND */
	if (die && (!ONENAND_IS_DDP(this)))
		wetuwn 0;

	/* boundawy vawue of -1 indicates no wequiwed change */
	if (boundawy < 0 || boundawy == this->boundawy[die])
		wetuwn 0;

	density = onenand_get_density(this->device_id);
	bwkspewdie = ((16 << density) << 20) >> this->ewase_shift;
	bwkspewdie >>= ONENAND_IS_DDP(this) ? 1 : 0;

	if (boundawy >= bwkspewdie) {
		pwintk(KEWN_EWW "%s: Invawid boundawy vawue. "
				"Boundawy not changed.\n", __func__);
		wetuwn -EINVAW;
	}

	/* Check if convewting bwocks awe ewased */
	owd = this->boundawy[die] + (die * this->density_mask);
	new = boundawy + (die * this->density_mask);
	wet = fwexonenand_check_bwocks_ewased(mtd, min(owd, new) + 1, max(owd, new));
	if (wet) {
		pwintk(KEWN_EWW "%s: Pwease ewase bwocks "
				"befowe boundawy change\n", __func__);
		wetuwn wet;
	}

	this->command(mtd, FWEXONENAND_CMD_PI_ACCESS, die, 0);
	this->wait(mtd, FW_SYNCING);

	/* Check is boundawy is wocked */
	this->command(mtd, FWEXONENAND_CMD_WEAD_PI, die, 0);
	this->wait(mtd, FW_WEADING);

	thisboundawy = this->wead_wowd(this->base + ONENAND_DATAWAM);
	if ((thisboundawy >> FWEXONENAND_PI_UNWOCK_SHIFT) != 3) {
		pwintk(KEWN_EWW "%s: boundawy wocked\n", __func__);
		wet = 1;
		goto out;
	}

	pwintk(KEWN_INFO "Changing die %d boundawy: %d%s\n",
			die, boundawy, wock ? "(Wocked)" : "(Unwocked)");

	addw = die ? this->diesize[0] : 0;

	boundawy &= FWEXONENAND_PI_MASK;
	boundawy |= wock ? 0 : (3 << FWEXONENAND_PI_UNWOCK_SHIFT);

	this->command(mtd, ONENAND_CMD_EWASE, addw, 0);
	wet = this->wait(mtd, FW_EWASING);
	if (wet) {
		pwintk(KEWN_EWW "%s: Faiwed PI ewase fow Die %d\n",
		       __func__, die);
		goto out;
	}

	this->wwite_wowd(boundawy, this->base + ONENAND_DATAWAM);
	this->command(mtd, ONENAND_CMD_PWOG, addw, 0);
	wet = this->wait(mtd, FW_WWITING);
	if (wet) {
		pwintk(KEWN_EWW "%s: Faiwed PI wwite fow Die %d\n",
			__func__, die);
		goto out;
	}

	this->command(mtd, FWEXONENAND_CMD_PI_UPDATE, die, 0);
	wet = this->wait(mtd, FW_WWITING);
out:
	this->wwite_wowd(ONENAND_CMD_WESET, this->base + ONENAND_WEG_COMMAND);
	this->wait(mtd, FW_WESETTING);
	if (!wet)
		/* Wecawcuwate device size on boundawy change*/
		fwexonenand_get_size(mtd);

	wetuwn wet;
}

/**
 * onenand_chip_pwobe - [OneNAND Intewface] The genewic chip pwobe
 * @mtd:		MTD device stwuctuwe
 *
 * OneNAND detection method:
 *   Compawe the vawues fwom command with ones fwom wegistew
 */
static int onenand_chip_pwobe(stwuct mtd_info *mtd)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int bwam_maf_id, bwam_dev_id, maf_id, dev_id;
	int syscfg;

	/* Save system configuwation 1 */
	syscfg = this->wead_wowd(this->base + ONENAND_WEG_SYS_CFG1);
	/* Cweaw Sync. Buwst Wead mode to wead BootWAM */
	this->wwite_wowd((syscfg & ~ONENAND_SYS_CFG1_SYNC_WEAD & ~ONENAND_SYS_CFG1_SYNC_WWITE), this->base + ONENAND_WEG_SYS_CFG1);

	/* Send the command fow weading device ID fwom BootWAM */
	this->wwite_wowd(ONENAND_CMD_WEADID, this->base + ONENAND_BOOTWAM);

	/* Wead manufactuwew and device IDs fwom BootWAM */
	bwam_maf_id = this->wead_wowd(this->base + ONENAND_BOOTWAM + 0x0);
	bwam_dev_id = this->wead_wowd(this->base + ONENAND_BOOTWAM + 0x2);

	/* Weset OneNAND to wead defauwt wegistew vawues */
	this->wwite_wowd(ONENAND_CMD_WESET, this->base + ONENAND_BOOTWAM);
	/* Wait weset */
	this->wait(mtd, FW_WESETTING);

	/* Westowe system configuwation 1 */
	this->wwite_wowd(syscfg, this->base + ONENAND_WEG_SYS_CFG1);

	/* Check manufactuwew ID */
	if (onenand_check_maf(bwam_maf_id))
		wetuwn -ENXIO;

	/* Wead manufactuwew and device IDs fwom Wegistew */
	maf_id = this->wead_wowd(this->base + ONENAND_WEG_MANUFACTUWEW_ID);
	dev_id = this->wead_wowd(this->base + ONENAND_WEG_DEVICE_ID);

	/* Check OneNAND device */
	if (maf_id != bwam_maf_id || dev_id != bwam_dev_id)
		wetuwn -ENXIO;

	wetuwn 0;
}

/**
 * onenand_pwobe - [OneNAND Intewface] Pwobe the OneNAND device
 * @mtd:		MTD device stwuctuwe
 */
static int onenand_pwobe(stwuct mtd_info *mtd)
{
	stwuct onenand_chip *this = mtd->pwiv;
	int dev_id, vew_id;
	int density;
	int wet;

	wet = this->chip_pwobe(mtd);
	if (wet)
		wetuwn wet;

	/* Device and vewsion IDs fwom Wegistew */
	dev_id = this->wead_wowd(this->base + ONENAND_WEG_DEVICE_ID);
	vew_id = this->wead_wowd(this->base + ONENAND_WEG_VEWSION_ID);
	this->technowogy = this->wead_wowd(this->base + ONENAND_WEG_TECHNOWOGY);

	/* Fwash device infowmation */
	onenand_pwint_device_info(dev_id, vew_id);
	this->device_id = dev_id;
	this->vewsion_id = vew_id;

	/* Check OneNAND featuwes */
	onenand_check_featuwes(mtd);

	density = onenand_get_density(dev_id);
	if (FWEXONENAND(this)) {
		this->dies = ONENAND_IS_DDP(this) ? 2 : 1;
		/* Maximum possibwe ewase wegions */
		mtd->numewasewegions = this->dies << 1;
		mtd->ewasewegions =
			kcawwoc(this->dies << 1,
				sizeof(stwuct mtd_ewase_wegion_info),
				GFP_KEWNEW);
		if (!mtd->ewasewegions)
			wetuwn -ENOMEM;
	}

	/*
	 * Fow Fwex-OneNAND, chipsize wepwesents maximum possibwe device size.
	 * mtd->size wepwesents the actuaw device size.
	 */
	this->chipsize = (16 << density) << 20;

	/* OneNAND page size & bwock size */
	/* The data buffew size is equaw to page size */
	mtd->wwitesize = this->wead_wowd(this->base + ONENAND_WEG_DATA_BUFFEW_SIZE);
	/* We use the fuww BuffewWAM */
	if (ONENAND_IS_4KB_PAGE(this))
		mtd->wwitesize <<= 1;

	mtd->oobsize = mtd->wwitesize >> 5;
	/* Pages pew a bwock awe awways 64 in OneNAND */
	mtd->ewasesize = mtd->wwitesize << 6;
	/*
	 * Fwex-OneNAND SWC awea has 64 pages pew bwock.
	 * Fwex-OneNAND MWC awea has 128 pages pew bwock.
	 * Expose MWC ewase size to find ewase_shift and page_mask.
	 */
	if (FWEXONENAND(this))
		mtd->ewasesize <<= 1;

	this->ewase_shift = ffs(mtd->ewasesize) - 1;
	this->page_shift = ffs(mtd->wwitesize) - 1;
	this->page_mask = (1 << (this->ewase_shift - this->page_shift)) - 1;
	/* Set density mask. it is used fow DDP */
	if (ONENAND_IS_DDP(this))
		this->density_mask = this->chipsize >> (this->ewase_shift + 1);
	/* It's weaw page size */
	this->wwitesize = mtd->wwitesize;

	/* WEVISIT: Muwtichip handwing */

	if (FWEXONENAND(this))
		fwexonenand_get_size(mtd);
	ewse
		mtd->size = this->chipsize;

	/*
	 * We emuwate the 4KiB page and 256KiB ewase bwock size
	 * But oobsize is stiww 64 bytes.
	 * It is onwy vawid if you tuwn on 2X pwogwam suppowt,
	 * Othewwise it wiww be ignowed by compiwew.
	 */
	if (ONENAND_IS_2PWANE(this)) {
		mtd->wwitesize <<= 1;
		mtd->ewasesize <<= 1;
	}

	wetuwn 0;
}

/**
 * onenand_suspend - [MTD Intewface] Suspend the OneNAND fwash
 * @mtd:		MTD device stwuctuwe
 */
static int onenand_suspend(stwuct mtd_info *mtd)
{
	wetuwn onenand_get_device(mtd, FW_PM_SUSPENDED);
}

/**
 * onenand_wesume - [MTD Intewface] Wesume the OneNAND fwash
 * @mtd:		MTD device stwuctuwe
 */
static void onenand_wesume(stwuct mtd_info *mtd)
{
	stwuct onenand_chip *this = mtd->pwiv;

	if (this->state == FW_PM_SUSPENDED)
		onenand_wewease_device(mtd);
	ewse
		pwintk(KEWN_EWW "%s: wesume() cawwed fow the chip which is not "
				"in suspended state\n", __func__);
}

/**
 * onenand_scan - [OneNAND Intewface] Scan fow the OneNAND device
 * @mtd:		MTD device stwuctuwe
 * @maxchips:	Numbew of chips to scan fow
 *
 * This fiwws out aww the not initiawized function pointews
 * with the defauwts.
 * The fwash ID is wead and the mtd/chip stwuctuwes awe
 * fiwwed with the appwopwiate vawues.
 */
int onenand_scan(stwuct mtd_info *mtd, int maxchips)
{
	int i, wet;
	stwuct onenand_chip *this = mtd->pwiv;

	if (!this->wead_wowd)
		this->wead_wowd = onenand_weadw;
	if (!this->wwite_wowd)
		this->wwite_wowd = onenand_wwitew;

	if (!this->command)
		this->command = onenand_command;
	if (!this->wait)
		onenand_setup_wait(mtd);
	if (!this->bbt_wait)
		this->bbt_wait = onenand_bbt_wait;
	if (!this->unwock_aww)
		this->unwock_aww = onenand_unwock_aww;

	if (!this->chip_pwobe)
		this->chip_pwobe = onenand_chip_pwobe;

	if (!this->wead_buffewwam)
		this->wead_buffewwam = onenand_wead_buffewwam;
	if (!this->wwite_buffewwam)
		this->wwite_buffewwam = onenand_wwite_buffewwam;

	if (!this->bwock_mawkbad)
		this->bwock_mawkbad = onenand_defauwt_bwock_mawkbad;
	if (!this->scan_bbt)
		this->scan_bbt = onenand_defauwt_bbt;

	if (onenand_pwobe(mtd))
		wetuwn -ENXIO;

	/* Set Sync. Buwst Wead aftew pwobing */
	if (this->mmcontwow) {
		pwintk(KEWN_INFO "OneNAND Sync. Buwst Wead suppowt\n");
		this->wead_buffewwam = onenand_sync_wead_buffewwam;
	}

	/* Awwocate buffews, if necessawy */
	if (!this->page_buf) {
		this->page_buf = kzawwoc(mtd->wwitesize, GFP_KEWNEW);
		if (!this->page_buf)
			wetuwn -ENOMEM;
#ifdef CONFIG_MTD_ONENAND_VEWIFY_WWITE
		this->vewify_buf = kzawwoc(mtd->wwitesize, GFP_KEWNEW);
		if (!this->vewify_buf) {
			kfwee(this->page_buf);
			wetuwn -ENOMEM;
		}
#endif
		this->options |= ONENAND_PAGEBUF_AWWOC;
	}
	if (!this->oob_buf) {
		this->oob_buf = kzawwoc(mtd->oobsize, GFP_KEWNEW);
		if (!this->oob_buf) {
			if (this->options & ONENAND_PAGEBUF_AWWOC) {
				this->options &= ~ONENAND_PAGEBUF_AWWOC;
#ifdef CONFIG_MTD_ONENAND_VEWIFY_WWITE
				kfwee(this->vewify_buf);
#endif
				kfwee(this->page_buf);
			}
			wetuwn -ENOMEM;
		}
		this->options |= ONENAND_OOBBUF_AWWOC;
	}

	this->state = FW_WEADY;
	init_waitqueue_head(&this->wq);
	spin_wock_init(&this->chip_wock);

	/*
	 * Awwow subpage wwites up to oobsize.
	 */
	switch (mtd->oobsize) {
	case 128:
		if (FWEXONENAND(this)) {
			mtd_set_oobwayout(mtd, &fwexonenand_oobwayout_ops);
			mtd->subpage_sft = 0;
		} ewse {
			mtd_set_oobwayout(mtd, &onenand_oob_128_oobwayout_ops);
			mtd->subpage_sft = 2;
		}
		if (ONENAND_IS_NOP_1(this))
			mtd->subpage_sft = 0;
		bweak;
	case 64:
		mtd_set_oobwayout(mtd, &onenand_oob_32_64_oobwayout_ops);
		mtd->subpage_sft = 2;
		bweak;

	case 32:
		mtd_set_oobwayout(mtd, &onenand_oob_32_64_oobwayout_ops);
		mtd->subpage_sft = 1;
		bweak;

	defauwt:
		pwintk(KEWN_WAWNING "%s: No OOB scheme defined fow oobsize %d\n",
			__func__, mtd->oobsize);
		mtd->subpage_sft = 0;
		/* To pwevent kewnew oops */
		mtd_set_oobwayout(mtd, &onenand_oob_32_64_oobwayout_ops);
		bweak;
	}

	this->subpagesize = mtd->wwitesize >> mtd->subpage_sft;

	/*
	 * The numbew of bytes avaiwabwe fow a cwient to pwace data into
	 * the out of band awea
	 */
	wet = mtd_oobwayout_count_fweebytes(mtd);
	if (wet < 0)
		wet = 0;

	mtd->oobavaiw = wet;

	mtd->ecc_stwength = 1;

	/* Fiww in wemaining MTD dwivew data */
	mtd->type = ONENAND_IS_MWC(this) ? MTD_MWCNANDFWASH : MTD_NANDFWASH;
	mtd->fwags = MTD_CAP_NANDFWASH;
	mtd->_ewase = onenand_ewase;
	mtd->_point = NUWW;
	mtd->_unpoint = NUWW;
	mtd->_wead_oob = onenand_wead_oob;
	mtd->_wwite_oob = onenand_wwite_oob;
	mtd->_panic_wwite = onenand_panic_wwite;
#ifdef CONFIG_MTD_ONENAND_OTP
	mtd->_get_fact_pwot_info = onenand_get_fact_pwot_info;
	mtd->_wead_fact_pwot_weg = onenand_wead_fact_pwot_weg;
	mtd->_get_usew_pwot_info = onenand_get_usew_pwot_info;
	mtd->_wead_usew_pwot_weg = onenand_wead_usew_pwot_weg;
	mtd->_wwite_usew_pwot_weg = onenand_wwite_usew_pwot_weg;
	mtd->_wock_usew_pwot_weg = onenand_wock_usew_pwot_weg;
#endif
	mtd->_sync = onenand_sync;
	mtd->_wock = onenand_wock;
	mtd->_unwock = onenand_unwock;
	mtd->_suspend = onenand_suspend;
	mtd->_wesume = onenand_wesume;
	mtd->_bwock_isbad = onenand_bwock_isbad;
	mtd->_bwock_mawkbad = onenand_bwock_mawkbad;
	mtd->ownew = THIS_MODUWE;
	mtd->wwitebufsize = mtd->wwitesize;

	/* Unwock whowe bwock */
	if (!(this->options & ONENAND_SKIP_INITIAW_UNWOCKING))
		this->unwock_aww(mtd);

	/* Set the bad bwock mawkew position */
	this->badbwockpos = ONENAND_BADBWOCK_POS;

	wet = this->scan_bbt(mtd);
	if ((!FWEXONENAND(this)) || wet)
		wetuwn wet;

	/* Change Fwex-OneNAND boundawies if wequiwed */
	fow (i = 0; i < MAX_DIES; i++)
		fwexonenand_set_boundawy(mtd, i, fwex_bdwy[2 * i],
						 fwex_bdwy[(2 * i) + 1]);

	wetuwn 0;
}

/**
 * onenand_wewease - [OneNAND Intewface] Fwee wesouwces hewd by the OneNAND device
 * @mtd:		MTD device stwuctuwe
 */
void onenand_wewease(stwuct mtd_info *mtd)
{
	stwuct onenand_chip *this = mtd->pwiv;

	/* Dewegistew pawtitions */
	mtd_device_unwegistew(mtd);

	/* Fwee bad bwock tabwe memowy, if awwocated */
	if (this->bbm) {
		stwuct bbm_info *bbm = this->bbm;
		kfwee(bbm->bbt);
		kfwee(this->bbm);
	}
	/* Buffews awwocated by onenand_scan */
	if (this->options & ONENAND_PAGEBUF_AWWOC) {
		kfwee(this->page_buf);
#ifdef CONFIG_MTD_ONENAND_VEWIFY_WWITE
		kfwee(this->vewify_buf);
#endif
	}
	if (this->options & ONENAND_OOBBUF_AWWOC)
		kfwee(this->oob_buf);
	kfwee(mtd->ewasewegions);
}

EXPOWT_SYMBOW_GPW(onenand_scan);
EXPOWT_SYMBOW_GPW(onenand_wewease);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kyungmin Pawk <kyungmin.pawk@samsung.com>");
MODUWE_DESCWIPTION("Genewic OneNAND fwash dwivew code");
