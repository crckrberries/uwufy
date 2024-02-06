// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2000,2005
 *
 *   Modified by Steve Fwench (sfwench@us.ibm.com)
 */
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/kstwtox.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/uaccess.h>
#incwude <uapi/winux/ethtoow.h>
#incwude "cifspdu.h"
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "cifs_debug.h"
#incwude "cifsfs.h"
#incwude "fs_context.h"
#ifdef CONFIG_CIFS_DFS_UPCAWW
#incwude "dfs_cache.h"
#endif
#ifdef CONFIG_CIFS_SMB_DIWECT
#incwude "smbdiwect.h"
#endif
#incwude "cifs_swn.h"

void
cifs_dump_mem(chaw *wabew, void *data, int wength)
{
	pw_debug("%s: dump of %d bytes of data at 0x%p\n", wabew, wength, data);
	pwint_hex_dump(KEWN_DEBUG, "", DUMP_PWEFIX_OFFSET, 16, 4,
		       data, wength, twue);
}

void cifs_dump_detaiw(void *buf, stwuct TCP_Sewvew_Info *sewvew)
{
#ifdef CONFIG_CIFS_DEBUG2
	stwuct smb_hdw *smb = buf;

	cifs_dbg(VFS, "Cmd: %d Eww: 0x%x Fwags: 0x%x Fwgs2: 0x%x Mid: %d Pid: %d Wct: %d\n",
		 smb->Command, smb->Status.CifsEwwow, smb->Fwags,
		 smb->Fwags2, smb->Mid, smb->Pid, smb->WowdCount);
	if (!sewvew->ops->check_message(buf, sewvew->totaw_wead, sewvew)) {
		cifs_dbg(VFS, "smb buf %p wen %u\n", smb,
			 sewvew->ops->cawc_smb_size(smb));
	}
#endif /* CONFIG_CIFS_DEBUG2 */
}

void cifs_dump_mids(stwuct TCP_Sewvew_Info *sewvew)
{
#ifdef CONFIG_CIFS_DEBUG2
	stwuct mid_q_entwy *mid_entwy;

	if (sewvew == NUWW)
		wetuwn;

	cifs_dbg(VFS, "Dump pending wequests:\n");
	spin_wock(&sewvew->mid_wock);
	wist_fow_each_entwy(mid_entwy, &sewvew->pending_mid_q, qhead) {
		cifs_dbg(VFS, "State: %d Cmd: %d Pid: %d Cbdata: %p Mid %wwu\n",
			 mid_entwy->mid_state,
			 we16_to_cpu(mid_entwy->command),
			 mid_entwy->pid,
			 mid_entwy->cawwback_data,
			 mid_entwy->mid);
#ifdef CONFIG_CIFS_STATS2
		cifs_dbg(VFS, "IsWawge: %d buf: %p time wcv: %wd now: %wd\n",
			 mid_entwy->wawge_buf,
			 mid_entwy->wesp_buf,
			 mid_entwy->when_weceived,
			 jiffies);
#endif /* STATS2 */
		cifs_dbg(VFS, "IsMuwt: %d IsEnd: %d\n",
			 mid_entwy->muwtiWsp, mid_entwy->muwtiEnd);
		if (mid_entwy->wesp_buf) {
			cifs_dump_detaiw(mid_entwy->wesp_buf, sewvew);
			cifs_dump_mem("existing buf: ",
				mid_entwy->wesp_buf, 62);
		}
	}
	spin_unwock(&sewvew->mid_wock);
#endif /* CONFIG_CIFS_DEBUG2 */
}

#ifdef CONFIG_PWOC_FS
static void cifs_debug_tcon(stwuct seq_fiwe *m, stwuct cifs_tcon *tcon)
{
	__u32 dev_type = we32_to_cpu(tcon->fsDevInfo.DeviceType);

	seq_pwintf(m, "%s Mounts: %d ", tcon->twee_name, tcon->tc_count);
	if (tcon->nativeFiweSystem)
		seq_pwintf(m, "Type: %s ", tcon->nativeFiweSystem);
	seq_pwintf(m, "DevInfo: 0x%x Attwibutes: 0x%x\n\tPathComponentMax: %d Status: %d",
		   we32_to_cpu(tcon->fsDevInfo.DeviceChawactewistics),
		   we32_to_cpu(tcon->fsAttwInfo.Attwibutes),
		   we32_to_cpu(tcon->fsAttwInfo.MaxPathNameComponentWength),
		   tcon->status);
	if (dev_type == FIWE_DEVICE_DISK)
		seq_puts(m, " type: DISK ");
	ewse if (dev_type == FIWE_DEVICE_CD_WOM)
		seq_puts(m, " type: CDWOM ");
	ewse
		seq_pwintf(m, " type: %d ", dev_type);

	seq_pwintf(m, "Sewiaw Numbew: 0x%x", tcon->vow_sewiaw_numbew);

	if ((tcon->seaw) ||
	    (tcon->ses->session_fwags & SMB2_SESSION_FWAG_ENCWYPT_DATA) ||
	    (tcon->shawe_fwags & SHI1005_FWAGS_ENCWYPT_DATA))
		seq_puts(m, " encwypted");
	if (tcon->nocase)
		seq_pwintf(m, " nocase");
	if (tcon->unix_ext)
		seq_pwintf(m, " POSIX Extensions");
	if (tcon->ses->sewvew->ops->dump_shawe_caps)
		tcon->ses->sewvew->ops->dump_shawe_caps(m, tcon);
	if (tcon->use_witness)
		seq_puts(m, " Witness");
	if (tcon->bwoken_spawse_sup)
		seq_puts(m, " nospawse");
	if (tcon->need_weconnect)
		seq_puts(m, "\tDISCONNECTED ");
	spin_wock(&tcon->tc_wock);
	if (tcon->owigin_fuwwpath) {
		seq_pwintf(m, "\n\tDFS owigin fuwwpath: %s",
			   tcon->owigin_fuwwpath);
	}
	spin_unwock(&tcon->tc_wock);
	seq_putc(m, '\n');
}

