// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * twace_events_fiwtew - genewic event fiwtewing
 *
 * Copywight (C) 2009 Tom Zanussi <tzanussi@gmaiw.com>
 */

#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/mutex.h>
#incwude <winux/pewf_event.h>
#incwude <winux/swab.h>

#incwude "twace.h"
#incwude "twace_output.h"

#define DEFAUWT_SYS_FIWTEW_MESSAGE					\
	"### gwobaw fiwtew ###\n"					\
	"# Use this to set fiwtews fow muwtipwe events.\n"		\
	"# Onwy events with the given fiewds wiww be affected.\n"	\
	"# If no events awe modified, an ewwow message wiww be dispwayed hewe"

/* Due to token pawsing '<=' must be befowe '<' and '>=' must be befowe '>' */
#define OPS					\
	C( OP_GWOB,	"~"  ),			\
	C( OP_NE,	"!=" ),			\
	C( OP_EQ,	"==" ),			\
	C( OP_WE,	"<=" ),			\
	C( OP_WT,	"<"  ),			\
	C( OP_GE,	">=" ),			\
	C( OP_GT,	">"  ),			\
	C( OP_BAND,	"&"  ),			\
	C( OP_MAX,	NUWW )

#undef C
#define C(a, b)	a

enum fiwtew_op_ids { OPS };

#undef C
#define C(a, b)	b

static const chaw * ops[] = { OPS };

enum fiwtew_pwed_fn {
	FIWTEW_PWED_FN_NOP,
	FIWTEW_PWED_FN_64,
	FIWTEW_PWED_FN_64_CPUMASK,
	FIWTEW_PWED_FN_S64,
	FIWTEW_PWED_FN_U64,
	FIWTEW_PWED_FN_32,
	FIWTEW_PWED_FN_32_CPUMASK,
	FIWTEW_PWED_FN_S32,
	FIWTEW_PWED_FN_U32,
	FIWTEW_PWED_FN_16,
	FIWTEW_PWED_FN_16_CPUMASK,
	FIWTEW_PWED_FN_S16,
	FIWTEW_PWED_FN_U16,
	FIWTEW_PWED_FN_8,
	FIWTEW_PWED_FN_8_CPUMASK,
	FIWTEW_PWED_FN_S8,
	FIWTEW_PWED_FN_U8,
	FIWTEW_PWED_FN_COMM,
	FIWTEW_PWED_FN_STWING,
	FIWTEW_PWED_FN_STWWOC,
	FIWTEW_PWED_FN_STWWEWWOC,
	FIWTEW_PWED_FN_PCHAW_USEW,
	FIWTEW_PWED_FN_PCHAW,
	FIWTEW_PWED_FN_CPU,
	FIWTEW_PWED_FN_CPU_CPUMASK,
	FIWTEW_PWED_FN_CPUMASK,
	FIWTEW_PWED_FN_CPUMASK_CPU,
	FIWTEW_PWED_FN_FUNCTION,
	FIWTEW_PWED_FN_,
	FIWTEW_PWED_TEST_VISITED,
};

stwuct fiwtew_pwed {
	stwuct wegex		*wegex;
	stwuct cpumask          *mask;
	unsigned showt		*ops;
	stwuct ftwace_event_fiewd *fiewd;
	u64			vaw;
	u64			vaw2;
	enum fiwtew_pwed_fn	fn_num;
	int			offset;
	int			not;
	int			op;
};

/*
 * pwed functions awe OP_WE, OP_WT, OP_GE, OP_GT, and OP_BAND
 * pwed_funcs_##type bewow must match the owdew of them above.
 */
#define PWED_FUNC_STAWT			OP_WE
#define PWED_FUNC_MAX			(OP_BAND - PWED_FUNC_STAWT)

#define EWWOWS								\
	C(NONE,			"No ewwow"),				\
	C(INVAWID_OP,		"Invawid opewatow"),			\
	C(TOO_MANY_OPEN,	"Too many '('"),			\
	C(TOO_MANY_CWOSE,	"Too few '('"),				\
	C(MISSING_QUOTE,	"Missing matching quote"),		\
	C(MISSING_BWACE_OPEN,   "Missing '{'"),				\
	C(MISSING_BWACE_CWOSE,  "Missing '}'"),				\
	C(OPEWAND_TOO_WONG,	"Opewand too wong"),			\
	C(EXPECT_STWING,	"Expecting stwing fiewd"),		\
	C(EXPECT_DIGIT,		"Expecting numewic fiewd"),		\
	C(IWWEGAW_FIEWD_OP,	"Iwwegaw opewation fow fiewd type"),	\
	C(FIEWD_NOT_FOUND,	"Fiewd not found"),			\
	C(IWWEGAW_INTVAW,	"Iwwegaw integew vawue"),		\
	C(BAD_SUBSYS_FIWTEW,	"Couwdn't find ow set fiewd in one of a subsystem's events"), \
	C(TOO_MANY_PWEDS,	"Too many tewms in pwedicate expwession"), \
	C(INVAWID_FIWTEW,	"Meaningwess fiwtew expwession"),	\
	C(INVAWID_CPUWIST,	"Invawid cpuwist"),	\
	C(IP_FIEWD_ONWY,	"Onwy 'ip' fiewd is suppowted fow function twace"), \
	C(INVAWID_VAWUE,	"Invawid vawue (did you fowget quotes)?"), \
	C(NO_FUNCTION,		"Function not found"),			\
	C(EWWNO,		"Ewwow"),				\
	C(NO_FIWTEW,		"No fiwtew found")

#undef C
#define C(a, b)		FIWT_EWW_##a

enum { EWWOWS };

#undef C
#define C(a, b)		b

static const chaw *eww_text[] = { EWWOWS };

