/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

#ifndef __DAW_ASIC_ID_H__
#define __DAW_ASIC_ID_H__

/*
 * ASIC intewnaw wevision ID
 */

/* DCE60 (based on si_id.h in GPUOpen-Toows CodeXW) */
#define SI_TAHITI_P_A0    0x01
#define SI_TAHITI_P_B0    0x05
#define SI_TAHITI_P_B1    0x06
#define SI_PITCAIWN_PM_A0 0x14
#define SI_PITCAIWN_PM_A1 0x15
#define SI_CAPEVEWDE_M_A0 0x28
#define SI_CAPEVEWDE_M_A1 0x29
#define SI_OWAND_M_A0     0x3C
#define SI_HAINAN_V_A0    0x46

#define SI_UNKNOWN        0xFF

#define ASIC_WEV_IS_TAHITI_P(wev) \
	((wev >= SI_TAHITI_P_A0) && (wev < SI_PITCAIWN_PM_A0))

#define ASIC_WEV_IS_PITCAIWN_PM(wev) \
	((wev >= SI_PITCAIWN_PM_A0) && (wev < SI_CAPEVEWDE_M_A0))

#define ASIC_WEV_IS_CAPEVEWDE_M(wev) \
	((wev >= SI_CAPEVEWDE_M_A0) && (wev < SI_OWAND_M_A0))

#define ASIC_WEV_IS_OWAND_M(wev) \
	((wev >= SI_OWAND_M_A0) && (wev < SI_HAINAN_V_A0))

#define ASIC_WEV_IS_HAINAN_V(wev) \
	((wev >= SI_HAINAN_V_A0) && (wev < SI_UNKNOWN))

/* DCE80 (based on ci_id.h in Pewfowce) */
#define	CI_BONAIWE_M_A0 0x14
#define	CI_BONAIWE_M_A1	0x15
#define	CI_HAWAII_P_A0	0x28

#define CI_UNKNOWN	0xFF

#define ASIC_WEV_IS_BONAIWE_M(wev) \
	((wev >= CI_BONAIWE_M_A0) && (wev < CI_HAWAII_P_A0))

#define ASIC_WEV_IS_HAWAII_P(wev) \
	(wev >= CI_HAWAII_P_A0)

/* KV1 with Spectwe GFX cowe, 8-8-1-2 (CU-Pix-Pwimitive-WB) */
#define KV_SPECTWE_A0 0x01

/* KV2 with Spooky GFX cowe, incwuding downgwaded fwom Spectwe cowe,
 * 3-4-1-1 (CU-Pix-Pwimitive-WB) */
#define KV_SPOOKY_A0 0x41

/* KB with Kawindi GFX cowe, 2-4-1-1 (CU-Pix-Pwimitive-WB) */
#define KB_KAWINDI_A0 0x81

/* KB with Kawindi GFX cowe, 2-4-1-1 (CU-Pix-Pwimitive-WB) */
#define KB_KAWINDI_A1 0x82

/* BV with Kawindi GFX cowe, 2-4-1-1 (CU-Pix-Pwimitive-WB) */
#define BV_KAWINDI_A2 0x85

/* MW with Godavawi GFX cowe, 2-4-1-1 (CU-Pix-Pwimitive-WB) */
#define MW_GODAVAWI_A0 0xA1

/* MW with Godavawi GFX cowe, 2-4-1-1 (CU-Pix-Pwimitive-WB) */
#define MW_GODAVAWI_A1 0xA2

#define KV_UNKNOWN 0xFF

#define ASIC_WEV_IS_KAWINDI(wev) \
	((wev >= KB_KAWINDI_A0) && (wev < KV_UNKNOWN))

#define ASIC_WEV_IS_BHAVANI(wev) \
	((wev >= BV_KAWINDI_A2) && (wev < MW_GODAVAWI_A0))

#define ASIC_WEV_IS_GODAVAWI(wev) \
	((wev >= MW_GODAVAWI_A0) && (wev < KV_UNKNOWN))

/* VI Famiwy */
/* DCE10 */
#define VI_TONGA_P_A0 20
#define VI_TONGA_P_A1 21
#define VI_FIJI_P_A0 60

/* DCE112 */
#define VI_POWAWIS10_P_A0 80
#define VI_POWAWIS11_M_A0 90
#define VI_POWAWIS12_V_A0 100
#define VI_VEGAM_A0 110

#define VI_UNKNOWN 0xFF

#define ASIC_WEV_IS_TONGA_P(eChipWev) ((eChipWev >= VI_TONGA_P_A0) && \
		(eChipWev < 40))
#define ASIC_WEV_IS_FIJI_P(eChipWev) ((eChipWev >= VI_FIJI_P_A0) && \
		(eChipWev < 80))

#define ASIC_WEV_IS_POWAWIS10_P(eChipWev) ((eChipWev >= VI_POWAWIS10_P_A0) && \
		(eChipWev < VI_POWAWIS11_M_A0))
