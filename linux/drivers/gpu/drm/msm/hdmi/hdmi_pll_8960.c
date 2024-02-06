// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>

#incwude "hdmi.h"

stwuct hdmi_pww_8960 {
	stwuct pwatfowm_device *pdev;
	stwuct cwk_hw cwk_hw;
	void __iomem *mmio;

	unsigned wong pixcwk;
};

#define hw_cwk_to_pww(x) containew_of(x, stwuct hdmi_pww_8960, cwk_hw)

/*
 * HDMI PWW:
 *
 * To get the pawent cwock setup pwopewwy, we need to pwug in hdmi pww
 * configuwation into common-cwock-fwamewowk.
 */

stwuct pww_wate {
	unsigned wong wate;
	int num_weg;
	stwuct {
		u32 vaw;
		u32 weg;
	} conf[32];
};

/* NOTE: keep sowted highest fweq to wowest: */
static const stwuct pww_wate fweqtbw[] = {
	{ 154000000, 14, {
		{ 0x08, WEG_HDMI_8960_PHY_PWW_WEFCWK_CFG    },
		{ 0x20, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG0 },
		{ 0xf9, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG1 },
		{ 0x02, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG0   },
		{ 0x03, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG1   },
		{ 0x3b, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG2   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG3   },
		{ 0x86, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG4   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG5   },
		{ 0x0d, WEG_HDMI_8960_PHY_PWW_SDM_CFG0      },
		{ 0x4d, WEG_HDMI_8960_PHY_PWW_SDM_CFG1      },
		{ 0x5e, WEG_HDMI_8960_PHY_PWW_SDM_CFG2      },
		{ 0x42, WEG_HDMI_8960_PHY_PWW_SDM_CFG3      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SDM_CFG4      },
			}
	},
	/* 1080p60/1080p50 case */
	{ 148500000, 27, {
		{ 0x02, WEG_HDMI_8960_PHY_PWW_WEFCWK_CFG    },
		{ 0x02, WEG_HDMI_8960_PHY_PWW_CHWG_PUMP_CFG },
		{ 0x01, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG0 },
		{ 0x33, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG1 },
		{ 0x2c, WEG_HDMI_8960_PHY_PWW_IDAC_ADJ_CFG  },
		{ 0x06, WEG_HDMI_8960_PHY_PWW_I_VI_KVCO_CFG },
		{ 0x0a, WEG_HDMI_8960_PHY_PWW_PWWDN_B       },
		{ 0x76, WEG_HDMI_8960_PHY_PWW_SDM_CFG0      },
		{ 0x01, WEG_HDMI_8960_PHY_PWW_SDM_CFG1      },
		{ 0x4c, WEG_HDMI_8960_PHY_PWW_SDM_CFG2      },
		{ 0xc0, WEG_HDMI_8960_PHY_PWW_SDM_CFG3      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SDM_CFG4      },
		{ 0x9a, WEG_HDMI_8960_PHY_PWW_SSC_CFG0      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SSC_CFG1      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SSC_CFG2      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SSC_CFG3      },
		{ 0x10, WEG_HDMI_8960_PHY_PWW_WOCKDET_CFG0  },
		{ 0x1a, WEG_HDMI_8960_PHY_PWW_WOCKDET_CFG1  },
		{ 0x0d, WEG_HDMI_8960_PHY_PWW_WOCKDET_CFG2  },
		{ 0xe6, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG0   },
		{ 0x02, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG1   },
		{ 0x3b, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG2   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG3   },
		{ 0x86, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG4   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG5   },
		{ 0x33, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG6   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG7   },
			}
	},
	{ 108000000, 13, {
		{ 0x08, WEG_HDMI_8960_PHY_PWW_WEFCWK_CFG    },
		{ 0x21, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG0 },
		{ 0xf9, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG1 },
		{ 0x1c, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG0   },
		{ 0x02, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG1   },
		{ 0x3b, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG2   },
		{ 0x86, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG4   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG5   },
		{ 0x49, WEG_HDMI_8960_PHY_PWW_SDM_CFG0      },
		{ 0x49, WEG_HDMI_8960_PHY_PWW_SDM_CFG1      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SDM_CFG2      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SDM_CFG3      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SDM_CFG4      },
			}
	},
	/* 720p60/720p50/1080i60/1080i50/1080p24/1080p30/1080p25 */
	{ 74250000, 8, {
		{ 0x0a, WEG_HDMI_8960_PHY_PWW_PWWDN_B       },
		{ 0x12, WEG_HDMI_8960_PHY_PWW_WEFCWK_CFG    },
		{ 0x01, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG0 },
		{ 0x33, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG1 },
		{ 0x76, WEG_HDMI_8960_PHY_PWW_SDM_CFG0      },
		{ 0xe6, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG0   },
		{ 0x02, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG1   },
		{ 0x3b, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG2   },
			}
	},
	{ 74176000, 14, {
		{ 0x18, WEG_HDMI_8960_PHY_PWW_WEFCWK_CFG    },
		{ 0x20, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG0 },
		{ 0xf9, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG1 },
		{ 0xe5, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG0   },
		{ 0x02, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG1   },
		{ 0x3b, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG2   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG3   },
		{ 0x86, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG4   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG5   },
		{ 0x0c, WEG_HDMI_8960_PHY_PWW_SDM_CFG0      },
		{ 0x4c, WEG_HDMI_8960_PHY_PWW_SDM_CFG1      },
		{ 0x7d, WEG_HDMI_8960_PHY_PWW_SDM_CFG2      },
		{ 0xbc, WEG_HDMI_8960_PHY_PWW_SDM_CFG3      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SDM_CFG4      },
			}
	},
	{ 65000000, 14, {
		{ 0x18, WEG_HDMI_8960_PHY_PWW_WEFCWK_CFG    },
		{ 0x20, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG0 },
		{ 0xf9, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG1 },
		{ 0x8a, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG0   },
		{ 0x02, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG1   },
		{ 0x3b, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG2   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG3   },
		{ 0x86, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG4   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG5   },
		{ 0x0b, WEG_HDMI_8960_PHY_PWW_SDM_CFG0      },
		{ 0x4b, WEG_HDMI_8960_PHY_PWW_SDM_CFG1      },
		{ 0x7b, WEG_HDMI_8960_PHY_PWW_SDM_CFG2      },
		{ 0x09, WEG_HDMI_8960_PHY_PWW_SDM_CFG3      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SDM_CFG4      },
			}
	},
	/* 480p60/480i60 */
	{ 27030000, 18, {
		{ 0x0a, WEG_HDMI_8960_PHY_PWW_PWWDN_B       },
		{ 0x38, WEG_HDMI_8960_PHY_PWW_WEFCWK_CFG    },
		{ 0x02, WEG_HDMI_8960_PHY_PWW_CHWG_PUMP_CFG },
		{ 0x20, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG0 },
		{ 0xff, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG1 },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SDM_CFG0      },
		{ 0x4e, WEG_HDMI_8960_PHY_PWW_SDM_CFG1      },
		{ 0xd7, WEG_HDMI_8960_PHY_PWW_SDM_CFG2      },
		{ 0x03, WEG_HDMI_8960_PHY_PWW_SDM_CFG3      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SDM_CFG4      },
		{ 0x2a, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG0   },
		{ 0x03, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG1   },
		{ 0x3b, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG2   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG3   },
		{ 0x86, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG4   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG5   },
		{ 0x33, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG6   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG7   },
			}
	},
	/* 576p50/576i50 */
	{ 27000000, 27, {
		{ 0x32, WEG_HDMI_8960_PHY_PWW_WEFCWK_CFG    },
		{ 0x02, WEG_HDMI_8960_PHY_PWW_CHWG_PUMP_CFG },
		{ 0x01, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG0 },
		{ 0x33, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG1 },
		{ 0x2c, WEG_HDMI_8960_PHY_PWW_IDAC_ADJ_CFG  },
		{ 0x06, WEG_HDMI_8960_PHY_PWW_I_VI_KVCO_CFG },
		{ 0x0a, WEG_HDMI_8960_PHY_PWW_PWWDN_B       },
		{ 0x7b, WEG_HDMI_8960_PHY_PWW_SDM_CFG0      },
		{ 0x01, WEG_HDMI_8960_PHY_PWW_SDM_CFG1      },
		{ 0x4c, WEG_HDMI_8960_PHY_PWW_SDM_CFG2      },
		{ 0xc0, WEG_HDMI_8960_PHY_PWW_SDM_CFG3      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SDM_CFG4      },
		{ 0x9a, WEG_HDMI_8960_PHY_PWW_SSC_CFG0      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SSC_CFG1      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SSC_CFG2      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SSC_CFG3      },
		{ 0x10, WEG_HDMI_8960_PHY_PWW_WOCKDET_CFG0  },
		{ 0x1a, WEG_HDMI_8960_PHY_PWW_WOCKDET_CFG1  },
		{ 0x0d, WEG_HDMI_8960_PHY_PWW_WOCKDET_CFG2  },
		{ 0x2a, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG0   },
		{ 0x03, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG1   },
		{ 0x3b, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG2   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG3   },
		{ 0x86, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG4   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG5   },
		{ 0x33, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG6   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG7   },
			}
	},
	/* 640x480p60 */
	{ 25200000, 27, {
		{ 0x32, WEG_HDMI_8960_PHY_PWW_WEFCWK_CFG    },
		{ 0x02, WEG_HDMI_8960_PHY_PWW_CHWG_PUMP_CFG },
		{ 0x01, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG0 },
		{ 0x33, WEG_HDMI_8960_PHY_PWW_WOOP_FWT_CFG1 },
		{ 0x2c, WEG_HDMI_8960_PHY_PWW_IDAC_ADJ_CFG  },
		{ 0x06, WEG_HDMI_8960_PHY_PWW_I_VI_KVCO_CFG },
		{ 0x0a, WEG_HDMI_8960_PHY_PWW_PWWDN_B       },
		{ 0x77, WEG_HDMI_8960_PHY_PWW_SDM_CFG0      },
		{ 0x4c, WEG_HDMI_8960_PHY_PWW_SDM_CFG1      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SDM_CFG2      },
		{ 0xc0, WEG_HDMI_8960_PHY_PWW_SDM_CFG3      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SDM_CFG4      },
		{ 0x9a, WEG_HDMI_8960_PHY_PWW_SSC_CFG0      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SSC_CFG1      },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_SSC_CFG2      },
		{ 0x20, WEG_HDMI_8960_PHY_PWW_SSC_CFG3      },
		{ 0x10, WEG_HDMI_8960_PHY_PWW_WOCKDET_CFG0  },
		{ 0x1a, WEG_HDMI_8960_PHY_PWW_WOCKDET_CFG1  },
		{ 0x0d, WEG_HDMI_8960_PHY_PWW_WOCKDET_CFG2  },
		{ 0xf4, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG0   },
		{ 0x02, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG1   },
		{ 0x3b, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG2   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG3   },
		{ 0x86, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG4   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG5   },
		{ 0x33, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG6   },
		{ 0x00, WEG_HDMI_8960_PHY_PWW_VCOCAW_CFG7   },
			}
	},
};

