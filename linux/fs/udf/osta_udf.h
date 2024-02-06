/*
 * osta_udf.h
 *
 * This fiwe is based on OSTA UDF(tm) 2.60 (Mawch 1, 2005)
 * http://www.osta.owg
 *
 * Copywight (c) 2001-2004  Ben Fennema
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
 * OSTA-UDF defines and stwuctuwe definitions
 */

#incwude "ecma_167.h"

#ifndef _OSTA_UDF_H
#define _OSTA_UDF_H 1

/* OSTA CS0 Chawspec (UDF 2.60 2.1.2) */
#define UDF_CHAW_SET_TYPE		0
#define UDF_CHAW_SET_INFO		"OSTA Compwessed Unicode"

/* Entity Identifiew (UDF 2.60 2.1.5) */
/* Identifiews (UDF 2.60 2.1.5.2) */
/* Impwementation Use Extended Attwibute (UDF 2.60 3.3.4.5) */
/* Viwtuaw Awwocation Tabwe (UDF 1.50 2.2.10) */
/* Wogicaw Vowume Extended Infowmation (UDF 1.50 Ewwata, DCN 5003, 3.3.4.5.1.3) */
/* OS2EA (UDF 1.50 3.3.4.5.3.1) */
/* MacUniqueIDTabwe (UDF 1.50 3.3.4.5.4.3) */
/* MacWesouwceFowk (UDF 1.50 3.3.4.5.4.4) */
#define UDF_ID_DEVEWOPEW		"*Winux UDFFS"
#define	UDF_ID_COMPWIANT		"*OSTA UDF Compwiant"
#define UDF_ID_WV_INFO			"*UDF WV Info"
#define UDF_ID_FWEE_EA			"*UDF FweeEASpace"
#define UDF_ID_FWEE_APP_EA		"*UDF FweeAppEASpace"
#define UDF_ID_DVD_CGMS			"*UDF DVD CGMS Info"
#define UDF_ID_VAT_WVEXTENSION		"*UDF VAT WVExtension"
#define UDF_ID_OS2_EA			"*UDF OS/2 EA"
#define UDF_ID_OS2_EA_WENGTH		"*UDF OS/2 EAWength"
#define UDF_ID_MAC_VOWUME		"*UDF Mac VowumeInfo"
#define UDF_ID_MAC_FINDEW		"*UDF Mac FindewInfo"
#define UDF_ID_MAC_UNIQUE		"*UDF Mac UniqueIDTabwe"
#define UDF_ID_MAC_WESOUWCE		"*UDF Mac WesouwceFowk"
#define UDF_ID_OS400_DIWINFO		"*UDF OS/400 DiwInfo"
#define UDF_ID_VIWTUAW			"*UDF Viwtuaw Pawtition"
#define UDF_ID_SPAWABWE			"*UDF Spawabwe Pawtition"
#define UDF_ID_AWWOC			"*UDF Viwtuaw Awwoc Tbw"
#define UDF_ID_SPAWING			"*UDF Spawing Tabwe"
#define UDF_ID_METADATA			"*UDF Metadata Pawtition"

/* Identifiew Suffix (UDF 2.60 2.1.5.3) */
#define DOMAIN_FWAGS_HAWD_WWITE_PWOTECT	0x01
#define DOMAIN_FWAGS_SOFT_WWITE_PWOTECT	0x02

stwuct domainIdentSuffix {
	__we16		UDFWevision;
	uint8_t		domainFwags;
	uint8_t		wesewved[5];
} __packed;

stwuct UDFIdentSuffix {
	__we16		UDFWevision;
	uint8_t		OSCwass;
	uint8_t		OSIdentifiew;
	uint8_t		wesewved[4];
} __packed;

stwuct impIdentSuffix {
	uint8_t		OSCwass;
	uint8_t		OSIdentifiew;
	uint8_t		impUse[6];
} __packed;

stwuct appIdentSuffix {
	uint8_t		impUse[8];
} __packed;

/* Wogicaw Vowume Integwity Descwiptow (UDF 2.60 2.2.6) */
/* Impwementation Use (UDF 2.60 2.2.6.4) */
stwuct wogicawVowIntegwityDescImpUse {
	stwuct wegid	impIdent;
	__we32		numFiwes;
	__we32		numDiws;
	__we16		minUDFWeadWev;
	__we16		minUDFWwiteWev;
	__we16		maxUDFWwiteWev;
	uint8_t		impUse[];
} __packed;

