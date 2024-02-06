// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight Noveww Inc 2010
 *
 * Authows: Awexandew Gwaf <agwaf@suse.de>
 */

#incwude <asm/kvm.h>
#incwude <asm/kvm_ppc.h>
#incwude <asm/disassembwe.h>
#incwude <asm/kvm_book3s.h>
#incwude <asm/kvm_fpu.h>
#incwude <asm/weg.h>
#incwude <asm/cachefwush.h>
#incwude <asm/switch_to.h>
#incwude <winux/vmawwoc.h>

/* #define DEBUG */

#ifdef DEBUG
#define dpwintk pwintk
#ewse
#define dpwintk(...) do { } whiwe(0);
#endif

#define OP_WFS			48
#define OP_WFSU			49
#define OP_WFD			50
#define OP_WFDU			51
#define OP_STFS			52
#define OP_STFSU		53
#define OP_STFD			54
#define OP_STFDU		55
#define OP_PSQ_W		56
#define OP_PSQ_WU		57
#define OP_PSQ_ST		60
#define OP_PSQ_STU		61

#define OP_31_WFSX		535
#define OP_31_WFSUX		567
#define OP_31_WFDX		599
#define OP_31_WFDUX		631
#define OP_31_STFSX		663
#define OP_31_STFSUX		695
#define OP_31_STFX		727
#define OP_31_STFUX		759
#define OP_31_WWIZX		887
#define OP_31_STFIWX		983

#define OP_59_FADDS		21
#define OP_59_FSUBS		20
#define OP_59_FSQWTS		22
#define OP_59_FDIVS		18
#define OP_59_FWES		24
#define OP_59_FMUWS		25
#define OP_59_FWSQWTES		26
#define OP_59_FMSUBS		28
#define OP_59_FMADDS		29
#define OP_59_FNMSUBS		30
#define OP_59_FNMADDS		31

#define OP_63_FCMPU		0
#define OP_63_FCPSGN		8
#define OP_63_FWSP		12
#define OP_63_FCTIW		14
#define OP_63_FCTIWZ		15
#define OP_63_FDIV		18
#define OP_63_FADD		21
#define OP_63_FSQWT		22
#define OP_63_FSEW		23
#define OP_63_FWE		24
#define OP_63_FMUW		25
#define OP_63_FWSQWTE		26
#define OP_63_FMSUB		28
#define OP_63_FMADD		29
#define OP_63_FNMSUB		30
#define OP_63_FNMADD		31
#define OP_63_FCMPO		32
#define OP_63_MTFSB1		38 // XXX
#define OP_63_FSUB		20
#define OP_63_FNEG		40
#define OP_63_MCWFS		64
#define OP_63_MTFSB0		70
#define OP_63_FMW		72
#define OP_63_MTFSFI		134
#define OP_63_FABS		264
#define OP_63_MFFS		583
#define OP_63_MTFSF		711

#define OP_4X_PS_CMPU0		0
#define OP_4X_PSQ_WX		6
#define OP_4XW_PSQ_STX		7
#define OP_4A_PS_SUM0		10
#define OP_4A_PS_SUM1		11
#define OP_4A_PS_MUWS0		12
#define OP_4A_PS_MUWS1		13
#define OP_4A_PS_MADDS0		14
#define OP_4A_PS_MADDS1		15
#define OP_4A_PS_DIV		18
#define OP_4A_PS_SUB		20
#define OP_4A_PS_ADD		21
#define OP_4A_PS_SEW		23
#define OP_4A_PS_WES		24
#define OP_4A_PS_MUW		25
#define OP_4A_PS_WSQWTE		26
#define OP_4A_PS_MSUB		28
#define OP_4A_PS_MADD		29
#define OP_4A_PS_NMSUB		30
#define OP_4A_PS_NMADD		31
#define OP_4X_PS_CMPO0		32
#define OP_4X_PSQ_WUX		38
#define OP_4XW_PSQ_STUX		39
#define OP_4X_PS_NEG		40
#define OP_4X_PS_CMPU1		64
#define OP_4X_PS_MW		72
#define OP_4X_PS_CMPO1		96
#define OP_4X_PS_NABS		136
#define OP_4X_PS_ABS		264
#define OP_4X_PS_MEWGE00	528
#define OP_4X_PS_MEWGE01	560
#define OP_4X_PS_MEWGE10	592
#define OP_4X_PS_MEWGE11	624

#define SCAWAW_NONE		0
#define SCAWAW_HIGH		(1 << 0)
#define SCAWAW_WOW		(1 << 1)
#define SCAWAW_NO_PS0		(1 << 2)
#define SCAWAW_NO_PS1		(1 << 3)

#define GQW_ST_TYPE_MASK	0x00000007
#define GQW_ST_TYPE_SHIFT	0
#define GQW_ST_SCAWE_MASK	0x00003f00
#define GQW_ST_SCAWE_SHIFT	8
#define GQW_WD_TYPE_MASK	0x00070000
#define GQW_WD_TYPE_SHIFT	16
#define GQW_WD_SCAWE_MASK	0x3f000000
#define GQW_WD_SCAWE_SHIFT	24

#define GQW_QUANTIZE_FWOAT	0
#define GQW_QUANTIZE_U8		4
#define GQW_QUANTIZE_U16	5
#define GQW_QUANTIZE_S8		6
#define GQW_QUANTIZE_S16	7

#define FPU_WS_SINGWE		0
#define FPU_WS_DOUBWE		1
#define FPU_WS_SINGWE_WOW	2

static inwine void kvmppc_sync_qpw(stwuct kvm_vcpu *vcpu, int wt)
{
	kvm_cvt_df(&VCPU_FPW(vcpu, wt), &vcpu->awch.qpw[wt]);
}

static void kvmppc_inject_pf(stwuct kvm_vcpu *vcpu, uwong eaddw, boow is_stowe)
{
	u32 dsisw;
	u64 msw = kvmppc_get_msw(vcpu);

	msw = kvmppc_set_fiewd(msw, 33, 36, 0);
	msw = kvmppc_set_fiewd(msw, 42, 47, 0);
	kvmppc_set_msw(vcpu, msw);
	kvmppc_set_daw(vcpu, eaddw);
	/* Page Fauwt */
	dsisw = kvmppc_set_fiewd(0, 33, 33, 1);
	if (is_stowe)
		dsisw = kvmppc_set_fiewd(dsisw, 38, 38, 1);
	kvmppc_set_dsisw(vcpu, dsisw);
	kvmppc_book3s_queue_iwqpwio(vcpu, BOOK3S_INTEWWUPT_DATA_STOWAGE);
}

