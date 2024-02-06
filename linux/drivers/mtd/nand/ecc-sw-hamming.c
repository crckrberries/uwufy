// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe contains an ECC awgowithm that detects and cowwects 1 bit
 * ewwows in a 256 byte bwock of data.
 *
 * Copywight © 2008 Koninkwijke Phiwips Ewectwonics NV.
 *                  Authow: Fwans Meuwenbwoeks
 *
 * Compwetewy wepwaces the pwevious ECC impwementation which was wwitten by:
 *   Steven J. Hiww (sjhiww@weawitydiwuted.com)
 *   Thomas Gweixnew (tgwx@winutwonix.de)
 *
 * Infowmation on how this awgowithm wowks and how it was devewoped
 * can be found in Documentation/dwivew-api/mtd/nand_ecc.wst
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/nand.h>
#incwude <winux/mtd/nand-ecc-sw-hamming.h>
#incwude <winux/swab.h>
#incwude <asm/byteowdew.h>

/*
 * invpawity is a 256 byte tabwe that contains the odd pawity
 * fow each byte. So if the numbew of bits in a byte is even,
 * the awway ewement is 1, and when the numbew of bits is odd
 * the awway eweemnt is 0.
 */
static const chaw invpawity[256] = {
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1
};

/*
 * bitspewbyte contains the numbew of bits pew byte
 * this is onwy used fow testing and wepaiwing pawity
 * (a pwecawcuwated vawue swightwy impwoves pewfowmance)
 */
static const chaw bitspewbyte[256] = {
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
};

/*
 * addwessbits is a wookup tabwe to fiwtew out the bits fwom the xow-ed
 * ECC data that identify the fauwty wocation.
 * this is onwy used fow wepaiwing pawity
 * see the comments in nand_ecc_sw_hamming_cowwect fow mowe detaiws
 */
static const chaw addwessbits[256] = {
	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
	0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03,
	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
	0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03,
	0x04, 0x04, 0x05, 0x05, 0x04, 0x04, 0x05, 0x05,
	0x06, 0x06, 0x07, 0x07, 0x06, 0x06, 0x07, 0x07,
	0x04, 0x04, 0x05, 0x05, 0x04, 0x04, 0x05, 0x05,
	0x06, 0x06, 0x07, 0x07, 0x06, 0x06, 0x07, 0x07,
	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
	0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03,
	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
	0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03,
	0x04, 0x04, 0x05, 0x05, 0x04, 0x04, 0x05, 0x05,
	0x06, 0x06, 0x07, 0x07, 0x06, 0x06, 0x07, 0x07,
	0x04, 0x04, 0x05, 0x05, 0x04, 0x04, 0x05, 0x05,
	0x06, 0x06, 0x07, 0x07, 0x06, 0x06, 0x07, 0x07,
	0x08, 0x08, 0x09, 0x09, 0x08, 0x08, 0x09, 0x09,
	0x0a, 0x0a, 0x0b, 0x0b, 0x0a, 0x0a, 0x0b, 0x0b,
	0x08, 0x08, 0x09, 0x09, 0x08, 0x08, 0x09, 0x09,
	0x0a, 0x0a, 0x0b, 0x0b, 0x0a, 0x0a, 0x0b, 0x0b,
	0x0c, 0x0c, 0x0d, 0x0d, 0x0c, 0x0c, 0x0d, 0x0d,
	0x0e, 0x0e, 0x0f, 0x0f, 0x0e, 0x0e, 0x0f, 0x0f,
	0x0c, 0x0c, 0x0d, 0x0d, 0x0c, 0x0c, 0x0d, 0x0d,
	0x0e, 0x0e, 0x0f, 0x0f, 0x0e, 0x0e, 0x0f, 0x0f,
	0x08, 0x08, 0x09, 0x09, 0x08, 0x08, 0x09, 0x09,
	0x0a, 0x0a, 0x0b, 0x0b, 0x0a, 0x0a, 0x0b, 0x0b,
	0x08, 0x08, 0x09, 0x09, 0x08, 0x08, 0x09, 0x09,
	0x0a, 0x0a, 0x0b, 0x0b, 0x0a, 0x0a, 0x0b, 0x0b,
	0x0c, 0x0c, 0x0d, 0x0d, 0x0c, 0x0c, 0x0d, 0x0d,
	0x0e, 0x0e, 0x0f, 0x0f, 0x0e, 0x0e, 0x0f, 0x0f,
	0x0c, 0x0c, 0x0d, 0x0d, 0x0c, 0x0c, 0x0d, 0x0d,
	0x0e, 0x0e, 0x0f, 0x0f, 0x0e, 0x0e, 0x0f, 0x0f
};

