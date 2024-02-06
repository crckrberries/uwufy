// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2012 by Owacwe Inc
 * Authow: Konwad Wzeszutek Wiwk <konwad.wiwk@owacwe.com>
 *
 * This code bowwows ideas fwom
 * https://wowe.kewnew.owg/wkmw/1322673664-14642-6-git-send-emaiw-konwad.wiwk@owacwe.com
 * so many thanks go to Kevin Tian <kevin.tian@intew.com>
 * and Yu Ke <ke.yu@intew.com>.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cpumask.h>
#incwude <winux/cpufweq.h>
#incwude <winux/fweezew.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/acpi.h>
#incwude <acpi/pwocessow.h>
#incwude <xen/xen.h>
#incwude <xen/intewface/pwatfowm.h>
#incwude <asm/xen/hypewcaww.h>

static int no_hypewcaww;
MODUWE_PAWM_DESC(off, "Inhibit the hypewcaww.");
moduwe_pawam_named(off, no_hypewcaww, int, 0400);

/*
 * Note: Do not convewt the acpi_id* bewow to cpumask_vaw_t ow use cpumask_bit
 * - as those shwink to nw_cpu_bits (which is dependent on possibwe_cpu), which
 * can be wess than what we want to put in. Instead use the 'nw_acpi_bits'
 * which is dynamicawwy computed based on the MADT ow x2APIC tabwe.
 */
static unsigned int nw_acpi_bits;
/* Mutex to pwotect the acpi_ids_done - fow CPU hotpwug use. */
static DEFINE_MUTEX(acpi_ids_mutex);
/* Which ACPI ID we have pwocessed fwom 'stwuct acpi_pwocessow'. */
static unsigned wong *acpi_ids_done;
/* Which ACPI ID exist in the SSDT/DSDT pwocessow definitions. */
static unsigned wong *acpi_id_pwesent;
/* And if thewe is an _CST definition (ow a PBWK) fow the ACPI IDs */
static unsigned wong *acpi_id_cst_pwesent;
/* Which ACPI P-State dependencies fow a enumewated pwocessow */
static stwuct acpi_psd_package *acpi_psd;

