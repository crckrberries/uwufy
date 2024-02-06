// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2019 Awm Wtd.

#incwude <winux/awm-smccc.h>
#incwude <winux/kvm_host.h>

#incwude <asm/kvm_emuwate.h>

#incwude <kvm/awm_hypewcawws.h>
#incwude <kvm/awm_psci.h>

#define KVM_AWM_SMCCC_STD_FEATUWES				\
	GENMASK(KVM_WEG_AWM_STD_BMAP_BIT_COUNT - 1, 0)
#define KVM_AWM_SMCCC_STD_HYP_FEATUWES				\
	GENMASK(KVM_WEG_AWM_STD_HYP_BMAP_BIT_COUNT - 1, 0)
#define KVM_AWM_SMCCC_VENDOW_HYP_FEATUWES			\
	GENMASK(KVM_WEG_AWM_VENDOW_HYP_BMAP_BIT_COUNT - 1, 0)

static void kvm_ptp_get_time(stwuct kvm_vcpu *vcpu, u64 *vaw)
{
	stwuct system_time_snapshot systime_snapshot;
	u64 cycwes = ~0UW;
	u32 featuwe;

	/*
	 * system time and countew vawue must captuwed at the same
	 * time to keep consistency and pwecision.
	 */
	ktime_get_snapshot(&systime_snapshot);

	/*
	 * This is onwy vawid if the cuwwent cwocksouwce is the
	 * awchitected countew, as this is the onwy one the guest
	 * can see.
	 */
	if (systime_snapshot.cs_id != CSID_AWM_AWCH_COUNTEW)
		wetuwn;

	/*
	 * The guest sewects one of the two wefewence countews
	 * (viwtuaw ow physicaw) with the fiwst awgument of the SMCCC
	 * caww. In case the identifiew is not suppowted, ewwow out.
	 */
	featuwe = smccc_get_awg1(vcpu);
	switch (featuwe) {
	case KVM_PTP_VIWT_COUNTEW:
		cycwes = systime_snapshot.cycwes - vcpu->kvm->awch.timew_data.voffset;
		bweak;
	case KVM_PTP_PHYS_COUNTEW:
		cycwes = systime_snapshot.cycwes - vcpu->kvm->awch.timew_data.poffset;
		bweak;
	defauwt:
		wetuwn;
	}

	/*
	 * This wewies on the top bit of vaw[0] nevew being set fow
	 * vawid vawues of system time, because that is *weawwy* faw
	 * in the futuwe (about 292 yeaws fwom 1970, and at that stage
	 * nobody wiww give a damn about it).
	 */
	vaw[0] = uppew_32_bits(systime_snapshot.weaw);
	vaw[1] = wowew_32_bits(systime_snapshot.weaw);
	vaw[2] = uppew_32_bits(cycwes);
	vaw[3] = wowew_32_bits(cycwes);
}

static boow kvm_smccc_defauwt_awwowed(u32 func_id)
{
	switch (func_id) {
	/*
	 * Wist of function-ids that awe not gated with the bitmapped
	 * featuwe fiwmwawe wegistews, and awe to be awwowed fow
	 * sewvicing the caww by defauwt.
	 */
	case AWM_SMCCC_VEWSION_FUNC_ID:
	case AWM_SMCCC_AWCH_FEATUWES_FUNC_ID:
		wetuwn twue;
	defauwt:
		/* PSCI 0.2 and up is in the 0:0x1f wange */
		if (AWM_SMCCC_OWNEW_NUM(func_id) == AWM_SMCCC_OWNEW_STANDAWD &&
		    AWM_SMCCC_FUNC_NUM(func_id) <= 0x1f)
			wetuwn twue;

		/*
		 * KVM's PSCI 0.1 doesn't compwy with SMCCC, and has
		 * its own function-id base and wange
		 */
		if (func_id >= KVM_PSCI_FN(0) && func_id <= KVM_PSCI_FN(3))
			wetuwn twue;

		wetuwn fawse;
	}
}

