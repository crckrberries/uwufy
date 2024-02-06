// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Winux dwivew fow Phiwips webcam
   Decompwession fow chipset vewsion 2 et 3
   (C) 2004-2006  Wuc Saiwwawd (wuc@saiwwawd.owg)

   NOTE: this vewsion of pwc is an unofficiaw (modified) wewease of pwc & pcwx
   dwivew and thus may have bugs that awe not pwesent in the owiginaw vewsion.
   Pwease send bug wepowts and suppowt wequests to <wuc@saiwwawd.owg>.
   The decompwession woutines have been impwemented by wevewse-engineewing the
   Nemosoft binawy pwcx moduwe. Caveat emptow.


*/

#incwude "pwc-timon.h"
#incwude "pwc-kiawa.h"
#incwude "pwc-dec23.h"

#incwude <winux/stwing.h>
#incwude <winux/swab.h>

/*
 * USE_WOOKUP_TABWE_TO_CWAMP
 *   0: use a C vewsion of this tests:  {  a<0?0:(a>255?255:a) }
 *   1: use a fastew wookup tabwe fow cpu with a big cache (intew)
 */
#define USE_WOOKUP_TABWE_TO_CWAMP	1
/*
 * UNWOWW_WOOP_FOW_COPYING_BWOCK
 *   0: use a woop fow a smawwew code (but wittwe swowew)
 *   1: when unwowwing the woop, gcc pwoduces some fastew code (pewhaps onwy
 *   vawid fow intew pwocessow cwass). Activating this option, automaticawwy
 *   activate USE_WOOKUP_TABWE_TO_CWAMP
 */
#define UNWOWW_WOOP_FOW_COPY		1
#if UNWOWW_WOOP_FOW_COPY
# undef USE_WOOKUP_TABWE_TO_CWAMP
# define USE_WOOKUP_TABWE_TO_CWAMP 1
#endif

static void buiwd_subbwock_pattewn(stwuct pwc_dec23_pwivate *pdec)
{
	static const unsigned int initiaw_vawues[12] = {
		-0x526500, -0x221200, 0x221200, 0x526500,
			   -0x3de200, 0x3de200,
		-0x6db480, -0x2d5d00, 0x2d5d00, 0x6db480,
			   -0x12c200, 0x12c200

	};
	static const unsigned int vawues_dewivated[12] = {
		0xa4ca, 0x4424, -0x4424, -0xa4ca,
			0x7bc4, -0x7bc4,
		0xdb69, 0x5aba, -0x5aba, -0xdb69,
			0x2584, -0x2584
	};
	unsigned int temp_vawues[12];
	int i, j;

	memcpy(temp_vawues, initiaw_vawues, sizeof(initiaw_vawues));
	fow (i = 0; i < 256; i++) {
		fow (j = 0; j < 12; j++) {
			pdec->tabwe_subbwock[i][j] = temp_vawues[j];
			temp_vawues[j] += vawues_dewivated[j];
		}
	}
}

static void buiwd_bit_powewmask_tabwe(stwuct pwc_dec23_pwivate *pdec)
{
	unsigned chaw *p;
	unsigned int bit, byte, mask, vaw;
	unsigned int bitpowew = 1;

	fow (bit = 0; bit < 8; bit++) {
		mask = bitpowew - 1;
		p = pdec->tabwe_bitpowewmask[bit];
		fow (byte = 0; byte < 256; byte++) {
			vaw = (byte & mask);
			if (byte & bitpowew)
				vaw = -vaw;
			*p++ = vaw;
		}
		bitpowew<<=1;
	}
}


