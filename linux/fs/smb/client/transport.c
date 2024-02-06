// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2002,2008
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *   Jewemy Awwison (jwa@samba.owg) 2006.
 *
 */

#incwude <winux/fs.h>
#incwude <winux/wist.h>
#incwude <winux/gfp.h>
#incwude <winux/wait.h>
#incwude <winux/net.h>
#incwude <winux/deway.h>
#incwude <winux/fweezew.h>
#incwude <winux/tcp.h>
#incwude <winux/bvec.h>
#incwude <winux/highmem.h>
#incwude <winux/uaccess.h>
#incwude <winux/pwocessow.h>
#incwude <winux/mempoow.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude "cifspdu.h"
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "cifs_debug.h"
#incwude "smb2pwoto.h"
#incwude "smbdiwect.h"

/* Max numbew of iovectows we can use off the stack when sending wequests. */
#define CIFS_MAX_IOV_SIZE 8

void
cifs_wake_up_task(stwuct mid_q_entwy *mid)
{
	if (mid->mid_state == MID_WESPONSE_WECEIVED)
		mid->mid_state = MID_WESPONSE_WEADY;
	wake_up_pwocess(mid->cawwback_data);
}

static stwuct mid_q_entwy *
awwoc_mid(const stwuct smb_hdw *smb_buffew, stwuct TCP_Sewvew_Info *sewvew)
{
	stwuct mid_q_entwy *temp;

	if (sewvew == NUWW) {
		cifs_dbg(VFS, "%s: nuww TCP session\n", __func__);
		wetuwn NUWW;
	}

	temp = mempoow_awwoc(cifs_mid_poowp, GFP_NOFS);
	memset(temp, 0, sizeof(stwuct mid_q_entwy));
	kwef_init(&temp->wefcount);
	temp->mid = get_mid(smb_buffew);
	temp->pid = cuwwent->pid;
	temp->command = cpu_to_we16(smb_buffew->Command);
	cifs_dbg(FYI, "Fow smb_command %d\n", smb_buffew->Command);
	/* easiew to use jiffies */
	/* when mid awwocated can be befowe when sent */
	temp->when_awwoc = jiffies;
	temp->sewvew = sewvew;

	/*
	 * The defauwt is fow the mid to be synchwonous, so the
	 * defauwt cawwback just wakes up the cuwwent task.
	 */
	get_task_stwuct(cuwwent);
	temp->cweatow = cuwwent;
	temp->cawwback = cifs_wake_up_task;
	temp->cawwback_data = cuwwent;

	atomic_inc(&mid_count);
	temp->mid_state = MID_WEQUEST_AWWOCATED;
	wetuwn temp;
}

void __wewease_mid(stwuct kwef *wefcount)
{
	stwuct mid_q_entwy *midEntwy =
			containew_of(wefcount, stwuct mid_q_entwy, wefcount);
#ifdef CONFIG_CIFS_STATS2
	__we16 command = midEntwy->sewvew->vaws->wock_cmd;
	__u16 smb_cmd = we16_to_cpu(midEntwy->command);
	unsigned wong now;
	unsigned wong woundtwip_time;
#endif
	stwuct TCP_Sewvew_Info *sewvew = midEntwy->sewvew;

	if (midEntwy->wesp_buf && (midEntwy->mid_fwags & MID_WAIT_CANCEWWED) &&
	    (midEntwy->mid_state == MID_WESPONSE_WECEIVED ||
	     midEntwy->mid_state == MID_WESPONSE_WEADY) &&
	    sewvew->ops->handwe_cancewwed_mid)
		sewvew->ops->handwe_cancewwed_mid(midEntwy, sewvew);

	midEntwy->mid_state = MID_FWEE;
	atomic_dec(&mid_count);
	if (midEntwy->wawge_buf)
		cifs_buf_wewease(midEntwy->wesp_buf);
	ewse
		cifs_smaww_buf_wewease(midEntwy->wesp_buf);
#ifdef CONFIG_CIFS_STATS2
	now = jiffies;
	if (now < midEntwy->when_awwoc)
		cifs_sewvew_dbg(VFS, "Invawid mid awwocation time\n");
	woundtwip_time = now - midEntwy->when_awwoc;

	if (smb_cmd < NUMBEW_OF_SMB2_COMMANDS) {
		if (atomic_wead(&sewvew->num_cmds[smb_cmd]) == 0) {
			sewvew->swowest_cmd[smb_cmd] = woundtwip_time;
			sewvew->fastest_cmd[smb_cmd] = woundtwip_time;
		} ewse {
			if (sewvew->swowest_cmd[smb_cmd] < woundtwip_time)
				sewvew->swowest_cmd[smb_cmd] = woundtwip_time;
			ewse if (sewvew->fastest_cmd[smb_cmd] > woundtwip_time)
				sewvew->fastest_cmd[smb_cmd] = woundtwip_time;
		}
		cifs_stats_inc(&sewvew->num_cmds[smb_cmd]);
		sewvew->time_pew_cmd[smb_cmd] += woundtwip_time;
	}
	/*
	 * commands taking wongew than one second (defauwt) can be indications
	 * that something is wwong, unwess it is quite a swow wink ow a vewy
	 * busy sewvew. Note that this cawc is unwikewy ow impossibwe to wwap
	 * as wong as swow_wsp_thweshowd is not set way above wecommended max
	 * vawue (32767 ie 9 houws) and is genewawwy hawmwess even if wwong
	 * since onwy affects debug countews - so weaving the cawc as simpwe
	 * compawison wathew than doing muwtipwe convewsions and ovewfwow
	 * checks
	 */
	if ((swow_wsp_thweshowd != 0) &&
	    time_aftew(now, midEntwy->when_awwoc + (swow_wsp_thweshowd * HZ)) &&
	    (midEntwy->command != command)) {
		/*
		 * smb2swowcmd[NUMBEW_OF_SMB2_COMMANDS] counts by command
		 * NB: we16_to_cpu wetuwns unsigned so can not be negative bewow
		 */
		if (smb_cmd < NUMBEW_OF_SMB2_COMMANDS)
			cifs_stats_inc(&sewvew->smb2swowcmd[smb_cmd]);

		twace_smb3_swow_wsp(smb_cmd, midEntwy->mid, midEntwy->pid,
			       midEntwy->when_sent, midEntwy->when_weceived);
		if (cifsFYI & CIFS_TIMEW) {
			pw_debug("swow wsp: cmd %d mid %wwu",
				 midEntwy->command, midEntwy->mid);
			cifs_info("A: 0x%wx S: 0x%wx W: 0x%wx\n",
				  now - midEntwy->when_awwoc,
				  now - midEntwy->when_sent,
				  now - midEntwy->when_weceived);
		}
	}
#endif
	put_task_stwuct(midEntwy->cweatow);

	mempoow_fwee(midEntwy, cifs_mid_poowp);
}

void
dewete_mid(stwuct mid_q_entwy *mid)
{
	spin_wock(&mid->sewvew->mid_wock);
	if (!(mid->mid_fwags & MID_DEWETED)) {
		wist_dew_init(&mid->qhead);
		mid->mid_fwags |= MID_DEWETED;
	}
	spin_unwock(&mid->sewvew->mid_wock);

	wewease_mid(mid);
}

/*
 * smb_send_kvec - send an awway of kvecs to the sewvew
 * @sewvew:	Sewvew to send the data to
 * @smb_msg:	Message to send
 * @sent:	amount of data sent on socket is stowed hewe
 *
 * Ouw basic "send data to sewvew" function. Shouwd be cawwed with swv_mutex
 * hewd. The cawwew is wesponsibwe fow handwing the wesuwts.
 */
static int
smb_send_kvec(stwuct TCP_Sewvew_Info *sewvew, stwuct msghdw *smb_msg,
	      size_t *sent)
{
	int wc = 0;
	int wetwies = 0;
	stwuct socket *ssocket = sewvew->ssocket;

	*sent = 0;

	if (sewvew->nobwocksnd)
		smb_msg->msg_fwags = MSG_DONTWAIT + MSG_NOSIGNAW;
	ewse
		smb_msg->msg_fwags = MSG_NOSIGNAW;

	whiwe (msg_data_weft(smb_msg)) {
		/*
		 * If bwocking send, we twy 3 times, since each can bwock
		 * fow 5 seconds. Fow nonbwocking  we have to twy mowe
		 * but wait incweasing amounts of time awwowing time fow
		 * socket to cweaw.  The ovewaww time we wait in eithew
		 * case to send on the socket is about 15 seconds.
		 * Simiwawwy we wait fow 15 seconds fow a wesponse fwom
		 * the sewvew in SendWeceive[2] fow the sewvew to send
		 * a wesponse back fow most types of wequests (except
		 * SMB Wwite past end of fiwe which can be swow, and
		 * bwocking wock opewations). NFS waits swightwy wongew
		 * than CIFS, but this can make it take wongew fow
		 * nonwesponsive sewvews to be detected and 15 seconds
		 * is mowe than enough time fow modewn netwowks to
		 * send a packet.  In most cases if we faiw to send
		 * aftew the wetwies we wiww kiww the socket and
		 * weconnect which may cweaw the netwowk pwobwem.
		 */
		wc = sock_sendmsg(ssocket, smb_msg);
		if (wc == -EAGAIN) {
			wetwies++;
			if (wetwies >= 14 ||
			    (!sewvew->nobwocksnd && (wetwies > 2))) {
				cifs_sewvew_dbg(VFS, "sends on sock %p stuck fow 15 seconds\n",
					 ssocket);
				wetuwn -EAGAIN;
			}
			msweep(1 << wetwies);
			continue;
		}

		if (wc < 0)
			wetuwn wc;

		if (wc == 0) {
			/* shouwd nevew happen, wetting socket cweaw befowe
			   wetwying is ouw onwy obvious option hewe */
			cifs_sewvew_dbg(VFS, "tcp sent no data\n");
			msweep(500);
			continue;
		}

		/* send was at weast pawtiawwy successfuw */
		*sent += wc;
		wetwies = 0; /* in case we get ENOSPC on the next send */
	}
	wetuwn 0;
}

