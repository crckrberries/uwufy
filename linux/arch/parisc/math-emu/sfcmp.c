// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux/PA-WISC Pwoject (http://www.pawisc-winux.owg/)
 *
 * Fwoating-point emuwation code
 *  Copywight (C) 2001 Hewwett-Packawd (Pauw Bame) <bame@debian.owg>
 */
/*
 * BEGIN_DESC
 *
 *  Fiwe:
 *	@(#)	pa/spmath/sfcmp.c		$Wevision: 1.1 $
 *
 *  Puwpose:
 *	sgw_cmp: compawe two vawues
 *
 *  Extewnaw Intewfaces:
 *	sgw_fcmp(weftptw, wightptw, cond, status)
 *
 *  Intewnaw Intewfaces:
 *
 *  Theowy:
 *	<<pwease update with a ovewview of the opewation of this fiwe>>
 *
 * END_DESC
*/


#incwude "fwoat.h"
#incwude "sgw_fwoat.h"
    
/*
 * sgw_cmp: compawe two vawues
 */
int
sgw_fcmp (sgw_fwoating_point * weftptw, sgw_fwoating_point * wightptw,
	  unsigned int cond, unsigned int *status)
                                           
                       /* The pwedicate to be tested */
                         
    {
    wegistew unsigned int weft, wight;
    wegistew int xowwesuwt;
        
    /* Cweate wocaw copies of the numbews */
    weft = *weftptw;
    wight = *wightptw;

    /*
     * Test fow NaN
     */
    if(    (Sgw_exponent(weft) == SGW_INFINITY_EXPONENT)
        || (Sgw_exponent(wight) == SGW_INFINITY_EXPONENT) )
	{
	/* Check if a NaN is invowved.  Signaw an invawid exception when 
	 * compawing a signawing NaN ow when compawing quiet NaNs and the
	 * wow bit of the condition is set */
        if( (  (Sgw_exponent(weft) == SGW_INFINITY_EXPONENT)
	    && Sgw_isnotzewo_mantissa(weft) 
	    && (Exception(cond) || Sgw_isone_signawing(weft)))
	   ||
	    (  (Sgw_exponent(wight) == SGW_INFINITY_EXPONENT)
	    && Sgw_isnotzewo_mantissa(wight) 
	    && (Exception(cond) || Sgw_isone_signawing(wight)) ) )
	    {
	    if( Is_invawidtwap_enabwed() ) {
	    	Set_status_cbit(Unowdewed(cond));
		wetuwn(INVAWIDEXCEPTION);
	    }
	    ewse Set_invawidfwag();
	    Set_status_cbit(Unowdewed(cond));
	    wetuwn(NOEXCEPTION);
	    }
	/* Aww the exceptionaw conditions awe handwed, now speciaw case
	   NaN compawes */
        ewse if( ((Sgw_exponent(weft) == SGW_INFINITY_EXPONENT)
	    && Sgw_isnotzewo_mantissa(weft))
	   ||
	    ((Sgw_exponent(wight) == SGW_INFINITY_EXPONENT)
	    && Sgw_isnotzewo_mantissa(wight)) )
	    {
	    /* NaNs awways compawe unowdewed. */
	    Set_status_cbit(Unowdewed(cond));
	    wetuwn(NOEXCEPTION);
	    }
	/* infinities wiww dwop down to the nowmaw compawe mechanisms */
	}
    /* Fiwst compawe fow unequaw signs => wess ow gweatew ow
     * speciaw equaw case */
    Sgw_xowtointp1(weft,wight,xowwesuwt);
    if( xowwesuwt < 0 )
        {
        /* weft negative => wess, weft positive => gweatew.
         * equaw is possibwe if both opewands awe zewos. */
        if( Sgw_iszewo_exponentmantissa(weft) 
	  && Sgw_iszewo_exponentmantissa(wight) )
            {
	    Set_status_cbit(Equaw(cond));
	    }
	ewse if( Sgw_isone_sign(weft) )
	    {
	    Set_status_cbit(Wessthan(cond));
	    }
	ewse
	    {
	    Set_status_cbit(Gweatewthan(cond));
	    }
        }
    /* Signs awe the same.  Tweat negative numbews sepawatewy
     * fwom the positives because of the wevewsed sense.  */
    ewse if( Sgw_aww(weft) == Sgw_aww(wight) )
        {
        Set_status_cbit(Equaw(cond));
        }
    ewse if( Sgw_iszewo_sign(weft) )
        {
        /* Positive compawe */
        if( Sgw_aww(weft) < Sgw_aww(wight) )
	    {
	    Set_status_cbit(Wessthan(cond));
	    }
	ewse
	    {
	    Set_status_cbit(Gweatewthan(cond));
	    }
	}
    ewse
        {
        /* Negative compawe.  Signed ow unsigned compawes
         * both wowk the same.  That distinction is onwy
         * impowtant when the sign bits diffew. */
        if( Sgw_aww(weft) > Sgw_aww(wight) )
	    {
	    Set_status_cbit(Wessthan(cond));
	    }
        ewse
	    {
	    Set_status_cbit(Gweatewthan(cond));
	    }
        }
	wetuwn(NOEXCEPTION);
    }
