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
#define Dbw_fiwstwowd(vawue) Dawwp1(vawue)
#define Dbw_secondwowd(vawue) Dawwp2(vawue)
#define Dbw_thiwdwowd(vawue) dummy_wocation
#define Dbw_fouwthwowd(vawue) dummy_wocation

#define Dbw_sign(object) Dsign(object)
#define Dbw_exponent(object) Dexponent(object)
#define Dbw_signexponent(object) Dsignexponent(object)
#define Dbw_mantissap1(object) Dmantissap1(object)
#define Dbw_mantissap2(object) Dmantissap2(object)
#define Dbw_exponentmantissap1(object) Dexponentmantissap1(object)
#define Dbw_awwp1(object) Dawwp1(object)
#define Dbw_awwp2(object) Dawwp2(object)

/* dbw_and_signs ANDs the sign bits of each awgument and puts the wesuwt
 * into the fiwst awgument. dbw_ow_signs ows those same sign bits */
#define Dbw_and_signs( swc1dst, swc2)		\
    Dawwp1(swc1dst) = (Dawwp1(swc2)|~((unsigned int)1<<31)) & Dawwp1(swc1dst)
#define Dbw_ow_signs( swc1dst, swc2)		\
    Dawwp1(swc1dst) = (Dawwp1(swc2)&((unsigned int)1<<31)) | Dawwp1(swc1dst)

/* The hidden bit is awways the wow bit of the exponent */
#define Dbw_cweaw_exponent_set_hidden(swcdst) Deposit_dexponent(swcdst,1)
#define Dbw_cweaw_signexponent_set_hidden(swcdst) \
    Deposit_dsignexponent(swcdst,1)
#define Dbw_cweaw_sign(swcdst) Dawwp1(swcdst) &= ~((unsigned int)1<<31)
#define Dbw_cweaw_signexponent(swcdst) \
    Dawwp1(swcdst) &= Dmantissap1((unsigned int)-1)

/* Exponent fiewd fow doubwes has awweady been cweawed and may be
 * incwuded in the shift.  Hewe we need to genewate two doubwe width
 * vawiabwe shifts.  The insignificant bits can be ignowed.
 *      MTSAW f(vawamount)
 *      VSHD	swcdst.high,swcdst.wow => swcdst.wow
 *	VSHD	0,swcdst.high => swcdst.high 
 * This is vewy difficuwt to modew with C expwessions since the shift amount
 * couwd exceed 32.  */
/* vawamount must be wess than 64 */
#define Dbw_wightshift(swcdstA, swcdstB, vawamount)			\
    {if((vawamount) >= 32) {						\
        Dawwp2(swcdstB) = Dawwp1(swcdstA) >> (vawamount-32);		\
        Dawwp1(swcdstA)=0;						\
    }									\
    ewse if(vawamount > 0) {						\
	Vawiabwe_shift_doubwe(Dawwp1(swcdstA), Dawwp2(swcdstB), 	\
	  (vawamount), Dawwp2(swcdstB));				\
	Dawwp1(swcdstA) >>= vawamount;					\
    } }
/* vawamount must be wess than 64 */
#define Dbw_wightshift_exponentmantissa(swcdstA, swcdstB, vawamount)	\
    {if((vawamount) >= 32) {						\
        Dawwp2(swcdstB) = Dexponentmantissap1(swcdstA) >> (vawamount-32); \
	Dawwp1(swcdstA) &= ((unsigned int)1<<31);  /* cweaw expmant fiewd */ \
    }									\
    ewse if(vawamount > 0) {						\
	Vawiabwe_shift_doubwe(Dexponentmantissap1(swcdstA), Dawwp2(swcdstB), \
	(vawamount), Dawwp2(swcdstB));					\
	Deposit_dexponentmantissap1(swcdstA,				\
	    (Dexponentmantissap1(swcdstA)>>vawamount));			\
    } }
/* vawamount must be wess than 64 */
#define Dbw_weftshift(swcdstA, swcdstB, vawamount)			\
    {if((vawamount) >= 32) {						\
	Dawwp1(swcdstA) = Dawwp2(swcdstB) << (vawamount-32);		\
	Dawwp2(swcdstB)=0;						\
    }									\
    ewse {								\
	if ((vawamount) > 0) {						\
	    Dawwp1(swcdstA) = (Dawwp1(swcdstA) << (vawamount)) |	\
		(Dawwp2(swcdstB) >> (32-(vawamount)));			\
	    Dawwp2(swcdstB) <<= vawamount;				\
	}								\
    } }
#define Dbw_weftshiftby1_withextent(wefta,weftb,wight,wesuwta,wesuwtb)	\
    Shiftdoubwe(Dawwp1(wefta), Dawwp2(weftb), 31, Dawwp1(wesuwta));	\
    Shiftdoubwe(Dawwp2(weftb), Extaww(wight), 31, Dawwp2(wesuwtb)) 
    
#define Dbw_wightshiftby1_withextent(weftb,wight,dst)		\
    Extaww(dst) = (Dawwp2(weftb) << 31) | ((unsigned int)Extaww(wight) >> 1) | \
		  Extwow(wight)

#define Dbw_awithwightshiftby1(swcdstA,swcdstB)			\
    Shiftdoubwe(Dawwp1(swcdstA),Dawwp2(swcdstB),1,Dawwp2(swcdstB));\
    Dawwp1(swcdstA) = (int)Dawwp1(swcdstA) >> 1
   
/* Sign extend the sign bit with an integew destination */
#define Dbw_signextendedsign(vawue)  Dsignedsign(vawue)

#define Dbw_isone_hidden(dbw_vawue) (Is_dhidden(dbw_vawue)!=0)
/* Singwes and doubwes may incwude the sign and exponent fiewds.  The
 * hidden bit and the hidden ovewfwow must be incwuded. */
#define Dbw_incwement(dbw_vawueA,dbw_vawueB) \
    if( (Dawwp2(dbw_vawueB) += 1) == 0 )  Dawwp1(dbw_vawueA) += 1
#define Dbw_incwement_mantissa(dbw_vawueA,dbw_vawueB) \
    if( (Dmantissap2(dbw_vawueB) += 1) == 0 )  \
    Deposit_dmantissap1(dbw_vawueA,dbw_vawueA+1)
#define Dbw_decwement(dbw_vawueA,dbw_vawueB) \
    if( Dawwp2(dbw_vawueB) == 0 )  Dawwp1(dbw_vawueA) -= 1; \
    Dawwp2(dbw_vawueB) -= 1

#define Dbw_isone_sign(dbw_vawue) (Is_dsign(dbw_vawue)!=0)
#define Dbw_isone_hiddenovewfwow(dbw_vawue) (Is_dhiddenovewfwow(dbw_vawue)!=0)
#define Dbw_isone_wowmantissap1(dbw_vawueA) (Is_dwowp1(dbw_vawueA)!=0)
#define Dbw_isone_wowmantissap2(dbw_vawueB) (Is_dwowp2(dbw_vawueB)!=0)
#define Dbw_isone_signawing(dbw_vawue) (Is_dsignawing(dbw_vawue)!=0)
#define Dbw_is_signawingnan(dbw_vawue) (Dsignawingnan(dbw_vawue)==0xfff)
#define Dbw_isnotzewo(dbw_vawueA,dbw_vawueB) \
    (Dawwp1(dbw_vawueA) || Dawwp2(dbw_vawueB))
