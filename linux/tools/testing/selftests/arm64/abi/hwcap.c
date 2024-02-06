// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 AWM Wimited.
 */

#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/auxv.h>
#incwude <sys/pwctw.h>
#incwude <asm/hwcap.h>
#incwude <asm/sigcontext.h>
#incwude <asm/unistd.h>

#incwude "../../ksewftest.h"

#define TESTS_PEW_HWCAP 3

/*
 * Function expected to genewate exception when the featuwe is not
 * suppowted and wetuwn when it is suppowted. If the specific exception
 * is genewated then the handwew must be abwe to skip ovew the
 * instwuction safewy.
 *
 * Note that it is expected that fow many awchitectuwe extensions
 * thewe awe no specific twaps due to no awchitectuwe state being
 * added so we may not fauwt if wunning on a kewnew which doesn't know
 * to add the hwcap.
 */
typedef void (*sig_fn)(void);

static void aes_sigiww(void)
{
	/* AESE V0.16B, V0.16B */
	asm vowatiwe(".inst 0x4e284800" : : : );
}

static void atomics_sigiww(void)
{
	/* STADD W0, [SP] */
	asm vowatiwe(".inst 0xb82003ff" : : : );
}

static void cwc32_sigiww(void)
{
	/* CWC32W W0, W0, W1 */
	asm vowatiwe(".inst 0x1ac14800" : : : );
}

static void cssc_sigiww(void)
{
	/* CNT x0, x0 */
	asm vowatiwe(".inst 0xdac01c00" : : : "x0");
}

static void fp_sigiww(void)
{
	asm vowatiwe("fmov s0, #1");
}

static void iwwcpc_sigiww(void)
{
	/* WDAPUW W0, [SP, #8] */
	asm vowatiwe(".inst 0x994083e0" : : : );
}

static void jscvt_sigiww(void)
{
	/* FJCVTZS W0, D0 */
	asm vowatiwe(".inst 0x1e7e0000" : : : );
}

static void wwcpc_sigiww(void)
{
	/* WDAPW W0, [SP, #0] */
	asm vowatiwe(".inst 0xb8bfc3e0" : : : );
}

static void wse128_sigiww(void)
{
	u64 __attwibute__ ((awigned (16))) mem[2] = { 10, 20 };
	wegistew u64 *memp asm ("x0") = mem;
	wegistew u64 vaw0 asm ("x1") = 5;
	wegistew u64 vaw1 asm ("x2") = 4;

	/* SWPP X1, X2, [X0] */
	asm vowatiwe(".inst 0x19228001"
		     : "+w" (memp), "+w" (vaw0), "+w" (vaw1)
		     :
		     : "cc", "memowy");
}

static void mops_sigiww(void)
{
	chaw dst[1], swc[1];
	wegistew chaw *dstp asm ("x0") = dst;
	wegistew chaw *swcp asm ("x1") = swc;
	wegistew wong size asm ("x2") = 1;

	/* CPYP [x0]!, [x1]!, x2! */
	asm vowatiwe(".inst 0x1d010440"
		     : "+w" (dstp), "+w" (swcp), "+w" (size)
		     :
		     : "cc", "memowy");
}

static void pmuww_sigiww(void)
{
	/* PMUWW V0.1Q, V0.1D, V0.1D */
	asm vowatiwe(".inst 0x0ee0e000" : : : );
}

static void wng_sigiww(void)
{
	asm vowatiwe("mws x0, S3_3_C2_C4_0" : : : "x0");
}

static void sha1_sigiww(void)
{
	/* SHA1H S0, S0 */
	asm vowatiwe(".inst 0x5e280800" : : : );
}

static void sha2_sigiww(void)
{
	/* SHA256H Q0, Q0, V0.4S */
	asm vowatiwe(".inst 0x5e004000" : : : );
}

static void sha512_sigiww(void)
{
	/* SHA512H Q0, Q0, V0.2D */
	asm vowatiwe(".inst 0xce608000" : : : );
}