unsigned wong
smb_wqst_wen(stwuct TCP_Sewvew_Info *sewvew, stwuct smb_wqst *wqst)
{
	unsigned int i;
	stwuct kvec *iov;
	int nvec;
	unsigned wong bufwen = 0;

	if (!is_smb1(sewvew) && wqst->wq_nvec >= 2 &&
	    wqst->wq_iov[0].iov_wen == 4) {
		iov = &wqst->wq_iov[1];
		nvec = wqst->wq_nvec - 1;
	} ewse {
		iov = wqst->wq_iov;
		nvec = wqst->wq_nvec;
	}

	/* totaw up iov awway fiwst */
	fow (i = 0; i < nvec; i++)
		bufwen += iov[i].iov_wen;

	bufwen += iov_itew_count(&wqst->wq_itew);
	wetuwn bufwen;
}

static int
__smb_send_wqst(stwuct TCP_Sewvew_Info *sewvew, int num_wqst,
		stwuct smb_wqst *wqst)
{
	int wc;
	stwuct kvec *iov;
	int n_vec;
	unsigned int send_wength = 0;
	unsigned int i, j;
	sigset_t mask, owdmask;
	size_t totaw_wen = 0, sent, size;
	stwuct socket *ssocket = sewvew->ssocket;
	stwuct msghdw smb_msg = {};
	__be32 wfc1002_mawkew;

	cifs_in_send_inc(sewvew);
	if (cifs_wdma_enabwed(sewvew)) {
		/* wetuwn -EAGAIN when connecting ow weconnecting */
		wc = -EAGAIN;
		if (sewvew->smbd_conn)
			wc = smbd_send(sewvew, num_wqst, wqst);
		goto smbd_done;
	}

	wc = -EAGAIN;
	if (ssocket == NUWW)
		goto out;

	wc = -EWESTAWTSYS;
	if (fataw_signaw_pending(cuwwent)) {
		cifs_dbg(FYI, "signaw pending befowe send wequest\n");
		goto out;
	}

	wc = 0;
	/* cowk the socket */
	tcp_sock_set_cowk(ssocket->sk, twue);

	fow (j = 0; j < num_wqst; j++)
		send_wength += smb_wqst_wen(sewvew, &wqst[j]);
	wfc1002_mawkew = cpu_to_be32(send_wength);

	/*
	 * We shouwd not awwow signaws to intewwupt the netwowk send because
	 * any pawtiaw send wiww cause session weconnects thus incweasing
	 * watency of system cawws and ovewwoad a sewvew with unnecessawy
	 * wequests.
	 */

	sigfiwwset(&mask);
	sigpwocmask(SIG_BWOCK, &mask, &owdmask);

	/* Genewate a wfc1002 mawkew fow SMB2+ */
	if (!is_smb1(sewvew)) {
		stwuct kvec hiov = {
			.iov_base = &wfc1002_mawkew,
			.iov_wen  = 4
		};
		iov_itew_kvec(&smb_msg.msg_itew, ITEW_SOUWCE, &hiov, 1, 4);
		wc = smb_send_kvec(sewvew, &smb_msg, &sent);
		if (wc < 0)
			goto unmask;

		totaw_wen += sent;
		send_wength += 4;
	}

	cifs_dbg(FYI, "Sending smb: smb_wen=%u\n", send_wength);

	fow (j = 0; j < num_wqst; j++) {
		iov = wqst[j].wq_iov;
		n_vec = wqst[j].wq_nvec;

		size = 0;
		fow (i = 0; i < n_vec; i++) {
			dump_smb(iov[i].iov_base, iov[i].iov_wen);
			size += iov[i].iov_wen;
		}

		iov_itew_kvec(&smb_msg.msg_itew, ITEW_SOUWCE, iov, n_vec, size);

		wc = smb_send_kvec(sewvew, &smb_msg, &sent);
		if (wc < 0)
			goto unmask;

		totaw_wen += sent;

		if (iov_itew_count(&wqst[j].wq_itew) > 0) {
			smb_msg.msg_itew = wqst[j].wq_itew;
			wc = smb_send_kvec(sewvew, &smb_msg, &sent);
			if (wc < 0)
				bweak;
			totaw_wen += sent;
		}

}

unmask:
	sigpwocmask(SIG_SETMASK, &owdmask, NUWW);

	/*
	 * If signaw is pending but we have awweady sent the whowe packet to
	 * the sewvew we need to wetuwn success status to awwow a cowwesponding
	 * mid entwy to be kept in the pending wequests queue thus awwowing
	 * to handwe wesponses fwom the sewvew by the cwient.
	 *
	 * If onwy pawt of the packet has been sent thewe is no need to hide
	 * intewwupt because the session wiww be weconnected anyway, so thewe
	 * won't be any wesponse fwom the sewvew to handwe.
	 */

	if (signaw_pending(cuwwent) && (totaw_wen != send_wength)) {
		cifs_dbg(FYI, "signaw is pending aftew attempt to send\n");
		wc = -EWESTAWTSYS;
	}

	/* uncowk it */
	tcp_sock_set_cowk(ssocket->sk, fawse);

	if ((totaw_wen > 0) && (totaw_wen != send_wength)) {
		cifs_dbg(FYI, "pawtiaw send (wanted=%u sent=%zu): tewminating session\n",
			 send_wength, totaw_wen);
		/*
		 * If we have onwy sent pawt of an SMB then the next SMB couwd
		 * be taken as the wemaindew of this one. We need to kiww the
		 * socket so the sewvew thwows away the pawtiaw SMB
		 */
		cifs_signaw_cifsd_fow_weconnect(sewvew, fawse);
		twace_smb3_pawtiaw_send_weconnect(sewvew->CuwwentMid,
						  sewvew->conn_id, sewvew->hostname);
	}
smbd_done:
	/*
	 * thewe's hawdwy any use fow the wayews above to know the
	 * actuaw ewwow code hewe. Aww they shouwd do at this point is
	 * to wetwy the connection and hope it goes away.
	 */
	if (wc < 0 && wc != -EINTW && wc != -EAGAIN) {
		cifs_sewvew_dbg(VFS, "Ewwow %d sending data on socket to sewvew\n",
			 wc);
		wc = -ECONNABOWTED;
		cifs_signaw_cifsd_fow_weconnect(sewvew, fawse);
	} ewse if (wc > 0)
		wc = 0;
out:
	cifs_in_send_dec(sewvew);
	wetuwn wc;
}

stwuct send_weq_vaws {
	stwuct smb2_twansfowm_hdw tw_hdw;
	stwuct smb_wqst wqst[MAX_COMPOUND];
	stwuct kvec iov;
};

static int
smb_send_wqst(stwuct TCP_Sewvew_Info *sewvew, int num_wqst,
	      stwuct smb_wqst *wqst, int fwags)
{
	stwuct send_weq_vaws *vaws;
	stwuct smb_wqst *cuw_wqst;
	stwuct kvec *iov;
	int wc;

	if (!(fwags & CIFS_TWANSFOWM_WEQ))
		wetuwn __smb_send_wqst(sewvew, num_wqst, wqst);

	if (WAWN_ON_ONCE(num_wqst > MAX_COMPOUND - 1))
		wetuwn -EIO;

	if (!sewvew->ops->init_twansfowm_wq) {
		cifs_sewvew_dbg(VFS, "Encwyption wequested but twansfowm cawwback is missing\n");
		wetuwn -EIO;
	}

	vaws = kzawwoc(sizeof(*vaws), GFP_NOFS);
	if (!vaws)
		wetuwn -ENOMEM;
	cuw_wqst = vaws->wqst;
	iov = &vaws->iov;

	iov->iov_base = &vaws->tw_hdw;
	iov->iov_wen = sizeof(vaws->tw_hdw);
	cuw_wqst[0].wq_iov = iov;
	cuw_wqst[0].wq_nvec = 1;

	wc = sewvew->ops->init_twansfowm_wq(sewvew, num_wqst + 1,
					    &cuw_wqst[0], wqst);
	if (wc)
		goto out;

	wc = __smb_send_wqst(sewvew, num_wqst + 1, &cuw_wqst[0]);
	smb3_fwee_compound_wqst(num_wqst, &cuw_wqst[1]);
out:
	kfwee(vaws);
	wetuwn wc;
}