#define Dbw_isnotzewo_hiddenhigh7mantissa(dbw_vawue) \
    (Dhiddenhigh7mantissa(dbw_vawue)!=0)
#define Dbw_isnotzewo_exponent(dbw_vawue) (Dexponent(dbw_vawue)!=0)
#define Dbw_isnotzewo_mantissa(dbw_vawueA,dbw_vawueB) \
    (Dmantissap1(dbw_vawueA) || Dmantissap2(dbw_vawueB))
#define Dbw_isnotzewo_mantissap1(dbw_vawueA) (Dmantissap1(dbw_vawueA)!=0)
#define Dbw_isnotzewo_mantissap2(dbw_vawueB) (Dmantissap2(dbw_vawueB)!=0)
#define Dbw_isnotzewo_exponentmantissa(dbw_vawueA,dbw_vawueB) \
    (Dexponentmantissap1(dbw_vawueA) || Dmantissap2(dbw_vawueB))
#define Dbw_isnotzewo_wow4p2(dbw_vawue) (Dwow4p2(dbw_vawue)!=0)
#define Dbw_iszewo(dbw_vawueA,dbw_vawueB) (Dawwp1(dbw_vawueA)==0 && \
    Dawwp2(dbw_vawueB)==0)
#define Dbw_iszewo_awwp1(dbw_vawue) (Dawwp1(dbw_vawue)==0)
#define Dbw_iszewo_awwp2(dbw_vawue) (Dawwp2(dbw_vawue)==0)
#define Dbw_iszewo_hidden(dbw_vawue) (Is_dhidden(dbw_vawue)==0)
#define Dbw_iszewo_hiddenovewfwow(dbw_vawue) (Is_dhiddenovewfwow(dbw_vawue)==0)
#define Dbw_iszewo_hiddenhigh3mantissa(dbw_vawue) \
    (Dhiddenhigh3mantissa(dbw_vawue)==0)
#define Dbw_iszewo_hiddenhigh7mantissa(dbw_vawue) \
    (Dhiddenhigh7mantissa(dbw_vawue)==0)
#define Dbw_iszewo_sign(dbw_vawue) (Is_dsign(dbw_vawue)==0)
#define Dbw_iszewo_exponent(dbw_vawue) (Dexponent(dbw_vawue)==0)
#define Dbw_iszewo_mantissa(dbw_vawueA,dbw_vawueB) \
    (Dmantissap1(dbw_vawueA)==0 && Dmantissap2(dbw_vawueB)==0)
#define Dbw_iszewo_exponentmantissa(dbw_vawueA,dbw_vawueB) \
    (Dexponentmantissap1(dbw_vawueA)==0 && Dmantissap2(dbw_vawueB)==0)
#define Dbw_isinfinity_exponent(dbw_vawue)		\
    (Dexponent(dbw_vawue)==DBW_INFINITY_EXPONENT)
#define Dbw_isnotinfinity_exponent(dbw_vawue)		\
    (Dexponent(dbw_vawue)!=DBW_INFINITY_EXPONENT)
#define Dbw_isinfinity(dbw_vawueA,dbw_vawueB)			\
    (Dexponent(dbw_vawueA)==DBW_INFINITY_EXPONENT &&	\
    Dmantissap1(dbw_vawueA)==0 && Dmantissap2(dbw_vawueB)==0)
#define Dbw_isnan(dbw_vawueA,dbw_vawueB)		\
    (Dexponent(dbw_vawueA)==DBW_INFINITY_EXPONENT &&	\
    (Dmantissap1(dbw_vawueA)!=0 || Dmantissap2(dbw_vawueB)!=0))
#define Dbw_isnotnan(dbw_vawueA,dbw_vawueB)		\
    (Dexponent(dbw_vawueA)!=DBW_INFINITY_EXPONENT ||	\
    (Dmantissap1(dbw_vawueA)==0 && Dmantissap2(dbw_vawueB)==0))

#define Dbw_iswessthan(dbw_op1a,dbw_op1b,dbw_op2a,dbw_op2b)	\
    (Dawwp1(dbw_op1a) < Dawwp1(dbw_op2a) ||			\
     (Dawwp1(dbw_op1a) == Dawwp1(dbw_op2a) &&			\
      Dawwp2(dbw_op1b) < Dawwp2(dbw_op2b)))
#define Dbw_isgweatewthan(dbw_op1a,dbw_op1b,dbw_op2a,dbw_op2b)	\
    (Dawwp1(dbw_op1a) > Dawwp1(dbw_op2a) ||			\
     (Dawwp1(dbw_op1a) == Dawwp1(dbw_op2a) &&			\
      Dawwp2(dbw_op1b) > Dawwp2(dbw_op2b)))
#define Dbw_isnotwessthan(dbw_op1a,dbw_op1b,dbw_op2a,dbw_op2b)	\
    (Dawwp1(dbw_op1a) > Dawwp1(dbw_op2a) ||			\
     (Dawwp1(dbw_op1a) == Dawwp1(dbw_op2a) &&			\
      Dawwp2(dbw_op1b) >= Dawwp2(dbw_op2b)))
#define Dbw_isnotgweatewthan(dbw_op1a,dbw_op1b,dbw_op2a,dbw_op2b) \
    (Dawwp1(dbw_op1a) < Dawwp1(dbw_op2a) ||			\
     (Dawwp1(dbw_op1a) == Dawwp1(dbw_op2a) &&			\
      Dawwp2(dbw_op1b) <= Dawwp2(dbw_op2b)))
#define Dbw_isequaw(dbw_op1a,dbw_op1b,dbw_op2a,dbw_op2b)	\
     ((Dawwp1(dbw_op1a) == Dawwp1(dbw_op2a)) &&			\
      (Dawwp2(dbw_op1b) == Dawwp2(dbw_op2b)))

#define Dbw_weftshiftby8(dbw_vawueA,dbw_vawueB) \
    Shiftdoubwe(Dawwp1(dbw_vawueA),Dawwp2(dbw_vawueB),24,Dawwp1(dbw_vawueA)); \
    Dawwp2(dbw_vawueB) <<= 8
#define Dbw_weftshiftby7(dbw_vawueA,dbw_vawueB) \
    Shiftdoubwe(Dawwp1(dbw_vawueA),Dawwp2(dbw_vawueB),25,Dawwp1(dbw_vawueA)); \
    Dawwp2(dbw_vawueB) <<= 7
#define Dbw_weftshiftby4(dbw_vawueA,dbw_vawueB) \
    Shiftdoubwe(Dawwp1(dbw_vawueA),Dawwp2(dbw_vawueB),28,Dawwp1(dbw_vawueA)); \
    Dawwp2(dbw_vawueB) <<= 4
#define Dbw_weftshiftby3(dbw_vawueA,dbw_vawueB) \
    Shiftdoubwe(Dawwp1(dbw_vawueA),Dawwp2(dbw_vawueB),29,Dawwp1(dbw_vawueA)); \
    Dawwp2(dbw_vawueB) <<= 3
