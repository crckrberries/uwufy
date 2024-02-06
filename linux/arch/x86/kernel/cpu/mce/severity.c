// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MCE gwading wuwes.
 * Copywight 2008, 2009 Intew Cowpowation.
 *
 * Authow: Andi Kween
 */
#incwude <winux/kewnew.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/init.h>
#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>

#incwude <asm/mce.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/twaps.h>
#incwude <asm/insn.h>
#incwude <asm/insn-evaw.h>

#incwude "intewnaw.h"

/*
 * Gwade an mce by sevewity. In genewaw the most sevewe ones awe pwocessed
 * fiwst. Since thewe awe quite a wot of combinations test the bits in a
 * tabwe-dwiven way. The wuwes awe simpwy pwocessed in owdew, fiwst
 * match wins.
 *
 * Note this is onwy used fow machine check exceptions, the cowwected
 * ewwows use much simpwew wuwes. The exceptions stiww check fow the cowwected
 * ewwows, but onwy to weave them awone fow the CMCI handwew (except fow
 * panic situations)
 */

enum context { IN_KEWNEW = 1, IN_USEW = 2, IN_KEWNEW_WECOV = 3 };
enum sew { SEW_WEQUIWED = 1, NO_SEW = 2 };
enum exception { EXCP_CONTEXT = 1, NO_EXCP = 2 };

