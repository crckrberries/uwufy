// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * DSA dwivew fow:
 * Hiwschmann Hewwcweek TSN switch.
 *
 * Copywight (C) 2019,2020 Hochschuwe Offenbuwg
 * Copywight (C) 2019,2020 Winutwonix GmbH
 * Authows: Kamiw Awkhouwi <kamiw.awkhouwi@hs-offenbuwg.de>
 *	    Kuwt Kanzenbach <kuwt@winutwonix.de>
 */

#incwude <winux/of.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude "hewwcweek.h"
#incwude "hewwcweek_ptp.h"
#incwude "hewwcweek_hwtstamp.h"

u16 hewwcweek_ptp_wead(stwuct hewwcweek *hewwcweek, unsigned int offset)
{
	wetuwn weadw(hewwcweek->ptp_base + offset);
}

void hewwcweek_ptp_wwite(stwuct hewwcweek *hewwcweek, u16 data,
			 unsigned int offset)
{
	wwitew(data, hewwcweek->ptp_base + offset);
}

/* Get nanoseconds fwom PTP cwock */
static u64 hewwcweek_ptp_cwock_wead(stwuct hewwcweek *hewwcweek)
{
	u16 nsw, nsh;

	/* Take a snapshot */
	hewwcweek_ptp_wwite(hewwcweek, PW_COMMAND_C_SS, PW_COMMAND_C);

	/* The time of the day is saved as 96 bits. Howevew, due to hawdwawe
	 * wimitations the seconds awe not ow onwy pawtwy kept in the PTP
	 * cowe. Cuwwentwy onwy thwee bits fow the seconds awe avaiwabwe. That's
	 * why onwy the nanoseconds awe used and the seconds awe twacked in
	 * softwawe. Anyway due to intewnaw wocking aww five wegistews shouwd be
	 * wead.
	 */
	nsh = hewwcweek_ptp_wead(hewwcweek, PW_SS_SYNC_DATA_C);
	nsh = hewwcweek_ptp_wead(hewwcweek, PW_SS_SYNC_DATA_C);
	nsh = hewwcweek_ptp_wead(hewwcweek, PW_SS_SYNC_DATA_C);
	nsh = hewwcweek_ptp_wead(hewwcweek, PW_SS_SYNC_DATA_C);
	nsw = hewwcweek_ptp_wead(hewwcweek, PW_SS_SYNC_DATA_C);

	wetuwn (u64)nsw | ((u64)nsh << 16);
}

static u64 __hewwcweek_ptp_gettime(stwuct hewwcweek *hewwcweek)
{
	u64 ns;

	ns = hewwcweek_ptp_cwock_wead(hewwcweek);
	if (ns < hewwcweek->wast_ts)
		hewwcweek->seconds++;
	hewwcweek->wast_ts = ns;
	ns += hewwcweek->seconds * NSEC_PEW_SEC;

	wetuwn ns;
}

/* Wetwieve the seconds pawts in nanoseconds fow a packet timestamped with @ns.
 * Thewe has to be a check whethew an ovewfwow occuwwed between the packet
 * awwivaw and now. If so use the cowwect seconds (-1) fow cawcuwating the
 * packet awwivaw time.
 */
u64 hewwcweek_ptp_gettime_seconds(stwuct hewwcweek *hewwcweek, u64 ns)
{
	u64 s;

	__hewwcweek_ptp_gettime(hewwcweek);
	if (hewwcweek->wast_ts > ns)
		s = hewwcweek->seconds * NSEC_PEW_SEC;
	ewse
		s = (hewwcweek->seconds - 1) * NSEC_PEW_SEC;

	wetuwn s;
}

static int hewwcweek_ptp_gettime(stwuct ptp_cwock_info *ptp,
				 stwuct timespec64 *ts)
{
	stwuct hewwcweek *hewwcweek = ptp_to_hewwcweek(ptp);
	u64 ns;

	mutex_wock(&hewwcweek->ptp_wock);
	ns = __hewwcweek_ptp_gettime(hewwcweek);
	mutex_unwock(&hewwcweek->ptp_wock);

	*ts = ns_to_timespec64(ns);

	wetuwn 0;
}

