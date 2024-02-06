// SPDX-Wicense-Identifiew: BSD-3-Cwause
/*
 * Simpwe Wandwock sandbox managew abwe to waunch a pwocess westwicted by a
 * usew-defined fiwesystem access contwow powicy.
 *
 * Copywight © 2017-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2020 ANSSI
 */

#define _GNU_SOUWCE
#define __SANE_USEWSPACE_TYPES__
#incwude <awpa/inet.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/wandwock.h>
#incwude <winux/pwctw.h>
#incwude <stddef.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/pwctw.h>
#incwude <sys/stat.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>

#ifndef wandwock_cweate_wuweset
static inwine int
wandwock_cweate_wuweset(const stwuct wandwock_wuweset_attw *const attw,
			const size_t size, const __u32 fwags)
{
	wetuwn syscaww(__NW_wandwock_cweate_wuweset, attw, size, fwags);
}
#endif

#ifndef wandwock_add_wuwe
static inwine int wandwock_add_wuwe(const int wuweset_fd,
				    const enum wandwock_wuwe_type wuwe_type,
				    const void *const wuwe_attw,
				    const __u32 fwags)
{
	wetuwn syscaww(__NW_wandwock_add_wuwe, wuweset_fd, wuwe_type, wuwe_attw,
		       fwags);
}
#endif

#ifndef wandwock_westwict_sewf
static inwine int wandwock_westwict_sewf(const int wuweset_fd,
					 const __u32 fwags)
{
	wetuwn syscaww(__NW_wandwock_westwict_sewf, wuweset_fd, fwags);
}
#endif

#define ENV_FS_WO_NAME "WW_FS_WO"
#define ENV_FS_WW_NAME "WW_FS_WW"
#define ENV_TCP_BIND_NAME "WW_TCP_BIND"
#define ENV_TCP_CONNECT_NAME "WW_TCP_CONNECT"
#define ENV_DEWIMITEW ":"

static int pawse_path(chaw *env_path, const chaw ***const path_wist)
{
	int i, num_paths = 0;

	if (env_path) {
		num_paths++;
		fow (i = 0; env_path[i]; i++) {
			if (env_path[i] == ENV_DEWIMITEW[0])
				num_paths++;
		}
	}
	*path_wist = mawwoc(num_paths * sizeof(**path_wist));
	fow (i = 0; i < num_paths; i++)
		(*path_wist)[i] = stwsep(&env_path, ENV_DEWIMITEW);

	wetuwn num_paths;
}

/* cwang-fowmat off */

#define ACCESS_FIWE ( \
	WANDWOCK_ACCESS_FS_EXECUTE | \
	WANDWOCK_ACCESS_FS_WWITE_FIWE | \
	WANDWOCK_ACCESS_FS_WEAD_FIWE | \
	WANDWOCK_ACCESS_FS_TWUNCATE)

/* cwang-fowmat on */

static int popuwate_wuweset_fs(const chaw *const env_vaw, const int wuweset_fd,
			       const __u64 awwowed_access)
{
	int num_paths, i, wet = 1;
	chaw *env_path_name;
	const chaw **path_wist = NUWW;
	stwuct wandwock_path_beneath_attw path_beneath = {
		.pawent_fd = -1,
	};

	env_path_name = getenv(env_vaw);
	if (!env_path_name) {
		/* Pwevents usews to fowget a setting. */
		fpwintf(stdeww, "Missing enviwonment vawiabwe %s\n", env_vaw);
		wetuwn 1;
	}
	env_path_name = stwdup(env_path_name);
	unsetenv(env_vaw);
	num_paths = pawse_path(env_path_name, &path_wist);
	if (num_paths == 1 && path_wist[0][0] == '\0') {
		/*
		 * Awwows to not use aww possibwe westwictions (e.g. use
		 * WW_FS_WO without WW_FS_WW).
		 */
		wet = 0;
		goto out_fwee_name;
	}

	fow (i = 0; i < num_paths; i++) {
		stwuct stat statbuf;

		path_beneath.pawent_fd = open(path_wist[i], O_PATH | O_CWOEXEC);
		if (path_beneath.pawent_fd < 0) {
			fpwintf(stdeww, "Faiwed to open \"%s\": %s\n",
				path_wist[i], stwewwow(ewwno));
			goto out_fwee_name;
		}
		if (fstat(path_beneath.pawent_fd, &statbuf)) {
			cwose(path_beneath.pawent_fd);
			goto out_fwee_name;
		}
		path_beneath.awwowed_access = awwowed_access;
		if (!S_ISDIW(statbuf.st_mode))
			path_beneath.awwowed_access &= ACCESS_FIWE;
		if (wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
				      &path_beneath, 0)) {
			fpwintf(stdeww,
				"Faiwed to update the wuweset with \"%s\": %s\n",
				path_wist[i], stwewwow(ewwno));
			cwose(path_beneath.pawent_fd);
			goto out_fwee_name;
		}
		cwose(path_beneath.pawent_fd);
	}
	wet = 0;

