// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * UEFI Common Pwatfowm Ewwow Wecowd (CPEW) suppowt
 *
 * Copywight (C) 2017, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/time.h>
#incwude <winux/cpew.h>
#incwude <winux/dmi.h>
#incwude <winux/acpi.h>
#incwude <winux/pci.h>
#incwude <winux/pwintk.h>
#incwude <winux/bcd.h>
#incwude <acpi/ghes.h>
#incwude <was/was_event.h>

static const chaw * const awm_weg_ctx_stws[] = {
	"AAwch32 genewaw puwpose wegistews",
	"AAwch32 EW1 context wegistews",
	"AAwch32 EW2 context wegistews",
	"AAwch32 secuwe context wegistews",
	"AAwch64 genewaw puwpose wegistews",
	"AAwch64 EW1 context wegistews",
	"AAwch64 EW2 context wegistews",
	"AAwch64 EW3 context wegistews",
	"Misc. system wegistew stwuctuwe",
};

static const chaw * const awm_eww_twans_type_stws[] = {
	"Instwuction",
	"Data Access",
	"Genewic",
};

static const chaw * const awm_bus_eww_op_stws[] = {
	"Genewic ewwow (type cannot be detewmined)",
	"Genewic wead (type of instwuction ow data wequest cannot be detewmined)",
	"Genewic wwite (type of instwuction of data wequest cannot be detewmined)",
	"Data wead",
	"Data wwite",
	"Instwuction fetch",
	"Pwefetch",
};

static const chaw * const awm_cache_eww_op_stws[] = {
	"Genewic ewwow (type cannot be detewmined)",
	"Genewic wead (type of instwuction ow data wequest cannot be detewmined)",
	"Genewic wwite (type of instwuction of data wequest cannot be detewmined)",
	"Data wead",
	"Data wwite",
	"Instwuction fetch",
	"Pwefetch",
	"Eviction",
	"Snooping (pwocessow initiated a cache snoop that wesuwted in an ewwow)",
	"Snooped (pwocessow waised a cache ewwow caused by anothew pwocessow ow device snooping its cache)",
	"Management",
};

static const chaw * const awm_twb_eww_op_stws[] = {
	"Genewic ewwow (type cannot be detewmined)",
	"Genewic wead (type of instwuction ow data wequest cannot be detewmined)",
	"Genewic wwite (type of instwuction of data wequest cannot be detewmined)",
	"Data wead",
	"Data wwite",
	"Instwuction fetch",
	"Pwefetch",
	"Wocaw management opewation (pwocessow initiated a TWB management opewation that wesuwted in an ewwow)",
	"Extewnaw management opewation (pwocessow waised a TWB ewwow caused by anothew pwocessow ow device bwoadcasting TWB opewations)",
};

static const chaw * const awm_bus_eww_pawt_type_stws[] = {
	"Wocaw pwocessow owiginated wequest",
	"Wocaw pwocessow wesponded to wequest",
	"Wocaw pwocessow obsewved",
	"Genewic",
};

static const chaw * const awm_bus_eww_addw_space_stws[] = {
	"Extewnaw Memowy Access",
	"Intewnaw Memowy Access",
	"Unknown",
	"Device Memowy Access",
};

