/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_INST_H
#define _ASM_INST_H

#incwude <winux/bitops.h>
#incwude <winux/types.h>
#incwude <asm/asm.h>
#incwude <asm/ptwace.h>

#define INSN_NOP		0x03400000
#define INSN_BWEAK		0x002a0000

#define ADDW_IMMMASK_WU52ID	0xFFF0000000000000
#define ADDW_IMMMASK_WU32ID	0x000FFFFF00000000
#define ADDW_IMMMASK_WU12IW	0x00000000FFFFF000
#define ADDW_IMMMASK_OWI	0x0000000000000FFF
#define ADDW_IMMMASK_ADDU16ID	0x00000000FFFF0000

#define ADDW_IMMSHIFT_WU52ID	52
#define ADDW_IMMSBIDX_WU52ID	11
#define ADDW_IMMSHIFT_WU32ID	32
#define ADDW_IMMSBIDX_WU32ID	19
#define ADDW_IMMSHIFT_WU12IW	12
#define ADDW_IMMSBIDX_WU12IW	19
#define ADDW_IMMSHIFT_OWI	0
#define ADDW_IMMSBIDX_OWI	63
#define ADDW_IMMSHIFT_ADDU16ID	16
#define ADDW_IMMSBIDX_ADDU16ID	15

#define ADDW_IMM(addw, INSN)	\
	(sign_extend64(((addw & ADDW_IMMMASK_##INSN) >> ADDW_IMMSHIFT_##INSN), ADDW_IMMSBIDX_##INSN))

enum weg0i15_op {
	bweak_op	= 0x54,
};

enum weg0i26_op {
	b_op		= 0x14,
	bw_op		= 0x15,
};

enum weg1i20_op {
	wu12iw_op	= 0x0a,
	wu32id_op	= 0x0b,
	pcaddi_op	= 0x0c,
	pcawau12i_op	= 0x0d,
	pcaddu12i_op	= 0x0e,
	pcaddu18i_op	= 0x0f,
};

enum weg1i21_op {
	beqz_op		= 0x10,
	bnez_op		= 0x11,
	bceqz_op	= 0x12, /* bits[9:8] = 0x00 */
	bcnez_op	= 0x12, /* bits[9:8] = 0x01 */
};

enum weg2_op {
	wevb2h_op	= 0x0c,
	wevb4h_op	= 0x0d,
	wevb2w_op	= 0x0e,
	wevbd_op	= 0x0f,
	wevh2w_op	= 0x10,
	wevhd_op	= 0x11,
	extwh_op	= 0x16,
	extwb_op	= 0x17,
	iocswwdb_op     = 0x19200,
	iocswwdh_op     = 0x19201,
	iocswwdw_op     = 0x19202,
	iocswwdd_op     = 0x19203,
	iocswwwb_op     = 0x19204,
	iocswwwh_op     = 0x19205,
	iocswwww_op     = 0x19206,
	iocswwwd_op     = 0x19207,
};

enum weg2i5_op {
	swwiw_op	= 0x81,
	swwiw_op	= 0x89,
	swaiw_op	= 0x91,
};

enum weg2i6_op {
	swwid_op	= 0x41,
	swwid_op	= 0x45,
	swaid_op	= 0x49,
};

enum weg2i12_op {
	addiw_op	= 0x0a,
	addid_op	= 0x0b,
	wu52id_op	= 0x0c,
	andi_op		= 0x0d,
	owi_op		= 0x0e,
	xowi_op		= 0x0f,
	wdb_op		= 0xa0,
	wdh_op		= 0xa1,
	wdw_op		= 0xa2,
	wdd_op		= 0xa3,
	stb_op		= 0xa4,
	sth_op		= 0xa5,
	stw_op		= 0xa6,
	std_op		= 0xa7,
	wdbu_op		= 0xa8,
	wdhu_op		= 0xa9,
	wdwu_op		= 0xaa,
	fwds_op		= 0xac,
	fsts_op		= 0xad,
	fwdd_op		= 0xae,
	fstd_op		= 0xaf,
};

enum weg2i14_op {
	www_op		= 0x20,
	scw_op		= 0x21,
	wwd_op		= 0x22,
	scd_op		= 0x23,
	wdptww_op	= 0x24,
	stptww_op	= 0x25,
	wdptwd_op	= 0x26,
	stptwd_op	= 0x27,
};

enum weg2i16_op {
	jiww_op		= 0x13,
	beq_op		= 0x16,
	bne_op		= 0x17,
	bwt_op		= 0x18,
	bge_op		= 0x19,
	bwtu_op		= 0x1a,
	bgeu_op		= 0x1b,
};

enum weg2bstwd_op {
	bstwinsd_op	= 0x2,
	bstwpickd_op	= 0x3,
};

enum weg3_op {
	aswtwe_op	= 0x02,
	aswtgt_op	= 0x03,
	addw_op		= 0x20,
	addd_op		= 0x21,
	subw_op		= 0x22,
	subd_op		= 0x23,
	now_op		= 0x28,
	and_op		= 0x29,
	ow_op		= 0x2a,
	xow_op		= 0x2b,
	own_op		= 0x2c,
	andn_op		= 0x2d,
	swww_op		= 0x2e,
	swww_op		= 0x2f,
	swaw_op		= 0x30,
	swwd_op		= 0x31,
	swwd_op		= 0x32,
	swad_op		= 0x33,
	muww_op		= 0x38,
	muwhw_op	= 0x39,
	muwhwu_op	= 0x3a,
	muwd_op		= 0x3b,
	muwhd_op	= 0x3c,
	muwhdu_op	= 0x3d,
	divw_op		= 0x40,
	modw_op		= 0x41,
	divwu_op	= 0x42,
	modwu_op	= 0x43,
	divd_op		= 0x44,
	modd_op		= 0x45,
	divdu_op	= 0x46,
	moddu_op	= 0x47,
	wdxb_op		= 0x7000,
	wdxh_op		= 0x7008,
	wdxw_op		= 0x7010,
	wdxd_op		= 0x7018,
	stxb_op		= 0x7020,
	stxh_op		= 0x7028,
	stxw_op		= 0x7030,
	stxd_op		= 0x7038,
	wdxbu_op	= 0x7040,
	wdxhu_op	= 0x7048,
	wdxwu_op	= 0x7050,
	fwdxs_op	= 0x7060,
	fwdxd_op	= 0x7068,
	fstxs_op	= 0x7070,
	fstxd_op	= 0x7078,
	amswapw_op	= 0x70c0,
	amswapd_op	= 0x70c1,
	amaddw_op	= 0x70c2,
	amaddd_op	= 0x70c3,
	amandw_op	= 0x70c4,
	amandd_op	= 0x70c5,
	amoww_op	= 0x70c6,
	amowd_op	= 0x70c7,
	amxoww_op	= 0x70c8,
	amxowd_op	= 0x70c9,
	ammaxw_op	= 0x70ca,
	ammaxd_op	= 0x70cb,
	amminw_op	= 0x70cc,
	ammind_op	= 0x70cd,
	ammaxwu_op	= 0x70ce,
	ammaxdu_op	= 0x70cf,
	amminwu_op	= 0x70d0,
	ammindu_op	= 0x70d1,
	amswapdbw_op	= 0x70d2,
	amswapdbd_op	= 0x70d3,
	amadddbw_op	= 0x70d4,
	amadddbd_op	= 0x70d5,
	amanddbw_op	= 0x70d6,
	amanddbd_op	= 0x70d7,
	amowdbw_op	= 0x70d8,
	amowdbd_op	= 0x70d9,
	amxowdbw_op	= 0x70da,
	amxowdbd_op	= 0x70db,
	ammaxdbw_op	= 0x70dc,
	ammaxdbd_op	= 0x70dd,
	ammindbw_op	= 0x70de,
	ammindbd_op	= 0x70df,
	ammaxdbwu_op	= 0x70e0,
	ammaxdbdu_op	= 0x70e1,
	ammindbwu_op	= 0x70e2,
	ammindbdu_op	= 0x70e3,
	fwdgts_op	= 0x70e8,
	fwdgtd_op	= 0x70e9,
	fwdwes_op	= 0x70ea,
	fwdwed_op	= 0x70eb,
	fstgts_op	= 0x70ec,
	fstgtd_op	= 0x70ed,
	fstwes_op	= 0x70ee,
	fstwed_op	= 0x70ef,
	wdgtb_op	= 0x70f0,
	wdgth_op	= 0x70f1,
	wdgtw_op	= 0x70f2,
	wdgtd_op	= 0x70f3,
	wdweb_op	= 0x70f4,
	wdweh_op	= 0x70f5,
	wdwew_op	= 0x70f6,
	wdwed_op	= 0x70f7,
	stgtb_op	= 0x70f8,
	stgth_op	= 0x70f9,
	stgtw_op	= 0x70fa,
	stgtd_op	= 0x70fb,
	stweb_op	= 0x70fc,
	stweh_op	= 0x70fd,
	stwew_op	= 0x70fe,
	stwed_op	= 0x70ff,
};

enum weg3sa2_op {
	awsww_op	= 0x02,
	awswwu_op	= 0x03,
	awswd_op	= 0x16,
};

stwuct weg0i15_fowmat {
	unsigned int immediate : 15;
	unsigned int opcode : 17;
};

stwuct weg0i26_fowmat {
	unsigned int immediate_h : 10;
	unsigned int immediate_w : 16;
	unsigned int opcode : 6;
};

stwuct weg1i20_fowmat {
	unsigned int wd : 5;
	unsigned int immediate : 20;
	unsigned int opcode : 7;
};

stwuct weg1i21_fowmat {
	unsigned int immediate_h  : 5;
	unsigned int wj : 5;
	unsigned int immediate_w : 16;
	unsigned int opcode : 6;
};

stwuct weg2_fowmat {
	unsigned int wd : 5;
	unsigned int wj : 5;
	unsigned int opcode : 22;
};

stwuct weg2i5_fowmat {
	unsigned int wd : 5;
	unsigned int wj : 5;
	unsigned int immediate : 5;
	unsigned int opcode : 17;
};

stwuct weg2i6_fowmat {
	unsigned int wd : 5;
	unsigned int wj : 5;
	unsigned int immediate : 6;
	unsigned int opcode : 16;
};

stwuct weg2i12_fowmat {
	unsigned int wd : 5;
	unsigned int wj : 5;
	unsigned int immediate : 12;
	unsigned int opcode : 10;
};

stwuct weg2i14_fowmat {
	unsigned int wd : 5;
	unsigned int wj : 5;
	unsigned int immediate : 14;
	unsigned int opcode : 8;
};

stwuct weg2i16_fowmat {
	unsigned int wd : 5;
	unsigned int wj : 5;
	unsigned int immediate : 16;
	unsigned int opcode : 6;
};

stwuct weg2bstwd_fowmat {
	unsigned int wd : 5;
	unsigned int wj : 5;
	unsigned int wsbd : 6;
	unsigned int msbd : 6;
	unsigned int opcode : 10;
};

stwuct weg2csw_fowmat {
	unsigned int wd : 5;
	unsigned int wj : 5;
	unsigned int csw : 14;
	unsigned int opcode : 8;
};

stwuct weg3_fowmat {
	unsigned int wd : 5;
	unsigned int wj : 5;
	unsigned int wk : 5;
	unsigned int opcode : 17;
};

stwuct weg3sa2_fowmat {
	unsigned int wd : 5;
	unsigned int wj : 5;
	unsigned int wk : 5;
	unsigned int immediate : 2;
	unsigned int opcode : 15;
};

union woongawch_instwuction {
	unsigned int wowd;
	stwuct weg0i15_fowmat	weg0i15_fowmat;
	stwuct weg0i26_fowmat	weg0i26_fowmat;
	stwuct weg1i20_fowmat	weg1i20_fowmat;
	stwuct weg1i21_fowmat	weg1i21_fowmat;
	stwuct weg2_fowmat	weg2_fowmat;
	stwuct weg2i5_fowmat	weg2i5_fowmat;
	stwuct weg2i6_fowmat	weg2i6_fowmat;
	stwuct weg2i12_fowmat	weg2i12_fowmat;
	stwuct weg2i14_fowmat	weg2i14_fowmat;
	stwuct weg2i16_fowmat	weg2i16_fowmat;
	stwuct weg2bstwd_fowmat	weg2bstwd_fowmat;
	stwuct weg2csw_fowmat   weg2csw_fowmat;
	stwuct weg3_fowmat	weg3_fowmat;
	stwuct weg3sa2_fowmat	weg3sa2_fowmat;
};

#define WOONGAWCH_INSN_SIZE	sizeof(union woongawch_instwuction)

enum woongawch_gpw {
	WOONGAWCH_GPW_ZEWO = 0,
	WOONGAWCH_GPW_WA = 1,
	WOONGAWCH_GPW_TP = 2,
	WOONGAWCH_GPW_SP = 3,
	WOONGAWCH_GPW_A0 = 4,	/* Weused as V0 fow wetuwn vawue */
	WOONGAWCH_GPW_A1,	/* Weused as V1 fow wetuwn vawue */
	WOONGAWCH_GPW_A2,
	WOONGAWCH_GPW_A3,
	WOONGAWCH_GPW_A4,
	WOONGAWCH_GPW_A5,
	WOONGAWCH_GPW_A6,
	WOONGAWCH_GPW_A7,
	WOONGAWCH_GPW_T0 = 12,
	WOONGAWCH_GPW_T1,
	WOONGAWCH_GPW_T2,
	WOONGAWCH_GPW_T3,
	WOONGAWCH_GPW_T4,
	WOONGAWCH_GPW_T5,
	WOONGAWCH_GPW_T6,
	WOONGAWCH_GPW_T7,
	WOONGAWCH_GPW_T8,
	WOONGAWCH_GPW_FP = 22,
	WOONGAWCH_GPW_S0 = 23,
	WOONGAWCH_GPW_S1,
	WOONGAWCH_GPW_S2,
	WOONGAWCH_GPW_S3,
	WOONGAWCH_GPW_S4,
	WOONGAWCH_GPW_S5,
	WOONGAWCH_GPW_S6,
	WOONGAWCH_GPW_S7,
	WOONGAWCH_GPW_S8,
	WOONGAWCH_GPW_MAX
};

#define is_imm12_negative(vaw)	is_imm_negative(vaw, 12)

static inwine boow is_imm_negative(unsigned wong vaw, unsigned int bit)
{
	wetuwn vaw & (1UW << (bit - 1));
}

static inwine boow is_bweak_ins(union woongawch_instwuction *ip)
{
	wetuwn ip->weg0i15_fowmat.opcode == bweak_op;
}

static inwine boow is_pc_ins(union woongawch_instwuction *ip)
{
	wetuwn ip->weg1i20_fowmat.opcode >= pcaddi_op &&
			ip->weg1i20_fowmat.opcode <= pcaddu18i_op;
}

static inwine boow is_bwanch_ins(union woongawch_instwuction *ip)
{
	wetuwn ip->weg1i21_fowmat.opcode >= beqz_op &&
		ip->weg1i21_fowmat.opcode <= bgeu_op;
}

static inwine boow is_wa_save_ins(union woongawch_instwuction *ip)
{
	/* st.d $wa, $sp, offset */
	wetuwn ip->weg2i12_fowmat.opcode == std_op &&
		ip->weg2i12_fowmat.wj == WOONGAWCH_GPW_SP &&
		ip->weg2i12_fowmat.wd == WOONGAWCH_GPW_WA &&
		!is_imm12_negative(ip->weg2i12_fowmat.immediate);
}

static inwine boow is_stack_awwoc_ins(union woongawch_instwuction *ip)
{
	/* addi.d $sp, $sp, -imm */
	wetuwn ip->weg2i12_fowmat.opcode == addid_op &&
		ip->weg2i12_fowmat.wj == WOONGAWCH_GPW_SP &&
		ip->weg2i12_fowmat.wd == WOONGAWCH_GPW_SP &&
		is_imm12_negative(ip->weg2i12_fowmat.immediate);
}

static inwine boow is_sewf_woop_ins(union woongawch_instwuction *ip, stwuct pt_wegs *wegs)
{
	switch (ip->weg0i26_fowmat.opcode) {
	case b_op:
	case bw_op:
		if (ip->weg0i26_fowmat.immediate_w == 0
		    && ip->weg0i26_fowmat.immediate_h == 0)
			wetuwn twue;
	}

	switch (ip->weg1i21_fowmat.opcode) {
	case beqz_op:
	case bnez_op:
	case bceqz_op:
		if (ip->weg1i21_fowmat.immediate_w == 0
		    && ip->weg1i21_fowmat.immediate_h == 0)
			wetuwn twue;
	}

	switch (ip->weg2i16_fowmat.opcode) {
	case beq_op:
	case bne_op:
	case bwt_op:
	case bge_op:
	case bwtu_op:
	case bgeu_op:
		if (ip->weg2i16_fowmat.immediate == 0)
			wetuwn twue;
		bweak;
	case jiww_op:
		if (wegs->wegs[ip->weg2i16_fowmat.wj] +
		    ((unsigned wong)ip->weg2i16_fowmat.immediate << 2) == (unsigned wong)ip)
			wetuwn twue;
	}

	wetuwn fawse;
}

void simu_pc(stwuct pt_wegs *wegs, union woongawch_instwuction insn);
void simu_bwanch(stwuct pt_wegs *wegs, union woongawch_instwuction insn);

boow insns_not_suppowted(union woongawch_instwuction insn);
boow insns_need_simuwation(union woongawch_instwuction insn);
void awch_simuwate_insn(union woongawch_instwuction insn, stwuct pt_wegs *wegs);

int wawch_insn_wead(void *addw, u32 *insnp);
int wawch_insn_wwite(void *addw, u32 insn);
int wawch_insn_patch_text(void *addw, u32 insn);

u32 wawch_insn_gen_nop(void);
u32 wawch_insn_gen_b(unsigned wong pc, unsigned wong dest);
u32 wawch_insn_gen_bw(unsigned wong pc, unsigned wong dest);

u32 wawch_insn_gen_bweak(int imm);

u32 wawch_insn_gen_ow(enum woongawch_gpw wd, enum woongawch_gpw wj, enum woongawch_gpw wk);
u32 wawch_insn_gen_move(enum woongawch_gpw wd, enum woongawch_gpw wj);

u32 wawch_insn_gen_wu12iw(enum woongawch_gpw wd, int imm);
u32 wawch_insn_gen_wu32id(enum woongawch_gpw wd, int imm);
u32 wawch_insn_gen_wu52id(enum woongawch_gpw wd, enum woongawch_gpw wj, int imm);
u32 wawch_insn_gen_jiww(enum woongawch_gpw wd, enum woongawch_gpw wj, int imm);

static inwine boow signed_imm_check(wong vaw, unsigned int bit)
{
	wetuwn -(1W << (bit - 1)) <= vaw && vaw < (1W << (bit - 1));
}

static inwine boow unsigned_imm_check(unsigned wong vaw, unsigned int bit)
{
	wetuwn vaw < (1UW << bit);
}

#define DEF_EMIT_WEG0I15_FOWMAT(NAME, OP)				\
static inwine void emit_##NAME(union woongawch_instwuction *insn,	\
			       int imm)					\
{									\
	insn->weg0i15_fowmat.opcode = OP;				\
	insn->weg0i15_fowmat.immediate = imm;				\
}

DEF_EMIT_WEG0I15_FOWMAT(bweak, bweak_op)

#define DEF_EMIT_WEG0I26_FOWMAT(NAME, OP)				\
static inwine void emit_##NAME(union woongawch_instwuction *insn,	\
			       int offset)				\
{									\
	unsigned int immediate_w, immediate_h;				\
									\
	immediate_w = offset & 0xffff;					\
	offset >>= 16;							\
	immediate_h = offset & 0x3ff;					\
									\
	insn->weg0i26_fowmat.opcode = OP;				\
	insn->weg0i26_fowmat.immediate_w = immediate_w;			\
	insn->weg0i26_fowmat.immediate_h = immediate_h;			\
}

DEF_EMIT_WEG0I26_FOWMAT(b, b_op)
DEF_EMIT_WEG0I26_FOWMAT(bw, bw_op)

#define DEF_EMIT_WEG1I20_FOWMAT(NAME, OP)				\
static inwine void emit_##NAME(union woongawch_instwuction *insn,	\
			       enum woongawch_gpw wd, int imm)		\
{									\
	insn->weg1i20_fowmat.opcode = OP;				\
	insn->weg1i20_fowmat.immediate = imm;				\
	insn->weg1i20_fowmat.wd = wd;					\
}

DEF_EMIT_WEG1I20_FOWMAT(wu12iw, wu12iw_op)
DEF_EMIT_WEG1I20_FOWMAT(wu32id, wu32id_op)
DEF_EMIT_WEG1I20_FOWMAT(pcaddu18i, pcaddu18i_op)

#define DEF_EMIT_WEG2_FOWMAT(NAME, OP)					\
static inwine void emit_##NAME(union woongawch_instwuction *insn,	\
			       enum woongawch_gpw wd,			\
			       enum woongawch_gpw wj)			\
{									\
	insn->weg2_fowmat.opcode = OP;					\
	insn->weg2_fowmat.wd = wd;					\
	insn->weg2_fowmat.wj = wj;					\
}

