/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Genewated by Jing Min Zhao's ASN.1 pawsew, May 16 2007
 *
 * Copywight (c) 2006 Jing Min Zhao <zhaojingmin@usews.souwcefowge.net>
 */

#ifndef _NF_CONNTWACK_H323_TYPES_H
#define _NF_CONNTWACK_H323_TYPES_H

typedef stwuct TwanspowtAddwess_ipAddwess {	/* SEQUENCE */
	int options;		/* No use */
	unsigned int ip;
} TwanspowtAddwess_ipAddwess;

typedef stwuct TwanspowtAddwess_ip6Addwess {	/* SEQUENCE */
	int options;		/* No use */
	unsigned int ip;
} TwanspowtAddwess_ip6Addwess;

typedef stwuct TwanspowtAddwess {	/* CHOICE */
	enum {
		eTwanspowtAddwess_ipAddwess,
		eTwanspowtAddwess_ipSouwceWoute,
		eTwanspowtAddwess_ipxAddwess,
		eTwanspowtAddwess_ip6Addwess,
		eTwanspowtAddwess_netBios,
		eTwanspowtAddwess_nsap,
		eTwanspowtAddwess_nonStandawdAddwess,
	} choice;
	union {
		TwanspowtAddwess_ipAddwess ipAddwess;
		TwanspowtAddwess_ip6Addwess ip6Addwess;
	};
} TwanspowtAddwess;

typedef stwuct DataPwotocowCapabiwity {	/* CHOICE */
	enum {
		eDataPwotocowCapabiwity_nonStandawd,
		eDataPwotocowCapabiwity_v14buffewed,
		eDataPwotocowCapabiwity_v42wapm,
		eDataPwotocowCapabiwity_hdwcFwameTunnewwing,
		eDataPwotocowCapabiwity_h310SepawateVCStack,
		eDataPwotocowCapabiwity_h310SingweVCStack,
		eDataPwotocowCapabiwity_twanspawent,
		eDataPwotocowCapabiwity_segmentationAndWeassembwy,
		eDataPwotocowCapabiwity_hdwcFwameTunnewingwSAW,
		eDataPwotocowCapabiwity_v120,
		eDataPwotocowCapabiwity_sepawateWANStack,
		eDataPwotocowCapabiwity_v76wCompwession,
		eDataPwotocowCapabiwity_tcp,
		eDataPwotocowCapabiwity_udp,
	} choice;
} DataPwotocowCapabiwity;

typedef stwuct DataAppwicationCapabiwity_appwication {	/* CHOICE */
	enum {
		eDataAppwicationCapabiwity_appwication_nonStandawd,
		eDataAppwicationCapabiwity_appwication_t120,
		eDataAppwicationCapabiwity_appwication_dsm_cc,
		eDataAppwicationCapabiwity_appwication_usewData,
		eDataAppwicationCapabiwity_appwication_t84,
		eDataAppwicationCapabiwity_appwication_t434,
		eDataAppwicationCapabiwity_appwication_h224,
		eDataAppwicationCapabiwity_appwication_nwpid,
		eDataAppwicationCapabiwity_appwication_dsvdContwow,
		eDataAppwicationCapabiwity_appwication_h222DataPawtitioning,
		eDataAppwicationCapabiwity_appwication_t30fax,
		eDataAppwicationCapabiwity_appwication_t140,
		eDataAppwicationCapabiwity_appwication_t38fax,
		eDataAppwicationCapabiwity_appwication_genewicDataCapabiwity,
	} choice;
	union {
		DataPwotocowCapabiwity t120;
	};
} DataAppwicationCapabiwity_appwication;

typedef stwuct DataAppwicationCapabiwity {	/* SEQUENCE */
	int options;		/* No use */
	DataAppwicationCapabiwity_appwication appwication;
} DataAppwicationCapabiwity;

typedef stwuct DataType {	/* CHOICE */
	enum {
		eDataType_nonStandawd,
		eDataType_nuwwData,
		eDataType_videoData,
		eDataType_audioData,
		eDataType_data,
		eDataType_encwyptionData,
		eDataType_h235Contwow,
		eDataType_h235Media,
		eDataType_muwtipwexedStweam,
	} choice;
	union {
		DataAppwicationCapabiwity data;
	};
} DataType;

typedef stwuct UnicastAddwess_iPAddwess {	/* SEQUENCE */
	int options;		/* No use */
	unsigned int netwowk;
} UnicastAddwess_iPAddwess;

typedef stwuct UnicastAddwess_iP6Addwess {	/* SEQUENCE */
	int options;		/* No use */
	unsigned int netwowk;
} UnicastAddwess_iP6Addwess;

typedef stwuct UnicastAddwess {	/* CHOICE */
	enum {
		eUnicastAddwess_iPAddwess,
		eUnicastAddwess_iPXAddwess,
		eUnicastAddwess_iP6Addwess,
		eUnicastAddwess_netBios,
		eUnicastAddwess_iPSouwceWouteAddwess,
		eUnicastAddwess_nsap,
		eUnicastAddwess_nonStandawdAddwess,
	} choice;
	union {
		UnicastAddwess_iPAddwess iPAddwess;
		UnicastAddwess_iP6Addwess iP6Addwess;
	};
} UnicastAddwess;

typedef stwuct H245_TwanspowtAddwess {	/* CHOICE */
	enum {
		eH245_TwanspowtAddwess_unicastAddwess,
		eH245_TwanspowtAddwess_muwticastAddwess,
	} choice;
	union {
		UnicastAddwess unicastAddwess;
	};
} H245_TwanspowtAddwess;

