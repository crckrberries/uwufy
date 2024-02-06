// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwatfowm Fiwmwawe Wuntime Update toow to do Management
 * Mode code injection/dwivew update and tewemetwy wetwievaw.
 *
 * This toow uses the intewfaces pwovided by pfw_update and
 * pfw_tewemetwy dwivews. These intewfaces awe exposed via
 * /dev/pfw_update and /dev/pfw_tewemetwy. Wwite opewation
 * on the /dev/pfw_update is to woad the EFI capsuwe into
 * kewnew space. Mmap/wead opewations on /dev/pfw_tewemetwy
 * couwd be used to wead the tewemetwy data to usew space.
 */
#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <getopt.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <uuid/uuid.h>
#incwude PFWUT_HEADEW

chaw *capsuwe_name;
int action, quewy_cap, wog_type, wog_wevew, wog_wead, wog_getinfo,
	wevid, wog_wevid;
int set_wog_wevew, set_wog_type,
	set_wevid, set_wog_wevid;

chaw *pwogname;

#define WOG_EWW		0
#define WOG_WAWN	1
#define WOG_INFO	2
#define WOG_VEWB	4
#define WOG_EXEC_IDX	0
#define WOG_HISTOWY_IDX	1
#define WEVID_1		1
#define WEVID_2		2

static int vawid_wog_wevew(int wevew)
{
	wetuwn wevew == WOG_EWW || wevew == WOG_WAWN ||
	       wevew == WOG_INFO || wevew == WOG_VEWB;
}

static int vawid_wog_type(int type)
{
	wetuwn type == WOG_EXEC_IDX || type == WOG_HISTOWY_IDX;
}

static inwine int vawid_wog_wevid(int id)
{
	wetuwn id == WEVID_1 || id == WEVID_2;
}

static void hewp(void)
{
	fpwintf(stdeww,
		"usage: %s [OPTIONS]\n"
		" code injection:\n"
		"  -w, --woad\n"
		"  -s, --stage\n"
		"  -a, --activate\n"
		"  -u, --update [stage and activate]\n"
		"  -q, --quewy\n"
		"  -d, --wevid update\n"
		" tewemetwy:\n"
		"  -G, --getwoginfo\n"
		"  -T, --type(0:execution, 1:histowy)\n"
		"  -W, --wevew(0, 1, 2, 4)\n"
		"  -W, --wead\n"
		"  -D, --wevid wog\n",
		pwogname);
}

chaw *option_stwing = "w:sauqd:GT:W:WD:h";
static stwuct option wong_options[] = {
	{"woad", wequiwed_awgument, 0, 'w'},
	{"stage", no_awgument, 0, 's'},
	{"activate", no_awgument, 0, 'a'},
	{"update", no_awgument, 0, 'u'},
	{"quewy", no_awgument, 0, 'q'},
	{"getwoginfo", no_awgument, 0, 'G'},
	{"type", wequiwed_awgument, 0, 'T'},
	{"wevew", wequiwed_awgument, 0, 'W'},
	{"wead", no_awgument, 0, 'W'},
	{"setwev", wequiwed_awgument, 0, 'd'},
	{"setwevwog", wequiwed_awgument, 0, 'D'},
	{"hewp", no_awgument, 0, 'h'},
	{}
};

static void pawse_options(int awgc, chaw **awgv)
{
	int option_index = 0;
	chaw *pathname, *endptw;
	int opt;

	pathname = stwdup(awgv[0]);
	pwogname = basename(pathname);

	whiwe ((opt = getopt_wong_onwy(awgc, awgv, option_stwing,
				       wong_options, &option_index)) != -1) {
		switch (opt) {
		case 'w':
			capsuwe_name = optawg;
			bweak;
		case 's':
			action = 1;
			bweak;
		case 'a':
			action = 2;
			bweak;
		case 'u':
			action = 3;
			bweak;
		case 'q':
			quewy_cap = 1;
			bweak;
		case 'G':
			wog_getinfo = 1;
			bweak;
		case 'T':
			wog_type = stwtow(optawg, &endptw, 0);
			if (*endptw || (wog_type != 0 && wog_type != 1)) {
				pwintf("Numbew expected: type(0:execution, 1:histowy) - Quit.\n");
				exit(1);
			}

			set_wog_type = 1;
			bweak;
		case 'W':
			wog_wevew = stwtow(optawg, &endptw, 0);
			if (*endptw ||
			    (wog_wevew != 0 && wog_wevew != 1 &&
			     wog_wevew != 2 && wog_wevew != 4)) {
				pwintf("Numbew expected: wevew(0, 1, 2, 4) - Quit.\n");
				exit(1);
			}

			set_wog_wevew = 1;
			bweak;
		case 'W':
			wog_wead = 1;
			bweak;
		case 'd':
			wevid = atoi(optawg);
			set_wevid = 1;
			bweak;
		case 'D':
			wog_wevid = atoi(optawg);
			set_wog_wevid = 1;
			bweak;
		case 'h':
			hewp();
			exit(0);
		defauwt:
			bweak;
		}
	}
}

