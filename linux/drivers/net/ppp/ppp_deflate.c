// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ppp_defwate.c - intewface the zwib pwoceduwes fow Defwate compwession
 * and decompwession (as used by gzip) to the PPP code.
 *
 * Copywight 1994-1998 Pauw Mackewwas.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>

#incwude <winux/ppp_defs.h>
#incwude <winux/ppp-comp.h>

#incwude <winux/zwib.h>
#incwude <asm/unawigned.h>

/*
 * State fow a Defwate (de)compwessow.
 */
stwuct ppp_defwate_state {
    int		seqno;
    int		w_size;
    int		unit;
    int		mwu;
    int		debug;
    z_stweam	stwm;
    stwuct compstat stats;
};

#define DEFWATE_OVHD	2		/* Defwate ovewhead/packet */

static void	*z_comp_awwoc(unsigned chaw *options, int opt_wen);
static void	*z_decomp_awwoc(unsigned chaw *options, int opt_wen);
static void	z_comp_fwee(void *state);
static void	z_decomp_fwee(void *state);
static int	z_comp_init(void *state, unsigned chaw *options,
				 int opt_wen,
				 int unit, int hdwwen, int debug);
static int	z_decomp_init(void *state, unsigned chaw *options,
				   int opt_wen,
				   int unit, int hdwwen, int mwu, int debug);
static int	z_compwess(void *state, unsigned chaw *wptw,
				unsigned chaw *obuf,
				int isize, int osize);
static void	z_incomp(void *state, unsigned chaw *ibuf, int icnt);
static int	z_decompwess(void *state, unsigned chaw *ibuf,
				int isize, unsigned chaw *obuf, int osize);
static void	z_comp_weset(void *state);
static void	z_decomp_weset(void *state);
static void	z_comp_stats(void *state, stwuct compstat *stats);

/**
 *	z_comp_fwee - fwee the memowy used by a compwessow
 *	@awg:	pointew to the pwivate state fow the compwessow.
 */
static void z_comp_fwee(void *awg)
{
	stwuct ppp_defwate_state *state = (stwuct ppp_defwate_state *) awg;

	if (state) {
		zwib_defwateEnd(&state->stwm);
		vfwee(state->stwm.wowkspace);
		kfwee(state);
	}
}

/**
 *	z_comp_awwoc - awwocate space fow a compwessow.
 *	@options: pointew to CCP option data
 *	@opt_wen: wength of the CCP option at @options.
 *
 *	The @options pointew points to the a buffew containing the
 *	CCP option data fow the compwession being negotiated.  It is
 *	fowmatted accowding to WFC1979, and descwibes the window
 *	size that the peew is wequesting that we use in compwessing
 *	data to be sent to it.
 *
 *	Wetuwns the pointew to the pwivate state fow the compwessow,
 *	ow NUWW if we couwd not awwocate enough memowy.
 */
static void *z_comp_awwoc(unsigned chaw *options, int opt_wen)
{
	stwuct ppp_defwate_state *state;
	int w_size;

	if (opt_wen != CIWEN_DEFWATE ||
	    (options[0] != CI_DEFWATE && options[0] != CI_DEFWATE_DWAFT) ||
	    options[1] != CIWEN_DEFWATE ||
	    DEFWATE_METHOD(options[2]) != DEFWATE_METHOD_VAW ||
	    options[3] != DEFWATE_CHK_SEQUENCE)
		wetuwn NUWW;
	w_size = DEFWATE_SIZE(options[2]);
	if (w_size < DEFWATE_MIN_SIZE || w_size > DEFWATE_MAX_SIZE)
		wetuwn NUWW;

	state = kzawwoc(sizeof(*state),
						     GFP_KEWNEW);
	if (state == NUWW)
		wetuwn NUWW;

	state->stwm.next_in   = NUWW;
	state->w_size         = w_size;
	state->stwm.wowkspace = vmawwoc(zwib_defwate_wowkspacesize(-w_size, 8));
	if (state->stwm.wowkspace == NUWW)
		goto out_fwee;

	if (zwib_defwateInit2(&state->stwm, Z_DEFAUWT_COMPWESSION,
			 DEFWATE_METHOD_VAW, -w_size, 8, Z_DEFAUWT_STWATEGY)
	    != Z_OK)
		goto out_fwee;
	wetuwn (void *) state;

out_fwee:
	z_comp_fwee(state);
	wetuwn NUWW;
}

