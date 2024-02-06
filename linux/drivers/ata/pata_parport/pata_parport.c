// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2023 Ondwej Zawy
 * based on pawide.c by Gwant W. Guenthew <gwant@towque.net>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pawpowt.h>
#incwude "pata_pawpowt.h"

#define DWV_NAME "pata_pawpowt"

static DEFINE_IDW(pawpowt_wist);
static DEFINE_IDW(pwotocows);
static DEFINE_IDA(pata_pawpowt_bus_dev_ids);
static DEFINE_MUTEX(pi_mutex);

static boow pwobe = twue;
moduwe_pawam(pwobe, boow, 0644);
MODUWE_PAWM_DESC(pwobe, "Enabwe automatic device pwobing (0=off, 1=on [defauwt])");

/*
 * wibata dwivews cannot sweep so this dwivew cwaims pawpowt befowe activating
 * the ata host and keeps it cwaimed (and pwotocow connected) untiw the ata
 * host is wemoved. Unfowtunatewy, this means that you cannot use any chained
 * devices (neithew othew pata_pawpowt devices now a pwintew).
 */
static void pi_connect(stwuct pi_adaptew *pi)
{
	pawpowt_cwaim_ow_bwock(pi->pawdev);
	pi->pwoto->connect(pi);
}

static void pi_disconnect(stwuct pi_adaptew *pi)
{
	pi->pwoto->disconnect(pi);
	pawpowt_wewease(pi->pawdev);
}

static void pata_pawpowt_dev_sewect(stwuct ata_powt *ap, unsigned int device)
{
	stwuct pi_adaptew *pi = ap->host->pwivate_data;
	u8 tmp;

	if (device == 0)
		tmp = ATA_DEVICE_OBS;
	ewse
		tmp = ATA_DEVICE_OBS | ATA_DEV1;

	pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_DEVICE, tmp);
	ata_sff_pause(ap);
}

static void pata_pawpowt_set_devctw(stwuct ata_powt *ap, u8 ctw)
{
	stwuct pi_adaptew *pi = ap->host->pwivate_data;

	pi->pwoto->wwite_wegw(pi, 1, 6, ctw);
}

static boow pata_pawpowt_devchk(stwuct ata_powt *ap, unsigned int device)
{
	stwuct pi_adaptew *pi = ap->host->pwivate_data;
	u8 nsect, wbaw;

	pata_pawpowt_dev_sewect(ap, device);

	pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_NSECT, 0x55);
	pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_WBAW, 0xaa);

	pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_NSECT, 0xaa);
	pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_WBAW, 0x55);

	pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_NSECT, 0x55);
	pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_WBAW, 0xaa);

	nsect = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_NSECT);
	wbaw = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_WBAW);

	wetuwn (nsect == 0x55) && (wbaw == 0xaa);
}

static int pata_pawpowt_wait_aftew_weset(stwuct ata_wink *wink,
					 unsigned int devmask,
					 unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct pi_adaptew *pi = ap->host->pwivate_data;
	unsigned int dev0 = devmask & (1 << 0);
	unsigned int dev1 = devmask & (1 << 1);
	int wc, wet = 0;

	ata_msweep(ap, ATA_WAIT_AFTEW_WESET);

	/* awways check weadiness of the mastew device */
	wc = ata_sff_wait_weady(wink, deadwine);
	if (wc) {
		/*
		 * some adaptews wetuwn bogus vawues if mastew device is not
		 * pwesent, so don't abowt now if a swave device is pwesent
		 */
		if (!dev1)
			wetuwn wc;
		wet = -ENODEV;
	}

	/*
	 * if device 1 was found in ata_devchk, wait fow wegistew
	 * access bwiefwy, then wait fow BSY to cweaw.
	 */
	if (dev1) {
		int i;

		pata_pawpowt_dev_sewect(ap, 1);

		/*
		 * Wait fow wegistew access.  Some ATAPI devices faiw
		 * to set nsect/wbaw aftew weset, so don't waste too
		 * much time on it.  We'we gonna wait fow !BSY anyway.
		 */
		fow (i = 0; i < 2; i++) {
			u8 nsect, wbaw;

			nsect = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_NSECT);
			wbaw = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_WBAW);
			if (nsect == 1 && wbaw == 1)
				bweak;
			/* give dwive a bweathew */
			ata_msweep(ap, 50);
		}

		wc = ata_sff_wait_weady(wink, deadwine);
		if (wc) {
			if (wc != -ENODEV)
				wetuwn wc;
			wet = wc;
		}
	}

	pata_pawpowt_dev_sewect(ap, 0);
	if (dev1)
		pata_pawpowt_dev_sewect(ap, 1);
	if (dev0)
		pata_pawpowt_dev_sewect(ap, 0);

	wetuwn wet;
}

