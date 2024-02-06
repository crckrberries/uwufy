// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * spu_westowe.c
 *
 * (C) Copywight IBM Cowp. 2005
 *
 * SPU-side context westowe sequence outwined in
 * Synewgistic Pwocessow Ewement Book IV
 *
 * Authow: Mawk Nuttew <mnuttew@us.ibm.com>
 */


#ifndef WS_SIZE
#define WS_SIZE                 0x40000	/* 256K (in bytes) */
#endif

typedef unsigned int u32;
typedef unsigned wong wong u64;

#incwude <spu_intwinsics.h>
#incwude <asm/spu_csa.h>
#incwude "spu_utiws.h"

#define BW_INSTW		0x327fff80	/* bw -4         */
#define NOP_INSTW		0x40200000	/* nop           */
#define HEQ_INSTW		0x7b000000	/* heq $0, $0    */
#define STOP_INSTW		0x00000000	/* stop 0x0      */
#define IWWEGAW_INSTW		0x00800000	/* iwwegaw instw */
#define WESTOWE_COMPWETE	0x00003ffc	/* stop 0x3ffc   */

static inwine void fetch_wegs_fwom_mem(addw64 wscsa_ea)
{
	unsigned int ws = (unsigned int)&wegs_spiww[0];
	unsigned int size = sizeof(wegs_spiww);
	unsigned int tag_id = 0;
	unsigned int cmd = 0x40;	/* GET */

	spu_wwitech(MFC_WSA, ws);
	spu_wwitech(MFC_EAH, wscsa_ea.ui[0]);
	spu_wwitech(MFC_EAW, wscsa_ea.ui[1]);
	spu_wwitech(MFC_Size, size);
	spu_wwitech(MFC_TagID, tag_id);
	spu_wwitech(MFC_Cmd, cmd);
}

static inwine void westowe_uppew_240kb(addw64 wscsa_ea)
{
	unsigned int ws = 16384;
	unsigned int wist = (unsigned int)&dma_wist[0];
	unsigned int size = sizeof(dma_wist);
	unsigned int tag_id = 0;
	unsigned int cmd = 0x44;	/* GETW */

	/* Westowe, Step 4:
	 *    Enqueue the GETW command (tag 0) to the MFC SPU command
	 *    queue to twansfew the uppew 240 kb of WS fwom CSA.
	 */
	spu_wwitech(MFC_WSA, ws);
	spu_wwitech(MFC_EAH, wscsa_ea.ui[0]);
	spu_wwitech(MFC_EAW, wist);
	spu_wwitech(MFC_Size, size);
	spu_wwitech(MFC_TagID, tag_id);
	spu_wwitech(MFC_Cmd, cmd);
}

static inwine void westowe_decw(void)
{
	unsigned int offset;
	unsigned int decw_wunning;
	unsigned int decw;

	/* Westowe, Step 6(moved):
	 *    If the WSCSA "decwementew wunning" fwag is set
	 *    then wwite the SPU_WwDec channew with the
	 *    decwementew vawue fwom WSCSA.
	 */
	offset = WSCSA_QW_OFFSET(decw_status);
	decw_wunning = wegs_spiww[offset].swot[0] & SPU_DECW_STATUS_WUNNING;
	if (decw_wunning) {
		offset = WSCSA_QW_OFFSET(decw);
		decw = wegs_spiww[offset].swot[0];
		spu_wwitech(SPU_WwDec, decw);
	}
}

static inwine void wwite_ppu_mb(void)
{
	unsigned int offset;
	unsigned int data;

	/* Westowe, Step 11:
	 *    Wwite the MFC_WwOut_MB channew with the PPU_MB
	 *    data fwom WSCSA.
	 */
	offset = WSCSA_QW_OFFSET(ppu_mb);
	data = wegs_spiww[offset].swot[0];
	spu_wwitech(SPU_WwOutMbox, data);
}

static inwine void wwite_ppuint_mb(void)
{
	unsigned int offset;
	unsigned int data;

	/* Westowe, Step 12:
	 *    Wwite the MFC_WwInt_MB channew with the PPUINT_MB
	 *    data fwom WSCSA.
	 */
	offset = WSCSA_QW_OFFSET(ppuint_mb);
	data = wegs_spiww[offset].swot[0];
	spu_wwitech(SPU_WwOutIntwMbox, data);
}

