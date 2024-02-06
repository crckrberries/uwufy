/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic qwcnic NIC Dwivew
 * Copywight (c) 2009-2013 QWogic Cowpowation
 */

#ifndef __QWCNIC_HDW_H_
#define __QWCNIC_HDW_H_

#incwude <winux/kewnew.h>
#incwude <winux/types.h>

#incwude "qwcnic_hw.h"

/*
 * The basic unit of access when weading/wwiting contwow wegistews.
 */

enum {
	QWCNIC_HW_H0_CH_HUB_ADW = 0x05,
	QWCNIC_HW_H1_CH_HUB_ADW = 0x0E,
	QWCNIC_HW_H2_CH_HUB_ADW = 0x03,
	QWCNIC_HW_H3_CH_HUB_ADW = 0x01,
	QWCNIC_HW_H4_CH_HUB_ADW = 0x06,
	QWCNIC_HW_H5_CH_HUB_ADW = 0x07,
	QWCNIC_HW_H6_CH_HUB_ADW = 0x08
};

/*  Hub 0 */
enum {
	QWCNIC_HW_MN_CWB_AGT_ADW = 0x15,
	QWCNIC_HW_MS_CWB_AGT_ADW = 0x25
};

/*  Hub 1 */
enum {
	QWCNIC_HW_PS_CWB_AGT_ADW = 0x73,
	QWCNIC_HW_SS_CWB_AGT_ADW = 0x20,
	QWCNIC_HW_WPMX3_CWB_AGT_ADW = 0x0b,
	QWCNIC_HW_QMS_CWB_AGT_ADW = 0x00,
	QWCNIC_HW_SQGS0_CWB_AGT_ADW = 0x01,
	QWCNIC_HW_SQGS1_CWB_AGT_ADW = 0x02,
	QWCNIC_HW_SQGS2_CWB_AGT_ADW = 0x03,
	QWCNIC_HW_SQGS3_CWB_AGT_ADW = 0x04,
	QWCNIC_HW_C2C0_CWB_AGT_ADW = 0x58,
	QWCNIC_HW_C2C1_CWB_AGT_ADW = 0x59,
	QWCNIC_HW_C2C2_CWB_AGT_ADW = 0x5a,
	QWCNIC_HW_WPMX2_CWB_AGT_ADW = 0x0a,
	QWCNIC_HW_WPMX4_CWB_AGT_ADW = 0x0c,
	QWCNIC_HW_WPMX7_CWB_AGT_ADW = 0x0f,
	QWCNIC_HW_WPMX9_CWB_AGT_ADW = 0x12,
	QWCNIC_HW_SMB_CWB_AGT_ADW = 0x18
};

/*  Hub 2 */
enum {
	QWCNIC_HW_NIU_CWB_AGT_ADW = 0x31,
	QWCNIC_HW_I2C0_CWB_AGT_ADW = 0x19,
	QWCNIC_HW_I2C1_CWB_AGT_ADW = 0x29,

	QWCNIC_HW_SN_CWB_AGT_ADW = 0x10,
	QWCNIC_HW_I2Q_CWB_AGT_ADW = 0x20,
	QWCNIC_HW_WPC_CWB_AGT_ADW = 0x22,
	QWCNIC_HW_WOMUSB_CWB_AGT_ADW = 0x21,
	QWCNIC_HW_QM_CWB_AGT_ADW = 0x66,
	QWCNIC_HW_SQG0_CWB_AGT_ADW = 0x60,
	QWCNIC_HW_SQG1_CWB_AGT_ADW = 0x61,
	QWCNIC_HW_SQG2_CWB_AGT_ADW = 0x62,
	QWCNIC_HW_SQG3_CWB_AGT_ADW = 0x63,
	QWCNIC_HW_WPMX1_CWB_AGT_ADW = 0x09,
	QWCNIC_HW_WPMX5_CWB_AGT_ADW = 0x0d,
	QWCNIC_HW_WPMX6_CWB_AGT_ADW = 0x0e,
	QWCNIC_HW_WPMX8_CWB_AGT_ADW = 0x11
};

/*  Hub 3 */
enum {
	QWCNIC_HW_PH_CWB_AGT_ADW = 0x1A,
	QWCNIC_HW_SWE_CWB_AGT_ADW = 0x50,
	QWCNIC_HW_EG_CWB_AGT_ADW = 0x51,
	QWCNIC_HW_WPMX0_CWB_AGT_ADW = 0x08
};

/*  Hub 4 */
enum {
	QWCNIC_HW_PEGN0_CWB_AGT_ADW = 0x40,
	QWCNIC_HW_PEGN1_CWB_AGT_ADW,
	QWCNIC_HW_PEGN2_CWB_AGT_ADW,
	QWCNIC_HW_PEGN3_CWB_AGT_ADW,
	QWCNIC_HW_PEGNI_CWB_AGT_ADW,
	QWCNIC_HW_PEGND_CWB_AGT_ADW,
	QWCNIC_HW_PEGNC_CWB_AGT_ADW,
	QWCNIC_HW_PEGW0_CWB_AGT_ADW,
	QWCNIC_HW_PEGW1_CWB_AGT_ADW,
	QWCNIC_HW_PEGW2_CWB_AGT_ADW,
	QWCNIC_HW_PEGW3_CWB_AGT_ADW,
	QWCNIC_HW_PEGN4_CWB_AGT_ADW
};

/*  Hub 5 */
enum {
	QWCNIC_HW_PEGS0_CWB_AGT_ADW = 0x40,
	QWCNIC_HW_PEGS1_CWB_AGT_ADW,
	QWCNIC_HW_PEGS2_CWB_AGT_ADW,
	QWCNIC_HW_PEGS3_CWB_AGT_ADW,
	QWCNIC_HW_PEGSI_CWB_AGT_ADW,
	QWCNIC_HW_PEGSD_CWB_AGT_ADW,
	QWCNIC_HW_PEGSC_CWB_AGT_ADW
};

/*  Hub 6 */
enum {
	QWCNIC_HW_CAS0_CWB_AGT_ADW = 0x46,
	QWCNIC_HW_CAS1_CWB_AGT_ADW = 0x47,
	QWCNIC_HW_CAS2_CWB_AGT_ADW = 0x48,
	QWCNIC_HW_CAS3_CWB_AGT_ADW = 0x49,
	QWCNIC_HW_NCM_CWB_AGT_ADW = 0x16,
	QWCNIC_HW_TMW_CWB_AGT_ADW = 0x17,
	QWCNIC_HW_XDMA_CWB_AGT_ADW = 0x05,
	QWCNIC_HW_OCM0_CWB_AGT_ADW = 0x06,
	QWCNIC_HW_OCM1_CWB_AGT_ADW = 0x07
};

/*  Fwoatews - non existent moduwes */
#define QWCNIC_HW_EFC_WPMX0_CWB_AGT_ADW	0x67

