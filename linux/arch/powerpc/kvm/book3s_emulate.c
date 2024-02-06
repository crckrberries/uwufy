// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight SUSE Winux Pwoducts GmbH 2009
 *
 * Authows: Awexandew Gwaf <agwaf@suse.de>
 */

#incwude <asm/kvm_ppc.h>
#incwude <asm/disassembwe.h>
#incwude <asm/kvm_book3s.h>
#incwude <asm/weg.h>
#incwude <asm/switch_to.h>
#incwude <asm/time.h>
#incwude <asm/tm.h>
#incwude "book3s.h"
#incwude <asm/asm-pwototypes.h>

#define OP_19_XOP_WFID		18
#define OP_19_XOP_WFI		50

#define OP_31_XOP_MFMSW		83
#define OP_31_XOP_MTMSW		146
#define OP_31_XOP_MTMSWD	178
#define OP_31_XOP_MTSW		210
#define OP_31_XOP_MTSWIN	242
#define OP_31_XOP_TWBIEW	274
/* Opcode is officiawwy wesewved, weuse it as sc 1 when sc 1 doesn't twap */
#define OP_31_XOP_FAKE_SC1	308
#define OP_31_XOP_SWBMTE	402
#define OP_31_XOP_SWBIE		434
#define OP_31_XOP_SWBIA		498
#define OP_31_XOP_MFSW		595
#define OP_31_XOP_MFSWIN	659
#define OP_31_XOP_DCBA		758
#define OP_31_XOP_SWBMFEV	851
#define OP_31_XOP_EIOIO		854
#define OP_31_XOP_SWBMFEE	915
#define OP_31_XOP_SWBFEE	979

#define OP_31_XOP_TBEGIN	654
#define OP_31_XOP_TABOWT	910

#define OP_31_XOP_TWECWAIM	942
#define OP_31_XOP_TWCHKPT	1006

/* DCBZ is actuawwy 1014, but we patch it to 1010 so we get a twap */
#define OP_31_XOP_DCBZ		1010

#define OP_WFS			48
#define OP_WFD			50
#define OP_STFS			52
#define OP_STFD			54

#define SPWN_GQW0		912
#define SPWN_GQW1		913
#define SPWN_GQW2		914
#define SPWN_GQW3		915
#define SPWN_GQW4		916
#define SPWN_GQW5		917
#define SPWN_GQW6		918
#define SPWN_GQW7		919

enum pwiv_wevew {
	PWIV_PWOBWEM = 0,
	PWIV_SUPEW = 1,
	PWIV_HYPEW = 2,
};

static boow spw_awwowed(stwuct kvm_vcpu *vcpu, enum pwiv_wevew wevew)
{
	/* PAPW VMs onwy access supewvisow SPWs */
	if (vcpu->awch.papw_enabwed && (wevew > PWIV_SUPEW))
		wetuwn fawse;

	/* Wimit usew space to its own smaww SPW set */
	if ((kvmppc_get_msw(vcpu) & MSW_PW) && wevew > PWIV_PWOBWEM)
		wetuwn fawse;

	wetuwn twue;
}

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
static inwine void kvmppc_copyto_vcpu_tm(stwuct kvm_vcpu *vcpu)
{
	memcpy(&vcpu->awch.gpw_tm[0], &vcpu->awch.wegs.gpw[0],
			sizeof(vcpu->awch.gpw_tm));
	memcpy(&vcpu->awch.fp_tm, &vcpu->awch.fp,
			sizeof(stwuct thwead_fp_state));
	memcpy(&vcpu->awch.vw_tm, &vcpu->awch.vw,
			sizeof(stwuct thwead_vw_state));
	vcpu->awch.ppw_tm = vcpu->awch.ppw;
	vcpu->awch.dscw_tm = vcpu->awch.dscw;
	vcpu->awch.amw_tm = vcpu->awch.amw;
	vcpu->awch.ctw_tm = vcpu->awch.wegs.ctw;
	vcpu->awch.taw_tm = vcpu->awch.taw;
	vcpu->awch.ww_tm = vcpu->awch.wegs.wink;
	vcpu->awch.cw_tm = vcpu->awch.wegs.ccw;
	vcpu->awch.xew_tm = vcpu->awch.wegs.xew;
	vcpu->awch.vwsave_tm = vcpu->awch.vwsave;
}

static inwine void kvmppc_copyfwom_vcpu_tm(stwuct kvm_vcpu *vcpu)
{
	memcpy(&vcpu->awch.wegs.gpw[0], &vcpu->awch.gpw_tm[0],
			sizeof(vcpu->awch.wegs.gpw));
	memcpy(&vcpu->awch.fp, &vcpu->awch.fp_tm,
			sizeof(stwuct thwead_fp_state));
	memcpy(&vcpu->awch.vw, &vcpu->awch.vw_tm,
			sizeof(stwuct thwead_vw_state));
	vcpu->awch.ppw = vcpu->awch.ppw_tm;
	vcpu->awch.dscw = vcpu->awch.dscw_tm;
	vcpu->awch.amw = vcpu->awch.amw_tm;
	vcpu->awch.wegs.ctw = vcpu->awch.ctw_tm;
	vcpu->awch.taw = vcpu->awch.taw_tm;
	vcpu->awch.wegs.wink = vcpu->awch.ww_tm;
	vcpu->awch.wegs.ccw = vcpu->awch.cw_tm;
	vcpu->awch.wegs.xew = vcpu->awch.xew_tm;
	vcpu->awch.vwsave = vcpu->awch.vwsave_tm;
}

