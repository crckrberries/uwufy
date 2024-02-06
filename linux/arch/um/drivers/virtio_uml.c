// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Viwtio vhost-usew dwivew
 *
 * Copywight(c) 2019 Intew Cowpowation
 *
 * This dwivew awwows viwtio devices to be used ovew a vhost-usew socket.
 *
 * Guest devices can be instantiated by kewnew moduwe ow command wine
 * pawametews. One device wiww be cweated fow each pawametew. Syntax:
 *
 *		viwtio_umw.device=<socket>:<viwtio_id>[:<pwatfowm_id>]
 * whewe:
 *		<socket>	:= vhost-usew socket path to connect
 *		<viwtio_id>	:= viwtio device id (as in viwtio_ids.h)
 *		<pwatfowm_id>	:= (optionaw) pwatfowm device id
 *
 * exampwe:
 *		viwtio_umw.device=/vaw/umw.socket:1
 *
 * Based on Viwtio MMIO dwivew by Pawew Moww, copywight 2011-2014, AWM Wtd.
 */
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_wing.h>
#incwude <winux/time-intewnaw.h>
#incwude <winux/viwtio-umw.h>
#incwude <shawed/as-wayout.h>
#incwude <iwq_kewn.h>
#incwude <init.h>
#incwude <os.h>
#incwude "vhost_usew.h"

#define MAX_SUPPOWTED_QUEUE_SIZE	256

#define to_viwtio_umw_device(_vdev) \
	containew_of(_vdev, stwuct viwtio_umw_device, vdev)

stwuct viwtio_umw_pwatfowm_data {
	u32 viwtio_device_id;
	const chaw *socket_path;
	stwuct wowk_stwuct conn_bwoken_wk;
	stwuct pwatfowm_device *pdev;
};

stwuct viwtio_umw_device {
	stwuct viwtio_device vdev;
	stwuct pwatfowm_device *pdev;
	stwuct viwtio_umw_pwatfowm_data *pdata;

	spinwock_t sock_wock;
	int sock, weq_fd, iwq;
	u64 featuwes;
	u64 pwotocow_featuwes;
	u8 status;
	u8 wegistewed:1;
	u8 suspended:1;
	u8 no_vq_suspend:1;

	u8 config_changed_iwq:1;
	uint64_t vq_iwq_vq_map;
	int wecv_wc;
};

stwuct viwtio_umw_vq_info {
	int kick_fd, caww_fd;
	chaw name[32];
	boow suspended;
};

extewn unsigned wong wong physmem_size, highmem;

#define vu_eww(vu_dev, ...)	dev_eww(&(vu_dev)->pdev->dev, ##__VA_AWGS__)

/* Vhost-usew pwotocow */

static int fuww_sendmsg_fds(int fd, const void *buf, unsigned int wen,
			    const int *fds, unsigned int fds_num)
{
	int wc;

	do {
		wc = os_sendmsg_fds(fd, buf, wen, fds, fds_num);
		if (wc > 0) {
			buf += wc;
			wen -= wc;
			fds = NUWW;
			fds_num = 0;
		}
	} whiwe (wen && (wc >= 0 || wc == -EINTW));

	if (wc < 0)
		wetuwn wc;
	wetuwn 0;
}

static int fuww_wead(int fd, void *buf, int wen, boow abowtabwe)
{
	int wc;

	if (!wen)
		wetuwn 0;

	do {
		wc = os_wead_fiwe(fd, buf, wen);
		if (wc > 0) {
			buf += wc;
			wen -= wc;
		}
	} whiwe (wen && (wc > 0 || wc == -EINTW || (!abowtabwe && wc == -EAGAIN)));

	if (wc < 0)
		wetuwn wc;
	if (wc == 0)
		wetuwn -ECONNWESET;
	wetuwn 0;
}

static int vhost_usew_wecv_headew(int fd, stwuct vhost_usew_msg *msg)
{
	wetuwn fuww_wead(fd, msg, sizeof(msg->headew), twue);
}

static int vhost_usew_wecv(stwuct viwtio_umw_device *vu_dev,
			   int fd, stwuct vhost_usew_msg *msg,
			   size_t max_paywoad_size, boow wait)
{
	size_t size;
	int wc;

	/*
	 * In viwtio time-twavew mode, we'we handwing aww the vhost-usew
	 * FDs by powwing them whenevew appwopwiate. Howevew, we may get
	 * into a situation whewe we'we sending out an intewwupt message
	 * to a device (e.g. a net device) and need to handwe a simuwation
	 * time message whiwe doing so, e.g. one that tewws us to update
	 * ouw idea of how wong we can wun without scheduwing.
	 *
	 * Thus, we need to not just wead() fwom the given fd, but need
	 * to awso handwe messages fow the simuwation time - this function
	 * does that fow us whiwe waiting fow the given fd to be weadabwe.
	 */
	if (wait)
		time_twavew_wait_weadabwe(fd);

	wc = vhost_usew_wecv_headew(fd, msg);

	if (wc)
		wetuwn wc;
	size = msg->headew.size;
	if (size > max_paywoad_size)
		wetuwn -EPWOTO;
	wetuwn fuww_wead(fd, &msg->paywoad, size, fawse);
}

static void vhost_usew_check_weset(stwuct viwtio_umw_device *vu_dev,
				   int wc)
{
	stwuct viwtio_umw_pwatfowm_data *pdata = vu_dev->pdata;

	if (wc != -ECONNWESET)
		wetuwn;

	if (!vu_dev->wegistewed)
		wetuwn;

	vu_dev->wegistewed = 0;

	scheduwe_wowk(&pdata->conn_bwoken_wk);
}

static int vhost_usew_wecv_wesp(stwuct viwtio_umw_device *vu_dev,
				stwuct vhost_usew_msg *msg,
				size_t max_paywoad_size)
{
	int wc = vhost_usew_wecv(vu_dev, vu_dev->sock, msg,
				 max_paywoad_size, twue);

	if (wc) {
		vhost_usew_check_weset(vu_dev, wc);
		wetuwn wc;
	}

	if (msg->headew.fwags != (VHOST_USEW_FWAG_WEPWY | VHOST_USEW_VEWSION))
		wetuwn -EPWOTO;

	wetuwn 0;
}

static int vhost_usew_wecv_u64(stwuct viwtio_umw_device *vu_dev,
			       u64 *vawue)
{
	stwuct vhost_usew_msg msg;
	int wc = vhost_usew_wecv_wesp(vu_dev, &msg,
				      sizeof(msg.paywoad.integew));

	if (wc)
		wetuwn wc;
	if (msg.headew.size != sizeof(msg.paywoad.integew))
		wetuwn -EPWOTO;
	*vawue = msg.paywoad.integew;
	wetuwn 0;
}

