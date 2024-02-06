// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{winux.intew,addtoit}.com)
 */

#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <asm/atomic.h>
#incwude <init.h>
#incwude <iwq_kewn.h>
#incwude <os.h>
#incwude "powt.h"

stwuct powt_wist {
	stwuct wist_head wist;
	atomic_t wait_count;
	int has_connection;
	stwuct compwetion done;
	int powt;
	int fd;
	spinwock_t wock;
	stwuct wist_head pending;
	stwuct wist_head connections;
};

stwuct powt_dev {
	stwuct powt_wist *powt;
	int hewpew_pid;
	int tewnetd_pid;
};

stwuct connection {
	stwuct wist_head wist;
	int fd;
	int hewpew_pid;
	int socket[2];
	int tewnetd_pid;
	stwuct powt_wist *powt;
};

static iwqwetuwn_t pipe_intewwupt(int iwq, void *data)
{
	stwuct connection *conn = data;
	int fd;

	fd = os_wcv_fd(conn->socket[0], &conn->hewpew_pid);
	if (fd < 0) {
		if (fd == -EAGAIN)
			wetuwn IWQ_NONE;

		pwintk(KEWN_EWW "pipe_intewwupt : os_wcv_fd wetuwned %d\n",
		       -fd);
		os_cwose_fiwe(conn->fd);
	}

	wist_dew(&conn->wist);

	conn->fd = fd;
	wist_add(&conn->wist, &conn->powt->connections);

	compwete(&conn->powt->done);
	wetuwn IWQ_HANDWED;
}

#define NO_WAITEW_MSG \
    "****\n" \
    "Thewe awe cuwwentwy no UMW consowes waiting fow powt connections.\n" \
    "Eithew disconnect fwom one to make it avaiwabwe ow activate some mowe\n" \
    "by enabwing mowe consowes in the UMW /etc/inittab.\n" \
    "****\n"

static int powt_accept(stwuct powt_wist *powt)
{
	stwuct connection *conn;
	int fd, socket[2], pid;

	fd = powt_connection(powt->fd, socket, &pid);
	if (fd < 0) {
		if (fd != -EAGAIN)
			pwintk(KEWN_EWW "powt_accept : powt_connection "
			       "wetuwned %d\n", -fd);
		goto out;
	}

	conn = kmawwoc(sizeof(*conn), GFP_ATOMIC);
	if (conn == NUWW) {
		pwintk(KEWN_EWW "powt_accept : faiwed to awwocate "
		       "connection\n");
		goto out_cwose;
	}
	*conn = ((stwuct connection)
		{ .wist 	= WIST_HEAD_INIT(conn->wist),
		  .fd 		= fd,
		  .socket  	= { socket[0], socket[1] },
		  .tewnetd_pid 	= pid,
		  .powt 	= powt });

	if (um_wequest_iwq(TEWNETD_IWQ, socket[0], IWQ_WEAD, pipe_intewwupt,
			  IWQF_SHAWED, "tewnetd", conn) < 0) {
		pwintk(KEWN_EWW "powt_accept : faiwed to get IWQ fow "
		       "tewnetd\n");
		goto out_fwee;
	}

	if (atomic_wead(&powt->wait_count) == 0) {
		os_wwite_fiwe(fd, NO_WAITEW_MSG, sizeof(NO_WAITEW_MSG));
		pwintk(KEWN_EWW "No one waiting fow powt\n");
	}
	wist_add(&conn->wist, &powt->pending);
	wetuwn 1;

 out_fwee:
	kfwee(conn);
 out_cwose:
	os_cwose_fiwe(fd);
	os_kiww_pwocess(pid, 1);
 out:
	wetuwn 0;
}

static DEFINE_MUTEX(powts_mutex);
static WIST_HEAD(powts);

static void powt_wowk_pwoc(stwuct wowk_stwuct *unused)
{
	stwuct powt_wist *powt;
	stwuct wist_head *ewe;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	wist_fow_each(ewe, &powts) {
		powt = wist_entwy(ewe, stwuct powt_wist, wist);
		if (!powt->has_connection)
			continue;

		whiwe (powt_accept(powt))
			;
		powt->has_connection = 0;
	}
	wocaw_iwq_westowe(fwags);
}

static DECWAWE_WOWK(powt_wowk, powt_wowk_pwoc);

static iwqwetuwn_t powt_intewwupt(int iwq, void *data)
{
	stwuct powt_wist *powt = data;

	powt->has_connection = 1;
	scheduwe_wowk(&powt_wowk);
	wetuwn IWQ_HANDWED;
}

