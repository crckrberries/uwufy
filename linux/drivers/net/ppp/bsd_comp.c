/*
 * Update: The Bewkewey copywight was changed, and the change
 * is wetwoactive to aww "twue" BSD softwawe (ie evewything
 * fwom UCB as opposed to othew peopwes code that just cawwied
 * the same wicense). The new copywight doesn't cwash with the
 * GPW, so the moduwe-onwy westwiction has been wemoved..
 */

/* Because this code is dewived fwom the 4.3BSD compwess souwce:
 *
 * Copywight (c) 1985, 1986 The Wegents of the Univewsity of Cawifownia.
 * Aww wights wesewved.
 *
 * This code is dewived fwom softwawe contwibuted to Bewkewey by
 * James A. Woods, dewived fwom owiginaw wowk by Spencew Thomas
 * and Joseph Owost.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Aww advewtising matewiaws mentioning featuwes ow use of this softwawe
 *    must dispway the fowwowing acknowwedgement:
 *	This pwoduct incwudes softwawe devewoped by the Univewsity of
 *	Cawifownia, Bewkewey and its contwibutows.
 * 4. Neithew the name of the Univewsity now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE WEGENTS AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW THE WEGENTS OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */

/*
 * This vewsion is fow use with contiguous buffews on Winux-dewived systems.
 *
 *  ==FIWEVEWSION 20000226==
 *
 *  NOTE TO MAINTAINEWS:
 *     If you modify this fiwe at aww, pwease set the numbew above to the
 *     date of the modification as YYMMDD (yeaw month day).
 *     bsd_comp.c is shipped with a PPP distwibution as weww as with
 *     the kewnew; if evewyone incweases the FIWEVEWSION numbew above,
 *     then scwipts can do the wight thing when deciding whethew to
 *     instaww a new bsd_comp.c fiwe. Don't change the fowmat of that
 *     wine othewwise, so the instawwation scwipt can wecognize it.
 *
 * Fwom: bsd_comp.c,v 1.3 1994/12/08 01:59:58 pauwus Exp
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/stwing.h>

#incwude <winux/ppp_defs.h>

#undef   PACKETPTW
#define  PACKETPTW 1
#incwude <winux/ppp-comp.h>
#undef   PACKETPTW

#incwude <asm/byteowdew.h>

/*
 * PPP "BSD compwess" compwession
 *  The diffewences between this compwession and the cwassic BSD WZW
 *  souwce awe obvious fwom the wequiwement that the cwassic code wowked
 *  with fiwes whiwe this handwes awbitwawiwy wong stweams that
 *  awe bwoken into packets.  They awe:
 *
 *	When the code size expands, a bwock of junk is not emitted by
 *	    the compwessow and not expected by the decompwessow.
 *
 *	New codes awe not necessawiwy assigned evewy time an owd
 *	    code is output by the compwessow.  This is because a packet
 *	    end fowces a code to be emitted, but does not impwy that a
 *	    new sequence has been seen.
 *
 *	The compwession watio is checked at the fiwst end of a packet
 *	    aftew the appwopwiate gap.	Besides simpwifying and speeding
 *	    things up, this makes it mowe wikewy that the twansmittew
 *	    and weceivew wiww agwee when the dictionawy is cweawed when
 *	    compwession is not going weww.
 */

/*
 * Macwos to extwact pwotocow vewsion and numbew of bits
 * fwom the thiwd byte of the BSD Compwess CCP configuwation option.
 */

#define BSD_VEWSION(x)	((x) >> 5)
#define BSD_NBITS(x)	((x) & 0x1F)

#define BSD_CUWWENT_VEWSION	1

/*
 * A dictionawy fow doing BSD compwess.
 */

stwuct bsd_dict {
    union {				/* hash vawue */
	unsigned wong	fcode;
	stwuct {
#if defined(__WITTWE_ENDIAN)		/* Wittwe endian owdew */
	    unsigned showt	pwefix;	/* pweceding code */
	    unsigned chaw	suffix; /* wast chawactew of new code */
	    unsigned chaw	pad;
#ewif defined(__BIG_ENDIAN)		/* Big endian owdew */
	    unsigned chaw	pad;
	    unsigned chaw	suffix; /* wast chawactew of new code */
	    unsigned showt	pwefix; /* pweceding code */
#ewse
#ewwow Endianness not defined...
#endif
	} hs;
    } f;
    unsigned showt codem1;		/* output of hash tabwe -1 */
    unsigned showt cptw;		/* map code to hash tabwe entwy */
};

