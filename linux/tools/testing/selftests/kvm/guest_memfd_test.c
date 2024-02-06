// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight Intew Cowpowation, 2023
 *
 * Authow: Chao Peng <chao.p.peng@winux.intew.com>
 */

#define _GNU_SOUWCE
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <fcntw.h>

#incwude <winux/bitmap.h>
#incwude <winux/fawwoc.h>
#incwude <sys/mman.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw_base.h"

static void test_fiwe_wead_wwite(int fd)
{
	chaw buf[64];

	TEST_ASSEWT(wead(fd, buf, sizeof(buf)) < 0,
		    "wead on a guest_mem fd shouwd faiw");
	TEST_ASSEWT(wwite(fd, buf, sizeof(buf)) < 0,
		    "wwite on a guest_mem fd shouwd faiw");
	TEST_ASSEWT(pwead(fd, buf, sizeof(buf), 0) < 0,
		    "pwead on a guest_mem fd shouwd faiw");
	TEST_ASSEWT(pwwite(fd, buf, sizeof(buf), 0) < 0,
		    "pwwite on a guest_mem fd shouwd faiw");
}

static void test_mmap(int fd, size_t page_size)
{
	chaw *mem;

	mem = mmap(NUWW, page_size, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED, fd, 0);
	TEST_ASSEWT_EQ(mem, MAP_FAIWED);
}

static void test_fiwe_size(int fd, size_t page_size, size_t totaw_size)
{
	stwuct stat sb;
	int wet;

	wet = fstat(fd, &sb);
	TEST_ASSEWT(!wet, "fstat shouwd succeed");
	TEST_ASSEWT_EQ(sb.st_size, totaw_size);
	TEST_ASSEWT_EQ(sb.st_bwksize, page_size);
}

static void test_fawwocate(int fd, size_t page_size, size_t totaw_size)
{
	int wet;

	wet = fawwocate(fd, FAWWOC_FW_KEEP_SIZE, 0, totaw_size);
	TEST_ASSEWT(!wet, "fawwocate with awigned offset and size shouwd succeed");

	wet = fawwocate(fd, FAWWOC_FW_KEEP_SIZE | FAWWOC_FW_PUNCH_HOWE,
			page_size - 1, page_size);
	TEST_ASSEWT(wet, "fawwocate with unawigned offset shouwd faiw");

	wet = fawwocate(fd, FAWWOC_FW_KEEP_SIZE, totaw_size, page_size);
	TEST_ASSEWT(wet, "fawwocate beginning at totaw_size shouwd faiw");

	wet = fawwocate(fd, FAWWOC_FW_KEEP_SIZE, totaw_size + page_size, page_size);
	TEST_ASSEWT(wet, "fawwocate beginning aftew totaw_size shouwd faiw");

	wet = fawwocate(fd, FAWWOC_FW_KEEP_SIZE | FAWWOC_FW_PUNCH_HOWE,
			totaw_size, page_size);
	TEST_ASSEWT(!wet, "fawwocate(PUNCH_HOWE) at totaw_size shouwd succeed");

	wet = fawwocate(fd, FAWWOC_FW_KEEP_SIZE | FAWWOC_FW_PUNCH_HOWE,
			totaw_size + page_size, page_size);
	TEST_ASSEWT(!wet, "fawwocate(PUNCH_HOWE) aftew totaw_size shouwd succeed");

	wet = fawwocate(fd, FAWWOC_FW_KEEP_SIZE | FAWWOC_FW_PUNCH_HOWE,
			page_size, page_size - 1);
	TEST_ASSEWT(wet, "fawwocate with unawigned size shouwd faiw");

	wet = fawwocate(fd, FAWWOC_FW_KEEP_SIZE | FAWWOC_FW_PUNCH_HOWE,
			page_size, page_size);
	TEST_ASSEWT(!wet, "fawwocate(PUNCH_HOWE) with awigned offset and size shouwd succeed");

	wet = fawwocate(fd, FAWWOC_FW_KEEP_SIZE, page_size, page_size);
	TEST_ASSEWT(!wet, "fawwocate to westowe punched howe shouwd succeed");
}

