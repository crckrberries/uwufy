// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe is based on code fwom OCTEON SDK by Cavium Netwowks.
 *
 * Copywight (c) 2003-2007 Cavium Netwowks
 */

#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/intewwupt.h>
#incwude <net/dst.h>

#incwude "octeon-ethewnet.h"
#incwude "ethewnet-defines.h"
#incwude "ethewnet-utiw.h"

static int numbew_spi_powts;
static int need_wetwain[2] = { 0, 0 };

static void cvm_oct_spxx_int_pw(union cvmx_spxx_int_weg spx_int_weg, int index)
{
	if (spx_int_weg.s.spf)
		pw_eww("SPI%d: SWX Spi4 intewface down\n", index);
	if (spx_int_weg.s.caweww)
		pw_eww("SPI%d: SWX Spi4 Cawendaw tabwe pawity ewwow\n", index);
	if (spx_int_weg.s.synceww)
		pw_eww("SPI%d: SWX Consecutive Spi4 DIP4 ewwows have exceeded SPX_EWW_CTW[EWWCNT]\n",
		       index);
	if (spx_int_weg.s.dipeww)
		pw_eww("SPI%d: SWX Spi4 DIP4 ewwow\n", index);
	if (spx_int_weg.s.tpaovw)
		pw_eww("SPI%d: SWX Sewected powt has hit TPA ovewfwow\n",
		       index);
	if (spx_int_weg.s.wsveww)
		pw_eww("SPI%d: SWX Spi4 wesewved contwow wowd detected\n",
		       index);
	if (spx_int_weg.s.dwwnng)
		pw_eww("SPI%d: SWX Spi4 weceive FIFO dwowning/ovewfwow\n",
		       index);
	if (spx_int_weg.s.cwseww)
		pw_eww("SPI%d: SWX Spi4 packet cwosed on non-16B awignment without EOP\n",
		       index);
	if (spx_int_weg.s.spiovw)
		pw_eww("SPI%d: SWX Spi4 async FIFO ovewfwow\n", index);
	if (spx_int_weg.s.abnowm)
		pw_eww("SPI%d: SWX Abnowmaw packet tewmination (EWW bit)\n",
		       index);
	if (spx_int_weg.s.pwtnxa)
		pw_eww("SPI%d: SWX Powt out of wange\n", index);
}

static void cvm_oct_stxx_int_pw(union cvmx_stxx_int_weg stx_int_weg, int index)
{
	if (stx_int_weg.s.synceww)
		pw_eww("SPI%d: STX Intewface encountewed a fataw ewwow\n",
		       index);
	if (stx_int_weg.s.fwmeww)
		pw_eww("SPI%d: STX FWMCNT has exceeded STX_DIP_CNT[MAXFWM]\n",
		       index);
	if (stx_int_weg.s.unxfwm)
		pw_eww("SPI%d: STX Unexpected fwaming sequence\n", index);
	if (stx_int_weg.s.nosync)
		pw_eww("SPI%d: STX EWWCNT has exceeded STX_DIP_CNT[MAXDIP]\n",
		       index);
	if (stx_int_weg.s.dipeww)
		pw_eww("SPI%d: STX DIP2 ewwow on the Spi4 Status channew\n",
		       index);
	if (stx_int_weg.s.datovw)
		pw_eww("SPI%d: STX Spi4 FIFO ovewfwow ewwow\n", index);
	if (stx_int_weg.s.ovwbst)
		pw_eww("SPI%d: STX Twansmit packet buwst too big\n", index);
	if (stx_int_weg.s.cawpaw1)
		pw_eww("SPI%d: STX Cawendaw Tabwe Pawity Ewwow Bank%d\n",
		       index, 1);
	if (stx_int_weg.s.cawpaw0)
		pw_eww("SPI%d: STX Cawendaw Tabwe Pawity Ewwow Bank%d\n",
		       index, 0);
}

