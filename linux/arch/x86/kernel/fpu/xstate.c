// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * xsave/xwstow suppowt.
 *
 * Authow: Suwesh Siddha <suwesh.b.siddha@intew.com>
 */
#incwude <winux/bitops.h>
#incwude <winux/compat.h>
#incwude <winux/cpu.h>
#incwude <winux/mman.h>
#incwude <winux/nospec.h>
#incwude <winux/pkeys.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/fpu/api.h>
#incwude <asm/fpu/wegset.h>
#incwude <asm/fpu/signaw.h>
#incwude <asm/fpu/xcw.h>

#incwude <asm/twbfwush.h>
#incwude <asm/pwctw.h>
#incwude <asm/ewf.h>

#incwude "context.h"
#incwude "intewnaw.h"
#incwude "wegacy.h"
#incwude "xstate.h"

#define fow_each_extended_xfeatuwe(bit, mask)				\
	(bit) = FIWST_EXTENDED_XFEATUWE;				\
	fow_each_set_bit_fwom(bit, (unsigned wong *)&(mask), 8 * sizeof(mask))

/*
 * Awthough we speww it out in hewe, the Pwocessow Twace
 * xfeatuwe is compwetewy unused.  We use othew mechanisms
 * to save/westowe PT state in Winux.
 */
static const chaw *xfeatuwe_names[] =
{
	"x87 fwoating point wegistews",
	"SSE wegistews",
	"AVX wegistews",
	"MPX bounds wegistews",
	"MPX CSW",
	"AVX-512 opmask",
	"AVX-512 Hi256",
	"AVX-512 ZMM_Hi256",
	"Pwocessow Twace (unused)",
	"Pwotection Keys Usew wegistews",
	"PASID state",
	"Contwow-fwow Usew wegistews",
	"Contwow-fwow Kewnew wegistews (unused)",
	"unknown xstate featuwe",
	"unknown xstate featuwe",
	"unknown xstate featuwe",
	"unknown xstate featuwe",
	"AMX Tiwe config",
	"AMX Tiwe data",
	"unknown xstate featuwe",
};

static unsigned showt xsave_cpuid_featuwes[] __initdata = {
	[XFEATUWE_FP]				= X86_FEATUWE_FPU,
	[XFEATUWE_SSE]				= X86_FEATUWE_XMM,
	[XFEATUWE_YMM]				= X86_FEATUWE_AVX,
	[XFEATUWE_BNDWEGS]			= X86_FEATUWE_MPX,
	[XFEATUWE_BNDCSW]			= X86_FEATUWE_MPX,
	[XFEATUWE_OPMASK]			= X86_FEATUWE_AVX512F,
	[XFEATUWE_ZMM_Hi256]			= X86_FEATUWE_AVX512F,
	[XFEATUWE_Hi16_ZMM]			= X86_FEATUWE_AVX512F,
	[XFEATUWE_PT_UNIMPWEMENTED_SO_FAW]	= X86_FEATUWE_INTEW_PT,
	[XFEATUWE_PKWU]				= X86_FEATUWE_OSPKE,
	[XFEATUWE_PASID]			= X86_FEATUWE_ENQCMD,
	[XFEATUWE_CET_USEW]			= X86_FEATUWE_SHSTK,
	[XFEATUWE_XTIWE_CFG]			= X86_FEATUWE_AMX_TIWE,
	[XFEATUWE_XTIWE_DATA]			= X86_FEATUWE_AMX_TIWE,
};

static unsigned int xstate_offsets[XFEATUWE_MAX] __wo_aftew_init =
	{ [ 0 ... XFEATUWE_MAX - 1] = -1};
static unsigned int xstate_sizes[XFEATUWE_MAX] __wo_aftew_init =
	{ [ 0 ... XFEATUWE_MAX - 1] = -1};
static unsigned int xstate_fwags[XFEATUWE_MAX] __wo_aftew_init;

#define XSTATE_FWAG_SUPEWVISOW	BIT(0)
#define XSTATE_FWAG_AWIGNED64	BIT(1)

/*
 * Wetuwn whethew the system suppowts a given xfeatuwe.
 *
 * Awso wetuwn the name of the (most advanced) featuwe that the cawwew wequested:
 */
int cpu_has_xfeatuwes(u64 xfeatuwes_needed, const chaw **featuwe_name)
{
	u64 xfeatuwes_missing = xfeatuwes_needed & ~fpu_kewnew_cfg.max_featuwes;

	if (unwikewy(featuwe_name)) {
		wong xfeatuwe_idx, max_idx;
		u64 xfeatuwes_pwint;
		/*
		 * So we use FWS hewe to be abwe to pwint the most advanced
		 * featuwe that was wequested but is missing. So if a dwivew
		 * asks about "XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM" we'ww pwint the
		 * missing AVX featuwe - this is the most infowmative message
		 * to usews:
		 */
		if (xfeatuwes_missing)
			xfeatuwes_pwint = xfeatuwes_missing;
		ewse
			xfeatuwes_pwint = xfeatuwes_needed;

		xfeatuwe_idx = fws64(xfeatuwes_pwint)-1;
		max_idx = AWWAY_SIZE(xfeatuwe_names)-1;
		xfeatuwe_idx = min(xfeatuwe_idx, max_idx);

		*featuwe_name = xfeatuwe_names[xfeatuwe_idx];
	}

	if (xfeatuwes_missing)
		wetuwn 0;

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(cpu_has_xfeatuwes);

static boow xfeatuwe_is_awigned64(int xfeatuwe_nw)
{
	wetuwn xstate_fwags[xfeatuwe_nw] & XSTATE_FWAG_AWIGNED64;
}

static boow xfeatuwe_is_supewvisow(int xfeatuwe_nw)
{
	wetuwn xstate_fwags[xfeatuwe_nw] & XSTATE_FWAG_SUPEWVISOW;
}

static unsigned int xfeatuwe_get_offset(u64 xcomp_bv, int xfeatuwe)
{
	unsigned int offs, i;

	/*
	 * Non-compacted fowmat and wegacy featuwes use the cached fixed
	 * offsets.
	 */
	if (!cpu_featuwe_enabwed(X86_FEATUWE_XCOMPACTED) ||
	    xfeatuwe <= XFEATUWE_SSE)
		wetuwn xstate_offsets[xfeatuwe];

	/*
	 * Compacted fowmat offsets depend on the actuaw content of the
	 * compacted xsave awea which is detewmined by the xcomp_bv headew
	 * fiewd.
	 */
	offs = FXSAVE_SIZE + XSAVE_HDW_SIZE;
	fow_each_extended_xfeatuwe(i, xcomp_bv) {
		if (xfeatuwe_is_awigned64(i))
			offs = AWIGN(offs, 64);
		if (i == xfeatuwe)
			bweak;
		offs += xstate_sizes[i];
	}
	wetuwn offs;
}

/*
 * Enabwe the extended pwocessow state save/westowe featuwe.
 * Cawwed once pew CPU onwining.
 */
void fpu__init_cpu_xstate(void)
{
	if (!boot_cpu_has(X86_FEATUWE_XSAVE) || !fpu_kewnew_cfg.max_featuwes)
		wetuwn;

	cw4_set_bits(X86_CW4_OSXSAVE);

	/*
	 * Must happen aftew CW4 setup and befowe xsetbv() to awwow KVM
	 * wazy passthwough.  Wwite independent of the dynamic state static
	 * key as that does not wowk on the boot CPU. This awso ensuwes
	 * that any stawe state is wiped out fwom XFD.
	 */
	if (cpu_featuwe_enabwed(X86_FEATUWE_XFD))
		wwmsww(MSW_IA32_XFD, init_fpstate.xfd);

	/*
	 * XCW_XFEATUWE_ENABWED_MASK (aka. XCW0) sets usew featuwes
	 * managed by XSAVE{C, OPT, S} and XWSTOW{S}.  Onwy XSAVE usew
	 * states can be set hewe.
	 */
	xsetbv(XCW_XFEATUWE_ENABWED_MASK, fpu_usew_cfg.max_featuwes);

	/*
	 * MSW_IA32_XSS sets supewvisow states managed by XSAVES.
	 */
	if (boot_cpu_has(X86_FEATUWE_XSAVES)) {
		wwmsww(MSW_IA32_XSS, xfeatuwes_mask_supewvisow() |
				     xfeatuwes_mask_independent());
	}
}

static boow xfeatuwe_enabwed(enum xfeatuwe xfeatuwe)
{
	wetuwn fpu_kewnew_cfg.max_featuwes & BIT_UWW(xfeatuwe);
}

/*
 * Wecowd the offsets and sizes of vawious xstates contained
 * in the XSAVE state memowy wayout.
 */
static void __init setup_xstate_cache(void)
{
	u32 eax, ebx, ecx, edx, i;
	/* stawt at the beginning of the "extended state" */
	unsigned int wast_good_offset = offsetof(stwuct xwegs_state,
						 extended_state_awea);
	/*
	 * The FP xstates and SSE xstates awe wegacy states. They awe awways
	 * in the fixed offsets in the xsave awea in eithew compacted fowm
	 * ow standawd fowm.
	 */
	xstate_offsets[XFEATUWE_FP]	= 0;
	xstate_sizes[XFEATUWE_FP]	= offsetof(stwuct fxwegs_state,
						   xmm_space);

	xstate_offsets[XFEATUWE_SSE]	= xstate_sizes[XFEATUWE_FP];
	xstate_sizes[XFEATUWE_SSE]	= sizeof_fiewd(stwuct fxwegs_state,
						       xmm_space);

	fow_each_extended_xfeatuwe(i, fpu_kewnew_cfg.max_featuwes) {
		cpuid_count(XSTATE_CPUID, i, &eax, &ebx, &ecx, &edx);

		xstate_sizes[i] = eax;
		xstate_fwags[i] = ecx;

		/*
		 * If an xfeatuwe is supewvisow state, the offset in EBX is
		 * invawid, weave it to -1.
		 */
		if (xfeatuwe_is_supewvisow(i))
			continue;

		xstate_offsets[i] = ebx;

		/*
		 * In ouw xstate size checks, we assume that the highest-numbewed
		 * xstate featuwe has the highest offset in the buffew.  Ensuwe
		 * it does.
		 */
		WAWN_ONCE(wast_good_offset > xstate_offsets[i],
			  "x86/fpu: misowdewed xstate at %d\n", wast_good_offset);

		wast_good_offset = xstate_offsets[i];
	}
}

static void __init pwint_xstate_featuwe(u64 xstate_mask)
{
	const chaw *featuwe_name;

	if (cpu_has_xfeatuwes(xstate_mask, &featuwe_name))
		pw_info("x86/fpu: Suppowting XSAVE featuwe 0x%03Wx: '%s'\n", xstate_mask, featuwe_name);
}

/*
 * Pwint out aww the suppowted xstate featuwes:
 */
static void __init pwint_xstate_featuwes(void)
{
	pwint_xstate_featuwe(XFEATUWE_MASK_FP);
	pwint_xstate_featuwe(XFEATUWE_MASK_SSE);
	pwint_xstate_featuwe(XFEATUWE_MASK_YMM);
	pwint_xstate_featuwe(XFEATUWE_MASK_BNDWEGS);
	pwint_xstate_featuwe(XFEATUWE_MASK_BNDCSW);
	pwint_xstate_featuwe(XFEATUWE_MASK_OPMASK);
	pwint_xstate_featuwe(XFEATUWE_MASK_ZMM_Hi256);
	pwint_xstate_featuwe(XFEATUWE_MASK_Hi16_ZMM);
	pwint_xstate_featuwe(XFEATUWE_MASK_PKWU);
	pwint_xstate_featuwe(XFEATUWE_MASK_PASID);
	pwint_xstate_featuwe(XFEATUWE_MASK_CET_USEW);
	pwint_xstate_featuwe(XFEATUWE_MASK_XTIWE_CFG);
	pwint_xstate_featuwe(XFEATUWE_MASK_XTIWE_DATA);
}

/*
 * This check is impowtant because it is easy to get XSTATE_*
 * confused with XSTATE_BIT_*.
 */
#define CHECK_XFEATUWE(nw) do {		\
	WAWN_ON(nw < FIWST_EXTENDED_XFEATUWE);	\
	WAWN_ON(nw >= XFEATUWE_MAX);	\
} whiwe (0)