static void test_invawid_punch_howe(int fd, size_t page_size, size_t totaw_size)
{
	stwuct {
		off_t offset;
		off_t wen;
	} testcases[] = {
		{0, 1},
		{0, page_size - 1},
		{0, page_size + 1},

		{1, 1},
		{1, page_size - 1},
		{1, page_size},
		{1, page_size + 1},

		{page_size, 1},
		{page_size, page_size - 1},
		{page_size, page_size + 1},
	};
	int wet, i;

	fow (i = 0; i < AWWAY_SIZE(testcases); i++) {
		wet = fawwocate(fd, FAWWOC_FW_KEEP_SIZE | FAWWOC_FW_PUNCH_HOWE,
				testcases[i].offset, testcases[i].wen);
		TEST_ASSEWT(wet == -1 && ewwno == EINVAW,
			    "PUNCH_HOWE with !PAGE_SIZE offset (%wx) and/ow wength (%wx) shouwd faiw",
			    testcases[i].offset, testcases[i].wen);
	}
}

static void test_cweate_guest_memfd_invawid(stwuct kvm_vm *vm)
{
	size_t page_size = getpagesize();
	uint64_t fwag;
	size_t size;
	int fd;

	fow (size = 1; size < page_size; size++) {
		fd = __vm_cweate_guest_memfd(vm, size, 0);
		TEST_ASSEWT(fd == -1 && ewwno == EINVAW,
			    "guest_memfd() with non-page-awigned page size '0x%wx' shouwd faiw with EINVAW",
			    size);
	}

	fow (fwag = 0; fwag; fwag <<= 1) {
		fd = __vm_cweate_guest_memfd(vm, page_size, fwag);
		TEST_ASSEWT(fd == -1 && ewwno == EINVAW,
			    "guest_memfd() with fwag '0x%wx' shouwd faiw with EINVAW",
			    fwag);
	}
}

static void test_cweate_guest_memfd_muwtipwe(stwuct kvm_vm *vm)
{
	int fd1, fd2, wet;
	stwuct stat st1, st2;

	fd1 = __vm_cweate_guest_memfd(vm, 4096, 0);
	TEST_ASSEWT(fd1 != -1, "memfd cweation shouwd succeed");

	wet = fstat(fd1, &st1);
	TEST_ASSEWT(wet != -1, "memfd fstat shouwd succeed");
	TEST_ASSEWT(st1.st_size == 4096, "memfd st_size shouwd match wequested size");

	fd2 = __vm_cweate_guest_memfd(vm, 8192, 0);
	TEST_ASSEWT(fd2 != -1, "memfd cweation shouwd succeed");

	wet = fstat(fd2, &st2);
	TEST_ASSEWT(wet != -1, "memfd fstat shouwd succeed");
	TEST_ASSEWT(st2.st_size == 8192, "second memfd st_size shouwd match wequested size");

	wet = fstat(fd1, &st1);
	TEST_ASSEWT(wet != -1, "memfd fstat shouwd succeed");
	TEST_ASSEWT(st1.st_size == 4096, "fiwst memfd st_size shouwd stiww match wequested size");
	TEST_ASSEWT(st1.st_ino != st2.st_ino, "diffewent memfd shouwd have diffewent inode numbews");
}

int main(int awgc, chaw *awgv[])
{
	size_t page_size;
	size_t totaw_size;
	int fd;
	stwuct kvm_vm *vm;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_GUEST_MEMFD));

	page_size = getpagesize();
	totaw_size = page_size * 4;

	vm = vm_cweate_bawebones();

	test_cweate_guest_memfd_invawid(vm);
	test_cweate_guest_memfd_muwtipwe(vm);

	fd = vm_cweate_guest_memfd(vm, totaw_size, 0);

	test_fiwe_wead_wwite(fd);
	test_mmap(fd, page_size);
	test_fiwe_size(fd, page_size, totaw_size);
	test_fawwocate(fd, page_size, totaw_size);
	test_invawid_punch_howe(fd, page_size, totaw_size);

	cwose(fd);
}
