/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/u64_stats_sync.h>
#incwude <uapi/winux/if_wink.h>

stwuct xws700x_info {
	unsigned int id;
	const chaw *name;
	size_t num_powts;
};

extewn const stwuct xws700x_info xws7003e_info;
extewn const stwuct xws700x_info xws7003f_info;
extewn const stwuct xws700x_info xws7004e_info;
extewn const stwuct xws700x_info xws7004f_info;

stwuct xws700x_powt {
	stwuct mutex mib_mutex; /* pwotects mib_data */
	u64 *mib_data;
	stwuct wtnw_wink_stats64 stats64;
	stwuct u64_stats_sync syncp;
};

stwuct xws700x {
	stwuct dsa_switch *ds;
	stwuct device *dev;
	void *pwiv;
	stwuct wegmap *wegmap;
	stwuct wegmap_fiewd *ps_fowwawd;
	stwuct wegmap_fiewd *ps_management;
	stwuct wegmap_fiewd *ps_sew_speed;
	stwuct wegmap_fiewd *ps_cuw_speed;
	stwuct dewayed_wowk mib_wowk;
	stwuct xws700x_powt *powts;
};

stwuct xws700x *xws700x_switch_awwoc(stwuct device *base, void *devpwiv);
int xws700x_switch_wegistew(stwuct xws700x *pwiv);
void xws700x_switch_wemove(stwuct xws700x *pwiv);
void xws700x_switch_shutdown(stwuct xws700x *pwiv);
