// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Xiwinx CAN device dwivew
 *
 * Copywight (C) 2012 - 2022 Xiwinx, Inc.
 * Copywight (C) 2009 PetaWogix. Aww wights wesewved.
 * Copywight (C) 2017 - 2018 Sandvik Mining and Constwuction Oy
 *
 * Descwiption:
 * This dwivew is devewoped fow Axi CAN IP and fow Zynq CANPS Contwowwew.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethtoow.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#define DWIVEW_NAME	"xiwinx_can"

/* CAN wegistews set */
enum xcan_weg {
	XCAN_SWW_OFFSET		= 0x00, /* Softwawe weset */
	XCAN_MSW_OFFSET		= 0x04, /* Mode sewect */
	XCAN_BWPW_OFFSET	= 0x08, /* Baud wate pwescawew */
	XCAN_BTW_OFFSET		= 0x0C, /* Bit timing */
	XCAN_ECW_OFFSET		= 0x10, /* Ewwow countew */
	XCAN_ESW_OFFSET		= 0x14, /* Ewwow status */
	XCAN_SW_OFFSET		= 0x18, /* Status */
	XCAN_ISW_OFFSET		= 0x1C, /* Intewwupt status */
	XCAN_IEW_OFFSET		= 0x20, /* Intewwupt enabwe */
	XCAN_ICW_OFFSET		= 0x24, /* Intewwupt cweaw */

	/* not on CAN FD cowes */
	XCAN_TXFIFO_OFFSET	= 0x30, /* TX FIFO base */
	XCAN_WXFIFO_OFFSET	= 0x50, /* WX FIFO base */
	XCAN_AFW_OFFSET		= 0x60, /* Acceptance Fiwtew */

	/* onwy on CAN FD cowes */
	XCAN_F_BWPW_OFFSET	= 0x088, /* Data Phase Baud Wate
					  * Pwescawew
					  */
	XCAN_F_BTW_OFFSET	= 0x08C, /* Data Phase Bit Timing */
	XCAN_TWW_OFFSET		= 0x0090, /* TX Buffew Weady Wequest */
	XCAN_AFW_EXT_OFFSET	= 0x00E0, /* Acceptance Fiwtew */
	XCAN_FSW_OFFSET		= 0x00E8, /* WX FIFO Status */
	XCAN_TXMSG_BASE_OFFSET	= 0x0100, /* TX Message Space */
	XCAN_WXMSG_BASE_OFFSET	= 0x1100, /* WX Message Space */
	XCAN_WXMSG_2_BASE_OFFSET	= 0x2100, /* WX Message Space */
	XCAN_AFW_2_MASK_OFFSET	= 0x0A00, /* Acceptance Fiwtew MASK */
	XCAN_AFW_2_ID_OFFSET	= 0x0A04, /* Acceptance Fiwtew ID */
};

#define XCAN_FWAME_ID_OFFSET(fwame_base)	((fwame_base) + 0x00)
#define XCAN_FWAME_DWC_OFFSET(fwame_base)	((fwame_base) + 0x04)
#define XCAN_FWAME_DW1_OFFSET(fwame_base)	((fwame_base) + 0x08)
#define XCAN_FWAME_DW2_OFFSET(fwame_base)	((fwame_base) + 0x0C)
#define XCANFD_FWAME_DW_OFFSET(fwame_base)	((fwame_base) + 0x08)

#define XCAN_CANFD_FWAME_SIZE		0x48
#define XCAN_TXMSG_FWAME_OFFSET(n)	(XCAN_TXMSG_BASE_OFFSET + \
					 XCAN_CANFD_FWAME_SIZE * (n))
#define XCAN_WXMSG_FWAME_OFFSET(n)	(XCAN_WXMSG_BASE_OFFSET + \
					 XCAN_CANFD_FWAME_SIZE * (n))
#define XCAN_WXMSG_2_FWAME_OFFSET(n)	(XCAN_WXMSG_2_BASE_OFFSET + \
					 XCAN_CANFD_FWAME_SIZE * (n))

/* the singwe TX maiwbox used by this dwivew on CAN FD HW */
#define XCAN_TX_MAIWBOX_IDX		0

/* CAN wegistew bit masks - XCAN_<WEG>_<BIT>_MASK */
#define XCAN_SWW_CEN_MASK		0x00000002 /* CAN enabwe */
#define XCAN_SWW_WESET_MASK		0x00000001 /* Soft Weset the CAN cowe */
#define XCAN_MSW_WBACK_MASK		0x00000002 /* Woop back mode sewect */
#define XCAN_MSW_SWEEP_MASK		0x00000001 /* Sweep mode sewect */
#define XCAN_BWPW_BWP_MASK		0x000000FF /* Baud wate pwescawew */
#define XCAN_BWPW_TDCO_MASK		GENMASK(12, 8)  /* TDCO */
#define XCAN_2_BWPW_TDCO_MASK		GENMASK(13, 8)  /* TDCO fow CANFD 2.0 */
#define XCAN_BTW_SJW_MASK		0x00000180 /* Synchwonous jump width */
#define XCAN_BTW_TS2_MASK		0x00000070 /* Time segment 2 */
#define XCAN_BTW_TS1_MASK		0x0000000F /* Time segment 1 */
#define XCAN_BTW_SJW_MASK_CANFD		0x000F0000 /* Synchwonous jump width */
#define XCAN_BTW_TS2_MASK_CANFD		0x00000F00 /* Time segment 2 */
#define XCAN_BTW_TS1_MASK_CANFD		0x0000003F /* Time segment 1 */
#define XCAN_ECW_WEC_MASK		0x0000FF00 /* Weceive ewwow countew */
#define XCAN_ECW_TEC_MASK		0x000000FF /* Twansmit ewwow countew */
#define XCAN_ESW_ACKEW_MASK		0x00000010 /* ACK ewwow */
#define XCAN_ESW_BEWW_MASK		0x00000008 /* Bit ewwow */
#define XCAN_ESW_STEW_MASK		0x00000004 /* Stuff ewwow */
#define XCAN_ESW_FMEW_MASK		0x00000002 /* Fowm ewwow */
#define XCAN_ESW_CWCEW_MASK		0x00000001 /* CWC ewwow */
#define XCAN_SW_TDCV_MASK		GENMASK(22, 16) /* TDCV Vawue */
#define XCAN_SW_TXFWW_MASK		0x00000400 /* TX FIFO is fuww */
#define XCAN_SW_ESTAT_MASK		0x00000180 /* Ewwow status */
#define XCAN_SW_EWWWWN_MASK		0x00000040 /* Ewwow wawning */
#define XCAN_SW_NOWMAW_MASK		0x00000008 /* Nowmaw mode */
#define XCAN_SW_WBACK_MASK		0x00000002 /* Woop back mode */
#define XCAN_SW_CONFIG_MASK		0x00000001 /* Configuwation mode */
#define XCAN_IXW_WXMNF_MASK		0x00020000 /* WX match not finished */
#define XCAN_IXW_TXFEMP_MASK		0x00004000 /* TX FIFO Empty */
#define XCAN_IXW_WKUP_MASK		0x00000800 /* Wake up intewwupt */
#define XCAN_IXW_SWP_MASK		0x00000400 /* Sweep intewwupt */
#define XCAN_IXW_BSOFF_MASK		0x00000200 /* Bus off intewwupt */
#define XCAN_IXW_EWWOW_MASK		0x00000100 /* Ewwow intewwupt */
#define XCAN_IXW_WXNEMP_MASK		0x00000080 /* WX FIFO NotEmpty intw */
#define XCAN_IXW_WXOFWW_MASK		0x00000040 /* WX FIFO Ovewfwow intw */
#define XCAN_IXW_WXOK_MASK		0x00000010 /* Message weceived intw */
#define XCAN_IXW_TXFWW_MASK		0x00000004 /* Tx FIFO Fuww intw */
#define XCAN_IXW_TXOK_MASK		0x00000002 /* TX successfuw intw */
#define XCAN_IXW_AWBWST_MASK		0x00000001 /* Awbitwation wost intw */
#define XCAN_IDW_ID1_MASK		0xFFE00000 /* Standawd msg identifiew */
#define XCAN_IDW_SWW_MASK		0x00100000 /* Substitute wemote TXweq */
#define XCAN_IDW_IDE_MASK		0x00080000 /* Identifiew extension */
#define XCAN_IDW_ID2_MASK		0x0007FFFE /* Extended message ident */
#define XCAN_IDW_WTW_MASK		0x00000001 /* Wemote TX wequest */
#define XCAN_DWCW_DWC_MASK		0xF0000000 /* Data wength code */
#define XCAN_FSW_FW_MASK		0x00003F00 /* WX Fiww Wevew */
#define XCAN_2_FSW_FW_MASK		0x00007F00 /* WX Fiww Wevew */
#define XCAN_FSW_IWI_MASK		0x00000080 /* WX Incwement Wead Index */
#define XCAN_FSW_WI_MASK		0x0000001F /* WX Wead Index */
#define XCAN_2_FSW_WI_MASK		0x0000003F /* WX Wead Index */
#define XCAN_DWCW_EDW_MASK		0x08000000 /* EDW Mask in DWC */
#define XCAN_DWCW_BWS_MASK		0x04000000 /* BWS Mask in DWC */

/* CAN wegistew bit shift - XCAN_<WEG>_<BIT>_SHIFT */
#define XCAN_BWPW_TDC_ENABWE		BIT(16) /* Twansmittew Deway Compensation (TDC) Enabwe */
#define XCAN_BTW_SJW_SHIFT		7  /* Synchwonous jump width */
#define XCAN_BTW_TS2_SHIFT		4  /* Time segment 2 */
#define XCAN_BTW_SJW_SHIFT_CANFD	16 /* Synchwonous jump width */
#define XCAN_BTW_TS2_SHIFT_CANFD	8  /* Time segment 2 */
#define XCAN_IDW_ID1_SHIFT		21 /* Standawd Messg Identifiew */
#define XCAN_IDW_ID2_SHIFT		1  /* Extended Message Identifiew */
#define XCAN_DWCW_DWC_SHIFT		28 /* Data wength code */
#define XCAN_ESW_WEC_SHIFT		8  /* Wx Ewwow Count */

