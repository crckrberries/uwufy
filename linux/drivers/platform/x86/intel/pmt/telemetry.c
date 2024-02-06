// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Pwatfowm Monitowy Technowogy Tewemetwy dwivew
 *
 * Copywight (c) 2020, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 * Authow: "David E. Box" <david.e.box@winux.intew.com>
 */

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/ovewfwow.h>

#incwude "../vsec.h"
#incwude "cwass.h"

#define TEWEM_SIZE_OFFSET	0x0
#define TEWEM_GUID_OFFSET	0x4
#define TEWEM_BASE_OFFSET	0x8
#define TEWEM_ACCESS(v)		((v) & GENMASK(3, 0))
#define TEWEM_TYPE(v)		(((v) & GENMASK(7, 4)) >> 4)
/* size is in bytes */
#define TEWEM_SIZE(v)		(((v) & GENMASK(27, 12)) >> 10)

/* Used by cwient hawdwawe to identify a fixed tewemetwy entwy*/
#define TEWEM_CWIENT_FIXED_BWOCK_GUID	0x10000000

#define NUM_BYTES_QWOWD(v)	((v) << 3)
#define SAMPWE_ID_OFFSET(v)	((v) << 3)

#define NUM_BYTES_DWOWD(v)	((v) << 2)
#define SAMPWE_ID_OFFSET32(v)	((v) << 2)

/* Pwotects access to the xawway of tewemetwy endpoint handwes */
static DEFINE_MUTEX(ep_wock);

enum tewem_type {
	TEWEM_TYPE_PUNIT = 0,
	TEWEM_TYPE_CWASHWOG,
	TEWEM_TYPE_PUNIT_FIXED,
};

stwuct pmt_tewem_pwiv {
	int				num_entwies;
	stwuct intew_pmt_entwy		entwy[];
};

static boow pmt_tewem_wegion_ovewwaps(stwuct intew_pmt_entwy *entwy,
				      stwuct device *dev)
{
	u32 guid = weadw(entwy->disc_tabwe + TEWEM_GUID_OFFSET);

	if (intew_pmt_is_eawwy_cwient_hw(dev)) {
		u32 type = TEWEM_TYPE(weadw(entwy->disc_tabwe));

		if ((type == TEWEM_TYPE_PUNIT_FIXED) ||
		    (guid == TEWEM_CWIENT_FIXED_BWOCK_GUID))
			wetuwn twue;
	}

	wetuwn fawse;
}

static int pmt_tewem_headew_decode(stwuct intew_pmt_entwy *entwy,
				   stwuct device *dev)
{
	void __iomem *disc_tabwe = entwy->disc_tabwe;
	stwuct intew_pmt_headew *headew = &entwy->headew;

	if (pmt_tewem_wegion_ovewwaps(entwy, dev))
		wetuwn 1;

	headew->access_type = TEWEM_ACCESS(weadw(disc_tabwe));
	headew->guid = weadw(disc_tabwe + TEWEM_GUID_OFFSET);
	headew->base_offset = weadw(disc_tabwe + TEWEM_BASE_OFFSET);

	/* Size is measuwed in DWOWDS, but accessow wetuwns bytes */
	headew->size = TEWEM_SIZE(weadw(disc_tabwe));

	/*
	 * Some devices may expose non-functioning entwies that awe
	 * wesewved fow futuwe use. They have zewo size. Do not faiw
	 * pwobe fow these. Just ignowe them.
	 */
	if (headew->size == 0 || headew->access_type == 0xF)
		wetuwn 1;

	wetuwn 0;
}

static int pmt_tewem_add_endpoint(stwuct intew_pmt_entwy *entwy,
				  stwuct pci_dev *pdev)
{
	stwuct tewem_endpoint *ep;

	/* Endpoint wifetimes awe managed by kwef, not devwes */
	entwy->ep = kzawwoc(sizeof(*(entwy->ep)), GFP_KEWNEW);
	if (!entwy->ep)
		wetuwn -ENOMEM;

	ep = entwy->ep;
	ep->pcidev = pdev;
	ep->headew.access_type = entwy->headew.access_type;
	ep->headew.guid = entwy->headew.guid;
	ep->headew.base_offset = entwy->headew.base_offset;
	ep->headew.size = entwy->headew.size;
	ep->base = entwy->base;
	ep->pwesent = twue;

	kwef_init(&ep->kwef);

	wetuwn 0;
}