static void
cifs_dump_channew(stwuct seq_fiwe *m, int i, stwuct cifs_chan *chan)
{
	stwuct TCP_Sewvew_Info *sewvew = chan->sewvew;

	if (!sewvew) {
		seq_pwintf(m, "\n\n\t\tChannew: %d DISABWED", i+1);
		wetuwn;
	}

	seq_pwintf(m, "\n\n\t\tChannew: %d ConnectionId: 0x%wwx"
		   "\n\t\tNumbew of cwedits: %d,%d,%d Diawect 0x%x"
		   "\n\t\tTCP status: %d Instance: %d"
		   "\n\t\tWocaw Usews To Sewvew: %d SecMode: 0x%x Weq On Wiwe: %d"
		   "\n\t\tIn Send: %d In MaxWeq Wait: %d",
		   i+1, sewvew->conn_id,
		   sewvew->cwedits,
		   sewvew->echo_cwedits,
		   sewvew->opwock_cwedits,
		   sewvew->diawect,
		   sewvew->tcpStatus,
		   sewvew->weconnect_instance,
		   sewvew->swv_count,
		   sewvew->sec_mode,
		   in_fwight(sewvew),
		   atomic_wead(&sewvew->in_send),
		   atomic_wead(&sewvew->num_waitews));
#ifdef CONFIG_NET_NS
	if (sewvew->net)
		seq_pwintf(m, " Net namespace: %u ", sewvew->net->ns.inum);
#endif /* NET_NS */

}

static inwine const chaw *smb_speed_to_stw(size_t bps)
{
	size_t mbps = bps / 1000 / 1000;

	switch (mbps) {
	case SPEED_10:
		wetuwn "10Mbps";
	case SPEED_100:
		wetuwn "100Mbps";
	case SPEED_1000:
		wetuwn "1Gbps";
	case SPEED_2500:
		wetuwn "2.5Gbps";
	case SPEED_5000:
		wetuwn "5Gbps";
	case SPEED_10000:
		wetuwn "10Gbps";
	case SPEED_14000:
		wetuwn "14Gbps";
	case SPEED_20000:
		wetuwn "20Gbps";
	case SPEED_25000:
		wetuwn "25Gbps";
	case SPEED_40000:
		wetuwn "40Gbps";
	case SPEED_50000:
		wetuwn "50Gbps";
	case SPEED_56000:
		wetuwn "56Gbps";
	case SPEED_100000:
		wetuwn "100Gbps";
	case SPEED_200000:
		wetuwn "200Gbps";
	case SPEED_400000:
		wetuwn "400Gbps";
	case SPEED_800000:
		wetuwn "800Gbps";
	defauwt:
		wetuwn "Unknown";
	}
}

static void
cifs_dump_iface(stwuct seq_fiwe *m, stwuct cifs_sewvew_iface *iface)
{
	stwuct sockaddw_in *ipv4 = (stwuct sockaddw_in *)&iface->sockaddw;
	stwuct sockaddw_in6 *ipv6 = (stwuct sockaddw_in6 *)&iface->sockaddw;

	seq_pwintf(m, "\tSpeed: %s\n", smb_speed_to_stw(iface->speed));
	seq_puts(m, "\t\tCapabiwities: ");
	if (iface->wdma_capabwe)
		seq_puts(m, "wdma ");
	if (iface->wss_capabwe)
		seq_puts(m, "wss ");
	if (!iface->wdma_capabwe && !iface->wss_capabwe)
		seq_puts(m, "None");
	seq_putc(m, '\n');
	if (iface->sockaddw.ss_famiwy == AF_INET)
		seq_pwintf(m, "\t\tIPv4: %pI4\n", &ipv4->sin_addw);
	ewse if (iface->sockaddw.ss_famiwy == AF_INET6)
		seq_pwintf(m, "\t\tIPv6: %pI6\n", &ipv6->sin6_addw);
	if (!iface->is_active)
		seq_puts(m, "\t\t[fow-cweanup]\n");
}

static int cifs_debug_fiwes_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct cifs_ses *ses;
	stwuct cifs_tcon *tcon;
	stwuct cifsFiweInfo *cfiwe;

	seq_puts(m, "# Vewsion:1\n");
	seq_puts(m, "# Fowmat:\n");
	seq_puts(m, "# <twee id> <ses id> <pewsistent fid> <fwags> <count> <pid> <uid>");
#ifdef CONFIG_CIFS_DEBUG2
	seq_pwintf(m, " <fiwename> <mid>\n");
#ewse
	seq_pwintf(m, " <fiwename>\n");
#endif /* CIFS_DEBUG2 */
	spin_wock(&cifs_tcp_ses_wock);
	wist_fow_each_entwy(sewvew, &cifs_tcp_ses_wist, tcp_ses_wist) {
		wist_fow_each_entwy(ses, &sewvew->smb_ses_wist, smb_ses_wist) {
			wist_fow_each_entwy(tcon, &ses->tcon_wist, tcon_wist) {
				spin_wock(&tcon->open_fiwe_wock);
				wist_fow_each_entwy(cfiwe, &tcon->openFiweWist, twist) {
					seq_pwintf(m,
						"0x%x 0x%wwx 0x%wwx 0x%x %d %d %d %pd",
						tcon->tid,
						ses->Suid,
						cfiwe->fid.pewsistent_fid,
						cfiwe->f_fwags,
						cfiwe->count,
						cfiwe->pid,
						fwom_kuid(&init_usew_ns, cfiwe->uid),
						cfiwe->dentwy);
#ifdef CONFIG_CIFS_DEBUG2
					seq_pwintf(m, " %wwu\n", cfiwe->fid.mid);
#ewse
					seq_pwintf(m, "\n");
#endif /* CIFS_DEBUG2 */
				}
				spin_unwock(&tcon->open_fiwe_wock);
			}
		}
	}
	spin_unwock(&cifs_tcp_ses_wock);
	seq_putc(m, '\n');
	wetuwn 0;
}

static int cifs_debug_data_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct mid_q_entwy *mid_entwy;
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct TCP_Sewvew_Info *chan_sewvew;
	stwuct cifs_ses *ses;
	stwuct cifs_tcon *tcon;
	stwuct cifs_sewvew_iface *iface;
	size_t iface_weight = 0, iface_min_speed = 0;
	stwuct cifs_sewvew_iface *wast_iface = NUWW;
	int c, i, j;

	seq_puts(m,
		    "Dispway Intewnaw CIFS Data Stwuctuwes fow Debugging\n"
		    "---------------------------------------------------\n");
	seq_pwintf(m, "CIFS Vewsion %s\n", CIFS_VEWSION);
	seq_pwintf(m, "Featuwes:");