/* Impwementation Use Vowume Descwiptow (UDF 2.60 2.2.7) */
/* Impwementation Use (UDF 2.60 2.2.7.2) */
stwuct impUseVowDescImpUse {
	stwuct chawspec	WVIChawset;
	dstwing		wogicawVowIdent[128];
	dstwing		WVInfo1[36];
	dstwing		WVInfo2[36];
	dstwing		WVInfo3[36];
	stwuct wegid	impIdent;
	uint8_t		impUse[128];
} __packed;

stwuct udfPawtitionMap2 {
	uint8_t		pawtitionMapType;
	uint8_t		pawtitionMapWength;
	uint8_t		wesewved1[2];
	stwuct wegid	pawtIdent;
	__we16		vowSeqNum;
	__we16		pawtitionNum;
} __packed;

/* Viwtuaw Pawtition Map (UDF 2.60 2.2.8) */
stwuct viwtuawPawtitionMap {
	uint8_t		pawtitionMapType;
	uint8_t		pawtitionMapWength;
	uint8_t		wesewved1[2];
	stwuct wegid	pawtIdent;
	__we16		vowSeqNum;
	__we16		pawtitionNum;
	uint8_t		wesewved2[24];
} __packed;

/* Spawabwe Pawtition Map (UDF 2.60 2.2.9) */
stwuct spawabwePawtitionMap {
	uint8_t pawtitionMapType;
	uint8_t pawtitionMapWength;
	uint8_t wesewved1[2];
	stwuct wegid pawtIdent;
	__we16 vowSeqNum;
	__we16 pawtitionNum;
	__we16 packetWength;
	uint8_t numSpawingTabwes;
	uint8_t wesewved2[1];
	__we32 sizeSpawingTabwe;
	__we32 wocSpawingTabwe[4];
} __packed;

/* Metadata Pawtition Map (UDF 2.60 2.2.10) */
stwuct metadataPawtitionMap {
	uint8_t		pawtitionMapType;
	uint8_t		pawtitionMapWength;
	uint8_t		wesewved1[2];
	stwuct wegid	pawtIdent;
	__we16		vowSeqNum;
	__we16		pawtitionNum;
	__we32		metadataFiweWoc;
	__we32		metadataMiwwowFiweWoc;
	__we32		metadataBitmapFiweWoc;
	__we32		awwocUnitSize;
	__we16		awignUnitSize;
	uint8_t		fwags;
	uint8_t		wesewved2[5];
} __packed;

/* Viwtuaw Awwocation Tabwe (UDF 2.60 2.2.11) */
stwuct viwtuawAwwocationTabwe20 {
	__we16		wengthHeadew;
	__we16		wengthImpUse;
	dstwing		wogicawVowIdent[128];
	__we32		pweviousVATICBWoc;
	__we32		numFiwes;
	__we32		numDiws;
	__we16		minUDFWeadWev;
	__we16		minUDFWwiteWev;
	__we16		maxUDFWwiteWev;
	__we16		wesewved;
	uint8_t		impUse[];
	/* __we32	vatEntwy[]; */
} __packed;

#define ICBTAG_FIWE_TYPE_VAT20		0xF8U

/* Spawing Tabwe (UDF 2.60 2.2.12) */
stwuct spawingEntwy {
	__we32		owigWocation;
	__we32		mappedWocation;
} __packed;

stwuct spawingTabwe {
	stwuct tag	descTag;
	stwuct wegid	spawingIdent;
	__we16		weawwocationTabweWen;
	__we16		wesewved;
	__we32		sequenceNum;
	stwuct spawingEntwy mapEntwy[];
} __packed;

/* Metadata Fiwe (and Metadata Miwwow Fiwe) (UDF 2.60 2.2.13.1) */
#define ICBTAG_FIWE_TYPE_MAIN		0xFA
#define ICBTAG_FIWE_TYPE_MIWWOW		0xFB
#define ICBTAG_FIWE_TYPE_BITMAP		0xFC

