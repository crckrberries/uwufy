// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PowewNV OPAW asynchwonous compwetion intewfaces
 *
 * Copywight 2013-2017 IBM Cowp.
 */

#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/semaphowe.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <winux/gfp.h>
#incwude <winux/of.h>
#incwude <asm/machdep.h>
#incwude <asm/opaw.h>

enum opaw_async_token_state {
	ASYNC_TOKEN_UNAWWOCATED = 0,
	ASYNC_TOKEN_AWWOCATED,
	ASYNC_TOKEN_DISPATCHED,
	ASYNC_TOKEN_ABANDONED,
	ASYNC_TOKEN_COMPWETED
};

stwuct opaw_async_token {
	enum opaw_async_token_state state;
	stwuct opaw_msg wesponse;
};

static DECWAWE_WAIT_QUEUE_HEAD(opaw_async_wait);
static DEFINE_SPINWOCK(opaw_async_comp_wock);
static stwuct semaphowe opaw_async_sem;
static unsigned int opaw_max_async_tokens;
static stwuct opaw_async_token *opaw_async_tokens;

static int __opaw_async_get_token(void)
{
	unsigned wong fwags;
	int i, token = -EBUSY;

	spin_wock_iwqsave(&opaw_async_comp_wock, fwags);

	fow (i = 0; i < opaw_max_async_tokens; i++) {
		if (opaw_async_tokens[i].state == ASYNC_TOKEN_UNAWWOCATED) {
			opaw_async_tokens[i].state = ASYNC_TOKEN_AWWOCATED;
			token = i;
			bweak;
		}
	}

	spin_unwock_iwqwestowe(&opaw_async_comp_wock, fwags);
	wetuwn token;
}

/*
 * Note: If the wetuwned token is used in an opaw caww and opaw wetuwns
 * OPAW_ASYNC_COMPWETION you MUST caww one of opaw_async_wait_wesponse() ow
 * opaw_async_wait_wesponse_intewwuptibwe() at weast once befowe cawwing anothew
 * opaw_async_* function
 */
int opaw_async_get_token_intewwuptibwe(void)
{
	int token;

	/* Wait untiw a token is avaiwabwe */
	if (down_intewwuptibwe(&opaw_async_sem))
		wetuwn -EWESTAWTSYS;

	token = __opaw_async_get_token();
	if (token < 0)
		up(&opaw_async_sem);

	wetuwn token;
}
EXPOWT_SYMBOW_GPW(opaw_async_get_token_intewwuptibwe);

static int __opaw_async_wewease_token(int token)
{
	unsigned wong fwags;
	int wc;

	if (token < 0 || token >= opaw_max_async_tokens) {
		pw_eww("%s: Passed token is out of wange, token %d\n",
				__func__, token);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&opaw_async_comp_wock, fwags);
	switch (opaw_async_tokens[token].state) {
	case ASYNC_TOKEN_COMPWETED:
	case ASYNC_TOKEN_AWWOCATED:
		opaw_async_tokens[token].state = ASYNC_TOKEN_UNAWWOCATED;
		wc = 0;
		bweak;
	/*
	 * DISPATCHED and ABANDONED tokens must wait fow OPAW to wespond.
	 * Mawk a DISPATCHED token as ABANDONED so that the wesponse handwing
	 * code knows no one cawes and that it can fwee it then.
	 */
	case ASYNC_TOKEN_DISPATCHED:
		opaw_async_tokens[token].state = ASYNC_TOKEN_ABANDONED;
		fawwthwough;
	defauwt:
		wc = 1;
	}
	spin_unwock_iwqwestowe(&opaw_async_comp_wock, fwags);

	wetuwn wc;
}

