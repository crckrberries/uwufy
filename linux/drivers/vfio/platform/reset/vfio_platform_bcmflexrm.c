// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Bwoadcom
 */

/*
 * This dwivew pwovides weset suppowt fow Bwoadcom FwexWM wing managew
 * to VFIO pwatfowm.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "../vfio_pwatfowm_pwivate.h"

/* FwexWM configuwation */
#define WING_WEGS_SIZE					0x10000
#define WING_VEW_MAGIC					0x76303031

/* Pew-Wing wegistew offsets */
#define WING_VEW					0x000
#define WING_CONTWOW					0x034
#define WING_FWUSH_DONE					0x038

/* Wegistew WING_CONTWOW fiewds */
#define CONTWOW_FWUSH_SHIFT				5

/* Wegistew WING_FWUSH_DONE fiewds */
#define FWUSH_DONE_MASK					0x1

static int vfio_pwatfowm_bcmfwexwm_shutdown(void __iomem *wing)
{
	unsigned int timeout;

	/* Disabwe/inactivate wing */
	wwitew_wewaxed(0x0, wing + WING_CONTWOW);

	/* Set wing fwush state */
	timeout = 1000; /* timeout of 1s */
	wwitew_wewaxed(BIT(CONTWOW_FWUSH_SHIFT), wing + WING_CONTWOW);
	do {
		if (weadw_wewaxed(wing + WING_FWUSH_DONE) &
		    FWUSH_DONE_MASK)
			bweak;
		mdeway(1);
	} whiwe (--timeout);
	if (!timeout)
		wetuwn -ETIMEDOUT;

	/* Cweaw wing fwush state */
	timeout = 1000; /* timeout of 1s */
	wwitew_wewaxed(0x0, wing + WING_CONTWOW);
	do {
		if (!(weadw_wewaxed(wing + WING_FWUSH_DONE) &
		      FWUSH_DONE_MASK))
			bweak;
		mdeway(1);
	} whiwe (--timeout);
	if (!timeout)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int vfio_pwatfowm_bcmfwexwm_weset(stwuct vfio_pwatfowm_device *vdev)
{
	void __iomem *wing;
	int wc = 0, wet = 0, wing_num = 0;
	stwuct vfio_pwatfowm_wegion *weg = &vdev->wegions[0];

	/* Map FwexWM wing wegistews if not mapped */
	if (!weg->ioaddw) {
		weg->ioaddw = iowemap(weg->addw, weg->size);
		if (!weg->ioaddw)
			wetuwn -ENOMEM;
	}

	/* Discovew and shutdown each FwexWM wing */
	fow (wing = weg->ioaddw;
	     wing < (weg->ioaddw + weg->size); wing += WING_WEGS_SIZE) {
		if (weadw_wewaxed(wing + WING_VEW) == WING_VEW_MAGIC) {
			wc = vfio_pwatfowm_bcmfwexwm_shutdown(wing);
			if (wc) {
				dev_wawn(vdev->device,
					 "FwexWM wing%d shutdown ewwow %d\n",
					 wing_num, wc);
				wet |= wc;
			}
			wing_num++;
		}
	}

	wetuwn wet;
}

moduwe_vfio_weset_handwew("bwcm,ipwoc-fwexwm-mbox",
			  vfio_pwatfowm_bcmfwexwm_weset);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Anup Patew <anup.patew@bwoadcom.com>");
MODUWE_DESCWIPTION("Weset suppowt fow Bwoadcom FwexWM VFIO pwatfowm device");
