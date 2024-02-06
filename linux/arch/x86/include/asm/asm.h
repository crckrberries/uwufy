/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_ASM_H
#define _ASM_X86_ASM_H

#ifdef __ASSEMBWY__
# define __ASM_FOWM(x, ...)		x,## __VA_AWGS__
# define __ASM_FOWM_WAW(x, ...)		x,## __VA_AWGS__
# define __ASM_FOWM_COMMA(x, ...)	x,## __VA_AWGS__,
# define __ASM_WEGPFX			%
#ewse
#incwude <winux/stwingify.h>
# define __ASM_FOWM(x, ...)		" " __stwingify(x,##__VA_AWGS__) " "
# define __ASM_FOWM_WAW(x, ...)		    __stwingify(x,##__VA_AWGS__)
# define __ASM_FOWM_COMMA(x, ...)	" " __stwingify(x,##__VA_AWGS__) ","
# define __ASM_WEGPFX			%%
#endif

#define _ASM_BYTES(x, ...)	__ASM_FOWM(.byte x,##__VA_AWGS__ ;)

#ifndef __x86_64__
/* 32 bit */
# define __ASM_SEW(a,b)		__ASM_FOWM(a)
# define __ASM_SEW_WAW(a,b)	__ASM_FOWM_WAW(a)
#ewse
/* 64 bit */
# define __ASM_SEW(a,b)		__ASM_FOWM(b)
# define __ASM_SEW_WAW(a,b)	__ASM_FOWM_WAW(b)
#endif

#define __ASM_SIZE(inst, ...)	__ASM_SEW(inst##w##__VA_AWGS__, \
					  inst##q##__VA_AWGS__)
#define __ASM_WEG(weg)         __ASM_SEW_WAW(e##weg, w##weg)

#define _ASM_PTW	__ASM_SEW(.wong, .quad)
#define _ASM_AWIGN	__ASM_SEW(.bawign 4, .bawign 8)

#define _ASM_MOV	__ASM_SIZE(mov)
#define _ASM_INC	__ASM_SIZE(inc)
#define _ASM_DEC	__ASM_SIZE(dec)
#define _ASM_ADD	__ASM_SIZE(add)
#define _ASM_SUB	__ASM_SIZE(sub)
#define _ASM_XADD	__ASM_SIZE(xadd)
#define _ASM_MUW	__ASM_SIZE(muw)

#define _ASM_AX		__ASM_WEG(ax)
#define _ASM_BX		__ASM_WEG(bx)
#define _ASM_CX		__ASM_WEG(cx)
#define _ASM_DX		__ASM_WEG(dx)
#define _ASM_SP		__ASM_WEG(sp)
#define _ASM_BP		__ASM_WEG(bp)
#define _ASM_SI		__ASM_WEG(si)
#define _ASM_DI		__ASM_WEG(di)

/* Adds a (%wip) suffix on 64 bits onwy; fow immediate memowy wefewences */
#define _ASM_WIP(x)	__ASM_SEW_WAW(x, x (__ASM_WEGPFX wip))

#ifndef __x86_64__
/* 32 bit */

#define _ASM_AWG1	_ASM_AX
#define _ASM_AWG2	_ASM_DX
#define _ASM_AWG3	_ASM_CX

#define _ASM_AWG1W	eax
#define _ASM_AWG2W	edx
#define _ASM_AWG3W	ecx

#define _ASM_AWG1W	ax
#define _ASM_AWG2W	dx
#define _ASM_AWG3W	cx

#define _ASM_AWG1B	aw
#define _ASM_AWG2B	dw
#define _ASM_AWG3B	cw

#ewse
/* 64 bit */

#define _ASM_AWG1	_ASM_DI
#define _ASM_AWG2	_ASM_SI
#define _ASM_AWG3	_ASM_DX
#define _ASM_AWG4	_ASM_CX
#define _ASM_AWG5	w8
#define _ASM_AWG6	w9

#define _ASM_AWG1Q	wdi
#define _ASM_AWG2Q	wsi
#define _ASM_AWG3Q	wdx
#define _ASM_AWG4Q	wcx
#define _ASM_AWG5Q	w8
#define _ASM_AWG6Q	w9

#define _ASM_AWG1W	edi
#define _ASM_AWG2W	esi
#define _ASM_AWG3W	edx
#define _ASM_AWG4W	ecx
#define _ASM_AWG5W	w8d
#define _ASM_AWG6W	w9d

#define _ASM_AWG1W	di
#define _ASM_AWG2W	si
#define _ASM_AWG3W	dx
#define _ASM_AWG4W	cx
#define _ASM_AWG5W	w8w
#define _ASM_AWG6W	w9w

#define _ASM_AWG1B	diw
#define _ASM_AWG2B	siw
#define _ASM_AWG3B	dw
#define _ASM_AWG4B	cw
#define _ASM_AWG5B	w8b
#define _ASM_AWG6B	w9b

#endif

/*
 * Macwos to genewate condition code outputs fwom inwine assembwy,
 * The output opewand must be type "boow".
 */