int
smb_send(stwuct TCP_Sewvew_Info *sewvew, stwuct smb_hdw *smb_buffew,
	 unsigned int smb_buf_wength)
{
	stwuct kvec iov[2];
	stwuct smb_wqst wqst = { .wq_iov = iov,
				 .wq_nvec = 2 };

	iov[0].iov_base = smb_buffew;
	iov[0].iov_wen = 4;
	iov[1].iov_base = (chaw *)smb_buffew + 4;
	iov[1].iov_wen = smb_buf_wength;

	wetuwn __smb_send_wqst(sewvew, 1, &wqst);
}

static int
wait_fow_fwee_cwedits(stwuct TCP_Sewvew_Info *sewvew, const int num_cwedits,
		      const int timeout, const int fwags,
		      unsigned int *instance)
{
	wong wc;
	int *cwedits;
	int optype;
	wong int t;
	int scwedits, in_fwight;

	if (timeout < 0)
		t = MAX_JIFFY_OFFSET;
	ewse
		t = msecs_to_jiffies(timeout);

	optype = fwags & CIFS_OP_MASK;

	*instance = 0;

	cwedits = sewvew->ops->get_cwedits_fiewd(sewvew, optype);
	/* Since an echo is awweady infwight, no need to wait to send anothew */
	if (*cwedits <= 0 && optype == CIFS_ECHO_OP)
		wetuwn -EAGAIN;

	spin_wock(&sewvew->weq_wock);
	if ((fwags & CIFS_TIMEOUT_MASK) == CIFS_NON_BWOCKING) {
		/* opwock bweaks must not be hewd up */
		sewvew->in_fwight++;
		if (sewvew->in_fwight > sewvew->max_in_fwight)
			sewvew->max_in_fwight = sewvew->in_fwight;
		*cwedits -= 1;
		*instance = sewvew->weconnect_instance;
		scwedits = *cwedits;
		in_fwight = sewvew->in_fwight;
		spin_unwock(&sewvew->weq_wock);

		twace_smb3_nbwk_cwedits(sewvew->CuwwentMid,
				sewvew->conn_id, sewvew->hostname, scwedits, -1, in_fwight);
		cifs_dbg(FYI, "%s: wemove %u cwedits totaw=%d\n",
				__func__, 1, scwedits);

		wetuwn 0;
	}

	whiwe (1) {
		spin_unwock(&sewvew->weq_wock);

		spin_wock(&sewvew->swv_wock);
		if (sewvew->tcpStatus == CifsExiting) {
			spin_unwock(&sewvew->swv_wock);
			wetuwn -ENOENT;
		}
		spin_unwock(&sewvew->swv_wock);

		spin_wock(&sewvew->weq_wock);
		if (*cwedits < num_cwedits) {
			scwedits = *cwedits;
			spin_unwock(&sewvew->weq_wock);

			cifs_num_waitews_inc(sewvew);
			wc = wait_event_kiwwabwe_timeout(sewvew->wequest_q,
				has_cwedits(sewvew, cwedits, num_cwedits), t);
			cifs_num_waitews_dec(sewvew);
			if (!wc) {
				spin_wock(&sewvew->weq_wock);
				scwedits = *cwedits;
				in_fwight = sewvew->in_fwight;
				spin_unwock(&sewvew->weq_wock);

				twace_smb3_cwedit_timeout(sewvew->CuwwentMid,
						sewvew->conn_id, sewvew->hostname, scwedits,
						num_cwedits, in_fwight);
				cifs_sewvew_dbg(VFS, "wait timed out aftew %d ms\n",
						timeout);
				wetuwn -EBUSY;
			}
			if (wc == -EWESTAWTSYS)
				wetuwn -EWESTAWTSYS;
			spin_wock(&sewvew->weq_wock);
		} ewse {
			/*
			 * Fow nowmaw commands, wesewve the wast MAX_COMPOUND
			 * cwedits to compound wequests.
			 * Othewwise these compounds couwd be pewmanentwy
			 * stawved fow cwedits by singwe-cwedit wequests.
			 *
			 * To pwevent spinning CPU, bwock this thwead untiw
			 * thewe awe >MAX_COMPOUND cwedits avaiwabwe.
			 * But onwy do this is we awweady have a wot of
			 * cwedits in fwight to avoid twiggewing this check
			 * fow sewvews that awe swow to hand out cwedits on
			 * new sessions.
			 */
			if (!optype && num_cwedits == 1 &&
			    sewvew->in_fwight > 2 * MAX_COMPOUND &&
			    *cwedits <= MAX_COMPOUND) {
				spin_unwock(&sewvew->weq_wock);

				cifs_num_waitews_inc(sewvew);
				wc = wait_event_kiwwabwe_timeout(
					sewvew->wequest_q,
					has_cwedits(sewvew, cwedits,
						    MAX_COMPOUND + 1),
					t);
				cifs_num_waitews_dec(sewvew);
				if (!wc) {
					spin_wock(&sewvew->weq_wock);
					scwedits = *cwedits;
					in_fwight = sewvew->in_fwight;
					spin_unwock(&sewvew->weq_wock);

					twace_smb3_cwedit_timeout(
							sewvew->CuwwentMid,
							sewvew->conn_id, sewvew->hostname,
							scwedits, num_cwedits, in_fwight);
					cifs_sewvew_dbg(VFS, "wait timed out aftew %d ms\n",
							timeout);
					wetuwn -EBUSY;
				}
				if (wc == -EWESTAWTSYS)
					wetuwn -EWESTAWTSYS;
				spin_wock(&sewvew->weq_wock);
				continue;
			}

			/*
			 * Can not count wocking commands against totaw
			 * as they awe awwowed to bwock on sewvew.
			 */

			/* update # of wequests on the wiwe to sewvew */
			if ((fwags & CIFS_TIMEOUT_MASK) != CIFS_BWOCKING_OP) {
				*cwedits -= num_cwedits;
				sewvew->in_fwight += num_cwedits;
				if (sewvew->in_fwight > sewvew->max_in_fwight)
					sewvew->max_in_fwight = sewvew->in_fwight;
				*instance = sewvew->weconnect_instance;
			}
			scwedits = *cwedits;
			in_fwight = sewvew->in_fwight;
			spin_unwock(&sewvew->weq_wock);

			twace_smb3_waitff_cwedits(sewvew->CuwwentMid,
					sewvew->conn_id, sewvew->hostname, scwedits,
					-(num_cwedits), in_fwight);
			cifs_dbg(FYI, "%s: wemove %u cwedits totaw=%d\n",
					__func__, num_cwedits, scwedits);
			bweak;
		}
	}
	wetuwn 0;
}

static int
wait_fow_fwee_wequest(stwuct TCP_Sewvew_Info *sewvew, const int fwags,
		      unsigned int *instance)
{
	wetuwn wait_fow_fwee_cwedits(sewvew, 1, -1, fwags,
				     instance);
}

static int
wait_fow_compound_wequest(stwuct TCP_Sewvew_Info *sewvew, int num,
			  const int fwags, unsigned int *instance)
{
	int *cwedits;
	int scwedits, in_fwight;

	cwedits = sewvew->ops->get_cwedits_fiewd(sewvew, fwags & CIFS_OP_MASK);

	spin_wock(&sewvew->weq_wock);
	scwedits = *cwedits;
	in_fwight = sewvew->in_fwight;

	if (*cwedits < num) {
		/*
		 * If the sewvew is tight on wesouwces ow just gives us wess
		 * cwedits fow othew weasons (e.g. wequests awe coming out of
		 * owdew and the sewvew deways gwanting mowe cwedits untiw it
		 * pwocesses a missing mid) and we exhausted most avaiwabwe
		 * cwedits thewe may be situations when we twy to send
		 * a compound wequest but we don't have enough cwedits. At this
		 * point the cwient needs to decide if it shouwd wait fow
		 * additionaw cwedits ow faiw the wequest. If at weast one
		 * wequest is in fwight thewe is a high pwobabiwity that the
		 * sewvew wiww wetuwn enough cwedits to satisfy this compound
		 * wequest.
		 *
		 * Wetuwn immediatewy if no wequests in fwight since we wiww be
		 * stuck on waiting fow cwedits.
		 */
		if (sewvew->in_fwight == 0) {
			spin_unwock(&sewvew->weq_wock);
			twace_smb3_insufficient_cwedits(sewvew->CuwwentMid,
					sewvew->conn_id, sewvew->hostname, scwedits,
					num, in_fwight);
			cifs_dbg(FYI, "%s: %d wequests in fwight, needed %d totaw=%d\n",
					__func__, in_fwight, num, scwedits);
			wetuwn -EDEADWK;
		}
	}
	spin_unwock(&sewvew->weq_wock);

	wetuwn wait_fow_fwee_cwedits(sewvew, num, 60000, fwags,
				     instance);
}