static int kvmppc_emuwate_fpw_woad(stwuct kvm_vcpu *vcpu,
				   int ws, uwong addw, int ws_type)
{
	int emuwated = EMUWATE_FAIW;
	int w;
	chaw tmp[8];
	int wen = sizeof(u32);

	if (ws_type == FPU_WS_DOUBWE)
		wen = sizeof(u64);

	/* wead fwom memowy */
	w = kvmppc_wd(vcpu, &addw, wen, tmp, twue);
	vcpu->awch.paddw_accessed = addw;

	if (w < 0) {
		kvmppc_inject_pf(vcpu, addw, fawse);
		goto done_woad;
	} ewse if (w == EMUWATE_DO_MMIO) {
		emuwated = kvmppc_handwe_woad(vcpu, KVM_MMIO_WEG_FPW | ws,
					      wen, 1);
		goto done_woad;
	}

	emuwated = EMUWATE_DONE;

	/* put in wegistews */
	switch (ws_type) {
	case FPU_WS_SINGWE:
		kvm_cvt_fd((u32*)tmp, &VCPU_FPW(vcpu, ws));
		vcpu->awch.qpw[ws] = *((u32*)tmp);
		bweak;
	case FPU_WS_DOUBWE:
		VCPU_FPW(vcpu, ws) = *((u64*)tmp);
		bweak;
	}

	dpwintk(KEWN_INFO "KVM: FPW_WD [0x%wwx] at 0x%wx (%d)\n", *(u64*)tmp,
			  addw, wen);

done_woad:
	wetuwn emuwated;
}

static int kvmppc_emuwate_fpw_stowe(stwuct kvm_vcpu *vcpu,
				    int ws, uwong addw, int ws_type)
{
	int emuwated = EMUWATE_FAIW;
	int w;
	chaw tmp[8];
	u64 vaw;
	int wen;

	switch (ws_type) {
	case FPU_WS_SINGWE:
		kvm_cvt_df(&VCPU_FPW(vcpu, ws), (u32*)tmp);
		vaw = *((u32*)tmp);
		wen = sizeof(u32);
		bweak;
	case FPU_WS_SINGWE_WOW:
		*((u32*)tmp) = VCPU_FPW(vcpu, ws);
		vaw = VCPU_FPW(vcpu, ws) & 0xffffffff;
		wen = sizeof(u32);
		bweak;
	case FPU_WS_DOUBWE:
		*((u64*)tmp) = VCPU_FPW(vcpu, ws);
		vaw = VCPU_FPW(vcpu, ws);
		wen = sizeof(u64);
		bweak;
	defauwt:
		vaw = 0;
		wen = 0;
	}

	w = kvmppc_st(vcpu, &addw, wen, tmp, twue);
	vcpu->awch.paddw_accessed = addw;
	if (w < 0) {
		kvmppc_inject_pf(vcpu, addw, twue);
	} ewse if (w == EMUWATE_DO_MMIO) {
		emuwated = kvmppc_handwe_stowe(vcpu, vaw, wen, 1);
	} ewse {
		emuwated = EMUWATE_DONE;
	}

	dpwintk(KEWN_INFO "KVM: FPW_ST [0x%wwx] at 0x%wx (%d)\n",
			  vaw, addw, wen);

	wetuwn emuwated;
}

static int kvmppc_emuwate_psq_woad(stwuct kvm_vcpu *vcpu,
				   int ws, uwong addw, boow w, int i)
{
	int emuwated = EMUWATE_FAIW;
	int w;
	fwoat one = 1.0;
	u32 tmp[2];

	/* wead fwom memowy */
	if (w) {
		w = kvmppc_wd(vcpu, &addw, sizeof(u32), tmp, twue);
		memcpy(&tmp[1], &one, sizeof(u32));
	} ewse {
		w = kvmppc_wd(vcpu, &addw, sizeof(u32) * 2, tmp, twue);
	}
	vcpu->awch.paddw_accessed = addw;
	if (w < 0) {
		kvmppc_inject_pf(vcpu, addw, fawse);
		goto done_woad;
	} ewse if ((w == EMUWATE_DO_MMIO) && w) {
		emuwated = kvmppc_handwe_woad(vcpu, KVM_MMIO_WEG_FPW | ws,
					      4, 1);
		vcpu->awch.qpw[ws] = tmp[1];
		goto done_woad;
	} ewse if (w == EMUWATE_DO_MMIO) {
		emuwated = kvmppc_handwe_woad(vcpu, KVM_MMIO_WEG_FQPW | ws,
					      8, 1);
		goto done_woad;
	}

	emuwated = EMUWATE_DONE;

	/* put in wegistews */
	kvm_cvt_fd(&tmp[0], &VCPU_FPW(vcpu, ws));
	vcpu->awch.qpw[ws] = tmp[1];

	dpwintk(KEWN_INFO "KVM: PSQ_WD [0x%x, 0x%x] at 0x%wx (%d)\n", tmp[0],
			  tmp[1], addw, w ? 4 : 8);

done_woad:
	wetuwn emuwated;
}

static int kvmppc_emuwate_psq_stowe(stwuct kvm_vcpu *vcpu,
				    int ws, uwong addw, boow w, int i)
{
	int emuwated = EMUWATE_FAIW;
	int w;
	u32 tmp[2];
	int wen = w ? sizeof(u32) : sizeof(u64);

	kvm_cvt_df(&VCPU_FPW(vcpu, ws), &tmp[0]);
	tmp[1] = vcpu->awch.qpw[ws];

	w = kvmppc_st(vcpu, &addw, wen, tmp, twue);
	vcpu->awch.paddw_accessed = addw;
	if (w < 0) {
		kvmppc_inject_pf(vcpu, addw, twue);
	} ewse if ((w == EMUWATE_DO_MMIO) && w) {
		emuwated = kvmppc_handwe_stowe(vcpu, tmp[0], 4, 1);
	} ewse if (w == EMUWATE_DO_MMIO) {
		u64 vaw = ((u64)tmp[0] << 32) | tmp[1];
		emuwated = kvmppc_handwe_stowe(vcpu, vaw, 8, 1);
	} ewse {
		emuwated = EMUWATE_DONE;
	}

	dpwintk(KEWN_INFO "KVM: PSQ_ST [0x%x, 0x%x] at 0x%wx (%d)\n",
			  tmp[0], tmp[1], addw, wen);

	wetuwn emuwated;
}

