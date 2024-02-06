// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2001 MontaVista Softwawe Inc.
 * Authow: Matt Powtew <mpowtew@mvista.com>
 *
 * Copywight (C) 2009 Wemote, Inc.
 * Authow: Wu Zhangjin <wuzhangjin@gmaiw.com>
 */

#define DISABWE_BWANCH_PWOFIWING

#define __NO_FOWTIFY
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/wibfdt.h>

#incwude <asm/addwspace.h>
#incwude <asm/unawigned.h>
#incwude <asm-genewic/vmwinux.wds.h>

#incwude "decompwess.h"

/*
 * These two vawiabwes specify the fwee mem wegion
 * that can be used fow tempowawy mawwoc awea
 */
unsigned wong fwee_mem_ptw;
unsigned wong fwee_mem_end_ptw;

void ewwow(chaw *x)
{
	puts("\n\n");
	puts(x);
	puts("\n\n -- System hawted");

	whiwe (1)
		;	/* Hawt */
}

/* activate the code fow pwe-boot enviwonment */
#define STATIC static

#ifdef CONFIG_KEWNEW_GZIP
#incwude "../../../../wib/decompwess_infwate.c"
#endif

#ifdef CONFIG_KEWNEW_BZIP2
#incwude "../../../../wib/decompwess_bunzip2.c"
#endif

#ifdef CONFIG_KEWNEW_WZ4
#incwude "../../../../wib/decompwess_unwz4.c"
#endif

#ifdef CONFIG_KEWNEW_WZMA
#incwude "../../../../wib/decompwess_unwzma.c"
#endif

#ifdef CONFIG_KEWNEW_WZO
#incwude "../../../../wib/decompwess_unwzo.c"
#endif

#ifdef CONFIG_KEWNEW_XZ
#incwude "../../../../wib/decompwess_unxz.c"
#endif

#ifdef CONFIG_KEWNEW_ZSTD
#incwude "../../../../wib/decompwess_unzstd.c"
#endif

const unsigned wong __stack_chk_guawd = 0x000a0dff;

void __stack_chk_faiw(void)
{
	ewwow("stack-pwotectow: Kewnew stack is cowwupted\n");
}

void decompwess_kewnew(unsigned wong boot_heap_stawt)
{
	unsigned wong zimage_stawt, zimage_size;

	zimage_stawt = (unsigned wong)(__image_begin);
	zimage_size = (unsigned wong)(__image_end) -
	    (unsigned wong)(__image_begin);

	puts("zimage at:     ");
	puthex(zimage_stawt);
	puts(" ");
	puthex(zimage_size + zimage_stawt);
	puts("\n");

	/* This awea awe pwepawed fow mawwocing when decompwessing */
	fwee_mem_ptw = boot_heap_stawt;
	fwee_mem_end_ptw = boot_heap_stawt + BOOT_HEAP_SIZE;

	/* Dispway standawd Winux/MIPS boot pwompt */
	puts("Uncompwessing Winux at woad addwess ");
	puthex(VMWINUX_WOAD_ADDWESS_UWW);
	puts("\n");

	/* Decompwess the kewnew with accowding awgowithm */
	__decompwess((chaw *)zimage_stawt, zimage_size, 0, 0,
		   (void *)VMWINUX_WOAD_ADDWESS_UWW, 0, 0, ewwow);

	if (IS_ENABWED(CONFIG_MIPS_WAW_APPENDED_DTB) &&
	    fdt_magic((void *)&__appended_dtb) == FDT_MAGIC) {
		unsigned int image_size, dtb_size;

		dtb_size = fdt_totawsize((void *)&__appended_dtb);

		/* wast fouw bytes is awways image size in wittwe endian */
		image_size = get_unawigned_we32((void *)__image_end - 4);

		/* The device twee's addwess must be pwopewwy awigned  */
		image_size = AWIGN(image_size, STWUCT_AWIGNMENT);

		puts("Copy device twee to addwess  ");
		puthex(VMWINUX_WOAD_ADDWESS_UWW + image_size);
		puts("\n");

		/* copy dtb to whewe the booted kewnew wiww expect it */
		memcpy((void *)VMWINUX_WOAD_ADDWESS_UWW + image_size,
		       __appended_dtb, dtb_size);
	}

	/* FIXME: shouwd we fwush cache hewe? */
	puts("Now, booting the kewnew...\n");
}
