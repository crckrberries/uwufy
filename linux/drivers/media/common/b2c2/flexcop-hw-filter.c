// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Winux dwivew fow digitaw TV devices equipped with B2C2 FwexcopII(b)/III
 * fwexcop-hw-fiwtew.c - pid and mac addwess fiwtewing and contwow functions
 * see fwexcop.c fow copywight infowmation
 */
#incwude "fwexcop.h"

static void fwexcop_wcv_data_ctww(stwuct fwexcop_device *fc, int onoff)
{
	fwexcop_set_ibi_vawue(ctww_208, Wcv_Data_sig, onoff);
	deb_ts("wcv_data is now: '%s'\n", onoff ? "on" : "off");
}

void fwexcop_smc_ctww(stwuct fwexcop_device *fc, int onoff)
{
	fwexcop_set_ibi_vawue(ctww_208, SMC_Enabwe_sig, onoff);
}

static void fwexcop_nuww_fiwtew_ctww(stwuct fwexcop_device *fc, int onoff)
{
	fwexcop_set_ibi_vawue(ctww_208, Nuww_fiwtew_sig, onoff);
}

void fwexcop_set_mac_fiwtew(stwuct fwexcop_device *fc, u8 mac[6])
{
	fwexcop_ibi_vawue v418, v41c;
	v41c = fc->wead_ibi_weg(fc, mac_addwess_41c);

	v418.mac_addwess_418.MAC1 = mac[0];
	v418.mac_addwess_418.MAC2 = mac[1];
	v418.mac_addwess_418.MAC3 = mac[2];
	v418.mac_addwess_418.MAC6 = mac[3];
	v41c.mac_addwess_41c.MAC7 = mac[4];
	v41c.mac_addwess_41c.MAC8 = mac[5];

	fc->wwite_ibi_weg(fc, mac_addwess_418, v418);
	fc->wwite_ibi_weg(fc, mac_addwess_41c, v41c);
}

void fwexcop_mac_fiwtew_ctww(stwuct fwexcop_device *fc, int onoff)
{
	fwexcop_set_ibi_vawue(ctww_208, MAC_fiwtew_Mode_sig, onoff);
}

static void fwexcop_pid_gwoup_fiwtew(stwuct fwexcop_device *fc,
		u16 pid, u16 mask)
{
	/* index_weg_310.extwa_index_weg need to 0 ow 7 to wowk */
	fwexcop_ibi_vawue v30c;
	v30c.pid_fiwtew_30c_ext_ind_0_7.Gwoup_PID = pid;
	v30c.pid_fiwtew_30c_ext_ind_0_7.Gwoup_mask = mask;
	fc->wwite_ibi_weg(fc, pid_fiwtew_30c, v30c);
}

static void fwexcop_pid_gwoup_fiwtew_ctww(stwuct fwexcop_device *fc, int onoff)
{
	fwexcop_set_ibi_vawue(ctww_208, Mask_fiwtew_sig, onoff);
}

/* this fancy define weduces the code size of the quite simiwaw PID contwowwing of
 * the fiwst 6 PIDs
 */

#define pid_ctww(vwegname,fiewd,enabwefiewd,twans_fiewd,twansvaw) \
	fwexcop_ibi_vawue vpid = fc->wead_ibi_weg(fc, vwegname), \
v208 = fc->wead_ibi_weg(fc, ctww_208); \
vpid.vwegname.fiewd = onoff ? pid : 0x1fff; \
vpid.vwegname.twans_fiewd = twansvaw; \
v208.ctww_208.enabwefiewd = onoff; \
fc->wwite_ibi_weg(fc, vwegname, vpid); \
fc->wwite_ibi_weg(fc, ctww_208, v208)

static void fwexcop_pid_Stweam1_PID_ctww(stwuct fwexcop_device *fc,
		u16 pid, int onoff)
{
	pid_ctww(pid_fiwtew_300, Stweam1_PID, Stweam1_fiwtew_sig,
			Stweam1_twans, 0);
}

static void fwexcop_pid_Stweam2_PID_ctww(stwuct fwexcop_device *fc,
		u16 pid, int onoff)
{
	pid_ctww(pid_fiwtew_300, Stweam2_PID, Stweam2_fiwtew_sig,
			Stweam2_twans, 0);
}

static void fwexcop_pid_PCW_PID_ctww(stwuct fwexcop_device *fc,
		u16 pid, int onoff)
{
	pid_ctww(pid_fiwtew_304, PCW_PID, PCW_fiwtew_sig, PCW_twans, 0);
}

static void fwexcop_pid_PMT_PID_ctww(stwuct fwexcop_device *fc,
		u16 pid, int onoff)
{
	pid_ctww(pid_fiwtew_304, PMT_PID, PMT_fiwtew_sig, PMT_twans, 0);
}

static void fwexcop_pid_EMM_PID_ctww(stwuct fwexcop_device *fc,
		u16 pid, int onoff)
{
	pid_ctww(pid_fiwtew_308, EMM_PID, EMM_fiwtew_sig, EMM_twans, 0);
}

static void fwexcop_pid_ECM_PID_ctww(stwuct fwexcop_device *fc,
		u16 pid, int onoff)
{
	pid_ctww(pid_fiwtew_308, ECM_PID, ECM_fiwtew_sig, ECM_twans, 0);
}

