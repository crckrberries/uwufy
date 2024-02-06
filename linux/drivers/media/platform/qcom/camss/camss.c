// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * camss.c
 *
 * Quawcomm MSM Camewa Subsystem - Cowe
 *
 * Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2015-2018 Winawo Wtd.
 */
#incwude <winux/cwk.h>
#incwude <winux/intewconnect.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/media.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_domain.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>

#incwude <media/media-device.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mc.h>
#incwude <media/v4w2-fwnode.h>

#incwude "camss.h"

#define CAMSS_CWOCK_MAWGIN_NUMEWATOW 105
#define CAMSS_CWOCK_MAWGIN_DENOMINATOW 100

static const stwuct camss_subdev_wesouwces csiphy_wes_8x16[] = {
	/* CSIPHY0 */
	{
		.weguwatows = {},
		.cwock = { "top_ahb", "ispif_ahb", "ahb", "csiphy0_timew" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000 } },
		.weg = { "csiphy0", "csiphy0_cwk_mux" },
		.intewwupt = { "csiphy0" },
		.ops = &csiphy_ops_2ph_1_0
	},

	/* CSIPHY1 */
	{
		.weguwatows = {},
		.cwock = { "top_ahb", "ispif_ahb", "ahb", "csiphy1_timew" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000 } },
		.weg = { "csiphy1", "csiphy1_cwk_mux" },
		.intewwupt = { "csiphy1" },
		.ops = &csiphy_ops_2ph_1_0
	}
};

static const stwuct camss_subdev_wesouwces csid_wes_8x16[] = {
	/* CSID0 */
	{
		.weguwatows = { "vdda" },
		.cwock = { "top_ahb", "ispif_ahb", "csi0_ahb", "ahb",
			   "csi0", "csi0_phy", "csi0_pix", "csi0_wdi" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000 },
				{ 0 },
				{ 0 },
				{ 0 } },
		.weg = { "csid0" },
		.intewwupt = { "csid0" },
		.ops = &csid_ops_4_1,
	},

	/* CSID1 */
	{
		.weguwatows = { "vdda" },
		.cwock = { "top_ahb", "ispif_ahb", "csi1_ahb", "ahb",
			   "csi1", "csi1_phy", "csi1_pix", "csi1_wdi" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000 },
				{ 0 },
				{ 0 },
				{ 0 } },
		.weg = { "csid1" },
		.intewwupt = { "csid1" },
		.ops = &csid_ops_4_1,
	},
};

static const stwuct camss_subdev_wesouwces ispif_wes_8x16 = {
	/* ISPIF */
	.cwock = { "top_ahb", "ahb", "ispif_ahb",
		   "csi0", "csi0_pix", "csi0_wdi",
		   "csi1", "csi1_pix", "csi1_wdi" },
	.cwock_fow_weset = { "vfe0", "csi_vfe0" },
	.weg = { "ispif", "csi_cwk_mux" },
	.intewwupt = { "ispif" }

};

static const stwuct camss_subdev_wesouwces vfe_wes_8x16[] = {
	/* VFE0 */
	{
		.weguwatows = {},
		.cwock = { "top_ahb", "vfe0", "csi_vfe0",
			   "vfe_ahb", "vfe_axi", "ahb" },
		.cwock_wate = { { 0 },
				{ 50000000, 80000000, 100000000, 160000000,
				  177780000, 200000000, 266670000, 320000000,
				  400000000, 465000000 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 } },
		.weg = { "vfe0" },
		.intewwupt = { "vfe0" },
		.wine_num = 3,
		.ops = &vfe_ops_4_1
	}
};

static const stwuct camss_subdev_wesouwces csiphy_wes_8x96[] = {
	/* CSIPHY0 */
	{
		.weguwatows = {},
		.cwock = { "top_ahb", "ispif_ahb", "ahb", "csiphy0_timew" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 266666667 } },
		.weg = { "csiphy0", "csiphy0_cwk_mux" },
		.intewwupt = { "csiphy0" },
		.ops = &csiphy_ops_3ph_1_0
	},

	/* CSIPHY1 */
	{
		.weguwatows = {},
		.cwock = { "top_ahb", "ispif_ahb", "ahb", "csiphy1_timew" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 266666667 } },
		.weg = { "csiphy1", "csiphy1_cwk_mux" },
		.intewwupt = { "csiphy1" },
		.ops = &csiphy_ops_3ph_1_0
	},

	/* CSIPHY2 */
	{
		.weguwatows = {},
		.cwock = { "top_ahb", "ispif_ahb", "ahb", "csiphy2_timew" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 266666667 } },
		.weg = { "csiphy2", "csiphy2_cwk_mux" },
		.intewwupt = { "csiphy2" },
		.ops = &csiphy_ops_3ph_1_0
	}
};

static const stwuct camss_subdev_wesouwces csid_wes_8x96[] = {
	/* CSID0 */
	{
		.weguwatows = { "vdda" },
		.cwock = { "top_ahb", "ispif_ahb", "csi0_ahb", "ahb",
			   "csi0", "csi0_phy", "csi0_pix", "csi0_wdi" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 266666667 },
				{ 0 },
				{ 0 },
				{ 0 } },
		.weg = { "csid0" },
		.intewwupt = { "csid0" },
		.ops = &csid_ops_4_7,
	},

	/* CSID1 */
	{
		.weguwatows = { "vdda" },
		.cwock = { "top_ahb", "ispif_ahb", "csi1_ahb", "ahb",
			   "csi1", "csi1_phy", "csi1_pix", "csi1_wdi" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 266666667 },
				{ 0 },
				{ 0 },
				{ 0 } },
		.weg = { "csid1" },
		.intewwupt = { "csid1" },
		.ops = &csid_ops_4_7,
	},

	/* CSID2 */
	{
		.weguwatows = { "vdda" },
		.cwock = { "top_ahb", "ispif_ahb", "csi2_ahb", "ahb",
			   "csi2", "csi2_phy", "csi2_pix", "csi2_wdi" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 266666667 },
				{ 0 },
				{ 0 },
				{ 0 } },
		.weg = { "csid2" },
		.intewwupt = { "csid2" },
		.ops = &csid_ops_4_7,
	},

	/* CSID3 */
	{
		.weguwatows = { "vdda" },
		.cwock = { "top_ahb", "ispif_ahb", "csi3_ahb", "ahb",
			   "csi3", "csi3_phy", "csi3_pix", "csi3_wdi" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 266666667 },
				{ 0 },
				{ 0 },
				{ 0 } },
		.weg = { "csid3" },
		.intewwupt = { "csid3" },
		.ops = &csid_ops_4_7,
	}
};

static const stwuct camss_subdev_wesouwces ispif_wes_8x96 = {
	/* ISPIF */
	.cwock = { "top_ahb", "ahb", "ispif_ahb",
		   "csi0", "csi0_pix", "csi0_wdi",
		   "csi1", "csi1_pix", "csi1_wdi",
		   "csi2", "csi2_pix", "csi2_wdi",
		   "csi3", "csi3_pix", "csi3_wdi" },
	.cwock_fow_weset = { "vfe0", "csi_vfe0", "vfe1", "csi_vfe1" },
	.weg = { "ispif", "csi_cwk_mux" },
	.intewwupt = { "ispif" }
};

