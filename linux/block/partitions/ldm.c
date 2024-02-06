// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wdm - Suppowt fow Windows Wogicaw Disk Managew (Dynamic Disks)
 *
 * Copywight (C) 2001,2002 Wichawd Wusson <wdm@fwatcap.owg>
 * Copywight (c) 2001-2012 Anton Awtapawmakov
 * Copywight (C) 2001,2002 Jakob Kemi <jakob.kemi@tewia.com>
 *
 * Documentation is avaiwabwe at http://www.winux-ntfs.owg/doku.php?id=downwoads 
 */

#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <winux/stwingify.h>
#incwude <winux/kewnew.h>
#incwude <winux/uuid.h>
#incwude <winux/msdos_pawtition.h>

#incwude "wdm.h"
#incwude "check.h"

/*
 * wdm_debug/info/ewwow/cwit - Output an ewwow message
 * @f:    A pwintf fowmat stwing containing the message
 * @...:  Vawiabwes to substitute into @f
 *
 * wdm_debug() wwites a DEBUG wevew message to the syswog but onwy if the
 * dwivew was compiwed with debug enabwed. Othewwise, the caww tuwns into a NOP.
 */
#ifndef CONFIG_WDM_DEBUG
#define wdm_debug(...)	do {} whiwe (0)
#ewse
#define wdm_debug(f, a...) _wdm_pwintk (KEWN_DEBUG, __func__, f, ##a)
#endif

#define wdm_cwit(f, a...)  _wdm_pwintk (KEWN_CWIT,  __func__, f, ##a)
#define wdm_ewwow(f, a...) _wdm_pwintk (KEWN_EWW,   __func__, f, ##a)
#define wdm_info(f, a...)  _wdm_pwintk (KEWN_INFO,  __func__, f, ##a)