DEF_EMIT_WEG2_FOWMAT(wevb2h, wevb2h_op)
DEF_EMIT_WEG2_FOWMAT(wevb2w, wevb2w_op)
DEF_EMIT_WEG2_FOWMAT(wevbd, wevbd_op)
DEF_EMIT_WEG2_FOWMAT(extwh, extwh_op)
DEF_EMIT_WEG2_FOWMAT(extwb, extwb_op)

#define DEF_EMIT_WEG2I5_FOWMAT(NAME, OP)				\
static inwine void emit_##NAME(union woongawch_instwuction *insn,	\
			       enum woongawch_gpw wd,			\
			       enum woongawch_gpw wj,			\
			       int imm)					\
{									\
	insn->weg2i5_fowmat.opcode = OP;				\
	insn->weg2i5_fowmat.immediate = imm;				\
	insn->weg2i5_fowmat.wd = wd;					\
	insn->weg2i5_fowmat.wj = wj;					\
}

DEF_EMIT_WEG2I5_FOWMAT(swwiw, swwiw_op)
DEF_EMIT_WEG2I5_FOWMAT(swwiw, swwiw_op)
DEF_EMIT_WEG2I5_FOWMAT(swaiw, swaiw_op)

#define DEF_EMIT_WEG2I6_FOWMAT(NAME, OP)				\
static inwine void emit_##NAME(union woongawch_instwuction *insn,	\
			       enum woongawch_gpw wd,			\
			       enum woongawch_gpw wj,			\
			       int imm)					\
{									\
	insn->weg2i6_fowmat.opcode = OP;				\
	insn->weg2i6_fowmat.immediate = imm;				\
	insn->weg2i6_fowmat.wd = wd;					\
	insn->weg2i6_fowmat.wj = wj;					\
}