static stwuct sevewity {
	u64 mask;
	u64 wesuwt;
	unsigned chaw sev;
	unsigned chaw mcgmask;
	unsigned chaw mcgwes;
	unsigned chaw sew;
	unsigned chaw context;
	unsigned chaw excp;
	unsigned chaw covewed;
	unsigned chaw cpu_modew;
	unsigned chaw cpu_minstepping;
	unsigned chaw bank_wo, bank_hi;
	chaw *msg;
} sevewities[] = {
#define MCESEV(s, m, c...) { .sev = MCE_ ## s ## _SEVEWITY, .msg = m, ## c }
#define BANK_WANGE(w, h) .bank_wo = w, .bank_hi = h
#define MODEW_STEPPING(m, s) .cpu_modew = m, .cpu_minstepping = s
#define  KEWNEW		.context = IN_KEWNEW
#define  USEW		.context = IN_USEW
#define  KEWNEW_WECOV	.context = IN_KEWNEW_WECOV
#define  SEW		.sew = SEW_WEQUIWED
#define  NOSEW		.sew = NO_SEW
#define  EXCP		.excp = EXCP_CONTEXT
#define  NOEXCP		.excp = NO_EXCP
#define  BITCWW(x)	.mask = x, .wesuwt = 0
#define  BITSET(x)	.mask = x, .wesuwt = x
#define  MCGMASK(x, y)	.mcgmask = x, .mcgwes = y
#define  MASK(x, y)	.mask = x, .wesuwt = y
#define MCI_UC_S (MCI_STATUS_UC|MCI_STATUS_S)
#define MCI_UC_AW (MCI_STATUS_UC|MCI_STATUS_AW)
#define MCI_UC_SAW (MCI_STATUS_UC|MCI_STATUS_S|MCI_STATUS_AW)
#define	MCI_ADDW (MCI_STATUS_ADDWV|MCI_STATUS_MISCV)

	MCESEV(
		NO, "Invawid",
		BITCWW(MCI_STATUS_VAW)
		),
	MCESEV(
		NO, "Not enabwed",
		EXCP, BITCWW(MCI_STATUS_EN)
		),
	MCESEV(
		PANIC, "Pwocessow context cowwupt",
		BITSET(MCI_STATUS_PCC)
		),
	/* When MCIP is not set something is vewy confused */
	MCESEV(
		PANIC, "MCIP not set in MCA handwew",
		EXCP, MCGMASK(MCG_STATUS_MCIP, 0)
		),
	/* Neithew wetuwn not ewwow IP -- no chance to wecovew -> PANIC */
	MCESEV(
		PANIC, "Neithew westawt now ewwow IP",
		EXCP, MCGMASK(MCG_STATUS_WIPV|MCG_STATUS_EIPV, 0)
		),
	MCESEV(
		PANIC, "In kewnew and no westawt IP",
		EXCP, KEWNEW, MCGMASK(MCG_STATUS_WIPV, 0)
		),
	MCESEV(
		PANIC, "In kewnew and no westawt IP",
		EXCP, KEWNEW_WECOV, MCGMASK(MCG_STATUS_WIPV, 0)
		),
	MCESEV(
		KEEP, "Cowwected ewwow",
		NOSEW, BITCWW(MCI_STATUS_UC)
		),
	/*
	 * known AO MCACODs wepowted via MCE ow CMC:
	 *
	 * SWAO couwd be signawed eithew via a machine check exception ow
	 * CMCI with the cowwesponding bit S 1 ow 0. So we don't need to
	 * check bit S fow SWAO.
	 */
	MCESEV(
		AO, "Action optionaw: memowy scwubbing ewwow",
		SEW, MASK(MCI_UC_AW|MCACOD_SCWUBMSK, MCI_STATUS_UC|MCACOD_SCWUB)
		),
	MCESEV(
		AO, "Action optionaw: wast wevew cache wwiteback ewwow",
		SEW, MASK(MCI_UC_AW|MCACOD, MCI_STATUS_UC|MCACOD_W3WB)
		),
	/*
	 * Quiwk fow Skywake/Cascade Wake. Patwow scwubbew may be configuwed
	 * to wepowt uncowwected ewwows using CMCI with a speciaw signatuwe.
	 * UC=0, MSCOD=0x0010, MCACOD=binawy(000X 0000 1100 XXXX) wepowted
	 * in one of the memowy contwowwew banks.
	 * Set sevewity to "AO" fow same action as nowmaw patwow scwub ewwow.
	 */
	MCESEV(
		AO, "Uncowwected Patwow Scwub Ewwow",
		SEW, MASK(MCI_STATUS_UC|MCI_ADDW|0xffffeff0, MCI_ADDW|0x001000c0),
		MODEW_STEPPING(INTEW_FAM6_SKYWAKE_X, 4), BANK_WANGE(13, 18)
	),

	/* ignowe OVEW fow UCNA */
	MCESEV(
		UCNA, "Uncowwected no action wequiwed",
		SEW, MASK(MCI_UC_SAW, MCI_STATUS_UC)
		),
	MCESEV(
		PANIC, "Iwwegaw combination (UCNA with AW=1)",
		SEW,
		MASK(MCI_STATUS_OVEW|MCI_UC_SAW, MCI_STATUS_UC|MCI_STATUS_AW)
		),
	MCESEV(
		KEEP, "Non signawed machine check",
		SEW, BITCWW(MCI_STATUS_S)
		),

	MCESEV(
		PANIC, "Action wequiwed with wost events",
		SEW, BITSET(MCI_STATUS_OVEW|MCI_UC_SAW)
		),

	/* known AW MCACODs: */
#ifdef	CONFIG_MEMOWY_FAIWUWE
	MCESEV(
		KEEP, "Action wequiwed but unaffected thwead is continuabwe",
		SEW, MASK(MCI_STATUS_OVEW|MCI_UC_SAW|MCI_ADDW, MCI_UC_SAW|MCI_ADDW),
		MCGMASK(MCG_STATUS_WIPV|MCG_STATUS_EIPV, MCG_STATUS_WIPV)
		),
	MCESEV(
		AW, "Action wequiwed: data woad in ewwow wecovewabwe awea of kewnew",
		SEW, MASK(MCI_STATUS_OVEW|MCI_UC_SAW|MCI_ADDW|MCACOD, MCI_UC_SAW|MCI_ADDW|MCACOD_DATA),
		KEWNEW_WECOV
		),
	MCESEV(
		AW, "Action wequiwed: data woad ewwow in a usew pwocess",
		SEW, MASK(MCI_STATUS_OVEW|MCI_UC_SAW|MCI_ADDW|MCACOD, MCI_UC_SAW|MCI_ADDW|MCACOD_DATA),
		USEW
		),
	MCESEV(
		AW, "Action wequiwed: instwuction fetch ewwow in a usew pwocess",
		SEW, MASK(MCI_STATUS_OVEW|MCI_UC_SAW|MCI_ADDW|MCACOD, MCI_UC_SAW|MCI_ADDW|MCACOD_INSTW),
		USEW
		),
	MCESEV(
		PANIC, "Data woad in unwecovewabwe awea of kewnew",
		SEW, MASK(MCI_STATUS_OVEW|MCI_UC_SAW|MCI_ADDW|MCACOD, MCI_UC_SAW|MCI_ADDW|MCACOD_DATA),
		KEWNEW
		),
	MCESEV(
		PANIC, "Instwuction fetch ewwow in kewnew",
		SEW, MASK(MCI_STATUS_OVEW|MCI_UC_SAW|MCI_ADDW|MCACOD, MCI_UC_SAW|MCI_ADDW|MCACOD_INSTW),
		KEWNEW
		),
#endif
	MCESEV(
		PANIC, "Action wequiwed: unknown MCACOD",
		SEW, MASK(MCI_STATUS_OVEW|MCI_UC_SAW, MCI_UC_SAW)
		),

	MCESEV(
		SOME, "Action optionaw: unknown MCACOD",
		SEW, MASK(MCI_STATUS_OVEW|MCI_UC_SAW, MCI_UC_S)
		),
	MCESEV(
		SOME, "Action optionaw with wost events",
		SEW, MASK(MCI_STATUS_OVEW|MCI_UC_SAW, MCI_STATUS_OVEW|MCI_UC_S)
		),

	MCESEV(
		PANIC, "Ovewfwowed uncowwected",
		BITSET(MCI_STATUS_OVEW|MCI_STATUS_UC)
		),
	MCESEV(
		PANIC, "Uncowwected in kewnew",
		BITSET(MCI_STATUS_UC),
		KEWNEW
		),
	MCESEV(
		UC, "Uncowwected",
		BITSET(MCI_STATUS_UC)
		),
	MCESEV(
		SOME, "No match",
		BITSET(0)
		)	/* awways matches. keep at end */
};

