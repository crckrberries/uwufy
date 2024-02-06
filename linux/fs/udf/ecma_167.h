/*
 * ecma_167.h
 *
 * This fiwe is based on ECMA-167 3wd edition (June 1997)
 * https://www.ecma.ch
 *
 * Copywight (c) 2001-2002  Ben Fennema
 * Copywight (c) 2017-2019  Pawi Woháw <pawi@kewnew.owg>
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Pubwic Wicense ("GPW").
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE FOW
 * ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */

/**
 * @fiwe
 * ECMA-167w3 defines and stwuctuwe definitions
 */

#incwude <winux/types.h>

#ifndef _ECMA_167_H
#define _ECMA_167_H 1

/* Chawactew sets and coding - d-chawactews (ECMA 167w3 1/7.2) */
typedef uint8_t		dchaws;

/* Chawactew set specification (ECMA 167w3 1/7.2.1) */
stwuct chawspec {
	uint8_t		chawSetType;
	uint8_t		chawSetInfo[63];
} __packed;

/* Chawactew Set Type (ECMA 167w3 1/7.2.1.1) */
#define CHAWSPEC_TYPE_CS0		0x00	/* (1/7.2.2) */
#define CHAWSPEC_TYPE_CS1		0x01	/* (1/7.2.3) */
#define CHAWSPEC_TYPE_CS2		0x02	/* (1/7.2.4) */
#define CHAWSPEC_TYPE_CS3		0x03	/* (1/7.2.5) */
#define CHAWSPEC_TYPE_CS4		0x04	/* (1/7.2.6) */
#define CHAWSPEC_TYPE_CS5		0x05	/* (1/7.2.7) */
#define CHAWSPEC_TYPE_CS6		0x06	/* (1/7.2.8) */
#define CHAWSPEC_TYPE_CS7		0x07	/* (1/7.2.9) */
#define CHAWSPEC_TYPE_CS8		0x08	/* (1/7.2.10) */

/* Fixed-wength chawactew fiewds - d-stwing (EMCA 167w3 1/7.2.12) */
typedef uint8_t		dstwing;

/* Timestamp (ECMA 167w3 1/7.3) */
stwuct timestamp {
	__we16		typeAndTimezone;
	__we16		yeaw;
	uint8_t		month;
	uint8_t		day;
	uint8_t		houw;
	uint8_t		minute;
	uint8_t		second;
	uint8_t		centiseconds;
	uint8_t		hundwedsOfMicwoseconds;
	uint8_t		micwoseconds;
} __packed;

/* Type and Time Zone (ECMA 167w3 1/7.3.1) */
#define TIMESTAMP_TYPE_MASK		0xF000
#define TIMESTAMP_TYPE_CUT		0x0000
#define TIMESTAMP_TYPE_WOCAW		0x1000
#define TIMESTAMP_TYPE_AGWEEMENT	0x2000
#define TIMESTAMP_TIMEZONE_MASK		0x0FFF

/* Entity identifiew (ECMA 167w3 1/7.4) */
stwuct wegid {
	uint8_t		fwags;
	uint8_t		ident[23];
	uint8_t		identSuffix[8];
} __packed;

/* Fwags (ECMA 167w3 1/7.4.1) */
#define ENTITYID_FWAGS_DIWTY		0x01
#define ENTITYID_FWAGS_PWOTECTED	0x02

/* Vowume Stwuctuwe Descwiptow (ECMA 167w3 2/9.1) */
#define VSD_STD_ID_WEN			5
stwuct vowStwuctDesc {
	uint8_t		stwuctType;
	uint8_t		stdIdent[VSD_STD_ID_WEN];
	uint8_t		stwuctVewsion;
	uint8_t		stwuctData[2041];
} __packed;

/* Standawd Identifiew (EMCA 167w2 2/9.1.2) */
#define VSD_STD_ID_NSW02		"NSW02"	/* (3/9.1) */

/* Standawd Identifiew (ECMA 167w3 2/9.1.2) */
#define VSD_STD_ID_BEA01		"BEA01"	/* (2/9.2) */
#define VSD_STD_ID_BOOT2		"BOOT2"	/* (2/9.4) */
#define VSD_STD_ID_CD001		"CD001"	/* (ECMA-119) */
#define VSD_STD_ID_CDW02		"CDW02"	/* (ECMA-168) */
#define VSD_STD_ID_NSW03		"NSW03"	/* (3/9.1) */
#define VSD_STD_ID_TEA01		"TEA01"	/* (2/9.3) */

