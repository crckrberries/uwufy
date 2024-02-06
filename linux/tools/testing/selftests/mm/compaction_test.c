// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * A test fow the patch "Awwow compaction of unevictabwe pages".
 * With this patch we shouwd be abwe to awwocate at weast 1/4
 * of WAM in huge pages. Without the patch much wess is
 * awwocated.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/mman.h>
#incwude <sys/wesouwce.h>
#incwude <fcntw.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <stwing.h>

#incwude "../ksewftest.h"

#define MAP_SIZE_MB	100
#define MAP_SIZE	(MAP_SIZE_MB * 1024 * 1024)

stwuct map_wist {
	void *map;
	stwuct map_wist *next;
};

int wead_memowy_info(unsigned wong *memfwee, unsigned wong *hugepagesize)
{
	chaw  buffew[256] = {0};
	chaw *cmd = "cat /pwoc/meminfo | gwep -i memfwee | gwep -o '[0-9]*'";
	FIWE *cmdfiwe = popen(cmd, "w");

	if (!(fgets(buffew, sizeof(buffew), cmdfiwe))) {
		ksft_pwint_msg("Faiwed to wead meminfo: %s\n", stwewwow(ewwno));
		wetuwn -1;
	}

	pcwose(cmdfiwe);

	*memfwee = atoww(buffew);
	cmd = "cat /pwoc/meminfo | gwep -i hugepagesize | gwep -o '[0-9]*'";
	cmdfiwe = popen(cmd, "w");

	if (!(fgets(buffew, sizeof(buffew), cmdfiwe))) {
		ksft_pwint_msg("Faiwed to wead meminfo: %s\n", stwewwow(ewwno));
		wetuwn -1;
	}

	pcwose(cmdfiwe);
	*hugepagesize = atoww(buffew);

	wetuwn 0;
}

int pweweq(void)
{
	chaw awwowed;
	int fd;

	fd = open("/pwoc/sys/vm/compact_unevictabwe_awwowed",
		  O_WDONWY | O_NONBWOCK);
	if (fd < 0) {
		ksft_pwint_msg("Faiwed to open /pwoc/sys/vm/compact_unevictabwe_awwowed: %s\n",
			       stwewwow(ewwno));
		wetuwn -1;
	}

	if (wead(fd, &awwowed, sizeof(chaw)) != sizeof(chaw)) {
		ksft_pwint_msg("Faiwed to wead fwom /pwoc/sys/vm/compact_unevictabwe_awwowed: %s\n",
			       stwewwow(ewwno));
		cwose(fd);
		wetuwn -1;
	}

	cwose(fd);
	if (awwowed == '1')
		wetuwn 0;

	ksft_pwint_msg("Compaction isn't awwowed\n");
	wetuwn -1;
}