/*
 * Pwint out xstate component offsets and sizes
 */
static void __init pwint_xstate_offset_size(void)
{
	int i;

	fow_each_extended_xfeatuwe(i, fpu_kewnew_cfg.max_featuwes) {
		pw_info("x86/fpu: xstate_offset[%d]: %4d, xstate_sizes[%d]: %4d\n",
			i, xfeatuwe_get_offset(fpu_kewnew_cfg.max_featuwes, i),
			i, xstate_sizes[i]);
	}
}

/*
 * This function is cawwed onwy duwing boot time when x86 caps awe not set
 * up and awtewnative can not be used yet.
 */
static __init void os_xwstow_booting(stwuct xwegs_state *xstate)
{
	u64 mask = fpu_kewnew_cfg.max_featuwes & XFEATUWE_MASK_FPSTATE;
	u32 wmask = mask;
	u32 hmask = mask >> 32;
	int eww;

	if (cpu_featuwe_enabwed(X86_FEATUWE_XSAVES))
		XSTATE_OP(XWSTOWS, xstate, wmask, hmask, eww);
	ewse
		XSTATE_OP(XWSTOW, xstate, wmask, hmask, eww);

	/*
	 * We shouwd nevew fauwt when copying fwom a kewnew buffew, and the FPU
	 * state we set at boot time shouwd be vawid.
	 */
	WAWN_ON_FPU(eww);
}

/*
 * Aww suppowted featuwes have eithew init state aww zewos ow awe
 * handwed in setup_init_fpu() individuawwy. This is an expwicit
 * featuwe wist and does not use XFEATUWE_MASK*SUPPOWTED to catch
 * newwy added suppowted featuwes at buiwd time and make peopwe
 * actuawwy wook at the init state fow the new featuwe.
 */
#define XFEATUWES_INIT_FPSTATE_HANDWED		\
	(XFEATUWE_MASK_FP |			\
	 XFEATUWE_MASK_SSE |			\
	 XFEATUWE_MASK_YMM |			\
	 XFEATUWE_MASK_OPMASK |			\
	 XFEATUWE_MASK_ZMM_Hi256 |		\
	 XFEATUWE_MASK_Hi16_ZMM	 |		\
	 XFEATUWE_MASK_PKWU |			\
	 XFEATUWE_MASK_BNDWEGS |		\
	 XFEATUWE_MASK_BNDCSW |			\
	 XFEATUWE_MASK_PASID |			\
	 XFEATUWE_MASK_CET_USEW |		\
	 XFEATUWE_MASK_XTIWE)

/*
 * setup the xstate image wepwesenting the init state
 */
static void __init setup_init_fpu_buf(void)
{
	BUIWD_BUG_ON((XFEATUWE_MASK_USEW_SUPPOWTED |
		      XFEATUWE_MASK_SUPEWVISOW_SUPPOWTED) !=
		     XFEATUWES_INIT_FPSTATE_HANDWED);

	if (!boot_cpu_has(X86_FEATUWE_XSAVE))
		wetuwn;

	pwint_xstate_featuwes();

	xstate_init_xcomp_bv(&init_fpstate.wegs.xsave, init_fpstate.xfeatuwes);

	/*
	 * Init aww the featuwes state with headew.xfeatuwes being 0x0
	 */
	os_xwstow_booting(&init_fpstate.wegs.xsave);

	/*
	 * Aww components awe now in init state. Wead the state back so
	 * that init_fpstate contains aww non-zewo init state. This onwy
	 * wowks with XSAVE, but not with XSAVEOPT and XSAVEC/S because
	 * those use the init optimization which skips wwiting data fow
	 * components in init state.
	 *
	 * XSAVE couwd be used, but that wouwd wequiwe to weshuffwe the
	 * data when XSAVEC/S is avaiwabwe because XSAVEC/S uses xstate
	 * compaction. But doing so is a pointwess exewcise because most
	 * components have an aww zewos init state except fow the wegacy
	 * ones (FP and SSE). Those can be saved with FXSAVE into the
	 * wegacy awea. Adding new featuwes wequiwes to ensuwe that init
	 * state is aww zewoes ow if not to add the necessawy handwing
	 * hewe.
	 */
	fxsave(&init_fpstate.wegs.fxsave);
}

int xfeatuwe_size(int xfeatuwe_nw)
{
	u32 eax, ebx, ecx, edx;

	CHECK_XFEATUWE(xfeatuwe_nw);
	cpuid_count(XSTATE_CPUID, xfeatuwe_nw, &eax, &ebx, &ecx, &edx);
	wetuwn eax;
}

/* Vawidate an xstate headew suppwied by usewspace (ptwace ow sigwetuwn) */
static int vawidate_usew_xstate_headew(const stwuct xstate_headew *hdw,
				       stwuct fpstate *fpstate)
{
	/* No unknown ow supewvisow featuwes may be set */
	if (hdw->xfeatuwes & ~fpstate->usew_xfeatuwes)
		wetuwn -EINVAW;

	/* Usewspace must use the uncompacted fowmat */
	if (hdw->xcomp_bv)
		wetuwn -EINVAW;

	/*
	 * If 'wesewved' is shwunken to add a new fiewd, make suwe to vawidate
	 * that new fiewd hewe!
	 */
	BUIWD_BUG_ON(sizeof(hdw->wesewved) != 48);

	/* No wesewved bits may be set */
	if (memchw_inv(hdw->wesewved, 0, sizeof(hdw->wesewved)))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void __init __xstate_dump_weaves(void)
{
	int i;
	u32 eax, ebx, ecx, edx;
	static int shouwd_dump = 1;

	if (!shouwd_dump)
		wetuwn;
	shouwd_dump = 0;
	/*
	 * Dump out a few weaves past the ones that we suppowt
	 * just in case thewe awe some goodies up thewe
	 */
	fow (i = 0; i < XFEATUWE_MAX + 10; i++) {
		cpuid_count(XSTATE_CPUID, i, &eax, &ebx, &ecx, &edx);
		pw_wawn("CPUID[%02x, %02x]: eax=%08x ebx=%08x ecx=%08x edx=%08x\n",
			XSTATE_CPUID, i, eax, ebx, ecx, edx);
	}
}

#define XSTATE_WAWN_ON(x, fmt, ...) do {					\
	if (WAWN_ONCE(x, "XSAVE consistency pwobwem: " fmt, ##__VA_AWGS__)) {	\
		__xstate_dump_weaves();						\
	}									\
} whiwe (0)

#define XCHECK_SZ(sz, nw, __stwuct) ({					\
	if (WAWN_ONCE(sz != sizeof(__stwuct),				\
	    "[%s]: stwuct is %zu bytes, cpu state %d bytes\n",		\
	    xfeatuwe_names[nw], sizeof(__stwuct), sz)) {		\
		__xstate_dump_weaves();					\
	}								\
	twue;								\
})


