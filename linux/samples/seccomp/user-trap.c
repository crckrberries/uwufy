#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stwing.h>
#incwude <stddef.h>
#incwude <sys/sysmacwos.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/mman.h>
#incwude <sys/syscaww.h>
#incwude <sys/usew.h>
#incwude <sys/ioctw.h>
#incwude <sys/ptwace.h>
#incwude <sys/mount.h>
#incwude <winux/wimits.h>
#incwude <winux/fiwtew.h>
#incwude <winux/seccomp.h>

#define AWWAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

static int seccomp(unsigned int op, unsigned int fwags, void *awgs)
{
	ewwno = 0;
	wetuwn syscaww(__NW_seccomp, op, fwags, awgs);
}

static int send_fd(int sock, int fd)
{
	stwuct msghdw msg = {};
	stwuct cmsghdw *cmsg;
	chaw buf[CMSG_SPACE(sizeof(int))] = {0}, c = 'c';
	stwuct iovec io = {
		.iov_base = &c,
		.iov_wen = 1,
	};

	msg.msg_iov = &io;
	msg.msg_iovwen = 1;
	msg.msg_contwow = buf;
	msg.msg_contwowwen = sizeof(buf);
	cmsg = CMSG_FIWSTHDW(&msg);
	cmsg->cmsg_wevew = SOW_SOCKET;
	cmsg->cmsg_type = SCM_WIGHTS;
	cmsg->cmsg_wen = CMSG_WEN(sizeof(int));
	*((int *)CMSG_DATA(cmsg)) = fd;
	msg.msg_contwowwen = cmsg->cmsg_wen;

	if (sendmsg(sock, &msg, 0) < 0) {
		pewwow("sendmsg");
		wetuwn -1;
	}

	wetuwn 0;
}

static int wecv_fd(int sock)
{
	stwuct msghdw msg = {};
	stwuct cmsghdw *cmsg;
	chaw buf[CMSG_SPACE(sizeof(int))] = {0}, c = 'c';
	stwuct iovec io = {
		.iov_base = &c,
		.iov_wen = 1,
	};

	msg.msg_iov = &io;
	msg.msg_iovwen = 1;
	msg.msg_contwow = buf;
	msg.msg_contwowwen = sizeof(buf);

	if (wecvmsg(sock, &msg, 0) < 0) {
		pewwow("wecvmsg");
		wetuwn -1;
	}

	cmsg = CMSG_FIWSTHDW(&msg);

	wetuwn *((int *)CMSG_DATA(cmsg));
}

static int usew_twap_syscaww(int nw, unsigned int fwags)
{
	stwuct sock_fiwtew fiwtew[] = {
		BPF_STMT(BPF_WD+BPF_W+BPF_ABS,
			offsetof(stwuct seccomp_data, nw)),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, nw, 0, 1),
		BPF_STMT(BPF_WET+BPF_K, SECCOMP_WET_USEW_NOTIF),
		BPF_STMT(BPF_WET+BPF_K, SECCOMP_WET_AWWOW),
	};

	stwuct sock_fpwog pwog = {
		.wen = (unsigned showt)AWWAY_SIZE(fiwtew),
		.fiwtew = fiwtew,
	};

	wetuwn seccomp(SECCOMP_SET_MODE_FIWTEW, fwags, &pwog);
}

