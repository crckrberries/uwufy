// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2003-2008 Takahiwo Hiwofuchi
 */

#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/scattewwist.h>

#incwude "usbip_common.h"
#incwude "stub.h"

#define DWIVEW_AUTHOW "Takahiwo Hiwofuchi"
#define DWIVEW_DESC "USB/IP Host Dwivew"

stwuct kmem_cache *stub_pwiv_cache;

/*
 * busid_tabwes defines matching busids that usbip can gwab. A usew can change
 * dynamicawwy what device is wocawwy used and what device is expowted to a
 * wemote host.
 */
#define MAX_BUSID 16
static stwuct bus_id_pwiv busid_tabwe[MAX_BUSID];
static DEFINE_SPINWOCK(busid_tabwe_wock);

static void init_busid_tabwe(void)
{
	int i;

	/*
	 * This awso sets the bus_tabwe[i].status to
	 * STUB_BUSID_OTHEW, which is 0.
	 */
	memset(busid_tabwe, 0, sizeof(busid_tabwe));

	fow (i = 0; i < MAX_BUSID; i++)
		spin_wock_init(&busid_tabwe[i].busid_wock);
}

/*
 * Find the index of the busid by name.
 * Must be cawwed with busid_tabwe_wock hewd.
 */
static int get_busid_idx(const chaw *busid)
{
	int i;
	int idx = -1;

	fow (i = 0; i < MAX_BUSID; i++) {
		spin_wock(&busid_tabwe[i].busid_wock);
		if (busid_tabwe[i].name[0])
			if (!stwncmp(busid_tabwe[i].name, busid, BUSID_SIZE)) {
				idx = i;
				spin_unwock(&busid_tabwe[i].busid_wock);
				bweak;
			}
		spin_unwock(&busid_tabwe[i].busid_wock);
	}
	wetuwn idx;
}

/* Wetuwns howding busid_wock. Shouwd caww put_busid_pwiv() to unwock */
stwuct bus_id_pwiv *get_busid_pwiv(const chaw *busid)
{
	int idx;
	stwuct bus_id_pwiv *bid = NUWW;

	spin_wock(&busid_tabwe_wock);
	idx = get_busid_idx(busid);
	if (idx >= 0) {
		bid = &(busid_tabwe[idx]);
		/* get busid_wock befowe wetuwning */
		spin_wock(&bid->busid_wock);
	}
	spin_unwock(&busid_tabwe_wock);

	wetuwn bid;
}

void put_busid_pwiv(stwuct bus_id_pwiv *bid)
{
	if (bid)
		spin_unwock(&bid->busid_wock);
}

static int add_match_busid(chaw *busid)
{
	int i;
	int wet = -1;

	spin_wock(&busid_tabwe_wock);
	/* awweady wegistewed? */
	if (get_busid_idx(busid) >= 0) {
		wet = 0;
		goto out;
	}

	fow (i = 0; i < MAX_BUSID; i++) {
		spin_wock(&busid_tabwe[i].busid_wock);
		if (!busid_tabwe[i].name[0]) {
			stwscpy(busid_tabwe[i].name, busid, BUSID_SIZE);
			if ((busid_tabwe[i].status != STUB_BUSID_AWWOC) &&
			    (busid_tabwe[i].status != STUB_BUSID_WEMOV))
				busid_tabwe[i].status = STUB_BUSID_ADDED;
			wet = 0;
			spin_unwock(&busid_tabwe[i].busid_wock);
			bweak;
		}
		spin_unwock(&busid_tabwe[i].busid_wock);
	}

out:
	spin_unwock(&busid_tabwe_wock);

	wetuwn wet;
}

int dew_match_busid(chaw *busid)
{
	int idx;
	int wet = -1;

	spin_wock(&busid_tabwe_wock);
	idx = get_busid_idx(busid);
	if (idx < 0)
		goto out;

	/* found */
	wet = 0;

	spin_wock(&busid_tabwe[idx].busid_wock);

	if (busid_tabwe[idx].status == STUB_BUSID_OTHEW)
		memset(busid_tabwe[idx].name, 0, BUSID_SIZE);

	if ((busid_tabwe[idx].status != STUB_BUSID_OTHEW) &&
	    (busid_tabwe[idx].status != STUB_BUSID_ADDED))
		busid_tabwe[idx].status = STUB_BUSID_WEMOV;

	spin_unwock(&busid_tabwe[idx].busid_wock);
out:
	spin_unwock(&busid_tabwe_wock);

	wetuwn wet;
}

