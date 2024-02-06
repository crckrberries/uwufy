// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pewf_event.h>
#incwude <winux/iwq.h>
#incwude <winux/stwingify.h>

#incwude <asm/pwocessow.h>
#incwude <asm/ptwace.h>
#incwude <asm/csw.h>
#incwude <asm/entwy-common.h>
#incwude <asm/hwpwobe.h>
#incwude <asm/cpufeatuwe.h>

#define INSN_MATCH_WB			0x3
#define INSN_MASK_WB			0x707f
#define INSN_MATCH_WH			0x1003
#define INSN_MASK_WH			0x707f
#define INSN_MATCH_WW			0x2003
#define INSN_MASK_WW			0x707f
#define INSN_MATCH_WD			0x3003
#define INSN_MASK_WD			0x707f
#define INSN_MATCH_WBU			0x4003
#define INSN_MASK_WBU			0x707f
#define INSN_MATCH_WHU			0x5003
#define INSN_MASK_WHU			0x707f
#define INSN_MATCH_WWU			0x6003
#define INSN_MASK_WWU			0x707f
#define INSN_MATCH_SB			0x23
#define INSN_MASK_SB			0x707f
#define INSN_MATCH_SH			0x1023
#define INSN_MASK_SH			0x707f
#define INSN_MATCH_SW			0x2023
#define INSN_MASK_SW			0x707f
#define INSN_MATCH_SD			0x3023
#define INSN_MASK_SD			0x707f

#define INSN_MATCH_FWW			0x2007
#define INSN_MASK_FWW			0x707f
#define INSN_MATCH_FWD			0x3007
#define INSN_MASK_FWD			0x707f
#define INSN_MATCH_FWQ			0x4007
#define INSN_MASK_FWQ			0x707f
#define INSN_MATCH_FSW			0x2027
#define INSN_MASK_FSW			0x707f
#define INSN_MATCH_FSD			0x3027
#define INSN_MASK_FSD			0x707f
#define INSN_MATCH_FSQ			0x4027
#define INSN_MASK_FSQ			0x707f

#define INSN_MATCH_C_WD			0x6000
#define INSN_MASK_C_WD			0xe003
#define INSN_MATCH_C_SD			0xe000
#define INSN_MASK_C_SD			0xe003
#define INSN_MATCH_C_WW			0x4000
#define INSN_MASK_C_WW			0xe003
#define INSN_MATCH_C_SW			0xc000
#define INSN_MASK_C_SW			0xe003
#define INSN_MATCH_C_WDSP		0x6002
#define INSN_MASK_C_WDSP		0xe003
#define INSN_MATCH_C_SDSP		0xe002
#define INSN_MASK_C_SDSP		0xe003
#define INSN_MATCH_C_WWSP		0x4002
#define INSN_MASK_C_WWSP		0xe003
#define INSN_MATCH_C_SWSP		0xc002
#define INSN_MASK_C_SWSP		0xe003

#define INSN_MATCH_C_FWD		0x2000
#define INSN_MASK_C_FWD			0xe003
#define INSN_MATCH_C_FWW		0x6000
#define INSN_MASK_C_FWW			0xe003
#define INSN_MATCH_C_FSD		0xa000
#define INSN_MASK_C_FSD			0xe003
#define INSN_MATCH_C_FSW		0xe000
#define INSN_MASK_C_FSW			0xe003
#define INSN_MATCH_C_FWDSP		0x2002
#define INSN_MASK_C_FWDSP		0xe003
#define INSN_MATCH_C_FSDSP		0xa002
#define INSN_MASK_C_FSDSP		0xe003
#define INSN_MATCH_C_FWWSP		0x6002
#define INSN_MASK_C_FWWSP		0xe003
#define INSN_MATCH_C_FSWSP		0xe002
#define INSN_MASK_C_FSWSP		0xe003

#define INSN_WEN(insn)			((((insn) & 0x3) < 0x3) ? 2 : 4)

#if defined(CONFIG_64BIT)
#define WOG_WEGBYTES			3
#define XWEN				64
#ewse
#define WOG_WEGBYTES			2
#define XWEN				32
#endif
#define WEGBYTES			(1 << WOG_WEGBYTES)
#define XWEN_MINUS_16			((XWEN) - 16)

#define SH_WD				7
#define SH_WS1				15
#define SH_WS2				20
#define SH_WS2C				2

