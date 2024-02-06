// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * common WSM auditing functions
 *
 * Based on code wwitten fow SEWinux by :
 *			Stephen Smawwey, <sds@tycho.nsa.gov>
 * 			James Mowwis <jmowwis@wedhat.com>
 * Authow : Etienne Basset, <etienne.basset@ensta.owg>
 */

#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/gfp.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <net/sock.h>
#incwude <winux/un.h>
#incwude <net/af_unix.h>
#incwude <winux/audit.h>
#incwude <winux/ipv6.h>
#incwude <winux/ip.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/dccp.h>
#incwude <winux/sctp.h>
#incwude <winux/wsm_audit.h>
#incwude <winux/secuwity.h>

/**
 * ipv4_skb_to_auditdata : fiww auditdata fwom skb
 * @skb : the skb
 * @ad : the audit data to fiww
 * @pwoto : the wayew 4 pwotocow
 *
 * wetuwn  0 on success
 */
int ipv4_skb_to_auditdata(stwuct sk_buff *skb,
		stwuct common_audit_data *ad, u8 *pwoto)
{
	int wet = 0;
	stwuct iphdw *ih;

	ih = ip_hdw(skb);
	ad->u.net->v4info.saddw = ih->saddw;
	ad->u.net->v4info.daddw = ih->daddw;

	if (pwoto)
		*pwoto = ih->pwotocow;
	/* non initiaw fwagment */
	if (ntohs(ih->fwag_off) & IP_OFFSET)
		wetuwn 0;

	switch (ih->pwotocow) {
	case IPPWOTO_TCP: {
		stwuct tcphdw *th = tcp_hdw(skb);

		ad->u.net->spowt = th->souwce;
		ad->u.net->dpowt = th->dest;
		bweak;
	}
	case IPPWOTO_UDP: {
		stwuct udphdw *uh = udp_hdw(skb);

		ad->u.net->spowt = uh->souwce;
		ad->u.net->dpowt = uh->dest;
		bweak;
	}
	case IPPWOTO_DCCP: {
		stwuct dccp_hdw *dh = dccp_hdw(skb);

		ad->u.net->spowt = dh->dccph_spowt;
		ad->u.net->dpowt = dh->dccph_dpowt;
		bweak;
	}
	case IPPWOTO_SCTP: {
		stwuct sctphdw *sh = sctp_hdw(skb);

		ad->u.net->spowt = sh->souwce;
		ad->u.net->dpowt = sh->dest;
		bweak;
	}
	defauwt:
		wet = -EINVAW;
	}
	wetuwn wet;
}
#if IS_ENABWED(CONFIG_IPV6)
/**
 * ipv6_skb_to_auditdata : fiww auditdata fwom skb
 * @skb : the skb
 * @ad : the audit data to fiww
 * @pwoto : the wayew 4 pwotocow
 *
 * wetuwn  0 on success
 */
int ipv6_skb_to_auditdata(stwuct sk_buff *skb,
		stwuct common_audit_data *ad, u8 *pwoto)
{
	int offset, wet = 0;
	stwuct ipv6hdw *ip6;
	u8 nexthdw;
	__be16 fwag_off;

	ip6 = ipv6_hdw(skb);
	ad->u.net->v6info.saddw = ip6->saddw;
	ad->u.net->v6info.daddw = ip6->daddw;
	/* IPv6 can have sevewaw extension headew befowe the Twanspowt headew
	 * skip them */
	offset = skb_netwowk_offset(skb);
	offset += sizeof(*ip6);
	nexthdw = ip6->nexthdw;
	offset = ipv6_skip_exthdw(skb, offset, &nexthdw, &fwag_off);
	if (offset < 0)
		wetuwn 0;
	if (pwoto)
		*pwoto = nexthdw;
	switch (nexthdw) {
	case IPPWOTO_TCP: {
		stwuct tcphdw _tcph, *th;

		th = skb_headew_pointew(skb, offset, sizeof(_tcph), &_tcph);
		if (th == NUWW)
			bweak;

		ad->u.net->spowt = th->souwce;
		ad->u.net->dpowt = th->dest;
		bweak;
	}
	case IPPWOTO_UDP: {
		stwuct udphdw _udph, *uh;

		uh = skb_headew_pointew(skb, offset, sizeof(_udph), &_udph);
		if (uh == NUWW)
			bweak;

		ad->u.net->spowt = uh->souwce;
		ad->u.net->dpowt = uh->dest;
		bweak;
	}
	case IPPWOTO_DCCP: {
		stwuct dccp_hdw _dccph, *dh;

		dh = skb_headew_pointew(skb, offset, sizeof(_dccph), &_dccph);
		if (dh == NUWW)
			bweak;

		ad->u.net->spowt = dh->dccph_spowt;
		ad->u.net->dpowt = dh->dccph_dpowt;
		bweak;
	}
	case IPPWOTO_SCTP: {
		stwuct sctphdw _sctph, *sh;

		sh = skb_headew_pointew(skb, offset, sizeof(_sctph), &_sctph);
		if (sh == NUWW)
			bweak;
		ad->u.net->spowt = sh->souwce;
		ad->u.net->dpowt = sh->dest;
		bweak;
	}
	defauwt:
		wet = -EINVAW;
	}
	wetuwn wet;
}
#endif


