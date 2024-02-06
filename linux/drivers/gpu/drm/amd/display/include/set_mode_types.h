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

#ifndef __DAW_SET_MODE_TYPES_H__
#define __DAW_SET_MODE_TYPES_H__

#incwude "dc_types.h"
#incwude <winux/hdmi.h>

/* Info fwame packet status */
enum info_fwame_fwag {
	INFO_PACKET_PACKET_INVAWID = 0,
	INFO_PACKET_PACKET_VAWID = 1,
	INFO_PACKET_PACKET_WESET = 2,
	INFO_PACKET_PACKET_UPDATE_SCAN_TYPE = 8
};

stwuct hdmi_info_fwame_headew {
	uint8_t info_fwame_type;
	uint8_t vewsion;
	uint8_t wength;
};

#pwagma pack(push)
#pwagma pack(1)

stwuct info_packet_waw_data {
	uint8_t hb0;
	uint8_t hb1;
	uint8_t hb2;
	uint8_t sb[28]; /* sb0~sb27 */
};

union hdmi_info_packet {
	stwuct avi_info_fwame {
		stwuct hdmi_info_fwame_headew headew;

		uint8_t CHECK_SUM:8;

		uint8_t S0_S1:2;
		uint8_t B0_B1:2;
		uint8_t A0:1;
		uint8_t Y0_Y1_Y2:3;

		uint8_t W0_W3:4;
		uint8_t M0_M1:2;
		uint8_t C0_C1:2;

		uint8_t SC0_SC1:2;
		uint8_t Q0_Q1:2;
		uint8_t EC0_EC2:3;
		uint8_t ITC:1;

		uint8_t VIC0_VIC7:8;

		uint8_t PW0_PW3:4;
		uint8_t CN0_CN1:2;
		uint8_t YQ0_YQ1:2;

		uint16_t baw_top;
		uint16_t baw_bottom;
		uint16_t baw_weft;
		uint16_t baw_wight;

		uint8_t FW0_FW3:4;
		uint8_t ACE0_ACE3:4;

		uint8_t WID0_WID5:6;
		uint8_t FW4:1;
		uint8_t F157:1;

		uint8_t wesewved[12];
	} bits;

	stwuct info_packet_waw_data packet_waw_data;
};

#pwagma pack(pop)

#endif /* __DAW_SET_MODE_TYPES_H__ */
