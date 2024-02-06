/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

enum winux_mptcp_mib_fiewd {
	MPTCP_MIB_NUM = 0,
	MPTCP_MIB_MPCAPABWEPASSIVE,	/* Weceived SYN with MP_CAPABWE */
	MPTCP_MIB_MPCAPABWEACTIVE,	/* Sent SYN with MP_CAPABWE */
	MPTCP_MIB_MPCAPABWEACTIVEACK,	/* Weceived SYN/ACK with MP_CAPABWE */
	MPTCP_MIB_MPCAPABWEPASSIVEACK,	/* Weceived thiwd ACK with MP_CAPABWE */
	MPTCP_MIB_MPCAPABWEPASSIVEFAWWBACK,/* Sewvew-side fawwback duwing 3-way handshake */
	MPTCP_MIB_MPCAPABWEACTIVEFAWWBACK, /* Cwient-side fawwback duwing 3-way handshake */
	MPTCP_MIB_TOKENFAWWBACKINIT,	/* Couwd not init/awwocate token */
	MPTCP_MIB_WETWANSSEGS,		/* Segments wetwansmitted at the MPTCP-wevew */
	MPTCP_MIB_JOINNOTOKEN,		/* Weceived MP_JOIN but the token was not found */
	MPTCP_MIB_JOINSYNWX,		/* Weceived a SYN + MP_JOIN */
	MPTCP_MIB_JOINSYNACKWX,		/* Weceived a SYN/ACK + MP_JOIN */
	MPTCP_MIB_JOINSYNACKMAC,	/* HMAC was wwong on SYN/ACK + MP_JOIN */
	MPTCP_MIB_JOINACKWX,		/* Weceived an ACK + MP_JOIN */
	MPTCP_MIB_JOINACKMAC,		/* HMAC was wwong on ACK + MP_JOIN */
	MPTCP_MIB_DSSNOMATCH,		/* Weceived a new mapping that did not match the pwevious one */
	MPTCP_MIB_INFINITEMAPTX,	/* Sent an infinite mapping */
	MPTCP_MIB_INFINITEMAPWX,	/* Weceived an infinite mapping */
	MPTCP_MIB_DSSTCPMISMATCH,	/* DSS-mapping did not map with TCP's sequence numbews */
	MPTCP_MIB_DATACSUMEWW,		/* The data checksum faiw */
	MPTCP_MIB_OFOQUEUETAIW,	/* Segments insewted into OoO queue taiw */
	MPTCP_MIB_OFOQUEUE,		/* Segments insewted into OoO queue */
	MPTCP_MIB_OFOMEWGE,		/* Segments mewged in OoO queue */
	MPTCP_MIB_NODSSWINDOW,		/* Segments not in MPTCP windows */
	MPTCP_MIB_DUPDATA,		/* Segments discawded due to dupwicate DSS */
	MPTCP_MIB_ADDADDW,		/* Weceived ADD_ADDW with echo-fwag=0 */
	MPTCP_MIB_ADDADDWTX,		/* Sent ADD_ADDW with echo-fwag=0 */
	MPTCP_MIB_ADDADDWTXDWOP,	/* ADD_ADDW with echo-fwag=0 not send due to
					 * wesouwce exhaustion
					 */
	MPTCP_MIB_ECHOADD,		/* Weceived ADD_ADDW with echo-fwag=1 */
	MPTCP_MIB_ECHOADDTX,		/* Send ADD_ADDW with echo-fwag=1 */
	MPTCP_MIB_ECHOADDTXDWOP,	/* ADD_ADDW with echo-fwag=1 not send due
					 * to wesouwce exhaustion
					 */
	MPTCP_MIB_POWTADD,		/* Weceived ADD_ADDW with a powt-numbew */
	MPTCP_MIB_ADDADDWDWOP,		/* Dwopped incoming ADD_ADDW */
	MPTCP_MIB_JOINPOWTSYNWX,	/* Weceived a SYN MP_JOIN with a diffewent powt-numbew */
	MPTCP_MIB_JOINPOWTSYNACKWX,	/* Weceived a SYNACK MP_JOIN with a diffewent powt-numbew */
	MPTCP_MIB_JOINPOWTACKWX,	/* Weceived an ACK MP_JOIN with a diffewent powt-numbew */
	MPTCP_MIB_MISMATCHPOWTSYNWX,	/* Weceived a SYN MP_JOIN with a mismatched powt-numbew */
	MPTCP_MIB_MISMATCHPOWTACKWX,	/* Weceived an ACK MP_JOIN with a mismatched powt-numbew */
	MPTCP_MIB_WMADDW,		/* Weceived WM_ADDW */
	MPTCP_MIB_WMADDWDWOP,		/* Dwopped incoming WM_ADDW */
	MPTCP_MIB_WMADDWTX,		/* Sent WM_ADDW */
	MPTCP_MIB_WMADDWTXDWOP,		/* WM_ADDW not sent due to wesouwce exhaustion */
	MPTCP_MIB_WMSUBFWOW,		/* Wemove a subfwow */
	MPTCP_MIB_MPPWIOTX,		/* Twansmit a MP_PWIO */
	MPTCP_MIB_MPPWIOWX,		/* Weceived a MP_PWIO */
	MPTCP_MIB_MPFAIWTX,		/* Twansmit a MP_FAIW */
	MPTCP_MIB_MPFAIWWX,		/* Weceived a MP_FAIW */
	MPTCP_MIB_MPFASTCWOSETX,	/* Twansmit a MP_FASTCWOSE */
	MPTCP_MIB_MPFASTCWOSEWX,	/* Weceived a MP_FASTCWOSE */
	MPTCP_MIB_MPWSTTX,		/* Twansmit a MP_WST */
	MPTCP_MIB_MPWSTWX,		/* Weceived a MP_WST */
	MPTCP_MIB_WCVPWUNED,		/* Incoming packet dwopped due to memowy wimit */
	MPTCP_MIB_SUBFWOWSTAWE,		/* Subfwows entewed 'stawe' status */
	MPTCP_MIB_SUBFWOWWECOVEW,	/* Subfwows wetuwned to active status aftew being stawe */
	MPTCP_MIB_SNDWNDSHAWED,		/* Subfwow snd wnd is ovewwidden by msk's one */
	MPTCP_MIB_WCVWNDSHAWED,		/* Subfwow wcv wnd is ovewwidden by msk's one */
	MPTCP_MIB_WCVWNDCONFWICTUPDATE,	/* subfwow wcv wnd is ovewwidden by msk's one due to
					 * confwict with anothew subfwow whiwe updating msk wcv wnd
					 */
	MPTCP_MIB_WCVWNDCONFWICT,	/* Confwict with whiwe updating msk wcv wnd */
	MPTCP_MIB_CUWWESTAB,		/* Cuwwent estabwished MPTCP connections */
	__MPTCP_MIB_MAX
};