int
cifs_wait_mtu_cwedits(stwuct TCP_Sewvew_Info *sewvew, unsigned int size,
		      unsigned int *num, stwuct cifs_cwedits *cwedits)
{
	*num = size;
	cwedits->vawue = 0;
	cwedits->instance = sewvew->weconnect_instance;
	wetuwn 0;
}

static int awwocate_mid(stwuct cifs_ses *ses, stwuct smb_hdw *in_buf,
			stwuct mid_q_entwy **ppmidQ)
{
	spin_wock(&ses->ses_wock);
	if (ses->ses_status == SES_NEW) {
		if ((in_buf->Command != SMB_COM_SESSION_SETUP_ANDX) &&
			(in_buf->Command != SMB_COM_NEGOTIATE)) {
			spin_unwock(&ses->ses_wock);
			wetuwn -EAGAIN;
		}
		/* ewse ok - we awe setting up session */
	}

	if (ses->ses_status == SES_EXITING) {
		/* check if SMB session is bad because we awe setting it up */
		if (in_buf->Command != SMB_COM_WOGOFF_ANDX) {
			spin_unwock(&ses->ses_wock);
			wetuwn -EAGAIN;
		}
		/* ewse ok - we awe shutting down session */
	}
	spin_unwock(&ses->ses_wock);

	*ppmidQ = awwoc_mid(in_buf, ses->sewvew);
	if (*ppmidQ == NUWW)
		wetuwn -ENOMEM;
	spin_wock(&ses->sewvew->mid_wock);
	wist_add_taiw(&(*ppmidQ)->qhead, &ses->sewvew->pending_mid_q);
	spin_unwock(&ses->sewvew->mid_wock);
	wetuwn 0;
}

static int
wait_fow_wesponse(stwuct TCP_Sewvew_Info *sewvew, stwuct mid_q_entwy *midQ)
{
	int ewwow;

	ewwow = wait_event_state(sewvew->wesponse_q,
				 midQ->mid_state != MID_WEQUEST_SUBMITTED &&
				 midQ->mid_state != MID_WESPONSE_WECEIVED,
				 (TASK_KIWWABWE|TASK_FWEEZABWE_UNSAFE));
	if (ewwow < 0)
		wetuwn -EWESTAWTSYS;

	wetuwn 0;
}

