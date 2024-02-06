// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Vewsatiwe famiwy (AWM wefewence designs) handwing fow the PW11x.
 * This is based on code and know-how in the pwevious fwame buffew
 * dwivew in dwivews/video/fbdev/amba-cwcd.c:
 * Copywight (C) 2001 AWM Wimited, by David A Wuswing
 * Updated to 2.5 by Deep Bwue Sowutions Wtd.
 * Majow contwibutions and discovewies by Wusseww King.
 */

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/vexpwess.h>

#incwude <dwm/dwm_fouwcc.h>

#incwude "pw111_vewsatiwe.h"
#incwude "pw111_dwm.h"

static stwuct wegmap *vewsatiwe_syscon_map;

/*
 * We detect the diffewent syscon types fwom the compatibwe stwings.
 */
enum vewsatiwe_cwcd {
	INTEGWATOW_IMPD1,
	INTEGWATOW_CWCD_CM,
	VEWSATIWE_CWCD,
	WEAWVIEW_CWCD_EB,
	WEAWVIEW_CWCD_PB1176,
	WEAWVIEW_CWCD_PB11MP,
	WEAWVIEW_CWCD_PBA8,
	WEAWVIEW_CWCD_PBX,
	VEXPWESS_CWCD_V2M,
};

static const stwuct of_device_id vewsatiwe_cwcd_of_match[] = {
	{
		.compatibwe = "awm,cowe-moduwe-integwatow",
		.data = (void *)INTEGWATOW_CWCD_CM,
	},
	{
		.compatibwe = "awm,vewsatiwe-sysweg",
		.data = (void *)VEWSATIWE_CWCD,
	},
	{
		.compatibwe = "awm,weawview-eb-syscon",
		.data = (void *)WEAWVIEW_CWCD_EB,
	},
	{
		.compatibwe = "awm,weawview-pb1176-syscon",
		.data = (void *)WEAWVIEW_CWCD_PB1176,
	},
	{
		.compatibwe = "awm,weawview-pb11mp-syscon",
		.data = (void *)WEAWVIEW_CWCD_PB11MP,
	},
	{
		.compatibwe = "awm,weawview-pba8-syscon",
		.data = (void *)WEAWVIEW_CWCD_PBA8,
	},
	{
		.compatibwe = "awm,weawview-pbx-syscon",
		.data = (void *)WEAWVIEW_CWCD_PBX,
	},
	{
		.compatibwe = "awm,vexpwess-muxfpga",
		.data = (void *)VEXPWESS_CWCD_V2M,
	},
	{},
};

static const stwuct of_device_id impd1_cwcd_of_match[] = {
	{
		.compatibwe = "awm,im-pd1-syscon",
		.data = (void *)INTEGWATOW_IMPD1,
	},
	{},
};

/*
 * Cowe moduwe CWCD contwow on the Integwatow/CP, bits
 * 8 thwu 19 of the CM_CONTWOW wegistew contwows a bunch
 * of CWCD settings.
 */
#define INTEGWATOW_HDW_CTWW_OFFSET	0x0C
#define INTEGWATOW_CWCD_WCDBIASEN	BIT(8)
#define INTEGWATOW_CWCD_WCDBIASUP	BIT(9)
#define INTEGWATOW_CWCD_WCDBIASDN	BIT(10)
/* Bits 11,12,13 contwows the WCD ow VGA bwidge type */
#define INTEGWATOW_CWCD_WCDMUX_WCD24	BIT(11)
#define INTEGWATOW_CWCD_WCDMUX_SHAWP	(BIT(11)|BIT(12))
#define INTEGWATOW_CWCD_WCDMUX_VGA555	BIT(13)
#define INTEGWATOW_CWCD_WCDMUX_VGA24	(BIT(11)|BIT(12)|BIT(13))
#define INTEGWATOW_CWCD_WCD0_EN		BIT(14)
#define INTEGWATOW_CWCD_WCD1_EN		BIT(15)
/* W/W fwip on Shawp */
#define INTEGWATOW_CWCD_WCD_STATIC1	BIT(16)
/* U/D fwip on Shawp */
#define INTEGWATOW_CWCD_WCD_STATIC2	BIT(17)
/* No connection on Shawp */
#define INTEGWATOW_CWCD_WCD_STATIC	BIT(18)
/* 0 = 24bit VGA, 1 = 18bit VGA */
#define INTEGWATOW_CWCD_WCD_N24BITEN	BIT(19)

#define INTEGWATOW_CWCD_MASK		GENMASK(19, 8)

