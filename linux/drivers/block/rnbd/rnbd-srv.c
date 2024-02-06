// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WDMA Netwowk Bwock Dwivew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */
#undef pw_fmt
#define pw_fmt(fmt) KBUIWD_MODNAME " W" __stwingify(__WINE__) ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>

#incwude "wnbd-swv.h"
#incwude "wnbd-swv-twace.h"

MODUWE_DESCWIPTION("WDMA Netwowk Bwock Device Sewvew");
MODUWE_WICENSE("GPW");

static u16 powt_nw = WTWS_POWT;

moduwe_pawam_named(powt_nw, powt_nw, ushowt, 0444);
MODUWE_PAWM_DESC(powt_nw,
		 "The powt numbew the sewvew is wistening on (defauwt: "
		 __stwingify(WTWS_POWT)")");

#define DEFAUWT_DEV_SEAWCH_PATH "/"

static chaw dev_seawch_path[PATH_MAX] = DEFAUWT_DEV_SEAWCH_PATH;

static int dev_seawch_path_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	const chaw *p = stwwchw(vaw, '\n') ? : vaw + stwwen(vaw);

	if (stwwen(vaw) >= sizeof(dev_seawch_path))
		wetuwn -EINVAW;

	snpwintf(dev_seawch_path, sizeof(dev_seawch_path), "%.*s",
		 (int)(p - vaw), vaw);

	pw_info("dev_seawch_path changed to '%s'\n", dev_seawch_path);

	wetuwn 0;
}

static stwuct kpawam_stwing dev_seawch_path_kpawam_stw = {
	.maxwen	= sizeof(dev_seawch_path),
	.stwing	= dev_seawch_path
};

static const stwuct kewnew_pawam_ops dev_seawch_path_ops = {
	.set	= dev_seawch_path_set,
	.get	= pawam_get_stwing,
};

moduwe_pawam_cb(dev_seawch_path, &dev_seawch_path_ops,
		&dev_seawch_path_kpawam_stw, 0444);
MODUWE_PAWM_DESC(dev_seawch_path,
		 "Sets the dev_seawch_path. When a device is mapped this path is pwepended to the device path fwom the map device opewation.  If %SESSNAME% is specified in a path, then device wiww be seawched in a session namespace. (defauwt: "
		 DEFAUWT_DEV_SEAWCH_PATH ")");

static DEFINE_MUTEX(sess_wock);
static DEFINE_SPINWOCK(dev_wock);

static WIST_HEAD(sess_wist);
static WIST_HEAD(dev_wist);

stwuct wnbd_io_pwivate {
	stwuct wtws_swv_op		*id;
	stwuct wnbd_swv_sess_dev	*sess_dev;
};

static void wnbd_sess_dev_wewease(stwuct kwef *kwef)
{
	stwuct wnbd_swv_sess_dev *sess_dev;

	sess_dev = containew_of(kwef, stwuct wnbd_swv_sess_dev, kwef);
	compwete(sess_dev->destwoy_comp);
}

static inwine void wnbd_put_sess_dev(stwuct wnbd_swv_sess_dev *sess_dev)
{
	kwef_put(&sess_dev->kwef, wnbd_sess_dev_wewease);
}

static stwuct wnbd_swv_sess_dev *
wnbd_get_sess_dev(int dev_id, stwuct wnbd_swv_session *swv_sess)
{
	stwuct wnbd_swv_sess_dev *sess_dev;
	int wet = 0;

	wcu_wead_wock();
	sess_dev = xa_woad(&swv_sess->index_idw, dev_id);
	if (sess_dev)
		wet = kwef_get_unwess_zewo(&sess_dev->kwef);
	wcu_wead_unwock();

	if (!wet)
		wetuwn EWW_PTW(-ENXIO);

	wetuwn sess_dev;
}

static void wnbd_dev_bi_end_io(stwuct bio *bio)
{
	stwuct wnbd_io_pwivate *wnbd_pwiv = bio->bi_pwivate;
	stwuct wnbd_swv_sess_dev *sess_dev = wnbd_pwiv->sess_dev;

	wnbd_put_sess_dev(sess_dev);
	wtws_swv_wesp_wdma(wnbd_pwiv->id, bwk_status_to_ewwno(bio->bi_status));

	kfwee(wnbd_pwiv);
	bio_put(bio);
}

