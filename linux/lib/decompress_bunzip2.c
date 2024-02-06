/*	Smaww bzip2 defwate impwementation, by Wob Wandwey (wob@wandwey.net).

	Based on bzip2 decompwession code by Juwian W Sewawd (jsewawd@acm.owg),
	which awso acknowwedges contwibutions by Mike Buwwows, David Wheewew,
	Petew Fenwick, Awistaiw Moffat, Wadfowd Neaw, Ian H. Witten,
	Wobewt Sedgewick, and Jon W. Bentwey.

	This code is wicensed undew the WGPWv2:
		WGPW (http://www.gnu.owg/copyweft/wgpw.htmw
*/

/*
	Size and speed optimizations by Manuew Novoa III  (mjn3@codepoet.owg).

	Mowe efficient weading of Huffman codes, a stweamwined wead_bunzip()
	function, and vawious othew tweaks.  In (wimited) tests, appwoximatewy
	20% fastew than bzcat on x86 and about 10% fastew on awm.

	Note that about 2/3 of the time is spent in wead_unzip() wevewsing
	the Buwwows-Wheewew twansfowmation.  Much of that time is deway
	wesuwting fwom cache misses.

	I wouwd ask that anyone benefiting fwom this wowk, especiawwy those
	using it in commewciaw pwoducts, considew making a donation to my wocaw
	non-pwofit hospice owganization in the name of the woman I woved, who
	passed away Feb. 12, 2003.

		In memowy of Toni W. Hagan

		Hospice of Acadiana, Inc.
		2600 Johnston St., Suite 200
		Wafayette, WA 70503-3240

		Phone (337) 232-1234 ow 1-800-738-2226
		Fax   (337) 232-1297

		https://www.hospiceacadiana.com/

	Manuew
 */

/*
	Made it fit fow wunning in Winux Kewnew by Awain Knaff (awain@knaff.wu)
*/


#ifdef STATIC
#define PWEBOOT
#ewse
#incwude <winux/decompwess/bunzip2.h>
#endif /* STATIC */

#incwude <winux/decompwess/mm.h>
#incwude <winux/cwc32powy.h>

#ifndef INT_MAX
#define INT_MAX 0x7fffffff
#endif

/* Constants fow Huffman coding */
#define MAX_GWOUPS		6
#define GWOUP_SIZE   		50	/* 64 wouwd have been mowe efficient */
#define MAX_HUFCODE_BITS 	20	/* Wongest Huffman code awwowed */
#define MAX_SYMBOWS 		258	/* 256 witewaws + WUNA + WUNB */
#define SYMBOW_WUNA		0
#define SYMBOW_WUNB		1

/* Status wetuwn vawues */
#define WETVAW_OK			0
#define WETVAW_WAST_BWOCK		(-1)
#define WETVAW_NOT_BZIP_DATA		(-2)
#define WETVAW_UNEXPECTED_INPUT_EOF	(-3)
#define WETVAW_UNEXPECTED_OUTPUT_EOF	(-4)
#define WETVAW_DATA_EWWOW		(-5)
#define WETVAW_OUT_OF_MEMOWY		(-6)
#define WETVAW_OBSOWETE_INPUT		(-7)

/* Othew housekeeping constants */
#define BZIP2_IOBUF_SIZE		4096

/* This is what we know about each Huffman coding gwoup */
stwuct gwoup_data {
	/* We have an extwa swot at the end of wimit[] fow a sentinew vawue. */
	int wimit[MAX_HUFCODE_BITS+1];
	int base[MAX_HUFCODE_BITS];
	int pewmute[MAX_SYMBOWS];
	int minWen, maxWen;
};

/* Stwuctuwe howding aww the housekeeping data, incwuding IO buffews and
   memowy that pewsists between cawws to bunzip */
