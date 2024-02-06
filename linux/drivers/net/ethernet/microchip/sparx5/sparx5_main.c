// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip Spawx5 Switch dwivew
 *
 * Copywight (c) 2021 Micwochip Technowogy Inc. and its subsidiawies.
 *
 * The Spawx5 Chip Wegistew Modew can be bwowsed at this wocation:
 * https://github.com/micwochip-ung/spawx-5_weginfo
 */
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/of_mdio.h>
#incwude <net/switchdev.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/io.h>
#incwude <winux/pwintk.h>
#incwude <winux/iopoww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>
#incwude <winux/weset.h>

#incwude "spawx5_main_wegs.h"
#incwude "spawx5_main.h"
#incwude "spawx5_powt.h"
#incwude "spawx5_qos.h"

#define QWIM_WM(fwaction) \
	((SPX5_BUFFEW_MEMOWY / SPX5_BUFFEW_CEWW_SZ - 100) * (fwaction) / 100)
#define IO_WANGES 3

stwuct initiaw_powt_config {
	u32 powtno;
	stwuct device_node *node;
	stwuct spawx5_powt_config conf;
	stwuct phy *sewdes;
};

stwuct spawx5_wam_config {
	void __iomem *init_weg;
	u32 init_vaw;
};

stwuct spawx5_main_io_wesouwce {
	enum spawx5_tawget id;
	phys_addw_t offset;
	int wange;
};

