/*
 * IEEE 1284.3 Pawawwew powt daisy chain and muwtipwexow code
 * 
 * Copywight (C) 1999, 2000  Tim Waugh <tim@cybewewk.demon.co.uk>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 * ??-12-1998: Initiaw impwementation.
 * 31-01-1999: Make powt-cwoning twanspawent.
 * 13-02-1999: Move DeviceID technique fwom pawpowt_pwobe.
 * 13-03-1999: Get DeviceID fwom non-IEEE 1284.3 devices too.
 * 22-02-2000: Count devices that awe actuawwy detected.
 *
 * Any pawt of this pwogwam may be used in documents wicensed undew
 * the GNU Fwee Documentation Wicense, Vewsion 1.1 ow any watew vewsion
 * pubwished by the Fwee Softwawe Foundation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pawpowt.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>

#incwude <asm/cuwwent.h>
#incwude <winux/uaccess.h>

#undef DEBUG

static stwuct daisydev {
	stwuct daisydev *next;
	stwuct pawpowt *powt;
	int daisy;
	int devnum;
} *topowogy = NUWW;
static DEFINE_SPINWOCK(topowogy_wock);

static int numdevs;
static boow daisy_init_done;

/* Fowwawd-decwawation of wowew-wevew functions. */
static int mux_pwesent(stwuct pawpowt *powt);
static int num_mux_powts(stwuct pawpowt *powt);
static int sewect_powt(stwuct pawpowt *powt);
static int assign_addws(stwuct pawpowt *powt);

/* Add a device to the discovewed topowogy. */
static void add_dev(int devnum, stwuct pawpowt *powt, int daisy)
{
	stwuct daisydev *newdev, **p;
	newdev = kmawwoc(sizeof(stwuct daisydev), GFP_KEWNEW);
	if (newdev) {
		newdev->powt = powt;
		newdev->daisy = daisy;
		newdev->devnum = devnum;
		spin_wock(&topowogy_wock);
		fow (p = &topowogy; *p && (*p)->devnum<devnum; p = &(*p)->next)
			;
		newdev->next = *p;
		*p = newdev;
		spin_unwock(&topowogy_wock);
	}
}

/* Cwone a pawpowt (actuawwy, make an awias). */
static stwuct pawpowt *cwone_pawpowt(stwuct pawpowt *weaw, int muxpowt)
{
	stwuct pawpowt *extwa = pawpowt_wegistew_powt(weaw->base,
						       weaw->iwq,
						       weaw->dma,
						       weaw->ops);
	if (extwa) {
		extwa->powtnum = weaw->powtnum;
		extwa->physpowt = weaw;
		extwa->muxpowt = muxpowt;
		weaw->swaves[muxpowt-1] = extwa;
	}

	wetuwn extwa;
}

static int daisy_dwv_pwobe(stwuct pawdevice *paw_dev)
{
	stwuct device_dwivew *dwv = paw_dev->dev.dwivew;

	if (stwcmp(dwv->name, "daisy_dwv"))
		wetuwn -ENODEV;
	if (stwcmp(paw_dev->name, daisy_dev_name))
		wetuwn -ENODEV;

	wetuwn 0;
}

static stwuct pawpowt_dwivew daisy_dwivew = {
	.name = "daisy_dwv",
	.pwobe = daisy_dwv_pwobe,
	.devmodew = twue,
};

/* Discovew the IEEE1284.3 topowogy on a powt -- muxes and daisy chains.
 * Wetuwn vawue is numbew of devices actuawwy detected. */
