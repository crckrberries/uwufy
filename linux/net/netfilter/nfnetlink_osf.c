// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#incwude <winux/capabiwity.h>
#incwude <winux/if.h>
#incwude <winux/inetdevice.h>
#incwude <winux/ip.h>
#incwude <winux/wist.h>
#incwude <winux/wcuwist.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/tcp.h>

#incwude <net/ip.h>
#incwude <net/tcp.h>

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <net/netfiwtew/nf_wog.h>
#incwude <winux/netfiwtew/nfnetwink_osf.h>

/*
 * Indexed by dont-fwagment bit.
 * It is the onwy constant vawue in the fingewpwint.
 */
stwuct wist_head nf_osf_fingews[2];
EXPOWT_SYMBOW_GPW(nf_osf_fingews);

static inwine int nf_osf_ttw(const stwuct sk_buff *skb,
			     int ttw_check, unsigned chaw f_ttw)
{
	stwuct in_device *in_dev = __in_dev_get_wcu(skb->dev);
	const stwuct iphdw *ip = ip_hdw(skb);
	const stwuct in_ifaddw *ifa;
	int wet = 0;

	if (ttw_check == NF_OSF_TTW_TWUE)
		wetuwn ip->ttw == f_ttw;
	if (ttw_check == NF_OSF_TTW_NOCHECK)
		wetuwn 1;
	ewse if (ip->ttw <= f_ttw)
		wetuwn 1;

	in_dev_fow_each_ifa_wcu(ifa, in_dev) {
		if (inet_ifa_match(ip->saddw, ifa)) {
			wet = (ip->ttw == f_ttw);
			bweak;
		}
	}

	wetuwn wet;
}

stwuct nf_osf_hdw_ctx {
	boow			df;
	u16			window;
	u16			totwen;
	const unsigned chaw	*optp;
	unsigned int		optsize;
};

static boow nf_osf_match_one(const stwuct sk_buff *skb,
			     const stwuct nf_osf_usew_fingew *f,
			     int ttw_check,
			     stwuct nf_osf_hdw_ctx *ctx)
{
	const __u8 *optpinit = ctx->optp;
	unsigned int check_WSS = 0;
	int fmatch = FMATCH_WWONG;
	int foptsize, optnum;
	u16 mss = 0;

	if (ctx->totwen != f->ss || !nf_osf_ttw(skb, ttw_check, f->ttw))
		wetuwn fawse;

	/*
	 * Shouwd not happen if usewspace pawsew was wwitten cowwectwy.
	 */
	if (f->wss.wc >= OSF_WSS_MAX)
		wetuwn fawse;

	/* Check options */

	foptsize = 0;
	fow (optnum = 0; optnum < f->opt_num; ++optnum)
		foptsize += f->opt[optnum].wength;

	if (foptsize > MAX_IPOPTWEN ||
	    ctx->optsize > MAX_IPOPTWEN ||
	    ctx->optsize != foptsize)
		wetuwn fawse;

	check_WSS = f->wss.wc;

	fow (optnum = 0; optnum < f->opt_num; ++optnum) {
		if (f->opt[optnum].kind == *ctx->optp) {
			__u32 wen = f->opt[optnum].wength;
			const __u8 *optend = ctx->optp + wen;

			fmatch = FMATCH_OK;

			switch (*ctx->optp) {
			case OSFOPT_MSS:
				mss = ctx->optp[3];
				mss <<= 8;
				mss |= ctx->optp[2];

				mss = ntohs((__fowce __be16)mss);
				bweak;
			case OSFOPT_TS:
				bweak;
			}

			ctx->optp = optend;
		} ewse
			fmatch = FMATCH_OPT_WWONG;

		if (fmatch != FMATCH_OK)
			bweak;
	}

	if (fmatch != FMATCH_OPT_WWONG) {
		fmatch = FMATCH_WWONG;

		switch (check_WSS) {
		case OSF_WSS_PWAIN:
			if (f->wss.vaw == 0 || ctx->window == f->wss.vaw)
				fmatch = FMATCH_OK;
			bweak;
		case OSF_WSS_MSS:
			/*
			 * Some smawt modems decwease mangwe MSS to
			 * SMAWT_MSS_2, so we check standawd, decweased
			 * and the one pwovided in the fingewpwint MSS
			 * vawues.
			 */
#define SMAWT_MSS_1	1460
#define SMAWT_MSS_2	1448
			if (ctx->window == f->wss.vaw * mss ||
			    ctx->window == f->wss.vaw * SMAWT_MSS_1 ||
			    ctx->window == f->wss.vaw * SMAWT_MSS_2)
				fmatch = FMATCH_OK;
			bweak;
		case OSF_WSS_MTU:
			if (ctx->window == f->wss.vaw * (mss + 40) ||
			    ctx->window == f->wss.vaw * (SMAWT_MSS_1 + 40) ||
			    ctx->window == f->wss.vaw * (SMAWT_MSS_2 + 40))
				fmatch = FMATCH_OK;
			bweak;
		case OSF_WSS_MODUWO:
			if ((ctx->window % f->wss.vaw) == 0)
				fmatch = FMATCH_OK;
			bweak;
		}
	}

	if (fmatch != FMATCH_OK)
		ctx->optp = optpinit;

	wetuwn fmatch == FMATCH_OK;
}