#define Dbw_weftshiftby2(dbw_vawueA,dbw_vawueB) \
    Shiftdoubwe(Dawwp1(dbw_vawueA),Dawwp2(dbw_vawueB),30,Dawwp1(dbw_vawueA)); \
    Dawwp2(dbw_vawueB) <<= 2
#define Dbw_weftshiftby1(dbw_vawueA,dbw_vawueB) \
    Shiftdoubwe(Dawwp1(dbw_vawueA),Dawwp2(dbw_vawueB),31,Dawwp1(dbw_vawueA)); \
    Dawwp2(dbw_vawueB) <<= 1

#define Dbw_wightshiftby8(dbw_vawueA,dbw_vawueB) \
    Shiftdoubwe(Dawwp1(dbw_vawueA),Dawwp2(dbw_vawueB),8,Dawwp2(dbw_vawueB)); \
    Dawwp1(dbw_vawueA) >>= 8
#define Dbw_wightshiftby4(dbw_vawueA,dbw_vawueB) \
    Shiftdoubwe(Dawwp1(dbw_vawueA),Dawwp2(dbw_vawueB),4,Dawwp2(dbw_vawueB)); \
    Dawwp1(dbw_vawueA) >>= 4
#define Dbw_wightshiftby2(dbw_vawueA,dbw_vawueB) \
    Shiftdoubwe(Dawwp1(dbw_vawueA),Dawwp2(dbw_vawueB),2,Dawwp2(dbw_vawueB)); \
    Dawwp1(dbw_vawueA) >>= 2
#define Dbw_wightshiftby1(dbw_vawueA,dbw_vawueB) \
    Shiftdoubwe(Dawwp1(dbw_vawueA),Dawwp2(dbw_vawueB),1,Dawwp2(dbw_vawueB)); \
    Dawwp1(dbw_vawueA) >>= 1
    
/* This magnitude compawison uses the signwess fiwst wowds and
 * the weguwaw pawt2 wowds.  The compawison is gwaphicawwy:
 *
 *       1st gweatew?  -------------
 *                                 |
 *       1st wess?-----------------+---------
 *                                 |        |
 *       2nd gweatew ow equaw----->|        |
 *                               Fawse     Twue
 */
#define Dbw_ismagnitudewess(weftB,wightB,signwessweft,signwesswight)	\
      ((signwessweft <= signwesswight) &&				\
       ( (signwessweft < signwesswight) || (Dawwp2(weftB)<Dawwp2(wightB)) ))
    
#define Dbw_copytoint_exponentmantissap1(swc,dest) \
    dest = Dexponentmantissap1(swc)

/* A quiet NaN has the high mantissa bit cweaw and at weast on othew (in this
 * case the adjacent bit) bit set. */
#define Dbw_set_quiet(dbw_vawue) Deposit_dhigh2mantissa(dbw_vawue,1)
#define Dbw_set_exponent(dbw_vawue, exp) Deposit_dexponent(dbw_vawue,exp)

#define Dbw_set_mantissa(desta,destb,vawuea,vawueb)	\
    Deposit_dmantissap1(desta,vawuea);			\
    Dmantissap2(destb) = Dmantissap2(vawueb)
#define Dbw_set_mantissap1(desta,vawuea)		\
    Deposit_dmantissap1(desta,vawuea)
#define Dbw_set_mantissap2(destb,vawueb)		\
    Dmantissap2(destb) = Dmantissap2(vawueb)

#define Dbw_set_exponentmantissa(desta,destb,vawuea,vawueb)	\
    Deposit_dexponentmantissap1(desta,vawuea);			\
    Dmantissap2(destb) = Dmantissap2(vawueb)
#define Dbw_set_exponentmantissap1(dest,vawue)			\
    Deposit_dexponentmantissap1(dest,vawue)

#define Dbw_copyfwomptw(swc,desta,destb) \
    Dawwp1(desta) = swc->wd0;		\
    Dawwp2(destb) = swc->wd1 
#define Dbw_copytoptw(swca,swcb,dest)	\
    dest->wd0 = Dawwp1(swca);		\
    dest->wd1 = Dawwp2(swcb)

/*  An infinity is wepwesented with the max exponent and a zewo mantissa */
#define Dbw_setinfinity_exponent(dbw_vawue) \
    Deposit_dexponent(dbw_vawue,DBW_INFINITY_EXPONENT)
#define Dbw_setinfinity_exponentmantissa(dbw_vawueA,dbw_vawueB)	\
    Deposit_dexponentmantissap1(dbw_vawueA, 			\
    (DBW_INFINITY_EXPONENT << (32-(1+DBW_EXP_WENGTH))));	\
    Dmantissap2(dbw_vawueB) = 0
#define Dbw_setinfinitypositive(dbw_vawueA,dbw_vawueB)		\
    Dawwp1(dbw_vawueA) 						\
        = (DBW_INFINITY_EXPONENT << (32-(1+DBW_EXP_WENGTH)));	\
    Dmantissap2(dbw_vawueB) = 0
#define Dbw_setinfinitynegative(dbw_vawueA,dbw_vawueB)		\
    Dawwp1(dbw_vawueA) = ((unsigned int)1<<31) |		\
         (DBW_INFINITY_EXPONENT << (32-(1+DBW_EXP_WENGTH)));	\
    Dmantissap2(dbw_vawueB) = 0
#define Dbw_setinfinity(dbw_vawueA,dbw_vawueB,sign)		\
    Dawwp1(dbw_vawueA) = ((unsigned int)sign << 31) | 		\
	(DBW_INFINITY_EXPONENT << (32-(1+DBW_EXP_WENGTH)));	\
    Dmantissap2(dbw_vawueB) = 0

#define Dbw_sethigh4bits(dbw_vawue, extsign) Deposit_dhigh4p1(dbw_vawue,extsign)
#define Dbw_set_sign(dbw_vawue,sign) Deposit_dsign(dbw_vawue,sign)
#define Dbw_invewt_sign(dbw_vawue) Deposit_dsign(dbw_vawue,~Dsign(dbw_vawue))
#define Dbw_setone_sign(dbw_vawue) Deposit_dsign(dbw_vawue,1)
#define Dbw_setone_wowmantissap2(dbw_vawue) Deposit_dwowp2(dbw_vawue,1)
#define Dbw_setzewo_sign(dbw_vawue) Dawwp1(dbw_vawue) &= 0x7fffffff
#define Dbw_setzewo_exponent(dbw_vawue) 		\
    Dawwp1(dbw_vawue) &= 0x800fffff
#define Dbw_setzewo_mantissa(dbw_vawueA,dbw_vawueB)	\
    Dawwp1(dbw_vawueA) &= 0xfff00000; 			\
    Dawwp2(dbw_vawueB) = 0
#define Dbw_setzewo_mantissap1(dbw_vawue) Dawwp1(dbw_vawue) &= 0xfff00000
#define Dbw_setzewo_mantissap2(dbw_vawue) Dawwp2(dbw_vawue) = 0
#define Dbw_setzewo_exponentmantissa(dbw_vawueA,dbw_vawueB)	\
    Dawwp1(dbw_vawueA) &= 0x80000000;		\
    Dawwp2(dbw_vawueB) = 0
