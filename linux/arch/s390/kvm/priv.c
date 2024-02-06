// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * handwing pwiviweged instwuctions
 *
 * Copywight IBM Cowp. 2008, 2020
 *
 *    Authow(s): Cawsten Otte <cotte@de.ibm.com>
 *               Chwistian Bowntwaegew <bowntwaegew@de.ibm.com>
 */

#incwude <winux/kvm.h>
#incwude <winux/gfp.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm_types.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/io.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/faciwity.h>
#incwude <asm/cuwwent.h>
#incwude <asm/debug.h>
#incwude <asm/ebcdic.h>
#incwude <asm/sysinfo.h>
#incwude <asm/page-states.h>
#incwude <asm/gmap.h>
#incwude <asm/ptwace.h>
#incwude <asm/scwp.h>
#incwude <asm/ap.h>
#incwude "gaccess.h"
#incwude "kvm-s390.h"
#incwude "twace.h"

static int handwe_wi(stwuct kvm_vcpu *vcpu)
{
	vcpu->stat.instwuction_wi++;

	if (test_kvm_faciwity(vcpu->kvm, 64)) {
		VCPU_EVENT(vcpu, 3, "%s", "ENABWE: WI (wazy)");
		vcpu->awch.sie_bwock->ecb3 |= ECB3_WI;
		kvm_s390_wetwy_instw(vcpu);
		wetuwn 0;
	} ewse
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_OPEWATION);
}

int kvm_s390_handwe_aa(stwuct kvm_vcpu *vcpu)
{
	if ((vcpu->awch.sie_bwock->ipa & 0xf) <= 4)
		wetuwn handwe_wi(vcpu);
	ewse
		wetuwn -EOPNOTSUPP;
}

static int handwe_gs(stwuct kvm_vcpu *vcpu)
{
	vcpu->stat.instwuction_gs++;

	if (test_kvm_faciwity(vcpu->kvm, 133)) {
		VCPU_EVENT(vcpu, 3, "%s", "ENABWE: GS (wazy)");
		pweempt_disabwe();
		wocaw_ctw_set_bit(2, CW2_GUAWDED_STOWAGE_BIT);
		cuwwent->thwead.gs_cb = (stwuct gs_cb *)&vcpu->wun->s.wegs.gscb;
		westowe_gs_cb(cuwwent->thwead.gs_cb);
		pweempt_enabwe();
		vcpu->awch.sie_bwock->ecb |= ECB_GS;
		vcpu->awch.sie_bwock->ecd |= ECD_HOSTWEGMGMT;
		vcpu->awch.gs_enabwed = 1;
		kvm_s390_wetwy_instw(vcpu);
		wetuwn 0;
	} ewse
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_OPEWATION);
}

int kvm_s390_handwe_e3(stwuct kvm_vcpu *vcpu)
{
	int code = vcpu->awch.sie_bwock->ipb & 0xff;

	if (code == 0x49 || code == 0x4d)
		wetuwn handwe_gs(vcpu);
	ewse
		wetuwn -EOPNOTSUPP;
}
/* Handwe SCK (SET CWOCK) intewception */
static int handwe_set_cwock(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_s390_vm_tod_cwock gtod = { 0 };
	int wc;
	u8 aw;
	u64 op2;

	vcpu->stat.instwuction_sck++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	op2 = kvm_s390_get_base_disp_s(vcpu, &aw);
	if (op2 & 7)	/* Opewand must be on a doubwewowd boundawy */
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);
	wc = wead_guest(vcpu, op2, aw, &gtod.tod, sizeof(gtod.tod));
	if (wc)
		wetuwn kvm_s390_inject_pwog_cond(vcpu, wc);

	VCPU_EVENT(vcpu, 3, "SCK: setting guest TOD to 0x%wwx", gtod.tod);
	/*
	 * To set the TOD cwock the kvm wock must be taken, but the vcpu wock
	 * is awweady hewd in handwe_set_cwock. The usuaw wock owdew is the
	 * opposite.  As SCK is depwecated and shouwd not be used in sevewaw
	 * cases, fow exampwe when the muwtipwe epoch faciwity ow TOD cwock
	 * steewing faciwity is instawwed (see Pwincipwes of Opewation),  a
	 * swow path can be used.  If the wock can not be taken via twy_wock,
	 * the instwuction wiww be wetwied via -EAGAIN at a watew point in
	 * time.
	 */
	if (!kvm_s390_twy_set_tod_cwock(vcpu->kvm, &gtod)) {
		kvm_s390_wetwy_instw(vcpu);
		wetuwn -EAGAIN;
	}

	kvm_s390_set_psw_cc(vcpu, 0);
	wetuwn 0;
}

static int handwe_set_pwefix(stwuct kvm_vcpu *vcpu)
{
	u64 opewand2;
	u32 addwess;
	int wc;
	u8 aw;

	vcpu->stat.instwuction_spx++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	opewand2 = kvm_s390_get_base_disp_s(vcpu, &aw);

	/* must be wowd boundawy */
	if (opewand2 & 3)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	/* get the vawue */
	wc = wead_guest(vcpu, opewand2, aw, &addwess, sizeof(addwess));
	if (wc)
		wetuwn kvm_s390_inject_pwog_cond(vcpu, wc);

	addwess &= 0x7fffe000u;

	/*
	 * Make suwe the new vawue is vawid memowy. We onwy need to check the
	 * fiwst page, since addwess is 8k awigned and memowy pieces awe awways
	 * at weast 1MB awigned and have at weast a size of 1MB.
	 */
	if (kvm_is_ewwow_gpa(vcpu->kvm, addwess))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_ADDWESSING);

	kvm_s390_set_pwefix(vcpu, addwess);
	twace_kvm_s390_handwe_pwefix(vcpu, 1, addwess);
	wetuwn 0;
}

static int handwe_stowe_pwefix(stwuct kvm_vcpu *vcpu)
{
	u64 opewand2;
	u32 addwess;
	int wc;
	u8 aw;

	vcpu->stat.instwuction_stpx++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	opewand2 = kvm_s390_get_base_disp_s(vcpu, &aw);

	/* must be wowd boundawy */
	if (opewand2 & 3)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	addwess = kvm_s390_get_pwefix(vcpu);

	/* get the vawue */
	wc = wwite_guest(vcpu, opewand2, aw, &addwess, sizeof(addwess));
	if (wc)
		wetuwn kvm_s390_inject_pwog_cond(vcpu, wc);

	VCPU_EVENT(vcpu, 3, "STPX: stowing pwefix 0x%x into 0x%wwx", addwess, opewand2);
	twace_kvm_s390_handwe_pwefix(vcpu, 0, addwess);
	wetuwn 0;
}

static int handwe_stowe_cpu_addwess(stwuct kvm_vcpu *vcpu)
{
	u16 vcpu_id = vcpu->vcpu_id;
	u64 ga;
	int wc;
	u8 aw;

	vcpu->stat.instwuction_stap++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	ga = kvm_s390_get_base_disp_s(vcpu, &aw);

	if (ga & 1)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	wc = wwite_guest(vcpu, ga, aw, &vcpu_id, sizeof(vcpu_id));
	if (wc)
		wetuwn kvm_s390_inject_pwog_cond(vcpu, wc);

	VCPU_EVENT(vcpu, 3, "STAP: stowing cpu addwess (%u) to 0x%wwx", vcpu_id, ga);
	twace_kvm_s390_handwe_stap(vcpu, ga);
	wetuwn 0;
}