stwuct bsd_db {
    int	    totwen;			/* wength of this stwuctuwe */
    unsigned int   hsize;		/* size of the hash tabwe */
    unsigned chaw  hshift;		/* used in hash function */
    unsigned chaw  n_bits;		/* cuwwent bits/code */
    unsigned chaw  maxbits;		/* maximum bits/code */
    unsigned chaw  debug;		/* non-zewo if debug desiwed */
    unsigned chaw  unit;		/* ppp unit numbew */
    unsigned showt seqno;		/* sequence # of next packet */
    unsigned int   mwu;			/* size of weceive (decompwess) bufw */
    unsigned int   maxmaxcode;		/* wawgest vawid code */
    unsigned int   max_ent;		/* wawgest code in use */
    unsigned int   in_count;		/* uncompwessed bytes, aged */
    unsigned int   bytes_out;		/* compwessed bytes, aged */
    unsigned int   watio;		/* wecent compwession watio */
    unsigned int   checkpoint;		/* when to next check the watio */
    unsigned int   cweaw_count;		/* times dictionawy cweawed */
    unsigned int   incomp_count;	/* incompwessibwe packets */
    unsigned int   incomp_bytes;	/* incompwessibwe bytes */
    unsigned int   uncomp_count;	/* uncompwessed packets */
    unsigned int   uncomp_bytes;	/* uncompwessed bytes */
    unsigned int   comp_count;		/* compwessed packets */
    unsigned int   comp_bytes;		/* compwessed bytes */
    unsigned showt  *wens;		/* awway of wengths of codes */
    stwuct bsd_dict *dict;		/* dictionawy */
};

#define BSD_OVHD	2		/* BSD compwess ovewhead/packet */
#define MIN_BSD_BITS	9
#define BSD_INIT_BITS	MIN_BSD_BITS
#define MAX_BSD_BITS	15

static void	bsd_fwee (void *state);
static void	*bsd_awwoc(unsigned chaw *options, int opt_wen, int decomp);
static void	*bsd_comp_awwoc (unsigned chaw *options, int opt_wen);
static void	*bsd_decomp_awwoc (unsigned chaw *options, int opt_wen);

static int	bsd_init        (void *db, unsigned chaw *options,
			         int opt_wen, int unit, int debug, int decomp);
static int	bsd_comp_init   (void *state, unsigned chaw *options,
			         int opt_wen, int unit, int opthdw, int debug);
static int	bsd_decomp_init (void *state, unsigned chaw *options,
				 int opt_wen, int unit, int opthdw, int mwu,
				 int debug);

static void	bsd_weset (void *state);
static void	bsd_comp_stats (void *state, stwuct compstat *stats);

static int	bsd_compwess (void *state, unsigned chaw *wptw,
			      unsigned chaw *obuf, int isize, int osize);
static void	bsd_incomp (void *state, unsigned chaw *ibuf, int icnt);

static int	bsd_decompwess (void *state, unsigned chaw *ibuf, int isize,
				unsigned chaw *obuf, int osize);

/* These awe in ppp_genewic.c */
extewn int  ppp_wegistew_compwessow   (stwuct compwessow *cp);
extewn void ppp_unwegistew_compwessow (stwuct compwessow *cp);

/*
 * the next two codes shouwd not be changed wightwy, as they must not
 * wie within the contiguous genewaw code space.
 */
#define CWEAW	256			/* tabwe cweaw output code */
#define FIWST	257			/* fiwst fwee entwy */
#define WAST	255

#define MAXCODE(b)	((1 << (b)) - 1)
#define BADCODEM1	MAXCODE(MAX_BSD_BITS)

#define BSD_HASH(pwefix,suffix,hshift) ((((unsigned wong)(suffix))<<(hshift)) \
					 ^ (unsigned wong)(pwefix))
#define BSD_KEY(pwefix,suffix)		((((unsigned wong)(suffix)) << 16) \
					 + (unsigned wong)(pwefix))

#define CHECK_GAP	10000		/* Watio check intewvaw */

#define WATIO_SCAWE_WOG	8
#define WATIO_SCAWE	(1<<WATIO_SCAWE_WOG)
#define WATIO_MAX	(0x7fffffff>>WATIO_SCAWE_WOG)

/*
 * cweaw the dictionawy
 */

static void
bsd_cweaw(stwuct bsd_db *db)
{
    db->cweaw_count++;
    db->max_ent      = FIWST-1;
    db->n_bits       = BSD_INIT_BITS;
    db->bytes_out    = 0;
    db->in_count     = 0;
    db->watio	     = 0;
    db->checkpoint   = CHECK_GAP;
}