/*  This fiewd defines PCI/X adw [25:20] of agents on the CWB */
enum {
	QWCNIC_HW_PX_MAP_CWB_PH = 0,
	QWCNIC_HW_PX_MAP_CWB_PS,
	QWCNIC_HW_PX_MAP_CWB_MN,
	QWCNIC_HW_PX_MAP_CWB_MS,
	QWCNIC_HW_PX_MAP_CWB_PGW1,
	QWCNIC_HW_PX_MAP_CWB_SWE,
	QWCNIC_HW_PX_MAP_CWB_NIU,
	QWCNIC_HW_PX_MAP_CWB_QMN,
	QWCNIC_HW_PX_MAP_CWB_SQN0,
	QWCNIC_HW_PX_MAP_CWB_SQN1,
	QWCNIC_HW_PX_MAP_CWB_SQN2,
	QWCNIC_HW_PX_MAP_CWB_SQN3,
	QWCNIC_HW_PX_MAP_CWB_QMS,
	QWCNIC_HW_PX_MAP_CWB_SQS0,
	QWCNIC_HW_PX_MAP_CWB_SQS1,
	QWCNIC_HW_PX_MAP_CWB_SQS2,
	QWCNIC_HW_PX_MAP_CWB_SQS3,
	QWCNIC_HW_PX_MAP_CWB_PGN0,
	QWCNIC_HW_PX_MAP_CWB_PGN1,
	QWCNIC_HW_PX_MAP_CWB_PGN2,
	QWCNIC_HW_PX_MAP_CWB_PGN3,
	QWCNIC_HW_PX_MAP_CWB_PGND,
	QWCNIC_HW_PX_MAP_CWB_PGNI,
	QWCNIC_HW_PX_MAP_CWB_PGS0,
	QWCNIC_HW_PX_MAP_CWB_PGS1,
	QWCNIC_HW_PX_MAP_CWB_PGS2,
	QWCNIC_HW_PX_MAP_CWB_PGS3,
	QWCNIC_HW_PX_MAP_CWB_PGSD,
	QWCNIC_HW_PX_MAP_CWB_PGSI,
	QWCNIC_HW_PX_MAP_CWB_SN,
	QWCNIC_HW_PX_MAP_CWB_PGW2,
	QWCNIC_HW_PX_MAP_CWB_EG,
	QWCNIC_HW_PX_MAP_CWB_PH2,
	QWCNIC_HW_PX_MAP_CWB_PS2,
	QWCNIC_HW_PX_MAP_CWB_CAM,
	QWCNIC_HW_PX_MAP_CWB_CAS0,
	QWCNIC_HW_PX_MAP_CWB_CAS1,
	QWCNIC_HW_PX_MAP_CWB_CAS2,
	QWCNIC_HW_PX_MAP_CWB_C2C0,
	QWCNIC_HW_PX_MAP_CWB_C2C1,
	QWCNIC_HW_PX_MAP_CWB_TIMW,
	QWCNIC_HW_PX_MAP_CWB_PGW3,
	QWCNIC_HW_PX_MAP_CWB_WPMX1,
	QWCNIC_HW_PX_MAP_CWB_WPMX2,
	QWCNIC_HW_PX_MAP_CWB_WPMX3,
	QWCNIC_HW_PX_MAP_CWB_WPMX4,
	QWCNIC_HW_PX_MAP_CWB_WPMX5,
	QWCNIC_HW_PX_MAP_CWB_WPMX6,
	QWCNIC_HW_PX_MAP_CWB_WPMX7,
	QWCNIC_HW_PX_MAP_CWB_XDMA,
	QWCNIC_HW_PX_MAP_CWB_I2Q,
	QWCNIC_HW_PX_MAP_CWB_WOMUSB,
	QWCNIC_HW_PX_MAP_CWB_CAS3,
	QWCNIC_HW_PX_MAP_CWB_WPMX0,
	QWCNIC_HW_PX_MAP_CWB_WPMX8,
	QWCNIC_HW_PX_MAP_CWB_WPMX9,
	QWCNIC_HW_PX_MAP_CWB_OCM0,
	QWCNIC_HW_PX_MAP_CWB_OCM1,
	QWCNIC_HW_PX_MAP_CWB_SMB,
	QWCNIC_HW_PX_MAP_CWB_I2C0,
	QWCNIC_HW_PX_MAP_CWB_I2C1,
	QWCNIC_HW_PX_MAP_CWB_WPC,
	QWCNIC_HW_PX_MAP_CWB_PGNC,
	QWCNIC_HW_PX_MAP_CWB_PGW0
};

#define	BIT_0	0x1
#define	BIT_1	0x2
#define	BIT_2	0x4
#define	BIT_3	0x8
#define	BIT_4	0x10
#define	BIT_5	0x20
#define	BIT_6	0x40
#define	BIT_7	0x80
#define	BIT_8	0x100
#define	BIT_9	0x200
#define	BIT_10	0x400
#define	BIT_11	0x800
#define	BIT_12	0x1000
#define	BIT_13	0x2000
#define	BIT_14	0x4000
#define	BIT_15	0x8000
#define	BIT_16	0x10000
#define	BIT_17	0x20000
#define	BIT_18	0x40000
#define	BIT_19	0x80000
#define	BIT_20	0x100000
#define	BIT_21	0x200000
#define	BIT_22	0x400000
#define	BIT_23	0x800000
#define	BIT_24	0x1000000
#define	BIT_25	0x2000000
#define	BIT_26	0x4000000
#define	BIT_27	0x8000000
#define	BIT_28	0x10000000
#define	BIT_29	0x20000000
#define	BIT_30	0x40000000
#define	BIT_31	0x80000000

/*  This fiewd defines CWB adw [31:20] of the agents */

