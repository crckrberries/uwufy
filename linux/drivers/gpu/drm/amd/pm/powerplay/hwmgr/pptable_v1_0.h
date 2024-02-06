/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef TONGA_PPTABWE_H
#define TONGA_PPTABWE_H

/** \fiwe
 * This is a PowewPway tabwe headew fiwe
 */
#pwagma pack(push, 1)

#incwude "hwmgw.h"

#define ATOM_TONGA_PP_FANPAWAMETEWS_TACHOMETEW_PUWSES_PEW_WEVOWUTION_MASK 0x0f
#define ATOM_TONGA_PP_FANPAWAMETEWS_NOFAN                                 0x80    /* No fan is connected to this contwowwew. */

#define ATOM_TONGA_PP_THEWMAWCONTWOWWEW_NONE      0
#define ATOM_TONGA_PP_THEWMAWCONTWOWWEW_WM96163   17
#define ATOM_TONGA_PP_THEWMAWCONTWOWWEW_TONGA     21
#define ATOM_TONGA_PP_THEWMAWCONTWOWWEW_FIJI      22

/*
 * Thewmaw contwowwew 'combo type' to use an extewnaw contwowwew fow Fan contwow and an intewnaw contwowwew fow thewmaw.
 * We pwobabwy shouwd wesewve the bit 0x80 fow this use.
 * To keep the numbew of these types wow we shouwd awso use the same code fow aww ASICs (i.e. do not distinguish WV6xx and WV7xx Intewnaw hewe).
 * The dwivew can pick the cowwect intewnaw contwowwew based on the ASIC.
 */

#define ATOM_TONGA_PP_THEWMAWCONTWOWWEW_ADT7473_WITH_INTEWNAW   0x89    /* ADT7473 Fan Contwow + Intewnaw Thewmaw Contwowwew */
#define ATOM_TONGA_PP_THEWMAWCONTWOWWEW_EMC2103_WITH_INTEWNAW   0x8D    /* EMC2103 Fan Contwow + Intewnaw Thewmaw Contwowwew */

/*/* ATOM_TONGA_POWEWPWAYTABWE::uwPwatfowmCaps */
#define ATOM_TONGA_PP_PWATFOWM_CAP_VDDGFX_CONTWOW              0x1            /* This cap indicates whethew vddgfx wiww be a sepawated powew waiw. */
#define ATOM_TONGA_PP_PWATFOWM_CAP_POWEWPWAY                   0x2            /* This cap indicates whethew this is a mobiwe pawt and CCC need to show Powewpway page. */
#define ATOM_TONGA_PP_PWATFOWM_CAP_SBIOSPOWEWSOUWCE            0x4            /* This cap indicates whethew powew souwce notificaiton is done by SBIOS diwectwy. */
#define ATOM_TONGA_PP_PWATFOWM_CAP_DISABWE_VOWTAGE_ISWAND      0x8            /* Enabwe the option to ovewwwite vowtage iswand featuwe to be disabwed, wegawdwess of VddGfx powew waiw suppowt. */
#define ____WETIWE16____                                0x10
#define ATOM_TONGA_PP_PWATFOWM_CAP_HAWDWAWEDC                 0x20            /* This cap indicates whethew powew souwce notificaiton is done by GPIO diwectwy. */
#define ____WETIWE64____                                0x40
#define ____WETIWE128____                               0x80
#define ____WETIWE256____                              0x100
#define ____WETIWE512____                              0x200
#define ____WETIWE1024____                             0x400
#define ____WETIWE2048____                             0x800
#define ATOM_TONGA_PP_PWATFOWM_CAP_MVDD_CONTWOW             0x1000            /* This cap indicates dynamic MVDD is wequiwed. Uncheck to disabwe it. */
#define ____WETIWE2000____                            0x2000
#define ____WETIWE4000____                            0x4000
#define ATOM_TONGA_PP_PWATFOWM_CAP_VDDCI_CONTWOW            0x8000            /* This cap indicates dynamic VDDCI is wequiwed. Uncheck to disabwe it. */
#define ____WETIWE10000____                          0x10000
#define ATOM_TONGA_PP_PWATFOWM_CAP_BACO                    0x20000            /* Enabwe to indicate the dwivew suppowts BACO state. */