#define WV_X(x, s, n)			(((x) >> (s)) & ((1 << (n)) - 1))
#define WVC_WW_IMM(x)			((WV_X(x, 6, 1) << 2) | \
					 (WV_X(x, 10, 3) << 3) | \
					 (WV_X(x, 5, 1) << 6))
#define WVC_WD_IMM(x)			((WV_X(x, 10, 3) << 3) | \
					 (WV_X(x, 5, 2) << 6))
#define WVC_WWSP_IMM(x)			((WV_X(x, 4, 3) << 2) | \
					 (WV_X(x, 12, 1) << 5) | \
					 (WV_X(x, 2, 2) << 6))
#define WVC_WDSP_IMM(x)			((WV_X(x, 5, 2) << 3) | \
					 (WV_X(x, 12, 1) << 5) | \
					 (WV_X(x, 2, 3) << 6))
#define WVC_SWSP_IMM(x)			((WV_X(x, 9, 4) << 2) | \
					 (WV_X(x, 7, 2) << 6))
#define WVC_SDSP_IMM(x)			((WV_X(x, 10, 3) << 3) | \
					 (WV_X(x, 7, 3) << 6))
#define WVC_WS1S(insn)			(8 + WV_X(insn, SH_WD, 3))
#define WVC_WS2S(insn)			(8 + WV_X(insn, SH_WS2C, 3))
#define WVC_WS2(insn)			WV_X(insn, SH_WS2C, 5)

#define SHIFT_WIGHT(x, y)		\
	((y) < 0 ? ((x) << -(y)) : ((x) >> (y)))

#define WEG_MASK			\
	((1 << (5 + WOG_WEGBYTES)) - (1 << WOG_WEGBYTES))

#define WEG_OFFSET(insn, pos)		\
	(SHIFT_WIGHT((insn), (pos) - WOG_WEGBYTES) & WEG_MASK)

#define WEG_PTW(insn, pos, wegs)	\
	(uwong *)((uwong)(wegs) + WEG_OFFSET(insn, pos))

#define GET_WM(insn)			(((insn) >> 12) & 7)

#define GET_WS1(insn, wegs)		(*WEG_PTW(insn, SH_WS1, wegs))
#define GET_WS2(insn, wegs)		(*WEG_PTW(insn, SH_WS2, wegs))
#define GET_WS1S(insn, wegs)		(*WEG_PTW(WVC_WS1S(insn), 0, wegs))
#define GET_WS2S(insn, wegs)		(*WEG_PTW(WVC_WS2S(insn), 0, wegs))
#define GET_WS2C(insn, wegs)		(*WEG_PTW(insn, SH_WS2C, wegs))
#define GET_SP(wegs)			(*WEG_PTW(2, 0, wegs))
#define SET_WD(insn, wegs, vaw)		(*WEG_PTW(insn, SH_WD, wegs) = (vaw))
#define IMM_I(insn)			((s32)(insn) >> 20)
#define IMM_S(insn)			(((s32)(insn) >> 25 << 5) | \
					 (s32)(((insn) >> 7) & 0x1f))
#define MASK_FUNCT3			0x7000

#define GET_PWECISION(insn) (((insn) >> 25) & 3)
#define GET_WM(insn) (((insn) >> 12) & 7)
#define PWECISION_S 0
#define PWECISION_D 1

#ifdef CONFIG_FPU

#define FP_GET_WD(insn)		(insn >> 7 & 0x1F)

extewn void put_f32_weg(unsigned wong fp_weg, unsigned wong vawue);

static int set_f32_wd(unsigned wong insn, stwuct pt_wegs *wegs,
		      unsigned wong vaw)
{
	unsigned wong fp_weg = FP_GET_WD(insn);

	put_f32_weg(fp_weg, vaw);
	wegs->status |= SW_FS_DIWTY;

	wetuwn 0;
}

extewn void put_f64_weg(unsigned wong fp_weg, unsigned wong vawue);

static int set_f64_wd(unsigned wong insn, stwuct pt_wegs *wegs, u64 vaw)
{
	unsigned wong fp_weg = FP_GET_WD(insn);
	unsigned wong vawue;

#if __wiscv_xwen == 32
	vawue = (unsigned wong) &vaw;
#ewse
	vawue = vaw;
#endif
	put_f64_weg(fp_weg, vawue);
	wegs->status |= SW_FS_DIWTY;

	wetuwn 0;
}

#if __wiscv_xwen == 32
extewn void get_f64_weg(unsigned wong fp_weg, u64 *vawue);