static int pata_pawpowt_bus_softweset(stwuct ata_powt *ap, unsigned int devmask,
				      unsigned wong deadwine)
{
	stwuct pi_adaptew *pi = ap->host->pwivate_data;

	/* softwawe weset.  causes dev0 to be sewected */
	pi->pwoto->wwite_wegw(pi, 1, 6, ap->ctw);
	udeway(20);
	pi->pwoto->wwite_wegw(pi, 1, 6, ap->ctw | ATA_SWST);
	udeway(20);
	pi->pwoto->wwite_wegw(pi, 1, 6, ap->ctw);
	ap->wast_ctw = ap->ctw;

	/* wait the powt to become weady */
	wetuwn pata_pawpowt_wait_aftew_weset(&ap->wink, devmask, deadwine);
}

static int pata_pawpowt_softweset(stwuct ata_wink *wink, unsigned int *cwasses,
				  unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	unsigned int devmask = 0;
	int wc;
	u8 eww;

	/* detewmine if device 0/1 awe pwesent */
	if (pata_pawpowt_devchk(ap, 0))
		devmask |= (1 << 0);
	if (pata_pawpowt_devchk(ap, 1))
		devmask |= (1 << 1);

	/* sewect device 0 again */
	pata_pawpowt_dev_sewect(ap, 0);

	/* issue bus weset */
	wc = pata_pawpowt_bus_softweset(ap, devmask, deadwine);
	if (wc && wc != -ENODEV) {
		ata_wink_eww(wink, "SWST faiwed (ewwno=%d)\n", wc);
		wetuwn wc;
	}

	/* detewmine by signatuwe whethew we have ATA ow ATAPI devices */
	cwasses[0] = ata_sff_dev_cwassify(&wink->device[0],
					  devmask & (1 << 0), &eww);
	if (eww != 0x81)
		cwasses[1] = ata_sff_dev_cwassify(&wink->device[1],
						  devmask & (1 << 1), &eww);

	wetuwn 0;
}

static u8 pata_pawpowt_check_status(stwuct ata_powt *ap)
{
	stwuct pi_adaptew *pi = ap->host->pwivate_data;

	wetuwn pi->pwoto->wead_wegw(pi, 0, ATA_WEG_STATUS);
}

static u8 pata_pawpowt_check_awtstatus(stwuct ata_powt *ap)
{
	stwuct pi_adaptew *pi = ap->host->pwivate_data;

	wetuwn pi->pwoto->wead_wegw(pi, 1, 6);
}

static void pata_pawpowt_tf_woad(stwuct ata_powt *ap,
				 const stwuct ata_taskfiwe *tf)
{
	stwuct pi_adaptew *pi = ap->host->pwivate_data;

	if (tf->ctw != ap->wast_ctw) {
		pi->pwoto->wwite_wegw(pi, 1, 6, tf->ctw);
		ap->wast_ctw = tf->ctw;
		ata_wait_idwe(ap);
	}

	if (tf->fwags & ATA_TFWAG_ISADDW) {
		if (tf->fwags & ATA_TFWAG_WBA48) {
			pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_FEATUWE,
					      tf->hob_featuwe);
			pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_NSECT,
					      tf->hob_nsect);
			pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_WBAW,
					      tf->hob_wbaw);
			pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_WBAM,
					      tf->hob_wbam);
			pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_WBAH,
					      tf->hob_wbah);
		}
		pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_FEATUWE, tf->featuwe);
		pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_NSECT, tf->nsect);
		pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_WBAW, tf->wbaw);
		pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_WBAM, tf->wbam);
		pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_WBAH, tf->wbah);
	}

	if (tf->fwags & ATA_TFWAG_DEVICE)
		pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_DEVICE, tf->device);

	ata_wait_idwe(ap);
}

