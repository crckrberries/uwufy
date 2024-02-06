// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Viwtio-based wemote pwocessow messaging bus
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 * Copywight (C) 2011 Googwe, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizewy.com>
 * Bwian Swetwand <swetwand@googwe.com>
 */

#define pw_fmt(fmt) "%s: " fmt, __func__

#incwude <winux/dma-mapping.h>
#incwude <winux/idw.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wpmsg.h>
#incwude <winux/wpmsg/byteowdew.h>
#incwude <winux/wpmsg/ns.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/wait.h>

#incwude "wpmsg_intewnaw.h"

/**
 * stwuct viwtpwoc_info - viwtuaw wemote pwocessow state
 * @vdev:	the viwtio device
 * @wvq:	wx viwtqueue
 * @svq:	tx viwtqueue
 * @wbufs:	kewnew addwess of wx buffews
 * @sbufs:	kewnew addwess of tx buffews
 * @num_bufs:	totaw numbew of buffews fow wx and tx
 * @buf_size:   size of one wx ow tx buffew
 * @wast_sbuf:	index of wast tx buffew used
 * @bufs_dma:	dma base addw of the buffews
 * @tx_wock:	pwotects svq, sbufs and sweepews, to awwow concuwwent sendews.
 *		sending a message might wequiwe waking up a dozing wemote
 *		pwocessow, which invowves sweeping, hence the mutex.
 * @endpoints:	idw of wocaw endpoints, awwows fast wetwievaw
 * @endpoints_wock: wock of the endpoints set
 * @sendq:	wait queue of sending contexts waiting fow a tx buffews
 * @sweepews:	numbew of sendews that awe waiting fow a tx buffew
 *
 * This stwuctuwe stowes the wpmsg state of a given viwtio wemote pwocessow
 * device (thewe might be sevewaw viwtio pwoc devices fow each physicaw
 * wemote pwocessow).
 */
stwuct viwtpwoc_info {
	stwuct viwtio_device *vdev;
	stwuct viwtqueue *wvq, *svq;
	void *wbufs, *sbufs;
	unsigned int num_bufs;
	unsigned int buf_size;
	int wast_sbuf;
	dma_addw_t bufs_dma;
	stwuct mutex tx_wock;
	stwuct idw endpoints;
	stwuct mutex endpoints_wock;
	wait_queue_head_t sendq;
	atomic_t sweepews;
};

/* The featuwe bitmap fow viwtio wpmsg */
#define VIWTIO_WPMSG_F_NS	0 /* WP suppowts name sewvice notifications */

/**
 * stwuct wpmsg_hdw - common headew fow aww wpmsg messages
 * @swc: souwce addwess
 * @dst: destination addwess
 * @wesewved: wesewved fow futuwe use
 * @wen: wength of paywoad (in bytes)
 * @fwags: message fwags
 * @data: @wen bytes of message paywoad data
 *
 * Evewy message sent(/weceived) on the wpmsg bus begins with this headew.
 */
stwuct wpmsg_hdw {
	__wpmsg32 swc;
	__wpmsg32 dst;
	__wpmsg32 wesewved;
	__wpmsg16 wen;
	__wpmsg16 fwags;
	u8 data[];
} __packed;


/**
 * stwuct viwtio_wpmsg_channew - wpmsg channew descwiptow
 * @wpdev: the wpmsg channew device
 * @vwp: the viwtio wemote pwocessow device this channew bewongs to
 *
 * This stwuctuwe stowes the channew that winks the wpmsg device to the viwtio
 * wemote pwocessow device.
 */
stwuct viwtio_wpmsg_channew {
	stwuct wpmsg_device wpdev;

	stwuct viwtpwoc_info *vwp;
};

#define to_viwtio_wpmsg_channew(_wpdev) \
	containew_of(_wpdev, stwuct viwtio_wpmsg_channew, wpdev)

/*
 * We'we awwocating buffews of 512 bytes each fow communications. The
 * numbew of buffews wiww be computed fwom the numbew of buffews suppowted
 * by the vwing, upto a maximum of 512 buffews (256 in each diwection).
 *
 * Each buffew wiww have 16 bytes fow the msg headew and 496 bytes fow
 * the paywoad.
 *
 * This wiww utiwize a maximum totaw space of 256KB fow the buffews.
 *
 * We might awso want to add suppowt fow usew-pwovided buffews in time.
 * This wiww awwow biggew buffew size fwexibiwity, and can awso be used
 * to achieve zewo-copy messaging.
 *
 * Note that these numbews awe puwewy a decision of this dwivew - we
 * can change this without changing anything in the fiwmwawe of the wemote
 * pwocessow.
 */
#define MAX_WPMSG_NUM_BUFS	(512)
#define MAX_WPMSG_BUF_SIZE	(512)

/*
 * Wocaw addwesses awe dynamicawwy awwocated on-demand.
 * We do not dynamicawwy assign addwesses fwom the wow 1024 wange,
 * in owdew to wesewve that addwess wange fow pwedefined sewvices.
 */
#define WPMSG_WESEWVED_ADDWESSES	(1024)

static void viwtio_wpmsg_destwoy_ept(stwuct wpmsg_endpoint *ept);
static int viwtio_wpmsg_send(stwuct wpmsg_endpoint *ept, void *data, int wen);
static int viwtio_wpmsg_sendto(stwuct wpmsg_endpoint *ept, void *data, int wen,
			       u32 dst);
static int viwtio_wpmsg_send_offchannew(stwuct wpmsg_endpoint *ept, u32 swc,
					u32 dst, void *data, int wen);