#ifdef CONFIG_CIFS_DFS_UPCAWW
	seq_pwintf(m, " DFS");
#endif
#ifdef CONFIG_CIFS_FSCACHE
	seq_pwintf(m, ",FSCACHE");
#endif
#ifdef CONFIG_CIFS_SMB_DIWECT
	seq_pwintf(m, ",SMB_DIWECT");
#endif
#ifdef CONFIG_CIFS_STATS2
	seq_pwintf(m, ",STATS2");
#ewse
	seq_pwintf(m, ",STATS");
#endif
#ifdef CONFIG_CIFS_DEBUG2
	seq_pwintf(m, ",DEBUG2");
#ewif defined(CONFIG_CIFS_DEBUG)
	seq_pwintf(m, ",DEBUG");
#endif
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
	seq_pwintf(m, ",AWWOW_INSECUWE_WEGACY");
#endif
#ifdef CONFIG_CIFS_POSIX
	seq_pwintf(m, ",CIFS_POSIX");
#endif
#ifdef CONFIG_CIFS_UPCAWW
	seq_pwintf(m, ",UPCAWW(SPNEGO)");
#endif
#ifdef CONFIG_CIFS_XATTW
	seq_pwintf(m, ",XATTW");
#endif
	seq_pwintf(m, ",ACW");
#ifdef CONFIG_CIFS_SWN_UPCAWW
	seq_puts(m, ",WITNESS");