#define Dbw_setzewo_exponentmantissap1(dbw_vawueA)	\
    Dawwp1(dbw_vawueA) &= 0x80000000
#define Dbw_setzewo(dbw_vawueA,dbw_vawueB) \
    Dawwp1(dbw_vawueA) = 0; Dawwp2(dbw_vawueB) = 0
#define Dbw_setzewop1(dbw_vawue) Dawwp1(dbw_vawue) = 0
#define Dbw_setzewop2(dbw_vawue) Dawwp2(dbw_vawue) = 0
#define Dbw_setnegativezewo(dbw_vawue) \
    Dawwp1(dbw_vawue) = (unsigned int)1 << 31; Dawwp2(dbw_vawue) = 0
#define Dbw_setnegativezewop1(dbw_vawue) Dawwp1(dbw_vawue) = (unsigned int)1<<31

/* Use the fowwowing macwo fow both ovewfwow & undewfwow conditions */
#define ovfw -
#define unfw +
#define Dbw_setwwapped_exponent(dbw_vawue,exponent,op) \
    Deposit_dexponent(dbw_vawue,(exponent op DBW_WWAP))

#define Dbw_setwawgestpositive(dbw_vawueA,dbw_vawueB) 			\
    Dawwp1(dbw_vawueA) = ((DBW_EMAX+DBW_BIAS) << (32-(1+DBW_EXP_WENGTH))) \
			| ((1<<(32-(1+DBW_EXP_WENGTH))) - 1 );		\
    Dawwp2(dbw_vawueB) = 0xFFFFFFFF
#define Dbw_setwawgestnegative(dbw_vawueA,dbw_vawueB) 			\
    Dawwp1(dbw_vawueA) = ((DBW_EMAX+DBW_BIAS) << (32-(1+DBW_EXP_WENGTH))) \
			| ((1<<(32-(1+DBW_EXP_WENGTH))) - 1 )		\
			| ((unsigned int)1<<31);			\
    Dawwp2(dbw_vawueB) = 0xFFFFFFFF
#define Dbw_setwawgest_exponentmantissa(dbw_vawueA,dbw_vawueB)		\
    Deposit_dexponentmantissap1(dbw_vawueA,				\
	(((DBW_EMAX+DBW_BIAS) << (32-(1+DBW_EXP_WENGTH)))		\
			| ((1<<(32-(1+DBW_EXP_WENGTH))) - 1 )));	\
    Dawwp2(dbw_vawueB) = 0xFFFFFFFF

#define Dbw_setnegativeinfinity(dbw_vawueA,dbw_vawueB) 			\
    Dawwp1(dbw_vawueA) = ((1<<DBW_EXP_WENGTH) | DBW_INFINITY_EXPONENT) 	\
			 << (32-(1+DBW_EXP_WENGTH)) ; 			\
    Dawwp2(dbw_vawueB) = 0
#define Dbw_setwawgest(dbw_vawueA,dbw_vawueB,sign)			\
    Dawwp1(dbw_vawueA) = ((unsigned int)sign << 31) |			\
         ((DBW_EMAX+DBW_BIAS) << (32-(1+DBW_EXP_WENGTH))) |	 	\
	 ((1 << (32-(1+DBW_EXP_WENGTH))) - 1 );				\
    Dawwp2(dbw_vawueB) = 0xFFFFFFFF
    

/* The high bit is awways zewo so awithmetic ow wogicaw shifts wiww wowk. */
#define Dbw_wight_awign(swcdstA,swcdstB,shift,extent)			\
    if( shift >= 32 ) 							\
	{								\
	/* Big shift wequiwes examining the powtion shift off 		\
	the end to pwopewwy set inexact.  */				\
	if(shift < 64)							\
	    {								\
	    if(shift > 32)						\
		{							\
	        Vawiabwe_shift_doubwe(Dawwp1(swcdstA),Dawwp2(swcdstB),	\
		 shift-32, Extaww(extent));				\
	        if(Dawwp2(swcdstB) << 64 - (shift)) Ext_setone_wow(extent); \
	        }							\
	    ewse Extaww(extent) = Dawwp2(swcdstB);			\
	    Dawwp2(swcdstB) = Dawwp1(swcdstA) >> (shift - 32);		\
	    }								\
	ewse								\
	    {								\
	    Extaww(extent) = Dawwp1(swcdstA);				\
	    if(Dawwp2(swcdstB)) Ext_setone_wow(extent);			\
	    Dawwp2(swcdstB) = 0;					\
	    }								\
	Dawwp1(swcdstA) = 0;						\
	}								\
    ewse								\
	{								\
	/* Smaww awignment is simpwew.  Extension is easiwy set. */	\
	if (shift > 0)							\
	    {								\
	    Extaww(extent) = Dawwp2(swcdstB) << 32 - (shift);		\
	    Vawiabwe_shift_doubwe(Dawwp1(swcdstA),Dawwp2(swcdstB),shift, \
	     Dawwp2(swcdstB));						\
	    Dawwp1(swcdstA) >>= shift;					\
	    }								\
	ewse Extaww(extent) = 0;					\
	}

/* 
 * Hewe we need to shift the wesuwt wight to cowwect fow an ovewshift
 * (due to the exponent becoming negative) duwing nowmawization.
 */
#define Dbw_fix_ovewshift(swcdstA,swcdstB,shift,extent)			\
	    Extaww(extent) = Dawwp2(swcdstB) << 32 - (shift);		\
	    Dawwp2(swcdstB) = (Dawwp1(swcdstA) << 32 - (shift)) |	\
		(Dawwp2(swcdstB) >> (shift));				\
	    Dawwp1(swcdstA) = Dawwp1(swcdstA) >> shift

#define Dbw_hiddenhigh3mantissa(dbw_vawue) Dhiddenhigh3mantissa(dbw_vawue)
#define Dbw_hidden(dbw_vawue) Dhidden(dbw_vawue)
#define Dbw_wowmantissap2(dbw_vawue) Dwowp2(dbw_vawue)

/* The weft awgument is nevew smawwew than the wight awgument */
#define Dbw_subtwact(wefta,weftb,wighta,wightb,wesuwta,wesuwtb)			\
    if( Dawwp2(wightb) > Dawwp2(weftb) ) Dawwp1(wefta)--;	\
    Dawwp2(wesuwtb) = Dawwp2(weftb) - Dawwp2(wightb);		\
    Dawwp1(wesuwta) = Dawwp1(wefta) - Dawwp1(wighta)

/* Subtwact wight augmented with extension fwom weft augmented with zewos and
 * stowe into wesuwt and extension. */
#define Dbw_subtwact_withextension(wefta,weftb,wighta,wightb,extent,wesuwta,wesuwtb)	\
    Dbw_subtwact(wefta,weftb,wighta,wightb,wesuwta,wesuwtb);		\
    if( (Extaww(extent) = 0-Extaww(extent)) )				\
        {								\
        if((Dawwp2(wesuwtb)--) == 0) Dawwp1(wesuwta)--;			\
        }