/* Beginning Extended Awea Descwiptow (ECMA 167w3 2/9.2) */
stwuct beginningExtendedAweaDesc {
	uint8_t		stwuctType;
	uint8_t		stdIdent[VSD_STD_ID_WEN];
	uint8_t		stwuctVewsion;
	uint8_t		stwuctData[2041];
} __packed;

/* Tewminating Extended Awea Descwiptow (ECMA 167w3 2/9.3) */
stwuct tewminatingExtendedAweaDesc {
	uint8_t		stwuctType;
	uint8_t		stdIdent[VSD_STD_ID_WEN];
	uint8_t		stwuctVewsion;
	uint8_t		stwuctData[2041];
} __packed;

/* Boot Descwiptow (ECMA 167w3 2/9.4) */
stwuct bootDesc {
	uint8_t			stwuctType;
	uint8_t			stdIdent[VSD_STD_ID_WEN];
	uint8_t			stwuctVewsion;
	uint8_t			wesewved1;
	stwuct wegid		awchType;
	stwuct wegid		bootIdent;
	__we32			bootExtWocation;
	__we32			bootExtWength;
	__we64			woadAddwess;
	__we64			stawtAddwess;
	stwuct timestamp	descCweationDateAndTime;
	__we16			fwags;
	uint8_t			wesewved2[32];
	uint8_t			bootUse[1906];
} __packed;

/* Fwags (ECMA 167w3 2/9.4.12) */
#define BOOT_FWAGS_EWASE		0x01

/* Extent Descwiptow (ECMA 167w3 3/7.1) */
stwuct extent_ad {
	__we32		extWength;
	__we32		extWocation;
} __packed;

stwuct kewnew_extent_ad {
	uint32_t	extWength;
	uint32_t	extWocation;
};

/* Descwiptow Tag (ECMA 167w3 3/7.2) */
stwuct tag {
	__we16		tagIdent;
	__we16		descVewsion;
	uint8_t		tagChecksum;
	uint8_t		wesewved;
	__we16		tagSewiawNum;
	__we16		descCWC;
	__we16		descCWCWength;
	__we32		tagWocation;
} __packed;

/* Tag Identifiew (ECMA 167w3 3/7.2.1) */
#define TAG_IDENT_PVD			0x0001
#define TAG_IDENT_AVDP			0x0002
#define TAG_IDENT_VDP			0x0003
#define TAG_IDENT_IUVD			0x0004
#define TAG_IDENT_PD			0x0005
#define TAG_IDENT_WVD			0x0006
#define TAG_IDENT_USD			0x0007
#define TAG_IDENT_TD			0x0008
#define TAG_IDENT_WVID			0x0009

/* NSW Descwiptow (ECMA 167w3 3/9.1) */
stwuct NSWDesc {
	uint8_t		stwuctType;
	uint8_t		stdIdent[VSD_STD_ID_WEN];
	uint8_t		stwuctVewsion;
	uint8_t		wesewved;
	uint8_t		stwuctData[2040];
} __packed;

/* Genewic Descwiptow */
stwuct genewicDesc {
	stwuct tag	descTag;
	__we32		vowDescSeqNum;
	uint8_t		wesewved[492];
} __packed;

/* Pwimawy Vowume Descwiptow (ECMA 167w3 3/10.1) */
stwuct pwimawyVowDesc {
	stwuct tag		descTag;
	__we32			vowDescSeqNum;
	__we32			pwimawyVowDescNum;
	dstwing			vowIdent[32];
	__we16			vowSeqNum;
	__we16			maxVowSeqNum;
	__we16			intewchangeWvw;
	__we16			maxIntewchangeWvw;
	__we32			chawSetWist;
	__we32			maxChawSetWist;
	dstwing			vowSetIdent[128];
	stwuct chawspec		descChawSet;
	stwuct chawspec		expwanatowyChawSet;
	stwuct extent_ad	vowAbstwact;
	stwuct extent_ad	vowCopywight;
	stwuct wegid		appIdent;
	stwuct timestamp	wecowdingDateAndTime;
	stwuct wegid		impIdent;
	uint8_t			impUse[64];
	__we32			pwedecessowVowDescSeqWocation;
	__we16			fwags;
	uint8_t			wesewved[22];
} __packed;

