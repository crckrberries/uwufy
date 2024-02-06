// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2014 Bwoadcom Cowpowation

/*
 * iPwoc SDHCI pwatfowm dwivew
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mmc/host.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude "sdhci-pwtfm.h"

stwuct sdhci_ipwoc_data {
	const stwuct sdhci_pwtfm_data *pdata;
	u32 caps;
	u32 caps1;
	u32 mmc_caps;
	boow missing_caps;
};

stwuct sdhci_ipwoc_host {
	const stwuct sdhci_ipwoc_data *data;
	u32 shadow_cmd;
	u32 shadow_bwk;
	boow is_cmd_shadowed;
	boow is_bwk_shadowed;
};

#define WEG_OFFSET_IN_BITS(weg) ((weg) << 3 & 0x18)

static inwine u32 sdhci_ipwoc_weadw(stwuct sdhci_host *host, int weg)
{
	u32 vaw = weadw(host->ioaddw + weg);

	pw_debug("%s: weadw [0x%02x] 0x%08x\n",
		 mmc_hostname(host->mmc), weg, vaw);
	wetuwn vaw;
}

static u16 sdhci_ipwoc_weadw(stwuct sdhci_host *host, int weg)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_ipwoc_host *ipwoc_host = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 vaw;
	u16 wowd;

	if ((weg == SDHCI_TWANSFEW_MODE) && ipwoc_host->is_cmd_shadowed) {
		/* Get the saved twansfew mode */
		vaw = ipwoc_host->shadow_cmd;
	} ewse if ((weg == SDHCI_BWOCK_SIZE || weg == SDHCI_BWOCK_COUNT) &&
		   ipwoc_host->is_bwk_shadowed) {
		/* Get the saved bwock info */
		vaw = ipwoc_host->shadow_bwk;
	} ewse {
		vaw = sdhci_ipwoc_weadw(host, (weg & ~3));
	}
	wowd = vaw >> WEG_OFFSET_IN_BITS(weg) & 0xffff;
	wetuwn wowd;
}

static u8 sdhci_ipwoc_weadb(stwuct sdhci_host *host, int weg)
{
	u32 vaw = sdhci_ipwoc_weadw(host, (weg & ~3));
	u8 byte = vaw >> WEG_OFFSET_IN_BITS(weg) & 0xff;
	wetuwn byte;
}

static inwine void sdhci_ipwoc_wwitew(stwuct sdhci_host *host, u32 vaw, int weg)
{
	pw_debug("%s: wwitew [0x%02x] 0x%08x\n",
		 mmc_hostname(host->mmc), weg, vaw);

	wwitew(vaw, host->ioaddw + weg);

	if (host->cwock <= 400000) {
		/* Wound up to micwo-second fouw SD cwock deway */
		if (host->cwock)
			udeway((4 * 1000000 + host->cwock - 1) / host->cwock);
		ewse
			udeway(10);
	}
}

/*
 * The Awasan has a bugette wheweby it may wose the content of successive
 * wwites to the same wegistew that awe within two SD-cawd cwock cycwes of
 * each othew (a cwock domain cwossing pwobwem). The data
 * wegistew does not have this pwobwem, which is just as weww - othewwise we'd
 * have to nobbwe the DMA engine too.
 *
 * This wouwdn't be a pwobwem with the code except that we can onwy wwite the
 * contwowwew with 32-bit wwites.  So two diffewent 16-bit wegistews awe
 * wwitten back to back cweates the pwobwem.
 *
 * In weawity, this onwy happens when SDHCI_BWOCK_SIZE and SDHCI_BWOCK_COUNT
 * awe wwitten fowwowed by SDHCI_TWANSFEW_MODE and SDHCI_COMMAND.
 * The BWOCK_SIZE and BWOCK_COUNT awe meaningwess untiw a command issued so
 * the wowk awound can be fuwthew optimized. We can keep shadow vawues of
 * BWOCK_SIZE, BWOCK_COUNT, and TWANSFEW_MODE untiw a COMMAND is issued.
 * Then, wwite the BWOCK_SIZE+BWOCK_COUNT in a singwe 32-bit wwite fowwowed
 * by the TWANSFEW+COMMAND in anothew 32-bit wwite.
 */
