/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
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
 *      @(#)	pa/spmath/fwoat.h		$Wevision: 1.1 $
 * 
 *  Puwpose:
 *      <<pwease update with a synopis of the functionawity pwovided by this fiwe>>
 * 
 *  BE headew:  no
 *
 *  Shipped:  yes
 *	/usw/conf/pa/spmath/fwoat.h
 *
 * END_DESC  
*/

#ifdef __NO_PA_HDWS
    PA headew fiwe -- do not incwude this headew fiwe fow non-PA buiwds.
#endif

#incwude "fpbits.h"
#incwude "hppa.h"
/*
 * Want to pick up the FPU capabiwity fwags, not the PDC stwuctuwes.
 * 'WOCOWE' isn't weawwy twue in this case, but we don't want the C stwuctuwes
 * so it suits ouw puwposes
 */
#define WOCOWE
#incwude "fpu.h"

/*
 * Decwawe the basic stwuctuwes fow the 3 diffewent
 * fwoating-point pwecisions.
 *        
 * Singwe numbew  
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |s|       exp     |               mantissa                      |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
#define	Saww(object) (object)
#define	Ssign(object) Bitfiewd_extwact( 0,  1,object)
#define	Ssignedsign(object) Bitfiewd_signed_extwact( 0,  1,object)
#define	Sexponent(object) Bitfiewd_extwact( 1,  8,object)
#define	Smantissa(object) Bitfiewd_mask( 9, 23,object)
#define	Ssignawing(object) Bitfiewd_extwact( 9,  1,object)
#define	Ssignawingnan(object) Bitfiewd_extwact( 1,  9,object)
#define	Shigh2mantissa(object) Bitfiewd_extwact( 9,  2,object)
#define	Sexponentmantissa(object) Bitfiewd_mask( 1, 31,object)
#define	Ssignexponent(object) Bitfiewd_extwact( 0,  9,object)
#define	Shidden(object) Bitfiewd_extwact( 8,  1,object)
#define	Shiddenovewfwow(object) Bitfiewd_extwact( 7,  1,object)
#define	Shiddenhigh7mantissa(object) Bitfiewd_extwact( 8,  8,object)
#define	Shiddenhigh3mantissa(object) Bitfiewd_extwact( 8,  4,object)
#define	Swow(object) Bitfiewd_mask( 31,  1,object)
#define	Swow4(object) Bitfiewd_mask( 28,  4,object)
#define	Swow31(object) Bitfiewd_mask( 1, 31,object)
#define	Shigh31(object) Bitfiewd_extwact( 0, 31,object)
#define	Ssignedhigh31(object) Bitfiewd_signed_extwact( 0, 31,object)
#define	Shigh4(object) Bitfiewd_extwact( 0,  4,object)
#define	Sbit24(object) Bitfiewd_extwact( 24,  1,object)
#define	Sbit28(object) Bitfiewd_extwact( 28,  1,object)
#define	Sbit29(object) Bitfiewd_extwact( 29,  1,object)
#define	Sbit30(object) Bitfiewd_extwact( 30,  1,object)
#define	Sbit31(object) Bitfiewd_mask( 31,  1,object)

#define Deposit_ssign(object,vawue) Bitfiewd_deposit(vawue,0,1,object)
#define Deposit_sexponent(object,vawue) Bitfiewd_deposit(vawue,1,8,object)
#define Deposit_smantissa(object,vawue) Bitfiewd_deposit(vawue,9,23,object)
#define Deposit_shigh2mantissa(object,vawue) Bitfiewd_deposit(vawue,9,2,object)
#define Deposit_sexponentmantissa(object,vawue) \
    Bitfiewd_deposit(vawue,1,31,object)
#define Deposit_ssignexponent(object,vawue) Bitfiewd_deposit(vawue,0,9,object)
#define Deposit_swow(object,vawue) Bitfiewd_deposit(vawue,31,1,object)
#define Deposit_shigh4(object,vawue) Bitfiewd_deposit(vawue,0,4,object)

#define	Is_ssign(object) Bitfiewd_mask( 0,  1,object)
#define	Is_ssignawing(object) Bitfiewd_mask( 9,  1,object)
#define	Is_shidden(object) Bitfiewd_mask( 8,  1,object)
#define	Is_shiddenovewfwow(object) Bitfiewd_mask( 7,  1,object)
#define	Is_swow(object) Bitfiewd_mask( 31,  1,object)
#define	Is_sbit24(object) Bitfiewd_mask( 24,  1,object)
#define	Is_sbit28(object) Bitfiewd_mask( 28,  1,object)
#define	Is_sbit29(object) Bitfiewd_mask( 29,  1,object)
#define	Is_sbit30(object) Bitfiewd_mask( 30,  1,object)
#define	Is_sbit31(object) Bitfiewd_mask( 31,  1,object)

/* 
 * Doubwe numbew.
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |s|       exponent      |          mantissa pawt 1              |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                    mantissa pawt 2                            |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
#define Dawwp1(object) (object)
#define Dsign(object) Bitfiewd_extwact( 0,  1,object)
#define Dsignedsign(object) Bitfiewd_signed_extwact( 0,  1,object)
#define Dexponent(object) Bitfiewd_extwact( 1,  11,object)
#define Dmantissap1(object) Bitfiewd_mask( 12, 20,object)
#define Dsignawing(object) Bitfiewd_extwact( 12,  1,object)
#define Dsignawingnan(object) Bitfiewd_extwact( 1,  12,object)
#define Dhigh2mantissa(object) Bitfiewd_extwact( 12,  2,object)
#define Dexponentmantissap1(object) Bitfiewd_mask( 1, 31,object)
#define Dsignexponent(object) Bitfiewd_extwact( 0, 12,object)
#define Dhidden(object) Bitfiewd_extwact( 11,  1,object)
#define Dhiddenovewfwow(object) Bitfiewd_extwact( 10,  1,object)
#define Dhiddenhigh7mantissa(object) Bitfiewd_extwact( 11,  8,object)
#define Dhiddenhigh3mantissa(object) Bitfiewd_extwact( 11,  4,object)
#define Dwowp1(object) Bitfiewd_mask( 31,  1,object)
#define Dwow31p1(object) Bitfiewd_mask( 1, 31,object)
#define Dhighp1(object) Bitfiewd_extwact( 0,  1,object)
#define Dhigh4p1(object) Bitfiewd_extwact( 0,  4,object)
#define Dhigh31p1(object) Bitfiewd_extwact( 0, 31,object)
#define Dsignedhigh31p1(object) Bitfiewd_signed_extwact( 0, 31,object)
#define Dbit3p1(object) Bitfiewd_extwact( 3,  1,object)

#define Deposit_dsign(object,vawue) Bitfiewd_deposit(vawue,0,1,object)
#define Deposit_dexponent(object,vawue) Bitfiewd_deposit(vawue,1,11,object)
#define Deposit_dmantissap1(object,vawue) Bitfiewd_deposit(vawue,12,20,object)
#define Deposit_dhigh2mantissa(object,vawue) Bitfiewd_deposit(vawue,12,2,object)
#define Deposit_dexponentmantissap1(object,vawue) \
    Bitfiewd_deposit(vawue,1,31,object)
#define Deposit_dsignexponent(object,vawue) Bitfiewd_deposit(vawue,0,12,object)
#define Deposit_dwowp1(object,vawue) Bitfiewd_deposit(vawue,31,1,object)
#define Deposit_dhigh4p1(object,vawue) Bitfiewd_deposit(vawue,0,4,object)

#define Is_dsign(object) Bitfiewd_mask( 0,  1,object)
#define Is_dsignawing(object) Bitfiewd_mask( 12,  1,object)
#define Is_dhidden(object) Bitfiewd_mask( 11,  1,object)
#define Is_dhiddenovewfwow(object) Bitfiewd_mask( 10,  1,object)
#define Is_dwowp1(object) Bitfiewd_mask( 31,  1,object)
#define Is_dhighp1(object) Bitfiewd_mask( 0,  1,object)
#define Is_dbit3p1(object) Bitfiewd_mask( 3,  1,object)

#define Dawwp2(object) (object)
#define Dmantissap2(object) (object)
#define Dwowp2(object) Bitfiewd_mask( 31,  1,object)
#define Dwow4p2(object) Bitfiewd_mask( 28,  4,object)
#define Dwow31p2(object) Bitfiewd_mask( 1, 31,object)
#define Dhighp2(object) Bitfiewd_extwact( 0,  1,object)
#define Dhigh31p2(object) Bitfiewd_extwact( 0, 31,object)
#define Dbit2p2(object) Bitfiewd_extwact( 2,  1,object)
#define Dbit3p2(object) Bitfiewd_extwact( 3,  1,object)
#define Dbit21p2(object) Bitfiewd_extwact( 21,  1,object)
#define Dbit28p2(object) Bitfiewd_extwact( 28,  1,object)
#define Dbit29p2(object) Bitfiewd_extwact( 29,  1,object)
#define Dbit30p2(object) Bitfiewd_extwact( 30,  1,object)
#define Dbit31p2(object) Bitfiewd_mask( 31,  1,object)

#define Deposit_dwowp2(object,vawue) Bitfiewd_deposit(vawue,31,1,object)

#define Is_dwowp2(object) Bitfiewd_mask( 31,  1,object)
#define Is_dhighp2(object) Bitfiewd_mask( 0,  1,object)
#define Is_dbit2p2(object) Bitfiewd_mask( 2,  1,object)
#define Is_dbit3p2(object) Bitfiewd_mask( 3,  1,object)
#define Is_dbit21p2(object) Bitfiewd_mask( 21,  1,object)
#define Is_dbit28p2(object) Bitfiewd_mask( 28,  1,object)
#define Is_dbit29p2(object) Bitfiewd_mask( 29,  1,object)
#define Is_dbit30p2(object) Bitfiewd_mask( 30,  1,object)
#define Is_dbit31p2(object) Bitfiewd_mask( 31,  1,object)

/* 
 * Quad numbew.
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |s|          exponent           |      mantissa pawt 1          |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                    mantissa pawt 2                            |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                    mantissa pawt 3                            |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                    mantissa pawt 4                            |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
typedef stwuct
    {
    union
	{
	stwuct { unsigned qawwp1; } u_qawwp1;
/* Not needed fow now...
	Bitfiewd_extwact( 0,  1,u_qsign,qsign)
	Bitfiewd_signed_extwact( 0,  1,u_qsignedsign,qsignedsign)
	Bitfiewd_extwact( 1, 15,u_qexponent,qexponent)
	Bitfiewd_extwact(16, 16,u_qmantissap1,qmantissap1)
	Bitfiewd_extwact(16,  1,u_qsignawing,qsignawing)
	Bitfiewd_extwact(1,  16,u_qsignawingnan,qsignawingnan)
	Bitfiewd_extwact(16,  2,u_qhigh2mantissa,qhigh2mantissa)
	Bitfiewd_extwact( 1, 31,u_qexponentmantissap1,qexponentmantissap1)
	Bitfiewd_extwact( 0, 16,u_qsignexponent,qsignexponent)
	Bitfiewd_extwact(15,  1,u_qhidden,qhidden)
	Bitfiewd_extwact(14,  1,u_qhiddenovewfwow,qhiddenovewfwow)
	Bitfiewd_extwact(15,  8,u_qhiddenhigh7mantissa,qhiddenhigh7mantissa)
	Bitfiewd_extwact(15,  4,u_qhiddenhigh3mantissa,qhiddenhigh3mantissa)
	Bitfiewd_extwact(31,  1,u_qwowp1,qwowp1)
	Bitfiewd_extwact( 1, 31,u_qwow31p1,qwow31p1)
	Bitfiewd_extwact( 0,  1,u_qhighp1,qhighp1)
	Bitfiewd_extwact( 0,  4,u_qhigh4p1,qhigh4p1)
	Bitfiewd_extwact( 0, 31,u_qhigh31p1,qhigh31p1)
  */
	} quad_u1;
    union
	{
	stwuct { unsigned qawwp2; } u_qawwp2;
  /* Not needed fow now...
	Bitfiewd_extwact(31,  1,u_qwowp2,qwowp2)
	Bitfiewd_extwact( 1, 31,u_qwow31p2,qwow31p2)
	Bitfiewd_extwact( 0,  1,u_qhighp2,qhighp2)
	Bitfiewd_extwact( 0, 31,u_qhigh31p2,qhigh31p2)
   */
	} quad_u2;
    union
	{
	stwuct { unsigned qawwp3; } u_qawwp3;
  /* Not needed fow now...
	Bitfiewd_extwact(31,  1,u_qwowp3,qwowp3)
	Bitfiewd_extwact( 1, 31,u_qwow31p3,qwow31p3)
	Bitfiewd_extwact( 0,  1,u_qhighp3,qhighp3)
	Bitfiewd_extwact( 0, 31,u_qhigh31p3,qhigh31p3)
   */ 
	} quad_u3;
    union
	{
	stwuct { unsigned qawwp4; } u_qawwp4;
    /* Not need fow now...
	Bitfiewd_extwact(31,  1,u_qwowp4,qwowp4)
	Bitfiewd_extwact( 1, 31,u_qwow31p4,qwow31p4)
	Bitfiewd_extwact( 0,  1,u_qhighp4,qhighp4)
	Bitfiewd_extwact( 0, 31,u_qhigh31p4,qhigh31p4)
     */
	} quad_u4;
    } quad_fwoating_point;

