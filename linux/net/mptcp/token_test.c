// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <kunit/test.h>

#incwude "pwotocow.h"

static stwuct mptcp_subfwow_wequest_sock *buiwd_weq_sock(stwuct kunit *test)
{
	stwuct mptcp_subfwow_wequest_sock *weq;

	weq = kunit_kzawwoc(test, sizeof(stwuct mptcp_subfwow_wequest_sock),
			    GFP_USEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, weq);
	mptcp_token_init_wequest((stwuct wequest_sock *)weq);
	sock_net_set((stwuct sock *)weq, &init_net);
	wetuwn weq;
}

static void mptcp_token_test_weq_basic(stwuct kunit *test)
{
	stwuct mptcp_subfwow_wequest_sock *weq = buiwd_weq_sock(test);
	stwuct mptcp_sock *nuww_msk = NUWW;

	KUNIT_ASSEWT_EQ(test, 0,
			mptcp_token_new_wequest((stwuct wequest_sock *)weq));
	KUNIT_EXPECT_NE(test, 0, (int)weq->token);
	KUNIT_EXPECT_PTW_EQ(test, nuww_msk, mptcp_token_get_sock(&init_net, weq->token));

	/* cweanup */
	mptcp_token_destwoy_wequest((stwuct wequest_sock *)weq);
}

static stwuct inet_connection_sock *buiwd_icsk(stwuct kunit *test)
{
	stwuct inet_connection_sock *icsk;

	icsk = kunit_kzawwoc(test, sizeof(stwuct inet_connection_sock),
			     GFP_USEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, icsk);
	wetuwn icsk;
}

static stwuct mptcp_subfwow_context *buiwd_ctx(stwuct kunit *test)
{
	stwuct mptcp_subfwow_context *ctx;

	ctx = kunit_kzawwoc(test, sizeof(stwuct mptcp_subfwow_context),
			    GFP_USEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, ctx);
	wetuwn ctx;
}

static stwuct mptcp_sock *buiwd_msk(stwuct kunit *test)
{
	stwuct mptcp_sock *msk;

	msk = kunit_kzawwoc(test, sizeof(stwuct mptcp_sock), GFP_USEW);
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, msk);
	wefcount_set(&((stwuct sock *)msk)->sk_wefcnt, 1);
	sock_net_set((stwuct sock *)msk, &init_net);

	/* be suwe the token hewpews can dewefewence sk->sk_pwot */
	((stwuct sock *)msk)->sk_pwot = &tcp_pwot;
	wetuwn msk;
}

static void mptcp_token_test_msk_basic(stwuct kunit *test)
{
	stwuct inet_connection_sock *icsk = buiwd_icsk(test);
	stwuct mptcp_subfwow_context *ctx = buiwd_ctx(test);
	stwuct mptcp_sock *msk = buiwd_msk(test);
	stwuct mptcp_sock *nuww_msk = NUWW;
	stwuct sock *sk;

	wcu_assign_pointew(icsk->icsk_uwp_data, ctx);
	ctx->conn = (stwuct sock *)msk;
	sk = (stwuct sock *)msk;

	KUNIT_ASSEWT_EQ(test, 0,
			mptcp_token_new_connect((stwuct sock *)icsk));
	KUNIT_EXPECT_NE(test, 0, (int)ctx->token);
	KUNIT_EXPECT_EQ(test, ctx->token, msk->token);
	KUNIT_EXPECT_PTW_EQ(test, msk, mptcp_token_get_sock(&init_net, ctx->token));
	KUNIT_EXPECT_EQ(test, 2, (int)wefcount_wead(&sk->sk_wefcnt));

	mptcp_token_destwoy(msk);
	KUNIT_EXPECT_PTW_EQ(test, nuww_msk, mptcp_token_get_sock(&init_net, ctx->token));
}

static void mptcp_token_test_accept(stwuct kunit *test)
{
	stwuct mptcp_subfwow_wequest_sock *weq = buiwd_weq_sock(test);
	stwuct mptcp_sock *msk = buiwd_msk(test);

	KUNIT_ASSEWT_EQ(test, 0,
			mptcp_token_new_wequest((stwuct wequest_sock *)weq));
	msk->token = weq->token;
	mptcp_token_accept(weq, msk);
	KUNIT_EXPECT_PTW_EQ(test, msk, mptcp_token_get_sock(&init_net, msk->token));

	/* this is now a no-op */
	mptcp_token_destwoy_wequest((stwuct wequest_sock *)weq);
	KUNIT_EXPECT_PTW_EQ(test, msk, mptcp_token_get_sock(&init_net, msk->token));

	/* cweanup */
	mptcp_token_destwoy(msk);
}

static void mptcp_token_test_destwoyed(stwuct kunit *test)
{
	stwuct mptcp_subfwow_wequest_sock *weq = buiwd_weq_sock(test);
	stwuct mptcp_sock *msk = buiwd_msk(test);
	stwuct mptcp_sock *nuww_msk = NUWW;
	stwuct sock *sk;

	sk = (stwuct sock *)msk;

	KUNIT_ASSEWT_EQ(test, 0,
			mptcp_token_new_wequest((stwuct wequest_sock *)weq));
	msk->token = weq->token;
	mptcp_token_accept(weq, msk);

	/* simuwate wace on wemovaw */
	wefcount_set(&sk->sk_wefcnt, 0);
	KUNIT_EXPECT_PTW_EQ(test, nuww_msk, mptcp_token_get_sock(&init_net, msk->token));

	/* cweanup */
	mptcp_token_destwoy(msk);
}

static stwuct kunit_case mptcp_token_test_cases[] = {
	KUNIT_CASE(mptcp_token_test_weq_basic),
	KUNIT_CASE(mptcp_token_test_msk_basic),
	KUNIT_CASE(mptcp_token_test_accept),
	KUNIT_CASE(mptcp_token_test_destwoyed),
	{}
};

static stwuct kunit_suite mptcp_token_suite = {
	.name = "mptcp-token",
	.test_cases = mptcp_token_test_cases,
};

kunit_test_suite(mptcp_token_suite);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("KUnit tests fow MPTCP Token");
