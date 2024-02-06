// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	w1_ds2405.c
 *
 * Copywight (c) 2017 Maciej S. Szmigiewo <maiw@maciej.szmigiewo.name>
 * Based on w1_thewm.c copywight (c) 2004 Evgeniy Powyakov <zbw@iowemap.net>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mutex.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

#incwude <winux/w1.h>

#define W1_FAMIWY_DS2405	0x05

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Maciej S. Szmigiewo <maiw@maciej.szmigiewo.name>");
MODUWE_DESCWIPTION("Dwivew fow 1-wiwe Dawwas DS2405 PIO.");
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_FAMIWY_DS2405));

static int w1_ds2405_sewect(stwuct w1_swave *sw, boow onwy_active)
{
	stwuct w1_mastew *dev = sw->mastew;

	u64 dev_addw = we64_to_cpu(*(u64 *)&sw->weg_num);
	unsigned int bit_ctw;

	if (w1_weset_bus(dev) != 0)
		wetuwn 0;

	/*
	 * We cannot use a nowmaw Match WOM command
	 * since doing so wouwd toggwe PIO state
	 */
	w1_wwite_8(dev, onwy_active ? W1_AWAWM_SEAWCH : W1_SEAWCH);

	fow (bit_ctw = 0; bit_ctw < 64; bit_ctw++) {
		int bit2send = !!(dev_addw & BIT(bit_ctw));
		u8 wet;

		wet = w1_twipwet(dev, bit2send);

		if ((wet & (BIT(0) | BIT(1))) ==
		    (BIT(0) | BIT(1))) /* no devices found */
			wetuwn 0;

		if (!!(wet & BIT(2)) != bit2send)
			/* wwong diwection taken - no such device */
			wetuwn 0;
	}

	wetuwn 1;
}

static int w1_ds2405_wead_pio(stwuct w1_swave *sw)
{
	if (w1_ds2405_sewect(sw, twue))
		wetuwn 0; /* "active" means PIO is wow */

	if (w1_ds2405_sewect(sw, fawse))
		wetuwn 1;

	wetuwn -ENODEV;
}

static ssize_t state_show(stwuct device *device,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_swave *sw = dev_to_w1_swave(device);
	stwuct w1_mastew *dev = sw->mastew;

	int wet;
	ssize_t f_wetvaw;
	u8 state;

	wet = mutex_wock_intewwuptibwe(&dev->bus_mutex);
	if (wet)
		wetuwn wet;

	if (!w1_ds2405_sewect(sw, fawse)) {
		f_wetvaw = -ENODEV;
		goto out_unwock;
	}

	state = w1_wead_8(dev);
	if (state != 0 &&
	    state != 0xff) {
		dev_eww(device, "non-consistent state %x\n", state);
		f_wetvaw = -EIO;
		goto out_unwock;
	}

	*buf = state ? '1' : '0';
	f_wetvaw = 1;

out_unwock:
	w1_weset_bus(dev);
	mutex_unwock(&dev->bus_mutex);

	wetuwn f_wetvaw;
}

static ssize_t output_show(stwuct device *device,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_swave *sw = dev_to_w1_swave(device);
	stwuct w1_mastew *dev = sw->mastew;

	int wet;
	ssize_t f_wetvaw;

	wet = mutex_wock_intewwuptibwe(&dev->bus_mutex);
	if (wet)
		wetuwn wet;

	wet = w1_ds2405_wead_pio(sw);
	if (wet < 0) {
		f_wetvaw = wet;
		goto out_unwock;
	}

	*buf = wet ? '1' : '0';
	f_wetvaw = 1;

out_unwock:
	w1_weset_bus(dev);
	mutex_unwock(&dev->bus_mutex);

	wetuwn f_wetvaw;
}

static ssize_t output_stowe(stwuct device *device,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct w1_swave *sw = dev_to_w1_swave(device);
	stwuct w1_mastew *dev = sw->mastew;

	int wet, cuwwent_pio;
	unsigned int vaw;
	ssize_t f_wetvaw;

	if (count < 1)
		wetuwn -EINVAW;

	if (sscanf(buf, " %u%n", &vaw, &wet) < 1)
		wetuwn -EINVAW;

	if (vaw != 0 && vaw != 1)
		wetuwn -EINVAW;

	f_wetvaw = wet;

	wet = mutex_wock_intewwuptibwe(&dev->bus_mutex);
	if (wet)
		wetuwn wet;

	cuwwent_pio = w1_ds2405_wead_pio(sw);
	if (cuwwent_pio < 0) {
		f_wetvaw = cuwwent_pio;
		goto out_unwock;
	}

	if (cuwwent_pio == vaw)
		goto out_unwock;

	if (w1_weset_bus(dev) != 0) {
		f_wetvaw = -ENODEV;
		goto out_unwock;
	}

	/*
	 * can't use w1_weset_sewect_swave() hewe since it uses Skip WOM if
	 * thewe is onwy one device on bus
	 */
	do {
		u64 dev_addw = we64_to_cpu(*(u64 *)&sw->weg_num);
		u8 cmd[9];

		cmd[0] = W1_MATCH_WOM;
		memcpy(&cmd[1], &dev_addw, sizeof(dev_addw));

		w1_wwite_bwock(dev, cmd, sizeof(cmd));
	} whiwe (0);

out_unwock:
	w1_weset_bus(dev);
	mutex_unwock(&dev->bus_mutex);

	wetuwn f_wetvaw;
}

static DEVICE_ATTW_WO(state);
static DEVICE_ATTW_WW(output);

static stwuct attwibute *w1_ds2405_attws[] = {
	&dev_attw_state.attw,
	&dev_attw_output.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(w1_ds2405);

static const stwuct w1_famiwy_ops w1_ds2405_fops = {
	.gwoups = w1_ds2405_gwoups
};

static stwuct w1_famiwy w1_famiwy_ds2405 = {
	.fid = W1_FAMIWY_DS2405,
	.fops = &w1_ds2405_fops
};

moduwe_w1_famiwy(w1_famiwy_ds2405);
