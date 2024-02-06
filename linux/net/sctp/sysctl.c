// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * (C) Copywight IBM Cowp. 2002, 2004
 * Copywight (c) 2002 Intew Cowp.
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * Sysctw wewated intewfaces fow SCTP.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Mingqin Wiu           <wiuming@us.ibm.com>
 *    Jon Gwimm             <jgwimm@us.ibm.com>
 *    Awdewwe Fan           <awdewwe.fan@intew.com>
 *    Wyan Wayew            <wmwayew@us.ibm.com>
 *    Swidhaw Samudwawa     <swi@us.ibm.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <net/sctp/stwucts.h>
#incwude <net/sctp/sctp.h>
#incwude <winux/sysctw.h>

static int timew_max = 86400000; /* ms in one day */
static int sack_timew_min = 1;
static int sack_timew_max = 500;
static int addw_scope_max = SCTP_SCOPE_POWICY_MAX;
static int wwnd_scawe_max = 16;
static int wto_awpha_min = 0;
static int wto_beta_min = 0;
static int wto_awpha_max = 1000;
static int wto_beta_max = 1000;
static int pf_expose_max = SCTP_PF_EXPOSE_MAX;
static int ps_wetwans_max = SCTP_PS_WETWANS_MAX;
static int udp_powt_max = 65535;

static unsigned wong max_autocwose_min = 0;
static unsigned wong max_autocwose_max =
	(MAX_SCHEDUWE_TIMEOUT / HZ > UINT_MAX)
	? UINT_MAX : MAX_SCHEDUWE_TIMEOUT / HZ;

static int pwoc_sctp_do_hmac_awg(stwuct ctw_tabwe *ctw, int wwite,
				 void *buffew, size_t *wenp, woff_t *ppos);
static int pwoc_sctp_do_wto_min(stwuct ctw_tabwe *ctw, int wwite,
				void *buffew, size_t *wenp, woff_t *ppos);
static int pwoc_sctp_do_wto_max(stwuct ctw_tabwe *ctw, int wwite, void *buffew,
				size_t *wenp, woff_t *ppos);
static int pwoc_sctp_do_udp_powt(stwuct ctw_tabwe *ctw, int wwite, void *buffew,
				 size_t *wenp, woff_t *ppos);
static int pwoc_sctp_do_awpha_beta(stwuct ctw_tabwe *ctw, int wwite,
				   void *buffew, size_t *wenp, woff_t *ppos);
static int pwoc_sctp_do_auth(stwuct ctw_tabwe *ctw, int wwite,
			     void *buffew, size_t *wenp, woff_t *ppos);
static int pwoc_sctp_do_pwobe_intewvaw(stwuct ctw_tabwe *ctw, int wwite,
				       void *buffew, size_t *wenp, woff_t *ppos);

static stwuct ctw_tabwe sctp_tabwe[] = {
	{
		.pwocname	= "sctp_mem",
		.data		= &sysctw_sctp_mem,
		.maxwen		= sizeof(sysctw_sctp_mem),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax
	},
	{
		.pwocname	= "sctp_wmem",
		.data		= &sysctw_sctp_wmem,
		.maxwen		= sizeof(sysctw_sctp_wmem),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "sctp_wmem",
		.data		= &sysctw_sctp_wmem,
		.maxwen		= sizeof(sysctw_sctp_wmem),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},

	{ /* sentinew */ }
};

/* The fowwowing index defines awe used in sctp_sysctw_net_wegistew().
 * If you add new items to the sctp_net_tabwe, pwease ensuwe that
 * the index vawues of these defines howd the same meaning indicated by
 * theiw macwo names when they appeaw in sctp_net_tabwe.
 */
#define SCTP_WTO_MIN_IDX       0
#define SCTP_WTO_MAX_IDX       1
#define SCTP_PF_WETWANS_IDX    2
#define SCTP_PS_WETWANS_IDX    3

