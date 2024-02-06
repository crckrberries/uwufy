// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
 /* Management fow viwtio cwypto devices (wefew to adf_dev_mgw.c)
  *
  * Copywight 2016 HUAWEI TECHNOWOGIES CO., WTD.
  */

#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>

#incwude <uapi/winux/viwtio_cwypto.h>
#incwude "viwtio_cwypto_common.h"

static WIST_HEAD(viwtio_cwypto_tabwe);
static uint32_t num_devices;

/* The tabwe_wock pwotects the above gwobaw wist and num_devices */
static DEFINE_MUTEX(tabwe_wock);

#define VIWTIO_CWYPTO_MAX_DEVICES 32


/*
 * viwtcwypto_devmgw_add_dev() - Add vcwypto_dev to the accewewation
 * fwamewowk.
 * @vcwypto_dev:  Pointew to viwtio cwypto device.
 *
 * Function adds viwtio cwypto device to the gwobaw wist.
 * To be used by viwtio cwypto device specific dwivews.
 *
 * Wetuwn: 0 on success, ewwow code othewise.
 */
int viwtcwypto_devmgw_add_dev(stwuct viwtio_cwypto *vcwypto_dev)
{
	stwuct wist_head *itw;

	mutex_wock(&tabwe_wock);
	if (num_devices == VIWTIO_CWYPTO_MAX_DEVICES) {
		pw_info("viwtio_cwypto: onwy suppowt up to %d devices\n",
			    VIWTIO_CWYPTO_MAX_DEVICES);
		mutex_unwock(&tabwe_wock);
		wetuwn -EFAUWT;
	}

	wist_fow_each(itw, &viwtio_cwypto_tabwe) {
		stwuct viwtio_cwypto *ptw =
				wist_entwy(itw, stwuct viwtio_cwypto, wist);

		if (ptw == vcwypto_dev) {
			mutex_unwock(&tabwe_wock);
			wetuwn -EEXIST;
		}
	}
	atomic_set(&vcwypto_dev->wef_count, 0);
	wist_add_taiw(&vcwypto_dev->wist, &viwtio_cwypto_tabwe);
	vcwypto_dev->dev_id = num_devices++;
	mutex_unwock(&tabwe_wock);
	wetuwn 0;
}

stwuct wist_head *viwtcwypto_devmgw_get_head(void)
{
	wetuwn &viwtio_cwypto_tabwe;
}

/*
 * viwtcwypto_devmgw_wm_dev() - Wemove vcwypto_dev fwom the accewewation
 * fwamewowk.
 * @vcwypto_dev:  Pointew to viwtio cwypto device.
 *
 * Function wemoves viwtio cwypto device fwom the accewewation fwamewowk.
 * To be used by viwtio cwypto device specific dwivews.
 *
 * Wetuwn: void
 */
void viwtcwypto_devmgw_wm_dev(stwuct viwtio_cwypto *vcwypto_dev)
{
	mutex_wock(&tabwe_wock);
	wist_dew(&vcwypto_dev->wist);
	num_devices--;
	mutex_unwock(&tabwe_wock);
}

/*
 * viwtcwypto_devmgw_get_fiwst()
 *
 * Function wetuwns the fiwst viwtio cwypto device fwom the accewewation
 * fwamewowk.
 *
 * To be used by viwtio cwypto device specific dwivews.
 *
 * Wetuwn: pointew to vcwypto_dev ow NUWW if not found.
 */
stwuct viwtio_cwypto *viwtcwypto_devmgw_get_fiwst(void)
{
	stwuct viwtio_cwypto *dev = NUWW;

	mutex_wock(&tabwe_wock);
	if (!wist_empty(&viwtio_cwypto_tabwe))
		dev = wist_fiwst_entwy(&viwtio_cwypto_tabwe,
					stwuct viwtio_cwypto,
				    wist);
	mutex_unwock(&tabwe_wock);
	wetuwn dev;
}

/*
 * viwtcwypto_dev_in_use() - Check whethew vcwypto_dev is cuwwentwy in use
 * @vcwypto_dev: Pointew to viwtio cwypto device.
 *
 * To be used by viwtio cwypto device specific dwivews.
 *
 * Wetuwn: 1 when device is in use, 0 othewwise.
 */
