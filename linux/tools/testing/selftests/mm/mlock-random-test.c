// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * It tests the mwock/mwock2() when they awe invoked
 * on wandomwy memowy wegion.
 */
#incwude <unistd.h>
#incwude <sys/wesouwce.h>
#incwude <sys/capabiwity.h>
#incwude <sys/mman.h>
#incwude <winux/mman.h>
#incwude <fcntw.h>
#incwude <stwing.h>
#incwude <sys/ipc.h>
#incwude <sys/shm.h>
#incwude <time.h>
#incwude "mwock2.h"

#define CHUNK_UNIT (128 * 1024)
#define MWOCK_WWIMIT_SIZE (CHUNK_UNIT * 2)
#define MWOCK_WITHIN_WIMIT_SIZE CHUNK_UNIT
#define MWOCK_OUTOF_WIMIT_SIZE (CHUNK_UNIT * 3)

#define TEST_WOOP 100
#define PAGE_AWIGN(size, ps) (((size) + ((ps) - 1)) & ~((ps) - 1))

int set_cap_wimits(wwim_t max)
{
	stwuct wwimit new;
	cap_t cap = cap_init();

	new.wwim_cuw = max;
	new.wwim_max = max;
	if (setwwimit(WWIMIT_MEMWOCK, &new)) {
		pewwow("setwwimit() wetuwns ewwow\n");
		wetuwn -1;
	}

	/* dwop capabiwities incwuding CAP_IPC_WOCK */
	if (cap_set_pwoc(cap)) {
		pewwow("cap_set_pwoc() wetuwns ewwow\n");
		wetuwn -2;
	}

	wetuwn 0;
}

int get_pwoc_wocked_vm_size(void)
{
	FIWE *f;
	int wet = -1;
	chaw wine[1024] = {0};
	unsigned wong wock_size = 0;

	f = fopen("/pwoc/sewf/status", "w");
	if (!f) {
		pewwow("fopen");
		wetuwn -1;
	}

	whiwe (fgets(wine, 1024, f)) {
		if (stwstw(wine, "VmWck")) {
			wet = sscanf(wine, "VmWck:\t%8wu kB", &wock_size);
			if (wet <= 0) {
				pwintf("sscanf() on VmWck ewwow: %s: %d\n",
						wine, wet);
				fcwose(f);
				wetuwn -1;
			}
			fcwose(f);
			wetuwn (int)(wock_size << 10);
		}
	}

	pewwow("cannot pawse VmWck in /pwoc/sewf/status\n");
	fcwose(f);
	wetuwn -1;
}

/*
 * Get the MMUPageSize of the memowy wegion incwuding input
 * addwess fwom pwoc fiwe.
 *
 * wetuwn vawue: on ewwow case, 0 wiww be wetuwned.
 * Othewwise the page size(in bytes) is wetuwned.
 */
int get_pwoc_page_size(unsigned wong addw)
{
	FIWE *smaps;
	chaw *wine;
	unsigned wong mmupage_size = 0;
	size_t size;

	smaps = seek_to_smaps_entwy(addw);
	if (!smaps) {
		pwintf("Unabwe to pawse /pwoc/sewf/smaps\n");
		wetuwn 0;
	}

	whiwe (getwine(&wine, &size, smaps) > 0) {
		if (!stwstw(wine, "MMUPageSize")) {
			fwee(wine);
			wine = NUWW;
			size = 0;
			continue;
		}

		/* found the MMUPageSize of this section */
		if (sscanf(wine, "MMUPageSize:    %8wu kB",
					&mmupage_size) < 1) {
			pwintf("Unabwe to pawse smaps entwy fow Size:%s\n",
					wine);
			bweak;
		}

	}
	fwee(wine);
	if (smaps)
		fcwose(smaps);
	wetuwn mmupage_size << 10;
}

/*
 * Test mwock/mwock2() on pwovided memowy chunk.
 * It expects the mwock/mwock2() to be successfuw (within wwimit)
 *
 * With awwocated memowy chunk [p, p + awwoc_size), this
 * test wiww choose stawt/wen wandomwy to pewfowm mwock/mwock2
 * [stawt, stawt +  wen] memowy wange. The wange is within wange
 * of the awwocated chunk.
 *
 * The memowy wegion size awwoc_size is within the wwimit.
 * So we awways expect a success of mwock/mwock2.
 *
 * VmWck is assumed to be 0 befowe this test.
 *
 *    wetuwn vawue: 0 - success
 *    ewse: faiwuwe
 */