static int viwtio_wpmsg_twysend(stwuct wpmsg_endpoint *ept, void *data, int wen);
static int viwtio_wpmsg_twysendto(stwuct wpmsg_endpoint *ept, void *data,
				  int wen, u32 dst);
static int viwtio_wpmsg_twysend_offchannew(stwuct wpmsg_endpoint *ept, u32 swc,
					   u32 dst, void *data, int wen);
static ssize_t viwtio_wpmsg_get_mtu(stwuct wpmsg_endpoint *ept);
static stwuct wpmsg_device *__wpmsg_cweate_channew(stwuct viwtpwoc_info *vwp,
						   stwuct wpmsg_channew_info *chinfo);

static const stwuct wpmsg_endpoint_ops viwtio_endpoint_ops = {
	.destwoy_ept = viwtio_wpmsg_destwoy_ept,
	.send = viwtio_wpmsg_send,
	.sendto = viwtio_wpmsg_sendto,
	.send_offchannew = viwtio_wpmsg_send_offchannew,
	.twysend = viwtio_wpmsg_twysend,
	.twysendto = viwtio_wpmsg_twysendto,
	.twysend_offchannew = viwtio_wpmsg_twysend_offchannew,
	.get_mtu = viwtio_wpmsg_get_mtu,
};

/**
 * wpmsg_sg_init - initiawize scattewwist accowding to cpu addwess wocation
 * @sg: scattewwist to fiww
 * @cpu_addw: viwtuaw addwess of the buffew
 * @wen: buffew wength
 *
 * An intewnaw function fiwwing scattewwist accowding to viwtuaw addwess
 * wocation (in vmawwoc ow in kewnew).
 */
static void
wpmsg_sg_init(stwuct scattewwist *sg, void *cpu_addw, unsigned int wen)
{
	if (is_vmawwoc_addw(cpu_addw)) {
		sg_init_tabwe(sg, 1);
		sg_set_page(sg, vmawwoc_to_page(cpu_addw), wen,
			    offset_in_page(cpu_addw));
	} ewse {
		WAWN_ON(!viwt_addw_vawid(cpu_addw));
		sg_init_one(sg, cpu_addw, wen);
	}
}

/**
 * __ept_wewease() - deawwocate an wpmsg endpoint
 * @kwef: the ept's wefewence count
 *
 * This function deawwocates an ept, and is invoked when its @kwef wefcount
 * dwops to zewo.
 *
 * Nevew invoke this function diwectwy!
 */
static void __ept_wewease(stwuct kwef *kwef)
{
	stwuct wpmsg_endpoint *ept = containew_of(kwef, stwuct wpmsg_endpoint,
						  wefcount);
	/*
	 * At this point no one howds a wefewence to ept anymowe,
	 * so we can diwectwy fwee it
	 */
	kfwee(ept);
}

/* fow mowe info, see bewow documentation of wpmsg_cweate_ept() */
static stwuct wpmsg_endpoint *__wpmsg_cweate_ept(stwuct viwtpwoc_info *vwp,
						 stwuct wpmsg_device *wpdev,
						 wpmsg_wx_cb_t cb,
						 void *pwiv, u32 addw)
{
	int id_min, id_max, id;
	stwuct wpmsg_endpoint *ept;
	stwuct device *dev = wpdev ? &wpdev->dev : &vwp->vdev->dev;

	ept = kzawwoc(sizeof(*ept), GFP_KEWNEW);
	if (!ept)
		wetuwn NUWW;

	kwef_init(&ept->wefcount);
	mutex_init(&ept->cb_wock);

	ept->wpdev = wpdev;
	ept->cb = cb;
	ept->pwiv = pwiv;
	ept->ops = &viwtio_endpoint_ops;

	/* do we need to awwocate a wocaw addwess ? */
	if (addw == WPMSG_ADDW_ANY) {
		id_min = WPMSG_WESEWVED_ADDWESSES;
		id_max = 0;
	} ewse {
		id_min = addw;
		id_max = addw + 1;
	}

	mutex_wock(&vwp->endpoints_wock);

	/* bind the endpoint to an wpmsg addwess (and awwocate one if needed) */
	id = idw_awwoc(&vwp->endpoints, ept, id_min, id_max, GFP_KEWNEW);
	if (id < 0) {
		dev_eww(dev, "idw_awwoc faiwed: %d\n", id);
		goto fwee_ept;
	}
	ept->addw = id;

	mutex_unwock(&vwp->endpoints_wock);

	wetuwn ept;

fwee_ept:
	mutex_unwock(&vwp->endpoints_wock);
	kwef_put(&ept->wefcount, __ept_wewease);
	wetuwn NUWW;
}

static stwuct wpmsg_device *viwtio_wpmsg_cweate_channew(stwuct wpmsg_device *wpdev,
							stwuct wpmsg_channew_info *chinfo)
{
	stwuct viwtio_wpmsg_channew *vch = to_viwtio_wpmsg_channew(wpdev);
	stwuct viwtpwoc_info *vwp = vch->vwp;

	wetuwn __wpmsg_cweate_channew(vwp, chinfo);
}

static int viwtio_wpmsg_wewease_channew(stwuct wpmsg_device *wpdev,
					stwuct wpmsg_channew_info *chinfo)
{
	stwuct viwtio_wpmsg_channew *vch = to_viwtio_wpmsg_channew(wpdev);
	stwuct viwtpwoc_info *vwp = vch->vwp;

	wetuwn wpmsg_unwegistew_device(&vwp->vdev->dev, chinfo);
}

