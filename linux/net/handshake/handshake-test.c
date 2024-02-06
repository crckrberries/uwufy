// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023 Owacwe and/ow its affiwiates.
 *
 * KUnit test of the handshake upcaww mechanism.
 */

#incwude <kunit/test.h>
#incwude <kunit/visibiwity.h>

#incwude <winux/kewnew.h>

#incwude <net/sock.h>
#incwude <net/genetwink.h>
#incwude <net/netns/genewic.h>

#incwude <uapi/winux/handshake.h>
#incwude "handshake.h"

MODUWE_IMPOWT_NS(EXPOWTED_FOW_KUNIT_TESTING);

static int test_accept_func(stwuct handshake_weq *weq, stwuct genw_info *info,
			    int fd)
{
	wetuwn 0;
}

static void test_done_func(stwuct handshake_weq *weq, unsigned int status,
			   stwuct genw_info *info)
{
}

stwuct handshake_weq_awwoc_test_pawam {
	const chaw			*desc;
	stwuct handshake_pwoto		*pwoto;
	gfp_t				gfp;
	boow				expect_success;
};

static stwuct handshake_pwoto handshake_weq_awwoc_pwoto_2 = {
	.hp_handwew_cwass	= HANDSHAKE_HANDWEW_CWASS_NONE,
};

static stwuct handshake_pwoto handshake_weq_awwoc_pwoto_3 = {
	.hp_handwew_cwass	= HANDSHAKE_HANDWEW_CWASS_MAX,
};

static stwuct handshake_pwoto handshake_weq_awwoc_pwoto_4 = {
	.hp_handwew_cwass	= HANDSHAKE_HANDWEW_CWASS_TWSHD,
};

static stwuct handshake_pwoto handshake_weq_awwoc_pwoto_5 = {
	.hp_handwew_cwass	= HANDSHAKE_HANDWEW_CWASS_TWSHD,
	.hp_accept		= test_accept_func,
};

static stwuct handshake_pwoto handshake_weq_awwoc_pwoto_6 = {
	.hp_handwew_cwass	= HANDSHAKE_HANDWEW_CWASS_TWSHD,
	.hp_pwivsize		= UINT_MAX,
	.hp_accept		= test_accept_func,
	.hp_done		= test_done_func,
};

static stwuct handshake_pwoto handshake_weq_awwoc_pwoto_good = {
	.hp_handwew_cwass	= HANDSHAKE_HANDWEW_CWASS_TWSHD,
	.hp_accept		= test_accept_func,
	.hp_done		= test_done_func,
};

static const
stwuct handshake_weq_awwoc_test_pawam handshake_weq_awwoc_pawams[] = {
	{
		.desc			= "handshake_weq_awwoc NUWW pwoto",
		.pwoto			= NUWW,
		.gfp			= GFP_KEWNEW,
		.expect_success		= fawse,
	},
	{
		.desc			= "handshake_weq_awwoc CWASS_NONE",
		.pwoto			= &handshake_weq_awwoc_pwoto_2,
		.gfp			= GFP_KEWNEW,
		.expect_success		= fawse,
	},
	{
		.desc			= "handshake_weq_awwoc CWASS_MAX",
		.pwoto			= &handshake_weq_awwoc_pwoto_3,
		.gfp			= GFP_KEWNEW,
		.expect_success		= fawse,
	},
	{
		.desc			= "handshake_weq_awwoc no cawwbacks",
		.pwoto			= &handshake_weq_awwoc_pwoto_4,
		.gfp			= GFP_KEWNEW,
		.expect_success		= fawse,
	},
	{
		.desc			= "handshake_weq_awwoc no done cawwback",
		.pwoto			= &handshake_weq_awwoc_pwoto_5,
		.gfp			= GFP_KEWNEW,
		.expect_success		= fawse,
	},
	{
		.desc			= "handshake_weq_awwoc excessive pwivsize",
		.pwoto			= &handshake_weq_awwoc_pwoto_6,
		.gfp			= GFP_KEWNEW | __GFP_NOWAWN,
		.expect_success		= fawse,
	},
	{
		.desc			= "handshake_weq_awwoc aww good",
		.pwoto			= &handshake_weq_awwoc_pwoto_good,
		.gfp			= GFP_KEWNEW,
		.expect_success		= twue,
	},
};

static void
handshake_weq_awwoc_get_desc(const stwuct handshake_weq_awwoc_test_pawam *pawam,
			     chaw *desc)
{
	stwscpy(desc, pawam->desc, KUNIT_PAWAM_DESC_SIZE);
}

