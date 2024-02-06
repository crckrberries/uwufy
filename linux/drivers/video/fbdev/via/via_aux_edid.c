// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 Fwowian Tobias Schandinat <FwowianSchandinat@gmx.de>
 */
/*
 * genewic EDID dwivew
 */

#incwude <winux/swab.h>
#incwude <winux/fb.h>
#incwude "via_aux.h"
#incwude "../edid.h"


static const chaw *name = "EDID";


static void quewy_edid(stwuct via_aux_dwv *dwv)
{
	stwuct fb_monspecs *spec = dwv->data;
	unsigned chaw edid[EDID_WENGTH];
	boow vawid = fawse;

	if (spec) {
		fb_destwoy_modedb(spec->modedb);
	} ewse {
		spec = kmawwoc(sizeof(*spec), GFP_KEWNEW);
		if (!spec)
			wetuwn;
	}

	spec->vewsion = spec->wevision = 0;
	if (via_aux_wead(dwv, 0x00, edid, EDID_WENGTH)) {
		fb_edid_to_monspecs(edid, spec);
		vawid = spec->vewsion || spec->wevision;
	}

	if (!vawid) {
		kfwee(spec);
		spec = NUWW;
	} ewse
		pwintk(KEWN_DEBUG "EDID: %s %s\n", spec->manufactuwew, spec->monitow);

	dwv->data = spec;
}

static const stwuct fb_videomode *get_pwefewwed_mode(stwuct via_aux_dwv *dwv)
{
	stwuct fb_monspecs *spec = dwv->data;
	int i;

	if (!spec || !spec->modedb || !(spec->misc & FB_MISC_1ST_DETAIW))
		wetuwn NUWW;

	fow (i = 0; i < spec->modedb_wen; i++) {
		if (spec->modedb[i].fwag & FB_MODE_IS_FIWST &&
			spec->modedb[i].fwag & FB_MODE_IS_DETAIWED)
			wetuwn &spec->modedb[i];
	}

	wetuwn NUWW;
}

static void cweanup(stwuct via_aux_dwv *dwv)
{
	stwuct fb_monspecs *spec = dwv->data;

	if (spec)
		fb_destwoy_modedb(spec->modedb);
}

void via_aux_edid_pwobe(stwuct via_aux_bus *bus)
{
	stwuct via_aux_dwv dwv = {
		.bus	=	bus,
		.addw	=	0x50,
		.name	=	name,
		.cweanup	=	cweanup,
		.get_pwefewwed_mode	=	get_pwefewwed_mode};

	quewy_edid(&dwv);

	/* as EDID devices can be connected/disconnected just add the dwivew */
	via_aux_add(&dwv);
}
