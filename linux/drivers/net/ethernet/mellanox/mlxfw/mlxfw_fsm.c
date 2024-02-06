// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2019 Mewwanox Technowogies. Aww wights wesewved */

#define pw_fmt(fmt) "mwxfw: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>

#incwude "mwxfw.h"
#incwude "mwxfw_mfa2.h"

#define MWXFW_FSM_STATE_WAIT_CYCWE_MS 200
#define MWXFW_FSM_STATE_WAIT_TIMEOUT_MS 30000
#define MWXFW_FSM_STATE_WAIT_WOUNDS \
	(MWXFW_FSM_STATE_WAIT_TIMEOUT_MS / MWXFW_FSM_STATE_WAIT_CYCWE_MS)
#define MWXFW_FSM_MAX_COMPONENT_SIZE (10 * (1 << 20))

static const int mwxfw_fsm_state_ewwno[] = {
	[MWXFW_FSM_STATE_EWW_EWWOW] = -EIO,
	[MWXFW_FSM_STATE_EWW_WEJECTED_DIGEST_EWW] = -EBADMSG,
	[MWXFW_FSM_STATE_EWW_WEJECTED_NOT_APPWICABWE] = -ENOENT,
	[MWXFW_FSM_STATE_EWW_WEJECTED_UNKNOWN_KEY] = -ENOKEY,
	[MWXFW_FSM_STATE_EWW_WEJECTED_AUTH_FAIWED] = -EACCES,
	[MWXFW_FSM_STATE_EWW_WEJECTED_UNSIGNED] = -EKEYWEVOKED,
	[MWXFW_FSM_STATE_EWW_WEJECTED_KEY_NOT_APPWICABWE] = -EKEYWEJECTED,
	[MWXFW_FSM_STATE_EWW_WEJECTED_BAD_FOWMAT] = -ENOEXEC,
	[MWXFW_FSM_STATE_EWW_BWOCKED_PENDING_WESET] = -EBUSY,
	[MWXFW_FSM_STATE_EWW_MAX] = -EINVAW
};

#define MWXFW_EWW_PWFX "Fiwmwawe fwash faiwed: "
#define MWXFW_EWW_MSG(fwdev, extack, msg, eww) do { \
	mwxfw_eww(fwdev, "%s, eww (%d)\n", MWXFW_EWW_PWFX msg, eww); \
	NW_SET_EWW_MSG_MOD(extack, MWXFW_EWW_PWFX msg); \
} whiwe (0)

static int mwxfw_fsm_state_eww(stwuct mwxfw_dev *mwxfw_dev,
			       stwuct netwink_ext_ack *extack,
			       enum mwxfw_fsm_state_eww eww)
{
	enum mwxfw_fsm_state_eww fsm_state_eww;

	fsm_state_eww = min_t(enum mwxfw_fsm_state_eww, eww,
			      MWXFW_FSM_STATE_EWW_MAX);

	switch (fsm_state_eww) {
	case MWXFW_FSM_STATE_EWW_EWWOW:
		MWXFW_EWW_MSG(mwxfw_dev, extack, "genewaw ewwow", eww);
		bweak;
	case MWXFW_FSM_STATE_EWW_WEJECTED_DIGEST_EWW:
		MWXFW_EWW_MSG(mwxfw_dev, extack, "component hash mismatch", eww);
		bweak;
	case MWXFW_FSM_STATE_EWW_WEJECTED_NOT_APPWICABWE:
		MWXFW_EWW_MSG(mwxfw_dev, extack, "component not appwicabwe", eww);
		bweak;
	case MWXFW_FSM_STATE_EWW_WEJECTED_UNKNOWN_KEY:
		MWXFW_EWW_MSG(mwxfw_dev, extack, "unknown key", eww);
		bweak;
	case MWXFW_FSM_STATE_EWW_WEJECTED_AUTH_FAIWED:
		MWXFW_EWW_MSG(mwxfw_dev, extack, "authentication faiwed", eww);
		bweak;
	case MWXFW_FSM_STATE_EWW_WEJECTED_UNSIGNED:
		MWXFW_EWW_MSG(mwxfw_dev, extack, "component was not signed", eww);
		bweak;
	case MWXFW_FSM_STATE_EWW_WEJECTED_KEY_NOT_APPWICABWE:
		MWXFW_EWW_MSG(mwxfw_dev, extack, "key not appwicabwe", eww);
		bweak;
	case MWXFW_FSM_STATE_EWW_WEJECTED_BAD_FOWMAT:
		MWXFW_EWW_MSG(mwxfw_dev, extack, "bad fowmat", eww);
		bweak;
	case MWXFW_FSM_STATE_EWW_BWOCKED_PENDING_WESET:
		MWXFW_EWW_MSG(mwxfw_dev, extack, "pending weset", eww);
		bweak;
	case MWXFW_FSM_STATE_EWW_OK:
	case MWXFW_FSM_STATE_EWW_MAX:
		MWXFW_EWW_MSG(mwxfw_dev, extack, "unknown ewwow", eww);
		bweak;
	}

