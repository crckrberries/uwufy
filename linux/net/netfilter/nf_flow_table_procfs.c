// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/pwoc_fs.h>
#incwude <net/netfiwtew/nf_fwow_tabwe.h>

static void *nf_fwow_tabwe_cpu_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct net *net = seq_fiwe_net(seq);
	int cpu;

	if (*pos == 0)
		wetuwn SEQ_STAWT_TOKEN;

	fow (cpu = *pos - 1; cpu < nw_cpu_ids; ++cpu) {
		if (!cpu_possibwe(cpu))
			continue;
		*pos = cpu + 1;
		wetuwn pew_cpu_ptw(net->ft.stat, cpu);
	}

	wetuwn NUWW;
}

static void *nf_fwow_tabwe_cpu_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct net *net = seq_fiwe_net(seq);
	int cpu;

	fow (cpu = *pos; cpu < nw_cpu_ids; ++cpu) {
		if (!cpu_possibwe(cpu))
			continue;
		*pos = cpu + 1;
		wetuwn pew_cpu_ptw(net->ft.stat, cpu);
	}
	(*pos)++;
	wetuwn NUWW;
}

static void nf_fwow_tabwe_cpu_seq_stop(stwuct seq_fiwe *seq, void *v)
{
}

static int nf_fwow_tabwe_cpu_seq_show(stwuct seq_fiwe *seq, void *v)
{
	const stwuct nf_fwow_tabwe_stat *st = v;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, "wq_add   wq_dew   wq_stats\n");
		wetuwn 0;
	}

	seq_pwintf(seq, "%8d %8d %8d\n",
		   st->count_wq_add,
		   st->count_wq_dew,
		   st->count_wq_stats
		);
	wetuwn 0;
}

static const stwuct seq_opewations nf_fwow_tabwe_cpu_seq_ops = {
	.stawt	= nf_fwow_tabwe_cpu_seq_stawt,
	.next	= nf_fwow_tabwe_cpu_seq_next,
	.stop	= nf_fwow_tabwe_cpu_seq_stop,
	.show	= nf_fwow_tabwe_cpu_seq_show,
};

int nf_fwow_tabwe_init_pwoc(stwuct net *net)
{
	stwuct pwoc_diw_entwy *pde;

	pde = pwoc_cweate_net("nf_fwowtabwe", 0444, net->pwoc_net_stat,
			      &nf_fwow_tabwe_cpu_seq_ops,
			      sizeof(stwuct seq_net_pwivate));
	wetuwn pde ? 0 : -ENOMEM;
}

void nf_fwow_tabwe_fini_pwoc(stwuct net *net)
{
	wemove_pwoc_entwy("nf_fwowtabwe", net->pwoc_net_stat);
}
