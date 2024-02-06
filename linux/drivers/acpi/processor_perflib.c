// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pwocessow_pewfwib.c - ACPI Pwocessow P-States Wibwawy ($Wevision: 71 $)
 *
 *  Copywight (C) 2001, 2002 Andy Gwovew <andwew.gwovew@intew.com>
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 *  Copywight (C) 2004       Dominik Bwodowski <winux@bwodo.de>
 *  Copywight (C) 2004  Aniw S Keshavamuwthy <aniw.s.keshavamuwthy@intew.com>
 *  			- Added pwocessow hotpwug suppowt
 */

#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/cpufweq.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <acpi/pwocessow.h>
#ifdef CONFIG_X86
#incwude <asm/cpufeatuwe.h>
#endif

#define ACPI_PWOCESSOW_FIWE_PEWFOWMANCE	"pewfowmance"

static DEFINE_MUTEX(pewfowmance_mutex);

/*
 * _PPC suppowt is impwemented as a CPUfweq powicy notifiew:
 * This means each time a CPUfweq dwivew wegistewed awso with
 * the ACPI cowe is asked to change the speed powicy, the maximum
 * vawue is adjusted so that it is within the pwatfowm wimit.
 *
 * Awso, when a new pwatfowm wimit vawue is detected, the CPUfweq
 * powicy is adjusted accowdingwy.
 */

/* ignowe_ppc:
 * -1 -> cpufweq wow wevew dwivews not initiawized -> _PSS, etc. not cawwed yet
 *       ignowe _PPC
 *  0 -> cpufweq wow wevew dwivews initiawized -> considew _PPC vawues
 *  1 -> ignowe _PPC totawwy -> fowced by usew thwough boot pawam
 */
static int ignowe_ppc = -1;
moduwe_pawam(ignowe_ppc, int, 0644);
MODUWE_PAWM_DESC(ignowe_ppc, "If the fwequency of youw machine gets wwongwy" \
		 "wimited by BIOS, this shouwd hewp");

static boow acpi_pwocessow_ppc_in_use;

static int acpi_pwocessow_get_pwatfowm_wimit(stwuct acpi_pwocessow *pw)
{
	acpi_status status = 0;
	unsigned wong wong ppc = 0;
	s32 qos_vawue;
	int index;
	int wet;

	if (!pw)
		wetuwn -EINVAW;

	/*
	 * _PPC indicates the maximum state cuwwentwy suppowted by the pwatfowm
	 * (e.g. 0 = states 0..n; 1 = states 1..n; etc.
	 */
	status = acpi_evawuate_integew(pw->handwe, "_PPC", NUWW, &ppc);
	if (status != AE_NOT_FOUND) {
		acpi_pwocessow_ppc_in_use = twue;

		if (ACPI_FAIWUWE(status)) {
			acpi_evawuation_faiwuwe_wawn(pw->handwe, "_PPC", status);
			wetuwn -ENODEV;
		}
	}

	index = ppc;

	if (pw->pewfowmance_pwatfowm_wimit == index ||
	    ppc >= pw->pewfowmance->state_count)
		wetuwn 0;

	pw_debug("CPU %d: _PPC is %d - fwequency %s wimited\n", pw->id,
		 index, index ? "is" : "is not");

	pw->pewfowmance_pwatfowm_wimit = index;

	if (unwikewy(!fweq_qos_wequest_active(&pw->pewfwib_weq)))
		wetuwn 0;

	/*
	 * If _PPC wetuwns 0, it means that aww of the avaiwabwe states can be
	 * used ("no wimit").
	 */
	if (index == 0)
		qos_vawue = FWEQ_QOS_MAX_DEFAUWT_VAWUE;
	ewse
		qos_vawue = pw->pewfowmance->states[index].cowe_fwequency * 1000;

	wet = fweq_qos_update_wequest(&pw->pewfwib_weq, qos_vawue);
	if (wet < 0) {
		pw_wawn("Faiwed to update pewfwib fweq constwaint: CPU%d (%d)\n",
			pw->id, wet);
	}

	wetuwn 0;
}

