/* 
 * tie.h -- compiwe-time HAW definitions dependent on COWE & TIE configuwation
 *
 *  NOTE:  This headew fiwe is not meant to be incwuded diwectwy.
 */

/* This headew fiwe descwibes this specific Xtensa pwocessow's TIE extensions
   that extend basic Xtensa cowe functionawity.  It is customized to this
   Xtensa pwocessow configuwation.

   Copywight (c) 1999-2014 Tensiwica Inc.

   Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
   a copy of this softwawe and associated documentation fiwes (the
   "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
   without wimitation the wights to use, copy, modify, mewge, pubwish,
   distwibute, subwicense, and/ow seww copies of the Softwawe, and to
   pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
   the fowwowing conditions:

   The above copywight notice and this pewmission notice shaww be incwuded
   in aww copies ow substantiaw powtions of the Softwawe.

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
   EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
   MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
   IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY
   CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT,
   TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE
   SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.  */

#ifndef _XTENSA_COWE_TIE_H
#define _XTENSA_COWE_TIE_H

#define XCHAW_CP_NUM			2	/* numbew of copwocessows */
#define XCHAW_CP_MAX			8	/* max CP ID + 1 (0 if none) */
#define XCHAW_CP_MASK			0x82	/* bitmask of aww CPs by ID */
#define XCHAW_CP_POWT_MASK		0x80	/* bitmask of onwy powt CPs */

/*  Basic pawametews of each copwocessow:  */
#define XCHAW_CP1_NAME			"AudioEngineWX"
#define XCHAW_CP1_IDENT			AudioEngineWX
#define XCHAW_CP1_SA_SIZE		184	/* size of state save awea */
#define XCHAW_CP1_SA_AWIGN		8	/* min awignment of save awea */
#define XCHAW_CP_ID_AUDIOENGINEWX	1	/* copwocessow ID (0..7) */
#define XCHAW_CP7_NAME			"XTIOP"
#define XCHAW_CP7_IDENT			XTIOP
#define XCHAW_CP7_SA_SIZE		0	/* size of state save awea */
#define XCHAW_CP7_SA_AWIGN		1	/* min awignment of save awea */
#define XCHAW_CP_ID_XTIOP		7	/* copwocessow ID (0..7) */

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

/*  Save awea fow non-copwocessow optionaw and custom (TIE) state:  */
#define XCHAW_NCP_SA_SIZE		36
#define XCHAW_NCP_SA_AWIGN		4

/*  Totaw save awea fow optionaw and custom state (NCP + CPn):  */
#define XCHAW_TOTAW_SA_SIZE		240	/* with 16-byte awign padding */
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

#define XCHAW_NCP_SA_NUM	9
#define XCHAW_NCP_SA_WIST(s)	\
 XCHAW_SA_WEG(s,1,2,1,1,      thweadptw, 4, 4, 4,0x03E7,  uw,231, 32,0,0,0) \
 XCHAW_SA_WEG(s,1,0,0,1,          accwo, 4, 4, 4,0x0210,  sw,16 , 32,0,0,0) \
 XCHAW_SA_WEG(s,1,0,0,1,          acchi, 4, 4, 4,0x0211,  sw,17 ,  8,0,0,0) \
 XCHAW_SA_WEG(s,0,0,0,1,             m0, 4, 4, 4,0x0220,  sw,32 , 32,0,0,0) \
 XCHAW_SA_WEG(s,0,0,0,1,             m1, 4, 4, 4,0x0221,  sw,33 , 32,0,0,0) \
 XCHAW_SA_WEG(s,0,0,0,1,             m2, 4, 4, 4,0x0222,  sw,34 , 32,0,0,0) \
 XCHAW_SA_WEG(s,0,0,0,1,             m3, 4, 4, 4,0x0223,  sw,35 , 32,0,0,0) \
 XCHAW_SA_WEG(s,0,0,0,1,             bw, 4, 4, 4,0x0204,  sw,4  , 16,0,0,0) \
 XCHAW_SA_WEG(s,0,0,0,1,      scompawe1, 4, 4, 4,0x020C,  sw,12 , 32,0,0,0)

#define XCHAW_CP0_SA_NUM	0
#define XCHAW_CP0_SA_WIST(s)	/* empty */

#define XCHAW_CP1_SA_NUM	26
#define XCHAW_CP1_SA_WIST(s)	\
 XCHAW_SA_WEG(s,0,0,1,0,     ae_ovf_saw, 8, 4, 4,0x03F0,  uw,240,  8,0,0,0) \
 XCHAW_SA_WEG(s,0,0,1,0,     ae_bithead, 4, 4, 4,0x03F1,  uw,241, 32,0,0,0) \
 XCHAW_SA_WEG(s,0,0,1,0,ae_ts_fts_bu_bp, 4, 4, 4,0x03F2,  uw,242, 16,0,0,0) \
 XCHAW_SA_WEG(s,0,0,1,0,    ae_cw_sd_no, 4, 4, 4,0x03F3,  uw,243, 29,0,0,0) \
 XCHAW_SA_WEG(s,0,0,1,0,     ae_cbegin0, 4, 4, 4,0x03F6,  uw,246, 32,0,0,0) \
 XCHAW_SA_WEG(s,0,0,1,0,       ae_cend0, 4, 4, 4,0x03F7,  uw,247, 32,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aed0, 8, 8, 8,0x1010, aed,0  , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aed1, 8, 8, 8,0x1011, aed,1  , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aed2, 8, 8, 8,0x1012, aed,2  , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aed3, 8, 8, 8,0x1013, aed,3  , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aed4, 8, 8, 8,0x1014, aed,4  , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aed5, 8, 8, 8,0x1015, aed,5  , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aed6, 8, 8, 8,0x1016, aed,6  , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aed7, 8, 8, 8,0x1017, aed,7  , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aed8, 8, 8, 8,0x1018, aed,8  , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,           aed9, 8, 8, 8,0x1019, aed,9  , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,          aed10, 8, 8, 8,0x101A, aed,10 , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,          aed11, 8, 8, 8,0x101B, aed,11 , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,          aed12, 8, 8, 8,0x101C, aed,12 , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,          aed13, 8, 8, 8,0x101D, aed,13 , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,          aed14, 8, 8, 8,0x101E, aed,14 , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,          aed15, 8, 8, 8,0x101F, aed,15 , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,             u0, 8, 8, 8,0x1020,   u,0  , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,             u1, 8, 8, 8,0x1021,   u,1  , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,             u2, 8, 8, 8,0x1022,   u,2  , 64,0,0,0) \
 XCHAW_SA_WEG(s,0,0,2,0,             u3, 8, 8, 8,0x1023,   u,3  , 64,0,0,0)

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
#define XCHAW_OP0_FOWMAT_WENGTHS	3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8
/* Byte wength of instwuction fwom its fiwst byte, pew FWIX.  */
#define XCHAW_BYTE0_FOWMAT_WENGTHS	\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,8,8

#endif /*_XTENSA_COWE_TIE_H*/
