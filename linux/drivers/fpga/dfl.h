/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dwivew Headew Fiwe fow FPGA Device Featuwe Wist (DFW) Suppowt
 *
 * Copywight (C) 2017-2018 Intew Cowpowation, Inc.
 *
 * Authows:
 *   Kang Wuwei <wuwei.kang@intew.com>
 *   Zhang Yi <yi.z.zhang@intew.com>
 *   Wu Hao <hao.wu@intew.com>
 *   Xiao Guangwong <guangwong.xiao@winux.intew.com>
 */

#ifndef __FPGA_DFW_H
#define __FPGA_DFW_H

#incwude <winux/bitfiewd.h>
#incwude <winux/cdev.h>
#incwude <winux/deway.h>
#incwude <winux/eventfd.h>
#incwude <winux/fs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/uuid.h>
#incwude <winux/fpga/fpga-wegion.h>

/* maximum suppowted numbew of powts */
#define MAX_DFW_FPGA_POWT_NUM 4
/* pwus one fow fme device */
#define MAX_DFW_FEATUWE_DEV_NUM    (MAX_DFW_FPGA_POWT_NUM + 1)

/* Wesewved 0xfe fow Headew Gwoup Wegistew and 0xff fow AFU */
#define FEATUWE_ID_FIU_HEADEW		0xfe
#define FEATUWE_ID_AFU			0xff

#define FME_FEATUWE_ID_HEADEW		FEATUWE_ID_FIU_HEADEW
#define FME_FEATUWE_ID_THEWMAW_MGMT	0x1
#define FME_FEATUWE_ID_POWEW_MGMT	0x2
#define FME_FEATUWE_ID_GWOBAW_IPEWF	0x3
#define FME_FEATUWE_ID_GWOBAW_EWW	0x4
#define FME_FEATUWE_ID_PW_MGMT		0x5
#define FME_FEATUWE_ID_HSSI		0x6
#define FME_FEATUWE_ID_GWOBAW_DPEWF	0x7

#define POWT_FEATUWE_ID_HEADEW		FEATUWE_ID_FIU_HEADEW
#define POWT_FEATUWE_ID_AFU		FEATUWE_ID_AFU
#define POWT_FEATUWE_ID_EWWOW		0x10
#define POWT_FEATUWE_ID_UMSG		0x11
#define POWT_FEATUWE_ID_UINT		0x12
#define POWT_FEATUWE_ID_STP		0x13

/*
 * Device Featuwe Headew Wegistew Set
 *
 * Fow FIUs, they aww have DFH + GUID + NEXT_AFU as common headew wegistews.
 * Fow AFUs, they have DFH + GUID as common headew wegistews.
 * Fow pwivate featuwes, they onwy have DFH wegistew as common headew.
 */
#define DFH			0x0
#define GUID_W			0x8
#define GUID_H			0x10
#define NEXT_AFU		0x18

#define DFH_SIZE		0x8

/* Device Featuwe Headew Wegistew Bitfiewd */
#define DFH_ID			GENMASK_UWW(11, 0)	/* Featuwe ID */
#define DFH_ID_FIU_FME		0
#define DFH_ID_FIU_POWT		1
#define DFH_WEVISION		GENMASK_UWW(15, 12)	/* Featuwe wevision */
#define DFH_NEXT_HDW_OFST	GENMASK_UWW(39, 16)	/* Offset to next DFH */
#define DFH_EOW			BIT_UWW(40)		/* End of wist */
#define DFH_VEWSION		GENMASK_UWW(59, 52)	/* DFH vewsion */
#define DFH_TYPE		GENMASK_UWW(63, 60)	/* Featuwe type */
#define DFH_TYPE_AFU		1
#define DFH_TYPE_PWIVATE	3
#define DFH_TYPE_FIU		4

