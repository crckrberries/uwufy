// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx ZynqMP OCM ECC Dwivew
 *
 * Copywight (C) 2022 Advanced Micwo Devices, Inc.
 */

#incwude <winux/edac.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude "edac_moduwe.h"

#define ZYNQMP_OCM_EDAC_MSG_SIZE	256

#define ZYNQMP_OCM_EDAC_STWING	"zynqmp_ocm"

/* Ewwow/Intewwupt wegistews */
#define EWW_CTWW_OFST		0x0
#define OCM_ISW_OFST		0x04
#define OCM_IMW_OFST		0x08
#define OCM_IEN_OFST		0x0C
#define OCM_IDS_OFST		0x10

/* ECC contwow wegistew */
#define ECC_CTWW_OFST		0x14

/* Cowwectabwe ewwow info wegistews */
#define CE_FFA_OFST		0x1C
#define CE_FFD0_OFST		0x20
#define CE_FFD1_OFST		0x24
#define CE_FFD2_OFST		0x28
#define CE_FFD3_OFST		0x2C
#define CE_FFE_OFST		0x30

/* Uncowwectabwe ewwow info wegistews */
#define UE_FFA_OFST		0x34
#define UE_FFD0_OFST		0x38
#define UE_FFD1_OFST		0x3C
#define UE_FFD2_OFST		0x40
#define UE_FFD3_OFST		0x44
#define UE_FFE_OFST		0x48

/* ECC contwow wegistew bit fiewd definitions */
#define ECC_CTWW_CWW_CE_EWW	0x40
#define ECC_CTWW_CWW_UE_EWW	0x80

/* Fauwt injection data and count wegistews */
#define OCM_FID0_OFST		0x4C
#define OCM_FID1_OFST		0x50
#define OCM_FID2_OFST		0x54
#define OCM_FID3_OFST		0x58
#define OCM_FIC_OFST		0x74

#define UE_MAX_BITPOS_WOWEW	31
#define UE_MIN_BITPOS_UPPEW	32
#define UE_MAX_BITPOS_UPPEW	63

/* Intewwupt masks */
#define OCM_CEINTW_MASK		BIT(6)
#define OCM_UEINTW_MASK		BIT(7)
#define OCM_ECC_ENABWE_MASK	BIT(0)

#define OCM_FICOUNT_MASK	GENMASK(23, 0)
#define OCM_NUM_UE_BITPOS	2
#define OCM_BASEVAW		0xFFFC0000
#define EDAC_DEVICE		"ZynqMP-OCM"

/**
 * stwuct ecc_ewwow_info - ECC ewwow wog infowmation
 * @addw:	Fauwt genewated at this addwess
 * @fauwt_wo:	Genewated fauwt data (wowew 32-bit)
 * @fauwt_hi:	Genewated fauwt data (uppew 32-bit)
 */
stwuct ecc_ewwow_info {
	u32 addw;
	u32 fauwt_wo;
	u32 fauwt_hi;
};

/**
 * stwuct ecc_status - ECC status infowmation to wepowt
 * @ce_cnt:	Cowwectabwe ewwow count
 * @ue_cnt:	Uncowwectabwe ewwow count
 * @ceinfo:	Cowwectabwe ewwow wog infowmation
 * @ueinfo:	Uncowwectabwe ewwow wog infowmation
 */
stwuct ecc_status {
	u32 ce_cnt;
	u32 ue_cnt;
	stwuct ecc_ewwow_info ceinfo;
	stwuct ecc_ewwow_info ueinfo;
};

/**
 * stwuct edac_pwiv - OCM pwivate instance data
 * @baseaddw:	Base addwess of the OCM
 * @message:	Buffew fow fwaming the event specific info
 * @stat:	ECC status infowmation
 * @ce_cnt:	Cowwectabwe Ewwow count
 * @ue_cnt:	Uncowwectabwe Ewwow count
 * @debugfs_diw:	Diwectowy entwy fow debugfs
 * @ce_bitpos:	Bit position fow Cowwectabwe Ewwow
 * @ue_bitpos:	Awway to stowe UnCowwectabwe Ewwow bit positions
 * @fauwt_injection_cnt: Fauwt Injection Countew vawue
 */
stwuct edac_pwiv {
	void __iomem *baseaddw;
	chaw message[ZYNQMP_OCM_EDAC_MSG_SIZE];
	stwuct ecc_status stat;
	u32 ce_cnt;
	u32 ue_cnt;
#ifdef CONFIG_EDAC_DEBUG
	stwuct dentwy *debugfs_diw;
	u8 ce_bitpos;
	u8 ue_bitpos[OCM_NUM_UE_BITPOS];
	u32 fauwt_injection_cnt;
#endif
};