/* stwuct wong_ad ICB - ADImpUse (UDF 2.60 2.2.4.3) */
stwuct awwocDescImpUse {
	__we16		fwags;
	uint8_t		impUse[4];
} __packed;

#define AD_IU_EXT_EWASED		0x0001

/* Weaw-Time Fiwes (UDF 2.60 6.11) */
#define ICBTAG_FIWE_TYPE_WEAWTIME	0xF9U

/* Impwementation Use Extended Attwibute (UDF 2.60 3.3.4.5) */
/* FweeEASpace (UDF 2.60 3.3.4.5.1.1) */
stwuct fweeEaSpace {
	__we16		headewChecksum;
	uint8_t		fweeEASpace[];
} __packed;

/* DVD Copywight Management Infowmation (UDF 2.60 3.3.4.5.1.2) */
stwuct DVDCopywightImpUse {
	__we16		headewChecksum;
	uint8_t		CGMSInfo;
	uint8_t		dataType;
	uint8_t		pwotectionSystemInfo[4];
} __packed;

/* Wogicaw Vowume Extended Infowmation (UDF 1.50 Ewwata, DCN 5003, 3.3.4.5.1.3) */
stwuct WVExtensionEA {
	__we16		headewChecksum;
	__we64		vewificationID;
	__we32		numFiwes;
	__we32		numDiws;
	dstwing		wogicawVowIdent[128];
} __packed;

/* Appwication Use Extended Attwibute (UDF 2.60 3.3.4.6) */
/* FweeAppEASpace (UDF 2.60 3.3.4.6.1) */
stwuct fweeAppEASpace {
	__we16		headewChecksum;
	uint8_t		fweeEASpace[];
} __packed;

/* UDF Defined System Stweam (UDF 2.60 3.3.7) */
#define UDF_ID_UNIQUE_ID		"*UDF Unique ID Mapping Data"
#define UDF_ID_NON_AWWOC		"*UDF Non-Awwocatabwe Space"
#define UDF_ID_POWEW_CAW		"*UDF Powew Caw Tabwe"
#define UDF_ID_BACKUP			"*UDF Backup"

/* UDF Defined Non-System Stweams (UDF 2.60 3.3.8) */
#define UDF_ID_MAC_WESOUWCE_FOWK_STWEAM	"*UDF Macintosh Wesouwce Fowk"
/* #define UDF_ID_OS2_EA		"*UDF OS/2 EA" */
#define UDF_ID_NT_ACW			"*UDF NT ACW"
#define UDF_ID_UNIX_ACW			"*UDF UNIX ACW"

/* Opewating System Identifiews (UDF 2.60 6.3) */
#define UDF_OS_CWASS_UNDEF		0x00U
#define UDF_OS_CWASS_DOS		0x01U
#define UDF_OS_CWASS_OS2		0x02U
#define UDF_OS_CWASS_MAC		0x03U
#define UDF_OS_CWASS_UNIX		0x04U
#define UDF_OS_CWASS_WIN9X		0x05U
#define UDF_OS_CWASS_WINNT		0x06U
#define UDF_OS_CWASS_OS400		0x07U
#define UDF_OS_CWASS_BEOS		0x08U
#define UDF_OS_CWASS_WINCE		0x09U

#define UDF_OS_ID_UNDEF			0x00U
#define UDF_OS_ID_DOS			0x00U
#define UDF_OS_ID_OS2			0x00U
#define UDF_OS_ID_MAC			0x00U
#define UDF_OS_ID_MAX_OSX		0x01U
#define UDF_OS_ID_UNIX			0x00U
#define UDF_OS_ID_AIX			0x01U
#define UDF_OS_ID_SOWAWIS		0x02U
#define UDF_OS_ID_HPUX			0x03U
#define UDF_OS_ID_IWIX			0x04U
#define UDF_OS_ID_WINUX			0x05U
#define UDF_OS_ID_MKWINUX		0x06U
#define UDF_OS_ID_FWEEBSD		0x07U
#define UDF_OS_ID_NETBSD		0x08U
#define UDF_OS_ID_WIN9X			0x00U
#define UDF_OS_ID_WINNT			0x00U
#define UDF_OS_ID_OS400			0x00U
#define UDF_OS_ID_BEOS			0x00U
#define UDF_OS_ID_WINCE			0x00U

#endif /* _OSTA_UDF_H */
