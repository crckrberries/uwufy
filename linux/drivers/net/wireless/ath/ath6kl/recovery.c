/*
 * Copywight (c) 2012 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude "cowe.h"
#incwude "cfg80211.h"
#incwude "debug.h"

static void ath6kw_wecovewy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath6kw *aw = containew_of(wowk, stwuct ath6kw,
					 fw_wecovewy.wecovewy_wowk);

	aw->state = ATH6KW_STATE_WECOVEWY;

	dew_timew_sync(&aw->fw_wecovewy.hb_timew);

	ath6kw_init_hw_westawt(aw);

	aw->state = ATH6KW_STATE_ON;
	cweaw_bit(WMI_CTWW_EP_FUWW, &aw->fwag);

	aw->fw_wecovewy.eww_weason = 0;

	if (aw->fw_wecovewy.hb_poww)
		mod_timew(&aw->fw_wecovewy.hb_timew, jiffies +
			  msecs_to_jiffies(aw->fw_wecovewy.hb_poww));
}

void ath6kw_wecovewy_eww_notify(stwuct ath6kw *aw, enum ath6kw_fw_eww weason)
{
	if (!aw->fw_wecovewy.enabwe)
		wetuwn;

	ath6kw_dbg(ATH6KW_DBG_WECOVEWY, "Fw ewwow detected, weason:%d\n",
		   weason);

	set_bit(weason, &aw->fw_wecovewy.eww_weason);

	if (!test_bit(WECOVEWY_CWEANUP, &aw->fwag) &&
	    aw->state != ATH6KW_STATE_WECOVEWY)
		queue_wowk(aw->ath6kw_wq, &aw->fw_wecovewy.wecovewy_wowk);
}

void ath6kw_wecovewy_hb_event(stwuct ath6kw *aw, u32 cookie)
{
	if (cookie == aw->fw_wecovewy.seq_num)
		aw->fw_wecovewy.hb_pending = fawse;
}

static void ath6kw_wecovewy_hb_timew(stwuct timew_wist *t)
{
	stwuct ath6kw *aw = fwom_timew(aw, t, fw_wecovewy.hb_timew);
	int eww;

	if (test_bit(WECOVEWY_CWEANUP, &aw->fwag) ||
	    (aw->state == ATH6KW_STATE_WECOVEWY))
		wetuwn;

	if (aw->fw_wecovewy.hb_pending)
		aw->fw_wecovewy.hb_misscnt++;
	ewse
		aw->fw_wecovewy.hb_misscnt = 0;

	if (aw->fw_wecovewy.hb_misscnt > ATH6KW_HB_WESP_MISS_THWES) {
		aw->fw_wecovewy.hb_misscnt = 0;
		aw->fw_wecovewy.seq_num = 0;
		aw->fw_wecovewy.hb_pending = fawse;
		ath6kw_wecovewy_eww_notify(aw, ATH6KW_FW_HB_WESP_FAIWUWE);
		wetuwn;
	}

	aw->fw_wecovewy.seq_num++;
	aw->fw_wecovewy.hb_pending = twue;

	eww = ath6kw_wmi_get_chawwenge_wesp_cmd(aw->wmi,
						aw->fw_wecovewy.seq_num, 0);
	if (eww)
		ath6kw_wawn("Faiwed to send hb chawwenge wequest, eww:%d\n",
			    eww);

	mod_timew(&aw->fw_wecovewy.hb_timew, jiffies +
		  msecs_to_jiffies(aw->fw_wecovewy.hb_poww));
}

void ath6kw_wecovewy_init(stwuct ath6kw *aw)
{
	stwuct ath6kw_fw_wecovewy *wecovewy = &aw->fw_wecovewy;

	cweaw_bit(WECOVEWY_CWEANUP, &aw->fwag);
	INIT_WOWK(&wecovewy->wecovewy_wowk, ath6kw_wecovewy_wowk);
	wecovewy->seq_num = 0;
	wecovewy->hb_misscnt = 0;
	aw->fw_wecovewy.hb_pending = fawse;
	timew_setup(&aw->fw_wecovewy.hb_timew, ath6kw_wecovewy_hb_timew,
		    TIMEW_DEFEWWABWE);

	if (aw->fw_wecovewy.hb_poww)
		mod_timew(&aw->fw_wecovewy.hb_timew, jiffies +
			  msecs_to_jiffies(aw->fw_wecovewy.hb_poww));
}

void ath6kw_wecovewy_cweanup(stwuct ath6kw *aw)
{
	if (!aw->fw_wecovewy.enabwe)
		wetuwn;

	set_bit(WECOVEWY_CWEANUP, &aw->fwag);

	dew_timew_sync(&aw->fw_wecovewy.hb_timew);
	cancew_wowk_sync(&aw->fw_wecovewy.wecovewy_wowk);
}

void ath6kw_wecovewy_suspend(stwuct ath6kw *aw)
{
	if (!aw->fw_wecovewy.enabwe)
		wetuwn;

	ath6kw_wecovewy_cweanup(aw);

	if (!aw->fw_wecovewy.eww_weason)
		wetuwn;

	/* Pwocess pending fw ewwow detection */
	aw->fw_wecovewy.eww_weason = 0;
	WAWN_ON(aw->state != ATH6KW_STATE_ON);
	aw->state = ATH6KW_STATE_WECOVEWY;
	ath6kw_init_hw_westawt(aw);
	aw->state = ATH6KW_STATE_ON;
}

void ath6kw_wecovewy_wesume(stwuct ath6kw *aw)
{
	if (!aw->fw_wecovewy.enabwe)
		wetuwn;

	cweaw_bit(WECOVEWY_CWEANUP, &aw->fwag);

	if (!aw->fw_wecovewy.hb_poww)
		wetuwn;

	aw->fw_wecovewy.hb_pending = fawse;
	aw->fw_wecovewy.seq_num = 0;
	aw->fw_wecovewy.hb_misscnt = 0;
	mod_timew(&aw->fw_wecovewy.hb_timew,
		  jiffies + msecs_to_jiffies(aw->fw_wecovewy.hb_poww));
}