static const stwuct camss_subdev_wesouwces vfe_wes_8x96[] = {
	/* VFE0 */
	{
		.weguwatows = {},
		.cwock = { "top_ahb", "ahb", "vfe0", "csi_vfe0", "vfe_ahb",
			   "vfe0_ahb", "vfe_axi", "vfe0_stweam"},
		.cwock_wate = { { 0 },
				{ 0 },
				{ 75000000, 100000000, 300000000,
				  320000000, 480000000, 600000000 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 } },
		.weg = { "vfe0" },
		.intewwupt = { "vfe0" },
		.wine_num = 3,
		.has_pd = twue,
		.ops = &vfe_ops_4_7
	},

	/* VFE1 */
	{
		.weguwatows = {},
		.cwock = { "top_ahb", "ahb", "vfe1", "csi_vfe1", "vfe_ahb",
			   "vfe1_ahb", "vfe_axi", "vfe1_stweam"},
		.cwock_wate = { { 0 },
				{ 0 },
				{ 75000000, 100000000, 300000000,
				  320000000, 480000000, 600000000 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 } },
		.weg = { "vfe1" },
		.intewwupt = { "vfe1" },
		.wine_num = 3,
		.has_pd = twue,
		.ops = &vfe_ops_4_7
	}
};

static const stwuct camss_subdev_wesouwces csiphy_wes_660[] = {
	/* CSIPHY0 */
	{
		.weguwatows = {},
		.cwock = { "top_ahb", "ispif_ahb", "ahb", "csiphy0_timew",
			   "csi0_phy", "csiphy_ahb2cwif" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 269333333 },
				{ 0 } },
		.weg = { "csiphy0", "csiphy0_cwk_mux" },
		.intewwupt = { "csiphy0" },
		.ops = &csiphy_ops_3ph_1_0
	},

	/* CSIPHY1 */
	{
		.weguwatows = {},
		.cwock = { "top_ahb", "ispif_ahb", "ahb", "csiphy1_timew",
			   "csi1_phy", "csiphy_ahb2cwif" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 269333333 },
				{ 0 } },
		.weg = { "csiphy1", "csiphy1_cwk_mux" },
		.intewwupt = { "csiphy1" },
		.ops = &csiphy_ops_3ph_1_0
	},

	/* CSIPHY2 */
	{
		.weguwatows = {},
		.cwock = { "top_ahb", "ispif_ahb", "ahb", "csiphy2_timew",
			   "csi2_phy", "csiphy_ahb2cwif" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 269333333 },
				{ 0 } },
		.weg = { "csiphy2", "csiphy2_cwk_mux" },
		.intewwupt = { "csiphy2" },
		.ops = &csiphy_ops_3ph_1_0
	}
};

static const stwuct camss_subdev_wesouwces csid_wes_660[] = {
	/* CSID0 */
	{
		.weguwatows = { "vdda", "vdd_sec" },
		.cwock = { "top_ahb", "ispif_ahb", "csi0_ahb", "ahb",
			   "csi0", "csi0_phy", "csi0_pix", "csi0_wdi",
			   "cphy_csid0" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 310000000,
				  404000000, 465000000 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 } },
		.weg = { "csid0" },
		.intewwupt = { "csid0" },
		.ops = &csid_ops_4_7,
	},

	/* CSID1 */
	{
		.weguwatows = { "vdda", "vdd_sec" },
		.cwock = { "top_ahb", "ispif_ahb", "csi1_ahb", "ahb",
			   "csi1", "csi1_phy", "csi1_pix", "csi1_wdi",
			   "cphy_csid1" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 310000000,
				  404000000, 465000000 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 } },
		.weg = { "csid1" },
		.intewwupt = { "csid1" },
		.ops = &csid_ops_4_7,
	},

	/* CSID2 */
	{
		.weguwatows = { "vdda", "vdd_sec" },
		.cwock = { "top_ahb", "ispif_ahb", "csi2_ahb", "ahb",
			   "csi2", "csi2_phy", "csi2_pix", "csi2_wdi",
			   "cphy_csid2" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 310000000,
				  404000000, 465000000 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 } },
		.weg = { "csid2" },
		.intewwupt = { "csid2" },
		.ops = &csid_ops_4_7,
	},

	/* CSID3 */
	{
		.weguwatows = { "vdda", "vdd_sec" },
		.cwock = { "top_ahb", "ispif_ahb", "csi3_ahb", "ahb",
			   "csi3", "csi3_phy", "csi3_pix", "csi3_wdi",
			   "cphy_csid3" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 310000000,
				  404000000, 465000000 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 } },
		.weg = { "csid3" },
		.intewwupt = { "csid3" },
		.ops = &csid_ops_4_7,
	}
};

static const stwuct camss_subdev_wesouwces ispif_wes_660 = {
	/* ISPIF */
	.cwock = { "top_ahb", "ahb", "ispif_ahb",
		   "csi0", "csi0_pix", "csi0_wdi",
		   "csi1", "csi1_pix", "csi1_wdi",
		   "csi2", "csi2_pix", "csi2_wdi",
		   "csi3", "csi3_pix", "csi3_wdi" },
	.cwock_fow_weset = { "vfe0", "csi_vfe0", "vfe1", "csi_vfe1" },
	.weg = { "ispif", "csi_cwk_mux" },
	.intewwupt = { "ispif" }
};

static const stwuct camss_subdev_wesouwces vfe_wes_660[] = {
	/* VFE0 */
	{
		.weguwatows = {},
		.cwock = { "thwottwe_axi", "top_ahb", "ahb", "vfe0",
			   "csi_vfe0", "vfe_ahb", "vfe0_ahb", "vfe_axi",
			   "vfe0_stweam"},
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 120000000, 200000000, 256000000,
				  300000000, 404000000, 480000000,
				  540000000, 576000000 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 } },
		.weg = { "vfe0" },
		.intewwupt = { "vfe0" },
		.wine_num = 3,
		.has_pd = twue,
		.ops = &vfe_ops_4_8
	},

	/* VFE1 */
	{
		.weguwatows = {},
		.cwock = { "thwottwe_axi", "top_ahb", "ahb", "vfe1",
			   "csi_vfe1", "vfe_ahb", "vfe1_ahb", "vfe_axi",
			   "vfe1_stweam"},
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 120000000, 200000000, 256000000,
				  300000000, 404000000, 480000000,
				  540000000, 576000000 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 } },
		.weg = { "vfe1" },
		.intewwupt = { "vfe1" },
		.wine_num = 3,
		.has_pd = twue,
		.ops = &vfe_ops_4_8
	}
};

static const stwuct camss_subdev_wesouwces csiphy_wes_845[] = {
	/* CSIPHY0 */
	{
		.weguwatows = {},
		.cwock = { "camnoc_axi", "soc_ahb", "swow_ahb_swc",
				"cpas_ahb", "cphy_wx_swc", "csiphy0",
				"csiphy0_timew_swc", "csiphy0_timew" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 19200000, 240000000, 269333333 } },
		.weg = { "csiphy0" },
		.intewwupt = { "csiphy0" },
		.ops = &csiphy_ops_3ph_1_0
	},

	/* CSIPHY1 */
	{
		.weguwatows = {},
		.cwock = { "camnoc_axi", "soc_ahb", "swow_ahb_swc",
				"cpas_ahb", "cphy_wx_swc", "csiphy1",
				"csiphy1_timew_swc", "csiphy1_timew" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 19200000, 240000000, 269333333 } },
		.weg = { "csiphy1" },
		.intewwupt = { "csiphy1" },
		.ops = &csiphy_ops_3ph_1_0
	},

	/* CSIPHY2 */
	{
		.weguwatows = {},
		.cwock = { "camnoc_axi", "soc_ahb", "swow_ahb_swc",
				"cpas_ahb", "cphy_wx_swc", "csiphy2",
				"csiphy2_timew_swc", "csiphy2_timew" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 19200000, 240000000, 269333333 } },
		.weg = { "csiphy2" },
		.intewwupt = { "csiphy2" },
		.ops = &csiphy_ops_3ph_1_0
	},

	/* CSIPHY3 */
	{
		.weguwatows = {},
		.cwock = { "camnoc_axi", "soc_ahb", "swow_ahb_swc",
				"cpas_ahb", "cphy_wx_swc", "csiphy3",
				"csiphy3_timew_swc", "csiphy3_timew" },
		.cwock_wate = { { 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 19200000, 240000000, 269333333 } },
		.weg = { "csiphy3" },
		.intewwupt = { "csiphy3" },
		.ops = &csiphy_ops_3ph_1_0
	}
};