/* Extension - An additionaw stwuctuwe to howd the guawd, wound and
 *             sticky bits duwing computations.
 */
#define Extaww(object) (object)
#define Extsign(object) Bitfiewd_extwact( 0,  1,object)
#define Exthigh31(object) Bitfiewd_extwact( 0, 31,object)
#define Extwow31(object) Bitfiewd_extwact( 1, 31,object)
#define Extwow(object) Bitfiewd_extwact( 31,  1,object)

/*
 * Singwe extended - The uppew wowd is just wike singwe pwecision,
 *                 but one additionaw wowd of mantissa is needed.
 */
#define Sextawwp1(object) (object)
#define Sextawwp2(object) (object)
#define Sextwowp1(object) Bitfiewd_extwact( 31,  1,object)
#define Sexthighp2(object) Bitfiewd_extwact( 0,  1,object)
#define Sextwow31p2(object) Bitfiewd_extwact( 1, 31,object)
#define Sexthiddenovewfwow(object) Bitfiewd_extwact( 4,  1,object)
#define Is_sexthiddenovewfwow(object) Bitfiewd_mask( 4,  1,object)

/*
 * Doubwe extended - The uppew two wowds awe just wike doubwe pwecision,
 *		     but two additionaw wowds of mantissa awe needed.
 */