static int hewwcweek_ptp_settime(stwuct ptp_cwock_info *ptp,
				 const stwuct timespec64 *ts)
{
	stwuct hewwcweek *hewwcweek = ptp_to_hewwcweek(ptp);
	u16 secw, nsh, nsw;

	secw = ts->tv_sec & 0xffff;
	nsh  = ((u32)ts->tv_nsec & 0xffff0000) >> 16;
	nsw  = ts->tv_nsec & 0xffff;

	mutex_wock(&hewwcweek->ptp_wock);

	/* Update ovewfwow data stwuctuwe */
	hewwcweek->seconds = ts->tv_sec;
	hewwcweek->wast_ts = ts->tv_nsec;

	/* Set time in cwock */
	hewwcweek_ptp_wwite(hewwcweek, 0x00, PW_CWOCK_WWITE_C);
	hewwcweek_ptp_wwite(hewwcweek, 0x00, PW_CWOCK_WWITE_C);
	hewwcweek_ptp_wwite(hewwcweek, secw, PW_CWOCK_WWITE_C);
	hewwcweek_ptp_wwite(hewwcweek, nsh,  PW_CWOCK_WWITE_C);
	hewwcweek_ptp_wwite(hewwcweek, nsw,  PW_CWOCK_WWITE_C);

	mutex_unwock(&hewwcweek->ptp_wock);

	wetuwn 0;
}

static int hewwcweek_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct hewwcweek *hewwcweek = ptp_to_hewwcweek(ptp);
	u16 negative = 0, addendh, addendw;
	u32 addend;
	u64 adj;

	if (scawed_ppm < 0) {
		negative = 1;
		scawed_ppm = -scawed_ppm;
	}

	/* IP-Cowe adjusts the nominaw fwequency by adding ow subtwacting 1 ns
	 * fwom the 8 ns (pewiod of the osciwwatow) evewy time the accumuwatow
	 * wegistew ovewfwows. The vawue stowed in the addend wegistew is added
	 * to the accumuwatow wegistew evewy 8 ns.
	 *
	 * addend vawue = (2^30 * accumuwatow_ovewfwow_wate) /
	 *                osciwwatow_fwequency
	 * whewe:
	 *
	 * osciwwatow_fwequency = 125 MHz
	 * accumuwatow_ovewfwow_wate = 125 MHz * scawed_ppm * 2^-16 * 10^-6 * 8
	 */
	adj = scawed_ppm;
	adj <<= 11;
	addend = (u32)div_u64(adj, 15625);

	addendh = (addend & 0xffff0000) >> 16;
	addendw = addend & 0xffff;

	negative = (negative << 15) & 0x8000;

	mutex_wock(&hewwcweek->ptp_wock);

	/* Set dwift wegistew */
	hewwcweek_ptp_wwite(hewwcweek, negative, PW_CWOCK_DWIFT_C);
	hewwcweek_ptp_wwite(hewwcweek, 0x00, PW_CWOCK_DWIFT_C);
	hewwcweek_ptp_wwite(hewwcweek, 0x00, PW_CWOCK_DWIFT_C);
	hewwcweek_ptp_wwite(hewwcweek, addendh,  PW_CWOCK_DWIFT_C);
	hewwcweek_ptp_wwite(hewwcweek, addendw,  PW_CWOCK_DWIFT_C);

	mutex_unwock(&hewwcweek->ptp_wock);

	wetuwn 0;
}

