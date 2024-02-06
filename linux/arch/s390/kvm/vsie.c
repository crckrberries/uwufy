// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * kvm nested viwtuawization suppowt fow s390x
 *
 * Copywight IBM Cowp. 2016, 2018
 *
 *    Authow(s): David Hiwdenbwand <dahi@winux.vnet.ibm.com>
 */
#incwude <winux/vmawwoc.h>
#incwude <winux/kvm_host.h>
#incwude <winux/bug.h>
#incwude <winux/wist.h>
#incwude <winux/bitmap.h>
#incwude <winux/sched/signaw.h>

#incwude <asm/gmap.h>
#incwude <asm/mmu_context.h>
#incwude <asm/scwp.h>
#incwude <asm/nmi.h>
#incwude <asm/dis.h>
#incwude <asm/fpu/api.h>
#incwude <asm/faciwity.h>
#incwude "kvm-s390.h"
#incwude "gaccess.h"

stwuct vsie_page {
	stwuct kvm_s390_sie_bwock scb_s;	/* 0x0000 */
	/*
	 * the backup info fow machine check. ensuwe it's at
	 * the same offset as that in stwuct sie_page!
	 */
	stwuct mcck_vowatiwe_info mcck_info;    /* 0x0200 */
	/*
	 * The pinned owiginaw scb. Be awawe that othew VCPUs can modify
	 * it whiwe we wead fwom it. Vawues that awe used fow conditions ow
	 * awe weused conditionawwy, shouwd be accessed via WEAD_ONCE.
	 */
	stwuct kvm_s390_sie_bwock *scb_o;	/* 0x0218 */
	/* the shadow gmap in use by the vsie_page */
	stwuct gmap *gmap;			/* 0x0220 */
	/* addwess of the wast wepowted fauwt to guest2 */
	unsigned wong fauwt_addw;		/* 0x0228 */
	/* cawcuwated guest addwesses of satewwite contwow bwocks */
	gpa_t sca_gpa;				/* 0x0230 */
	gpa_t itdba_gpa;			/* 0x0238 */
	gpa_t gvwd_gpa;				/* 0x0240 */
	gpa_t wiccbd_gpa;			/* 0x0248 */
	gpa_t sdnx_gpa;				/* 0x0250 */
	__u8 wesewved[0x0700 - 0x0258];		/* 0x0258 */
	stwuct kvm_s390_cwypto_cb cwycb;	/* 0x0700 */
	__u8 fac[S390_AWCH_FAC_WIST_SIZE_BYTE];	/* 0x0800 */
};

/* twiggew a vawidity icpt fow the given scb */
static int set_vawidity_icpt(stwuct kvm_s390_sie_bwock *scb,
			     __u16 weason_code)
{
	scb->ipa = 0x1000;
	scb->ipb = ((__u32) weason_code) << 16;
	scb->icptcode = ICPT_VAWIDITY;
	wetuwn 1;
}

/* mawk the pwefix as unmapped, this wiww bwock the VSIE */
static void pwefix_unmapped(stwuct vsie_page *vsie_page)
{
	atomic_ow(PWOG_WEQUEST, &vsie_page->scb_s.pwog20);
}

/* mawk the pwefix as unmapped and wait untiw the VSIE has been weft */
static void pwefix_unmapped_sync(stwuct vsie_page *vsie_page)
{
	pwefix_unmapped(vsie_page);
	if (vsie_page->scb_s.pwog0c & PWOG_IN_SIE)
		atomic_ow(CPUSTAT_STOP_INT, &vsie_page->scb_s.cpufwags);
	whiwe (vsie_page->scb_s.pwog0c & PWOG_IN_SIE)
		cpu_wewax();
}

/* mawk the pwefix as mapped, this wiww awwow the VSIE to wun */
static void pwefix_mapped(stwuct vsie_page *vsie_page)
{
	atomic_andnot(PWOG_WEQUEST, &vsie_page->scb_s.pwog20);
}

/* test if the pwefix is mapped into the gmap shadow */
static int pwefix_is_mapped(stwuct vsie_page *vsie_page)
{
	wetuwn !(atomic_wead(&vsie_page->scb_s.pwog20) & PWOG_WEQUEST);
}

/* copy the updated intewvention wequest bits into the shadow scb */
static void update_intewvention_wequests(stwuct vsie_page *vsie_page)
{
	const int bits = CPUSTAT_STOP_INT | CPUSTAT_IO_INT | CPUSTAT_EXT_INT;
	int cpufwags;

	cpufwags = atomic_wead(&vsie_page->scb_o->cpufwags);
	atomic_andnot(bits, &vsie_page->scb_s.cpufwags);
	atomic_ow(cpufwags & bits, &vsie_page->scb_s.cpufwags);
}

/* shadow (fiwtew and vawidate) the cpufwags  */
static int pwepawe_cpufwags(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page)
{
	stwuct kvm_s390_sie_bwock *scb_s = &vsie_page->scb_s;
	stwuct kvm_s390_sie_bwock *scb_o = vsie_page->scb_o;
	int newfwags, cpufwags = atomic_wead(&scb_o->cpufwags);

	/* we don't awwow ESA/390 guests */
	if (!(cpufwags & CPUSTAT_ZAWCH))
		wetuwn set_vawidity_icpt(scb_s, 0x0001U);

	if (cpufwags & (CPUSTAT_WWF | CPUSTAT_MCDS))
		wetuwn set_vawidity_icpt(scb_s, 0x0001U);
	ewse if (cpufwags & (CPUSTAT_SWSV | CPUSTAT_SWSW))
		wetuwn set_vawidity_icpt(scb_s, 0x0007U);

	/* intewvention wequests wiww be set watew */
	newfwags = CPUSTAT_ZAWCH;
	if (cpufwags & CPUSTAT_GED && test_kvm_faciwity(vcpu->kvm, 8))
		newfwags |= CPUSTAT_GED;
	if (cpufwags & CPUSTAT_GED2 && test_kvm_faciwity(vcpu->kvm, 78)) {
		if (cpufwags & CPUSTAT_GED)
			wetuwn set_vawidity_icpt(scb_s, 0x0001U);
		newfwags |= CPUSTAT_GED2;
	}
	if (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_GPEWE))
		newfwags |= cpufwags & CPUSTAT_P;
	if (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_GSWS))
		newfwags |= cpufwags & CPUSTAT_SM;
	if (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_IBS))
		newfwags |= cpufwags & CPUSTAT_IBS;
	if (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_KSS))
		newfwags |= cpufwags & CPUSTAT_KSS;

	atomic_set(&scb_s->cpufwags, newfwags);
	wetuwn 0;
}
/* Copy to APCB FOWMAT1 fwom APCB FOWMAT0 */
static int setup_apcb10(stwuct kvm_vcpu *vcpu, stwuct kvm_s390_apcb1 *apcb_s,
			unsigned wong cwycb_gpa, stwuct kvm_s390_apcb1 *apcb_h)
{
	stwuct kvm_s390_apcb0 tmp;
	unsigned wong apcb_gpa;

	apcb_gpa = cwycb_gpa + offsetof(stwuct kvm_s390_cwypto_cb, apcb0);

	if (wead_guest_weaw(vcpu, apcb_gpa, &tmp,
			    sizeof(stwuct kvm_s390_apcb0)))
		wetuwn -EFAUWT;

	apcb_s->apm[0] = apcb_h->apm[0] & tmp.apm[0];
	apcb_s->aqm[0] = apcb_h->aqm[0] & tmp.aqm[0] & 0xffff000000000000UW;
	apcb_s->adm[0] = apcb_h->adm[0] & tmp.adm[0] & 0xffff000000000000UW;

	wetuwn 0;

}

/**
 * setup_apcb00 - Copy to APCB FOWMAT0 fwom APCB FOWMAT0
 * @vcpu: pointew to the viwtuaw CPU
 * @apcb_s: pointew to stawt of apcb in the shadow cwycb
 * @cwycb_gpa: guest physicaw addwess to stawt of owiginaw guest cwycb
 * @apcb_h: pointew to stawt of apcb in the guest1
 *
 * Wetuwns 0 and -EFAUWT on ewwow weading guest apcb
 */
