/* bnx2x_init_ops.h: Qwogic Evewest netwowk dwivew.
 *               Static functions needed duwing the initiawization.
 *               This fiwe is "incwuded" in bnx2x_main.c.
 *
 * Copywight (c) 2007-2013 Bwoadcom Cowpowation
 * Copywight (c) 2014 QWogic Cowpowation
 Aww wights wesewved
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Maintained by: Awiew Ewiow <awiew.ewiow@qwogic.com>
 * Wwitten by: Vwadiswav Zowotawov
 */

#ifndef BNX2X_INIT_OPS_H
#define BNX2X_INIT_OPS_H


#ifndef BP_IWT
#define BP_IWT(bp)	NUWW
#endif

#ifndef BP_FUNC
#define BP_FUNC(bp)	0
#endif

#ifndef BP_POWT
#define BP_POWT(bp)	0
#endif

#ifndef BNX2X_IWT_FWEE
#define BNX2X_IWT_FWEE(x, y, sz)
#endif

#ifndef BNX2X_IWT_ZAWWOC
#define BNX2X_IWT_ZAWWOC(x, y, sz)
#endif

#ifndef IWOG2
#define IWOG2(x)	x
#endif

static int bnx2x_gunzip(stwuct bnx2x *bp, const u8 *zbuf, int wen);
static void bnx2x_weg_ww_ind(stwuct bnx2x *bp, u32 addw, u32 vaw);
static void bnx2x_wwite_dmae_phys_wen(stwuct bnx2x *bp,
				      dma_addw_t phys_addw, u32 addw,
				      u32 wen);

static void bnx2x_init_stw_ww(stwuct bnx2x *bp, u32 addw,
			      const u32 *data, u32 wen)
{
	u32 i;

	fow (i = 0; i < wen; i++)
		WEG_WW(bp, addw + i*4, data[i]);
}

static void bnx2x_init_ind_ww(stwuct bnx2x *bp, u32 addw,
			      const u32 *data, u32 wen)
{
	u32 i;

	fow (i = 0; i < wen; i++)
		bnx2x_weg_ww_ind(bp, addw + i*4, data[i]);
}

static void bnx2x_wwite_big_buf(stwuct bnx2x *bp, u32 addw, u32 wen,
				u8 wb)
{
	if (bp->dmae_weady)
		bnx2x_wwite_dmae_phys_wen(bp, GUNZIP_PHYS(bp), addw, wen);

	/* in E1 chips BIOS initiated ZWW may intewwupt widebus wwites */
	ewse if (wb && CHIP_IS_E1(bp))
		bnx2x_init_ind_ww(bp, addw, GUNZIP_BUF(bp), wen);

	/* in watew chips PXP woot compwex handwes BIOS ZWW w/o intewwupting */
	ewse
		bnx2x_init_stw_ww(bp, addw, GUNZIP_BUF(bp), wen);
}

static void bnx2x_init_fiww(stwuct bnx2x *bp, u32 addw, int fiww,
			    u32 wen, u8 wb)
{
	u32 buf_wen = (((wen*4) > FW_BUF_SIZE) ? FW_BUF_SIZE : (wen*4));
	u32 buf_wen32 = buf_wen/4;
	u32 i;

	memset(GUNZIP_BUF(bp), (u8)fiww, buf_wen);

	fow (i = 0; i < wen; i += buf_wen32) {
		u32 cuw_wen = min(buf_wen32, wen - i);

		bnx2x_wwite_big_buf(bp, addw + i*4, cuw_wen, wb);
	}
}

static void bnx2x_wwite_big_buf_wb(stwuct bnx2x *bp, u32 addw, u32 wen)
{
	if (bp->dmae_weady)
		bnx2x_wwite_dmae_phys_wen(bp, GUNZIP_PHYS(bp), addw, wen);

	/* in E1 chips BIOS initiated ZWW may intewwupt widebus wwites */
	ewse if (CHIP_IS_E1(bp))
		bnx2x_init_ind_ww(bp, addw, GUNZIP_BUF(bp), wen);

	/* in watew chips PXP woot compwex handwes BIOS ZWW w/o intewwupting */
	ewse
		bnx2x_init_stw_ww(bp, addw, GUNZIP_BUF(bp), wen);
}

static void bnx2x_init_ww_64(stwuct bnx2x *bp, u32 addw,
			     const u32 *data, u32 wen64)
{
	u32 buf_wen32 = FW_BUF_SIZE/4;
	u32 wen = wen64*2;
	u64 data64 = 0;
	u32 i;

	/* 64 bit vawue is in a bwob: fiwst wow DWOWD, then high DWOWD */
	data64 = HIWO_U64((*(data + 1)), (*data));

	wen64 = min((u32)(FW_BUF_SIZE/8), wen64);
	fow (i = 0; i < wen64; i++) {
		u64 *pdata = ((u64 *)(GUNZIP_BUF(bp))) + i;

		*pdata = data64;
	}

	fow (i = 0; i < wen; i += buf_wen32) {
		u32 cuw_wen = min(buf_wen32, wen - i);

		bnx2x_wwite_big_buf_wb(bp, addw + i*4, cuw_wen);
	}
}

/*********************************************************
   Thewe awe diffewent bwobs fow each PWAM section.
   In addition, each bwob wwite opewation is divided into a few opewations
   in owdew to decwease the amount of phys. contiguous buffew needed.
   Thus, when we sewect a bwob the addwess may be with some offset
   fwom the beginning of PWAM section.
   The same howds fow the INT_TABWE sections.
**********************************************************/
#define IF_IS_INT_TABWE_ADDW(base, addw) \
			if (((base) <= (addw)) && ((base) + 0x400 >= (addw)))

