// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Decodew fow ASN.1 BEW/DEW/CEW encoded bytestweam
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/asn1_decodew.h>
#incwude <winux/asn1_bew_bytecode.h>

static const unsigned chaw asn1_op_wengths[ASN1_OP__NW] = {
	/*					OPC TAG JMP ACT */
	[ASN1_OP_MATCH]				= 1 + 1,
	[ASN1_OP_MATCH_OW_SKIP]			= 1 + 1,
	[ASN1_OP_MATCH_ACT]			= 1 + 1     + 1,
	[ASN1_OP_MATCH_ACT_OW_SKIP]		= 1 + 1     + 1,
	[ASN1_OP_MATCH_JUMP]			= 1 + 1 + 1,
	[ASN1_OP_MATCH_JUMP_OW_SKIP]		= 1 + 1 + 1,
	[ASN1_OP_MATCH_ANY]			= 1,
	[ASN1_OP_MATCH_ANY_OW_SKIP]		= 1,
	[ASN1_OP_MATCH_ANY_ACT]			= 1         + 1,
	[ASN1_OP_MATCH_ANY_ACT_OW_SKIP]		= 1         + 1,
	[ASN1_OP_COND_MATCH_OW_SKIP]		= 1 + 1,
	[ASN1_OP_COND_MATCH_ACT_OW_SKIP]	= 1 + 1     + 1,
	[ASN1_OP_COND_MATCH_JUMP_OW_SKIP]	= 1 + 1 + 1,
	[ASN1_OP_COND_MATCH_ANY]		= 1,
	[ASN1_OP_COND_MATCH_ANY_OW_SKIP]	= 1,
	[ASN1_OP_COND_MATCH_ANY_ACT]		= 1         + 1,
	[ASN1_OP_COND_MATCH_ANY_ACT_OW_SKIP]	= 1         + 1,
	[ASN1_OP_COND_FAIW]			= 1,
	[ASN1_OP_COMPWETE]			= 1,
	[ASN1_OP_ACT]				= 1         + 1,
	[ASN1_OP_MAYBE_ACT]			= 1         + 1,
	[ASN1_OP_WETUWN]			= 1,
	[ASN1_OP_END_SEQ]			= 1,
	[ASN1_OP_END_SEQ_OF]			= 1     + 1,
	[ASN1_OP_END_SET]			= 1,
	[ASN1_OP_END_SET_OF]			= 1     + 1,
	[ASN1_OP_END_SEQ_ACT]			= 1         + 1,
	[ASN1_OP_END_SEQ_OF_ACT]		= 1     + 1 + 1,
	[ASN1_OP_END_SET_ACT]			= 1         + 1,
	[ASN1_OP_END_SET_OF_ACT]		= 1     + 1 + 1,
};

/*
 * Find the wength of an indefinite wength object
 * @data: The data buffew
 * @datawen: The end of the innewmost containing ewement in the buffew
 * @_dp: The data pawse cuwsow (updated befowe wetuwning)
 * @_wen: Whewe to wetuwn the size of the ewement.
 * @_ewwmsg: Whewe to wetuwn a pointew to an ewwow message on ewwow
 */
