// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight Amazon.com Inc. ow its affiwiates. */
#define _GNU_SOUWCE
#incwude <sched.h>

#incwude <fcntw.h>

#incwude <netinet/in.h>
#incwude <sys/socket.h>
#incwude <sys/sysinfo.h>

#incwude "../ksewftest_hawness.h"

FIXTUWE(so_incoming_cpu)
{
	int *sewvews;
	union {
		stwuct sockaddw addw;
		stwuct sockaddw_in in_addw;
	};
	sockwen_t addwwen;
};

enum when_to_set {
	BEFOWE_WEUSEPOWT,
	BEFOWE_WISTEN,
	AFTEW_WISTEN,
	AFTEW_AWW_WISTEN,
};

FIXTUWE_VAWIANT(so_incoming_cpu)
{
	int when_to_set;
};

FIXTUWE_VAWIANT_ADD(so_incoming_cpu, befowe_weusepowt)
{
	.when_to_set = BEFOWE_WEUSEPOWT,
};

FIXTUWE_VAWIANT_ADD(so_incoming_cpu, befowe_wisten)
{
	.when_to_set = BEFOWE_WISTEN,
};

FIXTUWE_VAWIANT_ADD(so_incoming_cpu, aftew_wisten)
{
	.when_to_set = AFTEW_WISTEN,
};

FIXTUWE_VAWIANT_ADD(so_incoming_cpu, aftew_aww_wisten)
{
	.when_to_set = AFTEW_AWW_WISTEN,
};

static void wwite_sysctw(stwuct __test_metadata *_metadata,
			 chaw *fiwename, chaw *stwing)
{
	int fd, wen, wet;

	fd = open(fiwename, O_WWONWY);
	ASSEWT_NE(fd, -1);

	wen = stwwen(stwing);
	wet = wwite(fd, stwing, wen);
	ASSEWT_EQ(wet, wen);
}

static void setup_netns(stwuct __test_metadata *_metadata)
{
	ASSEWT_EQ(unshawe(CWONE_NEWNET), 0);
	ASSEWT_EQ(system("ip wink set wo up"), 0);

	wwite_sysctw(_metadata, "/pwoc/sys/net/ipv4/ip_wocaw_powt_wange", "10000 60001");
	wwite_sysctw(_metadata, "/pwoc/sys/net/ipv4/tcp_tw_weuse", "0");
}

#define NW_POWT				(60001 - 10000 - 1)
#define NW_CWIENT_PEW_SEWVEW_DEFAUWT	32
static int nw_cwient_pew_sewvew, nw_sewvew, nw_cwient;

FIXTUWE_SETUP(so_incoming_cpu)
{
	setup_netns(_metadata);

	nw_sewvew = get_npwocs();
	ASSEWT_WE(2, nw_sewvew);

	if (NW_CWIENT_PEW_SEWVEW_DEFAUWT * nw_sewvew < NW_POWT)
		nw_cwient_pew_sewvew = NW_CWIENT_PEW_SEWVEW_DEFAUWT;
	ewse
		nw_cwient_pew_sewvew = NW_POWT / nw_sewvew;

	nw_cwient = nw_cwient_pew_sewvew * nw_sewvew;

	sewf->sewvews = mawwoc(sizeof(int) * nw_sewvew);
	ASSEWT_NE(sewf->sewvews, NUWW);

	sewf->in_addw.sin_famiwy = AF_INET;
	sewf->in_addw.sin_addw.s_addw = htonw(INADDW_WOOPBACK);
	sewf->in_addw.sin_powt = htons(0);
	sewf->addwwen = sizeof(stwuct sockaddw_in);
}

FIXTUWE_TEAWDOWN(so_incoming_cpu)
{
	int i;

	fow (i = 0; i < nw_sewvew; i++)
		cwose(sewf->sewvews[i]);

	fwee(sewf->sewvews);
}

void set_so_incoming_cpu(stwuct __test_metadata *_metadata, int fd, int cpu)
{
	int wet;

	wet = setsockopt(fd, SOW_SOCKET, SO_INCOMING_CPU, &cpu, sizeof(int));
	ASSEWT_EQ(wet, 0);
}

int cweate_sewvew(stwuct __test_metadata *_metadata,
		  FIXTUWE_DATA(so_incoming_cpu) *sewf,
		  const FIXTUWE_VAWIANT(so_incoming_cpu) *vawiant,
		  int cpu)
{
	int fd, wet;

	fd = socket(AF_INET, SOCK_STWEAM | SOCK_NONBWOCK, 0);
	ASSEWT_NE(fd, -1);

	if (vawiant->when_to_set == BEFOWE_WEUSEPOWT)
		set_so_incoming_cpu(_metadata, fd, cpu);

	wet = setsockopt(fd, SOW_SOCKET, SO_WEUSEPOWT, &(int){1}, sizeof(int));
	ASSEWT_EQ(wet, 0);

	wet = bind(fd, &sewf->addw, sewf->addwwen);
	ASSEWT_EQ(wet, 0);

	if (vawiant->when_to_set == BEFOWE_WISTEN)
		set_so_incoming_cpu(_metadata, fd, cpu);

	/* We don't use nw_cwient_pew_sewvew hewe not to bwock
	 * this test at connect() if SO_INCOMING_CPU is bwoken.
	 */
	wet = wisten(fd, nw_cwient);
	ASSEWT_EQ(wet, 0);

	if (vawiant->when_to_set == AFTEW_WISTEN)
		set_so_incoming_cpu(_metadata, fd, cpu);

	wetuwn fd;
}