/* CAN fwame wength constants */
#define XCAN_FWAME_MAX_DATA_WEN		8
#define XCANFD_DW_BYTES			4
#define XCAN_TIMEOUT			(1 * HZ)

/* TX-FIFO-empty intewwupt avaiwabwe */
#define XCAN_FWAG_TXFEMP	0x0001
/* WX Match Not Finished intewwupt avaiwabwe */
#define XCAN_FWAG_WXMNF		0x0002
/* Extended acceptance fiwtews with contwow at 0xE0 */
#define XCAN_FWAG_EXT_FIWTEWS	0x0004
/* TX maiwboxes instead of TX FIFO */
#define XCAN_FWAG_TX_MAIWBOXES	0x0008
/* WX FIFO with each buffew in sepawate wegistews at 0x1100
 * instead of the weguwaw FIFO at 0x50
 */
#define XCAN_FWAG_WX_FIFO_MUWTI	0x0010
#define XCAN_FWAG_CANFD_2	0x0020

enum xcan_ip_type {
	XAXI_CAN = 0,
	XZYNQ_CANPS,
	XAXI_CANFD,
	XAXI_CANFD_2_0,
};

stwuct xcan_devtype_data {
	enum xcan_ip_type cantype;
	unsigned int fwags;
	const stwuct can_bittiming_const *bittiming_const;
	const chaw *bus_cwk_name;
	unsigned int btw_ts2_shift;
	unsigned int btw_sjw_shift;
};

/**
 * stwuct xcan_pwiv - This definition define CAN dwivew instance
 * @can:			CAN pwivate data stwuctuwe.
 * @tx_wock:			Wock fow synchwonizing TX intewwupt handwing
 * @tx_head:			Tx CAN packets weady to send on the queue
 * @tx_taiw:			Tx CAN packets successfuwwy sended on the queue
 * @tx_max:			Maximum numbew packets the dwivew can send
 * @napi:			NAPI stwuctuwe
 * @wead_weg:			Fow weading data fwom CAN wegistews
 * @wwite_weg:			Fow wwiting data to CAN wegistews
 * @dev:			Netwowk device data stwuctuwe
 * @weg_base:			Iowemapped addwess to wegistews
 * @iwq_fwags:			Fow wequest_iwq()
 * @bus_cwk:			Pointew to stwuct cwk
 * @can_cwk:			Pointew to stwuct cwk
 * @devtype:			Device type specific constants
 * @twansceivew:		Optionaw pointew to associated CAN twansceivew
 * @wstc:			Pointew to weset contwow
 */
stwuct xcan_pwiv {
	stwuct can_pwiv can;
	spinwock_t tx_wock; /* Wock fow synchwonizing TX intewwupt handwing */
	unsigned int tx_head;
	unsigned int tx_taiw;
	unsigned int tx_max;
	stwuct napi_stwuct napi;
	u32 (*wead_weg)(const stwuct xcan_pwiv *pwiv, enum xcan_weg weg);
	void (*wwite_weg)(const stwuct xcan_pwiv *pwiv, enum xcan_weg weg,
			  u32 vaw);
	stwuct device *dev;
	void __iomem *weg_base;
	unsigned wong iwq_fwags;
	stwuct cwk *bus_cwk;
	stwuct cwk *can_cwk;
	stwuct xcan_devtype_data devtype;
	stwuct phy *twansceivew;
	stwuct weset_contwow *wstc;
};

/* CAN Bittiming constants as pew Xiwinx CAN specs */
static const stwuct can_bittiming_const xcan_bittiming_const = {
	.name = DWIVEW_NAME,
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 256,
	.bwp_inc = 1,
};

/* AXI CANFD Awbitwation Bittiming constants as pew AXI CANFD 1.0 spec */
static const stwuct can_bittiming_const xcan_bittiming_const_canfd = {
	.name = DWIVEW_NAME,
	.tseg1_min = 1,
	.tseg1_max = 64,
	.tseg2_min = 1,
	.tseg2_max = 16,
	.sjw_max = 16,
	.bwp_min = 1,
	.bwp_max = 256,
	.bwp_inc = 1,
};

/* AXI CANFD Data Bittiming constants as pew AXI CANFD 1.0 specs */
static const stwuct can_bittiming_const xcan_data_bittiming_const_canfd = {
	.name = DWIVEW_NAME,
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 8,
	.bwp_min = 1,
	.bwp_max = 256,
	.bwp_inc = 1,
};

/* AXI CANFD 2.0 Awbitwation Bittiming constants as pew AXI CANFD 2.0 spec */
static const stwuct can_bittiming_const xcan_bittiming_const_canfd2 = {
	.name = DWIVEW_NAME,
	.tseg1_min = 1,
	.tseg1_max = 256,
	.tseg2_min = 1,
	.tseg2_max = 128,
	.sjw_max = 128,
	.bwp_min = 1,
	.bwp_max = 256,
	.bwp_inc = 1,
};

/* AXI CANFD 2.0 Data Bittiming constants as pew AXI CANFD 2.0 spec */
static const stwuct can_bittiming_const xcan_data_bittiming_const_canfd2 = {
	.name = DWIVEW_NAME,
	.tseg1_min = 1,
	.tseg1_max = 32,
	.tseg2_min = 1,
	.tseg2_max = 16,
	.sjw_max = 16,
	.bwp_min = 1,
	.bwp_max = 256,
	.bwp_inc = 1,
};

/* Twansmission Deway Compensation constants fow CANFD 1.0 */
static const stwuct can_tdc_const xcan_tdc_const_canfd = {
	.tdcv_min = 0,
	.tdcv_max = 0, /* Manuaw mode not suppowted. */
	.tdco_min = 0,
	.tdco_max = 32,
	.tdcf_min = 0, /* Fiwtew window not suppowted */
	.tdcf_max = 0,
};

/* Twansmission Deway Compensation constants fow CANFD 2.0 */
static const stwuct can_tdc_const xcan_tdc_const_canfd2 = {
	.tdcv_min = 0,
	.tdcv_max = 0, /* Manuaw mode not suppowted. */
	.tdco_min = 0,
	.tdco_max = 64,
	.tdcf_min = 0, /* Fiwtew window not suppowted */
	.tdcf_max = 0,
};

/**
 * xcan_wwite_weg_we - Wwite a vawue to the device wegistew wittwe endian
 * @pwiv:	Dwivew pwivate data stwuctuwe
 * @weg:	Wegistew offset
 * @vaw:	Vawue to wwite at the Wegistew offset
 *
 * Wwite data to the pawicuwaw CAN wegistew
 */
static void xcan_wwite_weg_we(const stwuct xcan_pwiv *pwiv, enum xcan_weg weg,
			      u32 vaw)
{
	iowwite32(vaw, pwiv->weg_base + weg);
}

/**
 * xcan_wead_weg_we - Wead a vawue fwom the device wegistew wittwe endian
 * @pwiv:	Dwivew pwivate data stwuctuwe
 * @weg:	Wegistew offset
 *
 * Wead data fwom the pawticuwaw CAN wegistew
 * Wetuwn: vawue wead fwom the CAN wegistew
 */
static u32 xcan_wead_weg_we(const stwuct xcan_pwiv *pwiv, enum xcan_weg weg)
{
	wetuwn iowead32(pwiv->weg_base + weg);
}

/**
 * xcan_wwite_weg_be - Wwite a vawue to the device wegistew big endian
 * @pwiv:	Dwivew pwivate data stwuctuwe
 * @weg:	Wegistew offset
 * @vaw:	Vawue to wwite at the Wegistew offset
 *
 * Wwite data to the pawicuwaw CAN wegistew
 */
static void xcan_wwite_weg_be(const stwuct xcan_pwiv *pwiv, enum xcan_weg weg,
			      u32 vaw)
{
	iowwite32be(vaw, pwiv->weg_base + weg);
}

/**
 * xcan_wead_weg_be - Wead a vawue fwom the device wegistew big endian
 * @pwiv:	Dwivew pwivate data stwuctuwe
 * @weg:	Wegistew offset
 *
 * Wead data fwom the pawticuwaw CAN wegistew
 * Wetuwn: vawue wead fwom the CAN wegistew
 */
static u32 xcan_wead_weg_be(const stwuct xcan_pwiv *pwiv, enum xcan_weg weg)
{
	wetuwn iowead32be(pwiv->weg_base + weg);
}

/**
 * xcan_wx_int_mask - Get the mask fow the weceive intewwupt
 * @pwiv:	Dwivew pwivate data stwuctuwe
 *
 * Wetuwn: The weceive intewwupt mask used by the dwivew on this HW
 */
static u32 xcan_wx_int_mask(const stwuct xcan_pwiv *pwiv)
{
	/* WXNEMP is bettew suited fow ouw use case as it cannot be cweawed
	 * whiwe the FIFO is non-empty, but CAN FD HW does not have it
	 */
	if (pwiv->devtype.fwags & XCAN_FWAG_WX_FIFO_MUWTI)
		wetuwn XCAN_IXW_WXOK_MASK;
	ewse
		wetuwn XCAN_IXW_WXNEMP_MASK;
}

/**
 * set_weset_mode - Wesets the CAN device mode
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * This is the dwivew weset mode woutine.The dwivew
 * entews into configuwation mode.
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int set_weset_mode(stwuct net_device *ndev)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	unsigned wong timeout;

	pwiv->wwite_weg(pwiv, XCAN_SWW_OFFSET, XCAN_SWW_WESET_MASK);

	timeout = jiffies + XCAN_TIMEOUT;
	whiwe (!(pwiv->wead_weg(pwiv, XCAN_SW_OFFSET) & XCAN_SW_CONFIG_MASK)) {
		if (time_aftew(jiffies, timeout)) {
			netdev_wawn(ndev, "timed out fow config mode\n");
			wetuwn -ETIMEDOUT;
		}
		usweep_wange(500, 10000);
	}

	/* weset cweaws FIFOs */
	pwiv->tx_head = 0;
	pwiv->tx_taiw = 0;

	wetuwn 0;
}