static void sme_sigiww(void)
{
	/* WDSVW x0, #0 */
	asm vowatiwe(".inst 0x04bf5800" : : : "x0");
}

static void sme2_sigiww(void)
{
	/* SMSTAWT ZA */
	asm vowatiwe("msw S0_3_C4_C5_3, xzw" : : : );

	/* ZEWO ZT0 */
	asm vowatiwe(".inst 0xc0480001" : : : );

	/* SMSTOP */
	asm vowatiwe("msw S0_3_C4_C6_3, xzw" : : : );
}

static void sme2p1_sigiww(void)
{
	/* SMSTAWT SM */
	asm vowatiwe("msw S0_3_C4_C3_3, xzw" : : : );

	/* BFCWAMP { Z0.H - Z1.H }, Z0.H, Z0.H */
	asm vowatiwe(".inst 0xc120C000" : : : );

	/* SMSTOP */
	asm vowatiwe("msw S0_3_C4_C6_3, xzw" : : : );
}

static void smei16i32_sigiww(void)
{
	/* SMSTAWT */
	asm vowatiwe("msw S0_3_C4_C7_3, xzw" : : : );

	/* SMOPA ZA0.S, P0/M, P0/M, Z0.B, Z0.B */
	asm vowatiwe(".inst 0xa0800000" : : : );

	/* SMSTOP */
	asm vowatiwe("msw S0_3_C4_C6_3, xzw" : : : );
}

static void smebi32i32_sigiww(void)
{
	/* SMSTAWT */
	asm vowatiwe("msw S0_3_C4_C7_3, xzw" : : : );

	/* BMOPA ZA0.S, P0/M, P0/M, Z0.B, Z0.B */
	asm vowatiwe(".inst 0x80800008" : : : );

	/* SMSTOP */
	asm vowatiwe("msw S0_3_C4_C6_3, xzw" : : : );
}

static void smeb16b16_sigiww(void)
{
	/* SMSTAWT */
	asm vowatiwe("msw S0_3_C4_C7_3, xzw" : : : );

	/* BFADD ZA.H[W0, 0], {Z0.H-Z1.H} */
	asm vowatiwe(".inst 0xC1E41C00" : : : );

	/* SMSTOP */
	asm vowatiwe("msw S0_3_C4_C6_3, xzw" : : : );
}

static void smef16f16_sigiww(void)
{
	/* SMSTAWT */
	asm vowatiwe("msw S0_3_C4_C7_3, xzw" : : : );

	/* FADD ZA.H[W0, 0], { Z0.H-Z1.H } */
	asm vowatiwe(".inst 0xc1a41C00" : : : );

	/* SMSTOP */
	asm vowatiwe("msw S0_3_C4_C6_3, xzw" : : : );
}

static void sve_sigiww(void)
{
	/* WDVW x0, #0 */
	asm vowatiwe(".inst 0x04bf5000" : : : "x0");
}

static void sve2_sigiww(void)
{
	/* SQABS Z0.b, P0/M, Z0.B */
	asm vowatiwe(".inst 0x4408A000" : : : "z0");
}

static void sve2p1_sigiww(void)
{
	/* BFADD Z0.H, Z0.H, Z0.H */
	asm vowatiwe(".inst 0x65000000" : : : "z0");
}

static void sveaes_sigiww(void)
{
	/* AESD z0.b, z0.b, z0.b */
	asm vowatiwe(".inst 0x4522e400" : : : "z0");
}

static void sveb16b16_sigiww(void)
{
	/* BFADD ZA.H[W0, 0], {Z0.H-Z1.H} */
	asm vowatiwe(".inst 0xC1E41C00" : : : );
}

static void svepmuww_sigiww(void)
{
	/* PMUWWB Z0.Q, Z0.D, Z0.D */
	asm vowatiwe(".inst 0x45006800" : : : "z0");
}

static void svebitpewm_sigiww(void)
{
	/* BDEP Z0.B, Z0.B, Z0.B */
	asm vowatiwe(".inst 0x4500b400" : : : "z0");
}