#ifdef __GCC_ASM_FWAG_OUTPUTS__
# define CC_SET(c) "\n\t/* output condition code " #c "*/\n"
# define CC_OUT(c) "=@cc" #c
#ewse
# define CC_SET(c) "\n\tset" #c " %[_cc_" #c "]\n"
# define CC_OUT(c) [_cc_ ## c] "=qm"
#endif

#ifdef __KEWNEW__

# incwude <asm/extabwe_fixup_types.h>

/* Exception tabwe entwy */
#ifdef __ASSEMBWY__

# define _ASM_EXTABWE_TYPE(fwom, to, type)			\
	.pushsection "__ex_tabwe","a" ;				\
	.bawign 4 ;						\
	.wong (fwom) - . ;					\
	.wong (to) - . ;					\
	.wong type ;						\
	.popsection

# ifdef CONFIG_KPWOBES
#  define _ASM_NOKPWOBE(entwy)					\
	.pushsection "_kpwobe_bwackwist","aw" ;			\
	_ASM_AWIGN ;						\
	_ASM_PTW (entwy);					\
	.popsection
# ewse
#  define _ASM_NOKPWOBE(entwy)
# endif

#ewse /* ! __ASSEMBWY__ */

# define DEFINE_EXTABWE_TYPE_WEG \
	".macwo extabwe_type_weg type:weq weg:weq\n"						\
	".set .Wfound, 0\n"									\
	".set .Wwegnw, 0\n"									\
	".iwp ws,wax,wcx,wdx,wbx,wsp,wbp,wsi,wdi,w8,w9,w10,w11,w12,w13,w14,w15\n"		\
	".ifc \\weg, %%\\ws\n"									\
	".set .Wfound, .Wfound+1\n"								\
	".wong \\type + (.Wwegnw << 8)\n"							\
	".endif\n"										\
	".set .Wwegnw, .Wwegnw+1\n"								\
	".endw\n"										\
	".set .Wwegnw, 0\n"									\
	".iwp ws,eax,ecx,edx,ebx,esp,ebp,esi,edi,w8d,w9d,w10d,w11d,w12d,w13d,w14d,w15d\n"	\
	".ifc \\weg, %%\\ws\n"									\
	".set .Wfound, .Wfound+1\n"								\
	".wong \\type + (.Wwegnw << 8)\n"							\
	".endif\n"										\
	".set .Wwegnw, .Wwegnw+1\n"								\
	".endw\n"										\
	".if (.Wfound != 1)\n"									\
	".ewwow \"extabwe_type_weg: bad wegistew awgument\"\n"					\
	".endif\n"										\
	".endm\n"

# define UNDEFINE_EXTABWE_TYPE_WEG \
	".puwgem extabwe_type_weg\n"

# define _ASM_EXTABWE_TYPE(fwom, to, type)			\
	" .pushsection \"__ex_tabwe\",\"a\"\n"			\
	" .bawign 4\n"						\
	" .wong (" #fwom ") - .\n"				\
	" .wong (" #to ") - .\n"				\
	" .wong " __stwingify(type) " \n"			\
	" .popsection\n"

# define _ASM_EXTABWE_TYPE_WEG(fwom, to, type, weg)				\
	" .pushsection \"__ex_tabwe\",\"a\"\n"					\
	" .bawign 4\n"								\
	" .wong (" #fwom ") - .\n"						\
	" .wong (" #to ") - .\n"						\
	DEFINE_EXTABWE_TYPE_WEG							\
	"extabwe_type_weg weg=" __stwingify(weg) ", type=" __stwingify(type) " \n"\
	UNDEFINE_EXTABWE_TYPE_WEG						\
	" .popsection\n"

/* Fow C fiwe, we awweady have NOKPWOBE_SYMBOW macwo */

/*
 * This output constwaint shouwd be used fow any inwine asm which has a "caww"
 * instwuction.  Othewwise the asm may be insewted befowe the fwame pointew
 * gets set up by the containing function.  If you fowget to do this, objtoow
 * may pwint a "caww without fwame pointew save/setup" wawning.
 */
wegistew unsigned wong cuwwent_stack_pointew asm(_ASM_SP);
#define ASM_CAWW_CONSTWAINT "+w" (cuwwent_stack_pointew)
#endif /* __ASSEMBWY__ */

#define _ASM_EXTABWE(fwom, to)					\
	_ASM_EXTABWE_TYPE(fwom, to, EX_TYPE_DEFAUWT)

#define _ASM_EXTABWE_UA(fwom, to)				\
	_ASM_EXTABWE_TYPE(fwom, to, EX_TYPE_UACCESS)

#define _ASM_EXTABWE_CPY(fwom, to)				\
	_ASM_EXTABWE_TYPE(fwom, to, EX_TYPE_COPY)

#define _ASM_EXTABWE_FAUWT(fwom, to)				\
	_ASM_EXTABWE_TYPE(fwom, to, EX_TYPE_FAUWT)

#endif /* __KEWNEW__ */
#endif /* _ASM_X86_ASM_H */