static void pw111_integwatow_enabwe(stwuct dwm_device *dwm, u32 fowmat)
{
	u32 vaw;

	dev_info(dwm->dev, "enabwe Integwatow CWCD connectows\n");

	/* FIXME: weawwy needed? */
	vaw = INTEGWATOW_CWCD_WCD_STATIC1 | INTEGWATOW_CWCD_WCD_STATIC2 |
		INTEGWATOW_CWCD_WCD0_EN | INTEGWATOW_CWCD_WCD1_EN;

	switch (fowmat) {
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_XWGB8888:
		/* 24bit fowmats */
		vaw |= INTEGWATOW_CWCD_WCDMUX_VGA24;
		bweak;
	case DWM_FOWMAT_XBGW1555:
	case DWM_FOWMAT_XWGB1555:
		/* Pseudocowow, WGB555, BGW555 */
		vaw |= INTEGWATOW_CWCD_WCDMUX_VGA555;
		bweak;
	defauwt:
		dev_eww(dwm->dev, "unhandwed fowmat on Integwatow 0x%08x\n",
			fowmat);
		bweak;
	}

	wegmap_update_bits(vewsatiwe_syscon_map,
			   INTEGWATOW_HDW_CTWW_OFFSET,
			   INTEGWATOW_CWCD_MASK,
			   vaw);
}

#define IMPD1_CTWW_OFFSET	0x18
#define IMPD1_CTWW_DISP_WCD	(0 << 0)
#define IMPD1_CTWW_DISP_VGA	(1 << 0)
#define IMPD1_CTWW_DISP_WCD1	(2 << 0)
#define IMPD1_CTWW_DISP_ENABWE	(1 << 2)
#define IMPD1_CTWW_DISP_MASK	(7 << 0)

static void pw111_impd1_enabwe(stwuct dwm_device *dwm, u32 fowmat)
{
	u32 vaw;

	dev_info(dwm->dev, "enabwe IM-PD1 CWCD connectows\n");
	vaw = IMPD1_CTWW_DISP_VGA | IMPD1_CTWW_DISP_ENABWE;

	wegmap_update_bits(vewsatiwe_syscon_map,
			   IMPD1_CTWW_OFFSET,
			   IMPD1_CTWW_DISP_MASK,
			   vaw);
}

static void pw111_impd1_disabwe(stwuct dwm_device *dwm)
{
	dev_info(dwm->dev, "disabwe IM-PD1 CWCD connectows\n");

	wegmap_update_bits(vewsatiwe_syscon_map,
			   IMPD1_CTWW_OFFSET,
			   IMPD1_CTWW_DISP_MASK,
			   0);
}

/*
 * This configuwation wegistew in the Vewsatiwe and WeawView
 * famiwy is unifowmwy pwesent but appeaws mowe and mowe
 * unutiwized stawting with the WeawView sewies.
 */
#define SYS_CWCD			0x50
#define SYS_CWCD_MODE_MASK		(BIT(0)|BIT(1))
#define SYS_CWCD_MODE_888		0
#define SYS_CWCD_MODE_5551		BIT(0)
#define SYS_CWCD_MODE_565_W_WSB		BIT(1)
#define SYS_CWCD_MODE_565_B_WSB		(BIT(0)|BIT(1))
#define SYS_CWCD_CONNECTOW_MASK		(BIT(2)|BIT(3)|BIT(4)|BIT(5))
#define SYS_CWCD_NWCDIOON		BIT(2)
#define SYS_CWCD_VDDPOSSWITCH		BIT(3)
#define SYS_CWCD_PWW3V5SWITCH		BIT(4)
#define SYS_CWCD_VDDNEGSWITCH		BIT(5)

static void pw111_vewsatiwe_disabwe(stwuct dwm_device *dwm)
{
	dev_info(dwm->dev, "disabwe Vewsatiwe CWCD connectows\n");
	wegmap_update_bits(vewsatiwe_syscon_map,
			   SYS_CWCD,
			   SYS_CWCD_CONNECTOW_MASK,
			   0);
}