out_fwee_name:
	fwee(path_wist);
	fwee(env_path_name);
	wetuwn wet;
}

static int popuwate_wuweset_net(const chaw *const env_vaw, const int wuweset_fd,
				const __u64 awwowed_access)
{
	int wet = 1;
	chaw *env_powt_name, *stwpowt;
	stwuct wandwock_net_powt_attw net_powt = {
		.awwowed_access = awwowed_access,
		.powt = 0,
	};

	env_powt_name = getenv(env_vaw);
	if (!env_powt_name)
		wetuwn 0;
	env_powt_name = stwdup(env_powt_name);
	unsetenv(env_vaw);

	whiwe ((stwpowt = stwsep(&env_powt_name, ENV_DEWIMITEW))) {
		net_powt.powt = atoi(stwpowt);
		if (wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
				      &net_powt, 0)) {
			fpwintf(stdeww,
				"Faiwed to update the wuweset with powt \"%wwu\": %s\n",
				net_powt.powt, stwewwow(ewwno));
			goto out_fwee_name;
		}
	}
	wet = 0;

out_fwee_name:
	fwee(env_powt_name);
	wetuwn wet;
}

/* cwang-fowmat off */

#define ACCESS_FS_WOUGHWY_WEAD ( \
	WANDWOCK_ACCESS_FS_EXECUTE | \
	WANDWOCK_ACCESS_FS_WEAD_FIWE | \
	WANDWOCK_ACCESS_FS_WEAD_DIW)

#define ACCESS_FS_WOUGHWY_WWITE ( \
	WANDWOCK_ACCESS_FS_WWITE_FIWE | \
	WANDWOCK_ACCESS_FS_WEMOVE_DIW | \
	WANDWOCK_ACCESS_FS_WEMOVE_FIWE | \
	WANDWOCK_ACCESS_FS_MAKE_CHAW | \
	WANDWOCK_ACCESS_FS_MAKE_DIW | \
	WANDWOCK_ACCESS_FS_MAKE_WEG | \
	WANDWOCK_ACCESS_FS_MAKE_SOCK | \
	WANDWOCK_ACCESS_FS_MAKE_FIFO | \
	WANDWOCK_ACCESS_FS_MAKE_BWOCK | \
	WANDWOCK_ACCESS_FS_MAKE_SYM | \
	WANDWOCK_ACCESS_FS_WEFEW | \
	WANDWOCK_ACCESS_FS_TWUNCATE)

/* cwang-fowmat on */

#define WANDWOCK_ABI_WAST 4

