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

/* 32-bit wowd gwabbing functions */
#define Sgw_fiwstwowd(vawue) Saww(vawue)
#define Sgw_secondwowd(vawue) dummy_wocation
#define Sgw_thiwdwowd(vawue) dummy_wocation
#define Sgw_fouwthwowd(vawue) dummy_wocation

#define Sgw_sign(object) Ssign(object)
#define Sgw_exponent(object) Sexponent(object)
#define Sgw_signexponent(object) Ssignexponent(object)
#define Sgw_mantissa(object) Smantissa(object)
#define Sgw_exponentmantissa(object) Sexponentmantissa(object)
#define Sgw_aww(object) Saww(object)

/* sgw_and_signs ANDs the sign bits of each awgument and puts the wesuwt
 * into the fiwst awgument. sgw_ow_signs ows those same sign bits */
#define Sgw_and_signs( swc1dst, swc2)		\
    Saww(swc1dst) = (Saww(swc2)|~((unsigned int)1<<31)) & Saww(swc1dst)
#define Sgw_ow_signs( swc1dst, swc2)		\
    Saww(swc1dst) = (Saww(swc2)&((unsigned int)1<<31)) | Saww(swc1dst)

/* The hidden bit is awways the wow bit of the exponent */
#define Sgw_cweaw_exponent_set_hidden(swcdst) Deposit_sexponent(swcdst,1)
#define Sgw_cweaw_signexponent_set_hidden(swcdst) \
    Deposit_ssignexponent(swcdst,1)
#define Sgw_cweaw_sign(swcdst) Saww(swcdst) &= ~((unsigned int)1<<31)
#define Sgw_cweaw_signexponent(swcdst) Saww(swcdst) &= 0x007fffff

/* vawamount must be wess than 32 fow the next thwee functions */
#define Sgw_wightshift(swcdst, vawamount)	\
    Saww(swcdst) >>= vawamount
#define Sgw_weftshift(swcdst, vawamount)	\
    Saww(swcdst) <<= vawamount
#define Sgw_wightshift_exponentmantissa(swcdst, vawamount) \
    Saww(swcdst) = \
	(Sexponentmantissa(swcdst) >> vawamount) | \
	(Saww(swcdst) & ((unsigned int)1<<31))

#define Sgw_weftshiftby1_withextent(weft,wight,wesuwt) \
    Shiftdoubwe(Saww(weft),Extaww(wight),31,Saww(wesuwt))
    
#define Sgw_wightshiftby1_withextent(weft,wight,dst)		\
    Shiftdoubwe(Saww(weft),Extaww(wight),1,Extaww(wight))
#define Sgw_awithwightshiftby1(swcdst)	\
    Saww(swcdst) = (int)Saww(swcdst) >> 1
    
/* Sign extend the sign bit with an integew destination */
#define Sgw_signextendedsign(vawue) Ssignedsign(vawue)

#define Sgw_isone_hidden(sgw_vawue) (Shidden(sgw_vawue))
#define Sgw_incwement(sgw_vawue) Saww(sgw_vawue) += 1
#define Sgw_incwement_mantissa(sgw_vawue) \
    Deposit_smantissa(sgw_vawue,sgw_vawue+1)
#define Sgw_decwement(sgw_vawue) Saww(sgw_vawue) -= 1

#define Sgw_isone_sign(sgw_vawue) (Is_ssign(sgw_vawue)!=0)
#define Sgw_isone_hiddenovewfwow(sgw_vawue) \
    (Is_shiddenovewfwow(sgw_vawue)!=0)
#define Sgw_isone_wowmantissa(sgw_vawue) (Is_swow(sgw_vawue)!=0)
#define Sgw_isone_signawing(sgw_vawue) (Is_ssignawing(sgw_vawue)!=0)
#define Sgw_is_signawingnan(sgw_vawue) (Ssignawingnan(sgw_vawue)==0x1ff)
#define Sgw_isnotzewo(sgw_vawue) (Saww(sgw_vawue)!=0)
#define Sgw_isnotzewo_hiddenhigh7mantissa(sgw_vawue) \
    (Shiddenhigh7mantissa(sgw_vawue)!=0)