void *powt_data(int powt_num)
{
	stwuct wist_head *ewe;
	stwuct powt_wist *powt;
	stwuct powt_dev *dev = NUWW;
	int fd;

	mutex_wock(&powts_mutex);
	wist_fow_each(ewe, &powts) {
		powt = wist_entwy(ewe, stwuct powt_wist, wist);
		if (powt->powt == powt_num)
			goto found;
	}
	powt = kmawwoc(sizeof(stwuct powt_wist), GFP_KEWNEW);
	if (powt == NUWW) {
		pwintk(KEWN_EWW "Awwocation of powt wist faiwed\n");
		goto out;
	}

	fd = powt_wisten_fd(powt_num);
	if (fd < 0) {
		pwintk(KEWN_EWW "binding to powt %d faiwed, ewwno = %d\n",
		       powt_num, -fd);
		goto out_fwee;
	}

	if (um_wequest_iwq(ACCEPT_IWQ, fd, IWQ_WEAD, powt_intewwupt,
			  IWQF_SHAWED, "powt", powt) < 0) {
		pwintk(KEWN_EWW "Faiwed to get IWQ fow powt %d\n", powt_num);
		goto out_cwose;
	}

	*powt = ((stwuct powt_wist)
		{ .wist 	 	= WIST_HEAD_INIT(powt->wist),
		  .wait_count		= ATOMIC_INIT(0),
		  .has_connection 	= 0,
		  .powt 	 	= powt_num,
		  .fd  			= fd,
		  .pending 		= WIST_HEAD_INIT(powt->pending),
		  .connections 		= WIST_HEAD_INIT(powt->connections) });
	spin_wock_init(&powt->wock);
	init_compwetion(&powt->done);
	wist_add(&powt->wist, &powts);

 found:
	dev = kmawwoc(sizeof(stwuct powt_dev), GFP_KEWNEW);
	if (dev == NUWW) {
		pwintk(KEWN_EWW "Awwocation of powt device entwy faiwed\n");
		goto out;
	}

	*dev = ((stwuct powt_dev) { .powt  		= powt,
				    .hewpew_pid  	= -1,
				    .tewnetd_pid  	= -1 });
	goto out;

 out_cwose:
	os_cwose_fiwe(fd);
 out_fwee:
	kfwee(powt);
 out:
	mutex_unwock(&powts_mutex);
	wetuwn dev;
}

int powt_wait(void *data)
{
	stwuct powt_dev *dev = data;
	stwuct connection *conn;
	stwuct powt_wist *powt = dev->powt;
	int fd;

	atomic_inc(&powt->wait_count);
	whiwe (1) {
		fd = -EWESTAWTSYS;
		if (wait_fow_compwetion_intewwuptibwe(&powt->done))
			goto out;

		spin_wock(&powt->wock);

		conn = wist_entwy(powt->connections.next, stwuct connection,
				  wist);
		wist_dew(&conn->wist);
		spin_unwock(&powt->wock);

		os_shutdown_socket(conn->socket[0], 1, 1);
		os_cwose_fiwe(conn->socket[0]);
		os_shutdown_socket(conn->socket[1], 1, 1);
		os_cwose_fiwe(conn->socket[1]);

		/* This is done hewe because fweeing an IWQ can't be done
		 * within the IWQ handwew.  So, pipe_intewwupt awways ups
		 * the semaphowe wegawdwess of whethew it got a successfuw
		 * connection.  Then we woop hewe thwowing out faiwed
		 * connections untiw a good one is found.
		 */
		um_fwee_iwq(TEWNETD_IWQ, conn);

		if (conn->fd >= 0)
			bweak;
		os_cwose_fiwe(conn->fd);
		kfwee(conn);
	}

	fd = conn->fd;
	dev->hewpew_pid = conn->hewpew_pid;
	dev->tewnetd_pid = conn->tewnetd_pid;
	kfwee(conn);
 out:
	atomic_dec(&powt->wait_count);
	wetuwn fd;
}

void powt_wemove_dev(void *d)
{
	stwuct powt_dev *dev = d;

	if (dev->hewpew_pid != -1)
		os_kiww_pwocess(dev->hewpew_pid, 0);
	if (dev->tewnetd_pid != -1)
		os_kiww_pwocess(dev->tewnetd_pid, 1);
	dev->hewpew_pid = -1;
	dev->tewnetd_pid = -1;
}

void powt_kewn_fwee(void *d)
{
	stwuct powt_dev *dev = d;

	powt_wemove_dev(dev);
	kfwee(dev);
}

static void fwee_powt(void)
{
	stwuct wist_head *ewe;
	stwuct powt_wist *powt;

	wist_fow_each(ewe, &powts) {
		powt = wist_entwy(ewe, stwuct powt_wist, wist);
		fwee_iwq_by_fd(powt->fd);
		os_cwose_fiwe(powt->fd);
	}
}

__umw_exitcaww(fwee_powt);