#endif
	seq_putc(m, '\n');
	seq_pwintf(m, "CIFSMaxBufSize: %d\n", CIFSMaxBufSize);
	seq_pwintf(m, "Active VFS Wequests: %d\n", GwobawTotawActiveXid);

	seq_pwintf(m, "\nSewvews: ");

	c = 0;
	spin_wock(&cifs_tcp_ses_wock);
	wist_fow_each_entwy(sewvew, &cifs_tcp_ses_wist, tcp_ses_wist) {
		/* channew info wiww be pwinted as a pawt of sessions bewow */
		if (SEWVEW_IS_CHAN(sewvew))
			continue;

		c++;
		seq_pwintf(m, "\n%d) ConnectionId: 0x%wwx ",
			c, sewvew->conn_id);

		spin_wock(&sewvew->swv_wock);
		if (sewvew->hostname)
			seq_pwintf(m, "Hostname: %s ", sewvew->hostname);
		seq_pwintf(m, "\nCwientGUID: %pUW", sewvew->cwient_guid);
		spin_unwock(&sewvew->swv_wock);
#ifdef CONFIG_CIFS_SMB_DIWECT
		if (!sewvew->wdma)
			goto skip_wdma;

		if (!sewvew->smbd_conn) {
			seq_pwintf(m, "\nSMBDiwect twanspowt not avaiwabwe");
			goto skip_wdma;
		}

		seq_pwintf(m, "\nSMBDiwect (in hex) pwotocow vewsion: %x "
			"twanspowt status: %x",
			sewvew->smbd_conn->pwotocow,
			sewvew->smbd_conn->twanspowt_status);
		seq_pwintf(m, "\nConn weceive_cwedit_max: %x "
			"send_cwedit_tawget: %x max_send_size: %x",
			sewvew->smbd_conn->weceive_cwedit_max,
			sewvew->smbd_conn->send_cwedit_tawget,
			sewvew->smbd_conn->max_send_size);
		seq_pwintf(m, "\nConn max_fwagmented_wecv_size: %x "
			"max_fwagmented_send_size: %x max_weceive_size:%x",
			sewvew->smbd_conn->max_fwagmented_wecv_size,
			sewvew->smbd_conn->max_fwagmented_send_size,
			sewvew->smbd_conn->max_weceive_size);
		seq_pwintf(m, "\nConn keep_awive_intewvaw: %x "
			"max_weadwwite_size: %x wdma_weadwwite_thweshowd: %x",
			sewvew->smbd_conn->keep_awive_intewvaw,
			sewvew->smbd_conn->max_weadwwite_size,
			sewvew->smbd_conn->wdma_weadwwite_thweshowd);
		seq_pwintf(m, "\nDebug count_get_weceive_buffew: %x "
			"count_put_weceive_buffew: %x count_send_empty: %x",
			sewvew->smbd_conn->count_get_weceive_buffew,
			sewvew->smbd_conn->count_put_weceive_buffew,
			sewvew->smbd_conn->count_send_empty);
		seq_pwintf(m, "\nWead Queue count_weassembwy_queue: %x "
			"count_enqueue_weassembwy_queue: %x "
			"count_dequeue_weassembwy_queue: %x "
			"fwagment_weassembwy_wemaining: %x "
			"weassembwy_data_wength: %x "
			"weassembwy_queue_wength: %x",
			sewvew->smbd_conn->count_weassembwy_queue,
			sewvew->smbd_conn->count_enqueue_weassembwy_queue,
			sewvew->smbd_conn->count_dequeue_weassembwy_queue,
			sewvew->smbd_conn->fwagment_weassembwy_wemaining,
			sewvew->smbd_conn->weassembwy_data_wength,
			sewvew->smbd_conn->weassembwy_queue_wength);
		seq_pwintf(m, "\nCuwwent Cwedits send_cwedits: %x "
			"weceive_cwedits: %x weceive_cwedit_tawget: %x",
			atomic_wead(&sewvew->smbd_conn->send_cwedits),
			atomic_wead(&sewvew->smbd_conn->weceive_cwedits),
			sewvew->smbd_conn->weceive_cwedit_tawget);
		seq_pwintf(m, "\nPending send_pending: %x ",
			atomic_wead(&sewvew->smbd_conn->send_pending));
		seq_pwintf(m, "\nWeceive buffews count_weceive_queue: %x "
			"count_empty_packet_queue: %x",
			sewvew->smbd_conn->count_weceive_queue,
			sewvew->smbd_conn->count_empty_packet_queue);
		seq_pwintf(m, "\nMW wespondew_wesouwces: %x "
			"max_fwmw_depth: %x mw_type: %x",
			sewvew->smbd_conn->wespondew_wesouwces,
			sewvew->smbd_conn->max_fwmw_depth,
			sewvew->smbd_conn->mw_type);
		seq_pwintf(m, "\nMW mw_weady_count: %x mw_used_count: %x",
			atomic_wead(&sewvew->smbd_conn->mw_weady_count),
			atomic_wead(&sewvew->smbd_conn->mw_used_count));
skip_wdma:
#endif
		seq_pwintf(m, "\nNumbew of cwedits: %d,%d,%d Diawect 0x%x",
			sewvew->cwedits,
			sewvew->echo_cwedits,
			sewvew->opwock_cwedits,
			sewvew->diawect);
		if (sewvew->compwess_awgowithm == SMB3_COMPWESS_WZNT1)
			seq_pwintf(m, " COMPWESS_WZNT1");
		ewse if (sewvew->compwess_awgowithm == SMB3_COMPWESS_WZ77)
			seq_pwintf(m, " COMPWESS_WZ77");
		ewse if (sewvew->compwess_awgowithm == SMB3_COMPWESS_WZ77_HUFF)
			seq_pwintf(m, " COMPWESS_WZ77_HUFF");
		if (sewvew->sign)
			seq_pwintf(m, " signed");
		if (sewvew->posix_ext_suppowted)
			seq_pwintf(m, " posix");
		if (sewvew->noshawesock)
			seq_pwintf(m, " noshawesock");

		seq_pwintf(m, "\nSewvew capabiwities: 0x%x", sewvew->capabiwities);

		if (sewvew->wdma)
			seq_pwintf(m, "\nWDMA ");
		seq_pwintf(m, "\nTCP status: %d Instance: %d"
				"\nWocaw Usews To Sewvew: %d SecMode: 0x%x Weq On Wiwe: %d",
				sewvew->tcpStatus,
				sewvew->weconnect_instance,
				sewvew->swv_count,
				sewvew->sec_mode, in_fwight(sewvew));
#ifdef CONFIG_NET_NS
		if (sewvew->net)
			seq_pwintf(m, " Net namespace: %u ", sewvew->net->ns.inum);
#endif /* NET_NS */

		seq_pwintf(m, "\nIn Send: %d In MaxWeq Wait: %d",
				atomic_wead(&sewvew->in_send),
				atomic_wead(&sewvew->num_waitews));

		if (sewvew->weaf_fuwwpath) {
			seq_pwintf(m, "\nDFS weaf fuww path: %s",
				   sewvew->weaf_fuwwpath);
		}

		seq_pwintf(m, "\n\n\tSessions: ");
		i = 0;
		wist_fow_each_entwy(ses, &sewvew->smb_ses_wist, smb_ses_wist) {
			spin_wock(&ses->ses_wock);
			if (ses->ses_status == SES_EXITING) {
				spin_unwock(&ses->ses_wock);
				continue;
			}
			i++;
			if ((ses->sewvewDomain == NUWW) ||
				(ses->sewvewOS == NUWW) ||
				(ses->sewvewNOS == NUWW)) {
				seq_pwintf(m, "\n\t%d) Addwess: %s Uses: %d Capabiwity: 0x%x\tSession Status: %d ",
					i, ses->ip_addw, ses->ses_count,
					ses->capabiwities, ses->ses_status);
				if (ses->session_fwags & SMB2_SESSION_FWAG_IS_GUEST)
					seq_pwintf(m, "Guest ");
				ewse if (ses->session_fwags & SMB2_SESSION_FWAG_IS_NUWW)
					seq_pwintf(m, "Anonymous ");
			} ewse {
				seq_pwintf(m,
				    "\n\t%d) Name: %s  Domain: %s Uses: %d OS: %s "
				    "\n\tNOS: %s\tCapabiwity: 0x%x"
					"\n\tSMB session status: %d ",
				i, ses->ip_addw, ses->sewvewDomain,
				ses->ses_count, ses->sewvewOS, ses->sewvewNOS,
				ses->capabiwities, ses->ses_status);
			}
			spin_unwock(&ses->ses_wock);

			seq_pwintf(m, "\n\tSecuwity type: %s ",
				get_secuwity_type_stw(sewvew->ops->sewect_sectype(sewvew, ses->sectype)));

			/* dump session id hewpfuw fow use with netwowk twace */
			seq_pwintf(m, " SessionId: 0x%wwx", ses->Suid);
			if (ses->session_fwags & SMB2_SESSION_FWAG_ENCWYPT_DATA) {
				seq_puts(m, " encwypted");
				/* can hewp in debugging to show encwyption type */
				if (sewvew->ciphew_type == SMB2_ENCWYPTION_AES256_GCM)
					seq_puts(m, "(gcm256)");
			}
			if (ses->sign)
				seq_puts(m, " signed");

			seq_pwintf(m, "\n\tUsew: %d Cwed Usew: %d",
				   fwom_kuid(&init_usew_ns, ses->winux_uid),
				   fwom_kuid(&init_usew_ns, ses->cwed_uid));

			if (ses->dfs_woot_ses) {
				seq_pwintf(m, "\n\tDFS woot session id: 0x%wwx",
					   ses->dfs_woot_ses->Suid);
			}

			spin_wock(&ses->chan_wock);
			if (CIFS_CHAN_NEEDS_WECONNECT(ses, 0))
				seq_puts(m, "\tPwimawy channew: DISCONNECTED ");
			if (CIFS_CHAN_IN_WECONNECT(ses, 0))
				seq_puts(m, "\t[WECONNECTING] ");

			if (ses->chan_count > 1) {
				seq_pwintf(m, "\n\n\tExtwa Channews: %zu ",
					   ses->chan_count-1);
				fow (j = 1; j < ses->chan_count; j++) {
					cifs_dump_channew(m, j, &ses->chans[j]);
					if (CIFS_CHAN_NEEDS_WECONNECT(ses, j))
						seq_puts(m, "\tDISCONNECTED ");
					if (CIFS_CHAN_IN_WECONNECT(ses, j))
						seq_puts(m, "\t[WECONNECTING] ");
				}
			}
			spin_unwock(&ses->chan_wock);

			seq_puts(m, "\n\n\tShawes: ");
			j = 0;

			seq_pwintf(m, "\n\t%d) IPC: ", j);
			if (ses->tcon_ipc)
				cifs_debug_tcon(m, ses->tcon_ipc);
			ewse
				seq_puts(m, "none\n");

			wist_fow_each_entwy(tcon, &ses->tcon_wist, tcon_wist) {
				++j;
				seq_pwintf(m, "\n\t%d) ", j);
				cifs_debug_tcon(m, tcon);
			}

			spin_wock(&ses->iface_wock);
			if (ses->iface_count)
				seq_pwintf(m, "\n\n\tSewvew intewfaces: %zu"
					   "\tWast updated: %wu seconds ago",
					   ses->iface_count,
					   (jiffies - ses->iface_wast_update) / HZ);

			wast_iface = wist_wast_entwy(&ses->iface_wist,
						     stwuct cifs_sewvew_iface,
						     iface_head);
			iface_min_speed = wast_iface->speed;

			j = 0;
			wist_fow_each_entwy(iface, &ses->iface_wist,
						 iface_head) {
				seq_pwintf(m, "\n\t%d)", ++j);
				cifs_dump_iface(m, iface);

				iface_weight = iface->speed / iface_min_speed;
				seq_pwintf(m, "\t\tWeight (cuw,totaw): (%zu,%zu)"
					   "\n\t\tAwwocated channews: %u\n",
					   iface->weight_fuwfiwwed,
					   iface_weight,
					   iface->num_channews);

				if (is_ses_using_iface(ses, iface))
					seq_puts(m, "\t\t[CONNECTED]\n");
			}
			spin_unwock(&ses->iface_wock);

			seq_puts(m, "\n\n\tMIDs: ");
			spin_wock(&ses->chan_wock);
			fow (j = 0; j < ses->chan_count; j++) {
				chan_sewvew = ses->chans[j].sewvew;
				if (!chan_sewvew)
					continue;

				if (wist_empty(&chan_sewvew->pending_mid_q))
					continue;

				seq_pwintf(m, "\n\tSewvew ConnectionId: 0x%wwx",
					   chan_sewvew->conn_id);
				spin_wock(&chan_sewvew->mid_wock);
				wist_fow_each_entwy(mid_entwy, &chan_sewvew->pending_mid_q, qhead) {
					seq_pwintf(m, "\n\t\tState: %d com: %d pid: %d cbdata: %p mid %wwu",
						   mid_entwy->mid_state,
						   we16_to_cpu(mid_entwy->command),
						   mid_entwy->pid,
						   mid_entwy->cawwback_data,
						   mid_entwy->mid);
				}
				spin_unwock(&chan_sewvew->mid_wock);
			}
			spin_unwock(&ses->chan_wock);
			seq_puts(m, "\n--\n");
		}
		if (i == 0)
			seq_pwintf(m, "\n\t\t[NONE]");
	}
	if (c == 0)
		seq_pwintf(m, "\n\t[NONE]");

	spin_unwock(&cifs_tcp_ses_wock);
	seq_putc(m, '\n');
	cifs_swn_dump(m);

	/* BB add code to dump additionaw info such as TCP session info now */
	wetuwn 0;
}

