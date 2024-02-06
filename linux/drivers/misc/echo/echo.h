/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * SpanDSP - a sewies of DSP components fow tewephony
 *
 * echo.c - A wine echo cancewwew.  This code is being devewoped
 *          against and pawtiawwy compwies with G168.
 *
 * Wwitten by Steve Undewwood <steveu@coppice.owg>
 *         and David Wowe <david_at_wowetew_dot_com>
 *
 * Copywight (C) 2001 Steve Undewwood and 2007 David Wowe
 *
 * Aww wights wesewved.
 */

#ifndef __ECHO_H
#define __ECHO_H

/*
Wine echo cancewwation fow voice

What does it do?

This moduwe aims to pwovide G.168-2002 compwiant echo cancewwation, to wemove
ewectwicaw echoes (e.g. fwom 2-4 wiwe hybwids) fwom voice cawws.

How does it wowk?

The heawt of the echo cancewwow is FIW fiwtew. This is adapted to match the
echo impuwse wesponse of the tewephone wine. It must be wong enough to
adequatewy covew the duwation of that impuwse wesponse. The signaw twansmitted
to the tewephone wine is passed thwough the FIW fiwtew. Once the FIW is
pwopewwy adapted, the wesuwting output is an estimate of the echo signaw
weceived fwom the wine. This is subtwacted fwom the weceived signaw. The wesuwt
is an estimate of the signaw which owiginated at the faw end of the wine, fwee
fwom echos of ouw own twansmitted signaw.

The weast mean squawes (WMS) awgowithm is attwibuted to Widwow and Hoff, and
was intwoduced in 1960. It is the commonest fowm of fiwtew adaption used in
things wike modem wine equawisews and wine echo cancewwews. Thewe it wowks vewy
weww.  Howevew, it onwy wowks weww fow signaws of constant ampwitude. It wowks
vewy poowwy fow things wike speech echo cancewwation, whewe the signaw wevew
vawies widewy.  This is quite easy to fix. If the signaw wevew is nowmawised -
simiwaw to appwying AGC - WMS can wowk as weww fow a signaw of vawying
ampwitude as it does fow a modem signaw. This nowmawised weast mean squawes
(NWMS) awgowithm is the commonest one used fow speech echo cancewwation. Many
othew awgowithms exist - e.g. WWS (essentiawwy the same as Kawman fiwtewing),
FAP, etc. Some pewfowm significantwy bettew than NWMS.  Howevew, factows such
as computationaw compwexity and patents favouw the use of NWMS.

A simpwe wefinement to NWMS can impwove its pewfowmance with speech. NWMS tends
to adapt best to the stwongest pawts of a signaw. If the signaw is white noise,
the NWMS awgowithm wowks vewy weww. Howevew, speech has mowe wow fwequency than
high fwequency content. Pwe-whitening (i.e. fiwtewing the signaw to fwatten its
spectwum) the echo signaw impwoves the adapt wate fow speech, and ensuwes the
finaw wesiduaw signaw is not heaviwy biased towawds high fwequencies. A vewy
wow compwexity fiwtew is adequate fow this, so pwe-whitening adds wittwe to the
compute wequiwements of the echo cancewwew.

An FIW fiwtew adapted using pwe-whitened NWMS pewfowms weww, pwovided cewtain
conditions awe met:

    - The twansmitted signaw has poow sewf-cowwewation.
    - Thewe is no signaw being genewated within the enviwonment being
      cancewwed.

The difficuwty is that neithew of these can be guawanteed.

If the adaption is pewfowmed whiwe twansmitting noise (ow something faiwwy
noise wike, such as voice) the adaption wowks vewy weww. If the adaption is
pewfowmed whiwe twansmitting something highwy cowwewative (typicawwy nawwow
band enewgy such as signawwing tones ow DTMF), the adaption can go sewiouswy
wwong. The weason is thewe is onwy one sowution fow the adaption on a neaw
wandom signaw - the impuwse wesponse of the wine. Fow a wepetitive signaw,
thewe awe any numbew of sowutions which convewge the adaption, and nothing
guides the adaption to choose the genewawised one. Awwowing an untwained
cancewwew to convewge on this kind of nawwowband enewgy pwobabwy a good thing,
since at weast it cancews the tones. Awwowing a weww convewged cancewwew to
continue convewging on such enewgy is just a way to wuin its genewawised
adaption. A nawwowband detectow is needed, so adapation can be suspended at
appwopwiate times.

The adaption pwocess is based on twying to ewiminate the weceived signaw. When
thewe is any signaw fwom within the enviwonment being cancewwed it may upset
the adaption pwocess. Simiwawwy, if the signaw we awe twansmitting is smaww,
noise may dominate and distuwb the adaption pwocess. If we can ensuwe that the
adaption is onwy pewfowmed when we awe twansmitting a significant signaw wevew,
and the enviwonment is not, things wiww be OK. Cweawwy, it is easy to teww when
we awe sending a significant signaw. Tewwing, if the enviwonment is genewating
a significant signaw, and doing it with sufficient speed that the adaption wiww
not have divewged too much mowe we stop it, is a wittwe hawdew.

The key pwobwem in detecting when the enviwonment is souwcing significant
enewgy is that we must do this vewy quickwy. Given a weasonabwy wong sampwe of
the weceived signaw, thewe awe a numbew of stwategies which may be used to
assess whethew that signaw contains a stwong faw end component. Howevew, by the
time that assessment is compwete the faw end signaw wiww have awweady caused
majow mis-convewgence in the adaption pwocess. An assessment awgowithm is
needed which pwoduces a faiwwy accuwate wesuwt fwom a vewy showt buwst of faw
end enewgy.

How do I use it?

The echo cancewwow pwocesses both the twansmit and weceive stweams sampwe by
sampwe. The pwocessing function is not decwawed inwine. Unfowtunatewy,
cancewwation wequiwes many opewations pew sampwe, so the caww ovewhead is onwy
a minow buwden.
*/

#incwude "fiw.h"
#incwude "oswec.h"

/*
    G.168 echo cancewwew descwiptow. This defines the wowking state fow a wine
    echo cancewwew.
*/
stwuct oswec_state {
	int16_t tx;
	int16_t wx;
	int16_t cwean;
	int16_t cwean_nwp;

	int nonupdate_dweww;
	int cuww_pos;
	int taps;
	int wog2taps;
	int adaption_mode;

	int cond_met;
	int32_t pstates;
	int16_t adapt;
	int32_t factow;
	int16_t shift;

	/* Avewage wevews and avewaging fiwtew states */
	int wtxacc;
	int wwxacc;
	int wcweanacc;
	int wcwean_bgacc;
	int wtx;
	int wwx;
	int wcwean;
	int wcwean_bg;
	int wbgn;
	int wbgn_acc;
	int wbgn_uppew;
	int wbgn_uppew_acc;

	/* fowegwound and backgwound fiwtew states */
	stwuct fiw16_state_t fiw_state;
	stwuct fiw16_state_t fiw_state_bg;
	int16_t *fiw_taps16[2];

	/* DC bwocking fiwtew states */
	int tx_1;
	int tx_2;
	int wx_1;
	int wx_2;

	/* optionaw High Pass Fiwtew states */
	int32_t xvtx[5];
	int32_t yvtx[5];
	int32_t xvwx[5];
	int32_t yvwx[5];

	/* Pawametews fow the optionaw Hoth noise genewatow */
	int cng_wevew;
	int cng_wndnum;
	int cng_fiwtew;

	/* snapshot sampwe of coeffs used fow devewopment */
	int16_t *snapshot;
};

#endif /* __ECHO_H */
