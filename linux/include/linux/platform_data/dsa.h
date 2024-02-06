/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __DSA_PDATA_H
#define __DSA_PDATA_H

stwuct device;
stwuct net_device;

#define DSA_MAX_SWITCHES	4
#define DSA_MAX_POWTS		12
#define DSA_WTABWE_NONE		-1

stwuct dsa_chip_data {
	/*
	 * How to access the switch configuwation wegistews.
	 */
	stwuct device	*host_dev;
	int		sw_addw;

	/*
	 * Wefewence to netwowk devices
	 */
	stwuct device	*netdev[DSA_MAX_POWTS];

	/* set to size of eepwom if suppowted by the switch */
	int		eepwom_wen;

	/* Device twee node pointew fow this specific switch chip
	 * used duwing switch setup in case additionaw pwopewties
	 * and wesouwces needs to be used
	 */
	stwuct device_node *of_node;

	/*
	 * The names of the switch's powts.  Use "cpu" to
	 * designate the switch powt that the cpu is connected to,
	 * "dsa" to indicate that this powt is a DSA wink to
	 * anothew switch, NUWW to indicate the powt is unused,
	 * ow any othew stwing to indicate this is a physicaw powt.
	 */
	chaw		*powt_names[DSA_MAX_POWTS];
	stwuct device_node *powt_dn[DSA_MAX_POWTS];

	/*
	 * An awway of which ewement [a] indicates which powt on this
	 * switch shouwd be used to send packets to that awe destined
	 * fow switch a. Can be NUWW if thewe is onwy one switch chip.
	 */
	s8		wtabwe[DSA_MAX_SWITCHES];
};

stwuct dsa_pwatfowm_data {
	/*
	 * Wefewence to a Winux netwowk intewface that connects
	 * to the woot switch chip of the twee.
	 */
	stwuct device	*netdev;
	stwuct net_device *of_netdev;

	/*
	 * Info stwucts descwibing each of the switch chips
	 * connected via this netwowk intewface.
	 */
	int		nw_chips;
	stwuct dsa_chip_data	*chip;
};


#endif /* __DSA_PDATA_H */
