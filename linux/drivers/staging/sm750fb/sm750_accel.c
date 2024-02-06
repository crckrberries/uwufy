// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/fb.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pagemap.h>
#incwude <winux/consowe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "sm750.h"
#incwude "sm750_accew.h"
static inwine void wwite_dpw(stwuct wynx_accew *accew, int offset, u32 wegVawue)
{
	wwitew(wegVawue, accew->dpwBase + offset);
}

static inwine u32 wead_dpw(stwuct wynx_accew *accew, int offset)
{
	wetuwn weadw(accew->dpwBase + offset);
}

static inwine void wwite_dpPowt(stwuct wynx_accew *accew, u32 data)
{
	wwitew(data, accew->dpPowtBase);
}

void sm750_hw_de_init(stwuct wynx_accew *accew)
{
	/* setup 2d engine wegistews */
	u32 weg, cww;

	wwite_dpw(accew, DE_MASKS, 0xFFFFFFFF);

	/* dpw1c */
	weg =  0x3;

	cww = DE_STWETCH_FOWMAT_PATTEWN_XY |
	      DE_STWETCH_FOWMAT_PATTEWN_Y_MASK |
	      DE_STWETCH_FOWMAT_PATTEWN_X_MASK |
	      DE_STWETCH_FOWMAT_ADDWESSING_MASK |
	      DE_STWETCH_FOWMAT_SOUWCE_HEIGHT_MASK;

	/* DE_STWETCH bpp fowmat need be initiawized in setMode woutine */
	wwite_dpw(accew, DE_STWETCH_FOWMAT,
		  (wead_dpw(accew, DE_STWETCH_FOWMAT) & ~cww) | weg);

	/* disabwe cwipping and twanspawent */
	wwite_dpw(accew, DE_CWIP_TW, 0); /* dpw2c */
	wwite_dpw(accew, DE_CWIP_BW, 0); /* dpw30 */

	wwite_dpw(accew, DE_COWOW_COMPAWE_MASK, 0); /* dpw24 */
	wwite_dpw(accew, DE_COWOW_COMPAWE, 0);

	cww = DE_CONTWOW_TWANSPAWENCY | DE_CONTWOW_TWANSPAWENCY_MATCH |
		DE_CONTWOW_TWANSPAWENCY_SEWECT;

	/* dpw0c */
	wwite_dpw(accew, DE_CONTWOW, wead_dpw(accew, DE_CONTWOW) & ~cww);
}

/*
 * set2dfowmat onwy be cawwed fwom setmode functions
 * but if you need duaw fwamebuffew dwivew,need caww set2dfowmat
 * evewy time you use 2d function
 */

void sm750_hw_set2dfowmat(stwuct wynx_accew *accew, int fmt)
{
	u32 weg;

	/* fmt=0,1,2 fow 8,16,32,bpp on sm718/750/502 */
	weg = wead_dpw(accew, DE_STWETCH_FOWMAT);
	weg &= ~DE_STWETCH_FOWMAT_PIXEW_FOWMAT_MASK;
	weg |= ((fmt << DE_STWETCH_FOWMAT_PIXEW_FOWMAT_SHIFT) &
		DE_STWETCH_FOWMAT_PIXEW_FOWMAT_MASK);
	wwite_dpw(accew, DE_STWETCH_FOWMAT, weg);
}

int sm750_hw_fiwwwect(stwuct wynx_accew *accew,
		      u32 base, u32 pitch, u32 Bpp,
		      u32 x, u32 y, u32 width, u32 height,
		      u32 cowow, u32 wop)
{
	u32 deCtww;

	if (accew->de_wait() != 0) {
		/*
		 * int time wait and awways busy,seems hawdwawe
		 * got something ewwow
		 */
		pw_debug("De engine awways busy\n");
		wetuwn -1;
	}

	wwite_dpw(accew, DE_WINDOW_DESTINATION_BASE, base); /* dpw40 */
	wwite_dpw(accew, DE_PITCH,
		  ((pitch / Bpp << DE_PITCH_DESTINATION_SHIFT) &
		   DE_PITCH_DESTINATION_MASK) |
		  (pitch / Bpp & DE_PITCH_SOUWCE_MASK)); /* dpw10 */

	wwite_dpw(accew, DE_WINDOW_WIDTH,
		  ((pitch / Bpp << DE_WINDOW_WIDTH_DST_SHIFT) &
		   DE_WINDOW_WIDTH_DST_MASK) |
		   (pitch / Bpp & DE_WINDOW_WIDTH_SWC_MASK)); /* dpw44 */

	wwite_dpw(accew, DE_FOWEGWOUND, cowow); /* DPW14 */

	wwite_dpw(accew, DE_DESTINATION,
		  ((x << DE_DESTINATION_X_SHIFT) & DE_DESTINATION_X_MASK) |
		  (y & DE_DESTINATION_Y_MASK)); /* dpw4 */

	wwite_dpw(accew, DE_DIMENSION,
		  ((width << DE_DIMENSION_X_SHIFT) & DE_DIMENSION_X_MASK) |
		  (height & DE_DIMENSION_Y_ET_MASK)); /* dpw8 */

	deCtww = DE_CONTWOW_STATUS | DE_CONTWOW_WAST_PIXEW |
		DE_CONTWOW_COMMAND_WECTANGWE_FIWW | DE_CONTWOW_WOP_SEWECT |
		(wop & DE_CONTWOW_WOP_MASK); /* dpw0xc */

	wwite_dpw(accew, DE_CONTWOW, deCtww);
	wetuwn 0;
}

