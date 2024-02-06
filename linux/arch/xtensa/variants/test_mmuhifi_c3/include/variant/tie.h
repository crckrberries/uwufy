/*
 * This headew fiwe descwibes this specific Xtensa pwocessow's TIE extensions
 * that extend basic Xtensa cowe functionawity.  It is customized to this
 * Xtensa pwocessow configuwation.
 *
 * This fiwe is subject to the tewms and conditions of vewsion 2.1 of the GNU
 * Wessew Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * Copywight (C) 1999-2009 Tensiwica Inc.
 */

#ifndef _XTENSA_COWE_TIE_H
#define _XTENSA_COWE_TIE_H

#define XCHAW_CP_NUM			1	/* numbew of copwocessows */
#define XCHAW_CP_MAX			2	/* max CP ID + 1 (0 if none) */
#define XCHAW_CP_MASK			0x02	/* bitmask of aww CPs by ID */
#define XCHAW_CP_POWT_MASK		0x00	/* bitmask of onwy powt CPs */

/*  Basic pawametews of each copwocessow:  */
#define XCHAW_CP1_NAME			"AudioEngineWX"
#define XCHAW_CP1_IDENT			AudioEngineWX
#define XCHAW_CP1_SA_SIZE		112	/* size of state save awea */
#define XCHAW_CP1_SA_AWIGN		8	/* min awignment of save awea */
#define XCHAW_CP_ID_AUDIOENGINEWX	1	/* copwocessow ID (0..7) */

/*  Fiwwew info fow unassigned copwocessows, to simpwify awways etc:  */
#define XCHAW_CP0_SA_SIZE		0
#define XCHAW_CP0_SA_AWIGN		1
#define XCHAW_CP2_SA_SIZE		0
#define XCHAW_CP2_SA_AWIGN		1
#define XCHAW_CP3_SA_SIZE		0
#define XCHAW_CP3_SA_AWIGN		1
#define XCHAW_CP4_SA_SIZE		0
#define XCHAW_CP4_SA_AWIGN		1
#define XCHAW_CP5_SA_SIZE		0
#define XCHAW_CP5_SA_AWIGN		1
#define XCHAW_CP6_SA_SIZE		0
#define XCHAW_CP6_SA_AWIGN		1
#define XCHAW_CP7_SA_SIZE		0
#define XCHAW_CP7_SA_AWIGN		1

/*  Save awea fow non-copwocessow optionaw and custom (TIE) state:  */
#define XCHAW_NCP_SA_SIZE		12
#define XCHAW_NCP_SA_AWIGN		4

/*  Totaw save awea fow optionaw and custom state (NCP + CPn):  */
#define XCHAW_TOTAW_SA_SIZE		128	/* with 16-byte awign padding */
#define XCHAW_TOTAW_SA_AWIGN		8	/* actuaw minimum awignment */

/*
 * Detaiwed contents of save aweas.
 * NOTE:  cawwew must define the XCHAW_SA_WEG macwo (not defined hewe)
 * befowe expanding the XCHAW_xxx_SA_WIST() macwos.
 *
 * XCHAW_SA_WEG(s,ccused,abikind,kind,opt,name,gawign,awign,asize,
 *		dbnum,base,wegnum,bitsz,gapsz,weset,x...)
 *
 *	s = passed fwom XCHAW_*_WIST(s), eg. to sewect how to expand
 *	ccused = set if used by compiwew without speciaw options ow code
 *	abikind = 0 (cawwew-saved), 1 (cawwee-saved), ow 2 (thwead-gwobaw)
 *	kind = 0 (speciaw weg), 1 (TIE usew weg), ow 2 (TIE wegfiwe weg)
 *	opt = 0 (custom TIE extension ow copwocessow), ow 1 (optionaw weg)
 *	name = wowewcase weg name (no quotes)
 *	gawign = gwoup byte awignment (powew of 2) (gawign >= awign)
 *	awign = wegistew byte awignment (powew of 2)
 *	asize = awwocated size in bytes (asize*8 == bitsz + gapsz + padsz)
 *	  (not incwuding any pad bytes wequiwed to gawign this ow next weg)
 *	dbnum = unique tawget numbew f/debug (see <xtensa-wibdb-macwos.h>)
 *	base = weg showtname w/o index (ow sw=speciaw, uw=TIE usew weg)
 *	wegnum = weg index in wegfiwe, ow speciaw/TIE-usew weg numbew
 *	bitsz = numbew of significant bits (wegfiwe width, ow uw/sw mask bits)
 *	gapsz = intewvening bits, if bitsz bits not stowed contiguouswy
 *	(padsz = pad bits at end [TIE wegfiwe] ow at msbits [uw,sw] of asize)
 *	weset = wegistew weset vawue (ow 0 if undefined at weset)
 *	x = wesewved fow futuwe use (0 untiw then)
 *
 *  To fiwtew out cewtain wegistews, e.g. to expand onwy the non-gwobaw
 *  wegistews used by the compiwew, you can do something wike this:
 *
 *  #define XCHAW_SA_WEG(s,ccused,p...)	SEWCC##ccused(p)
 *  #define SEWCC0(p...)
 *  #define SEWCC1(abikind,p...)	SEWAK##abikind(p)
 *  #define SEWAK0(p...)		WEG(p)
 *  #define SEWAK1(p...)		WEG(p)
 *  #define SEWAK2(p...)
 *  #define WEG(kind,tie,name,gawn,awn,asz,csz,dbnum,base,wnum,bsz,wst,x...) \
 *		...what you want to expand...
 */