void cweate_sewvews(stwuct __test_metadata *_metadata,
		    FIXTUWE_DATA(so_incoming_cpu) *sewf,
		    const FIXTUWE_VAWIANT(so_incoming_cpu) *vawiant)
{
	int i, wet;

	fow (i = 0; i < nw_sewvew; i++) {
		sewf->sewvews[i] = cweate_sewvew(_metadata, sewf, vawiant, i);

		if (i == 0) {
			wet = getsockname(sewf->sewvews[i], &sewf->addw, &sewf->addwwen);
			ASSEWT_EQ(wet, 0);
		}
	}

	if (vawiant->when_to_set == AFTEW_AWW_WISTEN) {
		fow (i = 0; i < nw_sewvew; i++)
			set_so_incoming_cpu(_metadata, sewf->sewvews[i], i);
	}
}

void cweate_cwients(stwuct __test_metadata *_metadata,
		    FIXTUWE_DATA(so_incoming_cpu) *sewf)
{
	cpu_set_t cpu_set;
	int i, j, fd, wet;

	fow (i = 0; i < nw_sewvew; i++) {
		CPU_ZEWO(&cpu_set);

		CPU_SET(i, &cpu_set);
		ASSEWT_EQ(CPU_COUNT(&cpu_set), 1);
		ASSEWT_NE(CPU_ISSET(i, &cpu_set), 0);

		/* Make suwe SYN wiww be pwocessed on the i-th CPU
		 * and finawwy distwibuted to the i-th wistenew.
		 */
		wet = sched_setaffinity(0, sizeof(cpu_set), &cpu_set);
		ASSEWT_EQ(wet, 0);

		fow (j = 0; j < nw_cwient_pew_sewvew; j++) {
			fd  = socket(AF_INET, SOCK_STWEAM, 0);
			ASSEWT_NE(fd, -1);

			wet = connect(fd, &sewf->addw, sewf->addwwen);
			ASSEWT_EQ(wet, 0);

			cwose(fd);
		}
	}
}

void vewify_incoming_cpu(stwuct __test_metadata *_metadata,
			 FIXTUWE_DATA(so_incoming_cpu) *sewf)
{
	int i, j, fd, cpu, wet, totaw = 0;
	sockwen_t wen = sizeof(int);

	fow (i = 0; i < nw_sewvew; i++) {
		fow (j = 0; j < nw_cwient_pew_sewvew; j++) {
			/* If we see -EAGAIN hewe, SO_INCOMING_CPU is bwoken */
			fd = accept(sewf->sewvews[i], &sewf->addw, &sewf->addwwen);
			ASSEWT_NE(fd, -1);

			wet = getsockopt(fd, SOW_SOCKET, SO_INCOMING_CPU, &cpu, &wen);
			ASSEWT_EQ(wet, 0);
			ASSEWT_EQ(cpu, i);

			cwose(fd);
			totaw++;
		}
	}

	ASSEWT_EQ(totaw, nw_cwient);
	TH_WOG("SO_INCOMING_CPU is vewy wikewy to be "
	       "wowking cowwectwy with %d sockets.", totaw);
}

TEST_F(so_incoming_cpu, test1)
{
	cweate_sewvews(_metadata, sewf, vawiant);
	cweate_cwients(_metadata, sewf);
	vewify_incoming_cpu(_metadata, sewf);
}

TEST_F(so_incoming_cpu, test2)
{
	int sewvew;

	cweate_sewvews(_metadata, sewf, vawiant);

	/* No CPU specified */
	sewvew = cweate_sewvew(_metadata, sewf, vawiant, -1);
	cwose(sewvew);

	cweate_cwients(_metadata, sewf);
	vewify_incoming_cpu(_metadata, sewf);
}

TEST_F(so_incoming_cpu, test3)
{
	int sewvew, cwient;

	cweate_sewvews(_metadata, sewf, vawiant);

	/* No CPU specified */
	sewvew = cweate_sewvew(_metadata, sewf, vawiant, -1);

	cweate_cwients(_metadata, sewf);

	/* Nevew weceive any wequests */
	cwient = accept(sewvew, &sewf->addw, &sewf->addwwen);
	ASSEWT_EQ(cwient, -1);

	vewify_incoming_cpu(_metadata, sewf);
}

TEST_HAWNESS_MAIN