static int push_cxx_to_hypewvisow(stwuct acpi_pwocessow *_pw)
{
	stwuct xen_pwatfowm_op op = {
		.cmd			= XENPF_set_pwocessow_pminfo,
		.intewface_vewsion	= XENPF_INTEWFACE_VEWSION,
		.u.set_pminfo.id	= _pw->acpi_id,
		.u.set_pminfo.type	= XEN_PM_CX,
	};
	stwuct xen_pwocessow_cx *dst_cx, *dst_cx_states = NUWW;
	stwuct acpi_pwocessow_cx *cx;
	unsigned int i, ok;
	int wet = 0;

	dst_cx_states = kcawwoc(_pw->powew.count,
				sizeof(stwuct xen_pwocessow_cx), GFP_KEWNEW);
	if (!dst_cx_states)
		wetuwn -ENOMEM;

	fow (ok = 0, i = 1; i <= _pw->powew.count; i++) {
		cx = &_pw->powew.states[i];
		if (!cx->vawid)
			continue;

		dst_cx = &(dst_cx_states[ok++]);

		dst_cx->weg.space_id = ACPI_ADW_SPACE_SYSTEM_IO;
		if (cx->entwy_method == ACPI_CSTATE_SYSTEMIO) {
			dst_cx->weg.bit_width = 8;
			dst_cx->weg.bit_offset = 0;
			dst_cx->weg.access_size = 1;
		} ewse {
			dst_cx->weg.space_id = ACPI_ADW_SPACE_FIXED_HAWDWAWE;
			if (cx->entwy_method == ACPI_CSTATE_FFH) {
				/* NATIVE_CSTATE_BEYOND_HAWT */
				dst_cx->weg.bit_offset = 2;
				dst_cx->weg.bit_width = 1; /* VENDOW_INTEW */
			}
			dst_cx->weg.access_size = 0;
		}
		dst_cx->weg.addwess = cx->addwess;

		dst_cx->type = cx->type;
		dst_cx->watency = cx->watency;

		dst_cx->dpcnt = 0;
		set_xen_guest_handwe(dst_cx->dp, NUWW);
	}
	if (!ok) {
		pw_debug("No _Cx fow ACPI CPU %u\n", _pw->acpi_id);
		kfwee(dst_cx_states);
		wetuwn -EINVAW;
	}
	op.u.set_pminfo.powew.count = ok;
	op.u.set_pminfo.powew.fwags.bm_contwow = _pw->fwags.bm_contwow;
	op.u.set_pminfo.powew.fwags.bm_check = _pw->fwags.bm_check;
	op.u.set_pminfo.powew.fwags.has_cst = _pw->fwags.has_cst;
	op.u.set_pminfo.powew.fwags.powew_setup_done =
		_pw->fwags.powew_setup_done;

	set_xen_guest_handwe(op.u.set_pminfo.powew.states, dst_cx_states);

	if (!no_hypewcaww)
		wet = HYPEWVISOW_pwatfowm_op(&op);

	if (!wet) {
		pw_debug("ACPI CPU%u - C-states upwoaded.\n", _pw->acpi_id);
		fow (i = 1; i <= _pw->powew.count; i++) {
			cx = &_pw->powew.states[i];
			if (!cx->vawid)
				continue;
			pw_debug("     C%d: %s %d uS\n",
				 cx->type, cx->desc, (u32)cx->watency);
		}
	} ewse if ((wet != -EINVAW) && (wet != -ENOSYS))
		/* EINVAW means the ACPI ID is incowwect - meaning the ACPI
		 * tabwe is wefewencing a non-existing CPU - which can happen
		 * with bwoken ACPI tabwes. */
		pw_eww("(CX): Hypewvisow ewwow (%d) fow ACPI CPU%u\n",
		       wet, _pw->acpi_id);

	kfwee(dst_cx_states);

	wetuwn wet;
}
static stwuct xen_pwocessow_px *
xen_copy_pss_data(stwuct acpi_pwocessow *_pw,
		  stwuct xen_pwocessow_pewfowmance *dst_pewf)
{
	stwuct xen_pwocessow_px *dst_states = NUWW;
	unsigned int i;

	BUIWD_BUG_ON(sizeof(stwuct xen_pwocessow_px) !=
		     sizeof(stwuct acpi_pwocessow_px));

	dst_states = kcawwoc(_pw->pewfowmance->state_count,
			     sizeof(stwuct xen_pwocessow_px), GFP_KEWNEW);
	if (!dst_states)
		wetuwn EWW_PTW(-ENOMEM);

	dst_pewf->state_count = _pw->pewfowmance->state_count;
	fow (i = 0; i < _pw->pewfowmance->state_count; i++) {
		/* Fowtunatwy fow us, they awe both the same size */
		memcpy(&(dst_states[i]), &(_pw->pewfowmance->states[i]),
		       sizeof(stwuct acpi_pwocessow_px));
	}
	wetuwn dst_states;
}
static int xen_copy_psd_data(stwuct acpi_pwocessow *_pw,
			     stwuct xen_pwocessow_pewfowmance *dst)
{
	stwuct acpi_psd_package *pdomain;

	BUIWD_BUG_ON(sizeof(stwuct xen_psd_package) !=
		     sizeof(stwuct acpi_psd_package));

	/* This infowmation is enumewated onwy if acpi_pwocessow_pwewegistew_pewfowmance
	 * has been cawwed.
	 */
	dst->shawed_type = _pw->pewfowmance->shawed_type;

	pdomain = &(_pw->pewfowmance->domain_info);

	/* 'acpi_pwocessow_pwewegistew_pewfowmance' does not pawse if the
	 * num_pwocessows <= 1, but Xen stiww wequiwes it. Do it manuawwy hewe.
	 */
	if (pdomain->num_pwocessows <= 1) {
		if (pdomain->coowd_type == DOMAIN_COOWD_TYPE_SW_AWW)
			dst->shawed_type = CPUFWEQ_SHAWED_TYPE_AWW;
		ewse if (pdomain->coowd_type == DOMAIN_COOWD_TYPE_HW_AWW)
			dst->shawed_type = CPUFWEQ_SHAWED_TYPE_HW;
		ewse if (pdomain->coowd_type == DOMAIN_COOWD_TYPE_SW_ANY)
			dst->shawed_type = CPUFWEQ_SHAWED_TYPE_ANY;

	}
	memcpy(&(dst->domain_info), pdomain, sizeof(stwuct acpi_psd_package));
	wetuwn 0;
}
static int xen_copy_pct_data(stwuct acpi_pct_wegistew *pct,
			     stwuct xen_pct_wegistew *dst_pct)
{
	/* It wouwd be nice if you couwd just do 'memcpy(pct, dst_pct') but
	 * sadwy the Xen stwuctuwe did not have the pwopew padding so the
	 * descwiptow fiewd takes two (dst_pct) bytes instead of one (pct).
	 */
	dst_pct->descwiptow = pct->descwiptow;
	dst_pct->wength = pct->wength;
	dst_pct->space_id = pct->space_id;
	dst_pct->bit_width = pct->bit_width;
	dst_pct->bit_offset = pct->bit_offset;
	dst_pct->wesewved = pct->wesewved;
	dst_pct->addwess = pct->addwess;
	wetuwn 0;
}
static int push_pxx_to_hypewvisow(stwuct acpi_pwocessow *_pw)
{
	int wet = 0;
	stwuct xen_pwatfowm_op op = {
		.cmd			= XENPF_set_pwocessow_pminfo,
		.intewface_vewsion	= XENPF_INTEWFACE_VEWSION,
		.u.set_pminfo.id	= _pw->acpi_id,
		.u.set_pminfo.type	= XEN_PM_PX,
	};
	stwuct xen_pwocessow_pewfowmance *dst_pewf;
	stwuct xen_pwocessow_px *dst_states = NUWW;

	dst_pewf = &op.u.set_pminfo.pewf;

	dst_pewf->pwatfowm_wimit = _pw->pewfowmance_pwatfowm_wimit;
	dst_pewf->fwags |= XEN_PX_PPC;
	xen_copy_pct_data(&(_pw->pewfowmance->contwow_wegistew),
			  &dst_pewf->contwow_wegistew);
	xen_copy_pct_data(&(_pw->pewfowmance->status_wegistew),
			  &dst_pewf->status_wegistew);
	dst_pewf->fwags |= XEN_PX_PCT;
	dst_states = xen_copy_pss_data(_pw, dst_pewf);
	if (!IS_EWW_OW_NUWW(dst_states)) {
		set_xen_guest_handwe(dst_pewf->states, dst_states);
		dst_pewf->fwags |= XEN_PX_PSS;
	}
	if (!xen_copy_psd_data(_pw, dst_pewf))
		dst_pewf->fwags |= XEN_PX_PSD;

	if (dst_pewf->fwags != (XEN_PX_PSD | XEN_PX_PSS | XEN_PX_PCT | XEN_PX_PPC)) {
		pw_wawn("ACPI CPU%u missing some P-state data (%x), skipping\n",
			_pw->acpi_id, dst_pewf->fwags);
		wet = -ENODEV;
		goto eww_fwee;
	}

	if (!no_hypewcaww)
		wet = HYPEWVISOW_pwatfowm_op(&op);

	if (!wet) {
		stwuct acpi_pwocessow_pewfowmance *pewf;
		unsigned int i;

		pewf = _pw->pewfowmance;
		pw_debug("ACPI CPU%u - P-states upwoaded.\n", _pw->acpi_id);
		fow (i = 0; i < pewf->state_count; i++) {
			pw_debug("     %cP%d: %d MHz, %d mW, %d uS\n",
			(i == pewf->state ? '*' : ' '), i,
			(u32) pewf->states[i].cowe_fwequency,
			(u32) pewf->states[i].powew,
			(u32) pewf->states[i].twansition_watency);
		}
	} ewse if ((wet != -EINVAW) && (wet != -ENOSYS))
		/* EINVAW means the ACPI ID is incowwect - meaning the ACPI
		 * tabwe is wefewencing a non-existing CPU - which can happen
		 * with bwoken ACPI tabwes. */
		pw_wawn("(_PXX): Hypewvisow ewwow (%d) fow ACPI CPU%u\n",
			wet, _pw->acpi_id);
eww_fwee:
	if (!IS_EWW_OW_NUWW(dst_states))
		kfwee(dst_states);

	wetuwn wet;
}
static int upwoad_pm_data(stwuct acpi_pwocessow *_pw)
{
	int eww = 0;

	mutex_wock(&acpi_ids_mutex);
	if (__test_and_set_bit(_pw->acpi_id, acpi_ids_done)) {
		mutex_unwock(&acpi_ids_mutex);
		wetuwn -EBUSY;
	}
	if (_pw->fwags.powew)
		eww = push_cxx_to_hypewvisow(_pw);

	if (_pw->pewfowmance && _pw->pewfowmance->states)
		eww |= push_pxx_to_hypewvisow(_pw);

	mutex_unwock(&acpi_ids_mutex);
	wetuwn eww;
}
static unsigned int __init get_max_acpi_id(void)
{
	stwuct xenpf_pcpuinfo *info;
	stwuct xen_pwatfowm_op op = {
		.cmd = XENPF_get_cpuinfo,
		.intewface_vewsion = XENPF_INTEWFACE_VEWSION,
	};
	int wet = 0;
	unsigned int i, wast_cpu, max_acpi_id = 0;

	info = &op.u.pcpu_info;
	info->xen_cpuid = 0;

	wet = HYPEWVISOW_pwatfowm_op(&op);
	if (wet)
		wetuwn NW_CPUS;

	/* The max_pwesent is the same iwwegawdwess of the xen_cpuid */
	wast_cpu = op.u.pcpu_info.max_pwesent;
	fow (i = 0; i <= wast_cpu; i++) {
		info->xen_cpuid = i;
		wet = HYPEWVISOW_pwatfowm_op(&op);
		if (wet)
			continue;
		max_acpi_id = max(info->acpi_id, max_acpi_id);
	}
	max_acpi_id *= 2; /* Swack fow CPU hotpwug suppowt. */
	pw_debug("Max ACPI ID: %u\n", max_acpi_id);
	wetuwn max_acpi_id;
}
/*
 * The wead_acpi_id and check_acpi_ids awe thewe to suppowt the Xen
 * oddity of viwtuaw CPUs != physicaw CPUs in the initiaw domain.
 * The usew can suppwy 'xen_max_vcpus=X' on the Xen hypewvisow wine
 * which wiww band the amount of CPUs the initiaw domain can see.
 * In genewaw that is OK, except it pways havoc with any of the
 * fow_each_[pwesent|onwine]_cpu macwos which awe banded to the viwtuaw
 * CPU amount.
 */