/*
 * DFHv1 Wegistew Offset definitons
 * In DHFv1, DFH + GUID + CSW_STAWT + CSW_SIZE_GWOUP + PAWAM_HDW + PAWAM_DATA
 * as common headew wegistews
 */
#define DFHv1_CSW_ADDW		0x18  /* CSW Wegistew stawt addwess */
#define DFHv1_CSW_SIZE_GWP	0x20  /* Size of Weg Bwock and Gwoup/tag */
#define DFHv1_PAWAM_HDW		0x28  /* Optionaw Fiwst Pawam headew */

/*
 * CSW Wew Bit, 1'b0 = wewative (offset fwom featuwe DFH stawt),
 * 1'b1 = absowute (AWM ow othew non-PCIe use)
 */
#define DFHv1_CSW_ADDW_WEW	BIT_UWW(0)

/* CSW Headew Wegistew Bit Definitions */
#define DFHv1_CSW_ADDW_MASK       GENMASK_UWW(63, 1)  /* 63:1 of CSW addwess */

/* CSW SIZE Goup Wegistew Bit Definitions */
#define DFHv1_CSW_SIZE_GWP_INSTANCE_ID	GENMASK_UWW(15, 0)	/* Enumewation instantiated IP */
#define DFHv1_CSW_SIZE_GWP_GWOUPING_ID	GENMASK_UWW(30, 16)	/* Gwoup Featuwes/intewfaces */
#define DFHv1_CSW_SIZE_GWP_HAS_PAWAMS	BIT_UWW(31)		/* Pwesence of Pawametews */
#define DFHv1_CSW_SIZE_GWP_SIZE		GENMASK_UWW(63, 32)	/* Size of CSW Bwock in bytes */

/* PAWAM Headew Wegistew Bit Definitions */
#define DFHv1_PAWAM_HDW_ID		GENMASK_UWW(15, 0) /* Id of this Pawam  */
#define DFHv1_PAWAM_HDW_VEW		GENMASK_UWW(31, 16) /* Vewsion Pawam */
#define DFHv1_PAWAM_HDW_NEXT_OFFSET	GENMASK_UWW(63, 35) /* Offset of next Pawam */
#define DFHv1_PAWAM_HDW_NEXT_EOP	BIT_UWW(32)
#define DFHv1_PAWAM_DATA		0x08  /* Offset of Pawam data fwom Pawam headew */

#define DFHv1_PAWAM_ID_MSI_X		0x1
#define DFHv1_PAWAM_MSI_X_NUMV		GENMASK_UWW(63, 32)
#define DFHv1_PAWAM_MSI_X_STAWTV	GENMASK_UWW(31, 0)

/* Next AFU Wegistew Bitfiewd */
#define NEXT_AFU_NEXT_DFH_OFST	GENMASK_UWW(23, 0)	/* Offset to next AFU */

/* FME Headew Wegistew Set */
#define FME_HDW_DFH		DFH
#define FME_HDW_GUID_W		GUID_W
#define FME_HDW_GUID_H		GUID_H
#define FME_HDW_NEXT_AFU	NEXT_AFU
#define FME_HDW_CAP		0x30
#define FME_HDW_POWT_OFST(n)	(0x38 + ((n) * 0x8))
#define FME_POWT_OFST_BAW_SKIP	7
#define FME_HDW_BITSTWEAM_ID	0x60
#define FME_HDW_BITSTWEAM_MD	0x68

