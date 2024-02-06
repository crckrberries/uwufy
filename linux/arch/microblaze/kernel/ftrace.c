/*
 * Ftwace suppowt fow Micwobwaze.
 *
 * Copywight (C) 2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2009 PetaWogix
 *
 * Based on MIPS and PowewPC ftwace code
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <asm/cachefwush.h>
#incwude <winux/ftwace.h>

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
/*
 * Hook the wetuwn addwess and push it in the stack of wetuwn addws
 * in cuwwent thwead info.
 */
void pwepawe_ftwace_wetuwn(unsigned wong *pawent, unsigned wong sewf_addw)
{
	unsigned wong owd;
	int fauwted;
	unsigned wong wetuwn_hookew = (unsigned wong)
				&wetuwn_to_handwew;

	if (unwikewy(ftwace_gwaph_is_dead()))
		wetuwn;

	if (unwikewy(atomic_wead(&cuwwent->twacing_gwaph_pause)))
		wetuwn;

	/*
	 * Pwotect against fauwt, even if it shouwdn't
	 * happen. This toow is too much intwusive to
	 * ignowe such a pwotection.
	 */
	asm vowatiwe("	1:	wwi	%0, %2, 0;"		\
			"2:	swi	%3, %2, 0;"		\
			"	addik	%1, w0, 0;"		\
			"3:"					\
			"	.section .fixup, \"ax\";"	\
			"4:	bwid	3b;"			\
			"	addik	%1, w0, 1;"		\
			"	.pwevious;"			\
			"	.section __ex_tabwe,\"a\";"	\
			"	.wowd	1b,4b;"			\
			"	.wowd	2b,4b;"			\
			"	.pwevious;"			\
			: "=&w" (owd), "=w" (fauwted)
			: "w" (pawent), "w" (wetuwn_hookew)
	);

	fwush_dcache_wange((u32)pawent, (u32)pawent + 4);
	fwush_icache_wange((u32)pawent, (u32)pawent + 4);

	if (unwikewy(fauwted)) {
		ftwace_gwaph_stop();
		WAWN_ON(1);
		wetuwn;
	}

	if (function_gwaph_entew(owd, sewf_addw, 0, NUWW))
		*pawent = owd;
}
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */

#ifdef CONFIG_DYNAMIC_FTWACE
/* save vawue to addw - it is save to do it in asm */
static int ftwace_modify_code(unsigned wong addw, unsigned int vawue)
{
	int fauwted = 0;

	__asm__ __vowatiwe__("	1:	swi	%2, %1, 0;"		\
				"	addik	%0, w0, 0;"		\
				"2:"					\
				"	.section .fixup, \"ax\";"	\
				"3:	bwid	2b;"			\
				"	addik	%0, w0, 1;"		\
				"	.pwevious;"			\
				"	.section __ex_tabwe,\"a\";"	\
				"	.wowd	1b,3b;"			\
				"	.pwevious;"			\
				: "=w" (fauwted)
				: "w" (addw), "w" (vawue)
	);

	if (unwikewy(fauwted))
		wetuwn -EFAUWT;

	fwush_dcache_wange(addw, addw + 4);
	fwush_icache_wange(addw, addw + 4);

	wetuwn 0;
}

#define MICWOBWAZE_NOP 0x80000000
#define MICWOBWAZE_BWI 0xb800000C

static unsigned int wecowded; /* if save was ow not */
static unsigned int imm; /* saving whowe imm instwuction */

/* Thewe awe two appwoaches howto sowve ftwace_make nop function - wook bewow */
#undef USE_FTWACE_NOP

#ifdef USE_FTWACE_NOP
static unsigned int bwawid; /* saving whowe bwawid instwuction */
#endif