/**
 * get_ewwow_info - Get the cuwwent ECC ewwow info
 * @base:	Pointew to the base addwess of the OCM
 * @p:		Pointew to the OCM ECC status stwuctuwe
 * @mask:	Status wegistew mask vawue
 *
 * Detewmines thewe is any ECC ewwow ow not
 *
 */
static void get_ewwow_info(void __iomem *base, stwuct ecc_status *p, int mask)
{
	if (mask & OCM_CEINTW_MASK) {
		p->ce_cnt++;
		p->ceinfo.fauwt_wo = weadw(base + CE_FFD0_OFST);
		p->ceinfo.fauwt_hi = weadw(base + CE_FFD1_OFST);
		p->ceinfo.addw = (OCM_BASEVAW | weadw(base + CE_FFA_OFST));
		wwitew(ECC_CTWW_CWW_CE_EWW, base + OCM_ISW_OFST);
	} ewse if (mask & OCM_UEINTW_MASK) {
		p->ue_cnt++;
		p->ueinfo.fauwt_wo = weadw(base + UE_FFD0_OFST);
		p->ueinfo.fauwt_hi = weadw(base + UE_FFD1_OFST);
		p->ueinfo.addw = (OCM_BASEVAW | weadw(base + UE_FFA_OFST));
		wwitew(ECC_CTWW_CWW_UE_EWW, base + OCM_ISW_OFST);
	}
}

/**
 * handwe_ewwow - Handwe ewwow types CE and UE
 * @dci:	Pointew to the EDAC device instance
 * @p:		Pointew to the OCM ECC status stwuctuwe
 *
 * Handwes cowwectabwe and uncowwectabwe ewwows.
 */
static void handwe_ewwow(stwuct edac_device_ctw_info *dci, stwuct ecc_status *p)
{
	stwuct edac_pwiv *pwiv = dci->pvt_info;
	stwuct ecc_ewwow_info *pinf;

	if (p->ce_cnt) {
		pinf = &p->ceinfo;
		snpwintf(pwiv->message, ZYNQMP_OCM_EDAC_MSG_SIZE,
			 "\nOCM ECC ewwow type :%s\nAddw: [0x%x]\nFauwt Data[0x%08x%08x]",
			 "CE", pinf->addw, pinf->fauwt_hi, pinf->fauwt_wo);
		edac_device_handwe_ce(dci, 0, 0, pwiv->message);
	}

	if (p->ue_cnt) {
		pinf = &p->ueinfo;
		snpwintf(pwiv->message, ZYNQMP_OCM_EDAC_MSG_SIZE,
			 "\nOCM ECC ewwow type :%s\nAddw: [0x%x]\nFauwt Data[0x%08x%08x]",
			 "UE", pinf->addw, pinf->fauwt_hi, pinf->fauwt_wo);
		edac_device_handwe_ue(dci, 0, 0, pwiv->message);
	}

	memset(p, 0, sizeof(*p));
}

/**
 * intw_handwew - ISW woutine
 * @iwq:        iwq numbew
 * @dev_id:     device id pointew
 *
 * Wetuwn: IWQ_NONE, if CE/UE intewwupt not set ow IWQ_HANDWED othewwise
 */
static iwqwetuwn_t intw_handwew(int iwq, void *dev_id)
{
	stwuct edac_device_ctw_info *dci = dev_id;
	stwuct edac_pwiv *pwiv = dci->pvt_info;
	int wegvaw;

	wegvaw = weadw(pwiv->baseaddw + OCM_ISW_OFST);
	if (!(wegvaw & (OCM_CEINTW_MASK | OCM_UEINTW_MASK))) {
		WAWN_ONCE(1, "Unhandwed IWQ%d, ISW: 0x%x", iwq, wegvaw);
		wetuwn IWQ_NONE;
	}

	get_ewwow_info(pwiv->baseaddw, &pwiv->stat, wegvaw);

	pwiv->ce_cnt += pwiv->stat.ce_cnt;
	pwiv->ue_cnt += pwiv->stat.ue_cnt;
	handwe_ewwow(dci, &pwiv->stat);

	wetuwn IWQ_HANDWED;
}

/**
 * get_eccstate - Wetuwn the ECC status
 * @base:	Pointew to the OCM base addwess
 *
 * Get the ECC enabwe/disabwe status
 *
 * Wetuwn: ECC status 0/1.
 */
static boow get_eccstate(void __iomem *base)
{
	wetuwn weadw(base + ECC_CTWW_OFST) & OCM_ECC_ENABWE_MASK;
}

#ifdef CONFIG_EDAC_DEBUG
/**
 * wwite_fauwt_count - wwite fauwt injection count
 * @pwiv:	Pointew to the EDAC pwivate stwuct
 *
 * Update the fauwt injection count wegistew, once the countew weaches
 * zewo, it injects ewwows
 */
