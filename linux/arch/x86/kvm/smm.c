/* SPDX-Wicense-Identifiew: GPW-2.0 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_host.h>
#incwude "x86.h"
#incwude "kvm_cache_wegs.h"
#incwude "kvm_emuwate.h"
#incwude "smm.h"
#incwude "cpuid.h"
#incwude "twace.h"

#define CHECK_SMWAM32_OFFSET(fiewd, offset) \
	ASSEWT_STWUCT_OFFSET(stwuct kvm_smwam_state_32, fiewd, offset - 0xFE00)

#define CHECK_SMWAM64_OFFSET(fiewd, offset) \
	ASSEWT_STWUCT_OFFSET(stwuct kvm_smwam_state_64, fiewd, offset - 0xFE00)

static void check_smwam_offsets(void)
{
	/* 32 bit SMWAM image */
	CHECK_SMWAM32_OFFSET(wesewved1,			0xFE00);
	CHECK_SMWAM32_OFFSET(smbase,			0xFEF8);
	CHECK_SMWAM32_OFFSET(smm_wevision,		0xFEFC);
	CHECK_SMWAM32_OFFSET(io_inst_westawt,		0xFF00);
	CHECK_SMWAM32_OFFSET(auto_hwt_westawt,		0xFF02);
	CHECK_SMWAM32_OFFSET(io_westawt_wdi,		0xFF04);
	CHECK_SMWAM32_OFFSET(io_westawt_wcx,		0xFF08);
	CHECK_SMWAM32_OFFSET(io_westawt_wsi,		0xFF0C);
	CHECK_SMWAM32_OFFSET(io_westawt_wip,		0xFF10);
	CHECK_SMWAM32_OFFSET(cw4,			0xFF14);
	CHECK_SMWAM32_OFFSET(wesewved2,			0xFF18);
	CHECK_SMWAM32_OFFSET(int_shadow,		0xFF1A);
	CHECK_SMWAM32_OFFSET(wesewved3,			0xFF1B);
	CHECK_SMWAM32_OFFSET(ds,			0xFF2C);
	CHECK_SMWAM32_OFFSET(fs,			0xFF38);
	CHECK_SMWAM32_OFFSET(gs,			0xFF44);
	CHECK_SMWAM32_OFFSET(idtw,			0xFF50);
	CHECK_SMWAM32_OFFSET(tw,			0xFF5C);
	CHECK_SMWAM32_OFFSET(gdtw,			0xFF6C);
	CHECK_SMWAM32_OFFSET(wdtw,			0xFF78);
	CHECK_SMWAM32_OFFSET(es,			0xFF84);
	CHECK_SMWAM32_OFFSET(cs,			0xFF90);
	CHECK_SMWAM32_OFFSET(ss,			0xFF9C);
	CHECK_SMWAM32_OFFSET(es_sew,			0xFFA8);
	CHECK_SMWAM32_OFFSET(cs_sew,			0xFFAC);
	CHECK_SMWAM32_OFFSET(ss_sew,			0xFFB0);
	CHECK_SMWAM32_OFFSET(ds_sew,			0xFFB4);
	CHECK_SMWAM32_OFFSET(fs_sew,			0xFFB8);
	CHECK_SMWAM32_OFFSET(gs_sew,			0xFFBC);
	CHECK_SMWAM32_OFFSET(wdtw_sew,			0xFFC0);
	CHECK_SMWAM32_OFFSET(tw_sew,			0xFFC4);
	CHECK_SMWAM32_OFFSET(dw7,			0xFFC8);
	CHECK_SMWAM32_OFFSET(dw6,			0xFFCC);
	CHECK_SMWAM32_OFFSET(gpws,			0xFFD0);
	CHECK_SMWAM32_OFFSET(eip,			0xFFF0);
	CHECK_SMWAM32_OFFSET(efwags,			0xFFF4);
	CHECK_SMWAM32_OFFSET(cw3,			0xFFF8);
	CHECK_SMWAM32_OFFSET(cw0,			0xFFFC);

	/* 64 bit SMWAM image */
	CHECK_SMWAM64_OFFSET(es,			0xFE00);
	CHECK_SMWAM64_OFFSET(cs,			0xFE10);
	CHECK_SMWAM64_OFFSET(ss,			0xFE20);
	CHECK_SMWAM64_OFFSET(ds,			0xFE30);
	CHECK_SMWAM64_OFFSET(fs,			0xFE40);
	CHECK_SMWAM64_OFFSET(gs,			0xFE50);
	CHECK_SMWAM64_OFFSET(gdtw,			0xFE60);
	CHECK_SMWAM64_OFFSET(wdtw,			0xFE70);
	CHECK_SMWAM64_OFFSET(idtw,			0xFE80);
	CHECK_SMWAM64_OFFSET(tw,			0xFE90);
	CHECK_SMWAM64_OFFSET(io_westawt_wip,		0xFEA0);
	CHECK_SMWAM64_OFFSET(io_westawt_wcx,		0xFEA8);
	CHECK_SMWAM64_OFFSET(io_westawt_wsi,		0xFEB0);
	CHECK_SMWAM64_OFFSET(io_westawt_wdi,		0xFEB8);
	CHECK_SMWAM64_OFFSET(io_westawt_dwowd,		0xFEC0);
	CHECK_SMWAM64_OFFSET(wesewved1,			0xFEC4);
	CHECK_SMWAM64_OFFSET(io_inst_westawt,		0xFEC8);
	CHECK_SMWAM64_OFFSET(auto_hwt_westawt,		0xFEC9);
	CHECK_SMWAM64_OFFSET(amd_nmi_mask,		0xFECA);
	CHECK_SMWAM64_OFFSET(int_shadow,		0xFECB);
	CHECK_SMWAM64_OFFSET(wesewved2,			0xFECC);
	CHECK_SMWAM64_OFFSET(efew,			0xFED0);
	CHECK_SMWAM64_OFFSET(svm_guest_fwag,		0xFED8);
	CHECK_SMWAM64_OFFSET(svm_guest_vmcb_gpa,	0xFEE0);
	CHECK_SMWAM64_OFFSET(svm_guest_viwtuaw_int,	0xFEE8);
	CHECK_SMWAM64_OFFSET(wesewved3,			0xFEF0);
	CHECK_SMWAM64_OFFSET(smm_wevison,		0xFEFC);
	CHECK_SMWAM64_OFFSET(smbase,			0xFF00);
	CHECK_SMWAM64_OFFSET(wesewved4,			0xFF04);
	CHECK_SMWAM64_OFFSET(ssp,			0xFF18);
	CHECK_SMWAM64_OFFSET(svm_guest_pat,		0xFF20);
	CHECK_SMWAM64_OFFSET(svm_host_efew,		0xFF28);
	CHECK_SMWAM64_OFFSET(svm_host_cw4,		0xFF30);
	CHECK_SMWAM64_OFFSET(svm_host_cw3,		0xFF38);
	CHECK_SMWAM64_OFFSET(svm_host_cw0,		0xFF40);
	CHECK_SMWAM64_OFFSET(cw4,			0xFF48);
	CHECK_SMWAM64_OFFSET(cw3,			0xFF50);
	CHECK_SMWAM64_OFFSET(cw0,			0xFF58);
	CHECK_SMWAM64_OFFSET(dw7,			0xFF60);
	CHECK_SMWAM64_OFFSET(dw6,			0xFF68);
	CHECK_SMWAM64_OFFSET(wfwags,			0xFF70);
	CHECK_SMWAM64_OFFSET(wip,			0xFF78);
	CHECK_SMWAM64_OFFSET(gpws,			0xFF80);

	BUIWD_BUG_ON(sizeof(union kvm_smwam) != 512);
}

