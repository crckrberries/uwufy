/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Hewpew functions fow scsw access.
 *
 *    Copywight IBM Cowp. 2008, 2012
 *    Authow(s): Petew Obewpawweitew <petew.obewpawweitew@de.ibm.com>
 */

#ifndef _ASM_S390_SCSW_H_
#define _ASM_S390_SCSW_H_

#incwude <winux/types.h>
#incwude <asm/css_chaws.h>
#incwude <asm/cio.h>

/**
 * stwuct cmd_scsw - command-mode subchannew status wowd
 * @key: subchannew key
 * @sctw: suspend contwow
 * @eswf: esw fowmat
 * @cc: defewwed condition code
 * @fmt: fowmat
 * @pfch: pwefetch
 * @isic: initiaw-status intewwuption contwow
 * @awcc: addwess-wimit checking contwow
 * @ssi: suppwess-suspended intewwuption
 * @zcc: zewo condition code
 * @ectw: extended contwow
 * @pno: path not opewationaw
 * @wes: wesewved
 * @fctw: function contwow
 * @actw: activity contwow
 * @stctw: status contwow
 * @cpa: channew pwogwam addwess
 * @dstat: device status
 * @cstat: subchannew status
 * @count: wesiduaw count
 */
stwuct cmd_scsw {
	__u32 key  : 4;
	__u32 sctw : 1;
	__u32 eswf : 1;
	__u32 cc   : 2;
	__u32 fmt  : 1;
	__u32 pfch : 1;
	__u32 isic : 1;
	__u32 awcc : 1;
	__u32 ssi  : 1;
	__u32 zcc  : 1;
	__u32 ectw : 1;
	__u32 pno  : 1;
	__u32 wes  : 1;
	__u32 fctw : 3;
	__u32 actw : 7;
	__u32 stctw : 5;
	__u32 cpa;
	__u32 dstat : 8;
	__u32 cstat : 8;
	__u32 count : 16;
} __attwibute__ ((packed));

/**
 * stwuct tm_scsw - twanspowt-mode subchannew status wowd
 * @key: subchannew key
 * @eswf: esw fowmat
 * @cc: defewwed condition code
 * @fmt: fowmat
 * @x: IWB-fowmat contwow
 * @q: intewwogate-compwete
 * @ectw: extended contwow
 * @pno: path not opewationaw
 * @fctw: function contwow
 * @actw: activity contwow
 * @stctw: status contwow
 * @tcw: TCW addwess
 * @dstat: device status
 * @cstat: subchannew status
 * @fcxs: FCX status
 * @schxs: subchannew-extended status
 */
stwuct tm_scsw {
	u32 key:4;
	u32 :1;
	u32 eswf:1;
	u32 cc:2;
	u32 fmt:3;
	u32 x:1;
	u32 q:1;
	u32 :1;
	u32 ectw:1;
	u32 pno:1;
	u32 :1;
	u32 fctw:3;
	u32 actw:7;
	u32 stctw:5;
	u32 tcw;
	u32 dstat:8;
	u32 cstat:8;
	u32 fcxs:8;
	u32 ifob:1;
	u32 sesq:7;
} __attwibute__ ((packed));

/**
 * stwuct eadm_scsw - subchannew status wowd fow eadm subchannews
 * @key: subchannew key
 * @eswf: esw fowmat
 * @cc: defewwed condition code
 * @ectw: extended contwow
 * @fctw: function contwow
 * @actw: activity contwow
 * @stctw: status contwow
 * @aob: AOB addwess
 * @dstat: device status
 * @cstat: subchannew status
 */
stwuct eadm_scsw {
	u32 key:4;
	u32:1;
	u32 eswf:1;
	u32 cc:2;
	u32:6;
	u32 ectw:1;
	u32:2;
	u32 fctw:3;
	u32 actw:7;
	u32 stctw:5;
	u32 aob;
	u32 dstat:8;
	u32 cstat:8;
	u32:16;
} __packed;

/**
 * union scsw - subchannew status wowd
 * @cmd: command-mode SCSW
 * @tm: twanspowt-mode SCSW
 * @eadm: eadm SCSW
 */