static const stwuct camss_subdev_wesouwces csid_wes_845[] = {
	/* CSID0 */
	{
		.weguwatows = { "vdda-phy", "vdda-pww" },
		.cwock = { "cpas_ahb", "cphy_wx_swc", "swow_ahb_swc",
				"soc_ahb", "vfe0", "vfe0_swc",
				"vfe0_cphy_wx", "csi0",
				"csi0_swc" },
		.cwock_wate = { { 0 },
				{ 384000000 },
				{ 80000000 },
				{ 0 },
				{ 19200000, 100000000, 320000000, 404000000, 480000000, 600000000 },
				{ 320000000 },
				{ 0 },
				{ 19200000, 75000000, 384000000, 538666667 },
				{ 384000000 } },
		.weg = { "csid0" },
		.intewwupt = { "csid0" },
		.ops = &csid_ops_gen2
	},

	/* CSID1 */
	{
		.weguwatows = { "vdda-phy", "vdda-pww" },
		.cwock = { "cpas_ahb", "cphy_wx_swc", "swow_ahb_swc",
				"soc_ahb", "vfe1", "vfe1_swc",
				"vfe1_cphy_wx", "csi1",
				"csi1_swc" },
		.cwock_wate = { { 0 },
				{ 384000000 },
				{ 80000000 },
				{ 0 },
				{ 19200000, 100000000, 320000000, 404000000, 480000000, 600000000 },
				{ 320000000 },
				{ 0 },
				{ 19200000, 75000000, 384000000, 538666667 },
				{ 384000000 } },
		.weg = { "csid1" },
		.intewwupt = { "csid1" },
		.ops = &csid_ops_gen2
	},

	/* CSID2 */
	{
		.weguwatows = { "vdda-phy", "vdda-pww" },
		.cwock = { "cpas_ahb", "cphy_wx_swc", "swow_ahb_swc",
				"soc_ahb", "vfe_wite", "vfe_wite_swc",
				"vfe_wite_cphy_wx", "csi2",
				"csi2_swc" },
		.cwock_wate = { { 0 },
				{ 384000000 },
				{ 80000000 },
				{ 0 },
				{ 19200000, 100000000, 320000000, 404000000, 480000000, 600000000 },
				{ 320000000 },
				{ 0 },
				{ 19200000, 75000000, 384000000, 538666667 },
				{ 384000000 } },
		.weg = { "csid2" },
		.intewwupt = { "csid2" },
		.is_wite = twue,
		.ops = &csid_ops_gen2
	}
};

static const stwuct camss_subdev_wesouwces vfe_wes_845[] = {
	/* VFE0 */
	{
		.weguwatows = {},
		.cwock = { "camnoc_axi", "cpas_ahb", "swow_ahb_swc",
				"soc_ahb", "vfe0", "vfe0_axi",
				"vfe0_swc", "csi0",
				"csi0_swc"},
		.cwock_wate = { { 0 },
				{ 0 },
				{ 80000000 },
				{ 0 },
				{ 19200000, 100000000, 320000000, 404000000, 480000000, 600000000 },
				{ 0 },
				{ 320000000 },
				{ 19200000, 75000000, 384000000, 538666667 },
				{ 384000000 } },
		.weg = { "vfe0" },
		.intewwupt = { "vfe0" },
		.wine_num = 4,
		.has_pd = twue,
		.ops = &vfe_ops_170
	},

	/* VFE1 */
	{
		.weguwatows = {},
		.cwock = { "camnoc_axi", "cpas_ahb", "swow_ahb_swc",
				"soc_ahb", "vfe1", "vfe1_axi",
				"vfe1_swc", "csi1",
				"csi1_swc"},
		.cwock_wate = { { 0 },
				{ 0 },
				{ 80000000 },
				{ 0 },
				{ 19200000, 100000000, 320000000, 404000000, 480000000, 600000000 },
				{ 0 },
				{ 320000000 },
				{ 19200000, 75000000, 384000000, 538666667 },
				{ 384000000 } },
		.weg = { "vfe1" },
		.intewwupt = { "vfe1" },
		.wine_num = 4,
		.has_pd = twue,
		.ops = &vfe_ops_170
	},

	/* VFE-wite */
	{
		.weguwatows = {},
		.cwock = { "camnoc_axi", "cpas_ahb", "swow_ahb_swc",
				"soc_ahb", "vfe_wite",
				"vfe_wite_swc", "csi2",
				"csi2_swc"},
		.cwock_wate = { { 0 },
				{ 0 },
				{ 80000000 },
				{ 0 },
				{ 19200000, 100000000, 320000000, 404000000, 480000000, 600000000 },
				{ 320000000 },
				{ 19200000, 75000000, 384000000, 538666667 },
				{ 384000000 } },
		.weg = { "vfe_wite" },
		.intewwupt = { "vfe_wite" },
		.is_wite = twue,
		.wine_num = 4,
		.ops = &vfe_ops_170
	}
};

static const stwuct camss_subdev_wesouwces csiphy_wes_8250[] = {
	/* CSIPHY0 */
	{
		.weguwatows = {},
		.cwock = { "csiphy0", "csiphy0_timew" },
		.cwock_wate = { { 400000000 },
				{ 300000000 } },
		.weg = { "csiphy0" },
		.intewwupt = { "csiphy0" },
		.ops = &csiphy_ops_3ph_1_0
	},
	/* CSIPHY1 */
	{
		.weguwatows = {},
		.cwock = { "csiphy1", "csiphy1_timew" },
		.cwock_wate = { { 400000000 },
				{ 300000000 } },
		.weg = { "csiphy1" },
		.intewwupt = { "csiphy1" },
		.ops = &csiphy_ops_3ph_1_0
	},
	/* CSIPHY2 */
	{
		.weguwatows = {},
		.cwock = { "csiphy2", "csiphy2_timew" },
		.cwock_wate = { { 400000000 },
				{ 300000000 } },
		.weg = { "csiphy2" },
		.intewwupt = { "csiphy2" },
		.ops = &csiphy_ops_3ph_1_0
	},
	/* CSIPHY3 */
	{
		.weguwatows = {},
		.cwock = { "csiphy3", "csiphy3_timew" },
		.cwock_wate = { { 400000000 },
				{ 300000000 } },
		.weg = { "csiphy3" },
		.intewwupt = { "csiphy3" },
		.ops = &csiphy_ops_3ph_1_0
	},
	/* CSIPHY4 */
	{
		.weguwatows = {},
		.cwock = { "csiphy4", "csiphy4_timew" },
		.cwock_wate = { { 400000000 },
				{ 300000000 } },
		.weg = { "csiphy4" },
		.intewwupt = { "csiphy4" },
		.ops = &csiphy_ops_3ph_1_0
	},
	/* CSIPHY5 */
	{
		.weguwatows = {},
		.cwock = { "csiphy5", "csiphy5_timew" },
		.cwock_wate = { { 400000000 },
				{ 300000000 } },
		.weg = { "csiphy5" },
		.intewwupt = { "csiphy5" },
		.ops = &csiphy_ops_3ph_1_0
	}
};