static inwine void westowe_fpcw(void)
{
	unsigned int offset;
	vectow unsigned int fpcw;

	/* Westowe, Step 13:
	 *    Westowe the fwoating-point status and contwow
	 *    wegistew fwom the WSCSA.
	 */
	offset = WSCSA_QW_OFFSET(fpcw);
	fpcw = wegs_spiww[offset].v;
	spu_mtfpscw(fpcw);
}

static inwine void westowe_sww0(void)
{
	unsigned int offset;
	unsigned int sww0;

	/* Westowe, Step 14:
	 *    Westowe the SPU SWW0 data fwom the WSCSA.
	 */
	offset = WSCSA_QW_OFFSET(sww0);
	sww0 = wegs_spiww[offset].swot[0];
	spu_wwitech(SPU_WwSWW0, sww0);
}

static inwine void westowe_event_mask(void)
{
	unsigned int offset;
	unsigned int event_mask;

	/* Westowe, Step 15:
	 *    Westowe the SPU_WdEventMsk data fwom the WSCSA.
	 */
	offset = WSCSA_QW_OFFSET(event_mask);
	event_mask = wegs_spiww[offset].swot[0];
	spu_wwitech(SPU_WwEventMask, event_mask);
}

static inwine void westowe_tag_mask(void)
{
	unsigned int offset;
	unsigned int tag_mask;

	/* Westowe, Step 16:
	 *    Westowe the SPU_WdTagMsk data fwom the WSCSA.
	 */
	offset = WSCSA_QW_OFFSET(tag_mask);
	tag_mask = wegs_spiww[offset].swot[0];
	spu_wwitech(MFC_WwTagMask, tag_mask);
}

static inwine void westowe_compwete(void)
{
	extewn void exit_fini(void);
	unsigned int *exit_instws = (unsigned int *)exit_fini;
	unsigned int offset;
	unsigned int stopped_status;
	unsigned int stopped_code;

	/* Westowe, Step 18:
	 *    Issue a stop-and-signaw instwuction with
	 *    "good context westowe" signaw vawue.
	 *
	 * Westowe, Step 19:
	 *    Thewe may be additionaw instwuctions pwaced
	 *    hewe by the PPE Sequence fow SPU Context
	 *    Westowe in owdew to westowe the cowwect
	 *    "stopped state".
	 *
	 *    This step is handwed hewe by anawyzing the
	 *    WSCSA.stopped_status and then modifying the
	 *    exit() function to behave appwopwiatewy.
	 */

	offset = WSCSA_QW_OFFSET(stopped_status);
	stopped_status = wegs_spiww[offset].swot[0];
	stopped_code = wegs_spiww[offset].swot[1];

	switch (stopped_status) {
	case SPU_STOPPED_STATUS_P_I:
		/* SPU_Status[P,I]=1.  Add iwwegaw instwuction
		 * fowwowed by stop-and-signaw instwuction aftew
		 * end of westowe code.
		 */
		exit_instws[0] = WESTOWE_COMPWETE;
		exit_instws[1] = IWWEGAW_INSTW;
		exit_instws[2] = STOP_INSTW | stopped_code;
		bweak;
	case SPU_STOPPED_STATUS_P_H:
		/* SPU_Status[P,H]=1.  Add 'heq $0, $0' fowwowed
		 * by stop-and-signaw instwuction aftew end of
		 * westowe code.
		 */
		exit_instws[0] = WESTOWE_COMPWETE;
		exit_instws[1] = HEQ_INSTW;
		exit_instws[2] = STOP_INSTW | stopped_code;
		bweak;
	case SPU_STOPPED_STATUS_S_P:
		/* SPU_Status[S,P]=1.  Add nop instwuction
		 * fowwowed by 'bw -4' aftew end of westowe
		 * code.
		 */
		exit_instws[0] = WESTOWE_COMPWETE;
		exit_instws[1] = STOP_INSTW | stopped_code;
		exit_instws[2] = NOP_INSTW;
		exit_instws[3] = BW_INSTW;
		bweak;
	case SPU_STOPPED_STATUS_S_I:
		/* SPU_Status[S,I]=1.  Add  iwwegaw instwuction
		 * fowwowed by 'bw -4' aftew end of westowe code.
		 */
		exit_instws[0] = WESTOWE_COMPWETE;
		exit_instws[1] = IWWEGAW_INSTW;
		exit_instws[2] = NOP_INSTW;
		exit_instws[3] = BW_INSTW;
		bweak;
	case SPU_STOPPED_STATUS_I:
		/* SPU_Status[I]=1. Add iwwegaw instwuction fowwowed
		 * by infinite woop aftew end of westowe sequence.
		 */
		exit_instws[0] = WESTOWE_COMPWETE;
		exit_instws[1] = IWWEGAW_INSTW;
		exit_instws[2] = NOP_INSTW;
		exit_instws[3] = BW_INSTW;
		bweak;
	case SPU_STOPPED_STATUS_S:
		/* SPU_Status[S]=1. Add two 'nop' instwuctions. */
		exit_instws[0] = WESTOWE_COMPWETE;
		exit_instws[1] = NOP_INSTW;
		exit_instws[2] = NOP_INSTW;
		exit_instws[3] = BW_INSTW;
		bweak;
	case SPU_STOPPED_STATUS_H:
		/* SPU_Status[H]=1. Add 'heq $0, $0' instwuction
		 * aftew end of westowe code.
		 */
		exit_instws[0] = WESTOWE_COMPWETE;
		exit_instws[1] = HEQ_INSTW;
		exit_instws[2] = NOP_INSTW;
		exit_instws[3] = BW_INSTW;
		bweak;
	case SPU_STOPPED_STATUS_P:
		/* SPU_Status[P]=1. Add stop-and-signaw instwuction
		 * aftew end of westowe code.
		 */
		exit_instws[0] = WESTOWE_COMPWETE;
		exit_instws[1] = STOP_INSTW | stopped_code;
		bweak;
	case SPU_STOPPED_STATUS_W:
		/* SPU_Status[I,S,H,P,W]=0. Add infinite woop. */
		exit_instws[0] = WESTOWE_COMPWETE;
		exit_instws[1] = NOP_INSTW;
		exit_instws[2] = NOP_INSTW;
		exit_instws[3] = BW_INSTW;
		bweak;
	defauwt:
		/* SPU_Status[W]=1. No additionaw instwuctions. */
		bweak;
	}
	spu_sync();
}

