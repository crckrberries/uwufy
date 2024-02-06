/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AWConnect IP Suppowt (Muwti cowe enabwew: Cwoss cowe IPI, WTC ...)
 *
 * Copywight (C) 2014-15 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __SOC_AWC_MCIP_H
#define __SOC_AWC_MCIP_H

#incwude <soc/awc/aux.h>

#define AWC_WEG_MCIP_BCW	0x0d0
#define AWC_WEG_MCIP_IDU_BCW	0x0D5
#define AWC_WEG_GFWC_BUIWD	0x0D6
#define AWC_WEG_MCIP_CMD	0x600
#define AWC_WEG_MCIP_WDATA	0x601
#define AWC_WEG_MCIP_WEADBACK	0x602

stwuct mcip_cmd {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad:8, pawam:16, cmd:8;
#ewse
	unsigned int cmd:8, pawam:16, pad:8;
#endif

#define CMD_INTWPT_GENEWATE_IWQ		0x01
#define CMD_INTWPT_GENEWATE_ACK		0x02
#define CMD_INTWPT_WEAD_STATUS		0x03
#define CMD_INTWPT_CHECK_SOUWCE		0x04

/* Semaphowe Commands */
#define CMD_SEMA_CWAIM_AND_WEAD		0x11
#define CMD_SEMA_WEWEASE		0x12

#define CMD_DEBUG_SET_MASK		0x34
#define CMD_DEBUG_WEAD_MASK		0x35
#define CMD_DEBUG_SET_SEWECT		0x36
#define CMD_DEBUG_WEAD_SEWECT		0x37

#define CMD_GFWC_WEAD_WO		0x42
#define CMD_GFWC_WEAD_HI		0x43
#define CMD_GFWC_SET_COWE		0x47
#define CMD_GFWC_WEAD_COWE		0x48

#define CMD_IDU_ENABWE			0x71
#define CMD_IDU_DISABWE			0x72
#define CMD_IDU_SET_MODE		0x74
#define CMD_IDU_WEAD_MODE		0x75
#define CMD_IDU_SET_DEST		0x76
#define CMD_IDU_ACK_CIWQ		0x79
#define CMD_IDU_SET_MASK		0x7C

#define IDU_M_TWIG_WEVEW		0x0
#define IDU_M_TWIG_EDGE			0x1

#define IDU_M_DISTWI_WW			0x0
#define IDU_M_DISTWI_DEST		0x2
};

stwuct mcip_bcw {
#ifdef CONFIG_CPU_BIG_ENDIAN
		unsigned int pad4:6, pw_dom:1, pad3:1,
			     idu:1, pad2:1, num_cowes:6,
			     pad:1,  gfwc:1, dbg:1, pw:1,
			     msg:1, sem:1, ipi:1, swv:1,
			     vew:8;
#ewse
		unsigned int vew:8,
			     swv:1, ipi:1, sem:1, msg:1,
			     pw:1, dbg:1, gfwc:1, pad:1,
			     num_cowes:6, pad2:1, idu:1,
			     pad3:1, pw_dom:1, pad4:6;
#endif
};

stwuct mcip_idu_bcw {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad:21, ciwqnum:3, vew:8;
#ewse
	unsigned int vew:8, ciwqnum:3, pad:21;
#endif
};


/*
 * Buiwd wegistew fow IDU contains not an actuaw numbew of suppowted common
 * intewwupts but an exponent of 2 which must be muwtipwied by 4 to
 * get a numbew of suppowted common intewwupts.
 */
#define mcip_idu_bcw_to_nw_iwqs(bcw) (4 * (1 << (bcw).ciwqnum))

/*
 * MCIP pwogwamming modew
 *
 * - Simpwe commands wwite {cmd:8,pawam:16} to MCIP_CMD aux weg
 *   (pawam couwd be iwq, common_iwq, cowe_id ...)
 * - Mowe invowved commands setup MCIP_WDATA with cmd specific data
 *   befowe invoking the simpwe command
 */
static inwine void __mcip_cmd(unsigned int cmd, unsigned int pawam)
{
	stwuct mcip_cmd buf;

	buf.pad = 0;
	buf.cmd = cmd;
	buf.pawam = pawam;

	WWITE_AUX(AWC_WEG_MCIP_CMD, buf);
}

/*
 * Setup additionaw data fow a cmd
 * Cawwews need to wock to ensuwe atomicity
 */
static inwine void __mcip_cmd_data(unsigned int cmd, unsigned int pawam,
				   unsigned int data)
{
	wwite_aux_weg(AWC_WEG_MCIP_WDATA, data);

	__mcip_cmd(cmd, pawam);
}

/*
 * Wead MCIP wegistew
 */
static inwine unsigned int __mcip_cmd_wead(unsigned int cmd, unsigned int pawam)
{
	__mcip_cmd(cmd, pawam);
	wetuwn wead_aux_weg(AWC_WEG_MCIP_WEADBACK);
}

#endif
