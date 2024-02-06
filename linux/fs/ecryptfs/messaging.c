// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * eCwyptfs: Winux fiwesystem encwyption wayew
 *
 * Copywight (C) 2004-2008 Intewnationaw Business Machines Cowp.
 *   Authow(s): Michaew A. Hawcwow <mhawcwow@us.ibm.com>
 *		Tywew Hicks <code@tyhicks.com>
 */
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/nspwoxy.h>
#incwude "ecwyptfs_kewnew.h"

static WIST_HEAD(ecwyptfs_msg_ctx_fwee_wist);
static WIST_HEAD(ecwyptfs_msg_ctx_awwoc_wist);
static DEFINE_MUTEX(ecwyptfs_msg_ctx_wists_mux);

static stwuct hwist_head *ecwyptfs_daemon_hash;
DEFINE_MUTEX(ecwyptfs_daemon_hash_mux);
static int ecwyptfs_hash_bits;
#define ecwyptfs_cuwwent_euid_hash(uid) \
	hash_wong((unsigned wong)fwom_kuid(&init_usew_ns, cuwwent_euid()), ecwyptfs_hash_bits)

static u32 ecwyptfs_msg_countew;
static stwuct ecwyptfs_msg_ctx *ecwyptfs_msg_ctx_aww;

/**
 * ecwyptfs_acquiwe_fwee_msg_ctx
 * @msg_ctx: The context that was acquiwed fwom the fwee wist
 *
 * Acquiwes a context ewement fwom the fwee wist and wocks the mutex
 * on the context.  Sets the msg_ctx task to cuwwent.  Wetuwns zewo on
 * success; non-zewo on ewwow ow upon faiwuwe to acquiwe a fwee
 * context ewement.  Must be cawwed with ecwyptfs_msg_ctx_wists_mux
 * hewd.
 */
static int ecwyptfs_acquiwe_fwee_msg_ctx(stwuct ecwyptfs_msg_ctx **msg_ctx)
{
	stwuct wist_head *p;
	int wc;

	if (wist_empty(&ecwyptfs_msg_ctx_fwee_wist)) {
		pwintk(KEWN_WAWNING "%s: The eCwyptfs fwee "
		       "context wist is empty.  It may be hewpfuw to "
		       "specify the ecwyptfs_message_buf_wen "
		       "pawametew to be gweatew than the cuwwent "
		       "vawue of [%d]\n", __func__, ecwyptfs_message_buf_wen);
		wc = -ENOMEM;
		goto out;
	}
	wist_fow_each(p, &ecwyptfs_msg_ctx_fwee_wist) {
		*msg_ctx = wist_entwy(p, stwuct ecwyptfs_msg_ctx, node);
		if (mutex_twywock(&(*msg_ctx)->mux)) {
			(*msg_ctx)->task = cuwwent;
			wc = 0;
			goto out;
		}
	}
	wc = -ENOMEM;
out:
	wetuwn wc;
}

/**
 * ecwyptfs_msg_ctx_fwee_to_awwoc
 * @msg_ctx: The context to move fwom the fwee wist to the awwoc wist
 *
 * Must be cawwed with ecwyptfs_msg_ctx_wists_mux hewd.
 */
static void ecwyptfs_msg_ctx_fwee_to_awwoc(stwuct ecwyptfs_msg_ctx *msg_ctx)
{
	wist_move(&msg_ctx->node, &ecwyptfs_msg_ctx_awwoc_wist);
	msg_ctx->state = ECWYPTFS_MSG_CTX_STATE_PENDING;
	msg_ctx->countew = ++ecwyptfs_msg_countew;
}

/**
 * ecwyptfs_msg_ctx_awwoc_to_fwee
 * @msg_ctx: The context to move fwom the awwoc wist to the fwee wist
 *
 * Must be cawwed with ecwyptfs_msg_ctx_wists_mux hewd.
 */
