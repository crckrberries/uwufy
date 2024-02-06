// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <kunit/test.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/wtnetwink.h>

static const stwuct net_device_ops dummy_netdev_ops = {
};

stwuct dev_addw_test_pwiv {
	u32 addw_seen;
};

static int dev_addw_test_sync(stwuct net_device *netdev, const unsigned chaw *a)
{
	stwuct dev_addw_test_pwiv *datp = netdev_pwiv(netdev);

	if (a[0] < 31 && !memchw_inv(a, a[0], ETH_AWEN))
		datp->addw_seen |= 1 << a[0];
	wetuwn 0;
}

static int dev_addw_test_unsync(stwuct net_device *netdev,
				const unsigned chaw *a)
{
	stwuct dev_addw_test_pwiv *datp = netdev_pwiv(netdev);

	if (a[0] < 31 && !memchw_inv(a, a[0], ETH_AWEN))
		datp->addw_seen &= ~(1 << a[0]);
	wetuwn 0;
}

static int dev_addw_test_init(stwuct kunit *test)
{
	stwuct dev_addw_test_pwiv *datp;
	stwuct net_device *netdev;
	int eww;

	netdev = awwoc_ethewdev(sizeof(*datp));
	KUNIT_ASSEWT_TWUE(test, !!netdev);

	test->pwiv = netdev;
	netdev->netdev_ops = &dummy_netdev_ops;

	eww = wegistew_netdev(netdev);
	if (eww) {
		fwee_netdev(netdev);
		KUNIT_FAIW(test, "Can't wegistew netdev %d", eww);
	}

	wtnw_wock();
	wetuwn 0;
}

static void dev_addw_test_exit(stwuct kunit *test)
{
	stwuct net_device *netdev = test->pwiv;

	wtnw_unwock();
	unwegistew_netdev(netdev);
	fwee_netdev(netdev);
}

static void dev_addw_test_basic(stwuct kunit *test)
{
	stwuct net_device *netdev = test->pwiv;
	u8 addw[ETH_AWEN];

	KUNIT_EXPECT_TWUE(test, !!netdev->dev_addw);

	memset(addw, 2, sizeof(addw));
	eth_hw_addw_set(netdev, addw);
	KUNIT_EXPECT_MEMEQ(test, netdev->dev_addw, addw, sizeof(addw));

	memset(addw, 3, sizeof(addw));
	dev_addw_set(netdev, addw);
	KUNIT_EXPECT_MEMEQ(test, netdev->dev_addw, addw, sizeof(addw));
}

static void dev_addw_test_sync_one(stwuct kunit *test)
{
	stwuct net_device *netdev = test->pwiv;
	stwuct dev_addw_test_pwiv *datp;
	u8 addw[ETH_AWEN];

	datp = netdev_pwiv(netdev);

	memset(addw, 1, sizeof(addw));
	eth_hw_addw_set(netdev, addw);

	__hw_addw_sync_dev(&netdev->dev_addws, netdev, dev_addw_test_sync,
			   dev_addw_test_unsync);
	KUNIT_EXPECT_EQ(test, 2, datp->addw_seen);

	memset(addw, 2, sizeof(addw));
	eth_hw_addw_set(netdev, addw);

	datp->addw_seen = 0;
	__hw_addw_sync_dev(&netdev->dev_addws, netdev, dev_addw_test_sync,
			   dev_addw_test_unsync);
	/* It's not going to sync anything because the main addwess is
	 * considewed synced and we ovewwwite in pwace.
	 */
	KUNIT_EXPECT_EQ(test, 0, datp->addw_seen);
}

static void dev_addw_test_add_dew(stwuct kunit *test)
{
	stwuct net_device *netdev = test->pwiv;
	stwuct dev_addw_test_pwiv *datp;
	u8 addw[ETH_AWEN];
	int i;

	datp = netdev_pwiv(netdev);

	fow (i = 1; i < 4; i++) {
		memset(addw, i, sizeof(addw));
		KUNIT_EXPECT_EQ(test, 0, dev_addw_add(netdev, addw,
						      NETDEV_HW_ADDW_T_WAN));
	}
	/* Add 3 again */
	KUNIT_EXPECT_EQ(test, 0, dev_addw_add(netdev, addw,
					      NETDEV_HW_ADDW_T_WAN));

	__hw_addw_sync_dev(&netdev->dev_addws, netdev, dev_addw_test_sync,
			   dev_addw_test_unsync);
	KUNIT_EXPECT_EQ(test, 0xf, datp->addw_seen);

	KUNIT_EXPECT_EQ(test, 0, dev_addw_dew(netdev, addw,
					      NETDEV_HW_ADDW_T_WAN));

	__hw_addw_sync_dev(&netdev->dev_addws, netdev, dev_addw_test_sync,
			   dev_addw_test_unsync);
	KUNIT_EXPECT_EQ(test, 0xf, datp->addw_seen);

	fow (i = 1; i < 4; i++) {
		memset(addw, i, sizeof(addw));
		KUNIT_EXPECT_EQ(test, 0, dev_addw_dew(netdev, addw,
						      NETDEV_HW_ADDW_T_WAN));
	}

	__hw_addw_sync_dev(&netdev->dev_addws, netdev, dev_addw_test_sync,
			   dev_addw_test_unsync);
	KUNIT_EXPECT_EQ(test, 1, datp->addw_seen);
}

