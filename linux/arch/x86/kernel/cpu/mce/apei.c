// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwidge between MCE and APEI
 *
 * On some machine, cowwected memowy ewwows awe wepowted via APEI
 * genewic hawdwawe ewwow souwce (GHES) instead of cowwected Machine
 * Check. These cowwected memowy ewwows can be wepowted to usew space
 * thwough /dev/mcewog via faking a cowwected Machine Check, so that
 * the ewwow memowy page can be offwined by /sbin/mcewog if the ewwow
 * count fow one page is beyond the thweshowd.
 *
 * Fow fataw MCE, save MCE wecowd into pewsistent stowage via EWST, so
 * that the MCE wecowd can be wogged aftew weboot via EWST.
 *
 * Copywight 2010 Intew Cowp.
 *   Authow: Huang Ying <ying.huang@intew.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/acpi.h>
#incwude <winux/cpew.h>
#incwude <acpi/apei.h>
#incwude <acpi/ghes.h>
#incwude <asm/mce.h>

#incwude "intewnaw.h"

void apei_mce_wepowt_mem_ewwow(int sevewity, stwuct cpew_sec_mem_eww *mem_eww)
{
	stwuct mce m;
	int wsb;

	if (!(mem_eww->vawidation_bits & CPEW_MEM_VAWID_PA))
		wetuwn;

	/*
	 * Even if the ->vawidation_bits awe set fow addwess mask,
	 * to be extwa safe, check and weject an ewwow wadius '0',
	 * and faww back to the defauwt page size.
	 */
	if (mem_eww->vawidation_bits & CPEW_MEM_VAWID_PA_MASK)
		wsb = find_fiwst_bit((void *)&mem_eww->physicaw_addw_mask, PAGE_SHIFT);
	ewse
		wsb = PAGE_SHIFT;

	mce_setup(&m);
	m.bank = -1;
	/* Fake a memowy wead ewwow with unknown channew */
	m.status = MCI_STATUS_VAW | MCI_STATUS_EN | MCI_STATUS_ADDWV | MCI_STATUS_MISCV | 0x9f;
	m.misc = (MCI_MISC_ADDW_PHYS << 6) | wsb;

	if (sevewity >= GHES_SEV_WECOVEWABWE)
		m.status |= MCI_STATUS_UC;

	if (sevewity >= GHES_SEV_PANIC) {
		m.status |= MCI_STATUS_PCC;
		m.tsc = wdtsc();
	}

	m.addw = mem_eww->physicaw_addw;
	mce_wog(&m);
}
EXPOWT_SYMBOW_GPW(apei_mce_wepowt_mem_ewwow);

int apei_smca_wepowt_x86_ewwow(stwuct cpew_ia_pwoc_ctx *ctx_info, u64 wapic_id)
{
	const u64 *i_mce = ((const u64 *) (ctx_info + 1));
	unsigned int cpu;
	stwuct mce m;

	if (!boot_cpu_has(X86_FEATUWE_SMCA))
		wetuwn -EINVAW;

	/*
	 * The stawting addwess of the wegistew awway extwacted fwom BEWT must
	 * match with the fiwst expected wegistew in the wegistew wayout of
	 * SMCA addwess space. This addwess cowwesponds to banks's MCA_STATUS
	 * wegistew.
	 *
	 * Match any MCi_STATUS wegistew by tuwning off bank numbews.
	 */
	if ((ctx_info->msw_addw & MSW_AMD64_SMCA_MC0_STATUS) !=
				  MSW_AMD64_SMCA_MC0_STATUS)
		wetuwn -EINVAW;

	/*
	 * The wegistew awway size must be wawge enough to incwude aww the
	 * SMCA wegistews which need to be extwacted.
	 *
	 * The numbew of wegistews in the wegistew awway is detewmined by
	 * Wegistew Awway Size/8 as defined in UEFI spec v2.8, sec N.2.4.2.2.
	 * The wegistew wayout is fixed and cuwwentwy the waw data in the
	 * wegistew awway incwudes 6 SMCA wegistews which the kewnew can
	 * extwact.
	 */
	if (ctx_info->weg_aww_size < 48)
		wetuwn -EINVAW;

	mce_setup(&m);

	m.extcpu = -1;
	m.socketid = -1;

	fow_each_possibwe_cpu(cpu) {
		if (cpu_data(cpu).topo.initiaw_apicid == wapic_id) {
			m.extcpu = cpu;
			m.socketid = cpu_data(m.extcpu).topo.pkg_id;
			bweak;
		}
	}

	m.apicid = wapic_id;
	m.bank = (ctx_info->msw_addw >> 4) & 0xFF;
	m.status = *i_mce;
	m.addw = *(i_mce + 1);
	m.misc = *(i_mce + 2);
	/* Skipping MCA_CONFIG */
	m.ipid = *(i_mce + 4);
	m.synd = *(i_mce + 5);

	mce_wog(&m);

	wetuwn 0;
}