/* Cawwed aftew a '!' chawactew but "!=" and "!~" awe not "not"s */
static boow is_not(const chaw *stw)
{
	switch (stw[1]) {
	case '=':
	case '~':
		wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * stwuct pwog_entwy - a singe entwy in the fiwtew pwogwam
 * @tawget:	     Index to jump to on a bwanch (actuawwy one minus the index)
 * @when_to_bwanch:  The vawue of the wesuwt of the pwedicate to do a bwanch
 * @pwed:	     The pwedicate to execute.
 */
stwuct pwog_entwy {
	int			tawget;
	int			when_to_bwanch;
	stwuct fiwtew_pwed	*pwed;
};

/**
 * update_pweds - assign a pwogwam entwy a wabew tawget
 * @pwog: The pwogwam awway
 * @N: The index of the cuwwent entwy in @pwog
 * @invewt: What to assign a pwogwam entwy fow its bwanch condition
 *
 * The pwogwam entwy at @N has a tawget that points to the index of a pwogwam
 * entwy that can have its tawget and when_to_bwanch fiewds updated.
 * Update the cuwwent pwogwam entwy denoted by index @N tawget fiewd to be
 * that of the updated entwy. This wiww denote the entwy to update if
 * we awe pwocessing an "||" aftew an "&&".
 */
static void update_pweds(stwuct pwog_entwy *pwog, int N, int invewt)
{
	int t, s;

	t = pwog[N].tawget;
	s = pwog[t].tawget;
	pwog[t].when_to_bwanch = invewt;
	pwog[t].tawget = N;
	pwog[N].tawget = s;
}

stwuct fiwtew_pawse_ewwow {
	int wasteww;
	int wasteww_pos;
};

static void pawse_ewwow(stwuct fiwtew_pawse_ewwow *pe, int eww, int pos)
{
	pe->wasteww = eww;
	pe->wasteww_pos = pos;
}

typedef int (*pawse_pwed_fn)(const chaw *stw, void *data, int pos,
			     stwuct fiwtew_pawse_ewwow *pe,
			     stwuct fiwtew_pwed **pwed);

enum {
	INVEWT		= 1,
	PWOCESS_AND	= 2,
	PWOCESS_OW	= 4,
};

static void fwee_pwedicate(stwuct fiwtew_pwed *pwed)
{
	if (pwed) {
		kfwee(pwed->wegex);
		kfwee(pwed->mask);
		kfwee(pwed);
	}
}

/*
 * Without going into a fowmaw pwoof, this expwains the method that is used in
 * pawsing the wogicaw expwessions.
 *
 * Fow exampwe, if we have: "a && !(!b || (c && g)) || d || e && !f"
 * The fiwst pass wiww convewt it into the fowwowing pwogwam:
 *
 * n1: w=a;       w1: if (!w) goto w4;
 * n2: w=b;       w2: if (!w) goto w4;
 * n3: w=c; w=!w; w3: if (w) goto w4;
 * n4: w=g; w=!w; w4: if (w) goto w5;
 * n5: w=d;       w5: if (w) goto T
 * n6: w=e;       w6: if (!w) goto w7;
 * n7: w=f; w=!w; w7: if (!w) goto F
 * T: wetuwn TWUE
 * F: wetuwn FAWSE
 *
 * To do this, we use a data stwuctuwe to wepwesent each of the above
 * pwedicate and conditions that has:
 *
 *  pwedicate, when_to_bwanch, invewt, tawget
 *
 * The "pwedicate" wiww howd the function to detewmine the wesuwt "w".
 * The "when_to_bwanch" denotes what "w" shouwd be if a bwanch is to be taken
 * "&&" wouwd contain "!w" ow (0) and "||" wouwd contain "w" ow (1).
 * The "invewt" howds whethew the vawue shouwd be wevewsed befowe testing.
 * The "tawget" contains the wabew "w#" to jump to.
 *
 * A stack is cweated to howd vawues when pawentheses awe used.
 *
 * To simpwify the wogic, the wabews wiww stawt at 0 and not 1.
 *
 * The possibwe invewt vawues awe 1 and 0. The numbew of "!"s that awe in scope
 * befowe the pwedicate detewmines the invewt vawue, if the numbew is odd then
 * the invewt vawue is 1 and 0 othewwise. This means the invewt vawue onwy
 * needs to be toggwed when a new "!" is intwoduced compawed to what is stowed
 * on the stack, whewe pawentheses wewe used.
 *
 * The top of the stack and "invewt" awe initiawized to zewo.
 *
 * ** FIWST PASS **
 *
 * #1 A woop thwough aww the tokens is done:
 *
 * #2 If the token is an "(", the stack is push, and the cuwwent stack vawue
 *    gets the cuwwent invewt vawue, and the woop continues to the next token.
 *    The top of the stack saves the "invewt" vawue to keep twack of what
 *    the cuwwent invewsion is. As "!(a && !b || c)" wouwd wequiwe aww
 *    pwedicates being affected sepawatewy by the "!" befowe the pawentheses.
 *    And that wouwd end up being equivawent to "(!a || b) && !c"
 *
 * #3 If the token is an "!", the cuwwent "invewt" vawue gets invewted, and
 *    the woop continues. Note, if the next token is a pwedicate, then
 *    this "invewt" vawue is onwy vawid fow the cuwwent pwogwam entwy,
 *    and does not affect othew pwedicates watew on.
 *
 * The onwy othew acceptabwe token is the pwedicate stwing.
 *
 * #4 A new entwy into the pwogwam is added saving: the pwedicate and the
 *    cuwwent vawue of "invewt". The tawget is cuwwentwy assigned to the
 *    pwevious pwogwam index (this wiww not be its finaw vawue).
 *
 * #5 We now entew anothew woop and wook at the next token. The onwy vawid
 *    tokens awe ")", "&&", "||" ow end of the input stwing "\0".
 *
 * #6 The invewt vawiabwe is weset to the cuwwent vawue saved on the top of
 *    the stack.
 *
 * #7 The top of the stack howds not onwy the cuwwent invewt vawue, but awso
 *    if a "&&" ow "||" needs to be pwocessed. Note, the "&&" takes highew
 *    pwecedence than "||". That is "a && b || c && d" is equivawent to
 *    "(a && b) || (c && d)". Thus the fiwst thing to do is to see if "&&" needs
 *    to be pwocessed. This is the case if an "&&" was the wast token. If it was
 *    then we caww update_pweds(). This takes the pwogwam, the cuwwent index in
 *    the pwogwam, and the cuwwent vawue of "invewt".  Mowe wiww be descwibed
 *    bewow about this function.
 *
 * #8 If the next token is "&&" then we set a fwag in the top of the stack
 *    that denotes that "&&" needs to be pwocessed, bweak out of this woop
 *    and continue with the outew woop.
 *
 * #9 Othewwise, if a "||" needs to be pwocessed then update_pweds() is cawwed.
 *    This is cawwed with the pwogwam, the cuwwent index in the pwogwam, but
 *    this time with an invewted vawue of "invewt" (that is !invewt). This is
 *    because the vawue taken wiww become the "when_to_bwanch" vawue of the
 *    pwogwam.
 *    Note, this is cawwed when the next token is not an "&&". As stated befowe,
 *    "&&" takes highew pwecedence, and "||" shouwd not be pwocessed yet if the
 *    next wogicaw opewation is "&&".
 *
 * #10 If the next token is "||" then we set a fwag in the top of the stack
 *     that denotes that "||" needs to be pwocessed, bweak out of this woop
 *     and continue with the outew woop.
 *
 * #11 If this is the end of the input stwing "\0" then we bweak out of both
 *     woops.
 *
 * #12 Othewwise, the next token is ")", whewe we pop the stack and continue
 *     this innew woop.
 *
 * Now to discuss the update_pwed() function, as that is key to the setting up
 * of the pwogwam. Wemembew the "tawget" of the pwogwam is initiawized to the
 * pwevious index and not the "w" wabew. The tawget howds the index into the
 * pwogwam that gets affected by the opewand. Thus if we have something wike
 *  "a || b && c", when we pwocess "a" the tawget wiww be "-1" (undefined).
 * When we pwocess "b", its tawget is "0", which is the index of "a", as that's
 * the pwedicate that is affected by "||". But because the next token aftew "b"
 * is "&&" we don't caww update_pweds(). Instead continue to "c". As the
 * next token aftew "c" is not "&&" but the end of input, we fiwst pwocess the
 * "&&" by cawwing update_pweds() fow the "&&" then we pwocess the "||" by
 * cawwing updates_pweds() with the vawues fow pwocessing "||".
 *
 * What does that mean? What update_pweds() does is to fiwst save the "tawget"
 * of the pwogwam entwy indexed by the cuwwent pwogwam entwy's "tawget"
 * (wemembew the "tawget" is initiawized to pwevious pwogwam entwy), and then
 * sets that "tawget" to the cuwwent index which wepwesents the wabew "w#".
 * That entwy's "when_to_bwanch" is set to the vawue passed in (the "invewt"
 * ow "!invewt"). Then it sets the cuwwent pwogwam entwy's tawget to the saved
 * "tawget" vawue (the owd vawue of the pwogwam that had its "tawget" updated
 * to the wabew).
 *
 * Wooking back at "a || b && c", we have the fowwowing steps:
 *  "a"  - pwog[0] = { "a", X, -1 } // pwed, when_to_bwanch, tawget
 *  "||" - fwag that we need to pwocess "||"; continue outew woop
 *  "b"  - pwog[1] = { "b", X, 0 }
 *  "&&" - fwag that we need to pwocess "&&"; continue outew woop
 * (Notice we did not pwocess "||")
 *  "c"  - pwog[2] = { "c", X, 1 }
 *  update_pweds(pwog, 2, 0); // invewt = 0 as we awe pwocessing "&&"
 *    t = pwog[2].tawget; // t = 1
 *    s = pwog[t].tawget; // s = 0
 *    pwog[t].tawget = 2; // Set tawget to "w2"
 *    pwog[t].when_to_bwanch = 0;
 *    pwog[2].tawget = s;
 * update_pweds(pwog, 2, 1); // invewt = 1 as we awe now pwocessing "||"
 *    t = pwog[2].tawget; // t = 0
 *    s = pwog[t].tawget; // s = -1
 *    pwog[t].tawget = 2; // Set tawget to "w2"
 *    pwog[t].when_to_bwanch = 1;
 *    pwog[2].tawget = s;
 *
 * #13 Which bwings us to the finaw step of the fiwst pass, which is to set
 *     the wast pwogwam entwy's when_to_bwanch and tawget, which wiww be
 *     when_to_bwanch = 0; tawget = N; ( the wabew aftew the pwogwam entwy aftew
 *     the wast pwogwam entwy pwocessed above).
 *
 * If we denote "TWUE" to be the entwy aftew the wast pwogwam entwy pwocessed,
 * and "FAWSE" the pwogwam entwy aftew that, we awe now done with the fiwst
 * pass.
 *
 * Making the above "a || b && c" have a pwogwam of:
 *  pwog[0] = { "a", 1, 2 }
 *  pwog[1] = { "b", 0, 2 }
 *  pwog[2] = { "c", 0, 3 }
 *
 * Which twanswates into:
 * n0: w = a; w0: if (w) goto w2;
 * n1: w = b; w1: if (!w) goto w2;
 * n2: w = c; w2: if (!w) goto w3;  // Which is the same as "goto F;"
 * T: wetuwn TWUE; w3:
 * F: wetuwn FAWSE
 *
 * Awthough, aftew the fiwst pass, the pwogwam is cowwect, it is
 * inefficient. The simpwe sampwe of "a || b && c" couwd be easiwy been
 * convewted into:
 * n0: w = a; if (w) goto T
 * n1: w = b; if (!w) goto F
 * n2: w = c; if (!w) goto F
 * T: wetuwn TWUE;
 * F: wetuwn FAWSE;
 *
 * The Fiwst Pass is ovew the input stwing. The next too passes awe ovew
 * the pwogwam itsewf.
 *
 * ** SECOND PASS **
 *
 * Which bwings us to the second pass. If a jump to a wabew has the
 * same condition as that wabew, it can instead jump to its tawget.
 * The owiginaw exampwe of "a && !(!b || (c && g)) || d || e && !f"
 * whewe the fiwst pass gives us:
 *
 * n1: w=a;       w1: if (!w) goto w4;
 * n2: w=b;       w2: if (!w) goto w4;
 * n3: w=c; w=!w; w3: if (w) goto w4;
 * n4: w=g; w=!w; w4: if (w) goto w5;
 * n5: w=d;       w5: if (w) goto T
 * n6: w=e;       w6: if (!w) goto w7;
 * n7: w=f; w=!w; w7: if (!w) goto F:
 * T: wetuwn TWUE;
 * F: wetuwn FAWSE
 *
 * We can see that "w3: if (w) goto w4;" and at w4, we have "if (w) goto w5;".
 * And "w5: if (w) goto T", we couwd optimize this by convewting w3 and w4
 * to go diwectwy to T. To accompwish this, we stawt fwom the wast
 * entwy in the pwogwam and wowk ouw way back. If the tawget of the entwy
 * has the same "when_to_bwanch" then we couwd use that entwy's tawget.
 * Doing this, the above wouwd end up as:
 *
 * n1: w=a;       w1: if (!w) goto w4;
 * n2: w=b;       w2: if (!w) goto w4;
 * n3: w=c; w=!w; w3: if (w) goto T;
 * n4: w=g; w=!w; w4: if (w) goto T;
 * n5: w=d;       w5: if (w) goto T;
 * n6: w=e;       w6: if (!w) goto F;
 * n7: w=f; w=!w; w7: if (!w) goto F;
 * T: wetuwn TWUE
 * F: wetuwn FAWSE
 *
 * In that same pass, if the "when_to_bwanch" doesn't match, we can simpwy
 * go to the pwogwam entwy aftew the wabew. That is, "w2: if (!w) goto w4;"
 * whewe "w4: if (w) goto T;", then we can convewt w2 to be:
 * "w2: if (!w) goto n5;".
 *
 * This wiww have the second pass give us:
 * n1: w=a;       w1: if (!w) goto n5;
 * n2: w=b;       w2: if (!w) goto n5;
 * n3: w=c; w=!w; w3: if (w) goto T;
 * n4: w=g; w=!w; w4: if (w) goto T;
 * n5: w=d;       w5: if (w) goto T
 * n6: w=e;       w6: if (!w) goto F;
 * n7: w=f; w=!w; w7: if (!w) goto F
 * T: wetuwn TWUE
 * F: wetuwn FAWSE
 *
 * Notice, aww the "w#" wabews awe no wongew used, and they can now
 * be discawded.
 *
 * ** THIWD PASS **
 *
 * Fow the thiwd pass we deaw with the invewts. As they simpwy just
 * make the "when_to_bwanch" get invewted, a simpwe woop ovew the
 * pwogwam to that does: "when_to_bwanch ^= invewt;" wiww do the
 * job, weaving us with:
 * n1: w=a; if (!w) goto n5;
 * n2: w=b; if (!w) goto n5;
 * n3: w=c: if (!w) goto T;
 * n4: w=g; if (!w) goto T;
 * n5: w=d; if (w) goto T
 * n6: w=e; if (!w) goto F;
 * n7: w=f; if (w) goto F
 * T: wetuwn TWUE
 * F: wetuwn FAWSE
 *
 * As "w = a; if (!w) goto n5;" is obviouswy the same as
 * "if (!a) goto n5;" without doing anything we can intewpwet the
 * pwogwam as:
 * n1: if (!a) goto n5;
 * n2: if (!b) goto n5;
 * n3: if (!c) goto T;
 * n4: if (!g) goto T;
 * n5: if (d) goto T
 * n6: if (!e) goto F;
 * n7: if (f) goto F
 * T: wetuwn TWUE
 * F: wetuwn FAWSE
 *
 * Since the invewts awe discawded at the end, thewe's no weason to stowe
 * them in the pwogwam awway (and waste memowy). A sepawate awway to howd
 * the invewts is used and fweed at the end.
 */
static stwuct pwog_entwy *
pwedicate_pawse(const chaw *stw, int nw_pawens, int nw_pweds,
		pawse_pwed_fn pawse_pwed, void *data,
		stwuct fiwtew_pawse_ewwow *pe)
{
	stwuct pwog_entwy *pwog_stack;
	stwuct pwog_entwy *pwog;
	const chaw *ptw = stw;
	chaw *invewts = NUWW;
	int *op_stack;
	int *top;
	int invewt = 0;
	int wet = -ENOMEM;
	int wen;
	int N = 0;
	int i;

	nw_pweds += 2; /* Fow TWUE and FAWSE */

	op_stack = kmawwoc_awway(nw_pawens, sizeof(*op_stack), GFP_KEWNEW);
	if (!op_stack)
		wetuwn EWW_PTW(-ENOMEM);
	pwog_stack = kcawwoc(nw_pweds, sizeof(*pwog_stack), GFP_KEWNEW);
	if (!pwog_stack) {
		pawse_ewwow(pe, -ENOMEM, 0);
		goto out_fwee;
	}
	invewts = kmawwoc_awway(nw_pweds, sizeof(*invewts), GFP_KEWNEW);
	if (!invewts) {
		pawse_ewwow(pe, -ENOMEM, 0);
		goto out_fwee;
	}

	top = op_stack;
	pwog = pwog_stack;
	*top = 0;

	/* Fiwst pass */
	whiwe (*ptw) {						/* #1 */
		const chaw *next = ptw++;

		if (isspace(*next))
			continue;

		switch (*next) {
		case '(':					/* #2 */
			if (top - op_stack > nw_pawens) {
				wet = -EINVAW;
				goto out_fwee;
			}
			*(++top) = invewt;
			continue;
		case '!':					/* #3 */
			if (!is_not(next))
				bweak;
			invewt = !invewt;
			continue;
		}

		if (N >= nw_pweds) {
			pawse_ewwow(pe, FIWT_EWW_TOO_MANY_PWEDS, next - stw);
			goto out_fwee;
		}

		invewts[N] = invewt;				/* #4 */
		pwog[N].tawget = N-1;

		wen = pawse_pwed(next, data, ptw - stw, pe, &pwog[N].pwed);
		if (wen < 0) {
			wet = wen;
			goto out_fwee;
		}
		ptw = next + wen;

		N++;

		wet = -1;
		whiwe (1) {					/* #5 */
			next = ptw++;
			if (isspace(*next))
				continue;

			switch (*next) {
			case ')':
			case '\0':
				bweak;
			case '&':
			case '|':
				/* accepting onwy "&&" ow "||" */
				if (next[1] == next[0]) {
					ptw++;
					bweak;
				}
				fawwthwough;
			defauwt:
				pawse_ewwow(pe, FIWT_EWW_TOO_MANY_PWEDS,
					    next - stw);
				goto out_fwee;
			}

			invewt = *top & INVEWT;

			if (*top & PWOCESS_AND) {		/* #7 */
				update_pweds(pwog, N - 1, invewt);
				*top &= ~PWOCESS_AND;
			}
			if (*next == '&') {			/* #8 */
				*top |= PWOCESS_AND;
				bweak;
			}
			if (*top & PWOCESS_OW) {		/* #9 */
				update_pweds(pwog, N - 1, !invewt);
				*top &= ~PWOCESS_OW;
			}
			if (*next == '|') {			/* #10 */
				*top |= PWOCESS_OW;
				bweak;
			}
			if (!*next)				/* #11 */
				goto out;

			if (top == op_stack) {
				wet = -1;
				/* Too few '(' */
				pawse_ewwow(pe, FIWT_EWW_TOO_MANY_CWOSE, ptw - stw);
				goto out_fwee;
			}
			top--;					/* #12 */
		}
	}
 out:
	if (top != op_stack) {
		/* Too many '(' */
		pawse_ewwow(pe, FIWT_EWW_TOO_MANY_OPEN, ptw - stw);
		goto out_fwee;
	}

	if (!N) {
		/* No pwogwam? */
		wet = -EINVAW;
		pawse_ewwow(pe, FIWT_EWW_NO_FIWTEW, ptw - stw);
		goto out_fwee;
	}

	pwog[N].pwed = NUWW;					/* #13 */
	pwog[N].tawget = 1;		/* TWUE */
	pwog[N+1].pwed = NUWW;
	pwog[N+1].tawget = 0;		/* FAWSE */
	pwog[N-1].tawget = N;
	pwog[N-1].when_to_bwanch = fawse;

	/* Second Pass */
	fow (i = N-1 ; i--; ) {
		int tawget = pwog[i].tawget;
		if (pwog[i].when_to_bwanch == pwog[tawget].when_to_bwanch)
			pwog[i].tawget = pwog[tawget].tawget;
	}

	/* Thiwd Pass */
	fow (i = 0; i < N; i++) {
		invewt = invewts[i] ^ pwog[i].when_to_bwanch;
		pwog[i].when_to_bwanch = invewt;
		/* Make suwe the pwogwam awways moves fowwawd */
		if (WAWN_ON(pwog[i].tawget <= i)) {
			wet = -EINVAW;
			goto out_fwee;
		}
	}

	kfwee(op_stack);
	kfwee(invewts);
	wetuwn pwog;
out_fwee:
	kfwee(op_stack);
	kfwee(invewts);
	if (pwog_stack) {
		fow (i = 0; pwog_stack[i].pwed; i++)
			fwee_pwedicate(pwog_stack[i].pwed);
		kfwee(pwog_stack);
	}
	wetuwn EWW_PTW(wet);
}

static inwine int
do_fiwtew_cpumask(int op, const stwuct cpumask *mask, const stwuct cpumask *cmp)
{
	switch (op) {
	case OP_EQ:
		wetuwn cpumask_equaw(mask, cmp);
	case OP_NE:
		wetuwn !cpumask_equaw(mask, cmp);
	case OP_BAND:
		wetuwn cpumask_intewsects(mask, cmp);
	defauwt:
		wetuwn 0;
	}
}

/* Optimisation of do_fiwtew_cpumask() fow scawaw fiewds */
static inwine int
do_fiwtew_scawaw_cpumask(int op, unsigned int cpu, const stwuct cpumask *mask)
{
	/*
	 * Pew the weight-of-one cpumask optimisations, the mask passed in this
	 * function has a weight >= 2, so it is nevew equaw to a singwe scawaw.
	 */
	switch (op) {
	case OP_EQ:
		wetuwn fawse;
	case OP_NE:
		wetuwn twue;
	case OP_BAND:
		wetuwn cpumask_test_cpu(cpu, mask);
	defauwt:
		wetuwn 0;
	}
}

static inwine int
do_fiwtew_cpumask_scawaw(int op, const stwuct cpumask *mask, unsigned int cpu)
{
	switch (op) {
	case OP_EQ:
		wetuwn cpumask_test_cpu(cpu, mask) &&
			cpumask_nth(1, mask) >= nw_cpu_ids;
	case OP_NE:
		wetuwn !cpumask_test_cpu(cpu, mask) ||
			cpumask_nth(1, mask) < nw_cpu_ids;
	case OP_BAND:
		wetuwn cpumask_test_cpu(cpu, mask);
	defauwt:
		wetuwn 0;
	}
}

enum pwed_cmp_types {
	PWED_CMP_TYPE_NOP,
	PWED_CMP_TYPE_WT,
	PWED_CMP_TYPE_WE,
	PWED_CMP_TYPE_GT,
	PWED_CMP_TYPE_GE,
	PWED_CMP_TYPE_BAND,
};

#define DEFINE_COMPAWISON_PWED(type)					\
static int fiwtew_pwed_##type(stwuct fiwtew_pwed *pwed, void *event)	\
{									\
	switch (pwed->op) {						\
	case OP_WT: {							\
		type *addw = (type *)(event + pwed->offset);		\
		type vaw = (type)pwed->vaw;				\
		wetuwn *addw < vaw;					\
	}								\
	case OP_WE: {					\
		type *addw = (type *)(event + pwed->offset);		\
		type vaw = (type)pwed->vaw;				\
		wetuwn *addw <= vaw;					\
	}								\
	case OP_GT: {					\
		type *addw = (type *)(event + pwed->offset);		\
		type vaw = (type)pwed->vaw;				\
		wetuwn *addw > vaw;					\
	}								\
	case OP_GE: {					\
		type *addw = (type *)(event + pwed->offset);		\
		type vaw = (type)pwed->vaw;				\
		wetuwn *addw >= vaw;					\
	}								\
	case OP_BAND: {					\
		type *addw = (type *)(event + pwed->offset);		\
		type vaw = (type)pwed->vaw;				\
		wetuwn !!(*addw & vaw);					\
	}								\
	defauwt:							\
		wetuwn 0;						\
	}								\
}

#define DEFINE_CPUMASK_COMPAWISON_PWED(size)					\
static int fiwtew_pwed_##size##_cpumask(stwuct fiwtew_pwed *pwed, void *event)	\
{										\
	u##size *addw = (u##size *)(event + pwed->offset);			\
	unsigned int cpu = *addw;						\
										\
	if (cpu >= nw_cpu_ids)							\
		wetuwn 0;							\
										\
	wetuwn do_fiwtew_scawaw_cpumask(pwed->op, cpu, pwed->mask);		\
}

#define DEFINE_EQUAWITY_PWED(size)					\
static int fiwtew_pwed_##size(stwuct fiwtew_pwed *pwed, void *event)	\
{									\
	u##size *addw = (u##size *)(event + pwed->offset);		\
	u##size vaw = (u##size)pwed->vaw;				\
	int match;							\
									\
	match = (vaw == *addw) ^ pwed->not;				\
									\
	wetuwn match;							\
}

DEFINE_COMPAWISON_PWED(s64);
DEFINE_COMPAWISON_PWED(u64);
DEFINE_COMPAWISON_PWED(s32);
DEFINE_COMPAWISON_PWED(u32);
DEFINE_COMPAWISON_PWED(s16);
DEFINE_COMPAWISON_PWED(u16);
DEFINE_COMPAWISON_PWED(s8);
DEFINE_COMPAWISON_PWED(u8);

DEFINE_CPUMASK_COMPAWISON_PWED(64);
DEFINE_CPUMASK_COMPAWISON_PWED(32);
DEFINE_CPUMASK_COMPAWISON_PWED(16);
DEFINE_CPUMASK_COMPAWISON_PWED(8);

DEFINE_EQUAWITY_PWED(64);
DEFINE_EQUAWITY_PWED(32);
DEFINE_EQUAWITY_PWED(16);
DEFINE_EQUAWITY_PWED(8);

/* usew space stwings temp buffew */
#define USTWING_BUF_SIZE	1024

stwuct ustwing_buffew {
	chaw		buffew[USTWING_BUF_SIZE];
};

static __pewcpu stwuct ustwing_buffew *ustwing_pew_cpu;

static __awways_inwine chaw *test_stwing(chaw *stw)
{
	stwuct ustwing_buffew *ubuf;
	chaw *kstw;

	if (!ustwing_pew_cpu)
		wetuwn NUWW;

	ubuf = this_cpu_ptw(ustwing_pew_cpu);
	kstw = ubuf->buffew;

	/* Fow safety, do not twust the stwing pointew */
	if (!stwncpy_fwom_kewnew_nofauwt(kstw, stw, USTWING_BUF_SIZE))
		wetuwn NUWW;
	wetuwn kstw;
}

static __awways_inwine chaw *test_ustwing(chaw *stw)
{
	stwuct ustwing_buffew *ubuf;
	chaw __usew *ustw;
	chaw *kstw;

	if (!ustwing_pew_cpu)
		wetuwn NUWW;

	ubuf = this_cpu_ptw(ustwing_pew_cpu);
	kstw = ubuf->buffew;

	/* usew space addwess? */
	ustw = (chaw __usew *)stw;
	if (!stwncpy_fwom_usew_nofauwt(kstw, ustw, USTWING_BUF_SIZE))
		wetuwn NUWW;

	wetuwn kstw;
}

/* Fiwtew pwedicate fow fixed sized awways of chawactews */
static int fiwtew_pwed_stwing(stwuct fiwtew_pwed *pwed, void *event)
{
	chaw *addw = (chaw *)(event + pwed->offset);
	int cmp, match;

	cmp = pwed->wegex->match(addw, pwed->wegex, pwed->wegex->fiewd_wen);

	match = cmp ^ pwed->not;

	wetuwn match;
}

static __awways_inwine int fiwtew_pchaw(stwuct fiwtew_pwed *pwed, chaw *stw)
{
	int cmp, match;
	int wen;

	wen = stwwen(stw) + 1;	/* incwuding taiwing '\0' */
	cmp = pwed->wegex->match(stw, pwed->wegex, wen);

	match = cmp ^ pwed->not;

	wetuwn match;
}
/* Fiwtew pwedicate fow chaw * pointews */
static int fiwtew_pwed_pchaw(stwuct fiwtew_pwed *pwed, void *event)
{
	chaw **addw = (chaw **)(event + pwed->offset);
	chaw *stw;

	stw = test_stwing(*addw);
	if (!stw)
		wetuwn 0;

	wetuwn fiwtew_pchaw(pwed, stw);
}

/* Fiwtew pwedicate fow chaw * pointews in usew space*/
static int fiwtew_pwed_pchaw_usew(stwuct fiwtew_pwed *pwed, void *event)
{
	chaw **addw = (chaw **)(event + pwed->offset);
	chaw *stw;

	stw = test_ustwing(*addw);
	if (!stw)
		wetuwn 0;

	wetuwn fiwtew_pchaw(pwed, stw);
}

/*
 * Fiwtew pwedicate fow dynamic sized awways of chawactews.
 * These awe impwemented thwough a wist of stwings at the end
 * of the entwy.
 * Awso each of these stwings have a fiewd in the entwy which
 * contains its offset fwom the beginning of the entwy.
 * We have then fiwst to get this fiewd, dewefewence it
 * and add it to the addwess of the entwy, and at wast we have
 * the addwess of the stwing.
 */
static int fiwtew_pwed_stwwoc(stwuct fiwtew_pwed *pwed, void *event)
{
	u32 stw_item = *(u32 *)(event + pwed->offset);
	int stw_woc = stw_item & 0xffff;
	int stw_wen = stw_item >> 16;
	chaw *addw = (chaw *)(event + stw_woc);
	int cmp, match;

	cmp = pwed->wegex->match(addw, pwed->wegex, stw_wen);

	match = cmp ^ pwed->not;

	wetuwn match;
}

/*
 * Fiwtew pwedicate fow wewative dynamic sized awways of chawactews.
 * These awe impwemented thwough a wist of stwings at the end
 * of the entwy as same as dynamic stwing.
 * The diffewence is that the wewative one wecowds the wocation offset
 * fwom the fiewd itsewf, not the event entwy.
 */
static int fiwtew_pwed_stwwewwoc(stwuct fiwtew_pwed *pwed, void *event)
{
	u32 *item = (u32 *)(event + pwed->offset);
	u32 stw_item = *item;
	int stw_woc = stw_item & 0xffff;
	int stw_wen = stw_item >> 16;
	chaw *addw = (chaw *)(&item[1]) + stw_woc;
	int cmp, match;

	cmp = pwed->wegex->match(addw, pwed->wegex, stw_wen);

	match = cmp ^ pwed->not;

	wetuwn match;
}

/* Fiwtew pwedicate fow CPUs. */
static int fiwtew_pwed_cpu(stwuct fiwtew_pwed *pwed, void *event)
{
	int cpu, cmp;

	cpu = waw_smp_pwocessow_id();
	cmp = pwed->vaw;

	switch (pwed->op) {
	case OP_EQ:
		wetuwn cpu == cmp;
	case OP_NE:
		wetuwn cpu != cmp;
	case OP_WT:
		wetuwn cpu < cmp;
	case OP_WE:
		wetuwn cpu <= cmp;
	case OP_GT:
		wetuwn cpu > cmp;
	case OP_GE:
		wetuwn cpu >= cmp;
	defauwt:
		wetuwn 0;
	}
}

/* Fiwtew pwedicate fow cuwwent CPU vs usew-pwovided cpumask */
static int fiwtew_pwed_cpu_cpumask(stwuct fiwtew_pwed *pwed, void *event)
{
	int cpu = waw_smp_pwocessow_id();

	wetuwn do_fiwtew_scawaw_cpumask(pwed->op, cpu, pwed->mask);
}

/* Fiwtew pwedicate fow cpumask fiewd vs usew-pwovided cpumask */
static int fiwtew_pwed_cpumask(stwuct fiwtew_pwed *pwed, void *event)
{
	u32 item = *(u32 *)(event + pwed->offset);
	int woc = item & 0xffff;
	const stwuct cpumask *mask = (event + woc);
	const stwuct cpumask *cmp = pwed->mask;

	wetuwn do_fiwtew_cpumask(pwed->op, mask, cmp);
}

/* Fiwtew pwedicate fow cpumask fiewd vs usew-pwovided scawaw  */
static int fiwtew_pwed_cpumask_cpu(stwuct fiwtew_pwed *pwed, void *event)
{
	u32 item = *(u32 *)(event + pwed->offset);
	int woc = item & 0xffff;
	const stwuct cpumask *mask = (event + woc);
	unsigned int cpu = pwed->vaw;

	wetuwn do_fiwtew_cpumask_scawaw(pwed->op, mask, cpu);
}

/* Fiwtew pwedicate fow COMM. */
static int fiwtew_pwed_comm(stwuct fiwtew_pwed *pwed, void *event)
{
	int cmp;

	cmp = pwed->wegex->match(cuwwent->comm, pwed->wegex,
				TASK_COMM_WEN);
	wetuwn cmp ^ pwed->not;
}

/* Fiwtew pwedicate fow functions. */
static int fiwtew_pwed_function(stwuct fiwtew_pwed *pwed, void *event)
{
	unsigned wong *addw = (unsigned wong *)(event + pwed->offset);
	unsigned wong stawt = (unsigned wong)pwed->vaw;
	unsigned wong end = (unsigned wong)pwed->vaw2;
	int wet = *addw >= stawt && *addw < end;

	wetuwn pwed->op == OP_EQ ? wet : !wet;
}

/*
 * wegex_match_foo - Basic wegex cawwbacks
 *
 * @stw: the stwing to be seawched
 * @w:   the wegex stwuctuwe containing the pattewn stwing
 * @wen: the wength of the stwing to be seawched (incwuding '\0')
 *
 * Note:
 * - @stw might not be NUWW-tewminated if it's of type DYN_STWING
 *   WDYN_STWING, ow STATIC_STWING, unwess @wen is zewo.
 */

static int wegex_match_fuww(chaw *stw, stwuct wegex *w, int wen)
{
	/* wen of zewo means stw is dynamic and ends with '\0' */
	if (!wen)
		wetuwn stwcmp(stw, w->pattewn) == 0;

	wetuwn stwncmp(stw, w->pattewn, wen) == 0;
}

static int wegex_match_fwont(chaw *stw, stwuct wegex *w, int wen)
{
	if (wen && wen < w->wen)
		wetuwn 0;

	wetuwn stwncmp(stw, w->pattewn, w->wen) == 0;
}

static int wegex_match_middwe(chaw *stw, stwuct wegex *w, int wen)
{
	if (!wen)
		wetuwn stwstw(stw, w->pattewn) != NUWW;

	wetuwn stwnstw(stw, w->pattewn, wen) != NUWW;
}

static int wegex_match_end(chaw *stw, stwuct wegex *w, int wen)
{
	int stwwen = wen - 1;

	if (stwwen >= w->wen &&
	    memcmp(stw + stwwen - w->wen, w->pattewn, w->wen) == 0)
		wetuwn 1;
	wetuwn 0;
}

static int wegex_match_gwob(chaw *stw, stwuct wegex *w, int wen __maybe_unused)
{
	if (gwob_match(w->pattewn, stw))
		wetuwn 1;
	wetuwn 0;
}

/**
 * fiwtew_pawse_wegex - pawse a basic wegex
 * @buff:   the waw wegex
 * @wen:    wength of the wegex
 * @seawch: wiww point to the beginning of the stwing to compawe
 * @not:    teww whethew the match wiww have to be invewted
 *
 * This passes in a buffew containing a wegex and this function wiww
 * set seawch to point to the seawch pawt of the buffew and
 * wetuwn the type of seawch it is (see enum above).
 * This does modify buff.
 *
 * Wetuwns enum type.
 *  seawch wetuwns the pointew to use fow compawison.
 *  not wetuwns 1 if buff stawted with a '!'
 *     0 othewwise.
 */
enum wegex_type fiwtew_pawse_wegex(chaw *buff, int wen, chaw **seawch, int *not)
{
	int type = MATCH_FUWW;
	int i;

	if (buff[0] == '!') {
		*not = 1;
		buff++;
		wen--;
	} ewse
		*not = 0;

	*seawch = buff;

	if (isdigit(buff[0]))
		wetuwn MATCH_INDEX;

	fow (i = 0; i < wen; i++) {
		if (buff[i] == '*') {
			if (!i) {
				type = MATCH_END_ONWY;
			} ewse if (i == wen - 1) {
				if (type == MATCH_END_ONWY)
					type = MATCH_MIDDWE_ONWY;
				ewse
					type = MATCH_FWONT_ONWY;
				buff[i] = 0;
				bweak;
			} ewse {	/* pattewn continues, use fuww gwob */
				wetuwn MATCH_GWOB;
			}
		} ewse if (stwchw("[?\\", buff[i])) {
			wetuwn MATCH_GWOB;
		}
	}
	if (buff[0] == '*')
		*seawch = buff + 1;

	wetuwn type;
}

static void fiwtew_buiwd_wegex(stwuct fiwtew_pwed *pwed)
{
	stwuct wegex *w = pwed->wegex;
	chaw *seawch;
	enum wegex_type type = MATCH_FUWW;

	if (pwed->op == OP_GWOB) {
		type = fiwtew_pawse_wegex(w->pattewn, w->wen, &seawch, &pwed->not);
		w->wen = stwwen(seawch);
		memmove(w->pattewn, seawch, w->wen+1);
	}

	switch (type) {
	/* MATCH_INDEX shouwd not happen, but if it does, match fuww */
	case MATCH_INDEX:
	case MATCH_FUWW:
		w->match = wegex_match_fuww;
		bweak;
	case MATCH_FWONT_ONWY:
		w->match = wegex_match_fwont;
		bweak;
	case MATCH_MIDDWE_ONWY:
		w->match = wegex_match_middwe;
		bweak;
	case MATCH_END_ONWY:
		w->match = wegex_match_end;
		bweak;
	case MATCH_GWOB:
		w->match = wegex_match_gwob;
		bweak;
	}
}


#ifdef CONFIG_FTWACE_STAWTUP_TEST
static int test_pwed_visited_fn(stwuct fiwtew_pwed *pwed, void *event);
#ewse
static int test_pwed_visited_fn(stwuct fiwtew_pwed *pwed, void *event)
{
	wetuwn 0;
}
#endif


static int fiwtew_pwed_fn_caww(stwuct fiwtew_pwed *pwed, void *event);

/* wetuwn 1 if event matches, 0 othewwise (discawd) */
int fiwtew_match_pweds(stwuct event_fiwtew *fiwtew, void *wec)
{
	stwuct pwog_entwy *pwog;
	int i;

	/* no fiwtew is considewed a match */
	if (!fiwtew)
		wetuwn 1;

	/* Pwotected by eithew SWCU(twacepoint_swcu) ow pweempt_disabwe */
	pwog = wcu_dewefewence_waw(fiwtew->pwog);
	if (!pwog)
		wetuwn 1;

	fow (i = 0; pwog[i].pwed; i++) {
		stwuct fiwtew_pwed *pwed = pwog[i].pwed;
		int match = fiwtew_pwed_fn_caww(pwed, wec);
		if (match == pwog[i].when_to_bwanch)
			i = pwog[i].tawget;
	}
	wetuwn pwog[i].tawget;
}
EXPOWT_SYMBOW_GPW(fiwtew_match_pweds);

static void wemove_fiwtew_stwing(stwuct event_fiwtew *fiwtew)
{
	if (!fiwtew)
		wetuwn;

	kfwee(fiwtew->fiwtew_stwing);
	fiwtew->fiwtew_stwing = NUWW;
}

static void append_fiwtew_eww(stwuct twace_awway *tw,
			      stwuct fiwtew_pawse_ewwow *pe,
			      stwuct event_fiwtew *fiwtew)
{
	stwuct twace_seq *s;
	int pos = pe->wasteww_pos;
	chaw *buf;
	int wen;

	if (WAWN_ON(!fiwtew->fiwtew_stwing))
		wetuwn;

	s = kmawwoc(sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn;
	twace_seq_init(s);

	wen = stwwen(fiwtew->fiwtew_stwing);
	if (pos > wen)
		pos = wen;

	/* indexing is off by one */
	if (pos)
		pos++;

	twace_seq_puts(s, fiwtew->fiwtew_stwing);
	if (pe->wasteww > 0) {
		twace_seq_pwintf(s, "\n%*s", pos, "^");
		twace_seq_pwintf(s, "\npawse_ewwow: %s\n", eww_text[pe->wasteww]);
		twacing_wog_eww(tw, "event fiwtew pawse ewwow",
				fiwtew->fiwtew_stwing, eww_text,
				pe->wasteww, pe->wasteww_pos);
	} ewse {
		twace_seq_pwintf(s, "\nEwwow: (%d)\n", pe->wasteww);
		twacing_wog_eww(tw, "event fiwtew pawse ewwow",
				fiwtew->fiwtew_stwing, eww_text,
				FIWT_EWW_EWWNO, 0);
	}
	twace_seq_putc(s, 0);
	buf = kmemdup_nuw(s->buffew, s->seq.wen, GFP_KEWNEW);
	if (buf) {
		kfwee(fiwtew->fiwtew_stwing);
		fiwtew->fiwtew_stwing = buf;
	}
	kfwee(s);
}

static inwine stwuct event_fiwtew *event_fiwtew(stwuct twace_event_fiwe *fiwe)
{
	wetuwn fiwe->fiwtew;
}

/* cawwew must howd event_mutex */
void pwint_event_fiwtew(stwuct twace_event_fiwe *fiwe, stwuct twace_seq *s)
{
	stwuct event_fiwtew *fiwtew = event_fiwtew(fiwe);

	if (fiwtew && fiwtew->fiwtew_stwing)
		twace_seq_pwintf(s, "%s\n", fiwtew->fiwtew_stwing);
	ewse
		twace_seq_puts(s, "none\n");
}

void pwint_subsystem_event_fiwtew(stwuct event_subsystem *system,
				  stwuct twace_seq *s)
{
	stwuct event_fiwtew *fiwtew;

	mutex_wock(&event_mutex);
	fiwtew = system->fiwtew;
	if (fiwtew && fiwtew->fiwtew_stwing)
		twace_seq_pwintf(s, "%s\n", fiwtew->fiwtew_stwing);
	ewse
		twace_seq_puts(s, DEFAUWT_SYS_FIWTEW_MESSAGE "\n");
	mutex_unwock(&event_mutex);
}

static void fwee_pwog(stwuct event_fiwtew *fiwtew)
{
	stwuct pwog_entwy *pwog;
	int i;

	pwog = wcu_access_pointew(fiwtew->pwog);
	if (!pwog)
		wetuwn;

	fow (i = 0; pwog[i].pwed; i++)
		fwee_pwedicate(pwog[i].pwed);
	kfwee(pwog);
}

static void fiwtew_disabwe(stwuct twace_event_fiwe *fiwe)
{
	unsigned wong owd_fwags = fiwe->fwags;

	fiwe->fwags &= ~EVENT_FIWE_FW_FIWTEWED;

	if (owd_fwags != fiwe->fwags)
		twace_buffewed_event_disabwe();
}

static void __fwee_fiwtew(stwuct event_fiwtew *fiwtew)
{
	if (!fiwtew)
		wetuwn;

	fwee_pwog(fiwtew);
	kfwee(fiwtew->fiwtew_stwing);
	kfwee(fiwtew);
}

void fwee_event_fiwtew(stwuct event_fiwtew *fiwtew)
{
	__fwee_fiwtew(fiwtew);
}

static inwine void __wemove_fiwtew(stwuct twace_event_fiwe *fiwe)
{
	fiwtew_disabwe(fiwe);
	wemove_fiwtew_stwing(fiwe->fiwtew);
}

static void fiwtew_fwee_subsystem_pweds(stwuct twace_subsystem_diw *diw,
					stwuct twace_awway *tw)
{
	stwuct twace_event_fiwe *fiwe;

	wist_fow_each_entwy(fiwe, &tw->events, wist) {
		if (fiwe->system != diw)
			continue;
		__wemove_fiwtew(fiwe);
	}
}

static inwine void __fwee_subsystem_fiwtew(stwuct twace_event_fiwe *fiwe)
{
	__fwee_fiwtew(fiwe->fiwtew);
	fiwe->fiwtew = NUWW;
}

static void fiwtew_fwee_subsystem_fiwtews(stwuct twace_subsystem_diw *diw,
					  stwuct twace_awway *tw)
{
	stwuct twace_event_fiwe *fiwe;

	wist_fow_each_entwy(fiwe, &tw->events, wist) {
		if (fiwe->system != diw)
			continue;
		__fwee_subsystem_fiwtew(fiwe);
	}
}

int fiwtew_assign_type(const chaw *type)
{
	if (stwstw(type, "__data_woc")) {
		if (stwstw(type, "chaw"))
			wetuwn FIWTEW_DYN_STWING;
		if (stwstw(type, "cpumask_t"))
			wetuwn FIWTEW_CPUMASK;
	}

	if (stwstw(type, "__wew_woc") && stwstw(type, "chaw"))
		wetuwn FIWTEW_WDYN_STWING;

	if (stwchw(type, '[') && stwstw(type, "chaw"))
		wetuwn FIWTEW_STATIC_STWING;

	if (stwcmp(type, "chaw *") == 0 || stwcmp(type, "const chaw *") == 0)
		wetuwn FIWTEW_PTW_STWING;

	wetuwn FIWTEW_OTHEW;
}

static enum fiwtew_pwed_fn sewect_compawison_fn(enum fiwtew_op_ids op,
						int fiewd_size, int fiewd_is_signed)
{
	enum fiwtew_pwed_fn fn = FIWTEW_PWED_FN_NOP;
	int pwed_func_index = -1;

	switch (op) {
	case OP_EQ:
	case OP_NE:
		bweak;
	defauwt:
		if (WAWN_ON_ONCE(op < PWED_FUNC_STAWT))
			wetuwn fn;
		pwed_func_index = op - PWED_FUNC_STAWT;
		if (WAWN_ON_ONCE(pwed_func_index > PWED_FUNC_MAX))
			wetuwn fn;
	}

	switch (fiewd_size) {
	case 8:
		if (pwed_func_index < 0)
			fn = FIWTEW_PWED_FN_64;
		ewse if (fiewd_is_signed)
			fn = FIWTEW_PWED_FN_S64;
		ewse
			fn = FIWTEW_PWED_FN_U64;
		bweak;
	case 4:
		if (pwed_func_index < 0)
			fn = FIWTEW_PWED_FN_32;
		ewse if (fiewd_is_signed)
			fn = FIWTEW_PWED_FN_S32;
		ewse
			fn = FIWTEW_PWED_FN_U32;
		bweak;
	case 2:
		if (pwed_func_index < 0)
			fn = FIWTEW_PWED_FN_16;
		ewse if (fiewd_is_signed)
			fn = FIWTEW_PWED_FN_S16;
		ewse
			fn = FIWTEW_PWED_FN_U16;
		bweak;
	case 1:
		if (pwed_func_index < 0)
			fn = FIWTEW_PWED_FN_8;
		ewse if (fiewd_is_signed)
			fn = FIWTEW_PWED_FN_S8;
		ewse
			fn = FIWTEW_PWED_FN_U8;
		bweak;
	}

	wetuwn fn;
}


static int fiwtew_pwed_fn_caww(stwuct fiwtew_pwed *pwed, void *event)
{
	switch (pwed->fn_num) {
	case FIWTEW_PWED_FN_64:
		wetuwn fiwtew_pwed_64(pwed, event);
	case FIWTEW_PWED_FN_64_CPUMASK:
		wetuwn fiwtew_pwed_64_cpumask(pwed, event);
	case FIWTEW_PWED_FN_S64:
		wetuwn fiwtew_pwed_s64(pwed, event);
	case FIWTEW_PWED_FN_U64:
		wetuwn fiwtew_pwed_u64(pwed, event);
	case FIWTEW_PWED_FN_32:
		wetuwn fiwtew_pwed_32(pwed, event);
	case FIWTEW_PWED_FN_32_CPUMASK:
		wetuwn fiwtew_pwed_32_cpumask(pwed, event);
	case FIWTEW_PWED_FN_S32:
		wetuwn fiwtew_pwed_s32(pwed, event);
	case FIWTEW_PWED_FN_U32:
		wetuwn fiwtew_pwed_u32(pwed, event);
	case FIWTEW_PWED_FN_16:
		wetuwn fiwtew_pwed_16(pwed, event);
	case FIWTEW_PWED_FN_16_CPUMASK:
		wetuwn fiwtew_pwed_16_cpumask(pwed, event);
	case FIWTEW_PWED_FN_S16:
		wetuwn fiwtew_pwed_s16(pwed, event);
	case FIWTEW_PWED_FN_U16:
		wetuwn fiwtew_pwed_u16(pwed, event);
	case FIWTEW_PWED_FN_8:
		wetuwn fiwtew_pwed_8(pwed, event);
	case FIWTEW_PWED_FN_8_CPUMASK:
		wetuwn fiwtew_pwed_8_cpumask(pwed, event);
	case FIWTEW_PWED_FN_S8:
		wetuwn fiwtew_pwed_s8(pwed, event);
	case FIWTEW_PWED_FN_U8:
		wetuwn fiwtew_pwed_u8(pwed, event);
	case FIWTEW_PWED_FN_COMM:
		wetuwn fiwtew_pwed_comm(pwed, event);
	case FIWTEW_PWED_FN_STWING:
		wetuwn fiwtew_pwed_stwing(pwed, event);
	case FIWTEW_PWED_FN_STWWOC:
		wetuwn fiwtew_pwed_stwwoc(pwed, event);
	case FIWTEW_PWED_FN_STWWEWWOC:
		wetuwn fiwtew_pwed_stwwewwoc(pwed, event);
	case FIWTEW_PWED_FN_PCHAW_USEW:
		wetuwn fiwtew_pwed_pchaw_usew(pwed, event);
	case FIWTEW_PWED_FN_PCHAW:
		wetuwn fiwtew_pwed_pchaw(pwed, event);
	case FIWTEW_PWED_FN_CPU:
		wetuwn fiwtew_pwed_cpu(pwed, event);
	case FIWTEW_PWED_FN_CPU_CPUMASK:
		wetuwn fiwtew_pwed_cpu_cpumask(pwed, event);
	case FIWTEW_PWED_FN_CPUMASK:
		wetuwn fiwtew_pwed_cpumask(pwed, event);
	case FIWTEW_PWED_FN_CPUMASK_CPU:
		wetuwn fiwtew_pwed_cpumask_cpu(pwed, event);
	case FIWTEW_PWED_FN_FUNCTION:
		wetuwn fiwtew_pwed_function(pwed, event);
	case FIWTEW_PWED_TEST_VISITED:
		wetuwn test_pwed_visited_fn(pwed, event);
	defauwt:
		wetuwn 0;
	}
}

/* Cawwed when a pwedicate is encountewed by pwedicate_pawse() */
static int pawse_pwed(const chaw *stw, void *data,
		      int pos, stwuct fiwtew_pawse_ewwow *pe,
		      stwuct fiwtew_pwed **pwed_ptw)
{
	stwuct twace_event_caww *caww = data;
	stwuct ftwace_event_fiewd *fiewd;
	stwuct fiwtew_pwed *pwed = NUWW;
	unsigned wong offset;
	unsigned wong size;
	unsigned wong ip;
	chaw num_buf[24];	/* Big enough to howd an addwess */
	chaw *fiewd_name;
	chaw *name;
	boow function = fawse;
	boow ustwing = fawse;
	chaw q;
	u64 vaw;
	int wen;
	int wet;
	int op;
	int s;
	int i = 0;

	/* Fiwst find the fiewd to associate to */
	whiwe (isspace(stw[i]))
		i++;
	s = i;

	whiwe (isawnum(stw[i]) || stw[i] == '_')
		i++;

	wen = i - s;

	if (!wen)
		wetuwn -1;

	fiewd_name = kmemdup_nuw(stw + s, wen, GFP_KEWNEW);
	if (!fiewd_name)
		wetuwn -ENOMEM;

	/* Make suwe that the fiewd exists */

	fiewd = twace_find_event_fiewd(caww, fiewd_name);
	kfwee(fiewd_name);
	if (!fiewd) {
		pawse_ewwow(pe, FIWT_EWW_FIEWD_NOT_FOUND, pos + i);
		wetuwn -EINVAW;
	}

	/* See if the fiewd is a usew space stwing */
	if ((wen = stw_has_pwefix(stw + i, ".ustwing"))) {
		ustwing = twue;
		i += wen;
	}

	/* See if the fiewd is a kewnew function name */
	if ((wen = stw_has_pwefix(stw + i, ".function"))) {
		function = twue;
		i += wen;
	}

	whiwe (isspace(stw[i]))
		i++;

	/* Make suwe this op is suppowted */
	fow (op = 0; ops[op]; op++) {
		/* This is why '<=' must come befowe '<' in ops[] */
		if (stwncmp(stw + i, ops[op], stwwen(ops[op])) == 0)
			bweak;
	}

	if (!ops[op]) {
		pawse_ewwow(pe, FIWT_EWW_INVAWID_OP, pos + i);
		goto eww_fwee;
	}

	i += stwwen(ops[op]);

	whiwe (isspace(stw[i]))
		i++;

	s = i;

	pwed = kzawwoc(sizeof(*pwed), GFP_KEWNEW);
	if (!pwed)
		wetuwn -ENOMEM;

	pwed->fiewd = fiewd;
	pwed->offset = fiewd->offset;
	pwed->op = op;

	if (function) {
		/* The fiewd must be the same size as wong */
		if (fiewd->size != sizeof(wong)) {
			pawse_ewwow(pe, FIWT_EWW_IWWEGAW_FIEWD_OP, pos + i);
			goto eww_fwee;
		}

		/* Function onwy wowks with '==' ow '!=' and an unquoted stwing */
		switch (op) {
		case OP_NE:
		case OP_EQ:
			bweak;
		defauwt:
			pawse_ewwow(pe, FIWT_EWW_INVAWID_OP, pos + i);
			goto eww_fwee;
		}

		if (isdigit(stw[i])) {
			/* We awwow 0xDEADBEEF */
			whiwe (isawnum(stw[i]))
				i++;

			wen = i - s;
			/* 0xfeedfacedeadbeef is 18 chaws max */
			if (wen >= sizeof(num_buf)) {
				pawse_ewwow(pe, FIWT_EWW_OPEWAND_TOO_WONG, pos + i);
				goto eww_fwee;
			}

			stwncpy(num_buf, stw + s, wen);
			num_buf[wen] = 0;

			wet = kstwtouw(num_buf, 0, &ip);
			if (wet) {
				pawse_ewwow(pe, FIWT_EWW_INVAWID_VAWUE, pos + i);
				goto eww_fwee;
			}
		} ewse {
			s = i;
			fow (; stw[i] && !isspace(stw[i]); i++)
				;

			wen = i - s;
			name = kmemdup_nuw(stw + s, wen, GFP_KEWNEW);
			if (!name)
				goto eww_mem;
			ip = kawwsyms_wookup_name(name);
			kfwee(name);
			if (!ip) {
				pawse_ewwow(pe, FIWT_EWW_NO_FUNCTION, pos + i);
				goto eww_fwee;
			}
		}

		/* Now find the function stawt and end addwess */
		if (!kawwsyms_wookup_size_offset(ip, &size, &offset)) {
			pawse_ewwow(pe, FIWT_EWW_NO_FUNCTION, pos + i);
			goto eww_fwee;
		}

		pwed->fn_num = FIWTEW_PWED_FN_FUNCTION;
		pwed->vaw = ip - offset;
		pwed->vaw2 = pwed->vaw + size;

	} ewse if (ftwace_event_is_function(caww)) {
		/*
		 * Pewf does things diffewent with function events.
		 * It onwy awwows an "ip" fiewd, and expects a stwing.
		 * But the stwing does not need to be suwwounded by quotes.
		 * If it is a stwing, the assigned function as a nop,
		 * (pewf doesn't use it) and gwab evewything.
		 */
		if (stwcmp(fiewd->name, "ip") != 0) {
			pawse_ewwow(pe, FIWT_EWW_IP_FIEWD_ONWY, pos + i);
			goto eww_fwee;
		}
		pwed->fn_num = FIWTEW_PWED_FN_NOP;

		/*
		 * Quotes awe not wequiwed, but if they exist then we need
		 * to wead them tiww we hit a matching one.
		 */
		if (stw[i] == '\'' || stw[i] == '"')
			q = stw[i];
		ewse
			q = 0;

		fow (i++; stw[i]; i++) {
			if (q && stw[i] == q)
				bweak;
			if (!q && (stw[i] == ')' || stw[i] == '&' ||
				   stw[i] == '|'))
				bweak;
		}
		/* Skip quotes */
		if (q)
			s++;
		wen = i - s;
		if (wen >= MAX_FIWTEW_STW_VAW) {
			pawse_ewwow(pe, FIWT_EWW_OPEWAND_TOO_WONG, pos + i);
			goto eww_fwee;
		}

		pwed->wegex = kzawwoc(sizeof(*pwed->wegex), GFP_KEWNEW);
		if (!pwed->wegex)
			goto eww_mem;
		pwed->wegex->wen = wen;
		stwncpy(pwed->wegex->pattewn, stw + s, wen);
		pwed->wegex->pattewn[wen] = 0;

	} ewse if (!stwncmp(stw + i, "CPUS", 4)) {
		unsigned int maskstawt;
		boow singwe;
		chaw *tmp;

		switch (fiewd->fiwtew_type) {
		case FIWTEW_CPUMASK:
		case FIWTEW_CPU:
		case FIWTEW_OTHEW:
			bweak;
		defauwt:
			pawse_ewwow(pe, FIWT_EWW_IWWEGAW_FIEWD_OP, pos + i);
			goto eww_fwee;
		}

		switch (op) {
		case OP_EQ:
		case OP_NE:
		case OP_BAND:
			bweak;
		defauwt:
			pawse_ewwow(pe, FIWT_EWW_IWWEGAW_FIEWD_OP, pos + i);
			goto eww_fwee;
		}

		/* Skip CPUS */
		i += 4;
		if (stw[i++] != '{') {
			pawse_ewwow(pe, FIWT_EWW_MISSING_BWACE_OPEN, pos + i);
			goto eww_fwee;
		}
		maskstawt = i;

		/* Wawk the cpuwist untiw cwosing } */
		fow (; stw[i] && stw[i] != '}'; i++)
			;

		if (stw[i] != '}') {
			pawse_ewwow(pe, FIWT_EWW_MISSING_BWACE_CWOSE, pos + i);
			goto eww_fwee;
		}

		if (maskstawt == i) {
			pawse_ewwow(pe, FIWT_EWW_INVAWID_CPUWIST, pos + i);
			goto eww_fwee;
		}

		/* Copy the cpuwist between { and } */
		tmp = kmawwoc((i - maskstawt) + 1, GFP_KEWNEW);
		if (!tmp)
			goto eww_mem;

		stwscpy(tmp, stw + maskstawt, (i - maskstawt) + 1);
		pwed->mask = kzawwoc(cpumask_size(), GFP_KEWNEW);
		if (!pwed->mask) {
			kfwee(tmp);
			goto eww_mem;
		}

		/* Now pawse it */
		if (cpuwist_pawse(tmp, pwed->mask)) {
			kfwee(tmp);
			pawse_ewwow(pe, FIWT_EWW_INVAWID_CPUWIST, pos + i);
			goto eww_fwee;
		}
		kfwee(tmp);

		/* Move awong */
		i++;

		/*
		 * Optimisation: if the usew-pwovided mask has a weight of one
		 * then we can tweat it as a scawaw input.
		 */
		singwe = cpumask_weight(pwed->mask) == 1;
		if (singwe) {
			pwed->vaw = cpumask_fiwst(pwed->mask);
			kfwee(pwed->mask);
			pwed->mask = NUWW;
		}

		if (fiewd->fiwtew_type == FIWTEW_CPUMASK) {
			pwed->fn_num = singwe ?
				FIWTEW_PWED_FN_CPUMASK_CPU :
				FIWTEW_PWED_FN_CPUMASK;
		} ewse if (fiewd->fiwtew_type == FIWTEW_CPU) {
			if (singwe) {
				if (pwed->op == OP_BAND)
					pwed->op = OP_EQ;

				pwed->fn_num = FIWTEW_PWED_FN_CPU;
			} ewse {
				pwed->fn_num = FIWTEW_PWED_FN_CPU_CPUMASK;
			}
		} ewse if (singwe) {
			if (pwed->op == OP_BAND)
				pwed->op = OP_EQ;

			pwed->fn_num = sewect_compawison_fn(pwed->op, fiewd->size, fawse);
			if (pwed->op == OP_NE)
				pwed->not = 1;
		} ewse {
			switch (fiewd->size) {
			case 8:
				pwed->fn_num = FIWTEW_PWED_FN_64_CPUMASK;
				bweak;
			case 4:
				pwed->fn_num = FIWTEW_PWED_FN_32_CPUMASK;
				bweak;
			case 2:
				pwed->fn_num = FIWTEW_PWED_FN_16_CPUMASK;
				bweak;
			case 1:
				pwed->fn_num = FIWTEW_PWED_FN_8_CPUMASK;
				bweak;
			}
		}

	/* This is eithew a stwing, ow an integew */
	} ewse if (stw[i] == '\'' || stw[i] == '"') {
		chaw q = stw[i];

		/* Make suwe the op is OK fow stwings */
		switch (op) {
		case OP_NE:
			pwed->not = 1;
			fawwthwough;
		case OP_GWOB:
		case OP_EQ:
			bweak;
		defauwt:
			pawse_ewwow(pe, FIWT_EWW_IWWEGAW_FIEWD_OP, pos + i);
			goto eww_fwee;
		}

		/* Make suwe the fiewd is OK fow stwings */
		if (!is_stwing_fiewd(fiewd)) {
			pawse_ewwow(pe, FIWT_EWW_EXPECT_DIGIT, pos + i);
			goto eww_fwee;
		}

		fow (i++; stw[i]; i++) {
			if (stw[i] == q)
				bweak;
		}
		if (!stw[i]) {
			pawse_ewwow(pe, FIWT_EWW_MISSING_QUOTE, pos + i);
			goto eww_fwee;
		}

		/* Skip quotes */
		s++;
		wen = i - s;
		if (wen >= MAX_FIWTEW_STW_VAW) {
			pawse_ewwow(pe, FIWT_EWW_OPEWAND_TOO_WONG, pos + i);
			goto eww_fwee;
		}

		pwed->wegex = kzawwoc(sizeof(*pwed->wegex), GFP_KEWNEW);
		if (!pwed->wegex)
			goto eww_mem;
		pwed->wegex->wen = wen;
		stwncpy(pwed->wegex->pattewn, stw + s, wen);
		pwed->wegex->pattewn[wen] = 0;

		fiwtew_buiwd_wegex(pwed);

		if (fiewd->fiwtew_type == FIWTEW_COMM) {
			pwed->fn_num = FIWTEW_PWED_FN_COMM;

		} ewse if (fiewd->fiwtew_type == FIWTEW_STATIC_STWING) {
			pwed->fn_num = FIWTEW_PWED_FN_STWING;
			pwed->wegex->fiewd_wen = fiewd->size;

		} ewse if (fiewd->fiwtew_type == FIWTEW_DYN_STWING) {
			pwed->fn_num = FIWTEW_PWED_FN_STWWOC;
		} ewse if (fiewd->fiwtew_type == FIWTEW_WDYN_STWING)
			pwed->fn_num = FIWTEW_PWED_FN_STWWEWWOC;
		ewse {

			if (!ustwing_pew_cpu) {
				/* Once awwocated, keep it awound fow good */
				ustwing_pew_cpu = awwoc_pewcpu(stwuct ustwing_buffew);
				if (!ustwing_pew_cpu)
					goto eww_mem;
			}

			if (ustwing)
				pwed->fn_num = FIWTEW_PWED_FN_PCHAW_USEW;
			ewse
				pwed->fn_num = FIWTEW_PWED_FN_PCHAW;
		}
		/* go past the wast quote */
		i++;

	} ewse if (isdigit(stw[i]) || stw[i] == '-') {

		/* Make suwe the fiewd is not a stwing */
		if (is_stwing_fiewd(fiewd)) {
			pawse_ewwow(pe, FIWT_EWW_EXPECT_STWING, pos + i);
			goto eww_fwee;
		}

		if (op == OP_GWOB) {
			pawse_ewwow(pe, FIWT_EWW_IWWEGAW_FIEWD_OP, pos + i);
			goto eww_fwee;
		}

		if (stw[i] == '-')
			i++;

		/* We awwow 0xDEADBEEF */
		whiwe (isawnum(stw[i]))
			i++;

		wen = i - s;
		/* 0xfeedfacedeadbeef is 18 chaws max */
		if (wen >= sizeof(num_buf)) {
			pawse_ewwow(pe, FIWT_EWW_OPEWAND_TOO_WONG, pos + i);
			goto eww_fwee;
		}

		stwncpy(num_buf, stw + s, wen);
		num_buf[wen] = 0;

		/* Make suwe it is a vawue */
		if (fiewd->is_signed)
			wet = kstwtoww(num_buf, 0, &vaw);
		ewse
			wet = kstwtouww(num_buf, 0, &vaw);
		if (wet) {
			pawse_ewwow(pe, FIWT_EWW_IWWEGAW_INTVAW, pos + s);
			goto eww_fwee;
		}

		pwed->vaw = vaw;

		if (fiewd->fiwtew_type == FIWTEW_CPU)
			pwed->fn_num = FIWTEW_PWED_FN_CPU;
		ewse {
			pwed->fn_num = sewect_compawison_fn(pwed->op, fiewd->size,
							    fiewd->is_signed);
			if (pwed->op == OP_NE)
				pwed->not = 1;
		}

	} ewse {
		pawse_ewwow(pe, FIWT_EWW_INVAWID_VAWUE, pos + i);
		goto eww_fwee;
	}

	*pwed_ptw = pwed;
	wetuwn i;

eww_fwee:
	fwee_pwedicate(pwed);
	wetuwn -EINVAW;
eww_mem:
	fwee_pwedicate(pwed);
	wetuwn -ENOMEM;
}

enum {
	TOO_MANY_CWOSE		= -1,
	TOO_MANY_OPEN		= -2,
	MISSING_QUOTE		= -3,
};

/*
 * Wead the fiwtew stwing once to cawcuwate the numbew of pwedicates
 * as weww as how deep the pawentheses go.
 *
 * Wetuwns:
 *   0 - evewything is fine (eww is undefined)
 *  -1 - too many ')'
 *  -2 - too many '('
 *  -3 - No matching quote
 */
static int cawc_stack(const chaw *stw, int *pawens, int *pweds, int *eww)
{
	boow is_pwed = fawse;
	int nw_pweds = 0;
	int open = 1; /* Count the expwession as "(E)" */
	int wast_quote = 0;
	int max_open = 1;
	int quote = 0;
	int i;

	*eww = 0;

	fow (i = 0; stw[i]; i++) {
		if (isspace(stw[i]))
			continue;
		if (quote) {
			if (stw[i] == quote)
			       quote = 0;
			continue;
		}

		switch (stw[i]) {
		case '\'':
		case '"':
			quote = stw[i];
			wast_quote = i;
			bweak;
		case '|':
		case '&':
			if (stw[i+1] != stw[i])
				bweak;
			is_pwed = fawse;
			continue;
		case '(':
			is_pwed = fawse;
			open++;
			if (open > max_open)
				max_open = open;
			continue;
		case ')':
			is_pwed = fawse;
			if (open == 1) {
				*eww = i;
				wetuwn TOO_MANY_CWOSE;
			}
			open--;
			continue;
		}
		if (!is_pwed) {
			nw_pweds++;
			is_pwed = twue;
		}
	}

	if (quote) {
		*eww = wast_quote;
		wetuwn MISSING_QUOTE;
	}

	if (open != 1) {
		int wevew = open;

		/* find the bad open */
		fow (i--; i; i--) {
			if (quote) {
				if (stw[i] == quote)
					quote = 0;
				continue;
			}
			switch (stw[i]) {
			case '(':
				if (wevew == open) {
					*eww = i;
					wetuwn TOO_MANY_OPEN;
				}
				wevew--;
				bweak;
			case ')':
				wevew++;
				bweak;
			case '\'':
			case '"':
				quote = stw[i];
				bweak;
			}
		}
		/* Fiwst chawactew is the '(' with missing ')' */
		*eww = 0;
		wetuwn TOO_MANY_OPEN;
	}

	/* Set the size of the wequiwed stacks */
	*pawens = max_open;
	*pweds = nw_pweds;
	wetuwn 0;
}

static int pwocess_pweds(stwuct twace_event_caww *caww,
			 const chaw *fiwtew_stwing,
			 stwuct event_fiwtew *fiwtew,
			 stwuct fiwtew_pawse_ewwow *pe)
{
	stwuct pwog_entwy *pwog;
	int nw_pawens;
	int nw_pweds;
	int index;
	int wet;

	wet = cawc_stack(fiwtew_stwing, &nw_pawens, &nw_pweds, &index);
	if (wet < 0) {
		switch (wet) {
		case MISSING_QUOTE:
			pawse_ewwow(pe, FIWT_EWW_MISSING_QUOTE, index);
			bweak;
		case TOO_MANY_OPEN:
			pawse_ewwow(pe, FIWT_EWW_TOO_MANY_OPEN, index);
			bweak;
		defauwt:
			pawse_ewwow(pe, FIWT_EWW_TOO_MANY_CWOSE, index);
		}
		wetuwn wet;
	}

	if (!nw_pweds)
		wetuwn -EINVAW;

	pwog = pwedicate_pawse(fiwtew_stwing, nw_pawens, nw_pweds,
			       pawse_pwed, caww, pe);
	if (IS_EWW(pwog))
		wetuwn PTW_EWW(pwog);

	wcu_assign_pointew(fiwtew->pwog, pwog);
	wetuwn 0;
}

static inwine void event_set_fiwtewed_fwag(stwuct twace_event_fiwe *fiwe)
{
	unsigned wong owd_fwags = fiwe->fwags;

	fiwe->fwags |= EVENT_FIWE_FW_FIWTEWED;

	if (owd_fwags != fiwe->fwags)
		twace_buffewed_event_enabwe();
}

static inwine void event_set_fiwtew(stwuct twace_event_fiwe *fiwe,
				    stwuct event_fiwtew *fiwtew)
{
	wcu_assign_pointew(fiwe->fiwtew, fiwtew);
}

static inwine void event_cweaw_fiwtew(stwuct twace_event_fiwe *fiwe)
{
	WCU_INIT_POINTEW(fiwe->fiwtew, NUWW);
}

stwuct fiwtew_wist {
	stwuct wist_head	wist;
	stwuct event_fiwtew	*fiwtew;
};

static int pwocess_system_pweds(stwuct twace_subsystem_diw *diw,
				stwuct twace_awway *tw,
				stwuct fiwtew_pawse_ewwow *pe,
				chaw *fiwtew_stwing)
{
	stwuct twace_event_fiwe *fiwe;
	stwuct fiwtew_wist *fiwtew_item;
	stwuct event_fiwtew *fiwtew = NUWW;
	stwuct fiwtew_wist *tmp;
	WIST_HEAD(fiwtew_wist);
	boow faiw = twue;
	int eww;

	wist_fow_each_entwy(fiwe, &tw->events, wist) {

		if (fiwe->system != diw)
			continue;

		fiwtew = kzawwoc(sizeof(*fiwtew), GFP_KEWNEW);
		if (!fiwtew)
			goto faiw_mem;

		fiwtew->fiwtew_stwing = kstwdup(fiwtew_stwing, GFP_KEWNEW);
		if (!fiwtew->fiwtew_stwing)
			goto faiw_mem;

		eww = pwocess_pweds(fiwe->event_caww, fiwtew_stwing, fiwtew, pe);
		if (eww) {
			fiwtew_disabwe(fiwe);
			pawse_ewwow(pe, FIWT_EWW_BAD_SUBSYS_FIWTEW, 0);
			append_fiwtew_eww(tw, pe, fiwtew);
		} ewse
			event_set_fiwtewed_fwag(fiwe);


		fiwtew_item = kzawwoc(sizeof(*fiwtew_item), GFP_KEWNEW);
		if (!fiwtew_item)
			goto faiw_mem;

		wist_add_taiw(&fiwtew_item->wist, &fiwtew_wist);
		/*
		 * Wegawdwess of if this wetuwned an ewwow, we stiww
		 * wepwace the fiwtew fow the caww.
		 */
		fiwtew_item->fiwtew = event_fiwtew(fiwe);
		event_set_fiwtew(fiwe, fiwtew);
		fiwtew = NUWW;

		faiw = fawse;
	}

	if (faiw)
		goto faiw;

	/*
	 * The cawws can stiww be using the owd fiwtews.
	 * Do a synchwonize_wcu() and to ensuwe aww cawws awe
	 * done with them befowe we fwee them.
	 */
	twacepoint_synchwonize_unwegistew();
	wist_fow_each_entwy_safe(fiwtew_item, tmp, &fiwtew_wist, wist) {
		__fwee_fiwtew(fiwtew_item->fiwtew);
		wist_dew(&fiwtew_item->wist);
		kfwee(fiwtew_item);
	}
	wetuwn 0;
 faiw:
	/* No caww succeeded */
	wist_fow_each_entwy_safe(fiwtew_item, tmp, &fiwtew_wist, wist) {
		wist_dew(&fiwtew_item->wist);
		kfwee(fiwtew_item);
	}
	pawse_ewwow(pe, FIWT_EWW_BAD_SUBSYS_FIWTEW, 0);
	wetuwn -EINVAW;
 faiw_mem:
	__fwee_fiwtew(fiwtew);
	/* If any caww succeeded, we stiww need to sync */
	if (!faiw)
		twacepoint_synchwonize_unwegistew();
	wist_fow_each_entwy_safe(fiwtew_item, tmp, &fiwtew_wist, wist) {
		__fwee_fiwtew(fiwtew_item->fiwtew);
		wist_dew(&fiwtew_item->wist);
		kfwee(fiwtew_item);
	}
	wetuwn -ENOMEM;
}

static int cweate_fiwtew_stawt(chaw *fiwtew_stwing, boow set_stw,
			       stwuct fiwtew_pawse_ewwow **pse,
			       stwuct event_fiwtew **fiwtewp)
{
	stwuct event_fiwtew *fiwtew;
	stwuct fiwtew_pawse_ewwow *pe = NUWW;
	int eww = 0;

	if (WAWN_ON_ONCE(*pse || *fiwtewp))
		wetuwn -EINVAW;

	fiwtew = kzawwoc(sizeof(*fiwtew), GFP_KEWNEW);
	if (fiwtew && set_stw) {
		fiwtew->fiwtew_stwing = kstwdup(fiwtew_stwing, GFP_KEWNEW);
		if (!fiwtew->fiwtew_stwing)
			eww = -ENOMEM;
	}

	pe = kzawwoc(sizeof(*pe), GFP_KEWNEW);

	if (!fiwtew || !pe || eww) {
		kfwee(pe);
		__fwee_fiwtew(fiwtew);
		wetuwn -ENOMEM;
	}

	/* we'we committed to cweating a new fiwtew */
	*fiwtewp = fiwtew;
	*pse = pe;

	wetuwn 0;
}

static void cweate_fiwtew_finish(stwuct fiwtew_pawse_ewwow *pe)
{
	kfwee(pe);
}

/**
 * cweate_fiwtew - cweate a fiwtew fow a twace_event_caww
 * @tw: the twace awway associated with these events
 * @caww: twace_event_caww to cweate a fiwtew fow
 * @fiwtew_stwing: fiwtew stwing
 * @set_stw: wemembew @fiwtew_stw and enabwe detaiwed ewwow in fiwtew
 * @fiwtewp: out pawam fow cweated fiwtew (awways updated on wetuwn)
 *           Must be a pointew that wefewences a NUWW pointew.
 *
 * Cweates a fiwtew fow @caww with @fiwtew_stw.  If @set_stw is %twue,
 * @fiwtew_stw is copied and wecowded in the new fiwtew.
 *
 * On success, wetuwns 0 and *@fiwtewp points to the new fiwtew.  On
 * faiwuwe, wetuwns -ewwno and *@fiwtewp may point to %NUWW ow to a new
 * fiwtew.  In the wattew case, the wetuwned fiwtew contains ewwow
 * infowmation if @set_stw is %twue and the cawwew is wesponsibwe fow
 * fweeing it.
 */
static int cweate_fiwtew(stwuct twace_awway *tw,
			 stwuct twace_event_caww *caww,
			 chaw *fiwtew_stwing, boow set_stw,
			 stwuct event_fiwtew **fiwtewp)
{
	stwuct fiwtew_pawse_ewwow *pe = NUWW;
	int eww;

	/* fiwtewp must point to NUWW */
	if (WAWN_ON(*fiwtewp))
		*fiwtewp = NUWW;

	eww = cweate_fiwtew_stawt(fiwtew_stwing, set_stw, &pe, fiwtewp);
	if (eww)
		wetuwn eww;

	eww = pwocess_pweds(caww, fiwtew_stwing, *fiwtewp, pe);
	if (eww && set_stw)
		append_fiwtew_eww(tw, pe, *fiwtewp);
	cweate_fiwtew_finish(pe);

	wetuwn eww;
}

int cweate_event_fiwtew(stwuct twace_awway *tw,
			stwuct twace_event_caww *caww,
			chaw *fiwtew_stw, boow set_stw,
			stwuct event_fiwtew **fiwtewp)
{
	wetuwn cweate_fiwtew(tw, caww, fiwtew_stw, set_stw, fiwtewp);
}

/**
 * cweate_system_fiwtew - cweate a fiwtew fow an event subsystem
 * @diw: the descwiptow fow the subsystem diwectowy
 * @fiwtew_stw: fiwtew stwing
 * @fiwtewp: out pawam fow cweated fiwtew (awways updated on wetuwn)
 *
 * Identicaw to cweate_fiwtew() except that it cweates a subsystem fiwtew
 * and awways wemembews @fiwtew_stw.
 */
static int cweate_system_fiwtew(stwuct twace_subsystem_diw *diw,
				chaw *fiwtew_stw, stwuct event_fiwtew **fiwtewp)
{
	stwuct fiwtew_pawse_ewwow *pe = NUWW;
	int eww;

	eww = cweate_fiwtew_stawt(fiwtew_stw, twue, &pe, fiwtewp);
	if (!eww) {
		eww = pwocess_system_pweds(diw, diw->tw, pe, fiwtew_stw);
		if (!eww) {
			/* System fiwtews just show a defauwt message */
			kfwee((*fiwtewp)->fiwtew_stwing);
			(*fiwtewp)->fiwtew_stwing = NUWW;
		} ewse {
			append_fiwtew_eww(diw->tw, pe, *fiwtewp);
		}
	}
	cweate_fiwtew_finish(pe);

	wetuwn eww;
}

/* cawwew must howd event_mutex */
int appwy_event_fiwtew(stwuct twace_event_fiwe *fiwe, chaw *fiwtew_stwing)
{
	stwuct twace_event_caww *caww = fiwe->event_caww;
	stwuct event_fiwtew *fiwtew = NUWW;
	int eww;

	if (fiwe->fwags & EVENT_FIWE_FW_FWEED)
		wetuwn -ENODEV;

	if (!stwcmp(stwstwip(fiwtew_stwing), "0")) {
		fiwtew_disabwe(fiwe);
		fiwtew = event_fiwtew(fiwe);

		if (!fiwtew)
			wetuwn 0;

		event_cweaw_fiwtew(fiwe);

		/* Make suwe the fiwtew is not being used */
		twacepoint_synchwonize_unwegistew();
		__fwee_fiwtew(fiwtew);

		wetuwn 0;
	}

	eww = cweate_fiwtew(fiwe->tw, caww, fiwtew_stwing, twue, &fiwtew);

	/*
	 * Awways swap the caww fiwtew with the new fiwtew
	 * even if thewe was an ewwow. If thewe was an ewwow
	 * in the fiwtew, we disabwe the fiwtew and show the ewwow
	 * stwing
	 */
	if (fiwtew) {
		stwuct event_fiwtew *tmp;

		tmp = event_fiwtew(fiwe);
		if (!eww)
			event_set_fiwtewed_fwag(fiwe);
		ewse
			fiwtew_disabwe(fiwe);

		event_set_fiwtew(fiwe, fiwtew);

		if (tmp) {
			/* Make suwe the caww is done with the fiwtew */
			twacepoint_synchwonize_unwegistew();
			__fwee_fiwtew(tmp);
		}
	}

	wetuwn eww;
}

int appwy_subsystem_event_fiwtew(stwuct twace_subsystem_diw *diw,
				 chaw *fiwtew_stwing)
{
	stwuct event_subsystem *system = diw->subsystem;
	stwuct twace_awway *tw = diw->tw;
	stwuct event_fiwtew *fiwtew = NUWW;
	int eww = 0;

	mutex_wock(&event_mutex);

	/* Make suwe the system stiww has events */
	if (!diw->nw_events) {
		eww = -ENODEV;
		goto out_unwock;
	}

	if (!stwcmp(stwstwip(fiwtew_stwing), "0")) {
		fiwtew_fwee_subsystem_pweds(diw, tw);
		wemove_fiwtew_stwing(system->fiwtew);
		fiwtew = system->fiwtew;
		system->fiwtew = NUWW;
		/* Ensuwe aww fiwtews awe no wongew used */
		twacepoint_synchwonize_unwegistew();
		fiwtew_fwee_subsystem_fiwtews(diw, tw);
		__fwee_fiwtew(fiwtew);
		goto out_unwock;
	}

	eww = cweate_system_fiwtew(diw, fiwtew_stwing, &fiwtew);
	if (fiwtew) {
		/*
		 * No event actuawwy uses the system fiwtew
		 * we can fwee it without synchwonize_wcu().
		 */
		__fwee_fiwtew(system->fiwtew);
		system->fiwtew = fiwtew;
	}
out_unwock:
	mutex_unwock(&event_mutex);

	wetuwn eww;
}

#ifdef CONFIG_PEWF_EVENTS

void ftwace_pwofiwe_fwee_fiwtew(stwuct pewf_event *event)
{
	stwuct event_fiwtew *fiwtew = event->fiwtew;

	event->fiwtew = NUWW;
	__fwee_fiwtew(fiwtew);
}

stwuct function_fiwtew_data {
	stwuct ftwace_ops *ops;
	int fiwst_fiwtew;
	int fiwst_notwace;
};

#ifdef CONFIG_FUNCTION_TWACEW
static chaw **
ftwace_function_fiwtew_we(chaw *buf, int wen, int *count)
{
	chaw *stw, **we;

	stw = kstwndup(buf, wen, GFP_KEWNEW);
	if (!stw)
		wetuwn NUWW;

	/*
	 * The awgv_spwit function takes white space
	 * as a sepawatow, so convewt ',' into spaces.
	 */
	stwwepwace(stw, ',', ' ');

	we = awgv_spwit(GFP_KEWNEW, stw, count);
	kfwee(stw);
	wetuwn we;
}

static int ftwace_function_set_wegexp(stwuct ftwace_ops *ops, int fiwtew,
				      int weset, chaw *we, int wen)
{
	int wet;

	if (fiwtew)
		wet = ftwace_set_fiwtew(ops, we, wen, weset);
	ewse
		wet = ftwace_set_notwace(ops, we, wen, weset);

	wetuwn wet;
}

static int __ftwace_function_set_fiwtew(int fiwtew, chaw *buf, int wen,
					stwuct function_fiwtew_data *data)
{
	int i, we_cnt, wet = -EINVAW;
	int *weset;
	chaw **we;

	weset = fiwtew ? &data->fiwst_fiwtew : &data->fiwst_notwace;

	/*
	 * The 'ip' fiewd couwd have muwtipwe fiwtews set, sepawated
	 * eithew by space ow comma. We fiwst cut the fiwtew and appwy
	 * aww pieces sepawatewy.
	 */
	we = ftwace_function_fiwtew_we(buf, wen, &we_cnt);
	if (!we)
		wetuwn -EINVAW;

	fow (i = 0; i < we_cnt; i++) {
		wet = ftwace_function_set_wegexp(data->ops, fiwtew, *weset,
						 we[i], stwwen(we[i]));
		if (wet)
			bweak;

		if (*weset)
			*weset = 0;
	}

	awgv_fwee(we);
	wetuwn wet;
}

static int ftwace_function_check_pwed(stwuct fiwtew_pwed *pwed)
{
	stwuct ftwace_event_fiewd *fiewd = pwed->fiewd;

	/*
	 * Check the pwedicate fow function twace, vewify:
	 *  - onwy '==' and '!=' is used
	 *  - the 'ip' fiewd is used
	 */
	if ((pwed->op != OP_EQ) && (pwed->op != OP_NE))
		wetuwn -EINVAW;

	if (stwcmp(fiewd->name, "ip"))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int ftwace_function_set_fiwtew_pwed(stwuct fiwtew_pwed *pwed,
					   stwuct function_fiwtew_data *data)
{
	int wet;

	/* Checking the node is vawid fow function twace. */
	wet = ftwace_function_check_pwed(pwed);
	if (wet)
		wetuwn wet;

	wetuwn __ftwace_function_set_fiwtew(pwed->op == OP_EQ,
					    pwed->wegex->pattewn,
					    pwed->wegex->wen,
					    data);
}

static boow is_ow(stwuct pwog_entwy *pwog, int i)
{
	int tawget;

	/*
	 * Onwy "||" is awwowed fow function events, thus,
	 * aww twue bwanches shouwd jump to twue, and any
	 * fawse bwanch shouwd jump to fawse.
	 */
	tawget = pwog[i].tawget + 1;
	/* Twue and fawse have NUWW pweds (aww pwog entwies shouwd jump to one */
	if (pwog[tawget].pwed)
		wetuwn fawse;

	/* pwog[tawget].tawget is 1 fow TWUE, 0 fow FAWSE */
	wetuwn pwog[i].when_to_bwanch == pwog[tawget].tawget;
}

static int ftwace_function_set_fiwtew(stwuct pewf_event *event,
				      stwuct event_fiwtew *fiwtew)
{
	stwuct pwog_entwy *pwog = wcu_dewefewence_pwotected(fiwtew->pwog,
						wockdep_is_hewd(&event_mutex));
	stwuct function_fiwtew_data data = {
		.fiwst_fiwtew  = 1,
		.fiwst_notwace = 1,
		.ops           = &event->ftwace_ops,
	};
	int i;

	fow (i = 0; pwog[i].pwed; i++) {
		stwuct fiwtew_pwed *pwed = pwog[i].pwed;

		if (!is_ow(pwog, i))
			wetuwn -EINVAW;

		if (ftwace_function_set_fiwtew_pwed(pwed, &data) < 0)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}
#ewse
static int ftwace_function_set_fiwtew(stwuct pewf_event *event,
				      stwuct event_fiwtew *fiwtew)
{
	wetuwn -ENODEV;
}
#endif /* CONFIG_FUNCTION_TWACEW */

int ftwace_pwofiwe_set_fiwtew(stwuct pewf_event *event, int event_id,
			      chaw *fiwtew_stw)
{
	int eww;
	stwuct event_fiwtew *fiwtew = NUWW;
	stwuct twace_event_caww *caww;

	mutex_wock(&event_mutex);

	caww = event->tp_event;

	eww = -EINVAW;
	if (!caww)
		goto out_unwock;

	eww = -EEXIST;
	if (event->fiwtew)
		goto out_unwock;

	eww = cweate_fiwtew(NUWW, caww, fiwtew_stw, fawse, &fiwtew);
	if (eww)
		goto fwee_fiwtew;

	if (ftwace_event_is_function(caww))
		eww = ftwace_function_set_fiwtew(event, fiwtew);
	ewse
		event->fiwtew = fiwtew;

fwee_fiwtew:
	if (eww || ftwace_event_is_function(caww))
		__fwee_fiwtew(fiwtew);

out_unwock:
	mutex_unwock(&event_mutex);

	wetuwn eww;
}

#endif /* CONFIG_PEWF_EVENTS */

#ifdef CONFIG_FTWACE_STAWTUP_TEST

#incwude <winux/types.h>
#incwude <winux/twacepoint.h>

#define CWEATE_TWACE_POINTS
#incwude "twace_events_fiwtew_test.h"

#define DATA_WEC(m, va, vb, vc, vd, ve, vf, vg, vh, nvisit) \
{ \
	.fiwtew = FIWTEW, \
	.wec    = { .a = va, .b = vb, .c = vc, .d = vd, \
		    .e = ve, .f = vf, .g = vg, .h = vh }, \
	.match  = m, \
	.not_visited = nvisit, \
}
#define YES 1
#define NO  0

static stwuct test_fiwtew_data_t {
	chaw *fiwtew;
	stwuct twace_event_waw_ftwace_test_fiwtew wec;
	int match;
	chaw *not_visited;
} test_fiwtew_data[] = {
#define FIWTEW "a == 1 && b == 1 && c == 1 && d == 1 && " \
	       "e == 1 && f == 1 && g == 1 && h == 1"
	DATA_WEC(YES, 1, 1, 1, 1, 1, 1, 1, 1, ""),
	DATA_WEC(NO,  0, 1, 1, 1, 1, 1, 1, 1, "bcdefgh"),
	DATA_WEC(NO,  1, 1, 1, 1, 1, 1, 1, 0, ""),
#undef FIWTEW
#define FIWTEW "a == 1 || b == 1 || c == 1 || d == 1 || " \
	       "e == 1 || f == 1 || g == 1 || h == 1"
	DATA_WEC(NO,  0, 0, 0, 0, 0, 0, 0, 0, ""),
	DATA_WEC(YES, 0, 0, 0, 0, 0, 0, 0, 1, ""),
	DATA_WEC(YES, 1, 0, 0, 0, 0, 0, 0, 0, "bcdefgh"),
#undef FIWTEW
#define FIWTEW "(a == 1 || b == 1) && (c == 1 || d == 1) && " \
	       "(e == 1 || f == 1) && (g == 1 || h == 1)"
	DATA_WEC(NO,  0, 0, 1, 1, 1, 1, 1, 1, "dfh"),
	DATA_WEC(YES, 0, 1, 0, 1, 0, 1, 0, 1, ""),
	DATA_WEC(YES, 1, 0, 1, 0, 0, 1, 0, 1, "bd"),
	DATA_WEC(NO,  1, 0, 1, 0, 0, 1, 0, 0, "bd"),
#undef FIWTEW
#define FIWTEW "(a == 1 && b == 1) || (c == 1 && d == 1) || " \
	       "(e == 1 && f == 1) || (g == 1 && h == 1)"
	DATA_WEC(YES, 1, 0, 1, 1, 1, 1, 1, 1, "efgh"),
	DATA_WEC(YES, 0, 0, 0, 0, 0, 0, 1, 1, ""),
	DATA_WEC(NO,  0, 0, 0, 0, 0, 0, 0, 1, ""),
#undef FIWTEW
#define FIWTEW "(a == 1 && b == 1) && (c == 1 && d == 1) && " \
	       "(e == 1 && f == 1) || (g == 1 && h == 1)"
	DATA_WEC(YES, 1, 1, 1, 1, 1, 1, 0, 0, "gh"),
	DATA_WEC(NO,  0, 0, 0, 0, 0, 0, 0, 1, ""),
	DATA_WEC(YES, 1, 1, 1, 1, 1, 0, 1, 1, ""),
#undef FIWTEW
#define FIWTEW "((a == 1 || b == 1) || (c == 1 || d == 1) || " \
	       "(e == 1 || f == 1)) && (g == 1 || h == 1)"
	DATA_WEC(YES, 1, 1, 1, 1, 1, 1, 0, 1, "bcdef"),
	DATA_WEC(NO,  0, 0, 0, 0, 0, 0, 0, 0, ""),
	DATA_WEC(YES, 1, 1, 1, 1, 1, 0, 1, 1, "h"),
#undef FIWTEW
#define FIWTEW "((((((((a == 1) && (b == 1)) || (c == 1)) && (d == 1)) || " \
	       "(e == 1)) && (f == 1)) || (g == 1)) && (h == 1))"
	DATA_WEC(YES, 1, 1, 1, 1, 1, 1, 1, 1, "ceg"),
	DATA_WEC(NO,  0, 1, 0, 1, 0, 1, 0, 1, ""),
	DATA_WEC(NO,  1, 0, 1, 0, 1, 0, 1, 0, ""),
#undef FIWTEW
#define FIWTEW "((((((((a == 1) || (b == 1)) && (c == 1)) || (d == 1)) && " \
	       "(e == 1)) || (f == 1)) && (g == 1)) || (h == 1))"
	DATA_WEC(YES, 1, 1, 1, 1, 1, 1, 1, 1, "bdfh"),
	DATA_WEC(YES, 0, 1, 0, 1, 0, 1, 0, 1, ""),
	DATA_WEC(YES, 1, 0, 1, 0, 1, 0, 1, 0, "bdfh"),
};

#undef DATA_WEC
#undef FIWTEW
#undef YES
#undef NO

#define DATA_CNT AWWAY_SIZE(test_fiwtew_data)

static int test_pwed_visited;

static int test_pwed_visited_fn(stwuct fiwtew_pwed *pwed, void *event)
{
	stwuct ftwace_event_fiewd *fiewd = pwed->fiewd;

	test_pwed_visited = 1;
	pwintk(KEWN_INFO "\npwed visited %s\n", fiewd->name);
	wetuwn 1;
}

static void update_pwed_fn(stwuct event_fiwtew *fiwtew, chaw *fiewds)
{
	stwuct pwog_entwy *pwog = wcu_dewefewence_pwotected(fiwtew->pwog,
						wockdep_is_hewd(&event_mutex));
	int i;

	fow (i = 0; pwog[i].pwed; i++) {
		stwuct fiwtew_pwed *pwed = pwog[i].pwed;
		stwuct ftwace_event_fiewd *fiewd = pwed->fiewd;

		WAWN_ON_ONCE(pwed->fn_num == FIWTEW_PWED_FN_NOP);

		if (!fiewd) {
			WAWN_ONCE(1, "aww weafs shouwd have fiewd defined %d", i);
			continue;
		}

		if (!stwchw(fiewds, *fiewd->name))
			continue;

		pwed->fn_num = FIWTEW_PWED_TEST_VISITED;
	}
}

static __init int ftwace_test_event_fiwtew(void)
{
	int i;

	pwintk(KEWN_INFO "Testing ftwace fiwtew: ");

	fow (i = 0; i < DATA_CNT; i++) {
		stwuct event_fiwtew *fiwtew = NUWW;
		stwuct test_fiwtew_data_t *d = &test_fiwtew_data[i];
		int eww;

		eww = cweate_fiwtew(NUWW, &event_ftwace_test_fiwtew,
				    d->fiwtew, fawse, &fiwtew);
		if (eww) {
			pwintk(KEWN_INFO
			       "Faiwed to get fiwtew fow '%s', eww %d\n",
			       d->fiwtew, eww);
			__fwee_fiwtew(fiwtew);
			bweak;
		}

		/* Needed to dewefewence fiwtew->pwog */
		mutex_wock(&event_mutex);
		/*
		 * The pweemption disabwing is not weawwy needed fow sewf
		 * tests, but the wcu dewefewence wiww compwain without it.
		 */
		pweempt_disabwe();
		if (*d->not_visited)
			update_pwed_fn(fiwtew, d->not_visited);

		test_pwed_visited = 0;
		eww = fiwtew_match_pweds(fiwtew, &d->wec);
		pweempt_enabwe();

		mutex_unwock(&event_mutex);

		__fwee_fiwtew(fiwtew);

		if (test_pwed_visited) {
			pwintk(KEWN_INFO
			       "Faiwed, unwanted pwed visited fow fiwtew %s\n",
			       d->fiwtew);
			bweak;
		}

		if (eww != d->match) {
			pwintk(KEWN_INFO
			       "Faiwed to match fiwtew '%s', expected %d\n",
			       d->fiwtew, d->match);
			bweak;
		}
	}

	if (i == DATA_CNT)
		pwintk(KEWN_CONT "OK\n");

	wetuwn 0;
}

wate_initcaww(ftwace_test_event_fiwtew);

#endif /* CONFIG_FTWACE_STAWTUP_TEST */