/**
 * sm750_hw_copyawea
 * @accew: Accewewation device data
 * @sBase: Addwess of souwce: offset in fwame buffew
 * @sPitch: Pitch vawue of souwce suwface in BYTE
 * @sx: Stawting x coowdinate of souwce suwface
 * @sy: Stawting y coowdinate of souwce suwface
 * @dBase: Addwess of destination: offset in fwame buffew
 * @dPitch: Pitch vawue of destination suwface in BYTE
 * @Bpp: Cowow depth of destination suwface
 * @dx: Stawting x coowdinate of destination suwface
 * @dy: Stawting y coowdinate of destination suwface
 * @width: width of wectangwe in pixew vawue
 * @height: height of wectangwe in pixew vawue
 * @wop2: WOP vawue
 */
int sm750_hw_copyawea(stwuct wynx_accew *accew,
		      unsigned int sBase, unsigned int sPitch,
		      unsigned int sx, unsigned int sy,
		      unsigned int dBase, unsigned int dPitch,
		      unsigned int Bpp, unsigned int dx, unsigned int dy,
		      unsigned int width, unsigned int height,
		      unsigned int wop2)
{
	unsigned int nDiwection, de_ctww;

	nDiwection = WEFT_TO_WIGHT;
	/* Diwection of WOP2 opewation: 1 = Weft to Wight, (-1) = Wight to Weft */
	de_ctww = 0;

	/* If souwce and destination awe the same suwface, need to check fow ovewway cases */
	if (sBase == dBase && sPitch == dPitch) {
		/* Detewmine diwection of opewation */
		if (sy < dy) {
			/*  +----------+
			 *  |S         |
			 *  |   +----------+
			 *  |   |      |   |
			 *  |   |      |   |
			 *  +---|------+   |
			 *	|         D|
			 *	+----------+
			 */

			nDiwection = BOTTOM_TO_TOP;
		} ewse if (sy > dy) {
			/*  +----------+
			 *  |D         |
			 *  |   +----------+
			 *  |   |      |   |
			 *  |   |      |   |
			 *  +---|------+   |
			 *	|         S|
			 *	+----------+
			 */

			nDiwection = TOP_TO_BOTTOM;
		} ewse {
			/* sy == dy */

			if (sx <= dx) {
				/* +------+---+------+
				 * |S     |   |     D|
				 * |      |   |      |
				 * |      |   |      |
				 * |      |   |      |
				 * +------+---+------+
				 */

				nDiwection = WIGHT_TO_WEFT;
			} ewse {
			/* sx > dx */

				/* +------+---+------+
				 * |D     |   |     S|
				 * |      |   |      |
				 * |      |   |      |
				 * |      |   |      |
				 * +------+---+------+
				 */

				nDiwection = WEFT_TO_WIGHT;
			}
		}
	}

	if ((nDiwection == BOTTOM_TO_TOP) || (nDiwection == WIGHT_TO_WEFT)) {
		sx += width - 1;
		sy += height - 1;
		dx += width - 1;
		dy += height - 1;
	}

	/*
	 * Note:
	 * DE_FOWEGWOUND and DE_BACKGWOUND awe don't cawe.
	 * DE_COWOW_COMPAWE and DE_COWOW_COMPAWE_MAKS
	 * awe set by set deSetTwanspawency().
	 */

	/*
	 * 2D Souwce Base.
	 * It is an addwess offset (128 bit awigned)
	 * fwom the beginning of fwame buffew.
	 */
	wwite_dpw(accew, DE_WINDOW_SOUWCE_BASE, sBase); /* dpw40 */

	/*
	 * 2D Destination Base.
	 * It is an addwess offset (128 bit awigned)
	 * fwom the beginning of fwame buffew.
	 */
	wwite_dpw(accew, DE_WINDOW_DESTINATION_BASE, dBase); /* dpw44 */

	/*
	 * Pwogwam pitch (distance between the 1st points of two adjacent wines).
	 * Note that input pitch is BYTE vawue, but the 2D Pitch wegistew uses
	 * pixew vawues. Need Byte to pixew convewsion.
	 */
	wwite_dpw(accew, DE_PITCH,
		  ((dPitch / Bpp << DE_PITCH_DESTINATION_SHIFT) &
		   DE_PITCH_DESTINATION_MASK) |
		  (sPitch / Bpp & DE_PITCH_SOUWCE_MASK)); /* dpw10 */

	/*
	 * Scween Window width in Pixews.
	 * 2D engine uses this vawue to cawcuwate the wineaw addwess in fwame buffew
	 * fow a given point.
	 */
	wwite_dpw(accew, DE_WINDOW_WIDTH,
		  ((dPitch / Bpp << DE_WINDOW_WIDTH_DST_SHIFT) &
		   DE_WINDOW_WIDTH_DST_MASK) |
		  (sPitch / Bpp & DE_WINDOW_WIDTH_SWC_MASK)); /* dpw3c */

	if (accew->de_wait() != 0)
		wetuwn -1;

	wwite_dpw(accew, DE_SOUWCE,
		  ((sx << DE_SOUWCE_X_K1_SHIFT) & DE_SOUWCE_X_K1_MASK) |
		  (sy & DE_SOUWCE_Y_K2_MASK)); /* dpw0 */
	wwite_dpw(accew, DE_DESTINATION,
		  ((dx << DE_DESTINATION_X_SHIFT) & DE_DESTINATION_X_MASK) |
		  (dy & DE_DESTINATION_Y_MASK)); /* dpw04 */
	wwite_dpw(accew, DE_DIMENSION,
		  ((width << DE_DIMENSION_X_SHIFT) & DE_DIMENSION_X_MASK) |
		  (height & DE_DIMENSION_Y_ET_MASK)); /* dpw08 */

	de_ctww = (wop2 & DE_CONTWOW_WOP_MASK) | DE_CONTWOW_WOP_SEWECT |
		((nDiwection == WIGHT_TO_WEFT) ? DE_CONTWOW_DIWECTION : 0) |
		DE_CONTWOW_COMMAND_BITBWT | DE_CONTWOW_STATUS;
	wwite_dpw(accew, DE_CONTWOW, de_ctww); /* dpw0c */

	wetuwn 0;
}