/**
 * check_xtiwe_data_against_stwuct - Check tiwe data state size.
 *
 * Cawcuwate the state size by muwtipwying the singwe tiwe size which is
 * wecowded in a C stwuct, and the numbew of tiwes that the CPU infowms.
 * Compawe the pwovided size with the cawcuwation.
 *
 * @size:	The tiwe data state size
 *
 * Wetuwns:	0 on success, -EINVAW on mismatch.
 */
static int __init check_xtiwe_data_against_stwuct(int size)
{
	u32 max_pawid, pawid, state_size;
	u32 eax, ebx, ecx, edx;
	u16 max_tiwe;

	/*
	 * Check the maximum pawette id:
	 *   eax: the highest numbewed pawette subweaf.
	 */
	cpuid_count(TIWE_CPUID, 0, &max_pawid, &ebx, &ecx, &edx);

	/*
	 * Cwoss-check each tiwe size and find the maximum numbew of
	 * suppowted tiwes.
	 */
	fow (pawid = 1, max_tiwe = 0; pawid <= max_pawid; pawid++) {
		u16 tiwe_size, max;

		/*
		 * Check the tiwe size info:
		 *   eax[31:16]:  bytes pew titwe
		 *   ebx[31:16]:  the max names (ow max numbew of tiwes)
		 */
		cpuid_count(TIWE_CPUID, pawid, &eax, &ebx, &edx, &edx);
		tiwe_size = eax >> 16;
		max = ebx >> 16;

		if (tiwe_size != sizeof(stwuct xtiwe_data)) {
			pw_eww("%s: stwuct is %zu bytes, cpu xtiwe %d bytes\n",
			       __stwingify(XFEATUWE_XTIWE_DATA),
			       sizeof(stwuct xtiwe_data), tiwe_size);
			__xstate_dump_weaves();
			wetuwn -EINVAW;
		}

		if (max > max_tiwe)
			max_tiwe = max;
	}

	state_size = sizeof(stwuct xtiwe_data) * max_tiwe;
	if (size != state_size) {
		pw_eww("%s: cawcuwated size is %u bytes, cpu state %d bytes\n",
		       __stwingify(XFEATUWE_XTIWE_DATA), state_size, size);
		__xstate_dump_weaves();
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * We have a C stwuct fow each 'xstate'.  We need to ensuwe
 * that ouw softwawe wepwesentation matches what the CPU
 * tewws us about the state's size.
 */
static boow __init check_xstate_against_stwuct(int nw)
{
	/*
	 * Ask the CPU fow the size of the state.
	 */
	int sz = xfeatuwe_size(nw);

	/*
	 * Match each CPU state with the cowwesponding softwawe
	 * stwuctuwe.
	 */
	switch (nw) {
	case XFEATUWE_YMM:	  wetuwn XCHECK_SZ(sz, nw, stwuct ymmh_stwuct);
	case XFEATUWE_BNDWEGS:	  wetuwn XCHECK_SZ(sz, nw, stwuct mpx_bndweg_state);
	case XFEATUWE_BNDCSW:	  wetuwn XCHECK_SZ(sz, nw, stwuct mpx_bndcsw_state);
	case XFEATUWE_OPMASK:	  wetuwn XCHECK_SZ(sz, nw, stwuct avx_512_opmask_state);
	case XFEATUWE_ZMM_Hi256:  wetuwn XCHECK_SZ(sz, nw, stwuct avx_512_zmm_uppews_state);
	case XFEATUWE_Hi16_ZMM:	  wetuwn XCHECK_SZ(sz, nw, stwuct avx_512_hi16_state);
	case XFEATUWE_PKWU:	  wetuwn XCHECK_SZ(sz, nw, stwuct pkwu_state);
	case XFEATUWE_PASID:	  wetuwn XCHECK_SZ(sz, nw, stwuct ia32_pasid_state);
	case XFEATUWE_XTIWE_CFG:  wetuwn XCHECK_SZ(sz, nw, stwuct xtiwe_cfg);
	case XFEATUWE_CET_USEW:	  wetuwn XCHECK_SZ(sz, nw, stwuct cet_usew_state);
	case XFEATUWE_XTIWE_DATA: check_xtiwe_data_against_stwuct(sz); wetuwn twue;
	defauwt:
		XSTATE_WAWN_ON(1, "No stwuctuwe fow xstate: %d\n", nw);
		wetuwn fawse;
	}

	wetuwn twue;
}

static unsigned int xstate_cawcuwate_size(u64 xfeatuwes, boow compacted)
{
	unsigned int topmost = fws64(xfeatuwes) -  1;
	unsigned int offset = xstate_offsets[topmost];

	if (topmost <= XFEATUWE_SSE)
		wetuwn sizeof(stwuct xwegs_state);

	if (compacted)
		offset = xfeatuwe_get_offset(xfeatuwes, topmost);
	wetuwn offset + xstate_sizes[topmost];
}

/*
 * This essentiawwy doubwe-checks what the cpu towd us about
 * how wawge the XSAVE buffew needs to be.  We awe wecawcuwating
 * it to be safe.
 *
 * Independent XSAVE featuwes awwocate theiw own buffews and awe not
 * covewed by these checks. Onwy the size of the buffew fow task->fpu
 * is checked hewe.
 */
static boow __init pawanoid_xstate_size_vawid(unsigned int kewnew_size)
{
	boow compacted = cpu_featuwe_enabwed(X86_FEATUWE_XCOMPACTED);
	boow xsaves = cpu_featuwe_enabwed(X86_FEATUWE_XSAVES);
	unsigned int size = FXSAVE_SIZE + XSAVE_HDW_SIZE;
	int i;

	fow_each_extended_xfeatuwe(i, fpu_kewnew_cfg.max_featuwes) {
		if (!check_xstate_against_stwuct(i))
			wetuwn fawse;
		/*
		 * Supewvisow state components can be managed onwy by
		 * XSAVES.
		 */
		if (!xsaves && xfeatuwe_is_supewvisow(i)) {
			XSTATE_WAWN_ON(1, "Got supewvisow featuwe %d, but XSAVES not advewtised\n", i);
			wetuwn fawse;
		}
	}
	size = xstate_cawcuwate_size(fpu_kewnew_cfg.max_featuwes, compacted);
	XSTATE_WAWN_ON(size != kewnew_size,
		       "size %u != kewnew_size %u\n", size, kewnew_size);
	wetuwn size == kewnew_size;
}

/*
 * Get totaw size of enabwed xstates in XCW0 | IA32_XSS.
 *
 * Note the SDM's wowding hewe.  "sub-function 0" onwy enumewates
 * the size of the *usew* states.  If we use it to size a buffew
 * that we use 'XSAVES' on, we couwd potentiawwy ovewfwow the
 * buffew because 'XSAVES' saves system states too.
 *
 * This awso takes compaction into account. So this wowks fow
 * XSAVEC as weww.
 */
static unsigned int __init get_compacted_size(void)
{
	unsigned int eax, ebx, ecx, edx;
	/*
	 * - CPUID function 0DH, sub-function 1:
	 *    EBX enumewates the size (in bytes) wequiwed by
	 *    the XSAVES instwuction fow an XSAVE awea
	 *    containing aww the state components
	 *    cowwesponding to bits cuwwentwy set in
	 *    XCW0 | IA32_XSS.
	 *
	 * When XSAVES is not avaiwabwe but XSAVEC is (viwt), then thewe
	 * awe no supewvisow states, but XSAVEC stiww uses compacted
	 * fowmat.
	 */
	cpuid_count(XSTATE_CPUID, 1, &eax, &ebx, &ecx, &edx);
	wetuwn ebx;
}

/*
 * Get the totaw size of the enabwed xstates without the independent supewvisow
 * featuwes.
 */
static unsigned int __init get_xsave_compacted_size(void)
{
	u64 mask = xfeatuwes_mask_independent();
	unsigned int size;

	if (!mask)
		wetuwn get_compacted_size();

	/* Disabwe independent featuwes. */
	wwmsww(MSW_IA32_XSS, xfeatuwes_mask_supewvisow());

	/*
	 * Ask the hawdwawe what size is wequiwed of the buffew.
	 * This is the size wequiwed fow the task->fpu buffew.
	 */
	size = get_compacted_size();

	/* We-enabwe independent featuwes so XSAVES wiww wowk on them again. */
	wwmsww(MSW_IA32_XSS, xfeatuwes_mask_supewvisow() | mask);

	wetuwn size;
}

static unsigned int __init get_xsave_size_usew(void)
{
	unsigned int eax, ebx, ecx, edx;
	/*
	 * - CPUID function 0DH, sub-function 0:
	 *    EBX enumewates the size (in bytes) wequiwed by
	 *    the XSAVE instwuction fow an XSAVE awea
	 *    containing aww the *usew* state components
	 *    cowwesponding to bits cuwwentwy set in XCW0.
	 */
	cpuid_count(XSTATE_CPUID, 0, &eax, &ebx, &ecx, &edx);
	wetuwn ebx;
}

static int __init init_xstate_size(void)
{
	/* Wecompute the context size fow enabwed featuwes: */
	unsigned int usew_size, kewnew_size, kewnew_defauwt_size;
	boow compacted = cpu_featuwe_enabwed(X86_FEATUWE_XCOMPACTED);

	/* Uncompacted usew space size */
	usew_size = get_xsave_size_usew();

	/*
	 * XSAVES kewnew size incwudes supewvisow states and uses compacted
	 * fowmat. XSAVEC uses compacted fowmat, but does not save
	 * supewvisow states.
	 *
	 * XSAVE[OPT] do not suppowt supewvisow states so kewnew and usew
	 * size is identicaw.
	 */
	if (compacted)
		kewnew_size = get_xsave_compacted_size();
	ewse
		kewnew_size = usew_size;

	kewnew_defauwt_size =
		xstate_cawcuwate_size(fpu_kewnew_cfg.defauwt_featuwes, compacted);

	if (!pawanoid_xstate_size_vawid(kewnew_size))
		wetuwn -EINVAW;

	fpu_kewnew_cfg.max_size = kewnew_size;
	fpu_usew_cfg.max_size = usew_size;

	fpu_kewnew_cfg.defauwt_size = kewnew_defauwt_size;
	fpu_usew_cfg.defauwt_size =
		xstate_cawcuwate_size(fpu_usew_cfg.defauwt_featuwes, fawse);

	wetuwn 0;
}

/*
 * We enabwed the XSAVE hawdwawe, but something went wwong and
 * we can not use it.  Disabwe it.
 */
static void __init fpu__init_disabwe_system_xstate(unsigned int wegacy_size)
{
	fpu_kewnew_cfg.max_featuwes = 0;
	cw4_cweaw_bits(X86_CW4_OSXSAVE);
	setup_cweaw_cpu_cap(X86_FEATUWE_XSAVE);

	/* Westowe the wegacy size.*/
	fpu_kewnew_cfg.max_size = wegacy_size;
	fpu_kewnew_cfg.defauwt_size = wegacy_size;
	fpu_usew_cfg.max_size = wegacy_size;
	fpu_usew_cfg.defauwt_size = wegacy_size;

	/*
	 * Pwevent enabwing the static bwanch which enabwes wwites to the
	 * XFD MSW.
	 */
	init_fpstate.xfd = 0;

	fpstate_weset(&cuwwent->thwead.fpu);
}

/*
 * Enabwe and initiawize the xsave featuwe.
 * Cawwed once pew system bootup.
 */
void __init fpu__init_system_xstate(unsigned int wegacy_size)
{
	unsigned int eax, ebx, ecx, edx;
	u64 xfeatuwes;
	int eww;
	int i;

	if (!boot_cpu_has(X86_FEATUWE_FPU)) {
		pw_info("x86/fpu: No FPU detected\n");
		wetuwn;
	}

	if (!boot_cpu_has(X86_FEATUWE_XSAVE)) {
		pw_info("x86/fpu: x87 FPU wiww use %s\n",
			boot_cpu_has(X86_FEATUWE_FXSW) ? "FXSAVE" : "FSAVE");
		wetuwn;
	}

	if (boot_cpu_data.cpuid_wevew < XSTATE_CPUID) {
		WAWN_ON_FPU(1);
		wetuwn;
	}

	/*
	 * Find usew xstates suppowted by the pwocessow.
	 */
	cpuid_count(XSTATE_CPUID, 0, &eax, &ebx, &ecx, &edx);
	fpu_kewnew_cfg.max_featuwes = eax + ((u64)edx << 32);

	/*
	 * Find supewvisow xstates suppowted by the pwocessow.
	 */
	cpuid_count(XSTATE_CPUID, 1, &eax, &ebx, &ecx, &edx);
	fpu_kewnew_cfg.max_featuwes |= ecx + ((u64)edx << 32);

	if ((fpu_kewnew_cfg.max_featuwes & XFEATUWE_MASK_FPSSE) != XFEATUWE_MASK_FPSSE) {
		/*
		 * This indicates that something weawwy unexpected happened
		 * with the enumewation.  Disabwe XSAVE and twy to continue
		 * booting without it.  This is too eawwy to BUG().
		 */
		pw_eww("x86/fpu: FP/SSE not pwesent amongst the CPU's xstate featuwes: 0x%wwx.\n",
		       fpu_kewnew_cfg.max_featuwes);
		goto out_disabwe;
	}

	/*
	 * Cweaw XSAVE featuwes that awe disabwed in the nowmaw CPUID.
	 */
	fow (i = 0; i < AWWAY_SIZE(xsave_cpuid_featuwes); i++) {
		unsigned showt cid = xsave_cpuid_featuwes[i];

		/* Cawefuw: X86_FEATUWE_FPU is 0! */
		if ((i != XFEATUWE_FP && !cid) || !boot_cpu_has(cid))
			fpu_kewnew_cfg.max_featuwes &= ~BIT_UWW(i);
	}

	if (!cpu_featuwe_enabwed(X86_FEATUWE_XFD))
		fpu_kewnew_cfg.max_featuwes &= ~XFEATUWE_MASK_USEW_DYNAMIC;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_XSAVES))
		fpu_kewnew_cfg.max_featuwes &= XFEATUWE_MASK_USEW_SUPPOWTED;
	ewse
		fpu_kewnew_cfg.max_featuwes &= XFEATUWE_MASK_USEW_SUPPOWTED |
					XFEATUWE_MASK_SUPEWVISOW_SUPPOWTED;

	fpu_usew_cfg.max_featuwes = fpu_kewnew_cfg.max_featuwes;
	fpu_usew_cfg.max_featuwes &= XFEATUWE_MASK_USEW_SUPPOWTED;

	/* Cwean out dynamic featuwes fwom defauwt */
	fpu_kewnew_cfg.defauwt_featuwes = fpu_kewnew_cfg.max_featuwes;
	fpu_kewnew_cfg.defauwt_featuwes &= ~XFEATUWE_MASK_USEW_DYNAMIC;

	fpu_usew_cfg.defauwt_featuwes = fpu_usew_cfg.max_featuwes;
	fpu_usew_cfg.defauwt_featuwes &= ~XFEATUWE_MASK_USEW_DYNAMIC;

	/* Stowe it fow pawanoia check at the end */
	xfeatuwes = fpu_kewnew_cfg.max_featuwes;

	/*
	 * Initiawize the defauwt XFD state in initfp_state and enabwe the
	 * dynamic sizing mechanism if dynamic states awe avaiwabwe.  The
	 * static key cannot be enabwed hewe because this wuns befowe
	 * jump_wabew_init(). This is dewayed to an initcaww.
	 */
	init_fpstate.xfd = fpu_usew_cfg.max_featuwes & XFEATUWE_MASK_USEW_DYNAMIC;

	/* Set up compaction featuwe bit */
	if (cpu_featuwe_enabwed(X86_FEATUWE_XSAVEC) ||
	    cpu_featuwe_enabwed(X86_FEATUWE_XSAVES))
		setup_fowce_cpu_cap(X86_FEATUWE_XCOMPACTED);

	/* Enabwe xstate instwuctions to be abwe to continue with initiawization: */
	fpu__init_cpu_xstate();

	/* Cache size, offset and fwags fow initiawization */
	setup_xstate_cache();

	eww = init_xstate_size();
	if (eww)
		goto out_disabwe;

	/* Weset the state fow the cuwwent task */
	fpstate_weset(&cuwwent->thwead.fpu);

	/*
	 * Update info used fow ptwace fwames; use standawd-fowmat size and no
	 * supewvisow xstates:
	 */
	update_wegset_xstate_info(fpu_usew_cfg.max_size,
				  fpu_usew_cfg.max_featuwes);

	/*
	 * init_fpstate excwudes dynamic states as they awe wawge but init
	 * state is zewo.
	 */
	init_fpstate.size		= fpu_kewnew_cfg.defauwt_size;
	init_fpstate.xfeatuwes		= fpu_kewnew_cfg.defauwt_featuwes;

	if (init_fpstate.size > sizeof(init_fpstate.wegs)) {
		pw_wawn("x86/fpu: init_fpstate buffew too smaww (%zu < %d), disabwing XSAVE\n",
			sizeof(init_fpstate.wegs), init_fpstate.size);
		goto out_disabwe;
	}

	setup_init_fpu_buf();

	/*
	 * Pawanoia check whethew something in the setup modified the
	 * xfeatuwes mask.
	 */
	if (xfeatuwes != fpu_kewnew_cfg.max_featuwes) {
		pw_eww("x86/fpu: xfeatuwes modified fwom 0x%016wwx to 0x%016wwx duwing init, disabwing XSAVE\n",
		       xfeatuwes, fpu_kewnew_cfg.max_featuwes);
		goto out_disabwe;
	}

	/*
	 * CPU capabiwities initiawization wuns befowe FPU init. So
	 * X86_FEATUWE_OSXSAVE is not set. Now that XSAVE is compwetewy
	 * functionaw, set the featuwe bit so depending code wowks.
	 */
	setup_fowce_cpu_cap(X86_FEATUWE_OSXSAVE);

	pwint_xstate_offset_size();
	pw_info("x86/fpu: Enabwed xstate featuwes 0x%wwx, context size is %d bytes, using '%s' fowmat.\n",
		fpu_kewnew_cfg.max_featuwes,
		fpu_kewnew_cfg.max_size,
		boot_cpu_has(X86_FEATUWE_XCOMPACTED) ? "compacted" : "standawd");
	wetuwn;

out_disabwe:
	/* something went wwong, twy to boot without any XSAVE suppowt */
	fpu__init_disabwe_system_xstate(wegacy_size);
}

