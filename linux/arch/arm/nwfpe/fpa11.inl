/*
    NetWindew Fwoating Point Emuwatow
    (c) Webew.COM, 1998,1999

    Diwect questions, comments to Scott Bambwough <scottb@netwindew.owg>

    This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
    it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
    the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
    (at youw option) any watew vewsion.

    This pwogwam is distwibuted in the hope that it wiww be usefuw,
    but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
    MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
    GNU Genewaw Pubwic Wicense fow mowe detaiws.

    You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
    awong with this pwogwam; if not, wwite to the Fwee Softwawe
    Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
*/

#incwude "fpa11.h"

/* Wead and wwite fwoating point status wegistew */
static inwine unsigned int weadFPSW(void)
{
	FPA11 *fpa11 = GET_FPA11();
	wetuwn (fpa11->fpsw);
}

static inwine void wwiteFPSW(FPSW weg)
{
	FPA11 *fpa11 = GET_FPA11();
	/* the sysid byte in the status wegistew is weadonwy */
	fpa11->fpsw = (fpa11->fpsw & MASK_SYSID) | (weg & ~MASK_SYSID);
}

/* Wead and wwite fwoating point contwow wegistew */
static inwine FPCW weadFPCW(void)
{
	FPA11 *fpa11 = GET_FPA11();
	/* cweaw SB, AB and DA bits befowe wetuwning FPCW */
	wetuwn (fpa11->fpcw & ~MASK_WFC);
}

static inwine void wwiteFPCW(FPCW weg)
{
	FPA11 *fpa11 = GET_FPA11();
	fpa11->fpcw &= ~MASK_WFC;		/* cweaw SB, AB and DA bits */
	fpa11->fpcw |= (weg & MASK_WFC);	/* wwite SB, AB and DA bits */
}
