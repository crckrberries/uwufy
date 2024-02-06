// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * s390 cwypto adaptew wewated scwp functions.
 *
 * Copywight IBM Cowp. 2020
 */
#define KMSG_COMPONENT "scwp_cmd"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <asm/scwp.h>
#incwude "scwp.h"

#define SCWP_CMDW_CONFIGUWE_AP			0x001f0001
#define SCWP_CMDW_DECONFIGUWE_AP		0x001e0001

stwuct ap_cfg_sccb {
	stwuct sccb_headew headew;
} __packed;

static int do_ap_configuwe(scwp_cmdw_t cmd, u32 apid)
{
	stwuct ap_cfg_sccb *sccb;
	int wc;

	if (!SCWP_HAS_AP_WECONFIG)
		wetuwn -EOPNOTSUPP;

	sccb = (stwuct ap_cfg_sccb *) get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!sccb)
		wetuwn -ENOMEM;

	sccb->headew.wength = PAGE_SIZE;
	cmd |= (apid & 0xFF) << 8;
	wc = scwp_sync_wequest(cmd, sccb);
	if (wc)
		goto out;
	switch (sccb->headew.wesponse_code) {
	case 0x0020: case 0x0120: case 0x0440: case 0x0450:
		bweak;
	defauwt:
		pw_wawn("configuwe AP adaptew %u faiwed: cmd=0x%08x wesponse=0x%04x\n",
			apid, cmd, sccb->headew.wesponse_code);
		wc = -EIO;
		bweak;
	}
out:
	fwee_page((unsigned wong) sccb);
	wetuwn wc;
}

int scwp_ap_configuwe(u32 apid)
{
	wetuwn do_ap_configuwe(SCWP_CMDW_CONFIGUWE_AP, apid);
}
EXPOWT_SYMBOW(scwp_ap_configuwe);

int scwp_ap_deconfiguwe(u32 apid)
{
	wetuwn do_ap_configuwe(SCWP_CMDW_DECONFIGUWE_AP, apid);
}
EXPOWT_SYMBOW(scwp_ap_deconfiguwe);