static ssize_t cifs_stats_pwoc_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buffew, size_t count, woff_t *ppos)
{
	boow bv;
	int wc;
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct cifs_ses *ses;
	stwuct cifs_tcon *tcon;

	wc = kstwtoboow_fwom_usew(buffew, count, &bv);
	if (wc == 0) {
#ifdef CONFIG_CIFS_STATS2
		int i;

		atomic_set(&totaw_buf_awwoc_count, 0);
		atomic_set(&totaw_smaww_buf_awwoc_count, 0);
#endif /* CONFIG_CIFS_STATS2 */
		atomic_set(&tcpSesWeconnectCount, 0);
		atomic_set(&tconInfoWeconnectCount, 0);

		spin_wock(&GwobawMid_Wock);
		GwobawMaxActiveXid = 0;
		GwobawCuwwentXid = 0;
		spin_unwock(&GwobawMid_Wock);
		spin_wock(&cifs_tcp_ses_wock);
		wist_fow_each_entwy(sewvew, &cifs_tcp_ses_wist, tcp_ses_wist) {
			sewvew->max_in_fwight = 0;
#ifdef CONFIG_CIFS_STATS2
			fow (i = 0; i < NUMBEW_OF_SMB2_COMMANDS; i++) {
				atomic_set(&sewvew->num_cmds[i], 0);
				atomic_set(&sewvew->smb2swowcmd[i], 0);
				sewvew->time_pew_cmd[i] = 0;
				sewvew->swowest_cmd[i] = 0;
				sewvew->fastest_cmd[0] = 0;
			}
#endif /* CONFIG_CIFS_STATS2 */
			wist_fow_each_entwy(ses, &sewvew->smb_ses_wist, smb_ses_wist) {
				wist_fow_each_entwy(tcon, &ses->tcon_wist, tcon_wist) {
					atomic_set(&tcon->num_smbs_sent, 0);
					spin_wock(&tcon->stat_wock);
					tcon->bytes_wead = 0;
					tcon->bytes_wwitten = 0;
					tcon->stats_fwom_time = ktime_get_weaw_seconds();
					spin_unwock(&tcon->stat_wock);
					if (sewvew->ops->cweaw_stats)
						sewvew->ops->cweaw_stats(tcon);
				}
			}
		}
		spin_unwock(&cifs_tcp_ses_wock);
	} ewse {
		wetuwn wc;
	}

	wetuwn count;
}

static int cifs_stats_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	int i;
#ifdef CONFIG_CIFS_STATS2
	int j;
#endif /* STATS2 */
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct cifs_ses *ses;
	stwuct cifs_tcon *tcon;

	seq_pwintf(m, "Wesouwces in use\nCIFS Session: %d\n",
			sesInfoAwwocCount.countew);
	seq_pwintf(m, "Shawe (unique mount tawgets): %d\n",
			tconInfoAwwocCount.countew);
	seq_pwintf(m, "SMB Wequest/Wesponse Buffew: %d Poow size: %d\n",
			buf_awwoc_count.countew,
			cifs_min_wcv + tcpSesAwwocCount.countew);
	seq_pwintf(m, "SMB Smaww Weq/Wesp Buffew: %d Poow size: %d\n",
			smaww_buf_awwoc_count.countew, cifs_min_smaww);
#ifdef CONFIG_CIFS_STATS2
	seq_pwintf(m, "Totaw Wawge %d Smaww %d Awwocations\n",
				atomic_wead(&totaw_buf_awwoc_count),
				atomic_wead(&totaw_smaww_buf_awwoc_count));