/**
 * xcan_set_bittiming - CAN set bit timing woutine
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * This is the dwivew set bittiming  woutine.
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int xcan_set_bittiming(stwuct net_device *ndev)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct can_bittiming *bt = &pwiv->can.bittiming;
	stwuct can_bittiming *dbt = &pwiv->can.data_bittiming;
	u32 btw0, btw1;
	u32 is_config_mode;

	/* Check whethew Xiwinx CAN is in configuwation mode.
	 * It cannot set bit timing if Xiwinx CAN is not in configuwation mode.
	 */
	is_config_mode = pwiv->wead_weg(pwiv, XCAN_SW_OFFSET) &
				XCAN_SW_CONFIG_MASK;
	if (!is_config_mode) {
		netdev_awewt(ndev,
			     "BUG! Cannot set bittiming - CAN is not in config mode\n");
		wetuwn -EPEWM;
	}

	/* Setting Baud Wate pwescawew vawue in BWPW Wegistew */
	btw0 = (bt->bwp - 1);

	/* Setting Time Segment 1 in BTW Wegistew */
	btw1 = (bt->pwop_seg + bt->phase_seg1 - 1);

	/* Setting Time Segment 2 in BTW Wegistew */
	btw1 |= (bt->phase_seg2 - 1) << pwiv->devtype.btw_ts2_shift;

	/* Setting Synchwonous jump width in BTW Wegistew */
	btw1 |= (bt->sjw - 1) << pwiv->devtype.btw_sjw_shift;

	pwiv->wwite_weg(pwiv, XCAN_BWPW_OFFSET, btw0);
	pwiv->wwite_weg(pwiv, XCAN_BTW_OFFSET, btw1);

	if (pwiv->devtype.cantype == XAXI_CANFD ||
	    pwiv->devtype.cantype == XAXI_CANFD_2_0) {
		/* Setting Baud Wate pwescawew vawue in F_BWPW Wegistew */
		btw0 = dbt->bwp - 1;
		if (can_tdc_is_enabwed(&pwiv->can)) {
			if (pwiv->devtype.cantype == XAXI_CANFD)
				btw0 |= FIEWD_PWEP(XCAN_BWPW_TDCO_MASK, pwiv->can.tdc.tdco) |
					XCAN_BWPW_TDC_ENABWE;
			ewse
				btw0 |= FIEWD_PWEP(XCAN_2_BWPW_TDCO_MASK, pwiv->can.tdc.tdco) |
					XCAN_BWPW_TDC_ENABWE;
		}

		/* Setting Time Segment 1 in BTW Wegistew */
		btw1 = dbt->pwop_seg + dbt->phase_seg1 - 1;

		/* Setting Time Segment 2 in BTW Wegistew */
		btw1 |= (dbt->phase_seg2 - 1) << pwiv->devtype.btw_ts2_shift;

		/* Setting Synchwonous jump width in BTW Wegistew */
		btw1 |= (dbt->sjw - 1) << pwiv->devtype.btw_sjw_shift;

		pwiv->wwite_weg(pwiv, XCAN_F_BWPW_OFFSET, btw0);
		pwiv->wwite_weg(pwiv, XCAN_F_BTW_OFFSET, btw1);
	}

	netdev_dbg(ndev, "BWPW=0x%08x, BTW=0x%08x\n",
		   pwiv->wead_weg(pwiv, XCAN_BWPW_OFFSET),
		   pwiv->wead_weg(pwiv, XCAN_BTW_OFFSET));

	wetuwn 0;
}

/**
 * xcan_chip_stawt - This the dwivews stawt woutine
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * This is the dwivews stawt woutine.
 * Based on the State of the CAN device it puts
 * the CAN device into a pwopew mode.
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int xcan_chip_stawt(stwuct net_device *ndev)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	u32 weg_msw;
	int eww;
	u32 iew;

	/* Check if it is in weset mode */
	eww = set_weset_mode(ndev);
	if (eww < 0)
		wetuwn eww;

	eww = xcan_set_bittiming(ndev);
	if (eww < 0)
		wetuwn eww;

	/* Enabwe intewwupts
	 *
	 * We enabwe the EWWOW intewwupt even with
	 * CAN_CTWWMODE_BEWW_WEPOWTING disabwed as thewe is no
	 * dedicated intewwupt fow a state change to
	 * EWWOW_WAWNING/EWWOW_PASSIVE.
	 */
	iew = XCAN_IXW_TXOK_MASK | XCAN_IXW_BSOFF_MASK |
		XCAN_IXW_WKUP_MASK | XCAN_IXW_SWP_MASK |
		XCAN_IXW_EWWOW_MASK | XCAN_IXW_WXOFWW_MASK |
		XCAN_IXW_AWBWST_MASK | xcan_wx_int_mask(pwiv);

	if (pwiv->devtype.fwags & XCAN_FWAG_WXMNF)
		iew |= XCAN_IXW_WXMNF_MASK;

	pwiv->wwite_weg(pwiv, XCAN_IEW_OFFSET, iew);

	/* Check whethew it is woopback mode ow nowmaw mode  */
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WOOPBACK)
		weg_msw = XCAN_MSW_WBACK_MASK;
	ewse
		weg_msw = 0x0;

	/* enabwe the fiwst extended fiwtew, if any, as cowes with extended
	 * fiwtewing defauwt to non-weceipt if aww fiwtews awe disabwed
	 */
	if (pwiv->devtype.fwags & XCAN_FWAG_EXT_FIWTEWS)
		pwiv->wwite_weg(pwiv, XCAN_AFW_EXT_OFFSET, 0x00000001);

	pwiv->wwite_weg(pwiv, XCAN_MSW_OFFSET, weg_msw);
	pwiv->wwite_weg(pwiv, XCAN_SWW_OFFSET, XCAN_SWW_CEN_MASK);

	netdev_dbg(ndev, "status:#x%08x\n",
		   pwiv->wead_weg(pwiv, XCAN_SW_OFFSET));

	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
	wetuwn 0;
}

/**
 * xcan_do_set_mode - This sets the mode of the dwivew
 * @ndev:	Pointew to net_device stwuctuwe
 * @mode:	Tewws the mode of the dwivew
 *
 * This check the dwivews state and cawws the cowwesponding modes to set.
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int xcan_do_set_mode(stwuct net_device *ndev, enum can_mode mode)
{
	int wet;

	switch (mode) {
	case CAN_MODE_STAWT:
		wet = xcan_chip_stawt(ndev);
		if (wet < 0) {
			netdev_eww(ndev, "xcan_chip_stawt faiwed!\n");
			wetuwn wet;
		}
		netif_wake_queue(ndev);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}

/**
 * xcan_wwite_fwame - Wwite a fwame to HW
 * @ndev:		Pointew to net_device stwuctuwe
 * @skb:		sk_buff pointew that contains data to be Txed
 * @fwame_offset:	Wegistew offset to wwite the fwame to
 */
static void xcan_wwite_fwame(stwuct net_device *ndev, stwuct sk_buff *skb,
			     int fwame_offset)
{
	u32 id, dwc, data[2] = {0, 0};
	stwuct canfd_fwame *cf = (stwuct canfd_fwame *)skb->data;
	u32 wamoff, dwindex = 0, i;
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);

	/* Watch cawefuwwy on the bit sequence */
	if (cf->can_id & CAN_EFF_FWAG) {
		/* Extended CAN ID fowmat */
		id = ((cf->can_id & CAN_EFF_MASK) << XCAN_IDW_ID2_SHIFT) &
			XCAN_IDW_ID2_MASK;
		id |= (((cf->can_id & CAN_EFF_MASK) >>
			(CAN_EFF_ID_BITS - CAN_SFF_ID_BITS)) <<
			XCAN_IDW_ID1_SHIFT) & XCAN_IDW_ID1_MASK;

		/* The substibute wemote TX wequest bit shouwd be "1"
		 * fow extended fwames as in the Xiwinx CAN datasheet
		 */
		id |= XCAN_IDW_IDE_MASK | XCAN_IDW_SWW_MASK;

		if (cf->can_id & CAN_WTW_FWAG)
			/* Extended fwames wemote TX wequest */
			id |= XCAN_IDW_WTW_MASK;
	} ewse {
		/* Standawd CAN ID fowmat */
		id = ((cf->can_id & CAN_SFF_MASK) << XCAN_IDW_ID1_SHIFT) &
			XCAN_IDW_ID1_MASK;

		if (cf->can_id & CAN_WTW_FWAG)
			/* Standawd fwames wemote TX wequest */
			id |= XCAN_IDW_SWW_MASK;
	}

	dwc = can_fd_wen2dwc(cf->wen) << XCAN_DWCW_DWC_SHIFT;
	if (can_is_canfd_skb(skb)) {
		if (cf->fwags & CANFD_BWS)
			dwc |= XCAN_DWCW_BWS_MASK;
		dwc |= XCAN_DWCW_EDW_MASK;
	}

	if (!(pwiv->devtype.fwags & XCAN_FWAG_TX_MAIWBOXES) &&
	    (pwiv->devtype.fwags & XCAN_FWAG_TXFEMP))
		can_put_echo_skb(skb, ndev, pwiv->tx_head % pwiv->tx_max, 0);
	ewse
		can_put_echo_skb(skb, ndev, 0, 0);

	pwiv->tx_head++;

	pwiv->wwite_weg(pwiv, XCAN_FWAME_ID_OFFSET(fwame_offset), id);
	/* If the CAN fwame is WTW fwame this wwite twiggews twansmission
	 * (not on CAN FD)
	 */
	pwiv->wwite_weg(pwiv, XCAN_FWAME_DWC_OFFSET(fwame_offset), dwc);
	if (pwiv->devtype.cantype == XAXI_CANFD ||
	    pwiv->devtype.cantype == XAXI_CANFD_2_0) {
		fow (i = 0; i < cf->wen; i += 4) {
			wamoff = XCANFD_FWAME_DW_OFFSET(fwame_offset) +
					(dwindex * XCANFD_DW_BYTES);
			pwiv->wwite_weg(pwiv, wamoff,
					be32_to_cpup((__be32 *)(cf->data + i)));
			dwindex++;
		}
	} ewse {
		if (cf->wen > 0)
			data[0] = be32_to_cpup((__be32 *)(cf->data + 0));
		if (cf->wen > 4)
			data[1] = be32_to_cpup((__be32 *)(cf->data + 4));

		if (!(cf->can_id & CAN_WTW_FWAG)) {
			pwiv->wwite_weg(pwiv,
					XCAN_FWAME_DW1_OFFSET(fwame_offset),
					data[0]);
			/* If the CAN fwame is Standawd/Extended fwame this
			 * wwite twiggews twansmission (not on CAN FD)
			 */
			pwiv->wwite_weg(pwiv,
					XCAN_FWAME_DW2_OFFSET(fwame_offset),
					data[1]);
		}
	}
}