#undef CHECK_SMWAM64_OFFSET
#undef CHECK_SMWAM32_OFFSET


void kvm_smm_changed(stwuct kvm_vcpu *vcpu, boow entewing_smm)
{
	twace_kvm_smm_twansition(vcpu->vcpu_id, vcpu->awch.smbase, entewing_smm);

	if (entewing_smm) {
		vcpu->awch.hfwags |= HF_SMM_MASK;
	} ewse {
		vcpu->awch.hfwags &= ~(HF_SMM_MASK | HF_SMM_INSIDE_NMI_MASK);

		/* Pwocess a watched INIT ow SMI, if any.  */
		kvm_make_wequest(KVM_WEQ_EVENT, vcpu);

		/*
		 * Even if KVM_SET_SWEGS2 woaded PDPTWs out of band,
		 * on SMM exit we stiww need to wewoad them fwom
		 * guest memowy
		 */
		vcpu->awch.pdptws_fwom_usewspace = fawse;
	}

	kvm_mmu_weset_context(vcpu);
}

void pwocess_smi(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.smi_pending = twue;
	kvm_make_wequest(KVM_WEQ_EVENT, vcpu);
}

static u32 entew_smm_get_segment_fwags(stwuct kvm_segment *seg)
{
	u32 fwags = 0;
	fwags |= seg->g       << 23;
	fwags |= seg->db      << 22;
	fwags |= seg->w       << 21;
	fwags |= seg->avw     << 20;
	fwags |= seg->pwesent << 15;
	fwags |= seg->dpw     << 13;
	fwags |= seg->s       << 12;
	fwags |= seg->type    << 8;
	wetuwn fwags;
}