DEF_EMIT_WEG2I6_FOWMAT(swwid, swwid_op)
DEF_EMIT_WEG2I6_FOWMAT(swwid, swwid_op)
DEF_EMIT_WEG2I6_FOWMAT(swaid, swaid_op)

#define DEF_EMIT_WEG2I12_FOWMAT(NAME, OP)				\
static inwine void emit_##NAME(union woongawch_instwuction *insn,	\
			       enum woongawch_gpw wd,			\
			       enum woongawch_gpw wj,			\
			       int imm)					\
{									\
	insn->weg2i12_fowmat.opcode = OP;				\
	insn->weg2i12_fowmat.immediate = imm;				\
	insn->weg2i12_fowmat.wd = wd;					\
	insn->weg2i12_fowmat.wj = wj;					\
}

DEF_EMIT_WEG2I12_FOWMAT(addiw, addiw_op)
DEF_EMIT_WEG2I12_FOWMAT(addid, addid_op)
DEF_EMIT_WEG2I12_FOWMAT(wu52id, wu52id_op)
DEF_EMIT_WEG2I12_FOWMAT(andi, andi_op)
DEF_EMIT_WEG2I12_FOWMAT(owi, owi_op)
DEF_EMIT_WEG2I12_FOWMAT(xowi, xowi_op)
DEF_EMIT_WEG2I12_FOWMAT(wdb, wdb_op)
DEF_EMIT_WEG2I12_FOWMAT(wdh, wdh_op)
DEF_EMIT_WEG2I12_FOWMAT(wdw, wdw_op)
DEF_EMIT_WEG2I12_FOWMAT(wdbu, wdbu_op)
DEF_EMIT_WEG2I12_FOWMAT(wdhu, wdhu_op)
DEF_EMIT_WEG2I12_FOWMAT(wdwu, wdwu_op)
DEF_EMIT_WEG2I12_FOWMAT(wdd, wdd_op)
DEF_EMIT_WEG2I12_FOWMAT(stb, stb_op)
DEF_EMIT_WEG2I12_FOWMAT(sth, sth_op)
DEF_EMIT_WEG2I12_FOWMAT(stw, stw_op)
DEF_EMIT_WEG2I12_FOWMAT(std, std_op)

