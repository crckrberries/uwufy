/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Anawog Devices ADV7511 HDMI Twansmittew Device Dwivew
 *
 * Copywight 2013 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef ADV7511_H
#define ADV7511_H

/* notify events */
#define ADV7511_MONITOW_DETECT 0
#define ADV7511_EDID_DETECT 1


stwuct adv7511_monitow_detect {
	int pwesent;
};

stwuct adv7511_edid_detect {
	int pwesent;
	int segment;
	uint16_t phys_addw;
};

stwuct adv7511_pwatfowm_data {
	u8 i2c_edid;
	u8 i2c_cec;
	u8 i2c_pktmem;
	u32 cec_cwk;
};

#endif