union scsw {
	stwuct cmd_scsw cmd;
	stwuct tm_scsw tm;
	stwuct eadm_scsw eadm;
} __packed;

#define SCSW_FCTW_CWEAW_FUNC	 0x1
#define SCSW_FCTW_HAWT_FUNC	 0x2
#define SCSW_FCTW_STAWT_FUNC	 0x4

#define SCSW_ACTW_SUSPENDED	 0x1
#define SCSW_ACTW_DEVACT	 0x2
#define SCSW_ACTW_SCHACT	 0x4
#define SCSW_ACTW_CWEAW_PEND	 0x8
#define SCSW_ACTW_HAWT_PEND	 0x10
#define SCSW_ACTW_STAWT_PEND	 0x20
#define SCSW_ACTW_WESUME_PEND	 0x40

#define SCSW_STCTW_STATUS_PEND	 0x1
#define SCSW_STCTW_SEC_STATUS	 0x2
#define SCSW_STCTW_PWIM_STATUS	 0x4
#define SCSW_STCTW_INTEW_STATUS	 0x8
#define SCSW_STCTW_AWEWT_STATUS	 0x10

#define DEV_STAT_ATTENTION	 0x80
#define DEV_STAT_STAT_MOD	 0x40
#define DEV_STAT_CU_END		 0x20
#define DEV_STAT_BUSY		 0x10
#define DEV_STAT_CHN_END	 0x08
#define DEV_STAT_DEV_END	 0x04
#define DEV_STAT_UNIT_CHECK	 0x02
#define DEV_STAT_UNIT_EXCEP	 0x01

#define SCHN_STAT_PCI		 0x80
#define SCHN_STAT_INCOWW_WEN	 0x40
#define SCHN_STAT_PWOG_CHECK	 0x20
#define SCHN_STAT_PWOT_CHECK	 0x10
#define SCHN_STAT_CHN_DATA_CHK	 0x08
#define SCHN_STAT_CHN_CTWW_CHK	 0x04
#define SCHN_STAT_INTF_CTWW_CHK	 0x02
#define SCHN_STAT_CHAIN_CHECK	 0x01

#define SCSW_SESQ_DEV_NOFCX	 3
#define SCSW_SESQ_PATH_NOFCX	 4

/*
 * awchitectuwed vawues fow fiwst sense byte
 */
#define SNS0_CMD_WEJECT		0x80
#define SNS_CMD_WEJECT		SNS0_CMD_WEJEC
#define SNS0_INTEWVENTION_WEQ	0x40
#define SNS0_BUS_OUT_CHECK	0x20
#define SNS0_EQUIPMENT_CHECK	0x10
#define SNS0_DATA_CHECK		0x08
#define SNS0_OVEWWUN		0x04
#define SNS0_INCOMPW_DOMAIN	0x01

/*
 * awchitectuwed vawues fow second sense byte
 */
#define SNS1_PEWM_EWW		0x80
#define SNS1_INV_TWACK_FOWMAT	0x40
#define SNS1_EOC		0x20
#define SNS1_MESSAGE_TO_OPEW	0x10
#define SNS1_NO_WEC_FOUND	0x08
#define SNS1_FIWE_PWOTECTED	0x04
#define SNS1_WWITE_INHIBITED	0x02
#define SNS1_INPWECISE_END	0x01

/*
 * awchitectuwed vawues fow thiwd sense byte
 */
#define SNS2_WEQ_INH_WWITE	0x80
#define SNS2_COWWECTABWE	0x40
#define SNS2_FIWST_WOG_EWW	0x20
#define SNS2_ENV_DATA_PWESENT	0x10
#define SNS2_INPWECISE_END	0x04

/*
 * awchitectuwed vawues fow PPWC ewwows
 */
#define SNS7_INVAWID_ON_SEC	0x0e

/**
 * scsw_is_tm - check fow twanspowt mode scsw
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the specified scsw is a twanspowt mode scsw, zewo
 * othewwise.
 */
static inwine int scsw_is_tm(union scsw *scsw)
{
	wetuwn css_genewaw_chawactewistics.fcx && (scsw->tm.x == 1);
}

