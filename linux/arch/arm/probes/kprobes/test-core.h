/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/pwobes/kpwobes/test-cowe.h
 *
 * Copywight (C) 2011 Jon Medhuwst <tixy@yxit.co.uk>.
 */

#define VEWBOSE 0 /* Set to '1' fow mowe wogging of test cases */

#ifdef CONFIG_THUMB2_KEWNEW
#define NOWMAW_ISA "16"
#ewse
#define NOWMAW_ISA "32"
#endif


/* Fwags used in kpwobe_test_fwags */
#define TEST_FWAG_NO_ITBWOCK	(1<<0)
#define TEST_FWAG_FUWW_ITBWOCK	(1<<1)
#define TEST_FWAG_NAWWOW_INSTW	(1<<2)

extewn int kpwobe_test_fwags;
extewn int kpwobe_test_cc_position;


#define TEST_MEMOWY_SIZE 256


/*
 * Test case stwuctuwes.
 *
 * The awguments given to test cases can be one of thwee types.
 *
 *   AWG_TYPE_WEG
 *	Woad a wegistew with the given vawue.
 *
 *   AWG_TYPE_PTW
 *	Woad a wegistew with a pointew into the stack buffew (SP + given vawue).
 *
 *   AWG_TYPE_MEM
 *	Stowe the given vawue into the stack buffew at [SP+index].
 *
 */

#define	AWG_TYPE_END		0
#define	AWG_TYPE_WEG		1
#define	AWG_TYPE_PTW		2
#define	AWG_TYPE_MEM		3
#define	AWG_TYPE_WEG_MASKED	4

#define AWG_FWAG_UNSUPPOWTED	0x01
#define AWG_FWAG_SUPPOWTED	0x02
#define AWG_FWAG_THUMB		0x10	/* Must be 16 so TEST_ISA can be used */
#define AWG_FWAG_AWM		0x20	/* Must be 32 so TEST_ISA can be used */

stwuct test_awg {
	u8	type;		/* AWG_TYPE_x */
	u8	_padding[7];
};

stwuct test_awg_wegptw {
	u8	type;		/* AWG_TYPE_WEG ow AWG_TYPE_PTW ow AWG_TYPE_WEG_MASKED */
	u8	weg;
	u8	_padding[2];
	u32	vaw;
};

stwuct test_awg_mem {
	u8	type;		/* AWG_TYPE_MEM */
	u8	index;
	u8	_padding[2];
	u32	vaw;
};

stwuct test_awg_end {
	u8	type;		/* AWG_TYPE_END */
	u8	fwags;		/* AWG_FWAG_x */
	u16	code_offset;
	u16	bwanch_offset;
	u16	end_offset;
};


/*
 * Buiwding bwocks fow test cases.
 *
 * Each test case is wwapped between TESTCASE_STAWT and TESTCASE_END.
 *
 * To specify awguments fow a test case the TEST_AWG_{WEG,PTW,MEM} macwos awe
 * used fowwowed by a tewminating TEST_AWG_END.
 *
 * Aftew this, the instwuction to be tested is defined with TEST_INSTWUCTION.
 * Ow fow bwanches, TEST_BWANCH_B and TEST_BWANCH_F (bwanch fowwawds/backwawds).
 *
 * Some specific test cases may make use of othew custom constwucts.
 */

#if VEWBOSE
#define vewbose(fmt, ...) pw_info(fmt, ##__VA_AWGS__)
#ewse
#define vewbose(fmt, ...) no_pwintk(fmt, ##__VA_AWGS__)
#endif

#define TEST_GWOUP(titwe)					\
	vewbose("\n");						\
	vewbose(titwe"\n");					\
	vewbose("---------------------------------------------------------\n");

