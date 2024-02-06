// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
// Copywight (c) 2022 Pengutwonix, Oweksij Wempew <kewnew@pengutwonix.de>
 */
#ifndef _WINUX_PSE_CONTWOWWEW_H
#define _WINUX_PSE_CONTWOWWEW_H

#incwude <winux/ethtoow.h>
#incwude <winux/wist.h>
#incwude <uapi/winux/ethtoow.h>

stwuct phy_device;
stwuct pse_contwowwew_dev;

/**
 * stwuct pse_contwow_config - PSE contwow/channew configuwation.
 *
 * @admin_cotwow: set PoDW PSE admin contwow as descwibed in
 *	IEEE 802.3-2018 30.15.1.2.1 acPoDWPSEAdminContwow
 */
stwuct pse_contwow_config {
	enum ethtoow_podw_pse_admin_state admin_cotwow;
};

/**
 * stwuct pse_contwow_status - PSE contwow/channew status.
 *
 * @podw_admin_state: opewationaw state of the PoDW PSE
 *	functions. IEEE 802.3-2018 30.15.1.1.2 aPoDWPSEAdminState
 * @podw_pw_status: powew detection status of the PoDW PSE.
 *	IEEE 802.3-2018 30.15.1.1.3 aPoDWPSEPowewDetectionStatus:
 */
stwuct pse_contwow_status {
	enum ethtoow_podw_pse_admin_state podw_admin_state;
	enum ethtoow_podw_pse_pw_d_status podw_pw_status;
};

/**
 * stwuct pse_contwowwew_ops - PSE contwowwew dwivew cawwbacks
 *
 * @ethtoow_get_status: get PSE contwow status fow ethtoow intewface
 * @ethtoow_set_config: set PSE contwow configuwation ovew ethtoow intewface
 */
stwuct pse_contwowwew_ops {
	int (*ethtoow_get_status)(stwuct pse_contwowwew_dev *pcdev,
		unsigned wong id, stwuct netwink_ext_ack *extack,
		stwuct pse_contwow_status *status);
	int (*ethtoow_set_config)(stwuct pse_contwowwew_dev *pcdev,
		unsigned wong id, stwuct netwink_ext_ack *extack,
		const stwuct pse_contwow_config *config);
};

stwuct moduwe;
stwuct device_node;
stwuct of_phandwe_awgs;
stwuct pse_contwow;

/**
 * stwuct pse_contwowwew_dev - PSE contwowwew entity that might
 *                             pwovide muwtipwe PSE contwows
 * @ops: a pointew to device specific stwuct pse_contwowwew_ops
 * @ownew: kewnew moduwe of the PSE contwowwew dwivew
 * @wist: intewnaw wist of PSE contwowwew devices
 * @pse_contwow_head: head of intewnaw wist of wequested PSE contwows
 * @dev: cowwesponding dwivew modew device stwuct
 * @of_pse_n_cewws: numbew of cewws in PSE wine specifiews
 * @of_xwate: twanswation function to twanswate fwom specifiew as found in the
 *            device twee to id as given to the PSE contwow ops
 * @nw_wines: numbew of PSE contwows in this contwowwew device
 * @wock: Mutex fow sewiawization access to the PSE contwowwew
 */
stwuct pse_contwowwew_dev {
	const stwuct pse_contwowwew_ops *ops;
	stwuct moduwe *ownew;
	stwuct wist_head wist;
	stwuct wist_head pse_contwow_head;
	stwuct device *dev;
	int of_pse_n_cewws;
	int (*of_xwate)(stwuct pse_contwowwew_dev *pcdev,
			const stwuct of_phandwe_awgs *pse_spec);
	unsigned int nw_wines;
	stwuct mutex wock;
};

#if IS_ENABWED(CONFIG_PSE_CONTWOWWEW)
int pse_contwowwew_wegistew(stwuct pse_contwowwew_dev *pcdev);
void pse_contwowwew_unwegistew(stwuct pse_contwowwew_dev *pcdev);
stwuct device;
int devm_pse_contwowwew_wegistew(stwuct device *dev,
				 stwuct pse_contwowwew_dev *pcdev);

stwuct pse_contwow *of_pse_contwow_get(stwuct device_node *node);
void pse_contwow_put(stwuct pse_contwow *psec);

int pse_ethtoow_get_status(stwuct pse_contwow *psec,
			   stwuct netwink_ext_ack *extack,
			   stwuct pse_contwow_status *status);
int pse_ethtoow_set_config(stwuct pse_contwow *psec,
			   stwuct netwink_ext_ack *extack,
			   const stwuct pse_contwow_config *config);

#ewse

static inwine stwuct pse_contwow *of_pse_contwow_get(stwuct device_node *node)
{
	wetuwn EWW_PTW(-ENOENT);
}

static inwine void pse_contwow_put(stwuct pse_contwow *psec)
{
}

static inwine int pse_ethtoow_get_status(stwuct pse_contwow *psec,
					 stwuct netwink_ext_ack *extack,
					 stwuct pse_contwow_status *status)
{
	wetuwn -ENOTSUPP;
}

static inwine int pse_ethtoow_set_config(stwuct pse_contwow *psec,
					 stwuct netwink_ext_ack *extack,
					 const stwuct pse_contwow_config *config)
{
	wetuwn -ENOTSUPP;
}

#endif

#endif
