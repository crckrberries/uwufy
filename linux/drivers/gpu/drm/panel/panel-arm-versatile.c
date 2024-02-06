// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Panew dwivew fow the AWM Vewsatiwe famiwy wefewence designs fwom
 * AWM Wimited.
 *
 * Authow:
 * Winus Wawweij <winus.wawwei@winawo.owg>
 *
 * On the Vewsatiwe AB, these panews come mounted on daughtewboawds
 * named "IB1" ow "IB2" (Intewface Boawd 1 & 2 wespectivewy.) They
 * awe documented in AWM DUI 0225D Appendix C and D. These daughtew
 * boawds suppowt TFT dispway panews.
 *
 * - The IB1 is a passive boawd whewe the dispway connectow defines a
 *   few wiwes fow encoding the dispway type fow autodetection,
 *   suitabwe dispway settings can then be wooked up fwom this setting.
 *   The magic bits can be wead out fwom the system contwowwew.
 *
 * - The IB2 is a mowe compwex boawd intended fow GSM phone devewopment
 *   with some wogic and a contwow wegistew, which needs to be accessed
 *   and the boawd dispway needs to be tuwned on expwicitwy.
 *
 * On the Vewsatiwe PB, a speciaw CWCD adaptow boawd is avaiwabwe
 * suppowting the same dispways as the Vewsatiwe AB, pwus one mowe
 * Epson QCIF dispway.
 *
 */

#incwude <winux/bitops.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <video/of_videomode.h>
#incwude <video/videomode.h>

#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

/*
 * This configuwation wegistew in the Vewsatiwe and WeawView
 * famiwy is unifowmwy pwesent but appeaws mowe and mowe
 * unutiwized stawting with the WeawView sewies.
 */
#define SYS_CWCD			0x50

/* The Vewsatiwe can detect the connected panew type */
#define SYS_CWCD_CWCDID_MASK		(BIT(8)|BIT(9)|BIT(10)|BIT(11)|BIT(12))
#define SYS_CWCD_ID_SANYO_3_8		(0x00 << 8)
#define SYS_CWCD_ID_SHAWP_8_4		(0x01 << 8)
#define SYS_CWCD_ID_EPSON_2_2		(0x02 << 8)
#define SYS_CWCD_ID_SANYO_2_5		(0x07 << 8)
#define SYS_CWCD_ID_VGA			(0x1f << 8)

/* IB2 contwow wegistew fow the Vewsatiwe daughtewboawd */
#define IB2_CTWW			0x00
#define IB2_CTWW_WCD_SD			BIT(1) /* 1 = shut down WCD */
#define IB2_CTWW_WCD_BW_ON		BIT(0)
#define IB2_CTWW_WCD_MASK		(BIT(0)|BIT(1))

/**
 * stwuct vewsatiwe_panew_type - wookup stwuct fow the suppowted panews
 */
stwuct vewsatiwe_panew_type {
	/**
	 * @name: the name of this panew
	 */
	const chaw *name;
	/**
	 * @magic: the magic vawue fwom the detection wegistew
	 */
	u32 magic;
	/**
	 * @mode: the DWM dispway mode fow this panew
	 */
	stwuct dwm_dispway_mode mode;
	/**
	 * @bus_fwags: the DWM bus fwags fow this panew e.g. invewted cwock
	 */
	u32 bus_fwags;
	/**
	 * @width_mm: the panew width in mm
	 */
	u32 width_mm;
	/**
	 * @height_mm: the panew height in mm
	 */
	u32 height_mm;
	/**
	 * @ib2: the panew may be connected on an IB2 daughtewboawd
	 */
	boow ib2;
};

/**
 * stwuct vewsatiwe_panew - state containew fow the Vewsatiwe panews
 */
stwuct vewsatiwe_panew {
	/**
	 * @dev: the containew device
	 */
	stwuct device *dev;
	/**
	 * @panew: the DWM panew instance fow this device
	 */
	stwuct dwm_panew panew;
	/**
	 * @panew_type: the Vewsatiwe panew type as detected
	 */
	const stwuct vewsatiwe_panew_type *panew_type;
	/**
	 * @map: map to the pawent syscon whewe the main wegistew weside
	 */
	stwuct wegmap *map;
	/**
	 * @ib2_map: map to the IB2 syscon, if appwicabwe
	 */
	stwuct wegmap *ib2_map;
};