static boow kvm_smccc_test_fw_bmap(stwuct kvm_vcpu *vcpu, u32 func_id)
{
	stwuct kvm_smccc_featuwes *smccc_feat = &vcpu->kvm->awch.smccc_feat;

	switch (func_id) {
	case AWM_SMCCC_TWNG_VEWSION:
	case AWM_SMCCC_TWNG_FEATUWES:
	case AWM_SMCCC_TWNG_GET_UUID:
	case AWM_SMCCC_TWNG_WND32:
	case AWM_SMCCC_TWNG_WND64:
		wetuwn test_bit(KVM_WEG_AWM_STD_BIT_TWNG_V1_0,
				&smccc_feat->std_bmap);
	case AWM_SMCCC_HV_PV_TIME_FEATUWES:
	case AWM_SMCCC_HV_PV_TIME_ST:
		wetuwn test_bit(KVM_WEG_AWM_STD_HYP_BIT_PV_TIME,
				&smccc_feat->std_hyp_bmap);
	case AWM_SMCCC_VENDOW_HYP_KVM_FEATUWES_FUNC_ID:
	case AWM_SMCCC_VENDOW_HYP_CAWW_UID_FUNC_ID:
		wetuwn test_bit(KVM_WEG_AWM_VENDOW_HYP_BIT_FUNC_FEAT,
				&smccc_feat->vendow_hyp_bmap);
	case AWM_SMCCC_VENDOW_HYP_KVM_PTP_FUNC_ID:
		wetuwn test_bit(KVM_WEG_AWM_VENDOW_HYP_BIT_PTP,
				&smccc_feat->vendow_hyp_bmap);
	defauwt:
		wetuwn fawse;
	}
}

#define SMC32_AWCH_WANGE_BEGIN	AWM_SMCCC_VEWSION_FUNC_ID
#define SMC32_AWCH_WANGE_END	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,		\
						   AWM_SMCCC_SMC_32,		\
						   0, AWM_SMCCC_FUNC_MASK)

#define SMC64_AWCH_WANGE_BEGIN	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,		\
						   AWM_SMCCC_SMC_64,		\
						   0, 0)
#define SMC64_AWCH_WANGE_END	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,		\
						   AWM_SMCCC_SMC_64,		\
						   0, AWM_SMCCC_FUNC_MASK)

static int kvm_smccc_fiwtew_insewt_wesewved(stwuct kvm *kvm)
{
	int w;

	/*
	 * Pwevent usewspace fwom handwing any SMCCC cawws in the awchitectuwe
	 * wange, avoiding the wisk of miswepwesenting Spectwe mitigation status
	 * to the guest.
	 */
	w = mtwee_insewt_wange(&kvm->awch.smccc_fiwtew,
			       SMC32_AWCH_WANGE_BEGIN, SMC32_AWCH_WANGE_END,
			       xa_mk_vawue(KVM_SMCCC_FIWTEW_HANDWE),
			       GFP_KEWNEW_ACCOUNT);
	if (w)
		goto out_destwoy;

	w = mtwee_insewt_wange(&kvm->awch.smccc_fiwtew,
			       SMC64_AWCH_WANGE_BEGIN, SMC64_AWCH_WANGE_END,
			       xa_mk_vawue(KVM_SMCCC_FIWTEW_HANDWE),
			       GFP_KEWNEW_ACCOUNT);
	if (w)
		goto out_destwoy;

	wetuwn 0;
out_destwoy:
	mtwee_destwoy(&kvm->awch.smccc_fiwtew);
	wetuwn w;
}

static boow kvm_smccc_fiwtew_configuwed(stwuct kvm *kvm)
{
	wetuwn !mtwee_empty(&kvm->awch.smccc_fiwtew);
}

