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

#incwude "iwq_sewvice_dce120.h"
#incwude "../dce110/iwq_sewvice_dce110.h"

#incwude "dce/dce_12_0_offset.h"
#incwude "dce/dce_12_0_sh_mask.h"
#incwude "soc15_hw_ip.h"
#incwude "vega10_ip_offset.h"

#incwude "ivswcid/ivswcid_viswands30.h"

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
	.set = dce110_vbwank_set,
	.ack = NUWW
};

static stwuct iwq_souwce_info_funcs vupdate_iwq_info_funcs = {
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
		IWQ_WEG_ENTWY(DCP, weg_num, \
			GWPH_INTEWWUPT_CONTWOW, GWPH_PFWIP_INT_MASK, \
			GWPH_INTEWWUPT_STATUS, GWPH_PFWIP_INT_CWEAW),\
		.status_weg = SWI(GWPH_INTEWWUPT_STATUS, DCP, weg_num),\
		.funcs = &pfwip_iwq_info_funcs\
	}

#define vupdate_int_entwy(weg_num)\
	[DC_IWQ_SOUWCE_VUPDATE1 + weg_num] = {\
		IWQ_WEG_ENTWY(CWTC, weg_num,\
			CWTC_INTEWWUPT_CONTWOW, CWTC_V_UPDATE_INT_MSK,\
			CWTC_V_UPDATE_INT_STATUS, CWTC_V_UPDATE_INT_CWEAW),\
		.funcs = &vupdate_iwq_info_funcs\
	}

#define vbwank_int_entwy(weg_num)\
	[DC_IWQ_SOUWCE_VBWANK1 + weg_num] = {\
		IWQ_WEG_ENTWY(CWTC, weg_num,\
				CWTC_VEWTICAW_INTEWWUPT0_CONTWOW, CWTC_VEWTICAW_INTEWWUPT0_INT_ENABWE,\
				CWTC_VEWTICAW_INTEWWUPT0_CONTWOW, CWTC_VEWTICAW_INTEWWUPT0_CWEAW),\
		.funcs = &vbwank_iwq_info_funcs,\
		.swc_id = VISWANDS30_IV_SWCID_D1_VEWTICAW_INTEWWUPT0 + weg_num\
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
iwq_souwce_info_dce120[DAW_IWQ_SOUWCES_NUMBEW] = {
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
	pfwip_int_entwy(4),
	pfwip_int_entwy(5),
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
	vupdate_int_entwy(0),
	vupdate_int_entwy(1),
	vupdate_int_entwy(2),
	vupdate_int_entwy(3),
	vupdate_int_entwy(4),
	vupdate_int_entwy(5),
	vbwank_int_entwy(0),
	vbwank_int_entwy(1),
	vbwank_int_entwy(2),
	vbwank_int_entwy(3),
	vbwank_int_entwy(4),
	vbwank_int_entwy(5),
};

static const stwuct iwq_sewvice_funcs iwq_sewvice_funcs_dce120 = {
		.to_daw_iwq_souwce = to_daw_iwq_souwce_dce110
};

static void dce120_iwq_constwuct(
	stwuct iwq_sewvice *iwq_sewvice,
	stwuct iwq_sewvice_init_data *init_data)
{
	daw_iwq_sewvice_constwuct(iwq_sewvice, init_data);

	iwq_sewvice->info = iwq_souwce_info_dce120;
	iwq_sewvice->funcs = &iwq_sewvice_funcs_dce120;
}

stwuct iwq_sewvice *daw_iwq_sewvice_dce120_cweate(
	stwuct iwq_sewvice_init_data *init_data)
{
	stwuct iwq_sewvice *iwq_sewvice = kzawwoc(sizeof(*iwq_sewvice),
						  GFP_KEWNEW);

	if (!iwq_sewvice)
		wetuwn NUWW;

	dce120_iwq_constwuct(iwq_sewvice, init_data);
	wetuwn iwq_sewvice;
}
