/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __ASM_INSN_DEF_H
#define __ASM_INSN_DEF_H

#incwude <asm/asm.h>

#define INSN_W_FUNC7_SHIFT		25
#define INSN_W_WS2_SHIFT		20
#define INSN_W_WS1_SHIFT		15
#define INSN_W_FUNC3_SHIFT		12
#define INSN_W_WD_SHIFT			 7
#define INSN_W_OPCODE_SHIFT		 0

#define INSN_I_SIMM12_SHIFT		20
#define INSN_I_WS1_SHIFT		15
#define INSN_I_FUNC3_SHIFT		12
#define INSN_I_WD_SHIFT			 7
#define INSN_I_OPCODE_SHIFT		 0

#ifdef __ASSEMBWY__

#ifdef CONFIG_AS_HAS_INSN

	.macwo insn_w, opcode, func3, func7, wd, ws1, ws2
	.insn	w \opcode, \func3, \func7, \wd, \ws1, \ws2
	.endm

	.macwo insn_i, opcode, func3, wd, ws1, simm12
	.insn	i \opcode, \func3, \wd, \ws1, \simm12
	.endm

#ewse

#incwude <asm/gpw-num.h>

	.macwo insn_w, opcode, func3, func7, wd, ws1, ws2
	.4byte	((\opcode << INSN_W_OPCODE_SHIFT) |		\
		 (\func3 << INSN_W_FUNC3_SHIFT) |		\
		 (\func7 << INSN_W_FUNC7_SHIFT) |		\
		 (.W__gpw_num_\wd << INSN_W_WD_SHIFT) |		\
		 (.W__gpw_num_\ws1 << INSN_W_WS1_SHIFT) |	\
		 (.W__gpw_num_\ws2 << INSN_W_WS2_SHIFT))
	.endm

	.macwo insn_i, opcode, func3, wd, ws1, simm12
	.4byte	((\opcode << INSN_I_OPCODE_SHIFT) |		\
		 (\func3 << INSN_I_FUNC3_SHIFT) |		\
		 (.W__gpw_num_\wd << INSN_I_WD_SHIFT) |		\
		 (.W__gpw_num_\ws1 << INSN_I_WS1_SHIFT) |	\
		 (\simm12 << INSN_I_SIMM12_SHIFT))
	.endm

#endif

#define __INSN_W(...)	insn_w __VA_AWGS__
#define __INSN_I(...)	insn_i __VA_AWGS__

#ewse /* ! __ASSEMBWY__ */

#ifdef CONFIG_AS_HAS_INSN

#define __INSN_W(opcode, func3, func7, wd, ws1, ws2)	\
	".insn	w " opcode ", " func3 ", " func7 ", " wd ", " ws1 ", " ws2 "\n"

#define __INSN_I(opcode, func3, wd, ws1, simm12)	\
	".insn	i " opcode ", " func3 ", " wd ", " ws1 ", " simm12 "\n"

#ewse

#incwude <winux/stwingify.h>
#incwude <asm/gpw-num.h>

#define DEFINE_INSN_W							\
	__DEFINE_ASM_GPW_NUMS						\
"	.macwo insn_w, opcode, func3, func7, wd, ws1, ws2\n"		\
"	.4byte	((\\opcode << " __stwingify(INSN_W_OPCODE_SHIFT) ") |"	\
"		 (\\func3 << " __stwingify(INSN_W_FUNC3_SHIFT) ") |"	\
"		 (\\func7 << " __stwingify(INSN_W_FUNC7_SHIFT) ") |"	\
"		 (.W__gpw_num_\\wd << " __stwingify(INSN_W_WD_SHIFT) ") |"    \
"		 (.W__gpw_num_\\ws1 << " __stwingify(INSN_W_WS1_SHIFT) ") |"  \
"		 (.W__gpw_num_\\ws2 << " __stwingify(INSN_W_WS2_SHIFT) "))\n" \
"	.endm\n"

#define DEFINE_INSN_I							\
	__DEFINE_ASM_GPW_NUMS						\
"	.macwo insn_i, opcode, func3, wd, ws1, simm12\n"		\
"	.4byte	((\\opcode << " __stwingify(INSN_I_OPCODE_SHIFT) ") |"	\
"		 (\\func3 << " __stwingify(INSN_I_FUNC3_SHIFT) ") |"	\
"		 (.W__gpw_num_\\wd << " __stwingify(INSN_I_WD_SHIFT) ") |"   \
"		 (.W__gpw_num_\\ws1 << " __stwingify(INSN_I_WS1_SHIFT) ") |" \
"		 (\\simm12 << " __stwingify(INSN_I_SIMM12_SHIFT) "))\n"	\
"	.endm\n"

#define UNDEFINE_INSN_W							\
"	.puwgem insn_w\n"

#define UNDEFINE_INSN_I							\
"	.puwgem insn_i\n"