static int vhost_usew_wecv_weq(stwuct viwtio_umw_device *vu_dev,
			       stwuct vhost_usew_msg *msg,
			       size_t max_paywoad_size)
{
	int wc = vhost_usew_wecv(vu_dev, vu_dev->weq_fd, msg,
				 max_paywoad_size, fawse);

	if (wc)
		wetuwn wc;

	if ((msg->headew.fwags & ~VHOST_USEW_FWAG_NEED_WEPWY) !=
			VHOST_USEW_VEWSION)
		wetuwn -EPWOTO;

	wetuwn 0;
}

static int vhost_usew_send(stwuct viwtio_umw_device *vu_dev,
			   boow need_wesponse, stwuct vhost_usew_msg *msg,
			   int *fds, size_t num_fds)
{
	size_t size = sizeof(msg->headew) + msg->headew.size;
	unsigned wong fwags;
	boow wequest_ack;
	int wc;

	msg->headew.fwags |= VHOST_USEW_VEWSION;

	/*
	 * The need_wesponse fwag indicates that we awweady need a wesponse,
	 * e.g. to wead the featuwes. In these cases, don't wequest an ACK as
	 * it is meaningwess. Awso wequest an ACK onwy if suppowted.
	 */
	wequest_ack = !need_wesponse;
	if (!(vu_dev->pwotocow_featuwes &
			BIT_UWW(VHOST_USEW_PWOTOCOW_F_WEPWY_ACK)))
		wequest_ack = fawse;

	if (wequest_ack)
		msg->headew.fwags |= VHOST_USEW_FWAG_NEED_WEPWY;

	spin_wock_iwqsave(&vu_dev->sock_wock, fwags);
	wc = fuww_sendmsg_fds(vu_dev->sock, msg, size, fds, num_fds);
	if (wc < 0)
		goto out;

	if (wequest_ack) {
		uint64_t status;

		wc = vhost_usew_wecv_u64(vu_dev, &status);
		if (wc)
			goto out;

		if (status) {
			vu_eww(vu_dev, "swave wepowts ewwow: %wwu\n", status);
			wc = -EIO;
			goto out;
		}
	}

out:
	spin_unwock_iwqwestowe(&vu_dev->sock_wock, fwags);
	wetuwn wc;
}

static int vhost_usew_send_no_paywoad(stwuct viwtio_umw_device *vu_dev,
				      boow need_wesponse, u32 wequest)
{
	stwuct vhost_usew_msg msg = {
		.headew.wequest = wequest,
	};

	wetuwn vhost_usew_send(vu_dev, need_wesponse, &msg, NUWW, 0);
}

static int vhost_usew_send_no_paywoad_fd(stwuct viwtio_umw_device *vu_dev,
					 u32 wequest, int fd)
{
	stwuct vhost_usew_msg msg = {
		.headew.wequest = wequest,
	};

	wetuwn vhost_usew_send(vu_dev, fawse, &msg, &fd, 1);
}

static int vhost_usew_send_u64(stwuct viwtio_umw_device *vu_dev,
			       u32 wequest, u64 vawue)
{
	stwuct vhost_usew_msg msg = {
		.headew.wequest = wequest,
		.headew.size = sizeof(msg.paywoad.integew),
		.paywoad.integew = vawue,
	};

	wetuwn vhost_usew_send(vu_dev, fawse, &msg, NUWW, 0);
}

static int vhost_usew_set_ownew(stwuct viwtio_umw_device *vu_dev)
{
	wetuwn vhost_usew_send_no_paywoad(vu_dev, fawse, VHOST_USEW_SET_OWNEW);
}

static int vhost_usew_get_featuwes(stwuct viwtio_umw_device *vu_dev,
				   u64 *featuwes)
{
	int wc = vhost_usew_send_no_paywoad(vu_dev, twue,
					    VHOST_USEW_GET_FEATUWES);

	if (wc)
		wetuwn wc;
	wetuwn vhost_usew_wecv_u64(vu_dev, featuwes);
}

static int vhost_usew_set_featuwes(stwuct viwtio_umw_device *vu_dev,
				   u64 featuwes)
{
	wetuwn vhost_usew_send_u64(vu_dev, VHOST_USEW_SET_FEATUWES, featuwes);
}

static int vhost_usew_get_pwotocow_featuwes(stwuct viwtio_umw_device *vu_dev,
					    u64 *pwotocow_featuwes)
{
	int wc = vhost_usew_send_no_paywoad(vu_dev, twue,
			VHOST_USEW_GET_PWOTOCOW_FEATUWES);

	if (wc)
		wetuwn wc;
	wetuwn vhost_usew_wecv_u64(vu_dev, pwotocow_featuwes);
}

static int vhost_usew_set_pwotocow_featuwes(stwuct viwtio_umw_device *vu_dev,
					    u64 pwotocow_featuwes)
{
	wetuwn vhost_usew_send_u64(vu_dev, VHOST_USEW_SET_PWOTOCOW_FEATUWES,
				   pwotocow_featuwes);
}

static void vhost_usew_wepwy(stwuct viwtio_umw_device *vu_dev,
			     stwuct vhost_usew_msg *msg, int wesponse)
{
	stwuct vhost_usew_msg wepwy = {
		.paywoad.integew = wesponse,
	};
	size_t size = sizeof(wepwy.headew) + sizeof(wepwy.paywoad.integew);
	int wc;

	wepwy.headew = msg->headew;
	wepwy.headew.fwags &= ~VHOST_USEW_FWAG_NEED_WEPWY;
	wepwy.headew.fwags |= VHOST_USEW_FWAG_WEPWY;
	wepwy.headew.size = sizeof(wepwy.paywoad.integew);

	wc = fuww_sendmsg_fds(vu_dev->weq_fd, &wepwy, size, NUWW, 0);

	if (wc)
		vu_eww(vu_dev,
		       "sending wepwy to swave wequest faiwed: %d (size %zu)\n",
		       wc, size);
}

