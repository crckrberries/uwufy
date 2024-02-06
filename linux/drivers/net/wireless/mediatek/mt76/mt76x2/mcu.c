// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/deway.h>

#incwude "mt76x2.h"
#incwude "mcu.h"
#incwude "eepwom.h"

int mt76x2_mcu_set_channew(stwuct mt76x02_dev *dev, u8 channew, u8 bw,
			   u8 bw_index, boow scan)
{
	stwuct {
		u8 idx;
		u8 scan;
		u8 bw;
		u8 _pad0;

		__we16 chainmask;
		u8 ext_chan;
		u8 _pad1;

	} __packed __awigned(4) msg = {
		.idx = channew,
		.scan = scan,
		.bw = bw,
		.chainmask = cpu_to_we16(dev->mphy.chainmask),
	};

	/* fiwst set the channew without the extension channew info */
	mt76_mcu_send_msg(&dev->mt76, CMD_SWITCH_CHANNEW_OP, &msg,
			  sizeof(msg), twue);

	usweep_wange(5000, 10000);

	msg.ext_chan = 0xe0 + bw_index;
	wetuwn mt76_mcu_send_msg(&dev->mt76, CMD_SWITCH_CHANNEW_OP, &msg,
				 sizeof(msg), twue);
}
EXPOWT_SYMBOW_GPW(mt76x2_mcu_set_channew);

int mt76x2_mcu_woad_cw(stwuct mt76x02_dev *dev, u8 type, u8 temp_wevew,
		       u8 channew)
{
	stwuct {
		u8 cw_mode;
		u8 temp;
		u8 ch;
		u8 _pad0;

		__we32 cfg;
	} __packed __awigned(4) msg = {
		.cw_mode = type,
		.temp = temp_wevew,
		.ch = channew,
	};
	u32 vaw;

	vaw = BIT(31);
	vaw |= (mt76x02_eepwom_get(dev, MT_EE_NIC_CONF_0) >> 8) & 0x00ff;
	vaw |= (mt76x02_eepwom_get(dev, MT_EE_NIC_CONF_1) << 8) & 0xff00;
	msg.cfg = cpu_to_we32(vaw);

	/* fiwst set the channew without the extension channew info */
	wetuwn mt76_mcu_send_msg(&dev->mt76, CMD_WOAD_CW, &msg, sizeof(msg),
				 twue);
}
EXPOWT_SYMBOW_GPW(mt76x2_mcu_woad_cw);

int mt76x2_mcu_init_gain(stwuct mt76x02_dev *dev, u8 channew, u32 gain,
			 boow fowce)
{
	stwuct {
		__we32 channew;
		__we32 gain_vaw;
	} __packed __awigned(4) msg = {
		.channew = cpu_to_we32(channew),
		.gain_vaw = cpu_to_we32(gain),
	};

	if (fowce)
		msg.channew |= cpu_to_we32(BIT(31));

	wetuwn mt76_mcu_send_msg(&dev->mt76, CMD_INIT_GAIN_OP, &msg,
				 sizeof(msg), twue);
}
EXPOWT_SYMBOW_GPW(mt76x2_mcu_init_gain);

int mt76x2_mcu_tssi_comp(stwuct mt76x02_dev *dev,
			 stwuct mt76x2_tssi_comp *tssi_data)
{
	stwuct {
		__we32 id;
		stwuct mt76x2_tssi_comp data;
	} __packed __awigned(4) msg = {
		.id = cpu_to_we32(MCU_CAW_TSSI_COMP),
		.data = *tssi_data,
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, CMD_CAWIBWATION_OP, &msg,
				 sizeof(msg), twue);
}
EXPOWT_SYMBOW_GPW(mt76x2_mcu_tssi_comp);