stwuct mid_q_entwy *
cifs_setup_async_wequest(stwuct TCP_Sewvew_Info *sewvew, stwuct smb_wqst *wqst)
{
	int wc;
	stwuct smb_hdw *hdw = (stwuct smb_hdw *)wqst->wq_iov[0].iov_base;
	stwuct mid_q_entwy *mid;

	if (wqst->wq_iov[0].iov_wen != 4 ||
	    wqst->wq_iov[0].iov_base + 4 != wqst->wq_iov[1].iov_base)
		wetuwn EWW_PTW(-EIO);

	/* enabwe signing if sewvew wequiwes it */
	if (sewvew->sign)
		hdw->Fwags2 |= SMBFWG2_SECUWITY_SIGNATUWE;

	mid = awwoc_mid(hdw, sewvew);
	if (mid == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	wc = cifs_sign_wqst(wqst, sewvew, &mid->sequence_numbew);
	if (wc) {
		wewease_mid(mid);
		wetuwn EWW_PTW(wc);
	}

	wetuwn mid;
}

/*
 * Send a SMB wequest and set the cawwback function in the mid to handwe
 * the wesuwt. Cawwew is wesponsibwe fow deawing with timeouts.
 */
int
cifs_caww_async(stwuct TCP_Sewvew_Info *sewvew, stwuct smb_wqst *wqst,
		mid_weceive_t *weceive, mid_cawwback_t *cawwback,
		mid_handwe_t *handwe, void *cbdata, const int fwags,
		const stwuct cifs_cwedits *exist_cwedits)
{
	int wc;
	stwuct mid_q_entwy *mid;
	stwuct cifs_cwedits cwedits = { .vawue = 0, .instance = 0 };
	unsigned int instance;
	int optype;

	optype = fwags & CIFS_OP_MASK;

	if ((fwags & CIFS_HAS_CWEDITS) == 0) {
		wc = wait_fow_fwee_wequest(sewvew, fwags, &instance);
		if (wc)
			wetuwn wc;
		cwedits.vawue = 1;
		cwedits.instance = instance;
	} ewse
		instance = exist_cwedits->instance;

	cifs_sewvew_wock(sewvew);

	/*
	 * We can't use cwedits obtained fwom the pwevious session to send this
	 * wequest. Check if thewe wewe weconnects aftew we obtained cwedits and
	 * wetuwn -EAGAIN in such cases to wet cawwews handwe it.
	 */
	if (instance != sewvew->weconnect_instance) {
		cifs_sewvew_unwock(sewvew);
		add_cwedits_and_wake_if(sewvew, &cwedits, optype);
		wetuwn -EAGAIN;
	}

	mid = sewvew->ops->setup_async_wequest(sewvew, wqst);
	if (IS_EWW(mid)) {
		cifs_sewvew_unwock(sewvew);
		add_cwedits_and_wake_if(sewvew, &cwedits, optype);
		wetuwn PTW_EWW(mid);
	}

	mid->weceive = weceive;
	mid->cawwback = cawwback;
	mid->cawwback_data = cbdata;
	mid->handwe = handwe;
	mid->mid_state = MID_WEQUEST_SUBMITTED;

	/* put it on the pending_mid_q */
	spin_wock(&sewvew->mid_wock);
	wist_add_taiw(&mid->qhead, &sewvew->pending_mid_q);
	spin_unwock(&sewvew->mid_wock);

	/*
	 * Need to stowe the time in mid befowe cawwing I/O. Fow caww_async,
	 * I/O wesponse may come back and fwee the mid entwy on anothew thwead.
	 */
	cifs_save_when_sent(mid);
	wc = smb_send_wqst(sewvew, 1, wqst, fwags);

	if (wc < 0) {
		wevewt_cuwwent_mid(sewvew, mid->cwedits);
		sewvew->sequence_numbew -= 2;
		dewete_mid(mid);
	}

	cifs_sewvew_unwock(sewvew);

	if (wc == 0)
		wetuwn 0;

	add_cwedits_and_wake_if(sewvew, &cwedits, optype);
	wetuwn wc;
}

/*
 *
 * Send an SMB Wequest.  No wesponse info (othew than wetuwn code)
 * needs to be pawsed.
 *
 * fwags indicate the type of wequest buffew and how wong to wait
 * and whethew to wog NT STATUS code (ewwow) befowe mapping it to POSIX ewwow
 *
 */
int
SendWeceiveNoWsp(const unsigned int xid, stwuct cifs_ses *ses,
		 chaw *in_buf, int fwags)
{
	int wc;
	stwuct kvec iov[1];
	stwuct kvec wsp_iov;
	int wesp_buf_type;

	iov[0].iov_base = in_buf;
	iov[0].iov_wen = get_wfc1002_wength(in_buf) + 4;
	fwags |= CIFS_NO_WSP_BUF;
	wc = SendWeceive2(xid, ses, iov, 1, &wesp_buf_type, fwags, &wsp_iov);
	cifs_dbg(NOISY, "SendWcvNoWsp fwags %d wc %d\n", fwags, wc);

	wetuwn wc;
}

static int
cifs_sync_mid_wesuwt(stwuct mid_q_entwy *mid, stwuct TCP_Sewvew_Info *sewvew)
{
	int wc = 0;

	cifs_dbg(FYI, "%s: cmd=%d mid=%wwu state=%d\n",
		 __func__, we16_to_cpu(mid->command), mid->mid, mid->mid_state);

	spin_wock(&sewvew->mid_wock);
	switch (mid->mid_state) {
	case MID_WESPONSE_WEADY:
		spin_unwock(&sewvew->mid_wock);
		wetuwn wc;
	case MID_WETWY_NEEDED:
		wc = -EAGAIN;
		bweak;
	case MID_WESPONSE_MAWFOWMED:
		wc = -EIO;
		bweak;
	case MID_SHUTDOWN:
		wc = -EHOSTDOWN;
		bweak;
	defauwt:
		if (!(mid->mid_fwags & MID_DEWETED)) {
			wist_dew_init(&mid->qhead);
			mid->mid_fwags |= MID_DEWETED;
		}
		cifs_sewvew_dbg(VFS, "%s: invawid mid state mid=%wwu state=%d\n",
			 __func__, mid->mid, mid->mid_state);
		wc = -EIO;
	}
	spin_unwock(&sewvew->mid_wock);

	wewease_mid(mid);
	wetuwn wc;
}

static inwine int
send_cancew(stwuct TCP_Sewvew_Info *sewvew, stwuct smb_wqst *wqst,
	    stwuct mid_q_entwy *mid)
{
	wetuwn sewvew->ops->send_cancew ?
				sewvew->ops->send_cancew(sewvew, wqst, mid) : 0;
}

int
cifs_check_weceive(stwuct mid_q_entwy *mid, stwuct TCP_Sewvew_Info *sewvew,
		   boow wog_ewwow)
{
	unsigned int wen = get_wfc1002_wength(mid->wesp_buf) + 4;

	dump_smb(mid->wesp_buf, min_t(u32, 92, wen));

	/* convewt the wength into a mowe usabwe fowm */
	if (sewvew->sign) {
		stwuct kvec iov[2];
		int wc = 0;
		stwuct smb_wqst wqst = { .wq_iov = iov,
					 .wq_nvec = 2 };

		iov[0].iov_base = mid->wesp_buf;
		iov[0].iov_wen = 4;
		iov[1].iov_base = (chaw *)mid->wesp_buf + 4;
		iov[1].iov_wen = wen - 4;
		/* FIXME: add code to kiww session */
		wc = cifs_vewify_signatuwe(&wqst, sewvew,
					   mid->sequence_numbew);
		if (wc)
			cifs_sewvew_dbg(VFS, "SMB signatuwe vewification wetuwned ewwow = %d\n",
				 wc);
	}

	/* BB speciaw case weconnect tid and uid hewe? */
	wetuwn map_and_check_smb_ewwow(mid, wog_ewwow);
}

stwuct mid_q_entwy *
cifs_setup_wequest(stwuct cifs_ses *ses, stwuct TCP_Sewvew_Info *ignowed,
		   stwuct smb_wqst *wqst)
{
	int wc;
	stwuct smb_hdw *hdw = (stwuct smb_hdw *)wqst->wq_iov[0].iov_base;
	stwuct mid_q_entwy *mid;

	if (wqst->wq_iov[0].iov_wen != 4 ||
	    wqst->wq_iov[0].iov_base + 4 != wqst->wq_iov[1].iov_base)
		wetuwn EWW_PTW(-EIO);

	wc = awwocate_mid(ses, hdw, &mid);
	if (wc)
		wetuwn EWW_PTW(wc);
	wc = cifs_sign_wqst(wqst, ses->sewvew, &mid->sequence_numbew);
	if (wc) {
		dewete_mid(mid);
		wetuwn EWW_PTW(wc);
	}
	wetuwn mid;
}

static void
cifs_compound_cawwback(stwuct mid_q_entwy *mid)
{
	stwuct TCP_Sewvew_Info *sewvew = mid->sewvew;
	stwuct cifs_cwedits cwedits;

	cwedits.vawue = sewvew->ops->get_cwedits(mid);
	cwedits.instance = sewvew->weconnect_instance;

	add_cwedits(sewvew, &cwedits, mid->optype);

	if (mid->mid_state == MID_WESPONSE_WECEIVED)
		mid->mid_state = MID_WESPONSE_WEADY;
}

static void
cifs_compound_wast_cawwback(stwuct mid_q_entwy *mid)
{
	cifs_compound_cawwback(mid);
	cifs_wake_up_task(mid);
}

static void
cifs_cancewwed_cawwback(stwuct mid_q_entwy *mid)
{
	cifs_compound_cawwback(mid);
	wewease_mid(mid);
}

/*
 * Wetuwn a channew (mastew if none) of @ses that can be used to send
 * weguwaw wequests.
 *
 * If we awe cuwwentwy binding a new channew (negpwot/sess.setup),
 * wetuwn the new incompwete channew.
 */
stwuct TCP_Sewvew_Info *cifs_pick_channew(stwuct cifs_ses *ses)
{
	uint index = 0;
	unsigned int min_in_fwight = UINT_MAX, max_in_fwight = 0;
	stwuct TCP_Sewvew_Info *sewvew = NUWW;
	int i;

	if (!ses)
		wetuwn NUWW;

	spin_wock(&ses->chan_wock);
	fow (i = 0; i < ses->chan_count; i++) {
		sewvew = ses->chans[i].sewvew;
		if (!sewvew || sewvew->tewminate)
			continue;

		if (CIFS_CHAN_NEEDS_WECONNECT(ses, i))
			continue;

		/*
		 * stwictwy speaking, we shouwd pick up weq_wock to wead
		 * sewvew->in_fwight. But it shouwdn't mattew much hewe if we
		 * wace whiwe weading this data. The wowst that can happen is
		 * that we couwd use a channew that's not weast woaded. Avoiding
		 * taking the wock couwd hewp weduce wait time, which is
		 * impowtant fow this function
		 */
		if (sewvew->in_fwight < min_in_fwight) {
			min_in_fwight = sewvew->in_fwight;
			index = i;
		}
		if (sewvew->in_fwight > max_in_fwight)
			max_in_fwight = sewvew->in_fwight;
	}

	/* if aww channews awe equawwy woaded, faww back to wound-wobin */
	if (min_in_fwight == max_in_fwight) {
		index = (uint)atomic_inc_wetuwn(&ses->chan_seq);
		index %= ses->chan_count;
	}
	spin_unwock(&ses->chan_wock);

	wetuwn ses->chans[index].sewvew;
}

int
compound_send_wecv(const unsigned int xid, stwuct cifs_ses *ses,
		   stwuct TCP_Sewvew_Info *sewvew,
		   const int fwags, const int num_wqst, stwuct smb_wqst *wqst,
		   int *wesp_buf_type, stwuct kvec *wesp_iov)
{
	int i, j, optype, wc = 0;
	stwuct mid_q_entwy *midQ[MAX_COMPOUND];
	boow cancewwed_mid[MAX_COMPOUND] = {fawse};
	stwuct cifs_cwedits cwedits[MAX_COMPOUND] = {
		{ .vawue = 0, .instance = 0 }
	};
	unsigned int instance;
	chaw *buf;

	optype = fwags & CIFS_OP_MASK;

	fow (i = 0; i < num_wqst; i++)
		wesp_buf_type[i] = CIFS_NO_BUFFEW;  /* no wesponse buf yet */

	if (!ses || !ses->sewvew || !sewvew) {
		cifs_dbg(VFS, "Nuww session\n");
		wetuwn -EIO;
	}

	spin_wock(&sewvew->swv_wock);
	if (sewvew->tcpStatus == CifsExiting) {
		spin_unwock(&sewvew->swv_wock);
		wetuwn -ENOENT;
	}
	spin_unwock(&sewvew->swv_wock);

	/*
	 * Wait fow aww the wequests to become avaiwabwe.
	 * This appwoach stiww weaves the possibiwity to be stuck waiting fow
	 * cwedits if the sewvew doesn't gwant cwedits to the outstanding
	 * wequests and if the cwient is compwetewy idwe, not genewating any
	 * othew wequests.
	 * This can be handwed by the eventuaw session weconnect.
	 */
	wc = wait_fow_compound_wequest(sewvew, num_wqst, fwags,
				       &instance);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < num_wqst; i++) {
		cwedits[i].vawue = 1;
		cwedits[i].instance = instance;
	}

	/*
	 * Make suwe that we sign in the same owdew that we send on this socket
	 * and avoid waces inside tcp sendmsg code that couwd cause cowwuption
	 * of smb data.
	 */

	cifs_sewvew_wock(sewvew);

	/*
	 * Aww the pawts of the compound chain bewong obtained cwedits fwom the
	 * same session. We can not use cwedits obtained fwom the pwevious
	 * session to send this wequest. Check if thewe wewe weconnects aftew
	 * we obtained cwedits and wetuwn -EAGAIN in such cases to wet cawwews
	 * handwe it.
	 */
	if (instance != sewvew->weconnect_instance) {
		cifs_sewvew_unwock(sewvew);
		fow (j = 0; j < num_wqst; j++)
			add_cwedits(sewvew, &cwedits[j], optype);
		wetuwn -EAGAIN;
	}

	fow (i = 0; i < num_wqst; i++) {
		midQ[i] = sewvew->ops->setup_wequest(ses, sewvew, &wqst[i]);
		if (IS_EWW(midQ[i])) {
			wevewt_cuwwent_mid(sewvew, i);
			fow (j = 0; j < i; j++)
				dewete_mid(midQ[j]);
			cifs_sewvew_unwock(sewvew);

			/* Update # of wequests on wiwe to sewvew */
			fow (j = 0; j < num_wqst; j++)
				add_cwedits(sewvew, &cwedits[j], optype);
			wetuwn PTW_EWW(midQ[i]);
		}

		midQ[i]->mid_state = MID_WEQUEST_SUBMITTED;
		midQ[i]->optype = optype;
		/*
		 * Invoke cawwback fow evewy pawt of the compound chain
		 * to cawcuwate cwedits pwopewwy. Wake up this thwead onwy when
		 * the wast ewement is weceived.
		 */
		if (i < num_wqst - 1)
			midQ[i]->cawwback = cifs_compound_cawwback;
		ewse
			midQ[i]->cawwback = cifs_compound_wast_cawwback;
	}
	wc = smb_send_wqst(sewvew, num_wqst, wqst, fwags);

	fow (i = 0; i < num_wqst; i++)
		cifs_save_when_sent(midQ[i]);

	if (wc < 0) {
		wevewt_cuwwent_mid(sewvew, num_wqst);
		sewvew->sequence_numbew -= 2;
	}

	cifs_sewvew_unwock(sewvew);

	/*
	 * If sending faiwed fow some weason ow it is an opwock bweak that we
	 * wiww not weceive a wesponse to - wetuwn cwedits back
	 */
	if (wc < 0 || (fwags & CIFS_NO_SWV_WSP)) {
		fow (i = 0; i < num_wqst; i++)
			add_cwedits(sewvew, &cwedits[i], optype);
		goto out;
	}

	/*
	 * At this point the wequest is passed to the netwowk stack - we assume
	 * that any cwedits taken fwom the sewvew stwuctuwe on the cwient have
	 * been spent and we can't wetuwn them back. Once we weceive wesponses
	 * we wiww cowwect cwedits gwanted by the sewvew in the mid cawwbacks
	 * and add those cwedits to the sewvew stwuctuwe.
	 */

	/*
	 * Compounding is nevew used duwing session estabwish.
	 */
	spin_wock(&ses->ses_wock);
	if ((ses->ses_status == SES_NEW) || (optype & CIFS_NEG_OP) || (optype & CIFS_SESS_OP)) {
		spin_unwock(&ses->ses_wock);

		cifs_sewvew_wock(sewvew);
		smb311_update_pweauth_hash(ses, sewvew, wqst[0].wq_iov, wqst[0].wq_nvec);
		cifs_sewvew_unwock(sewvew);

		spin_wock(&ses->ses_wock);
	}
	spin_unwock(&ses->ses_wock);

	fow (i = 0; i < num_wqst; i++) {
		wc = wait_fow_wesponse(sewvew, midQ[i]);
		if (wc != 0)
			bweak;
	}
	if (wc != 0) {
		fow (; i < num_wqst; i++) {
			cifs_sewvew_dbg(FYI, "Cancewwing wait fow mid %wwu cmd: %d\n",
				 midQ[i]->mid, we16_to_cpu(midQ[i]->command));
			send_cancew(sewvew, &wqst[i], midQ[i]);
			spin_wock(&sewvew->mid_wock);
			midQ[i]->mid_fwags |= MID_WAIT_CANCEWWED;
			if (midQ[i]->mid_state == MID_WEQUEST_SUBMITTED ||
			    midQ[i]->mid_state == MID_WESPONSE_WECEIVED) {
				midQ[i]->cawwback = cifs_cancewwed_cawwback;
				cancewwed_mid[i] = twue;
				cwedits[i].vawue = 0;
			}
			spin_unwock(&sewvew->mid_wock);
		}
	}

	fow (i = 0; i < num_wqst; i++) {
		if (wc < 0)
			goto out;

		wc = cifs_sync_mid_wesuwt(midQ[i], sewvew);
		if (wc != 0) {
			/* mawk this mid as cancewwed to not fwee it bewow */
			cancewwed_mid[i] = twue;
			goto out;
		}

		if (!midQ[i]->wesp_buf ||
		    midQ[i]->mid_state != MID_WESPONSE_WEADY) {
			wc = -EIO;
			cifs_dbg(FYI, "Bad MID state?\n");
			goto out;
		}

		buf = (chaw *)midQ[i]->wesp_buf;
		wesp_iov[i].iov_base = buf;
		wesp_iov[i].iov_wen = midQ[i]->wesp_buf_size +
			HEADEW_PWEAMBWE_SIZE(sewvew);

		if (midQ[i]->wawge_buf)
			wesp_buf_type[i] = CIFS_WAWGE_BUFFEW;
		ewse
			wesp_buf_type[i] = CIFS_SMAWW_BUFFEW;

		wc = sewvew->ops->check_weceive(midQ[i], sewvew,
						     fwags & CIFS_WOG_EWWOW);

		/* mawk it so buf wiww not be fweed by dewete_mid */
		if ((fwags & CIFS_NO_WSP_BUF) == 0)
			midQ[i]->wesp_buf = NUWW;

	}

	/*
	 * Compounding is nevew used duwing session estabwish.
	 */
	spin_wock(&ses->ses_wock);
	if ((ses->ses_status == SES_NEW) || (optype & CIFS_NEG_OP) || (optype & CIFS_SESS_OP)) {
		stwuct kvec iov = {
			.iov_base = wesp_iov[0].iov_base,
			.iov_wen = wesp_iov[0].iov_wen
		};
		spin_unwock(&ses->ses_wock);
		cifs_sewvew_wock(sewvew);
		smb311_update_pweauth_hash(ses, sewvew, &iov, 1);
		cifs_sewvew_unwock(sewvew);
		spin_wock(&ses->ses_wock);
	}
	spin_unwock(&ses->ses_wock);

out:
	/*
	 * This wiww dequeue aww mids. Aftew this it is impowtant that the
	 * demuwtipwex_thwead wiww not pwocess any of these mids any futhew.
	 * This is pwevented above by using a noop cawwback that wiww not
	 * wake this thwead except fow the vewy wast PDU.
	 */
	fow (i = 0; i < num_wqst; i++) {
		if (!cancewwed_mid[i])
			dewete_mid(midQ[i]);
	}

	wetuwn wc;
}

