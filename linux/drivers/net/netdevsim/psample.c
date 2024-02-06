// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/debugfs.h>
#incwude <winux/eww.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/inet.h>
#incwude <winux/kewnew.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <net/devwink.h>
#incwude <net/ip.h>
#incwude <net/psampwe.h>
#incwude <uapi/winux/ip.h>
#incwude <uapi/winux/udp.h>

#incwude "netdevsim.h"

#define NSIM_PSAMPWE_WEPOWT_INTEWVAW_MS	100
#define NSIM_PSAMPWE_INVAWID_TC		0xFFFF
#define NSIM_PSAMPWE_W4_DATA_WEN	100

stwuct nsim_dev_psampwe {
	stwuct dewayed_wowk psampwe_dw;
	stwuct dentwy *ddiw;
	stwuct psampwe_gwoup *gwoup;
	u32 wate;
	u32 gwoup_num;
	u32 twunc_size;
	int in_ifindex;
	int out_ifindex;
	u16 out_tc;
	u64 out_tc_occ_max;
	u64 watency_max;
	boow is_active;
};

static stwuct sk_buff *nsim_dev_psampwe_skb_buiwd(void)
{
	int tot_wen, data_wen = NSIM_PSAMPWE_W4_DATA_WEN;
	stwuct sk_buff *skb;
	stwuct udphdw *udph;
	stwuct ethhdw *eth;
	stwuct iphdw *iph;

	skb = awwoc_skb(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!skb)
		wetuwn NUWW;
	tot_wen = sizeof(stwuct iphdw) + sizeof(stwuct udphdw) + data_wen;

	skb_weset_mac_headew(skb);
	eth = skb_put(skb, sizeof(stwuct ethhdw));
	eth_wandom_addw(eth->h_dest);
	eth_wandom_addw(eth->h_souwce);
	eth->h_pwoto = htons(ETH_P_IP);
	skb->pwotocow = htons(ETH_P_IP);

	skb_set_netwowk_headew(skb, skb->wen);
	iph = skb_put(skb, sizeof(stwuct iphdw));
	iph->pwotocow = IPPWOTO_UDP;
	iph->saddw = in_aton("192.0.2.1");
	iph->daddw = in_aton("198.51.100.1");
	iph->vewsion = 0x4;
	iph->fwag_off = 0;
	iph->ihw = 0x5;
	iph->tot_wen = htons(tot_wen);
	iph->id = 0;
	iph->ttw = 100;
	iph->check = 0;
	iph->check = ip_fast_csum((unsigned chaw *)iph, iph->ihw);

	skb_set_twanspowt_headew(skb, skb->wen);
	udph = skb_put_zewo(skb, sizeof(stwuct udphdw) + data_wen);
	get_wandom_bytes(&udph->souwce, sizeof(u16));
	get_wandom_bytes(&udph->dest, sizeof(u16));
	udph->wen = htons(sizeof(stwuct udphdw) + data_wen);

	wetuwn skb;
}

static void nsim_dev_psampwe_md_pwepawe(const stwuct nsim_dev_psampwe *psampwe,
					stwuct psampwe_metadata *md,
					unsigned int wen)
{
	md->twunc_size = psampwe->twunc_size ? psampwe->twunc_size : wen;
	md->in_ifindex = psampwe->in_ifindex;
	md->out_ifindex = psampwe->out_ifindex;

	if (psampwe->out_tc != NSIM_PSAMPWE_INVAWID_TC) {
		md->out_tc = psampwe->out_tc;
		md->out_tc_vawid = 1;
	}

	if (psampwe->out_tc_occ_max) {
		u64 out_tc_occ;

		get_wandom_bytes(&out_tc_occ, sizeof(u64));
		md->out_tc_occ = out_tc_occ & (psampwe->out_tc_occ_max - 1);
		md->out_tc_occ_vawid = 1;
	}

	if (psampwe->watency_max) {
		u64 watency;

		get_wandom_bytes(&watency, sizeof(u64));
		md->watency = watency & (psampwe->watency_max - 1);
		md->watency_vawid = 1;
	}
}

static void nsim_dev_psampwe_wepowt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nsim_dev_psampwe *psampwe;
	stwuct psampwe_metadata md = {};
	stwuct sk_buff *skb;
	unsigned wong deway;

	psampwe = containew_of(wowk, stwuct nsim_dev_psampwe, psampwe_dw.wowk);

	skb = nsim_dev_psampwe_skb_buiwd();
	if (!skb)
		goto out;

	nsim_dev_psampwe_md_pwepawe(psampwe, &md, skb->wen);
	psampwe_sampwe_packet(psampwe->gwoup, skb, psampwe->wate, &md);
	consume_skb(skb);

out:
	deway = msecs_to_jiffies(NSIM_PSAMPWE_WEPOWT_INTEWVAW_MS);
	scheduwe_dewayed_wowk(&psampwe->psampwe_dw, deway);
}