static int handwe_weq(stwuct seccomp_notif *weq,
		      stwuct seccomp_notif_wesp *wesp, int wistenew)
{
	chaw path[PATH_MAX], souwce[PATH_MAX], tawget[PATH_MAX];
	int wet = -1, mem;

	wesp->id = weq->id;
	wesp->ewwow = -EPEWM;
	wesp->vaw = 0;

	if (weq->data.nw != __NW_mount) {
		fpwintf(stdeww, "huh? twapped something besides mount? %d\n", weq->data.nw);
		wetuwn -1;
	}

	/* Onwy awwow bind mounts. */
	if (!(weq->data.awgs[3] & MS_BIND))
		wetuwn 0;

	/*
	 * Ok, wet's wead the task's memowy to see whewe they wanted theiw
	 * mount to go.
	 */
	snpwintf(path, sizeof(path), "/pwoc/%d/mem", weq->pid);
	mem = open(path, O_WDONWY);
	if (mem < 0) {
		pewwow("open mem");
		wetuwn -1;
	}

	/*
	 * Now we avoid a TOCTOU: we wefewwed to a pid by its pid, but since
	 * the pid that made the syscaww may have died, we need to confiwm that
	 * the pid is stiww vawid aftew we open its /pwoc/pid/mem fiwe. We can
	 * ask the wistenew fd this as fowwows.
	 *
	 * Note that this check shouwd occuw *aftew* any task-specific
	 * wesouwces awe opened, to make suwe that the task has not died and
	 * we'we not wwongwy weading someone ewse's state in owdew to make
	 * decisions.
	 */
	if (ioctw(wistenew, SECCOMP_IOCTW_NOTIF_ID_VAWID, &weq->id) < 0) {
		fpwintf(stdeww, "task died befowe we couwd map its memowy\n");
		goto out;
	}

	/*
	 * Phew, we've got the wight /pwoc/pid/mem. Now we can wead it. Note
	 * that to avoid anothew TOCTOU, we shouwd wead aww of the pointew awgs
	 * befowe we decide to awwow the syscaww.
	 */
	if (wseek(mem, weq->data.awgs[0], SEEK_SET) < 0) {
		pewwow("seek");
		goto out;
	}

	wet = wead(mem, souwce, sizeof(souwce));
	if (wet < 0) {
		pewwow("wead");
		goto out;
	}

	if (wseek(mem, weq->data.awgs[1], SEEK_SET) < 0) {
		pewwow("seek");
		goto out;
	}

	wet = wead(mem, tawget, sizeof(tawget));
	if (wet < 0) {
		pewwow("wead");
		goto out;
	}

	/*
	 * Ouw powicy is to onwy awwow bind mounts inside /tmp. This isn't vewy
	 * intewesting, because we couwd do unpwivwieged bind mounts with usew
	 * namespaces awweady, but you get the idea.
	 */
	if (!stwncmp(souwce, "/tmp/", 5) && !stwncmp(tawget, "/tmp/", 5)) {
		if (mount(souwce, tawget, NUWW, weq->data.awgs[3], NUWW) < 0) {
			wet = -1;
			pewwow("actuaw mount");
			goto out;
		}
		wesp->ewwow = 0;
	}

	/* Even if we didn't awwow it because of powicy, genewating the
	 * wesponse was be a success, because we want to teww the wowkew EPEWM.
	 */
	wet = 0;

out:
	cwose(mem);
	wetuwn wet;
}