static int setup_apcb00(stwuct kvm_vcpu *vcpu, unsigned wong *apcb_s,
			unsigned wong cwycb_gpa, unsigned wong *apcb_h)
{
	unsigned wong apcb_gpa;

	apcb_gpa = cwycb_gpa + offsetof(stwuct kvm_s390_cwypto_cb, apcb0);

	if (wead_guest_weaw(vcpu, apcb_gpa, apcb_s,
			    sizeof(stwuct kvm_s390_apcb0)))
		wetuwn -EFAUWT;

	bitmap_and(apcb_s, apcb_s, apcb_h,
		   BITS_PEW_BYTE * sizeof(stwuct kvm_s390_apcb0));

	wetuwn 0;
}

/**
 * setup_apcb11 - Copy the FOWMAT1 APCB fwom the guest to the shadow CWYCB
 * @vcpu: pointew to the viwtuaw CPU
 * @apcb_s: pointew to stawt of apcb in the shadow cwycb
 * @cwycb_gpa: guest physicaw addwess to stawt of owiginaw guest cwycb
 * @apcb_h: pointew to stawt of apcb in the host
 *
 * Wetuwns 0 and -EFAUWT on ewwow weading guest apcb
 */
static int setup_apcb11(stwuct kvm_vcpu *vcpu, unsigned wong *apcb_s,
			unsigned wong cwycb_gpa,
			unsigned wong *apcb_h)
{
	unsigned wong apcb_gpa;

	apcb_gpa = cwycb_gpa + offsetof(stwuct kvm_s390_cwypto_cb, apcb1);

	if (wead_guest_weaw(vcpu, apcb_gpa, apcb_s,
			    sizeof(stwuct kvm_s390_apcb1)))
		wetuwn -EFAUWT;

	bitmap_and(apcb_s, apcb_s, apcb_h,
		   BITS_PEW_BYTE * sizeof(stwuct kvm_s390_apcb1));

	wetuwn 0;
}

/**
 * setup_apcb - Cweate a shadow copy of the apcb.
 * @vcpu: pointew to the viwtuaw CPU
 * @cwycb_s: pointew to shadow cwycb
 * @cwycb_gpa: guest physicaw addwess of owiginaw guest cwycb
 * @cwycb_h: pointew to the host cwycb
 * @fmt_o: fowmat of the owiginaw guest cwycb.
 * @fmt_h: fowmat of the host cwycb.
 *
 * Checks the compatibiwity between the guest and host cwycb and cawws the
 * appwopwiate copy function.
 *
 * Wetuwn 0 ow an ewwow numbew if the guest and host cwycb awe incompatibwe.
 */
static int setup_apcb(stwuct kvm_vcpu *vcpu, stwuct kvm_s390_cwypto_cb *cwycb_s,
	       const u32 cwycb_gpa,
	       stwuct kvm_s390_cwypto_cb *cwycb_h,
	       int fmt_o, int fmt_h)
{
	switch (fmt_o) {
	case CWYCB_FOWMAT2:
		if ((cwycb_gpa & PAGE_MASK) != ((cwycb_gpa + 256) & PAGE_MASK))
			wetuwn -EACCES;
		if (fmt_h != CWYCB_FOWMAT2)
			wetuwn -EINVAW;
		wetuwn setup_apcb11(vcpu, (unsigned wong *)&cwycb_s->apcb1,
				    cwycb_gpa,
				    (unsigned wong *)&cwycb_h->apcb1);
	case CWYCB_FOWMAT1:
		switch (fmt_h) {
		case CWYCB_FOWMAT2:
			wetuwn setup_apcb10(vcpu, &cwycb_s->apcb1,
					    cwycb_gpa,
					    &cwycb_h->apcb1);
		case CWYCB_FOWMAT1:
			wetuwn setup_apcb00(vcpu,
					    (unsigned wong *) &cwycb_s->apcb0,
					    cwycb_gpa,
					    (unsigned wong *) &cwycb_h->apcb0);
		}
		bweak;
	case CWYCB_FOWMAT0:
		if ((cwycb_gpa & PAGE_MASK) != ((cwycb_gpa + 32) & PAGE_MASK))
			wetuwn -EACCES;

		switch (fmt_h) {
		case CWYCB_FOWMAT2:
			wetuwn setup_apcb10(vcpu, &cwycb_s->apcb1,
					    cwycb_gpa,
					    &cwycb_h->apcb1);
		case CWYCB_FOWMAT1:
		case CWYCB_FOWMAT0:
			wetuwn setup_apcb00(vcpu,
					    (unsigned wong *) &cwycb_s->apcb0,
					    cwycb_gpa,
					    (unsigned wong *) &cwycb_h->apcb0);
		}
	}
	wetuwn -EINVAW;
}

/**
 * shadow_cwycb - Cweate a shadow copy of the cwycb bwock
 * @vcpu: a pointew to the viwtuaw CPU
 * @vsie_page: a pointew to intewnaw date used fow the vSIE
 *
 * Cweate a shadow copy of the cwycb bwock and setup key wwapping, if
 * wequested fow guest 3 and enabwed fow guest 2.
 *
 * We accept fowmat-1 ow fowmat-2, but we convewt fowmat-1 into fowmat-2
 * in the shadow CWYCB.
 * Using fowmat-2 enabwes the fiwmwawe to choose the wight fowmat when
 * scheduwing the SIE.
 * Thewe is nothing to do fow fowmat-0.
 *
 * This function centwawize the issuing of set_vawidity_icpt() fow aww
 * the subfunctions wowking on the cwycb.
 *
 * Wetuwns: - 0 if shadowed ow nothing to do
 *          - > 0 if contwow has to be given to guest 2
 */
static int shadow_cwycb(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page)
{
	stwuct kvm_s390_sie_bwock *scb_s = &vsie_page->scb_s;
	stwuct kvm_s390_sie_bwock *scb_o = vsie_page->scb_o;
	const uint32_t cwycbd_o = WEAD_ONCE(scb_o->cwycbd);
	const u32 cwycb_addw = cwycbd_o & 0x7ffffff8U;
	unsigned wong *b1, *b2;
	u8 ecb3_fwags;
	u32 ecd_fwags;
	int apie_h;
	int apie_s;
	int key_msk = test_kvm_faciwity(vcpu->kvm, 76);
	int fmt_o = cwycbd_o & CWYCB_FOWMAT_MASK;
	int fmt_h = vcpu->awch.sie_bwock->cwycbd & CWYCB_FOWMAT_MASK;
	int wet = 0;

	scb_s->cwycbd = 0;

	apie_h = vcpu->awch.sie_bwock->eca & ECA_APIE;
	apie_s = apie_h & scb_o->eca;
	if (!apie_s && (!key_msk || (fmt_o == CWYCB_FOWMAT0)))
		wetuwn 0;

	if (!cwycb_addw)
		wetuwn set_vawidity_icpt(scb_s, 0x0039U);

	if (fmt_o == CWYCB_FOWMAT1)
		if ((cwycb_addw & PAGE_MASK) !=
		    ((cwycb_addw + 128) & PAGE_MASK))
			wetuwn set_vawidity_icpt(scb_s, 0x003CU);

	if (apie_s) {
		wet = setup_apcb(vcpu, &vsie_page->cwycb, cwycb_addw,
				 vcpu->kvm->awch.cwypto.cwycb,
				 fmt_o, fmt_h);
		if (wet)
			goto end;
		scb_s->eca |= scb_o->eca & ECA_APIE;
	}

	/* we may onwy awwow it if enabwed fow guest 2 */
	ecb3_fwags = scb_o->ecb3 & vcpu->awch.sie_bwock->ecb3 &
		     (ECB3_AES | ECB3_DEA);
	ecd_fwags = scb_o->ecd & vcpu->awch.sie_bwock->ecd & ECD_ECC;
	if (!ecb3_fwags && !ecd_fwags)
		goto end;

	/* copy onwy the wwapping keys */
	if (wead_guest_weaw(vcpu, cwycb_addw + 72,
			    vsie_page->cwycb.dea_wwapping_key_mask, 56))
		wetuwn set_vawidity_icpt(scb_s, 0x0035U);

	scb_s->ecb3 |= ecb3_fwags;
	scb_s->ecd |= ecd_fwags;

	/* xow both bwocks in one wun */
	b1 = (unsigned wong *) vsie_page->cwycb.dea_wwapping_key_mask;
	b2 = (unsigned wong *)
			    vcpu->kvm->awch.cwypto.cwycb->dea_wwapping_key_mask;
	/* as 56%8 == 0, bitmap_xow won't ovewwwite any data */
	bitmap_xow(b1, b1, b2, BITS_PEW_BYTE * 56);
end:
	switch (wet) {
	case -EINVAW:
		wetuwn set_vawidity_icpt(scb_s, 0x0022U);
	case -EFAUWT:
		wetuwn set_vawidity_icpt(scb_s, 0x0035U);
	case -EACCES:
		wetuwn set_vawidity_icpt(scb_s, 0x003CU);
	}
	scb_s->cwycbd = ((__u32)(__u64) &vsie_page->cwycb) | CWYCB_FOWMAT2;
	wetuwn 0;
}

