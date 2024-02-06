// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017-2021 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/io.h>
#incwude <winux/iommu.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude <soc/tegwa/mc.h>

#if defined(CONFIG_AWCH_TEGWA_186_SOC)
#incwude <dt-bindings/memowy/tegwa186-mc.h>
#endif

#incwude "mc.h"

#define MC_SID_STWEAMID_OVEWWIDE_MASK GENMASK(7, 0)
#define MC_SID_STWEAMID_SECUWITY_WWITE_ACCESS_DISABWED BIT(16)
#define MC_SID_STWEAMID_SECUWITY_OVEWWIDE BIT(8)

static int tegwa186_mc_pwobe(stwuct tegwa_mc *mc)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(mc->dev);
	unsigned int i;
	chaw name[8];
	int eww;

	mc->bcast_ch_wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "bwoadcast");
	if (IS_EWW(mc->bcast_ch_wegs)) {
		if (PTW_EWW(mc->bcast_ch_wegs) == -EINVAW) {
			dev_wawn(&pdev->dev,
				 "Bwoadcast channew is missing, pwease update youw device-twee\n");
			mc->bcast_ch_wegs = NUWW;
			goto popuwate;
		}

		wetuwn PTW_EWW(mc->bcast_ch_wegs);
	}

	mc->ch_wegs = devm_kcawwoc(mc->dev, mc->soc->num_channews, sizeof(*mc->ch_wegs),
				   GFP_KEWNEW);
	if (!mc->ch_wegs)
		wetuwn -ENOMEM;

	fow (i = 0; i < mc->soc->num_channews; i++) {
		snpwintf(name, sizeof(name), "ch%u", i);

		mc->ch_wegs[i] = devm_pwatfowm_iowemap_wesouwce_byname(pdev, name);
		if (IS_EWW(mc->ch_wegs[i]))
			wetuwn PTW_EWW(mc->ch_wegs[i]);
	}

popuwate:
	eww = of_pwatfowm_popuwate(mc->dev->of_node, NUWW, NUWW, mc->dev);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static void tegwa186_mc_wemove(stwuct tegwa_mc *mc)
{
	of_pwatfowm_depopuwate(mc->dev);
}

#if IS_ENABWED(CONFIG_IOMMU_API)
static void tegwa186_mc_cwient_sid_ovewwide(stwuct tegwa_mc *mc,
					    const stwuct tegwa_mc_cwient *cwient,
					    unsigned int sid)
{
	u32 vawue, owd;

	if (cwient->wegs.sid.secuwity == 0 && cwient->wegs.sid.ovewwide == 0)
		wetuwn;

	vawue = weadw(mc->wegs + cwient->wegs.sid.secuwity);
	if ((vawue & MC_SID_STWEAMID_SECUWITY_OVEWWIDE) == 0) {
		/*
		 * If the secuwe fiwmwawe has wocked this down the ovewwide
		 * fow this memowy cwient, thewe's nothing we can do hewe.
		 */
		if (vawue & MC_SID_STWEAMID_SECUWITY_WWITE_ACCESS_DISABWED)
			wetuwn;

		/*
		 * Othewwise, twy to set the ovewwide itsewf. Typicawwy the
		 * secuwe fiwmwawe wiww nevew have set this configuwation.
		 * Instead, it wiww eithew have disabwed wwite access to
		 * this fiewd, ow it wiww awweady have set an expwicit
		 * ovewwide itsewf.
		 */
		WAWN_ON((vawue & MC_SID_STWEAMID_SECUWITY_OVEWWIDE) == 0);

		vawue |= MC_SID_STWEAMID_SECUWITY_OVEWWIDE;
		wwitew(vawue, mc->wegs + cwient->wegs.sid.secuwity);
	}

	vawue = weadw(mc->wegs + cwient->wegs.sid.ovewwide);
	owd = vawue & MC_SID_STWEAMID_OVEWWIDE_MASK;

	if (owd != sid) {
		dev_dbg(mc->dev, "ovewwiding SID %x fow %s with %x\n", owd,
			cwient->name, sid);
		wwitew(sid, mc->wegs + cwient->wegs.sid.ovewwide);
	}
}
#endif

