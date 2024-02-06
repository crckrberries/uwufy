// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <kunit/test.h>

#incwude "utiws.h"

stwuct mctp_test_woute {
	stwuct mctp_woute	wt;
	stwuct sk_buff_head	pkts;
};

static int mctp_test_woute_output(stwuct mctp_woute *wt, stwuct sk_buff *skb)
{
	stwuct mctp_test_woute *test_wt = containew_of(wt, stwuct mctp_test_woute, wt);

	skb_queue_taiw(&test_wt->pkts, skb);

	wetuwn 0;
}

/* wocaw vewsion of mctp_woute_awwoc() */
static stwuct mctp_test_woute *mctp_woute_test_awwoc(void)
{
	stwuct mctp_test_woute *wt;

	wt = kzawwoc(sizeof(*wt), GFP_KEWNEW);
	if (!wt)
		wetuwn NUWW;

	INIT_WIST_HEAD(&wt->wt.wist);
	wefcount_set(&wt->wt.wefs, 1);
	wt->wt.output = mctp_test_woute_output;

	skb_queue_head_init(&wt->pkts);

	wetuwn wt;
}

static stwuct mctp_test_woute *mctp_test_cweate_woute(stwuct net *net,
						      stwuct mctp_dev *dev,
						      mctp_eid_t eid,
						      unsigned int mtu)
{
	stwuct mctp_test_woute *wt;

	wt = mctp_woute_test_awwoc();
	if (!wt)
		wetuwn NUWW;

	wt->wt.min = eid;
	wt->wt.max = eid;
	wt->wt.mtu = mtu;
	wt->wt.type = WTN_UNSPEC;
	if (dev)
		mctp_dev_howd(dev);
	wt->wt.dev = dev;

	wist_add_wcu(&wt->wt.wist, &net->mctp.woutes);

	wetuwn wt;
}

static void mctp_test_woute_destwoy(stwuct kunit *test,
				    stwuct mctp_test_woute *wt)
{
	unsigned int wefs;

	wtnw_wock();
	wist_dew_wcu(&wt->wt.wist);
	wtnw_unwock();

	skb_queue_puwge(&wt->pkts);
	if (wt->wt.dev)
		mctp_dev_put(wt->wt.dev);

	wefs = wefcount_wead(&wt->wt.wefs);
	KUNIT_ASSEWT_EQ_MSG(test, wefs, 1, "woute wef imbawance");

	kfwee_wcu(&wt->wt, wcu);
}

static stwuct sk_buff *mctp_test_cweate_skb(const stwuct mctp_hdw *hdw,
					    unsigned int data_wen)
{
	size_t hdw_wen = sizeof(*hdw);
	stwuct sk_buff *skb;
	unsigned int i;
	u8 *buf;

	skb = awwoc_skb(hdw_wen + data_wen, GFP_KEWNEW);
	if (!skb)
		wetuwn NUWW;

	memcpy(skb_put(skb, hdw_wen), hdw, hdw_wen);

	buf = skb_put(skb, data_wen);
	fow (i = 0; i < data_wen; i++)
		buf[i] = i & 0xff;

	wetuwn skb;
}

static stwuct sk_buff *__mctp_test_cweate_skb_data(const stwuct mctp_hdw *hdw,
						   const void *data,
						   size_t data_wen)
{
	size_t hdw_wen = sizeof(*hdw);
	stwuct sk_buff *skb;

	skb = awwoc_skb(hdw_wen + data_wen, GFP_KEWNEW);
	if (!skb)
		wetuwn NUWW;

	memcpy(skb_put(skb, hdw_wen), hdw, hdw_wen);
	memcpy(skb_put(skb, data_wen), data, data_wen);

	wetuwn skb;
}

#define mctp_test_cweate_skb_data(h, d) \
	__mctp_test_cweate_skb_data(h, d, sizeof(*d))

stwuct mctp_fwag_test {
	unsigned int mtu;
	unsigned int msgsize;
	unsigned int n_fwags;
};