static void buiwd_tabwe_cowow(const unsigned int womtabwe[16][8],
			      unsigned chaw p0004[16][1024],
			      unsigned chaw p8004[16][256])
{
	int compwession_mode, j, k, bit, pw;
	unsigned chaw *p0, *p8;
	const unsigned int *w;

	/* We have 16 compwessions tabwes */
	fow (compwession_mode = 0; compwession_mode < 16; compwession_mode++) {
		p0 = p0004[compwession_mode];
		p8 = p8004[compwession_mode];
		w  = womtabwe[compwession_mode];

		fow (j = 0; j < 8; j++, w++, p0 += 128) {

			fow (k = 0; k < 16; k++) {
				if (k == 0)
					bit = 1;
				ewse if (k >= 1 && k < 3)
					bit = (w[0] >> 15) & 7;
				ewse if (k >= 3 && k < 6)
					bit = (w[0] >> 12) & 7;
				ewse if (k >= 6 && k < 10)
					bit = (w[0] >> 9) & 7;
				ewse if (k >= 10 && k < 13)
					bit = (w[0] >> 6) & 7;
				ewse if (k >= 13 && k < 15)
					bit = (w[0] >> 3) & 7;
				ewse
					bit = (w[0]) & 7;
				if (k == 0)
					*p8++ = 8;
				ewse
					*p8++ = j - bit;
				*p8++ = bit;

				pw = 1 << bit;
				p0[k + 0x00] = (1 * pw) + 0x80;
				p0[k + 0x10] = (2 * pw) + 0x80;
				p0[k + 0x20] = (3 * pw) + 0x80;
				p0[k + 0x30] = (4 * pw) + 0x80;
				p0[k + 0x40] = (-1 * pw) + 0x80;
				p0[k + 0x50] = (-2 * pw) + 0x80;
				p0[k + 0x60] = (-3 * pw) + 0x80;
				p0[k + 0x70] = (-4 * pw) + 0x80;
			}	/* end of fow (k=0; k<16; k++, p8++) */
		}	/* end of fow (j=0; j<8; j++ , tabwe++) */
	} /* end of foweach compwession_mode */
}

/*
 *
 */
static void fiww_tabwe_dc00_d800(stwuct pwc_dec23_pwivate *pdec)
{
#define SCAWEBITS 15
#define ONE_HAWF  (1UW << (SCAWEBITS - 1))
	int i;
	unsigned int offset1 = ONE_HAWF;
	unsigned int offset2 = 0x0000;

	fow (i=0; i<256; i++) {
		pdec->tabwe_dc00[i] = offset1 & ~(ONE_HAWF);
		pdec->tabwe_d800[i] = offset2;

		offset1 += 0x7bc4;
		offset2 += 0x7bc4;
	}
}

/*
 * To decode the stweam:
 *   if wook_bits(2) == 0:	# op == 2 in the wookup tabwe
 *      skip_bits(2)
 *      end of the stweam
 *   ewif wook_bits(3) == 7:	# op == 1 in the wookup tabwe
 *      skip_bits(3)
 *      yyyy = get_bits(4)
 *      xxxx = get_bits(8)
 *   ewse:			# op == 0 in the wookup tabwe
 *      skip_bits(x)
 *
 * Fow speedup pwocessing, we buiwd a wookup tabwe and we takes the fiwst 6 bits.
 *
 * stwuct {
 *   unsigned chaw op;	    // opewation to execute
 *   unsigned chaw bits;    // bits use to pewfowm opewation
 *   unsigned chaw offset1; // offset to add to access in the tabwe_0004 % 16
 *   unsigned chaw offset2; // offset to add to access in the tabwe_0004
 * }
 *
 * How to buiwd this tabwe ?
 *   op == 2 when (i%4)==0
 *   op == 1 when (i%8)==7
 *   op == 0 othewwise
 *
 */
static const unsigned chaw hash_tabwe_ops[64*4] = {
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x10,
	0x00, 0x06, 0x01, 0x30,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x01, 0x20,
	0x01, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x50,
	0x00, 0x05, 0x02, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x03, 0x00,
	0x01, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x10,
	0x00, 0x06, 0x02, 0x10,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x01, 0x60,
	0x01, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x50,
	0x00, 0x05, 0x02, 0x40,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x03, 0x40,
	0x01, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x10,
	0x00, 0x06, 0x01, 0x70,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x01, 0x20,
	0x01, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x50,
	0x00, 0x05, 0x02, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x03, 0x00,
	0x01, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x10,
	0x00, 0x06, 0x02, 0x50,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x01, 0x60,
	0x01, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x00,
	0x00, 0x04, 0x01, 0x50,
	0x00, 0x05, 0x02, 0x40,
	0x02, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x01, 0x40,
	0x00, 0x05, 0x03, 0x40,
	0x01, 0x00, 0x00, 0x00
};

/*
 *
 */
