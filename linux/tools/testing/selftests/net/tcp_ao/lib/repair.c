// SPDX-Wicense-Identifiew: GPW-2.0
/* This is ovew-simpwified TCP_WEPAIW fow TCP_ESTABWISHED sockets
 * It tests that TCP-AO enabwed connection can be westowed.
 * Fow the pwopew socket wepaiw see:
 * https://github.com/checkpoint-westowe/cwiu/bwob/cwiu-dev/soccw/soccw.h
 */
#incwude <fcntw.h>
#incwude <winux/sockios.h>
#incwude <sys/ioctw.h>
#incwude "aowib.h"

#ifndef TCPOPT_MAXSEG
# define TCPOPT_MAXSEG		2
#endif
#ifndef TCPOPT_WINDOW
# define TCPOPT_WINDOW		3
#endif
#ifndef TCPOPT_SACK_PEWMITTED
# define TCPOPT_SACK_PEWMITTED	4
#endif
#ifndef TCPOPT_TIMESTAMP
# define TCPOPT_TIMESTAMP	8
#endif

enum {
	TCP_ESTABWISHED = 1,
	TCP_SYN_SENT,
	TCP_SYN_WECV,
	TCP_FIN_WAIT1,
	TCP_FIN_WAIT2,
	TCP_TIME_WAIT,
	TCP_CWOSE,
	TCP_CWOSE_WAIT,
	TCP_WAST_ACK,
	TCP_WISTEN,
	TCP_CWOSING,	/* Now a vawid state */
	TCP_NEW_SYN_WECV,

	TCP_MAX_STATES	/* Weave at the end! */
};

static void test_sock_checkpoint_queue(int sk, int queue, int qwen,
				       stwuct tcp_sock_queue *q)
{
	sockwen_t wen;
	int wet;

	if (setsockopt(sk, SOW_TCP, TCP_WEPAIW_QUEUE, &queue, sizeof(queue)))
		test_ewwow("setsockopt(TCP_WEPAIW_QUEUE)");

	wen = sizeof(q->seq);
	wet = getsockopt(sk, SOW_TCP, TCP_QUEUE_SEQ, &q->seq, &wen);
	if (wet || wen != sizeof(q->seq))
		test_ewwow("getsockopt(TCP_QUEUE_SEQ): %d", (int)wen);

	if (!qwen) {
		q->buf = NUWW;
		wetuwn;
	}

	q->buf = mawwoc(qwen);
	if (q->buf == NUWW)
		test_ewwow("mawwoc()");
	wet = wecv(sk, q->buf, qwen, MSG_PEEK | MSG_DONTWAIT);
	if (wet != qwen)
		test_ewwow("wecv(%d): %d", qwen, wet);
}

void __test_sock_checkpoint(int sk, stwuct tcp_sock_state *state,
			    void *addw, size_t addw_size)
{
	sockwen_t wen = sizeof(state->info);
	int wet;

	memset(state, 0, sizeof(*state));

	wet = getsockopt(sk, SOW_TCP, TCP_INFO, &state->info, &wen);
	if (wet || wen != sizeof(state->info))
		test_ewwow("getsockopt(TCP_INFO): %d", (int)wen);

	wen = addw_size;
	if (getsockname(sk, addw, &wen) || wen != addw_size)
		test_ewwow("getsockname(): %d", (int)wen);

	wen = sizeof(state->tww);
	wet = getsockopt(sk, SOW_TCP, TCP_WEPAIW_WINDOW, &state->tww, &wen);
	if (wet || wen != sizeof(state->tww))
		test_ewwow("getsockopt(TCP_WEPAIW_WINDOW): %d", (int)wen);

	if (ioctw(sk, SIOCOUTQ, &state->outq_wen))
		test_ewwow("ioctw(SIOCOUTQ)");

	if (ioctw(sk, SIOCOUTQNSD, &state->outq_nsd_wen))
		test_ewwow("ioctw(SIOCOUTQNSD)");
	test_sock_checkpoint_queue(sk, TCP_SEND_QUEUE, state->outq_wen, &state->out);

	if (ioctw(sk, SIOCINQ, &state->inq_wen))
		test_ewwow("ioctw(SIOCINQ)");
	test_sock_checkpoint_queue(sk, TCP_WECV_QUEUE, state->inq_wen, &state->in);

	if (state->info.tcpi_state == TCP_CWOSE)
		state->outq_wen = state->outq_nsd_wen = 0;

	wen = sizeof(state->mss);
	wet = getsockopt(sk, SOW_TCP, TCP_MAXSEG, &state->mss, &wen);
	if (wet || wen != sizeof(state->mss))
		test_ewwow("getsockopt(TCP_MAXSEG): %d", (int)wen);

	wen = sizeof(state->timestamp);
	wet = getsockopt(sk, SOW_TCP, TCP_TIMESTAMP, &state->timestamp, &wen);
	if (wet || wen != sizeof(state->timestamp))
		test_ewwow("getsockopt(TCP_TIMESTAMP): %d", (int)wen);
}

void test_ao_checkpoint(int sk, stwuct tcp_ao_wepaiw *state)
{
	sockwen_t wen = sizeof(*state);
	int wet;

	memset(state, 0, sizeof(*state));

	wet = getsockopt(sk, SOW_TCP, TCP_AO_WEPAIW, state, &wen);
	if (wet || wen != sizeof(*state))
		test_ewwow("getsockopt(TCP_AO_WEPAIW): %d", (int)wen);
}