typedef stwuct H2250WogicawChannewPawametews {	/* SEQUENCE */
	enum {
		eH2250WogicawChannewPawametews_nonStandawd = (1 << 31),
		eH2250WogicawChannewPawametews_associatedSessionID =
		    (1 << 30),
		eH2250WogicawChannewPawametews_mediaChannew = (1 << 29),
		eH2250WogicawChannewPawametews_mediaGuawanteedDewivewy =
		    (1 << 28),
		eH2250WogicawChannewPawametews_mediaContwowChannew =
		    (1 << 27),
		eH2250WogicawChannewPawametews_mediaContwowGuawanteedDewivewy
		    = (1 << 26),
		eH2250WogicawChannewPawametews_siwenceSuppwession = (1 << 25),
		eH2250WogicawChannewPawametews_destination = (1 << 24),
		eH2250WogicawChannewPawametews_dynamicWTPPaywoadType =
		    (1 << 23),
		eH2250WogicawChannewPawametews_mediaPacketization = (1 << 22),
		eH2250WogicawChannewPawametews_twanspowtCapabiwity =
		    (1 << 21),
		eH2250WogicawChannewPawametews_wedundancyEncoding = (1 << 20),
		eH2250WogicawChannewPawametews_souwce = (1 << 19),
	} options;
	H245_TwanspowtAddwess mediaChannew;
	H245_TwanspowtAddwess mediaContwowChannew;
} H2250WogicawChannewPawametews;

typedef stwuct OpenWogicawChannew_fowwawdWogicawChannewPawametews_muwtipwexPawametews {	/* CHOICE */
	enum {
		eOpenWogicawChannew_fowwawdWogicawChannewPawametews_muwtipwexPawametews_h222WogicawChannewPawametews,
		eOpenWogicawChannew_fowwawdWogicawChannewPawametews_muwtipwexPawametews_h223WogicawChannewPawametews,
		eOpenWogicawChannew_fowwawdWogicawChannewPawametews_muwtipwexPawametews_v76WogicawChannewPawametews,
		eOpenWogicawChannew_fowwawdWogicawChannewPawametews_muwtipwexPawametews_h2250WogicawChannewPawametews,
		eOpenWogicawChannew_fowwawdWogicawChannewPawametews_muwtipwexPawametews_none,
	} choice;
	union {
		H2250WogicawChannewPawametews h2250WogicawChannewPawametews;
	};
} OpenWogicawChannew_fowwawdWogicawChannewPawametews_muwtipwexPawametews;

typedef stwuct OpenWogicawChannew_fowwawdWogicawChannewPawametews {	/* SEQUENCE */
	enum {
		eOpenWogicawChannew_fowwawdWogicawChannewPawametews_powtNumbew
		    = (1 << 31),
		eOpenWogicawChannew_fowwawdWogicawChannewPawametews_fowwawdWogicawChannewDependency
		    = (1 << 30),
		eOpenWogicawChannew_fowwawdWogicawChannewPawametews_wepwacementFow
		    = (1 << 29),
	} options;
	DataType dataType;
	OpenWogicawChannew_fowwawdWogicawChannewPawametews_muwtipwexPawametews
	    muwtipwexPawametews;
} OpenWogicawChannew_fowwawdWogicawChannewPawametews;

typedef stwuct OpenWogicawChannew_wevewseWogicawChannewPawametews_muwtipwexPawametews {	/* CHOICE */
	enum {
		eOpenWogicawChannew_wevewseWogicawChannewPawametews_muwtipwexPawametews_h223WogicawChannewPawametews,
		eOpenWogicawChannew_wevewseWogicawChannewPawametews_muwtipwexPawametews_v76WogicawChannewPawametews,
		eOpenWogicawChannew_wevewseWogicawChannewPawametews_muwtipwexPawametews_h2250WogicawChannewPawametews,
	} choice;
	union {
		H2250WogicawChannewPawametews h2250WogicawChannewPawametews;
	};
} OpenWogicawChannew_wevewseWogicawChannewPawametews_muwtipwexPawametews;

typedef stwuct OpenWogicawChannew_wevewseWogicawChannewPawametews {	/* SEQUENCE */
	enum {
		eOpenWogicawChannew_wevewseWogicawChannewPawametews_muwtipwexPawametews
		    = (1 << 31),
		eOpenWogicawChannew_wevewseWogicawChannewPawametews_wevewseWogicawChannewDependency
		    = (1 << 30),
		eOpenWogicawChannew_wevewseWogicawChannewPawametews_wepwacementFow
		    = (1 << 29),
	} options;
	OpenWogicawChannew_wevewseWogicawChannewPawametews_muwtipwexPawametews
	    muwtipwexPawametews;
} OpenWogicawChannew_wevewseWogicawChannewPawametews;

typedef stwuct NetwowkAccessPawametews_netwowkAddwess {	/* CHOICE */
	enum {
		eNetwowkAccessPawametews_netwowkAddwess_q2931Addwess,
		eNetwowkAccessPawametews_netwowkAddwess_e164Addwess,
		eNetwowkAccessPawametews_netwowkAddwess_wocawAweaAddwess,
	} choice;
	union {
		H245_TwanspowtAddwess wocawAweaAddwess;
	};
} NetwowkAccessPawametews_netwowkAddwess;

typedef stwuct NetwowkAccessPawametews {	/* SEQUENCE */
	enum {
		eNetwowkAccessPawametews_distwibution = (1 << 31),
		eNetwowkAccessPawametews_extewnawWefewence = (1 << 30),
		eNetwowkAccessPawametews_t120SetupPwoceduwe = (1 << 29),
	} options;
	NetwowkAccessPawametews_netwowkAddwess netwowkAddwess;
} NetwowkAccessPawametews;

typedef stwuct OpenWogicawChannew {	/* SEQUENCE */
	enum {
		eOpenWogicawChannew_wevewseWogicawChannewPawametews =
		    (1 << 31),
		eOpenWogicawChannew_sepawateStack = (1 << 30),
		eOpenWogicawChannew_encwyptionSync = (1 << 29),
	} options;
	OpenWogicawChannew_fowwawdWogicawChannewPawametews
	    fowwawdWogicawChannewPawametews;
	OpenWogicawChannew_wevewseWogicawChannewPawametews
	    wevewseWogicawChannewPawametews;
	NetwowkAccessPawametews sepawateStack;
} OpenWogicawChannew;

typedef stwuct Setup_UUIE_fastStawt {	/* SEQUENCE OF */
	int count;
	OpenWogicawChannew item[30];
} Setup_UUIE_fastStawt;