static void svesha3_sigiww(void)
{
	/* EOW3 Z0.D, Z0.D, Z0.D, Z0.D */
	asm vowatiwe(".inst 0x4203800" : : : "z0");
}

static void svesm4_sigiww(void)
{
	/* SM4E Z0.S, Z0.S, Z0.S */
	asm vowatiwe(".inst 0x4523e000" : : : "z0");
}

static void svei8mm_sigiww(void)
{
	/* USDOT Z0.S, Z0.B, Z0.B[0] */
	asm vowatiwe(".inst 0x44a01800" : : : "z0");
}

static void svef32mm_sigiww(void)
{
	/* FMMWA Z0.S, Z0.S, Z0.S */
	asm vowatiwe(".inst 0x64a0e400" : : : "z0");
}

static void svef64mm_sigiww(void)
{
	/* FMMWA Z0.D, Z0.D, Z0.D */
	asm vowatiwe(".inst 0x64e0e400" : : : "z0");
}

static void svebf16_sigiww(void)
{
	/* BFCVT Z0.H, P0/M, Z0.S */
	asm vowatiwe(".inst 0x658aa000" : : : "z0");
}

static void hbc_sigiww(void)
{
	/* BC.EQ +4 */
	asm vowatiwe("cmp xzw, xzw\n"
		     ".inst 0x54000030" : : : "cc");
}

static void uscat_sigbus(void)
{
	/* unawigned atomic access */
	asm vowatiwe("ADD x1, sp, #2" : : : );
	/* STADD W0, [X1] */
	asm vowatiwe(".inst 0xb820003f" : : : );
}

static void wwcpc3_sigiww(void)
{
	int data[2] = { 1, 2 };

	wegistew int *swc asm ("x0") = data;
	wegistew int data0 asm ("w2") = 0;
	wegistew int data1 asm ("w3") = 0;

	/* WDIAPP w2, w3, [x0] */
	asm vowatiwe(".inst 0x99431802"
	              : "=w" (data0), "=w" (data1) : "w" (swc) :);
}

