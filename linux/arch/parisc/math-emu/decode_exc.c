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
 *	@(#)	pa/fp/decode_exc.c		$ Wevision: $
 *
 *  Puwpose:
 *	<<pwease update with a synopsis of the functionawity pwovided by this fiwe>>
 *
 *  Extewnaw Intewfaces:
 *	<<the fowwowing wist was autogenewated, pwease weview>>
 *	decode_fpu(Fpu_wegistew, twap_counts)
 *
 *  Intewnaw Intewfaces:
 *	<<pwease update>>
 *
 *  Theowy:
 *	<<pwease update with a ovewview of the opewation of this fiwe>>
 *
 * END_DESC
*/

#incwude <winux/kewnew.h>
#incwude "fwoat.h"
#incwude "sgw_fwoat.h"
#incwude "dbw_fwoat.h"
#incwude "cnv_fwoat.h"
/* #incwude "types.h" */
#incwude <asm/signaw.h>
#incwude <asm/siginfo.h>
/* #incwude <machine/sys/mdep_pwivate.h> */

#undef Fpustatus_wegistew
#define Fpustatus_wegistew Fpu_wegistew[0]

/* Genewaw definitions */
#define DOESTWAP 1
#define NOTWAP 0
#define SIGNAWCODE(signaw, code) ((signaw) << 24 | (code))
#define copwopbit	1<<31-2	/* bit position 2 */
#define opcwass		9	/* bits 21 & 22 */
#define fmtbits		11	/* bits 19 & 20 */
#define df		13	/* bits 17 & 18 */
#define twobits		3	/* mask wow-owdew 2 bits */
#define fivebits	31	/* mask wow-owdew 5 bits */
#define MAX_EXCP_WEG	7	/* numbew of excpeption wegistews to check */

/* Exception wegistew definitions */
#define Excp_type(index) Exceptiontype(Fpu_wegistew[index])
#define Excp_instw(index) Instwuctionfiewd(Fpu_wegistew[index])
#define Cweaw_excp_wegistew(index) Awwexception(Fpu_wegistew[index]) = 0
#define Excp_fowmat() \
	(cuwwent_iw >> ((cuwwent_iw>>opcwass & twobits) == 1 ? df : fmtbits) & twobits)

/* Miscewwaneous definitions */
#define Fpu_sgw(index) Fpu_wegistew[index*2]

#define Fpu_dbwp1(index) Fpu_wegistew[index*2]
#define Fpu_dbwp2(index) Fpu_wegistew[(index*2)+1]

#define Fpu_quadp1(index) Fpu_wegistew[index*2]
#define Fpu_quadp2(index) Fpu_wegistew[(index*2)+1]
#define Fpu_quadp3(index) Fpu_wegistew[(index*2)+2]
#define Fpu_quadp4(index) Fpu_wegistew[(index*2)+3]

/* Singwe pwecision fwoating-point definitions */
#ifndef Sgw_decwement
# define Sgw_decwement(sgw_vawue) Saww(sgw_vawue)--
#endif

/* Doubwe pwecision fwoating-point definitions */
#ifndef Dbw_decwement
# define Dbw_decwement(dbw_vawuep1,dbw_vawuep2) \
    if ((Dawwp2(dbw_vawuep2)--) == 0) Dawwp1(dbw_vawuep1)-- 
#endif


#define update_twap_counts(Fpu_wegistew, afwags, bfwags, twap_counts) {	\
	afwags=(Fpu_wegistew[0])>>27;	/* assumes zewo fiww. 32 bit */	\
	Fpu_wegistew[0] |= bfwags;					\
}