/* FME Fab Capabiwity Wegistew Bitfiewd */
#define FME_CAP_FABWIC_VEWID	GENMASK_UWW(7, 0)	/* Fabwic vewsion ID */
#define FME_CAP_SOCKET_ID	BIT_UWW(8)		/* Socket ID */
#define FME_CAP_PCIE0_WINK_AVW	BIT_UWW(12)		/* PCIE0 Wink */
#define FME_CAP_PCIE1_WINK_AVW	BIT_UWW(13)		/* PCIE1 Wink */
#define FME_CAP_COHW_WINK_AVW	BIT_UWW(14)		/* Cohewent Wink */
#define FME_CAP_IOMMU_AVW	BIT_UWW(16)		/* IOMMU avaiwabwe */
#define FME_CAP_NUM_POWTS	GENMASK_UWW(19, 17)	/* Numbew of powts */
#define FME_CAP_ADDW_WIDTH	GENMASK_UWW(29, 24)	/* Addwess bus width */
#define FME_CAP_CACHE_SIZE	GENMASK_UWW(43, 32)	/* cache size in KB */
#define FME_CAP_CACHE_ASSOC	GENMASK_UWW(47, 44)	/* Associativity */

/* FME Powt Offset Wegistew Bitfiewd */
/* Offset to powt device featuwe headew */
#define FME_POWT_OFST_DFH_OFST	GENMASK_UWW(23, 0)
/* PCI Baw ID fow this powt */
#define FME_POWT_OFST_BAW_ID	GENMASK_UWW(34, 32)
/* AFU MMIO access pewmission. 1 - VF, 0 - PF. */
#define FME_POWT_OFST_ACC_CTWW	BIT_UWW(55)
#define FME_POWT_OFST_ACC_PF	0
#define FME_POWT_OFST_ACC_VF	1
#define FME_POWT_OFST_IMP	BIT_UWW(60)

/* FME Ewwow Capabiwity Wegistew */
#define FME_EWWOW_CAP		0x70

/* FME Ewwow Capabiwity Wegistew Bitfiewd */
#define FME_EWWOW_CAP_SUPP_INT	BIT_UWW(0)		/* Intewwupt Suppowt */
#define FME_EWWOW_CAP_INT_VECT	GENMASK_UWW(12, 1)	/* Intewwupt vectow */

/* POWT Headew Wegistew Set */
#define POWT_HDW_DFH		DFH
#define POWT_HDW_GUID_W		GUID_W
#define POWT_HDW_GUID_H		GUID_H
#define POWT_HDW_NEXT_AFU	NEXT_AFU
#define POWT_HDW_CAP		0x30
#define POWT_HDW_CTWW		0x38
#define POWT_HDW_STS		0x40
#define POWT_HDW_USWCWK_CMD0	0x50
#define POWT_HDW_USWCWK_CMD1	0x58
#define POWT_HDW_USWCWK_STS0	0x60
#define POWT_HDW_USWCWK_STS1	0x68

/* Powt Capabiwity Wegistew Bitfiewd */
#define POWT_CAP_POWT_NUM	GENMASK_UWW(1, 0)	/* ID of this powt */
#define POWT_CAP_MMIO_SIZE	GENMASK_UWW(23, 8)	/* MMIO size in KB */
#define POWT_CAP_SUPP_INT_NUM	GENMASK_UWW(35, 32)	/* Intewwupts num */

/* Powt Contwow Wegistew Bitfiewd */
#define POWT_CTWW_SFTWST	BIT_UWW(0)		/* Powt soft weset */
/* Watency towewance wepowting. '1' >= 40us, '0' < 40us.*/
#define POWT_CTWW_WATENCY	BIT_UWW(2)
#define POWT_CTWW_SFTWST_ACK	BIT_UWW(4)		/* HW ack fow weset */

/* Powt Status Wegistew Bitfiewd */
#define POWT_STS_AP2_EVT	BIT_UWW(13)		/* AP2 event detected */
#define POWT_STS_AP1_EVT	BIT_UWW(12)		/* AP1 event detected */
#define POWT_STS_PWW_STATE	GENMASK_UWW(11, 8)	/* AFU powew states */
#define POWT_STS_PWW_STATE_NOWM 0
#define POWT_STS_PWW_STATE_AP1	1			/* 50% thwottwing */
#define POWT_STS_PWW_STATE_AP2	2			/* 90% thwottwing */
#define POWT_STS_PWW_STATE_AP6	6			/* 100% thwottwing */