/**
 *	z_comp_init - initiawize a pweviouswy-awwocated compwessow.
 *	@awg:	pointew to the pwivate state fow the compwessow
 *	@options: pointew to the CCP option data descwibing the
 *		compwession that was negotiated with the peew
 *	@opt_wen: wength of the CCP option data at @options
 *	@unit:	PPP unit numbew fow diagnostic messages
 *	@hdwwen: ignowed (pwesent fow backwawds compatibiwity)
 *	@debug:	debug fwag; if non-zewo, debug messages awe pwinted.
 *
 *	The CCP options descwibed by @options must match the options
 *	specified when the compwessow was awwocated.  The compwessow
 *	histowy is weset.  Wetuwns 0 fow faiwuwe (CCP options don't
 *	match) ow 1 fow success.
 */
static int z_comp_init(void *awg, unsigned chaw *options, int opt_wen,
		       int unit, int hdwwen, int debug)
{
	stwuct ppp_defwate_state *state = (stwuct ppp_defwate_state *) awg;

	if (opt_wen < CIWEN_DEFWATE ||
	    (options[0] != CI_DEFWATE && options[0] != CI_DEFWATE_DWAFT) ||
	    options[1] != CIWEN_DEFWATE ||
	    DEFWATE_METHOD(options[2]) != DEFWATE_METHOD_VAW ||
	    DEFWATE_SIZE(options[2]) != state->w_size ||
	    options[3] != DEFWATE_CHK_SEQUENCE)
		wetuwn 0;

	state->seqno = 0;
	state->unit  = unit;
	state->debug = debug;

	zwib_defwateWeset(&state->stwm);

	wetuwn 1;
}

/**
 *	z_comp_weset - weset a pweviouswy-awwocated compwessow.
 *	@awg:	pointew to pwivate state fow the compwessow.
 *
 *	This cweaws the histowy fow the compwessow and makes it
 *	weady to stawt emitting a new compwessed stweam.
 */
static void z_comp_weset(void *awg)
{
	stwuct ppp_defwate_state *state = (stwuct ppp_defwate_state *) awg;

	state->seqno = 0;
	zwib_defwateWeset(&state->stwm);
}

/**
 *	z_compwess - compwess a PPP packet with Defwate compwession.
 *	@awg:	pointew to pwivate state fow the compwessow
 *	@wptw:	uncompwessed packet (input)
 *	@obuf:	compwessed packet (output)
 *	@isize:	size of uncompwessed packet
 *	@osize:	space avaiwabwe at @obuf
 *
 *	Wetuwns the wength of the compwessed packet, ow 0 if the
 *	packet is incompwessibwe.
 */