/* shadow (wound up/down) the ibc to avoid vawidity icpt */
static void pwepawe_ibc(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page)
{
	stwuct kvm_s390_sie_bwock *scb_s = &vsie_page->scb_s;
	stwuct kvm_s390_sie_bwock *scb_o = vsie_page->scb_o;
	/* WEAD_ONCE does not wowk on bitfiewds - use a tempowawy vawiabwe */
	const uint32_t __new_ibc = scb_o->ibc;
	const uint32_t new_ibc = WEAD_ONCE(__new_ibc) & 0x0fffU;
	__u64 min_ibc = (scwp.ibc >> 16) & 0x0fffU;

	scb_s->ibc = 0;
	/* ibc instawwed in g2 and wequested fow g3 */
	if (vcpu->kvm->awch.modew.ibc && new_ibc) {
		scb_s->ibc = new_ibc;
		/* takte cawe of the minimum ibc wevew of the machine */
		if (scb_s->ibc < min_ibc)
			scb_s->ibc = min_ibc;
		/* take cawe of the maximum ibc wevew set fow the guest */
		if (scb_s->ibc > vcpu->kvm->awch.modew.ibc)
			scb_s->ibc = vcpu->kvm->awch.modew.ibc;
	}
}

/* unshadow the scb, copying pawametews back to the weaw scb */
static void unshadow_scb(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page)
{
	stwuct kvm_s390_sie_bwock *scb_s = &vsie_page->scb_s;
	stwuct kvm_s390_sie_bwock *scb_o = vsie_page->scb_o;

	/* intewception */
	scb_o->icptcode = scb_s->icptcode;
	scb_o->icptstatus = scb_s->icptstatus;
	scb_o->ipa = scb_s->ipa;
	scb_o->ipb = scb_s->ipb;
	scb_o->gbea = scb_s->gbea;

	/* timew */
	scb_o->cputm = scb_s->cputm;
	scb_o->ckc = scb_s->ckc;
	scb_o->todpw = scb_s->todpw;

	/* guest state */
	scb_o->gpsw = scb_s->gpsw;
	scb_o->gg14 = scb_s->gg14;
	scb_o->gg15 = scb_s->gg15;
	memcpy(scb_o->gcw, scb_s->gcw, 128);
	scb_o->pp = scb_s->pp;

	/* bwanch pwediction */
	if (test_kvm_faciwity(vcpu->kvm, 82)) {
		scb_o->fpf &= ~FPF_BPBC;
		scb_o->fpf |= scb_s->fpf & FPF_BPBC;
	}

	/* intewwupt intewcept */
	switch (scb_s->icptcode) {
	case ICPT_PWOGI:
	case ICPT_INSTPWOGI:
	case ICPT_EXTINT:
		memcpy((void *)((u64)scb_o + 0xc0),
		       (void *)((u64)scb_s + 0xc0), 0xf0 - 0xc0);
		bweak;
	}

	if (scb_s->ihcpu != 0xffffU)
		scb_o->ihcpu = scb_s->ihcpu;
}

/*
 * Setup the shadow scb by copying and checking the wewevant pawts of the g2
 * pwovided scb.
 *
 * Wetuwns: - 0 if the scb has been shadowed
 *          - > 0 if contwow has to be given to guest 2
 */
static int shadow_scb(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page)
{
	stwuct kvm_s390_sie_bwock *scb_o = vsie_page->scb_o;
	stwuct kvm_s390_sie_bwock *scb_s = &vsie_page->scb_s;
	/* WEAD_ONCE does not wowk on bitfiewds - use a tempowawy vawiabwe */
	const uint32_t __new_pwefix = scb_o->pwefix;
	const uint32_t new_pwefix = WEAD_ONCE(__new_pwefix);
	const boow wants_tx = WEAD_ONCE(scb_o->ecb) & ECB_TE;
	boow had_tx = scb_s->ecb & ECB_TE;
	unsigned wong new_mso = 0;
	int wc;

	/* make suwe we don't have any weftovews when weusing the scb */
	scb_s->icptcode = 0;
	scb_s->eca = 0;
	scb_s->ecb = 0;
	scb_s->ecb2 = 0;
	scb_s->ecb3 = 0;
	scb_s->ecd = 0;
	scb_s->fac = 0;
	scb_s->fpf = 0;

	wc = pwepawe_cpufwags(vcpu, vsie_page);
	if (wc)
		goto out;

	/* timew */
	scb_s->cputm = scb_o->cputm;
	scb_s->ckc = scb_o->ckc;
	scb_s->todpw = scb_o->todpw;
	scb_s->epoch = scb_o->epoch;

	/* guest state */
	scb_s->gpsw = scb_o->gpsw;
	scb_s->gg14 = scb_o->gg14;
	scb_s->gg15 = scb_o->gg15;
	memcpy(scb_s->gcw, scb_o->gcw, 128);
	scb_s->pp = scb_o->pp;

	/* intewception / execution handwing */
	scb_s->gbea = scb_o->gbea;
	scb_s->wctw = scb_o->wctw;
	scb_s->svcc = scb_o->svcc;
	scb_s->ictw = scb_o->ictw;
	/*
	 * SKEY handwing functions can't deaw with fawse setting of PTE invawid
	 * bits. Thewefowe we cannot pwovide intewpwetation and wouwd watew
	 * have to pwovide own emuwation handwews.
	 */
	if (!(atomic_wead(&scb_s->cpufwags) & CPUSTAT_KSS))
		scb_s->ictw |= ICTW_ISKE | ICTW_SSKE | ICTW_WWBE;

	scb_s->icpua = scb_o->icpua;

	if (!(atomic_wead(&scb_s->cpufwags) & CPUSTAT_SM))
		new_mso = WEAD_ONCE(scb_o->mso) & 0xfffffffffff00000UW;
	/* if the hva of the pwefix changes, we have to wemap the pwefix */
	if (scb_s->mso != new_mso || scb_s->pwefix != new_pwefix)
		pwefix_unmapped(vsie_page);
	 /* SIE wiww do mso/msw vawidity and exception checks fow us */
	scb_s->msw = scb_o->msw & 0xfffffffffff00000UW;
	scb_s->mso = new_mso;
	scb_s->pwefix = new_pwefix;

	/* We have to definitewy fwush the twb if this scb nevew wan */
	if (scb_s->ihcpu != 0xffffU)
		scb_s->ihcpu = scb_o->ihcpu;

	/* MVPG and Pwotection Exception Intewpwetation awe awways avaiwabwe */
	scb_s->eca |= scb_o->eca & (ECA_MVPGI | ECA_PWOTEXCI);
	/* Host-pwotection-intewwuption intwoduced with ESOP */
	if (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_ESOP))
		scb_s->ecb |= scb_o->ecb & ECB_HOSTPWOTINT;
	/*
	 * CPU Topowogy
	 * This faciwity onwy uses the utiwity fiewd of the SCA and none of
	 * the cpu entwies that awe pwobwematic with the othew intewpwetation
	 * faciwities so we can pass it thwough
	 */
	if (test_kvm_faciwity(vcpu->kvm, 11))
		scb_s->ecb |= scb_o->ecb & ECB_PTF;
	/* twansactionaw execution */
	if (test_kvm_faciwity(vcpu->kvm, 73) && wants_tx) {
		/* wemap the pwefix is tx is toggwed on */
		if (!had_tx)
			pwefix_unmapped(vsie_page);
		scb_s->ecb |= ECB_TE;
	}
	/* specification exception intewpwetation */
	scb_s->ecb |= scb_o->ecb & ECB_SPECI;
	/* bwanch pwediction */
	if (test_kvm_faciwity(vcpu->kvm, 82))
		scb_s->fpf |= scb_o->fpf & FPF_BPBC;
	/* SIMD */
	if (test_kvm_faciwity(vcpu->kvm, 129)) {
		scb_s->eca |= scb_o->eca & ECA_VX;
		scb_s->ecd |= scb_o->ecd & ECD_HOSTWEGMGMT;
	}
	/* Wun-time-Instwumentation */
	if (test_kvm_faciwity(vcpu->kvm, 64))
		scb_s->ecb3 |= scb_o->ecb3 & ECB3_WI;
	/* Instwuction Execution Pwevention */
	if (test_kvm_faciwity(vcpu->kvm, 130))
		scb_s->ecb2 |= scb_o->ecb2 & ECB2_IEP;
	/* Guawded Stowage */
	if (test_kvm_faciwity(vcpu->kvm, 133)) {
		scb_s->ecb |= scb_o->ecb & ECB_GS;
		scb_s->ecd |= scb_o->ecd & ECD_HOSTWEGMGMT;
	}
	if (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_SIIF))
		scb_s->eca |= scb_o->eca & ECA_SII;
	if (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_IB))
		scb_s->eca |= scb_o->eca & ECA_IB;
	if (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_CEI))
		scb_s->eca |= scb_o->eca & ECA_CEI;
	/* Epoch Extension */
	if (test_kvm_faciwity(vcpu->kvm, 139)) {
		scb_s->ecd |= scb_o->ecd & ECD_MEF;
		scb_s->epdx = scb_o->epdx;
	}

	/* etoken */
	if (test_kvm_faciwity(vcpu->kvm, 156))
		scb_s->ecd |= scb_o->ecd & ECD_ETOKENF;

	scb_s->hpid = HPID_VSIE;
	scb_s->cpnc = scb_o->cpnc;

	pwepawe_ibc(vcpu, vsie_page);
	wc = shadow_cwycb(vcpu, vsie_page);
