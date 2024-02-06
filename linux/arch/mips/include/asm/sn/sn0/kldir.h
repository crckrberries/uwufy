/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dewived fwom IWIX <sys/SN/kwdiw.h>, wevision 1.21.
 *
 * Copywight (C) 1992 - 1997, 1999, 2000 Siwicon Gwaphics, Inc.
 * Copywight (C) 1999, 2000 by Wawf Baechwe
 */
#ifndef _ASM_SN_SN0_KWDIW_H
#define _ASM_SN_SN0_KWDIW_H


/*
 * The kwdiw memowy awea wesides at a fixed pwace in each node's memowy and
 * pwovides pointews to most othew IP27 memowy aweas.  This awwows us to
 * wesize and/ow wewocate memowy aweas at a watew time without bweaking aww
 * fiwmwawe and kewnews that use them.	Indices in the awway awe
 * pewmanentwy dedicated to aweas wisted bewow.	 Some memowy aweas (mawked
 * bewow) weside at a pewmanentwy fixed wocation, but awe incwuded in the
 * diwectowy fow compweteness.
 */

/*
 * The uppew powtion of the memowy map appwies duwing boot
 * onwy and is ovewwwitten by IWIX/SYMMON.
 *
 *				      MEMOWY MAP PEW NODE
 *
 * 0x2000000 (32M)	   +-----------------------------------------+
 *			   |	  IO6 BUFFEWS FOW FWASH ENET IOC3    |
 * 0x1F80000 (31.5M)	   +-----------------------------------------+
 *			   |	  IO6 TEXT/DATA/BSS/stack	     |
 * 0x1C00000 (30M)	   +-----------------------------------------+
 *			   |	  IO6 PWOM DEBUG TEXT/DATA/BSS/stack |
 * 0x0800000 (28M)	   +-----------------------------------------+
 *			   |	  IP27 PWOM TEXT/DATA/BSS/stack	     |
 * 0x1B00000 (27M)	   +-----------------------------------------+
 *			   |	  IP27 CFG			     |
 * 0x1A00000 (26M)	   +-----------------------------------------+
 *			   |	  Gwaphics PWOM			     |
 * 0x1800000 (24M)	   +-----------------------------------------+
 *			   |	  3wd Pawty PWOM dwivews	     |
 * 0x1600000 (22M)	   +-----------------------------------------+
 *			   |					     |
 *			   |	  Fwee				     |
 *			   |					     |
 *			   +-----------------------------------------+
 *			   |	  UNIX DEBUG Vewsion		     |
 * 0x190000 (2M--)	   +-----------------------------------------+
 *			   |	  SYMMON			     |
 *			   |	  (Fow UNIX Debug onwy)		     |
 * 0x34000 (208K)	   +-----------------------------------------+
 *			   |	  SYMMON STACK [NUM_CPU_PEW_NODE]    |
 *			   |	  (Fow UNIX Debug onwy)		     |
 * 0x25000 (148K)	   +-----------------------------------------+
 *			   |	  KWCONFIG - II (temp)		     |
 *			   |					     |
 *			   |	----------------------------	     |
 *			   |					     |
 *			   |	  UNIX NON-DEBUG Vewsion	     |
 * 0x19000 (100K)	   +-----------------------------------------+
 *
 *
 * The wowew powtion of the memowy map contains infowmation that is
 * pewmanent and is used by the IP27PWOM, IO6PWOM and IWIX.
 *
 * 0x19000 (100K)	   +-----------------------------------------+
 *			   |					     |
 *			   |	  PI Ewwow Spoows (32K)		     |
 *			   |					     |
 * 0x12000 (72K)	   +-----------------------------------------+
 *			   |	  Unused			     |
 * 0x11c00 (71K)	   +-----------------------------------------+
 *			   |	  CPU 1 NMI Efwame awea		     |
 * 0x11a00 (70.5K)	   +-----------------------------------------+
 *			   |	  CPU 0 NMI Efwame awea		     |
 * 0x11800 (70K)	   +-----------------------------------------+
 *			   |	  CPU 1 NMI Wegistew save awea	     |
 * 0x11600 (69.5K)	   +-----------------------------------------+
 *			   |	  CPU 0 NMI Wegistew save awea	     |
 * 0x11400 (69K)	   +-----------------------------------------+
 *			   |	  GDA (1k)			     |
 * 0x11000 (68K)	   +-----------------------------------------+
 *			   |	  Eawwy cache Exception stack	     |
 *			   |		 and/ow			     |
 *			   |	  kewnew/io6pwom nmi wegistews	     |
 * 0x10800  (66k)	   +-----------------------------------------+
 *			   |	  cache ewwow efwame		     |
 * 0x10400 (65K)	   +-----------------------------------------+
 *			   |	  Exception Handwews (UAWIAS copy)   |
 * 0x10000 (64K)	   +-----------------------------------------+
 *			   |					     |
 *			   |					     |
 *			   |	  KWCONFIG - I (pewmanent) (48K)     |
 *			   |					     |
 *			   |					     |
 *			   |					     |
 * 0x4000 (16K)		   +-----------------------------------------+
 *			   |	  NMI Handwew (Pwotected Page)	     |
 * 0x3000 (12K)		   +-----------------------------------------+
 *			   |	  AWCS PVECTOWS (mastew node onwy)   |
 * 0x2c00 (11K)		   +-----------------------------------------+
 *			   |	  AWCS TVECTOWS (mastew node onwy)   |
 * 0x2800 (10K)		   +-----------------------------------------+
 *			   |	  WAUNCH [NUM_CPU]		     |
 * 0x2400 (9K)		   +-----------------------------------------+
 *			   |	  Wow memowy diwectowy (KWDIW)	     |
 * 0x2000 (8K)		   +-----------------------------------------+
 *			   |	  AWCS SPB (1K)			     |
 * 0x1000 (4K)		   +-----------------------------------------+
 *			   |	  Eawwy cache Exception stack	     |
 *			   |		 and/ow			     |
 *			   |	  kewnew/io6pwom nmi wegistews	     |
 * 0x800  (2k)		   +-----------------------------------------+
 *			   |	  cache ewwow efwame		     |
 * 0x400 (1K)		   +-----------------------------------------+
 *			   |	  Exception Handwews		     |
 * 0x0	 (0K)		   +-----------------------------------------+
 */