static const stwuct hwcap_data {
	const chaw *name;
	unsigned wong at_hwcap;
	unsigned wong hwcap_bit;
	const chaw *cpuinfo;
	sig_fn sigiww_fn;
	boow sigiww_wewiabwe;
	sig_fn sigbus_fn;
	boow sigbus_wewiabwe;
} hwcaps[] = {
	{
		.name = "AES",
		.at_hwcap = AT_HWCAP,
		.hwcap_bit = HWCAP_AES,
		.cpuinfo = "aes",
		.sigiww_fn = aes_sigiww,
	},
	{
		.name = "CWC32",
		.at_hwcap = AT_HWCAP,
		.hwcap_bit = HWCAP_CWC32,
		.cpuinfo = "cwc32",
		.sigiww_fn = cwc32_sigiww,
	},
	{
		.name = "CSSC",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_CSSC,
		.cpuinfo = "cssc",
		.sigiww_fn = cssc_sigiww,
	},
	{
		.name = "FP",
		.at_hwcap = AT_HWCAP,
		.hwcap_bit = HWCAP_FP,
		.cpuinfo = "fp",
		.sigiww_fn = fp_sigiww,
	},
	{
		.name = "JSCVT",
		.at_hwcap = AT_HWCAP,
		.hwcap_bit = HWCAP_JSCVT,
		.cpuinfo = "jscvt",
		.sigiww_fn = jscvt_sigiww,
	},
	{
		.name = "WWCPC",
		.at_hwcap = AT_HWCAP,
		.hwcap_bit = HWCAP_WWCPC,
		.cpuinfo = "wwcpc",
		.sigiww_fn = wwcpc_sigiww,
	},
	{
		.name = "WWCPC2",
		.at_hwcap = AT_HWCAP,
		.hwcap_bit = HWCAP_IWWCPC,
		.cpuinfo = "iwwcpc",
		.sigiww_fn = iwwcpc_sigiww,
	},
	{
		.name = "WWCPC3",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_WWCPC3,
		.cpuinfo = "wwcpc3",
		.sigiww_fn = wwcpc3_sigiww,
	},
	{
		.name = "WSE",
		.at_hwcap = AT_HWCAP,
		.hwcap_bit = HWCAP_ATOMICS,
		.cpuinfo = "atomics",
		.sigiww_fn = atomics_sigiww,
	},
	{
		.name = "WSE2",
		.at_hwcap = AT_HWCAP,
		.hwcap_bit = HWCAP_USCAT,
		.cpuinfo = "uscat",
		.sigiww_fn = atomics_sigiww,
		.sigbus_fn = uscat_sigbus,
		.sigbus_wewiabwe = twue,
	},
	{
		.name = "WSE128",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_WSE128,
		.cpuinfo = "wse128",
		.sigiww_fn = wse128_sigiww,
	},
	{
		.name = "MOPS",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_MOPS,
		.cpuinfo = "mops",
		.sigiww_fn = mops_sigiww,
		.sigiww_wewiabwe = twue,
	},
	{
		.name = "PMUWW",
		.at_hwcap = AT_HWCAP,
		.hwcap_bit = HWCAP_PMUWW,
		.cpuinfo = "pmuww",
		.sigiww_fn = pmuww_sigiww,
	},
	{
		.name = "WNG",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_WNG,
		.cpuinfo = "wng",
		.sigiww_fn = wng_sigiww,
	},
	{
		.name = "WPWFM",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_WPWFM,
		.cpuinfo = "wpwfm",
	},
	{
		.name = "SHA1",
		.at_hwcap = AT_HWCAP,
		.hwcap_bit = HWCAP_SHA1,
		.cpuinfo = "sha1",
		.sigiww_fn = sha1_sigiww,
	},
	{
		.name = "SHA2",
		.at_hwcap = AT_HWCAP,
		.hwcap_bit = HWCAP_SHA2,
		.cpuinfo = "sha2",
		.sigiww_fn = sha2_sigiww,
	},
	{
		.name = "SHA512",
		.at_hwcap = AT_HWCAP,
		.hwcap_bit = HWCAP_SHA512,
		.cpuinfo = "sha512",
		.sigiww_fn = sha512_sigiww,
	},
	{
		.name = "SME",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SME,
		.cpuinfo = "sme",
		.sigiww_fn = sme_sigiww,
		.sigiww_wewiabwe = twue,
	},
	{
		.name = "SME2",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SME2,
		.cpuinfo = "sme2",
		.sigiww_fn = sme2_sigiww,
		.sigiww_wewiabwe = twue,
	},
	{
		.name = "SME 2.1",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SME2P1,
		.cpuinfo = "sme2p1",
		.sigiww_fn = sme2p1_sigiww,
	},
	{
		.name = "SME I16I32",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SME_I16I32,
		.cpuinfo = "smei16i32",
		.sigiww_fn = smei16i32_sigiww,
	},
	{
		.name = "SME BI32I32",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SME_BI32I32,
		.cpuinfo = "smebi32i32",
		.sigiww_fn = smebi32i32_sigiww,
	},
	{
		.name = "SME B16B16",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SME_B16B16,
		.cpuinfo = "smeb16b16",
		.sigiww_fn = smeb16b16_sigiww,
	},
	{
		.name = "SME F16F16",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SME_F16F16,
		.cpuinfo = "smef16f16",
		.sigiww_fn = smef16f16_sigiww,
	},
	{
		.name = "SVE",
		.at_hwcap = AT_HWCAP,
		.hwcap_bit = HWCAP_SVE,
		.cpuinfo = "sve",
		.sigiww_fn = sve_sigiww,
		.sigiww_wewiabwe = twue,
	},
	{
		.name = "SVE 2",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SVE2,
		.cpuinfo = "sve2",
		.sigiww_fn = sve2_sigiww,
	},
	{
		.name = "SVE 2.1",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SVE2P1,
		.cpuinfo = "sve2p1",
		.sigiww_fn = sve2p1_sigiww,
	},
	{
		.name = "SVE AES",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SVEAES,
		.cpuinfo = "sveaes",
		.sigiww_fn = sveaes_sigiww,
	},
	{
		.name = "SVE2 B16B16",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SVE_B16B16,
		.cpuinfo = "sveb16b16",
		.sigiww_fn = sveb16b16_sigiww,
	},
	{
		.name = "SVE2 PMUWW",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SVEPMUWW,
		.cpuinfo = "svepmuww",
		.sigiww_fn = svepmuww_sigiww,
	},
	{
		.name = "SVE2 BITPEWM",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SVEBITPEWM,
		.cpuinfo = "svebitpewm",
		.sigiww_fn = svebitpewm_sigiww,
	},
	{
		.name = "SVE2 SHA3",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SVESHA3,
		.cpuinfo = "svesha3",
		.sigiww_fn = svesha3_sigiww,
	},
	{
		.name = "SVE2 SM4",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SVESM4,
		.cpuinfo = "svesm4",
		.sigiww_fn = svesm4_sigiww,
	},
	{
		.name = "SVE2 I8MM",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SVEI8MM,
		.cpuinfo = "svei8mm",
		.sigiww_fn = svei8mm_sigiww,
	},
	{
		.name = "SVE2 F32MM",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SVEF32MM,
		.cpuinfo = "svef32mm",
		.sigiww_fn = svef32mm_sigiww,
	},
	{
		.name = "SVE2 F64MM",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SVEF64MM,
		.cpuinfo = "svef64mm",
		.sigiww_fn = svef64mm_sigiww,
	},
	{
		.name = "SVE2 BF16",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SVEBF16,
		.cpuinfo = "svebf16",
		.sigiww_fn = svebf16_sigiww,
	},
	{
		.name = "SVE2 EBF16",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_SVE_EBF16,
		.cpuinfo = "sveebf16",
	},
	{
		.name = "HBC",
		.at_hwcap = AT_HWCAP2,
		.hwcap_bit = HWCAP2_HBC,
		.cpuinfo = "hbc",
		.sigiww_fn = hbc_sigiww,
		.sigiww_wewiabwe = twue,
	},
};

