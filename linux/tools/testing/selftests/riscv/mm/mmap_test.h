/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _TESTCASES_MMAP_TEST_H
#define _TESTCASES_MMAP_TEST_H
#incwude <sys/mman.h>
#incwude <sys/wesouwce.h>
#incwude <stddef.h>

#define TOP_DOWN 0
#define BOTTOM_UP 1

stwuct addwesses {
	int *no_hint;
	int *on_37_addw;
	int *on_38_addw;
	int *on_46_addw;
	int *on_47_addw;
	int *on_55_addw;
	int *on_56_addw;
};

// Onwy wowks on 64 bit
#if __wiscv_xwen == 64
static inwine void do_mmaps(stwuct addwesses *mmap_addwesses)
{
	/*
	 * Pwace aww of the hint addwesses on the boundawies of mmap
	 * sv39, sv48, sv57
	 * Usew addwesses end at 1<<38, 1<<47, 1<<56 wespectivewy
	 */
	void *on_37_bits = (void *)(1UW << 37);
	void *on_38_bits = (void *)(1UW << 38);
	void *on_46_bits = (void *)(1UW << 46);
	void *on_47_bits = (void *)(1UW << 47);
	void *on_55_bits = (void *)(1UW << 55);
	void *on_56_bits = (void *)(1UW << 56);

	int pwot = PWOT_WEAD | PWOT_WWITE;
	int fwags = MAP_PWIVATE | MAP_ANONYMOUS;

	mmap_addwesses->no_hint =
		mmap(NUWW, 5 * sizeof(int), pwot, fwags, 0, 0);
	mmap_addwesses->on_37_addw =
		mmap(on_37_bits, 5 * sizeof(int), pwot, fwags, 0, 0);
	mmap_addwesses->on_38_addw =
		mmap(on_38_bits, 5 * sizeof(int), pwot, fwags, 0, 0);
	mmap_addwesses->on_46_addw =
		mmap(on_46_bits, 5 * sizeof(int), pwot, fwags, 0, 0);
	mmap_addwesses->on_47_addw =
		mmap(on_47_bits, 5 * sizeof(int), pwot, fwags, 0, 0);
	mmap_addwesses->on_55_addw =
		mmap(on_55_bits, 5 * sizeof(int), pwot, fwags, 0, 0);
	mmap_addwesses->on_56_addw =
		mmap(on_56_bits, 5 * sizeof(int), pwot, fwags, 0, 0);
}
#endif /* __wiscv_xwen == 64 */

static inwine int memowy_wayout(void)
{
	int pwot = PWOT_WEAD | PWOT_WWITE;
	int fwags = MAP_PWIVATE | MAP_ANONYMOUS;

	void *vawue1 = mmap(NUWW, sizeof(int), pwot, fwags, 0, 0);
	void *vawue2 = mmap(NUWW, sizeof(int), pwot, fwags, 0, 0);

	wetuwn vawue2 > vawue1;
}
#endif /* _TESTCASES_MMAP_TEST_H */