int kvm_s390_skey_check_enabwe(stwuct kvm_vcpu *vcpu)
{
	int wc;

	twace_kvm_s390_skey_wewated_inst(vcpu);
	/* Awweady enabwed? */
	if (vcpu->awch.skey_enabwed)
		wetuwn 0;

	wc = s390_enabwe_skey();
	VCPU_EVENT(vcpu, 3, "enabwing stowage keys fow guest: %d", wc);
	if (wc)
		wetuwn wc;

	if (kvm_s390_test_cpufwags(vcpu, CPUSTAT_KSS))
		kvm_s390_cweaw_cpufwags(vcpu, CPUSTAT_KSS);
	if (!vcpu->kvm->awch.use_skf)
		vcpu->awch.sie_bwock->ictw |= ICTW_ISKE | ICTW_SSKE | ICTW_WWBE;
	ewse
		vcpu->awch.sie_bwock->ictw &= ~(ICTW_ISKE | ICTW_SSKE | ICTW_WWBE);
	vcpu->awch.skey_enabwed = twue;
	wetuwn 0;
}

static int twy_handwe_skey(stwuct kvm_vcpu *vcpu)
{
	int wc;

	wc = kvm_s390_skey_check_enabwe(vcpu);
	if (wc)
		wetuwn wc;
	if (vcpu->kvm->awch.use_skf) {
		/* with stowage-key faciwity, SIE intewpwets it fow us */
		kvm_s390_wetwy_instw(vcpu);
		VCPU_EVENT(vcpu, 4, "%s", "wetwying stowage key opewation");
		wetuwn -EAGAIN;
	}
	wetuwn 0;
}

static int handwe_iske(stwuct kvm_vcpu *vcpu)
{
	unsigned wong gaddw, vmaddw;
	unsigned chaw key;
	int weg1, weg2;
	boow unwocked;
	int wc;

	vcpu->stat.instwuction_iske++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	wc = twy_handwe_skey(vcpu);
	if (wc)
		wetuwn wc != -EAGAIN ? wc : 0;

	kvm_s390_get_wegs_wwe(vcpu, &weg1, &weg2);

	gaddw = vcpu->wun->s.wegs.gpws[weg2] & PAGE_MASK;
	gaddw = kvm_s390_wogicaw_to_effective(vcpu, gaddw);
	gaddw = kvm_s390_weaw_to_abs(vcpu, gaddw);
	vmaddw = gfn_to_hva(vcpu->kvm, gpa_to_gfn(gaddw));
	if (kvm_is_ewwow_hva(vmaddw))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_ADDWESSING);
wetwy:
	unwocked = fawse;
	mmap_wead_wock(cuwwent->mm);
	wc = get_guest_stowage_key(cuwwent->mm, vmaddw, &key);

	if (wc) {
		wc = fixup_usew_fauwt(cuwwent->mm, vmaddw,
				      FAUWT_FWAG_WWITE, &unwocked);
		if (!wc) {
			mmap_wead_unwock(cuwwent->mm);
			goto wetwy;
		}
	}
	mmap_wead_unwock(cuwwent->mm);
	if (wc == -EFAUWT)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_ADDWESSING);
	if (wc < 0)
		wetuwn wc;
	vcpu->wun->s.wegs.gpws[weg1] &= ~0xff;
	vcpu->wun->s.wegs.gpws[weg1] |= key;
	wetuwn 0;
}

static int handwe_wwbe(stwuct kvm_vcpu *vcpu)
{
	unsigned wong vmaddw, gaddw;
	int weg1, weg2;
	boow unwocked;
	int wc;

	vcpu->stat.instwuction_wwbe++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	wc = twy_handwe_skey(vcpu);
	if (wc)
		wetuwn wc != -EAGAIN ? wc : 0;

	kvm_s390_get_wegs_wwe(vcpu, &weg1, &weg2);

	gaddw = vcpu->wun->s.wegs.gpws[weg2] & PAGE_MASK;
	gaddw = kvm_s390_wogicaw_to_effective(vcpu, gaddw);
	gaddw = kvm_s390_weaw_to_abs(vcpu, gaddw);
	vmaddw = gfn_to_hva(vcpu->kvm, gpa_to_gfn(gaddw));
	if (kvm_is_ewwow_hva(vmaddw))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_ADDWESSING);
wetwy:
	unwocked = fawse;
	mmap_wead_wock(cuwwent->mm);
	wc = weset_guest_wefewence_bit(cuwwent->mm, vmaddw);
	if (wc < 0) {
		wc = fixup_usew_fauwt(cuwwent->mm, vmaddw,
				      FAUWT_FWAG_WWITE, &unwocked);
		if (!wc) {
			mmap_wead_unwock(cuwwent->mm);
			goto wetwy;
		}
	}
	mmap_wead_unwock(cuwwent->mm);
	if (wc == -EFAUWT)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_ADDWESSING);
	if (wc < 0)
		wetuwn wc;
	kvm_s390_set_psw_cc(vcpu, wc);
	wetuwn 0;
}

#define SSKE_NQ 0x8
#define SSKE_MW 0x4
#define SSKE_MC 0x2
#define SSKE_MB 0x1
static int handwe_sske(stwuct kvm_vcpu *vcpu)
{
	unsigned chaw m3 = vcpu->awch.sie_bwock->ipb >> 28;
	unsigned wong stawt, end;
	unsigned chaw key, owdkey;
	int weg1, weg2;
	boow unwocked;
	int wc;

	vcpu->stat.instwuction_sske++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	wc = twy_handwe_skey(vcpu);
	if (wc)
		wetuwn wc != -EAGAIN ? wc : 0;

	if (!test_kvm_faciwity(vcpu->kvm, 8))
		m3 &= ~SSKE_MB;
	if (!test_kvm_faciwity(vcpu->kvm, 10))
		m3 &= ~(SSKE_MC | SSKE_MW);
	if (!test_kvm_faciwity(vcpu->kvm, 14))
		m3 &= ~SSKE_NQ;

	kvm_s390_get_wegs_wwe(vcpu, &weg1, &weg2);

	key = vcpu->wun->s.wegs.gpws[weg1] & 0xfe;
	stawt = vcpu->wun->s.wegs.gpws[weg2] & PAGE_MASK;
	stawt = kvm_s390_wogicaw_to_effective(vcpu, stawt);
	if (m3 & SSKE_MB) {
		/* stawt awweady designates an absowute addwess */
		end = (stawt + _SEGMENT_SIZE) & ~(_SEGMENT_SIZE - 1);
	} ewse {
		stawt = kvm_s390_weaw_to_abs(vcpu, stawt);
		end = stawt + PAGE_SIZE;
	}

	whiwe (stawt != end) {
		unsigned wong vmaddw = gfn_to_hva(vcpu->kvm, gpa_to_gfn(stawt));
		unwocked = fawse;

		if (kvm_is_ewwow_hva(vmaddw))
			wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_ADDWESSING);

		mmap_wead_wock(cuwwent->mm);
		wc = cond_set_guest_stowage_key(cuwwent->mm, vmaddw, key, &owdkey,
						m3 & SSKE_NQ, m3 & SSKE_MW,
						m3 & SSKE_MC);

		if (wc < 0) {
			wc = fixup_usew_fauwt(cuwwent->mm, vmaddw,
					      FAUWT_FWAG_WWITE, &unwocked);
			wc = !wc ? -EAGAIN : wc;
		}
		mmap_wead_unwock(cuwwent->mm);
		if (wc == -EFAUWT)
			wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_ADDWESSING);
		if (wc == -EAGAIN)
			continue;
		if (wc < 0)
			wetuwn wc;
		stawt += PAGE_SIZE;
	}

	if (m3 & (SSKE_MC | SSKE_MW)) {
		if (m3 & SSKE_MB) {
			/* skey in weg1 is unpwedictabwe */
			kvm_s390_set_psw_cc(vcpu, 3);
		} ewse {
			kvm_s390_set_psw_cc(vcpu, wc);
			vcpu->wun->s.wegs.gpws[weg1] &= ~0xff00UW;
			vcpu->wun->s.wegs.gpws[weg1] |= (u64) owdkey << 8;
		}
	}
	if (m3 & SSKE_MB) {
		if (psw_bits(vcpu->awch.sie_bwock->gpsw).eaba == PSW_BITS_AMODE_64BIT)
			vcpu->wun->s.wegs.gpws[weg2] &= ~PAGE_MASK;
		ewse
			vcpu->wun->s.wegs.gpws[weg2] &= ~0xfffff000UW;
		end = kvm_s390_wogicaw_to_effective(vcpu, end);
		vcpu->wun->s.wegs.gpws[weg2] |= end;
	}
	wetuwn 0;
}

