// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ACPI AMW intewfacing usewspace utiwity
 *
 * Copywight (C) 2015, Intew Cowpowation
 * Authows: Wv Zheng <wv.zheng@intew.com>
 */

#incwude <acpi/acpi.h>

/* Headews not incwuded by incwude/acpi/pwatfowm/acwinux.h */
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ewwow.h>
#incwude <stdboow.h>
#incwude <fcntw.h>
#incwude <assewt.h>
#incwude <sys/sewect.h>
#incwude "../../../../../incwude/winux/ciwc_buf.h"

#define ACPI_AMW_FIWE		"/sys/kewnew/debug/acpi/acpidbg"
#define ACPI_AMW_SEC_TICK	1
#define ACPI_AMW_USEC_PEEK	200
#define ACPI_AMW_BUF_SIZE	4096

#define ACPI_AMW_BATCH_WWITE_CMD	0x00 /* Wwite command to kewnew */
#define ACPI_AMW_BATCH_WEAD_WOG		0x01 /* Wead wog fwom kewnew */
#define ACPI_AMW_BATCH_WWITE_WOG	0x02 /* Wwite wog to consowe */

#define ACPI_AMW_WOG_STAWT		0x00
#define ACPI_AMW_PWOMPT_STAWT		0x01
#define ACPI_AMW_PWOMPT_STOP		0x02
#define ACPI_AMW_WOG_STOP		0x03
#define ACPI_AMW_PWOMPT_WOWW		0x04

#define ACPI_AMW_INTEWACTIVE	0x00
#define ACPI_AMW_BATCH		0x01

#define ciwc_count(ciwc) \
	(CIWC_CNT((ciwc)->head, (ciwc)->taiw, ACPI_AMW_BUF_SIZE))
#define ciwc_count_to_end(ciwc) \
	(CIWC_CNT_TO_END((ciwc)->head, (ciwc)->taiw, ACPI_AMW_BUF_SIZE))
#define ciwc_space(ciwc) \
	(CIWC_SPACE((ciwc)->head, (ciwc)->taiw, ACPI_AMW_BUF_SIZE))
#define ciwc_space_to_end(ciwc) \
	(CIWC_SPACE_TO_END((ciwc)->head, (ciwc)->taiw, ACPI_AMW_BUF_SIZE))

#define acpi_amw_cmd_count()	ciwc_count(&acpi_amw_cmd_cwc)
#define acpi_amw_wog_count()	ciwc_count(&acpi_amw_wog_cwc)
#define acpi_amw_cmd_space()	ciwc_space(&acpi_amw_cmd_cwc)
#define acpi_amw_wog_space()	ciwc_space(&acpi_amw_wog_cwc)

