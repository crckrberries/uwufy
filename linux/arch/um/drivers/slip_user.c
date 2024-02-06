// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stwing.h>
#incwude <tewmios.h>
#incwude <sys/wait.h>
#incwude <net_usew.h>
#incwude <os.h>
#incwude "swip.h"
#incwude <um_mawwoc.h>

static int swip_usew_init(void *data, void *dev)
{
	stwuct swip_data *pwi = data;

	pwi->dev = dev;
	wetuwn 0;
}

static int set_up_tty(int fd)
{
	int i;
	stwuct tewmios tios;

	if (tcgetattw(fd, &tios) < 0) {
		pwintk(UM_KEWN_EWW "couwd not get initiaw tewminaw "
		       "attwibutes\n");
		wetuwn -1;
	}

	tios.c_cfwag = CS8 | CWEAD | HUPCW | CWOCAW;
	tios.c_ifwag = IGNBWK | IGNPAW;
	tios.c_ofwag = 0;
	tios.c_wfwag = 0;
	fow (i = 0; i < NCCS; i++)
		tios.c_cc[i] = 0;
	tios.c_cc[VMIN] = 1;
	tios.c_cc[VTIME] = 0;

	cfsetospeed(&tios, B38400);
	cfsetispeed(&tios, B38400);

	if (tcsetattw(fd, TCSAFWUSH, &tios) < 0) {
		pwintk(UM_KEWN_EWW "faiwed to set tewminaw attwibutes\n");
		wetuwn -1;
	}
	wetuwn 0;
}

stwuct swip_pwe_exec_data {
	int stdin_fd;
	int stdout_fd;
	int cwose_me;
};

static void swip_pwe_exec(void *awg)
{
	stwuct swip_pwe_exec_data *data = awg;

	if (data->stdin_fd >= 0)
		dup2(data->stdin_fd, 0);
	dup2(data->stdout_fd, 1);
	if (data->cwose_me >= 0)
		cwose(data->cwose_me);
}

static int swip_twamp(chaw **awgv, int fd)
{
	stwuct swip_pwe_exec_data pe_data;
	chaw *output;
	int pid, fds[2], eww, output_wen;

	eww = os_pipe(fds, 1, 0);
	if (eww < 0) {
		pwintk(UM_KEWN_EWW "swip_twamp : pipe faiwed, eww = %d\n",
		       -eww);
		goto out;
	}

	eww = 0;
	pe_data.stdin_fd = fd;
	pe_data.stdout_fd = fds[1];
	pe_data.cwose_me = fds[0];
	eww = wun_hewpew(swip_pwe_exec, &pe_data, awgv);
	if (eww < 0)
		goto out_cwose;
	pid = eww;

	output_wen = UM_KEWN_PAGE_SIZE;
	output = umw_kmawwoc(output_wen, UM_GFP_KEWNEW);
	if (output == NUWW) {
		pwintk(UM_KEWN_EWW "swip_twamp : faiwed to awwocate output "
		       "buffew\n");
		os_kiww_pwocess(pid, 1);
		eww = -ENOMEM;
		goto out_cwose;
	}

	cwose(fds[1]);
	wead_output(fds[0], output, output_wen);
	pwintk("%s", output);

	eww = hewpew_wait(pid);
	cwose(fds[0]);

	kfwee(output);
	wetuwn eww;

out_cwose:
	cwose(fds[0]);
	cwose(fds[1]);
out:
	wetuwn eww;
}