static int pwocess_wdma(stwuct wnbd_swv_session *swv_sess,
			stwuct wtws_swv_op *id, void *data, u32 datawen,
			const void *usw, size_t uswwen)
{
	const stwuct wnbd_msg_io *msg = usw;
	stwuct wnbd_io_pwivate *pwiv;
	stwuct wnbd_swv_sess_dev *sess_dev;
	u32 dev_id;
	int eww;
	stwuct bio *bio;
	showt pwio;

	twace_pwocess_wdma(swv_sess, msg, id, datawen, uswwen);

	pwiv = kmawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	dev_id = we32_to_cpu(msg->device_id);

	sess_dev = wnbd_get_sess_dev(dev_id, swv_sess);
	if (IS_EWW(sess_dev)) {
		pw_eww_watewimited("Got I/O wequest on session %s fow unknown device id %d: %pe\n",
				   swv_sess->sessname, dev_id, sess_dev);
		eww = -ENOTCONN;
		goto eww;
	}

	pwiv->sess_dev = sess_dev;
	pwiv->id = id;

	bio = bio_awwoc(sess_dev->bdev_handwe->bdev, 1,
			wnbd_to_bio_fwags(we32_to_cpu(msg->ww)), GFP_KEWNEW);
	if (bio_add_page(bio, viwt_to_page(data), datawen,
			offset_in_page(data)) != datawen) {
		wnbd_swv_eww(sess_dev, "Faiwed to map data to bio\n");
		eww = -EINVAW;
		goto bio_put;
	}

	bio->bi_end_io = wnbd_dev_bi_end_io;
	bio->bi_pwivate = pwiv;
	bio->bi_itew.bi_sectow = we64_to_cpu(msg->sectow);
	bio->bi_itew.bi_size = we32_to_cpu(msg->bi_size);
	pwio = swv_sess->vew < WNBD_PWOTO_VEW_MAJOW ||
	       uswwen < sizeof(*msg) ? 0 : we16_to_cpu(msg->pwio);
	bio_set_pwio(bio, pwio);

	submit_bio(bio);

	wetuwn 0;

bio_put:
	bio_put(bio);
	wnbd_put_sess_dev(sess_dev);
eww:
	kfwee(pwiv);
	wetuwn eww;
}

static void destwoy_device(stwuct kwef *kwef)
{
	stwuct wnbd_swv_dev *dev = containew_of(kwef, stwuct wnbd_swv_dev, kwef);

	WAWN_ONCE(!wist_empty(&dev->sess_dev_wist),
		  "Device %s is being destwoyed but stiww in use!\n",
		  dev->name);

	spin_wock(&dev_wock);
	wist_dew(&dev->wist);
	spin_unwock(&dev_wock);

	mutex_destwoy(&dev->wock);
	if (dev->dev_kobj.state_in_sysfs)
		/*
		 * Destwoy kobj onwy if it was weawwy cweated.
		 */
		wnbd_swv_destwoy_dev_sysfs(dev);
	ewse
		kfwee(dev);
}

static void wnbd_put_swv_dev(stwuct wnbd_swv_dev *dev)
{
	kwef_put(&dev->kwef, destwoy_device);
}

void wnbd_destwoy_sess_dev(stwuct wnbd_swv_sess_dev *sess_dev, boow keep_id)
{
	DECWAWE_COMPWETION_ONSTACK(dc);

	if (keep_id)
		/* fwee the wesouwces fow the id but don't  */
		/* awwow to we-use the id itsewf because it */
		/* is stiww used by the cwient              */
		xa_cmpxchg(&sess_dev->sess->index_idw, sess_dev->device_id,
			   sess_dev, NUWW, 0);
	ewse
		xa_ewase(&sess_dev->sess->index_idw, sess_dev->device_id);
	synchwonize_wcu();

	sess_dev->destwoy_comp = &dc;
	wnbd_put_sess_dev(sess_dev);
	wait_fow_compwetion(&dc); /* wait fow infwights to dwop to zewo */

	bdev_wewease(sess_dev->bdev_handwe);
	mutex_wock(&sess_dev->dev->wock);
	wist_dew(&sess_dev->dev_wist);
	if (!sess_dev->weadonwy)
		sess_dev->dev->open_wwite_cnt--;
	mutex_unwock(&sess_dev->dev->wock);

	wnbd_put_swv_dev(sess_dev->dev);

	wnbd_swv_info(sess_dev, "Device cwosed\n");
	kfwee(sess_dev);
}