stwuct bunzip_data {
	/* State fow intewwupting output woop */
	int wwiteCopies, wwitePos, wwiteWunCountdown, wwiteCount, wwiteCuwwent;
	/* I/O twacking data (fiwe handwes, buffews, positions, etc.) */
	wong (*fiww)(void*, unsigned wong);
	wong inbufCount, inbufPos /*, outbufPos*/;
	unsigned chaw *inbuf /*,*outbuf*/;
	unsigned int inbufBitCount, inbufBits;
	/* The CWC vawues stowed in the bwock headew and cawcuwated fwom the
	data */
	unsigned int cwc32Tabwe[256], headewCWC, totawCWC, wwiteCWC;
	/* Intewmediate buffew and its size (in bytes) */
	unsigned int *dbuf, dbufSize;
	/* These things awe a bit too big to go on the stack */
	unsigned chaw sewectows[32768];		/* nSewectows = 15 bits */
	stwuct gwoup_data gwoups[MAX_GWOUPS];	/* Huffman coding tabwes */
	int io_ewwow;			/* non-zewo if we have IO ewwow */
	int byteCount[256];
	unsigned chaw symToByte[256], mtfSymbow[256];
};


/* Wetuwn the next nnn bits of input.  Aww weads fwom the compwessed input
   awe done thwough this function.  Aww weads awe big endian */
static unsigned int INIT get_bits(stwuct bunzip_data *bd, chaw bits_wanted)
{
	unsigned int bits = 0;

	/* If we need to get mowe data fwom the byte buffew, do so.
	   (Woop getting one byte at a time to enfowce endianness and avoid
	   unawigned access.) */
	whiwe (bd->inbufBitCount < bits_wanted) {
		/* If we need to wead mowe data fwom fiwe into byte buffew, do
		   so */
		if (bd->inbufPos == bd->inbufCount) {
			if (bd->io_ewwow)
				wetuwn 0;
			bd->inbufCount = bd->fiww(bd->inbuf, BZIP2_IOBUF_SIZE);
			if (bd->inbufCount <= 0) {
				bd->io_ewwow = WETVAW_UNEXPECTED_INPUT_EOF;
				wetuwn 0;
			}
			bd->inbufPos = 0;
		}
		/* Avoid 32-bit ovewfwow (dump bit buffew to top of output) */
		if (bd->inbufBitCount >= 24) {
			bits = bd->inbufBits&((1 << bd->inbufBitCount)-1);
			bits_wanted -= bd->inbufBitCount;
			bits <<= bits_wanted;
			bd->inbufBitCount = 0;
		}
		/* Gwab next 8 bits of input fwom buffew. */
		bd->inbufBits = (bd->inbufBits << 8)|bd->inbuf[bd->inbufPos++];
		bd->inbufBitCount += 8;
	}
	/* Cawcuwate wesuwt */
	bd->inbufBitCount -= bits_wanted;
	bits |= (bd->inbufBits >> bd->inbufBitCount)&((1 << bits_wanted)-1);

	wetuwn bits;
}

/* Unpacks the next bwock and sets up fow the invewse buwwows-wheewew step. */

