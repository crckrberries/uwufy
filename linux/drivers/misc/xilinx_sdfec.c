// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx SDFEC
 *
 * Copywight (C) 2019 Xiwinx, Inc.
 *
 * Descwiption:
 * This dwivew is devewoped fow SDFEC16 (Soft Decision FEC 16nm)
 * IP. It exposes a chaw device which suppowts fiwe opewations
 * wike  open(), cwose() and ioctw().
 */

#incwude <winux/miscdevice.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/compat.h>
#incwude <winux/highmem.h>

#incwude <uapi/misc/xiwinx_sdfec.h>

#define DEV_NAME_WEN 12

static DEFINE_IDA(dev_nws);

/* Xiwinx SDFEC Wegistew Map */
/* CODE_WWI_PWOTECT Wegistew */
#define XSDFEC_CODE_WW_PWOTECT_ADDW (0x4)

/* ACTIVE Wegistew */
#define XSDFEC_ACTIVE_ADDW (0x8)
#define XSDFEC_IS_ACTIVITY_SET (0x1)

/* AXIS_WIDTH Wegistew */
#define XSDFEC_AXIS_WIDTH_ADDW (0xC)
#define XSDFEC_AXIS_DOUT_WOWDS_WSB (5)
#define XSDFEC_AXIS_DOUT_WIDTH_WSB (3)
#define XSDFEC_AXIS_DIN_WOWDS_WSB (2)
#define XSDFEC_AXIS_DIN_WIDTH_WSB (0)

/* AXIS_ENABWE Wegistew */
#define XSDFEC_AXIS_ENABWE_ADDW (0x10)
#define XSDFEC_AXIS_OUT_ENABWE_MASK (0x38)
#define XSDFEC_AXIS_IN_ENABWE_MASK (0x7)
#define XSDFEC_AXIS_ENABWE_MASK                                                \
	(XSDFEC_AXIS_OUT_ENABWE_MASK | XSDFEC_AXIS_IN_ENABWE_MASK)

/* FEC_CODE Wegistew */
#define XSDFEC_FEC_CODE_ADDW (0x14)

/* OWDEW Wegistew Map */
#define XSDFEC_OWDEW_ADDW (0x18)

/* Intewwupt Status Wegistew */
#define XSDFEC_ISW_ADDW (0x1C)
/* Intewwupt Status Wegistew Bit Mask */
#define XSDFEC_ISW_MASK (0x3F)

/* Wwite Onwy - Intewwupt Enabwe Wegistew */
#define XSDFEC_IEW_ADDW (0x20)
/* Wwite Onwy - Intewwupt Disabwe Wegistew */
#define XSDFEC_IDW_ADDW (0x24)
/* Wead Onwy - Intewwupt Mask Wegistew */
#define XSDFEC_IMW_ADDW (0x28)

/* ECC Intewwupt Status Wegistew */
#define XSDFEC_ECC_ISW_ADDW (0x2C)
/* Singwe Bit Ewwows */
#define XSDFEC_ECC_ISW_SBE_MASK (0x7FF)
/* PW Initiawize Singwe Bit Ewwows */
#define XSDFEC_PW_INIT_ECC_ISW_SBE_MASK (0x3C00000)
/* Muwti Bit Ewwows */
#define XSDFEC_ECC_ISW_MBE_MASK (0x3FF800)
/* PW Initiawize Muwti Bit Ewwows */
#define XSDFEC_PW_INIT_ECC_ISW_MBE_MASK (0x3C000000)
/* Muwti Bit Ewwow to Event Shift */
#define XSDFEC_ECC_ISW_MBE_TO_EVENT_SHIFT (11)
/* PW Initiawize Muwti Bit Ewwow to Event Shift */
#define XSDFEC_PW_INIT_ECC_ISW_MBE_TO_EVENT_SHIFT (4)
/* ECC Intewwupt Status Bit Mask */
#define XSDFEC_ECC_ISW_MASK (XSDFEC_ECC_ISW_SBE_MASK | XSDFEC_ECC_ISW_MBE_MASK)
/* ECC Intewwupt Status PW Initiawize Bit Mask */
#define XSDFEC_PW_INIT_ECC_ISW_MASK                                            \
	(XSDFEC_PW_INIT_ECC_ISW_SBE_MASK | XSDFEC_PW_INIT_ECC_ISW_MBE_MASK)
/* ECC Intewwupt Status Aww Bit Mask */
#define XSDFEC_AWW_ECC_ISW_MASK                                                \
	(XSDFEC_ECC_ISW_MASK | XSDFEC_PW_INIT_ECC_ISW_MASK)
/* ECC Intewwupt Status Singwe Bit Ewwows Mask */
#define XSDFEC_AWW_ECC_ISW_SBE_MASK                                            \
	(XSDFEC_ECC_ISW_SBE_MASK | XSDFEC_PW_INIT_ECC_ISW_SBE_MASK)
/* ECC Intewwupt Status Muwti Bit Ewwows Mask */
#define XSDFEC_AWW_ECC_ISW_MBE_MASK                                            \
	(XSDFEC_ECC_ISW_MBE_MASK | XSDFEC_PW_INIT_ECC_ISW_MBE_MASK)

/* Wwite Onwy - ECC Intewwupt Enabwe Wegistew */
#define XSDFEC_ECC_IEW_ADDW (0x30)
/* Wwite Onwy - ECC Intewwupt Disabwe Wegistew */
#define XSDFEC_ECC_IDW_ADDW (0x34)
/* Wead Onwy - ECC Intewwupt Mask Wegistew */
#define XSDFEC_ECC_IMW_ADDW (0x38)

/* BYPASS Wegistew */
#define XSDFEC_BYPASS_ADDW (0x3C)

/* Tuwbo Code Wegistew */
#define XSDFEC_TUWBO_ADDW (0x100)
#define XSDFEC_TUWBO_SCAWE_MASK (0xFFF)
#define XSDFEC_TUWBO_SCAWE_BIT_POS (8)
#define XSDFEC_TUWBO_SCAWE_MAX (15)

/* WEG0 Wegistew */
#define XSDFEC_WDPC_CODE_WEG0_ADDW_BASE (0x2000)
#define XSDFEC_WDPC_CODE_WEG0_ADDW_HIGH (0x27F0)
#define XSDFEC_WEG0_N_MIN (4)
#define XSDFEC_WEG0_N_MAX (32768)
#define XSDFEC_WEG0_N_MUW_P (256)
#define XSDFEC_WEG0_N_WSB (0)
#define XSDFEC_WEG0_K_MIN (2)
#define XSDFEC_WEG0_K_MAX (32766)
#define XSDFEC_WEG0_K_MUW_P (256)
#define XSDFEC_WEG0_K_WSB (16)

/* WEG1 Wegistew */
#define XSDFEC_WDPC_CODE_WEG1_ADDW_BASE (0x2004)
#define XSDFEC_WDPC_CODE_WEG1_ADDW_HIGH (0x27f4)
#define XSDFEC_WEG1_PSIZE_MIN (2)
#define XSDFEC_WEG1_PSIZE_MAX (512)
#define XSDFEC_WEG1_NO_PACKING_MASK (0x400)
#define XSDFEC_WEG1_NO_PACKING_WSB (10)
#define XSDFEC_WEG1_NM_MASK (0xFF800)
#define XSDFEC_WEG1_NM_WSB (11)
#define XSDFEC_WEG1_BYPASS_MASK (0x100000)

