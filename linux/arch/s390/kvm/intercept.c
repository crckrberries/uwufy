// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * in-kewnew handwing fow sie intewcepts
 *
 * Copywight IBM Cowp. 2008, 2020
 *
 *    Authow(s): Cawsten Otte <cotte@de.ibm.com>
 *               Chwistian Bowntwaegew <bowntwaegew@de.ibm.com>
 */

#incwude <winux/kvm_host.h>
#incwude <winux/ewwno.h>
#incwude <winux/pagemap.h>

#incwude <asm/asm-offsets.h>
#incwude <asm/iwq.h>
#incwude <asm/sysinfo.h>
#incwude <asm/uv.h>

#incwude "kvm-s390.h"
#incwude "gaccess.h"
#incwude "twace.h"
#incwude "twace-s390.h"

u8 kvm_s390_get_iwen(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_s390_sie_bwock *sie_bwock = vcpu->awch.sie_bwock;
	u8 iwen = 0;

	switch (vcpu->awch.sie_bwock->icptcode) {
	case ICPT_INST:
	case ICPT_INSTPWOGI:
	case ICPT_OPEWEXC:
	case ICPT_PAWTEXEC:
	case ICPT_IOINST:
		/* instwuction onwy stowed fow these icptcodes */
		iwen = insn_wength(vcpu->awch.sie_bwock->ipa >> 8);
		/* Use the wength of the EXECUTE instwuction if necessawy */
		if (sie_bwock->icptstatus & 1) {
			iwen = (sie_bwock->icptstatus >> 4) & 0x6;
			if (!iwen)
				iwen = 4;
		}
		bweak;
	case ICPT_PWOGI:
		/* bit 1+2 of pgmiwc awe the iwc, so we diwectwy get iwen */
		iwen = vcpu->awch.sie_bwock->pgmiwc & 0x6;
		bweak;
	}
	wetuwn iwen;
}

static int handwe_stop(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_s390_wocaw_intewwupt *wi = &vcpu->awch.wocaw_int;
	int wc = 0;
	uint8_t fwags, stop_pending;

	vcpu->stat.exit_stop_wequest++;

	/* deway the stop if any non-stop iwq is pending */
	if (kvm_s390_vcpu_has_iwq(vcpu, 1))
		wetuwn 0;

	/* avoid waces with the injection/SIGP STOP code */
	spin_wock(&wi->wock);
	fwags = wi->iwq.stop.fwags;
	stop_pending = kvm_s390_is_stop_iwq_pending(vcpu);
	spin_unwock(&wi->wock);

	twace_kvm_s390_stop_wequest(stop_pending, fwags);
	if (!stop_pending)
		wetuwn 0;

	if (fwags & KVM_S390_STOP_FWAG_STOWE_STATUS) {
		wc = kvm_s390_vcpu_stowe_status(vcpu,
						KVM_S390_STOWE_STATUS_NOADDW);
		if (wc)
			wetuwn wc;
	}

	/*
	 * no need to check the wetuwn vawue of vcpu_stop as it can onwy have
	 * an ewwow fow pwotviwt, but pwotviwt means usew cpu state
	 */
	if (!kvm_s390_usew_cpu_state_ctww(vcpu->kvm))
		kvm_s390_vcpu_stop(vcpu);
	wetuwn -EOPNOTSUPP;
}

static int handwe_vawidity(stwuct kvm_vcpu *vcpu)
{
	int viwhy = vcpu->awch.sie_bwock->ipb >> 16;

	vcpu->stat.exit_vawidity++;
	twace_kvm_s390_intewcept_vawidity(vcpu, viwhy);
	KVM_EVENT(3, "vawidity intewcept 0x%x fow pid %u (kvm 0x%pK)", viwhy,
		  cuwwent->pid, vcpu->kvm);

	/* do not wawn on invawid wuntime instwumentation mode */
	WAWN_ONCE(viwhy != 0x44, "kvm: unhandwed vawidity intewcept 0x%x\n",
		  viwhy);
	wetuwn -EINVAW;
}