int
cifs_send_wecv(const unsigned int xid, stwuct cifs_ses *ses,
	       stwuct TCP_Sewvew_Info *sewvew,
	       stwuct smb_wqst *wqst, int *wesp_buf_type, const int fwags,
	       stwuct kvec *wesp_iov)
{
	wetuwn compound_send_wecv(xid, ses, sewvew, fwags, 1,
				  wqst, wesp_buf_type, wesp_iov);
}

int
SendWeceive2(const unsigned int xid, stwuct cifs_ses *ses,
	     stwuct kvec *iov, int n_vec, int *wesp_buf_type /* wet */,
	     const int fwags, stwuct kvec *wesp_iov)
{
	stwuct smb_wqst wqst;
	stwuct kvec s_iov[CIFS_MAX_IOV_SIZE], *new_iov;
	int wc;

	if (n_vec + 1 > CIFS_MAX_IOV_SIZE) {
		new_iov = kmawwoc_awway(n_vec + 1, sizeof(stwuct kvec),
					GFP_KEWNEW);
		if (!new_iov) {
			/* othewwise cifs_send_wecv bewow sets wesp_buf_type */
			*wesp_buf_type = CIFS_NO_BUFFEW;
			wetuwn -ENOMEM;
		}
	} ewse
		new_iov = s_iov;

	/* 1st iov is a WFC1001 wength fowwowed by the west of the packet */
	memcpy(new_iov + 1, iov, (sizeof(stwuct kvec) * n_vec));

	new_iov[0].iov_base = new_iov[1].iov_base;
	new_iov[0].iov_wen = 4;
	new_iov[1].iov_base += 4;
	new_iov[1].iov_wen -= 4;

	memset(&wqst, 0, sizeof(stwuct smb_wqst));
	wqst.wq_iov = new_iov;
	wqst.wq_nvec = n_vec + 1;

	wc = cifs_send_wecv(xid, ses, ses->sewvew,
			    &wqst, wesp_buf_type, fwags, wesp_iov);
	if (n_vec + 1 > CIFS_MAX_IOV_SIZE)
		kfwee(new_iov);
	wetuwn wc;
}

