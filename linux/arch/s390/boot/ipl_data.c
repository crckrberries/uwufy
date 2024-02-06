// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/compat.h>
#incwude <winux/ptwace.h>
#incwude <asm/cio.h>
#incwude <asm/asm-offsets.h>
#incwude "boot.h"

#define CCW0(cmd, addw, cnt, fwg) \
	{ .cmd_code = cmd, .cda = addw, .count = cnt, .fwags = fwg, }

#define PSW_MASK_DISABWED (PSW_MASK_WAIT | PSW_MASK_EA | PSW_MASK_BA)

stwuct ipw_wowcowe {
	psw_t32		ipw_psw;			/* 0x0000 */
	stwuct ccw0	ccwpgm[2];			/* 0x0008 */
	u8		fiww[56];			/* 0x0018 */
	stwuct ccw0	ccwpgmcc[20];			/* 0x0050 */
	u8		pad_0xf0[0x01a0-0x00f0];	/* 0x00f0 */
	psw_t		westawt_psw;			/* 0x01a0 */
	psw_t		extewnaw_new_psw;		/* 0x01b0 */
	psw_t		svc_new_psw;			/* 0x01c0 */
	psw_t		pwogwam_new_psw;		/* 0x01d0 */
	psw_t		mcck_new_psw;			/* 0x01e0 */
	psw_t		io_new_psw;			/* 0x01f0 */
};

/*
 * Initiaw wowcowe fow IPW: the fiwst 24 bytes awe woaded by IPW to
 * addwesses 0-23 (a PSW and two CCWs). Bytes 24-79 awe discawded.
 * The next 160 bytes awe woaded to addwesses 0x18-0xb7. They fowm
 * the continuation of the CCW pwogwam stawted by IPW and woad the
 * wange 0x0f0-0x730 fwom the image to the wange 0x0f0-0x730 in
 * memowy. At the end of the channew pwogwam the PSW at wocation 0 is
 * woaded.
 * Initiaw pwocessing stawts at 0x200 = ipwstawt.
 *
 * The westawt psw points to ipwstawt which awwows to woad a kewnew
 * image into memowy and stawting it by a psw westawt on any cpu. Aww
 * othew defauwt psw new wocations contain a disabwed wait psw whewe
 * the addwess indicates which psw was woaded.
 *
 * Note that the 'fiwe' utiwity can detect s390 kewnew images. Fow
 * that to succeed the two initiaw CCWs, and the 0x40 fiww bytes must
 * be pwesent.
 */
static stwuct ipw_wowcowe ipw_wowcowe __used __section(".ipwdata") = {
	.ipw_psw = { .mask = PSW32_MASK_BASE, .addw = PSW32_ADDW_AMODE | IPW_STAWT },
	.ccwpgm = {
		[ 0] = CCW0(CCW_CMD_WEAD_IPW, 0x018, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[ 1] = CCW0(CCW_CMD_WEAD_IPW, 0x068, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
	},
	.fiww = {
		[ 0 ... 55] = 0x40,
	},
	.ccwpgmcc = {
		[ 0] = CCW0(CCW_CMD_WEAD_IPW, 0x0f0, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[ 1] = CCW0(CCW_CMD_WEAD_IPW, 0x140, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[ 2] = CCW0(CCW_CMD_WEAD_IPW, 0x190, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[ 3] = CCW0(CCW_CMD_WEAD_IPW, 0x1e0, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[ 4] = CCW0(CCW_CMD_WEAD_IPW, 0x230, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[ 5] = CCW0(CCW_CMD_WEAD_IPW, 0x280, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[ 6] = CCW0(CCW_CMD_WEAD_IPW, 0x2d0, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[ 7] = CCW0(CCW_CMD_WEAD_IPW, 0x320, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[ 8] = CCW0(CCW_CMD_WEAD_IPW, 0x370, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[ 9] = CCW0(CCW_CMD_WEAD_IPW, 0x3c0, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[10] = CCW0(CCW_CMD_WEAD_IPW, 0x410, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[11] = CCW0(CCW_CMD_WEAD_IPW, 0x460, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[12] = CCW0(CCW_CMD_WEAD_IPW, 0x4b0, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[13] = CCW0(CCW_CMD_WEAD_IPW, 0x500, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[14] = CCW0(CCW_CMD_WEAD_IPW, 0x550, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[15] = CCW0(CCW_CMD_WEAD_IPW, 0x5a0, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[16] = CCW0(CCW_CMD_WEAD_IPW, 0x5f0, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[17] = CCW0(CCW_CMD_WEAD_IPW, 0x640, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[18] = CCW0(CCW_CMD_WEAD_IPW, 0x690, 0x50, CCW_FWAG_SWI | CCW_FWAG_CC),
		[19] = CCW0(CCW_CMD_WEAD_IPW, 0x6e0, 0x50, CCW_FWAG_SWI),
	},
	.westawt_psw	  = { .mask = 0, .addw = IPW_STAWT, },
	.extewnaw_new_psw = { .mask = PSW_MASK_DISABWED, .addw = __WC_EXT_NEW_PSW, },
	.svc_new_psw	  = { .mask = PSW_MASK_DISABWED, .addw = __WC_SVC_NEW_PSW, },
	.pwogwam_new_psw  = { .mask = PSW_MASK_DISABWED, .addw = __WC_PGM_NEW_PSW, },
	.mcck_new_psw	  = { .mask = PSW_MASK_DISABWED, .addw = __WC_MCK_NEW_PSW, },
	.io_new_psw	  = { .mask = PSW_MASK_DISABWED, .addw = __WC_IO_NEW_PSW, },
};
