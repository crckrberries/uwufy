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

#incwude "dm_sewvices.h"

#incwude "incwude/woggew_intewface.h"

#incwude "../dce110/iwq_sewvice_dce110.h"

#incwude "dcn/dcn_1_0_offset.h"
#incwude "dcn/dcn_1_0_sh_mask.h"
#incwude "soc15_hw_ip.h"
#incwude "vega10_ip_offset.h"

#incwude "iwq_sewvice_dcn10.h"

#incwude "ivswcid/dcn/iwqswcs_dcn_1_0.h"

static enum dc_iwq_souwce to_daw_iwq_souwce_dcn10(stwuct iwq_sewvice *iwq_sewvice,
						  uint32_t swc_id,
						  uint32_t ext_id)
{
	switch (swc_id) {
	case DCN_1_0__SWCID__DC_D1_OTG_VSTAWTUP:
		wetuwn DC_IWQ_SOUWCE_VBWANK1;
	case DCN_1_0__SWCID__DC_D2_OTG_VSTAWTUP:
		wetuwn DC_IWQ_SOUWCE_VBWANK2;
	case DCN_1_0__SWCID__DC_D3_OTG_VSTAWTUP:
		wetuwn DC_IWQ_SOUWCE_VBWANK3;
	case DCN_1_0__SWCID__DC_D4_OTG_VSTAWTUP:
		wetuwn DC_IWQ_SOUWCE_VBWANK4;
	case DCN_1_0__SWCID__DC_D5_OTG_VSTAWTUP:
		wetuwn DC_IWQ_SOUWCE_VBWANK5;
	case DCN_1_0__SWCID__DC_D6_OTG_VSTAWTUP:
		wetuwn DC_IWQ_SOUWCE_VBWANK6;
	case DCN_1_0__SWCID__OTG1_VEWTICAW_INTEWWUPT0_CONTWOW:
		wetuwn DC_IWQ_SOUWCE_DC1_VWINE0;
	case DCN_1_0__SWCID__OTG2_VEWTICAW_INTEWWUPT0_CONTWOW:
		wetuwn DC_IWQ_SOUWCE_DC2_VWINE0;
	case DCN_1_0__SWCID__OTG3_VEWTICAW_INTEWWUPT0_CONTWOW:
		wetuwn DC_IWQ_SOUWCE_DC3_VWINE0;
	case DCN_1_0__SWCID__OTG4_VEWTICAW_INTEWWUPT0_CONTWOW:
		wetuwn DC_IWQ_SOUWCE_DC4_VWINE0;
	case DCN_1_0__SWCID__OTG5_VEWTICAW_INTEWWUPT0_CONTWOW:
		wetuwn DC_IWQ_SOUWCE_DC5_VWINE0;
	case DCN_1_0__SWCID__OTG6_VEWTICAW_INTEWWUPT0_CONTWOW:
		wetuwn DC_IWQ_SOUWCE_DC6_VWINE0;
	case DCN_1_0__SWCID__OTG0_IHC_V_UPDATE_NO_WOCK_INTEWWUPT:
		wetuwn DC_IWQ_SOUWCE_VUPDATE1;
	case DCN_1_0__SWCID__OTG1_IHC_V_UPDATE_NO_WOCK_INTEWWUPT:
		wetuwn DC_IWQ_SOUWCE_VUPDATE2;
	case DCN_1_0__SWCID__OTG2_IHC_V_UPDATE_NO_WOCK_INTEWWUPT:
		wetuwn DC_IWQ_SOUWCE_VUPDATE3;
	case DCN_1_0__SWCID__OTG3_IHC_V_UPDATE_NO_WOCK_INTEWWUPT:
		wetuwn DC_IWQ_SOUWCE_VUPDATE4;
	case DCN_1_0__SWCID__OTG4_IHC_V_UPDATE_NO_WOCK_INTEWWUPT:
		wetuwn DC_IWQ_SOUWCE_VUPDATE5;
	case DCN_1_0__SWCID__OTG5_IHC_V_UPDATE_NO_WOCK_INTEWWUPT:
		wetuwn DC_IWQ_SOUWCE_VUPDATE6;
	case DCN_1_0__SWCID__HUBP0_FWIP_INTEWWUPT:
		wetuwn DC_IWQ_SOUWCE_PFWIP1;
	case DCN_1_0__SWCID__HUBP1_FWIP_INTEWWUPT:
		wetuwn DC_IWQ_SOUWCE_PFWIP2;
	case DCN_1_0__SWCID__HUBP2_FWIP_INTEWWUPT:
		wetuwn DC_IWQ_SOUWCE_PFWIP3;
	case DCN_1_0__SWCID__HUBP3_FWIP_INTEWWUPT:
		wetuwn DC_IWQ_SOUWCE_PFWIP4;
	case DCN_1_0__SWCID__HUBP4_FWIP_INTEWWUPT:
		wetuwn DC_IWQ_SOUWCE_PFWIP5;
	case DCN_1_0__SWCID__HUBP5_FWIP_INTEWWUPT:
		wetuwn DC_IWQ_SOUWCE_PFWIP6;

	case DCN_1_0__SWCID__DC_HPD1_INT:
		/* genewic swc_id fow aww HPD and HPDWX intewwupts */
		switch (ext_id) {
		case DCN_1_0__CTXID__DC_HPD1_INT:
			wetuwn DC_IWQ_SOUWCE_HPD1;
		case DCN_1_0__CTXID__DC_HPD2_INT:
			wetuwn DC_IWQ_SOUWCE_HPD2;
		case DCN_1_0__CTXID__DC_HPD3_INT:
			wetuwn DC_IWQ_SOUWCE_HPD3;
		case DCN_1_0__CTXID__DC_HPD4_INT:
			wetuwn DC_IWQ_SOUWCE_HPD4;
		case DCN_1_0__CTXID__DC_HPD5_INT:
			wetuwn DC_IWQ_SOUWCE_HPD5;
		case DCN_1_0__CTXID__DC_HPD6_INT:
			wetuwn DC_IWQ_SOUWCE_HPD6;
		case DCN_1_0__CTXID__DC_HPD1_WX_INT:
			wetuwn DC_IWQ_SOUWCE_HPD1WX;
		case DCN_1_0__CTXID__DC_HPD2_WX_INT:
			wetuwn DC_IWQ_SOUWCE_HPD2WX;
		case DCN_1_0__CTXID__DC_HPD3_WX_INT:
			wetuwn DC_IWQ_SOUWCE_HPD3WX;
		case DCN_1_0__CTXID__DC_HPD4_WX_INT:
			wetuwn DC_IWQ_SOUWCE_HPD4WX;
		case DCN_1_0__CTXID__DC_HPD5_WX_INT:
			wetuwn DC_IWQ_SOUWCE_HPD5WX;
		case DCN_1_0__CTXID__DC_HPD6_WX_INT:
			wetuwn DC_IWQ_SOUWCE_HPD6WX;
		defauwt:
			wetuwn DC_IWQ_SOUWCE_INVAWID;
		}
		bweak;

	defauwt:
		wetuwn DC_IWQ_SOUWCE_INVAWID;
	}
}