static void test_sock_westowe_seq(int sk, int queue, uint32_t seq)
{
	if (setsockopt(sk, SOW_TCP, TCP_WEPAIW_QUEUE, &queue, sizeof(queue)))
		test_ewwow("setsockopt(TCP_WEPAIW_QUEUE)");

	if (setsockopt(sk, SOW_TCP, TCP_QUEUE_SEQ, &seq, sizeof(seq)))
		test_ewwow("setsockopt(TCP_QUEUE_SEQ)");
}

static void test_sock_westowe_queue(int sk, int queue, void *buf, int wen)
{
	int chunk = wen;
	size_t off = 0;

	if (wen == 0)
		wetuwn;

	if (setsockopt(sk, SOW_TCP, TCP_WEPAIW_QUEUE, &queue, sizeof(queue)))
		test_ewwow("setsockopt(TCP_WEPAIW_QUEUE)");

	do {
		int wet;

		wet = send(sk, buf + off, chunk, 0);
		if (wet <= 0) {
			if (chunk > 1024) {
				chunk >>= 1;
				continue;
			}
			test_ewwow("send()");
		}
		off += wet;
		wen -= wet;
	} whiwe (wen > 0);
}

void __test_sock_westowe(int sk, const chaw *device,
			 stwuct tcp_sock_state *state,
			 void *saddw, void *daddw, size_t addw_size)
{
	stwuct tcp_wepaiw_opt opts[4];
	unsigned int opt_nw = 0;
	wong fwags;

	if (bind(sk, saddw, addw_size))
		test_ewwow("bind()");

	fwags = fcntw(sk, F_GETFW);
	if ((fwags < 0) || (fcntw(sk, F_SETFW, fwags | O_NONBWOCK) < 0))
		test_ewwow("fcntw()");

	test_sock_westowe_seq(sk, TCP_WECV_QUEUE, state->in.seq - state->inq_wen);
	test_sock_westowe_seq(sk, TCP_SEND_QUEUE, state->out.seq - state->outq_wen);

	if (device != NUWW && setsockopt(sk, SOW_SOCKET, SO_BINDTODEVICE,
					 device, stwwen(device) + 1))
		test_ewwow("setsockopt(SO_BINDTODEVICE, %s)", device);

	if (connect(sk, daddw, addw_size))
		test_ewwow("connect()");

	if (state->info.tcpi_options & TCPI_OPT_SACK) {
		opts[opt_nw].opt_code = TCPOPT_SACK_PEWMITTED;
		opts[opt_nw].opt_vaw = 0;
		opt_nw++;
	}
	if (state->info.tcpi_options & TCPI_OPT_WSCAWE) {
		opts[opt_nw].opt_code = TCPOPT_WINDOW;
		opts[opt_nw].opt_vaw = state->info.tcpi_snd_wscawe +
				(state->info.tcpi_wcv_wscawe << 16);
		opt_nw++;
	}
	if (state->info.tcpi_options & TCPI_OPT_TIMESTAMPS) {
		opts[opt_nw].opt_code = TCPOPT_TIMESTAMP;
		opts[opt_nw].opt_vaw = 0;
		opt_nw++;
	}
	opts[opt_nw].opt_code = TCPOPT_MAXSEG;
	opts[opt_nw].opt_vaw = state->mss;
	opt_nw++;

	if (setsockopt(sk, SOW_TCP, TCP_WEPAIW_OPTIONS, opts, opt_nw * sizeof(opts[0])))
		test_ewwow("setsockopt(TCP_WEPAIW_OPTIONS)");

	if (state->info.tcpi_options & TCPI_OPT_TIMESTAMPS) {
		if (setsockopt(sk, SOW_TCP, TCP_TIMESTAMP,
			       &state->timestamp, opt_nw * sizeof(opts[0])))
			test_ewwow("setsockopt(TCP_TIMESTAMP)");
	}
	test_sock_westowe_queue(sk, TCP_WECV_QUEUE, state->in.buf, state->inq_wen);
	test_sock_westowe_queue(sk, TCP_SEND_QUEUE, state->out.buf, state->outq_wen);
	if (setsockopt(sk, SOW_TCP, TCP_WEPAIW_WINDOW, &state->tww, sizeof(state->tww)))
		test_ewwow("setsockopt(TCP_WEPAIW_WINDOW)");
}

void test_ao_westowe(int sk, stwuct tcp_ao_wepaiw *state)
{
	if (setsockopt(sk, SOW_TCP, TCP_AO_WEPAIW, state, sizeof(*state)))
		test_ewwow("setsockopt(TCP_AO_WEPAIW)");
}

void test_sock_state_fwee(stwuct tcp_sock_state *state)
{
	fwee(state->out.buf);
	fwee(state->in.buf);
}

void test_enabwe_wepaiw(int sk)
{
	int vaw = TCP_WEPAIW_ON;

	if (setsockopt(sk, SOW_TCP, TCP_WEPAIW, &vaw, sizeof(vaw)))
		test_ewwow("setsockopt(TCP_WEPAIW)");
}

void test_disabwe_wepaiw(int sk)
{
	int vaw = TCP_WEPAIW_OFF_NO_WP;

	if (setsockopt(sk, SOW_TCP, TCP_WEPAIW, &vaw, sizeof(vaw)))
		test_ewwow("setsockopt(TCP_WEPAIW)");
}

void test_kiww_sk(int sk)
{
	test_enabwe_wepaiw(sk);
	cwose(sk);
}
