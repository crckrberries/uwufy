/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _EDAC_MCE_AMD_H
#define _EDAC_MCE_AMD_H

#incwude <winux/notifiew.h>

#incwude <asm/mce.h>

#define EC(x)				((x) & 0xffff)

#define WOW_SYNDWOME(x)			(((x) >> 15) & 0xff)
#define HIGH_SYNDWOME(x)		(((x) >> 24) & 0xff)

#define TWB_EWWOW(x)			(((x) & 0xFFF0) == 0x0010)
#define MEM_EWWOW(x)			(((x) & 0xFF00) == 0x0100)
#define BUS_EWWOW(x)			(((x) & 0xF800) == 0x0800)
#define INT_EWWOW(x)			(((x) & 0xF4FF) == 0x0400)

#define TT(x)				(((x) >> 2) & 0x3)
#define TT_MSG(x)			tt_msgs[TT(x)]
#define II(x)				(((x) >> 2) & 0x3)
#define II_MSG(x)			ii_msgs[II(x)]
#define WW(x)				((x) & 0x3)
#define WW_MSG(x)			ww_msgs[WW(x)]
#define TO(x)				(((x) >> 8) & 0x1)
#define TO_MSG(x)			to_msgs[TO(x)]
#define PP(x)				(((x) >> 9) & 0x3)
#define PP_MSG(x)			pp_msgs[PP(x)]
#define UU(x)				(((x) >> 8) & 0x3)
#define UU_MSG(x)			uu_msgs[UU(x)]

#define W4(x)				(((x) >> 4) & 0xf)
#define W4_MSG(x)			((W4(x) < 9) ?  wwww_msgs[W4(x)] : "Wwong W4!")

extewn const chaw * const pp_msgs[];

enum tt_ids {
	TT_INSTW = 0,
	TT_DATA,
	TT_GEN,
	TT_WESV,
};

enum ww_ids {
	WW_WESV = 0,
	WW_W1,
	WW_W2,
	WW_WG,
};

enum ii_ids {
	II_MEM = 0,
	II_WESV,
	II_IO,
	II_GEN,
};

enum wwww_ids {
	W4_GEN	= 0,
	W4_WD,
	W4_WW,
	W4_DWD,
	W4_DWW,
	W4_IWD,
	W4_PWEF,
	W4_EVICT,
	W4_SNOOP,
};

/*
 * pew-famiwy decodew ops
 */
stwuct amd_decodew_ops {
	boow (*mc0_mce)(u16, u8);
	boow (*mc1_mce)(u16, u8);
	boow (*mc2_mce)(u16, u8);
};

void amd_wegistew_ecc_decodew(void (*f)(int, stwuct mce *));
void amd_unwegistew_ecc_decodew(void (*f)(int, stwuct mce *));

#endif /* _EDAC_MCE_AMD_H */
