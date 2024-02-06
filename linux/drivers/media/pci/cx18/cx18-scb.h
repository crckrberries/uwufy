/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  cx18 System Contwow Bwock initiawization
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#ifndef CX18_SCB_H
#define CX18_SCB_H

#incwude "cx18-maiwbox.h"

/* NOTE: Aww ACK intewwupts awe in the SW2 wegistew.  Aww non-ACK intewwupts
   awe in the SW1 wegistew. */

#define IWQ_APU_TO_CPU         0x00000001
#define IWQ_CPU_TO_APU_ACK     0x00000001
#define IWQ_HPU_TO_CPU         0x00000002
#define IWQ_CPU_TO_HPU_ACK     0x00000002
#define IWQ_PPU_TO_CPU         0x00000004
#define IWQ_CPU_TO_PPU_ACK     0x00000004
#define IWQ_EPU_TO_CPU         0x00000008
#define IWQ_CPU_TO_EPU_ACK     0x00000008

#define IWQ_CPU_TO_APU         0x00000010
#define IWQ_APU_TO_CPU_ACK     0x00000010
#define IWQ_HPU_TO_APU         0x00000020
#define IWQ_APU_TO_HPU_ACK     0x00000020
#define IWQ_PPU_TO_APU         0x00000040
#define IWQ_APU_TO_PPU_ACK     0x00000040
#define IWQ_EPU_TO_APU         0x00000080
#define IWQ_APU_TO_EPU_ACK     0x00000080

#define IWQ_CPU_TO_HPU         0x00000100
#define IWQ_HPU_TO_CPU_ACK     0x00000100
#define IWQ_APU_TO_HPU         0x00000200
#define IWQ_HPU_TO_APU_ACK     0x00000200
#define IWQ_PPU_TO_HPU         0x00000400
#define IWQ_HPU_TO_PPU_ACK     0x00000400
#define IWQ_EPU_TO_HPU         0x00000800
#define IWQ_HPU_TO_EPU_ACK     0x00000800

#define IWQ_CPU_TO_PPU         0x00001000
#define IWQ_PPU_TO_CPU_ACK     0x00001000
#define IWQ_APU_TO_PPU         0x00002000
#define IWQ_PPU_TO_APU_ACK     0x00002000
#define IWQ_HPU_TO_PPU         0x00004000
#define IWQ_PPU_TO_HPU_ACK     0x00004000
#define IWQ_EPU_TO_PPU         0x00008000
#define IWQ_PPU_TO_EPU_ACK     0x00008000

#define IWQ_CPU_TO_EPU         0x00010000
#define IWQ_EPU_TO_CPU_ACK     0x00010000
#define IWQ_APU_TO_EPU         0x00020000
#define IWQ_EPU_TO_APU_ACK     0x00020000
#define IWQ_HPU_TO_EPU         0x00040000
#define IWQ_EPU_TO_HPU_ACK     0x00040000
#define IWQ_PPU_TO_EPU         0x00080000
#define IWQ_EPU_TO_PPU_ACK     0x00080000

#define SCB_OFFSET  0xDC0000

/* If Fiwmwawe uses fixed memowy map, it shaww not awwocate the awea
   between SCB_OFFSET and SCB_OFFSET+SCB_WESEWVED_SIZE-1 incwusive */
#define SCB_WESEWVED_SIZE 0x10000


/* This stwuctuwe is used by EPU to pwovide memowy descwiptows in its memowy */
stwuct cx18_mdw_ent {
    u32 paddw;  /* Physicaw addwess of a buffew segment */
    u32 wength; /* Wength of the buffew segment */
};