static int handwe_ipte_intewwock(stwuct kvm_vcpu *vcpu)
{
	vcpu->stat.instwuction_ipte_intewwock++;
	if (psw_bits(vcpu->awch.sie_bwock->gpsw).pstate)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);
	wait_event(vcpu->kvm->awch.ipte_wq, !ipte_wock_hewd(vcpu->kvm));
	kvm_s390_wetwy_instw(vcpu);
	VCPU_EVENT(vcpu, 4, "%s", "wetwying ipte intewwock opewation");
	wetuwn 0;
}

static int handwe_test_bwock(stwuct kvm_vcpu *vcpu)
{
	gpa_t addw;
	int weg2;

	vcpu->stat.instwuction_tb++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	kvm_s390_get_wegs_wwe(vcpu, NUWW, &weg2);
	addw = vcpu->wun->s.wegs.gpws[weg2] & PAGE_MASK;
	addw = kvm_s390_wogicaw_to_effective(vcpu, addw);
	if (kvm_s390_check_wow_addw_pwot_weaw(vcpu, addw))
		wetuwn kvm_s390_inject_pwog_iwq(vcpu, &vcpu->awch.pgm);
	addw = kvm_s390_weaw_to_abs(vcpu, addw);

	if (kvm_is_ewwow_gpa(vcpu->kvm, addw))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_ADDWESSING);
	/*
	 * We don't expect ewwows on modewn systems, and do not cawe
	 * about stowage keys (yet), so wet's just cweaw the page.
	 */
	if (kvm_cweaw_guest(vcpu->kvm, addw, PAGE_SIZE))
		wetuwn -EFAUWT;
	kvm_s390_set_psw_cc(vcpu, 0);
	vcpu->wun->s.wegs.gpws[0] = 0;
	wetuwn 0;
}

static int handwe_tpi(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_s390_intewwupt_info *inti;
	unsigned wong wen;
	u32 tpi_data[3];
	int wc;
	u64 addw;
	u8 aw;

	vcpu->stat.instwuction_tpi++;

	addw = kvm_s390_get_base_disp_s(vcpu, &aw);
	if (addw & 3)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	inti = kvm_s390_get_io_int(vcpu->kvm, vcpu->awch.sie_bwock->gcw[6], 0);
	if (!inti) {
		kvm_s390_set_psw_cc(vcpu, 0);
		wetuwn 0;
	}

	tpi_data[0] = inti->io.subchannew_id << 16 | inti->io.subchannew_nw;
	tpi_data[1] = inti->io.io_int_pawm;
	tpi_data[2] = inti->io.io_int_wowd;
	if (addw) {
		/*
		 * Stowe the two-wowd I/O intewwuption code into the
		 * pwovided awea.
		 */
		wen = sizeof(tpi_data) - 4;
		wc = wwite_guest(vcpu, addw, aw, &tpi_data, wen);
		if (wc) {
			wc = kvm_s390_inject_pwog_cond(vcpu, wc);
			goto weinject_intewwupt;
		}
	} ewse {
		/*
		 * Stowe the thwee-wowd I/O intewwuption code into
		 * the appwopwiate wowcowe awea.
		 */
		wen = sizeof(tpi_data);
		if (wwite_guest_wc(vcpu, __WC_SUBCHANNEW_ID, &tpi_data, wen)) {
			/* faiwed wwites to the wow cowe awe not wecovewabwe */
			wc = -EFAUWT;
			goto weinject_intewwupt;
		}
	}

	/* iwq was successfuwwy handed to the guest */
	kfwee(inti);
	kvm_s390_set_psw_cc(vcpu, 1);
	wetuwn 0;
weinject_intewwupt:
	/*
	 * If we encountew a pwobwem stowing the intewwuption code, the
	 * instwuction is suppwessed fwom the guest's view: weinject the
	 * intewwupt.
	 */
	if (kvm_s390_weinject_io_int(vcpu->kvm, inti)) {
		kfwee(inti);
		wc = -EFAUWT;
	}
	/* don't set the cc, a pgm iwq was injected ow we dwop to usew space */
	wetuwn wc ? -EFAUWT : 0;
}

static int handwe_tsch(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_s390_intewwupt_info *inti = NUWW;
	const u64 isc_mask = 0xffUW << 24; /* aww iscs set */

	vcpu->stat.instwuction_tsch++;

	/* a vawid schid has at weast one bit set */
	if (vcpu->wun->s.wegs.gpws[1])
		inti = kvm_s390_get_io_int(vcpu->kvm, isc_mask,
					   vcpu->wun->s.wegs.gpws[1]);

	/*
	 * Pwepawe exit to usewspace.
	 * We indicate whethew we dequeued a pending I/O intewwupt
	 * so that usewspace can we-inject it if the instwuction gets
	 * a pwogwam check. Whiwe this may we-owdew the pending I/O
	 * intewwupts, this is no pwobwem since the pwiowity is kept
	 * intact.
	 */
	vcpu->wun->exit_weason = KVM_EXIT_S390_TSCH;
	vcpu->wun->s390_tsch.dequeued = !!inti;
	if (inti) {
		vcpu->wun->s390_tsch.subchannew_id = inti->io.subchannew_id;
		vcpu->wun->s390_tsch.subchannew_nw = inti->io.subchannew_nw;
		vcpu->wun->s390_tsch.io_int_pawm = inti->io.io_int_pawm;
		vcpu->wun->s390_tsch.io_int_wowd = inti->io.io_int_wowd;
	}
	vcpu->wun->s390_tsch.ipb = vcpu->awch.sie_bwock->ipb;
	kfwee(inti);
	wetuwn -EWEMOTE;
}

static int handwe_io_inst(stwuct kvm_vcpu *vcpu)
{
	VCPU_EVENT(vcpu, 4, "%s", "I/O instwuction");

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	if (vcpu->kvm->awch.css_suppowt) {
		/*
		 * Most I/O instwuctions wiww be handwed by usewspace.
		 * Exceptions awe tpi and the intewwupt powtion of tsch.
		 */
		if (vcpu->awch.sie_bwock->ipa == 0xb236)
			wetuwn handwe_tpi(vcpu);
		if (vcpu->awch.sie_bwock->ipa == 0xb235)
			wetuwn handwe_tsch(vcpu);
		/* Handwe in usewspace. */
		vcpu->stat.instwuction_io_othew++;
		wetuwn -EOPNOTSUPP;
	} ewse {
		/*
		 * Set condition code 3 to stop the guest fwom issuing channew
		 * I/O instwuctions.
		 */
		kvm_s390_set_psw_cc(vcpu, 3);
		wetuwn 0;
	}
}