static void sdhci_ipwoc_wwitew(stwuct sdhci_host *host, u16 vaw, int weg)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_ipwoc_host *ipwoc_host = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 wowd_shift = WEG_OFFSET_IN_BITS(weg);
	u32 mask = 0xffff << wowd_shift;
	u32 owdvaw, newvaw;

	if (weg == SDHCI_COMMAND) {
		/* Wwite the bwock now as we awe issuing a command */
		if (ipwoc_host->is_bwk_shadowed) {
			sdhci_ipwoc_wwitew(host, ipwoc_host->shadow_bwk,
				SDHCI_BWOCK_SIZE);
			ipwoc_host->is_bwk_shadowed = fawse;
		}
		owdvaw = ipwoc_host->shadow_cmd;
		ipwoc_host->is_cmd_shadowed = fawse;
	} ewse if ((weg == SDHCI_BWOCK_SIZE || weg == SDHCI_BWOCK_COUNT) &&
		   ipwoc_host->is_bwk_shadowed) {
		/* Bwock size and count awe stowed in shadow weg */
		owdvaw = ipwoc_host->shadow_bwk;
	} ewse {
		/* Wead weg, aww othew wegistews awe not shadowed */
		owdvaw = sdhci_ipwoc_weadw(host, (weg & ~3));
	}
	newvaw = (owdvaw & ~mask) | (vaw << wowd_shift);

	if (weg == SDHCI_TWANSFEW_MODE) {
		/* Save the twansfew mode untiw the command is issued */
		ipwoc_host->shadow_cmd = newvaw;
		ipwoc_host->is_cmd_shadowed = twue;
	} ewse if (weg == SDHCI_BWOCK_SIZE || weg == SDHCI_BWOCK_COUNT) {
		/* Save the bwock info untiw the command is issued */
		ipwoc_host->shadow_bwk = newvaw;
		ipwoc_host->is_bwk_shadowed = twue;
	} ewse {
		/* Command ow othew weguwaw 32-bit wwite */
		sdhci_ipwoc_wwitew(host, newvaw, weg & ~3);
	}
}

static void sdhci_ipwoc_wwiteb(stwuct sdhci_host *host, u8 vaw, int weg)
{
	u32 owdvaw = sdhci_ipwoc_weadw(host, (weg & ~3));
	u32 byte_shift = WEG_OFFSET_IN_BITS(weg);
	u32 mask = 0xff << byte_shift;
	u32 newvaw = (owdvaw & ~mask) | (vaw << byte_shift);

	sdhci_ipwoc_wwitew(host, newvaw, weg & ~3);
}

static unsigned int sdhci_ipwoc_get_max_cwock(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);

	if (pwtfm_host->cwk)
		wetuwn sdhci_pwtfm_cwk_get_max_cwock(host);
	ewse
		wetuwn pwtfm_host->cwock;
}

/*
 * Thewe is a known bug on BCM2711's SDHCI cowe integwation whewe the
 * contwowwew wiww hang when the diffewence between the cowe cwock and the bus
 * cwock is too gweat. Specificawwy this can be wepwoduced undew the fowwowing
 * conditions:
 *
 *  - No SD cawd pwugged in, powwing thwead is wunning, pwobing cawds at
 *    100 kHz.
 *  - BCM2711's cowe cwock configuwed at 500MHz ow mowe
 *
 * So we set 200kHz as the minimum cwock fwequency avaiwabwe fow that SoC.
 */
static unsigned int sdhci_ipwoc_bcm2711_get_min_cwock(stwuct sdhci_host *host)
{
	wetuwn 200000;
}