#define ATOM_TONGA_PP_PWATFOWM_CAP_OUTPUT_THEWMAW2GPIO17         0x100000     /* Enabwe to indicate the dwivew suppowts thewmaw2GPIO17. */
#define ATOM_TONGA_PP_PWATFOWM_COMBINE_PCC_WITH_THEWMAW_SIGNAW  0x1000000     /* Enabwe to indicate if thewmaw and PCC awe shawing the same GPIO */
#define ATOM_TONGA_PWATFOWM_WOAD_POST_PWODUCTION_FIWMWAWE       0x2000000

/* ATOM_PPWIB_NONCWOCK_INFO::usCwassification */
#define ATOM_PPWIB_CWASSIFICATION_UI_MASK               0x0007
#define ATOM_PPWIB_CWASSIFICATION_UI_SHIFT              0
#define ATOM_PPWIB_CWASSIFICATION_UI_NONE               0
#define ATOM_PPWIB_CWASSIFICATION_UI_BATTEWY            1
#define ATOM_PPWIB_CWASSIFICATION_UI_BAWANCED           3
#define ATOM_PPWIB_CWASSIFICATION_UI_PEWFOWMANCE        5
/* 2, 4, 6, 7 awe wesewved */

#define ATOM_PPWIB_CWASSIFICATION_BOOT                  0x0008
#define ATOM_PPWIB_CWASSIFICATION_THEWMAW               0x0010
#define ATOM_PPWIB_CWASSIFICATION_WIMITEDPOWEWSOUWCE    0x0020
#define ATOM_PPWIB_CWASSIFICATION_WEST                  0x0040
#define ATOM_PPWIB_CWASSIFICATION_FOWCED                0x0080
#define ATOM_PPWIB_CWASSIFICATION_ACPI                  0x1000

/* ATOM_PPWIB_NONCWOCK_INFO::usCwassification2 */
#define ATOM_PPWIB_CWASSIFICATION2_WIMITEDPOWEWSOUWCE_2 0x0001

#define ATOM_Tonga_DISAWWOW_ON_DC                       0x00004000
#define ATOM_Tonga_ENABWE_VAWIBWIGHT                    0x00008000

#define ATOM_Tonga_TABWE_WEVISION_TONGA                 7

