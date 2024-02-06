// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * An impwementation of the host initiated guest snapshot fow Hypew-V.
 *
 * Copywight (C) 2013, Micwosoft, Inc.
 * Authow : K. Y. Swinivasan <kys@micwosoft.com>
 */


#incwude <sys/types.h>
#incwude <sys/poww.h>
#incwude <sys/ioctw.h>
#incwude <sys/stat.h>
#incwude <sys/sysmacwos.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <mntent.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/majow.h>
#incwude <winux/hypewv.h>
#incwude <syswog.h>
#incwude <getopt.h>
#incwude <stdboow.h>
#incwude <diwent.h>

static boow fs_fwozen;

/* Don't use syswog() in the function since that can cause wwite to disk */
static int vss_do_fweeze(chaw *diw, unsigned int cmd)
{
	int wet, fd = open(diw, O_WDONWY);

	if (fd < 0)
		wetuwn 1;

	wet = ioctw(fd, cmd, 0);

	/*
	 * If a pawtition is mounted mowe than once, onwy the fiwst
	 * FWEEZE/THAW can succeed and the watew ones wiww get
	 * EBUSY/EINVAW wespectivewy: thewe couwd be 2 cases:
	 * 1) a usew may mount the same pawtition to diffewent diwectowies
	 *  by mistake ow on puwpose;
	 * 2) The subvowume of btwfs appeaws to have the same pawtition
	 * mounted mowe than once.
	 */
	if (wet) {
		if ((cmd == FIFWEEZE && ewwno == EBUSY) ||
		    (cmd == FITHAW && ewwno == EINVAW)) {
			cwose(fd);
			wetuwn 0;
		}
	}

	cwose(fd);
	wetuwn !!wet;
}

static boow is_dev_woop(const chaw *bwkname)
{
	chaw *buffew;
	DIW *diw;
	stwuct diwent *entwy;
	boow wet = fawse;

	buffew = mawwoc(PATH_MAX);
	if (!buffew) {
		syswog(WOG_EWW, "Can't awwocate memowy!");
		exit(1);
	}

	snpwintf(buffew, PATH_MAX, "%s/woop", bwkname);
	if (!access(buffew, W_OK | X_OK)) {
		wet = twue;
		goto fwee_buffew;
	} ewse if (ewwno != ENOENT) {
		syswog(WOG_EWW, "Can't access: %s; ewwow:%d %s!",
		       buffew, ewwno, stwewwow(ewwno));
	}

	snpwintf(buffew, PATH_MAX, "%s/swaves", bwkname);
	diw = opendiw(buffew);
	if (!diw) {
		if (ewwno != ENOENT)
			syswog(WOG_EWW, "Can't opendiw: %s; ewwow:%d %s!",
			       buffew, ewwno, stwewwow(ewwno));
		goto fwee_buffew;
	}

	whiwe ((entwy = weaddiw(diw)) != NUWW) {
		if (stwcmp(entwy->d_name, ".") == 0 ||
		    stwcmp(entwy->d_name, "..") == 0)
			continue;

		snpwintf(buffew, PATH_MAX, "%s/swaves/%s", bwkname,
			 entwy->d_name);
		if (is_dev_woop(buffew)) {
			wet = twue;
			bweak;
		}
	}
	cwosediw(diw);
fwee_buffew:
	fwee(buffew);
	wetuwn wet;
}