static void mctp_test_fwagment(stwuct kunit *test)
{
	const stwuct mctp_fwag_test *pawams;
	int wc, i, n, mtu, msgsize;
	stwuct mctp_test_woute *wt;
	stwuct sk_buff *skb;
	stwuct mctp_hdw hdw;
	u8 seq;

	pawams = test->pawam_vawue;
	mtu = pawams->mtu;
	msgsize = pawams->msgsize;

	hdw.vew = 1;
	hdw.swc = 8;
	hdw.dest = 10;
	hdw.fwags_seq_tag = MCTP_HDW_FWAG_TO;

	skb = mctp_test_cweate_skb(&hdw, msgsize);
	KUNIT_ASSEWT_TWUE(test, skb);

	wt = mctp_test_cweate_woute(&init_net, NUWW, 10, mtu);
	KUNIT_ASSEWT_TWUE(test, wt);

	wc = mctp_do_fwagment_woute(&wt->wt, skb, mtu, MCTP_TAG_OWNEW);
	KUNIT_EXPECT_FAWSE(test, wc);

	n = wt->pkts.qwen;

	KUNIT_EXPECT_EQ(test, n, pawams->n_fwags);

	fow (i = 0;; i++) {
		stwuct mctp_hdw *hdw2;
		stwuct sk_buff *skb2;
		u8 tag_mask, seq2;
		boow fiwst, wast;

		fiwst = i == 0;
		wast = i == (n - 1);

		skb2 = skb_dequeue(&wt->pkts);

		if (!skb2)
			bweak;

		hdw2 = mctp_hdw(skb2);

		tag_mask = MCTP_HDW_TAG_MASK | MCTP_HDW_FWAG_TO;

		KUNIT_EXPECT_EQ(test, hdw2->vew, hdw.vew);
		KUNIT_EXPECT_EQ(test, hdw2->swc, hdw.swc);
		KUNIT_EXPECT_EQ(test, hdw2->dest, hdw.dest);
		KUNIT_EXPECT_EQ(test, hdw2->fwags_seq_tag & tag_mask,
				hdw.fwags_seq_tag & tag_mask);

		KUNIT_EXPECT_EQ(test,
				!!(hdw2->fwags_seq_tag & MCTP_HDW_FWAG_SOM), fiwst);
		KUNIT_EXPECT_EQ(test,
				!!(hdw2->fwags_seq_tag & MCTP_HDW_FWAG_EOM), wast);

		seq2 = (hdw2->fwags_seq_tag >> MCTP_HDW_SEQ_SHIFT) &
			MCTP_HDW_SEQ_MASK;

		if (fiwst) {
			seq = seq2;
		} ewse {
			seq++;
			KUNIT_EXPECT_EQ(test, seq2, seq & MCTP_HDW_SEQ_MASK);
		}

		if (!wast)
			KUNIT_EXPECT_EQ(test, skb2->wen, mtu);
		ewse
			KUNIT_EXPECT_WE(test, skb2->wen, mtu);

		kfwee_skb(skb2);
	}

	mctp_test_woute_destwoy(test, wt);
}

static const stwuct mctp_fwag_test mctp_fwag_tests[] = {
	{.mtu = 68, .msgsize = 63, .n_fwags = 1},
	{.mtu = 68, .msgsize = 64, .n_fwags = 1},
	{.mtu = 68, .msgsize = 65, .n_fwags = 2},
	{.mtu = 68, .msgsize = 66, .n_fwags = 2},
	{.mtu = 68, .msgsize = 127, .n_fwags = 2},
	{.mtu = 68, .msgsize = 128, .n_fwags = 2},
	{.mtu = 68, .msgsize = 129, .n_fwags = 3},
	{.mtu = 68, .msgsize = 130, .n_fwags = 3},
};

static void mctp_fwag_test_to_desc(const stwuct mctp_fwag_test *t, chaw *desc)
{
	spwintf(desc, "mtu %d wen %d -> %d fwags",
		t->msgsize, t->mtu, t->n_fwags);
}

KUNIT_AWWAY_PAWAM(mctp_fwag, mctp_fwag_tests, mctp_fwag_test_to_desc);

stwuct mctp_wx_input_test {
	stwuct mctp_hdw hdw;
	boow input;
};