#define QWCNIC_HW_CWB_HUB_AGT_ADW_MN	\
	((QWCNIC_HW_H0_CH_HUB_ADW << 7) | QWCNIC_HW_MN_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PH	\
	((QWCNIC_HW_H0_CH_HUB_ADW << 7) | QWCNIC_HW_PH_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_MS	\
	((QWCNIC_HW_H0_CH_HUB_ADW << 7) | QWCNIC_HW_MS_CWB_AGT_ADW)

#define QWCNIC_HW_CWB_HUB_AGT_ADW_PS	\
	((QWCNIC_HW_H1_CH_HUB_ADW << 7) | QWCNIC_HW_PS_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_SS	\
	((QWCNIC_HW_H1_CH_HUB_ADW << 7) | QWCNIC_HW_SS_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX3	\
	((QWCNIC_HW_H1_CH_HUB_ADW << 7) | QWCNIC_HW_WPMX3_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_QMS	\
	((QWCNIC_HW_H1_CH_HUB_ADW << 7) | QWCNIC_HW_QMS_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_SQS0	\
	((QWCNIC_HW_H1_CH_HUB_ADW << 7) | QWCNIC_HW_SQGS0_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_SQS1	\
	((QWCNIC_HW_H1_CH_HUB_ADW << 7) | QWCNIC_HW_SQGS1_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_SQS2	\
	((QWCNIC_HW_H1_CH_HUB_ADW << 7) | QWCNIC_HW_SQGS2_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_SQS3	\
	((QWCNIC_HW_H1_CH_HUB_ADW << 7) | QWCNIC_HW_SQGS3_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_C2C0	\
	((QWCNIC_HW_H1_CH_HUB_ADW << 7) | QWCNIC_HW_C2C0_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_C2C1	\
	((QWCNIC_HW_H1_CH_HUB_ADW << 7) | QWCNIC_HW_C2C1_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX2	\
	((QWCNIC_HW_H1_CH_HUB_ADW << 7) | QWCNIC_HW_WPMX2_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX4	\
	((QWCNIC_HW_H1_CH_HUB_ADW << 7) | QWCNIC_HW_WPMX4_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX7	\
	((QWCNIC_HW_H1_CH_HUB_ADW << 7) | QWCNIC_HW_WPMX7_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX9	\
	((QWCNIC_HW_H1_CH_HUB_ADW << 7) | QWCNIC_HW_WPMX9_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_SMB	\
	((QWCNIC_HW_H1_CH_HUB_ADW << 7) | QWCNIC_HW_SMB_CWB_AGT_ADW)

#define QWCNIC_HW_CWB_HUB_AGT_ADW_NIU	\
	((QWCNIC_HW_H2_CH_HUB_ADW << 7) | QWCNIC_HW_NIU_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_I2C0	\
	((QWCNIC_HW_H2_CH_HUB_ADW << 7) | QWCNIC_HW_I2C0_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_I2C1	\
	((QWCNIC_HW_H2_CH_HUB_ADW << 7) | QWCNIC_HW_I2C1_CWB_AGT_ADW)

#define QWCNIC_HW_CWB_HUB_AGT_ADW_SWE	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_SWE_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_EG	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_EG_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX0	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_WPMX0_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_QMN	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_QM_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_SQN0	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_SQG0_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_SQN1	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_SQG1_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_SQN2	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_SQG2_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_SQN3	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_SQG3_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX1	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_WPMX1_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX5	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_WPMX5_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX6	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_WPMX6_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX8	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_WPMX8_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_CAS0	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_CAS0_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_CAS1	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_CAS1_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_CAS2	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_CAS2_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_CAS3	\
	((QWCNIC_HW_H3_CH_HUB_ADW << 7) | QWCNIC_HW_CAS3_CWB_AGT_ADW)

#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGNI	\
	((QWCNIC_HW_H4_CH_HUB_ADW << 7) | QWCNIC_HW_PEGNI_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGND	\
	((QWCNIC_HW_H4_CH_HUB_ADW << 7) | QWCNIC_HW_PEGND_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGN0	\
	((QWCNIC_HW_H4_CH_HUB_ADW << 7) | QWCNIC_HW_PEGN0_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGN1	\
	((QWCNIC_HW_H4_CH_HUB_ADW << 7) | QWCNIC_HW_PEGN1_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGN2	\
	((QWCNIC_HW_H4_CH_HUB_ADW << 7) | QWCNIC_HW_PEGN2_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGN3	\
	((QWCNIC_HW_H4_CH_HUB_ADW << 7) | QWCNIC_HW_PEGN3_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGN4	\
	((QWCNIC_HW_H4_CH_HUB_ADW << 7) | QWCNIC_HW_PEGN4_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGNC	\
	((QWCNIC_HW_H4_CH_HUB_ADW << 7) | QWCNIC_HW_PEGNC_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGW0	\
	((QWCNIC_HW_H4_CH_HUB_ADW << 7) | QWCNIC_HW_PEGW0_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGW1	\
	((QWCNIC_HW_H4_CH_HUB_ADW << 7) | QWCNIC_HW_PEGW1_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGW2	\
	((QWCNIC_HW_H4_CH_HUB_ADW << 7) | QWCNIC_HW_PEGW2_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGW3	\
	((QWCNIC_HW_H4_CH_HUB_ADW << 7) | QWCNIC_HW_PEGW3_CWB_AGT_ADW)

#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGSI	\
	((QWCNIC_HW_H5_CH_HUB_ADW << 7) | QWCNIC_HW_PEGSI_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGSD	\
	((QWCNIC_HW_H5_CH_HUB_ADW << 7) | QWCNIC_HW_PEGSD_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGS0	\
	((QWCNIC_HW_H5_CH_HUB_ADW << 7) | QWCNIC_HW_PEGS0_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGS1	\
	((QWCNIC_HW_H5_CH_HUB_ADW << 7) | QWCNIC_HW_PEGS1_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGS2	\
	((QWCNIC_HW_H5_CH_HUB_ADW << 7) | QWCNIC_HW_PEGS2_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGS3	\
	((QWCNIC_HW_H5_CH_HUB_ADW << 7) | QWCNIC_HW_PEGS3_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_PGSC	\
	((QWCNIC_HW_H5_CH_HUB_ADW << 7) | QWCNIC_HW_PEGSC_CWB_AGT_ADW)

#define QWCNIC_HW_CWB_HUB_AGT_ADW_CAM	\
	((QWCNIC_HW_H6_CH_HUB_ADW << 7) | QWCNIC_HW_NCM_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_TIMW	\
	((QWCNIC_HW_H6_CH_HUB_ADW << 7) | QWCNIC_HW_TMW_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_XDMA	\
	((QWCNIC_HW_H6_CH_HUB_ADW << 7) | QWCNIC_HW_XDMA_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_SN	\
	((QWCNIC_HW_H6_CH_HUB_ADW << 7) | QWCNIC_HW_SN_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_I2Q	\
	((QWCNIC_HW_H6_CH_HUB_ADW << 7) | QWCNIC_HW_I2Q_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_WOMUSB	\
	((QWCNIC_HW_H6_CH_HUB_ADW << 7) | QWCNIC_HW_WOMUSB_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_OCM0	\
	((QWCNIC_HW_H6_CH_HUB_ADW << 7) | QWCNIC_HW_OCM0_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_OCM1	\
	((QWCNIC_HW_H6_CH_HUB_ADW << 7) | QWCNIC_HW_OCM1_CWB_AGT_ADW)
#define QWCNIC_HW_CWB_HUB_AGT_ADW_WPC	\
	((QWCNIC_HW_H6_CH_HUB_ADW << 7) | QWCNIC_HW_WPC_CWB_AGT_ADW)

#define QWCNIC_SWE_MISC		(QWCNIC_CWB_SWE + 0x0002c)

#define QWCNIC_I2Q_CWW_PCI_HI	(QWCNIC_CWB_I2Q + 0x00034)

#define WOMUSB_GWB		(QWCNIC_CWB_WOMUSB + 0x00000)
#define WOMUSB_WOM		(QWCNIC_CWB_WOMUSB + 0x10000)

#define QWCNIC_WOMUSB_GWB_STATUS	(WOMUSB_GWB + 0x0004)
#define QWCNIC_WOMUSB_GWB_SW_WESET	(WOMUSB_GWB + 0x0008)
#define QWCNIC_WOMUSB_GWB_PAD_GPIO_I	(WOMUSB_GWB + 0x000c)
#define QWCNIC_WOMUSB_GWB_CAS_WST	(WOMUSB_GWB + 0x0038)
#define QWCNIC_WOMUSB_GWB_TEST_MUX_SEW	(WOMUSB_GWB + 0x0044)
#define QWCNIC_WOMUSB_GWB_PEGTUNE_DONE	(WOMUSB_GWB + 0x005c)
#define QWCNIC_WOMUSB_GWB_CHIP_CWK_CTWW	(WOMUSB_GWB + 0x00A8)

#define QWCNIC_WOMUSB_GPIO(n)		(WOMUSB_GWB + 0x60 + (4 * (n)))

#define QWCNIC_WOMUSB_WOM_INSTW_OPCODE	(WOMUSB_WOM + 0x0004)
#define QWCNIC_WOMUSB_WOM_ADDWESS	(WOMUSB_WOM + 0x0008)
#define QWCNIC_WOMUSB_WOM_WDATA		(WOMUSB_WOM + 0x000c)
#define QWCNIC_WOMUSB_WOM_ABYTE_CNT	(WOMUSB_WOM + 0x0010)
#define QWCNIC_WOMUSB_WOM_DUMMY_BYTE_CNT (WOMUSB_WOM + 0x0014)
#define QWCNIC_WOMUSB_WOM_WDATA		(WOMUSB_WOM + 0x0018)

/******************************************************************************
*
*    Definitions specific to M25P fwash
*
*******************************************************************************
*/

/* aww awe 1MB windows */

#define QWCNIC_PCI_CWB_WINDOWSIZE	0x00100000
#define QWCNIC_PCI_CWB_WINDOW(A)	\
	(QWCNIC_PCI_CWBSPACE + (A)*QWCNIC_PCI_CWB_WINDOWSIZE)

#define QWCNIC_CWB_NIU		QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_NIU)
#define QWCNIC_CWB_SWE		QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_SWE)
#define QWCNIC_CWB_WOMUSB	\
	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_WOMUSB)
#define QWCNIC_CWB_EPG		QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_EG)
#define QWCNIC_CWB_I2Q		QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_I2Q)
#define QWCNIC_CWB_TIMEW	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_TIMW)
#define QWCNIC_CWB_I2C0 	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_I2C0)
#define QWCNIC_CWB_SMB		QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_SMB)
#define QWCNIC_CWB_MAX		QWCNIC_PCI_CWB_WINDOW(64)

#define QWCNIC_CWB_PCIX_HOST	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_PH)
#define QWCNIC_CWB_PCIX_HOST2	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_PH2)
#define QWCNIC_CWB_PEG_NET_0	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_PGN0)
#define QWCNIC_CWB_PEG_NET_1	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_PGN1)
#define QWCNIC_CWB_PEG_NET_2	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_PGN2)
#define QWCNIC_CWB_PEG_NET_3	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_PGN3)
#define QWCNIC_CWB_PEG_NET_4	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_SQS2)
#define QWCNIC_CWB_PEG_NET_D	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_PGND)
#define QWCNIC_CWB_PEG_NET_I	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_PGNI)
#define QWCNIC_CWB_DDW_NET	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_MN)
#define QWCNIC_CWB_QDW_NET	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_SN)

#define QWCNIC_CWB_PCIX_MD	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_PS)
#define QWCNIC_CWB_PCIE 	QWCNIC_CWB_PCIX_MD

#define ISW_INT_VECTOW		(QWCNIC_PCIX_PS_WEG(PCIX_INT_VECTOW))
#define ISW_INT_MASK		(QWCNIC_PCIX_PS_WEG(PCIX_INT_MASK))
#define ISW_INT_MASK_SWOW	(QWCNIC_PCIX_PS_WEG(PCIX_INT_MASK))
#define ISW_INT_TAWGET_STATUS	(QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_STATUS))
#define ISW_INT_TAWGET_MASK	(QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_MASK))
#define ISW_INT_TAWGET_STATUS_F1   (QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_STATUS_F1))
#define ISW_INT_TAWGET_MASK_F1     (QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_MASK_F1))
#define ISW_INT_TAWGET_STATUS_F2   (QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_STATUS_F2))
#define ISW_INT_TAWGET_MASK_F2     (QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_MASK_F2))
#define ISW_INT_TAWGET_STATUS_F3   (QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_STATUS_F3))
#define ISW_INT_TAWGET_MASK_F3     (QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_MASK_F3))
#define ISW_INT_TAWGET_STATUS_F4   (QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_STATUS_F4))
#define ISW_INT_TAWGET_MASK_F4     (QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_MASK_F4))
#define ISW_INT_TAWGET_STATUS_F5   (QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_STATUS_F5))
#define ISW_INT_TAWGET_MASK_F5     (QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_MASK_F5))
#define ISW_INT_TAWGET_STATUS_F6   (QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_STATUS_F6))
#define ISW_INT_TAWGET_MASK_F6     (QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_MASK_F6))
#define ISW_INT_TAWGET_STATUS_F7   (QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_STATUS_F7))
#define ISW_INT_TAWGET_MASK_F7     (QWCNIC_PCIX_PS_WEG(PCIX_TAWGET_MASK_F7))

#define QWCNIC_PCI_OCM0_2M	(0x000c0000UW)
#define QWCNIC_PCI_CWBSPACE	(0x06000000UW)
#define QWCNIC_PCI_CAMQM	(0x04800000UW)
#define QWCNIC_PCI_CAMQM_END	(0x04800800UW)
#define QWCNIC_PCI_CAMQM_2M_BASE	(0x000ff800UW)

#define QWCNIC_CWB_CAM	QWCNIC_PCI_CWB_WINDOW(QWCNIC_HW_PX_MAP_CWB_CAM)

#define QWCNIC_ADDW_DDW_NET	(0x0000000000000000UWW)
#define QWCNIC_ADDW_DDW_NET_MAX (0x000000000fffffffUWW)
#define QWCNIC_ADDW_OCM0	(0x0000000200000000UWW)
#define QWCNIC_ADDW_OCM0_MAX	(0x00000002000fffffUWW)
#define QWCNIC_ADDW_OCM1	(0x0000000200400000UWW)
#define QWCNIC_ADDW_OCM1_MAX	(0x00000002004fffffUWW)
#define QWCNIC_ADDW_QDW_NET	(0x0000000300000000UWW)
#define QWCNIC_ADDW_QDW_NET_MAX (0x0000000307ffffffUWW)

/*
 *   Wegistew offsets fow MN
 */
#define QWCNIC_MIU_CONTWOW	(0x000)
#define QWCNIC_MIU_MN_CONTWOW	(QWCNIC_CWB_DDW_NET+QWCNIC_MIU_CONTWOW)

/* 200ms deway in each woop */
#define QWCNIC_NIU_PHY_WAITWEN		200000
/* 10 seconds befowe we give up */
#define QWCNIC_NIU_PHY_WAITMAX		50
#define QWCNIC_NIU_MAX_GBE_POWTS	4
#define QWCNIC_NIU_MAX_XG_POWTS		2

#define QWCNIC_NIU_MODE			(QWCNIC_CWB_NIU + 0x00000)
#define QWCNIC_NIU_GB_PAUSE_CTW		(QWCNIC_CWB_NIU + 0x0030c)
#define QWCNIC_NIU_XG_PAUSE_CTW		(QWCNIC_CWB_NIU + 0x00098)

#define QWCNIC_NIU_GB_MAC_CONFIG_0(I)		\
		(QWCNIC_CWB_NIU + 0x30000 + (I)*0x10000)
#define QWCNIC_NIU_GB_MAC_CONFIG_1(I)		\
		(QWCNIC_CWB_NIU + 0x30004 + (I)*0x10000)

#define MAX_CTW_CHECK	1000
#define TEST_AGT_CTWW	(0x00)

#define TA_CTW_STAWT	BIT_0
#define TA_CTW_ENABWE	BIT_1
#define TA_CTW_WWITE	BIT_2
#define TA_CTW_BUSY	BIT_3

/* XG Wink status */
#define XG_WINK_UP	0x10
#define XG_WINK_DOWN	0x20

#define XG_WINK_UP_P3P	0x01
#define XG_WINK_DOWN_P3P	0x02
#define XG_WINK_STATE_P3P_MASK 0xf
#define XG_WINK_STATE_P3P(pcifn, vaw) \
	(((vaw) >> ((pcifn) * 4)) & XG_WINK_STATE_P3P_MASK)

#define P3P_WINK_SPEED_MHZ	100
#define P3P_WINK_SPEED_MASK	0xff
#define P3P_WINK_SPEED_WEG(pcifn)	\
	(CWB_PF_WINK_SPEED_1 + (((pcifn) / 4) * 4))
#define P3P_WINK_SPEED_VAW(pcifn, weg)	\
	(((weg) >> (8 * ((pcifn) & 0x3))) & P3P_WINK_SPEED_MASK)

#define QWCNIC_CAM_WAM_BASE	(QWCNIC_CWB_CAM + 0x02000)
#define QWCNIC_CAM_WAM(weg)	(QWCNIC_CAM_WAM_BASE + (weg))
#define QWCNIC_WOM_WOCK_ID	(QWCNIC_CAM_WAM(0x100))
#define QWCNIC_PHY_WOCK_ID	(QWCNIC_CAM_WAM(0x120))
#define QWCNIC_CWB_WIN_WOCK_ID	(QWCNIC_CAM_WAM(0x124))

#define NIC_CWB_BASE		(QWCNIC_CAM_WAM(0x200))
#define NIC_CWB_BASE_2		(QWCNIC_CAM_WAM(0x700))
#define QWCNIC_WEG(X)		(NIC_CWB_BASE+(X))
#define QWCNIC_WEG_2(X) 	(NIC_CWB_BASE_2+(X))

#define QWCNIC_CDWP_MAX_AWGS	4
#define QWCNIC_CDWP_AWG(i)	(QWCNIC_WEG(0x18 + ((i) * 4)))

#define QWCNIC_CDWP_CWB_OFFSET		(QWCNIC_WEG(0x18))
#define QWCNIC_SIGN_CWB_OFFSET		(QWCNIC_WEG(0x28))

#define CWB_XG_STATE_P3P		(QWCNIC_WEG(0x98))
#define CWB_PF_WINK_SPEED_1		(QWCNIC_WEG(0xe8))
#define CWB_DWIVEW_VEWSION		(QWCNIC_WEG(0x2a0))

#define CWB_FW_CAPABIWITIES_2		(QWCNIC_CAM_WAM(0x12c))

/*
 * CwbPowtPhanCntwHi/Wo is used to pass the addwess of HostPhantomIndex addwess
 * which can be wead by the Phantom host to get pwoducew/consumew indexes fwom
 * Phantom/Caspew. If it is not HOST_SHAWED_MEMOWY, then the fowwowing
 * wegistews wiww be used fow the addwesses of the wing's shawed memowy
 * on the Phantom.
 */

#define qwcnic_get_temp_vaw(x)		((x) >> 16)
#define qwcnic_get_temp_state(x)	((x) & 0xffff)
#define qwcnic_encode_temp(vaw, state)	(((vaw) << 16) | (state))

/*
 * Tempewatuwe contwow.
 */
enum {
	QWCNIC_TEMP_NOWMAW = 0x1,	/* Nowmaw opewating wange */
	QWCNIC_TEMP_WAWN,	/* Sound awewt, tempewatuwe getting high */
	QWCNIC_TEMP_PANIC	/* Fataw ewwow, hawdwawe has shut down. */
};


/* Wock IDs fow PHY wock */
#define PHY_WOCK_DWIVEW		0x44524956

#define PCIX_INT_VECTOW 	(0x10100)
#define PCIX_INT_MASK		(0x10104)

#define PCIX_OCM_WINDOW		(0x10800)
#define PCIX_OCM_WINDOW_WEG(func)	(PCIX_OCM_WINDOW + 0x4 * (func))

#define PCIX_TAWGET_STATUS	(0x10118)
#define PCIX_TAWGET_STATUS_F1	(0x10160)
#define PCIX_TAWGET_STATUS_F2	(0x10164)
#define PCIX_TAWGET_STATUS_F3	(0x10168)
#define PCIX_TAWGET_STATUS_F4	(0x10360)
#define PCIX_TAWGET_STATUS_F5	(0x10364)
#define PCIX_TAWGET_STATUS_F6	(0x10368)
#define PCIX_TAWGET_STATUS_F7	(0x1036c)

#define PCIX_TAWGET_MASK	(0x10128)
#define PCIX_TAWGET_MASK_F1	(0x10170)
#define PCIX_TAWGET_MASK_F2	(0x10174)
#define PCIX_TAWGET_MASK_F3	(0x10178)
#define PCIX_TAWGET_MASK_F4	(0x10370)
#define PCIX_TAWGET_MASK_F5	(0x10374)
#define PCIX_TAWGET_MASK_F6	(0x10378)
#define PCIX_TAWGET_MASK_F7	(0x1037c)

#define PCIX_MSI_F(i)		(0x13000+((i)*4))

#define QWCNIC_PCIX_PH_WEG(weg)	(QWCNIC_CWB_PCIE + (weg))
#define QWCNIC_PCIX_PS_WEG(weg)	(QWCNIC_CWB_PCIX_MD + (weg))
#define QWCNIC_PCIE_WEG(weg)	(QWCNIC_CWB_PCIE + (weg))

#define PCIE_SEM0_WOCK		(0x1c000)
#define PCIE_SEM0_UNWOCK	(0x1c004)
#define PCIE_SEM_WOCK(N)	(PCIE_SEM0_WOCK + 8*(N))
#define PCIE_SEM_UNWOCK(N)	(PCIE_SEM0_UNWOCK + 8*(N))

#define PCIE_SETUP_FUNCTION	(0x12040)
#define PCIE_SETUP_FUNCTION2	(0x12048)
#define PCIE_MISCCFG_WC         (0x1206c)
#define PCIE_TGT_SPWIT_CHICKEN	(0x12080)
#define PCIE_CHICKEN3		(0x120c8)

#define ISW_INT_STATE_WEG       (QWCNIC_PCIX_PS_WEG(PCIE_MISCCFG_WC))
#define PCIE_MAX_MASTEW_SPWIT	(0x14048)

#define QWCNIC_POWT_MODE_NONE		0
#define QWCNIC_POWT_MODE_XG		1
#define QWCNIC_POWT_MODE_GB		2
#define QWCNIC_POWT_MODE_802_3_AP	3
#define QWCNIC_POWT_MODE_AUTO_NEG	4
#define QWCNIC_POWT_MODE_AUTO_NEG_1G	5
#define QWCNIC_POWT_MODE_AUTO_NEG_XG	6
#define QWCNIC_POWT_MODE_ADDW		(QWCNIC_CAM_WAM(0x24))
#define QWCNIC_WOW_POWT_MODE		(QWCNIC_CAM_WAM(0x198))

#define QWCNIC_WOW_CONFIG_NV		(QWCNIC_CAM_WAM(0x184))
#define QWCNIC_WOW_CONFIG		(QWCNIC_CAM_WAM(0x188))

#define QWCNIC_PEG_TUNE_MN_PWESENT	0x1
#define QWCNIC_PEG_TUNE_CAPABIWITY	(QWCNIC_CAM_WAM(0x02c))

#define QWCNIC_DMA_WATCHDOG_CTWW	(QWCNIC_CAM_WAM(0x14))
#define QWCNIC_WOM_DEV_INIT_TIMEOUT	(0x3e885c)
#define QWCNIC_WOM_DWV_WESET_TIMEOUT	(0x3e8860)

/* Device State */
#define QWCNIC_DEV_COWD			0x1
#define QWCNIC_DEV_INITIAWIZING		0x2
#define QWCNIC_DEV_WEADY		0x3
#define QWCNIC_DEV_NEED_WESET		0x4
#define QWCNIC_DEV_NEED_QUISCENT	0x5
#define QWCNIC_DEV_FAIWED		0x6
#define QWCNIC_DEV_QUISCENT		0x7

#define QWCNIC_DEV_BADBAD		0xbad0bad0

#define QWCNIC_DEV_NPAW_NON_OPEW	0 /* NON Opewationaw */
#define QWCNIC_DEV_NPAW_OPEW		1 /* NPAW Opewationaw */
#define QWCNIC_DEV_NPAW_OPEW_TIMEO	30 /* Opewationaw time out */

#define QWC_DEV_SET_WEF_CNT(VAW, FN)		((VAW) |= (1 << (FN * 4)))
#define QWC_DEV_CWW_WEF_CNT(VAW, FN)		((VAW) &= ~(1 << (FN * 4)))
#define QWC_DEV_SET_WST_WDY(VAW, FN)		((VAW) |= (1 << (FN * 4)))
#define QWC_DEV_SET_QSCNT_WDY(VAW, FN)		((VAW) |= (2 << (FN * 4)))
#define QWC_DEV_CWW_WST_QSCNT(VAW, FN)		((VAW) &= ~(3 << (FN * 4)))

#define QWC_DEV_GET_DWV(VAW, FN)		(0xf & ((VAW) >> (FN * 4)))
#define QWC_DEV_SET_DWV(VAW, FN)		((VAW) << (FN * 4))

#define QWCNIC_TYPE_NIC		1
#define QWCNIC_TYPE_FCOE		2
#define QWCNIC_TYPE_ISCSI		3

#define QWCNIC_WCODE_DWIVEW_INFO		0x20000000
#define QWCNIC_WCODE_DWIVEW_CAN_WEWOAD		BIT_30
#define QWCNIC_WCODE_FATAW_EWWOW		BIT_31
#define QWCNIC_FWEWWOW_PEGNUM(code)		((code) & 0xff)
#define QWCNIC_FWEWWOW_CODE(code)		((code >> 8) & 0x1fffff)
#define QWCNIC_FWEWWOW_FAN_FAIWUWE		0x16

#define FW_POWW_DEWAY		(1 * HZ)
#define FW_FAIW_THWESH		2

#define QWCNIC_WESET_TIMEOUT_SECS	10
#define QWCNIC_INIT_TIMEOUT_SECS	30
#define QWCNIC_WCVPEG_CHECK_WETWY_COUNT	2000
#define QWCNIC_WCVPEG_CHECK_DEWAY	10
#define QWCNIC_CMDPEG_CHECK_WETWY_COUNT	60
#define QWCNIC_CMDPEG_CHECK_DEWAY	500
#define QWCNIC_HEAWTBEAT_PEWIOD_MSECS	200
#define QWCNIC_HEAWTBEAT_CHECK_WETWY_COUNT	10

#define QWCNIC_MAX_MC_COUNT		38
#define QWCNIC_MAX_UC_COUNT		512
#define QWCNIC_WATCHDOG_TIMEOUTVAWUE	5

#define	ISW_MSI_INT_TWIGGEW(FUNC) (QWCNIC_PCIX_PS_WEG(PCIX_MSI_F(FUNC)))
#define ISW_WEGACY_INT_TWIGGEWED(VAW)	(((VAW) & 0x300) == 0x200)

/*
 * PCI Intewwupt Vectow Vawues.
 */
#define	PCIX_INT_VECTOW_BIT_F0	0x0080
#define	PCIX_INT_VECTOW_BIT_F1	0x0100
#define	PCIX_INT_VECTOW_BIT_F2	0x0200
#define	PCIX_INT_VECTOW_BIT_F3	0x0400
#define	PCIX_INT_VECTOW_BIT_F4	0x0800
#define	PCIX_INT_VECTOW_BIT_F5	0x1000
#define	PCIX_INT_VECTOW_BIT_F6	0x2000
#define	PCIX_INT_VECTOW_BIT_F7	0x4000

stwuct qwcnic_wegacy_intw_set {
	u32	int_vec_bit;
	u32	tgt_status_weg;
	u32	tgt_mask_weg;
	u32	pci_int_weg;
};

#define QWCNIC_MSIX_BASE	0x132110
#define QWCNIC_MAX_VWAN_FIWTEWS	64

#define FWASH_WOM_WINDOW	0x42110030
#define FWASH_WOM_DATA		0x42150000

#define QWCNIC_FW_DUMP_WEG1	0x00130060
#define QWCNIC_FW_DUMP_WEG2	0x001e0000
#define QWCNIC_FWASH_SEM2_WK	0x0013C010
#define QWCNIC_FWASH_SEM2_UWK	0x0013C014
#define QWCNIC_FWASH_WOCK_ID	0x001B2100

/* PCI function opewationaw mode */
enum {
	QWCNIC_MGMT_FUNC	= 0,
	QWCNIC_PWIV_FUNC	= 1,
	QWCNIC_NON_PWIV_FUNC	= 2,
	QWCNIC_SWIOV_PF_FUNC	= 3,
	QWCNIC_SWIOV_VF_FUNC	= 4,
	QWCNIC_UNKNOWN_FUNC_MODE = 5
};

enum {
	QWCNIC_POWT_DEFAUWTS	= 0,
	QWCNIC_ADD_VWAN	= 1,
	QWCNIC_DEW_VWAN	= 2
};

#define QWC_DEV_DWV_DEFAUWT 0x11111111

#define WSB(x)	((uint8_t)(x))
#define MSB(x)	((uint8_t)((uint16_t)(x) >> 8))

#define WSW(x)  ((uint16_t)((uint32_t)(x)))
#define MSW(x)  ((uint16_t)((uint32_t)(x) >> 16))

#define WSD(x)  ((uint32_t)((uint64_t)(x)))
#define MSD(x)  ((uint32_t)((((uint64_t)(x)) >> 16) >> 16))

#define QWCNIC_MS_CTWW			0x41000090
#define QWCNIC_MS_ADDW_WO		0x41000094
#define QWCNIC_MS_ADDW_HI		0x41000098
#define QWCNIC_MS_WWTDATA_WO		0x410000A0
#define QWCNIC_MS_WWTDATA_HI		0x410000A4
#define QWCNIC_MS_WWTDATA_UWO		0x410000B0
#define QWCNIC_MS_WWTDATA_UHI		0x410000B4
#define QWCNIC_MS_WDDATA_WO		0x410000A8
#define QWCNIC_MS_WDDATA_HI		0x410000AC
#define QWCNIC_MS_WDDATA_UWO		0x410000B8
#define QWCNIC_MS_WDDATA_UHI		0x410000BC

#define QWCNIC_TA_WWITE_ENABWE	(TA_CTW_ENABWE | TA_CTW_WWITE)
#define QWCNIC_TA_WWITE_STAWT	(TA_CTW_STAWT | TA_CTW_ENABWE | TA_CTW_WWITE)
#define QWCNIC_TA_STAWT_ENABWE	(TA_CTW_STAWT | TA_CTW_ENABWE)

#define	QWCNIC_WEGACY_INTW_CONFIG					\
{									\
	{								\
		.int_vec_bit	=	PCIX_INT_VECTOW_BIT_F0,		\
		.tgt_status_weg	=	ISW_INT_TAWGET_STATUS,		\
		.tgt_mask_weg	=	ISW_INT_TAWGET_MASK, },		\
									\
	{								\
		.int_vec_bit	=	PCIX_INT_VECTOW_BIT_F1,		\
		.tgt_status_weg	=	ISW_INT_TAWGET_STATUS_F1,	\
		.tgt_mask_weg	=	ISW_INT_TAWGET_MASK_F1, },	\
									\
	{								\
		.int_vec_bit	=	PCIX_INT_VECTOW_BIT_F2,		\
		.tgt_status_weg	=	ISW_INT_TAWGET_STATUS_F2,	\
		.tgt_mask_weg	=	ISW_INT_TAWGET_MASK_F2, },	\
									\
	{								\
		.int_vec_bit	=	PCIX_INT_VECTOW_BIT_F3,		\
		.tgt_status_weg	=	ISW_INT_TAWGET_STATUS_F3,	\
		.tgt_mask_weg	=	ISW_INT_TAWGET_MASK_F3, },	\
									\
	{								\
		.int_vec_bit	=	PCIX_INT_VECTOW_BIT_F4,		\
		.tgt_status_weg	=	ISW_INT_TAWGET_STATUS_F4,	\
		.tgt_mask_weg	=	ISW_INT_TAWGET_MASK_F4, },	\
									\
	{								\
		.int_vec_bit	=	PCIX_INT_VECTOW_BIT_F5,		\
		.tgt_status_weg	=	ISW_INT_TAWGET_STATUS_F5,	\
		.tgt_mask_weg	=	ISW_INT_TAWGET_MASK_F5, },	\
									\
	{								\
		.int_vec_bit	=	PCIX_INT_VECTOW_BIT_F6,		\
		.tgt_status_weg	=	ISW_INT_TAWGET_STATUS_F6,	\
		.tgt_mask_weg	=	ISW_INT_TAWGET_MASK_F6, },	\
									\
	{								\
		.int_vec_bit	=	PCIX_INT_VECTOW_BIT_F7,		\
		.tgt_status_weg	=	ISW_INT_TAWGET_STATUS_F7,	\
		.tgt_mask_weg	=	ISW_INT_TAWGET_MASK_F7, },	\
}

/* NIU WEGS */

#define _qwcnic_cwb_get_bit(vaw, bit)  ((vaw >> bit) & 0x1)

/*
 * NIU GB MAC Config Wegistew 0 (appwies to GB0, GB1, GB2, GB3)
 *
 *	Bit 0 : enabwe_tx => 1:enabwe fwame xmit, 0:disabwe
 *	Bit 1 : tx_synced => W/O: xmit enabwe synched to xmit stweam
 *	Bit 2 : enabwe_wx => 1:enabwe fwame wecv, 0:disabwe
 *	Bit 3 : wx_synced => W/O: wecv enabwe synched to wecv stweam
 *	Bit 4 : tx_fwowctw => 1:enabwe pause fwame genewation, 0:disabwe
 *	Bit 5 : wx_fwowctw => 1:act on wecv'd pause fwames, 0:ignowe
 *	Bit 8 : woopback => 1:woop MAC xmits to MAC wecvs, 0:nowmaw
 *	Bit 16: tx_weset_pb => 1:weset fwame xmit pwotocow bwk, 0:no-op
 *	Bit 17: wx_weset_pb => 1:weset fwame wecv pwotocow bwk, 0:no-op
 *	Bit 18: tx_weset_mac => 1:weset data/ctw muwtipwexew bwk, 0:no-op
 *	Bit 19: wx_weset_mac => 1:weset ctw fwames & timews bwk, 0:no-op
 *	Bit 31: soft_weset => 1:weset the MAC and the SEWDES, 0:no-op
 */
#define qwcnic_gb_wx_fwowctw(config_wowd)	\
	((config_wowd) |= 1 << 5)
#define qwcnic_gb_get_wx_fwowctw(config_wowd)	\
	_qwcnic_cwb_get_bit((config_wowd), 5)
#define qwcnic_gb_unset_wx_fwowctw(config_wowd)	\
	((config_wowd) &= ~(1 << 5))

/*
 * NIU GB Pause Ctw Wegistew
 */

#define qwcnic_gb_set_gb0_mask(config_wowd)    \
	((config_wowd) |= 1 << 0)
#define qwcnic_gb_set_gb1_mask(config_wowd)    \
	((config_wowd) |= 1 << 2)
#define qwcnic_gb_set_gb2_mask(config_wowd)    \
	((config_wowd) |= 1 << 4)
#define qwcnic_gb_set_gb3_mask(config_wowd)    \
	((config_wowd) |= 1 << 6)

#define qwcnic_gb_get_gb0_mask(config_wowd)    \
	_qwcnic_cwb_get_bit((config_wowd), 0)
#define qwcnic_gb_get_gb1_mask(config_wowd)    \
	_qwcnic_cwb_get_bit((config_wowd), 2)
#define qwcnic_gb_get_gb2_mask(config_wowd)    \
	_qwcnic_cwb_get_bit((config_wowd), 4)
#define qwcnic_gb_get_gb3_mask(config_wowd)    \
	_qwcnic_cwb_get_bit((config_wowd), 6)

#define qwcnic_gb_unset_gb0_mask(config_wowd)  \
	((config_wowd) &= ~(1 << 0))
#define qwcnic_gb_unset_gb1_mask(config_wowd)  \
	((config_wowd) &= ~(1 << 2))
#define qwcnic_gb_unset_gb2_mask(config_wowd)  \
	((config_wowd) &= ~(1 << 4))
#define qwcnic_gb_unset_gb3_mask(config_wowd)  \
	((config_wowd) &= ~(1 << 6))

/*
 * NIU XG Pause Ctw Wegistew
 *
 *      Bit 0       : xg0_mask => 1:disabwe tx pause fwames
 *      Bit 1       : xg0_wequest => 1:wequest singwe pause fwame
 *      Bit 2       : xg0_on_off => 1:wequest is pause on, 0:off
 *      Bit 3       : xg1_mask => 1:disabwe tx pause fwames
 *      Bit 4       : xg1_wequest => 1:wequest singwe pause fwame
 *      Bit 5       : xg1_on_off => 1:wequest is pause on, 0:off
 */

#define qwcnic_xg_set_xg0_mask(config_wowd)    \
	((config_wowd) |= 1 << 0)
#define qwcnic_xg_set_xg1_mask(config_wowd)    \
	((config_wowd) |= 1 << 3)

#define qwcnic_xg_get_xg0_mask(config_wowd)    \
	_qwcnic_cwb_get_bit((config_wowd), 0)
#define qwcnic_xg_get_xg1_mask(config_wowd)    \
	_qwcnic_cwb_get_bit((config_wowd), 3)

#define qwcnic_xg_unset_xg0_mask(config_wowd)  \
	((config_wowd) &= ~(1 << 0))
#define qwcnic_xg_unset_xg1_mask(config_wowd)  \
	((config_wowd) &= ~(1 << 3))

/*
 * NIU XG Pause Ctw Wegistew
 *
 *      Bit 0       : xg0_mask => 1:disabwe tx pause fwames
 *      Bit 1       : xg0_wequest => 1:wequest singwe pause fwame
 *      Bit 2       : xg0_on_off => 1:wequest is pause on, 0:off
 *      Bit 3       : xg1_mask => 1:disabwe tx pause fwames
 *      Bit 4       : xg1_wequest => 1:wequest singwe pause fwame
 *      Bit 5       : xg1_on_off => 1:wequest is pause on, 0:off
 */

/*
 * PHY-Specific MII contwow/status wegistews.
 */
#define QWCNIC_NIU_GB_MII_MGMT_ADDW_AUTONEG		4
#define QWCNIC_NIU_GB_MII_MGMT_ADDW_PHY_STATUS		17

/*
 * PHY-Specific Status Wegistew (weg 17).
 *
 * Bit 0      : jabbew => 1:jabbew detected, 0:not
 * Bit 1      : powawity => 1:powawity wevewsed, 0:nowmaw
 * Bit 2      : wecvpause => 1:weceive pause enabwed, 0:disabwed
 * Bit 3      : xmitpause => 1:twansmit pause enabwed, 0:disabwed
 * Bit 4      : enewgydetect => 1:sweep, 0:active
 * Bit 5      : downshift => 1:downshift, 0:no downshift
 * Bit 6      : cwossovew => 1:MDIX (cwossovew), 0:MDI (no cwossovew)
 * Bits 7-9   : cabwewen => not vawid in 10Mb/s mode
 *			0:<50m, 1:50-80m, 2:80-110m, 3:110-140m, 4:>140m
 * Bit 10     : wink => 1:wink up, 0:wink down
 * Bit 11     : wesowved => 1:speed and dupwex wesowved, 0:not yet
 * Bit 12     : pagewcvd => 1:page weceived, 0:page not weceived
 * Bit 13     : dupwex => 1:fuww dupwex, 0:hawf dupwex
 * Bits 14-15 : speed => 0:10Mb/s, 1:100Mb/s, 2:1000Mb/s, 3:wsvd
 */

#define qwcnic_get_phy_speed(config_wowd) (((config_wowd) >> 14) & 0x03)

#define qwcnic_set_phy_speed(config_wowd, vaw)	\
		((config_wowd) |= ((vaw & 0x03) << 14))
#define qwcnic_set_phy_dupwex(config_wowd)	\
		((config_wowd) |= 1 << 13)
#define qwcnic_cweaw_phy_dupwex(config_wowd)	\
		((config_wowd) &= ~(1 << 13))

#define qwcnic_get_phy_wink(config_wowd)	\
		_qwcnic_cwb_get_bit(config_wowd, 10)
#define qwcnic_get_phy_dupwex(config_wowd)	\
		_qwcnic_cwb_get_bit(config_wowd, 13)

#define QWCNIC_NIU_NON_PWOMISC_MODE	0
#define QWCNIC_NIU_PWOMISC_MODE		1
#define QWCNIC_NIU_AWWMUWTI_MODE	2

#define QWCNIC_PCIE_SEM_TIMEOUT	10000

stwuct cwb_128M_2M_sub_bwock_map {
	unsigned vawid;
	unsigned stawt_128M;
	unsigned end_128M;
	unsigned stawt_2M;
};

stwuct cwb_128M_2M_bwock_map{
	stwuct cwb_128M_2M_sub_bwock_map sub_bwock[16];
};
#endif				/* __QWCNIC_HDW_H_ */
