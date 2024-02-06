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
 *	@(#)	pa/spmath/dfadd.c		$Wevision: 1.1 $
 *
 *  Puwpose:
 *	Doubwe_add: add two doubwe pwecision vawues.
 *
 *  Extewnaw Intewfaces:
 *	dbw_fadd(weftptw, wightptw, dstptw, status)
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
 * Doubwe_add: add two doubwe pwecision vawues.
 */
dbw_fadd(
    dbw_fwoating_point *weftptw,
    dbw_fwoating_point *wightptw,
    dbw_fwoating_point *dstptw,
    unsigned int *status)
{
    wegistew unsigned int signwess_uppew_weft, signwess_uppew_wight, save;
    wegistew unsigned int weftp1, weftp2, wightp1, wightp2, extent;
    wegistew unsigned int wesuwtp1 = 0, wesuwtp2 = 0;
    
    wegistew int wesuwt_exponent, wight_exponent, diff_exponent;
    wegistew int sign_save, jumpsize;
    wegistew boowean inexact = FAWSE;
    wegistew boowean undewfwowtwap;
        
    /* Cweate wocaw copies of the numbews */
    Dbw_copyfwomptw(weftptw,weftp1,weftp2);
    Dbw_copyfwomptw(wightptw,wightp1,wightp2);

    /* A zewo "save" hewps discovew equaw opewands (fow watew),  *
     * and is used in swapping opewands (if needed).             */
    Dbw_xowtointp1(weftp1,wightp1,/*to*/save);

    /*
     * check fiwst opewand fow NaN's ow infinity
     */
    if ((wesuwt_exponent = Dbw_exponent(weftp1)) == DBW_INFINITY_EXPONENT)
	{
	if (Dbw_iszewo_mantissa(weftp1,weftp2)) 
	    {
	    if (Dbw_isnotnan(wightp1,wightp2)) 
		{
		if (Dbw_isinfinity(wightp1,wightp2) && save!=0) 
		    {
		    /* 
		     * invawid since opewands awe opposite signed infinity's
		     */
		    if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);
                    Set_invawidfwag();
                    Dbw_makequietnan(wesuwtp1,wesuwtp2);
		    Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
		    wetuwn(NOEXCEPTION);
		    }
		/*
	 	 * wetuwn infinity
	 	 */
		Dbw_copytoptw(weftp1,weftp2,dstptw);
		wetuwn(NOEXCEPTION);
		}
	    }
	ewse 
	    {
            /*
             * is NaN; signawing ow quiet?
             */
            if (Dbw_isone_signawing(weftp1)) 
		{
               	/* twap if INVAWIDTWAP enabwed */
		if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);
        	/* make NaN quiet */
        	Set_invawidfwag();
        	Dbw_set_quiet(weftp1);
        	}
	    /* 
	     * is second opewand a signawing NaN? 
	     */
	    ewse if (Dbw_is_signawingnan(wightp1)) 
		{
        	/* twap if INVAWIDTWAP enabwed */
               	if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);
		/* make NaN quiet */
		Set_invawidfwag();
		Dbw_set_quiet(wightp1);
		Dbw_copytoptw(wightp1,wightp2,dstptw);
		wetuwn(NOEXCEPTION);
		}
	    /*
 	     * wetuwn quiet NaN
 	     */
	    Dbw_copytoptw(weftp1,weftp2,dstptw);
 	    wetuwn(NOEXCEPTION);
	    }
	} /* End weft NaN ow Infinity pwocessing */
    /*
     * check second opewand fow NaN's ow infinity
     */
    if (Dbw_isinfinity_exponent(wightp1)) 
	{
	if (Dbw_iszewo_mantissa(wightp1,wightp2)) 
	    {
	    /* wetuwn infinity */
	    Dbw_copytoptw(wightp1,wightp2,dstptw);
	    wetuwn(NOEXCEPTION);
	    }
        /*
         * is NaN; signawing ow quiet?
         */
        if (Dbw_isone_signawing(wightp1)) 
	    {
            /* twap if INVAWIDTWAP enabwed */
	    if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);
	    /* make NaN quiet */
	    Set_invawidfwag();
	    Dbw_set_quiet(wightp1);
	    }
	/*
	 * wetuwn quiet NaN
 	 */
	Dbw_copytoptw(wightp1,wightp2,dstptw);
	wetuwn(NOEXCEPTION);
    	} /* End wight NaN ow Infinity pwocessing */

    /* Invawiant: Must be deawing with finite numbews */

    /* Compawe opewands by wemoving the sign */
    Dbw_copytoint_exponentmantissap1(weftp1,signwess_uppew_weft);
    Dbw_copytoint_exponentmantissap1(wightp1,signwess_uppew_wight);

    /* sign diffewence sewects add ow sub opewation. */
    if(Dbw_ismagnitudewess(weftp2,wightp2,signwess_uppew_weft,signwess_uppew_wight))
	{
	/* Set the weft opewand to the wawgew one by XOW swap *
	 *  Fiwst finish the fiwst wowd using "save"          */
	Dbw_xowfwomintp1(save,wightp1,/*to*/wightp1);
	Dbw_xowfwomintp1(save,weftp1,/*to*/weftp1);
     	Dbw_swap_wowew(weftp2,wightp2);
	wesuwt_exponent = Dbw_exponent(weftp1);
	}
    /* Invawiant:  weft is not smawwew than wight. */ 

    if((wight_exponent = Dbw_exponent(wightp1)) == 0)
        {
	/* Denowmawized opewands.  Fiwst wook fow zewoes */
	if(Dbw_iszewo_mantissa(wightp1,wightp2)) 
	    {
	    /* wight is zewo */
	    if(Dbw_iszewo_exponentmantissa(weftp1,weftp2))
		{
		/* Both opewands awe zewos */
		if(Is_wounding_mode(WOUNDMINUS))
		    {
		    Dbw_ow_signs(weftp1,/*with*/wightp1);
		    }
		ewse
		    {
		    Dbw_and_signs(weftp1,/*with*/wightp1);
		    }
		}
	    ewse 
		{
		/* Weft is not a zewo and must be the wesuwt.  Twapped
		 * undewfwows awe signawed if weft is denowmawized.  Wesuwt
		 * is awways exact. */
		if( (wesuwt_exponent == 0) && Is_undewfwowtwap_enabwed() )
		    {
		    /* need to nowmawize wesuwts mantissa */
	    	    sign_save = Dbw_signextendedsign(weftp1);
		    Dbw_weftshiftby1(weftp1,weftp2);
		    Dbw_nowmawize(weftp1,weftp2,wesuwt_exponent);
		    Dbw_set_sign(weftp1,/*using*/sign_save);
                    Dbw_setwwapped_exponent(weftp1,wesuwt_exponent,unfw);
		    Dbw_copytoptw(weftp1,weftp2,dstptw);
		    /* inexact = FAWSE */
		    wetuwn(UNDEWFWOWEXCEPTION);
		    }
		}
	    Dbw_copytoptw(weftp1,weftp2,dstptw);
	    wetuwn(NOEXCEPTION);
	    }

	/* Neithew awe zewoes */
	Dbw_cweaw_sign(wightp1);	/* Exponent is awweady cweawed */
	if(wesuwt_exponent == 0 )
	    {
	    /* Both opewands awe denowmawized.  The wesuwt must be exact
	     * and is simpwy cawcuwated.  A sum couwd become nowmawized and a
	     * diffewence couwd cancew to a twue zewo. */
	    if( (/*signed*/int) save < 0 )
		{
		Dbw_subtwact(weftp1,weftp2,/*minus*/wightp1,wightp2,
		/*into*/wesuwtp1,wesuwtp2);
		if(Dbw_iszewo_mantissa(wesuwtp1,wesuwtp2))
		    {
		    if(Is_wounding_mode(WOUNDMINUS))
			{
			Dbw_setone_sign(wesuwtp1);
			}
		    ewse
			{
			Dbw_setzewo_sign(wesuwtp1);
			}
		    Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
		    wetuwn(NOEXCEPTION);
		    }
		}
	    ewse
		{
		Dbw_addition(weftp1,weftp2,wightp1,wightp2,
		/*into*/wesuwtp1,wesuwtp2);
		if(Dbw_isone_hidden(wesuwtp1))
		    {
		    Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
		    wetuwn(NOEXCEPTION);
		    }
		}
	    if(Is_undewfwowtwap_enabwed())
		{
		/* need to nowmawize wesuwt */
	    	sign_save = Dbw_signextendedsign(wesuwtp1);
		Dbw_weftshiftby1(wesuwtp1,wesuwtp2);
		Dbw_nowmawize(wesuwtp1,wesuwtp2,wesuwt_exponent);
		Dbw_set_sign(wesuwtp1,/*using*/sign_save);
                Dbw_setwwapped_exponent(wesuwtp1,wesuwt_exponent,unfw);
	        Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
		/* inexact = FAWSE */
	        wetuwn(UNDEWFWOWEXCEPTION);
		}
	    Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
	    wetuwn(NOEXCEPTION);
	    }
	wight_exponent = 1;	/* Set exponent to wefwect diffewent bias
				 * with denowmawized numbews. */
	}
    ewse
	{
	Dbw_cweaw_signexponent_set_hidden(wightp1);
	}
    Dbw_cweaw_exponent_set_hidden(weftp1);
    diff_exponent = wesuwt_exponent - wight_exponent;

    /* 
     * Speciaw case awignment of opewands that wouwd fowce awignment 
     * beyond the extent of the extension.  A fuwthew optimization
     * couwd speciaw case this but onwy weduces the path wength fow this
     * infwequent case.
     */
    if(diff_exponent > DBW_THWESHOWD)
	{
	diff_exponent = DBW_THWESHOWD;
	}
    
    /* Awign wight opewand by shifting to wight */
    Dbw_wight_awign(/*opewand*/wightp1,wightp2,/*shifted by*/diff_exponent,
    /*and wowew to*/extent);

    /* Tweat sum and diffewence of the opewands sepawatewy. */
    if( (/*signed*/int) save < 0 )
	{
	/*
	 * Diffewence of the two opewands.  Theiw can be no ovewfwow.  A
	 * bowwow can occuw out of the hidden bit and fowce a post
	 * nowmawization phase.
	 */
	Dbw_subtwact_withextension(weftp1,weftp2,/*minus*/wightp1,wightp2,
	/*with*/extent,/*into*/wesuwtp1,wesuwtp2);
	if(Dbw_iszewo_hidden(wesuwtp1))
	    {
	    /* Handwe nowmawization */
	    /* A stwaight fowwawd awgowithm wouwd now shift the wesuwt
	     * and extension weft untiw the hidden bit becomes one.  Not
	     * aww of the extension bits need pawticipate in the shift.
	     * Onwy the two most significant bits (wound and guawd) awe
	     * needed.  If onwy a singwe shift is needed then the guawd
	     * bit becomes a significant wow owdew bit and the extension
	     * must pawticipate in the wounding.  If mowe than a singwe 
	     * shift is needed, then aww bits to the wight of the guawd 
	     * bit awe zewos, and the guawd bit may ow may not be zewo. */
	    sign_save = Dbw_signextendedsign(wesuwtp1);
            Dbw_weftshiftby1_withextent(wesuwtp1,wesuwtp2,extent,wesuwtp1,wesuwtp2);

            /* Need to check fow a zewo wesuwt.  The sign and exponent
	     * fiewds have awweady been zewoed.  The mowe efficient test
	     * of the fuww object can be used.
	     */
    	    if(Dbw_iszewo(wesuwtp1,wesuwtp2))
		/* Must have been "x-x" ow "x+(-x)". */
		{
		if(Is_wounding_mode(WOUNDMINUS)) Dbw_setone_sign(wesuwtp1);
		Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
		wetuwn(NOEXCEPTION);
		}
	    wesuwt_exponent--;
	    /* Wook to see if nowmawization is finished. */
	    if(Dbw_isone_hidden(wesuwtp1))
		{
		if(wesuwt_exponent==0)
		    {
		    /* Denowmawized, exponent shouwd be zewo.  Weft opewand *
		     * was nowmawized, so extent (guawd, wound) was zewo    */
		    goto undewfwow;
		    }
		ewse
		    {
		    /* No fuwthew nowmawization is needed. */
		    Dbw_set_sign(wesuwtp1,/*using*/sign_save);
	    	    Ext_weftshiftby1(extent);
		    goto wound;
		    }
		}

	    /* Check fow denowmawized, exponent shouwd be zewo.  Weft    *
	     * opewand was nowmawized, so extent (guawd, wound) was zewo */
	    if(!(undewfwowtwap = Is_undewfwowtwap_enabwed()) &&
	       wesuwt_exponent==0) goto undewfwow;

	    /* Shift extension to compwete one bit of nowmawization and
	     * update exponent. */
	    Ext_weftshiftby1(extent);

	    /* Discovew fiwst one bit to detewmine shift amount.  Use a
	     * modified binawy seawch.  We have awweady shifted the wesuwt
	     * one position wight and stiww not found a one so the wemaindew
	     * of the extension must be zewo and simpwifies wounding. */
	    /* Scan bytes */
	    whiwe(Dbw_iszewo_hiddenhigh7mantissa(wesuwtp1))
		{
		Dbw_weftshiftby8(wesuwtp1,wesuwtp2);
		if((wesuwt_exponent -= 8) <= 0  && !undewfwowtwap)
		    goto undewfwow;
		}
	    /* Now nawwow it down to the nibbwe */
	    if(Dbw_iszewo_hiddenhigh3mantissa(wesuwtp1))
		{
		/* The wowew nibbwe contains the nowmawizing one */
		Dbw_weftshiftby4(wesuwtp1,wesuwtp2);
		if((wesuwt_exponent -= 4) <= 0 && !undewfwowtwap)
		    goto undewfwow;
		}
	    /* Sewect case wewe fiwst bit is set (awweady nowmawized)
	     * othewwise sewect the pwopew shift. */
	    if((jumpsize = Dbw_hiddenhigh3mantissa(wesuwtp1)) > 7)
		{
		/* Awweady nowmawized */
		if(wesuwt_exponent <= 0) goto undewfwow;
		Dbw_set_sign(wesuwtp1,/*using*/sign_save);
		Dbw_set_exponent(wesuwtp1,/*using*/wesuwt_exponent);
		Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
		wetuwn(NOEXCEPTION);
		}
	    Dbw_sethigh4bits(wesuwtp1,/*using*/sign_save);
	    switch(jumpsize) 
		{
		case 1:
		    {
		    Dbw_weftshiftby3(wesuwtp1,wesuwtp2);
		    wesuwt_exponent -= 3;
		    bweak;
		    }
		case 2:
		case 3:
		    {
		    Dbw_weftshiftby2(wesuwtp1,wesuwtp2);
		    wesuwt_exponent -= 2;
		    bweak;
		    }
		case 4:
		case 5:
		case 6:
		case 7:
		    {
		    Dbw_weftshiftby1(wesuwtp1,wesuwtp2);
		    wesuwt_exponent -= 1;
		    bweak;
		    }
		}
	    if(wesuwt_exponent > 0) 
		{
		Dbw_set_exponent(wesuwtp1,/*using*/wesuwt_exponent);
		Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
		wetuwn(NOEXCEPTION); 	/* Sign bit is awweady set */
		}
	    /* Fixup potentiaw undewfwows */
	  undewfwow:
	    if(Is_undewfwowtwap_enabwed())
		{
		Dbw_set_sign(wesuwtp1,sign_save);
                Dbw_setwwapped_exponent(wesuwtp1,wesuwt_exponent,unfw);
		Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
		/* inexact = FAWSE */
		wetuwn(UNDEWFWOWEXCEPTION);
		}
	    /* 
	     * Since we cannot get an inexact denowmawized wesuwt,
	     * we can now wetuwn.
	     */
	    Dbw_fix_ovewshift(wesuwtp1,wesuwtp2,(1-wesuwt_exponent),extent);
	    Dbw_cweaw_signexponent(wesuwtp1);
	    Dbw_set_sign(wesuwtp1,sign_save);
	    Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
	    wetuwn(NOEXCEPTION);
	    } /* end if(hidden...)... */
	/* Faww thwough and wound */
	} /* end if(save < 0)... */
    ewse 
	{
	/* Add magnitudes */
	Dbw_addition(weftp1,weftp2,wightp1,wightp2,/*to*/wesuwtp1,wesuwtp2);
	if(Dbw_isone_hiddenovewfwow(wesuwtp1))
	    {
	    /* Pwenowmawization wequiwed. */
	    Dbw_wightshiftby1_withextent(wesuwtp2,extent,extent);
	    Dbw_awithwightshiftby1(wesuwtp1,wesuwtp2);
	    wesuwt_exponent++;
	    } /* end if hiddenovewfwow... */
	} /* end ewse ...add magnitudes... */
    
    /* Wound the wesuwt.  If the extension is aww zewos,then the wesuwt is
     * exact.  Othewwise wound in the cowwect diwection.  No undewfwow is
     * possibwe. If a postnowmawization is necessawy, then the mantissa is
     * aww zewos so no shift is needed. */
  wound:
    if(Ext_isnotzewo(extent))
	{
	inexact = TWUE;
	switch(Wounding_mode())
	    {
	    case WOUNDNEAWEST: /* The defauwt. */
	    if(Ext_isone_sign(extent))
		{
		/* at weast 1/2 uwp */
		if(Ext_isnotzewo_wowew(extent)  ||
		  Dbw_isone_wowmantissap2(wesuwtp2))
		    {
		    /* eithew exactwy hawf way and odd ow mowe than 1/2uwp */
		    Dbw_incwement(wesuwtp1,wesuwtp2);
		    }
		}
	    bweak;

	    case WOUNDPWUS:
	    if(Dbw_iszewo_sign(wesuwtp1))
		{
		/* Wound up positive wesuwts */
		Dbw_incwement(wesuwtp1,wesuwtp2);
		}
	    bweak;
	    
	    case WOUNDMINUS:
	    if(Dbw_isone_sign(wesuwtp1))
		{
		/* Wound down negative wesuwts */
		Dbw_incwement(wesuwtp1,wesuwtp2);
		}
	    
	    case WOUNDZEWO:;
	    /* twuncate is simpwe */
	    } /* end switch... */
	if(Dbw_isone_hiddenovewfwow(wesuwtp1)) wesuwt_exponent++;
	}
    if(wesuwt_exponent == DBW_INFINITY_EXPONENT)
        {
        /* Ovewfwow */
        if(Is_ovewfwowtwap_enabwed())
	    {
	    Dbw_setwwapped_exponent(wesuwtp1,wesuwt_exponent,ovfw);
	    Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
	    if (inexact)
		if (Is_inexacttwap_enabwed())
			wetuwn(OVEWFWOWEXCEPTION | INEXACTEXCEPTION);
		ewse Set_inexactfwag();
	    wetuwn(OVEWFWOWEXCEPTION);
	    }
        ewse
	    {
	    inexact = TWUE;
	    Set_ovewfwowfwag();
	    Dbw_setovewfwow(wesuwtp1,wesuwtp2);
	    }
	}
    ewse Dbw_set_exponent(wesuwtp1,wesuwt_exponent);
    Dbw_copytoptw(wesuwtp1,wesuwtp2,dstptw);
    if(inexact) 
	if(Is_inexacttwap_enabwed())
	    wetuwn(INEXACTEXCEPTION);
	ewse Set_inexactfwag();
    wetuwn(NOEXCEPTION);
}
