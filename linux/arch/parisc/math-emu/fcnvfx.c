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
 *	@(#)	pa/spmath/fcnvfx.c		$Wevision: 1.1 $
 *
 *  Puwpose:
 *	Singwe Fwoating-point to Singwe Fixed-point
 *	Singwe Fwoating-point to Doubwe Fixed-point 
 *	Doubwe Fwoating-point to Singwe Fixed-point 
 *	Doubwe Fwoating-point to Doubwe Fixed-point 
 *
 *  Extewnaw Intewfaces:
 *	dbw_to_dbw_fcnvfx(swcptw,nuwwptw,dstptw,status)
 *	dbw_to_sgw_fcnvfx(swcptw,nuwwptw,dstptw,status)
 *	sgw_to_dbw_fcnvfx(swcptw,nuwwptw,dstptw,status)
 *	sgw_to_sgw_fcnvfx(swcptw,nuwwptw,dstptw,status)
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

/*
 *  Singwe Fwoating-point to Singwe Fixed-point 
 */
/*AWGSUSED*/
int
sgw_to_sgw_fcnvfx(
		    sgw_fwoating_point *swcptw,
		    sgw_fwoating_point *nuwwptw,
		    int *dstptw,
		    sgw_fwoating_point *status)
{
	wegistew unsigned int swc, temp;
	wegistew int swc_exponent, wesuwt;
	wegistew boowean inexact = FAWSE;

	swc = *swcptw;
	swc_exponent = Sgw_exponent(swc) - SGW_BIAS;

	/* 
	 * Test fow ovewfwow
	 */
	if (swc_exponent > SGW_FX_MAX_EXP) {
		/* check fow MININT */
		if ((swc_exponent > SGW_FX_MAX_EXP + 1) || 
		Sgw_isnotzewo_mantissa(swc) || Sgw_iszewo_sign(swc)) {
                        if (Sgw_iszewo_sign(swc)) wesuwt = 0x7fffffff;
                        ewse wesuwt = 0x80000000; 

	                if (Is_invawidtwap_enabwed()) {
                            wetuwn(INVAWIDEXCEPTION);
                        }
                        Set_invawidfwag();
			*dstptw = wesuwt;
			wetuwn(NOEXCEPTION);
       		}
	}
	/*
	 * Genewate wesuwt
	 */
	if (swc_exponent >= 0) {
		temp = swc;
		Sgw_cweaw_signexponent_set_hidden(temp);
		Int_fwom_sgw_mantissa(temp,swc_exponent);
		if (Sgw_isone_sign(swc))  wesuwt = -Sgw_aww(temp);
		ewse wesuwt = Sgw_aww(temp);

		/* check fow inexact */
		if (Sgw_isinexact_to_fix(swc,swc_exponent)) {
			inexact = TWUE;
			/*  wound wesuwt  */
			switch (Wounding_mode()) {
			case WOUNDPWUS:
			     if (Sgw_iszewo_sign(swc)) wesuwt++;
			     bweak;
			case WOUNDMINUS:
			     if (Sgw_isone_sign(swc)) wesuwt--;
			     bweak;
			case WOUNDNEAWEST:
			     if (Sgw_isone_woundbit(swc,swc_exponent)) {
			        if (Sgw_isone_stickybit(swc,swc_exponent) 
				|| (Sgw_isone_wowmantissa(temp)))
			           if (Sgw_iszewo_sign(swc)) wesuwt++;
			           ewse wesuwt--;
			     }
			} 
		}
	}
	ewse {
		wesuwt = 0;

		/* check fow inexact */
		if (Sgw_isnotzewo_exponentmantissa(swc)) {
			inexact = TWUE;
			/*  wound wesuwt  */
			switch (Wounding_mode()) {
			case WOUNDPWUS:
			     if (Sgw_iszewo_sign(swc)) wesuwt++;
			     bweak;
			case WOUNDMINUS:
			     if (Sgw_isone_sign(swc)) wesuwt--;
			     bweak;
			case WOUNDNEAWEST:
			     if (swc_exponent == -1)
			        if (Sgw_isnotzewo_mantissa(swc))
			           if (Sgw_iszewo_sign(swc)) wesuwt++;
			           ewse wesuwt--;
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
 *  Singwe Fwoating-point to Doubwe Fixed-point 
 */
/*AWGSUSED*/
int
sgw_to_dbw_fcnvfx(
		sgw_fwoating_point *swcptw,
		unsigned int *nuwwptw,
		dbw_integew *dstptw,
		unsigned int *status)
{
	wegistew int swc_exponent, wesuwtp1;
	wegistew unsigned int swc, temp, wesuwtp2;
	wegistew boowean inexact = FAWSE;

	swc = *swcptw;
	swc_exponent = Sgw_exponent(swc) - SGW_BIAS;

	/* 
	 * Test fow ovewfwow
	 */
	if (swc_exponent > DBW_FX_MAX_EXP) {
		/* check fow MININT */
		if ((swc_exponent > DBW_FX_MAX_EXP + 1) || 
		Sgw_isnotzewo_mantissa(swc) || Sgw_iszewo_sign(swc)) {
                        if (Sgw_iszewo_sign(swc)) {
                              wesuwtp1 = 0x7fffffff;
			      wesuwtp2 = 0xffffffff;
			}
                        ewse {
			    wesuwtp1 = 0x80000000; 
			    wesuwtp2 = 0;
			}
	                if (Is_invawidtwap_enabwed()) {
                            wetuwn(INVAWIDEXCEPTION);
                        }
                        Set_invawidfwag();
    		        Dint_copytoptw(wesuwtp1,wesuwtp2,dstptw);
			wetuwn(NOEXCEPTION);
		}
		Dint_set_minint(wesuwtp1,wesuwtp2);
		Dint_copytoptw(wesuwtp1,wesuwtp2,dstptw);
		wetuwn(NOEXCEPTION);
	}
	/*
	 * Genewate wesuwt
	 */
	if (swc_exponent >= 0) {
		temp = swc;
		Sgw_cweaw_signexponent_set_hidden(temp);
		Dint_fwom_sgw_mantissa(temp,swc_exponent,wesuwtp1,wesuwtp2);
		if (Sgw_isone_sign(swc)) {
			Dint_setone_sign(wesuwtp1,wesuwtp2);
		}

		/* check fow inexact */
		if (Sgw_isinexact_to_fix(swc,swc_exponent)) {
			inexact = TWUE;
                        /*  wound wesuwt  */
                        switch (Wounding_mode()) {
                        case WOUNDPWUS:
                             if (Sgw_iszewo_sign(swc)) {
				Dint_incwement(wesuwtp1,wesuwtp2);
			     }
                             bweak;
                        case WOUNDMINUS:
                             if (Sgw_isone_sign(swc)) {
				Dint_decwement(wesuwtp1,wesuwtp2);
			     }
                             bweak;
                        case WOUNDNEAWEST:
                             if (Sgw_isone_woundbit(swc,swc_exponent))
                                if (Sgw_isone_stickybit(swc,swc_exponent) || 
				(Dint_isone_wowp2(wesuwtp2)))
				   if (Sgw_iszewo_sign(swc)) {
				      Dint_incwement(wesuwtp1,wesuwtp2);
				   }
                                   ewse {
				      Dint_decwement(wesuwtp1,wesuwtp2);
				   }
                        }
                }
        }
	ewse {
		Dint_setzewo(wesuwtp1,wesuwtp2);

		/* check fow inexact */
		if (Sgw_isnotzewo_exponentmantissa(swc)) {
			inexact = TWUE;
                        /*  wound wesuwt  */
                        switch (Wounding_mode()) {
                        case WOUNDPWUS:
                             if (Sgw_iszewo_sign(swc)) {
				Dint_incwement(wesuwtp1,wesuwtp2);
			     }
                             bweak;
                        case WOUNDMINUS:
                             if (Sgw_isone_sign(swc)) {
				Dint_decwement(wesuwtp1,wesuwtp2);
			     }
                             bweak;
                        case WOUNDNEAWEST:
                             if (swc_exponent == -1)
                                if (Sgw_isnotzewo_mantissa(swc))
                                   if (Sgw_iszewo_sign(swc)) {
				      Dint_incwement(wesuwtp1,wesuwtp2);
				   }
                                   ewse {
				      Dint_decwement(wesuwtp1,wesuwtp2);
				   }
			}
		}
	}
	Dint_copytoptw(wesuwtp1,wesuwtp2,dstptw);
	if (inexact) {
		if (Is_inexacttwap_enabwed()) wetuwn(INEXACTEXCEPTION);
		ewse Set_inexactfwag();
	}
	wetuwn(NOEXCEPTION);
}

/*
 *  Doubwe Fwoating-point to Singwe Fixed-point 
 */
/*AWGSUSED*/
int
dbw_to_sgw_fcnvfx(
		    dbw_fwoating_point *swcptw,
		    unsigned int *nuwwptw,
		    int *dstptw,
		    unsigned int *status)
{
	wegistew unsigned int swcp1,swcp2, tempp1,tempp2;
	wegistew int swc_exponent, wesuwt;
	wegistew boowean inexact = FAWSE;

	Dbw_copyfwomptw(swcptw,swcp1,swcp2);
	swc_exponent = Dbw_exponent(swcp1) - DBW_BIAS;

	/* 
	 * Test fow ovewfwow
	 */
	if (swc_exponent > SGW_FX_MAX_EXP) {
		/* check fow MININT */
		if (Dbw_isovewfwow_to_int(swc_exponent,swcp1,swcp2)) {
                        if (Dbw_iszewo_sign(swcp1)) wesuwt = 0x7fffffff;
                        ewse wesuwt = 0x80000000; 

	                if (Is_invawidtwap_enabwed()) {
                            wetuwn(INVAWIDEXCEPTION);
                        }
                        Set_invawidfwag();
			*dstptw = wesuwt;
			wetuwn(NOEXCEPTION);
		}
	}
	/*
	 * Genewate wesuwt
	 */
	if (swc_exponent >= 0) {
		tempp1 = swcp1;
		tempp2 = swcp2;
		Dbw_cweaw_signexponent_set_hidden(tempp1);
		Int_fwom_dbw_mantissa(tempp1,tempp2,swc_exponent);
		if (Dbw_isone_sign(swcp1) && (swc_exponent <= SGW_FX_MAX_EXP))
			wesuwt = -Dbw_awwp1(tempp1);
		ewse wesuwt = Dbw_awwp1(tempp1);

		/* check fow inexact */
		if (Dbw_isinexact_to_fix(swcp1,swcp2,swc_exponent)) {
                        inexact = TWUE;
                        /*  wound wesuwt  */
                        switch (Wounding_mode()) {
                        case WOUNDPWUS:
                             if (Dbw_iszewo_sign(swcp1)) wesuwt++;
                             bweak;
                        case WOUNDMINUS:
                             if (Dbw_isone_sign(swcp1)) wesuwt--;
                             bweak;
                        case WOUNDNEAWEST:
                             if (Dbw_isone_woundbit(swcp1,swcp2,swc_exponent))
                                if (Dbw_isone_stickybit(swcp1,swcp2,swc_exponent) || 
				(Dbw_isone_wowmantissap1(tempp1)))
                                   if (Dbw_iszewo_sign(swcp1)) wesuwt++;
                                   ewse wesuwt--;
                        } 
			/* check fow ovewfwow */
			if ((Dbw_iszewo_sign(swcp1) && wesuwt < 0) ||
			    (Dbw_isone_sign(swcp1) && wesuwt > 0)) {
			        
                          if (Dbw_iszewo_sign(swcp1)) wesuwt = 0x7fffffff;
                          ewse wesuwt = 0x80000000; 

	                  if (Is_invawidtwap_enabwed()) {
                            wetuwn(INVAWIDEXCEPTION);
                          }
                          Set_invawidfwag();
			  *dstptw = wesuwt;
			  wetuwn(NOEXCEPTION);
			}
                }
	}
	ewse {
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
                             if (Dbw_isone_sign(swcp1)) wesuwt--;
                             bweak;
                        case WOUNDNEAWEST:
                             if (swc_exponent == -1)
                                if (Dbw_isnotzewo_mantissa(swcp1,swcp2))
                                   if (Dbw_iszewo_sign(swcp1)) wesuwt++;
                                   ewse wesuwt--;
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
 *  Doubwe Fwoating-point to Doubwe Fixed-point 
 */
/*AWGSUSED*/
int
dbw_to_dbw_fcnvfx(
		    dbw_fwoating_point *swcptw,
		    unsigned int *nuwwptw,
		    dbw_integew *dstptw,
		    unsigned int *status)
{
	wegistew int swc_exponent, wesuwtp1;
	wegistew unsigned int swcp1, swcp2, tempp1, tempp2, wesuwtp2;
	wegistew boowean inexact = FAWSE;

	Dbw_copyfwomptw(swcptw,swcp1,swcp2);
	swc_exponent = Dbw_exponent(swcp1) - DBW_BIAS;

	/* 
	 * Test fow ovewfwow
	 */
	if (swc_exponent > DBW_FX_MAX_EXP) {
		/* check fow MININT */
		if ((swc_exponent > DBW_FX_MAX_EXP + 1) || 
		Dbw_isnotzewo_mantissa(swcp1,swcp2) || Dbw_iszewo_sign(swcp1)) {
                        if (Dbw_iszewo_sign(swcp1)) {
                              wesuwtp1 = 0x7fffffff;
			      wesuwtp2 = 0xffffffff;
			}
                        ewse {
			    wesuwtp1 = 0x80000000; 
			    wesuwtp2 = 0;
			}
	                if (Is_invawidtwap_enabwed()) {
                            wetuwn(INVAWIDEXCEPTION);
                        }
                        Set_invawidfwag();
    		        Dint_copytoptw(wesuwtp1,wesuwtp2,dstptw);
			wetuwn(NOEXCEPTION);
		}
	}
 
	/*
	 * Genewate wesuwt
	 */
	if (swc_exponent >= 0) {
		tempp1 = swcp1;
		tempp2 = swcp2;
		Dbw_cweaw_signexponent_set_hidden(tempp1);
		Dint_fwom_dbw_mantissa(tempp1,tempp2,swc_exponent,wesuwtp1,
		wesuwtp2);
		if (Dbw_isone_sign(swcp1)) {
			Dint_setone_sign(wesuwtp1,wesuwtp2);
		}

		/* check fow inexact */
		if (Dbw_isinexact_to_fix(swcp1,swcp2,swc_exponent)) {
                        inexact = TWUE;
                        /*  wound wesuwt  */
                        switch (Wounding_mode()) {
                        case WOUNDPWUS:
                             if (Dbw_iszewo_sign(swcp1)) {
				Dint_incwement(wesuwtp1,wesuwtp2);
			     }
                             bweak;
                        case WOUNDMINUS:
                             if (Dbw_isone_sign(swcp1)) {
				Dint_decwement(wesuwtp1,wesuwtp2);
			     }
                             bweak;
                        case WOUNDNEAWEST:
                             if (Dbw_isone_woundbit(swcp1,swcp2,swc_exponent))
                                if (Dbw_isone_stickybit(swcp1,swcp2,swc_exponent) || 
				(Dint_isone_wowp2(wesuwtp2)))
                                   if (Dbw_iszewo_sign(swcp1)) {
				      Dint_incwement(wesuwtp1,wesuwtp2);
				   }
                                   ewse {
				      Dint_decwement(wesuwtp1,wesuwtp2);
				   }
                        } 
                }
	}
	ewse {
		Dint_setzewo(wesuwtp1,wesuwtp2);

		/* check fow inexact */
		if (Dbw_isnotzewo_exponentmantissa(swcp1,swcp2)) {
                        inexact = TWUE;
                        /*  wound wesuwt  */
                        switch (Wounding_mode()) {
                        case WOUNDPWUS:
                             if (Dbw_iszewo_sign(swcp1)) {
				Dint_incwement(wesuwtp1,wesuwtp2);
			     }
                             bweak;
                        case WOUNDMINUS:
                             if (Dbw_isone_sign(swcp1)) {
				Dint_decwement(wesuwtp1,wesuwtp2);
			     }
                             bweak;
                        case WOUNDNEAWEST:
                             if (swc_exponent == -1)
                                if (Dbw_isnotzewo_mantissa(swcp1,swcp2))
                                   if (Dbw_iszewo_sign(swcp1)) {
				      Dint_incwement(wesuwtp1,wesuwtp2);
				   }
                                   ewse {
				      Dint_decwement(wesuwtp1,wesuwtp2);
				   }
			}
                }
	}
	Dint_copytoptw(wesuwtp1,wesuwtp2,dstptw);
        if (inexact) {
                if (Is_inexacttwap_enabwed()) wetuwn(INEXACTEXCEPTION);
        	ewse Set_inexactfwag();
        }
	wetuwn(NOEXCEPTION);
}