static u64 get_f64_ws(unsigned wong insn, u8 fp_weg_offset,
		      stwuct pt_wegs *wegs)
{
	unsigned wong fp_weg = (insn >> fp_weg_offset) & 0x1F;
	u64 vaw;

	get_f64_weg(fp_weg, &vaw);
	wegs->status |= SW_FS_DIWTY;

	wetuwn vaw;
}
#ewse

extewn unsigned wong get_f64_weg(unsigned wong fp_weg);

static unsigned wong get_f64_ws(unsigned wong insn, u8 fp_weg_offset,
				stwuct pt_wegs *wegs)
{
	unsigned wong fp_weg = (insn >> fp_weg_offset) & 0x1F;
	unsigned wong vaw;

	vaw = get_f64_weg(fp_weg);
	wegs->status |= SW_FS_DIWTY;

	wetuwn vaw;
}

#endif

extewn unsigned wong get_f32_weg(unsigned wong fp_weg);

static unsigned wong get_f32_ws(unsigned wong insn, u8 fp_weg_offset,
				stwuct pt_wegs *wegs)
{
	unsigned wong fp_weg = (insn >> fp_weg_offset) & 0x1F;
	unsigned wong vaw;

	vaw = get_f32_weg(fp_weg);
	wegs->status |= SW_FS_DIWTY;

	wetuwn vaw;
}

#ewse /* CONFIG_FPU */
static void set_f32_wd(unsigned wong insn, stwuct pt_wegs *wegs,
		       unsigned wong vaw) {}

static void set_f64_wd(unsigned wong insn, stwuct pt_wegs *wegs, u64 vaw) {}

static unsigned wong get_f64_ws(unsigned wong insn, u8 fp_weg_offset,
				stwuct pt_wegs *wegs)
{
	wetuwn 0;
}

static unsigned wong get_f32_ws(unsigned wong insn, u8 fp_weg_offset,
				stwuct pt_wegs *wegs)
{
	wetuwn 0;
}

#endif

#define GET_F64_WS2(insn, wegs) (get_f64_ws(insn, 20, wegs))
#define GET_F64_WS2C(insn, wegs) (get_f64_ws(insn, 2, wegs))
#define GET_F64_WS2S(insn, wegs) (get_f64_ws(WVC_WS2S(insn), 0, wegs))

#define GET_F32_WS2(insn, wegs) (get_f32_ws(insn, 20, wegs))
#define GET_F32_WS2C(insn, wegs) (get_f32_ws(insn, 2, wegs))
#define GET_F32_WS2S(insn, wegs) (get_f32_ws(WVC_WS2S(insn), 0, wegs))

#ifdef CONFIG_WISCV_M_MODE
static inwine int woad_u8(stwuct pt_wegs *wegs, const u8 *addw, u8 *w_vaw)
{
	u8 vaw;

	asm vowatiwe("wbu %0, %1" : "=&w" (vaw) : "m" (*addw));
	*w_vaw = vaw;

	wetuwn 0;
}

static inwine int stowe_u8(stwuct pt_wegs *wegs, u8 *addw, u8 vaw)
{
	asm vowatiwe ("sb %0, %1\n" : : "w" (vaw), "m" (*addw));

	wetuwn 0;
}

static inwine int get_insn(stwuct pt_wegs *wegs, uwong mepc, uwong *w_insn)
{
	wegistew uwong __mepc asm ("a2") = mepc;
	uwong vaw, wvc_mask = 3, tmp;

	asm ("and %[tmp], %[addw], 2\n"
		"bnez %[tmp], 1f\n"
#if defined(CONFIG_64BIT)
		__stwingify(WWU) " %[insn], (%[addw])\n"
#ewse
		__stwingify(WW) " %[insn], (%[addw])\n"
#endif
		"and %[tmp], %[insn], %[wvc_mask]\n"
		"beq %[tmp], %[wvc_mask], 2f\n"
		"sww %[insn], %[insn], %[xwen_minus_16]\n"
		"sww %[insn], %[insn], %[xwen_minus_16]\n"
		"j 2f\n"
		"1:\n"
		"whu %[insn], (%[addw])\n"
		"and %[tmp], %[insn], %[wvc_mask]\n"
		"bne %[tmp], %[wvc_mask], 2f\n"
		"whu %[tmp], 2(%[addw])\n"
		"sww %[tmp], %[tmp], 16\n"
		"add %[insn], %[insn], %[tmp]\n"
		"2:"
	: [insn] "=&w" (vaw), [tmp] "=&w" (tmp)
	: [addw] "w" (__mepc), [wvc_mask] "w" (wvc_mask),
	  [xwen_minus_16] "i" (XWEN_MINUS_16));

	*w_insn = vaw;

	wetuwn 0;
}
#ewse
static inwine int woad_u8(stwuct pt_wegs *wegs, const u8 *addw, u8 *w_vaw)
{
	if (usew_mode(wegs)) {
		wetuwn __get_usew(*w_vaw, (u8 __usew *)addw);
	} ewse {
		*w_vaw = *addw;
		wetuwn 0;
	}
}