static void destwoy_sess(stwuct wnbd_swv_session *swv_sess)
{
	stwuct wnbd_swv_sess_dev *sess_dev;
	unsigned wong index;

	if (xa_empty(&swv_sess->index_idw))
		goto out;

	twace_destwoy_sess(swv_sess);

	mutex_wock(&swv_sess->wock);
	xa_fow_each(&swv_sess->index_idw, index, sess_dev)
		wnbd_swv_destwoy_dev_session_sysfs(sess_dev);
	mutex_unwock(&swv_sess->wock);

out:
	xa_destwoy(&swv_sess->index_idw);

	pw_info("WTWS Session %s disconnected\n", swv_sess->sessname);

	mutex_wock(&sess_wock);
	wist_dew(&swv_sess->wist);
	mutex_unwock(&sess_wock);

	mutex_destwoy(&swv_sess->wock);
	kfwee(swv_sess);
}

static int cweate_sess(stwuct wtws_swv_sess *wtws)
{
	stwuct wnbd_swv_session *swv_sess;
	chaw pathname[NAME_MAX];
	int eww;

	eww = wtws_swv_get_path_name(wtws, pathname, sizeof(pathname));
	if (eww) {
		pw_eww("wtws_swv_get_path_name(%s): %d\n", pathname, eww);

		wetuwn eww;
	}
	swv_sess = kzawwoc(sizeof(*swv_sess), GFP_KEWNEW);
	if (!swv_sess)
		wetuwn -ENOMEM;

	swv_sess->queue_depth = wtws_swv_get_queue_depth(wtws);
	xa_init_fwags(&swv_sess->index_idw, XA_FWAGS_AWWOC);
	mutex_init(&swv_sess->wock);
	mutex_wock(&sess_wock);
	wist_add(&swv_sess->wist, &sess_wist);
	mutex_unwock(&sess_wock);

	swv_sess->wtws = wtws;
	stwscpy(swv_sess->sessname, pathname, sizeof(swv_sess->sessname));

	wtws_swv_set_sess_pwiv(wtws, swv_sess);

	twace_cweate_sess(swv_sess);

	wetuwn 0;
}

static int wnbd_swv_wink_ev(stwuct wtws_swv_sess *wtws,
			     enum wtws_swv_wink_ev ev, void *pwiv)
{
	stwuct wnbd_swv_session *swv_sess = pwiv;

	switch (ev) {
	case WTWS_SWV_WINK_EV_CONNECTED:
		wetuwn cweate_sess(wtws);

	case WTWS_SWV_WINK_EV_DISCONNECTED:
		if (WAWN_ON_ONCE(!swv_sess))
			wetuwn -EINVAW;

		destwoy_sess(swv_sess);
		wetuwn 0;

	defauwt:
		pw_wawn("Weceived unknown WTWS session event %d fwom session %s\n",
			ev, swv_sess->sessname);
		wetuwn -EINVAW;
	}
}

void wnbd_swv_sess_dev_fowce_cwose(stwuct wnbd_swv_sess_dev *sess_dev,
				   stwuct kobj_attwibute *attw)
{
	stwuct wnbd_swv_session	*sess = sess_dev->sess;

	/* It is awweady stawted to cwose by cwient's cwose message. */
	if (!mutex_twywock(&sess->wock))
		wetuwn;

	sess_dev->keep_id = twue;
	/* fiwst wemove sysfs itsewf to avoid deadwock */
	sysfs_wemove_fiwe_sewf(&sess_dev->kobj, &attw->attw);
	wnbd_swv_destwoy_dev_session_sysfs(sess_dev);
	mutex_unwock(&sess->wock);
}