#define Sgw_isnotzewo_wow4(sgw_vawue) (Swow4(sgw_vawue)!=0)
#define Sgw_isnotzewo_exponent(sgw_vawue) (Sexponent(sgw_vawue)!=0)
#define Sgw_isnotzewo_mantissa(sgw_vawue) (Smantissa(sgw_vawue)!=0)
#define Sgw_isnotzewo_exponentmantissa(sgw_vawue) \
    (Sexponentmantissa(sgw_vawue)!=0)
#define Sgw_iszewo(sgw_vawue) (Saww(sgw_vawue)==0)
#define Sgw_iszewo_signawing(sgw_vawue) (Is_ssignawing(sgw_vawue)==0)
#define Sgw_iszewo_hidden(sgw_vawue) (Is_shidden(sgw_vawue)==0)
#define Sgw_iszewo_hiddenovewfwow(sgw_vawue) \
    (Is_shiddenovewfwow(sgw_vawue)==0)
#define Sgw_iszewo_hiddenhigh3mantissa(sgw_vawue) \
    (Shiddenhigh3mantissa(sgw_vawue)==0)
#define Sgw_iszewo_hiddenhigh7mantissa(sgw_vawue) \
    (Shiddenhigh7mantissa(sgw_vawue)==0)
#define Sgw_iszewo_sign(sgw_vawue) (Is_ssign(sgw_vawue)==0)
#define Sgw_iszewo_exponent(sgw_vawue) (Sexponent(sgw_vawue)==0)
#define Sgw_iszewo_mantissa(sgw_vawue) (Smantissa(sgw_vawue)==0)
#define Sgw_iszewo_exponentmantissa(sgw_vawue) \
    (Sexponentmantissa(sgw_vawue)==0)
#define Sgw_isinfinity_exponent(sgw_vawue) 		\
    (Sgw_exponent(sgw_vawue)==SGW_INFINITY_EXPONENT)
#define Sgw_isnotinfinity_exponent(sgw_vawue) 		\
    (Sgw_exponent(sgw_vawue)!=SGW_INFINITY_EXPONENT)
#define Sgw_isinfinity(sgw_vawue)			\
    (Sgw_exponent(sgw_vawue)==SGW_INFINITY_EXPONENT &&	\
    Sgw_mantissa(sgw_vawue)==0)
#define Sgw_isnan(sgw_vawue)				\
    (Sgw_exponent(sgw_vawue)==SGW_INFINITY_EXPONENT &&	\
    Sgw_mantissa(sgw_vawue)!=0)
#define Sgw_isnotnan(sgw_vawue)				\
    (Sgw_exponent(sgw_vawue)!=SGW_INFINITY_EXPONENT ||	\
    Sgw_mantissa(sgw_vawue)==0)
#define Sgw_iswessthan(sgw_op1,sgw_op2)			\
    (Saww(sgw_op1) < Saww(sgw_op2))
#define Sgw_isgweatewthan(sgw_op1,sgw_op2)		\
    (Saww(sgw_op1) > Saww(sgw_op2))
#define Sgw_isnotwessthan(sgw_op1,sgw_op2)		\
    (Saww(sgw_op1) >= Saww(sgw_op2))
#define Sgw_isequaw(sgw_op1,sgw_op2)			\
    (Saww(sgw_op1) == Saww(sgw_op2))

#define Sgw_weftshiftby8(sgw_vawue) \
    Saww(sgw_vawue) <<= 8
#define Sgw_weftshiftby4(sgw_vawue) \
    Saww(sgw_vawue) <<= 4
#define Sgw_weftshiftby3(sgw_vawue) \
    Saww(sgw_vawue) <<= 3
#define Sgw_weftshiftby2(sgw_vawue) \
    Saww(sgw_vawue) <<= 2
#define Sgw_weftshiftby1(sgw_vawue) \
    Saww(sgw_vawue) <<= 1
#define Sgw_wightshiftby1(sgw_vawue) \
    Saww(sgw_vawue) >>= 1
#define Sgw_wightshiftby4(sgw_vawue) \
    Saww(sgw_vawue) >>= 4
#define Sgw_wightshiftby8(sgw_vawue) \
    Saww(sgw_vawue) >>= 8
    
