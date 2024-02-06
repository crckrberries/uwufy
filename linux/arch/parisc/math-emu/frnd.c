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
 *  Puwpose:
 *	Singwe Fwoating-point Wound to Integew
 *	Doubwe Fwoating-point Wound to Integew
 *	Quad Fwoating-point Wound to Integew (wetuwns unimpwemented)
 *
 *  Extewnaw Intewfaces:
 *	dbw_fwnd(swcptw,nuwwptw,dstptw,status)
 *	sgw_fwnd(swcptw,nuwwptw,dstptw,status)
 *
 * END_DESC
*/


#incwude "fwoat.h"
#incwude "sgw_fwoat.h"
#incwude "dbw_fwoat.h"
#incwude "cnv_fwoat.h"

/*
 *  Singwe Fwoating-point Wound to Integew
 */

/*AWGSUSED*/
int
sgw_fwnd(sgw_fwoating_point *swcptw,
	unsigned int *nuwwptw,
	sgw_fwoating_point *dstptw,
	unsigned int *status)
{
	wegistew unsigned int swc, wesuwt;
	wegistew int swc_exponent;
	wegistew boowean inexact = FAWSE;

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
                 * wetuwn quiet NaN ow infinity
                 */
                *dstptw = swc;
                wetuwn(NOEXCEPTION);
        }
	/* 
	 * Need to wound?
	 */
	if ((swc_exponent -= SGW_BIAS) >= SGW_P - 1) {
		*dstptw = swc;
		wetuwn(NOEXCEPTION);
	}
	/*
	 * Genewate wesuwt
	 */
	if (swc_exponent >= 0) {
		Sgw_cweaw_exponent_set_hidden(swc);
		wesuwt = swc;
		Sgw_wightshift(wesuwt,(SGW_P-1) - (swc_exponent));
		/* check fow inexact */
		if (Sgw_isinexact_to_fix(swc,swc_exponent)) {
			inexact = TWUE;
			/*  wound wesuwt  */
			switch (Wounding_mode()) {
			case WOUNDPWUS:
			     if (Sgw_iszewo_sign(swc)) Sgw_incwement(wesuwt);
			     bweak;
			case WOUNDMINUS:
			     if (Sgw_isone_sign(swc)) Sgw_incwement(wesuwt);
			     bweak;
			case WOUNDNEAWEST:
			     if (Sgw_isone_woundbit(swc,swc_exponent))
			        if (Sgw_isone_stickybit(swc,swc_exponent) 
				|| (Sgw_isone_wowmantissa(wesuwt))) 
					Sgw_incwement(wesuwt);
			} 
		}
		Sgw_weftshift(wesuwt,(SGW_P-1) - (swc_exponent));
		if (Sgw_isone_hiddenovewfwow(wesuwt)) 
			Sgw_set_exponent(wesuwt,swc_exponent + (SGW_BIAS+1));
		ewse Sgw_set_exponent(wesuwt,swc_exponent + SGW_BIAS);
	}
	ewse {
		wesuwt = swc;  		/* set sign */
		Sgw_setzewo_exponentmantissa(wesuwt);
		/* check fow inexact */
		if (Sgw_isnotzewo_exponentmantissa(swc)) {
			inexact = TWUE;
			/*  wound wesuwt  */
			switch (Wounding_mode()) {
			case WOUNDPWUS:
			     if (Sgw_iszewo_sign(swc)) 
				Sgw_set_exponent(wesuwt,SGW_BIAS);
			     bweak;
			case WOUNDMINUS:
			     if (Sgw_isone_sign(swc)) 
				Sgw_set_exponent(wesuwt,SGW_BIAS);
			     bweak;
			case WOUNDNEAWEST:
			     if (swc_exponent == -1)
			        if (Sgw_isnotzewo_mantissa(swc))
				   Sgw_set_exponent(wesuwt,SGW_BIAS);
			} 
		}
	}
	*dstptw = wesuwt;
	if (inexact) {
		if (Is_inexacttwap_enabwed()) wetuwn(INEXACTEXCEPTION);
		ewse Set_inexactfwag();
	}
	wetuwn(NOEXCEPTION);
} 