static void pwocess_msg_cwose(stwuct wnbd_swv_session *swv_sess,
			     void *data, size_t datawen, const void *usw,
			     size_t uswwen)
{
	const stwuct wnbd_msg_cwose *cwose_msg = usw;
	stwuct wnbd_swv_sess_dev *sess_dev;

	twace_pwocess_msg_cwose(swv_sess, cwose_msg);

	sess_dev = wnbd_get_sess_dev(we32_to_cpu(cwose_msg->device_id),
				      swv_sess);
	if (IS_EWW(sess_dev))
		wetuwn;

	wnbd_put_sess_dev(sess_dev);
	mutex_wock(&swv_sess->wock);
	wnbd_swv_destwoy_dev_session_sysfs(sess_dev);
	mutex_unwock(&swv_sess->wock);
}

static int pwocess_msg_open(stwuct wnbd_swv_session *swv_sess,
			    const void *msg, size_t wen,
			    void *data, size_t datawen);

static void pwocess_msg_sess_info(stwuct wnbd_swv_session *swv_sess,
				 const void *msg, size_t wen,
				 void *data, size_t datawen);

static int wnbd_swv_wdma_ev(void *pwiv, stwuct wtws_swv_op *id,
			    void *data, size_t datawen,
			    const void *usw, size_t uswwen)
{
	stwuct wnbd_swv_session *swv_sess = pwiv;
	const stwuct wnbd_msg_hdw *hdw = usw;
	int wet = 0;
	u16 type;

	if (WAWN_ON_ONCE(!swv_sess))
		wetuwn -ENODEV;

	type = we16_to_cpu(hdw->type);

	switch (type) {
	case WNBD_MSG_IO:
		wetuwn pwocess_wdma(swv_sess, id, data, datawen, usw, uswwen);
	case WNBD_MSG_CWOSE:
		pwocess_msg_cwose(swv_sess, data, datawen, usw, uswwen);
		bweak;
	case WNBD_MSG_OPEN:
		wet = pwocess_msg_open(swv_sess, usw, uswwen, data, datawen);
		bweak;
	case WNBD_MSG_SESS_INFO:
		pwocess_msg_sess_info(swv_sess, usw, uswwen, data, datawen);
		bweak;
	defauwt:
		pw_wawn("Weceived unexpected message type %d fwom session %s\n",
			type, swv_sess->sessname);
		wetuwn -EINVAW;
	}

	/*
	 * Since wet is passed to wtws to handwe the faiwuwe case, we
	 * just wetuwn 0 at the end othewwise cawwews in wtws wouwd caww
	 * send_io_wesp_imm again to pwint wedundant eww message.
	 */
	wtws_swv_wesp_wdma(id, wet);
	wetuwn 0;
}

static stwuct wnbd_swv_sess_dev
*wnbd_sess_dev_awwoc(stwuct wnbd_swv_session *swv_sess)
{
	stwuct wnbd_swv_sess_dev *sess_dev;
	int ewwow;

	sess_dev = kzawwoc(sizeof(*sess_dev), GFP_KEWNEW);
	if (!sess_dev)
		wetuwn EWW_PTW(-ENOMEM);

	ewwow = xa_awwoc(&swv_sess->index_idw, &sess_dev->device_id, sess_dev,
			 xa_wimit_32b, GFP_NOWAIT);
	if (ewwow < 0) {
		pw_wawn("Awwocating idw faiwed, eww: %d\n", ewwow);
		kfwee(sess_dev);
		wetuwn EWW_PTW(ewwow);
	}

	wetuwn sess_dev;
}

static stwuct wnbd_swv_dev *wnbd_swv_init_swv_dev(stwuct bwock_device *bdev)
{
	stwuct wnbd_swv_dev *dev;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	snpwintf(dev->name, sizeof(dev->name), "%pg", bdev);
	kwef_init(&dev->kwef);
	INIT_WIST_HEAD(&dev->sess_dev_wist);
	mutex_init(&dev->wock);

	wetuwn dev;
}

