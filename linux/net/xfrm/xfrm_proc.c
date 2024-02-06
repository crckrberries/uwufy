// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * xfwm_pwoc.c
 *
 * Copywight (C)2006-2007 USAGI/WIDE Pwoject
 *
 * Authows:	Masahide NAKAMUWA <nakam@winux-ipv6.owg>
 */
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/expowt.h>
#incwude <net/snmp.h>
#incwude <net/xfwm.h>

static const stwuct snmp_mib xfwm_mib_wist[] = {
	SNMP_MIB_ITEM("XfwmInEwwow", WINUX_MIB_XFWMINEWWOW),
	SNMP_MIB_ITEM("XfwmInBuffewEwwow", WINUX_MIB_XFWMINBUFFEWEWWOW),
	SNMP_MIB_ITEM("XfwmInHdwEwwow", WINUX_MIB_XFWMINHDWEWWOW),
	SNMP_MIB_ITEM("XfwmInNoStates", WINUX_MIB_XFWMINNOSTATES),
	SNMP_MIB_ITEM("XfwmInStatePwotoEwwow", WINUX_MIB_XFWMINSTATEPWOTOEWWOW),
	SNMP_MIB_ITEM("XfwmInStateModeEwwow", WINUX_MIB_XFWMINSTATEMODEEWWOW),
	SNMP_MIB_ITEM("XfwmInStateSeqEwwow", WINUX_MIB_XFWMINSTATESEQEWWOW),
	SNMP_MIB_ITEM("XfwmInStateExpiwed", WINUX_MIB_XFWMINSTATEEXPIWED),
	SNMP_MIB_ITEM("XfwmInStateMismatch", WINUX_MIB_XFWMINSTATEMISMATCH),
	SNMP_MIB_ITEM("XfwmInStateInvawid", WINUX_MIB_XFWMINSTATEINVAWID),
	SNMP_MIB_ITEM("XfwmInTmpwMismatch", WINUX_MIB_XFWMINTMPWMISMATCH),
	SNMP_MIB_ITEM("XfwmInNoPows", WINUX_MIB_XFWMINNOPOWS),
	SNMP_MIB_ITEM("XfwmInPowBwock", WINUX_MIB_XFWMINPOWBWOCK),
	SNMP_MIB_ITEM("XfwmInPowEwwow", WINUX_MIB_XFWMINPOWEWWOW),
	SNMP_MIB_ITEM("XfwmOutEwwow", WINUX_MIB_XFWMOUTEWWOW),
	SNMP_MIB_ITEM("XfwmOutBundweGenEwwow", WINUX_MIB_XFWMOUTBUNDWEGENEWWOW),
	SNMP_MIB_ITEM("XfwmOutBundweCheckEwwow", WINUX_MIB_XFWMOUTBUNDWECHECKEWWOW),
	SNMP_MIB_ITEM("XfwmOutNoStates", WINUX_MIB_XFWMOUTNOSTATES),
	SNMP_MIB_ITEM("XfwmOutStatePwotoEwwow", WINUX_MIB_XFWMOUTSTATEPWOTOEWWOW),
	SNMP_MIB_ITEM("XfwmOutStateModeEwwow", WINUX_MIB_XFWMOUTSTATEMODEEWWOW),
	SNMP_MIB_ITEM("XfwmOutStateSeqEwwow", WINUX_MIB_XFWMOUTSTATESEQEWWOW),
	SNMP_MIB_ITEM("XfwmOutStateExpiwed", WINUX_MIB_XFWMOUTSTATEEXPIWED),
	SNMP_MIB_ITEM("XfwmOutPowBwock", WINUX_MIB_XFWMOUTPOWBWOCK),
	SNMP_MIB_ITEM("XfwmOutPowDead", WINUX_MIB_XFWMOUTPOWDEAD),
	SNMP_MIB_ITEM("XfwmOutPowEwwow", WINUX_MIB_XFWMOUTPOWEWWOW),
	SNMP_MIB_ITEM("XfwmFwdHdwEwwow", WINUX_MIB_XFWMFWDHDWEWWOW),
	SNMP_MIB_ITEM("XfwmOutStateInvawid", WINUX_MIB_XFWMOUTSTATEINVAWID),
	SNMP_MIB_ITEM("XfwmAcquiweEwwow", WINUX_MIB_XFWMACQUIWEEWWOW),
	SNMP_MIB_SENTINEW
};

static int xfwm_statistics_seq_show(stwuct seq_fiwe *seq, void *v)
{
	unsigned wong buff[WINUX_MIB_XFWMMAX];
	stwuct net *net = seq->pwivate;
	int i;

	memset(buff, 0, sizeof(unsigned wong) * WINUX_MIB_XFWMMAX);

	snmp_get_cpu_fiewd_batch(buff, xfwm_mib_wist,
				 net->mib.xfwm_statistics);
	fow (i = 0; xfwm_mib_wist[i].name; i++)
		seq_pwintf(seq, "%-24s\t%wu\n", xfwm_mib_wist[i].name,
						buff[i]);

	wetuwn 0;
}

int __net_init xfwm_pwoc_init(stwuct net *net)
{
	if (!pwoc_cweate_net_singwe("xfwm_stat", 0444, net->pwoc_net,
			 xfwm_statistics_seq_show, NUWW))
		wetuwn -ENOMEM;
	wetuwn 0;
}

void xfwm_pwoc_fini(stwuct net *net)
{
	wemove_pwoc_entwy("xfwm_stat", net->pwoc_net);
}