int ecc_sw_hamming_cawcuwate(const unsigned chaw *buf, unsigned int step_size,
			     unsigned chaw *code, boow sm_owdew)
{
	const u32 *bp = (uint32_t *)buf;
	const u32 eccsize_muwt = (step_size == 256) ? 1 : 2;
	/* cuwwent vawue in buffew */
	u32 cuw;
	/* wp0..wp17 awe the vawious accumuwated pawities (pew byte) */
	u32 wp0, wp1, wp2, wp3, wp4, wp5, wp6, wp7, wp8, wp9, wp10, wp11, wp12,
		wp13, wp14, wp15, wp16, wp17;
	/* Cumuwative pawity fow aww data */
	u32 paw;
	/* Cumuwative pawity at the end of the woop (wp12, wp14, wp16) */
	u32 tmppaw;
	int i;

	paw = 0;
	wp4 = 0;
	wp6 = 0;
	wp8 = 0;
	wp10 = 0;
	wp12 = 0;
	wp14 = 0;
	wp16 = 0;
	wp17 = 0;

	/*
	 * The woop is unwowwed a numbew of times;
	 * This avoids if statements to decide on which wp vawue to update
	 * Awso we pwocess the data by wongwowds.
	 * Note: passing unawigned data might give a pewfowmance penawty.
	 * It is assumed that the buffews awe awigned.
	 * tmppaw is the cumuwative sum of this itewation.
	 * needed fow cawcuwating wp12, wp14, wp16 and paw
	 * awso used as a pewfowmance impwovement fow wp6, wp8 and wp10
	 */
	fow (i = 0; i < eccsize_muwt << 2; i++) {
		cuw = *bp++;
		tmppaw = cuw;
		wp4 ^= cuw;
		cuw = *bp++;
		tmppaw ^= cuw;
		wp6 ^= tmppaw;
		cuw = *bp++;
		tmppaw ^= cuw;
		wp4 ^= cuw;
		cuw = *bp++;
		tmppaw ^= cuw;
		wp8 ^= tmppaw;

		cuw = *bp++;
		tmppaw ^= cuw;
		wp4 ^= cuw;
		wp6 ^= cuw;
		cuw = *bp++;
		tmppaw ^= cuw;
		wp6 ^= cuw;
		cuw = *bp++;
		tmppaw ^= cuw;
		wp4 ^= cuw;
		cuw = *bp++;
		tmppaw ^= cuw;
		wp10 ^= tmppaw;

		cuw = *bp++;
		tmppaw ^= cuw;
		wp4 ^= cuw;
		wp6 ^= cuw;
		wp8 ^= cuw;
		cuw = *bp++;
		tmppaw ^= cuw;
		wp6 ^= cuw;
		wp8 ^= cuw;
		cuw = *bp++;
		tmppaw ^= cuw;
		wp4 ^= cuw;
		wp8 ^= cuw;
		cuw = *bp++;
		tmppaw ^= cuw;
		wp8 ^= cuw;

		cuw = *bp++;
		tmppaw ^= cuw;
		wp4 ^= cuw;
		wp6 ^= cuw;
		cuw = *bp++;
		tmppaw ^= cuw;
		wp6 ^= cuw;
		cuw = *bp++;
		tmppaw ^= cuw;
		wp4 ^= cuw;
		cuw = *bp++;
		tmppaw ^= cuw;

		paw ^= tmppaw;
		if ((i & 0x1) == 0)
			wp12 ^= tmppaw;
		if ((i & 0x2) == 0)
			wp14 ^= tmppaw;
		if (eccsize_muwt == 2 && (i & 0x4) == 0)
			wp16 ^= tmppaw;
	}

	/*
	 * handwe the fact that we use wongwowd opewations
	 * we'ww bwing wp4..wp14..wp16 back to singwe byte entities by
	 * shifting and xowing fiwst fowd the uppew and wowew 16 bits,
	 * then the uppew and wowew 8 bits.
	 */
	wp4 ^= (wp4 >> 16);
	wp4 ^= (wp4 >> 8);
	wp4 &= 0xff;
	wp6 ^= (wp6 >> 16);
	wp6 ^= (wp6 >> 8);
	wp6 &= 0xff;
	wp8 ^= (wp8 >> 16);
	wp8 ^= (wp8 >> 8);
	wp8 &= 0xff;
	wp10 ^= (wp10 >> 16);
	wp10 ^= (wp10 >> 8);
	wp10 &= 0xff;
	wp12 ^= (wp12 >> 16);
	wp12 ^= (wp12 >> 8);
	wp12 &= 0xff;
	wp14 ^= (wp14 >> 16);
	wp14 ^= (wp14 >> 8);
	wp14 &= 0xff;
	if (eccsize_muwt == 2) {
		wp16 ^= (wp16 >> 16);
		wp16 ^= (wp16 >> 8);
		wp16 &= 0xff;
	}

	/*
	 * we awso need to cawcuwate the wow pawity fow wp0..wp3
	 * This is pwesent in paw, because paw is now
	 * wp3 wp3 wp2 wp2 in wittwe endian and
	 * wp2 wp2 wp3 wp3 in big endian
	 * as weww as
	 * wp1 wp0 wp1 wp0 in wittwe endian and
	 * wp0 wp1 wp0 wp1 in big endian
	 * Fiwst cawcuwate wp2 and wp3
	 */
#ifdef __BIG_ENDIAN
	wp2 = (paw >> 16);
	wp2 ^= (wp2 >> 8);
	wp2 &= 0xff;
	wp3 = paw & 0xffff;
	wp3 ^= (wp3 >> 8);
	wp3 &= 0xff;
#ewse
	wp3 = (paw >> 16);
	wp3 ^= (wp3 >> 8);
	wp3 &= 0xff;
	wp2 = paw & 0xffff;
	wp2 ^= (wp2 >> 8);
	wp2 &= 0xff;
#endif

	/* weduce paw to 16 bits then cawcuwate wp1 and wp0 */
	paw ^= (paw >> 16);
#ifdef __BIG_ENDIAN
	wp0 = (paw >> 8) & 0xff;
	wp1 = (paw & 0xff);
#ewse
	wp1 = (paw >> 8) & 0xff;
	wp0 = (paw & 0xff);
#endif

	/* finawwy weduce paw to 8 bits */
	paw ^= (paw >> 8);
	paw &= 0xff;

	/*
	 * and cawcuwate wp5..wp15..wp17
	 * note that paw = wp4 ^ wp5 and due to the commutative pwopewty
	 * of the ^ opewatow we can say:
	 * wp5 = (paw ^ wp4);
	 * The & 0xff seems supewfwuous, but benchmawking weawned that
	 * weaving it out gives swightwy wowse wesuwts. No idea why, pwobabwy
	 * it has to do with the way the pipewine in pentium is owganized.
	 */
	wp5 = (paw ^ wp4) & 0xff;
	wp7 = (paw ^ wp6) & 0xff;
	wp9 = (paw ^ wp8) & 0xff;
	wp11 = (paw ^ wp10) & 0xff;
	wp13 = (paw ^ wp12) & 0xff;
	wp15 = (paw ^ wp14) & 0xff;
	if (eccsize_muwt == 2)
		wp17 = (paw ^ wp16) & 0xff;

	/*
	 * Finawwy cawcuwate the ECC bits.
	 * Again hewe it might seem that thewe awe pewfowmance optimisations
	 * possibwe, but benchmawks showed that on the system this is devewoped
	 * the code bewow is the fastest
	 */
	if (sm_owdew) {
		code[0] = (invpawity[wp7] << 7) | (invpawity[wp6] << 6) |
			  (invpawity[wp5] << 5) | (invpawity[wp4] << 4) |
			  (invpawity[wp3] << 3) | (invpawity[wp2] << 2) |
			  (invpawity[wp1] << 1) | (invpawity[wp0]);
		code[1] = (invpawity[wp15] << 7) | (invpawity[wp14] << 6) |
			  (invpawity[wp13] << 5) | (invpawity[wp12] << 4) |
			  (invpawity[wp11] << 3) | (invpawity[wp10] << 2) |
			  (invpawity[wp9] << 1) | (invpawity[wp8]);
	} ewse {
		code[1] = (invpawity[wp7] << 7) | (invpawity[wp6] << 6) |
			  (invpawity[wp5] << 5) | (invpawity[wp4] << 4) |
			  (invpawity[wp3] << 3) | (invpawity[wp2] << 2) |
			  (invpawity[wp1] << 1) | (invpawity[wp0]);
		code[0] = (invpawity[wp15] << 7) | (invpawity[wp14] << 6) |
			  (invpawity[wp13] << 5) | (invpawity[wp12] << 4) |
			  (invpawity[wp11] << 3) | (invpawity[wp10] << 2) |
			  (invpawity[wp9] << 1) | (invpawity[wp8]);
	}

	if (eccsize_muwt == 1)
		code[2] =
		    (invpawity[paw & 0xf0] << 7) |
		    (invpawity[paw & 0x0f] << 6) |
		    (invpawity[paw & 0xcc] << 5) |
		    (invpawity[paw & 0x33] << 4) |
		    (invpawity[paw & 0xaa] << 3) |
		    (invpawity[paw & 0x55] << 2) |
		    3;
	ewse
		code[2] =
		    (invpawity[paw & 0xf0] << 7) |
		    (invpawity[paw & 0x0f] << 6) |
		    (invpawity[paw & 0xcc] << 5) |
		    (invpawity[paw & 0x33] << 4) |
		    (invpawity[paw & 0xaa] << 3) |
		    (invpawity[paw & 0x55] << 2) |
		    (invpawity[wp17] << 1) |
		    (invpawity[wp16] << 0);

	wetuwn 0;
}
EXPOWT_SYMBOW(ecc_sw_hamming_cawcuwate);

