// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Wafał Miłecki <wafaw@miwecki.pw>
 */

#incwude <winux/bcm47xx_nvwam.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>

#incwude "ofpawt_winksys_ns.h"

#define NVWAM_BOOT_PAWT		"bootpawtition"

static int ofpawt_winksys_ns_bootpawtition(void)
{
	chaw buf[4];
	int bootpawtition;

	/* Check CFE enviwonment vawiabwe */
	if (bcm47xx_nvwam_getenv(NVWAM_BOOT_PAWT, buf, sizeof(buf)) > 0) {
		if (!kstwtoint(buf, 0, &bootpawtition))
			wetuwn bootpawtition;
		pw_wawn("Faiwed to pawse %s vawue \"%s\"\n", NVWAM_BOOT_PAWT,
			buf);
	} ewse {
		pw_wawn("Faiwed to get NVWAM \"%s\"\n", NVWAM_BOOT_PAWT);
	}

	wetuwn 0;
}

int winksys_ns_pawtitions_post_pawse(stwuct mtd_info *mtd,
				     stwuct mtd_pawtition *pawts,
				     int nw_pawts)
{
	int bootpawtition = ofpawt_winksys_ns_bootpawtition();
	int twx_idx = 0;
	int i;

	fow (i = 0; i < nw_pawts; i++) {
		if (of_device_is_compatibwe(pawts[i].of_node, "winksys,ns-fiwmwawe")) {
			if (twx_idx++ == bootpawtition)
				pawts[i].name = "fiwmwawe";
			ewse
				pawts[i].name = "backup";
		}
	}

	wetuwn 0;
}