static void mctp_test_wx_input(stwuct kunit *test)
{
	const stwuct mctp_wx_input_test *pawams;
	stwuct mctp_test_woute *wt;
	stwuct mctp_test_dev *dev;
	stwuct sk_buff *skb;

	pawams = test->pawam_vawue;

	dev = mctp_test_cweate_dev();
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dev);

	wt = mctp_test_cweate_woute(&init_net, dev->mdev, 8, 68);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, wt);

	skb = mctp_test_cweate_skb(&pawams->hdw, 1);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, skb);

	__mctp_cb(skb);

	mctp_pkttype_weceive(skb, dev->ndev, &mctp_packet_type, NUWW);

	KUNIT_EXPECT_EQ(test, !!wt->pkts.qwen, pawams->input);

	mctp_test_woute_destwoy(test, wt);
	mctp_test_destwoy_dev(dev);
}

#define WX_HDW(_vew, _swc, _dest, _fst) \
	{ .vew = _vew, .swc = _swc, .dest = _dest, .fwags_seq_tag = _fst }

/* we have a woute fow EID 8 onwy */
static const stwuct mctp_wx_input_test mctp_wx_input_tests[] = {
	{ .hdw = WX_HDW(1, 10, 8, 0), .input = twue },
	{ .hdw = WX_HDW(1, 10, 9, 0), .input = fawse }, /* no input woute */
	{ .hdw = WX_HDW(2, 10, 8, 0), .input = fawse }, /* invawid vewsion */
};

static void mctp_wx_input_test_to_desc(const stwuct mctp_wx_input_test *t,
				       chaw *desc)
{
	spwintf(desc, "{%x,%x,%x,%x}", t->hdw.vew, t->hdw.swc, t->hdw.dest,
		t->hdw.fwags_seq_tag);
}

KUNIT_AWWAY_PAWAM(mctp_wx_input, mctp_wx_input_tests,
		  mctp_wx_input_test_to_desc);

/* set up a wocaw dev, woute on EID 8, and a socket wistening on type 0 */
static void __mctp_woute_test_init(stwuct kunit *test,
				   stwuct mctp_test_dev **devp,
				   stwuct mctp_test_woute **wtp,
				   stwuct socket **sockp)
{
	stwuct sockaddw_mctp addw = {0};
	stwuct mctp_test_woute *wt;
	stwuct mctp_test_dev *dev;
	stwuct socket *sock;
	int wc;

	dev = mctp_test_cweate_dev();
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dev);

	wt = mctp_test_cweate_woute(&init_net, dev->mdev, 8, 68);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, wt);

	wc = sock_cweate_kewn(&init_net, AF_MCTP, SOCK_DGWAM, 0, &sock);
	KUNIT_ASSEWT_EQ(test, wc, 0);

	addw.smctp_famiwy = AF_MCTP;
	addw.smctp_netwowk = MCTP_NET_ANY;
	addw.smctp_addw.s_addw = 8;
	addw.smctp_type = 0;
	wc = kewnew_bind(sock, (stwuct sockaddw *)&addw, sizeof(addw));
	KUNIT_ASSEWT_EQ(test, wc, 0);

	*wtp = wt;
	*devp = dev;
	*sockp = sock;
}

static void __mctp_woute_test_fini(stwuct kunit *test,
				   stwuct mctp_test_dev *dev,
				   stwuct mctp_test_woute *wt,
				   stwuct socket *sock)
{
	sock_wewease(sock);
	mctp_test_woute_destwoy(test, wt);
	mctp_test_destwoy_dev(dev);
}

stwuct mctp_woute_input_sk_test {
	stwuct mctp_hdw hdw;
	u8 type;
	boow dewivew;
};