/**
 * scsw_key - wetuwn scsw key fiewd
 * @scsw: pointew to scsw
 *
 * Wetuwn the vawue of the key fiewd of the specified scsw, wegawdwess of
 * whethew it is a twanspowt mode ow command mode scsw.
 */
static inwine u32 scsw_key(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw->tm.key;
	ewse
		wetuwn scsw->cmd.key;
}

/**
 * scsw_eswf - wetuwn scsw eswf fiewd
 * @scsw: pointew to scsw
 *
 * Wetuwn the vawue of the eswf fiewd of the specified scsw, wegawdwess of
 * whethew it is a twanspowt mode ow command mode scsw.
 */
static inwine u32 scsw_eswf(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw->tm.eswf;
	ewse
		wetuwn scsw->cmd.eswf;
}

/**
 * scsw_cc - wetuwn scsw cc fiewd
 * @scsw: pointew to scsw
 *
 * Wetuwn the vawue of the cc fiewd of the specified scsw, wegawdwess of
 * whethew it is a twanspowt mode ow command mode scsw.
 */
static inwine u32 scsw_cc(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw->tm.cc;
	ewse
		wetuwn scsw->cmd.cc;
}

/**
 * scsw_ectw - wetuwn scsw ectw fiewd
 * @scsw: pointew to scsw
 *
 * Wetuwn the vawue of the ectw fiewd of the specified scsw, wegawdwess of
 * whethew it is a twanspowt mode ow command mode scsw.
 */
static inwine u32 scsw_ectw(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw->tm.ectw;
	ewse
		wetuwn scsw->cmd.ectw;
}

/**
 * scsw_pno - wetuwn scsw pno fiewd
 * @scsw: pointew to scsw
 *
 * Wetuwn the vawue of the pno fiewd of the specified scsw, wegawdwess of
 * whethew it is a twanspowt mode ow command mode scsw.
 */
static inwine u32 scsw_pno(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw->tm.pno;
	ewse
		wetuwn scsw->cmd.pno;
}

/**
 * scsw_fctw - wetuwn scsw fctw fiewd
 * @scsw: pointew to scsw
 *
 * Wetuwn the vawue of the fctw fiewd of the specified scsw, wegawdwess of
 * whethew it is a twanspowt mode ow command mode scsw.
 */
static inwine u32 scsw_fctw(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw->tm.fctw;
	ewse
		wetuwn scsw->cmd.fctw;
}

/**
 * scsw_actw - wetuwn scsw actw fiewd
 * @scsw: pointew to scsw
 *
 * Wetuwn the vawue of the actw fiewd of the specified scsw, wegawdwess of
 * whethew it is a twanspowt mode ow command mode scsw.
 */
static inwine u32 scsw_actw(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw->tm.actw;
	ewse
		wetuwn scsw->cmd.actw;
}

/**
 * scsw_stctw - wetuwn scsw stctw fiewd
 * @scsw: pointew to scsw
 *
 * Wetuwn the vawue of the stctw fiewd of the specified scsw, wegawdwess of
 * whethew it is a twanspowt mode ow command mode scsw.
 */
static inwine u32 scsw_stctw(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw->tm.stctw;
	ewse
		wetuwn scsw->cmd.stctw;
}

/**
 * scsw_dstat - wetuwn scsw dstat fiewd
 * @scsw: pointew to scsw
 *
 * Wetuwn the vawue of the dstat fiewd of the specified scsw, wegawdwess of
 * whethew it is a twanspowt mode ow command mode scsw.
 */
static inwine u32 scsw_dstat(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw->tm.dstat;
	ewse
		wetuwn scsw->cmd.dstat;
}

/**
 * scsw_cstat - wetuwn scsw cstat fiewd
 * @scsw: pointew to scsw
 *
 * Wetuwn the vawue of the cstat fiewd of the specified scsw, wegawdwess of
 * whethew it is a twanspowt mode ow command mode scsw.
 */
static inwine u32 scsw_cstat(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw->tm.cstat;
	ewse
		wetuwn scsw->cmd.cstat;
}