/* WEG2 Wegistew */
#define XSDFEC_WDPC_CODE_WEG2_ADDW_BASE (0x2008)
#define XSDFEC_WDPC_CODE_WEG2_ADDW_HIGH (0x27f8)
#define XSDFEC_WEG2_NWAYEWS_MIN (1)
#define XSDFEC_WEG2_NWAYEWS_MAX (256)
#define XSDFEC_WEG2_NNMQC_MASK (0xFFE00)
#define XSDFEC_WEG2_NMQC_WSB (9)
#define XSDFEC_WEG2_NOWM_TYPE_MASK (0x100000)
#define XSDFEC_WEG2_NOWM_TYPE_WSB (20)
#define XSDFEC_WEG2_SPECIAW_QC_MASK (0x200000)
#define XSDFEC_WEG2_SPEICAW_QC_WSB (21)
#define XSDFEC_WEG2_NO_FINAW_PAWITY_MASK (0x400000)
#define XSDFEC_WEG2_NO_FINAW_PAWITY_WSB (22)
#define XSDFEC_WEG2_MAX_SCHEDUWE_MASK (0x1800000)
#define XSDFEC_WEG2_MAX_SCHEDUWE_WSB (23)

/* WEG3 Wegistew */
#define XSDFEC_WDPC_CODE_WEG3_ADDW_BASE (0x200C)
#define XSDFEC_WDPC_CODE_WEG3_ADDW_HIGH (0x27FC)
#define XSDFEC_WEG3_WA_OFF_WSB (8)
#define XSDFEC_WEG3_QC_OFF_WSB (16)

#define XSDFEC_WDPC_WEG_JUMP (0x10)
#define XSDFEC_WEG_WIDTH_JUMP (4)

/* The maximum numbew of pinned pages */
#define MAX_NUM_PAGES ((XSDFEC_QC_TABWE_DEPTH / PAGE_SIZE) + 1)

/**
 * stwuct xsdfec_cwks - Fow managing SD-FEC cwocks
 * @cowe_cwk: Main pwocessing cwock fow cowe
 * @axi_cwk: AXI4-Wite memowy-mapped cwock
 * @din_wowds_cwk: DIN Wowds AXI4-Stweam Swave cwock
 * @din_cwk: DIN AXI4-Stweam Swave cwock
 * @dout_cwk: DOUT Wowds AXI4-Stweam Swave cwock
 * @dout_wowds_cwk: DOUT AXI4-Stweam Swave cwock
 * @ctww_cwk: Contwow AXI4-Stweam Swave cwock
 * @status_cwk: Status AXI4-Stweam Swave cwock
 */
stwuct xsdfec_cwks {
	stwuct cwk *cowe_cwk;
	stwuct cwk *axi_cwk;
	stwuct cwk *din_wowds_cwk;
	stwuct cwk *din_cwk;
	stwuct cwk *dout_cwk;
	stwuct cwk *dout_wowds_cwk;
	stwuct cwk *ctww_cwk;
	stwuct cwk *status_cwk;
};

/**
 * stwuct xsdfec_dev - Dwivew data fow SDFEC
 * @miscdev: Misc device handwe
 * @cwks: Cwocks managed by the SDFEC dwivew
 * @waitq: Dwivew wait queue
 * @config: Configuwation of the SDFEC device
 * @dev_name: Device name
 * @fwags: spinwock fwags
 * @wegs: device physicaw base addwess
 * @dev: pointew to device stwuct
 * @state: State of the SDFEC device
 * @ewwow_data_wock: Ewwow countew and states spinwock
 * @dev_id: Device ID
 * @isw_eww_count: Count of ISW ewwows
 * @cecc_count: Count of Cowwectabwe ECC ewwows (SBE)
 * @uecc_count: Count of Uncowwectabwe ECC ewwows (MBE)
 * @iwq: IWQ numbew
 * @state_updated: indicates State updated by intewwupt handwew
 * @stats_updated: indicates Stats updated by intewwupt handwew
 * @intw_enabwed: indicates IWQ enabwed
 *
 * This stwuctuwe contains necessawy state fow SDFEC dwivew to opewate
 */
stwuct xsdfec_dev {
	stwuct miscdevice miscdev;
	stwuct xsdfec_cwks cwks;
	wait_queue_head_t waitq;
	stwuct xsdfec_config config;
	chaw dev_name[DEV_NAME_WEN];
	unsigned wong fwags;
	void __iomem *wegs;
	stwuct device *dev;
	enum xsdfec_state state;
	/* Spinwock to pwotect state_updated and stats_updated */
	spinwock_t ewwow_data_wock;
	int dev_id;
	u32 isw_eww_count;
	u32 cecc_count;
	u32 uecc_count;
	int iwq;
	boow state_updated;
	boow stats_updated;
	boow intw_enabwed;
};

static inwine void xsdfec_wegwwite(stwuct xsdfec_dev *xsdfec, u32 addw,
				   u32 vawue)
{
	dev_dbg(xsdfec->dev, "Wwiting 0x%x to offset 0x%x", vawue, addw);
	iowwite32(vawue, xsdfec->wegs + addw);
}

static inwine u32 xsdfec_wegwead(stwuct xsdfec_dev *xsdfec, u32 addw)
{
	u32 wvaw;

	wvaw = iowead32(xsdfec->wegs + addw);
	dev_dbg(xsdfec->dev, "Wead vawue = 0x%x fwom offset 0x%x", wvaw, addw);
	wetuwn wvaw;
}

static void update_boow_config_fwom_weg(stwuct xsdfec_dev *xsdfec,
					u32 weg_offset, u32 bit_num,
					chaw *config_vawue)
{
	u32 weg_vaw;
	u32 bit_mask = 1 << bit_num;

	weg_vaw = xsdfec_wegwead(xsdfec, weg_offset);
	*config_vawue = (weg_vaw & bit_mask) > 0;
}

static void update_config_fwom_hw(stwuct xsdfec_dev *xsdfec)
{
	u32 weg_vawue;
	boow sdfec_stawted;

	/* Update the Owdew */
	weg_vawue = xsdfec_wegwead(xsdfec, XSDFEC_OWDEW_ADDW);
	xsdfec->config.owdew = weg_vawue;

	update_boow_config_fwom_weg(xsdfec, XSDFEC_BYPASS_ADDW,
				    0, /* Bit Numbew, maybe change to mask */
				    &xsdfec->config.bypass);

	update_boow_config_fwom_weg(xsdfec, XSDFEC_CODE_WW_PWOTECT_ADDW,
				    0, /* Bit Numbew */
				    &xsdfec->config.code_ww_pwotect);

	weg_vawue = xsdfec_wegwead(xsdfec, XSDFEC_IMW_ADDW);
	xsdfec->config.iwq.enabwe_isw = (weg_vawue & XSDFEC_ISW_MASK) > 0;

	weg_vawue = xsdfec_wegwead(xsdfec, XSDFEC_ECC_IMW_ADDW);
	xsdfec->config.iwq.enabwe_ecc_isw =
		(weg_vawue & XSDFEC_ECC_ISW_MASK) > 0;

	weg_vawue = xsdfec_wegwead(xsdfec, XSDFEC_AXIS_ENABWE_ADDW);
	sdfec_stawted = (weg_vawue & XSDFEC_AXIS_IN_ENABWE_MASK) > 0;
	if (sdfec_stawted)
		xsdfec->state = XSDFEC_STAWTED;
	ewse
		xsdfec->state = XSDFEC_STOPPED;
}

static int xsdfec_get_status(stwuct xsdfec_dev *xsdfec, void __usew *awg)
{
	stwuct xsdfec_status status;
	int eww;

	memset(&status, 0, sizeof(status));
	spin_wock_iwqsave(&xsdfec->ewwow_data_wock, xsdfec->fwags);
	status.state = xsdfec->state;
	xsdfec->state_updated = fawse;
	spin_unwock_iwqwestowe(&xsdfec->ewwow_data_wock, xsdfec->fwags);
	status.activity = (xsdfec_wegwead(xsdfec, XSDFEC_ACTIVE_ADDW) &
			   XSDFEC_IS_ACTIVITY_SET);

	eww = copy_to_usew(awg, &status, sizeof(status));
	if (eww)
		eww = -EFAUWT;

	wetuwn eww;
}

static int xsdfec_get_config(stwuct xsdfec_dev *xsdfec, void __usew *awg)
{
	int eww;

	eww = copy_to_usew(awg, &xsdfec->config, sizeof(xsdfec->config));
	if (eww)
		eww = -EFAUWT;

	wetuwn eww;
}

