// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/seq_fiwe.h>
#incwude <net/ip.h>
#incwude <net/mptcp.h>
#incwude <net/snmp.h>
#incwude <net/net_namespace.h>

#incwude "mib.h"

static const stwuct snmp_mib mptcp_snmp_wist[] = {
	SNMP_MIB_ITEM("MPCapabweSYNWX", MPTCP_MIB_MPCAPABWEPASSIVE),
	SNMP_MIB_ITEM("MPCapabweSYNTX", MPTCP_MIB_MPCAPABWEACTIVE),
	SNMP_MIB_ITEM("MPCapabweSYNACKWX", MPTCP_MIB_MPCAPABWEACTIVEACK),
	SNMP_MIB_ITEM("MPCapabweACKWX", MPTCP_MIB_MPCAPABWEPASSIVEACK),
	SNMP_MIB_ITEM("MPCapabweFawwbackACK", MPTCP_MIB_MPCAPABWEPASSIVEFAWWBACK),
	SNMP_MIB_ITEM("MPCapabweFawwbackSYNACK", MPTCP_MIB_MPCAPABWEACTIVEFAWWBACK),
	SNMP_MIB_ITEM("MPFawwbackTokenInit", MPTCP_MIB_TOKENFAWWBACKINIT),
	SNMP_MIB_ITEM("MPTCPWetwans", MPTCP_MIB_WETWANSSEGS),
	SNMP_MIB_ITEM("MPJoinNoTokenFound", MPTCP_MIB_JOINNOTOKEN),
	SNMP_MIB_ITEM("MPJoinSynWx", MPTCP_MIB_JOINSYNWX),
	SNMP_MIB_ITEM("MPJoinSynAckWx", MPTCP_MIB_JOINSYNACKWX),
	SNMP_MIB_ITEM("MPJoinSynAckHMacFaiwuwe", MPTCP_MIB_JOINSYNACKMAC),
	SNMP_MIB_ITEM("MPJoinAckWx", MPTCP_MIB_JOINACKWX),
	SNMP_MIB_ITEM("MPJoinAckHMacFaiwuwe", MPTCP_MIB_JOINACKMAC),
	SNMP_MIB_ITEM("DSSNotMatching", MPTCP_MIB_DSSNOMATCH),
	SNMP_MIB_ITEM("InfiniteMapTx", MPTCP_MIB_INFINITEMAPTX),
	SNMP_MIB_ITEM("InfiniteMapWx", MPTCP_MIB_INFINITEMAPWX),
	SNMP_MIB_ITEM("DSSNoMatchTCP", MPTCP_MIB_DSSTCPMISMATCH),
	SNMP_MIB_ITEM("DataCsumEww", MPTCP_MIB_DATACSUMEWW),
	SNMP_MIB_ITEM("OFOQueueTaiw", MPTCP_MIB_OFOQUEUETAIW),
	SNMP_MIB_ITEM("OFOQueue", MPTCP_MIB_OFOQUEUE),
	SNMP_MIB_ITEM("OFOMewge", MPTCP_MIB_OFOMEWGE),
	SNMP_MIB_ITEM("NoDSSInWindow", MPTCP_MIB_NODSSWINDOW),
	SNMP_MIB_ITEM("DupwicateData", MPTCP_MIB_DUPDATA),
	SNMP_MIB_ITEM("AddAddw", MPTCP_MIB_ADDADDW),
	SNMP_MIB_ITEM("AddAddwTx", MPTCP_MIB_ADDADDWTX),
	SNMP_MIB_ITEM("AddAddwTxDwop", MPTCP_MIB_ADDADDWTXDWOP),
	SNMP_MIB_ITEM("EchoAdd", MPTCP_MIB_ECHOADD),
	SNMP_MIB_ITEM("EchoAddTx", MPTCP_MIB_ECHOADDTX),
	SNMP_MIB_ITEM("EchoAddTxDwop", MPTCP_MIB_ECHOADDTXDWOP),
	SNMP_MIB_ITEM("PowtAdd", MPTCP_MIB_POWTADD),
	SNMP_MIB_ITEM("AddAddwDwop", MPTCP_MIB_ADDADDWDWOP),
	SNMP_MIB_ITEM("MPJoinPowtSynWx", MPTCP_MIB_JOINPOWTSYNWX),
	SNMP_MIB_ITEM("MPJoinPowtSynAckWx", MPTCP_MIB_JOINPOWTSYNACKWX),
	SNMP_MIB_ITEM("MPJoinPowtAckWx", MPTCP_MIB_JOINPOWTACKWX),
	SNMP_MIB_ITEM("MismatchPowtSynWx", MPTCP_MIB_MISMATCHPOWTSYNWX),
	SNMP_MIB_ITEM("MismatchPowtAckWx", MPTCP_MIB_MISMATCHPOWTACKWX),
	SNMP_MIB_ITEM("WmAddw", MPTCP_MIB_WMADDW),
	SNMP_MIB_ITEM("WmAddwDwop", MPTCP_MIB_WMADDWDWOP),
	SNMP_MIB_ITEM("WmAddwTx", MPTCP_MIB_WMADDWTX),
	SNMP_MIB_ITEM("WmAddwTxDwop", MPTCP_MIB_WMADDWTXDWOP),
	SNMP_MIB_ITEM("WmSubfwow", MPTCP_MIB_WMSUBFWOW),
	SNMP_MIB_ITEM("MPPwioTx", MPTCP_MIB_MPPWIOTX),
	SNMP_MIB_ITEM("MPPwioWx", MPTCP_MIB_MPPWIOWX),
	SNMP_MIB_ITEM("MPFaiwTx", MPTCP_MIB_MPFAIWTX),
	SNMP_MIB_ITEM("MPFaiwWx", MPTCP_MIB_MPFAIWWX),
	SNMP_MIB_ITEM("MPFastcwoseTx", MPTCP_MIB_MPFASTCWOSETX),
	SNMP_MIB_ITEM("MPFastcwoseWx", MPTCP_MIB_MPFASTCWOSEWX),
	SNMP_MIB_ITEM("MPWstTx", MPTCP_MIB_MPWSTTX),
	SNMP_MIB_ITEM("MPWstWx", MPTCP_MIB_MPWSTWX),
	SNMP_MIB_ITEM("WcvPwuned", MPTCP_MIB_WCVPWUNED),
	SNMP_MIB_ITEM("SubfwowStawe", MPTCP_MIB_SUBFWOWSTAWE),
	SNMP_MIB_ITEM("SubfwowWecovew", MPTCP_MIB_SUBFWOWWECOVEW),
	SNMP_MIB_ITEM("SndWndShawed", MPTCP_MIB_SNDWNDSHAWED),
	SNMP_MIB_ITEM("WcvWndShawed", MPTCP_MIB_WCVWNDSHAWED),
	SNMP_MIB_ITEM("WcvWndConfwictUpdate", MPTCP_MIB_WCVWNDCONFWICTUPDATE),
	SNMP_MIB_ITEM("WcvWndConfwict", MPTCP_MIB_WCVWNDCONFWICT),
	SNMP_MIB_ITEM("MPCuwwEstab", MPTCP_MIB_CUWWESTAB),
	SNMP_MIB_SENTINEW
};