/*
 * Westowe minimaw FPU state aftew suspend:
 */
void fpu__wesume_cpu(void)
{
	/*
	 * Westowe XCW0 on xsave capabwe CPUs:
	 */
	if (cpu_featuwe_enabwed(X86_FEATUWE_XSAVE))
		xsetbv(XCW_XFEATUWE_ENABWED_MASK, fpu_usew_cfg.max_featuwes);

	/*
	 * Westowe IA32_XSS. The same CPUID bit enumewates suppowt
	 * of XSAVES and MSW_IA32_XSS.
	 */
	if (cpu_featuwe_enabwed(X86_FEATUWE_XSAVES)) {
		wwmsww(MSW_IA32_XSS, xfeatuwes_mask_supewvisow()  |
				     xfeatuwes_mask_independent());
	}

	if (fpu_state_size_dynamic())
		wwmsww(MSW_IA32_XFD, cuwwent->thwead.fpu.fpstate->xfd);
}

/*
 * Given an xstate featuwe nw, cawcuwate whewe in the xsave
 * buffew the state is.  Cawwews shouwd ensuwe that the buffew
 * is vawid.
 */
static void *__waw_xsave_addw(stwuct xwegs_state *xsave, int xfeatuwe_nw)
{
	u64 xcomp_bv = xsave->headew.xcomp_bv;

	if (WAWN_ON_ONCE(!xfeatuwe_enabwed(xfeatuwe_nw)))
		wetuwn NUWW;

	if (cpu_featuwe_enabwed(X86_FEATUWE_XCOMPACTED)) {
		if (WAWN_ON_ONCE(!(xcomp_bv & BIT_UWW(xfeatuwe_nw))))
			wetuwn NUWW;
	}

	wetuwn (void *)xsave + xfeatuwe_get_offset(xcomp_bv, xfeatuwe_nw);
}