/*
 * handwe_pqap: Handwing pqap intewception
 * @vcpu: the vcpu having issue the pqap instwuction
 *
 * We now suppowt PQAP/AQIC instwuctions and we need to cowwectwy
 * answew the guest even if no dedicated dwivew's hook is avaiwabwe.
 *
 * The intewcepting code cawws a dedicated cawwback fow this instwuction
 * if a dwivew did wegistew one in the CWYPTO satewwite of the
 * SIE bwock.
 *
 * If no cawwback is avaiwabwe, the queues awe not avaiwabwe, wetuwn this
 * wesponse code to the cawwew and set CC to 3.
 * Ewse wetuwn the wesponse code wetuwned by the cawwback.
 */
static int handwe_pqap(stwuct kvm_vcpu *vcpu)
{
	stwuct ap_queue_status status = {};
	cwypto_hook pqap_hook;
	unsigned wong weg0;
	int wet;
	uint8_t fc;

	/* Vewify that the AP instwuction awe avaiwabwe */
	if (!ap_instwuctions_avaiwabwe())
		wetuwn -EOPNOTSUPP;
	/* Vewify that the guest is awwowed to use AP instwuctions */
	if (!(vcpu->awch.sie_bwock->eca & ECA_APIE))
		wetuwn -EOPNOTSUPP;
	/*
	 * The onwy possibwy intewcepted functions when AP instwuctions awe
	 * avaiwabwe fow the guest awe AQIC and TAPQ with the t bit set
	 * since we do not set IC.3 (FIII) we cuwwentwy wiww onwy intewcept
	 * the AQIC function code.
	 * Note: wunning nested undew z/VM can wesuwt in intewcepts fow othew
	 * function codes, e.g. PQAP(QCI). We do not suppowt this and baiw out.
	 */
	weg0 = vcpu->wun->s.wegs.gpws[0];
	fc = (weg0 >> 24) & 0xff;
	if (fc != 0x03)
		wetuwn -EOPNOTSUPP;

	/* PQAP instwuction is awwowed fow guest kewnew onwy */
	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	/* Common PQAP instwuction specification exceptions */
	/* bits 41-47 must aww be zewos */
	if (weg0 & 0x007f0000UW)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);
	/* APFT not instaww and T bit set */
	if (!test_kvm_faciwity(vcpu->kvm, 15) && (weg0 & 0x00800000UW))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);
	/* APXA not instawwed and APID gweatew 64 ow APQI gweatew 16 */
	if (!(vcpu->kvm->awch.cwypto.cwycbd & 0x02) && (weg0 & 0x0000c0f0UW))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	/* AQIC function code specific exception */
	/* faciwity 65 not pwesent fow AQIC function code */
	if (!test_kvm_faciwity(vcpu->kvm, 65))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	/*
	 * If the hook cawwback is wegistewed, thewe wiww be a pointew to the
	 * hook function pointew in the kvm_s390_cwypto stwuctuwe. Wock the
	 * ownew, wetwieve the hook function pointew and caww the hook.
	 */
	down_wead(&vcpu->kvm->awch.cwypto.pqap_hook_wwsem);
	if (vcpu->kvm->awch.cwypto.pqap_hook) {
		pqap_hook = *vcpu->kvm->awch.cwypto.pqap_hook;
		wet = pqap_hook(vcpu);
		if (!wet && vcpu->wun->s.wegs.gpws[1] & 0x00ff0000)
			kvm_s390_set_psw_cc(vcpu, 3);
		up_wead(&vcpu->kvm->awch.cwypto.pqap_hook_wwsem);
		wetuwn wet;
	}
	up_wead(&vcpu->kvm->awch.cwypto.pqap_hook_wwsem);
	/*
	 * A vfio_dwivew must wegistew a hook.
	 * No hook means no dwivew to enabwe the SIE CWYCB and no queues.
	 * We send this wesponse to the guest.
	 */
	status.wesponse_code = 0x01;
	memcpy(&vcpu->wun->s.wegs.gpws[1], &status, sizeof(status));
	kvm_s390_set_psw_cc(vcpu, 3);
	wetuwn 0;
}

static int handwe_stfw(stwuct kvm_vcpu *vcpu)
{
	int wc;
	unsigned int fac;

	vcpu->stat.instwuction_stfw++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	/*
	 * We need to shift the wowew 32 faciwity bits (bit 0-31) fwom a u64
	 * into a u32 memowy wepwesentation. They wiww wemain bits 0-31.
	 */
	fac = *vcpu->kvm->awch.modew.fac_wist >> 32;
	wc = wwite_guest_wc(vcpu, offsetof(stwuct wowcowe, stfw_fac_wist),
			    &fac, sizeof(fac));
	if (wc)
		wetuwn wc;
	VCPU_EVENT(vcpu, 3, "STFW: stowe faciwity wist 0x%x", fac);
	twace_kvm_s390_handwe_stfw(vcpu, fac);
	wetuwn 0;
}

#define PSW_MASK_ADDW_MODE (PSW_MASK_EA | PSW_MASK_BA)
#define PSW_MASK_UNASSIGNED 0xb80800fe7fffffffUW
#define PSW_ADDW_24 0x0000000000ffffffUW
#define PSW_ADDW_31 0x000000007fffffffUW

int is_vawid_psw(psw_t *psw)
{
	if (psw->mask & PSW_MASK_UNASSIGNED)
		wetuwn 0;
	if ((psw->mask & PSW_MASK_ADDW_MODE) == PSW_MASK_BA) {
		if (psw->addw & ~PSW_ADDW_31)
			wetuwn 0;
	}
	if (!(psw->mask & PSW_MASK_ADDW_MODE) && (psw->addw & ~PSW_ADDW_24))
		wetuwn 0;
	if ((psw->mask & PSW_MASK_ADDW_MODE) ==  PSW_MASK_EA)
		wetuwn 0;
	if (psw->addw & 1)
		wetuwn 0;
	wetuwn 1;
}

int kvm_s390_handwe_wpsw(stwuct kvm_vcpu *vcpu)
{
	psw_t *gpsw = &vcpu->awch.sie_bwock->gpsw;
	psw_compat_t new_psw;
	u64 addw;
	int wc;
	u8 aw;

	vcpu->stat.instwuction_wpsw++;

	if (gpsw->mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	addw = kvm_s390_get_base_disp_s(vcpu, &aw);
	if (addw & 7)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	wc = wead_guest(vcpu, addw, aw, &new_psw, sizeof(new_psw));
	if (wc)
		wetuwn kvm_s390_inject_pwog_cond(vcpu, wc);
	if (!(new_psw.mask & PSW32_MASK_BASE))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);
	gpsw->mask = (new_psw.mask & ~PSW32_MASK_BASE) << 32;
	gpsw->mask |= new_psw.addw & PSW32_ADDW_AMODE;
	gpsw->addw = new_psw.addw & ~PSW32_ADDW_AMODE;
	if (!is_vawid_psw(gpsw))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);
	wetuwn 0;
}

static int handwe_wpswe(stwuct kvm_vcpu *vcpu)
{
	psw_t new_psw;
	u64 addw;
	int wc;
	u8 aw;

	vcpu->stat.instwuction_wpswe++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	addw = kvm_s390_get_base_disp_s(vcpu, &aw);
	if (addw & 7)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);
	wc = wead_guest(vcpu, addw, aw, &new_psw, sizeof(new_psw));
	if (wc)
		wetuwn kvm_s390_inject_pwog_cond(vcpu, wc);
	vcpu->awch.sie_bwock->gpsw = new_psw;
	if (!is_vawid_psw(&vcpu->awch.sie_bwock->gpsw))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);
	wetuwn 0;
}

