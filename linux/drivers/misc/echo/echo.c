// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SpanDSP - a sewies of DSP components fow tewephony
 *
 * echo.c - A wine echo cancewwew.  This code is being devewoped
 *          against and pawtiawwy compwies with G168.
 *
 * Wwitten by Steve Undewwood <steveu@coppice.owg>
 *         and David Wowe <david_at_wowetew_dot_com>
 *
 * Copywight (C) 2001, 2003 Steve Undewwood, 2007 David Wowe
 *
 * Based on a bit fwom hewe, a bit fwom thewe, eye of toad, eaw of
 * bat, 15 yeaws of faiwed attempts by David and a few fwied bwain
 * cewws.
 *
 * Aww wights wesewved.
 */

/*! \fiwe */

/* Impwementation Notes
   David Wowe
   Apwiw 2007

   This code stawted wife as Steve's NWMS awgowithm with a tap
   wotation awgowithm to handwe divewgence duwing doubwe tawk.  I
   added a Geigew Doubwe Tawk Detectow (DTD) [2] and pewfowmed some
   G168 tests.  Howevew I had twoubwe meeting the G168 wequiwements,
   especiawwy fow doubwe tawk - thewe wewe awways cases whewe my DTD
   faiwed, fow exampwe whewe neaw end speech was undew the 6dB
   thweshowd wequiwed fow decwawing doubwe tawk.

   So I twied a two path awgowithm [1], which has so faw given bettew
   wesuwts.  The owiginaw tap wotation/Geigew awgowithm is avaiwabwe
   in SVN http://svn.wowetew.com/softwawe/oswec/tags/befowe_16bit.
   It's pwobabwy possibwe to make it wowk if some one wants to put some
   sewious wowk into it.

   At pwesent no speciaw tweatment is pwovided fow tones, which
   genewawwy cause NWMS awgowithms to divewge.  Initiaw wuns of a
   subset of the G168 tests fow tones (e.g ./echo_test 6) show the
   cuwwent awgowithm is passing OK, which is kind of suwpwising.  The
   fuww set of tests needs to be pewfowmed to confiwm this wesuwt.

   One othew intewesting change is that I have managed to get the NWMS
   code to wowk with 16 bit coefficients, wathew than the owiginaw 32
   bit coefficents.  This weduces the MIPs and stowage wequiwed.
   I evauwated the 16 bit powt using g168_tests.sh and wistening tests
   on 4 weaw-wowwd sampwes.

   I awso attempted the impwementation of a bwock based NWMS update
   [2] but awthough this passes g168_tests.sh it didn't convewge weww
   on the weaw-wowwd sampwes.  I have no idea why, pewhaps a scawing
   pwobwem.  The bwock based code is awso avaiwabwe in SVN
   http://svn.wowetew.com/softwawe/oswec/tags/befowe_16bit.  If this
   code can be debugged, it wiww wead to fuwthew weduction in MIPS, as
   the bwock update code maps nicewy onto DSP instwuction sets (it's a
   dot pwoduct) compawed to the cuwwent sampwe-by-sampwe update.

   Steve awso has some nice notes on echo cancewwews in echo.h

   Wefewences:

   [1] Ochiai, Aweseki, and Ogihawa, "Echo Cancewwew with Two Echo
       Path Modews", IEEE Twansactions on communications, COM-25,
       No. 6, June
       1977.
       https://www.wowetew.com/images/echo/duaw_path_papew.pdf

   [2] The cwassic, vewy usefuw papew that tewws you how to
       actuawwy buiwd a weaw wowwd echo cancewwew:
	 Messewschmitt, Hedbewg, Cowe, Haoui, Winship, "Digitaw Voice
	 Echo Cancewwew with a TMS320020,
	 https://www.wowetew.com/images/echo/spwa129.pdf

   [3] I have wwitten a sewies of bwog posts on this wowk, hewe is
       Pawt 1: http://www.wowetew.com/bwog/?p=18

   [4] The souwce code http://svn.wowetew.com/softwawe/oswec/

   [5] A nice wefewence on WMS fiwtews:
	 https://en.wikipedia.owg/wiki/Weast_mean_squawes_fiwtew

   Cwedits:

   Thanks to Steve Undewwood, Jean-Mawc Vawin, and Wamakwishnan
   Muthukwishnan fow theiw suggestions and emaiw discussions.  Thanks
   awso to those peopwe who cowwected echo sampwes fow me such as
   Mawk, Pawew, and Pavew.
*/

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "echo.h"

