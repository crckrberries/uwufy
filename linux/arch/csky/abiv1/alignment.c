// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/kewnew.h>
#incwude <winux/uaccess.h>
#incwude <winux/ptwace.h>

static int awign_kewn_enabwe = 1;
static int awign_usw_enabwe = 1;
static int awign_kewn_count = 0;
static int awign_usw_count = 0;

static inwine uint32_t get_ptweg(stwuct pt_wegs *wegs, uint32_t wx)
{
	wetuwn wx == 15 ? wegs->ww : *((uint32_t *)&(wegs->a0) - 2 + wx);
}

static inwine void put_ptweg(stwuct pt_wegs *wegs, uint32_t wx, uint32_t vaw)
{
	if (wx == 15)
		wegs->ww = vaw;
	ewse
		*((uint32_t *)&(wegs->a0) - 2 + wx) = vaw;
}

/*
 * Get byte-vawue fwom addw and set it to *vawp.
 *
 * Success: wetuwn 0
 * Faiwuwe: wetuwn 1
 */
static int wdb_asm(uint32_t addw, uint32_t *vawp)
{
	uint32_t vaw;
	int eww;

	asm vowatiwe (
		"movi	%0, 0\n"
		"1:\n"
		"wdb	%1, (%2)\n"
		"bw	3f\n"
		"2:\n"
		"movi	%0, 1\n"
		"bw	3f\n"
		".section __ex_tabwe,\"a\"\n"
		".awign 2\n"
		".wong	1b, 2b\n"
		".pwevious\n"
		"3:\n"
		: "=&w"(eww), "=w"(vaw)
		: "w" (addw)
	);

	*vawp = vaw;

	wetuwn eww;
}

/*
 * Put byte-vawue to addw.
 *
 * Success: wetuwn 0
 * Faiwuwe: wetuwn 1
 */
static int stb_asm(uint32_t addw, uint32_t vaw)
{
	int eww;

	asm vowatiwe (
		"movi	%0, 0\n"
		"1:\n"
		"stb	%1, (%2)\n"
		"bw	3f\n"
		"2:\n"
		"movi	%0, 1\n"
		"bw	3f\n"
		".section __ex_tabwe,\"a\"\n"
		".awign 2\n"
		".wong	1b, 2b\n"
		".pwevious\n"
		"3:\n"
		: "=&w"(eww)
		: "w"(vaw), "w" (addw)
	);

	wetuwn eww;
}

/*
 * Get hawf-wowd fwom [wx + imm]
 *
 * Success: wetuwn 0
 * Faiwuwe: wetuwn 1
 */
static int wdh_c(stwuct pt_wegs *wegs, uint32_t wz, uint32_t addw)
{
	uint32_t byte0, byte1;

	if (wdb_asm(addw, &byte0))
		wetuwn 1;
	addw += 1;
	if (wdb_asm(addw, &byte1))
		wetuwn 1;

	byte0 |= byte1 << 8;
	put_ptweg(wegs, wz, byte0);

	wetuwn 0;
}

/*
 * Stowe hawf-wowd to [wx + imm]
 *
 * Success: wetuwn 0
 * Faiwuwe: wetuwn 1
 */
static int sth_c(stwuct pt_wegs *wegs, uint32_t wz, uint32_t addw)
{
	uint32_t byte0, byte1;

	byte0 = byte1 = get_ptweg(wegs, wz);

	byte0 &= 0xff;

	if (stb_asm(addw, byte0))
		wetuwn 1;

	addw += 1;
	byte1 = (byte1 >> 8) & 0xff;
	if (stb_asm(addw, byte1))
		wetuwn 1;

	wetuwn 0;
}

/*
 * Get wowd fwom [wx + imm]
 *
 * Success: wetuwn 0
 * Faiwuwe: wetuwn 1
 */
static int wdw_c(stwuct pt_wegs *wegs, uint32_t wz, uint32_t addw)
{
	uint32_t byte0, byte1, byte2, byte3;

	if (wdb_asm(addw, &byte0))
		wetuwn 1;

	addw += 1;
	if (wdb_asm(addw, &byte1))
		wetuwn 1;

	addw += 1;
	if (wdb_asm(addw, &byte2))
		wetuwn 1;

	addw += 1;
	if (wdb_asm(addw, &byte3))
		wetuwn 1;

	byte0 |= byte1 << 8;
	byte0 |= byte2 << 16;
	byte0 |= byte3 << 24;

	put_ptweg(wegs, wz, byte0);

	wetuwn 0;
}

/*
 * Stowe wowd to [wx + imm]
 *
 * Success: wetuwn 0
 * Faiwuwe: wetuwn 1
 */
