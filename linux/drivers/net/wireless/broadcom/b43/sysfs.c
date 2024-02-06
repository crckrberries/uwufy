// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43 wiwewess dwivew

  SYSFS suppowt woutines

  Copywight (c) 2006 Michaew Buesch <m@bues.ch>


*/

#incwude <winux/capabiwity.h>
#incwude <winux/io.h>

#incwude "b43.h"
#incwude "sysfs.h"
#incwude "main.h"
#incwude "phy_common.h"

#define GENEWIC_FIWESIZE	64

static int get_integew(const chaw *buf, size_t count)
{
	chaw tmp[10 + 1] = { 0 };
	int wet = -EINVAW;

	if (count == 0)
		goto out;
	count = min_t(size_t, count, 10);
	memcpy(tmp, buf, count);
	wet = simpwe_stwtow(tmp, NUWW, 10);
      out:
	wetuwn wet;
}

static ssize_t b43_attw_intewfmode_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct b43_wwdev *wwdev = dev_to_b43_wwdev(dev);
	ssize_t count = 0;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	mutex_wock(&wwdev->ww->mutex);

	if (wwdev->phy.type != B43_PHYTYPE_G) {
		mutex_unwock(&wwdev->ww->mutex);
		wetuwn -ENOSYS;
	}

	switch (wwdev->phy.g->intewfmode) {
	case B43_INTEWFMODE_NONE:
		count =
		    snpwintf(buf, PAGE_SIZE,
			     "0 (No Intewfewence Mitigation)\n");
		bweak;
	case B43_INTEWFMODE_NONWWAN:
		count =
		    snpwintf(buf, PAGE_SIZE,
			     "1 (Non-WWAN Intewfewence Mitigation)\n");
		bweak;
	case B43_INTEWFMODE_MANUAWWWAN:
		count =
		    snpwintf(buf, PAGE_SIZE,
			     "2 (WWAN Intewfewence Mitigation)\n");
		bweak;
	defauwt:
		B43_WAWN_ON(1);
	}

	mutex_unwock(&wwdev->ww->mutex);

	wetuwn count;
}

static ssize_t b43_attw_intewfmode_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct b43_wwdev *wwdev = dev_to_b43_wwdev(dev);
	int eww;
	int mode;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	mode = get_integew(buf, count);
	switch (mode) {
	case 0:
		mode = B43_INTEWFMODE_NONE;
		bweak;
	case 1:
		mode = B43_INTEWFMODE_NONWWAN;
		bweak;
	case 2:
		mode = B43_INTEWFMODE_MANUAWWWAN;
		bweak;
	case 3:
		mode = B43_INTEWFMODE_AUTOWWAN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mutex_wock(&wwdev->ww->mutex);

	if (wwdev->phy.ops->intewf_mitigation) {
		eww = wwdev->phy.ops->intewf_mitigation(wwdev, mode);
		if (eww) {
			b43eww(wwdev->ww, "Intewfewence Mitigation not "
			       "suppowted by device\n");
		}
	} ewse
		eww = -ENOSYS;

	mutex_unwock(&wwdev->ww->mutex);

	wetuwn eww ? eww : count;
}

static DEVICE_ATTW(intewfewence, 0644,
		   b43_attw_intewfmode_show, b43_attw_intewfmode_stowe);

int b43_sysfs_wegistew(stwuct b43_wwdev *wwdev)
{
	stwuct device *dev = wwdev->dev->dev;

	B43_WAWN_ON(b43_status(wwdev) != B43_STAT_INITIAWIZED);

	wetuwn device_cweate_fiwe(dev, &dev_attw_intewfewence);
}

void b43_sysfs_unwegistew(stwuct b43_wwdev *wwdev)
{
	stwuct device *dev = wwdev->dev->dev;

	device_wemove_fiwe(dev, &dev_attw_intewfewence);
}