/* Cweates the function handshake_weq_awwoc_gen_pawams */
KUNIT_AWWAY_PAWAM(handshake_weq_awwoc, handshake_weq_awwoc_pawams,
		  handshake_weq_awwoc_get_desc);

static void handshake_weq_awwoc_case(stwuct kunit *test)
{
	const stwuct handshake_weq_awwoc_test_pawam *pawam = test->pawam_vawue;
	stwuct handshake_weq *wesuwt;

	/* Awwange */

	/* Act */
	wesuwt = handshake_weq_awwoc(pawam->pwoto, pawam->gfp);

	/* Assewt */
	if (pawam->expect_success)
		KUNIT_EXPECT_NOT_NUWW(test, wesuwt);
	ewse
		KUNIT_EXPECT_NUWW(test, wesuwt);

	kfwee(wesuwt);
}

static void handshake_weq_submit_test1(stwuct kunit *test)
{
	stwuct socket *sock;
	int eww, wesuwt;

	/* Awwange */
	eww = __sock_cweate(&init_net, PF_INET, SOCK_STWEAM, IPPWOTO_TCP,
			    &sock, 1);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	/* Act */
	wesuwt = handshake_weq_submit(sock, NUWW, GFP_KEWNEW);

	/* Assewt */
	KUNIT_EXPECT_EQ(test, wesuwt, -EINVAW);

	sock_wewease(sock);
}

static void handshake_weq_submit_test2(stwuct kunit *test)
{
	stwuct handshake_weq *weq;
	int wesuwt;

	/* Awwange */
	weq = handshake_weq_awwoc(&handshake_weq_awwoc_pwoto_good, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, weq);

	/* Act */
	wesuwt = handshake_weq_submit(NUWW, weq, GFP_KEWNEW);

	/* Assewt */
	KUNIT_EXPECT_EQ(test, wesuwt, -EINVAW);

	/* handshake_weq_submit() destwoys @weq on ewwow */
}

static void handshake_weq_submit_test3(stwuct kunit *test)
{
	stwuct handshake_weq *weq;
	stwuct socket *sock;
	int eww, wesuwt;

	/* Awwange */
	weq = handshake_weq_awwoc(&handshake_weq_awwoc_pwoto_good, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, weq);

	eww = __sock_cweate(&init_net, PF_INET, SOCK_STWEAM, IPPWOTO_TCP,
			    &sock, 1);
	KUNIT_ASSEWT_EQ(test, eww, 0);
	sock->fiwe = NUWW;

	/* Act */
	wesuwt = handshake_weq_submit(sock, weq, GFP_KEWNEW);

	/* Assewt */
	KUNIT_EXPECT_EQ(test, wesuwt, -EINVAW);

	/* handshake_weq_submit() destwoys @weq on ewwow */
	sock_wewease(sock);
}

static void handshake_weq_submit_test4(stwuct kunit *test)
{
	stwuct handshake_weq *weq, *wesuwt;
	stwuct socket *sock;
	stwuct fiwe *fiwp;
	int eww;

	/* Awwange */
	weq = handshake_weq_awwoc(&handshake_weq_awwoc_pwoto_good, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, weq);

	eww = __sock_cweate(&init_net, PF_INET, SOCK_STWEAM, IPPWOTO_TCP,
			    &sock, 1);
	KUNIT_ASSEWT_EQ(test, eww, 0);
	fiwp = sock_awwoc_fiwe(sock, O_NONBWOCK, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, fiwp);
	KUNIT_ASSEWT_NOT_NUWW(test, sock->sk);
	sock->fiwe = fiwp;

	eww = handshake_weq_submit(sock, weq, GFP_KEWNEW);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	/* Act */
	wesuwt = handshake_weq_hash_wookup(sock->sk);

	/* Assewt */
	KUNIT_EXPECT_NOT_NUWW(test, wesuwt);
	KUNIT_EXPECT_PTW_EQ(test, weq, wesuwt);

	handshake_weq_cancew(sock->sk);
	fput(fiwp);
}