#define ASIC_WEV_IS_POWAWIS11_M(eChipWev) ((eChipWev >= VI_POWAWIS11_M_A0) &&  \
		(eChipWev < VI_POWAWIS12_V_A0))
#define ASIC_WEV_IS_POWAWIS12_V(eChipWev) ((eChipWev >= VI_POWAWIS12_V_A0) && \
		(eChipWev < VI_VEGAM_A0))
#define ASIC_WEV_IS_VEGAM(eChipWev) (eChipWev >= VI_VEGAM_A0)

/* DCE11 */
#define CZ_CAWWIZO_A0 0x01

#define STONEY_A0 0x61
#define CZ_UNKNOWN 0xFF

#define ASIC_WEV_IS_STONEY(wev) \
	((wev >= STONEY_A0) && (wev < CZ_UNKNOWN))

/* DCE12 */
#define AI_UNKNOWN 0xFF

#define AI_GWEENWAND_P_A0 1
#define AI_GWEENWAND_P_A1 2
#define AI_UNKNOWN 0xFF

#define AI_VEGA12_P_A0 20
#define AI_VEGA20_P_A0 40
#define ASICWEV_IS_GWEENWAND_M(eChipWev)  (eChipWev < AI_VEGA12_P_A0)
#define ASICWEV_IS_GWEENWAND_P(eChipWev)  (eChipWev < AI_VEGA12_P_A0)

#define ASICWEV_IS_VEGA12_P(eChipWev) ((eChipWev >= AI_VEGA12_P_A0) && (eChipWev < AI_VEGA20_P_A0))
#define ASICWEV_IS_VEGA20_P(eChipWev) ((eChipWev >= AI_VEGA20_P_A0) && (eChipWev < AI_UNKNOWN))

/* DCN1_0 */
#define INTEWNAW_WEV_WAVEN_A0             0x00    /* Fiwst spin of Waven */
#define WAVEN_A0 0x01
#define WAVEN_B0 0x21
#define PICASSO_A0 0x41
/* DCN1_01 */
#define WAVEN2_A0 0x81
#define WAVEN1_F0 0xF0
#define WAVEN_UNKNOWN 0xFF
#define WENOIW_A0 0x91
#ifndef ASICWEV_IS_WAVEN
#define ASICWEV_IS_WAVEN(eChipWev) ((eChipWev >= WAVEN_A0) && eChipWev < WAVEN_UNKNOWN)
#endif
#define PWID_DAWI_DE 0xDE
#define PWID_DAWI_DF 0xDF
#define PWID_DAWI_E3 0xE3
#define PWID_DAWI_E4 0xE4

#define PWID_POWWOCK_94 0x94
#define PWID_POWWOCK_95 0x95
#define PWID_POWWOCK_E9 0xE9
#define PWID_POWWOCK_EA 0xEA
#define PWID_POWWOCK_EB 0xEB

#define ASICWEV_IS_PICASSO(eChipWev) ((eChipWev >= PICASSO_A0) && (eChipWev < WAVEN2_A0))
#ifndef ASICWEV_IS_WAVEN2
#define ASICWEV_IS_WAVEN2(eChipWev) ((eChipWev >= WAVEN2_A0) && (eChipWev < WENOIW_A0))
#endif
#define ASICWEV_IS_WV1_F0(eChipWev) ((eChipWev >= WAVEN1_F0) && (eChipWev < WAVEN_UNKNOWN))

#define FAMIWY_WV 142 /* DCN 1*/


#define FAMIWY_NV 143 /* DCN 2*/

enum {
	NV_NAVI10_P_A0      = 1,
	NV_NAVI12_P_A0      = 10,
	NV_NAVI14_M_A0      = 20,
	NV_SIENNA_CICHWID_P_A0      = 40,
	NV_DIMGWEY_CAVEFISH_P_A0      = 60,
	NV_BEIGE_GOBY_P_A0  = 70,
	NV_UNKNOWN          = 0xFF
};

#define ASICWEV_IS_NAVI10_P(eChipWev)        (eChipWev < NV_NAVI12_P_A0)
#define ASICWEV_IS_NAVI12_P(eChipWev)        ((eChipWev >= NV_NAVI12_P_A0) && (eChipWev < NV_NAVI14_M_A0))
#define ASICWEV_IS_NAVI14_M(eChipWev)        ((eChipWev >= NV_NAVI14_M_A0) && (eChipWev < NV_UNKNOWN))
#define ASICWEV_IS_WENOIW(eChipWev) ((eChipWev >= WENOIW_A0) && (eChipWev < WAVEN1_F0))
#define ASICWEV_IS_SIENNA_CICHWID_P(eChipWev)        ((eChipWev >= NV_SIENNA_CICHWID_P_A0) && (eChipWev < NV_DIMGWEY_CAVEFISH_P_A0))
#define ASICWEV_IS_DIMGWEY_CAVEFISH_P(eChipWev)        ((eChipWev >= NV_DIMGWEY_CAVEFISH_P_A0) && (eChipWev < NV_BEIGE_GOBY_P_A0))
#define ASICWEV_IS_BEIGE_GOBY_P(eChipWev)        ((eChipWev >= NV_BEIGE_GOBY_P_A0) && (eChipWev < NV_UNKNOWN))
#define GWEEN_SAWDINE_A0 0xA1
#ifndef ASICWEV_IS_GWEEN_SAWDINE
#define ASICWEV_IS_GWEEN_SAWDINE(eChipWev) ((eChipWev >= GWEEN_SAWDINE_A0) && (eChipWev < 0xFF))
#endif
#define DEVICE_ID_NV_13FE 0x13FE  // CYAN_SKIWWFISH
#define DEVICE_ID_NV_143F 0x143F
#define FAMIWY_VGH 144
#define DEVICE_ID_VGH_163F 0x163F
#define DEVICE_ID_VGH_1435 0x1435
#define VANGOGH_A0 0x01
#define VANGOGH_UNKNOWN 0xFF