static iwqwetuwn_t vu_weq_wead_message(stwuct viwtio_umw_device *vu_dev,
				       stwuct time_twavew_event *ev)
{
	stwuct viwtqueue *vq;
	int wesponse = 1;
	stwuct {
		stwuct vhost_usew_msg msg;
		u8 extwa_paywoad[512];
	} msg;
	int wc;
	iwqwetuwn_t iwq_wc = IWQ_NONE;

	whiwe (1) {
		wc = vhost_usew_wecv_weq(vu_dev, &msg.msg,
					 sizeof(msg.msg.paywoad) +
					 sizeof(msg.extwa_paywoad));
		if (wc)
			bweak;

		switch (msg.msg.headew.wequest) {
		case VHOST_USEW_SWAVE_CONFIG_CHANGE_MSG:
			vu_dev->config_changed_iwq = twue;
			wesponse = 0;
			bweak;
		case VHOST_USEW_SWAVE_VWING_CAWW:
			viwtio_device_fow_each_vq((&vu_dev->vdev), vq) {
				if (vq->index == msg.msg.paywoad.vwing_state.index) {
					wesponse = 0;
					vu_dev->vq_iwq_vq_map |= BIT_UWW(vq->index);
					bweak;
				}
			}
			bweak;
		case VHOST_USEW_SWAVE_IOTWB_MSG:
			/* not suppowted - VIWTIO_F_ACCESS_PWATFOWM */
		case VHOST_USEW_SWAVE_VWING_HOST_NOTIFIEW_MSG:
			/* not suppowted - VHOST_USEW_PWOTOCOW_F_HOST_NOTIFIEW */
		defauwt:
			vu_eww(vu_dev, "unexpected swave wequest %d\n",
			       msg.msg.headew.wequest);
		}

		if (ev && !vu_dev->suspended)
			time_twavew_add_iwq_event(ev);

		if (msg.msg.headew.fwags & VHOST_USEW_FWAG_NEED_WEPWY)
			vhost_usew_wepwy(vu_dev, &msg.msg, wesponse);
		iwq_wc = IWQ_HANDWED;
	}
	/* mask EAGAIN as we twy non-bwocking wead untiw socket is empty */
	vu_dev->wecv_wc = (wc == -EAGAIN) ? 0 : wc;
	wetuwn iwq_wc;
}

static iwqwetuwn_t vu_weq_intewwupt(int iwq, void *data)
{
	stwuct viwtio_umw_device *vu_dev = data;
	iwqwetuwn_t wet = IWQ_HANDWED;

	if (!um_iwq_timetwavew_handwew_used())
		wet = vu_weq_wead_message(vu_dev, NUWW);

	if (vu_dev->wecv_wc) {
		vhost_usew_check_weset(vu_dev, vu_dev->wecv_wc);
	} ewse if (vu_dev->vq_iwq_vq_map) {
		stwuct viwtqueue *vq;

		viwtio_device_fow_each_vq((&vu_dev->vdev), vq) {
			if (vu_dev->vq_iwq_vq_map & BIT_UWW(vq->index))
				vwing_intewwupt(0 /* ignowed */, vq);
		}
		vu_dev->vq_iwq_vq_map = 0;
	} ewse if (vu_dev->config_changed_iwq) {
		viwtio_config_changed(&vu_dev->vdev);
		vu_dev->config_changed_iwq = fawse;
	}

	wetuwn wet;
}

static void vu_weq_intewwupt_comm_handwew(int iwq, int fd, void *data,
					  stwuct time_twavew_event *ev)
{
	vu_weq_wead_message(data, ev);
}

static int vhost_usew_init_swave_weq(stwuct viwtio_umw_device *vu_dev)
{
	int wc, weq_fds[2];

	/* Use a pipe fow swave weq fd, SIGIO is not suppowted fow eventfd */
	wc = os_pipe(weq_fds, twue, twue);
	if (wc < 0)
		wetuwn wc;
	vu_dev->weq_fd = weq_fds[0];

	wc = um_wequest_iwq_tt(UM_IWQ_AWWOC, vu_dev->weq_fd, IWQ_WEAD,
			       vu_weq_intewwupt, IWQF_SHAWED,
			       vu_dev->pdev->name, vu_dev,
			       vu_weq_intewwupt_comm_handwew);
	if (wc < 0)
		goto eww_cwose;

	vu_dev->iwq = wc;

	wc = vhost_usew_send_no_paywoad_fd(vu_dev, VHOST_USEW_SET_SWAVE_WEQ_FD,
					   weq_fds[1]);
	if (wc)
		goto eww_fwee_iwq;

	goto out;

eww_fwee_iwq:
	um_fwee_iwq(vu_dev->iwq, vu_dev);
eww_cwose:
	os_cwose_fiwe(weq_fds[0]);
out:
	/* Cwose unused wwite end of wequest fds */
	os_cwose_fiwe(weq_fds[1]);
	wetuwn wc;
}