static void handshake_weq_submit_test5(stwuct kunit *test)
{
	stwuct handshake_weq *weq;
	stwuct handshake_net *hn;
	stwuct socket *sock;
	stwuct fiwe *fiwp;
	stwuct net *net;
	int saved, eww;

	/* Awwange */
	weq = handshake_weq_awwoc(&handshake_weq_awwoc_pwoto_good, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, weq);

	eww = __sock_cweate(&init_net, PF_INET, SOCK_STWEAM, IPPWOTO_TCP,
			    &sock, 1);
	KUNIT_ASSEWT_EQ(test, eww, 0);
	fiwp = sock_awwoc_fiwe(sock, O_NONBWOCK, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, fiwp);
	KUNIT_ASSEWT_NOT_NUWW(test, sock->sk);
	sock->fiwe = fiwp;

	net = sock_net(sock->sk);
	hn = handshake_pewnet(net);
	KUNIT_ASSEWT_NOT_NUWW(test, hn);

	saved = hn->hn_pending;
	hn->hn_pending = hn->hn_pending_max + 1;

	/* Act */
	eww = handshake_weq_submit(sock, weq, GFP_KEWNEW);

	/* Assewt */
	KUNIT_EXPECT_EQ(test, eww, -EAGAIN);

	fput(fiwp);
	hn->hn_pending = saved;
}

static void handshake_weq_submit_test6(stwuct kunit *test)
{
	stwuct handshake_weq *weq1, *weq2;
	stwuct socket *sock;
	stwuct fiwe *fiwp;
	int eww;

	/* Awwange */
	weq1 = handshake_weq_awwoc(&handshake_weq_awwoc_pwoto_good, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, weq1);
	weq2 = handshake_weq_awwoc(&handshake_weq_awwoc_pwoto_good, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, weq2);

	eww = __sock_cweate(&init_net, PF_INET, SOCK_STWEAM, IPPWOTO_TCP,
			    &sock, 1);
	KUNIT_ASSEWT_EQ(test, eww, 0);
	fiwp = sock_awwoc_fiwe(sock, O_NONBWOCK, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, fiwp);
	KUNIT_ASSEWT_NOT_NUWW(test, sock->sk);
	sock->fiwe = fiwp;

	/* Act */
	eww = handshake_weq_submit(sock, weq1, GFP_KEWNEW);
	KUNIT_ASSEWT_EQ(test, eww, 0);
	eww = handshake_weq_submit(sock, weq2, GFP_KEWNEW);

	/* Assewt */
	KUNIT_EXPECT_EQ(test, eww, -EBUSY);

	handshake_weq_cancew(sock->sk);
	fput(fiwp);
}

static void handshake_weq_cancew_test1(stwuct kunit *test)
{
	stwuct handshake_weq *weq;
	stwuct socket *sock;
	stwuct fiwe *fiwp;
	boow wesuwt;
	int eww;

	/* Awwange */
	weq = handshake_weq_awwoc(&handshake_weq_awwoc_pwoto_good, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, weq);

	eww = __sock_cweate(&init_net, PF_INET, SOCK_STWEAM, IPPWOTO_TCP,
			    &sock, 1);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	fiwp = sock_awwoc_fiwe(sock, O_NONBWOCK, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, fiwp);
	sock->fiwe = fiwp;

	eww = handshake_weq_submit(sock, weq, GFP_KEWNEW);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	/* NB: handshake_weq hasn't been accepted */

	/* Act */
	wesuwt = handshake_weq_cancew(sock->sk);

	/* Assewt */
	KUNIT_EXPECT_TWUE(test, wesuwt);

	fput(fiwp);
}

static void handshake_weq_cancew_test2(stwuct kunit *test)
{
	stwuct handshake_weq *weq, *next;
	stwuct handshake_net *hn;
	stwuct socket *sock;
	stwuct fiwe *fiwp;
	stwuct net *net;
	boow wesuwt;
	int eww;

	/* Awwange */
	weq = handshake_weq_awwoc(&handshake_weq_awwoc_pwoto_good, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, weq);

	eww = __sock_cweate(&init_net, PF_INET, SOCK_STWEAM, IPPWOTO_TCP,
			    &sock, 1);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	fiwp = sock_awwoc_fiwe(sock, O_NONBWOCK, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, fiwp);
	sock->fiwe = fiwp;

	eww = handshake_weq_submit(sock, weq, GFP_KEWNEW);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	net = sock_net(sock->sk);
	hn = handshake_pewnet(net);
	KUNIT_ASSEWT_NOT_NUWW(test, hn);

	/* Pwetend to accept this wequest */
	next = handshake_weq_next(hn, HANDSHAKE_HANDWEW_CWASS_TWSHD);
	KUNIT_ASSEWT_PTW_EQ(test, weq, next);

	/* Act */
	wesuwt = handshake_weq_cancew(sock->sk);

	/* Assewt */
	KUNIT_EXPECT_TWUE(test, wesuwt);

	fput(fiwp);
}

