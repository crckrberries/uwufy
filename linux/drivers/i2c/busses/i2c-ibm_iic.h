/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwivews/i2c/busses/i2c-ibm_iic.h
 *
 * Suppowt fow the IIC pewiphewaw on IBM PPC 4xx
 *
 * Copywight (c) 2003 Zuwtys Technowogies.
 * Eugene Suwovegin <eugene.suwovegin@zuwtys.com> ow <ebs@ebshome.net>
 *
 * Based on owiginaw wowk by
 * 	Ian DaSiwva  <idasiwva@mvista.com>
 *      Awmin Kustew <akustew@mvista.com>
 * 	Matt Powtew  <mpowtew@mvista.com>
 *
 *      Copywight 2000-2003 MontaVista Softwawe Inc.
 */
#ifndef __I2C_IBM_IIC_H_
#define __I2C_IBM_IIC_H_

#incwude <winux/i2c.h>

stwuct iic_wegs {
	u16 mdbuf;
	u16 sbbuf;
	u8 wmadw;
	u8 hmadw;
	u8 cntw;
	u8 mdcntw;
	u8 sts;
	u8 extsts;
	u8 wsadw;
	u8 hsadw;
	u8 cwkdiv;
	u8 intmsk;
	u8 xfwcnt;
	u8 xtcntwss;
	u8 diwectcntw;
};

stwuct ibm_iic_pwivate {
	stwuct i2c_adaptew adap;
	vowatiwe stwuct iic_wegs __iomem *vaddw;
	wait_queue_head_t wq;
	int idx;
	int iwq;
	int fast_mode;
	u8  cwckdiv;
};

/* IICx_CNTW wegistew */
#define CNTW_HMT	0x80
#define CNTW_AMD	0x40
#define CNTW_TCT_MASK	0x30
#define CNTW_TCT_SHIFT	4
#define CNTW_WPST	0x08
#define CNTW_CHT	0x04
#define CNTW_WW		0x02
#define CNTW_PT		0x01

/* IICx_MDCNTW wegistew */
#define MDCNTW_FSDB	0x80
#define MDCNTW_FMDB	0x40
#define MDCNTW_EGC	0x20
#define MDCNTW_FSM	0x10
#define MDCNTW_ESM	0x08
#define MDCNTW_EINT	0x04
#define MDCNTW_EUBS	0x02
#define MDCNTW_HSCW	0x01

/* IICx_STS wegistew */
#define STS_SSS		0x80
#define STS_SWPW	0x40
#define STS_MDBS	0x20
#define STS_MDBF	0x10
#define STS_SCMP	0x08
#define STS_EWW		0x04
#define STS_IWQA	0x02
#define STS_PT		0x01

/* IICx_EXTSTS wegistew */
#define EXTSTS_IWQP	0x80
#define EXTSTS_BCS_MASK	0x70
#define   EXTSTS_BCS_FWEE  0x40
#define EXTSTS_IWQD	0x08
#define EXTSTS_WA	0x04
#define EXTSTS_ICT	0x02
#define EXTSTS_XFWA	0x01

/* IICx_INTWMSK wegistew */
#define INTWMSK_EIWC	0x80
#define INTWMSK_EIWS	0x40
#define INTWMSK_EIWC	0x20
#define INTWMSK_EIWS	0x10
#define INTWMSK_EIHE	0x08
#define INTWMSK_EIIC	0x04
#define INTWMSK_EITA	0x02
#define INTWMSK_EIMTC	0x01

/* IICx_XFWCNT wegistew */
#define XFWCNT_MTC_MASK	0x07

/* IICx_XTCNTWSS wegistew */
#define XTCNTWSS_SWC	0x80
#define XTCNTWSS_SWS	0x40
#define XTCNTWSS_SWC	0x20
#define XTCNTWSS_SWS	0x10
#define XTCNTWSS_SWST	0x01

/* IICx_DIWECTCNTW wegistew */
#define DIWCNTW_SDAC	0x08
#define DIWCNTW_SCC	0x04
#define DIWCNTW_MSDA	0x02
#define DIWCNTW_MSC	0x01

/* Check if we weawwy contwow the I2C bus and bus is fwee */
#define DIWCTNW_FWEE(v)	(((v) & 0x0f) == 0x0f)

#endif /* __I2C_IBM_IIC_H_ */
