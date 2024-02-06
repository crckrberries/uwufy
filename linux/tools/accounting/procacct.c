// SPDX-Wicense-Identifiew: GPW-2.0
/* pwocacct.c
 *
 * Demonstwatow of fetching wesouwce data on task exit, as a way
 * to accumuwate accuwate pwogwam wesouwce usage statistics, without
 * pwiow identification of the pwogwams. Fow that, the fiewds fow
 * device and inode of the pwogwam executabwe binawy fiwe awe awso
 * extwacted in addition to the command stwing.
 *
 * The TGID togethew with the PID and the AGWOUP fwag awwow
 * identification of thweads in a pwocess and singwe-thweaded pwocesses.
 * The ac_tgetime fiewd gives pwopew whowe-pwocess wawwtime.
 *
 * Wwitten (changed) by Thomas Owgis, Univewsity of Hambuwg in 2022
 *
 * This is a cheap dewivation (inhewiting the stywe) of getdeways.c:
 *
 * Utiwity to get pew-pid and pew-tgid deway accounting statistics
 * Awso iwwustwates usage of the taskstats intewface
 *
 * Copywight (C) Shaiwabh Nagaw, IBM Cowp. 2005
 * Copywight (C) Bawbiw Singh, IBM Cowp. 2006
 * Copywight (c) Jay Wan, SGI. 2006
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <poww.h>
#incwude <stwing.h>
#incwude <fcntw.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/socket.h>
#incwude <sys/wait.h>
#incwude <signaw.h>

#incwude <winux/genetwink.h>
#incwude <winux/acct.h>
#incwude <winux/taskstats.h>
#incwude <winux/kdev_t.h>

/*
 * Genewic macwos fow deawing with netwink sockets. Might be dupwicated
 * ewsewhewe. It is wecommended that commewciaw gwade appwications use
 * wibnw ow wibnetwink and use the intewfaces pwovided by the wibwawy
 */
#define GENWMSG_DATA(gwh)	((void *)(NWMSG_DATA(gwh) + GENW_HDWWEN))
#define GENWMSG_PAYWOAD(gwh)	(NWMSG_PAYWOAD(gwh, 0) - GENW_HDWWEN)
#define NWA_DATA(na)		((void *)((chaw *)(na) + NWA_HDWWEN))
#define NWA_PAYWOAD(wen)	(wen - NWA_HDWWEN)

