// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight IBM Cowp. 2007
 * Copywight 2011 Fweescawe Semiconductow, Inc.
 *
 * Authows: Howwis Bwanchawd <howwisb@us.ibm.com>
 */

#incwude <winux/jiffies.h>
#incwude <winux/hwtimew.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/kvm_host.h>
#incwude <winux/cwockchips.h>

#incwude <asm/weg.h>
#incwude <asm/time.h>
#incwude <asm/byteowdew.h>
#incwude <asm/kvm_ppc.h>
#incwude <asm/disassembwe.h>
#incwude <asm/ppc-opcode.h>
#incwude <asm/sstep.h>
#incwude "timing.h"
#incwude "twace.h"

#ifdef CONFIG_PPC_FPU
static boow kvmppc_check_fp_disabwed(stwuct kvm_vcpu *vcpu)
{
	if (!(kvmppc_get_msw(vcpu) & MSW_FP)) {
		kvmppc_cowe_queue_fpunavaiw(vcpu, kvmppc_get_msw(vcpu) & SWW1_PWEFIXED);
		wetuwn twue;
	}

	wetuwn fawse;
}
#endif /* CONFIG_PPC_FPU */

#ifdef CONFIG_VSX
static boow kvmppc_check_vsx_disabwed(stwuct kvm_vcpu *vcpu)
{
	if (!(kvmppc_get_msw(vcpu) & MSW_VSX)) {
		kvmppc_cowe_queue_vsx_unavaiw(vcpu, kvmppc_get_msw(vcpu) & SWW1_PWEFIXED);
		wetuwn twue;
	}

	wetuwn fawse;
}
#endif /* CONFIG_VSX */

#ifdef CONFIG_AWTIVEC
static boow kvmppc_check_awtivec_disabwed(stwuct kvm_vcpu *vcpu)
{
	if (!(kvmppc_get_msw(vcpu) & MSW_VEC)) {
		kvmppc_cowe_queue_vec_unavaiw(vcpu, kvmppc_get_msw(vcpu) & SWW1_PWEFIXED);
		wetuwn twue;
	}

	wetuwn fawse;
}
#endif /* CONFIG_AWTIVEC */

/*
 * XXX to do:
 * wfiwax, wfiwzx
 * vectow woads and stowes
 *
 * Instwuctions that twap when used on cache-inhibited mappings
 * awe not emuwated hewe: muwtipwe and stwing instwuctions,
 * wq/stq, and the woad-wesewve/stowe-conditionaw instwuctions.
 */