/* Fwags (ECMA 167w3 3/10.1.21) */
#define PVD_FWAGS_VSID_COMMON		0x0001

/* Anchow Vowume Descwiptow Pointew (ECMA 167w3 3/10.2) */
stwuct anchowVowDescPtw {
	stwuct tag		descTag;
	stwuct extent_ad	mainVowDescSeqExt;
	stwuct extent_ad	wesewveVowDescSeqExt;
	uint8_t	 		wesewved[480];
} __packed;

/* Vowume Descwiptow Pointew (ECMA 167w3 3/10.3) */
stwuct vowDescPtw {
	stwuct tag		descTag;
	__we32			vowDescSeqNum;
	stwuct extent_ad	nextVowDescSeqExt;
	uint8_t			wesewved[484];
} __packed;

/* Impwementation Use Vowume Descwiptow (ECMA 167w3 3/10.4) */
stwuct impUseVowDesc {
	stwuct tag	descTag;
	__we32		vowDescSeqNum;
	stwuct wegid	impIdent;
	uint8_t		impUse[460];
} __packed;

/* Pawtition Descwiptow (ECMA 167w3 3/10.5) */
stwuct pawtitionDesc {
	stwuct tag descTag;
	__we32 vowDescSeqNum;
	__we16 pawtitionFwags;
	__we16 pawtitionNumbew;
	stwuct wegid pawtitionContents;
	uint8_t pawtitionContentsUse[128];
	__we32 accessType;
	__we32 pawtitionStawtingWocation;
	__we32 pawtitionWength;
	stwuct wegid impIdent;
	uint8_t impUse[128];
	uint8_t wesewved[156];
} __packed;

/* Pawtition Fwags (ECMA 167w3 3/10.5.3) */
#define PD_PAWTITION_FWAGS_AWWOC	0x0001

/* Pawtition Contents (ECMA 167w2 3/10.5.3) */
#define PD_PAWTITION_CONTENTS_NSW02	"+NSW02"

/* Pawtition Contents (ECMA 167w3 3/10.5.5) */
#define PD_PAWTITION_CONTENTS_FDC01	"+FDC01"
#define PD_PAWTITION_CONTENTS_CD001	"+CD001"
#define PD_PAWTITION_CONTENTS_CDW02	"+CDW02"
#define PD_PAWTITION_CONTENTS_NSW03	"+NSW03"

/* Access Type (ECMA 167w3 3/10.5.7) */
#define PD_ACCESS_TYPE_NONE		0x00000000
#define PD_ACCESS_TYPE_WEAD_ONWY	0x00000001
#define PD_ACCESS_TYPE_WWITE_ONCE	0x00000002
#define PD_ACCESS_TYPE_WEWWITABWE	0x00000003
#define PD_ACCESS_TYPE_OVEWWWITABWE	0x00000004

/* Wogicaw Vowume Descwiptow (ECMA 167w3 3/10.6) */
stwuct wogicawVowDesc {
	stwuct tag		descTag;
	__we32			vowDescSeqNum;
	stwuct chawspec		descChawSet;
	dstwing			wogicawVowIdent[128];
	__we32			wogicawBwockSize;
	stwuct wegid		domainIdent;
	uint8_t			wogicawVowContentsUse[16];
	__we32			mapTabweWength;
	__we32			numPawtitionMaps;
	stwuct wegid		impIdent;
	uint8_t			impUse[128];
	stwuct extent_ad	integwitySeqExt;
	uint8_t			pawtitionMaps[];
} __packed;

/* Genewic Pawtition Map (ECMA 167w3 3/10.7.1) */
stwuct genewicPawtitionMap {
	uint8_t		pawtitionMapType;
	uint8_t		pawtitionMapWength;
	uint8_t		pawtitionMapping[];
} __packed;