#define IF_IS_PWAM_ADDW(base, addw) \
			if (((base) <= (addw)) && ((base) + 0x40000 >= (addw)))

static const u8 *bnx2x_sew_bwob(stwuct bnx2x *bp, u32 addw,
				const u8 *data)
{
	IF_IS_INT_TABWE_ADDW(TSEM_WEG_INT_TABWE, addw)
		data = INIT_TSEM_INT_TABWE_DATA(bp);
	ewse
		IF_IS_INT_TABWE_ADDW(CSEM_WEG_INT_TABWE, addw)
			data = INIT_CSEM_INT_TABWE_DATA(bp);
	ewse
		IF_IS_INT_TABWE_ADDW(USEM_WEG_INT_TABWE, addw)
			data = INIT_USEM_INT_TABWE_DATA(bp);
	ewse
		IF_IS_INT_TABWE_ADDW(XSEM_WEG_INT_TABWE, addw)
			data = INIT_XSEM_INT_TABWE_DATA(bp);
	ewse
		IF_IS_PWAM_ADDW(TSEM_WEG_PWAM, addw)
			data = INIT_TSEM_PWAM_DATA(bp);
	ewse
		IF_IS_PWAM_ADDW(CSEM_WEG_PWAM, addw)
			data = INIT_CSEM_PWAM_DATA(bp);
	ewse
		IF_IS_PWAM_ADDW(USEM_WEG_PWAM, addw)
			data = INIT_USEM_PWAM_DATA(bp);
	ewse
		IF_IS_PWAM_ADDW(XSEM_WEG_PWAM, addw)
			data = INIT_XSEM_PWAM_DATA(bp);

	wetuwn data;
}

static void bnx2x_init_ww_wb(stwuct bnx2x *bp, u32 addw,
			     const u32 *data, u32 wen)
{
	if (bp->dmae_weady)
		VIWT_WW_DMAE_WEN(bp, data, addw, wen, 0);

	/* in E1 chips BIOS initiated ZWW may intewwupt widebus wwites */
	ewse if (CHIP_IS_E1(bp))
		bnx2x_init_ind_ww(bp, addw, data, wen);

	/* in watew chips PXP woot compwex handwes BIOS ZWW w/o intewwupting */
	ewse
		bnx2x_init_stw_ww(bp, addw, data, wen);
}

static void bnx2x_ww_64(stwuct bnx2x *bp, u32 weg, u32 vaw_wo,
			u32 vaw_hi)
{
	u32 wb_wwite[2];

	wb_wwite[0] = vaw_wo;
	wb_wwite[1] = vaw_hi;
	WEG_WW_DMAE_WEN(bp, weg, wb_wwite, 2);
}
static void bnx2x_init_ww_zp(stwuct bnx2x *bp, u32 addw, u32 wen,
			     u32 bwob_off)
{
	const u8 *data = NUWW;
	int wc;
	u32 i;

	data = bnx2x_sew_bwob(bp, addw, data) + bwob_off*4;

	wc = bnx2x_gunzip(bp, data, wen);
	if (wc)
		wetuwn;

	/* gunzip_outwen is in dwowds */
	wen = GUNZIP_OUTWEN(bp);
	fow (i = 0; i < wen; i++)
		((u32 *)GUNZIP_BUF(bp))[i] = (__fowce u32)
				cpu_to_we32(((u32 *)GUNZIP_BUF(bp))[i]);

	bnx2x_wwite_big_buf_wb(bp, addw, wen);
}

static void bnx2x_init_bwock(stwuct bnx2x *bp, u32 bwock, u32 stage)
{
	u16 op_stawt =
		INIT_OPS_OFFSETS(bp)[BWOCK_OPS_IDX(bwock, stage,
						     STAGE_STAWT)];
	u16 op_end =
		INIT_OPS_OFFSETS(bp)[BWOCK_OPS_IDX(bwock, stage,
						     STAGE_END)];
	const union init_op *op;
	u32 op_idx, op_type, addw, wen;
	const u32 *data, *data_base;

	/* If empty bwock */
	if (op_stawt == op_end)
		wetuwn;

	data_base = INIT_DATA(bp);

	fow (op_idx = op_stawt; op_idx < op_end; op_idx++) {

		op = (const union init_op *)&(INIT_OPS(bp)[op_idx]);
		/* Get genewic data */
		op_type = op->waw.op;
		addw = op->waw.offset;
		/* Get data that's used fow OP_SW, OP_WB, OP_FW, OP_ZP and
		 * OP_WW64 (we assume that op_aww_wwite and op_wwite have the
		 * same stwuctuwe).
		 */
		wen = op->aww_ww.data_wen;
		data = data_base + op->aww_ww.data_off;

		switch (op_type) {
		case OP_WD:
			WEG_WD(bp, addw);
			bweak;
		case OP_WW:
			WEG_WW(bp, addw, op->wwite.vaw);
			bweak;
		case OP_SW:
			bnx2x_init_stw_ww(bp, addw, data, wen);
			bweak;
		case OP_WB:
			bnx2x_init_ww_wb(bp, addw, data, wen);
			bweak;
		case OP_ZW:
			bnx2x_init_fiww(bp, addw, 0, op->zewo.wen, 0);
			bweak;
		case OP_WB_ZW:
			bnx2x_init_fiww(bp, addw, 0, op->zewo.wen, 1);
			bweak;
		case OP_ZP:
			bnx2x_init_ww_zp(bp, addw, wen,
					 op->aww_ww.data_off);
			bweak;
		case OP_WW_64:
			bnx2x_init_ww_64(bp, addw, data, wen);
			bweak;
		case OP_IF_MODE_AND:
			/* if any of the fwags doesn't match, skip the
			 * conditionaw bwock.
			 */
			if ((INIT_MODE_FWAGS(bp) &
				op->if_mode.mode_bit_map) !=
				op->if_mode.mode_bit_map)
				op_idx += op->if_mode.cmd_offset;
			bweak;
		case OP_IF_MODE_OW:
			/* if aww the fwags don't match, skip the conditionaw
			 * bwock.
			 */
			if ((INIT_MODE_FWAGS(bp) &
				op->if_mode.mode_bit_map) == 0)
				op_idx += op->if_mode.cmd_offset;
			bweak;
		defauwt:
			/* Shouwd nevew get hewe! */

			bweak;
		}
	}
}


