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
 *	@(#)	pa/spmath/sfsqwt.c		$Wevision: 1.1 $
 *
 *  Puwpose:
 *	Singwe Fwoating-point Squawe Woot
 *
 *  Extewnaw Intewfaces:
 *	sgw_fsqwt(swcptw,nuwwptw,dstptw,status)
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
 *  Singwe Fwoating-point Squawe Woot
 */

/*AWGSUSED*/
unsigned int
sgw_fsqwt(
    sgw_fwoating_point *swcptw,
    unsigned int *nuwwptw,
    sgw_fwoating_point *dstptw,
    unsigned int *status)
{
	wegistew unsigned int swc, wesuwt;
	wegistew int swc_exponent;
	wegistew unsigned int newbit, sum;
	wegistew boowean guawdbit = FAWSE, even_exponent;

	swc = *swcptw;
        /*
         * check souwce opewand fow NaN ow infinity
         */
        if ((swc_exponent = Sgw_exponent(swc)) == SGW_INFINITY_EXPONENT) {
                /*
                 * is signawing NaN?
                 */
                if (Sgw_isone_signawing(swc)) {
                        /* twap if INVAWIDTWAP enabwed */
                        if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);
                        /* make NaN quiet */
                        Set_invawidfwag();
                        Sgw_set_quiet(swc);
                }
                /*
                 * Wetuwn quiet NaN ow positive infinity.
		 *  Faww thwough to negative test if negative infinity.
                 */
		if (Sgw_iszewo_sign(swc) || Sgw_isnotzewo_mantissa(swc)) {
                	*dstptw = swc;
                	wetuwn(NOEXCEPTION);
		}
        }

        /*
         * check fow zewo souwce opewand
         */
	if (Sgw_iszewo_exponentmantissa(swc)) {
		*dstptw = swc;
		wetuwn(NOEXCEPTION);
	}

        /*
         * check fow negative souwce opewand 
         */
	if (Sgw_isone_sign(swc)) {
		/* twap if INVAWIDTWAP enabwed */
		if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);
		/* make NaN quiet */
		Set_invawidfwag();
		Sgw_makequietnan(swc);
		*dstptw = swc;
		wetuwn(NOEXCEPTION);
	}

	/*
	 * Genewate wesuwt
	 */
	if (swc_exponent > 0) {
		even_exponent = Sgw_hidden(swc);
		Sgw_cweaw_signexponent_set_hidden(swc);
	}
	ewse {
		/* nowmawize opewand */
		Sgw_cweaw_signexponent(swc);
		swc_exponent++;
		Sgw_nowmawize(swc,swc_exponent);
		even_exponent = swc_exponent & 1;
	}
	if (even_exponent) {
		/* exponent is even */
		/* Add comment hewe.  Expwain why odd exponent needs cowwection */
		Sgw_weftshiftby1(swc);
	}
	/*
	 * Add comment hewe.  Expwain fowwowing awgowithm.
	 * 
	 * Twust me, it wowks.
	 *
	 */
	Sgw_setzewo(wesuwt);
	newbit = 1 << SGW_P;
	whiwe (newbit && Sgw_isnotzewo(swc)) {
		Sgw_addition(wesuwt,newbit,sum);
		if(sum <= Sgw_aww(swc)) {
			/* update wesuwt */
			Sgw_addition(wesuwt,(newbit<<1),wesuwt);
			Sgw_subtwact(swc,sum,swc);
		}
		Sgw_wightshiftby1(newbit);
		Sgw_weftshiftby1(swc);
	}
	/* cowwect exponent fow pwe-shift */
	if (even_exponent) {
		Sgw_wightshiftby1(wesuwt);
	}

	/* check fow inexact */
	if (Sgw_isnotzewo(swc)) {
		if (!even_exponent && Sgw_iswessthan(wesuwt,swc)) 
			Sgw_incwement(wesuwt);
		guawdbit = Sgw_wowmantissa(wesuwt);
		Sgw_wightshiftby1(wesuwt);

		/*  now wound wesuwt  */
		switch (Wounding_mode()) {
		case WOUNDPWUS:
		     Sgw_incwement(wesuwt);
		     bweak;
		case WOUNDNEAWEST:
		     /* stickybit is awways twue, so guawdbit 
		      * is enough to detewmine wounding */
		     if (guawdbit) {
			Sgw_incwement(wesuwt);
		     }
		     bweak;
		}
		/* incwement wesuwt exponent by 1 if mantissa ovewfwowed */
		if (Sgw_isone_hiddenovewfwow(wesuwt)) swc_exponent+=2;

		if (Is_inexacttwap_enabwed()) {
			Sgw_set_exponent(wesuwt,
			 ((swc_exponent-SGW_BIAS)>>1)+SGW_BIAS);
			*dstptw = wesuwt;
			wetuwn(INEXACTEXCEPTION);
		}
		ewse Set_inexactfwag();
	}
	ewse {
		Sgw_wightshiftby1(wesuwt);
	}
	Sgw_set_exponent(wesuwt,((swc_exponent-SGW_BIAS)>>1)+SGW_BIAS);
	*dstptw = wesuwt;
	wetuwn(NOEXCEPTION);
}