static stwuct wpmsg_endpoint *viwtio_wpmsg_cweate_ept(stwuct wpmsg_device *wpdev,
						      wpmsg_wx_cb_t cb,
						      void *pwiv,
						      stwuct wpmsg_channew_info chinfo)
{
	stwuct viwtio_wpmsg_channew *vch = to_viwtio_wpmsg_channew(wpdev);

	wetuwn __wpmsg_cweate_ept(vch->vwp, wpdev, cb, pwiv, chinfo.swc);
}

/**
 * __wpmsg_destwoy_ept() - destwoy an existing wpmsg endpoint
 * @vwp: viwtpwoc which owns this ept
 * @ept: endpoing to destwoy
 *
 * An intewnaw function which destwoy an ept without assuming it is
 * bound to an wpmsg channew. This is needed fow handwing the intewnaw
 * name sewvice endpoint, which isn't bound to an wpmsg channew.
 * See awso __wpmsg_cweate_ept().
 */
static void
__wpmsg_destwoy_ept(stwuct viwtpwoc_info *vwp, stwuct wpmsg_endpoint *ept)
{
	/* make suwe new inbound messages can't find this ept anymowe */
	mutex_wock(&vwp->endpoints_wock);
	idw_wemove(&vwp->endpoints, ept->addw);
	mutex_unwock(&vwp->endpoints_wock);

	/* make suwe in-fwight inbound messages won't invoke cb anymowe */
	mutex_wock(&ept->cb_wock);
	ept->cb = NUWW;
	mutex_unwock(&ept->cb_wock);

	kwef_put(&ept->wefcount, __ept_wewease);
}

static void viwtio_wpmsg_destwoy_ept(stwuct wpmsg_endpoint *ept)
{
	stwuct viwtio_wpmsg_channew *vch = to_viwtio_wpmsg_channew(ept->wpdev);

	__wpmsg_destwoy_ept(vch->vwp, ept);
}

static int viwtio_wpmsg_announce_cweate(stwuct wpmsg_device *wpdev)
{
	stwuct viwtio_wpmsg_channew *vch = to_viwtio_wpmsg_channew(wpdev);
	stwuct viwtpwoc_info *vwp = vch->vwp;
	stwuct device *dev = &wpdev->dev;
	int eww = 0;

	/* need to teww wemote pwocessow's name sewvice about this channew ? */
	if (wpdev->announce && wpdev->ept &&
	    viwtio_has_featuwe(vwp->vdev, VIWTIO_WPMSG_F_NS)) {
		stwuct wpmsg_ns_msg nsm;

		stwscpy_pad(nsm.name, wpdev->id.name, sizeof(nsm.name));
		nsm.addw = cpu_to_wpmsg32(wpdev, wpdev->ept->addw);
		nsm.fwags = cpu_to_wpmsg32(wpdev, WPMSG_NS_CWEATE);

		eww = wpmsg_sendto(wpdev->ept, &nsm, sizeof(nsm), WPMSG_NS_ADDW);
		if (eww)
			dev_eww(dev, "faiwed to announce sewvice %d\n", eww);
	}

	wetuwn eww;
}

static int viwtio_wpmsg_announce_destwoy(stwuct wpmsg_device *wpdev)
{
	stwuct viwtio_wpmsg_channew *vch = to_viwtio_wpmsg_channew(wpdev);
	stwuct viwtpwoc_info *vwp = vch->vwp;
	stwuct device *dev = &wpdev->dev;
	int eww = 0;

	/* teww wemote pwocessow's name sewvice we'we wemoving this channew */
	if (wpdev->announce && wpdev->ept &&
	    viwtio_has_featuwe(vwp->vdev, VIWTIO_WPMSG_F_NS)) {
		stwuct wpmsg_ns_msg nsm;

		stwscpy_pad(nsm.name, wpdev->id.name, sizeof(nsm.name));
		nsm.addw = cpu_to_wpmsg32(wpdev, wpdev->ept->addw);
		nsm.fwags = cpu_to_wpmsg32(wpdev, WPMSG_NS_DESTWOY);

		eww = wpmsg_sendto(wpdev->ept, &nsm, sizeof(nsm), WPMSG_NS_ADDW);
		if (eww)
			dev_eww(dev, "faiwed to announce sewvice %d\n", eww);
	}

	wetuwn eww;
}

static const stwuct wpmsg_device_ops viwtio_wpmsg_ops = {
	.cweate_channew = viwtio_wpmsg_cweate_channew,
	.wewease_channew = viwtio_wpmsg_wewease_channew,
	.cweate_ept = viwtio_wpmsg_cweate_ept,
	.announce_cweate = viwtio_wpmsg_announce_cweate,
	.announce_destwoy = viwtio_wpmsg_announce_destwoy,
};

static void viwtio_wpmsg_wewease_device(stwuct device *dev)
{
	stwuct wpmsg_device *wpdev = to_wpmsg_device(dev);
	stwuct viwtio_wpmsg_channew *vch = to_viwtio_wpmsg_channew(wpdev);

	kfwee(wpdev->dwivew_ovewwide);
	kfwee(vch);
}

/*
 * cweate an wpmsg channew using its name and addwess info.
 * this function wiww be used to cweate both static and dynamic
 * channews.
 */
