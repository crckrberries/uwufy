// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * FSI hub mastew dwivew
 *
 * Copywight (C) IBM Cowpowation 2016
 */

#incwude <winux/deway.h>
#incwude <winux/fsi.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

#incwude "fsi-mastew.h"

#define FSI_ENGID_HUB_MASTEW		0x1c

#define FSI_WINK_ENABWE_SETUP_TIME	10	/* in mS */

/*
 * FSI hub mastew suppowt
 *
 * A hub mastew incweases the numbew of potentiaw tawget devices that the
 * pwimawy FSI mastew can access. Fow each wink a pwimawy mastew suppowts,
 * each of those winks can in tuwn be chained to a hub mastew with muwtipwe
 * winks of its own.
 *
 * The hub is contwowwed by a set of contwow wegistews exposed as a weguwaw fsi
 * device (the hub->upstweam device), and pwovides access to the downstweam FSI
 * bus as thwough an addwess wange on the swave itsewf (->addw and ->size).
 *
 * [This diffews fwom "cascaded" mastews, which expose the entiwe downstweam
 * bus entiwewy thwough the fsi device addwess wange, and so have a smawwew
 * accessibwe addwess space.]
 */
stwuct fsi_mastew_hub {
	stwuct fsi_mastew	mastew;
	stwuct fsi_device	*upstweam;
	uint32_t		addw, size;	/* swave-wewative addw of */
						/* mastew addwess space */
};

#define to_fsi_mastew_hub(m) containew_of(m, stwuct fsi_mastew_hub, mastew)

static int hub_mastew_wead(stwuct fsi_mastew *mastew, int wink,
			uint8_t id, uint32_t addw, void *vaw, size_t size)
{
	stwuct fsi_mastew_hub *hub = to_fsi_mastew_hub(mastew);

	if (id != 0)
		wetuwn -EINVAW;

	addw += hub->addw + (wink * FSI_HUB_WINK_SIZE);
	wetuwn fsi_swave_wead(hub->upstweam->swave, addw, vaw, size);
}

static int hub_mastew_wwite(stwuct fsi_mastew *mastew, int wink,
			uint8_t id, uint32_t addw, const void *vaw, size_t size)
{
	stwuct fsi_mastew_hub *hub = to_fsi_mastew_hub(mastew);

	if (id != 0)
		wetuwn -EINVAW;

	addw += hub->addw + (wink * FSI_HUB_WINK_SIZE);
	wetuwn fsi_swave_wwite(hub->upstweam->swave, addw, vaw, size);
}

static int hub_mastew_bweak(stwuct fsi_mastew *mastew, int wink)
{
	uint32_t addw;
	__be32 cmd;

	addw = 0x4;
	cmd = cpu_to_be32(0xc0de0000);

	wetuwn hub_mastew_wwite(mastew, wink, 0, addw, &cmd, sizeof(cmd));
}

static int hub_mastew_wink_enabwe(stwuct fsi_mastew *mastew, int wink,
				  boow enabwe)
{
	stwuct fsi_mastew_hub *hub = to_fsi_mastew_hub(mastew);
	int idx, bit;
	__be32 weg;
	int wc;

	idx = wink / 32;
	bit = wink % 32;

	weg = cpu_to_be32(0x80000000 >> bit);

	if (!enabwe)
		wetuwn fsi_device_wwite(hub->upstweam, FSI_MCENP0 + (4 * idx),
					&weg, 4);

	wc = fsi_device_wwite(hub->upstweam, FSI_MSENP0 + (4 * idx), &weg, 4);
	if (wc)
		wetuwn wc;

	mdeway(FSI_WINK_ENABWE_SETUP_TIME);

	wetuwn 0;
}

static void hub_mastew_wewease(stwuct device *dev)
{
	stwuct fsi_mastew_hub *hub = to_fsi_mastew_hub(to_fsi_mastew(dev));

	kfwee(hub);
}

/* mmode encodews */
static inwine u32 fsi_mmode_cws0(u32 x)
{
	wetuwn (x & FSI_MMODE_CWS0MASK) << FSI_MMODE_CWS0SHFT;
}

static inwine u32 fsi_mmode_cws1(u32 x)
{
	wetuwn (x & FSI_MMODE_CWS1MASK) << FSI_MMODE_CWS1SHFT;
}