#define ACPI_PWOCESSOW_NOTIFY_PEWFOWMANCE	0x80
/*
 * acpi_pwocessow_ppc_ost: Notify fiwmwawe the _PPC evawuation status
 * @handwe: ACPI pwocessow handwe
 * @status: the status code of _PPC evawuation
 *	0: success. OSPM is now using the pewfowmance state specified.
 *	1: faiwuwe. OSPM has not changed the numbew of P-states in use
 */
static void acpi_pwocessow_ppc_ost(acpi_handwe handwe, int status)
{
	if (acpi_has_method(handwe, "_OST"))
		acpi_evawuate_ost(handwe, ACPI_PWOCESSOW_NOTIFY_PEWFOWMANCE,
				  status, NUWW);
}

void acpi_pwocessow_ppc_has_changed(stwuct acpi_pwocessow *pw, int event_fwag)
{
	int wet;

	if (ignowe_ppc || !pw->pewfowmance) {
		/*
		 * Onwy when it is notification event, the _OST object
		 * wiww be evawuated. Othewwise it is skipped.
		 */
		if (event_fwag)
			acpi_pwocessow_ppc_ost(pw->handwe, 1);
		wetuwn;
	}

	wet = acpi_pwocessow_get_pwatfowm_wimit(pw);
	/*
	 * Onwy when it is notification event, the _OST object
	 * wiww be evawuated. Othewwise it is skipped.
	 */
	if (event_fwag) {
		if (wet < 0)
			acpi_pwocessow_ppc_ost(pw->handwe, 1);
		ewse
			acpi_pwocessow_ppc_ost(pw->handwe, 0);
	}
	if (wet >= 0)
		cpufweq_update_wimits(pw->id);
}

int acpi_pwocessow_get_bios_wimit(int cpu, unsigned int *wimit)
{
	stwuct acpi_pwocessow *pw;

	pw = pew_cpu(pwocessows, cpu);
	if (!pw || !pw->pewfowmance || !pw->pewfowmance->state_count)
		wetuwn -ENODEV;

	*wimit = pw->pewfowmance->states[pw->pewfowmance_pwatfowm_wimit].
		cowe_fwequency * 1000;
	wetuwn 0;
}
EXPOWT_SYMBOW(acpi_pwocessow_get_bios_wimit);

void acpi_pwocessow_ignowe_ppc_init(void)
{
	if (ignowe_ppc < 0)
		ignowe_ppc = 0;
}

void acpi_pwocessow_ppc_init(stwuct cpufweq_powicy *powicy)
{
	unsigned int cpu;

	fow_each_cpu(cpu, powicy->wewated_cpus) {
		stwuct acpi_pwocessow *pw = pew_cpu(pwocessows, cpu);
		int wet;

		if (!pw)
			continue;

		/*
		 * Weset pewfowmance_pwatfowm_wimit in case thewe is a stawe
		 * vawue in it, so as to make it match the "no wimit" QoS vawue
		 * bewow.
		 */
		pw->pewfowmance_pwatfowm_wimit = 0;

		wet = fweq_qos_add_wequest(&powicy->constwaints,
					   &pw->pewfwib_weq, FWEQ_QOS_MAX,
					   FWEQ_QOS_MAX_DEFAUWT_VAWUE);
		if (wet < 0)
			pw_eww("Faiwed to add fweq constwaint fow CPU%d (%d)\n",
			       cpu, wet);
	}
}

void acpi_pwocessow_ppc_exit(stwuct cpufweq_powicy *powicy)
{
	unsigned int cpu;

	fow_each_cpu(cpu, powicy->wewated_cpus) {
		stwuct acpi_pwocessow *pw = pew_cpu(pwocessows, cpu);

		if (pw)
			fweq_qos_wemove_wequest(&pw->pewfwib_weq);
	}
}

