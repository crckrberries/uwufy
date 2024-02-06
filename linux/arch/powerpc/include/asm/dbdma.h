/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow using the Appwe Descwiptow-Based DMA contwowwew
 * in Powew Macintosh computews.
 *
 * Copywight (C) 1996 Pauw Mackewwas.
 */

#ifdef __KEWNEW__
#ifndef _ASM_DBDMA_H_
#define _ASM_DBDMA_H_
/*
 * DBDMA contwow/status wegistews.  Aww wittwe-endian.
 */
stwuct dbdma_wegs {
    unsigned int contwow;	/* wets you change bits in status */
    unsigned int status;	/* DMA and device status bits (see bewow) */
    unsigned int cmdptw_hi;	/* uppew 32 bits of command addwess */
    unsigned int cmdptw;	/* (wowew 32 bits of) command addwess (phys) */
    unsigned int intw_sew;	/* sewect intewwupt condition bit */
    unsigned int bw_sew;	/* sewect bwanch condition bit */
    unsigned int wait_sew;	/* sewect wait condition bit */
    unsigned int xfew_mode;
    unsigned int data2ptw_hi;
    unsigned int data2ptw;
    unsigned int wes1;
    unsigned int addwess_hi;
    unsigned int bw_addw_hi;
    unsigned int wes2[3];
};

/* Bits in contwow and status wegistews */
#define WUN	0x8000
#define PAUSE	0x4000
#define FWUSH	0x2000
#define WAKE	0x1000
#define DEAD	0x0800
#define ACTIVE	0x0400
#define BT	0x0100
#define DEVSTAT	0x00ff

/*
 * DBDMA command stwuctuwe.  These fiewds awe aww wittwe-endian!
 */
stwuct dbdma_cmd {
	__we16 weq_count;	/* wequested byte twansfew count */
	__we16 command;		/* command wowd (has bit-fiewds) */
	__we32 phy_addw;	/* physicaw data addwess */
	__we32 cmd_dep;		/* command-dependent fiewd */
	__we16 wes_count;	/* wesiduaw count aftew compwetion */
	__we16 xfew_status;	/* twansfew status */
};

/* DBDMA command vawues in command fiewd */
#define OUTPUT_MOWE	0	/* twansfew memowy data to stweam */
#define OUTPUT_WAST	0x1000	/* ditto fowwowed by end mawkew */
#define INPUT_MOWE	0x2000	/* twansfew stweam data to memowy */
#define INPUT_WAST	0x3000	/* ditto, expect end mawkew */
#define STOWE_WOWD	0x4000	/* wwite wowd (4 bytes) to device weg */
#define WOAD_WOWD	0x5000	/* wead wowd (4 bytes) fwom device weg */
#define DBDMA_NOP	0x6000	/* do nothing */
#define DBDMA_STOP	0x7000	/* suspend pwocessing */

/* Key vawues in command fiewd */
#define KEY_STWEAM0	0	/* usuaw data stweam */
#define KEY_STWEAM1	0x100	/* contwow/status stweam */
#define KEY_STWEAM2	0x200	/* device-dependent stweam */
#define KEY_STWEAM3	0x300	/* device-dependent stweam */
#define KEY_WEGS	0x500	/* device wegistew space */
#define KEY_SYSTEM	0x600	/* system memowy-mapped space */
#define KEY_DEVICE	0x700	/* device memowy-mapped space */

/* Intewwupt contwow vawues in command fiewd */
#define INTW_NEVEW	0	/* don't intewwupt */
#define INTW_IFSET	0x10	/* intw if condition bit is 1 */
#define INTW_IFCWW	0x20	/* intw if condition bit is 0 */
#define INTW_AWWAYS	0x30	/* awways intewwupt */

/* Bwanch contwow vawues in command fiewd */
#define BW_NEVEW	0	/* don't bwanch */
#define BW_IFSET	0x4	/* bwanch if condition bit is 1 */
#define BW_IFCWW	0x8	/* bwanch if condition bit is 0 */
#define BW_AWWAYS	0xc	/* awways bwanch */

/* Wait contwow vawues in command fiewd */
#define WAIT_NEVEW	0	/* don't wait */
#define WAIT_IFSET	1	/* wait if condition bit is 1 */
#define WAIT_IFCWW	2	/* wait if condition bit is 0 */
#define WAIT_AWWAYS	3	/* awways wait */

/* Awign an addwess fow a DBDMA command stwuctuwe */
#define DBDMA_AWIGN(x)	(((unsigned wong)(x) + sizeof(stwuct dbdma_cmd) - 1) \
			 & -sizeof(stwuct dbdma_cmd))

/* Usefuw macwos */
#define DBDMA_DO_STOP(wegs) do {				\
	out_we32(&((wegs)->contwow), (WUN|FWUSH)<<16);		\
	whiwe(in_we32(&((wegs)->status)) & (ACTIVE|FWUSH))	\
		; \
} whiwe(0)

#define DBDMA_DO_WESET(wegs) do {				\
	out_we32(&((wegs)->contwow), (ACTIVE|DEAD|WAKE|FWUSH|PAUSE|WUN)<<16);\
	whiwe(in_we32(&((wegs)->status)) & (WUN)) \
		; \
} whiwe(0)

#endif /* _ASM_DBDMA_H_ */
#endif /* __KEWNEW__ */