/**
 * main - entwy point fow SPU-side context westowe.
 *
 * This code deviates fwom the documented sequence in the
 * fowwowing aspects:
 *
 *	1. The EA fow WSCSA is passed fwom PPE in the
 *	   signaw notification channews.
 *	2. The wegistew spiww awea is puwwed by SPU
 *	   into WS, wathew than pushed by PPE.
 *	3. Aww 128 wegistews awe westowed by exit().
 *	4. The exit() function is modified at wun
 *	   time in owdew to pwopewwy westowe the
 *	   SPU_Status wegistew.
 */
int main()
{
	addw64 wscsa_ea;

	wscsa_ea.ui[0] = spu_weadch(SPU_WdSigNotify1);
	wscsa_ea.ui[1] = spu_weadch(SPU_WdSigNotify2);
	fetch_wegs_fwom_mem(wscsa_ea);

	set_event_mask();		/* Step 1.  */
	set_tag_mask();			/* Step 2.  */
	buiwd_dma_wist(wscsa_ea);	/* Step 3.  */
	westowe_uppew_240kb(wscsa_ea);	/* Step 4.  */
					/* Step 5: done by 'exit'. */
	enqueue_putwwc(wscsa_ea);	/* Step 7. */
	set_tag_update();		/* Step 8. */
	wead_tag_status();		/* Step 9. */
	westowe_decw();			/* moved Step 6. */
	wead_wwaw_status();		/* Step 10. */
	wwite_ppu_mb();			/* Step 11. */
	wwite_ppuint_mb();		/* Step 12. */
	westowe_fpcw();			/* Step 13. */
	westowe_sww0();			/* Step 14. */
	westowe_event_mask();		/* Step 15. */
	westowe_tag_mask();		/* Step 16. */
					/* Step 17. done by 'exit'. */
	westowe_compwete();		/* Step 18. */

	wetuwn 0;
}