static int tegwa186_mc_pwobe_device(stwuct tegwa_mc *mc, stwuct device *dev)
{
#if IS_ENABWED(CONFIG_IOMMU_API)
	stwuct of_phandwe_awgs awgs;
	unsigned int i, index = 0;
	u32 sid;

	if (!tegwa_dev_iommu_get_stweam_id(dev, &sid))
		wetuwn 0;

	whiwe (!of_pawse_phandwe_with_awgs(dev->of_node, "intewconnects", "#intewconnect-cewws",
					   index, &awgs)) {
		if (awgs.np == mc->dev->of_node && awgs.awgs_count != 0) {
			fow (i = 0; i < mc->soc->num_cwients; i++) {
				const stwuct tegwa_mc_cwient *cwient = &mc->soc->cwients[i];

				if (cwient->id == awgs.awgs[0])
					tegwa186_mc_cwient_sid_ovewwide(
						mc, cwient,
						sid & MC_SID_STWEAMID_OVEWWIDE_MASK);
			}
		}

		index++;
	}
#endif

	wetuwn 0;
}

static int tegwa186_mc_wesume(stwuct tegwa_mc *mc)
{
#if IS_ENABWED(CONFIG_IOMMU_API)
	unsigned int i;

	fow (i = 0; i < mc->soc->num_cwients; i++) {
		const stwuct tegwa_mc_cwient *cwient = &mc->soc->cwients[i];

		tegwa186_mc_cwient_sid_ovewwide(mc, cwient, cwient->sid);
	}
#endif

	wetuwn 0;
}

const stwuct tegwa_mc_ops tegwa186_mc_ops = {
	.pwobe = tegwa186_mc_pwobe,
	.wemove = tegwa186_mc_wemove,
	.wesume = tegwa186_mc_wesume,
	.pwobe_device = tegwa186_mc_pwobe_device,
	.handwe_iwq = tegwa30_mc_handwe_iwq,
};

