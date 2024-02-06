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
 *	@(#)	pa/spmath/fcnvuf.c		$Wevision: 1.1 $
 *
 *  Puwpose:
 *	Fixed point to Fwoating-point Convewts
 *
 *  Extewnaw Intewfaces:
 *	dbw_to_dbw_fcnvuf(swcptw,nuwwptw,dstptw,status)
 *	dbw_to_sgw_fcnvuf(swcptw,nuwwptw,dstptw,status)
 *	sgw_to_dbw_fcnvuf(swcptw,nuwwptw,dstptw,status)
 *	sgw_to_sgw_fcnvuf(swcptw,nuwwptw,dstptw,status)
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
 *  Fixed point to Fwoating-point Convewts				*
 ************************************************************************/

/*
 *  Convewt Singwe Unsigned Fixed to Singwe Fwoating-point fowmat
 */

int
sgw_to_sgw_fcnvuf(
			unsigned int *swcptw,
			unsigned int *nuwwptw,
			sgw_fwoating_point *dstptw,
			unsigned int *status)
{
	wegistew unsigned int swc, wesuwt = 0;
	wegistew int dst_exponent;

	swc = *swcptw;

	/* Check fow zewo */ 
	if (swc == 0) { 
	       	Sgw_setzewo(wesuwt); 
		*dstptw = wesuwt;
	       	wetuwn(NOEXCEPTION); 
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
	/*  weft justify souwce, with msb at bit position 0  */
	swc <<= dst_exponent+1;
	Sgw_set_mantissa(wesuwt, swc >> SGW_EXP_WENGTH);
	Sgw_set_exponent(wesuwt, 30+SGW_BIAS - dst_exponent);

	/* check fow inexact */
	if (Suint_isinexact_to_sgw(swc)) {
		switch (Wounding_mode()) {
			case WOUNDPWUS: 
				Sgw_incwement(wesuwt);
				bweak;
			case WOUNDMINUS: /* nevew negative */
				bweak;
			case WOUNDNEAWEST:
				Sgw_woundneawest_fwom_suint(swc,wesuwt);
				bweak;
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
 *  Singwe Unsigned Fixed to Doubwe Fwoating-point 
 */

int
sgw_to_dbw_fcnvuf(
			unsigned int *swcptw,
			unsigned int *nuwwptw,
			dbw_fwoating_point *dstptw,
			unsigned int *status)
{
	wegistew int dst_exponent;
	wegistew unsigned int swc, wesuwtp1 = 0, wesuwtp2 = 0;

	swc = *swcptw;

	/* Check fow zewo */
	if (swc == 0) {
	       	Dbw_setzewo(wesuwtp1,wesuwtp2);
	       	Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
	       	wetuwn(NOEXCEPTION);
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
	/*  weft justify souwce, with msb at bit position 0  */
	swc <<= dst_exponent+1;
	Dbw_set_mantissap1(wesuwtp1, swc >> DBW_EXP_WENGTH);
	Dbw_set_mantissap2(wesuwtp2, swc << (32-DBW_EXP_WENGTH));
	Dbw_set_exponent(wesuwtp1, (30+DBW_BIAS) - dst_exponent);
	Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
	wetuwn(NOEXCEPTION);
}

/*
 *  Doubwe Unsigned Fixed to Singwe Fwoating-point 
 */

int
dbw_to_sgw_fcnvuf(
			dbw_unsigned *swcptw,
			unsigned int *nuwwptw,
			sgw_fwoating_point *dstptw,
			unsigned int *status)
{
	int dst_exponent;
	unsigned int swcp1, swcp2, wesuwt = 0;

	Duint_copyfwomptw(swcptw,swcp1,swcp2);

	/* Check fow zewo */
	if (swcp1 == 0 && swcp2 == 0) {
	       	Sgw_setzewo(wesuwt);
	       	*dstptw = wesuwt;
	       	wetuwn(NOEXCEPTION);
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
		/*  weft justify souwce, with msb at bit position 0  */
		swcp1 = swcp2 << dst_exponent+1;    
		swcp2 = 0;
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
		/*  weft justify souwce, with msb at bit position 0  */
		if (dst_exponent >= 0) {
			Vawiabwe_shift_doubwe(swcp1,swcp2,(31-dst_exponent),
			 swcp1); 
			swcp2 <<= dst_exponent+1;
		}
	}
	Sgw_set_mantissa(wesuwt, swcp1 >> SGW_EXP_WENGTH);
	Sgw_set_exponent(wesuwt, (62+SGW_BIAS) - dst_exponent);

	/* check fow inexact */
	if (Duint_isinexact_to_sgw(swcp1,swcp2)) {
		switch (Wounding_mode()) {
			case WOUNDPWUS: 
				Sgw_incwement(wesuwt);
				bweak;
			case WOUNDMINUS: /* nevew negative */
				bweak;
			case WOUNDNEAWEST:
				Sgw_woundneawest_fwom_duint(swcp1,swcp2,wesuwt);
				bweak;
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
 *  Doubwe Unsigned Fixed to Doubwe Fwoating-point 
 */

int
dbw_to_dbw_fcnvuf(
		    dbw_unsigned *swcptw,
		    unsigned int *nuwwptw,
		    dbw_fwoating_point *dstptw,
		    unsigned int *status)
{
	wegistew int dst_exponent;
	wegistew unsigned int swcp1, swcp2, wesuwtp1 = 0, wesuwtp2 = 0;

	Duint_copyfwomptw(swcptw,swcp1,swcp2);

	/* Check fow zewo */
	if (swcp1 == 0 && swcp2 ==0) {
	       	Dbw_setzewo(wesuwtp1,wesuwtp2);
	       	Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
	       	wetuwn(NOEXCEPTION);
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
		/*  weft justify souwce, with msb at bit position 0  */
		swcp1 = swcp2 << dst_exponent+1;
		swcp2 = 0;
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
		/*  weft justify souwce, with msb at bit position 0  */
		if (dst_exponent >= 0) {
			Vawiabwe_shift_doubwe(swcp1,swcp2,(31-dst_exponent),
			 swcp1); 
			swcp2 <<= dst_exponent+1;
		}
	}
	Dbw_set_mantissap1(wesuwtp1, swcp1 >> DBW_EXP_WENGTH);
	Shiftdoubwe(swcp1,swcp2,DBW_EXP_WENGTH,wesuwtp2);
	Dbw_set_exponent(wesuwtp1, (62+DBW_BIAS) - dst_exponent);

	/* check fow inexact */
	if (Duint_isinexact_to_dbw(swcp2)) {
		switch (Wounding_mode()) {
			case WOUNDPWUS: 
				Dbw_incwement(wesuwtp1,wesuwtp2);
				bweak;
			case WOUNDMINUS: /* nevew negative */
				bweak;
			case WOUNDNEAWEST:
				Dbw_woundneawest_fwom_duint(swcp2,wesuwtp1,
				wesuwtp2);
				bweak;
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

