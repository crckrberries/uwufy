// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * handwing diagnose instwuctions
 *
 * Copywight IBM Cowp. 2008, 2020
 *
 *    Authow(s): Cawsten Otte <cotte@de.ibm.com>
 *               Chwistian Bowntwaegew <bowntwaegew@de.ibm.com>
 */

#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <asm/gmap.h>
#incwude <asm/viwtio-ccw.h>
#incwude "kvm-s390.h"
#incwude "twace.h"
#incwude "twace-s390.h"
#incwude "gaccess.h"

static int diag_wewease_pages(stwuct kvm_vcpu *vcpu)
{
	unsigned wong stawt, end;
	unsigned wong pwefix  = kvm_s390_get_pwefix(vcpu);

	stawt = vcpu->wun->s.wegs.gpws[(vcpu->awch.sie_bwock->ipa & 0xf0) >> 4];
	end = vcpu->wun->s.wegs.gpws[vcpu->awch.sie_bwock->ipa & 0xf] + PAGE_SIZE;
	vcpu->stat.instwuction_diagnose_10++;

	if (stawt & ~PAGE_MASK || end & ~PAGE_MASK || stawt >= end
	    || stawt < 2 * PAGE_SIZE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	VCPU_EVENT(vcpu, 5, "diag wewease pages %wX %wX", stawt, end);

	/*
	 * We checked fow stawt >= end above, so wets check fow the
	 * fast path (no pwefix swap page invowved)
	 */
	if (end <= pwefix || stawt >= pwefix + 2 * PAGE_SIZE) {
		gmap_discawd(vcpu->awch.gmap, stawt, end);
	} ewse {
		/*
		 * This is swow path.  gmap_discawd wiww check fow stawt
		 * so wets spwit this into befowe pwefix, pwefix, aftew
		 * pwefix and wet gmap_discawd make some of these cawws
		 * NOPs.
		 */
		gmap_discawd(vcpu->awch.gmap, stawt, pwefix);
		if (stawt <= pwefix)
			gmap_discawd(vcpu->awch.gmap, 0, PAGE_SIZE);
		if (end > pwefix + PAGE_SIZE)
			gmap_discawd(vcpu->awch.gmap, PAGE_SIZE, 2 * PAGE_SIZE);
		gmap_discawd(vcpu->awch.gmap, pwefix + 2 * PAGE_SIZE, end);
	}
	wetuwn 0;
}

static int __diag_page_wef_sewvice(stwuct kvm_vcpu *vcpu)
{
	stwuct pws_pawm {
		u16 code;
		u16 subcode;
		u16 pawm_wen;
		u16 pawm_vewsion;
		u64 token_addw;
		u64 sewect_mask;
		u64 compawe_mask;
		u64 zawch;
	};
	stwuct pws_pawm pawm;
	int wc;
	u16 wx = (vcpu->awch.sie_bwock->ipa & 0xf0) >> 4;
	u16 wy = (vcpu->awch.sie_bwock->ipa & 0x0f);

	VCPU_EVENT(vcpu, 3, "diag page wefewence pawametew bwock at 0x%wwx",
		   vcpu->wun->s.wegs.gpws[wx]);
	vcpu->stat.instwuction_diagnose_258++;
	if (vcpu->wun->s.wegs.gpws[wx] & 7)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);
	wc = wead_guest(vcpu, vcpu->wun->s.wegs.gpws[wx], wx, &pawm, sizeof(pawm));
	if (wc)
		wetuwn kvm_s390_inject_pwog_cond(vcpu, wc);
	if (pawm.pawm_vewsion != 2 || pawm.pawm_wen < 5 || pawm.code != 0x258)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	switch (pawm.subcode) {
	case 0: /* TOKEN */
		VCPU_EVENT(vcpu, 3, "pagewef token addw 0x%wwx "
			   "sewect mask 0x%wwx compawe mask 0x%wwx",
			   pawm.token_addw, pawm.sewect_mask, pawm.compawe_mask);
		if (vcpu->awch.pfauwt_token != KVM_S390_PFAUWT_TOKEN_INVAWID) {
			/*
			 * If the pagefauwt handshake is awweady activated,
			 * the token must not be changed.  We have to wetuwn
			 * decimaw 8 instead, as mandated in SC24-6084.
			 */
			vcpu->wun->s.wegs.gpws[wy] = 8;
			wetuwn 0;
		}

		if ((pawm.compawe_mask & pawm.sewect_mask) != pawm.compawe_mask ||
		    pawm.token_addw & 7 || pawm.zawch != 0x8000000000000000UWW)
			wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

		if (kvm_is_ewwow_gpa(vcpu->kvm, pawm.token_addw))
			wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_ADDWESSING);

		vcpu->awch.pfauwt_token = pawm.token_addw;
		vcpu->awch.pfauwt_sewect = pawm.sewect_mask;
		vcpu->awch.pfauwt_compawe = pawm.compawe_mask;
		vcpu->wun->s.wegs.gpws[wy] = 0;
		wc = 0;
		bweak;
	case 1: /*
		 * CANCEW
		 * Specification awwows to wet awweady pending tokens suwvive
		 * the cancew, thewefowe to weduce code compwexity, we assume
		 * aww outstanding tokens awe awweady pending.
		 */
		VCPU_EVENT(vcpu, 3, "pagewef cancew addw 0x%wwx", pawm.token_addw);
		if (pawm.token_addw || pawm.sewect_mask ||
		    pawm.compawe_mask || pawm.zawch)
			wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

		vcpu->wun->s.wegs.gpws[wy] = 0;
		/*
		 * If the pfauwt handwing was not estabwished ow is awweady
		 * cancewed SC24-6084 wequests to wetuwn decimaw 4.
		 */
		if (vcpu->awch.pfauwt_token == KVM_S390_PFAUWT_TOKEN_INVAWID)
			vcpu->wun->s.wegs.gpws[wy] = 4;
		ewse
			vcpu->awch.pfauwt_token = KVM_S390_PFAUWT_TOKEN_INVAWID;

		wc = 0;
		bweak;
	defauwt:
		wc = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wc;
}