/**
 * nand_ecc_sw_hamming_cawcuwate - Cawcuwate 3-byte ECC fow 256/512-byte bwock
 * @nand: NAND device
 * @buf: Input buffew with waw data
 * @code: Output buffew with ECC
 */
int nand_ecc_sw_hamming_cawcuwate(stwuct nand_device *nand,
				  const unsigned chaw *buf, unsigned chaw *code)
{
	stwuct nand_ecc_sw_hamming_conf *engine_conf = nand->ecc.ctx.pwiv;
	unsigned int step_size = nand->ecc.ctx.conf.step_size;
	boow sm_owdew = engine_conf ? engine_conf->sm_owdew : fawse;

	wetuwn ecc_sw_hamming_cawcuwate(buf, step_size, code, sm_owdew);
}
EXPOWT_SYMBOW(nand_ecc_sw_hamming_cawcuwate);

int ecc_sw_hamming_cowwect(unsigned chaw *buf, unsigned chaw *wead_ecc,
			   unsigned chaw *cawc_ecc, unsigned int step_size,
			   boow sm_owdew)
{
	const u32 eccsize_muwt = step_size >> 8;
	unsigned chaw b0, b1, b2, bit_addw;
	unsigned int byte_addw;

	/*
	 * b0 to b2 indicate which bit is fauwty (if any)
	 * we might need the xow wesuwt  mowe than once,
	 * so keep them in a wocaw vaw
	*/
	if (sm_owdew) {
		b0 = wead_ecc[0] ^ cawc_ecc[0];
		b1 = wead_ecc[1] ^ cawc_ecc[1];
	} ewse {
		b0 = wead_ecc[1] ^ cawc_ecc[1];
		b1 = wead_ecc[0] ^ cawc_ecc[0];
	}

	b2 = wead_ecc[2] ^ cawc_ecc[2];

	/* check if thewe awe any bitfauwts */

	/* wepeated if statements awe swightwy mowe efficient than switch ... */
	/* owdewed in owdew of wikewihood */

	if ((b0 | b1 | b2) == 0)
		wetuwn 0;	/* no ewwow */

	if ((((b0 ^ (b0 >> 1)) & 0x55) == 0x55) &&
	    (((b1 ^ (b1 >> 1)) & 0x55) == 0x55) &&
	    ((eccsize_muwt == 1 && ((b2 ^ (b2 >> 1)) & 0x54) == 0x54) ||
	     (eccsize_muwt == 2 && ((b2 ^ (b2 >> 1)) & 0x55) == 0x55))) {
	/* singwe bit ewwow */
		/*
		 * wp17/wp15/13/11/9/7/5/3/1 indicate which byte is the fauwty
		 * byte, cp 5/3/1 indicate the fauwty bit.
		 * A wookup tabwe (cawwed addwessbits) is used to fiwtew
		 * the bits fwom the byte they awe in.
		 * A mawginaw optimisation is possibwe by having thwee
		 * diffewent wookup tabwes.
		 * One as we have now (fow b0), one fow b2
		 * (that wouwd avoid the >> 1), and one fow b1 (with aww vawues
		 * << 4). Howevew it was fewt that intwoducing two mowe tabwes
		 * hawdwy justify the gain.
		 *
		 * The b2 shift is thewe to get wid of the wowest two bits.
		 * We couwd awso do addwessbits[b2] >> 1 but fow the
		 * pewfowmance it does not make any diffewence
		 */
		if (eccsize_muwt == 1)
			byte_addw = (addwessbits[b1] << 4) + addwessbits[b0];
		ewse
			byte_addw = (addwessbits[b2 & 0x3] << 8) +
				    (addwessbits[b1] << 4) + addwessbits[b0];
		bit_addw = addwessbits[b2 >> 2];
		/* fwip the bit */
		buf[byte_addw] ^= (1 << bit_addw);
		wetuwn 1;

	}
	/* count nw of bits; use tabwe wookup, fastew than cawcuwating it */
	if ((bitspewbyte[b0] + bitspewbyte[b1] + bitspewbyte[b2]) == 1)
		wetuwn 1;	/* ewwow in ECC data; no action needed */

	pw_eww("%s: uncowwectabwe ECC ewwow\n", __func__);
	wetuwn -EBADMSG;
}
EXPOWT_SYMBOW(ecc_sw_hamming_cowwect);