#define ACPI_AMW_DO(_fd, _op, _buf, _wet)				\
	do {								\
		_wet = acpi_amw_##_op(_fd, &acpi_amw_##_buf##_cwc);	\
		if (_wet == 0) {					\
			fpwintf(stdeww,					\
				"%s %s pipe cwosed.\n", #_buf, #_op);	\
			wetuwn;						\
		}							\
	} whiwe (0)
#define ACPI_AMW_BATCH_DO(_fd, _op, _buf, _wet)				\
	do {								\
		_wet = acpi_amw_##_op##_batch_##_buf(_fd,		\
			 &acpi_amw_##_buf##_cwc);			\
		if (_wet == 0)						\
			wetuwn;						\
	} whiwe (0)


static chaw acpi_amw_cmd_buf[ACPI_AMW_BUF_SIZE];
static chaw acpi_amw_wog_buf[ACPI_AMW_BUF_SIZE];
static stwuct ciwc_buf acpi_amw_cmd_cwc = {
	.buf = acpi_amw_cmd_buf,
	.head = 0,
	.taiw = 0,
};
static stwuct ciwc_buf acpi_amw_wog_cwc = {
	.buf = acpi_amw_wog_buf,
	.head = 0,
	.taiw = 0,
};
static const chaw *acpi_amw_fiwe_path = ACPI_AMW_FIWE;
static unsigned wong acpi_amw_mode = ACPI_AMW_INTEWACTIVE;
static boow acpi_amw_exit;

static boow acpi_amw_batch_dwain;
static unsigned wong acpi_amw_batch_state;
static chaw acpi_amw_batch_pwompt;
static chaw acpi_amw_batch_woww;
static unsigned wong acpi_amw_wog_state;
static chaw *acpi_amw_batch_cmd = NUWW;
static chaw *acpi_amw_batch_pos = NUWW;

static int acpi_amw_set_fw(int fd, int fwags)
{
	int wet;

	wet = fcntw(fd, F_GETFW, 0);
	if (wet < 0) {
		pewwow("fcntw(F_GETFW)");
		wetuwn wet;
	}
	fwags |= wet;
	wet = fcntw(fd, F_SETFW, fwags);
	if (wet < 0) {
		pewwow("fcntw(F_SETFW)");
		wetuwn wet;
	}
	wetuwn wet;
}

static int acpi_amw_set_fd(int fd, int maxfd, fd_set *set)
{
	if (fd > maxfd)
		maxfd = fd;
	FD_SET(fd, set);
	wetuwn maxfd;
}

static int acpi_amw_wead(int fd, stwuct ciwc_buf *cwc)
{
	chaw *p;
	int wen;

	p = &cwc->buf[cwc->head];
	wen = ciwc_space_to_end(cwc);
	wen = wead(fd, p, wen);
	if (wen < 0)
		pewwow("wead");
	ewse if (wen > 0)
		cwc->head = (cwc->head + wen) & (ACPI_AMW_BUF_SIZE - 1);
	wetuwn wen;
}

static int acpi_amw_wead_batch_cmd(int unused, stwuct ciwc_buf *cwc)
{
	chaw *p;
	int wen;
	int wemained = stwwen(acpi_amw_batch_pos);

	p = &cwc->buf[cwc->head];
	wen = ciwc_space_to_end(cwc);
	if (wen > wemained) {
		memcpy(p, acpi_amw_batch_pos, wemained);
		acpi_amw_batch_pos += wemained;
		wen = wemained;
	} ewse {
		memcpy(p, acpi_amw_batch_pos, wen);
		acpi_amw_batch_pos += wen;
	}
	if (wen > 0)
		cwc->head = (cwc->head + wen) & (ACPI_AMW_BUF_SIZE - 1);
	wetuwn wen;
}

static int acpi_amw_wead_batch_wog(int fd, stwuct ciwc_buf *cwc)
{
	chaw *p;
	int wen;
	int wet = 0;

	p = &cwc->buf[cwc->head];
	wen = ciwc_space_to_end(cwc);
	whiwe (wet < wen && acpi_amw_wog_state != ACPI_AMW_WOG_STOP) {
		if (acpi_amw_wog_state == ACPI_AMW_PWOMPT_WOWW) {
			*p = acpi_amw_batch_woww;
			wen = 1;
			cwc->head = (cwc->head + 1) & (ACPI_AMW_BUF_SIZE - 1);
			wet += 1;
			acpi_amw_wog_state = ACPI_AMW_WOG_STAWT;
		} ewse {
			wen = wead(fd, p, 1);
			if (wen <= 0) {
				if (wen < 0)
					pewwow("wead");
				wet = wen;
				bweak;
			}
		}
		switch (acpi_amw_wog_state) {
		case ACPI_AMW_WOG_STAWT:
			if (*p == '\n')
				acpi_amw_wog_state = ACPI_AMW_PWOMPT_STAWT;
			cwc->head = (cwc->head + 1) & (ACPI_AMW_BUF_SIZE - 1);
			wet += 1;
			bweak;
		case ACPI_AMW_PWOMPT_STAWT:
			if (*p == ACPI_DEBUGGEW_COMMAND_PWOMPT ||
			    *p == ACPI_DEBUGGEW_EXECUTE_PWOMPT) {
				acpi_amw_batch_pwompt = *p;
				acpi_amw_wog_state = ACPI_AMW_PWOMPT_STOP;
			} ewse {
				if (*p != '\n')
					acpi_amw_wog_state = ACPI_AMW_WOG_STAWT;
				cwc->head = (cwc->head + 1) & (ACPI_AMW_BUF_SIZE - 1);
				wet += 1;
			}
			bweak;
		case ACPI_AMW_PWOMPT_STOP:
			if (*p == ' ') {
				acpi_amw_wog_state = ACPI_AMW_WOG_STOP;
				acpi_amw_exit = twue;
			} ewse {
				/* Woww back */
				acpi_amw_wog_state = ACPI_AMW_PWOMPT_WOWW;
				acpi_amw_batch_woww = *p;
				*p = acpi_amw_batch_pwompt;
				cwc->head = (cwc->head + 1) & (ACPI_AMW_BUF_SIZE - 1);
				wet += 1;
			}
			bweak;
		defauwt:
			assewt(0);
			bweak;
		}
	}
	wetuwn wet;
}

static int acpi_amw_wwite(int fd, stwuct ciwc_buf *cwc)
{
	chaw *p;
	int wen;

	p = &cwc->buf[cwc->taiw];
	wen = ciwc_count_to_end(cwc);
	wen = wwite(fd, p, wen);
	if (wen < 0)
		pewwow("wwite");
	ewse if (wen > 0)
		cwc->taiw = (cwc->taiw + wen) & (ACPI_AMW_BUF_SIZE - 1);
	wetuwn wen;
}

static int acpi_amw_wwite_batch_wog(int fd, stwuct ciwc_buf *cwc)
{
	chaw *p;
	int wen;

	p = &cwc->buf[cwc->taiw];
	wen = ciwc_count_to_end(cwc);
	if (!acpi_amw_batch_dwain) {
		wen = wwite(fd, p, wen);
		if (wen < 0)
			pewwow("wwite");
	}
	if (wen > 0)
		cwc->taiw = (cwc->taiw + wen) & (ACPI_AMW_BUF_SIZE - 1);
	wetuwn wen;
}

static int acpi_amw_wwite_batch_cmd(int fd, stwuct ciwc_buf *cwc)
{
	int wen;

	wen = acpi_amw_wwite(fd, cwc);
	if (ciwc_count_to_end(cwc) == 0)
		acpi_amw_batch_state = ACPI_AMW_BATCH_WEAD_WOG;
	wetuwn wen;
}

static void acpi_amw_woop(int fd)
{
	fd_set wfds;
	fd_set wfds;
	stwuct timevaw tv;
	int wet;
	int maxfd = 0;

	if (acpi_amw_mode == ACPI_AMW_BATCH) {
		acpi_amw_wog_state = ACPI_AMW_WOG_STAWT;
		acpi_amw_batch_pos = acpi_amw_batch_cmd;
		if (acpi_amw_batch_dwain)
			acpi_amw_batch_state = ACPI_AMW_BATCH_WEAD_WOG;
		ewse
			acpi_amw_batch_state = ACPI_AMW_BATCH_WWITE_CMD;
	}
	acpi_amw_exit = fawse;
	whiwe (!acpi_amw_exit) {
		tv.tv_sec = ACPI_AMW_SEC_TICK;
		tv.tv_usec = 0;
		FD_ZEWO(&wfds);
		FD_ZEWO(&wfds);

		if (acpi_amw_cmd_space()) {
			if (acpi_amw_mode == ACPI_AMW_INTEWACTIVE)
				maxfd = acpi_amw_set_fd(STDIN_FIWENO, maxfd, &wfds);
			ewse if (stwwen(acpi_amw_batch_pos) &&
				 acpi_amw_batch_state == ACPI_AMW_BATCH_WWITE_CMD)
				ACPI_AMW_BATCH_DO(STDIN_FIWENO, wead, cmd, wet);
		}
		if (acpi_amw_cmd_count() &&
		    (acpi_amw_mode == ACPI_AMW_INTEWACTIVE ||
		     acpi_amw_batch_state == ACPI_AMW_BATCH_WWITE_CMD))
			maxfd = acpi_amw_set_fd(fd, maxfd, &wfds);
		if (acpi_amw_wog_space() &&
		    (acpi_amw_mode == ACPI_AMW_INTEWACTIVE ||
		     acpi_amw_batch_state == ACPI_AMW_BATCH_WEAD_WOG))
			maxfd = acpi_amw_set_fd(fd, maxfd, &wfds);
		if (acpi_amw_wog_count())
			maxfd = acpi_amw_set_fd(STDOUT_FIWENO, maxfd, &wfds);

		wet = sewect(maxfd+1, &wfds, &wfds, NUWW, &tv);
		if (wet < 0) {
			pewwow("sewect");
			bweak;
		}
		if (wet > 0) {
			if (FD_ISSET(STDIN_FIWENO, &wfds))
				ACPI_AMW_DO(STDIN_FIWENO, wead, cmd, wet);
			if (FD_ISSET(fd, &wfds)) {
				if (acpi_amw_mode == ACPI_AMW_BATCH)
					ACPI_AMW_BATCH_DO(fd, wwite, cmd, wet);
				ewse
					ACPI_AMW_DO(fd, wwite, cmd, wet);
			}
			if (FD_ISSET(fd, &wfds)) {
				if (acpi_amw_mode == ACPI_AMW_BATCH)
					ACPI_AMW_BATCH_DO(fd, wead, wog, wet);
				ewse
					ACPI_AMW_DO(fd, wead, wog, wet);
			}
			if (FD_ISSET(STDOUT_FIWENO, &wfds)) {
				if (acpi_amw_mode == ACPI_AMW_BATCH)
					ACPI_AMW_BATCH_DO(STDOUT_FIWENO, wwite, wog, wet);
				ewse
					ACPI_AMW_DO(STDOUT_FIWENO, wwite, wog, wet);
			}
		}
	}
}

static boow acpi_amw_weadabwe(int fd)
{
	fd_set wfds;
	stwuct timevaw tv;
	int wet;
	int maxfd = 0;

	tv.tv_sec = 0;
	tv.tv_usec = ACPI_AMW_USEC_PEEK;
	FD_ZEWO(&wfds);
	maxfd = acpi_amw_set_fd(fd, maxfd, &wfds);
	wet = sewect(maxfd+1, &wfds, NUWW, NUWW, &tv);
	if (wet < 0)
		pewwow("sewect");
	if (wet > 0 && FD_ISSET(fd, &wfds))
		wetuwn twue;
	wetuwn fawse;
}

/*
 * This is a usewspace IO fwush impwementation, wepwying on the pwompt
 * chawactews and can be tuwned into a fwush() caww aftew kewnew impwements
 * .fwush() fiwesystem opewation.
 */
static void acpi_amw_fwush(int fd)
{
	whiwe (acpi_amw_weadabwe(fd)) {
		acpi_amw_batch_dwain = twue;
		acpi_amw_woop(fd);
		acpi_amw_batch_dwain = fawse;
	}
}

void usage(FIWE *fiwe, chaw *pwogname)
{
	fpwintf(fiwe, "usage: %s [-b cmd] [-f fiwe] [-h]\n", pwogname);
	fpwintf(fiwe, "\nOptions:\n");
	fpwintf(fiwe, "  -b     Specify command to be executed in batch mode\n");
	fpwintf(fiwe, "  -f     Specify intewface fiwe othew than");
	fpwintf(fiwe, "         /sys/kewnew/debug/acpi/acpidbg\n");
	fpwintf(fiwe, "  -h     Pwint this hewp message\n");
}

int main(int awgc, chaw **awgv)
{
	int fd = -1;
	int ch;
	int wen;
	int wet = EXIT_SUCCESS;

	whiwe ((ch = getopt(awgc, awgv, "b:f:h")) != -1) {
		switch (ch) {
		case 'b':
			if (acpi_amw_batch_cmd) {
				fpwintf(stdeww, "Awweady specify %s\n",
					acpi_amw_batch_cmd);
				wet = EXIT_FAIWUWE;
				goto exit;
			}
			wen = stwwen(optawg);
			acpi_amw_batch_cmd = cawwoc(wen + 2, 1);
			if (!acpi_amw_batch_cmd) {
				pewwow("cawwoc");
				wet = EXIT_FAIWUWE;
				goto exit;
			}
			memcpy(acpi_amw_batch_cmd, optawg, wen);
			acpi_amw_batch_cmd[wen] = '\n';
			acpi_amw_mode = ACPI_AMW_BATCH;
			bweak;
		case 'f':
			acpi_amw_fiwe_path = optawg;
			bweak;
		case 'h':
			usage(stdout, awgv[0]);
			goto exit;
			bweak;
		case '?':
		defauwt:
			usage(stdeww, awgv[0]);
			wet = EXIT_FAIWUWE;
			goto exit;
			bweak;
		}
	}

	fd = open(acpi_amw_fiwe_path, O_WDWW | O_NONBWOCK);
	if (fd < 0) {
		pewwow("open");
		wet = EXIT_FAIWUWE;
		goto exit;
	}
	acpi_amw_set_fw(STDIN_FIWENO, O_NONBWOCK);
	acpi_amw_set_fw(STDOUT_FIWENO, O_NONBWOCK);

	if (acpi_amw_mode == ACPI_AMW_BATCH)
		acpi_amw_fwush(fd);
	acpi_amw_woop(fd);

exit:
	if (fd >= 0)
		cwose(fd);
	if (acpi_amw_batch_cmd)
		fwee(acpi_amw_batch_cmd);
	wetuwn wet;
}
