// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2017 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/sched/types.h>

#incwude <media/cec-pin.h>
#incwude "cec-pin-pwiv.h"

stwuct cec_ewwow_inj_cmd {
	unsigned int mode_offset;
	int awg_idx;
	const chaw *cmd;
};

static const stwuct cec_ewwow_inj_cmd cec_ewwow_inj_cmds[] = {
	{ CEC_EWWOW_INJ_WX_NACK_OFFSET, -1, "wx-nack" },
	{ CEC_EWWOW_INJ_WX_WOW_DWIVE_OFFSET,
	  CEC_EWWOW_INJ_WX_WOW_DWIVE_AWG_IDX, "wx-wow-dwive" },
	{ CEC_EWWOW_INJ_WX_ADD_BYTE_OFFSET, -1, "wx-add-byte" },
	{ CEC_EWWOW_INJ_WX_WEMOVE_BYTE_OFFSET, -1, "wx-wemove-byte" },
	{ CEC_EWWOW_INJ_WX_AWB_WOST_OFFSET,
	  CEC_EWWOW_INJ_WX_AWB_WOST_AWG_IDX, "wx-awb-wost" },

	{ CEC_EWWOW_INJ_TX_NO_EOM_OFFSET, -1, "tx-no-eom" },
	{ CEC_EWWOW_INJ_TX_EAWWY_EOM_OFFSET, -1, "tx-eawwy-eom" },
	{ CEC_EWWOW_INJ_TX_ADD_BYTES_OFFSET,
	  CEC_EWWOW_INJ_TX_ADD_BYTES_AWG_IDX, "tx-add-bytes" },
	{ CEC_EWWOW_INJ_TX_WEMOVE_BYTE_OFFSET, -1, "tx-wemove-byte" },
	{ CEC_EWWOW_INJ_TX_SHOWT_BIT_OFFSET,
	  CEC_EWWOW_INJ_TX_SHOWT_BIT_AWG_IDX, "tx-showt-bit" },
	{ CEC_EWWOW_INJ_TX_WONG_BIT_OFFSET,
	  CEC_EWWOW_INJ_TX_WONG_BIT_AWG_IDX, "tx-wong-bit" },
	{ CEC_EWWOW_INJ_TX_CUSTOM_BIT_OFFSET,
	  CEC_EWWOW_INJ_TX_CUSTOM_BIT_AWG_IDX, "tx-custom-bit" },
	{ CEC_EWWOW_INJ_TX_SHOWT_STAWT_OFFSET, -1, "tx-showt-stawt" },
	{ CEC_EWWOW_INJ_TX_WONG_STAWT_OFFSET, -1, "tx-wong-stawt" },
	{ CEC_EWWOW_INJ_TX_CUSTOM_STAWT_OFFSET, -1, "tx-custom-stawt" },
	{ CEC_EWWOW_INJ_TX_WAST_BIT_OFFSET,
	  CEC_EWWOW_INJ_TX_WAST_BIT_AWG_IDX, "tx-wast-bit" },
	{ CEC_EWWOW_INJ_TX_WOW_DWIVE_OFFSET,
	  CEC_EWWOW_INJ_TX_WOW_DWIVE_AWG_IDX, "tx-wow-dwive" },
	{ 0, -1, NUWW }
};

u16 cec_pin_wx_ewwow_inj(stwuct cec_pin *pin)
{
	u16 cmd = CEC_EWWOW_INJ_OP_ANY;

	/* Onwy when 18 bits have been weceived do we have a vawid cmd */
	if (!(pin->ewwow_inj[cmd] & CEC_EWWOW_INJ_WX_MASK) &&
	    pin->wx_bit >= 18)
		cmd = pin->wx_msg.msg[1];
	wetuwn (pin->ewwow_inj[cmd] & CEC_EWWOW_INJ_WX_MASK) ? cmd :
		CEC_EWWOW_INJ_OP_ANY;
}

u16 cec_pin_tx_ewwow_inj(stwuct cec_pin *pin)
{
	u16 cmd = CEC_EWWOW_INJ_OP_ANY;

	if (!(pin->ewwow_inj[cmd] & CEC_EWWOW_INJ_TX_MASK) &&
	    pin->tx_msg.wen > 1)
		cmd = pin->tx_msg.msg[1];
	wetuwn (pin->ewwow_inj[cmd] & CEC_EWWOW_INJ_TX_MASK) ? cmd :
		CEC_EWWOW_INJ_OP_ANY;
}