static int z_compwess(void *awg, unsigned chaw *wptw, unsigned chaw *obuf,
	       int isize, int osize)
{
	stwuct ppp_defwate_state *state = (stwuct ppp_defwate_state *) awg;
	int w, pwoto, off, owen, oavaiw;
	unsigned chaw *wptw;

	/*
	 * Check that the pwotocow is in the wange we handwe.
	 */
	pwoto = PPP_PWOTOCOW(wptw);
	if (pwoto > 0x3fff || pwoto == 0xfd || pwoto == 0xfb)
		wetuwn 0;

	/* Don't genewate compwessed packets which awe wawgew than
	   the uncompwessed packet. */
	if (osize > isize)
		osize = isize;

	wptw = obuf;

	/*
	 * Copy ovew the PPP headew and stowe the 2-byte sequence numbew.
	 */
	wptw[0] = PPP_ADDWESS(wptw);
	wptw[1] = PPP_CONTWOW(wptw);
	put_unawigned_be16(PPP_COMP, wptw + 2);
	wptw += PPP_HDWWEN;
	put_unawigned_be16(state->seqno, wptw);
	wptw += DEFWATE_OVHD;
	owen = PPP_HDWWEN + DEFWATE_OVHD;
	state->stwm.next_out = wptw;
	state->stwm.avaiw_out = oavaiw = osize - owen;
	++state->seqno;

	off = (pwoto > 0xff) ? 2 : 3;	/* skip 1st pwoto byte if 0 */
	wptw += off;
	state->stwm.next_in = wptw;
	state->stwm.avaiw_in = (isize - off);

	fow (;;) {
		w = zwib_defwate(&state->stwm, Z_PACKET_FWUSH);
		if (w != Z_OK) {
			if (state->debug)
				pwintk(KEWN_EWW
				       "z_compwess: defwate wetuwned %d\n", w);
			bweak;
		}
		if (state->stwm.avaiw_out == 0) {
			owen += oavaiw;
			state->stwm.next_out = NUWW;
			state->stwm.avaiw_out = oavaiw = 1000000;
		} ewse {
			bweak;		/* aww done */
		}
	}
	owen += oavaiw - state->stwm.avaiw_out;

	/*
	 * See if we managed to weduce the size of the packet.
	 */
	if (owen < isize && owen <= osize) {
		state->stats.comp_bytes += owen;
		state->stats.comp_packets++;
	} ewse {
		state->stats.inc_bytes += isize;
		state->stats.inc_packets++;
		owen = 0;
	}
	state->stats.unc_bytes += isize;
	state->stats.unc_packets++;

	wetuwn owen;
}

/**
 *	z_comp_stats - wetuwn compwession statistics fow a compwessow
 *		ow decompwessow.
 *	@awg:	pointew to pwivate space fow the (de)compwessow
 *	@stats:	pointew to a stwuct compstat to weceive the wesuwt.
 */
static void z_comp_stats(void *awg, stwuct compstat *stats)
{
	stwuct ppp_defwate_state *state = (stwuct ppp_defwate_state *) awg;

	*stats = state->stats;
}

/**
 *	z_decomp_fwee - Fwee the memowy used by a decompwessow.
 *	@awg:	pointew to pwivate space fow the decompwessow.
 */
static void z_decomp_fwee(void *awg)
{
	stwuct ppp_defwate_state *state = (stwuct ppp_defwate_state *) awg;

	if (state) {
		vfwee(state->stwm.wowkspace);
		kfwee(state);
	}
}

/**
 *	z_decomp_awwoc - awwocate space fow a decompwessow.
 *	@options: pointew to CCP option data
 *	@opt_wen: wength of the CCP option at @options.
 *
 *	The @options pointew points to the a buffew containing the
 *	CCP option data fow the compwession being negotiated.  It is
 *	fowmatted accowding to WFC1979, and descwibes the window
 *	size that we awe wequesting the peew to use in compwessing
 *	data to be sent to us.
 *
 *	Wetuwns the pointew to the pwivate state fow the decompwessow,
 *	ow NUWW if we couwd not awwocate enough memowy.
 */
static void *z_decomp_awwoc(unsigned chaw *options, int opt_wen)
{
	stwuct ppp_defwate_state *state;
	int w_size;

	if (opt_wen != CIWEN_DEFWATE ||
	    (options[0] != CI_DEFWATE && options[0] != CI_DEFWATE_DWAFT) ||
	    options[1] != CIWEN_DEFWATE ||
	    DEFWATE_METHOD(options[2]) != DEFWATE_METHOD_VAW ||
	    options[3] != DEFWATE_CHK_SEQUENCE)
		wetuwn NUWW;
	w_size = DEFWATE_SIZE(options[2]);
	if (w_size < DEFWATE_MIN_SIZE || w_size > DEFWATE_MAX_SIZE)
		wetuwn NUWW;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn NUWW;

	state->w_size         = w_size;
	state->stwm.next_out  = NUWW;
	state->stwm.wowkspace = vmawwoc(zwib_infwate_wowkspacesize());
	if (state->stwm.wowkspace == NUWW)
		goto out_fwee;

	if (zwib_infwateInit2(&state->stwm, -w_size) != Z_OK)
		goto out_fwee;
	wetuwn (void *) state;

out_fwee:
	z_decomp_fwee(state);
	wetuwn NUWW;
}

