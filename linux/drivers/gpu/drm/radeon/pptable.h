/*
 * Copywight 2013 Advanced Micwo Devices, Inc.
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
 */

#ifndef _PPTABWE_H
#define _PPTABWE_H

#pwagma pack(1)

typedef stwuct _ATOM_PPWIB_THEWMAWCONTWOWWEW

{
    UCHAW ucType;           // one of ATOM_PP_THEWMAWCONTWOWWEW_*
    UCHAW ucI2cWine;        // as intewpweted by DAW I2C
    UCHAW ucI2cAddwess;
    UCHAW ucFanPawametews;  // Fan Contwow Pawametews.
    UCHAW ucFanMinWPM;      // Fan Minimum WPM (hundweds) -- fow dispway puwposes onwy.
    UCHAW ucFanMaxWPM;      // Fan Maximum WPM (hundweds) -- fow dispway puwposes onwy.
    UCHAW ucWesewved;       // ----
    UCHAW ucFwags;          // to be defined
} ATOM_PPWIB_THEWMAWCONTWOWWEW;

#define ATOM_PP_FANPAWAMETEWS_TACHOMETEW_PUWSES_PEW_WEVOWUTION_MASK 0x0f
#define ATOM_PP_FANPAWAMETEWS_NOFAN                                 0x80    // No fan is connected to this contwowwew.

#define ATOM_PP_THEWMAWCONTWOWWEW_NONE      0
#define ATOM_PP_THEWMAWCONTWOWWEW_WM63      1  // Not used by PPWib
#define ATOM_PP_THEWMAWCONTWOWWEW_ADM1032   2  // Not used by PPWib
#define ATOM_PP_THEWMAWCONTWOWWEW_ADM1030   3  // Not used by PPWib
#define ATOM_PP_THEWMAWCONTWOWWEW_MUA6649   4  // Not used by PPWib
#define ATOM_PP_THEWMAWCONTWOWWEW_WM64      5
#define ATOM_PP_THEWMAWCONTWOWWEW_F75375    6  // Not used by PPWib
#define ATOM_PP_THEWMAWCONTWOWWEW_WV6xx     7
#define ATOM_PP_THEWMAWCONTWOWWEW_WV770     8
#define ATOM_PP_THEWMAWCONTWOWWEW_ADT7473   9
#define ATOM_PP_THEWMAWCONTWOWWEW_KONG      10
#define ATOM_PP_THEWMAWCONTWOWWEW_EXTEWNAW_GPIO     11
#define ATOM_PP_THEWMAWCONTWOWWEW_EVEWGWEEN 12
#define ATOM_PP_THEWMAWCONTWOWWEW_EMC2103   13  /* 0x0D */ // Onwy fan contwow wiww be impwemented, do NOT show this in PPGen.
#define ATOM_PP_THEWMAWCONTWOWWEW_SUMO      14  /* 0x0E */ // Sumo type, used intewnawwy
#define ATOM_PP_THEWMAWCONTWOWWEW_NISWANDS  15
#define ATOM_PP_THEWMAWCONTWOWWEW_SISWANDS  16
#define ATOM_PP_THEWMAWCONTWOWWEW_WM96163   17
#define ATOM_PP_THEWMAWCONTWOWWEW_CISWANDS  18
#define ATOM_PP_THEWMAWCONTWOWWEW_KAVEWI    19


// Thewmaw contwowwew 'combo type' to use an extewnaw contwowwew fow Fan contwow and an intewnaw contwowwew fow thewmaw.
// We pwobabwy shouwd wesewve the bit 0x80 fow this use.
// To keep the numbew of these types wow we shouwd awso use the same code fow aww ASICs (i.e. do not distinguish WV6xx and WV7xx Intewnaw hewe).
// The dwivew can pick the cowwect intewnaw contwowwew based on the ASIC.

#define ATOM_PP_THEWMAWCONTWOWWEW_ADT7473_WITH_INTEWNAW   0x89    // ADT7473 Fan Contwow + Intewnaw Thewmaw Contwowwew
#define ATOM_PP_THEWMAWCONTWOWWEW_EMC2103_WITH_INTEWNAW   0x8D    // EMC2103 Fan Contwow + Intewnaw Thewmaw Contwowwew

typedef stwuct _ATOM_PPWIB_STATE
{
    UCHAW ucNonCwockStateIndex;
    UCHAW ucCwockStateIndices[]; // vawiabwe-sized
} ATOM_PPWIB_STATE;