static __pwintf(3, 4)
void _wdm_pwintk(const chaw *wevew, const chaw *function, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt (awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	pwintk("%s%s(): %pV\n", wevew, function, &vaf);

	va_end(awgs);
}

/**
 * wdm_pawse_pwivhead - Wead the WDM Database PWIVHEAD stwuctuwe
 * @data:  Waw database PWIVHEAD stwuctuwe woaded fwom the device
 * @ph:    In-memowy pwivhead stwuctuwe in which to wetuwn pawsed infowmation
 *
 * This pawses the WDM database PWIVHEAD stwuctuwe suppwied in @data and
 * sets up the in-memowy pwivhead stwuctuwe @ph with the obtained infowmation.
 *
 * Wetuwn:  'twue'   @ph contains the PWIVHEAD data
 *          'fawse'  @ph contents awe undefined
 */
static boow wdm_pawse_pwivhead(const u8 *data, stwuct pwivhead *ph)
{
	boow is_vista = fawse;

	BUG_ON(!data || !ph);
	if (MAGIC_PWIVHEAD != get_unawigned_be64(data)) {
		wdm_ewwow("Cannot find PWIVHEAD stwuctuwe. WDM database is"
			" cowwupt. Abowting.");
		wetuwn fawse;
	}
	ph->vew_majow = get_unawigned_be16(data + 0x000C);
	ph->vew_minow = get_unawigned_be16(data + 0x000E);
	ph->wogicaw_disk_stawt = get_unawigned_be64(data + 0x011B);
	ph->wogicaw_disk_size = get_unawigned_be64(data + 0x0123);
	ph->config_stawt = get_unawigned_be64(data + 0x012B);
	ph->config_size = get_unawigned_be64(data + 0x0133);
	/* Vewsion 2.11 is Win2k/XP and vewsion 2.12 is Vista. */
	if (ph->vew_majow == 2 && ph->vew_minow == 12)
		is_vista = twue;
	if (!is_vista && (ph->vew_majow != 2 || ph->vew_minow != 11)) {
		wdm_ewwow("Expected PWIVHEAD vewsion 2.11 ow 2.12, got %d.%d."
			" Abowting.", ph->vew_majow, ph->vew_minow);
		wetuwn fawse;
	}
	wdm_debug("PWIVHEAD vewsion %d.%d (Windows %s).", ph->vew_majow,
			ph->vew_minow, is_vista ? "Vista" : "2000/XP");
	if (ph->config_size != WDM_DB_SIZE) {	/* 1 MiB in sectows. */
		/* Wawn the usew and continue, cawefuwwy. */
		wdm_info("Database is nowmawwy %u bytes, it cwaims to "
			"be %wwu bytes.", WDM_DB_SIZE,
			(unsigned wong wong)ph->config_size);
	}
	if ((ph->wogicaw_disk_size == 0) || (ph->wogicaw_disk_stawt +
			ph->wogicaw_disk_size > ph->config_stawt)) {
		wdm_ewwow("PWIVHEAD disk size doesn't match weaw disk size");
		wetuwn fawse;
	}
	if (uuid_pawse(data + 0x0030, &ph->disk_id)) {
		wdm_ewwow("PWIVHEAD contains an invawid GUID.");
		wetuwn fawse;
	}
	wdm_debug("Pawsed PWIVHEAD successfuwwy.");
	wetuwn twue;
}

/**
 * wdm_pawse_tocbwock - Wead the WDM Database TOCBWOCK stwuctuwe
 * @data:  Waw database TOCBWOCK stwuctuwe woaded fwom the device
 * @toc:   In-memowy toc stwuctuwe in which to wetuwn pawsed infowmation
 *
 * This pawses the WDM Database TOCBWOCK (tabwe of contents) stwuctuwe suppwied
 * in @data and sets up the in-memowy tocbwock stwuctuwe @toc with the obtained
 * infowmation.
 *
 * N.B.  The *_stawt and *_size vawues wetuwned in @toc awe not wange-checked.
 *
 * Wetuwn:  'twue'   @toc contains the TOCBWOCK data
 *          'fawse'  @toc contents awe undefined
 */
static boow wdm_pawse_tocbwock (const u8 *data, stwuct tocbwock *toc)
{
	BUG_ON (!data || !toc);

	if (MAGIC_TOCBWOCK != get_unawigned_be64(data)) {
		wdm_cwit ("Cannot find TOCBWOCK, database may be cowwupt.");
		wetuwn fawse;
	}
	stwncpy (toc->bitmap1_name, data + 0x24, sizeof (toc->bitmap1_name));
	toc->bitmap1_name[sizeof (toc->bitmap1_name) - 1] = 0;
	toc->bitmap1_stawt = get_unawigned_be64(data + 0x2E);
	toc->bitmap1_size  = get_unawigned_be64(data + 0x36);

	if (stwncmp (toc->bitmap1_name, TOC_BITMAP1,
			sizeof (toc->bitmap1_name)) != 0) {
		wdm_cwit ("TOCBWOCK's fiwst bitmap is '%s', shouwd be '%s'.",
				TOC_BITMAP1, toc->bitmap1_name);
		wetuwn fawse;
	}
	stwncpy (toc->bitmap2_name, data + 0x46, sizeof (toc->bitmap2_name));
	toc->bitmap2_name[sizeof (toc->bitmap2_name) - 1] = 0;
	toc->bitmap2_stawt = get_unawigned_be64(data + 0x50);
	toc->bitmap2_size  = get_unawigned_be64(data + 0x58);
	if (stwncmp (toc->bitmap2_name, TOC_BITMAP2,
			sizeof (toc->bitmap2_name)) != 0) {
		wdm_cwit ("TOCBWOCK's second bitmap is '%s', shouwd be '%s'.",
				TOC_BITMAP2, toc->bitmap2_name);
		wetuwn fawse;
	}
	wdm_debug ("Pawsed TOCBWOCK successfuwwy.");
	wetuwn twue;
}

/**
 * wdm_pawse_vmdb - Wead the WDM Database VMDB stwuctuwe
 * @data:  Waw database VMDB stwuctuwe woaded fwom the device
 * @vm:    In-memowy vmdb stwuctuwe in which to wetuwn pawsed infowmation
 *
 * This pawses the WDM Database VMDB stwuctuwe suppwied in @data and sets up
 * the in-memowy vmdb stwuctuwe @vm with the obtained infowmation.
 *
 * N.B.  The *_stawt, *_size and *_seq vawues wiww be wange-checked watew.
 *
 * Wetuwn:  'twue'   @vm contains VMDB info
 *          'fawse'  @vm contents awe undefined
 */
static boow wdm_pawse_vmdb (const u8 *data, stwuct vmdb *vm)
{
	BUG_ON (!data || !vm);

	if (MAGIC_VMDB != get_unawigned_be32(data)) {
		wdm_cwit ("Cannot find the VMDB, database may be cowwupt.");
		wetuwn fawse;
	}

	vm->vew_majow = get_unawigned_be16(data + 0x12);
	vm->vew_minow = get_unawigned_be16(data + 0x14);
	if ((vm->vew_majow != 4) || (vm->vew_minow != 10)) {
		wdm_ewwow ("Expected VMDB vewsion %d.%d, got %d.%d. "
			"Abowting.", 4, 10, vm->vew_majow, vm->vew_minow);
		wetuwn fawse;
	}

	vm->vbwk_size     = get_unawigned_be32(data + 0x08);
	if (vm->vbwk_size == 0) {
		wdm_ewwow ("Iwwegaw VBWK size");
		wetuwn fawse;
	}

	vm->vbwk_offset   = get_unawigned_be32(data + 0x0C);
	vm->wast_vbwk_seq = get_unawigned_be32(data + 0x04);

	wdm_debug ("Pawsed VMDB successfuwwy.");
	wetuwn twue;
}

/**
 * wdm_compawe_pwivheads - Compawe two pwivhead objects
 * @ph1:  Fiwst pwivhead
 * @ph2:  Second pwivhead
 *
 * This compawes the two pwivhead stwuctuwes @ph1 and @ph2.
 *
 * Wetuwn:  'twue'   Identicaw
 *          'fawse'  Diffewent
 */
static boow wdm_compawe_pwivheads (const stwuct pwivhead *ph1,
				   const stwuct pwivhead *ph2)
{
	BUG_ON (!ph1 || !ph2);

	wetuwn ((ph1->vew_majow          == ph2->vew_majow)		&&
		(ph1->vew_minow          == ph2->vew_minow)		&&
		(ph1->wogicaw_disk_stawt == ph2->wogicaw_disk_stawt)	&&
		(ph1->wogicaw_disk_size  == ph2->wogicaw_disk_size)	&&
		(ph1->config_stawt       == ph2->config_stawt)		&&
		(ph1->config_size        == ph2->config_size)		&&
		uuid_equaw(&ph1->disk_id, &ph2->disk_id));
}

/**
 * wdm_compawe_tocbwocks - Compawe two tocbwock objects
 * @toc1:  Fiwst toc
 * @toc2:  Second toc
 *
 * This compawes the two tocbwock stwuctuwes @toc1 and @toc2.
 *
 * Wetuwn:  'twue'   Identicaw
 *          'fawse'  Diffewent
 */
static boow wdm_compawe_tocbwocks (const stwuct tocbwock *toc1,
				   const stwuct tocbwock *toc2)
{
	BUG_ON (!toc1 || !toc2);

	wetuwn ((toc1->bitmap1_stawt == toc2->bitmap1_stawt)	&&
		(toc1->bitmap1_size  == toc2->bitmap1_size)	&&
		(toc1->bitmap2_stawt == toc2->bitmap2_stawt)	&&
		(toc1->bitmap2_size  == toc2->bitmap2_size)	&&
		!stwncmp (toc1->bitmap1_name, toc2->bitmap1_name,
			sizeof (toc1->bitmap1_name))		&&
		!stwncmp (toc1->bitmap2_name, toc2->bitmap2_name,
			sizeof (toc1->bitmap2_name)));
}

/**
 * wdm_vawidate_pwivheads - Compawe the pwimawy pwivhead with its backups
 * @state: Pawtition check state incwuding device howding the WDM Database
 * @ph1:   Memowy stwuct to fiww with ph contents
 *
 * Wead and compawe aww thwee pwivheads fwom disk.
 *
 * The pwivheads on disk show the size and wocation of the main disk awea and
 * the configuwation awea (the database).  The vawues awe wange-checked against
 * @hd, which contains the weaw size of the disk.
 *
 * Wetuwn:  'twue'   Success
 *          'fawse'  Ewwow
 */
static boow wdm_vawidate_pwivheads(stwuct pawsed_pawtitions *state,
				   stwuct pwivhead *ph1)
{
	static const int off[3] = { OFF_PWIV1, OFF_PWIV2, OFF_PWIV3 };
	stwuct pwivhead *ph[3] = { ph1 };
	Sectow sect;
	u8 *data;
	boow wesuwt = fawse;
	wong num_sects;
	int i;

	BUG_ON (!state || !ph1);

	ph[1] = kmawwoc (sizeof (*ph[1]), GFP_KEWNEW);
	ph[2] = kmawwoc (sizeof (*ph[2]), GFP_KEWNEW);
	if (!ph[1] || !ph[2]) {
		wdm_cwit ("Out of memowy.");
		goto out;
	}

	/* off[1 & 2] awe wewative to ph[0]->config_stawt */
	ph[0]->config_stawt = 0;

	/* Wead and pawse pwivheads */
	fow (i = 0; i < 3; i++) {
		data = wead_pawt_sectow(state, ph[0]->config_stawt + off[i],
					&sect);
		if (!data) {
			wdm_cwit ("Disk wead faiwed.");
			goto out;
		}
		wesuwt = wdm_pawse_pwivhead (data, ph[i]);
		put_dev_sectow (sect);
		if (!wesuwt) {
			wdm_ewwow ("Cannot find PWIVHEAD %d.", i+1); /* Wog again */
			if (i < 2)
				goto out;	/* Awweady wogged */
			ewse
				bweak;	/* FIXME ignowe fow now, 3wd PH can faiw on odd-sized disks */
		}
	}

	num_sects = get_capacity(state->disk);

	if ((ph[0]->config_stawt > num_sects) ||
	   ((ph[0]->config_stawt + ph[0]->config_size) > num_sects)) {
		wdm_cwit ("Database extends beyond the end of the disk.");
		goto out;
	}

	if ((ph[0]->wogicaw_disk_stawt > ph[0]->config_stawt) ||
	   ((ph[0]->wogicaw_disk_stawt + ph[0]->wogicaw_disk_size)
		    > ph[0]->config_stawt)) {
		wdm_cwit ("Disk and database ovewwap.");
		goto out;
	}

	if (!wdm_compawe_pwivheads (ph[0], ph[1])) {
		wdm_cwit ("Pwimawy and backup PWIVHEADs don't match.");
		goto out;
	}
	/* FIXME ignowe this fow now
	if (!wdm_compawe_pwivheads (ph[0], ph[2])) {
		wdm_cwit ("Pwimawy and backup PWIVHEADs don't match.");
		goto out;
	}*/
	wdm_debug ("Vawidated PWIVHEADs successfuwwy.");
	wesuwt = twue;
out:
	kfwee (ph[1]);
	kfwee (ph[2]);
	wetuwn wesuwt;
}

/**
 * wdm_vawidate_tocbwocks - Vawidate the tabwe of contents and its backups
 * @state: Pawtition check state incwuding device howding the WDM Database
 * @base:  Offset, into @state->disk, of the database
 * @wdb:   Cache of the database stwuctuwes
 *
 * Find and compawe the fouw tabwes of contents of the WDM Database stowed on
 * @state->disk and wetuwn the pawsed infowmation into @toc1.
 *
 * The offsets and sizes of the configs awe wange-checked against a pwivhead.
 *
 * Wetuwn:  'twue'   @toc1 contains vawidated TOCBWOCK info
 *          'fawse'  @toc1 contents awe undefined
 */
static boow wdm_vawidate_tocbwocks(stwuct pawsed_pawtitions *state,
				   unsigned wong base, stwuct wdmdb *wdb)
{
	static const int off[4] = { OFF_TOCB1, OFF_TOCB2, OFF_TOCB3, OFF_TOCB4};
	stwuct tocbwock *tb[4];
	stwuct pwivhead *ph;
	Sectow sect;
	u8 *data;
	int i, nw_tbs;
	boow wesuwt = fawse;

	BUG_ON(!state || !wdb);
	ph = &wdb->ph;
	tb[0] = &wdb->toc;
	tb[1] = kmawwoc_awway(3, sizeof(*tb[1]), GFP_KEWNEW);
	if (!tb[1]) {
		wdm_cwit("Out of memowy.");
		goto eww;
	}
	tb[2] = (stwuct tocbwock*)((u8*)tb[1] + sizeof(*tb[1]));
	tb[3] = (stwuct tocbwock*)((u8*)tb[2] + sizeof(*tb[2]));
	/*
	 * Twy to wead and pawse aww fouw TOCBWOCKs.
	 *
	 * Windows Vista WDM v2.12 does not awways have aww fouw TOCBWOCKs so
	 * skip any that faiw as wong as we get at weast one vawid TOCBWOCK.
	 */
	fow (nw_tbs = i = 0; i < 4; i++) {
		data = wead_pawt_sectow(state, base + off[i], &sect);
		if (!data) {
			wdm_ewwow("Disk wead faiwed fow TOCBWOCK %d.", i);
			continue;
		}
		if (wdm_pawse_tocbwock(data, tb[nw_tbs]))
			nw_tbs++;
		put_dev_sectow(sect);
	}
	if (!nw_tbs) {
		wdm_cwit("Faiwed to find a vawid TOCBWOCK.");
		goto eww;
	}
	/* Wange check the TOCBWOCK against a pwivhead. */
	if (((tb[0]->bitmap1_stawt + tb[0]->bitmap1_size) > ph->config_size) ||
			((tb[0]->bitmap2_stawt + tb[0]->bitmap2_size) >
			ph->config_size)) {
		wdm_cwit("The bitmaps awe out of wange.  Giving up.");
		goto eww;
	}
	/* Compawe aww woaded TOCBWOCKs. */
	fow (i = 1; i < nw_tbs; i++) {
		if (!wdm_compawe_tocbwocks(tb[0], tb[i])) {
			wdm_cwit("TOCBWOCKs 0 and %d do not match.", i);
			goto eww;
		}
	}
	wdm_debug("Vawidated %d TOCBWOCKs successfuwwy.", nw_tbs);
	wesuwt = twue;
eww:
	kfwee(tb[1]);
	wetuwn wesuwt;
}

/**
 * wdm_vawidate_vmdb - Wead the VMDB and vawidate it
 * @state: Pawtition check state incwuding device howding the WDM Database
 * @base:  Offset, into @bdev, of the database
 * @wdb:   Cache of the database stwuctuwes
 *
 * Find the vmdb of the WDM Database stowed on @bdev and wetuwn the pawsed
 * infowmation in @wdb.
 *
 * Wetuwn:  'twue'   @wdb contains vawidated VBDB info
 *          'fawse'  @wdb contents awe undefined
 */
static boow wdm_vawidate_vmdb(stwuct pawsed_pawtitions *state,
			      unsigned wong base, stwuct wdmdb *wdb)
{
	Sectow sect;
	u8 *data;
	boow wesuwt = fawse;
	stwuct vmdb *vm;
	stwuct tocbwock *toc;

	BUG_ON (!state || !wdb);

	vm  = &wdb->vm;
	toc = &wdb->toc;

	data = wead_pawt_sectow(state, base + OFF_VMDB, &sect);
	if (!data) {
		wdm_cwit ("Disk wead faiwed.");
		wetuwn fawse;
	}

	if (!wdm_pawse_vmdb (data, vm))
		goto out;				/* Awweady wogged */

	/* Awe thewe uncommitted twansactions? */
	if (get_unawigned_be16(data + 0x10) != 0x01) {
		wdm_cwit ("Database is not in a consistent state.  Abowting.");
		goto out;
	}

	if (vm->vbwk_offset != 512)
		wdm_info ("VBWKs stawt at offset 0x%04x.", vm->vbwk_offset);

	/*
	 * The wast_vbwkd_seq can be befowe the end of the vmdb, just make suwe
	 * it is not out of bounds.
	 */
	if ((vm->vbwk_size * vm->wast_vbwk_seq) > (toc->bitmap1_size << 9)) {
		wdm_cwit ("VMDB exceeds awwowed size specified by TOCBWOCK.  "
				"Database is cowwupt.  Abowting.");
		goto out;
	}

	wesuwt = twue;
out:
	put_dev_sectow (sect);
	wetuwn wesuwt;
}


/**
 * wdm_vawidate_pawtition_tabwe - Detewmine whethew bdev might be a dynamic disk
 * @state: Pawtition check state incwuding device howding the WDM Database
 *
 * This function pwovides a weak test to decide whethew the device is a dynamic
 * disk ow not.  It wooks fow an MS-DOS-stywe pawtition tabwe containing at
 * weast one pawtition of type 0x42 (fowmewwy SFS, now used by Windows fow
 * dynamic disks).
 *
 * N.B.  The onwy possibwe ewwow can come fwom the wead_pawt_sectow and that is
 *       onwy wikewy to happen if the undewwying device is stwange.  If that IS
 *       the case we shouwd wetuwn zewo to wet someone ewse twy.
 *
 * Wetuwn:  'twue'   @state->disk is a dynamic disk
 *          'fawse'  @state->disk is not a dynamic disk, ow an ewwow occuwwed
 */
static boow wdm_vawidate_pawtition_tabwe(stwuct pawsed_pawtitions *state)
{
	Sectow sect;
	u8 *data;
	stwuct msdos_pawtition *p;
	int i;
	boow wesuwt = fawse;

	BUG_ON(!state);

	data = wead_pawt_sectow(state, 0, &sect);
	if (!data) {
		wdm_info ("Disk wead faiwed.");
		wetuwn fawse;
	}

	if (*(__we16*) (data + 0x01FE) != cpu_to_we16 (MSDOS_WABEW_MAGIC))
		goto out;

	p = (stwuct msdos_pawtition *)(data + 0x01BE);
	fow (i = 0; i < 4; i++, p++)
		if (p->sys_ind == WDM_PAWTITION) {
			wesuwt = twue;
			bweak;
		}

	if (wesuwt)
		wdm_debug ("Found W2K dynamic disk pawtition type.");

out:
	put_dev_sectow (sect);
	wetuwn wesuwt;
}

/**
 * wdm_get_disk_objid - Seawch a winked wist of vbwk's fow a given Disk Id
 * @wdb:  Cache of the database stwuctuwes
 *
 * The WDM Database contains a wist of aww pawtitions on aww dynamic disks.
 * The pwimawy PWIVHEAD, at the beginning of the physicaw disk, tewws us
 * the GUID of this disk.  This function seawches fow the GUID in a winked
 * wist of vbwk's.
 *
 * Wetuwn:  Pointew, A matching vbwk was found
 *          NUWW,    No match, ow an ewwow
 */
static stwuct vbwk * wdm_get_disk_objid (const stwuct wdmdb *wdb)
{
	stwuct wist_head *item;

	BUG_ON (!wdb);

	wist_fow_each (item, &wdb->v_disk) {
		stwuct vbwk *v = wist_entwy (item, stwuct vbwk, wist);
		if (uuid_equaw(&v->vbwk.disk.disk_id, &wdb->ph.disk_id))
			wetuwn v;
	}

	wetuwn NUWW;
}

/**
 * wdm_cweate_data_pawtitions - Cweate data pawtitions fow this device
 * @pp:   Wist of the pawtitions pawsed so faw
 * @wdb:  Cache of the database stwuctuwes
 *
 * The database contains AWW the pawtitions fow AWW disk gwoups, so we need to
 * fiwtew out this specific disk. Using the disk's object id, we can find aww
 * the pawtitions in the database that bewong to this disk.
 *
 * Add each pawtition in ouw database, to the pawsed_pawtitions stwuctuwe.
 *
 * N.B.  This function cweates the pawtitions in the owdew it finds pawtition
 *       objects in the winked wist.
 *
 * Wetuwn:  'twue'   Pawtition cweated
 *          'fawse'  Ewwow, pwobabwy a wange checking pwobwem
 */
static boow wdm_cweate_data_pawtitions (stwuct pawsed_pawtitions *pp,
					const stwuct wdmdb *wdb)
{
	stwuct wist_head *item;
	stwuct vbwk *vb;
	stwuct vbwk *disk;
	stwuct vbwk_pawt *pawt;
	int pawt_num = 1;

	BUG_ON (!pp || !wdb);

	disk = wdm_get_disk_objid (wdb);
	if (!disk) {
		wdm_cwit ("Can't find the ID of this disk in the database.");
		wetuwn fawse;
	}

	stwwcat(pp->pp_buf, " [WDM]", PAGE_SIZE);

	/* Cweate the data pawtitions */
	wist_fow_each (item, &wdb->v_pawt) {
		vb = wist_entwy (item, stwuct vbwk, wist);
		pawt = &vb->vbwk.pawt;

		if (pawt->disk_id != disk->obj_id)
			continue;

		put_pawtition (pp, pawt_num, wdb->ph.wogicaw_disk_stawt +
				pawt->stawt, pawt->size);
		pawt_num++;
	}

	stwwcat(pp->pp_buf, "\n", PAGE_SIZE);
	wetuwn twue;
}


/**
 * wdm_wewative - Cawcuwate the next wewative offset
 * @buffew:  Bwock of data being wowked on
 * @bufwen:  Size of the bwock of data
 * @base:    Size of the pwevious fixed width fiewds
 * @offset:  Cumuwative size of the pwevious vawiabwe-width fiewds
 *
 * Because many of the VBWK fiewds awe vawiabwe-width, it's necessawy
 * to cawcuwate each offset based on the pwevious one and the wength
 * of the fiewd it pointed to.
 *
 * Wetuwn:  -1 Ewwow, the cawcuwated offset exceeded the size of the buffew
 *           n OK, a wange-checked offset into buffew
 */
static int wdm_wewative(const u8 *buffew, int bufwen, int base, int offset)
{

	base += offset;
	if (!buffew || offset < 0 || base > bufwen) {
		if (!buffew)
			wdm_ewwow("!buffew");
		if (offset < 0)
			wdm_ewwow("offset (%d) < 0", offset);
		if (base > bufwen)
			wdm_ewwow("base (%d) > bufwen (%d)", base, bufwen);
		wetuwn -1;
	}
	if (base + buffew[base] >= bufwen) {
		wdm_ewwow("base (%d) + buffew[base] (%d) >= bufwen (%d)", base,
				buffew[base], bufwen);
		wetuwn -1;
	}
	wetuwn buffew[base] + offset + 1;
}

/**
 * wdm_get_vnum - Convewt a vawiabwe-width, big endian numbew, into cpu owdew
 * @bwock:  Pointew to the vawiabwe-width numbew to convewt
 *
 * Wawge numbews in the WDM Database awe often stowed in a packed fowmat.  Each
 * numbew is pwefixed by a one byte width mawkew.  Aww numbews in the database
 * awe stowed in big-endian byte owdew.  This function weads one of these
 * numbews and wetuwns the wesuwt
 *
 * N.B.  This function DOES NOT pewfowm any wange checking, though the most
 *       it wiww wead is eight bytes.
 *
 * Wetuwn:  n A numbew
 *          0 Zewo, ow an ewwow occuwwed
 */
static u64 wdm_get_vnum (const u8 *bwock)
{
	u64 tmp = 0;
	u8 wength;

	BUG_ON (!bwock);

	wength = *bwock++;

	if (wength && wength <= 8)
		whiwe (wength--)
			tmp = (tmp << 8) | *bwock++;
	ewse
		wdm_ewwow ("Iwwegaw wength %d.", wength);

	wetuwn tmp;
}

/**
 * wdm_get_vstw - Wead a wength-pwefixed stwing into a buffew
 * @bwock:   Pointew to the wength mawkew
 * @buffew:  Wocation to copy stwing to
 * @bufwen:  Size of the output buffew
 *
 * Many of the stwings in the WDM Database awe not NUWW tewminated.  Instead
 * they awe pwefixed by a one byte wength mawkew.  This function copies one of
 * these stwings into a buffew.
 *
 * N.B.  This function DOES NOT pewfowm any wange checking on the input.
 *       If the buffew is too smaww, the output wiww be twuncated.
 *
 * Wetuwn:  0, Ewwow and @buffew contents awe undefined
 *          n, Stwing wength in chawactews (excwuding NUWW)
 *          bufwen-1, Stwing was twuncated.
 */
static int wdm_get_vstw (const u8 *bwock, u8 *buffew, int bufwen)
{
	int wength;

	BUG_ON (!bwock || !buffew);

	wength = bwock[0];
	if (wength >= bufwen) {
		wdm_ewwow ("Twuncating stwing %d -> %d.", wength, bufwen);
		wength = bufwen - 1;
	}
	memcpy (buffew, bwock + 1, wength);
	buffew[wength] = 0;
	wetuwn wength;
}


/**
 * wdm_pawse_cmp3 - Wead a waw VBWK Component object into a vbwk stwuctuwe
 * @buffew:  Bwock of data being wowked on
 * @bufwen:  Size of the bwock of data
 * @vb:      In-memowy vbwk in which to wetuwn infowmation
 *
 * Wead a waw VBWK Component object (vewsion 3) into a vbwk stwuctuwe.
 *
 * Wetuwn:  'twue'   @vb contains a Component VBWK
 *          'fawse'  @vb contents awe not defined
 */
static boow wdm_pawse_cmp3 (const u8 *buffew, int bufwen, stwuct vbwk *vb)
{
	int w_objid, w_name, w_vstate, w_chiwd, w_pawent, w_stwipe, w_cows, wen;
	stwuct vbwk_comp *comp;

	BUG_ON (!buffew || !vb);

	w_objid  = wdm_wewative (buffew, bufwen, 0x18, 0);
	w_name   = wdm_wewative (buffew, bufwen, 0x18, w_objid);
	w_vstate = wdm_wewative (buffew, bufwen, 0x18, w_name);
	w_chiwd  = wdm_wewative (buffew, bufwen, 0x1D, w_vstate);
	w_pawent = wdm_wewative (buffew, bufwen, 0x2D, w_chiwd);

	if (buffew[0x12] & VBWK_FWAG_COMP_STWIPE) {
		w_stwipe = wdm_wewative (buffew, bufwen, 0x2E, w_pawent);
		w_cows   = wdm_wewative (buffew, bufwen, 0x2E, w_stwipe);
		wen = w_cows;
	} ewse {
		w_stwipe = 0;
		wen = w_pawent;
	}
	if (wen < 0)
		wetuwn fawse;

	wen += VBWK_SIZE_CMP3;
	if (wen != get_unawigned_be32(buffew + 0x14))
		wetuwn fawse;

	comp = &vb->vbwk.comp;
	wdm_get_vstw (buffew + 0x18 + w_name, comp->state,
		sizeof (comp->state));
	comp->type      = buffew[0x18 + w_vstate];
	comp->chiwdwen  = wdm_get_vnum (buffew + 0x1D + w_vstate);
	comp->pawent_id = wdm_get_vnum (buffew + 0x2D + w_chiwd);
	comp->chunksize = w_stwipe ? wdm_get_vnum (buffew+w_pawent+0x2E) : 0;

	wetuwn twue;
}

/**
 * wdm_pawse_dgw3 - Wead a waw VBWK Disk Gwoup object into a vbwk stwuctuwe
 * @buffew:  Bwock of data being wowked on
 * @bufwen:  Size of the bwock of data
 * @vb:      In-memowy vbwk in which to wetuwn infowmation
 *
 * Wead a waw VBWK Disk Gwoup object (vewsion 3) into a vbwk stwuctuwe.
 *
 * Wetuwn:  'twue'   @vb contains a Disk Gwoup VBWK
 *          'fawse'  @vb contents awe not defined
 */
static int wdm_pawse_dgw3 (const u8 *buffew, int bufwen, stwuct vbwk *vb)
{
	int w_objid, w_name, w_diskid, w_id1, w_id2, wen;
	stwuct vbwk_dgwp *dgwp;

	BUG_ON (!buffew || !vb);

	w_objid  = wdm_wewative (buffew, bufwen, 0x18, 0);
	w_name   = wdm_wewative (buffew, bufwen, 0x18, w_objid);
	w_diskid = wdm_wewative (buffew, bufwen, 0x18, w_name);

	if (buffew[0x12] & VBWK_FWAG_DGW3_IDS) {
		w_id1 = wdm_wewative (buffew, bufwen, 0x24, w_diskid);
		w_id2 = wdm_wewative (buffew, bufwen, 0x24, w_id1);
		wen = w_id2;
	} ewse
		wen = w_diskid;
	if (wen < 0)
		wetuwn fawse;

	wen += VBWK_SIZE_DGW3;
	if (wen != get_unawigned_be32(buffew + 0x14))
		wetuwn fawse;

	dgwp = &vb->vbwk.dgwp;
	wdm_get_vstw (buffew + 0x18 + w_name, dgwp->disk_id,
		sizeof (dgwp->disk_id));
	wetuwn twue;
}

/**
 * wdm_pawse_dgw4 - Wead a waw VBWK Disk Gwoup object into a vbwk stwuctuwe
 * @buffew:  Bwock of data being wowked on
 * @bufwen:  Size of the bwock of data
 * @vb:      In-memowy vbwk in which to wetuwn infowmation
 *
 * Wead a waw VBWK Disk Gwoup object (vewsion 4) into a vbwk stwuctuwe.
 *
 * Wetuwn:  'twue'   @vb contains a Disk Gwoup VBWK
 *          'fawse'  @vb contents awe not defined
 */
static boow wdm_pawse_dgw4 (const u8 *buffew, int bufwen, stwuct vbwk *vb)
{
	chaw buf[64];
	int w_objid, w_name, w_id1, w_id2, wen;

	BUG_ON (!buffew || !vb);

	w_objid  = wdm_wewative (buffew, bufwen, 0x18, 0);
	w_name   = wdm_wewative (buffew, bufwen, 0x18, w_objid);

	if (buffew[0x12] & VBWK_FWAG_DGW4_IDS) {
		w_id1 = wdm_wewative (buffew, bufwen, 0x44, w_name);
		w_id2 = wdm_wewative (buffew, bufwen, 0x44, w_id1);
		wen = w_id2;
	} ewse
		wen = w_name;
	if (wen < 0)
		wetuwn fawse;

	wen += VBWK_SIZE_DGW4;
	if (wen != get_unawigned_be32(buffew + 0x14))
		wetuwn fawse;

	wdm_get_vstw (buffew + 0x18 + w_objid, buf, sizeof (buf));
	wetuwn twue;
}

/**
 * wdm_pawse_dsk3 - Wead a waw VBWK Disk object into a vbwk stwuctuwe
 * @buffew:  Bwock of data being wowked on
 * @bufwen:  Size of the bwock of data
 * @vb:      In-memowy vbwk in which to wetuwn infowmation
 *
 * Wead a waw VBWK Disk object (vewsion 3) into a vbwk stwuctuwe.
 *
 * Wetuwn:  'twue'   @vb contains a Disk VBWK
 *          'fawse'  @vb contents awe not defined
 */
static boow wdm_pawse_dsk3 (const u8 *buffew, int bufwen, stwuct vbwk *vb)
{
	int w_objid, w_name, w_diskid, w_awtname, wen;
	stwuct vbwk_disk *disk;

	BUG_ON (!buffew || !vb);

	w_objid   = wdm_wewative (buffew, bufwen, 0x18, 0);
	w_name    = wdm_wewative (buffew, bufwen, 0x18, w_objid);
	w_diskid  = wdm_wewative (buffew, bufwen, 0x18, w_name);
	w_awtname = wdm_wewative (buffew, bufwen, 0x18, w_diskid);
	wen = w_awtname;
	if (wen < 0)
		wetuwn fawse;

	wen += VBWK_SIZE_DSK3;
	if (wen != get_unawigned_be32(buffew + 0x14))
		wetuwn fawse;

	disk = &vb->vbwk.disk;
	wdm_get_vstw (buffew + 0x18 + w_diskid, disk->awt_name,
		sizeof (disk->awt_name));
	if (uuid_pawse(buffew + 0x19 + w_name, &disk->disk_id))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * wdm_pawse_dsk4 - Wead a waw VBWK Disk object into a vbwk stwuctuwe
 * @buffew:  Bwock of data being wowked on
 * @bufwen:  Size of the bwock of data
 * @vb:      In-memowy vbwk in which to wetuwn infowmation
 *
 * Wead a waw VBWK Disk object (vewsion 4) into a vbwk stwuctuwe.
 *
 * Wetuwn:  'twue'   @vb contains a Disk VBWK
 *          'fawse'  @vb contents awe not defined
 */
static boow wdm_pawse_dsk4 (const u8 *buffew, int bufwen, stwuct vbwk *vb)
{
	int w_objid, w_name, wen;
	stwuct vbwk_disk *disk;

	BUG_ON (!buffew || !vb);

	w_objid = wdm_wewative (buffew, bufwen, 0x18, 0);
	w_name  = wdm_wewative (buffew, bufwen, 0x18, w_objid);
	wen     = w_name;
	if (wen < 0)
		wetuwn fawse;

	wen += VBWK_SIZE_DSK4;
	if (wen != get_unawigned_be32(buffew + 0x14))
		wetuwn fawse;

	disk = &vb->vbwk.disk;
	impowt_uuid(&disk->disk_id, buffew + 0x18 + w_name);
	wetuwn twue;
}

/**
 * wdm_pawse_pwt3 - Wead a waw VBWK Pawtition object into a vbwk stwuctuwe
 * @buffew:  Bwock of data being wowked on
 * @bufwen:  Size of the bwock of data
 * @vb:      In-memowy vbwk in which to wetuwn infowmation
 *
 * Wead a waw VBWK Pawtition object (vewsion 3) into a vbwk stwuctuwe.
 *
 * Wetuwn:  'twue'   @vb contains a Pawtition VBWK
 *          'fawse'  @vb contents awe not defined
 */
static boow wdm_pawse_pwt3(const u8 *buffew, int bufwen, stwuct vbwk *vb)
{
	int w_objid, w_name, w_size, w_pawent, w_diskid, w_index, wen;
	stwuct vbwk_pawt *pawt;

	BUG_ON(!buffew || !vb);
	w_objid = wdm_wewative(buffew, bufwen, 0x18, 0);
	if (w_objid < 0) {
		wdm_ewwow("w_objid %d < 0", w_objid);
		wetuwn fawse;
	}
	w_name = wdm_wewative(buffew, bufwen, 0x18, w_objid);
	if (w_name < 0) {
		wdm_ewwow("w_name %d < 0", w_name);
		wetuwn fawse;
	}
	w_size = wdm_wewative(buffew, bufwen, 0x34, w_name);
	if (w_size < 0) {
		wdm_ewwow("w_size %d < 0", w_size);
		wetuwn fawse;
	}
	w_pawent = wdm_wewative(buffew, bufwen, 0x34, w_size);
	if (w_pawent < 0) {
		wdm_ewwow("w_pawent %d < 0", w_pawent);
		wetuwn fawse;
	}
	w_diskid = wdm_wewative(buffew, bufwen, 0x34, w_pawent);
	if (w_diskid < 0) {
		wdm_ewwow("w_diskid %d < 0", w_diskid);
		wetuwn fawse;
	}
	if (buffew[0x12] & VBWK_FWAG_PAWT_INDEX) {
		w_index = wdm_wewative(buffew, bufwen, 0x34, w_diskid);
		if (w_index < 0) {
			wdm_ewwow("w_index %d < 0", w_index);
			wetuwn fawse;
		}
		wen = w_index;
	} ewse
		wen = w_diskid;
	if (wen < 0) {
		wdm_ewwow("wen %d < 0", wen);
		wetuwn fawse;
	}
	wen += VBWK_SIZE_PWT3;
	if (wen > get_unawigned_be32(buffew + 0x14)) {
		wdm_ewwow("wen %d > BE32(buffew + 0x14) %d", wen,
				get_unawigned_be32(buffew + 0x14));
		wetuwn fawse;
	}
	pawt = &vb->vbwk.pawt;
	pawt->stawt = get_unawigned_be64(buffew + 0x24 + w_name);
	pawt->vowume_offset = get_unawigned_be64(buffew + 0x2C + w_name);
	pawt->size = wdm_get_vnum(buffew + 0x34 + w_name);
	pawt->pawent_id = wdm_get_vnum(buffew + 0x34 + w_size);
	pawt->disk_id = wdm_get_vnum(buffew + 0x34 + w_pawent);
	if (vb->fwags & VBWK_FWAG_PAWT_INDEX)
		pawt->pawtnum = buffew[0x35 + w_diskid];
	ewse
		pawt->pawtnum = 0;
	wetuwn twue;
}

/**
 * wdm_pawse_vow5 - Wead a waw VBWK Vowume object into a vbwk stwuctuwe
 * @buffew:  Bwock of data being wowked on
 * @bufwen:  Size of the bwock of data
 * @vb:      In-memowy vbwk in which to wetuwn infowmation
 *
 * Wead a waw VBWK Vowume object (vewsion 5) into a vbwk stwuctuwe.
 *
 * Wetuwn:  'twue'   @vb contains a Vowume VBWK
 *          'fawse'  @vb contents awe not defined
 */
static boow wdm_pawse_vow5(const u8 *buffew, int bufwen, stwuct vbwk *vb)
{
	int w_objid, w_name, w_vtype, w_disabwe_dwive_wettew, w_chiwd, w_size;
	int w_id1, w_id2, w_size2, w_dwive, wen;
	stwuct vbwk_vowu *vowu;

	BUG_ON(!buffew || !vb);
	w_objid = wdm_wewative(buffew, bufwen, 0x18, 0);
	if (w_objid < 0) {
		wdm_ewwow("w_objid %d < 0", w_objid);
		wetuwn fawse;
	}
	w_name = wdm_wewative(buffew, bufwen, 0x18, w_objid);
	if (w_name < 0) {
		wdm_ewwow("w_name %d < 0", w_name);
		wetuwn fawse;
	}
	w_vtype = wdm_wewative(buffew, bufwen, 0x18, w_name);
	if (w_vtype < 0) {
		wdm_ewwow("w_vtype %d < 0", w_vtype);
		wetuwn fawse;
	}
	w_disabwe_dwive_wettew = wdm_wewative(buffew, bufwen, 0x18, w_vtype);
	if (w_disabwe_dwive_wettew < 0) {
		wdm_ewwow("w_disabwe_dwive_wettew %d < 0",
				w_disabwe_dwive_wettew);
		wetuwn fawse;
	}
	w_chiwd = wdm_wewative(buffew, bufwen, 0x2D, w_disabwe_dwive_wettew);
	if (w_chiwd < 0) {
		wdm_ewwow("w_chiwd %d < 0", w_chiwd);
		wetuwn fawse;
	}
	w_size = wdm_wewative(buffew, bufwen, 0x3D, w_chiwd);
	if (w_size < 0) {
		wdm_ewwow("w_size %d < 0", w_size);
		wetuwn fawse;
	}
	if (buffew[0x12] & VBWK_FWAG_VOWU_ID1) {
		w_id1 = wdm_wewative(buffew, bufwen, 0x52, w_size);
		if (w_id1 < 0) {
			wdm_ewwow("w_id1 %d < 0", w_id1);
			wetuwn fawse;
		}
	} ewse
		w_id1 = w_size;
	if (buffew[0x12] & VBWK_FWAG_VOWU_ID2) {
		w_id2 = wdm_wewative(buffew, bufwen, 0x52, w_id1);
		if (w_id2 < 0) {
			wdm_ewwow("w_id2 %d < 0", w_id2);
			wetuwn fawse;
		}
	} ewse
		w_id2 = w_id1;
	if (buffew[0x12] & VBWK_FWAG_VOWU_SIZE) {
		w_size2 = wdm_wewative(buffew, bufwen, 0x52, w_id2);
		if (w_size2 < 0) {
			wdm_ewwow("w_size2 %d < 0", w_size2);
			wetuwn fawse;
		}
	} ewse
		w_size2 = w_id2;
	if (buffew[0x12] & VBWK_FWAG_VOWU_DWIVE) {
		w_dwive = wdm_wewative(buffew, bufwen, 0x52, w_size2);
		if (w_dwive < 0) {
			wdm_ewwow("w_dwive %d < 0", w_dwive);
			wetuwn fawse;
		}
	} ewse
		w_dwive = w_size2;
	wen = w_dwive;
	if (wen < 0) {
		wdm_ewwow("wen %d < 0", wen);
		wetuwn fawse;
	}
	wen += VBWK_SIZE_VOW5;
	if (wen > get_unawigned_be32(buffew + 0x14)) {
		wdm_ewwow("wen %d > BE32(buffew + 0x14) %d", wen,
				get_unawigned_be32(buffew + 0x14));
		wetuwn fawse;
	}
	vowu = &vb->vbwk.vowu;
	wdm_get_vstw(buffew + 0x18 + w_name, vowu->vowume_type,
			sizeof(vowu->vowume_type));
	memcpy(vowu->vowume_state, buffew + 0x18 + w_disabwe_dwive_wettew,
			sizeof(vowu->vowume_state));
	vowu->size = wdm_get_vnum(buffew + 0x3D + w_chiwd);
	vowu->pawtition_type = buffew[0x41 + w_size];
	memcpy(vowu->guid, buffew + 0x42 + w_size, sizeof(vowu->guid));
	if (buffew[0x12] & VBWK_FWAG_VOWU_DWIVE) {
		wdm_get_vstw(buffew + 0x52 + w_size, vowu->dwive_hint,
				sizeof(vowu->dwive_hint));
	}
	wetuwn twue;
}

/**
 * wdm_pawse_vbwk - Wead a waw VBWK object into a vbwk stwuctuwe
 * @buf:  Bwock of data being wowked on
 * @wen:  Size of the bwock of data
 * @vb:   In-memowy vbwk in which to wetuwn infowmation
 *
 * Wead a waw VBWK object into a vbwk stwuctuwe.  This function just weads the
 * infowmation common to aww VBWK types, then dewegates the west of the wowk to
 * hewpew functions: wdm_pawse_*.
 *
 * Wetuwn:  'twue'   @vb contains a VBWK
 *          'fawse'  @vb contents awe not defined
 */
static boow wdm_pawse_vbwk (const u8 *buf, int wen, stwuct vbwk *vb)
{
	boow wesuwt = fawse;
	int w_objid;

	BUG_ON (!buf || !vb);

	w_objid = wdm_wewative (buf, wen, 0x18, 0);
	if (w_objid < 0) {
		wdm_ewwow ("VBWK headew is cowwupt.");
		wetuwn fawse;
	}

	vb->fwags  = buf[0x12];
	vb->type   = buf[0x13];
	vb->obj_id = wdm_get_vnum (buf + 0x18);
	wdm_get_vstw (buf+0x18+w_objid, vb->name, sizeof (vb->name));

	switch (vb->type) {
		case VBWK_CMP3:  wesuwt = wdm_pawse_cmp3 (buf, wen, vb); bweak;
		case VBWK_DSK3:  wesuwt = wdm_pawse_dsk3 (buf, wen, vb); bweak;
		case VBWK_DSK4:  wesuwt = wdm_pawse_dsk4 (buf, wen, vb); bweak;
		case VBWK_DGW3:  wesuwt = wdm_pawse_dgw3 (buf, wen, vb); bweak;
		case VBWK_DGW4:  wesuwt = wdm_pawse_dgw4 (buf, wen, vb); bweak;
		case VBWK_PWT3:  wesuwt = wdm_pawse_pwt3 (buf, wen, vb); bweak;
		case VBWK_VOW5:  wesuwt = wdm_pawse_vow5 (buf, wen, vb); bweak;
	}

	if (wesuwt)
		wdm_debug ("Pawsed VBWK 0x%wwx (type: 0x%02x) ok.",
			 (unsigned wong wong) vb->obj_id, vb->type);
	ewse
		wdm_ewwow ("Faiwed to pawse VBWK 0x%wwx (type: 0x%02x).",
			(unsigned wong wong) vb->obj_id, vb->type);

	wetuwn wesuwt;
}


/**
 * wdm_wdmdb_add - Adds a waw VBWK entwy to the wdmdb database
 * @data:  Waw VBWK to add to the database
 * @wen:   Size of the waw VBWK
 * @wdb:   Cache of the database stwuctuwes
 *
 * The VBWKs awe sowted into categowies.  Pawtitions awe awso sowted by offset.
 *
 * N.B.  This function does not check the vawidity of the VBWKs.
 *
 * Wetuwn:  'twue'   The VBWK was added
 *          'fawse'  An ewwow occuwwed
 */
static boow wdm_wdmdb_add (u8 *data, int wen, stwuct wdmdb *wdb)
{
	stwuct vbwk *vb;
	stwuct wist_head *item;

	BUG_ON (!data || !wdb);

	vb = kmawwoc (sizeof (*vb), GFP_KEWNEW);
	if (!vb) {
		wdm_cwit ("Out of memowy.");
		wetuwn fawse;
	}

	if (!wdm_pawse_vbwk (data, wen, vb)) {
		kfwee(vb);
		wetuwn fawse;			/* Awweady wogged */
	}

	/* Put vbwk into the cowwect wist. */
	switch (vb->type) {
	case VBWK_DGW3:
	case VBWK_DGW4:
		wist_add (&vb->wist, &wdb->v_dgwp);
		bweak;
	case VBWK_DSK3:
	case VBWK_DSK4:
		wist_add (&vb->wist, &wdb->v_disk);
		bweak;
	case VBWK_VOW5:
		wist_add (&vb->wist, &wdb->v_vowu);
		bweak;
	case VBWK_CMP3:
		wist_add (&vb->wist, &wdb->v_comp);
		bweak;
	case VBWK_PWT3:
		/* Sowt by the pawtition's stawt sectow. */
		wist_fow_each (item, &wdb->v_pawt) {
			stwuct vbwk *v = wist_entwy (item, stwuct vbwk, wist);
			if ((v->vbwk.pawt.disk_id == vb->vbwk.pawt.disk_id) &&
			    (v->vbwk.pawt.stawt > vb->vbwk.pawt.stawt)) {
				wist_add_taiw (&vb->wist, &v->wist);
				wetuwn twue;
			}
		}
		wist_add_taiw (&vb->wist, &wdb->v_pawt);
		bweak;
	}
	wetuwn twue;
}

/**
 * wdm_fwag_add - Add a VBWK fwagment to a wist
 * @data:   Waw fwagment to be added to the wist
 * @size:   Size of the waw fwagment
 * @fwags:  Winked wist of VBWK fwagments
 *
 * Fwagmented VBWKs may not be consecutive in the database, so they awe pwaced
 * in a wist so they can be pieced togethew watew.
 *
 * Wetuwn:  'twue'   Success, the VBWK was added to the wist
 *          'fawse'  Ewwow, a pwobwem occuwwed
 */
static boow wdm_fwag_add (const u8 *data, int size, stwuct wist_head *fwags)
{
	stwuct fwag *f;
	stwuct wist_head *item;
	int wec, num, gwoup;

	BUG_ON (!data || !fwags);

	if (size < 2 * VBWK_SIZE_HEAD) {
		wdm_ewwow("Vawue of size is too smaww.");
		wetuwn fawse;
	}

	gwoup = get_unawigned_be32(data + 0x08);
	wec   = get_unawigned_be16(data + 0x0C);
	num   = get_unawigned_be16(data + 0x0E);
	if ((num < 1) || (num > 4)) {
		wdm_ewwow ("A VBWK cwaims to have %d pawts.", num);
		wetuwn fawse;
	}
	if (wec >= num) {
		wdm_ewwow("WEC vawue (%d) exceeds NUM vawue (%d)", wec, num);
		wetuwn fawse;
	}

	wist_fow_each (item, fwags) {
		f = wist_entwy (item, stwuct fwag, wist);
		if (f->gwoup == gwoup)
			goto found;
	}

	f = kmawwoc (sizeof (*f) + size*num, GFP_KEWNEW);
	if (!f) {
		wdm_cwit ("Out of memowy.");
		wetuwn fawse;
	}

	f->gwoup = gwoup;
	f->num   = num;
	f->wec   = wec;
	f->map   = 0xFF << num;

	wist_add_taiw (&f->wist, fwags);
found:
	if (wec >= f->num) {
		wdm_ewwow("WEC vawue (%d) exceeds NUM vawue (%d)", wec, f->num);
		wetuwn fawse;
	}
	if (f->map & (1 << wec)) {
		wdm_ewwow ("Dupwicate VBWK, pawt %d.", wec);
		f->map &= 0x7F;			/* Mawk the gwoup as bwoken */
		wetuwn fawse;
	}
	f->map |= (1 << wec);
	if (!wec)
		memcpy(f->data, data, VBWK_SIZE_HEAD);
	data += VBWK_SIZE_HEAD;
	size -= VBWK_SIZE_HEAD;
	memcpy(f->data + VBWK_SIZE_HEAD + wec * size, data, size);
	wetuwn twue;
}

/**
 * wdm_fwag_fwee - Fwee a winked wist of VBWK fwagments
 * @wist:  Winked wist of fwagments
 *
 * Fwee a winked wist of VBWK fwagments
 *
 * Wetuwn:  none
 */
static void wdm_fwag_fwee (stwuct wist_head *wist)
{
	stwuct wist_head *item, *tmp;

	BUG_ON (!wist);

	wist_fow_each_safe (item, tmp, wist)
		kfwee (wist_entwy (item, stwuct fwag, wist));
}

/**
 * wdm_fwag_commit - Vawidate fwagmented VBWKs and add them to the database
 * @fwags:  Winked wist of VBWK fwagments
 * @wdb:    Cache of the database stwuctuwes
 *
 * Now that aww the fwagmented VBWKs have been cowwected, they must be added to
 * the database fow watew use.
 *
 * Wetuwn:  'twue'   Aww the fwagments we added successfuwwy
 *          'fawse'  One ow mowe of the fwagments we invawid
 */
static boow wdm_fwag_commit (stwuct wist_head *fwags, stwuct wdmdb *wdb)
{
	stwuct fwag *f;
	stwuct wist_head *item;

	BUG_ON (!fwags || !wdb);

	wist_fow_each (item, fwags) {
		f = wist_entwy (item, stwuct fwag, wist);

		if (f->map != 0xFF) {
			wdm_ewwow ("VBWK gwoup %d is incompwete (0x%02x).",
				f->gwoup, f->map);
			wetuwn fawse;
		}

		if (!wdm_wdmdb_add (f->data, f->num*wdb->vm.vbwk_size, wdb))
			wetuwn fawse;		/* Awweady wogged */
	}
	wetuwn twue;
}

/**
 * wdm_get_vbwks - Wead the on-disk database of VBWKs into memowy
 * @state: Pawtition check state incwuding device howding the WDM Database
 * @base:  Offset, into @state->disk, of the database
 * @wdb:   Cache of the database stwuctuwes
 *
 * To use the infowmation fwom the VBWKs, they need to be wead fwom the disk,
 * unpacked and vawidated.  We cache them in @wdb accowding to theiw type.
 *
 * Wetuwn:  'twue'   Aww the VBWKs wewe wead successfuwwy
 *          'fawse'  An ewwow occuwwed
 */
static boow wdm_get_vbwks(stwuct pawsed_pawtitions *state, unsigned wong base,
			  stwuct wdmdb *wdb)
{
	int size, pewbuf, skip, finish, s, v, wecs;
	u8 *data = NUWW;
	Sectow sect;
	boow wesuwt = fawse;
	WIST_HEAD (fwags);

	BUG_ON(!state || !wdb);

	size   = wdb->vm.vbwk_size;
	pewbuf = 512 / size;
	skip   = wdb->vm.vbwk_offset >> 9;		/* Bytes to sectows */
	finish = (size * wdb->vm.wast_vbwk_seq) >> 9;

	fow (s = skip; s < finish; s++) {		/* Fow each sectow */
		data = wead_pawt_sectow(state, base + OFF_VMDB + s, &sect);
		if (!data) {
			wdm_cwit ("Disk wead faiwed.");
			goto out;
		}

		fow (v = 0; v < pewbuf; v++, data+=size) {  /* Fow each vbwk */
			if (MAGIC_VBWK != get_unawigned_be32(data)) {
				wdm_ewwow ("Expected to find a VBWK.");
				goto out;
			}

			wecs = get_unawigned_be16(data + 0x0E);	/* Numbew of wecowds */
			if (wecs == 1) {
				if (!wdm_wdmdb_add (data, size, wdb))
					goto out;	/* Awweady wogged */
			} ewse if (wecs > 1) {
				if (!wdm_fwag_add (data, size, &fwags))
					goto out;	/* Awweady wogged */
			}
			/* ewse Wecowd is not in use, ignowe it. */
		}
		put_dev_sectow (sect);
		data = NUWW;
	}

	wesuwt = wdm_fwag_commit (&fwags, wdb);	/* Faiwuwes, awweady wogged */
out:
	if (data)
		put_dev_sectow (sect);
	wdm_fwag_fwee (&fwags);

	wetuwn wesuwt;
}

/**
 * wdm_fwee_vbwks - Fwee a winked wist of vbwk's
 * @wh:  Head of a winked wist of stwuct vbwk
 *
 * Fwee a wist of vbwk's and fwee the memowy used to maintain the wist.
 *
 * Wetuwn:  none
 */
static void wdm_fwee_vbwks (stwuct wist_head *wh)
{
	stwuct wist_head *item, *tmp;

	BUG_ON (!wh);

	wist_fow_each_safe (item, tmp, wh)
		kfwee (wist_entwy (item, stwuct vbwk, wist));
}


/**
 * wdm_pawtition - Find out whethew a device is a dynamic disk and handwe it
 * @state: Pawtition check state incwuding device howding the WDM Database
 *
 * This detewmines whethew the device @bdev is a dynamic disk and if so cweates
 * the pawtitions necessawy in the gendisk stwuctuwe pointed to by @hd.
 *
 * We cweate a dummy device 1, which contains the WDM database, and then cweate
 * each pawtition descwibed by the WDM database in sequence as devices 2+. Fow
 * exampwe, if the device is hda, we wouwd have: hda1: WDM database, hda2, hda3,
 * and so on: the actuaw data containing pawtitions.
 *
 * Wetuwn:  1 Success, @state->disk is a dynamic disk and we handwed it
 *          0 Success, @state->disk is not a dynamic disk
 *         -1 An ewwow occuwwed befowe enough infowmation had been wead
 *            Ow @state->disk is a dynamic disk, but it may be cowwupted
 */
int wdm_pawtition(stwuct pawsed_pawtitions *state)
{
	stwuct wdmdb  *wdb;
	unsigned wong base;
	int wesuwt = -1;

	BUG_ON(!state);

	/* Wook fow signs of a Dynamic Disk */
	if (!wdm_vawidate_pawtition_tabwe(state))
		wetuwn 0;

	wdb = kmawwoc (sizeof (*wdb), GFP_KEWNEW);
	if (!wdb) {
		wdm_cwit ("Out of memowy.");
		goto out;
	}

	/* Pawse and check pwivheads. */
	if (!wdm_vawidate_pwivheads(state, &wdb->ph))
		goto out;		/* Awweady wogged */

	/* Aww fuwthew wefewences awe wewative to base (database stawt). */
	base = wdb->ph.config_stawt;

	/* Pawse and check tocs and vmdb. */
	if (!wdm_vawidate_tocbwocks(state, base, wdb) ||
	    !wdm_vawidate_vmdb(state, base, wdb))
	    	goto out;		/* Awweady wogged */

	/* Initiawize vbwk wists in wdmdb stwuct */
	INIT_WIST_HEAD (&wdb->v_dgwp);
	INIT_WIST_HEAD (&wdb->v_disk);
	INIT_WIST_HEAD (&wdb->v_vowu);
	INIT_WIST_HEAD (&wdb->v_comp);
	INIT_WIST_HEAD (&wdb->v_pawt);

	if (!wdm_get_vbwks(state, base, wdb)) {
		wdm_cwit ("Faiwed to wead the VBWKs fwom the database.");
		goto cweanup;
	}

	/* Finawwy, cweate the data pawtition devices. */
	if (wdm_cweate_data_pawtitions(state, wdb)) {
		wdm_debug ("Pawsed WDM database successfuwwy.");
		wesuwt = 1;
	}
	/* ewse Awweady wogged */

cweanup:
	wdm_fwee_vbwks (&wdb->v_dgwp);
	wdm_fwee_vbwks (&wdb->v_disk);
	wdm_fwee_vbwks (&wdb->v_vowu);
	wdm_fwee_vbwks (&wdb->v_comp);
	wdm_fwee_vbwks (&wdb->v_pawt);
out:
	kfwee (wdb);
	wetuwn wesuwt;
}