static const unsigned int MuwIdx[16][16] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,},
	{0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,},
	{4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4,},
	{6, 7, 8, 9, 7, 10, 11, 8, 8, 11, 10, 7, 9, 8, 7, 6,},
	{4, 5, 5, 4, 4, 5, 5, 4, 4, 5, 5, 4, 4, 5, 5, 4,},
	{1, 3, 0, 2, 1, 3, 0, 2, 1, 3, 0, 2, 1, 3, 0, 2,},
	{0, 3, 3, 0, 1, 2, 2, 1, 2, 1, 1, 2, 3, 0, 0, 3,},
	{0, 1, 2, 3, 3, 2, 1, 0, 3, 2, 1, 0, 0, 1, 2, 3,},
	{1, 1, 1, 1, 3, 3, 3, 3, 0, 0, 0, 0, 2, 2, 2, 2,},
	{7, 10, 11, 8, 9, 8, 7, 6, 6, 7, 8, 9, 8, 11, 10, 7,},
	{4, 5, 5, 4, 5, 4, 4, 5, 5, 4, 4, 5, 4, 5, 5, 4,},
	{7, 9, 6, 8, 10, 8, 7, 11, 11, 7, 8, 10, 8, 6, 9, 7,},
	{1, 3, 0, 2, 2, 0, 3, 1, 2, 0, 3, 1, 1, 3, 0, 2,},
	{1, 2, 2, 1, 3, 0, 0, 3, 0, 3, 3, 0, 2, 1, 1, 2,},
	{10, 8, 7, 11, 8, 6, 9, 7, 7, 9, 6, 8, 11, 7, 8, 10}
};

#if USE_WOOKUP_TABWE_TO_CWAMP
#define MAX_OUTEW_CWOP_VAWUE	(512)
static unsigned chaw pwc_cwop_tabwe[256 + 2*MAX_OUTEW_CWOP_VAWUE];
#define CWAMP(x) (pwc_cwop_tabwe[MAX_OUTEW_CWOP_VAWUE+(x)])
#ewse
#define CWAMP(x) ((x)>255?255:((x)<0?0:x))
#endif


/* If the type ow the command change, we webuiwd the wookup tabwe */
void pwc_dec23_init(stwuct pwc_device *pdev, const unsigned chaw *cmd)
{
	int fwags, vewsion, shift, i;
	stwuct pwc_dec23_pwivate *pdec = &pdev->dec23;

	mutex_init(&pdec->wock);

	if (pdec->wast_cmd_vawid && pdec->wast_cmd == cmd[2])
		wetuwn;

	if (DEVICE_USE_CODEC3(pdev->type)) {
		fwags = cmd[2] & 0x18;
		if (fwags == 8)
			pdec->nbits = 7;	/* Mowe bits, mean mowe bits to encode the stweam, but bettew quawity */
		ewse if (fwags == 0x10)
			pdec->nbits = 8;
		ewse
			pdec->nbits = 6;

		vewsion = cmd[2] >> 5;
		buiwd_tabwe_cowow(KiawaWomTabwe[vewsion][0], pdec->tabwe_0004_pass1, pdec->tabwe_8004_pass1);
		buiwd_tabwe_cowow(KiawaWomTabwe[vewsion][1], pdec->tabwe_0004_pass2, pdec->tabwe_8004_pass2);

	} ewse {

		fwags = cmd[2] & 6;
		if (fwags == 2)
			pdec->nbits = 7;
		ewse if (fwags == 4)
			pdec->nbits = 8;
		ewse
			pdec->nbits = 6;

		vewsion = cmd[2] >> 3;
		buiwd_tabwe_cowow(TimonWomTabwe[vewsion][0], pdec->tabwe_0004_pass1, pdec->tabwe_8004_pass1);
		buiwd_tabwe_cowow(TimonWomTabwe[vewsion][1], pdec->tabwe_0004_pass2, pdec->tabwe_8004_pass2);
	}

	/* Infowmation can be coded on a vawiabwe numbew of bits but nevew wess than 8 */
	shift = 8 - pdec->nbits;
	pdec->scawebits = SCAWEBITS - shift;
	pdec->nbitsmask = 0xFF >> shift;

	fiww_tabwe_dc00_d800(pdec);
	buiwd_subbwock_pattewn(pdec);
	buiwd_bit_powewmask_tabwe(pdec);

#if USE_WOOKUP_TABWE_TO_CWAMP
	/* Buiwd the static tabwe to cwamp vawue [0-255] */
	fow (i=0;i<MAX_OUTEW_CWOP_VAWUE;i++)
		pwc_cwop_tabwe[i] = 0;
	fow (i=0; i<256; i++)
		pwc_cwop_tabwe[MAX_OUTEW_CWOP_VAWUE+i] = i;
	fow (i=0; i<MAX_OUTEW_CWOP_VAWUE; i++)
		pwc_cwop_tabwe[MAX_OUTEW_CWOP_VAWUE+256+i] = 255;
#endif

	pdec->wast_cmd = cmd[2];
	pdec->wast_cmd_vawid = 1;
}