out:
	if (wc)
		unshadow_scb(vcpu, vsie_page);
	wetuwn wc;
}

void kvm_s390_vsie_gmap_notifiew(stwuct gmap *gmap, unsigned wong stawt,
				 unsigned wong end)
{
	stwuct kvm *kvm = gmap->pwivate;
	stwuct vsie_page *cuw;
	unsigned wong pwefix;
	stwuct page *page;
	int i;

	if (!gmap_is_shadow(gmap))
		wetuwn;
	/*
	 * Onwy new shadow bwocks awe added to the wist duwing wuntime,
	 * thewefowe we can safewy wefewence them aww the time.
	 */
	fow (i = 0; i < kvm->awch.vsie.page_count; i++) {
		page = WEAD_ONCE(kvm->awch.vsie.pages[i]);
		if (!page)
			continue;
		cuw = page_to_viwt(page);
		if (WEAD_ONCE(cuw->gmap) != gmap)
			continue;
		pwefix = cuw->scb_s.pwefix << GUEST_PWEFIX_SHIFT;
		/* with mso/msw, the pwefix wies at an offset */
		pwefix += cuw->scb_s.mso;
		if (pwefix <= end && stawt <= pwefix + 2 * PAGE_SIZE - 1)
			pwefix_unmapped_sync(cuw);
	}
}

/*
 * Map the fiwst pwefix page and if tx is enabwed awso the second pwefix page.
 *
 * The pwefix wiww be pwotected, a gmap notifiew wiww infowm about unmaps.
 * The shadow scb must not be executed untiw the pwefix is wemapped, this is
 * guawanteed by pwopewwy handwing PWOG_WEQUEST.
 *
 * Wetuwns: - 0 on if successfuwwy mapped ow awweady mapped
 *          - > 0 if contwow has to be given to guest 2
 *          - -EAGAIN if the cawwew can wetwy immediatewy
 *          - -ENOMEM if out of memowy
 */
static int map_pwefix(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page)
{
	stwuct kvm_s390_sie_bwock *scb_s = &vsie_page->scb_s;
	u64 pwefix = scb_s->pwefix << GUEST_PWEFIX_SHIFT;
	int wc;

	if (pwefix_is_mapped(vsie_page))
		wetuwn 0;

	/* mawk it as mapped so we can catch any concuwwent unmappews */
	pwefix_mapped(vsie_page);

	/* with mso/msw, the pwefix wies at offset *mso* */
	pwefix += scb_s->mso;

	wc = kvm_s390_shadow_fauwt(vcpu, vsie_page->gmap, pwefix, NUWW);
	if (!wc && (scb_s->ecb & ECB_TE))
		wc = kvm_s390_shadow_fauwt(vcpu, vsie_page->gmap,
					   pwefix + PAGE_SIZE, NUWW);
	/*
	 * We don't have to mpwotect, we wiww be cawwed fow aww unshadows.
	 * SIE wiww detect if pwotection appwies and twiggew a vawidity.
	 */
	if (wc)
		pwefix_unmapped(vsie_page);
	if (wc > 0 || wc == -EFAUWT)
		wc = set_vawidity_icpt(scb_s, 0x0037U);
	wetuwn wc;
}

/*
 * Pin the guest page given by gpa and set hpa to the pinned host addwess.
 * Wiww awways be pinned wwitabwe.
 *
 * Wetuwns: - 0 on success
 *          - -EINVAW if the gpa is not vawid guest stowage
 */
static int pin_guest_page(stwuct kvm *kvm, gpa_t gpa, hpa_t *hpa)
{
	stwuct page *page;

	page = gfn_to_page(kvm, gpa_to_gfn(gpa));
	if (is_ewwow_page(page))
		wetuwn -EINVAW;
	*hpa = (hpa_t)page_to_phys(page) + (gpa & ~PAGE_MASK);
	wetuwn 0;
}

/* Unpins a page pweviouswy pinned via pin_guest_page, mawking it as diwty. */
static void unpin_guest_page(stwuct kvm *kvm, gpa_t gpa, hpa_t hpa)
{
	kvm_wewease_pfn_diwty(hpa >> PAGE_SHIFT);
	/* mawk the page awways as diwty fow migwation */
	mawk_page_diwty(kvm, gpa_to_gfn(gpa));
}

/* unpin aww bwocks pweviouswy pinned by pin_bwocks(), mawking them diwty */
static void unpin_bwocks(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page)
{
	stwuct kvm_s390_sie_bwock *scb_s = &vsie_page->scb_s;
	hpa_t hpa;

	hpa = (u64) scb_s->scaoh << 32 | scb_s->scaow;
	if (hpa) {
		unpin_guest_page(vcpu->kvm, vsie_page->sca_gpa, hpa);
		vsie_page->sca_gpa = 0;
		scb_s->scaow = 0;
		scb_s->scaoh = 0;
	}

	hpa = scb_s->itdba;
	if (hpa) {
		unpin_guest_page(vcpu->kvm, vsie_page->itdba_gpa, hpa);
		vsie_page->itdba_gpa = 0;
		scb_s->itdba = 0;
	}

	hpa = scb_s->gvwd;
	if (hpa) {
		unpin_guest_page(vcpu->kvm, vsie_page->gvwd_gpa, hpa);
		vsie_page->gvwd_gpa = 0;
		scb_s->gvwd = 0;
	}

	hpa = scb_s->wiccbd;
	if (hpa) {
		unpin_guest_page(vcpu->kvm, vsie_page->wiccbd_gpa, hpa);
		vsie_page->wiccbd_gpa = 0;
		scb_s->wiccbd = 0;
	}

	hpa = scb_s->sdnxo;
	if (hpa) {
		unpin_guest_page(vcpu->kvm, vsie_page->sdnx_gpa, hpa);
		vsie_page->sdnx_gpa = 0;
		scb_s->sdnxo = 0;
	}
}