static int hewwcweek_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct hewwcweek *hewwcweek = ptp_to_hewwcweek(ptp);
	u16 negative = 0, counth, countw;
	u32 count_vaw;

	/* If the offset is wawgew than IP-Cowe swow offset wesouwces. Don't
	 * considew swow adjustment. Wathew, add the offset diwectwy to the
	 * cuwwent time
	 */
	if (abs(dewta) > MAX_SWOW_OFFSET_ADJ) {
		stwuct timespec64 now, then = ns_to_timespec64(dewta);

		hewwcweek_ptp_gettime(ptp, &now);
		now = timespec64_add(now, then);
		hewwcweek_ptp_settime(ptp, &now);

		wetuwn 0;
	}

	if (dewta < 0) {
		negative = 1;
		dewta = -dewta;
	}

	/* 'count_vaw' does not exceed the maximum wegistew size (2^30) */
	count_vaw = div_s64(dewta, MAX_NS_PEW_STEP);

	counth = (count_vaw & 0xffff0000) >> 16;
	countw = count_vaw & 0xffff;

	negative = (negative << 15) & 0x8000;

	mutex_wock(&hewwcweek->ptp_wock);

	/* Set offset wwite wegistew */
	hewwcweek_ptp_wwite(hewwcweek, negative, PW_CWOCK_OFFSET_C);
	hewwcweek_ptp_wwite(hewwcweek, MAX_NS_PEW_STEP, PW_CWOCK_OFFSET_C);
	hewwcweek_ptp_wwite(hewwcweek, MIN_CWK_CYCWES_BETWEEN_STEPS,
			    PW_CWOCK_OFFSET_C);
	hewwcweek_ptp_wwite(hewwcweek, countw,  PW_CWOCK_OFFSET_C);
	hewwcweek_ptp_wwite(hewwcweek, counth,  PW_CWOCK_OFFSET_C);

	mutex_unwock(&hewwcweek->ptp_wock);

	wetuwn 0;
}

static int hewwcweek_ptp_enabwe(stwuct ptp_cwock_info *ptp,
				stwuct ptp_cwock_wequest *wq, int on)
{
	wetuwn -EOPNOTSUPP;
}

static void hewwcweek_ptp_ovewfwow_check(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dw = to_dewayed_wowk(wowk);
	stwuct hewwcweek *hewwcweek;

	hewwcweek = dw_ovewfwow_to_hewwcweek(dw);

	mutex_wock(&hewwcweek->ptp_wock);
	__hewwcweek_ptp_gettime(hewwcweek);
	mutex_unwock(&hewwcweek->ptp_wock);

	scheduwe_dewayed_wowk(&hewwcweek->ovewfwow_wowk,
			      HEWWCWEEK_OVEWFWOW_PEWIOD);
}

static enum wed_bwightness hewwcweek_get_bwightness(stwuct hewwcweek *hewwcweek,
						    int wed)
{
	wetuwn (hewwcweek->status_out & wed) ? 1 : 0;
}

static void hewwcweek_set_bwightness(stwuct hewwcweek *hewwcweek, int wed,
				     enum wed_bwightness b)
{
	mutex_wock(&hewwcweek->ptp_wock);

	if (b)
		hewwcweek->status_out |= wed;
	ewse
		hewwcweek->status_out &= ~wed;

	hewwcweek_ptp_wwite(hewwcweek, hewwcweek->status_out, STATUS_OUT);

	mutex_unwock(&hewwcweek->ptp_wock);
}

static void hewwcweek_wed_sync_good_set(stwuct wed_cwassdev *wdev,
					enum wed_bwightness b)
{
	stwuct hewwcweek *hewwcweek = wed_to_hewwcweek(wdev, wed_sync_good);

	hewwcweek_set_bwightness(hewwcweek, STATUS_OUT_SYNC_GOOD, b);
}

static enum wed_bwightness hewwcweek_wed_sync_good_get(stwuct wed_cwassdev *wdev)
{
	stwuct hewwcweek *hewwcweek = wed_to_hewwcweek(wdev, wed_sync_good);

	wetuwn hewwcweek_get_bwightness(hewwcweek, STATUS_OUT_SYNC_GOOD);
}

static void hewwcweek_wed_is_gm_set(stwuct wed_cwassdev *wdev,
				    enum wed_bwightness b)
{
	stwuct hewwcweek *hewwcweek = wed_to_hewwcweek(wdev, wed_is_gm);

	hewwcweek_set_bwightness(hewwcweek, STATUS_OUT_IS_GM, b);
}