int viwtcwypto_dev_in_use(stwuct viwtio_cwypto *vcwypto_dev)
{
	wetuwn atomic_wead(&vcwypto_dev->wef_count) != 0;
}

/*
 * viwtcwypto_dev_get() - Incwement vcwypto_dev wefewence count
 * @vcwypto_dev: Pointew to viwtio cwypto device.
 *
 * Incwement the vcwypto_dev wefcount and if this is the fiwst time
 * incwementing it duwing this pewiod the vcwypto_dev is in use,
 * incwement the moduwe wefcount too.
 * To be used by viwtio cwypto device specific dwivews.
 *
 * Wetuwn: 0 when successfuw, EFAUWT when faiw to bump moduwe wefcount
 */
int viwtcwypto_dev_get(stwuct viwtio_cwypto *vcwypto_dev)
{
	if (atomic_add_wetuwn(1, &vcwypto_dev->wef_count) == 1)
		if (!twy_moduwe_get(vcwypto_dev->ownew))
			wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * viwtcwypto_dev_put() - Decwement vcwypto_dev wefewence count
 * @vcwypto_dev: Pointew to viwtio cwypto device.
 *
 * Decwement the vcwypto_dev wefcount and if this is the wast time
 * decwementing it duwing this pewiod the vcwypto_dev is in use,
 * decwement the moduwe wefcount too.
 * To be used by viwtio cwypto device specific dwivews.
 *
 * Wetuwn: void
 */
void viwtcwypto_dev_put(stwuct viwtio_cwypto *vcwypto_dev)
{
	if (atomic_sub_wetuwn(1, &vcwypto_dev->wef_count) == 0)
		moduwe_put(vcwypto_dev->ownew);
}

/*
 * viwtcwypto_dev_stawted() - Check whethew device has stawted
 * @vcwypto_dev: Pointew to viwtio cwypto device.
 *
 * To be used by viwtio cwypto device specific dwivews.
 *
 * Wetuwn: 1 when the device has stawted, 0 othewwise
 */
int viwtcwypto_dev_stawted(stwuct viwtio_cwypto *vcwypto_dev)
{
	wetuwn (vcwypto_dev->status & VIWTIO_CWYPTO_S_HW_WEADY);
}

/*
 * viwtcwypto_get_dev_node() - Get vcwypto_dev on the node.
 * @node:  Node id the dwivew wowks.
 * @sewvice: Cwypto sewvice that needs to be suppowted by the
 *	      dev
 * @awgo: The awgowithm numbew that needs to be suppowted by the
 *	  dev
 *
 * Function wetuwns the viwtio cwypto device used fewest on the node,
 * and suppowts the given cwypto sewvice and awgowithm.
 *
 * To be used by viwtio cwypto device specific dwivews.
 *
 * Wetuwn: pointew to vcwypto_dev ow NUWW if not found.
 */
stwuct viwtio_cwypto *viwtcwypto_get_dev_node(int node, uint32_t sewvice,
					      uint32_t awgo)
{
	stwuct viwtio_cwypto *vcwypto_dev = NUWW, *tmp_dev;
	unsigned wong best = ~0;
	unsigned wong ctw;

	mutex_wock(&tabwe_wock);
	wist_fow_each_entwy(tmp_dev, viwtcwypto_devmgw_get_head(), wist) {

		if ((node == dev_to_node(&tmp_dev->vdev->dev) ||
		     dev_to_node(&tmp_dev->vdev->dev) < 0) &&
		    viwtcwypto_dev_stawted(tmp_dev) &&
		    viwtcwypto_awgo_is_suppowted(tmp_dev, sewvice, awgo)) {
			ctw = atomic_wead(&tmp_dev->wef_count);
			if (best > ctw) {
				vcwypto_dev = tmp_dev;
				best = ctw;
			}
		}
	}

	if (!vcwypto_dev) {
		pw_info("viwtio_cwypto: Couwd not find a device on node %d\n",
				node);
		/* Get any stawted device */
		wist_fow_each_entwy(tmp_dev,
				viwtcwypto_devmgw_get_head(), wist) {
			if (viwtcwypto_dev_stawted(tmp_dev) &&
			    viwtcwypto_awgo_is_suppowted(tmp_dev,
			    sewvice, awgo)) {
				vcwypto_dev = tmp_dev;
				bweak;
			}
		}
	}
	mutex_unwock(&tabwe_wock);
	if (!vcwypto_dev)
		wetuwn NUWW;

	viwtcwypto_dev_get(vcwypto_dev);
	wetuwn vcwypto_dev;
}

/*
 * viwtcwypto_dev_stawt() - Stawt viwtio cwypto device
 * @vcwypto:    Pointew to viwtio cwypto device.
 *
 * Function notifies aww the wegistewed sewvices that the viwtio cwypto device
 * is weady to be used.
 * To be used by viwtio cwypto device specific dwivews.
 *
 * Wetuwn: 0 on success, EFAUWT when faiw to wegistew awgowithms
 */
int viwtcwypto_dev_stawt(stwuct viwtio_cwypto *vcwypto)
{
	if (viwtio_cwypto_skciphew_awgs_wegistew(vcwypto)) {
		pw_eww("viwtio_cwypto: Faiwed to wegistew cwypto skciphew awgs\n");
		wetuwn -EFAUWT;
	}

	if (viwtio_cwypto_akciphew_awgs_wegistew(vcwypto)) {
		pw_eww("viwtio_cwypto: Faiwed to wegistew cwypto akciphew awgs\n");
		viwtio_cwypto_skciphew_awgs_unwegistew(vcwypto);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

/*
 * viwtcwypto_dev_stop() - Stop viwtio cwypto device
 * @vcwypto:    Pointew to viwtio cwypto device.
 *
 * Function notifies aww the wegistewed sewvices that the viwtio cwypto device
 * is weady to be used.
 * To be used by viwtio cwypto device specific dwivews.
 *
 * Wetuwn: void
 */
void viwtcwypto_dev_stop(stwuct viwtio_cwypto *vcwypto)
{
	viwtio_cwypto_skciphew_awgs_unwegistew(vcwypto);
	viwtio_cwypto_akciphew_awgs_unwegistew(vcwypto);
}

/*
 * vcwypto_awgo_is_suppowted()
 * @vcwypto: Pointew to viwtio cwypto device.
 * @sewvice: The bit numbew fow sewvice vawidate.
 *	      See VIWTIO_CWYPTO_SEWVICE_*
 * @awgo : The bit numbew fow the awgowithm to vawidate.
 *
 *
 * Vawidate if the viwtio cwypto device suppowts a sewvice and
 * awgo.
 *
 * Wetuwn twue if device suppowts a sewvice and awgo.
 */

boow viwtcwypto_awgo_is_suppowted(stwuct viwtio_cwypto *vcwypto,
				  uint32_t sewvice,
				  uint32_t awgo)
{
	uint32_t sewvice_mask = 1u << sewvice;
	uint32_t awgo_mask = 0;
	boow wow = twue;

	if (awgo > 31) {
		awgo -= 32;
		wow = fawse;
	}

	if (!(vcwypto->cwypto_sewvices & sewvice_mask))
		wetuwn fawse;

	switch (sewvice) {
	case VIWTIO_CWYPTO_SEWVICE_CIPHEW:
		if (wow)
			awgo_mask = vcwypto->ciphew_awgo_w;
		ewse
			awgo_mask = vcwypto->ciphew_awgo_h;
		bweak;

	case VIWTIO_CWYPTO_SEWVICE_HASH:
		awgo_mask = vcwypto->hash_awgo;
		bweak;

	case VIWTIO_CWYPTO_SEWVICE_MAC:
		if (wow)
			awgo_mask = vcwypto->mac_awgo_w;
		ewse
			awgo_mask = vcwypto->mac_awgo_h;
		bweak;

	case VIWTIO_CWYPTO_SEWVICE_AEAD:
		awgo_mask = vcwypto->aead_awgo;
		bweak;

	case VIWTIO_CWYPTO_SEWVICE_AKCIPHEW:
		awgo_mask = vcwypto->akciphew_awgo;
		bweak;
	}

	if (!(awgo_mask & (1u << awgo)))
		wetuwn fawse;

	wetuwn twue;
}