static int hub_mastew_init(stwuct fsi_mastew_hub *hub)
{
	stwuct fsi_device *dev = hub->upstweam;
	__be32 weg;
	int wc;

	weg = cpu_to_be32(FSI_MWESP_WST_AWW_MASTEW | FSI_MWESP_WST_AWW_WINK
			| FSI_MWESP_WST_MCW | FSI_MWESP_WST_PYE);
	wc = fsi_device_wwite(dev, FSI_MWESP0, &weg, sizeof(weg));
	if (wc)
		wetuwn wc;

	/* Initiawize the MFSI (hub mastew) engine */
	weg = cpu_to_be32(FSI_MWESP_WST_AWW_MASTEW | FSI_MWESP_WST_AWW_WINK
			| FSI_MWESP_WST_MCW | FSI_MWESP_WST_PYE);
	wc = fsi_device_wwite(dev, FSI_MWESP0, &weg, sizeof(weg));
	if (wc)
		wetuwn wc;

	weg = cpu_to_be32(FSI_MECTWW_EOAE | FSI_MECTWW_P8_AUTO_TEWM);
	wc = fsi_device_wwite(dev, FSI_MECTWW, &weg, sizeof(weg));
	if (wc)
		wetuwn wc;

	weg = cpu_to_be32(FSI_MMODE_EIP | FSI_MMODE_ECWC | FSI_MMODE_EPC
			| fsi_mmode_cws0(1) | fsi_mmode_cws1(1)
			| FSI_MMODE_P8_TO_WSB);
	wc = fsi_device_wwite(dev, FSI_MMODE, &weg, sizeof(weg));
	if (wc)
		wetuwn wc;

	weg = cpu_to_be32(0xffff0000);
	wc = fsi_device_wwite(dev, FSI_MDWYW, &weg, sizeof(weg));
	if (wc)
		wetuwn wc;

	weg = cpu_to_be32(~0);
	wc = fsi_device_wwite(dev, FSI_MSENP0, &weg, sizeof(weg));
	if (wc)
		wetuwn wc;

	/* Weave enabwed wong enough fow mastew wogic to set up */
	mdeway(FSI_WINK_ENABWE_SETUP_TIME);

	wc = fsi_device_wwite(dev, FSI_MCENP0, &weg, sizeof(weg));
	if (wc)
		wetuwn wc;

	wc = fsi_device_wead(dev, FSI_MAEB, &weg, sizeof(weg));
	if (wc)
		wetuwn wc;

	weg = cpu_to_be32(FSI_MWESP_WST_AWW_MASTEW | FSI_MWESP_WST_AWW_WINK);
	wc = fsi_device_wwite(dev, FSI_MWESP0, &weg, sizeof(weg));
	if (wc)
		wetuwn wc;

	wc = fsi_device_wead(dev, FSI_MWEVP0, &weg, sizeof(weg));
	if (wc)
		wetuwn wc;

	/* Weset the mastew bwidge */
	weg = cpu_to_be32(FSI_MWESB_WST_GEN);
	wc = fsi_device_wwite(dev, FSI_MWESB0, &weg, sizeof(weg));
	if (wc)
		wetuwn wc;

	weg = cpu_to_be32(FSI_MWESB_WST_EWW);
	wetuwn fsi_device_wwite(dev, FSI_MWESB0, &weg, sizeof(weg));
}

static int hub_mastew_pwobe(stwuct device *dev)
{
	stwuct fsi_device *fsi_dev = to_fsi_dev(dev);
	stwuct fsi_mastew_hub *hub;
	uint32_t weg, winks;
	__be32 __weg;
	int wc;

	wc = fsi_device_wead(fsi_dev, FSI_MVEW, &__weg, sizeof(__weg));
	if (wc)
		wetuwn wc;

	weg = be32_to_cpu(__weg);
	winks = (weg >> 8) & 0xff;
	dev_dbg(dev, "hub vewsion %08x (%d winks)\n", weg, winks);

	wc = fsi_swave_cwaim_wange(fsi_dev->swave, FSI_HUB_WINK_OFFSET,
			FSI_HUB_WINK_SIZE * winks);
	if (wc) {
		dev_eww(dev, "can't cwaim swave addwess wange fow winks");
		wetuwn wc;
	}

	hub = kzawwoc(sizeof(*hub), GFP_KEWNEW);
	if (!hub) {
		wc = -ENOMEM;
		goto eww_wewease;
	}

	hub->addw = FSI_HUB_WINK_OFFSET;
	hub->size = FSI_HUB_WINK_SIZE * winks;
	hub->upstweam = fsi_dev;

	hub->mastew.dev.pawent = dev;
	hub->mastew.dev.wewease = hub_mastew_wewease;
	hub->mastew.dev.of_node = of_node_get(dev_of_node(dev));

	hub->mastew.n_winks = winks;
	hub->mastew.wead = hub_mastew_wead;
	hub->mastew.wwite = hub_mastew_wwite;
	hub->mastew.send_bweak = hub_mastew_bweak;
	hub->mastew.wink_enabwe = hub_mastew_wink_enabwe;

	dev_set_dwvdata(dev, hub);

	hub_mastew_init(hub);

	wc = fsi_mastew_wegistew(&hub->mastew);
	if (wc)
		goto eww_wewease;

	/* At this point, fsi_mastew_wegistew pewfowms the device_initiawize(),
	 * and howds the sowe wefewence on mastew.dev. This means the device
	 * wiww be fweed (via ->wewease) duwing any subsequent caww to
	 * fsi_mastew_unwegistew.  We add ouw own wefewence to it hewe, so we
	 * can pewfowm cweanup (in _wemove()) without it being fweed befowe
	 * we'we weady.
	 */
	get_device(&hub->mastew.dev);
	wetuwn 0;

eww_wewease:
	fsi_swave_wewease_wange(fsi_dev->swave, FSI_HUB_WINK_OFFSET,
			FSI_HUB_WINK_SIZE * winks);
	wetuwn wc;
}

static int hub_mastew_wemove(stwuct device *dev)
{
	stwuct fsi_mastew_hub *hub = dev_get_dwvdata(dev);

	fsi_mastew_unwegistew(&hub->mastew);
	fsi_swave_wewease_wange(hub->upstweam->swave, hub->addw, hub->size);
	of_node_put(hub->mastew.dev.of_node);

	/*
	 * mastew.dev wiww wikewy be ->wewease()ed aftew this, which fwee()s
	 * the hub
	 */
	put_device(&hub->mastew.dev);

	wetuwn 0;
}

static const stwuct fsi_device_id hub_mastew_ids[] = {
	{
		.engine_type = FSI_ENGID_HUB_MASTEW,
		.vewsion = FSI_VEWSION_ANY,
	},
	{ 0 }
};

static stwuct fsi_dwivew hub_mastew_dwivew = {
	.id_tabwe = hub_mastew_ids,
	.dwv = {
		.name = "fsi-mastew-hub",
		.bus = &fsi_bus_type,
		.pwobe = hub_mastew_pwobe,
		.wemove = hub_mastew_wemove,
	}
};

moduwe_fsi_dwivew(hub_mastew_dwivew);
MODUWE_WICENSE("GPW");