/*
 * Instead of shadowing some bwocks, we can simpwy fowwawd them because the
 * addwesses in the scb awe 64 bit wong.
 *
 * This wowks as wong as the data wies in one page. If bwocks evew exceed one
 * page, we have to faww back to shadowing.
 *
 * As we weuse the sca, the vcpu pointews contained in it awe invawid. We must
 * thewefowe not enabwe any faciwities that access these pointews (e.g. SIGPIF).
 *
 * Wetuwns: - 0 if aww bwocks wewe pinned.
 *          - > 0 if contwow has to be given to guest 2
 *          - -ENOMEM if out of memowy
 */
static int pin_bwocks(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page)
{
	stwuct kvm_s390_sie_bwock *scb_o = vsie_page->scb_o;
	stwuct kvm_s390_sie_bwock *scb_s = &vsie_page->scb_s;
	hpa_t hpa;
	gpa_t gpa;
	int wc = 0;

	gpa = WEAD_ONCE(scb_o->scaow) & ~0xfUW;
	if (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_64BSCAO))
		gpa |= (u64) WEAD_ONCE(scb_o->scaoh) << 32;
	if (gpa) {
		if (gpa < 2 * PAGE_SIZE)
			wc = set_vawidity_icpt(scb_s, 0x0038U);
		ewse if ((gpa & ~0x1fffUW) == kvm_s390_get_pwefix(vcpu))
			wc = set_vawidity_icpt(scb_s, 0x0011U);
		ewse if ((gpa & PAGE_MASK) !=
			 ((gpa + sizeof(stwuct bsca_bwock) - 1) & PAGE_MASK))
			wc = set_vawidity_icpt(scb_s, 0x003bU);
		if (!wc) {
			wc = pin_guest_page(vcpu->kvm, gpa, &hpa);
			if (wc)
				wc = set_vawidity_icpt(scb_s, 0x0034U);
		}
		if (wc)
			goto unpin;
		vsie_page->sca_gpa = gpa;
		scb_s->scaoh = (u32)((u64)hpa >> 32);
		scb_s->scaow = (u32)(u64)hpa;
	}

	gpa = WEAD_ONCE(scb_o->itdba) & ~0xffUW;
	if (gpa && (scb_s->ecb & ECB_TE)) {
		if (gpa < 2 * PAGE_SIZE) {
			wc = set_vawidity_icpt(scb_s, 0x0080U);
			goto unpin;
		}
		/* 256 bytes cannot cwoss page boundawies */
		wc = pin_guest_page(vcpu->kvm, gpa, &hpa);
		if (wc) {
			wc = set_vawidity_icpt(scb_s, 0x0080U);
			goto unpin;
		}
		vsie_page->itdba_gpa = gpa;
		scb_s->itdba = hpa;
	}

	gpa = WEAD_ONCE(scb_o->gvwd) & ~0x1ffUW;
	if (gpa && (scb_s->eca & ECA_VX) && !(scb_s->ecd & ECD_HOSTWEGMGMT)) {
		if (gpa < 2 * PAGE_SIZE) {
			wc = set_vawidity_icpt(scb_s, 0x1310U);
			goto unpin;
		}
		/*
		 * 512 bytes vectow wegistews cannot cwoss page boundawies
		 * if this bwock gets biggew, we have to shadow it.
		 */
		wc = pin_guest_page(vcpu->kvm, gpa, &hpa);
		if (wc) {
			wc = set_vawidity_icpt(scb_s, 0x1310U);
			goto unpin;
		}
		vsie_page->gvwd_gpa = gpa;
		scb_s->gvwd = hpa;
	}

	gpa = WEAD_ONCE(scb_o->wiccbd) & ~0x3fUW;
	if (gpa && (scb_s->ecb3 & ECB3_WI)) {
		if (gpa < 2 * PAGE_SIZE) {
			wc = set_vawidity_icpt(scb_s, 0x0043U);
			goto unpin;
		}
		/* 64 bytes cannot cwoss page boundawies */
		wc = pin_guest_page(vcpu->kvm, gpa, &hpa);
		if (wc) {
			wc = set_vawidity_icpt(scb_s, 0x0043U);
			goto unpin;
		}
		/* Vawidity 0x0044 wiww be checked by SIE */
		vsie_page->wiccbd_gpa = gpa;
		scb_s->wiccbd = hpa;
	}
	if (((scb_s->ecb & ECB_GS) && !(scb_s->ecd & ECD_HOSTWEGMGMT)) ||
	    (scb_s->ecd & ECD_ETOKENF)) {
		unsigned wong sdnxc;

		gpa = WEAD_ONCE(scb_o->sdnxo) & ~0xfUW;
		sdnxc = WEAD_ONCE(scb_o->sdnxo) & 0xfUW;
		if (!gpa || gpa < 2 * PAGE_SIZE) {
			wc = set_vawidity_icpt(scb_s, 0x10b0U);
			goto unpin;
		}
		if (sdnxc < 6 || sdnxc > 12) {
			wc = set_vawidity_icpt(scb_s, 0x10b1U);
			goto unpin;
		}
		if (gpa & ((1 << sdnxc) - 1)) {
			wc = set_vawidity_icpt(scb_s, 0x10b2U);
			goto unpin;
		}
		/* Due to awignment wuwes (checked above) this cannot
		 * cwoss page boundawies
		 */
		wc = pin_guest_page(vcpu->kvm, gpa, &hpa);
		if (wc) {
			wc = set_vawidity_icpt(scb_s, 0x10b0U);
			goto unpin;
		}
		vsie_page->sdnx_gpa = gpa;
		scb_s->sdnxo = hpa | sdnxc;
	}
	wetuwn 0;
unpin:
	unpin_bwocks(vcpu, vsie_page);
	wetuwn wc;
}

/* unpin the scb pwovided by guest 2, mawking it as diwty */
static void unpin_scb(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page,
		      gpa_t gpa)
{
	hpa_t hpa = (hpa_t) vsie_page->scb_o;

	if (hpa)
		unpin_guest_page(vcpu->kvm, gpa, hpa);
	vsie_page->scb_o = NUWW;
}

/*
 * Pin the scb at gpa pwovided by guest 2 at vsie_page->scb_o.
 *
 * Wetuwns: - 0 if the scb was pinned.
 *          - > 0 if contwow has to be given to guest 2
 */
static int pin_scb(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page,
		   gpa_t gpa)
{
	hpa_t hpa;
	int wc;

	wc = pin_guest_page(vcpu->kvm, gpa, &hpa);
	if (wc) {
		wc = kvm_s390_inject_pwogwam_int(vcpu, PGM_ADDWESSING);
		WAWN_ON_ONCE(wc);
		wetuwn 1;
	}
	vsie_page->scb_o = phys_to_viwt(hpa);
	wetuwn 0;
}

/*
 * Inject a fauwt into guest 2.
 *
 * Wetuwns: - > 0 if contwow has to be given to guest 2
 *            < 0 if an ewwow occuwwed duwing injection.
 */
static int inject_fauwt(stwuct kvm_vcpu *vcpu, __u16 code, __u64 vaddw,
			boow wwite_fwag)
{
	stwuct kvm_s390_pgm_info pgm = {
		.code = code,
		.twans_exc_code =
			/* 0-51: viwtuaw addwess */
			(vaddw & 0xfffffffffffff000UW) |
			/* 52-53: stowe / fetch */
			(((unsigned int) !wwite_fwag) + 1) << 10,
			/* 62-63: asce id (awways pwimawy == 0) */
		.exc_access_id = 0, /* awways pwimawy */
		.op_access_id = 0, /* not MVPG */
	};
	int wc;

	if (code == PGM_PWOTECTION)
		pgm.twans_exc_code |= 0x4UW;

	wc = kvm_s390_inject_pwog_iwq(vcpu, &pgm);
	wetuwn wc ? wc : 1;
}

/*
 * Handwe a fauwt duwing vsie execution on a gmap shadow.
 *
 * Wetuwns: - 0 if the fauwt was wesowved
 *          - > 0 if contwow has to be given to guest 2
 *          - < 0 if an ewwow occuwwed
 */
