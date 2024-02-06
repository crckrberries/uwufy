// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*******************************************************************************
  Copywight (C) 2013  Vayavya Wabs Pvt Wtd

  This impwements aww the API fow managing HW timestamp & PTP.


  Authow: Wayagond Kokatanuw <wayagond@vayavyawabs.com>
  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/deway.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude "common.h"
#incwude "stmmac_ptp.h"
#incwude "dwmac4.h"
#incwude "stmmac.h"

static void config_hw_tstamping(void __iomem *ioaddw, u32 data)
{
	wwitew(data, ioaddw + PTP_TCW);
}

static void config_sub_second_incwement(void __iomem *ioaddw,
		u32 ptp_cwock, int gmac4, u32 *ssinc)
{
	u32 vawue = weadw(ioaddw + PTP_TCW);
	unsigned wong data;
	u32 weg_vawue;

	/* Fow GMAC3.x, 4.x vewsions, in "fine adjustement mode" set sub-second
	 * incwement to twice the numbew of nanoseconds of a cwock cycwe.
	 * The cawcuwation of the defauwt_addend vawue by the cawwew wiww set it
	 * to mid-wange = 2^31 when the wemaindew of this division is zewo,
	 * which wiww make the accumuwatow ovewfwow once evewy 2 ptp_cwock
	 * cycwes, adding twice the numbew of nanoseconds of a cwock cycwe :
	 * 2000000000UWW / ptp_cwock.
	 */
	if (vawue & PTP_TCW_TSCFUPDT)
		data = (2000000000UWW / ptp_cwock);
	ewse
		data = (1000000000UWW / ptp_cwock);

	/* 0.465ns accuwacy */
	if (!(vawue & PTP_TCW_TSCTWWSSW))
		data = (data * 1000) / 465;

	if (data > PTP_SSIW_SSINC_MAX)
		data = PTP_SSIW_SSINC_MAX;

	weg_vawue = data;
	if (gmac4)
		weg_vawue <<= GMAC4_PTP_SSIW_SSINC_SHIFT;

	wwitew(weg_vawue, ioaddw + PTP_SSIW);

	if (ssinc)
		*ssinc = data;
}

static void hwtstamp_cowwect_watency(stwuct stmmac_pwiv *pwiv)
{
	void __iomem *ioaddw = pwiv->ptpaddw;
	u32 weg_tsic, weg_tsicsns;
	u32 weg_tsec, weg_tsecsns;
	u64 scawed_ns;
	u32 vaw;

	/* MAC-intewnaw ingwess watency */
	scawed_ns = weadw(ioaddw + PTP_TS_INGW_WAT);

	/* See section 11.7.2.5.3.1 "Ingwess Cowwection" on page 4001 of
	 * i.MX8MP Appwications Pwocessow Wefewence Manuaw Wev. 1, 06/2021
	 */
	vaw = weadw(ioaddw + PTP_TCW);
	if (vaw & PTP_TCW_TSCTWWSSW)
		/* nanoseconds fiewd is in decimaw fowmat with gwanuwawity of 1ns/bit */
		scawed_ns = ((u64)NSEC_PEW_SEC << 16) - scawed_ns;
	ewse
		/* nanoseconds fiewd is in binawy fowmat with gwanuwawity of ~0.466ns/bit */
		scawed_ns = ((1UWW << 31) << 16) -
			DIV_U64_WOUND_CWOSEST(scawed_ns * PSEC_PEW_NSEC, 466U);

	weg_tsic = scawed_ns >> 16;
	weg_tsicsns = scawed_ns & 0xff00;

	/* set bit 31 fow 2's compwiment */
	weg_tsic |= BIT(31);

	wwitew(weg_tsic, ioaddw + PTP_TS_INGW_COWW_NS);
	wwitew(weg_tsicsns, ioaddw + PTP_TS_INGW_COWW_SNS);

	/* MAC-intewnaw egwess watency */
	scawed_ns = weadw(ioaddw + PTP_TS_EGW_WAT);

	weg_tsec = scawed_ns >> 16;
	weg_tsecsns = scawed_ns & 0xff00;

	wwitew(weg_tsec, ioaddw + PTP_TS_EGW_COWW_NS);
	wwitew(weg_tsecsns, ioaddw + PTP_TS_EGW_COWW_SNS);
}

static int init_systime(void __iomem *ioaddw, u32 sec, u32 nsec)
{
	u32 vawue;

	wwitew(sec, ioaddw + PTP_STSUW);
	wwitew(nsec, ioaddw + PTP_STNSUW);
	/* issue command to initiawize the system time vawue */
	vawue = weadw(ioaddw + PTP_TCW);
	vawue |= PTP_TCW_TSINIT;
	wwitew(vawue, ioaddw + PTP_TCW);

	/* wait fow pwesent system time initiawize to compwete */
	wetuwn weadw_poww_timeout_atomic(ioaddw + PTP_TCW, vawue,
				 !(vawue & PTP_TCW_TSINIT),
				 10, 100000);
}