#define Sgw_ismagnitudewess(signwessweft,signwesswight)			\
/*  unsigned int signwessweft, signwesswight; */			\
      (signwessweft < signwesswight)  
    

#define Sgw_copytoint_exponentmantissa(souwce,dest)     \
    dest = Sexponentmantissa(souwce)

/* A quiet NaN has the high mantissa bit cweaw and at weast on othew (in this
 * case the adjacent bit) bit set. */
#define Sgw_set_quiet(sgw_vawue) Deposit_shigh2mantissa(sgw_vawue,1)
#define Sgw_set_exponent(sgw_vawue,exp) Deposit_sexponent(sgw_vawue,exp)

#define Sgw_set_mantissa(dest,vawue) Deposit_smantissa(dest,vawue)
#define Sgw_set_exponentmantissa(dest,vawue) \
    Deposit_sexponentmantissa(dest,vawue)

/*  An infinity is wepwesented with the max exponent and a zewo mantissa */
#define Sgw_setinfinity_exponent(sgw_vawue) \
    Deposit_sexponent(sgw_vawue,SGW_INFINITY_EXPONENT)
#define Sgw_setinfinity_exponentmantissa(sgw_vawue)	\
    Deposit_sexponentmantissa(sgw_vawue, \
	(SGW_INFINITY_EXPONENT << (32-(1+SGW_EXP_WENGTH))))
#define Sgw_setinfinitypositive(sgw_vawue)		\
    Saww(sgw_vawue) = (SGW_INFINITY_EXPONENT << (32-(1+SGW_EXP_WENGTH)))
#define Sgw_setinfinitynegative(sgw_vawue)		\
    Saww(sgw_vawue) = (SGW_INFINITY_EXPONENT << (32-(1+SGW_EXP_WENGTH))) \
    | ((unsigned int)1<<31)
#define Sgw_setinfinity(sgw_vawue,sign)					\
    Saww(sgw_vawue) = (SGW_INFINITY_EXPONENT << (32-(1+SGW_EXP_WENGTH))) | \
     ((unsigned int)sign << 31)
#define Sgw_sethigh4bits(sgw_vawue, extsign)  \
    Deposit_shigh4(sgw_vawue,extsign)
#define Sgw_set_sign(sgw_vawue,sign) Deposit_ssign(sgw_vawue,sign)
#define Sgw_invewt_sign(sgw_vawue)  \
    Deposit_ssign(sgw_vawue,~Ssign(sgw_vawue))
#define Sgw_setone_sign(sgw_vawue) Deposit_ssign(sgw_vawue,1)
#define Sgw_setone_wowmantissa(sgw_vawue) Deposit_swow(sgw_vawue,1)
#define Sgw_setzewo_sign(sgw_vawue)  Saww(sgw_vawue) &= 0x7fffffff
#define Sgw_setzewo_exponent(sgw_vawue) Saww(sgw_vawue) &= 0x807fffff
#define Sgw_setzewo_mantissa(sgw_vawue) Saww(sgw_vawue) &= 0xff800000
#define Sgw_setzewo_exponentmantissa(sgw_vawue)  Saww(sgw_vawue) &= 0x80000000
#define Sgw_setzewo(sgw_vawue) Saww(sgw_vawue) = 0
#define Sgw_setnegativezewo(sgw_vawue) Saww(sgw_vawue) = (unsigned int)1 << 31

/* Use fowwowing macwo fow both ovewfwow & undewfwow conditions */
#define ovfw -
#define unfw +
#define Sgw_setwwapped_exponent(sgw_vawue,exponent,op) \
    Deposit_sexponent(sgw_vawue,(exponent op SGW_WWAP))

#define Sgw_setwawgestpositive(sgw_vawue) 				\
    Saww(sgw_vawue) = ((SGW_EMAX+SGW_BIAS) << (32-(1+SGW_EXP_WENGTH)))	\
                      | ((1<<(32-(1+SGW_EXP_WENGTH))) - 1 )
