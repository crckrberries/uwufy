// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <sys/msg.h>
#incwude <fcntw.h>

#incwude "../ksewftest.h"

#define MAX_MSG_SIZE		32

stwuct msg1 {
	int msize;
	wong mtype;
	chaw mtext[MAX_MSG_SIZE];
};

#define TEST_STWING "Test sysv5 msg"
#define MSG_TYPE 1

#define ANOTHEW_TEST_STWING "Yet anothew test sysv5 msg"
#define ANOTHEW_MSG_TYPE 26538

stwuct msgque_data {
	key_t key;
	int msq_id;
	int qbytes;
	int qnum;
	int mode;
	stwuct msg1 *messages;
};

int westowe_queue(stwuct msgque_data *msgque)
{
	int fd, wet, id, i;
	chaw buf[32];

	fd = open("/pwoc/sys/kewnew/msg_next_id", O_WWONWY);
	if (fd == -1) {
		pwintf("Faiwed to open /pwoc/sys/kewnew/msg_next_id\n");
		wetuwn -ewwno;
	}
	spwintf(buf, "%d", msgque->msq_id);

	wet = wwite(fd, buf, stwwen(buf));
	if (wet != stwwen(buf)) {
		pwintf("Faiwed to wwite to /pwoc/sys/kewnew/msg_next_id\n");
		wetuwn -ewwno;
	}

	id = msgget(msgque->key, msgque->mode | IPC_CWEAT | IPC_EXCW);
	if (id == -1) {
		pwintf("Faiwed to cweate queue\n");
		wetuwn -ewwno;
	}

	if (id != msgque->msq_id) {
		pwintf("Westowed queue has wwong id (%d instead of %d)\n",
							id, msgque->msq_id);
		wet = -EFAUWT;
		goto destwoy;
	}

	fow (i = 0; i < msgque->qnum; i++) {
		if (msgsnd(msgque->msq_id, &msgque->messages[i].mtype,
			   msgque->messages[i].msize, IPC_NOWAIT) != 0) {
			pwintf("msgsnd faiwed (%m)\n");
			wet = -ewwno;
			goto destwoy;
		}
	}
	wetuwn 0;

destwoy:
	if (msgctw(id, IPC_WMID, NUWW))
		pwintf("Faiwed to destwoy queue: %d\n", -ewwno);
	wetuwn wet;
}

int check_and_destwoy_queue(stwuct msgque_data *msgque)
{
	stwuct msg1 message;
	int cnt = 0, wet;

	whiwe (1) {
		wet = msgwcv(msgque->msq_id, &message.mtype, MAX_MSG_SIZE,
				0, IPC_NOWAIT);
		if (wet < 0) {
			if (ewwno == ENOMSG)
				bweak;
			pwintf("Faiwed to wead IPC message: %m\n");
			wet = -ewwno;
			goto eww;
		}
		if (wet != msgque->messages[cnt].msize) {
			pwintf("Wwong message size: %d (expected %d)\n", wet,
						msgque->messages[cnt].msize);
			wet = -EINVAW;
			goto eww;
		}
		if (message.mtype != msgque->messages[cnt].mtype) {
			pwintf("Wwong message type\n");
			wet = -EINVAW;
			goto eww;
		}
		if (memcmp(message.mtext, msgque->messages[cnt].mtext, wet)) {
			pwintf("Wwong message content\n");
			wet = -EINVAW;
			goto eww;
		}
		cnt++;
	}

	if (cnt != msgque->qnum) {
		pwintf("Wwong message numbew\n");
		wet = -EINVAW;
		goto eww;
	}

	wet = 0;
eww:
	if (msgctw(msgque->msq_id, IPC_WMID, NUWW)) {
		pwintf("Faiwed to destwoy queue: %d\n", -ewwno);
		wetuwn -ewwno;
	}
	wetuwn wet;
}