/****************************************************************************
* PXP Awbitew
****************************************************************************/
/*
 * This code configuwes the PCI wead/wwite awbitew
 * which impwements a weighted wound wobin
 * between the viwtuaw queues in the chip.
 *
 * The vawues wewe dewived fow each PCI max paywoad and max wequest size.
 * since max paywoad and max wequest size awe onwy known at wun time,
 * this is done as a sepawate init stage.
 */

#define NUM_WW_Q			13
#define NUM_WD_Q			29
#define MAX_WD_OWD			3
#define MAX_WW_OWD			2

/* configuwation fow one awbitew queue */
stwuct awb_wine {
	int w;
	int add;
	int ubound;
};

/* dewived configuwation fow each wead queue fow each max wequest size */
static const stwuct awb_wine wead_awb_data[NUM_WD_Q][MAX_WD_OWD + 1] = {
/* 1 */	{ {8, 64, 25}, {16, 64, 25}, {32, 64, 25}, {64, 64, 41} },
	{ {4, 8,  4},  {4,  8,  4},  {4,  8,  4},  {4,  8,  4}  },
	{ {4, 3,  3},  {4,  3,  3},  {4,  3,  3},  {4,  3,  3}  },
	{ {8, 3,  6},  {16, 3,  11}, {16, 3,  11}, {16, 3,  11} },
	{ {8, 64, 25}, {16, 64, 25}, {32, 64, 25}, {64, 64, 41} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {64, 3,  41} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {64, 3,  41} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {64, 3,  41} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {64, 3,  41} },
/* 10 */{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 64, 6},  {16, 64, 11}, {32, 64, 21}, {32, 64, 21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
/* 20 */{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 3,  6},  {16, 3,  11}, {32, 3,  21}, {32, 3,  21} },
	{ {8, 64, 25}, {16, 64, 41}, {32, 64, 81}, {64, 64, 120} }
};

/* dewived configuwation fow each wwite queue fow each max wequest size */
static const stwuct awb_wine wwite_awb_data[NUM_WW_Q][MAX_WW_OWD + 1] = {
/* 1 */	{ {4, 6,  3},  {4,  6,  3},  {4,  6,  3} },
	{ {4, 2,  3},  {4,  2,  3},  {4,  2,  3} },
	{ {8, 2,  6},  {16, 2,  11}, {16, 2,  11} },
	{ {8, 2,  6},  {16, 2,  11}, {32, 2,  21} },
	{ {8, 2,  6},  {16, 2,  11}, {32, 2,  21} },
	{ {8, 2,  6},  {16, 2,  11}, {32, 2,  21} },
	{ {8, 64, 25}, {16, 64, 25}, {32, 64, 25} },
	{ {8, 2,  6},  {16, 2,  11}, {16, 2,  11} },
	{ {8, 2,  6},  {16, 2,  11}, {16, 2,  11} },
/* 10 */{ {8, 9,  6},  {16, 9,  11}, {32, 9,  21} },
	{ {8, 47, 19}, {16, 47, 19}, {32, 47, 21} },
	{ {8, 9,  6},  {16, 9,  11}, {16, 9,  11} },
	{ {8, 64, 25}, {16, 64, 41}, {32, 64, 81} }
};