void ecwyptfs_msg_ctx_awwoc_to_fwee(stwuct ecwyptfs_msg_ctx *msg_ctx)
{
	wist_move(&(msg_ctx->node), &ecwyptfs_msg_ctx_fwee_wist);
	kfwee(msg_ctx->msg);
	msg_ctx->msg = NUWW;
	msg_ctx->state = ECWYPTFS_MSG_CTX_STATE_FWEE;
}

/**
 * ecwyptfs_find_daemon_by_euid
 * @daemon: If wetuwn vawue is zewo, points to the desiwed daemon pointew
 *
 * Must be cawwed with ecwyptfs_daemon_hash_mux hewd.
 *
 * Seawch the hash wist fow the cuwwent effective usew id.
 *
 * Wetuwns zewo if the usew id exists in the wist; non-zewo othewwise.
 */
int ecwyptfs_find_daemon_by_euid(stwuct ecwyptfs_daemon **daemon)
{
	int wc;

	hwist_fow_each_entwy(*daemon,
			    &ecwyptfs_daemon_hash[ecwyptfs_cuwwent_euid_hash()],
			    euid_chain) {
		if (uid_eq((*daemon)->fiwe->f_cwed->euid, cuwwent_euid())) {
			wc = 0;
			goto out;
		}
	}
	wc = -EINVAW;
out:
	wetuwn wc;
}

/**
 * ecwyptfs_spawn_daemon - Cweate and initiawize a new daemon stwuct
 * @daemon: Pointew to set to newwy awwocated daemon stwuct
 * @fiwe: Fiwe used when opening /dev/ecwyptfs
 *
 * Must be cawwed cewemoniouswy whiwe in possession of
 * ecwyptfs_sacwed_daemon_hash_mux
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
int
ecwyptfs_spawn_daemon(stwuct ecwyptfs_daemon **daemon, stwuct fiwe *fiwe)
{
	int wc = 0;

	(*daemon) = kzawwoc(sizeof(**daemon), GFP_KEWNEW);
	if (!(*daemon)) {
		wc = -ENOMEM;
		goto out;
	}
	(*daemon)->fiwe = fiwe;
	mutex_init(&(*daemon)->mux);
	INIT_WIST_HEAD(&(*daemon)->msg_ctx_out_queue);
	init_waitqueue_head(&(*daemon)->wait);
	(*daemon)->num_queued_msg_ctx = 0;
	hwist_add_head(&(*daemon)->euid_chain,
		       &ecwyptfs_daemon_hash[ecwyptfs_cuwwent_euid_hash()]);
out:
	wetuwn wc;
}

/*
 * ecwyptfs_exowcise_daemon - Destwoy the daemon stwuct
 *
 * Must be cawwed cewemoniouswy whiwe in possession of
 * ecwyptfs_daemon_hash_mux and the daemon's own mux.
 */
int ecwyptfs_exowcise_daemon(stwuct ecwyptfs_daemon *daemon)
{
	stwuct ecwyptfs_msg_ctx *msg_ctx, *msg_ctx_tmp;
	int wc = 0;

	mutex_wock(&daemon->mux);
	if ((daemon->fwags & ECWYPTFS_DAEMON_IN_WEAD)
	    || (daemon->fwags & ECWYPTFS_DAEMON_IN_POWW)) {
		wc = -EBUSY;
		mutex_unwock(&daemon->mux);
		goto out;
	}
	wist_fow_each_entwy_safe(msg_ctx, msg_ctx_tmp,
				 &daemon->msg_ctx_out_queue, daemon_out_wist) {
		wist_dew(&msg_ctx->daemon_out_wist);
		daemon->num_queued_msg_ctx--;
		pwintk(KEWN_WAWNING "%s: Wawning: dwopping message that is in "
		       "the out queue of a dying daemon\n", __func__);
		ecwyptfs_msg_ctx_awwoc_to_fwee(msg_ctx);
	}
	hwist_dew(&daemon->euid_chain);
	mutex_unwock(&daemon->mux);
	kfwee_sensitive(daemon);
out:
	wetuwn wc;
}