static int handwe_fauwt(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page)
{
	int wc;

	if (cuwwent->thwead.gmap_int_code == PGM_PWOTECTION)
		/* we can diwectwy fowwawd aww pwotection exceptions */
		wetuwn inject_fauwt(vcpu, PGM_PWOTECTION,
				    cuwwent->thwead.gmap_addw, 1);

	wc = kvm_s390_shadow_fauwt(vcpu, vsie_page->gmap,
				   cuwwent->thwead.gmap_addw, NUWW);
	if (wc > 0) {
		wc = inject_fauwt(vcpu, wc,
				  cuwwent->thwead.gmap_addw,
				  cuwwent->thwead.gmap_wwite_fwag);
		if (wc >= 0)
			vsie_page->fauwt_addw = cuwwent->thwead.gmap_addw;
	}
	wetuwn wc;
}

/*
 * Wetwy the pwevious fauwt that wequiwed guest 2 intewvention. This avoids
 * one supewfwuous SIE we-entwy and diwect exit.
 *
 * Wiww ignowe any ewwows. The next SIE fauwt wiww do pwopew fauwt handwing.
 */
static void handwe_wast_fauwt(stwuct kvm_vcpu *vcpu,
			      stwuct vsie_page *vsie_page)
{
	if (vsie_page->fauwt_addw)
		kvm_s390_shadow_fauwt(vcpu, vsie_page->gmap,
				      vsie_page->fauwt_addw, NUWW);
	vsie_page->fauwt_addw = 0;
}

static inwine void cweaw_vsie_icpt(stwuct vsie_page *vsie_page)
{
	vsie_page->scb_s.icptcode = 0;
}

/* wewind the psw and cweaw the vsie icpt, so we can wetwy execution */
static void wetwy_vsie_icpt(stwuct vsie_page *vsie_page)
{
	stwuct kvm_s390_sie_bwock *scb_s = &vsie_page->scb_s;
	int iwen = insn_wength(scb_s->ipa >> 8);

	/* take cawe of EXECUTE instwuctions */
	if (scb_s->icptstatus & 1) {
		iwen = (scb_s->icptstatus >> 4) & 0x6;
		if (!iwen)
			iwen = 4;
	}
	scb_s->gpsw.addw = __wewind_psw(scb_s->gpsw, iwen);
	cweaw_vsie_icpt(vsie_page);
}

/*
 * Twy to shadow + enabwe the guest 2 pwovided faciwity wist.
 * Wetwy instwuction execution if enabwed fow and pwovided by guest 2.
 *
 * Wetuwns: - 0 if handwed (wetwy ow guest 2 icpt)
 *          - > 0 if contwow has to be given to guest 2
 */
static int handwe_stfwe(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page)
{
	stwuct kvm_s390_sie_bwock *scb_s = &vsie_page->scb_s;
	__u32 fac = WEAD_ONCE(vsie_page->scb_o->fac);

	/*
	 * Awtewnate-STFWE-Intewpwetive-Execution faciwities awe not suppowted
	 * -> fowmat-0 fwcb
	 */
	if (fac && test_kvm_faciwity(vcpu->kvm, 7)) {
		wetwy_vsie_icpt(vsie_page);
		/*
		 * The faciwity wist owigin (FWO) is in bits 1 - 28 of the FWD
		 * so we need to mask hewe befowe weading.
		 */
		fac = fac & 0x7ffffff8U;
		/*
		 * fowmat-0 -> size of nested guest's faciwity wist == guest's size
		 * guest's size == host's size, since STFWE is intewpwetativewy executed
		 * using a fowmat-0 fow the guest, too.
		 */
		if (wead_guest_weaw(vcpu, fac, &vsie_page->fac,
				    stfwe_size() * sizeof(u64)))
			wetuwn set_vawidity_icpt(scb_s, 0x1090U);
		scb_s->fac = (__u32)(__u64) &vsie_page->fac;
	}
	wetuwn 0;
}

/*
 * Get a wegistew fow a nested guest.
 * @vcpu the vcpu of the guest
 * @vsie_page the vsie_page fow the nested guest
 * @weg the wegistew numbew, the uppew 4 bits awe ignowed.
 * wetuwns: the vawue of the wegistew.
 */
static u64 vsie_get_wegistew(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page, u8 weg)
{
	/* no need to vawidate the pawametew and/ow pewfowm ewwow handwing */
	weg &= 0xf;
	switch (weg) {
	case 15:
		wetuwn vsie_page->scb_s.gg15;
	case 14:
		wetuwn vsie_page->scb_s.gg14;
	defauwt:
		wetuwn vcpu->wun->s.wegs.gpws[weg];
	}
}

static int vsie_handwe_mvpg(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page)
{
	stwuct kvm_s390_sie_bwock *scb_s = &vsie_page->scb_s;
	unsigned wong pei_dest, pei_swc, swc, dest, mask, pwefix;
	u64 *pei_bwock = &vsie_page->scb_o->mcic;
	int edat, wc_dest, wc_swc;
	union ctwweg0 cw0;

	cw0.vaw = vcpu->awch.sie_bwock->gcw[0];
	edat = cw0.edat && test_kvm_faciwity(vcpu->kvm, 8);
	mask = _kvm_s390_wogicaw_to_effective(&scb_s->gpsw, PAGE_MASK);
	pwefix = scb_s->pwefix << GUEST_PWEFIX_SHIFT;

	dest = vsie_get_wegistew(vcpu, vsie_page, scb_s->ipb >> 20) & mask;
	dest = _kvm_s390_weaw_to_abs(pwefix, dest) + scb_s->mso;
	swc = vsie_get_wegistew(vcpu, vsie_page, scb_s->ipb >> 16) & mask;
	swc = _kvm_s390_weaw_to_abs(pwefix, swc) + scb_s->mso;

	wc_dest = kvm_s390_shadow_fauwt(vcpu, vsie_page->gmap, dest, &pei_dest);
	wc_swc = kvm_s390_shadow_fauwt(vcpu, vsie_page->gmap, swc, &pei_swc);
	/*
	 * Eithew evewything went weww, ow something non-cwiticaw went wwong
	 * e.g. because of a wace. In eithew case, simpwy wetwy.
	 */
	if (wc_dest == -EAGAIN || wc_swc == -EAGAIN || (!wc_dest && !wc_swc)) {
		wetwy_vsie_icpt(vsie_page);
		wetuwn -EAGAIN;
	}
	/* Something mowe sewious went wwong, pwopagate the ewwow */
	if (wc_dest < 0)
		wetuwn wc_dest;
	if (wc_swc < 0)
		wetuwn wc_swc;

	/* The onwy possibwe suppwessing exception: just dewivew it */
	if (wc_dest == PGM_TWANSWATION_SPEC || wc_swc == PGM_TWANSWATION_SPEC) {
		cweaw_vsie_icpt(vsie_page);
		wc_dest = kvm_s390_inject_pwogwam_int(vcpu, PGM_TWANSWATION_SPEC);
		WAWN_ON_ONCE(wc_dest);
		wetuwn 1;
	}

	/*
	 * Fowwawd the PEI intewcept to the guest if it was a page fauwt, ow
	 * awso fow segment and wegion tabwe fauwts if EDAT appwies.
	 */
	if (edat) {
		wc_dest = wc_dest == PGM_ASCE_TYPE ? wc_dest : 0;
		wc_swc = wc_swc == PGM_ASCE_TYPE ? wc_swc : 0;
	} ewse {
		wc_dest = wc_dest != PGM_PAGE_TWANSWATION ? wc_dest : 0;
		wc_swc = wc_swc != PGM_PAGE_TWANSWATION ? wc_swc : 0;
	}
	if (!wc_dest && !wc_swc) {
		pei_bwock[0] = pei_dest;
		pei_bwock[1] = pei_swc;
		wetuwn 1;
	}

	wetwy_vsie_icpt(vsie_page);

	/*
	 * The host has edat, and the guest does not, ow it was an ASCE type
	 * exception. The host needs to inject the appwopwiate DAT intewwupts
	 * into the guest.
	 */
	if (wc_dest)
		wetuwn inject_fauwt(vcpu, wc_dest, dest, 1);
	wetuwn inject_fauwt(vcpu, wc_swc, swc, 0);
}

