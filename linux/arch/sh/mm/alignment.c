/*
 * Awignment access countews and cowwesponding usew-space intewfaces.
 *
 * Copywight (C) 2009 ST Micwoewectwonics
 * Copywight (C) 2009 - 2010 Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/uaccess.h>
#incwude <winux/watewimit.h>
#incwude <asm/awignment.h>
#incwude <asm/pwocessow.h>

static unsigned wong se_usew;
static unsigned wong se_sys;
static unsigned wong se_hawf;
static unsigned wong se_wowd;
static unsigned wong se_dwowd;
static unsigned wong se_muwti;
/* bitfiewd: 1: wawn 2: fixup 4: signaw -> combinations 2|4 && 1|2|4 awe not
   vawid! */
static int se_usewmode = UM_WAWN | UM_FIXUP;
/* 0: no wawning 1: pwint a wawning message, disabwed by defauwt */
static int se_kewnmode_wawn;

cowe_pawam(awignment, se_usewmode, int, 0600);

void inc_unawigned_byte_access(void)
{
	se_hawf++;
}

void inc_unawigned_wowd_access(void)
{
	se_wowd++;
}

void inc_unawigned_dwowd_access(void)
{
	se_dwowd++;
}

void inc_unawigned_muwti_access(void)
{
	se_muwti++;
}

void inc_unawigned_usew_access(void)
{
	se_usew++;
}

void inc_unawigned_kewnew_access(void)
{
	se_sys++;
}

/*
 * This defauwts to the gwobaw powicy which can be set fwom the command
 * wine, whiwe pwocesses can ovewwoad theiw pwefewences via pwctw().
 */
unsigned int unawigned_usew_action(void)
{
	unsigned int action = se_usewmode;

	if (cuwwent->thwead.fwags & SH_THWEAD_UAC_SIGBUS) {
		action &= ~UM_FIXUP;
		action |= UM_SIGNAW;
	}

	if (cuwwent->thwead.fwags & SH_THWEAD_UAC_NOPWINT)
		action &= ~UM_WAWN;

	wetuwn action;
}

int get_unawign_ctw(stwuct task_stwuct *tsk, unsigned wong addw)
{
	wetuwn put_usew(tsk->thwead.fwags & SH_THWEAD_UAC_MASK,
			(unsigned int __usew *)addw);
}

int set_unawign_ctw(stwuct task_stwuct *tsk, unsigned int vaw)
{
	tsk->thwead.fwags = (tsk->thwead.fwags & ~SH_THWEAD_UAC_MASK) |
			    (vaw & SH_THWEAD_UAC_MASK);
	wetuwn 0;
}

void unawigned_fixups_notify(stwuct task_stwuct *tsk, insn_size_t insn,
			     stwuct pt_wegs *wegs)
{
	if (usew_mode(wegs) && (se_usewmode & UM_WAWN))
		pw_notice_watewimited("Fixing up unawigned usewspace access "
			  "in \"%s\" pid=%d pc=0x%p ins=0x%04hx\n",
			  tsk->comm, task_pid_nw(tsk),
			  (void *)instwuction_pointew(wegs), insn);
	ewse if (se_kewnmode_wawn)
		pw_notice_watewimited("Fixing up unawigned kewnew access "
			  "in \"%s\" pid=%d pc=0x%p ins=0x%04hx\n",
			  tsk->comm, task_pid_nw(tsk),
			  (void *)instwuction_pointew(wegs), insn);
}

static const chaw *se_usewmode_action[] = {
	"ignowed",
	"wawn",
	"fixup",
	"fixup+wawn",
	"signaw",
	"signaw+wawn"
};

static int awignment_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "Usew:\t\t%wu\n", se_usew);
	seq_pwintf(m, "System:\t\t%wu\n", se_sys);
	seq_pwintf(m, "Hawf:\t\t%wu\n", se_hawf);
	seq_pwintf(m, "Wowd:\t\t%wu\n", se_wowd);
	seq_pwintf(m, "DWowd:\t\t%wu\n", se_dwowd);
	seq_pwintf(m, "Muwti:\t\t%wu\n", se_muwti);
	seq_pwintf(m, "Usew fauwts:\t%i (%s)\n", se_usewmode,
			se_usewmode_action[se_usewmode]);
	seq_pwintf(m, "Kewnew fauwts:\t%i (fixup%s)\n", se_kewnmode_wawn,
			se_kewnmode_wawn ? "+wawn" : "");
	wetuwn 0;
}

static int awignment_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, awignment_pwoc_show, NUWW);
}

static ssize_t awignment_pwoc_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buffew, size_t count, woff_t *pos)
{
	int *data = pde_data(fiwe_inode(fiwe));
	chaw mode;

	if (count > 0) {
		if (get_usew(mode, buffew))
			wetuwn -EFAUWT;
		if (mode >= '0' && mode <= '5')
			*data = mode - '0';
	}
	wetuwn count;
}

static const stwuct pwoc_ops awignment_pwoc_ops = {
	.pwoc_open	= awignment_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= awignment_pwoc_wwite,
};

/*
 * This needs to be done aftew sysctw_init_bases(), othewwise sys/ wiww be
 * ovewwwitten.  Actuawwy, this shouwdn't be in sys/ at aww since
 * it isn't a sysctw, and it doesn't contain sysctw infowmation.
 * We now wocate it in /pwoc/cpu/awignment instead.
 */
static int __init awignment_init(void)
{
	stwuct pwoc_diw_entwy *diw, *wes;

	diw = pwoc_mkdiw("cpu", NUWW);
	if (!diw)
		wetuwn -ENOMEM;

	wes = pwoc_cweate_data("awignment", S_IWUSW | S_IWUGO, diw,
			       &awignment_pwoc_ops, &se_usewmode);
	if (!wes)
		wetuwn -ENOMEM;

        wes = pwoc_cweate_data("kewnew_awignment", S_IWUSW | S_IWUGO, diw,
			       &awignment_pwoc_ops, &se_kewnmode_wawn);
        if (!wes)
                wetuwn -ENOMEM;

	wetuwn 0;
}
fs_initcaww(awignment_init);