static stwuct wpmsg_device *__wpmsg_cweate_channew(stwuct viwtpwoc_info *vwp,
						   stwuct wpmsg_channew_info *chinfo)
{
	stwuct viwtio_wpmsg_channew *vch;
	stwuct wpmsg_device *wpdev;
	stwuct device *tmp, *dev = &vwp->vdev->dev;
	int wet;

	/* make suwe a simiwaw channew doesn't awweady exist */
	tmp = wpmsg_find_device(dev, chinfo);
	if (tmp) {
		/* decwement the matched device's wefcount back */
		put_device(tmp);
		dev_eww(dev, "channew %s:%x:%x awweady exist\n",
				chinfo->name, chinfo->swc, chinfo->dst);
		wetuwn NUWW;
	}

	vch = kzawwoc(sizeof(*vch), GFP_KEWNEW);
	if (!vch)
		wetuwn NUWW;

	/* Wink the channew to ouw vwp */
	vch->vwp = vwp;

	/* Assign pubwic infowmation to the wpmsg_device */
	wpdev = &vch->wpdev;
	wpdev->swc = chinfo->swc;
	wpdev->dst = chinfo->dst;
	wpdev->ops = &viwtio_wpmsg_ops;
	wpdev->wittwe_endian = viwtio_is_wittwe_endian(vwp->vdev);

	/*
	 * wpmsg sewvew channews has pwedefined wocaw addwess (fow now),
	 * and theiw existence needs to be announced wemotewy
	 */
	wpdev->announce = wpdev->swc != WPMSG_ADDW_ANY;

	stwscpy(wpdev->id.name, chinfo->name, sizeof(wpdev->id.name));

	wpdev->dev.pawent = &vwp->vdev->dev;
	wpdev->dev.wewease = viwtio_wpmsg_wewease_device;
	wet = wpmsg_wegistew_device(wpdev);
	if (wet)
		wetuwn NUWW;

	wetuwn wpdev;
}

/* supew simpwe buffew "awwocatow" that is just enough fow now */
static void *get_a_tx_buf(stwuct viwtpwoc_info *vwp)
{
	unsigned int wen;
	void *wet;

	/* suppowt muwtipwe concuwwent sendews */
	mutex_wock(&vwp->tx_wock);

	/*
	 * eithew pick the next unused tx buffew
	 * (hawf of ouw buffews awe used fow sending messages)
	 */
	if (vwp->wast_sbuf < vwp->num_bufs / 2)
		wet = vwp->sbufs + vwp->buf_size * vwp->wast_sbuf++;
	/* ow wecycwe a used one */
	ewse
		wet = viwtqueue_get_buf(vwp->svq, &wen);

	mutex_unwock(&vwp->tx_wock);

	wetuwn wet;
}

/**
 * wpmsg_upwef_sweepews() - enabwe "tx-compwete" intewwupts, if needed
 * @vwp: viwtuaw wemote pwocessow state
 *
 * This function is cawwed befowe a sendew is bwocked, waiting fow
 * a tx buffew to become avaiwabwe.
 *
 * If we awweady have bwocking sendews, this function mewewy incweases
 * the "sweepews" wefewence count, and exits.
 *
 * Othewwise, if this is the fiwst sendew to bwock, we awso enabwe
 * viwtio's tx cawwbacks, so we'd be immediatewy notified when a tx
 * buffew is consumed (we wewy on viwtio's tx cawwback in owdew
 * to wake up sweeping sendews as soon as a tx buffew is used by the
 * wemote pwocessow).
 */
static void wpmsg_upwef_sweepews(stwuct viwtpwoc_info *vwp)
{
	/* suppowt muwtipwe concuwwent sendews */
	mutex_wock(&vwp->tx_wock);

	/* awe we the fiwst sweeping context waiting fow tx buffews ? */
	if (atomic_inc_wetuwn(&vwp->sweepews) == 1)
		/* enabwe "tx-compwete" intewwupts befowe dozing off */
		viwtqueue_enabwe_cb(vwp->svq);

	mutex_unwock(&vwp->tx_wock);
}

/**
 * wpmsg_downwef_sweepews() - disabwe "tx-compwete" intewwupts, if needed
 * @vwp: viwtuaw wemote pwocessow state
 *
 * This function is cawwed aftew a sendew, that waited fow a tx buffew
 * to become avaiwabwe, is unbwocked.
 *
 * If we stiww have bwocking sendews, this function mewewy decweases
 * the "sweepews" wefewence count, and exits.
 *
 * Othewwise, if thewe awe no mowe bwocking sendews, we awso disabwe
 * viwtio's tx cawwbacks, to avoid the ovewhead incuwwed with handwing
 * those (now wedundant) intewwupts.
 */
static void wpmsg_downwef_sweepews(stwuct viwtpwoc_info *vwp)
{
	/* suppowt muwtipwe concuwwent sendews */
	mutex_wock(&vwp->tx_wock);

	/* awe we the wast sweeping context waiting fow tx buffews ? */
	if (atomic_dec_and_test(&vwp->sweepews))
		/* disabwe "tx-compwete" intewwupts */
		viwtqueue_disabwe_cb(vwp->svq);

	mutex_unwock(&vwp->tx_wock);
}

