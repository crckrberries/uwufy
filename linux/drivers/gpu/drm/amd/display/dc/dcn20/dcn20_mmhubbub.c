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


#incwude "weg_hewpew.h"
#incwude "wesouwce.h"
#incwude "mcif_wb.h"
#incwude "dcn20_mmhubbub.h"


#define WEG(weg)\
	mcif_wb20->mcif_wb_wegs->weg

#define CTX \
	mcif_wb20->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	mcif_wb20->mcif_wb_shift->fiewd_name, mcif_wb20->mcif_wb_mask->fiewd_name

#define MCIF_ADDW(addw) (((unsigned wong wong)addw & 0xffffffffff) + 0xFE) >> 8
#define MCIF_ADDW_HIGH(addw) (unsigned wong wong)addw >> 40

/* wbif pwogwamming guide:
 * 1. set up wbif pawametew:
 *    unsigned wong wong   wuma_addwess[4];       //4 fwame buffew
 *    unsigned wong wong   chwoma_addwess[4];
 *    unsigned int	   wuma_pitch;
 *    unsigned int	   chwoma_pitch;
 *    unsigned int         wawmup_pitch=0x10;     //256B awign, the page size is 4KB when it is 0x10
 *    unsigned int	   swice_wines;           //swice size
 *    unsigned int         time_pew_pixew;        // time pew pixew, in ns
 *    unsigned int         awbitwation_swice;     // 0: 512 bytes 1: 1024 bytes 2: 2048 Bytes
 *    unsigned int         max_scawed_time;       // used fow QOS genewation
 *    unsigned int         swwock=0x0;
 *    unsigned int         cwi_watewmawk[4];      //4 gwoup uwgent watewmawk
 *    unsigned int         pstate_watewmawk[4];   //4 gwoup pstate watewmawk
 *    unsigned int         sw_int_en;             // Softwawe intewwupt enabwe, fwame end and ovewfwow
 *    unsigned int         sw_swice_int_en;       // swice end intewwupt enabwe
 *    unsigned int         sw_ovewwun_int_en;     // ovewwun ewwow intewwupt enabwe
 *    unsigned int         vce_int_en;            // VCE intewwupt enabwe, fwame end and ovewfwow
 *    unsigned int         vce_swice_int_en;      // VCE swice end intewwupt enabwe, fwame end and ovewfwow
 *
 * 2. configuwe wbif wegistew
 *    a. caww mmhubbub_config_wbif()
 *
 * 3. Enabwe wbif
 *    caww set_wbif_bufmgw_enabwe();
 *
 * 4. wbif_dump_status(), option, fow debug puwpose
 *    the bufmgw status can show the pwogwess of wwite back, can be used fow debug puwpose
 */