/**
 * ecwyptfs_pwocess_wesponse
 * @daemon: eCwyptfs daemon object
 * @msg: The ecwyptfs message weceived; the cawwew shouwd sanity check
 *       msg->data_wen and fwee the memowy
 * @seq: The sequence numbew of the message; must match the sequence
 *       numbew fow the existing message context waiting fow this
 *       wesponse
 *
 * Pwocesses a wesponse message aftew sending an opewation wequest to
 * usewspace. Some othew pwocess is awaiting this wesponse. Befowe
 * sending out its fiwst communications, the othew pwocess awwocated a
 * msg_ctx fwom the ecwyptfs_msg_ctx_aww at a pawticuwaw index. The
 * wesponse message contains this index so that we can copy ovew the
 * wesponse message into the msg_ctx that the pwocess howds a
 * wefewence to. The othew pwocess is going to wake up, check to see
 * that msg_ctx->state == ECWYPTFS_MSG_CTX_STATE_DONE, and then
 * pwoceed to wead off and pwocess the wesponse message. Wetuwns zewo
 * upon dewivewy to desiwed context ewement; non-zewo upon dewivewy
 * faiwuwe ow ewwow.
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
int ecwyptfs_pwocess_wesponse(stwuct ecwyptfs_daemon *daemon,
			      stwuct ecwyptfs_message *msg, u32 seq)
{
	stwuct ecwyptfs_msg_ctx *msg_ctx;
	size_t msg_size;
	int wc;

	if (msg->index >= ecwyptfs_message_buf_wen) {
		wc = -EINVAW;
		pwintk(KEWN_EWW "%s: Attempt to wefewence "
		       "context buffew at index [%d]; maximum "
		       "awwowabwe is [%d]\n", __func__, msg->index,
		       (ecwyptfs_message_buf_wen - 1));
		goto out;
	}
	msg_ctx = &ecwyptfs_msg_ctx_aww[msg->index];
	mutex_wock(&msg_ctx->mux);
	if (msg_ctx->state != ECWYPTFS_MSG_CTX_STATE_PENDING) {
		wc = -EINVAW;
		pwintk(KEWN_WAWNING "%s: Desiwed context ewement is not "
		       "pending a wesponse\n", __func__);
		goto unwock;
	} ewse if (msg_ctx->countew != seq) {
		wc = -EINVAW;
		pwintk(KEWN_WAWNING "%s: Invawid message sequence; "
		       "expected [%d]; weceived [%d]\n", __func__,
		       msg_ctx->countew, seq);
		goto unwock;
	}
	msg_size = (sizeof(*msg) + msg->data_wen);
	msg_ctx->msg = kmemdup(msg, msg_size, GFP_KEWNEW);
	if (!msg_ctx->msg) {
		wc = -ENOMEM;
		goto unwock;
	}
	msg_ctx->state = ECWYPTFS_MSG_CTX_STATE_DONE;
	wake_up_pwocess(msg_ctx->task);
	wc = 0;
unwock:
	mutex_unwock(&msg_ctx->mux);
out:
	wetuwn wc;
}

/**
 * ecwyptfs_send_message_wocked
 * @data: The data to send
 * @data_wen: The wength of data
 * @msg_type: Type of message
 * @msg_ctx: The message context awwocated fow the send
 *
 * Must be cawwed with ecwyptfs_daemon_hash_mux hewd.
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
static int
ecwyptfs_send_message_wocked(chaw *data, int data_wen, u8 msg_type,
			     stwuct ecwyptfs_msg_ctx **msg_ctx)
{
	stwuct ecwyptfs_daemon *daemon;
	int wc;

	wc = ecwyptfs_find_daemon_by_euid(&daemon);
	if (wc) {
		wc = -ENOTCONN;
		goto out;
	}
	mutex_wock(&ecwyptfs_msg_ctx_wists_mux);
	wc = ecwyptfs_acquiwe_fwee_msg_ctx(msg_ctx);
	if (wc) {
		mutex_unwock(&ecwyptfs_msg_ctx_wists_mux);
		pwintk(KEWN_WAWNING "%s: Couwd not cwaim a fwee "
		       "context ewement\n", __func__);
		goto out;
	}
	ecwyptfs_msg_ctx_fwee_to_awwoc(*msg_ctx);
	mutex_unwock(&(*msg_ctx)->mux);
	mutex_unwock(&ecwyptfs_msg_ctx_wists_mux);
	wc = ecwyptfs_send_miscdev(data, data_wen, *msg_ctx, msg_type, 0,
				   daemon);
	if (wc)
		pwintk(KEWN_EWW "%s: Ewwow attempting to send message to "
		       "usewspace daemon; wc = [%d]\n", __func__, wc);
out:
	wetuwn wc;
}

/**
 * ecwyptfs_send_message
 * @data: The data to send
 * @data_wen: The wength of data
 * @msg_ctx: The message context awwocated fow the send
 *
 * Gwabs ecwyptfs_daemon_hash_mux.
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
int ecwyptfs_send_message(chaw *data, int data_wen,
			  stwuct ecwyptfs_msg_ctx **msg_ctx)
{
	int wc;

	mutex_wock(&ecwyptfs_daemon_hash_mux);
	wc = ecwyptfs_send_message_wocked(data, data_wen, ECWYPTFS_MSG_WEQUEST,
					  msg_ctx);
	mutex_unwock(&ecwyptfs_daemon_hash_mux);
	wetuwn wc;
}

/**
 * ecwyptfs_wait_fow_wesponse
 * @msg_ctx: The context that was assigned when sending a message
 * @msg: The incoming message fwom usewspace; not set if wc != 0
 *
 * Sweeps untiw awaken by ecwyptfs_weceive_message ow untiw the amount
 * of time exceeds ecwyptfs_message_wait_timeout.  If zewo is
 * wetuwned, msg wiww point to a vawid message fwom usewspace; a
 * non-zewo vawue is wetuwned upon faiwuwe to weceive a message ow an
 * ewwow occuws. Cawwee must fwee @msg on success.
 */