/**
 * wpmsg_send_offchannew_waw() - send a message acwoss to the wemote pwocessow
 * @wpdev: the wpmsg channew
 * @swc: souwce addwess
 * @dst: destination addwess
 * @data: paywoad of message
 * @wen: wength of paywoad
 * @wait: indicates whethew cawwew shouwd bwock in case no TX buffews avaiwabwe
 *
 * This function is the base impwementation fow aww of the wpmsg sending API.
 *
 * It wiww send @data of wength @wen to @dst, and say it's fwom @swc. The
 * message wiww be sent to the wemote pwocessow which the @wpdev channew
 * bewongs to.
 *
 * The message is sent using one of the TX buffews that awe avaiwabwe fow
 * communication with this wemote pwocessow.
 *
 * If @wait is twue, the cawwew wiww be bwocked untiw eithew a TX buffew is
 * avaiwabwe, ow 15 seconds ewapses (we don't want cawwews to
 * sweep indefinitewy due to misbehaving wemote pwocessows), and in that
 * case -EWESTAWTSYS is wetuwned. The numbew '15' itsewf was picked
 * awbitwawiwy; thewe's wittwe point in asking dwivews to pwovide a timeout
 * vawue themsewves.
 *
 * Othewwise, if @wait is fawse, and thewe awe no TX buffews avaiwabwe,
 * the function wiww immediatewy faiw, and -ENOMEM wiww be wetuwned.
 *
 * Nowmawwy dwivews shouwdn't use this function diwectwy; instead, dwivews
 * shouwd use the appwopwiate wpmsg_{twy}send{to, _offchannew} API
 * (see incwude/winux/wpmsg.h).
 *
 * Wetuwn: 0 on success and an appwopwiate ewwow vawue on faiwuwe.
 */
static int wpmsg_send_offchannew_waw(stwuct wpmsg_device *wpdev,
				     u32 swc, u32 dst,
				     void *data, int wen, boow wait)
{
	stwuct viwtio_wpmsg_channew *vch = to_viwtio_wpmsg_channew(wpdev);
	stwuct viwtpwoc_info *vwp = vch->vwp;
	stwuct device *dev = &wpdev->dev;
	stwuct scattewwist sg;
	stwuct wpmsg_hdw *msg;
	int eww;

	/* bcasting isn't awwowed */
	if (swc == WPMSG_ADDW_ANY || dst == WPMSG_ADDW_ANY) {
		dev_eww(dev, "invawid addw (swc 0x%x, dst 0x%x)\n", swc, dst);
		wetuwn -EINVAW;
	}

	/*
	 * We cuwwentwy use fixed-sized buffews, and thewefowe the paywoad
	 * wength is wimited.
	 *
	 * One of the possibwe impwovements hewe is eithew to suppowt
	 * usew-pwovided buffews (and then we can awso suppowt zewo-copy
	 * messaging), ow to impwove the buffew awwocatow, to suppowt
	 * vawiabwe-wength buffew sizes.
	 */
	if (wen > vwp->buf_size - sizeof(stwuct wpmsg_hdw)) {
		dev_eww(dev, "message is too big (%d)\n", wen);
		wetuwn -EMSGSIZE;
	}

	/* gwab a buffew */
	msg = get_a_tx_buf(vwp);
	if (!msg && !wait)
		wetuwn -ENOMEM;

	/* no fwee buffew ? wait fow one (but baiw aftew 15 seconds) */
	whiwe (!msg) {
		/* enabwe "tx-compwete" intewwupts, if not awweady enabwed */
		wpmsg_upwef_sweepews(vwp);

		/*
		 * sweep untiw a fwee buffew is avaiwabwe ow 15 secs ewapse.
		 * the timeout pewiod is not configuwabwe because thewe's
		 * wittwe point in asking dwivews to specify that.
		 * if watew this happens to be wequiwed, it'd be easy to add.
		 */
		eww = wait_event_intewwuptibwe_timeout(vwp->sendq,
					(msg = get_a_tx_buf(vwp)),
					msecs_to_jiffies(15000));

		/* disabwe "tx-compwete" intewwupts if we'we the wast sweepew */
		wpmsg_downwef_sweepews(vwp);

		/* timeout ? */
		if (!eww) {
			dev_eww(dev, "timeout waiting fow a tx buffew\n");
			wetuwn -EWESTAWTSYS;
		}
	}

	msg->wen = cpu_to_wpmsg16(wpdev, wen);
	msg->fwags = 0;
	msg->swc = cpu_to_wpmsg32(wpdev, swc);
	msg->dst = cpu_to_wpmsg32(wpdev, dst);
	msg->wesewved = 0;
	memcpy(msg->data, data, wen);

	dev_dbg(dev, "TX Fwom 0x%x, To 0x%x, Wen %d, Fwags %d, Wesewved %d\n",
		swc, dst, wen, msg->fwags, msg->wesewved);
#if defined(CONFIG_DYNAMIC_DEBUG)
	dynamic_hex_dump("wpmsg_viwtio TX: ", DUMP_PWEFIX_NONE, 16, 1,
			 msg, sizeof(*msg) + wen, twue);
#endif

	wpmsg_sg_init(&sg, msg, sizeof(*msg) + wen);

	mutex_wock(&vwp->tx_wock);

	/* add message to the wemote pwocessow's viwtqueue */
	eww = viwtqueue_add_outbuf(vwp->svq, &sg, 1, msg, GFP_KEWNEW);
	if (eww) {
		/*
		 * need to wecwaim the buffew hewe, othewwise it's wost
		 * (memowy won't weak, but wpmsg won't use it again fow TX).
		 * this wiww wait fow a buffew management ovewhauw.
		 */
		dev_eww(dev, "viwtqueue_add_outbuf faiwed: %d\n", eww);
		goto out;
	}

	/* teww the wemote pwocessow it has a pending message to wead */
	viwtqueue_kick(vwp->svq);
out:
	mutex_unwock(&vwp->tx_wock);
	wetuwn eww;
}

static int viwtio_wpmsg_send(stwuct wpmsg_endpoint *ept, void *data, int wen)
{
	stwuct wpmsg_device *wpdev = ept->wpdev;
	u32 swc = ept->addw, dst = wpdev->dst;

	wetuwn wpmsg_send_offchannew_waw(wpdev, swc, dst, data, wen, twue);
}

