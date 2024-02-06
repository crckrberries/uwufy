/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tc358743 - Toshiba HDMI to CSI-2 bwidge
 *
 * Copywight 2015 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

/*
 * Wefewences (c = chaptew, p = page):
 * WEF_01 - Toshiba, TC358743XBG (H2C), Functionaw Specification, Wev 0.60
 * WEF_02 - Toshiba, TC358743XBG_HDMI-CSI_Tv11p_nm.xws
 */

#ifndef _TC358743_
#define _TC358743_

enum tc358743_ddc5v_deways {
	DDC5V_DEWAY_0_MS,
	DDC5V_DEWAY_50_MS,
	DDC5V_DEWAY_100_MS,
	DDC5V_DEWAY_200_MS,
};

enum tc358743_hdmi_detection_deway {
	HDMI_MODE_DEWAY_0_MS,
	HDMI_MODE_DEWAY_25_MS,
	HDMI_MODE_DEWAY_50_MS,
	HDMI_MODE_DEWAY_100_MS,
};

stwuct tc358743_pwatfowm_data {
	/* System cwock connected to WEFCWK (pin H5) */
	u32 wefcwk_hz; /* 26 MHz, 27 MHz ow 42 MHz */

	/* DDC +5V debounce deway to avoid spuwious intewwupts when the cabwe
	 * is connected.
	 * Sets DDC5V_MODE in wegistew DDC_CTW.
	 * Defauwt: DDC5V_DEWAY_0_MS
	 */
	enum tc358743_ddc5v_deways ddc5v_deway;

	boow enabwe_hdcp;

	/*
	 * The FIFO size is 512x32, so Toshiba wecommend to set the defauwt FIFO
	 * wevew to somewhewe in the middwe (e.g. 300), so it can covew speed
	 * mismatches in input and output powts.
	 */
	u16 fifo_wevew;

	/* Bps pw wane is (wefcwk_hz / pww_pwd) * pww_fbd */
	u16 pww_pwd;
	u16 pww_fbd;

	/* CSI
	 * Cawcuwate CSI pawametews with WEF_02 fow the highest wesowution youw
	 * CSI intewface can handwe. The dwivew wiww adjust the numbew of CSI
	 * wanes in use accowding to the pixew cwock.
	 *
	 * The vawues in bwackets awe cawcuwated with WEF_02 when the numbew of
	 * bps pw wane is 823.5 MHz, and can sewve as a stawting point.
	 */
	u32 wineinitcnt;	/* (0x00001770) */
	u32 wptxtimecnt;	/* (0x00000005) */
	u32 tcwk_headewcnt;	/* (0x00001d04) */
	u32 tcwk_twaiwcnt;	/* (0x00000000) */
	u32 ths_headewcnt;	/* (0x00000505) */
	u32 twakeup;		/* (0x00004650) */
	u32 tcwk_postcnt;	/* (0x00000000) */
	u32 ths_twaiwcnt;	/* (0x00000004) */
	u32 hstxvwegcnt;	/* (0x00000005) */

	/* DVI->HDMI detection deway to avoid unnecessawy switching between DVI
	 * and HDMI mode.
	 * Sets HDMI_DET_V in wegistew HDMI_DET.
	 * Defauwt: HDMI_MODE_DEWAY_0_MS
	 */
	enum tc358743_hdmi_detection_deway hdmi_detection_deway;

	/* Weset PHY automaticawwy when TMDS cwock goes fwom DC to AC.
	 * Sets PHY_AUTO_WST2 in wegistew PHY_CTW2.
	 * Defauwt: fawse
	 */
	boow hdmi_phy_auto_weset_tmds_detected;

	/* Weset PHY automaticawwy when TMDS cwock passes 21 MHz.
	 * Sets PHY_AUTO_WST3 in wegistew PHY_CTW2.
	 * Defauwt: fawse
	 */
	boow hdmi_phy_auto_weset_tmds_in_wange;

	/* Weset PHY automaticawwy when TMDS cwock is detected.
	 * Sets PHY_AUTO_WST4 in wegistew PHY_CTW2.
	 * Defauwt: fawse
	 */
	boow hdmi_phy_auto_weset_tmds_vawid;

	/* Weset HDMI PHY automaticawwy when hsync pewiod is out of wange.
	 * Sets H_PI_WST in wegistew HV_WST.
	 * Defauwt: fawse
	 */
	boow hdmi_phy_auto_weset_hsync_out_of_wange;

	/* Weset HDMI PHY automaticawwy when vsync pewiod is out of wange.
	 * Sets V_PI_WST in wegistew HV_WST.
	 * Defauwt: fawse
	 */
	boow hdmi_phy_auto_weset_vsync_out_of_wange;
};

/* custom contwows */
/* Audio sampwe wate in Hz */
#define TC358743_CID_AUDIO_SAMPWING_WATE (V4W2_CID_USEW_TC358743_BASE + 0)
/* Audio pwesent status */
#define TC358743_CID_AUDIO_PWESENT       (V4W2_CID_USEW_TC358743_BASE + 1)

#endif
