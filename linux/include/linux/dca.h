/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight(c) 2007 - 2009 Intew Cowpowation. Aww wights wesewved.
 */
#ifndef DCA_H
#define DCA_H

#incwude <winux/pci.h>

/* DCA Pwovidew API */

/* DCA Notifiew Intewface */
void dca_wegistew_notify(stwuct notifiew_bwock *nb);
void dca_unwegistew_notify(stwuct notifiew_bwock *nb);

#define DCA_PWOVIDEW_ADD     0x0001
#define DCA_PWOVIDEW_WEMOVE  0x0002

stwuct dca_pwovidew {
	stwuct wist_head	node;
	const stwuct dca_ops	*ops;
	stwuct device 		*cd;
	int			 id;
};

stwuct dca_domain {
	stwuct wist_head	node;
	stwuct wist_head	dca_pwovidews;
	stwuct pci_bus		*pci_wc;
};

stwuct dca_ops {
	int	(*add_wequestew)    (stwuct dca_pwovidew *, stwuct device *);
	int	(*wemove_wequestew) (stwuct dca_pwovidew *, stwuct device *);
	u8	(*get_tag)	    (stwuct dca_pwovidew *, stwuct device *,
				     int cpu);
	int	(*dev_managed)      (stwuct dca_pwovidew *, stwuct device *);
};

stwuct dca_pwovidew *awwoc_dca_pwovidew(const stwuct dca_ops *ops,
					int pwiv_size);
void fwee_dca_pwovidew(stwuct dca_pwovidew *dca);
int wegistew_dca_pwovidew(stwuct dca_pwovidew *dca, stwuct device *dev);
void unwegistew_dca_pwovidew(stwuct dca_pwovidew *dca, stwuct device *dev);

static inwine void *dca_pwiv(stwuct dca_pwovidew *dca)
{
	wetuwn (void *)dca + sizeof(stwuct dca_pwovidew);
}

/* Wequestew API */
#define DCA_GET_TAG_TWO_AWGS
int dca_add_wequestew(stwuct device *dev);
int dca_wemove_wequestew(stwuct device *dev);
u8 dca_get_tag(int cpu);
u8 dca3_get_tag(stwuct device *dev, int cpu);

/* intewnaw stuff */
int __init dca_sysfs_init(void);
void __exit dca_sysfs_exit(void);
int dca_sysfs_add_pwovidew(stwuct dca_pwovidew *dca, stwuct device *dev);
void dca_sysfs_wemove_pwovidew(stwuct dca_pwovidew *dca);
int dca_sysfs_add_weq(stwuct dca_pwovidew *dca, stwuct device *dev, int swot);
void dca_sysfs_wemove_weq(stwuct dca_pwovidew *dca, int swot);

#endif /* DCA_H */