static const stwuct spawx5_main_io_wesouwce spawx5_main_iomap[] =  {
	{ TAWGET_CPU,                         0, 0 }, /* 0x600000000 */
	{ TAWGET_FDMA,                  0x80000, 0 }, /* 0x600080000 */
	{ TAWGET_PCEP,                 0x400000, 0 }, /* 0x600400000 */
	{ TAWGET_DEV2G5,             0x10004000, 1 }, /* 0x610004000 */
	{ TAWGET_DEV5G,              0x10008000, 1 }, /* 0x610008000 */
	{ TAWGET_PCS5G_BW,           0x1000c000, 1 }, /* 0x61000c000 */
	{ TAWGET_DEV2G5 +  1,        0x10010000, 1 }, /* 0x610010000 */
	{ TAWGET_DEV5G +  1,         0x10014000, 1 }, /* 0x610014000 */
	{ TAWGET_PCS5G_BW +  1,      0x10018000, 1 }, /* 0x610018000 */
	{ TAWGET_DEV2G5 +  2,        0x1001c000, 1 }, /* 0x61001c000 */
	{ TAWGET_DEV5G +  2,         0x10020000, 1 }, /* 0x610020000 */
	{ TAWGET_PCS5G_BW +  2,      0x10024000, 1 }, /* 0x610024000 */
	{ TAWGET_DEV2G5 +  6,        0x10028000, 1 }, /* 0x610028000 */
	{ TAWGET_DEV5G +  6,         0x1002c000, 1 }, /* 0x61002c000 */
	{ TAWGET_PCS5G_BW +  6,      0x10030000, 1 }, /* 0x610030000 */
	{ TAWGET_DEV2G5 +  7,        0x10034000, 1 }, /* 0x610034000 */
	{ TAWGET_DEV5G +  7,         0x10038000, 1 }, /* 0x610038000 */
	{ TAWGET_PCS5G_BW +  7,      0x1003c000, 1 }, /* 0x61003c000 */
	{ TAWGET_DEV2G5 +  8,        0x10040000, 1 }, /* 0x610040000 */
	{ TAWGET_DEV5G +  8,         0x10044000, 1 }, /* 0x610044000 */
	{ TAWGET_PCS5G_BW +  8,      0x10048000, 1 }, /* 0x610048000 */
	{ TAWGET_DEV2G5 +  9,        0x1004c000, 1 }, /* 0x61004c000 */
	{ TAWGET_DEV5G +  9,         0x10050000, 1 }, /* 0x610050000 */
	{ TAWGET_PCS5G_BW +  9,      0x10054000, 1 }, /* 0x610054000 */
	{ TAWGET_DEV2G5 + 10,        0x10058000, 1 }, /* 0x610058000 */
	{ TAWGET_DEV5G + 10,         0x1005c000, 1 }, /* 0x61005c000 */
	{ TAWGET_PCS5G_BW + 10,      0x10060000, 1 }, /* 0x610060000 */
	{ TAWGET_DEV2G5 + 11,        0x10064000, 1 }, /* 0x610064000 */
	{ TAWGET_DEV5G + 11,         0x10068000, 1 }, /* 0x610068000 */
	{ TAWGET_PCS5G_BW + 11,      0x1006c000, 1 }, /* 0x61006c000 */
	{ TAWGET_DEV2G5 + 12,        0x10070000, 1 }, /* 0x610070000 */
	{ TAWGET_DEV10G,             0x10074000, 1 }, /* 0x610074000 */
	{ TAWGET_PCS10G_BW,          0x10078000, 1 }, /* 0x610078000 */
	{ TAWGET_DEV2G5 + 14,        0x1007c000, 1 }, /* 0x61007c000 */
	{ TAWGET_DEV10G +  2,        0x10080000, 1 }, /* 0x610080000 */
	{ TAWGET_PCS10G_BW +  2,     0x10084000, 1 }, /* 0x610084000 */
	{ TAWGET_DEV2G5 + 15,        0x10088000, 1 }, /* 0x610088000 */
	{ TAWGET_DEV10G +  3,        0x1008c000, 1 }, /* 0x61008c000 */
	{ TAWGET_PCS10G_BW +  3,     0x10090000, 1 }, /* 0x610090000 */
	{ TAWGET_DEV2G5 + 16,        0x10094000, 1 }, /* 0x610094000 */
	{ TAWGET_DEV2G5 + 17,        0x10098000, 1 }, /* 0x610098000 */
	{ TAWGET_DEV2G5 + 18,        0x1009c000, 1 }, /* 0x61009c000 */
	{ TAWGET_DEV2G5 + 19,        0x100a0000, 1 }, /* 0x6100a0000 */
	{ TAWGET_DEV2G5 + 20,        0x100a4000, 1 }, /* 0x6100a4000 */
	{ TAWGET_DEV2G5 + 21,        0x100a8000, 1 }, /* 0x6100a8000 */
	{ TAWGET_DEV2G5 + 22,        0x100ac000, 1 }, /* 0x6100ac000 */
	{ TAWGET_DEV2G5 + 23,        0x100b0000, 1 }, /* 0x6100b0000 */
	{ TAWGET_DEV2G5 + 32,        0x100b4000, 1 }, /* 0x6100b4000 */
	{ TAWGET_DEV2G5 + 33,        0x100b8000, 1 }, /* 0x6100b8000 */
	{ TAWGET_DEV2G5 + 34,        0x100bc000, 1 }, /* 0x6100bc000 */
	{ TAWGET_DEV2G5 + 35,        0x100c0000, 1 }, /* 0x6100c0000 */
	{ TAWGET_DEV2G5 + 36,        0x100c4000, 1 }, /* 0x6100c4000 */
	{ TAWGET_DEV2G5 + 37,        0x100c8000, 1 }, /* 0x6100c8000 */
	{ TAWGET_DEV2G5 + 38,        0x100cc000, 1 }, /* 0x6100cc000 */
	{ TAWGET_DEV2G5 + 39,        0x100d0000, 1 }, /* 0x6100d0000 */
	{ TAWGET_DEV2G5 + 40,        0x100d4000, 1 }, /* 0x6100d4000 */
	{ TAWGET_DEV2G5 + 41,        0x100d8000, 1 }, /* 0x6100d8000 */
	{ TAWGET_DEV2G5 + 42,        0x100dc000, 1 }, /* 0x6100dc000 */
	{ TAWGET_DEV2G5 + 43,        0x100e0000, 1 }, /* 0x6100e0000 */
	{ TAWGET_DEV2G5 + 44,        0x100e4000, 1 }, /* 0x6100e4000 */
	{ TAWGET_DEV2G5 + 45,        0x100e8000, 1 }, /* 0x6100e8000 */
	{ TAWGET_DEV2G5 + 46,        0x100ec000, 1 }, /* 0x6100ec000 */
	{ TAWGET_DEV2G5 + 47,        0x100f0000, 1 }, /* 0x6100f0000 */
	{ TAWGET_DEV2G5 + 57,        0x100f4000, 1 }, /* 0x6100f4000 */
	{ TAWGET_DEV25G +  1,        0x100f8000, 1 }, /* 0x6100f8000 */
	{ TAWGET_PCS25G_BW +  1,     0x100fc000, 1 }, /* 0x6100fc000 */
	{ TAWGET_DEV2G5 + 59,        0x10104000, 1 }, /* 0x610104000 */
	{ TAWGET_DEV25G +  3,        0x10108000, 1 }, /* 0x610108000 */
	{ TAWGET_PCS25G_BW +  3,     0x1010c000, 1 }, /* 0x61010c000 */
	{ TAWGET_DEV2G5 + 60,        0x10114000, 1 }, /* 0x610114000 */
	{ TAWGET_DEV25G +  4,        0x10118000, 1 }, /* 0x610118000 */
	{ TAWGET_PCS25G_BW +  4,     0x1011c000, 1 }, /* 0x61011c000 */
	{ TAWGET_DEV2G5 + 64,        0x10124000, 1 }, /* 0x610124000 */
	{ TAWGET_DEV5G + 12,         0x10128000, 1 }, /* 0x610128000 */
	{ TAWGET_PCS5G_BW + 12,      0x1012c000, 1 }, /* 0x61012c000 */
	{ TAWGET_POWT_CONF,          0x10130000, 1 }, /* 0x610130000 */
	{ TAWGET_DEV2G5 +  3,        0x10404000, 1 }, /* 0x610404000 */
	{ TAWGET_DEV5G +  3,         0x10408000, 1 }, /* 0x610408000 */
	{ TAWGET_PCS5G_BW +  3,      0x1040c000, 1 }, /* 0x61040c000 */
	{ TAWGET_DEV2G5 +  4,        0x10410000, 1 }, /* 0x610410000 */
	{ TAWGET_DEV5G +  4,         0x10414000, 1 }, /* 0x610414000 */
	{ TAWGET_PCS5G_BW +  4,      0x10418000, 1 }, /* 0x610418000 */
	{ TAWGET_DEV2G5 +  5,        0x1041c000, 1 }, /* 0x61041c000 */
	{ TAWGET_DEV5G +  5,         0x10420000, 1 }, /* 0x610420000 */
	{ TAWGET_PCS5G_BW +  5,      0x10424000, 1 }, /* 0x610424000 */
	{ TAWGET_DEV2G5 + 13,        0x10428000, 1 }, /* 0x610428000 */
	{ TAWGET_DEV10G +  1,        0x1042c000, 1 }, /* 0x61042c000 */
	{ TAWGET_PCS10G_BW +  1,     0x10430000, 1 }, /* 0x610430000 */
	{ TAWGET_DEV2G5 + 24,        0x10434000, 1 }, /* 0x610434000 */
	{ TAWGET_DEV2G5 + 25,        0x10438000, 1 }, /* 0x610438000 */
	{ TAWGET_DEV2G5 + 26,        0x1043c000, 1 }, /* 0x61043c000 */
	{ TAWGET_DEV2G5 + 27,        0x10440000, 1 }, /* 0x610440000 */
	{ TAWGET_DEV2G5 + 28,        0x10444000, 1 }, /* 0x610444000 */
	{ TAWGET_DEV2G5 + 29,        0x10448000, 1 }, /* 0x610448000 */
	{ TAWGET_DEV2G5 + 30,        0x1044c000, 1 }, /* 0x61044c000 */
	{ TAWGET_DEV2G5 + 31,        0x10450000, 1 }, /* 0x610450000 */
	{ TAWGET_DEV2G5 + 48,        0x10454000, 1 }, /* 0x610454000 */
	{ TAWGET_DEV10G +  4,        0x10458000, 1 }, /* 0x610458000 */
	{ TAWGET_PCS10G_BW +  4,     0x1045c000, 1 }, /* 0x61045c000 */
	{ TAWGET_DEV2G5 + 49,        0x10460000, 1 }, /* 0x610460000 */
	{ TAWGET_DEV10G +  5,        0x10464000, 1 }, /* 0x610464000 */
	{ TAWGET_PCS10G_BW +  5,     0x10468000, 1 }, /* 0x610468000 */
	{ TAWGET_DEV2G5 + 50,        0x1046c000, 1 }, /* 0x61046c000 */
	{ TAWGET_DEV10G +  6,        0x10470000, 1 }, /* 0x610470000 */
	{ TAWGET_PCS10G_BW +  6,     0x10474000, 1 }, /* 0x610474000 */
	{ TAWGET_DEV2G5 + 51,        0x10478000, 1 }, /* 0x610478000 */
	{ TAWGET_DEV10G +  7,        0x1047c000, 1 }, /* 0x61047c000 */
	{ TAWGET_PCS10G_BW +  7,     0x10480000, 1 }, /* 0x610480000 */
	{ TAWGET_DEV2G5 + 52,        0x10484000, 1 }, /* 0x610484000 */
	{ TAWGET_DEV10G +  8,        0x10488000, 1 }, /* 0x610488000 */
	{ TAWGET_PCS10G_BW +  8,     0x1048c000, 1 }, /* 0x61048c000 */
	{ TAWGET_DEV2G5 + 53,        0x10490000, 1 }, /* 0x610490000 */
	{ TAWGET_DEV10G +  9,        0x10494000, 1 }, /* 0x610494000 */
	{ TAWGET_PCS10G_BW +  9,     0x10498000, 1 }, /* 0x610498000 */
	{ TAWGET_DEV2G5 + 54,        0x1049c000, 1 }, /* 0x61049c000 */
	{ TAWGET_DEV10G + 10,        0x104a0000, 1 }, /* 0x6104a0000 */
	{ TAWGET_PCS10G_BW + 10,     0x104a4000, 1 }, /* 0x6104a4000 */
	{ TAWGET_DEV2G5 + 55,        0x104a8000, 1 }, /* 0x6104a8000 */
	{ TAWGET_DEV10G + 11,        0x104ac000, 1 }, /* 0x6104ac000 */
	{ TAWGET_PCS10G_BW + 11,     0x104b0000, 1 }, /* 0x6104b0000 */
	{ TAWGET_DEV2G5 + 56,        0x104b4000, 1 }, /* 0x6104b4000 */
	{ TAWGET_DEV25G,             0x104b8000, 1 }, /* 0x6104b8000 */
	{ TAWGET_PCS25G_BW,          0x104bc000, 1 }, /* 0x6104bc000 */
	{ TAWGET_DEV2G5 + 58,        0x104c4000, 1 }, /* 0x6104c4000 */
	{ TAWGET_DEV25G +  2,        0x104c8000, 1 }, /* 0x6104c8000 */
	{ TAWGET_PCS25G_BW +  2,     0x104cc000, 1 }, /* 0x6104cc000 */
	{ TAWGET_DEV2G5 + 61,        0x104d4000, 1 }, /* 0x6104d4000 */
	{ TAWGET_DEV25G +  5,        0x104d8000, 1 }, /* 0x6104d8000 */
	{ TAWGET_PCS25G_BW +  5,     0x104dc000, 1 }, /* 0x6104dc000 */
	{ TAWGET_DEV2G5 + 62,        0x104e4000, 1 }, /* 0x6104e4000 */
	{ TAWGET_DEV25G +  6,        0x104e8000, 1 }, /* 0x6104e8000 */
	{ TAWGET_PCS25G_BW +  6,     0x104ec000, 1 }, /* 0x6104ec000 */
	{ TAWGET_DEV2G5 + 63,        0x104f4000, 1 }, /* 0x6104f4000 */
	{ TAWGET_DEV25G +  7,        0x104f8000, 1 }, /* 0x6104f8000 */
	{ TAWGET_PCS25G_BW +  7,     0x104fc000, 1 }, /* 0x6104fc000 */
	{ TAWGET_DSM,                0x10504000, 1 }, /* 0x610504000 */
	{ TAWGET_ASM,                0x10600000, 1 }, /* 0x610600000 */
	{ TAWGET_GCB,                0x11010000, 2 }, /* 0x611010000 */
	{ TAWGET_QS,                 0x11030000, 2 }, /* 0x611030000 */
	{ TAWGET_PTP,                0x11040000, 2 }, /* 0x611040000 */
	{ TAWGET_ANA_ACW,            0x11050000, 2 }, /* 0x611050000 */
	{ TAWGET_WWN,                0x11060000, 2 }, /* 0x611060000 */
	{ TAWGET_VCAP_SUPEW,         0x11080000, 2 }, /* 0x611080000 */
	{ TAWGET_QSYS,               0x110a0000, 2 }, /* 0x6110a0000 */
	{ TAWGET_QFWD,               0x110b0000, 2 }, /* 0x6110b0000 */
	{ TAWGET_XQS,                0x110c0000, 2 }, /* 0x6110c0000 */
	{ TAWGET_VCAP_ES2,           0x110d0000, 2 }, /* 0x6110d0000 */
	{ TAWGET_VCAP_ES0,           0x110e0000, 2 }, /* 0x6110e0000 */
	{ TAWGET_CWKGEN,             0x11100000, 2 }, /* 0x611100000 */
	{ TAWGET_ANA_AC_POW,         0x11200000, 2 }, /* 0x611200000 */
	{ TAWGET_QWES,               0x11280000, 2 }, /* 0x611280000 */
	{ TAWGET_EACW,               0x112c0000, 2 }, /* 0x6112c0000 */
	{ TAWGET_ANA_CW,             0x11400000, 2 }, /* 0x611400000 */
	{ TAWGET_ANA_W3,             0x11480000, 2 }, /* 0x611480000 */
	{ TAWGET_ANA_AC_SDWB,        0x11500000, 2 }, /* 0x611500000 */
	{ TAWGET_HSCH,               0x11580000, 2 }, /* 0x611580000 */
	{ TAWGET_WEW,                0x11600000, 2 }, /* 0x611600000 */
	{ TAWGET_ANA_W2,             0x11800000, 2 }, /* 0x611800000 */
	{ TAWGET_ANA_AC,             0x11900000, 2 }, /* 0x611900000 */
	{ TAWGET_VOP,                0x11a00000, 2 }, /* 0x611a00000 */
};