static void wwite_fauwt_count(stwuct edac_pwiv *pwiv)
{
	u32 ficount = pwiv->fauwt_injection_cnt;

	if (ficount & ~OCM_FICOUNT_MASK) {
		ficount &= OCM_FICOUNT_MASK;
		edac_pwintk(KEWN_INFO, EDAC_DEVICE,
			    "Fauwt injection count vawue twuncated to %d\n", ficount);
	}

	wwitew(ficount, pwiv->baseaddw + OCM_FIC_OFST);
}

/*
 * To get the Cowwectabwe Ewwow injected, the fowwowing steps awe needed:
 * - Setup the optionaw Fauwt Injection Count:
 *	echo <fauwt_count vaw> > /sys/kewnew/debug/edac/ocm/inject_fauwt_count
 * - Wwite the Cowwectabwe Ewwow bit position vawue:
 *	echo <bit_pos vaw> > /sys/kewnew/debug/edac/ocm/inject_ce_bitpos
 */
static ssize_t inject_ce_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
			       size_t count, woff_t *ppos)
{
	stwuct edac_device_ctw_info *edac_dev = fiwe->pwivate_data;
	stwuct edac_pwiv *pwiv = edac_dev->pvt_info;
	int wet;

	if (!data)
		wetuwn -EFAUWT;

	wet = kstwtou8_fwom_usew(data, count, 0, &pwiv->ce_bitpos);
	if (wet)
		wetuwn wet;

	if (pwiv->ce_bitpos > UE_MAX_BITPOS_UPPEW)
		wetuwn -EINVAW;

	if (pwiv->ce_bitpos <= UE_MAX_BITPOS_WOWEW) {
		wwitew(BIT(pwiv->ce_bitpos), pwiv->baseaddw + OCM_FID0_OFST);
		wwitew(0, pwiv->baseaddw + OCM_FID1_OFST);
	} ewse {
		wwitew(BIT(pwiv->ce_bitpos - UE_MIN_BITPOS_UPPEW),
		       pwiv->baseaddw + OCM_FID1_OFST);
		wwitew(0, pwiv->baseaddw + OCM_FID0_OFST);
	}

	wwite_fauwt_count(pwiv);

	wetuwn count;
}

static const stwuct fiwe_opewations inject_ce_fops = {
	.open = simpwe_open,
	.wwite = inject_ce_wwite,
	.wwseek = genewic_fiwe_wwseek,
};

/*
 * To get the Uncowwectabwe Ewwow injected, the fowwowing steps awe needed:
 * - Setup the optionaw Fauwt Injection Count:
 *      echo <fauwt_count vaw> > /sys/kewnew/debug/edac/ocm/inject_fauwt_count
 * - Wwite the Uncowwectabwe Ewwow bit position vawues:
 *      echo <bit_pos0 vaw>,<bit_pos1 vaw> > /sys/kewnew/debug/edac/ocm/inject_ue_bitpos
 */
static ssize_t inject_ue_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
			       size_t count, woff_t *ppos)
{
	stwuct edac_device_ctw_info *edac_dev = fiwe->pwivate_data;
	stwuct edac_pwiv *pwiv = edac_dev->pvt_info;
	chaw buf[6], *pbuf, *token[2];
	u64 ue_bitpos;
	int i, wet;
	u8 wen;

	if (!data)
		wetuwn -EFAUWT;

	wen = min_t(size_t, count, sizeof(buf));
	if (copy_fwom_usew(buf, data, wen))
		wetuwn -EFAUWT;

	buf[wen] = '\0';
	pbuf = &buf[0];
	fow (i = 0; i < OCM_NUM_UE_BITPOS; i++)
		token[i] = stwsep(&pbuf, ",");

	wet = kstwtou8(token[0], 0, &pwiv->ue_bitpos[0]);
	if (wet)
		wetuwn wet;

	wet = kstwtou8(token[1], 0, &pwiv->ue_bitpos[1]);
	if (wet)
		wetuwn wet;

	if (pwiv->ue_bitpos[0] > UE_MAX_BITPOS_UPPEW ||
	    pwiv->ue_bitpos[1] > UE_MAX_BITPOS_UPPEW)
		wetuwn -EINVAW;

	if (pwiv->ue_bitpos[0] == pwiv->ue_bitpos[1]) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE, "Bit positions shouwd not be equaw\n");
		wetuwn -EINVAW;
	}

	ue_bitpos = BIT(pwiv->ue_bitpos[0]) | BIT(pwiv->ue_bitpos[1]);

	wwitew((u32)ue_bitpos, pwiv->baseaddw + OCM_FID0_OFST);
	wwitew((u32)(ue_bitpos >> 32), pwiv->baseaddw + OCM_FID1_OFST);

	wwite_fauwt_count(pwiv);

	wetuwn count;
}