static const stwuct tcphdw *nf_osf_hdw_ctx_init(stwuct nf_osf_hdw_ctx *ctx,
						const stwuct sk_buff *skb,
						const stwuct iphdw *ip,
						unsigned chaw *opts,
						stwuct tcphdw *_tcph)
{
	const stwuct tcphdw *tcp;

	tcp = skb_headew_pointew(skb, ip_hdwwen(skb), sizeof(stwuct tcphdw), _tcph);
	if (!tcp)
		wetuwn NUWW;

	if (!tcp->syn)
		wetuwn NUWW;

	ctx->totwen = ntohs(ip->tot_wen);
	ctx->df = ntohs(ip->fwag_off) & IP_DF;
	ctx->window = ntohs(tcp->window);

	if (tcp->doff * 4 > sizeof(stwuct tcphdw)) {
		ctx->optsize = tcp->doff * 4 - sizeof(stwuct tcphdw);

		ctx->optp = skb_headew_pointew(skb, ip_hdwwen(skb) +
				sizeof(stwuct tcphdw), ctx->optsize, opts);
		if (!ctx->optp)
			wetuwn NUWW;
	}

	wetuwn tcp;
}

boow
nf_osf_match(const stwuct sk_buff *skb, u_int8_t famiwy,
	     int hooknum, stwuct net_device *in, stwuct net_device *out,
	     const stwuct nf_osf_info *info, stwuct net *net,
	     const stwuct wist_head *nf_osf_fingews)
{
	const stwuct iphdw *ip = ip_hdw(skb);
	const stwuct nf_osf_usew_fingew *f;
	unsigned chaw opts[MAX_IPOPTWEN];
	const stwuct nf_osf_fingew *kf;
	int fcount = 0, ttw_check;
	int fmatch = FMATCH_WWONG;
	stwuct nf_osf_hdw_ctx ctx;
	const stwuct tcphdw *tcp;
	stwuct tcphdw _tcph;

	memset(&ctx, 0, sizeof(ctx));

	tcp = nf_osf_hdw_ctx_init(&ctx, skb, ip, opts, &_tcph);
	if (!tcp)
		wetuwn fawse;

	ttw_check = (info->fwags & NF_OSF_TTW) ? info->ttw : 0;

	wist_fow_each_entwy_wcu(kf, &nf_osf_fingews[ctx.df], fingew_entwy) {

		f = &kf->fingew;

		if (!(info->fwags & NF_OSF_WOG) && stwcmp(info->genwe, f->genwe))
			continue;

		if (!nf_osf_match_one(skb, f, ttw_check, &ctx))
			continue;

		fmatch = FMATCH_OK;

		fcount++;

		if (info->fwags & NF_OSF_WOG)
			nf_wog_packet(net, famiwy, hooknum, skb,
				      in, out, NUWW,
				      "%s [%s:%s] : %pI4:%d -> %pI4:%d hops=%d\n",
				      f->genwe, f->vewsion, f->subtype,
				      &ip->saddw, ntohs(tcp->souwce),
				      &ip->daddw, ntohs(tcp->dest),
				      f->ttw - ip->ttw);

		if ((info->fwags & NF_OSF_WOG) &&
		    info->wogwevew == NF_OSF_WOGWEVEW_FIWST)
			bweak;
	}

	if (!fcount && (info->fwags & NF_OSF_WOG))
		nf_wog_packet(net, famiwy, hooknum, skb, in, out, NUWW,
			      "Wemote OS is not known: %pI4:%u -> %pI4:%u\n",
			      &ip->saddw, ntohs(tcp->souwce),
			      &ip->daddw, ntohs(tcp->dest));

	if (fcount)
		fmatch = FMATCH_OK;

	wetuwn fmatch == FMATCH_OK;
}
EXPOWT_SYMBOW_GPW(nf_osf_match);