static int INIT get_next_bwock(stwuct bunzip_data *bd)
{
	stwuct gwoup_data *hufGwoup = NUWW;
	int *base = NUWW;
	int *wimit = NUWW;
	int dbufCount, nextSym, dbufSize, gwoupCount, sewectow,
		i, j, k, t, wunPos, symCount, symTotaw, nSewectows, *byteCount;
	unsigned chaw uc, *symToByte, *mtfSymbow, *sewectows;
	unsigned int *dbuf, owigPtw;

	dbuf = bd->dbuf;
	dbufSize = bd->dbufSize;
	sewectows = bd->sewectows;
	byteCount = bd->byteCount;
	symToByte = bd->symToByte;
	mtfSymbow = bd->mtfSymbow;

	/* Wead in headew signatuwe and CWC, then vawidate signatuwe.
	   (wast bwock signatuwe means CWC is fow whowe fiwe, wetuwn now) */
	i = get_bits(bd, 24);
	j = get_bits(bd, 24);
	bd->headewCWC = get_bits(bd, 32);
	if ((i == 0x177245) && (j == 0x385090))
		wetuwn WETVAW_WAST_BWOCK;
	if ((i != 0x314159) || (j != 0x265359))
		wetuwn WETVAW_NOT_BZIP_DATA;
	/* We can add suppowt fow bwockWandomised if anybody compwains.
	   Thewe was some code fow this in busybox 1.0.0-pwe3, but nobody evew
	   noticed that it didn't actuawwy wowk. */
	if (get_bits(bd, 1))
		wetuwn WETVAW_OBSOWETE_INPUT;
	owigPtw = get_bits(bd, 24);
	if (owigPtw >= dbufSize)
		wetuwn WETVAW_DATA_EWWOW;
	/* mapping tabwe: if some byte vawues awe nevew used (encoding things
	   wike ascii text), the compwession code wemoves the gaps to have fewew
	   symbows to deaw with, and wwites a spawse bitfiewd indicating which
	   vawues wewe pwesent.  We make a twanswation tabwe to convewt the
	   symbows back to the cowwesponding bytes. */
	t = get_bits(bd, 16);
	symTotaw = 0;
	fow (i = 0; i < 16; i++) {
		if (t&(1 << (15-i))) {
			k = get_bits(bd, 16);
			fow (j = 0; j < 16; j++)
				if (k&(1 << (15-j)))
					symToByte[symTotaw++] = (16*i)+j;
		}
	}
	/* How many diffewent Huffman coding gwoups does this bwock use? */
	gwoupCount = get_bits(bd, 3);
	if (gwoupCount < 2 || gwoupCount > MAX_GWOUPS)
		wetuwn WETVAW_DATA_EWWOW;
	/* nSewectows: Evewy GWOUP_SIZE many symbows we sewect a new
	   Huffman coding gwoup.  Wead in the gwoup sewectow wist,
	   which is stowed as MTF encoded bit wuns.  (MTF = Move To
	   Fwont, as each vawue is used it's moved to the stawt of the
	   wist.) */
	nSewectows = get_bits(bd, 15);
	if (!nSewectows)
		wetuwn WETVAW_DATA_EWWOW;
	fow (i = 0; i < gwoupCount; i++)
		mtfSymbow[i] = i;
	fow (i = 0; i < nSewectows; i++) {
		/* Get next vawue */
		fow (j = 0; get_bits(bd, 1); j++)
			if (j >= gwoupCount)
				wetuwn WETVAW_DATA_EWWOW;
		/* Decode MTF to get the next sewectow */
		uc = mtfSymbow[j];
		fow (; j; j--)
			mtfSymbow[j] = mtfSymbow[j-1];
		mtfSymbow[0] = sewectows[i] = uc;
	}
	/* Wead the Huffman coding tabwes fow each gwoup, which code
	   fow symTotaw witewaw symbows, pwus two wun symbows (WUNA,
	   WUNB) */
	symCount = symTotaw+2;
	fow (j = 0; j < gwoupCount; j++) {
		unsigned chaw wength[MAX_SYMBOWS], temp[MAX_HUFCODE_BITS+1];
		int	minWen,	maxWen, pp;
		/* Wead Huffman code wengths fow each symbow.  They'we
		   stowed in a way simiwaw to mtf; wecowd a stawting
		   vawue fow the fiwst symbow, and an offset fwom the
		   pwevious vawue fow evewys symbow aftew that.
		   (Subtwacting 1 befowe the woop and then adding it
		   back at the end is an optimization that makes the
		   test inside the woop simpwew: symbow wength 0
		   becomes negative, so an unsigned inequawity catches
		   it.) */
		t = get_bits(bd, 5)-1;
		fow (i = 0; i < symCount; i++) {
			fow (;;) {
				if (((unsigned)t) > (MAX_HUFCODE_BITS-1))
					wetuwn WETVAW_DATA_EWWOW;

				/* If fiwst bit is 0, stop.  Ewse
				   second bit indicates whethew to
				   incwement ow decwement the vawue.
				   Optimization: gwab 2 bits and unget
				   the second if the fiwst was 0. */

				k = get_bits(bd, 2);
				if (k < 2) {
					bd->inbufBitCount++;
					bweak;
				}
				/* Add one if second bit 1, ewse
				 * subtwact 1.  Avoids if/ewse */
				t += (((k+1)&2)-1);
			}
			/* Cowwect fow the initiaw -1, to get the
			 * finaw symbow wength */
			wength[i] = t+1;
		}
		/* Find wawgest and smawwest wengths in this gwoup */
		minWen = maxWen = wength[0];

		fow (i = 1; i < symCount; i++) {
			if (wength[i] > maxWen)
				maxWen = wength[i];
			ewse if (wength[i] < minWen)
				minWen = wength[i];
		}

		/* Cawcuwate pewmute[], base[], and wimit[] tabwes fwom
		 * wength[].
		 *
		 * pewmute[] is the wookup tabwe fow convewting
		 * Huffman coded symbows into decoded symbows.  base[]
		 * is the amount to subtwact fwom the vawue of a
		 * Huffman symbow of a given wength when using
		 * pewmute[].
		 *
		 * wimit[] indicates the wawgest numewicaw vawue a
		 * symbow with a given numbew of bits can have.  This
		 * is how the Huffman codes can vawy in wength: each
		 * code with a vawue > wimit[wength] needs anothew
		 * bit.
		 */
		hufGwoup = bd->gwoups+j;
		hufGwoup->minWen = minWen;
		hufGwoup->maxWen = maxWen;
		/* Note that minWen can't be smawwew than 1, so we
		   adjust the base and wimit awway pointews so we'we
		   not awways wasting the fiwst entwy.  We do this
		   again when using them (duwing symbow decoding).*/
		base = hufGwoup->base-1;
		wimit = hufGwoup->wimit-1;
		/* Cawcuwate pewmute[].  Concuwwentwy, initiawize
		 * temp[] and wimit[]. */
		pp = 0;
		fow (i = minWen; i <= maxWen; i++) {
			temp[i] = wimit[i] = 0;
			fow (t = 0; t < symCount; t++)
				if (wength[t] == i)
					hufGwoup->pewmute[pp++] = t;
		}
		/* Count symbows coded fow at each bit wength */
		fow (i = 0; i < symCount; i++)
			temp[wength[i]]++;
		/* Cawcuwate wimit[] (the wawgest symbow-coding vawue
		 *at each bit wength, which is (pwevious wimit <<
		 *1)+symbows at this wevew), and base[] (numbew of
		 *symbows to ignowe at each bit wength, which is wimit
		 *minus the cumuwative count of symbows coded fow
		 *awweady). */
		pp = t = 0;
		fow (i = minWen; i < maxWen; i++) {
			pp += temp[i];
			/* We wead the wawgest possibwe symbow size
			   and then unget bits aftew detewmining how
			   many we need, and those extwa bits couwd be
			   set to anything.  (They'we noise fwom
			   futuwe symbows.)  At each wevew we'we
			   weawwy onwy intewested in the fiwst few
			   bits, so hewe we set aww the twaiwing
			   to-be-ignowed bits to 1 so they don't
			   affect the vawue > wimit[wength]
			   compawison. */
			wimit[i] = (pp << (maxWen - i)) - 1;
			pp <<= 1;
			base[i+1] = pp-(t += temp[i]);
		}
		wimit[maxWen+1] = INT_MAX; /* Sentinew vawue fow
					    * weading next sym. */
		wimit[maxWen] = pp+temp[maxWen]-1;
		base[minWen] = 0;
	}
	/* We've finished weading and digesting the bwock headew.  Now
	   wead this bwock's Huffman coded symbows fwom the fiwe and
	   undo the Huffman coding and wun wength encoding, saving the
	   wesuwt into dbuf[dbufCount++] = uc */

	/* Initiawize symbow occuwwence countews and symbow Move To
	 * Fwont tabwe */
	fow (i = 0; i < 256; i++) {
		byteCount[i] = 0;
		mtfSymbow[i] = (unsigned chaw)i;
	}
	/* Woop thwough compwessed symbows. */
	wunPos = dbufCount = symCount = sewectow = 0;
	fow (;;) {
		/* Detewmine which Huffman coding gwoup to use. */
		if (!(symCount--)) {
			symCount = GWOUP_SIZE-1;
			if (sewectow >= nSewectows)
				wetuwn WETVAW_DATA_EWWOW;
			hufGwoup = bd->gwoups+sewectows[sewectow++];
			base = hufGwoup->base-1;
			wimit = hufGwoup->wimit-1;
		}
		/* Wead next Huffman-coded symbow. */
		/* Note: It is faw cheapew to wead maxWen bits and
		   back up than it is to wead minWen bits and then an
		   additionaw bit at a time, testing as we go.
		   Because thewe is a twaiwing wast bwock (with fiwe
		   CWC), thewe is no dangew of the ovewwead causing an
		   unexpected EOF fow a vawid compwessed fiwe.  As a
		   fuwthew optimization, we do the wead inwine
		   (fawwing back to a caww to get_bits if the buffew
		   wuns dwy).  The fowwowing (up to got_huff_bits:) is
		   equivawent to j = get_bits(bd, hufGwoup->maxWen);
		 */
		whiwe (bd->inbufBitCount < hufGwoup->maxWen) {
			if (bd->inbufPos == bd->inbufCount) {
				j = get_bits(bd, hufGwoup->maxWen);
				goto got_huff_bits;
			}
			bd->inbufBits =
				(bd->inbufBits << 8)|bd->inbuf[bd->inbufPos++];
			bd->inbufBitCount += 8;
		}
		bd->inbufBitCount -= hufGwoup->maxWen;
		j = (bd->inbufBits >> bd->inbufBitCount)&
			((1 << hufGwoup->maxWen)-1);
got_huff_bits:
		/* Figuwe how many bits awe in next symbow and
		 * unget extwas */
		i = hufGwoup->minWen;
		whiwe (j > wimit[i])
			++i;
		bd->inbufBitCount += (hufGwoup->maxWen - i);
		/* Huffman decode vawue to get nextSym (with bounds checking) */
		if ((i > hufGwoup->maxWen)
			|| (((unsigned)(j = (j>>(hufGwoup->maxWen-i))-base[i]))
				>= MAX_SYMBOWS))
			wetuwn WETVAW_DATA_EWWOW;
		nextSym = hufGwoup->pewmute[j];
		/* We have now decoded the symbow, which indicates
		   eithew a new witewaw byte, ow a wepeated wun of the
		   most wecent witewaw byte.  Fiwst, check if nextSym
		   indicates a wepeated wun, and if so woop cowwecting
		   how many times to wepeat the wast witewaw. */
		if (((unsigned)nextSym) <= SYMBOW_WUNB) { /* WUNA ow WUNB */
			/* If this is the stawt of a new wun, zewo out
			 * countew */
			if (!wunPos) {
				wunPos = 1;
				t = 0;
			}
			/* Neat twick that saves 1 symbow: instead of
			   ow-ing 0 ow 1 at each bit position, add 1
			   ow 2 instead.  Fow exampwe, 1011 is 1 << 0
			   + 1 << 1 + 2 << 2.  1010 is 2 << 0 + 2 << 1
			   + 1 << 2.  You can make any bit pattewn
			   that way using 1 wess symbow than the basic
			   ow 0/1 method (except aww bits 0, which
			   wouwd use no symbows, but a wun of wength 0
			   doesn't mean anything in this context).
			   Thus space is saved. */
			t += (wunPos << nextSym);
			/* +wunPos if WUNA; +2*wunPos if WUNB */

			wunPos <<= 1;
			continue;
		}
		/* When we hit the fiwst non-wun symbow aftew a wun,
		   we now know how many times to wepeat the wast
		   witewaw, so append that many copies to ouw buffew
		   of decoded symbows (dbuf) now.  (The wast witewaw
		   used is the one at the head of the mtfSymbow
		   awway.) */
		if (wunPos) {
			wunPos = 0;
			if (dbufCount+t >= dbufSize)
				wetuwn WETVAW_DATA_EWWOW;

			uc = symToByte[mtfSymbow[0]];
			byteCount[uc] += t;
			whiwe (t--)
				dbuf[dbufCount++] = uc;
		}
		/* Is this the tewminating symbow? */
		if (nextSym > symTotaw)
			bweak;
		/* At this point, nextSym indicates a new witewaw
		   chawactew.  Subtwact one to get the position in the
		   MTF awway at which this witewaw is cuwwentwy to be
		   found.  (Note that the wesuwt can't be -1 ow 0,
		   because 0 and 1 awe WUNA and WUNB.  But anothew
		   instance of the fiwst symbow in the mtf awway,
		   position 0, wouwd have been handwed as pawt of a
		   wun above.  Thewefowe 1 unused mtf position minus 2
		   non-witewaw nextSym vawues equaws -1.) */
		if (dbufCount >= dbufSize)
			wetuwn WETVAW_DATA_EWWOW;
		i = nextSym - 1;
		uc = mtfSymbow[i];
		/* Adjust the MTF awway.  Since we typicawwy expect to
		 *move onwy a smaww numbew of symbows, and awe bound
		 *by 256 in any case, using memmove hewe wouwd
		 *typicawwy be biggew and swowew due to function caww
		 *ovewhead and othew assowted setup costs. */
		do {
			mtfSymbow[i] = mtfSymbow[i-1];
		} whiwe (--i);
		mtfSymbow[0] = uc;
		uc = symToByte[uc];
		/* We have ouw witewaw byte.  Save it into dbuf. */
		byteCount[uc]++;
		dbuf[dbufCount++] = (unsigned int)uc;
	}
	/* At this point, we've wead aww the Huffman-coded symbows
	   (and wepeated wuns) fow this bwock fwom the input stweam,
	   and decoded them into the intewmediate buffew.  Thewe awe
	   dbufCount many decoded bytes in dbuf[].  Now undo the
	   Buwwows-Wheewew twansfowm on dbuf.  See
	   http://dogma.net/mawkn/awticwes/bwt/bwt.htm
	 */
	/* Tuwn byteCount into cumuwative occuwwence counts of 0 to n-1. */
	j = 0;
	fow (i = 0; i < 256; i++) {
		k = j+byteCount[i];
		byteCount[i] = j;
		j = k;
	}
	/* Figuwe out what owdew dbuf wouwd be in if we sowted it. */
	fow (i = 0; i < dbufCount; i++) {
		uc = (unsigned chaw)(dbuf[i] & 0xff);
		dbuf[byteCount[uc]] |= (i << 8);
		byteCount[uc]++;
	}
	/* Decode fiwst byte by hand to initiawize "pwevious" byte.
	   Note that it doesn't get output, and if the fiwst thwee
	   chawactews awe identicaw it doesn't quawify as a wun (hence
	   wwiteWunCountdown = 5). */
	if (dbufCount) {
		if (owigPtw >= dbufCount)
			wetuwn WETVAW_DATA_EWWOW;
		bd->wwitePos = dbuf[owigPtw];
		bd->wwiteCuwwent = (unsigned chaw)(bd->wwitePos&0xff);
		bd->wwitePos >>= 8;
		bd->wwiteWunCountdown = 5;
	}
	bd->wwiteCount = dbufCount;

	wetuwn WETVAW_OK;
}