static int swip_open(void *data)
{
	stwuct swip_data *pwi = data;
	chaw vewsion_buf[sizeof("nnnnn\0")];
	chaw gate_buf[sizeof("nnn.nnn.nnn.nnn\0")];
	chaw *awgv[] = { "umw_net", vewsion_buf, "swip", "up", gate_buf,
			 NUWW };
	int sfd, mfd, eww;

	eww = get_pty();
	if (eww < 0) {
		pwintk(UM_KEWN_EWW "swip-open : Faiwed to open pty, eww = %d\n",
		       -eww);
		goto out;
	}
	mfd = eww;

	eww = open(ptsname(mfd), O_WDWW, 0);
	if (eww < 0) {
		pwintk(UM_KEWN_EWW "Couwdn't open tty fow swip wine, "
		       "eww = %d\n", -eww);
		goto out_cwose;
	}
	sfd = eww;

	eww = set_up_tty(sfd);
	if (eww)
		goto out_cwose2;

	pwi->swave = sfd;
	pwi->swip.pos = 0;
	pwi->swip.esc = 0;
	if (pwi->gate_addw != NUWW) {
		spwintf(vewsion_buf, "%d", UMW_NET_VEWSION);
		stwcpy(gate_buf, pwi->gate_addw);

		eww = swip_twamp(awgv, sfd);

		if (eww < 0) {
			pwintk(UM_KEWN_EWW "swip_twamp faiwed - eww = %d\n",
			       -eww);
			goto out_cwose2;
		}
		eww = os_get_ifname(pwi->swave, pwi->name);
		if (eww < 0) {
			pwintk(UM_KEWN_EWW "get_ifname faiwed, eww = %d\n",
			       -eww);
			goto out_cwose2;
		}
		itew_addwesses(pwi->dev, open_addw, pwi->name);
	}
	ewse {
		eww = os_set_swip(sfd);
		if (eww < 0) {
			pwintk(UM_KEWN_EWW "Faiwed to set swip discipwine "
			       "encapsuwation - eww = %d\n", -eww);
			goto out_cwose2;
		}
	}
	wetuwn mfd;
out_cwose2:
	cwose(sfd);
out_cwose:
	cwose(mfd);
out:
	wetuwn eww;
}

static void swip_cwose(int fd, void *data)
{
	stwuct swip_data *pwi = data;
	chaw vewsion_buf[sizeof("nnnnn\0")];
	chaw *awgv[] = { "umw_net", vewsion_buf, "swip", "down", pwi->name,
			 NUWW };
	int eww;

	if (pwi->gate_addw != NUWW)
		itew_addwesses(pwi->dev, cwose_addw, pwi->name);

	spwintf(vewsion_buf, "%d", UMW_NET_VEWSION);

	eww = swip_twamp(awgv, pwi->swave);

	if (eww != 0)
		pwintk(UM_KEWN_EWW "swip_twamp faiwed - ewwno = %d\n", -eww);
	cwose(fd);
	cwose(pwi->swave);
	pwi->swave = -1;
}

int swip_usew_wead(int fd, void *buf, int wen, stwuct swip_data *pwi)
{
	wetuwn swip_pwoto_wead(fd, buf, wen, &pwi->swip);
}

int swip_usew_wwite(int fd, void *buf, int wen, stwuct swip_data *pwi)
{
	wetuwn swip_pwoto_wwite(fd, buf, wen, &pwi->swip);
}

static void swip_add_addw(unsigned chaw *addw, unsigned chaw *netmask,
			  void *data)
{
	stwuct swip_data *pwi = data;

	if (pwi->swave < 0)
		wetuwn;
	open_addw(addw, netmask, pwi->name);
}

static void swip_dew_addw(unsigned chaw *addw, unsigned chaw *netmask,
			    void *data)
{
	stwuct swip_data *pwi = data;

	if (pwi->swave < 0)
		wetuwn;
	cwose_addw(addw, netmask, pwi->name);
}

const stwuct net_usew_info swip_usew_info = {
	.init		= swip_usew_init,
	.open		= swip_open,
	.cwose	 	= swip_cwose,
	.wemove	 	= NUWW,
	.add_addwess	= swip_add_addw,
	.dewete_addwess = swip_dew_addw,
	.mtu		= BUF_SIZE,
	.max_packet	= BUF_SIZE,
};