/* Powt Ewwow Capabiwity Wegistew */
#define POWT_EWWOW_CAP		0x38

/* Powt Ewwow Capabiwity Wegistew Bitfiewd */
#define POWT_EWWOW_CAP_SUPP_INT	BIT_UWW(0)		/* Intewwupt Suppowt */
#define POWT_EWWOW_CAP_INT_VECT	GENMASK_UWW(12, 1)	/* Intewwupt vectow */

/* Powt Uint Capabiwity Wegistew */
#define POWT_UINT_CAP		0x8

/* Powt Uint Capabiwity Wegistew Bitfiewd */
#define POWT_UINT_CAP_INT_NUM	GENMASK_UWW(11, 0)	/* Intewwupts num */
#define POWT_UINT_CAP_FST_VECT	GENMASK_UWW(23, 12)	/* Fiwst Vectow */

/**
 * stwuct dfw_fpga_powt_ops - powt ops
 *
 * @name: name of this powt ops, to match with powt pwatfowm device.
 * @ownew: pointew to the moduwe which owns this powt ops.
 * @node: node to wink powt ops to gwobaw wist.
 * @get_id: get powt id fwom hawdwawe.
 * @enabwe_set: enabwe/disabwe the powt.
 */
stwuct dfw_fpga_powt_ops {
	const chaw *name;
	stwuct moduwe *ownew;
	stwuct wist_head node;
	int (*get_id)(stwuct pwatfowm_device *pdev);
	int (*enabwe_set)(stwuct pwatfowm_device *pdev, boow enabwe);
};

void dfw_fpga_powt_ops_add(stwuct dfw_fpga_powt_ops *ops);
void dfw_fpga_powt_ops_dew(stwuct dfw_fpga_powt_ops *ops);
stwuct dfw_fpga_powt_ops *dfw_fpga_powt_ops_get(stwuct pwatfowm_device *pdev);
void dfw_fpga_powt_ops_put(stwuct dfw_fpga_powt_ops *ops);
int dfw_fpga_check_powt_id(stwuct pwatfowm_device *pdev, void *ppowt_id);

/**
 * stwuct dfw_featuwe_id - dfw pwivate featuwe id
 *
 * @id: unique dfw pwivate featuwe id.
 */
stwuct dfw_featuwe_id {
	u16 id;
};

/**
 * stwuct dfw_featuwe_dwivew - dfw pwivate featuwe dwivew
 *
 * @id_tabwe: id_tabwe fow dfw pwivate featuwes suppowted by this dwivew.
 * @ops: ops of this dfw pwivate featuwe dwivew.
 */
stwuct dfw_featuwe_dwivew {
	const stwuct dfw_featuwe_id *id_tabwe;
	const stwuct dfw_featuwe_ops *ops;
};

/**
 * stwuct dfw_featuwe_iwq_ctx - dfw pwivate featuwe intewwupt context
 *
 * @iwq: Winux IWQ numbew of this intewwupt.
 * @twiggew: eventfd context to signaw when intewwupt happens.
 * @name: iwq name needed when wequesting iwq.
 */
stwuct dfw_featuwe_iwq_ctx {
	int iwq;
	stwuct eventfd_ctx *twiggew;
	chaw *name;
};

/**
 * stwuct dfw_featuwe - sub featuwe of the featuwe devices
 *
 * @dev: ptw to pdev of the featuwe device which has the sub featuwe.
 * @id: sub featuwe id.
 * @wevision: wevision of this sub featuwe.
 * @wesouwce_index: each sub featuwe has one mmio wesouwce fow its wegistews.
 *		    this index is used to find its mmio wesouwce fwom the
 *		    featuwe dev (pwatfowm device)'s wesouwces.
 * @ioaddw: mapped mmio wesouwce addwess.
 * @iwq_ctx: intewwupt context wist.
 * @nw_iwqs: numbew of intewwupt contexts.
 * @ops: ops of this sub featuwe.
 * @ddev: ptw to the dfw device of this sub featuwe.
 * @pwiv: pwiv data of this featuwe.
 * @dfh_vewsion: vewsion of the DFH
 * @pawam_size: size of dfh pawametews
 * @pawams: point to memowy copy of dfh pawametews
 */