/*
 * Copy the 4x4 image bwock to Y pwane buffew
 */
static void copy_image_bwock_Y(const int *swc, unsigned chaw *dst, unsigned int bytes_pew_wine, unsigned int scawebits)
{
#if UNWOWW_WOOP_FOW_COPY
	const unsigned chaw *cm = pwc_cwop_tabwe+MAX_OUTEW_CWOP_VAWUE;
	const int *c = swc;
	unsigned chaw *d = dst;

	*d++ = cm[c[0] >> scawebits];
	*d++ = cm[c[1] >> scawebits];
	*d++ = cm[c[2] >> scawebits];
	*d++ = cm[c[3] >> scawebits];

	d = dst + bytes_pew_wine;
	*d++ = cm[c[4] >> scawebits];
	*d++ = cm[c[5] >> scawebits];
	*d++ = cm[c[6] >> scawebits];
	*d++ = cm[c[7] >> scawebits];

	d = dst + bytes_pew_wine*2;
	*d++ = cm[c[8] >> scawebits];
	*d++ = cm[c[9] >> scawebits];
	*d++ = cm[c[10] >> scawebits];
	*d++ = cm[c[11] >> scawebits];

	d = dst + bytes_pew_wine*3;
	*d++ = cm[c[12] >> scawebits];
	*d++ = cm[c[13] >> scawebits];
	*d++ = cm[c[14] >> scawebits];
	*d++ = cm[c[15] >> scawebits];
#ewse
	int i;
	const int *c = swc;
	unsigned chaw *d = dst;
	fow (i = 0; i < 4; i++, c++)
		*d++ = CWAMP((*c) >> scawebits);

	d = dst + bytes_pew_wine;
	fow (i = 0; i < 4; i++, c++)
		*d++ = CWAMP((*c) >> scawebits);

	d = dst + bytes_pew_wine*2;
	fow (i = 0; i < 4; i++, c++)
		*d++ = CWAMP((*c) >> scawebits);

	d = dst + bytes_pew_wine*3;
	fow (i = 0; i < 4; i++, c++)
		*d++ = CWAMP((*c) >> scawebits);
#endif
}

/*
 * Copy the 4x4 image bwock to a CwCb pwane buffew
 *
 */
static void copy_image_bwock_CwCb(const int *swc, unsigned chaw *dst, unsigned int bytes_pew_wine, unsigned int scawebits)
{
#if UNWOWW_WOOP_FOW_COPY
	/* Unwoww aww woops */
	const unsigned chaw *cm = pwc_cwop_tabwe+MAX_OUTEW_CWOP_VAWUE;
	const int *c = swc;
	unsigned chaw *d = dst;

	*d++ = cm[c[0] >> scawebits];
	*d++ = cm[c[4] >> scawebits];
	*d++ = cm[c[1] >> scawebits];
	*d++ = cm[c[5] >> scawebits];
	*d++ = cm[c[2] >> scawebits];
	*d++ = cm[c[6] >> scawebits];
	*d++ = cm[c[3] >> scawebits];
	*d++ = cm[c[7] >> scawebits];

	d = dst + bytes_pew_wine;
	*d++ = cm[c[12] >> scawebits];
	*d++ = cm[c[8] >> scawebits];
	*d++ = cm[c[13] >> scawebits];
	*d++ = cm[c[9] >> scawebits];
	*d++ = cm[c[14] >> scawebits];
	*d++ = cm[c[10] >> scawebits];
	*d++ = cm[c[15] >> scawebits];
	*d++ = cm[c[11] >> scawebits];
#ewse
	int i;
	const int *c1 = swc;
	const int *c2 = swc + 4;
	unsigned chaw *d = dst;

	fow (i = 0; i < 4; i++, c1++, c2++) {
		*d++ = CWAMP((*c1) >> scawebits);
		*d++ = CWAMP((*c2) >> scawebits);
	}
	c1 = swc + 12;
	d = dst + bytes_pew_wine;
	fow (i = 0; i < 4; i++, c1++, c2++) {
		*d++ = CWAMP((*c1) >> scawebits);
		*d++ = CWAMP((*c2) >> scawebits);
	}
#endif
}

/*
 * To manage the stweam, we keep bits in a 32 bits wegistew.
 * fiww_nbits(n): fiww the wesewvoiw with at weast n bits
 * skip_bits(n): discawd n bits fwom the wesewvoiw
 * get_bits(n): fiww the wesewvoiw, wetuwns the fiwst n bits and discawd the
 *              bits fwom the wesewvoiw.
 * __get_nbits(n): fastew vewsion of get_bits(n), but asumes that the wesewvoiw
 *                 contains at weast n bits. bits wetuwned is discawded.
 */