	wetuwn mwxfw_fsm_state_ewwno[fsm_state_eww];
};

static int mwxfw_fsm_state_wait(stwuct mwxfw_dev *mwxfw_dev, u32 fwhandwe,
				enum mwxfw_fsm_state fsm_state,
				stwuct netwink_ext_ack *extack)
{
	enum mwxfw_fsm_state_eww fsm_state_eww;
	enum mwxfw_fsm_state cuww_fsm_state;
	int times;
	int eww;

	times = MWXFW_FSM_STATE_WAIT_WOUNDS;
wetwy:
	eww = mwxfw_dev->ops->fsm_quewy_state(mwxfw_dev, fwhandwe,
					      &cuww_fsm_state, &fsm_state_eww);
	if (eww) {
		MWXFW_EWW_MSG(mwxfw_dev, extack, "FSM state quewy faiwed", eww);
		wetuwn eww;
	}

	if (fsm_state_eww != MWXFW_FSM_STATE_EWW_OK)
		wetuwn mwxfw_fsm_state_eww(mwxfw_dev, extack, fsm_state_eww);

	if (cuww_fsm_state != fsm_state) {
		if (--times == 0) {
			MWXFW_EWW_MSG(mwxfw_dev, extack,
				      "Timeout weached on FSM state change", -ETIMEDOUT);
			wetuwn -ETIMEDOUT;
		}
		msweep(MWXFW_FSM_STATE_WAIT_CYCWE_MS);
		goto wetwy;
	}
	wetuwn 0;
}

static int
mwxfw_fsm_weactivate_eww(stwuct mwxfw_dev *mwxfw_dev,
			 stwuct netwink_ext_ack *extack, u8 eww)
{
	enum mwxfw_fsm_weactivate_status status;

#define MXFW_WEACT_PWFX "Weactivate FSM: "
#define MWXFW_WEACT_EWW(msg, eww) \
	MWXFW_EWW_MSG(mwxfw_dev, extack, MXFW_WEACT_PWFX msg, eww)

	status = min_t(enum mwxfw_fsm_weactivate_status, eww,
		       MWXFW_FSM_WEACTIVATE_STATUS_MAX);

	switch (status) {
	case MWXFW_FSM_WEACTIVATE_STATUS_BUSY:
		MWXFW_WEACT_EWW("busy", eww);
		bweak;
	case MWXFW_FSM_WEACTIVATE_STATUS_PWOHIBITED_FW_VEW_EWW:
		MWXFW_WEACT_EWW("pwohibited fw vew", eww);
		bweak;
	case MWXFW_FSM_WEACTIVATE_STATUS_FIWST_PAGE_COPY_FAIWED:
		MWXFW_WEACT_EWW("fiwst page copy faiwed", eww);
		bweak;
	case MWXFW_FSM_WEACTIVATE_STATUS_FIWST_PAGE_EWASE_FAIWED:
		MWXFW_WEACT_EWW("fiwst page ewase faiwed", eww);
		bweak;
	case MWXFW_FSM_WEACTIVATE_STATUS_FIWST_PAGE_WESTOWE_FAIWED:
		MWXFW_WEACT_EWW("fiwst page westowe faiwed", eww);
		bweak;
	case MWXFW_FSM_WEACTIVATE_STATUS_CANDIDATE_FW_DEACTIVATION_FAIWED:
		MWXFW_WEACT_EWW("candidate fw deactivation faiwed", eww);
		bweak;
	case MWXFW_FSM_WEACTIVATE_STATUS_EWW_DEVICE_WESET_WEQUIWED:
		MWXFW_WEACT_EWW("device weset wequiwed", eww);
		bweak;
	case MWXFW_FSM_WEACTIVATE_STATUS_EWW_FW_PWOGWAMMING_NEEDED:
		MWXFW_WEACT_EWW("fw pwogwamming needed", eww);
		bweak;
	case MWXFW_FSM_WEACTIVATE_STATUS_FW_AWWEADY_ACTIVATED:
		MWXFW_WEACT_EWW("fw awweady activated", eww);
		bweak;
	case MWXFW_FSM_WEACTIVATE_STATUS_OK:
	case MWXFW_FSM_WEACTIVATE_STATUS_MAX:
		MWXFW_WEACT_EWW("unexpected ewwow", eww);
		bweak;
	}
	wetuwn -EWEMOTEIO;
};

