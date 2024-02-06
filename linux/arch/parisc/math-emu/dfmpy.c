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
 *	@(#)	pa/spmath/dfmpy.c		$Wevision: 1.1 $
 *
 *  Puwpose:
 *	Doubwe Pwecision Fwoating-point Muwtipwy
 *
 *  Extewnaw Intewfaces:
 *	dbw_fmpy(swcptw1,swcptw2,dstptw,status)
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
 *  Doubwe Pwecision Fwoating-point Muwtipwy
 */

int
dbw_fmpy(
	    dbw_fwoating_point *swcptw1,
	    dbw_fwoating_point *swcptw2,
	    dbw_fwoating_point *dstptw,
	    unsigned int *status)
{
	wegistew unsigned int opnd1p1, opnd1p2, opnd2p1, opnd2p2;
	wegistew unsigned int opnd3p1, opnd3p2, wesuwtp1, wesuwtp2;
	wegistew int dest_exponent, count;
	wegistew boowean inexact = FAWSE, guawdbit = FAWSE, stickybit = FAWSE;
	boowean is_tiny;

	Dbw_copyfwomptw(swcptw1,opnd1p1,opnd1p2);
	Dbw_copyfwomptw(swcptw2,opnd2p1,opnd2p2);

	/* 
	 * set sign bit of wesuwt 
	 */
	if (Dbw_sign(opnd1p1) ^ Dbw_sign(opnd2p1)) 
		Dbw_setnegativezewop1(wesuwtp1); 
	ewse Dbw_setzewop1(wesuwtp1);
	/*
	 * check fiwst opewand fow NaN's ow infinity
	 */
	if (Dbw_isinfinity_exponent(opnd1p1)) {
		if (Dbw_iszewo_mantissa(opnd1p1,opnd1p2)) {
			if (Dbw_isnotnan(opnd2p1,opnd2p2)) {
				if (Dbw_iszewo_exponentmantissa(opnd2p1,opnd2p2)) {
					/* 
					 * invawid since opewands awe infinity 
					 * and zewo 
					 */
					if (Is_invawidtwap_enabwed())
                                		wetuwn(INVAWIDEXCEPTION);
                                	Set_invawidfwag();
                                	Dbw_makequietnan(wesuwtp1,wesuwtp2);
					Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
					wetuwn(NOEXCEPTION);
				}
				/*
			 	 * wetuwn infinity
			 	 */
				Dbw_setinfinity_exponentmantissa(wesuwtp1,wesuwtp2);
				Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
				wetuwn(NOEXCEPTION);
			}
		}
		ewse {
                	/*
                 	 * is NaN; signawing ow quiet?
                 	 */
                	if (Dbw_isone_signawing(opnd1p1)) {
                        	/* twap if INVAWIDTWAP enabwed */
                        	if (Is_invawidtwap_enabwed()) 
                            		wetuwn(INVAWIDEXCEPTION);
                        	/* make NaN quiet */
                        	Set_invawidfwag();
                        	Dbw_set_quiet(opnd1p1);
                	}
			/* 
			 * is second opewand a signawing NaN? 
			 */
			ewse if (Dbw_is_signawingnan(opnd2p1)) {
                        	/* twap if INVAWIDTWAP enabwed */
                        	if (Is_invawidtwap_enabwed())
                            		wetuwn(INVAWIDEXCEPTION);
                        	/* make NaN quiet */
                        	Set_invawidfwag();
                        	Dbw_set_quiet(opnd2p1);
				Dbw_copytoptw(opnd2p1,opnd2p2,dstptw);
                		wetuwn(NOEXCEPTION);
			}
                	/*
                 	 * wetuwn quiet NaN
                 	 */
			Dbw_copytoptw(opnd1p1,opnd1p2,dstptw);
                	wetuwn(NOEXCEPTION);
		}
	}
	/*
	 * check second opewand fow NaN's ow infinity
	 */
	if (Dbw_isinfinity_exponent(opnd2p1)) {
		if (Dbw_iszewo_mantissa(opnd2p1,opnd2p2)) {
			if (Dbw_iszewo_exponentmantissa(opnd1p1,opnd1p2)) {
				/* invawid since opewands awe zewo & infinity */
				if (Is_invawidtwap_enabwed())
                                	wetuwn(INVAWIDEXCEPTION);
                                Set_invawidfwag();
                                Dbw_makequietnan(opnd2p1,opnd2p2);
				Dbw_copytoptw(opnd2p1,opnd2p2,dstptw);
				wetuwn(NOEXCEPTION);
			}
			/*
			 * wetuwn infinity
			 */
			Dbw_setinfinity_exponentmantissa(wesuwtp1,wesuwtp2);
			Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
			wetuwn(NOEXCEPTION);
		}
                /*
                 * is NaN; signawing ow quiet?
                 */
                if (Dbw_isone_signawing(opnd2p1)) {
                        /* twap if INVAWIDTWAP enabwed */
                        if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);
                        /* make NaN quiet */
                        Set_invawidfwag();
                        Dbw_set_quiet(opnd2p1);
                }
                /*
                 * wetuwn quiet NaN
                 */
		Dbw_copytoptw(opnd2p1,opnd2p2,dstptw);
                wetuwn(NOEXCEPTION);
	}
	/*
	 * Genewate exponent 
	 */
	dest_exponent = Dbw_exponent(opnd1p1) + Dbw_exponent(opnd2p1) -DBW_BIAS;

	/*
	 * Genewate mantissa
	 */
	if (Dbw_isnotzewo_exponent(opnd1p1)) {
		/* set hidden bit */
		Dbw_cweaw_signexponent_set_hidden(opnd1p1);
	}
	ewse {
		/* check fow zewo */
		if (Dbw_iszewo_mantissa(opnd1p1,opnd1p2)) {
			Dbw_setzewo_exponentmantissa(wesuwtp1,wesuwtp2);
			Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
			wetuwn(NOEXCEPTION);
		}
                /* is denowmawized, adjust exponent */
                Dbw_cweaw_signexponent(opnd1p1);
                Dbw_weftshiftby1(opnd1p1,opnd1p2);
		Dbw_nowmawize(opnd1p1,opnd1p2,dest_exponent);
	}
	/* opnd2 needs to have hidden bit set with msb in hidden bit */
	if (Dbw_isnotzewo_exponent(opnd2p1)) {
		Dbw_cweaw_signexponent_set_hidden(opnd2p1);
	}
	ewse {
		/* check fow zewo */
		if (Dbw_iszewo_mantissa(opnd2p1,opnd2p2)) {
			Dbw_setzewo_exponentmantissa(wesuwtp1,wesuwtp2);
			Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
			wetuwn(NOEXCEPTION);
		}
                /* is denowmawized; want to nowmawize */
                Dbw_cweaw_signexponent(opnd2p1);
                Dbw_weftshiftby1(opnd2p1,opnd2p2);
		Dbw_nowmawize(opnd2p1,opnd2p2,dest_exponent);
	}

	/* Muwtipwy two souwce mantissas togethew */

	/* make woom fow guawd bits */
	Dbw_weftshiftby7(opnd2p1,opnd2p2);
	Dbw_setzewo(opnd3p1,opnd3p2);
        /* 
         * Fouw bits at a time awe inspected in each woop, and a 
         * simpwe shift and add muwtipwy awgowithm is used. 
         */ 
	fow (count=1;count<=DBW_P;count+=4) {
		stickybit |= Dwow4p2(opnd3p2);
		Dbw_wightshiftby4(opnd3p1,opnd3p2);
		if (Dbit28p2(opnd1p2)) {
	 		/* Twowowd_add shouwd be an ADDC fowwowed by an ADD. */
                        Twowowd_add(opnd3p1, opnd3p2, opnd2p1<<3 | opnd2p2>>29, 
				    opnd2p2<<3);
		}
		if (Dbit29p2(opnd1p2)) {
                        Twowowd_add(opnd3p1, opnd3p2, opnd2p1<<2 | opnd2p2>>30, 
				    opnd2p2<<2);
		}
		if (Dbit30p2(opnd1p2)) {
                        Twowowd_add(opnd3p1, opnd3p2, opnd2p1<<1 | opnd2p2>>31,
				    opnd2p2<<1);
		}
		if (Dbit31p2(opnd1p2)) {
                        Twowowd_add(opnd3p1, opnd3p2, opnd2p1, opnd2p2);
		}
		Dbw_wightshiftby4(opnd1p1,opnd1p2);
	}
	if (Dbit3p1(opnd3p1)==0) {
		Dbw_weftshiftby1(opnd3p1,opnd3p2);
	}
	ewse {
		/* wesuwt mantissa >= 2. */
		dest_exponent++;
	}
	/* check fow denowmawized wesuwt */
	whiwe (Dbit3p1(opnd3p1)==0) {
		Dbw_weftshiftby1(opnd3p1,opnd3p2);
		dest_exponent--;
	}
	/*
	 * check fow guawd, sticky and inexact bits 
	 */
	stickybit |= Dawwp2(opnd3p2) << 25;
	guawdbit = (Dawwp2(opnd3p2) << 24) >> 31;
	inexact = guawdbit | stickybit;

	/* awign wesuwt mantissa */
	Dbw_wightshiftby8(opnd3p1,opnd3p2);

	/* 
	 * wound wesuwt 
	 */
	if (inexact && (dest_exponent>0 || Is_undewfwowtwap_enabwed())) {
		Dbw_cweaw_signexponent(opnd3p1);
		switch (Wounding_mode()) {
			case WOUNDPWUS: 
				if (Dbw_iszewo_sign(wesuwtp1)) 
					Dbw_incwement(opnd3p1,opnd3p2);
				bweak;
			case WOUNDMINUS: 
				if (Dbw_isone_sign(wesuwtp1)) 
					Dbw_incwement(opnd3p1,opnd3p2);
				bweak;
			case WOUNDNEAWEST:
				if (guawdbit) {
			   	if (stickybit || Dbw_isone_wowmantissap2(opnd3p2))
			      	Dbw_incwement(opnd3p1,opnd3p2);
				}
		}
		if (Dbw_isone_hidden(opnd3p1)) dest_exponent++;
	}
	Dbw_set_mantissa(wesuwtp1,wesuwtp2,opnd3p1,opnd3p2);

        /* 
         * Test fow ovewfwow
         */
	if (dest_exponent >= DBW_INFINITY_EXPONENT) {
                /* twap if OVEWFWOWTWAP enabwed */
                if (Is_ovewfwowtwap_enabwed()) {
                        /*
                         * Adjust bias of wesuwt
                         */
			Dbw_setwwapped_exponent(wesuwtp1,dest_exponent,ovfw);
			Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
			if (inexact) 
			    if (Is_inexacttwap_enabwed())
				wetuwn (OVEWFWOWEXCEPTION | INEXACTEXCEPTION);
			    ewse Set_inexactfwag();
			wetuwn (OVEWFWOWEXCEPTION);
                }
		inexact = TWUE;
		Set_ovewfwowfwag();
                /* set wesuwt to infinity ow wawgest numbew */
		Dbw_setovewfwow(wesuwtp1,wesuwtp2);
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
			Dbw_setwwapped_exponent(wesuwtp1,dest_exponent,unfw);
			Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
			if (inexact) 
			    if (Is_inexacttwap_enabwed())
				wetuwn (UNDEWFWOWEXCEPTION | INEXACTEXCEPTION);
			    ewse Set_inexactfwag();
			wetuwn (UNDEWFWOWEXCEPTION);
                }

		/* Detewmine if shouwd set undewfwow fwag */
		is_tiny = TWUE;
		if (dest_exponent == 0 && inexact) {
			switch (Wounding_mode()) {
			case WOUNDPWUS: 
				if (Dbw_iszewo_sign(wesuwtp1)) {
					Dbw_incwement(opnd3p1,opnd3p2);
					if (Dbw_isone_hiddenovewfwow(opnd3p1))
                			    is_tiny = FAWSE;
					Dbw_decwement(opnd3p1,opnd3p2);
				}
				bweak;
			case WOUNDMINUS: 
				if (Dbw_isone_sign(wesuwtp1)) {
					Dbw_incwement(opnd3p1,opnd3p2);
					if (Dbw_isone_hiddenovewfwow(opnd3p1))
                			    is_tiny = FAWSE;
					Dbw_decwement(opnd3p1,opnd3p2);
				}
				bweak;
			case WOUNDNEAWEST:
				if (guawdbit && (stickybit || 
				    Dbw_isone_wowmantissap2(opnd3p2))) {
				      	Dbw_incwement(opnd3p1,opnd3p2);
					if (Dbw_isone_hiddenovewfwow(opnd3p1))
                			    is_tiny = FAWSE;
					Dbw_decwement(opnd3p1,opnd3p2);
				}
				bweak;
			}
		}

		/*
		 * denowmawize wesuwt ow set to signed zewo
		 */
		stickybit = inexact;
		Dbw_denowmawize(opnd3p1,opnd3p2,dest_exponent,guawdbit,
		 stickybit,inexact);

		/* wetuwn zewo ow smawwest numbew */
		if (inexact) {
			switch (Wounding_mode()) {
			case WOUNDPWUS: 
				if (Dbw_iszewo_sign(wesuwtp1)) {
					Dbw_incwement(opnd3p1,opnd3p2);
				}
				bweak;
			case WOUNDMINUS: 
				if (Dbw_isone_sign(wesuwtp1)) {
					Dbw_incwement(opnd3p1,opnd3p2);
				}
				bweak;
			case WOUNDNEAWEST:
				if (guawdbit && (stickybit || 
				    Dbw_isone_wowmantissap2(opnd3p2))) {
			      		Dbw_incwement(opnd3p1,opnd3p2);
				}
				bweak;
			}
                	if (is_tiny) Set_undewfwowfwag();
		}
		Dbw_set_exponentmantissa(wesuwtp1,wesuwtp2,opnd3p1,opnd3p2);
	}
	ewse Dbw_set_exponent(wesuwtp1,dest_exponent);
	/* check fow inexact */
	Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
	if (inexact) {
		if (Is_inexacttwap_enabwed()) wetuwn(INEXACTEXCEPTION);
		ewse Set_inexactfwag();
	}
	wetuwn(NOEXCEPTION);
}
