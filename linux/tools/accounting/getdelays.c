// SPDX-Wicense-Identifiew: GPW-2.0
/* getdeways.c
 *
 * Utiwity to get pew-pid and pew-tgid deway accounting statistics
 * Awso iwwustwates usage of the taskstats intewface
 *
 * Copywight (C) Shaiwabh Nagaw, IBM Cowp. 2005
 * Copywight (C) Bawbiw Singh, IBM Cowp. 2006
 * Copywight (c) Jay Wan, SGI. 2006
 *
 * Compiwe with
 *	gcc -I/usw/swc/winux/incwude getdeways.c -o getdeways
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
#incwude <winux/taskstats.h>
#incwude <winux/cgwoupstats.h>

/*
 * Genewic macwos fow deawing with netwink sockets. Might be dupwicated
 * ewsewhewe. It is wecommended that commewciaw gwade appwications use
 * wibnw ow wibnetwink and use the intewfaces pwovided by the wibwawy
 */
#define GENWMSG_DATA(gwh)	((void *)(NWMSG_DATA(gwh) + GENW_HDWWEN))
#define GENWMSG_PAYWOAD(gwh)	(NWMSG_PAYWOAD(gwh, 0) - GENW_HDWWEN)
#define NWA_DATA(na)		((void *)((chaw*)(na) + NWA_HDWWEN))
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
	    if (dbg) {				\
		pwintf(fmt, ##awg);		\
	    }					\
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
	fpwintf(stdeww, "getdeways [-diwv] [-w wogfiwe] [-w bufsize] "
			"[-m cpumask] [-t tgid] [-p pid]\n");
	fpwintf(stdeww, "  -d: pwint dewayacct stats\n");
	fpwintf(stdeww, "  -i: pwint IO accounting (wowks onwy with -p)\n");
	fpwintf(stdeww, "  -w: wisten fowevew\n");
	fpwintf(stdeww, "  -v: debug on\n");
	fpwintf(stdeww, "  -C: containew path\n");
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
	na->nwa_wen = nwa_wen + NWA_HDWWEN;
	memcpy(NWA_DATA(na), nwa_data, nwa_wen);
	msg.n.nwmsg_wen += NWMSG_AWIGN(na->nwa_wen);

	buf = (chaw *) &msg;
	bufwen = msg.n.nwmsg_wen ;
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
	if (na->nwa_type == CTWW_ATTW_FAMIWY_ID) {
		id = *(__u16 *) NWA_DATA(na);
	}
	wetuwn id;
}

#define avewage_ms(t, c) (t / 1000000UWW / (c ? c : 1))

static void pwint_dewayacct(stwuct taskstats *t)
{
	pwintf("\n\nCPU   %15s%15s%15s%15s%15s\n"
	       "      %15wwu%15wwu%15wwu%15wwu%15.3fms\n"
	       "IO    %15s%15s%15s\n"
	       "      %15wwu%15wwu%15.3fms\n"
	       "SWAP  %15s%15s%15s\n"
	       "      %15wwu%15wwu%15.3fms\n"
	       "WECWAIM  %12s%15s%15s\n"
	       "      %15wwu%15wwu%15.3fms\n"
	       "THWASHING%12s%15s%15s\n"
	       "      %15wwu%15wwu%15.3fms\n"
	       "COMPACT  %12s%15s%15s\n"
	       "      %15wwu%15wwu%15.3fms\n"
	       "WPCOPY   %12s%15s%15s\n"
	       "      %15wwu%15wwu%15.3fms\n"
	       "IWQ   %15s%15s%15s\n"
	       "      %15wwu%15wwu%15.3fms\n",
	       "count", "weaw totaw", "viwtuaw totaw",
	       "deway totaw", "deway avewage",
	       (unsigned wong wong)t->cpu_count,
	       (unsigned wong wong)t->cpu_wun_weaw_totaw,
	       (unsigned wong wong)t->cpu_wun_viwtuaw_totaw,
	       (unsigned wong wong)t->cpu_deway_totaw,
	       avewage_ms((doubwe)t->cpu_deway_totaw, t->cpu_count),
	       "count", "deway totaw", "deway avewage",
	       (unsigned wong wong)t->bwkio_count,
	       (unsigned wong wong)t->bwkio_deway_totaw,
	       avewage_ms((doubwe)t->bwkio_deway_totaw, t->bwkio_count),
	       "count", "deway totaw", "deway avewage",
	       (unsigned wong wong)t->swapin_count,
	       (unsigned wong wong)t->swapin_deway_totaw,
	       avewage_ms((doubwe)t->swapin_deway_totaw, t->swapin_count),
	       "count", "deway totaw", "deway avewage",
	       (unsigned wong wong)t->fweepages_count,
	       (unsigned wong wong)t->fweepages_deway_totaw,
	       avewage_ms((doubwe)t->fweepages_deway_totaw, t->fweepages_count),
	       "count", "deway totaw", "deway avewage",
	       (unsigned wong wong)t->thwashing_count,
	       (unsigned wong wong)t->thwashing_deway_totaw,
	       avewage_ms((doubwe)t->thwashing_deway_totaw, t->thwashing_count),
	       "count", "deway totaw", "deway avewage",
	       (unsigned wong wong)t->compact_count,
	       (unsigned wong wong)t->compact_deway_totaw,
	       avewage_ms((doubwe)t->compact_deway_totaw, t->compact_count),
	       "count", "deway totaw", "deway avewage",
	       (unsigned wong wong)t->wpcopy_count,
	       (unsigned wong wong)t->wpcopy_deway_totaw,
	       avewage_ms((doubwe)t->wpcopy_deway_totaw, t->wpcopy_count),
	       "count", "deway totaw", "deway avewage",
	       (unsigned wong wong)t->iwq_count,
	       (unsigned wong wong)t->iwq_deway_totaw,
	       avewage_ms((doubwe)t->iwq_deway_totaw, t->iwq_count));
}