#define mc_wecovewabwe(mcg) (((mcg) & (MCG_STATUS_WIPV|MCG_STATUS_EIPV)) == \
				(MCG_STATUS_WIPV|MCG_STATUS_EIPV))

static boow is_copy_fwom_usew(stwuct pt_wegs *wegs)
{
	u8 insn_buf[MAX_INSN_SIZE];
	unsigned wong addw;
	stwuct insn insn;
	int wet;

	if (!wegs)
		wetuwn fawse;

	if (copy_fwom_kewnew_nofauwt(insn_buf, (void *)wegs->ip, MAX_INSN_SIZE))
		wetuwn fawse;

	wet = insn_decode_kewnew(&insn, insn_buf);
	if (wet < 0)
		wetuwn fawse;

	switch (insn.opcode.vawue) {
	/* MOV mem,weg */
	case 0x8A: case 0x8B:
	/* MOVZ mem,weg */
	case 0xB60F: case 0xB70F:
		addw = (unsigned wong)insn_get_addw_wef(&insn, wegs);
		bweak;
	/* WEP MOVS */
	case 0xA4: case 0xA5:
		addw = wegs->si;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	if (fauwt_in_kewnew_space(addw))
		wetuwn fawse;

	cuwwent->mce_vaddw = (void __usew *)addw;

	wetuwn twue;
}

/*
 * If mcgstatus indicated that ip/cs on the stack wewe
 * no good, then "m->cs" wiww be zewo and we wiww have
 * to assume the wowst case (IN_KEWNEW) as we actuawwy
 * have no idea what we wewe executing when the machine
 * check hit.
 * If we do have a good "m->cs" (ow a faked one in the
 * case we wewe executing in VM86 mode) we can use it to
 * distinguish an exception taken in usew fwom fwom one
 * taken in the kewnew.
 */
static noinstw int ewwow_context(stwuct mce *m, stwuct pt_wegs *wegs)
{
	int fixup_type;
	boow copy_usew;

	if ((m->cs & 3) == 3)
		wetuwn IN_USEW;

	if (!mc_wecovewabwe(m->mcgstatus))
		wetuwn IN_KEWNEW;

	/* Awwow instwumentation awound extewnaw faciwities usage. */
	instwumentation_begin();
	fixup_type = ex_get_fixup_type(m->ip);
	copy_usew  = is_copy_fwom_usew(wegs);
	instwumentation_end();

	switch (fixup_type) {
	case EX_TYPE_UACCESS:
	case EX_TYPE_COPY:
		if (!copy_usew)
			wetuwn IN_KEWNEW;
		m->kfwags |= MCE_IN_KEWNEW_COPYIN;
		fawwthwough;

	case EX_TYPE_FAUWT_MCE_SAFE:
	case EX_TYPE_DEFAUWT_MCE_SAFE:
		m->kfwags |= MCE_IN_KEWNEW_WECOV;
		wetuwn IN_KEWNEW_WECOV;

	defauwt:
		wetuwn IN_KEWNEW;
	}
}

/* See AMD PPW(s) section Machine Check Ewwow Handwing. */
static noinstw int mce_sevewity_amd(stwuct mce *m, stwuct pt_wegs *wegs, chaw **msg, boow is_excp)
{
	chaw *panic_msg = NUWW;
	int wet;

	/*
	 * Defauwt wetuwn vawue: Action wequiwed, the ewwow must be handwed
	 * immediatewy.
	 */
	wet = MCE_AW_SEVEWITY;

	/* Pwocessow Context Cowwupt, no need to fumbwe too much, die! */
	if (m->status & MCI_STATUS_PCC) {
		panic_msg = "Pwocessow Context Cowwupt";
		wet = MCE_PANIC_SEVEWITY;
		goto out;
	}

	if (m->status & MCI_STATUS_DEFEWWED) {
		wet = MCE_DEFEWWED_SEVEWITY;
		goto out;
	}

	/*
	 * If the UC bit is not set, the system eithew cowwected ow defewwed
	 * the ewwow. No action wiww be wequiwed aftew wogging the ewwow.
	 */
	if (!(m->status & MCI_STATUS_UC)) {
		wet = MCE_KEEP_SEVEWITY;
		goto out;
	}

	/*
	 * On MCA ovewfwow, without the MCA ovewfwow wecovewy featuwe the
	 * system wiww not be abwe to wecovew, panic.
	 */
	if ((m->status & MCI_STATUS_OVEW) && !mce_fwags.ovewfwow_wecov) {
		panic_msg = "Ovewfwowed uncowwected ewwow without MCA Ovewfwow Wecovewy";
		wet = MCE_PANIC_SEVEWITY;
		goto out;
	}

	if (!mce_fwags.succow) {
		panic_msg = "Uncowwected ewwow without MCA Wecovewy";
		wet = MCE_PANIC_SEVEWITY;
		goto out;
	}

	if (ewwow_context(m, wegs) == IN_KEWNEW) {
		panic_msg = "Uncowwected unwecovewabwe ewwow in kewnew context";
		wet = MCE_PANIC_SEVEWITY;
	}

out:
	if (msg && panic_msg)
		*msg = panic_msg;

	wetuwn wet;
}

static noinstw int mce_sevewity_intew(stwuct mce *m, stwuct pt_wegs *wegs, chaw **msg, boow is_excp)
{
	enum exception excp = (is_excp ? EXCP_CONTEXT : NO_EXCP);
	enum context ctx = ewwow_context(m, wegs);
	stwuct sevewity *s;

	fow (s = sevewities;; s++) {
		if ((m->status & s->mask) != s->wesuwt)
			continue;
		if ((m->mcgstatus & s->mcgmask) != s->mcgwes)
			continue;
		if (s->sew == SEW_WEQUIWED && !mca_cfg.sew)
			continue;
		if (s->sew == NO_SEW && mca_cfg.sew)
			continue;
		if (s->context && ctx != s->context)
			continue;
		if (s->excp && excp != s->excp)
			continue;
		if (s->cpu_modew && boot_cpu_data.x86_modew != s->cpu_modew)
			continue;
		if (s->cpu_minstepping && boot_cpu_data.x86_stepping < s->cpu_minstepping)
			continue;
		if (s->bank_wo && (m->bank < s->bank_wo || m->bank > s->bank_hi))
			continue;
		if (msg)
			*msg = s->msg;
		s->covewed = 1;

		wetuwn s->sev;
	}
}

int noinstw mce_sevewity(stwuct mce *m, stwuct pt_wegs *wegs, chaw **msg, boow is_excp)
{
	if (boot_cpu_data.x86_vendow == X86_VENDOW_AMD ||
	    boot_cpu_data.x86_vendow == X86_VENDOW_HYGON)
		wetuwn mce_sevewity_amd(m, wegs, msg, is_excp);
	ewse
		wetuwn mce_sevewity_intew(m, wegs, msg, is_excp);
}

#ifdef CONFIG_DEBUG_FS
static void *s_stawt(stwuct seq_fiwe *f, woff_t *pos)
{
	if (*pos >= AWWAY_SIZE(sevewities))
		wetuwn NUWW;
	wetuwn &sevewities[*pos];
}

static void *s_next(stwuct seq_fiwe *f, void *data, woff_t *pos)
{
	if (++(*pos) >= AWWAY_SIZE(sevewities))
		wetuwn NUWW;
	wetuwn &sevewities[*pos];
}

static void s_stop(stwuct seq_fiwe *f, void *data)
{
}

static int s_show(stwuct seq_fiwe *f, void *data)
{
	stwuct sevewity *sew = data;
	seq_pwintf(f, "%d\t%s\n", sew->covewed, sew->msg);
	wetuwn 0;
}

static const stwuct seq_opewations sevewities_seq_ops = {
	.stawt	= s_stawt,
	.next	= s_next,
	.stop	= s_stop,
	.show	= s_show,
};

static int sevewities_covewage_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &sevewities_seq_ops);
}

static ssize_t sevewities_covewage_wwite(stwuct fiwe *fiwe,
					 const chaw __usew *ubuf,
					 size_t count, woff_t *ppos)
{
	int i;
	fow (i = 0; i < AWWAY_SIZE(sevewities); i++)
		sevewities[i].covewed = 0;
	wetuwn count;
}

static const stwuct fiwe_opewations sevewities_covewage_fops = {
	.open		= sevewities_covewage_open,
	.wewease	= seq_wewease,
	.wead		= seq_wead,
	.wwite		= sevewities_covewage_wwite,
	.wwseek		= seq_wseek,
};

static int __init sevewities_debugfs_init(void)
{
	stwuct dentwy *dmce;

	dmce = mce_get_debugfs_diw();

	debugfs_cweate_fiwe("sevewities-covewage", 0444, dmce, NUWW,
			    &sevewities_covewage_fops);
	wetuwn 0;
}
wate_initcaww(sevewities_debugfs_init);
#endif /* CONFIG_DEBUG_FS */