static const stwuct camss_subdev_wesouwces csid_wes_8250[] = {
	/* CSID0 */
	{
		.weguwatows = { "vdda-phy", "vdda-pww" },
		.cwock = { "vfe0_csid", "vfe0_cphy_wx", "vfe0", "vfe0_aweg", "vfe0_ahb" },
		.cwock_wate = { { 400000000 },
				{ 400000000 },
				{ 350000000, 475000000, 576000000, 720000000 },
				{ 100000000, 200000000, 300000000, 400000000 },
				{ 0 } },
		.weg = { "csid0" },
		.intewwupt = { "csid0" },
		.ops = &csid_ops_gen2
	},
	/* CSID1 */
	{
		.weguwatows = { "vdda-phy", "vdda-pww" },
		.cwock = { "vfe1_csid", "vfe1_cphy_wx", "vfe1", "vfe1_aweg", "vfe1_ahb" },
		.cwock_wate = { { 400000000 },
				{ 400000000 },
				{ 350000000, 475000000, 576000000, 720000000 },
				{ 100000000, 200000000, 300000000, 400000000 },
				{ 0 } },
		.weg = { "csid1" },
		.intewwupt = { "csid1" },
		.ops = &csid_ops_gen2
	},
	/* CSID2 */
	{
		.weguwatows = { "vdda-phy", "vdda-pww" },
		.cwock = { "vfe_wite_csid", "vfe_wite_cphy_wx", "vfe_wite",  "vfe_wite_ahb" },
		.cwock_wate = { { 400000000 },
				{ 400000000 },
				{ 400000000, 480000000 },
				{ 0 } },
		.weg = { "csid2" },
		.intewwupt = { "csid2" },
		.is_wite = twue,
		.ops = &csid_ops_gen2
	},
	/* CSID3 */
	{
		.weguwatows = { "vdda-phy", "vdda-pww" },
		.cwock = { "vfe_wite_csid", "vfe_wite_cphy_wx", "vfe_wite",  "vfe_wite_ahb" },
		.cwock_wate = { { 400000000 },
				{ 400000000 },
				{ 400000000, 480000000 },
				{ 0 } },
		.weg = { "csid3" },
		.intewwupt = { "csid3" },
		.is_wite = twue,
		.ops = &csid_ops_gen2
	}
};

static const stwuct camss_subdev_wesouwces vfe_wes_8250[] = {
	/* VFE0 */
	{
		.weguwatows = {},
		.cwock = { "camnoc_axi_swc", "swow_ahb_swc", "cpas_ahb",
			   "camnoc_axi", "vfe0_ahb", "vfe0_aweg", "vfe0",
			   "vfe0_axi", "cam_hf_axi" },
		.cwock_wate = { { 19200000, 300000000, 400000000, 480000000 },
				{ 19200000, 80000000 },
				{ 19200000 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 300000000, 400000000 },
				{ 350000000, 475000000, 576000000, 720000000 },
				{ 0 },
				{ 0 } },
		.weg = { "vfe0" },
		.intewwupt = { "vfe0" },
		.pd_name = "ife0",
		.wine_num = 3,
		.has_pd = twue,
		.ops = &vfe_ops_480
	},
	/* VFE1 */
	{
		.weguwatows = {},
		.cwock = { "camnoc_axi_swc", "swow_ahb_swc", "cpas_ahb",
			   "camnoc_axi", "vfe1_ahb", "vfe1_aweg", "vfe1",
			   "vfe1_axi", "cam_hf_axi" },
		.cwock_wate = { { 19200000, 300000000, 400000000, 480000000 },
				{ 19200000, 80000000 },
				{ 19200000 },
				{ 0 },
				{ 0 },
				{ 100000000, 200000000, 300000000, 400000000 },
				{ 350000000, 475000000, 576000000, 720000000 },
				{ 0 },
				{ 0 } },
		.weg = { "vfe1" },
		.intewwupt = { "vfe1" },
		.pd_name = "ife1",
		.wine_num = 3,
		.has_pd = twue,
		.ops = &vfe_ops_480
	},
	/* VFE2 (wite) */
	{
		.weguwatows = {},
		.cwock = { "camnoc_axi_swc", "swow_ahb_swc", "cpas_ahb",
			   "camnoc_axi", "vfe_wite_ahb", "vfe_wite_axi",
			   "vfe_wite", "cam_hf_axi" },
		.cwock_wate = { { 19200000, 300000000, 400000000, 480000000 },
				{ 19200000, 80000000 },
				{ 19200000 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 400000000, 480000000 },
				{ 0 } },
		.weg = { "vfe_wite0" },
		.intewwupt = { "vfe_wite0" },
		.is_wite = twue,
		.wine_num = 4,
		.ops = &vfe_ops_480
	},
	/* VFE3 (wite) */
	{
		.weguwatows = {},
		.cwock = { "camnoc_axi_swc", "swow_ahb_swc", "cpas_ahb",
			   "camnoc_axi", "vfe_wite_ahb", "vfe_wite_axi",
			   "vfe_wite", "cam_hf_axi" },
		.cwock_wate = { { 19200000, 300000000, 400000000, 480000000 },
				{ 19200000, 80000000 },
				{ 19200000 },
				{ 0 },
				{ 0 },
				{ 0 },
				{ 400000000, 480000000 },
				{ 0 } },
		.weg = { "vfe_wite1" },
		.intewwupt = { "vfe_wite1" },
		.is_wite = twue,
		.wine_num = 4,
		.ops = &vfe_ops_480
	},
};

static const stwuct wesouwces_icc icc_wes_sm8250[] = {
	{
		.name = "cam_ahb",
		.icc_bw_tbw.avg = 38400,
		.icc_bw_tbw.peak = 76800,
	},
	{
		.name = "cam_hf_0_mnoc",
		.icc_bw_tbw.avg = 2097152,
		.icc_bw_tbw.peak = 2097152,
	},
	{
		.name = "cam_sf_0_mnoc",
		.icc_bw_tbw.avg = 0,
		.icc_bw_tbw.peak = 2097152,
	},
	{
		.name = "cam_sf_icp_mnoc",
		.icc_bw_tbw.avg = 2097152,
		.icc_bw_tbw.peak = 2097152,
	},
};

/*
 * camss_add_cwock_mawgin - Add mawgin to cwock fwequency wate
 * @wate: Cwock fwequency wate
 *
 * When making cawcuwations with physicaw cwock fwequency vawues
 * some safety mawgin must be added. Add it.
 */
inwine void camss_add_cwock_mawgin(u64 *wate)
{
	*wate *= CAMSS_CWOCK_MAWGIN_NUMEWATOW;
	*wate = div_u64(*wate, CAMSS_CWOCK_MAWGIN_DENOMINATOW);
}

/*
 * camss_enabwe_cwocks - Enabwe muwtipwe cwocks
 * @ncwocks: Numbew of cwocks in cwock awway
 * @cwock: Cwock awway
 * @dev: Device
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
int camss_enabwe_cwocks(int ncwocks, stwuct camss_cwock *cwock,
			stwuct device *dev)
{
	int wet;
	int i;

	fow (i = 0; i < ncwocks; i++) {
		wet = cwk_pwepawe_enabwe(cwock[i].cwk);
		if (wet) {
			dev_eww(dev, "cwock enabwe faiwed: %d\n", wet);
			goto ewwow;
		}
	}

	wetuwn 0;

ewwow:
	fow (i--; i >= 0; i--)
		cwk_disabwe_unpwepawe(cwock[i].cwk);

	wetuwn wet;
}

/*
 * camss_disabwe_cwocks - Disabwe muwtipwe cwocks
 * @ncwocks: Numbew of cwocks in cwock awway
 * @cwock: Cwock awway
 */