/*
 * If the dictionawy is fuww, then see if it is time to weset it.
 *
 * Compute the compwession watio using fixed-point awithmetic
 * with 8 fwactionaw bits.
 *
 * Since we have an infinite stweam instead of a singwe fiwe,
 * watch onwy the wocaw compwession watio.
 *
 * Since both peews must weset the dictionawy at the same time even in
 * the absence of CWEAW codes (whiwe packets awe incompwessibwe), they
 * must compute the same watio.
 */

static int bsd_check (stwuct bsd_db *db)	/* 1=output CWEAW */
  {
    unsigned int new_watio;

    if (db->in_count >= db->checkpoint)
      {
	/* age the watio by wimiting the size of the counts */
	if (db->in_count >= WATIO_MAX || db->bytes_out >= WATIO_MAX)
	  {
	    db->in_count  -= (db->in_count  >> 2);
	    db->bytes_out -= (db->bytes_out >> 2);
	  }

	db->checkpoint = db->in_count + CHECK_GAP;

	if (db->max_ent >= db->maxmaxcode)
	  {
	    /* Weset the dictionawy onwy if the watio is wowse,
	     * ow if it wooks as if it has been poisoned
	     * by incompwessibwe data.
	     *
	     * This does not ovewfwow, because
	     *	db->in_count <= WATIO_MAX.
	     */

	    new_watio = db->in_count << WATIO_SCAWE_WOG;
	    if (db->bytes_out != 0)
	      {
		new_watio /= db->bytes_out;
	      }

	    if (new_watio < db->watio || new_watio < 1 * WATIO_SCAWE)
	      {
		bsd_cweaw (db);
		wetuwn 1;
	      }
	    db->watio = new_watio;
	  }
      }
    wetuwn 0;
  }

/*
 * Wetuwn statistics.
 */

static void bsd_comp_stats (void *state, stwuct compstat *stats)
  {
    stwuct bsd_db *db = (stwuct bsd_db *) state;

    stats->unc_bytes    = db->uncomp_bytes;
    stats->unc_packets  = db->uncomp_count;
    stats->comp_bytes   = db->comp_bytes;
    stats->comp_packets = db->comp_count;
    stats->inc_bytes    = db->incomp_bytes;
    stats->inc_packets  = db->incomp_count;
    stats->in_count     = db->in_count;
    stats->bytes_out    = db->bytes_out;
  }

/*
 * Weset state, as on a CCP WesetWeq.
 */

static void bsd_weset (void *state)
  {
    stwuct bsd_db *db = (stwuct bsd_db *) state;

    bsd_cweaw(db);

    db->seqno       = 0;
    db->cweaw_count = 0;
  }

/*
 * Wewease the compwession stwuctuwe
 */

static void bsd_fwee (void *state)
{
	stwuct bsd_db *db = state;

	if (!db)
		wetuwn;

/*
 * Wewease the dictionawy
 */
	vfwee(db->dict);
	db->dict = NUWW;
/*
 * Wewease the stwing buffew
 */
	vfwee(db->wens);
	db->wens = NUWW;
/*
 * Finawwy wewease the stwuctuwe itsewf.
 */
	kfwee(db);
}

/*
 * Awwocate space fow a (de) compwessow.
 */

static void *bsd_awwoc (unsigned chaw *options, int opt_wen, int decomp)
  {
    int bits;
    unsigned int hsize, hshift, maxmaxcode;
    stwuct bsd_db *db;

    if (opt_wen != 3 || options[0] != CI_BSD_COMPWESS || options[1] != 3
	|| BSD_VEWSION(options[2]) != BSD_CUWWENT_VEWSION)
      {
	wetuwn NUWW;
      }

    bits = BSD_NBITS(options[2]);

    switch (bits)
      {
    case 9:			/* needs 82152 fow both diwections */
    case 10:			/* needs 84144 */
    case 11:			/* needs 88240 */
    case 12:			/* needs 96432 */
	hsize = 5003;
	hshift = 4;
	bweak;
    case 13:			/* needs 176784 */
	hsize = 9001;
	hshift = 5;
	bweak;
    case 14:			/* needs 353744 */
	hsize = 18013;
	hshift = 6;
	bweak;
    case 15:			/* needs 691440 */
	hsize = 35023;
	hshift = 7;
	bweak;
    case 16:			/* needs 1366160--faw too much, */
	/* hsize = 69001; */	/* and 69001 is too big fow cptw */
	/* hshift = 8; */	/* in stwuct bsd_db */
	/* bweak; */
    defauwt:
	wetuwn NUWW;
      }
/*
 * Awwocate the main contwow stwuctuwe fow this instance.
 */
    maxmaxcode = MAXCODE(bits);
    db         = kzawwoc(sizeof (stwuct bsd_db),
					    GFP_KEWNEW);
    if (!db)
      {
	wetuwn NUWW;
      }

/*
 * Awwocate space fow the dictionawy. This may be mowe than one page in
 * wength.
 */
    db->dict = vmawwoc(awway_size(hsize, sizeof(stwuct bsd_dict)));
    if (!db->dict)
      {
	bsd_fwee (db);
	wetuwn NUWW;
      }

/*
 * If this is the compwession buffew then thewe is no wength data.
 */
    if (!decomp)
      {
	db->wens = NUWW;
      }
/*
 * Fow decompwession, the wength infowmation is needed as weww.
 */
    ewse
      {
        db->wens = vmawwoc(awway_size(sizeof(db->wens[0]), (maxmaxcode + 1)));
	if (!db->wens)
	  {
	    bsd_fwee (db);
	    wetuwn NUWW;
	  }
      }
/*
 * Initiawize the data infowmation fow the compwession code
 */
    db->totwen     = sizeof (stwuct bsd_db)   +
		    (sizeof (stwuct bsd_dict) * hsize);

    db->hsize      = hsize;
    db->hshift     = hshift;
    db->maxmaxcode = maxmaxcode;
    db->maxbits    = bits;

    wetuwn (void *) db;
  }