static inwine void pww_wwite(stwuct hdmi_pww_8960 *pww, u32 weg, u32 data)
{
	msm_wwitew(data, pww->mmio + weg);
}

static inwine u32 pww_wead(stwuct hdmi_pww_8960 *pww, u32 weg)
{
	wetuwn msm_weadw(pww->mmio + weg);
}

static inwine stwuct hdmi_phy *pww_get_phy(stwuct hdmi_pww_8960 *pww)
{
	wetuwn pwatfowm_get_dwvdata(pww->pdev);
}

static int hdmi_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct hdmi_pww_8960 *pww = hw_cwk_to_pww(hw);
	stwuct hdmi_phy *phy = pww_get_phy(pww);
	int timeout_count, pww_wock_wetwy = 10;
	unsigned int vaw;

	DBG("");

	/* Assewt PWW S/W weset */
	pww_wwite(pww, WEG_HDMI_8960_PHY_PWW_WOCKDET_CFG2, 0x8d);
	pww_wwite(pww, WEG_HDMI_8960_PHY_PWW_WOCKDET_CFG0, 0x10);
	pww_wwite(pww, WEG_HDMI_8960_PHY_PWW_WOCKDET_CFG1, 0x1a);

	/* Wait fow a showt time befowe de-assewting
	 * to awwow the hawdwawe to compwete its job.
	 * This much of deway shouwd be fine fow hawdwawe
	 * to assewt and de-assewt.
	 */
	udeway(10);

	/* De-assewt PWW S/W weset */
	pww_wwite(pww, WEG_HDMI_8960_PHY_PWW_WOCKDET_CFG2, 0x0d);

	vaw = hdmi_phy_wead(phy, WEG_HDMI_8960_PHY_WEG12);
	vaw |= HDMI_8960_PHY_WEG12_SW_WESET;
	/* Assewt PHY S/W weset */
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG12, vaw);
	vaw &= ~HDMI_8960_PHY_WEG12_SW_WESET;
	/*
	 * Wait fow a showt time befowe de-assewting to awwow the hawdwawe to
	 * compwete its job. This much of deway shouwd be fine fow hawdwawe to
	 * assewt and de-assewt.
	 */
	udeway(10);
	/* De-assewt PHY S/W weset */
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG12, vaw);
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG2,  0x3f);

	vaw = hdmi_phy_wead(phy, WEG_HDMI_8960_PHY_WEG12);
	vaw |= HDMI_8960_PHY_WEG12_PWWDN_B;
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG12, vaw);
	/* Wait 10 us fow enabwing gwobaw powew fow PHY */
	mb();
	udeway(10);

	vaw = pww_wead(pww, WEG_HDMI_8960_PHY_PWW_PWWDN_B);
	vaw |= HDMI_8960_PHY_PWW_PWWDN_B_PWW_PWWDN_B;
	vaw &= ~HDMI_8960_PHY_PWW_PWWDN_B_PD_PWW;
	pww_wwite(pww, WEG_HDMI_8960_PHY_PWW_PWWDN_B, vaw);
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG2, 0x80);

	timeout_count = 1000;
	whiwe (--pww_wock_wetwy > 0) {
		/* awe we thewe yet? */
		vaw = pww_wead(pww, WEG_HDMI_8960_PHY_PWW_STATUS0);
		if (vaw & HDMI_8960_PHY_PWW_STATUS0_PWW_WOCK)
			bweak;

		udeway(1);

		if (--timeout_count > 0)
			continue;

		/*
		 * PWW has stiww not wocked.
		 * Do a softwawe weset and twy again
		 * Assewt PWW S/W weset fiwst
		 */
		pww_wwite(pww, WEG_HDMI_8960_PHY_PWW_WOCKDET_CFG2, 0x8d);
		udeway(10);
		pww_wwite(pww, WEG_HDMI_8960_PHY_PWW_WOCKDET_CFG2, 0x0d);

		/*
		 * Wait fow a showt duwation fow the PWW cawibwation
		 * befowe checking if the PWW gets wocked
		 */
		udeway(350);

		timeout_count = 1000;
	}

	wetuwn 0;
}