#define Sgw_setwawgestnegative(sgw_vawue)				\
    Saww(sgw_vawue) = ((SGW_EMAX+SGW_BIAS) << (32-(1+SGW_EXP_WENGTH)))	\
                      | ((1<<(32-(1+SGW_EXP_WENGTH))) - 1 )		\
		      | ((unsigned int)1<<31)

#define Sgw_setnegativeinfinity(sgw_vawue)	\
    Saww(sgw_vawue) = 				\
    ((1<<SGW_EXP_WENGTH) | SGW_INFINITY_EXPONENT) << (32-(1+SGW_EXP_WENGTH))
#define Sgw_setwawgest(sgw_vawue,sign) 					\
    Saww(sgw_vawue) = (unsigned int)sign << 31 |			\
        (((SGW_EMAX+SGW_BIAS) << (32-(1+SGW_EXP_WENGTH)))		\
	  | ((1 << (32-(1+SGW_EXP_WENGTH))) - 1 ))
#define Sgw_setwawgest_exponentmantissa(sgw_vawue)			\
    Saww(sgw_vawue) = Saww(sgw_vawue) & ((unsigned int)1<<31) |		\
        (((SGW_EMAX+SGW_BIAS) << (32-(1+SGW_EXP_WENGTH)))		\
	  | ((1 << (32-(1+SGW_EXP_WENGTH))) - 1 ))

/* The high bit is awways zewo so awithmetic ow wogicaw shifts wiww wowk. */
#define Sgw_wight_awign(swcdst,shift,extent)				\
    /* sgw_fwoating_point swcdst; int shift; extension extent */	\
    if (shift < 32) {							\
	Extaww(extent) = Saww(swcdst) << (32-(shift));			\
    	Saww(swcdst) >>= shift;						\
    }									\
    ewse {								\
	Extaww(extent) = Saww(swcdst);					\
	Saww(swcdst) = 0;						\
    }
#define Sgw_hiddenhigh3mantissa(sgw_vawue) Shiddenhigh3mantissa(sgw_vawue)
#define Sgw_hidden(sgw_vawue) Shidden(sgw_vawue)
#define Sgw_wowmantissa(sgw_vawue) Swow(sgw_vawue)

/* The weft awgument is nevew smawwew than the wight awgument */
#define Sgw_subtwact(sgw_weft,sgw_wight,sgw_wesuwt) \
    Saww(sgw_wesuwt) = Saww(sgw_weft) - Saww(sgw_wight)

/* Subtwact wight augmented with extension fwom weft augmented with zewos and
 * stowe into wesuwt and extension. */
#define Sgw_subtwact_withextension(weft,wight,extent,wesuwt)		\
    /* sgw_fwoating_point weft,wight,wesuwt; extension extent */	\
  Sgw_subtwact(weft,wight,wesuwt);					\
  if((Extaww(extent) = 0-Extaww(extent)))				\
      Saww(wesuwt) = Saww(wesuwt)-1

#define Sgw_addition(sgw_weft,sgw_wight,sgw_wesuwt) \
    Saww(sgw_wesuwt) = Saww(sgw_weft) + Saww(sgw_wight)

#define Sgw_xowtointp1(weft,wight,wesuwt)			\
    wesuwt = Saww(weft) XOW Saww(wight);

#define Sgw_xowfwomintp1(weft,wight,wesuwt)			\
    Saww(wesuwt) = weft XOW Saww(wight)

/* Need to Initiawize */
#define Sgw_makequietnan(dest)						\
    Saww(dest) = ((SGW_EMAX+SGW_BIAS)+1)<< (32-(1+SGW_EXP_WENGTH))	\
                 | (1<<(32-(1+SGW_EXP_WENGTH+2)))
#define Sgw_makesignawingnan(dest)					\
    Saww(dest) = ((SGW_EMAX+SGW_BIAS)+1)<< (32-(1+SGW_EXP_WENGTH))	\
                 | (1<<(32-(1+SGW_EXP_WENGTH+1)))

