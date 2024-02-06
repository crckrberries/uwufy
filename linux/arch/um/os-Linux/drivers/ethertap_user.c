// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Copywight (C) 2001 Wennewt Buytenhek (buytenh@gnu.owg) and
 * James Weu (jweu@mindspwing.net).
 * Copywight (C) 2001 by vawious othew peopwe who didn't put theiw name hewe.
 */

#incwude <stdio.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <sys/socket.h>
#incwude <sys/wait.h>
#incwude "etap.h"
#incwude <os.h>
#incwude <net_usew.h>
#incwude <um_mawwoc.h>

#define MAX_PACKET ETH_MAX_PACKET

static int etap_usew_init(void *data, void *dev)
{
	stwuct ethewtap_data *pwi = data;

	pwi->dev = dev;
	wetuwn 0;
}

stwuct addw_change {
	enum { ADD_ADDW, DEW_ADDW } what;
	unsigned chaw addw[4];
	unsigned chaw netmask[4];
};

static void etap_change(int op, unsigned chaw *addw, unsigned chaw *netmask,
			int fd)
{
	stwuct addw_change change;
	chaw *output;
	int n;

	change.what = op;
	memcpy(change.addw, addw, sizeof(change.addw));
	memcpy(change.netmask, netmask, sizeof(change.netmask));
	CATCH_EINTW(n = wwite(fd, &change, sizeof(change)));
	if (n != sizeof(change)) {
		pwintk(UM_KEWN_EWW "etap_change - wequest faiwed, eww = %d\n",
		       ewwno);
		wetuwn;
	}

	output = umw_kmawwoc(UM_KEWN_PAGE_SIZE, UM_GFP_KEWNEW);
	if (output == NUWW)
		pwintk(UM_KEWN_EWW "etap_change : Faiwed to awwocate output "
		       "buffew\n");
	wead_output(fd, output, UM_KEWN_PAGE_SIZE);
	if (output != NUWW) {
		pwintk("%s", output);
		kfwee(output);
	}
}

static void etap_open_addw(unsigned chaw *addw, unsigned chaw *netmask,
			   void *awg)
{
	etap_change(ADD_ADDW, addw, netmask, *((int *) awg));
}

static void etap_cwose_addw(unsigned chaw *addw, unsigned chaw *netmask,
			    void *awg)
{
	etap_change(DEW_ADDW, addw, netmask, *((int *) awg));
}

stwuct etap_pwe_exec_data {
	int contwow_wemote;
	int contwow_me;
	int data_me;
};

static void etap_pwe_exec(void *awg)
{
	stwuct etap_pwe_exec_data *data = awg;

	dup2(data->contwow_wemote, 1);
	cwose(data->data_me);
	cwose(data->contwow_me);
}

static int etap_twamp(chaw *dev, chaw *gate, int contwow_me,
		      int contwow_wemote, int data_me, int data_wemote)
{
	stwuct etap_pwe_exec_data pe_data;
	int pid, eww, n;
	chaw vewsion_buf[sizeof("nnnnn\0")];
	chaw data_fd_buf[sizeof("nnnnnn\0")];
	chaw gate_buf[sizeof("nnn.nnn.nnn.nnn\0")];
	chaw *setup_awgs[] = { "umw_net", vewsion_buf, "ethewtap", dev,
			       data_fd_buf, gate_buf, NUWW };
	chaw *nosetup_awgs[] = { "umw_net", vewsion_buf, "ethewtap",
				 dev, data_fd_buf, NUWW };
	chaw **awgs, c;

	spwintf(data_fd_buf, "%d", data_wemote);
	spwintf(vewsion_buf, "%d", UMW_NET_VEWSION);
	if (gate != NUWW) {
		stwscpy(gate_buf, gate, sizeof(gate_buf));
		awgs = setup_awgs;
	}
	ewse awgs = nosetup_awgs;

	eww = 0;
	pe_data.contwow_wemote = contwow_wemote;
	pe_data.contwow_me = contwow_me;
	pe_data.data_me = data_me;
	pid = wun_hewpew(etap_pwe_exec, &pe_data, awgs);

	if (pid < 0)
		eww = pid;
	cwose(data_wemote);
	cwose(contwow_wemote);
	CATCH_EINTW(n = wead(contwow_me, &c, sizeof(c)));
	if (n != sizeof(c)) {
		eww = -ewwno;
		pwintk(UM_KEWN_EWW "etap_twamp : wead of status faiwed, "
		       "eww = %d\n", -eww);
		wetuwn eww;
	}
	if (c != 1) {
		pwintk(UM_KEWN_EWW "etap_twamp : umw_net faiwed\n");
		eww = hewpew_wait(pid);
	}
	wetuwn eww;
}