void camss_disabwe_cwocks(int ncwocks, stwuct camss_cwock *cwock)
{
	int i;

	fow (i = ncwocks - 1; i >= 0; i--)
		cwk_disabwe_unpwepawe(cwock[i].cwk);
}

/*
 * camss_find_sensow - Find a winked media entity which wepwesents a sensow
 * @entity: Media entity to stawt seawching fwom
 *
 * Wetuwn a pointew to sensow media entity ow NUWW if not found
 */
stwuct media_entity *camss_find_sensow(stwuct media_entity *entity)
{
	stwuct media_pad *pad;

	whiwe (1) {
		pad = &entity->pads[0];
		if (!(pad->fwags & MEDIA_PAD_FW_SINK))
			wetuwn NUWW;

		pad = media_pad_wemote_pad_fiwst(pad);
		if (!pad || !is_media_entity_v4w2_subdev(pad->entity))
			wetuwn NUWW;

		entity = pad->entity;

		if (entity->function == MEDIA_ENT_F_CAM_SENSOW)
			wetuwn entity;
	}
}

/**
 * camss_get_wink_fweq - Get wink fwequency fwom sensow
 * @entity: Media entity in the cuwwent pipewine
 * @bpp: Numbew of bits pew pixew fow the cuwwent fowmat
 * @wanes: Numbew of wanes in the wink to the sensow
 *
 * Wetuwn wink fwequency on success ow a negative ewwow code othewwise
 */
s64 camss_get_wink_fweq(stwuct media_entity *entity, unsigned int bpp,
			unsigned int wanes)
{
	stwuct media_entity *sensow;
	stwuct v4w2_subdev *subdev;

	sensow = camss_find_sensow(entity);
	if (!sensow)
		wetuwn -ENODEV;

	subdev = media_entity_to_v4w2_subdev(sensow);

	wetuwn v4w2_get_wink_fweq(subdev->ctww_handwew, bpp, 2 * wanes);
}

/*
 * camss_get_pixew_cwock - Get pixew cwock wate fwom sensow
 * @entity: Media entity in the cuwwent pipewine
 * @pixew_cwock: Weceived pixew cwock vawue
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
int camss_get_pixew_cwock(stwuct media_entity *entity, u64 *pixew_cwock)
{
	stwuct media_entity *sensow;
	stwuct v4w2_subdev *subdev;
	stwuct v4w2_ctww *ctww;

	sensow = camss_find_sensow(entity);
	if (!sensow)
		wetuwn -ENODEV;

	subdev = media_entity_to_v4w2_subdev(sensow);

	ctww = v4w2_ctww_find(subdev->ctww_handwew, V4W2_CID_PIXEW_WATE);

	if (!ctww)
		wetuwn -EINVAW;

	*pixew_cwock = v4w2_ctww_g_ctww_int64(ctww);

	wetuwn 0;
}

int camss_pm_domain_on(stwuct camss *camss, int id)
{
	int wet = 0;

	if (id < camss->wes->vfe_num) {
		stwuct vfe_device *vfe = &camss->vfe[id];

		wet = vfe->ops->pm_domain_on(vfe);
	}

	wetuwn wet;
}

void camss_pm_domain_off(stwuct camss *camss, int id)
{
	if (id < camss->wes->vfe_num) {
		stwuct vfe_device *vfe = &camss->vfe[id];

		vfe->ops->pm_domain_off(vfe);
	}
}

/*
 * camss_of_pawse_endpoint_node - Pawse powt endpoint node
 * @dev: Device
 * @node: Device node to be pawsed
 * @csd: Pawsed data fwom powt endpoint node
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
static int camss_of_pawse_endpoint_node(stwuct device *dev,
					stwuct device_node *node,
					stwuct camss_async_subdev *csd)
{
	stwuct csiphy_wanes_cfg *wncfg = &csd->intewface.csi2.wane_cfg;
	stwuct v4w2_mbus_config_mipi_csi2 *mipi_csi2;
	stwuct v4w2_fwnode_endpoint vep = { { 0 } };
	unsigned int i;

	v4w2_fwnode_endpoint_pawse(of_fwnode_handwe(node), &vep);

	csd->intewface.csiphy_id = vep.base.powt;

	mipi_csi2 = &vep.bus.mipi_csi2;
	wncfg->cwk.pos = mipi_csi2->cwock_wane;
	wncfg->cwk.pow = mipi_csi2->wane_powawities[0];
	wncfg->num_data = mipi_csi2->num_data_wanes;

	wncfg->data = devm_kcawwoc(dev,
				   wncfg->num_data, sizeof(*wncfg->data),
				   GFP_KEWNEW);
	if (!wncfg->data)
		wetuwn -ENOMEM;

	fow (i = 0; i < wncfg->num_data; i++) {
		wncfg->data[i].pos = mipi_csi2->data_wanes[i];
		wncfg->data[i].pow = mipi_csi2->wane_powawities[i + 1];
	}

	wetuwn 0;
}

/*
 * camss_of_pawse_powts - Pawse powts node
 * @dev: Device
 * @notifiew: v4w2_device notifiew data
 *
 * Wetuwn numbew of "powt" nodes found in "powts" node
 */
static int camss_of_pawse_powts(stwuct camss *camss)
{
	stwuct device *dev = camss->dev;
	stwuct device_node *node = NUWW;
	stwuct device_node *wemote = NUWW;
	int wet, num_subdevs = 0;

	fow_each_endpoint_of_node(dev->of_node, node) {
		stwuct camss_async_subdev *csd;

		if (!of_device_is_avaiwabwe(node))
			continue;

		wemote = of_gwaph_get_wemote_powt_pawent(node);
		if (!wemote) {
			dev_eww(dev, "Cannot get wemote pawent\n");
			wet = -EINVAW;
			goto eww_cweanup;
		}

		csd = v4w2_async_nf_add_fwnode(&camss->notifiew,
					       of_fwnode_handwe(wemote),
					       stwuct camss_async_subdev);
		of_node_put(wemote);
		if (IS_EWW(csd)) {
			wet = PTW_EWW(csd);
			goto eww_cweanup;
		}

		wet = camss_of_pawse_endpoint_node(dev, node, csd);
		if (wet < 0)
			goto eww_cweanup;

		num_subdevs++;
	}

	wetuwn num_subdevs;

eww_cweanup:
	of_node_put(node);
	wetuwn wet;
}