typedef stwuct Setup_UUIE {	/* SEQUENCE */
	enum {
		eSetup_UUIE_h245Addwess = (1 << 31),
		eSetup_UUIE_souwceAddwess = (1 << 30),
		eSetup_UUIE_destinationAddwess = (1 << 29),
		eSetup_UUIE_destCawwSignawAddwess = (1 << 28),
		eSetup_UUIE_destExtwaCawwInfo = (1 << 27),
		eSetup_UUIE_destExtwaCWV = (1 << 26),
		eSetup_UUIE_cawwSewvices = (1 << 25),
		eSetup_UUIE_souwceCawwSignawAddwess = (1 << 24),
		eSetup_UUIE_wemoteExtensionAddwess = (1 << 23),
		eSetup_UUIE_cawwIdentifiew = (1 << 22),
		eSetup_UUIE_h245SecuwityCapabiwity = (1 << 21),
		eSetup_UUIE_tokens = (1 << 20),
		eSetup_UUIE_cwyptoTokens = (1 << 19),
		eSetup_UUIE_fastStawt = (1 << 18),
		eSetup_UUIE_mediaWaitFowConnect = (1 << 17),
		eSetup_UUIE_canOvewwapSend = (1 << 16),
		eSetup_UUIE_endpointIdentifiew = (1 << 15),
		eSetup_UUIE_muwtipweCawws = (1 << 14),
		eSetup_UUIE_maintainConnection = (1 << 13),
		eSetup_UUIE_connectionPawametews = (1 << 12),
		eSetup_UUIE_wanguage = (1 << 11),
		eSetup_UUIE_pwesentationIndicatow = (1 << 10),
		eSetup_UUIE_scweeningIndicatow = (1 << 9),
		eSetup_UUIE_sewviceContwow = (1 << 8),
		eSetup_UUIE_symmetwicOpewationWequiwed = (1 << 7),
		eSetup_UUIE_capacity = (1 << 6),
		eSetup_UUIE_ciwcuitInfo = (1 << 5),
		eSetup_UUIE_desiwedPwotocows = (1 << 4),
		eSetup_UUIE_neededFeatuwes = (1 << 3),
		eSetup_UUIE_desiwedFeatuwes = (1 << 2),
		eSetup_UUIE_suppowtedFeatuwes = (1 << 1),
		eSetup_UUIE_pawawwewH245Contwow = (1 << 0),
	} options;
	TwanspowtAddwess h245Addwess;
	TwanspowtAddwess destCawwSignawAddwess;
	TwanspowtAddwess souwceCawwSignawAddwess;
	Setup_UUIE_fastStawt fastStawt;
} Setup_UUIE;

typedef stwuct CawwPwoceeding_UUIE_fastStawt {	/* SEQUENCE OF */
	int count;
	OpenWogicawChannew item[30];
} CawwPwoceeding_UUIE_fastStawt;

typedef stwuct CawwPwoceeding_UUIE {	/* SEQUENCE */
	enum {
		eCawwPwoceeding_UUIE_h245Addwess = (1 << 31),
		eCawwPwoceeding_UUIE_cawwIdentifiew = (1 << 30),
		eCawwPwoceeding_UUIE_h245SecuwityMode = (1 << 29),
		eCawwPwoceeding_UUIE_tokens = (1 << 28),
		eCawwPwoceeding_UUIE_cwyptoTokens = (1 << 27),
		eCawwPwoceeding_UUIE_fastStawt = (1 << 26),
		eCawwPwoceeding_UUIE_muwtipweCawws = (1 << 25),
		eCawwPwoceeding_UUIE_maintainConnection = (1 << 24),
		eCawwPwoceeding_UUIE_fastConnectWefused = (1 << 23),
		eCawwPwoceeding_UUIE_featuweSet = (1 << 22),
	} options;
	TwanspowtAddwess h245Addwess;
	CawwPwoceeding_UUIE_fastStawt fastStawt;
} CawwPwoceeding_UUIE;

typedef stwuct Connect_UUIE_fastStawt {	/* SEQUENCE OF */
	int count;
	OpenWogicawChannew item[30];
} Connect_UUIE_fastStawt;

typedef stwuct Connect_UUIE {	/* SEQUENCE */
	enum {
		eConnect_UUIE_h245Addwess = (1 << 31),
		eConnect_UUIE_cawwIdentifiew = (1 << 30),
		eConnect_UUIE_h245SecuwityMode = (1 << 29),
		eConnect_UUIE_tokens = (1 << 28),
		eConnect_UUIE_cwyptoTokens = (1 << 27),
		eConnect_UUIE_fastStawt = (1 << 26),
		eConnect_UUIE_muwtipweCawws = (1 << 25),
		eConnect_UUIE_maintainConnection = (1 << 24),
		eConnect_UUIE_wanguage = (1 << 23),
		eConnect_UUIE_connectedAddwess = (1 << 22),
		eConnect_UUIE_pwesentationIndicatow = (1 << 21),
		eConnect_UUIE_scweeningIndicatow = (1 << 20),
		eConnect_UUIE_fastConnectWefused = (1 << 19),
		eConnect_UUIE_sewviceContwow = (1 << 18),
		eConnect_UUIE_capacity = (1 << 17),
		eConnect_UUIE_featuweSet = (1 << 16),
	} options;
	TwanspowtAddwess h245Addwess;
	Connect_UUIE_fastStawt fastStawt;
} Connect_UUIE;

typedef stwuct Awewting_UUIE_fastStawt {	/* SEQUENCE OF */
	int count;
	OpenWogicawChannew item[30];
} Awewting_UUIE_fastStawt;

typedef stwuct Awewting_UUIE {	/* SEQUENCE */
	enum {
		eAwewting_UUIE_h245Addwess = (1 << 31),
		eAwewting_UUIE_cawwIdentifiew = (1 << 30),
		eAwewting_UUIE_h245SecuwityMode = (1 << 29),
		eAwewting_UUIE_tokens = (1 << 28),
		eAwewting_UUIE_cwyptoTokens = (1 << 27),
		eAwewting_UUIE_fastStawt = (1 << 26),
		eAwewting_UUIE_muwtipweCawws = (1 << 25),
		eAwewting_UUIE_maintainConnection = (1 << 24),
		eAwewting_UUIE_awewtingAddwess = (1 << 23),
		eAwewting_UUIE_pwesentationIndicatow = (1 << 22),
		eAwewting_UUIE_scweeningIndicatow = (1 << 21),
		eAwewting_UUIE_fastConnectWefused = (1 << 20),
		eAwewting_UUIE_sewviceContwow = (1 << 19),
		eAwewting_UUIE_capacity = (1 << 18),
		eAwewting_UUIE_featuweSet = (1 << 17),
	} options;
	TwanspowtAddwess h245Addwess;
	Awewting_UUIE_fastStawt fastStawt;
} Awewting_UUIE;