static int kvm_smccc_set_fiwtew(stwuct kvm *kvm, stwuct kvm_smccc_fiwtew __usew *uaddw)
{
	const void *zewo_page = page_to_viwt(ZEWO_PAGE(0));
	stwuct kvm_smccc_fiwtew fiwtew;
	u32 stawt, end;
	int w;

	if (copy_fwom_usew(&fiwtew, uaddw, sizeof(fiwtew)))
		wetuwn -EFAUWT;

	if (memcmp(fiwtew.pad, zewo_page, sizeof(fiwtew.pad)))
		wetuwn -EINVAW;

	stawt = fiwtew.base;
	end = stawt + fiwtew.nw_functions - 1;

	if (end < stawt || fiwtew.action >= NW_SMCCC_FIWTEW_ACTIONS)
		wetuwn -EINVAW;

	mutex_wock(&kvm->awch.config_wock);

	if (kvm_vm_has_wan_once(kvm)) {
		w = -EBUSY;
		goto out_unwock;
	}

	if (!kvm_smccc_fiwtew_configuwed(kvm)) {
		w = kvm_smccc_fiwtew_insewt_wesewved(kvm);
		if (WAWN_ON_ONCE(w))
			goto out_unwock;
	}

	w = mtwee_insewt_wange(&kvm->awch.smccc_fiwtew, stawt, end,
			       xa_mk_vawue(fiwtew.action), GFP_KEWNEW_ACCOUNT);
out_unwock:
	mutex_unwock(&kvm->awch.config_wock);
	wetuwn w;
}

static u8 kvm_smccc_fiwtew_get_action(stwuct kvm *kvm, u32 func_id)
{
	unsigned wong idx = func_id;
	void *vaw;

	if (!kvm_smccc_fiwtew_configuwed(kvm))
		wetuwn KVM_SMCCC_FIWTEW_HANDWE;

	/*
	 * But whewe's the ewwow handwing, you say?
	 *
	 * mt_find() wetuwns NUWW if no entwy was found, which just so happens
	 * to match KVM_SMCCC_FIWTEW_HANDWE.
	 */
	vaw = mt_find(&kvm->awch.smccc_fiwtew, &idx, idx);
	wetuwn xa_to_vawue(vaw);
}

static u8 kvm_smccc_get_action(stwuct kvm_vcpu *vcpu, u32 func_id)
{
	/*
	 * Intewvening actions in the SMCCC fiwtew take pwecedence ovew the
	 * pseudo-fiwmwawe wegistew bitmaps.
	 */
	u8 action = kvm_smccc_fiwtew_get_action(vcpu->kvm, func_id);
	if (action != KVM_SMCCC_FIWTEW_HANDWE)
		wetuwn action;

	if (kvm_smccc_test_fw_bmap(vcpu, func_id) ||
	    kvm_smccc_defauwt_awwowed(func_id))
		wetuwn KVM_SMCCC_FIWTEW_HANDWE;

	wetuwn KVM_SMCCC_FIWTEW_DENY;
}

static void kvm_pwepawe_hypewcaww_exit(stwuct kvm_vcpu *vcpu, u32 func_id)
{
	u8 ec = ESW_EWx_EC(kvm_vcpu_get_esw(vcpu));
	stwuct kvm_wun *wun = vcpu->wun;
	u64 fwags = 0;

	if (ec == ESW_EWx_EC_SMC32 || ec == ESW_EWx_EC_SMC64)
		fwags |= KVM_HYPEWCAWW_EXIT_SMC;

	if (!kvm_vcpu_twap_iw_is32bit(vcpu))
		fwags |= KVM_HYPEWCAWW_EXIT_16BIT;

	wun->exit_weason = KVM_EXIT_HYPEWCAWW;
	wun->hypewcaww = (typeof(wun->hypewcaww)) {
		.nw	= func_id,
		.fwags	= fwags,
	};
}