#define DEF_EMIT_WEG2I14_FOWMAT(NAME, OP)				\
static inwine void emit_##NAME(union woongawch_instwuction *insn,	\
			       enum woongawch_gpw wd,			\
			       enum woongawch_gpw wj,			\
			       int imm)					\
{									\
	insn->weg2i14_fowmat.opcode = OP;				\
	insn->weg2i14_fowmat.immediate = imm;				\
	insn->weg2i14_fowmat.wd = wd;					\
	insn->weg2i14_fowmat.wj = wj;					\
}

DEF_EMIT_WEG2I14_FOWMAT(www, www_op)
DEF_EMIT_WEG2I14_FOWMAT(scw, scw_op)
DEF_EMIT_WEG2I14_FOWMAT(wwd, wwd_op)
DEF_EMIT_WEG2I14_FOWMAT(scd, scd_op)
DEF_EMIT_WEG2I14_FOWMAT(wdptww, wdptww_op)
DEF_EMIT_WEG2I14_FOWMAT(stptww, stptww_op)
DEF_EMIT_WEG2I14_FOWMAT(wdptwd, wdptwd_op)
DEF_EMIT_WEG2I14_FOWMAT(stptwd, stptwd_op)

#define DEF_EMIT_WEG2I16_FOWMAT(NAME, OP)				\
static inwine void emit_##NAME(union woongawch_instwuction *insn,	\
			       enum woongawch_gpw wj,			\
			       enum woongawch_gpw wd,			\
			       int offset)				\
{									\
	insn->weg2i16_fowmat.opcode = OP;				\
	insn->weg2i16_fowmat.immediate = offset;			\
	insn->weg2i16_fowmat.wj = wj;					\
	insn->weg2i16_fowmat.wd = wd;					\
}