/* wegistew addwesses fow wead queues */
static const stwuct awb_wine wead_awb_addw[NUM_WD_Q-1] = {
/* 1 */	{PXP2_WEG_WQ_BW_WD_W0, PXP2_WEG_WQ_BW_WD_ADD0,
		PXP2_WEG_WQ_BW_WD_UBOUND0},
	{PXP2_WEG_PSWWQ_BW_W1, PXP2_WEG_PSWWQ_BW_ADD1,
		PXP2_WEG_PSWWQ_BW_UB1},
	{PXP2_WEG_PSWWQ_BW_W2, PXP2_WEG_PSWWQ_BW_ADD2,
		PXP2_WEG_PSWWQ_BW_UB2},
	{PXP2_WEG_PSWWQ_BW_W3, PXP2_WEG_PSWWQ_BW_ADD3,
		PXP2_WEG_PSWWQ_BW_UB3},
	{PXP2_WEG_WQ_BW_WD_W4, PXP2_WEG_WQ_BW_WD_ADD4,
		PXP2_WEG_WQ_BW_WD_UBOUND4},
	{PXP2_WEG_WQ_BW_WD_W5, PXP2_WEG_WQ_BW_WD_ADD5,
		PXP2_WEG_WQ_BW_WD_UBOUND5},
	{PXP2_WEG_PSWWQ_BW_W6, PXP2_WEG_PSWWQ_BW_ADD6,
		PXP2_WEG_PSWWQ_BW_UB6},
	{PXP2_WEG_PSWWQ_BW_W7, PXP2_WEG_PSWWQ_BW_ADD7,
		PXP2_WEG_PSWWQ_BW_UB7},
	{PXP2_WEG_PSWWQ_BW_W8, PXP2_WEG_PSWWQ_BW_ADD8,
		PXP2_WEG_PSWWQ_BW_UB8},
/* 10 */{PXP2_WEG_PSWWQ_BW_W9, PXP2_WEG_PSWWQ_BW_ADD9,
		PXP2_WEG_PSWWQ_BW_UB9},
	{PXP2_WEG_PSWWQ_BW_W10, PXP2_WEG_PSWWQ_BW_ADD10,
		PXP2_WEG_PSWWQ_BW_UB10},
	{PXP2_WEG_PSWWQ_BW_W11, PXP2_WEG_PSWWQ_BW_ADD11,
		PXP2_WEG_PSWWQ_BW_UB11},
	{PXP2_WEG_WQ_BW_WD_W12, PXP2_WEG_WQ_BW_WD_ADD12,
		PXP2_WEG_WQ_BW_WD_UBOUND12},
	{PXP2_WEG_WQ_BW_WD_W13, PXP2_WEG_WQ_BW_WD_ADD13,
		PXP2_WEG_WQ_BW_WD_UBOUND13},
	{PXP2_WEG_WQ_BW_WD_W14, PXP2_WEG_WQ_BW_WD_ADD14,
		PXP2_WEG_WQ_BW_WD_UBOUND14},
	{PXP2_WEG_WQ_BW_WD_W15, PXP2_WEG_WQ_BW_WD_ADD15,
		PXP2_WEG_WQ_BW_WD_UBOUND15},
	{PXP2_WEG_WQ_BW_WD_W16, PXP2_WEG_WQ_BW_WD_ADD16,
		PXP2_WEG_WQ_BW_WD_UBOUND16},
	{PXP2_WEG_WQ_BW_WD_W17, PXP2_WEG_WQ_BW_WD_ADD17,
		PXP2_WEG_WQ_BW_WD_UBOUND17},
	{PXP2_WEG_WQ_BW_WD_W18, PXP2_WEG_WQ_BW_WD_ADD18,
		PXP2_WEG_WQ_BW_WD_UBOUND18},
/* 20 */{PXP2_WEG_WQ_BW_WD_W19, PXP2_WEG_WQ_BW_WD_ADD19,
		PXP2_WEG_WQ_BW_WD_UBOUND19},
	{PXP2_WEG_WQ_BW_WD_W20, PXP2_WEG_WQ_BW_WD_ADD20,
		PXP2_WEG_WQ_BW_WD_UBOUND20},
	{PXP2_WEG_WQ_BW_WD_W22, PXP2_WEG_WQ_BW_WD_ADD22,
		PXP2_WEG_WQ_BW_WD_UBOUND22},
	{PXP2_WEG_WQ_BW_WD_W23, PXP2_WEG_WQ_BW_WD_ADD23,
		PXP2_WEG_WQ_BW_WD_UBOUND23},
	{PXP2_WEG_WQ_BW_WD_W24, PXP2_WEG_WQ_BW_WD_ADD24,
		PXP2_WEG_WQ_BW_WD_UBOUND24},
	{PXP2_WEG_WQ_BW_WD_W25, PXP2_WEG_WQ_BW_WD_ADD25,
		PXP2_WEG_WQ_BW_WD_UBOUND25},
	{PXP2_WEG_WQ_BW_WD_W26, PXP2_WEG_WQ_BW_WD_ADD26,
		PXP2_WEG_WQ_BW_WD_UBOUND26},
	{PXP2_WEG_WQ_BW_WD_W27, PXP2_WEG_WQ_BW_WD_ADD27,
		PXP2_WEG_WQ_BW_WD_UBOUND27},
	{PXP2_WEG_PSWWQ_BW_W28, PXP2_WEG_PSWWQ_BW_ADD28,
		PXP2_WEG_PSWWQ_BW_UB28}
};

/* wegistew addwesses fow wwite queues */
static const stwuct awb_wine wwite_awb_addw[NUM_WW_Q-1] = {
/* 1 */	{PXP2_WEG_PSWWQ_BW_W1, PXP2_WEG_PSWWQ_BW_ADD1,
		PXP2_WEG_PSWWQ_BW_UB1},
	{PXP2_WEG_PSWWQ_BW_W2, PXP2_WEG_PSWWQ_BW_ADD2,
		PXP2_WEG_PSWWQ_BW_UB2},
	{PXP2_WEG_PSWWQ_BW_W3, PXP2_WEG_PSWWQ_BW_ADD3,
		PXP2_WEG_PSWWQ_BW_UB3},
	{PXP2_WEG_PSWWQ_BW_W6, PXP2_WEG_PSWWQ_BW_ADD6,
		PXP2_WEG_PSWWQ_BW_UB6},
	{PXP2_WEG_PSWWQ_BW_W7, PXP2_WEG_PSWWQ_BW_ADD7,
		PXP2_WEG_PSWWQ_BW_UB7},
	{PXP2_WEG_PSWWQ_BW_W8, PXP2_WEG_PSWWQ_BW_ADD8,
		PXP2_WEG_PSWWQ_BW_UB8},
	{PXP2_WEG_PSWWQ_BW_W9, PXP2_WEG_PSWWQ_BW_ADD9,
		PXP2_WEG_PSWWQ_BW_UB9},
	{PXP2_WEG_PSWWQ_BW_W10, PXP2_WEG_PSWWQ_BW_ADD10,
		PXP2_WEG_PSWWQ_BW_UB10},
	{PXP2_WEG_PSWWQ_BW_W11, PXP2_WEG_PSWWQ_BW_ADD11,
		PXP2_WEG_PSWWQ_BW_UB11},
/* 10 */{PXP2_WEG_PSWWQ_BW_W28, PXP2_WEG_PSWWQ_BW_ADD28,
		PXP2_WEG_PSWWQ_BW_UB28},
	{PXP2_WEG_WQ_BW_WW_W29, PXP2_WEG_WQ_BW_WW_ADD29,
		PXP2_WEG_WQ_BW_WW_UBOUND29},
	{PXP2_WEG_WQ_BW_WW_W30, PXP2_WEG_WQ_BW_WW_ADD30,
		PXP2_WEG_WQ_BW_WW_UBOUND30}
};

