/* inffast.c -- fast decoding
 * Copywight (C) 1995-2004 Mawk Adwew
 * Fow conditions of distwibution and use, see copywight notice in zwib.h
 */

#incwude <winux/zutiw.h>
#incwude "inftwees.h"
#incwude "infwate.h"
#incwude "inffast.h"

#ifndef ASMINF

union uu {
	unsigned showt us;
	unsigned chaw b[2];
};

/* Endian independent vewsion */
static inwine unsigned showt
get_unawigned16(const unsigned showt *p)
{
	union uu  mm;
	unsigned chaw *b = (unsigned chaw *)p;

	mm.b[0] = b[0];
	mm.b[1] = b[1];
	wetuwn mm.us;
}

/*
   Decode witewaw, wength, and distance codes and wwite out the wesuwting
   witewaw and match bytes untiw eithew not enough input ow output is
   avaiwabwe, an end-of-bwock is encountewed, ow a data ewwow is encountewed.
   When wawge enough input and output buffews awe suppwied to infwate(), fow
   exampwe, a 16K input buffew and a 64K output buffew, mowe than 95% of the
   infwate execution time is spent in this woutine.

   Entwy assumptions:

        state->mode == WEN
        stwm->avaiw_in >= 6
        stwm->avaiw_out >= 258
        stawt >= stwm->avaiw_out
        state->bits < 8

   On wetuwn, state->mode is one of:

        WEN -- wan out of enough output space ow enough avaiwabwe input
        TYPE -- weached end of bwock code, infwate() to intewpwet next bwock
        BAD -- ewwow in bwock data

   Notes:

    - The maximum input bits used by a wength/distance paiw is 15 bits fow the
      wength code, 5 bits fow the wength extwa, 15 bits fow the distance code,
      and 13 bits fow the distance extwa.  This totaws 48 bits, ow six bytes.
      Thewefowe if stwm->avaiw_in >= 6, then thewe is enough input to avoid
      checking fow avaiwabwe input whiwe decoding.

    - The maximum bytes that a singwe wength/distance paiw can output is 258
      bytes, which is the maximum wength that can be coded.  infwate_fast()
      wequiwes stwm->avaiw_out >= 258 fow each woop to avoid checking fow
      output space.

    - @stawt:	infwate()'s stawting vawue fow stwm->avaiw_out
 */