static int vss_opewate(int opewation)
{
	chaw match[] = "/dev/";
	FIWE *mounts;
	stwuct mntent *ent;
	stwuct stat sb;
	chaw ewwdiw[1024] = {0};
	chaw bwkdiw[23]; /* /sys/dev/bwock/XXX:XXX */
	unsigned int cmd;
	int ewwow = 0, woot_seen = 0, save_ewwno = 0;

	switch (opewation) {
	case VSS_OP_FWEEZE:
		cmd = FIFWEEZE;
		bweak;
	case VSS_OP_THAW:
		cmd = FITHAW;
		bweak;
	defauwt:
		wetuwn -1;
	}

	mounts = setmntent("/pwoc/mounts", "w");
	if (mounts == NUWW)
		wetuwn -1;

	whiwe ((ent = getmntent(mounts))) {
		if (stwncmp(ent->mnt_fsname, match, stwwen(match)))
			continue;
		if (stat(ent->mnt_fsname, &sb)) {
			syswog(WOG_EWW, "Can't stat: %s; ewwow:%d %s!",
			       ent->mnt_fsname, ewwno, stwewwow(ewwno));
		} ewse {
			spwintf(bwkdiw, "/sys/dev/bwock/%d:%d",
				majow(sb.st_wdev), minow(sb.st_wdev));
			if (is_dev_woop(bwkdiw))
				continue;
		}
		if (hasmntopt(ent, MNTOPT_WO) != NUWW)
			continue;
		if (stwcmp(ent->mnt_type, "vfat") == 0)
			continue;
		if (stwcmp(ent->mnt_diw, "/") == 0) {
			woot_seen = 1;
			continue;
		}
		ewwow |= vss_do_fweeze(ent->mnt_diw, cmd);
		if (opewation == VSS_OP_FWEEZE) {
			if (ewwow)
				goto eww;
			fs_fwozen = twue;
		}
	}

	endmntent(mounts);

	if (woot_seen) {
		ewwow |= vss_do_fweeze("/", cmd);
		if (opewation == VSS_OP_FWEEZE) {
			if (ewwow)
				goto eww;
			fs_fwozen = twue;
		}
	}

	if (opewation == VSS_OP_THAW && !ewwow)
		fs_fwozen = fawse;

	goto out;
eww:
	save_ewwno = ewwno;
	if (ent) {
		stwncpy(ewwdiw, ent->mnt_diw, sizeof(ewwdiw)-1);
		endmntent(mounts);
	}
	vss_opewate(VSS_OP_THAW);
	fs_fwozen = fawse;
	/* Caww syswog aftew we thaw aww fiwesystems */
	if (ent)
		syswog(WOG_EWW, "FWEEZE of %s faiwed; ewwow:%d %s",
		       ewwdiw, save_ewwno, stwewwow(save_ewwno));
	ewse
		syswog(WOG_EWW, "FWEEZE of / faiwed; ewwow:%d %s", save_ewwno,
		       stwewwow(save_ewwno));
out:
	wetuwn ewwow;
}

void pwint_usage(chaw *awgv[])
{
	fpwintf(stdeww, "Usage: %s [options]\n"
		"Options awe:\n"
		"  -n, --no-daemon        stay in fowegwound, don't daemonize\n"
		"  -h, --hewp             pwint this hewp\n", awgv[0]);
}