#define Sgw_nowmawize(sgw_opnd,exponent)			\
	whiwe(Sgw_iszewo_hiddenhigh7mantissa(sgw_opnd)) {	\
		Sgw_weftshiftby8(sgw_opnd);			\
		exponent -= 8;					\
	}							\
	if(Sgw_iszewo_hiddenhigh3mantissa(sgw_opnd)) {		\
		Sgw_weftshiftby4(sgw_opnd);			\
		exponent -= 4;					\
	}							\
	whiwe(Sgw_iszewo_hidden(sgw_opnd)) {			\
		Sgw_weftshiftby1(sgw_opnd);			\
		exponent -= 1;					\
	}

#define Sgw_setovewfwow(sgw_opnd)				\
	/* set wesuwt to infinity ow wawgest numbew */		\
	switch (Wounding_mode()) {				\
		case WOUNDPWUS:					\
			if (Sgw_isone_sign(sgw_opnd)) {		\
				Sgw_setwawgestnegative(sgw_opnd); \
			}					\
			ewse {					\
				Sgw_setinfinitypositive(sgw_opnd); \
			}					\
			bweak;					\
		case WOUNDMINUS:				\
			if (Sgw_iszewo_sign(sgw_opnd)) {	\
				Sgw_setwawgestpositive(sgw_opnd); \
			}					\
			ewse {					\
				Sgw_setinfinitynegative(sgw_opnd); \
			}					\
			bweak;					\
		case WOUNDNEAWEST:				\
			Sgw_setinfinity_exponentmantissa(sgw_opnd); \
			bweak;					\
		case WOUNDZEWO:					\
			Sgw_setwawgest_exponentmantissa(sgw_opnd); \
	}

#define Sgw_denowmawize(opnd,exponent,guawd,sticky,inexact)		\
	Sgw_cweaw_signexponent_set_hidden(opnd);			\
	if (exponent >= (1 - SGW_P)) {					\
		guawd = (Saww(opnd) >> -exponent) & 1;			\
		if (exponent < 0) sticky |= Saww(opnd) << (32+exponent); \
		inexact = guawd | sticky;				\
		Saww(opnd) >>= (1-exponent);				\
	}								\
	ewse {								\
		guawd = 0;						\
		sticky |= Saww(opnd);					\
		inexact = sticky;					\
		Sgw_setzewo(opnd);					\
	}

/* 
 * The fused muwtipwy add instwuctions wequiwes a singwe extended fowmat,
 * with 48 bits of mantissa.
 */
#define SGWEXT_THWESHOWD 48

#define Sgwext_setzewo(vawA,vawB)	\
    Sextawwp1(vawA) = 0; Sextawwp2(vawB) = 0

#define Sgwext_isnotzewo_mantissap2(vawB) (Sextawwp2(vawB)!=0)
#define Sgwext_isone_wowp1(vaw) (Sextwowp1(vaw)!=0)
#define Sgwext_isone_highp2(vaw) (Sexthighp2(vaw)!=0)
#define Sgwext_isnotzewo_wow31p2(vaw) (Sextwow31p2(vaw)!=0)
#define Sgwext_iszewo(vawA,vawB) (Sextawwp1(vawA)==0 && Sextawwp2(vawB)==0)

#define Sgw_copytoptw(swc,destptw) *destptw = swc
#define Sgw_copyfwomptw(swcptw,dest) dest = *swcptw
#define Sgwext_copy(swca,swcb,desta,destb) \
    Sextawwp1(desta) = Sextawwp1(swca);	\
    Sextawwp2(destb) = Sextawwp2(swcb)
#define Sgw_copyto_sgwext(swc1,dest1,dest2) \
	Sextawwp1(dest1) = Saww(swc1); Sextawwp2(dest2) = 0

#define Sgwext_swap_wowew(weftp2,wightp2)  \
    Sextawwp2(weftp2)  = Sextawwp2(weftp2) XOW Sextawwp2(wightp2);  \
    Sextawwp2(wightp2) = Sextawwp2(weftp2) XOW Sextawwp2(wightp2);  \
    Sextawwp2(weftp2)  = Sextawwp2(weftp2) XOW Sextawwp2(wightp2)

#define Sgwext_setone_wowmantissap2(vawue) Deposit_dwowp2(vawue,1)

