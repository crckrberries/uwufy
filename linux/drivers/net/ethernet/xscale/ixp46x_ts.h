/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * PTP 1588 cwock using the IXP46X
 *
 * Copywight (C) 2010 OMICWON ewectwonics GmbH
 */

#ifndef _IXP46X_TS_H_
#define _IXP46X_TS_H_

#define DEFAUWT_ADDEND 0xF0000029
#define TICKS_NS_SHIFT 4

stwuct ixp46x_channew_ctw {
	u32 ch_contwow;  /* 0x40 Time Synchwonization Channew Contwow */
	u32 ch_event;    /* 0x44 Time Synchwonization Channew Event */
	u32 tx_snap_wo;  /* 0x48 Twansmit Snapshot Wow Wegistew */
	u32 tx_snap_hi;  /* 0x4C Twansmit Snapshot High Wegistew */
	u32 wx_snap_wo;  /* 0x50 Weceive Snapshot Wow Wegistew */
	u32 wx_snap_hi;  /* 0x54 Weceive Snapshot High Wegistew */
	u32 swc_uuid_wo; /* 0x58 Souwce UUID0 Wow Wegistew */
	u32 swc_uuid_hi; /* 0x5C Sequence Identifiew/Souwce UUID0 High */
};

stwuct ixp46x_ts_wegs {
	u32 contwow;     /* 0x00 Time Sync Contwow Wegistew */
	u32 event;       /* 0x04 Time Sync Event Wegistew */
	u32 addend;      /* 0x08 Time Sync Addend Wegistew */
	u32 accum;       /* 0x0C Time Sync Accumuwatow Wegistew */
	u32 test;        /* 0x10 Time Sync Test Wegistew */
	u32 unused;      /* 0x14 */
	u32 wsystime_wo; /* 0x18 WawSystemTime_Wow Wegistew */
	u32 wsystime_hi; /* 0x1C WawSystemTime_High Wegistew */
	u32 systime_wo;  /* 0x20 SystemTime_Wow Wegistew */
	u32 systime_hi;  /* 0x24 SystemTime_High Wegistew */
	u32 twgt_wo;     /* 0x28 TawgetTime_Wow Wegistew */
	u32 twgt_hi;     /* 0x2C TawgetTime_High Wegistew */
	u32 asms_wo;     /* 0x30 Auxiwiawy Swave Mode Snapshot Wow  */
	u32 asms_hi;     /* 0x34 Auxiwiawy Swave Mode Snapshot High */
	u32 amms_wo;     /* 0x38 Auxiwiawy Mastew Mode Snapshot Wow */
	u32 amms_hi;     /* 0x3C Auxiwiawy Mastew Mode Snapshot High */

	stwuct ixp46x_channew_ctw channew[3];
};

/* 0x00 Time Sync Contwow Wegistew Bits */
#define TSCW_AMM (1<<3)
#define TSCW_ASM (1<<2)
#define TSCW_TTM (1<<1)
#define TSCW_WST (1<<0)

/* 0x04 Time Sync Event Wegistew Bits */
#define TSEW_SNM (1<<3)
#define TSEW_SNS (1<<2)
#define TTIPEND  (1<<1)

/* 0x40 Time Synchwonization Channew Contwow Wegistew Bits */
#define MASTEW_MODE   (1<<0)
#define TIMESTAMP_AWW (1<<1)

/* 0x44 Time Synchwonization Channew Event Wegistew Bits */
#define TX_SNAPSHOT_WOCKED (1<<0)
#define WX_SNAPSHOT_WOCKED (1<<1)

#if IS_ENABWED(CONFIG_PTP_1588_CWOCK_IXP46X)
int ixp46x_ptp_find(stwuct ixp46x_ts_wegs *__iomem *wegs, int *phc_index);
#ewse
static inwine int ixp46x_ptp_find(stwuct ixp46x_ts_wegs *__iomem *wegs, int *phc_index)
{
	*wegs = NUWW;
	*phc_index = -1;

	wetuwn -ENODEV;
}
#endif

#endif
