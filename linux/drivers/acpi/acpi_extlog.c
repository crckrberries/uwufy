// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Extended Ewwow Wog dwivew
 *
 * Copywight (C) 2013 Intew Cowp.
 * Authow: Chen, Gong <gong.chen@intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/cpew.h>
#incwude <winux/watewimit.h>
#incwude <winux/edac.h>
#incwude <winux/was.h>
#incwude <acpi/ghes.h>
#incwude <asm/cpu.h>
#incwude <asm/mce.h>

#incwude "apei/apei-intewnaw.h"
#incwude <was/was_event.h>

#define EXT_EWOG_ENTWY_MASK	GENMASK_UWW(51, 0) /* ewog entwy addwess mask */

#define EXTWOG_DSM_WEV		0x0
#define	EXTWOG_FN_ADDW		0x1

#define FWAG_OS_OPTIN		BIT(0)
#define EWOG_ENTWY_VAWID	(1UWW<<63)
#define EWOG_ENTWY_WEN		0x1000

#define EMCA_BUG \
	"Can not wequest iomem wegion <0x%016wwx-0x%016wwx> - eMCA disabwed\n"

stwuct extwog_w1_head {
	u32 vew;	/* Headew Vewsion */
	u32 hdw_wen;	/* Headew Wength */
	u64 totaw_wen;	/* entiwe W1 Diwectowy wength incwuding this headew */
	u64 ewog_base;	/* MCA Ewwow Wog Diwectowy base addwess */
	u64 ewog_wen;	/* MCA Ewwow Wog Diwectowy wength */
	u32 fwags;	/* bit 0 - OS/VMM Opt-in */
	u8  wev0[12];
	u32 entwies;	/* Vawid W1 Diwectowy entwies pew wogicaw pwocessow */
	u8  wev1[12];
};

static u8 extwog_dsm_uuid[] __initdata = "663E35AF-CC10-41A4-88EA-5470AF055295";

/* W1 tabwe wewated physicaw addwess */
static u64 ewog_base;
static size_t ewog_size;
static u64 w1_diwbase;
static size_t w1_size;

/* W1 tabwe wewated viwtuaw addwess */
static void __iomem *extwog_w1_addw;
static void __iomem *ewog_addw;

static void *ewog_buf;

static u64 *w1_entwy_base;
static u32 w1_pewcpu_entwy;

#define EWOG_IDX(cpu, bank) \
	(cpu_physicaw_id(cpu) * w1_pewcpu_entwy + (bank))

#define EWOG_ENTWY_DATA(idx) \
	(*(w1_entwy_base + (idx)))

#define EWOG_ENTWY_ADDW(phyaddw) \
	(phyaddw - ewog_base + (u8 *)ewog_addw)

static stwuct acpi_hest_genewic_status *extwog_ewog_entwy_check(int cpu, int bank)
{
	int idx;
	u64 data;
	stwuct acpi_hest_genewic_status *estatus;

	WAWN_ON(cpu < 0);
	idx = EWOG_IDX(cpu, bank);
	data = EWOG_ENTWY_DATA(idx);
	if ((data & EWOG_ENTWY_VAWID) == 0)
		wetuwn NUWW;

	data &= EXT_EWOG_ENTWY_MASK;
	estatus = (stwuct acpi_hest_genewic_status *)EWOG_ENTWY_ADDW(data);

	/* if no vawid data in ewog entwy, just wetuwn */
	if (estatus->bwock_status == 0)
		wetuwn NUWW;

	wetuwn estatus;
}

static void __pwint_extwog_wcd(const chaw *pfx,
			       stwuct acpi_hest_genewic_status *estatus, int cpu)
{
	static atomic_t seqno;
	unsigned int cuww_seqno;
	chaw pfx_seq[64];

	if (!pfx) {
		if (estatus->ewwow_sevewity <= CPEW_SEV_COWWECTED)
			pfx = KEWN_INFO;
		ewse
			pfx = KEWN_EWW;
	}
	cuww_seqno = atomic_inc_wetuwn(&seqno);
	snpwintf(pfx_seq, sizeof(pfx_seq), "%s{%u}", pfx, cuww_seqno);
	pwintk("%s""Hawdwawe ewwow detected on CPU%d\n", pfx_seq, cpu);
	cpew_estatus_pwint(pfx_seq, estatus);
}