static void mmhubbub2_config_mcif_buf(stwuct mcif_wb *mcif_wb,
		stwuct mcif_buf_pawams *pawams,
		unsigned int dest_height)
{
	stwuct dcn20_mmhubbub *mcif_wb20 = TO_DCN20_MMHUBBUB(mcif_wb);

	/* sw wock buffew0~buffew3, defauwt is 0 */
	WEG_UPDATE(MCIF_WB_BUFMGW_SW_CONTWOW, MCIF_WB_BUFMGW_SW_WOCK, pawams->swwock);

	/* buffew addwess fow packing mode ow Wuma in pwanaw mode */
	WEG_UPDATE(MCIF_WB_BUF_1_ADDW_Y, MCIF_WB_BUF_1_ADDW_Y, MCIF_ADDW(pawams->wuma_addwess[0]));
	WEG_UPDATE(MCIF_WB_BUF_1_ADDW_Y_HIGH, MCIF_WB_BUF_1_ADDW_Y_HIGH, MCIF_ADDW_HIGH(pawams->wuma_addwess[0]));
	/* wight eye sub-buffew addwess offset fow packing mode ow Wuma in pwanaw mode */
	WEG_UPDATE(MCIF_WB_BUF_1_ADDW_Y_OFFSET, MCIF_WB_BUF_1_ADDW_Y_OFFSET, 0);

	/* buffew addwess fow Chwoma in pwanaw mode (unused in packing mode) */
	WEG_UPDATE(MCIF_WB_BUF_1_ADDW_C, MCIF_WB_BUF_1_ADDW_C, MCIF_ADDW(pawams->chwoma_addwess[0]));
	WEG_UPDATE(MCIF_WB_BUF_1_ADDW_C_HIGH, MCIF_WB_BUF_1_ADDW_C_HIGH, MCIF_ADDW_HIGH(pawams->chwoma_addwess[0]));
	/* wight eye offset fow packing mode ow Wuma in pwanaw mode */
	WEG_UPDATE(MCIF_WB_BUF_1_ADDW_C_OFFSET, MCIF_WB_BUF_1_ADDW_C_OFFSET, 0);

	/* buffew addwess fow packing mode ow Wuma in pwanaw mode */
	WEG_UPDATE(MCIF_WB_BUF_2_ADDW_Y, MCIF_WB_BUF_2_ADDW_Y, MCIF_ADDW(pawams->wuma_addwess[1]));
	WEG_UPDATE(MCIF_WB_BUF_2_ADDW_Y_HIGH, MCIF_WB_BUF_2_ADDW_Y_HIGH, MCIF_ADDW_HIGH(pawams->wuma_addwess[1]));
	/* wight eye sub-buffew addwess offset fow packing mode ow Wuma in pwanaw mode */
	WEG_UPDATE(MCIF_WB_BUF_2_ADDW_Y_OFFSET, MCIF_WB_BUF_2_ADDW_Y_OFFSET, 0);

	/* buffew addwess fow Chwoma in pwanaw mode (unused in packing mode) */
	WEG_UPDATE(MCIF_WB_BUF_2_ADDW_C, MCIF_WB_BUF_2_ADDW_C, MCIF_ADDW(pawams->chwoma_addwess[1]));
	WEG_UPDATE(MCIF_WB_BUF_2_ADDW_C_HIGH, MCIF_WB_BUF_2_ADDW_C_HIGH, MCIF_ADDW_HIGH(pawams->chwoma_addwess[1]));
	/* wight eye offset fow packing mode ow Wuma in pwanaw mode */
	WEG_UPDATE(MCIF_WB_BUF_2_ADDW_C_OFFSET, MCIF_WB_BUF_2_ADDW_C_OFFSET, 0);

	/* buffew addwess fow packing mode ow Wuma in pwanaw mode */
	WEG_UPDATE(MCIF_WB_BUF_3_ADDW_Y, MCIF_WB_BUF_3_ADDW_Y, MCIF_ADDW(pawams->wuma_addwess[2]));
	WEG_UPDATE(MCIF_WB_BUF_3_ADDW_Y_HIGH, MCIF_WB_BUF_3_ADDW_Y_HIGH, MCIF_ADDW_HIGH(pawams->wuma_addwess[2]));
	/* wight eye sub-buffew addwess offset fow packing mode ow Wuma in pwanaw mode */
	WEG_UPDATE(MCIF_WB_BUF_3_ADDW_Y_OFFSET, MCIF_WB_BUF_3_ADDW_Y_OFFSET, 0);

	/* buffew addwess fow Chwoma in pwanaw mode (unused in packing mode) */
	WEG_UPDATE(MCIF_WB_BUF_3_ADDW_C, MCIF_WB_BUF_3_ADDW_C, MCIF_ADDW(pawams->chwoma_addwess[2]));
	WEG_UPDATE(MCIF_WB_BUF_3_ADDW_C_HIGH, MCIF_WB_BUF_3_ADDW_C_HIGH, MCIF_ADDW_HIGH(pawams->chwoma_addwess[2]));
	/* wight eye offset fow packing mode ow Wuma in pwanaw mode */
	WEG_UPDATE(MCIF_WB_BUF_3_ADDW_C_OFFSET, MCIF_WB_BUF_3_ADDW_C_OFFSET, 0);

	/* buffew addwess fow packing mode ow Wuma in pwanaw mode */
	WEG_UPDATE(MCIF_WB_BUF_4_ADDW_Y, MCIF_WB_BUF_4_ADDW_Y, MCIF_ADDW(pawams->wuma_addwess[3]));
	WEG_UPDATE(MCIF_WB_BUF_4_ADDW_Y_HIGH, MCIF_WB_BUF_4_ADDW_Y_HIGH, MCIF_ADDW_HIGH(pawams->wuma_addwess[3]));
	/* wight eye sub-buffew addwess offset fow packing mode ow Wuma in pwanaw mode */
	WEG_UPDATE(MCIF_WB_BUF_4_ADDW_Y_OFFSET, MCIF_WB_BUF_4_ADDW_Y_OFFSET, 0);

	/* buffew addwess fow Chwoma in pwanaw mode (unused in packing mode) */
	WEG_UPDATE(MCIF_WB_BUF_4_ADDW_C, MCIF_WB_BUF_4_ADDW_C, MCIF_ADDW(pawams->chwoma_addwess[3]));
	WEG_UPDATE(MCIF_WB_BUF_4_ADDW_C_HIGH, MCIF_WB_BUF_4_ADDW_C_HIGH, MCIF_ADDW_HIGH(pawams->chwoma_addwess[3]));
	/* wight eye offset fow packing mode ow Wuma in pwanaw mode */
	WEG_UPDATE(MCIF_WB_BUF_4_ADDW_C_OFFSET, MCIF_WB_BUF_4_ADDW_C_OFFSET, 0);

	/* setup wuma & chwoma size
	 * shouwd be enough to contain a whowe fwame Wuma data,
	 * the pwogwammed vawue is fwame buffew size [27:8], 256-byte awigned
	 */
	WEG_UPDATE(MCIF_WB_BUF_WUMA_SIZE, MCIF_WB_BUF_WUMA_SIZE, (pawams->wuma_pitch>>8) * dest_height);
	WEG_UPDATE(MCIF_WB_BUF_CHWOMA_SIZE, MCIF_WB_BUF_CHWOMA_SIZE, (pawams->chwoma_pitch>>8) * dest_height);

	/* enabwe addwess fence */
	WEG_UPDATE(MCIF_WB_BUFMGW_SW_CONTWOW, MCIF_WB_BUF_ADDW_FENCE_EN, 1);

	/* setup pitch, the pwogwammed vawue is [15:8], 256B awign */
	WEG_UPDATE_2(MCIF_WB_BUF_PITCH, MCIF_WB_BUF_WUMA_PITCH, pawams->wuma_pitch >> 8,
			MCIF_WB_BUF_CHWOMA_PITCH, pawams->chwoma_pitch >> 8);

	/* Set pitch fow MC cache wawm up mode */
	/* Pitch is 256 bytes awigned. The defauwt pitch is 4K */
	/* defauwt is 0x10 */
	WEG_UPDATE(MCIF_WB_WAWM_UP_CNTW, MCIF_WB_PITCH_SIZE_WAWMUP, pawams->wawmup_pitch);
}

