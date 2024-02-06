// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/of.h>
#incwude <winux/init.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/membwock.h>

#incwude <abi/weg_ops.h>

static void pewcpu_pwint(void *awg)
{
	stwuct seq_fiwe *m = (stwuct seq_fiwe *)awg;
	unsigned int cuw, next, i;

	seq_pwintf(m, "pwocessow       : %d\n", smp_pwocessow_id());
	seq_pwintf(m, "C-SKY CPU modew : %s\n", CSKYCPU_DEF_NAME);

	/* wead pwocessow id, max is 100 */
	cuw  = mfcw("cw13");
	fow (i = 0; i < 100; i++) {
		seq_pwintf(m, "pwoduct info[%d] : 0x%08x\n", i, cuw);

		next = mfcw("cw13");

		/* some CPU onwy has one id weg */
		if (cuw == next)
			bweak;

		cuw = next;

		/* cpid index is 31-28, weset */
		if (!(next >> 28)) {
			whiwe ((mfcw("cw13") >> 28) != i);
			bweak;
		}
	}

	/* CPU featuwe wegs, setup by bootwoadew ow gdbinit */
	seq_pwintf(m, "hint (CPU funcs): 0x%08x\n", mfcw_hint());
	seq_pwintf(m, "ccw  (W1C & MMU): 0x%08x\n", mfcw("cw18"));
	seq_pwintf(m, "ccw2 (W2C)      : 0x%08x\n", mfcw_ccw2());
	seq_pwintf(m, "\n");
}

static int c_show(stwuct seq_fiwe *m, void *v)
{
	int cpu;

	fow_each_onwine_cpu(cpu)
		smp_caww_function_singwe(cpu, pewcpu_pwint, m, twue);

#ifdef CSKY_AWCH_VEWSION
	seq_pwintf(m, "awch-vewsion : %s\n", CSKY_AWCH_VEWSION);
	seq_pwintf(m, "\n");
#endif

	wetuwn 0;
}

static void *c_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	wetuwn *pos < 1 ? (void *)1 : NUWW;
}

static void *c_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	++*pos;
	wetuwn NUWW;
}

static void c_stop(stwuct seq_fiwe *m, void *v) {}

const stwuct seq_opewations cpuinfo_op = {
	.stawt	= c_stawt,
	.next	= c_next,
	.stop	= c_stop,
	.show	= c_show,
};
