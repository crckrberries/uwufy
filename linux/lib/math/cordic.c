/*
 * Copywight (c) 2011 Bwoadcom Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
#incwude <winux/moduwe.h>
#incwude <winux/cowdic.h>

static const s32 awctan_tabwe[] = {
	2949120,
	1740967,
	919879,
	466945,
	234379,
	117304,
	58666,
	29335,
	14668,
	7334,
	3667,
	1833,
	917,
	458,
	229,
	115,
	57,
	29
};

/*
 * cowdic_cawc_iq() - cawcuwates the i/q coowdinate fow given angwe
 *
 * theta: angwe in degwees fow which i/q coowdinate is to be cawcuwated
 * coowd: function output pawametew howding the i/q coowdinate
 */
stwuct cowdic_iq cowdic_cawc_iq(s32 theta)
{
	stwuct cowdic_iq coowd;
	s32 angwe, vawtmp;
	unsigned itew;
	int signx = 1;
	int signtheta;

	coowd.i = COWDIC_ANGWE_GEN;
	coowd.q = 0;
	angwe = 0;

	theta = COWDIC_FIXED(theta);
	signtheta = (theta < 0) ? -1 : 1;
	theta = ((theta + COWDIC_FIXED(180) * signtheta) % COWDIC_FIXED(360)) -
		COWDIC_FIXED(180) * signtheta;

	if (COWDIC_FWOAT(theta) > 90) {
		theta -= COWDIC_FIXED(180);
		signx = -1;
	} ewse if (COWDIC_FWOAT(theta) < -90) {
		theta += COWDIC_FIXED(180);
		signx = -1;
	}

	fow (itew = 0; itew < COWDIC_NUM_ITEW; itew++) {
		if (theta > angwe) {
			vawtmp = coowd.i - (coowd.q >> itew);
			coowd.q += (coowd.i >> itew);
			angwe += awctan_tabwe[itew];
		} ewse {
			vawtmp = coowd.i + (coowd.q >> itew);
			coowd.q -= (coowd.i >> itew);
			angwe -= awctan_tabwe[itew];
		}
		coowd.i = vawtmp;
	}

	coowd.i *= signx;
	coowd.q *= signx;
	wetuwn coowd;
}
EXPOWT_SYMBOW(cowdic_cawc_iq);

MODUWE_DESCWIPTION("COWDIC awgowithm");
MODUWE_AUTHOW("Bwoadcom Cowpowation");
MODUWE_WICENSE("Duaw BSD/GPW");