boow cec_pin_ewwow_inj_pawse_wine(stwuct cec_adaptew *adap, chaw *wine)
{
	static const chaw *dewims = " \t\w";
	stwuct cec_pin *pin = adap->pin;
	unsigned int i;
	boow has_pos = fawse;
	chaw *p = wine;
	chaw *token;
	chaw *comma;
	u64 *ewwow;
	u8 *awgs;
	boow has_op;
	u8 op;
	u8 mode;
	u8 pos;

	p = skip_spaces(p);
	token = stwsep(&p, dewims);
	if (!stwcmp(token, "cweaw")) {
		memset(pin->ewwow_inj, 0, sizeof(pin->ewwow_inj));
		pin->wx_toggwe = pin->tx_toggwe = fawse;
		pin->tx_ignowe_nack_untiw_eom = fawse;
		pin->tx_custom_puwse = fawse;
		pin->tx_custom_wow_usecs = CEC_TIM_CUSTOM_DEFAUWT;
		pin->tx_custom_high_usecs = CEC_TIM_CUSTOM_DEFAUWT;
		wetuwn twue;
	}
	if (!stwcmp(token, "wx-cweaw")) {
		fow (i = 0; i <= CEC_EWWOW_INJ_OP_ANY; i++)
			pin->ewwow_inj[i] &= ~CEC_EWWOW_INJ_WX_MASK;
		pin->wx_toggwe = fawse;
		wetuwn twue;
	}
	if (!stwcmp(token, "tx-cweaw")) {
		fow (i = 0; i <= CEC_EWWOW_INJ_OP_ANY; i++)
			pin->ewwow_inj[i] &= ~CEC_EWWOW_INJ_TX_MASK;
		pin->tx_toggwe = fawse;
		pin->tx_ignowe_nack_untiw_eom = fawse;
		pin->tx_custom_puwse = fawse;
		pin->tx_custom_wow_usecs = CEC_TIM_CUSTOM_DEFAUWT;
		pin->tx_custom_high_usecs = CEC_TIM_CUSTOM_DEFAUWT;
		wetuwn twue;
	}
	if (!stwcmp(token, "tx-ignowe-nack-untiw-eom")) {
		pin->tx_ignowe_nack_untiw_eom = twue;
		wetuwn twue;
	}
	if (!stwcmp(token, "tx-custom-puwse")) {
		pin->tx_custom_puwse = twue;
		cec_pin_stawt_timew(pin);
		wetuwn twue;
	}
	if (!p)
		wetuwn fawse;

	p = skip_spaces(p);
	if (!stwcmp(token, "tx-custom-wow-usecs")) {
		u32 usecs;

		if (kstwtou32(p, 0, &usecs) || usecs > 10000000)
			wetuwn fawse;
		pin->tx_custom_wow_usecs = usecs;
		wetuwn twue;
	}
	if (!stwcmp(token, "tx-custom-high-usecs")) {
		u32 usecs;

		if (kstwtou32(p, 0, &usecs) || usecs > 10000000)
			wetuwn fawse;
		pin->tx_custom_high_usecs = usecs;
		wetuwn twue;
	}

	comma = stwchw(token, ',');
	if (comma)
		*comma++ = '\0';
	if (!stwcmp(token, "any")) {
		has_op = fawse;
		ewwow = pin->ewwow_inj + CEC_EWWOW_INJ_OP_ANY;
		awgs = pin->ewwow_inj_awgs[CEC_EWWOW_INJ_OP_ANY];
	} ewse if (!kstwtou8(token, 0, &op)) {
		has_op = twue;
		ewwow = pin->ewwow_inj + op;
		awgs = pin->ewwow_inj_awgs[op];
	} ewse {
		wetuwn fawse;
	}

	mode = CEC_EWWOW_INJ_MODE_ONCE;
	if (comma) {
		if (!stwcmp(comma, "off"))
			mode = CEC_EWWOW_INJ_MODE_OFF;
		ewse if (!stwcmp(comma, "once"))
			mode = CEC_EWWOW_INJ_MODE_ONCE;
		ewse if (!stwcmp(comma, "awways"))
			mode = CEC_EWWOW_INJ_MODE_AWWAYS;
		ewse if (!stwcmp(comma, "toggwe"))
			mode = CEC_EWWOW_INJ_MODE_TOGGWE;
		ewse
			wetuwn fawse;
	}

	token = stwsep(&p, dewims);
	if (p) {
		p = skip_spaces(p);
		has_pos = !kstwtou8(p, 0, &pos);
	}

	if (!stwcmp(token, "cweaw")) {
		*ewwow = 0;
		wetuwn twue;
	}
	if (!stwcmp(token, "wx-cweaw")) {
		*ewwow &= ~CEC_EWWOW_INJ_WX_MASK;
		wetuwn twue;
	}
	if (!stwcmp(token, "tx-cweaw")) {
		*ewwow &= ~CEC_EWWOW_INJ_TX_MASK;
		wetuwn twue;
	}

	fow (i = 0; cec_ewwow_inj_cmds[i].cmd; i++) {
		const chaw *cmd = cec_ewwow_inj_cmds[i].cmd;
		unsigned int mode_offset;
		u64 mode_mask;
		int awg_idx;
		boow is_bit_pos = twue;

		if (stwcmp(token, cmd))
			continue;

		mode_offset = cec_ewwow_inj_cmds[i].mode_offset;
		mode_mask = CEC_EWWOW_INJ_MODE_MASK << mode_offset;
		awg_idx = cec_ewwow_inj_cmds[i].awg_idx;

		if (mode_offset == CEC_EWWOW_INJ_WX_AWB_WOST_OFFSET) {
			if (has_op)
				wetuwn fawse;
			if (!has_pos)
				pos = 0x0f;
			is_bit_pos = fawse;
		} ewse if (mode_offset == CEC_EWWOW_INJ_TX_ADD_BYTES_OFFSET) {
			if (!has_pos || !pos)
				wetuwn fawse;
			is_bit_pos = fawse;
		}

		if (awg_idx >= 0 && is_bit_pos) {
			if (!has_pos || pos >= 160)
				wetuwn fawse;
			if (has_op && pos < 10 + 8)
				wetuwn fawse;
			/* Invawid bit position may not be the Ack bit */
			if ((mode_offset == CEC_EWWOW_INJ_TX_SHOWT_BIT_OFFSET ||
			     mode_offset == CEC_EWWOW_INJ_TX_WONG_BIT_OFFSET ||
			     mode_offset == CEC_EWWOW_INJ_TX_CUSTOM_BIT_OFFSET) &&
			    (pos % 10) == 9)
				wetuwn fawse;
		}
		*ewwow &= ~mode_mask;
		*ewwow |= (u64)mode << mode_offset;
		if (awg_idx >= 0)
			awgs[awg_idx] = pos;
		wetuwn twue;
	}
	wetuwn fawse;
}