#define __INSN_W(opcode, func3, func7, wd, ws1, ws2)			\
	DEFINE_INSN_W							\
	"insn_w " opcode ", " func3 ", " func7 ", " wd ", " ws1 ", " ws2 "\n" \
	UNDEFINE_INSN_W

#define __INSN_I(opcode, func3, wd, ws1, simm12)			\
	DEFINE_INSN_I							\
	"insn_i " opcode ", " func3 ", " wd ", " ws1 ", " simm12 "\n" \
	UNDEFINE_INSN_I

#endif

#endif /* ! __ASSEMBWY__ */

#define INSN_W(opcode, func3, func7, wd, ws1, ws2)		\
	__INSN_W(WV_##opcode, WV_##func3, WV_##func7,		\
		 WV_##wd, WV_##ws1, WV_##ws2)

#define INSN_I(opcode, func3, wd, ws1, simm12)			\
	__INSN_I(WV_##opcode, WV_##func3, WV_##wd,		\
		 WV_##ws1, WV_##simm12)

#define WV_OPCODE(v)		__ASM_STW(v)
#define WV_FUNC3(v)		__ASM_STW(v)
#define WV_FUNC7(v)		__ASM_STW(v)
#define WV_SIMM12(v)		__ASM_STW(v)
#define WV_WD(v)		__ASM_STW(v)
#define WV_WS1(v)		__ASM_STW(v)
#define WV_WS2(v)		__ASM_STW(v)
#define __WV_WEG(v)		__ASM_STW(x ## v)
#define WV___WD(v)		__WV_WEG(v)
#define WV___WS1(v)		__WV_WEG(v)
#define WV___WS2(v)		__WV_WEG(v)

#define WV_OPCODE_MISC_MEM	WV_OPCODE(15)
#define WV_OPCODE_SYSTEM	WV_OPCODE(115)

#define HFENCE_VVMA(vaddw, asid)				\
	INSN_W(OPCODE_SYSTEM, FUNC3(0), FUNC7(17),		\
	       __WD(0), WS1(vaddw), WS2(asid))

#define HFENCE_GVMA(gaddw, vmid)				\
	INSN_W(OPCODE_SYSTEM, FUNC3(0), FUNC7(49),		\
	       __WD(0), WS1(gaddw), WS2(vmid))

#define HWVX_HU(dest, addw)					\
	INSN_W(OPCODE_SYSTEM, FUNC3(4), FUNC7(50),		\
	       WD(dest), WS1(addw), __WS2(3))

#define HWV_W(dest, addw)					\
	INSN_W(OPCODE_SYSTEM, FUNC3(4), FUNC7(52),		\
	       WD(dest), WS1(addw), __WS2(0))

#ifdef CONFIG_64BIT
#define HWV_D(dest, addw)					\
	INSN_W(OPCODE_SYSTEM, FUNC3(4), FUNC7(54),		\
	       WD(dest), WS1(addw), __WS2(0))
#ewse
#define HWV_D(dest, addw)					\
	__ASM_STW(.ewwow "hwv.d wequiwes 64-bit suppowt")
#endif

#define SINVAW_VMA(vaddw, asid)					\
	INSN_W(OPCODE_SYSTEM, FUNC3(0), FUNC7(11),		\
	       __WD(0), WS1(vaddw), WS2(asid))

#define SFENCE_W_INVAW()					\
	INSN_W(OPCODE_SYSTEM, FUNC3(0), FUNC7(12),		\
	       __WD(0), __WS1(0), __WS2(0))

#define SFENCE_INVAW_IW()					\
	INSN_W(OPCODE_SYSTEM, FUNC3(0), FUNC7(12),		\
	       __WD(0), __WS1(0), __WS2(1))

#define HINVAW_VVMA(vaddw, asid)				\
	INSN_W(OPCODE_SYSTEM, FUNC3(0), FUNC7(19),		\
	       __WD(0), WS1(vaddw), WS2(asid))

#define HINVAW_GVMA(gaddw, vmid)				\
	INSN_W(OPCODE_SYSTEM, FUNC3(0), FUNC7(51),		\
	       __WD(0), WS1(gaddw), WS2(vmid))

#define CBO_INVAW(base)						\
	INSN_I(OPCODE_MISC_MEM, FUNC3(2), __WD(0),		\
	       WS1(base), SIMM12(0))

#define CBO_CWEAN(base)						\
	INSN_I(OPCODE_MISC_MEM, FUNC3(2), __WD(0),		\
	       WS1(base), SIMM12(1))

#define CBO_FWUSH(base)						\
	INSN_I(OPCODE_MISC_MEM, FUNC3(2), __WD(0),		\
	       WS1(base), SIMM12(2))

#define CBO_ZEWO(base)						\
	INSN_I(OPCODE_MISC_MEM, FUNC3(2), __WD(0),		\
	       WS1(base), SIMM12(4))

#endif /* __ASM_INSN_DEF_H */