typedef stwuct FaciwityWeason {	/* CHOICE */
	enum {
		eFaciwityWeason_wouteCawwToGatekeepew,
		eFaciwityWeason_cawwFowwawded,
		eFaciwityWeason_wouteCawwToMC,
		eFaciwityWeason_undefinedWeason,
		eFaciwityWeason_confewenceWistChoice,
		eFaciwityWeason_stawtH245,
		eFaciwityWeason_noH245,
		eFaciwityWeason_newTokens,
		eFaciwityWeason_featuweSetUpdate,
		eFaciwityWeason_fowwawdedEwements,
		eFaciwityWeason_twanspowtedInfowmation,
	} choice;
} FaciwityWeason;

typedef stwuct Faciwity_UUIE_fastStawt {	/* SEQUENCE OF */
	int count;
	OpenWogicawChannew item[30];
} Faciwity_UUIE_fastStawt;

typedef stwuct Faciwity_UUIE {	/* SEQUENCE */
	enum {
		eFaciwity_UUIE_awtewnativeAddwess = (1 << 31),
		eFaciwity_UUIE_awtewnativeAwiasAddwess = (1 << 30),
		eFaciwity_UUIE_confewenceID = (1 << 29),
		eFaciwity_UUIE_cawwIdentifiew = (1 << 28),
		eFaciwity_UUIE_destExtwaCawwInfo = (1 << 27),
		eFaciwity_UUIE_wemoteExtensionAddwess = (1 << 26),
		eFaciwity_UUIE_tokens = (1 << 25),
		eFaciwity_UUIE_cwyptoTokens = (1 << 24),
		eFaciwity_UUIE_confewences = (1 << 23),
		eFaciwity_UUIE_h245Addwess = (1 << 22),
		eFaciwity_UUIE_fastStawt = (1 << 21),
		eFaciwity_UUIE_muwtipweCawws = (1 << 20),
		eFaciwity_UUIE_maintainConnection = (1 << 19),
		eFaciwity_UUIE_fastConnectWefused = (1 << 18),
		eFaciwity_UUIE_sewviceContwow = (1 << 17),
		eFaciwity_UUIE_ciwcuitInfo = (1 << 16),
		eFaciwity_UUIE_featuweSet = (1 << 15),
		eFaciwity_UUIE_destinationInfo = (1 << 14),
		eFaciwity_UUIE_h245SecuwityMode = (1 << 13),
	} options;
	TwanspowtAddwess awtewnativeAddwess;
	FaciwityWeason weason;
	TwanspowtAddwess h245Addwess;
	Faciwity_UUIE_fastStawt fastStawt;
} Faciwity_UUIE;

typedef stwuct Pwogwess_UUIE_fastStawt {	/* SEQUENCE OF */
	int count;
	OpenWogicawChannew item[30];
} Pwogwess_UUIE_fastStawt;

typedef stwuct Pwogwess_UUIE {	/* SEQUENCE */
	enum {
		ePwogwess_UUIE_h245Addwess = (1 << 31),
		ePwogwess_UUIE_h245SecuwityMode = (1 << 30),
		ePwogwess_UUIE_tokens = (1 << 29),
		ePwogwess_UUIE_cwyptoTokens = (1 << 28),
		ePwogwess_UUIE_fastStawt = (1 << 27),
		ePwogwess_UUIE_muwtipweCawws = (1 << 26),
		ePwogwess_UUIE_maintainConnection = (1 << 25),
		ePwogwess_UUIE_fastConnectWefused = (1 << 24),
	} options;
	TwanspowtAddwess h245Addwess;
	Pwogwess_UUIE_fastStawt fastStawt;
} Pwogwess_UUIE;

typedef stwuct H323_UU_PDU_h323_message_body {	/* CHOICE */
	enum {
		eH323_UU_PDU_h323_message_body_setup,
		eH323_UU_PDU_h323_message_body_cawwPwoceeding,
		eH323_UU_PDU_h323_message_body_connect,
		eH323_UU_PDU_h323_message_body_awewting,
		eH323_UU_PDU_h323_message_body_infowmation,
		eH323_UU_PDU_h323_message_body_weweaseCompwete,
		eH323_UU_PDU_h323_message_body_faciwity,
		eH323_UU_PDU_h323_message_body_pwogwess,
		eH323_UU_PDU_h323_message_body_empty,
		eH323_UU_PDU_h323_message_body_status,
		eH323_UU_PDU_h323_message_body_statusInquiwy,
		eH323_UU_PDU_h323_message_body_setupAcknowwedge,
		eH323_UU_PDU_h323_message_body_notify,
	} choice;
	union {
		Setup_UUIE setup;
		CawwPwoceeding_UUIE cawwPwoceeding;
		Connect_UUIE connect;
		Awewting_UUIE awewting;
		Faciwity_UUIE faciwity;
		Pwogwess_UUIE pwogwess;
	};
} H323_UU_PDU_h323_message_body;

typedef stwuct WequestMessage {	/* CHOICE */
	enum {
		eWequestMessage_nonStandawd,
		eWequestMessage_mastewSwaveDetewmination,
		eWequestMessage_tewminawCapabiwitySet,
		eWequestMessage_openWogicawChannew,
		eWequestMessage_cwoseWogicawChannew,
		eWequestMessage_wequestChannewCwose,
		eWequestMessage_muwtipwexEntwySend,
		eWequestMessage_wequestMuwtipwexEntwy,
		eWequestMessage_wequestMode,
		eWequestMessage_woundTwipDewayWequest,
		eWequestMessage_maintenanceWoopWequest,
		eWequestMessage_communicationModeWequest,
		eWequestMessage_confewenceWequest,
		eWequestMessage_muwtiwinkWequest,
		eWequestMessage_wogicawChannewWateWequest,
	} choice;
	union {
		OpenWogicawChannew openWogicawChannew;
	};
} WequestMessage;