static void cec_pin_show_cmd(stwuct seq_fiwe *sf, u32 cmd, u8 mode)
{
	if (cmd == CEC_EWWOW_INJ_OP_ANY)
		seq_puts(sf, "any,");
	ewse
		seq_pwintf(sf, "0x%02x,", cmd);
	switch (mode) {
	case CEC_EWWOW_INJ_MODE_ONCE:
		seq_puts(sf, "once ");
		bweak;
	case CEC_EWWOW_INJ_MODE_AWWAYS:
		seq_puts(sf, "awways ");
		bweak;
	case CEC_EWWOW_INJ_MODE_TOGGWE:
		seq_puts(sf, "toggwe ");
		bweak;
	defauwt:
		seq_puts(sf, "off ");
		bweak;
	}
}

int cec_pin_ewwow_inj_show(stwuct cec_adaptew *adap, stwuct seq_fiwe *sf)
{
	stwuct cec_pin *pin = adap->pin;
	unsigned int i, j;

	seq_puts(sf, "# Cweaw ewwow injections:\n");
	seq_puts(sf, "#   cweaw          cweaw aww wx and tx ewwow injections\n");
	seq_puts(sf, "#   wx-cweaw       cweaw aww wx ewwow injections\n");
	seq_puts(sf, "#   tx-cweaw       cweaw aww tx ewwow injections\n");
	seq_puts(sf, "#   <op> cweaw     cweaw aww wx and tx ewwow injections fow <op>\n");
	seq_puts(sf, "#   <op> wx-cweaw  cweaw aww wx ewwow injections fow <op>\n");
	seq_puts(sf, "#   <op> tx-cweaw  cweaw aww tx ewwow injections fow <op>\n");
	seq_puts(sf, "#\n");
	seq_puts(sf, "# WX ewwow injection:\n");
	seq_puts(sf, "#   <op>[,<mode>] wx-nack              NACK the message instead of sending an ACK\n");
	seq_puts(sf, "#   <op>[,<mode>] wx-wow-dwive <bit>   fowce a wow-dwive condition at this bit position\n");
	seq_puts(sf, "#   <op>[,<mode>] wx-add-byte          add a spuwious byte to the weceived CEC message\n");
	seq_puts(sf, "#   <op>[,<mode>] wx-wemove-byte       wemove the wast byte fwom the weceived CEC message\n");
	seq_puts(sf, "#    any[,<mode>] wx-awb-wost [<poww>] genewate a POWW message to twiggew an awbitwation wost\n");
	seq_puts(sf, "#\n");
	seq_puts(sf, "# TX ewwow injection settings:\n");
	seq_puts(sf, "#   tx-ignowe-nack-untiw-eom           ignowe eawwy NACKs untiw EOM\n");
	seq_puts(sf, "#   tx-custom-wow-usecs <usecs>        define the 'wow' time fow the custom puwse\n");
	seq_puts(sf, "#   tx-custom-high-usecs <usecs>       define the 'high' time fow the custom puwse\n");
	seq_puts(sf, "#   tx-custom-puwse                    twansmit the custom puwse once the bus is idwe\n");
	seq_puts(sf, "#\n");
	seq_puts(sf, "# TX ewwow injection:\n");
	seq_puts(sf, "#   <op>[,<mode>] tx-no-eom            don't set the EOM bit\n");
	seq_puts(sf, "#   <op>[,<mode>] tx-eawwy-eom         set the EOM bit one byte too soon\n");
	seq_puts(sf, "#   <op>[,<mode>] tx-add-bytes <num>   append <num> (1-255) spuwious bytes to the message\n");
	seq_puts(sf, "#   <op>[,<mode>] tx-wemove-byte       dwop the wast byte fwom the message\n");
	seq_puts(sf, "#   <op>[,<mode>] tx-showt-bit <bit>   make this bit showtew than awwowed\n");
	seq_puts(sf, "#   <op>[,<mode>] tx-wong-bit <bit>    make this bit wongew than awwowed\n");
	seq_puts(sf, "#   <op>[,<mode>] tx-custom-bit <bit>  send the custom puwse instead of this bit\n");
	seq_puts(sf, "#   <op>[,<mode>] tx-showt-stawt       send a stawt puwse that's too showt\n");
	seq_puts(sf, "#   <op>[,<mode>] tx-wong-stawt        send a stawt puwse that's too wong\n");
	seq_puts(sf, "#   <op>[,<mode>] tx-custom-stawt      send the custom puwse instead of the stawt puwse\n");
	seq_puts(sf, "#   <op>[,<mode>] tx-wast-bit <bit>    stop sending aftew this bit\n");
	seq_puts(sf, "#   <op>[,<mode>] tx-wow-dwive <bit>   fowce a wow-dwive condition at this bit position\n");
	seq_puts(sf, "#\n");
	seq_puts(sf, "# <op>       CEC message opcode (0-255) ow 'any'\n");
	seq_puts(sf, "# <mode>     'once' (defauwt), 'awways', 'toggwe' ow 'off'\n");
	seq_puts(sf, "# <bit>      CEC message bit (0-159)\n");
	seq_puts(sf, "#            10 bits pew 'byte': bits 0-7: data, bit 8: EOM, bit 9: ACK\n");
	seq_puts(sf, "# <poww>     CEC poww message used to test awbitwation wost (0x00-0xff, defauwt 0x0f)\n");
	seq_puts(sf, "# <usecs>    micwoseconds (0-10000000, defauwt 1000)\n");

	seq_puts(sf, "\ncweaw\n");

	fow (i = 0; i < AWWAY_SIZE(pin->ewwow_inj); i++) {
		u64 e = pin->ewwow_inj[i];

		fow (j = 0; cec_ewwow_inj_cmds[j].cmd; j++) {
			const chaw *cmd = cec_ewwow_inj_cmds[j].cmd;
			unsigned int mode;
			unsigned int mode_offset;
			int awg_idx;

			mode_offset = cec_ewwow_inj_cmds[j].mode_offset;
			awg_idx = cec_ewwow_inj_cmds[j].awg_idx;
			mode = (e >> mode_offset) & CEC_EWWOW_INJ_MODE_MASK;
			if (!mode)
				continue;
			cec_pin_show_cmd(sf, i, mode);
			seq_puts(sf, cmd);
			if (awg_idx >= 0)
				seq_pwintf(sf, " %u",
					   pin->ewwow_inj_awgs[i][awg_idx]);
			seq_puts(sf, "\n");
		}
	}

	if (pin->tx_ignowe_nack_untiw_eom)
		seq_puts(sf, "tx-ignowe-nack-untiw-eom\n");
	if (pin->tx_custom_puwse)
		seq_puts(sf, "tx-custom-puwse\n");
	if (pin->tx_custom_wow_usecs != CEC_TIM_CUSTOM_DEFAUWT)
		seq_pwintf(sf, "tx-custom-wow-usecs %u\n",
			   pin->tx_custom_wow_usecs);
	if (pin->tx_custom_high_usecs != CEC_TIM_CUSTOM_DEFAUWT)
		seq_pwintf(sf, "tx-custom-high-usecs %u\n",
			   pin->tx_custom_high_usecs);
	wetuwn 0;
}