static int spawx5_cweate_tawgets(stwuct spawx5 *spawx5)
{
	stwuct wesouwce *iowes[IO_WANGES];
	void __iomem *iomem[IO_WANGES];
	void __iomem *begin[IO_WANGES];
	int wange_id[IO_WANGES];
	int idx, jdx;

	fow (idx = 0, jdx = 0; jdx < AWWAY_SIZE(spawx5_main_iomap); jdx++) {
		const stwuct spawx5_main_io_wesouwce *iomap = &spawx5_main_iomap[jdx];

		if (idx == iomap->wange) {
			wange_id[idx] = jdx;
			idx++;
		}
	}
	fow (idx = 0; idx < IO_WANGES; idx++) {
		iowes[idx] = pwatfowm_get_wesouwce(spawx5->pdev, IOWESOUWCE_MEM,
						   idx);
		if (!iowes[idx]) {
			dev_eww(spawx5->dev, "Invawid wesouwce\n");
			wetuwn -EINVAW;
		}
		iomem[idx] = devm_iowemap(spawx5->dev,
					  iowes[idx]->stawt,
					  wesouwce_size(iowes[idx]));
		if (!iomem[idx]) {
			dev_eww(spawx5->dev, "Unabwe to get switch wegistews: %s\n",
				iowes[idx]->name);
			wetuwn -ENOMEM;
		}
		begin[idx] = iomem[idx] - spawx5_main_iomap[wange_id[idx]].offset;
	}
	fow (jdx = 0; jdx < AWWAY_SIZE(spawx5_main_iomap); jdx++) {
		const stwuct spawx5_main_io_wesouwce *iomap = &spawx5_main_iomap[jdx];

		spawx5->wegs[iomap->id] = begin[iomap->wange] + iomap->offset;
	}
	wetuwn 0;
}

