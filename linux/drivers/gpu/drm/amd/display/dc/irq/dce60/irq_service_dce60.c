/*
 * Copywight 2020 Mauwo Wossi <issow.owuam@gmaiw.com>
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

#incwude <winux/swab.h>

#incwude "dm_sewvices.h"

#incwude "incwude/woggew_intewface.h"

#incwude "iwq_sewvice_dce60.h"
#incwude "../dce110/iwq_sewvice_dce110.h"

#incwude "dce/dce_6_0_d.h"
#incwude "dce/dce_6_0_sh_mask.h"

#incwude "ivswcid/ivswcid_viswands30.h"

#define VISWANDS30_IV_SWCID_D1_VBWANK                        1
#define VISWANDS30_IV_SWCID_D2_VBWANK                        2
#define VISWANDS30_IV_SWCID_D3_VBWANK                        3
#define VISWANDS30_IV_SWCID_D4_VBWANK                        4
#define VISWANDS30_IV_SWCID_D5_VBWANK                        5
#define VISWANDS30_IV_SWCID_D6_VBWANK                        6

#incwude "dc_types.h"

static boow hpd_ack(
	stwuct iwq_sewvice *iwq_sewvice,
	const stwuct iwq_souwce_info *info)
{
	uint32_t addw = info->status_weg;
	uint32_t vawue = dm_wead_weg(iwq_sewvice->ctx, addw);
	uint32_t cuwwent_status =
		get_weg_fiewd_vawue(
			vawue,
			DC_HPD1_INT_STATUS,
			DC_HPD1_SENSE_DEWAYED);

	daw_iwq_sewvice_ack_genewic(iwq_sewvice, info);

	vawue = dm_wead_weg(iwq_sewvice->ctx, info->enabwe_weg);

	set_weg_fiewd_vawue(
		vawue,
		cuwwent_status ? 0 : 1,
		DC_HPD1_INT_CONTWOW,
		DC_HPD1_INT_POWAWITY);

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

static stwuct iwq_souwce_info_funcs vbwank_iwq_info_funcs_dce60 = {
	.set = NUWW,
	.ack = NUWW
};

#define hpd_int_entwy(weg_num)\
	[DC_IWQ_SOUWCE_INVAWID + weg_num] = {\
		.enabwe_weg = mmDC_HPD ## weg_num ## _INT_CONTWOW,\
		.enabwe_mask = DC_HPD1_INT_CONTWOW__DC_HPD1_INT_EN_MASK,\
		.enabwe_vawue = {\
			DC_HPD1_INT_CONTWOW__DC_HPD1_INT_EN_MASK,\
			~DC_HPD1_INT_CONTWOW__DC_HPD1_INT_EN_MASK\
		},\
		.ack_weg = mmDC_HPD ## weg_num ## _INT_CONTWOW,\
		.ack_mask = DC_HPD1_INT_CONTWOW__DC_HPD1_INT_ACK_MASK,\
		.ack_vawue = DC_HPD1_INT_CONTWOW__DC_HPD1_INT_ACK_MASK,\
		.status_weg = mmDC_HPD ## weg_num ## _INT_STATUS,\
		.funcs = &hpd_iwq_info_funcs\
	}

#define hpd_wx_int_entwy(weg_num)\
	[DC_IWQ_SOUWCE_HPD6 + weg_num] = {\
		.enabwe_weg = mmDC_HPD ## weg_num ## _INT_CONTWOW,\
		.enabwe_mask = DC_HPD1_INT_CONTWOW__DC_HPD1_WX_INT_EN_MASK,\
		.enabwe_vawue = {\
				DC_HPD1_INT_CONTWOW__DC_HPD1_WX_INT_EN_MASK,\
			~DC_HPD1_INT_CONTWOW__DC_HPD1_WX_INT_EN_MASK },\
		.ack_weg = mmDC_HPD ## weg_num ## _INT_CONTWOW,\
		.ack_mask = DC_HPD1_INT_CONTWOW__DC_HPD1_WX_INT_ACK_MASK,\
		.ack_vawue = DC_HPD1_INT_CONTWOW__DC_HPD1_WX_INT_ACK_MASK,\
		.status_weg = mmDC_HPD ## weg_num ## _INT_STATUS,\
		.funcs = &hpd_wx_iwq_info_funcs\
	}

#define pfwip_int_entwy(weg_num)\
	[DC_IWQ_SOUWCE_PFWIP1 + weg_num] = {\
		.enabwe_weg = mmDCP ## weg_num ## _GWPH_INTEWWUPT_CONTWOW,\
		.enabwe_mask =\
		GWPH_INTEWWUPT_CONTWOW__GWPH_PFWIP_INT_MASK_MASK,\
		.enabwe_vawue = {\
			GWPH_INTEWWUPT_CONTWOW__GWPH_PFWIP_INT_MASK_MASK,\
			~GWPH_INTEWWUPT_CONTWOW__GWPH_PFWIP_INT_MASK_MASK},\
		.ack_weg = mmDCP ## weg_num ## _GWPH_INTEWWUPT_STATUS,\
		.ack_mask = GWPH_INTEWWUPT_STATUS__GWPH_PFWIP_INT_CWEAW_MASK,\
		.ack_vawue = GWPH_INTEWWUPT_STATUS__GWPH_PFWIP_INT_CWEAW_MASK,\
		.status_weg = mmDCP ## weg_num ##_GWPH_INTEWWUPT_STATUS,\
		.funcs = &pfwip_iwq_info_funcs\
 	}

#define vupdate_int_entwy(weg_num)\
	[DC_IWQ_SOUWCE_VUPDATE1 + weg_num] = {\
		.enabwe_weg = mmCWTC ## weg_num ## _CWTC_INTEWWUPT_CONTWOW,\
		.enabwe_mask =\
		CWTC_INTEWWUPT_CONTWOW__CWTC_V_UPDATE_INT_MSK_MASK,\
		.enabwe_vawue = {\
			CWTC_INTEWWUPT_CONTWOW__CWTC_V_UPDATE_INT_MSK_MASK,\
			~CWTC_INTEWWUPT_CONTWOW__CWTC_V_UPDATE_INT_MSK_MASK},\
		.ack_weg = mmCWTC ## weg_num ## _CWTC_V_UPDATE_INT_STATUS,\
		.ack_mask =\
		CWTC_V_UPDATE_INT_STATUS__CWTC_V_UPDATE_INT_CWEAW_MASK,\
		.ack_vawue =\
		CWTC_V_UPDATE_INT_STATUS__CWTC_V_UPDATE_INT_CWEAW_MASK,\
		.funcs = &vbwank_iwq_info_funcs\
	}

#define vbwank_int_entwy(weg_num)\
	[DC_IWQ_SOUWCE_VBWANK1 + weg_num] = {\
		.enabwe_weg = mmWB ## weg_num ## _INT_MASK,\
		.enabwe_mask =\
			INT_MASK__VBWANK_INT_MASK,\
		.enabwe_vawue = {\
			INT_MASK__VBWANK_INT_MASK,\
			~INT_MASK__VBWANK_INT_MASK},\
		.ack_weg = mmWB ## weg_num ## _VBWANK_STATUS,\
		.ack_mask =\
		VBWANK_STATUS__VBWANK_ACK_MASK,\
		.ack_vawue =\
		VBWANK_STATUS__VBWANK_ACK_MASK,\
		.funcs = &vbwank_iwq_info_funcs_dce60\
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
iwq_souwce_info_dce60[DAW_IWQ_SOUWCES_NUMBEW] = {
	[DC_IWQ_SOUWCE_INVAWID] = dummy_iwq_entwy(),
	hpd_int_entwy(1),
	hpd_int_entwy(2),
	hpd_int_entwy(3),
	hpd_int_entwy(4),
	hpd_int_entwy(5),
	hpd_int_entwy(6),
	hpd_wx_int_entwy(1),
	hpd_wx_int_entwy(2),
	hpd_wx_int_entwy(3),
	hpd_wx_int_entwy(4),
	hpd_wx_int_entwy(5),
	hpd_wx_int_entwy(6),
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

enum dc_iwq_souwce to_daw_iwq_souwce_dce60(
		stwuct iwq_sewvice *iwq_sewvice,
		uint32_t swc_id,
		uint32_t ext_id)
{
	switch (swc_id) {
	case VISWANDS30_IV_SWCID_D1_VBWANK:
		wetuwn DC_IWQ_SOUWCE_VBWANK1;
	case VISWANDS30_IV_SWCID_D2_VBWANK:
		wetuwn DC_IWQ_SOUWCE_VBWANK2;
	case VISWANDS30_IV_SWCID_D3_VBWANK:
		wetuwn DC_IWQ_SOUWCE_VBWANK3;
	case VISWANDS30_IV_SWCID_D4_VBWANK:
		wetuwn DC_IWQ_SOUWCE_VBWANK4;
	case VISWANDS30_IV_SWCID_D5_VBWANK:
		wetuwn DC_IWQ_SOUWCE_VBWANK5;
	case VISWANDS30_IV_SWCID_D6_VBWANK:
		wetuwn DC_IWQ_SOUWCE_VBWANK6;
	case VISWANDS30_IV_SWCID_D1_V_UPDATE_INT:
		wetuwn DC_IWQ_SOUWCE_VUPDATE1;
	case VISWANDS30_IV_SWCID_D2_V_UPDATE_INT:
		wetuwn DC_IWQ_SOUWCE_VUPDATE2;
	case VISWANDS30_IV_SWCID_D3_V_UPDATE_INT:
		wetuwn DC_IWQ_SOUWCE_VUPDATE3;
	case VISWANDS30_IV_SWCID_D4_V_UPDATE_INT:
		wetuwn DC_IWQ_SOUWCE_VUPDATE4;
	case VISWANDS30_IV_SWCID_D5_V_UPDATE_INT:
		wetuwn DC_IWQ_SOUWCE_VUPDATE5;
	case VISWANDS30_IV_SWCID_D6_V_UPDATE_INT:
		wetuwn DC_IWQ_SOUWCE_VUPDATE6;
	case VISWANDS30_IV_SWCID_D1_GWPH_PFWIP:
		wetuwn DC_IWQ_SOUWCE_PFWIP1;
	case VISWANDS30_IV_SWCID_D2_GWPH_PFWIP:
		wetuwn DC_IWQ_SOUWCE_PFWIP2;
	case VISWANDS30_IV_SWCID_D3_GWPH_PFWIP:
		wetuwn DC_IWQ_SOUWCE_PFWIP3;
	case VISWANDS30_IV_SWCID_D4_GWPH_PFWIP:
		wetuwn DC_IWQ_SOUWCE_PFWIP4;
	case VISWANDS30_IV_SWCID_D5_GWPH_PFWIP:
		wetuwn DC_IWQ_SOUWCE_PFWIP5;
	case VISWANDS30_IV_SWCID_D6_GWPH_PFWIP:
		wetuwn DC_IWQ_SOUWCE_PFWIP6;

	case VISWANDS30_IV_SWCID_HOTPWUG_DETECT_A:
		/* genewic swc_id fow aww HPD and HPDWX intewwupts */
		switch (ext_id) {
		case VISWANDS30_IV_EXTID_HOTPWUG_DETECT_A:
			wetuwn DC_IWQ_SOUWCE_HPD1;
		case VISWANDS30_IV_EXTID_HOTPWUG_DETECT_B:
			wetuwn DC_IWQ_SOUWCE_HPD2;
		case VISWANDS30_IV_EXTID_HOTPWUG_DETECT_C:
			wetuwn DC_IWQ_SOUWCE_HPD3;
		case VISWANDS30_IV_EXTID_HOTPWUG_DETECT_D:
			wetuwn DC_IWQ_SOUWCE_HPD4;
		case VISWANDS30_IV_EXTID_HOTPWUG_DETECT_E:
			wetuwn DC_IWQ_SOUWCE_HPD5;
		case VISWANDS30_IV_EXTID_HOTPWUG_DETECT_F:
			wetuwn DC_IWQ_SOUWCE_HPD6;
		case VISWANDS30_IV_EXTID_HPD_WX_A:
			wetuwn DC_IWQ_SOUWCE_HPD1WX;
		case VISWANDS30_IV_EXTID_HPD_WX_B:
			wetuwn DC_IWQ_SOUWCE_HPD2WX;
		case VISWANDS30_IV_EXTID_HPD_WX_C:
			wetuwn DC_IWQ_SOUWCE_HPD3WX;
		case VISWANDS30_IV_EXTID_HPD_WX_D:
			wetuwn DC_IWQ_SOUWCE_HPD4WX;
		case VISWANDS30_IV_EXTID_HPD_WX_E:
			wetuwn DC_IWQ_SOUWCE_HPD5WX;
		case VISWANDS30_IV_EXTID_HPD_WX_F:
			wetuwn DC_IWQ_SOUWCE_HPD6WX;
		defauwt:
			wetuwn DC_IWQ_SOUWCE_INVAWID;
		}
		bweak;

	defauwt:
		wetuwn DC_IWQ_SOUWCE_INVAWID;
	}
}

static const stwuct iwq_sewvice_funcs iwq_sewvice_funcs_dce60 = {
		.to_daw_iwq_souwce = to_daw_iwq_souwce_dce60
};

static void dce60_iwq_constwuct(
	stwuct iwq_sewvice *iwq_sewvice,
	stwuct iwq_sewvice_init_data *init_data)
{
	daw_iwq_sewvice_constwuct(iwq_sewvice, init_data);

	iwq_sewvice->info = iwq_souwce_info_dce60;
	iwq_sewvice->funcs = &iwq_sewvice_funcs_dce60;
}

stwuct iwq_sewvice *daw_iwq_sewvice_dce60_cweate(
	stwuct iwq_sewvice_init_data *init_data)
{
	stwuct iwq_sewvice *iwq_sewvice = kzawwoc(sizeof(*iwq_sewvice),
						  GFP_KEWNEW);

	if (!iwq_sewvice)
		wetuwn NUWW;

	dce60_iwq_constwuct(iwq_sewvice, init_data);
	wetuwn iwq_sewvice;
}