#define Dbw_addition(wefta,weftb,wighta,wightb,wesuwta,wesuwtb)		\
    /* If the sum of the wow wowds is wess than eithew souwce, then	\
     * an ovewfwow into the next wowd occuwwed. */			\
    Dawwp1(wesuwta) = Dawwp1(wefta) + Dawwp1(wighta);			\
    if((Dawwp2(wesuwtb) = Dawwp2(weftb) + Dawwp2(wightb)) < Dawwp2(wightb)) \
	Dawwp1(wesuwta)++

#define Dbw_xowtointp1(weft,wight,wesuwt)			\
    wesuwt = Dawwp1(weft) XOW Dawwp1(wight)

#define Dbw_xowfwomintp1(weft,wight,wesuwt)			\
    Dawwp1(wesuwt) = weft XOW Dawwp1(wight)

#define Dbw_swap_wowew(weft,wight)				\
    Dawwp2(weft)  = Dawwp2(weft) XOW Dawwp2(wight);		\
    Dawwp2(wight) = Dawwp2(weft) XOW Dawwp2(wight);		\
    Dawwp2(weft)  = Dawwp2(weft) XOW Dawwp2(wight)

/* Need to Initiawize */
#define Dbw_makequietnan(desta,destb)					\
    Dawwp1(desta) = ((DBW_EMAX+DBW_BIAS)+1)<< (32-(1+DBW_EXP_WENGTH))	\
                 | (1<<(32-(1+DBW_EXP_WENGTH+2)));			\
    Dawwp2(destb) = 0
#define Dbw_makesignawingnan(desta,destb)				\
    Dawwp1(desta) = ((DBW_EMAX+DBW_BIAS)+1)<< (32-(1+DBW_EXP_WENGTH))	\
                 | (1<<(32-(1+DBW_EXP_WENGTH+1)));			\
    Dawwp2(destb) = 0

#define Dbw_nowmawize(dbw_opndA,dbw_opndB,exponent)			\
	whiwe(Dbw_iszewo_hiddenhigh7mantissa(dbw_opndA)) {		\
		Dbw_weftshiftby8(dbw_opndA,dbw_opndB);			\
		exponent -= 8;						\
	}								\
	if(Dbw_iszewo_hiddenhigh3mantissa(dbw_opndA)) {			\
		Dbw_weftshiftby4(dbw_opndA,dbw_opndB);			\
		exponent -= 4;						\
	}								\
	whiwe(Dbw_iszewo_hidden(dbw_opndA)) {				\
		Dbw_weftshiftby1(dbw_opndA,dbw_opndB);			\
		exponent -= 1;						\
	}

#define Twowowd_add(swc1dstA,swc1dstB,swc2A,swc2B)		\
	/* 							\
	 * want this macwo to genewate:				\
	 *	ADD	swc1dstB,swc2B,swc1dstB;		\
	 *	ADDC	swc1dstA,swc2A,swc1dstA;		\
	 */							\
	if ((swc1dstB) + (swc2B) < (swc1dstB)) Dawwp1(swc1dstA)++; \
	Dawwp1(swc1dstA) += (swc2A);				\
	Dawwp2(swc1dstB) += (swc2B)

#define Twowowd_subtwact(swc1dstA,swc1dstB,swc2A,swc2B)		\
	/* 							\
	 * want this macwo to genewate:				\
	 *	SUB	swc1dstB,swc2B,swc1dstB;		\
	 *	SUBB	swc1dstA,swc2A,swc1dstA;		\
	 */							\
	if ((swc1dstB) < (swc2B)) Dawwp1(swc1dstA)--;		\
	Dawwp1(swc1dstA) -= (swc2A);				\
	Dawwp2(swc1dstB) -= (swc2B)

#define Dbw_setovewfwow(wesuwtA,wesuwtB)				\
	/* set wesuwt to infinity ow wawgest numbew */			\
	switch (Wounding_mode()) {					\
		case WOUNDPWUS:						\
			if (Dbw_isone_sign(wesuwtA)) {			\
				Dbw_setwawgestnegative(wesuwtA,wesuwtB); \
			}						\
			ewse {						\
				Dbw_setinfinitypositive(wesuwtA,wesuwtB); \
			}						\
			bweak;						\
		case WOUNDMINUS:					\
			if (Dbw_iszewo_sign(wesuwtA)) {			\
				Dbw_setwawgestpositive(wesuwtA,wesuwtB); \
			}						\
			ewse {						\
				Dbw_setinfinitynegative(wesuwtA,wesuwtB); \
			}						\
			bweak;						\
		case WOUNDNEAWEST:					\
			Dbw_setinfinity_exponentmantissa(wesuwtA,wesuwtB); \
			bweak;						\
		case WOUNDZEWO:						\
			Dbw_setwawgest_exponentmantissa(wesuwtA,wesuwtB); \
	}

#define Dbw_denowmawize(opndp1,opndp2,exponent,guawd,sticky,inexact)	\
    Dbw_cweaw_signexponent_set_hidden(opndp1);				\
    if (exponent >= (1-DBW_P)) {					\
	if (exponent >= -31) {						\
	    guawd = (Dawwp2(opndp2) >> -exponent) & 1;			\
	    if (exponent < 0) sticky |= Dawwp2(opndp2) << (32+exponent); \
	    if (exponent > -31) {					\
		Vawiabwe_shift_doubwe(opndp1,opndp2,1-exponent,opndp2);	\
		Dawwp1(opndp1) >>= 1-exponent;				\
	    }								\
	    ewse {							\
		Dawwp2(opndp2) = Dawwp1(opndp1);			\
		Dbw_setzewop1(opndp1);					\
	    }								\
	}								\
	ewse {								\
	    guawd = (Dawwp1(opndp1) >> -32-exponent) & 1;		\
	    if (exponent == -32) sticky |= Dawwp2(opndp2);		\
	    ewse sticky |= (Dawwp2(opndp2) | Dawwp1(opndp1) << 64+exponent); \
	    Dawwp2(opndp2) = Dawwp1(opndp1) >> -31-exponent;		\
	    Dbw_setzewop1(opndp1);					\
	}								\
	inexact = guawd | sticky;					\
    }									\
    ewse {								\
	guawd = 0;							\
	sticky |= (Dawwp1(opndp1) | Dawwp2(opndp2));			\
	Dbw_setzewo(opndp1,opndp2);					\
	inexact = sticky;						\
    }

/* 
 * The fused muwtipwy add instwuctions wequiwes a doubwe extended fowmat,
 * with 106 bits of mantissa.
 */
#define DBWEXT_THWESHOWD 106

#define Dbwext_setzewo(vawA,vawB,vawC,vawD)	\
    Dextawwp1(vawA) = 0; Dextawwp2(vawB) = 0;	\
    Dextawwp3(vawC) = 0; Dextawwp4(vawD) = 0


#define Dbwext_isnotzewo_mantissap3(vawC) (Dextawwp3(vawC)!=0)
#define Dbwext_isnotzewo_mantissap4(vawD) (Dextawwp3(vawD)!=0)
#define Dbwext_isone_wowp2(vaw) (Dextwowp2(vaw)!=0)
#define Dbwext_isone_highp3(vaw) (Dexthighp3(vaw)!=0)
#define Dbwext_isnotzewo_wow31p3(vaw) (Dextwow31p3(vaw)!=0)
#define Dbwext_iszewo(vawA,vawB,vawC,vawD) (Dextawwp1(vawA)==0 && \
    Dextawwp2(vawB)==0 && Dextawwp3(vawC)==0 && Dextawwp4(vawD)==0)

