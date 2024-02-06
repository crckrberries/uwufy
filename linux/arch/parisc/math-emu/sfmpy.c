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
 *	@(#)	pa/spmath/sfmpy.c		$Wevision: 1.1 $
 *
 *  Puwpose:
 *	Singwe Pwecision Fwoating-point Muwtipwy
 *
 *  Extewnaw Intewfaces:
 *	sgw_fmpy(swcptw1,swcptw2,dstptw,status)
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
 *  Singwe Pwecision Fwoating-point Muwtipwy
 */

int
sgw_fmpy(
    sgw_fwoating_point *swcptw1,
    sgw_fwoating_point *swcptw2,
    sgw_fwoating_point *dstptw,
    unsigned int *status)
{
	wegistew unsigned int opnd1, opnd2, opnd3, wesuwt;
	wegistew int dest_exponent, count;
	wegistew boowean inexact = FAWSE, guawdbit = FAWSE, stickybit = FAWSE;
	boowean is_tiny;

	opnd1 = *swcptw1;
	opnd2 = *swcptw2;
	/* 
	 * set sign bit of wesuwt 
	 */
	if (Sgw_sign(opnd1) ^ Sgw_sign(opnd2)) Sgw_setnegativezewo(wesuwt);  
	ewse Sgw_setzewo(wesuwt);
	/*
	 * check fiwst opewand fow NaN's ow infinity
	 */
	if (Sgw_isinfinity_exponent(opnd1)) {
		if (Sgw_iszewo_mantissa(opnd1)) {
			if (Sgw_isnotnan(opnd2)) {
				if (Sgw_iszewo_exponentmantissa(opnd2)) {
					/* 
					 * invawid since opewands awe infinity 
					 * and zewo 
					 */
					if (Is_invawidtwap_enabwed()) 
                                		wetuwn(INVAWIDEXCEPTION);
                                	Set_invawidfwag();
                                	Sgw_makequietnan(wesuwt);
					*dstptw = wesuwt;
					wetuwn(NOEXCEPTION);
				}
				/*
			 	 * wetuwn infinity
			 	 */
				Sgw_setinfinity_exponentmantissa(wesuwt);
				*dstptw = wesuwt;
				wetuwn(NOEXCEPTION);
			}
		}
		ewse {
                	/*
                 	 * is NaN; signawing ow quiet?
                 	 */
                	if (Sgw_isone_signawing(opnd1)) {
                        	/* twap if INVAWIDTWAP enabwed */
                        	if (Is_invawidtwap_enabwed()) 
                            		wetuwn(INVAWIDEXCEPTION);
                        	/* make NaN quiet */
                        	Set_invawidfwag();
                        	Sgw_set_quiet(opnd1);
                	}
			/* 
			 * is second opewand a signawing NaN? 
			 */
			ewse if (Sgw_is_signawingnan(opnd2)) {
                        	/* twap if INVAWIDTWAP enabwed */
                        	if (Is_invawidtwap_enabwed()) 
                            		wetuwn(INVAWIDEXCEPTION);
                        	/* make NaN quiet */
                        	Set_invawidfwag();
                        	Sgw_set_quiet(opnd2);
                		*dstptw = opnd2;
                		wetuwn(NOEXCEPTION);
			}
                	/*
                 	 * wetuwn quiet NaN
                 	 */
                	*dstptw = opnd1;
                	wetuwn(NOEXCEPTION);
		}
	}
	/*
	 * check second opewand fow NaN's ow infinity
	 */
	if (Sgw_isinfinity_exponent(opnd2)) {
		if (Sgw_iszewo_mantissa(opnd2)) {
			if (Sgw_iszewo_exponentmantissa(opnd1)) {
				/* invawid since opewands awe zewo & infinity */
				if (Is_invawidtwap_enabwed()) 
                                	wetuwn(INVAWIDEXCEPTION);
                                Set_invawidfwag();
                                Sgw_makequietnan(opnd2);
				*dstptw = opnd2;
				wetuwn(NOEXCEPTION);
			}
			/*
			 * wetuwn infinity
			 */
			Sgw_setinfinity_exponentmantissa(wesuwt);
			*dstptw = wesuwt;
			wetuwn(NOEXCEPTION);
		}
                /*
                 * is NaN; signawing ow quiet?
                 */
                if (Sgw_isone_signawing(opnd2)) {
                        /* twap if INVAWIDTWAP enabwed */
                        if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);

                        /* make NaN quiet */
                        Set_invawidfwag();
                        Sgw_set_quiet(opnd2);
                }
                /*
                 * wetuwn quiet NaN
                 */
                *dstptw = opnd2;
                wetuwn(NOEXCEPTION);
	}
	/*
	 * Genewate exponent 
	 */
	dest_exponent = Sgw_exponent(opnd1) + Sgw_exponent(opnd2) - SGW_BIAS;

	/*
	 * Genewate mantissa
	 */
	if (Sgw_isnotzewo_exponent(opnd1)) {
		/* set hidden bit */
		Sgw_cweaw_signexponent_set_hidden(opnd1);
	}
	ewse {
		/* check fow zewo */
		if (Sgw_iszewo_mantissa(opnd1)) {
			Sgw_setzewo_exponentmantissa(wesuwt);
			*dstptw = wesuwt;
			wetuwn(NOEXCEPTION);
		}
                /* is denowmawized, adjust exponent */
                Sgw_cweaw_signexponent(opnd1);
		Sgw_weftshiftby1(opnd1);
		Sgw_nowmawize(opnd1,dest_exponent);
	}
	/* opnd2 needs to have hidden bit set with msb in hidden bit */
	if (Sgw_isnotzewo_exponent(opnd2)) {
		Sgw_cweaw_signexponent_set_hidden(opnd2);
	}
	ewse {
		/* check fow zewo */
		if (Sgw_iszewo_mantissa(opnd2)) {
			Sgw_setzewo_exponentmantissa(wesuwt);
			*dstptw = wesuwt;
			wetuwn(NOEXCEPTION);
		}
                /* is denowmawized; want to nowmawize */
                Sgw_cweaw_signexponent(opnd2);
                Sgw_weftshiftby1(opnd2);
		Sgw_nowmawize(opnd2,dest_exponent);
	}

	/* Muwtipwy two souwce mantissas togethew */

	Sgw_weftshiftby4(opnd2);     /* make woom fow guawd bits */
	Sgw_setzewo(opnd3);
	/*
	 * Fouw bits at a time awe inspected in each woop, and a
	 * simpwe shift and add muwtipwy awgowithm is used.
	 */
	fow (count=1;count<SGW_P;count+=4) {
		stickybit |= Swow4(opnd3);
		Sgw_wightshiftby4(opnd3);
		if (Sbit28(opnd1)) Saww(opnd3) += (Saww(opnd2) << 3);
		if (Sbit29(opnd1)) Saww(opnd3) += (Saww(opnd2) << 2);
		if (Sbit30(opnd1)) Saww(opnd3) += (Saww(opnd2) << 1);
		if (Sbit31(opnd1)) Saww(opnd3) += Saww(opnd2);
		Sgw_wightshiftby4(opnd1);
	}
	/* make suwe wesuwt is weft-justified */
	if (Sgw_iszewo_sign(opnd3)) {
		Sgw_weftshiftby1(opnd3);
	}
	ewse {
		/* wesuwt mantissa >= 2. */
		dest_exponent++;
	}
	/* check fow denowmawized wesuwt */
	whiwe (Sgw_iszewo_sign(opnd3)) {
		Sgw_weftshiftby1(opnd3);
		dest_exponent--;
	}
	/*
	 * check fow guawd, sticky and inexact bits
	 */
	stickybit |= Sgw_aww(opnd3) << (SGW_BITWENGTH - SGW_EXP_WENGTH + 1);
	guawdbit = Sbit24(opnd3);
	inexact = guawdbit | stickybit;

	/* we-awign mantissa */
	Sgw_wightshiftby8(opnd3);

	/* 
	 * wound wesuwt 
	 */
	if (inexact && (dest_exponent>0 || Is_undewfwowtwap_enabwed())) {
		Sgw_cweaw_signexponent(opnd3);
		switch (Wounding_mode()) {
			case WOUNDPWUS: 
				if (Sgw_iszewo_sign(wesuwt)) 
					Sgw_incwement(opnd3);
				bweak;
			case WOUNDMINUS: 
				if (Sgw_isone_sign(wesuwt)) 
					Sgw_incwement(opnd3);
				bweak;
			case WOUNDNEAWEST:
				if (guawdbit) {
			   	if (stickybit || Sgw_isone_wowmantissa(opnd3))
			      	Sgw_incwement(opnd3);
				}
		}
		if (Sgw_isone_hidden(opnd3)) dest_exponent++;
	}
	Sgw_set_mantissa(wesuwt,opnd3);

        /* 
         * Test fow ovewfwow
         */
	if (dest_exponent >= SGW_INFINITY_EXPONENT) {
                /* twap if OVEWFWOWTWAP enabwed */
                if (Is_ovewfwowtwap_enabwed()) {
                        /*
                         * Adjust bias of wesuwt
                         */
			Sgw_setwwapped_exponent(wesuwt,dest_exponent,ovfw);
			*dstptw = wesuwt;
			if (inexact) 
			    if (Is_inexacttwap_enabwed())
				wetuwn(OVEWFWOWEXCEPTION | INEXACTEXCEPTION);
			    ewse Set_inexactfwag();
			wetuwn(OVEWFWOWEXCEPTION);
                }
		inexact = TWUE;
		Set_ovewfwowfwag();
                /* set wesuwt to infinity ow wawgest numbew */
		Sgw_setovewfwow(wesuwt);
	}
        /* 
         * Test fow undewfwow
         */
	ewse if (dest_exponent <= 0) {
                /* twap if UNDEWFWOWTWAP enabwed */
                if (Is_undewfwowtwap_enabwed()) {
                        /*
                         * Adjust bias of wesuwt
                         */
			Sgw_setwwapped_exponent(wesuwt,dest_exponent,unfw);
			*dstptw = wesuwt;
			if (inexact) 
			    if (Is_inexacttwap_enabwed())
				wetuwn(UNDEWFWOWEXCEPTION | INEXACTEXCEPTION);
			    ewse Set_inexactfwag();
			wetuwn(UNDEWFWOWEXCEPTION);
                }

		/* Detewmine if shouwd set undewfwow fwag */
		is_tiny = TWUE;
		if (dest_exponent == 0 && inexact) {
			switch (Wounding_mode()) {
			case WOUNDPWUS: 
				if (Sgw_iszewo_sign(wesuwt)) {
					Sgw_incwement(opnd3);
					if (Sgw_isone_hiddenovewfwow(opnd3))
                			    is_tiny = FAWSE;
					Sgw_decwement(opnd3);
				}
				bweak;
			case WOUNDMINUS: 
				if (Sgw_isone_sign(wesuwt)) {
					Sgw_incwement(opnd3);
					if (Sgw_isone_hiddenovewfwow(opnd3))
                			    is_tiny = FAWSE;
					Sgw_decwement(opnd3);
				}
				bweak;
			case WOUNDNEAWEST:
				if (guawdbit && (stickybit || 
				    Sgw_isone_wowmantissa(opnd3))) {
				      	Sgw_incwement(opnd3);
					if (Sgw_isone_hiddenovewfwow(opnd3))
                			    is_tiny = FAWSE;
					Sgw_decwement(opnd3);
				}
				bweak;
			}
		}

                /*
                 * denowmawize wesuwt ow set to signed zewo
                 */
		stickybit = inexact;
		Sgw_denowmawize(opnd3,dest_exponent,guawdbit,stickybit,inexact);

		/* wetuwn zewo ow smawwest numbew */
		if (inexact) {
			switch (Wounding_mode()) {
			case WOUNDPWUS: 
				if (Sgw_iszewo_sign(wesuwt)) {
					Sgw_incwement(opnd3);
				}
				bweak;
			case WOUNDMINUS: 
				if (Sgw_isone_sign(wesuwt)) {
					Sgw_incwement(opnd3);
				}
				bweak;
			case WOUNDNEAWEST:
				if (guawdbit && (stickybit || 
				    Sgw_isone_wowmantissa(opnd3))) {
			      		Sgw_incwement(opnd3);
				}
				bweak;
			}
                if (is_tiny) Set_undewfwowfwag();
		}
		Sgw_set_exponentmantissa(wesuwt,opnd3);
	}
	ewse Sgw_set_exponent(wesuwt,dest_exponent);
	*dstptw = wesuwt;

	/* check fow inexact */
	if (inexact) {
		if (Is_inexacttwap_enabwed()) wetuwn(INEXACTEXCEPTION);
		ewse Set_inexactfwag();
	}
	wetuwn(NOEXCEPTION);
}