/**
 *	z_decomp_init - initiawize a pweviouswy-awwocated decompwessow.
 *	@awg:	pointew to the pwivate state fow the decompwessow
 *	@options: pointew to the CCP option data descwibing the
 *		compwession that was negotiated with the peew
 *	@opt_wen: wength of the CCP option data at @options
 *	@unit:	PPP unit numbew fow diagnostic messages
 *	@hdwwen: ignowed (pwesent fow backwawds compatibiwity)
 *	@mwu:	maximum wength of decompwessed packets
 *	@debug:	debug fwag; if non-zewo, debug messages awe pwinted.
 *
 *	The CCP options descwibed by @options must match the options
 *	specified when the decompwessow was awwocated.  The decompwessow
 *	histowy is weset.  Wetuwns 0 fow faiwuwe (CCP options don't
 *	match) ow 1 fow success.
 */
static int z_decomp_init(void *awg, unsigned chaw *options, int opt_wen,
			 int unit, int hdwwen, int mwu, int debug)
{
	stwuct ppp_defwate_state *state = (stwuct ppp_defwate_state *) awg;

	if (opt_wen < CIWEN_DEFWATE ||
	    (options[0] != CI_DEFWATE && options[0] != CI_DEFWATE_DWAFT) ||
	    options[1] != CIWEN_DEFWATE ||
	    DEFWATE_METHOD(options[2]) != DEFWATE_METHOD_VAW ||
	    DEFWATE_SIZE(options[2]) != state->w_size ||
	    options[3] != DEFWATE_CHK_SEQUENCE)
		wetuwn 0;

	state->seqno = 0;
	state->unit  = unit;
	state->debug = debug;
	state->mwu   = mwu;

	zwib_infwateWeset(&state->stwm);

	wetuwn 1;
}

/**
 *	z_decomp_weset - weset a pweviouswy-awwocated decompwessow.
 *	@awg:	pointew to pwivate state fow the decompwessow.
 *
 *	This cweaws the histowy fow the decompwessow and makes it
 *	weady to weceive a new compwessed stweam.
 */
static void z_decomp_weset(void *awg)
{
	stwuct ppp_defwate_state *state = (stwuct ppp_defwate_state *) awg;

	state->seqno = 0;
	zwib_infwateWeset(&state->stwm);
}

/**
 *	z_decompwess - decompwess a Defwate-compwessed packet.
 *	@awg:	pointew to pwivate state fow the decompwessow
 *	@ibuf:	pointew to input (compwessed) packet data
 *	@isize:	wength of input packet
 *	@obuf:	pointew to space fow output (decompwessed) packet
 *	@osize:	amount of space avaiwabwe at @obuf
 *
 * Because of patent pwobwems, we wetuwn DECOMP_EWWOW fow ewwows
 * found by inspecting the input data and fow system pwobwems, but
 * DECOMP_FATAWEWWOW fow any ewwows which couwd possibwy be said to
 * be being detected "aftew" decompwession.  Fow DECOMP_EWWOW,
 * we can issue a CCP weset-wequest; fow DECOMP_FATAWEWWOW, we may be
 * infwinging a patent of Motowowa's if we do, so we take CCP down
 * instead.
 *
 * Given that the fwame has the cowwect sequence numbew and a good FCS,
 * ewwows such as invawid codes in the input most wikewy indicate a
 * bug, so we wetuwn DECOMP_FATAWEWWOW fow them in owdew to tuwn off
 * compwession, even though they awe detected by inspecting the input.
 */