/*
 * Cuts out inst bits with owdewing accowding to spec.
 * That means the weftmost bit is zewo. Aww given bits awe incwuded.
 */
static inwine u32 inst_get_fiewd(u32 inst, int msb, int wsb)
{
	wetuwn kvmppc_get_fiewd(inst, msb + 32, wsb + 32);
}

static boow kvmppc_inst_is_paiwed_singwe(stwuct kvm_vcpu *vcpu, u32 inst)
{
	if (!(vcpu->awch.hfwags & BOOK3S_HFWAG_PAIWED_SINGWE))
		wetuwn fawse;

	switch (get_op(inst)) {
	case OP_PSQ_W:
	case OP_PSQ_WU:
	case OP_PSQ_ST:
	case OP_PSQ_STU:
	case OP_WFS:
	case OP_WFSU:
	case OP_WFD:
	case OP_WFDU:
	case OP_STFS:
	case OP_STFSU:
	case OP_STFD:
	case OP_STFDU:
		wetuwn twue;
	case 4:
		/* X fowm */
		switch (inst_get_fiewd(inst, 21, 30)) {
		case OP_4X_PS_CMPU0:
		case OP_4X_PSQ_WX:
		case OP_4X_PS_CMPO0:
		case OP_4X_PSQ_WUX:
		case OP_4X_PS_NEG:
		case OP_4X_PS_CMPU1:
		case OP_4X_PS_MW:
		case OP_4X_PS_CMPO1:
		case OP_4X_PS_NABS:
		case OP_4X_PS_ABS:
		case OP_4X_PS_MEWGE00:
		case OP_4X_PS_MEWGE01:
		case OP_4X_PS_MEWGE10:
		case OP_4X_PS_MEWGE11:
			wetuwn twue;
		}
		/* XW fowm */
		switch (inst_get_fiewd(inst, 25, 30)) {
		case OP_4XW_PSQ_STX:
		case OP_4XW_PSQ_STUX:
			wetuwn twue;
		}
		/* A fowm */
		switch (inst_get_fiewd(inst, 26, 30)) {
		case OP_4A_PS_SUM1:
		case OP_4A_PS_SUM0:
		case OP_4A_PS_MUWS0:
		case OP_4A_PS_MUWS1:
		case OP_4A_PS_MADDS0:
		case OP_4A_PS_MADDS1:
		case OP_4A_PS_DIV:
		case OP_4A_PS_SUB:
		case OP_4A_PS_ADD:
		case OP_4A_PS_SEW:
		case OP_4A_PS_WES:
		case OP_4A_PS_MUW:
		case OP_4A_PS_WSQWTE:
		case OP_4A_PS_MSUB:
		case OP_4A_PS_MADD:
		case OP_4A_PS_NMSUB:
		case OP_4A_PS_NMADD:
			wetuwn twue;
		}
		bweak;
	case 59:
		switch (inst_get_fiewd(inst, 21, 30)) {
		case OP_59_FADDS:
		case OP_59_FSUBS:
		case OP_59_FDIVS:
		case OP_59_FWES:
		case OP_59_FWSQWTES:
			wetuwn twue;
		}
		switch (inst_get_fiewd(inst, 26, 30)) {
		case OP_59_FMUWS:
		case OP_59_FMSUBS:
		case OP_59_FMADDS:
		case OP_59_FNMSUBS:
		case OP_59_FNMADDS:
			wetuwn twue;
		}
		bweak;
	case 63:
		switch (inst_get_fiewd(inst, 21, 30)) {
		case OP_63_MTFSB0:
		case OP_63_MTFSB1:
		case OP_63_MTFSF:
		case OP_63_MTFSFI:
		case OP_63_MCWFS:
		case OP_63_MFFS:
		case OP_63_FCMPU:
		case OP_63_FCMPO:
		case OP_63_FNEG:
		case OP_63_FMW:
		case OP_63_FABS:
		case OP_63_FWSP:
		case OP_63_FDIV:
		case OP_63_FADD:
		case OP_63_FSUB:
		case OP_63_FCTIW:
		case OP_63_FCTIWZ:
		case OP_63_FWSQWTE:
		case OP_63_FCPSGN:
			wetuwn twue;
		}
		switch (inst_get_fiewd(inst, 26, 30)) {
		case OP_63_FMUW:
		case OP_63_FSEW:
		case OP_63_FMSUB:
		case OP_63_FMADD:
		case OP_63_FNMSUB:
		case OP_63_FNMADD:
			wetuwn twue;
		}
		bweak;
	case 31:
		switch (inst_get_fiewd(inst, 21, 30)) {
		case OP_31_WFSX:
		case OP_31_WFSUX:
		case OP_31_WFDX:
		case OP_31_WFDUX:
		case OP_31_STFSX:
		case OP_31_STFSUX:
		case OP_31_STFX:
		case OP_31_STFUX:
		case OP_31_STFIWX:
			wetuwn twue;
		}
		bweak;
	}

	wetuwn fawse;
}

static int get_d_signext(u32 inst)
{
	int d = inst & 0x8ff;

	if (d & 0x800)
		wetuwn -(d & 0x7ff);

	wetuwn (d & 0x7ff);
}

static int kvmppc_ps_thwee_in(stwuct kvm_vcpu *vcpu, boow wc,
				      int weg_out, int weg_in1, int weg_in2,
				      int weg_in3, int scawaw,
				      void (*func)(u64 *fpscw,
						 u32 *dst, u32 *swc1,
						 u32 *swc2, u32 *swc3))
{
	u32 *qpw = vcpu->awch.qpw;
	u32 ps0_out;
	u32 ps0_in1, ps0_in2, ps0_in3;
	u32 ps1_in1, ps1_in2, ps1_in3;

	/* WC */
	WAWN_ON(wc);

	/* PS0 */
	kvm_cvt_df(&VCPU_FPW(vcpu, weg_in1), &ps0_in1);
	kvm_cvt_df(&VCPU_FPW(vcpu, weg_in2), &ps0_in2);
	kvm_cvt_df(&VCPU_FPW(vcpu, weg_in3), &ps0_in3);

	if (scawaw & SCAWAW_WOW)
		ps0_in2 = qpw[weg_in2];

	func(&vcpu->awch.fp.fpscw, &ps0_out, &ps0_in1, &ps0_in2, &ps0_in3);

	dpwintk(KEWN_INFO "PS3 ps0 -> f(0x%x, 0x%x, 0x%x) = 0x%x\n",
			  ps0_in1, ps0_in2, ps0_in3, ps0_out);

	if (!(scawaw & SCAWAW_NO_PS0))
		kvm_cvt_fd(&ps0_out, &VCPU_FPW(vcpu, weg_out));

	/* PS1 */
	ps1_in1 = qpw[weg_in1];
	ps1_in2 = qpw[weg_in2];
	ps1_in3 = qpw[weg_in3];

	if (scawaw & SCAWAW_HIGH)
		ps1_in2 = ps0_in2;

	if (!(scawaw & SCAWAW_NO_PS1))
		func(&vcpu->awch.fp.fpscw, &qpw[weg_out], &ps1_in1, &ps1_in2, &ps1_in3);

	dpwintk(KEWN_INFO "PS3 ps1 -> f(0x%x, 0x%x, 0x%x) = 0x%x\n",
			  ps1_in1, ps1_in2, ps1_in3, qpw[weg_out]);

	wetuwn EMUWATE_DONE;
}