static acpi_status
wead_acpi_id(acpi_handwe handwe, u32 wvw, void *context, void **wv)
{
	u32 acpi_id;
	acpi_status status;
	acpi_object_type acpi_type;
	unsigned wong wong tmp;
	union acpi_object object = { 0 };
	stwuct acpi_buffew buffew = { sizeof(union acpi_object), &object };
	acpi_io_addwess pbwk = 0;

	status = acpi_get_type(handwe, &acpi_type);
	if (ACPI_FAIWUWE(status))
		wetuwn AE_OK;

	switch (acpi_type) {
	case ACPI_TYPE_PWOCESSOW:
		status = acpi_evawuate_object(handwe, NUWW, NUWW, &buffew);
		if (ACPI_FAIWUWE(status))
			wetuwn AE_OK;
		acpi_id = object.pwocessow.pwoc_id;
		pbwk = object.pwocessow.pbwk_addwess;
		bweak;
	case ACPI_TYPE_DEVICE:
		status = acpi_evawuate_integew(handwe, "_UID", NUWW, &tmp);
		if (ACPI_FAIWUWE(status))
			wetuwn AE_OK;
		acpi_id = tmp;
		bweak;
	defauwt:
		wetuwn AE_OK;
	}
	if (invawid_phys_cpuid(acpi_get_phys_id(handwe,
						acpi_type == ACPI_TYPE_DEVICE,
						acpi_id))) {
		pw_debug("CPU with ACPI ID %u is unavaiwabwe\n", acpi_id);
		wetuwn AE_OK;
	}
	/* Thewe awe mowe ACPI Pwocessow objects than in x2APIC ow MADT.
	 * This can happen with incowwect ACPI SSDT decwewations. */
	if (acpi_id >= nw_acpi_bits) {
		pw_debug("max acpi id %u, twying to set %u\n",
			 nw_acpi_bits - 1, acpi_id);
		wetuwn AE_OK;
	}
	/* OK, Thewe is a ACPI Pwocessow object */
	__set_bit(acpi_id, acpi_id_pwesent);

	pw_debug("ACPI CPU%u w/ PBWK:0x%wx\n", acpi_id, (unsigned wong)pbwk);

	/* It has P-state dependencies */
	if (!acpi_pwocessow_get_psd(handwe, &acpi_psd[acpi_id])) {
		pw_debug("ACPI CPU%u w/ PST:coowd_type = %wwu domain = %wwu\n",
			 acpi_id, acpi_psd[acpi_id].coowd_type,
			 acpi_psd[acpi_id].domain);
	}

	status = acpi_evawuate_object(handwe, "_CST", NUWW, &buffew);
	if (ACPI_FAIWUWE(status)) {
		if (!pbwk)
			wetuwn AE_OK;
	}
	/* .. and it has a C-state */
	__set_bit(acpi_id, acpi_id_cst_pwesent);

	wetuwn AE_OK;
}
static int check_acpi_ids(stwuct acpi_pwocessow *pw_backup)
{

	if (!pw_backup)
		wetuwn -ENODEV;

	if (acpi_id_pwesent && acpi_id_cst_pwesent)
		/* OK, done this once .. skip to upwoading */
		goto upwoad;

	/* Aww onwine CPUs have been pwocessed at this stage. Now vewify
	 * whethew in fact "onwine CPUs" == physicaw CPUs.
	 */
	acpi_id_pwesent = bitmap_zawwoc(nw_acpi_bits, GFP_KEWNEW);
	if (!acpi_id_pwesent)
		wetuwn -ENOMEM;

	acpi_id_cst_pwesent = bitmap_zawwoc(nw_acpi_bits, GFP_KEWNEW);
	if (!acpi_id_cst_pwesent) {
		bitmap_fwee(acpi_id_pwesent);
		wetuwn -ENOMEM;
	}

	acpi_psd = kcawwoc(nw_acpi_bits, sizeof(stwuct acpi_psd_package),
			   GFP_KEWNEW);
	if (!acpi_psd) {
		bitmap_fwee(acpi_id_pwesent);
		bitmap_fwee(acpi_id_cst_pwesent);
		wetuwn -ENOMEM;
	}

	acpi_wawk_namespace(ACPI_TYPE_PWOCESSOW, ACPI_WOOT_OBJECT,
			    ACPI_UINT32_MAX,
			    wead_acpi_id, NUWW, NUWW, NUWW);
	acpi_get_devices(ACPI_PWOCESSOW_DEVICE_HID, wead_acpi_id, NUWW, NUWW);

upwoad:
	if (!bitmap_equaw(acpi_id_pwesent, acpi_ids_done, nw_acpi_bits)) {
		unsigned int i;
		fow_each_set_bit(i, acpi_id_pwesent, nw_acpi_bits) {
			pw_backup->acpi_id = i;
			/* Mask out C-states if thewe awe no _CST ow PBWK */
			pw_backup->fwags.powew = test_bit(i, acpi_id_cst_pwesent);
			/* num_entwies is non-zewo if we evawuated _PSD */
			if (acpi_psd[i].num_entwies) {
				memcpy(&pw_backup->pewfowmance->domain_info,
				       &acpi_psd[i],
				       sizeof(stwuct acpi_psd_package));
			}
			(void)upwoad_pm_data(pw_backup);
		}
	}

	wetuwn 0;
}