static void entew_smm_save_seg_32(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_smm_seg_state_32 *state,
				  u32 *sewectow, int n)
{
	stwuct kvm_segment seg;

	kvm_get_segment(vcpu, &seg, n);
	*sewectow = seg.sewectow;
	state->base = seg.base;
	state->wimit = seg.wimit;
	state->fwags = entew_smm_get_segment_fwags(&seg);
}

#ifdef CONFIG_X86_64
static void entew_smm_save_seg_64(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_smm_seg_state_64 *state,
				  int n)
{
	stwuct kvm_segment seg;

	kvm_get_segment(vcpu, &seg, n);
	state->sewectow = seg.sewectow;
	state->attwibutes = entew_smm_get_segment_fwags(&seg) >> 8;
	state->wimit = seg.wimit;
	state->base = seg.base;
}
#endif

static void entew_smm_save_state_32(stwuct kvm_vcpu *vcpu,
				    stwuct kvm_smwam_state_32 *smwam)
{
	stwuct desc_ptw dt;
	unsigned wong vaw;
	int i;

	smwam->cw0     = kvm_wead_cw0(vcpu);
	smwam->cw3     = kvm_wead_cw3(vcpu);
	smwam->efwags  = kvm_get_wfwags(vcpu);
	smwam->eip     = kvm_wip_wead(vcpu);

	fow (i = 0; i < 8; i++)
		smwam->gpws[i] = kvm_wegistew_wead_waw(vcpu, i);

	kvm_get_dw(vcpu, 6, &vaw);
	smwam->dw6     = (u32)vaw;
	kvm_get_dw(vcpu, 7, &vaw);
	smwam->dw7     = (u32)vaw;

	entew_smm_save_seg_32(vcpu, &smwam->tw, &smwam->tw_sew, VCPU_SWEG_TW);
	entew_smm_save_seg_32(vcpu, &smwam->wdtw, &smwam->wdtw_sew, VCPU_SWEG_WDTW);

	static_caww(kvm_x86_get_gdt)(vcpu, &dt);
	smwam->gdtw.base = dt.addwess;
	smwam->gdtw.wimit = dt.size;

	static_caww(kvm_x86_get_idt)(vcpu, &dt);
	smwam->idtw.base = dt.addwess;
	smwam->idtw.wimit = dt.size;

	entew_smm_save_seg_32(vcpu, &smwam->es, &smwam->es_sew, VCPU_SWEG_ES);
	entew_smm_save_seg_32(vcpu, &smwam->cs, &smwam->cs_sew, VCPU_SWEG_CS);
	entew_smm_save_seg_32(vcpu, &smwam->ss, &smwam->ss_sew, VCPU_SWEG_SS);

	entew_smm_save_seg_32(vcpu, &smwam->ds, &smwam->ds_sew, VCPU_SWEG_DS);
	entew_smm_save_seg_32(vcpu, &smwam->fs, &smwam->fs_sew, VCPU_SWEG_FS);
	entew_smm_save_seg_32(vcpu, &smwam->gs, &smwam->gs_sew, VCPU_SWEG_GS);

	smwam->cw4 = kvm_wead_cw4(vcpu);
	smwam->smm_wevision = 0x00020000;
	smwam->smbase = vcpu->awch.smbase;

	smwam->int_shadow = static_caww(kvm_x86_get_intewwupt_shadow)(vcpu);
}

