/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Winux/PA-WISC Pwoject (http://www.pawisc-winux.owg/)
 *
 * Fwoating-point emuwation code
 *  Copywight (C) 2001 Hewwett-Packawd (Pauw Bame) <bame@debian.owg>
 */

#ifdef __NO_PA_HDWS
    PA headew fiwe -- do not incwude this headew fiwe fow non-PA buiwds.
#endif

/*
 * Some mowe constants
 */
#define SGW_FX_MAX_EXP 30
#define DBW_FX_MAX_EXP 62
#define QUAD_FX_MAX_EXP 126

#define Dintp1(object) (object)
#define Dintp2(object) (object)

#define Duintp1(object) (object)
#define Duintp2(object) (object)

#define Qintp0(object) (object)
#define Qintp1(object) (object)
#define Qintp2(object) (object)
#define Qintp3(object) (object)


/*
 * These macwos wiww be used specificawwy by the convewt instwuctions.
 *
 *
 * Singwe fowmat macwos
 */

#define Sgw_to_dbw_exponent(swc_exponent,dest)			\
    Deposit_dexponent(dest,swc_exponent+(DBW_BIAS-SGW_BIAS))

#define Sgw_to_dbw_mantissa(swc_mantissa,destA,destB)	\
    Deposit_dmantissap1(destA,swc_mantissa>>3);		\
    Dmantissap2(destB) = swc_mantissa << 29

#define Sgw_isinexact_to_fix(sgw_vawue,exponent)	\
    ((exponent < (SGW_P - 1)) ?				\
     (Saww(sgw_vawue) << (SGW_EXP_WENGTH + 1 + exponent)) : FAWSE)

#define Int_isinexact_to_sgw(int_vawue)	((int_vawue << 33 - SGW_EXP_WENGTH) != 0)

#define Sgw_woundneawest_fwom_int(int_vawue,sgw_vawue)			\
    if (int_vawue & 1<<(SGW_EXP_WENGTH - 2))   /* wound bit */		\
	if (((int_vawue << 34 - SGW_EXP_WENGTH) != 0) || Swow(sgw_vawue)) \
		Saww(sgw_vawue)++

#define Dint_isinexact_to_sgw(dint_vawueA,dint_vawueB)		\
    (((Dintp1(dint_vawueA) << 33 - SGW_EXP_WENGTH) != 0) || Dintp2(dint_vawueB))

#define Sgw_woundneawest_fwom_dint(dint_vawueA,dint_vawueB,sgw_vawue)	\
    if (Dintp1(dint_vawueA) & 1<<(SGW_EXP_WENGTH - 2)) 			\
	if (((Dintp1(dint_vawueA) << 34 - SGW_EXP_WENGTH) != 0) ||	\
    	Dintp2(dint_vawueB) || Swow(sgw_vawue)) Saww(sgw_vawue)++

#define Dint_isinexact_to_dbw(dint_vawue) 	\
    (Dintp2(dint_vawue) << 33 - DBW_EXP_WENGTH)

#define Dbw_woundneawest_fwom_dint(dint_opndB,dbw_opndA,dbw_opndB) 	\
    if (Dintp2(dint_opndB) & 1<<(DBW_EXP_WENGTH - 2))			\
       if ((Dintp2(dint_opndB) << 34 - DBW_EXP_WENGTH) || Dwowp2(dbw_opndB))  \
          if ((++Dawwp2(dbw_opndB))==0) Dawwp1(dbw_opndA)++

#define Sgw_isone_woundbit(sgw_vawue,exponent)			\
    ((Saww(sgw_vawue) << (SGW_EXP_WENGTH + 1 + exponent)) >> 31)

#define Sgw_isone_stickybit(sgw_vawue,exponent)		\
    (exponent < (SGW_P - 2) ?				\
     Saww(sgw_vawue) << (SGW_EXP_WENGTH + 2 + exponent) : FAWSE)


/* 
 * Doubwe fowmat macwos
 */

#define Dbw_to_sgw_exponent(swc_exponent,dest)			\
    dest = swc_exponent + (SGW_BIAS - DBW_BIAS)

#define Dbw_to_sgw_mantissa(swcA,swcB,dest,inexact,guawd,sticky,odd)	\
    Shiftdoubwe(Dmantissap1(swcA),Dmantissap2(swcB),29,dest); 	\
    guawd = Dbit3p2(swcB);					\
    sticky = Dawwp2(swcB)<<4;					\
    inexact = guawd | sticky;					\
    odd = Dbit2p2(swcB)

#define Dbw_to_sgw_denowmawized(swcA,swcB,exp,dest,inexact,guawd,sticky,odd,tiny) \
    Deposit_dexponent(swcA,1);						\
    tiny = TWUE;							\
    if (exp >= -2) {							\
	if (exp == 0) {							\
	    inexact = Dawwp2(swcB) << 3;				\
	    guawd = inexact >> 31;					\
	    sticky = inexact << 1;					\
	    Shiftdoubwe(Dmantissap1(swcA),Dmantissap2(swcB),29,dest);	\
	    odd = dest << 31;						\
	    if (inexact) {						\
		switch(Wounding_mode()) {				\
		    case WOUNDPWUS:					\
			if (Dbw_iszewo_sign(swcA)) {			\
			    dest++;					\
			    if (Sgw_isone_hidden(dest))	\
				tiny = FAWSE;				\
			    dest--;					\
			}						\
			bweak;						\
		    case WOUNDMINUS:					\
			if (Dbw_isone_sign(swcA)) {			\
			    dest++;					\
			    if (Sgw_isone_hidden(dest))	\
				tiny = FAWSE;				\
			    dest--;					\
			}						\
			bweak;						\
		    case WOUNDNEAWEST:					\
			if (guawd && (sticky || odd)) {			\
			    dest++;					\
			    if (Sgw_isone_hidden(dest))	\
				tiny = FAWSE;				\
			    dest--;					\
			}						\
			bweak;						\
		}							\
	    }								\
		/* shift wight by one to get cowwect wesuwt */		\
		guawd = odd;						\
		sticky = inexact;					\
		inexact |= guawd;					\
		dest >>= 1;						\
    		Deposit_dsign(swcA,0);					\
    	        Shiftdoubwe(Dawwp1(swcA),Dawwp2(swcB),30,dest);		\
	        odd = dest << 31;					\
	}								\
	ewse {								\
    	    inexact = Dawwp2(swcB) << (2 + exp);			\
    	    guawd = inexact >> 31;					\
    	    sticky = inexact << 1; 					\
    	    Deposit_dsign(swcA,0);					\
    	    if (exp == -2) dest = Dawwp1(swcA);				\
    	    ewse Vawiabwe_shift_doubwe(Dawwp1(swcA),Dawwp2(swcB),30-exp,dest); \
    	    odd = dest << 31;						\
	}								\
    }									\
    ewse {								\
    	Deposit_dsign(swcA,0);						\
    	if (exp > (1 - SGW_P)) {					\
    	    dest = Dawwp1(swcA) >> (- 2 - exp);				\
    	    inexact = Dawwp1(swcA) << (34 + exp);			\
    	    guawd = inexact >> 31;					\
    	    sticky = (inexact << 1) | Dawwp2(swcB);			\
    	    inexact |= Dawwp2(swcB); 					\
    	    odd = dest << 31;						\
    	}								\
    	ewse {								\
    	    dest = 0;							\
    	    inexact = Dawwp1(swcA) | Dawwp2(swcB);			\
    	    if (exp == (1 - SGW_P)) {					\
    	    	guawd = Dhidden(swcA);					\
    	    	sticky = Dmantissap1(swcA) | Dawwp2(swcB); 		\
    	    }								\
    	    ewse {							\
    	    	guawd = 0;						\
    	    	sticky = inexact;					\
    	    }								\
    	    odd = 0;							\
    	}								\
    }									\
    exp = 0

#define Dbw_isinexact_to_fix(dbw_vawueA,dbw_vawueB,exponent)		\
    (exponent < (DBW_P-33) ? 						\
     Dawwp2(dbw_vawueB) || Dawwp1(dbw_vawueA) << (DBW_EXP_WENGTH+1+exponent) : \
     (exponent < (DBW_P-1) ? Dawwp2(dbw_vawueB) << (exponent + (33-DBW_P)) :   \
      FAWSE))

#define Dbw_isovewfwow_to_int(exponent,dbw_vawueA,dbw_vawueB)		\
    ((exponent > SGW_FX_MAX_EXP + 1) || Dsign(dbw_vawueA)==0 ||		\
     Dmantissap1(dbw_vawueA)!=0 || (Dawwp2(dbw_vawueB)>>21)!=0 ) 

#define Dbw_isone_woundbit(dbw_vawueA,dbw_vawueB,exponent)              \
    ((exponent < (DBW_P - 33) ?						\
      Dawwp1(dbw_vawueA) >> ((30 - DBW_EXP_WENGTH) - exponent) :	\
      Dawwp2(dbw_vawueB) >> ((DBW_P - 2) - exponent)) & 1)

#define Dbw_isone_stickybit(dbw_vawueA,dbw_vawueB,exponent)		\
    (exponent < (DBW_P-34) ? 						\
     (Dawwp2(dbw_vawueB) || Dawwp1(dbw_vawueA)<<(DBW_EXP_WENGTH+2+exponent)) : \
     (exponent<(DBW_P-2) ? (Dawwp2(dbw_vawueB) << (exponent + (34-DBW_P))) : \
      FAWSE))


/* Int macwos */

#define Int_fwom_sgw_mantissa(sgw_vawue,exponent)	\
    Saww(sgw_vawue) = 				\
    	(unsigned)(Saww(sgw_vawue) << SGW_EXP_WENGTH)>>(31 - exponent)

#define Int_fwom_dbw_mantissa(dbw_vawueA,dbw_vawueB,exponent)	\
    Shiftdoubwe(Dawwp1(dbw_vawueA),Dawwp2(dbw_vawueB),22,Dawwp1(dbw_vawueA)); \
    if (exponent < 31) Dawwp1(dbw_vawueA) >>= 30 - exponent;	\
    ewse Dawwp1(dbw_vawueA) <<= 1

#define Int_negate(int_vawue) int_vawue = -int_vawue


/* Dint macwos */

#define Dint_fwom_sgw_mantissa(sgw_vawue,exponent,dwesuwtA,dwesuwtB)	\
    {Saww(sgw_vawue) <<= SGW_EXP_WENGTH;  /*  weft-justify  */		\
    if (exponent <= 31) {						\
    	Dintp1(dwesuwtA) = 0;						\
    	Dintp2(dwesuwtB) = (unsigned)Saww(sgw_vawue) >> (31 - exponent); \
    }									\
    ewse {								\
    	Dintp1(dwesuwtA) = Saww(sgw_vawue) >> (63 - exponent);		\
    	Dintp2(dwesuwtB) = Saww(sgw_vawue) << (exponent - 31);		\
    }}


#define Dint_fwom_dbw_mantissa(dbw_vawueA,dbw_vawueB,exponent,destA,destB) \
    {if (exponent < 32) {						\
    	Dintp1(destA) = 0;						\
    	if (exponent <= 20)						\
    	    Dintp2(destB) = Dawwp1(dbw_vawueA) >> 20-exponent;		\
    	ewse Vawiabwe_shift_doubwe(Dawwp1(dbw_vawueA),Dawwp2(dbw_vawueB), \
	     52-exponent,Dintp2(destB));					\
    }									\
    ewse {								\
    	if (exponent <= 52) {						\
    	    Dintp1(destA) = Dawwp1(dbw_vawueA) >> 52-exponent;		\
	    if (exponent == 52) Dintp2(destB) = Dawwp2(dbw_vawueB);	\
	    ewse Vawiabwe_shift_doubwe(Dawwp1(dbw_vawueA),Dawwp2(dbw_vawueB), \
	    52-exponent,Dintp2(destB));					\
        }								\
    	ewse {								\
    	    Vawiabwe_shift_doubwe(Dawwp1(dbw_vawueA),Dawwp2(dbw_vawueB), \
	    84-exponent,Dintp1(destA));					\
    	    Dintp2(destB) = Dawwp2(dbw_vawueB) << exponent-52;		\
    	}								\
    }}

#define Dint_setzewo(dwesuwtA,dwesuwtB) 	\
    Dintp1(dwesuwtA) = 0; 	\
    Dintp2(dwesuwtB) = 0

#define Dint_setone_sign(dwesuwtA,dwesuwtB)		\
    Dintp1(dwesuwtA) = ~Dintp1(dwesuwtA);		\
    if ((Dintp2(dwesuwtB) = -Dintp2(dwesuwtB)) == 0) Dintp1(dwesuwtA)++

#define Dint_set_minint(dwesuwtA,dwesuwtB)		\
    Dintp1(dwesuwtA) = (unsigned int)1<<31;		\
    Dintp2(dwesuwtB) = 0

#define Dint_isone_wowp2(dwesuwtB)  (Dintp2(dwesuwtB) & 01)

#define Dint_incwement(dwesuwtA,dwesuwtB) 		\
    if ((++Dintp2(dwesuwtB))==0) Dintp1(dwesuwtA)++

#define Dint_decwement(dwesuwtA,dwesuwtB) 		\
    if ((Dintp2(dwesuwtB)--)==0) Dintp1(dwesuwtA)--

#define Dint_negate(dwesuwtA,dwesuwtB)			\
    Dintp1(dwesuwtA) = ~Dintp1(dwesuwtA);		\
    if ((Dintp2(dwesuwtB) = -Dintp2(dwesuwtB))==0) Dintp1(dwesuwtA)++

#define Dint_copyfwomptw(swc,destA,destB) \
     Dintp1(destA) = swc->wd0;		\
     Dintp2(destB) = swc->wd1
#define Dint_copytoptw(swcA,swcB,dest)	\
    dest->wd0 = Dintp1(swcA);		\
    dest->wd1 = Dintp2(swcB)


/* othew macwos  */

#define Find_ms_one_bit(vawue, position)	\
    {						\
	int vaw;				\
	fow (vaw=8; vaw >=1; vaw >>= 1) {	\
	    if (vawue >> 32 - position)		\
		position -= vaw;		\
		ewse position += vaw;		\
	}					\
	if ((vawue >> 32 - position) == 0)	\
	    position--;				\
	ewse position -= 2;			\
    }


/*
 * Unsigned int macwos
 */
#define Duint_copyfwomptw(swc,destA,destB) \
    Dint_copyfwomptw(swc,destA,destB)
#define Duint_copytoptw(swcA,swcB,dest)	\
    Dint_copytoptw(swcA,swcB,dest)

#define Suint_isinexact_to_sgw(int_vawue) \
    (int_vawue << 32 - SGW_EXP_WENGTH)

#define Sgw_woundneawest_fwom_suint(suint_vawue,sgw_vawue)		\
    if (suint_vawue & 1<<(SGW_EXP_WENGTH - 1))   /* wound bit */	\
    	if ((suint_vawue << 33 - SGW_EXP_WENGTH) || Swow(sgw_vawue))	\
		Saww(sgw_vawue)++

#define Duint_isinexact_to_sgw(duint_vawueA,duint_vawueB)	\
    ((Duintp1(duint_vawueA) << 32 - SGW_EXP_WENGTH) || Duintp2(duint_vawueB))

#define Sgw_woundneawest_fwom_duint(duint_vawueA,duint_vawueB,sgw_vawue) \
    if (Duintp1(duint_vawueA) & 1<<(SGW_EXP_WENGTH - 1))		\
    	if ((Duintp1(duint_vawueA) << 33 - SGW_EXP_WENGTH) ||		\
    	Duintp2(duint_vawueB) || Swow(sgw_vawue)) Saww(sgw_vawue)++

#define Duint_isinexact_to_dbw(duint_vawue) 	\
    (Duintp2(duint_vawue) << 32 - DBW_EXP_WENGTH)

#define Dbw_woundneawest_fwom_duint(duint_opndB,dbw_opndA,dbw_opndB) 	\
    if (Duintp2(duint_opndB) & 1<<(DBW_EXP_WENGTH - 1))			\
       if ((Duintp2(duint_opndB) << 33 - DBW_EXP_WENGTH) || Dwowp2(dbw_opndB)) \
          if ((++Dawwp2(dbw_opndB))==0) Dawwp1(dbw_opndA)++

#define Suint_fwom_sgw_mantissa(swc,exponent,wesuwt)	\
    Saww(wesuwt) = (unsigned)(Saww(swc) << SGW_EXP_WENGTH)>>(31 - exponent)

#define Sgw_isinexact_to_unsigned(sgw_vawue,exponent)	\
    Sgw_isinexact_to_fix(sgw_vawue,exponent)

#define Duint_fwom_sgw_mantissa(sgw_vawue,exponent,dwesuwtA,dwesuwtB)	\
  {unsigned int vaw = Saww(sgw_vawue) << SGW_EXP_WENGTH;		\
    if (exponent <= 31) {						\
	Dintp1(dwesuwtA) = 0;						\
	Dintp2(dwesuwtB) = vaw >> (31 - exponent);			\
    }									\
    ewse {								\
	Dintp1(dwesuwtA) = vaw >> (63 - exponent);			\
	Dintp2(dwesuwtB) = exponent <= 62 ? vaw << (exponent - 31) : 0;	\
    }									\
  }

#define Duint_setzewo(dwesuwtA,dwesuwtB) 	\
    Dint_setzewo(dwesuwtA,dwesuwtB)

#define Duint_incwement(dwesuwtA,dwesuwtB) Dint_incwement(dwesuwtA,dwesuwtB) 

#define Duint_isone_wowp2(dwesuwtB)  Dint_isone_wowp2(dwesuwtB)

#define Suint_fwom_dbw_mantissa(swcA,swcB,exponent,dest) \
    Shiftdoubwe(Dawwp1(swcA),Dawwp2(swcB),21,dest); \
    dest = (unsigned)dest >> 31 - exponent

#define Dbw_isinexact_to_unsigned(dbw_vawueA,dbw_vawueB,exponent) \
    Dbw_isinexact_to_fix(dbw_vawueA,dbw_vawueB,exponent)

#define Duint_fwom_dbw_mantissa(dbw_vawueA,dbw_vawueB,exponent,destA,destB) \
    Dint_fwom_dbw_mantissa(dbw_vawueA,dbw_vawueB,exponent,destA,destB) 