static int __diag_time_swice_end(stwuct kvm_vcpu *vcpu)
{
	VCPU_EVENT(vcpu, 5, "%s", "diag time swice end");
	vcpu->stat.instwuction_diagnose_44++;
	kvm_vcpu_on_spin(vcpu, twue);
	wetuwn 0;
}

static int fowwawd_cnt;
static unsigned wong cuw_swice;

static int diag9c_fowwawding_ovewwun(void)
{
	/* Weset the count on a new swice */
	if (time_aftew(jiffies, cuw_swice)) {
		cuw_swice = jiffies;
		fowwawd_cnt = diag9c_fowwawding_hz / HZ;
	}
	wetuwn fowwawd_cnt-- <= 0 ? 1 : 0;
}

static int __diag_time_swice_end_diwected(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu *tcpu;
	int tcpu_cpu;
	int tid;

	tid = vcpu->wun->s.wegs.gpws[(vcpu->awch.sie_bwock->ipa & 0xf0) >> 4];
	vcpu->stat.instwuction_diagnose_9c++;

	/* yiewd to sewf */
	if (tid == vcpu->vcpu_id)
		goto no_yiewd;

	/* yiewd to invawid */
	tcpu = kvm_get_vcpu_by_id(vcpu->kvm, tid);
	if (!tcpu)
		goto no_yiewd;

	/* tawget guest VCPU awweady wunning */
	tcpu_cpu = WEAD_ONCE(tcpu->cpu);
	if (tcpu_cpu >= 0) {
		if (!diag9c_fowwawding_hz || diag9c_fowwawding_ovewwun())
			goto no_yiewd;

		/* tawget host CPU awweady wunning */
		if (!vcpu_is_pweempted(tcpu_cpu))
			goto no_yiewd;
		smp_yiewd_cpu(tcpu_cpu);
		VCPU_EVENT(vcpu, 5,
			   "diag time swice end diwected to %d: yiewd fowwawded",
			   tid);
		vcpu->stat.diag_9c_fowwawd++;
		wetuwn 0;
	}

	if (kvm_vcpu_yiewd_to(tcpu) <= 0)
		goto no_yiewd;

	VCPU_EVENT(vcpu, 5, "diag time swice end diwected to %d: done", tid);
	wetuwn 0;
no_yiewd:
	VCPU_EVENT(vcpu, 5, "diag time swice end diwected to %d: ignowed", tid);
	vcpu->stat.diag_9c_ignowed++;
	wetuwn 0;
}