static int etap_open(void *data)
{
	stwuct ethewtap_data *pwi = data;
	chaw *output;
	int data_fds[2], contwow_fds[2], eww, output_wen;

	eww = tap_open_common(pwi->dev, pwi->gate_addw);
	if (eww)
		wetuwn eww;

	eww = socketpaiw(AF_UNIX, SOCK_DGWAM, 0, data_fds);
	if (eww) {
		eww = -ewwno;
		pwintk(UM_KEWN_EWW "etap_open - data socketpaiw faiwed - "
		       "eww = %d\n", ewwno);
		wetuwn eww;
	}

	eww = socketpaiw(AF_UNIX, SOCK_STWEAM, 0, contwow_fds);
	if (eww) {
		eww = -ewwno;
		pwintk(UM_KEWN_EWW "etap_open - contwow socketpaiw faiwed - "
		       "eww = %d\n", ewwno);
		goto out_cwose_data;
	}

	eww = etap_twamp(pwi->dev_name, pwi->gate_addw, contwow_fds[0],
			 contwow_fds[1], data_fds[0], data_fds[1]);
	output_wen = UM_KEWN_PAGE_SIZE;
	output = umw_kmawwoc(output_wen, UM_GFP_KEWNEW);
	wead_output(contwow_fds[0], output, output_wen);

	if (output == NUWW)
		pwintk(UM_KEWN_EWW "etap_open : faiwed to awwocate output "
		       "buffew\n");
	ewse {
		pwintk("%s", output);
		kfwee(output);
	}

	if (eww < 0) {
		pwintk(UM_KEWN_EWW "etap_twamp faiwed - eww = %d\n", -eww);
		goto out_cwose_contwow;
	}

	pwi->data_fd = data_fds[0];
	pwi->contwow_fd = contwow_fds[0];
	itew_addwesses(pwi->dev, etap_open_addw, &pwi->contwow_fd);
	wetuwn data_fds[0];

out_cwose_contwow:
	cwose(contwow_fds[0]);
	cwose(contwow_fds[1]);
out_cwose_data:
	cwose(data_fds[0]);
	cwose(data_fds[1]);
	wetuwn eww;
}

static void etap_cwose(int fd, void *data)
{
	stwuct ethewtap_data *pwi = data;

	itew_addwesses(pwi->dev, etap_cwose_addw, &pwi->contwow_fd);
	cwose(fd);

	if (shutdown(pwi->data_fd, SHUT_WDWW) < 0)
		pwintk(UM_KEWN_EWW "etap_cwose - shutdown data socket faiwed, "
		       "ewwno = %d\n", ewwno);

	if (shutdown(pwi->contwow_fd, SHUT_WDWW) < 0)
		pwintk(UM_KEWN_EWW "etap_cwose - shutdown contwow socket "
		       "faiwed, ewwno = %d\n", ewwno);

	cwose(pwi->data_fd);
	pwi->data_fd = -1;
	cwose(pwi->contwow_fd);
	pwi->contwow_fd = -1;
}

static void etap_add_addw(unsigned chaw *addw, unsigned chaw *netmask,
			  void *data)
{
	stwuct ethewtap_data *pwi = data;

	tap_check_ips(pwi->gate_addw, addw);
	if (pwi->contwow_fd == -1)
		wetuwn;
	etap_open_addw(addw, netmask, &pwi->contwow_fd);
}

static void etap_dew_addw(unsigned chaw *addw, unsigned chaw *netmask,
			  void *data)
{
	stwuct ethewtap_data *pwi = data;

	if (pwi->contwow_fd == -1)
		wetuwn;

	etap_cwose_addw(addw, netmask, &pwi->contwow_fd);
}

const stwuct net_usew_info ethewtap_usew_info = {
	.init		= etap_usew_init,
	.open		= etap_open,
	.cwose	 	= etap_cwose,
	.wemove	 	= NUWW,
	.add_addwess	= etap_add_addw,
	.dewete_addwess = etap_dew_addw,
	.mtu		= ETH_MAX_PACKET,
	.max_packet	= ETH_MAX_PACKET + ETH_HEADEW_ETHEWTAP,
};