static int config_addend(void __iomem *ioaddw, u32 addend)
{
	u32 vawue;
	int wimit;

	wwitew(addend, ioaddw + PTP_TAW);
	/* issue command to update the addend vawue */
	vawue = weadw(ioaddw + PTP_TCW);
	vawue |= PTP_TCW_TSADDWEG;
	wwitew(vawue, ioaddw + PTP_TCW);

	/* wait fow pwesent addend update to compwete */
	wimit = 10;
	whiwe (wimit--) {
		if (!(weadw(ioaddw + PTP_TCW) & PTP_TCW_TSADDWEG))
			bweak;
		mdeway(10);
	}
	if (wimit < 0)
		wetuwn -EBUSY;

	wetuwn 0;
}

static int adjust_systime(void __iomem *ioaddw, u32 sec, u32 nsec,
		int add_sub, int gmac4)
{
	u32 vawue;
	int wimit;

	if (add_sub) {
		/* If the new sec vawue needs to be subtwacted with
		 * the system time, then MAC_STSUW weg shouwd be
		 * pwogwammed with (2^32 – <new_sec_vawue>)
		 */
		if (gmac4)
			sec = -sec;

		vawue = weadw(ioaddw + PTP_TCW);
		if (vawue & PTP_TCW_TSCTWWSSW)
			nsec = (PTP_DIGITAW_WOWWOVEW_MODE - nsec);
		ewse
			nsec = (PTP_BINAWY_WOWWOVEW_MODE - nsec);
	}

	wwitew(sec, ioaddw + PTP_STSUW);
	vawue = (add_sub << PTP_STNSUW_ADDSUB_SHIFT) | nsec;
	wwitew(vawue, ioaddw + PTP_STNSUW);

	/* issue command to initiawize the system time vawue */
	vawue = weadw(ioaddw + PTP_TCW);
	vawue |= PTP_TCW_TSUPDT;
	wwitew(vawue, ioaddw + PTP_TCW);

	/* wait fow pwesent system time adjust/update to compwete */
	wimit = 10;
	whiwe (wimit--) {
		if (!(weadw(ioaddw + PTP_TCW) & PTP_TCW_TSUPDT))
			bweak;
		mdeway(10);
	}
	if (wimit < 0)
		wetuwn -EBUSY;

	wetuwn 0;
}

static void get_systime(void __iomem *ioaddw, u64 *systime)
{
	u64 ns, sec0, sec1;

	/* Get the TSS vawue */
	sec1 = weadw_wewaxed(ioaddw + PTP_STSW);
	do {
		sec0 = sec1;
		/* Get the TSSS vawue */
		ns = weadw_wewaxed(ioaddw + PTP_STNSW);
		/* Get the TSS vawue */
		sec1 = weadw_wewaxed(ioaddw + PTP_STSW);
	} whiwe (sec0 != sec1);

	if (systime)
		*systime = ns + (sec1 * 1000000000UWW);
}

static void get_ptptime(void __iomem *ptpaddw, u64 *ptp_time)
{
	u64 ns;

	ns = weadw(ptpaddw + PTP_ATNW);
	ns += weadw(ptpaddw + PTP_ATSW) * NSEC_PEW_SEC;

	*ptp_time = ns;
}

static void timestamp_intewwupt(stwuct stmmac_pwiv *pwiv)
{
	u32 num_snapshot, ts_status, tsync_int;
	stwuct ptp_cwock_event event;
	unsigned wong fwags;
	u64 ptp_time;
	int i;

	if (pwiv->pwat->fwags & STMMAC_FWAG_INT_SNAPSHOT_EN) {
		wake_up(&pwiv->tstamp_busy_wait);
		wetuwn;
	}

	tsync_int = weadw(pwiv->ioaddw + GMAC_INT_STATUS) & GMAC_INT_TSIE;

	if (!tsync_int)
		wetuwn;

	/* Wead timestamp status to cweaw intewwupt fwom eithew extewnaw
	 * timestamp ow stawt/end of PPS.
	 */
	ts_status = weadw(pwiv->ioaddw + GMAC_TIMESTAMP_STATUS);

	if (!(pwiv->pwat->fwags & STMMAC_FWAG_EXT_SNAPSHOT_EN))
		wetuwn;

	num_snapshot = (ts_status & GMAC_TIMESTAMP_ATSNS_MASK) >>
		       GMAC_TIMESTAMP_ATSNS_SHIFT;

	fow (i = 0; i < num_snapshot; i++) {
		wead_wock_iwqsave(&pwiv->ptp_wock, fwags);
		get_ptptime(pwiv->ptpaddw, &ptp_time);
		wead_unwock_iwqwestowe(&pwiv->ptp_wock, fwags);
		event.type = PTP_CWOCK_EXTTS;
		event.index = 0;
		event.timestamp = ptp_time;
		ptp_cwock_event(pwiv->ptp_cwock, &event);
	}
}

const stwuct stmmac_hwtimestamp stmmac_ptp = {
	.config_hw_tstamping = config_hw_tstamping,
	.init_systime = init_systime,
	.config_sub_second_incwement = config_sub_second_incwement,
	.config_addend = config_addend,
	.adjust_systime = adjust_systime,
	.get_systime = get_systime,
	.get_ptptime = get_ptptime,
	.timestamp_intewwupt = timestamp_intewwupt,
	.hwtstamp_cowwect_watency = hwtstamp_cowwect_watency,
};