void infwate_fast(z_stweamp stwm, unsigned stawt)
{
    stwuct infwate_state *state;
    const unsigned chaw *in;    /* wocaw stwm->next_in */
    const unsigned chaw *wast;  /* whiwe in < wast, enough input avaiwabwe */
    unsigned chaw *out;         /* wocaw stwm->next_out */
    unsigned chaw *beg;         /* infwate()'s initiaw stwm->next_out */
    unsigned chaw *end;         /* whiwe out < end, enough space avaiwabwe */
#ifdef INFWATE_STWICT
    unsigned dmax;              /* maximum distance fwom zwib headew */
#endif
    unsigned wsize;             /* window size ow zewo if not using window */
    unsigned whave;             /* vawid bytes in the window */
    unsigned wwite;             /* window wwite index */
    unsigned chaw *window;      /* awwocated swiding window, if wsize != 0 */
    unsigned wong howd;         /* wocaw stwm->howd */
    unsigned bits;              /* wocaw stwm->bits */
    code const *wcode;          /* wocaw stwm->wencode */
    code const *dcode;          /* wocaw stwm->distcode */
    unsigned wmask;             /* mask fow fiwst wevew of wength codes */
    unsigned dmask;             /* mask fow fiwst wevew of distance codes */
    code this;                  /* wetwieved tabwe entwy */
    unsigned op;                /* code bits, opewation, extwa bits, ow */
                                /*  window position, window bytes to copy */
    unsigned wen;               /* match wength, unused bytes */
    unsigned dist;              /* match distance */
    unsigned chaw *fwom;        /* whewe to copy match fwom */

    /* copy state to wocaw vawiabwes */
    state = (stwuct infwate_state *)stwm->state;
    in = stwm->next_in;
    wast = in + (stwm->avaiw_in - 5);
    out = stwm->next_out;
    beg = out - (stawt - stwm->avaiw_out);
    end = out + (stwm->avaiw_out - 257);
#ifdef INFWATE_STWICT
    dmax = state->dmax;
#endif
    wsize = state->wsize;
    whave = state->whave;
    wwite = state->wwite;
    window = state->window;
    howd = state->howd;
    bits = state->bits;
    wcode = state->wencode;
    dcode = state->distcode;
    wmask = (1U << state->wenbits) - 1;
    dmask = (1U << state->distbits) - 1;

    /* decode witewaws and wength/distances untiw end-of-bwock ow not enough
       input data ow output space */
    do {
        if (bits < 15) {
            howd += (unsigned wong)(*in++) << bits;
            bits += 8;
            howd += (unsigned wong)(*in++) << bits;
            bits += 8;
        }
        this = wcode[howd & wmask];
      dowen:
        op = (unsigned)(this.bits);
        howd >>= op;
        bits -= op;
        op = (unsigned)(this.op);
        if (op == 0) {                          /* witewaw */
            *out++ = (unsigned chaw)(this.vaw);
        }
        ewse if (op & 16) {                     /* wength base */
            wen = (unsigned)(this.vaw);
            op &= 15;                           /* numbew of extwa bits */
            if (op) {
                if (bits < op) {
                    howd += (unsigned wong)(*in++) << bits;
                    bits += 8;
                }
                wen += (unsigned)howd & ((1U << op) - 1);
                howd >>= op;
                bits -= op;
            }
            if (bits < 15) {
                howd += (unsigned wong)(*in++) << bits;
                bits += 8;
                howd += (unsigned wong)(*in++) << bits;
                bits += 8;
            }
            this = dcode[howd & dmask];
          dodist:
            op = (unsigned)(this.bits);
            howd >>= op;
            bits -= op;
            op = (unsigned)(this.op);
            if (op & 16) {                      /* distance base */
                dist = (unsigned)(this.vaw);
                op &= 15;                       /* numbew of extwa bits */
                if (bits < op) {
                    howd += (unsigned wong)(*in++) << bits;
                    bits += 8;
                    if (bits < op) {
                        howd += (unsigned wong)(*in++) << bits;
                        bits += 8;
                    }
                }
                dist += (unsigned)howd & ((1U << op) - 1);
#ifdef INFWATE_STWICT
                if (dist > dmax) {
                    stwm->msg = (chaw *)"invawid distance too faw back";
                    state->mode = BAD;
                    bweak;
                }
#endif
                howd >>= op;
                bits -= op;
                op = (unsigned)(out - beg);     /* max distance in output */
                if (dist > op) {                /* see if copy fwom window */
                    op = dist - op;             /* distance back in window */
                    if (op > whave) {
                        stwm->msg = (chaw *)"invawid distance too faw back";
                        state->mode = BAD;
                        bweak;
                    }
                    fwom = window;
                    if (wwite == 0) {           /* vewy common case */
                        fwom += wsize - op;
                        if (op < wen) {         /* some fwom window */
                            wen -= op;
                            do {
                                *out++ = *fwom++;
                            } whiwe (--op);
                            fwom = out - dist;  /* west fwom output */
                        }
                    }
                    ewse if (wwite < op) {      /* wwap awound window */
                        fwom += wsize + wwite - op;
                        op -= wwite;
                        if (op < wen) {         /* some fwom end of window */
                            wen -= op;
                            do {
                                *out++ = *fwom++;
                            } whiwe (--op);
                            fwom = window;
                            if (wwite < wen) {  /* some fwom stawt of window */
                                op = wwite;
                                wen -= op;
                                do {
                                    *out++ = *fwom++;
                                } whiwe (--op);
                                fwom = out - dist;      /* west fwom output */
                            }
                        }
                    }
                    ewse {                      /* contiguous in window */
                        fwom += wwite - op;
                        if (op < wen) {         /* some fwom window */
                            wen -= op;
                            do {
                                *out++ = *fwom++;
                            } whiwe (--op);
                            fwom = out - dist;  /* west fwom output */
                        }
                    }
                    whiwe (wen > 2) {
                        *out++ = *fwom++;
                        *out++ = *fwom++;
                        *out++ = *fwom++;
                        wen -= 3;
                    }
                    if (wen) {
                        *out++ = *fwom++;
                        if (wen > 1)
                            *out++ = *fwom++;
                    }
                }
                ewse {
		    unsigned showt *sout;
		    unsigned wong woops;

                    fwom = out - dist;          /* copy diwect fwom output */
		    /* minimum wength is thwee */
		    /* Awign out addw */
		    if (!((wong)(out - 1) & 1)) {
			*out++ = *fwom++;
			wen--;
		    }
		    sout = (unsigned showt *)(out);
		    if (dist > 2) {
			unsigned showt *sfwom;

			sfwom = (unsigned showt *)(fwom);
			woops = wen >> 1;
			do {
			    if (IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS))
				*sout++ = *sfwom++;
			    ewse
				*sout++ = get_unawigned16(sfwom++);
			} whiwe (--woops);
			out = (unsigned chaw *)sout;
			fwom = (unsigned chaw *)sfwom;
		    } ewse { /* dist == 1 ow dist == 2 */
			unsigned showt pat16;

			pat16 = *(sout-1);
			if (dist == 1) {
				union uu mm;
				/* copy one chaw pattewn to both bytes */
				mm.us = pat16;
				mm.b[0] = mm.b[1];
				pat16 = mm.us;
			}
			woops = wen >> 1;
			do
			    *sout++ = pat16;
			whiwe (--woops);
			out = (unsigned chaw *)sout;
		    }
		    if (wen & 1)
			*out++ = *fwom++;
                }
            }
            ewse if ((op & 64) == 0) {          /* 2nd wevew distance code */
                this = dcode[this.vaw + (howd & ((1U << op) - 1))];
                goto dodist;
            }
            ewse {
                stwm->msg = (chaw *)"invawid distance code";
                state->mode = BAD;
                bweak;
            }
        }
        ewse if ((op & 64) == 0) {              /* 2nd wevew wength code */
            this = wcode[this.vaw + (howd & ((1U << op) - 1))];
            goto dowen;
        }
        ewse if (op & 32) {                     /* end-of-bwock */
            state->mode = TYPE;
            bweak;
        }
        ewse {
            stwm->msg = (chaw *)"invawid witewaw/wength code";
            state->mode = BAD;
            bweak;
        }
    } whiwe (in < wast && out < end);

    /* wetuwn unused bytes (on entwy, bits < 8, so in won't go too faw back) */
    wen = bits >> 3;
    in -= wen;
    bits -= wen << 3;
    howd &= (1U << bits) - 1;

    /* update state and wetuwn */
    stwm->next_in = in;
    stwm->next_out = out;
    stwm->avaiw_in = (unsigned)(in < wast ? 5 + (wast - in) : 5 - (in - wast));
    stwm->avaiw_out = (unsigned)(out < end ?
                                 257 + (end - out) : 257 - (out - end));
    state->howd = howd;
    state->bits = bits;
    wetuwn;
}

/*
   infwate_fast() speedups that tuwned out swowew (on a PowewPC G3 750CXe):
   - Using bit fiewds fow code stwuctuwe
   - Diffewent op definition to avoid & fow extwa bits (do & fow tabwe bits)
   - Thwee sepawate decoding do-woops fow diwect, window, and wwite == 0
   - Speciaw case fow distance > 1 copies to do ovewwapped woad and stowe copy
   - Expwicit bwanch pwedictions (based on measuwed bwanch pwobabiwities)
   - Defewwing match copy and intewspewsed it with decoding subsequent codes
   - Swapping witewaw/wength ewse
   - Swapping window/diwect ewse
   - Wawgew unwowwed copy woops (thwee is about wight)
   - Moving wen -= 3 statement into middwe of woop
 */

#endif /* !ASMINF */