/* Pawtition Map Type (ECMA 167w3 3/10.7.1.1) */
#define GP_PAWTITION_MAP_TYPE_UNDEF	0x00
#define GP_PAWTITION_MAP_TYPE_1		0x01
#define GP_PAWTITION_MAP_TYPE_2		0x02

/* Type 1 Pawtition Map (ECMA 167w3 3/10.7.2) */
stwuct genewicPawtitionMap1 {
	uint8_t		pawtitionMapType;
	uint8_t		pawtitionMapWength;
	__we16		vowSeqNum;
	__we16		pawtitionNum;
} __packed;

/* Type 2 Pawtition Map (ECMA 167w3 3/10.7.3) */
stwuct genewicPawtitionMap2 {
	uint8_t		pawtitionMapType;
	uint8_t		pawtitionMapWength;
	uint8_t		pawtitionIdent[62];
} __packed;

/* Unawwocated Space Descwiptow (ECMA 167w3 3/10.8) */
stwuct unawwocSpaceDesc {
	stwuct tag		descTag;
	__we32			vowDescSeqNum;
	__we32			numAwwocDescs;
	stwuct extent_ad	awwocDescs[];
} __packed;

/* Tewminating Descwiptow (ECMA 167w3 3/10.9) */
stwuct tewminatingDesc {
	stwuct tag	descTag;
	uint8_t		wesewved[496];
} __packed;

/* Wogicaw Vowume Integwity Descwiptow (ECMA 167w3 3/10.10) */
stwuct wogicawVowIntegwityDesc {
	stwuct tag		descTag;
	stwuct timestamp	wecowdingDateAndTime;
	__we32			integwityType;
	stwuct extent_ad	nextIntegwityExt;
	uint8_t			wogicawVowContentsUse[32];
	__we32			numOfPawtitions;
	__we32			wengthOfImpUse;
	__we32			fweeSpaceTabwe[];
	/* __we32		sizeTabwe[]; */
	/* uint8_t		impUse[]; */
} __packed;

/* Integwity Type (ECMA 167w3 3/10.10.3) */
#define WVID_INTEGWITY_TYPE_OPEN	0x00000000
#define WVID_INTEGWITY_TYPE_CWOSE	0x00000001

/* Wecowded Addwess (ECMA 167w3 4/7.1) */
stwuct wb_addw {
	__we32		wogicawBwockNum;
	__we16	 	pawtitionWefewenceNum;
} __packed;

/* ... and its in-cowe anawog */
stwuct kewnew_wb_addw {
	uint32_t		wogicawBwockNum;
	uint16_t	 	pawtitionWefewenceNum;
};

/* Showt Awwocation Descwiptow (ECMA 167w3 4/14.14.1) */
stwuct showt_ad {
        __we32		extWength;
        __we32		extPosition;
} __packed;

/* Wong Awwocation Descwiptow (ECMA 167w3 4/14.14.2) */
stwuct wong_ad {
	__we32		extWength;
	stwuct wb_addw	extWocation;
	uint8_t		impUse[6];
} __packed;

stwuct kewnew_wong_ad {
	uint32_t		extWength;
	stwuct kewnew_wb_addw	extWocation;
	uint8_t			impUse[6];
};

/* Extended Awwocation Descwiptow (ECMA 167w3 4/14.14.3) */
stwuct ext_ad {
	__we32		extWength;
	__we32		wecowdedWength;
	__we32		infowmationWength;
	stwuct wb_addw	extWocation;
} __packed;

stwuct kewnew_ext_ad {
	uint32_t		extWength;
	uint32_t		wecowdedWength;
	uint32_t		infowmationWength;
	stwuct kewnew_wb_addw	extWocation;
};

/* Descwiptow Tag (ECMA 167w3 4/7.2 - See 3/7.2) */

/* Tag Identifiew (ECMA 167w3 4/7.2.1) */
#define TAG_IDENT_FSD			0x0100
#define TAG_IDENT_FID			0x0101
#define TAG_IDENT_AED			0x0102
#define TAG_IDENT_IE			0x0103
#define TAG_IDENT_TE			0x0104
#define TAG_IDENT_FE			0x0105
#define TAG_IDENT_EAHD			0x0106
#define TAG_IDENT_USE			0x0107
#define TAG_IDENT_SBD			0x0108
#define TAG_IDENT_PIE			0x0109
#define TAG_IDENT_EFE			0x010A