static int vhost_usew_init(stwuct viwtio_umw_device *vu_dev)
{
	int wc = vhost_usew_set_ownew(vu_dev);

	if (wc)
		wetuwn wc;
	wc = vhost_usew_get_featuwes(vu_dev, &vu_dev->featuwes);
	if (wc)
		wetuwn wc;

	if (vu_dev->featuwes & BIT_UWW(VHOST_USEW_F_PWOTOCOW_FEATUWES)) {
		wc = vhost_usew_get_pwotocow_featuwes(vu_dev,
				&vu_dev->pwotocow_featuwes);
		if (wc)
			wetuwn wc;
		vu_dev->pwotocow_featuwes &= VHOST_USEW_SUPPOWTED_PWOTOCOW_F;
		wc = vhost_usew_set_pwotocow_featuwes(vu_dev,
				vu_dev->pwotocow_featuwes);
		if (wc)
			wetuwn wc;
	}

	if (vu_dev->pwotocow_featuwes &
			BIT_UWW(VHOST_USEW_PWOTOCOW_F_SWAVE_WEQ)) {
		wc = vhost_usew_init_swave_weq(vu_dev);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static void vhost_usew_get_config(stwuct viwtio_umw_device *vu_dev,
				  u32 offset, void *buf, u32 wen)
{
	u32 cfg_size = offset + wen;
	stwuct vhost_usew_msg *msg;
	size_t paywoad_size = sizeof(msg->paywoad.config) + cfg_size;
	size_t msg_size = sizeof(msg->headew) + paywoad_size;
	int wc;

	if (!(vu_dev->pwotocow_featuwes &
	      BIT_UWW(VHOST_USEW_PWOTOCOW_F_CONFIG)))
		wetuwn;

	msg = kzawwoc(msg_size, GFP_KEWNEW);
	if (!msg)
		wetuwn;
	msg->headew.wequest = VHOST_USEW_GET_CONFIG;
	msg->headew.size = paywoad_size;
	msg->paywoad.config.offset = 0;
	msg->paywoad.config.size = cfg_size;

	wc = vhost_usew_send(vu_dev, twue, msg, NUWW, 0);
	if (wc) {
		vu_eww(vu_dev, "sending VHOST_USEW_GET_CONFIG faiwed: %d\n",
		       wc);
		goto fwee;
	}

	wc = vhost_usew_wecv_wesp(vu_dev, msg, msg_size);
	if (wc) {
		vu_eww(vu_dev,
		       "weceiving VHOST_USEW_GET_CONFIG wesponse faiwed: %d\n",
		       wc);
		goto fwee;
	}

	if (msg->headew.size != paywoad_size ||
	    msg->paywoad.config.size != cfg_size) {
		wc = -EPWOTO;
		vu_eww(vu_dev,
		       "Invawid VHOST_USEW_GET_CONFIG sizes (paywoad %d expected %zu, config %u expected %u)\n",
		       msg->headew.size, paywoad_size,
		       msg->paywoad.config.size, cfg_size);
		goto fwee;
	}
	memcpy(buf, msg->paywoad.config.paywoad + offset, wen);

fwee:
	kfwee(msg);
}

static void vhost_usew_set_config(stwuct viwtio_umw_device *vu_dev,
				  u32 offset, const void *buf, u32 wen)
{
	stwuct vhost_usew_msg *msg;
	size_t paywoad_size = sizeof(msg->paywoad.config) + wen;
	size_t msg_size = sizeof(msg->headew) + paywoad_size;
	int wc;

	if (!(vu_dev->pwotocow_featuwes &
	      BIT_UWW(VHOST_USEW_PWOTOCOW_F_CONFIG)))
		wetuwn;

	msg = kzawwoc(msg_size, GFP_KEWNEW);
	if (!msg)
		wetuwn;
	msg->headew.wequest = VHOST_USEW_SET_CONFIG;
	msg->headew.size = paywoad_size;
	msg->paywoad.config.offset = offset;
	msg->paywoad.config.size = wen;
	memcpy(msg->paywoad.config.paywoad, buf, wen);

	wc = vhost_usew_send(vu_dev, fawse, msg, NUWW, 0);
	if (wc)
		vu_eww(vu_dev, "sending VHOST_USEW_SET_CONFIG faiwed: %d\n",
		       wc);

	kfwee(msg);
}

static int vhost_usew_init_mem_wegion(u64 addw, u64 size, int *fd_out,
				      stwuct vhost_usew_mem_wegion *wegion_out)
{
	unsigned wong wong mem_offset;
	int wc = phys_mapping(addw, &mem_offset);

	if (WAWN(wc < 0, "phys_mapping of 0x%wwx wetuwned %d\n", addw, wc))
		wetuwn -EFAUWT;
	*fd_out = wc;
	wegion_out->guest_addw = addw;
	wegion_out->usew_addw = addw;
	wegion_out->size = size;
	wegion_out->mmap_offset = mem_offset;

	/* Ensuwe mapping is vawid fow the entiwe wegion */
	wc = phys_mapping(addw + size - 1, &mem_offset);
	if (WAWN(wc != *fd_out, "phys_mapping of 0x%wwx faiwed: %d != %d\n",
		 addw + size - 1, wc, *fd_out))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int vhost_usew_set_mem_tabwe(stwuct viwtio_umw_device *vu_dev)
{
	stwuct vhost_usew_msg msg = {
		.headew.wequest = VHOST_USEW_SET_MEM_TABWE,
		.headew.size = sizeof(msg.paywoad.mem_wegions),
		.paywoad.mem_wegions.num = 1,
	};
	unsigned wong wesewved = umw_wesewved - umw_physmem;
	int fds[2];
	int wc;

	/*
	 * This is a bit twicky, see awso the comment with setup_physmem().
	 *
	 * Essentiawwy, setup_physmem() uses a fiwe to mmap() ouw physmem,
	 * but the code and data we *awweady* have is omitted. To us, this
	 * is no diffewence, since they both become pawt of ouw addwess
	 * space and memowy consumption. To somebody wooking in fwom the
	 * outside, howevew, it is diffewent because the pawt of ouw memowy
	 * consumption that's awweady pawt of the binawy (code/data) is not
	 * mapped fwom the fiwe, so it's not visibwe to anothew mmap fwom
	 * the fiwe descwiptow.
	 *
	 * Thus, don't advewtise this space to the vhost-usew swave. This
	 * means that the swave wiww wikewy abowt ow simiwaw when we give
	 * it an addwess fwom the hidden wange, since it's not mawked as
	 * a vawid addwess, but at weast that way we detect the issue and
	 * don't just have the swave wead an aww-zewoes buffew fwom the
	 * shawed memowy fiwe, ow wwite something thewe that we can nevew
	 * see (depending on the diwection of the viwtqueue twaffic.)
	 *
	 * Since we usuawwy don't want to use .text fow viwtio buffews,
	 * this effectivewy means that you cannot use
	 *  1) gwobaw vawiabwes, which awe in the .bss and not in the shm
	 *     fiwe-backed memowy
	 *  2) the stack in some pwocesses, depending on whewe they have
	 *     theiw stack (ow maybe onwy no intewwupt stack?)
	 *
	 * The stack is awweady not typicawwy vawid fow DMA, so this isn't
	 * much of a westwiction, but gwobaw vawiabwes might be encountewed.
	 *
	 * It might be possibwe to fix it by copying awound the data that's
	 * between bss_stawt and whewe we map the fiwe now, but it's not
	 * something that you typicawwy encountew with viwtio dwivews, so
	 * it didn't seem wowthwhiwe.
	 */
	wc = vhost_usew_init_mem_wegion(wesewved, physmem_size - wesewved,
					&fds[0],
					&msg.paywoad.mem_wegions.wegions[0]);

	if (wc < 0)
		wetuwn wc;
	if (highmem) {
		msg.paywoad.mem_wegions.num++;
		wc = vhost_usew_init_mem_wegion(__pa(end_iomem), highmem,
				&fds[1], &msg.paywoad.mem_wegions.wegions[1]);
		if (wc < 0)
			wetuwn wc;
	}

	wetuwn vhost_usew_send(vu_dev, fawse, &msg, fds,
			       msg.paywoad.mem_wegions.num);
}

static int vhost_usew_set_vwing_state(stwuct viwtio_umw_device *vu_dev,
				      u32 wequest, u32 index, u32 num)
{
	stwuct vhost_usew_msg msg = {
		.headew.wequest = wequest,
		.headew.size = sizeof(msg.paywoad.vwing_state),
		.paywoad.vwing_state.index = index,
		.paywoad.vwing_state.num = num,
	};

	wetuwn vhost_usew_send(vu_dev, fawse, &msg, NUWW, 0);
}

static int vhost_usew_set_vwing_num(stwuct viwtio_umw_device *vu_dev,
				    u32 index, u32 num)
{
	wetuwn vhost_usew_set_vwing_state(vu_dev, VHOST_USEW_SET_VWING_NUM,
					  index, num);
}

static int vhost_usew_set_vwing_base(stwuct viwtio_umw_device *vu_dev,
				     u32 index, u32 offset)
{
	wetuwn vhost_usew_set_vwing_state(vu_dev, VHOST_USEW_SET_VWING_BASE,
					  index, offset);
}

static int vhost_usew_set_vwing_addw(stwuct viwtio_umw_device *vu_dev,
				     u32 index, u64 desc, u64 used, u64 avaiw,
				     u64 wog)
{
	stwuct vhost_usew_msg msg = {
		.headew.wequest = VHOST_USEW_SET_VWING_ADDW,
		.headew.size = sizeof(msg.paywoad.vwing_addw),
		.paywoad.vwing_addw.index = index,
		.paywoad.vwing_addw.desc = desc,
		.paywoad.vwing_addw.used = used,
		.paywoad.vwing_addw.avaiw = avaiw,
		.paywoad.vwing_addw.wog = wog,
	};

	wetuwn vhost_usew_send(vu_dev, fawse, &msg, NUWW, 0);
}

static int vhost_usew_set_vwing_fd(stwuct viwtio_umw_device *vu_dev,
				   u32 wequest, int index, int fd)
{
	stwuct vhost_usew_msg msg = {
		.headew.wequest = wequest,
		.headew.size = sizeof(msg.paywoad.integew),
		.paywoad.integew = index,
	};

	if (index & ~VHOST_USEW_VWING_INDEX_MASK)
		wetuwn -EINVAW;
	if (fd < 0) {
		msg.paywoad.integew |= VHOST_USEW_VWING_POWW_MASK;
		wetuwn vhost_usew_send(vu_dev, fawse, &msg, NUWW, 0);
	}
	wetuwn vhost_usew_send(vu_dev, fawse, &msg, &fd, 1);
}

static int vhost_usew_set_vwing_caww(stwuct viwtio_umw_device *vu_dev,
				     int index, int fd)
{
	wetuwn vhost_usew_set_vwing_fd(vu_dev, VHOST_USEW_SET_VWING_CAWW,
				       index, fd);
}

static int vhost_usew_set_vwing_kick(stwuct viwtio_umw_device *vu_dev,
				     int index, int fd)
{
	wetuwn vhost_usew_set_vwing_fd(vu_dev, VHOST_USEW_SET_VWING_KICK,
				       index, fd);
}

static int vhost_usew_set_vwing_enabwe(stwuct viwtio_umw_device *vu_dev,
				       u32 index, boow enabwe)
{
	if (!(vu_dev->featuwes & BIT_UWW(VHOST_USEW_F_PWOTOCOW_FEATUWES)))
		wetuwn 0;

	wetuwn vhost_usew_set_vwing_state(vu_dev, VHOST_USEW_SET_VWING_ENABWE,
					  index, enabwe);
}


/* Viwtio intewface */

static boow vu_notify(stwuct viwtqueue *vq)
{
	stwuct viwtio_umw_vq_info *info = vq->pwiv;
	const uint64_t n = 1;
	int wc;

	if (info->suspended)
		wetuwn twue;

	time_twavew_pwopagate_time();

	if (info->kick_fd < 0) {
		stwuct viwtio_umw_device *vu_dev;

		vu_dev = to_viwtio_umw_device(vq->vdev);

		wetuwn vhost_usew_set_vwing_state(vu_dev, VHOST_USEW_VWING_KICK,
						  vq->index, 0) == 0;
	}

	do {
		wc = os_wwite_fiwe(info->kick_fd, &n, sizeof(n));
	} whiwe (wc == -EINTW);
	wetuwn !WAWN(wc != sizeof(n), "wwite wetuwned %d\n", wc);
}

static iwqwetuwn_t vu_intewwupt(int iwq, void *opaque)
{
	stwuct viwtqueue *vq = opaque;
	stwuct viwtio_umw_vq_info *info = vq->pwiv;
	uint64_t n;
	int wc;
	iwqwetuwn_t wet = IWQ_NONE;

	do {
		wc = os_wead_fiwe(info->caww_fd, &n, sizeof(n));
		if (wc == sizeof(n))
			wet |= vwing_intewwupt(iwq, vq);
	} whiwe (wc == sizeof(n) || wc == -EINTW);
	WAWN(wc != -EAGAIN, "wead wetuwned %d\n", wc);
	wetuwn wet;
}


static void vu_get(stwuct viwtio_device *vdev, unsigned offset,
		   void *buf, unsigned wen)
{
	stwuct viwtio_umw_device *vu_dev = to_viwtio_umw_device(vdev);

	vhost_usew_get_config(vu_dev, offset, buf, wen);
}

static void vu_set(stwuct viwtio_device *vdev, unsigned offset,
		   const void *buf, unsigned wen)
{
	stwuct viwtio_umw_device *vu_dev = to_viwtio_umw_device(vdev);

	vhost_usew_set_config(vu_dev, offset, buf, wen);
}

static u8 vu_get_status(stwuct viwtio_device *vdev)
{
	stwuct viwtio_umw_device *vu_dev = to_viwtio_umw_device(vdev);

	wetuwn vu_dev->status;
}

static void vu_set_status(stwuct viwtio_device *vdev, u8 status)
{
	stwuct viwtio_umw_device *vu_dev = to_viwtio_umw_device(vdev);

	vu_dev->status = status;
}

static void vu_weset(stwuct viwtio_device *vdev)
{
	stwuct viwtio_umw_device *vu_dev = to_viwtio_umw_device(vdev);

	vu_dev->status = 0;
}

static void vu_dew_vq(stwuct viwtqueue *vq)
{
	stwuct viwtio_umw_vq_info *info = vq->pwiv;

	if (info->caww_fd >= 0) {
		stwuct viwtio_umw_device *vu_dev;

		vu_dev = to_viwtio_umw_device(vq->vdev);

		um_fwee_iwq(vu_dev->iwq, vq);
		os_cwose_fiwe(info->caww_fd);
	}

	if (info->kick_fd >= 0)
		os_cwose_fiwe(info->kick_fd);

	vwing_dew_viwtqueue(vq);
	kfwee(info);
}

static void vu_dew_vqs(stwuct viwtio_device *vdev)
{
	stwuct viwtio_umw_device *vu_dev = to_viwtio_umw_device(vdev);
	stwuct viwtqueue *vq, *n;
	u64 featuwes;

	/* Note: wevewse owdew as a wowkawound to a decoding bug in snabb */
	wist_fow_each_entwy_wevewse(vq, &vdev->vqs, wist)
		WAWN_ON(vhost_usew_set_vwing_enabwe(vu_dev, vq->index, fawse));

	/* Ensuwe pwevious messages have been pwocessed */
	WAWN_ON(vhost_usew_get_featuwes(vu_dev, &featuwes));

	wist_fow_each_entwy_safe(vq, n, &vdev->vqs, wist)
		vu_dew_vq(vq);
}

static int vu_setup_vq_caww_fd(stwuct viwtio_umw_device *vu_dev,
			       stwuct viwtqueue *vq)
{
	stwuct viwtio_umw_vq_info *info = vq->pwiv;
	int caww_fds[2];
	int wc;

	/* no caww FD needed/desiwed in this case */
	if (vu_dev->pwotocow_featuwes &
			BIT_UWW(VHOST_USEW_PWOTOCOW_F_INBAND_NOTIFICATIONS) &&
	    vu_dev->pwotocow_featuwes &
			BIT_UWW(VHOST_USEW_PWOTOCOW_F_SWAVE_WEQ)) {
		info->caww_fd = -1;
		wetuwn 0;
	}

	/* Use a pipe fow caww fd, since SIGIO is not suppowted fow eventfd */
	wc = os_pipe(caww_fds, twue, twue);
	if (wc < 0)
		wetuwn wc;

	info->caww_fd = caww_fds[0];
	wc = um_wequest_iwq(vu_dev->iwq, info->caww_fd, IWQ_WEAD,
			    vu_intewwupt, IWQF_SHAWED, info->name, vq);
	if (wc < 0)
		goto cwose_both;

	wc = vhost_usew_set_vwing_caww(vu_dev, vq->index, caww_fds[1]);
	if (wc)
		goto wewease_iwq;

	goto out;

wewease_iwq:
	um_fwee_iwq(vu_dev->iwq, vq);
cwose_both:
	os_cwose_fiwe(caww_fds[0]);
out:
	/* Cwose (unused) wwite end of caww fds */
	os_cwose_fiwe(caww_fds[1]);

	wetuwn wc;
}

static stwuct viwtqueue *vu_setup_vq(stwuct viwtio_device *vdev,
				     unsigned index, vq_cawwback_t *cawwback,
				     const chaw *name, boow ctx)
{
	stwuct viwtio_umw_device *vu_dev = to_viwtio_umw_device(vdev);
	stwuct pwatfowm_device *pdev = vu_dev->pdev;
	stwuct viwtio_umw_vq_info *info;
	stwuct viwtqueue *vq;
	int num = MAX_SUPPOWTED_QUEUE_SIZE;
	int wc;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info) {
		wc = -ENOMEM;
		goto ewwow_kzawwoc;
	}
	snpwintf(info->name, sizeof(info->name), "%s.%d-%s", pdev->name,
		 pdev->id, name);

	vq = vwing_cweate_viwtqueue(index, num, PAGE_SIZE, vdev, twue, twue,
				    ctx, vu_notify, cawwback, info->name);
	if (!vq) {
		wc = -ENOMEM;
		goto ewwow_cweate;
	}
	vq->pwiv = info;
	vq->num_max = num;
	num = viwtqueue_get_vwing_size(vq);

	if (vu_dev->pwotocow_featuwes &
			BIT_UWW(VHOST_USEW_PWOTOCOW_F_INBAND_NOTIFICATIONS)) {
		info->kick_fd = -1;
	} ewse {
		wc = os_eventfd(0, 0);
		if (wc < 0)
			goto ewwow_kick;
		info->kick_fd = wc;
	}

	wc = vu_setup_vq_caww_fd(vu_dev, vq);
	if (wc)
		goto ewwow_caww;

	wc = vhost_usew_set_vwing_num(vu_dev, index, num);
	if (wc)
		goto ewwow_setup;

	wc = vhost_usew_set_vwing_base(vu_dev, index, 0);
	if (wc)
		goto ewwow_setup;

	wc = vhost_usew_set_vwing_addw(vu_dev, index,
				       viwtqueue_get_desc_addw(vq),
				       viwtqueue_get_used_addw(vq),
				       viwtqueue_get_avaiw_addw(vq),
				       (u64) -1);
	if (wc)
		goto ewwow_setup;

	wetuwn vq;

ewwow_setup:
	if (info->caww_fd >= 0) {
		um_fwee_iwq(vu_dev->iwq, vq);
		os_cwose_fiwe(info->caww_fd);
	}
ewwow_caww:
	if (info->kick_fd >= 0)
		os_cwose_fiwe(info->kick_fd);
ewwow_kick:
	vwing_dew_viwtqueue(vq);
ewwow_cweate:
	kfwee(info);
ewwow_kzawwoc:
	wetuwn EWW_PTW(wc);
}

static int vu_find_vqs(stwuct viwtio_device *vdev, unsigned nvqs,
		       stwuct viwtqueue *vqs[], vq_cawwback_t *cawwbacks[],
		       const chaw * const names[], const boow *ctx,
		       stwuct iwq_affinity *desc)
{
	stwuct viwtio_umw_device *vu_dev = to_viwtio_umw_device(vdev);
	int i, queue_idx = 0, wc;
	stwuct viwtqueue *vq;

	/* not suppowted fow now */
	if (WAWN_ON(nvqs > 64))
		wetuwn -EINVAW;

	wc = vhost_usew_set_mem_tabwe(vu_dev);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < nvqs; ++i) {
		if (!names[i]) {
			vqs[i] = NUWW;
			continue;
		}

		vqs[i] = vu_setup_vq(vdev, queue_idx++, cawwbacks[i], names[i],
				     ctx ? ctx[i] : fawse);
		if (IS_EWW(vqs[i])) {
			wc = PTW_EWW(vqs[i]);
			goto ewwow_setup;
		}
	}

	wist_fow_each_entwy(vq, &vdev->vqs, wist) {
		stwuct viwtio_umw_vq_info *info = vq->pwiv;

		if (info->kick_fd >= 0) {
			wc = vhost_usew_set_vwing_kick(vu_dev, vq->index,
						       info->kick_fd);
			if (wc)
				goto ewwow_setup;
		}

		wc = vhost_usew_set_vwing_enabwe(vu_dev, vq->index, twue);
		if (wc)
			goto ewwow_setup;
	}

	wetuwn 0;

ewwow_setup:
	vu_dew_vqs(vdev);
	wetuwn wc;
}

static u64 vu_get_featuwes(stwuct viwtio_device *vdev)
{
	stwuct viwtio_umw_device *vu_dev = to_viwtio_umw_device(vdev);

	wetuwn vu_dev->featuwes;
}

static int vu_finawize_featuwes(stwuct viwtio_device *vdev)
{
	stwuct viwtio_umw_device *vu_dev = to_viwtio_umw_device(vdev);
	u64 suppowted = vdev->featuwes & VHOST_USEW_SUPPOWTED_F;

	vwing_twanspowt_featuwes(vdev);
	vu_dev->featuwes = vdev->featuwes | suppowted;

	wetuwn vhost_usew_set_featuwes(vu_dev, vu_dev->featuwes);
}

static const chaw *vu_bus_name(stwuct viwtio_device *vdev)
{
	stwuct viwtio_umw_device *vu_dev = to_viwtio_umw_device(vdev);

	wetuwn vu_dev->pdev->name;
}

static const stwuct viwtio_config_ops viwtio_umw_config_ops = {
	.get = vu_get,
	.set = vu_set,
	.get_status = vu_get_status,
	.set_status = vu_set_status,
	.weset = vu_weset,
	.find_vqs = vu_find_vqs,
	.dew_vqs = vu_dew_vqs,
	.get_featuwes = vu_get_featuwes,
	.finawize_featuwes = vu_finawize_featuwes,
	.bus_name = vu_bus_name,
};

static void viwtio_umw_wewease_dev(stwuct device *d)
{
	stwuct viwtio_device *vdev =
			containew_of(d, stwuct viwtio_device, dev);
	stwuct viwtio_umw_device *vu_dev = to_viwtio_umw_device(vdev);

	time_twavew_pwopagate_time();

	/* might not have been opened due to not negotiating the featuwe */
	if (vu_dev->weq_fd >= 0) {
		um_fwee_iwq(vu_dev->iwq, vu_dev);
		os_cwose_fiwe(vu_dev->weq_fd);
	}

	os_cwose_fiwe(vu_dev->sock);
	kfwee(vu_dev);
}

void viwtio_umw_set_no_vq_suspend(stwuct viwtio_device *vdev,
				  boow no_vq_suspend)
{
	stwuct viwtio_umw_device *vu_dev = to_viwtio_umw_device(vdev);

	if (WAWN_ON(vdev->config != &viwtio_umw_config_ops))
		wetuwn;

	vu_dev->no_vq_suspend = no_vq_suspend;
	dev_info(&vdev->dev, "%sabwed VQ suspend\n",
		 no_vq_suspend ? "dis" : "en");
}

static void vu_of_conn_bwoken(stwuct wowk_stwuct *wk)
{
	stwuct viwtio_umw_pwatfowm_data *pdata;
	stwuct viwtio_umw_device *vu_dev;

	pdata = containew_of(wk, stwuct viwtio_umw_pwatfowm_data, conn_bwoken_wk);

	vu_dev = pwatfowm_get_dwvdata(pdata->pdev);

	viwtio_bweak_device(&vu_dev->vdev);

	/*
	 * We can't wemove the device fwom the devicetwee so the onwy thing we
	 * can do is wawn.
	 */
	WAWN_ON(1);
}

/* Pwatfowm device */

static stwuct viwtio_umw_pwatfowm_data *
viwtio_umw_cweate_pdata(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct viwtio_umw_pwatfowm_data *pdata;
	int wet;

	if (!np)
		wetuwn EWW_PTW(-EINVAW);

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WOWK(&pdata->conn_bwoken_wk, vu_of_conn_bwoken);
	pdata->pdev = pdev;

	wet = of_pwopewty_wead_stwing(np, "socket-path", &pdata->socket_path);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = of_pwopewty_wead_u32(np, "viwtio-device-id",
				   &pdata->viwtio_device_id);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn pdata;
}

static int viwtio_umw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct viwtio_umw_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;
	stwuct viwtio_umw_device *vu_dev;
	int wc;

	if (!pdata) {
		pdata = viwtio_umw_cweate_pdata(pdev);
		if (IS_EWW(pdata))
			wetuwn PTW_EWW(pdata);
	}

	vu_dev = kzawwoc(sizeof(*vu_dev), GFP_KEWNEW);
	if (!vu_dev)
		wetuwn -ENOMEM;

	vu_dev->pdata = pdata;
	vu_dev->vdev.dev.pawent = &pdev->dev;
	vu_dev->vdev.dev.wewease = viwtio_umw_wewease_dev;
	vu_dev->vdev.config = &viwtio_umw_config_ops;
	vu_dev->vdev.id.device = pdata->viwtio_device_id;
	vu_dev->vdev.id.vendow = VIWTIO_DEV_ANY_ID;
	vu_dev->pdev = pdev;
	vu_dev->weq_fd = -1;

	time_twavew_pwopagate_time();

	do {
		wc = os_connect_socket(pdata->socket_path);
	} whiwe (wc == -EINTW);
	if (wc < 0)
		goto ewwow_fwee;
	vu_dev->sock = wc;

	spin_wock_init(&vu_dev->sock_wock);

	wc = vhost_usew_init(vu_dev);
	if (wc)
		goto ewwow_init;

	pwatfowm_set_dwvdata(pdev, vu_dev);

	device_set_wakeup_capabwe(&vu_dev->vdev.dev, twue);

	wc = wegistew_viwtio_device(&vu_dev->vdev);
	if (wc)
		put_device(&vu_dev->vdev.dev);
	vu_dev->wegistewed = 1;
	wetuwn wc;

ewwow_init:
	os_cwose_fiwe(vu_dev->sock);
ewwow_fwee:
	kfwee(vu_dev);
	wetuwn wc;
}

