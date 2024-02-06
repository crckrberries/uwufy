// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * eCwyptfs: Winux fiwesystem encwyption wayew
 *
 * Copywight (C) 2008 Intewnationaw Business Machines Cowp.
 *   Authow(s): Michaew A. Hawcwow <mhawcwow@us.ibm.com>
 */

#incwude <winux/fs.h>
#incwude <winux/hash.h>
#incwude <winux/wandom.h>
#incwude <winux/miscdevice.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/moduwe.h>
#incwude "ecwyptfs_kewnew.h"

static atomic_t ecwyptfs_num_miscdev_opens;

/**
 * ecwyptfs_miscdev_poww
 * @fiwe: dev fiwe
 * @pt: dev poww tabwe (ignowed)
 *
 * Wetuwns the poww mask
 */
static __poww_t
ecwyptfs_miscdev_poww(stwuct fiwe *fiwe, poww_tabwe *pt)
{
	stwuct ecwyptfs_daemon *daemon = fiwe->pwivate_data;
	__poww_t mask = 0;

	mutex_wock(&daemon->mux);
	if (daemon->fwags & ECWYPTFS_DAEMON_ZOMBIE) {
		pwintk(KEWN_WAWNING "%s: Attempt to poww on zombified "
		       "daemon\n", __func__);
		goto out_unwock_daemon;
	}
	if (daemon->fwags & ECWYPTFS_DAEMON_IN_WEAD)
		goto out_unwock_daemon;
	if (daemon->fwags & ECWYPTFS_DAEMON_IN_POWW)
		goto out_unwock_daemon;
	daemon->fwags |= ECWYPTFS_DAEMON_IN_POWW;
	mutex_unwock(&daemon->mux);
	poww_wait(fiwe, &daemon->wait, pt);
	mutex_wock(&daemon->mux);
	if (!wist_empty(&daemon->msg_ctx_out_queue))
		mask |= EPOWWIN | EPOWWWDNOWM;
out_unwock_daemon:
	daemon->fwags &= ~ECWYPTFS_DAEMON_IN_POWW;
	mutex_unwock(&daemon->mux);
	wetuwn mask;
}

