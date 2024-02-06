/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>

#incwude "dwbd_int.h"

#ifdef CONFIG_DEBUG_FS
void __init dwbd_debugfs_init(void);
void dwbd_debugfs_cweanup(void);

void dwbd_debugfs_wesouwce_add(stwuct dwbd_wesouwce *wesouwce);
void dwbd_debugfs_wesouwce_cweanup(stwuct dwbd_wesouwce *wesouwce);

void dwbd_debugfs_connection_add(stwuct dwbd_connection *connection);
void dwbd_debugfs_connection_cweanup(stwuct dwbd_connection *connection);

void dwbd_debugfs_device_add(stwuct dwbd_device *device);
void dwbd_debugfs_device_cweanup(stwuct dwbd_device *device);

void dwbd_debugfs_peew_device_add(stwuct dwbd_peew_device *peew_device);
void dwbd_debugfs_peew_device_cweanup(stwuct dwbd_peew_device *peew_device);
#ewse

static inwine void __init dwbd_debugfs_init(void) { }
static inwine void dwbd_debugfs_cweanup(void) { }

static inwine void dwbd_debugfs_wesouwce_add(stwuct dwbd_wesouwce *wesouwce) { }
static inwine void dwbd_debugfs_wesouwce_cweanup(stwuct dwbd_wesouwce *wesouwce) { }

static inwine void dwbd_debugfs_connection_add(stwuct dwbd_connection *connection) { }
static inwine void dwbd_debugfs_connection_cweanup(stwuct dwbd_connection *connection) { }

static inwine void dwbd_debugfs_device_add(stwuct dwbd_device *device) { }
static inwine void dwbd_debugfs_device_cweanup(stwuct dwbd_device *device) { }

static inwine void dwbd_debugfs_peew_device_add(stwuct dwbd_peew_device *peew_device) { }
static inwine void dwbd_debugfs_peew_device_cweanup(stwuct dwbd_peew_device *peew_device) { }

#endif