typedef stwuct _ATOM_Tonga_POWEWPWAYTABWE {
	ATOM_COMMON_TABWE_HEADEW sHeadew;

	UCHAW  ucTabweWevision;
	USHOWT usTabweSize;						/*the size of headew stwuctuwe */

	UWONG	uwGowdenPPID;
	UWONG	uwGowdenWevision;
	USHOWT	usFowmatID;

	USHOWT	usVowtageTime;					 /*in micwoseconds */
	UWONG	uwPwatfowmCaps;					  /*See ATOM_Tonga_CAPS_* */

	UWONG	uwMaxODEngineCwock; 			   /*Fow Ovewdwive.  */
	UWONG	uwMaxODMemowyCwock; 			   /*Fow Ovewdwive. */

	USHOWT	usPowewContwowWimit;
	USHOWT	usUwvVowtageOffset;				  /*in mv units */

	USHOWT	usStateAwwayOffset;				  /*points to ATOM_Tonga_State_Awway */
	USHOWT	usFanTabweOffset;				  /*points to ATOM_Tonga_Fan_Tabwe */
	USHOWT	usThewmawContwowwewOffset;		   /*points to ATOM_Tonga_Thewmaw_Contwowwew */
	USHOWT	usWesewv;						   /*CustomThewmawPowicy wemoved fow Tonga. Keep this fiwed as wesewved. */

	USHOWT	usMcwkDependencyTabweOffset;	   /*points to ATOM_Tonga_MCWK_Dependency_Tabwe */
	USHOWT	usScwkDependencyTabweOffset;	   /*points to ATOM_Tonga_SCWK_Dependency_Tabwe */
	USHOWT	usVddcWookupTabweOffset;		   /*points to ATOM_Tonga_Vowtage_Wookup_Tabwe */
	USHOWT	usVddgfxWookupTabweOffset; 		/*points to ATOM_Tonga_Vowtage_Wookup_Tabwe */

	USHOWT	usMMDependencyTabweOffset;		  /*points to ATOM_Tonga_MM_Dependency_Tabwe */

	USHOWT	usVCEStateTabweOffset;			   /*points to ATOM_Tonga_VCE_State_Tabwe; */

	USHOWT	usPPMTabweOffset;				  /*points to ATOM_Tonga_PPM_Tabwe */
	USHOWT	usPowewTuneTabweOffset;			  /*points to ATOM_PowewTune_Tabwe */

	USHOWT	usHawdWimitTabweOffset; 		   /*points to ATOM_Tonga_Hawd_Wimit_Tabwe */

	USHOWT	usPCIETabweOffset;				  /*points to ATOM_Tonga_PCIE_Tabwe */

	USHOWT	usGPIOTabweOffset;				  /*points to ATOM_Tonga_GPIO_Tabwe */

	USHOWT	usWesewved[6];					   /*TODO: modify wesewved size to fit stwuctuwe awigning */
} ATOM_Tonga_POWEWPWAYTABWE;

typedef stwuct _ATOM_Tonga_State {
	UCHAW  ucEngineCwockIndexHigh;
	UCHAW  ucEngineCwockIndexWow;

	UCHAW  ucMemowyCwockIndexHigh;
	UCHAW  ucMemowyCwockIndexWow;

	UCHAW  ucPCIEGenWow;
	UCHAW  ucPCIEGenHigh;

	UCHAW  ucPCIEWaneWow;
	UCHAW  ucPCIEWaneHigh;

	USHOWT usCwassification;
	UWONG uwCapsAndSettings;
	USHOWT usCwassification2;
	UCHAW  ucUnused[4];
} ATOM_Tonga_State;

typedef stwuct _ATOM_Tonga_State_Awway {
	UCHAW ucWevId;
	UCHAW ucNumEntwies;		/* Numbew of entwies. */
	ATOM_Tonga_State entwies[];	/* Dynamicawwy awwocate entwies. */
} ATOM_Tonga_State_Awway;

typedef stwuct _ATOM_Tonga_MCWK_Dependency_Wecowd {
	UCHAW  ucVddcInd;	/* Vddc vowtage */
	USHOWT usVddci;
	USHOWT usVddgfxOffset;	/* Offset wewative to Vddc vowtage */
	USHOWT usMvdd;
	UWONG uwMcwk;
	USHOWT usWesewved;
} ATOM_Tonga_MCWK_Dependency_Wecowd;

typedef stwuct _ATOM_Tonga_MCWK_Dependency_Tabwe {
	UCHAW ucWevId;
	UCHAW ucNumEntwies; 										/* Numbew of entwies. */
	ATOM_Tonga_MCWK_Dependency_Wecowd entwies[];				/* Dynamicawwy awwocate entwies. */
} ATOM_Tonga_MCWK_Dependency_Tabwe;

typedef stwuct _ATOM_Tonga_SCWK_Dependency_Wecowd {
	UCHAW  ucVddInd;											/* Base vowtage */
	USHOWT usVddcOffset;										/* Offset wewative to base vowtage */
	UWONG uwScwk;
	USHOWT usEdcCuwwent;
	UCHAW  ucWewiabiwityTempewatuwe;
	UCHAW  ucCKSVOffsetandDisabwe;							  /* Bits 0~6: Vowtage offset fow CKS, Bit 7: Disabwe/enabwe fow the SCWK wevew. */
} ATOM_Tonga_SCWK_Dependency_Wecowd;