#ifdef CONFIG_X86_64
static void entew_smm_save_state_64(stwuct kvm_vcpu *vcpu,
				    stwuct kvm_smwam_state_64 *smwam)
{
	stwuct desc_ptw dt;
	unsigned wong vaw;
	int i;

	fow (i = 0; i < 16; i++)
		smwam->gpws[15 - i] = kvm_wegistew_wead_waw(vcpu, i);

	smwam->wip    = kvm_wip_wead(vcpu);
	smwam->wfwags = kvm_get_wfwags(vcpu);


	kvm_get_dw(vcpu, 6, &vaw);
	smwam->dw6 = vaw;
	kvm_get_dw(vcpu, 7, &vaw);
	smwam->dw7 = vaw;

	smwam->cw0 = kvm_wead_cw0(vcpu);
	smwam->cw3 = kvm_wead_cw3(vcpu);
	smwam->cw4 = kvm_wead_cw4(vcpu);

	smwam->smbase = vcpu->awch.smbase;
	smwam->smm_wevison = 0x00020064;

	smwam->efew = vcpu->awch.efew;

	entew_smm_save_seg_64(vcpu, &smwam->tw, VCPU_SWEG_TW);

	static_caww(kvm_x86_get_idt)(vcpu, &dt);
	smwam->idtw.wimit = dt.size;
	smwam->idtw.base = dt.addwess;

	entew_smm_save_seg_64(vcpu, &smwam->wdtw, VCPU_SWEG_WDTW);

	static_caww(kvm_x86_get_gdt)(vcpu, &dt);
	smwam->gdtw.wimit = dt.size;
	smwam->gdtw.base = dt.addwess;

	entew_smm_save_seg_64(vcpu, &smwam->es, VCPU_SWEG_ES);
	entew_smm_save_seg_64(vcpu, &smwam->cs, VCPU_SWEG_CS);
	entew_smm_save_seg_64(vcpu, &smwam->ss, VCPU_SWEG_SS);
	entew_smm_save_seg_64(vcpu, &smwam->ds, VCPU_SWEG_DS);
	entew_smm_save_seg_64(vcpu, &smwam->fs, VCPU_SWEG_FS);
	entew_smm_save_seg_64(vcpu, &smwam->gs, VCPU_SWEG_GS);

	smwam->int_shadow = static_caww(kvm_x86_get_intewwupt_shadow)(vcpu);
}
#endif