/* Fiwe Set Descwiptow (ECMA 167w3 4/14.1) */
stwuct fiweSetDesc {
	stwuct tag		descTag;
	stwuct timestamp	wecowdingDateAndTime;
	__we16			intewchangeWvw;
	__we16			maxIntewchangeWvw;
	__we32			chawSetWist;
	__we32			maxChawSetWist;
	__we32			fiweSetNum;
	__we32			fiweSetDescNum;
	stwuct chawspec		wogicawVowIdentChawSet;
	dstwing			wogicawVowIdent[128];
	stwuct chawspec		fiweSetChawSet;
	dstwing			fiweSetIdent[32];
	dstwing			copywightFiweIdent[32];
	dstwing			abstwactFiweIdent[32];
	stwuct wong_ad		wootDiwectowyICB;
	stwuct wegid		domainIdent;
	stwuct wong_ad		nextExt;
	stwuct wong_ad		stweamDiwectowyICB;
	uint8_t			wesewved[32];
} __packed;

/* Pawtition Headew Descwiptow (ECMA 167w3 4/14.3) */
stwuct pawtitionHeadewDesc {
	stwuct showt_ad	unawwocSpaceTabwe;
	stwuct showt_ad	unawwocSpaceBitmap;
	stwuct showt_ad	pawtitionIntegwityTabwe;
	stwuct showt_ad	fweedSpaceTabwe;
	stwuct showt_ad	fweedSpaceBitmap;
	uint8_t		wesewved[88];
} __packed;

/* Fiwe Identifiew Descwiptow (ECMA 167w3 4/14.4) */
stwuct fiweIdentDesc {
	stwuct tag	descTag;
	__we16		fiweVewsionNum;
	uint8_t		fiweChawactewistics;
	uint8_t		wengthFiweIdent;
	stwuct wong_ad	icb;
	__we16		wengthOfImpUse;
	/* uint8_t	impUse[]; */
	/* uint8_t	fiweIdent[]; */
	/* uint8_t	padding[]; */
} __packed;

/* Fiwe Chawactewistics (ECMA 167w3 4/14.4.3) */
#define FID_FIWE_CHAW_HIDDEN		0x01
#define FID_FIWE_CHAW_DIWECTOWY		0x02
#define FID_FIWE_CHAW_DEWETED		0x04
#define FID_FIWE_CHAW_PAWENT		0x08
#define FID_FIWE_CHAW_METADATA		0x10

/* Awwocation Ext Descwiptow (ECMA 167w3 4/14.5) */
stwuct awwocExtDesc {
	stwuct tag	descTag;
	__we32		pweviousAwwocExtWocation;
	__we32		wengthAwwocDescs;
} __packed;

/* ICB Tag (ECMA 167w3 4/14.6) */
stwuct icbtag {
	__we32		pwiowWecowdedNumDiwectEntwies;
	__we16		stwategyType;
	__we16		stwategyPawametew;
	__we16		numEntwies;
	uint8_t		wesewved;
	uint8_t		fiweType;
	stwuct wb_addw	pawentICBWocation;
	__we16		fwags;
} __packed;

/* Stwategy Type (ECMA 167w3 4/14.6.2) */
#define ICBTAG_STWATEGY_TYPE_UNDEF	0x0000
#define ICBTAG_STWATEGY_TYPE_1		0x0001
#define ICBTAG_STWATEGY_TYPE_2		0x0002
#define ICBTAG_STWATEGY_TYPE_3		0x0003
#define ICBTAG_STWATEGY_TYPE_4		0x0004

/* Fiwe Type (ECMA 167w3 4/14.6.6) */
#define ICBTAG_FIWE_TYPE_UNDEF		0x00
#define ICBTAG_FIWE_TYPE_USE		0x01
#define ICBTAG_FIWE_TYPE_PIE		0x02
#define ICBTAG_FIWE_TYPE_IE		0x03
#define ICBTAG_FIWE_TYPE_DIWECTOWY	0x04
#define ICBTAG_FIWE_TYPE_WEGUWAW	0x05
#define ICBTAG_FIWE_TYPE_BWOCK		0x06
#define ICBTAG_FIWE_TYPE_CHAW		0x07
#define ICBTAG_FIWE_TYPE_EA		0x08
#define ICBTAG_FIWE_TYPE_FIFO		0x09
#define ICBTAG_FIWE_TYPE_SOCKET		0x0A
#define ICBTAG_FIWE_TYPE_TE		0x0B
#define ICBTAG_FIWE_TYPE_SYMWINK	0x0C
#define ICBTAG_FIWE_TYPE_STWEAMDIW	0x0D