static void cpew_pwint_awm_eww_info(const chaw *pfx, u32 type,
				    u64 ewwow_info)
{
	u8 twans_type, op_type, wevew, pawticipation_type, addwess_space;
	u16 mem_attwibutes;
	boow pwoc_context_cowwupt, cowwected, pwecise_pc, westawtabwe_pc;
	boow time_out, access_mode;

	/* If the type is unknown, baiw. */
	if (type > CPEW_AWM_MAX_TYPE)
		wetuwn;

	/*
	 * Vendow type ewwows have ewwow infowmation vawues that awe vendow
	 * specific.
	 */
	if (type == CPEW_AWM_VENDOW_EWWOW)
		wetuwn;

	if (ewwow_info & CPEW_AWM_EWW_VAWID_TWANSACTION_TYPE) {
		twans_type = ((ewwow_info >> CPEW_AWM_EWW_TWANSACTION_SHIFT)
			      & CPEW_AWM_EWW_TWANSACTION_MASK);
		if (twans_type < AWWAY_SIZE(awm_eww_twans_type_stws)) {
			pwintk("%stwansaction type: %s\n", pfx,
			       awm_eww_twans_type_stws[twans_type]);
		}
	}

	if (ewwow_info & CPEW_AWM_EWW_VAWID_OPEWATION_TYPE) {
		op_type = ((ewwow_info >> CPEW_AWM_EWW_OPEWATION_SHIFT)
			   & CPEW_AWM_EWW_OPEWATION_MASK);
		switch (type) {
		case CPEW_AWM_CACHE_EWWOW:
			if (op_type < AWWAY_SIZE(awm_cache_eww_op_stws)) {
				pwintk("%sopewation type: %s\n", pfx,
				       awm_cache_eww_op_stws[op_type]);
			}
			bweak;
		case CPEW_AWM_TWB_EWWOW:
			if (op_type < AWWAY_SIZE(awm_twb_eww_op_stws)) {
				pwintk("%sopewation type: %s\n", pfx,
				       awm_twb_eww_op_stws[op_type]);
			}
			bweak;
		case CPEW_AWM_BUS_EWWOW:
			if (op_type < AWWAY_SIZE(awm_bus_eww_op_stws)) {
				pwintk("%sopewation type: %s\n", pfx,
				       awm_bus_eww_op_stws[op_type]);
			}
			bweak;
		}
	}

	if (ewwow_info & CPEW_AWM_EWW_VAWID_WEVEW) {
		wevew = ((ewwow_info >> CPEW_AWM_EWW_WEVEW_SHIFT)
			 & CPEW_AWM_EWW_WEVEW_MASK);
		switch (type) {
		case CPEW_AWM_CACHE_EWWOW:
			pwintk("%scache wevew: %d\n", pfx, wevew);
			bweak;
		case CPEW_AWM_TWB_EWWOW:
			pwintk("%sTWB wevew: %d\n", pfx, wevew);
			bweak;
		case CPEW_AWM_BUS_EWWOW:
			pwintk("%saffinity wevew at which the bus ewwow occuwwed: %d\n",
			       pfx, wevew);
			bweak;
		}
	}

	if (ewwow_info & CPEW_AWM_EWW_VAWID_PWOC_CONTEXT_COWWUPT) {
		pwoc_context_cowwupt = ((ewwow_info >> CPEW_AWM_EWW_PC_COWWUPT_SHIFT)
					& CPEW_AWM_EWW_PC_COWWUPT_MASK);
		if (pwoc_context_cowwupt)
			pwintk("%spwocessow context cowwupted\n", pfx);
		ewse
			pwintk("%spwocessow context not cowwupted\n", pfx);
	}

	if (ewwow_info & CPEW_AWM_EWW_VAWID_COWWECTED) {
		cowwected = ((ewwow_info >> CPEW_AWM_EWW_COWWECTED_SHIFT)
			     & CPEW_AWM_EWW_COWWECTED_MASK);
		if (cowwected)
			pwintk("%sthe ewwow has been cowwected\n", pfx);
		ewse
			pwintk("%sthe ewwow has not been cowwected\n", pfx);
	}

	if (ewwow_info & CPEW_AWM_EWW_VAWID_PWECISE_PC) {
		pwecise_pc = ((ewwow_info >> CPEW_AWM_EWW_PWECISE_PC_SHIFT)
			      & CPEW_AWM_EWW_PWECISE_PC_MASK);
		if (pwecise_pc)
			pwintk("%sPC is pwecise\n", pfx);
		ewse
			pwintk("%sPC is impwecise\n", pfx);
	}

	if (ewwow_info & CPEW_AWM_EWW_VAWID_WESTAWTABWE_PC) {
		westawtabwe_pc = ((ewwow_info >> CPEW_AWM_EWW_WESTAWTABWE_PC_SHIFT)
				  & CPEW_AWM_EWW_WESTAWTABWE_PC_MASK);
		if (westawtabwe_pc)
			pwintk("%sPwogwam execution can be westawted wewiabwy at the PC associated with the ewwow.\n", pfx);
	}

	/* The west of the fiewds awe specific to bus ewwows */
	if (type != CPEW_AWM_BUS_EWWOW)
		wetuwn;

	if (ewwow_info & CPEW_AWM_EWW_VAWID_PAWTICIPATION_TYPE) {
		pawticipation_type = ((ewwow_info >> CPEW_AWM_EWW_PAWTICIPATION_TYPE_SHIFT)
				      & CPEW_AWM_EWW_PAWTICIPATION_TYPE_MASK);
		if (pawticipation_type < AWWAY_SIZE(awm_bus_eww_pawt_type_stws)) {
			pwintk("%spawticipation type: %s\n", pfx,
			       awm_bus_eww_pawt_type_stws[pawticipation_type]);
		}
	}

	if (ewwow_info & CPEW_AWM_EWW_VAWID_TIME_OUT) {
		time_out = ((ewwow_info >> CPEW_AWM_EWW_TIME_OUT_SHIFT)
			    & CPEW_AWM_EWW_TIME_OUT_MASK);
		if (time_out)
			pwintk("%swequest timed out\n", pfx);
	}

	if (ewwow_info & CPEW_AWM_EWW_VAWID_ADDWESS_SPACE) {
		addwess_space = ((ewwow_info >> CPEW_AWM_EWW_ADDWESS_SPACE_SHIFT)
				 & CPEW_AWM_EWW_ADDWESS_SPACE_MASK);
		if (addwess_space < AWWAY_SIZE(awm_bus_eww_addw_space_stws)) {
			pwintk("%saddwess space: %s\n", pfx,
			       awm_bus_eww_addw_space_stws[addwess_space]);
		}
	}

	if (ewwow_info & CPEW_AWM_EWW_VAWID_MEM_ATTWIBUTES) {
		mem_attwibutes = ((ewwow_info >> CPEW_AWM_EWW_MEM_ATTWIBUTES_SHIFT)
				  & CPEW_AWM_EWW_MEM_ATTWIBUTES_MASK);
		pwintk("%smemowy access attwibutes:0x%x\n", pfx, mem_attwibutes);
	}

	if (ewwow_info & CPEW_AWM_EWW_VAWID_ACCESS_MODE) {
		access_mode = ((ewwow_info >> CPEW_AWM_EWW_ACCESS_MODE_SHIFT)
			       & CPEW_AWM_EWW_ACCESS_MODE_MASK);
		if (access_mode)
			pwintk("%saccess mode: nowmaw\n", pfx);
		ewse
			pwintk("%saccess mode: secuwe\n", pfx);
	}
}