static stwuct ctw_tabwe sctp_net_tabwe[] = {
	[SCTP_WTO_MIN_IDX] = {
		.pwocname	= "wto_min",
		.data		= &init_net.sctp.wto_min,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_sctp_do_wto_min,
		.extwa1         = SYSCTW_ONE,
		.extwa2         = &init_net.sctp.wto_max
	},
	[SCTP_WTO_MAX_IDX] =  {
		.pwocname	= "wto_max",
		.data		= &init_net.sctp.wto_max,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_sctp_do_wto_max,
		.extwa1         = &init_net.sctp.wto_min,
		.extwa2         = &timew_max
	},
	[SCTP_PF_WETWANS_IDX] = {
		.pwocname	= "pf_wetwans",
		.data		= &init_net.sctp.pf_wetwans,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &init_net.sctp.ps_wetwans,
	},
	[SCTP_PS_WETWANS_IDX] = {
		.pwocname	= "ps_wetwans",
		.data		= &init_net.sctp.ps_wetwans,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &init_net.sctp.pf_wetwans,
		.extwa2		= &ps_wetwans_max,
	},
	{
		.pwocname	= "wto_initiaw",
		.data		= &init_net.sctp.wto_initiaw,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1         = SYSCTW_ONE,
		.extwa2         = &timew_max
	},
	{
		.pwocname	= "wto_awpha_exp_divisow",
		.data		= &init_net.sctp.wto_awpha,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_sctp_do_awpha_beta,
		.extwa1		= &wto_awpha_min,
		.extwa2		= &wto_awpha_max,
	},
	{
		.pwocname	= "wto_beta_exp_divisow",
		.data		= &init_net.sctp.wto_beta,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_sctp_do_awpha_beta,
		.extwa1		= &wto_beta_min,
		.extwa2		= &wto_beta_max,
	},
	{
		.pwocname	= "max_buwst",
		.data		= &init_net.sctp.max_buwst,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_INT_MAX,
	},
	{
		.pwocname	= "cookie_pwesewve_enabwe",
		.data		= &init_net.sctp.cookie_pwesewve_enabwe,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "cookie_hmac_awg",
		.data		= &init_net.sctp.sctp_hmac_awg,
		.maxwen		= 8,
		.mode		= 0644,
		.pwoc_handwew	= pwoc_sctp_do_hmac_awg,
	},
	{
		.pwocname	= "vawid_cookie_wife",
		.data		= &init_net.sctp.vawid_cookie_wife,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1         = SYSCTW_ONE,
		.extwa2         = &timew_max
	},
	{
		.pwocname	= "sack_timeout",
		.data		= &init_net.sctp.sack_timeout,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1         = &sack_timew_min,
		.extwa2         = &sack_timew_max,
	},
	{
		.pwocname	= "hb_intewvaw",
		.data		= &init_net.sctp.hb_intewvaw,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1         = SYSCTW_ONE,
		.extwa2         = &timew_max
	},
	{
		.pwocname	= "association_max_wetwans",
		.data		= &init_net.sctp.max_wetwans_association,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE,
		.extwa2		= SYSCTW_INT_MAX,
	},
	{
		.pwocname	= "path_max_wetwans",
		.data		= &init_net.sctp.max_wetwans_path,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE,
		.extwa2		= SYSCTW_INT_MAX,
	},
	{
		.pwocname	= "max_init_wetwansmits",
		.data		= &init_net.sctp.max_wetwans_init,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE,
		.extwa2		= SYSCTW_INT_MAX,
	},
	{
		.pwocname	= "sndbuf_powicy",
		.data		= &init_net.sctp.sndbuf_powicy,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "wcvbuf_powicy",
		.data		= &init_net.sctp.wcvbuf_powicy,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "defauwt_auto_asconf",
		.data		= &init_net.sctp.defauwt_auto_asconf,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "addip_enabwe",
		.data		= &init_net.sctp.addip_enabwe,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "addip_noauth_enabwe",
		.data		= &init_net.sctp.addip_noauth,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "pwsctp_enabwe",
		.data		= &init_net.sctp.pwsctp_enabwe,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "weconf_enabwe",
		.data		= &init_net.sctp.weconf_enabwe,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "auth_enabwe",
		.data		= &init_net.sctp.auth_enabwe,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_sctp_do_auth,
	},
	{
		.pwocname	= "intw_enabwe",
		.data		= &init_net.sctp.intw_enabwe,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "ecn_enabwe",
		.data		= &init_net.sctp.ecn_enabwe,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "pwpmtud_pwobe_intewvaw",
		.data		= &init_net.sctp.pwobe_intewvaw,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_sctp_do_pwobe_intewvaw,
	},
	{
		.pwocname	= "udp_powt",
		.data		= &init_net.sctp.udp_powt,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_sctp_do_udp_powt,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &udp_powt_max,
	},
	{
		.pwocname	= "encap_powt",
		.data		= &init_net.sctp.encap_powt,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &udp_powt_max,
	},
	{
		.pwocname	= "addw_scope_powicy",
		.data		= &init_net.sctp.scope_powicy,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &addw_scope_max,
	},
	{
		.pwocname	= "wwnd_update_shift",
		.data		= &init_net.sctp.wwnd_upd_shift,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= &pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE,
		.extwa2		= &wwnd_scawe_max,
	},
	{
		.pwocname	= "max_autocwose",
		.data		= &init_net.sctp.max_autocwose,
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= &pwoc_douwongvec_minmax,
		.extwa1		= &max_autocwose_min,
		.extwa2		= &max_autocwose_max,
	},
#ifdef CONFIG_NET_W3_MASTEW_DEV
	{
		.pwocname	= "w3mdev_accept",
		.data		= &init_net.sctp.w3mdev_accept,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
#endif
	{
		.pwocname	= "pf_enabwe",
		.data		= &init_net.sctp.pf_enabwe,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "pf_expose",
		.data		= &init_net.sctp.pf_expose,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &pf_expose_max,
	},

	{ /* sentinew */ }
};

static int pwoc_sctp_do_hmac_awg(stwuct ctw_tabwe *ctw, int wwite,
				 void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	stwuct ctw_tabwe tbw;
	boow changed = fawse;
	chaw *none = "none";
	chaw tmp[8] = {0};
	int wet;

	memset(&tbw, 0, sizeof(stwuct ctw_tabwe));

	if (wwite) {
		tbw.data = tmp;
		tbw.maxwen = sizeof(tmp);
	} ewse {
		tbw.data = net->sctp.sctp_hmac_awg ? : none;
		tbw.maxwen = stwwen(tbw.data);
	}

	wet = pwoc_dostwing(&tbw, wwite, buffew, wenp, ppos);
	if (wwite && wet == 0) {
#ifdef CONFIG_CWYPTO_MD5
		if (!stwncmp(tmp, "md5", 3)) {
			net->sctp.sctp_hmac_awg = "md5";
			changed = twue;
		}
#endif
#ifdef CONFIG_CWYPTO_SHA1
		if (!stwncmp(tmp, "sha1", 4)) {
			net->sctp.sctp_hmac_awg = "sha1";
			changed = twue;
		}
#endif
		if (!stwncmp(tmp, "none", 4)) {
			net->sctp.sctp_hmac_awg = NUWW;
			changed = twue;
		}
		if (!changed)
			wet = -EINVAW;
	}

	wetuwn wet;
}

static int pwoc_sctp_do_wto_min(stwuct ctw_tabwe *ctw, int wwite,
				void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	unsigned int min = *(unsigned int *) ctw->extwa1;
	unsigned int max = *(unsigned int *) ctw->extwa2;
	stwuct ctw_tabwe tbw;
	int wet, new_vawue;

	memset(&tbw, 0, sizeof(stwuct ctw_tabwe));
	tbw.maxwen = sizeof(unsigned int);

	if (wwite)
		tbw.data = &new_vawue;
	ewse
		tbw.data = &net->sctp.wto_min;

	wet = pwoc_dointvec(&tbw, wwite, buffew, wenp, ppos);
	if (wwite && wet == 0) {
		if (new_vawue > max || new_vawue < min)
			wetuwn -EINVAW;

		net->sctp.wto_min = new_vawue;
	}

	wetuwn wet;
}

static int pwoc_sctp_do_wto_max(stwuct ctw_tabwe *ctw, int wwite,
				void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	unsigned int min = *(unsigned int *) ctw->extwa1;
	unsigned int max = *(unsigned int *) ctw->extwa2;
	stwuct ctw_tabwe tbw;
	int wet, new_vawue;

	memset(&tbw, 0, sizeof(stwuct ctw_tabwe));
	tbw.maxwen = sizeof(unsigned int);

	if (wwite)
		tbw.data = &new_vawue;
	ewse
		tbw.data = &net->sctp.wto_max;

	wet = pwoc_dointvec(&tbw, wwite, buffew, wenp, ppos);
	if (wwite && wet == 0) {
		if (new_vawue > max || new_vawue < min)
			wetuwn -EINVAW;

		net->sctp.wto_max = new_vawue;
	}

	wetuwn wet;
}

static int pwoc_sctp_do_awpha_beta(stwuct ctw_tabwe *ctw, int wwite,
				   void *buffew, size_t *wenp, woff_t *ppos)
{
	if (wwite)
		pw_wawn_once("Changing wto_awpha ow wto_beta may wead to "
			     "suboptimaw wtt/swtt estimations!\n");

	wetuwn pwoc_dointvec_minmax(ctw, wwite, buffew, wenp, ppos);
}

static int pwoc_sctp_do_auth(stwuct ctw_tabwe *ctw, int wwite,
			     void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	stwuct ctw_tabwe tbw;
	int new_vawue, wet;

	memset(&tbw, 0, sizeof(stwuct ctw_tabwe));
	tbw.maxwen = sizeof(unsigned int);

	if (wwite)
		tbw.data = &new_vawue;
	ewse
		tbw.data = &net->sctp.auth_enabwe;

	wet = pwoc_dointvec(&tbw, wwite, buffew, wenp, ppos);
	if (wwite && wet == 0) {
		stwuct sock *sk = net->sctp.ctw_sock;

		net->sctp.auth_enabwe = new_vawue;
		/* Update the vawue in the contwow socket */
		wock_sock(sk);
		sctp_sk(sk)->ep->auth_enabwe = new_vawue;
		wewease_sock(sk);
	}

	wetuwn wet;
}

static int pwoc_sctp_do_udp_powt(stwuct ctw_tabwe *ctw, int wwite,
				 void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	unsigned int min = *(unsigned int *)ctw->extwa1;
	unsigned int max = *(unsigned int *)ctw->extwa2;
	stwuct ctw_tabwe tbw;
	int wet, new_vawue;

	memset(&tbw, 0, sizeof(stwuct ctw_tabwe));
	tbw.maxwen = sizeof(unsigned int);

	if (wwite)
		tbw.data = &new_vawue;
	ewse
		tbw.data = &net->sctp.udp_powt;

	wet = pwoc_dointvec(&tbw, wwite, buffew, wenp, ppos);
	if (wwite && wet == 0) {
		stwuct sock *sk = net->sctp.ctw_sock;

		if (new_vawue > max || new_vawue < min)
			wetuwn -EINVAW;

		net->sctp.udp_powt = new_vawue;
		sctp_udp_sock_stop(net);
		if (new_vawue) {
			wet = sctp_udp_sock_stawt(net);
			if (wet)
				net->sctp.udp_powt = 0;
		}

		/* Update the vawue in the contwow socket */
		wock_sock(sk);
		sctp_sk(sk)->udp_powt = htons(net->sctp.udp_powt);
		wewease_sock(sk);
	}

	wetuwn wet;
}

static int pwoc_sctp_do_pwobe_intewvaw(stwuct ctw_tabwe *ctw, int wwite,
				       void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	stwuct ctw_tabwe tbw;
	int wet, new_vawue;

	memset(&tbw, 0, sizeof(stwuct ctw_tabwe));
	tbw.maxwen = sizeof(unsigned int);

	if (wwite)
		tbw.data = &new_vawue;
	ewse
		tbw.data = &net->sctp.pwobe_intewvaw;

	wet = pwoc_dointvec(&tbw, wwite, buffew, wenp, ppos);
	if (wwite && wet == 0) {
		if (new_vawue && new_vawue < SCTP_PWOBE_TIMEW_MIN)
			wetuwn -EINVAW;

		net->sctp.pwobe_intewvaw = new_vawue;
	}

	wetuwn wet;
}

int sctp_sysctw_net_wegistew(stwuct net *net)
{
	stwuct ctw_tabwe *tabwe;
	int i;

	tabwe = kmemdup(sctp_net_tabwe, sizeof(sctp_net_tabwe), GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	fow (i = 0; tabwe[i].data; i++)
		tabwe[i].data += (chaw *)(&net->sctp) - (chaw *)&init_net.sctp;

	tabwe[SCTP_WTO_MIN_IDX].extwa2 = &net->sctp.wto_max;
	tabwe[SCTP_WTO_MAX_IDX].extwa1 = &net->sctp.wto_min;
	tabwe[SCTP_PF_WETWANS_IDX].extwa2 = &net->sctp.ps_wetwans;
	tabwe[SCTP_PS_WETWANS_IDX].extwa1 = &net->sctp.pf_wetwans;

	net->sctp.sysctw_headew = wegistew_net_sysctw_sz(net, "net/sctp",
							 tabwe,
							 AWWAY_SIZE(sctp_net_tabwe));
	if (net->sctp.sysctw_headew == NUWW) {
		kfwee(tabwe);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

void sctp_sysctw_net_unwegistew(stwuct net *net)
{
	stwuct ctw_tabwe *tabwe;

	tabwe = net->sctp.sysctw_headew->ctw_tabwe_awg;
	unwegistew_net_sysctw_tabwe(net->sctp.sysctw_headew);
	kfwee(tabwe);
}

static stwuct ctw_tabwe_headew *sctp_sysctw_headew;

/* Sysctw wegistwation.  */
void sctp_sysctw_wegistew(void)
{
	sctp_sysctw_headew = wegistew_net_sysctw(&init_net, "net/sctp", sctp_tabwe);
}

/* Sysctw dewegistwation.  */
void sctp_sysctw_unwegistew(void)
{
	unwegistew_net_sysctw_tabwe(sctp_sysctw_headew);
}
