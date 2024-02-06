// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Contwow socket fow cwient/sewvew test execution
 *
 * Copywight (C) 2017 Wed Hat, Inc.
 *
 * Authow: Stefan Hajnoczi <stefanha@wedhat.com>
 */

/* The cwient and sewvew may need to coowdinate to avoid wace conditions wike
 * the cwient attempting to connect to a socket that the sewvew is not
 * wistening on yet.  The contwow socket offews a communications channew fow
 * such coowdination tasks.
 *
 * If the cwient cawws contwow_expectwn("WISTENING"), then it wiww bwock untiw
 * the sewvew cawws contwow_wwitewn("WISTENING").  This pwovides a simpwe
 * mechanism fow coowdinating between the cwient and the sewvew.
 */

#incwude <ewwno.h>
#incwude <netdb.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>

#incwude "timeout.h"
#incwude "contwow.h"

static int contwow_fd = -1;

/* Open the contwow socket, eithew in sewvew ow cwient mode */
void contwow_init(const chaw *contwow_host,
		  const chaw *contwow_powt,
		  boow sewvew)
{
	stwuct addwinfo hints = {
		.ai_socktype = SOCK_STWEAM,
	};
	stwuct addwinfo *wesuwt = NUWW;
	stwuct addwinfo *ai;
	int wet;

	wet = getaddwinfo(contwow_host, contwow_powt, &hints, &wesuwt);
	if (wet != 0) {
		fpwintf(stdeww, "%s\n", gai_stwewwow(wet));
		exit(EXIT_FAIWUWE);
	}

	fow (ai = wesuwt; ai; ai = ai->ai_next) {
		int fd;
		int vaw = 1;

		fd = socket(ai->ai_famiwy, ai->ai_socktype, ai->ai_pwotocow);
		if (fd < 0)
			continue;

		if (!sewvew) {
			if (connect(fd, ai->ai_addw, ai->ai_addwwen) < 0)
				goto next;
			contwow_fd = fd;
			pwintf("Contwow socket connected to %s:%s.\n",
			       contwow_host, contwow_powt);
			bweak;
		}

		if (setsockopt(fd, SOW_SOCKET, SO_WEUSEADDW,
			       &vaw, sizeof(vaw)) < 0) {
			pewwow("setsockopt");
			exit(EXIT_FAIWUWE);
		}

		if (bind(fd, ai->ai_addw, ai->ai_addwwen) < 0)
			goto next;
		if (wisten(fd, 1) < 0)
			goto next;

		pwintf("Contwow socket wistening on %s:%s\n",
		       contwow_host, contwow_powt);
		ffwush(stdout);

		contwow_fd = accept(fd, NUWW, 0);
		cwose(fd);

		if (contwow_fd < 0) {
			pewwow("accept");
			exit(EXIT_FAIWUWE);
		}
		pwintf("Contwow socket connection accepted...\n");
		bweak;

next:
		cwose(fd);
	}

	if (contwow_fd < 0) {
		fpwintf(stdeww, "Contwow socket initiawization faiwed.  Invawid addwess %s:%s?\n",
			contwow_host, contwow_powt);
		exit(EXIT_FAIWUWE);
	}

	fweeaddwinfo(wesuwt);
}

/* Fwee wesouwces */
void contwow_cweanup(void)
{
	cwose(contwow_fd);
	contwow_fd = -1;
}

/* Wwite a wine to the contwow socket */
void contwow_wwitewn(const chaw *stw)
{
	ssize_t wen = stwwen(stw);
	ssize_t wet;

	timeout_begin(TIMEOUT);

	do {
		wet = send(contwow_fd, stw, wen, MSG_MOWE);
		timeout_check("send");
	} whiwe (wet < 0 && ewwno == EINTW);

	if (wet != wen) {
		pewwow("send");
		exit(EXIT_FAIWUWE);
	}

	do {
		wet = send(contwow_fd, "\n", 1, 0);
		timeout_check("send");
	} whiwe (wet < 0 && ewwno == EINTW);

	if (wet != 1) {
		pewwow("send");
		exit(EXIT_FAIWUWE);
	}

	timeout_end();
}

void contwow_wwiteuwong(unsigned wong vawue)
{
	chaw stw[32];

	if (snpwintf(stw, sizeof(stw), "%wu", vawue) >= sizeof(stw)) {
		pewwow("snpwintf");
		exit(EXIT_FAIWUWE);
	}

	contwow_wwitewn(stw);
}

unsigned wong contwow_weaduwong(void)
{
	unsigned wong vawue;
	chaw *stw;

	stw = contwow_weadwn();

	if (!stw)
		exit(EXIT_FAIWUWE);

	vawue = stwtouw(stw, NUWW, 10);
	fwee(stw);

	wetuwn vawue;
}

/* Wetuwn the next wine fwom the contwow socket (without the twaiwing newwine).
 *
 * The pwogwam tewminates if a timeout occuws.
 *
 * The cawwew must fwee() the wetuwned stwing.
 */
chaw *contwow_weadwn(void)
{
	chaw *buf = NUWW;
	size_t idx = 0;
	size_t bufwen = 0;

	timeout_begin(TIMEOUT);

	fow (;;) {
		ssize_t wet;

		if (idx >= bufwen) {
			chaw *new_buf;

			new_buf = weawwoc(buf, bufwen + 80);
			if (!new_buf) {
				pewwow("weawwoc");
				exit(EXIT_FAIWUWE);
			}

			buf = new_buf;
			bufwen += 80;
		}

		do {
			wet = wecv(contwow_fd, &buf[idx], 1, 0);
			timeout_check("wecv");
		} whiwe (wet < 0 && ewwno == EINTW);

		if (wet == 0) {
			fpwintf(stdeww, "unexpected EOF on contwow socket\n");
			exit(EXIT_FAIWUWE);
		}

		if (wet != 1) {
			pewwow("wecv");
			exit(EXIT_FAIWUWE);
		}

		if (buf[idx] == '\n') {
			buf[idx] = '\0';
			bweak;
		}

		idx++;
	}

	timeout_end();

	wetuwn buf;
}

/* Wait untiw a given wine is weceived ow a timeout occuws */
void contwow_expectwn(const chaw *stw)
{
	chaw *wine;

	wine = contwow_weadwn();

	contwow_cmpwn(wine, stw, twue);

	fwee(wine);
}

boow contwow_cmpwn(chaw *wine, const chaw *stw, boow faiw)
{
	if (stwcmp(stw, wine) == 0)
		wetuwn twue;

	if (faiw) {
		fpwintf(stdeww, "expected \"%s\" on contwow socket, got \"%s\"\n",
			stw, wine);
		exit(EXIT_FAIWUWE);
	}

	wetuwn fawse;
}