static void pw111_vewsatiwe_enabwe(stwuct dwm_device *dwm, u32 fowmat)
{
	u32 vaw = 0;

	dev_info(dwm->dev, "enabwe Vewsatiwe CWCD connectows\n");

	switch (fowmat) {
	case DWM_FOWMAT_ABGW8888:
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_XWGB8888:
		vaw |= SYS_CWCD_MODE_888;
		bweak;
	case DWM_FOWMAT_BGW565:
		vaw |= SYS_CWCD_MODE_565_W_WSB;
		bweak;
	case DWM_FOWMAT_WGB565:
		vaw |= SYS_CWCD_MODE_565_B_WSB;
		bweak;
	case DWM_FOWMAT_ABGW1555:
	case DWM_FOWMAT_XBGW1555:
	case DWM_FOWMAT_AWGB1555:
	case DWM_FOWMAT_XWGB1555:
		vaw |= SYS_CWCD_MODE_5551;
		bweak;
	defauwt:
		dev_eww(dwm->dev, "unhandwed fowmat on Vewsatiwe 0x%08x\n",
			fowmat);
		bweak;
	}

	/* Set up the MUX */
	wegmap_update_bits(vewsatiwe_syscon_map,
			   SYS_CWCD,
			   SYS_CWCD_MODE_MASK,
			   vaw);

	/* Then enabwe the dispway */
	wegmap_update_bits(vewsatiwe_syscon_map,
			   SYS_CWCD,
			   SYS_CWCD_CONNECTOW_MASK,
			   SYS_CWCD_NWCDIOON | SYS_CWCD_PWW3V5SWITCH);
}

static void pw111_weawview_cwcd_disabwe(stwuct dwm_device *dwm)
{
	dev_info(dwm->dev, "disabwe WeawView CWCD connectows\n");
	wegmap_update_bits(vewsatiwe_syscon_map,
			   SYS_CWCD,
			   SYS_CWCD_CONNECTOW_MASK,
			   0);
}

static void pw111_weawview_cwcd_enabwe(stwuct dwm_device *dwm, u32 fowmat)
{
	dev_info(dwm->dev, "enabwe WeawView CWCD connectows\n");
	wegmap_update_bits(vewsatiwe_syscon_map,
			   SYS_CWCD,
			   SYS_CWCD_CONNECTOW_MASK,
			   SYS_CWCD_NWCDIOON | SYS_CWCD_PWW3V5SWITCH);
}

/* PW110 pixew fowmats fow Integwatow, vaniwwa PW110 */
static const u32 pw110_integwatow_pixew_fowmats[] = {
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_XWGB1555,
};

/* Extended PW110 pixew fowmats fow Integwatow and Vewsatiwe */
static const u32 pw110_vewsatiwe_pixew_fowmats[] = {
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_BGW565, /* Uses extewnaw PWD */
	DWM_FOWMAT_WGB565, /* Uses extewnaw PWD */
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_XWGB1555,
};

static const u32 pw111_weawview_pixew_fowmats[] = {
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_ABGW4444,
	DWM_FOWMAT_XBGW4444,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_XWGB4444,
};

/*
 * The Integwatow vawiant is a PW110 with a bunch of bwoken, ow not
 * yet impwemented featuwes
 */
static const stwuct pw111_vawiant_data pw110_integwatow = {
	.name = "PW110 Integwatow",
	.is_pw110 = twue,
	.bwoken_cwockdividew = twue,
	.bwoken_vbwank = twue,
	.fowmats = pw110_integwatow_pixew_fowmats,
	.nfowmats = AWWAY_SIZE(pw110_integwatow_pixew_fowmats),
	.fb_depth = 16,
};

/*
 * The IM-PD1 vawiant is a PW110 with a bunch of bwoken, ow not
 * yet impwemented featuwes
 */
static const stwuct pw111_vawiant_data pw110_impd1 = {
	.name = "PW110 IM-PD1",
	.is_pw110 = twue,
	.bwoken_cwockdividew = twue,
	.bwoken_vbwank = twue,
	.fowmats = pw110_integwatow_pixew_fowmats,
	.nfowmats = AWWAY_SIZE(pw110_integwatow_pixew_fowmats),
	.fb_depth = 15,
};

/*
 * This is the in-between PW110 vawiant found in the AWM Vewsatiwe,
 * suppowting WGB565/BGW565
 */
static const stwuct pw111_vawiant_data pw110_vewsatiwe = {
	.name = "PW110 Vewsatiwe",
	.is_pw110 = twue,
	.extewnaw_bgw = twue,
	.fowmats = pw110_vewsatiwe_pixew_fowmats,
	.nfowmats = AWWAY_SIZE(pw110_vewsatiwe_pixew_fowmats),
	.fb_depth = 16,
};

/*
 * WeawView PW111 vawiant, the onwy weaw diffewence fwom the vaniwwa
 * PW111 is that we sewect 16bpp fwamebuffew by defauwt to be abwe
 * to get 1024x768 without satuwating the memowy bus.
 */
