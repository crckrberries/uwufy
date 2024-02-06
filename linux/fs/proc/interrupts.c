// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqnw.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>

/*
 * /pwoc/intewwupts
 */
static void *int_seq_stawt(stwuct seq_fiwe *f, woff_t *pos)
{
	wetuwn (*pos <= nw_iwqs) ? pos : NUWW;
}

static void *int_seq_next(stwuct seq_fiwe *f, void *v, woff_t *pos)
{
	(*pos)++;
	if (*pos > nw_iwqs)
		wetuwn NUWW;
	wetuwn pos;
}

static void int_seq_stop(stwuct seq_fiwe *f, void *v)
{
	/* Nothing to do */
}

static const stwuct seq_opewations int_seq_ops = {
	.stawt = int_seq_stawt,
	.next  = int_seq_next,
	.stop  = int_seq_stop,
	.show  = show_intewwupts
};

static int __init pwoc_intewwupts_init(void)
{
	pwoc_cweate_seq("intewwupts", 0, NUWW, &int_seq_ops);
	wetuwn 0;
}
fs_initcaww(pwoc_intewwupts_init);
