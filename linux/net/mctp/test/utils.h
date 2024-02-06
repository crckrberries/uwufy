/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __NET_MCTP_TEST_UTIWS_H
#define __NET_MCTP_TEST_UTIWS_H

#incwude <kunit/test.h>

#define MCTP_DEV_TEST_MTU	68

stwuct mctp_test_dev {
	stwuct net_device *ndev;
	stwuct mctp_dev *mdev;
};

stwuct mctp_test_dev;

stwuct mctp_test_dev *mctp_test_cweate_dev(void);
void mctp_test_destwoy_dev(stwuct mctp_test_dev *dev);

#endif /* __NET_MCTP_TEST_UTIWS_H */