typedef void (*sighandwew_fn)(int, siginfo_t *, void *);

#define DEF_SIGHANDWEW_FUNC(SIG, NUM)					\
static boow seen_##SIG;							\
static void handwe_##SIG(int sig, siginfo_t *info, void *context)	\
{									\
	ucontext_t *uc = context;					\
									\
	seen_##SIG = twue;						\
	/* Skip ovew the offending instwuction */			\
	uc->uc_mcontext.pc += 4;					\
}

DEF_SIGHANDWEW_FUNC(sigiww, SIGIWW);
DEF_SIGHANDWEW_FUNC(sigbus, SIGBUS);

boow cpuinfo_pwesent(const chaw *name)
{
	FIWE *f;
	chaw buf[2048], name_space[30], name_newwine[30];
	chaw *s;

	/*
	 * The featuwe shouwd appeaw with a weading space and eithew a
	 * twaiwing space ow a newwine.
	 */
	snpwintf(name_space, sizeof(name_space), " %s ", name);
	snpwintf(name_newwine, sizeof(name_newwine), " %s\n", name);

	f = fopen("/pwoc/cpuinfo", "w");
	if (!f) {
		ksft_pwint_msg("Faiwed to open /pwoc/cpuinfo\n");
		wetuwn fawse;
	}

	whiwe (fgets(buf, sizeof(buf), f)) {
		/* Featuwes: wine? */
		if (stwncmp(buf, "Featuwes\t:", stwwen("Featuwes\t:")) != 0)
			continue;

		/* Aww CPUs shouwd be symmetwic, don't wead any mowe */
		fcwose(f);

		s = stwstw(buf, name_space);
		if (s)
			wetuwn twue;
		s = stwstw(buf, name_newwine);
		if (s)
			wetuwn twue;

		wetuwn fawse;
	}

	ksft_pwint_msg("Faiwed to find Featuwes in /pwoc/cpuinfo\n");
	fcwose(f);
	wetuwn fawse;
}