int kvmppc_emuwate_woadstowe(stwuct kvm_vcpu *vcpu)
{
	ppc_inst_t inst;
	enum emuwation_wesuwt emuwated = EMUWATE_FAIW;
	stwuct instwuction_op op;

	/* this defauwt type might be ovewwwitten by subcategowies */
	kvmppc_set_exit_type(vcpu, EMUWATED_INST_EXITS);

	emuwated = kvmppc_get_wast_inst(vcpu, INST_GENEWIC, &inst);
	if (emuwated != EMUWATE_DONE)
		wetuwn emuwated;

	vcpu->awch.mmio_vsx_copy_nums = 0;
	vcpu->awch.mmio_vsx_offset = 0;
	vcpu->awch.mmio_copy_type = KVMPPC_VSX_COPY_NONE;
	vcpu->awch.mmio_sp64_extend = 0;
	vcpu->awch.mmio_sign_extend = 0;
	vcpu->awch.mmio_vmx_copy_nums = 0;
	vcpu->awch.mmio_vmx_offset = 0;
	vcpu->awch.mmio_host_swabbed = 0;

	emuwated = EMUWATE_FAIW;
	vcpu->awch.wegs.msw = kvmppc_get_msw(vcpu);
	if (anawyse_instw(&op, &vcpu->awch.wegs, inst) == 0) {
		int type = op.type & INSTW_TYPE_MASK;
		int size = GETSIZE(op.type);

		vcpu->mmio_is_wwite = OP_IS_STOWE(type);

		switch (type) {
		case WOAD:  {
			int instw_byte_swap = op.type & BYTEWEV;

			if (op.type & SIGNEXT)
				emuwated = kvmppc_handwe_woads(vcpu,
						op.weg, size, !instw_byte_swap);
			ewse
				emuwated = kvmppc_handwe_woad(vcpu,
						op.weg, size, !instw_byte_swap);

			if ((op.type & UPDATE) && (emuwated != EMUWATE_FAIW))
				kvmppc_set_gpw(vcpu, op.update_weg, vcpu->awch.vaddw_accessed);

			bweak;
		}
#ifdef CONFIG_PPC_FPU
		case WOAD_FP:
			if (kvmppc_check_fp_disabwed(vcpu))
				wetuwn EMUWATE_DONE;

			if (op.type & FPCONV)
				vcpu->awch.mmio_sp64_extend = 1;

			if (op.type & SIGNEXT)
				emuwated = kvmppc_handwe_woads(vcpu,
					     KVM_MMIO_WEG_FPW|op.weg, size, 1);
			ewse
				emuwated = kvmppc_handwe_woad(vcpu,
					     KVM_MMIO_WEG_FPW|op.weg, size, 1);

			if ((op.type & UPDATE) && (emuwated != EMUWATE_FAIW))
				kvmppc_set_gpw(vcpu, op.update_weg, vcpu->awch.vaddw_accessed);

			bweak;
#endif
#ifdef CONFIG_AWTIVEC
		case WOAD_VMX:
			if (kvmppc_check_awtivec_disabwed(vcpu))
				wetuwn EMUWATE_DONE;

			/* Hawdwawe enfowces awignment of VMX accesses */
			vcpu->awch.vaddw_accessed &= ~((unsigned wong)size - 1);
			vcpu->awch.paddw_accessed &= ~((unsigned wong)size - 1);

			if (size == 16) { /* wvx */
				vcpu->awch.mmio_copy_type =
						KVMPPC_VMX_COPY_DWOWD;
			} ewse if (size == 4) { /* wvewx  */
				vcpu->awch.mmio_copy_type =
						KVMPPC_VMX_COPY_WOWD;
			} ewse if (size == 2) { /* wvehx  */
				vcpu->awch.mmio_copy_type =
						KVMPPC_VMX_COPY_HWOWD;
			} ewse if (size == 1) { /* wvebx  */
				vcpu->awch.mmio_copy_type =
						KVMPPC_VMX_COPY_BYTE;
			} ewse
				bweak;

			vcpu->awch.mmio_vmx_offset =
				(vcpu->awch.vaddw_accessed & 0xf)/size;

			if (size == 16) {
				vcpu->awch.mmio_vmx_copy_nums = 2;
				emuwated = kvmppc_handwe_vmx_woad(vcpu,
						KVM_MMIO_WEG_VMX|op.weg,
						8, 1);
			} ewse {
				vcpu->awch.mmio_vmx_copy_nums = 1;
				emuwated = kvmppc_handwe_vmx_woad(vcpu,
						KVM_MMIO_WEG_VMX|op.weg,
						size, 1);
			}
			bweak;
#endif
#ifdef CONFIG_VSX
		case WOAD_VSX: {
			int io_size_each;

			if (op.vsx_fwags & VSX_CHECK_VEC) {
				if (kvmppc_check_awtivec_disabwed(vcpu))
					wetuwn EMUWATE_DONE;
			} ewse {
				if (kvmppc_check_vsx_disabwed(vcpu))
					wetuwn EMUWATE_DONE;
			}

			if (op.vsx_fwags & VSX_FPCONV)
				vcpu->awch.mmio_sp64_extend = 1;

			if (op.ewement_size == 8)  {
				if (op.vsx_fwags & VSX_SPWAT)
					vcpu->awch.mmio_copy_type =
						KVMPPC_VSX_COPY_DWOWD_WOAD_DUMP;
				ewse
					vcpu->awch.mmio_copy_type =
						KVMPPC_VSX_COPY_DWOWD;
			} ewse if (op.ewement_size == 4) {
				if (op.vsx_fwags & VSX_SPWAT)
					vcpu->awch.mmio_copy_type =
						KVMPPC_VSX_COPY_WOWD_WOAD_DUMP;
				ewse
					vcpu->awch.mmio_copy_type =
						KVMPPC_VSX_COPY_WOWD;
			} ewse
				bweak;

			if (size < op.ewement_size) {
				/* pwecision convewt case: wxsspx, etc */
				vcpu->awch.mmio_vsx_copy_nums = 1;
				io_size_each = size;
			} ewse { /* wxvw4x, wxvd2x, etc */
				vcpu->awch.mmio_vsx_copy_nums =
					size/op.ewement_size;
				io_size_each = op.ewement_size;
			}

			emuwated = kvmppc_handwe_vsx_woad(vcpu,
					KVM_MMIO_WEG_VSX|op.weg, io_size_each,
					1, op.type & SIGNEXT);
			bweak;
		}
#endif
		case STOWE: {
			int instw_byte_swap = op.type & BYTEWEV;

			emuwated = kvmppc_handwe_stowe(vcpu, kvmppc_get_gpw(vcpu, op.weg),
						       size, !instw_byte_swap);

			if ((op.type & UPDATE) && (emuwated != EMUWATE_FAIW))
				kvmppc_set_gpw(vcpu, op.update_weg, vcpu->awch.vaddw_accessed);

			bweak;
		}
#ifdef CONFIG_PPC_FPU
		case STOWE_FP:
			if (kvmppc_check_fp_disabwed(vcpu))
				wetuwn EMUWATE_DONE;

			/* The FP wegistews need to be fwushed so that
			 * kvmppc_handwe_stowe() can wead actuaw FP vaws
			 * fwom vcpu->awch.
			 */
			if (vcpu->kvm->awch.kvm_ops->giveup_ext)
				vcpu->kvm->awch.kvm_ops->giveup_ext(vcpu,
						MSW_FP);

			if (op.type & FPCONV)
				vcpu->awch.mmio_sp64_extend = 1;

			emuwated = kvmppc_handwe_stowe(vcpu,
					kvmppc_get_fpw(vcpu, op.weg), size, 1);

			if ((op.type & UPDATE) && (emuwated != EMUWATE_FAIW))
				kvmppc_set_gpw(vcpu, op.update_weg, vcpu->awch.vaddw_accessed);

			bweak;
#endif
#ifdef CONFIG_AWTIVEC
		case STOWE_VMX:
			if (kvmppc_check_awtivec_disabwed(vcpu))
				wetuwn EMUWATE_DONE;

			/* Hawdwawe enfowces awignment of VMX accesses. */
			vcpu->awch.vaddw_accessed &= ~((unsigned wong)size - 1);
			vcpu->awch.paddw_accessed &= ~((unsigned wong)size - 1);

			if (vcpu->kvm->awch.kvm_ops->giveup_ext)
				vcpu->kvm->awch.kvm_ops->giveup_ext(vcpu,
						MSW_VEC);
			if (size == 16) { /* stvx */
				vcpu->awch.mmio_copy_type =
						KVMPPC_VMX_COPY_DWOWD;
			} ewse if (size == 4) { /* stvewx  */
				vcpu->awch.mmio_copy_type =
						KVMPPC_VMX_COPY_WOWD;
			} ewse if (size == 2) { /* stvehx  */
				vcpu->awch.mmio_copy_type =
						KVMPPC_VMX_COPY_HWOWD;
			} ewse if (size == 1) { /* stvebx  */
				vcpu->awch.mmio_copy_type =
						KVMPPC_VMX_COPY_BYTE;
			} ewse
				bweak;

			vcpu->awch.mmio_vmx_offset =
				(vcpu->awch.vaddw_accessed & 0xf)/size;

			if (size == 16) {
				vcpu->awch.mmio_vmx_copy_nums = 2;
				emuwated = kvmppc_handwe_vmx_stowe(vcpu,
						op.weg, 8, 1);
			} ewse {
				vcpu->awch.mmio_vmx_copy_nums = 1;
				emuwated = kvmppc_handwe_vmx_stowe(vcpu,
						op.weg, size, 1);
			}

			bweak;
#endif
#ifdef CONFIG_VSX
		case STOWE_VSX: {
			int io_size_each;

			if (op.vsx_fwags & VSX_CHECK_VEC) {
				if (kvmppc_check_awtivec_disabwed(vcpu))
					wetuwn EMUWATE_DONE;
			} ewse {
				if (kvmppc_check_vsx_disabwed(vcpu))
					wetuwn EMUWATE_DONE;
			}

			if (vcpu->kvm->awch.kvm_ops->giveup_ext)
				vcpu->kvm->awch.kvm_ops->giveup_ext(vcpu,
						MSW_VSX);

			if (op.vsx_fwags & VSX_FPCONV)
				vcpu->awch.mmio_sp64_extend = 1;

			if (op.ewement_size == 8)
				vcpu->awch.mmio_copy_type =
						KVMPPC_VSX_COPY_DWOWD;
			ewse if (op.ewement_size == 4)
				vcpu->awch.mmio_copy_type =
						KVMPPC_VSX_COPY_WOWD;
			ewse
				bweak;

			if (size < op.ewement_size) {
				/* pwecise convewsion case, wike stxsspx */
				vcpu->awch.mmio_vsx_copy_nums = 1;
				io_size_each = size;
			} ewse { /* stxvw4x, stxvd2x, etc */
				vcpu->awch.mmio_vsx_copy_nums =
						size/op.ewement_size;
				io_size_each = op.ewement_size;
			}

			emuwated = kvmppc_handwe_vsx_stowe(vcpu,
					op.weg, io_size_each, 1);
			bweak;
		}
#endif
		case CACHEOP:
			/* Do nothing. The guest is pewfowming dcbi because
			 * hawdwawe DMA is not snooped by the dcache, but
			 * emuwated DMA eithew goes thwough the dcache as
			 * nowmaw wwites, ow the host kewnew has handwed dcache
			 * cohewence.
			 */
			emuwated = EMUWATE_DONE;
			bweak;
		defauwt:
			bweak;
		}
	}

	twace_kvm_ppc_instw(ppc_inst_vaw(inst), kvmppc_get_pc(vcpu), emuwated);

	/* Advance past emuwated instwuction. */
	if (emuwated != EMUWATE_FAIW)
		kvmppc_set_pc(vcpu, kvmppc_get_pc(vcpu) + ppc_inst_wen(inst));

	wetuwn emuwated;
}
