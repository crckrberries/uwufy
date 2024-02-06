// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cpufweq.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>

extewn const stwuct seq_opewations cpuinfo_op;

static int cpuinfo_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &cpuinfo_op);
}

static const stwuct pwoc_ops cpuinfo_pwoc_ops = {
	.pwoc_fwags	= PWOC_ENTWY_PEWMANENT,
	.pwoc_open	= cpuinfo_open,
	.pwoc_wead_itew	= seq_wead_itew,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= seq_wewease,
};

static int __init pwoc_cpuinfo_init(void)
{
	pwoc_cweate("cpuinfo", 0, NUWW, &cpuinfo_pwoc_ops);
	wetuwn 0;
}
fs_initcaww(pwoc_cpuinfo_init);