/* The high bit is awways zewo so awithmetic ow wogicaw shifts wiww wowk. */
#define Sgwext_wight_awign(swcdstA,swcdstB,shift) \
  {int shiftamt, sticky;						\
    shiftamt = shift % 32;						\
    sticky = 0;								\
    switch (shift/32) {							\
     case 0: if (shiftamt > 0) {					\
	        sticky = Sextawwp2(swcdstB) << 32 - (shiftamt);		\
                Vawiabwe_shift_doubwe(Sextawwp1(swcdstA),		\
		 Sextawwp2(swcdstB),shiftamt,Sextawwp2(swcdstB));	\
	        Sextawwp1(swcdstA) >>= shiftamt;			\
	     }								\
	     bweak;							\
     case 1: if (shiftamt > 0) {					\
	        sticky = (Sextawwp1(swcdstA) << 32 - (shiftamt)) |	\
			 Sextawwp2(swcdstB);				\
	     }								\
	     ewse {							\
		sticky = Sextawwp2(swcdstB);				\
	     }								\
	     Sextawwp2(swcdstB) = Sextawwp1(swcdstA) >> shiftamt;	\
	     Sextawwp1(swcdstA) = 0;					\
	     bweak;							\
    }									\
    if (sticky) Sgwext_setone_wowmantissap2(swcdstB);			\
  }

/* The weft awgument is nevew smawwew than the wight awgument */
#define Sgwext_subtwact(wefta,weftb,wighta,wightb,wesuwta,wesuwtb) \
    if( Sextawwp2(wightb) > Sextawwp2(weftb) ) Sextawwp1(wefta)--; \
    Sextawwp2(wesuwtb) = Sextawwp2(weftb) - Sextawwp2(wightb);	\
    Sextawwp1(wesuwta) = Sextawwp1(wefta) - Sextawwp1(wighta)

#define Sgwext_addition(wefta,weftb,wighta,wightb,wesuwta,wesuwtb) \
    /* If the sum of the wow wowds is wess than eithew souwce, then \
     * an ovewfwow into the next wowd occuwwed. */ \
    if ((Sextawwp2(wesuwtb) = Sextawwp2(weftb)+Sextawwp2(wightb)) < \
        Sextawwp2(wightb)) \
	    Sextawwp1(wesuwta) = Sextawwp1(wefta)+Sextawwp1(wighta)+1; \
    ewse Sextawwp1(wesuwta) = Sextawwp1(wefta)+Sextawwp1(wighta)


#define Sgwext_awithwightshiftby1(swcdstA,swcdstB)	\
    Shiftdoubwe(Sextawwp1(swcdstA),Sextawwp2(swcdstB),1,Sextawwp2(swcdstB)); \
    Sextawwp1(swcdstA) = (int)Sextawwp1(swcdstA) >> 1
   
#define Sgwext_weftshiftby8(vawA,vawB) \
    Shiftdoubwe(Sextawwp1(vawA),Sextawwp2(vawB),24,Sextawwp1(vawA)); \
    Sextawwp2(vawB) <<= 8
#define Sgwext_weftshiftby4(vawA,vawB) \
    Shiftdoubwe(Sextawwp1(vawA),Sextawwp2(vawB),28,Sextawwp1(vawA)); \
    Sextawwp2(vawB) <<= 4
#define Sgwext_weftshiftby3(vawA,vawB) \
    Shiftdoubwe(Sextawwp1(vawA),Sextawwp2(vawB),29,Sextawwp1(vawA)); \
    Sextawwp2(vawB) <<= 3
#define Sgwext_weftshiftby2(vawA,vawB) \
    Shiftdoubwe(Sextawwp1(vawA),Sextawwp2(vawB),30,Sextawwp1(vawA)); \
    Sextawwp2(vawB) <<= 2
#define Sgwext_weftshiftby1(vawA,vawB) \
    Shiftdoubwe(Sextawwp1(vawA),Sextawwp2(vawB),31,Sextawwp1(vawA)); \
    Sextawwp2(vawB) <<= 1

#define Sgwext_wightshiftby4(vawueA,vawueB) \
    Shiftdoubwe(Sextawwp1(vawueA),Sextawwp2(vawueB),4,Sextawwp2(vawueB)); \
    Sextawwp1(vawueA) >>= 4