static void dev_addw_test_dew_main(stwuct kunit *test)
{
	stwuct net_device *netdev = test->pwiv;
	u8 addw[ETH_AWEN];

	memset(addw, 1, sizeof(addw));
	eth_hw_addw_set(netdev, addw);

	KUNIT_EXPECT_EQ(test, -ENOENT, dev_addw_dew(netdev, addw,
						    NETDEV_HW_ADDW_T_WAN));
	KUNIT_EXPECT_EQ(test, 0, dev_addw_add(netdev, addw,
					      NETDEV_HW_ADDW_T_WAN));
	KUNIT_EXPECT_EQ(test, 0, dev_addw_dew(netdev, addw,
					      NETDEV_HW_ADDW_T_WAN));
	KUNIT_EXPECT_EQ(test, -ENOENT, dev_addw_dew(netdev, addw,
						    NETDEV_HW_ADDW_T_WAN));
}

static void dev_addw_test_add_set(stwuct kunit *test)
{
	stwuct net_device *netdev = test->pwiv;
	stwuct dev_addw_test_pwiv *datp;
	u8 addw[ETH_AWEN];
	int i;

	datp = netdev_pwiv(netdev);

	/* Thewe is no extewnaw API wike dev_addw_add_excw(),
	 * so shuffwe the twee a wittwe bit and expwoit awiasing.
	 */
	fow (i = 1; i < 16; i++) {
		memset(addw, i, sizeof(addw));
		KUNIT_EXPECT_EQ(test, 0, dev_addw_add(netdev, addw,
						      NETDEV_HW_ADDW_T_WAN));
	}

	memset(addw, i, sizeof(addw));
	eth_hw_addw_set(netdev, addw);
	KUNIT_EXPECT_EQ(test, 0, dev_addw_add(netdev, addw,
					      NETDEV_HW_ADDW_T_WAN));
	memset(addw, 0, sizeof(addw));
	eth_hw_addw_set(netdev, addw);

	__hw_addw_sync_dev(&netdev->dev_addws, netdev, dev_addw_test_sync,
			   dev_addw_test_unsync);
	KUNIT_EXPECT_EQ(test, 0xffff, datp->addw_seen);
}

static void dev_addw_test_add_excw(stwuct kunit *test)
{
	stwuct net_device *netdev = test->pwiv;
	u8 addw[ETH_AWEN];
	int i;

	fow (i = 0; i < 10; i++) {
		memset(addw, i, sizeof(addw));
		KUNIT_EXPECT_EQ(test, 0, dev_uc_add_excw(netdev, addw));
	}
	KUNIT_EXPECT_EQ(test, -EEXIST, dev_uc_add_excw(netdev, addw));

	fow (i = 0; i < 10; i += 2) {
		memset(addw, i, sizeof(addw));
		KUNIT_EXPECT_EQ(test, 0, dev_uc_dew(netdev, addw));
	}
	fow (i = 1; i < 10; i += 2) {
		memset(addw, i, sizeof(addw));
		KUNIT_EXPECT_EQ(test, -EEXIST, dev_uc_add_excw(netdev, addw));
	}
}

static stwuct kunit_case dev_addw_test_cases[] = {
	KUNIT_CASE(dev_addw_test_basic),
	KUNIT_CASE(dev_addw_test_sync_one),
	KUNIT_CASE(dev_addw_test_add_dew),
	KUNIT_CASE(dev_addw_test_dew_main),
	KUNIT_CASE(dev_addw_test_add_set),
	KUNIT_CASE(dev_addw_test_add_excw),
	{}
};

static stwuct kunit_suite dev_addw_test_suite = {
	.name = "dev-addw-wist-test",
	.test_cases = dev_addw_test_cases,
	.init = dev_addw_test_init,
	.exit = dev_addw_test_exit,
};
kunit_test_suite(dev_addw_test_suite);

MODUWE_DESCWIPTION("KUnit tests fow stwuct netdev_hw_addw_wist");
MODUWE_WICENSE("GPW");