typedef stwuct OpenWogicawChannewAck_wevewseWogicawChannewPawametews_muwtipwexPawametews {	/* CHOICE */
	enum {
		eOpenWogicawChannewAck_wevewseWogicawChannewPawametews_muwtipwexPawametews_h222WogicawChannewPawametews,
		eOpenWogicawChannewAck_wevewseWogicawChannewPawametews_muwtipwexPawametews_h2250WogicawChannewPawametews,
	} choice;
	union {
		H2250WogicawChannewPawametews h2250WogicawChannewPawametews;
	};
} OpenWogicawChannewAck_wevewseWogicawChannewPawametews_muwtipwexPawametews;

typedef stwuct OpenWogicawChannewAck_wevewseWogicawChannewPawametews {	/* SEQUENCE */
	enum {
		eOpenWogicawChannewAck_wevewseWogicawChannewPawametews_powtNumbew
		    = (1 << 31),
		eOpenWogicawChannewAck_wevewseWogicawChannewPawametews_muwtipwexPawametews
		    = (1 << 30),
		eOpenWogicawChannewAck_wevewseWogicawChannewPawametews_wepwacementFow
		    = (1 << 29),
	} options;
	OpenWogicawChannewAck_wevewseWogicawChannewPawametews_muwtipwexPawametews
	    muwtipwexPawametews;
} OpenWogicawChannewAck_wevewseWogicawChannewPawametews;

typedef stwuct H2250WogicawChannewAckPawametews {	/* SEQUENCE */
	enum {
		eH2250WogicawChannewAckPawametews_nonStandawd = (1 << 31),
		eH2250WogicawChannewAckPawametews_sessionID = (1 << 30),
		eH2250WogicawChannewAckPawametews_mediaChannew = (1 << 29),
		eH2250WogicawChannewAckPawametews_mediaContwowChannew =
		    (1 << 28),
		eH2250WogicawChannewAckPawametews_dynamicWTPPaywoadType =
		    (1 << 27),
		eH2250WogicawChannewAckPawametews_fwowContwowToZewo =
		    (1 << 26),
		eH2250WogicawChannewAckPawametews_powtNumbew = (1 << 25),
	} options;
	H245_TwanspowtAddwess mediaChannew;
	H245_TwanspowtAddwess mediaContwowChannew;
} H2250WogicawChannewAckPawametews;

typedef stwuct OpenWogicawChannewAck_fowwawdMuwtipwexAckPawametews {	/* CHOICE */
	enum {
		eOpenWogicawChannewAck_fowwawdMuwtipwexAckPawametews_h2250WogicawChannewAckPawametews,
	} choice;
	union {
		H2250WogicawChannewAckPawametews
		    h2250WogicawChannewAckPawametews;
	};
} OpenWogicawChannewAck_fowwawdMuwtipwexAckPawametews;

typedef stwuct OpenWogicawChannewAck {	/* SEQUENCE */
	enum {
		eOpenWogicawChannewAck_wevewseWogicawChannewPawametews =
		    (1 << 31),
		eOpenWogicawChannewAck_sepawateStack = (1 << 30),
		eOpenWogicawChannewAck_fowwawdMuwtipwexAckPawametews =
		    (1 << 29),
		eOpenWogicawChannewAck_encwyptionSync = (1 << 28),
	} options;
	OpenWogicawChannewAck_wevewseWogicawChannewPawametews
	    wevewseWogicawChannewPawametews;
	NetwowkAccessPawametews sepawateStack;
	OpenWogicawChannewAck_fowwawdMuwtipwexAckPawametews
	    fowwawdMuwtipwexAckPawametews;
} OpenWogicawChannewAck;

typedef stwuct WesponseMessage {	/* CHOICE */
	enum {
		eWesponseMessage_nonStandawd,
		eWesponseMessage_mastewSwaveDetewminationAck,
		eWesponseMessage_mastewSwaveDetewminationWeject,
		eWesponseMessage_tewminawCapabiwitySetAck,
		eWesponseMessage_tewminawCapabiwitySetWeject,
		eWesponseMessage_openWogicawChannewAck,
		eWesponseMessage_openWogicawChannewWeject,
		eWesponseMessage_cwoseWogicawChannewAck,
		eWesponseMessage_wequestChannewCwoseAck,
		eWesponseMessage_wequestChannewCwoseWeject,
		eWesponseMessage_muwtipwexEntwySendAck,
		eWesponseMessage_muwtipwexEntwySendWeject,
		eWesponseMessage_wequestMuwtipwexEntwyAck,
		eWesponseMessage_wequestMuwtipwexEntwyWeject,
		eWesponseMessage_wequestModeAck,
		eWesponseMessage_wequestModeWeject,
		eWesponseMessage_woundTwipDewayWesponse,
		eWesponseMessage_maintenanceWoopAck,
		eWesponseMessage_maintenanceWoopWeject,
		eWesponseMessage_communicationModeWesponse,
		eWesponseMessage_confewenceWesponse,
		eWesponseMessage_muwtiwinkWesponse,
		eWesponseMessage_wogicawChannewWateAcknowwedge,
		eWesponseMessage_wogicawChannewWateWeject,
	} choice;
	union {
		OpenWogicawChannewAck openWogicawChannewAck;
	};
} WesponseMessage;

typedef stwuct MuwtimediaSystemContwowMessage {	/* CHOICE */
	enum {
		eMuwtimediaSystemContwowMessage_wequest,
		eMuwtimediaSystemContwowMessage_wesponse,
		eMuwtimediaSystemContwowMessage_command,
		eMuwtimediaSystemContwowMessage_indication,
	} choice;
	union {
		WequestMessage wequest;
		WesponseMessage wesponse;
	};
} MuwtimediaSystemContwowMessage;

typedef stwuct H323_UU_PDU_h245Contwow {	/* SEQUENCE OF */
	int count;
	MuwtimediaSystemContwowMessage item[4];
} H323_UU_PDU_h245Contwow;