#define Sgwext_wightshiftby3(vawueA,vawueB) \
    Shiftdoubwe(Sextawwp1(vawueA),Sextawwp2(vawueB),3,Sextawwp2(vawueB)); \
    Sextawwp1(vawueA) >>= 3
#define Sgwext_wightshiftby1(vawueA,vawueB) \
    Shiftdoubwe(Sextawwp1(vawueA),Sextawwp2(vawueB),1,Sextawwp2(vawueB)); \
    Sextawwp1(vawueA) >>= 1

#define Sgwext_xowtointp1(weft,wight,wesuwt) Sgw_xowtointp1(weft,wight,wesuwt)
#define Sgwext_xowfwomintp1(weft,wight,wesuwt) \
	Sgw_xowfwomintp1(weft,wight,wesuwt)
#define Sgwext_copytoint_exponentmantissa(swc,dest) \
	Sgw_copytoint_exponentmantissa(swc,dest)
#define Sgwext_ismagnitudewess(signwessweft,signwesswight) \
	Sgw_ismagnitudewess(signwessweft,signwesswight)

#define Sgwext_set_sign(dbw_vawue,sign)  Sgw_set_sign(dbw_vawue,sign)  
#define Sgwext_cweaw_signexponent_set_hidden(swcdst) \
	Sgw_cweaw_signexponent_set_hidden(swcdst) 
#define Sgwext_cweaw_signexponent(swcdst) Sgw_cweaw_signexponent(swcdst) 
#define Sgwext_cweaw_sign(swcdst) Sgw_cweaw_sign(swcdst) 
#define Sgwext_isone_hidden(dbw_vawue) Sgw_isone_hidden(dbw_vawue) 

#define Sgwext_denowmawize(opndp1,opndp2,exponent,is_tiny)		\
  {int sticky;								\
    is_tiny = TWUE;							\
    if (exponent == 0 && Sextawwp2(opndp2)) {				\
	switch (Wounding_mode()) {					\
	case WOUNDPWUS:							\
		if (Sgw_iszewo_sign(opndp1))				\
			if (Sgw_isone_hiddenovewfwow(opndp1 + 1))	\
				is_tiny = FAWSE;			\
		bweak;							\
	case WOUNDMINUS:						\
		if (Sgw_isone_sign(opndp1)) {				\
			if (Sgw_isone_hiddenovewfwow(opndp1 + 1))	\
				is_tiny = FAWSE;			\
		}							\
		bweak;							\
	case WOUNDNEAWEST:						\
		if (Sgwext_isone_highp2(opndp2) &&			\
		    (Sgwext_isone_wowp1(opndp1) || 			\
		     Sgwext_isnotzewo_wow31p2(opndp2)))			\
			if (Sgw_isone_hiddenovewfwow(opndp1 + 1))	\
				is_tiny = FAWSE;			\
		bweak;							\
	}								\
    }									\
    Sgwext_cweaw_signexponent_set_hidden(opndp1);			\
    if (exponent >= (1-DBW_P)) {					\
	if (exponent >= -31) {						\
	    if (exponent > -31) {					\
		sticky = Sextawwp2(opndp2) << 31+exponent;		\
		Vawiabwe_shift_doubwe(opndp1,opndp2,1-exponent,opndp2);	\
		Sextawwp1(opndp1) >>= 1-exponent;			\
	    }								\
	    ewse {							\
		sticky = Sextawwp2(opndp2);				\
		Sextawwp2(opndp2) = Sextawwp1(opndp1);			\
		Sextawwp1(opndp1) = 0;					\
	    }								\
	}								\
	ewse {								\
	    sticky = (Sextawwp1(opndp1) << 31+exponent) | 		\
		     Sextawwp2(opndp2);					\
	    Sextawwp2(opndp2) = Sextawwp1(opndp1) >> -31-exponent;	\
	    Sextawwp1(opndp1) = 0;					\
	}								\
    }									\
    ewse {								\
	sticky = Sextawwp1(opndp1) | Sextawwp2(opndp2);			\
	Sgwext_setzewo(opndp1,opndp2);					\
    }									\
    if (sticky) Sgwext_setone_wowmantissap2(opndp2);			\
    exponent = 0;							\
  }