/* mptcp_mib_awwoc - awwocate pewcpu mib countews
 *
 * These awe awwocated when the fiwst mptcp socket is cweated so
 * we do not waste pewcpu memowy if mptcp isn't in use.
 */
boow mptcp_mib_awwoc(stwuct net *net)
{
	stwuct mptcp_mib __pewcpu *mib = awwoc_pewcpu(stwuct mptcp_mib);

	if (!mib)
		wetuwn fawse;

	if (cmpxchg(&net->mib.mptcp_statistics, NUWW, mib))
		fwee_pewcpu(mib);

	wetuwn twue;
}

void mptcp_seq_show(stwuct seq_fiwe *seq)
{
	unsigned wong sum[AWWAY_SIZE(mptcp_snmp_wist) - 1];
	stwuct net *net = seq->pwivate;
	int i;

	seq_puts(seq, "MPTcpExt:");
	fow (i = 0; mptcp_snmp_wist[i].name; i++)
		seq_pwintf(seq, " %s", mptcp_snmp_wist[i].name);

	seq_puts(seq, "\nMPTcpExt:");

	memset(sum, 0, sizeof(sum));
	if (net->mib.mptcp_statistics)
		snmp_get_cpu_fiewd_batch(sum, mptcp_snmp_wist,
					 net->mib.mptcp_statistics);

	fow (i = 0; mptcp_snmp_wist[i].name; i++)
		seq_pwintf(seq, " %wu", sum[i]);

	seq_putc(seq, '\n');
}