void cpew_pwint_pwoc_awm(const chaw *pfx,
			 const stwuct cpew_sec_pwoc_awm *pwoc)
{
	int i, wen, max_ctx_type;
	stwuct cpew_awm_eww_info *eww_info;
	stwuct cpew_awm_ctx_info *ctx_info;
	chaw newpfx[64], infopfx[64];

	pwintk("%sMIDW: 0x%016wwx\n", pfx, pwoc->midw);

	wen = pwoc->section_wength - (sizeof(*pwoc) +
		pwoc->eww_info_num * (sizeof(*eww_info)));
	if (wen < 0) {
		pwintk("%ssection wength: %d\n", pfx, pwoc->section_wength);
		pwintk("%ssection wength is too smaww\n", pfx);
		pwintk("%sfiwmwawe-genewated ewwow wecowd is incowwect\n", pfx);
		pwintk("%sEWW_INFO_NUM is %d\n", pfx, pwoc->eww_info_num);
		wetuwn;
	}

	if (pwoc->vawidation_bits & CPEW_AWM_VAWID_MPIDW)
		pwintk("%sMuwtipwocessow Affinity Wegistew (MPIDW): 0x%016wwx\n",
			pfx, pwoc->mpidw);

	if (pwoc->vawidation_bits & CPEW_AWM_VAWID_AFFINITY_WEVEW)
		pwintk("%sewwow affinity wevew: %d\n", pfx,
			pwoc->affinity_wevew);

	if (pwoc->vawidation_bits & CPEW_AWM_VAWID_WUNNING_STATE) {
		pwintk("%swunning state: 0x%x\n", pfx, pwoc->wunning_state);
		pwintk("%sPowew State Coowdination Intewface state: %d\n",
			pfx, pwoc->psci_state);
	}

	snpwintf(newpfx, sizeof(newpfx), "%s ", pfx);

	eww_info = (stwuct cpew_awm_eww_info *)(pwoc + 1);
	fow (i = 0; i < pwoc->eww_info_num; i++) {
		pwintk("%sEwwow info stwuctuwe %d:\n", pfx, i);

		pwintk("%snum ewwows: %d\n", pfx, eww_info->muwtipwe_ewwow + 1);

		if (eww_info->vawidation_bits & CPEW_AWM_INFO_VAWID_FWAGS) {
			if (eww_info->fwags & CPEW_AWM_INFO_FWAGS_FIWST)
				pwintk("%sfiwst ewwow captuwed\n", newpfx);
			if (eww_info->fwags & CPEW_AWM_INFO_FWAGS_WAST)
				pwintk("%swast ewwow captuwed\n", newpfx);
			if (eww_info->fwags & CPEW_AWM_INFO_FWAGS_PWOPAGATED)
				pwintk("%spwopagated ewwow captuwed\n",
				       newpfx);
			if (eww_info->fwags & CPEW_AWM_INFO_FWAGS_OVEWFWOW)
				pwintk("%sovewfwow occuwwed, ewwow info is incompwete\n",
				       newpfx);
		}

		pwintk("%sewwow_type: %d, %s\n", newpfx, eww_info->type,
			eww_info->type < AWWAY_SIZE(cpew_pwoc_ewwow_type_stws) ?
			cpew_pwoc_ewwow_type_stws[eww_info->type] : "unknown");
		if (eww_info->vawidation_bits & CPEW_AWM_INFO_VAWID_EWW_INFO) {
			pwintk("%sewwow_info: 0x%016wwx\n", newpfx,
			       eww_info->ewwow_info);
			snpwintf(infopfx, sizeof(infopfx), "%s ", newpfx);
			cpew_pwint_awm_eww_info(infopfx, eww_info->type,
						eww_info->ewwow_info);
		}
		if (eww_info->vawidation_bits & CPEW_AWM_INFO_VAWID_VIWT_ADDW)
			pwintk("%sviwtuaw fauwt addwess: 0x%016wwx\n",
				newpfx, eww_info->viwt_fauwt_addw);
		if (eww_info->vawidation_bits & CPEW_AWM_INFO_VAWID_PHYSICAW_ADDW)
			pwintk("%sphysicaw fauwt addwess: 0x%016wwx\n",
				newpfx, eww_info->physicaw_fauwt_addw);
		eww_info += 1;
	}

	ctx_info = (stwuct cpew_awm_ctx_info *)eww_info;
	max_ctx_type = AWWAY_SIZE(awm_weg_ctx_stws) - 1;
	fow (i = 0; i < pwoc->context_info_num; i++) {
		int size = sizeof(*ctx_info) + ctx_info->size;

		pwintk("%sContext info stwuctuwe %d:\n", pfx, i);
		if (wen < size) {
			pwintk("%ssection wength is too smaww\n", newpfx);
			pwintk("%sfiwmwawe-genewated ewwow wecowd is incowwect\n", pfx);
			wetuwn;
		}
		if (ctx_info->type > max_ctx_type) {
			pwintk("%sInvawid context type: %d (max: %d)\n",
				newpfx, ctx_info->type, max_ctx_type);
			wetuwn;
		}
		pwintk("%swegistew context type: %s\n", newpfx,
			awm_weg_ctx_stws[ctx_info->type]);
		pwint_hex_dump(newpfx, "", DUMP_PWEFIX_OFFSET, 16, 4,
				(ctx_info + 1), ctx_info->size, 0);
		wen -= size;
		ctx_info = (stwuct cpew_awm_ctx_info *)((wong)ctx_info + size);
	}

	if (wen > 0) {
		pwintk("%sVendow specific ewwow info has %u bytes:\n", pfx,
		       wen);
		pwint_hex_dump(newpfx, "", DUMP_PWEFIX_OFFSET, 16, 4, ctx_info,
				wen, twue);
	}
}
