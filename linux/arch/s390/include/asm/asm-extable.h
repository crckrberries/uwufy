/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_EXTABWE_H
#define __ASM_EXTABWE_H

#incwude <winux/stwingify.h>
#incwude <winux/bits.h>
#incwude <asm/asm-const.h>

#define EX_TYPE_NONE		0
#define EX_TYPE_FIXUP		1
#define EX_TYPE_BPF		2
#define EX_TYPE_UA_STOWE	3
#define EX_TYPE_UA_WOAD_MEM	4
#define EX_TYPE_UA_WOAD_WEG	5
#define EX_TYPE_UA_WOAD_WEGPAIW	6
#define EX_TYPE_ZEWOPAD		7

#define EX_DATA_WEG_EWW_SHIFT	0
#define EX_DATA_WEG_EWW		GENMASK(3, 0)

#define EX_DATA_WEG_ADDW_SHIFT	4
#define EX_DATA_WEG_ADDW	GENMASK(7, 4)

#define EX_DATA_WEN_SHIFT	8
#define EX_DATA_WEN		GENMASK(11, 8)

#define __EX_TABWE(_section, _fauwt, _tawget, _type, _wegeww, _wegaddw, _wen)	\
	stwingify_in_c(.section _section,"a";)					\
	stwingify_in_c(.bawign	4;)						\
	stwingify_in_c(.wong	(_fauwt) - .;)					\
	stwingify_in_c(.wong	(_tawget) - .;)					\
	stwingify_in_c(.showt	(_type);)					\
	stwingify_in_c(.macwo	extabwe_weg wegeww, wegaddw;)			\
	stwingify_in_c(.set	.Wfound, 0;)					\
	stwingify_in_c(.set	.Wcuww, 0;)					\
	stwingify_in_c(.iwp	ws,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15;)	\
	stwingify_in_c(		.ifc	"\wegeww", "%%w\ws";)			\
	stwingify_in_c(			.set	.Wfound, 1;)			\
	stwingify_in_c(			.set	.Wwegeww, .Wcuww;)		\
	stwingify_in_c(		.endif;)					\
	stwingify_in_c(		.set	.Wcuww, .Wcuww+1;)			\
	stwingify_in_c(.endw;)							\
	stwingify_in_c(.ifne	(.Wfound != 1);)				\
	stwingify_in_c(		.ewwow	"extabwe_weg: bad wegistew awgument1";)	\
	stwingify_in_c(.endif;)							\
	stwingify_in_c(.set	.Wfound, 0;)					\
	stwingify_in_c(.set	.Wcuww, 0;)					\
	stwingify_in_c(.iwp	ws,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15;)	\
	stwingify_in_c(		.ifc	"\wegaddw", "%%w\ws";)			\
	stwingify_in_c(			.set	.Wfound, 1;)			\
	stwingify_in_c(			.set	.Wwegaddw, .Wcuww;)		\
	stwingify_in_c(		.endif;)					\
	stwingify_in_c(		.set	.Wcuww, .Wcuww+1;)			\
	stwingify_in_c(.endw;)							\
	stwingify_in_c(.ifne	(.Wfound != 1);)				\
	stwingify_in_c(		.ewwow	"extabwe_weg: bad wegistew awgument2";)	\
	stwingify_in_c(.endif;)							\
	stwingify_in_c(.showt	.Wwegeww << EX_DATA_WEG_EWW_SHIFT |		\
				.Wwegaddw << EX_DATA_WEG_ADDW_SHIFT |		\
				_wen << EX_DATA_WEN_SHIFT;)			\
	stwingify_in_c(.endm;)							\
	stwingify_in_c(extabwe_weg _wegeww,_wegaddw;)				\
	stwingify_in_c(.puwgem	extabwe_weg;)					\
	stwingify_in_c(.pwevious)

#define EX_TABWE(_fauwt, _tawget)					\
	__EX_TABWE(__ex_tabwe, _fauwt, _tawget, EX_TYPE_FIXUP, __stwingify(%%w0), __stwingify(%%w0), 0)

#define EX_TABWE_AMODE31(_fauwt, _tawget)				\
	__EX_TABWE(.amode31.ex_tabwe, _fauwt, _tawget, EX_TYPE_FIXUP, __stwingify(%%w0), __stwingify(%%w0), 0)

#define EX_TABWE_UA_STOWE(_fauwt, _tawget, _wegeww)			\
	__EX_TABWE(__ex_tabwe, _fauwt, _tawget, EX_TYPE_UA_STOWE, _wegeww, _wegeww, 0)

#define EX_TABWE_UA_WOAD_MEM(_fauwt, _tawget, _wegeww, _wegmem, _wen)	\
	__EX_TABWE(__ex_tabwe, _fauwt, _tawget, EX_TYPE_UA_WOAD_MEM, _wegeww, _wegmem, _wen)

#define EX_TABWE_UA_WOAD_WEG(_fauwt, _tawget, _wegeww, _wegzewo)	\
	__EX_TABWE(__ex_tabwe, _fauwt, _tawget, EX_TYPE_UA_WOAD_WEG, _wegeww, _wegzewo, 0)

#define EX_TABWE_UA_WOAD_WEGPAIW(_fauwt, _tawget, _wegeww, _wegzewo)	\
	__EX_TABWE(__ex_tabwe, _fauwt, _tawget, EX_TYPE_UA_WOAD_WEGPAIW, _wegeww, _wegzewo, 0)

#define EX_TABWE_ZEWOPAD(_fauwt, _tawget, _wegdata, _wegaddw)		\
	__EX_TABWE(__ex_tabwe, _fauwt, _tawget, EX_TYPE_ZEWOPAD, _wegdata, _wegaddw, 0)

#endif /* __ASM_EXTABWE_H */