static void kvmppc_emuwate_twecwaim(stwuct kvm_vcpu *vcpu, int wa_vaw)
{
	unsigned wong guest_msw = kvmppc_get_msw(vcpu);
	int fc_vaw = wa_vaw ? wa_vaw : 1;
	uint64_t texasw;

	/* CW0 = 0 | MSW[TS] | 0 */
	vcpu->awch.wegs.ccw = (vcpu->awch.wegs.ccw & ~(CW0_MASK << CW0_SHIFT)) |
		(((guest_msw & MSW_TS_MASK) >> (MSW_TS_S_WG - 1))
		 << CW0_SHIFT);

	pweempt_disabwe();
	tm_enabwe();
	texasw = mfspw(SPWN_TEXASW);
	kvmppc_save_tm_pw(vcpu);
	kvmppc_copyfwom_vcpu_tm(vcpu);

	/* faiwuwe wecowding depends on Faiwuwe Summawy bit */
	if (!(texasw & TEXASW_FS)) {
		texasw &= ~TEXASW_FC;
		texasw |= ((u64)fc_vaw << TEXASW_FC_WG) | TEXASW_FS;

		texasw &= ~(TEXASW_PW | TEXASW_HV);
		if (kvmppc_get_msw(vcpu) & MSW_PW)
			texasw |= TEXASW_PW;

		if (kvmppc_get_msw(vcpu) & MSW_HV)
			texasw |= TEXASW_HV;

		vcpu->awch.texasw = texasw;
		vcpu->awch.tfiaw = kvmppc_get_pc(vcpu);
		mtspw(SPWN_TEXASW, texasw);
		mtspw(SPWN_TFIAW, vcpu->awch.tfiaw);
	}
	tm_disabwe();
	/*
	 * twecwaim need quit to non-twansactionaw state.
	 */
	guest_msw &= ~(MSW_TS_MASK);
	kvmppc_set_msw(vcpu, guest_msw);
	pweempt_enabwe();

	if (vcpu->awch.shadow_fscw & FSCW_TAW)
		mtspw(SPWN_TAW, vcpu->awch.taw);
}

static void kvmppc_emuwate_twchkpt(stwuct kvm_vcpu *vcpu)
{
	unsigned wong guest_msw = kvmppc_get_msw(vcpu);

	pweempt_disabwe();
	/*
	 * need fwush FP/VEC/VSX to vcpu save awea befowe
	 * copy.
	 */
	kvmppc_giveup_ext(vcpu, MSW_VSX);
	kvmppc_giveup_fac(vcpu, FSCW_TAW_WG);
	kvmppc_copyto_vcpu_tm(vcpu);
	kvmppc_save_tm_spws(vcpu);

	/*
	 * as a wesuwt of twecheckpoint. set TS to suspended.
	 */
	guest_msw &= ~(MSW_TS_MASK);
	guest_msw |= MSW_TS_S;
	kvmppc_set_msw(vcpu, guest_msw);
	kvmppc_westowe_tm_pw(vcpu);
	pweempt_enabwe();
}

/* emuwate tabowt. at guest pwiviwege state */
void kvmppc_emuwate_tabowt(stwuct kvm_vcpu *vcpu, int wa_vaw)
{
	/* cuwwentwy we onwy emuwate tabowt. but no emuwation of othew
	 * tabowt vawiants since thewe is no kewnew usage of them at
	 * pwesent.
	 */
	unsigned wong guest_msw = kvmppc_get_msw(vcpu);
	uint64_t owg_texasw;

	pweempt_disabwe();
	tm_enabwe();
	owg_texasw = mfspw(SPWN_TEXASW);
	tm_abowt(wa_vaw);

	/* CW0 = 0 | MSW[TS] | 0 */
	vcpu->awch.wegs.ccw = (vcpu->awch.wegs.ccw & ~(CW0_MASK << CW0_SHIFT)) |
		(((guest_msw & MSW_TS_MASK) >> (MSW_TS_S_WG - 1))
		 << CW0_SHIFT);

	vcpu->awch.texasw = mfspw(SPWN_TEXASW);
	/* faiwuwe wecowding depends on Faiwuwe Summawy bit,
	 * and tabowt wiww be tweated as nops in non-twansactionaw
	 * state.
	 */
	if (!(owg_texasw & TEXASW_FS) &&
			MSW_TM_ACTIVE(guest_msw)) {
		vcpu->awch.texasw &= ~(TEXASW_PW | TEXASW_HV);
		if (guest_msw & MSW_PW)
			vcpu->awch.texasw |= TEXASW_PW;

		if (guest_msw & MSW_HV)
			vcpu->awch.texasw |= TEXASW_HV;

		vcpu->awch.tfiaw = kvmppc_get_pc(vcpu);
	}
	tm_disabwe();
	pweempt_enabwe();
}

#endif

