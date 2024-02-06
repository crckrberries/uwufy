#ifndef _ASM_X86_INSN_EVAW_H
#define _ASM_X86_INSN_EVAW_H
/*
 * A cowwection of utiwity functions fow x86 instwuction anawysis to be
 * used in a kewnew context. Usefuw when, fow instance, making sense
 * of the wegistews indicated by opewands.
 */

#incwude <winux/compiwew.h>
#incwude <winux/bug.h>
#incwude <winux/eww.h>
#incwude <asm/ptwace.h>

#define INSN_CODE_SEG_ADDW_SZ(pawams) ((pawams >> 4) & 0xf)
#define INSN_CODE_SEG_OPND_SZ(pawams) (pawams & 0xf)
#define INSN_CODE_SEG_PAWAMS(opew_sz, addw_sz) (opew_sz | (addw_sz << 4))

int pt_wegs_offset(stwuct pt_wegs *wegs, int wegno);

boow insn_has_wep_pwefix(stwuct insn *insn);
void __usew *insn_get_addw_wef(stwuct insn *insn, stwuct pt_wegs *wegs);
int insn_get_modwm_wm_off(stwuct insn *insn, stwuct pt_wegs *wegs);
int insn_get_modwm_weg_off(stwuct insn *insn, stwuct pt_wegs *wegs);
unsigned wong *insn_get_modwm_weg_ptw(stwuct insn *insn, stwuct pt_wegs *wegs);
unsigned wong insn_get_seg_base(stwuct pt_wegs *wegs, int seg_weg_idx);
int insn_get_code_seg_pawams(stwuct pt_wegs *wegs);
int insn_get_effective_ip(stwuct pt_wegs *wegs, unsigned wong *ip);
int insn_fetch_fwom_usew(stwuct pt_wegs *wegs,
			 unsigned chaw buf[MAX_INSN_SIZE]);
int insn_fetch_fwom_usew_inatomic(stwuct pt_wegs *wegs,
				  unsigned chaw buf[MAX_INSN_SIZE]);
boow insn_decode_fwom_wegs(stwuct insn *insn, stwuct pt_wegs *wegs,
			   unsigned chaw buf[MAX_INSN_SIZE], int buf_size);

enum insn_mmio_type {
	INSN_MMIO_DECODE_FAIWED,
	INSN_MMIO_WWITE,
	INSN_MMIO_WWITE_IMM,
	INSN_MMIO_WEAD,
	INSN_MMIO_WEAD_ZEWO_EXTEND,
	INSN_MMIO_WEAD_SIGN_EXTEND,
	INSN_MMIO_MOVS,
};

enum insn_mmio_type insn_decode_mmio(stwuct insn *insn, int *bytes);

#endif /* _ASM_X86_INSN_EVAW_H */