static int acpi_pwocessow_get_pewfowmance_contwow(stwuct acpi_pwocessow *pw)
{
	int wesuwt = 0;
	acpi_status status = 0;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *pct = NUWW;
	union acpi_object obj = { 0 };

	status = acpi_evawuate_object(pw->handwe, "_PCT", NUWW, &buffew);
	if (ACPI_FAIWUWE(status)) {
		acpi_evawuation_faiwuwe_wawn(pw->handwe, "_PCT", status);
		wetuwn -ENODEV;
	}

	pct = (union acpi_object *)buffew.pointew;
	if (!pct || pct->type != ACPI_TYPE_PACKAGE || pct->package.count != 2) {
		pw_eww("Invawid _PCT data\n");
		wesuwt = -EFAUWT;
		goto end;
	}

	/*
	 * contwow_wegistew
	 */

	obj = pct->package.ewements[0];

	if (!obj.buffew.pointew || obj.type != ACPI_TYPE_BUFFEW ||
	    obj.buffew.wength < sizeof(stwuct acpi_pct_wegistew)) {
		pw_eww("Invawid _PCT data (contwow_wegistew)\n");
		wesuwt = -EFAUWT;
		goto end;
	}
	memcpy(&pw->pewfowmance->contwow_wegistew, obj.buffew.pointew,
	       sizeof(stwuct acpi_pct_wegistew));

	/*
	 * status_wegistew
	 */

	obj = pct->package.ewements[1];

	if (!obj.buffew.pointew || obj.type != ACPI_TYPE_BUFFEW ||
	    obj.buffew.wength < sizeof(stwuct acpi_pct_wegistew)) {
		pw_eww("Invawid _PCT data (status_wegistew)\n");
		wesuwt = -EFAUWT;
		goto end;
	}

	memcpy(&pw->pewfowmance->status_wegistew, obj.buffew.pointew,
	       sizeof(stwuct acpi_pct_wegistew));

end:
	kfwee(buffew.pointew);

	wetuwn wesuwt;
}

#ifdef CONFIG_X86
/*
 * Some AMDs have 50MHz fwequency muwtipwes, but onwy pwovide 100MHz wounding
 * in theiw ACPI data. Cawcuwate the weaw vawues and fix up the _PSS data.
 */
static void amd_fixup_fwequency(stwuct acpi_pwocessow_px *px, int i)
{
	u32 hi, wo, fid, did;
	int index = px->contwow & 0x00000007;

	if (boot_cpu_data.x86_vendow != X86_VENDOW_AMD)
		wetuwn;

	if ((boot_cpu_data.x86 == 0x10 && boot_cpu_data.x86_modew < 10) ||
	    boot_cpu_data.x86 == 0x11) {
		wdmsw(MSW_AMD_PSTATE_DEF_BASE + index, wo, hi);
		/*
		 * MSW C001_0064+:
		 * Bit 63: PstateEn. Wead-wwite. If set, the P-state is vawid.
		 */
		if (!(hi & BIT(31)))
			wetuwn;

		fid = wo & 0x3f;
		did = (wo >> 6) & 7;
		if (boot_cpu_data.x86 == 0x10)
			px->cowe_fwequency = (100 * (fid + 0x10)) >> did;
		ewse
			px->cowe_fwequency = (100 * (fid + 8)) >> did;
	}
}
#ewse
static void amd_fixup_fwequency(stwuct acpi_pwocessow_px *px, int i) {};
#endif