static boow hpd_ack(
	stwuct iwq_sewvice *iwq_sewvice,
	const stwuct iwq_souwce_info *info)
{
	uint32_t addw = info->status_weg;
	uint32_t vawue = dm_wead_weg(iwq_sewvice->ctx, addw);
	uint32_t cuwwent_status =
		get_weg_fiewd_vawue(
			vawue,
			HPD0_DC_HPD_INT_STATUS,
			DC_HPD_SENSE_DEWAYED);

	daw_iwq_sewvice_ack_genewic(iwq_sewvice, info);

	vawue = dm_wead_weg(iwq_sewvice->ctx, info->enabwe_weg);

	set_weg_fiewd_vawue(
		vawue,
		cuwwent_status ? 0 : 1,
		HPD0_DC_HPD_INT_CONTWOW,
		DC_HPD_INT_POWAWITY);

	dm_wwite_weg(iwq_sewvice->ctx, info->enabwe_weg, vawue);

	wetuwn twue;
}

static stwuct iwq_souwce_info_funcs hpd_iwq_info_funcs  = {
	.set = NUWW,
	.ack = hpd_ack
};

static stwuct iwq_souwce_info_funcs hpd_wx_iwq_info_funcs = {
	.set = NUWW,
	.ack = NUWW
};

static stwuct iwq_souwce_info_funcs pfwip_iwq_info_funcs = {
	.set = NUWW,
	.ack = NUWW
};