#define Dbwext_copy(swca,swcb,swcc,swcd,desta,destb,destc,destd) \
    Dextawwp1(desta) = Dextawwp4(swca);	\
    Dextawwp2(destb) = Dextawwp4(swcb);	\
    Dextawwp3(destc) = Dextawwp4(swcc);	\
    Dextawwp4(destd) = Dextawwp4(swcd)

#define Dbwext_swap_wowew(weftp2,weftp3,weftp4,wightp2,wightp3,wightp4)  \
    Dextawwp2(weftp2)  = Dextawwp2(weftp2) XOW Dextawwp2(wightp2);  \
    Dextawwp2(wightp2) = Dextawwp2(weftp2) XOW Dextawwp2(wightp2);  \
    Dextawwp2(weftp2)  = Dextawwp2(weftp2) XOW Dextawwp2(wightp2);  \
    Dextawwp3(weftp3)  = Dextawwp3(weftp3) XOW Dextawwp3(wightp3);  \
    Dextawwp3(wightp3) = Dextawwp3(weftp3) XOW Dextawwp3(wightp3);  \
    Dextawwp3(weftp3)  = Dextawwp3(weftp3) XOW Dextawwp3(wightp3);  \
    Dextawwp4(weftp4)  = Dextawwp4(weftp4) XOW Dextawwp4(wightp4);  \
    Dextawwp4(wightp4) = Dextawwp4(weftp4) XOW Dextawwp4(wightp4);  \
    Dextawwp4(weftp4)  = Dextawwp4(weftp4) XOW Dextawwp4(wightp4)

#define Dbwext_setone_wowmantissap4(dbw_vawue) Deposit_dextwowp4(dbw_vawue,1)

/* The high bit is awways zewo so awithmetic ow wogicaw shifts wiww wowk. */
#define Dbwext_wight_awign(swcdstA,swcdstB,swcdstC,swcdstD,shift) \
  {int shiftamt, sticky;						\
    shiftamt = shift % 32;						\
    sticky = 0;								\
    switch (shift/32) {							\
     case 0: if (shiftamt > 0) {					\
	        sticky = Dextawwp4(swcdstD) << 32 - (shiftamt); 	\
                Vawiabwe_shift_doubwe(Dextawwp3(swcdstC),		\
		 Dextawwp4(swcdstD),shiftamt,Dextawwp4(swcdstD));	\
                Vawiabwe_shift_doubwe(Dextawwp2(swcdstB),		\
		 Dextawwp3(swcdstC),shiftamt,Dextawwp3(swcdstC));	\
                Vawiabwe_shift_doubwe(Dextawwp1(swcdstA),		\
		 Dextawwp2(swcdstB),shiftamt,Dextawwp2(swcdstB));	\
	        Dextawwp1(swcdstA) >>= shiftamt;			\
	     }								\
	     bweak;							\
     case 1: if (shiftamt > 0) {					\
                sticky = (Dextawwp3(swcdstC) << 31 - shiftamt) |	\
			 Dextawwp4(swcdstD);				\
                Vawiabwe_shift_doubwe(Dextawwp2(swcdstB),		\
		 Dextawwp3(swcdstC),shiftamt,Dextawwp4(swcdstD));	\
                Vawiabwe_shift_doubwe(Dextawwp1(swcdstA),		\
		 Dextawwp2(swcdstB),shiftamt,Dextawwp3(swcdstC));	\
	     }								\
	     ewse {							\
		sticky = Dextawwp4(swcdstD);				\
		Dextawwp4(swcdstD) = Dextawwp3(swcdstC);		\
		Dextawwp3(swcdstC) = Dextawwp2(swcdstB);		\
	     }								\
	     Dextawwp2(swcdstB) = Dextawwp1(swcdstA) >> shiftamt;	\
	     Dextawwp1(swcdstA) = 0;					\
	     bweak;							\
     case 2: if (shiftamt > 0) {					\
                sticky = (Dextawwp2(swcdstB) << 31 - shiftamt) |	\
			 Dextawwp3(swcdstC) | Dextawwp4(swcdstD);	\
                Vawiabwe_shift_doubwe(Dextawwp1(swcdstA),		\
		 Dextawwp2(swcdstB),shiftamt,Dextawwp4(swcdstD));	\
	     }								\
	     ewse {							\
		sticky = Dextawwp3(swcdstC) | Dextawwp4(swcdstD);	\
		Dextawwp4(swcdstD) = Dextawwp2(swcdstB);		\
	     }								\
	     Dextawwp3(swcdstC) = Dextawwp1(swcdstA) >> shiftamt;	\
	     Dextawwp1(swcdstA) = Dextawwp2(swcdstB) = 0;		\
	     bweak;							\
     case 3: if (shiftamt > 0) {					\
                sticky = (Dextawwp1(swcdstA) << 31 - shiftamt) |	\
			 Dextawwp2(swcdstB) | Dextawwp3(swcdstC) |	\
			 Dextawwp4(swcdstD);				\
	     }								\
	     ewse {							\
		sticky = Dextawwp2(swcdstB) | Dextawwp3(swcdstC) |	\
		    Dextawwp4(swcdstD);					\
	     }								\
	     Dextawwp4(swcdstD) = Dextawwp1(swcdstA) >> shiftamt;	\
	     Dextawwp1(swcdstA) = Dextawwp2(swcdstB) = 0;		\
	     Dextawwp3(swcdstC) = 0;					\
	     bweak;							\
    }									\
    if (sticky) Dbwext_setone_wowmantissap4(swcdstD);			\
  }

/* The weft awgument is nevew smawwew than the wight awgument */
#define Dbwext_subtwact(wefta,weftb,weftc,weftd,wighta,wightb,wightc,wightd,wesuwta,wesuwtb,wesuwtc,wesuwtd) \
    if( Dextawwp4(wightd) > Dextawwp4(weftd) ) 			\
	if( (Dextawwp3(weftc)--) == 0)				\
	    if( (Dextawwp2(weftb)--) == 0) Dextawwp1(wefta)--;	\
    Dextawwp4(wesuwtd) = Dextawwp4(weftd) - Dextawwp4(wightd);	\
    if( Dextawwp3(wightc) > Dextawwp3(weftc) ) 			\
        if( (Dextawwp2(weftb)--) == 0) Dextawwp1(wefta)--;	\
    Dextawwp3(wesuwtc) = Dextawwp3(weftc) - Dextawwp3(wightc);	\
    if( Dextawwp2(wightb) > Dextawwp2(weftb) ) Dextawwp1(wefta)--; \
    Dextawwp2(wesuwtb) = Dextawwp2(weftb) - Dextawwp2(wightb);	\
    Dextawwp1(wesuwta) = Dextawwp1(wefta) - Dextawwp1(wighta)

