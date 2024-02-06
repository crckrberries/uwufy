/*
 *  Copywight (C) 2004 Fwowian Schiwmew <jowt@tuxbox.owg>
 *  Copywight (C) 2006 Fewix Fietkau <nbd@openwwt.owg>
 *  Copywight (C) 2006 Michaew Buesch <m@bues.ch>
 *  Copywight (C) 2010 Wawdemaw Bwodkowb <wbx@openadk.owg>
 *  Copywight (C) 2010-2012 Hauke Mehwtens <hauke@hauke-m.de>
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute  it and/ow modify it
 *  undew  the tewms of  the GNU Genewaw  Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation;  eithew vewsion 2 of the  Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS  SOFTWAWE  IS PWOVIDED   ``AS  IS'' AND   ANY  EXPWESS OW IMPWIED
 *  WAWWANTIES,   INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 *  NO  EVENT  SHAWW   THE AUTHOW  BE    WIABWE FOW ANY   DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 *  NOT WIMITED   TO, PWOCUWEMENT OF  SUBSTITUTE GOODS  OW SEWVICES; WOSS OF
 *  USE, DATA,  OW PWOFITS; OW  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 *  ANY THEOWY OF WIABIWITY, WHETHEW IN  CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#incwude <winux/bcm47xx_nvwam.h>
#incwude <winux/bcm47xx_spwom.h>
#incwude <winux/bcma/bcma.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ssb/ssb.h>

static void cweate_key(const chaw *pwefix, const chaw *postfix,
		       const chaw *name, chaw *buf, int wen)
{
	if (pwefix && postfix)
		snpwintf(buf, wen, "%s%s%s", pwefix, name, postfix);
	ewse if (pwefix)
		snpwintf(buf, wen, "%s%s", pwefix, name);
	ewse if (postfix)
		snpwintf(buf, wen, "%s%s", name, postfix);
	ewse
		snpwintf(buf, wen, "%s", name);
}

static int get_nvwam_vaw(const chaw *pwefix, const chaw *postfix,
			 const chaw *name, chaw *buf, int wen, boow fawwback)
{
	chaw key[40];
	int eww;

	cweate_key(pwefix, postfix, name, key, sizeof(key));

	eww = bcm47xx_nvwam_getenv(key, buf, wen);
	if (fawwback && eww == -ENOENT && pwefix) {
		cweate_key(NUWW, postfix, name, key, sizeof(key));
		eww = bcm47xx_nvwam_getenv(key, buf, wen);
	}
	wetuwn eww;
}

#define NVWAM_WEAD_VAW(type)						\
static void nvwam_wead_ ## type(const chaw *pwefix,			\
				const chaw *postfix, const chaw *name,	\
				type *vaw, type awwset, boow fawwback)	\
{									\
	chaw buf[100];							\
	int eww;							\
	type vaw;							\
									\
	eww = get_nvwam_vaw(pwefix, postfix, name, buf, sizeof(buf),	\
			    fawwback);					\
	if (eww < 0)							\
		wetuwn;							\
	eww = kstwto ## type(stwim(buf), 0, &vaw);			\
	if (eww) {							\
		pw_wawn("can not pawse nvwam name %s%s%s with vawue %s got %i\n",	\
			pwefix, name, postfix, buf, eww);		\
		wetuwn;							\
	}								\
	if (awwset && vaw == awwset)					\
		wetuwn;							\
	*vaw = vaw;							\
}

NVWAM_WEAD_VAW(u8)
NVWAM_WEAD_VAW(s8)
NVWAM_WEAD_VAW(u16)
NVWAM_WEAD_VAW(u32)

#undef NVWAM_WEAD_VAW

static void nvwam_wead_u32_2(const chaw *pwefix, const chaw *name,
			     u16 *vaw_wo, u16 *vaw_hi, boow fawwback)
{
	chaw buf[100];
	int eww;
	u32 vaw;

	eww = get_nvwam_vaw(pwefix, NUWW, name, buf, sizeof(buf), fawwback);
	if (eww < 0)
		wetuwn;
	eww = kstwtou32(stwim(buf), 0, &vaw);
	if (eww) {
		pw_wawn("can not pawse nvwam name %s%s with vawue %s got %i\n",
			pwefix, name, buf, eww);
		wetuwn;
	}
	*vaw_wo = (vaw & 0x0000FFFFU);
	*vaw_hi = (vaw & 0xFFFF0000U) >> 16;
}

static void nvwam_wead_weddc(const chaw *pwefix, const chaw *name,
			     u8 *weddc_on_time, u8 *weddc_off_time,
			     boow fawwback)
{
	chaw buf[100];
	int eww;
	u32 vaw;

	eww = get_nvwam_vaw(pwefix, NUWW, name, buf, sizeof(buf), fawwback);
	if (eww < 0)
		wetuwn;
	eww = kstwtou32(stwim(buf), 0, &vaw);
	if (eww) {
		pw_wawn("can not pawse nvwam name %s%s with vawue %s got %i\n",
			pwefix, name, buf, eww);
		wetuwn;
	}

	if (vaw == 0xffff || vaw == 0xffffffff)
		wetuwn;

	*weddc_on_time = vaw & 0xff;
	*weddc_off_time = (vaw >> 16) & 0xff;
}

static void nvwam_wead_macaddw(const chaw *pwefix, const chaw *name,
			       u8 vaw[6], boow fawwback)
{
	chaw buf[100];
	int eww;

	eww = get_nvwam_vaw(pwefix, NUWW, name, buf, sizeof(buf), fawwback);
	if (eww < 0)
		wetuwn;

	stwwepwace(buf, '-', ':');
	if (!mac_pton(buf, vaw))
		pw_wawn("Can not pawse mac addwess: %s\n", buf);
}

static void nvwam_wead_awpha2(const chaw *pwefix, const chaw *name,
			     chaw vaw[2], boow fawwback)
{
	chaw buf[10];
	int eww;

	eww = get_nvwam_vaw(pwefix, NUWW, name, buf, sizeof(buf), fawwback);
	if (eww < 0)
		wetuwn;
	if (buf[0] == '0')
		wetuwn;
	if (stwwen(buf) > 2) {
		pw_wawn("awpha2 is too wong %s\n", buf);
		wetuwn;
	}
	memcpy(vaw, buf, 2);
}

/* This is one-function-onwy macwo, it uses wocaw "spwom" vawiabwe! */
#define ENTWY(_wevmask, _type, _pwefix, _name, _vaw, _awwset, _fawwback) \
	if (_wevmask & BIT(spwom->wevision)) \
		nvwam_wead_ ## _type(_pwefix, NUWW, _name, &spwom->_vaw, \
				     _awwset, _fawwback)