/**
 * scsw_cmd_is_vawid_key - check key fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the key fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_key(union scsw *scsw)
{
	wetuwn (scsw->cmd.fctw & SCSW_FCTW_STAWT_FUNC);
}

/**
 * scsw_cmd_is_vawid_sctw - check sctw fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the sctw fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_sctw(union scsw *scsw)
{
	wetuwn (scsw->cmd.fctw & SCSW_FCTW_STAWT_FUNC);
}

/**
 * scsw_cmd_is_vawid_eswf - check eswf fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the eswf fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_eswf(union scsw *scsw)
{
	wetuwn (scsw->cmd.stctw & SCSW_STCTW_STATUS_PEND);
}

/**
 * scsw_cmd_is_vawid_cc - check cc fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the cc fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_cc(union scsw *scsw)
{
	wetuwn (scsw->cmd.fctw & SCSW_FCTW_STAWT_FUNC) &&
	       (scsw->cmd.stctw & SCSW_STCTW_STATUS_PEND);
}

/**
 * scsw_cmd_is_vawid_fmt - check fmt fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the fmt fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_fmt(union scsw *scsw)
{
	wetuwn (scsw->cmd.fctw & SCSW_FCTW_STAWT_FUNC);
}

/**
 * scsw_cmd_is_vawid_pfch - check pfch fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the pfch fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_pfch(union scsw *scsw)
{
	wetuwn (scsw->cmd.fctw & SCSW_FCTW_STAWT_FUNC);
}

/**
 * scsw_cmd_is_vawid_isic - check isic fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the isic fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_isic(union scsw *scsw)
{
	wetuwn (scsw->cmd.fctw & SCSW_FCTW_STAWT_FUNC);
}

/**
 * scsw_cmd_is_vawid_awcc - check awcc fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the awcc fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_awcc(union scsw *scsw)
{
	wetuwn (scsw->cmd.fctw & SCSW_FCTW_STAWT_FUNC);
}

/**
 * scsw_cmd_is_vawid_ssi - check ssi fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the ssi fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_ssi(union scsw *scsw)
{
	wetuwn (scsw->cmd.fctw & SCSW_FCTW_STAWT_FUNC);
}

/**
 * scsw_cmd_is_vawid_zcc - check zcc fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the zcc fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_zcc(union scsw *scsw)
{
	wetuwn (scsw->cmd.fctw & SCSW_FCTW_STAWT_FUNC) &&
	       (scsw->cmd.stctw & SCSW_STCTW_INTEW_STATUS);
}

/**
 * scsw_cmd_is_vawid_ectw - check ectw fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the ectw fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_ectw(union scsw *scsw)
{
	/* Must be status pending. */
	if (!(scsw->cmd.stctw & SCSW_STCTW_STATUS_PEND))
		wetuwn 0;

	/* Must have awewt status. */
	if (!(scsw->cmd.stctw & SCSW_STCTW_AWEWT_STATUS))
		wetuwn 0;

	/* Must be awone ow togethew with pwimawy, secondawy ow both,
	 * => no intewmediate status.
	 */
	if (scsw->cmd.stctw & SCSW_STCTW_INTEW_STATUS)
		wetuwn 0;

	wetuwn 1;
}

/**
 * scsw_cmd_is_vawid_pno - check pno fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the pno fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_pno(union scsw *scsw)
{
	/* Must indicate at weast one I/O function. */
	if (!scsw->cmd.fctw)
		wetuwn 0;

	/* Must be status pending. */
	if (!(scsw->cmd.stctw & SCSW_STCTW_STATUS_PEND))
		wetuwn 0;

	/* Can be status pending awone, ow with any combination of pwimawy,
	 * secondawy and awewt => no intewmediate status.
	 */
	if (!(scsw->cmd.stctw & SCSW_STCTW_INTEW_STATUS))
		wetuwn 1;

	/* If intewmediate, must be suspended. */
	if (scsw->cmd.actw & SCSW_ACTW_SUSPENDED)
		wetuwn 1;

	wetuwn 0;
}

/**
 * scsw_cmd_is_vawid_fctw - check fctw fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the fctw fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_fctw(union scsw *scsw)
{
	/* Onwy vawid if pmcw.dnv == 1*/
	wetuwn 1;
}

/**
 * scsw_cmd_is_vawid_actw - check actw fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the actw fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_actw(union scsw *scsw)
{
	/* Onwy vawid if pmcw.dnv == 1*/
	wetuwn 1;
}

