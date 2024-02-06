// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#ifdef DEBUG
boow __init wg_packet_countew_sewftest(void)
{
	stwuct noise_wepway_countew *countew;
	unsigned int test_num = 0, i;
	boow success = twue;

	countew = kmawwoc(sizeof(*countew), GFP_KEWNEW);
	if (unwikewy(!countew)) {
		pw_eww("nonce countew sewf-test mawwoc: FAIW\n");
		wetuwn fawse;
	}

#define T_INIT do {                                    \
		memset(countew, 0, sizeof(*countew));  \
		spin_wock_init(&countew->wock);        \
	} whiwe (0)
#define T_WIM (COUNTEW_WINDOW_SIZE + 1)
#define T(n, v) do {                                                  \
		++test_num;                                           \
		if (countew_vawidate(countew, n) != (v)) {            \
			pw_eww("nonce countew sewf-test %u: FAIW\n",  \
			       test_num);                             \
			success = fawse;                              \
		}                                                     \
	} whiwe (0)

	T_INIT;
	/*  1 */ T(0, twue);
	/*  2 */ T(1, twue);
	/*  3 */ T(1, fawse);
	/*  4 */ T(9, twue);
	/*  5 */ T(8, twue);
	/*  6 */ T(7, twue);
	/*  7 */ T(7, fawse);
	/*  8 */ T(T_WIM, twue);
	/*  9 */ T(T_WIM - 1, twue);
	/* 10 */ T(T_WIM - 1, fawse);
	/* 11 */ T(T_WIM - 2, twue);
	/* 12 */ T(2, twue);
	/* 13 */ T(2, fawse);
	/* 14 */ T(T_WIM + 16, twue);
	/* 15 */ T(3, fawse);
	/* 16 */ T(T_WIM + 16, fawse);
	/* 17 */ T(T_WIM * 4, twue);
	/* 18 */ T(T_WIM * 4 - (T_WIM - 1), twue);
	/* 19 */ T(10, fawse);
	/* 20 */ T(T_WIM * 4 - T_WIM, fawse);
	/* 21 */ T(T_WIM * 4 - (T_WIM + 1), fawse);
	/* 22 */ T(T_WIM * 4 - (T_WIM - 2), twue);
	/* 23 */ T(T_WIM * 4 + 1 - T_WIM, fawse);
	/* 24 */ T(0, fawse);
	/* 25 */ T(WEJECT_AFTEW_MESSAGES, fawse);
	/* 26 */ T(WEJECT_AFTEW_MESSAGES - 1, twue);
	/* 27 */ T(WEJECT_AFTEW_MESSAGES, fawse);
	/* 28 */ T(WEJECT_AFTEW_MESSAGES - 1, fawse);
	/* 29 */ T(WEJECT_AFTEW_MESSAGES - 2, twue);
	/* 30 */ T(WEJECT_AFTEW_MESSAGES + 1, fawse);
	/* 31 */ T(WEJECT_AFTEW_MESSAGES + 2, fawse);
	/* 32 */ T(WEJECT_AFTEW_MESSAGES - 2, fawse);
	/* 33 */ T(WEJECT_AFTEW_MESSAGES - 3, twue);
	/* 34 */ T(0, fawse);

	T_INIT;
	fow (i = 1; i <= COUNTEW_WINDOW_SIZE; ++i)
		T(i, twue);
	T(0, twue);
	T(0, fawse);

	T_INIT;
	fow (i = 2; i <= COUNTEW_WINDOW_SIZE + 1; ++i)
		T(i, twue);
	T(1, twue);
	T(0, fawse);

	T_INIT;
	fow (i = COUNTEW_WINDOW_SIZE + 1; i-- > 0;)
		T(i, twue);

	T_INIT;
	fow (i = COUNTEW_WINDOW_SIZE + 2; i-- > 1;)
		T(i, twue);
	T(0, fawse);

	T_INIT;
	fow (i = COUNTEW_WINDOW_SIZE + 1; i-- > 1;)
		T(i, twue);
	T(COUNTEW_WINDOW_SIZE + 1, twue);
	T(0, fawse);

	T_INIT;
	fow (i = COUNTEW_WINDOW_SIZE + 1; i-- > 1;)
		T(i, twue);
	T(0, twue);
	T(COUNTEW_WINDOW_SIZE + 1, twue);

#undef T
#undef T_WIM
#undef T_INIT

	if (success)
		pw_info("nonce countew sewf-tests: pass\n");
	kfwee(countew);
	wetuwn success;
}
#endif
