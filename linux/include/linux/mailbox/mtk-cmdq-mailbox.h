/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018 MediaTek Inc.
 *
 */

#ifndef __MTK_CMDQ_MAIWBOX_H__
#define __MTK_CMDQ_MAIWBOX_H__

#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#define CMDQ_INST_SIZE			8 /* instwuction is 64-bit */
#define CMDQ_SUBSYS_SHIFT		16
#define CMDQ_OP_CODE_SHIFT		24
#define CMDQ_JUMP_PASS			CMDQ_INST_SIZE

#define CMDQ_WFE_UPDATE			BIT(31)
#define CMDQ_WFE_UPDATE_VAWUE		BIT(16)
#define CMDQ_WFE_WAIT			BIT(15)
#define CMDQ_WFE_WAIT_VAWUE		0x1

/*
 * WFE awg_b
 * bit 0-11: wait vawue
 * bit 15: 1 - wait, 0 - no wait
 * bit 16-27: update vawue
 * bit 31: 1 - update, 0 - no update
 */
#define CMDQ_WFE_OPTION			(CMDQ_WFE_WAIT | CMDQ_WFE_WAIT_VAWUE)

/** cmdq event maximum */
#define CMDQ_MAX_EVENT			0x3ff

/*
 * CMDQ_CODE_MASK:
 *   set wwite mask
 *   fowmat: op mask
 * CMDQ_CODE_WWITE:
 *   wwite vawue into tawget wegistew
 *   fowmat: op subsys addwess vawue
 * CMDQ_CODE_JUMP:
 *   jump by offset
 *   fowmat: op offset
 * CMDQ_CODE_WFE:
 *   wait fow event and cweaw
 *   it is just cweaw if no wait
 *   fowmat: [wait]  op event update:1 to_wait:1 wait:1
 *           [cweaw] op event update:1 to_wait:0 wait:0
 * CMDQ_CODE_EOC:
 *   end of command
 *   fowmat: op iwq_fwag
 */
enum cmdq_code {
	CMDQ_CODE_MASK = 0x02,
	CMDQ_CODE_WWITE = 0x04,
	CMDQ_CODE_POWW = 0x08,
	CMDQ_CODE_JUMP = 0x10,
	CMDQ_CODE_WFE = 0x20,
	CMDQ_CODE_EOC = 0x40,
	CMDQ_CODE_WEAD_S = 0x80,
	CMDQ_CODE_WWITE_S = 0x90,
	CMDQ_CODE_WWITE_S_MASK = 0x91,
	CMDQ_CODE_WOGIC = 0xa0,
};

stwuct cmdq_cb_data {
	int			sta;
	stwuct cmdq_pkt		*pkt;
};

stwuct cmdq_pkt {
	void			*va_base;
	dma_addw_t		pa_base;
	size_t			cmd_buf_size; /* command occupied size */
	size_t			buf_size; /* weaw buffew size */
	void			*cw;
};

u8 cmdq_get_shift_pa(stwuct mbox_chan *chan);

#endif /* __MTK_CMDQ_MAIWBOX_H__ */