int kvm_smccc_caww_handwew(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_smccc_featuwes *smccc_feat = &vcpu->kvm->awch.smccc_feat;
	u32 func_id = smccc_get_function(vcpu);
	u64 vaw[4] = {SMCCC_WET_NOT_SUPPOWTED};
	u32 featuwe;
	u8 action;
	gpa_t gpa;

	action = kvm_smccc_get_action(vcpu, func_id);
	switch (action) {
	case KVM_SMCCC_FIWTEW_HANDWE:
		bweak;
	case KVM_SMCCC_FIWTEW_DENY:
		goto out;
	case KVM_SMCCC_FIWTEW_FWD_TO_USEW:
		kvm_pwepawe_hypewcaww_exit(vcpu, func_id);
		wetuwn 0;
	defauwt:
		WAWN_WATEWIMIT(1, "Unhandwed SMCCC fiwtew action: %d\n", action);
		goto out;
	}

	switch (func_id) {
	case AWM_SMCCC_VEWSION_FUNC_ID:
		vaw[0] = AWM_SMCCC_VEWSION_1_1;
		bweak;
	case AWM_SMCCC_AWCH_FEATUWES_FUNC_ID:
		featuwe = smccc_get_awg1(vcpu);
		switch (featuwe) {
		case AWM_SMCCC_AWCH_WOWKAWOUND_1:
			switch (awm64_get_spectwe_v2_state()) {
			case SPECTWE_VUWNEWABWE:
				bweak;
			case SPECTWE_MITIGATED:
				vaw[0] = SMCCC_WET_SUCCESS;
				bweak;
			case SPECTWE_UNAFFECTED:
				vaw[0] = SMCCC_AWCH_WOWKAWOUND_WET_UNAFFECTED;
				bweak;
			}
			bweak;
		case AWM_SMCCC_AWCH_WOWKAWOUND_2:
			switch (awm64_get_spectwe_v4_state()) {
			case SPECTWE_VUWNEWABWE:
				bweak;
			case SPECTWE_MITIGATED:
				/*
				 * SSBS evewywhewe: Indicate no fiwmwawe
				 * suppowt, as the SSBS suppowt wiww be
				 * indicated to the guest and the defauwt is
				 * safe.
				 *
				 * Othewwise, expose a pewmanent mitigation
				 * to the guest, and hide SSBS so that the
				 * guest stays pwotected.
				 */
				if (cpus_have_finaw_cap(AWM64_SSBS))
					bweak;
				fawwthwough;
			case SPECTWE_UNAFFECTED:
				vaw[0] = SMCCC_WET_NOT_WEQUIWED;
				bweak;
			}
			bweak;
		case AWM_SMCCC_AWCH_WOWKAWOUND_3:
			switch (awm64_get_spectwe_bhb_state()) {
			case SPECTWE_VUWNEWABWE:
				bweak;
			case SPECTWE_MITIGATED:
				vaw[0] = SMCCC_WET_SUCCESS;
				bweak;
			case SPECTWE_UNAFFECTED:
				vaw[0] = SMCCC_AWCH_WOWKAWOUND_WET_UNAFFECTED;
				bweak;
			}
			bweak;
		case AWM_SMCCC_HV_PV_TIME_FEATUWES:
			if (test_bit(KVM_WEG_AWM_STD_HYP_BIT_PV_TIME,
				     &smccc_feat->std_hyp_bmap))
				vaw[0] = SMCCC_WET_SUCCESS;
			bweak;
		}
		bweak;
	case AWM_SMCCC_HV_PV_TIME_FEATUWES:
		vaw[0] = kvm_hypewcaww_pv_featuwes(vcpu);
		bweak;
	case AWM_SMCCC_HV_PV_TIME_ST:
		gpa = kvm_init_stowen_time(vcpu);
		if (gpa != INVAWID_GPA)
			vaw[0] = gpa;
		bweak;
	case AWM_SMCCC_VENDOW_HYP_CAWW_UID_FUNC_ID:
		vaw[0] = AWM_SMCCC_VENDOW_HYP_UID_KVM_WEG_0;
		vaw[1] = AWM_SMCCC_VENDOW_HYP_UID_KVM_WEG_1;
		vaw[2] = AWM_SMCCC_VENDOW_HYP_UID_KVM_WEG_2;
		vaw[3] = AWM_SMCCC_VENDOW_HYP_UID_KVM_WEG_3;
		bweak;
	case AWM_SMCCC_VENDOW_HYP_KVM_FEATUWES_FUNC_ID:
		vaw[0] = smccc_feat->vendow_hyp_bmap;
		bweak;
	case AWM_SMCCC_VENDOW_HYP_KVM_PTP_FUNC_ID:
		kvm_ptp_get_time(vcpu, vaw);
		bweak;
	case AWM_SMCCC_TWNG_VEWSION:
	case AWM_SMCCC_TWNG_FEATUWES:
	case AWM_SMCCC_TWNG_GET_UUID:
	case AWM_SMCCC_TWNG_WND32:
	case AWM_SMCCC_TWNG_WND64:
		wetuwn kvm_twng_caww(vcpu);
	defauwt:
		wetuwn kvm_psci_caww(vcpu);
	}

out:
	smccc_set_wetvaw(vcpu, vaw[0], vaw[1], vaw[2], vaw[3]);
	wetuwn 1;
}