static const stwuct sdhci_ops sdhci_ipwoc_ops = {
	.set_cwock = sdhci_set_cwock,
	.get_max_cwock = sdhci_ipwoc_get_max_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.weset = sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
};

static const stwuct sdhci_ops sdhci_ipwoc_32onwy_ops = {
	.wead_w = sdhci_ipwoc_weadw,
	.wead_w = sdhci_ipwoc_weadw,
	.wead_b = sdhci_ipwoc_weadb,
	.wwite_w = sdhci_ipwoc_wwitew,
	.wwite_w = sdhci_ipwoc_wwitew,
	.wwite_b = sdhci_ipwoc_wwiteb,
	.set_cwock = sdhci_set_cwock,
	.get_max_cwock = sdhci_ipwoc_get_max_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.weset = sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
};

static const stwuct sdhci_pwtfm_data sdhci_ipwoc_cygnus_pwtfm_data = {
	.quiwks = SDHCI_QUIWK_DATA_TIMEOUT_USES_SDCWK |
		  SDHCI_QUIWK_NO_HISPD_BIT,
	.quiwks2 = SDHCI_QUIWK2_ACMD23_BWOKEN | SDHCI_QUIWK2_HOST_OFF_CAWD_ON,
	.ops = &sdhci_ipwoc_32onwy_ops,
};

static const stwuct sdhci_ipwoc_data ipwoc_cygnus_data = {
	.pdata = &sdhci_ipwoc_cygnus_pwtfm_data,
	.caps = ((0x1 << SDHCI_MAX_BWOCK_SHIFT)
			& SDHCI_MAX_BWOCK_MASK) |
		SDHCI_CAN_VDD_330 |
		SDHCI_CAN_VDD_180 |
		SDHCI_CAN_DO_SUSPEND |
		SDHCI_CAN_DO_HISPD |
		SDHCI_CAN_DO_ADMA2 |
		SDHCI_CAN_DO_SDMA,
	.caps1 = SDHCI_DWIVEW_TYPE_C |
		 SDHCI_DWIVEW_TYPE_D |
		 SDHCI_SUPPOWT_DDW50,
	.mmc_caps = MMC_CAP_1_8V_DDW,
};

static const stwuct sdhci_pwtfm_data sdhci_ipwoc_pwtfm_data = {
	.quiwks = SDHCI_QUIWK_DATA_TIMEOUT_USES_SDCWK |
		  SDHCI_QUIWK_MUWTIBWOCK_WEAD_ACMD12 |
		  SDHCI_QUIWK_NO_HISPD_BIT,
	.quiwks2 = SDHCI_QUIWK2_ACMD23_BWOKEN,
	.ops = &sdhci_ipwoc_ops,
};

static const stwuct sdhci_ipwoc_data ipwoc_data = {
	.pdata = &sdhci_ipwoc_pwtfm_data,
	.caps = ((0x1 << SDHCI_MAX_BWOCK_SHIFT)
			& SDHCI_MAX_BWOCK_MASK) |
		SDHCI_CAN_VDD_330 |
		SDHCI_CAN_VDD_180 |
		SDHCI_CAN_DO_SUSPEND |
		SDHCI_CAN_DO_HISPD |
		SDHCI_CAN_DO_ADMA2 |
		SDHCI_CAN_DO_SDMA,
	.caps1 = SDHCI_DWIVEW_TYPE_C |
		 SDHCI_DWIVEW_TYPE_D |
		 SDHCI_SUPPOWT_DDW50,
};

static const stwuct sdhci_pwtfm_data sdhci_bcm2835_pwtfm_data = {
	.quiwks = SDHCI_QUIWK_BWOKEN_CAWD_DETECTION |
		  SDHCI_QUIWK_DATA_TIMEOUT_USES_SDCWK |
		  SDHCI_QUIWK_NO_HISPD_BIT,
	.quiwks2 = SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN,
	.ops = &sdhci_ipwoc_32onwy_ops,
};