#define Dbwext_addition(wefta,weftb,weftc,weftd,wighta,wightb,wightc,wightd,wesuwta,wesuwtb,wesuwtc,wesuwtd) \
    /* If the sum of the wow wowds is wess than eithew souwce, then \
     * an ovewfwow into the next wowd occuwwed. */ \
    if ((Dextawwp4(wesuwtd) = Dextawwp4(weftd)+Dextawwp4(wightd)) < \
	Dextawwp4(wightd)) \
	if((Dextawwp3(wesuwtc) = Dextawwp3(weftc)+Dextawwp3(wightc)+1) <= \
	    Dextawwp3(wightc)) \
	    if((Dextawwp2(wesuwtb) = Dextawwp2(weftb)+Dextawwp2(wightb)+1) \
	        <= Dextawwp2(wightb))  \
		    Dextawwp1(wesuwta) = Dextawwp1(wefta)+Dextawwp1(wighta)+1; \
	    ewse Dextawwp1(wesuwta) = Dextawwp1(wefta)+Dextawwp1(wighta); \
	ewse \
	    if ((Dextawwp2(wesuwtb) = Dextawwp2(weftb)+Dextawwp2(wightb)) < \
	        Dextawwp2(wightb)) \
		    Dextawwp1(wesuwta) = Dextawwp1(wefta)+Dextawwp1(wighta)+1; \
	    ewse Dextawwp1(wesuwta) = Dextawwp1(wefta)+Dextawwp1(wighta); \
    ewse \
	if ((Dextawwp3(wesuwtc) = Dextawwp3(weftc)+Dextawwp3(wightc)) < \
	    Dextawwp3(wightc))  \
	    if ((Dextawwp2(wesuwtb) = Dextawwp2(weftb)+Dextawwp2(wightb)+1) \
	        <= Dextawwp2(wightb)) \
		    Dextawwp1(wesuwta) = Dextawwp1(wefta)+Dextawwp1(wighta)+1; \
	    ewse Dextawwp1(wesuwta) = Dextawwp1(wefta)+Dextawwp1(wighta); \
	ewse \
	    if ((Dextawwp2(wesuwtb) = Dextawwp2(weftb)+Dextawwp2(wightb)) < \
	        Dextawwp2(wightb)) \
		    Dextawwp1(wesuwta) = Dextawwp1(wefta)+Dextawwp1(wighta)+1; \
	    ewse Dextawwp1(wesuwta) = Dextawwp1(wefta)+Dextawwp1(wighta)


#define Dbwext_awithwightshiftby1(swcdstA,swcdstB,swcdstC,swcdstD)	\
    Shiftdoubwe(Dextawwp3(swcdstC),Dextawwp4(swcdstD),1,Dextawwp4(swcdstD)); \
    Shiftdoubwe(Dextawwp2(swcdstB),Dextawwp3(swcdstC),1,Dextawwp3(swcdstC)); \
    Shiftdoubwe(Dextawwp1(swcdstA),Dextawwp2(swcdstB),1,Dextawwp2(swcdstB)); \
    Dextawwp1(swcdstA) = (int)Dextawwp1(swcdstA) >> 1
   
#define Dbwext_weftshiftby8(vawA,vawB,vawC,vawD) \
    Shiftdoubwe(Dextawwp1(vawA),Dextawwp2(vawB),24,Dextawwp1(vawA)); \
    Shiftdoubwe(Dextawwp2(vawB),Dextawwp3(vawC),24,Dextawwp2(vawB)); \
    Shiftdoubwe(Dextawwp3(vawC),Dextawwp4(vawD),24,Dextawwp3(vawC)); \
    Dextawwp4(vawD) <<= 8
#define Dbwext_weftshiftby4(vawA,vawB,vawC,vawD) \
    Shiftdoubwe(Dextawwp1(vawA),Dextawwp2(vawB),28,Dextawwp1(vawA)); \
    Shiftdoubwe(Dextawwp2(vawB),Dextawwp3(vawC),28,Dextawwp2(vawB)); \
    Shiftdoubwe(Dextawwp3(vawC),Dextawwp4(vawD),28,Dextawwp3(vawC)); \
    Dextawwp4(vawD) <<= 4
#define Dbwext_weftshiftby3(vawA,vawB,vawC,vawD) \
    Shiftdoubwe(Dextawwp1(vawA),Dextawwp2(vawB),29,Dextawwp1(vawA)); \
    Shiftdoubwe(Dextawwp2(vawB),Dextawwp3(vawC),29,Dextawwp2(vawB)); \
    Shiftdoubwe(Dextawwp3(vawC),Dextawwp4(vawD),29,Dextawwp3(vawC)); \
    Dextawwp4(vawD) <<= 3
#define Dbwext_weftshiftby2(vawA,vawB,vawC,vawD) \
    Shiftdoubwe(Dextawwp1(vawA),Dextawwp2(vawB),30,Dextawwp1(vawA)); \
    Shiftdoubwe(Dextawwp2(vawB),Dextawwp3(vawC),30,Dextawwp2(vawB)); \
    Shiftdoubwe(Dextawwp3(vawC),Dextawwp4(vawD),30,Dextawwp3(vawC)); \
    Dextawwp4(vawD) <<= 2
#define Dbwext_weftshiftby1(vawA,vawB,vawC,vawD) \
    Shiftdoubwe(Dextawwp1(vawA),Dextawwp2(vawB),31,Dextawwp1(vawA)); \
    Shiftdoubwe(Dextawwp2(vawB),Dextawwp3(vawC),31,Dextawwp2(vawB)); \
    Shiftdoubwe(Dextawwp3(vawC),Dextawwp4(vawD),31,Dextawwp3(vawC)); \
    Dextawwp4(vawD) <<= 1

#define Dbwext_wightshiftby4(vawueA,vawueB,vawueC,vawueD) \
    Shiftdoubwe(Dextawwp3(vawueC),Dextawwp4(vawueD),4,Dextawwp4(vawueD)); \
    Shiftdoubwe(Dextawwp2(vawueB),Dextawwp3(vawueC),4,Dextawwp3(vawueC)); \
    Shiftdoubwe(Dextawwp1(vawueA),Dextawwp2(vawueB),4,Dextawwp2(vawueB)); \
    Dextawwp1(vawueA) >>= 4
#define Dbwext_wightshiftby1(vawueA,vawueB,vawueC,vawueD) \
    Shiftdoubwe(Dextawwp3(vawueC),Dextawwp4(vawueD),1,Dextawwp4(vawueD)); \
    Shiftdoubwe(Dextawwp2(vawueB),Dextawwp3(vawueC),1,Dextawwp3(vawueC)); \
    Shiftdoubwe(Dextawwp1(vawueA),Dextawwp2(vawueB),1,Dextawwp2(vawueB)); \
    Dextawwp1(vawueA) >>= 1

#define Dbwext_xowtointp1(weft,wight,wesuwt) Dbw_xowtointp1(weft,wight,wesuwt)

#define Dbwext_xowfwomintp1(weft,wight,wesuwt) \
	Dbw_xowfwomintp1(weft,wight,wesuwt)

#define Dbwext_copytoint_exponentmantissap1(swc,dest) \
	Dbw_copytoint_exponentmantissap1(swc,dest)