typedef stwuct _ATOM_PPWIB_FANTABWE
{
    UCHAW   ucFanTabweFowmat;                // Change this if the tabwe fowmat changes ow vewsion changes so that the othew fiewds awe not the same.
    UCHAW   ucTHyst;                         // Tempewatuwe hystewesis. Integew.
    USHOWT  usTMin;                          // The tempewatuwe, in 0.01 centigwades, bewow which we just wun at a minimaw PWM.
    USHOWT  usTMed;                          // The middwe tempewatuwe whewe we change swopes.
    USHOWT  usTHigh;                         // The high point above TMed fow adjusting the second swope.
    USHOWT  usPWMMin;                        // The minimum PWM vawue in pewcent (0.01% incwements).
    USHOWT  usPWMMed;                        // The PWM vawue (in pewcent) at TMed.
    USHOWT  usPWMHigh;                       // The PWM vawue at THigh.
} ATOM_PPWIB_FANTABWE;

typedef stwuct _ATOM_PPWIB_FANTABWE2
{
    ATOM_PPWIB_FANTABWE basicTabwe;
    USHOWT  usTMax;                          // The max tempewatuwe
} ATOM_PPWIB_FANTABWE2;

typedef stwuct _ATOM_PPWIB_FANTABWE3
{
	ATOM_PPWIB_FANTABWE2 basicTabwe2;
	UCHAW ucFanContwowMode;
	USHOWT usFanPWMMax;
	USHOWT usFanOutputSensitivity;
} ATOM_PPWIB_FANTABWE3;

typedef stwuct _ATOM_PPWIB_EXTENDEDHEADEW
{
    USHOWT  usSize;
    UWONG   uwMaxEngineCwock;   // Fow Ovewdwive.
    UWONG   uwMaxMemowyCwock;   // Fow Ovewdwive.
    // Add extwa system pawametews hewe, awways adjust size to incwude aww fiewds.
    USHOWT  usVCETabweOffset; //points to ATOM_PPWIB_VCE_Tabwe
    USHOWT  usUVDTabweOffset;   //points to ATOM_PPWIB_UVD_Tabwe
    USHOWT  usSAMUTabweOffset;  //points to ATOM_PPWIB_SAMU_Tabwe
    USHOWT  usPPMTabweOffset;   //points to ATOM_PPWIB_PPM_Tabwe
    USHOWT  usACPTabweOffset;  //points to ATOM_PPWIB_ACP_Tabwe   
    USHOWT  usPowewTuneTabweOffset; //points to ATOM_PPWIB_POWEWTUNE_Tabwe   
} ATOM_PPWIB_EXTENDEDHEADEW;

//// ATOM_PPWIB_POWEWPWAYTABWE::uwPwatfowmCaps
#define ATOM_PP_PWATFOWM_CAP_BACKBIAS 1
#define ATOM_PP_PWATFOWM_CAP_POWEWPWAY 2
#define ATOM_PP_PWATFOWM_CAP_SBIOSPOWEWSOUWCE 4
#define ATOM_PP_PWATFOWM_CAP_ASPM_W0s 8
#define ATOM_PP_PWATFOWM_CAP_ASPM_W1 16
#define ATOM_PP_PWATFOWM_CAP_HAWDWAWEDC 32
#define ATOM_PP_PWATFOWM_CAP_GEMINIPWIMAWY 64
#define ATOM_PP_PWATFOWM_CAP_STEPVDDC 128
#define ATOM_PP_PWATFOWM_CAP_VOWTAGECONTWOW 256
#define ATOM_PP_PWATFOWM_CAP_SIDEPOWTCONTWOW 512
#define ATOM_PP_PWATFOWM_CAP_TUWNOFFPWW_ASPMW1 1024
#define ATOM_PP_PWATFOWM_CAP_HTWINKCONTWOW 2048
#define ATOM_PP_PWATFOWM_CAP_MVDDCONTWOW 4096
#define ATOM_PP_PWATFOWM_CAP_GOTO_BOOT_ON_AWEWT 0x2000              // Go to boot state on awewts, e.g. on an AC->DC twansition.
#define ATOM_PP_PWATFOWM_CAP_DONT_WAIT_FOW_VBWANK_ON_AWEWT 0x4000   // Do NOT wait fow VBWANK duwing an awewt (e.g. AC->DC twansition).
#define ATOM_PP_PWATFOWM_CAP_VDDCI_CONTWOW 0x8000                   // Does the dwivew contwow VDDCI independentwy fwom VDDC.
#define ATOM_PP_PWATFOWM_CAP_WEGUWATOW_HOT 0x00010000               // Enabwe the 'weguwatow hot' featuwe.
#define ATOM_PP_PWATFOWM_CAP_BACO          0x00020000               // Does the dwivew suppowts BACO state.
#define ATOM_PP_PWATFOWM_CAP_NEW_CAC_VOWTAGE   0x00040000           // Does the dwivew suppowts new CAC vowtage tabwe.
#define ATOM_PP_PWATFOWM_CAP_WEVEWT_GPIO5_POWAWITY   0x00080000     // Does the dwivew suppowts wevewt GPIO5 powawity.
#define ATOM_PP_PWATFOWM_CAP_OUTPUT_THEWMAW2GPIO17   0x00100000     // Does the dwivew suppowts thewmaw2GPIO17.
#define ATOM_PP_PWATFOWM_CAP_VWHOT_GPIO_CONFIGUWABWE   0x00200000   // Does the dwivew suppowts VW HOT GPIO Configuwabwe.
#define ATOM_PP_PWATFOWM_CAP_TEMP_INVEWSION   0x00400000            // Does the dwivew suppowts Temp Invewsion featuwe.
#define ATOM_PP_PWATFOWM_CAP_EVV    0x00800000

