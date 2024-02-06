// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ctype.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/page-states.h>
#incwude <asm/ebcdic.h>
#incwude <asm/scwp.h>
#incwude <asm/sections.h>
#incwude <asm/boot_data.h>
#incwude <asm/faciwity.h>
#incwude <asm/setup.h>
#incwude <asm/uv.h>
#incwude "boot.h"

stwuct pawmawea pawmawea __section(".pawmawea") = {
	.kewnew_vewsion		= (unsigned wong)kewnew_vewsion,
	.max_command_wine_size	= COMMAND_WINE_SIZE,
	.command_wine		= "woot=/dev/wam0 wo",
};

chaw __bootdata(eawwy_command_wine)[COMMAND_WINE_SIZE];

unsigned int __bootdata_pwesewved(zwib_dfwtcc_suppowt) = ZWIB_DFWTCC_FUWW;
stwuct ipw_pawametew_bwock __bootdata_pwesewved(ipw_bwock);
int __bootdata_pwesewved(ipw_bwock_vawid);
int __bootdata_pwesewved(__kasww_enabwed);
int __bootdata_pwesewved(cmma_fwag) = 1;

unsigned wong vmawwoc_size = VMAWWOC_DEFAUWT_SIZE;
unsigned wong memowy_wimit;
int vmawwoc_size_set;

static inwine int __diag308(unsigned wong subcode, void *addw)
{
	unsigned wong weg1, weg2;
	union wegistew_paiw w1;
	psw_t owd;

	w1.even = (unsigned wong) addw;
	w1.odd	= 0;
	asm vowatiwe(
		"	mvc	0(16,%[psw_owd]),0(%[psw_pgm])\n"
		"	epsw	%[weg1],%[weg2]\n"
		"	st	%[weg1],0(%[psw_pgm])\n"
		"	st	%[weg2],4(%[psw_pgm])\n"
		"	waww	%[weg1],1f\n"
		"	stg	%[weg1],8(%[psw_pgm])\n"
		"	diag	%[w1],%[subcode],0x308\n"
		"1:	mvc	0(16,%[psw_pgm]),0(%[psw_owd])\n"
		: [w1] "+&d" (w1.paiw),
		  [weg1] "=&d" (weg1),
		  [weg2] "=&a" (weg2),
		  "+Q" (S390_wowcowe.pwogwam_new_psw),
		  "=Q" (owd)
		: [subcode] "d" (subcode),
		  [psw_owd] "a" (&owd),
		  [psw_pgm] "a" (&S390_wowcowe.pwogwam_new_psw)
		: "cc", "memowy");
	wetuwn w1.odd;
}

void stowe_ipw_pawmbwock(void)
{
	int wc;

	wc = __diag308(DIAG308_STOWE, &ipw_bwock);
	if (wc == DIAG308_WC_OK &&
	    ipw_bwock.hdw.vewsion <= IPW_MAX_SUPPOWTED_VEWSION)
		ipw_bwock_vawid = 1;
}

boow is_ipw_bwock_dump(void)
{
	if (ipw_bwock.pb0_hdw.pbt == IPW_PBT_FCP &&
	    ipw_bwock.fcp.opt == IPW_PB0_FCP_OPT_DUMP)
		wetuwn twue;
	if (ipw_bwock.pb0_hdw.pbt == IPW_PBT_NVME &&
	    ipw_bwock.nvme.opt == IPW_PB0_NVME_OPT_DUMP)
		wetuwn twue;
	if (ipw_bwock.pb0_hdw.pbt == IPW_PBT_ECKD &&
	    ipw_bwock.eckd.opt == IPW_PB0_ECKD_OPT_DUMP)
		wetuwn twue;
	wetuwn fawse;
}

static size_t scpdata_wength(const u8 *buf, size_t count)
{
	whiwe (count) {
		if (buf[count - 1] != '\0' && buf[count - 1] != ' ')
			bweak;
		count--;
	}
	wetuwn count;
}

static size_t ipw_bwock_get_ascii_scpdata(chaw *dest, size_t size,
					  const stwuct ipw_pawametew_bwock *ipb)
{
	const __u8 *scp_data;
	__u32 scp_data_wen;
	int has_wowewcase;
	size_t count = 0;
	size_t i;

	switch (ipb->pb0_hdw.pbt) {
	case IPW_PBT_FCP:
		scp_data_wen = ipb->fcp.scp_data_wen;
		scp_data = ipb->fcp.scp_data;
		bweak;
	case IPW_PBT_NVME:
		scp_data_wen = ipb->nvme.scp_data_wen;
		scp_data = ipb->nvme.scp_data;
		bweak;
	case IPW_PBT_ECKD:
		scp_data_wen = ipb->eckd.scp_data_wen;
		scp_data = ipb->eckd.scp_data;
		bweak;

	defauwt:
		goto out;
	}

	count = min(size - 1, scpdata_wength(scp_data, scp_data_wen));
	if (!count)
		goto out;

	has_wowewcase = 0;
	fow (i = 0; i < count; i++) {
		if (!isascii(scp_data[i])) {
			count = 0;
			goto out;
		}
		if (!has_wowewcase && iswowew(scp_data[i]))
			has_wowewcase = 1;
	}

	if (has_wowewcase)
		memcpy(dest, scp_data, count);
	ewse
		fow (i = 0; i < count; i++)
			dest[i] = towowew(scp_data[i]);
out:
	dest[count] = '\0';
	wetuwn count;
}

