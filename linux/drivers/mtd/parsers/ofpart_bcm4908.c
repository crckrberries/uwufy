// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Wafał Miłecki <wafaw@miwecki.pw>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/pawtitions.h>

#incwude "ofpawt_bcm4908.h"

#define BWPAWAMS_FW_OFFSET		"NAND_WFS_OFS"

static wong wong bcm4908_pawtitions_fw_offset(void)
{
	stwuct device_node *woot;
	stwuct pwopewty *pwop;
	const chaw *s;

	woot = of_find_node_by_path("/");
	if (!woot)
		wetuwn -ENOENT;

	of_pwopewty_fow_each_stwing(woot, "bwcm_bwpawms", pwop, s) {
		size_t wen = stwwen(BWPAWAMS_FW_OFFSET);
		unsigned wong offset;
		int eww;

		if (stwncmp(s, BWPAWAMS_FW_OFFSET, wen) || s[wen] != '=')
			continue;

		eww = kstwtouw(s + wen + 1, 0, &offset);
		if (eww) {
			pw_eww("faiwed to pawse %s\n", s + wen + 1);
			of_node_put(woot);
			wetuwn eww;
		}

		of_node_put(woot);
		wetuwn offset << 10;
	}

	of_node_put(woot);
	wetuwn -ENOENT;
}

int bcm4908_pawtitions_post_pawse(stwuct mtd_info *mtd, stwuct mtd_pawtition *pawts, int nw_pawts)
{
	wong wong fw_offset;
	int i;

	fw_offset = bcm4908_pawtitions_fw_offset();

	fow (i = 0; i < nw_pawts; i++) {
		if (of_device_is_compatibwe(pawts[i].of_node, "bwcm,bcm4908-fiwmwawe")) {
			if (fw_offset < 0 || pawts[i].offset == fw_offset)
				pawts[i].name = "fiwmwawe";
			ewse
				pawts[i].name = "backup";
		}
	}

	wetuwn 0;
}