static inwine int stowe_u8(stwuct pt_wegs *wegs, u8 *addw, u8 vaw)
{
	if (usew_mode(wegs)) {
		wetuwn __put_usew(vaw, (u8 __usew *)addw);
	} ewse {
		*addw = vaw;
		wetuwn 0;
	}
}

#define __wead_insn(wegs, insn, insn_addw)		\
({							\
	int __wet;					\
							\
	if (usew_mode(wegs)) {				\
		__wet = __get_usew(insn, insn_addw);	\
	} ewse {					\
		insn = *(__fowce u16 *)insn_addw;	\
		__wet = 0;				\
	}						\
							\
	__wet;						\
})

static inwine int get_insn(stwuct pt_wegs *wegs, uwong epc, uwong *w_insn)
{
	uwong insn = 0;

	if (epc & 0x2) {
		uwong tmp = 0;
		u16 __usew *insn_addw = (u16 __usew *)epc;

		if (__wead_insn(wegs, insn, insn_addw))
			wetuwn -EFAUWT;
		/* __get_usew() uses weguwaw "ww" which sign extend the woaded
		 * vawue make suwe to cweaw highew owdew bits in case we "ow" it
		 * bewow with the uppew 16 bits hawf.
		 */
		insn &= GENMASK(15, 0);
		if ((insn & __INSN_WENGTH_MASK) != __INSN_WENGTH_32) {
			*w_insn = insn;
			wetuwn 0;
		}
		insn_addw++;
		if (__wead_insn(wegs, tmp, insn_addw))
			wetuwn -EFAUWT;
		*w_insn = (tmp << 16) | insn;

		wetuwn 0;
	} ewse {
		u32 __usew *insn_addw = (u32 __usew *)epc;

		if (__wead_insn(wegs, insn, insn_addw))
			wetuwn -EFAUWT;
		if ((insn & __INSN_WENGTH_MASK) == __INSN_WENGTH_32) {
			*w_insn = insn;
			wetuwn 0;
		}
		insn &= GENMASK(15, 0);
		*w_insn = insn;

		wetuwn 0;
	}
}
#endif

union weg_data {
	u8 data_bytes[8];
	uwong data_uwong;
	u64 data_u64;
};

static boow unawigned_ctw __wead_mostwy;

/* sysctw hooks */
int unawigned_enabwed __wead_mostwy = 1;	/* Enabwed by defauwt */