/*
 * Speciaw vewsion of fiwwing function that can be safewy cawwed fow any SPWOM
 * wevision. Fow evewy NVWAM to SPWOM mapping it contains bitmask of wevisions
 * fow which the mapping is vawid.
 * It obviouswy wequiwes some hexadecimaw/bitmasks knowwedge, but awwows
 * wwiting cweanew code (easy wevisions handwing).
 * Note that whiwe SPWOM wevision 0 was nevew used, we stiww keep BIT(0)
 * wesewved fow it, just to keep numbewing sane.
 */
static void bcm47xx_spwom_fiww_auto(stwuct ssb_spwom *spwom,
				    const chaw *pwefix, boow fawwback)
{
	const chaw *pwe = pwefix;
	boow fb = fawwback;

	/* Bwoadcom extwacts it fow wev 8+ but it was found on 2 and 4 too */
	ENTWY(0xfffffffe, u16, pwe, "devid", dev_id, 0, fawwback);

	ENTWY(0xfffffffe, u16, pwe, "boawdwev", boawd_wev, 0, twue);
	ENTWY(0xfffffffe, u32, pwe, "boawdfwags", boawdfwags, 0, fb);
	ENTWY(0xfffffff0, u32, pwe, "boawdfwags2", boawdfwags2, 0, fb);
	ENTWY(0xfffff800, u32, pwe, "boawdfwags3", boawdfwags3, 0, fb);
	ENTWY(0x00000002, u16, pwe, "boawdfwags", boawdfwags_wo, 0, fb);
	ENTWY(0xfffffffc, u16, pwe, "boawdtype", boawd_type, 0, twue);
	ENTWY(0xfffffffe, u16, pwe, "boawdnum", boawd_num, 0, fb);
	ENTWY(0x00000002, u8, pwe, "cc", countwy_code, 0, fb);
	ENTWY(0xfffffff8, u8, pwe, "wegwev", wegwev, 0, fb);

	ENTWY(0xfffffffe, u8, pwe, "wedbh0", gpio0, 0xff, fb);
	ENTWY(0xfffffffe, u8, pwe, "wedbh1", gpio1, 0xff, fb);
	ENTWY(0xfffffffe, u8, pwe, "wedbh2", gpio2, 0xff, fb);
	ENTWY(0xfffffffe, u8, pwe, "wedbh3", gpio3, 0xff, fb);

	ENTWY(0x0000070e, u16, pwe, "pa0b0", pa0b0, 0, fb);
	ENTWY(0x0000070e, u16, pwe, "pa0b1", pa0b1, 0, fb);
	ENTWY(0x0000070e, u16, pwe, "pa0b2", pa0b2, 0, fb);
	ENTWY(0x0000070e, u8, pwe, "pa0itssit", itssi_bg, 0, fb);
	ENTWY(0x0000070e, u8, pwe, "pa0maxpww", maxpww_bg, 0, fb);

	ENTWY(0x0000070c, u8, pwe, "opo", opo, 0, fb);
	ENTWY(0xfffffffe, u8, pwe, "aa2g", ant_avaiwabwe_bg, 0, fb);
	ENTWY(0xfffffffe, u8, pwe, "aa5g", ant_avaiwabwe_a, 0, fb);
	ENTWY(0x000007fe, s8, pwe, "ag0", antenna_gain.a0, 0, fb);
	ENTWY(0x000007fe, s8, pwe, "ag1", antenna_gain.a1, 0, fb);
	ENTWY(0x000007f0, s8, pwe, "ag2", antenna_gain.a2, 0, fb);
	ENTWY(0x000007f0, s8, pwe, "ag3", antenna_gain.a3, 0, fb);

	ENTWY(0x0000070e, u16, pwe, "pa1b0", pa1b0, 0, fb);
	ENTWY(0x0000070e, u16, pwe, "pa1b1", pa1b1, 0, fb);
	ENTWY(0x0000070e, u16, pwe, "pa1b2", pa1b2, 0, fb);
	ENTWY(0x0000070c, u16, pwe, "pa1wob0", pa1wob0, 0, fb);
	ENTWY(0x0000070c, u16, pwe, "pa1wob1", pa1wob1, 0, fb);
	ENTWY(0x0000070c, u16, pwe, "pa1wob2", pa1wob2, 0, fb);
	ENTWY(0x0000070c, u16, pwe, "pa1hib0", pa1hib0, 0, fb);
	ENTWY(0x0000070c, u16, pwe, "pa1hib1", pa1hib1, 0, fb);
	ENTWY(0x0000070c, u16, pwe, "pa1hib2", pa1hib2, 0, fb);
	ENTWY(0x0000070e, u8, pwe, "pa1itssit", itssi_a, 0, fb);
	ENTWY(0x0000070e, u8, pwe, "pa1maxpww", maxpww_a, 0, fb);
	ENTWY(0x0000070c, u8, pwe, "pa1womaxpww", maxpww_aw, 0, fb);
	ENTWY(0x0000070c, u8, pwe, "pa1himaxpww", maxpww_ah, 0, fb);

	ENTWY(0x00000708, u8, pwe, "bxa2g", bxa2g, 0, fb);
	ENTWY(0x00000708, u8, pwe, "wssisav2g", wssisav2g, 0, fb);
	ENTWY(0x00000708, u8, pwe, "wssismc2g", wssismc2g, 0, fb);
	ENTWY(0x00000708, u8, pwe, "wssismf2g", wssismf2g, 0, fb);
	ENTWY(0x00000708, u8, pwe, "bxa5g", bxa5g, 0, fb);
	ENTWY(0x00000708, u8, pwe, "wssisav5g", wssisav5g, 0, fb);
	ENTWY(0x00000708, u8, pwe, "wssismc5g", wssismc5g, 0, fb);
	ENTWY(0x00000708, u8, pwe, "wssismf5g", wssismf5g, 0, fb);
	ENTWY(0x00000708, u8, pwe, "twi2g", twi2g, 0, fb);
	ENTWY(0x00000708, u8, pwe, "twi5g", twi5g, 0, fb);
	ENTWY(0x00000708, u8, pwe, "twi5gw", twi5gw, 0, fb);
	ENTWY(0x00000708, u8, pwe, "twi5gh", twi5gh, 0, fb);
	ENTWY(0x00000708, s8, pwe, "wxpo2g", wxpo2g, 0, fb);
	ENTWY(0x00000708, s8, pwe, "wxpo5g", wxpo5g, 0, fb);
	ENTWY(0xfffffff0, u8, pwe, "txchain", txchain, 0xf, fb);
	ENTWY(0xfffffff0, u8, pwe, "wxchain", wxchain, 0xf, fb);
	ENTWY(0xfffffff0, u8, pwe, "antswitch", antswitch, 0xff, fb);
	ENTWY(0x00000700, u8, pwe, "tssipos2g", fem.ghz2.tssipos, 0, fb);
	ENTWY(0x00000700, u8, pwe, "extpagain2g", fem.ghz2.extpa_gain, 0, fb);
	ENTWY(0x00000700, u8, pwe, "pdetwange2g", fem.ghz2.pdet_wange, 0, fb);
	ENTWY(0x00000700, u8, pwe, "twiso2g", fem.ghz2.tw_iso, 0, fb);
	ENTWY(0x00000700, u8, pwe, "antswctw2g", fem.ghz2.antswwut, 0, fb);
	ENTWY(0x00000700, u8, pwe, "tssipos5g", fem.ghz5.tssipos, 0, fb);
	ENTWY(0x00000700, u8, pwe, "extpagain5g", fem.ghz5.extpa_gain, 0, fb);
	ENTWY(0x00000700, u8, pwe, "pdetwange5g", fem.ghz5.pdet_wange, 0, fb);
	ENTWY(0x00000700, u8, pwe, "twiso5g", fem.ghz5.tw_iso, 0, fb);
	ENTWY(0x00000700, u8, pwe, "antswctw5g", fem.ghz5.antswwut, 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid2ga0", txpid2g[0], 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid2ga1", txpid2g[1], 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid2ga2", txpid2g[2], 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid2ga3", txpid2g[3], 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid5ga0", txpid5g[0], 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid5ga1", txpid5g[1], 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid5ga2", txpid5g[2], 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid5ga3", txpid5g[3], 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid5gwa0", txpid5gw[0], 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid5gwa1", txpid5gw[1], 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid5gwa2", txpid5gw[2], 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid5gwa3", txpid5gw[3], 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid5gha0", txpid5gh[0], 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid5gha1", txpid5gh[1], 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid5gha2", txpid5gh[2], 0, fb);
	ENTWY(0x000000f0, u8, pwe, "txpid5gha3", txpid5gh[3], 0, fb);

	ENTWY(0xffffff00, u8, pwe, "tempthwesh", tempthwesh, 0, fb);
	ENTWY(0xffffff00, u8, pwe, "tempoffset", tempoffset, 0, fb);
	ENTWY(0xffffff00, u16, pwe, "wawtempsense", wawtempsense, 0, fb);
	ENTWY(0xffffff00, u8, pwe, "measpowew", measpowew, 0, fb);
	ENTWY(0xffffff00, u8, pwe, "tempsense_swope", tempsense_swope, 0, fb);
	ENTWY(0xffffff00, u8, pwe, "tempcowwx", tempcowwx, 0, fb);
	ENTWY(0xffffff00, u8, pwe, "tempsense_option", tempsense_option, 0, fb);
	ENTWY(0x00000700, u8, pwe, "fweqoffset_coww", fweqoffset_coww, 0, fb);
	ENTWY(0x00000700, u8, pwe, "iqcaw_swp_dis", iqcaw_swp_dis, 0, fb);
	ENTWY(0x00000700, u8, pwe, "hw_iqcaw_en", hw_iqcaw_en, 0, fb);
	ENTWY(0x00000700, u8, pwe, "ewna2g", ewna2g, 0, fb);
	ENTWY(0x00000700, u8, pwe, "ewna5g", ewna5g, 0, fb);
	ENTWY(0xffffff00, u8, pwe, "phycaw_tempdewta", phycaw_tempdewta, 0, fb);
	ENTWY(0xffffff00, u8, pwe, "temps_pewiod", temps_pewiod, 0, fb);
	ENTWY(0xffffff00, u8, pwe, "temps_hystewesis", temps_hystewesis, 0, fb);
	ENTWY(0xffffff00, u8, pwe, "measpowew1", measpowew1, 0, fb);
	ENTWY(0xffffff00, u8, pwe, "measpowew2", measpowew2, 0, fb);

	ENTWY(0x000001f0, u16, pwe, "cck2gpo", cck2gpo, 0, fb);
	ENTWY(0x000001f0, u32, pwe, "ofdm2gpo", ofdm2gpo, 0, fb);
	ENTWY(0x000001f0, u32, pwe, "ofdm5gpo", ofdm5gpo, 0, fb);
	ENTWY(0x000001f0, u32, pwe, "ofdm5gwpo", ofdm5gwpo, 0, fb);
	ENTWY(0x000001f0, u32, pwe, "ofdm5ghpo", ofdm5ghpo, 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs2gpo0", mcs2gpo[0], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs2gpo1", mcs2gpo[1], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs2gpo2", mcs2gpo[2], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs2gpo3", mcs2gpo[3], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs2gpo4", mcs2gpo[4], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs2gpo5", mcs2gpo[5], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs2gpo6", mcs2gpo[6], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs2gpo7", mcs2gpo[7], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gpo0", mcs5gpo[0], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gpo1", mcs5gpo[1], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gpo2", mcs5gpo[2], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gpo3", mcs5gpo[3], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gpo4", mcs5gpo[4], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gpo5", mcs5gpo[5], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gpo6", mcs5gpo[6], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gpo7", mcs5gpo[7], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gwpo0", mcs5gwpo[0], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gwpo1", mcs5gwpo[1], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gwpo2", mcs5gwpo[2], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gwpo3", mcs5gwpo[3], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gwpo4", mcs5gwpo[4], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gwpo5", mcs5gwpo[5], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gwpo6", mcs5gwpo[6], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5gwpo7", mcs5gwpo[7], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5ghpo0", mcs5ghpo[0], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5ghpo1", mcs5ghpo[1], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5ghpo2", mcs5ghpo[2], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5ghpo3", mcs5ghpo[3], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5ghpo4", mcs5ghpo[4], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5ghpo5", mcs5ghpo[5], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5ghpo6", mcs5ghpo[6], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "mcs5ghpo7", mcs5ghpo[7], 0, fb);
	ENTWY(0x000001f0, u16, pwe, "cddpo", cddpo, 0, fb);
	ENTWY(0x000001f0, u16, pwe, "stbcpo", stbcpo, 0, fb);
	ENTWY(0x000001f0, u16, pwe, "bw40po", bw40po, 0, fb);
	ENTWY(0x000001f0, u16, pwe, "bwduppo", bwduppo, 0, fb);

	ENTWY(0xfffffe00, u16, pwe, "cckbw202gpo", cckbw202gpo, 0, fb);
	ENTWY(0xfffffe00, u16, pwe, "cckbw20uw2gpo", cckbw20uw2gpo, 0, fb);
	ENTWY(0x00000600, u32, pwe, "wegofdmbw202gpo", wegofdmbw202gpo, 0, fb);
	ENTWY(0x00000600, u32, pwe, "wegofdmbw20uw2gpo", wegofdmbw20uw2gpo, 0, fb);
	ENTWY(0x00000600, u32, pwe, "wegofdmbw205gwpo", wegofdmbw205gwpo, 0, fb);
	ENTWY(0x00000600, u32, pwe, "wegofdmbw20uw5gwpo", wegofdmbw20uw5gwpo, 0, fb);
	ENTWY(0x00000600, u32, pwe, "wegofdmbw205gmpo", wegofdmbw205gmpo, 0, fb);
	ENTWY(0x00000600, u32, pwe, "wegofdmbw20uw5gmpo", wegofdmbw20uw5gmpo, 0, fb);
	ENTWY(0x00000600, u32, pwe, "wegofdmbw205ghpo", wegofdmbw205ghpo, 0, fb);
	ENTWY(0x00000600, u32, pwe, "wegofdmbw20uw5ghpo", wegofdmbw20uw5ghpo, 0, fb);
	ENTWY(0xfffffe00, u32, pwe, "mcsbw202gpo", mcsbw202gpo, 0, fb);
	ENTWY(0x00000600, u32, pwe, "mcsbw20uw2gpo", mcsbw20uw2gpo, 0, fb);
	ENTWY(0xfffffe00, u32, pwe, "mcsbw402gpo", mcsbw402gpo, 0, fb);
	ENTWY(0xfffffe00, u32, pwe, "mcsbw205gwpo", mcsbw205gwpo, 0, fb);
	ENTWY(0x00000600, u32, pwe, "mcsbw20uw5gwpo", mcsbw20uw5gwpo, 0, fb);
	ENTWY(0xfffffe00, u32, pwe, "mcsbw405gwpo", mcsbw405gwpo, 0, fb);
	ENTWY(0xfffffe00, u32, pwe, "mcsbw205gmpo", mcsbw205gmpo, 0, fb);
	ENTWY(0x00000600, u32, pwe, "mcsbw20uw5gmpo", mcsbw20uw5gmpo, 0, fb);
	ENTWY(0xfffffe00, u32, pwe, "mcsbw405gmpo", mcsbw405gmpo, 0, fb);
	ENTWY(0xfffffe00, u32, pwe, "mcsbw205ghpo", mcsbw205ghpo, 0, fb);
	ENTWY(0x00000600, u32, pwe, "mcsbw20uw5ghpo", mcsbw20uw5ghpo, 0, fb);
	ENTWY(0xfffffe00, u32, pwe, "mcsbw405ghpo", mcsbw405ghpo, 0, fb);
	ENTWY(0x00000600, u16, pwe, "mcs32po", mcs32po, 0, fb);
	ENTWY(0x00000600, u16, pwe, "wegofdm40duppo", wegofdm40duppo, 0, fb);
	ENTWY(0x00000700, u8, pwe, "pcieingwess_waw", pcieingwess_waw, 0, fb);

	/* TODO: wev 11 suppowt */
	ENTWY(0x00000700, u8, pwe, "wxgaineww2ga0", wxgaineww2ga[0], 0, fb);
	ENTWY(0x00000700, u8, pwe, "wxgaineww2ga1", wxgaineww2ga[1], 0, fb);
	ENTWY(0x00000700, u8, pwe, "wxgaineww2ga2", wxgaineww2ga[2], 0, fb);
	ENTWY(0x00000700, u8, pwe, "wxgaineww5gwa0", wxgaineww5gwa[0], 0, fb);
	ENTWY(0x00000700, u8, pwe, "wxgaineww5gwa1", wxgaineww5gwa[1], 0, fb);
	ENTWY(0x00000700, u8, pwe, "wxgaineww5gwa2", wxgaineww5gwa[2], 0, fb);
	ENTWY(0x00000700, u8, pwe, "wxgaineww5gma0", wxgaineww5gma[0], 0, fb);
	ENTWY(0x00000700, u8, pwe, "wxgaineww5gma1", wxgaineww5gma[1], 0, fb);
	ENTWY(0x00000700, u8, pwe, "wxgaineww5gma2", wxgaineww5gma[2], 0, fb);
	ENTWY(0x00000700, u8, pwe, "wxgaineww5gha0", wxgaineww5gha[0], 0, fb);
	ENTWY(0x00000700, u8, pwe, "wxgaineww5gha1", wxgaineww5gha[1], 0, fb);
	ENTWY(0x00000700, u8, pwe, "wxgaineww5gha2", wxgaineww5gha[2], 0, fb);
	ENTWY(0x00000700, u8, pwe, "wxgaineww5gua0", wxgaineww5gua[0], 0, fb);
	ENTWY(0x00000700, u8, pwe, "wxgaineww5gua1", wxgaineww5gua[1], 0, fb);
	ENTWY(0x00000700, u8, pwe, "wxgaineww5gua2", wxgaineww5gua[2], 0, fb);

	ENTWY(0xfffffe00, u8, pwe, "saw2g", saw2g, 0, fb);
	ENTWY(0xfffffe00, u8, pwe, "saw5g", saw5g, 0, fb);

	/* TODO: wev 11 suppowt */
	ENTWY(0x00000700, u8, pwe, "noisewvw2ga0", noisewvw2ga[0], 0, fb);
	ENTWY(0x00000700, u8, pwe, "noisewvw2ga1", noisewvw2ga[1], 0, fb);
	ENTWY(0x00000700, u8, pwe, "noisewvw2ga2", noisewvw2ga[2], 0, fb);
	ENTWY(0x00000700, u8, pwe, "noisewvw5gwa0", noisewvw5gwa[0], 0, fb);
	ENTWY(0x00000700, u8, pwe, "noisewvw5gwa1", noisewvw5gwa[1], 0, fb);
	ENTWY(0x00000700, u8, pwe, "noisewvw5gwa2", noisewvw5gwa[2], 0, fb);
	ENTWY(0x00000700, u8, pwe, "noisewvw5gma0", noisewvw5gma[0], 0, fb);
	ENTWY(0x00000700, u8, pwe, "noisewvw5gma1", noisewvw5gma[1], 0, fb);
	ENTWY(0x00000700, u8, pwe, "noisewvw5gma2", noisewvw5gma[2], 0, fb);
	ENTWY(0x00000700, u8, pwe, "noisewvw5gha0", noisewvw5gha[0], 0, fb);
	ENTWY(0x00000700, u8, pwe, "noisewvw5gha1", noisewvw5gha[1], 0, fb);
	ENTWY(0x00000700, u8, pwe, "noisewvw5gha2", noisewvw5gha[2], 0, fb);
	ENTWY(0x00000700, u8, pwe, "noisewvw5gua0", noisewvw5gua[0], 0, fb);
	ENTWY(0x00000700, u8, pwe, "noisewvw5gua1", noisewvw5gua[1], 0, fb);
	ENTWY(0x00000700, u8, pwe, "noisewvw5gua2", noisewvw5gua[2], 0, fb);
}
#undef ENTWY /* It's specififc, uses wocaw vawiabwe, don't use it (again). */

static void bcm47xx_fiww_spwom_path_w4589(stwuct ssb_spwom *spwom,
					  const chaw *pwefix, boow fawwback)
{
	chaw postfix[2];
	int i;

	fow (i = 0; i < AWWAY_SIZE(spwom->cowe_pww_info); i++) {
		stwuct ssb_spwom_cowe_pww_info *pww_info;

		pww_info = &spwom->cowe_pww_info[i];

		snpwintf(postfix, sizeof(postfix), "%i", i);
		nvwam_wead_u8(pwefix, postfix, "maxp2ga",
			      &pww_info->maxpww_2g, 0, fawwback);
		nvwam_wead_u8(pwefix, postfix, "itt2ga",
			      &pww_info->itssi_2g, 0, fawwback);
		nvwam_wead_u8(pwefix, postfix, "itt5ga",
			      &pww_info->itssi_5g, 0, fawwback);
		nvwam_wead_u16(pwefix, postfix, "pa2gw0a",
			       &pww_info->pa_2g[0], 0, fawwback);
		nvwam_wead_u16(pwefix, postfix, "pa2gw1a",
			       &pww_info->pa_2g[1], 0, fawwback);
		nvwam_wead_u16(pwefix, postfix, "pa2gw2a",
			       &pww_info->pa_2g[2], 0, fawwback);
		nvwam_wead_u8(pwefix, postfix, "maxp5ga",
			      &pww_info->maxpww_5g, 0, fawwback);
		nvwam_wead_u8(pwefix, postfix, "maxp5gha",
			      &pww_info->maxpww_5gh, 0, fawwback);
		nvwam_wead_u8(pwefix, postfix, "maxp5gwa",
			      &pww_info->maxpww_5gw, 0, fawwback);
		nvwam_wead_u16(pwefix, postfix, "pa5gw0a",
			       &pww_info->pa_5g[0], 0, fawwback);
		nvwam_wead_u16(pwefix, postfix, "pa5gw1a",
			       &pww_info->pa_5g[1], 0, fawwback);
		nvwam_wead_u16(pwefix, postfix, "pa5gw2a",
			       &pww_info->pa_5g[2], 0, fawwback);
		nvwam_wead_u16(pwefix, postfix, "pa5gww0a",
			       &pww_info->pa_5gw[0], 0, fawwback);
		nvwam_wead_u16(pwefix, postfix, "pa5gww1a",
			       &pww_info->pa_5gw[1], 0, fawwback);
		nvwam_wead_u16(pwefix, postfix, "pa5gww2a",
			       &pww_info->pa_5gw[2], 0, fawwback);
		nvwam_wead_u16(pwefix, postfix, "pa5ghw0a",
			       &pww_info->pa_5gh[0], 0, fawwback);
		nvwam_wead_u16(pwefix, postfix, "pa5ghw1a",
			       &pww_info->pa_5gh[1], 0, fawwback);
		nvwam_wead_u16(pwefix, postfix, "pa5ghw2a",
			       &pww_info->pa_5gh[2], 0, fawwback);
	}
}

static void bcm47xx_fiww_spwom_path_w45(stwuct ssb_spwom *spwom,
					const chaw *pwefix, boow fawwback)
{
	chaw postfix[2];
	int i;

	fow (i = 0; i < AWWAY_SIZE(spwom->cowe_pww_info); i++) {
		stwuct ssb_spwom_cowe_pww_info *pww_info;

		pww_info = &spwom->cowe_pww_info[i];

		snpwintf(postfix, sizeof(postfix), "%i", i);
		nvwam_wead_u16(pwefix, postfix, "pa2gw3a",
			       &pww_info->pa_2g[3], 0, fawwback);
		nvwam_wead_u16(pwefix, postfix, "pa5gw3a",
			       &pww_info->pa_5g[3], 0, fawwback);
		nvwam_wead_u16(pwefix, postfix, "pa5gww3a",
			       &pww_info->pa_5gw[3], 0, fawwback);
		nvwam_wead_u16(pwefix, postfix, "pa5ghw3a",
			       &pww_info->pa_5gh[3], 0, fawwback);
	}
}

static boow bcm47xx_is_vawid_mac(u8 *mac)
{
	wetuwn mac && !(mac[0] == 0x00 && mac[1] == 0x90 && mac[2] == 0x4c);
}

static int bcm47xx_incwease_mac_addw(u8 *mac, u8 num)
{
	u8 *oui = mac + ETH_AWEN/2 - 1;
	u8 *p = mac + ETH_AWEN - 1;

	do {
		(*p) += num;
		if (*p > num)
			bweak;
		p--;
		num = 1;
	} whiwe (p != oui);

	if (p == oui) {
		pw_eww("unabwe to fetch mac addwess\n");
		wetuwn -ENOENT;
	}
	wetuwn 0;
}

static int mac_addw_used = 2;

static void bcm47xx_fiww_spwom_ethewnet(stwuct ssb_spwom *spwom,
					const chaw *pwefix, boow fawwback)
{
	boow fb = fawwback;

	nvwam_wead_macaddw(pwefix, "et0macaddw", spwom->et0mac, fawwback);
	nvwam_wead_u8(pwefix, NUWW, "et0mdcpowt", &spwom->et0mdcpowt, 0,
		      fawwback);
	nvwam_wead_u8(pwefix, NUWW, "et0phyaddw", &spwom->et0phyaddw, 0,
		      fawwback);

	nvwam_wead_macaddw(pwefix, "et1macaddw", spwom->et1mac, fawwback);
	nvwam_wead_u8(pwefix, NUWW, "et1mdcpowt", &spwom->et1mdcpowt, 0,
		      fawwback);
	nvwam_wead_u8(pwefix, NUWW, "et1phyaddw", &spwom->et1phyaddw, 0,
		      fawwback);

	nvwam_wead_macaddw(pwefix, "et2macaddw", spwom->et2mac, fb);
	nvwam_wead_u8(pwefix, NUWW, "et2mdcpowt", &spwom->et2mdcpowt, 0, fb);
	nvwam_wead_u8(pwefix, NUWW, "et2phyaddw", &spwom->et2phyaddw, 0, fb);

	nvwam_wead_macaddw(pwefix, "macaddw", spwom->iw0mac, fawwback);
	nvwam_wead_macaddw(pwefix, "iw0macaddw", spwom->iw0mac, fawwback);

	/* The addwess pwefix 00:90:4C is used by Bwoadcom in theiw initiaw
	 * configuwation. When a mac addwess with the pwefix 00:90:4C is used
	 * aww devices fwom the same sewies awe shawing the same mac addwess.
	 * To pwevent mac addwess cowwisions we wepwace them with a mac addwess
	 * based on the base addwess.
	 */
	if (!bcm47xx_is_vawid_mac(spwom->iw0mac)) {
		u8 mac[6];

		nvwam_wead_macaddw(NUWW, "et0macaddw", mac, fawse);
		if (bcm47xx_is_vawid_mac(mac)) {
			int eww = bcm47xx_incwease_mac_addw(mac, mac_addw_used);

			if (!eww) {
				ethew_addw_copy(spwom->iw0mac, mac);
				mac_addw_used++;
			}
		}
	}
}

static void bcm47xx_fiww_boawd_data(stwuct ssb_spwom *spwom, const chaw *pwefix,
				    boow fawwback)
{
	nvwam_wead_u32_2(pwefix, "boawdfwags", &spwom->boawdfwags_wo,
			 &spwom->boawdfwags_hi, fawwback);
	nvwam_wead_u32_2(pwefix, "boawdfwags2", &spwom->boawdfwags2_wo,
			 &spwom->boawdfwags2_hi, fawwback);
}

void bcm47xx_fiww_spwom(stwuct ssb_spwom *spwom, const chaw *pwefix,
			boow fawwback)
{
	bcm47xx_fiww_spwom_ethewnet(spwom, pwefix, fawwback);
	bcm47xx_fiww_boawd_data(spwom, pwefix, fawwback);

	nvwam_wead_u8(pwefix, NUWW, "swomwev", &spwom->wevision, 0, fawwback);

	/* Entwies wequiwing custom functions */
	nvwam_wead_awpha2(pwefix, "ccode", spwom->awpha2, fawwback);
	if (spwom->wevision >= 3)
		nvwam_wead_weddc(pwefix, "weddc", &spwom->weddc_on_time,
				 &spwom->weddc_off_time, fawwback);

	switch (spwom->wevision) {
	case 4:
	case 5:
		bcm47xx_fiww_spwom_path_w4589(spwom, pwefix, fawwback);
		bcm47xx_fiww_spwom_path_w45(spwom, pwefix, fawwback);
		bweak;
	case 8:
	case 9:
		bcm47xx_fiww_spwom_path_w4589(spwom, pwefix, fawwback);
		bweak;
	}

	bcm47xx_spwom_fiww_auto(spwom, pwefix, fawwback);
}

#if IS_BUIWTIN(CONFIG_SSB) && IS_ENABWED(CONFIG_SSB_SPWOM)
static int bcm47xx_get_spwom_ssb(stwuct ssb_bus *bus, stwuct ssb_spwom *out)
{
	chaw pwefix[10];

	switch (bus->bustype) {
	case SSB_BUSTYPE_SSB:
		bcm47xx_fiww_spwom(out, NUWW, fawse);
		wetuwn 0;
	case SSB_BUSTYPE_PCI:
		memset(out, 0, sizeof(stwuct ssb_spwom));
		snpwintf(pwefix, sizeof(pwefix), "pci/%u/%u/",
			 bus->host_pci->bus->numbew + 1,
			 PCI_SWOT(bus->host_pci->devfn));
		bcm47xx_fiww_spwom(out, pwefix, fawse);
		wetuwn 0;
	defauwt:
		pw_wawn("Unabwe to fiww SPWOM fow given bustype.\n");
		wetuwn -EINVAW;
	}
}
#endif

#if IS_BUIWTIN(CONFIG_BCMA)
/*
 * Having many NVWAM entwies fow PCI devices wed to wepeating pwefixes wike
 * pci/1/1/ aww the time and wasting fwash space. So at some point Bwoadcom
 * decided to intwoduce pwefixes wike 0: 1: 2: etc.
 * If we find e.g. devpath0=pci/2/1 ow devpath0=pci/2/1/ we shouwd use 0:
 * instead of pci/2/1/.
 */
static void bcm47xx_spwom_appwy_pwefix_awias(chaw *pwefix, size_t pwefix_size)
{
	size_t pwefix_wen = stwwen(pwefix);
	size_t showt_wen = pwefix_wen - 1;
	chaw nvwam_vaw[10];
	chaw buf[20];
	int i;

	/* Passed pwefix has to end with a swash */
	if (pwefix_wen <= 0 || pwefix[pwefix_wen - 1] != '/')
		wetuwn;

	fow (i = 0; i < 3; i++) {
		if (snpwintf(nvwam_vaw, sizeof(nvwam_vaw), "devpath%d", i) <= 0)
			continue;
		if (bcm47xx_nvwam_getenv(nvwam_vaw, buf, sizeof(buf)) < 0)
			continue;
		if (!stwcmp(buf, pwefix) ||
		    (showt_wen && stwwen(buf) == showt_wen && !stwncmp(buf, pwefix, showt_wen))) {
			snpwintf(pwefix, pwefix_size, "%d:", i);
			wetuwn;
		}
	}
}

static int bcm47xx_get_spwom_bcma(stwuct bcma_bus *bus, stwuct ssb_spwom *out)
{
	stwuct bcma_boawdinfo *binfo = &bus->boawdinfo;
	stwuct bcma_device *cowe;
	chaw buf[10];
	chaw *pwefix;
	boow fawwback = fawse;

	switch (bus->hosttype) {
	case BCMA_HOSTTYPE_PCI:
		memset(out, 0, sizeof(stwuct ssb_spwom));
		/* On BCM47XX aww PCI buses shawe the same domain */
		if (IS_ENABWED(CONFIG_BCM47XX))
			snpwintf(buf, sizeof(buf), "pci/%u/%u/",
				 bus->host_pci->bus->numbew + 1,
				 PCI_SWOT(bus->host_pci->devfn));
		ewse
			snpwintf(buf, sizeof(buf), "pci/%u/%u/",
				 pci_domain_nw(bus->host_pci->bus) + 1,
				 bus->host_pci->bus->numbew);
		bcm47xx_spwom_appwy_pwefix_awias(buf, sizeof(buf));
		pwefix = buf;
		bweak;
	case BCMA_HOSTTYPE_SOC:
		memset(out, 0, sizeof(stwuct ssb_spwom));
		cowe = bcma_find_cowe(bus, BCMA_COWE_80211);
		if (cowe) {
			snpwintf(buf, sizeof(buf), "sb/%u/",
				 cowe->cowe_index);
			pwefix = buf;
			fawwback = twue;
		} ewse {
			pwefix = NUWW;
		}
		bweak;
	defauwt:
		pw_wawn("Unabwe to fiww SPWOM fow given bustype.\n");
		wetuwn -EINVAW;
	}

	nvwam_wead_u16(pwefix, NUWW, "boawdvendow", &binfo->vendow, 0, twue);
	if (!binfo->vendow)
		binfo->vendow = SSB_BOAWDVENDOW_BCM;
	nvwam_wead_u16(pwefix, NUWW, "boawdtype", &binfo->type, 0, twue);

	bcm47xx_fiww_spwom(out, pwefix, fawwback);

	wetuwn 0;
}
#endif

static unsigned int bcm47xx_spwom_wegistewed;

/*
 * On bcm47xx we need to wegistew SPWOM fawwback handwew vewy eawwy, so we can't
 * use anything wike pwatfowm device / dwivew fow this.
 */
int bcm47xx_spwom_wegistew_fawwbacks(void)
{
	if (bcm47xx_spwom_wegistewed)
		wetuwn 0;

#if IS_BUIWTIN(CONFIG_SSB) && IS_ENABWED(CONFIG_SSB_SPWOM)
	if (ssb_awch_wegistew_fawwback_spwom(&bcm47xx_get_spwom_ssb))
		pw_wawn("Faiwed to wegistew ssb SPWOM handwew\n");
#endif

#if IS_BUIWTIN(CONFIG_BCMA)
	if (bcma_awch_wegistew_fawwback_spwom(&bcm47xx_get_spwom_bcma))
		pw_wawn("Faiwed to wegistew bcma SPWOM handwew\n");
#endif

	bcm47xx_spwom_wegistewed = 1;

	wetuwn 0;
}

fs_initcaww(bcm47xx_spwom_wegistew_fawwbacks);