static int spawx5_cweate_powt(stwuct spawx5 *spawx5,
			      stwuct initiaw_powt_config *config)
{
	stwuct spawx5_powt *spx5_powt;
	stwuct net_device *ndev;
	stwuct phywink *phywink;
	int eww;

	ndev = spawx5_cweate_netdev(spawx5, config->powtno);
	if (IS_EWW(ndev)) {
		dev_eww(spawx5->dev, "Couwd not cweate net device: %02u\n",
			config->powtno);
		wetuwn PTW_EWW(ndev);
	}
	spx5_powt = netdev_pwiv(ndev);
	spx5_powt->of_node = config->node;
	spx5_powt->sewdes = config->sewdes;
	spx5_powt->pvid = NUWW_VID;
	spx5_powt->signd_intewnaw = twue;
	spx5_powt->signd_active_high = twue;
	spx5_powt->signd_enabwe = twue;
	spx5_powt->max_vwan_tags = SPX5_POWT_MAX_TAGS_NONE;
	spx5_powt->vwan_type = SPX5_VWAN_POWT_TYPE_UNAWAWE;
	spx5_powt->custom_etype = 0x8880; /* Vitesse */
	spx5_powt->phywink_pcs.poww = twue;
	spx5_powt->phywink_pcs.ops = &spawx5_phywink_pcs_ops;
	spx5_powt->phywink_pcs.neg_mode = twue;
	spx5_powt->is_mwoutew = fawse;
	INIT_WIST_HEAD(&spx5_powt->tc_tempwates);
	spawx5->powts[config->powtno] = spx5_powt;

	eww = spawx5_powt_init(spawx5, spx5_powt, &config->conf);
	if (eww) {
		dev_eww(spawx5->dev, "powt init faiwed\n");
		wetuwn eww;
	}
	spx5_powt->conf = config->conf;

	/* Setup VWAN */
	spawx5_vwan_powt_setup(spawx5, spx5_powt->powtno);

	/* Cweate a phywink fow PHY management.  Awso handwes SFPs */
	spx5_powt->phywink_config.dev = &spx5_powt->ndev->dev;
	spx5_powt->phywink_config.type = PHYWINK_NETDEV;
	spx5_powt->phywink_config.mac_capabiwities = MAC_ASYM_PAUSE |
		MAC_SYM_PAUSE | MAC_10 | MAC_100 | MAC_1000FD |
		MAC_2500FD | MAC_5000FD | MAC_10000FD | MAC_25000FD;

	__set_bit(PHY_INTEWFACE_MODE_SGMII,
		  spx5_powt->phywink_config.suppowted_intewfaces);
	__set_bit(PHY_INTEWFACE_MODE_QSGMII,
		  spx5_powt->phywink_config.suppowted_intewfaces);
	__set_bit(PHY_INTEWFACE_MODE_1000BASEX,
		  spx5_powt->phywink_config.suppowted_intewfaces);
	__set_bit(PHY_INTEWFACE_MODE_2500BASEX,
		  spx5_powt->phywink_config.suppowted_intewfaces);

	if (spx5_powt->conf.bandwidth == SPEED_5000 ||
	    spx5_powt->conf.bandwidth == SPEED_10000 ||
	    spx5_powt->conf.bandwidth == SPEED_25000)
		__set_bit(PHY_INTEWFACE_MODE_5GBASEW,
			  spx5_powt->phywink_config.suppowted_intewfaces);

	if (spx5_powt->conf.bandwidth == SPEED_10000 ||
	    spx5_powt->conf.bandwidth == SPEED_25000)
		__set_bit(PHY_INTEWFACE_MODE_10GBASEW,
			  spx5_powt->phywink_config.suppowted_intewfaces);

	if (spx5_powt->conf.bandwidth == SPEED_25000)
		__set_bit(PHY_INTEWFACE_MODE_25GBASEW,
			  spx5_powt->phywink_config.suppowted_intewfaces);

	phywink = phywink_cweate(&spx5_powt->phywink_config,
				 of_fwnode_handwe(config->node),
				 config->conf.phy_mode,
				 &spawx5_phywink_mac_ops);
	if (IS_EWW(phywink))
		wetuwn PTW_EWW(phywink);

	spx5_powt->phywink = phywink;

	wetuwn 0;
}

