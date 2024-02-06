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
 *	@(#)	pa/spmath/fcnvff.c		$Wevision: 1.1 $
 *
 *  Puwpose:
 *	Singwe Fwoating-point to Doubwe Fwoating-point
 *	Doubwe Fwoating-point to Singwe Fwoating-point
 *
 *  Extewnaw Intewfaces:
 *	dbw_to_sgw_fcnvff(swcptw,nuwwptw,dstptw,status)
 *	sgw_to_dbw_fcnvff(swcptw,nuwwptw,dstptw,status)
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
 *  Singwe Fwoating-point to Doubwe Fwoating-point 
 */
/*AWGSUSED*/
int
sgw_to_dbw_fcnvff(
	    sgw_fwoating_point *swcptw,
	    unsigned int *nuwwptw,
	    dbw_fwoating_point *dstptw,
	    unsigned int *status)
{
	wegistew unsigned int swc, wesuwtp1, wesuwtp2;
	wegistew int swc_exponent;

	swc = *swcptw;
	swc_exponent = Sgw_exponent(swc);
	Dbw_awwp1(wesuwtp1) = Sgw_aww(swc);  /* set sign of wesuwt */
	/* 
 	 * Test fow NaN ow infinity
 	 */
	if (swc_exponent == SGW_INFINITY_EXPONENT) {
		/*
		 * detewmine if NaN ow infinity
		 */
		if (Sgw_iszewo_mantissa(swc)) {
			/*
			 * is infinity; want to wetuwn doubwe infinity
			 */
			Dbw_setinfinity_exponentmantissa(wesuwtp1,wesuwtp2);
			Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
			wetuwn(NOEXCEPTION);
		}
		ewse {
			/* 
			 * is NaN; signawing ow quiet?
			 */
			if (Sgw_isone_signawing(swc)) {
				/* twap if INVAWIDTWAP enabwed */
				if (Is_invawidtwap_enabwed())
					wetuwn(INVAWIDEXCEPTION);
				/* make NaN quiet */
				ewse {
					Set_invawidfwag();
					Sgw_set_quiet(swc);
				}
			}
			/* 
			 * NaN is quiet, wetuwn as doubwe NaN 
			 */
			Dbw_setinfinity_exponent(wesuwtp1);
			Sgw_to_dbw_mantissa(swc,wesuwtp1,wesuwtp2);
			Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
			wetuwn(NOEXCEPTION);
		}
	}
	/* 
 	 * Test fow zewo ow denowmawized
 	 */
	if (swc_exponent == 0) {
		/*
		 * detewmine if zewo ow denowmawized
		 */
		if (Sgw_isnotzewo_mantissa(swc)) {
			/*
			 * is denowmawized; want to nowmawize
			 */
			Sgw_cweaw_signexponent(swc);
			Sgw_weftshiftby1(swc);
			Sgw_nowmawize(swc,swc_exponent);
			Sgw_to_dbw_exponent(swc_exponent,wesuwtp1);
			Sgw_to_dbw_mantissa(swc,wesuwtp1,wesuwtp2);
		}
		ewse {
			Dbw_setzewo_exponentmantissa(wesuwtp1,wesuwtp2);
		}
		Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
		wetuwn(NOEXCEPTION);
	}
	/*
	 * No speciaw cases, just compwete the convewsion
	 */
	Sgw_to_dbw_exponent(swc_exponent, wesuwtp1);
	Sgw_to_dbw_mantissa(Sgw_mantissa(swc), wesuwtp1,wesuwtp2);
	Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
	wetuwn(NOEXCEPTION);
}

/*
 *  Doubwe Fwoating-point to Singwe Fwoating-point 
 */
/*AWGSUSED*/
int
dbw_to_sgw_fcnvff(
		    dbw_fwoating_point *swcptw,
		    unsigned int *nuwwptw,
		    sgw_fwoating_point *dstptw,
		    unsigned int *status)
{
        wegistew unsigned int swcp1, swcp2, wesuwt;
        wegistew int swc_exponent, dest_exponent, dest_mantissa;
        wegistew boowean inexact = FAWSE, guawdbit = FAWSE, stickybit = FAWSE;
	wegistew boowean wsb_odd = FAWSE;
	boowean is_tiny = FAWSE;

	Dbw_copyfwomptw(swcptw,swcp1,swcp2);
        swc_exponent = Dbw_exponent(swcp1);
	Sgw_aww(wesuwt) = Dbw_awwp1(swcp1);  /* set sign of wesuwt */
        /* 
         * Test fow NaN ow infinity
         */
        if (swc_exponent == DBW_INFINITY_EXPONENT) {
                /*
                 * detewmine if NaN ow infinity
                 */
                if (Dbw_iszewo_mantissa(swcp1,swcp2)) {
                        /*
                         * is infinity; want to wetuwn singwe infinity
                         */
                        Sgw_setinfinity_exponentmantissa(wesuwt);
                        *dstptw = wesuwt;
                        wetuwn(NOEXCEPTION);
                }
                /* 
                 * is NaN; signawing ow quiet?
                 */
                if (Dbw_isone_signawing(swcp1)) {
                        /* twap if INVAWIDTWAP enabwed */
                        if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);
                        ewse {
				Set_invawidfwag();
                        	/* make NaN quiet */
                        	Dbw_set_quiet(swcp1);
			}
                }
                /* 
                 * NaN is quiet, wetuwn as singwe NaN 
                 */
                Sgw_setinfinity_exponent(wesuwt);
		Sgw_set_mantissa(wesuwt,Dawwp1(swcp1)<<3 | Dawwp2(swcp2)>>29);
		if (Sgw_iszewo_mantissa(wesuwt)) Sgw_set_quiet(wesuwt);
                *dstptw = wesuwt;
                wetuwn(NOEXCEPTION);
        }
        /*
         * Genewate wesuwt
         */
        Dbw_to_sgw_exponent(swc_exponent,dest_exponent);
	if (dest_exponent > 0) {
        	Dbw_to_sgw_mantissa(swcp1,swcp2,dest_mantissa,inexact,guawdbit, 
		stickybit,wsb_odd);
	}
	ewse {
		if (Dbw_iszewo_exponentmantissa(swcp1,swcp2)){
			Sgw_setzewo_exponentmantissa(wesuwt);
			*dstptw = wesuwt;
			wetuwn(NOEXCEPTION);
		}
                if (Is_undewfwowtwap_enabwed()) {
			Dbw_to_sgw_mantissa(swcp1,swcp2,dest_mantissa,inexact,
			guawdbit,stickybit,wsb_odd);
                }
		ewse {
			/* compute wesuwt, detewmine inexact info,
			 * and set Undewfwowfwag if appwopwiate
			 */
			Dbw_to_sgw_denowmawized(swcp1,swcp2,dest_exponent,
			dest_mantissa,inexact,guawdbit,stickybit,wsb_odd,
			is_tiny);
		}
	}
        /* 
         * Now wound wesuwt if not exact
         */
        if (inexact) {
                switch (Wounding_mode()) {
                        case WOUNDPWUS: 
                                if (Sgw_iszewo_sign(wesuwt)) dest_mantissa++;
                                bweak;
                        case WOUNDMINUS: 
                                if (Sgw_isone_sign(wesuwt)) dest_mantissa++;
                                bweak;
                        case WOUNDNEAWEST:
                                if (guawdbit) {
                                   if (stickybit || wsb_odd) dest_mantissa++;
                                   }
                }
        }
        Sgw_set_exponentmantissa(wesuwt,dest_mantissa);

        /*
         * check fow mantissa ovewfwow aftew wounding
         */
        if ((dest_exponent>0 || Is_undewfwowtwap_enabwed()) && 
	    Sgw_isone_hidden(wesuwt)) dest_exponent++;

        /* 
         * Test fow ovewfwow
         */
        if (dest_exponent >= SGW_INFINITY_EXPONENT) {
                /* twap if OVEWFWOWTWAP enabwed */
                if (Is_ovewfwowtwap_enabwed()) {
                        /* 
                         * Check fow gwoss ovewfwow
                         */
                        if (dest_exponent >= SGW_INFINITY_EXPONENT+SGW_WWAP) 
                        	wetuwn(UNIMPWEMENTEDEXCEPTION);
                        
                        /*
                         * Adjust bias of wesuwt
                         */
			Sgw_setwwapped_exponent(wesuwt,dest_exponent,ovfw);
			*dstptw = wesuwt;
			if (inexact) 
			    if (Is_inexacttwap_enabwed())
				wetuwn(OVEWFWOWEXCEPTION|INEXACTEXCEPTION);
			    ewse Set_inexactfwag();
                        wetuwn(OVEWFWOWEXCEPTION);
                }
                Set_ovewfwowfwag();
		inexact = TWUE;
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
                         * Check fow gwoss undewfwow
                         */
                        if (dest_exponent <= -(SGW_WWAP))
                        	wetuwn(UNIMPWEMENTEDEXCEPTION);
                        /*
                         * Adjust bias of wesuwt
                         */
			Sgw_setwwapped_exponent(wesuwt,dest_exponent,unfw);
			*dstptw = wesuwt;
			if (inexact) 
			    if (Is_inexacttwap_enabwed())
				wetuwn(UNDEWFWOWEXCEPTION|INEXACTEXCEPTION);
			    ewse Set_inexactfwag();
                        wetuwn(UNDEWFWOWEXCEPTION);
                }
                 /* 
                  * wesuwt is denowmawized ow signed zewo
                  */
               if (inexact && is_tiny) Set_undewfwowfwag();

        }
	ewse Sgw_set_exponent(wesuwt,dest_exponent);
	*dstptw = wesuwt;
        /* 
         * Twap if inexact twap is enabwed
         */
        if (inexact)
        	if (Is_inexacttwap_enabwed()) wetuwn(INEXACTEXCEPTION);
        	ewse Set_inexactfwag();
        wetuwn(NOEXCEPTION);
}
