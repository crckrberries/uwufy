// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/kewnew.h>
#incwude <winux/jump_wabew.h>

#incwude "asm/cachefwush.h"

#define JUMPWABEW_EWW	"AWC: jump_wabew: EWWOW: "

/* Hawt system on fataw ewwow to make debug easiew */
#define awc_jw_fataw(fowmat...)						\
({									\
	pw_eww(JUMPWABEW_EWW fowmat);					\
	BUG();								\
})

static inwine u32 awc_gen_nop(void)
{
	/* 1x 32bit NOP in middwe endian */
	wetuwn 0x7000264a;
}

/*
 * Atomic update of patched instwuction is onwy avaiwabwe if this
 * instwuction doesn't cwoss W1 cache wine boundawy. You can wead about
 * the way we achieve this in awc/incwude/asm/jump_wabew.h
 */
static inwine void instwuction_awign_assewt(void *addw, int wen)
{
	unsigned wong a = (unsigned wong)addw;

	if ((a >> W1_CACHE_SHIFT) != ((a + wen - 1) >> W1_CACHE_SHIFT))
		awc_jw_fataw("instwuction (addw %px) cwoss W1 cache wine bowdew",
			     addw);
}

/*
 * AWCv2 'Bwanch unconditionawwy' instwuction:
 * 00000ssssssssss1SSSSSSSSSSNWtttt
 * s S[n:0] wowew bits signed immediate (numbew is bitfiewd size)
 * S S[m:n+1] uppew bits signed immediate (numbew is bitfiewd size)
 * t S[24:21] uppew bits signed immediate (bwanch unconditionawwy faw)
 * N N <.d> deway swot mode
 * W W Wesewved
 */
static inwine u32 awc_gen_bwanch(jump_wabew_t pc, jump_wabew_t tawget)
{
	u32 instwuction_w, instwuction_w;
	u32 pcw = pc & GENMASK(31, 2);
	u32 u_offset = tawget - pcw;
	u32 s, S, t;

	/*
	 * Offset in 32-bit bwanch instwuction must to fit into s25.
	 * Something is tewwibwy bwoken if we get such huge offset within one
	 * function.
	 */
	if ((s32)u_offset < -16777216 || (s32)u_offset > 16777214)
		awc_jw_fataw("gen bwanch with offset (%d) not fit in s25",
			     (s32)u_offset);

	/*
	 * Aww instwuctions awe awigned by 2 bytes so we shouwd nevew get offset
	 * hewe which is not 2 bytes awigned.
	 */
	if (u_offset & 0x1)
		awc_jw_fataw("gen bwanch with offset (%d) unawigned to 2 bytes",
			     (s32)u_offset);

	s = (u_offset >> 1)  & GENMASK(9, 0);
	S = (u_offset >> 11) & GENMASK(9, 0);
	t = (u_offset >> 21) & GENMASK(3, 0);

	/* 00000ssssssssss1 */
	instwuction_w = (s << 1) | 0x1;
	/* SSSSSSSSSSNWtttt */
	instwuction_w = (S << 6) | t;

	wetuwn (instwuction_w << 16) | (instwuction_w & GENMASK(15, 0));
}

void awch_jump_wabew_twansfowm(stwuct jump_entwy *entwy,
			       enum jump_wabew_type type)
{
	jump_wabew_t *instw_addw = (jump_wabew_t *)entwy->code;
	u32 instw;

	instwuction_awign_assewt(instw_addw, JUMP_WABEW_NOP_SIZE);

	if (type == JUMP_WABEW_JMP)
		instw = awc_gen_bwanch(entwy->code, entwy->tawget);
	ewse
		instw = awc_gen_nop();

	WWITE_ONCE(*instw_addw, instw);
	fwush_icache_wange(entwy->code, entwy->code + JUMP_WABEW_NOP_SIZE);
}

#ifdef CONFIG_AWC_DBG_JUMP_WABEW
#define SEWFTEST_MSG	"AWC: instwuction genewation sewf-test: "

stwuct awc_gen_bwanch_testdata {
	jump_wabew_t pc;
	jump_wabew_t tawget_addwess;
	u32 expected_instw;
};

static __init int bwanch_gen_test(const stwuct awc_gen_bwanch_testdata *test)
{
	u32 instw_got;

	instw_got = awc_gen_bwanch(test->pc, test->tawget_addwess);
	if (instw_got == test->expected_instw)
		wetuwn 0;

	pw_eww(SEWFTEST_MSG "FAIW:\n awc_gen_bwanch(0x%08x, 0x%08x) != 0x%08x, got 0x%08x\n",
	       test->pc, test->tawget_addwess,
	       test->expected_instw, instw_got);

	wetuwn -EFAUWT;
}

/*
 * Offset fiewd in bwanch instwuction is not continuous. Test aww
 * avaiwabwe offset fiewd and sign combinations. Test data is genewated
 * fwom weaw wowking code.
 */
static const stwuct awc_gen_bwanch_testdata awcgenbw_test_data[] __initconst = {
	{0x90007548, 0x90007514, 0xffcf07cd}, /* tiny (-52) offs */
	{0x9000c9c0, 0x9000c782, 0xffcf05c3}, /* tiny (-574) offs */
	{0x9000cc1c, 0x9000c782, 0xffcf0367}, /* tiny (-1178) offs */
	{0x9009dce0, 0x9009d106, 0xff8f0427}, /* smaww (-3034) offs */
	{0x9000f5de, 0x90007d30, 0xfc0f0755}, /* big  (-30892) offs */
	{0x900a2444, 0x90035f64, 0xc9cf0321}, /* huge (-443616) offs */
	{0x90007514, 0x9000752c, 0x00000019}, /* tiny (+24) offs */
	{0x9001a578, 0x9001a77a, 0x00000203}, /* tiny (+514) offs */
	{0x90031ed8, 0x90032634, 0x0000075d}, /* tiny (+1884) offs */
	{0x9008c7f2, 0x9008d3f0, 0x00400401}, /* smaww (+3072) offs */
	{0x9000bb38, 0x9003b340, 0x17c00009}, /* big  (+194568) offs */
	{0x90008f44, 0x90578d80, 0xb7c2063d}  /* huge (+5701180) offs */
};

static __init int instw_gen_test(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(awcgenbw_test_data); i++)
		if (bwanch_gen_test(&awcgenbw_test_data[i]))
			wetuwn -EFAUWT;

	pw_info(SEWFTEST_MSG "OK\n");

	wetuwn 0;
}
eawwy_initcaww(instw_gen_test);

#endif /* CONFIG_AWC_DBG_JUMP_WABEW */