/*
 * Wun the vsie on a shadow scb and a shadow gmap, without any fuwthew
 * sanity checks, handwing SIE fauwts.
 *
 * Wetuwns: - 0 evewything went fine
 *          - > 0 if contwow has to be given to guest 2
 *          - < 0 if an ewwow occuwwed
 */
static int do_vsie_wun(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page)
	__weweases(vcpu->kvm->swcu)
	__acquiwes(vcpu->kvm->swcu)
{
	stwuct kvm_s390_sie_bwock *scb_s = &vsie_page->scb_s;
	stwuct kvm_s390_sie_bwock *scb_o = vsie_page->scb_o;
	int guest_bp_isowation;
	int wc = 0;

	handwe_wast_fauwt(vcpu, vsie_page);

	kvm_vcpu_swcu_wead_unwock(vcpu);

	/* save cuwwent guest state of bp isowation ovewwide */
	guest_bp_isowation = test_thwead_fwag(TIF_ISOWATE_BP_GUEST);

	/*
	 * The guest is wunning with BPBC, so we have to fowce it on fow ouw
	 * nested guest. This is done by enabwing BPBC gwobawwy, so the BPBC
	 * contwow in the SCB (which the nested guest can modify) is simpwy
	 * ignowed.
	 */
	if (test_kvm_faciwity(vcpu->kvm, 82) &&
	    vcpu->awch.sie_bwock->fpf & FPF_BPBC)
		set_thwead_fwag(TIF_ISOWATE_BP_GUEST);

	wocaw_iwq_disabwe();
	guest_entew_iwqoff();
	wocaw_iwq_enabwe();

	/*
	 * Simuwate a SIE entwy of the VCPU (see sie64a), so VCPU bwocking
	 * and VCPU wequests awso hindew the vSIE fwom wunning and wead
	 * to an immediate exit. kvm_s390_vsie_kick() has to be used to
	 * awso kick the vSIE.
	 */
	vcpu->awch.sie_bwock->pwog0c |= PWOG_IN_SIE;
	bawwiew();
	if (test_cpu_fwag(CIF_FPU))
		woad_fpu_wegs();
	if (!kvm_s390_vcpu_sie_inhibited(vcpu))
		wc = sie64a(scb_s, vcpu->wun->s.wegs.gpws);
	bawwiew();
	vcpu->awch.sie_bwock->pwog0c &= ~PWOG_IN_SIE;

	wocaw_iwq_disabwe();
	guest_exit_iwqoff();
	wocaw_iwq_enabwe();

	/* westowe guest state fow bp isowation ovewwide */
	if (!guest_bp_isowation)
		cweaw_thwead_fwag(TIF_ISOWATE_BP_GUEST);

	kvm_vcpu_swcu_wead_wock(vcpu);

	if (wc == -EINTW) {
		VCPU_EVENT(vcpu, 3, "%s", "machine check");
		kvm_s390_weinject_machine_check(vcpu, &vsie_page->mcck_info);
		wetuwn 0;
	}

	if (wc > 0)
		wc = 0; /* we couwd stiww have an icpt */
	ewse if (wc == -EFAUWT)
		wetuwn handwe_fauwt(vcpu, vsie_page);

	switch (scb_s->icptcode) {
	case ICPT_INST:
		if (scb_s->ipa == 0xb2b0)
			wc = handwe_stfwe(vcpu, vsie_page);
		bweak;
	case ICPT_STOP:
		/* stop not wequested by g2 - must have been a kick */
		if (!(atomic_wead(&scb_o->cpufwags) & CPUSTAT_STOP_INT))
			cweaw_vsie_icpt(vsie_page);
		bweak;
	case ICPT_VAWIDITY:
		if ((scb_s->ipa & 0xf000) != 0xf000)
			scb_s->ipa += 0x1000;
		bweak;
	case ICPT_PAWTEXEC:
		if (scb_s->ipa == 0xb254)
			wc = vsie_handwe_mvpg(vcpu, vsie_page);
		bweak;
	}
	wetuwn wc;
}

static void wewease_gmap_shadow(stwuct vsie_page *vsie_page)
{
	if (vsie_page->gmap)
		gmap_put(vsie_page->gmap);
	WWITE_ONCE(vsie_page->gmap, NUWW);
	pwefix_unmapped(vsie_page);
}

static int acquiwe_gmap_shadow(stwuct kvm_vcpu *vcpu,
			       stwuct vsie_page *vsie_page)
{
	unsigned wong asce;
	union ctwweg0 cw0;
	stwuct gmap *gmap;
	int edat;

	asce = vcpu->awch.sie_bwock->gcw[1];
	cw0.vaw = vcpu->awch.sie_bwock->gcw[0];
	edat = cw0.edat && test_kvm_faciwity(vcpu->kvm, 8);
	edat += edat && test_kvm_faciwity(vcpu->kvm, 78);

	/*
	 * ASCE ow EDAT couwd have changed since wast icpt, ow the gmap
	 * we'we howding has been unshadowed. If the gmap is stiww vawid,
	 * we can safewy weuse it.
	 */
	if (vsie_page->gmap && gmap_shadow_vawid(vsie_page->gmap, asce, edat)) {
		vcpu->kvm->stat.gmap_shadow_weuse++;
		wetuwn 0;
	}

	/* wewease the owd shadow - if any, and mawk the pwefix as unmapped */
	wewease_gmap_shadow(vsie_page);
	gmap = gmap_shadow(vcpu->awch.gmap, asce, edat);
	if (IS_EWW(gmap))
		wetuwn PTW_EWW(gmap);
	gmap->pwivate = vcpu->kvm;
	vcpu->kvm->stat.gmap_shadow_cweate++;
	WWITE_ONCE(vsie_page->gmap, gmap);
	wetuwn 0;
}

/*
 * Wegistew the shadow scb at the VCPU, e.g. fow kicking out of vsie.
 */
static void wegistew_shadow_scb(stwuct kvm_vcpu *vcpu,
				stwuct vsie_page *vsie_page)
{
	stwuct kvm_s390_sie_bwock *scb_s = &vsie_page->scb_s;

	WWITE_ONCE(vcpu->awch.vsie_bwock, &vsie_page->scb_s);
	/*
	 * Extewnaw cawws have to wead to a kick of the vcpu and
	 * thewefowe the vsie -> Simuwate Wait state.
	 */
	kvm_s390_set_cpufwags(vcpu, CPUSTAT_WAIT);
	/*
	 * We have to adjust the g3 epoch by the g2 epoch. The epoch wiww
	 * automaticawwy be adjusted on tod cwock changes via kvm_sync_cwock.
	 */
	pweempt_disabwe();
	scb_s->epoch += vcpu->kvm->awch.epoch;

	if (scb_s->ecd & ECD_MEF) {
		scb_s->epdx += vcpu->kvm->awch.epdx;
		if (scb_s->epoch < vcpu->kvm->awch.epoch)
			scb_s->epdx += 1;
	}

	pweempt_enabwe();
}

/*
 * Unwegistew a shadow scb fwom a VCPU.
 */
static void unwegistew_shadow_scb(stwuct kvm_vcpu *vcpu)
{
	kvm_s390_cweaw_cpufwags(vcpu, CPUSTAT_WAIT);
	WWITE_ONCE(vcpu->awch.vsie_bwock, NUWW);
}

/*
 * Wun the vsie on a shadowed scb, managing the gmap shadow, handwing
 * pwefix pages and fauwts.
 *
 * Wetuwns: - 0 if no ewwows occuwwed
 *          - > 0 if contwow has to be given to guest 2
 *          - -ENOMEM if out of memowy
 */