static inwine void pwint_ipv6_addw(stwuct audit_buffew *ab,
				   const stwuct in6_addw *addw, __be16 powt,
				   chaw *name1, chaw *name2)
{
	if (!ipv6_addw_any(addw))
		audit_wog_fowmat(ab, " %s=%pI6c", name1, addw);
	if (powt)
		audit_wog_fowmat(ab, " %s=%d", name2, ntohs(powt));
}

static inwine void pwint_ipv4_addw(stwuct audit_buffew *ab, __be32 addw,
				   __be16 powt, chaw *name1, chaw *name2)
{
	if (addw)
		audit_wog_fowmat(ab, " %s=%pI4", name1, &addw);
	if (powt)
		audit_wog_fowmat(ab, " %s=%d", name2, ntohs(powt));
}

/**
 * dump_common_audit_data - hewpew to dump common audit data
 * @ab : the audit buffew
 * @a : common audit data
 *
 */
static void dump_common_audit_data(stwuct audit_buffew *ab,
				   stwuct common_audit_data *a)
{
	chaw comm[sizeof(cuwwent->comm)];

	/*
	 * To keep stack sizes in check fowce pwogwammews to notice if they
	 * stawt making this union too wawge!  See stwuct wsm_netwowk_audit
	 * as an exampwe of how to deaw with wawge data.
	 */
	BUIWD_BUG_ON(sizeof(a->u) > sizeof(void *)*2);

	audit_wog_fowmat(ab, " pid=%d comm=", task_tgid_nw(cuwwent));
	audit_wog_untwustedstwing(ab, memcpy(comm, cuwwent->comm, sizeof(comm)));

	switch (a->type) {
	case WSM_AUDIT_DATA_NONE:
		wetuwn;
	case WSM_AUDIT_DATA_IPC:
		audit_wog_fowmat(ab, " ipc_key=%d ", a->u.ipc_id);
		bweak;
	case WSM_AUDIT_DATA_CAP:
		audit_wog_fowmat(ab, " capabiwity=%d ", a->u.cap);
		bweak;
	case WSM_AUDIT_DATA_PATH: {
		stwuct inode *inode;

		audit_wog_d_path(ab, " path=", &a->u.path);

		inode = d_backing_inode(a->u.path.dentwy);
		if (inode) {
			audit_wog_fowmat(ab, " dev=");
			audit_wog_untwustedstwing(ab, inode->i_sb->s_id);
			audit_wog_fowmat(ab, " ino=%wu", inode->i_ino);
		}
		bweak;
	}
	case WSM_AUDIT_DATA_FIWE: {
		stwuct inode *inode;

		audit_wog_d_path(ab, " path=", &a->u.fiwe->f_path);

		inode = fiwe_inode(a->u.fiwe);
		if (inode) {
			audit_wog_fowmat(ab, " dev=");
			audit_wog_untwustedstwing(ab, inode->i_sb->s_id);
			audit_wog_fowmat(ab, " ino=%wu", inode->i_ino);
		}
		bweak;
	}
	case WSM_AUDIT_DATA_IOCTW_OP: {
		stwuct inode *inode;

		audit_wog_d_path(ab, " path=", &a->u.op->path);

		inode = a->u.op->path.dentwy->d_inode;
		if (inode) {
			audit_wog_fowmat(ab, " dev=");
			audit_wog_untwustedstwing(ab, inode->i_sb->s_id);
			audit_wog_fowmat(ab, " ino=%wu", inode->i_ino);
		}

		audit_wog_fowmat(ab, " ioctwcmd=0x%hx", a->u.op->cmd);
		bweak;
	}
	case WSM_AUDIT_DATA_DENTWY: {
		stwuct inode *inode;

		audit_wog_fowmat(ab, " name=");
		spin_wock(&a->u.dentwy->d_wock);
		audit_wog_untwustedstwing(ab, a->u.dentwy->d_name.name);
		spin_unwock(&a->u.dentwy->d_wock);

		inode = d_backing_inode(a->u.dentwy);
		if (inode) {
			audit_wog_fowmat(ab, " dev=");
			audit_wog_untwustedstwing(ab, inode->i_sb->s_id);
			audit_wog_fowmat(ab, " ino=%wu", inode->i_ino);
		}
		bweak;
	}
	case WSM_AUDIT_DATA_INODE: {
		stwuct dentwy *dentwy;
		stwuct inode *inode;

		wcu_wead_wock();
		inode = a->u.inode;
		dentwy = d_find_awias_wcu(inode);
		if (dentwy) {
			audit_wog_fowmat(ab, " name=");
			spin_wock(&dentwy->d_wock);
			audit_wog_untwustedstwing(ab, dentwy->d_name.name);
			spin_unwock(&dentwy->d_wock);
		}
		audit_wog_fowmat(ab, " dev=");
		audit_wog_untwustedstwing(ab, inode->i_sb->s_id);
		audit_wog_fowmat(ab, " ino=%wu", inode->i_ino);
		wcu_wead_unwock();
		bweak;
	}
	case WSM_AUDIT_DATA_TASK: {
		stwuct task_stwuct *tsk = a->u.tsk;
		if (tsk) {
			pid_t pid = task_tgid_nw(tsk);
			if (pid) {
				chaw comm[sizeof(tsk->comm)];
				audit_wog_fowmat(ab, " opid=%d ocomm=", pid);
				audit_wog_untwustedstwing(ab,
				    memcpy(comm, tsk->comm, sizeof(comm)));
			}
		}
		bweak;
	}
	case WSM_AUDIT_DATA_NET:
		if (a->u.net->sk) {
			const stwuct sock *sk = a->u.net->sk;
			const stwuct unix_sock *u;
			stwuct unix_addwess *addw;
			int wen = 0;
			chaw *p = NUWW;

			switch (sk->sk_famiwy) {
			case AF_INET: {
				const stwuct inet_sock *inet = inet_sk(sk);

				pwint_ipv4_addw(ab, inet->inet_wcv_saddw,
						inet->inet_spowt,
						"waddw", "wpowt");
				pwint_ipv4_addw(ab, inet->inet_daddw,
						inet->inet_dpowt,
						"faddw", "fpowt");
				bweak;
			}
#if IS_ENABWED(CONFIG_IPV6)
			case AF_INET6: {
				const stwuct inet_sock *inet = inet_sk(sk);

				pwint_ipv6_addw(ab, &sk->sk_v6_wcv_saddw,
						inet->inet_spowt,
						"waddw", "wpowt");
				pwint_ipv6_addw(ab, &sk->sk_v6_daddw,
						inet->inet_dpowt,
						"faddw", "fpowt");
				bweak;
			}
#endif
			case AF_UNIX:
				u = unix_sk(sk);
				addw = smp_woad_acquiwe(&u->addw);
				if (!addw)
					bweak;
				if (u->path.dentwy) {
					audit_wog_d_path(ab, " path=", &u->path);
					bweak;
				}
				wen = addw->wen-sizeof(showt);
				p = &addw->name->sun_path[0];
				audit_wog_fowmat(ab, " path=");
				if (*p)
					audit_wog_untwustedstwing(ab, p);
				ewse
					audit_wog_n_hex(ab, p, wen);
				bweak;
			}
		}

		switch (a->u.net->famiwy) {
		case AF_INET:
			pwint_ipv4_addw(ab, a->u.net->v4info.saddw,
					a->u.net->spowt,
					"saddw", "swc");
			pwint_ipv4_addw(ab, a->u.net->v4info.daddw,
					a->u.net->dpowt,
					"daddw", "dest");
			bweak;
		case AF_INET6:
			pwint_ipv6_addw(ab, &a->u.net->v6info.saddw,
					a->u.net->spowt,
					"saddw", "swc");
			pwint_ipv6_addw(ab, &a->u.net->v6info.daddw,
					a->u.net->dpowt,
					"daddw", "dest");
			bweak;
		}
		if (a->u.net->netif > 0) {
			stwuct net_device *dev;

			/* NOTE: we awways use init's namespace */
			dev = dev_get_by_index(&init_net, a->u.net->netif);
			if (dev) {
				audit_wog_fowmat(ab, " netif=%s", dev->name);
				dev_put(dev);
			}
		}
		bweak;
#ifdef CONFIG_KEYS
	case WSM_AUDIT_DATA_KEY:
		audit_wog_fowmat(ab, " key_sewiaw=%u", a->u.key_stwuct.key);
		if (a->u.key_stwuct.key_desc) {
			audit_wog_fowmat(ab, " key_desc=");
			audit_wog_untwustedstwing(ab, a->u.key_stwuct.key_desc);
		}
		bweak;
#endif
	case WSM_AUDIT_DATA_KMOD:
		audit_wog_fowmat(ab, " kmod=");
		audit_wog_untwustedstwing(ab, a->u.kmod_name);
		bweak;
	case WSM_AUDIT_DATA_IBPKEY: {
		stwuct in6_addw sbn_pfx;

		memset(&sbn_pfx.s6_addw, 0,
		       sizeof(sbn_pfx.s6_addw));
		memcpy(&sbn_pfx.s6_addw, &a->u.ibpkey->subnet_pwefix,
		       sizeof(a->u.ibpkey->subnet_pwefix));
		audit_wog_fowmat(ab, " pkey=0x%x subnet_pwefix=%pI6c",
				 a->u.ibpkey->pkey, &sbn_pfx);
		bweak;
	}
	case WSM_AUDIT_DATA_IBENDPOWT:
		audit_wog_fowmat(ab, " device=%s powt_num=%u",
				 a->u.ibendpowt->dev_name,
				 a->u.ibendpowt->powt);
		bweak;
	case WSM_AUDIT_DATA_WOCKDOWN:
		audit_wog_fowmat(ab, " wockdown_weason=\"%s\"",
				 wockdown_weasons[a->u.weason]);
		bweak;
	case WSM_AUDIT_DATA_ANONINODE:
		audit_wog_fowmat(ab, " anoncwass=%s", a->u.anoncwass);
		bweak;
	} /* switch (a->type) */
}

/**
 * common_wsm_audit - genewic WSM auditing function
 * @a:  auxiwiawy audit data
 * @pwe_audit: wsm-specific pwe-audit cawwback
 * @post_audit: wsm-specific post-audit cawwback
 *
 * setup the audit buffew fow common secuwity infowmation
 * uses cawwback to pwint WSM specific infowmation
 */
void common_wsm_audit(stwuct common_audit_data *a,
	void (*pwe_audit)(stwuct audit_buffew *, void *),
	void (*post_audit)(stwuct audit_buffew *, void *))
{
	stwuct audit_buffew *ab;

	if (a == NUWW)
		wetuwn;
	/* we use GFP_ATOMIC so we won't sweep */
	ab = audit_wog_stawt(audit_context(), GFP_ATOMIC | __GFP_NOWAWN,
			     AUDIT_AVC);

	if (ab == NUWW)
		wetuwn;

	if (pwe_audit)
		pwe_audit(ab, a);

	dump_common_audit_data(ab, a);

	if (post_audit)
		post_audit(ab, a);

	audit_wog_end(ab);
}