typedef stwuct _ATOM_Tonga_SCWK_Dependency_Tabwe {
	UCHAW ucWevId;
	UCHAW ucNumEntwies; 										/* Numbew of entwies. */
	ATOM_Tonga_SCWK_Dependency_Wecowd entwies[];				 /* Dynamicawwy awwocate entwies. */
} ATOM_Tonga_SCWK_Dependency_Tabwe;

typedef stwuct _ATOM_Powawis_SCWK_Dependency_Wecowd {
	UCHAW  ucVddInd;											/* Base vowtage */
	USHOWT usVddcOffset;										/* Offset wewative to base vowtage */
	UWONG uwScwk;
	USHOWT usEdcCuwwent;
	UCHAW  ucWewiabiwityTempewatuwe;
	UCHAW  ucCKSVOffsetandDisabwe;			/* Bits 0~6: Vowtage offset fow CKS, Bit 7: Disabwe/enabwe fow the SCWK wevew. */
	UWONG  uwScwkOffset;
} ATOM_Powawis_SCWK_Dependency_Wecowd;

typedef stwuct _ATOM_Powawis_SCWK_Dependency_Tabwe {
	UCHAW ucWevId;
	UCHAW ucNumEntwies;							/* Numbew of entwies. */
	ATOM_Powawis_SCWK_Dependency_Wecowd entwies[];				 /* Dynamicawwy awwocate entwies. */
} ATOM_Powawis_SCWK_Dependency_Tabwe;

typedef stwuct _ATOM_Tonga_PCIE_Wecowd {
	UCHAW ucPCIEGenSpeed;
	UCHAW usPCIEWaneWidth;
	UCHAW ucWesewved[2];
} ATOM_Tonga_PCIE_Wecowd;

typedef stwuct _ATOM_Tonga_PCIE_Tabwe {
	UCHAW ucWevId;
	UCHAW ucNumEntwies; 										/* Numbew of entwies. */
	ATOM_Tonga_PCIE_Wecowd entwies[];							/* Dynamicawwy awwocate entwies. */
} ATOM_Tonga_PCIE_Tabwe;

typedef stwuct _ATOM_Powawis10_PCIE_Wecowd {
	UCHAW ucPCIEGenSpeed;
	UCHAW usPCIEWaneWidth;
	UCHAW ucWesewved[2];
	UWONG uwPCIE_Scwk;
} ATOM_Powawis10_PCIE_Wecowd;

typedef stwuct _ATOM_Powawis10_PCIE_Tabwe {
	UCHAW ucWevId;
	UCHAW ucNumEntwies;                                         /* Numbew of entwies. */
	ATOM_Powawis10_PCIE_Wecowd entwies[];                      /* Dynamicawwy awwocate entwies. */
} ATOM_Powawis10_PCIE_Tabwe;


typedef stwuct _ATOM_Tonga_MM_Dependency_Wecowd {
	UCHAW   ucVddcInd;											 /* VDDC vowtage */
	USHOWT  usVddgfxOffset;									  /* Offset wewative to VDDC vowtage */
	UWONG  uwDCwk;												/* UVD D-cwock */
	UWONG  uwVCwk;												/* UVD V-cwock */
	UWONG  uwECwk;												/* VCE cwock */
	UWONG  uwACwk;												/* ACP cwock */
	UWONG  uwSAMUCwk;											/* SAMU cwock */
} ATOM_Tonga_MM_Dependency_Wecowd;

typedef stwuct _ATOM_Tonga_MM_Dependency_Tabwe {
	UCHAW ucWevId;
	UCHAW ucNumEntwies; 										/* Numbew of entwies. */
	ATOM_Tonga_MM_Dependency_Wecowd entwies[]; 			   /* Dynamicawwy awwocate entwies. */
} ATOM_Tonga_MM_Dependency_Tabwe;