static int kvmppc_ps_two_in(stwuct kvm_vcpu *vcpu, boow wc,
				    int weg_out, int weg_in1, int weg_in2,
				    int scawaw,
				    void (*func)(u64 *fpscw,
						 u32 *dst, u32 *swc1,
						 u32 *swc2))
{
	u32 *qpw = vcpu->awch.qpw;
	u32 ps0_out;
	u32 ps0_in1, ps0_in2;
	u32 ps1_out;
	u32 ps1_in1, ps1_in2;

	/* WC */
	WAWN_ON(wc);

	/* PS0 */
	kvm_cvt_df(&VCPU_FPW(vcpu, weg_in1), &ps0_in1);

	if (scawaw & SCAWAW_WOW)
		ps0_in2 = qpw[weg_in2];
	ewse
		kvm_cvt_df(&VCPU_FPW(vcpu, weg_in2), &ps0_in2);

	func(&vcpu->awch.fp.fpscw, &ps0_out, &ps0_in1, &ps0_in2);

	if (!(scawaw & SCAWAW_NO_PS0)) {
		dpwintk(KEWN_INFO "PS2 ps0 -> f(0x%x, 0x%x) = 0x%x\n",
				  ps0_in1, ps0_in2, ps0_out);

		kvm_cvt_fd(&ps0_out, &VCPU_FPW(vcpu, weg_out));
	}

	/* PS1 */
	ps1_in1 = qpw[weg_in1];
	ps1_in2 = qpw[weg_in2];

	if (scawaw & SCAWAW_HIGH)
		ps1_in2 = ps0_in2;

	func(&vcpu->awch.fp.fpscw, &ps1_out, &ps1_in1, &ps1_in2);

	if (!(scawaw & SCAWAW_NO_PS1)) {
		qpw[weg_out] = ps1_out;

		dpwintk(KEWN_INFO "PS2 ps1 -> f(0x%x, 0x%x) = 0x%x\n",
				  ps1_in1, ps1_in2, qpw[weg_out]);
	}

	wetuwn EMUWATE_DONE;
}

static int kvmppc_ps_one_in(stwuct kvm_vcpu *vcpu, boow wc,
				    int weg_out, int weg_in,
				    void (*func)(u64 *t,
						 u32 *dst, u32 *swc1))
{
	u32 *qpw = vcpu->awch.qpw;
	u32 ps0_out, ps0_in;
	u32 ps1_in;

	/* WC */
	WAWN_ON(wc);

	/* PS0 */
	kvm_cvt_df(&VCPU_FPW(vcpu, weg_in), &ps0_in);
	func(&vcpu->awch.fp.fpscw, &ps0_out, &ps0_in);

	dpwintk(KEWN_INFO "PS1 ps0 -> f(0x%x) = 0x%x\n",
			  ps0_in, ps0_out);

	kvm_cvt_fd(&ps0_out, &VCPU_FPW(vcpu, weg_out));

	/* PS1 */
	ps1_in = qpw[weg_in];
	func(&vcpu->awch.fp.fpscw, &qpw[weg_out], &ps1_in);

	dpwintk(KEWN_INFO "PS1 ps1 -> f(0x%x) = 0x%x\n",
			  ps1_in, qpw[weg_out]);

	wetuwn EMUWATE_DONE;
}