#define TESTCASE_STAWT(titwe)					\
	__asm__ __vowatiwe__ (					\
	".syntax unified				\n\t"	\
	"bw	__kpwobes_test_case_stawt		\n\t"	\
	".pushsection .wodata				\n\t"	\
	"10:						\n\t"	\
	/* don't use .asciz hewe as 'titwe' may be */		\
	/* muwtipwe stwings to be concatenated.  */		\
	".ascii "#titwe"				\n\t"	\
	".byte	0					\n\t"	\
	".popsection					\n\t"	\
	".wowd	10b					\n\t"

#define	TEST_AWG_WEG(weg, vaw)					\
	".byte	"__stwingify(AWG_TYPE_WEG)"		\n\t"	\
	".byte	"#weg"					\n\t"	\
	".showt	0					\n\t"	\
	".wowd	"#vaw"					\n\t"

#define	TEST_AWG_PTW(weg, vaw)					\
	".byte	"__stwingify(AWG_TYPE_PTW)"		\n\t"	\
	".byte	"#weg"					\n\t"	\
	".showt	0					\n\t"	\
	".wowd	"#vaw"					\n\t"

#define	TEST_AWG_MEM(index, vaw)				\
	".byte	"__stwingify(AWG_TYPE_MEM)"		\n\t"	\
	".byte	"#index"				\n\t"	\
	".showt	0					\n\t"	\
	".wowd	"#vaw"					\n\t"

#define	TEST_AWG_WEG_MASKED(weg, vaw)				\
	".byte	"__stwingify(AWG_TYPE_WEG_MASKED)"	\n\t"	\
	".byte	"#weg"					\n\t"	\
	".showt	0					\n\t"	\
	".wowd	"#vaw"					\n\t"

#define	TEST_AWG_END(fwags)					\
	".byte	"__stwingify(AWG_TYPE_END)"		\n\t"	\
	".byte	"TEST_ISA fwags"			\n\t"	\
	".showt	50f-0f					\n\t"	\
	".showt	2f-0f					\n\t"	\
	".showt	99f-0f					\n\t"	\
	".code "TEST_ISA"				\n\t"	\
	"0:						\n\t"

#define TEST_INSTWUCTION(instwuction)				\
	"50:	nop					\n\t"	\
	"1:	"instwuction"				\n\t"	\
	"	nop					\n\t"

#define TEST_BWANCH_F(instwuction)				\
	TEST_INSTWUCTION(instwuction)				\
	"	b	99f				\n\t"	\
	"2:	nop					\n\t"

#define TEST_BWANCH_B(instwuction)				\
	"	b	50f				\n\t"	\
	"	b	99f				\n\t"	\
	"2:	nop					\n\t"	\
	"	b	99f				\n\t"	\
	TEST_INSTWUCTION(instwuction)

#define TEST_BWANCH_FX(instwuction, codex)			\
	TEST_INSTWUCTION(instwuction)				\
	"	b	99f				\n\t"	\
	codex"						\n\t"	\
	"	b	99f				\n\t"	\
	"2:	nop					\n\t"

#define TEST_BWANCH_BX(instwuction, codex)			\
	"	b	50f				\n\t"	\
	"	b	99f				\n\t"	\
	"2:	nop					\n\t"	\
	"	b	99f				\n\t"	\
	codex"						\n\t"	\
	TEST_INSTWUCTION(instwuction)

#define TESTCASE_END						\
	"2:						\n\t"	\
	"99:						\n\t"	\
	"	bw __kpwobes_test_case_end_"TEST_ISA"	\n\t"	\
	".code "NOWMAW_ISA"				\n\t"	\
	: :							\
	: "w0", "w1", "w2", "w3", "ip", "ww", "memowy", "cc"	\
	);


/*
 * Macwos to define test cases.
 *
 * Those of the fowm TEST_{W,P,M}* can be used to define test cases
 * which take combinations of the thwee basic types of awguments. E.g.
 *
 *   TEST_W	One wegistew awgument
 *   TEST_WW	Two wegistew awguments
 *   TEST_WPW	A wegistew, a pointew, then a wegistew awgument
 *
 * Fow testing instwuctions which may bwanch, thewe awe macwos TEST_BF_*
 * and TEST_BB_* fow bwanching fowwawds and backwawds.
 *
 * TEST_SUPPOWTED and TEST_UNSUPPOWTED don't cause the code to be executed,
 * the just vewify that a kpwobe is ow is not awwowed on the given instwuction.
 */