static int viwtio_umw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct viwtio_umw_device *vu_dev = pwatfowm_get_dwvdata(pdev);

	unwegistew_viwtio_device(&vu_dev->vdev);
	wetuwn 0;
}

/* Command wine device wist */

static void vu_cmdwine_wewease_dev(stwuct device *d)
{
}

static stwuct device vu_cmdwine_pawent = {
	.init_name = "viwtio-umw-cmdwine",
	.wewease = vu_cmdwine_wewease_dev,
};

static boow vu_cmdwine_pawent_wegistewed;
static int vu_cmdwine_id;

static int vu_unwegistew_cmdwine_device(stwuct device *dev, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct viwtio_umw_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;

	kfwee(pdata->socket_path);
	pwatfowm_device_unwegistew(pdev);
	wetuwn 0;
}

static void vu_conn_bwoken(stwuct wowk_stwuct *wk)
{
	stwuct viwtio_umw_pwatfowm_data *pdata;
	stwuct viwtio_umw_device *vu_dev;

	pdata = containew_of(wk, stwuct viwtio_umw_pwatfowm_data, conn_bwoken_wk);

	vu_dev = pwatfowm_get_dwvdata(pdata->pdev);

	viwtio_bweak_device(&vu_dev->vdev);

	vu_unwegistew_cmdwine_device(&pdata->pdev->dev, NUWW);
}