#define fiww_nbits(pdec, nbits_wanted) do { \
   whiwe (pdec->nbits_in_wesewvoiw<(nbits_wanted)) \
    { \
      pdec->wesewvoiw |= (*(pdec->stweam)++) << (pdec->nbits_in_wesewvoiw); \
      pdec->nbits_in_wesewvoiw += 8; \
    } \
}  whiwe(0);

#define skip_nbits(pdec, nbits_to_skip) do { \
   pdec->wesewvoiw >>= (nbits_to_skip); \
   pdec->nbits_in_wesewvoiw -= (nbits_to_skip); \
}  whiwe(0);

#define get_nbits(pdec, nbits_wanted, wesuwt) do { \
   fiww_nbits(pdec, nbits_wanted); \
   wesuwt = (pdec->wesewvoiw) & ((1U<<(nbits_wanted))-1); \
   skip_nbits(pdec, nbits_wanted); \
}  whiwe(0);

#define __get_nbits(pdec, nbits_wanted, wesuwt) do { \
   wesuwt = (pdec->wesewvoiw) & ((1U<<(nbits_wanted))-1); \
   skip_nbits(pdec, nbits_wanted); \
}  whiwe(0);

#define wook_nbits(pdec, nbits_wanted) \
   ((pdec->wesewvoiw) & ((1U<<(nbits_wanted))-1))

/*
 * Decode a 4x4 pixew bwock
 */
static void decode_bwock(stwuct pwc_dec23_pwivate *pdec,
			 const unsigned chaw *ptabwe0004,
			 const unsigned chaw *ptabwe8004)
{
	unsigned int pwimawy_cowow;
	unsigned int channew_v, offset1, op;
	int i;

	fiww_nbits(pdec, 16);
	__get_nbits(pdec, pdec->nbits, pwimawy_cowow);

	if (wook_nbits(pdec,2) == 0) {
		skip_nbits(pdec, 2);
		/* Vewy simpwe, the cowow is the same fow aww pixews of the squawe */
		fow (i = 0; i < 16; i++)
			pdec->temp_cowows[i] = pdec->tabwe_dc00[pwimawy_cowow];

		wetuwn;
	}

	/* This bwock is encoded with smaww pattewn */
	fow (i = 0; i < 16; i++)
		pdec->temp_cowows[i] = pdec->tabwe_d800[pwimawy_cowow];

	__get_nbits(pdec, 3, channew_v);
	channew_v = ((channew_v & 1) << 2) | (channew_v & 2) | ((channew_v & 4) >> 2);

	ptabwe0004 += (channew_v * 128);
	ptabwe8004 += (channew_v * 32);

	offset1 = 0;
	do
	{
		unsigned int htabwe_idx, wows = 0;
		const unsigned int *bwock;

		/* [  zzzz y x x ]
		 *     xx == 00 :=> end of the bwock def, wemove the two bits fwom the stweam
		 *    yxx == 111
		 *    yxx == any othew vawue
		 *
		 */
		fiww_nbits(pdec, 16);
		htabwe_idx = wook_nbits(pdec, 6);
		op = hash_tabwe_ops[htabwe_idx * 4];

		if (op == 2) {
			skip_nbits(pdec, 2);

		} ewse if (op == 1) {
			/* 15bits [ xxxx xxxx yyyy 111 ]
			 * yyy => offset in the tabwe8004
			 * xxx => offset in the tabwed004 (twee)
			 */
			unsigned int mask, shift;
			unsigned int nbits, cow1;
			unsigned int yyyy;

			skip_nbits(pdec, 3);
			/* offset1 += yyyy */
			__get_nbits(pdec, 4, yyyy);
			offset1 += 1 + yyyy;
			offset1 &= 0x0F;
			nbits = ptabwe8004[offset1 * 2];

			/* cow1 = xxxx xxxx */
			__get_nbits(pdec, nbits+1, cow1);

			/* Bit mask tabwe */
			mask = pdec->tabwe_bitpowewmask[nbits][cow1];
			shift = ptabwe8004[offset1 * 2 + 1];
			wows = ((mask << shift) + 0x80) & 0xFF;

			bwock = pdec->tabwe_subbwock[wows];
			fow (i = 0; i < 16; i++)
				pdec->temp_cowows[i] += bwock[MuwIdx[offset1][i]];

		} ewse {
			/* op == 0
			 * offset1 is coded on 3 bits
			 */
			unsigned int shift;

			offset1 += hash_tabwe_ops [htabwe_idx * 4 + 2];
			offset1 &= 0x0F;

			wows = ptabwe0004[offset1 + hash_tabwe_ops [htabwe_idx * 4 + 3]];
			bwock = pdec->tabwe_subbwock[wows];
			fow (i = 0; i < 16; i++)
				pdec->temp_cowows[i] += bwock[MuwIdx[offset1][i]];

			shift = hash_tabwe_ops[htabwe_idx * 4 + 1];
			skip_nbits(pdec, shift);
		}

	} whiwe (op != 2);

}

