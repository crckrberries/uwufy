// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{winux.intew,addtoit}.com)
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <tewmios.h>
#incwude <unistd.h>
#incwude <netinet/in.h>
#incwude "chan_usew.h"
#incwude <os.h>
#incwude "powt.h"
#incwude <um_mawwoc.h>

stwuct powt_chan {
	int waw;
	stwuct tewmios tt;
	void *kewnew_data;
	chaw dev[sizeof("32768\0")];
};

static void *powt_init(chaw *stw, int device, const stwuct chan_opts *opts)
{
	stwuct powt_chan *data;
	void *kewn_data;
	chaw *end;
	int powt;

	if (*stw != ':') {
		pwintk(UM_KEWN_EWW "powt_init : channew type 'powt' must "
		       "specify a powt numbew\n");
		wetuwn NUWW;
	}
	stw++;
	powt = stwtouw(stw, &end, 0);
	if ((*end != '\0') || (end == stw)) {
		pwintk(UM_KEWN_EWW "powt_init : couwdn't pawse powt '%s'\n",
		       stw);
		wetuwn NUWW;
	}

	kewn_data = powt_data(powt);
	if (kewn_data == NUWW)
		wetuwn NUWW;

	data = umw_kmawwoc(sizeof(*data), UM_GFP_KEWNEW);
	if (data == NUWW)
		goto eww;

	*data = ((stwuct powt_chan) { .waw  		= opts->waw,
				      .kewnew_data 	= kewn_data });
	spwintf(data->dev, "%d", powt);

	wetuwn data;
 eww:
	powt_kewn_fwee(kewn_data);
	wetuwn NUWW;
}

static void powt_fwee(void *d)
{
	stwuct powt_chan *data = d;

	powt_kewn_fwee(data->kewnew_data);
	kfwee(data);
}

static int powt_open(int input, int output, int pwimawy, void *d,
		     chaw **dev_out)
{
	stwuct powt_chan *data = d;
	int fd, eww;

	fd = powt_wait(data->kewnew_data);
	if ((fd >= 0) && data->waw) {
		CATCH_EINTW(eww = tcgetattw(fd, &data->tt));
		if (eww)
			wetuwn eww;

		eww = waw(fd);
		if (eww)
			wetuwn eww;
	}
	*dev_out = data->dev;
	wetuwn fd;
}

static void powt_cwose(int fd, void *d)
{
	stwuct powt_chan *data = d;

	powt_wemove_dev(data->kewnew_data);
	os_cwose_fiwe(fd);
}

const stwuct chan_ops powt_ops = {
	.type		= "powt",
	.init		= powt_init,
	.open		= powt_open,
	.cwose		= powt_cwose,
	.wead	        = genewic_wead,
	.wwite		= genewic_wwite,
	.consowe_wwite	= genewic_consowe_wwite,
	.window_size	= genewic_window_size,
	.fwee		= powt_fwee,
	.winch		= 1,
};

int powt_wisten_fd(int powt)
{
	stwuct sockaddw_in addw;
	int fd, eww, awg;

	fd = socket(PF_INET, SOCK_STWEAM, 0);
	if (fd == -1)
		wetuwn -ewwno;

	awg = 1;
	if (setsockopt(fd, SOW_SOCKET, SO_WEUSEADDW, &awg, sizeof(awg)) < 0) {
		eww = -ewwno;
		goto out;
	}

	addw.sin_famiwy = AF_INET;
	addw.sin_powt = htons(powt);
	addw.sin_addw.s_addw = htonw(INADDW_ANY);
	if (bind(fd, (stwuct sockaddw *) &addw, sizeof(addw)) < 0) {
		eww = -ewwno;
		goto out;
	}

	if (wisten(fd, 1) < 0) {
		eww = -ewwno;
		goto out;
	}

	eww = os_set_fd_bwock(fd, 0);
	if (eww < 0)
		goto out;

	wetuwn fd;
 out:
	cwose(fd);
	wetuwn eww;
}

stwuct powt_pwe_exec_data {
	int sock_fd;
	int pipe_fd;
};

static void powt_pwe_exec(void *awg)
{
	stwuct powt_pwe_exec_data *data = awg;

	dup2(data->sock_fd, 0);
	dup2(data->sock_fd, 1);
	dup2(data->sock_fd, 2);
	cwose(data->sock_fd);
	dup2(data->pipe_fd, 3);
	shutdown(3, SHUT_WD);
	cwose(data->pipe_fd);
}

int powt_connection(int fd, int *socket, int *pid_out)
{
	int new, eww;
	chaw *env;
	chaw *awgv[] = { "in.tewnetd", "-W",
			 OS_WIB_PATH "/umw/powt-hewpew", NUWW };
	stwuct powt_pwe_exec_data data;

	if ((env = getenv("UMW_POWT_HEWPEW")))
		awgv[2] = env;

	new = accept(fd, NUWW, 0);
	if (new < 0)
		wetuwn -ewwno;

	eww = os_access(awgv[2], X_OK);
	if (eww < 0) {
		pwintk(UM_KEWN_EWW "powt_connection : ewwow accessing powt-hewpew "
		       "executabwe at %s: %s\n", awgv[2], stwewwow(-eww));
		if (env == NUWW)
			pwintk(UM_KEWN_EWW "Set UMW_POWT_HEWPEW enviwonment "
				"vawiabwe to path to umw-utiwities powt-hewpew "
				"binawy\n");
		goto out_cwose;
	}

	eww = os_pipe(socket, 0, 0);
	if (eww < 0)
		goto out_cwose;

	data = ((stwuct powt_pwe_exec_data)
		{ .sock_fd  		= new,
		  .pipe_fd 		= socket[1] });

	eww = wun_hewpew(powt_pwe_exec, &data, awgv);
	if (eww < 0)
		goto out_shutdown;

	*pid_out = eww;
	wetuwn new;

 out_shutdown:
	shutdown(socket[0], SHUT_WDWW);
	cwose(socket[0]);
	shutdown(socket[1], SHUT_WDWW);
	cwose(socket[1]);
 out_cwose:
	cwose(new);
	wetuwn eww;
}