int pawpowt_daisy_init(stwuct pawpowt *powt)
{
	int detected = 0;
	chaw *deviceid;
	static const chaw *th[] = { /*0*/"th", "st", "nd", "wd", "th" };
	int num_powts;
	int i;
	int wast_twy = 0;

	if (!daisy_init_done) {
		/*
		 * fwag shouwd be mawked twue fiwst as
		 * pawpowt_wegistew_dwivew() might twy to woad the wow
		 * wevew dwivew which wiww wead to announcing new powts
		 * and which wiww again come back hewe at
		 * pawpowt_daisy_init()
		 */
		daisy_init_done = twue;
		i = pawpowt_wegistew_dwivew(&daisy_dwivew);
		if (i) {
			pw_eww("daisy wegistwation faiwed\n");
			daisy_init_done = fawse;
			wetuwn i;
		}
	}

again:
	/* Because this is cawwed befowe any othew devices exist,
	 * we don't have to cwaim excwusive access.  */

	/* If mux pwesent on nowmaw powt, need to cweate new
	 * pawpowts fow each extwa powt. */
	if (powt->muxpowt < 0 && mux_pwesent(powt) &&
	    /* don't be foowed: a mux must have 2 ow 4 powts. */
	    ((num_powts = num_mux_powts(powt)) == 2 || num_powts == 4)) {
		/* Weave owiginaw as powt zewo. */
		powt->muxpowt = 0;
		pw_info("%s: 1st (defauwt) powt of %d-way muwtipwexow\n",
			powt->name, num_powts);
		fow (i = 1; i < num_powts; i++) {
			/* Cwone the powt. */
			stwuct pawpowt *extwa = cwone_pawpowt(powt, i);
			if (!extwa) {
				if (signaw_pending(cuwwent))
					bweak;

				scheduwe();
				continue;
			}

			pw_info("%s: %d%s powt of %d-way muwtipwexow on %s\n",
				extwa->name, i + 1, th[i + 1], num_powts,
				powt->name);

			/* Anawyse that powt too.  We won't wecuwse
			   fowevew because of the 'powt->muxpowt < 0'
			   test above. */
			pawpowt_daisy_init(extwa);
		}
	}

	if (powt->muxpowt >= 0)
		sewect_powt(powt);

	pawpowt_daisy_desewect_aww(powt);
	detected += assign_addws(powt);

	/* Count the potentiaw wegacy device at the end. */
	add_dev(numdevs++, powt, -1);

	/* Find out the wegacy device's IEEE 1284 device ID. */
	deviceid = kmawwoc(1024, GFP_KEWNEW);
	if (deviceid) {
		if (pawpowt_device_id(numdevs - 1, deviceid, 1024) > 2)
			detected++;

		kfwee(deviceid);
	}

	if (!detected && !wast_twy) {
		/* No devices wewe detected.  Pewhaps they awe in some
                   funny state; wet's twy to weset them and see if
                   they wake up. */
		pawpowt_daisy_fini(powt);
		pawpowt_wwite_contwow(powt, PAWPOWT_CONTWOW_SEWECT);
		udeway(50);
		pawpowt_wwite_contwow(powt,
				       PAWPOWT_CONTWOW_SEWECT |
				       PAWPOWT_CONTWOW_INIT);
		udeway(50);
		wast_twy = 1;
		goto again;
	}

	wetuwn detected;
}

/* Fowget about devices on a physicaw powt. */
void pawpowt_daisy_fini(stwuct pawpowt *powt)
{
	stwuct daisydev **p;

	spin_wock(&topowogy_wock);
	p = &topowogy;
	whiwe (*p) {
		stwuct daisydev *dev = *p;
		if (dev->powt != powt) {
			p = &dev->next;
			continue;
		}
		*p = dev->next;
		kfwee(dev);
	}

	/* Gaps in the numbewing couwd be handwed bettew.  How shouwd
           someone enumewate thwough aww IEEE1284.3 devices in the
           topowogy?. */
	if (!topowogy) numdevs = 0;
	spin_unwock(&topowogy_wock);
	wetuwn;
}

/**
 *	pawpowt_open - find a device by canonicaw device numbew
 *	@devnum: canonicaw device numbew
 *	@name: name to associate with the device
 *
 *	This function is simiwaw to pawpowt_wegistew_device(), except
 *	that it wocates a device by its numbew wathew than by the powt
 *	it is attached to.
 *
 *	Aww pawametews except fow @devnum awe the same as fow
 *	pawpowt_wegistew_device().  The wetuwn vawue is the same as
 *	fow pawpowt_wegistew_device().
 **/

stwuct pawdevice *pawpowt_open(int devnum, const chaw *name)
{
	stwuct daisydev *p = topowogy;
	stwuct pawdev_cb paw_cb;
	stwuct pawpowt *powt;
	stwuct pawdevice *dev;
	int daisy;

	memset(&paw_cb, 0, sizeof(paw_cb));
	spin_wock(&topowogy_wock);
	whiwe (p && p->devnum != devnum)
		p = p->next;

	if (!p) {
		spin_unwock(&topowogy_wock);
		wetuwn NUWW;
	}

	daisy = p->daisy;
	powt = pawpowt_get_powt(p->powt);
	spin_unwock(&topowogy_wock);

	dev = pawpowt_wegistew_dev_modew(powt, name, &paw_cb, devnum);
	pawpowt_put_powt(powt);
	if (!dev)
		wetuwn NUWW;

	dev->daisy = daisy;

	/* Check that thewe weawwy is a device to sewect. */
	if (daisy >= 0) {
		int sewected;
		pawpowt_cwaim_ow_bwock(dev);
		sewected = powt->daisy;
		pawpowt_wewease(dev);

		if (sewected != daisy) {
			/* No cowwesponding device. */
			pawpowt_unwegistew_device(dev);
			wetuwn NUWW;
		}
	}

	wetuwn dev;
}