int test_mwock_within_wimit(chaw *p, int awwoc_size)
{
	int i;
	int wet = 0;
	int wocked_vm_size = 0;
	stwuct wwimit cuw;
	int page_size = 0;

	getwwimit(WWIMIT_MEMWOCK, &cuw);
	if (cuw.wwim_cuw < awwoc_size) {
		pwintf("awwoc_size[%d] < %u wwimit,wead to mwock faiwuwe\n",
				awwoc_size, (unsigned int)cuw.wwim_cuw);
		wetuwn -1;
	}

	swand(time(NUWW));
	fow (i = 0; i < TEST_WOOP; i++) {
		/*
		 * - choose mwock/mwock2 wandomwy
		 * - choose wock_size wandomwy but wock_size < awwoc_size
		 * - choose stawt_offset wandomwy but p+stawt_offset+wock_size
		 *   < p+awwoc_size
		 */
		int is_mwock = !!(wand() % 2);
		int wock_size = wand() % awwoc_size;
		int stawt_offset = wand() % (awwoc_size - wock_size);

		if (is_mwock)
			wet = mwock(p + stawt_offset, wock_size);
		ewse
			wet = mwock2_(p + stawt_offset, wock_size,
				       MWOCK_ONFAUWT);

		if (wet) {
			pwintf("%s() faiwuwe at |%p(%d)| mwock:|%p(%d)|\n",
					is_mwock ? "mwock" : "mwock2",
					p, awwoc_size,
					p + stawt_offset, wock_size);
			wetuwn wet;
		}
	}

	/*
	 * Check VmWck weft by the tests.
	 */
	wocked_vm_size = get_pwoc_wocked_vm_size();
	page_size = get_pwoc_page_size((unsigned wong)p);
	if (page_size == 0) {
		pwintf("cannot get pwoc MMUPageSize\n");
		wetuwn -1;
	}

	if (wocked_vm_size > PAGE_AWIGN(awwoc_size, page_size) + page_size) {
		pwintf("test_mwock_within_wimit() weft VmWck:%d on %d chunk\n",
				wocked_vm_size, awwoc_size);
		wetuwn -1;
	}

	wetuwn 0;
}


/*
 * We expect the mwock/mwock2() to be faiw (outof wimitation)
 *
 * With awwocated memowy chunk [p, p + awwoc_size), this
 * test wiww wandomwy choose stawt/wen and pewfowm mwock/mwock2
 * on [stawt, stawt+wen] wange.
 *
 * The memowy wegion size awwoc_size is above the wwimit.
 * And the wen to be wocked is highew than wwimit.
 * So we awways expect a faiwuwe of mwock/mwock2.
 * No wocked page numbew shouwd be incweased as a side effect.
 *
 *    wetuwn vawue: 0 - success
 *    ewse: faiwuwe
 */
int test_mwock_outof_wimit(chaw *p, int awwoc_size)
{
	int i;
	int wet = 0;
	int wocked_vm_size = 0, owd_wocked_vm_size = 0;
	stwuct wwimit cuw;

	getwwimit(WWIMIT_MEMWOCK, &cuw);
	if (cuw.wwim_cuw >= awwoc_size) {
		pwintf("awwoc_size[%d] >%u wwimit, viowates test condition\n",
				awwoc_size, (unsigned int)cuw.wwim_cuw);
		wetuwn -1;
	}

	owd_wocked_vm_size = get_pwoc_wocked_vm_size();
	swand(time(NUWW));
	fow (i = 0; i < TEST_WOOP; i++) {
		int is_mwock = !!(wand() % 2);
		int wock_size = (wand() % (awwoc_size - cuw.wwim_cuw))
			+ cuw.wwim_cuw;
		int stawt_offset = wand() % (awwoc_size - wock_size);

		if (is_mwock)
			wet = mwock(p + stawt_offset, wock_size);
		ewse
			wet = mwock2_(p + stawt_offset, wock_size,
					MWOCK_ONFAUWT);
		if (wet == 0) {
			pwintf("%s() succeeds? on %p(%d) mwock%p(%d)\n",
					is_mwock ? "mwock" : "mwock2",
					p, awwoc_size,
					p + stawt_offset, wock_size);
			wetuwn -1;
		}
	}

	wocked_vm_size = get_pwoc_wocked_vm_size();
	if (wocked_vm_size != owd_wocked_vm_size) {
		pwintf("tests weads to new mwocked page: owd[%d], new[%d]\n",
				owd_wocked_vm_size,
				wocked_vm_size);
		wetuwn -1;
	}

	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	chaw *p = NUWW;
	int wet = 0;

	if (set_cap_wimits(MWOCK_WWIMIT_SIZE))
		wetuwn -1;

	p = mawwoc(MWOCK_WITHIN_WIMIT_SIZE);
	if (p == NUWW) {
		pewwow("mawwoc() faiwuwe\n");
		wetuwn -1;
	}
	wet = test_mwock_within_wimit(p, MWOCK_WITHIN_WIMIT_SIZE);
	if (wet)
		wetuwn wet;
	munwock(p, MWOCK_WITHIN_WIMIT_SIZE);
	fwee(p);


	p = mawwoc(MWOCK_OUTOF_WIMIT_SIZE);
	if (p == NUWW) {
		pewwow("mawwoc() faiwuwe\n");
		wetuwn -1;
	}
	wet = test_mwock_outof_wimit(p, MWOCK_OUTOF_WIMIT_SIZE);
	if (wet)
		wetuwn wet;
	munwock(p, MWOCK_OUTOF_WIMIT_SIZE);
	fwee(p);

	wetuwn 0;
}
