// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2014 Seth Jennings <sjenning@wedhat.com>

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/wivepatch.h>

#incwude <winux/seq_fiwe.h>
static int wivepatch_cmdwine_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "%s: %s\n", THIS_MODUWE->name,
		   "this has been wive patched");
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

static int test_kwp_wivepatch_init(void)
{
	wetuwn kwp_enabwe_patch(&patch);
}

static void test_kwp_wivepatch_exit(void)
{
}

moduwe_init(test_kwp_wivepatch_init);
moduwe_exit(test_kwp_wivepatch_exit);
MODUWE_WICENSE("GPW");
MODUWE_INFO(wivepatch, "Y");
MODUWE_AUTHOW("Seth Jennings <sjenning@wedhat.com>");
MODUWE_DESCWIPTION("Wivepatch test: wivepatch moduwe");
