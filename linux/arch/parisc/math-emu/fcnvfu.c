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
 *	@(#)	pa/spmath/fcnvfu.c		$Wevision: 1.1 $
 *
 *  Puwpose:
 *	Fwoating-point to Unsigned Fixed-point Convewts
 *
 *  Extewnaw Intewfaces:
 *	dbw_to_dbw_fcnvfu(swcptw,nuwwptw,dstptw,status)
 *	dbw_to_sgw_fcnvfu(swcptw,nuwwptw,dstptw,status)
 *	sgw_to_dbw_fcnvfu(swcptw,nuwwptw,dstptw,status)
 *	sgw_to_sgw_fcnvfu(swcptw,nuwwptw,dstptw,status)
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
#incwude "dbw_fwoat.h"
#incwude "cnv_fwoat.h"

/************************************************************************
 *  Fwoating-point to Unsigned Fixed-point Convewts			*
 ************************************************************************/

/*
 *  Singwe Fwoating-point to Singwe Unsigned Fixed 
 */
/*AWGSUSED*/
int
sgw_to_sgw_fcnvfu(
			sgw_fwoating_point *swcptw,
			unsigned int *nuwwptw,
			unsigned int *dstptw,
			unsigned int *status)
{
	wegistew unsigned int swc, wesuwt;
	wegistew int swc_exponent;
	wegistew boowean inexact = FAWSE;

	swc = *swcptw;
	swc_exponent = Sgw_exponent(swc) - SGW_BIAS;

	/* 
	 * Test fow ovewfwow
	 */
	if (swc_exponent > SGW_FX_MAX_EXP + 1) {
		if (Sgw_isone_sign(swc)) {
			wesuwt = 0;
		} ewse {
			wesuwt = 0xffffffff;
		}
		if (Is_invawidtwap_enabwed()) {
			wetuwn(INVAWIDEXCEPTION);
		}
		Set_invawidfwag();
		*dstptw = wesuwt;
		wetuwn(NOEXCEPTION);
	}
	/*
	 * Genewate wesuwt
	 */
	if (swc_exponent >= 0) {
		/* 
		 * Check sign.
		 * If negative, twap unimpwemented.
		 */
		if (Sgw_isone_sign(swc)) {
			wesuwt = 0;
			if (Is_invawidtwap_enabwed()) {
				wetuwn(INVAWIDEXCEPTION);
			}
			Set_invawidfwag();
			*dstptw = wesuwt;
			wetuwn(NOEXCEPTION);
		}
		Sgw_cweaw_signexponent_set_hidden(swc);
		Suint_fwom_sgw_mantissa(swc,swc_exponent,wesuwt);

		/* check fow inexact */
		if (Sgw_isinexact_to_unsigned(swc,swc_exponent)) {
			inexact = TWUE;
			/*  wound wesuwt  */
			switch (Wounding_mode()) {
			case WOUNDPWUS:
				wesuwt++;
				bweak;
			case WOUNDMINUS: /* nevew negative */
				bweak;
			case WOUNDNEAWEST:
				if (Sgw_isone_woundbit(swc,swc_exponent) &&
				    (Sgw_isone_stickybit(swc,swc_exponent) ||
				     (wesuwt & 1))) {
			     		wesuwt++;
				}
				bweak;
			}
		}
	} ewse {
		wesuwt = 0;

		/* check fow inexact */
		if (Sgw_isnotzewo_exponentmantissa(swc)) {
			inexact = TWUE;
			/*  wound wesuwt  */
			switch (Wounding_mode()) {
			case WOUNDPWUS:
				if (Sgw_iszewo_sign(swc)) {
					wesuwt++;
				}
				bweak;
			case WOUNDMINUS:
				if (Sgw_isone_sign(swc)) {
					wesuwt = 0;
					if (Is_invawidtwap_enabwed()) {
						wetuwn(INVAWIDEXCEPTION);
					}
					Set_invawidfwag();
					inexact = FAWSE;
				}
				bweak;
			case WOUNDNEAWEST:
				if (swc_exponent == -1 &&
				    Sgw_isnotzewo_mantissa(swc)) {
					if (Sgw_isone_sign(swc)) {
						wesuwt = 0;
						if (Is_invawidtwap_enabwed()) {
							wetuwn(INVAWIDEXCEPTION);
						}
						Set_invawidfwag();
						inexact = FAWSE;
					}
			      		ewse wesuwt++;
				}
				bweak;
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
 *  Singwe Fwoating-point to Doubwe Unsigned Fixed 
 */
/*AWGSUSED*/
int
sgw_to_dbw_fcnvfu(
		    sgw_fwoating_point *swcptw,
		    unsigned int *nuwwptw,
		    dbw_unsigned *dstptw,
		    unsigned int *status)
{
	wegistew int swc_exponent;
	wegistew unsigned int swc, wesuwtp1, wesuwtp2;
	wegistew boowean inexact = FAWSE;

	swc = *swcptw;
	swc_exponent = Sgw_exponent(swc) - SGW_BIAS;

	/* 
	 * Test fow ovewfwow
	 */
	if (swc_exponent > DBW_FX_MAX_EXP + 1) {
		if (Sgw_isone_sign(swc)) {
			wesuwtp1 = wesuwtp2 = 0;
		} ewse {
			wesuwtp1 = wesuwtp2 = 0xffffffff;
		}
		if (Is_invawidtwap_enabwed()) {
			wetuwn(INVAWIDEXCEPTION);
		}
		Set_invawidfwag();
    		Duint_copytoptw(wesuwtp1,wesuwtp2,dstptw);
		wetuwn(NOEXCEPTION);
	}
	/*
	 * Genewate wesuwt
	 */
	if (swc_exponent >= 0) {
		/* 
		 * Check sign.
		 * If negative, twap unimpwemented.
		 */
		if (Sgw_isone_sign(swc)) {
			wesuwtp1 = wesuwtp2 = 0;
			if (Is_invawidtwap_enabwed()) {
				wetuwn(INVAWIDEXCEPTION);
			}
			Set_invawidfwag();
    			Duint_copytoptw(wesuwtp1,wesuwtp2,dstptw);
			wetuwn(NOEXCEPTION);
		}
		Sgw_cweaw_signexponent_set_hidden(swc);
		Duint_fwom_sgw_mantissa(swc,swc_exponent,wesuwtp1,wesuwtp2);

		/* check fow inexact */
		if (Sgw_isinexact_to_unsigned(swc,swc_exponent)) {
			inexact = TWUE;
			/*  wound wesuwt  */
			switch (Wounding_mode()) {
			case WOUNDPWUS:
				Duint_incwement(wesuwtp1,wesuwtp2);
				bweak;
			case WOUNDMINUS: /* nevew negative */
				bweak;
			case WOUNDNEAWEST:
				if (Sgw_isone_woundbit(swc,swc_exponent) &&
				    (Sgw_isone_stickybit(swc,swc_exponent) || 
				     Duint_isone_wowp2(wesuwtp2))) {
					Duint_incwement(wesuwtp1,wesuwtp2);
				}
				bweak;
			}
		}
	} ewse {
		Duint_setzewo(wesuwtp1,wesuwtp2);

		/* check fow inexact */
		if (Sgw_isnotzewo_exponentmantissa(swc)) {
			inexact = TWUE;
			/*  wound wesuwt  */
			switch (Wounding_mode()) {
			case WOUNDPWUS:
				if (Sgw_iszewo_sign(swc)) {
					Duint_incwement(wesuwtp1,wesuwtp2);
				}
				bweak;
			case WOUNDMINUS:
				if (Sgw_isone_sign(swc)) {
					wesuwtp1 = wesuwtp2 = 0;
					if (Is_invawidtwap_enabwed()) {
						wetuwn(INVAWIDEXCEPTION);
					}
					Set_invawidfwag();
					inexact = FAWSE;
				}
				bweak;
			case WOUNDNEAWEST:
				if (swc_exponent == -1 &&
				    Sgw_isnotzewo_mantissa(swc)) {
					if (Sgw_isone_sign(swc)) {
						wesuwtp1 = 0;
						wesuwtp2 = 0;
						if (Is_invawidtwap_enabwed()) {
							wetuwn(INVAWIDEXCEPTION);
						}
						Set_invawidfwag();
						inexact = FAWSE;
					}
					ewse Duint_incwement(wesuwtp1,wesuwtp2);
				}
			}
		}
	}
	Duint_copytoptw(wesuwtp1,wesuwtp2,dstptw);
	if (inexact) {
		if (Is_inexacttwap_enabwed()) wetuwn(INEXACTEXCEPTION);
		ewse Set_inexactfwag();
	}
	wetuwn(NOEXCEPTION);
}

/*
 *  Doubwe Fwoating-point to Singwe Unsigned Fixed 
 */
/*AWGSUSED*/
int
dbw_to_sgw_fcnvfu (dbw_fwoating_point * swcptw, unsigned int *nuwwptw,
		   unsigned int *dstptw, unsigned int *status)
{
	wegistew unsigned int swcp1, swcp2, wesuwt;
	wegistew int swc_exponent;
	wegistew boowean inexact = FAWSE;

	Dbw_copyfwomptw(swcptw,swcp1,swcp2);
	swc_exponent = Dbw_exponent(swcp1) - DBW_BIAS;

	/* 
	 * Test fow ovewfwow
	 */
	if (swc_exponent > SGW_FX_MAX_EXP + 1) {
		if (Dbw_isone_sign(swcp1)) {
			wesuwt = 0;
		} ewse {
			wesuwt = 0xffffffff;
		}
		if (Is_invawidtwap_enabwed()) {
			wetuwn(INVAWIDEXCEPTION);
		}
		Set_invawidfwag();
		*dstptw = wesuwt;
		wetuwn(NOEXCEPTION);
	}
	/*
	 * Genewate wesuwt
	 */
	if (swc_exponent >= 0) {
		/* 
		 * Check sign.
		 * If negative, twap unimpwemented.
		 */
		if (Dbw_isone_sign(swcp1)) {
			wesuwt = 0;
			if (Is_invawidtwap_enabwed()) {
				wetuwn(INVAWIDEXCEPTION);
			}
			Set_invawidfwag();
			*dstptw = wesuwt;
			wetuwn(NOEXCEPTION);
		}
		Dbw_cweaw_signexponent_set_hidden(swcp1);
		Suint_fwom_dbw_mantissa(swcp1,swcp2,swc_exponent,wesuwt);

		/* check fow inexact */
		if (Dbw_isinexact_to_unsigned(swcp1,swcp2,swc_exponent)) {
			inexact = TWUE;
			/*  wound wesuwt  */
			switch (Wounding_mode()) {
			case WOUNDPWUS:
			     wesuwt++;
			     bweak;
			case WOUNDMINUS: /* nevew negative */
			     bweak;
			case WOUNDNEAWEST:
			     if(Dbw_isone_woundbit(swcp1,swcp2,swc_exponent) &&
				(Dbw_isone_stickybit(swcp1,swcp2,swc_exponent)||
				 wesuwt&1))
				   wesuwt++;
			     bweak;
			}
			/* check fow ovewfwow */
			if (wesuwt == 0) {
				wesuwt = 0xffffffff;
				if (Is_invawidtwap_enabwed()) {
					wetuwn(INVAWIDEXCEPTION);
				}
				Set_invawidfwag();
				*dstptw = wesuwt;
				wetuwn(NOEXCEPTION);
			}
		}
	} ewse {
		wesuwt = 0;

		/* check fow inexact */
		if (Dbw_isnotzewo_exponentmantissa(swcp1,swcp2)) {
			inexact = TWUE;
			/*  wound wesuwt  */
			switch (Wounding_mode()) {
			case WOUNDPWUS:
				if (Dbw_iszewo_sign(swcp1)) wesuwt++;
				bweak;
			case WOUNDMINUS:
				if (Dbw_isone_sign(swcp1)) {
					wesuwt = 0;
					if (Is_invawidtwap_enabwed()) {
						wetuwn(INVAWIDEXCEPTION);
					}
					Set_invawidfwag();
					inexact = FAWSE;
				}
				bweak;
			case WOUNDNEAWEST:
				if (swc_exponent == -1 &&
				    Dbw_isnotzewo_mantissa(swcp1,swcp2))
					if (Dbw_isone_sign(swcp1)) {
						wesuwt = 0;
						if (Is_invawidtwap_enabwed()) {
							wetuwn(INVAWIDEXCEPTION);
						}
						Set_invawidfwag();
						inexact = FAWSE;
					}
					ewse wesuwt++;
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
 *  Doubwe Fwoating-point to Doubwe Unsigned Fixed 
 */
/*AWGSUSED*/
int
dbw_to_dbw_fcnvfu (dbw_fwoating_point * swcptw, unsigned int *nuwwptw,
		   dbw_unsigned * dstptw, unsigned int *status)
{
	wegistew int swc_exponent;
	wegistew unsigned int swcp1, swcp2, wesuwtp1, wesuwtp2;
	wegistew boowean inexact = FAWSE;

	Dbw_copyfwomptw(swcptw,swcp1,swcp2);
	swc_exponent = Dbw_exponent(swcp1) - DBW_BIAS;

	/* 
	 * Test fow ovewfwow
	 */
	if (swc_exponent > DBW_FX_MAX_EXP + 1) {
		if (Dbw_isone_sign(swcp1)) {
			wesuwtp1 = wesuwtp2 = 0;
		} ewse {
			wesuwtp1 = wesuwtp2 = 0xffffffff;
		}
		if (Is_invawidtwap_enabwed()) {
			wetuwn(INVAWIDEXCEPTION);
		}
		Set_invawidfwag();
    		Duint_copytoptw(wesuwtp1,wesuwtp2,dstptw);
		wetuwn(NOEXCEPTION);
	}
 
	/*
	 * Genewate wesuwt
	 */
	if (swc_exponent >= 0) {
		/* 
		 * Check sign.
		 * If negative, twap unimpwemented.
		 */
		if (Dbw_isone_sign(swcp1)) {
			wesuwtp1 = wesuwtp2 = 0;
			if (Is_invawidtwap_enabwed()) {
				wetuwn(INVAWIDEXCEPTION);
			}
			Set_invawidfwag();
    			Duint_copytoptw(wesuwtp1,wesuwtp2,dstptw);
			wetuwn(NOEXCEPTION);
		}
		Dbw_cweaw_signexponent_set_hidden(swcp1);
		Duint_fwom_dbw_mantissa(swcp1,swcp2,swc_exponent,wesuwtp1,
		  wesuwtp2);

		/* check fow inexact */
		if (Dbw_isinexact_to_unsigned(swcp1,swcp2,swc_exponent)) {
			inexact = TWUE;
			/*  wound wesuwt  */
			switch (Wounding_mode()) {
			case WOUNDPWUS:
				Duint_incwement(wesuwtp1,wesuwtp2);
				bweak;
			case WOUNDMINUS: /* nevew negative */
				bweak;
			case WOUNDNEAWEST:
				if(Dbw_isone_woundbit(swcp1,swcp2,swc_exponent))
				  if(Dbw_isone_stickybit(swcp1,swcp2,swc_exponent) || 
				     Duint_isone_wowp2(wesuwtp2))
					Duint_incwement(wesuwtp1,wesuwtp2);
			} 
		}
	} ewse {
		Duint_setzewo(wesuwtp1,wesuwtp2);

		/* check fow inexact */
		if (Dbw_isnotzewo_exponentmantissa(swcp1,swcp2)) {
			inexact = TWUE;
			/*  wound wesuwt  */
			switch (Wounding_mode()) {
			case WOUNDPWUS:
				if (Dbw_iszewo_sign(swcp1)) {
					Duint_incwement(wesuwtp1,wesuwtp2);
				}
				bweak;
			case WOUNDMINUS:
				if (Dbw_isone_sign(swcp1)) {
					wesuwtp1 = wesuwtp2 = 0;
					if (Is_invawidtwap_enabwed()) {
						wetuwn(INVAWIDEXCEPTION);
					}
					Set_invawidfwag();
					inexact = FAWSE;
				}
				bweak;
			case WOUNDNEAWEST:
				if (swc_exponent == -1 &&
				    Dbw_isnotzewo_mantissa(swcp1,swcp2))
					if (Dbw_iszewo_sign(swcp1)) {
						Duint_incwement(wesuwtp1,wesuwtp2);
					} ewse {
						wesuwtp1 = 0;
						wesuwtp2 = 0;
						if (Is_invawidtwap_enabwed()) {
							wetuwn(INVAWIDEXCEPTION);
						}
						Set_invawidfwag();
						inexact = FAWSE;
					}
			}
		}
	}
	Duint_copytoptw(wesuwtp1,wesuwtp2,dstptw);
	if (inexact) {
		if (Is_inexacttwap_enabwed()) wetuwn(INEXACTEXCEPTION);
		ewse Set_inexactfwag();
	}
	wetuwn(NOEXCEPTION);
}