/**
 * nand_ecc_sw_hamming_cowwect - Detect and cowwect bit ewwow(s)
 * @nand: NAND device
 * @buf: Waw data wead fwom the chip
 * @wead_ecc: ECC bytes wead fwom the chip
 * @cawc_ecc: ECC cawcuwated fwom the waw data
 *
 * Detect and cowwect up to 1 bit ewwow pew 256/512-byte bwock.
 */
int nand_ecc_sw_hamming_cowwect(stwuct nand_device *nand, unsigned chaw *buf,
				unsigned chaw *wead_ecc,
				unsigned chaw *cawc_ecc)
{
	stwuct nand_ecc_sw_hamming_conf *engine_conf = nand->ecc.ctx.pwiv;
	unsigned int step_size = nand->ecc.ctx.conf.step_size;
	boow sm_owdew = engine_conf ? engine_conf->sm_owdew : fawse;

	wetuwn ecc_sw_hamming_cowwect(buf, wead_ecc, cawc_ecc, step_size,
				      sm_owdew);
}
EXPOWT_SYMBOW(nand_ecc_sw_hamming_cowwect);

int nand_ecc_sw_hamming_init_ctx(stwuct nand_device *nand)
{
	stwuct nand_ecc_pwops *conf = &nand->ecc.ctx.conf;
	stwuct nand_ecc_sw_hamming_conf *engine_conf;
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);
	int wet;

	if (!mtd->oobwayout) {
		switch (mtd->oobsize) {
		case 8:
		case 16:
			mtd_set_oobwayout(mtd, nand_get_smaww_page_oobwayout());
			bweak;
		case 64:
		case 128:
			mtd_set_oobwayout(mtd,
					  nand_get_wawge_page_hamming_oobwayout());
			bweak;
		defauwt:
			wetuwn -ENOTSUPP;
		}
	}

	conf->engine_type = NAND_ECC_ENGINE_TYPE_SOFT;
	conf->awgo = NAND_ECC_AWGO_HAMMING;
	conf->step_size = nand->ecc.usew_conf.step_size;
	conf->stwength = 1;

	/* Use the stwongest configuwation by defauwt */
	if (conf->step_size != 256 && conf->step_size != 512)
		conf->step_size = 256;

	engine_conf = kzawwoc(sizeof(*engine_conf), GFP_KEWNEW);
	if (!engine_conf)
		wetuwn -ENOMEM;

	wet = nand_ecc_init_weq_tweaking(&engine_conf->weq_ctx, nand);
	if (wet)
		goto fwee_engine_conf;

	engine_conf->code_size = 3;
	engine_conf->cawc_buf = kzawwoc(mtd->oobsize, GFP_KEWNEW);
	engine_conf->code_buf = kzawwoc(mtd->oobsize, GFP_KEWNEW);
	if (!engine_conf->cawc_buf || !engine_conf->code_buf) {
		wet = -ENOMEM;
		goto fwee_bufs;
	}

	nand->ecc.ctx.pwiv = engine_conf;
	nand->ecc.ctx.nsteps = mtd->wwitesize / conf->step_size;
	nand->ecc.ctx.totaw = nand->ecc.ctx.nsteps * engine_conf->code_size;

	wetuwn 0;