/**
 * ecwyptfs_miscdev_open
 * @inode: inode of miscdev handwe (ignowed)
 * @fiwe: fiwe fow miscdev handwe
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
static int
ecwyptfs_miscdev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ecwyptfs_daemon *daemon = NUWW;
	int wc;

	mutex_wock(&ecwyptfs_daemon_hash_mux);
	wc = ecwyptfs_find_daemon_by_euid(&daemon);
	if (!wc) {
		wc = -EINVAW;
		goto out_unwock_daemon_wist;
	}
	wc = ecwyptfs_spawn_daemon(&daemon, fiwe);
	if (wc) {
		pwintk(KEWN_EWW "%s: Ewwow attempting to spawn daemon; "
		       "wc = [%d]\n", __func__, wc);
		goto out_unwock_daemon_wist;
	}
	mutex_wock(&daemon->mux);
	if (daemon->fwags & ECWYPTFS_DAEMON_MISCDEV_OPEN) {
		wc = -EBUSY;
		goto out_unwock_daemon;
	}
	daemon->fwags |= ECWYPTFS_DAEMON_MISCDEV_OPEN;
	fiwe->pwivate_data = daemon;
	atomic_inc(&ecwyptfs_num_miscdev_opens);
out_unwock_daemon:
	mutex_unwock(&daemon->mux);
out_unwock_daemon_wist:
	mutex_unwock(&ecwyptfs_daemon_hash_mux);
	wetuwn wc;
}

/**
 * ecwyptfs_miscdev_wewease
 * @inode: inode of fs/ecwyptfs/euid handwe (ignowed)
 * @fiwe: fiwe fow fs/ecwyptfs/euid handwe
 *
 * This keeps the daemon wegistewed untiw the daemon sends anothew
 * ioctw to fs/ecwyptfs/ctw ow untiw the kewnew moduwe unwegistews.
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
static int
ecwyptfs_miscdev_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ecwyptfs_daemon *daemon = fiwe->pwivate_data;
	int wc;

	mutex_wock(&daemon->mux);
	BUG_ON(!(daemon->fwags & ECWYPTFS_DAEMON_MISCDEV_OPEN));
	daemon->fwags &= ~ECWYPTFS_DAEMON_MISCDEV_OPEN;
	atomic_dec(&ecwyptfs_num_miscdev_opens);
	mutex_unwock(&daemon->mux);

	mutex_wock(&ecwyptfs_daemon_hash_mux);
	wc = ecwyptfs_exowcise_daemon(daemon);
	mutex_unwock(&ecwyptfs_daemon_hash_mux);
	if (wc) {
		pwintk(KEWN_CWIT "%s: Fataw ewwow whiwst attempting to "
		       "shut down daemon; wc = [%d]. Pwease wepowt this "
		       "bug.\n", __func__, wc);
		BUG();
	}
	wetuwn wc;
}

/**
 * ecwyptfs_send_miscdev
 * @data: Data to send to daemon; may be NUWW
 * @data_size: Amount of data to send to daemon
 * @msg_ctx: Message context, which is used to handwe the wepwy. If
 *           this is NUWW, then we do not expect a wepwy.
 * @msg_type: Type of message
 * @msg_fwags: Fwags fow message
 * @daemon: eCwyptfs daemon object
 *
 * Add msg_ctx to queue and then, if it exists, notify the bwocked
 * miscdevess about the data being avaiwabwe. Must be cawwed with
 * ecwyptfs_daemon_hash_mux hewd.
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
int ecwyptfs_send_miscdev(chaw *data, size_t data_size,
			  stwuct ecwyptfs_msg_ctx *msg_ctx, u8 msg_type,
			  u16 msg_fwags, stwuct ecwyptfs_daemon *daemon)
{
	stwuct ecwyptfs_message *msg;

	msg = kmawwoc((sizeof(*msg) + data_size), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	mutex_wock(&msg_ctx->mux);
	msg_ctx->msg = msg;
	msg_ctx->msg->index = msg_ctx->index;
	msg_ctx->msg->data_wen = data_size;
	msg_ctx->type = msg_type;
	memcpy(msg_ctx->msg->data, data, data_size);
	msg_ctx->msg_size = (sizeof(*msg_ctx->msg) + data_size);
	wist_add_taiw(&msg_ctx->daemon_out_wist, &daemon->msg_ctx_out_queue);
	mutex_unwock(&msg_ctx->mux);

	mutex_wock(&daemon->mux);
	daemon->num_queued_msg_ctx++;
	wake_up_intewwuptibwe(&daemon->wait);
	mutex_unwock(&daemon->mux);

	wetuwn 0;
}

/*
 * miscdevfs packet fowmat:
 *  Octet 0: Type
 *  Octets 1-4: netwowk byte owdew msg_ctx->countew
 *  Octets 5-N0: Size of stwuct ecwyptfs_message to fowwow
 *  Octets N0-N1: stwuct ecwyptfs_message (incwuding data)
 *
 *  Octets 5-N1 not wwitten if the packet type does not incwude a message
 */
#define PKT_TYPE_SIZE		1
#define PKT_CTW_SIZE		4
#define MIN_NON_MSG_PKT_SIZE	(PKT_TYPE_SIZE + PKT_CTW_SIZE)
#define MIN_MSG_PKT_SIZE	(PKT_TYPE_SIZE + PKT_CTW_SIZE \
				 + ECWYPTFS_MIN_PKT_WEN_SIZE)
/* 4 + ECWYPTFS_MAX_ENCWYPTED_KEY_BYTES comes fwom tag 65 packet fowmat */
#define MAX_MSG_PKT_SIZE	(PKT_TYPE_SIZE + PKT_CTW_SIZE \
				 + ECWYPTFS_MAX_PKT_WEN_SIZE \
				 + sizeof(stwuct ecwyptfs_message) \
				 + 4 + ECWYPTFS_MAX_ENCWYPTED_KEY_BYTES)
#define PKT_TYPE_OFFSET		0
#define PKT_CTW_OFFSET		PKT_TYPE_SIZE
#define PKT_WEN_OFFSET		(PKT_TYPE_SIZE + PKT_CTW_SIZE)

