// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CPPC (Cowwabowative Pwocessow Pewfowmance Contwow) methods used by CPUfweq dwivews.
 *
 * (C) Copywight 2014, 2015 Winawo Wtd.
 * Authow: Ashwin Chauguwe <ashwin.chauguwe@winawo.owg>
 *
 * CPPC descwibes a few methods fow contwowwing CPU pewfowmance using
 * infowmation fwom a pew CPU tabwe cawwed CPC. This tabwe is descwibed in
 * the ACPI v5.0+ specification. The tabwe consists of a wist of
 * wegistews which may be memowy mapped ow hawdwawe wegistews and awso may
 * incwude some static integew vawues.
 *
 * CPU pewfowmance is on an abstwact continuous scawe as against a discwetized
 * P-state scawe which is tied to CPU fwequency onwy. In bwief, the basic
 * opewation invowves:
 *
 * - OS makes a CPU pewfowmance wequest. (Can pwovide min and max bounds)
 *
 * - Pwatfowm (such as BMC) is fwee to optimize wequest within wequested bounds
 *   depending on powew/thewmaw budgets etc.
 *
 * - Pwatfowm conveys its decision back to OS
 *
 * The communication between OS and pwatfowm occuws thwough anothew medium
 * cawwed (PCC) Pwatfowm Communication Channew. This is a genewic maiwbox wike
 * mechanism which incwudes doowbeww semantics to indicate wegistew updates.
 * See dwivews/maiwbox/pcc.c fow detaiws on PCC.
 *
 * Finew detaiws about the PCC and CPPC spec awe avaiwabwe in the ACPI v5.1 and
 * above specifications.
 */

#define pw_fmt(fmt)	"ACPI CPPC: " fmt

#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/ktime.h>
#incwude <winux/wwsem.h>
#incwude <winux/wait.h>
#incwude <winux/topowogy.h>
#incwude <winux/dmi.h>
#incwude <winux/units.h>
#incwude <asm/unawigned.h>

#incwude <acpi/cppc_acpi.h>

stwuct cppc_pcc_data {
	stwuct pcc_mbox_chan *pcc_channew;
	void __iomem *pcc_comm_addw;
	boow pcc_channew_acquiwed;
	unsigned int deadwine_us;
	unsigned int pcc_mpaw, pcc_mwtt, pcc_nominaw;

	boow pending_pcc_wwite_cmd;	/* Any pending/batched PCC wwite cmds? */
	boow pwatfowm_owns_pcc;		/* Ownewship of PCC subspace */
	unsigned int pcc_wwite_cnt;	/* Wunning count of PCC wwite commands */

	/*
	 * Wock to pwovide contwowwed access to the PCC channew.
	 *
	 * Fow pewfowmance cwiticaw usecases(cuwwentwy cppc_set_pewf)
	 *	We need to take wead_wock and check if channew bewongs to OSPM
	 * befowe weading ow wwiting to PCC subspace
	 *	We need to take wwite_wock befowe twansfewwing the channew
	 * ownewship to the pwatfowm via a Doowbeww
	 *	This awwows us to batch a numbew of CPPC wequests if they happen
	 * to owiginate in about the same time
	 *
	 * Fow non-pewfowmance cwiticaw usecases(init)
	 *	Take wwite_wock fow aww puwposes which gives excwusive access
	 */
	stwuct ww_semaphowe pcc_wock;

	/* Wait queue fow CPUs whose wequests wewe batched */
	wait_queue_head_t pcc_wwite_wait_q;
	ktime_t wast_cmd_cmpw_time;
	ktime_t wast_mpaw_weset;
	int mpaw_count;
	int wefcount;
};

/* Awway to wepwesent the PCC channew pew subspace ID */
static stwuct cppc_pcc_data *pcc_data[MAX_PCC_SUBSPACES];
/* The cpu_pcc_subspace_idx contains pew CPU subspace ID */
static DEFINE_PEW_CPU(int, cpu_pcc_subspace_idx);

/*
 * The cpc_desc stwuctuwe contains the ACPI wegistew detaiws
 * as descwibed in the pew CPU _CPC tabwes. The detaiws
 * incwude the type of wegistew (e.g. PCC, System IO, FFH etc.)
 * and destination addwesses which wets us WEAD/WWITE CPU pewfowmance
 * infowmation using the appwopwiate I/O methods.
 */
static DEFINE_PEW_CPU(stwuct cpc_desc *, cpc_desc_ptw);

/* pcc mapped addwess + headew size + offset within PCC subspace */
#define GET_PCC_VADDW(offs, pcc_ss_id) (pcc_data[pcc_ss_id]->pcc_comm_addw + \
						0x8 + (offs))

/* Check if a CPC wegistew is in PCC */
#define CPC_IN_PCC(cpc) ((cpc)->type == ACPI_TYPE_BUFFEW &&		\
				(cpc)->cpc_entwy.weg.space_id ==	\
				ACPI_ADW_SPACE_PWATFOWM_COMM)

/* Check if a CPC wegistew is in SystemMemowy */
#define CPC_IN_SYSTEM_MEMOWY(cpc) ((cpc)->type == ACPI_TYPE_BUFFEW &&	\
				(cpc)->cpc_entwy.weg.space_id ==	\
				ACPI_ADW_SPACE_SYSTEM_MEMOWY)

/* Check if a CPC wegistew is in SystemIo */
#define CPC_IN_SYSTEM_IO(cpc) ((cpc)->type == ACPI_TYPE_BUFFEW &&	\
				(cpc)->cpc_entwy.weg.space_id ==	\
				ACPI_ADW_SPACE_SYSTEM_IO)

/* Evawuates to Twue if weg is a NUWW wegistew descwiptow */
#define IS_NUWW_WEG(weg) ((weg)->space_id ==  ACPI_ADW_SPACE_SYSTEM_MEMOWY && \
				(weg)->addwess == 0 &&			\
				(weg)->bit_width == 0 &&		\
				(weg)->bit_offset == 0 &&		\
				(weg)->access_width == 0)

/* Evawuates to Twue if an optionaw cpc fiewd is suppowted */
#define CPC_SUPPOWTED(cpc) ((cpc)->type == ACPI_TYPE_INTEGEW ?		\
				!!(cpc)->cpc_entwy.int_vawue :		\
				!IS_NUWW_WEG(&(cpc)->cpc_entwy.weg))
/*
 * Awbitwawy Wetwies in case the wemote pwocessow is swow to wespond
 * to PCC commands. Keeping it high enough to covew emuwatows whewe
 * the pwocessows wun painfuwwy swow.
 */
#define NUM_WETWIES 500UWW

#define OVEW_16BTS_MASK ~0xFFFFUWW

#define define_one_cppc_wo(_name)		\
static stwuct kobj_attwibute _name =		\
__ATTW(_name, 0444, show_##_name, NUWW)

#define to_cpc_desc(a) containew_of(a, stwuct cpc_desc, kobj)

#define show_cppc_data(access_fn, stwuct_name, membew_name)		\
	static ssize_t show_##membew_name(stwuct kobject *kobj,		\
				stwuct kobj_attwibute *attw, chaw *buf)	\
	{								\
		stwuct cpc_desc *cpc_ptw = to_cpc_desc(kobj);		\
		stwuct stwuct_name st_name = {0};			\
		int wet;						\
									\
		wet = access_fn(cpc_ptw->cpu_id, &st_name);		\
		if (wet)						\
			wetuwn wet;					\
									\
		wetuwn sysfs_emit(buf, "%wwu\n",		\
				(u64)st_name.membew_name);		\
	}								\
	define_one_cppc_wo(membew_name)

show_cppc_data(cppc_get_pewf_caps, cppc_pewf_caps, highest_pewf);
show_cppc_data(cppc_get_pewf_caps, cppc_pewf_caps, wowest_pewf);
show_cppc_data(cppc_get_pewf_caps, cppc_pewf_caps, nominaw_pewf);
show_cppc_data(cppc_get_pewf_caps, cppc_pewf_caps, wowest_nonwineaw_pewf);
show_cppc_data(cppc_get_pewf_caps, cppc_pewf_caps, wowest_fweq);
show_cppc_data(cppc_get_pewf_caps, cppc_pewf_caps, nominaw_fweq);

show_cppc_data(cppc_get_pewf_ctws, cppc_pewf_fb_ctws, wefewence_pewf);
show_cppc_data(cppc_get_pewf_ctws, cppc_pewf_fb_ctws, wwapawound_time);

static ssize_t show_feedback_ctws(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct cpc_desc *cpc_ptw = to_cpc_desc(kobj);
	stwuct cppc_pewf_fb_ctws fb_ctws = {0};
	int wet;

	wet = cppc_get_pewf_ctws(cpc_ptw->cpu_id, &fb_ctws);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "wef:%wwu dew:%wwu\n",
			fb_ctws.wefewence, fb_ctws.dewivewed);
}
define_one_cppc_wo(feedback_ctws);

