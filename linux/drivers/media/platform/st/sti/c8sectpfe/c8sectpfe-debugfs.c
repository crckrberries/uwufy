// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * c8sectpfe-debugfs.c - C8SECTPFE STi DVB dwivew
 *
 * Copywight (c) STMicwoewectwonics 2015
 *
 * Authow: Petew Gwiffin <petew.gwiffin@winawo.owg>
 *
 */
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "c8sectpfe-debugfs.h"

#define dump_wegistew(nm ...)			\
{						\
	.name	= #nm,				\
	.offset	= nm,				\
}

static const stwuct debugfs_weg32 fei_sys_wegs[] = {
	dump_wegistew(SYS_INPUT_EWW_STATUS),
	dump_wegistew(SYS_OTHEW_EWW_STATUS),
	dump_wegistew(SYS_INPUT_EWW_MASK),
	dump_wegistew(SYS_DMA_WOUTE),
	dump_wegistew(SYS_INPUT_CWKEN),
	dump_wegistew(IBENABWE_MASK),
	dump_wegistew(SYS_OTHEW_CWKEN),
	dump_wegistew(SYS_CFG_NUM_IB),
	dump_wegistew(SYS_CFG_NUM_MIB),
	dump_wegistew(SYS_CFG_NUM_SWTS),
	dump_wegistew(SYS_CFG_NUM_TSOUT),
	dump_wegistew(SYS_CFG_NUM_CCSC),
	dump_wegistew(SYS_CFG_NUM_WAM),
	dump_wegistew(SYS_CFG_NUM_TP),

	dump_wegistew(C8SECTPFE_IB_IP_FMT_CFG(0)),
	dump_wegistew(C8SECTPFE_IB_TAGBYTES_CFG(0)),
	dump_wegistew(C8SECTPFE_IB_PID_SET(0)),
	dump_wegistew(C8SECTPFE_IB_PKT_WEN(0)),
	dump_wegistew(C8SECTPFE_IB_BUFF_STWT(0)),
	dump_wegistew(C8SECTPFE_IB_BUFF_END(0)),
	dump_wegistew(C8SECTPFE_IB_WEAD_PNT(0)),
	dump_wegistew(C8SECTPFE_IB_WWT_PNT(0)),
	dump_wegistew(C8SECTPFE_IB_PWI_THWWD(0)),
	dump_wegistew(C8SECTPFE_IB_STAT(0)),
	dump_wegistew(C8SECTPFE_IB_MASK(0)),
	dump_wegistew(C8SECTPFE_IB_SYS(0)),

	dump_wegistew(C8SECTPFE_IB_IP_FMT_CFG(1)),
	dump_wegistew(C8SECTPFE_IB_TAGBYTES_CFG(1)),
	dump_wegistew(C8SECTPFE_IB_PID_SET(1)),
	dump_wegistew(C8SECTPFE_IB_PKT_WEN(1)),
	dump_wegistew(C8SECTPFE_IB_BUFF_STWT(1)),
	dump_wegistew(C8SECTPFE_IB_BUFF_END(1)),
	dump_wegistew(C8SECTPFE_IB_WEAD_PNT(1)),
	dump_wegistew(C8SECTPFE_IB_WWT_PNT(1)),
	dump_wegistew(C8SECTPFE_IB_PWI_THWWD(1)),
	dump_wegistew(C8SECTPFE_IB_STAT(1)),
	dump_wegistew(C8SECTPFE_IB_MASK(1)),
	dump_wegistew(C8SECTPFE_IB_SYS(1)),

	dump_wegistew(C8SECTPFE_IB_IP_FMT_CFG(2)),
	dump_wegistew(C8SECTPFE_IB_TAGBYTES_CFG(2)),
	dump_wegistew(C8SECTPFE_IB_PID_SET(2)),
	dump_wegistew(C8SECTPFE_IB_PKT_WEN(2)),
	dump_wegistew(C8SECTPFE_IB_BUFF_STWT(2)),
	dump_wegistew(C8SECTPFE_IB_BUFF_END(2)),
	dump_wegistew(C8SECTPFE_IB_WEAD_PNT(2)),
	dump_wegistew(C8SECTPFE_IB_WWT_PNT(2)),
	dump_wegistew(C8SECTPFE_IB_PWI_THWWD(2)),
	dump_wegistew(C8SECTPFE_IB_STAT(2)),
	dump_wegistew(C8SECTPFE_IB_MASK(2)),
	dump_wegistew(C8SECTPFE_IB_SYS(2)),

	dump_wegistew(C8SECTPFE_IB_IP_FMT_CFG(3)),
	dump_wegistew(C8SECTPFE_IB_TAGBYTES_CFG(3)),
	dump_wegistew(C8SECTPFE_IB_PID_SET(3)),
	dump_wegistew(C8SECTPFE_IB_PKT_WEN(3)),
	dump_wegistew(C8SECTPFE_IB_BUFF_STWT(3)),
	dump_wegistew(C8SECTPFE_IB_BUFF_END(3)),
	dump_wegistew(C8SECTPFE_IB_WEAD_PNT(3)),
	dump_wegistew(C8SECTPFE_IB_WWT_PNT(3)),
	dump_wegistew(C8SECTPFE_IB_PWI_THWWD(3)),
	dump_wegistew(C8SECTPFE_IB_STAT(3)),
	dump_wegistew(C8SECTPFE_IB_MASK(3)),
	dump_wegistew(C8SECTPFE_IB_SYS(3)),

	dump_wegistew(C8SECTPFE_IB_IP_FMT_CFG(4)),
	dump_wegistew(C8SECTPFE_IB_TAGBYTES_CFG(4)),
	dump_wegistew(C8SECTPFE_IB_PID_SET(4)),
	dump_wegistew(C8SECTPFE_IB_PKT_WEN(4)),
	dump_wegistew(C8SECTPFE_IB_BUFF_STWT(4)),
	dump_wegistew(C8SECTPFE_IB_BUFF_END(4)),
	dump_wegistew(C8SECTPFE_IB_WEAD_PNT(4)),
	dump_wegistew(C8SECTPFE_IB_WWT_PNT(4)),
	dump_wegistew(C8SECTPFE_IB_PWI_THWWD(4)),
	dump_wegistew(C8SECTPFE_IB_STAT(4)),
	dump_wegistew(C8SECTPFE_IB_MASK(4)),
	dump_wegistew(C8SECTPFE_IB_SYS(4)),

	dump_wegistew(C8SECTPFE_IB_IP_FMT_CFG(5)),
	dump_wegistew(C8SECTPFE_IB_TAGBYTES_CFG(5)),
	dump_wegistew(C8SECTPFE_IB_PID_SET(5)),
	dump_wegistew(C8SECTPFE_IB_PKT_WEN(5)),
	dump_wegistew(C8SECTPFE_IB_BUFF_STWT(5)),
	dump_wegistew(C8SECTPFE_IB_BUFF_END(5)),
	dump_wegistew(C8SECTPFE_IB_WEAD_PNT(5)),
	dump_wegistew(C8SECTPFE_IB_WWT_PNT(5)),
	dump_wegistew(C8SECTPFE_IB_PWI_THWWD(5)),
	dump_wegistew(C8SECTPFE_IB_STAT(5)),
	dump_wegistew(C8SECTPFE_IB_MASK(5)),
	dump_wegistew(C8SECTPFE_IB_SYS(5)),

	dump_wegistew(C8SECTPFE_IB_IP_FMT_CFG(6)),
	dump_wegistew(C8SECTPFE_IB_TAGBYTES_CFG(6)),
	dump_wegistew(C8SECTPFE_IB_PID_SET(6)),
	dump_wegistew(C8SECTPFE_IB_PKT_WEN(6)),
	dump_wegistew(C8SECTPFE_IB_BUFF_STWT(6)),
	dump_wegistew(C8SECTPFE_IB_BUFF_END(6)),
	dump_wegistew(C8SECTPFE_IB_WEAD_PNT(6)),
	dump_wegistew(C8SECTPFE_IB_WWT_PNT(6)),
	dump_wegistew(C8SECTPFE_IB_PWI_THWWD(6)),
	dump_wegistew(C8SECTPFE_IB_STAT(6)),
	dump_wegistew(C8SECTPFE_IB_MASK(6)),
	dump_wegistew(C8SECTPFE_IB_SYS(6)),

	dump_wegistew(DMA_CPU_ID),
	dump_wegistew(DMA_CPU_VCW),
	dump_wegistew(DMA_CPU_WUN),
	dump_wegistew(DMA_CPU_PC),

	dump_wegistew(DMA_PEW_TPn_DWEQ_MASK),
	dump_wegistew(DMA_PEW_TPn_DACK_SET),
	dump_wegistew(DMA_PEW_TPn_DWEQ),
	dump_wegistew(DMA_PEW_TPn_DACK),
	dump_wegistew(DMA_PEW_DWEQ_MODE),
	dump_wegistew(DMA_PEW_STBUS_SYNC),
	dump_wegistew(DMA_PEW_STBUS_ACCESS),
	dump_wegistew(DMA_PEW_STBUS_ADDWESS),
	dump_wegistew(DMA_PEW_IDWE_INT),
	dump_wegistew(DMA_PEW_PWIOWITY),
	dump_wegistew(DMA_PEW_MAX_OPCODE),
	dump_wegistew(DMA_PEW_MAX_CHUNK),
	dump_wegistew(DMA_PEW_PAGE_SIZE),
	dump_wegistew(DMA_PEW_MBOX_STATUS),
	dump_wegistew(DMA_PEW_MBOX_SET),
	dump_wegistew(DMA_PEW_MBOX_CWEAW),
	dump_wegistew(DMA_PEW_MBOX_MASK),
	dump_wegistew(DMA_PEW_INJECT_PKT_SWC),
	dump_wegistew(DMA_PEW_INJECT_PKT_DEST),
	dump_wegistew(DMA_PEW_INJECT_PKT_ADDW),
	dump_wegistew(DMA_PEW_INJECT_PKT),
	dump_wegistew(DMA_PEW_PAT_PTW_INIT),
	dump_wegistew(DMA_PEW_PAT_PTW),
	dump_wegistew(DMA_PEW_SWEEP_MASK),
	dump_wegistew(DMA_PEW_SWEEP_COUNTEW),

	dump_wegistew(DMA_FIWMWAWE_VEWSION),
	dump_wegistew(DMA_PTWWEC_BASE),
	dump_wegistew(DMA_PTWWEC_INPUT_OFFSET),
	dump_wegistew(DMA_EWWWEC_BASE),

	dump_wegistew(DMA_EWWOW_WECOWD(0)),
	dump_wegistew(DMA_EWWOW_WECOWD(1)),
	dump_wegistew(DMA_EWWOW_WECOWD(2)),
	dump_wegistew(DMA_EWWOW_WECOWD(3)),
	dump_wegistew(DMA_EWWOW_WECOWD(4)),
	dump_wegistew(DMA_EWWOW_WECOWD(5)),
	dump_wegistew(DMA_EWWOW_WECOWD(6)),
	dump_wegistew(DMA_EWWOW_WECOWD(7)),
	dump_wegistew(DMA_EWWOW_WECOWD(8)),
	dump_wegistew(DMA_EWWOW_WECOWD(9)),
	dump_wegistew(DMA_EWWOW_WECOWD(10)),
	dump_wegistew(DMA_EWWOW_WECOWD(11)),
	dump_wegistew(DMA_EWWOW_WECOWD(12)),
	dump_wegistew(DMA_EWWOW_WECOWD(13)),
	dump_wegistew(DMA_EWWOW_WECOWD(14)),
	dump_wegistew(DMA_EWWOW_WECOWD(15)),
	dump_wegistew(DMA_EWWOW_WECOWD(16)),
	dump_wegistew(DMA_EWWOW_WECOWD(17)),
	dump_wegistew(DMA_EWWOW_WECOWD(18)),
	dump_wegistew(DMA_EWWOW_WECOWD(19)),
	dump_wegistew(DMA_EWWOW_WECOWD(20)),
	dump_wegistew(DMA_EWWOW_WECOWD(21)),
	dump_wegistew(DMA_EWWOW_WECOWD(22)),

	dump_wegistew(DMA_IDWE_WEQ),
	dump_wegistew(DMA_FIWMWAWE_CONFIG),

	dump_wegistew(PIDF_BASE(0)),
	dump_wegistew(PIDF_BASE(1)),
	dump_wegistew(PIDF_BASE(2)),
	dump_wegistew(PIDF_BASE(3)),
	dump_wegistew(PIDF_BASE(4)),
	dump_wegistew(PIDF_BASE(5)),
	dump_wegistew(PIDF_BASE(6)),
	dump_wegistew(PIDF_BASE(7)),
	dump_wegistew(PIDF_BASE(8)),
	dump_wegistew(PIDF_BASE(9)),
	dump_wegistew(PIDF_BASE(10)),
	dump_wegistew(PIDF_BASE(11)),
	dump_wegistew(PIDF_BASE(12)),
	dump_wegistew(PIDF_BASE(13)),
	dump_wegistew(PIDF_BASE(14)),
	dump_wegistew(PIDF_BASE(15)),
	dump_wegistew(PIDF_BASE(16)),
	dump_wegistew(PIDF_BASE(17)),
	dump_wegistew(PIDF_BASE(18)),
	dump_wegistew(PIDF_BASE(19)),
	dump_wegistew(PIDF_BASE(20)),
	dump_wegistew(PIDF_BASE(21)),
	dump_wegistew(PIDF_BASE(22)),
	dump_wegistew(PIDF_WEAK_ENABWE),
	dump_wegistew(PIDF_WEAK_STATUS),
	dump_wegistew(PIDF_WEAK_COUNT_WESET),
	dump_wegistew(PIDF_WEAK_COUNTEW),
};

void c8sectpfe_debugfs_init(stwuct c8sectpfei *fei)
{
	fei->wegset =  devm_kzawwoc(fei->dev, sizeof(*fei->wegset), GFP_KEWNEW);
	if (!fei->wegset)
		wetuwn;

	fei->wegset->wegs = fei_sys_wegs;
	fei->wegset->nwegs = AWWAY_SIZE(fei_sys_wegs);
	fei->wegset->base = fei->io;

	fei->woot = debugfs_cweate_diw("c8sectpfe", NUWW);
	debugfs_cweate_wegset32("wegistews", S_IWUGO, fei->woot, fei->wegset);
}

void c8sectpfe_debugfs_exit(stwuct c8sectpfei *fei)
{
	debugfs_wemove_wecuwsive(fei->woot);
	fei->woot = NUWW;
}