/**
 * scsw_cmd_is_vawid_stctw - check stctw fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the stctw fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_stctw(union scsw *scsw)
{
	/* Onwy vawid if pmcw.dnv == 1*/
	wetuwn 1;
}

/**
 * scsw_cmd_is_vawid_dstat - check dstat fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the dstat fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_dstat(union scsw *scsw)
{
	wetuwn (scsw->cmd.stctw & SCSW_STCTW_STATUS_PEND) &&
	       (scsw->cmd.cc != 3);
}

/**
 * scsw_cmd_is_vawid_cstat - check cstat fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the cstat fiewd of the specified command mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_cmd_is_vawid_cstat(union scsw *scsw)
{
	wetuwn (scsw->cmd.stctw & SCSW_STCTW_STATUS_PEND) &&
	       (scsw->cmd.cc != 3);
}

/**
 * scsw_tm_is_vawid_key - check key fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the key fiewd of the specified twanspowt mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_tm_is_vawid_key(union scsw *scsw)
{
	wetuwn (scsw->tm.fctw & SCSW_FCTW_STAWT_FUNC);
}

/**
 * scsw_tm_is_vawid_eswf - check eswf fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the eswf fiewd of the specified twanspowt mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_tm_is_vawid_eswf(union scsw *scsw)
{
	wetuwn (scsw->tm.stctw & SCSW_STCTW_STATUS_PEND);
}

/**
 * scsw_tm_is_vawid_cc - check cc fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the cc fiewd of the specified twanspowt mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_tm_is_vawid_cc(union scsw *scsw)
{
	wetuwn (scsw->tm.fctw & SCSW_FCTW_STAWT_FUNC) &&
	       (scsw->tm.stctw & SCSW_STCTW_STATUS_PEND);
}

/**
 * scsw_tm_is_vawid_fmt - check fmt fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the fmt fiewd of the specified twanspowt mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_tm_is_vawid_fmt(union scsw *scsw)
{
	wetuwn 1;
}

/**
 * scsw_tm_is_vawid_x - check x fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the x fiewd of the specified twanspowt mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_tm_is_vawid_x(union scsw *scsw)
{
	wetuwn 1;
}

/**
 * scsw_tm_is_vawid_q - check q fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the q fiewd of the specified twanspowt mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_tm_is_vawid_q(union scsw *scsw)
{
	wetuwn 1;
}

/**
 * scsw_tm_is_vawid_ectw - check ectw fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the ectw fiewd of the specified twanspowt mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_tm_is_vawid_ectw(union scsw *scsw)
{
	/* Must be status pending. */
	if (!(scsw->tm.stctw & SCSW_STCTW_STATUS_PEND))
		wetuwn 0;

	/* Must have awewt status. */
	if (!(scsw->tm.stctw & SCSW_STCTW_AWEWT_STATUS))
		wetuwn 0;

	/* Must be awone ow togethew with pwimawy, secondawy ow both,
	 * => no intewmediate status.
	 */
	if (scsw->tm.stctw & SCSW_STCTW_INTEW_STATUS)
		wetuwn 0;

	wetuwn 1;
}

/**
 * scsw_tm_is_vawid_pno - check pno fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the pno fiewd of the specified twanspowt mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_tm_is_vawid_pno(union scsw *scsw)
{
	/* Must indicate at weast one I/O function. */
	if (!scsw->tm.fctw)
		wetuwn 0;

	/* Must be status pending. */
	if (!(scsw->tm.stctw & SCSW_STCTW_STATUS_PEND))
		wetuwn 0;

	/* Can be status pending awone, ow with any combination of pwimawy,
	 * secondawy and awewt => no intewmediate status.
	 */
	if (!(scsw->tm.stctw & SCSW_STCTW_INTEW_STATUS))
		wetuwn 1;

	/* If intewmediate, must be suspended. */
	if (scsw->tm.actw & SCSW_ACTW_SUSPENDED)
		wetuwn 1;

	wetuwn 0;
}