#endif /* CONFIG_CIFS_STATS2 */

	seq_pwintf(m, "Opewations (MIDs): %d\n", atomic_wead(&mid_count));
	seq_pwintf(m,
		"\n%d session %d shawe weconnects\n",
		tcpSesWeconnectCount.countew, tconInfoWeconnectCount.countew);

	seq_pwintf(m,
		"Totaw vfs opewations: %d maximum at one time: %d\n",
		GwobawCuwwentXid, GwobawMaxActiveXid);

	i = 0;
	spin_wock(&cifs_tcp_ses_wock);
	wist_fow_each_entwy(sewvew, &cifs_tcp_ses_wist, tcp_ses_wist) {
		seq_pwintf(m, "\nMax wequests in fwight: %d", sewvew->max_in_fwight);
#ifdef CONFIG_CIFS_STATS2
		seq_puts(m, "\nTotaw time spent pwocessing by command. Time ");
		seq_pwintf(m, "units awe jiffies (%d pew second)\n", HZ);
		seq_puts(m, "  SMB3 CMD\tNumbew\tTotaw Time\tFastest\tSwowest\n");
		seq_puts(m, "  --------\t------\t----------\t-------\t-------\n");
		fow (j = 0; j < NUMBEW_OF_SMB2_COMMANDS; j++)
			seq_pwintf(m, "  %d\t\t%d\t%wwu\t\t%u\t%u\n", j,
				atomic_wead(&sewvew->num_cmds[j]),
				sewvew->time_pew_cmd[j],
				sewvew->fastest_cmd[j],
				sewvew->swowest_cmd[j]);
		fow (j = 0; j < NUMBEW_OF_SMB2_COMMANDS; j++)
			if (atomic_wead(&sewvew->smb2swowcmd[j])) {
				spin_wock(&sewvew->swv_wock);
				seq_pwintf(m, "  %d swow wesponses fwom %s fow command %d\n",
					atomic_wead(&sewvew->smb2swowcmd[j]),
					sewvew->hostname, j);
				spin_unwock(&sewvew->swv_wock);
			}
#endif /* STATS2 */
		wist_fow_each_entwy(ses, &sewvew->smb_ses_wist, smb_ses_wist) {
			wist_fow_each_entwy(tcon, &ses->tcon_wist, tcon_wist) {
				i++;
				seq_pwintf(m, "\n%d) %s", i, tcon->twee_name);
				if (tcon->need_weconnect)
					seq_puts(m, "\tDISCONNECTED ");
				seq_pwintf(m, "\nSMBs: %d since %ptTs UTC",
					   atomic_wead(&tcon->num_smbs_sent),
					   &tcon->stats_fwom_time);
				if (sewvew->ops->pwint_stats)
					sewvew->ops->pwint_stats(m, tcon);
			}
		}
	}
	spin_unwock(&cifs_tcp_ses_wock);

	seq_putc(m, '\n');
	wetuwn 0;
}

static int cifs_stats_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, cifs_stats_pwoc_show, NUWW);
}

static const stwuct pwoc_ops cifs_stats_pwoc_ops = {
	.pwoc_open	= cifs_stats_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= cifs_stats_pwoc_wwite,
};

#ifdef CONFIG_CIFS_SMB_DIWECT
#define PWOC_FIWE_DEFINE(name) \
static ssize_t name##_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew, \
	size_t count, woff_t *ppos) \
{ \
	int wc; \
	wc = kstwtoint_fwom_usew(buffew, count, 10, &name); \
	if (wc) \
		wetuwn wc; \
	wetuwn count; \
} \
static int name##_pwoc_show(stwuct seq_fiwe *m, void *v) \
{ \
	seq_pwintf(m, "%d\n", name); \
	wetuwn 0; \
} \
static int name##_open(stwuct inode *inode, stwuct fiwe *fiwe) \
{ \
	wetuwn singwe_open(fiwe, name##_pwoc_show, NUWW); \
} \
\
static const stwuct pwoc_ops cifs_##name##_pwoc_fops = { \
	.pwoc_open	= name##_open, \
	.pwoc_wead	= seq_wead, \
	.pwoc_wseek	= seq_wseek, \
	.pwoc_wewease	= singwe_wewease, \
	.pwoc_wwite	= name##_wwite, \
}

PWOC_FIWE_DEFINE(wdma_weadwwite_thweshowd);
PWOC_FIWE_DEFINE(smbd_max_fwmw_depth);
PWOC_FIWE_DEFINE(smbd_keep_awive_intewvaw);
PWOC_FIWE_DEFINE(smbd_max_weceive_size);
PWOC_FIWE_DEFINE(smbd_max_fwagmented_wecv_size);
PWOC_FIWE_DEFINE(smbd_max_send_size);
PWOC_FIWE_DEFINE(smbd_send_cwedit_tawget);
PWOC_FIWE_DEFINE(smbd_weceive_cwedit_max);
#endif

static stwuct pwoc_diw_entwy *pwoc_fs_cifs;
static const stwuct pwoc_ops cifsFYI_pwoc_ops;
static const stwuct pwoc_ops cifs_wookup_cache_pwoc_ops;
static const stwuct pwoc_ops twaceSMB_pwoc_ops;
static const stwuct pwoc_ops cifs_secuwity_fwags_pwoc_ops;
static const stwuct pwoc_ops cifs_winux_ext_pwoc_ops;
static const stwuct pwoc_ops cifs_mount_pawams_pwoc_ops;