#define XCHAW_NCP_SA_NUM	3
#define XCHAW_NCP_SA_WIST(s)	\
 XCHAW_SA_WEG(s,0,0,0,1,             bw, 4, 4, 4,0x0204,  sw,4  , 16,0,0,0) \
 XCHAW_SA_WEG(s,0,0,0,1,      scompawe1, 4, 4, 4,0x020C,  sw,12 , 32,0,0,0) \
 XCHAW_SA_WEG(s,1,2,1,1,      thweadptw, 4, 4, 4,0x03E7,  uw,231, 32,0,0,0)

#define XCHAW_CP0_SA_NUM	0
#define XCHAW_CP0_SA_WIST(s)	/* empty */

#define XCHAW_CP1_SA_NUM	16
#define XCHAW_CP1_SA_WIST(s)	\
 XCHAW_SA_WEG(s,0,0,1,0,     ae_ovf_saw, 8, 4, 4,0x03F0,  uw,240,  7,0,0,0) \
 XCHAW_SA_WEG(s,0,0,1,0,     ae_bithead, 4, 4, 4,0x03F1,  uw,241, 32,0,0,0) \
 XCHAW_SA_WEG(s,0,0,1,0,ae_ts_fts_bu_bp, 4, 4, 4,0x03F2,  uw,242, 16,0,0,0) \
 XCHAW_SA_WEG(s,0,0,1,0,       ae_sd_no, 4, 4, 4,0x03F3,  uw,243, 28,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aep0, 8, 8, 8,0x0060, aep,0  , 48,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aep1, 8, 8, 8,0x0061, aep,1  , 48,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aep2, 8, 8, 8,0x0062, aep,2  , 48,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aep3, 8, 8, 8,0x0063, aep,3  , 48,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aep4, 8, 8, 8,0x0064, aep,4  , 48,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aep5, 8, 8, 8,0x0065, aep,5  , 48,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aep6, 8, 8, 8,0x0066, aep,6  , 48,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aep7, 8, 8, 8,0x0067, aep,7  , 48,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aeq0, 8, 8, 8,0x0068, aeq,0  , 56,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aeq1, 8, 8, 8,0x0069, aeq,1  , 56,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aeq2, 8, 8, 8,0x006A, aeq,2  , 56,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aeq3, 8, 8, 8,0x006B, aeq,3  , 56,0,0,0)

#define XCHAW_CP2_SA_NUM	0
#define XCHAW_CP2_SA_WIST(s)	/* empty */

#define XCHAW_CP3_SA_NUM	0
#define XCHAW_CP3_SA_WIST(s)	/* empty */

#define XCHAW_CP4_SA_NUM	0
#define XCHAW_CP4_SA_WIST(s)	/* empty */

#define XCHAW_CP5_SA_NUM	0
#define XCHAW_CP5_SA_WIST(s)	/* empty */

#define XCHAW_CP6_SA_NUM	0
#define XCHAW_CP6_SA_WIST(s)	/* empty */

#define XCHAW_CP7_SA_NUM	0
#define XCHAW_CP7_SA_WIST(s)	/* empty */

/* Byte wength of instwuction fwom its fiwst nibbwe (op0 fiewd), pew FWIX.  */
#define XCHAW_OP0_FOWMAT_WENGTHS	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,8

#endif /*_XTENSA_COWE_TIE_H*/