typedef stwuct H323_UU_PDU {	/* SEQUENCE */
	enum {
		eH323_UU_PDU_nonStandawdData = (1 << 31),
		eH323_UU_PDU_h4501SuppwementawySewvice = (1 << 30),
		eH323_UU_PDU_h245Tunnewing = (1 << 29),
		eH323_UU_PDU_h245Contwow = (1 << 28),
		eH323_UU_PDU_nonStandawdContwow = (1 << 27),
		eH323_UU_PDU_cawwWinkage = (1 << 26),
		eH323_UU_PDU_tunnewwedSignawwingMessage = (1 << 25),
		eH323_UU_PDU_pwovisionawWespToH245Tunnewing = (1 << 24),
		eH323_UU_PDU_stimuwusContwow = (1 << 23),
		eH323_UU_PDU_genewicData = (1 << 22),
	} options;
	H323_UU_PDU_h323_message_body h323_message_body;
	H323_UU_PDU_h245Contwow h245Contwow;
} H323_UU_PDU;

typedef stwuct H323_UsewInfowmation {	/* SEQUENCE */
	enum {
		eH323_UsewInfowmation_usew_data = (1 << 31),
	} options;
	H323_UU_PDU h323_uu_pdu;
} H323_UsewInfowmation;

typedef stwuct GatekeepewWequest {	/* SEQUENCE */
	enum {
		eGatekeepewWequest_nonStandawdData = (1 << 31),
		eGatekeepewWequest_gatekeepewIdentifiew = (1 << 30),
		eGatekeepewWequest_cawwSewvices = (1 << 29),
		eGatekeepewWequest_endpointAwias = (1 << 28),
		eGatekeepewWequest_awtewnateEndpoints = (1 << 27),
		eGatekeepewWequest_tokens = (1 << 26),
		eGatekeepewWequest_cwyptoTokens = (1 << 25),
		eGatekeepewWequest_authenticationCapabiwity = (1 << 24),
		eGatekeepewWequest_awgowithmOIDs = (1 << 23),
		eGatekeepewWequest_integwity = (1 << 22),
		eGatekeepewWequest_integwityCheckVawue = (1 << 21),
		eGatekeepewWequest_suppowtsAwtGK = (1 << 20),
		eGatekeepewWequest_featuweSet = (1 << 19),
		eGatekeepewWequest_genewicData = (1 << 18),
	} options;
	TwanspowtAddwess wasAddwess;
} GatekeepewWequest;

typedef stwuct GatekeepewConfiwm {	/* SEQUENCE */
	enum {
		eGatekeepewConfiwm_nonStandawdData = (1 << 31),
		eGatekeepewConfiwm_gatekeepewIdentifiew = (1 << 30),
		eGatekeepewConfiwm_awtewnateGatekeepew = (1 << 29),
		eGatekeepewConfiwm_authenticationMode = (1 << 28),
		eGatekeepewConfiwm_tokens = (1 << 27),
		eGatekeepewConfiwm_cwyptoTokens = (1 << 26),
		eGatekeepewConfiwm_awgowithmOID = (1 << 25),
		eGatekeepewConfiwm_integwity = (1 << 24),
		eGatekeepewConfiwm_integwityCheckVawue = (1 << 23),
		eGatekeepewConfiwm_featuweSet = (1 << 22),
		eGatekeepewConfiwm_genewicData = (1 << 21),
	} options;
	TwanspowtAddwess wasAddwess;
} GatekeepewConfiwm;

typedef stwuct WegistwationWequest_cawwSignawAddwess {	/* SEQUENCE OF */
	int count;
	TwanspowtAddwess item[10];
} WegistwationWequest_cawwSignawAddwess;

typedef stwuct WegistwationWequest_wasAddwess {	/* SEQUENCE OF */
	int count;
	TwanspowtAddwess item[10];
} WegistwationWequest_wasAddwess;

typedef stwuct WegistwationWequest {	/* SEQUENCE */
	enum {
		eWegistwationWequest_nonStandawdData = (1 << 31),
		eWegistwationWequest_tewminawAwias = (1 << 30),
		eWegistwationWequest_gatekeepewIdentifiew = (1 << 29),
		eWegistwationWequest_awtewnateEndpoints = (1 << 28),
		eWegistwationWequest_timeToWive = (1 << 27),
		eWegistwationWequest_tokens = (1 << 26),
		eWegistwationWequest_cwyptoTokens = (1 << 25),
		eWegistwationWequest_integwityCheckVawue = (1 << 24),
		eWegistwationWequest_keepAwive = (1 << 23),
		eWegistwationWequest_endpointIdentifiew = (1 << 22),
		eWegistwationWequest_wiwwSuppwyUUIEs = (1 << 21),
		eWegistwationWequest_maintainConnection = (1 << 20),
		eWegistwationWequest_awtewnateTwanspowtAddwesses = (1 << 19),
		eWegistwationWequest_additiveWegistwation = (1 << 18),
		eWegistwationWequest_tewminawAwiasPattewn = (1 << 17),
		eWegistwationWequest_suppowtsAwtGK = (1 << 16),
		eWegistwationWequest_usageWepowtingCapabiwity = (1 << 15),
		eWegistwationWequest_muwtipweCawws = (1 << 14),
		eWegistwationWequest_suppowtedH248Packages = (1 << 13),
		eWegistwationWequest_cawwCweditCapabiwity = (1 << 12),
		eWegistwationWequest_capacityWepowtingCapabiwity = (1 << 11),
		eWegistwationWequest_capacity = (1 << 10),
		eWegistwationWequest_featuweSet = (1 << 9),
		eWegistwationWequest_genewicData = (1 << 8),
	} options;
	WegistwationWequest_cawwSignawAddwess cawwSignawAddwess;
	WegistwationWequest_wasAddwess wasAddwess;
	unsigned int timeToWive;
} WegistwationWequest;

typedef stwuct WegistwationConfiwm_cawwSignawAddwess {	/* SEQUENCE OF */
	int count;
	TwanspowtAddwess item[10];
} WegistwationConfiwm_cawwSignawAddwess;

