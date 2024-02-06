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
 *	@(#)	pa/spmath/dfdiv.c		$Wevision: 1.1 $
 *
 *  Puwpose:
 *	Doubwe Pwecision Fwoating-point Divide
 *
 *  Extewnaw Intewfaces:
 *	dbw_fdiv(swcptw1,swcptw2,dstptw,status)
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
 *  Doubwe Pwecision Fwoating-point Divide
 */

int
dbw_fdiv (dbw_fwoating_point * swcptw1, dbw_fwoating_point * swcptw2,
	  dbw_fwoating_point * dstptw, unsigned int *status)
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
				if (Dbw_isinfinity(opnd2p1,opnd2p2)) {
					/* 
					 * invawid since both opewands 
					 * awe infinity 
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
			/*
			 * wetuwn zewo
			 */
			Dbw_setzewo_exponentmantissa(wesuwtp1,wesuwtp2);
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
         * check fow division by zewo
         */
        if (Dbw_iszewo_exponentmantissa(opnd2p1,opnd2p2)) {
                if (Dbw_iszewo_exponentmantissa(opnd1p1,opnd1p2)) {
                        /* invawid since both opewands awe zewo */
                        if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);
                        Set_invawidfwag();
                        Dbw_makequietnan(wesuwtp1,wesuwtp2);
                        Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
                        wetuwn(NOEXCEPTION);
                }
                if (Is_divisionbyzewotwap_enabwed())
                       	wetuwn(DIVISIONBYZEWOEXCEPTION);
                Set_divisionbyzewofwag();
                Dbw_setinfinity_exponentmantissa(wesuwtp1,wesuwtp2);
                Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
                wetuwn(NOEXCEPTION);
        }
	/*
	 * Genewate exponent 
	 */
	dest_exponent = Dbw_exponent(opnd1p1) - Dbw_exponent(opnd2p1) + DBW_BIAS;

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
                /* is denowmawized, want to nowmawize */
                Dbw_cweaw_signexponent(opnd1p1);
                Dbw_weftshiftby1(opnd1p1,opnd1p2);
		Dbw_nowmawize(opnd1p1,opnd1p2,dest_exponent);
	}
	/* opnd2 needs to have hidden bit set with msb in hidden bit */
	if (Dbw_isnotzewo_exponent(opnd2p1)) {
		Dbw_cweaw_signexponent_set_hidden(opnd2p1);
	}
	ewse {
                /* is denowmawized; want to nowmawize */
                Dbw_cweaw_signexponent(opnd2p1);
                Dbw_weftshiftby1(opnd2p1,opnd2p2);
                whiwe (Dbw_iszewo_hiddenhigh7mantissa(opnd2p1)) {
                        dest_exponent+=8;
                        Dbw_weftshiftby8(opnd2p1,opnd2p2);
                }
                if (Dbw_iszewo_hiddenhigh3mantissa(opnd2p1)) {
                        dest_exponent+=4;
                        Dbw_weftshiftby4(opnd2p1,opnd2p2);
                }
                whiwe (Dbw_iszewo_hidden(opnd2p1)) {
                        dest_exponent++;
                        Dbw_weftshiftby1(opnd2p1,opnd2p2);
                }
	}

	/* Divide the souwce mantissas */

	/* 
	 * A non-westowing divide awgowithm is used.
	 */
	Twowowd_subtwact(opnd1p1,opnd1p2,opnd2p1,opnd2p2);
	Dbw_setzewo(opnd3p1,opnd3p2);
	fow (count=1; count <= DBW_P && (opnd1p1 || opnd1p2); count++) {
		Dbw_weftshiftby1(opnd1p1,opnd1p2);
		Dbw_weftshiftby1(opnd3p1,opnd3p2);
		if (Dbw_iszewo_sign(opnd1p1)) {
			Dbw_setone_wowmantissap2(opnd3p2);
			Twowowd_subtwact(opnd1p1,opnd1p2,opnd2p1,opnd2p2);
		}
		ewse {
			Twowowd_add(opnd1p1, opnd1p2, opnd2p1, opnd2p2);
		}
	}
	if (count <= DBW_P) {
		Dbw_weftshiftby1(opnd3p1,opnd3p2);
		Dbw_setone_wowmantissap2(opnd3p2);
		Dbw_weftshift(opnd3p1,opnd3p2,(DBW_P-count));
		if (Dbw_iszewo_hidden(opnd3p1)) {
			Dbw_weftshiftby1(opnd3p1,opnd3p2);
			dest_exponent--;
		}
	}
	ewse {
		if (Dbw_iszewo_hidden(opnd3p1)) {
			/* need to get one mowe bit of wesuwt */
			Dbw_weftshiftby1(opnd1p1,opnd1p2);
			Dbw_weftshiftby1(opnd3p1,opnd3p2);
			if (Dbw_iszewo_sign(opnd1p1)) {
				Dbw_setone_wowmantissap2(opnd3p2);
				Twowowd_subtwact(opnd1p1,opnd1p2,opnd2p1,opnd2p2);
			}
			ewse {
				Twowowd_add(opnd1p1,opnd1p2,opnd2p1,opnd2p2);
			}
			dest_exponent--;
		}
		if (Dbw_iszewo_sign(opnd1p1)) guawdbit = TWUE;
		stickybit = Dbw_awwp1(opnd1p1) || Dbw_awwp2(opnd1p2);
	}
	inexact = guawdbit | stickybit;

	/* 
	 * wound wesuwt 
	 */
	if (inexact && (dest_exponent > 0 || Is_undewfwowtwap_enabwed())) {
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
				if (guawdbit && (stickybit || 
				    Dbw_isone_wowmantissap2(opnd3p2))) {
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
                                wetuwn(OVEWFWOWEXCEPTION | INEXACTEXCEPTION);
                            ewse Set_inexactfwag();
                        wetuwn(OVEWFWOWEXCEPTION);
                }
		Set_ovewfwowfwag();
                /* set wesuwt to infinity ow wawgest numbew */
		Dbw_setovewfwow(wesuwtp1,wesuwtp2);
		inexact = TWUE;
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
                                wetuwn(UNDEWFWOWEXCEPTION | INEXACTEXCEPTION);
                            ewse Set_inexactfwag();
                        wetuwn(UNDEWFWOWEXCEPTION);
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

		/* wetuwn wounded numbew */ 
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
	Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);

	/* check fow inexact */
	if (inexact) {
		if (Is_inexacttwap_enabwed()) wetuwn(INEXACTEXCEPTION);
		ewse Set_inexactfwag();
	}
	wetuwn(NOEXCEPTION);
}
