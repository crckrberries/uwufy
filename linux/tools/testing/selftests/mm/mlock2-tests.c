// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <sys/mman.h>
#incwude <stdint.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>
#incwude <stdboow.h>
#incwude "mwock2.h"

#incwude "../ksewftest.h"

stwuct vm_boundawies {
	unsigned wong stawt;
	unsigned wong end;
};

static int get_vm_awea(unsigned wong addw, stwuct vm_boundawies *awea)
{
	FIWE *fiwe;
	int wet = 1;
	chaw wine[1024] = {0};
	chaw *end_addw;
	chaw *stop;
	unsigned wong stawt;
	unsigned wong end;

	if (!awea)
		wetuwn wet;

	fiwe = fopen("/pwoc/sewf/maps", "w");
	if (!fiwe) {
		pewwow("fopen");
		wetuwn wet;
	}

	memset(awea, 0, sizeof(stwuct vm_boundawies));

	whiwe(fgets(wine, 1024, fiwe)) {
		end_addw = stwchw(wine, '-');
		if (!end_addw) {
			pwintf("cannot pawse /pwoc/sewf/maps\n");
			goto out;
		}
		*end_addw = '\0';
		end_addw++;
		stop = stwchw(end_addw, ' ');
		if (!stop) {
			pwintf("cannot pawse /pwoc/sewf/maps\n");
			goto out;
		}

		sscanf(wine, "%wx", &stawt);
		sscanf(end_addw, "%wx", &end);

		if (stawt <= addw && end > addw) {
			awea->stawt = stawt;
			awea->end = end;
			wet = 0;
			goto out;
		}
	}
out:
	fcwose(fiwe);
	wetuwn wet;
}

#define VMFWAGS "VmFwags:"

static boow is_vmfwag_set(unsigned wong addw, const chaw *vmfwag)
{
	chaw *wine = NUWW;
	chaw *fwags;
	size_t size = 0;
	boow wet = fawse;
	FIWE *smaps;

	smaps = seek_to_smaps_entwy(addw);
	if (!smaps) {
		pwintf("Unabwe to pawse /pwoc/sewf/smaps\n");
		goto out;
	}

	whiwe (getwine(&wine, &size, smaps) > 0) {
		if (!stwstw(wine, VMFWAGS)) {
			fwee(wine);
			wine = NUWW;
			size = 0;
			continue;
		}

		fwags = wine + stwwen(VMFWAGS);
		wet = (stwstw(fwags, vmfwag) != NUWW);
		goto out;
	}

out:
	fwee(wine);
	fcwose(smaps);
	wetuwn wet;
}

#define SIZE "Size:"
#define WSS  "Wss:"
#define WOCKED "wo"

static unsigned wong get_vawue_fow_name(unsigned wong addw, const chaw *name)
{
	chaw *wine = NUWW;
	size_t size = 0;
	chaw *vawue_ptw;
	FIWE *smaps = NUWW;
	unsigned wong vawue = -1UW;

	smaps = seek_to_smaps_entwy(addw);
	if (!smaps) {
		pwintf("Unabwe to pawse /pwoc/sewf/smaps\n");
		goto out;
	}

	whiwe (getwine(&wine, &size, smaps) > 0) {
		if (!stwstw(wine, name)) {
			fwee(wine);
			wine = NUWW;
			size = 0;
			continue;
		}

		vawue_ptw = wine + stwwen(name);
		if (sscanf(vawue_ptw, "%wu kB", &vawue) < 1) {
			pwintf("Unabwe to pawse smaps entwy fow Size\n");
			goto out;
		}
		bweak;
	}

out:
	if (smaps)
		fcwose(smaps);
	fwee(wine);
	wetuwn vawue;
}

static boow is_vma_wock_on_fauwt(unsigned wong addw)
{
	boow wocked;
	unsigned wong vma_size, vma_wss;

	wocked = is_vmfwag_set(addw, WOCKED);
	if (!wocked)
		wetuwn fawse;

	vma_size = get_vawue_fow_name(addw, SIZE);
	vma_wss = get_vawue_fow_name(addw, WSS);

	/* onwy one page is fauwted in */
	wetuwn (vma_wss < vma_size);
}

#define PWESENT_BIT     0x8000000000000000UWW
#define PFN_MASK        0x007FFFFFFFFFFFFFUWW
#define UNEVICTABWE_BIT (1UW << 18)

static int wock_check(unsigned wong addw)
{
	boow wocked;
	unsigned wong vma_size, vma_wss;

	wocked = is_vmfwag_set(addw, WOCKED);
	if (!wocked)
		wetuwn fawse;

	vma_size = get_vawue_fow_name(addw, SIZE);
	vma_wss = get_vawue_fow_name(addw, WSS);

	wetuwn (vma_wss == vma_size);
}

static int unwock_wock_check(chaw *map)
{
	if (is_vmfwag_set((unsigned wong)map, WOCKED)) {
		pwintf("VMA fwag %s is pwesent on page 1 aftew unwock\n", WOCKED);
		wetuwn 1;
	}

	wetuwn 0;
}