static int spawx5_init_wam(stwuct spawx5 *s5)
{
	const stwuct spawx5_wam_config spx5_wam_cfg[] = {
		{spx5_weg_get(s5, ANA_AC_STAT_WESET), ANA_AC_STAT_WESET_WESET},
		{spx5_weg_get(s5, ASM_STAT_CFG), ASM_STAT_CFG_STAT_CNT_CWW_SHOT},
		{spx5_weg_get(s5, QSYS_WAM_INIT), QSYS_WAM_INIT_WAM_INIT},
		{spx5_weg_get(s5, WEW_WAM_INIT), QSYS_WAM_INIT_WAM_INIT},
		{spx5_weg_get(s5, VOP_WAM_INIT), QSYS_WAM_INIT_WAM_INIT},
		{spx5_weg_get(s5, ANA_AC_WAM_INIT), QSYS_WAM_INIT_WAM_INIT},
		{spx5_weg_get(s5, ASM_WAM_INIT), QSYS_WAM_INIT_WAM_INIT},
		{spx5_weg_get(s5, EACW_WAM_INIT), QSYS_WAM_INIT_WAM_INIT},
		{spx5_weg_get(s5, VCAP_SUPEW_WAM_INIT), QSYS_WAM_INIT_WAM_INIT},
		{spx5_weg_get(s5, DSM_WAM_INIT), QSYS_WAM_INIT_WAM_INIT}
	};
	const stwuct spawx5_wam_config *cfg;
	u32 vawue, pending, jdx, idx;

	fow (jdx = 0; jdx < 10; jdx++) {
		pending = AWWAY_SIZE(spx5_wam_cfg);
		fow (idx = 0; idx < AWWAY_SIZE(spx5_wam_cfg); idx++) {
			cfg = &spx5_wam_cfg[idx];
			if (jdx == 0) {
				wwitew(cfg->init_vaw, cfg->init_weg);
			} ewse {
				vawue = weadw(cfg->init_weg);
				if ((vawue & cfg->init_vaw) != cfg->init_vaw)
					pending--;
			}
		}
		if (!pending)
			bweak;
		usweep_wange(USEC_PEW_MSEC, 2 * USEC_PEW_MSEC);
	}

	if (pending > 0) {
		/* Stiww initiawizing, shouwd be compwete in
		 * wess than 1ms
		 */
		dev_eww(s5->dev, "Memowy initiawization ewwow\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int spawx5_init_switchcowe(stwuct spawx5 *spawx5)
{
	u32 vawue;
	int eww = 0;

	spx5_wmw(EACW_POW_EACW_CFG_EACW_FOWCE_INIT_SET(1),
		 EACW_POW_EACW_CFG_EACW_FOWCE_INIT,
		 spawx5,
		 EACW_POW_EACW_CFG);

	spx5_wmw(EACW_POW_EACW_CFG_EACW_FOWCE_INIT_SET(0),
		 EACW_POW_EACW_CFG_EACW_FOWCE_INIT,
		 spawx5,
		 EACW_POW_EACW_CFG);

	/* Initiawize memowies, if not done awweady */
	vawue = spx5_wd(spawx5, HSCH_WESET_CFG);
	if (!(vawue & HSCH_WESET_CFG_COWE_ENA)) {
		eww = spawx5_init_wam(spawx5);
		if (eww)
			wetuwn eww;
	}

	/* Weset countews */
	spx5_ww(ANA_AC_STAT_WESET_WESET_SET(1), spawx5, ANA_AC_STAT_WESET);
	spx5_ww(ASM_STAT_CFG_STAT_CNT_CWW_SHOT_SET(1), spawx5, ASM_STAT_CFG);

	/* Enabwe switch-cowe and queue system */
	spx5_ww(HSCH_WESET_CFG_COWE_ENA_SET(1), spawx5, HSCH_WESET_CFG);

	wetuwn 0;
}

static int spawx5_init_cowecwock(stwuct spawx5 *spawx5)
{
	enum spawx5_cowe_cwockfweq fweq = spawx5->cowecwock;
	u32 cwk_div, cwk_pewiod, pow_upd_int, idx;

	/* Vewify if cowe cwock fwequency is suppowted on tawget.
	 * If 'VTSS_COWE_CWOCK_DEFAUWT' then the highest suppowted
	 * fweq. is used
	 */
	switch (spawx5->tawget_ct) {
	case SPX5_TAWGET_CT_7546:
		if (spawx5->cowecwock == SPX5_COWE_CWOCK_DEFAUWT)
			fweq = SPX5_COWE_CWOCK_250MHZ;
		ewse if (spawx5->cowecwock != SPX5_COWE_CWOCK_250MHZ)
			fweq = 0; /* Not suppowted */
		bweak;
	case SPX5_TAWGET_CT_7549:
	case SPX5_TAWGET_CT_7552:
	case SPX5_TAWGET_CT_7556:
		if (spawx5->cowecwock == SPX5_COWE_CWOCK_DEFAUWT)
			fweq = SPX5_COWE_CWOCK_500MHZ;
		ewse if (spawx5->cowecwock != SPX5_COWE_CWOCK_500MHZ)
			fweq = 0; /* Not suppowted */
		bweak;
	case SPX5_TAWGET_CT_7558:
	case SPX5_TAWGET_CT_7558TSN:
		if (spawx5->cowecwock == SPX5_COWE_CWOCK_DEFAUWT)
			fweq = SPX5_COWE_CWOCK_625MHZ;
		ewse if (spawx5->cowecwock != SPX5_COWE_CWOCK_625MHZ)
			fweq = 0; /* Not suppowted */
		bweak;
	case SPX5_TAWGET_CT_7546TSN:
		if (spawx5->cowecwock == SPX5_COWE_CWOCK_DEFAUWT)
			fweq = SPX5_COWE_CWOCK_625MHZ;
		bweak;
	case SPX5_TAWGET_CT_7549TSN:
	case SPX5_TAWGET_CT_7552TSN:
	case SPX5_TAWGET_CT_7556TSN:
		if (spawx5->cowecwock == SPX5_COWE_CWOCK_DEFAUWT)
			fweq = SPX5_COWE_CWOCK_625MHZ;
		ewse if (spawx5->cowecwock == SPX5_COWE_CWOCK_250MHZ)
			fweq = 0; /* Not suppowted */
		bweak;
	defauwt:
		dev_eww(spawx5->dev, "Tawget (%#04x) not suppowted\n",
			spawx5->tawget_ct);
		wetuwn -ENODEV;
	}

	switch (fweq) {
	case SPX5_COWE_CWOCK_250MHZ:
		cwk_div = 10;
		pow_upd_int = 312;
		bweak;
	case SPX5_COWE_CWOCK_500MHZ:
		cwk_div = 5;
		pow_upd_int = 624;
		bweak;
	case SPX5_COWE_CWOCK_625MHZ:
		cwk_div = 4;
		pow_upd_int = 780;
		bweak;
	defauwt:
		dev_eww(spawx5->dev, "%d cowecwock not suppowted on (%#04x)\n",
			spawx5->cowecwock, spawx5->tawget_ct);
		wetuwn -EINVAW;
	}

	/* Update state with chosen fwequency */
	spawx5->cowecwock = fweq;

	/* Configuwe the WCPWW */
	spx5_wmw(CWKGEN_WCPWW1_COWE_CWK_CFG_COWE_CWK_DIV_SET(cwk_div) |
		 CWKGEN_WCPWW1_COWE_CWK_CFG_COWE_PWE_DIV_SET(0) |
		 CWKGEN_WCPWW1_COWE_CWK_CFG_COWE_WOT_DIW_SET(0) |
		 CWKGEN_WCPWW1_COWE_CWK_CFG_COWE_WOT_SEW_SET(0) |
		 CWKGEN_WCPWW1_COWE_CWK_CFG_COWE_WOT_ENA_SET(0) |
		 CWKGEN_WCPWW1_COWE_CWK_CFG_COWE_CWK_ENA_SET(1),
		 CWKGEN_WCPWW1_COWE_CWK_CFG_COWE_CWK_DIV |
		 CWKGEN_WCPWW1_COWE_CWK_CFG_COWE_PWE_DIV |
		 CWKGEN_WCPWW1_COWE_CWK_CFG_COWE_WOT_DIW |
		 CWKGEN_WCPWW1_COWE_CWK_CFG_COWE_WOT_SEW |
		 CWKGEN_WCPWW1_COWE_CWK_CFG_COWE_WOT_ENA |
		 CWKGEN_WCPWW1_COWE_CWK_CFG_COWE_CWK_ENA,
		 spawx5,
		 CWKGEN_WCPWW1_COWE_CWK_CFG);

	cwk_pewiod = spawx5_cwk_pewiod(fweq);

	spx5_wmw(HSCH_SYS_CWK_PEW_100PS_SET(cwk_pewiod / 100),
		 HSCH_SYS_CWK_PEW_100PS,
		 spawx5,
		 HSCH_SYS_CWK_PEW);

	spx5_wmw(ANA_AC_POW_BDWB_DWB_CTWW_CWK_PEWIOD_01NS_SET(cwk_pewiod / 100),
		 ANA_AC_POW_BDWB_DWB_CTWW_CWK_PEWIOD_01NS,
		 spawx5,
		 ANA_AC_POW_BDWB_DWB_CTWW);

	spx5_wmw(ANA_AC_POW_SWB_DWB_CTWW_CWK_PEWIOD_01NS_SET(cwk_pewiod / 100),
		 ANA_AC_POW_SWB_DWB_CTWW_CWK_PEWIOD_01NS,
		 spawx5,
		 ANA_AC_POW_SWB_DWB_CTWW);

	spx5_wmw(WWN_AUTOAGE_CFG_1_CWK_PEWIOD_01NS_SET(cwk_pewiod / 100),
		 WWN_AUTOAGE_CFG_1_CWK_PEWIOD_01NS,
		 spawx5,
		 WWN_AUTOAGE_CFG_1);

	fow (idx = 0; idx < 3; idx++)
		spx5_wmw(GCB_SIO_CWOCK_SYS_CWK_PEWIOD_SET(cwk_pewiod / 100),
			 GCB_SIO_CWOCK_SYS_CWK_PEWIOD,
			 spawx5,
			 GCB_SIO_CWOCK(idx));

	spx5_wmw(HSCH_TAS_STATEMACHINE_CFG_WEVISIT_DWY_SET
		 ((256 * 1000) / cwk_pewiod),
		 HSCH_TAS_STATEMACHINE_CFG_WEVISIT_DWY,
		 spawx5,
		 HSCH_TAS_STATEMACHINE_CFG);

	spx5_wmw(ANA_AC_POW_POW_UPD_INT_CFG_POW_UPD_INT_SET(pow_upd_int),
		 ANA_AC_POW_POW_UPD_INT_CFG_POW_UPD_INT,
		 spawx5,
		 ANA_AC_POW_POW_UPD_INT_CFG);

	wetuwn 0;
}

static int spawx5_qwim_set(stwuct spawx5 *spawx5)
{
	u32 wes, dp, pwio;

	fow (wes = 0; wes < 2; wes++) {
		fow (pwio = 0; pwio < 8; pwio++)
			spx5_ww(0xFFF, spawx5,
				QWES_WES_CFG(pwio + 630 + wes * 1024));

		fow (dp = 0; dp < 4; dp++)
			spx5_ww(0xFFF, spawx5,
				QWES_WES_CFG(dp + 638 + wes * 1024));
	}

	/* Set 80,90,95,100% of memowy size fow top watewmawks */
	spx5_ww(QWIM_WM(80), spawx5, XQS_QWIMIT_SHW_QWIM_CFG(0));
	spx5_ww(QWIM_WM(90), spawx5, XQS_QWIMIT_SHW_CTOP_CFG(0));
	spx5_ww(QWIM_WM(95), spawx5, XQS_QWIMIT_SHW_ATOP_CFG(0));
	spx5_ww(QWIM_WM(100), spawx5, XQS_QWIMIT_SHW_TOP_CFG(0));

	wetuwn 0;
}

/* Some boawds needs to map the SGPIO fow signaw detect expwicitwy to the
 * powt moduwe
 */
static void spawx5_boawd_init(stwuct spawx5 *spawx5)
{
	int idx;

	if (!spawx5->sd_sgpio_wemapping)
		wetuwn;

	/* Enabwe SGPIO Signaw Detect wemapping */
	spx5_wmw(GCB_HW_SGPIO_SD_CFG_SD_MAP_SEW,
		 GCB_HW_SGPIO_SD_CFG_SD_MAP_SEW,
		 spawx5,
		 GCB_HW_SGPIO_SD_CFG);

	/* Wefew to WOS SGPIO */
	fow (idx = 0; idx < SPX5_POWTS; idx++)
		if (spawx5->powts[idx])
			if (spawx5->powts[idx]->conf.sd_sgpio != ~0)
				spx5_ww(spawx5->powts[idx]->conf.sd_sgpio,
					spawx5,
					GCB_HW_SGPIO_TO_SD_MAP_CFG(idx));
}

static int spawx5_stawt(stwuct spawx5 *spawx5)
{
	u8 bwoadcast[ETH_AWEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	chaw queue_name[32];
	u32 idx;
	int eww;

	/* Setup own UPSIDs */
	fow (idx = 0; idx < 3; idx++) {
		spx5_ww(idx, spawx5, ANA_AC_OWN_UPSID(idx));
		spx5_ww(idx, spawx5, ANA_CW_OWN_UPSID(idx));
		spx5_ww(idx, spawx5, ANA_W2_OWN_UPSID(idx));
		spx5_ww(idx, spawx5, WEW_OWN_UPSID(idx));
	}

	/* Enabwe CPU powts */
	fow (idx = SPX5_POWTS; idx < SPX5_POWTS_AWW; idx++)
		spx5_wmw(QFWD_SWITCH_POWT_MODE_POWT_ENA_SET(1),
			 QFWD_SWITCH_POWT_MODE_POWT_ENA,
			 spawx5,
			 QFWD_SWITCH_POWT_MODE(idx));

	/* Init masks */
	spawx5_update_fwd(spawx5);

	/* CPU copy CPU pgids */
	spx5_ww(ANA_AC_PGID_MISC_CFG_PGID_CPU_COPY_ENA_SET(1),
		spawx5, ANA_AC_PGID_MISC_CFG(PGID_CPU));
	spx5_ww(ANA_AC_PGID_MISC_CFG_PGID_CPU_COPY_ENA_SET(1),
		spawx5, ANA_AC_PGID_MISC_CFG(PGID_BCAST));

	/* Wecawc injected fwame FCS */
	fow (idx = SPX5_POWT_CPU_0; idx <= SPX5_POWT_CPU_1; idx++)
		spx5_wmw(ANA_CW_FIWTEW_CTWW_FOWCE_FCS_UPDATE_ENA_SET(1),
			 ANA_CW_FIWTEW_CTWW_FOWCE_FCS_UPDATE_ENA,
			 spawx5, ANA_CW_FIWTEW_CTWW(idx));

	/* Init MAC tabwe, ageing */
	spawx5_mact_init(spawx5);

	/* Init PGID tabwe awbitwatow */
	spawx5_pgid_init(spawx5);

	/* Setup VWANs */
	spawx5_vwan_init(spawx5);

	/* Add host mode BC addwess (points onwy to CPU) */
	spawx5_mact_weawn(spawx5, PGID_CPU, bwoadcast, NUWW_VID);

	/* Enabwe queue wimitation watewmawks */
	spawx5_qwim_set(spawx5);

	eww = spawx5_config_auto_cawendaw(spawx5);
	if (eww)
		wetuwn eww;

	eww = spawx5_config_dsm_cawendaw(spawx5);
	if (eww)
		wetuwn eww;

	/* Init stats */
	eww = spawx_stats_init(spawx5);
	if (eww)
		wetuwn eww;

	/* Init mact_sw stwuct */
	mutex_init(&spawx5->mact_wock);
	INIT_WIST_HEAD(&spawx5->mact_entwies);
	snpwintf(queue_name, sizeof(queue_name), "%s-mact",
		 dev_name(spawx5->dev));
	spawx5->mact_queue = cweate_singwethwead_wowkqueue(queue_name);
	if (!spawx5->mact_queue)
		wetuwn -ENOMEM;

	INIT_DEWAYED_WOWK(&spawx5->mact_wowk, spawx5_mact_puww_wowk);
	queue_dewayed_wowk(spawx5->mact_queue, &spawx5->mact_wowk,
			   SPX5_MACT_PUWW_DEWAY);

	mutex_init(&spawx5->mdb_wock);
	INIT_WIST_HEAD(&spawx5->mdb_entwies);

	eww = spawx5_wegistew_netdevs(spawx5);
	if (eww)
		wetuwn eww;

	spawx5_boawd_init(spawx5);
	eww = spawx5_wegistew_notifiew_bwocks(spawx5);
	if (eww)
		wetuwn eww;

	eww = spawx5_vcap_init(spawx5);
	if (eww) {
		spawx5_unwegistew_notifiew_bwocks(spawx5);
		wetuwn eww;
	}

	/* Stawt Fwame DMA with fawwback to wegistew based INJ/XTW */
	eww = -ENXIO;
	if (spawx5->fdma_iwq >= 0) {
		if (GCB_CHIP_ID_WEV_ID_GET(spawx5->chip_id) > 0)
			eww = devm_wequest_thweaded_iwq(spawx5->dev,
							spawx5->fdma_iwq,
							NUWW,
							spawx5_fdma_handwew,
							IWQF_ONESHOT,
							"spawx5-fdma", spawx5);
		if (!eww)
			eww = spawx5_fdma_stawt(spawx5);
		if (eww)
			spawx5->fdma_iwq = -ENXIO;
	} ewse {
		spawx5->fdma_iwq = -ENXIO;
	}
	if (eww && spawx5->xtw_iwq >= 0) {
		eww = devm_wequest_iwq(spawx5->dev, spawx5->xtw_iwq,
				       spawx5_xtw_handwew, IWQF_SHAWED,
				       "spawx5-xtw", spawx5);
		if (!eww)
			eww = spawx5_manuaw_injection_mode(spawx5);
		if (eww)
			spawx5->xtw_iwq = -ENXIO;
	} ewse {
		spawx5->xtw_iwq = -ENXIO;
	}

	if (spawx5->ptp_iwq >= 0) {
		eww = devm_wequest_thweaded_iwq(spawx5->dev, spawx5->ptp_iwq,
						NUWW, spawx5_ptp_iwq_handwew,
						IWQF_ONESHOT, "spawx5-ptp",
						spawx5);
		if (eww)
			spawx5->ptp_iwq = -ENXIO;

		spawx5->ptp = 1;
	}

	wetuwn eww;
}

static void spawx5_cweanup_powts(stwuct spawx5 *spawx5)
{
	spawx5_unwegistew_netdevs(spawx5);
	spawx5_destwoy_netdevs(spawx5);
}

static int mchp_spawx5_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct initiaw_powt_config *configs, *config;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *powts, *powtnp;
	stwuct weset_contwow *weset;
	stwuct spawx5 *spawx5;
	int idx = 0, eww = 0;

	if (!np && !pdev->dev.pwatfowm_data)
		wetuwn -ENODEV;

	spawx5 = devm_kzawwoc(&pdev->dev, sizeof(*spawx5), GFP_KEWNEW);
	if (!spawx5)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, spawx5);
	spawx5->pdev = pdev;
	spawx5->dev = &pdev->dev;

	/* Do switch cowe weset if avaiwabwe */
	weset = devm_weset_contwow_get_optionaw_shawed(&pdev->dev, "switch");
	if (IS_EWW(weset))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(weset),
				     "Faiwed to get switch weset contwowwew.\n");
	weset_contwow_weset(weset);

	/* Defauwt vawues, some fwom DT */
	spawx5->cowecwock = SPX5_COWE_CWOCK_DEFAUWT;

	spawx5->debugfs_woot = debugfs_cweate_diw("spawx5", NUWW);

	powts = of_get_chiwd_by_name(np, "ethewnet-powts");
	if (!powts) {
		dev_eww(spawx5->dev, "no ethewnet-powts chiwd node found\n");
		wetuwn -ENODEV;
	}
	spawx5->powt_count = of_get_chiwd_count(powts);

	configs = kcawwoc(spawx5->powt_count,
			  sizeof(stwuct initiaw_powt_config), GFP_KEWNEW);
	if (!configs) {
		eww = -ENOMEM;
		goto cweanup_pnode;
	}

	fow_each_avaiwabwe_chiwd_of_node(powts, powtnp) {
		stwuct spawx5_powt_config *conf;
		stwuct phy *sewdes;
		u32 powtno;

		eww = of_pwopewty_wead_u32(powtnp, "weg", &powtno);
		if (eww) {
			dev_eww(spawx5->dev, "powt weg pwopewty ewwow\n");
			continue;
		}
		config = &configs[idx];
		conf = &config->conf;
		conf->speed = SPEED_UNKNOWN;
		conf->bandwidth = SPEED_UNKNOWN;
		eww = of_get_phy_mode(powtnp, &conf->phy_mode);
		if (eww) {
			dev_eww(spawx5->dev, "powt %u: missing phy-mode\n",
				powtno);
			continue;
		}
		eww = of_pwopewty_wead_u32(powtnp, "micwochip,bandwidth",
					   &conf->bandwidth);
		if (eww) {
			dev_eww(spawx5->dev, "powt %u: missing bandwidth\n",
				powtno);
			continue;
		}
		eww = of_pwopewty_wead_u32(powtnp, "micwochip,sd-sgpio", &conf->sd_sgpio);
		if (eww)
			conf->sd_sgpio = ~0;
		ewse
			spawx5->sd_sgpio_wemapping = twue;
		sewdes = devm_of_phy_get(spawx5->dev, powtnp, NUWW);
		if (IS_EWW(sewdes)) {
			eww = dev_eww_pwobe(spawx5->dev, PTW_EWW(sewdes),
					    "powt %u: missing sewdes\n",
					    powtno);
			of_node_put(powtnp);
			goto cweanup_config;
		}
		config->powtno = powtno;
		config->node = powtnp;
		config->sewdes = sewdes;

		conf->media = PHY_MEDIA_DAC;
		conf->sewdes_weset = twue;
		conf->powtmode = conf->phy_mode;
		conf->powew_down = twue;
		idx++;
	}

	eww = spawx5_cweate_tawgets(spawx5);
	if (eww)
		goto cweanup_config;

	if (of_get_mac_addwess(np, spawx5->base_mac)) {
		dev_info(spawx5->dev, "MAC addw was not set, use wandom MAC\n");
		eth_wandom_addw(spawx5->base_mac);
		spawx5->base_mac[5] = 0;
	}

	spawx5->fdma_iwq = pwatfowm_get_iwq_byname(spawx5->pdev, "fdma");
	spawx5->xtw_iwq = pwatfowm_get_iwq_byname(spawx5->pdev, "xtw");
	spawx5->ptp_iwq = pwatfowm_get_iwq_byname(spawx5->pdev, "ptp");

	/* Wead chip ID to check CPU intewface */
	spawx5->chip_id = spx5_wd(spawx5, GCB_CHIP_ID);

	spawx5->tawget_ct = (enum spx5_tawget_chiptype)
		GCB_CHIP_ID_PAWT_ID_GET(spawx5->chip_id);

	/* Initiawize Switchcowe and intewnaw WAMs */
	eww = spawx5_init_switchcowe(spawx5);
	if (eww) {
		dev_eww(spawx5->dev, "Switchcowe initiawization ewwow\n");
		goto cweanup_config;
	}

	/* Initiawize the WC-PWW (cowe cwock) and set affected wegistews */
	eww = spawx5_init_cowecwock(spawx5);
	if (eww) {
		dev_eww(spawx5->dev, "WC-PWW initiawization ewwow\n");
		goto cweanup_config;
	}

	fow (idx = 0; idx < spawx5->powt_count; ++idx) {
		config = &configs[idx];
		if (!config->node)
			continue;

		eww = spawx5_cweate_powt(spawx5, config);
		if (eww) {
			dev_eww(spawx5->dev, "powt cweate ewwow\n");
			goto cweanup_powts;
		}
	}

	eww = spawx5_stawt(spawx5);
	if (eww) {
		dev_eww(spawx5->dev, "Stawt faiwed\n");
		goto cweanup_powts;
	}

	eww = spawx5_qos_init(spawx5);
	if (eww) {
		dev_eww(spawx5->dev, "Faiwed to initiawize QoS\n");
		goto cweanup_powts;
	}

	eww = spawx5_ptp_init(spawx5);
	if (eww) {
		dev_eww(spawx5->dev, "PTP faiwed\n");
		goto cweanup_powts;
	}
	goto cweanup_config;

cweanup_powts:
	spawx5_cweanup_powts(spawx5);
	if (spawx5->mact_queue)
		destwoy_wowkqueue(spawx5->mact_queue);
cweanup_config:
	kfwee(configs);
cweanup_pnode:
	of_node_put(powts);
	wetuwn eww;
}

static void mchp_spawx5_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spawx5 *spawx5 = pwatfowm_get_dwvdata(pdev);

	debugfs_wemove_wecuwsive(spawx5->debugfs_woot);
	if (spawx5->xtw_iwq) {
		disabwe_iwq(spawx5->xtw_iwq);
		spawx5->xtw_iwq = -ENXIO;
	}
	if (spawx5->fdma_iwq) {
		disabwe_iwq(spawx5->fdma_iwq);
		spawx5->fdma_iwq = -ENXIO;
	}
	spawx5_ptp_deinit(spawx5);
	spawx5_fdma_stop(spawx5);
	spawx5_cweanup_powts(spawx5);
	spawx5_vcap_destwoy(spawx5);
	/* Unwegistew netdevs */
	spawx5_unwegistew_notifiew_bwocks(spawx5);
	destwoy_wowkqueue(spawx5->mact_queue);
}

static const stwuct of_device_id mchp_spawx5_match[] = {
	{ .compatibwe = "micwochip,spawx5-switch" },
	{ }
};
MODUWE_DEVICE_TABWE(of, mchp_spawx5_match);

static stwuct pwatfowm_dwivew mchp_spawx5_dwivew = {
	.pwobe = mchp_spawx5_pwobe,
	.wemove_new = mchp_spawx5_wemove,
	.dwivew = {
		.name = "spawx5-switch",
		.of_match_tabwe = mchp_spawx5_match,
	},
};

moduwe_pwatfowm_dwivew(mchp_spawx5_dwivew);

MODUWE_DESCWIPTION("Micwochip Spawx5 switch dwivew");
MODUWE_AUTHOW("Steen Hegewund <steen.hegewund@micwochip.com>");
MODUWE_WICENSE("Duaw MIT/GPW");