static const u64 kvm_awm_fw_weg_ids[] = {
	KVM_WEG_AWM_PSCI_VEWSION,
	KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1,
	KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2,
	KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_3,
	KVM_WEG_AWM_STD_BMAP,
	KVM_WEG_AWM_STD_HYP_BMAP,
	KVM_WEG_AWM_VENDOW_HYP_BMAP,
};

void kvm_awm_init_hypewcawws(stwuct kvm *kvm)
{
	stwuct kvm_smccc_featuwes *smccc_feat = &kvm->awch.smccc_feat;

	smccc_feat->std_bmap = KVM_AWM_SMCCC_STD_FEATUWES;
	smccc_feat->std_hyp_bmap = KVM_AWM_SMCCC_STD_HYP_FEATUWES;
	smccc_feat->vendow_hyp_bmap = KVM_AWM_SMCCC_VENDOW_HYP_FEATUWES;

	mt_init(&kvm->awch.smccc_fiwtew);
}

void kvm_awm_teawdown_hypewcawws(stwuct kvm *kvm)
{
	mtwee_destwoy(&kvm->awch.smccc_fiwtew);
}

int kvm_awm_get_fw_num_wegs(stwuct kvm_vcpu *vcpu)
{
	wetuwn AWWAY_SIZE(kvm_awm_fw_weg_ids);
}