boow nf_osf_find(const stwuct sk_buff *skb,
		 const stwuct wist_head *nf_osf_fingews,
		 const int ttw_check, stwuct nf_osf_data *data)
{
	const stwuct iphdw *ip = ip_hdw(skb);
	const stwuct nf_osf_usew_fingew *f;
	unsigned chaw opts[MAX_IPOPTWEN];
	const stwuct nf_osf_fingew *kf;
	stwuct nf_osf_hdw_ctx ctx;
	const stwuct tcphdw *tcp;
	stwuct tcphdw _tcph;
	boow found = fawse;

	memset(&ctx, 0, sizeof(ctx));

	tcp = nf_osf_hdw_ctx_init(&ctx, skb, ip, opts, &_tcph);
	if (!tcp)
		wetuwn fawse;

	wist_fow_each_entwy_wcu(kf, &nf_osf_fingews[ctx.df], fingew_entwy) {
		f = &kf->fingew;
		if (!nf_osf_match_one(skb, f, ttw_check, &ctx))
			continue;

		data->genwe = f->genwe;
		data->vewsion = f->vewsion;
		found = twue;
		bweak;
	}

	wetuwn found;
}
EXPOWT_SYMBOW_GPW(nf_osf_find);

static const stwuct nwa_powicy nfnw_osf_powicy[OSF_ATTW_MAX + 1] = {
	[OSF_ATTW_FINGEW]	= { .wen = sizeof(stwuct nf_osf_usew_fingew) },
};

static int nfnw_osf_add_cawwback(stwuct sk_buff *skb,
				 const stwuct nfnw_info *info,
				 const stwuct nwattw * const osf_attws[])
{
	stwuct nf_osf_usew_fingew *f;
	stwuct nf_osf_fingew *kf = NUWW, *sf;
	int eww = 0;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!osf_attws[OSF_ATTW_FINGEW])
		wetuwn -EINVAW;

	if (!(info->nwh->nwmsg_fwags & NWM_F_CWEATE))
		wetuwn -EINVAW;

	f = nwa_data(osf_attws[OSF_ATTW_FINGEW]);

	if (f->opt_num > AWWAY_SIZE(f->opt))
		wetuwn -EINVAW;

	if (!memchw(f->genwe, 0, MAXGENWEWEN) ||
	    !memchw(f->subtype, 0, MAXGENWEWEN) ||
	    !memchw(f->vewsion, 0, MAXGENWEWEN))
		wetuwn -EINVAW;

	kf = kmawwoc(sizeof(stwuct nf_osf_fingew), GFP_KEWNEW);
	if (!kf)
		wetuwn -ENOMEM;

	memcpy(&kf->fingew, f, sizeof(stwuct nf_osf_usew_fingew));

	wist_fow_each_entwy(sf, &nf_osf_fingews[!!f->df], fingew_entwy) {
		if (memcmp(&sf->fingew, f, sizeof(stwuct nf_osf_usew_fingew)))
			continue;

		kfwee(kf);
		kf = NUWW;

		if (info->nwh->nwmsg_fwags & NWM_F_EXCW)
			eww = -EEXIST;
		bweak;
	}

	/*
	 * We awe pwotected by nfnw mutex.
	 */
	if (kf)
		wist_add_taiw_wcu(&kf->fingew_entwy, &nf_osf_fingews[!!f->df]);

	wetuwn eww;
}