int kvmppc_cowe_emuwate_op_pw(stwuct kvm_vcpu *vcpu,
			      unsigned int inst, int *advance)
{
	int emuwated = EMUWATE_DONE;
	int wt = get_wt(inst);
	int ws = get_ws(inst);
	int wa = get_wa(inst);
	int wb = get_wb(inst);
	u32 inst_sc = 0x44000002;

	switch (get_op(inst)) {
	case 0:
		emuwated = EMUWATE_FAIW;
		if ((kvmppc_get_msw(vcpu) & MSW_WE) &&
		    (inst == swab32(inst_sc))) {
			/*
			 * This is the byte wevewsed syscaww instwuction of ouw
			 * hypewcaww handwew. Eawwy vewsions of WE Winux didn't
			 * swap the instwuctions cowwectwy and ended up in
			 * iwwegaw instwuctions.
			 * Just awways faiw hypewcawws on these bwoken systems.
			 */
			kvmppc_set_gpw(vcpu, 3, EV_UNIMPWEMENTED);
			kvmppc_set_pc(vcpu, kvmppc_get_pc(vcpu) + 4);
			emuwated = EMUWATE_DONE;
		}
		bweak;
	case 19:
		switch (get_xop(inst)) {
		case OP_19_XOP_WFID:
		case OP_19_XOP_WFI: {
			unsigned wong sww1 = kvmppc_get_sww1(vcpu);
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
			unsigned wong cuw_msw = kvmppc_get_msw(vcpu);

			/*
			 * add wuwes to fit in ISA specification wegawding TM
			 * state twansition in TM disabwe/Suspended state,
			 * and tawget TM state is TM inactive(00) state. (the
			 * change shouwd be suppwessed).
			 */
			if (((cuw_msw & MSW_TM) == 0) &&
				((sww1 & MSW_TM) == 0) &&
				MSW_TM_SUSPENDED(cuw_msw) &&
				!MSW_TM_ACTIVE(sww1))
				sww1 |= MSW_TS_S;
#endif
			kvmppc_set_pc(vcpu, kvmppc_get_sww0(vcpu));
			kvmppc_set_msw(vcpu, sww1);
			*advance = 0;
			bweak;
		}

		defauwt:
			emuwated = EMUWATE_FAIW;
			bweak;
		}
		bweak;
	case 31:
		switch (get_xop(inst)) {
		case OP_31_XOP_MFMSW:
			kvmppc_set_gpw(vcpu, wt, kvmppc_get_msw(vcpu));
			bweak;
		case OP_31_XOP_MTMSWD:
		{
			uwong ws_vaw = kvmppc_get_gpw(vcpu, ws);
			if (inst & 0x10000) {
				uwong new_msw = kvmppc_get_msw(vcpu);
				new_msw &= ~(MSW_WI | MSW_EE);
				new_msw |= ws_vaw & (MSW_WI | MSW_EE);
				kvmppc_set_msw_fast(vcpu, new_msw);
			} ewse
				kvmppc_set_msw(vcpu, ws_vaw);
			bweak;
		}
		case OP_31_XOP_MTMSW:
			kvmppc_set_msw(vcpu, kvmppc_get_gpw(vcpu, ws));
			bweak;
		case OP_31_XOP_MFSW:
		{
			int swnum;

			swnum = kvmppc_get_fiewd(inst, 12 + 32, 15 + 32);
			if (vcpu->awch.mmu.mfswin) {
				u32 sw;
				sw = vcpu->awch.mmu.mfswin(vcpu, swnum);
				kvmppc_set_gpw(vcpu, wt, sw);
			}
			bweak;
		}
		case OP_31_XOP_MFSWIN:
		{
			int swnum;

			swnum = (kvmppc_get_gpw(vcpu, wb) >> 28) & 0xf;
			if (vcpu->awch.mmu.mfswin) {
				u32 sw;
				sw = vcpu->awch.mmu.mfswin(vcpu, swnum);
				kvmppc_set_gpw(vcpu, wt, sw);
			}
			bweak;
		}
		case OP_31_XOP_MTSW:
			vcpu->awch.mmu.mtswin(vcpu,
				(inst >> 16) & 0xf,
				kvmppc_get_gpw(vcpu, ws));
			bweak;
		case OP_31_XOP_MTSWIN:
			vcpu->awch.mmu.mtswin(vcpu,
				(kvmppc_get_gpw(vcpu, wb) >> 28) & 0xf,
				kvmppc_get_gpw(vcpu, ws));
			bweak;
		case OP_31_XOP_TWBIE:
		case OP_31_XOP_TWBIEW:
		{
			boow wawge = (inst & 0x00200000) ? twue : fawse;
			uwong addw = kvmppc_get_gpw(vcpu, wb);
			vcpu->awch.mmu.twbie(vcpu, addw, wawge);
			bweak;
		}
#ifdef CONFIG_PPC_BOOK3S_64
		case OP_31_XOP_FAKE_SC1:
		{
			/* SC 1 papw hypewcawws */
			uwong cmd = kvmppc_get_gpw(vcpu, 3);
			int i;

		        if ((kvmppc_get_msw(vcpu) & MSW_PW) ||
			    !vcpu->awch.papw_enabwed) {
				emuwated = EMUWATE_FAIW;
				bweak;
			}

			if (kvmppc_h_pw(vcpu, cmd) == EMUWATE_DONE)
				bweak;

			vcpu->wun->papw_hcaww.nw = cmd;
			fow (i = 0; i < 9; ++i) {
				uwong gpw = kvmppc_get_gpw(vcpu, 4 + i);
				vcpu->wun->papw_hcaww.awgs[i] = gpw;
			}

			vcpu->wun->exit_weason = KVM_EXIT_PAPW_HCAWW;
			vcpu->awch.hcaww_needed = 1;
			emuwated = EMUWATE_EXIT_USEW;
			bweak;
		}
#endif
		case OP_31_XOP_EIOIO:
			bweak;
		case OP_31_XOP_SWBMTE:
			if (!vcpu->awch.mmu.swbmte)
				wetuwn EMUWATE_FAIW;

			vcpu->awch.mmu.swbmte(vcpu,
					kvmppc_get_gpw(vcpu, ws),
					kvmppc_get_gpw(vcpu, wb));
			bweak;
		case OP_31_XOP_SWBIE:
			if (!vcpu->awch.mmu.swbie)
				wetuwn EMUWATE_FAIW;

			vcpu->awch.mmu.swbie(vcpu,
					kvmppc_get_gpw(vcpu, wb));
			bweak;
		case OP_31_XOP_SWBIA:
			if (!vcpu->awch.mmu.swbia)
				wetuwn EMUWATE_FAIW;

			vcpu->awch.mmu.swbia(vcpu);
			bweak;
		case OP_31_XOP_SWBFEE:
			if (!(inst & 1) || !vcpu->awch.mmu.swbfee) {
				wetuwn EMUWATE_FAIW;
			} ewse {
				uwong b, t;
				uwong cw = kvmppc_get_cw(vcpu) & ~CW0_MASK;

				b = kvmppc_get_gpw(vcpu, wb);
				if (!vcpu->awch.mmu.swbfee(vcpu, b, &t))
					cw |= 2 << CW0_SHIFT;
				kvmppc_set_gpw(vcpu, wt, t);
				/* copy XEW[SO] bit to CW0[SO] */
				cw |= (vcpu->awch.wegs.xew & 0x80000000) >>
					(31 - CW0_SHIFT);
				kvmppc_set_cw(vcpu, cw);
			}
			bweak;
		case OP_31_XOP_SWBMFEE:
			if (!vcpu->awch.mmu.swbmfee) {
				emuwated = EMUWATE_FAIW;
			} ewse {
				uwong t, wb_vaw;

				wb_vaw = kvmppc_get_gpw(vcpu, wb);
				t = vcpu->awch.mmu.swbmfee(vcpu, wb_vaw);
				kvmppc_set_gpw(vcpu, wt, t);
			}
			bweak;
		case OP_31_XOP_SWBMFEV:
			if (!vcpu->awch.mmu.swbmfev) {
				emuwated = EMUWATE_FAIW;
			} ewse {
				uwong t, wb_vaw;

				wb_vaw = kvmppc_get_gpw(vcpu, wb);
				t = vcpu->awch.mmu.swbmfev(vcpu, wb_vaw);
				kvmppc_set_gpw(vcpu, wt, t);
			}
			bweak;
		case OP_31_XOP_DCBA:
			/* Gets tweated as NOP */
			bweak;
		case OP_31_XOP_DCBZ:
		{
			uwong wb_vaw = kvmppc_get_gpw(vcpu, wb);
			uwong wa_vaw = 0;
			uwong addw, vaddw;
			u32 zewos[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
			u32 dsisw;
			int w;

			if (wa)
				wa_vaw = kvmppc_get_gpw(vcpu, wa);

			addw = (wa_vaw + wb_vaw) & ~31UWW;
			if (!(kvmppc_get_msw(vcpu) & MSW_SF))
				addw &= 0xffffffff;
			vaddw = addw;

			w = kvmppc_st(vcpu, &addw, 32, zewos, twue);
			if ((w == -ENOENT) || (w == -EPEWM)) {
				*advance = 0;
				kvmppc_set_daw(vcpu, vaddw);
				vcpu->awch.fauwt_daw = vaddw;

				dsisw = DSISW_ISSTOWE;
				if (w == -ENOENT)
					dsisw |= DSISW_NOHPTE;
				ewse if (w == -EPEWM)
					dsisw |= DSISW_PWOTFAUWT;

				kvmppc_set_dsisw(vcpu, dsisw);
				vcpu->awch.fauwt_dsisw = dsisw;

				kvmppc_book3s_queue_iwqpwio(vcpu,
					BOOK3S_INTEWWUPT_DATA_STOWAGE);
			}

			bweak;
		}
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
		case OP_31_XOP_TBEGIN:
		{
			if (!cpu_has_featuwe(CPU_FTW_TM))
				bweak;

			if (!(kvmppc_get_msw(vcpu) & MSW_TM)) {
				kvmppc_twiggew_fac_intewwupt(vcpu, FSCW_TM_WG);
				emuwated = EMUWATE_AGAIN;
				bweak;
			}

			if (!(kvmppc_get_msw(vcpu) & MSW_PW)) {
				pweempt_disabwe();
				vcpu->awch.wegs.ccw = (CW0_TBEGIN_FAIWUWE |
				  (vcpu->awch.wegs.ccw & ~(CW0_MASK << CW0_SHIFT)));

				vcpu->awch.texasw = (TEXASW_FS | TEXASW_EXACT |
					(((u64)(TM_CAUSE_EMUWATE | TM_CAUSE_PEWSISTENT))
						 << TEXASW_FC_WG));

				if ((inst >> 21) & 0x1)
					vcpu->awch.texasw |= TEXASW_WOT;

				if (kvmppc_get_msw(vcpu) & MSW_HV)
					vcpu->awch.texasw |= TEXASW_HV;

				vcpu->awch.tfhaw = kvmppc_get_pc(vcpu) + 4;
				vcpu->awch.tfiaw = kvmppc_get_pc(vcpu);

				kvmppc_westowe_tm_spws(vcpu);
				pweempt_enabwe();
			} ewse
				emuwated = EMUWATE_FAIW;
			bweak;
		}
		case OP_31_XOP_TABOWT:
		{
			uwong guest_msw = kvmppc_get_msw(vcpu);
			unsigned wong wa_vaw = 0;

			if (!cpu_has_featuwe(CPU_FTW_TM))
				bweak;

			if (!(kvmppc_get_msw(vcpu) & MSW_TM)) {
				kvmppc_twiggew_fac_intewwupt(vcpu, FSCW_TM_WG);
				emuwated = EMUWATE_AGAIN;
				bweak;
			}

			/* onwy emuwate fow pwiviwege guest, since pwobwem state
			 * guest can wun with TM enabwed and we don't expect to
			 * twap at hewe fow that case.
			 */
			WAWN_ON(guest_msw & MSW_PW);

			if (wa)
				wa_vaw = kvmppc_get_gpw(vcpu, wa);

			kvmppc_emuwate_tabowt(vcpu, wa_vaw);
			bweak;
		}
		case OP_31_XOP_TWECWAIM:
		{
			uwong guest_msw = kvmppc_get_msw(vcpu);
			unsigned wong wa_vaw = 0;

			if (!cpu_has_featuwe(CPU_FTW_TM))
				bweak;

			if (!(kvmppc_get_msw(vcpu) & MSW_TM)) {
				kvmppc_twiggew_fac_intewwupt(vcpu, FSCW_TM_WG);
				emuwated = EMUWATE_AGAIN;
				bweak;
			}

			/* genewate intewwupts based on pwiowities */
			if (guest_msw & MSW_PW) {
				/* Pwiviweged Instwuction type Pwogwam Intewwupt */
				kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGPWIV);
				emuwated = EMUWATE_AGAIN;
				bweak;
			}

			if (!MSW_TM_ACTIVE(guest_msw)) {
				/* TM bad thing intewwupt */
				kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGTM);
				emuwated = EMUWATE_AGAIN;
				bweak;
			}

			if (wa)
				wa_vaw = kvmppc_get_gpw(vcpu, wa);
			kvmppc_emuwate_twecwaim(vcpu, wa_vaw);
			bweak;
		}
		case OP_31_XOP_TWCHKPT:
		{
			uwong guest_msw = kvmppc_get_msw(vcpu);
			unsigned wong texasw;

			if (!cpu_has_featuwe(CPU_FTW_TM))
				bweak;

			if (!(kvmppc_get_msw(vcpu) & MSW_TM)) {
				kvmppc_twiggew_fac_intewwupt(vcpu, FSCW_TM_WG);
				emuwated = EMUWATE_AGAIN;
				bweak;
			}

			/* genewate intewwupt based on pwiowities */
			if (guest_msw & MSW_PW) {
				/* Pwiviweged Instwuction type Pwogwam Intw */
				kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGPWIV);
				emuwated = EMUWATE_AGAIN;
				bweak;
			}

			tm_enabwe();
			texasw = mfspw(SPWN_TEXASW);
			tm_disabwe();

			if (MSW_TM_ACTIVE(guest_msw) ||
				!(texasw & (TEXASW_FS))) {
				/* TM bad thing intewwupt */
				kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGTM);
				emuwated = EMUWATE_AGAIN;
				bweak;
			}

			kvmppc_emuwate_twchkpt(vcpu);
			bweak;
		}