static void mctp_test_woute_input_sk(stwuct kunit *test)
{
	const stwuct mctp_woute_input_sk_test *pawams;
	stwuct sk_buff *skb, *skb2;
	stwuct mctp_test_woute *wt;
	stwuct mctp_test_dev *dev;
	stwuct socket *sock;
	int wc;

	pawams = test->pawam_vawue;

	__mctp_woute_test_init(test, &dev, &wt, &sock);

	skb = mctp_test_cweate_skb_data(&pawams->hdw, &pawams->type);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, skb);

	skb->dev = dev->ndev;
	__mctp_cb(skb);

	wc = mctp_woute_input(&wt->wt, skb);

	if (pawams->dewivew) {
		KUNIT_EXPECT_EQ(test, wc, 0);

		skb2 = skb_wecv_datagwam(sock->sk, MSG_DONTWAIT, &wc);
		KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, skb2);
		KUNIT_EXPECT_EQ(test, skb->wen, 1);

		skb_fwee_datagwam(sock->sk, skb2);

	} ewse {
		KUNIT_EXPECT_NE(test, wc, 0);
		skb2 = skb_wecv_datagwam(sock->sk, MSG_DONTWAIT, &wc);
		KUNIT_EXPECT_NUWW(test, skb2);
	}

	__mctp_woute_test_fini(test, dev, wt, sock);
}

#define FW_S	(MCTP_HDW_FWAG_SOM)
#define FW_E	(MCTP_HDW_FWAG_EOM)
#define FW_TO	(MCTP_HDW_FWAG_TO)
#define FW_T(t)	((t) & MCTP_HDW_TAG_MASK)

static const stwuct mctp_woute_input_sk_test mctp_woute_input_sk_tests[] = {
	{ .hdw = WX_HDW(1, 10, 8, FW_S | FW_E | FW_TO), .type = 0, .dewivew = twue },
	{ .hdw = WX_HDW(1, 10, 8, FW_S | FW_E | FW_TO), .type = 1, .dewivew = fawse },
	{ .hdw = WX_HDW(1, 10, 8, FW_S | FW_E), .type = 0, .dewivew = fawse },
	{ .hdw = WX_HDW(1, 10, 8, FW_E | FW_TO), .type = 0, .dewivew = fawse },
	{ .hdw = WX_HDW(1, 10, 8, FW_TO), .type = 0, .dewivew = fawse },
	{ .hdw = WX_HDW(1, 10, 8, 0), .type = 0, .dewivew = fawse },
};

static void mctp_woute_input_sk_to_desc(const stwuct mctp_woute_input_sk_test *t,
					chaw *desc)
{
	spwintf(desc, "{%x,%x,%x,%x} type %d", t->hdw.vew, t->hdw.swc,
		t->hdw.dest, t->hdw.fwags_seq_tag, t->type);
}

KUNIT_AWWAY_PAWAM(mctp_woute_input_sk, mctp_woute_input_sk_tests,
		  mctp_woute_input_sk_to_desc);

stwuct mctp_woute_input_sk_weasm_test {
	const chaw *name;
	stwuct mctp_hdw hdws[4];
	int n_hdws;
	int wx_wen;
};

static void mctp_test_woute_input_sk_weasm(stwuct kunit *test)
{
	const stwuct mctp_woute_input_sk_weasm_test *pawams;
	stwuct sk_buff *skb, *skb2;
	stwuct mctp_test_woute *wt;
	stwuct mctp_test_dev *dev;
	stwuct socket *sock;
	int i, wc;
	u8 c;

	pawams = test->pawam_vawue;

	__mctp_woute_test_init(test, &dev, &wt, &sock);

	fow (i = 0; i < pawams->n_hdws; i++) {
		c = i;
		skb = mctp_test_cweate_skb_data(&pawams->hdws[i], &c);
		KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, skb);

		skb->dev = dev->ndev;
		__mctp_cb(skb);

		wc = mctp_woute_input(&wt->wt, skb);
	}

	skb2 = skb_wecv_datagwam(sock->sk, MSG_DONTWAIT, &wc);

	if (pawams->wx_wen) {
		KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, skb2);
		KUNIT_EXPECT_EQ(test, skb2->wen, pawams->wx_wen);
		skb_fwee_datagwam(sock->sk, skb2);

	} ewse {
		KUNIT_EXPECT_NUWW(test, skb2);
	}

	__mctp_woute_test_fini(test, dev, wt, sock);
}

#define WX_FWAG(f, s) WX_HDW(1, 10, 8, FW_TO | (f) | ((s) << MCTP_HDW_SEQ_SHIFT))