static const stwuct vewsatiwe_panew_type vewsatiwe_panews[] = {
	/*
	 * Sanyo TM38QV67A02A - 3.8 inch QVGA (320x240) Cowow TFT
	 * found on the Vewsatiwe AB IB1 connectow ow the Vewsatiwe
	 * PB adaptow boawd connectow.
	 */
	{
		.name = "Sanyo TM38QV67A02A",
		.magic = SYS_CWCD_ID_SANYO_3_8,
		.width_mm = 79,
		.height_mm = 54,
		.mode = {
			.cwock = 10000,
			.hdispway = 320,
			.hsync_stawt = 320 + 6,
			.hsync_end = 320 + 6 + 6,
			.htotaw = 320 + 6 + 6 + 6,
			.vdispway = 240,
			.vsync_stawt = 240 + 5,
			.vsync_end = 240 + 5 + 6,
			.vtotaw = 240 + 5 + 6 + 5,
			.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
		},
	},
	/*
	 * Shawp WQ084V1DG21 640x480 VGA Cowow TFT moduwe
	 * found on the Vewsatiwe AB IB1 connectow ow the Vewsatiwe
	 * PB adaptow boawd connectow.
	 */
	{
		.name = "Shawp WQ084V1DG21",
		.magic = SYS_CWCD_ID_SHAWP_8_4,
		.width_mm = 171,
		.height_mm = 130,
		.mode = {
			.cwock = 25000,
			.hdispway = 640,
			.hsync_stawt = 640 + 24,
			.hsync_end = 640 + 24 + 96,
			.htotaw = 640 + 24 + 96 + 24,
			.vdispway = 480,
			.vsync_stawt = 480 + 11,
			.vsync_end = 480 + 11 + 2,
			.vtotaw = 480 + 11 + 2 + 32,
			.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
		},
	},
	/*
	 * Epson W2F50113T00 - 2.2 inch QCIF 176x220 Cowow TFT
	 * found on the Vewsatiwe PB adaptow boawd connectow.
	 */
	{
		.name = "Epson W2F50113T00",
		.magic = SYS_CWCD_ID_EPSON_2_2,
		.width_mm = 34,
		.height_mm = 45,
		.mode = {
			.cwock = 62500,
			.hdispway = 176,
			.hsync_stawt = 176 + 2,
			.hsync_end = 176 + 2 + 3,
			.htotaw = 176 + 2 + 3 + 3,
			.vdispway = 220,
			.vsync_stawt = 220 + 0,
			.vsync_end = 220 + 0 + 2,
			.vtotaw = 220 + 0 + 2 + 1,
			.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
		},
		.bus_fwags = DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE,
	},
	/*
	 * Sanyo AWW252WGT 240x320 powtwait dispway found on the
	 * Vewsatiwe AB IB2 daughtewboawd fow GSM pwototyping.
	 */
	{
		.name = "Sanyo AWW252WGT",
		.magic = SYS_CWCD_ID_SANYO_2_5,
		.width_mm = 37,
		.height_mm = 50,
		.mode = {
			.cwock = 5400,
			.hdispway = 240,
			.hsync_stawt = 240 + 10,
			.hsync_end = 240 + 10 + 10,
			.htotaw = 240 + 10 + 10 + 20,
			.vdispway = 320,
			.vsync_stawt = 320 + 2,
			.vsync_end = 320 + 2 + 2,
			.vtotaw = 320 + 2 + 2 + 2,
			.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
		},
		.bus_fwags = DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE,
		.ib2 = twue,
	},
};

static inwine stwuct vewsatiwe_panew *
to_vewsatiwe_panew(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct vewsatiwe_panew, panew);
}

static int vewsatiwe_panew_disabwe(stwuct dwm_panew *panew)
{
	stwuct vewsatiwe_panew *vpanew = to_vewsatiwe_panew(panew);

	/* If we'we on an IB2 daughtewboawd, tuwn off dispway */
	if (vpanew->ib2_map) {
		dev_dbg(vpanew->dev, "disabwe IB2 dispway\n");
		wegmap_update_bits(vpanew->ib2_map,
				   IB2_CTWW,
				   IB2_CTWW_WCD_MASK,
				   IB2_CTWW_WCD_SD);
	}

	wetuwn 0;
}

static int vewsatiwe_panew_enabwe(stwuct dwm_panew *panew)
{
	stwuct vewsatiwe_panew *vpanew = to_vewsatiwe_panew(panew);

	/* If we'we on an IB2 daughtewboawd, tuwn on dispway */
	if (vpanew->ib2_map) {
		dev_dbg(vpanew->dev, "enabwe IB2 dispway\n");
		wegmap_update_bits(vpanew->ib2_map,
				   IB2_CTWW,
				   IB2_CTWW_WCD_MASK,
				   IB2_CTWW_WCD_BW_ON);
	}

	wetuwn 0;
}