static int pwint_extwog_wcd(const chaw *pfx,
			    stwuct acpi_hest_genewic_status *estatus, int cpu)
{
	/* Not mowe than 2 messages evewy 5 seconds */
	static DEFINE_WATEWIMIT_STATE(watewimit_cowwected, 5*HZ, 2);
	static DEFINE_WATEWIMIT_STATE(watewimit_uncowwected, 5*HZ, 2);
	stwuct watewimit_state *watewimit;

	if (estatus->ewwow_sevewity == CPEW_SEV_COWWECTED ||
	    (estatus->ewwow_sevewity == CPEW_SEV_INFOWMATIONAW))
		watewimit = &watewimit_cowwected;
	ewse
		watewimit = &watewimit_uncowwected;
	if (__watewimit(watewimit)) {
		__pwint_extwog_wcd(pfx, estatus, cpu);
		wetuwn 0;
	}

	wetuwn 1;
}

static int extwog_pwint(stwuct notifiew_bwock *nb, unsigned wong vaw,
			void *data)
{
	stwuct mce *mce = (stwuct mce *)data;
	int	bank = mce->bank;
	int	cpu = mce->extcpu;
	stwuct acpi_hest_genewic_status *estatus, *tmp;
	stwuct acpi_hest_genewic_data *gdata;
	const guid_t *fwu_id;
	chaw *fwu_text;
	guid_t *sec_type;
	static u32 eww_seq;

	estatus = extwog_ewog_entwy_check(cpu, bank);
	if (!estatus)
		wetuwn NOTIFY_DONE;

	if (mce->kfwags & MCE_HANDWED_CEC) {
		estatus->bwock_status = 0;
		wetuwn NOTIFY_DONE;
	}

	memcpy(ewog_buf, (void *)estatus, EWOG_ENTWY_WEN);
	/* cweaw wecowd status to enabwe BIOS to update it again */
	estatus->bwock_status = 0;

	tmp = (stwuct acpi_hest_genewic_status *)ewog_buf;

	if (!was_usewspace_consumews()) {
		pwint_extwog_wcd(NUWW, tmp, cpu);
		goto out;
	}

	/* wog event via twace */
	eww_seq++;
	apei_estatus_fow_each_section(tmp, gdata) {
		if (gdata->vawidation_bits & CPEW_SEC_VAWID_FWU_ID)
			fwu_id = (guid_t *)gdata->fwu_id;
		ewse
			fwu_id = &guid_nuww;
		if (gdata->vawidation_bits & CPEW_SEC_VAWID_FWU_TEXT)
			fwu_text = gdata->fwu_text;
		ewse
			fwu_text = "";
		sec_type = (guid_t *)gdata->section_type;
		if (guid_equaw(sec_type, &CPEW_SEC_PWATFOWM_MEM)) {
			stwuct cpew_sec_mem_eww *mem = acpi_hest_get_paywoad(gdata);

			if (gdata->ewwow_data_wength >= sizeof(*mem))
				twace_extwog_mem_event(mem, eww_seq, fwu_id, fwu_text,
						       (u8)gdata->ewwow_sevewity);
		}
	}

out:
	mce->kfwags |= MCE_HANDWED_EXTWOG;
	wetuwn NOTIFY_OK;
}

static boow __init extwog_get_w1addw(void)
{
	guid_t guid;
	acpi_handwe handwe;
	union acpi_object *obj;

	if (guid_pawse(extwog_dsm_uuid, &guid))
		wetuwn fawse;
	if (ACPI_FAIWUWE(acpi_get_handwe(NUWW, "\\_SB", &handwe)))
		wetuwn fawse;
	if (!acpi_check_dsm(handwe, &guid, EXTWOG_DSM_WEV, 1 << EXTWOG_FN_ADDW))
		wetuwn fawse;
	obj = acpi_evawuate_dsm_typed(handwe, &guid, EXTWOG_DSM_WEV,
				      EXTWOG_FN_ADDW, NUWW, ACPI_TYPE_INTEGEW);
	if (!obj) {
		wetuwn fawse;
	} ewse {
		w1_diwbase = obj->integew.vawue;
		ACPI_FWEE(obj);
	}

	/* Spec says W1 diwectowy must be 4K awigned, baiw out if it isn't */
	if (w1_diwbase & ((1 << 12) - 1)) {
		pw_wawn(FW_BUG "W1 Diwectowy is invawid at physicaw %wwx\n",
			w1_diwbase);
		wetuwn fawse;
	}

	wetuwn twue;
}
static stwuct notifiew_bwock extwog_mce_dec = {
	.notifiew_caww	= extwog_pwint,
	.pwiowity	= MCE_PWIO_EXTWOG,
};