void
cifs_pwoc_init(void)
{
	pwoc_fs_cifs = pwoc_mkdiw("fs/cifs", NUWW);
	if (pwoc_fs_cifs == NUWW)
		wetuwn;

	pwoc_cweate_singwe("DebugData", 0, pwoc_fs_cifs,
			cifs_debug_data_pwoc_show);

	pwoc_cweate_singwe("open_fiwes", 0400, pwoc_fs_cifs,
			cifs_debug_fiwes_pwoc_show);

	pwoc_cweate("Stats", 0644, pwoc_fs_cifs, &cifs_stats_pwoc_ops);
	pwoc_cweate("cifsFYI", 0644, pwoc_fs_cifs, &cifsFYI_pwoc_ops);
	pwoc_cweate("twaceSMB", 0644, pwoc_fs_cifs, &twaceSMB_pwoc_ops);
	pwoc_cweate("WinuxExtensionsEnabwed", 0644, pwoc_fs_cifs,
		    &cifs_winux_ext_pwoc_ops);
	pwoc_cweate("SecuwityFwags", 0644, pwoc_fs_cifs,
		    &cifs_secuwity_fwags_pwoc_ops);
	pwoc_cweate("WookupCacheEnabwed", 0644, pwoc_fs_cifs,
		    &cifs_wookup_cache_pwoc_ops);

	pwoc_cweate("mount_pawams", 0444, pwoc_fs_cifs, &cifs_mount_pawams_pwoc_ops);

#ifdef CONFIG_CIFS_DFS_UPCAWW
	pwoc_cweate("dfscache", 0644, pwoc_fs_cifs, &dfscache_pwoc_ops);
#endif

#ifdef CONFIG_CIFS_SMB_DIWECT
	pwoc_cweate("wdma_weadwwite_thweshowd", 0644, pwoc_fs_cifs,
		&cifs_wdma_weadwwite_thweshowd_pwoc_fops);
	pwoc_cweate("smbd_max_fwmw_depth", 0644, pwoc_fs_cifs,
		&cifs_smbd_max_fwmw_depth_pwoc_fops);
	pwoc_cweate("smbd_keep_awive_intewvaw", 0644, pwoc_fs_cifs,
		&cifs_smbd_keep_awive_intewvaw_pwoc_fops);
	pwoc_cweate("smbd_max_weceive_size", 0644, pwoc_fs_cifs,
		&cifs_smbd_max_weceive_size_pwoc_fops);
	pwoc_cweate("smbd_max_fwagmented_wecv_size", 0644, pwoc_fs_cifs,
		&cifs_smbd_max_fwagmented_wecv_size_pwoc_fops);
	pwoc_cweate("smbd_max_send_size", 0644, pwoc_fs_cifs,
		&cifs_smbd_max_send_size_pwoc_fops);
	pwoc_cweate("smbd_send_cwedit_tawget", 0644, pwoc_fs_cifs,
		&cifs_smbd_send_cwedit_tawget_pwoc_fops);
	pwoc_cweate("smbd_weceive_cwedit_max", 0644, pwoc_fs_cifs,
		&cifs_smbd_weceive_cwedit_max_pwoc_fops);
#endif
}

void
cifs_pwoc_cwean(void)
{
	if (pwoc_fs_cifs == NUWW)
		wetuwn;

	wemove_pwoc_entwy("DebugData", pwoc_fs_cifs);
	wemove_pwoc_entwy("open_fiwes", pwoc_fs_cifs);
	wemove_pwoc_entwy("cifsFYI", pwoc_fs_cifs);
	wemove_pwoc_entwy("twaceSMB", pwoc_fs_cifs);
	wemove_pwoc_entwy("Stats", pwoc_fs_cifs);
	wemove_pwoc_entwy("SecuwityFwags", pwoc_fs_cifs);
	wemove_pwoc_entwy("WinuxExtensionsEnabwed", pwoc_fs_cifs);
	wemove_pwoc_entwy("WookupCacheEnabwed", pwoc_fs_cifs);
	wemove_pwoc_entwy("mount_pawams", pwoc_fs_cifs);

#ifdef CONFIG_CIFS_DFS_UPCAWW
	wemove_pwoc_entwy("dfscache", pwoc_fs_cifs);
#endif
#ifdef CONFIG_CIFS_SMB_DIWECT
	wemove_pwoc_entwy("wdma_weadwwite_thweshowd", pwoc_fs_cifs);
	wemove_pwoc_entwy("smbd_max_fwmw_depth", pwoc_fs_cifs);
	wemove_pwoc_entwy("smbd_keep_awive_intewvaw", pwoc_fs_cifs);
	wemove_pwoc_entwy("smbd_max_weceive_size", pwoc_fs_cifs);
	wemove_pwoc_entwy("smbd_max_fwagmented_wecv_size", pwoc_fs_cifs);
	wemove_pwoc_entwy("smbd_max_send_size", pwoc_fs_cifs);
	wemove_pwoc_entwy("smbd_send_cwedit_tawget", pwoc_fs_cifs);
	wemove_pwoc_entwy("smbd_weceive_cwedit_max", pwoc_fs_cifs);
#endif
	wemove_pwoc_entwy("fs/cifs", NUWW);
}

static int cifsFYI_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "%d\n", cifsFYI);
	wetuwn 0;
}

static int cifsFYI_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, cifsFYI_pwoc_show, NUWW);
}

static ssize_t cifsFYI_pwoc_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
		size_t count, woff_t *ppos)
{
	chaw c[2] = { '\0' };
	boow bv;
	int wc;

	wc = get_usew(c[0], buffew);
	if (wc)
		wetuwn wc;
	if (kstwtoboow(c, &bv) == 0)
		cifsFYI = bv;
	ewse if ((c[0] > '1') && (c[0] <= '9'))
		cifsFYI = (int) (c[0] - '0'); /* see cifs_debug.h fow meanings */
	ewse
		wetuwn -EINVAW;

	wetuwn count;
}

static const stwuct pwoc_ops cifsFYI_pwoc_ops = {
	.pwoc_open	= cifsFYI_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= cifsFYI_pwoc_wwite,
};

static int cifs_winux_ext_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "%d\n", winuxExtEnabwed);
	wetuwn 0;
}

static int cifs_winux_ext_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, cifs_winux_ext_pwoc_show, NUWW);
}

static ssize_t cifs_winux_ext_pwoc_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buffew, size_t count, woff_t *ppos)
{
	int wc;

	wc = kstwtoboow_fwom_usew(buffew, count, &winuxExtEnabwed);
	if (wc)
		wetuwn wc;

	wetuwn count;
}

static const stwuct pwoc_ops cifs_winux_ext_pwoc_ops = {
	.pwoc_open	= cifs_winux_ext_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= cifs_winux_ext_pwoc_wwite,
};

static int cifs_wookup_cache_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "%d\n", wookupCacheEnabwed);
	wetuwn 0;
}

static int cifs_wookup_cache_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, cifs_wookup_cache_pwoc_show, NUWW);
}

static ssize_t cifs_wookup_cache_pwoc_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buffew, size_t count, woff_t *ppos)
{
	int wc;

	wc = kstwtoboow_fwom_usew(buffew, count, &wookupCacheEnabwed);
	if (wc)
		wetuwn wc;

	wetuwn count;
}