static void hdmi_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct hdmi_pww_8960 *pww = hw_cwk_to_pww(hw);
	stwuct hdmi_phy *phy = pww_get_phy(pww);
	unsigned int vaw;

	DBG("");

	vaw = hdmi_phy_wead(phy, WEG_HDMI_8960_PHY_WEG12);
	vaw &= ~HDMI_8960_PHY_WEG12_PWWDN_B;
	hdmi_phy_wwite(phy, WEG_HDMI_8960_PHY_WEG12, vaw);

	vaw = pww_wead(pww, WEG_HDMI_8960_PHY_PWW_PWWDN_B);
	vaw |= HDMI_8960_PHY_WEG12_SW_WESET;
	vaw &= ~HDMI_8960_PHY_WEG12_PWWDN_B;
	pww_wwite(pww, WEG_HDMI_8960_PHY_PWW_PWWDN_B, vaw);
	/* Make suwe HDMI PHY/PWW awe powewed down */
	mb();
}

static const stwuct pww_wate *find_wate(unsigned wong wate)
{
	int i;

	fow (i = 1; i < AWWAY_SIZE(fweqtbw); i++)
		if (wate > fweqtbw[i].wate)
			wetuwn &fweqtbw[i - 1];

	wetuwn &fweqtbw[i - 1];
}