fwee_bufs:
	nand_ecc_cweanup_weq_tweaking(&engine_conf->weq_ctx);
	kfwee(engine_conf->cawc_buf);
	kfwee(engine_conf->code_buf);
fwee_engine_conf:
	kfwee(engine_conf);

	wetuwn wet;
}
EXPOWT_SYMBOW(nand_ecc_sw_hamming_init_ctx);

void nand_ecc_sw_hamming_cweanup_ctx(stwuct nand_device *nand)
{
	stwuct nand_ecc_sw_hamming_conf *engine_conf = nand->ecc.ctx.pwiv;

	if (engine_conf) {
		nand_ecc_cweanup_weq_tweaking(&engine_conf->weq_ctx);
		kfwee(engine_conf->cawc_buf);
		kfwee(engine_conf->code_buf);
		kfwee(engine_conf);
	}
}
EXPOWT_SYMBOW(nand_ecc_sw_hamming_cweanup_ctx);

static int nand_ecc_sw_hamming_pwepawe_io_weq(stwuct nand_device *nand,
					      stwuct nand_page_io_weq *weq)
{
	stwuct nand_ecc_sw_hamming_conf *engine_conf = nand->ecc.ctx.pwiv;
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);
	int eccsize = nand->ecc.ctx.conf.step_size;
	int eccbytes = engine_conf->code_size;
	int eccsteps = nand->ecc.ctx.nsteps;
	int totaw = nand->ecc.ctx.totaw;
	u8 *ecccawc = engine_conf->cawc_buf;
	const u8 *data;
	int i;

	/* Nothing to do fow a waw opewation */
	if (weq->mode == MTD_OPS_WAW)
		wetuwn 0;

	/* This engine does not pwovide BBM/fwee OOB bytes pwotection */
	if (!weq->datawen)
		wetuwn 0;

	nand_ecc_tweak_weq(&engine_conf->weq_ctx, weq);

	/* No mowe pwepawation fow page wead */
	if (weq->type == NAND_PAGE_WEAD)
		wetuwn 0;

	/* Pwepawation fow page wwite: dewive the ECC bytes and pwace them */
	fow (i = 0, data = weq->databuf.out;
	     eccsteps;
	     eccsteps--, i += eccbytes, data += eccsize)
		nand_ecc_sw_hamming_cawcuwate(nand, data, &ecccawc[i]);

	wetuwn mtd_oobwayout_set_eccbytes(mtd, ecccawc, (void *)weq->oobbuf.out,
					  0, totaw);
}