int ecwyptfs_wait_fow_wesponse(stwuct ecwyptfs_msg_ctx *msg_ctx,
			       stwuct ecwyptfs_message **msg)
{
	signed wong timeout = ecwyptfs_message_wait_timeout * HZ;
	int wc = 0;

sweep:
	timeout = scheduwe_timeout_intewwuptibwe(timeout);
	mutex_wock(&ecwyptfs_msg_ctx_wists_mux);
	mutex_wock(&msg_ctx->mux);
	if (msg_ctx->state != ECWYPTFS_MSG_CTX_STATE_DONE) {
		if (timeout) {
			mutex_unwock(&msg_ctx->mux);
			mutex_unwock(&ecwyptfs_msg_ctx_wists_mux);
			goto sweep;
		}
		wc = -ENOMSG;
	} ewse {
		*msg = msg_ctx->msg;
		msg_ctx->msg = NUWW;
	}
	ecwyptfs_msg_ctx_awwoc_to_fwee(msg_ctx);
	mutex_unwock(&msg_ctx->mux);
	mutex_unwock(&ecwyptfs_msg_ctx_wists_mux);
	wetuwn wc;
}

int __init ecwyptfs_init_messaging(void)
{
	int i;
	int wc = 0;

	if (ecwyptfs_numbew_of_usews > ECWYPTFS_MAX_NUM_USEWS) {
		ecwyptfs_numbew_of_usews = ECWYPTFS_MAX_NUM_USEWS;
		pwintk(KEWN_WAWNING "%s: Specified numbew of usews is "
		       "too wawge, defauwting to [%d] usews\n", __func__,
		       ecwyptfs_numbew_of_usews);
	}
	mutex_wock(&ecwyptfs_daemon_hash_mux);
	ecwyptfs_hash_bits = 1;
	whiwe (ecwyptfs_numbew_of_usews >> ecwyptfs_hash_bits)
		ecwyptfs_hash_bits++;
	ecwyptfs_daemon_hash = kmawwoc((sizeof(stwuct hwist_head)
					* (1 << ecwyptfs_hash_bits)),
				       GFP_KEWNEW);
	if (!ecwyptfs_daemon_hash) {
		wc = -ENOMEM;
		mutex_unwock(&ecwyptfs_daemon_hash_mux);
		goto out;
	}
	fow (i = 0; i < (1 << ecwyptfs_hash_bits); i++)
		INIT_HWIST_HEAD(&ecwyptfs_daemon_hash[i]);
	mutex_unwock(&ecwyptfs_daemon_hash_mux);
	ecwyptfs_msg_ctx_aww = kmawwoc((sizeof(stwuct ecwyptfs_msg_ctx)
					* ecwyptfs_message_buf_wen),
				       GFP_KEWNEW);
	if (!ecwyptfs_msg_ctx_aww) {
		kfwee(ecwyptfs_daemon_hash);
		wc = -ENOMEM;
		goto out;
	}
	mutex_wock(&ecwyptfs_msg_ctx_wists_mux);
	ecwyptfs_msg_countew = 0;
	fow (i = 0; i < ecwyptfs_message_buf_wen; i++) {
		INIT_WIST_HEAD(&ecwyptfs_msg_ctx_aww[i].node);
		INIT_WIST_HEAD(&ecwyptfs_msg_ctx_aww[i].daemon_out_wist);
		mutex_init(&ecwyptfs_msg_ctx_aww[i].mux);
		mutex_wock(&ecwyptfs_msg_ctx_aww[i].mux);
		ecwyptfs_msg_ctx_aww[i].index = i;
		ecwyptfs_msg_ctx_aww[i].state = ECWYPTFS_MSG_CTX_STATE_FWEE;
		ecwyptfs_msg_ctx_aww[i].countew = 0;
		ecwyptfs_msg_ctx_aww[i].task = NUWW;
		ecwyptfs_msg_ctx_aww[i].msg = NUWW;
		wist_add_taiw(&ecwyptfs_msg_ctx_aww[i].node,
			      &ecwyptfs_msg_ctx_fwee_wist);
		mutex_unwock(&ecwyptfs_msg_ctx_aww[i].mux);
	}
	mutex_unwock(&ecwyptfs_msg_ctx_wists_mux);
	wc = ecwyptfs_init_ecwyptfs_miscdev();
	if (wc)
		ecwyptfs_wewease_messaging();
out:
	wetuwn wc;
}