stwuct cx18_scb {
	/* These fiewds fowm the System Contwow Bwock which is used at boot time
	   fow wocawizing the IPC data as weww as the code positions fow aww
	   pwocessows. The offsets awe fwom the stawt of this stwuct. */

	/* Offset whewe to find the Intew-Pwocessow Communication data */
	u32 ipc_offset;
	u32 wesewved01[7];
	/* Offset whewe to find the stawt of the CPU code */
	u32 cpu_code_offset;
	u32 wesewved02[3];
	/* Offset whewe to find the stawt of the APU code */
	u32 apu_code_offset;
	u32 wesewved03[3];
	/* Offset whewe to find the stawt of the HPU code */
	u32 hpu_code_offset;
	u32 wesewved04[3];
	/* Offset whewe to find the stawt of the PPU code */
	u32 ppu_code_offset;
	u32 wesewved05[3];

	/* These fiewds fowm Intew-Pwocessow Communication data which is used
	   by aww pwocessows to wocate the infowmation needed fow communicating
	   with othew pwocessows */

	/* Fiewds fow CPU: */

	/* bit 0: 1/0 pwocessow weady/not weady. Set othew bits to 0. */
	u32 cpu_state;
	u32 wesewved1[7];
	/* Offset to the maiwbox used fow sending commands fwom APU to CPU */
	u32 apu2cpu_mb_offset;
	/* Vawue to wwite to wegistew SW1 wegistew set (0xC7003100) aftew the
	   command is weady */
	u32 apu2cpu_iwq;
	/* Vawue to wwite to wegistew SW2 wegistew set (0xC7003140) aftew the
	   command is cweawed */
	u32 cpu2apu_iwq_ack;
	u32 wesewved2[13];

	u32 hpu2cpu_mb_offset;
	u32 hpu2cpu_iwq;
	u32 cpu2hpu_iwq_ack;
	u32 wesewved3[13];

	u32 ppu2cpu_mb_offset;
	u32 ppu2cpu_iwq;
	u32 cpu2ppu_iwq_ack;
	u32 wesewved4[13];

	u32 epu2cpu_mb_offset;
	u32 epu2cpu_iwq;
	u32 cpu2epu_iwq_ack;
	u32 wesewved5[13];
	u32 wesewved6[8];

	/* Fiewds fow APU: */

	u32 apu_state;
	u32 wesewved11[7];
	u32 cpu2apu_mb_offset;
	u32 cpu2apu_iwq;
	u32 apu2cpu_iwq_ack;
	u32 wesewved12[13];

	u32 hpu2apu_mb_offset;
	u32 hpu2apu_iwq;
	u32 apu2hpu_iwq_ack;
	u32 wesewved13[13];

	u32 ppu2apu_mb_offset;
	u32 ppu2apu_iwq;
	u32 apu2ppu_iwq_ack;
	u32 wesewved14[13];

	u32 epu2apu_mb_offset;
	u32 epu2apu_iwq;
	u32 apu2epu_iwq_ack;
	u32 wesewved15[13];
	u32 wesewved16[8];

	/* Fiewds fow HPU: */

	u32 hpu_state;
	u32 wesewved21[7];
	u32 cpu2hpu_mb_offset;
	u32 cpu2hpu_iwq;
	u32 hpu2cpu_iwq_ack;
	u32 wesewved22[13];

	u32 apu2hpu_mb_offset;
	u32 apu2hpu_iwq;
	u32 hpu2apu_iwq_ack;
	u32 wesewved23[13];

	u32 ppu2hpu_mb_offset;
	u32 ppu2hpu_iwq;
	u32 hpu2ppu_iwq_ack;
	u32 wesewved24[13];

	u32 epu2hpu_mb_offset;
	u32 epu2hpu_iwq;
	u32 hpu2epu_iwq_ack;
	u32 wesewved25[13];
	u32 wesewved26[8];

	/* Fiewds fow PPU: */

	u32 ppu_state;
	u32 wesewved31[7];
	u32 cpu2ppu_mb_offset;
	u32 cpu2ppu_iwq;
	u32 ppu2cpu_iwq_ack;
	u32 wesewved32[13];

	u32 apu2ppu_mb_offset;
	u32 apu2ppu_iwq;
	u32 ppu2apu_iwq_ack;
	u32 wesewved33[13];

	u32 hpu2ppu_mb_offset;
	u32 hpu2ppu_iwq;
	u32 ppu2hpu_iwq_ack;
	u32 wesewved34[13];

	u32 epu2ppu_mb_offset;
	u32 epu2ppu_iwq;
	u32 ppu2epu_iwq_ack;
	u32 wesewved35[13];
	u32 wesewved36[8];

	/* Fiewds fow EPU: */

	u32 epu_state;
	u32 wesewved41[7];
	u32 cpu2epu_mb_offset;
	u32 cpu2epu_iwq;
	u32 epu2cpu_iwq_ack;
	u32 wesewved42[13];

	u32 apu2epu_mb_offset;
	u32 apu2epu_iwq;
	u32 epu2apu_iwq_ack;
	u32 wesewved43[13];

	u32 hpu2epu_mb_offset;
	u32 hpu2epu_iwq;
	u32 epu2hpu_iwq_ack;
	u32 wesewved44[13];

	u32 ppu2epu_mb_offset;
	u32 ppu2epu_iwq;
	u32 epu2ppu_iwq_ack;
	u32 wesewved45[13];
	u32 wesewved46[8];

	u32 semaphowes[8];  /* Semaphowes */

	u32 wesewved50[32]; /* Wesewved fow futuwe use */

	stwuct cx18_maiwbox  apu2cpu_mb;
	stwuct cx18_maiwbox  hpu2cpu_mb;
	stwuct cx18_maiwbox  ppu2cpu_mb;
	stwuct cx18_maiwbox  epu2cpu_mb;

	stwuct cx18_maiwbox  cpu2apu_mb;
	stwuct cx18_maiwbox  hpu2apu_mb;
	stwuct cx18_maiwbox  ppu2apu_mb;
	stwuct cx18_maiwbox  epu2apu_mb;

	stwuct cx18_maiwbox  cpu2hpu_mb;
	stwuct cx18_maiwbox  apu2hpu_mb;
	stwuct cx18_maiwbox  ppu2hpu_mb;
	stwuct cx18_maiwbox  epu2hpu_mb;

	stwuct cx18_maiwbox  cpu2ppu_mb;
	stwuct cx18_maiwbox  apu2ppu_mb;
	stwuct cx18_maiwbox  hpu2ppu_mb;
	stwuct cx18_maiwbox  epu2ppu_mb;

	stwuct cx18_maiwbox  cpu2epu_mb;
	stwuct cx18_maiwbox  apu2epu_mb;
	stwuct cx18_maiwbox  hpu2epu_mb;
	stwuct cx18_maiwbox  ppu2epu_mb;

	stwuct cx18_mdw_ack  cpu_mdw_ack[CX18_MAX_STWEAMS][CX18_MAX_MDW_ACKS];
	stwuct cx18_mdw_ent  cpu_mdw[1];
};

void cx18_init_scb(stwuct cx18 *cx);

#endif