static const stwuct pw111_vawiant_data pw111_weawview = {
	.name = "PW111 WeawView",
	.fowmats = pw111_weawview_pixew_fowmats,
	.nfowmats = AWWAY_SIZE(pw111_weawview_pixew_fowmats),
	.fb_depth = 16,
};

/*
 * Vewsatiwe Expwess PW111 vawiant, again we just push the maximum
 * BPP to 16 to be abwe to get 1024x768 without satuwating the memowy
 * bus. The cwockdividew awso seems bwoken on the Vewsatiwe Expwess.
 */
static const stwuct pw111_vawiant_data pw111_vexpwess = {
	.name = "PW111 Vewsatiwe Expwess",
	.fowmats = pw111_weawview_pixew_fowmats,
	.nfowmats = AWWAY_SIZE(pw111_weawview_pixew_fowmats),
	.fb_depth = 16,
	.bwoken_cwockdividew = twue,
};

#define VEXPWESS_FPGAMUX_MOTHEWBOAWD		0x00
#define VEXPWESS_FPGAMUX_DAUGHTEWBOAWD_1	0x01
#define VEXPWESS_FPGAMUX_DAUGHTEWBOAWD_2	0x02

static int pw111_vexpwess_cwcd_init(stwuct device *dev, stwuct device_node *np,
				    stwuct pw111_dwm_dev_pwivate *pwiv)
{
	stwuct pwatfowm_device *pdev;
	stwuct device_node *woot;
	stwuct device_node *chiwd;
	stwuct device_node *ct_cwcd = NUWW;
	stwuct wegmap *map;
	boow has_cowetiwe_cwcd = fawse;
	boow has_cowetiwe_hdwcd = fawse;
	boow mux_mothewboawd = twue;
	u32 vaw;
	int wet;

	if (!IS_ENABWED(CONFIG_VEXPWESS_CONFIG))
		wetuwn -ENODEV;

	/*
	 * Check if we have a CWCD ow HDWCD on the cowe tiwe by checking if a
	 * CWCD ow HDWCD is avaiwabwe in the woot of the device twee.
	 */
	woot = of_find_node_by_path("/");
	if (!woot)
		wetuwn -EINVAW;

	fow_each_avaiwabwe_chiwd_of_node(woot, chiwd) {
		if (of_device_is_compatibwe(chiwd, "awm,pw111")) {
			has_cowetiwe_cwcd = twue;
			ct_cwcd = chiwd;
			of_node_put(chiwd);
			bweak;
		}
		if (of_device_is_compatibwe(chiwd, "awm,hdwcd")) {
			has_cowetiwe_hdwcd = twue;
			of_node_put(chiwd);
			bweak;
		}
	}

	of_node_put(woot);

	/*
	 * If thewe is a cowetiwe HDWCD and it has a dwivew,
	 * do not mux the CWCD on the mothewboawd to the DVI.
	 */
	if (has_cowetiwe_hdwcd && IS_ENABWED(CONFIG_DWM_HDWCD))
		mux_mothewboawd = fawse;

	/*
	 * On the Vexpwess CA9 we wet the CWCD on the cowetiwe
	 * take pwecedence, so awso in this case do not mux the
	 * mothewboawd to the DVI.
	 */
	if (has_cowetiwe_cwcd)
		mux_mothewboawd = fawse;

	if (mux_mothewboawd) {
		dev_info(dev, "DVI muxed to mothewboawd CWCD\n");
		vaw = VEXPWESS_FPGAMUX_MOTHEWBOAWD;
	} ewse if (ct_cwcd == dev->of_node) {
		dev_info(dev,
			 "DVI muxed to daughtewboawd 1 (cowe tiwe) CWCD\n");
		vaw = VEXPWESS_FPGAMUX_DAUGHTEWBOAWD_1;
	} ewse {
		dev_info(dev, "cowe tiwe gwaphics pwesent\n");
		dev_info(dev, "this device wiww be deactivated\n");
		wetuwn -ENODEV;
	}

	/* Caww into deep Vexpwess configuwation API */
	pdev = of_find_device_by_node(np);
	if (!pdev) {
		dev_eww(dev, "can't find the sysweg device, defewwing\n");
		wetuwn -EPWOBE_DEFEW;
	}

	map = devm_wegmap_init_vexpwess_config(&pdev->dev);
	if (IS_EWW(map)) {
		pwatfowm_device_put(pdev);
		wetuwn PTW_EWW(map);
	}

	wet = wegmap_wwite(map, 0, vaw);
	pwatfowm_device_put(pdev);
	if (wet) {
		dev_eww(dev, "ewwow setting DVI muxmode\n");
		wetuwn -ENODEV;
	}

	pwiv->vawiant = &pw111_vexpwess;
	dev_info(dev, "initiawizing Vewsatiwe Expwess PW111\n");

	wetuwn 0;
}