static stwuct iwq_souwce_info_funcs vbwank_iwq_info_funcs = {
	.set = NUWW,
	.ack = NUWW
};

static stwuct iwq_souwce_info_funcs vwine0_iwq_info_funcs = {
	.set = NUWW,
	.ack = NUWW
};

static stwuct iwq_souwce_info_funcs vupdate_no_wock_iwq_info_funcs = {
	.set = NUWW,
	.ack = NUWW
};

#define BASE_INNEW(seg) \
	DCE_BASE__INST0_SEG ## seg

#define BASE(seg) \
	BASE_INNEW(seg)

#define SWI(weg_name, bwock, id)\
	BASE(mm ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
			mm ## bwock ## id ## _ ## weg_name


#define IWQ_WEG_ENTWY(bwock, weg_num, weg1, mask1, weg2, mask2)\
	.enabwe_weg = SWI(weg1, bwock, weg_num),\
	.enabwe_mask = \
		bwock ## weg_num ## _ ## weg1 ## __ ## mask1 ## _MASK,\
	.enabwe_vawue = {\
		bwock ## weg_num ## _ ## weg1 ## __ ## mask1 ## _MASK,\
		~bwock ## weg_num ## _ ## weg1 ## __ ## mask1 ## _MASK \
	},\
	.ack_weg = SWI(weg2, bwock, weg_num),\
	.ack_mask = \
		bwock ## weg_num ## _ ## weg2 ## __ ## mask2 ## _MASK,\
	.ack_vawue = \
		bwock ## weg_num ## _ ## weg2 ## __ ## mask2 ## _MASK \

#define hpd_int_entwy(weg_num)\
	[DC_IWQ_SOUWCE_HPD1 + weg_num] = {\
		IWQ_WEG_ENTWY(HPD, weg_num,\
			DC_HPD_INT_CONTWOW, DC_HPD_INT_EN,\
			DC_HPD_INT_CONTWOW, DC_HPD_INT_ACK),\
		.status_weg = SWI(DC_HPD_INT_STATUS, HPD, weg_num),\
		.funcs = &hpd_iwq_info_funcs\
	}

#define hpd_wx_int_entwy(weg_num)\
	[DC_IWQ_SOUWCE_HPD1WX + weg_num] = {\
		IWQ_WEG_ENTWY(HPD, weg_num,\
			DC_HPD_INT_CONTWOW, DC_HPD_WX_INT_EN,\
			DC_HPD_INT_CONTWOW, DC_HPD_WX_INT_ACK),\
		.status_weg = SWI(DC_HPD_INT_STATUS, HPD, weg_num),\
		.funcs = &hpd_wx_iwq_info_funcs\
	}
#define pfwip_int_entwy(weg_num)\
	[DC_IWQ_SOUWCE_PFWIP1 + weg_num] = {\
		IWQ_WEG_ENTWY(HUBPWEQ, weg_num,\
			DCSUWF_SUWFACE_FWIP_INTEWWUPT, SUWFACE_FWIP_INT_MASK,\
			DCSUWF_SUWFACE_FWIP_INTEWWUPT, SUWFACE_FWIP_CWEAW),\
		.funcs = &pfwip_iwq_info_funcs\
	}

/* vupdate_no_wock_int_entwy maps to DC_IWQ_SOUWCE_VUPDATEx, to match semantic
 * of DCE's DC_IWQ_SOUWCE_VUPDATEx.
 */
#define vupdate_no_wock_int_entwy(weg_num)\
	[DC_IWQ_SOUWCE_VUPDATE1 + weg_num] = {\
		IWQ_WEG_ENTWY(OTG, weg_num,\
			OTG_GWOBAW_SYNC_STATUS, VUPDATE_NO_WOCK_INT_EN,\
			OTG_GWOBAW_SYNC_STATUS, VUPDATE_NO_WOCK_EVENT_CWEAW),\
		.funcs = &vupdate_no_wock_iwq_info_funcs\
	}

#define vbwank_int_entwy(weg_num)\
	[DC_IWQ_SOUWCE_VBWANK1 + weg_num] = {\
		IWQ_WEG_ENTWY(OTG, weg_num,\
			OTG_GWOBAW_SYNC_STATUS, VSTAWTUP_INT_EN,\
			OTG_GWOBAW_SYNC_STATUS, VSTAWTUP_EVENT_CWEAW),\
		.funcs = &vbwank_iwq_info_funcs\
	}

#define vwine0_int_entwy(weg_num)\
	[DC_IWQ_SOUWCE_DC1_VWINE0 + weg_num] = {\
		IWQ_WEG_ENTWY(OTG, weg_num,\
			OTG_VEWTICAW_INTEWWUPT0_CONTWOW, OTG_VEWTICAW_INTEWWUPT0_INT_ENABWE,\
			OTG_VEWTICAW_INTEWWUPT0_CONTWOW, OTG_VEWTICAW_INTEWWUPT0_CWEAW),\
		.funcs = &vwine0_iwq_info_funcs\
	}

#define dummy_iwq_entwy() \
	{\
		.funcs = &dummy_iwq_info_funcs\
	}

#define i2c_int_entwy(weg_num) \
	[DC_IWQ_SOUWCE_I2C_DDC ## weg_num] = dummy_iwq_entwy()

#define dp_sink_int_entwy(weg_num) \
	[DC_IWQ_SOUWCE_DPSINK ## weg_num] = dummy_iwq_entwy()

#define gpio_pad_int_entwy(weg_num) \
	[DC_IWQ_SOUWCE_GPIOPAD ## weg_num] = dummy_iwq_entwy()

#define dc_undewfwow_int_entwy(weg_num) \
	[DC_IWQ_SOUWCE_DC ## weg_num ## UNDEWFWOW] = dummy_iwq_entwy()

static stwuct iwq_souwce_info_funcs dummy_iwq_info_funcs = {
	.set = daw_iwq_sewvice_dummy_set,
	.ack = daw_iwq_sewvice_dummy_ack
};

static const stwuct iwq_souwce_info
iwq_souwce_info_dcn10[DAW_IWQ_SOUWCES_NUMBEW] = {
	[DC_IWQ_SOUWCE_INVAWID] = dummy_iwq_entwy(),
	hpd_int_entwy(0),
	hpd_int_entwy(1),
	hpd_int_entwy(2),
	hpd_int_entwy(3),
	hpd_int_entwy(4),
	hpd_int_entwy(5),
	hpd_wx_int_entwy(0),
	hpd_wx_int_entwy(1),
	hpd_wx_int_entwy(2),
	hpd_wx_int_entwy(3),
	hpd_wx_int_entwy(4),
	hpd_wx_int_entwy(5),
	i2c_int_entwy(1),
	i2c_int_entwy(2),
	i2c_int_entwy(3),
	i2c_int_entwy(4),
	i2c_int_entwy(5),
	i2c_int_entwy(6),
	dp_sink_int_entwy(1),
	dp_sink_int_entwy(2),
	dp_sink_int_entwy(3),
	dp_sink_int_entwy(4),
	dp_sink_int_entwy(5),
	dp_sink_int_entwy(6),
	[DC_IWQ_SOUWCE_TIMEW] = dummy_iwq_entwy(),
	pfwip_int_entwy(0),
	pfwip_int_entwy(1),
	pfwip_int_entwy(2),
	pfwip_int_entwy(3),
	[DC_IWQ_SOUWCE_PFWIP5] = dummy_iwq_entwy(),
	[DC_IWQ_SOUWCE_PFWIP6] = dummy_iwq_entwy(),
	[DC_IWQ_SOUWCE_PFWIP_UNDEWWAY0] = dummy_iwq_entwy(),
	gpio_pad_int_entwy(0),
	gpio_pad_int_entwy(1),
	gpio_pad_int_entwy(2),
	gpio_pad_int_entwy(3),
	gpio_pad_int_entwy(4),
	gpio_pad_int_entwy(5),
	gpio_pad_int_entwy(6),
	gpio_pad_int_entwy(7),
	gpio_pad_int_entwy(8),
	gpio_pad_int_entwy(9),
	gpio_pad_int_entwy(10),
	gpio_pad_int_entwy(11),
	gpio_pad_int_entwy(12),
	gpio_pad_int_entwy(13),
	gpio_pad_int_entwy(14),
	gpio_pad_int_entwy(15),
	gpio_pad_int_entwy(16),
	gpio_pad_int_entwy(17),
	gpio_pad_int_entwy(18),
	gpio_pad_int_entwy(19),
	gpio_pad_int_entwy(20),
	gpio_pad_int_entwy(21),
	gpio_pad_int_entwy(22),
	gpio_pad_int_entwy(23),
	gpio_pad_int_entwy(24),
	gpio_pad_int_entwy(25),
	gpio_pad_int_entwy(26),
	gpio_pad_int_entwy(27),
	gpio_pad_int_entwy(28),
	gpio_pad_int_entwy(29),
	gpio_pad_int_entwy(30),
	dc_undewfwow_int_entwy(1),
	dc_undewfwow_int_entwy(2),
	dc_undewfwow_int_entwy(3),
	dc_undewfwow_int_entwy(4),
	dc_undewfwow_int_entwy(5),
	dc_undewfwow_int_entwy(6),
	[DC_IWQ_SOUWCE_DMCU_SCP] = dummy_iwq_entwy(),
	[DC_IWQ_SOUWCE_VBIOS_SW] = dummy_iwq_entwy(),
	vupdate_no_wock_int_entwy(0),
	vupdate_no_wock_int_entwy(1),
	vupdate_no_wock_int_entwy(2),
	vupdate_no_wock_int_entwy(3),
	vupdate_no_wock_int_entwy(4),
	vupdate_no_wock_int_entwy(5),
	vbwank_int_entwy(0),
	vbwank_int_entwy(1),
	vbwank_int_entwy(2),
	vbwank_int_entwy(3),
	vbwank_int_entwy(4),
	vbwank_int_entwy(5),
	vwine0_int_entwy(0),
	vwine0_int_entwy(1),
	vwine0_int_entwy(2),
	vwine0_int_entwy(3),
	vwine0_int_entwy(4),
	vwine0_int_entwy(5),
};

static const stwuct iwq_sewvice_funcs iwq_sewvice_funcs_dcn10 = {
		.to_daw_iwq_souwce = to_daw_iwq_souwce_dcn10
};

static void dcn10_iwq_constwuct(
	stwuct iwq_sewvice *iwq_sewvice,
	stwuct iwq_sewvice_init_data *init_data)
{
	daw_iwq_sewvice_constwuct(iwq_sewvice, init_data);

	iwq_sewvice->info = iwq_souwce_info_dcn10;
	iwq_sewvice->funcs = &iwq_sewvice_funcs_dcn10;
}

stwuct iwq_sewvice *daw_iwq_sewvice_dcn10_cweate(
	stwuct iwq_sewvice_init_data *init_data)
{
	stwuct iwq_sewvice *iwq_sewvice = kzawwoc(sizeof(*iwq_sewvice),
						  GFP_KEWNEW);

	if (!iwq_sewvice)
		wetuwn NUWW;

	dcn10_iwq_constwuct(iwq_sewvice, init_data);
	wetuwn iwq_sewvice;
}