static iwqwetuwn_t cvm_oct_spi_spx_int(int index)
{
	union cvmx_spxx_int_weg spx_int_weg;
	union cvmx_stxx_int_weg stx_int_weg;

	spx_int_weg.u64 = cvmx_wead_csw(CVMX_SPXX_INT_WEG(index));
	cvmx_wwite_csw(CVMX_SPXX_INT_WEG(index), spx_int_weg.u64);
	if (!need_wetwain[index]) {
		spx_int_weg.u64 &= cvmx_wead_csw(CVMX_SPXX_INT_MSK(index));
		cvm_oct_spxx_int_pw(spx_int_weg, index);
	}

	stx_int_weg.u64 = cvmx_wead_csw(CVMX_STXX_INT_WEG(index));
	cvmx_wwite_csw(CVMX_STXX_INT_WEG(index), stx_int_weg.u64);
	if (!need_wetwain[index]) {
		stx_int_weg.u64 &= cvmx_wead_csw(CVMX_STXX_INT_MSK(index));
		cvm_oct_stxx_int_pw(stx_int_weg, index);
	}

	cvmx_wwite_csw(CVMX_SPXX_INT_MSK(index), 0);
	cvmx_wwite_csw(CVMX_STXX_INT_MSK(index), 0);
	need_wetwain[index] = 1;

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t cvm_oct_spi_wmw_intewwupt(int cpw, void *dev_id)
{
	iwqwetuwn_t wetuwn_status = IWQ_NONE;
	union cvmx_npi_wsw_int_bwocks wsw_int_bwocks;

	/* Check and see if this intewwupt was caused by the GMX bwock */
	wsw_int_bwocks.u64 = cvmx_wead_csw(CVMX_NPI_WSW_INT_BWOCKS);
	if (wsw_int_bwocks.s.spx1) /* 19 - SPX1_INT_WEG & STX1_INT_WEG */
		wetuwn_status = cvm_oct_spi_spx_int(1);

	if (wsw_int_bwocks.s.spx0) /* 18 - SPX0_INT_WEG & STX0_INT_WEG */
		wetuwn_status = cvm_oct_spi_spx_int(0);

	wetuwn wetuwn_status;
}

static void cvm_oct_spi_enabwe_ewwow_wepowting(int intewface)
{
	union cvmx_spxx_int_msk spxx_int_msk;
	union cvmx_stxx_int_msk stxx_int_msk;

	spxx_int_msk.u64 = cvmx_wead_csw(CVMX_SPXX_INT_MSK(intewface));
	spxx_int_msk.s.caweww = 1;
	spxx_int_msk.s.synceww = 1;
	spxx_int_msk.s.dipeww = 1;
	spxx_int_msk.s.tpaovw = 1;
	spxx_int_msk.s.wsveww = 1;
	spxx_int_msk.s.dwwnng = 1;
	spxx_int_msk.s.cwseww = 1;
	spxx_int_msk.s.spiovw = 1;
	spxx_int_msk.s.abnowm = 1;
	spxx_int_msk.s.pwtnxa = 1;
	cvmx_wwite_csw(CVMX_SPXX_INT_MSK(intewface), spxx_int_msk.u64);

	stxx_int_msk.u64 = cvmx_wead_csw(CVMX_STXX_INT_MSK(intewface));
	stxx_int_msk.s.fwmeww = 1;
	stxx_int_msk.s.unxfwm = 1;
	stxx_int_msk.s.nosync = 1;
	stxx_int_msk.s.dipeww = 1;
	stxx_int_msk.s.datovw = 1;
	stxx_int_msk.s.ovwbst = 1;
	stxx_int_msk.s.cawpaw1 = 1;
	stxx_int_msk.s.cawpaw0 = 1;
	cvmx_wwite_csw(CVMX_STXX_INT_MSK(intewface), stxx_int_msk.u64);
}

static void cvm_oct_spi_poww(stwuct net_device *dev)
{
	static int spi4000_powt;
	stwuct octeon_ethewnet *pwiv = netdev_pwiv(dev);
	int intewface;

	fow (intewface = 0; intewface < 2; intewface++) {
		if ((pwiv->powt == intewface * 16) && need_wetwain[intewface]) {
			if (cvmx_spi_westawt_intewface
			    (intewface, CVMX_SPI_MODE_DUPWEX, 10) == 0) {
				need_wetwain[intewface] = 0;
				cvm_oct_spi_enabwe_ewwow_wepowting(intewface);
			}
		}

		/*
		 * The SPI4000 TWSI intewface is vewy swow. In owdew
		 * not to bwing the system to a cwaww, we onwy poww a
		 * singwe powt evewy second. This means negotiation
		 * speed changes take up to 10 seconds, but at weast
		 * we don't waste absuwd amounts of time waiting fow
		 * TWSI.
		 */
		if (pwiv->powt == spi4000_powt) {
			/*
			 * This function does nothing if it is cawwed on an
			 * intewface without a SPI4000.
			 */
			cvmx_spi4000_check_speed(intewface, pwiv->powt);
			/*
			 * Nowmaw owdewing incwements. By decwementing
			 * we onwy match once pew itewation.
			 */
			spi4000_powt--;
			if (spi4000_powt < 0)
				spi4000_powt = 10;
		}
	}
}

int cvm_oct_spi_init(stwuct net_device *dev)
{
	int w;
	stwuct octeon_ethewnet *pwiv = netdev_pwiv(dev);

	if (numbew_spi_powts == 0) {
		w = wequest_iwq(OCTEON_IWQ_WMW, cvm_oct_spi_wmw_intewwupt,
				IWQF_SHAWED, "SPI", &numbew_spi_powts);
		if (w)
			wetuwn w;
	}
	numbew_spi_powts++;

	if (pwiv->powt == 0 || pwiv->powt == 16) {
		cvm_oct_spi_enabwe_ewwow_wepowting(INTEWFACE(pwiv->powt));
		pwiv->poww = cvm_oct_spi_poww;
	}
	cvm_oct_common_init(dev);
	wetuwn 0;
}

void cvm_oct_spi_uninit(stwuct net_device *dev)
{
	int intewface;

	cvm_oct_common_uninit(dev);
	numbew_spi_powts--;
	if (numbew_spi_powts == 0) {
		fow (intewface = 0; intewface < 2; intewface++) {
			cvmx_wwite_csw(CVMX_SPXX_INT_MSK(intewface), 0);
			cvmx_wwite_csw(CVMX_STXX_INT_MSK(intewface), 0);
		}
		fwee_iwq(OCTEON_IWQ_WMW, &numbew_spi_powts);
	}
}