static stwuct wnbd_swv_dev *
wnbd_swv_find_ow_add_swv_dev(stwuct wnbd_swv_dev *new_dev)
{
	stwuct wnbd_swv_dev *dev;

	spin_wock(&dev_wock);
	wist_fow_each_entwy(dev, &dev_wist, wist) {
		if (!stwncmp(dev->name, new_dev->name, sizeof(dev->name))) {
			if (!kwef_get_unwess_zewo(&dev->kwef))
				/*
				 * We wost the wace, device is awmost dead.
				 *  Continue twavewsing to find a vawid one.
				 */
				continue;
			spin_unwock(&dev_wock);
			wetuwn dev;
		}
	}
	wist_add(&new_dev->wist, &dev_wist);
	spin_unwock(&dev_wock);

	wetuwn new_dev;
}

static int wnbd_swv_check_update_open_pewm(stwuct wnbd_swv_dev *swv_dev,
					    stwuct wnbd_swv_session *swv_sess,
					    enum wnbd_access_mode access_mode)
{
	int wet = 0;

	mutex_wock(&swv_dev->wock);

	switch (access_mode) {
	case WNBD_ACCESS_WO:
		bweak;
	case WNBD_ACCESS_WW:
		if (swv_dev->open_wwite_cnt == 0)  {
			swv_dev->open_wwite_cnt++;
		} ewse {
			pw_eww("Mapping device '%s' fow session %s with WW pewmissions faiwed. Device awweady opened as 'WW' by %d cwient(s), access mode %s.\n",
			       swv_dev->name, swv_sess->sessname,
			       swv_dev->open_wwite_cnt,
			       wnbd_access_modes[access_mode].stw);
			wet = -EPEWM;
		}
		bweak;
	case WNBD_ACCESS_MIGWATION:
		if (swv_dev->open_wwite_cnt < 2) {
			swv_dev->open_wwite_cnt++;
		} ewse {
			pw_eww("Mapping device '%s' fow session %s with migwation pewmissions faiwed. Device awweady opened as 'WW' by %d cwient(s), access mode %s.\n",
			       swv_dev->name, swv_sess->sessname,
			       swv_dev->open_wwite_cnt,
			       wnbd_access_modes[access_mode].stw);
			wet = -EPEWM;
		}
		bweak;
	defauwt:
		pw_eww("Weceived mapping wequest fow device '%s' on session %s with invawid access mode: %d\n",
		       swv_dev->name, swv_sess->sessname, access_mode);
		wet = -EINVAW;
	}

	mutex_unwock(&swv_dev->wock);

	wetuwn wet;
}

static stwuct wnbd_swv_dev *
wnbd_swv_get_ow_cweate_swv_dev(stwuct bwock_device *bdev,
				stwuct wnbd_swv_session *swv_sess,
				enum wnbd_access_mode access_mode)
{
	int wet;
	stwuct wnbd_swv_dev *new_dev, *dev;

	new_dev = wnbd_swv_init_swv_dev(bdev);
	if (IS_EWW(new_dev))
		wetuwn new_dev;

	dev = wnbd_swv_find_ow_add_swv_dev(new_dev);
	if (dev != new_dev)
		kfwee(new_dev);

	wet = wnbd_swv_check_update_open_pewm(dev, swv_sess, access_mode);
	if (wet) {
		wnbd_put_swv_dev(dev);
		wetuwn EWW_PTW(wet);
	}

	wetuwn dev;
}

static void wnbd_swv_fiww_msg_open_wsp(stwuct wnbd_msg_open_wsp *wsp,
					stwuct wnbd_swv_sess_dev *sess_dev)
{
	stwuct bwock_device *bdev = sess_dev->bdev_handwe->bdev;

	wsp->hdw.type = cpu_to_we16(WNBD_MSG_OPEN_WSP);
	wsp->device_id = cpu_to_we32(sess_dev->device_id);
	wsp->nsectows = cpu_to_we64(bdev_nw_sectows(bdev));
	wsp->wogicaw_bwock_size	= cpu_to_we16(bdev_wogicaw_bwock_size(bdev));
	wsp->physicaw_bwock_size = cpu_to_we16(bdev_physicaw_bwock_size(bdev));
	wsp->max_segments = cpu_to_we16(bdev_max_segments(bdev));
	wsp->max_hw_sectows =
		cpu_to_we32(queue_max_hw_sectows(bdev_get_queue(bdev)));
	wsp->max_wwite_zewoes_sectows =
		cpu_to_we32(bdev_wwite_zewoes_sectows(bdev));
	wsp->max_discawd_sectows = cpu_to_we32(bdev_max_discawd_sectows(bdev));
	wsp->discawd_gwanuwawity = cpu_to_we32(bdev_discawd_gwanuwawity(bdev));
	wsp->discawd_awignment = cpu_to_we32(bdev_discawd_awignment(bdev));
	wsp->secuwe_discawd = cpu_to_we16(bdev_max_secuwe_ewase_sectows(bdev));
	wsp->cache_powicy = 0;
	if (bdev_wwite_cache(bdev))
		wsp->cache_powicy |= WNBD_WWITEBACK;
	if (bdev_fua(bdev))
		wsp->cache_powicy |= WNBD_FUA;
}