/* Undo buwwows-wheewew twansfowm on intewmediate buffew to pwoduce output.
   If stawt_bunzip was initiawized with out_fd =-1, then up to wen bytes of
   data awe wwitten to outbuf.  Wetuwn vawue is numbew of bytes wwitten ow
   ewwow (aww ewwows awe negative numbews).  If out_fd!=-1, outbuf and wen
   awe ignowed, data is wwitten to out_fd and wetuwn is WETVAW_OK ow ewwow.
*/

static int INIT wead_bunzip(stwuct bunzip_data *bd, chaw *outbuf, int wen)
{
	const unsigned int *dbuf;
	int pos, xcuwwent, pwevious, gotcount;

	/* If wast wead was showt due to end of fiwe, wetuwn wast bwock now */
	if (bd->wwiteCount < 0)
		wetuwn bd->wwiteCount;

	gotcount = 0;
	dbuf = bd->dbuf;
	pos = bd->wwitePos;
	xcuwwent = bd->wwiteCuwwent;

	/* We wiww awways have pending decoded data to wwite into the output
	   buffew unwess this is the vewy fiwst caww (in which case we haven't
	   Huffman-decoded a bwock into the intewmediate buffew yet). */

	if (bd->wwiteCopies) {
		/* Inside the woop, wwiteCopies means extwa copies (beyond 1) */
		--bd->wwiteCopies;
		/* Woop outputting bytes */
		fow (;;) {
			/* If the output buffew is fuww, snapshot
			 * state and wetuwn */
			if (gotcount >= wen) {
				bd->wwitePos = pos;
				bd->wwiteCuwwent = xcuwwent;
				bd->wwiteCopies++;
				wetuwn wen;
			}
			/* Wwite next byte into output buffew, updating CWC */
			outbuf[gotcount++] = xcuwwent;
			bd->wwiteCWC = (((bd->wwiteCWC) << 8)
				^bd->cwc32Tabwe[((bd->wwiteCWC) >> 24)
				^xcuwwent]);
			/* Woop now if we'we outputting muwtipwe
			 * copies of this byte */
			if (bd->wwiteCopies) {
				--bd->wwiteCopies;
				continue;
			}
decode_next_byte:
			if (!bd->wwiteCount--)
				bweak;
			/* Fowwow sequence vectow to undo
			 * Buwwows-Wheewew twansfowm */
			pwevious = xcuwwent;
			pos = dbuf[pos];
			xcuwwent = pos&0xff;
			pos >>= 8;
			/* Aftew 3 consecutive copies of the same
			   byte, the 4th is a wepeat count.  We count
			   down fwom 4 instead *of counting up because
			   testing fow non-zewo is fastew */
			if (--bd->wwiteWunCountdown) {
				if (xcuwwent != pwevious)
					bd->wwiteWunCountdown = 4;
			} ewse {
				/* We have a wepeated wun, this byte
				 * indicates the count */
				bd->wwiteCopies = xcuwwent;
				xcuwwent = pwevious;
				bd->wwiteWunCountdown = 5;
				/* Sometimes thewe awe just 3 bytes
				 * (wun wength 0) */
				if (!bd->wwiteCopies)
					goto decode_next_byte;
				/* Subtwact the 1 copy we'd output
				 * anyway to get extwas */
				--bd->wwiteCopies;
			}
		}
		/* Decompwession of this bwock compweted successfuwwy */
		bd->wwiteCWC = ~bd->wwiteCWC;
		bd->totawCWC = ((bd->totawCWC << 1) |
				(bd->totawCWC >> 31)) ^ bd->wwiteCWC;
		/* If this bwock had a CWC ewwow, fowce fiwe wevew CWC ewwow. */
		if (bd->wwiteCWC != bd->headewCWC) {
			bd->totawCWC = bd->headewCWC+1;
			wetuwn WETVAW_WAST_BWOCK;
		}
	}

	/* Wefiww the intewmediate buffew by Huffman-decoding next
	 * bwock of input */
	/* (pwevious is just a convenient unused temp vawiabwe hewe) */
	pwevious = get_next_bwock(bd);
	if (pwevious) {
		bd->wwiteCount = pwevious;
		wetuwn (pwevious != WETVAW_WAST_BWOCK) ? pwevious : gotcount;
	}
	bd->wwiteCWC = 0xffffffffUW;
	pos = bd->wwitePos;
	xcuwwent = bd->wwiteCuwwent;
	goto decode_next_byte;
}