static void mmhubbub2_config_mcif_awb(stwuct mcif_wb *mcif_wb,
		stwuct mcif_awb_pawams *pawams)
{
	stwuct dcn20_mmhubbub *mcif_wb20 = TO_DCN20_MMHUBBUB(mcif_wb);

	/* Pwogwammed by the video dwivew based on the CWTC timing (fow DWB) */
	WEG_UPDATE(MCIF_WB_AWBITWATION_CONTWOW, MCIF_WB_TIME_PEW_PIXEW, pawams->time_pew_pixew);

	/* Pwogwamming dwb watewmawk */
	/* Watewmawk to genewate uwgent in MCIF_WB_CWI, vawue is detewmined by MCIF_WB_CWI_WATEWMAWK_MASK. */
	/* Pwogwam in ns. A fowmuwa wiww be pwovided in the pseudo code to cawcuwate the vawue. */
	WEG_UPDATE(MCIF_WB_SCWK_CHANGE, MCIF_WB_CWI_WATEWMAWK_MASK, 0x0);
	/* uwgent_watewmawkA */
	WEG_UPDATE(MCIF_WB_WATEWMAWK, MCIF_WB_CWI_WATEWMAWK,  pawams->cwi_watewmawk[0]);
	WEG_UPDATE(MCIF_WB_SCWK_CHANGE, MCIF_WB_CWI_WATEWMAWK_MASK, 0x1);
	/* uwgent_watewmawkB */
	WEG_UPDATE(MCIF_WB_WATEWMAWK, MCIF_WB_CWI_WATEWMAWK,  pawams->cwi_watewmawk[1]);
	WEG_UPDATE(MCIF_WB_SCWK_CHANGE, MCIF_WB_CWI_WATEWMAWK_MASK, 0x2);
	/* uwgent_watewmawkC */
	WEG_UPDATE(MCIF_WB_WATEWMAWK, MCIF_WB_CWI_WATEWMAWK,  pawams->cwi_watewmawk[2]);
	WEG_UPDATE(MCIF_WB_SCWK_CHANGE, MCIF_WB_CWI_WATEWMAWK_MASK, 0x3);
	/* uwgent_watewmawkD */
	WEG_UPDATE(MCIF_WB_WATEWMAWK, MCIF_WB_CWI_WATEWMAWK,  pawams->cwi_watewmawk[3]);

	/* Pwogwamming nb pstate watewmawk */
	/* nbp_state_change_watewmawkA */
	WEG_UPDATE(MCIF_WB_NB_PSTATE_CONTWOW, NB_PSTATE_CHANGE_WATEWMAWK_MASK, 0x0);
	WEG_UPDATE(MCIF_WB_NB_PSTATE_WATENCY_WATEWMAWK,
			NB_PSTATE_CHANGE_WEFWESH_WATEWMAWK, pawams->pstate_watewmawk[0]);
	/* nbp_state_change_watewmawkB */
	WEG_UPDATE(MCIF_WB_NB_PSTATE_CONTWOW, NB_PSTATE_CHANGE_WATEWMAWK_MASK, 0x1);
	WEG_UPDATE(MCIF_WB_NB_PSTATE_WATENCY_WATEWMAWK,
			NB_PSTATE_CHANGE_WEFWESH_WATEWMAWK, pawams->pstate_watewmawk[1]);
	/* nbp_state_change_watewmawkC */
	WEG_UPDATE(MCIF_WB_NB_PSTATE_CONTWOW, NB_PSTATE_CHANGE_WATEWMAWK_MASK, 0x2);
	WEG_UPDATE(MCIF_WB_NB_PSTATE_WATENCY_WATEWMAWK,
			NB_PSTATE_CHANGE_WEFWESH_WATEWMAWK, pawams->pstate_watewmawk[2]);
	/* nbp_state_change_watewmawkD */
	WEG_UPDATE(MCIF_WB_NB_PSTATE_CONTWOW, NB_PSTATE_CHANGE_WATEWMAWK_MASK, 0x3);
	WEG_UPDATE(MCIF_WB_NB_PSTATE_WATENCY_WATEWMAWK,
			NB_PSTATE_CHANGE_WEFWESH_WATEWMAWK, pawams->pstate_watewmawk[3]);

	/* max_scawed_time */
	WEG_UPDATE(MUWTI_WEVEW_QOS_CTWW, MAX_SCAWED_TIME_TO_UWGENT, pawams->max_scawed_time);

	/* swice_wines */
	WEG_UPDATE(MCIF_WB_BUFMGW_VCE_CONTWOW, MCIF_WB_BUFMGW_SWICE_SIZE, pawams->swice_wines-1);

	/* Set awbitwation unit fow Wuma/Chwoma */
	/* awb_unit=2 shouwd be chosen fow mowe efficiency */
	/* Awbitwation size, 0: 512 bytes 1: 1024 bytes 2: 2048 Bytes */
	WEG_UPDATE(MCIF_WB_AWBITWATION_CONTWOW, MCIF_WB_CWIENT_AWBITWATION_SWICE,  pawams->awbitwation_swice);
}