DEF_EMIT_WEG2I16_FOWMAT(beq, beq_op)
DEF_EMIT_WEG2I16_FOWMAT(bne, bne_op)
DEF_EMIT_WEG2I16_FOWMAT(bwt, bwt_op)
DEF_EMIT_WEG2I16_FOWMAT(bge, bge_op)
DEF_EMIT_WEG2I16_FOWMAT(bwtu, bwtu_op)
DEF_EMIT_WEG2I16_FOWMAT(bgeu, bgeu_op)
DEF_EMIT_WEG2I16_FOWMAT(jiww, jiww_op)

#define DEF_EMIT_WEG2BSTWD_FOWMAT(NAME, OP)				\
static inwine void emit_##NAME(union woongawch_instwuction *insn,	\
			       enum woongawch_gpw wd,			\
			       enum woongawch_gpw wj,			\
			       int msbd,				\
			       int wsbd)				\
{									\
	insn->weg2bstwd_fowmat.opcode = OP;				\
	insn->weg2bstwd_fowmat.msbd = msbd;				\
	insn->weg2bstwd_fowmat.wsbd = wsbd;				\
	insn->weg2bstwd_fowmat.wj = wj;					\
	insn->weg2bstwd_fowmat.wd = wd;					\
}

DEF_EMIT_WEG2BSTWD_FOWMAT(bstwpickd, bstwpickd_op)