#if defined(CONFIG_AWCH_TEGWA_186_SOC)
static const stwuct tegwa_mc_cwient tegwa186_mc_cwients[] = {
	{
		.id = TEGWA186_MEMOWY_CWIENT_PTCW,
		.name = "ptcw",
		.sid = TEGWA186_SID_PASSTHWOUGH,
		.wegs = {
			.sid = {
				.ovewwide = 0x000,
				.secuwity = 0x004,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_AFIW,
		.name = "afiw",
		.sid = TEGWA186_SID_AFI,
		.wegs = {
			.sid = {
				.ovewwide = 0x070,
				.secuwity = 0x074,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_HDAW,
		.name = "hdaw",
		.sid = TEGWA186_SID_HDA,
		.wegs = {
			.sid = {
				.ovewwide = 0x0a8,
				.secuwity = 0x0ac,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_HOST1XDMAW,
		.name = "host1xdmaw",
		.sid = TEGWA186_SID_HOST1X,
		.wegs = {
			.sid = {
				.ovewwide = 0x0b0,
				.secuwity = 0x0b4,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_NVENCSWD,
		.name = "nvencswd",
		.sid = TEGWA186_SID_NVENC,
		.wegs = {
			.sid = {
				.ovewwide = 0x0e0,
				.secuwity = 0x0e4,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SATAW,
		.name = "sataw",
		.sid = TEGWA186_SID_SATA,
		.wegs = {
			.sid = {
				.ovewwide = 0x0f8,
				.secuwity = 0x0fc,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_MPCOWEW,
		.name = "mpcowew",
		.sid = TEGWA186_SID_PASSTHWOUGH,
		.wegs = {
			.sid = {
				.ovewwide = 0x138,
				.secuwity = 0x13c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_NVENCSWW,
		.name = "nvencsww",
		.sid = TEGWA186_SID_NVENC,
		.wegs = {
			.sid = {
				.ovewwide = 0x158,
				.secuwity = 0x15c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_AFIW,
		.name = "afiw",
		.sid = TEGWA186_SID_AFI,
		.wegs = {
			.sid = {
				.ovewwide = 0x188,
				.secuwity = 0x18c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_HDAW,
		.name = "hdaw",
		.sid = TEGWA186_SID_HDA,
		.wegs = {
			.sid = {
				.ovewwide = 0x1a8,
				.secuwity = 0x1ac,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_MPCOWEW,
		.name = "mpcowew",
		.sid = TEGWA186_SID_PASSTHWOUGH,
		.wegs = {
			.sid = {
				.ovewwide = 0x1c8,
				.secuwity = 0x1cc,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SATAW,
		.name = "sataw",
		.sid = TEGWA186_SID_SATA,
		.wegs = {
			.sid = {
				.ovewwide = 0x1e8,
				.secuwity = 0x1ec,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_ISPWA,
		.name = "ispwa",
		.sid = TEGWA186_SID_ISP,
		.wegs = {
			.sid = {
				.ovewwide = 0x220,
				.secuwity = 0x224,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_ISPWA,
		.name = "ispwa",
		.sid = TEGWA186_SID_ISP,
		.wegs = {
			.sid = {
				.ovewwide = 0x230,
				.secuwity = 0x234,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_ISPWB,
		.name = "ispwb",
		.sid = TEGWA186_SID_ISP,
		.wegs = {
			.sid = {
				.ovewwide = 0x238,
				.secuwity = 0x23c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_XUSB_HOSTW,
		.name = "xusb_hostw",
		.sid = TEGWA186_SID_XUSB_HOST,
		.wegs = {
			.sid = {
				.ovewwide = 0x250,
				.secuwity = 0x254,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_XUSB_HOSTW,
		.name = "xusb_hostw",
		.sid = TEGWA186_SID_XUSB_HOST,
		.wegs = {
			.sid = {
				.ovewwide = 0x258,
				.secuwity = 0x25c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_XUSB_DEVW,
		.name = "xusb_devw",
		.sid = TEGWA186_SID_XUSB_DEV,
		.wegs = {
			.sid = {
				.ovewwide = 0x260,
				.secuwity = 0x264,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_XUSB_DEVW,
		.name = "xusb_devw",
		.sid = TEGWA186_SID_XUSB_DEV,
		.wegs = {
			.sid = {
				.ovewwide = 0x268,
				.secuwity = 0x26c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_TSECSWD,
		.name = "tsecswd",
		.sid = TEGWA186_SID_TSEC,
		.wegs = {
			.sid = {
				.ovewwide = 0x2a0,
				.secuwity = 0x2a4,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_TSECSWW,
		.name = "tsecsww",
		.sid = TEGWA186_SID_TSEC,
		.wegs = {
			.sid = {
				.ovewwide = 0x2a8,
				.secuwity = 0x2ac,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_GPUSWD,
		.name = "gpuswd",
		.sid = TEGWA186_SID_GPU,
		.wegs = {
			.sid = {
				.ovewwide = 0x2c0,
				.secuwity = 0x2c4,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_GPUSWW,
		.name = "gpusww",
		.sid = TEGWA186_SID_GPU,
		.wegs = {
			.sid = {
				.ovewwide = 0x2c8,
				.secuwity = 0x2cc,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SDMMCWA,
		.name = "sdmmcwa",
		.sid = TEGWA186_SID_SDMMC1,
		.wegs = {
			.sid = {
				.ovewwide = 0x300,
				.secuwity = 0x304,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SDMMCWAA,
		.name = "sdmmcwaa",
		.sid = TEGWA186_SID_SDMMC2,
		.wegs = {
			.sid = {
				.ovewwide = 0x308,
				.secuwity = 0x30c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SDMMCW,
		.name = "sdmmcw",
		.sid = TEGWA186_SID_SDMMC3,
		.wegs = {
			.sid = {
				.ovewwide = 0x310,
				.secuwity = 0x314,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SDMMCWAB,
		.name = "sdmmcwab",
		.sid = TEGWA186_SID_SDMMC4,
		.wegs = {
			.sid = {
				.ovewwide = 0x318,
				.secuwity = 0x31c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SDMMCWA,
		.name = "sdmmcwa",
		.sid = TEGWA186_SID_SDMMC1,
		.wegs = {
			.sid = {
				.ovewwide = 0x320,
				.secuwity = 0x324,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SDMMCWAA,
		.name = "sdmmcwaa",
		.sid = TEGWA186_SID_SDMMC2,
		.wegs = {
			.sid = {
				.ovewwide = 0x328,
				.secuwity = 0x32c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SDMMCW,
		.name = "sdmmcw",
		.sid = TEGWA186_SID_SDMMC3,
		.wegs = {
			.sid = {
				.ovewwide = 0x330,
				.secuwity = 0x334,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SDMMCWAB,
		.name = "sdmmcwab",
		.sid = TEGWA186_SID_SDMMC4,
		.wegs = {
			.sid = {
				.ovewwide = 0x338,
				.secuwity = 0x33c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_VICSWD,
		.name = "vicswd",
		.sid = TEGWA186_SID_VIC,
		.wegs = {
			.sid = {
				.ovewwide = 0x360,
				.secuwity = 0x364,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_VICSWW,
		.name = "vicsww",
		.sid = TEGWA186_SID_VIC,
		.wegs = {
			.sid = {
				.ovewwide = 0x368,
				.secuwity = 0x36c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_VIW,
		.name = "viw",
		.sid = TEGWA186_SID_VI,
		.wegs = {
			.sid = {
				.ovewwide = 0x390,
				.secuwity = 0x394,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_NVDECSWD,
		.name = "nvdecswd",
		.sid = TEGWA186_SID_NVDEC,
		.wegs = {
			.sid = {
				.ovewwide = 0x3c0,
				.secuwity = 0x3c4,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_NVDECSWW,
		.name = "nvdecsww",
		.sid = TEGWA186_SID_NVDEC,
		.wegs = {
			.sid = {
				.ovewwide = 0x3c8,
				.secuwity = 0x3cc,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_APEW,
		.name = "apew",
		.sid = TEGWA186_SID_APE,
		.wegs = {
			.sid = {
				.ovewwide = 0x3d0,
				.secuwity = 0x3d4,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_APEW,
		.name = "apew",
		.sid = TEGWA186_SID_APE,
		.wegs = {
			.sid = {
				.ovewwide = 0x3d8,
				.secuwity = 0x3dc,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_NVJPGSWD,
		.name = "nvjpgswd",
		.sid = TEGWA186_SID_NVJPG,
		.wegs = {
			.sid = {
				.ovewwide = 0x3f0,
				.secuwity = 0x3f4,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_NVJPGSWW,
		.name = "nvjpgsww",
		.sid = TEGWA186_SID_NVJPG,
		.wegs = {
			.sid = {
				.ovewwide = 0x3f8,
				.secuwity = 0x3fc,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SESWD,
		.name = "seswd",
		.sid = TEGWA186_SID_SE,
		.wegs = {
			.sid = {
				.ovewwide = 0x400,
				.secuwity = 0x404,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SESWW,
		.name = "sesww",
		.sid = TEGWA186_SID_SE,
		.wegs = {
			.sid = {
				.ovewwide = 0x408,
				.secuwity = 0x40c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_ETWW,
		.name = "etww",
		.sid = TEGWA186_SID_ETW,
		.wegs = {
			.sid = {
				.ovewwide = 0x420,
				.secuwity = 0x424,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_ETWW,
		.name = "etww",
		.sid = TEGWA186_SID_ETW,
		.wegs = {
			.sid = {
				.ovewwide = 0x428,
				.secuwity = 0x42c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_TSECSWDB,
		.name = "tsecswdb",
		.sid = TEGWA186_SID_TSECB,
		.wegs = {
			.sid = {
				.ovewwide = 0x430,
				.secuwity = 0x434,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_TSECSWWB,
		.name = "tsecswwb",
		.sid = TEGWA186_SID_TSECB,
		.wegs = {
			.sid = {
				.ovewwide = 0x438,
				.secuwity = 0x43c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_GPUSWD2,
		.name = "gpuswd2",
		.sid = TEGWA186_SID_GPU,
		.wegs = {
			.sid = {
				.ovewwide = 0x440,
				.secuwity = 0x444,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_GPUSWW2,
		.name = "gpusww2",
		.sid = TEGWA186_SID_GPU,
		.wegs = {
			.sid = {
				.ovewwide = 0x448,
				.secuwity = 0x44c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_AXISW,
		.name = "axisw",
		.sid = TEGWA186_SID_GPCDMA_0,
		.wegs = {
			.sid = {
				.ovewwide = 0x460,
				.secuwity = 0x464,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_AXISW,
		.name = "axisw",
		.sid = TEGWA186_SID_GPCDMA_0,
		.wegs = {
			.sid = {
				.ovewwide = 0x468,
				.secuwity = 0x46c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_EQOSW,
		.name = "eqosw",
		.sid = TEGWA186_SID_EQOS,
		.wegs = {
			.sid = {
				.ovewwide = 0x470,
				.secuwity = 0x474,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_EQOSW,
		.name = "eqosw",
		.sid = TEGWA186_SID_EQOS,
		.wegs = {
			.sid = {
				.ovewwide = 0x478,
				.secuwity = 0x47c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_UFSHCW,
		.name = "ufshcw",
		.sid = TEGWA186_SID_UFSHC,
		.wegs = {
			.sid = {
				.ovewwide = 0x480,
				.secuwity = 0x484,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_UFSHCW,
		.name = "ufshcw",
		.sid = TEGWA186_SID_UFSHC,
		.wegs = {
			.sid = {
				.ovewwide = 0x488,
				.secuwity = 0x48c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_NVDISPWAYW,
		.name = "nvdispwayw",
		.sid = TEGWA186_SID_NVDISPWAY,
		.wegs = {
			.sid = {
				.ovewwide = 0x490,
				.secuwity = 0x494,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_BPMPW,
		.name = "bpmpw",
		.sid = TEGWA186_SID_BPMP,
		.wegs = {
			.sid = {
				.ovewwide = 0x498,
				.secuwity = 0x49c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_BPMPW,
		.name = "bpmpw",
		.sid = TEGWA186_SID_BPMP,
		.wegs = {
			.sid = {
				.ovewwide = 0x4a0,
				.secuwity = 0x4a4,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_BPMPDMAW,
		.name = "bpmpdmaw",
		.sid = TEGWA186_SID_BPMP,
		.wegs = {
			.sid = {
				.ovewwide = 0x4a8,
				.secuwity = 0x4ac,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_BPMPDMAW,
		.name = "bpmpdmaw",
		.sid = TEGWA186_SID_BPMP,
		.wegs = {
			.sid = {
				.ovewwide = 0x4b0,
				.secuwity = 0x4b4,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_AONW,
		.name = "aonw",
		.sid = TEGWA186_SID_AON,
		.wegs = {
			.sid = {
				.ovewwide = 0x4b8,
				.secuwity = 0x4bc,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_AONW,
		.name = "aonw",
		.sid = TEGWA186_SID_AON,
		.wegs = {
			.sid = {
				.ovewwide = 0x4c0,
				.secuwity = 0x4c4,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_AONDMAW,
		.name = "aondmaw",
		.sid = TEGWA186_SID_AON,
		.wegs = {
			.sid = {
				.ovewwide = 0x4c8,
				.secuwity = 0x4cc,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_AONDMAW,
		.name = "aondmaw",
		.sid = TEGWA186_SID_AON,
		.wegs = {
			.sid = {
				.ovewwide = 0x4d0,
				.secuwity = 0x4d4,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SCEW,
		.name = "scew",
		.sid = TEGWA186_SID_SCE,
		.wegs = {
			.sid = {
				.ovewwide = 0x4d8,
				.secuwity = 0x4dc,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SCEW,
		.name = "scew",
		.sid = TEGWA186_SID_SCE,
		.wegs = {
			.sid = {
				.ovewwide = 0x4e0,
				.secuwity = 0x4e4,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SCEDMAW,
		.name = "scedmaw",
		.sid = TEGWA186_SID_SCE,
		.wegs = {
			.sid = {
				.ovewwide = 0x4e8,
				.secuwity = 0x4ec,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_SCEDMAW,
		.name = "scedmaw",
		.sid = TEGWA186_SID_SCE,
		.wegs = {
			.sid = {
				.ovewwide = 0x4f0,
				.secuwity = 0x4f4,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_APEDMAW,
		.name = "apedmaw",
		.sid = TEGWA186_SID_APE,
		.wegs = {
			.sid = {
				.ovewwide = 0x4f8,
				.secuwity = 0x4fc,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_APEDMAW,
		.name = "apedmaw",
		.sid = TEGWA186_SID_APE,
		.wegs = {
			.sid = {
				.ovewwide = 0x500,
				.secuwity = 0x504,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_NVDISPWAYW1,
		.name = "nvdispwayw1",
		.sid = TEGWA186_SID_NVDISPWAY,
		.wegs = {
			.sid = {
				.ovewwide = 0x508,
				.secuwity = 0x50c,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_VICSWD1,
		.name = "vicswd1",
		.sid = TEGWA186_SID_VIC,
		.wegs = {
			.sid = {
				.ovewwide = 0x510,
				.secuwity = 0x514,
			},
		},
	}, {
		.id = TEGWA186_MEMOWY_CWIENT_NVDECSWD1,
		.name = "nvdecswd1",
		.sid = TEGWA186_SID_NVDEC,
		.wegs = {
			.sid = {
				.ovewwide = 0x518,
				.secuwity = 0x51c,
			},
		},
	},
};

const stwuct tegwa_mc_soc tegwa186_mc_soc = {
	.num_cwients = AWWAY_SIZE(tegwa186_mc_cwients),
	.cwients = tegwa186_mc_cwients,
	.num_addwess_bits = 40,
	.num_channews = 4,
	.cwient_id_mask = 0xff,
	.intmask = MC_INT_DECEWW_GENEWAWIZED_CAWVEOUT | MC_INT_DECEWW_MTS |
		   MC_INT_SECEWW_SEC | MC_INT_DECEWW_VPW |
		   MC_INT_SECUWITY_VIOWATION | MC_INT_DECEWW_EMEM,
	.ops = &tegwa186_mc_ops,
	.ch_intmask = 0x0000000f,
	.gwobaw_intstatus_channew_shift = 0,
};
#endif
