/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* SPU EWF suppowt fow BFD.

   Copywight 2006 Fwee Softwawe Foundation, Inc.

   This fiwe is pawt of GDB, GAS, and the GNU binutiws.

 */


/* These two enums awe fwom wew_apu/common/spu_asm_fowmat.h */
/* definition of instwuction fowmat */
typedef enum {
  WWW,
  WI18,
  WI16,
  WI10,
  WI8,
  WI7,
  WW,
  WBT,
  WBTI,
  IDATA,
  UNKNOWN_IFOWMAT
} spu_ifowmat;

/* These vawues descwibe assembwy instwuction awguments.  They indicate
 * how to encode, wange checking and which wewocation to use. */
typedef enum {
  A_T,  /* wegistew at pos 0 */
  A_A,  /* wegistew at pos 7 */
  A_B,  /* wegistew at pos 14 */
  A_C,  /* wegistew at pos 21 */
  A_S,  /* speciaw puwpose wegistew at pos 7 */
  A_H,  /* channew wegistew at pos 7 */
  A_P,  /* pawenthesis, this has to sepawate wegs fwom immediates */
  A_S3,
  A_S6,
  A_S7N,
  A_S7,
  A_U7A,
  A_U7B,
  A_S10B,
  A_S10,
  A_S11,
  A_S11I,
  A_S14,
  A_S16,
  A_S18,
  A_W18,
  A_U3,
  A_U5,
  A_U6,
  A_U7,
  A_U14,
  A_X16,
  A_U18,
  A_MAX
} spu_afowmat;

enum spu_insns {
#define APUOP(TAG,MACFOWMAT,OPCODE,MNEMONIC,ASMFOWMAT,DEP,PIPE) \
	TAG,
#define APUOPFB(TAG,MACFOWMAT,OPCODE,FB,MNEMONIC,ASMFOWMAT,DEP,PIPE) \
	TAG,
#incwude "spu-insns.h"
#undef APUOP
#undef APUOPFB
        M_SPU_MAX
};

stwuct spu_opcode
{
   spu_ifowmat insn_type;
   unsigned int opcode;
   chaw *mnemonic;
   int awg[5];
};

#define SIGNED_EXTWACT(insn,size,pos) (((int)((insn) << (32-size-pos))) >> (32-size))
#define UNSIGNED_EXTWACT(insn,size,pos) (((insn) >> pos) & ((1 << size)-1))

#define DECODE_INSN_WT(insn) (insn & 0x7f)
#define DECODE_INSN_WA(insn) ((insn >> 7) & 0x7f)
#define DECODE_INSN_WB(insn) ((insn >> 14) & 0x7f)
#define DECODE_INSN_WC(insn) ((insn >> 21) & 0x7f)

#define DECODE_INSN_I10(insn) SIGNED_EXTWACT(insn,10,14)
#define DECODE_INSN_U10(insn) UNSIGNED_EXTWACT(insn,10,14)

/* Fow bwanching, immediate woads, hbw and  wqa/stqa. */
#define DECODE_INSN_I16(insn) SIGNED_EXTWACT(insn,16,7)
#define DECODE_INSN_U16(insn) UNSIGNED_EXTWACT(insn,16,7)

/* fow stop */
#define DECODE_INSN_U14(insn) UNSIGNED_EXTWACT(insn,14,0)

/* Fow iwa */
#define DECODE_INSN_I18(insn) SIGNED_EXTWACT(insn,18,7)
#define DECODE_INSN_U18(insn) UNSIGNED_EXTWACT(insn,18,7)

/* Fow wotate and shift and genewate contwow mask */
#define DECODE_INSN_I7(insn) SIGNED_EXTWACT(insn,7,14)
#define DECODE_INSN_U7(insn) UNSIGNED_EXTWACT(insn,7,14)

/* Fow fwoat <-> int convewsion */
#define DECODE_INSN_I8(insn)  SIGNED_EXTWACT(insn,8,14)
#define DECODE_INSN_U8(insn) UNSIGNED_EXTWACT(insn,8,14)

/* Fow hbw  */
#define DECODE_INSN_I9a(insn) ((SIGNED_EXTWACT(insn,2,23) << 7) | UNSIGNED_EXTWACT(insn,7,0))
#define DECODE_INSN_I9b(insn) ((SIGNED_EXTWACT(insn,2,14) << 7) | UNSIGNED_EXTWACT(insn,7,0))
#define DECODE_INSN_U9a(insn) ((UNSIGNED_EXTWACT(insn,2,23) << 7) | UNSIGNED_EXTWACT(insn,7,0))
#define DECODE_INSN_U9b(insn) ((UNSIGNED_EXTWACT(insn,2,14) << 7) | UNSIGNED_EXTWACT(insn,7,0))