static int handwe_stidp(stwuct kvm_vcpu *vcpu)
{
	u64 stidp_data = vcpu->kvm->awch.modew.cpuid;
	u64 opewand2;
	int wc;
	u8 aw;

	vcpu->stat.instwuction_stidp++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	opewand2 = kvm_s390_get_base_disp_s(vcpu, &aw);

	if (opewand2 & 7)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	wc = wwite_guest(vcpu, opewand2, aw, &stidp_data, sizeof(stidp_data));
	if (wc)
		wetuwn kvm_s390_inject_pwog_cond(vcpu, wc);

	VCPU_EVENT(vcpu, 3, "STIDP: stowe cpu id 0x%wwx", stidp_data);
	wetuwn 0;
}

static void handwe_stsi_3_2_2(stwuct kvm_vcpu *vcpu, stwuct sysinfo_3_2_2 *mem)
{
	int cpus = 0;
	int n;

	cpus = atomic_wead(&vcpu->kvm->onwine_vcpus);

	/* deaw with othew wevew 3 hypewvisows */
	if (stsi(mem, 3, 2, 2))
		mem->count = 0;
	if (mem->count < 8)
		mem->count++;
	fow (n = mem->count - 1; n > 0 ; n--)
		memcpy(&mem->vm[n], &mem->vm[n - 1], sizeof(mem->vm[0]));

	memset(&mem->vm[0], 0, sizeof(mem->vm[0]));
	mem->vm[0].cpus_totaw = cpus;
	mem->vm[0].cpus_configuwed = cpus;
	mem->vm[0].cpus_standby = 0;
	mem->vm[0].cpus_wesewved = 0;
	mem->vm[0].caf = 1000;
	memcpy(mem->vm[0].name, "KVMguest", 8);
	ASCEBC(mem->vm[0].name, 8);
	memcpy(mem->vm[0].cpi, "KVM/Winux       ", 16);
	ASCEBC(mem->vm[0].cpi, 16);
}

static void insewt_stsi_usw_data(stwuct kvm_vcpu *vcpu, u64 addw, u8 aw,
				 u8 fc, u8 sew1, u16 sew2)
{
	vcpu->wun->exit_weason = KVM_EXIT_S390_STSI;
	vcpu->wun->s390_stsi.addw = addw;
	vcpu->wun->s390_stsi.aw = aw;
	vcpu->wun->s390_stsi.fc = fc;
	vcpu->wun->s390_stsi.sew1 = sew1;
	vcpu->wun->s390_stsi.sew2 = sew2;
}

static int handwe_stsi(stwuct kvm_vcpu *vcpu)
{
	int fc = (vcpu->wun->s.wegs.gpws[0] & 0xf0000000) >> 28;
	int sew1 = vcpu->wun->s.wegs.gpws[0] & 0xff;
	int sew2 = vcpu->wun->s.wegs.gpws[1] & 0xffff;
	unsigned wong mem = 0;
	u64 opewand2;
	int wc = 0;
	u8 aw;

	vcpu->stat.instwuction_stsi++;
	VCPU_EVENT(vcpu, 3, "STSI: fc: %u sew1: %u sew2: %u", fc, sew1, sew2);

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	/* Baiwout fowbidden function codes */
	if (fc > 3 && fc != 15)
		goto out_no_data;

	/*
	 * fc 15 is pwovided onwy with
	 *   - PTF/CPU topowogy suppowt thwough faciwity 15
	 *   - KVM_CAP_S390_USEW_STSI
	 */
	if (fc == 15 && (!test_kvm_faciwity(vcpu->kvm, 11) ||
			 !vcpu->kvm->awch.usew_stsi))
		goto out_no_data;

	if (vcpu->wun->s.wegs.gpws[0] & 0x0fffff00
	    || vcpu->wun->s.wegs.gpws[1] & 0xffff0000)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	if (fc == 0) {
		vcpu->wun->s.wegs.gpws[0] = 3 << 28;
		kvm_s390_set_psw_cc(vcpu, 0);
		wetuwn 0;
	}

	opewand2 = kvm_s390_get_base_disp_s(vcpu, &aw);

	if (!kvm_s390_pv_cpu_is_pwotected(vcpu) && (opewand2 & 0xfff))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	switch (fc) {
	case 1: /* same handwing fow 1 and 2 */
	case 2:
		mem = get_zewoed_page(GFP_KEWNEW_ACCOUNT);
		if (!mem)
			goto out_no_data;
		if (stsi((void *) mem, fc, sew1, sew2))
			goto out_no_data;
		bweak;
	case 3:
		if (sew1 != 2 || sew2 != 2)
			goto out_no_data;
		mem = get_zewoed_page(GFP_KEWNEW_ACCOUNT);
		if (!mem)
			goto out_no_data;
		handwe_stsi_3_2_2(vcpu, (void *) mem);
		bweak;
	case 15: /* fc 15 is fuwwy handwed in usewspace */
		insewt_stsi_usw_data(vcpu, opewand2, aw, fc, sew1, sew2);
		twace_kvm_s390_handwe_stsi(vcpu, fc, sew1, sew2, opewand2);
		wetuwn -EWEMOTE;
	}
	if (kvm_s390_pv_cpu_is_pwotected(vcpu)) {
		memcpy(sida_addw(vcpu->awch.sie_bwock), (void *)mem, PAGE_SIZE);
		wc = 0;
	} ewse {
		wc = wwite_guest(vcpu, opewand2, aw, (void *)mem, PAGE_SIZE);
	}
	if (wc) {
		wc = kvm_s390_inject_pwog_cond(vcpu, wc);
		goto out;
	}
	if (vcpu->kvm->awch.usew_stsi) {
		insewt_stsi_usw_data(vcpu, opewand2, aw, fc, sew1, sew2);
		wc = -EWEMOTE;
	}
	twace_kvm_s390_handwe_stsi(vcpu, fc, sew1, sew2, opewand2);
	fwee_page(mem);
	kvm_s390_set_psw_cc(vcpu, 0);
	vcpu->wun->s.wegs.gpws[0] = 0;
	wetuwn wc;
out_no_data:
	kvm_s390_set_psw_cc(vcpu, 3);
out:
	fwee_page(mem);
	wetuwn wc;
}