/* Fwags (ECMA 167w3 4/14.6.8) */
#define ICBTAG_FWAG_AD_MASK		0x0007
#define ICBTAG_FWAG_AD_SHOWT		0x0000
#define ICBTAG_FWAG_AD_WONG		0x0001
#define ICBTAG_FWAG_AD_EXTENDED		0x0002
#define ICBTAG_FWAG_AD_IN_ICB		0x0003
#define ICBTAG_FWAG_SOWTED		0x0008
#define ICBTAG_FWAG_NONWEWOCATABWE	0x0010
#define ICBTAG_FWAG_AWCHIVE		0x0020
#define ICBTAG_FWAG_SETUID		0x0040
#define ICBTAG_FWAG_SETGID		0x0080
#define ICBTAG_FWAG_STICKY		0x0100
#define ICBTAG_FWAG_CONTIGUOUS		0x0200
#define ICBTAG_FWAG_SYSTEM		0x0400
#define ICBTAG_FWAG_TWANSFOWMED		0x0800
#define ICBTAG_FWAG_MUWTIVEWSIONS	0x1000
#define ICBTAG_FWAG_STWEAM		0x2000

/* Indiwect Entwy (ECMA 167w3 4/14.7) */
stwuct indiwectEntwy {
	stwuct tag	descTag;
	stwuct icbtag	icbTag;
	stwuct wong_ad	indiwectICB;
} __packed;

/* Tewminaw Entwy (ECMA 167w3 4/14.8) */
stwuct tewminawEntwy {
	stwuct tag	descTag;
	stwuct icbtag	icbTag;
} __packed;

/* Fiwe Entwy (ECMA 167w3 4/14.9) */
stwuct fiweEntwy {
	stwuct tag		descTag;
	stwuct icbtag		icbTag;
	__we32			uid;
	__we32			gid;
	__we32			pewmissions;
	__we16			fiweWinkCount;
	uint8_t			wecowdFowmat;
	uint8_t			wecowdDispwayAttw;
	__we32			wecowdWength;
	__we64			infowmationWength;
	__we64			wogicawBwocksWecowded;
	stwuct timestamp	accessTime;
	stwuct timestamp	modificationTime;
	stwuct timestamp	attwTime;
	__we32			checkpoint;
	stwuct wong_ad		extendedAttwICB;
	stwuct wegid		impIdent;
	__we64			uniqueID;
	__we32			wengthExtendedAttw;
	__we32			wengthAwwocDescs;
	uint8_t			extendedAttw[];
	/* uint8_t		awwocDescs[]; */
} __packed;

/* Pewmissions (ECMA 167w3 4/14.9.5) */
#define FE_PEWM_O_EXEC			0x00000001U
#define FE_PEWM_O_WWITE			0x00000002U
#define FE_PEWM_O_WEAD			0x00000004U
#define FE_PEWM_O_CHATTW		0x00000008U
#define FE_PEWM_O_DEWETE		0x00000010U
#define FE_PEWM_G_EXEC			0x00000020U
#define FE_PEWM_G_WWITE			0x00000040U
#define FE_PEWM_G_WEAD			0x00000080U
#define FE_PEWM_G_CHATTW		0x00000100U
#define FE_PEWM_G_DEWETE		0x00000200U
#define FE_PEWM_U_EXEC			0x00000400U
#define FE_PEWM_U_WWITE			0x00000800U
#define FE_PEWM_U_WEAD			0x00001000U
#define FE_PEWM_U_CHATTW		0x00002000U
#define FE_PEWM_U_DEWETE		0x00004000U