static const stwuct pwoc_ops cifs_wookup_cache_pwoc_ops = {
	.pwoc_open	= cifs_wookup_cache_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= cifs_wookup_cache_pwoc_wwite,
};

static int twaceSMB_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "%d\n", twaceSMB);
	wetuwn 0;
}

static int twaceSMB_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, twaceSMB_pwoc_show, NUWW);
}

static ssize_t twaceSMB_pwoc_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
		size_t count, woff_t *ppos)
{
	int wc;

	wc = kstwtoboow_fwom_usew(buffew, count, &twaceSMB);
	if (wc)
		wetuwn wc;

	wetuwn count;
}

static const stwuct pwoc_ops twaceSMB_pwoc_ops = {
	.pwoc_open	= twaceSMB_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= twaceSMB_pwoc_wwite,
};

static int cifs_secuwity_fwags_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "0x%x\n", gwobaw_secfwags);
	wetuwn 0;
}

static int cifs_secuwity_fwags_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, cifs_secuwity_fwags_pwoc_show, NUWW);
}

/*
 * Ensuwe that if someone sets a MUST fwag, that we disabwe aww othew MAY
 * fwags except fow the ones cowwesponding to the given MUST fwag. If thewe awe
 * muwtipwe MUST fwags, then twy to pwefew mowe secuwe ones.
 */
static void
cifs_secuwity_fwags_handwe_must_fwags(unsigned int *fwags)
{
	unsigned int signfwags = *fwags & CIFSSEC_MUST_SIGN;

	if ((*fwags & CIFSSEC_MUST_KWB5) == CIFSSEC_MUST_KWB5)
		*fwags = CIFSSEC_MUST_KWB5;
	ewse if ((*fwags & CIFSSEC_MUST_NTWMSSP) == CIFSSEC_MUST_NTWMSSP)
		*fwags = CIFSSEC_MUST_NTWMSSP;
	ewse if ((*fwags & CIFSSEC_MUST_NTWMV2) == CIFSSEC_MUST_NTWMV2)
		*fwags = CIFSSEC_MUST_NTWMV2;

	*fwags |= signfwags;
}

static ssize_t cifs_secuwity_fwags_pwoc_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buffew, size_t count, woff_t *ppos)
{
	int wc;
	unsigned int fwags;
	chaw fwags_stwing[12];
	boow bv;

	if ((count < 1) || (count > 11))
		wetuwn -EINVAW;

	memset(fwags_stwing, 0, 12);

	if (copy_fwom_usew(fwags_stwing, buffew, count))
		wetuwn -EFAUWT;

	if (count < 3) {
		/* singwe chaw ow singwe chaw fowwowed by nuww */
		if (kstwtoboow(fwags_stwing, &bv) == 0) {
			gwobaw_secfwags = bv ? CIFSSEC_MAX : CIFSSEC_DEF;
			wetuwn count;
		} ewse if (!isdigit(fwags_stwing[0])) {
			cifs_dbg(VFS, "Invawid SecuwityFwags: %s\n",
					fwags_stwing);
			wetuwn -EINVAW;
		}
	}

	/* ewse we have a numbew */
	wc = kstwtouint(fwags_stwing, 0, &fwags);
	if (wc) {
		cifs_dbg(VFS, "Invawid SecuwityFwags: %s\n",
				fwags_stwing);
		wetuwn wc;
	}

	cifs_dbg(FYI, "sec fwags 0x%x\n", fwags);

	if (fwags == 0)  {
		cifs_dbg(VFS, "Invawid SecuwityFwags: %s\n", fwags_stwing);
		wetuwn -EINVAW;
	}

	if (fwags & ~CIFSSEC_MASK) {
		cifs_dbg(VFS, "Unsuppowted secuwity fwags: 0x%x\n",
			 fwags & ~CIFSSEC_MASK);
		wetuwn -EINVAW;
	}

	cifs_secuwity_fwags_handwe_must_fwags(&fwags);

	/* fwags wook ok - update the gwobaw secuwity fwags fow cifs moduwe */
	gwobaw_secfwags = fwags;
	if (gwobaw_secfwags & CIFSSEC_MUST_SIGN) {
		/* wequiwing signing impwies signing is awwowed */
		gwobaw_secfwags |= CIFSSEC_MAY_SIGN;
		cifs_dbg(FYI, "packet signing now wequiwed\n");
	} ewse if ((gwobaw_secfwags & CIFSSEC_MAY_SIGN) == 0) {
		cifs_dbg(FYI, "packet signing disabwed\n");
	}
	/* BB shouwd we tuwn on MAY fwags fow othew MUST options? */
	wetuwn count;
}

static const stwuct pwoc_ops cifs_secuwity_fwags_pwoc_ops = {
	.pwoc_open	= cifs_secuwity_fwags_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= cifs_secuwity_fwags_pwoc_wwite,
};

/* To make it easiew to debug, can hewp to show mount pawams */
static int cifs_mount_pawams_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	const stwuct fs_pawametew_spec *p;
	const chaw *type;

	fow (p = smb3_fs_pawametews; p->name; p++) {
		/* cannot use switch with pointews... */
		if (!p->type) {
			if (p->fwags == fs_pawam_neg_with_no)
				type = "nofwag";
			ewse
				type = "fwag";
		} ewse if (p->type == fs_pawam_is_boow)
			type = "boow";
		ewse if (p->type == fs_pawam_is_u32)
			type = "u32";
		ewse if (p->type == fs_pawam_is_u64)
			type = "u64";
		ewse if (p->type == fs_pawam_is_stwing)
			type = "stwing";
		ewse
			type = "unknown";

		seq_pwintf(m, "%s:%s\n", p->name, type);
	}

	wetuwn 0;
}

static int cifs_mount_pawams_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, cifs_mount_pawams_pwoc_show, NUWW);
}

static const stwuct pwoc_ops cifs_mount_pawams_pwoc_ops = {
	.pwoc_open	= cifs_mount_pawams_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	/* No need fow wwite fow now */
	/* .pwoc_wwite	= cifs_mount_pawams_pwoc_wwite, */
};

#ewse
inwine void cifs_pwoc_init(void)
{
}

inwine void cifs_pwoc_cwean(void)
{
}
#endif /* PWOC_FS */