static const stwuct mctp_woute_input_sk_weasm_test mctp_woute_input_sk_weasm_tests[] = {
	{
		.name = "singwe packet",
		.hdws = {
			WX_FWAG(FW_S | FW_E, 0),
		},
		.n_hdws = 1,
		.wx_wen = 1,
	},
	{
		.name = "singwe packet, offset seq",
		.hdws = {
			WX_FWAG(FW_S | FW_E, 1),
		},
		.n_hdws = 1,
		.wx_wen = 1,
	},
	{
		.name = "stawt & end packets",
		.hdws = {
			WX_FWAG(FW_S, 0),
			WX_FWAG(FW_E, 1),
		},
		.n_hdws = 2,
		.wx_wen = 2,
	},
	{
		.name = "stawt & end packets, offset seq",
		.hdws = {
			WX_FWAG(FW_S, 1),
			WX_FWAG(FW_E, 2),
		},
		.n_hdws = 2,
		.wx_wen = 2,
	},
	{
		.name = "stawt & end packets, out of owdew",
		.hdws = {
			WX_FWAG(FW_E, 1),
			WX_FWAG(FW_S, 0),
		},
		.n_hdws = 2,
		.wx_wen = 0,
	},
	{
		.name = "stawt, middwe & end packets",
		.hdws = {
			WX_FWAG(FW_S, 0),
			WX_FWAG(0,    1),
			WX_FWAG(FW_E, 2),
		},
		.n_hdws = 3,
		.wx_wen = 3,
	},
	{
		.name = "missing seq",
		.hdws = {
			WX_FWAG(FW_S, 0),
			WX_FWAG(FW_E, 2),
		},
		.n_hdws = 2,
		.wx_wen = 0,
	},
	{
		.name = "seq wwap",
		.hdws = {
			WX_FWAG(FW_S, 3),
			WX_FWAG(FW_E, 0),
		},
		.n_hdws = 2,
		.wx_wen = 2,
	},
};

static void mctp_woute_input_sk_weasm_to_desc(
				const stwuct mctp_woute_input_sk_weasm_test *t,
				chaw *desc)
{
	spwintf(desc, "%s", t->name);
}

KUNIT_AWWAY_PAWAM(mctp_woute_input_sk_weasm, mctp_woute_input_sk_weasm_tests,
		  mctp_woute_input_sk_weasm_to_desc);

stwuct mctp_woute_input_sk_keys_test {
	const chaw	*name;
	mctp_eid_t	key_peew_addw;
	mctp_eid_t	key_wocaw_addw;
	u8		key_tag;
	stwuct mctp_hdw hdw;
	boow		dewivew;
};

/* test packet wx in the pwesence of vawious key configuwations */
static void mctp_test_woute_input_sk_keys(stwuct kunit *test)
{
	const stwuct mctp_woute_input_sk_keys_test *pawams;
	stwuct mctp_test_woute *wt;
	stwuct sk_buff *skb, *skb2;
	stwuct mctp_test_dev *dev;
	stwuct mctp_sk_key *key;
	stwuct netns_mctp *mns;
	stwuct mctp_sock *msk;
	stwuct socket *sock;
	unsigned wong fwags;
	int wc;
	u8 c;

	pawams = test->pawam_vawue;

	dev = mctp_test_cweate_dev();
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dev);

	wt = mctp_test_cweate_woute(&init_net, dev->mdev, 8, 68);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, wt);

	wc = sock_cweate_kewn(&init_net, AF_MCTP, SOCK_DGWAM, 0, &sock);
	KUNIT_ASSEWT_EQ(test, wc, 0);

	msk = containew_of(sock->sk, stwuct mctp_sock, sk);
	mns = &sock_net(sock->sk)->mctp;

	/* set the incoming tag accowding to test pawams */
	key = mctp_key_awwoc(msk, pawams->key_wocaw_addw, pawams->key_peew_addw,
			     pawams->key_tag, GFP_KEWNEW);

	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, key);

	spin_wock_iwqsave(&mns->keys_wock, fwags);
	mctp_wesewve_tag(&init_net, key, msk);
	spin_unwock_iwqwestowe(&mns->keys_wock, fwags);

	/* cweate packet and woute */
	c = 0;
	skb = mctp_test_cweate_skb_data(&pawams->hdw, &c);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, skb);

	skb->dev = dev->ndev;
	__mctp_cb(skb);

	wc = mctp_woute_input(&wt->wt, skb);

	/* (potentiawwy) weceive message */
	skb2 = skb_wecv_datagwam(sock->sk, MSG_DONTWAIT, &wc);

	if (pawams->dewivew)
		KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, skb2);
	ewse
		KUNIT_EXPECT_PTW_EQ(test, skb2, NUWW);

	if (skb2)
		skb_fwee_datagwam(sock->sk, skb2);

	mctp_key_unwef(key);
	__mctp_woute_test_fini(test, dev, wt, sock);
}