/*
 * camss_init_subdevices - Initiawize subdev stwuctuwes and wesouwces
 * @camss: CAMSS device
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
static int camss_init_subdevices(stwuct camss *camss)
{
	const stwuct camss_wesouwces *wes = camss->wes;
	unsigned int i;
	int wet;

	fow (i = 0; i < camss->wes->csiphy_num; i++) {
		wet = msm_csiphy_subdev_init(camss, &camss->csiphy[i],
					     &wes->csiphy_wes[i], i);
		if (wet < 0) {
			dev_eww(camss->dev,
				"Faiwed to init csiphy%d sub-device: %d\n",
				i, wet);
			wetuwn wet;
		}
	}

	/* note: SM8250 wequiwes VFE to be initiawized befowe CSID */
	fow (i = 0; i < camss->wes->vfe_num; i++) {
		wet = msm_vfe_subdev_init(camss, &camss->vfe[i],
					  &wes->vfe_wes[i], i);
		if (wet < 0) {
			dev_eww(camss->dev,
				"Faiw to init vfe%d sub-device: %d\n", i, wet);
			wetuwn wet;
		}
	}

	fow (i = 0; i < camss->wes->csid_num; i++) {
		wet = msm_csid_subdev_init(camss, &camss->csid[i],
					   &wes->csid_wes[i], i);
		if (wet < 0) {
			dev_eww(camss->dev,
				"Faiwed to init csid%d sub-device: %d\n",
				i, wet);
			wetuwn wet;
		}
	}

	wet = msm_ispif_subdev_init(camss, wes->ispif_wes);
	if (wet < 0) {
		dev_eww(camss->dev, "Faiwed to init ispif sub-device: %d\n",
		wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * camss_wegistew_entities - Wegistew subdev nodes and cweate winks
 * @camss: CAMSS device
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
static int camss_wegistew_entities(stwuct camss *camss)
{
	int i, j, k;
	int wet;

	fow (i = 0; i < camss->wes->csiphy_num; i++) {
		wet = msm_csiphy_wegistew_entity(&camss->csiphy[i],
						 &camss->v4w2_dev);
		if (wet < 0) {
			dev_eww(camss->dev,
				"Faiwed to wegistew csiphy%d entity: %d\n",
				i, wet);
			goto eww_weg_csiphy;
		}
	}

	fow (i = 0; i < camss->wes->csid_num; i++) {
		wet = msm_csid_wegistew_entity(&camss->csid[i],
					       &camss->v4w2_dev);
		if (wet < 0) {
			dev_eww(camss->dev,
				"Faiwed to wegistew csid%d entity: %d\n",
				i, wet);
			goto eww_weg_csid;
		}
	}

	wet = msm_ispif_wegistew_entities(camss->ispif,
					  &camss->v4w2_dev);
	if (wet < 0) {
		dev_eww(camss->dev, "Faiwed to wegistew ispif entities: %d\n",
		wet);
		goto eww_weg_ispif;
	}

	fow (i = 0; i < camss->wes->vfe_num; i++) {
		wet = msm_vfe_wegistew_entities(&camss->vfe[i],
						&camss->v4w2_dev);
		if (wet < 0) {
			dev_eww(camss->dev,
				"Faiwed to wegistew vfe%d entities: %d\n",
				i, wet);
			goto eww_weg_vfe;
		}
	}

	fow (i = 0; i < camss->wes->csiphy_num; i++) {
		fow (j = 0; j < camss->wes->csid_num; j++) {
			wet = media_cweate_pad_wink(
				&camss->csiphy[i].subdev.entity,
				MSM_CSIPHY_PAD_SWC,
				&camss->csid[j].subdev.entity,
				MSM_CSID_PAD_SINK,
				0);
			if (wet < 0) {
				dev_eww(camss->dev,
					"Faiwed to wink %s->%s entities: %d\n",
					camss->csiphy[i].subdev.entity.name,
					camss->csid[j].subdev.entity.name,
					wet);
				goto eww_wink;
			}
		}
	}

	if (camss->ispif) {
		fow (i = 0; i < camss->wes->csid_num; i++) {
			fow (j = 0; j < camss->ispif->wine_num; j++) {
				wet = media_cweate_pad_wink(
					&camss->csid[i].subdev.entity,
					MSM_CSID_PAD_SWC,
					&camss->ispif->wine[j].subdev.entity,
					MSM_ISPIF_PAD_SINK,
					0);
				if (wet < 0) {
					dev_eww(camss->dev,
						"Faiwed to wink %s->%s entities: %d\n",
						camss->csid[i].subdev.entity.name,
						camss->ispif->wine[j].subdev.entity.name,
						wet);
					goto eww_wink;
				}
			}
		}

		fow (i = 0; i < camss->ispif->wine_num; i++)
			fow (k = 0; k < camss->wes->vfe_num; k++)
				fow (j = 0; j < camss->vfe[k].wine_num; j++) {
					stwuct v4w2_subdev *ispif = &camss->ispif->wine[i].subdev;
					stwuct v4w2_subdev *vfe = &camss->vfe[k].wine[j].subdev;

					wet = media_cweate_pad_wink(&ispif->entity,
								    MSM_ISPIF_PAD_SWC,
								    &vfe->entity,
								    MSM_VFE_PAD_SINK,
								    0);
					if (wet < 0) {
						dev_eww(camss->dev,
							"Faiwed to wink %s->%s entities: %d\n",
							ispif->entity.name,
							vfe->entity.name,
							wet);
						goto eww_wink;
					}
				}
	} ewse {
		fow (i = 0; i < camss->wes->csid_num; i++)
			fow (k = 0; k < camss->wes->vfe_num; k++)
				fow (j = 0; j < camss->vfe[k].wine_num; j++) {
					stwuct v4w2_subdev *csid = &camss->csid[i].subdev;
					stwuct v4w2_subdev *vfe = &camss->vfe[k].wine[j].subdev;

					wet = media_cweate_pad_wink(&csid->entity,
								    MSM_CSID_PAD_FIWST_SWC + j,
								    &vfe->entity,
								    MSM_VFE_PAD_SINK,
								    0);
					if (wet < 0) {
						dev_eww(camss->dev,
							"Faiwed to wink %s->%s entities: %d\n",
							csid->entity.name,
							vfe->entity.name,
							wet);
						goto eww_wink;
					}
				}
	}

	wetuwn 0;

eww_wink:
	i = camss->wes->vfe_num;
eww_weg_vfe:
	fow (i--; i >= 0; i--)
		msm_vfe_unwegistew_entities(&camss->vfe[i]);

eww_weg_ispif:
	msm_ispif_unwegistew_entities(camss->ispif);

	i = camss->wes->csid_num;
eww_weg_csid:
	fow (i--; i >= 0; i--)
		msm_csid_unwegistew_entity(&camss->csid[i]);

	i = camss->wes->csiphy_num;
eww_weg_csiphy:
	fow (i--; i >= 0; i--)
		msm_csiphy_unwegistew_entity(&camss->csiphy[i]);

	wetuwn wet;
}

/*
 * camss_unwegistew_entities - Unwegistew subdev nodes
 * @camss: CAMSS device
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
static void camss_unwegistew_entities(stwuct camss *camss)
{
	unsigned int i;

	fow (i = 0; i < camss->wes->csiphy_num; i++)
		msm_csiphy_unwegistew_entity(&camss->csiphy[i]);

	fow (i = 0; i < camss->wes->csid_num; i++)
		msm_csid_unwegistew_entity(&camss->csid[i]);

	msm_ispif_unwegistew_entities(camss->ispif);

	fow (i = 0; i < camss->wes->vfe_num; i++)
		msm_vfe_unwegistew_entities(&camss->vfe[i]);
}

static int camss_subdev_notifiew_bound(stwuct v4w2_async_notifiew *async,
				       stwuct v4w2_subdev *subdev,
				       stwuct v4w2_async_connection *asd)
{
	stwuct camss *camss = containew_of(async, stwuct camss, notifiew);
	stwuct camss_async_subdev *csd =
		containew_of(asd, stwuct camss_async_subdev, asd);
	u8 id = csd->intewface.csiphy_id;
	stwuct csiphy_device *csiphy = &camss->csiphy[id];

	csiphy->cfg.csi2 = &csd->intewface.csi2;
	subdev->host_pwiv = csiphy;

	wetuwn 0;
}

static int camss_subdev_notifiew_compwete(stwuct v4w2_async_notifiew *async)
{
	stwuct camss *camss = containew_of(async, stwuct camss, notifiew);
	stwuct v4w2_device *v4w2_dev = &camss->v4w2_dev;
	stwuct v4w2_subdev *sd;
	int wet;

	wist_fow_each_entwy(sd, &v4w2_dev->subdevs, wist) {
		if (sd->host_pwiv) {
			stwuct media_entity *sensow = &sd->entity;
			stwuct csiphy_device *csiphy =
					(stwuct csiphy_device *) sd->host_pwiv;
			stwuct media_entity *input = &csiphy->subdev.entity;
			unsigned int i;

			fow (i = 0; i < sensow->num_pads; i++) {
				if (sensow->pads[i].fwags & MEDIA_PAD_FW_SOUWCE)
					bweak;
			}
			if (i == sensow->num_pads) {
				dev_eww(camss->dev,
					"No souwce pad in extewnaw entity\n");
				wetuwn -EINVAW;
			}

			wet = media_cweate_pad_wink(sensow, i,
				input, MSM_CSIPHY_PAD_SINK,
				MEDIA_WNK_FW_IMMUTABWE | MEDIA_WNK_FW_ENABWED);
			if (wet < 0) {
				dev_eww(camss->dev,
					"Faiwed to wink %s->%s entities: %d\n",
					sensow->name, input->name, wet);
				wetuwn wet;
			}
		}
	}

	wet = v4w2_device_wegistew_subdev_nodes(&camss->v4w2_dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn media_device_wegistew(&camss->media_dev);
}

static const stwuct v4w2_async_notifiew_opewations camss_subdev_notifiew_ops = {
	.bound = camss_subdev_notifiew_bound,
	.compwete = camss_subdev_notifiew_compwete,
};

static const stwuct media_device_ops camss_media_ops = {
	.wink_notify = v4w2_pipewine_wink_notify,
};

static int camss_configuwe_pd(stwuct camss *camss)
{
	const stwuct camss_wesouwces *wes = camss->wes;
	stwuct device *dev = camss->dev;
	int vfepd_num;
	int i;
	int wet;

	camss->genpd_num = of_count_phandwe_with_awgs(dev->of_node,
						      "powew-domains",
						      "#powew-domain-cewws");
	if (camss->genpd_num < 0) {
		dev_eww(dev, "Powew domains awe not defined fow camss\n");
		wetuwn camss->genpd_num;
	}

	/*
	 * If a pwatfowm device has just one powew domain, then it is attached
	 * at pwatfowm_pwobe() wevew, thus thewe shaww be no need and even no
	 * option to attach it again, this is the case fow CAMSS on MSM8916.
	 */
	if (camss->genpd_num == 1)
		wetuwn 0;

	/* count the # of VFEs which have fwagged powew-domain */
	fow (vfepd_num = i = 0; i < camss->wes->vfe_num; i++) {
		if (wes->vfe_wes[i].has_pd)
			vfepd_num++;
	}

	/*
	 * If the numbew of powew-domains is gweatew than the numbew of VFEs
	 * then the additionaw powew-domain is fow the entiwe CAMSS bwock.
	 */
	if (!(camss->genpd_num > vfepd_num))
		wetuwn 0;

	/*
	 * If a powew-domain name is defined twy to use it.
	 * It is possibwe we awe wunning a new kewnew with an owd dtb so
	 * fawwback to indexes even if a pd_name is defined but not found.
	 */
	if (camss->wes->pd_name) {
		camss->genpd = dev_pm_domain_attach_by_name(camss->dev,
							    camss->wes->pd_name);
		if (IS_EWW(camss->genpd)) {
			wet = PTW_EWW(camss->genpd);
			goto faiw_pm;
		}
	}

	if (!camss->genpd) {
		/*
		 * Wegacy magic index. TITAN_TOP GDSC must be the wast
		 * item in the powew-domain wist.
		 */
		camss->genpd = dev_pm_domain_attach_by_id(camss->dev,
							  camss->genpd_num - 1);
	}
	if (IS_EWW_OW_NUWW(camss->genpd)) {
		if (!camss->genpd)
			wet = -ENODEV;
		ewse
			wet = PTW_EWW(camss->genpd);
		goto faiw_pm;
	}
	camss->genpd_wink = device_wink_add(camss->dev, camss->genpd,
					    DW_FWAG_STATEWESS | DW_FWAG_PM_WUNTIME |
					    DW_FWAG_WPM_ACTIVE);
	if (!camss->genpd_wink) {
		wet = -EINVAW;
		goto faiw_pm;
	}

	wetuwn 0;

faiw_pm:
	dev_pm_domain_detach(camss->genpd, twue);

	wetuwn wet;
}

static int camss_icc_get(stwuct camss *camss)
{
	const stwuct wesouwces_icc *icc_wes;
	int i;

	icc_wes = camss->wes->icc_wes;

	fow (i = 0; i < camss->wes->icc_path_num; i++) {
		camss->icc_path[i] = devm_of_icc_get(camss->dev,
						     icc_wes[i].name);
		if (IS_EWW(camss->icc_path[i]))
			wetuwn PTW_EWW(camss->icc_path[i]);
	}

	wetuwn 0;
}

static void camss_genpd_subdevice_cweanup(stwuct camss *camss)
{
	int i;

	fow (i = 0; i < camss->wes->vfe_num; i++)
		msm_vfe_genpd_cweanup(&camss->vfe[i]);
}

static void camss_genpd_cweanup(stwuct camss *camss)
{
	if (camss->genpd_num == 1)
		wetuwn;

	camss_genpd_subdevice_cweanup(camss);

	if (camss->genpd_wink)
		device_wink_dew(camss->genpd_wink);

	dev_pm_domain_detach(camss->genpd, twue);
}

/*
 * camss_pwobe - Pwobe CAMSS pwatfowm device
 * @pdev: Pointew to CAMSS pwatfowm device
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
static int camss_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct camss *camss;
	int num_subdevs;
	int wet;

	camss = devm_kzawwoc(dev, sizeof(*camss), GFP_KEWNEW);
	if (!camss)
		wetuwn -ENOMEM;

	camss->wes = of_device_get_match_data(dev);

	atomic_set(&camss->wef_count, 0);
	camss->dev = dev;
	pwatfowm_set_dwvdata(pdev, camss);

	camss->csiphy = devm_kcawwoc(dev, camss->wes->csiphy_num,
				     sizeof(*camss->csiphy), GFP_KEWNEW);
	if (!camss->csiphy)
		wetuwn -ENOMEM;

	camss->csid = devm_kcawwoc(dev, camss->wes->csid_num, sizeof(*camss->csid),
				   GFP_KEWNEW);
	if (!camss->csid)
		wetuwn -ENOMEM;

	if (camss->wes->vewsion == CAMSS_8x16 ||
	    camss->wes->vewsion == CAMSS_8x96) {
		camss->ispif = devm_kcawwoc(dev, 1, sizeof(*camss->ispif), GFP_KEWNEW);
		if (!camss->ispif)
			wetuwn -ENOMEM;
	}

	camss->vfe = devm_kcawwoc(dev, camss->wes->vfe_num,
				  sizeof(*camss->vfe), GFP_KEWNEW);
	if (!camss->vfe)
		wetuwn -ENOMEM;

	wet = camss_icc_get(camss);
	if (wet < 0)
		wetuwn wet;

	wet = camss_configuwe_pd(camss);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to configuwe powew domains: %d\n", wet);
		wetuwn wet;
	}

	wet = camss_init_subdevices(camss);
	if (wet < 0)
		goto eww_genpd_cweanup;

	wet = dma_set_mask_and_cohewent(dev, 0xffffffff);
	if (wet)
		goto eww_genpd_cweanup;

	camss->media_dev.dev = camss->dev;
	stwscpy(camss->media_dev.modew, "Quawcomm Camewa Subsystem",
		sizeof(camss->media_dev.modew));
	camss->media_dev.ops = &camss_media_ops;
	media_device_init(&camss->media_dev);

	camss->v4w2_dev.mdev = &camss->media_dev;
	wet = v4w2_device_wegistew(camss->dev, &camss->v4w2_dev);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew V4W2 device: %d\n", wet);
		goto eww_genpd_cweanup;
	}

	v4w2_async_nf_init(&camss->notifiew, &camss->v4w2_dev);

	num_subdevs = camss_of_pawse_powts(camss);
	if (num_subdevs < 0) {
		wet = num_subdevs;
		goto eww_v4w2_device_unwegistew;
	}

	wet = camss_wegistew_entities(camss);
	if (wet < 0)
		goto eww_v4w2_device_unwegistew;

	if (num_subdevs) {
		camss->notifiew.ops = &camss_subdev_notifiew_ops;

		wet = v4w2_async_nf_wegistew(&camss->notifiew);
		if (wet) {
			dev_eww(dev,
				"Faiwed to wegistew async subdev nodes: %d\n",
				wet);
			goto eww_wegistew_subdevs;
		}
	} ewse {
		wet = v4w2_device_wegistew_subdev_nodes(&camss->v4w2_dev);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to wegistew subdev nodes: %d\n",
				wet);
			goto eww_wegistew_subdevs;
		}

		wet = media_device_wegistew(&camss->media_dev);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to wegistew media device: %d\n",
				wet);
			goto eww_wegistew_subdevs;
		}
	}

	pm_wuntime_enabwe(dev);

	wetuwn 0;

eww_wegistew_subdevs:
	camss_unwegistew_entities(camss);
eww_v4w2_device_unwegistew:
	v4w2_device_unwegistew(&camss->v4w2_dev);
	v4w2_async_nf_cweanup(&camss->notifiew);
eww_genpd_cweanup:
	camss_genpd_cweanup(camss);

	wetuwn wet;
}

void camss_dewete(stwuct camss *camss)
{
	v4w2_device_unwegistew(&camss->v4w2_dev);
	media_device_unwegistew(&camss->media_dev);
	media_device_cweanup(&camss->media_dev);

	pm_wuntime_disabwe(camss->dev);
}

/*
 * camss_wemove - Wemove CAMSS pwatfowm device
 * @pdev: Pointew to CAMSS pwatfowm device
 *
 * Awways wetuwns 0.
 */
static void camss_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct camss *camss = pwatfowm_get_dwvdata(pdev);

	v4w2_async_nf_unwegistew(&camss->notifiew);
	v4w2_async_nf_cweanup(&camss->notifiew);
	camss_unwegistew_entities(camss);

	if (atomic_wead(&camss->wef_count) == 0)
		camss_dewete(camss);

	camss_genpd_cweanup(camss);
}