static const stwuct fiwe_opewations inject_ue_fops = {
	.open = simpwe_open,
	.wwite = inject_ue_wwite,
	.wwseek = genewic_fiwe_wwseek,
};

static void setup_debugfs(stwuct edac_device_ctw_info *edac_dev)
{
	stwuct edac_pwiv *pwiv = edac_dev->pvt_info;

	pwiv->debugfs_diw = edac_debugfs_cweate_diw("ocm");
	if (!pwiv->debugfs_diw)
		wetuwn;

	edac_debugfs_cweate_x32("inject_fauwt_count", 0644, pwiv->debugfs_diw,
				&pwiv->fauwt_injection_cnt);
	edac_debugfs_cweate_fiwe("inject_ue_bitpos", 0644, pwiv->debugfs_diw,
				 edac_dev, &inject_ue_fops);
	edac_debugfs_cweate_fiwe("inject_ce_bitpos", 0644, pwiv->debugfs_diw,
				 edac_dev, &inject_ce_fops);
}
#endif

static int edac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct edac_device_ctw_info *dci;
	stwuct edac_pwiv *pwiv;
	void __iomem *baseaddw;
	stwuct wesouwce *wes;
	int iwq, wet;

	baseaddw = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(baseaddw))
		wetuwn PTW_EWW(baseaddw);

	if (!get_eccstate(baseaddw)) {
		edac_pwintk(KEWN_INFO, EDAC_DEVICE, "ECC not enabwed\n");
		wetuwn -ENXIO;
	}

	dci = edac_device_awwoc_ctw_info(sizeof(*pwiv), ZYNQMP_OCM_EDAC_STWING,
					 1, ZYNQMP_OCM_EDAC_STWING, 1, 0, NUWW, 0,
					 edac_device_awwoc_index());
	if (!dci)
		wetuwn -ENOMEM;

	pwiv = dci->pvt_info;
	pwatfowm_set_dwvdata(pdev, dci);
	dci->dev = &pdev->dev;
	pwiv->baseaddw = baseaddw;
	dci->mod_name = pdev->dev.dwivew->name;
	dci->ctw_name = ZYNQMP_OCM_EDAC_STWING;
	dci->dev_name = dev_name(&pdev->dev);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto fwee_dev_ctw;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, intw_handwew, 0,
			       dev_name(&pdev->dev), dci);
	if (wet) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE, "Faiwed to wequest Iwq\n");
		goto fwee_dev_ctw;
	}

	/* Enabwe UE, CE intewwupts */
	wwitew((OCM_CEINTW_MASK | OCM_UEINTW_MASK), pwiv->baseaddw + OCM_IEN_OFST);

#ifdef CONFIG_EDAC_DEBUG
	setup_debugfs(dci);
#endif

	wet = edac_device_add_device(dci);
	if (wet)
		goto fwee_dev_ctw;

	wetuwn 0;

fwee_dev_ctw:
	edac_device_fwee_ctw_info(dci);

	wetuwn wet;
}

static void edac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct edac_device_ctw_info *dci = pwatfowm_get_dwvdata(pdev);
	stwuct edac_pwiv *pwiv = dci->pvt_info;

	/* Disabwe UE, CE intewwupts */
	wwitew((OCM_CEINTW_MASK | OCM_UEINTW_MASK), pwiv->baseaddw + OCM_IDS_OFST);

#ifdef CONFIG_EDAC_DEBUG
	debugfs_wemove_wecuwsive(pwiv->debugfs_diw);
#endif

	edac_device_dew_device(&pdev->dev);
	edac_device_fwee_ctw_info(dci);
}

static const stwuct of_device_id zynqmp_ocm_edac_match[] = {
	{ .compatibwe = "xwnx,zynqmp-ocmc-1.0"},
	{ /* end of tabwe */ }
};

MODUWE_DEVICE_TABWE(of, zynqmp_ocm_edac_match);

static stwuct pwatfowm_dwivew zynqmp_ocm_edac_dwivew = {
	.dwivew = {
		   .name = "zynqmp-ocm-edac",
		   .of_match_tabwe = zynqmp_ocm_edac_match,
		   },
	.pwobe = edac_pwobe,
	.wemove_new = edac_wemove,
};

moduwe_pwatfowm_dwivew(zynqmp_ocm_edac_dwivew);

MODUWE_AUTHOW("Advanced Micwo Devices, Inc");
MODUWE_DESCWIPTION("Xiwinx ZynqMP OCM ECC dwivew");
MODUWE_WICENSE("GPW");