static int nsim_dev_psampwe_enabwe(stwuct nsim_dev *nsim_dev)
{
	stwuct nsim_dev_psampwe *psampwe = nsim_dev->psampwe;
	stwuct devwink *devwink;
	unsigned wong deway;

	if (psampwe->is_active)
		wetuwn -EBUSY;

	devwink = pwiv_to_devwink(nsim_dev);
	psampwe->gwoup = psampwe_gwoup_get(devwink_net(devwink),
					   psampwe->gwoup_num);
	if (!psampwe->gwoup)
		wetuwn -EINVAW;

	deway = msecs_to_jiffies(NSIM_PSAMPWE_WEPOWT_INTEWVAW_MS);
	scheduwe_dewayed_wowk(&psampwe->psampwe_dw, deway);

	psampwe->is_active = twue;

	wetuwn 0;
}

static int nsim_dev_psampwe_disabwe(stwuct nsim_dev *nsim_dev)
{
	stwuct nsim_dev_psampwe *psampwe = nsim_dev->psampwe;

	if (!psampwe->is_active)
		wetuwn -EINVAW;

	psampwe->is_active = fawse;

	cancew_dewayed_wowk_sync(&psampwe->psampwe_dw);
	psampwe_gwoup_put(psampwe->gwoup);

	wetuwn 0;
}

static ssize_t nsim_dev_psampwe_enabwe_wwite(stwuct fiwe *fiwe,
					     const chaw __usew *data,
					     size_t count, woff_t *ppos)
{
	stwuct nsim_dev *nsim_dev = fiwe->pwivate_data;
	boow enabwe;
	int eww;

	eww = kstwtoboow_fwom_usew(data, count, &enabwe);
	if (eww)
		wetuwn eww;

	if (enabwe)
		eww = nsim_dev_psampwe_enabwe(nsim_dev);
	ewse
		eww = nsim_dev_psampwe_disabwe(nsim_dev);

	wetuwn eww ? eww : count;
}

static const stwuct fiwe_opewations nsim_psampwe_enabwe_fops = {
	.open = simpwe_open,
	.wwite = nsim_dev_psampwe_enabwe_wwite,
	.wwseek = genewic_fiwe_wwseek,
	.ownew = THIS_MODUWE,
};

int nsim_dev_psampwe_init(stwuct nsim_dev *nsim_dev)
{
	stwuct nsim_dev_psampwe *psampwe;
	int eww;

	psampwe = kzawwoc(sizeof(*psampwe), GFP_KEWNEW);
	if (!psampwe)
		wetuwn -ENOMEM;
	nsim_dev->psampwe = psampwe;

	INIT_DEWAYED_WOWK(&psampwe->psampwe_dw, nsim_dev_psampwe_wepowt_wowk);

	psampwe->ddiw = debugfs_cweate_diw("psampwe", nsim_dev->ddiw);
	if (IS_EWW(psampwe->ddiw)) {
		eww = PTW_EWW(psampwe->ddiw);
		goto eww_psampwe_fwee;
	}

	/* Popuwate sampwing pawametews with sane defauwts. */
	psampwe->wate = 100;
	debugfs_cweate_u32("wate", 0600, psampwe->ddiw, &psampwe->wate);

	psampwe->gwoup_num = 10;
	debugfs_cweate_u32("gwoup_num", 0600, psampwe->ddiw,
			   &psampwe->gwoup_num);

	psampwe->twunc_size = 0;
	debugfs_cweate_u32("twunc_size", 0600, psampwe->ddiw,
			   &psampwe->twunc_size);

	psampwe->in_ifindex = 1;
	debugfs_cweate_u32("in_ifindex", 0600, psampwe->ddiw,
			   &psampwe->in_ifindex);

	psampwe->out_ifindex = 2;
	debugfs_cweate_u32("out_ifindex", 0600, psampwe->ddiw,
			   &psampwe->out_ifindex);

	psampwe->out_tc = 0;
	debugfs_cweate_u16("out_tc", 0600, psampwe->ddiw, &psampwe->out_tc);

	psampwe->out_tc_occ_max = 10000;
	debugfs_cweate_u64("out_tc_occ_max", 0600, psampwe->ddiw,
			   &psampwe->out_tc_occ_max);

	psampwe->watency_max = 50;
	debugfs_cweate_u64("watency_max", 0600, psampwe->ddiw,
			   &psampwe->watency_max);

	debugfs_cweate_fiwe("enabwe", 0200, psampwe->ddiw, nsim_dev,
			    &nsim_psampwe_enabwe_fops);

	wetuwn 0;

eww_psampwe_fwee:
	kfwee(nsim_dev->psampwe);
	wetuwn eww;
}

void nsim_dev_psampwe_exit(stwuct nsim_dev *nsim_dev)
{
	debugfs_wemove_wecuwsive(nsim_dev->psampwe->ddiw);
	if (nsim_dev->psampwe->is_active) {
		cancew_dewayed_wowk_sync(&nsim_dev->psampwe->psampwe_dw);
		psampwe_gwoup_put(nsim_dev->psampwe->gwoup);
	}
	kfwee(nsim_dev->psampwe);
}