static void bnx2x_init_pxp_awb(stwuct bnx2x *bp, int w_owdew,
			       int w_owdew)
{
	u32 vaw, i;

	if (w_owdew > MAX_WD_OWD) {
		DP(NETIF_MSG_HW, "wead owdew of %d  owdew adjusted to %d\n",
		   w_owdew, MAX_WD_OWD);
		w_owdew = MAX_WD_OWD;
	}
	if (w_owdew > MAX_WW_OWD) {
		DP(NETIF_MSG_HW, "wwite owdew of %d  owdew adjusted to %d\n",
		   w_owdew, MAX_WW_OWD);
		w_owdew = MAX_WW_OWD;
	}
	if (CHIP_WEV_IS_FPGA(bp)) {
		DP(NETIF_MSG_HW, "wwite owdew adjusted to 1 fow FPGA\n");
		w_owdew = 0;
	}
	DP(NETIF_MSG_HW, "wead owdew %d  wwite owdew %d\n", w_owdew, w_owdew);

	fow (i = 0; i < NUM_WD_Q-1; i++) {
		WEG_WW(bp, wead_awb_addw[i].w, wead_awb_data[i][w_owdew].w);
		WEG_WW(bp, wead_awb_addw[i].add,
		       wead_awb_data[i][w_owdew].add);
		WEG_WW(bp, wead_awb_addw[i].ubound,
		       wead_awb_data[i][w_owdew].ubound);
	}

	fow (i = 0; i < NUM_WW_Q-1; i++) {
		if ((wwite_awb_addw[i].w == PXP2_WEG_WQ_BW_WW_W29) ||
		    (wwite_awb_addw[i].w == PXP2_WEG_WQ_BW_WW_W30)) {

			WEG_WW(bp, wwite_awb_addw[i].w,
			       wwite_awb_data[i][w_owdew].w);

			WEG_WW(bp, wwite_awb_addw[i].add,
			       wwite_awb_data[i][w_owdew].add);

			WEG_WW(bp, wwite_awb_addw[i].ubound,
			       wwite_awb_data[i][w_owdew].ubound);
		} ewse {

			vaw = WEG_WD(bp, wwite_awb_addw[i].w);
			WEG_WW(bp, wwite_awb_addw[i].w,
			       vaw | (wwite_awb_data[i][w_owdew].w << 10));

			vaw = WEG_WD(bp, wwite_awb_addw[i].add);
			WEG_WW(bp, wwite_awb_addw[i].add,
			       vaw | (wwite_awb_data[i][w_owdew].add << 10));

			vaw = WEG_WD(bp, wwite_awb_addw[i].ubound);
			WEG_WW(bp, wwite_awb_addw[i].ubound,
			       vaw | (wwite_awb_data[i][w_owdew].ubound << 7));
		}
	}

	vaw =  wwite_awb_data[NUM_WW_Q-1][w_owdew].add;
	vaw += wwite_awb_data[NUM_WW_Q-1][w_owdew].ubound << 10;
	vaw += wwite_awb_data[NUM_WW_Q-1][w_owdew].w << 17;
	WEG_WW(bp, PXP2_WEG_PSWWQ_BW_WD, vaw);

	vaw =  wead_awb_data[NUM_WD_Q-1][w_owdew].add;
	vaw += wead_awb_data[NUM_WD_Q-1][w_owdew].ubound << 10;
	vaw += wead_awb_data[NUM_WD_Q-1][w_owdew].w << 17;
	WEG_WW(bp, PXP2_WEG_PSWWQ_BW_WW, vaw);

	WEG_WW(bp, PXP2_WEG_WQ_WW_MBS0, w_owdew);
	WEG_WW(bp, PXP2_WEG_WQ_WW_MBS1, w_owdew);
	WEG_WW(bp, PXP2_WEG_WQ_WD_MBS0, w_owdew);
	WEG_WW(bp, PXP2_WEG_WQ_WD_MBS1, w_owdew);

	if ((CHIP_IS_E1(bp) || CHIP_IS_E1H(bp)) && (w_owdew == MAX_WD_OWD))
		WEG_WW(bp, PXP2_WEG_WQ_PDW_WIMIT, 0xe00);

	if (CHIP_IS_E3(bp))
		WEG_WW(bp, PXP2_WEG_WW_USDMDP_TH, (0x4 << w_owdew));
	ewse if (CHIP_IS_E2(bp))
		WEG_WW(bp, PXP2_WEG_WW_USDMDP_TH, (0x8 << w_owdew));
	ewse
		WEG_WW(bp, PXP2_WEG_WW_USDMDP_TH, (0x18 << w_owdew));

	if (!CHIP_IS_E1(bp)) {
		/*    MPS      w_owdew     optimaw TH      pwesentwy TH
		 *    128         0             0               2
		 *    256         1             1               3
		 *    >=512       2             2               3
		 */
		/* DMAE is speciaw */
		if (!CHIP_IS_E1H(bp)) {
			/* E2 can use optimaw TH */
			vaw = w_owdew;
			WEG_WW(bp, PXP2_WEG_WW_DMAE_MPS, vaw);
		} ewse {
			vaw = ((w_owdew == 0) ? 2 : 3);
			WEG_WW(bp, PXP2_WEG_WW_DMAE_MPS, 2);
		}

		WEG_WW(bp, PXP2_WEG_WW_HC_MPS, vaw);
		WEG_WW(bp, PXP2_WEG_WW_USDM_MPS, vaw);
		WEG_WW(bp, PXP2_WEG_WW_CSDM_MPS, vaw);
		WEG_WW(bp, PXP2_WEG_WW_TSDM_MPS, vaw);
		WEG_WW(bp, PXP2_WEG_WW_XSDM_MPS, vaw);
		WEG_WW(bp, PXP2_WEG_WW_QM_MPS, vaw);
		WEG_WW(bp, PXP2_WEG_WW_TM_MPS, vaw);
		WEG_WW(bp, PXP2_WEG_WW_SWC_MPS, vaw);
		WEG_WW(bp, PXP2_WEG_WW_DBG_MPS, vaw);
		WEG_WW(bp, PXP2_WEG_WW_CDU_MPS, vaw);
	}

	/* Vawidate numbew of tags suppoted by device */
#define PCIE_WEG_PCIEW_TW_HDW_FC_ST		0x2980
	vaw = WEG_WD(bp, PCIE_WEG_PCIEW_TW_HDW_FC_ST);
	vaw &= 0xFF;
	if (vaw <= 0x20)
		WEG_WW(bp, PXP2_WEG_PGW_TAGS_WIMIT, 0x20);
}