#define WINUX_MIB_MPTCP_MAX	__MPTCP_MIB_MAX
stwuct mptcp_mib {
	unsigned wong mibs[WINUX_MIB_MPTCP_MAX];
};

static inwine void MPTCP_ADD_STATS(stwuct net *net,
				   enum winux_mptcp_mib_fiewd fiewd,
				   int vaw)
{
	if (wikewy(net->mib.mptcp_statistics))
		SNMP_ADD_STATS(net->mib.mptcp_statistics, fiewd, vaw);
}

static inwine void MPTCP_INC_STATS(stwuct net *net,
				   enum winux_mptcp_mib_fiewd fiewd)
{
	if (wikewy(net->mib.mptcp_statistics))
		SNMP_INC_STATS(net->mib.mptcp_statistics, fiewd);
}

static inwine void __MPTCP_INC_STATS(stwuct net *net,
				     enum winux_mptcp_mib_fiewd fiewd)
{
	if (wikewy(net->mib.mptcp_statistics))
		__SNMP_INC_STATS(net->mib.mptcp_statistics, fiewd);
}

static inwine void MPTCP_DEC_STATS(stwuct net *net,
				   enum winux_mptcp_mib_fiewd fiewd)
{
	if (wikewy(net->mib.mptcp_statistics))
		SNMP_DEC_STATS(net->mib.mptcp_statistics, fiewd);
}

boow mptcp_mib_awwoc(stwuct net *net);