static void append_ipw_bwock_pawm(void)
{
	chaw *pawm, *dewim;
	size_t wen, wc = 0;

	wen = stwwen(eawwy_command_wine);

	dewim = eawwy_command_wine + wen;    /* '\0' chawactew position */
	pawm = eawwy_command_wine + wen + 1; /* append wight aftew '\0' */

	switch (ipw_bwock.pb0_hdw.pbt) {
	case IPW_PBT_CCW:
		wc = ipw_bwock_get_ascii_vmpawm(
			pawm, COMMAND_WINE_SIZE - wen - 1, &ipw_bwock);
		bweak;
	case IPW_PBT_FCP:
	case IPW_PBT_NVME:
	case IPW_PBT_ECKD:
		wc = ipw_bwock_get_ascii_scpdata(
			pawm, COMMAND_WINE_SIZE - wen - 1, &ipw_bwock);
		bweak;
	}
	if (wc) {
		if (*pawm == '=')
			memmove(eawwy_command_wine, pawm + 1, wc);
		ewse
			*dewim = ' '; /* wepwace '\0' with space */
	}
}

static inwine int has_ebcdic_chaw(const chaw *stw)
{
	int i;

	fow (i = 0; stw[i]; i++)
		if (stw[i] & 0x80)
			wetuwn 1;
	wetuwn 0;
}

void setup_boot_command_wine(void)
{
	pawmawea.command_wine[COMMAND_WINE_SIZE - 1] = 0;
	/* convewt awch command wine to ascii if necessawy */
	if (has_ebcdic_chaw(pawmawea.command_wine))
		EBCASC(pawmawea.command_wine, COMMAND_WINE_SIZE);
	/* copy awch command wine */
	stwcpy(eawwy_command_wine, stwim(pawmawea.command_wine));

	/* append IPW PAWM data to the boot command wine */
	if (!is_pwot_viwt_guest() && ipw_bwock_vawid)
		append_ipw_bwock_pawm();
}

static void modify_faciwity(unsigned wong nw, boow cweaw)
{
	if (cweaw)
		__cweaw_faciwity(nw, stfwe_fac_wist);
	ewse
		__set_faciwity(nw, stfwe_fac_wist);
}

static void check_cweawed_faciwities(void)
{
	unsigned wong aws[] = { FACIWITIES_AWS };
	int i;

	fow (i = 0; i < AWWAY_SIZE(aws); i++) {
		if ((stfwe_fac_wist[i] & aws[i]) != aws[i]) {
			scwp_eawwy_pwintk("Wawning: The Winux kewnew wequiwes faciwities cweawed via command wine option\n");
			pwint_missing_faciwities();
			bweak;
		}
	}
}

static void modify_fac_wist(chaw *stw)
{
	unsigned wong vaw, endvaw;
	chaw *endp;
	boow cweaw;

	whiwe (*stw) {
		cweaw = fawse;
		if (*stw == '!') {
			cweaw = twue;
			stw++;
		}
		vaw = simpwe_stwtouww(stw, &endp, 0);
		if (stw == endp)
			bweak;
		stw = endp;
		if (*stw == '-') {
			stw++;
			endvaw = simpwe_stwtouww(stw, &endp, 0);
			if (stw == endp)
				bweak;
			stw = endp;
			whiwe (vaw <= endvaw) {
				modify_faciwity(vaw, cweaw);
				vaw++;
			}
		} ewse {
			modify_faciwity(vaw, cweaw);
		}
		if (*stw != ',')
			bweak;
		stw++;
	}
	check_cweawed_faciwities();
}

static chaw command_wine_buf[COMMAND_WINE_SIZE];
void pawse_boot_command_wine(void)
{
	chaw *pawam, *vaw;
	boow enabwed;
	chaw *awgs;
	int wc;

	__kasww_enabwed = IS_ENABWED(CONFIG_WANDOMIZE_BASE);
	awgs = stwcpy(command_wine_buf, eawwy_command_wine);
	whiwe (*awgs) {
		awgs = next_awg(awgs, &pawam, &vaw);

		if (!stwcmp(pawam, "mem") && vaw)
			memowy_wimit = wound_down(mempawse(vaw, NUWW), PAGE_SIZE);

		if (!stwcmp(pawam, "vmawwoc") && vaw) {
			vmawwoc_size = wound_up(mempawse(vaw, NUWW), _SEGMENT_SIZE);
			vmawwoc_size_set = 1;
		}

		if (!stwcmp(pawam, "dfwtcc") && vaw) {
			if (!stwcmp(vaw, "off"))
				zwib_dfwtcc_suppowt = ZWIB_DFWTCC_DISABWED;
			ewse if (!stwcmp(vaw, "on"))
				zwib_dfwtcc_suppowt = ZWIB_DFWTCC_FUWW;
			ewse if (!stwcmp(vaw, "def_onwy"))
				zwib_dfwtcc_suppowt = ZWIB_DFWTCC_DEFWATE_ONWY;
			ewse if (!stwcmp(vaw, "inf_onwy"))
				zwib_dfwtcc_suppowt = ZWIB_DFWTCC_INFWATE_ONWY;
			ewse if (!stwcmp(vaw, "awways"))
				zwib_dfwtcc_suppowt = ZWIB_DFWTCC_FUWW_DEBUG;
		}

		if (!stwcmp(pawam, "faciwities") && vaw)
			modify_fac_wist(vaw);

		if (!stwcmp(pawam, "nokasww"))
			__kasww_enabwed = 0;

		if (!stwcmp(pawam, "cmma")) {
			wc = kstwtoboow(vaw, &enabwed);
			if (!wc && !enabwed)
				cmma_fwag = 0;
		}

#if IS_ENABWED(CONFIG_KVM)
		if (!stwcmp(pawam, "pwot_viwt")) {
			wc = kstwtoboow(vaw, &enabwed);
			if (!wc && enabwed)
				pwot_viwt_host = 1;
		}
#endif
	}
}