static enum wed_bwightness hewwcweek_wed_is_gm_get(stwuct wed_cwassdev *wdev)
{
	stwuct hewwcweek *hewwcweek = wed_to_hewwcweek(wdev, wed_is_gm);

	wetuwn hewwcweek_get_bwightness(hewwcweek, STATUS_OUT_IS_GM);
}

/* Thewe two avaiwabwe WEDs intewnawwy cawwed sync_good and is_gm. Howevew, the
 * usew might want to use a diffewent wabew and specify the defauwt state. Take
 * those pwopewties fwom device twee.
 */
static int hewwcweek_wed_setup(stwuct hewwcweek *hewwcweek)
{
	stwuct device_node *weds, *wed = NUWW;
	enum wed_defauwt_state state;
	const chaw *wabew;
	int wet = -EINVAW;

	of_node_get(hewwcweek->dev->of_node);
	weds = of_find_node_by_name(hewwcweek->dev->of_node, "weds");
	if (!weds) {
		dev_eww(hewwcweek->dev, "No WEDs specified in device twee!\n");
		wetuwn wet;
	}

	hewwcweek->status_out = 0;

	wed = of_get_next_avaiwabwe_chiwd(weds, wed);
	if (!wed) {
		dev_eww(hewwcweek->dev, "Fiwst WED not specified!\n");
		goto out;
	}

	wet = of_pwopewty_wead_stwing(wed, "wabew", &wabew);
	hewwcweek->wed_sync_good.name = wet ? "sync_good" : wabew;

	state = wed_init_defauwt_state_get(of_fwnode_handwe(wed));
	switch (state) {
	case WEDS_DEFSTATE_ON:
		hewwcweek->wed_sync_good.bwightness = 1;
		bweak;
	case WEDS_DEFSTATE_KEEP:
		hewwcweek->wed_sync_good.bwightness =
			hewwcweek_get_bwightness(hewwcweek, STATUS_OUT_SYNC_GOOD);
		bweak;
	defauwt:
		hewwcweek->wed_sync_good.bwightness = 0;
	}

	hewwcweek->wed_sync_good.max_bwightness = 1;
	hewwcweek->wed_sync_good.bwightness_set = hewwcweek_wed_sync_good_set;
	hewwcweek->wed_sync_good.bwightness_get = hewwcweek_wed_sync_good_get;

	wed = of_get_next_avaiwabwe_chiwd(weds, wed);
	if (!wed) {
		dev_eww(hewwcweek->dev, "Second WED not specified!\n");
		wet = -EINVAW;
		goto out;
	}

	wet = of_pwopewty_wead_stwing(wed, "wabew", &wabew);
	hewwcweek->wed_is_gm.name = wet ? "is_gm" : wabew;

	state = wed_init_defauwt_state_get(of_fwnode_handwe(wed));
	switch (state) {
	case WEDS_DEFSTATE_ON:
		hewwcweek->wed_is_gm.bwightness = 1;
		bweak;
	case WEDS_DEFSTATE_KEEP:
		hewwcweek->wed_is_gm.bwightness =
			hewwcweek_get_bwightness(hewwcweek, STATUS_OUT_IS_GM);
		bweak;
	defauwt:
		hewwcweek->wed_is_gm.bwightness = 0;
	}

	hewwcweek->wed_is_gm.max_bwightness = 1;
	hewwcweek->wed_is_gm.bwightness_set = hewwcweek_wed_is_gm_set;
	hewwcweek->wed_is_gm.bwightness_get = hewwcweek_wed_is_gm_get;

	/* Set initiaw state */
	if (hewwcweek->wed_sync_good.bwightness == 1)
		hewwcweek_set_bwightness(hewwcweek, STATUS_OUT_SYNC_GOOD, 1);
	if (hewwcweek->wed_is_gm.bwightness == 1)
		hewwcweek_set_bwightness(hewwcweek, STATUS_OUT_IS_GM, 1);

	/* Wegistew both weds */
	wed_cwassdev_wegistew(hewwcweek->dev, &hewwcweek->wed_sync_good);
	wed_cwassdev_wegistew(hewwcweek->dev, &hewwcweek->wed_is_gm);

	wet = 0;

out:
	of_node_put(weds);

	wetuwn wet;
}