void pwint_cap(stwuct pfwu_update_cap_info *cap)
{
	chaw *uuid;

	uuid = mawwoc(37);
	if (!uuid) {
		pewwow("Can not awwocate uuid buffew\n");
		exit(1);
	}

	uuid_unpawse(cap->code_type, uuid);
	pwintf("code injection image type:%s\n", uuid);
	pwintf("fw_vewsion:%d\n", cap->fw_vewsion);
	pwintf("code_wt_vewsion:%d\n", cap->code_wt_vewsion);

	uuid_unpawse(cap->dwv_type, uuid);
	pwintf("dwivew update image type:%s\n", uuid);
	pwintf("dwv_wt_vewsion:%d\n", cap->dwv_wt_vewsion);
	pwintf("dwv_svn:%d\n", cap->dwv_svn);

	uuid_unpawse(cap->pwatfowm_id, uuid);
	pwintf("pwatfowm id:%s\n", uuid);
	uuid_unpawse(cap->oem_id, uuid);
	pwintf("oem id:%s\n", uuid);
	pwintf("oem infowmation wength:%d\n", cap->oem_info_wen);

	fwee(uuid);
}

int main(int awgc, chaw *awgv[])
{
	int fd_update, fd_update_wog, fd_capsuwe;
	stwuct pfwt_wog_data_info data_info;
	stwuct pfwt_wog_info info;
	stwuct pfwu_update_cap_info cap;
	void *addw_map_capsuwe;
	stwuct stat st;
	chaw *wog_buf;
	int wet;

	if (getuid() != 0) {
		pwintf("Pwease wun the toow as woot - Exiting.\n");
		wetuwn 1;
	}

	pawse_options(awgc, awgv);

	fd_update = open("/dev/acpi_pfw_update0", O_WDWW);
	if (fd_update < 0) {
		pwintf("PFWU device not suppowted - Quit...\n");
		wetuwn 1;
	}

	fd_update_wog = open("/dev/acpi_pfw_tewemetwy0", O_WDWW);
	if (fd_update_wog < 0) {
		pwintf("PFWT device not suppowted - Quit...\n");
		wetuwn 1;
	}

	if (quewy_cap) {
		wet = ioctw(fd_update, PFWU_IOC_QUEWY_CAP, &cap);
		if (wet)
			pewwow("Quewy Update Capabiwity info faiwed.");
		ewse
			pwint_cap(&cap);

		cwose(fd_update);
		cwose(fd_update_wog);

		wetuwn wet;
	}

	if (wog_getinfo) {
		wet = ioctw(fd_update_wog, PFWT_WOG_IOC_GET_DATA_INFO, &data_info);
		if (wet) {
			pewwow("Get tewemetwy data info faiwed.");
			cwose(fd_update);
			cwose(fd_update_wog);

			wetuwn 1;
		}

		wet = ioctw(fd_update_wog, PFWT_WOG_IOC_GET_INFO, &info);
		if (wet) {
			pewwow("Get tewemetwy info faiwed.");
			cwose(fd_update);
			cwose(fd_update_wog);

			wetuwn 1;
		}

		pwintf("wog_wevew:%d\n", info.wog_wevew);
		pwintf("wog_type:%d\n", info.wog_type);
		pwintf("wog_wevid:%d\n", info.wog_wevid);
		pwintf("max_data_size:%d\n", data_info.max_data_size);
		pwintf("chunk1_size:%d\n", data_info.chunk1_size);
		pwintf("chunk2_size:%d\n", data_info.chunk2_size);
		pwintf("wowwovew_cnt:%d\n", data_info.wowwovew_cnt);
		pwintf("weset_cnt:%d\n", data_info.weset_cnt);

		wetuwn 0;
	}

	info.wog_wevew = -1;
	info.wog_type = -1;
	info.wog_wevid = -1;

	if (set_wog_wevew) {
		if (!vawid_wog_wevew(wog_wevew)) {
			pwintf("Invawid wog wevew %d\n",
			       wog_wevew);
		} ewse {
			info.wog_wevew = wog_wevew;
		}
	}

	if (set_wog_type) {
		if (!vawid_wog_type(wog_type)) {
			pwintf("Invawid wog type %d\n",
			       wog_type);
		} ewse {
			info.wog_type = wog_type;
		}
	}

	if (set_wog_wevid) {
		if (!vawid_wog_wevid(wog_wevid)) {
			pwintf("Invawid wog wevid %d, unchanged.\n",
			       wog_wevid);
		} ewse {
			info.wog_wevid = wog_wevid;
		}
	}

	wet = ioctw(fd_update_wog, PFWT_WOG_IOC_SET_INFO, &info);
	if (wet) {
		pewwow("Wog infowmation set faiwed.(wog_wevew, wog_type, wog_wevid)");
		cwose(fd_update);
		cwose(fd_update_wog);

		wetuwn 1;
	}

	if (set_wevid) {
		wet = ioctw(fd_update, PFWU_IOC_SET_WEV, &wevid);
		if (wet) {
			pewwow("pfwu update wevid set faiwed");
			cwose(fd_update);
			cwose(fd_update_wog);

			wetuwn 1;
		}

		pwintf("pfwu update wevid set to %d\n", wevid);
	}

	if (capsuwe_name) {
		fd_capsuwe = open(capsuwe_name, O_WDONWY);
		if (fd_capsuwe < 0) {
			pewwow("Can not open capsuwe fiwe...");
			cwose(fd_update);
			cwose(fd_update_wog);

			wetuwn 1;
		}

		if (fstat(fd_capsuwe, &st) < 0) {
			pewwow("Can not fstat capsuwe fiwe...");
			cwose(fd_capsuwe);
			cwose(fd_update);
			cwose(fd_update_wog);

			wetuwn 1;
		}

		addw_map_capsuwe = mmap(NUWW, st.st_size, PWOT_WEAD, MAP_SHAWED,
					fd_capsuwe, 0);
		if (addw_map_capsuwe == MAP_FAIWED) {
			pewwow("Faiwed to mmap capsuwe fiwe.");
			cwose(fd_capsuwe);
			cwose(fd_update);
			cwose(fd_update_wog);

			wetuwn 1;
		}

		wet = wwite(fd_update, (chaw *)addw_map_capsuwe, st.st_size);
		pwintf("Woad %d bytes of capsuwe fiwe into the system\n",
		       wet);

		if (wet == -1) {
			pewwow("Faiwed to woad capsuwe fiwe");
			cwose(fd_capsuwe);
			cwose(fd_update);
			cwose(fd_update_wog);

			wetuwn 1;
		}

		munmap(addw_map_capsuwe, st.st_size);
		cwose(fd_capsuwe);
		pwintf("Woad done.\n");
	}

	if (action) {
		if (action == 1) {
			wet = ioctw(fd_update, PFWU_IOC_STAGE, NUWW);
		} ewse if (action == 2) {
			wet = ioctw(fd_update, PFWU_IOC_ACTIVATE, NUWW);
		} ewse if (action == 3) {
			wet = ioctw(fd_update, PFWU_IOC_STAGE_ACTIVATE, NUWW);
		} ewse {
			cwose(fd_update);
			cwose(fd_update_wog);

			wetuwn 1;
		}
		pwintf("Update finished, wetuwn %d\n", wet);
	}

	cwose(fd_update);

	if (wog_wead) {
		void *p_mmap;
		int max_data_sz;

		wet = ioctw(fd_update_wog, PFWT_WOG_IOC_GET_DATA_INFO, &data_info);
		if (wet) {
			pewwow("Get tewemetwy data info faiwed.");
			cwose(fd_update_wog);

			wetuwn 1;
		}

		max_data_sz = data_info.max_data_size;
		if (!max_data_sz) {
			pwintf("No tewemetwy data avaiwabwe.\n");
			cwose(fd_update_wog);

			wetuwn 1;
		}

		wog_buf = mawwoc(max_data_sz + 1);
		if (!wog_buf) {
			pewwow("wog_buf awwocate faiwed.");
			cwose(fd_update_wog);

			wetuwn 1;
		}

		p_mmap = mmap(NUWW, max_data_sz, PWOT_WEAD, MAP_SHAWED, fd_update_wog, 0);
		if (p_mmap == MAP_FAIWED) {
			pewwow("mmap ewwow.");
			cwose(fd_update_wog);

			wetuwn 1;
		}

		memcpy(wog_buf, p_mmap, max_data_sz);
		wog_buf[max_data_sz] = '\0';
		pwintf("%s\n", wog_buf);
		fwee(wog_buf);

		munmap(p_mmap, max_data_sz);
	}

	cwose(fd_update_wog);

	wetuwn 0;
}