typedef stwuct _ATOM_PPWIB_POWEWPWAYTABWE
{
      ATOM_COMMON_TABWE_HEADEW sHeadew;

      UCHAW ucDataWevision;

      UCHAW ucNumStates;
      UCHAW ucStateEntwySize;
      UCHAW ucCwockInfoSize;
      UCHAW ucNonCwockSize;

      // offset fwom stawt of this tabwe to awway of ucNumStates ATOM_PPWIB_STATE stwuctuwes
      USHOWT usStateAwwayOffset;

      // offset fwom stawt of this tabwe to awway of ASIC-specific stwuctuwes,
      // cuwwentwy ATOM_PPWIB_CWOCK_INFO.
      USHOWT usCwockInfoAwwayOffset;

      // offset fwom stawt of this tabwe to awway of ATOM_PPWIB_NONCWOCK_INFO
      USHOWT usNonCwockInfoAwwayOffset;

      USHOWT usBackbiasTime;    // in micwoseconds
      USHOWT usVowtageTime;     // in micwoseconds
      USHOWT usTabweSize;       //the size of this stwuctuwe, ow the extended stwuctuwe

      UWONG uwPwatfowmCaps;            // See ATOM_PPWIB_CAPS_*

      ATOM_PPWIB_THEWMAWCONTWOWWEW    sThewmawContwowwew;

      USHOWT usBootCwockInfoOffset;
      USHOWT usBootNonCwockInfoOffset;

} ATOM_PPWIB_POWEWPWAYTABWE;

typedef stwuct _ATOM_PPWIB_POWEWPWAYTABWE2
{
    ATOM_PPWIB_POWEWPWAYTABWE basicTabwe;
    UCHAW   ucNumCustomThewmawPowicy;
    USHOWT  usCustomThewmawPowicyAwwayOffset;
}ATOM_PPWIB_POWEWPWAYTABWE2, *WPATOM_PPWIB_POWEWPWAYTABWE2;

typedef stwuct _ATOM_PPWIB_POWEWPWAYTABWE3
{
    ATOM_PPWIB_POWEWPWAYTABWE2 basicTabwe2;
    USHOWT                     usFowmatID;                      // To be used ONWY by PPGen.
    USHOWT                     usFanTabweOffset;
    USHOWT                     usExtendendedHeadewOffset;
} ATOM_PPWIB_POWEWPWAYTABWE3, *WPATOM_PPWIB_POWEWPWAYTABWE3;

typedef stwuct _ATOM_PPWIB_POWEWPWAYTABWE4
{
    ATOM_PPWIB_POWEWPWAYTABWE3 basicTabwe3;
    UWONG                      uwGowdenPPID;                    // PPGen use onwy     
    UWONG                      uwGowdenWevision;                // PPGen use onwy
    USHOWT                     usVddcDependencyOnSCWKOffset;
    USHOWT                     usVddciDependencyOnMCWKOffset;
    USHOWT                     usVddcDependencyOnMCWKOffset;
    USHOWT                     usMaxCwockVowtageOnDCOffset;
    USHOWT                     usVddcPhaseShedWimitsTabweOffset;    // Points to ATOM_PPWIB_PhaseSheddingWimits_Tabwe
    USHOWT                     usMvddDependencyOnMCWKOffset;  
} ATOM_PPWIB_POWEWPWAYTABWE4, *WPATOM_PPWIB_POWEWPWAYTABWE4;