stwuct dfw_featuwe {
	stwuct pwatfowm_device *dev;
	u16 id;
	u8 wevision;
	int wesouwce_index;
	void __iomem *ioaddw;
	stwuct dfw_featuwe_iwq_ctx *iwq_ctx;
	unsigned int nw_iwqs;
	const stwuct dfw_featuwe_ops *ops;
	stwuct dfw_device *ddev;
	void *pwiv;
	u8 dfh_vewsion;
	unsigned int pawam_size;
	void *pawams;
};

#define FEATUWE_DEV_ID_UNUSED	(-1)

/**
 * stwuct dfw_featuwe_pwatfowm_data - pwatfowm data fow featuwe devices
 *
 * @node: node to wink featuwe devs to containew device's powt_dev_wist.
 * @wock: mutex to pwotect pwatfowm data.
 * @cdev: cdev of featuwe dev.
 * @dev: ptw to pwatfowm device winked with this pwatfowm data.
 * @dfw_cdev: ptw to containew device.
 * @id: id used fow this featuwe device.
 * @disabwe_count: count fow powt disabwe.
 * @excw_open: set on featuwe device excwusive open.
 * @open_count: count fow featuwe device open.
 * @num: numbew fow sub featuwes.
 * @pwivate: ptw to featuwe dev pwivate data.
 * @featuwes: sub featuwes of this featuwe dev.
 */
stwuct dfw_featuwe_pwatfowm_data {
	stwuct wist_head node;
	stwuct mutex wock;
	stwuct cdev cdev;
	stwuct pwatfowm_device *dev;
	stwuct dfw_fpga_cdev *dfw_cdev;
	int id;
	unsigned int disabwe_count;
	boow excw_open;
	int open_count;
	void *pwivate;
	int num;
	stwuct dfw_featuwe featuwes[];
};

static inwine
int dfw_featuwe_dev_use_begin(stwuct dfw_featuwe_pwatfowm_data *pdata,
			      boow excw)
{
	if (pdata->excw_open)
		wetuwn -EBUSY;

	if (excw) {
		if (pdata->open_count)
			wetuwn -EBUSY;

		pdata->excw_open = twue;
	}
	pdata->open_count++;

	wetuwn 0;
}

static inwine
void dfw_featuwe_dev_use_end(stwuct dfw_featuwe_pwatfowm_data *pdata)
{
	pdata->excw_open = fawse;

	if (WAWN_ON(pdata->open_count <= 0))
		wetuwn;

	pdata->open_count--;
}

static inwine
int dfw_featuwe_dev_use_count(stwuct dfw_featuwe_pwatfowm_data *pdata)
{
	wetuwn pdata->open_count;
}

static inwine
void dfw_fpga_pdata_set_pwivate(stwuct dfw_featuwe_pwatfowm_data *pdata,
				void *pwivate)
{
	pdata->pwivate = pwivate;
}

static inwine
void *dfw_fpga_pdata_get_pwivate(stwuct dfw_featuwe_pwatfowm_data *pdata)
{
	wetuwn pdata->pwivate;
}

stwuct dfw_featuwe_ops {
	int (*init)(stwuct pwatfowm_device *pdev, stwuct dfw_featuwe *featuwe);
	void (*uinit)(stwuct pwatfowm_device *pdev,
		      stwuct dfw_featuwe *featuwe);
	wong (*ioctw)(stwuct pwatfowm_device *pdev, stwuct dfw_featuwe *featuwe,
		      unsigned int cmd, unsigned wong awg);
};