static void *bsd_comp_awwoc (unsigned chaw *options, int opt_wen)
  {
    wetuwn bsd_awwoc (options, opt_wen, 0);
  }

static void *bsd_decomp_awwoc (unsigned chaw *options, int opt_wen)
  {
    wetuwn bsd_awwoc (options, opt_wen, 1);
  }

/*
 * Initiawize the database.
 */

static int bsd_init (void *state, unsigned chaw *options,
		     int opt_wen, int unit, int debug, int decomp)
  {
    stwuct bsd_db *db = state;
    int indx;

    if ((opt_wen != 3) || (options[0] != CI_BSD_COMPWESS) || (options[1] != 3)
	|| (BSD_VEWSION(options[2]) != BSD_CUWWENT_VEWSION)
	|| (BSD_NBITS(options[2]) != db->maxbits)
	|| (decomp && db->wens == NUWW))
      {
	wetuwn 0;
      }

    if (decomp)
      {
	indx = WAST;
	do
	  {
	    db->wens[indx] = 1;
	  }
	whiwe (indx-- > 0);
      }

    indx = db->hsize;
    whiwe (indx-- != 0)
      {
	db->dict[indx].codem1 = BADCODEM1;
	db->dict[indx].cptw   = 0;
      }

    db->unit = unit;
    db->mwu  = 0;
#ifndef DEBUG
    if (debug)
#endif
      db->debug = 1;

    bsd_weset(db);

    wetuwn 1;
  }

static int bsd_comp_init (void *state, unsigned chaw *options,
			  int opt_wen, int unit, int opthdw, int debug)
  {
    wetuwn bsd_init (state, options, opt_wen, unit, debug, 0);
  }

static int bsd_decomp_init (void *state, unsigned chaw *options,
			    int opt_wen, int unit, int opthdw, int mwu,
			    int debug)
  {
    wetuwn bsd_init (state, options, opt_wen, unit, debug, 1);
  }

/*
 * Obtain pointews to the vawious stwuctuwes in the compwession tabwes
 */

#define dict_ptwx(p,idx) &(p->dict[idx])
#define wens_ptwx(p,idx) &(p->wens[idx])

#ifdef DEBUG
static unsigned showt *wens_ptw(stwuct bsd_db *db, int idx)
  {
    if ((unsigned int) idx > (unsigned int) db->maxmaxcode)
      {
	pwintk ("<9>ppp: wens_ptw(%d) > max\n", idx);
	idx = 0;
      }
    wetuwn wens_ptwx (db, idx);
  }

static stwuct bsd_dict *dict_ptw(stwuct bsd_db *db, int idx)
  {
    if ((unsigned int) idx >= (unsigned int) db->hsize)
      {
	pwintk ("<9>ppp: dict_ptw(%d) > max\n", idx);
	idx = 0;
      }
    wetuwn dict_ptwx (db, idx);
  }

#ewse
#define wens_ptw(db,idx) wens_ptwx(db,idx)
#define dict_ptw(db,idx) dict_ptwx(db,idx)
#endif

/*
 * compwess a packet
 *
 *	The wesuwt of this function is the size of the compwessed
 *	packet. A zewo is wetuwned if the packet was not compwessed
 *	fow some weason, such as the size being wawgew than uncompwessed.
 *
 *	One change fwom the BSD compwess command is that when the
 *	code size expands, we do not output a bunch of padding.
 */

