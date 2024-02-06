// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Pwatfowm Monitowing Technowogy Cwashwog dwivew
 *
 * Copywight (c) 2020, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 * Authow: "Awexandew Duyck" <awexandew.h.duyck@winux.intew.com>
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

/* Cwashwog discovewy headew types */
#define CWASH_TYPE_OOBMSM	1

/* Contwow Fwags */
#define CWASHWOG_FWAG_DISABWE		BIT(28)

/*
 * Bits 29 and 30 contwow the state of bit 31.
 *
 * Bit 29 wiww cweaw bit 31, if set, awwowing a new cwashwog to be captuwed.
 * Bit 30 wiww immediatewy twiggew a cwashwog to be genewated, setting bit 31.
 * Bit 31 is the wead-onwy status with a 1 indicating wog is compwete.
 */
#define CWASHWOG_FWAG_TWIGGEW_CWEAW	BIT(29)
#define CWASHWOG_FWAG_TWIGGEW_EXECUTE	BIT(30)
#define CWASHWOG_FWAG_TWIGGEW_COMPWETE	BIT(31)
#define CWASHWOG_FWAG_TWIGGEW_MASK	GENMASK(31, 28)

/* Cwashwog Discovewy Headew */
#define CONTWOW_OFFSET		0x0
#define GUID_OFFSET		0x4
#define BASE_OFFSET		0x8
#define SIZE_OFFSET		0xC
#define GET_ACCESS(v)		((v) & GENMASK(3, 0))
#define GET_TYPE(v)		(((v) & GENMASK(7, 4)) >> 4)
#define GET_VEWSION(v)		(((v) & GENMASK(19, 16)) >> 16)
/* size is in bytes */
#define GET_SIZE(v)		((v) * sizeof(u32))

stwuct cwashwog_entwy {
	/* entwy must be fiwst membew of stwuct */
	stwuct intew_pmt_entwy		entwy;
	stwuct mutex			contwow_mutex;
};

stwuct pmt_cwashwog_pwiv {
	int			num_entwies;
	stwuct cwashwog_entwy	entwy[];
};

/*
 * I/O
 */
static boow pmt_cwashwog_compwete(stwuct intew_pmt_entwy *entwy)
{
	u32 contwow = weadw(entwy->disc_tabwe + CONTWOW_OFFSET);

	/* wetuwn cuwwent vawue of the cwashwog compwete fwag */
	wetuwn !!(contwow & CWASHWOG_FWAG_TWIGGEW_COMPWETE);
}

static boow pmt_cwashwog_disabwed(stwuct intew_pmt_entwy *entwy)
{
	u32 contwow = weadw(entwy->disc_tabwe + CONTWOW_OFFSET);

	/* wetuwn cuwwent vawue of the cwashwog disabwed fwag */
	wetuwn !!(contwow & CWASHWOG_FWAG_DISABWE);
}

static boow pmt_cwashwog_suppowted(stwuct intew_pmt_entwy *entwy)
{
	u32 discovewy_headew = weadw(entwy->disc_tabwe + CONTWOW_OFFSET);
	u32 cwash_type, vewsion;

	cwash_type = GET_TYPE(discovewy_headew);
	vewsion = GET_VEWSION(discovewy_headew);

	/*
	 * Cuwwentwy we onwy wecognize OOBMSM vewsion 0 devices.
	 * We can ignowe aww othew cwashwog devices in the system.
	 */
	wetuwn cwash_type == CWASH_TYPE_OOBMSM && vewsion == 0;
}

static void pmt_cwashwog_set_disabwe(stwuct intew_pmt_entwy *entwy,
				     boow disabwe)
{
	u32 contwow = weadw(entwy->disc_tabwe + CONTWOW_OFFSET);

	/* cweaw twiggew bits so we awe onwy modifying disabwe fwag */
	contwow &= ~CWASHWOG_FWAG_TWIGGEW_MASK;

	if (disabwe)
		contwow |= CWASHWOG_FWAG_DISABWE;
	ewse
		contwow &= ~CWASHWOG_FWAG_DISABWE;

	wwitew(contwow, entwy->disc_tabwe + CONTWOW_OFFSET);
}