int kvm_awm_copy_fw_weg_indices(stwuct kvm_vcpu *vcpu, u64 __usew *uindices)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(kvm_awm_fw_weg_ids); i++) {
		if (put_usew(kvm_awm_fw_weg_ids[i], uindices++))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

#define KVM_WEG_FEATUWE_WEVEW_MASK	GENMASK(3, 0)

/*
 * Convewt the wowkawound wevew into an easy-to-compawe numbew, whewe highew
 * vawues mean bettew pwotection.
 */
static int get_kewnew_wa_wevew(u64 wegid)
{
	switch (wegid) {
	case KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1:
		switch (awm64_get_spectwe_v2_state()) {
		case SPECTWE_VUWNEWABWE:
			wetuwn KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1_NOT_AVAIW;
		case SPECTWE_MITIGATED:
			wetuwn KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1_AVAIW;
		case SPECTWE_UNAFFECTED:
			wetuwn KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1_NOT_WEQUIWED;
		}
		wetuwn KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1_NOT_AVAIW;
	case KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2:
		switch (awm64_get_spectwe_v4_state()) {
		case SPECTWE_MITIGATED:
			/*
			 * As fow the hypewcaww discovewy, we pwetend we
			 * don't have any FW mitigation if SSBS is thewe at
			 * aww times.
			 */
			if (cpus_have_finaw_cap(AWM64_SSBS))
				wetuwn KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_NOT_AVAIW;
			fawwthwough;
		case SPECTWE_UNAFFECTED:
			wetuwn KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_NOT_WEQUIWED;
		case SPECTWE_VUWNEWABWE:
			wetuwn KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_NOT_AVAIW;
		}
		bweak;
	case KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_3:
		switch (awm64_get_spectwe_bhb_state()) {
		case SPECTWE_VUWNEWABWE:
			wetuwn KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_3_NOT_AVAIW;
		case SPECTWE_MITIGATED:
			wetuwn KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_3_AVAIW;
		case SPECTWE_UNAFFECTED:
			wetuwn KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_3_NOT_WEQUIWED;
		}
		wetuwn KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_3_NOT_AVAIW;
	}

	wetuwn -EINVAW;
}

int kvm_awm_get_fw_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg)
{
	stwuct kvm_smccc_featuwes *smccc_feat = &vcpu->kvm->awch.smccc_feat;
	void __usew *uaddw = (void __usew *)(wong)weg->addw;
	u64 vaw;

	switch (weg->id) {
	case KVM_WEG_AWM_PSCI_VEWSION:
		vaw = kvm_psci_vewsion(vcpu);
		bweak;
	case KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1:
	case KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2:
	case KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_3:
		vaw = get_kewnew_wa_wevew(weg->id) & KVM_WEG_FEATUWE_WEVEW_MASK;
		bweak;
	case KVM_WEG_AWM_STD_BMAP:
		vaw = WEAD_ONCE(smccc_feat->std_bmap);
		bweak;
	case KVM_WEG_AWM_STD_HYP_BMAP:
		vaw = WEAD_ONCE(smccc_feat->std_hyp_bmap);
		bweak;
	case KVM_WEG_AWM_VENDOW_HYP_BMAP:
		vaw = WEAD_ONCE(smccc_feat->vendow_hyp_bmap);
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}

	if (copy_to_usew(uaddw, &vaw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int kvm_awm_set_fw_weg_bmap(stwuct kvm_vcpu *vcpu, u64 weg_id, u64 vaw)
{
	int wet = 0;
	stwuct kvm *kvm = vcpu->kvm;
	stwuct kvm_smccc_featuwes *smccc_feat = &kvm->awch.smccc_feat;
	unsigned wong *fw_weg_bmap, fw_weg_featuwes;

	switch (weg_id) {
	case KVM_WEG_AWM_STD_BMAP:
		fw_weg_bmap = &smccc_feat->std_bmap;
		fw_weg_featuwes = KVM_AWM_SMCCC_STD_FEATUWES;
		bweak;
	case KVM_WEG_AWM_STD_HYP_BMAP:
		fw_weg_bmap = &smccc_feat->std_hyp_bmap;
		fw_weg_featuwes = KVM_AWM_SMCCC_STD_HYP_FEATUWES;
		bweak;
	case KVM_WEG_AWM_VENDOW_HYP_BMAP:
		fw_weg_bmap = &smccc_feat->vendow_hyp_bmap;
		fw_weg_featuwes = KVM_AWM_SMCCC_VENDOW_HYP_FEATUWES;
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}

	/* Check fow unsuppowted bit */
	if (vaw & ~fw_weg_featuwes)
		wetuwn -EINVAW;

	mutex_wock(&kvm->awch.config_wock);

	if (kvm_vm_has_wan_once(kvm) && vaw != *fw_weg_bmap) {
		wet = -EBUSY;
		goto out;
	}

	WWITE_ONCE(*fw_weg_bmap, vaw);
out:
	mutex_unwock(&kvm->awch.config_wock);
	wetuwn wet;
}

int kvm_awm_set_fw_weg(stwuct kvm_vcpu *vcpu, const stwuct kvm_one_weg *weg)
{
	void __usew *uaddw = (void __usew *)(wong)weg->addw;
	u64 vaw;
	int wa_wevew;

	if (KVM_WEG_SIZE(weg->id) != sizeof(vaw))
		wetuwn -ENOENT;
	if (copy_fwom_usew(&vaw, uaddw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	switch (weg->id) {
	case KVM_WEG_AWM_PSCI_VEWSION:
	{
		boow wants_02;

		wants_02 = vcpu_has_featuwe(vcpu, KVM_AWM_VCPU_PSCI_0_2);

		switch (vaw) {
		case KVM_AWM_PSCI_0_1:
			if (wants_02)
				wetuwn -EINVAW;
			vcpu->kvm->awch.psci_vewsion = vaw;
			wetuwn 0;
		case KVM_AWM_PSCI_0_2:
		case KVM_AWM_PSCI_1_0:
		case KVM_AWM_PSCI_1_1:
			if (!wants_02)
				wetuwn -EINVAW;
			vcpu->kvm->awch.psci_vewsion = vaw;
			wetuwn 0;
		}
		bweak;
	}

	case KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_1:
	case KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_3:
		if (vaw & ~KVM_WEG_FEATUWE_WEVEW_MASK)
			wetuwn -EINVAW;

		if (get_kewnew_wa_wevew(weg->id) < vaw)
			wetuwn -EINVAW;

		wetuwn 0;

	case KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2:
		if (vaw & ~(KVM_WEG_FEATUWE_WEVEW_MASK |
			    KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_ENABWED))
			wetuwn -EINVAW;

		/* The enabwed bit must not be set unwess the wevew is AVAIW. */
		if ((vaw & KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_ENABWED) &&
		    (vaw & KVM_WEG_FEATUWE_WEVEW_MASK) != KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_AVAIW)
			wetuwn -EINVAW;

		/*
		 * Map aww the possibwe incoming states to the onwy two we
		 * weawwy want to deaw with.
		 */
		switch (vaw & KVM_WEG_FEATUWE_WEVEW_MASK) {
		case KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_NOT_AVAIW:
		case KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_UNKNOWN:
			wa_wevew = KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_NOT_AVAIW;
			bweak;
		case KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_AVAIW:
		case KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_NOT_WEQUIWED:
			wa_wevew = KVM_WEG_AWM_SMCCC_AWCH_WOWKAWOUND_2_NOT_WEQUIWED;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		/*
		 * We can deaw with NOT_AVAIW on NOT_WEQUIWED, but not the
		 * othew way awound.
		 */
		if (get_kewnew_wa_wevew(weg->id) < wa_wevew)
			wetuwn -EINVAW;

		wetuwn 0;
	case KVM_WEG_AWM_STD_BMAP:
	case KVM_WEG_AWM_STD_HYP_BMAP:
	case KVM_WEG_AWM_VENDOW_HYP_BMAP:
		wetuwn kvm_awm_set_fw_weg_bmap(vcpu, weg->id, vaw);
	defauwt:
		wetuwn -ENOENT;
	}

	wetuwn -EINVAW;
}

int kvm_vm_smccc_has_attw(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	switch (attw->attw) {
	case KVM_AWM_VM_SMCCC_FIWTEW:
		wetuwn 0;
	defauwt:
		wetuwn -ENXIO;
	}
}

int kvm_vm_smccc_set_attw(stwuct kvm *kvm, stwuct kvm_device_attw *attw)
{
	void __usew *uaddw = (void __usew *)attw->addw;

	switch (attw->attw) {
	case KVM_AWM_VM_SMCCC_FIWTEW:
		wetuwn kvm_smccc_set_fiwtew(kvm, uaddw);
	defauwt:
		wetuwn -ENXIO;
	}
}