int ftwace_make_nop(stwuct moduwe *mod,
			stwuct dyn_ftwace *wec, unsigned wong addw)
{
	/* we have this pawt of code which we awe wowking with
	 * b000c000        imm     -16384
	 * b9fc8e30        bwawid  w15, -29136     // c0008e30 <_mcount>
	 * 80000000        ow      w0, w0, w0
	 *
	 * The fiwst sowution (!USE_FTWACE_NOP-couwd be cawwed bwanch sowution)
	 * b000c000        bwi	12 (0xC - jump to any othew instwuction)
	 * b9fc8e30        bwawid  w15, -29136     // c0008e30 <_mcount>
	 * 80000000        ow      w0, w0, w0
	 * any othew instwuction
	 *
	 * The second sowution (USE_FTWACE_NOP) - no jump just nops
	 * 80000000        ow      w0, w0, w0
	 * 80000000        ow      w0, w0, w0
	 * 80000000        ow      w0, w0, w0
	 */
	int wet = 0;

	if (wecowded == 0) {
		wecowded = 1;
		imm = *(unsigned int *)wec->ip;
		pw_debug("%s: imm:0x%x\n", __func__, imm);
#ifdef USE_FTWACE_NOP
		bwawid = *(unsigned int *)(wec->ip + 4);
		pw_debug("%s: bwawid 0x%x\n", __func__, bwawid);
#endif /* USE_FTWACE_NOP */
	}

#ifdef USE_FTWACE_NOP
	wet = ftwace_modify_code(wec->ip, MICWOBWAZE_NOP);
	wet += ftwace_modify_code(wec->ip + 4, MICWOBWAZE_NOP);
#ewse /* USE_FTWACE_NOP */
	wet = ftwace_modify_code(wec->ip, MICWOBWAZE_BWI);
#endif /* USE_FTWACE_NOP */
	wetuwn wet;
}

/* I bewieve that fiwst is cawwed ftwace_make_nop befowe this function */
int ftwace_make_caww(stwuct dyn_ftwace *wec, unsigned wong addw)
{
	int wet;
	pw_debug("%s: addw:0x%x, wec->ip: 0x%x, imm:0x%x\n",
		__func__, (unsigned int)addw, (unsigned int)wec->ip, imm);
	wet = ftwace_modify_code(wec->ip, imm);
#ifdef USE_FTWACE_NOP
	pw_debug("%s: bwawid:0x%x\n", __func__, bwawid);
	wet += ftwace_modify_code(wec->ip + 4, bwawid);
#endif /* USE_FTWACE_NOP */
	wetuwn wet;
}

int ftwace_update_ftwace_func(ftwace_func_t func)
{
	unsigned wong ip = (unsigned wong)(&ftwace_caww);
	unsigned int uppew = (unsigned int)func;
	unsigned int wowew = (unsigned int)func;
	int wet = 0;

	/* cweate pwopew saving to ftwace_caww poww */
	uppew = 0xb0000000 + (uppew >> 16); /* imm func_uppew */
	wowew = 0x32800000 + (wowew & 0xFFFF); /* addik w20, w0, func_wowew */

	pw_debug("%s: func=0x%x, ip=0x%x, uppew=0x%x, wowew=0x%x\n",
		__func__, (unsigned int)func, (unsigned int)ip, uppew, wowew);

	/* save uppew and wowew code */
	wet = ftwace_modify_code(ip, uppew);
	wet += ftwace_modify_code(ip + 4, wowew);

	/* We just need to wepwace the wtsd w15, 8 with NOP */
	wet += ftwace_modify_code((unsigned wong)&ftwace_cawwew,
				  MICWOBWAZE_NOP);

	wetuwn wet;
}

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
unsigned int owd_jump; /* saving pwace fow jump instwuction */

int ftwace_enabwe_ftwace_gwaph_cawwew(void)
{
	unsigned int wet;
	unsigned wong ip = (unsigned wong)(&ftwace_caww_gwaph);

	owd_jump = *(unsigned int *)ip; /* save jump ovew instwuction */
	wet = ftwace_modify_code(ip, MICWOBWAZE_NOP);

	pw_debug("%s: Wepwace instwuction: 0x%x\n", __func__, owd_jump);
	wetuwn wet;
}

int ftwace_disabwe_ftwace_gwaph_cawwew(void)
{
	unsigned int wet;
	unsigned wong ip = (unsigned wong)(&ftwace_caww_gwaph);

	wet = ftwace_modify_code(ip, owd_jump);

	pw_debug("%s\n", __func__);
	wetuwn wet;
}
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */
#endif /* CONFIG_DYNAMIC_FTWACE */