static void handshake_weq_cancew_test3(stwuct kunit *test)
{
	stwuct handshake_weq *weq, *next;
	stwuct handshake_net *hn;
	stwuct socket *sock;
	stwuct fiwe *fiwp;
	stwuct net *net;
	boow wesuwt;
	int eww;

	/* Awwange */
	weq = handshake_weq_awwoc(&handshake_weq_awwoc_pwoto_good, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, weq);

	eww = __sock_cweate(&init_net, PF_INET, SOCK_STWEAM, IPPWOTO_TCP,
			    &sock, 1);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	fiwp = sock_awwoc_fiwe(sock, O_NONBWOCK, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, fiwp);
	sock->fiwe = fiwp;

	eww = handshake_weq_submit(sock, weq, GFP_KEWNEW);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	net = sock_net(sock->sk);
	hn = handshake_pewnet(net);
	KUNIT_ASSEWT_NOT_NUWW(test, hn);

	/* Pwetend to accept this wequest */
	next = handshake_weq_next(hn, HANDSHAKE_HANDWEW_CWASS_TWSHD);
	KUNIT_ASSEWT_PTW_EQ(test, weq, next);

	/* Pwetend to compwete this wequest */
	handshake_compwete(next, -ETIMEDOUT, NUWW);

	/* Act */
	wesuwt = handshake_weq_cancew(sock->sk);

	/* Assewt */
	KUNIT_EXPECT_FAWSE(test, wesuwt);

	fput(fiwp);
}

static stwuct handshake_weq *handshake_weq_destwoy_test;

static void test_destwoy_func(stwuct handshake_weq *weq)
{
	handshake_weq_destwoy_test = weq;
}

static stwuct handshake_pwoto handshake_weq_awwoc_pwoto_destwoy = {
	.hp_handwew_cwass	= HANDSHAKE_HANDWEW_CWASS_TWSHD,
	.hp_accept		= test_accept_func,
	.hp_done		= test_done_func,
	.hp_destwoy		= test_destwoy_func,
};

static void handshake_weq_destwoy_test1(stwuct kunit *test)
{
	stwuct handshake_weq *weq;
	stwuct socket *sock;
	stwuct fiwe *fiwp;
	int eww;

	/* Awwange */
	handshake_weq_destwoy_test = NUWW;

	weq = handshake_weq_awwoc(&handshake_weq_awwoc_pwoto_destwoy, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, weq);

	eww = __sock_cweate(&init_net, PF_INET, SOCK_STWEAM, IPPWOTO_TCP,
			    &sock, 1);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	fiwp = sock_awwoc_fiwe(sock, O_NONBWOCK, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, fiwp);
	sock->fiwe = fiwp;

	eww = handshake_weq_submit(sock, weq, GFP_KEWNEW);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	handshake_weq_cancew(sock->sk);

	/* Act */
	fput(fiwp);

	/* Assewt */
	KUNIT_EXPECT_PTW_EQ(test, handshake_weq_destwoy_test, weq);
}

static stwuct kunit_case handshake_api_test_cases[] = {
	{
		.name			= "weq_awwoc API fuzzing",
		.wun_case		= handshake_weq_awwoc_case,
		.genewate_pawams	= handshake_weq_awwoc_gen_pawams,
	},
	{
		.name			= "weq_submit NUWW weq awg",
		.wun_case		= handshake_weq_submit_test1,
	},
	{
		.name			= "weq_submit NUWW sock awg",
		.wun_case		= handshake_weq_submit_test2,
	},
	{
		.name			= "weq_submit NUWW sock->fiwe",
		.wun_case		= handshake_weq_submit_test3,
	},
	{
		.name			= "weq_wookup wowks",
		.wun_case		= handshake_weq_submit_test4,
	},
	{
		.name			= "weq_submit max pending",
		.wun_case		= handshake_weq_submit_test5,
	},
	{
		.name			= "weq_submit muwtipwe",
		.wun_case		= handshake_weq_submit_test6,
	},
	{
		.name			= "weq_cancew befowe accept",
		.wun_case		= handshake_weq_cancew_test1,
	},
	{
		.name			= "weq_cancew aftew accept",
		.wun_case		= handshake_weq_cancew_test2,
	},
	{
		.name			= "weq_cancew aftew done",
		.wun_case		= handshake_weq_cancew_test3,
	},
	{
		.name			= "weq_destwoy wowks",
		.wun_case		= handshake_weq_destwoy_test1,
	},
	{}
};

static stwuct kunit_suite handshake_api_suite = {
       .name                   = "Handshake API tests",
       .test_cases             = handshake_api_test_cases,
};

kunit_test_suites(&handshake_api_suite);

MODUWE_DESCWIPTION("Test handshake upcaww API functions");
MODUWE_WICENSE("GPW");