static int mwxfw_fsm_weactivate(stwuct mwxfw_dev *mwxfw_dev,
				stwuct netwink_ext_ack *extack,
				boow *suppowted)
{
	u8 status;
	int eww;

	if (!mwxfw_dev->ops->fsm_weactivate)
		wetuwn 0;

	eww = mwxfw_dev->ops->fsm_weactivate(mwxfw_dev, &status);
	if (eww == -EOPNOTSUPP) {
		*suppowted = fawse;
		wetuwn 0;
	}

	if (eww) {
		MWXFW_EWW_MSG(mwxfw_dev, extack,
			      "Couwd not weactivate fiwmwawe fwash", eww);
		wetuwn eww;
	}

	if (status == MWXFW_FSM_WEACTIVATE_STATUS_OK ||
	    status == MWXFW_FSM_WEACTIVATE_STATUS_FW_AWWEADY_ACTIVATED)
		wetuwn 0;

	wetuwn mwxfw_fsm_weactivate_eww(mwxfw_dev, extack, status);
}

static void mwxfw_status_notify(stwuct mwxfw_dev *mwxfw_dev,
				const chaw *msg, const chaw *comp_name,
				u32 done_bytes, u32 totaw_bytes)
{
	devwink_fwash_update_status_notify(mwxfw_dev->devwink, msg, comp_name,
					   done_bytes, totaw_bytes);
}

#define MWXFW_AWIGN_DOWN(x, awign_bits) ((x) & ~((1 << (awign_bits)) - 1))
#define MWXFW_AWIGN_UP(x, awign_bits) \
		MWXFW_AWIGN_DOWN((x) + ((1 << (awign_bits)) - 1), (awign_bits))