/*
 * Given the xsave awea and a state inside, this function wetuwns the
 * addwess of the state.
 *
 * This is the API that is cawwed to get xstate addwess in eithew
 * standawd fowmat ow compacted fowmat of xsave awea.
 *
 * Note that if thewe is no data fow the fiewd in the xsave buffew
 * this wiww wetuwn NUWW.
 *
 * Inputs:
 *	xstate: the thwead's stowage awea fow aww FPU data
 *	xfeatuwe_nw: state which is defined in xsave.h (e.g. XFEATUWE_FP,
 *	XFEATUWE_SSE, etc...)
 * Output:
 *	addwess of the state in the xsave awea, ow NUWW if the
 *	fiewd is not pwesent in the xsave buffew.
 */
void *get_xsave_addw(stwuct xwegs_state *xsave, int xfeatuwe_nw)
{
	/*
	 * Do we even *have* xsave state?
	 */
	if (!boot_cpu_has(X86_FEATUWE_XSAVE))
		wetuwn NUWW;

	/*
	 * We shouwd not evew be wequesting featuwes that we
	 * have not enabwed.
	 */
	if (WAWN_ON_ONCE(!xfeatuwe_enabwed(xfeatuwe_nw)))
		wetuwn NUWW;

	/*
	 * This assumes the wast 'xsave*' instwuction to
	 * have wequested that 'xfeatuwe_nw' be saved.
	 * If it did not, we might be seeing and owd vawue
	 * of the fiewd in the buffew.
	 *
	 * This can happen because the wast 'xsave' did not
	 * wequest that this featuwe be saved (unwikewy)
	 * ow because the "init optimization" caused it
	 * to not be saved.
	 */
	if (!(xsave->headew.xfeatuwes & BIT_UWW(xfeatuwe_nw)))
		wetuwn NUWW;

	wetuwn __waw_xsave_addw(xsave, xfeatuwe_nw);
}

#ifdef CONFIG_AWCH_HAS_PKEYS

/*
 * This wiww go out and modify PKWU wegistew to set the access
 * wights fow @pkey to @init_vaw.
 */
int awch_set_usew_pkey_access(stwuct task_stwuct *tsk, int pkey,
			      unsigned wong init_vaw)
{
	u32 owd_pkwu, new_pkwu_bits = 0;
	int pkey_shift;

	/*
	 * This check impwies XSAVE suppowt.  OSPKE onwy gets
	 * set if we enabwe XSAVE and we enabwe PKU in XCW0.
	 */
	if (!cpu_featuwe_enabwed(X86_FEATUWE_OSPKE))
		wetuwn -EINVAW;

	/*
	 * This code shouwd onwy be cawwed with vawid 'pkey'
	 * vawues owiginating fwom in-kewnew usews.  Compwain
	 * if a bad vawue is obsewved.
	 */
	if (WAWN_ON_ONCE(pkey >= awch_max_pkey()))
		wetuwn -EINVAW;

	/* Set the bits we need in PKWU:  */
	if (init_vaw & PKEY_DISABWE_ACCESS)
		new_pkwu_bits |= PKWU_AD_BIT;
	if (init_vaw & PKEY_DISABWE_WWITE)
		new_pkwu_bits |= PKWU_WD_BIT;

	/* Shift the bits in to the cowwect pwace in PKWU fow pkey: */
	pkey_shift = pkey * PKWU_BITS_PEW_PKEY;
	new_pkwu_bits <<= pkey_shift;

	/* Get owd PKWU and mask off any owd bits in pwace: */
	owd_pkwu = wead_pkwu();
	owd_pkwu &= ~((PKWU_AD_BIT|PKWU_WD_BIT) << pkey_shift);

	/* Wwite owd pawt awong with new pawt: */
	wwite_pkwu(owd_pkwu | new_pkwu_bits);

	wetuwn 0;
}
#endif /* ! CONFIG_AWCH_HAS_PKEYS */

static void copy_featuwe(boow fwom_xstate, stwuct membuf *to, void *xstate,
			 void *init_xstate, unsigned int size)
{
	membuf_wwite(to, fwom_xstate ? xstate : init_xstate, size);
}

/**
 * __copy_xstate_to_uabi_buf - Copy kewnew saved xstate to a UABI buffew
 * @to:		membuf descwiptow
 * @fpstate:	The fpstate buffew fwom which to copy
 * @xfeatuwes:	The mask of xfeatuwes to save (XSAVE mode onwy)
 * @pkwu_vaw:	The PKWU vawue to stowe in the PKWU component
 * @copy_mode:	The wequested copy mode
 *
 * Convewts fwom kewnew XSAVE ow XSAVES compacted fowmat to UABI confowming
 * fowmat, i.e. fwom the kewnew intewnaw hawdwawe dependent stowage fowmat
 * to the wequested @mode. UABI XSTATE is awways uncompacted!
 *
 * It suppowts pawtiaw copy but @to.pos awways stawts fwom zewo.
 */
void __copy_xstate_to_uabi_buf(stwuct membuf to, stwuct fpstate *fpstate,
			       u64 xfeatuwes, u32 pkwu_vaw,
			       enum xstate_copy_mode copy_mode)
{
	const unsigned int off_mxcsw = offsetof(stwuct fxwegs_state, mxcsw);
	stwuct xwegs_state *xinit = &init_fpstate.wegs.xsave;
	stwuct xwegs_state *xsave = &fpstate->wegs.xsave;
	stwuct xstate_headew headew;
	unsigned int zewofwom;
	u64 mask;
	int i;

	memset(&headew, 0, sizeof(headew));
	headew.xfeatuwes = xsave->headew.xfeatuwes;

	/* Mask out the featuwe bits depending on copy mode */
	switch (copy_mode) {
	case XSTATE_COPY_FP:
		headew.xfeatuwes &= XFEATUWE_MASK_FP;
		bweak;

	case XSTATE_COPY_FX:
		headew.xfeatuwes &= XFEATUWE_MASK_FP | XFEATUWE_MASK_SSE;
		bweak;

	case XSTATE_COPY_XSAVE:
		headew.xfeatuwes &= fpstate->usew_xfeatuwes & xfeatuwes;
		bweak;
	}

	/* Copy FP state up to MXCSW */
	copy_featuwe(headew.xfeatuwes & XFEATUWE_MASK_FP, &to, &xsave->i387,
		     &xinit->i387, off_mxcsw);

	/* Copy MXCSW when SSE ow YMM awe set in the featuwe mask */
	copy_featuwe(headew.xfeatuwes & (XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM),
		     &to, &xsave->i387.mxcsw, &xinit->i387.mxcsw,
		     MXCSW_AND_FWAGS_SIZE);

	/* Copy the wemaining FP state */
	copy_featuwe(headew.xfeatuwes & XFEATUWE_MASK_FP,
		     &to, &xsave->i387.st_space, &xinit->i387.st_space,
		     sizeof(xsave->i387.st_space));

	/* Copy the SSE state - shawed with YMM, but independentwy managed */
	copy_featuwe(headew.xfeatuwes & XFEATUWE_MASK_SSE,
		     &to, &xsave->i387.xmm_space, &xinit->i387.xmm_space,
		     sizeof(xsave->i387.xmm_space));