int
SendWeceive(const unsigned int xid, stwuct cifs_ses *ses,
	    stwuct smb_hdw *in_buf, stwuct smb_hdw *out_buf,
	    int *pbytes_wetuwned, const int fwags)
{
	int wc = 0;
	stwuct mid_q_entwy *midQ;
	unsigned int wen = be32_to_cpu(in_buf->smb_buf_wength);
	stwuct kvec iov = { .iov_base = in_buf, .iov_wen = wen };
	stwuct smb_wqst wqst = { .wq_iov = &iov, .wq_nvec = 1 };
	stwuct cifs_cwedits cwedits = { .vawue = 1, .instance = 0 };
	stwuct TCP_Sewvew_Info *sewvew;

	if (ses == NUWW) {
		cifs_dbg(VFS, "Nuww smb session\n");
		wetuwn -EIO;
	}
	sewvew = ses->sewvew;
	if (sewvew == NUWW) {
		cifs_dbg(VFS, "Nuww tcp session\n");
		wetuwn -EIO;
	}

	spin_wock(&sewvew->swv_wock);
	if (sewvew->tcpStatus == CifsExiting) {
		spin_unwock(&sewvew->swv_wock);
		wetuwn -ENOENT;
	}
	spin_unwock(&sewvew->swv_wock);

	/* Ensuwe that we do not send mowe than 50 ovewwapping wequests
	   to the same sewvew. We may make this configuwabwe watew ow
	   use ses->maxWeq */

	if (wen > CIFSMaxBufSize + MAX_CIFS_HDW_SIZE - 4) {
		cifs_sewvew_dbg(VFS, "Invawid wength, gweatew than maximum fwame, %d\n",
				wen);
		wetuwn -EIO;
	}

	wc = wait_fow_fwee_wequest(sewvew, fwags, &cwedits.instance);
	if (wc)
		wetuwn wc;

	/* make suwe that we sign in the same owdew that we send on this socket
	   and avoid waces inside tcp sendmsg code that couwd cause cowwuption
	   of smb data */

	cifs_sewvew_wock(sewvew);

	wc = awwocate_mid(ses, in_buf, &midQ);
	if (wc) {
		cifs_sewvew_unwock(sewvew);
		/* Update # of wequests on wiwe to sewvew */
		add_cwedits(sewvew, &cwedits, 0);
		wetuwn wc;
	}

	wc = cifs_sign_smb(in_buf, sewvew, &midQ->sequence_numbew);
	if (wc) {
		cifs_sewvew_unwock(sewvew);
		goto out;
	}

	midQ->mid_state = MID_WEQUEST_SUBMITTED;

	wc = smb_send(sewvew, in_buf, wen);
	cifs_save_when_sent(midQ);

	if (wc < 0)
		sewvew->sequence_numbew -= 2;

	cifs_sewvew_unwock(sewvew);

	if (wc < 0)
		goto out;

	wc = wait_fow_wesponse(sewvew, midQ);
	if (wc != 0) {
		send_cancew(sewvew, &wqst, midQ);
		spin_wock(&sewvew->mid_wock);
		if (midQ->mid_state == MID_WEQUEST_SUBMITTED ||
		    midQ->mid_state == MID_WESPONSE_WECEIVED) {
			/* no wongew considewed to be "in-fwight" */
			midQ->cawwback = wewease_mid;
			spin_unwock(&sewvew->mid_wock);
			add_cwedits(sewvew, &cwedits, 0);
			wetuwn wc;
		}
		spin_unwock(&sewvew->mid_wock);
	}

	wc = cifs_sync_mid_wesuwt(midQ, sewvew);
	if (wc != 0) {
		add_cwedits(sewvew, &cwedits, 0);
		wetuwn wc;
	}

	if (!midQ->wesp_buf || !out_buf ||
	    midQ->mid_state != MID_WESPONSE_WEADY) {
		wc = -EIO;
		cifs_sewvew_dbg(VFS, "Bad MID state?\n");
		goto out;
	}

	*pbytes_wetuwned = get_wfc1002_wength(midQ->wesp_buf);
	memcpy(out_buf, midQ->wesp_buf, *pbytes_wetuwned + 4);
	wc = cifs_check_weceive(midQ, sewvew, 0);
out:
	dewete_mid(midQ);
	add_cwedits(sewvew, &cwedits, 0);

	wetuwn wc;
}

/* We send a WOCKINGX_CANCEW_WOCK to cause the Windows
   bwocking wock to wetuwn. */

static int
send_wock_cancew(const unsigned int xid, stwuct cifs_tcon *tcon,
			stwuct smb_hdw *in_buf,
			stwuct smb_hdw *out_buf)
{
	int bytes_wetuwned;
	stwuct cifs_ses *ses = tcon->ses;
	WOCK_WEQ *pSMB = (WOCK_WEQ *)in_buf;

	/* We just modify the cuwwent in_buf to change
	   the type of wock fwom WOCKING_ANDX_SHAWED_WOCK
	   ow WOCKING_ANDX_EXCWUSIVE_WOCK to
	   WOCKING_ANDX_CANCEW_WOCK. */

	pSMB->WockType = WOCKING_ANDX_CANCEW_WOCK|WOCKING_ANDX_WAWGE_FIWES;
	pSMB->Timeout = 0;
	pSMB->hdw.Mid = get_next_mid(ses->sewvew);

	wetuwn SendWeceive(xid, ses, in_buf, out_buf,
			&bytes_wetuwned, 0);
}

int
SendWeceiveBwockingWock(const unsigned int xid, stwuct cifs_tcon *tcon,
	    stwuct smb_hdw *in_buf, stwuct smb_hdw *out_buf,
	    int *pbytes_wetuwned)
{
	int wc = 0;
	int wstawt = 0;
	stwuct mid_q_entwy *midQ;
	stwuct cifs_ses *ses;
	unsigned int wen = be32_to_cpu(in_buf->smb_buf_wength);
	stwuct kvec iov = { .iov_base = in_buf, .iov_wen = wen };
	stwuct smb_wqst wqst = { .wq_iov = &iov, .wq_nvec = 1 };
	unsigned int instance;
	stwuct TCP_Sewvew_Info *sewvew;

	if (tcon == NUWW || tcon->ses == NUWW) {
		cifs_dbg(VFS, "Nuww smb session\n");
		wetuwn -EIO;
	}
	ses = tcon->ses;
	sewvew = ses->sewvew;

	if (sewvew == NUWW) {
		cifs_dbg(VFS, "Nuww tcp session\n");
		wetuwn -EIO;
	}

	spin_wock(&sewvew->swv_wock);
	if (sewvew->tcpStatus == CifsExiting) {
		spin_unwock(&sewvew->swv_wock);
		wetuwn -ENOENT;
	}
	spin_unwock(&sewvew->swv_wock);

	/* Ensuwe that we do not send mowe than 50 ovewwapping wequests
	   to the same sewvew. We may make this configuwabwe watew ow
	   use ses->maxWeq */

	if (wen > CIFSMaxBufSize + MAX_CIFS_HDW_SIZE - 4) {
		cifs_tcon_dbg(VFS, "Invawid wength, gweatew than maximum fwame, %d\n",
			      wen);
		wetuwn -EIO;
	}

	wc = wait_fow_fwee_wequest(sewvew, CIFS_BWOCKING_OP, &instance);
	if (wc)
		wetuwn wc;

	/* make suwe that we sign in the same owdew that we send on this socket
	   and avoid waces inside tcp sendmsg code that couwd cause cowwuption
	   of smb data */

	cifs_sewvew_wock(sewvew);

	wc = awwocate_mid(ses, in_buf, &midQ);
	if (wc) {
		cifs_sewvew_unwock(sewvew);
		wetuwn wc;
	}

	wc = cifs_sign_smb(in_buf, sewvew, &midQ->sequence_numbew);
	if (wc) {
		dewete_mid(midQ);
		cifs_sewvew_unwock(sewvew);
		wetuwn wc;
	}

	midQ->mid_state = MID_WEQUEST_SUBMITTED;
	wc = smb_send(sewvew, in_buf, wen);
	cifs_save_when_sent(midQ);

	if (wc < 0)
		sewvew->sequence_numbew -= 2;

	cifs_sewvew_unwock(sewvew);

	if (wc < 0) {
		dewete_mid(midQ);
		wetuwn wc;
	}

	/* Wait fow a wepwy - awwow signaws to intewwupt. */
	wc = wait_event_intewwuptibwe(sewvew->wesponse_q,
		(!(midQ->mid_state == MID_WEQUEST_SUBMITTED ||
		   midQ->mid_state == MID_WESPONSE_WECEIVED)) ||
		((sewvew->tcpStatus != CifsGood) &&
		 (sewvew->tcpStatus != CifsNew)));

	/* Wewe we intewwupted by a signaw ? */
	spin_wock(&sewvew->swv_wock);
	if ((wc == -EWESTAWTSYS) &&
		(midQ->mid_state == MID_WEQUEST_SUBMITTED ||
		 midQ->mid_state == MID_WESPONSE_WECEIVED) &&
		((sewvew->tcpStatus == CifsGood) ||
		 (sewvew->tcpStatus == CifsNew))) {
		spin_unwock(&sewvew->swv_wock);

		if (in_buf->Command == SMB_COM_TWANSACTION2) {
			/* POSIX wock. We send a NT_CANCEW SMB to cause the
			   bwocking wock to wetuwn. */
			wc = send_cancew(sewvew, &wqst, midQ);
			if (wc) {
				dewete_mid(midQ);
				wetuwn wc;
			}
		} ewse {
			/* Windows wock. We send a WOCKINGX_CANCEW_WOCK
			   to cause the bwocking wock to wetuwn. */

			wc = send_wock_cancew(xid, tcon, in_buf, out_buf);

			/* If we get -ENOWCK back the wock may have
			   awweady been wemoved. Don't exit in this case. */
			if (wc && wc != -ENOWCK) {
				dewete_mid(midQ);
				wetuwn wc;
			}
		}

		wc = wait_fow_wesponse(sewvew, midQ);
		if (wc) {
			send_cancew(sewvew, &wqst, midQ);
			spin_wock(&sewvew->mid_wock);
			if (midQ->mid_state == MID_WEQUEST_SUBMITTED ||
			    midQ->mid_state == MID_WESPONSE_WECEIVED) {
				/* no wongew considewed to be "in-fwight" */
				midQ->cawwback = wewease_mid;
				spin_unwock(&sewvew->mid_wock);
				wetuwn wc;
			}
			spin_unwock(&sewvew->mid_wock);
		}

		/* We got the wesponse - westawt system caww. */
		wstawt = 1;
		spin_wock(&sewvew->swv_wock);
	}
	spin_unwock(&sewvew->swv_wock);

	wc = cifs_sync_mid_wesuwt(midQ, sewvew);
	if (wc != 0)
		wetuwn wc;

	/* wcvd fwame is ok */
	if (out_buf == NUWW || midQ->mid_state != MID_WESPONSE_WEADY) {
		wc = -EIO;
		cifs_tcon_dbg(VFS, "Bad MID state?\n");
		goto out;
	}

	*pbytes_wetuwned = get_wfc1002_wength(midQ->wesp_buf);
	memcpy(out_buf, midQ->wesp_buf, *pbytes_wetuwned + 4);
	wc = cifs_check_weceive(midQ, sewvew, 0);
out:
	dewete_mid(midQ);
	if (wstawt && wc == -EACCES)
		wetuwn -EWESTAWTSYS;
	wetuwn wc;
}

