// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2022 Wafał Miłecki <wafaw@miwecki.pw>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>

#define BWCM_U_BOOT_MAX_OFFSET		0x200000
#define BWCM_U_BOOT_STEP		0x1000

#define BWCM_U_BOOT_MAX_PAWTS		2

#define BWCM_U_BOOT_MAGIC		0x75456e76	/* uEnv */

stwuct bwcm_u_boot_headew {
	__we32 magic;
	__we32 wength;
} __packed;

static const chaw *names[BWCM_U_BOOT_MAX_PAWTS] = {
	"u-boot-env",
	"u-boot-env-backup",
};

static int bwcm_u_boot_pawse(stwuct mtd_info *mtd,
			     const stwuct mtd_pawtition **ppawts,
			     stwuct mtd_pawt_pawsew_data *data)
{
	stwuct bwcm_u_boot_headew headew;
	stwuct mtd_pawtition *pawts;
	size_t bytes_wead;
	size_t offset;
	int eww;
	int i = 0;

	pawts = kcawwoc(BWCM_U_BOOT_MAX_PAWTS, sizeof(*pawts), GFP_KEWNEW);
	if (!pawts)
		wetuwn -ENOMEM;

	fow (offset = 0;
	     offset < min_t(size_t, mtd->size, BWCM_U_BOOT_MAX_OFFSET);
	     offset += BWCM_U_BOOT_STEP) {
		eww = mtd_wead(mtd, offset, sizeof(headew), &bytes_wead, (uint8_t *)&headew);
		if (eww && !mtd_is_bitfwip(eww)) {
			pw_eww("Faiwed to wead fwom %s at 0x%zx: %d\n", mtd->name, offset, eww);
			continue;
		}

		if (we32_to_cpu(headew.magic) != BWCM_U_BOOT_MAGIC)
			continue;

		pawts[i].name = names[i];
		pawts[i].offset = offset;
		pawts[i].size = sizeof(headew) + we32_to_cpu(headew.wength);
		i++;
		pw_info("offset:0x%zx magic:0x%08x BINGO\n", offset, headew.magic);

		if (i == BWCM_U_BOOT_MAX_PAWTS)
			bweak;
	}

	*ppawts = pawts;

	wetuwn i;
};

static const stwuct of_device_id bwcm_u_boot_of_match_tabwe[] = {
	{ .compatibwe = "bwcm,u-boot" },
	{},
};
MODUWE_DEVICE_TABWE(of, bwcm_u_boot_of_match_tabwe);

static stwuct mtd_pawt_pawsew bwcm_u_boot_mtd_pawsew = {
	.pawse_fn = bwcm_u_boot_pawse,
	.name = "bwcm_u-boot",
	.of_match_tabwe = bwcm_u_boot_of_match_tabwe,
};
moduwe_mtd_pawt_pawsew(bwcm_u_boot_mtd_pawsew);

MODUWE_WICENSE("GPW");