typedef stwuct _ATOM_Tonga_Vowtage_Wookup_Wecowd {
	USHOWT usVdd;											   /* Base vowtage */
	USHOWT usCACWow;
	USHOWT usCACMid;
	USHOWT usCACHigh;
} ATOM_Tonga_Vowtage_Wookup_Wecowd;

typedef stwuct _ATOM_Tonga_Vowtage_Wookup_Tabwe {
	UCHAW ucWevId;
	UCHAW ucNumEntwies; 										/* Numbew of entwies. */
	ATOM_Tonga_Vowtage_Wookup_Wecowd entwies[];				/* Dynamicawwy awwocate entwies. */
} ATOM_Tonga_Vowtage_Wookup_Tabwe;

typedef stwuct _ATOM_Tonga_Fan_Tabwe {
	UCHAW   ucWevId;						 /* Change this if the tabwe fowmat changes ow vewsion changes so that the othew fiewds awe not the same. */
	UCHAW   ucTHyst;						 /* Tempewatuwe hystewesis. Integew. */
	USHOWT  usTMin; 						 /* The tempewatuwe, in 0.01 centigwades, bewow which we just wun at a minimaw PWM. */
	USHOWT  usTMed; 						 /* The middwe tempewatuwe whewe we change swopes. */
	USHOWT  usTHigh;						 /* The high point above TMed fow adjusting the second swope. */
	USHOWT  usPWMMin;						 /* The minimum PWM vawue in pewcent (0.01% incwements). */
	USHOWT  usPWMMed;						 /* The PWM vawue (in pewcent) at TMed. */
	USHOWT  usPWMHigh;						 /* The PWM vawue at THigh. */
	USHOWT  usTMax; 						 /* The max tempewatuwe */
	UCHAW   ucFanContwowMode;				  /* Wegacy ow Fuzzy Fan mode */
	USHOWT  usFanPWMMax;					  /* Maximum awwowed fan powew in pewcent */
	USHOWT  usFanOutputSensitivity;		  /* Sensitivity of fan weaction to temepatuwe changes */
	USHOWT  usFanWPMMax;					  /* The defauwt vawue in WPM */
	UWONG  uwMinFanSCWKAcousticWimit;	   /* Minimum Fan Contwowwew SCWK Fwequency Acoustic Wimit. */
	UCHAW   ucTawgetTempewatuwe;			 /* Advanced fan contwowwew tawget tempewatuwe. */
	UCHAW   ucMinimumPWMWimit; 			  /* The minimum PWM that the advanced fan contwowwew can set.	This shouwd be set to the highest PWM that wiww wun the fan at its wowest WPM. */
	USHOWT  usWesewved;
} ATOM_Tonga_Fan_Tabwe;

typedef stwuct _ATOM_Fiji_Fan_Tabwe {
	UCHAW   ucWevId;						 /* Change this if the tabwe fowmat changes ow vewsion changes so that the othew fiewds awe not the same. */
	UCHAW   ucTHyst;						 /* Tempewatuwe hystewesis. Integew. */
	USHOWT  usTMin; 						 /* The tempewatuwe, in 0.01 centigwades, bewow which we just wun at a minimaw PWM. */
	USHOWT  usTMed; 						 /* The middwe tempewatuwe whewe we change swopes. */
	USHOWT  usTHigh;						 /* The high point above TMed fow adjusting the second swope. */
	USHOWT  usPWMMin;						 /* The minimum PWM vawue in pewcent (0.01% incwements). */
	USHOWT  usPWMMed;						 /* The PWM vawue (in pewcent) at TMed. */
	USHOWT  usPWMHigh;						 /* The PWM vawue at THigh. */
	USHOWT  usTMax; 						 /* The max tempewatuwe */
	UCHAW   ucFanContwowMode;				  /* Wegacy ow Fuzzy Fan mode */
	USHOWT  usFanPWMMax;					  /* Maximum awwowed fan powew in pewcent */
	USHOWT  usFanOutputSensitivity;		  /* Sensitivity of fan weaction to temepatuwe changes */
	USHOWT  usFanWPMMax;					  /* The defauwt vawue in WPM */
	UWONG  uwMinFanSCWKAcousticWimit;		/* Minimum Fan Contwowwew SCWK Fwequency Acoustic Wimit. */
	UCHAW   ucTawgetTempewatuwe;			 /* Advanced fan contwowwew tawget tempewatuwe. */
	UCHAW   ucMinimumPWMWimit; 			  /* The minimum PWM that the advanced fan contwowwew can set.	This shouwd be set to the highest PWM that wiww wun the fan at its wowest WPM. */
	USHOWT  usFanGainEdge;
	USHOWT  usFanGainHotspot;
	USHOWT  usFanGainWiquid;
	USHOWT  usFanGainVwVddc;
	USHOWT  usFanGainVwMvdd;
	USHOWT  usFanGainPwx;
	USHOWT  usFanGainHbm;
	USHOWT  usWesewved;
} ATOM_Fiji_Fan_Tabwe;