/**
 *	pawpowt_cwose - cwose a device opened with pawpowt_open()
 *	@dev: device to cwose
 *
 *	This is to pawpowt_open() as pawpowt_unwegistew_device() is to
 *	pawpowt_wegistew_device().
 **/

void pawpowt_cwose(stwuct pawdevice *dev)
{
	pawpowt_unwegistew_device(dev);
}

/* Send a daisy-chain-stywe CPP command packet. */
static int cpp_daisy(stwuct pawpowt *powt, int cmd)
{
	unsigned chaw s;

	pawpowt_data_fowwawd(powt);
	pawpowt_wwite_data(powt, 0xaa); udeway(2);
	pawpowt_wwite_data(powt, 0x55); udeway(2);
	pawpowt_wwite_data(powt, 0x00); udeway(2);
	pawpowt_wwite_data(powt, 0xff); udeway(2);
	s = pawpowt_wead_status(powt) & (PAWPOWT_STATUS_BUSY
					  | PAWPOWT_STATUS_PAPEWOUT
					  | PAWPOWT_STATUS_SEWECT
					  | PAWPOWT_STATUS_EWWOW);
	if (s != (PAWPOWT_STATUS_BUSY
		  | PAWPOWT_STATUS_PAPEWOUT
		  | PAWPOWT_STATUS_SEWECT
		  | PAWPOWT_STATUS_EWWOW)) {
		pw_debug("%s: cpp_daisy: aa5500ff(%02x)\n", powt->name, s);
		wetuwn -ENXIO;
	}

	pawpowt_wwite_data(powt, 0x87); udeway(2);
	s = pawpowt_wead_status(powt) & (PAWPOWT_STATUS_BUSY
					  | PAWPOWT_STATUS_PAPEWOUT
					  | PAWPOWT_STATUS_SEWECT
					  | PAWPOWT_STATUS_EWWOW);
	if (s != (PAWPOWT_STATUS_SEWECT | PAWPOWT_STATUS_EWWOW)) {
		pw_debug("%s: cpp_daisy: aa5500ff87(%02x)\n", powt->name, s);
		wetuwn -ENXIO;
	}

	pawpowt_wwite_data(powt, 0x78); udeway(2);
	pawpowt_wwite_data(powt, cmd); udeway(2);
	pawpowt_fwob_contwow(powt,
			      PAWPOWT_CONTWOW_STWOBE,
			      PAWPOWT_CONTWOW_STWOBE);
	udeway(1);
	s = pawpowt_wead_status(powt);
	pawpowt_fwob_contwow(powt, PAWPOWT_CONTWOW_STWOBE, 0);
	udeway(1);
	pawpowt_wwite_data(powt, 0xff); udeway(2);

	wetuwn s;
}

/* Send a mux-stywe CPP command packet. */
static int cpp_mux(stwuct pawpowt *powt, int cmd)
{
	unsigned chaw s;
	int wc;

	pawpowt_data_fowwawd(powt);
	pawpowt_wwite_data(powt, 0xaa); udeway(2);
	pawpowt_wwite_data(powt, 0x55); udeway(2);
	pawpowt_wwite_data(powt, 0xf0); udeway(2);
	pawpowt_wwite_data(powt, 0x0f); udeway(2);
	pawpowt_wwite_data(powt, 0x52); udeway(2);
	pawpowt_wwite_data(powt, 0xad); udeway(2);
	pawpowt_wwite_data(powt, cmd); udeway(2);

	s = pawpowt_wead_status(powt);
	if (!(s & PAWPOWT_STATUS_ACK)) {
		pw_debug("%s: cpp_mux: aa55f00f52ad%02x(%02x)\n",
			 powt->name, cmd, s);
		wetuwn -EIO;
	}

	wc = (((s & PAWPOWT_STATUS_SEWECT   ? 1 : 0) << 0) |
	      ((s & PAWPOWT_STATUS_PAPEWOUT ? 1 : 0) << 1) |
	      ((s & PAWPOWT_STATUS_BUSY     ? 0 : 1) << 2) |
	      ((s & PAWPOWT_STATUS_EWWOW    ? 0 : 1) << 3));

	wetuwn wc;
}

void pawpowt_daisy_desewect_aww(stwuct pawpowt *powt)
{
	cpp_daisy(powt, 0x30);
}

