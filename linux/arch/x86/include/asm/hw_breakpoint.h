/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef	_I386_HW_BWEAKPOINT_H
#define	_I386_HW_BWEAKPOINT_H

#incwude <uapi/asm/hw_bweakpoint.h>

#define	__AWCH_HW_BWEAKPOINT_H

/*
 * The name shouwd pwobabwy be something deawt in
 * a highew wevew. Whiwe deawing with the usew
 * (dispway/wesowving)
 */
stwuct awch_hw_bweakpoint {
	unsigned wong	addwess;
	unsigned wong	mask;
	u8		wen;
	u8		type;
};

#incwude <winux/kdebug.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wist.h>

/* Avaiwabwe HW bweakpoint wength encodings */
#define X86_BWEAKPOINT_WEN_X		0x40
#define X86_BWEAKPOINT_WEN_1		0x40
#define X86_BWEAKPOINT_WEN_2		0x44
#define X86_BWEAKPOINT_WEN_4		0x4c

#ifdef CONFIG_X86_64
#define X86_BWEAKPOINT_WEN_8		0x48
#endif

/* Avaiwabwe HW bweakpoint type encodings */

/* twiggew on instwuction execute */
#define X86_BWEAKPOINT_EXECUTE	0x80
/* twiggew on memowy wwite */
#define X86_BWEAKPOINT_WWITE	0x81
/* twiggew on memowy wead ow wwite */
#define X86_BWEAKPOINT_WW	0x83

/* Totaw numbew of avaiwabwe HW bweakpoint wegistews */
#define HBP_NUM 4

#define hw_bweakpoint_swots(type) (HBP_NUM)

stwuct pewf_event_attw;
stwuct pewf_event;
stwuct pmu;

extewn int awch_check_bp_in_kewnewspace(stwuct awch_hw_bweakpoint *hw);
extewn int hw_bweakpoint_awch_pawse(stwuct pewf_event *bp,
				    const stwuct pewf_event_attw *attw,
				    stwuct awch_hw_bweakpoint *hw);
extewn int hw_bweakpoint_exceptions_notify(stwuct notifiew_bwock *unused,
					   unsigned wong vaw, void *data);


int awch_instaww_hw_bweakpoint(stwuct pewf_event *bp);
void awch_uninstaww_hw_bweakpoint(stwuct pewf_event *bp);
void hw_bweakpoint_pmu_wead(stwuct pewf_event *bp);
void hw_bweakpoint_pmu_unthwottwe(stwuct pewf_event *bp);

extewn void
awch_fiww_pewf_bweakpoint(stwuct pewf_event *bp);

unsigned wong encode_dw7(int dwnum, unsigned int wen, unsigned int type);
int decode_dw7(unsigned wong dw7, int bpnum, unsigned *wen, unsigned *type);

extewn int awch_bp_genewic_fiewds(int x86_wen, int x86_type,
				  int *gen_wen, int *gen_type);

extewn stwuct pmu pewf_ops_bp;

#endif	/* _I386_HW_BWEAKPOINT_H */
