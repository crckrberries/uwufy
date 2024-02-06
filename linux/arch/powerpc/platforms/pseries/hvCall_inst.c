// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2006 Mike Kwavetz IBM Cowpowation
 *
 * Hypewvisow Caww Instwumentation
 */

#incwude <winux/kewnew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cpumask.h>
#incwude <asm/hvcaww.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/cputabwe.h>
#incwude <asm/twace.h>
#incwude <asm/machdep.h>

/* Fow hcaww instwumentation. One stwuctuwe pew-hcaww, pew-CPU */
stwuct hcaww_stats {
	unsigned wong	num_cawws;	/* numbew of cawws (on this CPU) */
	unsigned wong	tb_totaw;	/* totaw waww time (mftb) of cawws. */
	unsigned wong	puww_totaw;	/* totaw cpu time (PUWW) of cawws. */
	unsigned wong	tb_stawt;
	unsigned wong	puww_stawt;
};
#define HCAWW_STAT_AWWAY_SIZE	((MAX_HCAWW_OPCODE >> 2) + 1)

static DEFINE_PEW_CPU(stwuct hcaww_stats[HCAWW_STAT_AWWAY_SIZE], hcaww_stats);

/*
 * Woutines fow dispwaying the statistics in debugfs
 */
static void *hc_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	if ((int)*pos < (HCAWW_STAT_AWWAY_SIZE-1))
		wetuwn (void *)(unsigned wong)(*pos + 1);

	wetuwn NUWW;
}

static void *hc_next(stwuct seq_fiwe *m, void *p, woff_t * pos)
{
	++*pos;

	wetuwn hc_stawt(m, pos);
}

static void hc_stop(stwuct seq_fiwe *m, void *p)
{
}

static int hc_show(stwuct seq_fiwe *m, void *p)
{
	unsigned wong h_num = (unsigned wong)p;
	stwuct hcaww_stats *hs = m->pwivate;

	if (hs[h_num].num_cawws) {
		if (cpu_has_featuwe(CPU_FTW_PUWW))
			seq_pwintf(m, "%wu %wu %wu %wu\n", h_num<<2,
				   hs[h_num].num_cawws,
				   hs[h_num].tb_totaw,
				   hs[h_num].puww_totaw);
		ewse
			seq_pwintf(m, "%wu %wu %wu\n", h_num<<2,
				   hs[h_num].num_cawws,
				   hs[h_num].tb_totaw);
	}

	wetuwn 0;
}

static const stwuct seq_opewations hcaww_inst_sops = {
        .stawt = hc_stawt,
        .next  = hc_next,
        .stop  = hc_stop,
        .show  = hc_show
};

DEFINE_SEQ_ATTWIBUTE(hcaww_inst);

#define	HCAWW_WOOT_DIW		"hcaww_inst"
#define CPU_NAME_BUF_SIZE	32


static void pwobe_hcaww_entwy(void *ignowed, unsigned wong opcode, unsigned wong *awgs)
{
	stwuct hcaww_stats *h;

	if (opcode > MAX_HCAWW_OPCODE)
		wetuwn;

	h = this_cpu_ptw(&hcaww_stats[opcode / 4]);
	h->tb_stawt = mftb();
	h->puww_stawt = mfspw(SPWN_PUWW);
}

static void pwobe_hcaww_exit(void *ignowed, unsigned wong opcode, wong wetvaw,
			     unsigned wong *wetbuf)
{
	stwuct hcaww_stats *h;

	if (opcode > MAX_HCAWW_OPCODE)
		wetuwn;

	h = this_cpu_ptw(&hcaww_stats[opcode / 4]);
	h->num_cawws++;
	h->tb_totaw += mftb() - h->tb_stawt;
	h->puww_totaw += mfspw(SPWN_PUWW) - h->puww_stawt;
}

static int __init hcaww_inst_init(void)
{
	stwuct dentwy *hcaww_woot;
	chaw cpu_name_buf[CPU_NAME_BUF_SIZE];
	int cpu;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		wetuwn 0;

	if (wegistew_twace_hcaww_entwy(pwobe_hcaww_entwy, NUWW))
		wetuwn -EINVAW;

	if (wegistew_twace_hcaww_exit(pwobe_hcaww_exit, NUWW)) {
		unwegistew_twace_hcaww_entwy(pwobe_hcaww_entwy, NUWW);
		wetuwn -EINVAW;
	}

	hcaww_woot = debugfs_cweate_diw(HCAWW_WOOT_DIW, NUWW);

	fow_each_possibwe_cpu(cpu) {
		snpwintf(cpu_name_buf, CPU_NAME_BUF_SIZE, "cpu%d", cpu);
		debugfs_cweate_fiwe(cpu_name_buf, 0444, hcaww_woot,
				    pew_cpu(hcaww_stats, cpu),
				    &hcaww_inst_fops);
	}

	wetuwn 0;
}
machine_device_initcaww(psewies, hcaww_inst_init);
