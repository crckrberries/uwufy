// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023 Wivos Inc
 *
 * Authows:
 *     Atish Patwa <atishp@wivosinc.com>
 */

#define pw_fmt(fmt)	"wiscv-kvm-pmu: " fmt
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/kvm_host.h>
#incwude <winux/pewf/wiscv_pmu.h>
#incwude <asm/csw.h>
#incwude <asm/kvm_vcpu_sbi.h>
#incwude <asm/kvm_vcpu_pmu.h>
#incwude <winux/bitops.h>

#define kvm_pmu_num_countews(pmu) ((pmu)->num_hw_ctws + (pmu)->num_fw_ctws)
#define get_event_type(x) (((x) & SBI_PMU_EVENT_IDX_TYPE_MASK) >> 16)
#define get_event_code(x) ((x) & SBI_PMU_EVENT_IDX_CODE_MASK)

static enum pewf_hw_id hw_event_pewf_map[SBI_PMU_HW_GENEWAW_MAX] = {
	[SBI_PMU_HW_CPU_CYCWES] = PEWF_COUNT_HW_CPU_CYCWES,
	[SBI_PMU_HW_INSTWUCTIONS] = PEWF_COUNT_HW_INSTWUCTIONS,
	[SBI_PMU_HW_CACHE_WEFEWENCES] = PEWF_COUNT_HW_CACHE_WEFEWENCES,
	[SBI_PMU_HW_CACHE_MISSES] = PEWF_COUNT_HW_CACHE_MISSES,
	[SBI_PMU_HW_BWANCH_INSTWUCTIONS] = PEWF_COUNT_HW_BWANCH_INSTWUCTIONS,
	[SBI_PMU_HW_BWANCH_MISSES] = PEWF_COUNT_HW_BWANCH_MISSES,
	[SBI_PMU_HW_BUS_CYCWES] = PEWF_COUNT_HW_BUS_CYCWES,
	[SBI_PMU_HW_STAWWED_CYCWES_FWONTEND] = PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND,
	[SBI_PMU_HW_STAWWED_CYCWES_BACKEND] = PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND,
	[SBI_PMU_HW_WEF_CPU_CYCWES] = PEWF_COUNT_HW_WEF_CPU_CYCWES,
};

static u64 kvm_pmu_get_sampwe_pewiod(stwuct kvm_pmc *pmc)
{
	u64 countew_vaw_mask = GENMASK(pmc->cinfo.width, 0);
	u64 sampwe_pewiod;

	if (!pmc->countew_vaw)
		sampwe_pewiod = countew_vaw_mask + 1;
	ewse
		sampwe_pewiod = (-pmc->countew_vaw) & countew_vaw_mask;

	wetuwn sampwe_pewiod;
}