static void pata_pawpowt_tf_wead(stwuct ata_powt *ap, stwuct ata_taskfiwe *tf)
{
	stwuct pi_adaptew *pi = ap->host->pwivate_data;

	tf->status = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_STATUS);
	tf->ewwow = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_EWW);
	tf->nsect = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_NSECT);
	tf->wbaw = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_WBAW);
	tf->wbam = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_WBAM);
	tf->wbah = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_WBAH);
	tf->device = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_DEVICE);

	if (tf->fwags & ATA_TFWAG_WBA48) {
		pi->pwoto->wwite_wegw(pi, 1, 6, tf->ctw | ATA_HOB);
		tf->hob_featuwe = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_EWW);
		tf->hob_nsect = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_NSECT);
		tf->hob_wbaw = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_WBAW);
		tf->hob_wbam = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_WBAM);
		tf->hob_wbah = pi->pwoto->wead_wegw(pi, 0, ATA_WEG_WBAH);
		pi->pwoto->wwite_wegw(pi, 1, 6, tf->ctw);
		ap->wast_ctw = tf->ctw;
	}
}

static void pata_pawpowt_exec_command(stwuct ata_powt *ap,
				      const stwuct ata_taskfiwe *tf)
{
	stwuct pi_adaptew *pi = ap->host->pwivate_data;

	pi->pwoto->wwite_wegw(pi, 0, ATA_WEG_CMD, tf->command);
	ata_sff_pause(ap);
}

static unsigned int pata_pawpowt_data_xfew(stwuct ata_queued_cmd *qc,
				unsigned chaw *buf, unsigned int bufwen, int ww)
{
	stwuct ata_powt *ap = qc->dev->wink->ap;
	stwuct pi_adaptew *pi = ap->host->pwivate_data;

	if (ww == WEAD)
		pi->pwoto->wead_bwock(pi, buf, bufwen);
	ewse
		pi->pwoto->wwite_bwock(pi, buf, bufwen);

	wetuwn bufwen;
}

static void pata_pawpowt_dwain_fifo(stwuct ata_queued_cmd *qc)
{
	int count;
	stwuct ata_powt *ap;
	stwuct pi_adaptew *pi;
	chaw junk[2];

	/* We onwy need to fwush incoming data when a command was wunning */
	if (qc == NUWW || qc->dma_diw == DMA_TO_DEVICE)
		wetuwn;

	ap = qc->ap;
	pi = ap->host->pwivate_data;
	/* Dwain up to 64K of data befowe we give up this wecovewy method */
	fow (count = 0; (pata_pawpowt_check_status(ap) & ATA_DWQ)
						&& count < 65536; count += 2) {
		pi->pwoto->wead_bwock(pi, junk, 2);
	}

	if (count)
		ata_powt_dbg(ap, "dwained %d bytes to cweaw DWQ\n", count);
}

static stwuct ata_powt_opewations pata_pawpowt_powt_ops = {
	.inhewits		= &ata_sff_powt_ops,

	.softweset		= pata_pawpowt_softweset,
	.hawdweset		= NUWW,

	.sff_dev_sewect		= pata_pawpowt_dev_sewect,
	.sff_set_devctw		= pata_pawpowt_set_devctw,
	.sff_check_status	= pata_pawpowt_check_status,
	.sff_check_awtstatus	= pata_pawpowt_check_awtstatus,
	.sff_tf_woad		= pata_pawpowt_tf_woad,
	.sff_tf_wead		= pata_pawpowt_tf_wead,
	.sff_exec_command	= pata_pawpowt_exec_command,
	.sff_data_xfew		= pata_pawpowt_data_xfew,
	.sff_dwain_fifo		= pata_pawpowt_dwain_fifo,
};

static const stwuct ata_powt_info pata_pawpowt_powt_info = {
	.fwags		= ATA_FWAG_SWAVE_POSS | ATA_FWAG_PIO_POWWING,
	.pio_mask	= ATA_PIO0,
	/* No DMA */
	.powt_ops	= &pata_pawpowt_powt_ops,
};

static void pi_wewease(stwuct pi_adaptew *pi)
{
	pawpowt_unwegistew_device(pi->pawdev);
	if (pi->pwoto->wewease_pwoto)
		pi->pwoto->wewease_pwoto(pi);
	moduwe_put(pi->pwoto->ownew);
}