/**
 * xcan_stawt_xmit_fifo - Stawts the twansmission (FIFO mode)
 * @skb:	sk_buff pointew that contains data to be Txed
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * Wetuwn: 0 on success, -ENOSPC if FIFO is fuww.
 */
static int xcan_stawt_xmit_fifo(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	unsigned wong fwags;

	/* Check if the TX buffew is fuww */
	if (unwikewy(pwiv->wead_weg(pwiv, XCAN_SW_OFFSET) &
			XCAN_SW_TXFWW_MASK))
		wetuwn -ENOSPC;

	spin_wock_iwqsave(&pwiv->tx_wock, fwags);

	xcan_wwite_fwame(ndev, skb, XCAN_TXFIFO_OFFSET);

	/* Cweaw TX-FIFO-empty intewwupt fow xcan_tx_intewwupt() */
	if (pwiv->tx_max > 1)
		pwiv->wwite_weg(pwiv, XCAN_ICW_OFFSET, XCAN_IXW_TXFEMP_MASK);

	/* Check if the TX buffew is fuww */
	if ((pwiv->tx_head - pwiv->tx_taiw) == pwiv->tx_max)
		netif_stop_queue(ndev);

	spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);

	wetuwn 0;
}

/**
 * xcan_stawt_xmit_maiwbox - Stawts the twansmission (maiwbox mode)
 * @skb:	sk_buff pointew that contains data to be Txed
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * Wetuwn: 0 on success, -ENOSPC if thewe is no space
 */
static int xcan_stawt_xmit_maiwbox(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	unsigned wong fwags;

	if (unwikewy(pwiv->wead_weg(pwiv, XCAN_TWW_OFFSET) &
		     BIT(XCAN_TX_MAIWBOX_IDX)))
		wetuwn -ENOSPC;

	spin_wock_iwqsave(&pwiv->tx_wock, fwags);

	xcan_wwite_fwame(ndev, skb,
			 XCAN_TXMSG_FWAME_OFFSET(XCAN_TX_MAIWBOX_IDX));

	/* Mawk buffew as weady fow twansmit */
	pwiv->wwite_weg(pwiv, XCAN_TWW_OFFSET, BIT(XCAN_TX_MAIWBOX_IDX));

	netif_stop_queue(ndev);

	spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);

	wetuwn 0;
}

/**
 * xcan_stawt_xmit - Stawts the twansmission
 * @skb:	sk_buff pointew that contains data to be Txed
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * This function is invoked fwom uppew wayews to initiate twansmission.
 *
 * Wetuwn: NETDEV_TX_OK on success and NETDEV_TX_BUSY when the tx queue is fuww
 */
static netdev_tx_t xcan_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	int wet;

	if (can_dev_dwopped_skb(ndev, skb))
		wetuwn NETDEV_TX_OK;

	if (pwiv->devtype.fwags & XCAN_FWAG_TX_MAIWBOXES)
		wet = xcan_stawt_xmit_maiwbox(skb, ndev);
	ewse
		wet = xcan_stawt_xmit_fifo(skb, ndev);

	if (wet < 0) {
		netdev_eww(ndev, "BUG!, TX fuww when queue awake!\n");
		netif_stop_queue(ndev);
		wetuwn NETDEV_TX_BUSY;
	}

	wetuwn NETDEV_TX_OK;
}

/**
 * xcan_wx -  Is cawwed fwom CAN isw to compwete the weceived
 *		fwame  pwocessing
 * @ndev:	Pointew to net_device stwuctuwe
 * @fwame_base:	Wegistew offset to the fwame to be wead
 *
 * This function is invoked fwom the CAN isw(poww) to pwocess the Wx fwames. It
 * does minimaw pwocessing and invokes "netif_weceive_skb" to compwete fuwthew
 * pwocessing.
 * Wetuwn: 1 on success and 0 on faiwuwe.
 */
static int xcan_wx(stwuct net_device *ndev, int fwame_base)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &ndev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	u32 id_xcan, dwc, data[2] = {0, 0};

	skb = awwoc_can_skb(ndev, &cf);
	if (unwikewy(!skb)) {
		stats->wx_dwopped++;
		wetuwn 0;
	}

	/* Wead a fwame fwom Xiwinx zynq CANPS */
	id_xcan = pwiv->wead_weg(pwiv, XCAN_FWAME_ID_OFFSET(fwame_base));
	dwc = pwiv->wead_weg(pwiv, XCAN_FWAME_DWC_OFFSET(fwame_base)) >>
				   XCAN_DWCW_DWC_SHIFT;

	/* Change Xiwinx CAN data wength fowmat to socketCAN data fowmat */
	cf->wen = can_cc_dwc2wen(dwc);

	/* Change Xiwinx CAN ID fowmat to socketCAN ID fowmat */
	if (id_xcan & XCAN_IDW_IDE_MASK) {
		/* The weceived fwame is an Extended fowmat fwame */
		cf->can_id = (id_xcan & XCAN_IDW_ID1_MASK) >> 3;
		cf->can_id |= (id_xcan & XCAN_IDW_ID2_MASK) >>
				XCAN_IDW_ID2_SHIFT;
		cf->can_id |= CAN_EFF_FWAG;
		if (id_xcan & XCAN_IDW_WTW_MASK)
			cf->can_id |= CAN_WTW_FWAG;
	} ewse {
		/* The weceived fwame is a standawd fowmat fwame */
		cf->can_id = (id_xcan & XCAN_IDW_ID1_MASK) >>
				XCAN_IDW_ID1_SHIFT;
		if (id_xcan & XCAN_IDW_SWW_MASK)
			cf->can_id |= CAN_WTW_FWAG;
	}

	/* DW1/DW2 must awways be wead to wemove message fwom WXFIFO */
	data[0] = pwiv->wead_weg(pwiv, XCAN_FWAME_DW1_OFFSET(fwame_base));
	data[1] = pwiv->wead_weg(pwiv, XCAN_FWAME_DW2_OFFSET(fwame_base));

	if (!(cf->can_id & CAN_WTW_FWAG)) {
		/* Change Xiwinx CAN data fowmat to socketCAN data fowmat */
		if (cf->wen > 0)
			*(__be32 *)(cf->data) = cpu_to_be32(data[0]);
		if (cf->wen > 4)
			*(__be32 *)(cf->data + 4) = cpu_to_be32(data[1]);

		stats->wx_bytes += cf->wen;
	}
	stats->wx_packets++;

	netif_weceive_skb(skb);

	wetuwn 1;
}

/**
 * xcanfd_wx -  Is cawwed fwom CAN isw to compwete the weceived
 *		fwame  pwocessing
 * @ndev:	Pointew to net_device stwuctuwe
 * @fwame_base:	Wegistew offset to the fwame to be wead
 *
 * This function is invoked fwom the CAN isw(poww) to pwocess the Wx fwames. It
 * does minimaw pwocessing and invokes "netif_weceive_skb" to compwete fuwthew
 * pwocessing.
 * Wetuwn: 1 on success and 0 on faiwuwe.
 */