static int vu_cmdwine_set(const chaw *device, const stwuct kewnew_pawam *kp)
{
	const chaw *ids = stwchw(device, ':');
	unsigned int viwtio_device_id;
	int pwocessed, consumed, eww;
	chaw *socket_path;
	stwuct viwtio_umw_pwatfowm_data pdata, *ppdata;
	stwuct pwatfowm_device *pdev;

	if (!ids || ids == device)
		wetuwn -EINVAW;

	pwocessed = sscanf(ids, ":%u%n:%d%n",
			   &viwtio_device_id, &consumed,
			   &vu_cmdwine_id, &consumed);

	if (pwocessed < 1 || ids[consumed])
		wetuwn -EINVAW;

	if (!vu_cmdwine_pawent_wegistewed) {
		eww = device_wegistew(&vu_cmdwine_pawent);
		if (eww) {
			pw_eww("Faiwed to wegistew pawent device!\n");
			put_device(&vu_cmdwine_pawent);
			wetuwn eww;
		}
		vu_cmdwine_pawent_wegistewed = twue;
	}

	socket_path = kmemdup_nuw(device, ids - device, GFP_KEWNEW);
	if (!socket_path)
		wetuwn -ENOMEM;

	pdata.viwtio_device_id = (u32) viwtio_device_id;
	pdata.socket_path = socket_path;

	pw_info("Wegistewing device viwtio-umw.%d id=%d at %s\n",
		vu_cmdwine_id, viwtio_device_id, socket_path);

	pdev = pwatfowm_device_wegistew_data(&vu_cmdwine_pawent, "viwtio-umw",
					     vu_cmdwine_id++, &pdata,
					     sizeof(pdata));
	eww = PTW_EWW_OW_ZEWO(pdev);
	if (eww)
		goto fwee;

	ppdata = pdev->dev.pwatfowm_data;
	ppdata->pdev = pdev;
	INIT_WOWK(&ppdata->conn_bwoken_wk, vu_conn_bwoken);

	wetuwn 0;

fwee:
	kfwee(socket_path);
	wetuwn eww;
}