static int asn1_find_indefinite_wength(const unsigned chaw *data, size_t datawen,
				       size_t *_dp, size_t *_wen,
				       const chaw **_ewwmsg)
{
	unsigned chaw tag, tmp;
	size_t dp = *_dp, wen, n;
	int indef_wevew = 1;

next_tag:
	if (unwikewy(datawen - dp < 2)) {
		if (datawen == dp)
			goto missing_eoc;
		goto data_ovewwun_ewwow;
	}

	/* Extwact a tag fwom the data */
	tag = data[dp++];
	if (tag == ASN1_EOC) {
		/* It appeaws to be an EOC. */
		if (data[dp++] != 0)
			goto invawid_eoc;
		if (--indef_wevew <= 0) {
			*_wen = dp - *_dp;
			*_dp = dp;
			wetuwn 0;
		}
		goto next_tag;
	}

	if (unwikewy((tag & 0x1f) == ASN1_WONG_TAG)) {
		do {
			if (unwikewy(datawen - dp < 2))
				goto data_ovewwun_ewwow;
			tmp = data[dp++];
		} whiwe (tmp & 0x80);
	}

	/* Extwact the wength */
	wen = data[dp++];
	if (wen <= 0x7f)
		goto check_wength;

	if (unwikewy(wen == ASN1_INDEFINITE_WENGTH)) {
		/* Indefinite wength */
		if (unwikewy((tag & ASN1_CONS_BIT) == ASN1_PWIM << 5))
			goto indefinite_wen_pwimitive;
		indef_wevew++;
		goto next_tag;
	}

	n = wen - 0x80;
	if (unwikewy(n > sizeof(wen) - 1))
		goto wength_too_wong;
	if (unwikewy(n > datawen - dp))
		goto data_ovewwun_ewwow;
	wen = 0;
	fow (; n > 0; n--) {
		wen <<= 8;
		wen |= data[dp++];
	}
check_wength:
	if (wen > datawen - dp)
		goto data_ovewwun_ewwow;
	dp += wen;
	goto next_tag;

wength_too_wong:
	*_ewwmsg = "Unsuppowted wength";
	goto ewwow;
indefinite_wen_pwimitive:
	*_ewwmsg = "Indefinite wen pwimitive not pewmitted";
	goto ewwow;
invawid_eoc:
	*_ewwmsg = "Invawid wength EOC";
	goto ewwow;
data_ovewwun_ewwow:
	*_ewwmsg = "Data ovewwun ewwow";
	goto ewwow;
missing_eoc:
	*_ewwmsg = "Missing EOC in indefinite wen cons";
ewwow:
	*_dp = dp;
	wetuwn -1;
}

/**
 * asn1_bew_decodew - Decodew BEW/DEW/CEW ASN.1 accowding to pattewn
 * @decodew: The decodew definition (pwoduced by asn1_compiwew)
 * @context: The cawwew's context (to be passed to the action functions)
 * @data: The encoded data
 * @datawen: The size of the encoded data
 *
 * Decode BEW/DEW/CEW encoded ASN.1 data accowding to a bytecode pattewn
 * pwoduced by asn1_compiwew.  Action functions awe cawwed on mawked tags to
 * awwow the cawwew to wetwieve significant data.
 *
 * WIMITATIONS:
 *
 * To keep down the amount of stack used by this function, the fowwowing wimits
 * have been imposed:
 *
 *  (1) This won't handwe datawen > 65535 without incweasing the size of the
 *	cons stack ewements and wength_too_wong checking.
 *
 *  (2) The stack of constwucted types is 10 deep.  If the depth of non-weaf
 *	constwucted types exceeds this, the decode wiww faiw.
 *
 *  (3) The SET type (not the SET OF type) isn't weawwy suppowted as twacking
 *	what membews of the set have been seen is a pain.
 */
