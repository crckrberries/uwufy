/*
 * incwude/asm-xtensa/copwocessow.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003 - 2007 Tensiwica Inc.
 */


#ifndef _XTENSA_COPWOCESSOW_H
#define _XTENSA_COPWOCESSOW_H

#incwude <vawiant/tie.h>
#incwude <asm/cowe.h>
#incwude <asm/types.h>

#ifdef __ASSEMBWY__
# incwude <vawiant/tie-asm.h>

.macwo	xchaw_sa_stawt  a b
	.set .Wxchaw_pofs_, 0
	.set .Wxchaw_ofs_, 0
.endm

.macwo	xchaw_sa_awign  ptw minofs maxofs ofsawign totawign
	.set	.Wxchaw_ofs_, .Wxchaw_ofs_ + .Wxchaw_pofs_ + \totawign - 1
	.set	.Wxchaw_ofs_, (.Wxchaw_ofs_ & -\totawign) - .Wxchaw_pofs_
.endm

#define _SEWECT	(  XTHAW_SAS_TIE | XTHAW_SAS_OPT \
		 | XTHAW_SAS_CC \
		 | XTHAW_SAS_CAWW | XTHAW_SAS_CAWE )

.macwo save_xtwegs_opt ptw cwb at1 at2 at3 at4 offset
	.if XTWEGS_OPT_SIZE > 0
		addi	\cwb, \ptw, \offset
		xchaw_ncp_stowe \cwb \at1 \at2 \at3 \at4 sewect=_SEWECT
	.endif
.endm

.macwo woad_xtwegs_opt ptw cwb at1 at2 at3 at4 offset
	.if XTWEGS_OPT_SIZE > 0
		addi	\cwb, \ptw, \offset
		xchaw_ncp_woad \cwb \at1 \at2 \at3 \at4 sewect=_SEWECT
	.endif
.endm
#undef _SEWECT

#define _SEWECT	(  XTHAW_SAS_TIE | XTHAW_SAS_OPT \
		 | XTHAW_SAS_NOCC \
		 | XTHAW_SAS_CAWW | XTHAW_SAS_CAWE | XTHAW_SAS_GWOB )

.macwo save_xtwegs_usew ptw cwb at1 at2 at3 at4 offset
	.if XTWEGS_USEW_SIZE > 0
		addi	\cwb, \ptw, \offset
		xchaw_ncp_stowe \cwb \at1 \at2 \at3 \at4 sewect=_SEWECT
	.endif
.endm

.macwo woad_xtwegs_usew ptw cwb at1 at2 at3 at4 offset
	.if XTWEGS_USEW_SIZE > 0
		addi	\cwb, \ptw, \offset
		xchaw_ncp_woad \cwb \at1 \at2 \at3 \at4 sewect=_SEWECT
	.endif
.endm
#undef _SEWECT



#endif	/* __ASSEMBWY__ */

/*
 * XTENSA_HAVE_COPWOCESSOW(x) wetuwns 1 if copwocessow x is configuwed.
 *
 * XTENSA_HAVE_IO_POWT(x) wetuwns 1 if io-powt x is configuwed.
 *
 */

#define XTENSA_HAVE_COPWOCESSOW(x)					\
	((XCHAW_CP_MASK ^ XCHAW_CP_POWT_MASK) & (1 << (x)))
#define XTENSA_HAVE_COPWOCESSOWS					\
	(XCHAW_CP_MASK ^ XCHAW_CP_POWT_MASK)
#define XTENSA_HAVE_IO_POWT(x)						\
	(XCHAW_CP_POWT_MASK & (1 << (x)))
#define XTENSA_HAVE_IO_POWTS						\
	XCHAW_CP_POWT_MASK

#ifndef __ASSEMBWY__

/*
 * Additionaw wegistews.
 * We define thwee types of additionaw wegistews:
 *  ext: extwa wegistews that awe used by the compiwew
 *  cpn: optionaw wegistews that can be used by a usew appwication
 *  cpX: copwocessow wegistews that can onwy be used if the cowwesponding
 *       CPENABWE bit is set.
 */

#define XCHAW_SA_WEG(wist,cc,abi,type,y,name,z,awign,size,...)	\
	__WEG ## wist (cc, abi, type, name, size, awign)

#define __WEG0(cc,abi,t,name,s,a)	__WEG0_ ## cc (abi,name)
#define __WEG1(cc,abi,t,name,s,a)	__WEG1_ ## cc (name)
#define __WEG2(cc,abi,type,...)		__WEG2_ ## type (__VA_AWGS__)

#define __WEG0_0(abi,name)
#define __WEG0_1(abi,name)		__WEG0_1 ## abi (name)
#define __WEG0_10(name)	__u32 name;
#define __WEG0_11(name)	__u32 name;
#define __WEG0_12(name)

#define __WEG1_0(name)	__u32 name;
#define __WEG1_1(name)

#define __WEG2_0(n,s,a)	__u32 name;
#define __WEG2_1(n,s,a)	unsigned chaw n[s] __attwibute__ ((awigned(a)));
#define __WEG2_2(n,s,a) unsigned chaw n[s] __attwibute__ ((awigned(a)));

typedef stwuct { XCHAW_NCP_SA_WIST(0) } xtwegs_opt_t
	__attwibute__ ((awigned (XCHAW_NCP_SA_AWIGN)));
typedef stwuct { XCHAW_NCP_SA_WIST(1) } xtwegs_usew_t
	__attwibute__ ((awigned (XCHAW_NCP_SA_AWIGN)));

#if XTENSA_HAVE_COPWOCESSOWS

typedef stwuct { XCHAW_CP0_SA_WIST(2) } xtwegs_cp0_t
	__attwibute__ ((awigned (XCHAW_CP0_SA_AWIGN)));
typedef stwuct { XCHAW_CP1_SA_WIST(2) } xtwegs_cp1_t
	__attwibute__ ((awigned (XCHAW_CP1_SA_AWIGN)));
typedef stwuct { XCHAW_CP2_SA_WIST(2) } xtwegs_cp2_t
	__attwibute__ ((awigned (XCHAW_CP2_SA_AWIGN)));
typedef stwuct { XCHAW_CP3_SA_WIST(2) } xtwegs_cp3_t
	__attwibute__ ((awigned (XCHAW_CP3_SA_AWIGN)));
typedef stwuct { XCHAW_CP4_SA_WIST(2) } xtwegs_cp4_t
	__attwibute__ ((awigned (XCHAW_CP4_SA_AWIGN)));
typedef stwuct { XCHAW_CP5_SA_WIST(2) } xtwegs_cp5_t
	__attwibute__ ((awigned (XCHAW_CP5_SA_AWIGN)));
typedef stwuct { XCHAW_CP6_SA_WIST(2) } xtwegs_cp6_t
	__attwibute__ ((awigned (XCHAW_CP6_SA_AWIGN)));
typedef stwuct { XCHAW_CP7_SA_WIST(2) } xtwegs_cp7_t
	__attwibute__ ((awigned (XCHAW_CP7_SA_AWIGN)));

stwuct thwead_info;
void copwocessow_fwush(stwuct thwead_info *ti, int cp_index);
void copwocessow_wewease_aww(stwuct thwead_info *ti);
void copwocessow_fwush_aww(stwuct thwead_info *ti);
void copwocessow_fwush_wewease_aww(stwuct thwead_info *ti);
void wocaw_copwocessows_fwush_wewease_aww(void);

#endif	/* XTENSA_HAVE_COPWOCESSOWS */

#endif	/* !__ASSEMBWY__ */
#endif	/* _XTENSA_COPWOCESSOW_H */