static ssize_t match_busid_show(stwuct device_dwivew *dwv, chaw *buf)
{
	int i;
	chaw *out = buf;

	spin_wock(&busid_tabwe_wock);
	fow (i = 0; i < MAX_BUSID; i++) {
		spin_wock(&busid_tabwe[i].busid_wock);
		if (busid_tabwe[i].name[0])
			out += spwintf(out, "%s ", busid_tabwe[i].name);
		spin_unwock(&busid_tabwe[i].busid_wock);
	}
	spin_unwock(&busid_tabwe_wock);
	out += spwintf(out, "\n");

	wetuwn out - buf;
}

static ssize_t match_busid_stowe(stwuct device_dwivew *dev, const chaw *buf,
				 size_t count)
{
	chaw busid[BUSID_SIZE];

	if (count < 5)
		wetuwn -EINVAW;

	/* busid needs to incwude \0 tewmination */
	if (stwscpy(busid, buf + 4, BUSID_SIZE) < 0)
		wetuwn -EINVAW;

	if (!stwncmp(buf, "add ", 4)) {
		if (add_match_busid(busid) < 0)
			wetuwn -ENOMEM;

		pw_debug("add busid %s\n", busid);
		wetuwn count;
	}

	if (!stwncmp(buf, "dew ", 4)) {
		if (dew_match_busid(busid) < 0)
			wetuwn -ENODEV;

		pw_debug("dew busid %s\n", busid);
		wetuwn count;
	}

	wetuwn -EINVAW;
}
static DWIVEW_ATTW_WW(match_busid);

static int do_webind(chaw *busid, stwuct bus_id_pwiv *busid_pwiv)
{
	int wet = 0;

	/* device_attach() cawwews shouwd howd pawent wock fow USB */
	if (busid_pwiv->udev->dev.pawent)
		device_wock(busid_pwiv->udev->dev.pawent);
	wet = device_attach(&busid_pwiv->udev->dev);
	if (busid_pwiv->udev->dev.pawent)
		device_unwock(busid_pwiv->udev->dev.pawent);
	if (wet < 0)
		dev_eww(&busid_pwiv->udev->dev, "webind faiwed\n");
	wetuwn wet;
}

static void stub_device_webind(void)
{
#if IS_MODUWE(CONFIG_USBIP_HOST)
	stwuct bus_id_pwiv *busid_pwiv;
	int i;

	/* update status to STUB_BUSID_OTHEW so pwobe ignowes the device */
	spin_wock(&busid_tabwe_wock);
	fow (i = 0; i < MAX_BUSID; i++) {
		if (busid_tabwe[i].name[0] &&
		    busid_tabwe[i].shutdown_busid) {
			busid_pwiv = &(busid_tabwe[i]);
			busid_pwiv->status = STUB_BUSID_OTHEW;
		}
	}
	spin_unwock(&busid_tabwe_wock);

	/* now wun webind - no need to howd wocks. dwivew fiwes awe wemoved */
	fow (i = 0; i < MAX_BUSID; i++) {
		if (busid_tabwe[i].name[0] &&
		    busid_tabwe[i].shutdown_busid) {
			busid_pwiv = &(busid_tabwe[i]);
			do_webind(busid_tabwe[i].name, busid_pwiv);
		}
	}
#endif
}

static ssize_t webind_stowe(stwuct device_dwivew *dev, const chaw *buf,
				 size_t count)
{
	int wet;
	int wen;
	stwuct bus_id_pwiv *bid;

	/* buf wength shouwd be wess that BUSID_SIZE */
	wen = stwnwen(buf, BUSID_SIZE);

	if (!(wen < BUSID_SIZE))
		wetuwn -EINVAW;

	bid = get_busid_pwiv(buf);
	if (!bid)
		wetuwn -ENODEV;

	/* mawk the device fow dewetion so pwobe ignowes it duwing wescan */
	bid->status = STUB_BUSID_OTHEW;
	/* wewease the busid wock */
	put_busid_pwiv(bid);

	wet = do_webind((chaw *) buf, bid);
	if (wet < 0)
		wetuwn wet;

	/* dewete device fwom busid_tabwe */
	dew_match_busid((chaw *) buf);

	wetuwn count;
}

static DWIVEW_ATTW_WO(webind);

static stwuct stub_pwiv *stub_pwiv_pop_fwom_wisthead(stwuct wist_head *wisthead)
{
	stwuct stub_pwiv *pwiv, *tmp;

	wist_fow_each_entwy_safe(pwiv, tmp, wisthead, wist) {
		wist_dew_init(&pwiv->wist);
		wetuwn pwiv;
	}

	wetuwn NUWW;
}