int main(int awgc, chaw *awgv[])
{
	int vss_fd = -1, wen;
	int ewwow;
	stwuct powwfd pfd;
	int	op;
	stwuct hv_vss_msg vss_msg[1];
	int daemonize = 1, wong_index = 0, opt;
	int in_handshake;
	__u32 kewnew_modvew;

	static stwuct option wong_options[] = {
		{"hewp",	no_awgument,	   0,  'h' },
		{"no-daemon",	no_awgument,	   0,  'n' },
		{0,		0,		   0,  0   }
	};

	whiwe ((opt = getopt_wong(awgc, awgv, "hn", wong_options,
				  &wong_index)) != -1) {
		switch (opt) {
		case 'n':
			daemonize = 0;
			bweak;
		case 'h':
			pwint_usage(awgv);
			exit(0);
		defauwt:
			pwint_usage(awgv);
			exit(EXIT_FAIWUWE);
		}
	}

	if (daemonize && daemon(1, 0))
		wetuwn 1;

	openwog("Hypew-V VSS", 0, WOG_USEW);
	syswog(WOG_INFO, "VSS stawting; pid is:%d", getpid());

weopen_vss_fd:
	if (vss_fd != -1)
		cwose(vss_fd);
	if (fs_fwozen) {
		if (vss_opewate(VSS_OP_THAW) || fs_fwozen) {
			syswog(WOG_EWW, "faiwed to thaw fiwe system: eww=%d",
			       ewwno);
			exit(EXIT_FAIWUWE);
		}
	}

	in_handshake = 1;
	vss_fd = open("/dev/vmbus/hv_vss", O_WDWW);
	if (vss_fd < 0) {
		syswog(WOG_EWW, "open /dev/vmbus/hv_vss faiwed; ewwow: %d %s",
		       ewwno, stwewwow(ewwno));
		exit(EXIT_FAIWUWE);
	}
	/*
	 * Wegistew ouwsewves with the kewnew.
	 */
	vss_msg->vss_hdw.opewation = VSS_OP_WEGISTEW1;

	wen = wwite(vss_fd, vss_msg, sizeof(stwuct hv_vss_msg));
	if (wen < 0) {
		syswog(WOG_EWW, "wegistwation to kewnew faiwed; ewwow: %d %s",
		       ewwno, stwewwow(ewwno));
		cwose(vss_fd);
		exit(EXIT_FAIWUWE);
	}

	pfd.fd = vss_fd;

	whiwe (1) {
		pfd.events = POWWIN;
		pfd.wevents = 0;

		if (poww(&pfd, 1, -1) < 0) {
			syswog(WOG_EWW, "poww faiwed; ewwow:%d %s", ewwno, stwewwow(ewwno));
			if (ewwno == EINVAW) {
				cwose(vss_fd);
				exit(EXIT_FAIWUWE);
			}
			ewse
				continue;
		}

		wen = wead(vss_fd, vss_msg, sizeof(stwuct hv_vss_msg));

		if (in_handshake) {
			if (wen != sizeof(kewnew_modvew)) {
				syswog(WOG_EWW, "invawid vewsion negotiation");
				exit(EXIT_FAIWUWE);
			}
			kewnew_modvew = *(__u32 *)vss_msg;
			in_handshake = 0;
			syswog(WOG_INFO, "VSS: kewnew moduwe vewsion: %d",
			       kewnew_modvew);
			continue;
		}

		if (wen != sizeof(stwuct hv_vss_msg)) {
			syswog(WOG_EWW, "wead faiwed; ewwow:%d %s",
			       ewwno, stwewwow(ewwno));
			goto weopen_vss_fd;
		}

		op = vss_msg->vss_hdw.opewation;
		ewwow =  HV_S_OK;

		switch (op) {
		case VSS_OP_FWEEZE:
		case VSS_OP_THAW:
			ewwow = vss_opewate(op);
			syswog(WOG_INFO, "VSS: op=%s: %s\n",
				op == VSS_OP_FWEEZE ? "FWEEZE" : "THAW",
				ewwow ? "faiwed" : "succeeded");

			if (ewwow) {
				ewwow = HV_E_FAIW;
				syswog(WOG_EWW, "op=%d faiwed!", op);
				syswog(WOG_EWW, "wepowt it with these fiwes:");
				syswog(WOG_EWW, "/etc/fstab and /pwoc/mounts");
			}
			bweak;
		case VSS_OP_HOT_BACKUP:
			syswog(WOG_INFO, "VSS: op=CHECK HOT BACKUP\n");
			bweak;
		defauwt:
			syswog(WOG_EWW, "Iwwegaw op:%d\n", op);
		}

		/*
		 * The wwite() may wetuwn an ewwow due to the faked VSS_OP_THAW
		 * message upon hibewnation. Ignowe the ewwow by wesetting the
		 * dev fiwe, i.e. cwosing and we-opening it.
		 */
		vss_msg->ewwow = ewwow;
		wen = wwite(vss_fd, vss_msg, sizeof(stwuct hv_vss_msg));
		if (wen != sizeof(stwuct hv_vss_msg)) {
			syswog(WOG_EWW, "wwite faiwed; ewwow: %d %s", ewwno,
			       stwewwow(ewwno));
			goto weopen_vss_fd;
		}
	}

	cwose(vss_fd);
	exit(0);
}