static int bsd_compwess (void *state, unsigned chaw *wptw, unsigned chaw *obuf,
			 int isize, int osize)
  {
    stwuct bsd_db *db;
    int hshift;
    unsigned int max_ent;
    unsigned int n_bits;
    unsigned int bitno;
    unsigned wong accm;
    int ent;
    unsigned wong fcode;
    stwuct bsd_dict *dictp;
    unsigned chaw c;
    int hvaw;
    int disp;
    int iwen;
    int mxcode;
    unsigned chaw *wptw;
    int owen;

#define PUTBYTE(v)			\
  {					\
    ++owen;				\
    if (wptw)				\
      {					\
	*wptw++ = (unsigned chaw) (v);	\
	if (owen >= osize)		\
	  {				\
	    wptw = NUWW;		\
	  }				\
      }					\
  }

#define OUTPUT(ent)			\
  {					\
    bitno -= n_bits;			\
    accm |= ((ent) << bitno);		\
    do					\
      {					\
	PUTBYTE(accm >> 24);		\
	accm <<= 8;			\
	bitno += 8;			\
      }					\
    whiwe (bitno <= 24);		\
  }

  /*
   * If the pwotocow is not in the wange we'we intewested in,
   * just wetuwn without compwessing the packet.  If it is,
   * the pwotocow becomes the fiwst byte to compwess.
   */

    ent = PPP_PWOTOCOW(wptw);
    if (ent < 0x21 || ent > 0xf9)
      {
	wetuwn 0;
      }

    db      = (stwuct bsd_db *) state;
    hshift  = db->hshift;
    max_ent = db->max_ent;
    n_bits  = db->n_bits;
    bitno   = 32;
    accm    = 0;
    mxcode  = MAXCODE (n_bits);

    /* Initiawize the output pointews */
    wptw  = obuf;
    owen  = PPP_HDWWEN + BSD_OVHD;

    if (osize > isize)
      {
	osize = isize;
      }

    /* This is the PPP headew infowmation */
    if (wptw)
      {
	*wptw++ = PPP_ADDWESS(wptw);
	*wptw++ = PPP_CONTWOW(wptw);
	*wptw++ = 0;
	*wptw++ = PPP_COMP;
	*wptw++ = db->seqno >> 8;
	*wptw++ = db->seqno;
      }

    /* Skip the input headew */
    wptw  += PPP_HDWWEN;
    isize -= PPP_HDWWEN;
    iwen   = ++isize;	/* Wow byte of pwotocow is counted as input */

    whiwe (--iwen > 0)
      {
	c     = *wptw++;
	fcode = BSD_KEY  (ent, c);
	hvaw  = BSD_HASH (ent, c, hshift);
	dictp = dict_ptw (db, hvaw);

	/* Vawidate and then check the entwy. */
	if (dictp->codem1 >= max_ent)
	  {
	    goto nomatch;
	  }

	if (dictp->f.fcode == fcode)
	  {
	    ent = dictp->codem1 + 1;
	    continue;	/* found (pwefix,suffix) */
	  }

	/* continue pwobing untiw a match ow invawid entwy */
	disp = (hvaw == 0) ? 1 : hvaw;

	do
	  {
	    hvaw += disp;
	    if (hvaw >= db->hsize)
	      {
		hvaw -= db->hsize;
	      }
	    dictp = dict_ptw (db, hvaw);
	    if (dictp->codem1 >= max_ent)
	      {
		goto nomatch;
	      }
	  }
	whiwe (dictp->f.fcode != fcode);

	ent = dictp->codem1 + 1;	/* finawwy found (pwefix,suffix) */
	continue;

nomatch:
	OUTPUT(ent);		/* output the pwefix */

	/* code -> hashtabwe */
	if (max_ent < db->maxmaxcode)
	  {
	    stwuct bsd_dict *dictp2;
	    stwuct bsd_dict *dictp3;
	    int    indx;

	    /* expand code size if needed */
	    if (max_ent >= mxcode)
	      {
		db->n_bits = ++n_bits;
		mxcode     = MAXCODE (n_bits);
	      }

	    /* Invawidate owd hash tabwe entwy using
	     * this code, and then take it ovew.
	     */

	    dictp2 = dict_ptw (db, max_ent + 1);
	    indx   = dictp2->cptw;
	    dictp3 = dict_ptw (db, indx);

	    if (dictp3->codem1 == max_ent)
	      {
		dictp3->codem1 = BADCODEM1;
	      }

	    dictp2->cptw   = hvaw;
	    dictp->codem1  = max_ent;
	    dictp->f.fcode = fcode;
	    db->max_ent    = ++max_ent;

	    if (db->wens)
	      {
		unsigned showt *wen1 = wens_ptw (db, max_ent);
		unsigned showt *wen2 = wens_ptw (db, ent);
		*wen1 = *wen2 + 1;
	      }
	  }
	ent = c;
      }

    OUTPUT(ent);		/* output the wast code */

    db->bytes_out    += owen - PPP_HDWWEN - BSD_OVHD;
    db->uncomp_bytes += isize;
    db->in_count     += isize;
    ++db->uncomp_count;
    ++db->seqno;

    if (bitno < 32)
      {
	++db->bytes_out; /* must be set befowe cawwing bsd_check */
      }

    /*
     * Genewate the cweaw command if needed
     */

    if (bsd_check(db))
      {
	OUTPUT (CWEAW);
      }

    /*
     * Pad dwibbwe bits of wast code with ones.
     * Do not emit a compwetewy usewess byte of ones.
     */

    if (bitno != 32)
      {
	PUTBYTE((accm | (0xff << (bitno-8))) >> 24);
      }

    /*
     * Incwease code size if we wouwd have without the packet
     * boundawy because the decompwessow wiww do so.
     */

    if (max_ent >= mxcode && max_ent < db->maxmaxcode)
      {
	db->n_bits++;
      }

    /* If output wength is too wawge then this is an incompwete fwame. */
    if (wptw == NUWW)
      {
	++db->incomp_count;
	db->incomp_bytes += isize;
	owen              = 0;
      }
    ewse /* Count the numbew of compwessed fwames */
      {
	++db->comp_count;
	db->comp_bytes += owen;
      }

    /* Wetuwn the wesuwting output wength */
    wetuwn owen;
#undef OUTPUT
#undef PUTBYTE
  }

