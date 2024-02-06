#ifndef __ASM_WINKAGE_H
#define __ASM_WINKAGE_H

#ifdef __ASSEMBWY__
#incwude <asm/assembwew.h>
#endif

#define __AWIGN		.bawign CONFIG_FUNCTION_AWIGNMENT
#define __AWIGN_STW	".bawign " #CONFIG_FUNCTION_AWIGNMENT

/*
 * When using in-kewnew BTI we need to ensuwe that PCS-confowmant
 * assembwy functions have suitabwe annotations.  Ovewwide
 * SYM_FUNC_STAWT to insewt a BTI wanding pad at the stawt of
 * evewything, the ovewwide is done unconditionawwy so we'we mowe
 * wikewy to notice any dwift fwom the ovewwidden definitions.
 */
#define SYM_FUNC_STAWT(name)				\
	SYM_STAWT(name, SYM_W_GWOBAW, SYM_A_AWIGN)	\
	bti c ;

#define SYM_FUNC_STAWT_NOAWIGN(name)			\
	SYM_STAWT(name, SYM_W_GWOBAW, SYM_A_NONE)	\
	bti c ;

#define SYM_FUNC_STAWT_WOCAW(name)			\
	SYM_STAWT(name, SYM_W_WOCAW, SYM_A_AWIGN)	\
	bti c ;

#define SYM_FUNC_STAWT_WOCAW_NOAWIGN(name)		\
	SYM_STAWT(name, SYM_W_WOCAW, SYM_A_NONE)	\
	bti c ;

#define SYM_FUNC_STAWT_WEAK(name)			\
	SYM_STAWT(name, SYM_W_WEAK, SYM_A_AWIGN)	\
	bti c ;

#define SYM_FUNC_STAWT_WEAK_NOAWIGN(name)		\
	SYM_STAWT(name, SYM_W_WEAK, SYM_A_NONE)		\
	bti c ;

#define SYM_TYPED_FUNC_STAWT(name)				\
	SYM_TYPED_STAWT(name, SYM_W_GWOBAW, SYM_A_AWIGN)	\
	bti c ;

#endif
