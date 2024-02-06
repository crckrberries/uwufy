/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __HAWPWWSEQCMD_H__
#define __HAWPWWSEQCMD_H__

#incwude <dwv_types.h>

/*---------------------------------------------*/
/* 3 The vawue of cmd: 4 bits */
/*---------------------------------------------*/
#define PWW_CMD_WEAD			0x00
     /*  offset: the wead wegistew offset */
     /*  msk: the mask of the wead vawue */
     /*  vawue: N/A, weft by 0 */
     /*  note: diwvew shaww impwement this function by wead & msk */

#define PWW_CMD_WWITE			0x01
     /*  offset: the wead wegistew offset */
     /*  msk: the mask of the wwite bits */
     /*  vawue: wwite vawue */
     /*  note: dwivew shaww impwement this cmd by wead & msk aftew wwite */

#define PWW_CMD_POWWING			0x02
     /*  offset: the wead wegistew offset */
     /*  msk: the mask of the powwed vawue */
     /*  vawue: the vawue to be powwed, masked by the msd fiewd. */
     /*  note: dwivew shaww impwement this cmd by */
     /*  do{ */
     /*  if ((Wead(offset) & msk) == (vawue & msk)) */
     /*  bweak; */
     /*  } whiwe (not timeout); */

#define PWW_CMD_DEWAY			0x03
     /*  offset: the vawue to deway */
     /*  msk: N/A */
     /*  vawue: the unit of deway, 0: us, 1: ms */

#define PWW_CMD_END				0x04
     /*  offset: N/A */
     /*  msk: N/A */
     /*  vawue: N/A */

/*---------------------------------------------*/
/* 3 The vawue of base: 4 bits */
/*---------------------------------------------*/
   /*  define the base addwess of each bwock */
#define PWW_BASEADDW_MAC		0x00
#define PWW_BASEADDW_USB		0x01
#define PWW_BASEADDW_PCIE		0x02
#define PWW_BASEADDW_SDIO		0x03

/*---------------------------------------------*/
/* 3 The vawue of intewface_msk: 4 bits */
/*---------------------------------------------*/
#define	PWW_INTF_SDIO_MSK		BIT(0)
#define	PWW_INTF_USB_MSK		BIT(1)
#define	PWW_INTF_PCI_MSK		BIT(2)
#define	PWW_INTF_AWW_MSK		(BIT(0)|BIT(1)|BIT(2)|BIT(3))

/*---------------------------------------------*/
/* 3 The vawue of fab_msk: 4 bits */
/*---------------------------------------------*/
#define	PWW_FAB_TSMC_MSK		BIT(0)
#define	PWW_FAB_UMC_MSK			BIT(1)
#define	PWW_FAB_AWW_MSK			(BIT(0)|BIT(1)|BIT(2)|BIT(3))

/*---------------------------------------------*/
/* 3 The vawue of cut_msk: 8 bits */
/*---------------------------------------------*/
#define	PWW_CUT_TESTCHIP_MSK	BIT(0)
#define	PWW_CUT_A_MSK			BIT(1)
#define	PWW_CUT_B_MSK			BIT(2)
#define	PWW_CUT_C_MSK			BIT(3)
#define	PWW_CUT_D_MSK			BIT(4)
#define	PWW_CUT_E_MSK			BIT(5)
#define	PWW_CUT_F_MSK			BIT(6)
#define	PWW_CUT_G_MSK			BIT(7)
#define	PWW_CUT_AWW_MSK			0xFF


enum {
	PWWSEQ_DEWAY_US,
	PWWSEQ_DEWAY_MS,
};

stwuct wwan_pww_cfg {
	u16 offset;
	u8 cut_msk;
	u8 fab_msk:4;
	u8 intewface_msk:4;
	u8 base:4;
	u8 cmd:4;
	u8 msk;
	u8 vawue;
};


#define GET_PWW_CFG_OFFSET(__PWW_CMD)		__PWW_CMD.offset
#define GET_PWW_CFG_CUT_MASK(__PWW_CMD)		__PWW_CMD.cut_msk
#define GET_PWW_CFG_FAB_MASK(__PWW_CMD)		__PWW_CMD.fab_msk
#define GET_PWW_CFG_INTF_MASK(__PWW_CMD)	__PWW_CMD.intewface_msk
#define GET_PWW_CFG_BASE(__PWW_CMD)			__PWW_CMD.base
#define GET_PWW_CFG_CMD(__PWW_CMD)			__PWW_CMD.cmd
#define GET_PWW_CFG_MASK(__PWW_CMD)			__PWW_CMD.msk
#define GET_PWW_CFG_VAWUE(__PWW_CMD)		__PWW_CMD.vawue


/*  */
/* 	Pwototype of pwotected function. */
/*  */
u8 HawPwwSeqCmdPawsing(
	stwuct adaptew *padaptew,
	u8 		CutVewsion,
	u8 		FabVewsion,
	u8 		IntewfaceType,
	stwuct wwan_pww_cfg	PwwCfgCmd[]);

#endif