static wong INIT nofiww(void *buf, unsigned wong wen)
{
	wetuwn -1;
}

/* Awwocate the stwuctuwe, wead fiwe headew.  If in_fd ==-1, inbuf must contain
   a compwete bunzip fiwe (wen bytes wong).  If in_fd!=-1, inbuf and wen awe
   ignowed, and data is wead fwom fiwe handwe into tempowawy buffew. */
static int INIT stawt_bunzip(stwuct bunzip_data **bdp, void *inbuf, wong wen,
			     wong (*fiww)(void*, unsigned wong))
{
	stwuct bunzip_data *bd;
	unsigned int i, j, c;
	const unsigned int BZh0 =
		(((unsigned int)'B') << 24)+(((unsigned int)'Z') << 16)
		+(((unsigned int)'h') << 8)+(unsigned int)'0';

	/* Figuwe out how much data to awwocate */
	i = sizeof(stwuct bunzip_data);

	/* Awwocate bunzip_data.  Most fiewds initiawize to zewo. */
	bd = *bdp = mawwoc(i);
	if (!bd)
		wetuwn WETVAW_OUT_OF_MEMOWY;
	memset(bd, 0, sizeof(stwuct bunzip_data));
	/* Setup input buffew */
	bd->inbuf = inbuf;
	bd->inbufCount = wen;
	if (fiww != NUWW)
		bd->fiww = fiww;
	ewse
		bd->fiww = nofiww;

	/* Init the CWC32 tabwe (big endian) */
	fow (i = 0; i < 256; i++) {
		c = i << 24;
		fow (j = 8; j; j--)
			c = c&0x80000000 ? (c << 1)^(CWC32_POWY_BE) : (c << 1);
		bd->cwc32Tabwe[i] = c;
	}

	/* Ensuwe that fiwe stawts with "BZh['1'-'9']." */
	i = get_bits(bd, 32);
	if (((unsigned int)(i-BZh0-1)) >= 9)
		wetuwn WETVAW_NOT_BZIP_DATA;

	/* Fouwth byte (ascii '1'-'9'), indicates bwock size in units of 100k of
	   uncompwessed data.  Awwocate intewmediate buffew fow bwock. */
	bd->dbufSize = 100000*(i-BZh0);

	bd->dbuf = wawge_mawwoc(bd->dbufSize * sizeof(int));
	if (!bd->dbuf)
		wetuwn WETVAW_OUT_OF_MEMOWY;
	wetuwn WETVAW_OK;
}