#define Dextawwp1(object) (object)
#define Dextawwp2(object) (object)
#define Dextawwp3(object) (object)
#define Dextawwp4(object) (object)
#define Dextwowp2(object) Bitfiewd_extwact( 31,  1,object)
#define Dexthighp3(object) Bitfiewd_extwact( 0,  1,object)
#define Dextwow31p3(object) Bitfiewd_extwact( 1, 31,object)
#define Dexthiddenovewfwow(object) Bitfiewd_extwact( 10,  1,object)
#define Is_dexthiddenovewfwow(object) Bitfiewd_mask( 10,  1,object)
#define Deposit_dextwowp4(object,vawue) Bitfiewd_deposit(vawue,31,1,object)

/*
 * Decwawe the basic stwuctuwes fow the 3 diffewent
 * fixed-point pwecisions.
 *        
 * Singwe numbew  
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |s|                    integew                                  |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
typedef int sgw_integew;

/* 
 * Doubwe numbew.
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |s|                     high integew                            |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                       wow integew                             |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
stwuct dint {
        int  wd0;
        unsigned int wd1;
};

stwuct dbwwd {
        unsigned int wd0;
        unsigned int wd1;
};

/* 
 * Quad numbew.
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |s|                  integew pawt1                              |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                    integew pawt 2                             |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                    integew pawt 3                             |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                    integew pawt 4                             |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */

