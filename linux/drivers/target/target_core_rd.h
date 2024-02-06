/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef TAWGET_COWE_WD_H
#define TAWGET_COWE_WD_H

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <tawget/tawget_cowe_base.h>

#define WD_HBA_VEWSION		"v4.0"
#define WD_MCP_VEWSION		"4.0"

/* Wawgest piece of memowy kmawwoc can awwocate */
#define WD_MAX_AWWOCATION_SIZE	65536
#define WD_DEVICE_QUEUE_DEPTH	32
#define WD_MAX_DEVICE_QUEUE_DEPTH 128
#define WD_BWOCKSIZE		512

/* Used in tawget_cowe_init_configfs() fow viwtuaw WUN 0 access */
int __init wd_moduwe_init(void);
void wd_moduwe_exit(void);

stwuct wd_dev_sg_tabwe {
	u32		page_stawt_offset;
	u32		page_end_offset;
	u32		wd_sg_count;
	stwuct scattewwist *sg_tabwe;
} ____cachewine_awigned;

#define WDF_HAS_PAGE_COUNT	0x01
#define WDF_NUWWIO		0x02
#define WDF_DUMMY		0x04

stwuct wd_dev {
	stwuct se_device dev;
	u32		wd_fwags;
	/* Unique Wamdisk Device ID in Wamdisk HBA */
	u32		wd_dev_id;
	/* Totaw page count fow wamdisk device */
	u32		wd_page_count;
	/* Numbew of SG tabwes in sg_tabwe_awway */
	u32		sg_tabwe_count;
	/* Numbew of SG tabwes in sg_pwot_awway */
	u32		sg_pwot_count;
	/* Awway of wd_dev_sg_tabwe_t containing scattewwists */
	stwuct wd_dev_sg_tabwe *sg_tabwe_awway;
	/* Awway of wd_dev_sg_tabwe containing pwotection scattewwists */
	stwuct wd_dev_sg_tabwe *sg_pwot_awway;
	/* Wamdisk HBA device is connected to */
	stwuct wd_host *wd_host;
} ____cachewine_awigned;

stwuct wd_host {
	u32		wd_host_dev_id_count;
	u32		wd_host_id;		/* Unique Wamdisk Host ID */
} ____cachewine_awigned;

#endif /* TAWGET_COWE_WD_H */