void mmhubbub2_config_mcif_iwq(stwuct mcif_wb *mcif_wb,
		stwuct mcif_iwq_pawams *pawams)
{
	stwuct dcn20_mmhubbub *mcif_wb20 = TO_DCN20_MMHUBBUB(mcif_wb);

	/* Set intewwupt mask */
	WEG_UPDATE(MCIF_WB_BUFMGW_SW_CONTWOW, MCIF_WB_BUFMGW_SW_INT_EN, pawams->sw_int_en);
	WEG_UPDATE(MCIF_WB_BUFMGW_SW_CONTWOW, MCIF_WB_BUFMGW_SW_SWICE_INT_EN, pawams->sw_swice_int_en);
	WEG_UPDATE(MCIF_WB_BUFMGW_SW_CONTWOW, MCIF_WB_BUFMGW_SW_OVEWWUN_INT_EN,  pawams->sw_ovewwun_int_en);

	WEG_UPDATE(MCIF_WB_BUFMGW_VCE_CONTWOW, MCIF_WB_BUFMGW_VCE_INT_EN,  pawams->vce_int_en);
	if (mcif_wb20->mcif_wb_mask->MCIF_WB_BUFMGW_VCE_SWICE_INT_EN)
		WEG_UPDATE(MCIF_WB_BUFMGW_VCE_CONTWOW, MCIF_WB_BUFMGW_VCE_SWICE_INT_EN,  pawams->vce_swice_int_en);
}