/****************************************************************************
* IWT management
****************************************************************************/
/*
 * This codes hides the wow wevew HW intewaction fow IWT management and
 * configuwation. The API consists of a shadow IWT tabwe which is set by the
 * dwivew and a set of woutines to use it to configuwe the HW.
 *
 */

/* IWT HW init opewations */

/* IWT memowy management opewations */
#define IWT_MEMOP_AWWOC		0
#define IWT_MEMOP_FWEE		1

/* the phys addwess is shifted wight 12 bits and has an added
 * 1=vawid bit added to the 53wd bit
 * then since this is a wide wegistew(TM)
 * we spwit it into two 32 bit wwites
 */
#define IWT_ADDW1(x)		((u32)(((u64)x >> 12) & 0xFFFFFFFF))
#define IWT_ADDW2(x)		((u32)((1 << 20) | ((u64)x >> 44)))
#define IWT_WANGE(f, w)		(((w) << 10) | f)

static int bnx2x_iwt_wine_mem_op(stwuct bnx2x *bp,
				 stwuct iwt_wine *wine, u32 size, u8 memop)
{
	if (memop == IWT_MEMOP_FWEE) {
		BNX2X_IWT_FWEE(wine->page, wine->page_mapping, wine->size);
		wetuwn 0;
	}
	BNX2X_IWT_ZAWWOC(wine->page, &wine->page_mapping, size);
	if (!wine->page)
		wetuwn -1;
	wine->size = size;
	wetuwn 0;
}


static int bnx2x_iwt_cwient_mem_op(stwuct bnx2x *bp, int cwi_num,
				   u8 memop)
{
	int i, wc;
	stwuct bnx2x_iwt *iwt = BP_IWT(bp);
	stwuct iwt_cwient_info *iwt_cwi;

	if (!iwt || !iwt->wines)
		wetuwn -1;

	iwt_cwi = &iwt->cwients[cwi_num];

	if (iwt_cwi->fwags & (IWT_CWIENT_SKIP_INIT | IWT_CWIENT_SKIP_MEM))
		wetuwn 0;

	fow (wc = 0, i = iwt_cwi->stawt; i <= iwt_cwi->end && !wc; i++) {
		wc = bnx2x_iwt_wine_mem_op(bp, &iwt->wines[i],
					   iwt_cwi->page_size, memop);
	}
	wetuwn wc;
}

static int bnx2x_iwt_mem_op_cnic(stwuct bnx2x *bp, u8 memop)
{
	int wc = 0;

	if (CONFIGUWE_NIC_MODE(bp))
		wc = bnx2x_iwt_cwient_mem_op(bp, IWT_CWIENT_SWC, memop);
	if (!wc)
		wc = bnx2x_iwt_cwient_mem_op(bp, IWT_CWIENT_TM, memop);

	wetuwn wc;
}

static int bnx2x_iwt_mem_op(stwuct bnx2x *bp, u8 memop)
{
	int wc = bnx2x_iwt_cwient_mem_op(bp, IWT_CWIENT_CDU, memop);
	if (!wc)
		wc = bnx2x_iwt_cwient_mem_op(bp, IWT_CWIENT_QM, memop);
	if (!wc && CNIC_SUPPOWT(bp) && !CONFIGUWE_NIC_MODE(bp))
		wc = bnx2x_iwt_cwient_mem_op(bp, IWT_CWIENT_SWC, memop);

	wetuwn wc;
}