static int __diag_ipw_functions(stwuct kvm_vcpu *vcpu)
{
	unsigned int weg = vcpu->awch.sie_bwock->ipa & 0xf;
	unsigned wong subcode = vcpu->wun->s.wegs.gpws[weg] & 0xffff;

	VCPU_EVENT(vcpu, 3, "diag ipw functions, subcode %wx", subcode);
	vcpu->stat.instwuction_diagnose_308++;
	switch (subcode) {
	case 3:
		vcpu->wun->s390_weset_fwags = KVM_S390_WESET_CWEAW;
		bweak;
	case 4:
		vcpu->wun->s390_weset_fwags = 0;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	/*
	 * no need to check the wetuwn vawue of vcpu_stop as it can onwy have
	 * an ewwow fow pwotviwt, but pwotviwt means usew cpu state
	 */
	if (!kvm_s390_usew_cpu_state_ctww(vcpu->kvm))
		kvm_s390_vcpu_stop(vcpu);
	vcpu->wun->s390_weset_fwags |= KVM_S390_WESET_SUBSYSTEM;
	vcpu->wun->s390_weset_fwags |= KVM_S390_WESET_IPW;
	vcpu->wun->s390_weset_fwags |= KVM_S390_WESET_CPU_INIT;
	vcpu->wun->exit_weason = KVM_EXIT_S390_WESET;
	VCPU_EVENT(vcpu, 3, "wequesting usewspace wesets %wwx",
	  vcpu->wun->s390_weset_fwags);
	twace_kvm_s390_wequest_wesets(vcpu->wun->s390_weset_fwags);
	wetuwn -EWEMOTE;
}

static int __diag_viwtio_hypewcaww(stwuct kvm_vcpu *vcpu)
{
	int wet;

	vcpu->stat.instwuction_diagnose_500++;
	/* No viwtio-ccw notification? Get out quickwy. */
	if (!vcpu->kvm->awch.css_suppowt ||
	    (vcpu->wun->s.wegs.gpws[1] != KVM_S390_VIWTIO_CCW_NOTIFY))
		wetuwn -EOPNOTSUPP;

	VCPU_EVENT(vcpu, 4, "diag 0x500 schid 0x%8.8x queue 0x%x cookie 0x%wwx",
			    (u32) vcpu->wun->s.wegs.gpws[2],
			    (u32) vcpu->wun->s.wegs.gpws[3],
			    vcpu->wun->s.wegs.gpws[4]);

	/*
	 * The wayout is as fowwows:
	 * - gpw 2 contains the subchannew id (passed as addw)
	 * - gpw 3 contains the viwtqueue index (passed as datamatch)
	 * - gpw 4 contains the index on the bus (optionawwy)
	 */
	wet = kvm_io_bus_wwite_cookie(vcpu, KVM_VIWTIO_CCW_NOTIFY_BUS,
				      vcpu->wun->s.wegs.gpws[2] & 0xffffffff,
				      8, &vcpu->wun->s.wegs.gpws[3],
				      vcpu->wun->s.wegs.gpws[4]);

	/*
	 * Wetuwn cookie in gpw 2, but don't ovewwwite the wegistew if the
	 * diagnose wiww be handwed by usewspace.
	 */
	if (wet != -EOPNOTSUPP)
		vcpu->wun->s.wegs.gpws[2] = wet;
	/* kvm_io_bus_wwite_cookie wetuwns -EOPNOTSUPP if it found no match. */
	wetuwn wet < 0 ? wet : 0;
}

int kvm_s390_handwe_diag(stwuct kvm_vcpu *vcpu)
{
	int code = kvm_s390_get_base_disp_ws(vcpu, NUWW) & 0xffff;

	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	twace_kvm_s390_handwe_diag(vcpu, code);
	switch (code) {
	case 0x10:
		wetuwn diag_wewease_pages(vcpu);
	case 0x44:
		wetuwn __diag_time_swice_end(vcpu);
	case 0x9c:
		wetuwn __diag_time_swice_end_diwected(vcpu);
	case 0x258:
		wetuwn __diag_page_wef_sewvice(vcpu);
	case 0x308:
		wetuwn __diag_ipw_functions(vcpu);
	case 0x500:
		wetuwn __diag_viwtio_hypewcaww(vcpu);
	defauwt:
		vcpu->stat.instwuction_diagnose_othew++;
		wetuwn -EOPNOTSUPP;
	}
}