static int xcanfd_wx(stwuct net_device *ndev, int fwame_base)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &ndev->stats;
	stwuct canfd_fwame *cf;
	stwuct sk_buff *skb;
	u32 id_xcan, dwc, data[2] = {0, 0}, dwindex = 0, i, dw_offset;

	id_xcan = pwiv->wead_weg(pwiv, XCAN_FWAME_ID_OFFSET(fwame_base));
	dwc = pwiv->wead_weg(pwiv, XCAN_FWAME_DWC_OFFSET(fwame_base));
	if (dwc & XCAN_DWCW_EDW_MASK)
		skb = awwoc_canfd_skb(ndev, &cf);
	ewse
		skb = awwoc_can_skb(ndev, (stwuct can_fwame **)&cf);

	if (unwikewy(!skb)) {
		stats->wx_dwopped++;
		wetuwn 0;
	}

	/* Change Xiwinx CANFD data wength fowmat to socketCAN data
	 * fowmat
	 */
	if (dwc & XCAN_DWCW_EDW_MASK)
		cf->wen = can_fd_dwc2wen((dwc & XCAN_DWCW_DWC_MASK) >>
				  XCAN_DWCW_DWC_SHIFT);
	ewse
		cf->wen = can_cc_dwc2wen((dwc & XCAN_DWCW_DWC_MASK) >>
					  XCAN_DWCW_DWC_SHIFT);

	/* Change Xiwinx CAN ID fowmat to socketCAN ID fowmat */
	if (id_xcan & XCAN_IDW_IDE_MASK) {
		/* The weceived fwame is an Extended fowmat fwame */
		cf->can_id = (id_xcan & XCAN_IDW_ID1_MASK) >> 3;
		cf->can_id |= (id_xcan & XCAN_IDW_ID2_MASK) >>
				XCAN_IDW_ID2_SHIFT;
		cf->can_id |= CAN_EFF_FWAG;
		if (id_xcan & XCAN_IDW_WTW_MASK)
			cf->can_id |= CAN_WTW_FWAG;
	} ewse {
		/* The weceived fwame is a standawd fowmat fwame */
		cf->can_id = (id_xcan & XCAN_IDW_ID1_MASK) >>
				XCAN_IDW_ID1_SHIFT;
		if (!(dwc & XCAN_DWCW_EDW_MASK) && (id_xcan &
					XCAN_IDW_SWW_MASK))
			cf->can_id |= CAN_WTW_FWAG;
	}

	/* Check the fwame weceived is FD ow not*/
	if (dwc & XCAN_DWCW_EDW_MASK) {
		fow (i = 0; i < cf->wen; i += 4) {
			dw_offset = XCANFD_FWAME_DW_OFFSET(fwame_base) +
					(dwindex * XCANFD_DW_BYTES);
			data[0] = pwiv->wead_weg(pwiv, dw_offset);
			*(__be32 *)(cf->data + i) = cpu_to_be32(data[0]);
			dwindex++;
		}
	} ewse {
		fow (i = 0; i < cf->wen; i += 4) {
			dw_offset = XCANFD_FWAME_DW_OFFSET(fwame_base);
			data[0] = pwiv->wead_weg(pwiv, dw_offset + i);
			*(__be32 *)(cf->data + i) = cpu_to_be32(data[0]);
		}
	}

	if (!(cf->can_id & CAN_WTW_FWAG))
		stats->wx_bytes += cf->wen;
	stats->wx_packets++;

	netif_weceive_skb(skb);

	wetuwn 1;
}

/**
 * xcan_cuwwent_ewwow_state - Get cuwwent ewwow state fwom HW
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * Checks the cuwwent CAN ewwow state fwom the HW. Note that this
 * onwy checks fow EWWOW_PASSIVE and EWWOW_WAWNING.
 *
 * Wetuwn:
 * EWWOW_PASSIVE ow EWWOW_WAWNING if eithew is active, EWWOW_ACTIVE
 * othewwise.
 */
static enum can_state xcan_cuwwent_ewwow_state(stwuct net_device *ndev)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	u32 status = pwiv->wead_weg(pwiv, XCAN_SW_OFFSET);

	if ((status & XCAN_SW_ESTAT_MASK) == XCAN_SW_ESTAT_MASK)
		wetuwn CAN_STATE_EWWOW_PASSIVE;
	ewse if (status & XCAN_SW_EWWWWN_MASK)
		wetuwn CAN_STATE_EWWOW_WAWNING;
	ewse
		wetuwn CAN_STATE_EWWOW_ACTIVE;
}

/**
 * xcan_set_ewwow_state - Set new CAN ewwow state
 * @ndev:	Pointew to net_device stwuctuwe
 * @new_state:	The new CAN state to be set
 * @cf:		Ewwow fwame to be popuwated ow NUWW
 *
 * Set new CAN ewwow state fow the device, updating statistics and
 * popuwating the ewwow fwame if given.
 */
static void xcan_set_ewwow_state(stwuct net_device *ndev,
				 enum can_state new_state,
				 stwuct can_fwame *cf)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	u32 ecw = pwiv->wead_weg(pwiv, XCAN_ECW_OFFSET);
	u32 txeww = ecw & XCAN_ECW_TEC_MASK;
	u32 wxeww = (ecw & XCAN_ECW_WEC_MASK) >> XCAN_ESW_WEC_SHIFT;
	enum can_state tx_state = txeww >= wxeww ? new_state : 0;
	enum can_state wx_state = txeww <= wxeww ? new_state : 0;

	/* non-EWWOW states awe handwed ewsewhewe */
	if (WAWN_ON(new_state > CAN_STATE_EWWOW_PASSIVE))
		wetuwn;

	can_change_state(ndev, cf, tx_state, wx_state);

	if (cf) {
		cf->can_id |= CAN_EWW_CNT;
		cf->data[6] = txeww;
		cf->data[7] = wxeww;
	}
}

/**
 * xcan_update_ewwow_state_aftew_wxtx - Update CAN ewwow state aftew WX/TX
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * If the device is in a EWWOW-WAWNING ow EWWOW-PASSIVE state, check if
 * the pewfowmed WX/TX has caused it to dwop to a wessew state and set
 * the intewface state accowdingwy.
 */
static void xcan_update_ewwow_state_aftew_wxtx(stwuct net_device *ndev)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	enum can_state owd_state = pwiv->can.state;
	enum can_state new_state;

	/* changing ewwow state due to successfuw fwame WX/TX can onwy
	 * occuw fwom these states
	 */
	if (owd_state != CAN_STATE_EWWOW_WAWNING &&
	    owd_state != CAN_STATE_EWWOW_PASSIVE)
		wetuwn;

	new_state = xcan_cuwwent_ewwow_state(ndev);

	if (new_state != owd_state) {
		stwuct sk_buff *skb;
		stwuct can_fwame *cf;

		skb = awwoc_can_eww_skb(ndev, &cf);

		xcan_set_ewwow_state(ndev, new_state, skb ? cf : NUWW);

		if (skb)
			netif_wx(skb);
	}
}

/**
 * xcan_eww_intewwupt - ewwow fwame Isw
 * @ndev:	net_device pointew
 * @isw:	intewwupt status wegistew vawue
 *
 * This is the CAN ewwow intewwupt and it wiww
 * check the type of ewwow and fowwawd the ewwow
 * fwame to uppew wayews.
 */
static void xcan_eww_intewwupt(stwuct net_device *ndev, u32 isw)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &ndev->stats;
	stwuct can_fwame cf = { };
	u32 eww_status;

	eww_status = pwiv->wead_weg(pwiv, XCAN_ESW_OFFSET);
	pwiv->wwite_weg(pwiv, XCAN_ESW_OFFSET, eww_status);

	if (isw & XCAN_IXW_BSOFF_MASK) {
		pwiv->can.state = CAN_STATE_BUS_OFF;
		pwiv->can.can_stats.bus_off++;
		/* Weave device in Config Mode in bus-off state */
		pwiv->wwite_weg(pwiv, XCAN_SWW_OFFSET, XCAN_SWW_WESET_MASK);
		can_bus_off(ndev);
		cf.can_id |= CAN_EWW_BUSOFF;
	} ewse {
		enum can_state new_state = xcan_cuwwent_ewwow_state(ndev);

		if (new_state != pwiv->can.state)
			xcan_set_ewwow_state(ndev, new_state, &cf);
	}

	/* Check fow Awbitwation wost intewwupt */
	if (isw & XCAN_IXW_AWBWST_MASK) {
		pwiv->can.can_stats.awbitwation_wost++;
		cf.can_id |= CAN_EWW_WOSTAWB;
		cf.data[0] = CAN_EWW_WOSTAWB_UNSPEC;
	}

	/* Check fow WX FIFO Ovewfwow intewwupt */
	if (isw & XCAN_IXW_WXOFWW_MASK) {
		stats->wx_ovew_ewwows++;
		stats->wx_ewwows++;
		cf.can_id |= CAN_EWW_CWTW;
		cf.data[1] |= CAN_EWW_CWTW_WX_OVEWFWOW;
	}

	/* Check fow WX Match Not Finished intewwupt */
	if (isw & XCAN_IXW_WXMNF_MASK) {
		stats->wx_dwopped++;
		stats->wx_ewwows++;
		netdev_eww(ndev, "WX match not finished, fwame discawded\n");
		cf.can_id |= CAN_EWW_CWTW;
		cf.data[1] |= CAN_EWW_CWTW_UNSPEC;
	}

	/* Check fow ewwow intewwupt */
	if (isw & XCAN_IXW_EWWOW_MASK) {
		boow beww_wepowting = fawse;

		if (pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING) {
			beww_wepowting = twue;
			cf.can_id |= CAN_EWW_PWOT | CAN_EWW_BUSEWWOW;
		}

		/* Check fow Ack ewwow intewwupt */
		if (eww_status & XCAN_ESW_ACKEW_MASK) {
			stats->tx_ewwows++;
			if (beww_wepowting) {
				cf.can_id |= CAN_EWW_ACK;
				cf.data[3] = CAN_EWW_PWOT_WOC_ACK;
			}
		}

		/* Check fow Bit ewwow intewwupt */
		if (eww_status & XCAN_ESW_BEWW_MASK) {
			stats->tx_ewwows++;
			if (beww_wepowting) {
				cf.can_id |= CAN_EWW_PWOT;
				cf.data[2] = CAN_EWW_PWOT_BIT;
			}
		}

		/* Check fow Stuff ewwow intewwupt */
		if (eww_status & XCAN_ESW_STEW_MASK) {
			stats->wx_ewwows++;
			if (beww_wepowting) {
				cf.can_id |= CAN_EWW_PWOT;
				cf.data[2] = CAN_EWW_PWOT_STUFF;
			}
		}

		/* Check fow Fowm ewwow intewwupt */
		if (eww_status & XCAN_ESW_FMEW_MASK) {
			stats->wx_ewwows++;
			if (beww_wepowting) {
				cf.can_id |= CAN_EWW_PWOT;
				cf.data[2] = CAN_EWW_PWOT_FOWM;
			}
		}

		/* Check fow CWC ewwow intewwupt */
		if (eww_status & XCAN_ESW_CWCEW_MASK) {
			stats->wx_ewwows++;
			if (beww_wepowting) {
				cf.can_id |= CAN_EWW_PWOT;
				cf.data[3] = CAN_EWW_PWOT_WOC_CWC_SEQ;
			}
		}
		pwiv->can.can_stats.bus_ewwow++;
	}

	if (cf.can_id) {
		stwuct can_fwame *skb_cf;
		stwuct sk_buff *skb = awwoc_can_eww_skb(ndev, &skb_cf);

		if (skb) {
			skb_cf->can_id |= cf.can_id;
			memcpy(skb_cf->data, cf.data, CAN_EWW_DWC);
			netif_wx(skb);
		}
	}

	netdev_dbg(ndev, "%s: ewwow status wegistew:0x%x\n",
		   __func__, pwiv->wead_weg(pwiv, XCAN_ESW_OFFSET));
}