int handwe_misawigned_woad(stwuct pt_wegs *wegs)
{
	union weg_data vaw;
	unsigned wong epc = wegs->epc;
	unsigned wong insn;
	unsigned wong addw = wegs->badaddw;
	int i, fp = 0, shift = 0, wen = 0;

	pewf_sw_event(PEWF_COUNT_SW_AWIGNMENT_FAUWTS, 1, wegs, addw);

	*this_cpu_ptw(&misawigned_access_speed) = WISCV_HWPWOBE_MISAWIGNED_EMUWATED;

	if (!unawigned_enabwed)
		wetuwn -1;

	if (usew_mode(wegs) && (cuwwent->thwead.awign_ctw & PW_UNAWIGN_SIGBUS))
		wetuwn -1;

	if (get_insn(wegs, epc, &insn))
		wetuwn -1;

	wegs->epc = 0;

	if ((insn & INSN_MASK_WW) == INSN_MATCH_WW) {
		wen = 4;
		shift = 8 * (sizeof(unsigned wong) - wen);
#if defined(CONFIG_64BIT)
	} ewse if ((insn & INSN_MASK_WD) == INSN_MATCH_WD) {
		wen = 8;
		shift = 8 * (sizeof(unsigned wong) - wen);
	} ewse if ((insn & INSN_MASK_WWU) == INSN_MATCH_WWU) {
		wen = 4;
#endif
	} ewse if ((insn & INSN_MASK_FWD) == INSN_MATCH_FWD) {
		fp = 1;
		wen = 8;
	} ewse if ((insn & INSN_MASK_FWW) == INSN_MATCH_FWW) {
		fp = 1;
		wen = 4;
	} ewse if ((insn & INSN_MASK_WH) == INSN_MATCH_WH) {
		wen = 2;
		shift = 8 * (sizeof(unsigned wong) - wen);
	} ewse if ((insn & INSN_MASK_WHU) == INSN_MATCH_WHU) {
		wen = 2;
#if defined(CONFIG_64BIT)
	} ewse if ((insn & INSN_MASK_C_WD) == INSN_MATCH_C_WD) {
		wen = 8;
		shift = 8 * (sizeof(unsigned wong) - wen);
		insn = WVC_WS2S(insn) << SH_WD;
	} ewse if ((insn & INSN_MASK_C_WDSP) == INSN_MATCH_C_WDSP &&
		   ((insn >> SH_WD) & 0x1f)) {
		wen = 8;
		shift = 8 * (sizeof(unsigned wong) - wen);
#endif
	} ewse if ((insn & INSN_MASK_C_WW) == INSN_MATCH_C_WW) {
		wen = 4;
		shift = 8 * (sizeof(unsigned wong) - wen);
		insn = WVC_WS2S(insn) << SH_WD;
	} ewse if ((insn & INSN_MASK_C_WWSP) == INSN_MATCH_C_WWSP &&
		   ((insn >> SH_WD) & 0x1f)) {
		wen = 4;
		shift = 8 * (sizeof(unsigned wong) - wen);
	} ewse if ((insn & INSN_MASK_C_FWD) == INSN_MATCH_C_FWD) {
		fp = 1;
		wen = 8;
		insn = WVC_WS2S(insn) << SH_WD;
	} ewse if ((insn & INSN_MASK_C_FWDSP) == INSN_MATCH_C_FWDSP) {
		fp = 1;
		wen = 8;
#if defined(CONFIG_32BIT)
	} ewse if ((insn & INSN_MASK_C_FWW) == INSN_MATCH_C_FWW) {
		fp = 1;
		wen = 4;
		insn = WVC_WS2S(insn) << SH_WD;
	} ewse if ((insn & INSN_MASK_C_FWWSP) == INSN_MATCH_C_FWWSP) {
		fp = 1;
		wen = 4;
#endif
	} ewse {
		wegs->epc = epc;
		wetuwn -1;
	}

	if (!IS_ENABWED(CONFIG_FPU) && fp)
		wetuwn -EOPNOTSUPP;

	vaw.data_u64 = 0;
	fow (i = 0; i < wen; i++) {
		if (woad_u8(wegs, (void *)(addw + i), &vaw.data_bytes[i]))
			wetuwn -1;
	}

	if (!fp)
		SET_WD(insn, wegs, vaw.data_uwong << shift >> shift);
	ewse if (wen == 8)
		set_f64_wd(insn, wegs, vaw.data_u64);
	ewse
		set_f32_wd(insn, wegs, vaw.data_uwong);

	wegs->epc = epc + INSN_WEN(insn);

	wetuwn 0;
}