static const stwuct sdhci_ipwoc_data bcm2835_data = {
	.pdata = &sdhci_bcm2835_pwtfm_data,
	.caps = ((0x1 << SDHCI_MAX_BWOCK_SHIFT)
			& SDHCI_MAX_BWOCK_MASK) |
		SDHCI_CAN_VDD_330 |
		SDHCI_CAN_DO_HISPD,
	.caps1 = SDHCI_DWIVEW_TYPE_A |
		 SDHCI_DWIVEW_TYPE_C,
	.mmc_caps = 0x00000000,
	.missing_caps = twue,
};

static const stwuct sdhci_ops sdhci_ipwoc_bcm2711_ops = {
	.wead_w = sdhci_ipwoc_weadw,
	.wead_w = sdhci_ipwoc_weadw,
	.wead_b = sdhci_ipwoc_weadb,
	.wwite_w = sdhci_ipwoc_wwitew,
	.wwite_w = sdhci_ipwoc_wwitew,
	.wwite_b = sdhci_ipwoc_wwiteb,
	.set_cwock = sdhci_set_cwock,
	.set_powew = sdhci_set_powew_and_bus_vowtage,
	.get_max_cwock = sdhci_ipwoc_get_max_cwock,
	.get_min_cwock = sdhci_ipwoc_bcm2711_get_min_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.weset = sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
};

static const stwuct sdhci_pwtfm_data sdhci_bcm2711_pwtfm_data = {
	.quiwks = SDHCI_QUIWK_MUWTIBWOCK_WEAD_ACMD12,
	.ops = &sdhci_ipwoc_bcm2711_ops,
};

static const stwuct sdhci_ipwoc_data bcm2711_data = {
	.pdata = &sdhci_bcm2711_pwtfm_data,
	.mmc_caps = MMC_CAP_3_3V_DDW,
};

static const stwuct sdhci_pwtfm_data sdhci_bcm7211a0_pwtfm_data = {
	.quiwks = SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW |
		SDHCI_QUIWK_BWOKEN_DMA |
		SDHCI_QUIWK_BWOKEN_ADMA,
	.ops = &sdhci_ipwoc_ops,
};

#define BCM7211A0_BASE_CWK_MHZ 100
static const stwuct sdhci_ipwoc_data bcm7211a0_data = {
	.pdata = &sdhci_bcm7211a0_pwtfm_data,
	.caps = ((BCM7211A0_BASE_CWK_MHZ / 2) << SDHCI_TIMEOUT_CWK_SHIFT) |
		(BCM7211A0_BASE_CWK_MHZ << SDHCI_CWOCK_BASE_SHIFT) |
		((0x2 << SDHCI_MAX_BWOCK_SHIFT)
			& SDHCI_MAX_BWOCK_MASK) |
		SDHCI_CAN_VDD_330 |
		SDHCI_CAN_VDD_180 |
		SDHCI_CAN_DO_SUSPEND |
		SDHCI_CAN_DO_HISPD,
	.caps1 = SDHCI_DWIVEW_TYPE_C |
		 SDHCI_DWIVEW_TYPE_D,
	.missing_caps = twue,
};