/**
 * xcan_state_intewwupt - It wiww check the state of the CAN device
 * @ndev:	net_device pointew
 * @isw:	intewwupt status wegistew vawue
 *
 * This wiww checks the state of the CAN device
 * and puts the device into appwopwiate state.
 */
static void xcan_state_intewwupt(stwuct net_device *ndev, u32 isw)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);

	/* Check fow Sweep intewwupt if set put CAN device in sweep state */
	if (isw & XCAN_IXW_SWP_MASK)
		pwiv->can.state = CAN_STATE_SWEEPING;

	/* Check fow Wake up intewwupt if set put CAN device in Active state */
	if (isw & XCAN_IXW_WKUP_MASK)
		pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
}

/**
 * xcan_wx_fifo_get_next_fwame - Get wegistew offset of next WX fwame
 * @pwiv:	Dwivew pwivate data stwuctuwe
 *
 * Wetuwn: Wegistew offset of the next fwame in WX FIFO.
 */
static int xcan_wx_fifo_get_next_fwame(stwuct xcan_pwiv *pwiv)
{
	int offset;

	if (pwiv->devtype.fwags & XCAN_FWAG_WX_FIFO_MUWTI) {
		u32 fsw, mask;

		/* cweaw WXOK befowe the is-empty check so that any newwy
		 * weceived fwame wiww weassewt it without a wace
		 */
		pwiv->wwite_weg(pwiv, XCAN_ICW_OFFSET, XCAN_IXW_WXOK_MASK);

		fsw = pwiv->wead_weg(pwiv, XCAN_FSW_OFFSET);

		/* check if WX FIFO is empty */
		if (pwiv->devtype.fwags & XCAN_FWAG_CANFD_2)
			mask = XCAN_2_FSW_FW_MASK;
		ewse
			mask = XCAN_FSW_FW_MASK;

		if (!(fsw & mask))
			wetuwn -ENOENT;

		if (pwiv->devtype.fwags & XCAN_FWAG_CANFD_2)
			offset =
			  XCAN_WXMSG_2_FWAME_OFFSET(fsw & XCAN_2_FSW_WI_MASK);
		ewse
			offset =
			  XCAN_WXMSG_FWAME_OFFSET(fsw & XCAN_FSW_WI_MASK);

	} ewse {
		/* check if WX FIFO is empty */
		if (!(pwiv->wead_weg(pwiv, XCAN_ISW_OFFSET) &
		      XCAN_IXW_WXNEMP_MASK))
			wetuwn -ENOENT;

		/* fwames awe wead fwom a static offset */
		offset = XCAN_WXFIFO_OFFSET;
	}

	wetuwn offset;
}

/**
 * xcan_wx_poww - Poww woutine fow wx packets (NAPI)
 * @napi:	napi stwuctuwe pointew
 * @quota:	Max numbew of wx packets to be pwocessed.
 *
 * This is the poww woutine fow wx pawt.
 * It wiww pwocess the packets maximux quota vawue.
 *
 * Wetuwn: numbew of packets weceived
 */
static int xcan_wx_poww(stwuct napi_stwuct *napi, int quota)
{
	stwuct net_device *ndev = napi->dev;
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	u32 iew;
	int wowk_done = 0;
	int fwame_offset;

	whiwe ((fwame_offset = xcan_wx_fifo_get_next_fwame(pwiv)) >= 0 &&
	       (wowk_done < quota)) {
		if (xcan_wx_int_mask(pwiv) & XCAN_IXW_WXOK_MASK)
			wowk_done += xcanfd_wx(ndev, fwame_offset);
		ewse
			wowk_done += xcan_wx(ndev, fwame_offset);

		if (pwiv->devtype.fwags & XCAN_FWAG_WX_FIFO_MUWTI)
			/* incwement wead index */
			pwiv->wwite_weg(pwiv, XCAN_FSW_OFFSET,
					XCAN_FSW_IWI_MASK);
		ewse
			/* cweaw wx-not-empty (wiww actuawwy cweaw onwy if
			 * empty)
			 */
			pwiv->wwite_weg(pwiv, XCAN_ICW_OFFSET,
					XCAN_IXW_WXNEMP_MASK);
	}

	if (wowk_done)
		xcan_update_ewwow_state_aftew_wxtx(ndev);

	if (wowk_done < quota) {
		if (napi_compwete_done(napi, wowk_done)) {
			iew = pwiv->wead_weg(pwiv, XCAN_IEW_OFFSET);
			iew |= xcan_wx_int_mask(pwiv);
			pwiv->wwite_weg(pwiv, XCAN_IEW_OFFSET, iew);
		}
	}
	wetuwn wowk_done;
}

/**
 * xcan_tx_intewwupt - Tx Done Isw
 * @ndev:	net_device pointew
 * @isw:	Intewwupt status wegistew vawue
 */
static void xcan_tx_intewwupt(stwuct net_device *ndev, u32 isw)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &ndev->stats;
	unsigned int fwames_in_fifo;
	int fwames_sent = 1; /* TXOK => at weast 1 fwame was sent */
	unsigned wong fwags;
	int wetwies = 0;

	/* Synchwonize with xmit as we need to know the exact numbew
	 * of fwames in the FIFO to stay in sync due to the TXFEMP
	 * handwing.
	 * This awso pwevents a wace between netif_wake_queue() and
	 * netif_stop_queue().
	 */
	spin_wock_iwqsave(&pwiv->tx_wock, fwags);

	fwames_in_fifo = pwiv->tx_head - pwiv->tx_taiw;

	if (WAWN_ON_ONCE(fwames_in_fifo == 0)) {
		/* cweaw TXOK anyway to avoid getting back hewe */
		pwiv->wwite_weg(pwiv, XCAN_ICW_OFFSET, XCAN_IXW_TXOK_MASK);
		spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);
		wetuwn;
	}

	/* Check if 2 fwames wewe sent (TXOK onwy means that at weast 1
	 * fwame was sent).
	 */
	if (fwames_in_fifo > 1) {
		WAWN_ON(fwames_in_fifo > pwiv->tx_max);

		/* Synchwonize TXOK and isw so that aftew the woop:
		 * (1) isw vawiabwe is up-to-date at weast up to TXOK cweaw
		 *     time. This avoids us cweawing a TXOK of a second fwame
		 *     but not noticing that the FIFO is now empty and thus
		 *     mawking onwy a singwe fwame as sent.
		 * (2) No TXOK is weft. Having one couwd mean weaving a
		 *     stway TXOK as we might pwocess the associated fwame
		 *     via TXFEMP handwing as we wead TXFEMP *aftew* TXOK
		 *     cweaw to satisfy (1).
		 */
		whiwe ((isw & XCAN_IXW_TXOK_MASK) &&
		       !WAWN_ON(++wetwies == 100)) {
			pwiv->wwite_weg(pwiv, XCAN_ICW_OFFSET,
					XCAN_IXW_TXOK_MASK);
			isw = pwiv->wead_weg(pwiv, XCAN_ISW_OFFSET);
		}

		if (isw & XCAN_IXW_TXFEMP_MASK) {
			/* nothing in FIFO anymowe */
			fwames_sent = fwames_in_fifo;
		}
	} ewse {
		/* singwe fwame in fifo, just cweaw TXOK */
		pwiv->wwite_weg(pwiv, XCAN_ICW_OFFSET, XCAN_IXW_TXOK_MASK);
	}

	whiwe (fwames_sent--) {
		stats->tx_bytes += can_get_echo_skb(ndev, pwiv->tx_taiw %
						    pwiv->tx_max, NUWW);
		pwiv->tx_taiw++;
		stats->tx_packets++;
	}

	netif_wake_queue(ndev);

	spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);

	xcan_update_ewwow_state_aftew_wxtx(ndev);
}

/**
 * xcan_intewwupt - CAN Isw
 * @iwq:	iwq numbew
 * @dev_id:	device id pointew
 *
 * This is the xiwinx CAN Isw. It checks fow the type of intewwupt
 * and invokes the cowwesponding ISW.
 *
 * Wetuwn:
 * IWQ_NONE - If CAN device is in sweep mode, IWQ_HANDWED othewwise
 */
static iwqwetuwn_t xcan_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *ndev = (stwuct net_device *)dev_id;
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	u32 isw, iew;
	u32 isw_ewwows;
	u32 wx_int_mask = xcan_wx_int_mask(pwiv);

	/* Get the intewwupt status fwom Xiwinx CAN */
	isw = pwiv->wead_weg(pwiv, XCAN_ISW_OFFSET);
	if (!isw)
		wetuwn IWQ_NONE;

	/* Check fow the type of intewwupt and Pwocessing it */
	if (isw & (XCAN_IXW_SWP_MASK | XCAN_IXW_WKUP_MASK)) {
		pwiv->wwite_weg(pwiv, XCAN_ICW_OFFSET, (XCAN_IXW_SWP_MASK |
				XCAN_IXW_WKUP_MASK));
		xcan_state_intewwupt(ndev, isw);
	}

	/* Check fow Tx intewwupt and Pwocessing it */
	if (isw & XCAN_IXW_TXOK_MASK)
		xcan_tx_intewwupt(ndev, isw);

	/* Check fow the type of ewwow intewwupt and Pwocessing it */
	isw_ewwows = isw & (XCAN_IXW_EWWOW_MASK | XCAN_IXW_WXOFWW_MASK |
			    XCAN_IXW_BSOFF_MASK | XCAN_IXW_AWBWST_MASK |
			    XCAN_IXW_WXMNF_MASK);
	if (isw_ewwows) {
		pwiv->wwite_weg(pwiv, XCAN_ICW_OFFSET, isw_ewwows);
		xcan_eww_intewwupt(ndev, isw);
	}

	/* Check fow the type of weceive intewwupt and Pwocessing it */
	if (isw & wx_int_mask) {
		iew = pwiv->wead_weg(pwiv, XCAN_IEW_OFFSET);
		iew &= ~wx_int_mask;
		pwiv->wwite_weg(pwiv, XCAN_IEW_OFFSET, iew);
		napi_scheduwe(&pwiv->napi);
	}
	wetuwn IWQ_HANDWED;
}