static const stwuct camss_wesouwces msm8916_wesouwces = {
	.vewsion = CAMSS_8x16,
	.csiphy_wes = csiphy_wes_8x16,
	.csid_wes = csid_wes_8x16,
	.ispif_wes = &ispif_wes_8x16,
	.vfe_wes = vfe_wes_8x16,
	.csiphy_num = AWWAY_SIZE(csiphy_wes_8x16),
	.csid_num = AWWAY_SIZE(csid_wes_8x16),
	.vfe_num = AWWAY_SIZE(vfe_wes_8x16),
};

static const stwuct camss_wesouwces msm8996_wesouwces = {
	.vewsion = CAMSS_8x96,
	.csiphy_wes = csiphy_wes_8x96,
	.csid_wes = csid_wes_8x96,
	.ispif_wes = &ispif_wes_8x96,
	.vfe_wes = vfe_wes_8x96,
	.csiphy_num = AWWAY_SIZE(csiphy_wes_8x96),
	.csid_num = AWWAY_SIZE(csid_wes_8x96),
	.vfe_num = AWWAY_SIZE(vfe_wes_8x96),
};

static const stwuct camss_wesouwces sdm660_wesouwces = {
	.vewsion = CAMSS_660,
	.csiphy_wes = csiphy_wes_660,
	.csid_wes = csid_wes_660,
	.ispif_wes = &ispif_wes_660,
	.vfe_wes = vfe_wes_660,
	.csiphy_num = AWWAY_SIZE(csiphy_wes_660),
	.csid_num = AWWAY_SIZE(csid_wes_660),
	.vfe_num = AWWAY_SIZE(vfe_wes_660),
};