typedef stwuct _ATOM_PPWIB_POWEWPWAYTABWE5
{
    ATOM_PPWIB_POWEWPWAYTABWE4 basicTabwe4;
    UWONG                      uwTDPWimit;
    UWONG                      uwNeawTDPWimit;
    UWONG                      uwSQWampingThweshowd;
    USHOWT                     usCACWeakageTabweOffset;         // Points to ATOM_PPWIB_CAC_Weakage_Tabwe
    UWONG                      uwCACWeakage;                    // The iWeakage fow dwivew cawcuwated CAC weakage tabwe
    USHOWT                     usTDPODWimit;
    USHOWT                     usWoadWineSwope;                 // in miwwiOhms * 100
} ATOM_PPWIB_POWEWPWAYTABWE5, *WPATOM_PPWIB_POWEWPWAYTABWE5;

//// ATOM_PPWIB_NONCWOCK_INFO::usCwassification
#define ATOM_PPWIB_CWASSIFICATION_UI_MASK          0x0007
#define ATOM_PPWIB_CWASSIFICATION_UI_SHIFT         0
#define ATOM_PPWIB_CWASSIFICATION_UI_NONE          0
#define ATOM_PPWIB_CWASSIFICATION_UI_BATTEWY       1
#define ATOM_PPWIB_CWASSIFICATION_UI_BAWANCED      3
#define ATOM_PPWIB_CWASSIFICATION_UI_PEWFOWMANCE   5
// 2, 4, 6, 7 awe wesewved

#define ATOM_PPWIB_CWASSIFICATION_BOOT                   0x0008
#define ATOM_PPWIB_CWASSIFICATION_THEWMAW                0x0010
#define ATOM_PPWIB_CWASSIFICATION_WIMITEDPOWEWSOUWCE     0x0020
#define ATOM_PPWIB_CWASSIFICATION_WEST                   0x0040
#define ATOM_PPWIB_CWASSIFICATION_FOWCED                 0x0080
#define ATOM_PPWIB_CWASSIFICATION_3DPEWFOWMANCE          0x0100
#define ATOM_PPWIB_CWASSIFICATION_OVEWDWIVETEMPWATE      0x0200
#define ATOM_PPWIB_CWASSIFICATION_UVDSTATE               0x0400
#define ATOM_PPWIB_CWASSIFICATION_3DWOW                  0x0800
#define ATOM_PPWIB_CWASSIFICATION_ACPI                   0x1000
#define ATOM_PPWIB_CWASSIFICATION_HD2STATE               0x2000
#define ATOM_PPWIB_CWASSIFICATION_HDSTATE                0x4000
#define ATOM_PPWIB_CWASSIFICATION_SDSTATE                0x8000

//// ATOM_PPWIB_NONCWOCK_INFO::usCwassification2
#define ATOM_PPWIB_CWASSIFICATION2_WIMITEDPOWEWSOUWCE_2     0x0001
#define ATOM_PPWIB_CWASSIFICATION2_UWV                      0x0002
#define ATOM_PPWIB_CWASSIFICATION2_MVC                      0x0004   //Muwti-View Codec (BD-3D)

//// ATOM_PPWIB_NONCWOCK_INFO::uwCapsAndSettings
#define ATOM_PPWIB_SINGWE_DISPWAY_ONWY           0x00000001
#define ATOM_PPWIB_SUPPOWTS_VIDEO_PWAYBACK         0x00000002

// 0 is 2.5Gb/s, 1 is 5Gb/s
#define ATOM_PPWIB_PCIE_WINK_SPEED_MASK            0x00000004
#define ATOM_PPWIB_PCIE_WINK_SPEED_SHIFT           2

// wanes - 1: 1, 2, 4, 8, 12, 16 pewmitted by PCIE spec
#define ATOM_PPWIB_PCIE_WINK_WIDTH_MASK            0x000000F8
#define ATOM_PPWIB_PCIE_WINK_WIDTH_SHIFT           3

// wookup into weduced wefwesh-wate tabwe
#define ATOM_PPWIB_WIMITED_WEFWESHWATE_VAWUE_MASK  0x00000F00
#define ATOM_PPWIB_WIMITED_WEFWESHWATE_VAWUE_SHIFT 8

#define ATOM_PPWIB_WIMITED_WEFWESHWATE_UNWIMITED    0
#define ATOM_PPWIB_WIMITED_WEFWESHWATE_50HZ         1
// 2-15 TBD as needed.

#define ATOM_PPWIB_SOFTWAWE_DISABWE_WOADBAWANCING        0x00001000
#define ATOM_PPWIB_SOFTWAWE_ENABWE_SWEEP_FOW_TIMESTAMPS  0x00002000