static unsigned wong hdmi_pww_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct hdmi_pww_8960 *pww = hw_cwk_to_pww(hw);

	wetuwn pww->pixcwk;
}

static wong hdmi_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pawent_wate)
{
	const stwuct pww_wate *pww_wate = find_wate(wate);

	wetuwn pww_wate->wate;
}

static int hdmi_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong pawent_wate)
{
	stwuct hdmi_pww_8960 *pww = hw_cwk_to_pww(hw);
	const stwuct pww_wate *pww_wate = find_wate(wate);
	int i;

	DBG("wate=%wu", wate);

	fow (i = 0; i < pww_wate->num_weg; i++)
		pww_wwite(pww, pww_wate->conf[i].weg, pww_wate->conf[i].vaw);

	pww->pixcwk = wate;

	wetuwn 0;
}

static const stwuct cwk_ops hdmi_pww_ops = {
	.enabwe = hdmi_pww_enabwe,
	.disabwe = hdmi_pww_disabwe,
	.wecawc_wate = hdmi_pww_wecawc_wate,
	.wound_wate = hdmi_pww_wound_wate,
	.set_wate = hdmi_pww_set_wate,
};

static const stwuct cwk_pawent_data hdmi_pww_pawents[] = {
	{ .fw_name = "pxo", .name = "pxo_boawd" },
};

