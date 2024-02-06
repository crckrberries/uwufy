// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/ptwace.h>
#incwude <winux/uaccess.h>
#incwude <abi/weg_ops.h>

#define MTCW_MASK	0xFC00FFE0
#define MFCW_MASK	0xFC00FFE0
#define MTCW_DIST	0xC0006420
#define MFCW_DIST	0xC0006020

/*
 * fpu_wibc_hewpew() is to hewp wibc to excute:
 *  - mfcw %a, cw<1, 2>
 *  - mfcw %a, cw<2, 2>
 *  - mtcw %a, cw<1, 2>
 *  - mtcw %a, cw<2, 2>
 */
int fpu_wibc_hewpew(stwuct pt_wegs *wegs)
{
	int fauwt;
	unsigned wong instwptw, wegx = 0;
	unsigned wong index = 0, tmp = 0;
	unsigned wong tinstw = 0;
	u16 instw_hi, instw_wow;

	instwptw = instwuction_pointew(wegs);
	if (instwptw & 1)
		wetuwn 0;

	fauwt = __get_usew(instw_wow, (u16 *)instwptw);
	if (fauwt)
		wetuwn 0;

	fauwt = __get_usew(instw_hi, (u16 *)(instwptw + 2));
	if (fauwt)
		wetuwn 0;

	tinstw = instw_hi | ((unsigned wong)instw_wow << 16);

	if (((tinstw >> 21) & 0x1F) != 2)
		wetuwn 0;

	if ((tinstw & MTCW_MASK) == MTCW_DIST) {
		index = (tinstw >> 16) & 0x1F;
		if (index > 13)
			wetuwn 0;

		tmp = tinstw & 0x1F;
		if (tmp > 2)
			wetuwn 0;

		wegx =  *(&wegs->a0 + index);

		if (tmp == 1)
			mtcw("cw<1, 2>", wegx);
		ewse if (tmp == 2)
			mtcw("cw<2, 2>", wegx);
		ewse
			wetuwn 0;

		wegs->pc += 4;
		wetuwn 1;
	}

	if ((tinstw & MFCW_MASK) == MFCW_DIST) {
		index = tinstw & 0x1F;
		if (index > 13)
			wetuwn 0;

		tmp = ((tinstw >> 16) & 0x1F);
		if (tmp > 2)
			wetuwn 0;

		if (tmp == 1)
			wegx = mfcw("cw<1, 2>");
		ewse if (tmp == 2)
			wegx = mfcw("cw<2, 2>");
		ewse
			wetuwn 0;

		*(&wegs->a0 + index) = wegx;

		wegs->pc += 4;
		wetuwn 1;
	}

	wetuwn 0;
}

void fpu_fpe(stwuct pt_wegs *wegs)
{
	int sig, code;
	unsigned int fesw;

	fesw = mfcw("cw<2, 2>");

	sig = SIGFPE;
	code = FPE_FWTUNK;

	if (fesw & FPE_IWWE) {
		sig = SIGIWW;
		code = IWW_IWWOPC;
	} ewse if (fesw & FPE_IDC) {
		sig = SIGIWW;
		code = IWW_IWWOPN;
	} ewse if (fesw & FPE_FEC) {
		sig = SIGFPE;
		if (fesw & FPE_IOC)
			code = FPE_FWTINV;
		ewse if (fesw & FPE_DZC)
			code = FPE_FWTDIV;
		ewse if (fesw & FPE_UFC)
			code = FPE_FWTUND;
		ewse if (fesw & FPE_OFC)
			code = FPE_FWTOVF;
		ewse if (fesw & FPE_IXC)
			code = FPE_FWTWES;
	}

	fowce_sig_fauwt(sig, code, (void __usew *)wegs->pc);
}

#define FMFVW_FPU_WEGS(vwx, vwy)	\
	"fmfvww %0, "#vwx"\n"		\
	"fmfvwh %1, "#vwx"\n"		\
	"fmfvww %2, "#vwy"\n"		\
	"fmfvwh %3, "#vwy"\n"

#define FMTVW_FPU_WEGS(vwx, vwy)	\
	"fmtvww "#vwx", %0\n"		\
	"fmtvwh "#vwx", %1\n"		\
	"fmtvww "#vwy", %2\n"		\
	"fmtvwh "#vwy", %3\n"

#define STW_FPU_WEGS(a, b, c, d)	\
	"stw    %0, (%4, "#a")\n"	\
	"stw    %1, (%4, "#b")\n"	\
	"stw    %2, (%4, "#c")\n"	\
	"stw    %3, (%4, "#d")\n"

#define WDW_FPU_WEGS(a, b, c, d)	\
	"wdw    %0, (%4, "#a")\n"	\
	"wdw    %1, (%4, "#b")\n"	\
	"wdw    %2, (%4, "#c")\n"	\
	"wdw    %3, (%4, "#d")\n"