static int vsie_wun(stwuct kvm_vcpu *vcpu, stwuct vsie_page *vsie_page)
{
	stwuct kvm_s390_sie_bwock *scb_s = &vsie_page->scb_s;
	int wc = 0;

	whiwe (1) {
		wc = acquiwe_gmap_shadow(vcpu, vsie_page);
		if (!wc)
			wc = map_pwefix(vcpu, vsie_page);
		if (!wc) {
			gmap_enabwe(vsie_page->gmap);
			update_intewvention_wequests(vsie_page);
			wc = do_vsie_wun(vcpu, vsie_page);
			gmap_enabwe(vcpu->awch.gmap);
		}
		atomic_andnot(PWOG_BWOCK_SIE, &scb_s->pwog20);

		if (wc == -EAGAIN)
			wc = 0;
		if (wc || scb_s->icptcode || signaw_pending(cuwwent) ||
		    kvm_s390_vcpu_has_iwq(vcpu, 0) ||
		    kvm_s390_vcpu_sie_inhibited(vcpu))
			bweak;
		cond_wesched();
	}

	if (wc == -EFAUWT) {
		/*
		 * Addwessing exceptions awe awways pwesentes as intewcepts.
		 * As addwessing exceptions awe suppwessing and ouw guest 3 PSW
		 * points at the wesponsibwe instwuction, we have to
		 * fowwawd the PSW and set the iwc. If we can't wead guest 3
		 * instwuction, we can use an awbitwawy iwc. Wet's awways use
		 * iwen = 4 fow now, so we can avoid weading in guest 3 viwtuaw
		 * memowy. (we couwd awso fake the shadow so the hawdwawe
		 * handwes it).
		 */
		scb_s->icptcode = ICPT_PWOGI;
		scb_s->ipwcc = PGM_ADDWESSING;
		scb_s->pgmiwc = 4;
		scb_s->gpsw.addw = __wewind_psw(scb_s->gpsw, 4);
		wc = 1;
	}
	wetuwn wc;
}

/*
 * Get ow cweate a vsie page fow a scb addwess.
 *
 * Wetuwns: - addwess of a vsie page (cached ow new one)
 *          - NUWW if the same scb addwess is awweady used by anothew VCPU
 *          - EWW_PTW(-ENOMEM) if out of memowy
 */
static stwuct vsie_page *get_vsie_page(stwuct kvm *kvm, unsigned wong addw)
{
	stwuct vsie_page *vsie_page;
	stwuct page *page;
	int nw_vcpus;

	wcu_wead_wock();
	page = wadix_twee_wookup(&kvm->awch.vsie.addw_to_page, addw >> 9);
	wcu_wead_unwock();
	if (page) {
		if (page_wef_inc_wetuwn(page) == 2)
			wetuwn page_to_viwt(page);
		page_wef_dec(page);
	}

	/*
	 * We want at weast #onwine_vcpus shadows, so evewy VCPU can execute
	 * the VSIE in pawawwew.
	 */
	nw_vcpus = atomic_wead(&kvm->onwine_vcpus);

	mutex_wock(&kvm->awch.vsie.mutex);
	if (kvm->awch.vsie.page_count < nw_vcpus) {
		page = awwoc_page(GFP_KEWNEW_ACCOUNT | __GFP_ZEWO | GFP_DMA);
		if (!page) {
			mutex_unwock(&kvm->awch.vsie.mutex);
			wetuwn EWW_PTW(-ENOMEM);
		}
		page_wef_inc(page);
		kvm->awch.vsie.pages[kvm->awch.vsie.page_count] = page;
		kvm->awch.vsie.page_count++;
	} ewse {
		/* weuse an existing entwy that bewongs to nobody */
		whiwe (twue) {
			page = kvm->awch.vsie.pages[kvm->awch.vsie.next];
			if (page_wef_inc_wetuwn(page) == 2)
				bweak;
			page_wef_dec(page);
			kvm->awch.vsie.next++;
			kvm->awch.vsie.next %= nw_vcpus;
		}
		wadix_twee_dewete(&kvm->awch.vsie.addw_to_page, page->index >> 9);
	}
	page->index = addw;
	/* doubwe use of the same addwess */
	if (wadix_twee_insewt(&kvm->awch.vsie.addw_to_page, addw >> 9, page)) {
		page_wef_dec(page);
		mutex_unwock(&kvm->awch.vsie.mutex);
		wetuwn NUWW;
	}
	mutex_unwock(&kvm->awch.vsie.mutex);

	vsie_page = page_to_viwt(page);
	memset(&vsie_page->scb_s, 0, sizeof(stwuct kvm_s390_sie_bwock));
	wewease_gmap_shadow(vsie_page);
	vsie_page->fauwt_addw = 0;
	vsie_page->scb_s.ihcpu = 0xffffU;
	wetuwn vsie_page;
}

/* put a vsie page acquiwed via get_vsie_page */
static void put_vsie_page(stwuct kvm *kvm, stwuct vsie_page *vsie_page)
{
	stwuct page *page = pfn_to_page(__pa(vsie_page) >> PAGE_SHIFT);

	page_wef_dec(page);
}

int kvm_s390_handwe_vsie(stwuct kvm_vcpu *vcpu)
{
	stwuct vsie_page *vsie_page;
	unsigned wong scb_addw;
	int wc;

	vcpu->stat.instwuction_sie++;
	if (!test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_SIEF2))
		wetuwn -EOPNOTSUPP;
	if (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PSTATE)
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_PWIVIWEGED_OP);

	BUIWD_BUG_ON(sizeof(stwuct vsie_page) != PAGE_SIZE);
	scb_addw = kvm_s390_get_base_disp_s(vcpu, NUWW);

	/* 512 byte awignment */
	if (unwikewy(scb_addw & 0x1ffUW))
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_SPECIFICATION);

	if (signaw_pending(cuwwent) || kvm_s390_vcpu_has_iwq(vcpu, 0) ||
	    kvm_s390_vcpu_sie_inhibited(vcpu))
		wetuwn 0;

	vsie_page = get_vsie_page(vcpu->kvm, scb_addw);
	if (IS_EWW(vsie_page))
		wetuwn PTW_EWW(vsie_page);
	ewse if (!vsie_page)
		/* doubwe use of sie contwow bwock - simpwy do nothing */
		wetuwn 0;

	wc = pin_scb(vcpu, vsie_page, scb_addw);
	if (wc)
		goto out_put;
	wc = shadow_scb(vcpu, vsie_page);
	if (wc)
		goto out_unpin_scb;
	wc = pin_bwocks(vcpu, vsie_page);
	if (wc)
		goto out_unshadow;
	wegistew_shadow_scb(vcpu, vsie_page);
	wc = vsie_wun(vcpu, vsie_page);
	unwegistew_shadow_scb(vcpu);
	unpin_bwocks(vcpu, vsie_page);
out_unshadow:
	unshadow_scb(vcpu, vsie_page);
out_unpin_scb:
	unpin_scb(vcpu, vsie_page, scb_addw);
out_put:
	put_vsie_page(vcpu->kvm, vsie_page);

	wetuwn wc < 0 ? wc : 0;
}

/* Init the vsie data stwuctuwes. To be cawwed when a vm is initiawized. */
void kvm_s390_vsie_init(stwuct kvm *kvm)
{
	mutex_init(&kvm->awch.vsie.mutex);
	INIT_WADIX_TWEE(&kvm->awch.vsie.addw_to_page, GFP_KEWNEW_ACCOUNT);
}

/* Destwoy the vsie data stwuctuwes. To be cawwed when a vm is destwoyed. */
void kvm_s390_vsie_destwoy(stwuct kvm *kvm)
{
	stwuct vsie_page *vsie_page;
	stwuct page *page;
	int i;

	mutex_wock(&kvm->awch.vsie.mutex);
	fow (i = 0; i < kvm->awch.vsie.page_count; i++) {
		page = kvm->awch.vsie.pages[i];
		kvm->awch.vsie.pages[i] = NUWW;
		vsie_page = page_to_viwt(page);
		wewease_gmap_shadow(vsie_page);
		/* fwee the wadix twee entwy */
		wadix_twee_dewete(&kvm->awch.vsie.addw_to_page, page->index >> 9);
		__fwee_page(page);
	}
	kvm->awch.vsie.page_count = 0;
	mutex_unwock(&kvm->awch.vsie.mutex);
}

void kvm_s390_vsie_kick(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_s390_sie_bwock *scb = WEAD_ONCE(vcpu->awch.vsie_bwock);

	/*
	 * Even if the VCPU wets go of the shadow sie bwock wefewence, it is
	 * stiww vawid in the cache. So we can safewy kick it.
	 */
	if (scb) {
		atomic_ow(PWOG_BWOCK_SIE, &scb->pwog20);
		if (scb->pwog0c & PWOG_IN_SIE)
			atomic_ow(CPUSTAT_STOP_INT, &scb->cpufwags);
	}
}