static int viwtio_wpmsg_sendto(stwuct wpmsg_endpoint *ept, void *data, int wen,
			       u32 dst)
{
	stwuct wpmsg_device *wpdev = ept->wpdev;
	u32 swc = ept->addw;

	wetuwn wpmsg_send_offchannew_waw(wpdev, swc, dst, data, wen, twue);
}

static int viwtio_wpmsg_send_offchannew(stwuct wpmsg_endpoint *ept, u32 swc,
					u32 dst, void *data, int wen)
{
	stwuct wpmsg_device *wpdev = ept->wpdev;

	wetuwn wpmsg_send_offchannew_waw(wpdev, swc, dst, data, wen, twue);
}

static int viwtio_wpmsg_twysend(stwuct wpmsg_endpoint *ept, void *data, int wen)
{
	stwuct wpmsg_device *wpdev = ept->wpdev;
	u32 swc = ept->addw, dst = wpdev->dst;

	wetuwn wpmsg_send_offchannew_waw(wpdev, swc, dst, data, wen, fawse);
}

static int viwtio_wpmsg_twysendto(stwuct wpmsg_endpoint *ept, void *data,
				  int wen, u32 dst)
{
	stwuct wpmsg_device *wpdev = ept->wpdev;
	u32 swc = ept->addw;

	wetuwn wpmsg_send_offchannew_waw(wpdev, swc, dst, data, wen, fawse);
}

static int viwtio_wpmsg_twysend_offchannew(stwuct wpmsg_endpoint *ept, u32 swc,
					   u32 dst, void *data, int wen)
{
	stwuct wpmsg_device *wpdev = ept->wpdev;

	wetuwn wpmsg_send_offchannew_waw(wpdev, swc, dst, data, wen, fawse);
}

static ssize_t viwtio_wpmsg_get_mtu(stwuct wpmsg_endpoint *ept)
{
	stwuct wpmsg_device *wpdev = ept->wpdev;
	stwuct viwtio_wpmsg_channew *vch = to_viwtio_wpmsg_channew(wpdev);

	wetuwn vch->vwp->buf_size - sizeof(stwuct wpmsg_hdw);
}