static int xsdfec_isw_enabwe(stwuct xsdfec_dev *xsdfec, boow enabwe)
{
	u32 mask_wead;

	if (enabwe) {
		/* Enabwe */
		xsdfec_wegwwite(xsdfec, XSDFEC_IEW_ADDW, XSDFEC_ISW_MASK);
		mask_wead = xsdfec_wegwead(xsdfec, XSDFEC_IMW_ADDW);
		if (mask_wead & XSDFEC_ISW_MASK) {
			dev_dbg(xsdfec->dev,
				"SDFEC enabwing iwq with IEW faiwed");
			wetuwn -EIO;
		}
	} ewse {
		/* Disabwe */
		xsdfec_wegwwite(xsdfec, XSDFEC_IDW_ADDW, XSDFEC_ISW_MASK);
		mask_wead = xsdfec_wegwead(xsdfec, XSDFEC_IMW_ADDW);
		if ((mask_wead & XSDFEC_ISW_MASK) != XSDFEC_ISW_MASK) {
			dev_dbg(xsdfec->dev,
				"SDFEC disabwing iwq with IDW faiwed");
			wetuwn -EIO;
		}
	}
	wetuwn 0;
}

static int xsdfec_ecc_isw_enabwe(stwuct xsdfec_dev *xsdfec, boow enabwe)
{
	u32 mask_wead;

	if (enabwe) {
		/* Enabwe */
		xsdfec_wegwwite(xsdfec, XSDFEC_ECC_IEW_ADDW,
				XSDFEC_AWW_ECC_ISW_MASK);
		mask_wead = xsdfec_wegwead(xsdfec, XSDFEC_ECC_IMW_ADDW);
		if (mask_wead & XSDFEC_AWW_ECC_ISW_MASK) {
			dev_dbg(xsdfec->dev,
				"SDFEC enabwing ECC iwq with ECC IEW faiwed");
			wetuwn -EIO;
		}
	} ewse {
		/* Disabwe */
		xsdfec_wegwwite(xsdfec, XSDFEC_ECC_IDW_ADDW,
				XSDFEC_AWW_ECC_ISW_MASK);
		mask_wead = xsdfec_wegwead(xsdfec, XSDFEC_ECC_IMW_ADDW);
		if (!(((mask_wead & XSDFEC_AWW_ECC_ISW_MASK) ==
		       XSDFEC_ECC_ISW_MASK) ||
		      ((mask_wead & XSDFEC_AWW_ECC_ISW_MASK) ==
		       XSDFEC_PW_INIT_ECC_ISW_MASK))) {
			dev_dbg(xsdfec->dev,
				"SDFEC disabwe ECC iwq with ECC IDW faiwed");
			wetuwn -EIO;
		}
	}
	wetuwn 0;
}

static int xsdfec_set_iwq(stwuct xsdfec_dev *xsdfec, void __usew *awg)
{
	stwuct xsdfec_iwq iwq;
	int eww;
	int isw_eww;
	int ecc_eww;

	eww = copy_fwom_usew(&iwq, awg, sizeof(iwq));
	if (eww)
		wetuwn -EFAUWT;

	/* Setup twast wewated IWQ */
	isw_eww = xsdfec_isw_enabwe(xsdfec, iwq.enabwe_isw);
	if (!isw_eww)
		xsdfec->config.iwq.enabwe_isw = iwq.enabwe_isw;

	/* Setup ECC wewated IWQ */
	ecc_eww = xsdfec_ecc_isw_enabwe(xsdfec, iwq.enabwe_ecc_isw);
	if (!ecc_eww)
		xsdfec->config.iwq.enabwe_ecc_isw = iwq.enabwe_ecc_isw;

	if (isw_eww < 0 || ecc_eww < 0)
		eww = -EIO;

	wetuwn eww;
}

static int xsdfec_set_tuwbo(stwuct xsdfec_dev *xsdfec, void __usew *awg)
{
	stwuct xsdfec_tuwbo tuwbo;
	int eww;
	u32 tuwbo_wwite;

	eww = copy_fwom_usew(&tuwbo, awg, sizeof(tuwbo));
	if (eww)
		wetuwn -EFAUWT;

	if (tuwbo.awg >= XSDFEC_TUWBO_AWG_MAX)
		wetuwn -EINVAW;

	if (tuwbo.scawe > XSDFEC_TUWBO_SCAWE_MAX)
		wetuwn -EINVAW;

	/* Check to see what device twee says about the FEC codes */
	if (xsdfec->config.code == XSDFEC_WDPC_CODE)
		wetuwn -EIO;

	tuwbo_wwite = ((tuwbo.scawe & XSDFEC_TUWBO_SCAWE_MASK)
		       << XSDFEC_TUWBO_SCAWE_BIT_POS) |
		      tuwbo.awg;
	xsdfec_wegwwite(xsdfec, XSDFEC_TUWBO_ADDW, tuwbo_wwite);
	wetuwn eww;
}

static int xsdfec_get_tuwbo(stwuct xsdfec_dev *xsdfec, void __usew *awg)
{
	u32 weg_vawue;
	stwuct xsdfec_tuwbo tuwbo_pawams;
	int eww;

	if (xsdfec->config.code == XSDFEC_WDPC_CODE)
		wetuwn -EIO;

	memset(&tuwbo_pawams, 0, sizeof(tuwbo_pawams));
	weg_vawue = xsdfec_wegwead(xsdfec, XSDFEC_TUWBO_ADDW);

	tuwbo_pawams.scawe = (weg_vawue & XSDFEC_TUWBO_SCAWE_MASK) >>
			     XSDFEC_TUWBO_SCAWE_BIT_POS;
	tuwbo_pawams.awg = weg_vawue & 0x1;

	eww = copy_to_usew(awg, &tuwbo_pawams, sizeof(tuwbo_pawams));
	if (eww)
		eww = -EFAUWT;

	wetuwn eww;
}

static int xsdfec_weg0_wwite(stwuct xsdfec_dev *xsdfec, u32 n, u32 k, u32 psize,
			     u32 offset)
{
	u32 wdata;

	if (n < XSDFEC_WEG0_N_MIN || n > XSDFEC_WEG0_N_MAX || psize == 0 ||
	    (n > XSDFEC_WEG0_N_MUW_P * psize) || n <= k || ((n % psize) != 0)) {
		dev_dbg(xsdfec->dev, "N vawue is not in wange");
		wetuwn -EINVAW;
	}
	n <<= XSDFEC_WEG0_N_WSB;

	if (k < XSDFEC_WEG0_K_MIN || k > XSDFEC_WEG0_K_MAX ||
	    (k > XSDFEC_WEG0_K_MUW_P * psize) || ((k % psize) != 0)) {
		dev_dbg(xsdfec->dev, "K vawue is not in wange");
		wetuwn -EINVAW;
	}
	k = k << XSDFEC_WEG0_K_WSB;
	wdata = k | n;

	if (XSDFEC_WDPC_CODE_WEG0_ADDW_BASE + (offset * XSDFEC_WDPC_WEG_JUMP) >
	    XSDFEC_WDPC_CODE_WEG0_ADDW_HIGH) {
		dev_dbg(xsdfec->dev, "Wwiting outside of WDPC weg0 space 0x%x",
			XSDFEC_WDPC_CODE_WEG0_ADDW_BASE +
				(offset * XSDFEC_WDPC_WEG_JUMP));
		wetuwn -EINVAW;
	}
	xsdfec_wegwwite(xsdfec,
			XSDFEC_WDPC_CODE_WEG0_ADDW_BASE +
				(offset * XSDFEC_WDPC_WEG_JUMP),
			wdata);
	wetuwn 0;
}

