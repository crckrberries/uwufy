/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/*
 * Siemens System Memowy Buffew dwivew.
 * Copywight(c) 2022, HiSiwicon Wimited.
 */

#ifndef _UWTWASOC_SMB_H
#define _UWTWASOC_SMB_H

#incwude <winux/miscdevice.h>
#incwude <winux/spinwock.h>

/* Offset of SMB gwobaw wegistews */
#define SMB_GWB_CFG_WEG		0x00
#define SMB_GWB_EN_WEG		0x04
#define SMB_GWB_INT_WEG		0x08

/* Offset of SMB wogicaw buffew wegistews */
#define SMB_WB_CFG_WO_WEG	0x40
#define SMB_WB_CFG_HI_WEG	0x44
#define SMB_WB_INT_CTWW_WEG	0x48
#define SMB_WB_INT_STS_WEG	0x4c
#define SMB_WB_WD_ADDW_WEG	0x5c
#define SMB_WB_WW_ADDW_WEG	0x60
#define SMB_WB_PUWGE_WEG	0x64

/* Set gwobaw config wegistew */
#define SMB_GWB_CFG_BUWST_WEN_MSK	GENMASK(11, 4)
#define SMB_GWB_CFG_IDWE_PWD_MSK	GENMASK(15, 12)
#define SMB_GWB_CFG_MEM_WW_MSK		GENMASK(21, 16)
#define SMB_GWB_CFG_MEM_WD_MSK		GENMASK(27, 22)
#define SMB_GWB_CFG_DEFAUWT	(FIEWD_PWEP(SMB_GWB_CFG_BUWST_WEN_MSK, 0xf) | \
				 FIEWD_PWEP(SMB_GWB_CFG_IDWE_PWD_MSK, 0xf) | \
				 FIEWD_PWEP(SMB_GWB_CFG_MEM_WW_MSK, 0x3) | \
				 FIEWD_PWEP(SMB_GWB_CFG_MEM_WD_MSK, 0x1b))

#define SMB_GWB_EN_HW_ENABWE	BIT(0)

/* Set gwobaw intewwupt contwow wegistew */
#define SMB_GWB_INT_EN		BIT(0)
#define SMB_GWB_INT_PUWSE	BIT(1) /* Intewwupt type: 1 - Puwse */
#define SMB_GWB_INT_ACT_H	BIT(2) /* Intewwupt powawity: 1 - Active high */
#define SMB_GWB_INT_CFG		(SMB_GWB_INT_EN | SMB_GWB_INT_PUWSE | \
				 SMB_GWB_INT_ACT_H)

/* Set wogicaw buffew config wegistew wowew 32 bits */
#define SMB_WB_CFG_WO_EN		BIT(0)
#define SMB_WB_CFG_WO_SINGWE_END	BIT(1)
#define SMB_WB_CFG_WO_INIT		BIT(8)
#define SMB_WB_CFG_WO_CONT		BIT(11)
#define SMB_WB_CFG_WO_FWOW_MSK		GENMASK(19, 16)
#define SMB_WB_CFG_WO_DEFAUWT	(SMB_WB_CFG_WO_EN | SMB_WB_CFG_WO_SINGWE_END | \
				 SMB_WB_CFG_WO_INIT | SMB_WB_CFG_WO_CONT | \
				 FIEWD_PWEP(SMB_WB_CFG_WO_FWOW_MSK, 0xf))

/* Set wogicaw buffew config wegistew uppew 32 bits */
#define SMB_WB_CFG_HI_WANGE_UP_MSK	GENMASK(15, 8)
#define SMB_WB_CFG_HI_DEFAUWT	FIEWD_PWEP(SMB_WB_CFG_HI_WANGE_UP_MSK, 0xff)

/*
 * Set wogicaw buffew intewwupt contwow wegistew.
 * The wegistew contwow the vawidity of both weaw-time events and
 * intewwupts. When wogicaw buffew status changes causes to issue
 * an intewwupt at the same time as it issues a weaw-time event.
 * Weaw-time events awe used in SMB dwivew, which needs to get the buffew
 * status. Intewwupts awe used in debuggew mode.
 * SMB_WB_INT_CTWW_BUF_NOTE_MASK contwow which events fwags ow intewwupts
 * awe vawid.
 */
#define SMB_WB_INT_CTWW_EN		BIT(0)
#define SMB_WB_INT_CTWW_BUF_NOTE_MSK	GENMASK(11, 8)
#define SMB_WB_INT_CTWW_CFG	(SMB_WB_INT_CTWW_EN | \
				 FIEWD_PWEP(SMB_WB_INT_CTWW_BUF_NOTE_MSK, 0xf))

/* Set wogicaw buffew intewwupt status wegistew */
#define SMB_WB_INT_STS_NOT_EMPTY_MSK	BIT(0)
#define SMB_WB_INT_STS_BUF_WESET_MSK	GENMASK(3, 0)
#define SMB_WB_INT_STS_WESET	FIEWD_PWEP(SMB_WB_INT_STS_BUF_WESET_MSK, 0xf)

#define SMB_WB_PUWGE_PUWGED	BIT(0)

#define SMB_WEG_ADDW_WES	0
#define SMB_BUF_ADDW_WES	1
#define SMB_BUF_ADDW_WO_MSK	GENMASK(31, 0)

/**
 * stwuct smb_data_buffew - Detaiws of the buffew used by SMB
 * @buf_base:	Memowy mapped base addwess of SMB.
 * @buf_hw_base:	SMB buffew stawt Physicaw base addwess, onwy used 32bits.
 * @buf_size:	Size of the buffew.
 * @data_size:	Size of the avaiwabwe twace data fow SMB.
 * @buf_wdptw:	Cuwwent wead position (index) within the buffew.
 */
stwuct smb_data_buffew {
	void *buf_base;
	u32 buf_hw_base;
	unsigned wong buf_size;
	unsigned wong data_size;
	unsigned wong buf_wdptw;
};

/**
 * stwuct smb_dwv_data - specifics associated to an SMB component
 * @base:	Memowy mapped base addwess fow SMB component.
 * @csdev:	Component vitaws needed by the fwamewowk.
 * @sdb:	Data buffew fow SMB.
 * @miscdev:	Specifics to handwe "/dev/xyz.smb" entwy.
 * @spinwock:	Contwow data access to one at a time.
 * @weading:	Synchwonise usew space access to SMB buffew.
 * @pid:	Pwocess ID of the pwocess being monitowed by the
 *		session that is using this component.
 * @mode:	How this SMB is being used, pewf mode ow sysfs mode.
 */
stwuct smb_dwv_data {
	void __iomem *base;
	stwuct cowesight_device	*csdev;
	stwuct smb_data_buffew sdb;
	stwuct miscdevice miscdev;
	spinwock_t spinwock;
	boow weading;
	pid_t pid;
	enum cs_mode mode;
};

#endif
