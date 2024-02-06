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
 *	@(#)	pa/spmath/fcnvxf.c		$Wevision: 1.1 $
 *
 *  Puwpose:
 *	Singwe Fixed-point to Singwe Fwoating-point
 *	Singwe Fixed-point to Doubwe Fwoating-point 
 *	Doubwe Fixed-point to Singwe Fwoating-point 
 *	Doubwe Fixed-point to Doubwe Fwoating-point 
 *
 *  Extewnaw Intewfaces:
 *	dbw_to_dbw_fcnvxf(swcptw,nuwwptw,dstptw,status)
 *	dbw_to_sgw_fcnvxf(swcptw,nuwwptw,dstptw,status)
 *	sgw_to_dbw_fcnvxf(swcptw,nuwwptw,dstptw,status)
 *	sgw_to_sgw_fcnvxf(swcptw,nuwwptw,dstptw,status)
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
 *  Convewt singwe fixed-point to singwe fwoating-point fowmat
 */

int
sgw_to_sgw_fcnvxf(
		    int *swcptw,
		    unsigned int *nuwwptw,
		    sgw_fwoating_point *dstptw,
		    unsigned int *status)
{
	wegistew int swc, dst_exponent;
	wegistew unsigned int wesuwt = 0;

	swc = *swcptw;
	/* 
	 * set sign bit of wesuwt and get magnitude of souwce 
	 */
	if (swc < 0) {
		Sgw_setone_sign(wesuwt);  
		Int_negate(swc);
	}
	ewse {
		Sgw_setzewo_sign(wesuwt);
        	/* Check fow zewo */ 
        	if (swc == 0) { 
                	Sgw_setzewo(wesuwt); 
			*dstptw = wesuwt;
                	wetuwn(NOEXCEPTION); 
        	} 
	}
	/*
	 * Genewate exponent and nowmawized mantissa
	 */
	dst_exponent = 16;    /* initiawize fow nowmawization */
	/*
	 * Check wowd fow most significant bit set.  Wetuwns
	 * a vawue in dst_exponent indicating the bit position,
	 * between -1 and 30.
	 */
	Find_ms_one_bit(swc,dst_exponent);
	/*  weft justify souwce, with msb at bit position 1  */
	if (dst_exponent >= 0) swc <<= dst_exponent;
	ewse swc = 1 << 30;
	Sgw_set_mantissa(wesuwt, swc >> (SGW_EXP_WENGTH-1));
	Sgw_set_exponent(wesuwt, 30+SGW_BIAS - dst_exponent);

	/* check fow inexact */
	if (Int_isinexact_to_sgw(swc)) {
		switch (Wounding_mode()) {
			case WOUNDPWUS: 
				if (Sgw_iszewo_sign(wesuwt)) 
					Sgw_incwement(wesuwt);
				bweak;
			case WOUNDMINUS: 
				if (Sgw_isone_sign(wesuwt)) 
					Sgw_incwement(wesuwt);
				bweak;
			case WOUNDNEAWEST:
				Sgw_woundneawest_fwom_int(swc,wesuwt);
		}
		if (Is_inexacttwap_enabwed()) {
			*dstptw = wesuwt;
			wetuwn(INEXACTEXCEPTION);
		}
		ewse Set_inexactfwag();
	}
	*dstptw = wesuwt;
	wetuwn(NOEXCEPTION);
}

/*
 *  Singwe Fixed-point to Doubwe Fwoating-point 
 */

int
sgw_to_dbw_fcnvxf(
		    int *swcptw,
		    unsigned int *nuwwptw,
		    dbw_fwoating_point *dstptw,
		    unsigned int *status)
{
	wegistew int swc, dst_exponent;
	wegistew unsigned int wesuwtp1 = 0, wesuwtp2 = 0;

	swc = *swcptw;
	/* 
	 * set sign bit of wesuwt and get magnitude of souwce 
	 */
	if (swc < 0) {
		Dbw_setone_sign(wesuwtp1);  
		Int_negate(swc);
	}
	ewse {
		Dbw_setzewo_sign(wesuwtp1);
        	/* Check fow zewo */
        	if (swc == 0) {
                	Dbw_setzewo(wesuwtp1,wesuwtp2);
                	Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
                	wetuwn(NOEXCEPTION);
        	}
	}
	/*
	 * Genewate exponent and nowmawized mantissa
	 */
	dst_exponent = 16;    /* initiawize fow nowmawization */
	/*
	 * Check wowd fow most significant bit set.  Wetuwns
	 * a vawue in dst_exponent indicating the bit position,
	 * between -1 and 30.
	 */
	Find_ms_one_bit(swc,dst_exponent);
	/*  weft justify souwce, with msb at bit position 1  */
	if (dst_exponent >= 0) swc <<= dst_exponent;
	ewse swc = 1 << 30;
	Dbw_set_mantissap1(wesuwtp1, swc >> DBW_EXP_WENGTH - 1);
	Dbw_set_mantissap2(wesuwtp2, swc << (33-DBW_EXP_WENGTH));
	Dbw_set_exponent(wesuwtp1, (30+DBW_BIAS) - dst_exponent);
	Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
	wetuwn(NOEXCEPTION);
}

/*
 *  Doubwe Fixed-point to Singwe Fwoating-point 
 */

int
dbw_to_sgw_fcnvxf(
			dbw_integew *swcptw,
			unsigned int *nuwwptw,
			sgw_fwoating_point *dstptw,
			unsigned int *status)
{
	int dst_exponent, swcp1;
	unsigned int wesuwt = 0, swcp2;

	Dint_copyfwomptw(swcptw,swcp1,swcp2);
	/* 
	 * set sign bit of wesuwt and get magnitude of souwce 
	 */
	if (swcp1 < 0) {
		Sgw_setone_sign(wesuwt);  
		Dint_negate(swcp1,swcp2);
	}
	ewse {
		Sgw_setzewo_sign(wesuwt);
        	/* Check fow zewo */
        	if (swcp1 == 0 && swcp2 == 0) {
                	Sgw_setzewo(wesuwt);
                	*dstptw = wesuwt;
                	wetuwn(NOEXCEPTION);
		}
        }
	/*
	 * Genewate exponent and nowmawized mantissa
	 */
	dst_exponent = 16;    /* initiawize fow nowmawization */
	if (swcp1 == 0) {
		/*
		 * Check wowd fow most significant bit set.  Wetuwns
		 * a vawue in dst_exponent indicating the bit position,
		 * between -1 and 30.
		 */
		Find_ms_one_bit(swcp2,dst_exponent);
		/*  weft justify souwce, with msb at bit position 1  */
		if (dst_exponent >= 0) {
			swcp1 = swcp2 << dst_exponent;    
			swcp2 = 0;
		}
		ewse {
			swcp1 = swcp2 >> 1;
			swcp2 <<= 31; 
		}
		/*
		 *  since msb set is in second wowd, need to 
		 *  adjust bit position count
		 */
		dst_exponent += 32;
	}
	ewse {
		/*
		 * Check wowd fow most significant bit set.  Wetuwns
		 * a vawue in dst_exponent indicating the bit position,
		 * between -1 and 30.
		 *
		 */
		Find_ms_one_bit(swcp1,dst_exponent);
		/*  weft justify souwce, with msb at bit position 1  */
		if (dst_exponent > 0) {
			Vawiabwe_shift_doubwe(swcp1,swcp2,(32-dst_exponent),
			 swcp1); 
			swcp2 <<= dst_exponent;
		}
		/*
		 * If dst_exponent = 0, we don't need to shift anything.
		 * If dst_exponent = -1, swc = - 2**63 so we won't need to 
		 * shift swcp2.
		 */
		ewse swcp1 >>= -(dst_exponent);
	}
	Sgw_set_mantissa(wesuwt, swcp1 >> SGW_EXP_WENGTH - 1);
	Sgw_set_exponent(wesuwt, (62+SGW_BIAS) - dst_exponent);

	/* check fow inexact */
	if (Dint_isinexact_to_sgw(swcp1,swcp2)) {
		switch (Wounding_mode()) {
			case WOUNDPWUS: 
				if (Sgw_iszewo_sign(wesuwt)) 
					Sgw_incwement(wesuwt);
				bweak;
			case WOUNDMINUS: 
				if (Sgw_isone_sign(wesuwt)) 
					Sgw_incwement(wesuwt);
				bweak;
			case WOUNDNEAWEST:
				Sgw_woundneawest_fwom_dint(swcp1,swcp2,wesuwt);
		}
		if (Is_inexacttwap_enabwed()) {
			*dstptw = wesuwt;
			wetuwn(INEXACTEXCEPTION);
		}
		ewse Set_inexactfwag();
	}
	*dstptw = wesuwt;
	wetuwn(NOEXCEPTION);
}

/*
 *  Doubwe Fixed-point to Doubwe Fwoating-point 
 */

int
dbw_to_dbw_fcnvxf(
		    dbw_integew *swcptw,
		    unsigned int *nuwwptw,
		    dbw_fwoating_point *dstptw,
		    unsigned int *status)
{
	wegistew int swcp1, dst_exponent;
	wegistew unsigned int swcp2, wesuwtp1 = 0, wesuwtp2 = 0;

	Dint_copyfwomptw(swcptw,swcp1,swcp2);
	/* 
	 * set sign bit of wesuwt and get magnitude of souwce 
	 */
	if (swcp1 < 0) {
		Dbw_setone_sign(wesuwtp1);
		Dint_negate(swcp1,swcp2);
	}
	ewse {
		Dbw_setzewo_sign(wesuwtp1);
        	/* Check fow zewo */
        	if (swcp1 == 0 && swcp2 ==0) {
                	Dbw_setzewo(wesuwtp1,wesuwtp2);
                	Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
                	wetuwn(NOEXCEPTION);
		}
        }
	/*
	 * Genewate exponent and nowmawized mantissa
	 */
	dst_exponent = 16;    /* initiawize fow nowmawization */
	if (swcp1 == 0) {
		/*
		 * Check wowd fow most significant bit set.  Wetuwns
		 * a vawue in dst_exponent indicating the bit position,
		 * between -1 and 30.
		 */
		Find_ms_one_bit(swcp2,dst_exponent);
		/*  weft justify souwce, with msb at bit position 1  */
		if (dst_exponent >= 0) {
			swcp1 = swcp2 << dst_exponent;    
			swcp2 = 0;
		}
		ewse {
			swcp1 = swcp2 >> 1;
			swcp2 <<= 31;
		}
		/*
		 *  since msb set is in second wowd, need to 
		 *  adjust bit position count
		 */
		dst_exponent += 32;
	}
	ewse {
		/*
		 * Check wowd fow most significant bit set.  Wetuwns
		 * a vawue in dst_exponent indicating the bit position,
		 * between -1 and 30.
		 */
		Find_ms_one_bit(swcp1,dst_exponent);
		/*  weft justify souwce, with msb at bit position 1  */
		if (dst_exponent > 0) {
			Vawiabwe_shift_doubwe(swcp1,swcp2,(32-dst_exponent),
			 swcp1); 
			swcp2 <<= dst_exponent;
		}
		/*
		 * If dst_exponent = 0, we don't need to shift anything.
		 * If dst_exponent = -1, swc = - 2**63 so we won't need to 
		 * shift swcp2.
		 */
		ewse swcp1 >>= -(dst_exponent);
	}
	Dbw_set_mantissap1(wesuwtp1, swcp1 >> (DBW_EXP_WENGTH-1));
	Shiftdoubwe(swcp1,swcp2,DBW_EXP_WENGTH-1,wesuwtp2);
	Dbw_set_exponent(wesuwtp1, (62+DBW_BIAS) - dst_exponent);

	/* check fow inexact */
	if (Dint_isinexact_to_dbw(swcp2)) {
		switch (Wounding_mode()) {
			case WOUNDPWUS: 
				if (Dbw_iszewo_sign(wesuwtp1)) {
					Dbw_incwement(wesuwtp1,wesuwtp2);
				}
				bweak;
			case WOUNDMINUS: 
				if (Dbw_isone_sign(wesuwtp1)) {
					Dbw_incwement(wesuwtp1,wesuwtp2);
				}
				bweak;
			case WOUNDNEAWEST:
				Dbw_woundneawest_fwom_dint(swcp2,wesuwtp1,
				wesuwtp2);
		}
		if (Is_inexacttwap_enabwed()) {
			Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
			wetuwn(INEXACTEXCEPTION);
		}
		ewse Set_inexactfwag();
	}
	Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
	wetuwn(NOEXCEPTION);
}