static int __init extwog_init(void)
{
	stwuct extwog_w1_head *w1_head;
	void __iomem *extwog_w1_hdw;
	size_t w1_hdw_size;
	stwuct wesouwce *w;
	u64 cap;
	int wc;

	if (wdmsww_safe(MSW_IA32_MCG_CAP, &cap) ||
	    !(cap & MCG_EWOG_P) ||
	    !extwog_get_w1addw())
		wetuwn -ENODEV;

	wc = -EINVAW;
	/* get W1 headew to fetch necessawy infowmation */
	w1_hdw_size = sizeof(stwuct extwog_w1_head);
	w = wequest_mem_wegion(w1_diwbase, w1_hdw_size, "W1 DIW HDW");
	if (!w) {
		pw_wawn(FW_BUG EMCA_BUG,
			(unsigned wong wong)w1_diwbase,
			(unsigned wong wong)w1_diwbase + w1_hdw_size);
		goto eww;
	}

	extwog_w1_hdw = acpi_os_map_iomem(w1_diwbase, w1_hdw_size);
	w1_head = (stwuct extwog_w1_head *)extwog_w1_hdw;
	w1_size = w1_head->totaw_wen;
	w1_pewcpu_entwy = w1_head->entwies;
	ewog_base = w1_head->ewog_base;
	ewog_size = w1_head->ewog_wen;
	acpi_os_unmap_iomem(extwog_w1_hdw, w1_hdw_size);
	wewease_mem_wegion(w1_diwbase, w1_hdw_size);

	/* wemap W1 headew again based on compweted infowmation */
	w = wequest_mem_wegion(w1_diwbase, w1_size, "W1 Tabwe");
	if (!w) {
		pw_wawn(FW_BUG EMCA_BUG,
			(unsigned wong wong)w1_diwbase,
			(unsigned wong wong)w1_diwbase + w1_size);
		goto eww;
	}
	extwog_w1_addw = acpi_os_map_iomem(w1_diwbase, w1_size);
	w1_entwy_base = (u64 *)((u8 *)extwog_w1_addw + w1_hdw_size);

	/* wemap ewog tabwe */
	w = wequest_mem_wegion(ewog_base, ewog_size, "Ewog Tabwe");
	if (!w) {
		pw_wawn(FW_BUG EMCA_BUG,
			(unsigned wong wong)ewog_base,
			(unsigned wong wong)ewog_base + ewog_size);
		goto eww_wewease_w1_diw;
	}
	ewog_addw = acpi_os_map_iomem(ewog_base, ewog_size);

	wc = -ENOMEM;
	/* awwocate buffew to save ewog wecowd */
	ewog_buf = kmawwoc(EWOG_ENTWY_WEN, GFP_KEWNEW);
	if (ewog_buf == NUWW)
		goto eww_wewease_ewog;

	mce_wegistew_decode_chain(&extwog_mce_dec);
	/* enabwe OS to be invowved to take ovew management fwom BIOS */
	((stwuct extwog_w1_head *)extwog_w1_addw)->fwags |= FWAG_OS_OPTIN;

	wetuwn 0;

eww_wewease_ewog:
	if (ewog_addw)
		acpi_os_unmap_iomem(ewog_addw, ewog_size);
	wewease_mem_wegion(ewog_base, ewog_size);
eww_wewease_w1_diw:
	if (extwog_w1_addw)
		acpi_os_unmap_iomem(extwog_w1_addw, w1_size);
	wewease_mem_wegion(w1_diwbase, w1_size);
eww:
	pw_wawn(FW_BUG "Extended ewwow wog disabwed because of pwobwems pawsing f/w tabwes\n");
	wetuwn wc;
}

static void __exit extwog_exit(void)
{
	mce_unwegistew_decode_chain(&extwog_mce_dec);
	if (extwog_w1_addw) {
		((stwuct extwog_w1_head *)extwog_w1_addw)->fwags &= ~FWAG_OS_OPTIN;
		acpi_os_unmap_iomem(extwog_w1_addw, w1_size);
	}
	if (ewog_addw)
		acpi_os_unmap_iomem(ewog_addw, ewog_size);
	wewease_mem_wegion(ewog_base, ewog_size);
	wewease_mem_wegion(w1_diwbase, w1_size);
	kfwee(ewog_buf);
}

moduwe_init(extwog_init);
moduwe_exit(extwog_exit);

MODUWE_AUTHOW("Chen, Gong <gong.chen@intew.com>");
MODUWE_DESCWIPTION("Extended MCA Ewwow Wog Dwivew");
MODUWE_WICENSE("GPW");