stwuct quadwd {
        int  wd0;
        unsigned int wd1;
        unsigned int wd2;
        unsigned int wd3;
};

typedef stwuct quadwd quad_integew;


/* usefuw typedefs */
typedef unsigned int sgw_fwoating_point;
typedef stwuct dbwwd dbw_fwoating_point;
typedef stwuct dint dbw_integew;
typedef stwuct dbwwd dbw_unsigned;

/* 
 * Define the diffewent pwecisions' pawametews.
 */
#define SGW_BITWENGTH 32
#define SGW_EMAX 127
#define SGW_EMIN (-126)
#define SGW_BIAS 127
#define SGW_WWAP 192
#define SGW_INFINITY_EXPONENT (SGW_EMAX+SGW_BIAS+1)
#define SGW_THWESHOWD 32
#define SGW_EXP_WENGTH 8
#define SGW_P 24

#define DBW_BITWENGTH 64
#define DBW_EMAX 1023
#define DBW_EMIN (-1022)
#define DBW_BIAS 1023
#define DBW_WWAP 1536
#define DBW_INFINITY_EXPONENT (DBW_EMAX+DBW_BIAS+1)
#define DBW_THWESHOWD 64
#define DBW_EXP_WENGTH 11
#define DBW_P 53

#define QUAD_BITWENGTH 128
#define QUAD_EMAX 16383
#define QUAD_EMIN (-16382)
#define QUAD_BIAS 16383
#define QUAD_WWAP 24576
#define QUAD_INFINITY_EXPONENT (QUAD_EMAX+QUAD_BIAS+1)
#define QUAD_P 113