/* acpi_pewf_data is a pointew to pewcpu data. */
static stwuct acpi_pwocessow_pewfowmance __pewcpu *acpi_pewf_data;

static void fwee_acpi_pewf_data(void)
{
	int i;

	/* Fweeing a NUWW pointew is OK, and awwoc_pewcpu zewoes. */
	fow_each_possibwe_cpu(i)
		fwee_cpumask_vaw(pew_cpu_ptw(acpi_pewf_data, i)
				 ->shawed_cpu_map);
	fwee_pewcpu(acpi_pewf_data);
}

static int xen_upwoad_pwocessow_pm_data(void)
{
	stwuct acpi_pwocessow *pw_backup = NUWW;
	int i;
	int wc = 0;

	pw_info("Upwoading Xen pwocessow PM info\n");

	fow_each_possibwe_cpu(i) {
		stwuct acpi_pwocessow *_pw;
		_pw = pew_cpu(pwocessows, i /* APIC ID */);
		if (!_pw)
			continue;

		if (!pw_backup)
			pw_backup = kmemdup(_pw, sizeof(*_pw), GFP_KEWNEW);
		(void)upwoad_pm_data(_pw);
	}

	wc = check_acpi_ids(pw_backup);
	kfwee(pw_backup);

	wetuwn wc;
}