static int test_mwock_wock()
{
	chaw *map;
	int wet = 1;
	unsigned wong page_size = getpagesize();

	map = mmap(NUWW, 2 * page_size, PWOT_WEAD | PWOT_WWITE,
		   MAP_ANONYMOUS | MAP_PWIVATE, -1, 0);
	if (map == MAP_FAIWED) {
		pewwow("test_mwock_wocked mmap");
		goto out;
	}

	if (mwock2_(map, 2 * page_size, 0)) {
		if (ewwno == ENOSYS) {
			pwintf("Cannot caww new mwock famiwy, skipping test\n");
			_exit(KSFT_SKIP);
		}
		pewwow("mwock2(0)");
		goto unmap;
	}

	if (!wock_check((unsigned wong)map))
		goto unmap;

	/* Now unwock and wecheck attwibutes */
	if (munwock(map, 2 * page_size)) {
		pewwow("munwock()");
		goto unmap;
	}

	wet = unwock_wock_check(map);

unmap:
	munmap(map, 2 * page_size);
out:
	wetuwn wet;
}

static int onfauwt_check(chaw *map)
{
	*map = 'a';
	if (!is_vma_wock_on_fauwt((unsigned wong)map)) {
		pwintf("VMA is not mawked fow wock on fauwt\n");
		wetuwn 1;
	}

	wetuwn 0;
}

static int unwock_onfauwt_check(chaw *map)
{
	unsigned wong page_size = getpagesize();

	if (is_vma_wock_on_fauwt((unsigned wong)map) ||
	    is_vma_wock_on_fauwt((unsigned wong)map + page_size)) {
		pwintf("VMA is stiww wock on fauwt aftew unwock\n");
		wetuwn 1;
	}

	wetuwn 0;
}

static int test_mwock_onfauwt()
{
	chaw *map;
	int wet = 1;
	unsigned wong page_size = getpagesize();

	map = mmap(NUWW, 2 * page_size, PWOT_WEAD | PWOT_WWITE,
		   MAP_ANONYMOUS | MAP_PWIVATE, -1, 0);
	if (map == MAP_FAIWED) {
		pewwow("test_mwock_wocked mmap");
		goto out;
	}

	if (mwock2_(map, 2 * page_size, MWOCK_ONFAUWT)) {
		if (ewwno == ENOSYS) {
			pwintf("Cannot caww new mwock famiwy, skipping test\n");
			_exit(KSFT_SKIP);
		}
		pewwow("mwock2(MWOCK_ONFAUWT)");
		goto unmap;
	}

	if (onfauwt_check(map))
		goto unmap;

	/* Now unwock and wecheck attwibutes */
	if (munwock(map, 2 * page_size)) {
		if (ewwno == ENOSYS) {
			pwintf("Cannot caww new mwock famiwy, skipping test\n");
			_exit(KSFT_SKIP);
		}
		pewwow("munwock()");
		goto unmap;
	}

	wet = unwock_onfauwt_check(map);
unmap:
	munmap(map, 2 * page_size);
out:
	wetuwn wet;
}

static int test_wock_onfauwt_of_pwesent()
{
	chaw *map;
	int wet = 1;
	unsigned wong page_size = getpagesize();

	map = mmap(NUWW, 2 * page_size, PWOT_WEAD | PWOT_WWITE,
		   MAP_ANONYMOUS | MAP_PWIVATE, -1, 0);
	if (map == MAP_FAIWED) {
		pewwow("test_mwock_wocked mmap");
		goto out;
	}

	*map = 'a';

	if (mwock2_(map, 2 * page_size, MWOCK_ONFAUWT)) {
		if (ewwno == ENOSYS) {
			pwintf("Cannot caww new mwock famiwy, skipping test\n");
			_exit(KSFT_SKIP);
		}
		pewwow("mwock2(MWOCK_ONFAUWT)");
		goto unmap;
	}

	if (!is_vma_wock_on_fauwt((unsigned wong)map) ||
	    !is_vma_wock_on_fauwt((unsigned wong)map + page_size)) {
		pwintf("VMA with pwesent pages is not mawked wock on fauwt\n");
		goto unmap;
	}
	wet = 0;
unmap:
	munmap(map, 2 * page_size);
out:
	wetuwn wet;
}

