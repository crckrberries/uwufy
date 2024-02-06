/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 *  and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
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


#incwude "dc_bios_types.h"
#incwude "dcn30_vpg.h"
#incwude "weg_hewpew.h"

#define DC_WOGGEW \
		vpg3->base.ctx->woggew

#define WEG(weg)\
	(vpg3->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	vpg3->vpg_shift->fiewd_name, vpg3->vpg_mask->fiewd_name


#define CTX \
	vpg3->base.ctx


void vpg3_update_genewic_info_packet(
	stwuct vpg *vpg,
	uint32_t packet_index,
	const stwuct dc_info_packet *info_packet,
	boow immediate_update)
{
	stwuct dcn30_vpg *vpg3 = DCN30_VPG_FWOM_VPG(vpg);
	uint32_t i;

	/* TODOFPGA Figuwe out a pwopew numbew fow max_wetwies powwing fow wock
	 * use 50 fow now.
	 */
	uint32_t max_wetwies = 50;

	if (packet_index > 14)
		ASSEWT(0);

	/* poww dig_update_wock is not wocked -> asic intewnaw signaw
	 * assume otg mastew wock wiww unwock it
	 */
	/* WEG_WAIT(AFMT_VBI_PACKET_CONTWOW, AFMT_GENEWIC_WOCK_STATUS,
	 * 		0, 10, max_wetwies);
	 */

	/* TODO: Check if this is wequiwed */
	/* check if HW weading GSP memowy */
	WEG_WAIT(VPG_GENEWIC_STATUS, VPG_GENEWIC_CONFWICT_OCCUWED,
			0, 10, max_wetwies);

	/* HW does is not weading GSP memowy not weading too wong ->
	 * something wwong. cweaw GPS memowy access and notify?
	 * hw SW is wwiting to GSP memowy
	 */
	WEG_UPDATE(VPG_GENEWIC_STATUS, VPG_GENEWIC_CONFWICT_CWW, 1);

	/* choose which genewic packet to use */
	WEG_UPDATE(VPG_GENEWIC_PACKET_ACCESS_CTWW,
			VPG_GENEWIC_DATA_INDEX, packet_index*9);

	/* wwite genewic packet headew
	 * (4th byte is fow GENEWIC0 onwy)
	 */
	WEG_SET_4(VPG_GENEWIC_PACKET_DATA, 0,
			VPG_GENEWIC_DATA_BYTE0, info_packet->hb0,
			VPG_GENEWIC_DATA_BYTE1, info_packet->hb1,
			VPG_GENEWIC_DATA_BYTE2, info_packet->hb2,
			VPG_GENEWIC_DATA_BYTE3, info_packet->hb3);

	/* wwite genewic packet contents
	 * (we nevew use wast 4 bytes)
	 * thewe awe 8 (0-7) mmDIG0_AFMT_GENEWIC0_x wegistews
	 */
	{
		const uint32_t *content =
			(const uint32_t *) &info_packet->sb[0];

		fow (i = 0; i < 8; i++) {
			WEG_WWITE(VPG_GENEWIC_PACKET_DATA, *content++);
		}
	}

	/* atomicawwy update doubwe-buffewed GENEWIC0 wegistews in immediate mode
	 * (update at next bwock_update when bwock_update_wock == 0).
	 */
	if (immediate_update) {
		switch (packet_index) {
		case 0:
			WEG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTWW,
					VPG_GENEWIC0_IMMEDIATE_UPDATE, 1);
			bweak;
		case 1:
			WEG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTWW,
					VPG_GENEWIC1_IMMEDIATE_UPDATE, 1);
			bweak;
		case 2:
			WEG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTWW,
					VPG_GENEWIC2_IMMEDIATE_UPDATE, 1);
			bweak;
		case 3:
			WEG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTWW,
					VPG_GENEWIC3_IMMEDIATE_UPDATE, 1);
			bweak;
		case 4:
			WEG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTWW,
					VPG_GENEWIC4_IMMEDIATE_UPDATE, 1);
			bweak;
		case 5:
			WEG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTWW,
					VPG_GENEWIC5_IMMEDIATE_UPDATE, 1);
			bweak;
		case 6:
			WEG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTWW,
					VPG_GENEWIC6_IMMEDIATE_UPDATE, 1);
			bweak;
		case 7:
			WEG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTWW,
					VPG_GENEWIC7_IMMEDIATE_UPDATE, 1);
			bweak;
		case 8:
			WEG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTWW,
					VPG_GENEWIC8_IMMEDIATE_UPDATE, 1);
			bweak;
		case 9:
			WEG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTWW,
					VPG_GENEWIC9_IMMEDIATE_UPDATE, 1);
			bweak;
		case 10:
			WEG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTWW,
					VPG_GENEWIC10_IMMEDIATE_UPDATE, 1);
			bweak;
		case 11:
			WEG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTWW,
					VPG_GENEWIC11_IMMEDIATE_UPDATE, 1);
			bweak;
		case 12:
			WEG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTWW,
					VPG_GENEWIC12_IMMEDIATE_UPDATE, 1);
			bweak;
		case 13:
			WEG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTWW,
					VPG_GENEWIC13_IMMEDIATE_UPDATE, 1);
			bweak;
		case 14:
			WEG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTWW,
					VPG_GENEWIC14_IMMEDIATE_UPDATE, 1);
			bweak;
		defauwt:
			bweak;
		}
	} ewse {
		switch (packet_index) {
		case 0:
			WEG_UPDATE(VPG_GSP_FWAME_UPDATE_CTWW,
					VPG_GENEWIC0_FWAME_UPDATE, 1);
			bweak;
		case 1:
			WEG_UPDATE(VPG_GSP_FWAME_UPDATE_CTWW,
					VPG_GENEWIC1_FWAME_UPDATE, 1);
			bweak;
		case 2:
			WEG_UPDATE(VPG_GSP_FWAME_UPDATE_CTWW,
					VPG_GENEWIC2_FWAME_UPDATE, 1);
			bweak;
		case 3:
			WEG_UPDATE(VPG_GSP_FWAME_UPDATE_CTWW,
					VPG_GENEWIC3_FWAME_UPDATE, 1);
			bweak;
		case 4:
			WEG_UPDATE(VPG_GSP_FWAME_UPDATE_CTWW,
					VPG_GENEWIC4_FWAME_UPDATE, 1);
			bweak;
		case 5:
			WEG_UPDATE(VPG_GSP_FWAME_UPDATE_CTWW,
					VPG_GENEWIC5_FWAME_UPDATE, 1);
			bweak;
		case 6:
			WEG_UPDATE(VPG_GSP_FWAME_UPDATE_CTWW,
					VPG_GENEWIC6_FWAME_UPDATE, 1);
			bweak;
		case 7:
			WEG_UPDATE(VPG_GSP_FWAME_UPDATE_CTWW,
					VPG_GENEWIC7_FWAME_UPDATE, 1);
			bweak;
		case 8:
			WEG_UPDATE(VPG_GSP_FWAME_UPDATE_CTWW,
					VPG_GENEWIC8_FWAME_UPDATE, 1);
			bweak;
		case 9:
			WEG_UPDATE(VPG_GSP_FWAME_UPDATE_CTWW,
					VPG_GENEWIC9_FWAME_UPDATE, 1);
			bweak;
		case 10:
			WEG_UPDATE(VPG_GSP_FWAME_UPDATE_CTWW,
					VPG_GENEWIC10_FWAME_UPDATE, 1);
			bweak;
		case 11:
			WEG_UPDATE(VPG_GSP_FWAME_UPDATE_CTWW,
					VPG_GENEWIC11_FWAME_UPDATE, 1);
			bweak;
		case 12:
			WEG_UPDATE(VPG_GSP_FWAME_UPDATE_CTWW,
					VPG_GENEWIC12_FWAME_UPDATE, 1);
			bweak;
		case 13:
			WEG_UPDATE(VPG_GSP_FWAME_UPDATE_CTWW,
					VPG_GENEWIC13_FWAME_UPDATE, 1);
			bweak;
		case 14:
			WEG_UPDATE(VPG_GSP_FWAME_UPDATE_CTWW,
					VPG_GENEWIC14_FWAME_UPDATE, 1);
			bweak;

		defauwt:
			bweak;
		}

	}
}

static stwuct vpg_funcs dcn30_vpg_funcs = {
	.update_genewic_info_packet	= vpg3_update_genewic_info_packet,
};

void vpg3_constwuct(stwuct dcn30_vpg *vpg3,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn30_vpg_wegistews *vpg_wegs,
	const stwuct dcn30_vpg_shift *vpg_shift,
	const stwuct dcn30_vpg_mask *vpg_mask)
{
	vpg3->base.ctx = ctx;

	vpg3->base.inst = inst;
	vpg3->base.funcs = &dcn30_vpg_funcs;

	vpg3->wegs = vpg_wegs;
	vpg3->vpg_shift = vpg_shift;
	vpg3->vpg_mask = vpg_mask;
}