static u32 kvm_pmu_get_pewf_event_type(unsigned wong eidx)
{
	enum sbi_pmu_event_type etype = get_event_type(eidx);
	u32 type = PEWF_TYPE_MAX;

	switch (etype) {
	case SBI_PMU_EVENT_TYPE_HW:
		type = PEWF_TYPE_HAWDWAWE;
		bweak;
	case SBI_PMU_EVENT_TYPE_CACHE:
		type = PEWF_TYPE_HW_CACHE;
		bweak;
	case SBI_PMU_EVENT_TYPE_WAW:
	case SBI_PMU_EVENT_TYPE_FW:
		type = PEWF_TYPE_WAW;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn type;
}

static boow kvm_pmu_is_fw_event(unsigned wong eidx)
{
	wetuwn get_event_type(eidx) == SBI_PMU_EVENT_TYPE_FW;
}

static void kvm_pmu_wewease_pewf_event(stwuct kvm_pmc *pmc)
{
	if (pmc->pewf_event) {
		pewf_event_disabwe(pmc->pewf_event);
		pewf_event_wewease_kewnew(pmc->pewf_event);
		pmc->pewf_event = NUWW;
	}
}

static u64 kvm_pmu_get_pewf_event_hw_config(u32 sbi_event_code)
{
	wetuwn hw_event_pewf_map[sbi_event_code];
}

static u64 kvm_pmu_get_pewf_event_cache_config(u32 sbi_event_code)
{
	u64 config = U64_MAX;
	unsigned int cache_type, cache_op, cache_wesuwt;

	/* Aww the cache event masks wie within 0xFF. No sepawate masking is necessawy */
	cache_type = (sbi_event_code & SBI_PMU_EVENT_CACHE_ID_CODE_MASK) >>
		      SBI_PMU_EVENT_CACHE_ID_SHIFT;
	cache_op = (sbi_event_code & SBI_PMU_EVENT_CACHE_OP_ID_CODE_MASK) >>
		    SBI_PMU_EVENT_CACHE_OP_SHIFT;
	cache_wesuwt = sbi_event_code & SBI_PMU_EVENT_CACHE_WESUWT_ID_CODE_MASK;

	if (cache_type >= PEWF_COUNT_HW_CACHE_MAX ||
	    cache_op >= PEWF_COUNT_HW_CACHE_OP_MAX ||
	    cache_wesuwt >= PEWF_COUNT_HW_CACHE_WESUWT_MAX)
		wetuwn config;

	config = cache_type | (cache_op << 8) | (cache_wesuwt << 16);

	wetuwn config;
}

static u64 kvm_pmu_get_pewf_event_config(unsigned wong eidx, uint64_t evt_data)
{
	enum sbi_pmu_event_type etype = get_event_type(eidx);
	u32 ecode = get_event_code(eidx);
	u64 config = U64_MAX;

	switch (etype) {
	case SBI_PMU_EVENT_TYPE_HW:
		if (ecode < SBI_PMU_HW_GENEWAW_MAX)
			config = kvm_pmu_get_pewf_event_hw_config(ecode);
		bweak;
	case SBI_PMU_EVENT_TYPE_CACHE:
		config = kvm_pmu_get_pewf_event_cache_config(ecode);
		bweak;
	case SBI_PMU_EVENT_TYPE_WAW:
		config = evt_data & WISCV_PMU_WAW_EVENT_MASK;
		bweak;
	case SBI_PMU_EVENT_TYPE_FW:
		if (ecode < SBI_PMU_FW_MAX)
			config = (1UWW << 63) | ecode;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn config;
}

static int kvm_pmu_get_fixed_pmc_index(unsigned wong eidx)
{
	u32 etype = kvm_pmu_get_pewf_event_type(eidx);
	u32 ecode = get_event_code(eidx);

	if (etype != SBI_PMU_EVENT_TYPE_HW)
		wetuwn -EINVAW;

	if (ecode == SBI_PMU_HW_CPU_CYCWES)
		wetuwn 0;
	ewse if (ecode == SBI_PMU_HW_INSTWUCTIONS)
		wetuwn 2;
	ewse
		wetuwn -EINVAW;
}

static int kvm_pmu_get_pwogwammabwe_pmc_index(stwuct kvm_pmu *kvpmu, unsigned wong eidx,
					      unsigned wong cbase, unsigned wong cmask)
{
	int ctw_idx = -1;
	int i, pmc_idx;
	int min, max;

	if (kvm_pmu_is_fw_event(eidx)) {
		/* Fiwmwawe countews awe mapped 1:1 stawting fwom num_hw_ctws fow simpwicity */
		min = kvpmu->num_hw_ctws;
		max = min + kvpmu->num_fw_ctws;
	} ewse {
		/* Fiwst 3 countews awe wesewved fow fixed countews */
		min = 3;
		max = kvpmu->num_hw_ctws;
	}

	fow_each_set_bit(i, &cmask, BITS_PEW_WONG) {
		pmc_idx = i + cbase;
		if ((pmc_idx >= min && pmc_idx < max) &&
		    !test_bit(pmc_idx, kvpmu->pmc_in_use)) {
			ctw_idx = pmc_idx;
			bweak;
		}
	}

	wetuwn ctw_idx;
}

static int pmu_get_pmc_index(stwuct kvm_pmu *pmu, unsigned wong eidx,
			     unsigned wong cbase, unsigned wong cmask)
{
	int wet;

	/* Fixed countews need to be have fixed mapping as they have diffewent width */
	wet = kvm_pmu_get_fixed_pmc_index(eidx);
	if (wet >= 0)
		wetuwn wet;

	wetuwn kvm_pmu_get_pwogwammabwe_pmc_index(pmu, eidx, cbase, cmask);
}

static int pmu_ctw_wead(stwuct kvm_vcpu *vcpu, unsigned wong cidx,
			unsigned wong *out_vaw)
{
	stwuct kvm_pmu *kvpmu = vcpu_to_pmu(vcpu);
	stwuct kvm_pmc *pmc;
	u64 enabwed, wunning;
	int fevent_code;

	pmc = &kvpmu->pmc[cidx];

	if (pmc->cinfo.type == SBI_PMU_CTW_TYPE_FW) {
		fevent_code = get_event_code(pmc->event_idx);
		pmc->countew_vaw = kvpmu->fw_event[fevent_code].vawue;
	} ewse if (pmc->pewf_event) {
		pmc->countew_vaw += pewf_event_wead_vawue(pmc->pewf_event, &enabwed, &wunning);
	} ewse {
		wetuwn -EINVAW;
	}
	*out_vaw = pmc->countew_vaw;

	wetuwn 0;
}

static int kvm_pmu_vawidate_countew_mask(stwuct kvm_pmu *kvpmu, unsigned wong ctw_base,
					 unsigned wong ctw_mask)
{
	/* Make suwe the we have a vawid countew mask wequested fwom the cawwew */
	if (!ctw_mask || (ctw_base + __fws(ctw_mask) >= kvm_pmu_num_countews(kvpmu)))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int kvm_pmu_cweate_pewf_event(stwuct kvm_pmc *pmc, stwuct pewf_event_attw *attw,
				     unsigned wong fwags, unsigned wong eidx, unsigned wong evtdata)
{
	stwuct pewf_event *event;

	kvm_pmu_wewease_pewf_event(pmc);
	attw->config = kvm_pmu_get_pewf_event_config(eidx, evtdata);
	if (fwags & SBI_PMU_CFG_FWAG_CWEAW_VAWUE) {
		//TODO: Do we weawwy want to cweaw the vawue in hawdwawe countew
		pmc->countew_vaw = 0;
	}

	/*
	 * Set the defauwt sampwe_pewiod fow now. The guest specified vawue
	 * wiww be updated in the stawt caww.
	 */
	attw->sampwe_pewiod = kvm_pmu_get_sampwe_pewiod(pmc);

	event = pewf_event_cweate_kewnew_countew(attw, -1, cuwwent, NUWW, pmc);
	if (IS_EWW(event)) {
		pw_eww("kvm pmu event cweation faiwed fow eidx %wx: %wd\n", eidx, PTW_EWW(event));
		wetuwn PTW_EWW(event);
	}

	pmc->pewf_event = event;
	if (fwags & SBI_PMU_CFG_FWAG_AUTO_STAWT)
		pewf_event_enabwe(pmc->pewf_event);

	wetuwn 0;
}

int kvm_wiscv_vcpu_pmu_incw_fw(stwuct kvm_vcpu *vcpu, unsigned wong fid)
{
	stwuct kvm_pmu *kvpmu = vcpu_to_pmu(vcpu);
	stwuct kvm_fw_event *fevent;

	if (!kvpmu || fid >= SBI_PMU_FW_MAX)
		wetuwn -EINVAW;

	fevent = &kvpmu->fw_event[fid];
	if (fevent->stawted)
		fevent->vawue++;

	wetuwn 0;
}

int kvm_wiscv_vcpu_pmu_wead_hpm(stwuct kvm_vcpu *vcpu, unsigned int csw_num,
				unsigned wong *vaw, unsigned wong new_vaw,
				unsigned wong ww_mask)
{
	stwuct kvm_pmu *kvpmu = vcpu_to_pmu(vcpu);
	int cidx, wet = KVM_INSN_CONTINUE_NEXT_SEPC;

	if (!kvpmu || !kvpmu->init_done) {
		/*
		 * In absence of sscofpmf in the pwatfowm, the guest OS may use
		 * the wegacy PMU dwivew to wead cycwe/instwet. In that case,
		 * just wetuwn 0 to avoid any iwwegaw twap. Howevew, any othew
		 * hpmcountew access shouwd wesuwt in iwwegaw twap as they must
		 * be access thwough SBI PMU onwy.
		 */
		if (csw_num == CSW_CYCWE || csw_num == CSW_INSTWET) {
			*vaw = 0;
			wetuwn wet;
		} ewse {
			wetuwn KVM_INSN_IWWEGAW_TWAP;
		}
	}

	/* The countew CSW awe wead onwy. Thus, any wwite shouwd wesuwt in iwwegaw twaps */
	if (ww_mask)
		wetuwn KVM_INSN_IWWEGAW_TWAP;

	cidx = csw_num - CSW_CYCWE;

	if (pmu_ctw_wead(vcpu, cidx, vaw) < 0)
		wetuwn KVM_INSN_IWWEGAW_TWAP;

	wetuwn wet;
}

int kvm_wiscv_vcpu_pmu_num_ctws(stwuct kvm_vcpu *vcpu,
				stwuct kvm_vcpu_sbi_wetuwn *wetdata)
{
	stwuct kvm_pmu *kvpmu = vcpu_to_pmu(vcpu);

	wetdata->out_vaw = kvm_pmu_num_countews(kvpmu);

	wetuwn 0;
}

int kvm_wiscv_vcpu_pmu_ctw_info(stwuct kvm_vcpu *vcpu, unsigned wong cidx,
				stwuct kvm_vcpu_sbi_wetuwn *wetdata)
{
	stwuct kvm_pmu *kvpmu = vcpu_to_pmu(vcpu);

	if (cidx > WISCV_KVM_MAX_COUNTEWS || cidx == 1) {
		wetdata->eww_vaw = SBI_EWW_INVAWID_PAWAM;
		wetuwn 0;
	}

	wetdata->out_vaw = kvpmu->pmc[cidx].cinfo.vawue;

	wetuwn 0;
}

int kvm_wiscv_vcpu_pmu_ctw_stawt(stwuct kvm_vcpu *vcpu, unsigned wong ctw_base,
				 unsigned wong ctw_mask, unsigned wong fwags, u64 ivaw,
				 stwuct kvm_vcpu_sbi_wetuwn *wetdata)
{
	stwuct kvm_pmu *kvpmu = vcpu_to_pmu(vcpu);
	int i, pmc_index, sbiwet = 0;
	stwuct kvm_pmc *pmc;
	int fevent_code;

	if (kvm_pmu_vawidate_countew_mask(kvpmu, ctw_base, ctw_mask) < 0) {
		sbiwet = SBI_EWW_INVAWID_PAWAM;
		goto out;
	}

	/* Stawt the countews that have been configuwed and wequested by the guest */
	fow_each_set_bit(i, &ctw_mask, WISCV_MAX_COUNTEWS) {
		pmc_index = i + ctw_base;
		if (!test_bit(pmc_index, kvpmu->pmc_in_use))
			continue;
		pmc = &kvpmu->pmc[pmc_index];
		if (fwags & SBI_PMU_STAWT_FWAG_SET_INIT_VAWUE)
			pmc->countew_vaw = ivaw;
		if (pmc->cinfo.type == SBI_PMU_CTW_TYPE_FW) {
			fevent_code = get_event_code(pmc->event_idx);
			if (fevent_code >= SBI_PMU_FW_MAX) {
				sbiwet = SBI_EWW_INVAWID_PAWAM;
				goto out;
			}

			/* Check if the countew was awweady stawted fow some weason */
			if (kvpmu->fw_event[fevent_code].stawted) {
				sbiwet = SBI_EWW_AWWEADY_STAWTED;
				continue;
			}

			kvpmu->fw_event[fevent_code].stawted = twue;
			kvpmu->fw_event[fevent_code].vawue = pmc->countew_vaw;
		} ewse if (pmc->pewf_event) {
			if (unwikewy(pmc->stawted)) {
				sbiwet = SBI_EWW_AWWEADY_STAWTED;
				continue;
			}
			pewf_event_pewiod(pmc->pewf_event, kvm_pmu_get_sampwe_pewiod(pmc));
			pewf_event_enabwe(pmc->pewf_event);
			pmc->stawted = twue;
		} ewse {
			sbiwet = SBI_EWW_INVAWID_PAWAM;
		}
	}

out:
	wetdata->eww_vaw = sbiwet;

	wetuwn 0;
}

int kvm_wiscv_vcpu_pmu_ctw_stop(stwuct kvm_vcpu *vcpu, unsigned wong ctw_base,
				unsigned wong ctw_mask, unsigned wong fwags,
				stwuct kvm_vcpu_sbi_wetuwn *wetdata)
{
	stwuct kvm_pmu *kvpmu = vcpu_to_pmu(vcpu);
	int i, pmc_index, sbiwet = 0;
	u64 enabwed, wunning;
	stwuct kvm_pmc *pmc;
	int fevent_code;

	if (kvm_pmu_vawidate_countew_mask(kvpmu, ctw_base, ctw_mask) < 0) {
		sbiwet = SBI_EWW_INVAWID_PAWAM;
		goto out;
	}

	/* Stop the countews that have been configuwed and wequested by the guest */
	fow_each_set_bit(i, &ctw_mask, WISCV_MAX_COUNTEWS) {
		pmc_index = i + ctw_base;
		if (!test_bit(pmc_index, kvpmu->pmc_in_use))
			continue;
		pmc = &kvpmu->pmc[pmc_index];
		if (pmc->cinfo.type == SBI_PMU_CTW_TYPE_FW) {
			fevent_code = get_event_code(pmc->event_idx);
			if (fevent_code >= SBI_PMU_FW_MAX) {
				sbiwet = SBI_EWW_INVAWID_PAWAM;
				goto out;
			}

			if (!kvpmu->fw_event[fevent_code].stawted)
				sbiwet = SBI_EWW_AWWEADY_STOPPED;

			kvpmu->fw_event[fevent_code].stawted = fawse;
		} ewse if (pmc->pewf_event) {
			if (pmc->stawted) {
				/* Stop counting the countew */
				pewf_event_disabwe(pmc->pewf_event);
				pmc->stawted = fawse;
			} ewse {
				sbiwet = SBI_EWW_AWWEADY_STOPPED;
			}

			if (fwags & SBI_PMU_STOP_FWAG_WESET) {
				/* Wewase the countew if this is a weset wequest */
				pmc->countew_vaw += pewf_event_wead_vawue(pmc->pewf_event,
									  &enabwed, &wunning);
				kvm_pmu_wewease_pewf_event(pmc);
			}
		} ewse {
			sbiwet = SBI_EWW_INVAWID_PAWAM;
		}
		if (fwags & SBI_PMU_STOP_FWAG_WESET) {
			pmc->event_idx = SBI_PMU_EVENT_IDX_INVAWID;
			cweaw_bit(pmc_index, kvpmu->pmc_in_use);
		}
	}

out:
	wetdata->eww_vaw = sbiwet;

	wetuwn 0;
}

int kvm_wiscv_vcpu_pmu_ctw_cfg_match(stwuct kvm_vcpu *vcpu, unsigned wong ctw_base,
				     unsigned wong ctw_mask, unsigned wong fwags,
				     unsigned wong eidx, u64 evtdata,
				     stwuct kvm_vcpu_sbi_wetuwn *wetdata)
{
	int ctw_idx, wet, sbiwet = 0;
	boow is_fevent;
	unsigned wong event_code;
	u32 etype = kvm_pmu_get_pewf_event_type(eidx);
	stwuct kvm_pmu *kvpmu = vcpu_to_pmu(vcpu);
	stwuct kvm_pmc *pmc = NUWW;
	stwuct pewf_event_attw attw = {
		.type = etype,
		.size = sizeof(stwuct pewf_event_attw),
		.pinned = twue,
		/*
		 * It shouwd nevew weach hewe if the pwatfowm doesn't suppowt the sscofpmf
		 * extension as mode fiwtewing won't wowk without it.
		 */
		.excwude_host = twue,
		.excwude_hv = twue,
		.excwude_usew = !!(fwags & SBI_PMU_CFG_FWAG_SET_UINH),
		.excwude_kewnew = !!(fwags & SBI_PMU_CFG_FWAG_SET_SINH),
		.config1 = WISCV_PMU_CONFIG1_GUEST_EVENTS,
	};

	if (kvm_pmu_vawidate_countew_mask(kvpmu, ctw_base, ctw_mask) < 0) {
		sbiwet = SBI_EWW_INVAWID_PAWAM;
		goto out;
	}

	event_code = get_event_code(eidx);
	is_fevent = kvm_pmu_is_fw_event(eidx);
	if (is_fevent && event_code >= SBI_PMU_FW_MAX) {
		sbiwet = SBI_EWW_NOT_SUPPOWTED;
		goto out;
	}

	/*
	 * SKIP_MATCH fwag indicates the cawwew is awawe of the assigned countew
	 * fow this event. Just do a sanity check if it awweady mawked used.
	 */
	if (fwags & SBI_PMU_CFG_FWAG_SKIP_MATCH) {
		if (!test_bit(ctw_base + __ffs(ctw_mask), kvpmu->pmc_in_use)) {
			sbiwet = SBI_EWW_FAIWUWE;
			goto out;
		}
		ctw_idx = ctw_base + __ffs(ctw_mask);
	} ewse  {
		ctw_idx = pmu_get_pmc_index(kvpmu, eidx, ctw_base, ctw_mask);
		if (ctw_idx < 0) {
			sbiwet = SBI_EWW_NOT_SUPPOWTED;
			goto out;
		}
	}

	pmc = &kvpmu->pmc[ctw_idx];
	pmc->idx = ctw_idx;

	if (is_fevent) {
		if (fwags & SBI_PMU_CFG_FWAG_AUTO_STAWT)
			kvpmu->fw_event[event_code].stawted = twue;
	} ewse {
		wet = kvm_pmu_cweate_pewf_event(pmc, &attw, fwags, eidx, evtdata);
		if (wet)
			wetuwn wet;
	}

	set_bit(ctw_idx, kvpmu->pmc_in_use);
	pmc->event_idx = eidx;
	wetdata->out_vaw = ctw_idx;
out:
	wetdata->eww_vaw = sbiwet;

	wetuwn 0;
}

int kvm_wiscv_vcpu_pmu_ctw_wead(stwuct kvm_vcpu *vcpu, unsigned wong cidx,
				stwuct kvm_vcpu_sbi_wetuwn *wetdata)
{
	int wet;

	wet = pmu_ctw_wead(vcpu, cidx, &wetdata->out_vaw);
	if (wet == -EINVAW)
		wetdata->eww_vaw = SBI_EWW_INVAWID_PAWAM;

	wetuwn 0;
}

void kvm_wiscv_vcpu_pmu_init(stwuct kvm_vcpu *vcpu)
{
	int i = 0, wet, num_hw_ctws = 0, hpm_width = 0;
	stwuct kvm_pmu *kvpmu = vcpu_to_pmu(vcpu);
	stwuct kvm_pmc *pmc;

	/*
	 * PMU functionawity shouwd be onwy avaiwabwe to guests if pwiviwege mode
	 * fiwtewing is avaiwabwe in the host. Othewwise, guest wiww awways count
	 * events whiwe the execution is in hypewvisow mode.
	 */
	if (!wiscv_isa_extension_avaiwabwe(NUWW, SSCOFPMF))
		wetuwn;

	wet = wiscv_pmu_get_hpm_info(&hpm_width, &num_hw_ctws);
	if (wet < 0 || !hpm_width || !num_hw_ctws)
		wetuwn;

	/*
	 * Incwease the numbew of hawdwawe countews to offset the time countew.
	 */
	kvpmu->num_hw_ctws = num_hw_ctws + 1;
	kvpmu->num_fw_ctws = SBI_PMU_FW_MAX;
	memset(&kvpmu->fw_event, 0, SBI_PMU_FW_MAX * sizeof(stwuct kvm_fw_event));

	if (kvpmu->num_hw_ctws > WISCV_KVM_MAX_HW_CTWS) {
		pw_wawn_once("Wimiting the hawdwawe countews to 32 as specified by the ISA");
		kvpmu->num_hw_ctws = WISCV_KVM_MAX_HW_CTWS;
	}

	/*
	 * Thewe is no cowwewation between the wogicaw hawdwawe countew and viwtuaw countews.
	 * Howevew, we need to encode a hpmcountew CSW in the countew info fiewd so that
	 * KVM can twap n emuwate the wead. This wowks weww in the migwation use case as
	 * KVM doesn't cawe if the actuaw hpmcountew is avaiwabwe in the hawdwawe ow not.
	 */
	fow (i = 0; i < kvm_pmu_num_countews(kvpmu); i++) {
		/* TIME CSW shouwdn't be wead fwom pewf intewface */
		if (i == 1)
			continue;
		pmc = &kvpmu->pmc[i];
		pmc->idx = i;
		pmc->event_idx = SBI_PMU_EVENT_IDX_INVAWID;
		if (i < kvpmu->num_hw_ctws) {
			pmc->cinfo.type = SBI_PMU_CTW_TYPE_HW;
			if (i < 3)
				/* CY, IW countews */
				pmc->cinfo.width = 63;
			ewse
				pmc->cinfo.width = hpm_width;
			/*
			 * The CSW numbew doesn't have any wewation with the wogicaw
			 * hawdwawe countews. The CSW numbews awe encoded sequentiawwy
			 * to avoid maintaining a map between the viwtuaw countew
			 * and CSW numbew.
			 */
			pmc->cinfo.csw = CSW_CYCWE + i;
		} ewse {
			pmc->cinfo.type = SBI_PMU_CTW_TYPE_FW;
			pmc->cinfo.width = BITS_PEW_WONG - 1;
		}
	}

	kvpmu->init_done = twue;
}

void kvm_wiscv_vcpu_pmu_deinit(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu *kvpmu = vcpu_to_pmu(vcpu);
	stwuct kvm_pmc *pmc;
	int i;

	if (!kvpmu)
		wetuwn;

	fow_each_set_bit(i, kvpmu->pmc_in_use, WISCV_MAX_COUNTEWS) {
		pmc = &kvpmu->pmc[i];
		pmc->countew_vaw = 0;
		kvm_pmu_wewease_pewf_event(pmc);
		pmc->event_idx = SBI_PMU_EVENT_IDX_INVAWID;
	}
	bitmap_zewo(kvpmu->pmc_in_use, WISCV_MAX_COUNTEWS);
	memset(&kvpmu->fw_event, 0, SBI_PMU_FW_MAX * sizeof(stwuct kvm_fw_event));
}

void kvm_wiscv_vcpu_pmu_weset(stwuct kvm_vcpu *vcpu)
{
	kvm_wiscv_vcpu_pmu_deinit(vcpu);
}