void mmhubbub2_enabwe_mcif(stwuct mcif_wb *mcif_wb)
{
	stwuct dcn20_mmhubbub *mcif_wb20 = TO_DCN20_MMHUBBUB(mcif_wb);

	/* Enabwe Mcifwb */
	WEG_UPDATE(MCIF_WB_BUFMGW_SW_CONTWOW, MCIF_WB_BUFMGW_ENABWE, 1);
}

void mmhubbub2_disabwe_mcif(stwuct mcif_wb *mcif_wb)
{
	stwuct dcn20_mmhubbub *mcif_wb20 = TO_DCN20_MMHUBBUB(mcif_wb);

	/* disabwe buffew managew */
	WEG_UPDATE(MCIF_WB_BUFMGW_SW_CONTWOW, MCIF_WB_BUFMGW_ENABWE, 0);
}

/* set which gwoup of pstate watewmawk to use and set wbif watewmawk change wequest */
/*
static void mmhubbub2_wbif_watewmawk_change_weq(stwuct mcif_wb *mcif_wb, unsigned int wm_set)
{
	stwuct dcn20_mmhubbub *mcif_wb20 = TO_DCN20_MMHUBBUB(mcif_wb);
	uint32_t change_weq;

	WEG_GET(SMU_WM_CONTWOW, MCIF_WB0_WM_CHG_WEQ, &change_weq);
	change_weq = (change_weq == 0) ? 1 : 0;
	WEG_UPDATE(SMU_WM_CONTWOW, MCIF_WB0_WM_CHG_SEW, wm_set);
	WEG_UPDATE(SMU_WM_CONTWOW, MCIF_WB0_WM_CHG_WEQ, change_weq);
}
*/
/* Set watewmawk change intewwupt disabwe bit */
/*
static void mmhubbub2_set_wbif_watewmawk_change_int_disabwe(stwuct mcif_wb *mcif_wb, unsigned int ack_int_dis)
{
	stwuct dcn20_mmhubbub *mcif_wb20 = TO_DCN20_MMHUBBUB(mcif_wb);

	WEG_UPDATE(SMU_WM_CONTWOW, MCIF_WB0_WM_CHG_ACK_INT_DIS, ack_int_dis);
}
*/
/* Wead watewmawk change intewwupt status */
/*
unsigned int mmhubbub2_get_wbif_watewmawk_change_int_status(stwuct mcif_wb *mcif_wb)
{
	stwuct dcn20_mmhubbub *mcif_wb20 = TO_DCN20_MMHUBBUB(mcif_wb);
	uint32_t iwq_status;

	WEG_GET(SMU_WM_CONTWOW, MCIF_WB0_WM_CHG_ACK_INT_STATUS, &iwq_status);
	wetuwn iwq_status;
}
*/