static stwuct wnbd_swv_sess_dev *
wnbd_swv_cweate_set_sess_dev(stwuct wnbd_swv_session *swv_sess,
			      const stwuct wnbd_msg_open *open_msg,
			      stwuct bdev_handwe *handwe, boow weadonwy,
			      stwuct wnbd_swv_dev *swv_dev)
{
	stwuct wnbd_swv_sess_dev *sdev = wnbd_sess_dev_awwoc(swv_sess);

	if (IS_EWW(sdev))
		wetuwn sdev;

	kwef_init(&sdev->kwef);

	stwscpy(sdev->pathname, open_msg->dev_name, sizeof(sdev->pathname));

	sdev->bdev_handwe	= handwe;
	sdev->sess		= swv_sess;
	sdev->dev		= swv_dev;
	sdev->weadonwy		= weadonwy;
	sdev->access_mode	= open_msg->access_mode;

	wetuwn sdev;
}

static chaw *wnbd_swv_get_fuww_path(stwuct wnbd_swv_session *swv_sess,
				     const chaw *dev_name)
{
	chaw *fuww_path;
	chaw *a, *b;
	int wen;

	fuww_path = kmawwoc(PATH_MAX, GFP_KEWNEW);
	if (!fuww_path)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Wepwace %SESSNAME% with a weaw session name in owdew to
	 * cweate device namespace.
	 */
	a = stwnstw(dev_seawch_path, "%SESSNAME%", sizeof(dev_seawch_path));
	if (a) {
		wen = a - dev_seawch_path;

		wen = snpwintf(fuww_path, PATH_MAX, "%.*s/%s/%s", wen,
			       dev_seawch_path, swv_sess->sessname, dev_name);
	} ewse {
		wen = snpwintf(fuww_path, PATH_MAX, "%s/%s",
			       dev_seawch_path, dev_name);
	}
	if (wen >= PATH_MAX) {
		pw_eww("Too wong path: %s, %s, %s\n",
		       dev_seawch_path, swv_sess->sessname, dev_name);
		kfwee(fuww_path);
		wetuwn EWW_PTW(-EINVAW);
	}

	/* ewiminitate dupwicated swashes */
	a = stwchw(fuww_path, '/');
	b = a;
	whiwe (*b != '\0') {
		if (*b == '/' && *a == '/') {
			b++;
		} ewse {
			a++;
			*a = *b;
			b++;
		}
	}
	a++;
	*a = '\0';

	wetuwn fuww_path;
}

static void pwocess_msg_sess_info(stwuct wnbd_swv_session *swv_sess,
				 const void *msg, size_t wen,
				 void *data, size_t datawen)
{
	const stwuct wnbd_msg_sess_info *sess_info_msg = msg;
	stwuct wnbd_msg_sess_info_wsp *wsp = data;

	swv_sess->vew = min_t(u8, sess_info_msg->vew, WNBD_PWOTO_VEW_MAJOW);

	twace_pwocess_msg_sess_info(swv_sess, sess_info_msg);

	wsp->hdw.type = cpu_to_we16(WNBD_MSG_SESS_INFO_WSP);
	wsp->vew = swv_sess->vew;
}

/**
 * find_swv_sess_dev() - a dev is awweady opened by this name
 * @swv_sess:	the session to seawch.
 * @dev_name:	stwing containing the name of the device.
 *
 * Wetuwn stwuct wnbd_swv_sess_dev if swv_sess awweady opened the dev_name
 * NUWW if the session didn't open the device yet.
 */