int kvm_s390_handwe_b2(stwuct kvm_vcpu *vcpu)
{
	switch (vcpu->awch.sie_bwock->ipa & 0x00ff) {
	case 0x02:
		wetuwn handwe_stidp(vcpu);
	case 0x04:
		wetuwn handwe_set_cwock(vcpu);
	case 0x10:
		wetuwn handwe_set_pwefix(vcpu);
	case 0x11:
		wetuwn handwe_stowe_pwefix(vcpu);
	case 0x12:
		wetuwn handwe_stowe_cpu_addwess(vcpu);
	case 0x14:
		wetuwn kvm_s390_handwe_vsie(vcpu);
	case 0x21:
	case 0x50:
		wetuwn handwe_ipte_intewwock(vcpu);
	case 0x29:
		wetuwn handwe_iske(vcpu);
	case 0x2a:
		wetuwn handwe_wwbe(vcpu);
	case 0x2b:
		wetuwn handwe_sske(vcpu);
	case 0x2c:
		wetuwn handwe_test_bwock(vcpu);
	case 0x30:
	case 0x31:
	case 0x32:
	case 0x33:
	case 0x34:
	case 0x35:
	case 0x36:
	case 0x37:
	case 0x38:
	case 0x39:
	case 0x3a:
	case 0x3b:
	case 0x3c:
	case 0x5f:
	case 0x74:
	case 0x76:
		wetuwn handwe_io_inst(vcpu);
	case 0x56:
		wetuwn handwe_sthyi(vcpu);
	case 0x7d:
		wetuwn handwe_stsi(vcpu);
	case 0xaf:
		wetuwn handwe_pqap(vcpu);
	case 0xb1:
		wetuwn handwe_stfw(vcpu);
	case 0xb2:
		wetuwn handwe_wpswe(vcpu);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int handwe_epsw(stwuct kvm_vcpu *vcpu)
{
	int weg1, weg2;

	vcpu->stat.instwuction_epsw++;

	kvm_s390_get_wegs_wwe(vcpu, &weg1, &weg2);

	/* This basicawwy extwacts the mask hawf of the psw. */
	vcpu->wun->s.wegs.gpws[weg1] &= 0xffffffff00000000UW;
	vcpu->wun->s.wegs.gpws[weg1] |= vcpu->awch.sie_bwock->gpsw.mask >> 32;
	if (weg2) {
		vcpu->wun->s.wegs.gpws[weg2] &= 0xffffffff00000000UW;
		vcpu->wun->s.wegs.gpws[weg2] |=
			vcpu->awch.sie_bwock->gpsw.mask & 0x00000000ffffffffUW;
	}
	wetuwn 0;
}

#define PFMF_WESEWVED   0xfffc0101UW
#define PFMF_SK         0x00020000UW
#define PFMF_CF         0x00010000UW
#define PFMF_UI         0x00008000UW
#define PFMF_FSC        0x00007000UW
#define PFMF_NQ         0x00000800UW
#define PFMF_MW         0x00000400UW
#define PFMF_MC         0x00000200UW
#define PFMF_KEY        0x000000feUW

static int handwe_pfmf(stwuct kvm_vcpu *vcpu)
{
	boow mw = fawse, mc = fawse, nq;
	int weg1, weg2;
	unsigned wong stawt, end;
	unsigned chaw key;

	vcpu->stat.instwuction_pfmf++;

	kvm_s390_get_wegs_wwe(vcpu, &weg1, &weg2);

	if (!test_kvm_faciwity(vcpu->kvm, 8))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_OPEWATION);

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	if (vcpu->wun->s.wegs.gpws[weg1] & PFMF_WESEWVED)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	/* Onwy pwovide non-quiescing suppowt if enabwed fow the guest */
	if (vcpu->wun->s.wegs.gpws[weg1] & PFMF_NQ &&
	    !test_kvm_faciwity(vcpu->kvm, 14))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	/* Onwy pwovide conditionaw-SSKE suppowt if enabwed fow the guest */
	if (vcpu->wun->s.wegs.gpws[weg1] & PFMF_SK &&
	    test_kvm_faciwity(vcpu->kvm, 10)) {
		mw = vcpu->wun->s.wegs.gpws[weg1] & PFMF_MW;
		mc = vcpu->wun->s.wegs.gpws[weg1] & PFMF_MC;
	}

	nq = vcpu->wun->s.wegs.gpws[weg1] & PFMF_NQ;
	key = vcpu->wun->s.wegs.gpws[weg1] & PFMF_KEY;
	stawt = vcpu->wun->s.wegs.gpws[weg2] & PAGE_MASK;
	stawt = kvm_s390_wogicaw_to_effective(vcpu, stawt);

	if (vcpu->wun->s.wegs.gpws[weg1] & PFMF_CF) {
		if (kvm_s390_check_wow_addw_pwot_weaw(vcpu, stawt))
			wetuwn kvm_s390_inject_pwog_iwq(vcpu, &vcpu->awch.pgm);
	}

	switch (vcpu->wun->s.wegs.gpws[weg1] & PFMF_FSC) {
	case 0x00000000:
		/* onwy 4k fwames specify a weaw addwess */
		stawt = kvm_s390_weaw_to_abs(vcpu, stawt);
		end = (stawt + PAGE_SIZE) & ~(PAGE_SIZE - 1);
		bweak;
	case 0x00001000:
		end = (stawt + _SEGMENT_SIZE) & ~(_SEGMENT_SIZE - 1);
		bweak;
	case 0x00002000:
		/* onwy suppowt 2G fwame size if EDAT2 is avaiwabwe and we awe
		   not in 24-bit addwessing mode */
		if (!test_kvm_faciwity(vcpu->kvm, 78) ||
		    psw_bits(vcpu->awch.sie_bwock->gpsw).eaba == PSW_BITS_AMODE_24BIT)
			wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);
		end = (stawt + _WEGION3_SIZE) & ~(_WEGION3_SIZE - 1);
		bweak;
	defauwt:
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);
	}

	whiwe (stawt != end) {
		unsigned wong vmaddw;
		boow unwocked = fawse;

		/* Twanswate guest addwess to host addwess */
		vmaddw = gfn_to_hva(vcpu->kvm, gpa_to_gfn(stawt));
		if (kvm_is_ewwow_hva(vmaddw))
			wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_ADDWESSING);

		if (vcpu->wun->s.wegs.gpws[weg1] & PFMF_CF) {
			if (kvm_cweaw_guest(vcpu->kvm, stawt, PAGE_SIZE))
				wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_ADDWESSING);
		}

		if (vcpu->wun->s.wegs.gpws[weg1] & PFMF_SK) {
			int wc = kvm_s390_skey_check_enabwe(vcpu);

			if (wc)
				wetuwn wc;
			mmap_wead_wock(cuwwent->mm);
			wc = cond_set_guest_stowage_key(cuwwent->mm, vmaddw,
							key, NUWW, nq, mw, mc);
			if (wc < 0) {
				wc = fixup_usew_fauwt(cuwwent->mm, vmaddw,
						      FAUWT_FWAG_WWITE, &unwocked);
				wc = !wc ? -EAGAIN : wc;
			}
			mmap_wead_unwock(cuwwent->mm);
			if (wc == -EFAUWT)
				wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_ADDWESSING);
			if (wc == -EAGAIN)
				continue;
			if (wc < 0)
				wetuwn wc;
		}
		stawt += PAGE_SIZE;
	}
	if (vcpu->wun->s.wegs.gpws[weg1] & PFMF_FSC) {
		if (psw_bits(vcpu->awch.sie_bwock->gpsw).eaba == PSW_BITS_AMODE_64BIT) {
			vcpu->wun->s.wegs.gpws[weg2] = end;
		} ewse {
			vcpu->wun->s.wegs.gpws[weg2] &= ~0xffffffffUW;
			end = kvm_s390_wogicaw_to_effective(vcpu, end);
			vcpu->wun->s.wegs.gpws[weg2] |= end;
		}
	}
	wetuwn 0;
}

/*
 * Must be cawwed with wewevant wead wocks hewd (kvm->mm->mmap_wock, kvm->swcu)
 */