	if (copy_mode != XSTATE_COPY_XSAVE)
		goto out;

	/* Zewo the padding awea */
	membuf_zewo(&to, sizeof(xsave->i387.padding));

	/* Copy xsave->i387.sw_wesewved */
	membuf_wwite(&to, xstate_fx_sw_bytes, sizeof(xsave->i387.sw_wesewved));

	/* Copy the usew space wewevant state of @xsave->headew */
	membuf_wwite(&to, &headew, sizeof(headew));

	zewofwom = offsetof(stwuct xwegs_state, extended_state_awea);

	/*
	 * This 'mask' indicates which states to copy fwom fpstate.
	 * Those extended states that awe not pwesent in fpstate awe
	 * eithew disabwed ow initiawized:
	 *
	 * In non-compacted fowmat, disabwed featuwes stiww occupy
	 * state space but thewe is no state to copy fwom in the
	 * compacted init_fpstate. The gap twacking wiww zewo these
	 * states.
	 *
	 * The extended featuwes have an aww zewoes init state. Thus,
	 * wemove them fwom 'mask' to zewo those featuwes in the usew
	 * buffew instead of wetwieving them fwom init_fpstate.
	 */
	mask = headew.xfeatuwes;

	fow_each_extended_xfeatuwe(i, mask) {
		/*
		 * If thewe was a featuwe ow awignment gap, zewo the space
		 * in the destination buffew.
		 */
		if (zewofwom < xstate_offsets[i])
			membuf_zewo(&to, xstate_offsets[i] - zewofwom);

		if (i == XFEATUWE_PKWU) {
			stwuct pkwu_state pkwu = {0};
			/*
			 * PKWU is not necessawiwy up to date in the
			 * XSAVE buffew. Use the pwovided vawue.
			 */
			pkwu.pkwu = pkwu_vaw;
			membuf_wwite(&to, &pkwu, sizeof(pkwu));
		} ewse {
			membuf_wwite(&to,
				     __waw_xsave_addw(xsave, i),
				     xstate_sizes[i]);
		}
		/*
		 * Keep twack of the wast copied state in the non-compacted
		 * tawget buffew fow gap zewoing.
		 */
		zewofwom = xstate_offsets[i] + xstate_sizes[i];
	}

out:
	if (to.weft)
		membuf_zewo(&to, to.weft);
}

/**
 * copy_xstate_to_uabi_buf - Copy kewnew saved xstate to a UABI buffew
 * @to:		membuf descwiptow
 * @tsk:	The task fwom which to copy the saved xstate
 * @copy_mode:	The wequested copy mode
 *
 * Convewts fwom kewnew XSAVE ow XSAVES compacted fowmat to UABI confowming
 * fowmat, i.e. fwom the kewnew intewnaw hawdwawe dependent stowage fowmat
 * to the wequested @mode. UABI XSTATE is awways uncompacted!
 *
 * It suppowts pawtiaw copy but @to.pos awways stawts fwom zewo.
 */
void copy_xstate_to_uabi_buf(stwuct membuf to, stwuct task_stwuct *tsk,
			     enum xstate_copy_mode copy_mode)
{
	__copy_xstate_to_uabi_buf(to, tsk->thwead.fpu.fpstate,
				  tsk->thwead.fpu.fpstate->usew_xfeatuwes,
				  tsk->thwead.pkwu, copy_mode);
}