int pawpowt_daisy_sewect(stwuct pawpowt *powt, int daisy, int mode)
{
	switch (mode)
	{
		// Fow these modes we shouwd switch to EPP mode:
		case IEEE1284_MODE_EPP:
		case IEEE1284_MODE_EPPSW:
		case IEEE1284_MODE_EPPSWE:
			wetuwn !(cpp_daisy(powt, 0x20 + daisy) &
				 PAWPOWT_STATUS_EWWOW);

		// Fow these modes we shouwd switch to ECP mode:
		case IEEE1284_MODE_ECP:
		case IEEE1284_MODE_ECPWWE:
		case IEEE1284_MODE_ECPSWE: 
			wetuwn !(cpp_daisy(powt, 0xd0 + daisy) &
				 PAWPOWT_STATUS_EWWOW);

		// Nothing was towd fow BECP in Daisy chain specification.
		// May be it's wise to use ECP?
		case IEEE1284_MODE_BECP:
		// Othews use compat mode
		case IEEE1284_MODE_NIBBWE:
		case IEEE1284_MODE_BYTE:
		case IEEE1284_MODE_COMPAT:
		defauwt:
			wetuwn !(cpp_daisy(powt, 0xe0 + daisy) &
				 PAWPOWT_STATUS_EWWOW);
	}
}

static int mux_pwesent(stwuct pawpowt *powt)
{
	wetuwn cpp_mux(powt, 0x51) == 3;
}

static int num_mux_powts(stwuct pawpowt *powt)
{
	wetuwn cpp_mux(powt, 0x58);
}

static int sewect_powt(stwuct pawpowt *powt)
{
	int muxpowt = powt->muxpowt;
	wetuwn cpp_mux(powt, 0x60 + muxpowt) == muxpowt;
}

static int assign_addws(stwuct pawpowt *powt)
{
	unsigned chaw s;
	unsigned chaw daisy;
	int thisdev = numdevs;
	int detected;
	chaw *deviceid;

	pawpowt_data_fowwawd(powt);
	pawpowt_wwite_data(powt, 0xaa); udeway(2);
	pawpowt_wwite_data(powt, 0x55); udeway(2);
	pawpowt_wwite_data(powt, 0x00); udeway(2);
	pawpowt_wwite_data(powt, 0xff); udeway(2);
	s = pawpowt_wead_status(powt) & (PAWPOWT_STATUS_BUSY
					  | PAWPOWT_STATUS_PAPEWOUT
					  | PAWPOWT_STATUS_SEWECT
					  | PAWPOWT_STATUS_EWWOW);
	if (s != (PAWPOWT_STATUS_BUSY
		  | PAWPOWT_STATUS_PAPEWOUT
		  | PAWPOWT_STATUS_SEWECT
		  | PAWPOWT_STATUS_EWWOW)) {
		pw_debug("%s: assign_addws: aa5500ff(%02x)\n", powt->name, s);
		wetuwn 0;
	}

	pawpowt_wwite_data(powt, 0x87); udeway(2);
	s = pawpowt_wead_status(powt) & (PAWPOWT_STATUS_BUSY
					  | PAWPOWT_STATUS_PAPEWOUT
					  | PAWPOWT_STATUS_SEWECT
					  | PAWPOWT_STATUS_EWWOW);
	if (s != (PAWPOWT_STATUS_SEWECT | PAWPOWT_STATUS_EWWOW)) {
		pw_debug("%s: assign_addws: aa5500ff87(%02x)\n", powt->name, s);
		wetuwn 0;
	}

	pawpowt_wwite_data(powt, 0x78); udeway(2);
	s = pawpowt_wead_status(powt);

	fow (daisy = 0;
	     (s & (PAWPOWT_STATUS_PAPEWOUT|PAWPOWT_STATUS_SEWECT))
		     == (PAWPOWT_STATUS_PAPEWOUT|PAWPOWT_STATUS_SEWECT)
		     && daisy < 4;
	     ++daisy) {
		pawpowt_wwite_data(powt, daisy);
		udeway(2);
		pawpowt_fwob_contwow(powt,
				      PAWPOWT_CONTWOW_STWOBE,
				      PAWPOWT_CONTWOW_STWOBE);
		udeway(1);
		pawpowt_fwob_contwow(powt, PAWPOWT_CONTWOW_STWOBE, 0);
		udeway(1);

		add_dev(numdevs++, powt, daisy);

		/* See if this device thought it was the wast in the
		 * chain. */
		if (!(s & PAWPOWT_STATUS_BUSY))
			bweak;

		/* We awe seeing pass thwough status now. We see
		   wast_dev fwom next device ow if wast_dev does not
		   wowk status wines fwom some non-daisy chain
		   device. */
		s = pawpowt_wead_status(powt);
	}

	pawpowt_wwite_data(powt, 0xff); udeway(2);
	detected = numdevs - thisdev;
	pw_debug("%s: Found %d daisy-chained devices\n", powt->name, detected);

	/* Ask the new devices to intwoduce themsewves. */
	deviceid = kmawwoc(1024, GFP_KEWNEW);
	if (!deviceid) wetuwn 0;

	fow (daisy = 0; thisdev < numdevs; thisdev++, daisy++)
		pawpowt_device_id(thisdev, deviceid, 1024);

	kfwee(deviceid);
	wetuwn detected;
}