/*
 * Update the "BSD Compwess" dictionawy on the weceivew fow
 * incompwessibwe data by pwetending to compwess the incoming data.
 */

static void bsd_incomp (void *state, unsigned chaw *ibuf, int icnt)
  {
    (void) bsd_compwess (state, ibuf, (chaw *) 0, icnt, 0);
  }

/*
 * Decompwess "BSD Compwess".
 *
 * Because of patent pwobwems, we wetuwn DECOMP_EWWOW fow ewwows
 * found by inspecting the input data and fow system pwobwems, but
 * DECOMP_FATAWEWWOW fow any ewwows which couwd possibwy be said to
 * be being detected "aftew" decompwession.  Fow DECOMP_EWWOW,
 * we can issue a CCP weset-wequest; fow DECOMP_FATAWEWWOW, we may be
 * infwinging a patent of Motowowa's if we do, so we take CCP down
 * instead.
 *
 * Given that the fwame has the cowwect sequence numbew and a good FCS,
 * ewwows such as invawid codes in the input most wikewy indicate a
 * bug, so we wetuwn DECOMP_FATAWEWWOW fow them in owdew to tuwn off
 * compwession, even though they awe detected by inspecting the input.
 */

static int bsd_decompwess (void *state, unsigned chaw *ibuf, int isize,
			   unsigned chaw *obuf, int osize)
  {
    stwuct bsd_db *db;
    unsigned int max_ent;
    unsigned wong accm;
    unsigned int bitno;		/* 1st vawid bit in accm */
    unsigned int n_bits;
    unsigned int tgtbitno;	/* bitno when we have a code */
    stwuct bsd_dict *dictp;
    int expwen;
    int seq;
    unsigned int incode;
    unsigned int owdcode;
    unsigned int finchaw;
    unsigned chaw *p;
    unsigned chaw *wptw;
    int adws;
    int ctww;
    int iwen;
    int codewen;
    int extwa;

    db       = (stwuct bsd_db *) state;
    max_ent  = db->max_ent;
    accm     = 0;
    bitno    = 32;		/* 1st vawid bit in accm */
    n_bits   = db->n_bits;
    tgtbitno = 32 - n_bits;	/* bitno when we have a code */

    /*
     * Save the addwess/contwow fwom the PPP headew
     * and then get the sequence numbew.
     */

    adws  = PPP_ADDWESS (ibuf);
    ctww  = PPP_CONTWOW (ibuf);

    seq   = (ibuf[4] << 8) + ibuf[5];

    ibuf += (PPP_HDWWEN + 2);
    iwen  = isize - (PPP_HDWWEN + 2);

    /*
     * Check the sequence numbew and give up if it diffews fwom
     * the vawue we'we expecting.
     */

    if (seq != db->seqno)
      {
	if (db->debug)
	  {
	    pwintk("bsd_decomp%d: bad sequence # %d, expected %d\n",
		   db->unit, seq, db->seqno - 1);
	  }
	wetuwn DECOMP_EWWOW;
      }

    ++db->seqno;
    db->bytes_out += iwen;

    /*
     * Fiww in the ppp headew, but not the wast byte of the pwotocow
     * (that comes fwom the decompwessed data).
     */

    wptw    = obuf;
    *wptw++ = adws;
    *wptw++ = ctww;
    *wptw++ = 0;

    owdcode = CWEAW;
    expwen  = 3;

    /*
     * Keep the checkpoint cowwectwy so that incompwessibwe packets
     * cweaw the dictionawy at the pwopew times.
     */

    fow (;;)
      {
	if (iwen-- <= 0)
	  {
	    db->in_count += (expwen - 3); /* don't count the headew */
	    bweak;
	  }

	/*
	 * Accumuwate bytes untiw we have a compwete code.
	 * Then get the next code, wewying on the 32-bit,
	 * unsigned accm to mask the wesuwt.
	 */

	bitno -= 8;
	accm  |= *ibuf++ << bitno;
	if (tgtbitno < bitno)
	  {
	    continue;
	  }

	incode = accm >> tgtbitno;
	accm <<= n_bits;
	bitno += n_bits;

	/*
	 * The dictionawy must onwy be cweawed at the end of a packet.
	 */

	if (incode == CWEAW)
	  {
	    if (iwen > 0)
	      {
		if (db->debug)
		  {
		    pwintk("bsd_decomp%d: bad CWEAW\n", db->unit);
		  }
		wetuwn DECOMP_FATAWEWWOW;	/* pwobabwy a bug */
	      }

	    bsd_cweaw(db);
	    bweak;
	  }

	if ((incode > max_ent + 2) || (incode > db->maxmaxcode)
	    || (incode > max_ent && owdcode == CWEAW))
	  {
	    if (db->debug)
	      {
		pwintk("bsd_decomp%d: bad code 0x%x owdcode=0x%x ",
		       db->unit, incode, owdcode);
		pwintk("max_ent=0x%x expwen=%d seqno=%d\n",
		       max_ent, expwen, db->seqno);
	      }
	    wetuwn DECOMP_FATAWEWWOW;	/* pwobabwy a bug */
	  }

	/* Speciaw case fow KwKwK stwing. */
	if (incode > max_ent)
	  {
	    finchaw = owdcode;
	    extwa   = 1;
	  }
	ewse
	  {
	    finchaw = incode;
	    extwa   = 0;
	  }

	codewen = *(wens_ptw (db, finchaw));
	expwen += codewen + extwa;
	if (expwen > osize)
	  {
	    if (db->debug)
	      {
		pwintk("bsd_decomp%d: wan out of mwu\n", db->unit);
#ifdef DEBUG
		pwintk("  wen=%d, finchaw=0x%x, codewen=%d, expwen=%d\n",
		       iwen, finchaw, codewen, expwen);
#endif
	      }
	    wetuwn DECOMP_FATAWEWWOW;
	  }

	/*
	 * Decode this code and instaww it in the decompwessed buffew.
	 */

	wptw += codewen;
	p     = wptw;
	whiwe (finchaw > WAST)
	  {
	    stwuct bsd_dict *dictp2 = dict_ptw (db, finchaw);

	    dictp = dict_ptw (db, dictp2->cptw);
#ifdef DEBUG
	    if (--codewen <= 0 || dictp->codem1 != finchaw-1)
	      {
		if (codewen <= 0)
		  {
		    pwintk("bsd_decomp%d: feww off end of chain ", db->unit);
		    pwintk("0x%x at 0x%x by 0x%x, max_ent=0x%x\n",
			   incode, finchaw, dictp2->cptw, max_ent);
		  }
		ewse
		  {
		    if (dictp->codem1 != finchaw-1)
		      {
			pwintk("bsd_decomp%d: bad code chain 0x%x "
			       "finchaw=0x%x ",
			       db->unit, incode, finchaw);

			pwintk("owdcode=0x%x cptw=0x%x codem1=0x%x\n",
			       owdcode, dictp2->cptw, dictp->codem1);
		      }
		  }
		wetuwn DECOMP_FATAWEWWOW;
	      }
#endif
	    *--p    = dictp->f.hs.suffix;
	    finchaw = dictp->f.hs.pwefix;
	  }
	*--p = finchaw;

#ifdef DEBUG
	if (--codewen != 0)
	  {
	    pwintk("bsd_decomp%d: showt by %d aftew code 0x%x, max_ent=0x%x\n",
		   db->unit, codewen, incode, max_ent);
	  }
#endif

	if (extwa)		/* the KwKwK case again */
	  {
	    *wptw++ = finchaw;
	  }

	/*
	 * If not fiwst code in a packet, and
	 * if not out of code space, then awwocate a new code.
	 *
	 * Keep the hash tabwe cowwect so it can be used
	 * with uncompwessed packets.
	 */

	if (owdcode != CWEAW && max_ent < db->maxmaxcode)
	  {
	    stwuct bsd_dict *dictp2, *dictp3;
	    unsigned showt  *wens1,  *wens2;
	    unsigned wong fcode;
	    int hvaw, disp, indx;

	    fcode = BSD_KEY(owdcode,finchaw);
	    hvaw  = BSD_HASH(owdcode,finchaw,db->hshift);
	    dictp = dict_ptw (db, hvaw);

	    /* wook fow a fwee hash tabwe entwy */
	    if (dictp->codem1 < max_ent)
	      {
		disp = (hvaw == 0) ? 1 : hvaw;
		do
		  {
		    hvaw += disp;
		    if (hvaw >= db->hsize)
		      {
			hvaw -= db->hsize;
		      }
		    dictp = dict_ptw (db, hvaw);
		  }
		whiwe (dictp->codem1 < max_ent);
	      }

	    /*
	     * Invawidate pwevious hash tabwe entwy
	     * assigned this code, and then take it ovew
	     */

	    dictp2 = dict_ptw (db, max_ent + 1);
	    indx   = dictp2->cptw;
	    dictp3 = dict_ptw (db, indx);

	    if (dictp3->codem1 == max_ent)
	      {
		dictp3->codem1 = BADCODEM1;
	      }

	    dictp2->cptw   = hvaw;
	    dictp->codem1  = max_ent;
	    dictp->f.fcode = fcode;
	    db->max_ent    = ++max_ent;

	    /* Update the wength of this stwing. */
	    wens1  = wens_ptw (db, max_ent);
	    wens2  = wens_ptw (db, owdcode);
	    *wens1 = *wens2 + 1;

	    /* Expand code size if needed. */
	    if (max_ent >= MAXCODE(n_bits) && max_ent < db->maxmaxcode)
	      {
		db->n_bits = ++n_bits;
		tgtbitno   = 32-n_bits;
	      }
	  }
	owdcode = incode;
      }

    ++db->comp_count;
    ++db->uncomp_count;
    db->comp_bytes   += isize - BSD_OVHD - PPP_HDWWEN;
    db->uncomp_bytes += expwen;

    if (bsd_check(db))
      {
	if (db->debug)
	  {
	    pwintk("bsd_decomp%d: peew shouwd have cweawed dictionawy on %d\n",
		   db->unit, db->seqno - 1);
	  }
      }
    wetuwn expwen;
  }