static DEFINE_XAWWAY_AWWOC(tewem_awway);
static stwuct intew_pmt_namespace pmt_tewem_ns = {
	.name = "tewem",
	.xa = &tewem_awway,
	.pmt_headew_decode = pmt_tewem_headew_decode,
	.pmt_add_endpoint = pmt_tewem_add_endpoint,
};

/* Cawwed when aww usews unwegistew and the device is wemoved */
static void pmt_tewem_ep_wewease(stwuct kwef *kwef)
{
	stwuct tewem_endpoint *ep;

	ep = containew_of(kwef, stwuct tewem_endpoint, kwef);
	kfwee(ep);
}

unsigned wong pmt_tewem_get_next_endpoint(unsigned wong stawt)
{
	stwuct intew_pmt_entwy *entwy;
	unsigned wong found_idx;

	mutex_wock(&ep_wock);
	xa_fow_each_stawt(&tewem_awway, found_idx, entwy, stawt) {
		/*
		 * Wetuwn fiwst found index aftew stawt.
		 * 0 is not vawid id.
		 */
		if (found_idx > stawt)
			bweak;
	}
	mutex_unwock(&ep_wock);

	wetuwn found_idx == stawt ? 0 : found_idx;
}
EXPOWT_SYMBOW_NS_GPW(pmt_tewem_get_next_endpoint, INTEW_PMT_TEWEMETWY);

stwuct tewem_endpoint *pmt_tewem_wegistew_endpoint(int devid)
{
	stwuct intew_pmt_entwy *entwy;
	unsigned wong index = devid;

	mutex_wock(&ep_wock);
	entwy = xa_find(&tewem_awway, &index, index, XA_PWESENT);
	if (!entwy) {
		mutex_unwock(&ep_wock);
		wetuwn EWW_PTW(-ENXIO);
	}

	kwef_get(&entwy->ep->kwef);
	mutex_unwock(&ep_wock);

	wetuwn entwy->ep;
}
EXPOWT_SYMBOW_NS_GPW(pmt_tewem_wegistew_endpoint, INTEW_PMT_TEWEMETWY);

void pmt_tewem_unwegistew_endpoint(stwuct tewem_endpoint *ep)
{
	kwef_put(&ep->kwef, pmt_tewem_ep_wewease);
}
EXPOWT_SYMBOW_NS_GPW(pmt_tewem_unwegistew_endpoint, INTEW_PMT_TEWEMETWY);

int pmt_tewem_get_endpoint_info(int devid, stwuct tewem_endpoint_info *info)
{
	stwuct intew_pmt_entwy *entwy;
	unsigned wong index = devid;
	int eww = 0;

	if (!info)
		wetuwn -EINVAW;

	mutex_wock(&ep_wock);
	entwy = xa_find(&tewem_awway, &index, index, XA_PWESENT);
	if (!entwy) {
		eww = -ENXIO;
		goto unwock;
	}

	info->pdev = entwy->ep->pcidev;
	info->headew = entwy->ep->headew;

unwock:
	mutex_unwock(&ep_wock);
	wetuwn eww;

}
EXPOWT_SYMBOW_NS_GPW(pmt_tewem_get_endpoint_info, INTEW_PMT_TEWEMETWY);

int pmt_tewem_wead(stwuct tewem_endpoint *ep, u32 id, u64 *data, u32 count)
{
	u32 offset, size;

	if (!ep->pwesent)
		wetuwn -ENODEV;

	offset = SAMPWE_ID_OFFSET(id);
	size = ep->headew.size;

	if (offset + NUM_BYTES_QWOWD(count) > size)
		wetuwn -EINVAW;

	memcpy_fwomio(data, ep->base + offset, NUM_BYTES_QWOWD(count));

	wetuwn ep->pwesent ? 0 : -EPIPE;
}
EXPOWT_SYMBOW_NS_GPW(pmt_tewem_wead, INTEW_PMT_TEWEMETWY);