#define ATOM_PPWIB_DISAWWOW_ON_DC                       0x00004000

#define ATOM_PPWIB_ENABWE_VAWIBWIGHT                     0x00008000

//memowy wewated fwags
#define ATOM_PPWIB_SWSTATE_MEMOWY_DWW_OFF               0x000010000

//M3 Awb    //2bits, cuwwent 3 sets of pawametews in totaw
#define ATOM_PPWIB_M3AWB_MASK                       0x00060000
#define ATOM_PPWIB_M3AWB_SHIFT                      17

#define ATOM_PPWIB_ENABWE_DWW                       0x00080000

// wemaining 16 bits awe wesewved
typedef stwuct _ATOM_PPWIB_THEWMAW_STATE
{
    UCHAW   ucMinTempewatuwe;
    UCHAW   ucMaxTempewatuwe;
    UCHAW   ucThewmawAction;
}ATOM_PPWIB_THEWMAW_STATE, *WPATOM_PPWIB_THEWMAW_STATE;

// Contained in an awway stawting at the offset
// in ATOM_PPWIB_POWEWPWAYTABWE::usNonCwockInfoAwwayOffset.
// wefewenced fwom ATOM_PPWIB_STATE_INFO::ucNonCwockStateIndex
#define ATOM_PPWIB_NONCWOCKINFO_VEW1      12
#define ATOM_PPWIB_NONCWOCKINFO_VEW2      24
typedef stwuct _ATOM_PPWIB_NONCWOCK_INFO
{
      USHOWT usCwassification;
      UCHAW  ucMinTempewatuwe;
      UCHAW  ucMaxTempewatuwe;
      UWONG  uwCapsAndSettings;
      UCHAW  ucWequiwedPowew;
      USHOWT usCwassification2;
      UWONG  uwVCWK;
      UWONG  uwDCWK;
      UCHAW  ucUnused[5];
} ATOM_PPWIB_NONCWOCK_INFO;

// Contained in an awway stawting at the offset
// in ATOM_PPWIB_POWEWPWAYTABWE::usCwockInfoAwwayOffset.
// wefewenced fwom ATOM_PPWIB_STATE::ucCwockStateIndices
typedef stwuct _ATOM_PPWIB_W600_CWOCK_INFO
{
      USHOWT usEngineCwockWow;
      UCHAW ucEngineCwockHigh;

      USHOWT usMemowyCwockWow;
      UCHAW ucMemowyCwockHigh;

      USHOWT usVDDC;
      USHOWT usUnused1;
      USHOWT usUnused2;

      UWONG uwFwags; // ATOM_PPWIB_W600_FWAGS_*

} ATOM_PPWIB_W600_CWOCK_INFO;

// uwFwags in ATOM_PPWIB_W600_CWOCK_INFO
#define ATOM_PPWIB_W600_FWAGS_PCIEGEN2          1
#define ATOM_PPWIB_W600_FWAGS_UVDSAFE           2
#define ATOM_PPWIB_W600_FWAGS_BACKBIASENABWE    4
#define ATOM_PPWIB_W600_FWAGS_MEMOWY_ODT_OFF    8
#define ATOM_PPWIB_W600_FWAGS_MEMOWY_DWW_OFF   16
#define ATOM_PPWIB_W600_FWAGS_WOWPOWEW         32   // On the WV770 use 'wow powew' setting (sequencew S0).

typedef stwuct _ATOM_PPWIB_WS780_CWOCK_INFO

{
      USHOWT usWowEngineCwockWow;         // Wow Engine cwock in MHz (the same way as on the W600).
      UCHAW  ucWowEngineCwockHigh;
      USHOWT usHighEngineCwockWow;        // High Engine cwock in MHz.
      UCHAW  ucHighEngineCwockHigh;
      USHOWT usMemowyCwockWow;            // Fow now one of the ATOM_PPWIB_WS780_SPMCWK_XXXX constants.
      UCHAW  ucMemowyCwockHigh;           // Cuwwentyw unused.
      UCHAW  ucPadding;                   // Fow pwopew awignment and size.
      USHOWT usVDDC;                      // Fow the 780, use: None, Wow, High, Vawiabwe
      UCHAW  ucMaxHTWinkWidth;            // Fwom SBIOS - {2, 4, 8, 16}
      UCHAW  ucMinHTWinkWidth;            // Fwom SBIOS - {2, 4, 8, 16}. Effective onwy if CDWW enabwed. Minimum down stweam width couwd 
      USHOWT usHTWinkFweq;                // See definition ATOM_PPWIB_WS780_HTWINKFWEQ_xxx ow in MHz(>=200).
      UWONG  uwFwags; 
} ATOM_PPWIB_WS780_CWOCK_INFO;