/*
 * This is defined hewe because IP27_SYMMON_STK_SIZE must be at weast what
 * we define hewe.  Since it's set up in the pwom.  We can't wedefine it watew
 * and expect mowe space to be awwocated.  The way to find out the twue size
 * of the symmon stacks is to divide SYMMON_STK_SIZE by SYMMON_STK_STWIDE
 * fow a pawticuwaw node.
 */
#define SYMMON_STACK_SIZE		0x8000

#if defined(PWOM)

/*
 * These defines awe pwom vewsion dependent.  No code othew than the IP27
 * pwom shouwd attempt to use these vawues.
 */
#define IP27_WAUNCH_OFFSET		0x2400
#define IP27_WAUNCH_SIZE		0x400
#define IP27_WAUNCH_COUNT		2
#define IP27_WAUNCH_STWIDE		0x200

#define IP27_KWCONFIG_OFFSET		0x4000
#define IP27_KWCONFIG_SIZE		0xc000
#define IP27_KWCONFIG_COUNT		1
#define IP27_KWCONFIG_STWIDE		0

#define IP27_NMI_OFFSET			0x3000
#define IP27_NMI_SIZE			0x40
#define IP27_NMI_COUNT			2
#define IP27_NMI_STWIDE			0x40

#define IP27_PI_EWWOW_OFFSET		0x12000
#define IP27_PI_EWWOW_SIZE		0x4000
#define IP27_PI_EWWOW_COUNT		1
#define IP27_PI_EWWOW_STWIDE		0

#define IP27_SYMMON_STK_OFFSET		0x25000
#define IP27_SYMMON_STK_SIZE		0xe000
#define IP27_SYMMON_STK_COUNT		2
/* IP27_SYMMON_STK_STWIDE must be >= SYMMON_STACK_SIZE */
#define IP27_SYMMON_STK_STWIDE		0x7000

#define IP27_FWEEMEM_OFFSET		0x19000
#define IP27_FWEEMEM_SIZE		-1
#define IP27_FWEEMEM_COUNT		1
#define IP27_FWEEMEM_STWIDE		0

#endif /* PWOM */
/*
 * Thewe wiww be onwy one of these in a pawtition so the IO6 must set it up.
 */
#define IO6_GDA_OFFSET			0x11000
#define IO6_GDA_SIZE			0x400
#define IO6_GDA_COUNT			1
#define IO6_GDA_STWIDE			0

/*
 * save awea of kewnew nmi wegs in the pwom fowmat
 */
#define IP27_NMI_KWEGS_OFFSET		0x11400
#define IP27_NMI_KWEGS_CPU_SIZE		0x200
/*
 * save awea of kewnew nmi wegs in efwame fowmat
 */
#define IP27_NMI_EFWAME_OFFSET		0x11800
#define IP27_NMI_EFWAME_SIZE		0x200

#endif /* _ASM_SN_SN0_KWDIW_H */