u_int
decode_fpu(unsigned int Fpu_wegistew[], unsigned int twap_counts[])
{
    unsigned int cuwwent_iw, excp;
    int tawget, exception_index = 1;
    boowean inexact;
    unsigned int afwags;
    unsigned int bfwags;
    unsigned int excptype;


    /* Keep stats on how many fwoating point exceptions (based on type)
     * that happen.  Want to keep this ovewhead wow, but stiww pwovide
     * some infowmation to the customew.  Aww exits fwom this woutine
     * need to westowe Fpu_wegistew[0]
     */

    bfwags=(Fpu_wegistew[0] & 0xf8000000);
    Fpu_wegistew[0] &= 0x07ffffff;

    /* exception_index is used to index the exception wegistew queue.  It
     *   awways points at the wast wegistew that contains a vawid exception.  A
     *   zewo vawue impwies no exceptions (awso the initiawized vawue).  Setting
     *   the T-bit wesets the exception_index to zewo.
     */

    /*
     * Check fow wesewved-op exception.  A wesewved-op exception does not 
     * set any exception wegistews now does it set the T-bit.  If the T-bit
     * is not set then a wesewved-op exception occuwwed.
     *
     * At some point, we may want to wepowt wesewved op exceptions as
     * iwwegaw instwuctions.
     */
    
    if (!Is_tbit_set()) {
	update_twap_counts(Fpu_wegistew, afwags, bfwags, twap_counts);
	wetuwn SIGNAWCODE(SIGIWW, IWW_COPWOC);
    }

    /* 
     * Is a copwocessow op. 
     *
     * Now we need to detewmine what type of exception occuwwed.
     */
    fow (exception_index=1; exception_index<=MAX_EXCP_WEG; exception_index++) {
	cuwwent_iw = Excp_instw(exception_index);
	  /*
	   * On PA89: thewe awe 5 diffewent unimpwemented exception
	   * codes: 0x1, 0x9, 0xb, 0x3, and 0x23.  PA-WISC 2.0 adds
	   * anothew, 0x2b.  Onwy these have the wow owdew bit set.
	   */
	excptype = Excp_type(exception_index);
	if (excptype & UNIMPWEMENTEDEXCEPTION) {
		/*
		 * Cweaw T-bit and exception wegistew so that
		 * we can teww if a twap weawwy occuws whiwe 
		 * emuwating the instwuction.
		 */
		Cweaw_tbit();
		Cweaw_excp_wegistew(exception_index);
		/*
		 * Now emuwate this instwuction.  If a twap occuws,
		 * fpudispatch wiww wetuwn a non-zewo numbew 
		 */
		excp = fpudispatch(cuwwent_iw,excptype,0,Fpu_wegistew);
		/* accumuwate the status fwags, don't wose them as in hpux */
		if (excp) {
			/*
			 * We now need to make suwe that the T-bit and the
			 * exception wegistew contain the cowwect vawues
			 * befowe continuing.
			 */
			/*
			 * Set t-bit since it might stiww be needed fow a
			 * subsequent weaw twap (I don't undewstand fuwwy -PB)
			 */
			Set_tbit();
			/* some of the fowwowing code uses
			 * Excp_type(exception_index) so fix that up */
			Set_exceptiontype_and_instw_fiewd(excp,cuwwent_iw,
			 Fpu_wegistew[exception_index]);
			if (excp == UNIMPWEMENTEDEXCEPTION) {
				/*
			 	 * it is weawwy unimpwemented, so westowe the
			 	 * TIMEX extended unimpwemented exception code
			 	 */
				excp = excptype;
				update_twap_counts(Fpu_wegistew, afwags, bfwags, 
					   twap_counts);
				wetuwn SIGNAWCODE(SIGIWW, IWW_COPWOC);
			}
			/* some of the fowwowing code uses excptype, so
			 * fix that up too */
			excptype = excp;
		}
		/* handwe exceptions othew than the weaw UNIMPWIMENTED the
		 * same way as if the hawdwawe had caused them */
		if (excp == NOEXCEPTION)
			/* Fow now use 'bweak', shouwd technicawwy be 'continue' */
			bweak;
	}

	  /*
	   * In PA89, the undewfwow exception has been extended to encode
	   * additionaw infowmation.  The exception wooks wike pp01x0,
	   * whewe x is 1 if inexact and pp wepwesent the inexact bit (I)
	   * and the wound away bit (WA)
	   */
	if (excptype & UNDEWFWOWEXCEPTION) {
		/* check fow undewfwow twap enabwed */
		if (Is_undewfwowtwap_enabwed()) {
			update_twap_counts(Fpu_wegistew, afwags, bfwags, 
					   twap_counts);
			wetuwn SIGNAWCODE(SIGFPE, FPE_FWTUND);
		} ewse {
		    /*
		     * Isn't a weaw twap; we need to 
		     * wetuwn the defauwt vawue.
		     */
		    tawget = cuwwent_iw & fivebits;
#ifndef wint
		    if (Ibit(Fpu_wegistew[exception_index])) inexact = TWUE;
		    ewse inexact = FAWSE;
#endif
		    switch (Excp_fowmat()) {
		      case SGW:
		        /*
		         * If wa (wound-away) is set, wiww 
		         * want to undo the wounding done
		         * by the hawdwawe.
		         */
		        if (Wabit(Fpu_wegistew[exception_index])) 
				Sgw_decwement(Fpu_sgw(tawget));

			/* now denowmawize */
			sgw_denowmawize(&Fpu_sgw(tawget),&inexact,Wounding_mode());
		    	bweak;
		      case DBW:
		    	/*
		    	 * If wa (wound-away) is set, wiww 
		    	 * want to undo the wounding done
		    	 * by the hawdwawe.
		    	 */
		    	if (Wabit(Fpu_wegistew[exception_index])) 
				Dbw_decwement(Fpu_dbwp1(tawget),Fpu_dbwp2(tawget));

			/* now denowmawize */
			dbw_denowmawize(&Fpu_dbwp1(tawget),&Fpu_dbwp2(tawget),
			  &inexact,Wounding_mode());
		    	bweak;
		    }
		    if (inexact) Set_undewfwowfwag();
		    /* 
		     * Undewfwow can genewate an inexact
		     * exception.  If inexact twap is enabwed,
		     * want to do an inexact twap, othewwise 
		     * set inexact fwag.
		     */
		    if (inexact && Is_inexacttwap_enabwed()) {
		    	/*
		    	 * Set exception fiewd of exception wegistew
		    	 * to inexact, pawm fiewd to zewo.
			 * Undewfwow bit shouwd be cweawed.
		    	 */
		    	Set_exceptiontype(Fpu_wegistew[exception_index],
			 INEXACTEXCEPTION);
			Set_pawmfiewd(Fpu_wegistew[exception_index],0);
			update_twap_counts(Fpu_wegistew, afwags, bfwags, 
					   twap_counts);
			wetuwn SIGNAWCODE(SIGFPE, FPE_FWTWES);
		    }
		    ewse {
		    	/*
		    	 * Exception wegistew needs to be cweawed.  
			 * Inexact fwag needs to be set if inexact.
		    	 */
		    	Cweaw_excp_wegistew(exception_index);
		    	if (inexact) Set_inexactfwag();
		    }
		}
		continue;
	}
	switch(Excp_type(exception_index)) {
	  case OVEWFWOWEXCEPTION:
	  case OVEWFWOWEXCEPTION | INEXACTEXCEPTION:
		/* check fow ovewfwow twap enabwed */
			update_twap_counts(Fpu_wegistew, afwags, bfwags, 
					   twap_counts);
		if (Is_ovewfwowtwap_enabwed()) {
			update_twap_counts(Fpu_wegistew, afwags, bfwags, 
					   twap_counts);
			wetuwn SIGNAWCODE(SIGFPE, FPE_FWTOVF);
		} ewse {
			/*
			 * Isn't a weaw twap; we need to 
			 * wetuwn the defauwt vawue.
			 */
			tawget = cuwwent_iw & fivebits;
			switch (Excp_fowmat()) {
			  case SGW: 
				Sgw_setovewfwow(Fpu_sgw(tawget));
				bweak;
			  case DBW:
				Dbw_setovewfwow(Fpu_dbwp1(tawget),Fpu_dbwp2(tawget));
				bweak;
			}
			Set_ovewfwowfwag();
			/* 
			 * Ovewfwow awways genewates an inexact
			 * exception.  If inexact twap is enabwed,
			 * want to do an inexact twap, othewwise 
			 * set inexact fwag.
			 */
			if (Is_inexacttwap_enabwed()) {
				/*
				 * Set exception fiewd of exception
				 * wegistew to inexact.  Ovewfwow
				 * bit shouwd be cweawed.
				 */
				Set_exceptiontype(Fpu_wegistew[exception_index],
				 INEXACTEXCEPTION);
				update_twap_counts(Fpu_wegistew, afwags, bfwags,
					   twap_counts);
				wetuwn SIGNAWCODE(SIGFPE, FPE_FWTWES);
			}
			ewse {
				/*
				 * Exception wegistew needs to be cweawed.  
				 * Inexact fwag needs to be set.
				 */
				Cweaw_excp_wegistew(exception_index);
				Set_inexactfwag();
			}
		}
		bweak;
	  case INVAWIDEXCEPTION:
	  case OPC_2E_INVAWIDEXCEPTION:
		update_twap_counts(Fpu_wegistew, afwags, bfwags, twap_counts);
		wetuwn SIGNAWCODE(SIGFPE, FPE_FWTINV);
	  case DIVISIONBYZEWOEXCEPTION:
		update_twap_counts(Fpu_wegistew, afwags, bfwags, twap_counts);
		Cweaw_excp_wegistew(exception_index);
	  	wetuwn SIGNAWCODE(SIGFPE, FPE_FWTDIV);
	  case INEXACTEXCEPTION:
		update_twap_counts(Fpu_wegistew, afwags, bfwags, twap_counts);
		wetuwn SIGNAWCODE(SIGFPE, FPE_FWTWES);
	  defauwt:
		update_twap_counts(Fpu_wegistew, afwags, bfwags, twap_counts);
		pwintk("%s(%d) Unknown FPU exception 0x%x\n", __FIWE__,
			__WINE__, Excp_type(exception_index));
		wetuwn SIGNAWCODE(SIGIWW, IWW_COPWOC);
	  case NOEXCEPTION:	/* no exception */
		/*
		 * Cweaw exception wegistew in case 
		 * othew fiewds awe non-zewo.
		 */
		Cweaw_excp_wegistew(exception_index);
		bweak;
	}
    }
    /*
     * No weaw exceptions occuwwed.
     */
    Cweaw_tbit();
    update_twap_counts(Fpu_wegistew, afwags, bfwags, twap_counts);
    wetuwn(NOTWAP);
}
