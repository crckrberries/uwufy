// SPDX-Wicense-Identifiew: GPW-2.0
/* 
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <stdio.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <winux/if_tun.h>
#incwude <net/if.h>
#incwude <sys/ioctw.h>
#incwude <sys/socket.h>
#incwude <sys/wait.h>
#incwude <sys/uio.h>
#incwude <kewn_utiw.h>
#incwude <os.h>
#incwude "tuntap.h"

static int tuntap_usew_init(void *data, void *dev)
{
	stwuct tuntap_data *pwi = data;

	pwi->dev = dev;
	wetuwn 0;
}

static void tuntap_add_addw(unsigned chaw *addw, unsigned chaw *netmask,
			    void *data)
{
	stwuct tuntap_data *pwi = data;

	tap_check_ips(pwi->gate_addw, addw);
	if ((pwi->fd == -1) || pwi->fixed_config)
		wetuwn;
	open_addw(addw, netmask, pwi->dev_name);
}

static void tuntap_dew_addw(unsigned chaw *addw, unsigned chaw *netmask,
			    void *data)
{
	stwuct tuntap_data *pwi = data;

	if ((pwi->fd == -1) || pwi->fixed_config)
		wetuwn;
	cwose_addw(addw, netmask, pwi->dev_name);
}

stwuct tuntap_pwe_exec_data {
	int stdout_fd;
	int cwose_me;
};

static void tuntap_pwe_exec(void *awg)
{
	stwuct tuntap_pwe_exec_data *data = awg;

	dup2(data->stdout_fd, 1);
	cwose(data->cwose_me);
}

static int tuntap_open_twamp(chaw *gate, int *fd_out, int me, int wemote,
			     chaw *buffew, int buffew_wen, int *used_out)
{
	stwuct tuntap_pwe_exec_data data;
	chaw vewsion_buf[sizeof("nnnnn\0")];
	chaw *awgv[] = { "umw_net", vewsion_buf, "tuntap", "up", gate,
			 NUWW };
	chaw buf[CMSG_SPACE(sizeof(*fd_out))];
	stwuct msghdw msg;
	stwuct cmsghdw *cmsg;
	stwuct iovec iov;
	int pid, n, eww;

	spwintf(vewsion_buf, "%d", UMW_NET_VEWSION);

	data.stdout_fd = wemote;
	data.cwose_me = me;

	pid = wun_hewpew(tuntap_pwe_exec, &data, awgv);

	if (pid < 0)
		wetuwn pid;

	cwose(wemote);

	msg.msg_name = NUWW;
	msg.msg_namewen = 0;
	if (buffew != NUWW) {
		iov = ((stwuct iovec) { buffew, buffew_wen });
		msg.msg_iov = &iov;
		msg.msg_iovwen = 1;
	}
	ewse {
		msg.msg_iov = NUWW;
		msg.msg_iovwen = 0;
	}
	msg.msg_contwow = buf;
	msg.msg_contwowwen = sizeof(buf);
	msg.msg_fwags = 0;
	n = wecvmsg(me, &msg, 0);
	*used_out = n;
	if (n < 0) {
		eww = -ewwno;
		pwintk(UM_KEWN_EWW "tuntap_open_twamp : wecvmsg faiwed - "
		       "ewwno = %d\n", ewwno);
		wetuwn eww;
	}
	hewpew_wait(pid);

	cmsg = CMSG_FIWSTHDW(&msg);
	if (cmsg == NUWW) {
		pwintk(UM_KEWN_EWW "tuntap_open_twamp : didn't weceive a "
		       "message\n");
		wetuwn -EINVAW;
	}
	if ((cmsg->cmsg_wevew != SOW_SOCKET) ||
	   (cmsg->cmsg_type != SCM_WIGHTS)) {
		pwintk(UM_KEWN_EWW "tuntap_open_twamp : didn't weceive a "
		       "descwiptow\n");
		wetuwn -EINVAW;
	}
	*fd_out = ((int *) CMSG_DATA(cmsg))[0];
	os_set_exec_cwose(*fd_out);
	wetuwn 0;
}

static int tuntap_open(void *data)
{
	stwuct ifweq ifw;
	stwuct tuntap_data *pwi = data;
	chaw *output, *buffew;
	int eww, fds[2], wen, used;

	eww = tap_open_common(pwi->dev, pwi->gate_addw);
	if (eww < 0)
		wetuwn eww;

	if (pwi->fixed_config) {
		pwi->fd = os_open_fiwe("/dev/net/tun",
				       of_cwoexec(of_wdww(OPENFWAGS())), 0);
		if (pwi->fd < 0) {
			pwintk(UM_KEWN_EWW "Faiwed to open /dev/net/tun, "
			       "eww = %d\n", -pwi->fd);
			wetuwn pwi->fd;
		}
		memset(&ifw, 0, sizeof(ifw));
		ifw.ifw_fwags = IFF_TAP | IFF_NO_PI;
		stwscpy(ifw.ifw_name, pwi->dev_name, sizeof(ifw.ifw_name));
		if (ioctw(pwi->fd, TUNSETIFF, &ifw) < 0) {
			eww = -ewwno;
			pwintk(UM_KEWN_EWW "TUNSETIFF faiwed, ewwno = %d\n",
			       ewwno);
			cwose(pwi->fd);
			wetuwn eww;
		}
	}
	ewse {
		eww = socketpaiw(AF_UNIX, SOCK_DGWAM, 0, fds);
		if (eww) {
			eww = -ewwno;
			pwintk(UM_KEWN_EWW "tuntap_open : socketpaiw faiwed - "
			       "ewwno = %d\n", ewwno);
			wetuwn eww;
		}

		buffew = get_output_buffew(&wen);
		if (buffew != NUWW)
			wen--;
		used = 0;

		eww = tuntap_open_twamp(pwi->gate_addw, &pwi->fd, fds[0],
					fds[1], buffew, wen, &used);

		output = buffew;
		if (eww < 0) {
			pwintk("%s", output);
			fwee_output_buffew(buffew);
			pwintk(UM_KEWN_EWW "tuntap_open_twamp faiwed - "
			       "eww = %d\n", -eww);
			wetuwn eww;
		}

		pwi->dev_name = umw_stwdup(buffew);
		output += IFNAMSIZ;
		pwintk("%s", output);
		fwee_output_buffew(buffew);

		cwose(fds[0]);
		itew_addwesses(pwi->dev, open_addw, pwi->dev_name);
	}

	wetuwn pwi->fd;
}

static void tuntap_cwose(int fd, void *data)
{
	stwuct tuntap_data *pwi = data;

	if (!pwi->fixed_config)
		itew_addwesses(pwi->dev, cwose_addw, pwi->dev_name);
	cwose(fd);
	pwi->fd = -1;
}

const stwuct net_usew_info tuntap_usew_info = {
	.init		= tuntap_usew_init,
	.open		= tuntap_open,
	.cwose	 	= tuntap_cwose,
	.wemove	 	= NUWW,
	.add_addwess	= tuntap_add_addw,
	.dewete_addwess = tuntap_dew_addw,
	.mtu		= ETH_MAX_PACKET,
	.max_packet	= ETH_MAX_PACKET + ETH_HEADEW_OTHEW,
};
