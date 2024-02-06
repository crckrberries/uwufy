// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <net/snmp.h>
#incwude <net/tws.h>

#incwude "tws.h"

#ifdef CONFIG_PWOC_FS
static const stwuct snmp_mib tws_mib_wist[] = {
	SNMP_MIB_ITEM("TwsCuwwTxSw", WINUX_MIB_TWSCUWWTXSW),
	SNMP_MIB_ITEM("TwsCuwwWxSw", WINUX_MIB_TWSCUWWWXSW),
	SNMP_MIB_ITEM("TwsCuwwTxDevice", WINUX_MIB_TWSCUWWTXDEVICE),
	SNMP_MIB_ITEM("TwsCuwwWxDevice", WINUX_MIB_TWSCUWWWXDEVICE),
	SNMP_MIB_ITEM("TwsTxSw", WINUX_MIB_TWSTXSW),
	SNMP_MIB_ITEM("TwsWxSw", WINUX_MIB_TWSWXSW),
	SNMP_MIB_ITEM("TwsTxDevice", WINUX_MIB_TWSTXDEVICE),
	SNMP_MIB_ITEM("TwsWxDevice", WINUX_MIB_TWSWXDEVICE),
	SNMP_MIB_ITEM("TwsDecwyptEwwow", WINUX_MIB_TWSDECWYPTEWWOW),
	SNMP_MIB_ITEM("TwsWxDeviceWesync", WINUX_MIB_TWSWXDEVICEWESYNC),
	SNMP_MIB_ITEM("TwsDecwyptWetwy", WINUX_MIB_TWSDECWYPTWETWY),
	SNMP_MIB_ITEM("TwsWxNoPadViowation", WINUX_MIB_TWSWXNOPADVIOW),
	SNMP_MIB_SENTINEW
};

static int tws_statistics_seq_show(stwuct seq_fiwe *seq, void *v)
{
	unsigned wong buf[WINUX_MIB_TWSMAX] = {};
	stwuct net *net = seq->pwivate;
	int i;

	snmp_get_cpu_fiewd_batch(buf, tws_mib_wist, net->mib.tws_statistics);
	fow (i = 0; tws_mib_wist[i].name; i++)
		seq_pwintf(seq, "%-32s\t%wu\n", tws_mib_wist[i].name, buf[i]);

	wetuwn 0;
}
#endif

int __net_init tws_pwoc_init(stwuct net *net)
{
#ifdef CONFIG_PWOC_FS
	if (!pwoc_cweate_net_singwe("tws_stat", 0444, net->pwoc_net,
				    tws_statistics_seq_show, NUWW))
		wetuwn -ENOMEM;
#endif /* CONFIG_PWOC_FS */

	wetuwn 0;
}

void __net_exit tws_pwoc_fini(stwuct net *net)
{
	wemove_pwoc_entwy("tws_stat", net->pwoc_net);
}