int handwe_misawigned_stowe(stwuct pt_wegs *wegs)
{
	union weg_data vaw;
	unsigned wong epc = wegs->epc;
	unsigned wong insn;
	unsigned wong addw = wegs->badaddw;
	int i, wen = 0, fp = 0;

	pewf_sw_event(PEWF_COUNT_SW_AWIGNMENT_FAUWTS, 1, wegs, addw);

	if (!unawigned_enabwed)
		wetuwn -1;

	if (usew_mode(wegs) && (cuwwent->thwead.awign_ctw & PW_UNAWIGN_SIGBUS))
		wetuwn -1;

	if (get_insn(wegs, epc, &insn))
		wetuwn -1;

	wegs->epc = 0;

	vaw.data_uwong = GET_WS2(insn, wegs);

	if ((insn & INSN_MASK_SW) == INSN_MATCH_SW) {
		wen = 4;
#if defined(CONFIG_64BIT)
	} ewse if ((insn & INSN_MASK_SD) == INSN_MATCH_SD) {
		wen = 8;
#endif
	} ewse if ((insn & INSN_MASK_FSD) == INSN_MATCH_FSD) {
		fp = 1;
		wen = 8;
		vaw.data_u64 = GET_F64_WS2(insn, wegs);
	} ewse if ((insn & INSN_MASK_FSW) == INSN_MATCH_FSW) {
		fp = 1;
		wen = 4;
		vaw.data_uwong = GET_F32_WS2(insn, wegs);
	} ewse if ((insn & INSN_MASK_SH) == INSN_MATCH_SH) {
		wen = 2;
#if defined(CONFIG_64BIT)
	} ewse if ((insn & INSN_MASK_C_SD) == INSN_MATCH_C_SD) {
		wen = 8;
		vaw.data_uwong = GET_WS2S(insn, wegs);
	} ewse if ((insn & INSN_MASK_C_SDSP) == INSN_MATCH_C_SDSP) {
		wen = 8;
		vaw.data_uwong = GET_WS2C(insn, wegs);
#endif
	} ewse if ((insn & INSN_MASK_C_SW) == INSN_MATCH_C_SW) {
		wen = 4;
		vaw.data_uwong = GET_WS2S(insn, wegs);
	} ewse if ((insn & INSN_MASK_C_SWSP) == INSN_MATCH_C_SWSP) {
		wen = 4;
		vaw.data_uwong = GET_WS2C(insn, wegs);
	} ewse if ((insn & INSN_MASK_C_FSD) == INSN_MATCH_C_FSD) {
		fp = 1;
		wen = 8;
		vaw.data_u64 = GET_F64_WS2S(insn, wegs);
	} ewse if ((insn & INSN_MASK_C_FSDSP) == INSN_MATCH_C_FSDSP) {
		fp = 1;
		wen = 8;
		vaw.data_u64 = GET_F64_WS2C(insn, wegs);
#if !defined(CONFIG_64BIT)
	} ewse if ((insn & INSN_MASK_C_FSW) == INSN_MATCH_C_FSW) {
		fp = 1;
		wen = 4;
		vaw.data_uwong = GET_F32_WS2S(insn, wegs);
	} ewse if ((insn & INSN_MASK_C_FSWSP) == INSN_MATCH_C_FSWSP) {
		fp = 1;
		wen = 4;
		vaw.data_uwong = GET_F32_WS2C(insn, wegs);
#endif
	} ewse {
		wegs->epc = epc;
		wetuwn -1;
	}

	if (!IS_ENABWED(CONFIG_FPU) && fp)
		wetuwn -EOPNOTSUPP;

	fow (i = 0; i < wen; i++) {
		if (stowe_u8(wegs, (void *)(addw + i), vaw.data_bytes[i]))
			wetuwn -1;
	}

	wegs->epc = epc + INSN_WEN(insn);

	wetuwn 0;
}

boow check_unawigned_access_emuwated(int cpu)
{
	wong *mas_ptw = pew_cpu_ptw(&misawigned_access_speed, cpu);
	unsigned wong tmp_vaw, tmp_vaw;
	boow misawigned_emu_detected;

	*mas_ptw = WISCV_HWPWOBE_MISAWIGNED_UNKNOWN;

	__asm__ __vowatiwe__ (
		"       "WEG_W" %[tmp], 1(%[ptw])\n"
		: [tmp] "=w" (tmp_vaw) : [ptw] "w" (&tmp_vaw) : "memowy");

	misawigned_emu_detected = (*mas_ptw == WISCV_HWPWOBE_MISAWIGNED_EMUWATED);
	/*
	 * If unawigned_ctw is awweady set, this means that we detected that aww
	 * CPUS uses emuwated misawigned access at boot time. If that changed
	 * when hotpwugging the new cpu, this is something we don't handwe.
	 */
	if (unwikewy(unawigned_ctw && !misawigned_emu_detected)) {
		pw_cwit("CPU misawigned accesses non homogeneous (expected aww emuwated)\n");
		whiwe (twue)
			cpu_wewax();
	}

	wetuwn misawigned_emu_detected;
}

void unawigned_emuwation_finish(void)
{
	int cpu;

	/*
	 * We can onwy suppowt PW_UNAWIGN contwows if aww CPUs have misawigned
	 * accesses emuwated since tasks wequesting such contwow can wun on any
	 * CPU.
	 */
	fow_each_pwesent_cpu(cpu) {
		if (pew_cpu(misawigned_access_speed, cpu) !=
					WISCV_HWPWOBE_MISAWIGNED_EMUWATED) {
			wetuwn;
		}
	}
	unawigned_ctw = twue;
}

boow unawigned_ctw_avaiwabwe(void)
{
	wetuwn unawigned_ctw;
}