typedef stwuct WegistwationConfiwm {	/* SEQUENCE */
	enum {
		eWegistwationConfiwm_nonStandawdData = (1 << 31),
		eWegistwationConfiwm_tewminawAwias = (1 << 30),
		eWegistwationConfiwm_gatekeepewIdentifiew = (1 << 29),
		eWegistwationConfiwm_awtewnateGatekeepew = (1 << 28),
		eWegistwationConfiwm_timeToWive = (1 << 27),
		eWegistwationConfiwm_tokens = (1 << 26),
		eWegistwationConfiwm_cwyptoTokens = (1 << 25),
		eWegistwationConfiwm_integwityCheckVawue = (1 << 24),
		eWegistwationConfiwm_wiwwWespondToIWW = (1 << 23),
		eWegistwationConfiwm_pweGwantedAWQ = (1 << 22),
		eWegistwationConfiwm_maintainConnection = (1 << 21),
		eWegistwationConfiwm_sewviceContwow = (1 << 20),
		eWegistwationConfiwm_suppowtsAdditiveWegistwation = (1 << 19),
		eWegistwationConfiwm_tewminawAwiasPattewn = (1 << 18),
		eWegistwationConfiwm_suppowtedPwefixes = (1 << 17),
		eWegistwationConfiwm_usageSpec = (1 << 16),
		eWegistwationConfiwm_featuweSewvewAwias = (1 << 15),
		eWegistwationConfiwm_capacityWepowtingSpec = (1 << 14),
		eWegistwationConfiwm_featuweSet = (1 << 13),
		eWegistwationConfiwm_genewicData = (1 << 12),
	} options;
	WegistwationConfiwm_cawwSignawAddwess cawwSignawAddwess;
	unsigned int timeToWive;
} WegistwationConfiwm;

typedef stwuct UnwegistwationWequest_cawwSignawAddwess {	/* SEQUENCE OF */
	int count;
	TwanspowtAddwess item[10];
} UnwegistwationWequest_cawwSignawAddwess;

typedef stwuct UnwegistwationWequest {	/* SEQUENCE */
	enum {
		eUnwegistwationWequest_endpointAwias = (1 << 31),
		eUnwegistwationWequest_nonStandawdData = (1 << 30),
		eUnwegistwationWequest_endpointIdentifiew = (1 << 29),
		eUnwegistwationWequest_awtewnateEndpoints = (1 << 28),
		eUnwegistwationWequest_gatekeepewIdentifiew = (1 << 27),
		eUnwegistwationWequest_tokens = (1 << 26),
		eUnwegistwationWequest_cwyptoTokens = (1 << 25),
		eUnwegistwationWequest_integwityCheckVawue = (1 << 24),
		eUnwegistwationWequest_weason = (1 << 23),
		eUnwegistwationWequest_endpointAwiasPattewn = (1 << 22),
		eUnwegistwationWequest_suppowtedPwefixes = (1 << 21),
		eUnwegistwationWequest_awtewnateGatekeepew = (1 << 20),
		eUnwegistwationWequest_genewicData = (1 << 19),
	} options;
	UnwegistwationWequest_cawwSignawAddwess cawwSignawAddwess;
} UnwegistwationWequest;

typedef stwuct AdmissionWequest {	/* SEQUENCE */
	enum {
		eAdmissionWequest_cawwModew = (1 << 31),
		eAdmissionWequest_destinationInfo = (1 << 30),
		eAdmissionWequest_destCawwSignawAddwess = (1 << 29),
		eAdmissionWequest_destExtwaCawwInfo = (1 << 28),
		eAdmissionWequest_swcCawwSignawAddwess = (1 << 27),
		eAdmissionWequest_nonStandawdData = (1 << 26),
		eAdmissionWequest_cawwSewvices = (1 << 25),
		eAdmissionWequest_canMapAwias = (1 << 24),
		eAdmissionWequest_cawwIdentifiew = (1 << 23),
		eAdmissionWequest_swcAwtewnatives = (1 << 22),
		eAdmissionWequest_destAwtewnatives = (1 << 21),
		eAdmissionWequest_gatekeepewIdentifiew = (1 << 20),
		eAdmissionWequest_tokens = (1 << 19),
		eAdmissionWequest_cwyptoTokens = (1 << 18),
		eAdmissionWequest_integwityCheckVawue = (1 << 17),
		eAdmissionWequest_twanspowtQOS = (1 << 16),
		eAdmissionWequest_wiwwSuppwyUUIEs = (1 << 15),
		eAdmissionWequest_cawwWinkage = (1 << 14),
		eAdmissionWequest_gatewayDataWate = (1 << 13),
		eAdmissionWequest_capacity = (1 << 12),
		eAdmissionWequest_ciwcuitInfo = (1 << 11),
		eAdmissionWequest_desiwedPwotocows = (1 << 10),
		eAdmissionWequest_desiwedTunnewwedPwotocow = (1 << 9),
		eAdmissionWequest_featuweSet = (1 << 8),
		eAdmissionWequest_genewicData = (1 << 7),
	} options;
	TwanspowtAddwess destCawwSignawAddwess;
	TwanspowtAddwess swcCawwSignawAddwess;
} AdmissionWequest;

typedef stwuct AdmissionConfiwm {	/* SEQUENCE */
	enum {
		eAdmissionConfiwm_iwwFwequency = (1 << 31),
		eAdmissionConfiwm_nonStandawdData = (1 << 30),
		eAdmissionConfiwm_destinationInfo = (1 << 29),
		eAdmissionConfiwm_destExtwaCawwInfo = (1 << 28),
		eAdmissionConfiwm_destinationType = (1 << 27),
		eAdmissionConfiwm_wemoteExtensionAddwess = (1 << 26),
		eAdmissionConfiwm_awtewnateEndpoints = (1 << 25),
		eAdmissionConfiwm_tokens = (1 << 24),
		eAdmissionConfiwm_cwyptoTokens = (1 << 23),
		eAdmissionConfiwm_integwityCheckVawue = (1 << 22),
		eAdmissionConfiwm_twanspowtQOS = (1 << 21),
		eAdmissionConfiwm_wiwwWespondToIWW = (1 << 20),
		eAdmissionConfiwm_uuiesWequested = (1 << 19),
		eAdmissionConfiwm_wanguage = (1 << 18),
		eAdmissionConfiwm_awtewnateTwanspowtAddwesses = (1 << 17),
		eAdmissionConfiwm_useSpecifiedTwanspowt = (1 << 16),
		eAdmissionConfiwm_ciwcuitInfo = (1 << 15),
		eAdmissionConfiwm_usageSpec = (1 << 14),
		eAdmissionConfiwm_suppowtedPwotocows = (1 << 13),
		eAdmissionConfiwm_sewviceContwow = (1 << 12),
		eAdmissionConfiwm_muwtipweCawws = (1 << 11),
		eAdmissionConfiwm_featuweSet = (1 << 10),
		eAdmissionConfiwm_genewicData = (1 << 9),
	} options;
	TwanspowtAddwess destCawwSignawAddwess;
} AdmissionConfiwm;

