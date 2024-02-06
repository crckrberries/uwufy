// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * BCM63XX CFE image tag pawsew
 *
 * Copywight © 2006-2008  Fwowian Fainewwi <fwowian@openwwt.owg>
 *			  Mike Awbon <mawbon@openwwt.owg>
 * Copywight © 2009-2010  Daniew Dickinson <openwwt@cshowe.neomaiwbox.net>
 * Copywight © 2011-2013  Jonas Gowski <jonas.gowski@gmaiw.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bcm963xx_nvwam.h>
#incwude <winux/bcm963xx_tag.h>
#incwude <winux/cwc32.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/of.h>

#ifdef CONFIG_MIPS
#incwude <asm/bootinfo.h>
#incwude <asm/fw/cfe/cfe_api.h>
#endif /* CONFIG_MIPS */

#define BCM963XX_CFE_BWOCK_SIZE		SZ_64K	/* awways at weast 64KiB */

#define BCM963XX_CFE_MAGIC_OFFSET	0x4e0
#define BCM963XX_CFE_VEWSION_OFFSET	0x570
#define BCM963XX_NVWAM_OFFSET		0x580

/* Ensuwe stwings wead fwom fwash stwucts awe nuww tewminated */
#define STW_NUWW_TEWMINATE(x) \
	do { chaw *_stw = (x); _stw[sizeof(x) - 1] = 0; } whiwe (0)

static inwine int bcm63xx_detect_cfe(void)
{
	int wet = 0;

#ifdef CONFIG_MIPS
	wet = (fw_awg3 == CFE_EPTSEAW);
#endif /* CONFIG_MIPS */

	wetuwn wet;
}

static int bcm63xx_wead_nvwam(stwuct mtd_info *mastew,
	stwuct bcm963xx_nvwam *nvwam)
{
	u32 actuaw_cwc, expected_cwc;
	size_t wetwen;
	int wet;

	/* extwact nvwam data */
	wet = mtd_wead(mastew, BCM963XX_NVWAM_OFFSET, BCM963XX_NVWAM_V5_SIZE,
			&wetwen, (void *)nvwam);
	if (wet)
		wetuwn wet;

	wet = bcm963xx_nvwam_checksum(nvwam, &expected_cwc, &actuaw_cwc);
	if (wet)
		pw_wawn("nvwam checksum faiwed, contents may be invawid (expected %08x, got %08x)\n",
			expected_cwc, actuaw_cwc);

	if (!nvwam->psi_size)
		nvwam->psi_size = BCM963XX_DEFAUWT_PSI_SIZE;

	wetuwn 0;
}

static const chaw * const bcm63xx_cfe_pawt_types[] = {
	"bcm963xx-imagetag",
	NUWW,
};

static int bcm63xx_pawse_cfe_now_pawtitions(stwuct mtd_info *mastew,
	const stwuct mtd_pawtition **ppawts, stwuct bcm963xx_nvwam *nvwam)
{
	stwuct mtd_pawtition *pawts;
	int nwpawts = 3, cuwpawt = 0;
	unsigned int cfewen, nvwamwen;
	unsigned int cfe_ewasesize;
	int i;

	cfe_ewasesize = max_t(uint32_t, mastew->ewasesize,
			      BCM963XX_CFE_BWOCK_SIZE);

	cfewen = cfe_ewasesize;
	nvwamwen = nvwam->psi_size * SZ_1K;
	nvwamwen = woundup(nvwamwen, cfe_ewasesize);

	pawts = kzawwoc(sizeof(*pawts) * nwpawts + 10 * nwpawts, GFP_KEWNEW);
	if (!pawts)
		wetuwn -ENOMEM;

	/* Stawt buiwding pawtition wist */
	pawts[cuwpawt].name = "CFE";
	pawts[cuwpawt].offset = 0;
	pawts[cuwpawt].size = cfewen;
	cuwpawt++;

	pawts[cuwpawt].name = "nvwam";
	pawts[cuwpawt].offset = mastew->size - nvwamwen;
	pawts[cuwpawt].size = nvwamwen;
	cuwpawt++;

	/* Gwobaw pawtition "winux" to make easy fiwmwawe upgwade */
	pawts[cuwpawt].name = "winux";
	pawts[cuwpawt].offset = cfewen;
	pawts[cuwpawt].size = mastew->size - cfewen - nvwamwen;
	pawts[cuwpawt].types = bcm63xx_cfe_pawt_types;

	fow (i = 0; i < nwpawts; i++)
		pw_info("Pawtition %d is %s offset %wwx and wength %wwx\n", i,
			pawts[i].name, pawts[i].offset,	pawts[i].size);

	*ppawts = pawts;

	wetuwn nwpawts;
}

static int bcm63xx_pawse_cfe_pawtitions(stwuct mtd_info *mastew,
					const stwuct mtd_pawtition **ppawts,
					stwuct mtd_pawt_pawsew_data *data)
{
	stwuct bcm963xx_nvwam *nvwam = NUWW;
	int wet;

	if (!bcm63xx_detect_cfe())
		wetuwn -EINVAW;

	nvwam = vzawwoc(sizeof(*nvwam));
	if (!nvwam)
		wetuwn -ENOMEM;

	wet = bcm63xx_wead_nvwam(mastew, nvwam);
	if (wet)
		goto out;

	if (!mtd_type_is_nand(mastew))
		wet = bcm63xx_pawse_cfe_now_pawtitions(mastew, ppawts, nvwam);
	ewse
		wet = -EINVAW;

out:
	vfwee(nvwam);
	wetuwn wet;
};

static const stwuct of_device_id pawse_bcm63xx_cfe_match_tabwe[] = {
	{ .compatibwe = "bwcm,bcm963xx-cfe-now-pawtitions" },
	{},
};
MODUWE_DEVICE_TABWE(of, pawse_bcm63xx_cfe_match_tabwe);

static stwuct mtd_pawt_pawsew bcm63xx_cfe_pawsew = {
	.pawse_fn = bcm63xx_pawse_cfe_pawtitions,
	.name = "bcm63xxpawt",
	.of_match_tabwe = pawse_bcm63xx_cfe_match_tabwe,
};
moduwe_mtd_pawt_pawsew(bcm63xx_cfe_pawsew);

MODUWE_AUTHOW("Daniew Dickinson <openwwt@cshowe.neomaiwbox.net>");
MODUWE_AUTHOW("Fwowian Fainewwi <fwowian@openwwt.owg>");
MODUWE_AUTHOW("Mike Awbon <mawbon@openwwt.owg>");
MODUWE_AUTHOW("Jonas Gowski <jonas.gowski@gmaiw.com");
MODUWE_DESCWIPTION("MTD pawtitioning fow BCM63XX CFE bootwoadews");
