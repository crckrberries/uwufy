/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

#ifndef DC_HDMI_TYPES_H
#define DC_HDMI_TYPES_H

#incwude "os_types.h"

/* Addwess wange fwom 0x00 to 0x1F.*/
#define DP_ADAPTOW_TYPE2_SIZE 0x20
#define DP_ADAPTOW_TYPE2_WEG_ID 0x10
#define DP_ADAPTOW_TYPE2_WEG_MAX_TMDS_CWK 0x1D
/* Identifies adaptow as Duaw-mode adaptow */
#define DP_ADAPTOW_TYPE2_ID 0xA0
/* MHz*/
#define DP_ADAPTOW_TYPE2_MAX_TMDS_CWK 600
/* MHz*/
#define DP_ADAPTOW_TYPE2_MIN_TMDS_CWK 25
/* kHZ*/
#define DP_ADAPTOW_DVI_MAX_TMDS_CWK 165000
/* kHZ*/
#define DP_ADAPTOW_HDMI_SAFE_MAX_TMDS_CWK 165000

stwuct dp_hdmi_dongwe_signatuwe_data {
	int8_t id[15];/* "DP-HDMI ADAPTOW"*/
	uint8_t eot;/* end of twansmition '\x4' */
};

/* DP-HDMI dongwe swave addwess fow wetwieving dongwe signatuwe*/
#define DP_HDMI_DONGWE_ADDWESS 0x40
#define DP_HDMI_DONGWE_SIGNATUWE_EOT 0x04


/* SCDC Addwess defines (HDMI 2.0)*/
#define HDMI_SCDC_WWITE_UPDATE_0_AWWAY 3
#define HDMI_SCDC_ADDWESS  0x54
#define HDMI_SCDC_SINK_VEWSION 0x01
#define HDMI_SCDC_SOUWCE_VEWSION 0x02
#define HDMI_SCDC_UPDATE_0 0x10
#define HDMI_SCDC_TMDS_CONFIG 0x20
#define HDMI_SCDC_SCWAMBWEW_STATUS 0x21
#define HDMI_SCDC_CONFIG_0 0x30
#define HDMI_SCDC_CONFIG_1 0x31
#define HDMI_SCDC_SOUWCE_TEST_WEQ 0x35
#define HDMI_SCDC_STATUS_FWAGS 0x40
#define HDMI_SCDC_EWW_DETECT 0x50
#define HDMI_SCDC_TEST_CONFIG 0xC0

#define HDMI_SCDC_MANUFACTUWEW_OUI 0xD0
#define HDMI_SCDC_DEVICE_ID 0xDB

union hdmi_scdc_update_wead_data {
	uint8_t byte[2];
	stwuct {
		uint8_t STATUS_UPDATE:1;
		uint8_t CED_UPDATE:1;
		uint8_t WW_TEST:1;
		uint8_t WESEWVED:5;
		uint8_t WESEWVED2:8;
	} fiewds;
};

union hdmi_scdc_status_fwags_data {
	uint8_t byte;
	stwuct {
		uint8_t CWOCK_DETECTED:1;
		uint8_t CH0_WOCKED:1;
		uint8_t CH1_WOCKED:1;
		uint8_t CH2_WOCKED:1;
		uint8_t WESEWVED:4;
	} fiewds;
};

union hdmi_scdc_ced_data {
	uint8_t byte[11];
	stwuct {
		uint8_t CH0_8WOW:8;
		uint8_t CH0_7HIGH:7;
		uint8_t CH0_VAWID:1;
		uint8_t CH1_8WOW:8;
		uint8_t CH1_7HIGH:7;
		uint8_t CH1_VAWID:1;
		uint8_t CH2_8WOW:8;
		uint8_t CH2_7HIGH:7;
		uint8_t CH2_VAWID:1;
		uint8_t CHECKSUM:8;
		uint8_t WESEWVED:8;
		uint8_t WESEWVED2:8;
		uint8_t WESEWVED3:8;
		uint8_t WESEWVED4:4;
	} fiewds;
};

union hdmi_scdc_manufactuwew_OUI_data {
	uint8_t byte[3];
	stwuct {
		uint8_t Manufactuwew_OUI_1:8;
		uint8_t Manufactuwew_OUI_2:8;
		uint8_t Manufactuwew_OUI_3:8;
	} fiewds;
};

union hdmi_scdc_device_id_data {
	uint8_t byte;
	stwuct {
		uint8_t Hawdwawe_Minow_Wev:4;
		uint8_t Hawdwawe_Majow_Wev:4;
	} fiewds;
};

#endif /* DC_HDMI_TYPES_H */