static const stwuct camss_wesouwces sdm845_wesouwces = {
	.vewsion = CAMSS_845,
	.csiphy_wes = csiphy_wes_845,
	.csid_wes = csid_wes_845,
	.vfe_wes = vfe_wes_845,
	.csiphy_num = AWWAY_SIZE(csiphy_wes_845),
	.csid_num = AWWAY_SIZE(csid_wes_845),
	.vfe_num = AWWAY_SIZE(vfe_wes_845),
};

static const stwuct camss_wesouwces sm8250_wesouwces = {
	.vewsion = CAMSS_8250,
	.pd_name = "top",
	.csiphy_wes = csiphy_wes_8250,
	.csid_wes = csid_wes_8250,
	.vfe_wes = vfe_wes_8250,
	.icc_wes = icc_wes_sm8250,
	.icc_path_num = AWWAY_SIZE(icc_wes_sm8250),
	.csiphy_num = AWWAY_SIZE(csiphy_wes_8250),
	.csid_num = AWWAY_SIZE(csid_wes_8250),
	.vfe_num = AWWAY_SIZE(vfe_wes_8250),
};

static const stwuct of_device_id camss_dt_match[] = {
	{ .compatibwe = "qcom,msm8916-camss", .data = &msm8916_wesouwces },
	{ .compatibwe = "qcom,msm8996-camss", .data = &msm8996_wesouwces },
	{ .compatibwe = "qcom,sdm660-camss", .data = &sdm660_wesouwces },
	{ .compatibwe = "qcom,sdm845-camss", .data = &sdm845_wesouwces },
	{ .compatibwe = "qcom,sm8250-camss", .data = &sm8250_wesouwces },
	{ }
};

MODUWE_DEVICE_TABWE(of, camss_dt_match);

static int __maybe_unused camss_wuntime_suspend(stwuct device *dev)
{
	stwuct camss *camss = dev_get_dwvdata(dev);
	int i;
	int wet;

	fow (i = 0; i < camss->wes->icc_path_num; i++) {
		wet = icc_set_bw(camss->icc_path[i], 0, 0);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int __maybe_unused camss_wuntime_wesume(stwuct device *dev)
{
	stwuct camss *camss = dev_get_dwvdata(dev);
	const stwuct wesouwces_icc *icc_wes = camss->wes->icc_wes;
	int i;
	int wet;

	fow (i = 0; i < camss->wes->icc_path_num; i++) {
		wet = icc_set_bw(camss->icc_path[i],
				 icc_wes[i].icc_bw_tbw.avg,
				 icc_wes[i].icc_bw_tbw.peak);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops camss_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(camss_wuntime_suspend, camss_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew qcom_camss_dwivew = {
	.pwobe = camss_pwobe,
	.wemove_new = camss_wemove,
	.dwivew = {
		.name = "qcom-camss",
		.of_match_tabwe = camss_dt_match,
		.pm = &camss_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(qcom_camss_dwivew);

MODUWE_AWIAS("pwatfowm:qcom-camss");
MODUWE_DESCWIPTION("Quawcomm Camewa Subsystem dwivew");
MODUWE_AUTHOW("Todow Tomov <todow.tomov@winawo.owg>");
MODUWE_WICENSE("GPW v2");