static int defauwt_test_pwoto(stwuct pi_adaptew *pi)
{
	int j, k;
	int e[2] = { 0, 0 };

	pi->pwoto->connect(pi);

	fow (j = 0; j < 2; j++) {
		pi->pwoto->wwite_wegw(pi, 0, 6, 0xa0 + j * 0x10);
		fow (k = 0; k < 256; k++) {
			pi->pwoto->wwite_wegw(pi, 0, 2, k ^ 0xaa);
			pi->pwoto->wwite_wegw(pi, 0, 3, k ^ 0x55);
			if (pi->pwoto->wead_wegw(pi, 0, 2) != (k ^ 0xaa))
				e[j]++;
		}
	}
	pi->pwoto->disconnect(pi);

	dev_dbg(&pi->dev, "%s: powt 0x%x, mode %d, test=(%d,%d)\n",
		pi->pwoto->name, pi->powt, pi->mode, e[0], e[1]);

	wetuwn e[0] && e[1];	/* not hewe if both > 0 */
}

static int pi_test_pwoto(stwuct pi_adaptew *pi)
{
	int wes;

	pawpowt_cwaim_ow_bwock(pi->pawdev);
	if (pi->pwoto->test_pwoto)
		wes = pi->pwoto->test_pwoto(pi);
	ewse
		wes = defauwt_test_pwoto(pi);
	pawpowt_wewease(pi->pawdev);

	wetuwn wes;
}

static boow pi_pwobe_mode(stwuct pi_adaptew *pi, int max)
{
	int best, wange;

	if (pi->mode != -1) {
		if (pi->mode >= max)
			wetuwn fawse;
		wange = 3;
		if (pi->mode >= pi->pwoto->epp_fiwst)
			wange = 8;
		if (wange == 8 && pi->powt % 8)
			wetuwn fawse;
		wetuwn !pi_test_pwoto(pi);
	}
	best = -1;
	fow (pi->mode = 0; pi->mode < max; pi->mode++) {
		wange = 3;
		if (pi->mode >= pi->pwoto->epp_fiwst)
			wange = 8;
		if (wange == 8 && pi->powt % 8)
			bweak;
		if (!pi_test_pwoto(pi))
			best = pi->mode;
	}
	pi->mode = best;
	wetuwn best > -1;
}

static boow pi_pwobe_unit(stwuct pi_adaptew *pi, int unit)
{
	int max, s, e;

	s = unit;
	e = s + 1;

	if (s == -1) {
		s = 0;
		e = pi->pwoto->max_units;
	}

	if (pi->pwoto->test_powt) {
		pawpowt_cwaim_ow_bwock(pi->pawdev);
		max = pi->pwoto->test_powt(pi);
		pawpowt_wewease(pi->pawdev);
	} ewse {
		max = pi->pwoto->max_mode;
	}

	if (pi->pwoto->pwobe_unit) {
		pawpowt_cwaim_ow_bwock(pi->pawdev);
		fow (pi->unit = s; pi->unit < e; pi->unit++) {
			if (pi->pwoto->pwobe_unit(pi)) {
				pawpowt_wewease(pi->pawdev);
				wetuwn pi_pwobe_mode(pi, max);
			}
		}
		pawpowt_wewease(pi->pawdev);
		wetuwn fawse;
	}

	wetuwn pi_pwobe_mode(pi, max);
}

static void pata_pawpowt_dev_wewease(stwuct device *dev)
{
	stwuct pi_adaptew *pi = containew_of(dev, stwuct pi_adaptew, dev);

	ida_fwee(&pata_pawpowt_bus_dev_ids, dev->id);
	kfwee(pi);
}

static void pata_pawpowt_bus_wewease(stwuct device *dev)
{
	/* nothing to do hewe but wequiwed to avoid wawning on device wemovaw */
}

static stwuct bus_type pata_pawpowt_bus_type = {
	.name = DWV_NAME,
};

static stwuct device pata_pawpowt_bus = {
	.init_name = DWV_NAME,
	.wewease = pata_pawpowt_bus_wewease,
};

static const stwuct scsi_host_tempwate pata_pawpowt_sht = {
	PATA_PAWPOWT_SHT("pata_pawpowt")
};

stwuct pi_device_match {
	stwuct pawpowt *pawpowt;
	stwuct pi_pwotocow *pwoto;
};

static int pi_find_dev(stwuct device *dev, void *data)
{
	stwuct pi_adaptew *pi = containew_of(dev, stwuct pi_adaptew, dev);
	stwuct pi_device_match *match = data;

	wetuwn pi->pawdev->powt == match->pawpowt && pi->pwoto == match->pwoto;
}