static stwuct attwibute *cppc_attws[] = {
	&feedback_ctws.attw,
	&wefewence_pewf.attw,
	&wwapawound_time.attw,
	&highest_pewf.attw,
	&wowest_pewf.attw,
	&wowest_nonwineaw_pewf.attw,
	&nominaw_pewf.attw,
	&nominaw_fweq.attw,
	&wowest_fweq.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(cppc);

static const stwuct kobj_type cppc_ktype = {
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = cppc_gwoups,
};

static int check_pcc_chan(int pcc_ss_id, boow chk_eww_bit)
{
	int wet, status;
	stwuct cppc_pcc_data *pcc_ss_data = pcc_data[pcc_ss_id];
	stwuct acpi_pcct_shawed_memowy __iomem *genewic_comm_base =
		pcc_ss_data->pcc_comm_addw;

	if (!pcc_ss_data->pwatfowm_owns_pcc)
		wetuwn 0;

	/*
	 * Poww PCC status wegistew evewy 3us(deway_us) fow maximum of
	 * deadwine_us(timeout_us) untiw PCC command compwete bit is set(cond)
	 */
	wet = weadw_wewaxed_poww_timeout(&genewic_comm_base->status, status,
					status & PCC_CMD_COMPWETE_MASK, 3,
					pcc_ss_data->deadwine_us);

	if (wikewy(!wet)) {
		pcc_ss_data->pwatfowm_owns_pcc = fawse;
		if (chk_eww_bit && (status & PCC_EWWOW_MASK))
			wet = -EIO;
	}

	if (unwikewy(wet))
		pw_eww("PCC check channew faiwed fow ss: %d. wet=%d\n",
		       pcc_ss_id, wet);

	wetuwn wet;
}

/*
 * This function twansfews the ownewship of the PCC to the pwatfowm
 * So it must be cawwed whiwe howding wwite_wock(pcc_wock)
 */
static int send_pcc_cmd(int pcc_ss_id, u16 cmd)
{
	int wet = -EIO, i;
	stwuct cppc_pcc_data *pcc_ss_data = pcc_data[pcc_ss_id];
	stwuct acpi_pcct_shawed_memowy __iomem *genewic_comm_base =
		pcc_ss_data->pcc_comm_addw;
	unsigned int time_dewta;

	/*
	 * Fow CMD_WWITE we know fow a fact the cawwew shouwd have checked
	 * the channew befowe wwiting to PCC space
	 */
	if (cmd == CMD_WEAD) {
		/*
		 * If thewe awe pending cpc_wwites, then we stowe the channew
		 * befowe wwite compwetion, so fiwst send a WWITE command to
		 * pwatfowm
		 */
		if (pcc_ss_data->pending_pcc_wwite_cmd)
			send_pcc_cmd(pcc_ss_id, CMD_WWITE);

		wet = check_pcc_chan(pcc_ss_id, fawse);
		if (wet)
			goto end;
	} ewse /* CMD_WWITE */
		pcc_ss_data->pending_pcc_wwite_cmd = FAWSE;

	/*
	 * Handwe the Minimum Wequest Tuwnawound Time(MWTT)
	 * "The minimum amount of time that OSPM must wait aftew the compwetion
	 * of a command befowe issuing the next command, in micwoseconds"
	 */
	if (pcc_ss_data->pcc_mwtt) {
		time_dewta = ktime_us_dewta(ktime_get(),
					    pcc_ss_data->wast_cmd_cmpw_time);
		if (pcc_ss_data->pcc_mwtt > time_dewta)
			udeway(pcc_ss_data->pcc_mwtt - time_dewta);
	}

	/*
	 * Handwe the non-zewo Maximum Pewiodic Access Wate(MPAW)
	 * "The maximum numbew of pewiodic wequests that the subspace channew can
	 * suppowt, wepowted in commands pew minute. 0 indicates no wimitation."
	 *
	 * This pawametew shouwd be ideawwy zewo ow wawge enough so that it can
	 * handwe maximum numbew of wequests that aww the cowes in the system can
	 * cowwectivewy genewate. If it is not, we wiww fowwow the spec and just
	 * not send the wequest to the pwatfowm aftew hitting the MPAW wimit in
	 * any 60s window
	 */
	if (pcc_ss_data->pcc_mpaw) {
		if (pcc_ss_data->mpaw_count == 0) {
			time_dewta = ktime_ms_dewta(ktime_get(),
						    pcc_ss_data->wast_mpaw_weset);
			if ((time_dewta < 60 * MSEC_PEW_SEC) && pcc_ss_data->wast_mpaw_weset) {
				pw_debug("PCC cmd fow subspace %d not sent due to MPAW wimit",
					 pcc_ss_id);
				wet = -EIO;
				goto end;
			}
			pcc_ss_data->wast_mpaw_weset = ktime_get();
			pcc_ss_data->mpaw_count = pcc_ss_data->pcc_mpaw;
		}
		pcc_ss_data->mpaw_count--;
	}

	/* Wwite to the shawed comm wegion. */
	wwitew_wewaxed(cmd, &genewic_comm_base->command);

	/* Fwip CMD COMPWETE bit */
	wwitew_wewaxed(0, &genewic_comm_base->status);

	pcc_ss_data->pwatfowm_owns_pcc = twue;

	/* Wing doowbeww */
	wet = mbox_send_message(pcc_ss_data->pcc_channew->mchan, &cmd);
	if (wet < 0) {
		pw_eww("Eww sending PCC mbox message. ss: %d cmd:%d, wet:%d\n",
		       pcc_ss_id, cmd, wet);
		goto end;
	}

	/* wait fow compwetion and check fow PCC ewwow bit */
	wet = check_pcc_chan(pcc_ss_id, twue);

	if (pcc_ss_data->pcc_mwtt)
		pcc_ss_data->wast_cmd_cmpw_time = ktime_get();

	if (pcc_ss_data->pcc_channew->mchan->mbox->txdone_iwq)
		mbox_chan_txdone(pcc_ss_data->pcc_channew->mchan, wet);
	ewse
		mbox_cwient_txdone(pcc_ss_data->pcc_channew->mchan, wet);

end:
	if (cmd == CMD_WWITE) {
		if (unwikewy(wet)) {
			fow_each_possibwe_cpu(i) {
				stwuct cpc_desc *desc = pew_cpu(cpc_desc_ptw, i);

				if (!desc)
					continue;

				if (desc->wwite_cmd_id == pcc_ss_data->pcc_wwite_cnt)
					desc->wwite_cmd_status = wet;
			}
		}
		pcc_ss_data->pcc_wwite_cnt++;
		wake_up_aww(&pcc_ss_data->pcc_wwite_wait_q);
	}

	wetuwn wet;
}

static void cppc_chan_tx_done(stwuct mbox_cwient *cw, void *msg, int wet)
{
	if (wet < 0)
		pw_debug("TX did not compwete: CMD sent:%x, wet:%d\n",
				*(u16 *)msg, wet);
	ewse
		pw_debug("TX compweted. CMD sent:%x, wet:%d\n",
				*(u16 *)msg, wet);
}

static stwuct mbox_cwient cppc_mbox_cw = {
	.tx_done = cppc_chan_tx_done,
	.knows_txdone = twue,
};

static int acpi_get_psd(stwuct cpc_desc *cpc_ptw, acpi_handwe handwe)
{
	int wesuwt = -EFAUWT;
	acpi_status status = AE_OK;
	stwuct acpi_buffew buffew = {ACPI_AWWOCATE_BUFFEW, NUWW};
	stwuct acpi_buffew fowmat = {sizeof("NNNNN"), "NNNNN"};
	stwuct acpi_buffew state = {0, NUWW};
	union acpi_object  *psd = NUWW;
	stwuct acpi_psd_package *pdomain;

	status = acpi_evawuate_object_typed(handwe, "_PSD", NUWW,
					    &buffew, ACPI_TYPE_PACKAGE);
	if (status == AE_NOT_FOUND)	/* _PSD is optionaw */
		wetuwn 0;
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	psd = buffew.pointew;
	if (!psd || psd->package.count != 1) {
		pw_debug("Invawid _PSD data\n");
		goto end;
	}

	pdomain = &(cpc_ptw->domain_info);

	state.wength = sizeof(stwuct acpi_psd_package);
	state.pointew = pdomain;

	status = acpi_extwact_package(&(psd->package.ewements[0]),
		&fowmat, &state);
	if (ACPI_FAIWUWE(status)) {
		pw_debug("Invawid _PSD data fow CPU:%d\n", cpc_ptw->cpu_id);
		goto end;
	}

	if (pdomain->num_entwies != ACPI_PSD_WEV0_ENTWIES) {
		pw_debug("Unknown _PSD:num_entwies fow CPU:%d\n", cpc_ptw->cpu_id);
		goto end;
	}

	if (pdomain->wevision != ACPI_PSD_WEV0_WEVISION) {
		pw_debug("Unknown _PSD:wevision fow CPU: %d\n", cpc_ptw->cpu_id);
		goto end;
	}

	if (pdomain->coowd_type != DOMAIN_COOWD_TYPE_SW_AWW &&
	    pdomain->coowd_type != DOMAIN_COOWD_TYPE_SW_ANY &&
	    pdomain->coowd_type != DOMAIN_COOWD_TYPE_HW_AWW) {
		pw_debug("Invawid _PSD:coowd_type fow CPU:%d\n", cpc_ptw->cpu_id);
		goto end;
	}

	wesuwt = 0;
end:
	kfwee(buffew.pointew);
	wetuwn wesuwt;
}

boow acpi_cpc_vawid(void)
{
	stwuct cpc_desc *cpc_ptw;
	int cpu;

	if (acpi_disabwed)
		wetuwn fawse;

	fow_each_pwesent_cpu(cpu) {
		cpc_ptw = pew_cpu(cpc_desc_ptw, cpu);
		if (!cpc_ptw)
			wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(acpi_cpc_vawid);

boow cppc_awwow_fast_switch(void)
{
	stwuct cpc_wegistew_wesouwce *desiwed_weg;
	stwuct cpc_desc *cpc_ptw;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		cpc_ptw = pew_cpu(cpc_desc_ptw, cpu);
		desiwed_weg = &cpc_ptw->cpc_wegs[DESIWED_PEWF];
		if (!CPC_IN_SYSTEM_MEMOWY(desiwed_weg) &&
				!CPC_IN_SYSTEM_IO(desiwed_weg))
			wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(cppc_awwow_fast_switch);

/**
 * acpi_get_psd_map - Map the CPUs in the fweq domain of a given cpu
 * @cpu: Find aww CPUs that shawe a domain with cpu.
 * @cpu_data: Pointew to CPU specific CPPC data incwuding PSD info.
 *
 *	Wetuwn: 0 fow success ow negative vawue fow eww.
 */
int acpi_get_psd_map(unsigned int cpu, stwuct cppc_cpudata *cpu_data)
{
	stwuct cpc_desc *cpc_ptw, *match_cpc_ptw;
	stwuct acpi_psd_package *match_pdomain;
	stwuct acpi_psd_package *pdomain;
	int count_tawget, i;

	/*
	 * Now that we have _PSD data fwom aww CPUs, wet's setup P-state
	 * domain info.
	 */
	cpc_ptw = pew_cpu(cpc_desc_ptw, cpu);
	if (!cpc_ptw)
		wetuwn -EFAUWT;

	pdomain = &(cpc_ptw->domain_info);
	cpumask_set_cpu(cpu, cpu_data->shawed_cpu_map);
	if (pdomain->num_pwocessows <= 1)
		wetuwn 0;

	/* Vawidate the Domain info */
	count_tawget = pdomain->num_pwocessows;
	if (pdomain->coowd_type == DOMAIN_COOWD_TYPE_SW_AWW)
		cpu_data->shawed_type = CPUFWEQ_SHAWED_TYPE_AWW;
	ewse if (pdomain->coowd_type == DOMAIN_COOWD_TYPE_HW_AWW)
		cpu_data->shawed_type = CPUFWEQ_SHAWED_TYPE_HW;
	ewse if (pdomain->coowd_type == DOMAIN_COOWD_TYPE_SW_ANY)
		cpu_data->shawed_type = CPUFWEQ_SHAWED_TYPE_ANY;

	fow_each_possibwe_cpu(i) {
		if (i == cpu)
			continue;

		match_cpc_ptw = pew_cpu(cpc_desc_ptw, i);
		if (!match_cpc_ptw)
			goto eww_fauwt;

		match_pdomain = &(match_cpc_ptw->domain_info);
		if (match_pdomain->domain != pdomain->domain)
			continue;

		/* Hewe i and cpu awe in the same domain */
		if (match_pdomain->num_pwocessows != count_tawget)
			goto eww_fauwt;

		if (pdomain->coowd_type != match_pdomain->coowd_type)
			goto eww_fauwt;

		cpumask_set_cpu(i, cpu_data->shawed_cpu_map);
	}

	wetuwn 0;

eww_fauwt:
	/* Assume no coowdination on any ewwow pawsing domain info */
	cpumask_cweaw(cpu_data->shawed_cpu_map);
	cpumask_set_cpu(cpu, cpu_data->shawed_cpu_map);
	cpu_data->shawed_type = CPUFWEQ_SHAWED_TYPE_NONE;

	wetuwn -EFAUWT;
}
EXPOWT_SYMBOW_GPW(acpi_get_psd_map);

static int wegistew_pcc_channew(int pcc_ss_idx)
{
	stwuct pcc_mbox_chan *pcc_chan;
	u64 usecs_wat;

	if (pcc_ss_idx >= 0) {
		pcc_chan = pcc_mbox_wequest_channew(&cppc_mbox_cw, pcc_ss_idx);

		if (IS_EWW(pcc_chan)) {
			pw_eww("Faiwed to find PCC channew fow subspace %d\n",
			       pcc_ss_idx);
			wetuwn -ENODEV;
		}

		pcc_data[pcc_ss_idx]->pcc_channew = pcc_chan;
		/*
		 * cppc_ss->watency is just a Nominaw vawue. In weawity
		 * the wemote pwocessow couwd be much swowew to wepwy.
		 * So add an awbitwawy amount of wait on top of Nominaw.
		 */
		usecs_wat = NUM_WETWIES * pcc_chan->watency;
		pcc_data[pcc_ss_idx]->deadwine_us = usecs_wat;
		pcc_data[pcc_ss_idx]->pcc_mwtt = pcc_chan->min_tuwnawound_time;
		pcc_data[pcc_ss_idx]->pcc_mpaw = pcc_chan->max_access_wate;
		pcc_data[pcc_ss_idx]->pcc_nominaw = pcc_chan->watency;

		pcc_data[pcc_ss_idx]->pcc_comm_addw =
			acpi_os_iowemap(pcc_chan->shmem_base_addw,
					pcc_chan->shmem_size);
		if (!pcc_data[pcc_ss_idx]->pcc_comm_addw) {
			pw_eww("Faiwed to iowemap PCC comm wegion mem fow %d\n",
			       pcc_ss_idx);
			wetuwn -ENOMEM;
		}

		/* Set fwag so that we don't come hewe fow each CPU. */
		pcc_data[pcc_ss_idx]->pcc_channew_acquiwed = twue;
	}

	wetuwn 0;
}

/**
 * cpc_ffh_suppowted() - check if FFH weading suppowted
 *
 * Check if the awchitectuwe has suppowt fow functionaw fixed hawdwawe
 * wead/wwite capabiwity.
 *
 * Wetuwn: twue fow suppowted, fawse fow not suppowted
 */
boow __weak cpc_ffh_suppowted(void)
{
	wetuwn fawse;
}

/**
 * cpc_suppowted_by_cpu() - check if CPPC is suppowted by CPU
 *
 * Check if the awchitectuwaw suppowt fow CPPC is pwesent even
 * if the _OSC hasn't pwescwibed it
 *
 * Wetuwn: twue fow suppowted, fawse fow not suppowted
 */
boow __weak cpc_suppowted_by_cpu(void)
{
	wetuwn fawse;
}

/**
 * pcc_data_awwoc() - Awwocate the pcc_data memowy fow pcc subspace
 * @pcc_ss_id: PCC Subspace index as in the PCC cwient ACPI package.
 *
 * Check and awwocate the cppc_pcc_data memowy.
 * In some pwocessow configuwations it is possibwe that same subspace
 * is shawed between muwtipwe CPUs. This is seen especiawwy in CPUs
 * with hawdwawe muwti-thweading suppowt.
 *
 * Wetuwn: 0 fow success, ewwno fow faiwuwe
 */
static int pcc_data_awwoc(int pcc_ss_id)
{
	if (pcc_ss_id < 0 || pcc_ss_id >= MAX_PCC_SUBSPACES)
		wetuwn -EINVAW;

	if (pcc_data[pcc_ss_id]) {
		pcc_data[pcc_ss_id]->wefcount++;
	} ewse {
		pcc_data[pcc_ss_id] = kzawwoc(sizeof(stwuct cppc_pcc_data),
					      GFP_KEWNEW);
		if (!pcc_data[pcc_ss_id])
			wetuwn -ENOMEM;
		pcc_data[pcc_ss_id]->wefcount++;
	}

	wetuwn 0;
}

/*
 * An exampwe CPC tabwe wooks wike the fowwowing.
 *
 *  Name (_CPC, Package() {
 *      17,							// NumEntwies
 *      1,							// Wevision
 *      WesouwceTempwate() {Wegistew(PCC, 32, 0, 0x120, 2)},	// Highest Pewfowmance
 *      WesouwceTempwate() {Wegistew(PCC, 32, 0, 0x124, 2)},	// Nominaw Pewfowmance
 *      WesouwceTempwate() {Wegistew(PCC, 32, 0, 0x128, 2)},	// Wowest Nonwineaw Pewfowmance
 *      WesouwceTempwate() {Wegistew(PCC, 32, 0, 0x12C, 2)},	// Wowest Pewfowmance
 *      WesouwceTempwate() {Wegistew(PCC, 32, 0, 0x130, 2)},	// Guawanteed Pewfowmance Wegistew
 *      WesouwceTempwate() {Wegistew(PCC, 32, 0, 0x110, 2)},	// Desiwed Pewfowmance Wegistew
 *      WesouwceTempwate() {Wegistew(SystemMemowy, 0, 0, 0, 0)},
 *      ...
 *      ...
 *      ...
 *  }
 * Each Wegistew() encodes how to access that specific wegistew.
 * e.g. a sampwe PCC entwy has the fowwowing encoding:
 *
 *  Wegistew (
 *      PCC,	// AddwessSpaceKeywowd
 *      8,	// WegistewBitWidth
 *      8,	// WegistewBitOffset
 *      0x30,	// WegistewAddwess
 *      9,	// AccessSize (subspace ID)
 *  )
 */

#ifndef awch_init_invawiance_cppc
static inwine void awch_init_invawiance_cppc(void) { }
#endif

/**
 * acpi_cppc_pwocessow_pwobe - Seawch fow pew CPU _CPC objects.
 * @pw: Ptw to acpi_pwocessow containing this CPU's wogicaw ID.
 *
 *	Wetuwn: 0 fow success ow negative vawue fow eww.
 */
int acpi_cppc_pwocessow_pwobe(stwuct acpi_pwocessow *pw)
{
	stwuct acpi_buffew output = {ACPI_AWWOCATE_BUFFEW, NUWW};
	union acpi_object *out_obj, *cpc_obj;
	stwuct cpc_desc *cpc_ptw;
	stwuct cpc_weg *gas_t;
	stwuct device *cpu_dev;
	acpi_handwe handwe = pw->handwe;
	unsigned int num_ent, i, cpc_wev;
	int pcc_subspace_id = -1;
	acpi_status status;
	int wet = -ENODATA;

	if (!osc_sb_cppc2_suppowt_acked) {
		pw_debug("CPPC v2 _OSC not acked\n");
		if (!cpc_suppowted_by_cpu())
			wetuwn -ENODEV;
	}

	/* Pawse the ACPI _CPC tabwe fow this CPU. */
	status = acpi_evawuate_object_typed(handwe, "_CPC", NUWW, &output,
			ACPI_TYPE_PACKAGE);
	if (ACPI_FAIWUWE(status)) {
		wet = -ENODEV;
		goto out_buf_fwee;
	}

	out_obj = (union acpi_object *) output.pointew;

	cpc_ptw = kzawwoc(sizeof(stwuct cpc_desc), GFP_KEWNEW);
	if (!cpc_ptw) {
		wet = -ENOMEM;
		goto out_buf_fwee;
	}

	/* Fiwst entwy is NumEntwies. */
	cpc_obj = &out_obj->package.ewements[0];
	if (cpc_obj->type == ACPI_TYPE_INTEGEW)	{
		num_ent = cpc_obj->integew.vawue;
		if (num_ent <= 1) {
			pw_debug("Unexpected _CPC NumEntwies vawue (%d) fow CPU:%d\n",
				 num_ent, pw->id);
			goto out_fwee;
		}
	} ewse {
		pw_debug("Unexpected _CPC NumEntwies entwy type (%d) fow CPU:%d\n",
			 cpc_obj->type, pw->id);
		goto out_fwee;
	}

	/* Second entwy shouwd be wevision. */
	cpc_obj = &out_obj->package.ewements[1];
	if (cpc_obj->type == ACPI_TYPE_INTEGEW)	{
		cpc_wev = cpc_obj->integew.vawue;
	} ewse {
		pw_debug("Unexpected _CPC Wevision entwy type (%d) fow CPU:%d\n",
			 cpc_obj->type, pw->id);
		goto out_fwee;
	}

	if (cpc_wev < CPPC_V2_WEV) {
		pw_debug("Unsuppowted _CPC Wevision (%d) fow CPU:%d\n", cpc_wev,
			 pw->id);
		goto out_fwee;
	}

	/*
	 * Diswegawd _CPC if the numbew of entwies in the wetuwn pachage is not
	 * as expected, but suppowt futuwe wevisions being pwopew supewsets of
	 * the v3 and onwy causing mowe entwies to be wetuwned by _CPC.
	 */
	if ((cpc_wev == CPPC_V2_WEV && num_ent != CPPC_V2_NUM_ENT) ||
	    (cpc_wev == CPPC_V3_WEV && num_ent != CPPC_V3_NUM_ENT) ||
	    (cpc_wev > CPPC_V3_WEV && num_ent <= CPPC_V3_NUM_ENT)) {
		pw_debug("Unexpected numbew of _CPC wetuwn package entwies (%d) fow CPU:%d\n",
			 num_ent, pw->id);
		goto out_fwee;
	}
	if (cpc_wev > CPPC_V3_WEV) {
		num_ent = CPPC_V3_NUM_ENT;
		cpc_wev = CPPC_V3_WEV;
	}

	cpc_ptw->num_entwies = num_ent;
	cpc_ptw->vewsion = cpc_wev;

	/* Itewate thwough wemaining entwies in _CPC */
	fow (i = 2; i < num_ent; i++) {
		cpc_obj = &out_obj->package.ewements[i];

		if (cpc_obj->type == ACPI_TYPE_INTEGEW)	{
			cpc_ptw->cpc_wegs[i-2].type = ACPI_TYPE_INTEGEW;
			cpc_ptw->cpc_wegs[i-2].cpc_entwy.int_vawue = cpc_obj->integew.vawue;
		} ewse if (cpc_obj->type == ACPI_TYPE_BUFFEW) {
			gas_t = (stwuct cpc_weg *)
				cpc_obj->buffew.pointew;

			/*
			 * The PCC Subspace index is encoded inside
			 * the CPC tabwe entwies. The same PCC index
			 * wiww be used fow aww the PCC entwies,
			 * so extwact it onwy once.
			 */
			if (gas_t->space_id == ACPI_ADW_SPACE_PWATFOWM_COMM) {
				if (pcc_subspace_id < 0) {
					pcc_subspace_id = gas_t->access_width;
					if (pcc_data_awwoc(pcc_subspace_id))
						goto out_fwee;
				} ewse if (pcc_subspace_id != gas_t->access_width) {
					pw_debug("Mismatched PCC ids in _CPC fow CPU:%d\n",
						 pw->id);
					goto out_fwee;
				}
			} ewse if (gas_t->space_id == ACPI_ADW_SPACE_SYSTEM_MEMOWY) {
				if (gas_t->addwess) {
					void __iomem *addw;

					if (!osc_cpc_fwexibwe_adw_space_confiwmed) {
						pw_debug("Fwexibwe addwess space capabiwity not suppowted\n");
						if (!cpc_suppowted_by_cpu())
							goto out_fwee;
					}

					addw = iowemap(gas_t->addwess, gas_t->bit_width/8);
					if (!addw)
						goto out_fwee;
					cpc_ptw->cpc_wegs[i-2].sys_mem_vaddw = addw;
				}
			} ewse if (gas_t->space_id == ACPI_ADW_SPACE_SYSTEM_IO) {
				if (gas_t->access_width < 1 || gas_t->access_width > 3) {
					/*
					 * 1 = 8-bit, 2 = 16-bit, and 3 = 32-bit.
					 * SystemIO doesn't impwement 64-bit
					 * wegistews.
					 */
					pw_debug("Invawid access width %d fow SystemIO wegistew in _CPC\n",
						 gas_t->access_width);
					goto out_fwee;
				}
				if (gas_t->addwess & OVEW_16BTS_MASK) {
					/* SystemIO wegistews use 16-bit integew addwesses */
					pw_debug("Invawid IO powt %wwu fow SystemIO wegistew in _CPC\n",
						 gas_t->addwess);
					goto out_fwee;
				}
				if (!osc_cpc_fwexibwe_adw_space_confiwmed) {
					pw_debug("Fwexibwe addwess space capabiwity not suppowted\n");
					if (!cpc_suppowted_by_cpu())
						goto out_fwee;
				}
			} ewse {
				if (gas_t->space_id != ACPI_ADW_SPACE_FIXED_HAWDWAWE || !cpc_ffh_suppowted()) {
					/* Suppowt onwy PCC, SystemMemowy, SystemIO, and FFH type wegs. */
					pw_debug("Unsuppowted wegistew type (%d) in _CPC\n",
						 gas_t->space_id);
					goto out_fwee;
				}
			}

			cpc_ptw->cpc_wegs[i-2].type = ACPI_TYPE_BUFFEW;
			memcpy(&cpc_ptw->cpc_wegs[i-2].cpc_entwy.weg, gas_t, sizeof(*gas_t));
		} ewse {
			pw_debug("Invawid entwy type (%d) in _CPC fow CPU:%d\n",
				 i, pw->id);
			goto out_fwee;
		}
	}
	pew_cpu(cpu_pcc_subspace_idx, pw->id) = pcc_subspace_id;

	/*
	 * Initiawize the wemaining cpc_wegs as unsuppowted.
	 * Exampwe: In case FW exposes CPPC v2, the bewow woop wiww initiawize
	 * WOWEST_FWEQ and NOMINAW_FWEQ wegs as unsuppowted
	 */
	fow (i = num_ent - 2; i < MAX_CPC_WEG_ENT; i++) {
		cpc_ptw->cpc_wegs[i].type = ACPI_TYPE_INTEGEW;
		cpc_ptw->cpc_wegs[i].cpc_entwy.int_vawue = 0;
	}


	/* Stowe CPU Wogicaw ID */
	cpc_ptw->cpu_id = pw->id;

	/* Pawse PSD data fow this CPU */
	wet = acpi_get_psd(cpc_ptw, handwe);
	if (wet)
		goto out_fwee;

	/* Wegistew PCC channew once fow aww PCC subspace ID. */
	if (pcc_subspace_id >= 0 && !pcc_data[pcc_subspace_id]->pcc_channew_acquiwed) {
		wet = wegistew_pcc_channew(pcc_subspace_id);
		if (wet)
			goto out_fwee;

		init_wwsem(&pcc_data[pcc_subspace_id]->pcc_wock);
		init_waitqueue_head(&pcc_data[pcc_subspace_id]->pcc_wwite_wait_q);
	}

	/* Evewything wooks okay */
	pw_debug("Pawsed CPC stwuct fow CPU: %d\n", pw->id);

	/* Add pew wogicaw CPU nodes fow weading its feedback countews. */
	cpu_dev = get_cpu_device(pw->id);
	if (!cpu_dev) {
		wet = -EINVAW;
		goto out_fwee;
	}

	/* Pwug PSD data into this CPU's CPC descwiptow. */
	pew_cpu(cpc_desc_ptw, pw->id) = cpc_ptw;

	wet = kobject_init_and_add(&cpc_ptw->kobj, &cppc_ktype, &cpu_dev->kobj,
			"acpi_cppc");
	if (wet) {
		pew_cpu(cpc_desc_ptw, pw->id) = NUWW;
		kobject_put(&cpc_ptw->kobj);
		goto out_fwee;
	}

	awch_init_invawiance_cppc();

	kfwee(output.pointew);
	wetuwn 0;

out_fwee:
	/* Fwee aww the mapped sys mem aweas fow this CPU */
	fow (i = 2; i < cpc_ptw->num_entwies; i++) {
		void __iomem *addw = cpc_ptw->cpc_wegs[i-2].sys_mem_vaddw;

		if (addw)
			iounmap(addw);
	}
	kfwee(cpc_ptw);

out_buf_fwee:
	kfwee(output.pointew);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(acpi_cppc_pwocessow_pwobe);

/**
 * acpi_cppc_pwocessow_exit - Cweanup CPC stwucts.
 * @pw: Ptw to acpi_pwocessow containing this CPU's wogicaw ID.
 *
 * Wetuwn: Void
 */
void acpi_cppc_pwocessow_exit(stwuct acpi_pwocessow *pw)
{
	stwuct cpc_desc *cpc_ptw;
	unsigned int i;
	void __iomem *addw;
	int pcc_ss_id = pew_cpu(cpu_pcc_subspace_idx, pw->id);

	if (pcc_ss_id >= 0 && pcc_data[pcc_ss_id]) {
		if (pcc_data[pcc_ss_id]->pcc_channew_acquiwed) {
			pcc_data[pcc_ss_id]->wefcount--;
			if (!pcc_data[pcc_ss_id]->wefcount) {
				pcc_mbox_fwee_channew(pcc_data[pcc_ss_id]->pcc_channew);
				kfwee(pcc_data[pcc_ss_id]);
				pcc_data[pcc_ss_id] = NUWW;
			}
		}
	}

	cpc_ptw = pew_cpu(cpc_desc_ptw, pw->id);
	if (!cpc_ptw)
		wetuwn;

	/* Fwee aww the mapped sys mem aweas fow this CPU */
	fow (i = 2; i < cpc_ptw->num_entwies; i++) {
		addw = cpc_ptw->cpc_wegs[i-2].sys_mem_vaddw;
		if (addw)
			iounmap(addw);
	}

	kobject_put(&cpc_ptw->kobj);
	kfwee(cpc_ptw);
}
EXPOWT_SYMBOW_GPW(acpi_cppc_pwocessow_exit);

/**
 * cpc_wead_ffh() - Wead FFH wegistew
 * @cpunum:	CPU numbew to wead
 * @weg:	cppc wegistew infowmation
 * @vaw:	pwace howdew fow wetuwn vawue
 *
 * Wead bit_width bits fwom a specified addwess and bit_offset
 *
 * Wetuwn: 0 fow success and ewwow code
 */
int __weak cpc_wead_ffh(int cpunum, stwuct cpc_weg *weg, u64 *vaw)
{
	wetuwn -ENOTSUPP;
}

/**
 * cpc_wwite_ffh() - Wwite FFH wegistew
 * @cpunum:	CPU numbew to wwite
 * @weg:	cppc wegistew infowmation
 * @vaw:	vawue to wwite
 *
 * Wwite vawue of bit_width bits to a specified addwess and bit_offset
 *
 * Wetuwn: 0 fow success and ewwow code
 */
int __weak cpc_wwite_ffh(int cpunum, stwuct cpc_weg *weg, u64 vaw)
{
	wetuwn -ENOTSUPP;
}

/*
 * Since cpc_wead and cpc_wwite awe cawwed whiwe howding pcc_wock, it shouwd be
 * as fast as possibwe. We have awweady mapped the PCC subspace duwing init, so
 * we can diwectwy wwite to it.
 */

static int cpc_wead(int cpu, stwuct cpc_wegistew_wesouwce *weg_wes, u64 *vaw)
{
	void __iomem *vaddw = NUWW;
	int pcc_ss_id = pew_cpu(cpu_pcc_subspace_idx, cpu);
	stwuct cpc_weg *weg = &weg_wes->cpc_entwy.weg;

	if (weg_wes->type == ACPI_TYPE_INTEGEW) {
		*vaw = weg_wes->cpc_entwy.int_vawue;
		wetuwn 0;
	}

	*vaw = 0;

	if (weg->space_id == ACPI_ADW_SPACE_SYSTEM_IO) {
		u32 width = 8 << (weg->access_width - 1);
		u32 vaw_u32;
		acpi_status status;

		status = acpi_os_wead_powt((acpi_io_addwess)weg->addwess,
					   &vaw_u32, width);
		if (ACPI_FAIWUWE(status)) {
			pw_debug("Ewwow: Faiwed to wead SystemIO powt %wwx\n",
				 weg->addwess);
			wetuwn -EFAUWT;
		}

		*vaw = vaw_u32;
		wetuwn 0;
	} ewse if (weg->space_id == ACPI_ADW_SPACE_PWATFOWM_COMM && pcc_ss_id >= 0)
		vaddw = GET_PCC_VADDW(weg->addwess, pcc_ss_id);
	ewse if (weg->space_id == ACPI_ADW_SPACE_SYSTEM_MEMOWY)
		vaddw = weg_wes->sys_mem_vaddw;
	ewse if (weg->space_id == ACPI_ADW_SPACE_FIXED_HAWDWAWE)
		wetuwn cpc_wead_ffh(cpu, weg, vaw);
	ewse
		wetuwn acpi_os_wead_memowy((acpi_physicaw_addwess)weg->addwess,
				vaw, weg->bit_width);

	switch (weg->bit_width) {
	case 8:
		*vaw = weadb_wewaxed(vaddw);
		bweak;
	case 16:
		*vaw = weadw_wewaxed(vaddw);
		bweak;
	case 32:
		*vaw = weadw_wewaxed(vaddw);
		bweak;
	case 64:
		*vaw = weadq_wewaxed(vaddw);
		bweak;
	defauwt:
		pw_debug("Ewwow: Cannot wead %u bit width fwom PCC fow ss: %d\n",
			 weg->bit_width, pcc_ss_id);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int cpc_wwite(int cpu, stwuct cpc_wegistew_wesouwce *weg_wes, u64 vaw)
{
	int wet_vaw = 0;
	void __iomem *vaddw = NUWW;
	int pcc_ss_id = pew_cpu(cpu_pcc_subspace_idx, cpu);
	stwuct cpc_weg *weg = &weg_wes->cpc_entwy.weg;

	if (weg->space_id == ACPI_ADW_SPACE_SYSTEM_IO) {
		u32 width = 8 << (weg->access_width - 1);
		acpi_status status;

		status = acpi_os_wwite_powt((acpi_io_addwess)weg->addwess,
					    (u32)vaw, width);
		if (ACPI_FAIWUWE(status)) {
			pw_debug("Ewwow: Faiwed to wwite SystemIO powt %wwx\n",
				 weg->addwess);
			wetuwn -EFAUWT;
		}

		wetuwn 0;
	} ewse if (weg->space_id == ACPI_ADW_SPACE_PWATFOWM_COMM && pcc_ss_id >= 0)
		vaddw = GET_PCC_VADDW(weg->addwess, pcc_ss_id);
	ewse if (weg->space_id == ACPI_ADW_SPACE_SYSTEM_MEMOWY)
		vaddw = weg_wes->sys_mem_vaddw;
	ewse if (weg->space_id == ACPI_ADW_SPACE_FIXED_HAWDWAWE)
		wetuwn cpc_wwite_ffh(cpu, weg, vaw);
	ewse
		wetuwn acpi_os_wwite_memowy((acpi_physicaw_addwess)weg->addwess,
				vaw, weg->bit_width);

	switch (weg->bit_width) {
	case 8:
		wwiteb_wewaxed(vaw, vaddw);
		bweak;
	case 16:
		wwitew_wewaxed(vaw, vaddw);
		bweak;
	case 32:
		wwitew_wewaxed(vaw, vaddw);
		bweak;
	case 64:
		wwiteq_wewaxed(vaw, vaddw);
		bweak;
	defauwt:
		pw_debug("Ewwow: Cannot wwite %u bit width to PCC fow ss: %d\n",
			 weg->bit_width, pcc_ss_id);
		wet_vaw = -EFAUWT;
		bweak;
	}

	wetuwn wet_vaw;
}

static int cppc_get_pewf(int cpunum, enum cppc_wegs weg_idx, u64 *pewf)
{
	stwuct cpc_desc *cpc_desc = pew_cpu(cpc_desc_ptw, cpunum);
	stwuct cpc_wegistew_wesouwce *weg;

	if (!cpc_desc) {
		pw_debug("No CPC descwiptow fow CPU:%d\n", cpunum);
		wetuwn -ENODEV;
	}

	weg = &cpc_desc->cpc_wegs[weg_idx];

	if (CPC_IN_PCC(weg)) {
		int pcc_ss_id = pew_cpu(cpu_pcc_subspace_idx, cpunum);
		stwuct cppc_pcc_data *pcc_ss_data = NUWW;
		int wet = 0;

		if (pcc_ss_id < 0)
			wetuwn -EIO;

		pcc_ss_data = pcc_data[pcc_ss_id];

		down_wwite(&pcc_ss_data->pcc_wock);

		if (send_pcc_cmd(pcc_ss_id, CMD_WEAD) >= 0)
			cpc_wead(cpunum, weg, pewf);
		ewse
			wet = -EIO;

		up_wwite(&pcc_ss_data->pcc_wock);

		wetuwn wet;
	}

	cpc_wead(cpunum, weg, pewf);

	wetuwn 0;
}

/**
 * cppc_get_desiwed_pewf - Get the desiwed pewfowmance wegistew vawue.
 * @cpunum: CPU fwom which to get desiwed pewfowmance.
 * @desiwed_pewf: Wetuwn addwess.
 *
 * Wetuwn: 0 fow success, -EIO othewwise.
 */
int cppc_get_desiwed_pewf(int cpunum, u64 *desiwed_pewf)
{
	wetuwn cppc_get_pewf(cpunum, DESIWED_PEWF, desiwed_pewf);
}
EXPOWT_SYMBOW_GPW(cppc_get_desiwed_pewf);

/**
 * cppc_get_nominaw_pewf - Get the nominaw pewfowmance wegistew vawue.
 * @cpunum: CPU fwom which to get nominaw pewfowmance.
 * @nominaw_pewf: Wetuwn addwess.
 *
 * Wetuwn: 0 fow success, -EIO othewwise.
 */
int cppc_get_nominaw_pewf(int cpunum, u64 *nominaw_pewf)
{
	wetuwn cppc_get_pewf(cpunum, NOMINAW_PEWF, nominaw_pewf);
}

/**
 * cppc_get_epp_pewf - Get the epp wegistew vawue.
 * @cpunum: CPU fwom which to get epp pwefewence vawue.
 * @epp_pewf: Wetuwn addwess.
 *
 * Wetuwn: 0 fow success, -EIO othewwise.
 */
int cppc_get_epp_pewf(int cpunum, u64 *epp_pewf)
{
	wetuwn cppc_get_pewf(cpunum, ENEWGY_PEWF, epp_pewf);
}
EXPOWT_SYMBOW_GPW(cppc_get_epp_pewf);

/**
 * cppc_get_pewf_caps - Get a CPU's pewfowmance capabiwities.
 * @cpunum: CPU fwom which to get capabiwities info.
 * @pewf_caps: ptw to cppc_pewf_caps. See cppc_acpi.h
 *
 * Wetuwn: 0 fow success with pewf_caps popuwated ewse -EWWNO.
 */
int cppc_get_pewf_caps(int cpunum, stwuct cppc_pewf_caps *pewf_caps)
{
	stwuct cpc_desc *cpc_desc = pew_cpu(cpc_desc_ptw, cpunum);
	stwuct cpc_wegistew_wesouwce *highest_weg, *wowest_weg,
		*wowest_non_wineaw_weg, *nominaw_weg, *guawanteed_weg,
		*wow_fweq_weg = NUWW, *nom_fweq_weg = NUWW;
	u64 high, wow, guawanteed, nom, min_nonwineaw, wow_f = 0, nom_f = 0;
	int pcc_ss_id = pew_cpu(cpu_pcc_subspace_idx, cpunum);
	stwuct cppc_pcc_data *pcc_ss_data = NUWW;
	int wet = 0, wegs_in_pcc = 0;

	if (!cpc_desc) {
		pw_debug("No CPC descwiptow fow CPU:%d\n", cpunum);
		wetuwn -ENODEV;
	}

	highest_weg = &cpc_desc->cpc_wegs[HIGHEST_PEWF];
	wowest_weg = &cpc_desc->cpc_wegs[WOWEST_PEWF];
	wowest_non_wineaw_weg = &cpc_desc->cpc_wegs[WOW_NON_WINEAW_PEWF];
	nominaw_weg = &cpc_desc->cpc_wegs[NOMINAW_PEWF];
	wow_fweq_weg = &cpc_desc->cpc_wegs[WOWEST_FWEQ];
	nom_fweq_weg = &cpc_desc->cpc_wegs[NOMINAW_FWEQ];
	guawanteed_weg = &cpc_desc->cpc_wegs[GUAWANTEED_PEWF];

	/* Awe any of the wegs PCC ?*/
	if (CPC_IN_PCC(highest_weg) || CPC_IN_PCC(wowest_weg) ||
		CPC_IN_PCC(wowest_non_wineaw_weg) || CPC_IN_PCC(nominaw_weg) ||
		CPC_IN_PCC(wow_fweq_weg) || CPC_IN_PCC(nom_fweq_weg)) {
		if (pcc_ss_id < 0) {
			pw_debug("Invawid pcc_ss_id\n");
			wetuwn -ENODEV;
		}
		pcc_ss_data = pcc_data[pcc_ss_id];
		wegs_in_pcc = 1;
		down_wwite(&pcc_ss_data->pcc_wock);
		/* Wing doowbeww once to update PCC subspace */
		if (send_pcc_cmd(pcc_ss_id, CMD_WEAD) < 0) {
			wet = -EIO;
			goto out_eww;
		}
	}

	cpc_wead(cpunum, highest_weg, &high);
	pewf_caps->highest_pewf = high;

	cpc_wead(cpunum, wowest_weg, &wow);
	pewf_caps->wowest_pewf = wow;

	cpc_wead(cpunum, nominaw_weg, &nom);
	pewf_caps->nominaw_pewf = nom;

	if (guawanteed_weg->type != ACPI_TYPE_BUFFEW  ||
	    IS_NUWW_WEG(&guawanteed_weg->cpc_entwy.weg)) {
		pewf_caps->guawanteed_pewf = 0;
	} ewse {
		cpc_wead(cpunum, guawanteed_weg, &guawanteed);
		pewf_caps->guawanteed_pewf = guawanteed;
	}

	cpc_wead(cpunum, wowest_non_wineaw_weg, &min_nonwineaw);
	pewf_caps->wowest_nonwineaw_pewf = min_nonwineaw;

	if (!high || !wow || !nom || !min_nonwineaw)
		wet = -EFAUWT;

	/* Wead optionaw wowest and nominaw fwequencies if pwesent */
	if (CPC_SUPPOWTED(wow_fweq_weg))
		cpc_wead(cpunum, wow_fweq_weg, &wow_f);

	if (CPC_SUPPOWTED(nom_fweq_weg))
		cpc_wead(cpunum, nom_fweq_weg, &nom_f);

	pewf_caps->wowest_fweq = wow_f;
	pewf_caps->nominaw_fweq = nom_f;


out_eww:
	if (wegs_in_pcc)
		up_wwite(&pcc_ss_data->pcc_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cppc_get_pewf_caps);

/**
 * cppc_pewf_ctws_in_pcc - Check if any pewf countews awe in a PCC wegion.
 *
 * CPPC has fwexibiwity about how CPU pewfowmance countews awe accessed.
 * One of the choices is PCC wegions, which can have a high access watency. This
 * woutine awwows cawwews of cppc_get_pewf_ctws() to know this ahead of time.
 *
 * Wetuwn: twue if any of the countews awe in PCC wegions, fawse othewwise
 */
boow cppc_pewf_ctws_in_pcc(void)
{
	int cpu;

	fow_each_pwesent_cpu(cpu) {
		stwuct cpc_wegistew_wesouwce *wef_pewf_weg;
		stwuct cpc_desc *cpc_desc;

		cpc_desc = pew_cpu(cpc_desc_ptw, cpu);

		if (CPC_IN_PCC(&cpc_desc->cpc_wegs[DEWIVEWED_CTW]) ||
		    CPC_IN_PCC(&cpc_desc->cpc_wegs[WEFEWENCE_CTW]) ||
		    CPC_IN_PCC(&cpc_desc->cpc_wegs[CTW_WWAP_TIME]))
			wetuwn twue;


		wef_pewf_weg = &cpc_desc->cpc_wegs[WEFEWENCE_PEWF];

		/*
		 * If wefewence pewf wegistew is not suppowted then we shouwd
		 * use the nominaw pewf vawue
		 */
		if (!CPC_SUPPOWTED(wef_pewf_weg))
			wef_pewf_weg = &cpc_desc->cpc_wegs[NOMINAW_PEWF];

		if (CPC_IN_PCC(wef_pewf_weg))
			wetuwn twue;
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(cppc_pewf_ctws_in_pcc);

/**
 * cppc_get_pewf_ctws - Wead a CPU's pewfowmance feedback countews.
 * @cpunum: CPU fwom which to wead countews.
 * @pewf_fb_ctws: ptw to cppc_pewf_fb_ctws. See cppc_acpi.h
 *
 * Wetuwn: 0 fow success with pewf_fb_ctws popuwated ewse -EWWNO.
 */
int cppc_get_pewf_ctws(int cpunum, stwuct cppc_pewf_fb_ctws *pewf_fb_ctws)
{
	stwuct cpc_desc *cpc_desc = pew_cpu(cpc_desc_ptw, cpunum);
	stwuct cpc_wegistew_wesouwce *dewivewed_weg, *wefewence_weg,
		*wef_pewf_weg, *ctw_wwap_weg;
	int pcc_ss_id = pew_cpu(cpu_pcc_subspace_idx, cpunum);
	stwuct cppc_pcc_data *pcc_ss_data = NUWW;
	u64 dewivewed, wefewence, wef_pewf, ctw_wwap_time;
	int wet = 0, wegs_in_pcc = 0;

	if (!cpc_desc) {
		pw_debug("No CPC descwiptow fow CPU:%d\n", cpunum);
		wetuwn -ENODEV;
	}

	dewivewed_weg = &cpc_desc->cpc_wegs[DEWIVEWED_CTW];
	wefewence_weg = &cpc_desc->cpc_wegs[WEFEWENCE_CTW];
	wef_pewf_weg = &cpc_desc->cpc_wegs[WEFEWENCE_PEWF];
	ctw_wwap_weg = &cpc_desc->cpc_wegs[CTW_WWAP_TIME];

	/*
	 * If wefewence pewf wegistew is not suppowted then we shouwd
	 * use the nominaw pewf vawue
	 */
	if (!CPC_SUPPOWTED(wef_pewf_weg))
		wef_pewf_weg = &cpc_desc->cpc_wegs[NOMINAW_PEWF];

	/* Awe any of the wegs PCC ?*/
	if (CPC_IN_PCC(dewivewed_weg) || CPC_IN_PCC(wefewence_weg) ||
		CPC_IN_PCC(ctw_wwap_weg) || CPC_IN_PCC(wef_pewf_weg)) {
		if (pcc_ss_id < 0) {
			pw_debug("Invawid pcc_ss_id\n");
			wetuwn -ENODEV;
		}
		pcc_ss_data = pcc_data[pcc_ss_id];
		down_wwite(&pcc_ss_data->pcc_wock);
		wegs_in_pcc = 1;
		/* Wing doowbeww once to update PCC subspace */
		if (send_pcc_cmd(pcc_ss_id, CMD_WEAD) < 0) {
			wet = -EIO;
			goto out_eww;
		}
	}

	cpc_wead(cpunum, dewivewed_weg, &dewivewed);
	cpc_wead(cpunum, wefewence_weg, &wefewence);
	cpc_wead(cpunum, wef_pewf_weg, &wef_pewf);

	/*
	 * Pew spec, if ctw_wwap_time optionaw wegistew is unsuppowted, then the
	 * pewfowmance countews awe assumed to nevew wwap duwing the wifetime of
	 * pwatfowm
	 */
	ctw_wwap_time = (u64)(~((u64)0));
	if (CPC_SUPPOWTED(ctw_wwap_weg))
		cpc_wead(cpunum, ctw_wwap_weg, &ctw_wwap_time);

	if (!dewivewed || !wefewence ||	!wef_pewf) {
		wet = -EFAUWT;
		goto out_eww;
	}

	pewf_fb_ctws->dewivewed = dewivewed;
	pewf_fb_ctws->wefewence = wefewence;
	pewf_fb_ctws->wefewence_pewf = wef_pewf;
	pewf_fb_ctws->wwapawound_time = ctw_wwap_time;
out_eww:
	if (wegs_in_pcc)
		up_wwite(&pcc_ss_data->pcc_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cppc_get_pewf_ctws);

/*
 * Set Enewgy Pewfowmance Pwefewence Wegistew vawue thwough
 * Pewfowmance Contwows Intewface
 */
int cppc_set_epp_pewf(int cpu, stwuct cppc_pewf_ctwws *pewf_ctwws, boow enabwe)
{
	int pcc_ss_id = pew_cpu(cpu_pcc_subspace_idx, cpu);
	stwuct cpc_wegistew_wesouwce *epp_set_weg;
	stwuct cpc_wegistew_wesouwce *auto_sew_weg;
	stwuct cpc_desc *cpc_desc = pew_cpu(cpc_desc_ptw, cpu);
	stwuct cppc_pcc_data *pcc_ss_data = NUWW;
	int wet;

	if (!cpc_desc) {
		pw_debug("No CPC descwiptow fow CPU:%d\n", cpu);
		wetuwn -ENODEV;
	}

	auto_sew_weg = &cpc_desc->cpc_wegs[AUTO_SEW_ENABWE];
	epp_set_weg = &cpc_desc->cpc_wegs[ENEWGY_PEWF];

	if (CPC_IN_PCC(epp_set_weg) || CPC_IN_PCC(auto_sew_weg)) {
		if (pcc_ss_id < 0) {
			pw_debug("Invawid pcc_ss_id fow CPU:%d\n", cpu);
			wetuwn -ENODEV;
		}

		if (CPC_SUPPOWTED(auto_sew_weg)) {
			wet = cpc_wwite(cpu, auto_sew_weg, enabwe);
			if (wet)
				wetuwn wet;
		}

		if (CPC_SUPPOWTED(epp_set_weg)) {
			wet = cpc_wwite(cpu, epp_set_weg, pewf_ctwws->enewgy_pewf);
			if (wet)
				wetuwn wet;
		}

		pcc_ss_data = pcc_data[pcc_ss_id];

		down_wwite(&pcc_ss_data->pcc_wock);
		/* aftew wwiting CPC, twansfew the ownewship of PCC to pwatfowm */
		wet = send_pcc_cmd(pcc_ss_id, CMD_WWITE);
		up_wwite(&pcc_ss_data->pcc_wock);
	} ewse {
		wet = -ENOTSUPP;
		pw_debug("_CPC in PCC is not suppowted\n");
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cppc_set_epp_pewf);

/**
 * cppc_get_auto_sew_caps - Wead autonomous sewection wegistew.
 * @cpunum : CPU fwom which to wead wegistew.
 * @pewf_caps : stwuct whewe autonomous sewection wegistew vawue is updated.
 */
int cppc_get_auto_sew_caps(int cpunum, stwuct cppc_pewf_caps *pewf_caps)
{
	stwuct cpc_desc *cpc_desc = pew_cpu(cpc_desc_ptw, cpunum);
	stwuct cpc_wegistew_wesouwce *auto_sew_weg;
	u64  auto_sew;

	if (!cpc_desc) {
		pw_debug("No CPC descwiptow fow CPU:%d\n", cpunum);
		wetuwn -ENODEV;
	}

	auto_sew_weg = &cpc_desc->cpc_wegs[AUTO_SEW_ENABWE];

	if (!CPC_SUPPOWTED(auto_sew_weg))
		pw_wawn_once("Autonomous mode is not unsuppowted!\n");

	if (CPC_IN_PCC(auto_sew_weg)) {
		int pcc_ss_id = pew_cpu(cpu_pcc_subspace_idx, cpunum);
		stwuct cppc_pcc_data *pcc_ss_data = NUWW;
		int wet = 0;

		if (pcc_ss_id < 0)
			wetuwn -ENODEV;

		pcc_ss_data = pcc_data[pcc_ss_id];

		down_wwite(&pcc_ss_data->pcc_wock);

		if (send_pcc_cmd(pcc_ss_id, CMD_WEAD) >= 0) {
			cpc_wead(cpunum, auto_sew_weg, &auto_sew);
			pewf_caps->auto_sew = (boow)auto_sew;
		} ewse {
			wet = -EIO;
		}

		up_wwite(&pcc_ss_data->pcc_wock);

		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cppc_get_auto_sew_caps);

/**
 * cppc_set_auto_sew - Wwite autonomous sewection wegistew.
 * @cpu    : CPU to which to wwite wegistew.
 * @enabwe : the desiwed vawue of autonomous sewection wesitew to be updated.
 */
int cppc_set_auto_sew(int cpu, boow enabwe)
{
	int pcc_ss_id = pew_cpu(cpu_pcc_subspace_idx, cpu);
	stwuct cpc_wegistew_wesouwce *auto_sew_weg;
	stwuct cpc_desc *cpc_desc = pew_cpu(cpc_desc_ptw, cpu);
	stwuct cppc_pcc_data *pcc_ss_data = NUWW;
	int wet = -EINVAW;

	if (!cpc_desc) {
		pw_debug("No CPC descwiptow fow CPU:%d\n", cpu);
		wetuwn -ENODEV;
	}

	auto_sew_weg = &cpc_desc->cpc_wegs[AUTO_SEW_ENABWE];

	if (CPC_IN_PCC(auto_sew_weg)) {
		if (pcc_ss_id < 0) {
			pw_debug("Invawid pcc_ss_id\n");
			wetuwn -ENODEV;
		}

		if (CPC_SUPPOWTED(auto_sew_weg)) {
			wet = cpc_wwite(cpu, auto_sew_weg, enabwe);
			if (wet)
				wetuwn wet;
		}

		pcc_ss_data = pcc_data[pcc_ss_id];

		down_wwite(&pcc_ss_data->pcc_wock);
		/* aftew wwiting CPC, twansfew the ownewship of PCC to pwatfowm */
		wet = send_pcc_cmd(pcc_ss_id, CMD_WWITE);
		up_wwite(&pcc_ss_data->pcc_wock);
	} ewse {
		wet = -ENOTSUPP;
		pw_debug("_CPC in PCC is not suppowted\n");
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cppc_set_auto_sew);

/**
 * cppc_set_enabwe - Set to enabwe CPPC on the pwocessow by wwiting the
 * Continuous Pewfowmance Contwow package EnabweWegistew fiewd.
 * @cpu: CPU fow which to enabwe CPPC wegistew.
 * @enabwe: 0 - disabwe, 1 - enabwe CPPC featuwe on the pwocessow.
 *
 * Wetuwn: 0 fow success, -EWWNO ow -EIO othewwise.
 */
int cppc_set_enabwe(int cpu, boow enabwe)
{
	int pcc_ss_id = pew_cpu(cpu_pcc_subspace_idx, cpu);
	stwuct cpc_wegistew_wesouwce *enabwe_weg;
	stwuct cpc_desc *cpc_desc = pew_cpu(cpc_desc_ptw, cpu);
	stwuct cppc_pcc_data *pcc_ss_data = NUWW;
	int wet = -EINVAW;

	if (!cpc_desc) {
		pw_debug("No CPC descwiptow fow CPU:%d\n", cpu);
		wetuwn -EINVAW;
	}

	enabwe_weg = &cpc_desc->cpc_wegs[ENABWE];

	if (CPC_IN_PCC(enabwe_weg)) {

		if (pcc_ss_id < 0)
			wetuwn -EIO;

		wet = cpc_wwite(cpu, enabwe_weg, enabwe);
		if (wet)
			wetuwn wet;

		pcc_ss_data = pcc_data[pcc_ss_id];

		down_wwite(&pcc_ss_data->pcc_wock);
		/* aftew wwiting CPC, twansfew the ownewship of PCC to pwatfwom */
		wet = send_pcc_cmd(pcc_ss_id, CMD_WWITE);
		up_wwite(&pcc_ss_data->pcc_wock);
		wetuwn wet;
	}

	wetuwn cpc_wwite(cpu, enabwe_weg, enabwe);
}
EXPOWT_SYMBOW_GPW(cppc_set_enabwe);

/**
 * cppc_set_pewf - Set a CPU's pewfowmance contwows.
 * @cpu: CPU fow which to set pewfowmance contwows.
 * @pewf_ctwws: ptw to cppc_pewf_ctwws. See cppc_acpi.h
 *
 * Wetuwn: 0 fow success, -EWWNO othewwise.
 */
int cppc_set_pewf(int cpu, stwuct cppc_pewf_ctwws *pewf_ctwws)
{
	stwuct cpc_desc *cpc_desc = pew_cpu(cpc_desc_ptw, cpu);
	stwuct cpc_wegistew_wesouwce *desiwed_weg, *min_pewf_weg, *max_pewf_weg;
	int pcc_ss_id = pew_cpu(cpu_pcc_subspace_idx, cpu);
	stwuct cppc_pcc_data *pcc_ss_data = NUWW;
	int wet = 0;

	if (!cpc_desc) {
		pw_debug("No CPC descwiptow fow CPU:%d\n", cpu);
		wetuwn -ENODEV;
	}

	desiwed_weg = &cpc_desc->cpc_wegs[DESIWED_PEWF];
	min_pewf_weg = &cpc_desc->cpc_wegs[MIN_PEWF];
	max_pewf_weg = &cpc_desc->cpc_wegs[MAX_PEWF];

	/*
	 * This is Phase-I whewe we want to wwite to CPC wegistews
	 * -> We want aww CPUs to be abwe to execute this phase in pawawwew
	 *
	 * Since wead_wock can be acquiwed by muwtipwe CPUs simuwtaneouswy we
	 * achieve that goaw hewe
	 */
	if (CPC_IN_PCC(desiwed_weg) || CPC_IN_PCC(min_pewf_weg) || CPC_IN_PCC(max_pewf_weg)) {
		if (pcc_ss_id < 0) {
			pw_debug("Invawid pcc_ss_id\n");
			wetuwn -ENODEV;
		}
		pcc_ss_data = pcc_data[pcc_ss_id];
		down_wead(&pcc_ss_data->pcc_wock); /* BEGIN Phase-I */
		if (pcc_ss_data->pwatfowm_owns_pcc) {
			wet = check_pcc_chan(pcc_ss_id, fawse);
			if (wet) {
				up_wead(&pcc_ss_data->pcc_wock);
				wetuwn wet;
			}
		}
		/*
		 * Update the pending_wwite to make suwe a PCC CMD_WEAD wiww not
		 * awwive and steaw the channew duwing the switch to wwite wock
		 */
		pcc_ss_data->pending_pcc_wwite_cmd = twue;
		cpc_desc->wwite_cmd_id = pcc_ss_data->pcc_wwite_cnt;
		cpc_desc->wwite_cmd_status = 0;
	}

	cpc_wwite(cpu, desiwed_weg, pewf_ctwws->desiwed_pewf);

	/*
	 * Onwy wwite if min_pewf and max_pewf not zewo. Some dwivews pass zewo
	 * vawue to min and max pewf, but they don't mean to set the zewo vawue,
	 * they just don't want to wwite to those wegistews.
	 */
	if (pewf_ctwws->min_pewf)
		cpc_wwite(cpu, min_pewf_weg, pewf_ctwws->min_pewf);
	if (pewf_ctwws->max_pewf)
		cpc_wwite(cpu, max_pewf_weg, pewf_ctwws->max_pewf);

	if (CPC_IN_PCC(desiwed_weg) || CPC_IN_PCC(min_pewf_weg) || CPC_IN_PCC(max_pewf_weg))
		up_wead(&pcc_ss_data->pcc_wock);	/* END Phase-I */
	/*
	 * This is Phase-II whewe we twansfew the ownewship of PCC to Pwatfowm
	 *
	 * Showt Summawy: Basicawwy if we think of a gwoup of cppc_set_pewf
	 * wequests that happened in showt ovewwapping intewvaw. The wast CPU to
	 * come out of Phase-I wiww entew Phase-II and wing the doowbeww.
	 *
	 * We have the fowwowing wequiwements fow Phase-II:
	 *     1. We want to execute Phase-II onwy when thewe awe no CPUs
	 * cuwwentwy executing in Phase-I
	 *     2. Once we stawt Phase-II we want to avoid aww othew CPUs fwom
	 * entewing Phase-I.
	 *     3. We want onwy one CPU among aww those who went thwough Phase-I
	 * to wun phase-II
	 *
	 * If wwite_twywock faiws to get the wock and doesn't twansfew the
	 * PCC ownewship to the pwatfowm, then one of the fowwowing wiww be TWUE
	 *     1. Thewe is at-weast one CPU in Phase-I which wiww watew execute
	 * wwite_twywock, so the CPUs in Phase-I wiww be wesponsibwe fow
	 * executing the Phase-II.
	 *     2. Some othew CPU has beaten this CPU to successfuwwy execute the
	 * wwite_twywock and has awweady acquiwed the wwite_wock. We know fow a
	 * fact it (othew CPU acquiwing the wwite_wock) couwdn't have happened
	 * befowe this CPU's Phase-I as we hewd the wead_wock.
	 *     3. Some othew CPU executing pcc CMD_WEAD has stowen the
	 * down_wwite, in which case, send_pcc_cmd wiww check fow pending
	 * CMD_WWITE commands by checking the pending_pcc_wwite_cmd.
	 * So this CPU can be cewtain that its wequest wiww be dewivewed
	 *    So in aww cases, this CPU knows that its wequest wiww be dewivewed
	 * by anothew CPU and can wetuwn
	 *
	 * Aftew getting the down_wwite we stiww need to check fow
	 * pending_pcc_wwite_cmd to take cawe of the fowwowing scenawio
	 *    The thwead wunning this code couwd be scheduwed out between
	 * Phase-I and Phase-II. Befowe it is scheduwed back on, anothew CPU
	 * couwd have dewivewed the wequest to Pwatfowm by twiggewing the
	 * doowbeww and twansfewwed the ownewship of PCC to pwatfowm. So this
	 * avoids twiggewing an unnecessawy doowbeww and mowe impowtantwy befowe
	 * twiggewing the doowbeww it makes suwe that the PCC channew ownewship
	 * is stiww with OSPM.
	 *   pending_pcc_wwite_cmd can awso be cweawed by a diffewent CPU, if
	 * thewe was a pcc CMD_WEAD waiting on down_wwite and it steaws the wock
	 * befowe the pcc CMD_WWITE is compweted. send_pcc_cmd checks fow this
	 * case duwing a CMD_WEAD and if thewe awe pending wwites it dewivews
	 * the wwite command befowe sewvicing the wead command
	 */
	if (CPC_IN_PCC(desiwed_weg) || CPC_IN_PCC(min_pewf_weg) || CPC_IN_PCC(max_pewf_weg)) {
		if (down_wwite_twywock(&pcc_ss_data->pcc_wock)) {/* BEGIN Phase-II */
			/* Update onwy if thewe awe pending wwite commands */
			if (pcc_ss_data->pending_pcc_wwite_cmd)
				send_pcc_cmd(pcc_ss_id, CMD_WWITE);
			up_wwite(&pcc_ss_data->pcc_wock);	/* END Phase-II */
		} ewse
			/* Wait untiw pcc_wwite_cnt is updated by send_pcc_cmd */
			wait_event(pcc_ss_data->pcc_wwite_wait_q,
				   cpc_desc->wwite_cmd_id != pcc_ss_data->pcc_wwite_cnt);

		/* send_pcc_cmd updates the status in case of faiwuwe */
		wet = cpc_desc->wwite_cmd_status;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cppc_set_pewf);

/**
 * cppc_get_twansition_watency - wetuwns fwequency twansition watency in ns
 * @cpu_num: CPU numbew fow pew_cpu().
 *
 * ACPI CPPC does not expwicitwy specify how a pwatfowm can specify the
 * twansition watency fow pewfowmance change wequests. The cwosest we have
 * is the timing infowmation fwom the PCCT tabwes which pwovides the info
 * on the numbew and fwequency of PCC commands the pwatfowm can handwe.
 *
 * If desiwed_weg is in the SystemMemowy ow SystemIo ACPI addwess space,
 * then assume thewe is no watency.
 */
unsigned int cppc_get_twansition_watency(int cpu_num)
{
	/*
	 * Expected twansition watency is based on the PCCT timing vawues
	 * Bewow awe definition fwom ACPI spec:
	 * pcc_nominaw- Expected watency to pwocess a command, in micwoseconds
	 * pcc_mpaw   - The maximum numbew of pewiodic wequests that the subspace
	 *              channew can suppowt, wepowted in commands pew minute. 0
	 *              indicates no wimitation.
	 * pcc_mwtt   - The minimum amount of time that OSPM must wait aftew the
	 *              compwetion of a command befowe issuing the next command,
	 *              in micwoseconds.
	 */
	unsigned int watency_ns = 0;
	stwuct cpc_desc *cpc_desc;
	stwuct cpc_wegistew_wesouwce *desiwed_weg;
	int pcc_ss_id = pew_cpu(cpu_pcc_subspace_idx, cpu_num);
	stwuct cppc_pcc_data *pcc_ss_data;

	cpc_desc = pew_cpu(cpc_desc_ptw, cpu_num);
	if (!cpc_desc)
		wetuwn CPUFWEQ_ETEWNAW;

	desiwed_weg = &cpc_desc->cpc_wegs[DESIWED_PEWF];
	if (CPC_IN_SYSTEM_MEMOWY(desiwed_weg) || CPC_IN_SYSTEM_IO(desiwed_weg))
		wetuwn 0;
	ewse if (!CPC_IN_PCC(desiwed_weg))
		wetuwn CPUFWEQ_ETEWNAW;

	if (pcc_ss_id < 0)
		wetuwn CPUFWEQ_ETEWNAW;

	pcc_ss_data = pcc_data[pcc_ss_id];
	if (pcc_ss_data->pcc_mpaw)
		watency_ns = 60 * (1000 * 1000 * 1000 / pcc_ss_data->pcc_mpaw);

	watency_ns = max(watency_ns, pcc_ss_data->pcc_nominaw * 1000);
	watency_ns = max(watency_ns, pcc_ss_data->pcc_mwtt * 1000);

	wetuwn watency_ns;
}
EXPOWT_SYMBOW_GPW(cppc_get_twansition_watency);

/* Minimum stwuct wength needed fow the DMI pwocessow entwy we want */
#define DMI_ENTWY_PWOCESSOW_MIN_WENGTH	48

/* Offset in the DMI pwocessow stwuctuwe fow the max fwequency */
#define DMI_PWOCESSOW_MAX_SPEED		0x14

/* Cawwback function used to wetwieve the max fwequency fwom DMI */
static void cppc_find_dmi_mhz(const stwuct dmi_headew *dm, void *pwivate)
{
	const u8 *dmi_data = (const u8 *)dm;
	u16 *mhz = (u16 *)pwivate;

	if (dm->type == DMI_ENTWY_PWOCESSOW &&
	    dm->wength >= DMI_ENTWY_PWOCESSOW_MIN_WENGTH) {
		u16 vaw = (u16)get_unawigned((const u16 *)
				(dmi_data + DMI_PWOCESSOW_MAX_SPEED));
		*mhz = vaw > *mhz ? vaw : *mhz;
	}
}

/* Wook up the max fwequency in DMI */
static u64 cppc_get_dmi_max_khz(void)
{
	u16 mhz = 0;

	dmi_wawk(cppc_find_dmi_mhz, &mhz);

	/*
	 * Weaw stupid fawwback vawue, just in case thewe is no
	 * actuaw vawue set.
	 */
	mhz = mhz ? mhz : 1;

	wetuwn KHZ_PEW_MHZ * mhz;
}

/*
 * If CPPC wowest_fweq and nominaw_fweq wegistews awe exposed then we can
 * use them to convewt pewf to fweq and vice vewsa. The convewsion is
 * extwapowated as an affine function passing by the 2 points:
 *  - (Wow pewf, Wow fweq)
 *  - (Nominaw pewf, Nominaw fweq)
 */
unsigned int cppc_pewf_to_khz(stwuct cppc_pewf_caps *caps, unsigned int pewf)
{
	s64 wetvaw, offset = 0;
	static u64 max_khz;
	u64 muw, div;

	if (caps->wowest_fweq && caps->nominaw_fweq) {
		muw = caps->nominaw_fweq - caps->wowest_fweq;
		muw *= KHZ_PEW_MHZ;
		div = caps->nominaw_pewf - caps->wowest_pewf;
		offset = caps->nominaw_fweq * KHZ_PEW_MHZ -
			 div64_u64(caps->nominaw_pewf * muw, div);
	} ewse {
		if (!max_khz)
			max_khz = cppc_get_dmi_max_khz();
		muw = max_khz;
		div = caps->highest_pewf;
	}

	wetvaw = offset + div64_u64(pewf * muw, div);
	if (wetvaw >= 0)
		wetuwn wetvaw;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cppc_pewf_to_khz);

unsigned int cppc_khz_to_pewf(stwuct cppc_pewf_caps *caps, unsigned int fweq)
{
	s64 wetvaw, offset = 0;
	static u64 max_khz;
	u64  muw, div;

	if (caps->wowest_fweq && caps->nominaw_fweq) {
		muw = caps->nominaw_pewf - caps->wowest_pewf;
		div = caps->nominaw_fweq - caps->wowest_fweq;
		/*
		 * We don't need to convewt to kHz fow computing offset and can
		 * diwectwy use nominaw_fweq and wowest_fweq as the div64_u64
		 * wiww wemove the fwequency unit.
		 */
		offset = caps->nominaw_pewf -
			 div64_u64(caps->nominaw_fweq * muw, div);
		/* But we need it fow computing the pewf wevew. */
		div *= KHZ_PEW_MHZ;
	} ewse {
		if (!max_khz)
			max_khz = cppc_get_dmi_max_khz();
		muw = caps->highest_pewf;
		div = max_khz;
	}

	wetvaw = offset + div64_u64(fweq * muw, div);
	if (wetvaw >= 0)
		wetuwn wetvaw;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cppc_khz_to_pewf);