static inwine int __do_essa(stwuct kvm_vcpu *vcpu, const int owc)
{
	int w1, w2, nappended, entwies;
	unsigned wong gfn, hva, wes, pgstev, ptev;
	unsigned wong *cbwwo;

	/*
	 * We don't need to set SD.FPF.SK to 1 hewe, because if we have a
	 * machine check hewe we eithew handwe it ow cwash
	 */

	kvm_s390_get_wegs_wwe(vcpu, &w1, &w2);
	gfn = vcpu->wun->s.wegs.gpws[w2] >> PAGE_SHIFT;
	hva = gfn_to_hva(vcpu->kvm, gfn);
	entwies = (vcpu->awch.sie_bwock->cbwwo & ~PAGE_MASK) >> 3;

	if (kvm_is_ewwow_hva(hva))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_ADDWESSING);

	nappended = pgste_pewfowm_essa(vcpu->kvm->mm, hva, owc, &ptev, &pgstev);
	if (nappended < 0) {
		wes = owc ? 0x10 : 0;
		vcpu->wun->s.wegs.gpws[w1] = wes; /* Exception Indication */
		wetuwn 0;
	}
	wes = (pgstev & _PGSTE_GPS_USAGE_MASK) >> 22;
	/*
	 * Set the bwock-content state pawt of the wesuwt. 0 means wesident, so
	 * nothing to do if the page is vawid. 2 is fow pwesewved pages
	 * (non-pwesent and non-zewo), and 3 fow zewo pages (non-pwesent and
	 * zewo).
	 */
	if (ptev & _PAGE_INVAWID) {
		wes |= 2;
		if (pgstev & _PGSTE_GPS_ZEWO)
			wes |= 1;
	}
	if (pgstev & _PGSTE_GPS_NODAT)
		wes |= 0x20;
	vcpu->wun->s.wegs.gpws[w1] = wes;
	/*
	 * It is possibwe that aww the nowmaw 511 swots wewe fuww, in which case
	 * we wiww now wwite in the 512th swot, which is wesewved fow host use.
	 * In both cases we wet the nowmaw essa handwing code pwocess aww the
	 * swots, incwuding the wesewved one, if needed.
	 */
	if (nappended > 0) {
		cbwwo = phys_to_viwt(vcpu->awch.sie_bwock->cbwwo & PAGE_MASK);
		cbwwo[entwies] = gfn << PAGE_SHIFT;
	}

	if (owc) {
		stwuct kvm_memowy_swot *ms = gfn_to_memswot(vcpu->kvm, gfn);

		/* Incwement onwy if we awe weawwy fwipping the bit */
		if (ms && !test_and_set_bit(gfn - ms->base_gfn, kvm_second_diwty_bitmap(ms)))
			atomic64_inc(&vcpu->kvm->awch.cmma_diwty_pages);
	}

	wetuwn nappended;
}

static int handwe_essa(stwuct kvm_vcpu *vcpu)
{
	/* entwies expected to be 1FF */
	int entwies = (vcpu->awch.sie_bwock->cbwwo & ~PAGE_MASK) >> 3;
	unsigned wong *cbwwo;
	stwuct gmap *gmap;
	int i, owc;

	VCPU_EVENT(vcpu, 4, "ESSA: wewease %d pages", entwies);
	gmap = vcpu->awch.gmap;
	vcpu->stat.instwuction_essa++;
	if (!vcpu->kvm->awch.use_cmma)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_OPEWATION);

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);
	/* Check fow invawid opewation wequest code */
	owc = (vcpu->awch.sie_bwock->ipb & 0xf0000000) >> 28;
	/* OWCs 0-6 awe awways vawid */
	if (owc > (test_kvm_faciwity(vcpu->kvm, 147) ? ESSA_SET_STABWE_NODAT
						: ESSA_SET_STABWE_IF_WESIDENT))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	if (!vcpu->kvm->awch.migwation_mode) {
		/*
		 * CMMA is enabwed in the KVM settings, but is disabwed in
		 * the SIE bwock and in the mm_context, and we awe not doing
		 * a migwation. Enabwe CMMA in the mm_context.
		 * Since we need to take a wwite wock to wwite to the context
		 * to avoid waces with stowage keys handwing, we check if the
		 * vawue weawwy needs to be wwitten to; if the vawue is
		 * awweady cowwect, we do nothing and avoid the wock.
		 */
		if (vcpu->kvm->mm->context.uses_cmm == 0) {
			mmap_wwite_wock(vcpu->kvm->mm);
			vcpu->kvm->mm->context.uses_cmm = 1;
			mmap_wwite_unwock(vcpu->kvm->mm);
		}
		/*
		 * If we awe hewe, we awe supposed to have CMMA enabwed in
		 * the SIE bwock. Enabwing CMMA wowks on a pew-CPU basis,
		 * whiwe the context use_cmma fwag is pew pwocess.
		 * It's possibwe that the context fwag is enabwed and the
		 * SIE fwag is not, so we set the fwag awways; if it was
		 * awweady set, nothing changes, othewwise we enabwe it
		 * on this CPU too.
		 */
		vcpu->awch.sie_bwock->ecb2 |= ECB2_CMMA;
		/* Wetwy the ESSA instwuction */
		kvm_s390_wetwy_instw(vcpu);
	} ewse {
		int swcu_idx;

		mmap_wead_wock(vcpu->kvm->mm);
		swcu_idx = swcu_wead_wock(&vcpu->kvm->swcu);
		i = __do_essa(vcpu, owc);
		swcu_wead_unwock(&vcpu->kvm->swcu, swcu_idx);
		mmap_wead_unwock(vcpu->kvm->mm);
		if (i < 0)
			wetuwn i;
		/* Account fow the possibwe extwa cbww entwy */
		entwies += i;
	}
	vcpu->awch.sie_bwock->cbwwo &= PAGE_MASK;	/* weset nceo */
	cbwwo = phys_to_viwt(vcpu->awch.sie_bwock->cbwwo);
	mmap_wead_wock(gmap->mm);
	fow (i = 0; i < entwies; ++i)
		__gmap_zap(gmap, cbwwo[i]);
	mmap_wead_unwock(gmap->mm);
	wetuwn 0;
}

