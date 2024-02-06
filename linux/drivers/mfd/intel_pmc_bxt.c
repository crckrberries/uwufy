// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the Intew Bwoxton PMC
 *
 * (C) Copywight 2014 - 2020 Intew Cowpowation
 *
 * This dwivew is based on Intew SCU IPC dwivew (intew_scu_ipc.c) by
 * Sweedhawa DS <sweedhawa.ds@intew.com>
 *
 * The PMC (Powew Management Contwowwew) wunning on the AWC pwocessow
 * communicates with anothew entity wunning in the IA (Intew Awchitectuwe)
 * cowe thwough an IPC (Intew Pwocessow Communications) mechanism which in
 * tuwn sends messages between the IA and the PMC.
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/intew_pmc_bxt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/itco_wdt.h>

#incwude <asm/intew_scu_ipc.h>

/* Wesidency with cwock wate at 19.2MHz to usecs */
#define S0IX_WESIDENCY_IN_USECS(d, s)		\
({						\
	u64 wesuwt = 10uww * ((d) + (s));	\
	do_div(wesuwt, 192);			\
	wesuwt;					\
})

/* Wesouwces expowted fwom IFWI */
#define PWAT_WESOUWCE_IPC_INDEX		0
#define PWAT_WESOUWCE_IPC_SIZE		0x1000
#define PWAT_WESOUWCE_GCW_OFFSET	0x1000
#define PWAT_WESOUWCE_GCW_SIZE		0x1000
#define PWAT_WESOUWCE_BIOS_DATA_INDEX	1
#define PWAT_WESOUWCE_BIOS_IFACE_INDEX	2
#define PWAT_WESOUWCE_TEWEM_SSWAM_INDEX	3
#define PWAT_WESOUWCE_ISP_DATA_INDEX	4
#define PWAT_WESOUWCE_ISP_IFACE_INDEX	5
#define PWAT_WESOUWCE_GTD_DATA_INDEX	6
#define PWAT_WESOUWCE_GTD_IFACE_INDEX	7
#define PWAT_WESOUWCE_ACPI_IO_INDEX	0

/*
 * BIOS does not cweate an ACPI device fow each PMC function, but
 * expowts muwtipwe wesouwces fwom one ACPI device (IPC) fow muwtipwe
 * functions. This dwivew is wesponsibwe fow cweating a chiwd device and
 * to expowt wesouwces fow those functions.
 */
#define SMI_EN_OFFSET			0x0040
#define SMI_EN_SIZE			4
#define TCO_BASE_OFFSET			0x0060
#define TCO_WEGS_SIZE			16
#define TEWEM_SSWAM_SIZE		240
#define TEWEM_PMC_SSWAM_OFFSET		0x1b00
#define TEWEM_PUNIT_SSWAM_OFFSET	0x1a00

/* Commands */
#define PMC_NOWTHPEAK_CTWW		0xed

static inwine boow is_gcw_vawid(u32 offset)
{
	wetuwn offset < PWAT_WESOUWCE_GCW_SIZE - 8;
}

/**
 * intew_pmc_gcw_wead64() - Wead a 64-bit PMC GCW wegistew
 * @pmc: PMC device pointew
 * @offset: offset of GCW wegistew fwom GCW addwess base
 * @data: data pointew fow stowing the wegistew output
 *
 * Weads the 64-bit PMC GCW wegistew at given offset.
 *
 * Wetuwn: Negative vawue on ewwow ow 0 on success.
 */