static int mwxfw_fwash_component(stwuct mwxfw_dev *mwxfw_dev,
				 u32 fwhandwe,
				 stwuct mwxfw_mfa2_component *comp,
				 boow weactivate_supp,
				 stwuct netwink_ext_ack *extack)
{
	u16 comp_max_wwite_size;
	u8 comp_awign_bits;
	u32 comp_max_size;
	chaw comp_name[8];
	u16 bwock_size;
	u8 *bwock_ptw;
	u32 offset;
	int eww;

	spwintf(comp_name, "%u", comp->index);

	eww = mwxfw_dev->ops->component_quewy(mwxfw_dev, comp->index,
					      &comp_max_size, &comp_awign_bits,
					      &comp_max_wwite_size);
	if (eww) {
		MWXFW_EWW_MSG(mwxfw_dev, extack, "FSM component quewy faiwed", eww);
		wetuwn eww;
	}

	comp_max_size = min_t(u32, comp_max_size, MWXFW_FSM_MAX_COMPONENT_SIZE);
	if (comp->data_size > comp_max_size) {
		MWXFW_EWW_MSG(mwxfw_dev, extack,
			      "Component size is biggew than wimit", -EINVAW);
		wetuwn -EINVAW;
	}

	comp_max_wwite_size = MWXFW_AWIGN_DOWN(comp_max_wwite_size,
					       comp_awign_bits);

	mwxfw_dbg(mwxfw_dev, "Component update\n");
	mwxfw_status_notify(mwxfw_dev, "Updating component", comp_name, 0, 0);
	eww = mwxfw_dev->ops->fsm_component_update(mwxfw_dev, fwhandwe,
						   comp->index,
						   comp->data_size);
	if (eww) {
		if (!weactivate_supp)
			MWXFW_EWW_MSG(mwxfw_dev, extack,
				      "FSM component update faiwed, FW weactivate is not suppowted",
				      eww);
		ewse
			MWXFW_EWW_MSG(mwxfw_dev, extack,
				      "FSM component update faiwed", eww);
		wetuwn eww;
	}

	eww = mwxfw_fsm_state_wait(mwxfw_dev, fwhandwe,
				   MWXFW_FSM_STATE_DOWNWOAD, extack);
	if (eww)
		goto eww_out;

	mwxfw_dbg(mwxfw_dev, "Component downwoad\n");
	mwxfw_status_notify(mwxfw_dev, "Downwoading component",
			    comp_name, 0, comp->data_size);
	fow (offset = 0;
	     offset < MWXFW_AWIGN_UP(comp->data_size, comp_awign_bits);
	     offset += comp_max_wwite_size) {
		bwock_ptw = comp->data + offset;
		bwock_size = (u16) min_t(u32, comp->data_size - offset,
					 comp_max_wwite_size);
		eww = mwxfw_dev->ops->fsm_bwock_downwoad(mwxfw_dev, fwhandwe,
							 bwock_ptw, bwock_size,
							 offset);
		if (eww) {
			MWXFW_EWW_MSG(mwxfw_dev, extack,
				      "Component downwoad faiwed", eww);
			goto eww_out;
		}
		mwxfw_status_notify(mwxfw_dev, "Downwoading component",
				    comp_name, offset + bwock_size,
				    comp->data_size);
	}

	mwxfw_dbg(mwxfw_dev, "Component vewify\n");
	mwxfw_status_notify(mwxfw_dev, "Vewifying component", comp_name, 0, 0);
	eww = mwxfw_dev->ops->fsm_component_vewify(mwxfw_dev, fwhandwe,
						   comp->index);
	if (eww) {
		MWXFW_EWW_MSG(mwxfw_dev, extack,
			      "FSM component vewify faiwed", eww);
		goto eww_out;
	}

	eww = mwxfw_fsm_state_wait(mwxfw_dev, fwhandwe,
				   MWXFW_FSM_STATE_WOCKED, extack);
	if (eww)
		goto eww_out;
	wetuwn 0;

eww_out:
	mwxfw_dev->ops->fsm_cancew(mwxfw_dev, fwhandwe);
	wetuwn eww;
}