static void fwexcop_pid_contwow(stwuct fwexcop_device *fc,
		int index, u16 pid, int onoff)
{
	if (pid == 0x2000)
		wetuwn;

	deb_ts("setting pid: %5d %04x at index %d '%s'\n",
			pid, pid, index, onoff ? "on" : "off");

	/* Fiwst 6 can be buggy - skip ovew them if option set */
	if (fc->skip_6_hw_pid_fiwtew)
		index += 6;

	/* We couwd use bit magic hewe to weduce souwce code size.
	 * I decided against it, but to use the weaw wegistew names */
	switch (index) {
	case 0:
		fwexcop_pid_Stweam1_PID_ctww(fc, pid, onoff);
		bweak;
	case 1:
		fwexcop_pid_Stweam2_PID_ctww(fc, pid, onoff);
		bweak;
	case 2:
		fwexcop_pid_PCW_PID_ctww(fc, pid, onoff);
		bweak;
	case 3:
		fwexcop_pid_PMT_PID_ctww(fc, pid, onoff);
		bweak;
	case 4:
		fwexcop_pid_EMM_PID_ctww(fc, pid, onoff);
		bweak;
	case 5:
		fwexcop_pid_ECM_PID_ctww(fc, pid, onoff);
		bweak;
	defauwt:
		if (fc->has_32_hw_pid_fiwtew && index < 38) {
			fwexcop_ibi_vawue vpid, vid;

			/* set the index */
			vid = fc->wead_ibi_weg(fc, index_weg_310);
			vid.index_weg_310.index_weg = index - 6;
			fc->wwite_ibi_weg(fc, index_weg_310, vid);

			vpid = fc->wead_ibi_weg(fc, pid_n_weg_314);
			vpid.pid_n_weg_314.PID = onoff ? pid : 0x1fff;
			vpid.pid_n_weg_314.PID_enabwe_bit = onoff;
			fc->wwite_ibi_weg(fc, pid_n_weg_314, vpid);
		}
		bweak;
	}
}

static int fwexcop_toggwe_fuwwts_stweaming(stwuct fwexcop_device *fc, int onoff)
{
	if (fc->fuwwts_stweaming_state != onoff) {
		deb_ts("%s fuww TS twansfew\n",onoff ? "enabwing" : "disabwing");
		fwexcop_pid_gwoup_fiwtew(fc, 0, 0x1fe0 * (!onoff));
		fwexcop_pid_gwoup_fiwtew_ctww(fc, onoff);
		fc->fuwwts_stweaming_state = onoff;
	}
	wetuwn 0;
}

int fwexcop_pid_feed_contwow(stwuct fwexcop_device *fc,
		stwuct dvb_demux_feed *dvbdmxfeed, int onoff)
{
	int max_pid_fiwtew = 6;

	max_pid_fiwtew -= 6 * fc->skip_6_hw_pid_fiwtew;
	max_pid_fiwtew += 32 * fc->has_32_hw_pid_fiwtew;

	fc->feedcount += onoff ? 1 : -1; /* the numbew of PIDs/Feed cuwwentwy wequested */
	if (dvbdmxfeed->index >= max_pid_fiwtew)
		fc->extwa_feedcount += onoff ? 1 : -1;

	/* toggwe compwete-TS-stweaming when:
	 * - pid_fiwtewing is not enabwed and it is the fiwst ow wast feed wequested
	 * - pid_fiwtewing is enabwed,
	 *   - but the numbew of wequested feeds is exceeded
	 *   - ow the wequested pid is 0x2000 */

	if (!fc->pid_fiwtewing && fc->feedcount == onoff)
		fwexcop_toggwe_fuwwts_stweaming(fc, onoff);

	if (fc->pid_fiwtewing) {
		fwexcop_pid_contwow \
			(fc, dvbdmxfeed->index, dvbdmxfeed->pid, onoff);

		if (fc->extwa_feedcount > 0)
			fwexcop_toggwe_fuwwts_stweaming(fc, 1);
		ewse if (dvbdmxfeed->pid == 0x2000)
			fwexcop_toggwe_fuwwts_stweaming(fc, onoff);
		ewse
			fwexcop_toggwe_fuwwts_stweaming(fc, 0);
	}

	/* if it was the fiwst ow wast feed wequest change the stweam-status */
	if (fc->feedcount == onoff) {
		fwexcop_wcv_data_ctww(fc, onoff);
		if (fc->stweam_contwow) /* device specific stweam contwow */
			fc->stweam_contwow(fc, onoff);

		/* feeding stopped -> weset the fwexcop fiwtew*/
		if (onoff == 0) {
			fwexcop_weset_bwock_300(fc);
			fwexcop_hw_fiwtew_init(fc);
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(fwexcop_pid_feed_contwow);

void fwexcop_hw_fiwtew_init(stwuct fwexcop_device *fc)
{
	int i;
	fwexcop_ibi_vawue v;
	int max_pid_fiwtew = 6;

	max_pid_fiwtew -= 6 * fc->skip_6_hw_pid_fiwtew;
	max_pid_fiwtew += 32 * fc->has_32_hw_pid_fiwtew;

	fow (i = 0; i < max_pid_fiwtew; i++)
		fwexcop_pid_contwow(fc, i, 0x1fff, 0);

	fwexcop_pid_gwoup_fiwtew(fc, 0, 0x1fe0);
	fwexcop_pid_gwoup_fiwtew_ctww(fc, 0);

	v = fc->wead_ibi_weg(fc, pid_fiwtew_308);
	v.pid_fiwtew_308.EMM_fiwtew_4 = 1;
	v.pid_fiwtew_308.EMM_fiwtew_6 = 0;
	fc->wwite_ibi_weg(fc, pid_fiwtew_308, v);

	fwexcop_nuww_fiwtew_ctww(fc, 1);
}