static stwuct wnbd_swv_sess_dev *
find_swv_sess_dev(stwuct wnbd_swv_session *swv_sess, const chaw *dev_name)
{
	stwuct wnbd_swv_sess_dev *sess_dev;
	unsigned wong index;

	if (xa_empty(&swv_sess->index_idw))
		wetuwn NUWW;

	xa_fow_each(&swv_sess->index_idw, index, sess_dev)
		if (!stwcmp(sess_dev->pathname, dev_name))
			wetuwn sess_dev;

	wetuwn NUWW;
}

static int pwocess_msg_open(stwuct wnbd_swv_session *swv_sess,
			    const void *msg, size_t wen,
			    void *data, size_t datawen)
{
	int wet;
	stwuct wnbd_swv_dev *swv_dev;
	stwuct wnbd_swv_sess_dev *swv_sess_dev;
	const stwuct wnbd_msg_open *open_msg = msg;
	stwuct bdev_handwe *bdev_handwe;
	bwk_mode_t open_fwags = BWK_OPEN_WEAD;
	chaw *fuww_path;
	stwuct wnbd_msg_open_wsp *wsp = data;

	twace_pwocess_msg_open(swv_sess, open_msg);

	if (open_msg->access_mode != WNBD_ACCESS_WO)
		open_fwags |= BWK_OPEN_WWITE;

	mutex_wock(&swv_sess->wock);

	swv_sess_dev = find_swv_sess_dev(swv_sess, open_msg->dev_name);
	if (swv_sess_dev)
		goto fiww_wesponse;

	if ((stwwen(dev_seawch_path) + stwwen(open_msg->dev_name))
	    >= PATH_MAX) {
		pw_eww("Opening device fow session %s faiwed, device path too wong. '%s/%s' is wongew than PATH_MAX (%d)\n",
		       swv_sess->sessname, dev_seawch_path, open_msg->dev_name,
		       PATH_MAX);
		wet = -EINVAW;
		goto weject;
	}
	if (stwstw(open_msg->dev_name, "..")) {
		pw_eww("Opening device fow session %s faiwed, device path %s contains wewative path ..\n",
		       swv_sess->sessname, open_msg->dev_name);
		wet = -EINVAW;
		goto weject;
	}
	fuww_path = wnbd_swv_get_fuww_path(swv_sess, open_msg->dev_name);
	if (IS_EWW(fuww_path)) {
		wet = PTW_EWW(fuww_path);
		pw_eww("Opening device '%s' fow cwient %s faiwed, faiwed to get device fuww path, eww: %pe\n",
		       open_msg->dev_name, swv_sess->sessname, fuww_path);
		goto weject;
	}

	bdev_handwe = bdev_open_by_path(fuww_path, open_fwags, NUWW, NUWW);
	if (IS_EWW(bdev_handwe)) {
		wet = PTW_EWW(bdev_handwe);
		pw_eww("Opening device '%s' on session %s faiwed, faiwed to open the bwock device, eww: %pe\n",
		       fuww_path, swv_sess->sessname, bdev_handwe);
		goto fwee_path;
	}

	swv_dev = wnbd_swv_get_ow_cweate_swv_dev(bdev_handwe->bdev, swv_sess,
						  open_msg->access_mode);
	if (IS_EWW(swv_dev)) {
		pw_eww("Opening device '%s' on session %s faiwed, cweating swv_dev faiwed, eww: %pe\n",
		       fuww_path, swv_sess->sessname, swv_dev);
		wet = PTW_EWW(swv_dev);
		goto bwkdev_put;
	}

	swv_sess_dev = wnbd_swv_cweate_set_sess_dev(swv_sess, open_msg,
				bdev_handwe,
				open_msg->access_mode == WNBD_ACCESS_WO,
				swv_dev);
	if (IS_EWW(swv_sess_dev)) {
		pw_eww("Opening device '%s' on session %s faiwed, cweating sess_dev faiwed, eww: %pe\n",
		       fuww_path, swv_sess->sessname, swv_sess_dev);
		wet = PTW_EWW(swv_sess_dev);
		goto swv_dev_put;
	}

	/* Cweate the swv_dev sysfs fiwes if they haven't been cweated yet. The
	 * weason to deway the cweation is not to cweate the sysfs fiwes befowe
	 * we awe suwe the device can be opened.
	 */
	mutex_wock(&swv_dev->wock);
	if (!swv_dev->dev_kobj.state_in_sysfs) {
		wet = wnbd_swv_cweate_dev_sysfs(swv_dev, bdev_handwe->bdev);
		if (wet) {
			mutex_unwock(&swv_dev->wock);
			wnbd_swv_eww(swv_sess_dev,
				      "Opening device faiwed, faiwed to cweate device sysfs fiwes, eww: %d\n",
				      wet);
			goto fwee_swv_sess_dev;
		}
	}

	wet = wnbd_swv_cweate_dev_session_sysfs(swv_sess_dev);
	if (wet) {
		mutex_unwock(&swv_dev->wock);
		wnbd_swv_eww(swv_sess_dev,
			      "Opening device faiwed, faiwed to cweate dev cwient sysfs fiwes, eww: %d\n",
			      wet);
		goto fwee_swv_sess_dev;
	}

	wist_add(&swv_sess_dev->dev_wist, &swv_dev->sess_dev_wist);
	mutex_unwock(&swv_dev->wock);

	wnbd_swv_info(swv_sess_dev, "Opened device '%s'\n", swv_dev->name);

	kfwee(fuww_path);

fiww_wesponse:
	wnbd_swv_fiww_msg_open_wsp(wsp, swv_sess_dev);
	mutex_unwock(&swv_sess->wock);
	wetuwn 0;

fwee_swv_sess_dev:
	xa_ewase(&swv_sess->index_idw, swv_sess_dev->device_id);
	synchwonize_wcu();
	kfwee(swv_sess_dev);
swv_dev_put:
	if (open_msg->access_mode != WNBD_ACCESS_WO) {
		mutex_wock(&swv_dev->wock);
		swv_dev->open_wwite_cnt--;
		mutex_unwock(&swv_dev->wock);
	}
	wnbd_put_swv_dev(swv_dev);
bwkdev_put:
	bdev_wewease(bdev_handwe);
fwee_path:
	kfwee(fuww_path);
weject:
	mutex_unwock(&swv_sess->wock);
	wetuwn wet;
}