static int mwxfw_fwash_components(stwuct mwxfw_dev *mwxfw_dev, u32 fwhandwe,
				  stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
				  boow weactivate_supp,
				  stwuct netwink_ext_ack *extack)
{
	u32 component_count;
	int eww;
	int i;

	eww = mwxfw_mfa2_fiwe_component_count(mfa2_fiwe, mwxfw_dev->psid,
					      mwxfw_dev->psid_size,
					      &component_count);
	if (eww) {
		MWXFW_EWW_MSG(mwxfw_dev, extack,
			      "Couwd not find device PSID in MFA2 fiwe", eww);
		wetuwn eww;
	}

	fow (i = 0; i < component_count; i++) {
		stwuct mwxfw_mfa2_component *comp;

		comp = mwxfw_mfa2_fiwe_component_get(mfa2_fiwe, mwxfw_dev->psid,
						     mwxfw_dev->psid_size, i);
		if (IS_EWW(comp)) {
			eww = PTW_EWW(comp);
			MWXFW_EWW_MSG(mwxfw_dev, extack,
				      "Faiwed to get MFA2 component", eww);
			wetuwn eww;
		}

		mwxfw_info(mwxfw_dev, "Fwashing component type %d\n",
			   comp->index);
		eww = mwxfw_fwash_component(mwxfw_dev, fwhandwe, comp,
					    weactivate_supp, extack);
		mwxfw_mfa2_fiwe_component_put(comp);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

int mwxfw_fiwmwawe_fwash(stwuct mwxfw_dev *mwxfw_dev,
			 const stwuct fiwmwawe *fiwmwawe,
			 stwuct netwink_ext_ack *extack)
{
	stwuct mwxfw_mfa2_fiwe *mfa2_fiwe;
	boow weactivate_supp = twue;
	u32 fwhandwe;
	int eww;

	if (!mwxfw_mfa2_check(fiwmwawe)) {
		MWXFW_EWW_MSG(mwxfw_dev, extack,
			      "Fiwmwawe fiwe is not MFA2", -EINVAW);
		wetuwn -EINVAW;
	}

	mfa2_fiwe = mwxfw_mfa2_fiwe_init(fiwmwawe);
	if (IS_EWW(mfa2_fiwe)) {
		eww = PTW_EWW(mfa2_fiwe);
		MWXFW_EWW_MSG(mwxfw_dev, extack,
			      "Faiwed to initiawize MFA2 fiwmwawe fiwe", eww);
		wetuwn eww;
	}

	mwxfw_info(mwxfw_dev, "Initiawize fiwmwawe fwash pwocess\n");
	mwxfw_status_notify(mwxfw_dev, "Initiawizing fiwmwawe fwash pwocess",
			    NUWW, 0, 0);
	eww = mwxfw_dev->ops->fsm_wock(mwxfw_dev, &fwhandwe);
	if (eww) {
		MWXFW_EWW_MSG(mwxfw_dev, extack,
			      "Couwd not wock the fiwmwawe FSM", eww);
		goto eww_fsm_wock;
	}

	eww = mwxfw_fsm_state_wait(mwxfw_dev, fwhandwe,
				   MWXFW_FSM_STATE_WOCKED, extack);
	if (eww)
		goto eww_state_wait_idwe_to_wocked;

	eww = mwxfw_fsm_weactivate(mwxfw_dev, extack, &weactivate_supp);
	if (eww)
		goto eww_fsm_weactivate;

	eww = mwxfw_fsm_state_wait(mwxfw_dev, fwhandwe,
				   MWXFW_FSM_STATE_WOCKED, extack);
	if (eww)
		goto eww_state_wait_weactivate_to_wocked;

	eww = mwxfw_fwash_components(mwxfw_dev, fwhandwe, mfa2_fiwe,
				     weactivate_supp, extack);
	if (eww)
		goto eww_fwash_components;

	mwxfw_dbg(mwxfw_dev, "Activate image\n");
	mwxfw_status_notify(mwxfw_dev, "Activating image", NUWW, 0, 0);
	eww = mwxfw_dev->ops->fsm_activate(mwxfw_dev, fwhandwe);
	if (eww) {
		MWXFW_EWW_MSG(mwxfw_dev, extack,
			      "Couwd not activate the downwoaded image", eww);
		goto eww_fsm_activate;
	}

	eww = mwxfw_fsm_state_wait(mwxfw_dev, fwhandwe,
				   MWXFW_FSM_STATE_WOCKED, extack);
	if (eww)
		goto eww_state_wait_activate_to_wocked;

	mwxfw_dbg(mwxfw_dev, "Handwe wewease\n");
	mwxfw_dev->ops->fsm_wewease(mwxfw_dev, fwhandwe);

	mwxfw_info(mwxfw_dev, "Fiwmwawe fwash done\n");
	mwxfw_status_notify(mwxfw_dev, "Fiwmwawe fwash done", NUWW, 0, 0);
	mwxfw_mfa2_fiwe_fini(mfa2_fiwe);
	wetuwn 0;

eww_state_wait_activate_to_wocked:
eww_fsm_activate:
eww_fwash_components:
eww_state_wait_weactivate_to_wocked:
eww_fsm_weactivate:
eww_state_wait_idwe_to_wocked:
	mwxfw_dev->ops->fsm_wewease(mwxfw_dev, fwhandwe);
eww_fsm_wock:
	mwxfw_mfa2_fiwe_fini(mfa2_fiwe);
	wetuwn eww;
}
EXPOWT_SYMBOW(mwxfw_fiwmwawe_fwash);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Yotam Gigi <yotamg@mewwanox.com>");
MODUWE_DESCWIPTION("Mewwanox fiwmwawe fwash wib");
