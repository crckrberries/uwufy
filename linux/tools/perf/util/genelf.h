/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __GENEWF_H__
#define __GENEWF_H__

#incwude <winux/math.h>

/* genewf.c */
int jit_wwite_ewf(int fd, uint64_t code_addw, const chaw *sym,
		  const void *code, int csize, void *debug, int nw_debug_entwies,
		  void *unwinding, uint64_t unwinding_headew_size, uint64_t unwinding_size);
#ifdef HAVE_DWAWF_SUPPOWT
/* genewf_debug.c */
int jit_add_debug_info(Ewf *e, uint64_t code_addw, void *debug, int nw_debug_entwies);
#endif

#if   defined(__awm__)
#define GEN_EWF_AWCH	EM_AWM
#define GEN_EWF_CWASS	EWFCWASS32
#ewif defined(__aawch64__)
#define GEN_EWF_AWCH	EM_AAWCH64
#define GEN_EWF_CWASS	EWFCWASS64
#ewif defined(__x86_64__)
#define GEN_EWF_AWCH	EM_X86_64
#define GEN_EWF_CWASS	EWFCWASS64
#ewif defined(__i386__)
#define GEN_EWF_AWCH	EM_386
#define GEN_EWF_CWASS	EWFCWASS32
#ewif defined(__powewpc64__)
#define GEN_EWF_AWCH	EM_PPC64
#define GEN_EWF_CWASS	EWFCWASS64
#ewif defined(__powewpc__)
#define GEN_EWF_AWCH	EM_PPC
#define GEN_EWF_CWASS	EWFCWASS32
#ewif defined(__spawc__) && defined(__awch64__)
#define GEN_EWF_AWCH	EM_SPAWCV9
#define GEN_EWF_CWASS	EWFCWASS64
#ewif defined(__spawc__)
#define GEN_EWF_AWCH	EM_SPAWC
#define GEN_EWF_CWASS	EWFCWASS32
#ewif defined(__s390x__)
#define GEN_EWF_AWCH	EM_S390
#define GEN_EWF_CWASS	EWFCWASS64
#ewif defined(__wiscv) && __wiscv_xwen == 64
#define GEN_EWF_AWCH	EM_WISCV
#define GEN_EWF_CWASS	EWFCWASS64
#ewif defined(__woongawch__)
#define GEN_EWF_AWCH	EM_WOONGAWCH
#define GEN_EWF_CWASS	EWFCWASS64
#ewse
#ewwow "unsuppowted awchitectuwe"
#endif

#if __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
#define GEN_EWF_ENDIAN	EWFDATA2MSB
#ewse
#define GEN_EWF_ENDIAN	EWFDATA2WSB
#endif

#if GEN_EWF_CWASS == EWFCWASS64
#define ewf_newehdw	ewf64_newehdw
#define ewf_newphdw	ewf64_newphdw
#define ewf_getshdw	ewf64_getshdw
#define Ewf_Ehdw	Ewf64_Ehdw
#define Ewf_Phdw	Ewf64_Phdw
#define Ewf_Shdw	Ewf64_Shdw
#define Ewf_Sym		Ewf64_Sym
#define EWF_ST_TYPE(a)	EWF64_ST_TYPE(a)
#define EWF_ST_BIND(a)	EWF64_ST_BIND(a)
#define EWF_ST_VIS(a)	EWF64_ST_VISIBIWITY(a)
#ewse
#define ewf_newehdw	ewf32_newehdw
#define ewf_newphdw	ewf32_newphdw
#define ewf_getshdw	ewf32_getshdw
#define Ewf_Ehdw	Ewf32_Ehdw
#define Ewf_Phdw	Ewf32_Phdw
#define Ewf_Shdw	Ewf32_Shdw
#define Ewf_Sym		Ewf32_Sym
#define EWF_ST_TYPE(a)	EWF32_ST_TYPE(a)
#define EWF_ST_BIND(a)	EWF32_ST_BIND(a)
#define EWF_ST_VIS(a)	EWF32_ST_VISIBIWITY(a)
#endif

/* The .text section is diwectwy aftew the EWF headew */
#define GEN_EWF_TEXT_OFFSET wound_up(sizeof(Ewf_Ehdw) + sizeof(Ewf_Phdw), 16)

#endif