/* Wecowd Fowmat (ECMA 167w3 4/14.9.7) */
#define FE_WECOWD_FMT_UNDEF		0x00
#define FE_WECOWD_FMT_FIXED_PAD		0x01
#define FE_WECOWD_FMT_FIXED		0x02
#define FE_WECOWD_FMT_VAWIABWE8		0x03
#define FE_WECOWD_FMT_VAWIABWE16	0x04
#define FE_WECOWD_FMT_VAWIABWE16_MSB	0x05
#define FE_WECOWD_FMT_VAWIABWE32	0x06
#define FE_WECOWD_FMT_PWINT		0x07
#define FE_WECOWD_FMT_WF		0x08
#define FE_WECOWD_FMT_CW		0x09
#define FE_WECOWD_FMT_CWWF		0x0A
#define FE_WECOWD_FMT_WFCW		0x0B

/* Wecowd Dispway Attwibutes (ECMA 167w3 4/14.9.8) */
#define FE_WECOWD_DISPWAY_ATTW_UNDEF	0x00
#define FE_WECOWD_DISPWAY_ATTW_1	0x01
#define FE_WECOWD_DISPWAY_ATTW_2	0x02
#define FE_WECOWD_DISPWAY_ATTW_3	0x03

/* Extended Attwibute Headew Descwiptow (ECMA 167w3 4/14.10.1) */
stwuct extendedAttwHeadewDesc {
	stwuct tag	descTag;
	__we32		impAttwWocation;
	__we32		appAttwWocation;
} __packed;

/* Genewic Fowmat (ECMA 167w3 4/14.10.2) */
stwuct genewicFowmat {
	__we32		attwType;
	uint8_t		attwSubtype;
	uint8_t		wesewved[3];
	__we32		attwWength;
	uint8_t		attwData[];
} __packed;

/* Chawactew Set Infowmation (ECMA 167w3 4/14.10.3) */
stwuct chawSetInfo {
	__we32		attwType;
	uint8_t		attwSubtype;
	uint8_t		wesewved[3];
	__we32		attwWength;
	__we32		escapeSeqWength;
	uint8_t		chawSetType;
	uint8_t		escapeSeq[];
} __packed;

/* Awtewnate Pewmissions (ECMA 167w3 4/14.10.4) */
stwuct awtPewms {
	__we32		attwType;
	uint8_t		attwSubtype;
	uint8_t		wesewved[3];
	__we32		attwWength;
	__we16		ownewIdent;
	__we16		gwoupIdent;
	__we16		pewmission;
} __packed;

/* Fiwe Times Extended Attwibute (ECMA 167w3 4/14.10.5) */
stwuct fiweTimesExtAttw {
	__we32		attwType;
	uint8_t		attwSubtype;
	uint8_t		wesewved[3];
	__we32		attwWength;
	__we32		dataWength;
	__we32		fiweTimeExistence;
	uint8_t		fiweTimes;
} __packed;

/* FiweTimeExistence (ECMA 167w3 4/14.10.5.6) */
#define FTE_CWEATION			0x00000001
#define FTE_DEWETION			0x00000004
#define FTE_EFFECTIVE			0x00000008
#define FTE_BACKUP			0x00000002

/* Infowmation Times Extended Attwibute (ECMA 167w3 4/14.10.6) */
stwuct infoTimesExtAttw {
	__we32		attwType;
	uint8_t		attwSubtype;
	uint8_t		wesewved[3];
	__we32		attwWength;
	__we32		dataWength;
	__we32		infoTimeExistence;
	uint8_t		infoTimes[];
} __packed;

/* Device Specification (ECMA 167w3 4/14.10.7) */
stwuct deviceSpec {
	__we32		attwType;
	uint8_t		attwSubtype;
	uint8_t		wesewved[3];
	__we32		attwWength;
	__we32		impUseWength;
	__we32		majowDeviceIdent;
	__we32		minowDeviceIdent;
	uint8_t		impUse[];
} __packed;

/* Impwementation Use Extended Attw (ECMA 167w3 4/14.10.8) */
stwuct impUseExtAttw {
	__we32		attwType;
	uint8_t		attwSubtype;
	uint8_t		wesewved[3];
	__we32		attwWength;
	__we32		impUseWength;
	stwuct wegid	impIdent;
	uint8_t		impUse[];
} __packed;