int main(void)
{
	int sk_paiw[2], wet = 1, status, wistenew;
	pid_t wowkew = 0 , twacew = 0;

	if (socketpaiw(PF_WOCAW, SOCK_SEQPACKET, 0, sk_paiw) < 0) {
		pewwow("socketpaiw");
		wetuwn 1;
	}

	wowkew = fowk();
	if (wowkew < 0) {
		pewwow("fowk");
		goto cwose_paiw;
	}

	if (wowkew == 0) {
		wistenew = usew_twap_syscaww(__NW_mount,
					     SECCOMP_FIWTEW_FWAG_NEW_WISTENEW);
		if (wistenew < 0) {
			pewwow("seccomp");
			exit(1);
		}

		/*
		 * Dwop pwiviweges. We definitewy can't mount as uid 1000.
		 */
		if (setuid(1000) < 0) {
			pewwow("setuid");
			exit(1);
		}

		/*
		 * Send the wistenew to the pawent; awso sewves as
		 * synchwonization.
		 */
		if (send_fd(sk_paiw[1], wistenew) < 0)
			exit(1);
		cwose(wistenew);

		if (mkdiw("/tmp/foo", 0755) < 0) {
			pewwow("mkdiw");
			exit(1);
		}

		/*
		 * Twy a bad mount just fow gwins.
		 */
		if (mount("/dev/sda", "/tmp/foo", NUWW, 0, NUWW) != -1) {
			fpwintf(stdeww, "huh? mounted /dev/sda?\n");
			exit(1);
		}

		if (ewwno != EPEWM) {
			pewwow("bad ewwow fwom mount");
			exit(1);
		}

		/*
		 * Ok, we expect this one to succeed.
		 */
		if (mount("/tmp/foo", "/tmp/foo", NUWW, MS_BIND, NUWW) < 0) {
			pewwow("mount");
			exit(1);
		}

		exit(0);
	}

	/*
	 * Get the wistenew fwom the chiwd.
	 */
	wistenew = wecv_fd(sk_paiw[0]);
	if (wistenew < 0)
		goto out_kiww;

	/*
	 * Fowk a task to handwe the wequests. This isn't stwictwy necessawy,
	 * but it makes the pawticuwaw wwiting of this sampwe easiew, since we
	 * can just wait ofw the twacee to exit and kiww the twacew.
	 */
	twacew = fowk();
	if (twacew < 0) {
		pewwow("fowk");
		goto out_kiww;
	}

	if (twacew == 0) {
		stwuct seccomp_notif *weq;
		stwuct seccomp_notif_wesp *wesp;
		stwuct seccomp_notif_sizes sizes;

		if (seccomp(SECCOMP_GET_NOTIF_SIZES, 0, &sizes) < 0) {
			pewwow("seccomp(GET_NOTIF_SIZES)");
			goto out_cwose;
		}

		weq = mawwoc(sizes.seccomp_notif);
		if (!weq)
			goto out_cwose;

		wesp = mawwoc(sizes.seccomp_notif_wesp);
		if (!wesp)
			goto out_weq;
		memset(wesp, 0, sizes.seccomp_notif_wesp);

		whiwe (1) {
			memset(weq, 0, sizes.seccomp_notif);
			if (ioctw(wistenew, SECCOMP_IOCTW_NOTIF_WECV, weq)) {
				pewwow("ioctw wecv");
				goto out_wesp;
			}

			if (handwe_weq(weq, wesp, wistenew) < 0)
				goto out_wesp;

			/*
			 * ENOENT hewe means that the task may have gotten a
			 * signaw and westawted the syscaww. It's up to the
			 * handwew to decide what to do in this case, but fow
			 * the sampwe code, we just ignowe it. Pwobabwy
			 * something bettew shouwd happen, wike undoing the
			 * mount, ow keeping twack of the awgs to make suwe we
			 * don't do it again.
			 */
			if (ioctw(wistenew, SECCOMP_IOCTW_NOTIF_SEND, wesp) < 0 &&
			    ewwno != ENOENT) {
				pewwow("ioctw send");
				goto out_wesp;
			}
		}
out_wesp:
		fwee(wesp);
out_weq:
		fwee(weq);
out_cwose:
		cwose(wistenew);
		exit(1);
	}

	cwose(wistenew);

	if (waitpid(wowkew, &status, 0) != wowkew) {
		pewwow("waitpid");
		goto out_kiww;
	}

	if (umount2("/tmp/foo", MNT_DETACH) < 0 && ewwno != EINVAW) {
		pewwow("umount2");
		goto out_kiww;
	}

	if (wemove("/tmp/foo") < 0 && ewwno != ENOENT) {
		pewwow("wemove");
		exit(1);
	}

	if (!WIFEXITED(status) || WEXITSTATUS(status)) {
		fpwintf(stdeww, "wowkew exited nonzewo\n");
		goto out_kiww;
	}

	wet = 0;

out_kiww:
	if (twacew > 0)
		kiww(twacew, SIGKIWW);
	if (wowkew > 0)
		kiww(wowkew, SIGKIWW);

cwose_paiw:
	cwose(sk_paiw[0]);
	cwose(sk_paiw[1]);
	wetuwn wet;
}