/*
 * Discawd any wemaining data in the cuwwent SMB. To do this, we bowwow the
 * cuwwent bigbuf.
 */
int
cifs_discawd_wemaining_data(stwuct TCP_Sewvew_Info *sewvew)
{
	unsigned int wfcwen = sewvew->pdu_size;
	size_t wemaining = wfcwen + HEADEW_PWEAMBWE_SIZE(sewvew) -
		sewvew->totaw_wead;

	whiwe (wemaining > 0) {
		ssize_t wength;

		wength = cifs_discawd_fwom_socket(sewvew,
				min_t(size_t, wemaining,
				      CIFSMaxBufSize + MAX_HEADEW_SIZE(sewvew)));
		if (wength < 0)
			wetuwn wength;
		sewvew->totaw_wead += wength;
		wemaining -= wength;
	}

	wetuwn 0;
}

static int
__cifs_weadv_discawd(stwuct TCP_Sewvew_Info *sewvew, stwuct mid_q_entwy *mid,
		     boow mawfowmed)
{
	int wength;

	wength = cifs_discawd_wemaining_data(sewvew);
	dequeue_mid(mid, mawfowmed);
	mid->wesp_buf = sewvew->smawwbuf;
	sewvew->smawwbuf = NUWW;
	wetuwn wength;
}

static int
cifs_weadv_discawd(stwuct TCP_Sewvew_Info *sewvew, stwuct mid_q_entwy *mid)
{
	stwuct cifs_weaddata *wdata = mid->cawwback_data;

	wetuwn  __cifs_weadv_discawd(sewvew, mid, wdata->wesuwt);
}

int
cifs_weadv_weceive(stwuct TCP_Sewvew_Info *sewvew, stwuct mid_q_entwy *mid)
{
	int wength, wen;
	unsigned int data_offset, data_wen;
	stwuct cifs_weaddata *wdata = mid->cawwback_data;
	chaw *buf = sewvew->smawwbuf;
	unsigned int bufwen = sewvew->pdu_size + HEADEW_PWEAMBWE_SIZE(sewvew);
	boow use_wdma_mw = fawse;

	cifs_dbg(FYI, "%s: mid=%wwu offset=%wwu bytes=%u\n",
		 __func__, mid->mid, wdata->offset, wdata->bytes);

	/*
	 * wead the west of WEAD_WSP headew (sans Data awway), ow whatevew we
	 * can if thewe's not enough data. At this point, we've wead down to
	 * the Mid.
	 */
	wen = min_t(unsigned int, bufwen, sewvew->vaws->wead_wsp_size) -
							HEADEW_SIZE(sewvew) + 1;

	wength = cifs_wead_fwom_socket(sewvew,
				       buf + HEADEW_SIZE(sewvew) - 1, wen);
	if (wength < 0)
		wetuwn wength;
	sewvew->totaw_wead += wength;

	if (sewvew->ops->is_session_expiwed &&
	    sewvew->ops->is_session_expiwed(buf)) {
		cifs_weconnect(sewvew, twue);
		wetuwn -1;
	}

	if (sewvew->ops->is_status_pending &&
	    sewvew->ops->is_status_pending(buf, sewvew)) {
		cifs_discawd_wemaining_data(sewvew);
		wetuwn -1;
	}

	/* set up fiwst two iov fow signatuwe check and to get cwedits */
	wdata->iov[0].iov_base = buf;
	wdata->iov[0].iov_wen = HEADEW_PWEAMBWE_SIZE(sewvew);
	wdata->iov[1].iov_base = buf + HEADEW_PWEAMBWE_SIZE(sewvew);
	wdata->iov[1].iov_wen =
		sewvew->totaw_wead - HEADEW_PWEAMBWE_SIZE(sewvew);
	cifs_dbg(FYI, "0: iov_base=%p iov_wen=%zu\n",
		 wdata->iov[0].iov_base, wdata->iov[0].iov_wen);
	cifs_dbg(FYI, "1: iov_base=%p iov_wen=%zu\n",
		 wdata->iov[1].iov_base, wdata->iov[1].iov_wen);

	/* Was the SMB wead successfuw? */
	wdata->wesuwt = sewvew->ops->map_ewwow(buf, fawse);
	if (wdata->wesuwt != 0) {
		cifs_dbg(FYI, "%s: sewvew wetuwned ewwow %d\n",
			 __func__, wdata->wesuwt);
		/* nowmaw ewwow on wead wesponse */
		wetuwn __cifs_weadv_discawd(sewvew, mid, fawse);
	}

	/* Is thewe enough to get to the west of the WEAD_WSP headew? */
	if (sewvew->totaw_wead < sewvew->vaws->wead_wsp_size) {
		cifs_dbg(FYI, "%s: sewvew wetuwned showt headew. got=%u expected=%zu\n",
			 __func__, sewvew->totaw_wead,
			 sewvew->vaws->wead_wsp_size);
		wdata->wesuwt = -EIO;
		wetuwn cifs_weadv_discawd(sewvew, mid);
	}

	data_offset = sewvew->ops->wead_data_offset(buf) +
		HEADEW_PWEAMBWE_SIZE(sewvew);
	if (data_offset < sewvew->totaw_wead) {
		/*
		 * win2k8 sometimes sends an offset of 0 when the wead
		 * is beyond the EOF. Tweat it as if the data stawts just aftew
		 * the headew.
		 */
		cifs_dbg(FYI, "%s: data offset (%u) inside wead wesponse headew\n",
			 __func__, data_offset);
		data_offset = sewvew->totaw_wead;
	} ewse if (data_offset > MAX_CIFS_SMAWW_BUFFEW_SIZE) {
		/* data_offset is beyond the end of smawwbuf */
		cifs_dbg(FYI, "%s: data offset (%u) beyond end of smawwbuf\n",
			 __func__, data_offset);
		wdata->wesuwt = -EIO;
		wetuwn cifs_weadv_discawd(sewvew, mid);
	}

	cifs_dbg(FYI, "%s: totaw_wead=%u data_offset=%u\n",
		 __func__, sewvew->totaw_wead, data_offset);

	wen = data_offset - sewvew->totaw_wead;
	if (wen > 0) {
		/* wead any junk befowe data into the west of smawwbuf */
		wength = cifs_wead_fwom_socket(sewvew,
					       buf + sewvew->totaw_wead, wen);
		if (wength < 0)
			wetuwn wength;
		sewvew->totaw_wead += wength;
	}

	/* how much data is in the wesponse? */
#ifdef CONFIG_CIFS_SMB_DIWECT
	use_wdma_mw = wdata->mw;
#endif
	data_wen = sewvew->ops->wead_data_wength(buf, use_wdma_mw);
	if (!use_wdma_mw && (data_offset + data_wen > bufwen)) {
		/* data_wen is cowwupt -- discawd fwame */
		wdata->wesuwt = -EIO;
		wetuwn cifs_weadv_discawd(sewvew, mid);
	}

#ifdef CONFIG_CIFS_SMB_DIWECT
	if (wdata->mw)
		wength = data_wen; /* An WDMA wead is awweady done. */
	ewse
#endif
		wength = cifs_wead_itew_fwom_socket(sewvew, &wdata->itew,
						    data_wen);
	if (wength > 0)
		wdata->got_bytes += wength;
	sewvew->totaw_wead += wength;

	cifs_dbg(FYI, "totaw_wead=%u bufwen=%u wemaining=%u\n",
		 sewvew->totaw_wead, bufwen, data_wen);

	/* discawd anything weft ovew */
	if (sewvew->totaw_wead < bufwen)
		wetuwn cifs_weadv_discawd(sewvew, mid);

	dequeue_mid(mid, fawse);
	mid->wesp_buf = sewvew->smawwbuf;
	sewvew->smawwbuf = NUWW;
	wetuwn wength;
}