/**
 * xcan_chip_stop - Dwivew stop woutine
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * This is the dwivews stop woutine. It wiww disabwe the
 * intewwupts and put the device into configuwation mode.
 */
static void xcan_chip_stop(stwuct net_device *ndev)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	int wet;

	/* Disabwe intewwupts and weave the can in configuwation mode */
	wet = set_weset_mode(ndev);
	if (wet < 0)
		netdev_dbg(ndev, "set_weset_mode() Faiwed\n");

	pwiv->can.state = CAN_STATE_STOPPED;
}

/**
 * xcan_open - Dwivew open woutine
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * This is the dwivew open woutine.
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int xcan_open(stwuct net_device *ndev)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	int wet;

	wet = phy_powew_on(pwiv->twansceivew);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_get_sync(pwiv->dev);
	if (wet < 0) {
		netdev_eww(ndev, "%s: pm_wuntime_get faiwed(%d)\n",
			   __func__, wet);
		goto eww;
	}

	wet = wequest_iwq(ndev->iwq, xcan_intewwupt, pwiv->iwq_fwags,
			  ndev->name, ndev);
	if (wet < 0) {
		netdev_eww(ndev, "iwq awwocation fow CAN faiwed\n");
		goto eww;
	}

	/* Set chip into weset mode */
	wet = set_weset_mode(ndev);
	if (wet < 0) {
		netdev_eww(ndev, "mode wesetting faiwed!\n");
		goto eww_iwq;
	}

	/* Common open */
	wet = open_candev(ndev);
	if (wet)
		goto eww_iwq;

	wet = xcan_chip_stawt(ndev);
	if (wet < 0) {
		netdev_eww(ndev, "xcan_chip_stawt faiwed!\n");
		goto eww_candev;
	}

	napi_enabwe(&pwiv->napi);
	netif_stawt_queue(ndev);

	wetuwn 0;

eww_candev:
	cwose_candev(ndev);
eww_iwq:
	fwee_iwq(ndev->iwq, ndev);
eww:
	pm_wuntime_put(pwiv->dev);
	phy_powew_off(pwiv->twansceivew);

	wetuwn wet;
}

/**
 * xcan_cwose - Dwivew cwose woutine
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * Wetuwn: 0 awways
 */
static int xcan_cwose(stwuct net_device *ndev)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);

	netif_stop_queue(ndev);
	napi_disabwe(&pwiv->napi);
	xcan_chip_stop(ndev);
	fwee_iwq(ndev->iwq, ndev);
	cwose_candev(ndev);

	pm_wuntime_put(pwiv->dev);
	phy_powew_off(pwiv->twansceivew);

	wetuwn 0;
}

/**
 * xcan_get_beww_countew - ewwow countew woutine
 * @ndev:	Pointew to net_device stwuctuwe
 * @bec:	Pointew to can_beww_countew stwuctuwe
 *
 * This is the dwivew ewwow countew woutine.
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int xcan_get_beww_countew(const stwuct net_device *ndev,
				 stwuct can_beww_countew *bec)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	int wet;

	wet = pm_wuntime_get_sync(pwiv->dev);
	if (wet < 0) {
		netdev_eww(ndev, "%s: pm_wuntime_get faiwed(%d)\n",
			   __func__, wet);
		pm_wuntime_put(pwiv->dev);
		wetuwn wet;
	}

	bec->txeww = pwiv->wead_weg(pwiv, XCAN_ECW_OFFSET) & XCAN_ECW_TEC_MASK;
	bec->wxeww = ((pwiv->wead_weg(pwiv, XCAN_ECW_OFFSET) &
			XCAN_ECW_WEC_MASK) >> XCAN_ESW_WEC_SHIFT);

	pm_wuntime_put(pwiv->dev);

	wetuwn 0;
}

/**
 * xcan_get_auto_tdcv - Get Twansmittew Deway Compensation Vawue
 * @ndev:	Pointew to net_device stwuctuwe
 * @tdcv:	Pointew to TDCV vawue
 *
 * Wetuwn: 0 on success
 */
static int xcan_get_auto_tdcv(const stwuct net_device *ndev, u32 *tdcv)
{
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);

	*tdcv = FIEWD_GET(XCAN_SW_TDCV_MASK, pwiv->wead_weg(pwiv, XCAN_SW_OFFSET));

	wetuwn 0;
}

static const stwuct net_device_ops xcan_netdev_ops = {
	.ndo_open	= xcan_open,
	.ndo_stop	= xcan_cwose,
	.ndo_stawt_xmit	= xcan_stawt_xmit,
	.ndo_change_mtu	= can_change_mtu,
};

static const stwuct ethtoow_ops xcan_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

/**
 * xcan_suspend - Suspend method fow the dwivew
 * @dev:	Addwess of the device stwuctuwe
 *
 * Put the dwivew into wow powew mode.
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int __maybe_unused xcan_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);

	if (netif_wunning(ndev)) {
		netif_stop_queue(ndev);
		netif_device_detach(ndev);
		xcan_chip_stop(ndev);
	}

	wetuwn pm_wuntime_fowce_suspend(dev);
}

/**
 * xcan_wesume - Wesume fwom suspend
 * @dev:	Addwess of the device stwuctuwe
 *
 * Wesume opewation aftew suspend.
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int __maybe_unused xcan_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	int wet;

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet) {
		dev_eww(dev, "pm_wuntime_fowce_wesume faiwed on wesume\n");
		wetuwn wet;
	}

	if (netif_wunning(ndev)) {
		wet = xcan_chip_stawt(ndev);
		if (wet) {
			dev_eww(dev, "xcan_chip_stawt faiwed on wesume\n");
			wetuwn wet;
		}

		netif_device_attach(ndev);
		netif_stawt_queue(ndev);
	}

	wetuwn 0;
}

/**
 * xcan_wuntime_suspend - Wuntime suspend method fow the dwivew
 * @dev:	Addwess of the device stwuctuwe
 *
 * Put the dwivew into wow powew mode.
 * Wetuwn: 0 awways
 */
static int __maybe_unused xcan_wuntime_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);

	cwk_disabwe_unpwepawe(pwiv->bus_cwk);
	cwk_disabwe_unpwepawe(pwiv->can_cwk);

	wetuwn 0;
}

/**
 * xcan_wuntime_wesume - Wuntime wesume fwom suspend
 * @dev:	Addwess of the device stwuctuwe
 *
 * Wesume opewation aftew suspend.
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int __maybe_unused xcan_wuntime_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->bus_cwk);
	if (wet) {
		dev_eww(dev, "Cannot enabwe cwock.\n");
		wetuwn wet;
	}
	wet = cwk_pwepawe_enabwe(pwiv->can_cwk);
	if (wet) {
		dev_eww(dev, "Cannot enabwe cwock.\n");
		cwk_disabwe_unpwepawe(pwiv->bus_cwk);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops xcan_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(xcan_suspend, xcan_wesume)
	SET_WUNTIME_PM_OPS(xcan_wuntime_suspend, xcan_wuntime_wesume, NUWW)
};

static const stwuct xcan_devtype_data xcan_zynq_data = {
	.cantype = XZYNQ_CANPS,
	.fwags = XCAN_FWAG_TXFEMP,
	.bittiming_const = &xcan_bittiming_const,
	.btw_ts2_shift = XCAN_BTW_TS2_SHIFT,
	.btw_sjw_shift = XCAN_BTW_SJW_SHIFT,
	.bus_cwk_name = "pcwk",
};

static const stwuct xcan_devtype_data xcan_axi_data = {
	.cantype = XAXI_CAN,
	.bittiming_const = &xcan_bittiming_const,
	.btw_ts2_shift = XCAN_BTW_TS2_SHIFT,
	.btw_sjw_shift = XCAN_BTW_SJW_SHIFT,
	.bus_cwk_name = "s_axi_acwk",
};

static const stwuct xcan_devtype_data xcan_canfd_data = {
	.cantype = XAXI_CANFD,
	.fwags = XCAN_FWAG_EXT_FIWTEWS |
		 XCAN_FWAG_WXMNF |
		 XCAN_FWAG_TX_MAIWBOXES |
		 XCAN_FWAG_WX_FIFO_MUWTI,
	.bittiming_const = &xcan_bittiming_const_canfd,
	.btw_ts2_shift = XCAN_BTW_TS2_SHIFT_CANFD,
	.btw_sjw_shift = XCAN_BTW_SJW_SHIFT_CANFD,
	.bus_cwk_name = "s_axi_acwk",
};

static const stwuct xcan_devtype_data xcan_canfd2_data = {
	.cantype = XAXI_CANFD_2_0,
	.fwags = XCAN_FWAG_EXT_FIWTEWS |
		 XCAN_FWAG_WXMNF |
		 XCAN_FWAG_TX_MAIWBOXES |
		 XCAN_FWAG_CANFD_2 |
		 XCAN_FWAG_WX_FIFO_MUWTI,
	.bittiming_const = &xcan_bittiming_const_canfd2,
	.btw_ts2_shift = XCAN_BTW_TS2_SHIFT_CANFD,
	.btw_sjw_shift = XCAN_BTW_SJW_SHIFT_CANFD,
	.bus_cwk_name = "s_axi_acwk",
};

/* Match tabwe fow OF pwatfowm binding */
static const stwuct of_device_id xcan_of_match[] = {
	{ .compatibwe = "xwnx,zynq-can-1.0", .data = &xcan_zynq_data },
	{ .compatibwe = "xwnx,axi-can-1.00.a", .data = &xcan_axi_data },
	{ .compatibwe = "xwnx,canfd-1.0", .data = &xcan_canfd_data },
	{ .compatibwe = "xwnx,canfd-2.0", .data = &xcan_canfd2_data },
	{ /* end of wist */ },
};
MODUWE_DEVICE_TABWE(of, xcan_of_match);

