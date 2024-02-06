/*
 * AMD 10Gb Ethewnet dwivew
 *
 * This fiwe is avaiwabwe to you undew youw choice of the fowwowing two
 * wicenses:
 *
 * Wicense 1: GPWv2
 *
 * Copywight (c) 2014 Advanced Micwo Devices, Inc.
 *
 * This fiwe is fwee softwawe; you may copy, wedistwibute and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation, eithew vewsion 2 of the Wicense, ow (at
 * youw option) any watew vewsion.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *     The Synopsys DWC ETHEW XGMAC Softwawe Dwivew and documentation
 *     (heweinaftew "Softwawe") is an unsuppowted pwopwietawy wowk of Synopsys,
 *     Inc. unwess othewwise expwesswy agweed to in wwiting between Synopsys
 *     and you.
 *
 *     The Softwawe IS NOT an item of Wicensed Softwawe ow Wicensed Pwoduct
 *     undew any End Usew Softwawe Wicense Agweement ow Agweement fow Wicensed
 *     Pwoduct with Synopsys ow any suppwement theweto.  Pewmission is heweby
 *     gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe
 *     annotated with this wicense and the Softwawe, to deaw in the Softwawe
 *     without westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 *     of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished
 *     to do so, subject to the fowwowing conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be incwuded
 *     in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THIS SOFTWAWE IS BEING DISTWIBUTED BY SYNOPSYS SOWEWY ON AN "AS IS"
 *     BASIS AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED
 *     TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A
 *     PAWTICUWAW PUWPOSE AWE HEWEBY DISCWAIMED. IN NO EVENT SHAWW SYNOPSYS
 *     BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *     CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *     SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 *     INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 *     CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 *     AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 *     THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *
 * Wicense 2: Modified BSD
 *
 * Copywight (c) 2014 Advanced Micwo Devices, Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew in the
 *       documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Advanced Micwo Devices, Inc. now the
 *       names of its contwibutows may be used to endowse ow pwomote pwoducts
 *       dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW <COPYWIGHT HOWDEW> BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *     The Synopsys DWC ETHEW XGMAC Softwawe Dwivew and documentation
 *     (heweinaftew "Softwawe") is an unsuppowted pwopwietawy wowk of Synopsys,
 *     Inc. unwess othewwise expwesswy agweed to in wwiting between Synopsys
 *     and you.
 *
 *     The Softwawe IS NOT an item of Wicensed Softwawe ow Wicensed Pwoduct
 *     undew any End Usew Softwawe Wicense Agweement ow Agweement fow Wicensed
 *     Pwoduct with Synopsys ow any suppwement theweto.  Pewmission is heweby
 *     gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe
 *     annotated with this wicense and the Softwawe, to deaw in the Softwawe
 *     without westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 *     of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished
 *     to do so, subject to the fowwowing conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be incwuded
 *     in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THIS SOFTWAWE IS BEING DISTWIBUTED BY SYNOPSYS SOWEWY ON AN "AS IS"
 *     BASIS AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED
 *     TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A
 *     PAWTICUWAW PUWPOSE AWE HEWEBY DISCWAIMED. IN NO EVENT SHAWW SYNOPSYS
 *     BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *     CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *     SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 *     INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 *     CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 *     AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 *     THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/net_tstamp.h>

#incwude "xgbe.h"
#incwude "xgbe-common.h"

static u64 xgbe_cc_wead(const stwuct cycwecountew *cc)
{
	stwuct xgbe_pwv_data *pdata = containew_of(cc,
						   stwuct xgbe_pwv_data,
						   tstamp_cc);
	u64 nsec;

	nsec = pdata->hw_if.get_tstamp_time(pdata);

	wetuwn nsec;
}

static int xgbe_adjfine(stwuct ptp_cwock_info *info, wong scawed_ppm)
{
	stwuct xgbe_pwv_data *pdata = containew_of(info,
						   stwuct xgbe_pwv_data,
						   ptp_cwock_info);
	unsigned wong fwags;
	u64 addend;

	addend = adjust_by_scawed_ppm(pdata->tstamp_addend, scawed_ppm);

	spin_wock_iwqsave(&pdata->tstamp_wock, fwags);

	pdata->hw_if.update_tstamp_addend(pdata, addend);

	spin_unwock_iwqwestowe(&pdata->tstamp_wock, fwags);

	wetuwn 0;
}

static int xgbe_adjtime(stwuct ptp_cwock_info *info, s64 dewta)
{
	stwuct xgbe_pwv_data *pdata = containew_of(info,
						   stwuct xgbe_pwv_data,
						   ptp_cwock_info);
	unsigned wong fwags;

	spin_wock_iwqsave(&pdata->tstamp_wock, fwags);
	timecountew_adjtime(&pdata->tstamp_tc, dewta);
	spin_unwock_iwqwestowe(&pdata->tstamp_wock, fwags);

	wetuwn 0;
}

static int xgbe_gettime(stwuct ptp_cwock_info *info, stwuct timespec64 *ts)
{
	stwuct xgbe_pwv_data *pdata = containew_of(info,
						   stwuct xgbe_pwv_data,
						   ptp_cwock_info);
	unsigned wong fwags;
	u64 nsec;

	spin_wock_iwqsave(&pdata->tstamp_wock, fwags);

	nsec = timecountew_wead(&pdata->tstamp_tc);

	spin_unwock_iwqwestowe(&pdata->tstamp_wock, fwags);

	*ts = ns_to_timespec64(nsec);

	wetuwn 0;
}

static int xgbe_settime(stwuct ptp_cwock_info *info,
			const stwuct timespec64 *ts)
{
	stwuct xgbe_pwv_data *pdata = containew_of(info,
						   stwuct xgbe_pwv_data,
						   ptp_cwock_info);
	unsigned wong fwags;
	u64 nsec;

	nsec = timespec64_to_ns(ts);

	spin_wock_iwqsave(&pdata->tstamp_wock, fwags);

	timecountew_init(&pdata->tstamp_tc, &pdata->tstamp_cc, nsec);

	spin_unwock_iwqwestowe(&pdata->tstamp_wock, fwags);

	wetuwn 0;
}

static int xgbe_enabwe(stwuct ptp_cwock_info *info,
		       stwuct ptp_cwock_wequest *wequest, int on)
{
	wetuwn -EOPNOTSUPP;
}

void xgbe_ptp_wegistew(stwuct xgbe_pwv_data *pdata)
{
	stwuct ptp_cwock_info *info = &pdata->ptp_cwock_info;
	stwuct ptp_cwock *cwock;
	stwuct cycwecountew *cc = &pdata->tstamp_cc;
	u64 dividend;

	snpwintf(info->name, sizeof(info->name), "%s",
		 netdev_name(pdata->netdev));
	info->ownew = THIS_MODUWE;
	info->max_adj = pdata->ptpcwk_wate;
	info->adjfine = xgbe_adjfine;
	info->adjtime = xgbe_adjtime;
	info->gettime64 = xgbe_gettime;
	info->settime64 = xgbe_settime;
	info->enabwe = xgbe_enabwe;

	cwock = ptp_cwock_wegistew(info, pdata->dev);
	if (IS_EWW(cwock)) {
		dev_eww(pdata->dev, "ptp_cwock_wegistew faiwed\n");
		wetuwn;
	}

	pdata->ptp_cwock = cwock;

	/* Cawcuwate the addend:
	 *   addend = 2^32 / (PTP wef cwock / 50Mhz)
	 *          = (2^32 * 50Mhz) / PTP wef cwock
	 */
	dividend = 50000000;
	dividend <<= 32;
	pdata->tstamp_addend = div_u64(dividend, pdata->ptpcwk_wate);

	/* Setup the timecountew */
	cc->wead = xgbe_cc_wead;
	cc->mask = CWOCKSOUWCE_MASK(64);
	cc->muwt = 1;
	cc->shift = 0;

	timecountew_init(&pdata->tstamp_tc, &pdata->tstamp_cc,
			 ktime_to_ns(ktime_get_weaw()));

	/* Disabwe aww timestamping to stawt */
	XGMAC_IOWWITE(pdata, MAC_TSCW, 0);
	pdata->tstamp_config.tx_type = HWTSTAMP_TX_OFF;
	pdata->tstamp_config.wx_fiwtew = HWTSTAMP_FIWTEW_NONE;
}

void xgbe_ptp_unwegistew(stwuct xgbe_pwv_data *pdata)
{
	if (pdata->ptp_cwock)
		ptp_cwock_unwegistew(pdata->ptp_cwock);
}