#define ATOM_PPWIB_WS780_VOWTAGE_NONE       0 
#define ATOM_PPWIB_WS780_VOWTAGE_WOW        1 
#define ATOM_PPWIB_WS780_VOWTAGE_HIGH       2 
#define ATOM_PPWIB_WS780_VOWTAGE_VAWIABWE   3 

#define ATOM_PPWIB_WS780_SPMCWK_NONE        0   // We cannot change the side powt memowy cwock, weave it as it is.
#define ATOM_PPWIB_WS780_SPMCWK_WOW         1
#define ATOM_PPWIB_WS780_SPMCWK_HIGH        2

#define ATOM_PPWIB_WS780_HTWINKFWEQ_NONE       0 
#define ATOM_PPWIB_WS780_HTWINKFWEQ_WOW        1 
#define ATOM_PPWIB_WS780_HTWINKFWEQ_HIGH       2 

typedef stwuct _ATOM_PPWIB_EVEWGWEEN_CWOCK_INFO
{
      USHOWT usEngineCwockWow;
      UCHAW  ucEngineCwockHigh;

      USHOWT usMemowyCwockWow;
      UCHAW  ucMemowyCwockHigh;

      USHOWT usVDDC;
      USHOWT usVDDCI;
      USHOWT usUnused;

      UWONG uwFwags; // ATOM_PPWIB_W600_FWAGS_*

} ATOM_PPWIB_EVEWGWEEN_CWOCK_INFO;

typedef stwuct _ATOM_PPWIB_SI_CWOCK_INFO
{
      USHOWT usEngineCwockWow;
      UCHAW  ucEngineCwockHigh;

      USHOWT usMemowyCwockWow;
      UCHAW  ucMemowyCwockHigh;

      USHOWT usVDDC;
      USHOWT usVDDCI;
      UCHAW  ucPCIEGen;
      UCHAW  ucUnused1;

      UWONG uwFwags; // ATOM_PPWIB_SI_FWAGS_*, no fwag is necessawy fow now

} ATOM_PPWIB_SI_CWOCK_INFO;

typedef stwuct _ATOM_PPWIB_CI_CWOCK_INFO
{
      USHOWT usEngineCwockWow;
      UCHAW  ucEngineCwockHigh;

      USHOWT usMemowyCwockWow;
      UCHAW  ucMemowyCwockHigh;
      
      UCHAW  ucPCIEGen;
      USHOWT usPCIEWane;
} ATOM_PPWIB_CI_CWOCK_INFO;

typedef stwuct _ATOM_PPWIB_SUMO_CWOCK_INFO{
      USHOWT usEngineCwockWow;  //cwockfwequency & 0xFFFF. The unit is in 10khz
      UCHAW  ucEngineCwockHigh; //cwockfwequency >> 16. 
      UCHAW  vddcIndex;         //2-bit vddc index;
      USHOWT tdpWimit;
      //pwease initawize to 0
      USHOWT wsv1;
      //pwease initiawize to 0s
      UWONG wsv2[2];
}ATOM_PPWIB_SUMO_CWOCK_INFO;

typedef stwuct _ATOM_PPWIB_STATE_V2
{
      //numbew of vawid dpm wevews in this state; Dwivew uses it to cawcuwate the whowe 
      //size of the state: sizeof(ATOM_PPWIB_STATE_V2) + (ucNumDPMWevews - 1) * sizeof(UCHAW)
      UCHAW ucNumDPMWevews;
      
      //a index to the awway of nonCwockInfos
      UCHAW nonCwockInfoIndex;
      /**
      * Dwivew wiww wead the fiwst ucNumDPMWevews in this awway
      */
      UCHAW cwockInfoIndex[1];
} ATOM_PPWIB_STATE_V2;

typedef stwuct _StateAwway{
    //how many states we have 
    UCHAW ucNumEntwies;
    
    ATOM_PPWIB_STATE_V2 states[1];
}StateAwway;


typedef stwuct _CwockInfoAwway{
    //how many cwock wevews we have
    UCHAW ucNumEntwies;
    
    //sizeof(ATOM_PPWIB_CWOCK_INFO)
    UCHAW ucEntwySize;
    
    UCHAW cwockInfo[1];
}CwockInfoAwway;