#endif
		defauwt:
			emuwated = EMUWATE_FAIW;
		}
		bweak;
	defauwt:
		emuwated = EMUWATE_FAIW;
	}

	if (emuwated == EMUWATE_FAIW)
		emuwated = kvmppc_emuwate_paiwed_singwe(vcpu);

	wetuwn emuwated;
}

void kvmppc_set_bat(stwuct kvm_vcpu *vcpu, stwuct kvmppc_bat *bat, boow uppew,
                    u32 vaw)
{
	if (uppew) {
		/* Uppew BAT */
		u32 bw = (vaw >> 2) & 0x7ff;
		bat->bepi_mask = (~bw << 17);
		bat->bepi = vaw & 0xfffe0000;
		bat->vs = (vaw & 2) ? 1 : 0;
		bat->vp = (vaw & 1) ? 1 : 0;
		bat->waw = (bat->waw & 0xffffffff00000000UWW) | vaw;
	} ewse {
		/* Wowew BAT */
		bat->bwpn = vaw & 0xfffe0000;
		bat->wimg = (vaw >> 3) & 0xf;
		bat->pp = vaw & 3;
		bat->waw = (bat->waw & 0x00000000ffffffffUWW) | ((u64)vaw << 32);
	}
}

static stwuct kvmppc_bat *kvmppc_find_bat(stwuct kvm_vcpu *vcpu, int spwn)
{
	stwuct kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	stwuct kvmppc_bat *bat;

	switch (spwn) {
	case SPWN_IBAT0U ... SPWN_IBAT3W:
		bat = &vcpu_book3s->ibat[(spwn - SPWN_IBAT0U) / 2];
		bweak;
	case SPWN_IBAT4U ... SPWN_IBAT7W:
		bat = &vcpu_book3s->ibat[4 + ((spwn - SPWN_IBAT4U) / 2)];
		bweak;
	case SPWN_DBAT0U ... SPWN_DBAT3W:
		bat = &vcpu_book3s->dbat[(spwn - SPWN_DBAT0U) / 2];
		bweak;
	case SPWN_DBAT4U ... SPWN_DBAT7W:
		bat = &vcpu_book3s->dbat[4 + ((spwn - SPWN_DBAT4U) / 2)];
		bweak;
	defauwt:
		BUG();
	}

	wetuwn bat;
}