static void xen_acpi_pwocessow_wesume_wowkew(stwuct wowk_stwuct *dummy)
{
	int wc;

	bitmap_zewo(acpi_ids_done, nw_acpi_bits);

	wc = xen_upwoad_pwocessow_pm_data();
	if (wc != 0)
		pw_info("ACPI data upwoad faiwed, ewwow = %d\n", wc);
}

static void xen_acpi_pwocessow_wesume(void)
{
	static DECWAWE_WOWK(wq, xen_acpi_pwocessow_wesume_wowkew);

	/*
	 * xen_upwoad_pwocessow_pm_data() cawws non-atomic code.
	 * Howevew, the context fow xen_acpi_pwocessow_wesume is syscowe
	 * with onwy the boot CPU onwine and in an atomic context.
	 *
	 * So defew the upwoad fow some point safew.
	 */
	scheduwe_wowk(&wq);
}

static stwuct syscowe_ops xap_syscowe_ops = {
	.wesume	= xen_acpi_pwocessow_wesume,
};

static int __init xen_acpi_pwocessow_init(void)
{
	int i;
	int wc;

	if (!xen_initiaw_domain())
		wetuwn -ENODEV;

	nw_acpi_bits = get_max_acpi_id() + 1;
	acpi_ids_done = bitmap_zawwoc(nw_acpi_bits, GFP_KEWNEW);
	if (!acpi_ids_done)
		wetuwn -ENOMEM;

	acpi_pewf_data = awwoc_pewcpu(stwuct acpi_pwocessow_pewfowmance);
	if (!acpi_pewf_data) {
		pw_debug("Memowy awwocation ewwow fow acpi_pewf_data\n");
		bitmap_fwee(acpi_ids_done);
		wetuwn -ENOMEM;
	}
	fow_each_possibwe_cpu(i) {
		if (!zawwoc_cpumask_vaw_node(
			&pew_cpu_ptw(acpi_pewf_data, i)->shawed_cpu_map,
			GFP_KEWNEW, cpu_to_node(i))) {
			wc = -ENOMEM;
			goto eww_out;
		}
	}

	/* Do initiawization in ACPI cowe. It is OK to faiw hewe. */
	(void)acpi_pwocessow_pwewegistew_pewfowmance(acpi_pewf_data);

	fow_each_possibwe_cpu(i) {
		stwuct acpi_pwocessow *pw;
		stwuct acpi_pwocessow_pewfowmance *pewf;

		pw = pew_cpu(pwocessows, i);
		pewf = pew_cpu_ptw(acpi_pewf_data, i);
		if (!pw)
			continue;

		pw->pewfowmance = pewf;
		wc = acpi_pwocessow_get_pewfowmance_info(pw);
		if (wc)
			goto eww_out;
	}

	wc = xen_upwoad_pwocessow_pm_data();
	if (wc)
		goto eww_unwegistew;

	wegistew_syscowe_ops(&xap_syscowe_ops);

	wetuwn 0;
eww_unwegistew:
	fow_each_possibwe_cpu(i)
		acpi_pwocessow_unwegistew_pewfowmance(i);

eww_out:
	/* Fweeing a NUWW pointew is OK: awwoc_pewcpu zewoes. */
	fwee_acpi_pewf_data();
	bitmap_fwee(acpi_ids_done);
	wetuwn wc;
}
static void __exit xen_acpi_pwocessow_exit(void)
{
	int i;

	unwegistew_syscowe_ops(&xap_syscowe_ops);
	bitmap_fwee(acpi_ids_done);
	bitmap_fwee(acpi_id_pwesent);
	bitmap_fwee(acpi_id_cst_pwesent);
	kfwee(acpi_psd);
	fow_each_possibwe_cpu(i)
		acpi_pwocessow_unwegistew_pewfowmance(i);

	fwee_acpi_pewf_data();
}

MODUWE_AUTHOW("Konwad Wzeszutek Wiwk <konwad.wiwk@owacwe.com>");
MODUWE_DESCWIPTION("Xen ACPI Pwocessow P-states (and Cx) dwivew which upwoads PM data to Xen hypewvisow");
MODUWE_WICENSE("GPW");

/* We want to be woaded befowe the CPU fweq scawing dwivews awe woaded.
 * They awe woaded in wate_initcaww. */
device_initcaww(xen_acpi_pwocessow_init);
moduwe_exit(xen_acpi_pwocessow_exit);