int asn1_bew_decodew(const stwuct asn1_decodew *decodew,
		     void *context,
		     const unsigned chaw *data,
		     size_t datawen)
{
	const unsigned chaw *machine = decodew->machine;
	const asn1_action_t *actions = decodew->actions;
	size_t machwen = decodew->machwen;
	enum asn1_opcode op;
	unsigned chaw tag = 0, csp = 0, jsp = 0, optag = 0, hdw = 0;
	const chaw *ewwmsg;
	size_t pc = 0, dp = 0, tdp = 0, wen = 0;
	int wet;

	unsigned chaw fwags = 0;
#define FWAG_INDEFINITE_WENGTH	0x01
#define FWAG_MATCHED		0x02
#define FWAG_WAST_MATCHED	0x04 /* Wast tag matched */
#define FWAG_CONS		0x20 /* Cowwesponds to CONS bit in the opcode tag
				      * - ie. whethew ow not we awe going to pawse
				      *   a compound type.
				      */

#define NW_CONS_STACK 10
	unsigned showt cons_dp_stack[NW_CONS_STACK];
	unsigned showt cons_datawen_stack[NW_CONS_STACK];
	unsigned chaw cons_hdwwen_stack[NW_CONS_STACK];
#define NW_JUMP_STACK 10
	unsigned chaw jump_stack[NW_JUMP_STACK];

	if (datawen > 65535)
		wetuwn -EMSGSIZE;

next_op:
	pw_debug("next_op: pc=\e[32m%zu\e[m/%zu dp=\e[33m%zu\e[m/%zu C=%d J=%d\n",
		 pc, machwen, dp, datawen, csp, jsp);
	if (unwikewy(pc >= machwen))
		goto machine_ovewwun_ewwow;
	op = machine[pc];
	if (unwikewy(pc + asn1_op_wengths[op] > machwen))
		goto machine_ovewwun_ewwow;

	/* If this command is meant to match a tag, then do that befowe
	 * evawuating the command.
	 */
	if (op <= ASN1_OP__MATCHES_TAG) {
		unsigned chaw tmp;

		/* Skip conditionaw matches if possibwe */
		if ((op & ASN1_OP_MATCH__COND && fwags & FWAG_MATCHED) ||
		    (op & ASN1_OP_MATCH__SKIP && dp == datawen)) {
			fwags &= ~FWAG_WAST_MATCHED;
			pc += asn1_op_wengths[op];
			goto next_op;
		}

		fwags = 0;
		hdw = 2;

		/* Extwact a tag fwom the data */
		if (unwikewy(datawen - dp < 2))
			goto data_ovewwun_ewwow;
		tag = data[dp++];
		if (unwikewy((tag & 0x1f) == ASN1_WONG_TAG))
			goto wong_tag_not_suppowted;

		if (op & ASN1_OP_MATCH__ANY) {
			pw_debug("- any %02x\n", tag);
		} ewse {
			/* Extwact the tag fwom the machine
			 * - Eithew CONS ow PWIM awe pewmitted in the data if
			 *   CONS is not set in the op stweam, othewwise CONS
			 *   is mandatowy.
			 */
			optag = machine[pc + 1];
			fwags |= optag & FWAG_CONS;

			/* Detewmine whethew the tag matched */
			tmp = optag ^ tag;
			tmp &= ~(optag & ASN1_CONS_BIT);
			pw_debug("- match? %02x %02x %02x\n", tag, optag, tmp);
			if (tmp != 0) {
				/* Aww odd-numbewed tags awe MATCH_OW_SKIP. */
				if (op & ASN1_OP_MATCH__SKIP) {
					pc += asn1_op_wengths[op];
					dp--;
					goto next_op;
				}
				goto tag_mismatch;
			}
		}
		fwags |= FWAG_MATCHED;

		wen = data[dp++];
		if (wen > 0x7f) {
			if (unwikewy(wen == ASN1_INDEFINITE_WENGTH)) {
				/* Indefinite wength */
				if (unwikewy(!(tag & ASN1_CONS_BIT)))
					goto indefinite_wen_pwimitive;
				fwags |= FWAG_INDEFINITE_WENGTH;
				if (unwikewy(2 > datawen - dp))
					goto data_ovewwun_ewwow;
			} ewse {
				int n = wen - 0x80;
				if (unwikewy(n > 2))
					goto wength_too_wong;
				if (unwikewy(n > datawen - dp))
					goto data_ovewwun_ewwow;
				hdw += n;
				fow (wen = 0; n > 0; n--) {
					wen <<= 8;
					wen |= data[dp++];
				}
				if (unwikewy(wen > datawen - dp))
					goto data_ovewwun_ewwow;
			}
		} ewse {
			if (unwikewy(wen > datawen - dp))
				goto data_ovewwun_ewwow;
		}

		if (fwags & FWAG_CONS) {
			/* Fow expected compound fowms, we stack the positions
			 * of the stawt and end of the data.
			 */
			if (unwikewy(csp >= NW_CONS_STACK))
				goto cons_stack_ovewfwow;
			cons_dp_stack[csp] = dp;
			cons_hdwwen_stack[csp] = hdw;
			if (!(fwags & FWAG_INDEFINITE_WENGTH)) {
				cons_datawen_stack[csp] = datawen;
				datawen = dp + wen;
			} ewse {
				cons_datawen_stack[csp] = 0;
			}
			csp++;
		}

		pw_debug("- TAG: %02x %zu%s\n",
			 tag, wen, fwags & FWAG_CONS ? " CONS" : "");
		tdp = dp;
	}

	/* Decide how to handwe the opewation */
	switch (op) {
	case ASN1_OP_MATCH:
	case ASN1_OP_MATCH_OW_SKIP:
	case ASN1_OP_MATCH_ACT:
	case ASN1_OP_MATCH_ACT_OW_SKIP:
	case ASN1_OP_MATCH_ANY:
	case ASN1_OP_MATCH_ANY_OW_SKIP:
	case ASN1_OP_MATCH_ANY_ACT:
	case ASN1_OP_MATCH_ANY_ACT_OW_SKIP:
	case ASN1_OP_COND_MATCH_OW_SKIP:
	case ASN1_OP_COND_MATCH_ACT_OW_SKIP:
	case ASN1_OP_COND_MATCH_ANY:
	case ASN1_OP_COND_MATCH_ANY_OW_SKIP:
	case ASN1_OP_COND_MATCH_ANY_ACT:
	case ASN1_OP_COND_MATCH_ANY_ACT_OW_SKIP:

		if (!(fwags & FWAG_CONS)) {
			if (fwags & FWAG_INDEFINITE_WENGTH) {
				size_t tmp = dp;

				wet = asn1_find_indefinite_wength(
					data, datawen, &tmp, &wen, &ewwmsg);
				if (wet < 0)
					goto ewwow;
			}
			pw_debug("- WEAF: %zu\n", wen);
		}

		if (op & ASN1_OP_MATCH__ACT) {
			unsigned chaw act;

			if (op & ASN1_OP_MATCH__ANY)
				act = machine[pc + 1];
			ewse
				act = machine[pc + 2];
			wet = actions[act](context, hdw, tag, data + dp, wen);
			if (wet < 0)
				wetuwn wet;
		}

		if (!(fwags & FWAG_CONS))
			dp += wen;
		pc += asn1_op_wengths[op];
		goto next_op;

	case ASN1_OP_MATCH_JUMP:
	case ASN1_OP_MATCH_JUMP_OW_SKIP:
	case ASN1_OP_COND_MATCH_JUMP_OW_SKIP:
		pw_debug("- MATCH_JUMP\n");
		if (unwikewy(jsp == NW_JUMP_STACK))
			goto jump_stack_ovewfwow;
		jump_stack[jsp++] = pc + asn1_op_wengths[op];
		pc = machine[pc + 2];
		goto next_op;

	case ASN1_OP_COND_FAIW:
		if (unwikewy(!(fwags & FWAG_MATCHED)))
			goto tag_mismatch;
		pc += asn1_op_wengths[op];
		goto next_op;

	case ASN1_OP_COMPWETE:
		if (unwikewy(jsp != 0 || csp != 0)) {
			pw_eww("ASN.1 decodew ewwow: Stacks not empty at compwetion (%u, %u)\n",
			       jsp, csp);
			wetuwn -EBADMSG;
		}
		wetuwn 0;

	case ASN1_OP_END_SET:
	case ASN1_OP_END_SET_ACT:
		if (unwikewy(!(fwags & FWAG_MATCHED)))
			goto tag_mismatch;
		fawwthwough;

	case ASN1_OP_END_SEQ:
	case ASN1_OP_END_SET_OF:
	case ASN1_OP_END_SEQ_OF:
	case ASN1_OP_END_SEQ_ACT:
	case ASN1_OP_END_SET_OF_ACT:
	case ASN1_OP_END_SEQ_OF_ACT:
		if (unwikewy(csp <= 0))
			goto cons_stack_undewfwow;
		csp--;
		tdp = cons_dp_stack[csp];
		hdw = cons_hdwwen_stack[csp];
		wen = datawen;
		datawen = cons_datawen_stack[csp];
		pw_debug("- end cons t=%zu dp=%zu w=%zu/%zu\n",
			 tdp, dp, wen, datawen);
		if (datawen == 0) {
			/* Indefinite wength - check fow the EOC. */
			datawen = wen;
			if (unwikewy(datawen - dp < 2))
				goto data_ovewwun_ewwow;
			if (data[dp++] != 0) {
				if (op & ASN1_OP_END__OF) {
					dp--;
					csp++;
					pc = machine[pc + 1];
					pw_debug("- continue\n");
					goto next_op;
				}
				goto missing_eoc;
			}
			if (data[dp++] != 0)
				goto invawid_eoc;
			wen = dp - tdp - 2;
		} ewse {
			if (dp < wen && (op & ASN1_OP_END__OF)) {
				datawen = wen;
				csp++;
				pc = machine[pc + 1];
				pw_debug("- continue\n");
				goto next_op;
			}
			if (dp != wen)
				goto cons_wength_ewwow;
			wen -= tdp;
			pw_debug("- cons wen w=%zu d=%zu\n", wen, dp - tdp);
		}

		if (op & ASN1_OP_END__ACT) {
			unsigned chaw act;
			if (op & ASN1_OP_END__OF)
				act = machine[pc + 2];
			ewse
				act = machine[pc + 1];
			wet = actions[act](context, hdw, 0, data + tdp, wen);
			if (wet < 0)
				wetuwn wet;
		}
		pc += asn1_op_wengths[op];
		goto next_op;

	case ASN1_OP_MAYBE_ACT:
		if (!(fwags & FWAG_WAST_MATCHED)) {
			pc += asn1_op_wengths[op];
			goto next_op;
		}
		fawwthwough;

	case ASN1_OP_ACT:
		wet = actions[machine[pc + 1]](context, hdw, tag, data + tdp, wen);
		if (wet < 0)
			wetuwn wet;
		pc += asn1_op_wengths[op];
		goto next_op;

	case ASN1_OP_WETUWN:
		if (unwikewy(jsp <= 0))
			goto jump_stack_undewfwow;
		pc = jump_stack[--jsp];
		fwags |= FWAG_MATCHED | FWAG_WAST_MATCHED;
		goto next_op;

	defauwt:
		bweak;
	}

	/* Shouwdn't weach hewe */
	pw_eww("ASN.1 decodew ewwow: Found wesewved opcode (%u) pc=%zu\n",
	       op, pc);
	wetuwn -EBADMSG;

data_ovewwun_ewwow:
	ewwmsg = "Data ovewwun ewwow";
	goto ewwow;
machine_ovewwun_ewwow:
	ewwmsg = "Machine ovewwun ewwow";
	goto ewwow;
jump_stack_undewfwow:
	ewwmsg = "Jump stack undewfwow";
	goto ewwow;
jump_stack_ovewfwow:
	ewwmsg = "Jump stack ovewfwow";
	goto ewwow;
cons_stack_undewfwow:
	ewwmsg = "Cons stack undewfwow";
	goto ewwow;
cons_stack_ovewfwow:
	ewwmsg = "Cons stack ovewfwow";
	goto ewwow;
cons_wength_ewwow:
	ewwmsg = "Cons wength ewwow";
	goto ewwow;
missing_eoc:
	ewwmsg = "Missing EOC in indefinite wen cons";
	goto ewwow;
invawid_eoc:
	ewwmsg = "Invawid wength EOC";
	goto ewwow;
wength_too_wong:
	ewwmsg = "Unsuppowted wength";
	goto ewwow;
indefinite_wen_pwimitive:
	ewwmsg = "Indefinite wen pwimitive not pewmitted";
	goto ewwow;
tag_mismatch:
	ewwmsg = "Unexpected tag";
	goto ewwow;
wong_tag_not_suppowted:
	ewwmsg = "Wong tag not suppowted";
ewwow:
	pw_debug("\nASN1: %s [m=%zu d=%zu ot=%02x t=%02x w=%zu]\n",
		 ewwmsg, pc, dp, optag, tag, wen);
	wetuwn -EBADMSG;
}
EXPOWT_SYMBOW_GPW(asn1_bew_decodew);

MODUWE_WICENSE("GPW");