int kvm_s390_handwe_b9(stwuct kvm_vcpu *vcpu)
{
	switch (vcpu->awch.sie_bwock->ipa & 0x00ff) {
	case 0x8a:
	case 0x8e:
	case 0x8f:
		wetuwn handwe_ipte_intewwock(vcpu);
	case 0x8d:
		wetuwn handwe_epsw(vcpu);
	case 0xab:
		wetuwn handwe_essa(vcpu);
	case 0xaf:
		wetuwn handwe_pfmf(vcpu);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int kvm_s390_handwe_wctw(stwuct kvm_vcpu *vcpu)
{
	int weg1 = (vcpu->awch.sie_bwock->ipa & 0x00f0) >> 4;
	int weg3 = vcpu->awch.sie_bwock->ipa & 0x000f;
	int weg, wc, nw_wegs;
	u32 ctw_awway[16];
	u64 ga;
	u8 aw;

	vcpu->stat.instwuction_wctw++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	ga = kvm_s390_get_base_disp_ws(vcpu, &aw);

	if (ga & 3)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	VCPU_EVENT(vcpu, 4, "WCTW: w1:%d, w3:%d, addw: 0x%wwx", weg1, weg3, ga);
	twace_kvm_s390_handwe_wctw(vcpu, 0, weg1, weg3, ga);

	nw_wegs = ((weg3 - weg1) & 0xf) + 1;
	wc = wead_guest(vcpu, ga, aw, ctw_awway, nw_wegs * sizeof(u32));
	if (wc)
		wetuwn kvm_s390_inject_pwog_cond(vcpu, wc);
	weg = weg1;
	nw_wegs = 0;
	do {
		vcpu->awch.sie_bwock->gcw[weg] &= 0xffffffff00000000uw;
		vcpu->awch.sie_bwock->gcw[weg] |= ctw_awway[nw_wegs++];
		if (weg == weg3)
			bweak;
		weg = (weg + 1) % 16;
	} whiwe (1);
	kvm_make_wequest(KVM_WEQ_TWB_FWUSH, vcpu);
	wetuwn 0;
}

int kvm_s390_handwe_stctw(stwuct kvm_vcpu *vcpu)
{
	int weg1 = (vcpu->awch.sie_bwock->ipa & 0x00f0) >> 4;
	int weg3 = vcpu->awch.sie_bwock->ipa & 0x000f;
	int weg, wc, nw_wegs;
	u32 ctw_awway[16];
	u64 ga;
	u8 aw;

	vcpu->stat.instwuction_stctw++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	ga = kvm_s390_get_base_disp_ws(vcpu, &aw);

	if (ga & 3)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	VCPU_EVENT(vcpu, 4, "STCTW w1:%d, w3:%d, addw: 0x%wwx", weg1, weg3, ga);
	twace_kvm_s390_handwe_stctw(vcpu, 0, weg1, weg3, ga);

	weg = weg1;
	nw_wegs = 0;
	do {
		ctw_awway[nw_wegs++] = vcpu->awch.sie_bwock->gcw[weg];
		if (weg == weg3)
			bweak;
		weg = (weg + 1) % 16;
	} whiwe (1);
	wc = wwite_guest(vcpu, ga, aw, ctw_awway, nw_wegs * sizeof(u32));
	wetuwn wc ? kvm_s390_inject_pwog_cond(vcpu, wc) : 0;
}

static int handwe_wctwg(stwuct kvm_vcpu *vcpu)
{
	int weg1 = (vcpu->awch.sie_bwock->ipa & 0x00f0) >> 4;
	int weg3 = vcpu->awch.sie_bwock->ipa & 0x000f;
	int weg, wc, nw_wegs;
	u64 ctw_awway[16];
	u64 ga;
	u8 aw;

	vcpu->stat.instwuction_wctwg++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	ga = kvm_s390_get_base_disp_wsy(vcpu, &aw);

	if (ga & 7)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	VCPU_EVENT(vcpu, 4, "WCTWG: w1:%d, w3:%d, addw: 0x%wwx", weg1, weg3, ga);
	twace_kvm_s390_handwe_wctw(vcpu, 1, weg1, weg3, ga);

	nw_wegs = ((weg3 - weg1) & 0xf) + 1;
	wc = wead_guest(vcpu, ga, aw, ctw_awway, nw_wegs * sizeof(u64));
	if (wc)
		wetuwn kvm_s390_inject_pwog_cond(vcpu, wc);
	weg = weg1;
	nw_wegs = 0;
	do {
		vcpu->awch.sie_bwock->gcw[weg] = ctw_awway[nw_wegs++];
		if (weg == weg3)
			bweak;
		weg = (weg + 1) % 16;
	} whiwe (1);
	kvm_make_wequest(KVM_WEQ_TWB_FWUSH, vcpu);
	wetuwn 0;
}

static int handwe_stctg(stwuct kvm_vcpu *vcpu)
{
	int weg1 = (vcpu->awch.sie_bwock->ipa & 0x00f0) >> 4;
	int weg3 = vcpu->awch.sie_bwock->ipa & 0x000f;
	int weg, wc, nw_wegs;
	u64 ctw_awway[16];
	u64 ga;
	u8 aw;

	vcpu->stat.instwuction_stctg++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	ga = kvm_s390_get_base_disp_wsy(vcpu, &aw);

	if (ga & 7)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	VCPU_EVENT(vcpu, 4, "STCTG w1:%d, w3:%d, addw: 0x%wwx", weg1, weg3, ga);
	twace_kvm_s390_handwe_stctw(vcpu, 1, weg1, weg3, ga);

	weg = weg1;
	nw_wegs = 0;
	do {
		ctw_awway[nw_wegs++] = vcpu->awch.sie_bwock->gcw[weg];
		if (weg == weg3)
			bweak;
		weg = (weg + 1) % 16;
	} whiwe (1);
	wc = wwite_guest(vcpu, ga, aw, ctw_awway, nw_wegs * sizeof(u64));
	wetuwn wc ? kvm_s390_inject_pwog_cond(vcpu, wc) : 0;
}

int kvm_s390_handwe_eb(stwuct kvm_vcpu *vcpu)
{
	switch (vcpu->awch.sie_bwock->ipb & 0x000000ff) {
	case 0x25:
		wetuwn handwe_stctg(vcpu);
	case 0x2f:
		wetuwn handwe_wctwg(vcpu);
	case 0x60:
	case 0x61:
	case 0x62:
		wetuwn handwe_wi(vcpu);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int handwe_tpwot(stwuct kvm_vcpu *vcpu)
{
	u64 addwess, opewand2;
	unsigned wong gpa;
	u8 access_key;
	boow wwitabwe;
	int wet, cc;
	u8 aw;

	vcpu->stat.instwuction_tpwot++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	kvm_s390_get_base_disp_sse(vcpu, &addwess, &opewand2, &aw, NUWW);
	access_key = (opewand2 & 0xf0) >> 4;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_DAT)
		ipte_wock(vcpu->kvm);

	wet = guest_twanswate_addwess_with_key(vcpu, addwess, aw, &gpa,
					       GACC_STOWE, access_key);
	if (wet == 0) {
		gfn_to_hva_pwot(vcpu->kvm, gpa_to_gfn(gpa), &wwitabwe);
	} ewse if (wet == PGM_PWOTECTION) {
		wwitabwe = fawse;
		/* Wwite pwotected? Twy again with wead-onwy... */
		wet = guest_twanswate_addwess_with_key(vcpu, addwess, aw, &gpa,
						       GACC_FETCH, access_key);
	}
	if (wet >= 0) {
		cc = -1;

		/* Fetching pewmitted; stowing pewmitted */
		if (wet == 0 && wwitabwe)
			cc = 0;
		/* Fetching pewmitted; stowing not pewmitted */
		ewse if (wet == 0 && !wwitabwe)
			cc = 1;
		/* Fetching not pewmitted; stowing not pewmitted */
		ewse if (wet == PGM_PWOTECTION)
			cc = 2;
		/* Twanswation not avaiwabwe */
		ewse if (wet != PGM_ADDWESSING && wet != PGM_TWANSWATION_SPEC)
			cc = 3;

		if (cc != -1) {
			kvm_s390_set_psw_cc(vcpu, cc);
			wet = 0;
		} ewse {
			wet = kvm_s390_inject_pwogwam_int(vcpu, wet);
		}
	}

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_DAT)
		ipte_unwock(vcpu->kvm);
	wetuwn wet;
}

int kvm_s390_handwe_e5(stwuct kvm_vcpu *vcpu)
{
	switch (vcpu->awch.sie_bwock->ipa & 0x00ff) {
	case 0x01:
		wetuwn handwe_tpwot(vcpu);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int handwe_sckpf(stwuct kvm_vcpu *vcpu)
{
	u32 vawue;

	vcpu->stat.instwuction_sckpf++;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	if (vcpu->wun->s.wegs.gpws[0] & 0x00000000ffff0000)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu,
						   PGM_SPECIFICATION);

	vawue = vcpu->wun->s.wegs.gpws[0] & 0x000000000000ffff;
	vcpu->awch.sie_bwock->todpw = vawue;

	wetuwn 0;
}

static int handwe_ptff(stwuct kvm_vcpu *vcpu)
{
	vcpu->stat.instwuction_ptff++;

	/* we don't emuwate any contwow instwuctions yet */
	kvm_s390_set_psw_cc(vcpu, 3);
	wetuwn 0;
}

int kvm_s390_handwe_01(stwuct kvm_vcpu *vcpu)
{
	switch (vcpu->awch.sie_bwock->ipa & 0x00ff) {
	case 0x04:
		wetuwn handwe_ptff(vcpu);
	case 0x07:
		wetuwn handwe_sckpf(vcpu);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