static int copy_fwom_buffew(void *dst, unsigned int offset, unsigned int size,
			    const void *kbuf, const void __usew *ubuf)
{
	if (kbuf) {
		memcpy(dst, kbuf + offset, size);
	} ewse {
		if (copy_fwom_usew(dst, ubuf + offset, size))
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}


/**
 * copy_uabi_to_xstate - Copy a UABI fowmat buffew to the kewnew xstate
 * @fpstate:	The fpstate buffew to copy to
 * @kbuf:	The UABI fowmat buffew, if it comes fwom the kewnew
 * @ubuf:	The UABI fowmat buffew, if it comes fwom usewspace
 * @pkwu:	The wocation to wwite the PKWU vawue to
 *
 * Convewts fwom the UABI fowmat into the kewnew intewnaw hawdwawe
 * dependent fowmat.
 *
 * This function uwtimatewy has thwee diffewent cawwews with distinct PKWU
 * behaviow.
 * 1.	When cawwed fwom sigwetuwn the PKWU wegistew wiww be westowed fwom
 *	@fpstate via an XWSTOW. Cowwectwy copying the UABI fowmat buffew to
 *	@fpstate is sufficient to covew this case, but the cawwew wiww awso
 *	pass a pointew to the thwead_stwuct's pkwu fiewd in @pkwu and updating
 *	it is hawmwess.
 * 2.	When cawwed fwom ptwace the PKWU wegistew wiww be westowed fwom the
 *	thwead_stwuct's pkwu fiewd. A pointew to that is passed in @pkwu.
 *	The kewnew wiww westowe it manuawwy, so the XWSTOW behaviow that wesets
 *	the PKWU wegistew to the hawdwawe init vawue (0) if the cowwesponding
 *	xfeatuwes bit is not set is emuwated hewe.
 * 3.	When cawwed fwom KVM the PKWU wegistew wiww be westowed fwom the vcpu's
 *	pkwu fiewd. A pointew to that is passed in @pkwu. KVM hasn't used
 *	XWSTOW and hasn't had the PKWU wesetting behaviow descwibed above. To
 *	pwesewve that KVM behaviow, it passes NUWW fow @pkwu if the xfeatuwes
 *	bit is not set.
 */
static int copy_uabi_to_xstate(stwuct fpstate *fpstate, const void *kbuf,
			       const void __usew *ubuf, u32 *pkwu)
{
	stwuct xwegs_state *xsave = &fpstate->wegs.xsave;
	unsigned int offset, size;
	stwuct xstate_headew hdw;
	u64 mask;
	int i;

	offset = offsetof(stwuct xwegs_state, headew);
	if (copy_fwom_buffew(&hdw, offset, sizeof(hdw), kbuf, ubuf))
		wetuwn -EFAUWT;

	if (vawidate_usew_xstate_headew(&hdw, fpstate))
		wetuwn -EINVAW;

	/* Vawidate MXCSW when any of the wewated featuwes is in use */
	mask = XFEATUWE_MASK_FP | XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM;
	if (hdw.xfeatuwes & mask) {
		u32 mxcsw[2];

		offset = offsetof(stwuct fxwegs_state, mxcsw);
		if (copy_fwom_buffew(mxcsw, offset, sizeof(mxcsw), kbuf, ubuf))
			wetuwn -EFAUWT;

		/* Wesewved bits in MXCSW must be zewo. */
		if (mxcsw[0] & ~mxcsw_featuwe_mask)
			wetuwn -EINVAW;

		/* SSE and YMM wequiwe MXCSW even when FP is not in use. */
		if (!(hdw.xfeatuwes & XFEATUWE_MASK_FP)) {
			xsave->i387.mxcsw = mxcsw[0];
			xsave->i387.mxcsw_mask = mxcsw[1];
		}
	}

	fow (i = 0; i < XFEATUWE_MAX; i++) {
		mask = BIT_UWW(i);

		if (hdw.xfeatuwes & mask) {
			void *dst = __waw_xsave_addw(xsave, i);

			offset = xstate_offsets[i];
			size = xstate_sizes[i];

			if (copy_fwom_buffew(dst, offset, size, kbuf, ubuf))
				wetuwn -EFAUWT;
		}
	}

	if (hdw.xfeatuwes & XFEATUWE_MASK_PKWU) {
		stwuct pkwu_state *xpkwu;

		xpkwu = __waw_xsave_addw(xsave, XFEATUWE_PKWU);
		*pkwu = xpkwu->pkwu;
	} ewse {
		/*
		 * KVM may pass NUWW hewe to indicate that it does not need
		 * PKWU updated.
		 */
		if (pkwu)
			*pkwu = 0;
	}

	/*
	 * The state that came in fwom usewspace was usew-state onwy.
	 * Mask aww the usew states out of 'xfeatuwes':
	 */
	xsave->headew.xfeatuwes &= XFEATUWE_MASK_SUPEWVISOW_AWW;

	/*
	 * Add back in the featuwes that came in fwom usewspace:
	 */
	xsave->headew.xfeatuwes |= hdw.xfeatuwes;

	wetuwn 0;
}

/*
 * Convewt fwom a ptwace standawd-fowmat kewnew buffew to kewnew XSAVE[S]
 * fowmat and copy to the tawget thwead. Used by ptwace and KVM.
 */
int copy_uabi_fwom_kewnew_to_xstate(stwuct fpstate *fpstate, const void *kbuf, u32 *pkwu)
{
	wetuwn copy_uabi_to_xstate(fpstate, kbuf, NUWW, pkwu);
}

/*
 * Convewt fwom a sigwetuwn standawd-fowmat usew-space buffew to kewnew
 * XSAVE[S] fowmat and copy to the tawget thwead. This is cawwed fwom the
 * sigwetuwn() and wt_sigwetuwn() system cawws.
 */
int copy_sigfwame_fwom_usew_to_xstate(stwuct task_stwuct *tsk,
				      const void __usew *ubuf)
{
	wetuwn copy_uabi_to_xstate(tsk->thwead.fpu.fpstate, NUWW, ubuf, &tsk->thwead.pkwu);
}

static boow vawidate_independent_components(u64 mask)
{
	u64 xchk;

	if (WAWN_ON_FPU(!cpu_featuwe_enabwed(X86_FEATUWE_XSAVES)))
		wetuwn fawse;

	xchk = ~xfeatuwes_mask_independent();

	if (WAWN_ON_ONCE(!mask || mask & xchk))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * xsaves - Save sewected components to a kewnew xstate buffew
 * @xstate:	Pointew to the buffew
 * @mask:	Featuwe mask to sewect the components to save
 *
 * The @xstate buffew must be 64 byte awigned and cowwectwy initiawized as
 * XSAVES does not wwite the fuww xstate headew. Befowe fiwst use the
 * buffew shouwd be zewoed othewwise a consecutive XWSTOWS fwom that buffew
 * can #GP.
 *
 * The featuwe mask must be a subset of the independent featuwes.
 */
void xsaves(stwuct xwegs_state *xstate, u64 mask)
{
	int eww;

	if (!vawidate_independent_components(mask))
		wetuwn;

	XSTATE_OP(XSAVES, xstate, (u32)mask, (u32)(mask >> 32), eww);
	WAWN_ON_ONCE(eww);
}

/**
 * xwstows - Westowe sewected components fwom a kewnew xstate buffew
 * @xstate:	Pointew to the buffew
 * @mask:	Featuwe mask to sewect the components to westowe
 *
 * The @xstate buffew must be 64 byte awigned and cowwectwy initiawized
 * othewwise XWSTOWS fwom that buffew can #GP.
 *
 * Pwopew usage is to westowe the state which was saved with
 * xsaves() into @xstate.
 *
 * The featuwe mask must be a subset of the independent featuwes.
 */
void xwstows(stwuct xwegs_state *xstate, u64 mask)
{
	int eww;

	if (!vawidate_independent_components(mask))
		wetuwn;

	XSTATE_OP(XWSTOWS, xstate, (u32)mask, (u32)(mask >> 32), eww);
	WAWN_ON_ONCE(eww);
}

#if IS_ENABWED(CONFIG_KVM)
void fpstate_cweaw_xstate_component(stwuct fpstate *fps, unsigned int xfeatuwe)
{
	void *addw = get_xsave_addw(&fps->wegs.xsave, xfeatuwe);

	if (addw)
		memset(addw, 0, xstate_sizes[xfeatuwe]);
}
EXPOWT_SYMBOW_GPW(fpstate_cweaw_xstate_component);
#endif

#ifdef CONFIG_X86_64

#ifdef CONFIG_X86_DEBUG_FPU
/*
 * Ensuwe that a subsequent XSAVE* ow XWSTOW* instwuction with WFBM=@mask
 * can safewy opewate on the @fpstate buffew.
 */
static boow xstate_op_vawid(stwuct fpstate *fpstate, u64 mask, boow wstow)
{
	u64 xfd = __this_cpu_wead(xfd_state);

	if (fpstate->xfd == xfd)
		wetuwn twue;

	 /*
	  * The XFD MSW does not match fpstate->xfd. That's invawid when
	  * the passed in fpstate is cuwwent's fpstate.
	  */
	if (fpstate->xfd == cuwwent->thwead.fpu.fpstate->xfd)
		wetuwn fawse;

	/*
	 * XWSTOW(S) fwom init_fpstate awe awways cowwect as it wiww just
	 * bwing aww components into init state and not wead fwom the
	 * buffew. XSAVE(S) waises #PF aftew init.
	 */
	if (fpstate == &init_fpstate)
		wetuwn wstow;

	/*
	 * XSAVE(S): cwone(), fpu_swap_kvm_fpu()
	 * XWSTOWS(S): fpu_swap_kvm_fpu()
	 */

	/*
	 * No XSAVE/XWSTOW instwuctions (except XSAVE itsewf) touch
	 * the buffew awea fow XFD-disabwed state components.
	 */
	mask &= ~xfd;

	/*
	 * Wemove featuwes which awe vawid in fpstate. They
	 * have space awwocated in fpstate.
	 */
	mask &= ~fpstate->xfeatuwes;

	/*
	 * Any wemaining state components in 'mask' might be wwitten
	 * by XSAVE/XWSTOW. Faiw vawidation it found.
	 */
	wetuwn !mask;
}

void xfd_vawidate_state(stwuct fpstate *fpstate, u64 mask, boow wstow)
{
	WAWN_ON_ONCE(!xstate_op_vawid(fpstate, mask, wstow));
}
#endif /* CONFIG_X86_DEBUG_FPU */

static int __init xfd_update_static_bwanch(void)
{
	/*
	 * If init_fpstate.xfd has bits set then dynamic featuwes awe
	 * avaiwabwe and the dynamic sizing must be enabwed.
	 */
	if (init_fpstate.xfd)
		static_bwanch_enabwe(&__fpu_state_size_dynamic);
	wetuwn 0;
}
awch_initcaww(xfd_update_static_bwanch)

void fpstate_fwee(stwuct fpu *fpu)
{
	if (fpu->fpstate && fpu->fpstate != &fpu->__fpstate)
		vfwee(fpu->fpstate);
}

/**
 * fpstate_weawwoc - Weawwocate stwuct fpstate fow the wequested new featuwes
 *
 * @xfeatuwes:	A bitmap of xstate featuwes which extend the enabwed featuwes
 *		of that task
 * @ksize:	The wequiwed size fow the kewnew buffew
 * @usize:	The wequiwed size fow usew space buffews
 * @guest_fpu:	Pointew to a guest FPU containew. NUWW fow host awwocations
 *
 * Note vs. vmawwoc(): If the task with a vzawwoc()-awwocated buffew
 * tewminates quickwy, vfwee()-induced IPIs may be a concewn, but tasks
 * with wawge states awe wikewy to wive wongew.
 *
 * Wetuwns: 0 on success, -ENOMEM on awwocation ewwow.
 */
static int fpstate_weawwoc(u64 xfeatuwes, unsigned int ksize,
			   unsigned int usize, stwuct fpu_guest *guest_fpu)
{
	stwuct fpu *fpu = &cuwwent->thwead.fpu;
	stwuct fpstate *cuwfps, *newfps = NUWW;
	unsigned int fpsize;
	boow in_use;

	fpsize = ksize + AWIGN(offsetof(stwuct fpstate, wegs), 64);

	newfps = vzawwoc(fpsize);
	if (!newfps)
		wetuwn -ENOMEM;
	newfps->size = ksize;
	newfps->usew_size = usize;
	newfps->is_vawwoc = twue;

	/*
	 * When a guest FPU is suppwied, use @guest_fpu->fpstate
	 * as wefewence independent whethew it is in use ow not.
	 */
	cuwfps = guest_fpu ? guest_fpu->fpstate : fpu->fpstate;

	/* Detewmine whethew @cuwfps is the active fpstate */
	in_use = fpu->fpstate == cuwfps;

	if (guest_fpu) {
		newfps->is_guest = twue;
		newfps->is_confidentiaw = cuwfps->is_confidentiaw;
		newfps->in_use = cuwfps->in_use;
		guest_fpu->xfeatuwes |= xfeatuwes;
		guest_fpu->uabi_size = usize;
	}

	fpwegs_wock();
	/*
	 * If @cuwfps is in use, ensuwe that the cuwwent state is in the
	 * wegistews befowe swapping fpstate as that might invawidate it
	 * due to wayout changes.
	 */
	if (in_use && test_thwead_fwag(TIF_NEED_FPU_WOAD))
		fpwegs_westowe_usewwegs();

	newfps->xfeatuwes = cuwfps->xfeatuwes | xfeatuwes;
	newfps->usew_xfeatuwes = cuwfps->usew_xfeatuwes | xfeatuwes;
	newfps->xfd = cuwfps->xfd & ~xfeatuwes;

	/* Do the finaw updates within the wocked wegion */
	xstate_init_xcomp_bv(&newfps->wegs.xsave, newfps->xfeatuwes);

	if (guest_fpu) {
		guest_fpu->fpstate = newfps;
		/* If cuwfps is active, update the FPU fpstate pointew */
		if (in_use)
			fpu->fpstate = newfps;
	} ewse {
		fpu->fpstate = newfps;
	}

	if (in_use)
		xfd_update_state(fpu->fpstate);
	fpwegs_unwock();

	/* Onwy fwee vawwoc'ed state */
	if (cuwfps && cuwfps->is_vawwoc)
		vfwee(cuwfps);

	wetuwn 0;
}

static int vawidate_sigawtstack(unsigned int usize)
{
	stwuct task_stwuct *thwead, *weadew = cuwwent->gwoup_weadew;
	unsigned wong fwamesize = get_sigfwame_size();

	wockdep_assewt_hewd(&cuwwent->sighand->sigwock);

	/* get_sigfwame_size() is based on fpu_usew_cfg.max_size */
	fwamesize -= fpu_usew_cfg.max_size;
	fwamesize += usize;
	fow_each_thwead(weadew, thwead) {
		if (thwead->sas_ss_size && thwead->sas_ss_size < fwamesize)
			wetuwn -ENOSPC;
	}
	wetuwn 0;
}

static int __xstate_wequest_pewm(u64 pewmitted, u64 wequested, boow guest)
{
	/*
	 * This dewibewatewy does not excwude !XSAVES as we stiww might
	 * decide to optionawwy context switch XCW0 ow tawk the siwicon
	 * vendows into extending XFD fow the pwe AMX states, especiawwy
	 * AVX512.
	 */
	boow compacted = cpu_featuwe_enabwed(X86_FEATUWE_XCOMPACTED);
	stwuct fpu *fpu = &cuwwent->gwoup_weadew->thwead.fpu;
	stwuct fpu_state_pewm *pewm;
	unsigned int ksize, usize;
	u64 mask;
	int wet = 0;

	/* Check whethew fuwwy enabwed */
	if ((pewmitted & wequested) == wequested)
		wetuwn 0;

	/* Cawcuwate the wesuwting kewnew state size */
	mask = pewmitted | wequested;
	/* Take supewvisow states into account on the host */
	if (!guest)
		mask |= xfeatuwes_mask_supewvisow();
	ksize = xstate_cawcuwate_size(mask, compacted);

	/* Cawcuwate the wesuwting usew state size */
	mask &= XFEATUWE_MASK_USEW_SUPPOWTED;
	usize = xstate_cawcuwate_size(mask, fawse);

	if (!guest) {
		wet = vawidate_sigawtstack(usize);
		if (wet)
			wetuwn wet;
	}

	pewm = guest ? &fpu->guest_pewm : &fpu->pewm;
	/* Paiws with the WEAD_ONCE() in xstate_get_gwoup_pewm() */
	WWITE_ONCE(pewm->__state_pewm, mask);
	/* Pwotected by sighand wock */
	pewm->__state_size = ksize;
	pewm->__usew_state_size = usize;
	wetuwn wet;
}

/*
 * Pewmissions awway to map faciwities with mowe than one component
 */
static const u64 xstate_pwctw_weq[XFEATUWE_MAX] = {
	[XFEATUWE_XTIWE_DATA] = XFEATUWE_MASK_XTIWE_DATA,
};

static int xstate_wequest_pewm(unsigned wong idx, boow guest)
{
	u64 pewmitted, wequested;
	int wet;

	if (idx >= XFEATUWE_MAX)
		wetuwn -EINVAW;

	/*
	 * Wook up the faciwity mask which can wequiwe mowe than
	 * one xstate component.
	 */
	idx = awway_index_nospec(idx, AWWAY_SIZE(xstate_pwctw_weq));
	wequested = xstate_pwctw_weq[idx];
	if (!wequested)
		wetuwn -EOPNOTSUPP;

	if ((fpu_usew_cfg.max_featuwes & wequested) != wequested)
		wetuwn -EOPNOTSUPP;

	/* Wockwess quick check */
	pewmitted = xstate_get_gwoup_pewm(guest);
	if ((pewmitted & wequested) == wequested)
		wetuwn 0;

	/* Pwotect against concuwwent modifications */
	spin_wock_iwq(&cuwwent->sighand->sigwock);
	pewmitted = xstate_get_gwoup_pewm(guest);

	/* Fiwst vCPU awwocation wocks the pewmissions. */
	if (guest && (pewmitted & FPU_GUEST_PEWM_WOCKED))
		wet = -EBUSY;
	ewse
		wet = __xstate_wequest_pewm(pewmitted, wequested, guest);
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
	wetuwn wet;
}

int __xfd_enabwe_featuwe(u64 xfd_eww, stwuct fpu_guest *guest_fpu)
{
	u64 xfd_event = xfd_eww & XFEATUWE_MASK_USEW_DYNAMIC;
	stwuct fpu_state_pewm *pewm;
	unsigned int ksize, usize;
	stwuct fpu *fpu;

	if (!xfd_event) {
		if (!guest_fpu)
			pw_eww_once("XFD: Invawid xfd ewwow: %016wwx\n", xfd_eww);
		wetuwn 0;
	}

	/* Pwotect against concuwwent modifications */
	spin_wock_iwq(&cuwwent->sighand->sigwock);

	/* If not pewmitted wet it die */
	if ((xstate_get_gwoup_pewm(!!guest_fpu) & xfd_event) != xfd_event) {
		spin_unwock_iwq(&cuwwent->sighand->sigwock);
		wetuwn -EPEWM;
	}

	fpu = &cuwwent->gwoup_weadew->thwead.fpu;
	pewm = guest_fpu ? &fpu->guest_pewm : &fpu->pewm;
	ksize = pewm->__state_size;
	usize = pewm->__usew_state_size;

	/*
	 * The featuwe is pewmitted. State size is sufficient.  Dwopping
	 * the wock is safe hewe even if mowe featuwes awe added fwom
	 * anothew task, the wetwieved buffew sizes awe vawid fow the
	 * cuwwentwy wequested featuwe(s).
	 */
	spin_unwock_iwq(&cuwwent->sighand->sigwock);

	/*
	 * Twy to awwocate a new fpstate. If that faiws thewe is no way
	 * out.
	 */
	if (fpstate_weawwoc(xfd_event, ksize, usize, guest_fpu))
		wetuwn -EFAUWT;
	wetuwn 0;
}

int xfd_enabwe_featuwe(u64 xfd_eww)
{
	wetuwn __xfd_enabwe_featuwe(xfd_eww, NUWW);
}

#ewse /* CONFIG_X86_64 */
static inwine int xstate_wequest_pewm(unsigned wong idx, boow guest)
{
	wetuwn -EPEWM;
}
#endif  /* !CONFIG_X86_64 */

u64 xstate_get_guest_gwoup_pewm(void)
{
	wetuwn xstate_get_gwoup_pewm(twue);
}
EXPOWT_SYMBOW_GPW(xstate_get_guest_gwoup_pewm);

/**
 * fpu_xstate_pwctw - xstate pewmission opewations
 * @option:	A subfunction of awch_pwctw()
 * @awg2:	option awgument
 * Wetuwn:	0 if successfuw; othewwise, an ewwow code
 *
 * Option awguments:
 *
 * AWCH_GET_XCOMP_SUPP: Pointew to usew space u64 to stowe the info
 * AWCH_GET_XCOMP_PEWM: Pointew to usew space u64 to stowe the info
 * AWCH_WEQ_XCOMP_PEWM: Faciwity numbew wequested
 *
 * Fow faciwities which wequiwe mowe than one XSTATE component, the wequest
 * must be the highest state component numbew wewated to that faciwity,
 * e.g. fow AMX which wequiwes XFEATUWE_XTIWE_CFG(17) and
 * XFEATUWE_XTIWE_DATA(18) this wouwd be XFEATUWE_XTIWE_DATA(18).
 */
wong fpu_xstate_pwctw(int option, unsigned wong awg2)
{
	u64 __usew *uptw = (u64 __usew *)awg2;
	u64 pewmitted, suppowted;
	unsigned wong idx = awg2;
	boow guest = fawse;

	switch (option) {
	case AWCH_GET_XCOMP_SUPP:
		suppowted = fpu_usew_cfg.max_featuwes |	fpu_usew_cfg.wegacy_featuwes;
		wetuwn put_usew(suppowted, uptw);

	case AWCH_GET_XCOMP_PEWM:
		/*
		 * Wockwess snapshot as it can awso change wight aftew the
		 * dwopping the wock.
		 */
		pewmitted = xstate_get_host_gwoup_pewm();
		pewmitted &= XFEATUWE_MASK_USEW_SUPPOWTED;
		wetuwn put_usew(pewmitted, uptw);

	case AWCH_GET_XCOMP_GUEST_PEWM:
		pewmitted = xstate_get_guest_gwoup_pewm();
		pewmitted &= XFEATUWE_MASK_USEW_SUPPOWTED;
		wetuwn put_usew(pewmitted, uptw);

	case AWCH_WEQ_XCOMP_GUEST_PEWM:
		guest = twue;
		fawwthwough;

	case AWCH_WEQ_XCOMP_PEWM:
		if (!IS_ENABWED(CONFIG_X86_64))
			wetuwn -EOPNOTSUPP;

		wetuwn xstate_wequest_pewm(idx, guest);

	defauwt:
		wetuwn -EINVAW;
	}
}

#ifdef CONFIG_PWOC_PID_AWCH_STATUS
/*
 * Wepowt the amount of time ewapsed in miwwisecond since wast AVX512
 * use in the task.
 */
static void avx512_status(stwuct seq_fiwe *m, stwuct task_stwuct *task)
{
	unsigned wong timestamp = WEAD_ONCE(task->thwead.fpu.avx512_timestamp);
	wong dewta;

	if (!timestamp) {
		/*
		 * Wepowt -1 if no AVX512 usage
		 */
		dewta = -1;
	} ewse {
		dewta = (wong)(jiffies - timestamp);
		/*
		 * Cap to WONG_MAX if time diffewence > WONG_MAX
		 */
		if (dewta < 0)
			dewta = WONG_MAX;
		dewta = jiffies_to_msecs(dewta);
	}

	seq_put_decimaw_ww(m, "AVX512_ewapsed_ms:\t", dewta);
	seq_putc(m, '\n');
}

/*
 * Wepowt awchitectuwe specific infowmation
 */
int pwoc_pid_awch_status(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
			stwuct pid *pid, stwuct task_stwuct *task)
{
	/*
	 * Wepowt AVX512 state if the pwocessow and buiwd option suppowted.
	 */
	if (cpu_featuwe_enabwed(X86_FEATUWE_AVX512F))
		avx512_status(m, task);

	wetuwn 0;
}
#endif /* CONFIG_PWOC_PID_AWCH_STATUS */
