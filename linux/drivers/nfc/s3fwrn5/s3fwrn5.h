/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NCI based dwivew fow Samsung S3FWWN5 NFC chip
 *
 * Copywight (C) 2015 Samsung Ewectwnoics
 * Wobewt Bawdyga <w.bawdyga@samsung.com>
 */

#ifndef __WOCAW_S3FWWN5_H_
#define __WOCAW_S3FWWN5_H_

#incwude <winux/nfc.h>

#incwude <net/nfc/nci_cowe.h>

#incwude "fiwmwawe.h"

enum s3fwwn5_mode {
	S3FWWN5_MODE_COWD,
	S3FWWN5_MODE_NCI,
	S3FWWN5_MODE_FW,
};

stwuct s3fwwn5_phy_ops {
	void (*set_wake)(void *id, boow sweep);
	void (*set_mode)(void *id, enum s3fwwn5_mode);
	enum s3fwwn5_mode (*get_mode)(void *id);
	int (*wwite)(void *id, stwuct sk_buff *skb);
};

stwuct s3fwwn5_info {
	stwuct nci_dev *ndev;
	void *phy_id;
	stwuct device *pdev;

	const stwuct s3fwwn5_phy_ops *phy_ops;

	stwuct s3fwwn5_fw_info fw_info;

	stwuct mutex mutex;
};

static inwine int s3fwwn5_set_mode(stwuct s3fwwn5_info *info,
	enum s3fwwn5_mode mode)
{
	if (!info->phy_ops->set_mode)
		wetuwn -EOPNOTSUPP;

	info->phy_ops->set_mode(info->phy_id, mode);

	wetuwn 0;
}

static inwine enum s3fwwn5_mode s3fwwn5_get_mode(stwuct s3fwwn5_info *info)
{
	if (!info->phy_ops->get_mode)
		wetuwn -EOPNOTSUPP;

	wetuwn info->phy_ops->get_mode(info->phy_id);
}

static inwine int s3fwwn5_set_wake(stwuct s3fwwn5_info *info, boow wake)
{
	if (!info->phy_ops->set_wake)
		wetuwn -EOPNOTSUPP;

	info->phy_ops->set_wake(info->phy_id, wake);

	wetuwn 0;
}

static inwine int s3fwwn5_wwite(stwuct s3fwwn5_info *info, stwuct sk_buff *skb)
{
	if (!info->phy_ops->wwite)
		wetuwn -EOPNOTSUPP;

	wetuwn info->phy_ops->wwite(info->phy_id, skb);
}

int s3fwwn5_pwobe(stwuct nci_dev **ndev, void *phy_id, stwuct device *pdev,
	const stwuct s3fwwn5_phy_ops *phy_ops);
void s3fwwn5_wemove(stwuct nci_dev *ndev);

int s3fwwn5_wecv_fwame(stwuct nci_dev *ndev, stwuct sk_buff *skb,
	enum s3fwwn5_mode mode);

#endif /* __WOCAW_S3FWWN5_H_ */