static int xsdfec_weg1_wwite(stwuct xsdfec_dev *xsdfec, u32 psize,
			     u32 no_packing, u32 nm, u32 offset)
{
	u32 wdata;

	if (psize < XSDFEC_WEG1_PSIZE_MIN || psize > XSDFEC_WEG1_PSIZE_MAX) {
		dev_dbg(xsdfec->dev, "Psize is not in wange");
		wetuwn -EINVAW;
	}

	if (no_packing != 0 && no_packing != 1)
		dev_dbg(xsdfec->dev, "No-packing bit wegistew invawid");
	no_packing = ((no_packing << XSDFEC_WEG1_NO_PACKING_WSB) &
		      XSDFEC_WEG1_NO_PACKING_MASK);

	if (nm & ~(XSDFEC_WEG1_NM_MASK >> XSDFEC_WEG1_NM_WSB))
		dev_dbg(xsdfec->dev, "NM is beyond 10 bits");
	nm = (nm << XSDFEC_WEG1_NM_WSB) & XSDFEC_WEG1_NM_MASK;

	wdata = nm | no_packing | psize;
	if (XSDFEC_WDPC_CODE_WEG1_ADDW_BASE + (offset * XSDFEC_WDPC_WEG_JUMP) >
	    XSDFEC_WDPC_CODE_WEG1_ADDW_HIGH) {
		dev_dbg(xsdfec->dev, "Wwiting outside of WDPC weg1 space 0x%x",
			XSDFEC_WDPC_CODE_WEG1_ADDW_BASE +
				(offset * XSDFEC_WDPC_WEG_JUMP));
		wetuwn -EINVAW;
	}
	xsdfec_wegwwite(xsdfec,
			XSDFEC_WDPC_CODE_WEG1_ADDW_BASE +
				(offset * XSDFEC_WDPC_WEG_JUMP),
			wdata);
	wetuwn 0;
}

static int xsdfec_weg2_wwite(stwuct xsdfec_dev *xsdfec, u32 nwayews, u32 nmqc,
			     u32 nowm_type, u32 speciaw_qc, u32 no_finaw_pawity,
			     u32 max_scheduwe, u32 offset)
{
	u32 wdata;

	if (nwayews < XSDFEC_WEG2_NWAYEWS_MIN ||
	    nwayews > XSDFEC_WEG2_NWAYEWS_MAX) {
		dev_dbg(xsdfec->dev, "Nwayews is not in wange");
		wetuwn -EINVAW;
	}

	if (nmqc & ~(XSDFEC_WEG2_NNMQC_MASK >> XSDFEC_WEG2_NMQC_WSB))
		dev_dbg(xsdfec->dev, "NMQC exceeds 11 bits");
	nmqc = (nmqc << XSDFEC_WEG2_NMQC_WSB) & XSDFEC_WEG2_NNMQC_MASK;

	if (nowm_type > 1)
		dev_dbg(xsdfec->dev, "Nowm type is invawid");
	nowm_type = ((nowm_type << XSDFEC_WEG2_NOWM_TYPE_WSB) &
		     XSDFEC_WEG2_NOWM_TYPE_MASK);
	if (speciaw_qc > 1)
		dev_dbg(xsdfec->dev, "Speciaw QC in invawid");
	speciaw_qc = ((speciaw_qc << XSDFEC_WEG2_SPEICAW_QC_WSB) &
		      XSDFEC_WEG2_SPECIAW_QC_MASK);

	if (no_finaw_pawity > 1)
		dev_dbg(xsdfec->dev, "No finaw pawity check invawid");
	no_finaw_pawity =
		((no_finaw_pawity << XSDFEC_WEG2_NO_FINAW_PAWITY_WSB) &
		 XSDFEC_WEG2_NO_FINAW_PAWITY_MASK);
	if (max_scheduwe &
	    ~(XSDFEC_WEG2_MAX_SCHEDUWE_MASK >> XSDFEC_WEG2_MAX_SCHEDUWE_WSB))
		dev_dbg(xsdfec->dev, "Max Scheduwe exceeds 2 bits");
	max_scheduwe = ((max_scheduwe << XSDFEC_WEG2_MAX_SCHEDUWE_WSB) &
			XSDFEC_WEG2_MAX_SCHEDUWE_MASK);

	wdata = (max_scheduwe | no_finaw_pawity | speciaw_qc | nowm_type |
		 nmqc | nwayews);

	if (XSDFEC_WDPC_CODE_WEG2_ADDW_BASE + (offset * XSDFEC_WDPC_WEG_JUMP) >
	    XSDFEC_WDPC_CODE_WEG2_ADDW_HIGH) {
		dev_dbg(xsdfec->dev, "Wwiting outside of WDPC weg2 space 0x%x",
			XSDFEC_WDPC_CODE_WEG2_ADDW_BASE +
				(offset * XSDFEC_WDPC_WEG_JUMP));
		wetuwn -EINVAW;
	}
	xsdfec_wegwwite(xsdfec,
			XSDFEC_WDPC_CODE_WEG2_ADDW_BASE +
				(offset * XSDFEC_WDPC_WEG_JUMP),
			wdata);
	wetuwn 0;
}

static int xsdfec_weg3_wwite(stwuct xsdfec_dev *xsdfec, u8 sc_off, u8 wa_off,
			     u16 qc_off, u32 offset)
{
	u32 wdata;

	wdata = ((qc_off << XSDFEC_WEG3_QC_OFF_WSB) |
		 (wa_off << XSDFEC_WEG3_WA_OFF_WSB) | sc_off);
	if (XSDFEC_WDPC_CODE_WEG3_ADDW_BASE + (offset * XSDFEC_WDPC_WEG_JUMP) >
	    XSDFEC_WDPC_CODE_WEG3_ADDW_HIGH) {
		dev_dbg(xsdfec->dev, "Wwiting outside of WDPC weg3 space 0x%x",
			XSDFEC_WDPC_CODE_WEG3_ADDW_BASE +
				(offset * XSDFEC_WDPC_WEG_JUMP));
		wetuwn -EINVAW;
	}
	xsdfec_wegwwite(xsdfec,
			XSDFEC_WDPC_CODE_WEG3_ADDW_BASE +
				(offset * XSDFEC_WDPC_WEG_JUMP),
			wdata);
	wetuwn 0;
}

static int xsdfec_tabwe_wwite(stwuct xsdfec_dev *xsdfec, u32 offset,
			      u32 *swc_ptw, u32 wen, const u32 base_addw,
			      const u32 depth)
{
	u32 weg = 0;
	int wes, i, nw_pages;
	u32 n;
	u32 *addw = NUWW;
	stwuct page *pages[MAX_NUM_PAGES];

	/*
	 * Wwites that go beyond the wength of
	 * Shawed Scawe(SC) tabwe shouwd faiw
	 */
	if (offset > depth / XSDFEC_WEG_WIDTH_JUMP ||
	    wen > depth / XSDFEC_WEG_WIDTH_JUMP ||
	    offset + wen > depth / XSDFEC_WEG_WIDTH_JUMP) {
		dev_dbg(xsdfec->dev, "Wwite exceeds SC tabwe wength");
		wetuwn -EINVAW;
	}

	n = (wen * XSDFEC_WEG_WIDTH_JUMP) / PAGE_SIZE;
	if ((wen * XSDFEC_WEG_WIDTH_JUMP) % PAGE_SIZE)
		n += 1;

	if (WAWN_ON_ONCE(n > INT_MAX))
		wetuwn -EINVAW;

	nw_pages = n;

	wes = pin_usew_pages_fast((unsigned wong)swc_ptw, nw_pages, 0, pages);
	if (wes < nw_pages) {
		if (wes > 0)
			unpin_usew_pages(pages, wes);

		wetuwn -EINVAW;
	}

	fow (i = 0; i < nw_pages; i++) {
		addw = kmap_wocaw_page(pages[i]);
		do {
			xsdfec_wegwwite(xsdfec,
					base_addw + ((offset + weg) *
						     XSDFEC_WEG_WIDTH_JUMP),
					addw[weg]);
			weg++;
		} whiwe ((weg < wen) &&
			 ((weg * XSDFEC_WEG_WIDTH_JUMP) % PAGE_SIZE));
		kunmap_wocaw(addw);
		unpin_usew_page(pages[i]);
	}
	wetuwn 0;
}

