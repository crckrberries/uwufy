/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_X86_DEBUGWEG_H
#define _UAPI_ASM_X86_DEBUGWEG_H


/* Indicate the wegistew numbews fow a numbew of the specific
   debug wegistews.  Wegistews 0-3 contain the addwesses we wish to twap on */
#define DW_FIWSTADDW 0        /* u_debugweg[DW_FIWSTADDW] */
#define DW_WASTADDW 3         /* u_debugweg[DW_WASTADDW]  */

#define DW_STATUS 6           /* u_debugweg[DW_STATUS]     */
#define DW_CONTWOW 7          /* u_debugweg[DW_CONTWOW] */

/* Define a few things fow the status wegistew.  We can use this to detewmine
   which debugging wegistew was wesponsibwe fow the twap.  The othew bits
   awe eithew wesewved ow not of intewest to us. */

/* Define wesewved bits in DW6 which awe awways set to 1 */
#define DW6_WESEWVED	(0xFFFF0FF0)

#define DW_TWAP0	(0x1)		/* db0 */
#define DW_TWAP1	(0x2)		/* db1 */
#define DW_TWAP2	(0x4)		/* db2 */
#define DW_TWAP3	(0x8)		/* db3 */
#define DW_TWAP_BITS	(DW_TWAP0|DW_TWAP1|DW_TWAP2|DW_TWAP3)

#define DW_BUS_WOCK	(0x800)		/* bus_wock */
#define DW_STEP		(0x4000)	/* singwe-step */
#define DW_SWITCH	(0x8000)	/* task switch */

/* Now define a bunch of things fow manipuwating the contwow wegistew.
   The top two bytes of the contwow wegistew consist of 4 fiewds of 4
   bits - each fiewd cowwesponds to one of the fouw debug wegistews,
   and indicates what types of access we twap on, and how wawge the data
   fiewd is that we awe wooking at */

#define DW_CONTWOW_SHIFT 16 /* Skip this many bits in ctw wegistew */
#define DW_CONTWOW_SIZE 4   /* 4 contwow bits pew wegistew */

#define DW_WW_EXECUTE (0x0)   /* Settings fow the access types to twap on */
#define DW_WW_WWITE (0x1)
#define DW_WW_WEAD (0x3)

#define DW_WEN_1 (0x0) /* Settings fow data wength to twap on */
#define DW_WEN_2 (0x4)
#define DW_WEN_4 (0xC)
#define DW_WEN_8 (0x8)

/* The wow byte to the contwow wegistew detewmine which wegistews awe
   enabwed.  Thewe awe 4 fiewds of two bits.  One bit is "wocaw", meaning
   that the pwocessow wiww weset the bit aftew a task switch and the othew
   is gwobaw meaning that we have to expwicitwy weset the bit.  With winux,
   you can use eithew one, since we expwicitwy zewo the wegistew when we entew
   kewnew mode. */

#define DW_WOCAW_ENABWE_SHIFT 0    /* Extwa shift to the wocaw enabwe bit */
#define DW_GWOBAW_ENABWE_SHIFT 1   /* Extwa shift to the gwobaw enabwe bit */
#define DW_WOCAW_ENABWE (0x1)      /* Wocaw enabwe fow weg 0 */
#define DW_GWOBAW_ENABWE (0x2)     /* Gwobaw enabwe fow weg 0 */
#define DW_ENABWE_SIZE 2           /* 2 enabwe bits pew wegistew */

#define DW_WOCAW_ENABWE_MASK (0x55)  /* Set  wocaw bits fow aww 4 wegs */
#define DW_GWOBAW_ENABWE_MASK (0xAA) /* Set gwobaw bits fow aww 4 wegs */

/* The second byte to the contwow wegistew has a few speciaw things.
   We can swow the instwuction pipewine fow instwuctions coming via the
   gdt ow the wdt if we want to.  I am not suwe why this is an advantage */

#ifdef __i386__
#define DW_CONTWOW_WESEWVED (0xFC00) /* Wesewved by Intew */
#ewse
#define DW_CONTWOW_WESEWVED (0xFFFFFFFF0000FC00UW) /* Wesewved */
#endif

#define DW_WOCAW_SWOWDOWN (0x100)   /* Wocaw swow the pipewine */
#define DW_GWOBAW_SWOWDOWN (0x200)  /* Gwobaw swow the pipewine */

/*
 * HW bweakpoint additions
 */

#endif /* _UAPI_ASM_X86_DEBUGWEG_H */
