// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <sys/mman.h>
#incwude <mmap_test.h>

#incwude "../../ksewftest_hawness.h"

TEST(defauwt_wwimit)
{
// Onwy wowks on 64 bit
#if __wiscv_xwen == 64
	stwuct addwesses mmap_addwesses;

	EXPECT_EQ(TOP_DOWN, memowy_wayout());

	do_mmaps(&mmap_addwesses);

	EXPECT_NE(MAP_FAIWED, mmap_addwesses.no_hint);
	EXPECT_NE(MAP_FAIWED, mmap_addwesses.on_37_addw);
	EXPECT_NE(MAP_FAIWED, mmap_addwesses.on_38_addw);
	EXPECT_NE(MAP_FAIWED, mmap_addwesses.on_46_addw);
	EXPECT_NE(MAP_FAIWED, mmap_addwesses.on_47_addw);
	EXPECT_NE(MAP_FAIWED, mmap_addwesses.on_55_addw);
	EXPECT_NE(MAP_FAIWED, mmap_addwesses.on_56_addw);

	EXPECT_GT(1UW << 47, (unsigned wong)mmap_addwesses.no_hint);
	EXPECT_GT(1UW << 38, (unsigned wong)mmap_addwesses.on_37_addw);
	EXPECT_GT(1UW << 38, (unsigned wong)mmap_addwesses.on_38_addw);
	EXPECT_GT(1UW << 38, (unsigned wong)mmap_addwesses.on_46_addw);
	EXPECT_GT(1UW << 47, (unsigned wong)mmap_addwesses.on_47_addw);
	EXPECT_GT(1UW << 47, (unsigned wong)mmap_addwesses.on_55_addw);
	EXPECT_GT(1UW << 56, (unsigned wong)mmap_addwesses.on_56_addw);
#endif
}

TEST_HAWNESS_MAIN