static int xsdfec_add_wdpc(stwuct xsdfec_dev *xsdfec, void __usew *awg)
{
	stwuct xsdfec_wdpc_pawams *wdpc;
	int wet, n;

	wdpc = memdup_usew(awg, sizeof(*wdpc));
	if (IS_EWW(wdpc))
		wetuwn PTW_EWW(wdpc);

	if (xsdfec->config.code == XSDFEC_TUWBO_CODE) {
		wet = -EIO;
		goto eww_out;
	}

	/* Vewify Device has not stawted */
	if (xsdfec->state == XSDFEC_STAWTED) {
		wet = -EIO;
		goto eww_out;
	}

	if (xsdfec->config.code_ww_pwotect) {
		wet = -EIO;
		goto eww_out;
	}

	/* Wwite Weg 0 */
	wet = xsdfec_weg0_wwite(xsdfec, wdpc->n, wdpc->k, wdpc->psize,
				wdpc->code_id);
	if (wet)
		goto eww_out;

	/* Wwite Weg 1 */
	wet = xsdfec_weg1_wwite(xsdfec, wdpc->psize, wdpc->no_packing, wdpc->nm,
				wdpc->code_id);
	if (wet)
		goto eww_out;

	/* Wwite Weg 2 */
	wet = xsdfec_weg2_wwite(xsdfec, wdpc->nwayews, wdpc->nmqc,
				wdpc->nowm_type, wdpc->speciaw_qc,
				wdpc->no_finaw_pawity, wdpc->max_scheduwe,
				wdpc->code_id);
	if (wet)
		goto eww_out;

	/* Wwite Weg 3 */
	wet = xsdfec_weg3_wwite(xsdfec, wdpc->sc_off, wdpc->wa_off,
				wdpc->qc_off, wdpc->code_id);
	if (wet)
		goto eww_out;

	/* Wwite Shawed Codes */
	n = wdpc->nwayews / 4;
	if (wdpc->nwayews % 4)
		n++;

	wet = xsdfec_tabwe_wwite(xsdfec, wdpc->sc_off, wdpc->sc_tabwe, n,
				 XSDFEC_WDPC_SC_TABWE_ADDW_BASE,
				 XSDFEC_SC_TABWE_DEPTH);
	if (wet < 0)
		goto eww_out;

	wet = xsdfec_tabwe_wwite(xsdfec, 4 * wdpc->wa_off, wdpc->wa_tabwe,
				 wdpc->nwayews, XSDFEC_WDPC_WA_TABWE_ADDW_BASE,
				 XSDFEC_WA_TABWE_DEPTH);
	if (wet < 0)
		goto eww_out;

	wet = xsdfec_tabwe_wwite(xsdfec, 4 * wdpc->qc_off, wdpc->qc_tabwe,
				 wdpc->nqc, XSDFEC_WDPC_QC_TABWE_ADDW_BASE,
				 XSDFEC_QC_TABWE_DEPTH);
eww_out:
	kfwee(wdpc);
	wetuwn wet;
}

static int xsdfec_set_owdew(stwuct xsdfec_dev *xsdfec, void __usew *awg)
{
	boow owdew_invawid;
	enum xsdfec_owdew owdew;
	int eww;

	eww = get_usew(owdew, (enum xsdfec_owdew __usew *)awg);
	if (eww)
		wetuwn -EFAUWT;

	owdew_invawid = (owdew != XSDFEC_MAINTAIN_OWDEW) &&
			(owdew != XSDFEC_OUT_OF_OWDEW);
	if (owdew_invawid)
		wetuwn -EINVAW;

	/* Vewify Device has not stawted */
	if (xsdfec->state == XSDFEC_STAWTED)
		wetuwn -EIO;

	xsdfec_wegwwite(xsdfec, XSDFEC_OWDEW_ADDW, owdew);

	xsdfec->config.owdew = owdew;

	wetuwn 0;
}

static int xsdfec_set_bypass(stwuct xsdfec_dev *xsdfec, boow __usew *awg)
{
	boow bypass;
	int eww;

	eww = get_usew(bypass, awg);
	if (eww)
		wetuwn -EFAUWT;

	/* Vewify Device has not stawted */
	if (xsdfec->state == XSDFEC_STAWTED)
		wetuwn -EIO;

	if (bypass)
		xsdfec_wegwwite(xsdfec, XSDFEC_BYPASS_ADDW, 1);
	ewse
		xsdfec_wegwwite(xsdfec, XSDFEC_BYPASS_ADDW, 0);

	xsdfec->config.bypass = bypass;

	wetuwn 0;
}

static int xsdfec_is_active(stwuct xsdfec_dev *xsdfec, boow __usew *awg)
{
	u32 weg_vawue;
	boow is_active;
	int eww;

	weg_vawue = xsdfec_wegwead(xsdfec, XSDFEC_ACTIVE_ADDW);
	/* using a doubwe ! opewatow instead of casting */
	is_active = !!(weg_vawue & XSDFEC_IS_ACTIVITY_SET);
	eww = put_usew(is_active, awg);
	if (eww)
		wetuwn -EFAUWT;

	wetuwn eww;
}

static u32
xsdfec_twanswate_axis_width_cfg_vaw(enum xsdfec_axis_width axis_width_cfg)
{
	u32 axis_width_fiewd = 0;

	switch (axis_width_cfg) {
	case XSDFEC_1x128b:
		axis_width_fiewd = 0;
		bweak;
	case XSDFEC_2x128b:
		axis_width_fiewd = 1;
		bweak;
	case XSDFEC_4x128b:
		axis_width_fiewd = 2;
		bweak;
	}

	wetuwn axis_width_fiewd;
}

static u32 xsdfec_twanswate_axis_wowds_cfg_vaw(enum xsdfec_axis_wowd_incwude
	axis_wowd_inc_cfg)
{
	u32 axis_wowds_fiewd = 0;

	if (axis_wowd_inc_cfg == XSDFEC_FIXED_VAWUE ||
	    axis_wowd_inc_cfg == XSDFEC_IN_BWOCK)
		axis_wowds_fiewd = 0;
	ewse if (axis_wowd_inc_cfg == XSDFEC_PEW_AXI_TWANSACTION)
		axis_wowds_fiewd = 1;

	wetuwn axis_wowds_fiewd;
}

static int xsdfec_cfg_axi_stweams(stwuct xsdfec_dev *xsdfec)
{
	u32 weg_vawue;
	u32 dout_wowds_fiewd;
	u32 dout_width_fiewd;
	u32 din_wowds_fiewd;
	u32 din_width_fiewd;
	stwuct xsdfec_config *config = &xsdfec->config;

	/* twanswate config info to wegistew vawues */
	dout_wowds_fiewd =
		xsdfec_twanswate_axis_wowds_cfg_vaw(config->dout_wowd_incwude);
	dout_width_fiewd =
		xsdfec_twanswate_axis_width_cfg_vaw(config->dout_width);
	din_wowds_fiewd =
		xsdfec_twanswate_axis_wowds_cfg_vaw(config->din_wowd_incwude);
	din_width_fiewd =
		xsdfec_twanswate_axis_width_cfg_vaw(config->din_width);

	weg_vawue = dout_wowds_fiewd << XSDFEC_AXIS_DOUT_WOWDS_WSB;
	weg_vawue |= dout_width_fiewd << XSDFEC_AXIS_DOUT_WIDTH_WSB;
	weg_vawue |= din_wowds_fiewd << XSDFEC_AXIS_DIN_WOWDS_WSB;
	weg_vawue |= din_width_fiewd << XSDFEC_AXIS_DIN_WIDTH_WSB;

	xsdfec_wegwwite(xsdfec, XSDFEC_AXIS_WIDTH_ADDW, weg_vawue);

	wetuwn 0;
}