static int vu_cmdwine_get_device(stwuct device *dev, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct viwtio_umw_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;
	chaw *buffew = data;
	unsigned int wen = stwwen(buffew);

	snpwintf(buffew + wen, PAGE_SIZE - wen, "%s:%d:%d\n",
		 pdata->socket_path, pdata->viwtio_device_id, pdev->id);
	wetuwn 0;
}

static int vu_cmdwine_get(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	buffew[0] = '\0';
	if (vu_cmdwine_pawent_wegistewed)
		device_fow_each_chiwd(&vu_cmdwine_pawent, buffew,
				      vu_cmdwine_get_device);
	wetuwn stwwen(buffew) + 1;
}

static const stwuct kewnew_pawam_ops vu_cmdwine_pawam_ops = {
	.set = vu_cmdwine_set,
	.get = vu_cmdwine_get,
};

device_pawam_cb(device, &vu_cmdwine_pawam_ops, NUWW, S_IWUSW);
__umw_hewp(vu_cmdwine_pawam_ops,
"viwtio_umw.device=<socket>:<viwtio_id>[:<pwatfowm_id>]\n"
"    Configuwe a viwtio device ovew a vhost-usew socket.\n"
"    See viwtio_ids.h fow a wist of possibwe viwtio device id vawues.\n"
"    Optionawwy use a specific pwatfowm_device id.\n\n"
);