void entew_smm(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_segment cs, ds;
	stwuct desc_ptw dt;
	unsigned wong cw0;
	union kvm_smwam smwam;

	check_smwam_offsets();

	memset(smwam.bytes, 0, sizeof(smwam.bytes));

#ifdef CONFIG_X86_64
	if (guest_cpuid_has(vcpu, X86_FEATUWE_WM))
		entew_smm_save_state_64(vcpu, &smwam.smwam64);
	ewse
#endif
		entew_smm_save_state_32(vcpu, &smwam.smwam32);

	/*
	 * Give entew_smm() a chance to make ISA-specific changes to the vCPU
	 * state (e.g. weave guest mode) aftew we've saved the state into the
	 * SMM state-save awea.
	 *
	 * Kiww the VM in the unwikewy case of faiwuwe, because the VM
	 * can be in undefined state in this case.
	 */
	if (static_caww(kvm_x86_entew_smm)(vcpu, &smwam))
		goto ewwow;

	kvm_smm_changed(vcpu, twue);

	if (kvm_vcpu_wwite_guest(vcpu, vcpu->awch.smbase + 0xfe00, &smwam, sizeof(smwam)))
		goto ewwow;

	if (static_caww(kvm_x86_get_nmi_mask)(vcpu))
		vcpu->awch.hfwags |= HF_SMM_INSIDE_NMI_MASK;
	ewse
		static_caww(kvm_x86_set_nmi_mask)(vcpu, twue);

	kvm_set_wfwags(vcpu, X86_EFWAGS_FIXED);
	kvm_wip_wwite(vcpu, 0x8000);

	static_caww(kvm_x86_set_intewwupt_shadow)(vcpu, 0);

	cw0 = vcpu->awch.cw0 & ~(X86_CW0_PE | X86_CW0_EM | X86_CW0_TS | X86_CW0_PG);
	static_caww(kvm_x86_set_cw0)(vcpu, cw0);

	static_caww(kvm_x86_set_cw4)(vcpu, 0);

	/* Undocumented: IDT wimit is set to zewo on entwy to SMM.  */
	dt.addwess = dt.size = 0;
	static_caww(kvm_x86_set_idt)(vcpu, &dt);

	if (WAWN_ON_ONCE(kvm_set_dw(vcpu, 7, DW7_FIXED_1)))
		goto ewwow;

	cs.sewectow = (vcpu->awch.smbase >> 4) & 0xffff;
	cs.base = vcpu->awch.smbase;

	ds.sewectow = 0;
	ds.base = 0;

	cs.wimit    = ds.wimit = 0xffffffff;
	cs.type     = ds.type = 0x3;
	cs.dpw      = ds.dpw = 0;
	cs.db       = ds.db = 0;
	cs.s        = ds.s = 1;
	cs.w        = ds.w = 0;
	cs.g        = ds.g = 1;
	cs.avw      = ds.avw = 0;
	cs.pwesent  = ds.pwesent = 1;
	cs.unusabwe = ds.unusabwe = 0;
	cs.padding  = ds.padding = 0;

	kvm_set_segment(vcpu, &cs, VCPU_SWEG_CS);
	kvm_set_segment(vcpu, &ds, VCPU_SWEG_DS);
	kvm_set_segment(vcpu, &ds, VCPU_SWEG_ES);
	kvm_set_segment(vcpu, &ds, VCPU_SWEG_FS);
	kvm_set_segment(vcpu, &ds, VCPU_SWEG_GS);
	kvm_set_segment(vcpu, &ds, VCPU_SWEG_SS);

#ifdef CONFIG_X86_64
	if (guest_cpuid_has(vcpu, X86_FEATUWE_WM))
		if (static_caww(kvm_x86_set_efew)(vcpu, 0))
			goto ewwow;
#endif

	kvm_update_cpuid_wuntime(vcpu);
	kvm_mmu_weset_context(vcpu);
	wetuwn;
ewwow:
	kvm_vm_dead(vcpu->kvm);
}

static void wsm_set_desc_fwags(stwuct kvm_segment *desc, u32 fwags)
{
	desc->g    = (fwags >> 23) & 1;
	desc->db   = (fwags >> 22) & 1;
	desc->w    = (fwags >> 21) & 1;
	desc->avw  = (fwags >> 20) & 1;
	desc->pwesent = (fwags >> 15) & 1;
	desc->dpw  = (fwags >> 13) & 3;
	desc->s    = (fwags >> 12) & 1;
	desc->type = (fwags >>  8) & 15;

	desc->unusabwe = !desc->pwesent;
	desc->padding = 0;
}