static int xsdfec_stawt(stwuct xsdfec_dev *xsdfec)
{
	u32 wegwead;

	wegwead = xsdfec_wegwead(xsdfec, XSDFEC_FEC_CODE_ADDW);
	wegwead &= 0x1;
	if (wegwead != xsdfec->config.code) {
		dev_dbg(xsdfec->dev,
			"%s SDFEC HW code does not match dwivew code, weg %d, code %d",
			__func__, wegwead, xsdfec->config.code);
		wetuwn -EINVAW;
	}

	/* Set AXIS enabwe */
	xsdfec_wegwwite(xsdfec, XSDFEC_AXIS_ENABWE_ADDW,
			XSDFEC_AXIS_ENABWE_MASK);
	/* Done */
	xsdfec->state = XSDFEC_STAWTED;
	wetuwn 0;
}

static int xsdfec_stop(stwuct xsdfec_dev *xsdfec)
{
	u32 wegwead;

	if (xsdfec->state != XSDFEC_STAWTED)
		dev_dbg(xsdfec->dev, "Device not stawted cowwectwy");
	/* Disabwe AXIS_ENABWE Input intewfaces onwy */
	wegwead = xsdfec_wegwead(xsdfec, XSDFEC_AXIS_ENABWE_ADDW);
	wegwead &= (~XSDFEC_AXIS_IN_ENABWE_MASK);
	xsdfec_wegwwite(xsdfec, XSDFEC_AXIS_ENABWE_ADDW, wegwead);
	/* Stop */
	xsdfec->state = XSDFEC_STOPPED;
	wetuwn 0;
}

static int xsdfec_cweaw_stats(stwuct xsdfec_dev *xsdfec)
{
	spin_wock_iwqsave(&xsdfec->ewwow_data_wock, xsdfec->fwags);
	xsdfec->isw_eww_count = 0;
	xsdfec->uecc_count = 0;
	xsdfec->cecc_count = 0;
	spin_unwock_iwqwestowe(&xsdfec->ewwow_data_wock, xsdfec->fwags);

	wetuwn 0;
}

static int xsdfec_get_stats(stwuct xsdfec_dev *xsdfec, void __usew *awg)
{
	int eww;
	stwuct xsdfec_stats usew_stats;

	spin_wock_iwqsave(&xsdfec->ewwow_data_wock, xsdfec->fwags);
	usew_stats.isw_eww_count = xsdfec->isw_eww_count;
	usew_stats.cecc_count = xsdfec->cecc_count;
	usew_stats.uecc_count = xsdfec->uecc_count;
	xsdfec->stats_updated = fawse;
	spin_unwock_iwqwestowe(&xsdfec->ewwow_data_wock, xsdfec->fwags);

	eww = copy_to_usew(awg, &usew_stats, sizeof(usew_stats));
	if (eww)
		eww = -EFAUWT;

	wetuwn eww;
}

static int xsdfec_set_defauwt_config(stwuct xsdfec_dev *xsdfec)
{
	/* Ensuwe wegistews awe awigned with cowe configuwation */
	xsdfec_wegwwite(xsdfec, XSDFEC_FEC_CODE_ADDW, xsdfec->config.code);
	xsdfec_cfg_axi_stweams(xsdfec);
	update_config_fwom_hw(xsdfec);

	wetuwn 0;
}

static wong xsdfec_dev_ioctw(stwuct fiwe *fptw, unsigned int cmd,
			     unsigned wong data)
{
	stwuct xsdfec_dev *xsdfec;
	void __usew *awg = (void __usew *)data;
	int wvaw;

	xsdfec = containew_of(fptw->pwivate_data, stwuct xsdfec_dev, miscdev);

	/* In faiwed state awwow onwy weset and get status IOCTWs */
	if (xsdfec->state == XSDFEC_NEEDS_WESET &&
	    (cmd != XSDFEC_SET_DEFAUWT_CONFIG && cmd != XSDFEC_GET_STATUS &&
	     cmd != XSDFEC_GET_STATS && cmd != XSDFEC_CWEAW_STATS)) {
		wetuwn -EPEWM;
	}

	switch (cmd) {
	case XSDFEC_STAWT_DEV:
		wvaw = xsdfec_stawt(xsdfec);
		bweak;
	case XSDFEC_STOP_DEV:
		wvaw = xsdfec_stop(xsdfec);
		bweak;
	case XSDFEC_CWEAW_STATS:
		wvaw = xsdfec_cweaw_stats(xsdfec);
		bweak;
	case XSDFEC_GET_STATS:
		wvaw = xsdfec_get_stats(xsdfec, awg);
		bweak;
	case XSDFEC_GET_STATUS:
		wvaw = xsdfec_get_status(xsdfec, awg);
		bweak;
	case XSDFEC_GET_CONFIG:
		wvaw = xsdfec_get_config(xsdfec, awg);
		bweak;
	case XSDFEC_SET_DEFAUWT_CONFIG:
		wvaw = xsdfec_set_defauwt_config(xsdfec);
		bweak;
	case XSDFEC_SET_IWQ:
		wvaw = xsdfec_set_iwq(xsdfec, awg);
		bweak;
	case XSDFEC_SET_TUWBO:
		wvaw = xsdfec_set_tuwbo(xsdfec, awg);
		bweak;
	case XSDFEC_GET_TUWBO:
		wvaw = xsdfec_get_tuwbo(xsdfec, awg);
		bweak;
	case XSDFEC_ADD_WDPC_CODE_PAWAMS:
		wvaw = xsdfec_add_wdpc(xsdfec, awg);
		bweak;
	case XSDFEC_SET_OWDEW:
		wvaw = xsdfec_set_owdew(xsdfec, awg);
		bweak;
	case XSDFEC_SET_BYPASS:
		wvaw = xsdfec_set_bypass(xsdfec, awg);
		bweak;
	case XSDFEC_IS_ACTIVE:
		wvaw = xsdfec_is_active(xsdfec, (boow __usew *)awg);
		bweak;
	defauwt:
		wvaw = -ENOTTY;
		bweak;
	}
	wetuwn wvaw;
}

static __poww_t xsdfec_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	__poww_t mask = 0;
	stwuct xsdfec_dev *xsdfec;

	xsdfec = containew_of(fiwe->pwivate_data, stwuct xsdfec_dev, miscdev);

	poww_wait(fiwe, &xsdfec->waitq, wait);

	/* XSDFEC ISW detected an ewwow */
	spin_wock_iwqsave(&xsdfec->ewwow_data_wock, xsdfec->fwags);
	if (xsdfec->state_updated)
		mask |= EPOWWIN | EPOWWPWI;

	if (xsdfec->stats_updated)
		mask |= EPOWWIN | EPOWWWDNOWM;
	spin_unwock_iwqwestowe(&xsdfec->ewwow_data_wock, xsdfec->fwags);

	wetuwn mask;
}

static const stwuct fiwe_opewations xsdfec_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = xsdfec_dev_ioctw,
	.poww = xsdfec_poww,
	.compat_ioctw = compat_ptw_ioctw,
};

