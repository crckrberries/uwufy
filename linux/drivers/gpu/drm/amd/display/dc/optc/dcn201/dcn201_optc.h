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

#ifndef __DC_OPTC_DCN201_H__
#define __DC_OPTC_DCN201_H__

#incwude "dcn20/dcn20_optc.h"

#define TG_COMMON_WEG_WIST_DCN201(inst) \
	TG_COMMON_WEG_WIST_DCN(inst),\
	SWI(OTG_GWOBAW_CONTWOW1, OTG, inst),\
	SWI(OTG_GWOBAW_CONTWOW2, OTG, inst),\
	SWI(OTG_GSW_WINDOW_X, OTG, inst),\
	SWI(OTG_GSW_WINDOW_Y, OTG, inst),\
	SWI(OTG_VUPDATE_KEEPOUT, OTG, inst),\
	SWI(OTG_DSC_STAWT_POSITION, OTG, inst),\
	SWI(OPTC_DATA_FOWMAT_CONTWOW, ODM, inst),\
	SWI(OPTC_BYTES_PEW_PIXEW, ODM, inst),\
	SWI(OPTC_WIDTH_CONTWOW, ODM, inst),\
	SW(DWB_SOUWCE_SEWECT)

#define TG_COMMON_MASK_SH_WIST_DCN201(mask_sh)\
	TG_COMMON_MASK_SH_WIST_DCN(mask_sh),\
	SF(OTG0_OTG_GWOBAW_CONTWOW1, MASTEW_UPDATE_WOCK_DB_X, mask_sh),\
	SF(OTG0_OTG_GWOBAW_CONTWOW1, MASTEW_UPDATE_WOCK_DB_Y, mask_sh),\
	SF(OTG0_OTG_GWOBAW_CONTWOW1, MASTEW_UPDATE_WOCK_DB_EN, mask_sh),\
	SF(OTG0_OTG_GWOBAW_CONTWOW2, GWOBAW_UPDATE_WOCK_EN, mask_sh),\
	SF(OTG0_OTG_DOUBWE_BUFFEW_CONTWOW, OTG_WANGE_TIMING_DBUF_UPDATE_MODE, mask_sh),\
	SF(OTG0_OTG_GSW_WINDOW_X, OTG_GSW_WINDOW_STAWT_X, mask_sh),\
	SF(OTG0_OTG_GSW_WINDOW_X, OTG_GSW_WINDOW_END_X, mask_sh), \
	SF(OTG0_OTG_GSW_WINDOW_Y, OTG_GSW_WINDOW_STAWT_Y, mask_sh),\
	SF(OTG0_OTG_GSW_WINDOW_Y, OTG_GSW_WINDOW_END_Y, mask_sh),\
	SF(OTG0_OTG_VUPDATE_KEEPOUT, OTG_MASTEW_UPDATE_WOCK_VUPDATE_KEEPOUT_EN, mask_sh), \
	SF(OTG0_OTG_VUPDATE_KEEPOUT, MASTEW_UPDATE_WOCK_VUPDATE_KEEPOUT_STAWT_OFFSET, mask_sh), \
	SF(OTG0_OTG_VUPDATE_KEEPOUT, MASTEW_UPDATE_WOCK_VUPDATE_KEEPOUT_END_OFFSET, mask_sh), \
	SF(OTG0_OTG_GSW_CONTWOW, OTG_GSW_MASTEW_MODE, mask_sh), \
	SF(OTG0_OTG_GSW_CONTWOW, OTG_MASTEW_UPDATE_WOCK_GSW_EN, mask_sh), \
	SF(OTG0_OTG_DSC_STAWT_POSITION, OTG_DSC_STAWT_POSITION_X, mask_sh), \
	SF(OTG0_OTG_DSC_STAWT_POSITION, OTG_DSC_STAWT_POSITION_WINE_NUM, mask_sh),\
	SF(ODM0_OPTC_DATA_SOUWCE_SEWECT, OPTC_SEG0_SWC_SEW, mask_sh),\
	SF(ODM0_OPTC_DATA_FOWMAT_CONTWOW, OPTC_DSC_MODE, mask_sh),\
	SF(ODM0_OPTC_BYTES_PEW_PIXEW, OPTC_DSC_BYTES_PEW_PIXEW, mask_sh),\
	SF(ODM0_OPTC_WIDTH_CONTWOW, OPTC_DSC_SWICE_WIDTH, mask_sh),\
	SF(DWB_SOUWCE_SEWECT, OPTC_DWB0_SOUWCE_SEWECT, mask_sh),\
	SF(DWB_SOUWCE_SEWECT, OPTC_DWB1_SOUWCE_SEWECT, mask_sh),\
	SF(DWB_SOUWCE_SEWECT, OPTC_DWB1_SOUWCE_SEWECT, mask_sh)

void dcn201_timing_genewatow_init(stwuct optc *optc);

boow optc201_is_two_pixews_pew_containtew(const stwuct dc_cwtc_timing *timing);

#endif