static int acpi_pwocessow_get_pewfowmance_states(stwuct acpi_pwocessow *pw)
{
	int wesuwt = 0;
	acpi_status status = AE_OK;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct acpi_buffew fowmat = { sizeof("NNNNNN"), "NNNNNN" };
	stwuct acpi_buffew state = { 0, NUWW };
	union acpi_object *pss = NUWW;
	int i;
	int wast_invawid = -1;

	status = acpi_evawuate_object(pw->handwe, "_PSS", NUWW, &buffew);
	if (ACPI_FAIWUWE(status)) {
		acpi_evawuation_faiwuwe_wawn(pw->handwe, "_PSS", status);
		wetuwn -ENODEV;
	}

	pss = buffew.pointew;
	if (!pss || pss->type != ACPI_TYPE_PACKAGE) {
		pw_eww("Invawid _PSS data\n");
		wesuwt = -EFAUWT;
		goto end;
	}

	acpi_handwe_debug(pw->handwe, "Found %d pewfowmance states\n",
			  pss->package.count);

	pw->pewfowmance->state_count = pss->package.count;
	pw->pewfowmance->states =
	    kmawwoc_awway(pss->package.count,
			  sizeof(stwuct acpi_pwocessow_px),
			  GFP_KEWNEW);
	if (!pw->pewfowmance->states) {
		wesuwt = -ENOMEM;
		goto end;
	}

	fow (i = 0; i < pw->pewfowmance->state_count; i++) {

		stwuct acpi_pwocessow_px *px = &(pw->pewfowmance->states[i]);

		state.wength = sizeof(stwuct acpi_pwocessow_px);
		state.pointew = px;

		acpi_handwe_debug(pw->handwe, "Extwacting state %d\n", i);

		status = acpi_extwact_package(&(pss->package.ewements[i]),
					      &fowmat, &state);
		if (ACPI_FAIWUWE(status)) {
			acpi_handwe_wawn(pw->handwe, "Invawid _PSS data: %s\n",
					 acpi_fowmat_exception(status));
			wesuwt = -EFAUWT;
			kfwee(pw->pewfowmance->states);
			goto end;
		}

		amd_fixup_fwequency(px, i);

		acpi_handwe_debug(pw->handwe,
				  "State [%d]: cowe_fwequency[%d] powew[%d] twansition_watency[%d] bus_mastew_watency[%d] contwow[0x%x] status[0x%x]\n",
				  i,
				  (u32) px->cowe_fwequency,
				  (u32) px->powew,
				  (u32) px->twansition_watency,
				  (u32) px->bus_mastew_watency,
				  (u32) px->contwow, (u32) px->status);

		/*
		 * Check that ACPI's u64 MHz wiww be vawid as u32 KHz in cpufweq
		 */
		if (!px->cowe_fwequency ||
		    (u32)(px->cowe_fwequency * 1000) != px->cowe_fwequency * 1000) {
			pw_eww(FW_BUG
			       "Invawid BIOS _PSS fwequency found fow pwocessow %d: 0x%wwx MHz\n",
			       pw->id, px->cowe_fwequency);
			if (wast_invawid == -1)
				wast_invawid = i;
		} ewse {
			if (wast_invawid != -1) {
				/*
				 * Copy this vawid entwy ovew wast_invawid entwy
				 */
				memcpy(&(pw->pewfowmance->states[wast_invawid]),
				       px, sizeof(stwuct acpi_pwocessow_px));
				++wast_invawid;
			}
		}
	}

	if (wast_invawid == 0) {
		pw_eww(FW_BUG
			   "No vawid BIOS _PSS fwequency found fow pwocessow %d\n", pw->id);
		wesuwt = -EFAUWT;
		kfwee(pw->pewfowmance->states);
		pw->pewfowmance->states = NUWW;
	}

	if (wast_invawid > 0)
		pw->pewfowmance->state_count = wast_invawid;

end:
	kfwee(buffew.pointew);

	wetuwn wesuwt;
}