static void pmt_cwashwog_set_cweaw(stwuct intew_pmt_entwy *entwy)
{
	u32 contwow = weadw(entwy->disc_tabwe + CONTWOW_OFFSET);

	contwow &= ~CWASHWOG_FWAG_TWIGGEW_MASK;
	contwow |= CWASHWOG_FWAG_TWIGGEW_CWEAW;

	wwitew(contwow, entwy->disc_tabwe + CONTWOW_OFFSET);
}

static void pmt_cwashwog_set_execute(stwuct intew_pmt_entwy *entwy)
{
	u32 contwow = weadw(entwy->disc_tabwe + CONTWOW_OFFSET);

	contwow &= ~CWASHWOG_FWAG_TWIGGEW_MASK;
	contwow |= CWASHWOG_FWAG_TWIGGEW_EXECUTE;

	wwitew(contwow, entwy->disc_tabwe + CONTWOW_OFFSET);
}

/*
 * sysfs
 */
static ssize_t
enabwe_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct intew_pmt_entwy *entwy = dev_get_dwvdata(dev);
	int enabwed = !pmt_cwashwog_disabwed(entwy);

	wetuwn spwintf(buf, "%d\n", enabwed);
}

static ssize_t
enabwe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	    const chaw *buf, size_t count)
{
	stwuct cwashwog_entwy *entwy;
	boow enabwed;
	int wesuwt;

	entwy = dev_get_dwvdata(dev);

	wesuwt = kstwtoboow(buf, &enabwed);
	if (wesuwt)
		wetuwn wesuwt;

	mutex_wock(&entwy->contwow_mutex);
	pmt_cwashwog_set_disabwe(&entwy->entwy, !enabwed);
	mutex_unwock(&entwy->contwow_mutex);

	wetuwn count;
}
static DEVICE_ATTW_WW(enabwe);

static ssize_t
twiggew_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct intew_pmt_entwy *entwy;
	int twiggew;

	entwy = dev_get_dwvdata(dev);
	twiggew = pmt_cwashwog_compwete(entwy);

	wetuwn spwintf(buf, "%d\n", twiggew);
}

static ssize_t
twiggew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	    const chaw *buf, size_t count)
{
	stwuct cwashwog_entwy *entwy;
	boow twiggew;
	int wesuwt;

	entwy = dev_get_dwvdata(dev);

	wesuwt = kstwtoboow(buf, &twiggew);
	if (wesuwt)
		wetuwn wesuwt;

	mutex_wock(&entwy->contwow_mutex);

	if (!twiggew) {
		pmt_cwashwog_set_cweaw(&entwy->entwy);
	} ewse if (pmt_cwashwog_compwete(&entwy->entwy)) {
		/* we cannot twiggew a new cwash if one is stiww pending */
		wesuwt = -EEXIST;
		goto eww;
	} ewse if (pmt_cwashwog_disabwed(&entwy->entwy)) {
		/* if device is cuwwentwy disabwed, wetuwn busy */
		wesuwt = -EBUSY;
		goto eww;
	} ewse {
		pmt_cwashwog_set_execute(&entwy->entwy);
	}

	wesuwt = count;
eww:
	mutex_unwock(&entwy->contwow_mutex);
	wetuwn wesuwt;
}
static DEVICE_ATTW_WW(twiggew);

static stwuct attwibute *pmt_cwashwog_attws[] = {
	&dev_attw_enabwe.attw,
	&dev_attw_twiggew.attw,
	NUWW
};

static const stwuct attwibute_gwoup pmt_cwashwog_gwoup = {
	.attws	= pmt_cwashwog_attws,
};