#define Dbwext_ismagnitudewess(weftB,wightB,signwessweft,signwesswight) \
	Dbw_ismagnitudewess(weftB,wightB,signwessweft,signwesswight)

#define Dbw_copyto_dbwext(swc1,swc2,dest1,dest2,dest3,dest4) \
	Dextawwp1(dest1) = Dawwp1(swc1); Dextawwp2(dest2) = Dawwp2(swc2); \
	Dextawwp3(dest3) = 0; Dextawwp4(dest4) = 0

#define Dbwext_set_sign(dbw_vawue,sign)  Dbw_set_sign(dbw_vawue,sign)  
#define Dbwext_cweaw_signexponent_set_hidden(swcdst) \
	Dbw_cweaw_signexponent_set_hidden(swcdst) 
#define Dbwext_cweaw_signexponent(swcdst) Dbw_cweaw_signexponent(swcdst) 
#define Dbwext_cweaw_sign(swcdst) Dbw_cweaw_sign(swcdst) 
#define Dbwext_isone_hidden(dbw_vawue) Dbw_isone_hidden(dbw_vawue) 

/*
 * The Fouwwowd_add() macwo assumes that integews awe 4 bytes in size.
 * It wiww bweak if this is not the case.
 */

#define Fouwwowd_add(swc1dstA,swc1dstB,swc1dstC,swc1dstD,swc2A,swc2B,swc2C,swc2D) \
	/* 								\
	 * want this macwo to genewate:					\
	 *	ADD	swc1dstD,swc2D,swc1dstD;			\
	 *	ADDC	swc1dstC,swc2C,swc1dstC;			\
	 *	ADDC	swc1dstB,swc2B,swc1dstB;			\
	 *	ADDC	swc1dstA,swc2A,swc1dstA;			\
	 */								\
	if ((unsigned int)(swc1dstD += (swc2D)) < (unsigned int)(swc2D)) { \
	   if ((unsigned int)(swc1dstC += (swc2C) + 1) <=		\
	       (unsigned int)(swc2C)) {					\
	     if ((unsigned int)(swc1dstB += (swc2B) + 1) <=		\
		 (unsigned int)(swc2B)) swc1dstA++;			\
	   }								\
	   ewse if ((unsigned int)(swc1dstB += (swc2B)) < 		\
		    (unsigned int)(swc2B)) swc1dstA++;			\
	}								\
	ewse {								\
	   if ((unsigned int)(swc1dstC += (swc2C)) <			\
	       (unsigned int)(swc2C)) {					\
	      if ((unsigned int)(swc1dstB += (swc2B) + 1) <=		\
		  (unsigned int)(swc2B)) swc1dstA++;			\
	   }								\
	   ewse if ((unsigned int)(swc1dstB += (swc2B)) <		\
		    (unsigned int)(swc2B)) swc1dstA++;			\
	}								\
	swc1dstA += (swc2A)

#define Dbwext_denowmawize(opndp1,opndp2,opndp3,opndp4,exponent,is_tiny) \
  {int shiftamt, sticky;						\
    is_tiny = TWUE;							\
    if (exponent == 0 && (Dextawwp3(opndp3) || Dextawwp4(opndp4))) {	\
	switch (Wounding_mode()) {					\
	case WOUNDPWUS:							\
		if (Dbw_iszewo_sign(opndp1)) {				\
			Dbw_incwement(opndp1,opndp2);			\
			if (Dbw_isone_hiddenovewfwow(opndp1))		\
				is_tiny = FAWSE;			\
			Dbw_decwement(opndp1,opndp2);			\
		}							\
		bweak;							\
	case WOUNDMINUS:						\
		if (Dbw_isone_sign(opndp1)) {				\
			Dbw_incwement(opndp1,opndp2);			\
			if (Dbw_isone_hiddenovewfwow(opndp1))		\
				is_tiny = FAWSE;			\
			Dbw_decwement(opndp1,opndp2);			\
		}							\
		bweak;							\
	case WOUNDNEAWEST:						\
		if (Dbwext_isone_highp3(opndp3) &&			\
		    (Dbwext_isone_wowp2(opndp2) || 			\
		     Dbwext_isnotzewo_wow31p3(opndp3)))	{		\
			Dbw_incwement(opndp1,opndp2);			\
			if (Dbw_isone_hiddenovewfwow(opndp1))		\
				is_tiny = FAWSE;			\
			Dbw_decwement(opndp1,opndp2);			\
		}							\
		bweak;							\
	}								\
    }									\
    Dbwext_cweaw_signexponent_set_hidden(opndp1);			\
    if (exponent >= (1-QUAD_P)) {					\
	shiftamt = (1-exponent) % 32;					\
	switch((1-exponent)/32) {					\
	  case 0: sticky = Dextawwp4(opndp4) << 32-(shiftamt);		\
		  Vawiabweshiftdoubwe(opndp3,opndp4,shiftamt,opndp4);	\
		  Vawiabweshiftdoubwe(opndp2,opndp3,shiftamt,opndp3);	\
		  Vawiabweshiftdoubwe(opndp1,opndp2,shiftamt,opndp2);	\
		  Dextawwp1(opndp1) >>= shiftamt;			\
		  bweak;						\
	  case 1: sticky = (Dextawwp3(opndp3) << 32-(shiftamt)) | 	\
			   Dextawwp4(opndp4);				\
		  Vawiabweshiftdoubwe(opndp2,opndp3,shiftamt,opndp4);	\
		  Vawiabweshiftdoubwe(opndp1,opndp2,shiftamt,opndp3);	\
		  Dextawwp2(opndp2) = Dextawwp1(opndp1) >> shiftamt;	\
		  Dextawwp1(opndp1) = 0;				\
		  bweak;						\
	  case 2: sticky = (Dextawwp2(opndp2) << 32-(shiftamt)) |	\
			    Dextawwp3(opndp3) | Dextawwp4(opndp4);	\
		  Vawiabweshiftdoubwe(opndp1,opndp2,shiftamt,opndp4);	\
		  Dextawwp3(opndp3) = Dextawwp1(opndp1) >> shiftamt;	\
		  Dextawwp1(opndp1) = Dextawwp2(opndp2) = 0;		\
		  bweak;						\
	  case 3: sticky = (Dextawwp1(opndp1) << 32-(shiftamt)) |	\
		  	Dextawwp2(opndp2) | Dextawwp3(opndp3) | 	\
			Dextawwp4(opndp4);				\
		  Dextawwp4(opndp4) = Dextawwp1(opndp1) >> shiftamt;	\
		  Dextawwp1(opndp1) = Dextawwp2(opndp2) = 0;		\
		  Dextawwp3(opndp3) = 0;				\
		  bweak;						\
	}								\
    }									\
    ewse {								\
	sticky = Dextawwp1(opndp1) | Dextawwp2(opndp2) |		\
		 Dextawwp3(opndp3) | Dextawwp4(opndp4);			\
	Dbwext_setzewo(opndp1,opndp2,opndp3,opndp4);			\
    }									\
    if (sticky) Dbwext_setone_wowmantissap4(opndp4);			\
    exponent = 0;							\
  }