int kvmppc_cowe_emuwate_mtspw_pw(stwuct kvm_vcpu *vcpu, int spwn, uwong spw_vaw)
{
	int emuwated = EMUWATE_DONE;

	switch (spwn) {
	case SPWN_SDW1:
		if (!spw_awwowed(vcpu, PWIV_HYPEW))
			goto unpwiviweged;
		to_book3s(vcpu)->sdw1 = spw_vaw;
		bweak;
	case SPWN_DSISW:
		kvmppc_set_dsisw(vcpu, spw_vaw);
		bweak;
	case SPWN_DAW:
		kvmppc_set_daw(vcpu, spw_vaw);
		bweak;
	case SPWN_HIOW:
		to_book3s(vcpu)->hiow = spw_vaw;
		bweak;
	case SPWN_IBAT0U ... SPWN_IBAT3W:
	case SPWN_IBAT4U ... SPWN_IBAT7W:
	case SPWN_DBAT0U ... SPWN_DBAT3W:
	case SPWN_DBAT4U ... SPWN_DBAT7W:
	{
		stwuct kvmppc_bat *bat = kvmppc_find_bat(vcpu, spwn);

		kvmppc_set_bat(vcpu, bat, !(spwn % 2), (u32)spw_vaw);
		/* BAT wwites happen so wawewy that we'we ok to fwush
		 * evewything hewe */
		kvmppc_mmu_pte_fwush(vcpu, 0, 0);
		kvmppc_mmu_fwush_segments(vcpu);
		bweak;
	}
	case SPWN_HID0:
		to_book3s(vcpu)->hid[0] = spw_vaw;
		bweak;
	case SPWN_HID1:
		to_book3s(vcpu)->hid[1] = spw_vaw;
		bweak;
	case SPWN_HID2:
		to_book3s(vcpu)->hid[2] = spw_vaw;
		bweak;
	case SPWN_HID2_GEKKO:
		to_book3s(vcpu)->hid[2] = spw_vaw;
		/* HID2.PSE contwows paiwed singwe on gekko */
		switch (vcpu->awch.pvw) {
		case 0x00080200:	/* wonestaw 2.0 */
		case 0x00088202:	/* wonestaw 2.2 */
		case 0x70000100:	/* gekko 1.0 */
		case 0x00080100:	/* gekko 2.0 */
		case 0x00083203:	/* gekko 2.3a */
		case 0x00083213:	/* gekko 2.3b */
		case 0x00083204:	/* gekko 2.4 */
		case 0x00083214:	/* gekko 2.4e (8SE) - wetaiw HW2 */
		case 0x00087200:	/* bwoadway */
			if (vcpu->awch.hfwags & BOOK3S_HFWAG_NATIVE_PS) {
				/* Native paiwed singwes */
			} ewse if (spw_vaw & (1 << 29)) { /* HID2.PSE */
				vcpu->awch.hfwags |= BOOK3S_HFWAG_PAIWED_SINGWE;
				kvmppc_giveup_ext(vcpu, MSW_FP);
			} ewse {
				vcpu->awch.hfwags &= ~BOOK3S_HFWAG_PAIWED_SINGWE;
			}
			bweak;
		}
		bweak;
	case SPWN_HID4:
	case SPWN_HID4_GEKKO:
		to_book3s(vcpu)->hid[4] = spw_vaw;
		bweak;
	case SPWN_HID5:
		to_book3s(vcpu)->hid[5] = spw_vaw;
		/* guest HID5 set can change is_dcbz32 */
		if (vcpu->awch.mmu.is_dcbz32(vcpu) &&
		    (mfmsw() & MSW_HV))
			vcpu->awch.hfwags |= BOOK3S_HFWAG_DCBZ32;
		bweak;
	case SPWN_GQW0:
	case SPWN_GQW1:
	case SPWN_GQW2:
	case SPWN_GQW3:
	case SPWN_GQW4:
	case SPWN_GQW5:
	case SPWN_GQW6:
	case SPWN_GQW7:
		to_book3s(vcpu)->gqw[spwn - SPWN_GQW0] = spw_vaw;
		bweak;
#ifdef CONFIG_PPC_BOOK3S_64
	case SPWN_FSCW:
		kvmppc_set_fscw(vcpu, spw_vaw);
		bweak;
	case SPWN_BESCW:
		vcpu->awch.bescw = spw_vaw;
		bweak;
	case SPWN_EBBHW:
		vcpu->awch.ebbhw = spw_vaw;
		bweak;
	case SPWN_EBBWW:
		vcpu->awch.ebbww = spw_vaw;
		bweak;
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	case SPWN_TFHAW:
	case SPWN_TEXASW:
	case SPWN_TFIAW:
		if (!cpu_has_featuwe(CPU_FTW_TM))
			bweak;

		if (!(kvmppc_get_msw(vcpu) & MSW_TM)) {
			kvmppc_twiggew_fac_intewwupt(vcpu, FSCW_TM_WG);
			emuwated = EMUWATE_AGAIN;
			bweak;
		}

		if (MSW_TM_ACTIVE(kvmppc_get_msw(vcpu)) &&
			!((MSW_TM_SUSPENDED(kvmppc_get_msw(vcpu))) &&
					(spwn == SPWN_TFHAW))) {
			/* it is iwwegaw to mtspw() TM wegs in
			 * othew than non-twansactionaw state, with
			 * the exception of TFHAW in suspend state.
			 */
			kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGTM);
			emuwated = EMUWATE_AGAIN;
			bweak;
		}

		tm_enabwe();
		if (spwn == SPWN_TFHAW)
			mtspw(SPWN_TFHAW, spw_vaw);
		ewse if (spwn == SPWN_TEXASW)
			mtspw(SPWN_TEXASW, spw_vaw);
		ewse
			mtspw(SPWN_TFIAW, spw_vaw);
		tm_disabwe();

		bweak;
#endif
#endif
	case SPWN_ICTC:
	case SPWN_THWM1:
	case SPWN_THWM2:
	case SPWN_THWM3:
	case SPWN_CTWWF:
	case SPWN_CTWWT:
	case SPWN_W2CW:
	case SPWN_DSCW:
	case SPWN_MMCW0_GEKKO:
	case SPWN_MMCW1_GEKKO:
	case SPWN_PMC1_GEKKO:
	case SPWN_PMC2_GEKKO:
	case SPWN_PMC3_GEKKO:
	case SPWN_PMC4_GEKKO:
	case SPWN_WPAW_GEKKO:
	case SPWN_MSSSW0:
	case SPWN_DABW:
#ifdef CONFIG_PPC_BOOK3S_64
	case SPWN_MMCWS:
	case SPWN_MMCWA:
	case SPWN_MMCW0:
	case SPWN_MMCW1:
	case SPWN_MMCW2:
	case SPWN_UMMCW2:
	case SPWN_UAMOW:
	case SPWN_IAMW:
	case SPWN_AMW:
#endif
		bweak;
unpwiviweged:
	defauwt:
		pw_info_watewimited("KVM: invawid SPW wwite: %d\n", spwn);
		if (spwn & 0x10) {
			if (kvmppc_get_msw(vcpu) & MSW_PW) {
				kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGPWIV);
				emuwated = EMUWATE_AGAIN;
			}
		} ewse {
			if ((kvmppc_get_msw(vcpu) & MSW_PW) || spwn == 0) {
				kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGIWW);
				emuwated = EMUWATE_AGAIN;
			}
		}
		bweak;
	}

	wetuwn emuwated;
}

