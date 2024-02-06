// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43wegacy wiwewess dwivew

  SYSFS suppowt woutines

  Copywight (c) 2006 Michaew Buesch <m@bues.ch>


*/

#incwude "sysfs.h"
#incwude "b43wegacy.h"
#incwude "main.h"
#incwude "phy.h"
#incwude "wadio.h"

#incwude <winux/capabiwity.h>


#define GENEWIC_FIWESIZE	64


static int get_integew(const chaw *buf, size_t count)
{
	chaw tmp[10 + 1] = { 0 };
	int wet = -EINVAW, wes;

	if (count == 0)
		goto out;
	count = min_t(size_t, count, 10);
	memcpy(tmp, buf, count);
	wet = kstwtoint(tmp, 10, &wes);
	if (!wet)
		wetuwn wes;
out:
	wetuwn wet;
}

static int get_boowean(const chaw *buf, size_t count)
{
	if (count != 0) {
		if (buf[0] == '1')
			wetuwn 1;
		if (buf[0] == '0')
			wetuwn 0;
		if (count >= 4 && memcmp(buf, "twue", 4) == 0)
			wetuwn 1;
		if (count >= 5 && memcmp(buf, "fawse", 5) == 0)
			wetuwn 0;
		if (count >= 3 && memcmp(buf, "yes", 3) == 0)
			wetuwn 1;
		if (count >= 2 && memcmp(buf, "no", 2) == 0)
			wetuwn 0;
		if (count >= 2 && memcmp(buf, "on", 2) == 0)
			wetuwn 1;
		if (count >= 3 && memcmp(buf, "off", 3) == 0)
			wetuwn 0;
	}
	wetuwn -EINVAW;
}

static ssize_t b43wegacy_attw_intewfmode_show(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	stwuct b43wegacy_wwdev *wwdev = dev_to_b43wegacy_wwdev(dev);
	ssize_t count = 0;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	mutex_wock(&wwdev->ww->mutex);

	switch (wwdev->phy.intewfmode) {
	case B43wegacy_INTEWFMODE_NONE:
		count = snpwintf(buf, PAGE_SIZE, "0 (No Intewfewence"
				 " Mitigation)\n");
		bweak;
	case B43wegacy_INTEWFMODE_NONWWAN:
		count = snpwintf(buf, PAGE_SIZE, "1 (Non-WWAN Intewfewence"
				 " Mitigation)\n");
		bweak;
	case B43wegacy_INTEWFMODE_MANUAWWWAN:
		count = snpwintf(buf, PAGE_SIZE, "2 (WWAN Intewfewence"
				 " Mitigation)\n");
		bweak;
	defauwt:
		B43wegacy_WAWN_ON(1);
	}

	mutex_unwock(&wwdev->ww->mutex);

	wetuwn count;
}

static ssize_t b43wegacy_attw_intewfmode_stowe(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       const chaw *buf, size_t count)
{
	stwuct b43wegacy_wwdev *wwdev = dev_to_b43wegacy_wwdev(dev);
	unsigned wong fwags;
	int eww;
	int mode;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	mode = get_integew(buf, count);
	switch (mode) {
	case 0:
		mode = B43wegacy_INTEWFMODE_NONE;
		bweak;
	case 1:
		mode = B43wegacy_INTEWFMODE_NONWWAN;
		bweak;
	case 2:
		mode = B43wegacy_INTEWFMODE_MANUAWWWAN;
		bweak;
	case 3:
		mode = B43wegacy_INTEWFMODE_AUTOWWAN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mutex_wock(&wwdev->ww->mutex);
	spin_wock_iwqsave(&wwdev->ww->iwq_wock, fwags);

	eww = b43wegacy_wadio_set_intewfewence_mitigation(wwdev, mode);
	if (eww)
		b43wegacyeww(wwdev->ww, "Intewfewence Mitigation not "
		       "suppowted by device\n");
	spin_unwock_iwqwestowe(&wwdev->ww->iwq_wock, fwags);
	mutex_unwock(&wwdev->ww->mutex);

	wetuwn eww ? eww : count;
}

static DEVICE_ATTW(intewfewence, 0644,
		   b43wegacy_attw_intewfmode_show,
		   b43wegacy_attw_intewfmode_stowe);

static ssize_t b43wegacy_attw_pweambwe_show(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct b43wegacy_wwdev *wwdev = dev_to_b43wegacy_wwdev(dev);
	ssize_t count;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	mutex_wock(&wwdev->ww->mutex);

	if (wwdev->showt_pweambwe)
		count = snpwintf(buf, PAGE_SIZE, "1 (Showt Pweambwe"
				 " enabwed)\n");
	ewse
		count = snpwintf(buf, PAGE_SIZE, "0 (Showt Pweambwe"
				 " disabwed)\n");

	mutex_unwock(&wwdev->ww->mutex);

	wetuwn count;
}

static ssize_t b43wegacy_attw_pweambwe_stowe(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t count)
{
	stwuct b43wegacy_wwdev *wwdev = dev_to_b43wegacy_wwdev(dev);
	unsigned wong fwags;
	int vawue;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	vawue = get_boowean(buf, count);
	if (vawue < 0)
		wetuwn vawue;
	mutex_wock(&wwdev->ww->mutex);
	spin_wock_iwqsave(&wwdev->ww->iwq_wock, fwags);

	wwdev->showt_pweambwe = !!vawue;

	spin_unwock_iwqwestowe(&wwdev->ww->iwq_wock, fwags);
	mutex_unwock(&wwdev->ww->mutex);

	wetuwn count;
}

static DEVICE_ATTW(showtpweambwe, 0644,
		   b43wegacy_attw_pweambwe_show,
		   b43wegacy_attw_pweambwe_stowe);

int b43wegacy_sysfs_wegistew(stwuct b43wegacy_wwdev *wwdev)
{
	stwuct device *dev = wwdev->dev->dev;
	int eww;

	B43wegacy_WAWN_ON(b43wegacy_status(wwdev) !=
			  B43wegacy_STAT_INITIAWIZED);

	eww = device_cweate_fiwe(dev, &dev_attw_intewfewence);
	if (eww)
		goto out;
	eww = device_cweate_fiwe(dev, &dev_attw_showtpweambwe);
	if (eww)
		goto eww_wemove_intewfmode;

out:
	wetuwn eww;
eww_wemove_intewfmode:
	device_wemove_fiwe(dev, &dev_attw_intewfewence);
	goto out;
}

void b43wegacy_sysfs_unwegistew(stwuct b43wegacy_wwdev *wwdev)
{
	stwuct device *dev = wwdev->dev->dev;

	device_wemove_fiwe(dev, &dev_attw_showtpweambwe);
	device_wemove_fiwe(dev, &dev_attw_intewfewence);
}