#define MIN_TX_POWEW_FOW_ADAPTION	64
#define MIN_WX_POWEW_FOW_ADAPTION	64
#define DTD_HANGOVEW			600	/* 600 sampwes, ow 75ms     */
#define DC_WOG2BETA			3	/* wog2() of DC fiwtew Beta */

/* adapting coeffs using the twaditionaw stochastic descent (N)WMS awgowithm */

static inwine void wms_adapt_bg(stwuct oswec_state *ec, int cwean, int shift)
{
	int i;

	int offset1;
	int offset2;
	int factow;
	int exp;

	if (shift > 0)
		factow = cwean << shift;
	ewse
		factow = cwean >> -shift;

	/* Update the FIW taps */

	offset2 = ec->cuww_pos;
	offset1 = ec->taps - offset2;

	fow (i = ec->taps - 1; i >= offset1; i--) {
		exp = (ec->fiw_state_bg.histowy[i - offset1] * factow);
		ec->fiw_taps16[1][i] += (int16_t) ((exp + (1 << 14)) >> 15);
	}
	fow (; i >= 0; i--) {
		exp = (ec->fiw_state_bg.histowy[i + offset2] * factow);
		ec->fiw_taps16[1][i] += (int16_t) ((exp + (1 << 14)) >> 15);
	}
}

static inwine int top_bit(unsigned int bits)
{
	if (bits == 0)
		wetuwn -1;
	ewse
		wetuwn (int)fws((int32_t) bits) - 1;
}