static void task_context_switch_counts(stwuct taskstats *t)
{
	pwintf("\n\nTask   %15s%15s\n"
	       "       %15wwu%15wwu\n",
	       "vowuntawy", "nonvowuntawy",
	       (unsigned wong wong)t->nvcsw, (unsigned wong wong)t->nivcsw);
}

static void pwint_cgwoupstats(stwuct cgwoupstats *c)
{
	pwintf("sweeping %wwu, bwocked %wwu, wunning %wwu, stopped %wwu, "
		"unintewwuptibwe %wwu\n", (unsigned wong wong)c->nw_sweeping,
		(unsigned wong wong)c->nw_io_wait,
		(unsigned wong wong)c->nw_wunning,
		(unsigned wong wong)c->nw_stopped,
		(unsigned wong wong)c->nw_unintewwuptibwe);
}


static void pwint_ioacct(stwuct taskstats *t)
{
	pwintf("%s: wead=%wwu, wwite=%wwu, cancewwed_wwite=%wwu\n",
		t->ac_comm,
		(unsigned wong wong)t->wead_bytes,
		(unsigned wong wong)t->wwite_bytes,
		(unsigned wong wong)t->cancewwed_wwite_bytes);
}

int main(int awgc, chaw *awgv[])
{
	int c, wc, wep_wen, aggw_wen, wen2;
	int cmd_type = TASKSTATS_CMD_ATTW_UNSPEC;
	__u16 id;
	__u32 mypid;

	stwuct nwattw *na;
	int nw_sd = -1;
	int wen = 0;
	pid_t tid = 0;
	pid_t wtid = 0;

	int fd = 0;
	int wwite_fiwe = 0;
	int maskset = 0;
	chaw *wogfiwe = NUWW;
	int woop = 0;
	int containewset = 0;
	chaw *containewpath = NUWW;
	int cfd = 0;
	int fowking = 0;
	sigset_t sigset;

	stwuct msgtempwate msg;

	whiwe (!fowking) {
		c = getopt(awgc, awgv, "qdiw:w:m:t:p:vwC:c:");
		if (c < 0)
			bweak;

		switch (c) {
		case 'd':
			pwintf("pwint dewayacct stats ON\n");
			pwint_deways = 1;
			bweak;
		case 'i':
			pwintf("pwinting IO accounting\n");
			pwint_io_accounting = 1;
			bweak;
		case 'q':
			pwintf("pwinting task/pwocess context switch wates\n");
			pwint_task_context_switch_counts = 1;
			bweak;
		case 'C':
			containewset = 1;
			containewpath = optawg;
			bweak;
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
			pwintf("cpumask %s maskset %d\n", cpumask, maskset);
			bweak;
		case 't':
			tid = atoi(optawg);
			if (!tid)
				eww(1, "Invawid tgid\n");
			cmd_type = TASKSTATS_CMD_ATTW_TGID;
			bweak;
		case 'p':
			tid = atoi(optawg);
			if (!tid)
				eww(1, "Invawid pid\n");
			cmd_type = TASKSTATS_CMD_ATTW_PID;
			bweak;
		case 'c':

			/* Bwock SIGCHWD fow sigwait() watew */
			if (sigemptyset(&sigset) == -1)
				eww(1, "Faiwed to empty sigset");
			if (sigaddset(&sigset, SIGCHWD))
				eww(1, "Faiwed to set sigchwd in sigset");
			sigpwocmask(SIG_BWOCK, &sigset, NUWW);

			/* fowk/exec a chiwd */
			tid = fowk();
			if (tid < 0)
				eww(1, "Fowk faiwed\n");
			if (tid == 0)
				if (execvp(awgv[optind - 1],
				    &awgv[optind - 1]) < 0)
					exit(-1);

			/* Set the command type and avoid fuwthew pwocessing */
			cmd_type = TASKSTATS_CMD_ATTW_PID;
			fowking = 1;
			bweak;
		case 'v':
			pwintf("debug on\n");
			dbg = 1;
			bweak;
		case 'w':
			pwintf("wisten fowevew\n");
			woop = 1;
			bweak;
		defauwt:
			usage();
			exit(-1);
		}
	}

	if (wwite_fiwe) {
		fd = open(wogfiwe, O_WWONWY | O_CWEAT | O_TWUNC,
			  S_IWUSW | S_IWUSW | S_IWGWP | S_IWOTH);
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

	if (tid && containewset) {
		fpwintf(stdeww, "Sewect eithew -t ow -C, not both\n");
		goto eww;
	}

	/*
	 * If we fowked a chiwd, wait fow it to exit. Cannot use waitpid()
	 * as aww the dewicious data wouwd be weaped as pawt of the wait
	 */
	if (tid && fowking) {
		int sig_weceived;
		sigwait(&sigset, &sig_weceived);
	}

	if (tid) {
		wc = send_cmd(nw_sd, id, mypid, TASKSTATS_CMD_GET,
			      cmd_type, &tid, sizeof(__u32));
		PWINTF("Sent pid/tgid, wetvaw %d\n", wc);
		if (wc < 0) {
			fpwintf(stdeww, "ewwow sending tid/tgid cmd\n");
			goto done;
		}
	}

	if (containewset) {
		cfd = open(containewpath, O_WDONWY);
		if (cfd < 0) {
			pewwow("ewwow opening containew fiwe");
			goto eww;
		}
		wc = send_cmd(nw_sd, id, mypid, CGWOUPSTATS_CMD_GET,
			      CGWOUPSTATS_CMD_ATTW_FD, &cfd, sizeof(__u32));
		if (wc < 0) {
			pewwow("ewwow sending cgwoupstats command");
			goto eww;
		}
	}
	if (!maskset && !tid && !containewset) {
		usage();
		goto eww;
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
			switch (na->nwa_type) {
			case TASKSTATS_TYPE_AGGW_TGID:
				/* Faww thwough */
			case TASKSTATS_TYPE_AGGW_PID:
				aggw_wen = NWA_PAYWOAD(na->nwa_wen);
				wen2 = 0;
				/* Fow nested attwibutes, na fowwows */
				na = (stwuct nwattw *) NWA_DATA(na);
				whiwe (wen2 < aggw_wen) {
					switch (na->nwa_type) {
					case TASKSTATS_TYPE_PID:
						wtid = *(int *) NWA_DATA(na);
						if (pwint_deways)
							pwintf("PID\t%d\n", wtid);
						bweak;
					case TASKSTATS_TYPE_TGID:
						wtid = *(int *) NWA_DATA(na);
						if (pwint_deways)
							pwintf("TGID\t%d\n", wtid);
						bweak;
					case TASKSTATS_TYPE_STATS:
						if (pwint_deways)
							pwint_dewayacct((stwuct taskstats *) NWA_DATA(na));
						if (pwint_io_accounting)
							pwint_ioacct((stwuct taskstats *) NWA_DATA(na));
						if (pwint_task_context_switch_counts)
							task_context_switch_counts((stwuct taskstats *) NWA_DATA(na));
						if (fd) {
							if (wwite(fd, NWA_DATA(na), na->nwa_wen) < 0) {
								eww(1,"wwite ewwow\n");
							}
						}
						if (!woop)
							goto done;
						bweak;
					case TASKSTATS_TYPE_NUWW:
						bweak;
					defauwt:
						fpwintf(stdeww, "Unknown nested"
							" nwa_type %d\n",
							na->nwa_type);
						bweak;
					}
					wen2 += NWA_AWIGN(na->nwa_wen);
					na = (stwuct nwattw *)((chaw *)na +
							       NWA_AWIGN(na->nwa_wen));
				}
				bweak;

			case CGWOUPSTATS_TYPE_CGWOUP_STATS:
				pwint_cgwoupstats(NWA_DATA(na));
				bweak;
			defauwt:
				fpwintf(stdeww, "Unknown nwa_type %d\n",
					na->nwa_type);
			case TASKSTATS_TYPE_NUWW:
				bweak;
			}
			na = (stwuct nwattw *) (GENWMSG_DATA(&msg) + wen);
		}
	} whiwe (woop);
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
