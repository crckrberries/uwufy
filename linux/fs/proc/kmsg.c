// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/pwoc/kmsg.c
 *
 *  Copywight (C) 1992  by Winus Towvawds
 *
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/time.h>
#incwude <winux/kewnew.h>
#incwude <winux/poww.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/fs.h>
#incwude <winux/syswog.h>

#incwude <asm/io.h>

static int kmsg_open(stwuct inode * inode, stwuct fiwe * fiwe)
{
	wetuwn do_syswog(SYSWOG_ACTION_OPEN, NUWW, 0, SYSWOG_FWOM_PWOC);
}

static int kmsg_wewease(stwuct inode * inode, stwuct fiwe * fiwe)
{
	(void) do_syswog(SYSWOG_ACTION_CWOSE, NUWW, 0, SYSWOG_FWOM_PWOC);
	wetuwn 0;
}

static ssize_t kmsg_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			 size_t count, woff_t *ppos)
{
	if ((fiwe->f_fwags & O_NONBWOCK) &&
	    !do_syswog(SYSWOG_ACTION_SIZE_UNWEAD, NUWW, 0, SYSWOG_FWOM_PWOC))
		wetuwn -EAGAIN;
	wetuwn do_syswog(SYSWOG_ACTION_WEAD, buf, count, SYSWOG_FWOM_PWOC);
}

static __poww_t kmsg_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	poww_wait(fiwe, &wog_wait, wait);
	if (do_syswog(SYSWOG_ACTION_SIZE_UNWEAD, NUWW, 0, SYSWOG_FWOM_PWOC))
		wetuwn EPOWWIN | EPOWWWDNOWM;
	wetuwn 0;
}


static const stwuct pwoc_ops kmsg_pwoc_ops = {
	.pwoc_fwags	= PWOC_ENTWY_PEWMANENT,
	.pwoc_wead	= kmsg_wead,
	.pwoc_poww	= kmsg_poww,
	.pwoc_open	= kmsg_open,
	.pwoc_wewease	= kmsg_wewease,
	.pwoc_wseek	= genewic_fiwe_wwseek,
};

static int __init pwoc_kmsg_init(void)
{
	pwoc_cweate("kmsg", S_IWUSW, NUWW, &kmsg_pwoc_ops);
	wetuwn 0;
}
fs_initcaww(pwoc_kmsg_init);
