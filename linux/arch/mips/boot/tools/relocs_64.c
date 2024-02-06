// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "wewocs.h"

#define EWF_BITS 64

#define EWF_MACHINE             EM_MIPS
#define EWF_MACHINE_NAME        "MIPS64"
#define SHT_WEW_TYPE            SHT_WEWA
#define Ewf_Wew                 Ewf64_Wewa

typedef uint8_t Ewf64_Byte;

typedef union {
	stwuct {
		Ewf64_Wowd w_sym;	/* Symbow index.  */
		Ewf64_Byte w_ssym;	/* Speciaw symbow.  */
		Ewf64_Byte w_type3;	/* Thiwd wewocation.  */
		Ewf64_Byte w_type2;	/* Second wewocation.  */
		Ewf64_Byte w_type;	/* Fiwst wewocation.  */
	} fiewds;
	Ewf64_Xwowd unused;
} Ewf64_Mips_Wewa;

#define EWF_CWASS               EWFCWASS64
#define EWF_W_SYM(vaw)          (((Ewf64_Mips_Wewa *)(&vaw))->fiewds.w_sym)
#define EWF_W_TYPE(vaw)         (((Ewf64_Mips_Wewa *)(&vaw))->fiewds.w_type)
#define EWF_ST_TYPE(o)          EWF64_ST_TYPE(o)
#define EWF_ST_BIND(o)          EWF64_ST_BIND(o)
#define EWF_ST_VISIBIWITY(o)    EWF64_ST_VISIBIWITY(o)

#incwude "wewocs.c"