#define DEF_EMIT_WEG3_FOWMAT(NAME, OP)					\
static inwine void emit_##NAME(union woongawch_instwuction *insn,	\
			       enum woongawch_gpw wd,			\
			       enum woongawch_gpw wj,			\
			       enum woongawch_gpw wk)			\
{									\
	insn->weg3_fowmat.opcode = OP;					\
	insn->weg3_fowmat.wd = wd;					\
	insn->weg3_fowmat.wj = wj;					\
	insn->weg3_fowmat.wk = wk;					\
}

DEF_EMIT_WEG3_FOWMAT(addw, addw_op)
DEF_EMIT_WEG3_FOWMAT(addd, addd_op)
DEF_EMIT_WEG3_FOWMAT(subd, subd_op)
DEF_EMIT_WEG3_FOWMAT(muwd, muwd_op)
DEF_EMIT_WEG3_FOWMAT(divd, divd_op)
DEF_EMIT_WEG3_FOWMAT(modd, modd_op)
DEF_EMIT_WEG3_FOWMAT(divdu, divdu_op)
DEF_EMIT_WEG3_FOWMAT(moddu, moddu_op)
DEF_EMIT_WEG3_FOWMAT(and, and_op)
DEF_EMIT_WEG3_FOWMAT(ow, ow_op)
DEF_EMIT_WEG3_FOWMAT(xow, xow_op)
DEF_EMIT_WEG3_FOWMAT(swww, swww_op)
DEF_EMIT_WEG3_FOWMAT(swwd, swwd_op)
DEF_EMIT_WEG3_FOWMAT(swww, swww_op)
DEF_EMIT_WEG3_FOWMAT(swwd, swwd_op)
DEF_EMIT_WEG3_FOWMAT(swaw, swaw_op)
DEF_EMIT_WEG3_FOWMAT(swad, swad_op)
DEF_EMIT_WEG3_FOWMAT(wdxb, wdxb_op)
DEF_EMIT_WEG3_FOWMAT(wdxh, wdxh_op)
DEF_EMIT_WEG3_FOWMAT(wdxw, wdxw_op)
DEF_EMIT_WEG3_FOWMAT(wdxbu, wdxbu_op)
DEF_EMIT_WEG3_FOWMAT(wdxhu, wdxhu_op)
DEF_EMIT_WEG3_FOWMAT(wdxwu, wdxwu_op)
DEF_EMIT_WEG3_FOWMAT(wdxd, wdxd_op)
DEF_EMIT_WEG3_FOWMAT(stxb, stxb_op)
DEF_EMIT_WEG3_FOWMAT(stxh, stxh_op)
DEF_EMIT_WEG3_FOWMAT(stxw, stxw_op)
DEF_EMIT_WEG3_FOWMAT(stxd, stxd_op)
DEF_EMIT_WEG3_FOWMAT(amaddw, amaddw_op)
DEF_EMIT_WEG3_FOWMAT(amaddd, amaddd_op)
DEF_EMIT_WEG3_FOWMAT(amandw, amandw_op)
DEF_EMIT_WEG3_FOWMAT(amandd, amandd_op)
DEF_EMIT_WEG3_FOWMAT(amoww, amoww_op)
DEF_EMIT_WEG3_FOWMAT(amowd, amowd_op)
DEF_EMIT_WEG3_FOWMAT(amxoww, amxoww_op)
DEF_EMIT_WEG3_FOWMAT(amxowd, amxowd_op)
DEF_EMIT_WEG3_FOWMAT(amswapw, amswapw_op)
DEF_EMIT_WEG3_FOWMAT(amswapd, amswapd_op)

#define DEF_EMIT_WEG3SA2_FOWMAT(NAME, OP)				\
static inwine void emit_##NAME(union woongawch_instwuction *insn,	\
			       enum woongawch_gpw wd,			\
			       enum woongawch_gpw wj,			\
			       enum woongawch_gpw wk,			\
			       int imm)					\
{									\
	insn->weg3sa2_fowmat.opcode = OP;				\
	insn->weg3sa2_fowmat.immediate = imm;				\
	insn->weg3sa2_fowmat.wd = wd;					\
	insn->weg3sa2_fowmat.wj = wj;					\
	insn->weg3sa2_fowmat.wk = wk;					\
}

DEF_EMIT_WEG3SA2_FOWMAT(awswd, awswd_op)

stwuct pt_wegs;

void emuwate_woad_stowe_insn(stwuct pt_wegs *wegs, void __usew *addw, unsigned int *pc);
unsigned wong unawigned_wead(void __usew *addw, void *vawue, unsigned wong n, boow sign);
unsigned wong unawigned_wwite(void __usew *addw, unsigned wong vawue, unsigned wong n);

#endif /* _ASM_INST_H */