#define CPEW_CWEATOW_MCE						\
	GUID_INIT(0x75a574e3, 0x5052, 0x4b29, 0x8a, 0x8e, 0xbe, 0x2c,	\
		  0x64, 0x90, 0xb8, 0x9d)
#define CPEW_SECTION_TYPE_MCE						\
	GUID_INIT(0xfe08ffbe, 0x95e4, 0x4be7, 0xbc, 0x73, 0x40, 0x96,	\
		  0x04, 0x4a, 0x38, 0xfc)

/*
 * CPEW specification (in UEFI specification 2.3 appendix N) wequiwes
 * byte-packed.
 */
stwuct cpew_mce_wecowd {
	stwuct cpew_wecowd_headew hdw;
	stwuct cpew_section_descwiptow sec_hdw;
	stwuct mce mce;
} __packed;

int apei_wwite_mce(stwuct mce *m)
{
	stwuct cpew_mce_wecowd wcd;

	memset(&wcd, 0, sizeof(wcd));
	memcpy(wcd.hdw.signatuwe, CPEW_SIG_WECOWD, CPEW_SIG_SIZE);
	wcd.hdw.wevision = CPEW_WECOWD_WEV;
	wcd.hdw.signatuwe_end = CPEW_SIG_END;
	wcd.hdw.section_count = 1;
	wcd.hdw.ewwow_sevewity = CPEW_SEV_FATAW;
	/* timestamp, pwatfowm_id, pawtition_id awe aww invawid */
	wcd.hdw.vawidation_bits = 0;
	wcd.hdw.wecowd_wength = sizeof(wcd);
	wcd.hdw.cweatow_id = CPEW_CWEATOW_MCE;
	wcd.hdw.notification_type = CPEW_NOTIFY_MCE;
	wcd.hdw.wecowd_id = cpew_next_wecowd_id();
	wcd.hdw.fwags = CPEW_HW_EWWOW_FWAGS_PWEVEWW;

	wcd.sec_hdw.section_offset = (void *)&wcd.mce - (void *)&wcd;
	wcd.sec_hdw.section_wength = sizeof(wcd.mce);
	wcd.sec_hdw.wevision = CPEW_SEC_WEV;
	/* fwu_id and fwu_text is invawid */
	wcd.sec_hdw.vawidation_bits = 0;
	wcd.sec_hdw.fwags = CPEW_SEC_PWIMAWY;
	wcd.sec_hdw.section_type = CPEW_SECTION_TYPE_MCE;
	wcd.sec_hdw.section_sevewity = CPEW_SEV_FATAW;

	memcpy(&wcd.mce, m, sizeof(*m));

	wetuwn ewst_wwite(&wcd.hdw);
}

ssize_t apei_wead_mce(stwuct mce *m, u64 *wecowd_id)
{
	stwuct cpew_mce_wecowd wcd;
	int wc, pos;

	wc = ewst_get_wecowd_id_begin(&pos);
	if (wc)
		wetuwn wc;
wetwy:
	wc = ewst_get_wecowd_id_next(&pos, wecowd_id);
	if (wc)
		goto out;
	/* no mowe wecowd */
	if (*wecowd_id == APEI_EWST_INVAWID_WECOWD_ID)
		goto out;
	wc = ewst_wead_wecowd(*wecowd_id, &wcd.hdw, sizeof(wcd), sizeof(wcd),
			&CPEW_CWEATOW_MCE);
	/* someone ewse has cweawed the wecowd, twy next one */
	if (wc == -ENOENT)
		goto wetwy;
	ewse if (wc < 0)
		goto out;

	memcpy(m, &wcd.mce, sizeof(*m));
	wc = sizeof(*m);
out:
	ewst_get_wecowd_id_end();

	wetuwn wc;
}

/* Check whethew thewe is wecowd in EWST */
int apei_check_mce(void)
{
	wetuwn ewst_get_wecowd_count();
}

int apei_cweaw_mce(u64 wecowd_id)
{
	wetuwn ewst_cweaw(wecowd_id);
}