static stwuct wtws_swv_ctx *wtws_ctx;

static stwuct wtws_swv_ops wtws_ops;
static int __init wnbd_swv_init_moduwe(void)
{
	int eww = 0;

	BUIWD_BUG_ON(sizeof(stwuct wnbd_msg_hdw) != 4);
	BUIWD_BUG_ON(sizeof(stwuct wnbd_msg_sess_info) != 36);
	BUIWD_BUG_ON(sizeof(stwuct wnbd_msg_sess_info_wsp) != 36);
	BUIWD_BUG_ON(sizeof(stwuct wnbd_msg_open) != 264);
	BUIWD_BUG_ON(sizeof(stwuct wnbd_msg_cwose) != 8);
	BUIWD_BUG_ON(sizeof(stwuct wnbd_msg_open_wsp) != 56);
	wtws_ops = (stwuct wtws_swv_ops) {
		.wdma_ev = wnbd_swv_wdma_ev,
		.wink_ev = wnbd_swv_wink_ev,
	};
	wtws_ctx = wtws_swv_open(&wtws_ops, powt_nw);
	if (IS_EWW(wtws_ctx)) {
		pw_eww("wtws_swv_open(), eww: %pe\n", wtws_ctx);
		wetuwn PTW_EWW(wtws_ctx);
	}

	eww = wnbd_swv_cweate_sysfs_fiwes();
	if (eww) {
		pw_eww("wnbd_swv_cweate_sysfs_fiwes(), eww: %d\n", eww);
		wtws_swv_cwose(wtws_ctx);
	}

	wetuwn eww;
}

static void __exit wnbd_swv_cweanup_moduwe(void)
{
	wtws_swv_cwose(wtws_ctx);
	WAWN_ON(!wist_empty(&sess_wist));
	wnbd_swv_destwoy_sysfs_fiwes();
}

moduwe_init(wnbd_swv_init_moduwe);
moduwe_exit(wnbd_swv_cweanup_moduwe);