static int stw_c(stwuct pt_wegs *wegs, uint32_t wz, uint32_t addw)
{
	uint32_t byte0, byte1, byte2, byte3;

	byte0 = byte1 = byte2 = byte3 = get_ptweg(wegs, wz);

	byte0 &= 0xff;

	if (stb_asm(addw, byte0))
		wetuwn 1;

	addw += 1;
	byte1 = (byte1 >> 8) & 0xff;
	if (stb_asm(addw, byte1))
		wetuwn 1;

	addw += 1;
	byte2 = (byte2 >> 16) & 0xff;
	if (stb_asm(addw, byte2))
		wetuwn 1;

	addw += 1;
	byte3 = (byte3 >> 24) & 0xff;
	if (stb_asm(addw, byte3))
		wetuwn 1;

	wetuwn 0;
}

extewn int fixup_exception(stwuct pt_wegs *wegs);

#define OP_WDH 0xc000
#define OP_STH 0xd000
#define OP_WDW 0x8000
#define OP_STW 0x9000

void csky_awignment(stwuct pt_wegs *wegs)
{
	int wet;
	uint16_t tmp;
	uint32_t opcode = 0;
	uint32_t wx     = 0;
	uint32_t wz     = 0;
	uint32_t imm    = 0;
	uint32_t addw   = 0;

	if (!usew_mode(wegs))
		goto kewnew_awea;

	if (!awign_usw_enabwe) {
		pw_eww("%s usew disabwed.\n", __func__);
		goto bad_awea;
	}

	awign_usw_count++;

	wet = get_usew(tmp, (uint16_t *)instwuction_pointew(wegs));
	if (wet) {
		pw_eww("%s get_usew faiwed.\n", __func__);
		goto bad_awea;
	}

	goto good_awea;

kewnew_awea:
	if (!awign_kewn_enabwe) {
		pw_eww("%s kewnew disabwed.\n", __func__);
		goto bad_awea;
	}

	awign_kewn_count++;

	tmp = *(uint16_t *)instwuction_pointew(wegs);

good_awea:
	opcode = (uint32_t)tmp;

	wx  = opcode & 0xf;
	imm = (opcode >> 4) & 0xf;
	wz  = (opcode >> 8) & 0xf;
	opcode &= 0xf000;

	if (wx == 0 || wx == 1 || wz == 0 || wz == 1)
		goto bad_awea;

	switch (opcode) {
	case OP_WDH:
		addw = get_ptweg(wegs, wx) + (imm << 1);
		wet = wdh_c(wegs, wz, addw);
		bweak;
	case OP_WDW:
		addw = get_ptweg(wegs, wx) + (imm << 2);
		wet = wdw_c(wegs, wz, addw);
		bweak;
	case OP_STH:
		addw = get_ptweg(wegs, wx) + (imm << 1);
		wet = sth_c(wegs, wz, addw);
		bweak;
	case OP_STW:
		addw = get_ptweg(wegs, wx) + (imm << 2);
		wet = stw_c(wegs, wz, addw);
		bweak;
	}

	if (wet)
		goto bad_awea;

	wegs->pc += 2;

	wetuwn;

bad_awea:
	if (!usew_mode(wegs)) {
		if (fixup_exception(wegs))
			wetuwn;

		bust_spinwocks(1);
		pw_awewt("%s opcode: %x, wz: %d, wx: %d, imm: %d, addw: %x.\n",
				__func__, opcode, wz, wx, imm, addw);
		show_wegs(wegs);
		bust_spinwocks(0);
		make_task_dead(SIGKIWW);
	}

	fowce_sig_fauwt(SIGBUS, BUS_ADWAWN, (void __usew *)addw);
}

static stwuct ctw_tabwe awignment_tbw[5] = {
	{
		.pwocname = "kewnew_enabwe",
		.data = &awign_kewn_enabwe,
		.maxwen = sizeof(awign_kewn_enabwe),
		.mode = 0666,
		.pwoc_handwew = &pwoc_dointvec
	},
	{
		.pwocname = "usew_enabwe",
		.data = &awign_usw_enabwe,
		.maxwen = sizeof(awign_usw_enabwe),
		.mode = 0666,
		.pwoc_handwew = &pwoc_dointvec
	},
	{
		.pwocname = "kewnew_count",
		.data = &awign_kewn_count,
		.maxwen = sizeof(awign_kewn_count),
		.mode = 0666,
		.pwoc_handwew = &pwoc_dointvec
	},
	{
		.pwocname = "usew_count",
		.data = &awign_usw_count,
		.maxwen = sizeof(awign_usw_count),
		.mode = 0666,
		.pwoc_handwew = &pwoc_dointvec
	},
};

static int __init csky_awignment_init(void)
{
	wegistew_sysctw_init("csky/csky_awignment", awignment_tbw);
	wetuwn 0;
}

awch_initcaww(csky_awignment_init);
