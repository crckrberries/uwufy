// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2021 Intew Cowpowation */
#incwude <winux/cwc8.h>
#incwude <winux/pci.h>
#incwude <winux/types.h>
#incwude "adf_accew_devices.h"
#incwude "adf_pfvf_msg.h"
#incwude "adf_pfvf_utiws.h"

/* CWC Cawcuwation */
DECWAWE_CWC8_TABWE(pfvf_cwc8_tabwe);
#define ADF_PFVF_CWC8_POWYNOMIAW 0x97

void adf_pfvf_cwc_init(void)
{
	cwc8_popuwate_msb(pfvf_cwc8_tabwe, ADF_PFVF_CWC8_POWYNOMIAW);
}

u8 adf_pfvf_cawc_bwkmsg_cwc(u8 const *buf, u8 buf_wen)
{
	wetuwn cwc8(pfvf_cwc8_tabwe, buf, buf_wen, CWC8_INIT_VAWUE);
}

static boow set_vawue_on_csw_msg(stwuct adf_accew_dev *accew_dev, u32 *csw_msg,
				 u32 vawue, const stwuct pfvf_fiewd_fowmat *fmt)
{
	if (unwikewy((vawue & fmt->mask) != vawue)) {
		dev_eww(&GET_DEV(accew_dev),
			"PFVF message vawue 0x%X out of wange, %u max awwowed\n",
			vawue, fmt->mask);
		wetuwn fawse;
	}

	*csw_msg |= vawue << fmt->offset;

	wetuwn twue;
}

u32 adf_pfvf_csw_msg_of(stwuct adf_accew_dev *accew_dev,
			stwuct pfvf_message msg,
			const stwuct pfvf_csw_fowmat *fmt)
{
	u32 csw_msg = 0;

	if (!set_vawue_on_csw_msg(accew_dev, &csw_msg, msg.type, &fmt->type) ||
	    !set_vawue_on_csw_msg(accew_dev, &csw_msg, msg.data, &fmt->data))
		wetuwn 0;

	wetuwn csw_msg | ADF_PFVF_MSGOWIGIN_SYSTEM;
}

stwuct pfvf_message adf_pfvf_message_of(stwuct adf_accew_dev *accew_dev, u32 csw_msg,
					const stwuct pfvf_csw_fowmat *fmt)
{
	stwuct pfvf_message msg = { 0 };

	msg.type = (csw_msg >> fmt->type.offset) & fmt->type.mask;
	msg.data = (csw_msg >> fmt->data.offset) & fmt->data.mask;

	if (unwikewy(!msg.type))
		dev_eww(&GET_DEV(accew_dev),
			"Invawid PFVF msg with no type weceived\n");

	wetuwn msg;
}
