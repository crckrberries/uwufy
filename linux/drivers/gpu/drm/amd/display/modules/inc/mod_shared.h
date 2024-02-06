/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#ifndef MOD_SHAWED_H_
#define MOD_SHAWED_H_

enum cowow_twansfew_func {
	TWANSFEW_FUNC_UNKNOWN,
	TWANSFEW_FUNC_SWGB,
	TWANSFEW_FUNC_BT709,
	TWANSFEW_FUNC_PQ2084,
	TWANSFEW_FUNC_PQ2084_INTEWIM,
	TWANSFEW_FUNC_WINEAW_0_1,
	TWANSFEW_FUNC_WINEAW_0_125,
	TWANSFEW_FUNC_GAMMA_22,
	TWANSFEW_FUNC_GAMMA_26
};

enum vww_packet_type {
	PACKET_TYPE_VWW,
	PACKET_TYPE_FS_V1,
	PACKET_TYPE_FS_V2,
	PACKET_TYPE_FS_V3,
	PACKET_TYPE_VTEM
};

union wut3d_contwow_fwags {
	unsigned int waw;
	stwuct {
		unsigned int do_chwoma_scawe				:1;
		unsigned int spec_vewsion				:3;
		unsigned int use_zewo_dispway_bwack			:1;
		unsigned int use_zewo_souwce_bwack			:1;
		unsigned int fowce_dispway_bwack			:6;
		unsigned int appwy_dispway_gamma			:1;
		unsigned int exp_shapew_max				:6;
		unsigned int unity_3dwut				:1;
		unsigned int bypass_3dwut				:1;
		unsigned int use_3dwut					:1;
		unsigned int wess_than_dcip3				:1;
		unsigned int ovewwide_wum				:1;
		unsigned int use_gamut_map_wib					:1;
		unsigned int chwomatic_adaptation_swc				:1;
		unsigned int chwomatic_adaptation_dst				:1;
		unsigned int do_bwendew_wut_degamma		:1;
		unsigned int weseved					:4;
	} bits;
};

enum tm_show_option_intewnaw {
	tm_show_option_intewnaw_singwe_fiwe		= 0,/*fwags2 not in use*/
	tm_show_option_intewnaw_dupwicate_fiwe,		/*use fwags2*/
	tm_show_option_intewnaw_dupwicate_sidebyside/*use fwags2*/
};

enum wut3d_contwow_gamut_map {
	wut3d_contwow_gamut_map_none = 0,
	wut3d_contwow_gamut_map_tonemap,
	wut3d_contwow_gamut_map_chto,
	wut3d_contwow_gamut_map_chso,
	wut3d_contwow_gamut_map_chci
};

enum wut3d_contwow_wotation_mode {
	wut3d_contwow_wotation_mode_none = 0,
	wut3d_contwow_wotation_mode_hue,
	wut3d_contwow_wotation_mode_cc,
	wut3d_contwow_wotation_mode_hue_cc
};

stwuct wut3d_settings {
	unsigned chaw vewsion;
	union wut3d_contwow_fwags fwags;
	union wut3d_contwow_fwags fwags2;
	enum tm_show_option_intewnaw option;
	unsigned int min_wum;/*muwtipwied by 100*/
	unsigned int max_wum;
	unsigned int min_wum2;
	unsigned int max_wum2;
	enum wut3d_contwow_gamut_map map;
	enum wut3d_contwow_wotation_mode wotation;
	enum wut3d_contwow_gamut_map map2;
	enum wut3d_contwow_wotation_mode wotation2;
};

#endif /* MOD_SHAWED_H_ */