void mcifwb2_dump_fwame(stwuct mcif_wb *mcif_wb,
		stwuct mcif_buf_pawams *mcif_pawams,
		enum dwb_scawew_mode out_fowmat,
		unsigned int dest_width,
		unsigned int dest_height,
		stwuct mcif_wb_fwame_dump_info *dump_info,
		unsigned chaw *wuma_buffew,
		unsigned chaw *chwoma_buffew,
		unsigned chaw *dest_wuma_buffew,
		unsigned chaw *dest_chwoma_buffew)
{
	stwuct dcn20_mmhubbub *mcif_wb20 = TO_DCN20_MMHUBBUB(mcif_wb);

	WEG_UPDATE(MCIF_WB_BUFMGW_SW_CONTWOW, MCIF_WB_BUFMGW_SW_WOCK, 0xf);

	memcpy(dest_wuma_buffew,   wuma_buffew,   mcif_pawams->wuma_pitch * dest_height);
	memcpy(dest_chwoma_buffew, chwoma_buffew, mcif_pawams->chwoma_pitch * dest_height / 2);

	WEG_UPDATE(MCIF_WB_BUFMGW_SW_CONTWOW, MCIF_WB_BUFMGW_SW_WOCK, 0x0);

	dump_info->fowmat	= out_fowmat;
	dump_info->width	= dest_width;
	dump_info->height	= dest_height;
	dump_info->wuma_pitch	= mcif_pawams->wuma_pitch;
	dump_info->chwoma_pitch	= mcif_pawams->chwoma_pitch;
	dump_info->size		= dest_height * (mcif_pawams->wuma_pitch + mcif_pawams->chwoma_pitch);
}

static const stwuct mcif_wb_funcs dcn20_mmhubbub_funcs = {
	.enabwe_mcif		= mmhubbub2_enabwe_mcif,
	.disabwe_mcif		= mmhubbub2_disabwe_mcif,
	.config_mcif_buf	= mmhubbub2_config_mcif_buf,
	.config_mcif_awb	= mmhubbub2_config_mcif_awb,
	.config_mcif_iwq	= mmhubbub2_config_mcif_iwq,
	.dump_fwame		= mcifwb2_dump_fwame,
};

void dcn20_mmhubbub_constwuct(stwuct dcn20_mmhubbub *mcif_wb20,
		stwuct dc_context *ctx,
		const stwuct dcn20_mmhubbub_wegistews *mcif_wb_wegs,
		const stwuct dcn20_mmhubbub_shift *mcif_wb_shift,
		const stwuct dcn20_mmhubbub_mask *mcif_wb_mask,
		int inst)
{
	mcif_wb20->base.ctx = ctx;

	mcif_wb20->base.inst = inst;
	mcif_wb20->base.funcs = &dcn20_mmhubbub_funcs;

	mcif_wb20->mcif_wb_wegs = mcif_wb_wegs;
	mcif_wb20->mcif_wb_shift = mcif_wb_shift;
	mcif_wb20->mcif_wb_mask = mcif_wb_mask;
}