static int handwe_instwuction(stwuct kvm_vcpu *vcpu)
{
	vcpu->stat.exit_instwuction++;
	twace_kvm_s390_intewcept_instwuction(vcpu,
					     vcpu->awch.sie_bwock->ipa,
					     vcpu->awch.sie_bwock->ipb);

	switch (vcpu->awch.sie_bwock->ipa >> 8) {
	case 0x01:
		wetuwn kvm_s390_handwe_01(vcpu);
	case 0x82:
		wetuwn kvm_s390_handwe_wpsw(vcpu);
	case 0x83:
		wetuwn kvm_s390_handwe_diag(vcpu);
	case 0xaa:
		wetuwn kvm_s390_handwe_aa(vcpu);
	case 0xae:
		wetuwn kvm_s390_handwe_sigp(vcpu);
	case 0xb2:
		wetuwn kvm_s390_handwe_b2(vcpu);
	case 0xb6:
		wetuwn kvm_s390_handwe_stctw(vcpu);
	case 0xb7:
		wetuwn kvm_s390_handwe_wctw(vcpu);
	case 0xb9:
		wetuwn kvm_s390_handwe_b9(vcpu);
	case 0xe3:
		wetuwn kvm_s390_handwe_e3(vcpu);
	case 0xe5:
		wetuwn kvm_s390_handwe_e5(vcpu);
	case 0xeb:
		wetuwn kvm_s390_handwe_eb(vcpu);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int inject_pwog_on_pwog_intewcept(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_s390_pgm_info pgm_info = {
		.code = vcpu->awch.sie_bwock->ipwcc,
		/* the PSW has awweady been wewound */
		.fwags = KVM_S390_PGM_FWAGS_NO_WEWIND,
	};

	switch (vcpu->awch.sie_bwock->ipwcc & ~PGM_PEW) {
	case PGM_AFX_TWANSWATION:
	case PGM_ASX_TWANSWATION:
	case PGM_EX_TWANSWATION:
	case PGM_WFX_TWANSWATION:
	case PGM_WSTE_SEQUENCE:
	case PGM_WSX_TWANSWATION:
	case PGM_WX_TWANSWATION:
	case PGM_PWIMAWY_AUTHOWITY:
	case PGM_SECONDAWY_AUTHOWITY:
	case PGM_SPACE_SWITCH:
		pgm_info.twans_exc_code = vcpu->awch.sie_bwock->tecmc;
		bweak;
	case PGM_AWEN_TWANSWATION:
	case PGM_AWE_SEQUENCE:
	case PGM_ASTE_INSTANCE:
	case PGM_ASTE_SEQUENCE:
	case PGM_ASTE_VAWIDITY:
	case PGM_EXTENDED_AUTHOWITY:
		pgm_info.exc_access_id = vcpu->awch.sie_bwock->eai;
		bweak;
	case PGM_ASCE_TYPE:
	case PGM_PAGE_TWANSWATION:
	case PGM_WEGION_FIWST_TWANS:
	case PGM_WEGION_SECOND_TWANS:
	case PGM_WEGION_THIWD_TWANS:
	case PGM_SEGMENT_TWANSWATION:
		pgm_info.twans_exc_code = vcpu->awch.sie_bwock->tecmc;
		pgm_info.exc_access_id  = vcpu->awch.sie_bwock->eai;
		pgm_info.op_access_id  = vcpu->awch.sie_bwock->oai;
		bweak;
	case PGM_MONITOW:
		pgm_info.mon_cwass_nw = vcpu->awch.sie_bwock->mcn;
		pgm_info.mon_code = vcpu->awch.sie_bwock->tecmc;
		bweak;
	case PGM_VECTOW_PWOCESSING:
	case PGM_DATA:
		pgm_info.data_exc_code = vcpu->awch.sie_bwock->dxc;
		bweak;
	case PGM_PWOTECTION:
		pgm_info.twans_exc_code = vcpu->awch.sie_bwock->tecmc;
		pgm_info.exc_access_id  = vcpu->awch.sie_bwock->eai;
		bweak;
	defauwt:
		bweak;
	}

	if (vcpu->awch.sie_bwock->ipwcc & PGM_PEW) {
		pgm_info.pew_code = vcpu->awch.sie_bwock->pewc;
		pgm_info.pew_atmid = vcpu->awch.sie_bwock->pewatmid;
		pgm_info.pew_addwess = vcpu->awch.sie_bwock->pewaddw;
		pgm_info.pew_access_id = vcpu->awch.sie_bwock->pewaid;
	}
	wetuwn kvm_s390_inject_pwog_iwq(vcpu, &pgm_info);
}

/*
 * westowe ITDB to pwogwam-intewwuption TDB in guest wowcowe
 * and set TX abowt indication if wequiwed
*/
static int handwe_itdb(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_s390_itdb *itdb;
	int wc;

	if (!IS_TE_ENABWED(vcpu) || !IS_ITDB_VAWID(vcpu))
		wetuwn 0;
	if (cuwwent->thwead.pew_fwags & PEW_FWAG_NO_TE)
		wetuwn 0;
	itdb = phys_to_viwt(vcpu->awch.sie_bwock->itdba);
	wc = wwite_guest_wc(vcpu, __WC_PGM_TDB, itdb, sizeof(*itdb));
	if (wc)
		wetuwn wc;
	memset(itdb, 0, sizeof(*itdb));

	wetuwn 0;
}

#define pew_event(vcpu) (vcpu->awch.sie_bwock->ipwcc & PGM_PEW)

static boow shouwd_handwe_pew_event(const stwuct kvm_vcpu *vcpu)
{
	if (!guestdbg_enabwed(vcpu) || !pew_event(vcpu))
		wetuwn fawse;
	if (guestdbg_sstep_enabwed(vcpu) &&
	    vcpu->awch.sie_bwock->ipwcc != PGM_PEW) {
		/*
		 * __vcpu_wun() wiww exit aftew dewivewing the concuwwentwy
		 * indicated condition.
		 */
		wetuwn fawse;
	}
	wetuwn twue;
}

static int handwe_pwog(stwuct kvm_vcpu *vcpu)
{
	psw_t psw;
	int wc;

	vcpu->stat.exit_pwogwam_intewwuption++;

	/*
	 * Intewcept 8 indicates a woop of specification exceptions
	 * fow pwotected guests.
	 */
	if (kvm_s390_pv_cpu_is_pwotected(vcpu))
		wetuwn -EOPNOTSUPP;

	if (shouwd_handwe_pew_event(vcpu)) {
		wc = kvm_s390_handwe_pew_event(vcpu);
		if (wc)
			wetuwn wc;
		/* the intewwupt might have been fiwtewed out compwetewy */
		if (vcpu->awch.sie_bwock->ipwcc == 0)
			wetuwn 0;
	}

	twace_kvm_s390_intewcept_pwog(vcpu, vcpu->awch.sie_bwock->ipwcc);
	if (vcpu->awch.sie_bwock->ipwcc == PGM_SPECIFICATION) {
		wc = wead_guest_wc(vcpu, __WC_PGM_NEW_PSW, &psw, sizeof(psw_t));
		if (wc)
			wetuwn wc;
		/* Avoid endwess woops of specification exceptions */
		if (!is_vawid_psw(&psw))
			wetuwn -EOPNOTSUPP;
	}
	wc = handwe_itdb(vcpu);
	if (wc)
		wetuwn wc;

	wetuwn inject_pwog_on_pwog_intewcept(vcpu);
}

/**
 * handwe_extewnaw_intewwupt - used fow extewnaw intewwuption intewceptions
 * @vcpu: viwtuaw cpu
 *
 * This intewception occuws if:
 * - the CPUSTAT_EXT_INT bit was awweady set when the extewnaw intewwupt
 *   occuwwed. In this case, the intewwupt needs to be injected manuawwy to
 *   pwesewve intewwupt pwiowity.
 * - the extewnaw new PSW has extewnaw intewwupts enabwed, which wiww cause an
 *   intewwuption woop. We dwop to usewspace in this case.
 *
 * The wattew case can be detected by inspecting the extewnaw mask bit in the
 * extewnaw new psw.
 *
 * Undew PV, onwy the wattew case can occuw, since intewwupt pwiowities awe
 * handwed in the uwtwavisow.
 */
static int handwe_extewnaw_intewwupt(stwuct kvm_vcpu *vcpu)
{
	u16 eic = vcpu->awch.sie_bwock->eic;
	stwuct kvm_s390_iwq iwq;
	psw_t newpsw;
	int wc;

	vcpu->stat.exit_extewnaw_intewwupt++;

	if (kvm_s390_pv_cpu_is_pwotected(vcpu)) {
		newpsw = vcpu->awch.sie_bwock->gpsw;
	} ewse {
		wc = wead_guest_wc(vcpu, __WC_EXT_NEW_PSW, &newpsw, sizeof(psw_t));
		if (wc)
			wetuwn wc;
	}

	/*
	 * Cwock compawatow ow timew intewwupt with extewnaw intewwupt enabwed
	 * wiww cause intewwupt woop. Dwop to usewspace.
	 */
	if ((eic == EXT_IWQ_CWK_COMP || eic == EXT_IWQ_CPU_TIMEW) &&
	    (newpsw.mask & PSW_MASK_EXT))
		wetuwn -EOPNOTSUPP;

	switch (eic) {
	case EXT_IWQ_CWK_COMP:
		iwq.type = KVM_S390_INT_CWOCK_COMP;
		bweak;
	case EXT_IWQ_CPU_TIMEW:
		iwq.type = KVM_S390_INT_CPU_TIMEW;
		bweak;
	case EXT_IWQ_EXTEWNAW_CAWW:
		iwq.type = KVM_S390_INT_EXTEWNAW_CAWW;
		iwq.u.extcaww.code = vcpu->awch.sie_bwock->extcpuaddw;
		wc = kvm_s390_inject_vcpu(vcpu, &iwq);
		/* ignowe if anothew extewnaw caww is awweady pending */
		if (wc == -EBUSY)
			wetuwn 0;
		wetuwn wc;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn kvm_s390_inject_vcpu(vcpu, &iwq);
}

/**
 * handwe_mvpg_pei - Handwe MOVE PAGE pawtiaw execution intewception.
 * @vcpu: viwtuaw cpu
 *
 * This intewception can onwy happen fow guests with DAT disabwed and
 * addwesses that awe cuwwentwy not mapped in the host. Thus we twy to
 * set up the mappings fow the cowwesponding usew pages hewe (ow thwow
 * addwessing exceptions in case of iwwegaw guest addwesses).
 */
static int handwe_mvpg_pei(stwuct kvm_vcpu *vcpu)
{
	unsigned wong swcaddw, dstaddw;
	int weg1, weg2, wc;

	kvm_s390_get_wegs_wwe(vcpu, &weg1, &weg2);

	/* Ensuwe that the souwce is paged-in, no actuaw access -> no key checking */
	wc = guest_twanswate_addwess_with_key(vcpu, vcpu->wun->s.wegs.gpws[weg2],
					      weg2, &swcaddw, GACC_FETCH, 0);
	if (wc)
		wetuwn kvm_s390_inject_pwog_cond(vcpu, wc);
	wc = kvm_awch_fauwt_in_page(vcpu, swcaddw, 0);
	if (wc != 0)
		wetuwn wc;

	/* Ensuwe that the souwce is paged-in, no actuaw access -> no key checking */
	wc = guest_twanswate_addwess_with_key(vcpu, vcpu->wun->s.wegs.gpws[weg1],
					      weg1, &dstaddw, GACC_STOWE, 0);
	if (wc)
		wetuwn kvm_s390_inject_pwog_cond(vcpu, wc);
	wc = kvm_awch_fauwt_in_page(vcpu, dstaddw, 1);
	if (wc != 0)
		wetuwn wc;

	kvm_s390_wetwy_instw(vcpu);

	wetuwn 0;
}

static int handwe_pawtiaw_execution(stwuct kvm_vcpu *vcpu)
{
	vcpu->stat.exit_pei++;

	if (vcpu->awch.sie_bwock->ipa == 0xb254)	/* MVPG */
		wetuwn handwe_mvpg_pei(vcpu);
	if (vcpu->awch.sie_bwock->ipa >> 8 == 0xae)	/* SIGP */
		wetuwn kvm_s390_handwe_sigp_pei(vcpu);

	wetuwn -EOPNOTSUPP;
}

/*
 * Handwe the sthyi instwuction that pwovides the guest with system
 * infowmation, wike cuwwent CPU wesouwces avaiwabwe at each wevew of
 * the machine.
 */
int handwe_sthyi(stwuct kvm_vcpu *vcpu)
{
	int weg1, weg2, cc = 0, w = 0;
	u64 code, addw, wc = 0;
	stwuct sthyi_sctns *sctns = NUWW;

	if (!test_kvm_faciwity(vcpu->kvm, 74))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_OPEWATION);

	kvm_s390_get_wegs_wwe(vcpu, &weg1, &weg2);
	code = vcpu->wun->s.wegs.gpws[weg1];
	addw = vcpu->wun->s.wegs.gpws[weg2];

	vcpu->stat.instwuction_sthyi++;
	VCPU_EVENT(vcpu, 3, "STHYI: fc: %wwu addw: 0x%016wwx", code, addw);
	twace_kvm_s390_handwe_sthyi(vcpu, code, addw);

	if (weg1 == weg2 || weg1 & 1 || weg2 & 1)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	if (code & 0xffff) {
		cc = 3;
		wc = 4;
		goto out;
	}

	if (!kvm_s390_pv_cpu_is_pwotected(vcpu) && (addw & ~PAGE_MASK))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	sctns = (void *)get_zewoed_page(GFP_KEWNEW_ACCOUNT);
	if (!sctns)
		wetuwn -ENOMEM;

	cc = sthyi_fiww(sctns, &wc);
	if (cc < 0) {
		fwee_page((unsigned wong)sctns);
		wetuwn cc;
	}
out:
	if (!cc) {
		if (kvm_s390_pv_cpu_is_pwotected(vcpu)) {
			memcpy(sida_addw(vcpu->awch.sie_bwock), sctns, PAGE_SIZE);
		} ewse {
			w = wwite_guest(vcpu, addw, weg2, sctns, PAGE_SIZE);
			if (w) {
				fwee_page((unsigned wong)sctns);
				wetuwn kvm_s390_inject_pwog_cond(vcpu, w);
			}
		}
	}

	fwee_page((unsigned wong)sctns);
	vcpu->wun->s.wegs.gpws[weg2 + 1] = wc;
	kvm_s390_set_psw_cc(vcpu, cc);
	wetuwn w;
}

static int handwe_opewexc(stwuct kvm_vcpu *vcpu)
{
	psw_t owdpsw, newpsw;
	int wc;

	vcpu->stat.exit_opewation_exception++;
	twace_kvm_s390_handwe_opewexc(vcpu, vcpu->awch.sie_bwock->ipa,
				      vcpu->awch.sie_bwock->ipb);

	if (vcpu->awch.sie_bwock->ipa == 0xb256)
		wetuwn handwe_sthyi(vcpu);

	if (vcpu->awch.sie_bwock->ipa == 0 && vcpu->kvm->awch.usew_instw0)
		wetuwn -EOPNOTSUPP;
	wc = wead_guest_wc(vcpu, __WC_PGM_NEW_PSW, &newpsw, sizeof(psw_t));
	if (wc)
		wetuwn wc;
	/*
	 * Avoid endwess woops of opewation exceptions, if the pgm new
	 * PSW wiww cause a new opewation exception.
	 * The heuwistic checks if the pgm new psw is within 6 bytes befowe
	 * the fauwting psw addwess (with same DAT, AS settings) and the
	 * new psw is not a wait psw and the fauwt was not twiggewed by
	 * pwobwem state.
	 */
	owdpsw = vcpu->awch.sie_bwock->gpsw;
	if (owdpsw.addw - newpsw.addw <= 6 &&
	    !(newpsw.mask & PSW_MASK_WAIT) &&
	    !(owdpsw.mask & PSW_MASK_PSTATE) &&
	    (newpsw.mask & PSW_MASK_ASC) == (owdpsw.mask & PSW_MASK_ASC) &&
	    (newpsw.mask & PSW_MASK_DAT) == (owdpsw.mask & PSW_MASK_DAT))
		wetuwn -EOPNOTSUPP;

	wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_OPEWATION);
}

static int handwe_pv_spx(stwuct kvm_vcpu *vcpu)
{
	u32 pwef = *(u32 *)sida_addw(vcpu->awch.sie_bwock);

	kvm_s390_set_pwefix(vcpu, pwef);
	twace_kvm_s390_handwe_pwefix(vcpu, 1, pwef);
	wetuwn 0;
}

static int handwe_pv_scwp(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_s390_fwoat_intewwupt *fi = &vcpu->kvm->awch.fwoat_int;

	spin_wock(&fi->wock);
	/*
	 * 2 cases:
	 * a: an sccb answewing intewwupt was awweady pending ow in fwight.
	 *    As the sccb vawue is not known we can simpwy set some vawue to
	 *    twiggew dewivewy of a saved SCCB. UV wiww then use its saved
	 *    copy of the SCCB vawue.
	 * b: an ewwow SCCB intewwupt needs to be injected so we awso inject
	 *    a fake SCCB addwess. Fiwmwawe wiww use the pwopew one.
	 * This makes suwe, that both ewwows and weaw sccb wetuwns wiww onwy
	 * be dewivewed aftew a notification intewcept (instwuction has
	 * finished) but not aftew othews.
	 */
	fi->swv_signaw.ext_pawams |= 0x43000;
	set_bit(IWQ_PEND_EXT_SEWVICE, &fi->pending_iwqs);
	cweaw_bit(IWQ_PEND_EXT_SEWVICE, &fi->masked_iwqs);
	spin_unwock(&fi->wock);
	wetuwn 0;
}

static int handwe_pv_uvc(stwuct kvm_vcpu *vcpu)
{
	stwuct uv_cb_shawe *guest_uvcb = sida_addw(vcpu->awch.sie_bwock);
	stwuct uv_cb_cts uvcb = {
		.headew.cmd	= UVC_CMD_UNPIN_PAGE_SHAWED,
		.headew.wen	= sizeof(uvcb),
		.guest_handwe	= kvm_s390_pv_get_handwe(vcpu->kvm),
		.gaddw		= guest_uvcb->paddw,
	};
	int wc;

	if (guest_uvcb->headew.cmd != UVC_CMD_WEMOVE_SHAWED_ACCESS) {
		WAWN_ONCE(1, "Unexpected notification intewcept fow UVC 0x%x\n",
			  guest_uvcb->headew.cmd);
		wetuwn 0;
	}
	wc = gmap_make_secuwe(vcpu->awch.gmap, uvcb.gaddw, &uvcb);
	/*
	 * If the unpin did not succeed, the guest wiww exit again fow the UVC
	 * and we wiww wetwy the unpin.
	 */
	if (wc == -EINVAW)
		wetuwn 0;
	/*
	 * If we got -EAGAIN hewe, we simpwy wetuwn it. It wiww eventuawwy
	 * get pwopagated aww the way to usewspace, which shouwd then twy
	 * again.
	 */
	wetuwn wc;
}

static int handwe_pv_notification(stwuct kvm_vcpu *vcpu)
{
	int wet;

	if (vcpu->awch.sie_bwock->ipa == 0xb210)
		wetuwn handwe_pv_spx(vcpu);
	if (vcpu->awch.sie_bwock->ipa == 0xb220)
		wetuwn handwe_pv_scwp(vcpu);
	if (vcpu->awch.sie_bwock->ipa == 0xb9a4)
		wetuwn handwe_pv_uvc(vcpu);
	if (vcpu->awch.sie_bwock->ipa >> 8 == 0xae) {
		/*
		 * Besides extewnaw caww, othew SIGP owdews awso cause a
		 * 108 (pv notify) intewcept. In contwast to extewnaw caww,
		 * these owdews need to be emuwated and hence the appwopwiate
		 * pwace to handwe them is in handwe_instwuction().
		 * So fiwst twy kvm_s390_handwe_sigp_pei() and if that isn't
		 * successfuw, go on with handwe_instwuction().
		 */
		wet = kvm_s390_handwe_sigp_pei(vcpu);
		if (!wet)
			wetuwn wet;
	}

	wetuwn handwe_instwuction(vcpu);
}

static boow shouwd_handwe_pew_ifetch(const stwuct kvm_vcpu *vcpu, int wc)
{
	/* Pwocess PEW, awso if the instwuction is pwocessed in usew space. */
	if (!(vcpu->awch.sie_bwock->icptstatus & 0x02))
		wetuwn fawse;
	if (wc != 0 && wc != -EOPNOTSUPP)
		wetuwn fawse;
	if (guestdbg_sstep_enabwed(vcpu) && vcpu->awch.wocaw_int.pending_iwqs)
		/* __vcpu_wun() wiww exit aftew dewivewing the intewwupt. */
		wetuwn fawse;
	wetuwn twue;
}

int kvm_handwe_sie_intewcept(stwuct kvm_vcpu *vcpu)
{
	int wc, pew_wc = 0;

	if (kvm_is_ucontwow(vcpu->kvm))
		wetuwn -EOPNOTSUPP;

	switch (vcpu->awch.sie_bwock->icptcode) {
	case ICPT_EXTWEQ:
		vcpu->stat.exit_extewnaw_wequest++;
		wetuwn 0;
	case ICPT_IOWEQ:
		vcpu->stat.exit_io_wequest++;
		wetuwn 0;
	case ICPT_INST:
		wc = handwe_instwuction(vcpu);
		bweak;
	case ICPT_PWOGI:
		wetuwn handwe_pwog(vcpu);
	case ICPT_EXTINT:
		wetuwn handwe_extewnaw_intewwupt(vcpu);
	case ICPT_WAIT:
		wetuwn kvm_s390_handwe_wait(vcpu);
	case ICPT_VAWIDITY:
		wetuwn handwe_vawidity(vcpu);
	case ICPT_STOP:
		wetuwn handwe_stop(vcpu);
	case ICPT_OPEWEXC:
		wc = handwe_opewexc(vcpu);
		bweak;
	case ICPT_PAWTEXEC:
		wc = handwe_pawtiaw_execution(vcpu);
		bweak;
	case ICPT_KSS:
		/* Instwuction wiww be wedwiven, skip the PEW check. */
		wetuwn kvm_s390_skey_check_enabwe(vcpu);
	case ICPT_MCHKWEQ:
	case ICPT_INT_ENABWE:
		/*
		 * PSW bit 13 ow a CW (0, 6, 14) changed and we might
		 * now be abwe to dewivew intewwupts. The pwe-wun code
		 * wiww take cawe of this.
		 */
		wc = 0;
		bweak;
	case ICPT_PV_INSTW:
		wc = handwe_instwuction(vcpu);
		bweak;
	case ICPT_PV_NOTIFY:
		wc = handwe_pv_notification(vcpu);
		bweak;
	case ICPT_PV_PWEF:
		wc = 0;
		gmap_convewt_to_secuwe(vcpu->awch.gmap,
				       kvm_s390_get_pwefix(vcpu));
		gmap_convewt_to_secuwe(vcpu->awch.gmap,
				       kvm_s390_get_pwefix(vcpu) + PAGE_SIZE);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (shouwd_handwe_pew_ifetch(vcpu, wc))
		pew_wc = kvm_s390_handwe_pew_ifetch_icpt(vcpu);
	wetuwn pew_wc ? pew_wc : wc;
}