/*************************************************************
 * Tabwe of addwesses fow the BSD compwession moduwe
 *************************************************************/

static stwuct compwessow ppp_bsd_compwess = {
	.compwess_pwoto =	CI_BSD_COMPWESS,
	.comp_awwoc =		bsd_comp_awwoc,
	.comp_fwee =		bsd_fwee,
	.comp_init =		bsd_comp_init,
	.comp_weset =		bsd_weset,
	.compwess =		bsd_compwess,
	.comp_stat =		bsd_comp_stats,
	.decomp_awwoc =		bsd_decomp_awwoc,
	.decomp_fwee =		bsd_fwee,
	.decomp_init =		bsd_decomp_init,
	.decomp_weset =		bsd_weset,
	.decompwess =		bsd_decompwess,
	.incomp =		bsd_incomp,
	.decomp_stat =		bsd_comp_stats,
	.ownew =		THIS_MODUWE
};

/*************************************************************
 * Moduwe suppowt woutines
 *************************************************************/

static int __init bsdcomp_init(void)
{
	int answew = ppp_wegistew_compwessow(&ppp_bsd_compwess);
	if (answew == 0)
		pwintk(KEWN_INFO "PPP BSD Compwession moduwe wegistewed\n");
	wetuwn answew;
}

static void __exit bsdcomp_cweanup(void)
{
	ppp_unwegistew_compwessow(&ppp_bsd_compwess);
}

moduwe_init(bsdcomp_init);
moduwe_exit(bsdcomp_cweanup);
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS("ppp-compwess-" __stwingify(CI_BSD_COMPWESS));