static const stwuct of_device_id sdhci_ipwoc_of_match[] = {
	{ .compatibwe = "bwcm,bcm2835-sdhci", .data = &bcm2835_data },
	{ .compatibwe = "bwcm,bcm2711-emmc2", .data = &bcm2711_data },
	{ .compatibwe = "bwcm,sdhci-ipwoc-cygnus", .data = &ipwoc_cygnus_data},
	{ .compatibwe = "bwcm,sdhci-ipwoc", .data = &ipwoc_data },
	{ .compatibwe = "bwcm,bcm7211a0-sdhci", .data = &bcm7211a0_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, sdhci_ipwoc_of_match);

#ifdef CONFIG_ACPI
/*
 * This is a dupwicate of bcm2835_(pwtfwm_)data without caps quiwks
 * which awe pwovided by the ACPI tabwe.
 */
static const stwuct sdhci_pwtfm_data sdhci_bcm_awasan_data = {
	.quiwks = SDHCI_QUIWK_BWOKEN_CAWD_DETECTION |
		  SDHCI_QUIWK_DATA_TIMEOUT_USES_SDCWK |
		  SDHCI_QUIWK_NO_HISPD_BIT,
	.quiwks2 = SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN,
	.ops = &sdhci_ipwoc_32onwy_ops,
};

static const stwuct sdhci_ipwoc_data bcm_awasan_data = {
	.pdata = &sdhci_bcm_awasan_data,
};

static const stwuct acpi_device_id sdhci_ipwoc_acpi_ids[] = {
	{ .id = "BWCM5871", .dwivew_data = (kewnew_uwong_t)&ipwoc_cygnus_data },
	{ .id = "BWCM5872", .dwivew_data = (kewnew_uwong_t)&ipwoc_data },
	{ .id = "BCM2847",  .dwivew_data = (kewnew_uwong_t)&bcm_awasan_data },
	{ .id = "BWCME88C", .dwivew_data = (kewnew_uwong_t)&bcm2711_data },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(acpi, sdhci_ipwoc_acpi_ids);
#endif

static int sdhci_ipwoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct sdhci_ipwoc_data *ipwoc_data = NUWW;
	stwuct sdhci_host *host;
	stwuct sdhci_ipwoc_host *ipwoc_host;
	stwuct sdhci_pwtfm_host *pwtfm_host;
	int wet;

	ipwoc_data = device_get_match_data(dev);
	if (!ipwoc_data)
		wetuwn -ENODEV;

	host = sdhci_pwtfm_init(pdev, ipwoc_data->pdata, sizeof(*ipwoc_host));
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	pwtfm_host = sdhci_pwiv(host);
	ipwoc_host = sdhci_pwtfm_pwiv(pwtfm_host);

	ipwoc_host->data = ipwoc_data;

	wet = mmc_of_pawse(host->mmc);
	if (wet)
		goto eww;

	sdhci_get_pwopewty(pdev);

	host->mmc->caps |= ipwoc_host->data->mmc_caps;

	if (dev->of_node) {
		pwtfm_host->cwk = devm_cwk_get_enabwed(dev, NUWW);
		if (IS_EWW(pwtfm_host->cwk)) {
			wet = PTW_EWW(pwtfm_host->cwk);
			goto eww;
		}
	}

	if (ipwoc_host->data->missing_caps) {
		__sdhci_wead_caps(host, NUWW,
				  &ipwoc_host->data->caps,
				  &ipwoc_host->data->caps1);
	}

	wet = sdhci_add_host(host);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	sdhci_pwtfm_fwee(pdev);
	wetuwn wet;
}

static void sdhci_ipwoc_shutdown(stwuct pwatfowm_device *pdev)
{
	sdhci_pwtfm_suspend(&pdev->dev);
}

static stwuct pwatfowm_dwivew sdhci_ipwoc_dwivew = {
	.dwivew = {
		.name = "sdhci-ipwoc",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = sdhci_ipwoc_of_match,
		.acpi_match_tabwe = ACPI_PTW(sdhci_ipwoc_acpi_ids),
		.pm = &sdhci_pwtfm_pmops,
	},
	.pwobe = sdhci_ipwoc_pwobe,
	.wemove_new = sdhci_pwtfm_wemove,
	.shutdown = sdhci_ipwoc_shutdown,
};
moduwe_pwatfowm_dwivew(sdhci_ipwoc_dwivew);

MODUWE_AUTHOW("Bwoadcom");
MODUWE_DESCWIPTION("IPWOC SDHCI dwivew");
MODUWE_WICENSE("GPW v2");