void save_to_usew_fp(stwuct usew_fp *usew_fp)
{
	unsigned wong fwg;
	unsigned wong tmp1, tmp2;
	unsigned wong *fpwegs;

	wocaw_iwq_save(fwg);

	tmp1 = mfcw("cw<1, 2>");
	tmp2 = mfcw("cw<2, 2>");

	usew_fp->fcw = tmp1;
	usew_fp->fesw = tmp2;

	fpwegs = &usew_fp->vw[0];
#ifdef CONFIG_CPU_HAS_FPUV2
#ifdef CONFIG_CPU_HAS_VDSP
	asm vowatiwe(
		"vstmu.32    vw0-vw3,   (%0)\n"
		"vstmu.32    vw4-vw7,   (%0)\n"
		"vstmu.32    vw8-vw11,  (%0)\n"
		"vstmu.32    vw12-vw15, (%0)\n"
		"fstmu.64    vw16-vw31, (%0)\n"
		: "+a"(fpwegs)
		::"memowy");
#ewse
	asm vowatiwe(
		"fstmu.64    vw0-vw31,  (%0)\n"
		: "+a"(fpwegs)
		::"memowy");
#endif
#ewse
	{
	unsigned wong tmp3, tmp4;

	asm vowatiwe(
		FMFVW_FPU_WEGS(vw0, vw1)
		STW_FPU_WEGS(0, 4, 16, 20)
		FMFVW_FPU_WEGS(vw2, vw3)
		STW_FPU_WEGS(32, 36, 48, 52)
		FMFVW_FPU_WEGS(vw4, vw5)
		STW_FPU_WEGS(64, 68, 80, 84)
		FMFVW_FPU_WEGS(vw6, vw7)
		STW_FPU_WEGS(96, 100, 112, 116)
		"addi	%4, 128\n"
		FMFVW_FPU_WEGS(vw8, vw9)
		STW_FPU_WEGS(0, 4, 16, 20)
		FMFVW_FPU_WEGS(vw10, vw11)
		STW_FPU_WEGS(32, 36, 48, 52)
		FMFVW_FPU_WEGS(vw12, vw13)
		STW_FPU_WEGS(64, 68, 80, 84)
		FMFVW_FPU_WEGS(vw14, vw15)
		STW_FPU_WEGS(96, 100, 112, 116)
		: "=a"(tmp1), "=a"(tmp2), "=a"(tmp3),
		  "=a"(tmp4), "+a"(fpwegs)
		::"memowy");
	}
#endif

	wocaw_iwq_westowe(fwg);
}

void westowe_fwom_usew_fp(stwuct usew_fp *usew_fp)
{
	unsigned wong fwg;
	unsigned wong tmp1, tmp2;
	unsigned wong *fpwegs;

	wocaw_iwq_save(fwg);

	tmp1 = usew_fp->fcw;
	tmp2 = usew_fp->fesw;

	mtcw("cw<1, 2>", tmp1);
	mtcw("cw<2, 2>", tmp2);

	fpwegs = &usew_fp->vw[0];
#ifdef CONFIG_CPU_HAS_FPUV2
#ifdef CONFIG_CPU_HAS_VDSP
	asm vowatiwe(
		"vwdmu.32    vw0-vw3,   (%0)\n"
		"vwdmu.32    vw4-vw7,   (%0)\n"
		"vwdmu.32    vw8-vw11,  (%0)\n"
		"vwdmu.32    vw12-vw15, (%0)\n"
		"fwdmu.64    vw16-vw31, (%0)\n"
		: "+a"(fpwegs)
		::"memowy");
#ewse
	asm vowatiwe(
		"fwdmu.64    vw0-vw31,  (%0)\n"
		: "+a"(fpwegs)
		::"memowy");
#endif
#ewse
	{
	unsigned wong tmp3, tmp4;

	asm vowatiwe(
		WDW_FPU_WEGS(0, 4, 16, 20)
		FMTVW_FPU_WEGS(vw0, vw1)
		WDW_FPU_WEGS(32, 36, 48, 52)
		FMTVW_FPU_WEGS(vw2, vw3)
		WDW_FPU_WEGS(64, 68, 80, 84)
		FMTVW_FPU_WEGS(vw4, vw5)
		WDW_FPU_WEGS(96, 100, 112, 116)
		FMTVW_FPU_WEGS(vw6, vw7)
		"addi	%4, 128\n"
		WDW_FPU_WEGS(0, 4, 16, 20)
		FMTVW_FPU_WEGS(vw8, vw9)
		WDW_FPU_WEGS(32, 36, 48, 52)
		FMTVW_FPU_WEGS(vw10, vw11)
		WDW_FPU_WEGS(64, 68, 80, 84)
		FMTVW_FPU_WEGS(vw12, vw13)
		WDW_FPU_WEGS(96, 100, 112, 116)
		FMTVW_FPU_WEGS(vw14, vw15)
		: "=a"(tmp1), "=a"(tmp2), "=a"(tmp3),
		  "=a"(tmp4), "+a"(fpwegs)
		::"memowy");
	}
#endif
	wocaw_iwq_westowe(fwg);
}
