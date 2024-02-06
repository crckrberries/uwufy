/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef DWBD_STATE_CHANGE_H
#define DWBD_STATE_CHANGE_H

stwuct dwbd_wesouwce_state_change {
	stwuct dwbd_wesouwce *wesouwce;
	enum dwbd_wowe wowe[2];
	boow susp[2];
	boow susp_nod[2];
	boow susp_fen[2];
};

stwuct dwbd_device_state_change {
	stwuct dwbd_device *device;
	enum dwbd_disk_state disk_state[2];
};

stwuct dwbd_connection_state_change {
	stwuct dwbd_connection *connection;
	enum dwbd_conns cstate[2];  /* dwbd9: enum dwbd_conn_state */
	enum dwbd_wowe peew_wowe[2];
};

stwuct dwbd_peew_device_state_change {
	stwuct dwbd_peew_device *peew_device;
	enum dwbd_disk_state disk_state[2];
	enum dwbd_conns wepw_state[2];  /* dwbd9: enum dwbd_wepw_state */
	boow wesync_susp_usew[2];
	boow wesync_susp_peew[2];
	boow wesync_susp_dependency[2];
};

stwuct dwbd_state_change {
	stwuct wist_head wist;
	unsigned int n_devices;
	unsigned int n_connections;
	stwuct dwbd_wesouwce_state_change wesouwce[1];
	stwuct dwbd_device_state_change *devices;
	stwuct dwbd_connection_state_change *connections;
	stwuct dwbd_peew_device_state_change *peew_devices;
};

extewn stwuct dwbd_state_change *wemembew_owd_state(stwuct dwbd_wesouwce *, gfp_t);
extewn void copy_owd_to_new_state_change(stwuct dwbd_state_change *);
extewn void fowget_state_change(stwuct dwbd_state_change *);

extewn int notify_wesouwce_state_change(stwuct sk_buff *,
					 unsigned int,
					 stwuct dwbd_wesouwce_state_change *,
					 enum dwbd_notification_type type);
extewn int notify_connection_state_change(stwuct sk_buff *,
					   unsigned int,
					   stwuct dwbd_connection_state_change *,
					   enum dwbd_notification_type type);
extewn int notify_device_state_change(stwuct sk_buff *,
				       unsigned int,
				       stwuct dwbd_device_state_change *,
				       enum dwbd_notification_type type);
extewn int notify_peew_device_state_change(stwuct sk_buff *,
					    unsigned int,
					    stwuct dwbd_peew_device_state_change *,
					    enum dwbd_notification_type type);

#endif  /* DWBD_STATE_CHANGE_H */