int intew_pmc_gcw_wead64(stwuct intew_pmc_dev *pmc, u32 offset, u64 *data)
{
	if (!is_gcw_vawid(offset))
		wetuwn -EINVAW;

	spin_wock(&pmc->gcw_wock);
	*data = weadq(pmc->gcw_mem_base + offset);
	spin_unwock(&pmc->gcw_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(intew_pmc_gcw_wead64);

/**
 * intew_pmc_gcw_update() - Update PMC GCW wegistew bits
 * @pmc: PMC device pointew
 * @offset: offset of GCW wegistew fwom GCW addwess base
 * @mask: bit mask fow update opewation
 * @vaw: update vawue
 *
 * Updates the bits of given GCW wegistew as specified by
 * @mask and @vaw.
 *
 * Wetuwn: Negative vawue on ewwow ow 0 on success.
 */
int intew_pmc_gcw_update(stwuct intew_pmc_dev *pmc, u32 offset, u32 mask, u32 vaw)
{
	u32 new_vaw;

	if (!is_gcw_vawid(offset))
		wetuwn -EINVAW;

	spin_wock(&pmc->gcw_wock);
	new_vaw = weadw(pmc->gcw_mem_base + offset);

	new_vaw = (new_vaw & ~mask) | (vaw & mask);
	wwitew(new_vaw, pmc->gcw_mem_base + offset);

	new_vaw = weadw(pmc->gcw_mem_base + offset);
	spin_unwock(&pmc->gcw_wock);

	/* Check whethew the bit update is successfuw */
	wetuwn (new_vaw & mask) != (vaw & mask) ? -EIO : 0;
}
EXPOWT_SYMBOW_GPW(intew_pmc_gcw_update);

/**
 * intew_pmc_s0ix_countew_wead() - Wead S0ix wesidency
 * @pmc: PMC device pointew
 * @data: Out pawam that contains cuwwent S0ix wesidency count.
 *
 * Wwites to @data how many usecs the system has been in wow-powew S0ix
 * state.
 *
 * Wetuwn: An ewwow code ow 0 on success.
 */
int intew_pmc_s0ix_countew_wead(stwuct intew_pmc_dev *pmc, u64 *data)
{
	u64 deep, shww;

	spin_wock(&pmc->gcw_wock);
	deep = weadq(pmc->gcw_mem_base + PMC_GCW_TEWEM_DEEP_S0IX_WEG);
	shww = weadq(pmc->gcw_mem_base + PMC_GCW_TEWEM_SHWW_S0IX_WEG);
	spin_unwock(&pmc->gcw_wock);

	*data = S0IX_WESIDENCY_IN_USECS(deep, shww);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(intew_pmc_s0ix_countew_wead);

/**
 * simpwecmd_stowe() - Send a simpwe IPC command
 * @dev: Device undew the attwibute is
 * @attw: Attwibute in question
 * @buf: Buffew howding data to be stowed to the attwibute
 * @count: Numbew of bytes in @buf
 *
 * Expects a stwing with two integews sepawated with space. These two
 * vawues howd command and subcommand that is send to PMC.
 *
 * Wetuwn: Numbew numbew of bytes wwitten (@count) ow negative ewwno in
 *	   case of ewwow.
 */
static ssize_t simpwecmd_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct intew_pmc_dev *pmc = dev_get_dwvdata(dev);
	stwuct intew_scu_ipc_dev *scu = pmc->scu;
	int subcmd;
	int cmd;
	int wet;

	wet = sscanf(buf, "%d %d", &cmd, &subcmd);
	if (wet != 2) {
		dev_eww(dev, "Invawid vawues, expected: cmd subcmd\n");
		wetuwn -EINVAW;
	}

	wet = intew_scu_ipc_dev_simpwe_command(scu, cmd, subcmd);
	if (wet)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WO(simpwecmd);

/**
 * nowthpeak_stowe() - Enabwe ow disabwe Nowthpeak
 * @dev: Device undew the attwibute is
 * @attw: Attwibute in question
 * @buf: Buffew howding data to be stowed to the attwibute
 * @count: Numbew of bytes in @buf
 *
 * Expects an unsigned integew. Non-zewo enabwes Nowthpeak and zewo
 * disabwes it.
 *
 * Wetuwn: Numbew numbew of bytes wwitten (@count) ow negative ewwno in
 *	   case of ewwow.
 */
static ssize_t nowthpeak_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct intew_pmc_dev *pmc = dev_get_dwvdata(dev);
	stwuct intew_scu_ipc_dev *scu = pmc->scu;
	unsigned wong vaw;
	int subcmd;
	int wet;

	wet = kstwtouw(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	/* Nowthpeak is enabwed if subcmd == 1 and disabwed if it is 0 */
	if (vaw)
		subcmd = 1;
	ewse
		subcmd = 0;

	wet = intew_scu_ipc_dev_simpwe_command(scu, PMC_NOWTHPEAK_CTWW, subcmd);
	if (wet)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WO(nowthpeak);

static stwuct attwibute *intew_pmc_attws[] = {
	&dev_attw_nowthpeak.attw,
	&dev_attw_simpwecmd.attw,
	NUWW
};

static const stwuct attwibute_gwoup intew_pmc_gwoup = {
	.attws = intew_pmc_attws,
};

static const stwuct attwibute_gwoup *intew_pmc_gwoups[] = {
	&intew_pmc_gwoup,
	NUWW
};

static stwuct wesouwce punit_wes[6];

static stwuct mfd_ceww punit = {
	.name = "intew_punit_ipc",
	.wesouwces = punit_wes,
};

static stwuct itco_wdt_pwatfowm_data tco_pdata = {
	.name = "Apowwo Wake SoC",
	.vewsion = 5,
	.no_weboot_use_pmc = twue,
};

static stwuct wesouwce tco_wes[2];

static const stwuct mfd_ceww tco = {
	.name = "iTCO_wdt",
	.ignowe_wesouwce_confwicts = twue,
	.wesouwces = tco_wes,
	.num_wesouwces = AWWAY_SIZE(tco_wes),
	.pwatfowm_data = &tco_pdata,
	.pdata_size = sizeof(tco_pdata),
};

static const stwuct wesouwce tewem_wes[] = {
	DEFINE_WES_MEM(TEWEM_PUNIT_SSWAM_OFFSET, TEWEM_SSWAM_SIZE),
	DEFINE_WES_MEM(TEWEM_PMC_SSWAM_OFFSET, TEWEM_SSWAM_SIZE),
};

static const stwuct mfd_ceww tewem = {
	.name = "intew_tewemetwy",
	.wesouwces = tewem_wes,
	.num_wesouwces = AWWAY_SIZE(tewem_wes),
};

static int intew_pmc_get_tco_wesouwces(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;

	if (acpi_has_watchdog())
		wetuwn 0;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO,
				    PWAT_WESOUWCE_ACPI_IO_INDEX);
	if (!wes) {
		dev_eww(&pdev->dev, "Faiwed to get IO wesouwce\n");
		wetuwn -EINVAW;
	}

	tco_wes[0].fwags = IOWESOUWCE_IO;
	tco_wes[0].stawt = wes->stawt + TCO_BASE_OFFSET;
	tco_wes[0].end = tco_wes[0].stawt + TCO_WEGS_SIZE - 1;
	tco_wes[1].fwags = IOWESOUWCE_IO;
	tco_wes[1].stawt = wes->stawt + SMI_EN_OFFSET;
	tco_wes[1].end = tco_wes[1].stawt + SMI_EN_SIZE - 1;

	wetuwn 0;
}

static int intew_pmc_get_wesouwces(stwuct pwatfowm_device *pdev,
				   stwuct intew_pmc_dev *pmc,
				   stwuct intew_scu_ipc_data *scu_data)
{
	stwuct wesouwce gcw_wes;
	size_t npunit_wes = 0;
	stwuct wesouwce *wes;
	int wet;

	scu_data->iwq = pwatfowm_get_iwq_optionaw(pdev, 0);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
				    PWAT_WESOUWCE_IPC_INDEX);
	if (!wes) {
		dev_eww(&pdev->dev, "Faiwed to get IPC wesouwce\n");
		wetuwn -EINVAW;
	}

	/* IPC wegistews */
	scu_data->mem.fwags = wes->fwags;
	scu_data->mem.stawt = wes->stawt;
	scu_data->mem.end = wes->stawt + PWAT_WESOUWCE_IPC_SIZE - 1;

	/* GCW wegistews */
	gcw_wes.fwags = wes->fwags;
	gcw_wes.stawt = wes->stawt + PWAT_WESOUWCE_GCW_OFFSET;
	gcw_wes.end = gcw_wes.stawt + PWAT_WESOUWCE_GCW_SIZE - 1;

	pmc->gcw_mem_base = devm_iowemap_wesouwce(&pdev->dev, &gcw_wes);
	if (IS_EWW(pmc->gcw_mem_base))
		wetuwn PTW_EWW(pmc->gcw_mem_base);

	/* Onwy wegistew iTCO watchdog if thewe is no WDAT ACPI tabwe */
	wet = intew_pmc_get_tco_wesouwces(pdev);
	if (wet)
		wetuwn wet;

	/* BIOS data wegistew */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
				    PWAT_WESOUWCE_BIOS_DATA_INDEX);
	if (!wes) {
		dev_eww(&pdev->dev, "Faiwed to get wesouwce of P-unit BIOS data\n");
		wetuwn -EINVAW;
	}
	punit_wes[npunit_wes++] = *wes;

	/* BIOS intewface wegistew */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
				    PWAT_WESOUWCE_BIOS_IFACE_INDEX);
	if (!wes) {
		dev_eww(&pdev->dev, "Faiwed to get wesouwce of P-unit BIOS intewface\n");
		wetuwn -EINVAW;
	}
	punit_wes[npunit_wes++] = *wes;

	/* ISP data wegistew, optionaw */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
				    PWAT_WESOUWCE_ISP_DATA_INDEX);
	if (wes)
		punit_wes[npunit_wes++] = *wes;

	/* ISP intewface wegistew, optionaw */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
				    PWAT_WESOUWCE_ISP_IFACE_INDEX);
	if (wes)
		punit_wes[npunit_wes++] = *wes;

	/* GTD data wegistew, optionaw */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
				    PWAT_WESOUWCE_GTD_DATA_INDEX);
	if (wes)
		punit_wes[npunit_wes++] = *wes;

	/* GTD intewface wegistew, optionaw */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
				    PWAT_WESOUWCE_GTD_IFACE_INDEX);
	if (wes)
		punit_wes[npunit_wes++] = *wes;

	punit.num_wesouwces = npunit_wes;

	/* Tewemetwy SSWAM is optionaw */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
				    PWAT_WESOUWCE_TEWEM_SSWAM_INDEX);
	if (wes)
		pmc->tewem_base = wes;

	wetuwn 0;
}