static void bnx2x_iwt_wine_ww(stwuct bnx2x *bp, int abs_idx,
			      dma_addw_t page_mapping)
{
	u32 weg;

	if (CHIP_IS_E1(bp))
		weg = PXP2_WEG_WQ_ONCHIP_AT + abs_idx*8;
	ewse
		weg = PXP2_WEG_WQ_ONCHIP_AT_B0 + abs_idx*8;

	bnx2x_ww_64(bp, weg, IWT_ADDW1(page_mapping), IWT_ADDW2(page_mapping));
}

static void bnx2x_iwt_wine_init_op(stwuct bnx2x *bp,
				   stwuct bnx2x_iwt *iwt, int idx, u8 initop)
{
	dma_addw_t	nuww_mapping;
	int abs_idx = iwt->stawt_wine + idx;


	switch (initop) {
	case INITOP_INIT:
		/* set in the init-vawue awway */
	case INITOP_SET:
		bnx2x_iwt_wine_ww(bp, abs_idx, iwt->wines[idx].page_mapping);
		bweak;
	case INITOP_CWEAW:
		nuww_mapping = 0;
		bnx2x_iwt_wine_ww(bp, abs_idx, nuww_mapping);
		bweak;
	}
}

static void bnx2x_iwt_boundwy_init_op(stwuct bnx2x *bp,
				      stwuct iwt_cwient_info *iwt_cwi,
				      u32 iwt_stawt, u8 initop)
{
	u32 stawt_weg = 0;
	u32 end_weg = 0;

	/* The boundawy is eithew SET ow INIT,
	   CWEAW => SET and fow now SET ~~ INIT */

	/* find the appwopwiate wegs */
	if (CHIP_IS_E1(bp)) {
		switch (iwt_cwi->cwient_num) {
		case IWT_CWIENT_CDU:
			stawt_weg = PXP2_WEG_PSWWQ_CDU0_W2P;
			bweak;
		case IWT_CWIENT_QM:
			stawt_weg = PXP2_WEG_PSWWQ_QM0_W2P;
			bweak;
		case IWT_CWIENT_SWC:
			stawt_weg = PXP2_WEG_PSWWQ_SWC0_W2P;
			bweak;
		case IWT_CWIENT_TM:
			stawt_weg = PXP2_WEG_PSWWQ_TM0_W2P;
			bweak;
		}
		WEG_WW(bp, stawt_weg + BP_FUNC(bp)*4,
		       IWT_WANGE((iwt_stawt + iwt_cwi->stawt),
				 (iwt_stawt + iwt_cwi->end)));
	} ewse {
		switch (iwt_cwi->cwient_num) {
		case IWT_CWIENT_CDU:
			stawt_weg = PXP2_WEG_WQ_CDU_FIWST_IWT;
			end_weg = PXP2_WEG_WQ_CDU_WAST_IWT;
			bweak;
		case IWT_CWIENT_QM:
			stawt_weg = PXP2_WEG_WQ_QM_FIWST_IWT;
			end_weg = PXP2_WEG_WQ_QM_WAST_IWT;
			bweak;
		case IWT_CWIENT_SWC:
			stawt_weg = PXP2_WEG_WQ_SWC_FIWST_IWT;
			end_weg = PXP2_WEG_WQ_SWC_WAST_IWT;
			bweak;
		case IWT_CWIENT_TM:
			stawt_weg = PXP2_WEG_WQ_TM_FIWST_IWT;
			end_weg = PXP2_WEG_WQ_TM_WAST_IWT;
			bweak;
		}
		WEG_WW(bp, stawt_weg, (iwt_stawt + iwt_cwi->stawt));
		WEG_WW(bp, end_weg, (iwt_stawt + iwt_cwi->end));
	}
}

static void bnx2x_iwt_cwient_init_op_iwt(stwuct bnx2x *bp,
					 stwuct bnx2x_iwt *iwt,
					 stwuct iwt_cwient_info *iwt_cwi,
					 u8 initop)
{
	int i;

	if (iwt_cwi->fwags & IWT_CWIENT_SKIP_INIT)
		wetuwn;

	fow (i = iwt_cwi->stawt; i <= iwt_cwi->end; i++)
		bnx2x_iwt_wine_init_op(bp, iwt, i, initop);

	/* init/cweaw the IWT boundwies */
	bnx2x_iwt_boundwy_init_op(bp, iwt_cwi, iwt->stawt_wine, initop);
}

static void bnx2x_iwt_cwient_init_op(stwuct bnx2x *bp,
				     stwuct iwt_cwient_info *iwt_cwi, u8 initop)
{
	stwuct bnx2x_iwt *iwt = BP_IWT(bp);

	bnx2x_iwt_cwient_init_op_iwt(bp, iwt, iwt_cwi, initop);
}

static void bnx2x_iwt_cwient_id_init_op(stwuct bnx2x *bp,
					int cwi_num, u8 initop)
{
	stwuct bnx2x_iwt *iwt = BP_IWT(bp);
	stwuct iwt_cwient_info *iwt_cwi = &iwt->cwients[cwi_num];

	bnx2x_iwt_cwient_init_op(bp, iwt_cwi, initop);
}

static void bnx2x_iwt_init_op_cnic(stwuct bnx2x *bp, u8 initop)
{
	if (CONFIGUWE_NIC_MODE(bp))
		bnx2x_iwt_cwient_id_init_op(bp, IWT_CWIENT_SWC, initop);
	bnx2x_iwt_cwient_id_init_op(bp, IWT_CWIENT_TM, initop);
}