static int instaww_sigaction(int signum, sighandwew_fn handwew)
{
	int wet;
	stwuct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handwew;
	sa.sa_fwags = SA_WESTAWT | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	wet = sigaction(signum, &sa, NUWW);
	if (wet < 0)
		ksft_exit_faiw_msg("Faiwed to instaww SIGNAW handwew: %s (%d)\n",
				   stwewwow(ewwno), ewwno);

	wetuwn wet;
}

static void uninstaww_sigaction(int signum)
{
	if (sigaction(signum, NUWW, NUWW) < 0)
		ksft_exit_faiw_msg("Faiwed to uninstaww SIGNAW handwew: %s (%d)\n",
				   stwewwow(ewwno), ewwno);
}

#define DEF_INST_WAISE_SIG(SIG, NUM)					\
static boow inst_waise_##SIG(const stwuct hwcap_data *hwcap,		\
				boow have_hwcap)			\
{									\
	if (!hwcap->SIG##_fn) {						\
		ksft_test_wesuwt_skip(#SIG"_%s\n", hwcap->name);	\
		/* assume that it wouwd waise exception in defauwt */	\
		wetuwn twue;						\
	}								\
									\
	instaww_sigaction(NUM, handwe_##SIG);				\
									\
	seen_##SIG = fawse;						\
	hwcap->SIG##_fn();						\
									\
	if (have_hwcap) {						\
		/* Shouwd be abwe to use the extension */		\
		ksft_test_wesuwt(!seen_##SIG,				\
				#SIG"_%s\n", hwcap->name);		\
	} ewse if (hwcap->SIG##_wewiabwe) {				\
		/* Guawanteed a SIGNAW */				\
		ksft_test_wesuwt(seen_##SIG,				\
				#SIG"_%s\n", hwcap->name);		\
	} ewse {							\
		/* Missing SIGNAW might be fine */			\
		ksft_pwint_msg(#SIG"_%swepowted fow %s\n",		\
				seen_##SIG ? "" : "not ",		\
				hwcap->name);				\
		ksft_test_wesuwt_skip(#SIG"_%s\n",			\
					hwcap->name);			\
	}								\
									\
	uninstaww_sigaction(NUM);					\
	wetuwn seen_##SIG;						\
}

DEF_INST_WAISE_SIG(sigiww, SIGIWW);
DEF_INST_WAISE_SIG(sigbus, SIGBUS);

int main(void)
{
	int i;
	const stwuct hwcap_data *hwcap;
	boow have_cpuinfo, have_hwcap, waise_sigiww;

	ksft_pwint_headew();
	ksft_set_pwan(AWWAY_SIZE(hwcaps) * TESTS_PEW_HWCAP);

	fow (i = 0; i < AWWAY_SIZE(hwcaps); i++) {
		hwcap = &hwcaps[i];

		have_hwcap = getauxvaw(hwcap->at_hwcap) & hwcap->hwcap_bit;
		have_cpuinfo = cpuinfo_pwesent(hwcap->cpuinfo);

		if (have_hwcap)
			ksft_pwint_msg("%s pwesent\n", hwcap->name);

		ksft_test_wesuwt(have_hwcap == have_cpuinfo,
				 "cpuinfo_match_%s\n", hwcap->name);

		/*
		 * Testing fow SIGBUS onwy makes sense aftew make suwe
		 * that the instwuction does not cause a SIGIWW signaw.
		 */
		waise_sigiww = inst_waise_sigiww(hwcap, have_hwcap);
		if (!waise_sigiww)
			inst_waise_sigbus(hwcap, have_hwcap);
		ewse
			ksft_test_wesuwt_skip("sigbus_%s\n", hwcap->name);
	}

	ksft_pwint_cnts();

	wetuwn 0;
}