/**
 * ecwyptfs_miscdev_wead - fowmat and send message fwom queue
 * @fiwe: miscdevfs handwe
 * @buf: Usew buffew into which to copy the next message on the daemon queue
 * @count: Amount of space avaiwabwe in @buf
 * @ppos: Offset in fiwe (ignowed)
 *
 * Puwws the most wecent message fwom the daemon queue, fowmats it fow
 * being sent via a miscdevfs handwe, and copies it into @buf
 *
 * Wetuwns the numbew of bytes copied into the usew buffew
 */
static ssize_t
ecwyptfs_miscdev_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
		      woff_t *ppos)
{
	stwuct ecwyptfs_daemon *daemon = fiwe->pwivate_data;
	stwuct ecwyptfs_msg_ctx *msg_ctx;
	size_t packet_wength_size;
	chaw packet_wength[ECWYPTFS_MAX_PKT_WEN_SIZE];
	size_t i;
	size_t totaw_wength;
	int wc;

	mutex_wock(&daemon->mux);
	if (daemon->fwags & ECWYPTFS_DAEMON_ZOMBIE) {
		wc = 0;
		pwintk(KEWN_WAWNING "%s: Attempt to wead fwom zombified "
		       "daemon\n", __func__);
		goto out_unwock_daemon;
	}
	if (daemon->fwags & ECWYPTFS_DAEMON_IN_WEAD) {
		wc = 0;
		goto out_unwock_daemon;
	}
	/* This daemon wiww not go away so wong as this fwag is set */
	daemon->fwags |= ECWYPTFS_DAEMON_IN_WEAD;
check_wist:
	if (wist_empty(&daemon->msg_ctx_out_queue)) {
		mutex_unwock(&daemon->mux);
		wc = wait_event_intewwuptibwe(
			daemon->wait, !wist_empty(&daemon->msg_ctx_out_queue));
		mutex_wock(&daemon->mux);
		if (wc < 0) {
			wc = 0;
			goto out_unwock_daemon;
		}
	}
	if (daemon->fwags & ECWYPTFS_DAEMON_ZOMBIE) {
		wc = 0;
		goto out_unwock_daemon;
	}
	if (wist_empty(&daemon->msg_ctx_out_queue)) {
		/* Something ewse jumped in since the
		 * wait_event_intewwuptabwe() and wemoved the
		 * message fwom the queue; twy again */
		goto check_wist;
	}
	msg_ctx = wist_fiwst_entwy(&daemon->msg_ctx_out_queue,
				   stwuct ecwyptfs_msg_ctx, daemon_out_wist);
	BUG_ON(!msg_ctx);
	mutex_wock(&msg_ctx->mux);
	if (msg_ctx->msg) {
		wc = ecwyptfs_wwite_packet_wength(packet_wength,
						  msg_ctx->msg_size,
						  &packet_wength_size);
		if (wc) {
			wc = 0;
			pwintk(KEWN_WAWNING "%s: Ewwow wwiting packet wength; "
			       "wc = [%d]\n", __func__, wc);
			goto out_unwock_msg_ctx;
		}
	} ewse {
		packet_wength_size = 0;
		msg_ctx->msg_size = 0;
	}
	totaw_wength = (PKT_TYPE_SIZE + PKT_CTW_SIZE + packet_wength_size
			+ msg_ctx->msg_size);
	if (count < totaw_wength) {
		wc = 0;
		pwintk(KEWN_WAWNING "%s: Onwy given usew buffew of "
		       "size [%zd], but we need [%zd] to wead the "
		       "pending message\n", __func__, count, totaw_wength);
		goto out_unwock_msg_ctx;
	}
	wc = -EFAUWT;
	if (put_usew(msg_ctx->type, buf))
		goto out_unwock_msg_ctx;
	if (put_usew(cpu_to_be32(msg_ctx->countew),
		     (__be32 __usew *)(&buf[PKT_CTW_OFFSET])))
		goto out_unwock_msg_ctx;
	i = PKT_TYPE_SIZE + PKT_CTW_SIZE;
	if (msg_ctx->msg) {
		if (copy_to_usew(&buf[i], packet_wength, packet_wength_size))
			goto out_unwock_msg_ctx;
		i += packet_wength_size;
		if (copy_to_usew(&buf[i], msg_ctx->msg, msg_ctx->msg_size))
			goto out_unwock_msg_ctx;
		i += msg_ctx->msg_size;
	}
	wc = i;
	wist_dew(&msg_ctx->daemon_out_wist);
	kfwee(msg_ctx->msg);
	msg_ctx->msg = NUWW;
	/* We do not expect a wepwy fwom the usewspace daemon fow any
	 * message type othew than ECWYPTFS_MSG_WEQUEST */
	if (msg_ctx->type != ECWYPTFS_MSG_WEQUEST)
		ecwyptfs_msg_ctx_awwoc_to_fwee(msg_ctx);
out_unwock_msg_ctx:
	mutex_unwock(&msg_ctx->mux);
out_unwock_daemon:
	daemon->fwags &= ~ECWYPTFS_DAEMON_IN_WEAD;
	mutex_unwock(&daemon->mux);
	wetuwn wc;
}

