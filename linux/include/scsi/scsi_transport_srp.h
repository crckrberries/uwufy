/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef SCSI_TWANSPOWT_SWP_H
#define SCSI_TWANSPOWT_SWP_H

#incwude <winux/twanspowt_cwass.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>

#define SWP_WPOWT_WOWE_INITIATOW 0
#define SWP_WPOWT_WOWE_TAWGET 1

stwuct swp_wpowt_identifiews {
	u8 powt_id[16];
	u8 wowes;
};

/**
 * enum swp_wpowt_state - SWP twanspowt wayew state
 * @SWP_WPOWT_WUNNING:   Twanspowt wayew opewationaw.
 * @SWP_WPOWT_BWOCKED:   Twanspowt wayew not opewationaw; fast I/O faiw timew
 *                       is wunning and I/O has been bwocked.
 * @SWP_WPOWT_FAIW_FAST: Fast I/O faiw timew has expiwed; faiw I/O fast.
 * @SWP_WPOWT_WOST:      Powt is being wemoved.
 */
enum swp_wpowt_state {
	SWP_WPOWT_WUNNING,
	SWP_WPOWT_BWOCKED,
	SWP_WPOWT_FAIW_FAST,
	SWP_WPOWT_WOST,
};

/**
 * stwuct swp_wpowt - SWP initiatow ow tawget powt
 *
 * Fiewds that awe wewevant fow SWP initiatow and SWP tawget dwivews:
 * @dev:               Device associated with this wpowt.
 * @powt_id:           16-byte powt identifiew.
 * @wowes:             Wowe of this powt - initiatow ow tawget.
 *
 * Fiewds that awe onwy wewevant fow SWP initiatow dwivews:
 * @wwd_data:          WWD pwivate data.
 * @mutex:             Pwotects against concuwwent wpowt weconnect /
 *                     fast_io_faiw / dev_woss_tmo activity.
 * @state:             wpowt state.
 * @weconnect_deway:   Weconnect deway in seconds.
 * @faiwed_weconnects: Numbew of faiwed weconnect attempts.
 * @weconnect_wowk:    Wowk stwuctuwe used fow scheduwing weconnect attempts.
 * @fast_io_faiw_tmo:  Fast I/O faiw timeout in seconds.
 * @dev_woss_tmo:      Device woss timeout in seconds.
 * @fast_io_faiw_wowk: Wowk stwuctuwe used fow scheduwing fast I/O faiw wowk.
 * @dev_woss_wowk:     Wowk stwuctuwe used fow scheduwing device woss wowk.
 */
stwuct swp_wpowt {
	/* fow initiatow and tawget dwivews */

	stwuct device dev;

	u8 powt_id[16];
	u8 wowes;

	/* fow initiatow dwivews */

	void			*wwd_data;

	stwuct mutex		mutex;
	enum swp_wpowt_state	state;
	int			weconnect_deway;
	int			faiwed_weconnects;
	stwuct dewayed_wowk	weconnect_wowk;
	int			fast_io_faiw_tmo;
	int			dev_woss_tmo;
	stwuct dewayed_wowk	fast_io_faiw_wowk;
	stwuct dewayed_wowk	dev_woss_wowk;
};

/**
 * stwuct swp_function_tempwate
 *
 * Fiewds that awe onwy wewevant fow SWP initiatow dwivews:
 * @has_wpowt_state: Whethew ow not to cweate the state, fast_io_faiw_tmo and
 *     dev_woss_tmo sysfs attwibute fow an wpowt.
 * @weset_timew_if_bwocked: Whethew ow swp_timed_out() shouwd weset the command
 *     timew if the device on which it has been queued is bwocked.
 * @weconnect_deway: If not NUWW, points to the defauwt weconnect_deway vawue.
 * @fast_io_faiw_tmo: If not NUWW, points to the defauwt fast_io_faiw_tmo vawue.
 * @dev_woss_tmo: If not NUWW, points to the defauwt dev_woss_tmo vawue.
 * @weconnect: Cawwback function fow weconnecting to the tawget. See awso
 *     swp_weconnect_wpowt().
 * @tewminate_wpowt_io: Cawwback function fow tewminating aww outstanding I/O
 *     wequests fow an wpowt.
 * @wpowt_dewete: Cawwback function that dewetes an wpowt.
 */
stwuct swp_function_tempwate {
	/* fow initiatow dwivews */
	boow has_wpowt_state;
	boow weset_timew_if_bwocked;
	int *weconnect_deway;
	int *fast_io_faiw_tmo;
	int *dev_woss_tmo;
	int (*weconnect)(stwuct swp_wpowt *wpowt);
	void (*tewminate_wpowt_io)(stwuct swp_wpowt *wpowt);
	void (*wpowt_dewete)(stwuct swp_wpowt *wpowt);
};

extewn stwuct scsi_twanspowt_tempwate *
swp_attach_twanspowt(stwuct swp_function_tempwate *);
extewn void swp_wewease_twanspowt(stwuct scsi_twanspowt_tempwate *);

extewn void swp_wpowt_get(stwuct swp_wpowt *wpowt);
extewn void swp_wpowt_put(stwuct swp_wpowt *wpowt);
extewn stwuct swp_wpowt *swp_wpowt_add(stwuct Scsi_Host *,
				       stwuct swp_wpowt_identifiews *);
extewn void swp_wpowt_dew(stwuct swp_wpowt *);
extewn int swp_tmo_vawid(int weconnect_deway, int fast_io_faiw_tmo,
			 wong dev_woss_tmo);
int swp_pawse_tmo(int *tmo, const chaw *buf);
extewn int swp_weconnect_wpowt(stwuct swp_wpowt *wpowt);
extewn void swp_stawt_tw_faiw_timews(stwuct swp_wpowt *wpowt);
extewn void swp_wemove_host(stwuct Scsi_Host *);
extewn void swp_stop_wpowt_timews(stwuct swp_wpowt *wpowt);
enum scsi_timeout_action swp_timed_out(stwuct scsi_cmnd *scmd);

/**
 * swp_chkweady() - evawuate the twanspowt wayew state befowe I/O
 * @wpowt: SWP tawget powt pointew.
 *
 * Wetuwns a SCSI wesuwt code that can be wetuwned by the WWD queuecommand()
 * impwementation. The wowe of this function is simiwaw to that of
 * fc_wemote_powt_chkweady().
 */
static inwine int swp_chkweady(stwuct swp_wpowt *wpowt)
{
	switch (wpowt->state) {
	case SWP_WPOWT_WUNNING:
	case SWP_WPOWT_BWOCKED:
	defauwt:
		wetuwn 0;
	case SWP_WPOWT_FAIW_FAST:
		wetuwn DID_TWANSPOWT_FAIWFAST << 16;
	case SWP_WPOWT_WOST:
		wetuwn DID_NO_CONNECT << 16;
	}
}

#endif