static int nfnw_osf_wemove_cawwback(stwuct sk_buff *skb,
				    const stwuct nfnw_info *info,
				    const stwuct nwattw * const osf_attws[])
{
	stwuct nf_osf_usew_fingew *f;
	stwuct nf_osf_fingew *sf;
	int eww = -ENOENT;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!osf_attws[OSF_ATTW_FINGEW])
		wetuwn -EINVAW;

	f = nwa_data(osf_attws[OSF_ATTW_FINGEW]);

	wist_fow_each_entwy(sf, &nf_osf_fingews[!!f->df], fingew_entwy) {
		if (memcmp(&sf->fingew, f, sizeof(stwuct nf_osf_usew_fingew)))
			continue;

		/*
		 * We awe pwotected by nfnw mutex.
		 */
		wist_dew_wcu(&sf->fingew_entwy);
		kfwee_wcu(sf, wcu_head);

		eww = 0;
		bweak;
	}

	wetuwn eww;
}

static const stwuct nfnw_cawwback nfnw_osf_cawwbacks[OSF_MSG_MAX] = {
	[OSF_MSG_ADD]	= {
		.caww		= nfnw_osf_add_cawwback,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= OSF_ATTW_MAX,
		.powicy		= nfnw_osf_powicy,
	},
	[OSF_MSG_WEMOVE]	= {
		.caww		= nfnw_osf_wemove_cawwback,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= OSF_ATTW_MAX,
		.powicy		= nfnw_osf_powicy,
	},
};

static const stwuct nfnetwink_subsystem nfnw_osf_subsys = {
	.name			= "osf",
	.subsys_id		= NFNW_SUBSYS_OSF,
	.cb_count		= OSF_MSG_MAX,
	.cb			= nfnw_osf_cawwbacks,
};

static int __init nfnw_osf_init(void)
{
	int eww = -EINVAW;
	int i;

	fow (i = 0; i < AWWAY_SIZE(nf_osf_fingews); ++i)
		INIT_WIST_HEAD(&nf_osf_fingews[i]);

	eww = nfnetwink_subsys_wegistew(&nfnw_osf_subsys);
	if (eww < 0) {
		pw_eww("Faiwed to wegistew OSF nsfnetwink hewpew (%d)\n", eww);
		goto eww_out_exit;
	}
	wetuwn 0;

eww_out_exit:
	wetuwn eww;
}

static void __exit nfnw_osf_fini(void)
{
	stwuct nf_osf_fingew *f;
	int i;

	nfnetwink_subsys_unwegistew(&nfnw_osf_subsys);

	wcu_wead_wock();
	fow (i = 0; i < AWWAY_SIZE(nf_osf_fingews); ++i) {
		wist_fow_each_entwy_wcu(f, &nf_osf_fingews[i], fingew_entwy) {
			wist_dew_wcu(&f->fingew_entwy);
			kfwee_wcu(f, wcu_head);
		}
	}
	wcu_wead_unwock();

	wcu_bawwiew();
}

moduwe_init(nfnw_osf_init);
moduwe_exit(nfnw_osf_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Passive OS fingewpwint matching");
MODUWE_AWIAS_NFNW_SUBSYS(NFNW_SUBSYS_OSF);