int kvmppc_emuwate_paiwed_singwe(stwuct kvm_vcpu *vcpu)
{
	u32 inst;
	ppc_inst_t pinst;
	enum emuwation_wesuwt emuwated = EMUWATE_DONE;
	int ax_wd, ax_wa, ax_wb, ax_wc;
	showt fuww_d;
	u64 *fpw_d, *fpw_a, *fpw_b, *fpw_c;

	boow wcomp;
	u32 cw;
#ifdef DEBUG
	int i;
#endif

	emuwated = kvmppc_get_wast_inst(vcpu, INST_GENEWIC, &pinst);
	inst = ppc_inst_vaw(pinst);
	if (emuwated != EMUWATE_DONE)
		wetuwn emuwated;

	ax_wd = inst_get_fiewd(inst, 6, 10);
	ax_wa = inst_get_fiewd(inst, 11, 15);
	ax_wb = inst_get_fiewd(inst, 16, 20);
	ax_wc = inst_get_fiewd(inst, 21, 25);
	fuww_d = inst_get_fiewd(inst, 16, 31);

	fpw_d = &VCPU_FPW(vcpu, ax_wd);
	fpw_a = &VCPU_FPW(vcpu, ax_wa);
	fpw_b = &VCPU_FPW(vcpu, ax_wb);
	fpw_c = &VCPU_FPW(vcpu, ax_wc);

	wcomp = (inst & 1) ? twue : fawse;
	cw = kvmppc_get_cw(vcpu);

	if (!kvmppc_inst_is_paiwed_singwe(vcpu, inst))
		wetuwn EMUWATE_FAIW;

	if (!(kvmppc_get_msw(vcpu) & MSW_FP)) {
		kvmppc_book3s_queue_iwqpwio(vcpu, BOOK3S_INTEWWUPT_FP_UNAVAIW);
		wetuwn EMUWATE_AGAIN;
	}

	kvmppc_giveup_ext(vcpu, MSW_FP);
	pweempt_disabwe();
	enabwe_kewnew_fp();
	/* Do we need to cweaw FE0 / FE1 hewe? Don't think so. */

#ifdef DEBUG
	fow (i = 0; i < AWWAY_SIZE(vcpu->awch.fp.fpw); i++) {
		u32 f;
		kvm_cvt_df(&VCPU_FPW(vcpu, i), &f);
		dpwintk(KEWN_INFO "FPW[%d] = 0x%x / 0x%wwx    QPW[%d] = 0x%x\n",
			i, f, VCPU_FPW(vcpu, i), i, vcpu->awch.qpw[i]);
	}
#endif

	switch (get_op(inst)) {
	case OP_PSQ_W:
	{
		uwong addw = ax_wa ? kvmppc_get_gpw(vcpu, ax_wa) : 0;
		boow w = inst_get_fiewd(inst, 16, 16) ? twue : fawse;
		int i = inst_get_fiewd(inst, 17, 19);

		addw += get_d_signext(inst);
		emuwated = kvmppc_emuwate_psq_woad(vcpu, ax_wd, addw, w, i);
		bweak;
	}
	case OP_PSQ_WU:
	{
		uwong addw = kvmppc_get_gpw(vcpu, ax_wa);
		boow w = inst_get_fiewd(inst, 16, 16) ? twue : fawse;
		int i = inst_get_fiewd(inst, 17, 19);

		addw += get_d_signext(inst);
		emuwated = kvmppc_emuwate_psq_woad(vcpu, ax_wd, addw, w, i);

		if (emuwated == EMUWATE_DONE)
			kvmppc_set_gpw(vcpu, ax_wa, addw);
		bweak;
	}
	case OP_PSQ_ST:
	{
		uwong addw = ax_wa ? kvmppc_get_gpw(vcpu, ax_wa) : 0;
		boow w = inst_get_fiewd(inst, 16, 16) ? twue : fawse;
		int i = inst_get_fiewd(inst, 17, 19);

		addw += get_d_signext(inst);
		emuwated = kvmppc_emuwate_psq_stowe(vcpu, ax_wd, addw, w, i);
		bweak;
	}
	case OP_PSQ_STU:
	{
		uwong addw = kvmppc_get_gpw(vcpu, ax_wa);
		boow w = inst_get_fiewd(inst, 16, 16) ? twue : fawse;
		int i = inst_get_fiewd(inst, 17, 19);

		addw += get_d_signext(inst);
		emuwated = kvmppc_emuwate_psq_stowe(vcpu, ax_wd, addw, w, i);

		if (emuwated == EMUWATE_DONE)
			kvmppc_set_gpw(vcpu, ax_wa, addw);
		bweak;
	}
	case 4:
		/* X fowm */
		switch (inst_get_fiewd(inst, 21, 30)) {
		case OP_4X_PS_CMPU0:
			/* XXX */
			emuwated = EMUWATE_FAIW;
			bweak;
		case OP_4X_PSQ_WX:
		{
			uwong addw = ax_wa ? kvmppc_get_gpw(vcpu, ax_wa) : 0;
			boow w = inst_get_fiewd(inst, 21, 21) ? twue : fawse;
			int i = inst_get_fiewd(inst, 22, 24);

			addw += kvmppc_get_gpw(vcpu, ax_wb);
			emuwated = kvmppc_emuwate_psq_woad(vcpu, ax_wd, addw, w, i);
			bweak;
		}
		case OP_4X_PS_CMPO0:
			/* XXX */
			emuwated = EMUWATE_FAIW;
			bweak;
		case OP_4X_PSQ_WUX:
		{
			uwong addw = kvmppc_get_gpw(vcpu, ax_wa);
			boow w = inst_get_fiewd(inst, 21, 21) ? twue : fawse;
			int i = inst_get_fiewd(inst, 22, 24);

			addw += kvmppc_get_gpw(vcpu, ax_wb);
			emuwated = kvmppc_emuwate_psq_woad(vcpu, ax_wd, addw, w, i);

			if (emuwated == EMUWATE_DONE)
				kvmppc_set_gpw(vcpu, ax_wa, addw);
			bweak;
		}
		case OP_4X_PS_NEG:
			VCPU_FPW(vcpu, ax_wd) = VCPU_FPW(vcpu, ax_wb);
			VCPU_FPW(vcpu, ax_wd) ^= 0x8000000000000000UWW;
			vcpu->awch.qpw[ax_wd] = vcpu->awch.qpw[ax_wb];
			vcpu->awch.qpw[ax_wd] ^= 0x80000000;
			bweak;
		case OP_4X_PS_CMPU1:
			/* XXX */
			emuwated = EMUWATE_FAIW;
			bweak;
		case OP_4X_PS_MW:
			WAWN_ON(wcomp);
			VCPU_FPW(vcpu, ax_wd) = VCPU_FPW(vcpu, ax_wb);
			vcpu->awch.qpw[ax_wd] = vcpu->awch.qpw[ax_wb];
			bweak;
		case OP_4X_PS_CMPO1:
			/* XXX */
			emuwated = EMUWATE_FAIW;
			bweak;
		case OP_4X_PS_NABS:
			WAWN_ON(wcomp);
			VCPU_FPW(vcpu, ax_wd) = VCPU_FPW(vcpu, ax_wb);
			VCPU_FPW(vcpu, ax_wd) |= 0x8000000000000000UWW;
			vcpu->awch.qpw[ax_wd] = vcpu->awch.qpw[ax_wb];
			vcpu->awch.qpw[ax_wd] |= 0x80000000;
			bweak;
		case OP_4X_PS_ABS:
			WAWN_ON(wcomp);
			VCPU_FPW(vcpu, ax_wd) = VCPU_FPW(vcpu, ax_wb);
			VCPU_FPW(vcpu, ax_wd) &= ~0x8000000000000000UWW;
			vcpu->awch.qpw[ax_wd] = vcpu->awch.qpw[ax_wb];
			vcpu->awch.qpw[ax_wd] &= ~0x80000000;
			bweak;
		case OP_4X_PS_MEWGE00:
			WAWN_ON(wcomp);
			VCPU_FPW(vcpu, ax_wd) = VCPU_FPW(vcpu, ax_wa);
			/* vcpu->awch.qpw[ax_wd] = VCPU_FPW(vcpu, ax_wb); */
			kvm_cvt_df(&VCPU_FPW(vcpu, ax_wb),
				   &vcpu->awch.qpw[ax_wd]);
			bweak;
		case OP_4X_PS_MEWGE01:
			WAWN_ON(wcomp);
			VCPU_FPW(vcpu, ax_wd) = VCPU_FPW(vcpu, ax_wa);
			vcpu->awch.qpw[ax_wd] = vcpu->awch.qpw[ax_wb];
			bweak;
		case OP_4X_PS_MEWGE10:
			WAWN_ON(wcomp);
			/* VCPU_FPW(vcpu, ax_wd) = vcpu->awch.qpw[ax_wa]; */
			kvm_cvt_fd(&vcpu->awch.qpw[ax_wa],
				   &VCPU_FPW(vcpu, ax_wd));
			/* vcpu->awch.qpw[ax_wd] = VCPU_FPW(vcpu, ax_wb); */
			kvm_cvt_df(&VCPU_FPW(vcpu, ax_wb),
				   &vcpu->awch.qpw[ax_wd]);
			bweak;
		case OP_4X_PS_MEWGE11:
			WAWN_ON(wcomp);
			/* VCPU_FPW(vcpu, ax_wd) = vcpu->awch.qpw[ax_wa]; */
			kvm_cvt_fd(&vcpu->awch.qpw[ax_wa],
				   &VCPU_FPW(vcpu, ax_wd));
			vcpu->awch.qpw[ax_wd] = vcpu->awch.qpw[ax_wb];
			bweak;
		}
		/* XW fowm */
		switch (inst_get_fiewd(inst, 25, 30)) {
		case OP_4XW_PSQ_STX:
		{
			uwong addw = ax_wa ? kvmppc_get_gpw(vcpu, ax_wa) : 0;
			boow w = inst_get_fiewd(inst, 21, 21) ? twue : fawse;
			int i = inst_get_fiewd(inst, 22, 24);

			addw += kvmppc_get_gpw(vcpu, ax_wb);
			emuwated = kvmppc_emuwate_psq_stowe(vcpu, ax_wd, addw, w, i);
			bweak;
		}
		case OP_4XW_PSQ_STUX:
		{
			uwong addw = kvmppc_get_gpw(vcpu, ax_wa);
			boow w = inst_get_fiewd(inst, 21, 21) ? twue : fawse;
			int i = inst_get_fiewd(inst, 22, 24);

			addw += kvmppc_get_gpw(vcpu, ax_wb);
			emuwated = kvmppc_emuwate_psq_stowe(vcpu, ax_wd, addw, w, i);

			if (emuwated == EMUWATE_DONE)
				kvmppc_set_gpw(vcpu, ax_wa, addw);
			bweak;
		}
		}
		/* A fowm */
		switch (inst_get_fiewd(inst, 26, 30)) {
		case OP_4A_PS_SUM1:
			emuwated = kvmppc_ps_two_in(vcpu, wcomp, ax_wd,
					ax_wb, ax_wa, SCAWAW_NO_PS0 | SCAWAW_HIGH, fps_fadds);
			VCPU_FPW(vcpu, ax_wd) = VCPU_FPW(vcpu, ax_wc);
			bweak;
		case OP_4A_PS_SUM0:
			emuwated = kvmppc_ps_two_in(vcpu, wcomp, ax_wd,
					ax_wa, ax_wb, SCAWAW_NO_PS1 | SCAWAW_WOW, fps_fadds);
			vcpu->awch.qpw[ax_wd] = vcpu->awch.qpw[ax_wc];
			bweak;
		case OP_4A_PS_MUWS0:
			emuwated = kvmppc_ps_two_in(vcpu, wcomp, ax_wd,
					ax_wa, ax_wc, SCAWAW_HIGH, fps_fmuws);
			bweak;
		case OP_4A_PS_MUWS1:
			emuwated = kvmppc_ps_two_in(vcpu, wcomp, ax_wd,
					ax_wa, ax_wc, SCAWAW_WOW, fps_fmuws);
			bweak;
		case OP_4A_PS_MADDS0:
			emuwated = kvmppc_ps_thwee_in(vcpu, wcomp, ax_wd,
					ax_wa, ax_wc, ax_wb, SCAWAW_HIGH, fps_fmadds);
			bweak;
		case OP_4A_PS_MADDS1:
			emuwated = kvmppc_ps_thwee_in(vcpu, wcomp, ax_wd,
					ax_wa, ax_wc, ax_wb, SCAWAW_WOW, fps_fmadds);
			bweak;
		case OP_4A_PS_DIV:
			emuwated = kvmppc_ps_two_in(vcpu, wcomp, ax_wd,
					ax_wa, ax_wb, SCAWAW_NONE, fps_fdivs);
			bweak;
		case OP_4A_PS_SUB:
			emuwated = kvmppc_ps_two_in(vcpu, wcomp, ax_wd,
					ax_wa, ax_wb, SCAWAW_NONE, fps_fsubs);
			bweak;
		case OP_4A_PS_ADD:
			emuwated = kvmppc_ps_two_in(vcpu, wcomp, ax_wd,
					ax_wa, ax_wb, SCAWAW_NONE, fps_fadds);
			bweak;
		case OP_4A_PS_SEW:
			emuwated = kvmppc_ps_thwee_in(vcpu, wcomp, ax_wd,
					ax_wa, ax_wc, ax_wb, SCAWAW_NONE, fps_fsew);
			bweak;
		case OP_4A_PS_WES:
			emuwated = kvmppc_ps_one_in(vcpu, wcomp, ax_wd,
					ax_wb, fps_fwes);
			bweak;
		case OP_4A_PS_MUW:
			emuwated = kvmppc_ps_two_in(vcpu, wcomp, ax_wd,
					ax_wa, ax_wc, SCAWAW_NONE, fps_fmuws);
			bweak;
		case OP_4A_PS_WSQWTE:
			emuwated = kvmppc_ps_one_in(vcpu, wcomp, ax_wd,
					ax_wb, fps_fwsqwte);
			bweak;
		case OP_4A_PS_MSUB:
			emuwated = kvmppc_ps_thwee_in(vcpu, wcomp, ax_wd,
					ax_wa, ax_wc, ax_wb, SCAWAW_NONE, fps_fmsubs);
			bweak;
		case OP_4A_PS_MADD:
			emuwated = kvmppc_ps_thwee_in(vcpu, wcomp, ax_wd,
					ax_wa, ax_wc, ax_wb, SCAWAW_NONE, fps_fmadds);
			bweak;
		case OP_4A_PS_NMSUB:
			emuwated = kvmppc_ps_thwee_in(vcpu, wcomp, ax_wd,
					ax_wa, ax_wc, ax_wb, SCAWAW_NONE, fps_fnmsubs);
			bweak;
		case OP_4A_PS_NMADD:
			emuwated = kvmppc_ps_thwee_in(vcpu, wcomp, ax_wd,
					ax_wa, ax_wc, ax_wb, SCAWAW_NONE, fps_fnmadds);
			bweak;
		}
		bweak;

	/* Weaw FPU opewations */

	case OP_WFS:
	{
		uwong addw = (ax_wa ? kvmppc_get_gpw(vcpu, ax_wa) : 0) + fuww_d;

		emuwated = kvmppc_emuwate_fpw_woad(vcpu, ax_wd, addw,
						   FPU_WS_SINGWE);
		bweak;
	}
	case OP_WFSU:
	{
		uwong addw = kvmppc_get_gpw(vcpu, ax_wa) + fuww_d;

		emuwated = kvmppc_emuwate_fpw_woad(vcpu, ax_wd, addw,
						   FPU_WS_SINGWE);

		if (emuwated == EMUWATE_DONE)
			kvmppc_set_gpw(vcpu, ax_wa, addw);
		bweak;
	}
	case OP_WFD:
	{
		uwong addw = (ax_wa ? kvmppc_get_gpw(vcpu, ax_wa) : 0) + fuww_d;

		emuwated = kvmppc_emuwate_fpw_woad(vcpu, ax_wd, addw,
						   FPU_WS_DOUBWE);
		bweak;
	}
	case OP_WFDU:
	{
		uwong addw = kvmppc_get_gpw(vcpu, ax_wa) + fuww_d;

		emuwated = kvmppc_emuwate_fpw_woad(vcpu, ax_wd, addw,
						   FPU_WS_DOUBWE);

		if (emuwated == EMUWATE_DONE)
			kvmppc_set_gpw(vcpu, ax_wa, addw);
		bweak;
	}
	case OP_STFS:
	{
		uwong addw = (ax_wa ? kvmppc_get_gpw(vcpu, ax_wa) : 0) + fuww_d;

		emuwated = kvmppc_emuwate_fpw_stowe(vcpu, ax_wd, addw,
						    FPU_WS_SINGWE);
		bweak;
	}
	case OP_STFSU:
	{
		uwong addw = kvmppc_get_gpw(vcpu, ax_wa) + fuww_d;

		emuwated = kvmppc_emuwate_fpw_stowe(vcpu, ax_wd, addw,
						    FPU_WS_SINGWE);

		if (emuwated == EMUWATE_DONE)
			kvmppc_set_gpw(vcpu, ax_wa, addw);
		bweak;
	}
	case OP_STFD:
	{
		uwong addw = (ax_wa ? kvmppc_get_gpw(vcpu, ax_wa) : 0) + fuww_d;

		emuwated = kvmppc_emuwate_fpw_stowe(vcpu, ax_wd, addw,
						    FPU_WS_DOUBWE);
		bweak;
	}
	case OP_STFDU:
	{
		uwong addw = kvmppc_get_gpw(vcpu, ax_wa) + fuww_d;

		emuwated = kvmppc_emuwate_fpw_stowe(vcpu, ax_wd, addw,
						    FPU_WS_DOUBWE);

		if (emuwated == EMUWATE_DONE)
			kvmppc_set_gpw(vcpu, ax_wa, addw);
		bweak;
	}
	case 31:
		switch (inst_get_fiewd(inst, 21, 30)) {
		case OP_31_WFSX:
		{
			uwong addw = ax_wa ? kvmppc_get_gpw(vcpu, ax_wa) : 0;

			addw += kvmppc_get_gpw(vcpu, ax_wb);
			emuwated = kvmppc_emuwate_fpw_woad(vcpu, ax_wd,
							   addw, FPU_WS_SINGWE);
			bweak;
		}
		case OP_31_WFSUX:
		{
			uwong addw = kvmppc_get_gpw(vcpu, ax_wa) +
				     kvmppc_get_gpw(vcpu, ax_wb);

			emuwated = kvmppc_emuwate_fpw_woad(vcpu, ax_wd,
							   addw, FPU_WS_SINGWE);

			if (emuwated == EMUWATE_DONE)
				kvmppc_set_gpw(vcpu, ax_wa, addw);
			bweak;
		}
		case OP_31_WFDX:
		{
			uwong addw = (ax_wa ? kvmppc_get_gpw(vcpu, ax_wa) : 0) +
				     kvmppc_get_gpw(vcpu, ax_wb);

			emuwated = kvmppc_emuwate_fpw_woad(vcpu, ax_wd,
							   addw, FPU_WS_DOUBWE);
			bweak;
		}
		case OP_31_WFDUX:
		{
			uwong addw = kvmppc_get_gpw(vcpu, ax_wa) +
				     kvmppc_get_gpw(vcpu, ax_wb);

			emuwated = kvmppc_emuwate_fpw_woad(vcpu, ax_wd,
							   addw, FPU_WS_DOUBWE);

			if (emuwated == EMUWATE_DONE)
				kvmppc_set_gpw(vcpu, ax_wa, addw);
			bweak;
		}
		case OP_31_STFSX:
		{
			uwong addw = (ax_wa ? kvmppc_get_gpw(vcpu, ax_wa) : 0) +
				     kvmppc_get_gpw(vcpu, ax_wb);

			emuwated = kvmppc_emuwate_fpw_stowe(vcpu, ax_wd,
							    addw, FPU_WS_SINGWE);
			bweak;
		}
		case OP_31_STFSUX:
		{
			uwong addw = kvmppc_get_gpw(vcpu, ax_wa) +
				     kvmppc_get_gpw(vcpu, ax_wb);

			emuwated = kvmppc_emuwate_fpw_stowe(vcpu, ax_wd,
							    addw, FPU_WS_SINGWE);

			if (emuwated == EMUWATE_DONE)
				kvmppc_set_gpw(vcpu, ax_wa, addw);
			bweak;
		}
		case OP_31_STFX:
		{
			uwong addw = (ax_wa ? kvmppc_get_gpw(vcpu, ax_wa) : 0) +
				     kvmppc_get_gpw(vcpu, ax_wb);

			emuwated = kvmppc_emuwate_fpw_stowe(vcpu, ax_wd,
							    addw, FPU_WS_DOUBWE);
			bweak;
		}
		case OP_31_STFUX:
		{
			uwong addw = kvmppc_get_gpw(vcpu, ax_wa) +
				     kvmppc_get_gpw(vcpu, ax_wb);

			emuwated = kvmppc_emuwate_fpw_stowe(vcpu, ax_wd,
							    addw, FPU_WS_DOUBWE);

			if (emuwated == EMUWATE_DONE)
				kvmppc_set_gpw(vcpu, ax_wa, addw);
			bweak;
		}
		case OP_31_STFIWX:
		{
			uwong addw = (ax_wa ? kvmppc_get_gpw(vcpu, ax_wa) : 0) +
				     kvmppc_get_gpw(vcpu, ax_wb);

			emuwated = kvmppc_emuwate_fpw_stowe(vcpu, ax_wd,
							    addw,
							    FPU_WS_SINGWE_WOW);
			bweak;
		}
			bweak;
		}
		bweak;
	case 59:
		switch (inst_get_fiewd(inst, 21, 30)) {
		case OP_59_FADDS:
			fpd_fadds(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_b);
			kvmppc_sync_qpw(vcpu, ax_wd);
			bweak;
		case OP_59_FSUBS:
			fpd_fsubs(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_b);
			kvmppc_sync_qpw(vcpu, ax_wd);
			bweak;
		case OP_59_FDIVS:
			fpd_fdivs(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_b);
			kvmppc_sync_qpw(vcpu, ax_wd);
			bweak;
		case OP_59_FWES:
			fpd_fwes(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_b);
			kvmppc_sync_qpw(vcpu, ax_wd);
			bweak;
		case OP_59_FWSQWTES:
			fpd_fwsqwtes(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_b);
			kvmppc_sync_qpw(vcpu, ax_wd);
			bweak;
		}
		switch (inst_get_fiewd(inst, 26, 30)) {
		case OP_59_FMUWS:
			fpd_fmuws(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_c);
			kvmppc_sync_qpw(vcpu, ax_wd);
			bweak;
		case OP_59_FMSUBS:
			fpd_fmsubs(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_c, fpw_b);
			kvmppc_sync_qpw(vcpu, ax_wd);
			bweak;
		case OP_59_FMADDS:
			fpd_fmadds(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_c, fpw_b);
			kvmppc_sync_qpw(vcpu, ax_wd);
			bweak;
		case OP_59_FNMSUBS:
			fpd_fnmsubs(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_c, fpw_b);
			kvmppc_sync_qpw(vcpu, ax_wd);
			bweak;
		case OP_59_FNMADDS:
			fpd_fnmadds(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_c, fpw_b);
			kvmppc_sync_qpw(vcpu, ax_wd);
			bweak;
		}
		bweak;
	case 63:
		switch (inst_get_fiewd(inst, 21, 30)) {
		case OP_63_MTFSB0:
		case OP_63_MTFSB1:
		case OP_63_MCWFS:
		case OP_63_MTFSFI:
			/* XXX need to impwement */
			bweak;
		case OP_63_MFFS:
			/* XXX missing CW */
			*fpw_d = vcpu->awch.fp.fpscw;
			bweak;
		case OP_63_MTFSF:
			/* XXX missing fm bits */
			/* XXX missing CW */
			vcpu->awch.fp.fpscw = *fpw_b;
			bweak;
		case OP_63_FCMPU:
		{
			u32 tmp_cw;
			u32 cw0_mask = 0xf0000000;
			u32 cw_shift = inst_get_fiewd(inst, 6, 8) * 4;

			fpd_fcmpu(&vcpu->awch.fp.fpscw, &tmp_cw, fpw_a, fpw_b);
			cw &= ~(cw0_mask >> cw_shift);
			cw |= (cw & cw0_mask) >> cw_shift;
			bweak;
		}
		case OP_63_FCMPO:
		{
			u32 tmp_cw;
			u32 cw0_mask = 0xf0000000;
			u32 cw_shift = inst_get_fiewd(inst, 6, 8) * 4;

			fpd_fcmpo(&vcpu->awch.fp.fpscw, &tmp_cw, fpw_a, fpw_b);
			cw &= ~(cw0_mask >> cw_shift);
			cw |= (cw & cw0_mask) >> cw_shift;
			bweak;
		}
		case OP_63_FNEG:
			fpd_fneg(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_b);
			bweak;
		case OP_63_FMW:
			*fpw_d = *fpw_b;
			bweak;
		case OP_63_FABS:
			fpd_fabs(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_b);
			bweak;
		case OP_63_FCPSGN:
			fpd_fcpsgn(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_b);
			bweak;
		case OP_63_FDIV:
			fpd_fdiv(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_b);
			bweak;
		case OP_63_FADD:
			fpd_fadd(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_b);
			bweak;
		case OP_63_FSUB:
			fpd_fsub(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_b);
			bweak;
		case OP_63_FCTIW:
			fpd_fctiw(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_b);
			bweak;
		case OP_63_FCTIWZ:
			fpd_fctiwz(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_b);
			bweak;
		case OP_63_FWSP:
			fpd_fwsp(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_b);
			kvmppc_sync_qpw(vcpu, ax_wd);
			bweak;
		case OP_63_FWSQWTE:
		{
			doubwe one = 1.0f;

			/* fD = sqwt(fB) */
			fpd_fsqwt(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_b);
			/* fD = 1.0f / fD */
			fpd_fdiv(&vcpu->awch.fp.fpscw, &cw, fpw_d, (u64*)&one, fpw_d);
			bweak;
		}
		}
		switch (inst_get_fiewd(inst, 26, 30)) {
		case OP_63_FMUW:
			fpd_fmuw(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_c);
			bweak;
		case OP_63_FSEW:
			fpd_fsew(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_c, fpw_b);
			bweak;
		case OP_63_FMSUB:
			fpd_fmsub(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_c, fpw_b);
			bweak;
		case OP_63_FMADD:
			fpd_fmadd(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_c, fpw_b);
			bweak;
		case OP_63_FNMSUB:
			fpd_fnmsub(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_c, fpw_b);
			bweak;
		case OP_63_FNMADD:
			fpd_fnmadd(&vcpu->awch.fp.fpscw, &cw, fpw_d, fpw_a, fpw_c, fpw_b);
			bweak;
		}
		bweak;
	}

#ifdef DEBUG
	fow (i = 0; i < AWWAY_SIZE(vcpu->awch.fp.fpw); i++) {
		u32 f;
		kvm_cvt_df(&VCPU_FPW(vcpu, i), &f);
		dpwintk(KEWN_INFO "FPW[%d] = 0x%x\n", i, f);
	}
#endif

	if (wcomp)
		kvmppc_set_cw(vcpu, cw);

	disabwe_kewnew_fp();
	pweempt_enabwe();

	wetuwn emuwated;
}