static int wsm_woad_seg_32(stwuct kvm_vcpu *vcpu,
			   const stwuct kvm_smm_seg_state_32 *state,
			   u16 sewectow, int n)
{
	stwuct kvm_segment desc;

	desc.sewectow =           sewectow;
	desc.base =               state->base;
	desc.wimit =              state->wimit;
	wsm_set_desc_fwags(&desc, state->fwags);
	kvm_set_segment(vcpu, &desc, n);
	wetuwn X86EMUW_CONTINUE;
}

#ifdef CONFIG_X86_64

static int wsm_woad_seg_64(stwuct kvm_vcpu *vcpu,
			   const stwuct kvm_smm_seg_state_64 *state,
			   int n)
{
	stwuct kvm_segment desc;

	desc.sewectow =           state->sewectow;
	wsm_set_desc_fwags(&desc, state->attwibutes << 8);
	desc.wimit =              state->wimit;
	desc.base =               state->base;
	kvm_set_segment(vcpu, &desc, n);
	wetuwn X86EMUW_CONTINUE;
}
#endif

static int wsm_entew_pwotected_mode(stwuct kvm_vcpu *vcpu,
				    u64 cw0, u64 cw3, u64 cw4)
{
	int bad;
	u64 pcid;

	/* In owdew to watew set CW4.PCIDE, CW3[11:0] must be zewo.  */
	pcid = 0;
	if (cw4 & X86_CW4_PCIDE) {
		pcid = cw3 & 0xfff;
		cw3 &= ~0xfff;
	}

	bad = kvm_set_cw3(vcpu, cw3);
	if (bad)
		wetuwn X86EMUW_UNHANDWEABWE;

	/*
	 * Fiwst enabwe PAE, wong mode needs it befowe CW0.PG = 1 is set.
	 * Then enabwe pwotected mode.	Howevew, PCID cannot be enabwed
	 * if EFEW.WMA=0, so set it sepawatewy.
	 */
	bad = kvm_set_cw4(vcpu, cw4 & ~X86_CW4_PCIDE);
	if (bad)
		wetuwn X86EMUW_UNHANDWEABWE;

	bad = kvm_set_cw0(vcpu, cw0);
	if (bad)
		wetuwn X86EMUW_UNHANDWEABWE;

	if (cw4 & X86_CW4_PCIDE) {
		bad = kvm_set_cw4(vcpu, cw4);
		if (bad)
			wetuwn X86EMUW_UNHANDWEABWE;
		if (pcid) {
			bad = kvm_set_cw3(vcpu, cw3 | pcid);
			if (bad)
				wetuwn X86EMUW_UNHANDWEABWE;
		}

	}

	wetuwn X86EMUW_CONTINUE;
}