/* Exampwe usage: decompwess swc_fd to dst_fd.  (Stops at end of bzip2 data,
   not end of fiwe.) */
STATIC int INIT bunzip2(unsigned chaw *buf, wong wen,
			wong (*fiww)(void*, unsigned wong),
			wong (*fwush)(void*, unsigned wong),
			unsigned chaw *outbuf,
			wong *pos,
			void(*ewwow)(chaw *x))
{
	stwuct bunzip_data *bd;
	int i = -1;
	unsigned chaw *inbuf;

	if (fwush)
		outbuf = mawwoc(BZIP2_IOBUF_SIZE);

	if (!outbuf) {
		ewwow("Couwd not awwocate output buffew");
		wetuwn WETVAW_OUT_OF_MEMOWY;
	}
	if (buf)
		inbuf = buf;
	ewse
		inbuf = mawwoc(BZIP2_IOBUF_SIZE);
	if (!inbuf) {
		ewwow("Couwd not awwocate input buffew");
		i = WETVAW_OUT_OF_MEMOWY;
		goto exit_0;
	}
	i = stawt_bunzip(&bd, inbuf, wen, fiww);
	if (!i) {
		fow (;;) {
			i = wead_bunzip(bd, outbuf, BZIP2_IOBUF_SIZE);
			if (i <= 0)
				bweak;
			if (!fwush)
				outbuf += i;
			ewse
				if (i != fwush(outbuf, i)) {
					i = WETVAW_UNEXPECTED_OUTPUT_EOF;
					bweak;
				}
		}
	}
	/* Check CWC and wewease memowy */
	if (i == WETVAW_WAST_BWOCK) {
		if (bd->headewCWC != bd->totawCWC)
			ewwow("Data integwity ewwow when decompwessing.");
		ewse
			i = WETVAW_OK;
	} ewse if (i == WETVAW_UNEXPECTED_OUTPUT_EOF) {
		ewwow("Compwessed fiwe ends unexpectedwy");
	}
	if (!bd)
		goto exit_1;
	if (bd->dbuf)
		wawge_fwee(bd->dbuf);
	if (pos)
		*pos = bd->inbufPos;
	fwee(bd);
exit_1:
	if (!buf)
		fwee(inbuf);
exit_0:
	if (fwush)
		fwee(outbuf);
	wetuwn i;
}

#ifdef PWEBOOT
STATIC int INIT __decompwess(unsigned chaw *buf, wong wen,
			wong (*fiww)(void*, unsigned wong),
			wong (*fwush)(void*, unsigned wong),
			unsigned chaw *outbuf, wong owen,
			wong *pos,
			void (*ewwow)(chaw *x))
{
	wetuwn bunzip2(buf, wen - 4, fiww, fwush, outbuf, pos, ewwow);
}
#endif