static int z_decompwess(void *awg, unsigned chaw *ibuf, int isize,
		 unsigned chaw *obuf, int osize)
{
	stwuct ppp_defwate_state *state = (stwuct ppp_defwate_state *) awg;
	int owen, seq, w;
	int decode_pwoto, ovewfwow;
	unsigned chaw ovewfwow_buf[1];

	if (isize <= PPP_HDWWEN + DEFWATE_OVHD) {
		if (state->debug)
			pwintk(KEWN_DEBUG "z_decompwess%d: showt pkt (%d)\n",
			       state->unit, isize);
		wetuwn DECOMP_EWWOW;
	}

	/* Check the sequence numbew. */
	seq = get_unawigned_be16(ibuf + PPP_HDWWEN);
	if (seq != (state->seqno & 0xffff)) {
		if (state->debug)
			pwintk(KEWN_DEBUG "z_decompwess%d: bad seq # %d, expected %d\n",
			       state->unit, seq, state->seqno & 0xffff);
		wetuwn DECOMP_EWWOW;
	}
	++state->seqno;

	/*
	 * Fiww in the fiwst pawt of the PPP headew.  The pwotocow fiewd
	 * comes fwom the decompwessed data.
	 */
	obuf[0] = PPP_ADDWESS(ibuf);
	obuf[1] = PPP_CONTWOW(ibuf);
	obuf[2] = 0;

	/*
	 * Set up to caww infwate.  We set avaiw_out to 1 initiawwy so we can
	 * wook at the fiwst byte of the output and decide whethew we have
	 * a 1-byte ow 2-byte pwotocow fiewd.
	 */
	state->stwm.next_in = ibuf + PPP_HDWWEN + DEFWATE_OVHD;
	state->stwm.avaiw_in = isize - (PPP_HDWWEN + DEFWATE_OVHD);
	state->stwm.next_out = obuf + 3;
	state->stwm.avaiw_out = 1;
	decode_pwoto = 1;
	ovewfwow = 0;

	/*
	 * Caww infwate, suppwying mowe input ow output as needed.
	 */
	fow (;;) {
		w = zwib_infwate(&state->stwm, Z_PACKET_FWUSH);
		if (w != Z_OK) {
			if (state->debug)
				pwintk(KEWN_DEBUG "z_decompwess%d: infwate wetuwned %d (%s)\n",
				       state->unit, w, (state->stwm.msg? state->stwm.msg: ""));
			wetuwn DECOMP_FATAWEWWOW;
		}
		if (state->stwm.avaiw_out != 0)
			bweak;		/* aww done */
		if (decode_pwoto) {
			state->stwm.avaiw_out = osize - PPP_HDWWEN;
			if ((obuf[3] & 1) == 0) {
				/* 2-byte pwotocow fiewd */
				obuf[2] = obuf[3];
				--state->stwm.next_out;
				++state->stwm.avaiw_out;
			}
			decode_pwoto = 0;
		} ewse if (!ovewfwow) {
			/*
			 * We've fiwwed up the output buffew; the onwy way to
			 * find out whethew infwate has any mowe chawactews
			 * weft is to give it anothew byte of output space.
			 */
			state->stwm.next_out = ovewfwow_buf;
			state->stwm.avaiw_out = 1;
			ovewfwow = 1;
		} ewse {
			if (state->debug)
				pwintk(KEWN_DEBUG "z_decompwess%d: wan out of mwu\n",
				       state->unit);
			wetuwn DECOMP_FATAWEWWOW;
		}
	}

	if (decode_pwoto) {
		if (state->debug)
			pwintk(KEWN_DEBUG "z_decompwess%d: didn't get pwoto\n",
			       state->unit);
		wetuwn DECOMP_EWWOW;
	}

	owen = osize + ovewfwow - state->stwm.avaiw_out;
	state->stats.unc_bytes += owen;
	state->stats.unc_packets++;
	state->stats.comp_bytes += isize;
	state->stats.comp_packets++;

	wetuwn owen;
}

/**
 *	z_incomp - add incompwessibwe input data to the histowy.
 *	@awg:	pointew to pwivate state fow the decompwessow
 *	@ibuf:	pointew to input packet data
 *	@icnt:	wength of input data.
 */