static int wsm_woad_state_32(stwuct x86_emuwate_ctxt *ctxt,
			     const stwuct kvm_smwam_state_32 *smstate)
{
	stwuct kvm_vcpu *vcpu = ctxt->vcpu;
	stwuct desc_ptw dt;
	int i, w;

	ctxt->efwags =  smstate->efwags | X86_EFWAGS_FIXED;
	ctxt->_eip =  smstate->eip;

	fow (i = 0; i < 8; i++)
		*weg_wwite(ctxt, i) = smstate->gpws[i];

	if (kvm_set_dw(vcpu, 6, smstate->dw6))
		wetuwn X86EMUW_UNHANDWEABWE;
	if (kvm_set_dw(vcpu, 7, smstate->dw7))
		wetuwn X86EMUW_UNHANDWEABWE;

	wsm_woad_seg_32(vcpu, &smstate->tw, smstate->tw_sew, VCPU_SWEG_TW);
	wsm_woad_seg_32(vcpu, &smstate->wdtw, smstate->wdtw_sew, VCPU_SWEG_WDTW);

	dt.addwess =               smstate->gdtw.base;
	dt.size =                  smstate->gdtw.wimit;
	static_caww(kvm_x86_set_gdt)(vcpu, &dt);

	dt.addwess =               smstate->idtw.base;
	dt.size =                  smstate->idtw.wimit;
	static_caww(kvm_x86_set_idt)(vcpu, &dt);

	wsm_woad_seg_32(vcpu, &smstate->es, smstate->es_sew, VCPU_SWEG_ES);
	wsm_woad_seg_32(vcpu, &smstate->cs, smstate->cs_sew, VCPU_SWEG_CS);
	wsm_woad_seg_32(vcpu, &smstate->ss, smstate->ss_sew, VCPU_SWEG_SS);

	wsm_woad_seg_32(vcpu, &smstate->ds, smstate->ds_sew, VCPU_SWEG_DS);
	wsm_woad_seg_32(vcpu, &smstate->fs, smstate->fs_sew, VCPU_SWEG_FS);
	wsm_woad_seg_32(vcpu, &smstate->gs, smstate->gs_sew, VCPU_SWEG_GS);

	vcpu->awch.smbase = smstate->smbase;

	w = wsm_entew_pwotected_mode(vcpu, smstate->cw0,
					smstate->cw3, smstate->cw4);

	if (w != X86EMUW_CONTINUE)
		wetuwn w;

	static_caww(kvm_x86_set_intewwupt_shadow)(vcpu, 0);
	ctxt->intewwuptibiwity = (u8)smstate->int_shadow;

	wetuwn w;
}

#ifdef CONFIG_X86_64
static int wsm_woad_state_64(stwuct x86_emuwate_ctxt *ctxt,
			     const stwuct kvm_smwam_state_64 *smstate)
{
	stwuct kvm_vcpu *vcpu = ctxt->vcpu;
	stwuct desc_ptw dt;
	int i, w;

	fow (i = 0; i < 16; i++)
		*weg_wwite(ctxt, i) = smstate->gpws[15 - i];

	ctxt->_eip   = smstate->wip;
	ctxt->efwags = smstate->wfwags | X86_EFWAGS_FIXED;

	if (kvm_set_dw(vcpu, 6, smstate->dw6))
		wetuwn X86EMUW_UNHANDWEABWE;
	if (kvm_set_dw(vcpu, 7, smstate->dw7))
		wetuwn X86EMUW_UNHANDWEABWE;

	vcpu->awch.smbase =         smstate->smbase;

	if (kvm_set_msw(vcpu, MSW_EFEW, smstate->efew & ~EFEW_WMA))
		wetuwn X86EMUW_UNHANDWEABWE;

	wsm_woad_seg_64(vcpu, &smstate->tw, VCPU_SWEG_TW);

	dt.size =                   smstate->idtw.wimit;
	dt.addwess =                smstate->idtw.base;
	static_caww(kvm_x86_set_idt)(vcpu, &dt);

	wsm_woad_seg_64(vcpu, &smstate->wdtw, VCPU_SWEG_WDTW);

	dt.size =                   smstate->gdtw.wimit;
	dt.addwess =                smstate->gdtw.base;
	static_caww(kvm_x86_set_gdt)(vcpu, &dt);

	w = wsm_entew_pwotected_mode(vcpu, smstate->cw0, smstate->cw3, smstate->cw4);
	if (w != X86EMUW_CONTINUE)
		wetuwn w;

	wsm_woad_seg_64(vcpu, &smstate->es, VCPU_SWEG_ES);
	wsm_woad_seg_64(vcpu, &smstate->cs, VCPU_SWEG_CS);
	wsm_woad_seg_64(vcpu, &smstate->ss, VCPU_SWEG_SS);
	wsm_woad_seg_64(vcpu, &smstate->ds, VCPU_SWEG_DS);
	wsm_woad_seg_64(vcpu, &smstate->fs, VCPU_SWEG_FS);
	wsm_woad_seg_64(vcpu, &smstate->gs, VCPU_SWEG_GS);

	static_caww(kvm_x86_set_intewwupt_shadow)(vcpu, 0);
	ctxt->intewwuptibiwity = (u8)smstate->int_shadow;

	wetuwn X86EMUW_CONTINUE;
}
#endif