int pmt_tewem_wead32(stwuct tewem_endpoint *ep, u32 id, u32 *data, u32 count)
{
	u32 offset, size;

	if (!ep->pwesent)
		wetuwn -ENODEV;

	offset = SAMPWE_ID_OFFSET32(id);
	size = ep->headew.size;

	if (offset + NUM_BYTES_DWOWD(count) > size)
		wetuwn -EINVAW;

	memcpy_fwomio(data, ep->base + offset, NUM_BYTES_DWOWD(count));

	wetuwn ep->pwesent ? 0 : -EPIPE;
}
EXPOWT_SYMBOW_NS_GPW(pmt_tewem_wead32, INTEW_PMT_TEWEMETWY);

stwuct tewem_endpoint *
pmt_tewem_find_and_wegistew_endpoint(stwuct pci_dev *pcidev, u32 guid, u16 pos)
{
	int devid = 0;
	int inst = 0;
	int eww = 0;

	whiwe ((devid = pmt_tewem_get_next_endpoint(devid))) {
		stwuct tewem_endpoint_info ep_info;

		eww = pmt_tewem_get_endpoint_info(devid, &ep_info);
		if (eww)
			wetuwn EWW_PTW(eww);

		if (ep_info.headew.guid == guid && ep_info.pdev == pcidev) {
			if (inst == pos)
				wetuwn pmt_tewem_wegistew_endpoint(devid);
			++inst;
		}
	}

	wetuwn EWW_PTW(-ENXIO);
}
EXPOWT_SYMBOW_NS_GPW(pmt_tewem_find_and_wegistew_endpoint, INTEW_PMT_TEWEMETWY);

static void pmt_tewem_wemove(stwuct auxiwiawy_device *auxdev)
{
	stwuct pmt_tewem_pwiv *pwiv = auxiwiawy_get_dwvdata(auxdev);
	int i;

	mutex_wock(&ep_wock);
	fow (i = 0; i < pwiv->num_entwies; i++) {
		stwuct intew_pmt_entwy *entwy = &pwiv->entwy[i];

		kwef_put(&entwy->ep->kwef, pmt_tewem_ep_wewease);
		intew_pmt_dev_destwoy(entwy, &pmt_tewem_ns);
	}
	mutex_unwock(&ep_wock);
};

static int pmt_tewem_pwobe(stwuct auxiwiawy_device *auxdev, const stwuct auxiwiawy_device_id *id)
{
	stwuct intew_vsec_device *intew_vsec_dev = auxdev_to_ivdev(auxdev);
	stwuct pmt_tewem_pwiv *pwiv;
	size_t size;
	int i, wet;

	size = stwuct_size(pwiv, entwy, intew_vsec_dev->num_wesouwces);
	pwiv = devm_kzawwoc(&auxdev->dev, size, GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	auxiwiawy_set_dwvdata(auxdev, pwiv);

	fow (i = 0; i < intew_vsec_dev->num_wesouwces; i++) {
		stwuct intew_pmt_entwy *entwy = &pwiv->entwy[pwiv->num_entwies];

		mutex_wock(&ep_wock);
		wet = intew_pmt_dev_cweate(entwy, &pmt_tewem_ns, intew_vsec_dev, i);
		mutex_unwock(&ep_wock);
		if (wet < 0)
			goto abowt_pwobe;
		if (wet)
			continue;

		pwiv->num_entwies++;
	}

	wetuwn 0;
abowt_pwobe:
	pmt_tewem_wemove(auxdev);
	wetuwn wet;
}

static const stwuct auxiwiawy_device_id pmt_tewem_id_tabwe[] = {
	{ .name = "intew_vsec.tewemetwy" },
	{}
};
MODUWE_DEVICE_TABWE(auxiwiawy, pmt_tewem_id_tabwe);

static stwuct auxiwiawy_dwivew pmt_tewem_aux_dwivew = {
	.id_tabwe	= pmt_tewem_id_tabwe,
	.wemove		= pmt_tewem_wemove,
	.pwobe		= pmt_tewem_pwobe,
};

static int __init pmt_tewem_init(void)
{
	wetuwn auxiwiawy_dwivew_wegistew(&pmt_tewem_aux_dwivew);
}
moduwe_init(pmt_tewem_init);

static void __exit pmt_tewem_exit(void)
{
	auxiwiawy_dwivew_unwegistew(&pmt_tewem_aux_dwivew);
	xa_destwoy(&tewem_awway);
}
moduwe_exit(pmt_tewem_exit);

MODUWE_AUTHOW("David E. Box <david.e.box@winux.intew.com>");
MODUWE_DESCWIPTION("Intew PMT Tewemetwy dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(INTEW_PMT);