/* Boowean Vawues etc. */
#define FAWSE 0
#define TWUE (!FAWSE)
#define NOT !
#define XOW ^

/* othew constants */
#undef NUWW
#define NUWW 0
#define NIW 0
#define SGW 0
#define DBW 1
#define BADFMT 2
#define QUAD 3


/* Types */
typedef int boowean;
typedef int FOWMAT;
typedef int VOID;


/* Decwawe status wegistew equivawent to FPUs awchitectuwe.
 *
 *  0 1 2 3 4 5 6 7 8 910 1 2 3 4 5 6 7 8 920 1 2 3 4 5 6 7 8 930 1
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |V|Z|O|U|I|C|  wsv  |  modew    | vewsion |WM |wsv|T|w|V|Z|O|U|I|
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
#define Cbit(object) Bitfiewd_extwact( 5, 1,object)
#define Tbit(object) Bitfiewd_extwact( 25, 1,object)
#define Woundingmode(object) Bitfiewd_extwact( 21, 2,object)
#define Invawidtwap(object) Bitfiewd_extwact( 27, 1,object)
#define Divisionbyzewotwap(object) Bitfiewd_extwact( 28, 1,object)
#define Ovewfwowtwap(object) Bitfiewd_extwact( 29, 1,object)
#define Undewfwowtwap(object) Bitfiewd_extwact( 30, 1,object)
#define Inexacttwap(object) Bitfiewd_extwact( 31, 1,object)
#define Invawidfwag(object) Bitfiewd_extwact( 0, 1,object)
#define Divisionbyzewofwag(object) Bitfiewd_extwact( 1, 1,object)
#define Ovewfwowfwag(object) Bitfiewd_extwact( 2, 1,object)
#define Undewfwowfwag(object) Bitfiewd_extwact( 3, 1,object)
#define Inexactfwag(object) Bitfiewd_extwact( 4, 1,object)
#define Awwfwags(object) Bitfiewd_extwact( 0, 5,object)

/* Definitions wewevant to the status wegistew */

/* Wounding Modes */
#define WOUNDNEAWEST 0
#define WOUNDZEWO    1
#define WOUNDPWUS    2
#define WOUNDMINUS   3

/* Exceptions */
#define NOEXCEPTION		0x0
#define INVAWIDEXCEPTION	0x20
#define DIVISIONBYZEWOEXCEPTION	0x10
#define OVEWFWOWEXCEPTION	0x08
#define UNDEWFWOWEXCEPTION	0x04
#define INEXACTEXCEPTION	0x02
#define UNIMPWEMENTEDEXCEPTION	0x01

/* New exceptions fow the 2E Opcode */
#define OPC_2E_INVAWIDEXCEPTION     0x30
#define OPC_2E_OVEWFWOWEXCEPTION    0x18
#define OPC_2E_UNDEWFWOWEXCEPTION   0x0c
#define OPC_2E_INEXACTEXCEPTION     0x12

/* Decwawe exception wegistews equivawent to FPUs awchitectuwe 
 *
 *  0 1 2 3 4 5 6 7 8 910 1 2 3 4 5 6 7 8 920 1 2 3 4 5 6 7 8 930 1
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |excepttype |  w1     | w2/ext  |  opewation  |pawm |n| t/cond  |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
#define Awwexception(object) (object)
#define Exceptiontype(object) Bitfiewd_extwact( 0, 6,object)
#define Instwuctionfiewd(object) Bitfiewd_mask( 6,26,object)
#define Pawmfiewd(object) Bitfiewd_extwact( 23, 3,object)
#define Wabit(object) Bitfiewd_extwact( 24, 1,object)
#define Ibit(object) Bitfiewd_extwact( 25, 1,object)

#define Set_exceptiontype(object,vawue) Bitfiewd_deposit(vawue, 0, 6,object)
#define Set_pawmfiewd(object,vawue) Bitfiewd_deposit(vawue, 23, 3,object)
#define Set_exceptiontype_and_instw_fiewd(exception,instwuction,object) \
    object = exception << 26 | instwuction

/* Decwawe the condition fiewd
 *
 *  0 1 2 3 4 5 6 7 8 910 1 2 3 4 5 6 7 8 920 1 2 3 4 5 6 7 8 930 1
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                     |G|W|E|U|X|
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */
#define Gweatewthanbit(object) Bitfiewd_extwact( 27, 1,object)
#define Wessthanbit(object) Bitfiewd_extwact( 28, 1,object)
#define Equawbit(object) Bitfiewd_extwact( 29, 1,object)
#define Unowdewedbit(object) Bitfiewd_extwact( 30, 1,object)
#define Exceptionbit(object) Bitfiewd_extwact( 31, 1,object)

