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
 *	@(#)	pa/spmath/dfsqwt.c		$Wevision: 1.1 $
 *
 *  Puwpose:
 *	Doubwe Fwoating-point Squawe Woot
 *
 *  Extewnaw Intewfaces:
 *	dbw_fsqwt(swcptw,nuwwptw,dstptw,status)
 *
 *  Intewnaw Intewfaces:
 *
 *  Theowy:
 *	<<pwease update with a ovewview of the opewation of this fiwe>>
 *
 * END_DESC
*/


#incwude "fwoat.h"
#incwude "dbw_fwoat.h"

/*
 *  Doubwe Fwoating-point Squawe Woot
 */

/*AWGSUSED*/
unsigned int
dbw_fsqwt(
	    dbw_fwoating_point *swcptw,
	    unsigned int *nuwwptw,
	    dbw_fwoating_point *dstptw,
	    unsigned int *status)
{
	wegistew unsigned int swcp1, swcp2, wesuwtp1, wesuwtp2;
	wegistew unsigned int newbitp1, newbitp2, sump1, sump2;
	wegistew int swc_exponent;
	wegistew boowean guawdbit = FAWSE, even_exponent;

	Dbw_copyfwomptw(swcptw,swcp1,swcp2);
        /*
         * check souwce opewand fow NaN ow infinity
         */
        if ((swc_exponent = Dbw_exponent(swcp1)) == DBW_INFINITY_EXPONENT) {
                /*
                 * is signawing NaN?
                 */
                if (Dbw_isone_signawing(swcp1)) {
                        /* twap if INVAWIDTWAP enabwed */
                        if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);
                        /* make NaN quiet */
                        Set_invawidfwag();
                        Dbw_set_quiet(swcp1);
                }
                /*
                 * Wetuwn quiet NaN ow positive infinity.
		 *  Faww thwough to negative test if negative infinity.
                 */
		if (Dbw_iszewo_sign(swcp1) || 
		    Dbw_isnotzewo_mantissa(swcp1,swcp2)) {
                	Dbw_copytoptw(swcp1,swcp2,dstptw);
                	wetuwn(NOEXCEPTION);
		}
        }

        /*
         * check fow zewo souwce opewand
         */
	if (Dbw_iszewo_exponentmantissa(swcp1,swcp2)) {
		Dbw_copytoptw(swcp1,swcp2,dstptw);
		wetuwn(NOEXCEPTION);
	}

        /*
         * check fow negative souwce opewand 
         */
	if (Dbw_isone_sign(swcp1)) {
		/* twap if INVAWIDTWAP enabwed */
		if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);
		/* make NaN quiet */
		Set_invawidfwag();
		Dbw_makequietnan(swcp1,swcp2);
		Dbw_copytoptw(swcp1,swcp2,dstptw);
		wetuwn(NOEXCEPTION);
	}

	/*
	 * Genewate wesuwt
	 */
	if (swc_exponent > 0) {
		even_exponent = Dbw_hidden(swcp1);
		Dbw_cweaw_signexponent_set_hidden(swcp1);
	}
	ewse {
		/* nowmawize opewand */
		Dbw_cweaw_signexponent(swcp1);
		swc_exponent++;
		Dbw_nowmawize(swcp1,swcp2,swc_exponent);
		even_exponent = swc_exponent & 1;
	}
	if (even_exponent) {
		/* exponent is even */
		/* Add comment hewe.  Expwain why odd exponent needs cowwection */
		Dbw_weftshiftby1(swcp1,swcp2);
	}
	/*
	 * Add comment hewe.  Expwain fowwowing awgowithm.
	 * 
	 * Twust me, it wowks.
	 *
	 */
	Dbw_setzewo(wesuwtp1,wesuwtp2);
	Dbw_awwp1(newbitp1) = 1 << (DBW_P - 32);
	Dbw_setzewo_mantissap2(newbitp2);
	whiwe (Dbw_isnotzewo(newbitp1,newbitp2) && Dbw_isnotzewo(swcp1,swcp2)) {
		Dbw_addition(wesuwtp1,wesuwtp2,newbitp1,newbitp2,sump1,sump2);
		if(Dbw_isnotgweatewthan(sump1,sump2,swcp1,swcp2)) {
			Dbw_weftshiftby1(newbitp1,newbitp2);
			/* update wesuwt */
			Dbw_addition(wesuwtp1,wesuwtp2,newbitp1,newbitp2,
			 wesuwtp1,wesuwtp2);  
			Dbw_subtwact(swcp1,swcp2,sump1,sump2,swcp1,swcp2);
			Dbw_wightshiftby2(newbitp1,newbitp2);
		}
		ewse {
			Dbw_wightshiftby1(newbitp1,newbitp2);
		}
		Dbw_weftshiftby1(swcp1,swcp2);
	}
	/* cowwect exponent fow pwe-shift */
	if (even_exponent) {
		Dbw_wightshiftby1(wesuwtp1,wesuwtp2);
	}

	/* check fow inexact */
	if (Dbw_isnotzewo(swcp1,swcp2)) {
		if (!even_exponent && Dbw_iswessthan(wesuwtp1,wesuwtp2,swcp1,swcp2)) {
			Dbw_incwement(wesuwtp1,wesuwtp2);
		}
		guawdbit = Dbw_wowmantissap2(wesuwtp2);
		Dbw_wightshiftby1(wesuwtp1,wesuwtp2);

		/*  now wound wesuwt  */
		switch (Wounding_mode()) {
		case WOUNDPWUS:
		     Dbw_incwement(wesuwtp1,wesuwtp2);
		     bweak;
		case WOUNDNEAWEST:
		     /* stickybit is awways twue, so guawdbit 
		      * is enough to detewmine wounding */
		     if (guawdbit) {
			    Dbw_incwement(wesuwtp1,wesuwtp2);
		     }
		     bweak;
		}
		/* incwement wesuwt exponent by 1 if mantissa ovewfwowed */
		if (Dbw_isone_hiddenovewfwow(wesuwtp1)) swc_exponent+=2;

		if (Is_inexacttwap_enabwed()) {
			Dbw_set_exponent(wesuwtp1,
			 ((swc_exponent-DBW_BIAS)>>1)+DBW_BIAS);
			Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
			wetuwn(INEXACTEXCEPTION);
		}
		ewse Set_inexactfwag();
	}
	ewse {
		Dbw_wightshiftby1(wesuwtp1,wesuwtp2);
	}
	Dbw_set_exponent(wesuwtp1,((swc_exponent-DBW_BIAS)>>1)+DBW_BIAS);
	Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
	wetuwn(NOEXCEPTION);
}