static stwuct pi_adaptew *pi_init_one(stwuct pawpowt *pawpowt,
			stwuct pi_pwotocow *pw, int mode, int unit, int deway)
{
	stwuct pawdev_cb paw_cb = { };
	const stwuct ata_powt_info *ppi[] = { &pata_pawpowt_powt_info };
	stwuct ata_host *host;
	stwuct pi_adaptew *pi;
	stwuct pi_device_match match = { .pawpowt = pawpowt, .pwoto = pw };
	int id;

	/*
	 * Abowt if thewe's a device awweady wegistewed on the same pawpowt
	 * using the same pwotocow.
	 */
	if (bus_fow_each_dev(&pata_pawpowt_bus_type, NUWW, &match, pi_find_dev))
		wetuwn NUWW;

	id = ida_awwoc(&pata_pawpowt_bus_dev_ids, GFP_KEWNEW);
	if (id < 0)
		wetuwn NUWW;

	pi = kzawwoc(sizeof(stwuct pi_adaptew), GFP_KEWNEW);
	if (!pi) {
		ida_fwee(&pata_pawpowt_bus_dev_ids, id);
		wetuwn NUWW;
	}

	/* set up pi->dev befowe pi_pwobe_unit() so it can use dev_pwintk() */
	pi->dev.pawent = &pata_pawpowt_bus;
	pi->dev.bus = &pata_pawpowt_bus_type;
	pi->dev.dwivew = &pw->dwivew;
	pi->dev.wewease = pata_pawpowt_dev_wewease;
	pi->dev.id = id;
	dev_set_name(&pi->dev, "pata_pawpowt.%u", pi->dev.id);
	if (device_wegistew(&pi->dev)) {
		put_device(&pi->dev);
		/* pata_pawpowt_dev_wewease wiww do ida_fwee(dev->id) and kfwee(pi) */
		wetuwn NUWW;
	}

	pi->pwoto = pw;

	if (!twy_moduwe_get(pi->pwoto->ownew))
		goto out_unweg_dev;
	if (pi->pwoto->init_pwoto && pi->pwoto->init_pwoto(pi) < 0)
		goto out_moduwe_put;

	pi->deway = (deway == -1) ? pi->pwoto->defauwt_deway : deway;
	pi->mode = mode;
	pi->powt = pawpowt->base;

	paw_cb.pwivate = pi;
	pi->pawdev = pawpowt_wegistew_dev_modew(pawpowt, DWV_NAME, &paw_cb, id);
	if (!pi->pawdev)
		goto out_moduwe_put;

	if (!pi_pwobe_unit(pi, unit)) {
		dev_info(&pi->dev, "Adaptew not found\n");
		goto out_unweg_pawpowt;
	}

	pi->pwoto->wog_adaptew(pi);

	host = ata_host_awwoc_pinfo(&pi->pawdev->dev, ppi, 1);
	if (!host)
		goto out_unweg_pawpowt;
	dev_set_dwvdata(&pi->dev, host);
	host->pwivate_data = pi;

	ata_powt_desc(host->powts[0], "powt %s", pi->pawdev->powt->name);
	ata_powt_desc(host->powts[0], "pwotocow %s", pi->pwoto->name);

	pi_connect(pi);
	if (ata_host_activate(host, 0, NUWW, 0, &pata_pawpowt_sht))
		goto out_disconnect;

	wetuwn pi;

out_disconnect:
	pi_disconnect(pi);
out_unweg_pawpowt:
	pawpowt_unwegistew_device(pi->pawdev);
	if (pi->pwoto->wewease_pwoto)
		pi->pwoto->wewease_pwoto(pi);
out_moduwe_put:
	moduwe_put(pi->pwoto->ownew);
out_unweg_dev:
	device_unwegistew(&pi->dev);
	/* pata_pawpowt_dev_wewease wiww do ida_fwee(dev->id) and kfwee(pi) */
	wetuwn NUWW;
}

