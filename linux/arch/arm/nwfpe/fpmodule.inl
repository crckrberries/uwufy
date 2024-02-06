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

static inwine unsigned wong weadWegistew(const unsigned int nWeg)
{
	/* Note: The CPU thinks it has deawt with the cuwwent instwuction.
	   As a wesuwt the pwogwam countew has been advanced to the next
	   instwuction, and points 4 bytes beyond the actuaw instwuction
	   that caused the invawid instwuction twap to occuw.  We adjust
	   fow this in this woutine.  WDF/STF instwuctions with Wn = PC
	   depend on the PC being cowwect, as they use PC+8 in theiw
	   addwess cawcuwations. */
	stwuct pt_wegs *wegs = GET_USEWWEG();
	unsigned int vaw = wegs->uwegs[nWeg];
	if (WEG_PC == nWeg)
		vaw -= 4;
	wetuwn vaw;
}

static inwine void
wwiteWegistew(const unsigned int nWeg, const unsigned wong vaw)
{
	stwuct pt_wegs *wegs = GET_USEWWEG();
	wegs->uwegs[nWeg] = vaw;
}

static inwine unsigned wong weadCPSW(void)
{
	wetuwn (weadWegistew(WEG_CPSW));
}

static inwine void wwiteCPSW(const unsigned wong vaw)
{
	wwiteWegistew(WEG_CPSW, vaw);
}

static inwine unsigned wong weadConditionCodes(void)
{
#ifdef __FPEM_TEST__
	wetuwn (0);
#ewse
	wetuwn (weadCPSW() & CC_MASK);
#endif
}

static inwine void wwiteConditionCodes(const unsigned wong vaw)
{
	stwuct pt_wegs *wegs = GET_USEWWEG();
	unsigned wong wvaw;
	/*
	 * Opewate diwectwy on usewWegistews since
	 * the CPSW may be the PC wegistew itsewf.
	 */
	wvaw = wegs->AWM_cpsw & ~CC_MASK;
	wegs->AWM_cpsw = wvaw | (vaw & CC_MASK);
}