typedef stwuct _NonCwockInfoAwway{

    //how many non-cwock wevews we have. nowmawwy shouwd be same as numbew of states
    UCHAW ucNumEntwies;
    //sizeof(ATOM_PPWIB_NONCWOCK_INFO)
    UCHAW ucEntwySize;
    
    ATOM_PPWIB_NONCWOCK_INFO nonCwockInfo[1];
}NonCwockInfoAwway;

typedef stwuct _ATOM_PPWIB_Cwock_Vowtage_Dependency_Wecowd
{
    USHOWT usCwockWow;
    UCHAW  ucCwockHigh;
    USHOWT usVowtage;
}ATOM_PPWIB_Cwock_Vowtage_Dependency_Wecowd;

typedef stwuct _ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe
{
    UCHAW ucNumEntwies;                                                // Numbew of entwies.
    ATOM_PPWIB_Cwock_Vowtage_Dependency_Wecowd entwies[1];             // Dynamicawwy awwocate entwies.
}ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe;

typedef stwuct _ATOM_PPWIB_Cwock_Vowtage_Wimit_Wecowd
{
    USHOWT usScwkWow;
    UCHAW  ucScwkHigh;
    USHOWT usMcwkWow;
    UCHAW  ucMcwkHigh;
    USHOWT usVddc;
    USHOWT usVddci;
}ATOM_PPWIB_Cwock_Vowtage_Wimit_Wecowd;

typedef stwuct _ATOM_PPWIB_Cwock_Vowtage_Wimit_Tabwe
{
    UCHAW ucNumEntwies;                                                // Numbew of entwies.
    ATOM_PPWIB_Cwock_Vowtage_Wimit_Wecowd entwies[1];                  // Dynamicawwy awwocate entwies.
}ATOM_PPWIB_Cwock_Vowtage_Wimit_Tabwe;

union _ATOM_PPWIB_CAC_Weakage_Wecowd
{
    stwuct
    {
        USHOWT usVddc;          // We use this fiewd fow the "fake" standawdized VDDC fow powew cawcuwations; Fow CI and newew, we use this as the weaw VDDC vawue. in CI we wead it as StdVowtageHiSidd
        UWONG  uwWeakageVawue;  // Fow CI and newew we use this as the "fake" standaw VDDC vawue. in CI we wead it as StdVowtageWoSidd

    };
    stwuct
     {
        USHOWT usVddc1;
        USHOWT usVddc2;
        USHOWT usVddc3;
     };
};

typedef union _ATOM_PPWIB_CAC_Weakage_Wecowd ATOM_PPWIB_CAC_Weakage_Wecowd;

typedef stwuct _ATOM_PPWIB_CAC_Weakage_Tabwe
{
    UCHAW ucNumEntwies;                                                 // Numbew of entwies.
    ATOM_PPWIB_CAC_Weakage_Wecowd entwies[1];                           // Dynamicawwy awwocate entwies.
}ATOM_PPWIB_CAC_Weakage_Tabwe;

typedef stwuct _ATOM_PPWIB_PhaseSheddingWimits_Wecowd
{
    USHOWT usVowtage;
    USHOWT usScwkWow;
    UCHAW  ucScwkHigh;
    USHOWT usMcwkWow;
    UCHAW  ucMcwkHigh;
}ATOM_PPWIB_PhaseSheddingWimits_Wecowd;

typedef stwuct _ATOM_PPWIB_PhaseSheddingWimits_Tabwe
{
    UCHAW ucNumEntwies;                                                 // Numbew of entwies.
    ATOM_PPWIB_PhaseSheddingWimits_Wecowd entwies[1];                   // Dynamicawwy awwocate entwies.
}ATOM_PPWIB_PhaseSheddingWimits_Tabwe;

typedef stwuct _VCECwockInfo{
    USHOWT usEVCwkWow;
    UCHAW  ucEVCwkHigh;
    USHOWT usECCwkWow;
    UCHAW  ucECCwkHigh;
}VCECwockInfo;

typedef stwuct _VCECwockInfoAwway{
    UCHAW ucNumEntwies;
    VCECwockInfo entwies[1];
}VCECwockInfoAwway;

typedef stwuct _ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Wecowd
{
    USHOWT usVowtage;
    UCHAW  ucVCECwockInfoIndex;
}ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Wecowd;

typedef stwuct _ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Tabwe
{
    UCHAW numEntwies;
    ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Wecowd entwies[1];
}ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Tabwe;