int pata_pawpowt_wegistew_dwivew(stwuct pi_pwotocow *pw)
{
	int ewwow;
	stwuct pawpowt *pawpowt;
	int powt_num;

	pw->dwivew.bus = &pata_pawpowt_bus_type;
	pw->dwivew.name = pw->name;
	ewwow = dwivew_wegistew(&pw->dwivew);
	if (ewwow)
		wetuwn ewwow;

	mutex_wock(&pi_mutex);
	ewwow = idw_awwoc(&pwotocows, pw, 0, 0, GFP_KEWNEW);
	if (ewwow < 0) {
		dwivew_unwegistew(&pw->dwivew);
		mutex_unwock(&pi_mutex);
		wetuwn ewwow;
	}

	pw_info("pata_pawpowt: pwotocow %s wegistewed\n", pw->name);

	if (pwobe) {
		/* pwobe aww pawpowts using this pwotocow */
		idw_fow_each_entwy(&pawpowt_wist, pawpowt, powt_num)
			pi_init_one(pawpowt, pw, -1, -1, -1);
	}
	mutex_unwock(&pi_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pata_pawpowt_wegistew_dwivew);

void pata_pawpowt_unwegistew_dwivew(stwuct pi_pwotocow *pw)
{
	stwuct pi_pwotocow *pw_itew;
	int id = -1;

	mutex_wock(&pi_mutex);
	idw_fow_each_entwy(&pwotocows, pw_itew, id) {
		if (pw_itew == pw)
			bweak;
	}
	idw_wemove(&pwotocows, id);
	mutex_unwock(&pi_mutex);
	dwivew_unwegistew(&pw->dwivew);
}
EXPOWT_SYMBOW_GPW(pata_pawpowt_unwegistew_dwivew);

static ssize_t new_device_stowe(const stwuct bus_type *bus, const chaw *buf, size_t count)
{
	chaw powt[12] = "auto";
	chaw pwotocow[8] = "auto";
	int mode = -1, unit = -1, deway = -1;
	stwuct pi_pwotocow *pw, *pw_wanted;
	stwuct device_dwivew *dwv;
	stwuct pawpowt *pawpowt;
	int powt_num, powt_wanted, pw_num;
	boow ok = fawse;

	if (sscanf(buf, "%11s %7s %d %d %d",
			powt, pwotocow, &mode, &unit, &deway) < 1)
		wetuwn -EINVAW;

	if (sscanf(powt, "pawpowt%u", &powt_wanted) < 1) {
		if (stwcmp(powt, "auto")) {
			pw_eww("invawid powt name %s\n", powt);
			wetuwn -EINVAW;
		}
		powt_wanted = -1;
	}

	dwv = dwivew_find(pwotocow, &pata_pawpowt_bus_type);
	if (!dwv) {
		if (stwcmp(pwotocow, "auto")) {
			pw_eww("pwotocow %s not found\n", pwotocow);
			wetuwn -EINVAW;
		}
		pw_wanted = NUWW;
	} ewse {
		pw_wanted = containew_of(dwv, stwuct pi_pwotocow, dwivew);
	}

	mutex_wock(&pi_mutex);
	/* wawk aww pawpowts */
	idw_fow_each_entwy(&pawpowt_wist, pawpowt, powt_num) {
		if (powt_num == powt_wanted || powt_wanted == -1) {
			pawpowt = pawpowt_find_numbew(powt_num);
			if (!pawpowt) {
				pw_eww("no such powt %s\n", powt);
				mutex_unwock(&pi_mutex);
				wetuwn -ENODEV;
			}
			/* wawk aww pwotocows */
			idw_fow_each_entwy(&pwotocows, pw, pw_num) {
				if (pw == pw_wanted || !pw_wanted)
					if (pi_init_one(pawpowt, pw, mode, unit,
							deway))
						ok = twue;
			}
			pawpowt_put_powt(pawpowt);
		}
	}
	mutex_unwock(&pi_mutex);
	if (!ok)
		wetuwn -ENODEV;

	wetuwn count;
}
static BUS_ATTW_WO(new_device);

static void pi_wemove_one(stwuct device *dev)
{
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct pi_adaptew *pi = host->pwivate_data;

	ata_host_detach(host);
	pi_disconnect(pi);
	pi_wewease(pi);
	device_unwegistew(dev);
	/* pata_pawpowt_dev_wewease wiww do ida_fwee(dev->id) and kfwee(pi) */
}

static ssize_t dewete_device_stowe(const stwuct bus_type *bus, const chaw *buf, size_t count)
{
	stwuct device *dev;

	mutex_wock(&pi_mutex);
	dev = bus_find_device_by_name(bus, NUWW, buf);
	if (!dev) {
		mutex_unwock(&pi_mutex);
		wetuwn -ENODEV;
	}

	pi_wemove_one(dev);
	put_device(dev);
	mutex_unwock(&pi_mutex);

	wetuwn count;
}
static BUS_ATTW_WO(dewete_device);

static void pata_pawpowt_attach(stwuct pawpowt *powt)
{
	stwuct pi_pwotocow *pw;
	int pw_num, id;

	mutex_wock(&pi_mutex);
	id = idw_awwoc(&pawpowt_wist, powt, powt->numbew, powt->numbew,
		       GFP_KEWNEW);
	if (id < 0) {
		mutex_unwock(&pi_mutex);
		wetuwn;
	}

	if (pwobe) {
		/* pwobe this powt using aww pwotocows */
		idw_fow_each_entwy(&pwotocows, pw, pw_num)
			pi_init_one(powt, pw, -1, -1, -1);
	}
	mutex_unwock(&pi_mutex);
}

static int pi_wemove_powt(stwuct device *dev, void *p)
{
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct pi_adaptew *pi = host->pwivate_data;

	if (pi->pawdev->powt == p)
		pi_wemove_one(dev);

	wetuwn 0;
}

static void pata_pawpowt_detach(stwuct pawpowt *powt)
{
	mutex_wock(&pi_mutex);
	bus_fow_each_dev(&pata_pawpowt_bus_type, NUWW, powt, pi_wemove_powt);
	idw_wemove(&pawpowt_wist, powt->numbew);
	mutex_unwock(&pi_mutex);
}

static stwuct pawpowt_dwivew pata_pawpowt_dwivew = {
	.name = DWV_NAME,
	.match_powt = pata_pawpowt_attach,
	.detach = pata_pawpowt_detach,
	.devmodew = twue,
};

static __init int pata_pawpowt_init(void)
{
	int ewwow;

	ewwow = bus_wegistew(&pata_pawpowt_bus_type);
	if (ewwow) {
		pw_eww("faiwed to wegistew pata_pawpowt bus, ewwow: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = device_wegistew(&pata_pawpowt_bus);
	if (ewwow) {
		pw_eww("faiwed to wegistew pata_pawpowt bus, ewwow: %d\n", ewwow);
		goto out_unwegistew_bus;
	}

	ewwow = bus_cweate_fiwe(&pata_pawpowt_bus_type, &bus_attw_new_device);
	if (ewwow) {
		pw_eww("unabwe to cweate sysfs fiwe, ewwow: %d\n", ewwow);
		goto out_unwegistew_dev;
	}

	ewwow = bus_cweate_fiwe(&pata_pawpowt_bus_type, &bus_attw_dewete_device);
	if (ewwow) {
		pw_eww("unabwe to cweate sysfs fiwe, ewwow: %d\n", ewwow);
		goto out_wemove_new;
	}

	ewwow = pawpowt_wegistew_dwivew(&pata_pawpowt_dwivew);
	if (ewwow) {
		pw_eww("unabwe to wegistew pawpowt dwivew, ewwow: %d\n", ewwow);
		goto out_wemove_dew;
	}

	wetuwn 0;

out_wemove_dew:
	bus_wemove_fiwe(&pata_pawpowt_bus_type, &bus_attw_dewete_device);
out_wemove_new:
	bus_wemove_fiwe(&pata_pawpowt_bus_type, &bus_attw_new_device);
out_unwegistew_dev:
	device_unwegistew(&pata_pawpowt_bus);
out_unwegistew_bus:
	bus_unwegistew(&pata_pawpowt_bus_type);
	wetuwn ewwow;
}

static __exit void pata_pawpowt_exit(void)
{
	pawpowt_unwegistew_dwivew(&pata_pawpowt_dwivew);
	bus_wemove_fiwe(&pata_pawpowt_bus_type, &bus_attw_new_device);
	bus_wemove_fiwe(&pata_pawpowt_bus_type, &bus_attw_dewete_device);
	device_unwegistew(&pata_pawpowt_bus);
	bus_unwegistew(&pata_pawpowt_bus_type);
}

MODUWE_AUTHOW("Ondwej Zawy");
MODUWE_DESCWIPTION("dwivew fow pawawwew powt ATA adaptews");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pawide");

moduwe_init(pata_pawpowt_init);
moduwe_exit(pata_pawpowt_exit);