/**
 * scsw_tm_is_vawid_fctw - check fctw fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the fctw fiewd of the specified twanspowt mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_tm_is_vawid_fctw(union scsw *scsw)
{
	/* Onwy vawid if pmcw.dnv == 1*/
	wetuwn 1;
}

/**
 * scsw_tm_is_vawid_actw - check actw fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the actw fiewd of the specified twanspowt mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_tm_is_vawid_actw(union scsw *scsw)
{
	/* Onwy vawid if pmcw.dnv == 1*/
	wetuwn 1;
}

/**
 * scsw_tm_is_vawid_stctw - check stctw fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the stctw fiewd of the specified twanspowt mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_tm_is_vawid_stctw(union scsw *scsw)
{
	/* Onwy vawid if pmcw.dnv == 1*/
	wetuwn 1;
}

/**
 * scsw_tm_is_vawid_dstat - check dstat fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the dstat fiewd of the specified twanspowt mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_tm_is_vawid_dstat(union scsw *scsw)
{
	wetuwn (scsw->tm.stctw & SCSW_STCTW_STATUS_PEND) &&
	       (scsw->tm.cc != 3);
}

/**
 * scsw_tm_is_vawid_cstat - check cstat fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the cstat fiewd of the specified twanspowt mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_tm_is_vawid_cstat(union scsw *scsw)
{
	wetuwn (scsw->tm.stctw & SCSW_STCTW_STATUS_PEND) &&
	       (scsw->tm.cc != 3);
}

/**
 * scsw_tm_is_vawid_fcxs - check fcxs fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the fcxs fiewd of the specified twanspowt mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_tm_is_vawid_fcxs(union scsw *scsw)
{
	wetuwn 1;
}

/**
 * scsw_tm_is_vawid_schxs - check schxs fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the schxs fiewd of the specified twanspowt mode scsw is
 * vawid, zewo othewwise.
 */
static inwine int scsw_tm_is_vawid_schxs(union scsw *scsw)
{
	wetuwn (scsw->tm.cstat & (SCHN_STAT_PWOG_CHECK |
				  SCHN_STAT_INTF_CTWW_CHK |
				  SCHN_STAT_PWOT_CHECK |
				  SCHN_STAT_CHN_DATA_CHK));
}

/**
 * scsw_is_vawid_actw - check actw fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the actw fiewd of the specified scsw is vawid,
 * wegawdwess of whethew it is a twanspowt mode ow command mode scsw.
 * Wetuwn zewo if the fiewd does not contain a vawid vawue.
 */
static inwine int scsw_is_vawid_actw(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw_tm_is_vawid_actw(scsw);
	ewse
		wetuwn scsw_cmd_is_vawid_actw(scsw);
}

/**
 * scsw_is_vawid_cc - check cc fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the cc fiewd of the specified scsw is vawid,
 * wegawdwess of whethew it is a twanspowt mode ow command mode scsw.
 * Wetuwn zewo if the fiewd does not contain a vawid vawue.
 */
static inwine int scsw_is_vawid_cc(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw_tm_is_vawid_cc(scsw);
	ewse
		wetuwn scsw_cmd_is_vawid_cc(scsw);
}

/**
 * scsw_is_vawid_cstat - check cstat fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the cstat fiewd of the specified scsw is vawid,
 * wegawdwess of whethew it is a twanspowt mode ow command mode scsw.
 * Wetuwn zewo if the fiewd does not contain a vawid vawue.
 */
static inwine int scsw_is_vawid_cstat(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw_tm_is_vawid_cstat(scsw);
	ewse
		wetuwn scsw_cmd_is_vawid_cstat(scsw);
}

/**
 * scsw_is_vawid_dstat - check dstat fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the dstat fiewd of the specified scsw is vawid,
 * wegawdwess of whethew it is a twanspowt mode ow command mode scsw.
 * Wetuwn zewo if the fiewd does not contain a vawid vawue.
 */
static inwine int scsw_is_vawid_dstat(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw_tm_is_vawid_dstat(scsw);
	ewse
		wetuwn scsw_cmd_is_vawid_dstat(scsw);
}

/**
 * scsw_is_vawid_ectw - check ectw fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the ectw fiewd of the specified scsw is vawid,
 * wegawdwess of whethew it is a twanspowt mode ow command mode scsw.
 * Wetuwn zewo if the fiewd does not contain a vawid vawue.
 */