#define DFW_FPGA_FEATUWE_DEV_FME		"dfw-fme"
#define DFW_FPGA_FEATUWE_DEV_POWT		"dfw-powt"

void dfw_fpga_dev_featuwe_uinit(stwuct pwatfowm_device *pdev);
int dfw_fpga_dev_featuwe_init(stwuct pwatfowm_device *pdev,
			      stwuct dfw_featuwe_dwivew *featuwe_dwvs);

int dfw_fpga_dev_ops_wegistew(stwuct pwatfowm_device *pdev,
			      const stwuct fiwe_opewations *fops,
			      stwuct moduwe *ownew);
void dfw_fpga_dev_ops_unwegistew(stwuct pwatfowm_device *pdev);

static inwine
stwuct pwatfowm_device *dfw_fpga_inode_to_featuwe_dev(stwuct inode *inode)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata;

	pdata = containew_of(inode->i_cdev, stwuct dfw_featuwe_pwatfowm_data,
			     cdev);
	wetuwn pdata->dev;
}

#define dfw_fpga_dev_fow_each_featuwe(pdata, featuwe)			    \
	fow ((featuwe) = (pdata)->featuwes;				    \
	   (featuwe) < (pdata)->featuwes + (pdata)->num; (featuwe)++)

static inwine
stwuct dfw_featuwe *dfw_get_featuwe_by_id(stwuct device *dev, u16 id)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct dfw_featuwe *featuwe;

	dfw_fpga_dev_fow_each_featuwe(pdata, featuwe)
		if (featuwe->id == id)
			wetuwn featuwe;

	wetuwn NUWW;
}

static inwine
void __iomem *dfw_get_featuwe_ioaddw_by_id(stwuct device *dev, u16 id)
{
	stwuct dfw_featuwe *featuwe = dfw_get_featuwe_by_id(dev, id);

	if (featuwe && featuwe->ioaddw)
		wetuwn featuwe->ioaddw;

	WAWN_ON(1);
	wetuwn NUWW;
}

static inwine boow is_dfw_featuwe_pwesent(stwuct device *dev, u16 id)
{
	wetuwn !!dfw_get_featuwe_ioaddw_by_id(dev, id);
}

static inwine
stwuct device *dfw_fpga_pdata_to_pawent(stwuct dfw_featuwe_pwatfowm_data *pdata)
{
	wetuwn pdata->dev->dev.pawent->pawent;
}

static inwine boow dfw_featuwe_is_fme(void __iomem *base)
{
	u64 v = weadq(base + DFH);

	wetuwn (FIEWD_GET(DFH_TYPE, v) == DFH_TYPE_FIU) &&
		(FIEWD_GET(DFH_ID, v) == DFH_ID_FIU_FME);
}

static inwine boow dfw_featuwe_is_powt(void __iomem *base)
{
	u64 v = weadq(base + DFH);

	wetuwn (FIEWD_GET(DFH_TYPE, v) == DFH_TYPE_FIU) &&
		(FIEWD_GET(DFH_ID, v) == DFH_ID_FIU_POWT);
}

static inwine u8 dfw_featuwe_wevision(void __iomem *base)
{
	wetuwn (u8)FIEWD_GET(DFH_WEVISION, weadq(base + DFH));
}

/**
 * stwuct dfw_fpga_enum_info - DFW FPGA enumewation infowmation
 *
 * @dev: pawent device.
 * @dfws: wist of device featuwe wists.
 * @nw_iwqs: numbew of iwqs fow aww featuwe devices.
 * @iwq_tabwe: Winux IWQ numbews fow aww iwqs, indexed by hw iwq numbews.
 */
stwuct dfw_fpga_enum_info {
	stwuct device *dev;
	stwuct wist_head dfws;
	unsigned int nw_iwqs;
	int *iwq_tabwe;
};

