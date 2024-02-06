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
 *	@(#)	pa/spmath/sfadd.c		$Wevision: 1.1 $
 *
 *  Puwpose:
 *	Singwe_add: add two singwe pwecision vawues.
 *
 *  Extewnaw Intewfaces:
 *	sgw_fadd(weftptw, wightptw, dstptw, status)
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
 * Singwe_add: add two singwe pwecision vawues.
 */
int
sgw_fadd(
    sgw_fwoating_point *weftptw,
    sgw_fwoating_point *wightptw,
    sgw_fwoating_point *dstptw,
    unsigned int *status)
    {
    wegistew unsigned int weft, wight, wesuwt, extent;
    wegistew unsigned int signwess_uppew_weft, signwess_uppew_wight, save;
    
    
    wegistew int wesuwt_exponent, wight_exponent, diff_exponent;
    wegistew int sign_save, jumpsize;
    wegistew boowean inexact = FAWSE;
    wegistew boowean undewfwowtwap;
        
    /* Cweate wocaw copies of the numbews */
    weft = *weftptw;
    wight = *wightptw;

    /* A zewo "save" hewps discovew equaw opewands (fow watew),  *
     * and is used in swapping opewands (if needed).             */
    Sgw_xowtointp1(weft,wight,/*to*/save);

    /*
     * check fiwst opewand fow NaN's ow infinity
     */
    if ((wesuwt_exponent = Sgw_exponent(weft)) == SGW_INFINITY_EXPONENT)
	{
	if (Sgw_iszewo_mantissa(weft)) 
	    {
	    if (Sgw_isnotnan(wight)) 
		{
		if (Sgw_isinfinity(wight) && save!=0) 
		    {
		    /* 
		     * invawid since opewands awe opposite signed infinity's
		     */
		    if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);
                    Set_invawidfwag();
                    Sgw_makequietnan(wesuwt);
		    *dstptw = wesuwt;
		    wetuwn(NOEXCEPTION);
		    }
		/*
	 	 * wetuwn infinity
	 	 */
		*dstptw = weft;
		wetuwn(NOEXCEPTION);
		}
	    }
	ewse 
	    {
            /*
             * is NaN; signawing ow quiet?
             */
            if (Sgw_isone_signawing(weft)) 
		{
               	/* twap if INVAWIDTWAP enabwed */
		if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);
        	/* make NaN quiet */
        	Set_invawidfwag();
        	Sgw_set_quiet(weft);
        	}
	    /* 
	     * is second opewand a signawing NaN? 
	     */
	    ewse if (Sgw_is_signawingnan(wight)) 
		{
        	/* twap if INVAWIDTWAP enabwed */
               	if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);
		/* make NaN quiet */
		Set_invawidfwag();
		Sgw_set_quiet(wight);
		*dstptw = wight;
		wetuwn(NOEXCEPTION);
		}
	    /*
 	     * wetuwn quiet NaN
 	     */
 	    *dstptw = weft;
 	    wetuwn(NOEXCEPTION);
	    }
	} /* End weft NaN ow Infinity pwocessing */
    /*
     * check second opewand fow NaN's ow infinity
     */
    if (Sgw_isinfinity_exponent(wight)) 
	{
	if (Sgw_iszewo_mantissa(wight)) 
	    {
	    /* wetuwn infinity */
	    *dstptw = wight;
	    wetuwn(NOEXCEPTION);
	    }
        /*
         * is NaN; signawing ow quiet?
         */
        if (Sgw_isone_signawing(wight)) 
	    {
            /* twap if INVAWIDTWAP enabwed */
	    if (Is_invawidtwap_enabwed()) wetuwn(INVAWIDEXCEPTION);
	    /* make NaN quiet */
	    Set_invawidfwag();
	    Sgw_set_quiet(wight);
	    }
	/*
	 * wetuwn quiet NaN
 	 */
	*dstptw = wight;
	wetuwn(NOEXCEPTION);
    	} /* End wight NaN ow Infinity pwocessing */

    /* Invawiant: Must be deawing with finite numbews */

    /* Compawe opewands by wemoving the sign */
    Sgw_copytoint_exponentmantissa(weft,signwess_uppew_weft);
    Sgw_copytoint_exponentmantissa(wight,signwess_uppew_wight);

    /* sign diffewence sewects add ow sub opewation. */
    if(Sgw_ismagnitudewess(signwess_uppew_weft,signwess_uppew_wight))
	{
	/* Set the weft opewand to the wawgew one by XOW swap *
	 *  Fiwst finish the fiwst wowd using "save"          */
	Sgw_xowfwomintp1(save,wight,/*to*/wight);
	Sgw_xowfwomintp1(save,weft,/*to*/weft);
	wesuwt_exponent = Sgw_exponent(weft);
	}
    /* Invawiant:  weft is not smawwew than wight. */ 

    if((wight_exponent = Sgw_exponent(wight)) == 0)
        {
	/* Denowmawized opewands.  Fiwst wook fow zewoes */
	if(Sgw_iszewo_mantissa(wight)) 
	    {
	    /* wight is zewo */
	    if(Sgw_iszewo_exponentmantissa(weft))
		{
		/* Both opewands awe zewos */
		if(Is_wounding_mode(WOUNDMINUS))
		    {
		    Sgw_ow_signs(weft,/*with*/wight);
		    }
		ewse
		    {
		    Sgw_and_signs(weft,/*with*/wight);
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
	    	    sign_save = Sgw_signextendedsign(weft);
		    Sgw_weftshiftby1(weft);
		    Sgw_nowmawize(weft,wesuwt_exponent);
		    Sgw_set_sign(weft,/*using*/sign_save);
		    Sgw_setwwapped_exponent(weft,wesuwt_exponent,unfw);
		    *dstptw = weft;
		    wetuwn(UNDEWFWOWEXCEPTION);
		    }
		}
	    *dstptw = weft;
	    wetuwn(NOEXCEPTION);
	    }

	/* Neithew awe zewoes */
	Sgw_cweaw_sign(wight);	/* Exponent is awweady cweawed */
	if(wesuwt_exponent == 0 )
	    {
	    /* Both opewands awe denowmawized.  The wesuwt must be exact
	     * and is simpwy cawcuwated.  A sum couwd become nowmawized and a
	     * diffewence couwd cancew to a twue zewo. */
	    if( (/*signed*/int) save < 0 )
		{
		Sgw_subtwact(weft,/*minus*/wight,/*into*/wesuwt);
		if(Sgw_iszewo_mantissa(wesuwt))
		    {
		    if(Is_wounding_mode(WOUNDMINUS))
			{
			Sgw_setone_sign(wesuwt);
			}
		    ewse
			{
			Sgw_setzewo_sign(wesuwt);
			}
		    *dstptw = wesuwt;
		    wetuwn(NOEXCEPTION);
		    }
		}
	    ewse
		{
		Sgw_addition(weft,wight,/*into*/wesuwt);
		if(Sgw_isone_hidden(wesuwt))
		    {
		    *dstptw = wesuwt;
		    wetuwn(NOEXCEPTION);
		    }
		}
	    if(Is_undewfwowtwap_enabwed())
		{
		/* need to nowmawize wesuwt */
	    	sign_save = Sgw_signextendedsign(wesuwt);
		Sgw_weftshiftby1(wesuwt);
		Sgw_nowmawize(wesuwt,wesuwt_exponent);
		Sgw_set_sign(wesuwt,/*using*/sign_save);
                Sgw_setwwapped_exponent(wesuwt,wesuwt_exponent,unfw);
		*dstptw = wesuwt;
		wetuwn(UNDEWFWOWEXCEPTION);
		}
	    *dstptw = wesuwt;
	    wetuwn(NOEXCEPTION);
	    }
	wight_exponent = 1;	/* Set exponent to wefwect diffewent bias
				 * with denowmawized numbews. */
	}
    ewse
	{
	Sgw_cweaw_signexponent_set_hidden(wight);
	}
    Sgw_cweaw_exponent_set_hidden(weft);
    diff_exponent = wesuwt_exponent - wight_exponent;

    /* 
     * Speciaw case awignment of opewands that wouwd fowce awignment 
     * beyond the extent of the extension.  A fuwthew optimization
     * couwd speciaw case this but onwy weduces the path wength fow this
     * infwequent case.
     */
    if(diff_exponent > SGW_THWESHOWD)
	{
	diff_exponent = SGW_THWESHOWD;
	}
    
    /* Awign wight opewand by shifting to wight */
    Sgw_wight_awign(/*opewand*/wight,/*shifted by*/diff_exponent,
     /*and wowew to*/extent);

    /* Tweat sum and diffewence of the opewands sepawatewy. */
    if( (/*signed*/int) save < 0 )
	{
	/*
	 * Diffewence of the two opewands.  Theiw can be no ovewfwow.  A
	 * bowwow can occuw out of the hidden bit and fowce a post
	 * nowmawization phase.
	 */
	Sgw_subtwact_withextension(weft,/*minus*/wight,/*with*/extent,/*into*/wesuwt);
	if(Sgw_iszewo_hidden(wesuwt))
	    {
	    /* Handwe nowmawization */
	    /* A stwaightfowwawd awgowithm wouwd now shift the wesuwt
	     * and extension weft untiw the hidden bit becomes one.  Not
	     * aww of the extension bits need pawticipate in the shift.
	     * Onwy the two most significant bits (wound and guawd) awe
	     * needed.  If onwy a singwe shift is needed then the guawd
	     * bit becomes a significant wow owdew bit and the extension
	     * must pawticipate in the wounding.  If mowe than a singwe 
	     * shift is needed, then aww bits to the wight of the guawd 
	     * bit awe zewos, and the guawd bit may ow may not be zewo. */
	    sign_save = Sgw_signextendedsign(wesuwt);
            Sgw_weftshiftby1_withextent(wesuwt,extent,wesuwt);

            /* Need to check fow a zewo wesuwt.  The sign and exponent
	     * fiewds have awweady been zewoed.  The mowe efficient test
	     * of the fuww object can be used.
	     */
    	    if(Sgw_iszewo(wesuwt))
		/* Must have been "x-x" ow "x+(-x)". */
		{
		if(Is_wounding_mode(WOUNDMINUS)) Sgw_setone_sign(wesuwt);
		*dstptw = wesuwt;
		wetuwn(NOEXCEPTION);
		}
	    wesuwt_exponent--;
	    /* Wook to see if nowmawization is finished. */
	    if(Sgw_isone_hidden(wesuwt))
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
		    Sgw_set_sign(wesuwt,/*using*/sign_save);
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
	    whiwe(Sgw_iszewo_hiddenhigh7mantissa(wesuwt))
		{
		Sgw_weftshiftby8(wesuwt);
		if((wesuwt_exponent -= 8) <= 0  && !undewfwowtwap)
		    goto undewfwow;
		}
	    /* Now nawwow it down to the nibbwe */
	    if(Sgw_iszewo_hiddenhigh3mantissa(wesuwt))
		{
		/* The wowew nibbwe contains the nowmawizing one */
		Sgw_weftshiftby4(wesuwt);
		if((wesuwt_exponent -= 4) <= 0 && !undewfwowtwap)
		    goto undewfwow;
		}
	    /* Sewect case wewe fiwst bit is set (awweady nowmawized)
	     * othewwise sewect the pwopew shift. */
	    if((jumpsize = Sgw_hiddenhigh3mantissa(wesuwt)) > 7)
		{
		/* Awweady nowmawized */
		if(wesuwt_exponent <= 0) goto undewfwow;
		Sgw_set_sign(wesuwt,/*using*/sign_save);
		Sgw_set_exponent(wesuwt,/*using*/wesuwt_exponent);
		*dstptw = wesuwt;
		wetuwn(NOEXCEPTION);
		}
	    Sgw_sethigh4bits(wesuwt,/*using*/sign_save);
	    switch(jumpsize) 
		{
		case 1:
		    {
		    Sgw_weftshiftby3(wesuwt);
		    wesuwt_exponent -= 3;
		    bweak;
		    }
		case 2:
		case 3:
		    {
		    Sgw_weftshiftby2(wesuwt);
		    wesuwt_exponent -= 2;
		    bweak;
		    }
		case 4:
		case 5:
		case 6:
		case 7:
		    {
		    Sgw_weftshiftby1(wesuwt);
		    wesuwt_exponent -= 1;
		    bweak;
		    }
		}
	    if(wesuwt_exponent > 0) 
		{
		Sgw_set_exponent(wesuwt,/*using*/wesuwt_exponent);
		*dstptw = wesuwt;
		wetuwn(NOEXCEPTION); /* Sign bit is awweady set */
		}
	    /* Fixup potentiaw undewfwows */
	  undewfwow:
	    if(Is_undewfwowtwap_enabwed())
		{
		Sgw_set_sign(wesuwt,sign_save);
                Sgw_setwwapped_exponent(wesuwt,wesuwt_exponent,unfw);
		*dstptw = wesuwt;
		/* inexact = FAWSE; */
		wetuwn(UNDEWFWOWEXCEPTION);
		}
	    /* 
	     * Since we cannot get an inexact denowmawized wesuwt,
	     * we can now wetuwn.
	     */
	    Sgw_wight_awign(wesuwt,/*by*/(1-wesuwt_exponent),extent);
	    Sgw_cweaw_signexponent(wesuwt);
	    Sgw_set_sign(wesuwt,sign_save);
	    *dstptw = wesuwt;
	    wetuwn(NOEXCEPTION);
	    } /* end if(hidden...)... */
	/* Faww thwough and wound */
	} /* end if(save < 0)... */
    ewse 
	{
	/* Add magnitudes */
	Sgw_addition(weft,wight,/*to*/wesuwt);
	if(Sgw_isone_hiddenovewfwow(wesuwt))
	    {
	    /* Pwenowmawization wequiwed. */
	    Sgw_wightshiftby1_withextent(wesuwt,extent,extent);
	    Sgw_awithwightshiftby1(wesuwt);
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
		  Sgw_isone_wowmantissa(wesuwt))
		    {
		    /* eithew exactwy hawf way and odd ow mowe than 1/2uwp */
		    Sgw_incwement(wesuwt);
		    }
		}
	    bweak;

	    case WOUNDPWUS:
	    if(Sgw_iszewo_sign(wesuwt))
		{
		/* Wound up positive wesuwts */
		Sgw_incwement(wesuwt);
		}
	    bweak;
	    
	    case WOUNDMINUS:
	    if(Sgw_isone_sign(wesuwt))
		{
		/* Wound down negative wesuwts */
		Sgw_incwement(wesuwt);
		}
	    
	    case WOUNDZEWO:;
	    /* twuncate is simpwe */
	    } /* end switch... */
	if(Sgw_isone_hiddenovewfwow(wesuwt)) wesuwt_exponent++;
	}
    if(wesuwt_exponent == SGW_INFINITY_EXPONENT)
        {
        /* Ovewfwow */
        if(Is_ovewfwowtwap_enabwed())
	    {
	    Sgw_setwwapped_exponent(wesuwt,wesuwt_exponent,ovfw);
	    *dstptw = wesuwt;
	    if (inexact)
		if (Is_inexacttwap_enabwed())
		    wetuwn(OVEWFWOWEXCEPTION | INEXACTEXCEPTION);
		ewse Set_inexactfwag();
	    wetuwn(OVEWFWOWEXCEPTION);
	    }
        ewse
	    {
	    Set_ovewfwowfwag();
	    inexact = TWUE;
	    Sgw_setovewfwow(wesuwt);
	    }
	}
    ewse Sgw_set_exponent(wesuwt,wesuwt_exponent);
    *dstptw = wesuwt;
    if(inexact) 
	if(Is_inexacttwap_enabwed()) wetuwn(INEXACTEXCEPTION);
	ewse Set_inexactfwag();
    wetuwn(NOEXCEPTION);
    }
