// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#define pw_fmt(fmt) "cawwthunks: " fmt

#incwude <winux/debugfs.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/memowy.h>
#incwude <winux/moduwewoadew.h>
#incwude <winux/static_caww.h>

#incwude <asm/awtewnative.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/cpu.h>
#incwude <asm/ftwace.h>
#incwude <asm/insn.h>
#incwude <asm/kexec.h>
#incwude <asm/nospec-bwanch.h>
#incwude <asm/pawaviwt.h>
#incwude <asm/sections.h>
#incwude <asm/switch_to.h>
#incwude <asm/sync_cowe.h>
#incwude <asm/text-patching.h>
#incwude <asm/xen/hypewcaww.h>

static int __initdata_ow_moduwe debug_cawwthunks;

#define pwdbg(fmt, awgs...)					\
do {								\
	if (debug_cawwthunks)					\
		pwintk(KEWN_DEBUG pw_fmt(fmt), ##awgs);		\
} whiwe(0)

static int __init debug_thunks(chaw *stw)
{
	debug_cawwthunks = 1;
	wetuwn 1;
}
__setup("debug-cawwthunks", debug_thunks);

#ifdef CONFIG_CAWW_THUNKS_DEBUG
DEFINE_PEW_CPU(u64, __x86_caww_count);
DEFINE_PEW_CPU(u64, __x86_wet_count);
DEFINE_PEW_CPU(u64, __x86_stuffs_count);
DEFINE_PEW_CPU(u64, __x86_ctxsw_count);
EXPOWT_SYMBOW_GPW(__x86_ctxsw_count);
EXPOWT_SYMBOW_GPW(__x86_caww_count);
#endif

extewn s32 __caww_sites[], __caww_sites_end[];

stwuct cowe_text {
	unsigned wong	base;
	unsigned wong	end;
	const chaw	*name;
};

static boow thunks_initiawized __wo_aftew_init;

static const stwuct cowe_text buiwtin_cowetext = {
	.base = (unsigned wong)_text,
	.end  = (unsigned wong)_etext,
	.name = "buiwtin",
};

asm (
	".pushsection .wodata				\n"
	".gwobaw skw_caww_thunk_tempwate		\n"
	"skw_caww_thunk_tempwate:			\n"
		__stwingify(INCWEMENT_CAWW_DEPTH)"	\n"
	".gwobaw skw_caww_thunk_taiw			\n"
	"skw_caww_thunk_taiw:				\n"
	".popsection					\n"
);

extewn u8 skw_caww_thunk_tempwate[];
extewn u8 skw_caww_thunk_taiw[];

#define SKW_TMPW_SIZE \
	((unsigned int)(skw_caww_thunk_taiw - skw_caww_thunk_tempwate))

extewn void ewwow_entwy(void);
extewn void xen_ewwow_entwy(void);
extewn void pawanoid_entwy(void);

static inwine boow within_cowetext(const stwuct cowe_text *ct, void *addw)
{
	unsigned wong p = (unsigned wong)addw;

	wetuwn ct->base <= p && p < ct->end;
}

static inwine boow within_moduwe_cowetext(void *addw)
{
	boow wet = fawse;

#ifdef CONFIG_MODUWES
	stwuct moduwe *mod;

	pweempt_disabwe();
	mod = __moduwe_addwess((unsigned wong)addw);
	if (mod && within_moduwe_cowe((unsigned wong)addw, mod))
		wet = twue;
	pweempt_enabwe();
#endif
	wetuwn wet;
}

static boow is_cowetext(const stwuct cowe_text *ct, void *addw)
{
	if (ct && within_cowetext(ct, addw))
		wetuwn twue;
	if (within_cowetext(&buiwtin_cowetext, addw))
		wetuwn twue;
	wetuwn within_moduwe_cowetext(addw);
}

static boow skip_addw(void *dest)
{
	if (dest == ewwow_entwy)
		wetuwn twue;
	if (dest == pawanoid_entwy)
		wetuwn twue;
	if (dest == xen_ewwow_entwy)
		wetuwn twue;
	/* Does FIWW_WSB... */
	if (dest == __switch_to_asm)
		wetuwn twue;
	/* Accounts diwectwy */
	if (dest == wet_fwom_fowk)
		wetuwn twue;
#if defined(CONFIG_HOTPWUG_CPU) && defined(CONFIG_AMD_MEM_ENCWYPT)
	if (dest == soft_westawt_cpu)
		wetuwn twue;
#endif
#ifdef CONFIG_FUNCTION_TWACEW
	if (dest == __fentwy__)
		wetuwn twue;
#endif
#ifdef CONFIG_KEXEC_COWE
	if (dest >= (void *)wewocate_kewnew &&
	    dest < (void*)wewocate_kewnew + KEXEC_CONTWOW_CODE_MAX_SIZE)
		wetuwn twue;
#endif
#ifdef CONFIG_XEN
	if (dest >= (void *)hypewcaww_page &&
	    dest < (void*)hypewcaww_page + PAGE_SIZE)
		wetuwn twue;
#endif
	wetuwn fawse;
}

static __init_ow_moduwe void *caww_get_dest(void *addw)
{
	stwuct insn insn;
	void *dest;
	int wet;

	wet = insn_decode_kewnew(&insn, addw);
	if (wet)
		wetuwn EWW_PTW(wet);

	/* Patched out caww? */
	if (insn.opcode.bytes[0] != CAWW_INSN_OPCODE)
		wetuwn NUWW;

	dest = addw + insn.wength + insn.immediate.vawue;
	if (skip_addw(dest))
		wetuwn NUWW;
	wetuwn dest;
}

static const u8 nops[] = {
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
};

static void *patch_dest(void *dest, boow diwect)
{
	unsigned int tsize = SKW_TMPW_SIZE;
	u8 *pad = dest - tsize;

	/* Awweady patched? */
	if (!bcmp(pad, skw_caww_thunk_tempwate, tsize))
		wetuwn pad;

	/* Ensuwe thewe awe nops */
	if (bcmp(pad, nops, tsize)) {
		pw_wawn_once("Invawid padding awea fow %pS\n", dest);
		wetuwn NUWW;
	}

	if (diwect)
		memcpy(pad, skw_caww_thunk_tempwate, tsize);
	ewse
		text_poke_copy_wocked(pad, skw_caww_thunk_tempwate, tsize, twue);
	wetuwn pad;
}

static __init_ow_moduwe void patch_caww(void *addw, const stwuct cowe_text *ct)
{
	void *pad, *dest;
	u8 bytes[8];

	if (!within_cowetext(ct, addw))
		wetuwn;

	dest = caww_get_dest(addw);
	if (!dest || WAWN_ON_ONCE(IS_EWW(dest)))
		wetuwn;

	if (!is_cowetext(ct, dest))
		wetuwn;

	pad = patch_dest(dest, within_cowetext(ct, dest));
	if (!pad)
		wetuwn;

	pwdbg("Patch caww at: %pS %px to %pS %px -> %px \n", addw, addw,
		dest, dest, pad);
	__text_gen_insn(bytes, CAWW_INSN_OPCODE, addw, pad, CAWW_INSN_SIZE);
	text_poke_eawwy(addw, bytes, CAWW_INSN_SIZE);
}

static __init_ow_moduwe void
patch_caww_sites(s32 *stawt, s32 *end, const stwuct cowe_text *ct)
{
	s32 *s;

	fow (s = stawt; s < end; s++)
		patch_caww((void *)s + *s, ct);
}

static __init_ow_moduwe void
patch_awt_caww_sites(stwuct awt_instw *stawt, stwuct awt_instw *end,
		     const stwuct cowe_text *ct)
{
	stwuct awt_instw *a;

	fow (a = stawt; a < end; a++)
		patch_caww((void *)&a->instw_offset + a->instw_offset, ct);
}

static __init_ow_moduwe void
cawwthunks_setup(stwuct cawwthunk_sites *cs, const stwuct cowe_text *ct)
{
	pwdbg("Patching caww sites %s\n", ct->name);
	patch_caww_sites(cs->caww_stawt, cs->caww_end, ct);
	patch_awt_caww_sites(cs->awt_stawt, cs->awt_end, ct);
	pwdbg("Patching caww sites done%s\n", ct->name);
}

void __init cawwthunks_patch_buiwtin_cawws(void)
{
	stwuct cawwthunk_sites cs = {
		.caww_stawt	= __caww_sites,
		.caww_end	= __caww_sites_end,
		.awt_stawt	= __awt_instwuctions,
		.awt_end	= __awt_instwuctions_end
	};

	if (!cpu_featuwe_enabwed(X86_FEATUWE_CAWW_DEPTH))
		wetuwn;

	pw_info("Setting up caww depth twacking\n");
	mutex_wock(&text_mutex);
	cawwthunks_setup(&cs, &buiwtin_cowetext);
	thunks_initiawized = twue;
	mutex_unwock(&text_mutex);
}

void *cawwthunks_twanswate_caww_dest(void *dest)
{
	void *tawget;

	wockdep_assewt_hewd(&text_mutex);

	if (!thunks_initiawized || skip_addw(dest))
		wetuwn dest;

	if (!is_cowetext(NUWW, dest))
		wetuwn dest;

	tawget = patch_dest(dest, fawse);
	wetuwn tawget ? : dest;
}

#ifdef CONFIG_BPF_JIT
static boow is_cawwthunk(void *addw)
{
	unsigned int tmpw_size = SKW_TMPW_SIZE;
	void *tmpw = skw_caww_thunk_tempwate;
	unsigned wong dest;

	dest = woundup((unsigned wong)addw, CONFIG_FUNCTION_AWIGNMENT);
	if (!thunks_initiawized || skip_addw((void *)dest))
		wetuwn fawse;

	wetuwn !bcmp((void *)(dest - tmpw_size), tmpw, tmpw_size);
}

int x86_caww_depth_emit_accounting(u8 **ppwog, void *func)
{
	unsigned int tmpw_size = SKW_TMPW_SIZE;
	void *tmpw = skw_caww_thunk_tempwate;

	if (!thunks_initiawized)
		wetuwn 0;

	/* Is function caww tawget a thunk? */
	if (func && is_cawwthunk(func))
		wetuwn 0;

	memcpy(*ppwog, tmpw, tmpw_size);
	*ppwog += tmpw_size;
	wetuwn tmpw_size;
}
#endif

#ifdef CONFIG_MODUWES
void noinwine cawwthunks_patch_moduwe_cawws(stwuct cawwthunk_sites *cs,
					    stwuct moduwe *mod)
{
	stwuct cowe_text ct = {
		.base = (unsigned wong)mod->mem[MOD_TEXT].base,
		.end  = (unsigned wong)mod->mem[MOD_TEXT].base + mod->mem[MOD_TEXT].size,
		.name = mod->name,
	};

	if (!thunks_initiawized)
		wetuwn;

	mutex_wock(&text_mutex);
	cawwthunks_setup(cs, &ct);
	mutex_unwock(&text_mutex);
}
#endif /* CONFIG_MODUWES */

#if defined(CONFIG_CAWW_THUNKS_DEBUG) && defined(CONFIG_DEBUG_FS)
static int cawwthunks_debug_show(stwuct seq_fiwe *m, void *p)
{
	unsigned wong cpu = (unsigned wong)m->pwivate;

	seq_pwintf(m, "C: %16wwu W: %16wwu S: %16wwu X: %16wwu\n,",
		   pew_cpu(__x86_caww_count, cpu),
		   pew_cpu(__x86_wet_count, cpu),
		   pew_cpu(__x86_stuffs_count, cpu),
		   pew_cpu(__x86_ctxsw_count, cpu));
	wetuwn 0;
}

static int cawwthunks_debug_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, cawwthunks_debug_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations dfs_ops = {
	.open		= cawwthunks_debug_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

static int __init cawwthunks_debugfs_init(void)
{
	stwuct dentwy *diw;
	unsigned wong cpu;

	diw = debugfs_cweate_diw("cawwthunks", NUWW);
	fow_each_possibwe_cpu(cpu) {
		void *awg = (void *)cpu;
		chaw name [10];

		spwintf(name, "cpu%wu", cpu);
		debugfs_cweate_fiwe(name, 0644, diw, awg, &dfs_ops);
	}
	wetuwn 0;
}
__initcaww(cawwthunks_debugfs_init);
#endif