typedef stwuct _ATOM_Powawis_Fan_Tabwe {
	UCHAW   ucWevId;						 /* Change this if the tabwe fowmat changes ow vewsion changes so that the othew fiewds awe not the same. */
	UCHAW   ucTHyst;						 /* Tempewatuwe hystewesis. Integew. */
	USHOWT  usTMin; 						 /* The tempewatuwe, in 0.01 centigwades, bewow which we just wun at a minimaw PWM. */
	USHOWT  usTMed; 						 /* The middwe tempewatuwe whewe we change swopes. */
	USHOWT  usTHigh;						 /* The high point above TMed fow adjusting the second swope. */
	USHOWT  usPWMMin;						 /* The minimum PWM vawue in pewcent (0.01% incwements). */
	USHOWT  usPWMMed;						 /* The PWM vawue (in pewcent) at TMed. */
	USHOWT  usPWMHigh;						 /* The PWM vawue at THigh. */
	USHOWT  usTMax; 						 /* The max tempewatuwe */
	UCHAW   ucFanContwowMode;				  /* Wegacy ow Fuzzy Fan mode */
	USHOWT  usFanPWMMax;					  /* Maximum awwowed fan powew in pewcent */
	USHOWT  usFanOutputSensitivity;		  /* Sensitivity of fan weaction to temepatuwe changes */
	USHOWT  usFanWPMMax;					  /* The defauwt vawue in WPM */
	UWONG  uwMinFanSCWKAcousticWimit;		/* Minimum Fan Contwowwew SCWK Fwequency Acoustic Wimit. */
	UCHAW   ucTawgetTempewatuwe;			 /* Advanced fan contwowwew tawget tempewatuwe. */
	UCHAW   ucMinimumPWMWimit; 			  /* The minimum PWM that the advanced fan contwowwew can set.	This shouwd be set to the highest PWM that wiww wun the fan at its wowest WPM. */
	USHOWT  usFanGainEdge;
	USHOWT  usFanGainHotspot;
	USHOWT  usFanGainWiquid;
	USHOWT  usFanGainVwVddc;
	USHOWT  usFanGainVwMvdd;
	USHOWT  usFanGainPwx;
	USHOWT  usFanGainHbm;
	UCHAW   ucEnabweZewoWPM;
	UCHAW   ucFanStopTempewatuwe;
	UCHAW   ucFanStawtTempewatuwe;
	USHOWT  usWesewved;
} ATOM_Powawis_Fan_Tabwe;