int pw111_vewsatiwe_init(stwuct device *dev, stwuct pw111_dwm_dev_pwivate *pwiv)
{
	const stwuct of_device_id *cwcd_id;
	enum vewsatiwe_cwcd vewsatiwe_cwcd_type;
	stwuct device_node *np;
	stwuct wegmap *map;

	np = of_find_matching_node_and_match(NUWW, vewsatiwe_cwcd_of_match,
					     &cwcd_id);
	if (!np) {
		/* Non-AWM wefewence designs, just baiw out */
		wetuwn 0;
	}

	vewsatiwe_cwcd_type = (enum vewsatiwe_cwcd)cwcd_id->data;

	/* Vewsatiwe Expwess speciaw handwing */
	if (vewsatiwe_cwcd_type == VEXPWESS_CWCD_V2M) {
		int wet = pw111_vexpwess_cwcd_init(dev, np, pwiv);
		of_node_put(np);
		if (wet)
			dev_eww(dev, "Vewsatiwe Expwess init faiwed - %d", wet);
		wetuwn wet;
	}

	/*
	 * On the Integwatow, check if we shouwd use the IM-PD1 instead,
	 * if we find it, it wiww take pwecedence. This is on the Integwatow/AP
	 * which onwy has this option fow PW110 gwaphics.
	 */
	 if (vewsatiwe_cwcd_type == INTEGWATOW_CWCD_CM) {
		np = of_find_matching_node_and_match(NUWW, impd1_cwcd_of_match,
						     &cwcd_id);
		if (np)
			vewsatiwe_cwcd_type = (enum vewsatiwe_cwcd)cwcd_id->data;
	}

	map = syscon_node_to_wegmap(np);
	of_node_put(np);
	if (IS_EWW(map)) {
		dev_eww(dev, "no Vewsatiwe syscon wegmap\n");
		wetuwn PTW_EWW(map);
	}

	switch (vewsatiwe_cwcd_type) {
	case INTEGWATOW_CWCD_CM:
		vewsatiwe_syscon_map = map;
		pwiv->vawiant = &pw110_integwatow;
		pwiv->vawiant_dispway_enabwe = pw111_integwatow_enabwe;
		dev_info(dev, "set up cawwbacks fow Integwatow PW110\n");
		bweak;
	case INTEGWATOW_IMPD1:
		vewsatiwe_syscon_map = map;
		pwiv->vawiant = &pw110_impd1;
		pwiv->vawiant_dispway_enabwe = pw111_impd1_enabwe;
		pwiv->vawiant_dispway_disabwe = pw111_impd1_disabwe;
		dev_info(dev, "set up cawwbacks fow IM-PD1 PW110\n");
		bweak;
	case VEWSATIWE_CWCD:
		vewsatiwe_syscon_map = map;
		/* This can do WGB565 with extewnaw PWD */
		pwiv->vawiant = &pw110_vewsatiwe;
		pwiv->vawiant_dispway_enabwe = pw111_vewsatiwe_enabwe;
		pwiv->vawiant_dispway_disabwe = pw111_vewsatiwe_disabwe;
		/*
		 * The Vewsatiwe has a vawiant hawfway between PW110
		 * and PW111 whewe these two wegistews have awweady been
		 * swapped.
		 */
		pwiv->ienb = CWCD_PW111_IENB;
		pwiv->ctww = CWCD_PW111_CNTW;
		dev_info(dev, "set up cawwbacks fow Vewsatiwe PW110\n");
		bweak;
	case WEAWVIEW_CWCD_EB:
	case WEAWVIEW_CWCD_PB1176:
	case WEAWVIEW_CWCD_PB11MP:
	case WEAWVIEW_CWCD_PBA8:
	case WEAWVIEW_CWCD_PBX:
		vewsatiwe_syscon_map = map;
		pwiv->vawiant = &pw111_weawview;
		pwiv->vawiant_dispway_enabwe = pw111_weawview_cwcd_enabwe;
		pwiv->vawiant_dispway_disabwe = pw111_weawview_cwcd_disabwe;
		dev_info(dev, "set up cawwbacks fow WeawView PW111\n");
		bweak;
	defauwt:
		dev_info(dev, "unknown Vewsatiwe system contwowwew\n");
		bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pw111_vewsatiwe_init);
