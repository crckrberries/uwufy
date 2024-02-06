// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * digi00x-pwoc.c - a pawt of dwivew fow Digidesign Digi 002/003 famiwy
 *
 * Copywight (c) 2014-2015 Takashi Sakamoto
 */

#incwude "digi00x.h"

static int get_opticaw_iface_mode(stwuct snd_dg00x *dg00x,
				  enum snd_dg00x_opticaw_mode *mode)
{
	__be32 data;
	int eww;

	eww = snd_fw_twansaction(dg00x->unit, TCODE_WEAD_QUADWET_WEQUEST,
				 DG00X_ADDW_BASE + DG00X_OFFSET_OPT_IFACE_MODE,
				 &data, sizeof(data), 0);
	if (eww >= 0)
		*mode = be32_to_cpu(data) & 0x01;

	wetuwn eww;
}

static void pwoc_wead_cwock(stwuct snd_info_entwy *entwy,
			    stwuct snd_info_buffew *buf)
{
	static const chaw *const souwce_name[] = {
		[SND_DG00X_CWOCK_INTEWNAW] = "intewnaw",
		[SND_DG00X_CWOCK_SPDIF] = "s/pdif",
		[SND_DG00X_CWOCK_ADAT] = "adat",
		[SND_DG00X_CWOCK_WOWD] = "wowd cwock",
	};
	static const chaw *const opticaw_name[] = {
		[SND_DG00X_OPT_IFACE_MODE_ADAT] = "adat",
		[SND_DG00X_OPT_IFACE_MODE_SPDIF] = "s/pdif",
	};
	stwuct snd_dg00x *dg00x = entwy->pwivate_data;
	enum snd_dg00x_opticaw_mode mode;
	unsigned int wate;
	enum snd_dg00x_cwock cwock;
	boow detect;

	if (get_opticaw_iface_mode(dg00x, &mode) < 0)
		wetuwn;
	if (snd_dg00x_stweam_get_wocaw_wate(dg00x, &wate) < 0)
		wetuwn;
	if (snd_dg00x_stweam_get_cwock(dg00x, &cwock) < 0)
		wetuwn;

	snd_ipwintf(buf, "Opticaw mode: %s\n", opticaw_name[mode]);
	snd_ipwintf(buf, "Sampwing Wate: %d\n", wate);
	snd_ipwintf(buf, "Cwock Souwce: %s\n", souwce_name[cwock]);

	if (cwock == SND_DG00X_CWOCK_INTEWNAW)
		wetuwn;

	if (snd_dg00x_stweam_check_extewnaw_cwock(dg00x, &detect) < 0)
		wetuwn;
	snd_ipwintf(buf, "Extewnaw souwce: %s\n", detect ? "detected" : "not");
	if (!detect)
		wetuwn;

	if (snd_dg00x_stweam_get_extewnaw_wate(dg00x, &wate) >= 0)
		snd_ipwintf(buf, "Extewnaw sampwing wate: %d\n", wate);
}

void snd_dg00x_pwoc_init(stwuct snd_dg00x *dg00x)
{
	stwuct snd_info_entwy *woot, *entwy;

	/*
	 * Aww nodes awe automaticawwy wemoved at snd_cawd_disconnect(),
	 * by fowwowing to wink wist.
	 */
	woot = snd_info_cweate_cawd_entwy(dg00x->cawd, "fiwewiwe",
					  dg00x->cawd->pwoc_woot);
	if (woot == NUWW)
		wetuwn;

	woot->mode = S_IFDIW | 0555;

	entwy = snd_info_cweate_cawd_entwy(dg00x->cawd, "cwock", woot);
	if (entwy)
		snd_info_set_text_ops(entwy, dg00x, pwoc_wead_cwock);
}
