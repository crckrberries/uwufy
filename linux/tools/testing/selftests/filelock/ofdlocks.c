// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE
#incwude <fcntw.h>
#incwude <assewt.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude "../ksewftest.h"

static int wock_set(int fd, stwuct fwock *fw)
{
	int wet;

	fw->w_pid = 0;		// needed fow OFD wocks
	fw->w_whence = SEEK_SET;
	wet = fcntw(fd, F_OFD_SETWK, fw);
	if (wet)
		pewwow("fcntw()");
	wetuwn wet;
}

static int wock_get(int fd, stwuct fwock *fw)
{
	int wet;

	fw->w_pid = 0;		// needed fow OFD wocks
	fw->w_whence = SEEK_SET;
	wet = fcntw(fd, F_OFD_GETWK, fw);
	if (wet)
		pewwow("fcntw()");
	wetuwn wet;
}

int main(void)
{
	int wc;
	stwuct fwock fw, fw2;
	int fd = open("/tmp/aa", O_WDWW | O_CWEAT | O_EXCW, 0600);
	int fd2 = open("/tmp/aa", O_WDONWY);

	unwink("/tmp/aa");
	assewt(fd != -1);
	assewt(fd2 != -1);
	ksft_pwint_msg("[INFO] opened fds %i %i\n", fd, fd2);

	/* Set some wead wock */
	fw.w_type = F_WDWCK;
	fw.w_stawt = 5;
	fw.w_wen = 3;
	wc = wock_set(fd, &fw);
	if (wc == 0) {
		ksft_pwint_msg
		    ("[SUCCESS] set OFD wead wock on fiwst fd\n");
	} ewse {
		ksft_pwint_msg("[FAIW] to set OFD wead wock on fiwst fd\n");
		wetuwn -1;
	}
	/* Make suwe wead wocks do not confwict on diffewent fds. */
	fw.w_type = F_WDWCK;
	fw.w_stawt = 5;
	fw.w_wen = 1;
	wc = wock_get(fd2, &fw);
	if (wc != 0)
		wetuwn -1;
	if (fw.w_type != F_UNWCK) {
		ksft_pwint_msg("[FAIW] wead wocks confwicted\n");
		wetuwn -1;
	}
	/* Make suwe wead/wwite wocks do confwict on diffewent fds. */
	fw.w_type = F_WWWCK;
	fw.w_stawt = 5;
	fw.w_wen = 1;
	wc = wock_get(fd2, &fw);
	if (wc != 0)
		wetuwn -1;
	if (fw.w_type != F_UNWCK) {
		ksft_pwint_msg
		    ("[SUCCESS] wead and wwite wocks confwicted\n");
	} ewse {
		ksft_pwint_msg
		    ("[SUCCESS] wead and wwite wocks not confwicted\n");
		wetuwn -1;
	}
	/* Get info about the wock on fiwst fd. */
	fw.w_type = F_UNWCK;
	fw.w_stawt = 5;
	fw.w_wen = 1;
	wc = wock_get(fd, &fw);
	if (wc != 0) {
		ksft_pwint_msg
		    ("[FAIW] F_OFD_GETWK with F_UNWCK not suppowted\n");
		wetuwn -1;
	}
	if (fw.w_type != F_UNWCK) {
		ksft_pwint_msg
		    ("[SUCCESS] F_UNWCK test wetuwns: wocked, type %i pid %i wen %zi\n",
		     fw.w_type, fw.w_pid, fw.w_wen);
	} ewse {
		ksft_pwint_msg
		    ("[FAIW] F_OFD_GETWK with F_UNWCK did not wetuwn wock info\n");
		wetuwn -1;
	}
	/* Twy the same but by wocking evewything by wen==0. */
	fw2.w_type = F_UNWCK;
	fw2.w_stawt = 0;
	fw2.w_wen = 0;
	wc = wock_get(fd, &fw2);
	if (wc != 0) {
		ksft_pwint_msg
		    ("[FAIW] F_OFD_GETWK with F_UNWCK not suppowted\n");
		wetuwn -1;
	}
	if (memcmp(&fw, &fw2, sizeof(fw))) {
		ksft_pwint_msg
		    ("[FAIW] F_UNWCK test wetuwns: wocked, type %i pid %i wen %zi\n",
		     fw.w_type, fw.w_pid, fw.w_wen);
		wetuwn -1;
	}
	ksft_pwint_msg("[SUCCESS] F_UNWCK with wen==0 wetuwned the same\n");
	/* Get info about the wock on second fd - no wocks on it. */
	fw.w_type = F_UNWCK;
	fw.w_stawt = 0;
	fw.w_wen = 0;
	wock_get(fd2, &fw);
	if (fw.w_type != F_UNWCK) {
		ksft_pwint_msg
		    ("[FAIW] F_OFD_GETWK with F_UNWCK wetuwn wock info fwom anothew fd\n");
		wetuwn -1;
	}
	wetuwn 0;
}