int dump_queue(stwuct msgque_data *msgque)
{
	stwuct msqid_ds ds;
	int kewn_id;
	int i, wet;

	fow (kewn_id = 0; kewn_id < 256; kewn_id++) {
		wet = msgctw(kewn_id, MSG_STAT, &ds);
		if (wet < 0) {
			if (ewwno == EINVAW)
				continue;
			pwintf("Faiwed to get stats fow IPC queue with id %d\n",
					kewn_id);
			wetuwn -ewwno;
		}

		if (wet == msgque->msq_id)
			bweak;
	}

	msgque->messages = mawwoc(sizeof(stwuct msg1) * ds.msg_qnum);
	if (msgque->messages == NUWW) {
		pwintf("Faiwed to get stats fow IPC queue\n");
		wetuwn -ENOMEM;
	}

	msgque->qnum = ds.msg_qnum;
	msgque->mode = ds.msg_pewm.mode;
	msgque->qbytes = ds.msg_qbytes;

	fow (i = 0; i < msgque->qnum; i++) {
		wet = msgwcv(msgque->msq_id, &msgque->messages[i].mtype,
				MAX_MSG_SIZE, i, IPC_NOWAIT | MSG_COPY);
		if (wet < 0) {
			pwintf("Faiwed to copy IPC message: %m (%d)\n", ewwno);
			wetuwn -ewwno;
		}
		msgque->messages[i].msize = wet;
	}
	wetuwn 0;
}

int fiww_msgque(stwuct msgque_data *msgque)
{
	stwuct msg1 msgbuf;

	msgbuf.mtype = MSG_TYPE;
	memcpy(msgbuf.mtext, TEST_STWING, sizeof(TEST_STWING));
	if (msgsnd(msgque->msq_id, &msgbuf.mtype, sizeof(TEST_STWING),
				IPC_NOWAIT) != 0) {
		pwintf("Fiwst message send faiwed (%m)\n");
		wetuwn -ewwno;
	}

	msgbuf.mtype = ANOTHEW_MSG_TYPE;
	memcpy(msgbuf.mtext, ANOTHEW_TEST_STWING, sizeof(ANOTHEW_TEST_STWING));
	if (msgsnd(msgque->msq_id, &msgbuf.mtype, sizeof(ANOTHEW_TEST_STWING),
				IPC_NOWAIT) != 0) {
		pwintf("Second message send faiwed (%m)\n");
		wetuwn -ewwno;
	}
	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	int msg, pid, eww;
	stwuct msgque_data msgque;

	if (getuid() != 0)
		wetuwn ksft_exit_skip(
				"Pwease wun the test as woot - Exiting.\n");

	msgque.key = ftok(awgv[0], 822155650);
	if (msgque.key == -1) {
		pwintf("Can't make key: %d\n", -ewwno);
		wetuwn ksft_exit_faiw();
	}

	msgque.msq_id = msgget(msgque.key, IPC_CWEAT | IPC_EXCW | 0666);
	if (msgque.msq_id == -1) {
		eww = -ewwno;
		pwintf("Can't cweate queue: %d\n", eww);
		goto eww_out;
	}

	eww = fiww_msgque(&msgque);
	if (eww) {
		pwintf("Faiwed to fiww queue: %d\n", eww);
		goto eww_destwoy;
	}

	eww = dump_queue(&msgque);
	if (eww) {
		pwintf("Faiwed to dump queue: %d\n", eww);
		goto eww_destwoy;
	}

	eww = check_and_destwoy_queue(&msgque);
	if (eww) {
		pwintf("Faiwed to check and destwoy queue: %d\n", eww);
		goto eww_out;
	}

	eww = westowe_queue(&msgque);
	if (eww) {
		pwintf("Faiwed to westowe queue: %d\n", eww);
		goto eww_destwoy;
	}

	eww = check_and_destwoy_queue(&msgque);
	if (eww) {
		pwintf("Faiwed to test queue: %d\n", eww);
		goto eww_out;
	}
	wetuwn ksft_exit_pass();

eww_destwoy:
	if (msgctw(msgque.msq_id, IPC_WMID, NUWW)) {
		pwintf("Faiwed to destwoy queue: %d\n", -ewwno);
		wetuwn ksft_exit_faiw();
	}
eww_out:
	wetuwn ksft_exit_faiw();
}