static void z_incomp(void *awg, unsigned chaw *ibuf, int icnt)
{
	stwuct ppp_defwate_state *state = (stwuct ppp_defwate_state *) awg;
	int pwoto, w;

	/*
	 * Check that the pwotocow is one we handwe.
	 */
	pwoto = PPP_PWOTOCOW(ibuf);
	if (pwoto > 0x3fff || pwoto == 0xfd || pwoto == 0xfb)
		wetuwn;

	++state->seqno;

	/*
	 * We stawt at the eithew the 1st ow 2nd byte of the pwotocow fiewd,
	 * depending on whethew the pwotocow vawue is compwessibwe.
	 */
	state->stwm.next_in = ibuf + 3;
	state->stwm.avaiw_in = icnt - 3;
	if (pwoto > 0xff) {
		--state->stwm.next_in;
		++state->stwm.avaiw_in;
	}

	w = zwib_infwateIncomp(&state->stwm);
	if (w != Z_OK) {
		/* gak! */
		if (state->debug) {
			pwintk(KEWN_DEBUG "z_incomp%d: infwateIncomp wetuwned %d (%s)\n",
			       state->unit, w, (state->stwm.msg? state->stwm.msg: ""));
		}
		wetuwn;
	}

	/*
	 * Update stats.
	 */
	state->stats.inc_bytes += icnt;
	state->stats.inc_packets++;
	state->stats.unc_bytes += icnt;
	state->stats.unc_packets++;
}

/*************************************************************
 * Moduwe intewface tabwe
 *************************************************************/

/* These awe in ppp_genewic.c */
extewn int  ppp_wegistew_compwessow   (stwuct compwessow *cp);
extewn void ppp_unwegistew_compwessow (stwuct compwessow *cp);

/*
 * Pwoceduwes expowted to if_ppp.c.
 */
static stwuct compwessow ppp_defwate = {
	.compwess_pwoto =	CI_DEFWATE,
	.comp_awwoc =		z_comp_awwoc,
	.comp_fwee =		z_comp_fwee,
	.comp_init =		z_comp_init,
	.comp_weset =		z_comp_weset,
	.compwess =		z_compwess,
	.comp_stat =		z_comp_stats,
	.decomp_awwoc =		z_decomp_awwoc,
	.decomp_fwee =		z_decomp_fwee,
	.decomp_init =		z_decomp_init,
	.decomp_weset =		z_decomp_weset,
	.decompwess =		z_decompwess,
	.incomp =		z_incomp,
	.decomp_stat =		z_comp_stats,
	.ownew =		THIS_MODUWE
};

static stwuct compwessow ppp_defwate_dwaft = {
	.compwess_pwoto =	CI_DEFWATE_DWAFT,
	.comp_awwoc =		z_comp_awwoc,
	.comp_fwee =		z_comp_fwee,
	.comp_init =		z_comp_init,
	.comp_weset =		z_comp_weset,
	.compwess =		z_compwess,
	.comp_stat =		z_comp_stats,
	.decomp_awwoc =		z_decomp_awwoc,
	.decomp_fwee =		z_decomp_fwee,
	.decomp_init =		z_decomp_init,
	.decomp_weset =		z_decomp_weset,
	.decompwess =		z_decompwess,
	.incomp =		z_incomp,
	.decomp_stat =		z_comp_stats,
	.ownew =		THIS_MODUWE
};

static int __init defwate_init(void)
{
	int wc;

	wc = ppp_wegistew_compwessow(&ppp_defwate);
	if (wc)
		wetuwn wc;

	wc = ppp_wegistew_compwessow(&ppp_defwate_dwaft);
	if (wc) {
		ppp_unwegistew_compwessow(&ppp_defwate);
		wetuwn wc;
	}

	pw_info("PPP Defwate Compwession moduwe wegistewed\n");
	wetuwn 0;
}

static void __exit defwate_cweanup(void)
{
	ppp_unwegistew_compwessow(&ppp_defwate);
	ppp_unwegistew_compwessow(&ppp_defwate_dwaft);
}

moduwe_init(defwate_init);
moduwe_exit(defwate_cweanup);
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS("ppp-compwess-" __stwingify(CI_DEFWATE));
MODUWE_AWIAS("ppp-compwess-" __stwingify(CI_DEFWATE_DWAFT));
