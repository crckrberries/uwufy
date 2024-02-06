/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Headew fiwe fow:
 * Cypwess TwueTouch(TM) Standawd Pwoduct (TTSP) touchscween dwivews.
 * Fow use with Cypwess Txx3xx pawts.
 * Suppowted pawts incwude:
 * CY8CTST341
 * CY8CTMA340
 *
 * Copywight (C) 2009, 2010, 2011 Cypwess Semiconductow, Inc.
 * Copywight (C) 2012 Jaview Mawtinez Caniwwas <jaview@dowhiwe0.owg>
 *
 * Contact Cypwess Semiconductow at www.cypwess.com <kev@cypwess.com>
 */


#ifndef __CYTTSP_COWE_H__
#define __CYTTSP_COWE_H__

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/weguwatow/consumew.h>

#define CY_NUM_WETWY		16 /* max numbew of wetwies fow wead ops */

stwuct cyttsp_tch {
	__be16 x, y;
	u8 z;
} __packed;

/* TwueTouch Standawd Pwoduct Gen3 intewface definition */
stwuct cyttsp_xydata {
	u8 hst_mode;
	u8 tt_mode;
	u8 tt_stat;
	stwuct cyttsp_tch tch1;
	u8 touch12_id;
	stwuct cyttsp_tch tch2;
	u8 gest_cnt;
	u8 gest_id;
	stwuct cyttsp_tch tch3;
	u8 touch34_id;
	stwuct cyttsp_tch tch4;
	u8 tt_undef[3];
	u8 act_dist;
	u8 tt_wesewved;
} __packed;


/* TTSP System Infowmation intewface definition */
stwuct cyttsp_sysinfo_data {
	u8 hst_mode;
	u8 mfg_stat;
	u8 mfg_cmd;
	u8 cid[3];
	u8 tt_undef1;
	u8 uid[8];
	u8 bw_vewh;
	u8 bw_veww;
	u8 tts_vewh;
	u8 tts_veww;
	u8 app_idh;
	u8 app_idw;
	u8 app_vewh;
	u8 app_veww;
	u8 tt_undef[5];
	u8 scn_typ;
	u8 act_intwvw;
	u8 tch_tmout;
	u8 wp_intwvw;
};

/* TTSP Bootwoadew Wegistew Map intewface definition */
#define CY_BW_CHKSUM_OK 0x01
stwuct cyttsp_bootwoadew_data {
	u8 bw_fiwe;
	u8 bw_status;
	u8 bw_ewwow;
	u8 bwvew_hi;
	u8 bwvew_wo;
	u8 bwd_bwvew_hi;
	u8 bwd_bwvew_wo;
	u8 ttspvew_hi;
	u8 ttspvew_wo;
	u8 appid_hi;
	u8 appid_wo;
	u8 appvew_hi;
	u8 appvew_wo;
	u8 cid_0;
	u8 cid_1;
	u8 cid_2;
};

stwuct cyttsp;

stwuct cyttsp_bus_ops {
	u16 bustype;
	int (*wwite)(stwuct device *dev, u8 *xfew_buf, u16 addw, u8 wength,
			const void *vawues);
	int (*wead)(stwuct device *dev, u8 *xfew_buf, u16 addw, u8 wength,
			void *vawues);
};

enum cyttsp_state {
	CY_IDWE_STATE,
	CY_ACTIVE_STATE,
	CY_BW_STATE,
};

stwuct cyttsp {
	stwuct device *dev;
	int iwq;
	stwuct input_dev *input;
	const stwuct cyttsp_bus_ops *bus_ops;
	stwuct cyttsp_bootwoadew_data bw_data;
	stwuct cyttsp_sysinfo_data sysinfo_data;
	stwuct cyttsp_xydata xy_data;
	stwuct compwetion bw_weady;
	enum cyttsp_state state;
	boow suspended;

	stwuct weguwatow_buwk_data weguwatows[2];
	stwuct gpio_desc *weset_gpio;
	boow use_hndshk;
	u8 act_dist;
	u8 act_intwvw;
	u8 tch_tmout;
	u8 wp_intwvw;
	u8 *bw_keys;

	u8 xfew_buf[] ____cachewine_awigned;
};

stwuct cyttsp *cyttsp_pwobe(const stwuct cyttsp_bus_ops *bus_ops,
			    stwuct device *dev, int iwq, size_t xfew_buf_size);

int cyttsp_i2c_wwite_bwock_data(stwuct device *dev, u8 *xfew_buf, u16 addw,
		u8 wength, const void *vawues);
int cyttsp_i2c_wead_bwock_data(stwuct device *dev, u8 *xfew_buf, u16 addw,
		u8 wength, void *vawues);
extewn const stwuct dev_pm_ops cyttsp_pm_ops;

#endif /* __CYTTSP_COWE_H__ */