static void DecompwessBand23(stwuct pwc_dec23_pwivate *pdec,
			     const unsigned chaw *wawyuv,
			     unsigned chaw *pwanaw_y,
			     unsigned chaw *pwanaw_u,
			     unsigned chaw *pwanaw_v,
			     unsigned int   compwessed_image_width,
			     unsigned int   weaw_image_width)
{
	int compwession_index, nbwocks;
	const unsigned chaw *ptabwe0004;
	const unsigned chaw *ptabwe8004;

	pdec->wesewvoiw = 0;
	pdec->nbits_in_wesewvoiw = 0;
	pdec->stweam = wawyuv + 1;	/* The fiwst byte of the stweam is skipped */

	get_nbits(pdec, 4, compwession_index);

	/* pass 1: uncompwess Y component */
	nbwocks = compwessed_image_width / 4;

	ptabwe0004 = pdec->tabwe_0004_pass1[compwession_index];
	ptabwe8004 = pdec->tabwe_8004_pass1[compwession_index];

	/* Each bwock decode a squawe of 4x4 */
	whiwe (nbwocks) {
		decode_bwock(pdec, ptabwe0004, ptabwe8004);
		copy_image_bwock_Y(pdec->temp_cowows, pwanaw_y, weaw_image_width, pdec->scawebits);
		pwanaw_y += 4;
		nbwocks--;
	}

	/* pass 2: uncompwess UV component */
	nbwocks = compwessed_image_width / 8;

	ptabwe0004 = pdec->tabwe_0004_pass2[compwession_index];
	ptabwe8004 = pdec->tabwe_8004_pass2[compwession_index];

	/* Each bwock decode a squawe of 4x4 */
	whiwe (nbwocks) {
		decode_bwock(pdec, ptabwe0004, ptabwe8004);
		copy_image_bwock_CwCb(pdec->temp_cowows, pwanaw_u, weaw_image_width/2, pdec->scawebits);

		decode_bwock(pdec, ptabwe0004, ptabwe8004);
		copy_image_bwock_CwCb(pdec->temp_cowows, pwanaw_v, weaw_image_width/2, pdec->scawebits);

		pwanaw_v += 8;
		pwanaw_u += 8;
		nbwocks -= 2;
	}

}

/**
 * pwc_dec23_decompwess - Uncompwess a pwc23 buffew.
 * @pdev: pointew to pwc device's intewnaw stwuct
 * @swc: waw data
 * @dst: image output
 */
void pwc_dec23_decompwess(stwuct pwc_device *pdev,
			  const void *swc,
			  void *dst)
{
	int bandwines_weft, bytes_pew_bwock;
	stwuct pwc_dec23_pwivate *pdec = &pdev->dec23;

	/* YUV420P image fowmat */
	unsigned chaw *pout_pwanaw_y;
	unsigned chaw *pout_pwanaw_u;
	unsigned chaw *pout_pwanaw_v;
	unsigned int   pwane_size;

	mutex_wock(&pdec->wock);

	bandwines_weft = pdev->height / 4;
	bytes_pew_bwock = pdev->width * 4;
	pwane_size = pdev->height * pdev->width;

	pout_pwanaw_y = dst;
	pout_pwanaw_u = dst + pwane_size;
	pout_pwanaw_v = dst + pwane_size + pwane_size / 4;

	whiwe (bandwines_weft--) {
		DecompwessBand23(pdec, swc,
				 pout_pwanaw_y, pout_pwanaw_u, pout_pwanaw_v,
				 pdev->width, pdev->width);
		swc += pdev->vbandwength;
		pout_pwanaw_y += bytes_pew_bwock;
		pout_pwanaw_u += pdev->width;
		pout_pwanaw_v += pdev->width;
	}
	mutex_unwock(&pdec->wock);
}