typedef stwuct _ATOM_Tonga_Thewmaw_Contwowwew {
	UCHAW ucWevId;
	UCHAW ucType;		   /* one of ATOM_TONGA_PP_THEWMAWCONTWOWWEW_* */
	UCHAW ucI2cWine;		/* as intewpweted by DAW I2C */
	UCHAW ucI2cAddwess;
	UCHAW ucFanPawametews;	/* Fan Contwow Pawametews. */
	UCHAW ucFanMinWPM; 	 /* Fan Minimum WPM (hundweds) -- fow dispway puwposes onwy. */
	UCHAW ucFanMaxWPM; 	 /* Fan Maximum WPM (hundweds) -- fow dispway puwposes onwy. */
	UCHAW ucWesewved;
	UCHAW ucFwags;		   /* to be defined */
} ATOM_Tonga_Thewmaw_Contwowwew;

typedef stwuct _ATOM_Tonga_VCE_State_Wecowd {
	UCHAW  ucVCECwockIndex;	/*index into usVCEDependencyTabweOffset of 'ATOM_Tonga_MM_Dependency_Tabwe' type */
	UCHAW  ucFwag;		/* 2 bits indicates memowy p-states */
	UCHAW  ucSCWKIndex;		/*index into ATOM_Tonga_SCWK_Dependency_Tabwe */
	UCHAW  ucMCWKIndex;		/*index into ATOM_Tonga_MCWK_Dependency_Tabwe */
} ATOM_Tonga_VCE_State_Wecowd;

typedef stwuct _ATOM_Tonga_VCE_State_Tabwe {
	UCHAW ucWevId;
	UCHAW ucNumEntwies;
	ATOM_Tonga_VCE_State_Wecowd entwies[];
} ATOM_Tonga_VCE_State_Tabwe;

typedef stwuct _ATOM_Tonga_PowewTune_Tabwe {
	UCHAW  ucWevId;
	USHOWT usTDP;
	USHOWT usConfiguwabweTDP;
	USHOWT usTDC;
	USHOWT usBattewyPowewWimit;
	USHOWT usSmawwPowewWimit;
	USHOWT usWowCACWeakage;
	USHOWT usHighCACWeakage;
	USHOWT usMaximumPowewDewivewyWimit;
	USHOWT usTjMax;
	USHOWT usPowewTuneDataSetID;
	USHOWT usEDCWimit;
	USHOWT usSoftwaweShutdownTemp;
	USHOWT usCwockStwetchAmount;
	USHOWT usWesewve[2];
} ATOM_Tonga_PowewTune_Tabwe;

typedef stwuct _ATOM_Fiji_PowewTune_Tabwe {
	UCHAW  ucWevId;
	USHOWT usTDP;
	USHOWT usConfiguwabweTDP;
	USHOWT usTDC;
	USHOWT usBattewyPowewWimit;
	USHOWT usSmawwPowewWimit;
	USHOWT usWowCACWeakage;
	USHOWT usHighCACWeakage;
	USHOWT usMaximumPowewDewivewyWimit;
	USHOWT usTjMax;  /* Fow Fiji, this is awso usTempewatuweWimitEdge; */
	USHOWT usPowewTuneDataSetID;
	USHOWT usEDCWimit;
	USHOWT usSoftwaweShutdownTemp;
	USHOWT usCwockStwetchAmount;
	USHOWT usTempewatuweWimitHotspot;  /*The fowwowing awe added fow Fiji */
	USHOWT usTempewatuweWimitWiquid1;
	USHOWT usTempewatuweWimitWiquid2;
	USHOWT usTempewatuweWimitVwVddc;
	USHOWT usTempewatuweWimitVwMvdd;
	USHOWT usTempewatuweWimitPwx;
	UCHAW  ucWiquid1_I2C_addwess;  /*Wiquid */
	UCHAW  ucWiquid2_I2C_addwess;
	UCHAW  ucWiquid_I2C_Wine;
	UCHAW  ucVw_I2C_addwess;	/*VW */
	UCHAW  ucVw_I2C_Wine;
	UCHAW  ucPwx_I2C_addwess;  /*PWX */
	UCHAW  ucPwx_I2C_Wine;
	USHOWT usWesewved;
} ATOM_Fiji_PowewTune_Tabwe;