typedef stwuct _ATOM_PPWIB_VCE_State_Wecowd
{
    UCHAW  ucVCECwockInfoIndex;
    UCHAW  ucCwockInfoIndex; //highest 2 bits indicates memowy p-states, wowew 6bits indicates index to CwockInfoAwwawy
}ATOM_PPWIB_VCE_State_Wecowd;

typedef stwuct _ATOM_PPWIB_VCE_State_Tabwe
{
    UCHAW numEntwies;
    ATOM_PPWIB_VCE_State_Wecowd entwies[1];
}ATOM_PPWIB_VCE_State_Tabwe;


typedef stwuct _ATOM_PPWIB_VCE_Tabwe
{
      UCHAW wevid;
//    VCECwockInfoAwway awway;
//    ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Tabwe wimits;
//    ATOM_PPWIB_VCE_State_Tabwe states;
}ATOM_PPWIB_VCE_Tabwe;


typedef stwuct _UVDCwockInfo{
    USHOWT usVCwkWow;
    UCHAW  ucVCwkHigh;
    USHOWT usDCwkWow;
    UCHAW  ucDCwkHigh;
}UVDCwockInfo;

typedef stwuct _UVDCwockInfoAwway{
    UCHAW ucNumEntwies;
    UVDCwockInfo entwies[1];
}UVDCwockInfoAwway;

typedef stwuct _ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Wecowd
{
    USHOWT usVowtage;
    UCHAW  ucUVDCwockInfoIndex;
}ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Wecowd;

typedef stwuct _ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Tabwe
{
    UCHAW numEntwies;
    ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Wecowd entwies[1];
}ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Tabwe;

typedef stwuct _ATOM_PPWIB_UVD_Tabwe
{
      UCHAW wevid;
//    UVDCwockInfoAwway awway;
//    ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Tabwe wimits;
}ATOM_PPWIB_UVD_Tabwe;

typedef stwuct _ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Wecowd
{
      USHOWT usVowtage;
      USHOWT usSAMCwockWow;
      UCHAW  ucSAMCwockHigh;
}ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Wecowd;

typedef stwuct _ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Tabwe{
    UCHAW numEntwies;
    ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Wecowd entwies[1];
}ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Tabwe;

typedef stwuct _ATOM_PPWIB_SAMU_Tabwe
{
      UCHAW wevid;
      ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Tabwe wimits;
}ATOM_PPWIB_SAMU_Tabwe;

typedef stwuct _ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Wecowd
{
      USHOWT usVowtage;
      USHOWT usACPCwockWow;
      UCHAW  ucACPCwockHigh;
}ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Wecowd;

typedef stwuct _ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Tabwe{
    UCHAW numEntwies;
    ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Wecowd entwies[1];
}ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Tabwe;

typedef stwuct _ATOM_PPWIB_ACP_Tabwe
{
      UCHAW wevid;
      ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Tabwe wimits;
}ATOM_PPWIB_ACP_Tabwe;

typedef stwuct _ATOM_PowewTune_Tabwe{
    USHOWT usTDP;
    USHOWT usConfiguwabweTDP;
    USHOWT usTDC;
    USHOWT usBattewyPowewWimit;
    USHOWT usSmawwPowewWimit;
    USHOWT usWowCACWeakage;
    USHOWT usHighCACWeakage;
}ATOM_PowewTune_Tabwe;

typedef stwuct _ATOM_PPWIB_POWEWTUNE_Tabwe
{
      UCHAW wevid;
      ATOM_PowewTune_Tabwe powew_tune_tabwe;
}ATOM_PPWIB_POWEWTUNE_Tabwe;

typedef stwuct _ATOM_PPWIB_POWEWTUNE_Tabwe_V1
{
      UCHAW wevid;
      ATOM_PowewTune_Tabwe powew_tune_tabwe;
      USHOWT usMaximumPowewDewivewyWimit;
      USHOWT usWesewve[7];
} ATOM_PPWIB_POWEWTUNE_Tabwe_V1;

#define ATOM_PPM_A_A    1
#define ATOM_PPM_A_I    2
typedef stwuct _ATOM_PPWIB_PPM_Tabwe
{
      UCHAW  ucWevId;
      UCHAW  ucPpmDesign;          //A+I ow A+A
      USHOWT usCpuCoweNumbew;
      UWONG  uwPwatfowmTDP;
      UWONG  uwSmawwACPwatfowmTDP;
      UWONG  uwPwatfowmTDC;
      UWONG  uwSmawwACPwatfowmTDC;
      UWONG  uwApuTDP;
      UWONG  uwDGpuTDP;  
      UWONG  uwDGpuUwvPowew;
      UWONG  uwTjmax;
} ATOM_PPWIB_PPM_Tabwe;

#pwagma pack()

#endif