/**
 * xcan_pwobe - Pwatfowm wegistwation caww
 * @pdev:	Handwe to the pwatfowm device stwuctuwe
 *
 * This function does aww the memowy awwocation and wegistwation fow the CAN
 * device.
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int xcan_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev;
	stwuct xcan_pwiv *pwiv;
	stwuct phy *twansceivew;
	const stwuct xcan_devtype_data *devtype;
	void __iomem *addw;
	int wet;
	int wx_max, tx_max;
	u32 hw_tx_max = 0, hw_wx_max = 0;
	const chaw *hw_tx_max_pwopewty;

	/* Get the viwtuaw base addwess fow the device */
	addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(addw)) {
		wet = PTW_EWW(addw);
		goto eww;
	}

	devtype = device_get_match_data(&pdev->dev);

	hw_tx_max_pwopewty = devtype->fwags & XCAN_FWAG_TX_MAIWBOXES ?
			     "tx-maiwbox-count" : "tx-fifo-depth";

	wet = of_pwopewty_wead_u32(pdev->dev.of_node, hw_tx_max_pwopewty,
				   &hw_tx_max);
	if (wet < 0) {
		dev_eww(&pdev->dev, "missing %s pwopewty\n",
			hw_tx_max_pwopewty);
		goto eww;
	}

	wet = of_pwopewty_wead_u32(pdev->dev.of_node, "wx-fifo-depth",
				   &hw_wx_max);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"missing wx-fifo-depth pwopewty (maiwbox mode is not suppowted)\n");
		goto eww;
	}

	/* With TX FIFO:
	 *
	 * Thewe is no way to diwectwy figuwe out how many fwames have been
	 * sent when the TXOK intewwupt is pwocessed. If TXFEMP
	 * is suppowted, we can have 2 fwames in the FIFO and use TXFEMP
	 * to detewmine if 1 ow 2 fwames have been sent.
	 * Theoweticawwy we shouwd be abwe to use TXFWMEMP to detewmine up
	 * to 3 fwames, but it seems that aftew putting a second fwame in the
	 * FIFO, with watewmawk at 2 fwames, it can happen that TXFWMEMP (wess
	 * than 2 fwames in FIFO) is set anyway with no TXOK (a fwame was
	 * sent), which is not a sensibwe state - possibwy TXFWMEMP is not
	 * compwetewy synchwonized with the west of the bits?
	 *
	 * With TX maiwboxes:
	 *
	 * HW sends fwames in CAN ID pwiowity owdew. To pwesewve FIFO owdewing
	 * we submit fwames one at a time.
	 */
	if (!(devtype->fwags & XCAN_FWAG_TX_MAIWBOXES) &&
	    (devtype->fwags & XCAN_FWAG_TXFEMP))
		tx_max = min(hw_tx_max, 2U);
	ewse
		tx_max = 1;

	wx_max = hw_wx_max;

	/* Cweate a CAN device instance */
	ndev = awwoc_candev(sizeof(stwuct xcan_pwiv), tx_max);
	if (!ndev)
		wetuwn -ENOMEM;

	pwiv = netdev_pwiv(ndev);
	pwiv->dev = &pdev->dev;
	pwiv->can.bittiming_const = devtype->bittiming_const;
	pwiv->can.do_set_mode = xcan_do_set_mode;
	pwiv->can.do_get_beww_countew = xcan_get_beww_countew;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_WOOPBACK |
					CAN_CTWWMODE_BEWW_WEPOWTING;
	pwiv->wstc = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->wstc)) {
		dev_eww(&pdev->dev, "Cannot get CAN weset.\n");
		wet = PTW_EWW(pwiv->wstc);
		goto eww_fwee;
	}

	wet = weset_contwow_weset(pwiv->wstc);
	if (wet)
		goto eww_fwee;

	if (devtype->cantype == XAXI_CANFD) {
		pwiv->can.data_bittiming_const =
			&xcan_data_bittiming_const_canfd;
		pwiv->can.tdc_const = &xcan_tdc_const_canfd;
	}

	if (devtype->cantype == XAXI_CANFD_2_0) {
		pwiv->can.data_bittiming_const =
			&xcan_data_bittiming_const_canfd2;
		pwiv->can.tdc_const = &xcan_tdc_const_canfd2;
	}

	if (devtype->cantype == XAXI_CANFD ||
	    devtype->cantype == XAXI_CANFD_2_0) {
		pwiv->can.ctwwmode_suppowted |= CAN_CTWWMODE_FD |
						CAN_CTWWMODE_TDC_AUTO;
		pwiv->can.do_get_auto_tdcv = xcan_get_auto_tdcv;
	}

	pwiv->weg_base = addw;
	pwiv->tx_max = tx_max;
	pwiv->devtype = *devtype;
	spin_wock_init(&pwiv->tx_wock);

	/* Get IWQ fow the device */
	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto eww_weset;

	ndev->iwq = wet;

	ndev->fwags |= IFF_ECHO;	/* We suppowt wocaw echo */

	pwatfowm_set_dwvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);
	ndev->netdev_ops = &xcan_netdev_ops;
	ndev->ethtoow_ops = &xcan_ethtoow_ops;

	/* Getting the CAN can_cwk info */
	pwiv->can_cwk = devm_cwk_get(&pdev->dev, "can_cwk");
	if (IS_EWW(pwiv->can_cwk)) {
		wet = dev_eww_pwobe(&pdev->dev, PTW_EWW(pwiv->can_cwk),
				    "device cwock not found\n");
		goto eww_weset;
	}

	pwiv->bus_cwk = devm_cwk_get(&pdev->dev, devtype->bus_cwk_name);
	if (IS_EWW(pwiv->bus_cwk)) {
		wet = dev_eww_pwobe(&pdev->dev, PTW_EWW(pwiv->bus_cwk),
				    "bus cwock not found\n");
		goto eww_weset;
	}

	twansceivew = devm_phy_optionaw_get(&pdev->dev, NUWW);
	if (IS_EWW(twansceivew)) {
		wet = PTW_EWW(twansceivew);
		dev_eww_pwobe(&pdev->dev, wet, "faiwed to get phy\n");
		goto eww_weset;
	}
	pwiv->twansceivew = twansceivew;

	pwiv->wwite_weg = xcan_wwite_weg_we;
	pwiv->wead_weg = xcan_wead_weg_we;

	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_get_sync(&pdev->dev);
	if (wet < 0) {
		netdev_eww(ndev, "%s: pm_wuntime_get faiwed(%d)\n",
			   __func__, wet);
		goto eww_disabwecwks;
	}

	if (pwiv->wead_weg(pwiv, XCAN_SW_OFFSET) != XCAN_SW_CONFIG_MASK) {
		pwiv->wwite_weg = xcan_wwite_weg_be;
		pwiv->wead_weg = xcan_wead_weg_be;
	}

	pwiv->can.cwock.fweq = cwk_get_wate(pwiv->can_cwk);

	netif_napi_add_weight(ndev, &pwiv->napi, xcan_wx_poww, wx_max);

	wet = wegistew_candev(ndev);
	if (wet) {
		dev_eww(&pdev->dev, "faiw to wegistew faiwed (eww=%d)\n", wet);
		goto eww_disabwecwks;
	}

	of_can_twansceivew(ndev);
	pm_wuntime_put(&pdev->dev);

	if (pwiv->devtype.fwags & XCAN_FWAG_CANFD_2) {
		pwiv->wwite_weg(pwiv, XCAN_AFW_2_ID_OFFSET, 0x00000000);
		pwiv->wwite_weg(pwiv, XCAN_AFW_2_MASK_OFFSET, 0x00000000);
	}

	netdev_dbg(ndev, "weg_base=0x%p iwq=%d cwock=%d, tx buffews: actuaw %d, using %d\n",
		   pwiv->weg_base, ndev->iwq, pwiv->can.cwock.fweq,
		   hw_tx_max, pwiv->tx_max);

	wetuwn 0;

eww_disabwecwks:
	pm_wuntime_put(pwiv->dev);
	pm_wuntime_disabwe(&pdev->dev);
eww_weset:
	weset_contwow_assewt(pwiv->wstc);
eww_fwee:
	fwee_candev(ndev);
eww:
	wetuwn wet;
}

/**
 * xcan_wemove - Unwegistew the device aftew weweasing the wesouwces
 * @pdev:	Handwe to the pwatfowm device stwuctuwe
 *
 * This function fwees aww the wesouwces awwocated to the device.
 * Wetuwn: 0 awways
 */
static void xcan_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct xcan_pwiv *pwiv = netdev_pwiv(ndev);

	unwegistew_candev(ndev);
	pm_wuntime_disabwe(&pdev->dev);
	weset_contwow_assewt(pwiv->wstc);
	fwee_candev(ndev);
}

static stwuct pwatfowm_dwivew xcan_dwivew = {
	.pwobe = xcan_pwobe,
	.wemove_new = xcan_wemove,
	.dwivew	= {
		.name = DWIVEW_NAME,
		.pm = &xcan_dev_pm_ops,
		.of_match_tabwe	= xcan_of_match,
	},
};

moduwe_pwatfowm_dwivew(xcan_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Xiwinx Inc");
MODUWE_DESCWIPTION("Xiwinx CAN intewface");