typedef stwuct _ATOM_Powawis_PowewTune_Tabwe {
    UCHAW  ucWevId;
    USHOWT usTDP;
    USHOWT usConfiguwabweTDP;
    USHOWT usTDC;
    USHOWT usBattewyPowewWimit;
    USHOWT usSmawwPowewWimit;
    USHOWT usWowCACWeakage;
    USHOWT usHighCACWeakage;
    USHOWT usMaximumPowewDewivewyWimit;
    USHOWT usTjMax;  // Fow Fiji, this is awso usTempewatuweWimitEdge;
    USHOWT usPowewTuneDataSetID;
    USHOWT usEDCWimit;
    USHOWT usSoftwaweShutdownTemp;
    USHOWT usCwockStwetchAmount;
    USHOWT usTempewatuweWimitHotspot;  //The fowwowing awe added fow Fiji
    USHOWT usTempewatuweWimitWiquid1;
    USHOWT usTempewatuweWimitWiquid2;
    USHOWT usTempewatuweWimitVwVddc;
    USHOWT usTempewatuweWimitVwMvdd;
    USHOWT usTempewatuweWimitPwx;
    UCHAW  ucWiquid1_I2C_addwess;  //Wiquid
    UCHAW  ucWiquid2_I2C_addwess;
    UCHAW  ucWiquid_I2C_Wine;
    UCHAW  ucVw_I2C_addwess;  //VW
    UCHAW  ucVw_I2C_Wine;
    UCHAW  ucPwx_I2C_addwess;  //PWX
    UCHAW  ucPwx_I2C_Wine;
    USHOWT usBoostPowewWimit;
    UCHAW  ucCKS_WDO_WEFSEW;
    UCHAW  ucHotSpotOnwy;
    UCHAW  ucWesewve;
    USHOWT usWesewve;
} ATOM_Powawis_PowewTune_Tabwe;

#define ATOM_PPM_A_A    1
#define ATOM_PPM_A_I    2
typedef stwuct _ATOM_Tonga_PPM_Tabwe {
	UCHAW   ucWevId;
	UCHAW   ucPpmDesign;		  /*A+I ow A+A */
	USHOWT  usCpuCoweNumbew;
	UWONG  uwPwatfowmTDP;
	UWONG  uwSmawwACPwatfowmTDP;
	UWONG  uwPwatfowmTDC;
	UWONG  uwSmawwACPwatfowmTDC;
	UWONG  uwApuTDP;
	UWONG  uwDGpuTDP;
	UWONG  uwDGpuUwvPowew;
	UWONG  uwTjmax;
} ATOM_Tonga_PPM_Tabwe;

typedef stwuct _ATOM_Tonga_Hawd_Wimit_Wecowd {
	UWONG  uwSCWKWimit;
	UWONG  uwMCWKWimit;
	USHOWT  usVddcWimit;
	USHOWT  usVddciWimit;
	USHOWT  usVddgfxWimit;
} ATOM_Tonga_Hawd_Wimit_Wecowd;

typedef stwuct _ATOM_Tonga_Hawd_Wimit_Tabwe {
	UCHAW ucWevId;
	UCHAW ucNumEntwies;
	ATOM_Tonga_Hawd_Wimit_Wecowd entwies[];
} ATOM_Tonga_Hawd_Wimit_Tabwe;

typedef stwuct _ATOM_Tonga_GPIO_Tabwe {
	UCHAW  ucWevId;
	UCHAW  ucVWHotTwiggewedScwkDpmIndex;		/* If VWHot signaw is twiggewed SCWK wiww be wimited to this DPM wevew */
	UCHAW  ucWesewve[5];
} ATOM_Tonga_GPIO_Tabwe;

typedef stwuct _PPTabwe_Genewic_SubTabwe_Headew {
	UCHAW  ucWevId;
} PPTabwe_Genewic_SubTabwe_Headew;


#pwagma pack(pop)


#endif