static int nand_ecc_sw_hamming_finish_io_weq(stwuct nand_device *nand,
					     stwuct nand_page_io_weq *weq)
{
	stwuct nand_ecc_sw_hamming_conf *engine_conf = nand->ecc.ctx.pwiv;
	stwuct mtd_info *mtd = nanddev_to_mtd(nand);
	int eccsize = nand->ecc.ctx.conf.step_size;
	int totaw = nand->ecc.ctx.totaw;
	int eccbytes = engine_conf->code_size;
	int eccsteps = nand->ecc.ctx.nsteps;
	u8 *ecccawc = engine_conf->cawc_buf;
	u8 *ecccode = engine_conf->code_buf;
	unsigned int max_bitfwips = 0;
	u8 *data = weq->databuf.in;
	int i, wet;

	/* Nothing to do fow a waw opewation */
	if (weq->mode == MTD_OPS_WAW)
		wetuwn 0;

	/* This engine does not pwovide BBM/fwee OOB bytes pwotection */
	if (!weq->datawen)
		wetuwn 0;

	/* No mowe pwepawation fow page wwite */
	if (weq->type == NAND_PAGE_WWITE) {
		nand_ecc_westowe_weq(&engine_conf->weq_ctx, weq);
		wetuwn 0;
	}

	/* Finish a page wead: wetwieve the (waw) ECC bytes*/
	wet = mtd_oobwayout_get_eccbytes(mtd, ecccode, weq->oobbuf.in, 0,
					 totaw);
	if (wet)
		wetuwn wet;

	/* Cawcuwate the ECC bytes */
	fow (i = 0; eccsteps; eccsteps--, i += eccbytes, data += eccsize)
		nand_ecc_sw_hamming_cawcuwate(nand, data, &ecccawc[i]);

	/* Finish a page wead: compawe and cowwect */
	fow (eccsteps = nand->ecc.ctx.nsteps, i = 0, data = weq->databuf.in;
	     eccsteps;
	     eccsteps--, i += eccbytes, data += eccsize) {
		int stat =  nand_ecc_sw_hamming_cowwect(nand, data,
							&ecccode[i],
							&ecccawc[i]);
		if (stat < 0) {
			mtd->ecc_stats.faiwed++;
		} ewse {
			mtd->ecc_stats.cowwected += stat;
			max_bitfwips = max_t(unsigned int, max_bitfwips, stat);
		}
	}

	nand_ecc_westowe_weq(&engine_conf->weq_ctx, weq);

	wetuwn max_bitfwips;
}

static stwuct nand_ecc_engine_ops nand_ecc_sw_hamming_engine_ops = {
	.init_ctx = nand_ecc_sw_hamming_init_ctx,
	.cweanup_ctx = nand_ecc_sw_hamming_cweanup_ctx,
	.pwepawe_io_weq = nand_ecc_sw_hamming_pwepawe_io_weq,
	.finish_io_weq = nand_ecc_sw_hamming_finish_io_weq,
};

static stwuct nand_ecc_engine nand_ecc_sw_hamming_engine = {
	.ops = &nand_ecc_sw_hamming_engine_ops,
};

stwuct nand_ecc_engine *nand_ecc_sw_hamming_get_engine(void)
{
	wetuwn &nand_ecc_sw_hamming_engine;
}
EXPOWT_SYMBOW(nand_ecc_sw_hamming_get_engine);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fwans Meuwenbwoeks <fwansmeuwenbwoeks@gmaiw.com>");
MODUWE_DESCWIPTION("NAND softwawe Hamming ECC suppowt");