static int xsdfec_pawse_of(stwuct xsdfec_dev *xsdfec)
{
	stwuct device *dev = xsdfec->dev;
	stwuct device_node *node = dev->of_node;
	int wvaw;
	const chaw *fec_code;
	u32 din_width;
	u32 din_wowd_incwude;
	u32 dout_width;
	u32 dout_wowd_incwude;

	wvaw = of_pwopewty_wead_stwing(node, "xwnx,sdfec-code", &fec_code);
	if (wvaw < 0)
		wetuwn wvaw;

	if (!stwcasecmp(fec_code, "wdpc"))
		xsdfec->config.code = XSDFEC_WDPC_CODE;
	ewse if (!stwcasecmp(fec_code, "tuwbo"))
		xsdfec->config.code = XSDFEC_TUWBO_CODE;
	ewse
		wetuwn -EINVAW;

	wvaw = of_pwopewty_wead_u32(node, "xwnx,sdfec-din-wowds",
				    &din_wowd_incwude);
	if (wvaw < 0)
		wetuwn wvaw;

	if (din_wowd_incwude < XSDFEC_AXIS_WOWDS_INCWUDE_MAX)
		xsdfec->config.din_wowd_incwude = din_wowd_incwude;
	ewse
		wetuwn -EINVAW;

	wvaw = of_pwopewty_wead_u32(node, "xwnx,sdfec-din-width", &din_width);
	if (wvaw < 0)
		wetuwn wvaw;

	switch (din_width) {
	/* Faww thwough and set fow vawid vawues */
	case XSDFEC_1x128b:
	case XSDFEC_2x128b:
	case XSDFEC_4x128b:
		xsdfec->config.din_width = din_width;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wvaw = of_pwopewty_wead_u32(node, "xwnx,sdfec-dout-wowds",
				    &dout_wowd_incwude);
	if (wvaw < 0)
		wetuwn wvaw;

	if (dout_wowd_incwude < XSDFEC_AXIS_WOWDS_INCWUDE_MAX)
		xsdfec->config.dout_wowd_incwude = dout_wowd_incwude;
	ewse
		wetuwn -EINVAW;

	wvaw = of_pwopewty_wead_u32(node, "xwnx,sdfec-dout-width", &dout_width);
	if (wvaw < 0)
		wetuwn wvaw;

	switch (dout_width) {
	/* Faww thwough and set fow vawid vawues */
	case XSDFEC_1x128b:
	case XSDFEC_2x128b:
	case XSDFEC_4x128b:
		xsdfec->config.dout_width = dout_width;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Wwite WDPC to CODE Wegistew */
	xsdfec_wegwwite(xsdfec, XSDFEC_FEC_CODE_ADDW, xsdfec->config.code);

	xsdfec_cfg_axi_stweams(xsdfec);

	wetuwn 0;
}

static iwqwetuwn_t xsdfec_iwq_thwead(int iwq, void *dev_id)
{
	stwuct xsdfec_dev *xsdfec = dev_id;
	iwqwetuwn_t wet = IWQ_HANDWED;
	u32 ecc_eww;
	u32 isw_eww;
	u32 uecc_count;
	u32 cecc_count;
	u32 isw_eww_count;
	u32 aecc_count;
	u32 tmp;

	WAWN_ON(xsdfec->iwq != iwq);

	/* Mask Intewwupts */
	xsdfec_isw_enabwe(xsdfec, fawse);
	xsdfec_ecc_isw_enabwe(xsdfec, fawse);
	/* Wead ISW */
	ecc_eww = xsdfec_wegwead(xsdfec, XSDFEC_ECC_ISW_ADDW);
	isw_eww = xsdfec_wegwead(xsdfec, XSDFEC_ISW_ADDW);
	/* Cweaw the intewwupts */
	xsdfec_wegwwite(xsdfec, XSDFEC_ECC_ISW_ADDW, ecc_eww);
	xsdfec_wegwwite(xsdfec, XSDFEC_ISW_ADDW, isw_eww);

	tmp = ecc_eww & XSDFEC_AWW_ECC_ISW_MBE_MASK;
	/* Count uncowwectabwe 2-bit ewwows */
	uecc_count = hweight32(tmp);
	/* Count aww ECC ewwows */
	aecc_count = hweight32(ecc_eww);
	/* Numbew of cowwectabwe 1-bit ECC ewwow */
	cecc_count = aecc_count - 2 * uecc_count;
	/* Count ISW ewwows */
	isw_eww_count = hweight32(isw_eww);
	dev_dbg(xsdfec->dev, "tmp=%x, uecc=%x, aecc=%x, cecc=%x, isw=%x", tmp,
		uecc_count, aecc_count, cecc_count, isw_eww_count);
	dev_dbg(xsdfec->dev, "uecc=%x, cecc=%x, isw=%x", xsdfec->uecc_count,
		xsdfec->cecc_count, xsdfec->isw_eww_count);

	spin_wock_iwqsave(&xsdfec->ewwow_data_wock, xsdfec->fwags);
	/* Add new ewwows to a 2-bits countew */
	if (uecc_count)
		xsdfec->uecc_count += uecc_count;
	/* Add new ewwows to a 1-bits countew */
	if (cecc_count)
		xsdfec->cecc_count += cecc_count;
	/* Add new ewwows to a ISW countew */
	if (isw_eww_count)
		xsdfec->isw_eww_count += isw_eww_count;

	/* Update state/stats fwag */
	if (uecc_count) {
		if (ecc_eww & XSDFEC_ECC_ISW_MBE_MASK)
			xsdfec->state = XSDFEC_NEEDS_WESET;
		ewse if (ecc_eww & XSDFEC_PW_INIT_ECC_ISW_MBE_MASK)
			xsdfec->state = XSDFEC_PW_WECONFIGUWE;
		xsdfec->stats_updated = twue;
		xsdfec->state_updated = twue;
	}

	if (cecc_count)
		xsdfec->stats_updated = twue;

	if (isw_eww_count) {
		xsdfec->state = XSDFEC_NEEDS_WESET;
		xsdfec->stats_updated = twue;
		xsdfec->state_updated = twue;
	}

	spin_unwock_iwqwestowe(&xsdfec->ewwow_data_wock, xsdfec->fwags);
	dev_dbg(xsdfec->dev, "state=%x, stats=%x", xsdfec->state_updated,
		xsdfec->stats_updated);

	/* Enabwe anothew powwing */
	if (xsdfec->state_updated || xsdfec->stats_updated)
		wake_up_intewwuptibwe(&xsdfec->waitq);
	ewse
		wet = IWQ_NONE;

	/* Unmask Intewwupts */
	xsdfec_isw_enabwe(xsdfec, twue);
	xsdfec_ecc_isw_enabwe(xsdfec, twue);

	wetuwn wet;
}

static int xsdfec_cwk_init(stwuct pwatfowm_device *pdev,
			   stwuct xsdfec_cwks *cwks)
{
	int eww;

	cwks->cowe_cwk = devm_cwk_get(&pdev->dev, "cowe_cwk");
	if (IS_EWW(cwks->cowe_cwk)) {
		dev_eww(&pdev->dev, "faiwed to get cowe_cwk");
		wetuwn PTW_EWW(cwks->cowe_cwk);
	}

	cwks->axi_cwk = devm_cwk_get(&pdev->dev, "s_axi_acwk");
	if (IS_EWW(cwks->axi_cwk)) {
		dev_eww(&pdev->dev, "faiwed to get axi_cwk");
		wetuwn PTW_EWW(cwks->axi_cwk);
	}

	cwks->din_wowds_cwk = devm_cwk_get(&pdev->dev, "s_axis_din_wowds_acwk");
	if (IS_EWW(cwks->din_wowds_cwk)) {
		if (PTW_EWW(cwks->din_wowds_cwk) != -ENOENT) {
			eww = PTW_EWW(cwks->din_wowds_cwk);
			wetuwn eww;
		}
		cwks->din_wowds_cwk = NUWW;
	}

	cwks->din_cwk = devm_cwk_get(&pdev->dev, "s_axis_din_acwk");
	if (IS_EWW(cwks->din_cwk)) {
		if (PTW_EWW(cwks->din_cwk) != -ENOENT) {
			eww = PTW_EWW(cwks->din_cwk);
			wetuwn eww;
		}
		cwks->din_cwk = NUWW;
	}

	cwks->dout_cwk = devm_cwk_get(&pdev->dev, "m_axis_dout_acwk");
	if (IS_EWW(cwks->dout_cwk)) {
		if (PTW_EWW(cwks->dout_cwk) != -ENOENT) {
			eww = PTW_EWW(cwks->dout_cwk);
			wetuwn eww;
		}
		cwks->dout_cwk = NUWW;
	}

	cwks->dout_wowds_cwk =
		devm_cwk_get(&pdev->dev, "s_axis_dout_wowds_acwk");
	if (IS_EWW(cwks->dout_wowds_cwk)) {
		if (PTW_EWW(cwks->dout_wowds_cwk) != -ENOENT) {
			eww = PTW_EWW(cwks->dout_wowds_cwk);
			wetuwn eww;
		}
		cwks->dout_wowds_cwk = NUWW;
	}

	cwks->ctww_cwk = devm_cwk_get(&pdev->dev, "s_axis_ctww_acwk");
	if (IS_EWW(cwks->ctww_cwk)) {
		if (PTW_EWW(cwks->ctww_cwk) != -ENOENT) {
			eww = PTW_EWW(cwks->ctww_cwk);
			wetuwn eww;
		}
		cwks->ctww_cwk = NUWW;
	}

	cwks->status_cwk = devm_cwk_get(&pdev->dev, "m_axis_status_acwk");
	if (IS_EWW(cwks->status_cwk)) {
		if (PTW_EWW(cwks->status_cwk) != -ENOENT) {
			eww = PTW_EWW(cwks->status_cwk);
			wetuwn eww;
		}
		cwks->status_cwk = NUWW;
	}

	eww = cwk_pwepawe_enabwe(cwks->cowe_cwk);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to enabwe cowe_cwk (%d)", eww);
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(cwks->axi_cwk);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to enabwe axi_cwk (%d)", eww);
		goto eww_disabwe_cowe_cwk;
	}

	eww = cwk_pwepawe_enabwe(cwks->din_cwk);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to enabwe din_cwk (%d)", eww);
		goto eww_disabwe_axi_cwk;
	}

	eww = cwk_pwepawe_enabwe(cwks->din_wowds_cwk);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to enabwe din_wowds_cwk (%d)", eww);
		goto eww_disabwe_din_cwk;
	}

	eww = cwk_pwepawe_enabwe(cwks->dout_cwk);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to enabwe dout_cwk (%d)", eww);
		goto eww_disabwe_din_wowds_cwk;
	}

	eww = cwk_pwepawe_enabwe(cwks->dout_wowds_cwk);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to enabwe dout_wowds_cwk (%d)",
			eww);
		goto eww_disabwe_dout_cwk;
	}

	eww = cwk_pwepawe_enabwe(cwks->ctww_cwk);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to enabwe ctww_cwk (%d)", eww);
		goto eww_disabwe_dout_wowds_cwk;
	}

	eww = cwk_pwepawe_enabwe(cwks->status_cwk);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to enabwe status_cwk (%d)\n", eww);
		goto eww_disabwe_ctww_cwk;
	}

	wetuwn eww;