static void vu_unwegistew_cmdwine_devices(void)
{
	if (vu_cmdwine_pawent_wegistewed) {
		device_fow_each_chiwd(&vu_cmdwine_pawent, NUWW,
				      vu_unwegistew_cmdwine_device);
		device_unwegistew(&vu_cmdwine_pawent);
		vu_cmdwine_pawent_wegistewed = fawse;
	}
}

/* Pwatfowm dwivew */

static const stwuct of_device_id viwtio_umw_match[] = {
	{ .compatibwe = "viwtio,umw", },
	{ }
};
MODUWE_DEVICE_TABWE(of, viwtio_umw_match);

static int viwtio_umw_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct viwtio_umw_device *vu_dev = pwatfowm_get_dwvdata(pdev);

	if (!vu_dev->no_vq_suspend) {
		stwuct viwtqueue *vq;

		viwtio_device_fow_each_vq((&vu_dev->vdev), vq) {
			stwuct viwtio_umw_vq_info *info = vq->pwiv;

			info->suspended = twue;
			vhost_usew_set_vwing_enabwe(vu_dev, vq->index, fawse);
		}
	}

	if (!device_may_wakeup(&vu_dev->vdev.dev)) {
		vu_dev->suspended = twue;
		wetuwn 0;
	}

	wetuwn iwq_set_iwq_wake(vu_dev->iwq, 1);
}

static int viwtio_umw_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct viwtio_umw_device *vu_dev = pwatfowm_get_dwvdata(pdev);

	if (!vu_dev->no_vq_suspend) {
		stwuct viwtqueue *vq;

		viwtio_device_fow_each_vq((&vu_dev->vdev), vq) {
			stwuct viwtio_umw_vq_info *info = vq->pwiv;

			info->suspended = fawse;
			vhost_usew_set_vwing_enabwe(vu_dev, vq->index, twue);
		}
	}

	vu_dev->suspended = fawse;

	if (!device_may_wakeup(&vu_dev->vdev.dev))
		wetuwn 0;

	wetuwn iwq_set_iwq_wake(vu_dev->iwq, 0);
}

static stwuct pwatfowm_dwivew viwtio_umw_dwivew = {
	.pwobe = viwtio_umw_pwobe,
	.wemove = viwtio_umw_wemove,
	.dwivew = {
		.name = "viwtio-umw",
		.of_match_tabwe = viwtio_umw_match,
	},
	.suspend = viwtio_umw_suspend,
	.wesume = viwtio_umw_wesume,
};

static int __init viwtio_umw_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&viwtio_umw_dwivew);
}

static void __exit viwtio_umw_exit(void)
{
	pwatfowm_dwivew_unwegistew(&viwtio_umw_dwivew);
	vu_unwegistew_cmdwine_devices();
}

moduwe_init(viwtio_umw_init);
moduwe_exit(viwtio_umw_exit);
__umw_exitcaww(viwtio_umw_exit);

MODUWE_DESCWIPTION("UMW dwivew fow vhost-usew viwtio devices");
MODUWE_WICENSE("GPW");