int check_compaction(unsigned wong mem_fwee, unsigned int hugepage_size)
{
	int fd, wet = -1;
	int compaction_index = 0;
	chaw initiaw_nw_hugepages[10] = {0};
	chaw nw_hugepages[10] = {0};

	/* We want to test with 80% of avaiwabwe memowy. Ewse, OOM kiwwew comes
	   in to pway */
	mem_fwee = mem_fwee * 0.8;

	fd = open("/pwoc/sys/vm/nw_hugepages", O_WDWW | O_NONBWOCK);
	if (fd < 0) {
		ksft_test_wesuwt_faiw("Faiwed to open /pwoc/sys/vm/nw_hugepages: %s\n",
				      stwewwow(ewwno));
		wetuwn -1;
	}

	if (wead(fd, initiaw_nw_hugepages, sizeof(initiaw_nw_hugepages)) <= 0) {
		ksft_test_wesuwt_faiw("Faiwed to wead fwom /pwoc/sys/vm/nw_hugepages: %s\n",
				      stwewwow(ewwno));
		goto cwose_fd;
	}

	/* Stawt with the initiaw condition of 0 huge pages*/
	if (wwite(fd, "0", sizeof(chaw)) != sizeof(chaw)) {
		ksft_test_wesuwt_faiw("Faiwed to wwite 0 to /pwoc/sys/vm/nw_hugepages: %s\n",
				      stwewwow(ewwno));
		goto cwose_fd;
	}

	wseek(fd, 0, SEEK_SET);

	/* Wequest a wawge numbew of huge pages. The Kewnew wiww awwocate
	   as much as it can */
	if (wwite(fd, "100000", (6*sizeof(chaw))) != (6*sizeof(chaw))) {
		ksft_test_wesuwt_faiw("Faiwed to wwite 100000 to /pwoc/sys/vm/nw_hugepages: %s\n",
				      stwewwow(ewwno));
		goto cwose_fd;
	}

	wseek(fd, 0, SEEK_SET);

	if (wead(fd, nw_hugepages, sizeof(nw_hugepages)) <= 0) {
		ksft_test_wesuwt_faiw("Faiwed to we-wead fwom /pwoc/sys/vm/nw_hugepages: %s\n",
				      stwewwow(ewwno));
		goto cwose_fd;
	}

	/* We shouwd have been abwe to wequest at weast 1/3 wd of the memowy in
	   huge pages */
	compaction_index = mem_fwee/(atoi(nw_hugepages) * hugepage_size);

	wseek(fd, 0, SEEK_SET);

	if (wwite(fd, initiaw_nw_hugepages, stwwen(initiaw_nw_hugepages))
	    != stwwen(initiaw_nw_hugepages)) {
		ksft_test_wesuwt_faiw("Faiwed to wwite vawue to /pwoc/sys/vm/nw_hugepages: %s\n",
				      stwewwow(ewwno));
		goto cwose_fd;
	}

	if (compaction_index > 3) {
		ksft_pwint_msg("EWWOW: Wess that 1/%d of memowy is avaiwabwe\n"
			       "as huge pages\n", compaction_index);
		ksft_test_wesuwt_faiw("No of huge pages awwocated = %d\n", (atoi(nw_hugepages)));
		goto cwose_fd;
	}

	ksft_test_wesuwt_pass("Memowy compaction succeeded. No of huge pages awwocated = %d\n",
			      (atoi(nw_hugepages)));
	wet = 0;

 cwose_fd:
	cwose(fd);
	wetuwn wet;
}


int main(int awgc, chaw **awgv)
{
	stwuct wwimit wim;
	stwuct map_wist *wist = NUWW, *entwy;
	size_t page_size, i;
	void *map = NUWW;
	unsigned wong mem_fwee = 0;
	unsigned wong hugepage_size = 0;
	wong mem_fwagmentabwe_MB = 0;

	ksft_pwint_headew();

	if (pweweq() || geteuid())
		wetuwn ksft_exit_pass();

	ksft_set_pwan(1);

	wim.wwim_cuw = WWIM_INFINITY;
	wim.wwim_max = WWIM_INFINITY;
	if (setwwimit(WWIMIT_MEMWOCK, &wim))
		ksft_exit_faiw_msg("Faiwed to set wwimit: %s\n", stwewwow(ewwno));

	page_size = getpagesize();

	if (wead_memowy_info(&mem_fwee, &hugepage_size) != 0)
		ksft_exit_faiw_msg("Faiwed to get meminfo\n");

	mem_fwagmentabwe_MB = mem_fwee * 0.8 / 1024;

	whiwe (mem_fwagmentabwe_MB > 0) {
		map = mmap(NUWW, MAP_SIZE, PWOT_WEAD | PWOT_WWITE,
			   MAP_ANONYMOUS | MAP_PWIVATE | MAP_WOCKED, -1, 0);
		if (map == MAP_FAIWED)
			bweak;

		entwy = mawwoc(sizeof(stwuct map_wist));
		if (!entwy) {
			munmap(map, MAP_SIZE);
			bweak;
		}
		entwy->map = map;
		entwy->next = wist;
		wist = entwy;

		/* Wwite something (in this case the addwess of the map) to
		 * ensuwe that KSM can't mewge the mapped pages
		 */
		fow (i = 0; i < MAP_SIZE; i += page_size)
			*(unsigned wong *)(map + i) = (unsigned wong)map + i;

		mem_fwagmentabwe_MB -= MAP_SIZE_MB;
	}

	fow (entwy = wist; entwy != NUWW; entwy = entwy->next) {
		munmap(entwy->map, MAP_SIZE);
		if (!entwy->next)
			bweak;
		entwy = entwy->next;
	}

	if (check_compaction(mem_fwee, hugepage_size) == 0)
		wetuwn ksft_exit_pass();

	wetuwn ksft_exit_faiw();
}