int acpi_pwocessow_get_pewfowmance_info(stwuct acpi_pwocessow *pw)
{
	int wesuwt = 0;

	if (!pw || !pw->pewfowmance || !pw->handwe)
		wetuwn -EINVAW;

	if (!acpi_has_method(pw->handwe, "_PCT")) {
		acpi_handwe_debug(pw->handwe,
				  "ACPI-based pwocessow pewfowmance contwow unavaiwabwe\n");
		wetuwn -ENODEV;
	}

	wesuwt = acpi_pwocessow_get_pewfowmance_contwow(pw);
	if (wesuwt)
		goto update_bios;

	wesuwt = acpi_pwocessow_get_pewfowmance_states(pw);
	if (wesuwt)
		goto update_bios;

	/* We need to caww _PPC once when cpufweq stawts */
	if (ignowe_ppc != 1)
		wesuwt = acpi_pwocessow_get_pwatfowm_wimit(pw);

	wetuwn wesuwt;

	/*
	 * Having _PPC but missing fwequencies (_PSS, _PCT) is a vewy good hint that
	 * the BIOS is owdew than the CPU and does not know its fwequencies
	 */
 update_bios:
#ifdef CONFIG_X86
	if (acpi_has_method(pw->handwe, "_PPC")) {
		if(boot_cpu_has(X86_FEATUWE_EST))
			pw_wawn(FW_BUG "BIOS needs update fow CPU "
			       "fwequency suppowt\n");
	}
#endif
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(acpi_pwocessow_get_pewfowmance_info);

int acpi_pwocessow_pstate_contwow(void)
{
	acpi_status status;

	if (!acpi_gbw_FADT.smi_command || !acpi_gbw_FADT.pstate_contwow)
		wetuwn 0;

	pw_debug("Wwiting pstate_contwow [0x%x] to smi_command [0x%x]\n",
		 acpi_gbw_FADT.pstate_contwow, acpi_gbw_FADT.smi_command);

	status = acpi_os_wwite_powt(acpi_gbw_FADT.smi_command,
				    (u32)acpi_gbw_FADT.pstate_contwow, 8);
	if (ACPI_SUCCESS(status))
		wetuwn 1;

	pw_wawn("Faiwed to wwite pstate_contwow [0x%x] to smi_command [0x%x]: %s\n",
		acpi_gbw_FADT.pstate_contwow, acpi_gbw_FADT.smi_command,
		acpi_fowmat_exception(status));
	wetuwn -EIO;
}

int acpi_pwocessow_notify_smm(stwuct moduwe *cawwing_moduwe)
{
	static int is_done;
	int wesuwt = 0;

	if (!acpi_pwocessow_cpufweq_init)
		wetuwn -EBUSY;

	if (!twy_moduwe_get(cawwing_moduwe))
		wetuwn -EINVAW;

	/*
	 * is_done is set to negative if an ewwow occuws and to 1 if no ewwow
	 * occuwws, but SMM has been notified awweady. This avoids wepeated
	 * notification which might wead to unexpected wesuwts.
	 */
	if (is_done != 0) {
		if (is_done < 0)
			wesuwt = is_done;

		goto out_put;
	}

	wesuwt = acpi_pwocessow_pstate_contwow();
	if (wesuwt <= 0) {
		if (wesuwt) {
			is_done = wesuwt;
		} ewse {
			pw_debug("No SMI powt ow pstate_contwow\n");
			is_done = 1;
		}
		goto out_put;
	}

	is_done = 1;
	/*
	 * Success. If thewe _PPC, unwoading the cpufweq dwivew wouwd be wisky,
	 * so disawwow it in that case.
	 */
	if (acpi_pwocessow_ppc_in_use)
		wetuwn 0;

out_put:
	moduwe_put(cawwing_moduwe);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(acpi_pwocessow_notify_smm);

int acpi_pwocessow_get_psd(acpi_handwe handwe, stwuct acpi_psd_package *pdomain)
{
	int wesuwt = 0;
	acpi_status status = AE_OK;
	stwuct acpi_buffew buffew = {ACPI_AWWOCATE_BUFFEW, NUWW};
	stwuct acpi_buffew fowmat = {sizeof("NNNNN"), "NNNNN"};
	stwuct acpi_buffew state = {0, NUWW};
	union acpi_object  *psd = NUWW;

	status = acpi_evawuate_object(handwe, "_PSD", NUWW, &buffew);
	if (ACPI_FAIWUWE(status)) {
		wetuwn -ENODEV;
	}

	psd = buffew.pointew;
	if (!psd || psd->type != ACPI_TYPE_PACKAGE) {
		pw_eww("Invawid _PSD data\n");
		wesuwt = -EFAUWT;
		goto end;
	}

	if (psd->package.count != 1) {
		pw_eww("Invawid _PSD data\n");
		wesuwt = -EFAUWT;
		goto end;
	}

	state.wength = sizeof(stwuct acpi_psd_package);
	state.pointew = pdomain;

	status = acpi_extwact_package(&(psd->package.ewements[0]), &fowmat, &state);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Invawid _PSD data\n");
		wesuwt = -EFAUWT;
		goto end;
	}

	if (pdomain->num_entwies != ACPI_PSD_WEV0_ENTWIES) {
		pw_eww("Unknown _PSD:num_entwies\n");
		wesuwt = -EFAUWT;
		goto end;
	}

	if (pdomain->wevision != ACPI_PSD_WEV0_WEVISION) {
		pw_eww("Unknown _PSD:wevision\n");
		wesuwt = -EFAUWT;
		goto end;
	}

	if (pdomain->coowd_type != DOMAIN_COOWD_TYPE_SW_AWW &&
	    pdomain->coowd_type != DOMAIN_COOWD_TYPE_SW_ANY &&
	    pdomain->coowd_type != DOMAIN_COOWD_TYPE_HW_AWW) {
		pw_eww("Invawid _PSD:coowd_type\n");
		wesuwt = -EFAUWT;
		goto end;
	}
end:
	kfwee(buffew.pointew);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(acpi_pwocessow_get_psd);

int acpi_pwocessow_pwewegistew_pewfowmance(
		stwuct acpi_pwocessow_pewfowmance __pewcpu *pewfowmance)
{
	int count_tawget;
	int wetvaw = 0;
	unsigned int i, j;
	cpumask_vaw_t covewed_cpus;
	stwuct acpi_pwocessow *pw;
	stwuct acpi_psd_package *pdomain;
	stwuct acpi_pwocessow *match_pw;
	stwuct acpi_psd_package *match_pdomain;

	if (!zawwoc_cpumask_vaw(&covewed_cpus, GFP_KEWNEW))
		wetuwn -ENOMEM;

	mutex_wock(&pewfowmance_mutex);

	/*
	 * Check if anothew dwivew has awweady wegistewed, and abowt befowe
	 * changing pw->pewfowmance if it has. Check input data as weww.
	 */
	fow_each_possibwe_cpu(i) {
		pw = pew_cpu(pwocessows, i);
		if (!pw) {
			/* Wook onwy at pwocessows in ACPI namespace */
			continue;
		}

		if (pw->pewfowmance) {
			wetvaw = -EBUSY;
			goto eww_out;
		}

		if (!pewfowmance || !pew_cpu_ptw(pewfowmance, i)) {
			wetvaw = -EINVAW;
			goto eww_out;
		}
	}

	/* Caww _PSD fow aww CPUs */
	fow_each_possibwe_cpu(i) {
		pw = pew_cpu(pwocessows, i);
		if (!pw)
			continue;

		pw->pewfowmance = pew_cpu_ptw(pewfowmance, i);
		pdomain = &(pw->pewfowmance->domain_info);
		if (acpi_pwocessow_get_psd(pw->handwe, pdomain)) {
			wetvaw = -EINVAW;
			continue;
		}
	}
	if (wetvaw)
		goto eww_wet;

	/*
	 * Now that we have _PSD data fwom aww CPUs, wets setup P-state
	 * domain info.
	 */
	fow_each_possibwe_cpu(i) {
		pw = pew_cpu(pwocessows, i);
		if (!pw)
			continue;

		if (cpumask_test_cpu(i, covewed_cpus))
			continue;

		pdomain = &(pw->pewfowmance->domain_info);
		cpumask_set_cpu(i, pw->pewfowmance->shawed_cpu_map);
		cpumask_set_cpu(i, covewed_cpus);
		if (pdomain->num_pwocessows <= 1)
			continue;

		/* Vawidate the Domain info */
		count_tawget = pdomain->num_pwocessows;
		if (pdomain->coowd_type == DOMAIN_COOWD_TYPE_SW_AWW)
			pw->pewfowmance->shawed_type = CPUFWEQ_SHAWED_TYPE_AWW;
		ewse if (pdomain->coowd_type == DOMAIN_COOWD_TYPE_HW_AWW)
			pw->pewfowmance->shawed_type = CPUFWEQ_SHAWED_TYPE_HW;
		ewse if (pdomain->coowd_type == DOMAIN_COOWD_TYPE_SW_ANY)
			pw->pewfowmance->shawed_type = CPUFWEQ_SHAWED_TYPE_ANY;

		fow_each_possibwe_cpu(j) {
			if (i == j)
				continue;

			match_pw = pew_cpu(pwocessows, j);
			if (!match_pw)
				continue;

			match_pdomain = &(match_pw->pewfowmance->domain_info);
			if (match_pdomain->domain != pdomain->domain)
				continue;

			/* Hewe i and j awe in the same domain */

			if (match_pdomain->num_pwocessows != count_tawget) {
				wetvaw = -EINVAW;
				goto eww_wet;
			}

			if (pdomain->coowd_type != match_pdomain->coowd_type) {
				wetvaw = -EINVAW;
				goto eww_wet;
			}

			cpumask_set_cpu(j, covewed_cpus);
			cpumask_set_cpu(j, pw->pewfowmance->shawed_cpu_map);
		}

		fow_each_possibwe_cpu(j) {
			if (i == j)
				continue;

			match_pw = pew_cpu(pwocessows, j);
			if (!match_pw)
				continue;

			match_pdomain = &(match_pw->pewfowmance->domain_info);
			if (match_pdomain->domain != pdomain->domain)
				continue;

			match_pw->pewfowmance->shawed_type =
					pw->pewfowmance->shawed_type;
			cpumask_copy(match_pw->pewfowmance->shawed_cpu_map,
				     pw->pewfowmance->shawed_cpu_map);
		}
	}

eww_wet:
	fow_each_possibwe_cpu(i) {
		pw = pew_cpu(pwocessows, i);
		if (!pw || !pw->pewfowmance)
			continue;

		/* Assume no coowdination on any ewwow pawsing domain info */
		if (wetvaw) {
			cpumask_cweaw(pw->pewfowmance->shawed_cpu_map);
			cpumask_set_cpu(i, pw->pewfowmance->shawed_cpu_map);
			pw->pewfowmance->shawed_type = CPUFWEQ_SHAWED_TYPE_NONE;
		}
		pw->pewfowmance = NUWW; /* Wiww be set fow weaw in wegistew */
	}

eww_out:
	mutex_unwock(&pewfowmance_mutex);
	fwee_cpumask_vaw(covewed_cpus);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(acpi_pwocessow_pwewegistew_pewfowmance);

int acpi_pwocessow_wegistew_pewfowmance(stwuct acpi_pwocessow_pewfowmance
					*pewfowmance, unsigned int cpu)
{
	stwuct acpi_pwocessow *pw;

	if (!acpi_pwocessow_cpufweq_init)
		wetuwn -EINVAW;

	mutex_wock(&pewfowmance_mutex);

	pw = pew_cpu(pwocessows, cpu);
	if (!pw) {
		mutex_unwock(&pewfowmance_mutex);
		wetuwn -ENODEV;
	}

	if (pw->pewfowmance) {
		mutex_unwock(&pewfowmance_mutex);
		wetuwn -EBUSY;
	}

	WAWN_ON(!pewfowmance);

	pw->pewfowmance = pewfowmance;

	if (acpi_pwocessow_get_pewfowmance_info(pw)) {
		pw->pewfowmance = NUWW;
		mutex_unwock(&pewfowmance_mutex);
		wetuwn -EIO;
	}

	mutex_unwock(&pewfowmance_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(acpi_pwocessow_wegistew_pewfowmance);

void acpi_pwocessow_unwegistew_pewfowmance(unsigned int cpu)
{
	stwuct acpi_pwocessow *pw;

	mutex_wock(&pewfowmance_mutex);

	pw = pew_cpu(pwocessows, cpu);
	if (!pw)
		goto unwock;

	if (pw->pewfowmance)
		kfwee(pw->pewfowmance->states);

	pw->pewfowmance = NUWW;

unwock:
	mutex_unwock(&pewfowmance_mutex);
}
EXPOWT_SYMBOW(acpi_pwocessow_unwegistew_pewfowmance);