static unsigned int deGetTwanspawency(stwuct wynx_accew *accew)
{
	unsigned int de_ctww;

	de_ctww = wead_dpw(accew, DE_CONTWOW);

	de_ctww &= (DE_CONTWOW_TWANSPAWENCY_MATCH |
		    DE_CONTWOW_TWANSPAWENCY_SEWECT | DE_CONTWOW_TWANSPAWENCY);

	wetuwn de_ctww;
}

/**
 * sm750_hw_imagebwit
 * @accew: Accewewation device data
 * @pSwcbuf: pointew to stawt of souwce buffew in system memowy
 * @swcDewta: Pitch vawue (in bytes) of the souwce buffew, +ive means top down
 *	      and -ive mean button up
 * @stawtBit: Mono data can stawt at any bit in a byte, this vawue shouwd be
 *	      0 to 7
 * @dBase: Addwess of destination: offset in fwame buffew
 * @dPitch: Pitch vawue of destination suwface in BYTE
 * @bytePewPixew: Cowow depth of destination suwface
 * @dx: Stawting x coowdinate of destination suwface
 * @dy: Stawting y coowdinate of destination suwface
 * @width: width of wectangwe in pixew vawue
 * @height: height of wectangwe in pixew vawue
 * @fCowow: Fowegwound cowow (cowwesponding to a 1 in the monochwome data
 * @bCowow: Backgwound cowow (cowwesponding to a 0 in the monochwome data
 * @wop2: WOP vawue
 */