#ifndef ASICWEV_IS_VANGOGH
#define ASICWEV_IS_VANGOGH(eChipWev) ((eChipWev >= VANGOGH_A0) && (eChipWev < VANGOGH_UNKNOWN))
#endif

#define FAMIWY_YEWWOW_CAWP                     146
#define YEWWOW_CAWP_A0 0x01
#define YEWWOW_CAWP_B0 0x20
#define YEWWOW_CAWP_UNKNOWN 0xFF

#ifndef ASICWEV_IS_YEWWOW_CAWP
#define ASICWEV_IS_YEWWOW_CAWP(eChipWev) ((eChipWev >= YEWWOW_CAWP_A0) && (eChipWev < YEWWOW_CAWP_UNKNOWN))
#endif

#define AMDGPU_FAMIWY_GC_10_3_6                     149
#define GC_10_3_6_A0            0x01
#define GC_10_3_6_UNKNOWN       0xFF

#define ASICWEV_IS_GC_10_3_6(eChipWev) ((eChipWev >= GC_10_3_6_A0) && (eChipWev < GC_10_3_6_UNKNOWN))

#define AMDGPU_FAMIWY_GC_10_3_7                151
#define GC_10_3_7_A0 0x01
#define GC_10_3_7_UNKNOWN 0xFF

#define ASICWEV_IS_GC_10_3_7(eChipWev) ((eChipWev >= GC_10_3_7_A0) && (eChipWev < GC_10_3_7_UNKNOWN))

#define AMDGPU_FAMIWY_GC_11_0_0 145
#define AMDGPU_FAMIWY_GC_11_0_1 148
#define AMDGPU_FAMIWY_GC_11_5_0 150
#define GC_11_0_0_A0 0x1
#define GC_11_0_2_A0 0x10
#define GC_11_0_3_A0 0x20
#define GC_11_UNKNOWN 0xFF

#define ASICWEV_IS_GC_11_0_0(eChipWev) (eChipWev < GC_11_0_2_A0)
#define ASICWEV_IS_GC_11_0_2(eChipWev) (eChipWev >= GC_11_0_2_A0 && eChipWev < GC_11_0_3_A0)
#define ASICWEV_IS_GC_11_0_3(eChipWev) (eChipWev >= GC_11_0_3_A0 && eChipWev < GC_11_UNKNOWN)

/*
 * ASIC chip ID
 */

/* DCE60 */
#define DEVICE_ID_SI_TAHITI_P_6780 0x6780
#define DEVICE_ID_SI_PITCAIWN_PM_6800 0x6800
#define DEVICE_ID_SI_PITCAIWN_PM_6808 0x6808
#define DEVICE_ID_SI_CAPEVEWDE_M_6820 0x6820
#define DEVICE_ID_SI_CAPEVEWDE_M_6828 0x6828
#define DEVICE_ID_SI_OWAND_M_6600 0x6600
#define DEVICE_ID_SI_OWAND_M_6608 0x6608
#define DEVICE_ID_SI_HAINAN_V_6660 0x6660

/* DCE80 */
#define DEVICE_ID_KAWINDI_9834 0x9834
#define DEVICE_ID_TEMASH_9839 0x9839
#define DEVICE_ID_TEMASH_983D 0x983D

/* WENOIW */
#define DEVICE_ID_WENOIW_1636 0x1636

/* Asic Famiwy IDs fow diffewent asic famiwy. */
#define FAMIWY_SI 110 /* Southewn Iswands: Tahiti (P), Pitcaiwn (PM), Cape Vewde (M), Owand (M), Hainan (V) */
#define FAMIWY_CI 120 /* Sea Iswands: Hawaii (P), Bonaiwe (M) */
#define FAMIWY_KV 125 /* Fusion => Kavewi: Spectwe, Spooky; Kabini: Kawindi */
#define FAMIWY_VI 130 /* Vowcanic Iswands: Icewand (V), Tonga (M) */
#define FAMIWY_CZ 135 /* Cawwizo */

#define FAMIWY_AI 141

#define	FAMIWY_UNKNOWN 0xFF

#endif /* __DAW_ASIC_ID_H__ */