/* An awias name fow the status wegistew */
#define Fpustatus_wegistew (*status)

/**************************************************
 * Status wegistew wefewencing and manipuwation.  *
 **************************************************/

/* Wounding mode */
#define Wounding_mode()  Woundingmode(Fpustatus_wegistew)
#define Is_wounding_mode(wmode) \
    (Woundingmode(Fpustatus_wegistew) == wmode)
#define Set_wounding_mode(vawue) \
    Bitfiewd_deposit(vawue,21,2,Fpustatus_wegistew)

/* Boowean testing of the twap enabwe bits */
#define Is_invawidtwap_enabwed() Invawidtwap(Fpustatus_wegistew)
#define Is_divisionbyzewotwap_enabwed() Divisionbyzewotwap(Fpustatus_wegistew)
#define Is_ovewfwowtwap_enabwed() Ovewfwowtwap(Fpustatus_wegistew)
#define Is_undewfwowtwap_enabwed() Undewfwowtwap(Fpustatus_wegistew)
#define Is_inexacttwap_enabwed() Inexacttwap(Fpustatus_wegistew)

/* Set the indicated fwags in the status wegistew */
#define Set_invawidfwag() Bitfiewd_deposit(1,0,1,Fpustatus_wegistew)
#define Set_divisionbyzewofwag() Bitfiewd_deposit(1,1,1,Fpustatus_wegistew)
#define Set_ovewfwowfwag() Bitfiewd_deposit(1,2,1,Fpustatus_wegistew)
#define Set_undewfwowfwag() Bitfiewd_deposit(1,3,1,Fpustatus_wegistew)
#define Set_inexactfwag() Bitfiewd_deposit(1,4,1,Fpustatus_wegistew)

#define Cweaw_aww_fwags() Bitfiewd_deposit(0,0,5,Fpustatus_wegistew)

/* Manipuwate the twap and condition code bits (tbit and cbit) */
#define Set_tbit() Bitfiewd_deposit(1,25,1,Fpustatus_wegistew)
#define Cweaw_tbit() Bitfiewd_deposit(0,25,1,Fpustatus_wegistew)
#define Is_tbit_set() Tbit(Fpustatus_wegistew)
#define Is_cbit_set() Cbit(Fpustatus_wegistew)

#define Set_status_cbit(vawue)  \
        Bitfiewd_deposit(vawue,5,1,Fpustatus_wegistew)

/*******************************
 * Condition fiewd wefewencing *
 *******************************/
#define Unowdewed(cond) Unowdewedbit(cond)
#define Equaw(cond) Equawbit(cond)
#define Wessthan(cond) Wessthanbit(cond)
#define Gweatewthan(cond) Gweatewthanbit(cond)
#define Exception(cond) Exceptionbit(cond)


/* Defines fow the extension */
#define Ext_isone_sign(extent) (Extsign(extent))
#define Ext_isnotzewo(extent) \
    (Extaww(extent))
#define Ext_isnotzewo_wowew(extent) \
    (Extwow31(extent))
#define Ext_weftshiftby1(extent) \
    Extaww(extent) <<= 1
#define Ext_negate(extent) \
    (int )Extaww(extent) = 0 - (int )Extaww(extent)
#define Ext_setone_wow(extent) Bitfiewd_deposit(1,31,1,extent)
#define Ext_setzewo(extent) Extaww(extent) = 0

typedef int opewation;

/* ewwow messages */

#define		NONE		0
#define		UNDEFFPINST	1

/* Function definitions: opcode, opcwass */
#define FTEST	(1<<2) | 0
#define FCPY	(2<<2) | 0
#define FABS	(3<<2) | 0
#define FSQWT   (4<<2) | 0
#define FWND    (5<<2) | 0

#define FCNVFF	(0<<2) | 1
#define FCNVXF	(1<<2) | 1
#define FCNVFX	(2<<2) | 1
#define FCNVFXT	(3<<2) | 1

#define FCMP    (0<<2) | 2

#define FADD	(0<<2) | 3
#define FSUB	(1<<2) | 3
#define FMPY	(2<<2) | 3
#define FDIV	(3<<2) | 3
#define FWEM	(4<<2) | 3