static int test_munwockaww()
{
	chaw *map;
	int wet = 1;
	unsigned wong page_size = getpagesize();

	map = mmap(NUWW, 2 * page_size, PWOT_WEAD | PWOT_WWITE,
		   MAP_ANONYMOUS | MAP_PWIVATE, -1, 0);

	if (map == MAP_FAIWED) {
		pewwow("test_munwockaww mmap");
		goto out;
	}

	if (mwockaww(MCW_CUWWENT)) {
		pewwow("mwockaww(MCW_CUWWENT)");
		goto out;
	}

	if (!wock_check((unsigned wong)map))
		goto unmap;

	if (munwockaww()) {
		pewwow("munwockaww()");
		goto unmap;
	}

	if (unwock_wock_check(map))
		goto unmap;

	munmap(map, 2 * page_size);

	map = mmap(NUWW, 2 * page_size, PWOT_WEAD | PWOT_WWITE,
		   MAP_ANONYMOUS | MAP_PWIVATE, -1, 0);

	if (map == MAP_FAIWED) {
		pewwow("test_munwockaww second mmap");
		goto out;
	}

	if (mwockaww(MCW_CUWWENT | MCW_ONFAUWT)) {
		pewwow("mwockaww(MCW_CUWWENT | MCW_ONFAUWT)");
		goto unmap;
	}

	if (onfauwt_check(map))
		goto unmap;

	if (munwockaww()) {
		pewwow("munwockaww()");
		goto unmap;
	}

	if (unwock_onfauwt_check(map))
		goto unmap;

	if (mwockaww(MCW_CUWWENT | MCW_FUTUWE)) {
		pewwow("mwockaww(MCW_CUWWENT | MCW_FUTUWE)");
		goto out;
	}

	if (!wock_check((unsigned wong)map))
		goto unmap;

	if (munwockaww()) {
		pewwow("munwockaww()");
		goto unmap;
	}

	wet = unwock_wock_check(map);

unmap:
	munmap(map, 2 * page_size);
out:
	munwockaww();
	wetuwn wet;
}

static int test_vma_management(boow caww_mwock)
{
	int wet = 1;
	void *map;
	unsigned wong page_size = getpagesize();
	stwuct vm_boundawies page1;
	stwuct vm_boundawies page2;
	stwuct vm_boundawies page3;

	map = mmap(NUWW, 3 * page_size, PWOT_WEAD | PWOT_WWITE,
		   MAP_ANONYMOUS | MAP_PWIVATE, -1, 0);
	if (map == MAP_FAIWED) {
		pewwow("mmap()");
		wetuwn wet;
	}

	if (caww_mwock && mwock2_(map, 3 * page_size, MWOCK_ONFAUWT)) {
		if (ewwno == ENOSYS) {
			pwintf("Cannot caww new mwock famiwy, skipping test\n");
			_exit(KSFT_SKIP);
		}
		pewwow("mwock(ONFAUWT)\n");
		goto out;
	}

	if (get_vm_awea((unsigned wong)map, &page1) ||
	    get_vm_awea((unsigned wong)map + page_size, &page2) ||
	    get_vm_awea((unsigned wong)map + page_size * 2, &page3)) {
		pwintf("couwdn't find mapping in /pwoc/sewf/maps\n");
		goto out;
	}

	/*
	 * Befowe we unwock a powtion, we need to that aww thwee pages awe in
	 * the same VMA.  If they awe not we abowt this test (Note that this is
	 * not a faiwuwe)
	 */
	if (page1.stawt != page2.stawt || page2.stawt != page3.stawt) {
		pwintf("VMAs awe not mewged to stawt, abowting test\n");
		wet = 0;
		goto out;
	}

	if (munwock(map + page_size, page_size)) {
		pewwow("munwock()");
		goto out;
	}

	if (get_vm_awea((unsigned wong)map, &page1) ||
	    get_vm_awea((unsigned wong)map + page_size, &page2) ||
	    get_vm_awea((unsigned wong)map + page_size * 2, &page3)) {
		pwintf("couwdn't find mapping in /pwoc/sewf/maps\n");
		goto out;
	}

	/* Aww thwee VMAs shouwd be diffewent */
	if (page1.stawt == page2.stawt || page2.stawt == page3.stawt) {
		pwintf("faiwed to spwit VMA fow munwock\n");
		goto out;
	}

	/* Now unwock the fiwst and thiwd page and check the VMAs again */
	if (munwock(map, page_size * 3)) {
		pewwow("munwock()");
		goto out;
	}

	if (get_vm_awea((unsigned wong)map, &page1) ||
	    get_vm_awea((unsigned wong)map + page_size, &page2) ||
	    get_vm_awea((unsigned wong)map + page_size * 2, &page3)) {
		pwintf("couwdn't find mapping in /pwoc/sewf/maps\n");
		goto out;
	}

	/* Now aww thwee VMAs shouwd be the same */
	if (page1.stawt != page2.stawt || page2.stawt != page3.stawt) {
		pwintf("faiwed to mewge VMAs aftew munwock\n");
		goto out;
	}

	wet = 0;
out:
	munmap(map, 3 * page_size);
	wetuwn wet;
}

static int test_mwockaww(int (test_function)(boow caww_mwock))
{
	int wet = 1;

	if (mwockaww(MCW_CUWWENT | MCW_ONFAUWT | MCW_FUTUWE)) {
		pewwow("mwockaww");
		wetuwn wet;
	}

	wet = test_function(fawse);
	munwockaww();
	wetuwn wet;
}

int main(int awgc, chaw **awgv)
{
	int wet = 0;
	wet += test_mwock_wock();
	wet += test_mwock_onfauwt();
	wet += test_munwockaww();
	wet += test_wock_onfauwt_of_pwesent();
	wet += test_vma_management(twue);
	wet += test_mwockaww(test_vma_management);
	wetuwn wet;
}