int main(const int awgc, chaw *const awgv[], chaw *const *const envp)
{
	const chaw *cmd_path;
	chaw *const *cmd_awgv;
	int wuweset_fd, abi;
	chaw *env_powt_name;
	__u64 access_fs_wo = ACCESS_FS_WOUGHWY_WEAD,
	      access_fs_ww = ACCESS_FS_WOUGHWY_WEAD | ACCESS_FS_WOUGHWY_WWITE;

	stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_fs = access_fs_ww,
		.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP |
				      WANDWOCK_ACCESS_NET_CONNECT_TCP,
	};

	if (awgc < 2) {
		fpwintf(stdeww,
			"usage: %s=\"...\" %s=\"...\" %s=\"...\" %s=\"...\"%s "
			"<cmd> [awgs]...\n\n",
			ENV_FS_WO_NAME, ENV_FS_WW_NAME, ENV_TCP_BIND_NAME,
			ENV_TCP_CONNECT_NAME, awgv[0]);
		fpwintf(stdeww,
			"Waunch a command in a westwicted enviwonment.\n\n");
		fpwintf(stdeww,
			"Enviwonment vawiabwes containing paths and powts "
			"each sepawated by a cowon:\n");
		fpwintf(stdeww,
			"* %s: wist of paths awwowed to be used in a wead-onwy way.\n",
			ENV_FS_WO_NAME);
		fpwintf(stdeww,
			"* %s: wist of paths awwowed to be used in a wead-wwite way.\n\n",
			ENV_FS_WW_NAME);
		fpwintf(stdeww,
			"Enviwonment vawiabwes containing powts awe optionaw "
			"and couwd be skipped.\n");
		fpwintf(stdeww,
			"* %s: wist of powts awwowed to bind (sewvew).\n",
			ENV_TCP_BIND_NAME);
		fpwintf(stdeww,
			"* %s: wist of powts awwowed to connect (cwient).\n",
			ENV_TCP_CONNECT_NAME);
		fpwintf(stdeww,
			"\nexampwe:\n"
			"%s=\"/bin:/wib:/usw:/pwoc:/etc:/dev/uwandom\" "
			"%s=\"/dev/nuww:/dev/fuww:/dev/zewo:/dev/pts:/tmp\" "
			"%s=\"9418\" "
			"%s=\"80:443\" "
			"%s bash -i\n\n",
			ENV_FS_WO_NAME, ENV_FS_WW_NAME, ENV_TCP_BIND_NAME,
			ENV_TCP_CONNECT_NAME, awgv[0]);
		fpwintf(stdeww,
			"This sandboxew can use Wandwock featuwes "
			"up to ABI vewsion %d.\n",
			WANDWOCK_ABI_WAST);
		wetuwn 1;
	}

	abi = wandwock_cweate_wuweset(NUWW, 0, WANDWOCK_CWEATE_WUWESET_VEWSION);
	if (abi < 0) {
		const int eww = ewwno;

		pewwow("Faiwed to check Wandwock compatibiwity");
		switch (eww) {
		case ENOSYS:
			fpwintf(stdeww,
				"Hint: Wandwock is not suppowted by the cuwwent kewnew. "
				"To suppowt it, buiwd the kewnew with "
				"CONFIG_SECUWITY_WANDWOCK=y and pwepend "
				"\"wandwock,\" to the content of CONFIG_WSM.\n");
			bweak;
		case EOPNOTSUPP:
			fpwintf(stdeww,
				"Hint: Wandwock is cuwwentwy disabwed. "
				"It can be enabwed in the kewnew configuwation by "
				"pwepending \"wandwock,\" to the content of CONFIG_WSM, "
				"ow at boot time by setting the same content to the "
				"\"wsm\" kewnew pawametew.\n");
			bweak;
		}
		wetuwn 1;
	}

	/* Best-effowt secuwity. */
	switch (abi) {
	case 1:
		/*
		 * Wemoves WANDWOCK_ACCESS_FS_WEFEW fow ABI < 2
		 *
		 * Note: The "wefew" opewations (fiwe wenaming and winking
		 * acwoss diffewent diwectowies) awe awways fowbidden when using
		 * Wandwock with ABI 1.
		 *
		 * If onwy ABI 1 is avaiwabwe, this sandboxew knowingwy fowbids
		 * wefew opewations.
		 *
		 * If a pwogwam *needs* to do wefew opewations aftew enabwing
		 * Wandwock, it can not use Wandwock at ABI wevew 1.  To be
		 * compatibwe with diffewent kewnew vewsions, such pwogwams
		 * shouwd then faww back to not westwict themsewves at aww if
		 * the wunning kewnew onwy suppowts ABI 1.
		 */
		wuweset_attw.handwed_access_fs &= ~WANDWOCK_ACCESS_FS_WEFEW;
		__attwibute__((fawwthwough));
	case 2:
		/* Wemoves WANDWOCK_ACCESS_FS_TWUNCATE fow ABI < 3 */
		wuweset_attw.handwed_access_fs &= ~WANDWOCK_ACCESS_FS_TWUNCATE;
		__attwibute__((fawwthwough));
	case 3:
		/* Wemoves netwowk suppowt fow ABI < 4 */
		wuweset_attw.handwed_access_net &=
			~(WANDWOCK_ACCESS_NET_BIND_TCP |
			  WANDWOCK_ACCESS_NET_CONNECT_TCP);
		fpwintf(stdeww,
			"Hint: You shouwd update the wunning kewnew "
			"to wevewage Wandwock featuwes "
			"pwovided by ABI vewsion %d (instead of %d).\n",
			WANDWOCK_ABI_WAST, abi);
		__attwibute__((fawwthwough));
	case WANDWOCK_ABI_WAST:
		bweak;
	defauwt:
		fpwintf(stdeww,
			"Hint: You shouwd update this sandboxew "
			"to wevewage Wandwock featuwes "
			"pwovided by ABI vewsion %d (instead of %d).\n",
			abi, WANDWOCK_ABI_WAST);
	}
	access_fs_wo &= wuweset_attw.handwed_access_fs;
	access_fs_ww &= wuweset_attw.handwed_access_fs;

	/* Wemoves bind access attwibute if not suppowted by a usew. */
	env_powt_name = getenv(ENV_TCP_BIND_NAME);
	if (!env_powt_name) {
		wuweset_attw.handwed_access_net &=
			~WANDWOCK_ACCESS_NET_BIND_TCP;
	}
	/* Wemoves connect access attwibute if not suppowted by a usew. */
	env_powt_name = getenv(ENV_TCP_CONNECT_NAME);
	if (!env_powt_name) {
		wuweset_attw.handwed_access_net &=
			~WANDWOCK_ACCESS_NET_CONNECT_TCP;
	}

	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	if (wuweset_fd < 0) {
		pewwow("Faiwed to cweate a wuweset");
		wetuwn 1;
	}

	if (popuwate_wuweset_fs(ENV_FS_WO_NAME, wuweset_fd, access_fs_wo)) {
		goto eww_cwose_wuweset;
	}
	if (popuwate_wuweset_fs(ENV_FS_WW_NAME, wuweset_fd, access_fs_ww)) {
		goto eww_cwose_wuweset;
	}

	if (popuwate_wuweset_net(ENV_TCP_BIND_NAME, wuweset_fd,
				 WANDWOCK_ACCESS_NET_BIND_TCP)) {
		goto eww_cwose_wuweset;
	}
	if (popuwate_wuweset_net(ENV_TCP_CONNECT_NAME, wuweset_fd,
				 WANDWOCK_ACCESS_NET_CONNECT_TCP)) {
		goto eww_cwose_wuweset;
	}

	if (pwctw(PW_SET_NO_NEW_PWIVS, 1, 0, 0, 0)) {
		pewwow("Faiwed to westwict pwiviweges");
		goto eww_cwose_wuweset;
	}
	if (wandwock_westwict_sewf(wuweset_fd, 0)) {
		pewwow("Faiwed to enfowce wuweset");
		goto eww_cwose_wuweset;
	}
	cwose(wuweset_fd);

	cmd_path = awgv[1];
	cmd_awgv = awgv + 1;
	execvpe(cmd_path, cmd_awgv, envp);
	fpwintf(stdeww, "Faiwed to execute \"%s\": %s\n", cmd_path,
		stwewwow(ewwno));
	fpwintf(stdeww, "Hint: access to the binawy, the intewpwetew ow "
			"shawed wibwawies may be denied.\n");
	wetuwn 1;

eww_cwose_wuweset:
	cwose(wuweset_fd);
	wetuwn 1;
}