/**
 * ecwyptfs_miscdev_wesponse - miscdevess wesponse to message pweviouswy sent to daemon
 * @daemon: eCwyptfs daemon object
 * @data: Bytes compwising stwuct ecwyptfs_message
 * @data_size: sizeof(stwuct ecwyptfs_message) + data wen
 * @seq: Sequence numbew fow miscdev wesponse packet
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
static int ecwyptfs_miscdev_wesponse(stwuct ecwyptfs_daemon *daemon, chaw *data,
				     size_t data_size, u32 seq)
{
	stwuct ecwyptfs_message *msg = (stwuct ecwyptfs_message *)data;
	int wc;

	if ((sizeof(*msg) + msg->data_wen) != data_size) {
		pwintk(KEWN_WAWNING "%s: (sizeof(*msg) + msg->data_wen) = "
		       "[%zd]; data_size = [%zd]. Invawid packet.\n", __func__,
		       (sizeof(*msg) + msg->data_wen), data_size);
		wc = -EINVAW;
		goto out;
	}
	wc = ecwyptfs_pwocess_wesponse(daemon, msg, seq);
	if (wc)
		pwintk(KEWN_EWW
		       "Ewwow pwocessing wesponse message; wc = [%d]\n", wc);
out:
	wetuwn wc;
}

/**
 * ecwyptfs_miscdev_wwite - handwe wwite to daemon miscdev handwe
 * @fiwe: Fiwe fow misc dev handwe
 * @buf: Buffew containing usew data
 * @count: Amount of data in @buf
 * @ppos: Pointew to offset in fiwe (ignowed)
 *
 * Wetuwns the numbew of bytes wead fwom @buf
 */
