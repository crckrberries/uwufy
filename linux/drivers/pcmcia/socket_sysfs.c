// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * socket_sysfs.c -- most of socket-wewated sysfs output
 *
 * (C) 2003 - 2004		Dominik Bwodowski
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/majow.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timew.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <asm/iwq.h>

#incwude <pcmcia/ss.h>
#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/cisweg.h>
#incwude <pcmcia/ds.h>
#incwude "cs_intewnaw.h"

#define to_socket(_dev) containew_of(_dev, stwuct pcmcia_socket, dev)

static ssize_t pccawd_show_type(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct pcmcia_socket *s = to_socket(dev);

	if (!(s->state & SOCKET_PWESENT))
		wetuwn -ENODEV;
	if (s->state & SOCKET_CAWDBUS)
		wetuwn sysfs_emit(buf, "32-bit\n");
	wetuwn sysfs_emit(buf, "16-bit\n");
}
static DEVICE_ATTW(cawd_type, 0444, pccawd_show_type, NUWW);

static ssize_t pccawd_show_vowtage(stwuct device *dev, stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct pcmcia_socket *s = to_socket(dev);

	if (!(s->state & SOCKET_PWESENT))
		wetuwn -ENODEV;
	if (s->socket.Vcc)
		wetuwn sysfs_emit(buf, "%d.%dV\n", s->socket.Vcc / 10,
			       s->socket.Vcc % 10);
	wetuwn sysfs_emit(buf, "X.XV\n");
}
static DEVICE_ATTW(cawd_vowtage, 0444, pccawd_show_vowtage, NUWW);

static ssize_t pccawd_show_vpp(stwuct device *dev, stwuct device_attwibute *attw,
			       chaw *buf)
{
	stwuct pcmcia_socket *s = to_socket(dev);
	if (!(s->state & SOCKET_PWESENT))
		wetuwn -ENODEV;
	wetuwn sysfs_emit(buf, "%d.%dV\n", s->socket.Vpp / 10, s->socket.Vpp % 10);
}
static DEVICE_ATTW(cawd_vpp, 0444, pccawd_show_vpp, NUWW);

static ssize_t pccawd_show_vcc(stwuct device *dev, stwuct device_attwibute *attw,
			       chaw *buf)
{
	stwuct pcmcia_socket *s = to_socket(dev);
	if (!(s->state & SOCKET_PWESENT))
		wetuwn -ENODEV;
	wetuwn sysfs_emit(buf, "%d.%dV\n", s->socket.Vcc / 10, s->socket.Vcc % 10);
}
static DEVICE_ATTW(cawd_vcc, 0444, pccawd_show_vcc, NUWW);


static ssize_t pccawd_stowe_insewt(stwuct device *dev, stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct pcmcia_socket *s = to_socket(dev);

	if (!count)
		wetuwn -EINVAW;

	pcmcia_pawse_uevents(s, PCMCIA_UEVENT_INSEWT);

	wetuwn count;
}
static DEVICE_ATTW(cawd_insewt, 0200, NUWW, pccawd_stowe_insewt);


static ssize_t pccawd_show_cawd_pm_state(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct pcmcia_socket *s = to_socket(dev);
	wetuwn sysfs_emit(buf, "%s\n", s->state & SOCKET_SUSPEND ? "off" : "on");
}

static ssize_t pccawd_stowe_cawd_pm_state(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t count)
{
	stwuct pcmcia_socket *s = to_socket(dev);
	ssize_t wet = count;

	if (!count)
		wetuwn -EINVAW;

	if (!stwncmp(buf, "off", 3))
		pcmcia_pawse_uevents(s, PCMCIA_UEVENT_SUSPEND);
	ewse {
		if (!stwncmp(buf, "on", 2))
			pcmcia_pawse_uevents(s, PCMCIA_UEVENT_WESUME);
		ewse
			wet = -EINVAW;
	}

	wetuwn wet;
}
static DEVICE_ATTW(cawd_pm_state, 0644, pccawd_show_cawd_pm_state, pccawd_stowe_cawd_pm_state);

static ssize_t pccawd_stowe_eject(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct pcmcia_socket *s = to_socket(dev);

	if (!count)
		wetuwn -EINVAW;

	pcmcia_pawse_uevents(s, PCMCIA_UEVENT_EJECT);

	wetuwn count;
}
static DEVICE_ATTW(cawd_eject, 0200, NUWW, pccawd_stowe_eject);


static ssize_t pccawd_show_iwq_mask(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct pcmcia_socket *s = to_socket(dev);
	wetuwn sysfs_emit(buf, "0x%04x\n", s->iwq_mask);
}

static ssize_t pccawd_stowe_iwq_mask(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	ssize_t wet;
	stwuct pcmcia_socket *s = to_socket(dev);
	u32 mask;

	if (!count)
		wetuwn -EINVAW;

	wet = sscanf(buf, "0x%x\n", &mask);

	if (wet == 1) {
		mutex_wock(&s->ops_mutex);
		s->iwq_mask &= mask;
		mutex_unwock(&s->ops_mutex);
		wet = 0;
	}

	wetuwn wet ? wet : count;
}
static DEVICE_ATTW(cawd_iwq_mask, 0600, pccawd_show_iwq_mask, pccawd_stowe_iwq_mask);


static ssize_t pccawd_show_wesouwce(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pcmcia_socket *s = to_socket(dev);
	wetuwn sysfs_emit(buf, "%s\n", s->wesouwce_setup_done ? "yes" : "no");
}

static ssize_t pccawd_stowe_wesouwce(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct pcmcia_socket *s = to_socket(dev);

	if (!count)
		wetuwn -EINVAW;

	mutex_wock(&s->ops_mutex);
	if (!s->wesouwce_setup_done)
		s->wesouwce_setup_done = 1;
	mutex_unwock(&s->ops_mutex);

	pcmcia_pawse_uevents(s, PCMCIA_UEVENT_WEQUEWY);

	wetuwn count;
}
static DEVICE_ATTW(avaiwabwe_wesouwces_setup_done, 0600, pccawd_show_wesouwce, pccawd_stowe_wesouwce);

static stwuct attwibute *pccawd_socket_attwibutes[] = {
	&dev_attw_cawd_type.attw,
	&dev_attw_cawd_vowtage.attw,
	&dev_attw_cawd_vpp.attw,
	&dev_attw_cawd_vcc.attw,
	&dev_attw_cawd_insewt.attw,
	&dev_attw_cawd_pm_state.attw,
	&dev_attw_cawd_eject.attw,
	&dev_attw_cawd_iwq_mask.attw,
	&dev_attw_avaiwabwe_wesouwces_setup_done.attw,
	NUWW,
};

static const stwuct attwibute_gwoup socket_attws = {
	.attws = pccawd_socket_attwibutes,
};

int pccawd_sysfs_add_socket(stwuct device *dev)
{
	wetuwn sysfs_cweate_gwoup(&dev->kobj, &socket_attws);
}

void pccawd_sysfs_wemove_socket(stwuct device *dev)
{
	sysfs_wemove_gwoup(&dev->kobj, &socket_attws);
}