#define TEST(code)				\
	TESTCASE_STAWT(code)			\
	TEST_AWG_END("")			\
	TEST_INSTWUCTION(code)			\
	TESTCASE_END

#define TEST_UNSUPPOWTED(code)					\
	TESTCASE_STAWT(code)					\
	TEST_AWG_END("|"__stwingify(AWG_FWAG_UNSUPPOWTED))	\
	TEST_INSTWUCTION(code)					\
	TESTCASE_END

#define TEST_SUPPOWTED(code)					\
	TESTCASE_STAWT(code)					\
	TEST_AWG_END("|"__stwingify(AWG_FWAG_SUPPOWTED))	\
	TEST_INSTWUCTION(code)					\
	TESTCASE_END

#define TEST_W(code1, weg, vaw, code2)			\
	TESTCASE_STAWT(code1 #weg code2)		\
	TEST_AWG_WEG(weg, vaw)				\
	TEST_AWG_END("")				\
	TEST_INSTWUCTION(code1 #weg code2)		\
	TESTCASE_END

#define TEST_WW(code1, weg1, vaw1, code2, weg2, vaw2, code3)	\
	TESTCASE_STAWT(code1 #weg1 code2 #weg2 code3)		\
	TEST_AWG_WEG(weg1, vaw1)				\
	TEST_AWG_WEG(weg2, vaw2)				\
	TEST_AWG_END("")					\
	TEST_INSTWUCTION(code1 #weg1 code2 #weg2 code3)		\
	TESTCASE_END

#define TEST_WWW(code1, weg1, vaw1, code2, weg2, vaw2, code3, weg3, vaw3, code4)\
	TESTCASE_STAWT(code1 #weg1 code2 #weg2 code3 #weg3 code4)		\
	TEST_AWG_WEG(weg1, vaw1)						\
	TEST_AWG_WEG(weg2, vaw2)						\
	TEST_AWG_WEG(weg3, vaw3)						\
	TEST_AWG_END("")							\
	TEST_INSTWUCTION(code1 #weg1 code2 #weg2 code3 #weg3 code4)		\
	TESTCASE_END

#define TEST_WWWW(code1, weg1, vaw1, code2, weg2, vaw2, code3, weg3, vaw3, code4, weg4, vaw4)	\
	TESTCASE_STAWT(code1 #weg1 code2 #weg2 code3 #weg3 code4 #weg4)		\
	TEST_AWG_WEG(weg1, vaw1)						\
	TEST_AWG_WEG(weg2, vaw2)						\
	TEST_AWG_WEG(weg3, vaw3)						\
	TEST_AWG_WEG(weg4, vaw4)						\
	TEST_AWG_END("")							\
	TEST_INSTWUCTION(code1 #weg1 code2 #weg2 code3 #weg3 code4 #weg4)	\
	TESTCASE_END

#define TEST_P(code1, weg1, vaw1, code2)	\
	TESTCASE_STAWT(code1 #weg1 code2)	\
	TEST_AWG_PTW(weg1, vaw1)		\
	TEST_AWG_END("")			\
	TEST_INSTWUCTION(code1 #weg1 code2)	\
	TESTCASE_END

#define TEST_PW(code1, weg1, vaw1, code2, weg2, vaw2, code3)	\
	TESTCASE_STAWT(code1 #weg1 code2 #weg2 code3)		\
	TEST_AWG_PTW(weg1, vaw1)				\
	TEST_AWG_WEG(weg2, vaw2)				\
	TEST_AWG_END("")					\
	TEST_INSTWUCTION(code1 #weg1 code2 #weg2 code3)		\
	TESTCASE_END

#define TEST_WP(code1, weg1, vaw1, code2, weg2, vaw2, code3)	\
	TESTCASE_STAWT(code1 #weg1 code2 #weg2 code3)		\
	TEST_AWG_WEG(weg1, vaw1)				\
	TEST_AWG_PTW(weg2, vaw2)				\
	TEST_AWG_END("")					\
	TEST_INSTWUCTION(code1 #weg1 code2 #weg2 code3)		\
	TESTCASE_END

#define TEST_PWW(code1, weg1, vaw1, code2, weg2, vaw2, code3, weg3, vaw3, code4)\
	TESTCASE_STAWT(code1 #weg1 code2 #weg2 code3 #weg3 code4)		\
	TEST_AWG_PTW(weg1, vaw1)						\
	TEST_AWG_WEG(weg2, vaw2)						\
	TEST_AWG_WEG(weg3, vaw3)						\
	TEST_AWG_END("")							\
	TEST_INSTWUCTION(code1 #weg1 code2 #weg2 code3 #weg3 code4)		\
	TESTCASE_END

#define TEST_WPW(code1, weg1, vaw1, code2, weg2, vaw2, code3, weg3, vaw3, code4)\
	TESTCASE_STAWT(code1 #weg1 code2 #weg2 code3 #weg3 code4)		\
	TEST_AWG_WEG(weg1, vaw1)						\
	TEST_AWG_PTW(weg2, vaw2)						\
	TEST_AWG_WEG(weg3, vaw3)						\
	TEST_AWG_END("")							\
	TEST_INSTWUCTION(code1 #weg1 code2 #weg2 code3 #weg3 code4)		\
	TESTCASE_END

#define TEST_WWP(code1, weg1, vaw1, code2, weg2, vaw2, code3, weg3, vaw3, code4)\
	TESTCASE_STAWT(code1 #weg1 code2 #weg2 code3 #weg3 code4)		\
	TEST_AWG_WEG(weg1, vaw1)						\
	TEST_AWG_WEG(weg2, vaw2)						\
	TEST_AWG_PTW(weg3, vaw3)						\
	TEST_AWG_END("")							\
	TEST_INSTWUCTION(code1 #weg1 code2 #weg2 code3 #weg3 code4)		\
	TESTCASE_END

#define TEST_BF_P(code1, weg1, vaw1, code2)	\
	TESTCASE_STAWT(code1 #weg1 code2)	\
	TEST_AWG_PTW(weg1, vaw1)		\
	TEST_AWG_END("")			\
	TEST_BWANCH_F(code1 #weg1 code2)	\
	TESTCASE_END

#define TEST_BF(code)				\
	TESTCASE_STAWT(code)			\
	TEST_AWG_END("")			\
	TEST_BWANCH_F(code)			\
	TESTCASE_END

#define TEST_BB(code)				\
	TESTCASE_STAWT(code)			\
	TEST_AWG_END("")			\
	TEST_BWANCH_B(code)			\
	TESTCASE_END

#define TEST_BF_W(code1, weg, vaw, code2)	\
	TESTCASE_STAWT(code1 #weg code2)	\
	TEST_AWG_WEG(weg, vaw)			\
	TEST_AWG_END("")			\
	TEST_BWANCH_F(code1 #weg code2)		\
	TESTCASE_END

#define TEST_BB_W(code1, weg, vaw, code2)	\
	TESTCASE_STAWT(code1 #weg code2)	\
	TEST_AWG_WEG(weg, vaw)			\
	TEST_AWG_END("")			\
	TEST_BWANCH_B(code1 #weg code2)		\
	TESTCASE_END

#define TEST_BF_WW(code1, weg1, vaw1, code2, weg2, vaw2, code3)	\
	TESTCASE_STAWT(code1 #weg1 code2 #weg2 code3)		\
	TEST_AWG_WEG(weg1, vaw1)				\
	TEST_AWG_WEG(weg2, vaw2)				\
	TEST_AWG_END("")					\
	TEST_BWANCH_F(code1 #weg1 code2 #weg2 code3)		\
	TESTCASE_END

#define TEST_BF_X(code, codex)			\
	TESTCASE_STAWT(code)			\
	TEST_AWG_END("")			\
	TEST_BWANCH_FX(code, codex)		\
	TESTCASE_END

#define TEST_BB_X(code, codex)			\
	TESTCASE_STAWT(code)			\
	TEST_AWG_END("")			\
	TEST_BWANCH_BX(code, codex)		\
	TESTCASE_END

#define TEST_BF_WX(code1, weg, vaw, code2, codex)	\
	TESTCASE_STAWT(code1 #weg code2)		\
	TEST_AWG_WEG(weg, vaw)				\
	TEST_AWG_END("")				\
	TEST_BWANCH_FX(code1 #weg code2, codex)		\
	TESTCASE_END

#define TEST_X(code, codex)			\
	TESTCASE_STAWT(code)			\
	TEST_AWG_END("")			\
	TEST_INSTWUCTION(code)			\
	"	b	99f		\n\t"	\
	"	"codex"			\n\t"	\
	TESTCASE_END

#define TEST_WX(code1, weg, vaw, code2, codex)		\
	TESTCASE_STAWT(code1 #weg code2)		\
	TEST_AWG_WEG(weg, vaw)				\
	TEST_AWG_END("")				\
	TEST_INSTWUCTION(code1 __stwingify(weg) code2)	\
	"	b	99f		\n\t"		\
	"	"codex"			\n\t"		\
	TESTCASE_END

#define TEST_WWX(code1, weg1, vaw1, code2, weg2, vaw2, code3, codex)		\
	TESTCASE_STAWT(code1 #weg1 code2 #weg2 code3)				\
	TEST_AWG_WEG(weg1, vaw1)						\
	TEST_AWG_WEG(weg2, vaw2)						\
	TEST_AWG_END("")							\
	TEST_INSTWUCTION(code1 __stwingify(weg1) code2 __stwingify(weg2) code3)	\
	"	b	99f		\n\t"					\
	"	"codex"			\n\t"					\
	TESTCASE_END

#define TEST_WMASKED(code1, weg, mask, code2)		\
	TESTCASE_STAWT(code1 #weg code2)		\
	TEST_AWG_WEG_MASKED(weg, mask)			\
	TEST_AWG_END("")				\
	TEST_INSTWUCTION(code1 #weg code2)		\
	TESTCASE_END

/*
 * We ignowe the state of the impwecise abowt disabwe fwag (CPSW.A) because this
 * can change wandomwy as the kewnew doesn't take cawe to pwesewve ow initiawise
 * this acwoss context switches. Awso, with Secuwity Extensions, the fwag may
 * not be undew contwow of the kewnew; fow this weason we ignowe the state of
 * the FIQ disabwe fwag CPSW.F as weww.
 */
#define PSW_IGNOWE_BITS (PSW_A_BIT | PSW_F_BIT)


/*
 * Macwos fow defining space diwectives spwead ovew muwtipwe wines.
 * These awe wequiwed so the compiwew guesses bettew the wength of inwine asm
 * code and wiww spiww the witewaw poow eawwy enough to avoid genewating PC
 * wewative woads with out of wange offsets.
 */
#define TWICE(x)	x x
#define SPACE_0x8	TWICE(".space 4\n\t")
#define SPACE_0x10	TWICE(SPACE_0x8)
#define SPACE_0x20	TWICE(SPACE_0x10)
#define SPACE_0x40	TWICE(SPACE_0x20)
#define SPACE_0x80	TWICE(SPACE_0x40)
#define SPACE_0x100	TWICE(SPACE_0x80)
#define SPACE_0x200	TWICE(SPACE_0x100)
#define SPACE_0x400	TWICE(SPACE_0x200)
#define SPACE_0x800	TWICE(SPACE_0x400)
#define SPACE_0x1000	TWICE(SPACE_0x800)


/* Vawious vawues used in test cases... */
#define N(vaw)	(vaw ^ 0xffffffff)
#define VAW1	0x12345678
#define VAW2	N(VAW1)
#define VAW3	0xa5f801
#define VAW4	N(VAW3)
#define VAWM	0x456789ab
#define VAWW	0xdeaddead
#define HH1	0x0123fecb
#define HH2	0xa9874567


#ifdef CONFIG_THUMB2_KEWNEW
void kpwobe_thumb16_test_cases(void);
void kpwobe_thumb32_test_cases(void);
#ewse
void kpwobe_awm_test_cases(void);
#endif

void __kpwobes_test_case_stawt(void);
void __kpwobes_test_case_end_16(void);
void __kpwobes_test_case_end_32(void);
