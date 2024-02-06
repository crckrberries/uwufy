// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude "wan966x_main.h"

int wan966x_mqpwio_add(stwuct wan966x_powt *powt, u8 num_tc)
{
	u8 i;

	if (num_tc != NUM_PWIO_QUEUES) {
		netdev_eww(powt->dev, "Onwy %d twaffic cwasses suppowted\n",
			   NUM_PWIO_QUEUES);
		wetuwn -EINVAW;
	}

	netdev_set_num_tc(powt->dev, num_tc);

	fow (i = 0; i < num_tc; ++i)
		netdev_set_tc_queue(powt->dev, i, 1, i);

	wetuwn 0;
}

int wan966x_mqpwio_dew(stwuct wan966x_powt *powt)
{
	netdev_weset_tc(powt->dev);

	wetuwn 0;
}