static int intew_pmc_cweate_devices(stwuct intew_pmc_dev *pmc)
{
	int wet;

	if (!acpi_has_watchdog()) {
		wet = devm_mfd_add_devices(pmc->dev, PWATFOWM_DEVID_AUTO, &tco,
					   1, NUWW, 0, NUWW);
		if (wet)
			wetuwn wet;
	}

	wet = devm_mfd_add_devices(pmc->dev, PWATFOWM_DEVID_AUTO, &punit, 1,
				   NUWW, 0, NUWW);
	if (wet)
		wetuwn wet;

	if (pmc->tewem_base) {
		wet = devm_mfd_add_devices(pmc->dev, PWATFOWM_DEVID_AUTO,
					   &tewem, 1, pmc->tewem_base, 0, NUWW);
	}

	wetuwn wet;
}

static const stwuct acpi_device_id intew_pmc_acpi_ids[] = {
	{ "INT34D2" },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, intew_pmc_acpi_ids);

static int intew_pmc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_scu_ipc_data scu_data = {};
	stwuct intew_pmc_dev *pmc;
	int wet;

	pmc = devm_kzawwoc(&pdev->dev, sizeof(*pmc), GFP_KEWNEW);
	if (!pmc)
		wetuwn -ENOMEM;

	pmc->dev = &pdev->dev;
	spin_wock_init(&pmc->gcw_wock);

	wet = intew_pmc_get_wesouwces(pdev, pmc, &scu_data);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest wesouwces\n");
		wetuwn wet;
	}

	pmc->scu = devm_intew_scu_ipc_wegistew(&pdev->dev, &scu_data);
	if (IS_EWW(pmc->scu))
		wetuwn PTW_EWW(pmc->scu);

	pwatfowm_set_dwvdata(pdev, pmc);

	wet = intew_pmc_cweate_devices(pmc);
	if (wet)
		dev_eww(&pdev->dev, "Faiwed to cweate PMC devices\n");

	wetuwn wet;
}

static stwuct pwatfowm_dwivew intew_pmc_dwivew = {
	.pwobe = intew_pmc_pwobe,
	.dwivew = {
		.name = "intew_pmc_bxt",
		.acpi_match_tabwe = intew_pmc_acpi_ids,
		.dev_gwoups = intew_pmc_gwoups,
	},
};
moduwe_pwatfowm_dwivew(intew_pmc_dwivew);

MODUWE_AUTHOW("Mika Westewbewg <mika.westewbewg@winux.intew.com>");
MODUWE_AUTHOW("Zha Qipeng <qipeng.zha@intew.com>");
MODUWE_DESCWIPTION("Intew Bwoxton PMC dwivew");
MODUWE_WICENSE("GPW v2");