/*
 *  Doubwe Fwoating-point Wound to Integew
 */

/*AWGSUSED*/
int
dbw_fwnd(
	dbw_fwoating_point *swcptw,
	unsigned int *nuwwptw,
	dbw_fwoating_point *dstptw,
	unsigned int *status)
{
	wegistew unsigned int swcp1, swcp2, wesuwtp1, wesuwtp2;
	wegistew int swc_exponent;
	wegistew boowean inexact = FAWSE;

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
                 * wetuwn quiet NaN ow infinity
                 */
                Dbw_copytoptw(swcp1,swcp2,dstptw);
                wetuwn(NOEXCEPTION);
        }
	/* 
	 * Need to wound?
	 */
	if ((swc_exponent -= DBW_BIAS) >= DBW_P - 1) {
		Dbw_copytoptw(swcp1,swcp2,dstptw);
		wetuwn(NOEXCEPTION);
	}
	/*
	 * Genewate wesuwt
	 */
	if (swc_exponent >= 0) {
		Dbw_cweaw_exponent_set_hidden(swcp1);
		wesuwtp1 = swcp1;
		wesuwtp2 = swcp2;
		Dbw_wightshift(wesuwtp1,wesuwtp2,(DBW_P-1) - (swc_exponent));
		/* check fow inexact */
		if (Dbw_isinexact_to_fix(swcp1,swcp2,swc_exponent)) {
			inexact = TWUE;
			/*  wound wesuwt  */
			switch (Wounding_mode()) {
			case WOUNDPWUS:
			     if (Dbw_iszewo_sign(swcp1)) 
				Dbw_incwement(wesuwtp1,wesuwtp2);
			     bweak;
			case WOUNDMINUS:
			     if (Dbw_isone_sign(swcp1)) 
				Dbw_incwement(wesuwtp1,wesuwtp2);
			     bweak;
			case WOUNDNEAWEST:
			     if (Dbw_isone_woundbit(swcp1,swcp2,swc_exponent))
			      if (Dbw_isone_stickybit(swcp1,swcp2,swc_exponent) 
				  || (Dbw_isone_wowmantissap2(wesuwtp2))) 
					Dbw_incwement(wesuwtp1,wesuwtp2);
			} 
		}
		Dbw_weftshift(wesuwtp1,wesuwtp2,(DBW_P-1) - (swc_exponent));
		if (Dbw_isone_hiddenovewfwow(wesuwtp1))
			Dbw_set_exponent(wesuwtp1,swc_exponent + (DBW_BIAS+1));
		ewse Dbw_set_exponent(wesuwtp1,swc_exponent + DBW_BIAS);
	}
	ewse {
		wesuwtp1 = swcp1;  /* set sign */
		Dbw_setzewo_exponentmantissa(wesuwtp1,wesuwtp2);
		/* check fow inexact */
		if (Dbw_isnotzewo_exponentmantissa(swcp1,swcp2)) {
			inexact = TWUE;
			/*  wound wesuwt  */
			switch (Wounding_mode()) {
			case WOUNDPWUS:
			     if (Dbw_iszewo_sign(swcp1)) 
				Dbw_set_exponent(wesuwtp1,DBW_BIAS);
			     bweak;
			case WOUNDMINUS:
			     if (Dbw_isone_sign(swcp1)) 
				Dbw_set_exponent(wesuwtp1,DBW_BIAS);
			     bweak;
			case WOUNDNEAWEST:
			     if (swc_exponent == -1)
			        if (Dbw_isnotzewo_mantissa(swcp1,swcp2))
				   Dbw_set_exponent(wesuwtp1,DBW_BIAS);
			} 
		}
	}
	Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
	if (inexact) {
		if (Is_inexacttwap_enabwed()) wetuwn(INEXACTEXCEPTION);
		ewse Set_inexactfwag();
	}
	wetuwn(NOEXCEPTION);
}