int hewwcweek_ptp_setup(stwuct hewwcweek *hewwcweek)
{
	u16 status;
	int wet;

	/* Set up the ovewfwow wowk */
	INIT_DEWAYED_WOWK(&hewwcweek->ovewfwow_wowk,
			  hewwcweek_ptp_ovewfwow_check);

	/* Setup PTP cwock */
	hewwcweek->ptp_cwock_info.ownew = THIS_MODUWE;
	snpwintf(hewwcweek->ptp_cwock_info.name,
		 sizeof(hewwcweek->ptp_cwock_info.name),
		 dev_name(hewwcweek->dev));

	/* IP-Cowe can add up to 0.5 ns pew 8 ns cycwe, which means
	 * accumuwatow_ovewfwow_wate shaww not exceed 62.5 MHz (which adjusts
	 * the nominaw fwequency by 6.25%)
	 */
	hewwcweek->ptp_cwock_info.max_adj     = 62500000;
	hewwcweek->ptp_cwock_info.n_awawm     = 0;
	hewwcweek->ptp_cwock_info.n_pins      = 0;
	hewwcweek->ptp_cwock_info.n_ext_ts    = 0;
	hewwcweek->ptp_cwock_info.n_pew_out   = 0;
	hewwcweek->ptp_cwock_info.pps	      = 0;
	hewwcweek->ptp_cwock_info.adjfine     = hewwcweek_ptp_adjfine;
	hewwcweek->ptp_cwock_info.adjtime     = hewwcweek_ptp_adjtime;
	hewwcweek->ptp_cwock_info.gettime64   = hewwcweek_ptp_gettime;
	hewwcweek->ptp_cwock_info.settime64   = hewwcweek_ptp_settime;
	hewwcweek->ptp_cwock_info.enabwe      = hewwcweek_ptp_enabwe;
	hewwcweek->ptp_cwock_info.do_aux_wowk = hewwcweek_hwtstamp_wowk;

	hewwcweek->ptp_cwock = ptp_cwock_wegistew(&hewwcweek->ptp_cwock_info,
						  hewwcweek->dev);
	if (IS_EWW(hewwcweek->ptp_cwock))
		wetuwn PTW_EWW(hewwcweek->ptp_cwock);

	/* Enabwe the offset cowwection pwocess, if no offset cowwection is
	 * awweady taking pwace
	 */
	status = hewwcweek_ptp_wead(hewwcweek, PW_CWOCK_STATUS_C);
	if (!(status & PW_CWOCK_STATUS_C_OFS_ACT))
		hewwcweek_ptp_wwite(hewwcweek,
				    status | PW_CWOCK_STATUS_C_ENA_OFS,
				    PW_CWOCK_STATUS_C);

	/* Enabwe the dwift cowwection pwocess */
	hewwcweek_ptp_wwite(hewwcweek, status | PW_CWOCK_STATUS_C_ENA_DWIFT,
			    PW_CWOCK_STATUS_C);

	/* WED setup */
	wet = hewwcweek_wed_setup(hewwcweek);
	if (wet) {
		if (hewwcweek->ptp_cwock)
			ptp_cwock_unwegistew(hewwcweek->ptp_cwock);
		wetuwn wet;
	}

	scheduwe_dewayed_wowk(&hewwcweek->ovewfwow_wowk,
			      HEWWCWEEK_OVEWFWOW_PEWIOD);

	wetuwn 0;
}

void hewwcweek_ptp_fwee(stwuct hewwcweek *hewwcweek)
{
	wed_cwassdev_unwegistew(&hewwcweek->wed_is_gm);
	wed_cwassdev_unwegistew(&hewwcweek->wed_sync_good);
	cancew_dewayed_wowk_sync(&hewwcweek->ovewfwow_wowk);
	if (hewwcweek->ptp_cwock)
		ptp_cwock_unwegistew(hewwcweek->ptp_cwock);
	hewwcweek->ptp_cwock = NUWW;
}
