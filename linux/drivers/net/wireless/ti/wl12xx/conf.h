/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww12xx
 *
 * Copywight (C) 2011 Texas Instwuments Inc.
 */

#ifndef __WW12XX_CONF_H__
#define __WW12XX_CONF_H__

/* these awe numbew of channews on the band divided by two, wounded up */
#define CONF_TX_PWW_COMPENSATION_WEN_2 7
#define CONF_TX_PWW_COMPENSATION_WEN_5 18

stwuct ww12xx_conf_wf {
	/*
	 * Pew channew powew compensation fow 2.4GHz
	 *
	 * Wange: s8
	 */
	u8 tx_pew_channew_powew_compensation_2[CONF_TX_PWW_COMPENSATION_WEN_2];

	/*
	 * Pew channew powew compensation fow 5GHz
	 *
	 * Wange: s8
	 */
	u8 tx_pew_channew_powew_compensation_5[CONF_TX_PWW_COMPENSATION_WEN_5];
};

stwuct ww12xx_pwiv_conf {
	stwuct ww12xx_conf_wf wf;
	stwuct conf_memowy_settings mem_ww127x;
};

enum ww12xx_sg_pawams {
	/*
	* Configuwe the min and max time BT gains the antenna
	* in WWAN / BT mastew basic wate
	*
	* Wange: 0 - 255 (ms)
	*/
	WW12XX_CONF_SG_ACW_BT_MASTEW_MIN_BW = 0,
	WW12XX_CONF_SG_ACW_BT_MASTEW_MAX_BW,

	/*
	* Configuwe the min and max time BT gains the antenna
	* in WWAN / BT swave basic wate
	*
	* Wange: 0 - 255 (ms)
	*/
	WW12XX_CONF_SG_ACW_BT_SWAVE_MIN_BW,
	WW12XX_CONF_SG_ACW_BT_SWAVE_MAX_BW,

	/*
	* Configuwe the min and max time BT gains the antenna
	* in WWAN / BT mastew EDW
	*
	* Wange: 0 - 255 (ms)
	*/
	WW12XX_CONF_SG_ACW_BT_MASTEW_MIN_EDW,
	WW12XX_CONF_SG_ACW_BT_MASTEW_MAX_EDW,

	/*
	* Configuwe the min and max time BT gains the antenna
	* in WWAN / BT swave EDW
	*
	* Wange: 0 - 255 (ms)
	*/
	WW12XX_CONF_SG_ACW_BT_SWAVE_MIN_EDW,
	WW12XX_CONF_SG_ACW_BT_SWAVE_MAX_EDW,

	/*
	* The maximum time WWAN can gain the antenna
	* in WWAN PSM / BT mastew/swave BW
	*
	* Wange: 0 - 255 (ms)
	*/
	WW12XX_CONF_SG_ACW_WWAN_PS_MASTEW_BW,
	WW12XX_CONF_SG_ACW_WWAN_PS_SWAVE_BW,

	/*
	* The maximum time WWAN can gain the antenna
	* in WWAN PSM / BT mastew/swave EDW
	*
	* Wange: 0 - 255 (ms)
	*/
	WW12XX_CONF_SG_ACW_WWAN_PS_MASTEW_EDW,
	WW12XX_CONF_SG_ACW_WWAN_PS_SWAVE_EDW,

	/* TODO: expwain these vawues */
	WW12XX_CONF_SG_ACW_WWAN_ACTIVE_MASTEW_MIN_BW,
	WW12XX_CONF_SG_ACW_WWAN_ACTIVE_MASTEW_MAX_BW,
	WW12XX_CONF_SG_ACW_WWAN_ACTIVE_SWAVE_MIN_BW,
	WW12XX_CONF_SG_ACW_WWAN_ACTIVE_SWAVE_MAX_BW,
	WW12XX_CONF_SG_ACW_WWAN_ACTIVE_MASTEW_MIN_EDW,
	WW12XX_CONF_SG_ACW_WWAN_ACTIVE_MASTEW_MAX_EDW,
	WW12XX_CONF_SG_ACW_WWAN_ACTIVE_SWAVE_MIN_EDW,
	WW12XX_CONF_SG_ACW_WWAN_ACTIVE_SWAVE_MAX_EDW,

	WW12XX_CONF_SG_ACW_ACTIVE_SCAN_WWAN_BW,
	WW12XX_CONF_SG_ACW_ACTIVE_SCAN_WWAN_EDW,
	WW12XX_CONF_SG_ACW_PASSIVE_SCAN_BT_BW,
	WW12XX_CONF_SG_ACW_PASSIVE_SCAN_WWAN_BW,
	WW12XX_CONF_SG_ACW_PASSIVE_SCAN_BT_EDW,
	WW12XX_CONF_SG_ACW_PASSIVE_SCAN_WWAN_EDW,

	/*
	* Compensation pewcentage of pwobe wequests when scan initiated
	* duwing BT voice/ACW wink.
	*
	* Wange: 0 - 255 (%)
	*/
	WW12XX_CONF_SG_AUTO_SCAN_PWOBE_WEQ,

	/*
	* Compensation pewcentage of pwobe wequests when active scan initiated
	* duwing BT voice
	*
	* Wange: 0 - 255 (%)
	*/
	WW12XX_CONF_SG_ACTIVE_SCAN_DUWATION_FACTOW_HV3,

	/*
	* Compensation pewcentage of WWAN active scan window if initiated
	* duwing BT A2DP
	*
	* Wange: 0 - 1000 (%)
	*/
	WW12XX_CONF_SG_ACTIVE_SCAN_DUWATION_FACTOW_A2DP,

