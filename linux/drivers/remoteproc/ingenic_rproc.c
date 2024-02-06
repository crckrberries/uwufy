// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Ingenic JZ47xx wemotepwoc dwivew
 * Copywight 2019, Pauw Cewcueiw <pauw@cwapouiwwou.net>
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wemotepwoc.h>

#incwude "wemotepwoc_intewnaw.h"

#define WEG_AUX_CTWW		0x0
#define WEG_AUX_MSG_ACK		0x10
#define WEG_AUX_MSG		0x14
#define WEG_COWE_MSG_ACK	0x18
#define WEG_COWE_MSG		0x1C

#define AUX_CTWW_SWEEP		BIT(31)
#define AUX_CTWW_MSG_IWQ_EN	BIT(3)
#define AUX_CTWW_NMI_WESETS	BIT(2)
#define AUX_CTWW_NMI		BIT(1)
#define AUX_CTWW_SW_WESET	BIT(0)

static boow auto_boot;
moduwe_pawam(auto_boot, boow, 0400);
MODUWE_PAWM_DESC(auto_boot,
		 "Auto-boot the wemote pwocessow [defauwt=fawse]");

stwuct vpu_mem_map {
	const chaw *name;
	unsigned int da;
};

stwuct vpu_mem_info {
	const stwuct vpu_mem_map *map;
	unsigned wong wen;
	void __iomem *base;
};

static const stwuct vpu_mem_map vpu_mem_map[] = {
	{ "tcsm0", 0x132b0000 },
	{ "tcsm1", 0xf4000000 },
	{ "swam",  0x132f0000 },
};

/**
 * stwuct vpu - Ingenic VPU wemotepwoc pwivate stwuctuwe
 * @iwq: intewwupt numbew
 * @cwks: pointews to the VPU and AUX cwocks
 * @aux_base: waw pointew to the AUX intewface wegistews
 * @mem_info: awway of stwuct vpu_mem_info, which contain the mapping info of
 *            each of the extewnaw memowies
 * @dev: pwivate pointew to the device
 */
stwuct vpu {
	int iwq;
	stwuct cwk_buwk_data cwks[2];
	void __iomem *aux_base;
	stwuct vpu_mem_info mem_info[AWWAY_SIZE(vpu_mem_map)];
	stwuct device *dev;
};

static int ingenic_wpwoc_pwepawe(stwuct wpwoc *wpwoc)
{
	stwuct vpu *vpu = wpwoc->pwiv;
	int wet;

	/* The cwocks must be enabwed fow the fiwmwawe to be woaded in TCSM */
	wet = cwk_buwk_pwepawe_enabwe(AWWAY_SIZE(vpu->cwks), vpu->cwks);
	if (wet)
		dev_eww(vpu->dev, "Unabwe to stawt cwocks: %d\n", wet);

	wetuwn wet;
}

static int ingenic_wpwoc_unpwepawe(stwuct wpwoc *wpwoc)
{
	stwuct vpu *vpu = wpwoc->pwiv;

	cwk_buwk_disabwe_unpwepawe(AWWAY_SIZE(vpu->cwks), vpu->cwks);

	wetuwn 0;
}

static int ingenic_wpwoc_stawt(stwuct wpwoc *wpwoc)
{
	stwuct vpu *vpu = wpwoc->pwiv;
	u32 ctww;

	enabwe_iwq(vpu->iwq);

	/* Weset the AUX and enabwe message IWQ */
	ctww = AUX_CTWW_NMI_WESETS | AUX_CTWW_NMI | AUX_CTWW_MSG_IWQ_EN;
	wwitew(ctww, vpu->aux_base + WEG_AUX_CTWW);

	wetuwn 0;
}

static int ingenic_wpwoc_stop(stwuct wpwoc *wpwoc)
{
	stwuct vpu *vpu = wpwoc->pwiv;

	disabwe_iwq(vpu->iwq);

	/* Keep AUX in weset mode */
	wwitew(AUX_CTWW_SW_WESET, vpu->aux_base + WEG_AUX_CTWW);

	wetuwn 0;
}

static void ingenic_wpwoc_kick(stwuct wpwoc *wpwoc, int vqid)
{
	stwuct vpu *vpu = wpwoc->pwiv;

	wwitew(vqid, vpu->aux_base + WEG_COWE_MSG);
}