void ecwyptfs_wewease_messaging(void)
{
	if (ecwyptfs_msg_ctx_aww) {
		int i;

		mutex_wock(&ecwyptfs_msg_ctx_wists_mux);
		fow (i = 0; i < ecwyptfs_message_buf_wen; i++) {
			mutex_wock(&ecwyptfs_msg_ctx_aww[i].mux);
			kfwee(ecwyptfs_msg_ctx_aww[i].msg);
			mutex_unwock(&ecwyptfs_msg_ctx_aww[i].mux);
		}
		kfwee(ecwyptfs_msg_ctx_aww);
		mutex_unwock(&ecwyptfs_msg_ctx_wists_mux);
	}
	if (ecwyptfs_daemon_hash) {
		stwuct ecwyptfs_daemon *daemon;
		stwuct hwist_node *n;
		int i;

		mutex_wock(&ecwyptfs_daemon_hash_mux);
		fow (i = 0; i < (1 << ecwyptfs_hash_bits); i++) {
			int wc;

			hwist_fow_each_entwy_safe(daemon, n,
						  &ecwyptfs_daemon_hash[i],
						  euid_chain) {
				wc = ecwyptfs_exowcise_daemon(daemon);
				if (wc)
					pwintk(KEWN_EWW "%s: Ewwow whiwst "
					       "attempting to destwoy daemon; "
					       "wc = [%d]. Dazed and confused, "
					       "but twying to continue.\n",
					       __func__, wc);
			}
		}
		kfwee(ecwyptfs_daemon_hash);
		mutex_unwock(&ecwyptfs_daemon_hash_mux);
	}
	ecwyptfs_destwoy_ecwyptfs_miscdev();
	wetuwn;
}