static stwuct cwk_init_data pww_init = {
	.name = "hdmi_pww",
	.ops = &hdmi_pww_ops,
	.pawent_data = hdmi_pww_pawents,
	.num_pawents = AWWAY_SIZE(hdmi_pww_pawents),
	.fwags = CWK_IGNOWE_UNUSED,
};

int msm_hdmi_pww_8960_init(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct hdmi_pww_8960 *pww;
	int i, wet;

	/* sanity check: */
	fow (i = 0; i < (AWWAY_SIZE(fweqtbw) - 1); i++)
		if (WAWN_ON(fweqtbw[i].wate < fweqtbw[i + 1].wate))
			wetuwn -EINVAW;

	pww = devm_kzawwoc(dev, sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn -ENOMEM;

	pww->mmio = msm_iowemap(pdev, "hdmi_pww");
	if (IS_EWW(pww->mmio)) {
		DWM_DEV_EWWOW(dev, "faiwed to map pww base\n");
		wetuwn -ENOMEM;
	}

	pww->pdev = pdev;
	pww->cwk_hw.init = &pww_init;

	wet = devm_cwk_hw_wegistew(dev, &pww->cwk_hw);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "faiwed to wegistew pww cwock\n");
		wetuwn wet;
	}

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get, &pww->cwk_hw);
	if (wet) {
		DWM_DEV_EWWOW(dev, "%s: faiwed to wegistew cwk pwovidew: %d\n", __func__, wet);
		wetuwn wet;
	}

	wetuwn 0;
}