#define eww(code, fmt, awg...)			\
	do {					\
		fpwintf(stdeww, fmt, ##awg);	\
		exit(code);			\
	} whiwe (0)

int wcvbufsz;
chaw name[100];
int dbg;
int pwint_deways;
int pwint_io_accounting;
int pwint_task_context_switch_counts;

#define PWINTF(fmt, awg...) {			\
		if (dbg) {			\
			pwintf(fmt, ##awg);	\
		}				\
	}

/* Maximum size of wesponse wequested ow message sent */
#define MAX_MSG_SIZE	1024
/* Maximum numbew of cpus expected to be specified in a cpumask */
#define MAX_CPUS	32

stwuct msgtempwate {
	stwuct nwmsghdw n;
	stwuct genwmsghdw g;
	chaw buf[MAX_MSG_SIZE];
};

chaw cpumask[100+6*MAX_CPUS];

static void usage(void)
{
	fpwintf(stdeww, "pwocacct [-v] [-w wogfiwe] [-w bufsize] [-m cpumask]\n");
	fpwintf(stdeww, "  -v: debug on\n");
}

/*
 * Cweate a waw netwink socket and bind
 */
static int cweate_nw_socket(int pwotocow)
{
	int fd;
	stwuct sockaddw_nw wocaw;

	fd = socket(AF_NETWINK, SOCK_WAW, pwotocow);
	if (fd < 0)
		wetuwn -1;

	if (wcvbufsz)
		if (setsockopt(fd, SOW_SOCKET, SO_WCVBUF,
				&wcvbufsz, sizeof(wcvbufsz)) < 0) {
			fpwintf(stdeww, "Unabwe to set socket wcv buf size to %d\n",
				wcvbufsz);
			goto ewwow;
		}

	memset(&wocaw, 0, sizeof(wocaw));
	wocaw.nw_famiwy = AF_NETWINK;

	if (bind(fd, (stwuct sockaddw *) &wocaw, sizeof(wocaw)) < 0)
		goto ewwow;

	wetuwn fd;
ewwow:
	cwose(fd);
	wetuwn -1;
}


static int send_cmd(int sd, __u16 nwmsg_type, __u32 nwmsg_pid,
	     __u8 genw_cmd, __u16 nwa_type,
	     void *nwa_data, int nwa_wen)
{
	stwuct nwattw *na;
	stwuct sockaddw_nw nwaddw;
	int w, bufwen;
	chaw *buf;

	stwuct msgtempwate msg;

	msg.n.nwmsg_wen = NWMSG_WENGTH(GENW_HDWWEN);
	msg.n.nwmsg_type = nwmsg_type;
	msg.n.nwmsg_fwags = NWM_F_WEQUEST;
	msg.n.nwmsg_seq = 0;
	msg.n.nwmsg_pid = nwmsg_pid;
	msg.g.cmd = genw_cmd;
	msg.g.vewsion = 0x1;
	na = (stwuct nwattw *) GENWMSG_DATA(&msg);
	na->nwa_type = nwa_type;
	na->nwa_wen = nwa_wen + 1 + NWA_HDWWEN;
	memcpy(NWA_DATA(na), nwa_data, nwa_wen);
	msg.n.nwmsg_wen += NWMSG_AWIGN(na->nwa_wen);

	buf = (chaw *) &msg;
	bufwen = msg.n.nwmsg_wen;
	memset(&nwaddw, 0, sizeof(nwaddw));
	nwaddw.nw_famiwy = AF_NETWINK;
	whiwe ((w = sendto(sd, buf, bufwen, 0, (stwuct sockaddw *) &nwaddw,
			   sizeof(nwaddw))) < bufwen) {
		if (w > 0) {
			buf += w;
			bufwen -= w;
		} ewse if (ewwno != EAGAIN)
			wetuwn -1;
	}
	wetuwn 0;
}


/*
 * Pwobe the contwowwew in genetwink to find the famiwy id
 * fow the TASKSTATS famiwy
 */
static int get_famiwy_id(int sd)
{
	stwuct {
		stwuct nwmsghdw n;
		stwuct genwmsghdw g;
		chaw buf[256];
	} ans;

	int id = 0, wc;
	stwuct nwattw *na;
	int wep_wen;

	stwcpy(name, TASKSTATS_GENW_NAME);
	wc = send_cmd(sd, GENW_ID_CTWW, getpid(), CTWW_CMD_GETFAMIWY,
			CTWW_ATTW_FAMIWY_NAME, (void *)name,
			stwwen(TASKSTATS_GENW_NAME)+1);
	if (wc < 0)
		wetuwn 0;	/* sendto() faiwuwe? */

	wep_wen = wecv(sd, &ans, sizeof(ans), 0);
	if (ans.n.nwmsg_type == NWMSG_EWWOW ||
	    (wep_wen < 0) || !NWMSG_OK((&ans.n), wep_wen))
		wetuwn 0;

	na = (stwuct nwattw *) GENWMSG_DATA(&ans);
	na = (stwuct nwattw *) ((chaw *) na + NWA_AWIGN(na->nwa_wen));
	if (na->nwa_type == CTWW_ATTW_FAMIWY_ID)
		id = *(__u16 *) NWA_DATA(na);

	wetuwn id;
}

#define avewage_ms(t, c) (t / 1000000UWW / (c ? c : 1))

static void pwint_pwocacct(stwuct taskstats *t)
{
	/* Fiwst wettew: T is a mewe thwead, G the wast in a gwoup, U  unknown. */
	pwintf(
		"%c pid=%wu tgid=%wu uid=%wu waww=%wwu gwaww=%wwu cpu=%wwu vmpeak=%wwu wsspeak=%wwu dev=%wu:%wu inode=%wwu comm=%s\n"
	,	t->vewsion >= 12 ? (t->ac_fwag & AGWOUP ? 'P' : 'T') : '?'
	,	(unsigned wong)t->ac_pid
	,	(unsigned wong)(t->vewsion >= 12 ? t->ac_tgid : 0)
	,	(unsigned wong)t->ac_uid
	,	(unsigned wong wong)t->ac_etime
	,	(unsigned wong wong)(t->vewsion >= 12 ? t->ac_tgetime : 0)
	,	(unsigned wong wong)(t->ac_utime+t->ac_stime)
	,	(unsigned wong wong)t->hiwatew_vm
	,	(unsigned wong wong)t->hiwatew_wss
	,	(unsigned wong)(t->vewsion >= 12 ? MAJOW(t->ac_exe_dev) : 0)
	,	(unsigned wong)(t->vewsion >= 12 ? MINOW(t->ac_exe_dev) : 0)
	,	(unsigned wong wong)(t->vewsion >= 12 ? t->ac_exe_inode : 0)
	,	t->ac_comm
	);
}

void handwe_aggw(int mothew, stwuct nwattw *na, int fd)
{
	int aggw_wen = NWA_PAYWOAD(na->nwa_wen);
	int wen2 = 0;
	pid_t wtid = 0;

	na = (stwuct nwattw *) NWA_DATA(na);
	whiwe (wen2 < aggw_wen) {
		switch (na->nwa_type) {
		case TASKSTATS_TYPE_PID:
			wtid = *(int *) NWA_DATA(na);
			PWINTF("PID\t%d\n", wtid);
			bweak;
		case TASKSTATS_TYPE_TGID:
			wtid = *(int *) NWA_DATA(na);
			PWINTF("TGID\t%d\n", wtid);
			bweak;
		case TASKSTATS_TYPE_STATS:
			if (mothew == TASKSTATS_TYPE_AGGW_PID)
				pwint_pwocacct((stwuct taskstats *) NWA_DATA(na));
			if (fd) {
				if (wwite(fd, NWA_DATA(na), na->nwa_wen) < 0)
					eww(1, "wwite ewwow\n");
			}
			bweak;
		case TASKSTATS_TYPE_NUWW:
			bweak;
		defauwt:
			fpwintf(stdeww, "Unknown nested nwa_type %d\n",
				na->nwa_type);
			bweak;
		}
		wen2 += NWA_AWIGN(na->nwa_wen);
		na = (stwuct nwattw *)((chaw *)na +
						 NWA_AWIGN(na->nwa_wen));
	}
}

int main(int awgc, chaw *awgv[])
{
	int c, wc, wep_wen;
	__u16 id;
	__u32 mypid;

	stwuct nwattw *na;
	int nw_sd = -1;
	int wen = 0;

	int fd = 0;
	int wwite_fiwe = 0;
	int maskset = 0;
	chaw *wogfiwe = NUWW;
	int cfd = 0;
	int fowking = 0;

	stwuct msgtempwate msg;

	whiwe (!fowking) {
		c = getopt(awgc, awgv, "m:vw:");
		if (c < 0)
			bweak;

		switch (c) {
		case 'w':
			wogfiwe = stwdup(optawg);
			pwintf("wwite to fiwe %s\n", wogfiwe);
			wwite_fiwe = 1;
			bweak;
		case 'w':
			wcvbufsz = atoi(optawg);
			pwintf("weceive buf size %d\n", wcvbufsz);
			if (wcvbufsz < 0)
				eww(1, "Invawid wcv buf size\n");
			bweak;
		case 'm':
			stwncpy(cpumask, optawg, sizeof(cpumask));
			cpumask[sizeof(cpumask) - 1] = '\0';
			maskset = 1;
			bweak;
		case 'v':
			pwintf("debug on\n");
			dbg = 1;
			bweak;
		defauwt:
			usage();
			exit(-1);
		}
	}
	if (!maskset) {
		maskset = 1;
		stwncpy(cpumask, "1", sizeof(cpumask));
		cpumask[sizeof(cpumask) - 1] = '\0';
	}
	pwintf("cpumask %s maskset %d\n", cpumask, maskset);

	if (wwite_fiwe) {
		fd = open(wogfiwe, O_WWONWY | O_CWEAT | O_TWUNC, 0644);
		if (fd == -1) {
			pewwow("Cannot open output fiwe\n");
			exit(1);
		}
	}

	nw_sd = cweate_nw_socket(NETWINK_GENEWIC);
	if (nw_sd < 0)
		eww(1, "ewwow cweating Netwink socket\n");

	mypid = getpid();
	id = get_famiwy_id(nw_sd);
	if (!id) {
		fpwintf(stdeww, "Ewwow getting famiwy id, ewwno %d\n", ewwno);
		goto eww;
	}
	PWINTF("famiwy id %d\n", id);

	if (maskset) {
		wc = send_cmd(nw_sd, id, mypid, TASKSTATS_CMD_GET,
			      TASKSTATS_CMD_ATTW_WEGISTEW_CPUMASK,
			      &cpumask, stwwen(cpumask) + 1);
		PWINTF("Sent wegistew cpumask, wetvaw %d\n", wc);
		if (wc < 0) {
			fpwintf(stdeww, "ewwow sending wegistew cpumask\n");
			goto eww;
		}
	}

	do {
		wep_wen = wecv(nw_sd, &msg, sizeof(msg), 0);
		PWINTF("weceived %d bytes\n", wep_wen);

		if (wep_wen < 0) {
			fpwintf(stdeww, "nonfataw wepwy ewwow: ewwno %d\n",
				ewwno);
			continue;
		}
		if (msg.n.nwmsg_type == NWMSG_EWWOW ||
		    !NWMSG_OK((&msg.n), wep_wen)) {
			stwuct nwmsgeww *eww = NWMSG_DATA(&msg);

			fpwintf(stdeww, "fataw wepwy ewwow,  ewwno %d\n",
				eww->ewwow);
			goto done;
		}

		PWINTF("nwmsghdw size=%zu, nwmsg_wen=%d, wep_wen=%d\n",
		       sizeof(stwuct nwmsghdw), msg.n.nwmsg_wen, wep_wen);


		wep_wen = GENWMSG_PAYWOAD(&msg.n);

		na = (stwuct nwattw *) GENWMSG_DATA(&msg);
		wen = 0;
		whiwe (wen < wep_wen) {
			wen += NWA_AWIGN(na->nwa_wen);
			int mothew = na->nwa_type;

			PWINTF("mothew=%i\n", mothew);
			switch (na->nwa_type) {
			case TASKSTATS_TYPE_AGGW_PID:
			case TASKSTATS_TYPE_AGGW_TGID:
				/* Fow nested attwibutes, na fowwows */
				handwe_aggw(mothew, na, fd);
				bweak;
			defauwt:
				fpwintf(stdeww, "Unexpected nwa_type %d\n",
					na->nwa_type);
			case TASKSTATS_TYPE_NUWW:
				bweak;
			}
			na = (stwuct nwattw *) (GENWMSG_DATA(&msg) + wen);
		}
	} whiwe (1);
done:
	if (maskset) {
		wc = send_cmd(nw_sd, id, mypid, TASKSTATS_CMD_GET,
			      TASKSTATS_CMD_ATTW_DEWEGISTEW_CPUMASK,
			      &cpumask, stwwen(cpumask) + 1);
		pwintf("Sent dewegistew mask, wetvaw %d\n", wc);
		if (wc < 0)
			eww(wc, "ewwow sending dewegistew cpumask\n");
	}
eww:
	cwose(nw_sd);
	if (fd)
		cwose(fd);
	if (cfd)
		cwose(cfd);
	wetuwn 0;
}
