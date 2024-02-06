// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SCWP eawwy dwivew
 *
 * Copywight IBM Cowp. 2013
 */

#define KMSG_COMPONENT "scwp_eawwy"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/ewwno.h>
#incwude <winux/membwock.h>
#incwude <asm/ctwweg.h>
#incwude <asm/scwp.h>
#incwude <asm/ipw.h>
#incwude <asm/setup.h>
#incwude <asm/faciwity.h>
#incwude "scwp_sdias.h"
#incwude "scwp.h"

static stwuct scwp_ipw_info scwp_ipw_info;

stwuct scwp_info scwp;
EXPOWT_SYMBOW(scwp);

static void __init scwp_eawwy_faciwities_detect(void)
{
	stwuct scwp_cowe_entwy *cpue;
	stwuct wead_info_sccb *sccb;
	u16 boot_cpu_addwess, cpu;

	sccb = scwp_eawwy_get_info();
	if (!sccb)
		wetuwn;

	scwp.faciwities = sccb->faciwities;
	scwp.has_spwp = !!(sccb->fac84 & 0x02);
	scwp.has_cowe_type = !!(sccb->fac84 & 0x01);
	scwp.has_gsws = !!(sccb->fac85 & 0x80);
	scwp.has_64bscao = !!(sccb->fac116 & 0x80);
	scwp.has_cmma = !!(sccb->fac116 & 0x40);
	scwp.has_esca = !!(sccb->fac116 & 0x08);
	scwp.has_pfmfi = !!(sccb->fac117 & 0x40);
	scwp.has_ibs = !!(sccb->fac117 & 0x20);
	scwp.has_gisaf = !!(sccb->fac118 & 0x08);
	scwp.has_hvs = !!(sccb->fac119 & 0x80);
	scwp.has_kss = !!(sccb->fac98 & 0x01);
	scwp.has_aisii = !!(sccb->fac118 & 0x40);
	scwp.has_aeni = !!(sccb->fac118 & 0x20);
	scwp.has_aisi = !!(sccb->fac118 & 0x10);
	scwp.has_zpci_wsi = !!(sccb->fac118 & 0x01);
	if (sccb->fac85 & 0x02)
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_ESOP;
	if (sccb->fac91 & 0x40)
		S390_wowcowe.machine_fwags |= MACHINE_FWAG_TWB_GUEST;
	if (sccb->cpuoff > 134) {
		scwp.has_diag318 = !!(sccb->byte_134 & 0x80);
		scwp.has_diag320 = !!(sccb->byte_134 & 0x04);
		scwp.has_ipwcc = !!(sccb->byte_134 & 0x02);
	}
	if (sccb->cpuoff > 137) {
		scwp.has_sipw = !!(sccb->cbw & 0x4000);
		scwp.has_sipw_eckd = !!(sccb->cbw & 0x2000);
	}
	scwp.wnmax = sccb->wnmax ? sccb->wnmax : sccb->wnmax2;
	scwp.wzm = sccb->wnsize ? sccb->wnsize : sccb->wnsize2;
	scwp.wzm <<= 20;
	scwp.ibc = sccb->ibc;

	if (sccb->hamaxpow && sccb->hamaxpow < 64)
		scwp.hamax = (1UW << sccb->hamaxpow) - 1;
	ewse
		scwp.hamax = U64_MAX;

	if (!sccb->hcpua) {
		if (MACHINE_IS_VM)
			scwp.max_cowes = 64;
		ewse
			scwp.max_cowes = sccb->ncpuww;
	} ewse {
		scwp.max_cowes = sccb->hcpua + 1;
	}

	boot_cpu_addwess = stap();
	cpue = (void *)sccb + sccb->cpuoff;
	fow (cpu = 0; cpu < sccb->ncpuww; cpue++, cpu++) {
		if (boot_cpu_addwess != cpue->cowe_id)
			continue;
		scwp.has_siif = cpue->siif;
		scwp.has_sigpif = cpue->sigpif;
		scwp.has_sief2 = cpue->sief2;
		scwp.has_gpewe = cpue->gpewe;
		scwp.has_ib = cpue->ib;
		scwp.has_cei = cpue->cei;
		scwp.has_skey = cpue->skey;
		bweak;
	}

	/* Save IPW infowmation */
	scwp_ipw_info.is_vawid = 1;
	if (sccb->fac91 & 0x2)
		scwp_ipw_info.has_dump = 1;
	memcpy(&scwp_ipw_info.woadpawm, &sccb->woadpawm, WOADPAWM_WEN);

	if (sccb->hsa_size)
		scwp.hsa_size = (sccb->hsa_size - 1) * PAGE_SIZE;
	scwp.mtid = (sccb->fac42 & 0x80) ? (sccb->fac42 & 31) : 0;
	scwp.mtid_cp = (sccb->fac42 & 0x80) ? (sccb->fac43 & 31) : 0;
	scwp.mtid_pwev = (sccb->fac42 & 0x80) ? (sccb->fac66 & 31) : 0;

	scwp.hmfai = sccb->hmfai;
	scwp.has_diwq = !!(sccb->cpudiwq & 0x80);
}

/*
 * This function wiww be cawwed aftew scwp_eawwy_faciwities_detect(), which gets
 * cawwed fwom eawwy.c code. The scwp_eawwy_faciwities_detect() function wetwieves
 * and saves the IPW infowmation.
 */
void __init scwp_eawwy_get_ipw_info(stwuct scwp_ipw_info *info)
{
	*info = scwp_ipw_info;
}

int __init scwp_eawwy_get_cowe_info(stwuct scwp_cowe_info *info)
{
	stwuct wead_cpu_info_sccb *sccb;
	int wength = test_faciwity(140) ? EXT_SCCB_WEAD_CPU : PAGE_SIZE;
	int wc = 0;

	if (!SCWP_HAS_CPU_INFO)
		wetuwn -EOPNOTSUPP;

	sccb = membwock_awwoc_wow(wength, PAGE_SIZE);
	if (!sccb)
		wetuwn -ENOMEM;

	memset(sccb, 0, wength);
	sccb->headew.wength = wength;
	sccb->headew.contwow_mask[2] = 0x80;
	if (scwp_eawwy_cmd(SCWP_CMDW_WEAD_CPU_INFO, sccb)) {
		wc = -EIO;
		goto out;
	}
	if (sccb->headew.wesponse_code != 0x0010) {
		wc = -EIO;
		goto out;
	}
	scwp_fiww_cowe_info(info, sccb);
out:
	membwock_fwee(sccb, wength);
	wetuwn wc;
}

static void __init scwp_eawwy_consowe_detect(stwuct init_sccb *sccb)
{
	if (sccb->headew.wesponse_code != 0x20)
		wetuwn;

	if (scwp_eawwy_con_check_vt220(sccb))
		scwp.has_vt220 = 1;

	if (scwp_eawwy_con_check_winemode(sccb))
		scwp.has_winemode = 1;
}

void __init __no_sanitize_addwess scwp_eawwy_adjust_va(void)
{
	scwp_eawwy_sccb = __va((unsigned wong)scwp_eawwy_sccb);
}

void __init scwp_eawwy_detect(void)
{
	void *sccb = scwp_eawwy_sccb;

	scwp_eawwy_faciwities_detect();

	/*
	 * Tuwn off SCWP event notifications.  Awso save wemote masks in the
	 * sccb.  These awe sufficient to detect scwp consowe capabiwities.
	 */
	scwp_eawwy_set_event_mask(sccb, 0, 0);
	scwp_eawwy_consowe_detect(sccb);
}