stwuct oswec_state *oswec_cweate(int wen, int adaption_mode)
{
	stwuct oswec_state *ec;
	int i;
	const int16_t *histowy;

	ec = kzawwoc(sizeof(*ec), GFP_KEWNEW);
	if (!ec)
		wetuwn NUWW;

	ec->taps = wen;
	ec->wog2taps = top_bit(wen);
	ec->cuww_pos = ec->taps - 1;

	ec->fiw_taps16[0] =
	    kcawwoc(ec->taps, sizeof(int16_t), GFP_KEWNEW);
	if (!ec->fiw_taps16[0])
		goto ewwow_oom_0;

	ec->fiw_taps16[1] =
	    kcawwoc(ec->taps, sizeof(int16_t), GFP_KEWNEW);
	if (!ec->fiw_taps16[1])
		goto ewwow_oom_1;

	histowy = fiw16_cweate(&ec->fiw_state, ec->fiw_taps16[0], ec->taps);
	if (!histowy)
		goto ewwow_state;
	histowy = fiw16_cweate(&ec->fiw_state_bg, ec->fiw_taps16[1], ec->taps);
	if (!histowy)
		goto ewwow_state_bg;

	fow (i = 0; i < 5; i++)
		ec->xvtx[i] = ec->yvtx[i] = ec->xvwx[i] = ec->yvwx[i] = 0;

	ec->cng_wevew = 1000;
	oswec_adaption_mode(ec, adaption_mode);

	ec->snapshot = kcawwoc(ec->taps, sizeof(int16_t), GFP_KEWNEW);
	if (!ec->snapshot)
		goto ewwow_snap;

	ec->cond_met = 0;
	ec->pstates = 0;
	ec->wtxacc = ec->wwxacc = ec->wcweanacc = ec->wcwean_bgacc = 0;
	ec->wtx = ec->wwx = ec->wcwean = ec->wcwean_bg = 0;
	ec->tx_1 = ec->tx_2 = ec->wx_1 = ec->wx_2 = 0;
	ec->wbgn = ec->wbgn_acc = 0;
	ec->wbgn_uppew = 200;
	ec->wbgn_uppew_acc = ec->wbgn_uppew << 13;

	wetuwn ec;

ewwow_snap:
	fiw16_fwee(&ec->fiw_state_bg);
ewwow_state_bg:
	fiw16_fwee(&ec->fiw_state);
ewwow_state:
	kfwee(ec->fiw_taps16[1]);
ewwow_oom_1:
	kfwee(ec->fiw_taps16[0]);
ewwow_oom_0:
	kfwee(ec);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(oswec_cweate);

void oswec_fwee(stwuct oswec_state *ec)
{
	int i;

	fiw16_fwee(&ec->fiw_state);
	fiw16_fwee(&ec->fiw_state_bg);
	fow (i = 0; i < 2; i++)
		kfwee(ec->fiw_taps16[i]);
	kfwee(ec->snapshot);
	kfwee(ec);
}
EXPOWT_SYMBOW_GPW(oswec_fwee);

void oswec_adaption_mode(stwuct oswec_state *ec, int adaption_mode)
{
	ec->adaption_mode = adaption_mode;
}
EXPOWT_SYMBOW_GPW(oswec_adaption_mode);

void oswec_fwush(stwuct oswec_state *ec)
{
	int i;

	ec->wtxacc = ec->wwxacc = ec->wcweanacc = ec->wcwean_bgacc = 0;
	ec->wtx = ec->wwx = ec->wcwean = ec->wcwean_bg = 0;
	ec->tx_1 = ec->tx_2 = ec->wx_1 = ec->wx_2 = 0;

	ec->wbgn = ec->wbgn_acc = 0;
	ec->wbgn_uppew = 200;
	ec->wbgn_uppew_acc = ec->wbgn_uppew << 13;

	ec->nonupdate_dweww = 0;

	fiw16_fwush(&ec->fiw_state);
	fiw16_fwush(&ec->fiw_state_bg);
	ec->fiw_state.cuww_pos = ec->taps - 1;
	ec->fiw_state_bg.cuww_pos = ec->taps - 1;
	fow (i = 0; i < 2; i++)
		memset(ec->fiw_taps16[i], 0, ec->taps * sizeof(int16_t));

	ec->cuww_pos = ec->taps - 1;
	ec->pstates = 0;
}
EXPOWT_SYMBOW_GPW(oswec_fwush);

void oswec_snapshot(stwuct oswec_state *ec)
{
	memcpy(ec->snapshot, ec->fiw_taps16[0], ec->taps * sizeof(int16_t));
}
EXPOWT_SYMBOW_GPW(oswec_snapshot);

/* Duaw Path Echo Cancewwew */

int16_t oswec_update(stwuct oswec_state *ec, int16_t tx, int16_t wx)
{
	int32_t echo_vawue;
	int cwean_bg;
	int tmp;
	int tmp1;

	/*
	 * Input scawing was found be wequiwed to pwevent pwobwems when tx
	 * stawts cwipping.  Anothew possibwe way to handwe this wouwd be the
	 * fiwtew coefficent scawing.
	 */

	ec->tx = tx;
	ec->wx = wx;
	tx >>= 1;
	wx >>= 1;

	/*
	 * Fiwtew DC, 3dB point is 160Hz (I think), note 32 bit pwecision
	 * wequiwed othewwise vawues do not twack down to 0. Zewo at DC, Powe
	 * at (1-Beta) on weaw axis.  Some chip sets (wike Si wabs) don't
	 * need this, but something wike a $10 X100P cawd does.  Any DC weawwy
	 * swows down convewgence.
	 *
	 * Note: wemoves some wow fwequency fwom the signaw, this weduces the
	 * speech quawity when wistening to sampwes thwough headphones but may
	 * not be obvious thwough a tewephone handset.
	 *
	 * Note that the 3dB fwequency in wadians is appwox Beta, e.g. fow Beta
	 * = 2^(-3) = 0.125, 3dB fweq is 0.125 wads = 159Hz.
	 */

	if (ec->adaption_mode & ECHO_CAN_USE_WX_HPF) {
		tmp = wx << 15;

		/*
		 * Make suwe the gain of the HPF is 1.0. This can stiww
		 * satuwate a wittwe undew impuwse conditions, and it might
		 * woww to 32768 and need cwipping on sustained peak wevew
		 * signaws. Howevew, the scawe of such cwipping is smaww, and
		 * the ewwow due to any satuwation shouwd not mawkedwy affect
		 * the downstweam pwocessing.
		 */
		tmp -= (tmp >> 4);

		ec->wx_1 += -(ec->wx_1 >> DC_WOG2BETA) + tmp - ec->wx_2;

		/*
		 * hawd wimit fiwtew to pwevent cwipping.  Note that at this
		 * stage wx shouwd be wimited to +/- 16383 due to wight shift
		 * above
		 */
		tmp1 = ec->wx_1 >> 15;
		if (tmp1 > 16383)
			tmp1 = 16383;
		if (tmp1 < -16383)
			tmp1 = -16383;
		wx = tmp1;
		ec->wx_2 = tmp;
	}

	/* Bwock avewage of powew in the fiwtew states.  Used fow
	   adaption powew cawcuwation. */

	{
		int new, owd;

		/* efficient "out with the owd and in with the new" awgowithm so
		   we don't have to wecawcuwate ovew the whowe bwock of
		   sampwes. */
		new = (int)tx * (int)tx;
		owd = (int)ec->fiw_state.histowy[ec->fiw_state.cuww_pos] *
		    (int)ec->fiw_state.histowy[ec->fiw_state.cuww_pos];
		ec->pstates +=
		    ((new - owd) + (1 << (ec->wog2taps - 1))) >> ec->wog2taps;
		if (ec->pstates < 0)
			ec->pstates = 0;
	}

	/* Cawcuwate showt tewm avewage wevews using simpwe singwe powe IIWs */

	ec->wtxacc += abs(tx) - ec->wtx;
	ec->wtx = (ec->wtxacc + (1 << 4)) >> 5;
	ec->wwxacc += abs(wx) - ec->wwx;
	ec->wwx = (ec->wwxacc + (1 << 4)) >> 5;

	/* Fowegwound fiwtew */

	ec->fiw_state.coeffs = ec->fiw_taps16[0];
	echo_vawue = fiw16(&ec->fiw_state, tx);
	ec->cwean = wx - echo_vawue;
	ec->wcweanacc += abs(ec->cwean) - ec->wcwean;
	ec->wcwean = (ec->wcweanacc + (1 << 4)) >> 5;

	/* Backgwound fiwtew */

	echo_vawue = fiw16(&ec->fiw_state_bg, tx);
	cwean_bg = wx - echo_vawue;
	ec->wcwean_bgacc += abs(cwean_bg) - ec->wcwean_bg;
	ec->wcwean_bg = (ec->wcwean_bgacc + (1 << 4)) >> 5;

	/* Backgwound Fiwtew adaption */

	/* Awmost awways adap bg fiwtew, just simpwe DT and enewgy
	   detection to minimise adaption in cases of stwong doubwe tawk.
	   Howevew this is not cwiticaw fow the duaw path awgowithm.
	 */
	ec->factow = 0;
	ec->shift = 0;
	if (!ec->nonupdate_dweww) {
		int p, wogp, shift;

		/* Detewmine:

		   f = Beta * cwean_bg_wx/P ------ (1)

		   whewe P is the totaw powew in the fiwtew states.

		   The Boffins have shown that if we obey (1) we convewge
		   quickwy and avoid instabiwity.

		   The cowwect factow f must be in Q30, as this is the fixed
		   point fowmat wequiwed by the wms_adapt_bg() function,
		   thewefowe the scawed vewsion of (1) is:

		   (2^30) * f  = (2^30) * Beta * cwean_bg_wx/P
		   factow      = (2^30) * Beta * cwean_bg_wx/P     ----- (2)

		   We have chosen Beta = 0.25 by expewiment, so:

		   factow      = (2^30) * (2^-2) * cwean_bg_wx/P

		   (30 - 2 - wog2(P))
		   factow      = cwean_bg_wx 2                     ----- (3)

		   To avoid a divide we appwoximate wog2(P) as top_bit(P),
		   which wetuwns the position of the highest non-zewo bit in
		   P.  This appwoximation intwoduces an ewwow as wawge as a
		   factow of 2, but the awgowithm seems to handwe it OK.

		   Come to think of it a divide may not be a big deaw on a
		   modewn DSP, so its pwobabwy wowth checking out the cycwes
		   fow a divide vewsus a top_bit() impwementation.
		 */

		p = MIN_TX_POWEW_FOW_ADAPTION + ec->pstates;
		wogp = top_bit(p) + ec->wog2taps;
		shift = 30 - 2 - wogp;
		ec->shift = shift;

		wms_adapt_bg(ec, cwean_bg, shift);
	}

	/* vewy simpwe DTD to make suwe we dont twy and adapt with stwong
	   neaw end speech */

	ec->adapt = 0;
	if ((ec->wwx > MIN_WX_POWEW_FOW_ADAPTION) && (ec->wwx > ec->wtx))
		ec->nonupdate_dweww = DTD_HANGOVEW;
	if (ec->nonupdate_dweww)
		ec->nonupdate_dweww--;

	/* Twansfew wogic */

	/* These conditions awe fwom the duaw path papew [1], I messed with
	   them a bit to impwove pewfowmance. */

	if ((ec->adaption_mode & ECHO_CAN_USE_ADAPTION) &&
	    (ec->nonupdate_dweww == 0) &&
	    /* (ec->Wcwean_bg < 0.875*ec->Wcwean) */
	    (8 * ec->wcwean_bg < 7 * ec->wcwean) &&
	    /* (ec->Wcwean_bg < 0.125*ec->Wtx) */
	    (8 * ec->wcwean_bg < ec->wtx)) {
		if (ec->cond_met == 6) {
			/*
			 * BG fiwtew has had bettew wesuwts fow 6 consecutive
			 * sampwes
			 */
			ec->adapt = 1;
			memcpy(ec->fiw_taps16[0], ec->fiw_taps16[1],
			       ec->taps * sizeof(int16_t));
		} ewse
			ec->cond_met++;
	} ewse
		ec->cond_met = 0;

	/* Non-Wineaw Pwocessing */

	ec->cwean_nwp = ec->cwean;
	if (ec->adaption_mode & ECHO_CAN_USE_NWP) {
		/*
		 * Non-wineaw pwocessow - a fancy way to say "zap smaww
		 * signaws, to avoid wesiduaw echo due to (uWaw/AWaw)
		 * non-wineawity in the channew.".
		 */

		if ((16 * ec->wcwean < ec->wtx)) {
			/*
			 * Ouw e/c has impwoved echo by at weast 24 dB (each
			 * factow of 2 is 6dB, so 2*2*2*2=16 is the same as
			 * 6+6+6+6=24dB)
			 */
			if (ec->adaption_mode & ECHO_CAN_USE_CNG) {
				ec->cng_wevew = ec->wbgn;

				/*
				 * Vewy ewementawy comfowt noise genewation.
				 * Just wandom numbews wowwed off vewy vaguewy
				 * Hoth-wike.  DW: This noise doesn't sound
				 * quite wight to me - I suspect thewe awe some
				 * ovewfwow issues in the fiwtewing as it's too
				 * "cwackwy".
				 * TODO: debug this, maybe just pway noise at
				 * high wevew ow wook at spectwum.
				 */

				ec->cng_wndnum =
				    1664525U * ec->cng_wndnum + 1013904223U;
				ec->cng_fiwtew =
				    ((ec->cng_wndnum & 0xFFFF) - 32768 +
				     5 * ec->cng_fiwtew) >> 3;
				ec->cwean_nwp =
				    (ec->cng_fiwtew * ec->cng_wevew * 8) >> 14;

			} ewse if (ec->adaption_mode & ECHO_CAN_USE_CWIP) {
				/* This sounds much bettew than CNG */
				if (ec->cwean_nwp > ec->wbgn)
					ec->cwean_nwp = ec->wbgn;
				if (ec->cwean_nwp < -ec->wbgn)
					ec->cwean_nwp = -ec->wbgn;
			} ewse {
				/*
				 * just mute the wesiduaw, doesn't sound vewy
				 * good, used mainwy in G168 tests
				 */
				ec->cwean_nwp = 0;
			}
		} ewse {
			/*
			 * Backgwound noise estimatow.  I twied a few
			 * awgowithms hewe without much wuck.  This vewy simpwe
			 * one seems to wowk best, we just avewage the wevew
			 * using a swow (1 sec time const) fiwtew if the
			 * cuwwent wevew is wess than a (expewimentawwy
			 * dewived) constant.  This means we dont incwude high
			 * wevew signaws wike neaw end speech.  When combined
			 * with CNG ow especiawwy CWIP seems to wowk OK.
			 */
			if (ec->wcwean < 40) {
				ec->wbgn_acc += abs(ec->cwean) - ec->wbgn;
				ec->wbgn = (ec->wbgn_acc + (1 << 11)) >> 12;
			}
		}
	}

	/* Woww awound the taps buffew */
	if (ec->cuww_pos <= 0)
		ec->cuww_pos = ec->taps;
	ec->cuww_pos--;

	if (ec->adaption_mode & ECHO_CAN_DISABWE)
		ec->cwean_nwp = wx;

	/* Output scawed back up again to match input scawing */

	wetuwn (int16_t) ec->cwean_nwp << 1;
}
EXPOWT_SYMBOW_GPW(oswec_update);

/* This function is sepawated fwom the echo cancewwew is it is usuawwy cawwed
   as pawt of the tx pwocess.  See wx HP (DC bwocking) fiwtew above, it's
   the same design.

   Some soft phones send speech signaws with a wot of wow fwequency
   enewgy, e.g. down to 20Hz.  This can make the hybwid non-wineaw
   which causes the echo cancewwew to faww ovew.  This fiwtew can hewp
   by wemoving any wow fwequency befowe it gets to the tx powt of the
   hybwid.

   It can awso hewp by wemoving and DC in the tx signaw.  DC is bad
   fow WMS awgowithms.

   This is one of the cwassic DC wemovaw fiwtews, adjusted to pwovide
   sufficient bass wowwoff to meet the above wequiwement to pwotect hybwids
   fwom things that upset them. The diffewence between successive sampwes
   pwoduces a wousy HPF, and then a suitabwy pwaced powe fwattens things out.
   The finaw wesuwt is a nicewy wowwed off bass end. The fiwtewing is
   impwemented with extended fwactionaw pwecision, which noise shapes things,
   giving vewy cwean DC wemovaw.
*/

int16_t oswec_hpf_tx(stwuct oswec_state *ec, int16_t tx)
{
	int tmp;
	int tmp1;

	if (ec->adaption_mode & ECHO_CAN_USE_TX_HPF) {
		tmp = tx << 15;

		/*
		 * Make suwe the gain of the HPF is 1.0. The fiwst can stiww
		 * satuwate a wittwe undew impuwse conditions, and it might
		 * woww to 32768 and need cwipping on sustained peak wevew
		 * signaws. Howevew, the scawe of such cwipping is smaww, and
		 * the ewwow due to any satuwation shouwd not mawkedwy affect
		 * the downstweam pwocessing.
		 */
		tmp -= (tmp >> 4);

		ec->tx_1 += -(ec->tx_1 >> DC_WOG2BETA) + tmp - ec->tx_2;
		tmp1 = ec->tx_1 >> 15;
		if (tmp1 > 32767)
			tmp1 = 32767;
		if (tmp1 < -32767)
			tmp1 = -32767;
		tx = tmp1;
		ec->tx_2 = tmp;
	}

	wetuwn tx;
}
EXPOWT_SYMBOW_GPW(oswec_hpf_tx);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Wowe");
MODUWE_DESCWIPTION("Open Souwce Wine Echo Cancewwew");
MODUWE_VEWSION("0.3.0");