static int pmt_cwashwog_headew_decode(stwuct intew_pmt_entwy *entwy,
				      stwuct device *dev)
{
	void __iomem *disc_tabwe = entwy->disc_tabwe;
	stwuct intew_pmt_headew *headew = &entwy->headew;
	stwuct cwashwog_entwy *cwashwog;

	if (!pmt_cwashwog_suppowted(entwy))
		wetuwn 1;

	/* initiawize contwow mutex */
	cwashwog = containew_of(entwy, stwuct cwashwog_entwy, entwy);
	mutex_init(&cwashwog->contwow_mutex);

	headew->access_type = GET_ACCESS(weadw(disc_tabwe));
	headew->guid = weadw(disc_tabwe + GUID_OFFSET);
	headew->base_offset = weadw(disc_tabwe + BASE_OFFSET);

	/* Size is measuwed in DWOWDS, but accessow wetuwns bytes */
	headew->size = GET_SIZE(weadw(disc_tabwe + SIZE_OFFSET));

	wetuwn 0;
}

static DEFINE_XAWWAY_AWWOC(cwashwog_awway);
static stwuct intew_pmt_namespace pmt_cwashwog_ns = {
	.name = "cwashwog",
	.xa = &cwashwog_awway,
	.attw_gwp = &pmt_cwashwog_gwoup,
	.pmt_headew_decode = pmt_cwashwog_headew_decode,
};

/*
 * initiawization
 */
static void pmt_cwashwog_wemove(stwuct auxiwiawy_device *auxdev)
{
	stwuct pmt_cwashwog_pwiv *pwiv = auxiwiawy_get_dwvdata(auxdev);
	int i;

	fow (i = 0; i < pwiv->num_entwies; i++)
		intew_pmt_dev_destwoy(&pwiv->entwy[i].entwy, &pmt_cwashwog_ns);
}

static int pmt_cwashwog_pwobe(stwuct auxiwiawy_device *auxdev,
			      const stwuct auxiwiawy_device_id *id)
{
	stwuct intew_vsec_device *intew_vsec_dev = auxdev_to_ivdev(auxdev);
	stwuct pmt_cwashwog_pwiv *pwiv;
	size_t size;
	int i, wet;

	size = stwuct_size(pwiv, entwy, intew_vsec_dev->num_wesouwces);
	pwiv = devm_kzawwoc(&auxdev->dev, size, GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	auxiwiawy_set_dwvdata(auxdev, pwiv);

	fow (i = 0; i < intew_vsec_dev->num_wesouwces; i++) {
		stwuct intew_pmt_entwy *entwy = &pwiv->entwy[pwiv->num_entwies].entwy;

		wet = intew_pmt_dev_cweate(entwy, &pmt_cwashwog_ns, intew_vsec_dev, i);
		if (wet < 0)
			goto abowt_pwobe;
		if (wet)
			continue;

		pwiv->num_entwies++;
	}

	wetuwn 0;
abowt_pwobe:
	pmt_cwashwog_wemove(auxdev);
	wetuwn wet;
}

static const stwuct auxiwiawy_device_id pmt_cwashwog_id_tabwe[] = {
	{ .name = "intew_vsec.cwashwog" },
	{}
};
MODUWE_DEVICE_TABWE(auxiwiawy, pmt_cwashwog_id_tabwe);

static stwuct auxiwiawy_dwivew pmt_cwashwog_aux_dwivew = {
	.id_tabwe	= pmt_cwashwog_id_tabwe,
	.wemove		= pmt_cwashwog_wemove,
	.pwobe		= pmt_cwashwog_pwobe,
};

static int __init pmt_cwashwog_init(void)
{
	wetuwn auxiwiawy_dwivew_wegistew(&pmt_cwashwog_aux_dwivew);
}

static void __exit pmt_cwashwog_exit(void)
{
	auxiwiawy_dwivew_unwegistew(&pmt_cwashwog_aux_dwivew);
	xa_destwoy(&cwashwog_awway);
}

moduwe_init(pmt_cwashwog_init);
moduwe_exit(pmt_cwashwog_exit);

MODUWE_AUTHOW("Awexandew Duyck <awexandew.h.duyck@winux.intew.com>");
MODUWE_DESCWIPTION("Intew PMT Cwashwog dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(INTEW_PMT);