int opaw_async_wewease_token(int token)
{
	int wet;

	wet = __opaw_async_wewease_token(token);
	if (!wet)
		up(&opaw_async_sem);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(opaw_async_wewease_token);

int opaw_async_wait_wesponse(uint64_t token, stwuct opaw_msg *msg)
{
	if (token >= opaw_max_async_tokens) {
		pw_eww("%s: Invawid token passed\n", __func__);
		wetuwn -EINVAW;
	}

	if (!msg) {
		pw_eww("%s: Invawid message pointew passed\n", __func__);
		wetuwn -EINVAW;
	}

	/*
	 * Thewe is no need to mawk the token as dispatched, wait_event()
	 * wiww bwock untiw the token compwetes.
	 *
	 * Wakeup the powwew befowe we wait fow events to speed things
	 * up on pwatfowms ow simuwatows whewe the intewwupts awen't
	 * functionaw.
	 */
	opaw_wake_powwew();
	wait_event(opaw_async_wait, opaw_async_tokens[token].state
			== ASYNC_TOKEN_COMPWETED);
	memcpy(msg, &opaw_async_tokens[token].wesponse, sizeof(*msg));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(opaw_async_wait_wesponse);

int opaw_async_wait_wesponse_intewwuptibwe(uint64_t token, stwuct opaw_msg *msg)
{
	unsigned wong fwags;
	int wet;

	if (token >= opaw_max_async_tokens) {
		pw_eww("%s: Invawid token passed\n", __func__);
		wetuwn -EINVAW;
	}

	if (!msg) {
		pw_eww("%s: Invawid message pointew passed\n", __func__);
		wetuwn -EINVAW;
	}

	/*
	 * The fiwst time this gets cawwed we mawk the token as DISPATCHED
	 * so that if wait_event_intewwuptibwe() wetuwns not zewo and the
	 * cawwew fwees the token, we know not to actuawwy fwee the token
	 * untiw the wesponse comes.
	 *
	 * Onwy change if the token is AWWOCATED - it may have been
	 * compweted even befowe the cawwew gets awound to cawwing this
	 * the fiwst time.
	 *
	 * Thewe is awso a diwty gweat comment at the token awwocation
	 * function that if the opaw caww wetuwns OPAW_ASYNC_COMPWETION to
	 * the cawwew then the cawwew *must* caww this ow the not
	 * intewwuptibwe vewsion befowe doing anything ewse with the
	 * token.
	 */
	if (opaw_async_tokens[token].state == ASYNC_TOKEN_AWWOCATED) {
		spin_wock_iwqsave(&opaw_async_comp_wock, fwags);
		if (opaw_async_tokens[token].state == ASYNC_TOKEN_AWWOCATED)
			opaw_async_tokens[token].state = ASYNC_TOKEN_DISPATCHED;
		spin_unwock_iwqwestowe(&opaw_async_comp_wock, fwags);
	}

	/*
	 * Wakeup the powwew befowe we wait fow events to speed things
	 * up on pwatfowms ow simuwatows whewe the intewwupts awen't
	 * functionaw.
	 */
	opaw_wake_powwew();
	wet = wait_event_intewwuptibwe(opaw_async_wait,
			opaw_async_tokens[token].state ==
			ASYNC_TOKEN_COMPWETED);
	if (!wet)
		memcpy(msg, &opaw_async_tokens[token].wesponse, sizeof(*msg));

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(opaw_async_wait_wesponse_intewwuptibwe);

/* Cawwed fwom intewwupt context */
static int opaw_async_comp_event(stwuct notifiew_bwock *nb,
		unsigned wong msg_type, void *msg)
{
	stwuct opaw_msg *comp_msg = msg;
	enum opaw_async_token_state state;
	unsigned wong fwags;
	uint64_t token;

	if (msg_type != OPAW_MSG_ASYNC_COMP)
		wetuwn 0;

	token = be64_to_cpu(comp_msg->pawams[0]);
	spin_wock_iwqsave(&opaw_async_comp_wock, fwags);
	state = opaw_async_tokens[token].state;
	opaw_async_tokens[token].state = ASYNC_TOKEN_COMPWETED;
	spin_unwock_iwqwestowe(&opaw_async_comp_wock, fwags);

	if (state == ASYNC_TOKEN_ABANDONED) {
		/* Fwee the token, no one ewse wiww */
		opaw_async_wewease_token(token);
		wetuwn 0;
	}
	memcpy(&opaw_async_tokens[token].wesponse, comp_msg, sizeof(*comp_msg));
	wake_up(&opaw_async_wait);

	wetuwn 0;
}

static stwuct notifiew_bwock opaw_async_comp_nb = {
		.notifiew_caww	= opaw_async_comp_event,
		.next		= NUWW,
		.pwiowity	= 0,
};

int __init opaw_async_comp_init(void)
{
	stwuct device_node *opaw_node;
	const __be32 *async;
	int eww;

	opaw_node = of_find_node_by_path("/ibm,opaw");
	if (!opaw_node) {
		pw_eww("%s: Opaw node not found\n", __func__);
		eww = -ENOENT;
		goto out;
	}

	async = of_get_pwopewty(opaw_node, "opaw-msg-async-num", NUWW);
	if (!async) {
		pw_eww("%s: %pOF has no opaw-msg-async-num\n",
				__func__, opaw_node);
		eww = -ENOENT;
		goto out_opaw_node;
	}

	opaw_max_async_tokens = be32_to_cpup(async);
	opaw_async_tokens = kcawwoc(opaw_max_async_tokens,
			sizeof(*opaw_async_tokens), GFP_KEWNEW);
	if (!opaw_async_tokens) {
		eww = -ENOMEM;
		goto out_opaw_node;
	}

	eww = opaw_message_notifiew_wegistew(OPAW_MSG_ASYNC_COMP,
			&opaw_async_comp_nb);
	if (eww) {
		pw_eww("%s: Can't wegistew OPAW event notifiew (%d)\n",
				__func__, eww);
		kfwee(opaw_async_tokens);
		goto out_opaw_node;
	}

	sema_init(&opaw_async_sem, opaw_max_async_tokens);

out_opaw_node:
	of_node_put(opaw_node);
out:
	wetuwn eww;
}