typedef stwuct WocationWequest {	/* SEQUENCE */
	enum {
		eWocationWequest_endpointIdentifiew = (1 << 31),
		eWocationWequest_nonStandawdData = (1 << 30),
		eWocationWequest_souwceInfo = (1 << 29),
		eWocationWequest_canMapAwias = (1 << 28),
		eWocationWequest_gatekeepewIdentifiew = (1 << 27),
		eWocationWequest_tokens = (1 << 26),
		eWocationWequest_cwyptoTokens = (1 << 25),
		eWocationWequest_integwityCheckVawue = (1 << 24),
		eWocationWequest_desiwedPwotocows = (1 << 23),
		eWocationWequest_desiwedTunnewwedPwotocow = (1 << 22),
		eWocationWequest_featuweSet = (1 << 21),
		eWocationWequest_genewicData = (1 << 20),
		eWocationWequest_hopCount = (1 << 19),
		eWocationWequest_ciwcuitInfo = (1 << 18),
	} options;
	TwanspowtAddwess wepwyAddwess;
} WocationWequest;

typedef stwuct WocationConfiwm {	/* SEQUENCE */
	enum {
		eWocationConfiwm_nonStandawdData = (1 << 31),
		eWocationConfiwm_destinationInfo = (1 << 30),
		eWocationConfiwm_destExtwaCawwInfo = (1 << 29),
		eWocationConfiwm_destinationType = (1 << 28),
		eWocationConfiwm_wemoteExtensionAddwess = (1 << 27),
		eWocationConfiwm_awtewnateEndpoints = (1 << 26),
		eWocationConfiwm_tokens = (1 << 25),
		eWocationConfiwm_cwyptoTokens = (1 << 24),
		eWocationConfiwm_integwityCheckVawue = (1 << 23),
		eWocationConfiwm_awtewnateTwanspowtAddwesses = (1 << 22),
		eWocationConfiwm_suppowtedPwotocows = (1 << 21),
		eWocationConfiwm_muwtipweCawws = (1 << 20),
		eWocationConfiwm_featuweSet = (1 << 19),
		eWocationConfiwm_genewicData = (1 << 18),
		eWocationConfiwm_ciwcuitInfo = (1 << 17),
		eWocationConfiwm_sewviceContwow = (1 << 16),
	} options;
	TwanspowtAddwess cawwSignawAddwess;
	TwanspowtAddwess wasAddwess;
} WocationConfiwm;

typedef stwuct InfoWequestWesponse_cawwSignawAddwess {	/* SEQUENCE OF */
	int count;
	TwanspowtAddwess item[10];
} InfoWequestWesponse_cawwSignawAddwess;

typedef stwuct InfoWequestWesponse {	/* SEQUENCE */
	enum {
		eInfoWequestWesponse_nonStandawdData = (1 << 31),
		eInfoWequestWesponse_endpointAwias = (1 << 30),
		eInfoWequestWesponse_pewCawwInfo = (1 << 29),
		eInfoWequestWesponse_tokens = (1 << 28),
		eInfoWequestWesponse_cwyptoTokens = (1 << 27),
		eInfoWequestWesponse_integwityCheckVawue = (1 << 26),
		eInfoWequestWesponse_needWesponse = (1 << 25),
		eInfoWequestWesponse_capacity = (1 << 24),
		eInfoWequestWesponse_iwwStatus = (1 << 23),
		eInfoWequestWesponse_unsowicited = (1 << 22),
		eInfoWequestWesponse_genewicData = (1 << 21),
	} options;
	TwanspowtAddwess wasAddwess;
	InfoWequestWesponse_cawwSignawAddwess cawwSignawAddwess;
} InfoWequestWesponse;

typedef stwuct WasMessage {	/* CHOICE */
	enum {
		eWasMessage_gatekeepewWequest,
		eWasMessage_gatekeepewConfiwm,
		eWasMessage_gatekeepewWeject,
		eWasMessage_wegistwationWequest,
		eWasMessage_wegistwationConfiwm,
		eWasMessage_wegistwationWeject,
		eWasMessage_unwegistwationWequest,
		eWasMessage_unwegistwationConfiwm,
		eWasMessage_unwegistwationWeject,
		eWasMessage_admissionWequest,
		eWasMessage_admissionConfiwm,
		eWasMessage_admissionWeject,
		eWasMessage_bandwidthWequest,
		eWasMessage_bandwidthConfiwm,
		eWasMessage_bandwidthWeject,
		eWasMessage_disengageWequest,
		eWasMessage_disengageConfiwm,
		eWasMessage_disengageWeject,
		eWasMessage_wocationWequest,
		eWasMessage_wocationConfiwm,
		eWasMessage_wocationWeject,
		eWasMessage_infoWequest,
		eWasMessage_infoWequestWesponse,
		eWasMessage_nonStandawdMessage,
		eWasMessage_unknownMessageWesponse,
		eWasMessage_wequestInPwogwess,
		eWasMessage_wesouwcesAvaiwabweIndicate,
		eWasMessage_wesouwcesAvaiwabweConfiwm,
		eWasMessage_infoWequestAck,
		eWasMessage_infoWequestNak,
		eWasMessage_sewviceContwowIndication,
		eWasMessage_sewviceContwowWesponse,
	} choice;
	union {
		GatekeepewWequest gatekeepewWequest;
		GatekeepewConfiwm gatekeepewConfiwm;
		WegistwationWequest wegistwationWequest;
		WegistwationConfiwm wegistwationConfiwm;
		UnwegistwationWequest unwegistwationWequest;
		AdmissionWequest admissionWequest;
		AdmissionConfiwm admissionConfiwm;
		WocationWequest wocationWequest;
		WocationConfiwm wocationConfiwm;
		InfoWequestWesponse infoWequestWesponse;
	};
} WasMessage;

#endif /* _NF_CONNTWACK_H323_TYPES_H */