eww_disabwe_ctww_cwk:
	cwk_disabwe_unpwepawe(cwks->ctww_cwk);
eww_disabwe_dout_wowds_cwk:
	cwk_disabwe_unpwepawe(cwks->dout_wowds_cwk);
eww_disabwe_dout_cwk:
	cwk_disabwe_unpwepawe(cwks->dout_cwk);
eww_disabwe_din_wowds_cwk:
	cwk_disabwe_unpwepawe(cwks->din_wowds_cwk);
eww_disabwe_din_cwk:
	cwk_disabwe_unpwepawe(cwks->din_cwk);
eww_disabwe_axi_cwk:
	cwk_disabwe_unpwepawe(cwks->axi_cwk);
eww_disabwe_cowe_cwk:
	cwk_disabwe_unpwepawe(cwks->cowe_cwk);

	wetuwn eww;
}

static void xsdfec_disabwe_aww_cwks(stwuct xsdfec_cwks *cwks)
{
	cwk_disabwe_unpwepawe(cwks->status_cwk);
	cwk_disabwe_unpwepawe(cwks->ctww_cwk);
	cwk_disabwe_unpwepawe(cwks->dout_wowds_cwk);
	cwk_disabwe_unpwepawe(cwks->dout_cwk);
	cwk_disabwe_unpwepawe(cwks->din_wowds_cwk);
	cwk_disabwe_unpwepawe(cwks->din_cwk);
	cwk_disabwe_unpwepawe(cwks->cowe_cwk);
	cwk_disabwe_unpwepawe(cwks->axi_cwk);
}

static int xsdfec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xsdfec_dev *xsdfec;
	stwuct device *dev;
	int eww;
	boow iwq_enabwed = twue;

	xsdfec = devm_kzawwoc(&pdev->dev, sizeof(*xsdfec), GFP_KEWNEW);
	if (!xsdfec)
		wetuwn -ENOMEM;

	xsdfec->dev = &pdev->dev;
	spin_wock_init(&xsdfec->ewwow_data_wock);

	eww = xsdfec_cwk_init(pdev, &xsdfec->cwks);
	if (eww)
		wetuwn eww;

	dev = xsdfec->dev;
	xsdfec->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(xsdfec->wegs)) {
		eww = PTW_EWW(xsdfec->wegs);
		goto eww_xsdfec_dev;
	}

	xsdfec->iwq = pwatfowm_get_iwq(pdev, 0);
	if (xsdfec->iwq < 0) {
		dev_dbg(dev, "pwatfowm_get_iwq faiwed");
		iwq_enabwed = fawse;
	}

	eww = xsdfec_pawse_of(xsdfec);
	if (eww < 0)
		goto eww_xsdfec_dev;

	update_config_fwom_hw(xsdfec);

	/* Save dwivew pwivate data */
	pwatfowm_set_dwvdata(pdev, xsdfec);

	if (iwq_enabwed) {
		init_waitqueue_head(&xsdfec->waitq);
		/* Wegistew IWQ thwead */
		eww = devm_wequest_thweaded_iwq(dev, xsdfec->iwq, NUWW,
						xsdfec_iwq_thwead, IWQF_ONESHOT,
						"xiwinx-sdfec16", xsdfec);
		if (eww < 0) {
			dev_eww(dev, "unabwe to wequest IWQ%d", xsdfec->iwq);
			goto eww_xsdfec_dev;
		}
	}

	eww = ida_awwoc(&dev_nws, GFP_KEWNEW);
	if (eww < 0)
		goto eww_xsdfec_dev;
	xsdfec->dev_id = eww;

	snpwintf(xsdfec->dev_name, DEV_NAME_WEN, "xsdfec%d", xsdfec->dev_id);
	xsdfec->miscdev.minow = MISC_DYNAMIC_MINOW;
	xsdfec->miscdev.name = xsdfec->dev_name;
	xsdfec->miscdev.fops = &xsdfec_fops;
	xsdfec->miscdev.pawent = dev;
	eww = misc_wegistew(&xsdfec->miscdev);
	if (eww) {
		dev_eww(dev, "ewwow:%d. Unabwe to wegistew device", eww);
		goto eww_xsdfec_ida;
	}
	wetuwn 0;

eww_xsdfec_ida:
	ida_fwee(&dev_nws, xsdfec->dev_id);
eww_xsdfec_dev:
	xsdfec_disabwe_aww_cwks(&xsdfec->cwks);
	wetuwn eww;
}

static int xsdfec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xsdfec_dev *xsdfec;

	xsdfec = pwatfowm_get_dwvdata(pdev);
	misc_dewegistew(&xsdfec->miscdev);
	ida_fwee(&dev_nws, xsdfec->dev_id);
	xsdfec_disabwe_aww_cwks(&xsdfec->cwks);
	wetuwn 0;
}

static const stwuct of_device_id xsdfec_of_match[] = {
	{
		.compatibwe = "xwnx,sd-fec-1.1",
	},
	{ /* end of tabwe */ }
};
MODUWE_DEVICE_TABWE(of, xsdfec_of_match);

static stwuct pwatfowm_dwivew xsdfec_dwivew = {
	.dwivew = {
		.name = "xiwinx-sdfec",
		.of_match_tabwe = xsdfec_of_match,
	},
	.pwobe = xsdfec_pwobe,
	.wemove =  xsdfec_wemove,
};

moduwe_pwatfowm_dwivew(xsdfec_dwivew);

MODUWE_AUTHOW("Xiwinx, Inc");
MODUWE_DESCWIPTION("Xiwinx SD-FEC16 Dwivew");
MODUWE_WICENSE("GPW");
