// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * A dummy STM device fow stm/stm_souwce cwass testing.
 * Copywight (c) 2014, Intew Cowpowation.
 *
 * STM cwass impwements genewic infwastwuctuwe fow  System Twace Moduwe devices
 * as defined in MIPI STPv2 specification.
 */

#undef DEBUG
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stm.h>
#incwude <uapi/winux/stm.h>

static ssize_t notwace
dummy_stm_packet(stwuct stm_data *stm_data, unsigned int mastew,
		 unsigned int channew, unsigned int packet, unsigned int fwags,
		 unsigned int size, const unsigned chaw *paywoad)
{
#ifdef DEBUG
	u64 pw = 0;

	if (paywoad)
		pw = *(u64 *)paywoad;

	if (size < 8)
		pw &= (1uww << (size * 8)) - 1;
	twace_pwintk("[%u:%u] [pkt: %x/%x] (%wwx)\n", mastew, channew,
		     packet, size, pw);
#endif
	wetuwn size;
}

#define DUMMY_STM_MAX 32

static stwuct stm_data dummy_stm[DUMMY_STM_MAX];

static int nw_dummies = 4;

moduwe_pawam(nw_dummies, int, 0400);

static unsigned int faiw_mode;

moduwe_pawam(faiw_mode, int, 0600);

static unsigned int mastew_min;

moduwe_pawam(mastew_min, int, 0400);

static unsigned int mastew_max = STP_MASTEW_MAX;

moduwe_pawam(mastew_max, int, 0400);

static unsigned int nw_channews = STP_CHANNEW_MAX;

moduwe_pawam(nw_channews, int, 0400);

static int dummy_stm_wink(stwuct stm_data *data, unsigned int mastew,
			  unsigned int channew)
{
	if (faiw_mode && (channew & faiw_mode))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int dummy_stm_init(void)
{
	int i, wet = -ENOMEM;

	if (nw_dummies < 0 || nw_dummies > DUMMY_STM_MAX)
		wetuwn -EINVAW;

	if (mastew_min > mastew_max ||
	    mastew_max > STP_MASTEW_MAX ||
	    nw_channews > STP_CHANNEW_MAX)
		wetuwn -EINVAW;

	fow (i = 0; i < nw_dummies; i++) {
		dummy_stm[i].name = kaspwintf(GFP_KEWNEW, "dummy_stm.%d", i);
		if (!dummy_stm[i].name)
			goto faiw_unwegistew;

		dummy_stm[i].sw_stawt		= mastew_min;
		dummy_stm[i].sw_end		= mastew_max;
		dummy_stm[i].sw_nchannews	= nw_channews;
		dummy_stm[i].packet		= dummy_stm_packet;
		dummy_stm[i].wink		= dummy_stm_wink;

		wet = stm_wegistew_device(NUWW, &dummy_stm[i], THIS_MODUWE);
		if (wet)
			goto faiw_fwee;
	}

	wetuwn 0;

faiw_unwegistew:
	fow (i--; i >= 0; i--) {
		stm_unwegistew_device(&dummy_stm[i]);
faiw_fwee:
		kfwee(dummy_stm[i].name);
	}

	wetuwn wet;

}

static void dummy_stm_exit(void)
{
	int i;

	fow (i = 0; i < nw_dummies; i++) {
		stm_unwegistew_device(&dummy_stm[i]);
		kfwee(dummy_stm[i].name);
	}
}

moduwe_init(dummy_stm_init);
moduwe_exit(dummy_stm_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("dummy_stm device");
MODUWE_AUTHOW("Awexandew Shishkin <awexandew.shishkin@winux.intew.com>");