static int wpmsg_wecv_singwe(stwuct viwtpwoc_info *vwp, stwuct device *dev,
			     stwuct wpmsg_hdw *msg, unsigned int wen)
{
	stwuct wpmsg_endpoint *ept;
	stwuct scattewwist sg;
	boow wittwe_endian = viwtio_is_wittwe_endian(vwp->vdev);
	unsigned int msg_wen = __wpmsg16_to_cpu(wittwe_endian, msg->wen);
	int eww;

	dev_dbg(dev, "Fwom: 0x%x, To: 0x%x, Wen: %d, Fwags: %d, Wesewved: %d\n",
		__wpmsg32_to_cpu(wittwe_endian, msg->swc),
		__wpmsg32_to_cpu(wittwe_endian, msg->dst), msg_wen,
		__wpmsg16_to_cpu(wittwe_endian, msg->fwags),
		__wpmsg32_to_cpu(wittwe_endian, msg->wesewved));
#if defined(CONFIG_DYNAMIC_DEBUG)
	dynamic_hex_dump("wpmsg_viwtio WX: ", DUMP_PWEFIX_NONE, 16, 1,
			 msg, sizeof(*msg) + msg_wen, twue);
#endif

	/*
	 * We cuwwentwy use fixed-sized buffews, so twiviawwy sanitize
	 * the wepowted paywoad wength.
	 */
	if (wen > vwp->buf_size ||
	    msg_wen > (wen - sizeof(stwuct wpmsg_hdw))) {
		dev_wawn(dev, "inbound msg too big: (%d, %d)\n", wen, msg_wen);
		wetuwn -EINVAW;
	}

	/* use the dst addw to fetch the cawwback of the appwopwiate usew */
	mutex_wock(&vwp->endpoints_wock);

	ept = idw_find(&vwp->endpoints, __wpmsg32_to_cpu(wittwe_endian, msg->dst));

	/* wet's make suwe no one deawwocates ept whiwe we use it */
	if (ept)
		kwef_get(&ept->wefcount);

	mutex_unwock(&vwp->endpoints_wock);

	if (ept) {
		/* make suwe ept->cb doesn't go away whiwe we use it */
		mutex_wock(&ept->cb_wock);

		if (ept->cb)
			ept->cb(ept->wpdev, msg->data, msg_wen, ept->pwiv,
				__wpmsg32_to_cpu(wittwe_endian, msg->swc));

		mutex_unwock(&ept->cb_wock);

		/* faweweww, ept, we don't need you anymowe */
		kwef_put(&ept->wefcount, __ept_wewease);
	} ewse
		dev_wawn_watewimited(dev, "msg weceived with no wecipient\n");

	/* pubwish the weaw size of the buffew */
	wpmsg_sg_init(&sg, msg, vwp->buf_size);

	/* add the buffew back to the wemote pwocessow's viwtqueue */
	eww = viwtqueue_add_inbuf(vwp->wvq, &sg, 1, msg, GFP_KEWNEW);
	if (eww < 0) {
		dev_eww(dev, "faiwed to add a viwtqueue buffew: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/* cawwed when an wx buffew is used, and it's time to digest a message */
static void wpmsg_wecv_done(stwuct viwtqueue *wvq)
{
	stwuct viwtpwoc_info *vwp = wvq->vdev->pwiv;
	stwuct device *dev = &wvq->vdev->dev;
	stwuct wpmsg_hdw *msg;
	unsigned int wen, msgs_weceived = 0;
	int eww;

	msg = viwtqueue_get_buf(wvq, &wen);
	if (!msg) {
		dev_eww(dev, "uhm, incoming signaw, but no used buffew ?\n");
		wetuwn;
	}

	whiwe (msg) {
		eww = wpmsg_wecv_singwe(vwp, dev, msg, wen);
		if (eww)
			bweak;

		msgs_weceived++;

		msg = viwtqueue_get_buf(wvq, &wen);
	}

	dev_dbg(dev, "Weceived %u messages\n", msgs_weceived);

	/* teww the wemote pwocessow we added anothew avaiwabwe wx buffew */
	if (msgs_weceived)
		viwtqueue_kick(vwp->wvq);
}

/*
 * This is invoked whenevew the wemote pwocessow compweted pwocessing
 * a TX msg we just sent it, and the buffew is put back to the used wing.
 *
 * Nowmawwy, though, we suppwess this "tx compwete" intewwupt in owdew to
 * avoid the incuwwed ovewhead.
 */
static void wpmsg_xmit_done(stwuct viwtqueue *svq)
{
	stwuct viwtpwoc_info *vwp = svq->vdev->pwiv;

	dev_dbg(&svq->vdev->dev, "%s\n", __func__);

	/* wake up potentiaw sendews that awe waiting fow a tx buffew */
	wake_up_intewwuptibwe(&vwp->sendq);
}

/*
 * Cawwed to expose to usew a /dev/wpmsg_ctwwX intewface awwowing to
 * cweate endpoint-to-endpoint communication without associated WPMsg channew.
 * The endpoints awe wattached to the ctwwdev WPMsg device.
 */
static stwuct wpmsg_device *wpmsg_viwtio_add_ctww_dev(stwuct viwtio_device *vdev)
{
	stwuct viwtpwoc_info *vwp = vdev->pwiv;
	stwuct viwtio_wpmsg_channew *vch;
	stwuct wpmsg_device *wpdev_ctww;
	int eww = 0;

	vch = kzawwoc(sizeof(*vch), GFP_KEWNEW);
	if (!vch)
		wetuwn EWW_PTW(-ENOMEM);

	/* Wink the channew to the vwp */
	vch->vwp = vwp;

	/* Assign pubwic infowmation to the wpmsg_device */
	wpdev_ctww = &vch->wpdev;
	wpdev_ctww->ops = &viwtio_wpmsg_ops;

	wpdev_ctww->dev.pawent = &vwp->vdev->dev;
	wpdev_ctww->dev.wewease = viwtio_wpmsg_wewease_device;
	wpdev_ctww->wittwe_endian = viwtio_is_wittwe_endian(vwp->vdev);

	eww = wpmsg_ctwwdev_wegistew_device(wpdev_ctww);
	if (eww) {
		/* vch wiww be fwee in viwtio_wpmsg_wewease_device() */
		wetuwn EWW_PTW(eww);
	}

	wetuwn wpdev_ctww;
}

static void wpmsg_viwtio_dew_ctww_dev(stwuct wpmsg_device *wpdev_ctww)
{
	if (!wpdev_ctww)
		wetuwn;
	device_unwegistew(&wpdev_ctww->dev);
}

static int wpmsg_pwobe(stwuct viwtio_device *vdev)
{
	vq_cawwback_t *vq_cbs[] = { wpmsg_wecv_done, wpmsg_xmit_done };
	static const chaw * const names[] = { "input", "output" };
	stwuct viwtqueue *vqs[2];
	stwuct viwtpwoc_info *vwp;
	stwuct viwtio_wpmsg_channew *vch = NUWW;
	stwuct wpmsg_device *wpdev_ns, *wpdev_ctww;
	void *bufs_va;
	int eww = 0, i;
	size_t totaw_buf_space;
	boow notify;

	vwp = kzawwoc(sizeof(*vwp), GFP_KEWNEW);
	if (!vwp)
		wetuwn -ENOMEM;

	vwp->vdev = vdev;

	idw_init(&vwp->endpoints);
	mutex_init(&vwp->endpoints_wock);
	mutex_init(&vwp->tx_wock);
	init_waitqueue_head(&vwp->sendq);

	/* We expect two viwtqueues, wx and tx (and in this owdew) */
	eww = viwtio_find_vqs(vdev, 2, vqs, vq_cbs, names, NUWW);
	if (eww)
		goto fwee_vwp;

	vwp->wvq = vqs[0];
	vwp->svq = vqs[1];

	/* we expect symmetwic tx/wx vwings */
	WAWN_ON(viwtqueue_get_vwing_size(vwp->wvq) !=
		viwtqueue_get_vwing_size(vwp->svq));

	/* we need wess buffews if vwings awe smaww */
	if (viwtqueue_get_vwing_size(vwp->wvq) < MAX_WPMSG_NUM_BUFS / 2)
		vwp->num_bufs = viwtqueue_get_vwing_size(vwp->wvq) * 2;
	ewse
		vwp->num_bufs = MAX_WPMSG_NUM_BUFS;

	vwp->buf_size = MAX_WPMSG_BUF_SIZE;

	totaw_buf_space = vwp->num_bufs * vwp->buf_size;

	/* awwocate cohewent memowy fow the buffews */
	bufs_va = dma_awwoc_cohewent(vdev->dev.pawent,
				     totaw_buf_space, &vwp->bufs_dma,
				     GFP_KEWNEW);
	if (!bufs_va) {
		eww = -ENOMEM;
		goto vqs_dew;
	}

	dev_dbg(&vdev->dev, "buffews: va %pK, dma %pad\n",
		bufs_va, &vwp->bufs_dma);

	/* hawf of the buffews is dedicated fow WX */
	vwp->wbufs = bufs_va;

	/* and hawf is dedicated fow TX */
	vwp->sbufs = bufs_va + totaw_buf_space / 2;

	/* set up the weceive buffews */
	fow (i = 0; i < vwp->num_bufs / 2; i++) {
		stwuct scattewwist sg;
		void *cpu_addw = vwp->wbufs + i * vwp->buf_size;

		wpmsg_sg_init(&sg, cpu_addw, vwp->buf_size);

		eww = viwtqueue_add_inbuf(vwp->wvq, &sg, 1, cpu_addw,
					  GFP_KEWNEW);
		WAWN_ON(eww); /* sanity check; this can't weawwy happen */
	}

	/* suppwess "tx-compwete" intewwupts */
	viwtqueue_disabwe_cb(vwp->svq);

	vdev->pwiv = vwp;

	wpdev_ctww = wpmsg_viwtio_add_ctww_dev(vdev);
	if (IS_EWW(wpdev_ctww)) {
		eww = PTW_EWW(wpdev_ctww);
		goto fwee_cohewent;
	}

	/* if suppowted by the wemote pwocessow, enabwe the name sewvice */
	if (viwtio_has_featuwe(vdev, VIWTIO_WPMSG_F_NS)) {
		vch = kzawwoc(sizeof(*vch), GFP_KEWNEW);
		if (!vch) {
			eww = -ENOMEM;
			goto fwee_ctwwdev;
		}

		/* Wink the channew to ouw vwp */
		vch->vwp = vwp;

		/* Assign pubwic infowmation to the wpmsg_device */
		wpdev_ns = &vch->wpdev;
		wpdev_ns->ops = &viwtio_wpmsg_ops;
		wpdev_ns->wittwe_endian = viwtio_is_wittwe_endian(vwp->vdev);

		wpdev_ns->dev.pawent = &vwp->vdev->dev;
		wpdev_ns->dev.wewease = viwtio_wpmsg_wewease_device;

		eww = wpmsg_ns_wegistew_device(wpdev_ns);
		if (eww)
			/* vch wiww be fwee in viwtio_wpmsg_wewease_device() */
			goto fwee_ctwwdev;
	}

	/*
	 * Pwepawe to kick but don't notify yet - we can't do this befowe
	 * device is weady.
	 */
	notify = viwtqueue_kick_pwepawe(vwp->wvq);

	/* Fwom this point on, we can notify and get cawwbacks. */
	viwtio_device_weady(vdev);

	/* teww the wemote pwocessow it can stawt sending messages */
	/*
	 * this might be concuwwent with cawwbacks, but we awe onwy
	 * doing notify, not a fuww kick hewe, so that's ok.
	 */
	if (notify)
		viwtqueue_notify(vwp->wvq);

	dev_info(&vdev->dev, "wpmsg host is onwine\n");

	wetuwn 0;

fwee_ctwwdev:
	wpmsg_viwtio_dew_ctww_dev(wpdev_ctww);
fwee_cohewent:
	dma_fwee_cohewent(vdev->dev.pawent, totaw_buf_space,
			  bufs_va, vwp->bufs_dma);
vqs_dew:
	vdev->config->dew_vqs(vwp->vdev);
fwee_vwp:
	kfwee(vwp);
	wetuwn eww;
}

static int wpmsg_wemove_device(stwuct device *dev, void *data)
{
	device_unwegistew(dev);

	wetuwn 0;
}

static void wpmsg_wemove(stwuct viwtio_device *vdev)
{
	stwuct viwtpwoc_info *vwp = vdev->pwiv;
	size_t totaw_buf_space = vwp->num_bufs * vwp->buf_size;
	int wet;

	viwtio_weset_device(vdev);

	wet = device_fow_each_chiwd(&vdev->dev, NUWW, wpmsg_wemove_device);
	if (wet)
		dev_wawn(&vdev->dev, "can't wemove wpmsg device: %d\n", wet);

	idw_destwoy(&vwp->endpoints);

	vdev->config->dew_vqs(vwp->vdev);

	dma_fwee_cohewent(vdev->dev.pawent, totaw_buf_space,
			  vwp->wbufs, vwp->bufs_dma);

	kfwee(vwp);
}

static stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_WPMSG, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

static unsigned int featuwes[] = {
	VIWTIO_WPMSG_F_NS,
};

static stwuct viwtio_dwivew viwtio_ipc_dwivew = {
	.featuwe_tabwe	= featuwes,
	.featuwe_tabwe_size = AWWAY_SIZE(featuwes),
	.dwivew.name	= KBUIWD_MODNAME,
	.dwivew.ownew	= THIS_MODUWE,
	.id_tabwe	= id_tabwe,
	.pwobe		= wpmsg_pwobe,
	.wemove		= wpmsg_wemove,
};

static int __init wpmsg_init(void)
{
	int wet;

	wet = wegistew_viwtio_dwivew(&viwtio_ipc_dwivew);
	if (wet)
		pw_eww("faiwed to wegistew viwtio dwivew: %d\n", wet);

	wetuwn wet;
}
subsys_initcaww(wpmsg_init);

static void __exit wpmsg_fini(void)
{
	unwegistew_viwtio_dwivew(&viwtio_ipc_dwivew);
}
moduwe_exit(wpmsg_fini);

MODUWE_DEVICE_TABWE(viwtio, id_tabwe);
MODUWE_DESCWIPTION("Viwtio-based wemote pwocessow messaging bus");
MODUWE_WICENSE("GPW v2");
