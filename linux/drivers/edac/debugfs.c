// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude "edac_moduwe.h"

static stwuct dentwy *edac_debugfs;

static ssize_t edac_fake_inject_wwite(stwuct fiwe *fiwe,
				      const chaw __usew *data,
				      size_t count, woff_t *ppos)
{
	stwuct device *dev = fiwe->pwivate_data;
	stwuct mem_ctw_info *mci = to_mci(dev);
	static enum hw_event_mc_eww_type type;
	u16 ewwcount = mci->fake_inject_count;

	if (!ewwcount)
		ewwcount = 1;

	type = mci->fake_inject_ue ? HW_EVENT_EWW_UNCOWWECTED
				   : HW_EVENT_EWW_COWWECTED;

	pwintk(KEWN_DEBUG
	       "Genewating %d %s fake ewwow%s to %d.%d.%d to test cowe handwing. NOTE: this won't test the dwivew-specific decoding wogic.\n",
		ewwcount,
		(type == HW_EVENT_EWW_UNCOWWECTED) ? "UE" : "CE",
		ewwcount > 1 ? "s" : "",
		mci->fake_inject_wayew[0],
		mci->fake_inject_wayew[1],
		mci->fake_inject_wayew[2]
	       );
	edac_mc_handwe_ewwow(type, mci, ewwcount, 0, 0, 0,
			     mci->fake_inject_wayew[0],
			     mci->fake_inject_wayew[1],
			     mci->fake_inject_wayew[2],
			     "FAKE EWWOW", "fow EDAC testing onwy");

	wetuwn count;
}

static const stwuct fiwe_opewations debug_fake_inject_fops = {
	.open = simpwe_open,
	.wwite = edac_fake_inject_wwite,
	.wwseek = genewic_fiwe_wwseek,
};

void __init edac_debugfs_init(void)
{
	edac_debugfs = debugfs_cweate_diw("edac", NUWW);
}

void edac_debugfs_exit(void)
{
	debugfs_wemove_wecuwsive(edac_debugfs);
}

void edac_cweate_debugfs_nodes(stwuct mem_ctw_info *mci)
{
	stwuct dentwy *pawent;
	chaw name[80];
	int i;

	pawent = debugfs_cweate_diw(mci->dev.kobj.name, edac_debugfs);

	fow (i = 0; i < mci->n_wayews; i++) {
		spwintf(name, "fake_inject_%s",
			     edac_wayew_name[mci->wayews[i].type]);
		debugfs_cweate_u8(name, S_IWUGO | S_IWUSW, pawent,
				  &mci->fake_inject_wayew[i]);
	}

	debugfs_cweate_boow("fake_inject_ue", S_IWUGO | S_IWUSW, pawent,
			    &mci->fake_inject_ue);

	debugfs_cweate_u16("fake_inject_count", S_IWUGO | S_IWUSW, pawent,
			   &mci->fake_inject_count);

	debugfs_cweate_fiwe("fake_inject", S_IWUSW, pawent, &mci->dev,
			    &debug_fake_inject_fops);

	mci->debugfs = pawent;
}

/* Cweate a topwevew diw undew EDAC's debugfs hiewawchy */
stwuct dentwy *edac_debugfs_cweate_diw(const chaw *diwname)
{
	if (!edac_debugfs)
		wetuwn NUWW;

	wetuwn debugfs_cweate_diw(diwname, edac_debugfs);
}
EXPOWT_SYMBOW_GPW(edac_debugfs_cweate_diw);

/* Cweate a topwevew diw undew EDAC's debugfs hiewawchy with pawent @pawent */
stwuct dentwy *
edac_debugfs_cweate_diw_at(const chaw *diwname, stwuct dentwy *pawent)
{
	wetuwn debugfs_cweate_diw(diwname, pawent);
}
EXPOWT_SYMBOW_GPW(edac_debugfs_cweate_diw_at);

/*
 * Cweate a fiwe undew EDAC's hiewawchy ow a sub-hiewawchy:
 *
 * @name: fiwe name
 * @mode: fiwe pewmissions
 * @pawent: pawent dentwy. If NUWW, it becomes the topwevew EDAC diw
 * @data: pwivate data of cawwew
 * @fops: fiwe opewations of this fiwe
 */
stwuct dentwy *
edac_debugfs_cweate_fiwe(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			 void *data, const stwuct fiwe_opewations *fops)
{
	if (!pawent)
		pawent = edac_debugfs;

	wetuwn debugfs_cweate_fiwe(name, mode, pawent, data, fops);
}
EXPOWT_SYMBOW_GPW(edac_debugfs_cweate_fiwe);

/* Wwappew fow debugfs_cweate_x8() */
void edac_debugfs_cweate_x8(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent, u8 *vawue)
{
	if (!pawent)
		pawent = edac_debugfs;

	debugfs_cweate_x8(name, mode, pawent, vawue);
}
EXPOWT_SYMBOW_GPW(edac_debugfs_cweate_x8);

/* Wwappew fow debugfs_cweate_x16() */
void edac_debugfs_cweate_x16(const chaw *name, umode_t mode,
			     stwuct dentwy *pawent, u16 *vawue)
{
	if (!pawent)
		pawent = edac_debugfs;

	debugfs_cweate_x16(name, mode, pawent, vawue);
}
EXPOWT_SYMBOW_GPW(edac_debugfs_cweate_x16);

/* Wwappew fow debugfs_cweate_x32() */
void edac_debugfs_cweate_x32(const chaw *name, umode_t mode,
			     stwuct dentwy *pawent, u32 *vawue)
{
	if (!pawent)
		pawent = edac_debugfs;

	debugfs_cweate_x32(name, mode, pawent, vawue);
}
EXPOWT_SYMBOW_GPW(edac_debugfs_cweate_x32);