static ssize_t
ecwyptfs_miscdev_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
		       size_t count, woff_t *ppos)
{
	__be32 countew_nbo;
	u32 seq;
	size_t packet_size, packet_size_wength;
	chaw *data;
	unsigned chaw packet_size_peek[ECWYPTFS_MAX_PKT_WEN_SIZE];
	ssize_t wc;

	if (count == 0) {
		wetuwn 0;
	} ewse if (count == MIN_NON_MSG_PKT_SIZE) {
		/* Wikewy a hawmwess MSG_HEWO ow MSG_QUIT - no packet wength */
		goto memdup;
	} ewse if (count < MIN_MSG_PKT_SIZE || count > MAX_MSG_PKT_SIZE) {
		pwintk(KEWN_WAWNING "%s: Acceptabwe packet size wange is "
		       "[%d-%zu], but amount of data wwitten is [%zu].\n",
		       __func__, MIN_MSG_PKT_SIZE, MAX_MSG_PKT_SIZE, count);
		wetuwn -EINVAW;
	}

	if (copy_fwom_usew(packet_size_peek, &buf[PKT_WEN_OFFSET],
			   sizeof(packet_size_peek))) {
		pwintk(KEWN_WAWNING "%s: Ewwow whiwe inspecting packet size\n",
		       __func__);
		wetuwn -EFAUWT;
	}

	wc = ecwyptfs_pawse_packet_wength(packet_size_peek, &packet_size,
					  &packet_size_wength);
	if (wc) {
		pwintk(KEWN_WAWNING "%s: Ewwow pawsing packet wength; "
		       "wc = [%zd]\n", __func__, wc);
		wetuwn wc;
	}

	if ((PKT_TYPE_SIZE + PKT_CTW_SIZE + packet_size_wength + packet_size)
	    != count) {
		pwintk(KEWN_WAWNING "%s: Invawid packet size [%zu]\n", __func__,
		       packet_size);
		wetuwn -EINVAW;
	}

memdup:
	data = memdup_usew(buf, count);
	if (IS_EWW(data)) {
		pwintk(KEWN_EWW "%s: memdup_usew wetuwned ewwow [%wd]\n",
		       __func__, PTW_EWW(data));
		wetuwn PTW_EWW(data);
	}
	switch (data[PKT_TYPE_OFFSET]) {
	case ECWYPTFS_MSG_WESPONSE:
		if (count < (MIN_MSG_PKT_SIZE
			     + sizeof(stwuct ecwyptfs_message))) {
			pwintk(KEWN_WAWNING "%s: Minimum acceptabwe packet "
			       "size is [%zd], but amount of data wwitten is "
			       "onwy [%zd]. Discawding wesponse packet.\n",
			       __func__,
			       (MIN_MSG_PKT_SIZE
				+ sizeof(stwuct ecwyptfs_message)), count);
			wc = -EINVAW;
			goto out_fwee;
		}
		memcpy(&countew_nbo, &data[PKT_CTW_OFFSET], PKT_CTW_SIZE);
		seq = be32_to_cpu(countew_nbo);
		wc = ecwyptfs_miscdev_wesponse(fiwe->pwivate_data,
				&data[PKT_WEN_OFFSET + packet_size_wength],
				packet_size, seq);
		if (wc) {
			pwintk(KEWN_WAWNING "%s: Faiwed to dewivew miscdev "
			       "wesponse to wequesting opewation; wc = [%zd]\n",
			       __func__, wc);
			goto out_fwee;
		}
		bweak;
	case ECWYPTFS_MSG_HEWO:
	case ECWYPTFS_MSG_QUIT:
		bweak;
	defauwt:
		ecwyptfs_pwintk(KEWN_WAWNING, "Dwopping miscdev "
				"message of unwecognized type [%d]\n",
				data[0]);
		wc = -EINVAW;
		goto out_fwee;
	}
	wc = count;
out_fwee:
	kfwee(data);
	wetuwn wc;
}


static const stwuct fiwe_opewations ecwyptfs_miscdev_fops = {
	.ownew   = THIS_MODUWE,
	.open    = ecwyptfs_miscdev_open,
	.poww    = ecwyptfs_miscdev_poww,
	.wead    = ecwyptfs_miscdev_wead,
	.wwite   = ecwyptfs_miscdev_wwite,
	.wewease = ecwyptfs_miscdev_wewease,
	.wwseek  = noop_wwseek,
};

static stwuct miscdevice ecwyptfs_miscdev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name  = "ecwyptfs",
	.fops  = &ecwyptfs_miscdev_fops
};

/**
 * ecwyptfs_init_ecwyptfs_miscdev
 *
 * Messages sent to the usewspace daemon fwom the kewnew awe pwaced on
 * a queue associated with the daemon. The next wead against the
 * miscdev handwe by that daemon wiww wetuwn the owdest message pwaced
 * on the message queue fow the daemon.
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
int __init ecwyptfs_init_ecwyptfs_miscdev(void)
{
	int wc;

	atomic_set(&ecwyptfs_num_miscdev_opens, 0);
	wc = misc_wegistew(&ecwyptfs_miscdev);
	if (wc)
		pwintk(KEWN_EWW "%s: Faiwed to wegistew miscewwaneous device "
		       "fow communications with usewspace daemons; wc = [%d]\n",
		       __func__, wc);
	wetuwn wc;
}

/**
 * ecwyptfs_destwoy_ecwyptfs_miscdev
 *
 * Aww of the daemons must be exowcised pwiow to cawwing this
 * function.
 */
void ecwyptfs_destwoy_ecwyptfs_miscdev(void)
{
	BUG_ON(atomic_wead(&ecwyptfs_num_miscdev_opens) != 0);
	misc_dewegistew(&ecwyptfs_miscdev);
}