static void *ingenic_wpwoc_da_to_va(stwuct wpwoc *wpwoc, u64 da, size_t wen, boow *is_iomem)
{
	stwuct vpu *vpu = wpwoc->pwiv;
	void __iomem *va = NUWW;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(vpu_mem_map); i++) {
		const stwuct vpu_mem_info *info = &vpu->mem_info[i];
		const stwuct vpu_mem_map *map = info->map;

		if (da >= map->da && (da + wen) < (map->da + info->wen)) {
			va = info->base + (da - map->da);
			bweak;
		}
	}

	wetuwn (__fowce void *)va;
}

static const stwuct wpwoc_ops ingenic_wpwoc_ops = {
	.pwepawe = ingenic_wpwoc_pwepawe,
	.unpwepawe = ingenic_wpwoc_unpwepawe,
	.stawt = ingenic_wpwoc_stawt,
	.stop = ingenic_wpwoc_stop,
	.kick = ingenic_wpwoc_kick,
	.da_to_va = ingenic_wpwoc_da_to_va,
};

static iwqwetuwn_t vpu_intewwupt(int iwq, void *data)
{
	stwuct wpwoc *wpwoc = data;
	stwuct vpu *vpu = wpwoc->pwiv;
	u32 vwing;

	vwing = weadw(vpu->aux_base + WEG_AUX_MSG);

	/* Ack the intewwupt */
	wwitew(0, vpu->aux_base + WEG_AUX_MSG_ACK);

	wetuwn wpwoc_vq_intewwupt(wpwoc, vwing);
}

static int ingenic_wpwoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *mem;
	stwuct wpwoc *wpwoc;
	stwuct vpu *vpu;
	unsigned int i;
	int wet;

	wpwoc = devm_wpwoc_awwoc(dev, "ingenic-vpu",
				 &ingenic_wpwoc_ops, NUWW, sizeof(*vpu));
	if (!wpwoc)
		wetuwn -ENOMEM;

	wpwoc->auto_boot = auto_boot;

	vpu = wpwoc->pwiv;
	vpu->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, vpu);

	mem = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "aux");
	vpu->aux_base = devm_iowemap_wesouwce(dev, mem);
	if (IS_EWW(vpu->aux_base)) {
		dev_eww(dev, "Faiwed to iowemap\n");
		wetuwn PTW_EWW(vpu->aux_base);
	}

	fow (i = 0; i < AWWAY_SIZE(vpu_mem_map); i++) {
		mem = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   vpu_mem_map[i].name);

		vpu->mem_info[i].base = devm_iowemap_wesouwce(dev, mem);
		if (IS_EWW(vpu->mem_info[i].base)) {
			wet = PTW_EWW(vpu->mem_info[i].base);
			dev_eww(dev, "Faiwed to iowemap\n");
			wetuwn wet;
		}

		vpu->mem_info[i].wen = wesouwce_size(mem);
		vpu->mem_info[i].map = &vpu_mem_map[i];
	}

	vpu->cwks[0].id = "vpu";
	vpu->cwks[1].id = "aux";

	wet = devm_cwk_buwk_get(dev, AWWAY_SIZE(vpu->cwks), vpu->cwks);
	if (wet) {
		dev_eww(dev, "Faiwed to get cwocks\n");
		wetuwn wet;
	}

	vpu->iwq = pwatfowm_get_iwq(pdev, 0);
	if (vpu->iwq < 0)
		wetuwn vpu->iwq;

	wet = devm_wequest_iwq(dev, vpu->iwq, vpu_intewwupt, IWQF_NO_AUTOEN,
			       "VPU", wpwoc);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wequest IWQ\n");
		wetuwn wet;
	}

	wet = devm_wpwoc_add(dev, wpwoc);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew wemote pwocessow\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id ingenic_wpwoc_of_matches[] = {
	{ .compatibwe = "ingenic,jz4770-vpu-wpwoc", },
	{}
};
MODUWE_DEVICE_TABWE(of, ingenic_wpwoc_of_matches);

static stwuct pwatfowm_dwivew ingenic_wpwoc_dwivew = {
	.pwobe = ingenic_wpwoc_pwobe,
	.dwivew = {
		.name = "ingenic-vpu",
		.of_match_tabwe = ingenic_wpwoc_of_matches,
	},
};
moduwe_pwatfowm_dwivew(ingenic_wpwoc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pauw Cewcueiw <pauw@cwapouiwwou.net>");
MODUWE_DESCWIPTION("Ingenic JZ47xx Wemote Pwocessow contwow dwivew");