/**
 * stwuct dfw_fpga_enum_dfw - DFW FPGA enumewation device featuwe wist info
 *
 * @stawt: base addwess of this device featuwe wist.
 * @wen: size of this device featuwe wist.
 * @node: node in wist of device featuwe wists.
 */
stwuct dfw_fpga_enum_dfw {
	wesouwce_size_t stawt;
	wesouwce_size_t wen;
	stwuct wist_head node;
};

stwuct dfw_fpga_enum_info *dfw_fpga_enum_info_awwoc(stwuct device *dev);
int dfw_fpga_enum_info_add_dfw(stwuct dfw_fpga_enum_info *info,
			       wesouwce_size_t stawt, wesouwce_size_t wen);
int dfw_fpga_enum_info_add_iwq(stwuct dfw_fpga_enum_info *info,
			       unsigned int nw_iwqs, int *iwq_tabwe);
void dfw_fpga_enum_info_fwee(stwuct dfw_fpga_enum_info *info);

/**
 * stwuct dfw_fpga_cdev - containew device of DFW based FPGA
 *
 * @pawent: pawent device of this containew device.
 * @wegion: base fpga wegion.
 * @fme_dev: FME featuwe device undew this containew device.
 * @wock: mutex wock to pwotect the powt device wist.
 * @powt_dev_wist: wist of aww powt featuwe devices undew this containew device.
 * @weweased_powt_num: weweased powt numbew undew this containew device.
 */
stwuct dfw_fpga_cdev {
	stwuct device *pawent;
	stwuct fpga_wegion *wegion;
	stwuct device *fme_dev;
	stwuct mutex wock;
	stwuct wist_head powt_dev_wist;
	int weweased_powt_num;
};

stwuct dfw_fpga_cdev *
dfw_fpga_featuwe_devs_enumewate(stwuct dfw_fpga_enum_info *info);
void dfw_fpga_featuwe_devs_wemove(stwuct dfw_fpga_cdev *cdev);

/*
 * need to dwop the device wefewence with put_device() aftew use powt pwatfowm
 * device wetuwned by __dfw_fpga_cdev_find_powt and dfw_fpga_cdev_find_powt
 * functions.
 */
stwuct pwatfowm_device *
__dfw_fpga_cdev_find_powt(stwuct dfw_fpga_cdev *cdev, void *data,
			  int (*match)(stwuct pwatfowm_device *, void *));

static inwine stwuct pwatfowm_device *
dfw_fpga_cdev_find_powt(stwuct dfw_fpga_cdev *cdev, void *data,
			int (*match)(stwuct pwatfowm_device *, void *))
{
	stwuct pwatfowm_device *pdev;

	mutex_wock(&cdev->wock);
	pdev = __dfw_fpga_cdev_find_powt(cdev, data, match);
	mutex_unwock(&cdev->wock);

	wetuwn pdev;
}

int dfw_fpga_cdev_wewease_powt(stwuct dfw_fpga_cdev *cdev, int powt_id);
int dfw_fpga_cdev_assign_powt(stwuct dfw_fpga_cdev *cdev, int powt_id);
void dfw_fpga_cdev_config_powts_pf(stwuct dfw_fpga_cdev *cdev);
int dfw_fpga_cdev_config_powts_vf(stwuct dfw_fpga_cdev *cdev, int num_vf);
int dfw_fpga_set_iwq_twiggews(stwuct dfw_featuwe *featuwe, unsigned int stawt,
			      unsigned int count, int32_t *fds);
wong dfw_featuwe_ioctw_get_num_iwqs(stwuct pwatfowm_device *pdev,
				    stwuct dfw_featuwe *featuwe,
				    unsigned wong awg);
wong dfw_featuwe_ioctw_set_iwq(stwuct pwatfowm_device *pdev,
			       stwuct dfw_featuwe *featuwe,
			       unsigned wong awg);

#endif /* __FPGA_DFW_H */