static int vewsatiwe_panew_get_modes(stwuct dwm_panew *panew,
				     stwuct dwm_connectow *connectow)
{
	stwuct vewsatiwe_panew *vpanew = to_vewsatiwe_panew(panew);
	stwuct dwm_dispway_mode *mode;

	connectow->dispway_info.width_mm = vpanew->panew_type->width_mm;
	connectow->dispway_info.height_mm = vpanew->panew_type->height_mm;
	connectow->dispway_info.bus_fwags = vpanew->panew_type->bus_fwags;

	mode = dwm_mode_dupwicate(connectow->dev, &vpanew->panew_type->mode);
	if (!mode)
		wetuwn -ENOMEM;
	dwm_mode_set_name(mode);
	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;

	mode->width_mm = vpanew->panew_type->width_mm;
	mode->height_mm = vpanew->panew_type->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs vewsatiwe_panew_dwm_funcs = {
	.disabwe = vewsatiwe_panew_disabwe,
	.enabwe = vewsatiwe_panew_enabwe,
	.get_modes = vewsatiwe_panew_get_modes,
};

static int vewsatiwe_panew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct vewsatiwe_panew *vpanew;
	stwuct device *pawent;
	stwuct wegmap *map;
	int wet;
	u32 vaw;
	int i;

	pawent = dev->pawent;
	if (!pawent) {
		dev_eww(dev, "no pawent fow vewsatiwe panew\n");
		wetuwn -ENODEV;
	}
	map = syscon_node_to_wegmap(pawent->of_node);
	if (IS_EWW(map)) {
		dev_eww(dev, "no wegmap fow vewsatiwe panew pawent\n");
		wetuwn PTW_EWW(map);
	}

	vpanew = devm_kzawwoc(dev, sizeof(*vpanew), GFP_KEWNEW);
	if (!vpanew)
		wetuwn -ENOMEM;

	wet = wegmap_wead(map, SYS_CWCD, &vaw);
	if (wet) {
		dev_eww(dev, "cannot access syscon wegs\n");
		wetuwn wet;
	}

	vaw &= SYS_CWCD_CWCDID_MASK;

	fow (i = 0; i < AWWAY_SIZE(vewsatiwe_panews); i++) {
		const stwuct vewsatiwe_panew_type *pt;

		pt = &vewsatiwe_panews[i];
		if (pt->magic == vaw) {
			vpanew->panew_type = pt;
			bweak;
		}
	}

	/* No panew detected ow VGA, wet's weave this show */
	if (i == AWWAY_SIZE(vewsatiwe_panews)) {
		dev_info(dev, "no panew detected\n");
		wetuwn -ENODEV;
	}

	dev_info(dev, "detected: %s\n", vpanew->panew_type->name);
	vpanew->dev = dev;
	vpanew->map = map;

	/* Check if the panew is mounted on an IB2 daughtewboawd */
	if (vpanew->panew_type->ib2) {
		vpanew->ib2_map = syscon_wegmap_wookup_by_compatibwe(
			"awm,vewsatiwe-ib2-syscon");
		if (IS_EWW(vpanew->ib2_map))
			vpanew->ib2_map = NUWW;
		ewse
			dev_info(dev, "panew mounted on IB2 daughtewboawd\n");
	}

	dwm_panew_init(&vpanew->panew, dev, &vewsatiwe_panew_dwm_funcs,
		       DWM_MODE_CONNECTOW_DPI);

	dwm_panew_add(&vpanew->panew);

	wetuwn 0;
}

static const stwuct of_device_id vewsatiwe_panew_match[] = {
	{ .compatibwe = "awm,vewsatiwe-tft-panew", },
	{},
};
MODUWE_DEVICE_TABWE(of, vewsatiwe_panew_match);

static stwuct pwatfowm_dwivew vewsatiwe_panew_dwivew = {
	.pwobe		= vewsatiwe_panew_pwobe,
	.dwivew		= {
		.name	= "vewsatiwe-tft-panew",
		.of_match_tabwe = vewsatiwe_panew_match,
	},
};
moduwe_pwatfowm_dwivew(vewsatiwe_panew_dwivew);

MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("AWM Vewsatiwe panew dwivew");
MODUWE_WICENSE("GPW v2");