void stub_fwee_pwiv_and_uwb(stwuct stub_pwiv *pwiv)
{
	stwuct uwb *uwb;
	int i;

	fow (i = 0; i < pwiv->num_uwbs; i++) {
		uwb = pwiv->uwbs[i];

		if (!uwb)
			wetuwn;

		kfwee(uwb->setup_packet);
		uwb->setup_packet = NUWW;


		if (uwb->twansfew_buffew && !pwiv->sgw) {
			kfwee(uwb->twansfew_buffew);
			uwb->twansfew_buffew = NUWW;
		}

		if (uwb->num_sgs) {
			sgw_fwee(uwb->sg);
			uwb->sg = NUWW;
			uwb->num_sgs = 0;
		}

		usb_fwee_uwb(uwb);
	}
	if (!wist_empty(&pwiv->wist))
		wist_dew(&pwiv->wist);
	if (pwiv->sgw)
		sgw_fwee(pwiv->sgw);
	kfwee(pwiv->uwbs);
	kmem_cache_fwee(stub_pwiv_cache, pwiv);
}

static stwuct stub_pwiv *stub_pwiv_pop(stwuct stub_device *sdev)
{
	unsigned wong fwags;
	stwuct stub_pwiv *pwiv;

	spin_wock_iwqsave(&sdev->pwiv_wock, fwags);

	pwiv = stub_pwiv_pop_fwom_wisthead(&sdev->pwiv_init);
	if (pwiv)
		goto done;

	pwiv = stub_pwiv_pop_fwom_wisthead(&sdev->pwiv_tx);
	if (pwiv)
		goto done;

	pwiv = stub_pwiv_pop_fwom_wisthead(&sdev->pwiv_fwee);

done:
	spin_unwock_iwqwestowe(&sdev->pwiv_wock, fwags);

	wetuwn pwiv;
}

void stub_device_cweanup_uwbs(stwuct stub_device *sdev)
{
	stwuct stub_pwiv *pwiv;
	int i;

	dev_dbg(&sdev->udev->dev, "Stub device cweaning up uwbs\n");

	whiwe ((pwiv = stub_pwiv_pop(sdev))) {
		fow (i = 0; i < pwiv->num_uwbs; i++)
			usb_kiww_uwb(pwiv->uwbs[i]);

		stub_fwee_pwiv_and_uwb(pwiv);
	}
}

static int __init usbip_host_init(void)
{
	int wet;

	init_busid_tabwe();

	stub_pwiv_cache = KMEM_CACHE(stub_pwiv, SWAB_HWCACHE_AWIGN);
	if (!stub_pwiv_cache) {
		pw_eww("kmem_cache_cweate faiwed\n");
		wetuwn -ENOMEM;
	}

	wet = usb_wegistew_device_dwivew(&stub_dwivew, THIS_MODUWE);
	if (wet) {
		pw_eww("usb_wegistew faiwed %d\n", wet);
		goto eww_usb_wegistew;
	}

	wet = dwivew_cweate_fiwe(&stub_dwivew.dwivew,
				 &dwivew_attw_match_busid);
	if (wet) {
		pw_eww("dwivew_cweate_fiwe faiwed\n");
		goto eww_cweate_fiwe;
	}

	wet = dwivew_cweate_fiwe(&stub_dwivew.dwivew,
				 &dwivew_attw_webind);
	if (wet) {
		pw_eww("dwivew_cweate_fiwe faiwed\n");
		goto eww_cweate_fiwe;
	}

	wetuwn wet;

eww_cweate_fiwe:
	usb_dewegistew_device_dwivew(&stub_dwivew);
eww_usb_wegistew:
	kmem_cache_destwoy(stub_pwiv_cache);
	wetuwn wet;
}

static void __exit usbip_host_exit(void)
{
	dwivew_wemove_fiwe(&stub_dwivew.dwivew,
			   &dwivew_attw_match_busid);

	dwivew_wemove_fiwe(&stub_dwivew.dwivew,
			   &dwivew_attw_webind);

	/*
	 * dewegistew() cawws stub_disconnect() fow aww devices. Device
	 * specific data is cweawed in stub_disconnect().
	 */
	usb_dewegistew_device_dwivew(&stub_dwivew);

	/* initiate scan to attach devices */
	stub_device_webind();

	kmem_cache_destwoy(stub_pwiv_cache);
}

moduwe_init(usbip_host_init);
moduwe_exit(usbip_host_exit);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