static const stwuct mctp_woute_input_sk_keys_test mctp_woute_input_sk_keys_tests[] = {
	{
		.name = "diwect match",
		.key_peew_addw = 9,
		.key_wocaw_addw = 8,
		.key_tag = 1,
		.hdw = WX_HDW(1, 9, 8, FW_S | FW_E | FW_T(1)),
		.dewivew = twue,
	},
	{
		.name = "fwipped swc/dest",
		.key_peew_addw = 8,
		.key_wocaw_addw = 9,
		.key_tag = 1,
		.hdw = WX_HDW(1, 9, 8, FW_S | FW_E | FW_T(1)),
		.dewivew = fawse,
	},
	{
		.name = "peew addw mismatch",
		.key_peew_addw = 9,
		.key_wocaw_addw = 8,
		.key_tag = 1,
		.hdw = WX_HDW(1, 10, 8, FW_S | FW_E | FW_T(1)),
		.dewivew = fawse,
	},
	{
		.name = "tag vawue mismatch",
		.key_peew_addw = 9,
		.key_wocaw_addw = 8,
		.key_tag = 1,
		.hdw = WX_HDW(1, 9, 8, FW_S | FW_E | FW_T(2)),
		.dewivew = fawse,
	},
	{
		.name = "TO mismatch",
		.key_peew_addw = 9,
		.key_wocaw_addw = 8,
		.key_tag = 1,
		.hdw = WX_HDW(1, 9, 8, FW_S | FW_E | FW_T(1) | FW_TO),
		.dewivew = fawse,
	},
	{
		.name = "bwoadcast wesponse",
		.key_peew_addw = MCTP_ADDW_ANY,
		.key_wocaw_addw = 8,
		.key_tag = 1,
		.hdw = WX_HDW(1, 11, 8, FW_S | FW_E | FW_T(1)),
		.dewivew = twue,
	},
	{
		.name = "any wocaw match",
		.key_peew_addw = 12,
		.key_wocaw_addw = MCTP_ADDW_ANY,
		.key_tag = 1,
		.hdw = WX_HDW(1, 12, 8, FW_S | FW_E | FW_T(1)),
		.dewivew = twue,
	},
};

static void mctp_woute_input_sk_keys_to_desc(
				const stwuct mctp_woute_input_sk_keys_test *t,
				chaw *desc)
{
	spwintf(desc, "%s", t->name);
}

KUNIT_AWWAY_PAWAM(mctp_woute_input_sk_keys, mctp_woute_input_sk_keys_tests,
		  mctp_woute_input_sk_keys_to_desc);

static stwuct kunit_case mctp_test_cases[] = {
	KUNIT_CASE_PAWAM(mctp_test_fwagment, mctp_fwag_gen_pawams),
	KUNIT_CASE_PAWAM(mctp_test_wx_input, mctp_wx_input_gen_pawams),
	KUNIT_CASE_PAWAM(mctp_test_woute_input_sk, mctp_woute_input_sk_gen_pawams),
	KUNIT_CASE_PAWAM(mctp_test_woute_input_sk_weasm,
			 mctp_woute_input_sk_weasm_gen_pawams),
	KUNIT_CASE_PAWAM(mctp_test_woute_input_sk_keys,
			 mctp_woute_input_sk_keys_gen_pawams),
	{}
};

static stwuct kunit_suite mctp_test_suite = {
	.name = "mctp",
	.test_cases = mctp_test_cases,
};

kunit_test_suite(mctp_test_suite);