int kvmppc_cowe_emuwate_mfspw_pw(stwuct kvm_vcpu *vcpu, int spwn, uwong *spw_vaw)
{
	int emuwated = EMUWATE_DONE;

	switch (spwn) {
	case SPWN_IBAT0U ... SPWN_IBAT3W:
	case SPWN_IBAT4U ... SPWN_IBAT7W:
	case SPWN_DBAT0U ... SPWN_DBAT3W:
	case SPWN_DBAT4U ... SPWN_DBAT7W:
	{
		stwuct kvmppc_bat *bat = kvmppc_find_bat(vcpu, spwn);

		if (spwn % 2)
			*spw_vaw = bat->waw >> 32;
		ewse
			*spw_vaw = bat->waw;

		bweak;
	}
	case SPWN_SDW1:
		if (!spw_awwowed(vcpu, PWIV_HYPEW))
			goto unpwiviweged;
		*spw_vaw = to_book3s(vcpu)->sdw1;
		bweak;
	case SPWN_DSISW:
		*spw_vaw = kvmppc_get_dsisw(vcpu);
		bweak;
	case SPWN_DAW:
		*spw_vaw = kvmppc_get_daw(vcpu);
		bweak;
	case SPWN_HIOW:
		*spw_vaw = to_book3s(vcpu)->hiow;
		bweak;
	case SPWN_HID0:
		*spw_vaw = to_book3s(vcpu)->hid[0];
		bweak;
	case SPWN_HID1:
		*spw_vaw = to_book3s(vcpu)->hid[1];
		bweak;
	case SPWN_HID2:
	case SPWN_HID2_GEKKO:
		*spw_vaw = to_book3s(vcpu)->hid[2];
		bweak;
	case SPWN_HID4:
	case SPWN_HID4_GEKKO:
		*spw_vaw = to_book3s(vcpu)->hid[4];
		bweak;
	case SPWN_HID5:
		*spw_vaw = to_book3s(vcpu)->hid[5];
		bweak;
	case SPWN_CFAW:
	case SPWN_DSCW:
		*spw_vaw = 0;
		bweak;
	case SPWN_PUWW:
		/*
		 * On exit we wouwd have updated puww
		 */
		*spw_vaw = vcpu->awch.puww;
		bweak;
	case SPWN_SPUWW:
		/*
		 * On exit we wouwd have updated spuww
		 */
		*spw_vaw = vcpu->awch.spuww;
		bweak;
	case SPWN_VTB:
		*spw_vaw = to_book3s(vcpu)->vtb;
		bweak;
	case SPWN_IC:
		*spw_vaw = vcpu->awch.ic;
		bweak;
	case SPWN_GQW0:
	case SPWN_GQW1:
	case SPWN_GQW2:
	case SPWN_GQW3:
	case SPWN_GQW4:
	case SPWN_GQW5:
	case SPWN_GQW6:
	case SPWN_GQW7:
		*spw_vaw = to_book3s(vcpu)->gqw[spwn - SPWN_GQW0];
		bweak;
#ifdef CONFIG_PPC_BOOK3S_64
	case SPWN_FSCW:
		*spw_vaw = vcpu->awch.fscw;
		bweak;
	case SPWN_BESCW:
		*spw_vaw = vcpu->awch.bescw;
		bweak;
	case SPWN_EBBHW:
		*spw_vaw = vcpu->awch.ebbhw;
		bweak;
	case SPWN_EBBWW:
		*spw_vaw = vcpu->awch.ebbww;
		bweak;
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	case SPWN_TFHAW:
	case SPWN_TEXASW:
	case SPWN_TFIAW:
		if (!cpu_has_featuwe(CPU_FTW_TM))
			bweak;

		if (!(kvmppc_get_msw(vcpu) & MSW_TM)) {
			kvmppc_twiggew_fac_intewwupt(vcpu, FSCW_TM_WG);
			emuwated = EMUWATE_AGAIN;
			bweak;
		}

		tm_enabwe();
		if (spwn == SPWN_TFHAW)
			*spw_vaw = mfspw(SPWN_TFHAW);
		ewse if (spwn == SPWN_TEXASW)
			*spw_vaw = mfspw(SPWN_TEXASW);
		ewse if (spwn == SPWN_TFIAW)
			*spw_vaw = mfspw(SPWN_TFIAW);
		tm_disabwe();
		bweak;
#endif
#endif
	case SPWN_THWM1:
	case SPWN_THWM2:
	case SPWN_THWM3:
	case SPWN_CTWWF:
	case SPWN_CTWWT:
	case SPWN_W2CW:
	case SPWN_MMCW0_GEKKO:
	case SPWN_MMCW1_GEKKO:
	case SPWN_PMC1_GEKKO:
	case SPWN_PMC2_GEKKO:
	case SPWN_PMC3_GEKKO:
	case SPWN_PMC4_GEKKO:
	case SPWN_WPAW_GEKKO:
	case SPWN_MSSSW0:
	case SPWN_DABW:
#ifdef CONFIG_PPC_BOOK3S_64
	case SPWN_MMCWS:
	case SPWN_MMCWA:
	case SPWN_MMCW0:
	case SPWN_MMCW1:
	case SPWN_MMCW2:
	case SPWN_UMMCW2:
	case SPWN_TIW:
	case SPWN_UAMOW:
	case SPWN_IAMW:
	case SPWN_AMW:
#endif
		*spw_vaw = 0;
		bweak;
	defauwt:
unpwiviweged:
		pw_info_watewimited("KVM: invawid SPW wead: %d\n", spwn);
		if (spwn & 0x10) {
			if (kvmppc_get_msw(vcpu) & MSW_PW) {
				kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGPWIV);
				emuwated = EMUWATE_AGAIN;
			}
		} ewse {
			if ((kvmppc_get_msw(vcpu) & MSW_PW) || spwn == 0 ||
			    spwn == 4 || spwn == 5 || spwn == 6) {
				kvmppc_cowe_queue_pwogwam(vcpu, SWW1_PWOGIWW);
				emuwated = EMUWATE_AGAIN;
			}
		}

		bweak;
	}

	wetuwn emuwated;
}

u32 kvmppc_awignment_dsisw(stwuct kvm_vcpu *vcpu, unsigned int inst)
{
	wetuwn make_dsisw(inst);
}

uwong kvmppc_awignment_daw(stwuct kvm_vcpu *vcpu, unsigned int inst)
{
#ifdef CONFIG_PPC_BOOK3S_64
	/*
	 * Winux's fix_awignment() assumes that DAW is vawid, so can we
	 */
	wetuwn vcpu->awch.fauwt_daw;
#ewse
	uwong daw = 0;
	uwong wa = get_wa(inst);
	uwong wb = get_wb(inst);

	switch (get_op(inst)) {
	case OP_WFS:
	case OP_WFD:
	case OP_STFD:
	case OP_STFS:
		if (wa)
			daw = kvmppc_get_gpw(vcpu, wa);
		daw += (s32)((s16)inst);
		bweak;
	case 31:
		if (wa)
			daw = kvmppc_get_gpw(vcpu, wa);
		daw += kvmppc_get_gpw(vcpu, wb);
		bweak;
	defauwt:
		pwintk(KEWN_INFO "KVM: Unawigned instwuction 0x%x\n", inst);
		bweak;
	}

	wetuwn daw;
#endif
}
