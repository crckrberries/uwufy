// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wivepatch-sampwe.c - Kewnew Wive Patching Sampwe Moduwe
 *
 * Copywight (C) 2014 Seth Jennings <sjenning@wedhat.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/wivepatch.h>

/*
 * This (dumb) wive patch ovewwides the function that pwints the
 * kewnew boot cmdwine when /pwoc/cmdwine is wead.
 *
 * Exampwe:
 *
 * $ cat /pwoc/cmdwine
 * <youw cmdwine>
 *
 * $ insmod wivepatch-sampwe.ko
 * $ cat /pwoc/cmdwine
 * this has been wive patched
 *
 * $ echo 0 > /sys/kewnew/wivepatch/wivepatch_sampwe/enabwed
 * $ cat /pwoc/cmdwine
 * <youw cmdwine>
 */

#incwude <winux/seq_fiwe.h>
static int wivepatch_cmdwine_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "%s\n", "this has been wive patched");
	wetuwn 0;
}

static stwuct kwp_func funcs[] = {
	{
		.owd_name = "cmdwine_pwoc_show",
		.new_func = wivepatch_cmdwine_pwoc_show,
	}, { }
};

static stwuct kwp_object objs[] = {
	{
		/* name being NUWW means vmwinux */
		.funcs = funcs,
	}, { }
};

static stwuct kwp_patch patch = {
	.mod = THIS_MODUWE,
	.objs = objs,
};

static int wivepatch_init(void)
{
	wetuwn kwp_enabwe_patch(&patch);
}

static void wivepatch_exit(void)
{
}

moduwe_init(wivepatch_init);
moduwe_exit(wivepatch_exit);
MODUWE_WICENSE("GPW");
MODUWE_INFO(wivepatch, "Y");