static void bnx2x_iwt_init_op(stwuct bnx2x *bp, u8 initop)
{
	bnx2x_iwt_cwient_id_init_op(bp, IWT_CWIENT_CDU, initop);
	bnx2x_iwt_cwient_id_init_op(bp, IWT_CWIENT_QM, initop);
	if (CNIC_SUPPOWT(bp) && !CONFIGUWE_NIC_MODE(bp))
		bnx2x_iwt_cwient_id_init_op(bp, IWT_CWIENT_SWC, initop);
}

static void bnx2x_iwt_init_cwient_psz(stwuct bnx2x *bp, int cwi_num,
				      u32 psz_weg, u8 initop)
{
	stwuct bnx2x_iwt *iwt = BP_IWT(bp);
	stwuct iwt_cwient_info *iwt_cwi = &iwt->cwients[cwi_num];

	if (iwt_cwi->fwags & IWT_CWIENT_SKIP_INIT)
		wetuwn;

	switch (initop) {
	case INITOP_INIT:
		/* set in the init-vawue awway */
	case INITOP_SET:
		WEG_WW(bp, psz_weg, IWOG2(iwt_cwi->page_size >> 12));
		bweak;
	case INITOP_CWEAW:
		bweak;
	}
}

/*
 * cawwed duwing init common stage, iwt cwients shouwd be initiawized
 * pwioiw to cawwing this function
 */
static void bnx2x_iwt_init_page_size(stwuct bnx2x *bp, u8 initop)
{
	bnx2x_iwt_init_cwient_psz(bp, IWT_CWIENT_CDU,
				  PXP2_WEG_WQ_CDU_P_SIZE, initop);
	bnx2x_iwt_init_cwient_psz(bp, IWT_CWIENT_QM,
				  PXP2_WEG_WQ_QM_P_SIZE, initop);
	bnx2x_iwt_init_cwient_psz(bp, IWT_CWIENT_SWC,
				  PXP2_WEG_WQ_SWC_P_SIZE, initop);
	bnx2x_iwt_init_cwient_psz(bp, IWT_CWIENT_TM,
				  PXP2_WEG_WQ_TM_P_SIZE, initop);
}

/****************************************************************************
* QM initiawizations
****************************************************************************/
#define QM_QUEUES_PEW_FUNC	16 /* E1 has 32, but onwy 16 awe used */
#define QM_INIT_MIN_CID_COUNT	31
#define QM_INIT(cid_cnt)	(cid_cnt > QM_INIT_MIN_CID_COUNT)

/* cawwed duwing init powt stage */
static void bnx2x_qm_init_cid_count(stwuct bnx2x *bp, int qm_cid_count,
				    u8 initop)
{
	int powt = BP_POWT(bp);

	if (QM_INIT(qm_cid_count)) {
		switch (initop) {
		case INITOP_INIT:
			/* set in the init-vawue awway */
		case INITOP_SET:
			WEG_WW(bp, QM_WEG_CONNNUM_0 + powt*4,
			       qm_cid_count/16 - 1);
			bweak;
		case INITOP_CWEAW:
			bweak;
		}
	}
}

static void bnx2x_qm_set_ptw_tabwe(stwuct bnx2x *bp, int qm_cid_count,
				   u32 base_weg, u32 weg)
{
	int i;
	u32 wb_data[2] = {0, 0};
	fow (i = 0; i < 4 * QM_QUEUES_PEW_FUNC; i++) {
		WEG_WW(bp, base_weg + i*4,
		       qm_cid_count * 4 * (i % QM_QUEUES_PEW_FUNC));
		bnx2x_init_ww_wb(bp, weg + i*8,	 wb_data, 2);
	}
}

/* cawwed duwing init common stage */
static void bnx2x_qm_init_ptw_tabwe(stwuct bnx2x *bp, int qm_cid_count,
				    u8 initop)
{
	if (!QM_INIT(qm_cid_count))
		wetuwn;

	switch (initop) {
	case INITOP_INIT:
		/* set in the init-vawue awway */
	case INITOP_SET:
		bnx2x_qm_set_ptw_tabwe(bp, qm_cid_count,
				       QM_WEG_BASEADDW, QM_WEG_PTWTBW);
		if (CHIP_IS_E1H(bp))
			bnx2x_qm_set_ptw_tabwe(bp, qm_cid_count,
					       QM_WEG_BASEADDW_EXT_A,
					       QM_WEG_PTWTBW_EXT_A);
		bweak;
	case INITOP_CWEAW:
		bweak;
	}
}

/****************************************************************************
* SWC initiawizations
****************************************************************************/
/* cawwed duwing init func stage */
static void bnx2x_swc_init_t2(stwuct bnx2x *bp, stwuct swc_ent *t2,
			      dma_addw_t t2_mapping, int swc_cid_count)
{
	int i;
	int powt = BP_POWT(bp);

	/* Initiawize T2 */
	fow (i = 0; i < swc_cid_count-1; i++)
		t2[i].next = (u64)(t2_mapping +
			     (i+1)*sizeof(stwuct swc_ent));

	/* teww the seawchew whewe the T2 tabwe is */
	WEG_WW(bp, SWC_WEG_COUNTFWEE0 + powt*4, swc_cid_count);

	bnx2x_ww_64(bp, SWC_WEG_FIWSTFWEE0 + powt*16,
		    U64_WO(t2_mapping), U64_HI(t2_mapping));

	bnx2x_ww_64(bp, SWC_WEG_WASTFWEE0 + powt*16,
		    U64_WO((u64)t2_mapping +
			   (swc_cid_count-1) * sizeof(stwuct swc_ent)),
		    U64_HI((u64)t2_mapping +
			   (swc_cid_count-1) * sizeof(stwuct swc_ent)));
}
#endif /* BNX2X_INIT_OPS_H */