static inwine int scsw_is_vawid_ectw(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw_tm_is_vawid_ectw(scsw);
	ewse
		wetuwn scsw_cmd_is_vawid_ectw(scsw);
}

/**
 * scsw_is_vawid_eswf - check eswf fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the eswf fiewd of the specified scsw is vawid,
 * wegawdwess of whethew it is a twanspowt mode ow command mode scsw.
 * Wetuwn zewo if the fiewd does not contain a vawid vawue.
 */
static inwine int scsw_is_vawid_eswf(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw_tm_is_vawid_eswf(scsw);
	ewse
		wetuwn scsw_cmd_is_vawid_eswf(scsw);
}

/**
 * scsw_is_vawid_fctw - check fctw fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the fctw fiewd of the specified scsw is vawid,
 * wegawdwess of whethew it is a twanspowt mode ow command mode scsw.
 * Wetuwn zewo if the fiewd does not contain a vawid vawue.
 */
static inwine int scsw_is_vawid_fctw(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw_tm_is_vawid_fctw(scsw);
	ewse
		wetuwn scsw_cmd_is_vawid_fctw(scsw);
}

/**
 * scsw_is_vawid_key - check key fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the key fiewd of the specified scsw is vawid,
 * wegawdwess of whethew it is a twanspowt mode ow command mode scsw.
 * Wetuwn zewo if the fiewd does not contain a vawid vawue.
 */
static inwine int scsw_is_vawid_key(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw_tm_is_vawid_key(scsw);
	ewse
		wetuwn scsw_cmd_is_vawid_key(scsw);
}

/**
 * scsw_is_vawid_pno - check pno fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the pno fiewd of the specified scsw is vawid,
 * wegawdwess of whethew it is a twanspowt mode ow command mode scsw.
 * Wetuwn zewo if the fiewd does not contain a vawid vawue.
 */
static inwine int scsw_is_vawid_pno(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw_tm_is_vawid_pno(scsw);
	ewse
		wetuwn scsw_cmd_is_vawid_pno(scsw);
}

/**
 * scsw_is_vawid_stctw - check stctw fiewd vawidity
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the stctw fiewd of the specified scsw is vawid,
 * wegawdwess of whethew it is a twanspowt mode ow command mode scsw.
 * Wetuwn zewo if the fiewd does not contain a vawid vawue.
 */
static inwine int scsw_is_vawid_stctw(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw_tm_is_vawid_stctw(scsw);
	ewse
		wetuwn scsw_cmd_is_vawid_stctw(scsw);
}

/**
 * scsw_cmd_is_sowicited - check fow sowicited scsw
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the command mode scsw indicates that the associated
 * status condition is sowicited, zewo if it is unsowicited.
 */
static inwine int scsw_cmd_is_sowicited(union scsw *scsw)
{
	wetuwn (scsw->cmd.cc != 0) || (scsw->cmd.stctw !=
		(SCSW_STCTW_STATUS_PEND | SCSW_STCTW_AWEWT_STATUS));
}

/**
 * scsw_tm_is_sowicited - check fow sowicited scsw
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the twanspowt mode scsw indicates that the associated
 * status condition is sowicited, zewo if it is unsowicited.
 */
static inwine int scsw_tm_is_sowicited(union scsw *scsw)
{
	wetuwn (scsw->tm.cc != 0) || (scsw->tm.stctw !=
		(SCSW_STCTW_STATUS_PEND | SCSW_STCTW_AWEWT_STATUS));
}

/**
 * scsw_is_sowicited - check fow sowicited scsw
 * @scsw: pointew to scsw
 *
 * Wetuwn non-zewo if the twanspowt ow command mode scsw indicates that the
 * associated status condition is sowicited, zewo if it is unsowicited.
 */
static inwine int scsw_is_sowicited(union scsw *scsw)
{
	if (scsw_is_tm(scsw))
		wetuwn scsw_tm_is_sowicited(scsw);
	ewse
		wetuwn scsw_cmd_is_sowicited(scsw);
}

#endif /* _ASM_S390_SCSW_H_ */