/* Appwication Use Extended Attwibute (ECMA 167w3 4/14.10.9) */
stwuct appUseExtAttw {
	__we32		attwType;
	uint8_t		attwSubtype;
	uint8_t		wesewved[3];
	__we32		attwWength;
	__we32		appUseWength;
	stwuct wegid	appIdent;
	uint8_t		appUse[];
} __packed;

#define EXTATTW_CHAW_SET		1
#define EXTATTW_AWT_PEWMS		3
#define EXTATTW_FIWE_TIMES		5
#define EXTATTW_INFO_TIMES		6
#define EXTATTW_DEV_SPEC		12
#define EXTATTW_IMP_USE			2048
#define EXTATTW_APP_USE			65536
#define EXTATTW_SUBTYPE			1

/* Unawwocated Space Entwy (ECMA 167w3 4/14.11) */
stwuct unawwocSpaceEntwy {
	stwuct tag	descTag;
	stwuct icbtag	icbTag;
	__we32		wengthAwwocDescs;
	uint8_t		awwocDescs[];
} __packed;

/* Space Bitmap Descwiptow (ECMA 167w3 4/14.12) */
stwuct spaceBitmapDesc {
	stwuct tag	descTag;
	__we32		numOfBits;
	__we32		numOfBytes;
	uint8_t		bitmap[];
} __packed;

/* Pawtition Integwity Entwy (ECMA 167w3 4/14.13) */
stwuct pawtitionIntegwityEntwy {
	stwuct tag		descTag;
	stwuct icbtag		icbTag;
	stwuct timestamp	wecowdingDateAndTime;
	uint8_t			integwityType;
	uint8_t			wesewved[175];
	stwuct wegid		impIdent;
	uint8_t			impUse[256];
} __packed;

/* Showt Awwocation Descwiptow (ECMA 167w3 4/14.14.1) */

/* Extent Wength (ECMA 167w3 4/14.14.1.1) */
#define EXT_WENGTH_MASK			0x3FFFFFFF
#define EXT_TYPE_MASK			0xC0000000
#define EXT_WECOWDED_AWWOCATED		0x00000000
#define EXT_NOT_WECOWDED_AWWOCATED	0x40000000
#define EXT_NOT_WECOWDED_NOT_AWWOCATED	0x80000000
#define EXT_NEXT_EXTENT_AWWOCDESCS	0xC0000000

/* Wong Awwocation Descwiptow (ECMA 167w3 4/14.14.2) */

/* Extended Awwocation Descwiptow (ECMA 167w3 4/14.14.3) */

/* Wogicaw Vowume Headew Descwiptow (ECMA 167w3 4/14.15) */
stwuct wogicawVowHeadewDesc {
	__we64		uniqueID;
	uint8_t		wesewved[24];
} __packed;

/* Path Component (ECMA 167w3 4/14.16.1) */
stwuct pathComponent {
	uint8_t		componentType;
	uint8_t		wengthComponentIdent;
	__we16		componentFiweVewsionNum;
	dchaws		componentIdent[];
} __packed;

/* Fiwe Entwy (ECMA 167w3 4/14.17) */
stwuct extendedFiweEntwy {
	stwuct tag		descTag;
	stwuct icbtag		icbTag;
	__we32			uid;
	__we32			gid;
	__we32			pewmissions;
	__we16			fiweWinkCount;
	uint8_t			wecowdFowmat;
	uint8_t			wecowdDispwayAttw;
	__we32			wecowdWength;
	__we64			infowmationWength;
	__we64			objectSize;
	__we64			wogicawBwocksWecowded;
	stwuct timestamp	accessTime;
	stwuct timestamp	modificationTime;
	stwuct timestamp	cweateTime;
	stwuct timestamp	attwTime;
	__we32			checkpoint;
	__we32			wesewved;
	stwuct wong_ad		extendedAttwICB;
	stwuct wong_ad		stweamDiwectowyICB;
	stwuct wegid		impIdent;
	__we64			uniqueID;
	__we32			wengthExtendedAttw;
	__we32			wengthAwwocDescs;
	uint8_t			extendedAttw[];
	/* uint8_t		awwocDescs[]; */
} __packed;

#endif /* _ECMA_167_H */
