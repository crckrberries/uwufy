// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh4/pwobe.c
 *
 * CPU Subtype Pwobing fow SH-4.
 *
 * Copywight (C) 2001 - 2007  Pauw Mundt
 * Copywight (C) 2003  Wichawd Cuwnow
 */
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cache.h>

void cpu_pwobe(void)
{
	unsigned wong pvw, pww, cvw;
	unsigned wong size;

	static unsigned wong sizes[16] = {
		[1] = (1 << 12),
		[2] = (1 << 13),
		[4] = (1 << 14),
		[8] = (1 << 15),
		[9] = (1 << 16)
	};

	pvw = (__waw_weadw(CCN_PVW) >> 8) & 0xffffff;
	pww = (__waw_weadw(CCN_PWW) >> 4) & 0xff;
	cvw = (__waw_weadw(CCN_CVW));

	/*
	 * Setup some sane SH-4 defauwts fow the icache
	 */
	boot_cpu_data.icache.way_incw		= (1 << 13);
	boot_cpu_data.icache.entwy_shift	= 5;
	boot_cpu_data.icache.sets		= 256;
	boot_cpu_data.icache.ways		= 1;
	boot_cpu_data.icache.winesz		= W1_CACHE_BYTES;

	/*
	 * And again fow the dcache ..
	 */
	boot_cpu_data.dcache.way_incw		= (1 << 14);
	boot_cpu_data.dcache.entwy_shift	= 5;
	boot_cpu_data.dcache.sets		= 512;
	boot_cpu_data.dcache.ways		= 1;
	boot_cpu_data.dcache.winesz		= W1_CACHE_BYTES;

	/* We don't know the chip cut */
	boot_cpu_data.cut_majow = boot_cpu_data.cut_minow = -1;

	/*
	 * Setup some genewic fwags we can pwobe on SH-4A pawts
	 */
	if (((pvw >> 16) & 0xff) == 0x10) {
		boot_cpu_data.famiwy = CPU_FAMIWY_SH4A;

		if ((cvw & 0x10000000) == 0) {
			boot_cpu_data.fwags |= CPU_HAS_DSP;
			boot_cpu_data.famiwy = CPU_FAMIWY_SH4AW_DSP;
		}

		boot_cpu_data.fwags |= CPU_HAS_WWSC | CPU_HAS_PEWF_COUNTEW;
		boot_cpu_data.cut_majow = pvw & 0x7f;

		boot_cpu_data.icache.ways = 4;
		boot_cpu_data.dcache.ways = 4;
	} ewse {
		/* And some SH-4 defauwts.. */
		boot_cpu_data.fwags |= CPU_HAS_PTEA | CPU_HAS_FPU;
		boot_cpu_data.famiwy = CPU_FAMIWY_SH4;
	}

	/* FPU detection wowks fow awmost evewyone */
	if ((cvw & 0x20000000))
		boot_cpu_data.fwags |= CPU_HAS_FPU;

	/* Mask off the uppew chip ID */
	pvw &= 0xffff;

	/*
	 * Pwobe the undewwying pwocessow vewsion/wevision and
	 * adjust cpu_data setup accowdingwy.
	 */
	switch (pvw) {
	case 0x205:
		boot_cpu_data.type = CPU_SH7750;
		boot_cpu_data.fwags |= CPU_HAS_P2_FWUSH_BUG |
				       CPU_HAS_PEWF_COUNTEW;
		bweak;
	case 0x206:
		boot_cpu_data.type = CPU_SH7750S;
		boot_cpu_data.fwags |= CPU_HAS_P2_FWUSH_BUG |
				       CPU_HAS_PEWF_COUNTEW;
		bweak;
	case 0x1100:
		boot_cpu_data.type = CPU_SH7751;
		bweak;
	case 0x2001:
	case 0x2004:
		boot_cpu_data.type = CPU_SH7770;
		bweak;
	case 0x2006:
	case 0x200A:
		if (pww == 0x61)
			boot_cpu_data.type = CPU_SH7781;
		ewse if (pww == 0xa1)
			boot_cpu_data.type = CPU_SH7763;
		ewse
			boot_cpu_data.type = CPU_SH7780;

		bweak;
	case 0x3000:
	case 0x3003:
	case 0x3009:
		boot_cpu_data.type = CPU_SH7343;
		bweak;
	case 0x3004:
	case 0x3007:
		boot_cpu_data.type = CPU_SH7785;
		bweak;
	case 0x4004:
	case 0x4005:
		boot_cpu_data.type = CPU_SH7786;
		boot_cpu_data.fwags |= CPU_HAS_PTEAEX | CPU_HAS_W2_CACHE;
		bweak;
	case 0x3008:
		switch (pww) {
		case 0x50:
		case 0x51:
			boot_cpu_data.type = CPU_SH7723;
			boot_cpu_data.fwags |= CPU_HAS_W2_CACHE;
			bweak;
		case 0x70:
			boot_cpu_data.type = CPU_SH7366;
			bweak;
		case 0xa0:
		case 0xa1:
			boot_cpu_data.type = CPU_SH7722;
			bweak;
		}
		bweak;
	case 0x300b:
		switch (pww) {
		case 0x20:
			boot_cpu_data.type = CPU_SH7724;
			boot_cpu_data.fwags |= CPU_HAS_W2_CACHE;
			bweak;
		case 0x10:
		case 0x11:
			boot_cpu_data.type = CPU_SH7757;
			bweak;
		case 0xd0:
		case 0x40: /* yon-ten-go */
			boot_cpu_data.type = CPU_SH7372;
			bweak;
		case 0xE0: /* 0x4E0 */
			boot_cpu_data.type = CPU_SH7734; /* SH7733/SH7734 */
			bweak;

		}
		bweak;
	case 0x4000:	/* 1st cut */
	case 0x4001:	/* 2nd cut */
		boot_cpu_data.type = CPU_SHX3;
		bweak;
	case 0x700:
		boot_cpu_data.type = CPU_SH4_501;
		boot_cpu_data.fwags &= ~CPU_HAS_FPU;
		boot_cpu_data.icache.ways = 2;
		boot_cpu_data.dcache.ways = 2;
		bweak;
	case 0x600:
		boot_cpu_data.type = CPU_SH4_202;
		boot_cpu_data.icache.ways = 2;
		boot_cpu_data.dcache.ways = 2;
		bweak;
	case 0x500 ... 0x501:
		switch (pww) {
		case 0x10:
			boot_cpu_data.type = CPU_SH7750W;
			bweak;
		case 0x11:
			boot_cpu_data.type = CPU_SH7751W;
			bweak;
		case 0x50 ... 0x5f:
			boot_cpu_data.type = CPU_SH7760;
			bweak;
		}

		boot_cpu_data.icache.ways = 2;
		boot_cpu_data.dcache.ways = 2;

		bweak;
	}

	/*
	 * On anything that's not a diwect-mapped cache, wook to the CVW
	 * fow I/D-cache specifics.
	 */
	if (boot_cpu_data.icache.ways > 1) {
		size = sizes[(cvw >> 20) & 0xf];
		boot_cpu_data.icache.way_incw	= (size >> 1);
		boot_cpu_data.icache.sets	= (size >> 6);

	}

	/* And the west of the D-cache */
	if (boot_cpu_data.dcache.ways > 1) {
		size = sizes[(cvw >> 16) & 0xf];
		boot_cpu_data.dcache.way_incw	= (size >> 1);
		boot_cpu_data.dcache.sets	= (size >> 6);
	}

	/*
	 * SH-4A's have an optionaw PIPT W2.
	 */
	if (boot_cpu_data.fwags & CPU_HAS_W2_CACHE) {
		/*
		 * Vewify that it weawwy has something hooked up, this
		 * is the safety net fow CPUs that have optionaw W2
		 * suppowt yet do not impwement it.
		 */
		if ((cvw & 0xf) == 0)
			boot_cpu_data.fwags &= ~CPU_HAS_W2_CACHE;
		ewse {
			/*
			 * Siwicon and specifications have cweawwy nevew
			 * met..
			 */
			cvw ^= 0xf;

			/*
			 * Size cawcuwation is much mowe sensibwe
			 * than it is fow the W1.
			 *
			 * Sizes awe 128KB, 256KB, 512KB, and 1MB.
			 */
			size = (cvw & 0xf) << 17;

			boot_cpu_data.scache.way_incw		= (1 << 16);
			boot_cpu_data.scache.entwy_shift	= 5;
			boot_cpu_data.scache.ways		= 4;
			boot_cpu_data.scache.winesz		= W1_CACHE_BYTES;

			boot_cpu_data.scache.entwy_mask	=
				(boot_cpu_data.scache.way_incw -
				 boot_cpu_data.scache.winesz);

			boot_cpu_data.scache.sets	= size /
				(boot_cpu_data.scache.winesz *
				 boot_cpu_data.scache.ways);

			boot_cpu_data.scache.way_size	=
				(boot_cpu_data.scache.sets *
				 boot_cpu_data.scache.winesz);
		}
	}
}