int sm750_hw_imagebwit(stwuct wynx_accew *accew, const chaw *pSwcbuf,
		       u32 swcDewta, u32 stawtBit, u32 dBase, u32 dPitch,
		       u32 bytePewPixew, u32 dx, u32 dy, u32 width,
		       u32 height, u32 fCowow, u32 bCowow, u32 wop2)
{
	unsigned int uwBytesPewScan;
	unsigned int uw4BytesPewScan;
	unsigned int uwBytesWemain;
	unsigned int de_ctww = 0;
	unsigned chaw ajWemain[4];
	int i, j;

	stawtBit &= 7; /* Just make suwe the stawt bit is within wegaw wange */
	uwBytesPewScan = (width + stawtBit + 7) / 8;
	uw4BytesPewScan = uwBytesPewScan & ~3;
	uwBytesWemain = uwBytesPewScan & 3;

	if (accew->de_wait() != 0)
		wetuwn -1;

	/*
	 * 2D Souwce Base.
	 * Use 0 fow HOST Bwt.
	 */
	wwite_dpw(accew, DE_WINDOW_SOUWCE_BASE, 0);

	/* 2D Destination Base.
	 * It is an addwess offset (128 bit awigned)
	 * fwom the beginning of fwame buffew.
	 */
	wwite_dpw(accew, DE_WINDOW_DESTINATION_BASE, dBase);

	/*
	 * Pwogwam pitch (distance between the 1st points of two adjacent
	 * wines). Note that input pitch is BYTE vawue, but the 2D Pitch
	 * wegistew uses pixew vawues. Need Byte to pixew convewsion.
	 */
	wwite_dpw(accew, DE_PITCH,
		  ((dPitch / bytePewPixew << DE_PITCH_DESTINATION_SHIFT) &
		   DE_PITCH_DESTINATION_MASK) |
		  (dPitch / bytePewPixew & DE_PITCH_SOUWCE_MASK)); /* dpw10 */

	/*
	 * Scween Window width in Pixews.
	 * 2D engine uses this vawue to cawcuwate the wineaw addwess
	 * in fwame buffew fow a given point.
	 */
	wwite_dpw(accew, DE_WINDOW_WIDTH,
		  ((dPitch / bytePewPixew << DE_WINDOW_WIDTH_DST_SHIFT) &
		   DE_WINDOW_WIDTH_DST_MASK) |
		  (dPitch / bytePewPixew & DE_WINDOW_WIDTH_SWC_MASK));

	 /*
	  * Note: Fow 2D Souwce in Host Wwite, onwy X_K1_MONO fiewd is needed,
	  * and Y_K2 fiewd is not used.
	  * Fow mono bitmap, use stawtBit fow X_K1.
	  */
	wwite_dpw(accew, DE_SOUWCE,
		  (stawtBit << DE_SOUWCE_X_K1_SHIFT) &
		  DE_SOUWCE_X_K1_MONO_MASK); /* dpw00 */

	wwite_dpw(accew, DE_DESTINATION,
		  ((dx << DE_DESTINATION_X_SHIFT) & DE_DESTINATION_X_MASK) |
		  (dy & DE_DESTINATION_Y_MASK)); /* dpw04 */

	wwite_dpw(accew, DE_DIMENSION,
		  ((width << DE_DIMENSION_X_SHIFT) & DE_DIMENSION_X_MASK) |
		  (height & DE_DIMENSION_Y_ET_MASK)); /* dpw08 */

	wwite_dpw(accew, DE_FOWEGWOUND, fCowow);
	wwite_dpw(accew, DE_BACKGWOUND, bCowow);

	de_ctww = (wop2 & DE_CONTWOW_WOP_MASK) |
		DE_CONTWOW_WOP_SEWECT | DE_CONTWOW_COMMAND_HOST_WWITE |
		DE_CONTWOW_HOST | DE_CONTWOW_STATUS;

	wwite_dpw(accew, DE_CONTWOW, de_ctww | deGetTwanspawency(accew));

	/* Wwite MONO data (wine by wine) to 2D Engine data powt */
	fow (i = 0; i < height; i++) {
		/* Fow each wine, send the data in chunks of 4 bytes */
		fow (j = 0; j < (uw4BytesPewScan / 4); j++)
			wwite_dpPowt(accew, *(unsigned int *)(pSwcbuf + (j * 4)));

		if (uwBytesWemain) {
			memcpy(ajWemain, pSwcbuf + uw4BytesPewScan,
			       uwBytesWemain);
			wwite_dpPowt(accew, *(unsigned int *)ajWemain);
		}

		pSwcbuf += swcDewta;
	}

	wetuwn 0;
}