	/*
	* Compensation pewcentage of WWAN passive scan window if initiated
	* duwing BT A2DP BW
	*
	* Wange: 0 - 1000 (%)
	*/
	WW12XX_CONF_SG_PASSIVE_SCAN_DUW_FACTOW_A2DP_BW,

	/*
	* Compensation pewcentage of WWAN passive scan window if initiated
	* duwing BT A2DP EDW
	*
	* Wange: 0 - 1000 (%)
	*/
	WW12XX_CONF_SG_PASSIVE_SCAN_DUW_FACTOW_A2DP_EDW,

	/*
	* Compensation pewcentage of WWAN passive scan window if initiated
	* duwing BT voice
	*
	* Wange: 0 - 1000 (%)
	*/
	WW12XX_CONF_SG_PASSIVE_SCAN_DUW_FACTOW_HV3,

	/* TODO: expwain these vawues */
	WW12XX_CONF_SG_CONSECUTIVE_HV3_IN_PASSIVE_SCAN,
	WW12XX_CONF_SG_BCN_HV3_COWW_THW_IN_PASSIVE_SCAN,
	WW12XX_CONF_SG_TX_WX_PWOTECT_BW_IN_PASSIVE_SCAN,

	/*
	* Defines whethew the SG wiww fowce WWAN host to entew/exit PSM
	*
	* Wange: 1 - SG can fowce, 0 - host handwes PSM
	*/
	WW12XX_CONF_SG_STA_FOWCE_PS_IN_BT_SCO,

	/*
	* Defines antenna configuwation (singwe/duaw antenna)
	*
	* Wange: 0 - singwe antenna, 1 - duaw antenna
	*/
	WW12XX_CONF_SG_ANTENNA_CONFIGUWATION,

	/*
	* The thweshowd (pewcent) of max consecutive beacon misses befowe
	* incweasing pwiowity of beacon weception.
	*
	* Wange: 0 - 100 (%)
	*/
	WW12XX_CONF_SG_BEACON_MISS_PEWCENT,

	/*
	* Pwotection time of the DHCP pwoceduwe.
	*
	* Wange: 0 - 100000 (ms)
	*/
	WW12XX_CONF_SG_DHCP_TIME,

	/*
	* WX guawd time befowe the beginning of a new BT voice fwame duwing
	* which no new WWAN twiggew fwame is twansmitted.
	*
	* Wange: 0 - 100000 (us)
	*/
	WW12XX_CONF_SG_WXT,

	/*
	* TX guawd time befowe the beginning of a new BT voice fwame duwing
	* which no new WWAN fwame is twansmitted.
	*
	* Wange: 0 - 100000 (us)
	*/
	WW12XX_CONF_SG_TXT,

	/*
	* Enabwe adaptive WXT/TXT awgowithm. If disabwed, the host vawues
	* wiww be utiwized.
	*
	* Wange: 0 - disabwe, 1 - enabwe
	*/
	WW12XX_CONF_SG_ADAPTIVE_WXT_TXT,

	/* TODO: expwain this vawue */
	WW12XX_CONF_SG_GENEWAW_USAGE_BIT_MAP,

	/*
	* Numbew of consecutive BT voice fwames not intewwupted by WWAN
	*
	* Wange: 0 - 100
	*/
	WW12XX_CONF_SG_HV3_MAX_SEWVED,

	/*
	* The used WWAN wegacy sewvice pewiod duwing active BT ACW wink
	*
	* Wange: 0 - 255 (ms)
	*/
	WW12XX_CONF_SG_PS_POWW_TIMEOUT,

	/*
	* The used WWAN UPSD sewvice pewiod duwing active BT ACW wink
	*
	* Wange: 0 - 255 (ms)
	*/
	WW12XX_CONF_SG_UPSD_TIMEOUT,

	WW12XX_CONF_SG_CONSECUTIVE_CTS_THWESHOWD,
	WW12XX_CONF_SG_STA_WX_WINDOW_AFTEW_DTIM,
	WW12XX_CONF_SG_STA_CONNECTION_PWOTECTION_TIME,

	/* AP pawams */
	WW12XX_CONF_AP_BEACON_MISS_TX,
	WW12XX_CONF_AP_WX_WINDOW_AFTEW_BEACON,
	WW12XX_CONF_AP_BEACON_WINDOW_INTEWVAW,
	WW12XX_CONF_AP_CONNECTION_PWOTECTION_TIME,
	WW12XX_CONF_AP_BT_ACW_VAW_BT_SEWVE_TIME,
	WW12XX_CONF_AP_BT_ACW_VAW_WW_SEWVE_TIME,

	/* CTS Diwuting pawams */
	WW12XX_CONF_SG_CTS_DIWUTED_BAD_WX_PACKETS_TH,
	WW12XX_CONF_SG_CTS_CHOP_IN_DUAW_ANT_SCO_MASTEW,

	WW12XX_CONF_SG_TEMP_PAWAM_1,
	WW12XX_CONF_SG_TEMP_PAWAM_2,
	WW12XX_CONF_SG_TEMP_PAWAM_3,
	WW12XX_CONF_SG_TEMP_PAWAM_4,
	WW12XX_CONF_SG_TEMP_PAWAM_5,
	WW12XX_CONF_SG_TEMP_PAWAM_6,
	WW12XX_CONF_SG_TEMP_PAWAM_7,
	WW12XX_CONF_SG_TEMP_PAWAM_8,
	WW12XX_CONF_SG_TEMP_PAWAM_9,
	WW12XX_CONF_SG_TEMP_PAWAM_10,

	WW12XX_CONF_SG_PAWAMS_MAX,
	WW12XX_CONF_SG_PAWAMS_AWW = 0xff
};

#endif /* __WW12XX_CONF_H__ */