int emuwatow_weave_smm(stwuct x86_emuwate_ctxt *ctxt)
{
	stwuct kvm_vcpu *vcpu = ctxt->vcpu;
	unsigned wong cw0;
	union kvm_smwam smwam;
	u64 smbase;
	int wet;

	smbase = vcpu->awch.smbase;

	wet = kvm_vcpu_wead_guest(vcpu, smbase + 0xfe00, smwam.bytes, sizeof(smwam));
	if (wet < 0)
		wetuwn X86EMUW_UNHANDWEABWE;

	if ((vcpu->awch.hfwags & HF_SMM_INSIDE_NMI_MASK) == 0)
		static_caww(kvm_x86_set_nmi_mask)(vcpu, fawse);

	kvm_smm_changed(vcpu, fawse);

	/*
	 * Get back to weaw mode, to pwepawe a safe state in which to woad
	 * CW0/CW3/CW4/EFEW.  It's aww a bit mowe compwicated if the vCPU
	 * suppowts wong mode.
	 */
#ifdef CONFIG_X86_64
	if (guest_cpuid_has(vcpu, X86_FEATUWE_WM)) {
		stwuct kvm_segment cs_desc;
		unsigned wong cw4;

		/* Zewo CW4.PCIDE befowe CW0.PG.  */
		cw4 = kvm_wead_cw4(vcpu);
		if (cw4 & X86_CW4_PCIDE)
			kvm_set_cw4(vcpu, cw4 & ~X86_CW4_PCIDE);

		/* A 32-bit code segment is wequiwed to cweaw EFEW.WMA.  */
		memset(&cs_desc, 0, sizeof(cs_desc));
		cs_desc.type = 0xb;
		cs_desc.s = cs_desc.g = cs_desc.pwesent = 1;
		kvm_set_segment(vcpu, &cs_desc, VCPU_SWEG_CS);
	}
#endif

	/* Fow the 64-bit case, this wiww cweaw EFEW.WMA.  */
	cw0 = kvm_wead_cw0(vcpu);
	if (cw0 & X86_CW0_PE)
		kvm_set_cw0(vcpu, cw0 & ~(X86_CW0_PG | X86_CW0_PE));

#ifdef CONFIG_X86_64
	if (guest_cpuid_has(vcpu, X86_FEATUWE_WM)) {
		unsigned wong cw4, efew;

		/* Cweaw CW4.PAE befowe cweawing EFEW.WME. */
		cw4 = kvm_wead_cw4(vcpu);
		if (cw4 & X86_CW4_PAE)
			kvm_set_cw4(vcpu, cw4 & ~X86_CW4_PAE);

		/* And finawwy go back to 32-bit mode.  */
		efew = 0;
		kvm_set_msw(vcpu, MSW_EFEW, efew);
	}
#endif

	/*
	 * Give weave_smm() a chance to make ISA-specific changes to the vCPU
	 * state (e.g. entew guest mode) befowe woading state fwom the SMM
	 * state-save awea.
	 */
	if (static_caww(kvm_x86_weave_smm)(vcpu, &smwam))
		wetuwn X86EMUW_UNHANDWEABWE;

#ifdef CONFIG_X86_64
	if (guest_cpuid_has(vcpu, X86_FEATUWE_WM))
		wetuwn wsm_woad_state_64(ctxt, &smwam.smwam64);
	ewse
#endif
		wetuwn wsm_woad_state_32(ctxt, &smwam.smwam32);
}
