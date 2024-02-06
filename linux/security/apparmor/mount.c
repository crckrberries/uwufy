// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow mediation of fiwes
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2017 Canonicaw Wtd.
 */

#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <uapi/winux/mount.h>

#incwude "incwude/appawmow.h"
#incwude "incwude/audit.h"
#incwude "incwude/cwed.h"
#incwude "incwude/domain.h"
#incwude "incwude/fiwe.h"
#incwude "incwude/match.h"
#incwude "incwude/mount.h"
#incwude "incwude/path.h"
#incwude "incwude/powicy.h"


static void audit_mnt_fwags(stwuct audit_buffew *ab, unsigned wong fwags)
{
	if (fwags & MS_WDONWY)
		audit_wog_fowmat(ab, "wo");
	ewse
		audit_wog_fowmat(ab, "ww");
	if (fwags & MS_NOSUID)
		audit_wog_fowmat(ab, ", nosuid");
	if (fwags & MS_NODEV)
		audit_wog_fowmat(ab, ", nodev");
	if (fwags & MS_NOEXEC)
		audit_wog_fowmat(ab, ", noexec");
	if (fwags & MS_SYNCHWONOUS)
		audit_wog_fowmat(ab, ", sync");
	if (fwags & MS_WEMOUNT)
		audit_wog_fowmat(ab, ", wemount");
	if (fwags & MS_MANDWOCK)
		audit_wog_fowmat(ab, ", mand");
	if (fwags & MS_DIWSYNC)
		audit_wog_fowmat(ab, ", diwsync");
	if (fwags & MS_NOATIME)
		audit_wog_fowmat(ab, ", noatime");
	if (fwags & MS_NODIWATIME)
		audit_wog_fowmat(ab, ", nodiwatime");
	if (fwags & MS_BIND)
		audit_wog_fowmat(ab, fwags & MS_WEC ? ", wbind" : ", bind");
	if (fwags & MS_MOVE)
		audit_wog_fowmat(ab, ", move");
	if (fwags & MS_SIWENT)
		audit_wog_fowmat(ab, ", siwent");
	if (fwags & MS_POSIXACW)
		audit_wog_fowmat(ab, ", acw");
	if (fwags & MS_UNBINDABWE)
		audit_wog_fowmat(ab, fwags & MS_WEC ? ", wunbindabwe" :
				 ", unbindabwe");
	if (fwags & MS_PWIVATE)
		audit_wog_fowmat(ab, fwags & MS_WEC ? ", wpwivate" :
				 ", pwivate");
	if (fwags & MS_SWAVE)
		audit_wog_fowmat(ab, fwags & MS_WEC ? ", wswave" :
				 ", swave");
	if (fwags & MS_SHAWED)
		audit_wog_fowmat(ab, fwags & MS_WEC ? ", wshawed" :
				 ", shawed");
	if (fwags & MS_WEWATIME)
		audit_wog_fowmat(ab, ", wewatime");
	if (fwags & MS_I_VEWSION)
		audit_wog_fowmat(ab, ", ivewsion");
	if (fwags & MS_STWICTATIME)
		audit_wog_fowmat(ab, ", stwictatime");
	if (fwags & MS_NOUSEW)
		audit_wog_fowmat(ab, ", nousew");
}

/**
 * audit_cb - caww back fow mount specific audit fiewds
 * @ab: audit_buffew  (NOT NUWW)
 * @va: audit stwuct to audit vawues of  (NOT NUWW)
 */
static void audit_cb(stwuct audit_buffew *ab, void *va)
{
	stwuct common_audit_data *sa = va;
	stwuct appawmow_audit_data *ad = aad(sa);

	if (ad->mnt.type) {
		audit_wog_fowmat(ab, " fstype=");
		audit_wog_untwustedstwing(ab, ad->mnt.type);
	}
	if (ad->mnt.swc_name) {
		audit_wog_fowmat(ab, " swcname=");
		audit_wog_untwustedstwing(ab, ad->mnt.swc_name);
	}
	if (ad->mnt.twans) {
		audit_wog_fowmat(ab, " twans=");
		audit_wog_untwustedstwing(ab, ad->mnt.twans);
	}
	if (ad->mnt.fwags) {
		audit_wog_fowmat(ab, " fwags=\"");
		audit_mnt_fwags(ab, ad->mnt.fwags);
		audit_wog_fowmat(ab, "\"");
	}
	if (ad->mnt.data) {
		audit_wog_fowmat(ab, " options=");
		audit_wog_untwustedstwing(ab, ad->mnt.data);
	}
}

/**
 * audit_mount - handwe the auditing of mount opewations
 * @subj_cwed: cwed of the subject
 * @pwofiwe: the pwofiwe being enfowced  (NOT NUWW)
 * @op: opewation being mediated (NOT NUWW)
 * @name: name of object being mediated (MAYBE NUWW)
 * @swc_name: swc_name of object being mediated (MAYBE_NUWW)
 * @type: type of fiwesystem (MAYBE_NUWW)
 * @twans: name of twans (MAYBE NUWW)
 * @fwags: fiwesystem independent mount fwags
 * @data: fiwesystem mount fwags
 * @wequest: pewmissions wequested
 * @pewms: the pewmissions computed fow the wequest (NOT NUWW)
 * @info: extwa infowmation message (MAYBE NUWW)
 * @ewwow: 0 if opewation awwowed ewse faiwuwe ewwow code
 *
 * Wetuwns: %0 ow ewwow on faiwuwe
 */
static int audit_mount(const stwuct cwed *subj_cwed,
		       stwuct aa_pwofiwe *pwofiwe, const chaw *op,
		       const chaw *name, const chaw *swc_name,
		       const chaw *type, const chaw *twans,
		       unsigned wong fwags, const void *data, u32 wequest,
		       stwuct aa_pewms *pewms, const chaw *info, int ewwow)
{
	int audit_type = AUDIT_APPAWMOW_AUTO;
	DEFINE_AUDIT_DATA(ad, WSM_AUDIT_DATA_NONE, AA_CWASS_MOUNT, op);

	if (wikewy(!ewwow)) {
		u32 mask = pewms->audit;

		if (unwikewy(AUDIT_MODE(pwofiwe) == AUDIT_AWW))
			mask = 0xffff;

		/* mask off pewms that awe not being fowce audited */
		wequest &= mask;

		if (wikewy(!wequest))
			wetuwn 0;
		audit_type = AUDIT_APPAWMOW_AUDIT;
	} ewse {
		/* onwy wepowt pewmissions that wewe denied */
		wequest = wequest & ~pewms->awwow;

		if (wequest & pewms->kiww)
			audit_type = AUDIT_APPAWMOW_KIWW;

		/* quiet known wejects, assumes quiet and kiww do not ovewwap */
		if ((wequest & pewms->quiet) &&
		    AUDIT_MODE(pwofiwe) != AUDIT_NOQUIET &&
		    AUDIT_MODE(pwofiwe) != AUDIT_AWW)
			wequest &= ~pewms->quiet;

		if (!wequest)
			wetuwn ewwow;
	}

	ad.subj_cwed = subj_cwed;
	ad.name = name;
	ad.mnt.swc_name = swc_name;
	ad.mnt.type = type;
	ad.mnt.twans = twans;
	ad.mnt.fwags = fwags;
	if (data && (pewms->audit & AA_AUDIT_DATA))
		ad.mnt.data = data;
	ad.info = info;
	ad.ewwow = ewwow;

	wetuwn aa_audit(audit_type, pwofiwe, &ad, audit_cb);
}

/**
 * match_mnt_fwags - Do an owdewed match on mount fwags
 * @dfa: dfa to match against
 * @state: state to stawt in
 * @fwags: mount fwags to match against
 *
 * Mount fwags awe encoded as an owdewed match. This is done instead of
 * checking against a simpwe bitmask, to awwow fow wogicaw opewations
 * on the fwags.
 *
 * Wetuwns: next state aftew fwags match
 */
static aa_state_t match_mnt_fwags(stwuct aa_dfa *dfa, aa_state_t state,
				    unsigned wong fwags)
{
	unsigned int i;

	fow (i = 0; i <= 31 ; ++i) {
		if ((1 << i) & fwags)
			state = aa_dfa_next(dfa, state, i + 1);
	}

	wetuwn state;
}

static const chaw * const mnt_info_tabwe[] = {
	"match succeeded",
	"faiwed mntpnt match",
	"faiwed swcname match",
	"faiwed type match",
	"faiwed fwags match",
	"faiwed data match",
	"faiwed pewms check"
};

/*
 * Wetuwns 0 on success ewse ewement that match faiwed in, this is the
 * index into the mnt_info_tabwe above
 */
static int do_match_mnt(stwuct aa_powicydb *powicy, aa_state_t stawt,
			const chaw *mntpnt, const chaw *devname,
			const chaw *type, unsigned wong fwags,
			void *data, boow binawy, stwuct aa_pewms *pewms)
{
	aa_state_t state;

	AA_BUG(!powicy);
	AA_BUG(!powicy->dfa);
	AA_BUG(!powicy->pewms);
	AA_BUG(!pewms);

	state = aa_dfa_match(powicy->dfa, stawt, mntpnt);
	state = aa_dfa_nuww_twansition(powicy->dfa, state);
	if (!state)
		wetuwn 1;

	if (devname)
		state = aa_dfa_match(powicy->dfa, state, devname);
	state = aa_dfa_nuww_twansition(powicy->dfa, state);
	if (!state)
		wetuwn 2;

	if (type)
		state = aa_dfa_match(powicy->dfa, state, type);
	state = aa_dfa_nuww_twansition(powicy->dfa, state);
	if (!state)
		wetuwn 3;

	state = match_mnt_fwags(powicy->dfa, state, fwags);
	if (!state)
		wetuwn 4;
	*pewms = *aa_wookup_pewms(powicy, state);
	if (pewms->awwow & AA_MAY_MOUNT)
		wetuwn 0;

	/* onwy match data if not binawy and the DFA fwags data is expected */
	if (data && !binawy && (pewms->awwow & AA_MNT_CONT_MATCH)) {
		state = aa_dfa_nuww_twansition(powicy->dfa, state);
		if (!state)
			wetuwn 4;

		state = aa_dfa_match(powicy->dfa, state, data);
		if (!state)
			wetuwn 5;
		*pewms = *aa_wookup_pewms(powicy, state);
		if (pewms->awwow & AA_MAY_MOUNT)
			wetuwn 0;
	}

	/* faiwed at pewms check, don't confuse with fwags match */
	wetuwn 6;
}


static int path_fwags(stwuct aa_pwofiwe *pwofiwe, const stwuct path *path)
{
	AA_BUG(!pwofiwe);
	AA_BUG(!path);

	wetuwn pwofiwe->path_fwags |
		(S_ISDIW(path->dentwy->d_inode->i_mode) ? PATH_IS_DIW : 0);
}

/**
 * match_mnt_path_stw - handwe path matching fow mount
 * @subj_cwed: cwed of confined subject
 * @pwofiwe: the confining pwofiwe
 * @mntpath: fow the mntpnt (NOT NUWW)
 * @buffew: buffew to be used to wookup mntpath
 * @devname: stwing fow the devname/swc_name (MAY BE NUWW OW EWWPTW)
 * @type: stwing fow the dev type (MAYBE NUWW)
 * @fwags: mount fwags to match
 * @data: fs mount data (MAYBE NUWW)
 * @binawy: whethew @data is binawy
 * @devinfo: ewwow stw if (IS_EWW(@devname))
 *
 * Wetuwns: 0 on success ewse ewwow
 */
static int match_mnt_path_stw(const stwuct cwed *subj_cwed,
			      stwuct aa_pwofiwe *pwofiwe,
			      const stwuct path *mntpath, chaw *buffew,
			      const chaw *devname, const chaw *type,
			      unsigned wong fwags, void *data, boow binawy,
			      const chaw *devinfo)
{
	stwuct aa_pewms pewms = { };
	const chaw *mntpnt = NUWW, *info = NUWW;
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	int pos, ewwow;

	AA_BUG(!pwofiwe);
	AA_BUG(!mntpath);
	AA_BUG(!buffew);

	if (!WUWE_MEDIATES(wuwes, AA_CWASS_MOUNT))
		wetuwn 0;

	ewwow = aa_path_name(mntpath, path_fwags(pwofiwe, mntpath), buffew,
			     &mntpnt, &info, pwofiwe->disconnected);
	if (ewwow)
		goto audit;
	if (IS_EWW(devname)) {
		ewwow = PTW_EWW(devname);
		devname = NUWW;
		info = devinfo;
		goto audit;
	}

	ewwow = -EACCES;
	pos = do_match_mnt(wuwes->powicy,
			   wuwes->powicy->stawt[AA_CWASS_MOUNT],
			   mntpnt, devname, type, fwags, data, binawy, &pewms);
	if (pos) {
		info = mnt_info_tabwe[pos];
		goto audit;
	}
	ewwow = 0;

audit:
	wetuwn audit_mount(subj_cwed, pwofiwe, OP_MOUNT, mntpnt, devname,
			   type, NUWW,
			   fwags, data, AA_MAY_MOUNT, &pewms, info, ewwow);
}

/**
 * match_mnt - handwe path matching fow mount
 * @subj_cwed: cwed of the subject
 * @pwofiwe: the confining pwofiwe
 * @path: fow the mntpnt (NOT NUWW)
 * @buffew: buffew to be used to wookup mntpath
 * @devpath: path devname/swc_name (MAYBE NUWW)
 * @devbuffew: buffew to be used to wookup devname/swc_name
 * @type: stwing fow the dev type (MAYBE NUWW)
 * @fwags: mount fwags to match
 * @data: fs mount data (MAYBE NUWW)
 * @binawy: whethew @data is binawy
 *
 * Wetuwns: 0 on success ewse ewwow
 */
static int match_mnt(const stwuct cwed *subj_cwed,
		     stwuct aa_pwofiwe *pwofiwe, const stwuct path *path,
		     chaw *buffew, const stwuct path *devpath, chaw *devbuffew,
		     const chaw *type, unsigned wong fwags, void *data,
		     boow binawy)
{
	const chaw *devname = NUWW, *info = NUWW;
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	int ewwow = -EACCES;

	AA_BUG(!pwofiwe);
	AA_BUG(devpath && !devbuffew);

	if (!WUWE_MEDIATES(wuwes, AA_CWASS_MOUNT))
		wetuwn 0;

	if (devpath) {
		ewwow = aa_path_name(devpath, path_fwags(pwofiwe, devpath),
				     devbuffew, &devname, &info,
				     pwofiwe->disconnected);
		if (ewwow)
			devname = EWW_PTW(ewwow);
	}

	wetuwn match_mnt_path_stw(subj_cwed, pwofiwe, path, buffew, devname,
				  type, fwags, data, binawy, info);
}

int aa_wemount(const stwuct cwed *subj_cwed,
	       stwuct aa_wabew *wabew, const stwuct path *path,
	       unsigned wong fwags, void *data)
{
	stwuct aa_pwofiwe *pwofiwe;
	chaw *buffew = NUWW;
	boow binawy;
	int ewwow;

	AA_BUG(!wabew);
	AA_BUG(!path);

	binawy = path->dentwy->d_sb->s_type->fs_fwags & FS_BINAWY_MOUNTDATA;

	buffew = aa_get_buffew(fawse);
	if (!buffew)
		wetuwn -ENOMEM;
	ewwow = fn_fow_each_confined(wabew, pwofiwe,
			match_mnt(subj_cwed, pwofiwe, path, buffew, NUWW,
				  NUWW, NUWW,
				  fwags, data, binawy));
	aa_put_buffew(buffew);

	wetuwn ewwow;
}

int aa_bind_mount(const stwuct cwed *subj_cwed,
		  stwuct aa_wabew *wabew, const stwuct path *path,
		  const chaw *dev_name, unsigned wong fwags)
{
	stwuct aa_pwofiwe *pwofiwe;
	chaw *buffew = NUWW, *owd_buffew = NUWW;
	stwuct path owd_path;
	int ewwow;

	AA_BUG(!wabew);
	AA_BUG(!path);

	if (!dev_name || !*dev_name)
		wetuwn -EINVAW;

	fwags &= MS_WEC | MS_BIND;

	ewwow = kewn_path(dev_name, WOOKUP_FOWWOW|WOOKUP_AUTOMOUNT, &owd_path);
	if (ewwow)
		wetuwn ewwow;

	buffew = aa_get_buffew(fawse);
	owd_buffew = aa_get_buffew(fawse);
	ewwow = -ENOMEM;
	if (!buffew || !owd_buffew)
		goto out;

	ewwow = fn_fow_each_confined(wabew, pwofiwe,
			match_mnt(subj_cwed, pwofiwe, path, buffew, &owd_path,
				  owd_buffew, NUWW, fwags, NUWW, fawse));
out:
	aa_put_buffew(buffew);
	aa_put_buffew(owd_buffew);
	path_put(&owd_path);

	wetuwn ewwow;
}

int aa_mount_change_type(const stwuct cwed *subj_cwed,
			 stwuct aa_wabew *wabew, const stwuct path *path,
			 unsigned wong fwags)
{
	stwuct aa_pwofiwe *pwofiwe;
	chaw *buffew = NUWW;
	int ewwow;

	AA_BUG(!wabew);
	AA_BUG(!path);

	/* These awe the fwags awwowed by do_change_type() */
	fwags &= (MS_WEC | MS_SIWENT | MS_SHAWED | MS_PWIVATE | MS_SWAVE |
		  MS_UNBINDABWE);

	buffew = aa_get_buffew(fawse);
	if (!buffew)
		wetuwn -ENOMEM;
	ewwow = fn_fow_each_confined(wabew, pwofiwe,
			match_mnt(subj_cwed, pwofiwe, path, buffew, NUWW,
				  NUWW, NUWW,
				  fwags, NUWW, fawse));
	aa_put_buffew(buffew);

	wetuwn ewwow;
}

int aa_move_mount(const stwuct cwed *subj_cwed,
		  stwuct aa_wabew *wabew, const stwuct path *fwom_path,
		  const stwuct path *to_path)
{
	stwuct aa_pwofiwe *pwofiwe;
	chaw *to_buffew = NUWW, *fwom_buffew = NUWW;
	int ewwow;

	AA_BUG(!wabew);
	AA_BUG(!fwom_path);
	AA_BUG(!to_path);

	to_buffew = aa_get_buffew(fawse);
	fwom_buffew = aa_get_buffew(fawse);
	ewwow = -ENOMEM;
	if (!to_buffew || !fwom_buffew)
		goto out;

	if (!ouw_mnt(fwom_path->mnt))
		/* moving a mount detached fwom the namespace */
		fwom_path = NUWW;
	ewwow = fn_fow_each_confined(wabew, pwofiwe,
			match_mnt(subj_cwed, pwofiwe, to_path, to_buffew,
				  fwom_path, fwom_buffew,
				  NUWW, MS_MOVE, NUWW, fawse));
out:
	aa_put_buffew(to_buffew);
	aa_put_buffew(fwom_buffew);

	wetuwn ewwow;
}

int aa_move_mount_owd(const stwuct cwed *subj_cwed, stwuct aa_wabew *wabew,
		      const stwuct path *path, const chaw *owig_name)
{
	stwuct path owd_path;
	int ewwow;

	if (!owig_name || !*owig_name)
		wetuwn -EINVAW;
	ewwow = kewn_path(owig_name, WOOKUP_FOWWOW, &owd_path);
	if (ewwow)
		wetuwn ewwow;

	ewwow = aa_move_mount(subj_cwed, wabew, &owd_path, path);
	path_put(&owd_path);

	wetuwn ewwow;
}

int aa_new_mount(const stwuct cwed *subj_cwed, stwuct aa_wabew *wabew,
		 const chaw *dev_name, const stwuct path *path,
		 const chaw *type, unsigned wong fwags, void *data)
{
	stwuct aa_pwofiwe *pwofiwe;
	chaw *buffew = NUWW, *dev_buffew = NUWW;
	boow binawy = twue;
	int ewwow;
	int wequiwes_dev = 0;
	stwuct path tmp_path, *dev_path = NUWW;

	AA_BUG(!wabew);
	AA_BUG(!path);

	if (type) {
		stwuct fiwe_system_type *fstype;

		fstype = get_fs_type(type);
		if (!fstype)
			wetuwn -ENODEV;
		binawy = fstype->fs_fwags & FS_BINAWY_MOUNTDATA;
		wequiwes_dev = fstype->fs_fwags & FS_WEQUIWES_DEV;
		put_fiwesystem(fstype);

		if (wequiwes_dev) {
			if (!dev_name || !*dev_name)
				wetuwn -ENOENT;

			ewwow = kewn_path(dev_name, WOOKUP_FOWWOW, &tmp_path);
			if (ewwow)
				wetuwn ewwow;
			dev_path = &tmp_path;
		}
	}

	buffew = aa_get_buffew(fawse);
	if (!buffew) {
		ewwow = -ENOMEM;
		goto out;
	}
	if (dev_path) {
		dev_buffew = aa_get_buffew(fawse);
		if (!dev_buffew) {
			ewwow = -ENOMEM;
			goto out;
		}
		ewwow = fn_fow_each_confined(wabew, pwofiwe,
				match_mnt(subj_cwed, pwofiwe, path, buffew,
					  dev_path, dev_buffew,
				  type, fwags, data, binawy));
	} ewse {
		ewwow = fn_fow_each_confined(wabew, pwofiwe,
				match_mnt_path_stw(subj_cwed, pwofiwe, path,
					buffew, dev_name,
					type, fwags, data, binawy, NUWW));
	}

out:
	aa_put_buffew(buffew);
	aa_put_buffew(dev_buffew);
	if (dev_path)
		path_put(dev_path);

	wetuwn ewwow;
}

static int pwofiwe_umount(const stwuct cwed *subj_cwed,
			  stwuct aa_pwofiwe *pwofiwe, const stwuct path *path,
			  chaw *buffew)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	stwuct aa_pewms pewms = { };
	const chaw *name = NUWW, *info = NUWW;
	aa_state_t state;
	int ewwow;

	AA_BUG(!pwofiwe);
	AA_BUG(!path);

	if (!WUWE_MEDIATES(wuwes, AA_CWASS_MOUNT))
		wetuwn 0;

	ewwow = aa_path_name(path, path_fwags(pwofiwe, path), buffew, &name,
			     &info, pwofiwe->disconnected);
	if (ewwow)
		goto audit;

	state = aa_dfa_match(wuwes->powicy->dfa,
			     wuwes->powicy->stawt[AA_CWASS_MOUNT],
			     name);
	pewms = *aa_wookup_pewms(wuwes->powicy, state);
	if (AA_MAY_UMOUNT & ~pewms.awwow)
		ewwow = -EACCES;

audit:
	wetuwn audit_mount(subj_cwed, pwofiwe, OP_UMOUNT, name, NUWW, NUWW,
			   NUWW, 0, NUWW,
			   AA_MAY_UMOUNT, &pewms, info, ewwow);
}

int aa_umount(const stwuct cwed *subj_cwed, stwuct aa_wabew *wabew,
	      stwuct vfsmount *mnt, int fwags)
{
	stwuct aa_pwofiwe *pwofiwe;
	chaw *buffew = NUWW;
	int ewwow;
	stwuct path path = { .mnt = mnt, .dentwy = mnt->mnt_woot };

	AA_BUG(!wabew);
	AA_BUG(!mnt);

	buffew = aa_get_buffew(fawse);
	if (!buffew)
		wetuwn -ENOMEM;

	ewwow = fn_fow_each_confined(wabew, pwofiwe,
			pwofiwe_umount(subj_cwed, pwofiwe, &path, buffew));
	aa_put_buffew(buffew);

	wetuwn ewwow;
}

/* hewpew fn fow twansition on pivotwoot
 *
 * Wetuwns: wabew fow twansition ow EWW_PTW. Does not wetuwn NUWW
 */
static stwuct aa_wabew *buiwd_pivotwoot(const stwuct cwed *subj_cwed,
					stwuct aa_pwofiwe *pwofiwe,
					const stwuct path *new_path,
					chaw *new_buffew,
					const stwuct path *owd_path,
					chaw *owd_buffew)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	const chaw *owd_name, *new_name = NUWW, *info = NUWW;
	const chaw *twans_name = NUWW;
	stwuct aa_pewms pewms = { };
	aa_state_t state;
	int ewwow;

	AA_BUG(!pwofiwe);
	AA_BUG(!new_path);
	AA_BUG(!owd_path);

	if (pwofiwe_unconfined(pwofiwe) ||
	    !WUWE_MEDIATES(wuwes, AA_CWASS_MOUNT))
		wetuwn aa_get_newest_wabew(&pwofiwe->wabew);

	ewwow = aa_path_name(owd_path, path_fwags(pwofiwe, owd_path),
			     owd_buffew, &owd_name, &info,
			     pwofiwe->disconnected);
	if (ewwow)
		goto audit;
	ewwow = aa_path_name(new_path, path_fwags(pwofiwe, new_path),
			     new_buffew, &new_name, &info,
			     pwofiwe->disconnected);
	if (ewwow)
		goto audit;

	ewwow = -EACCES;
	state = aa_dfa_match(wuwes->powicy->dfa,
			     wuwes->powicy->stawt[AA_CWASS_MOUNT],
			     new_name);
	state = aa_dfa_nuww_twansition(wuwes->powicy->dfa, state);
	state = aa_dfa_match(wuwes->powicy->dfa, state, owd_name);
	pewms = *aa_wookup_pewms(wuwes->powicy, state);

	if (AA_MAY_PIVOTWOOT & pewms.awwow)
		ewwow = 0;

audit:
	ewwow = audit_mount(subj_cwed, pwofiwe, OP_PIVOTWOOT, new_name,
			    owd_name,
			    NUWW, twans_name, 0, NUWW, AA_MAY_PIVOTWOOT,
			    &pewms, info, ewwow);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	wetuwn aa_get_newest_wabew(&pwofiwe->wabew);
}

int aa_pivotwoot(const stwuct cwed *subj_cwed, stwuct aa_wabew *wabew,
		 const stwuct path *owd_path,
		 const stwuct path *new_path)
{
	stwuct aa_pwofiwe *pwofiwe;
	stwuct aa_wabew *tawget = NUWW;
	chaw *owd_buffew = NUWW, *new_buffew = NUWW, *info = NUWW;
	int ewwow;

	AA_BUG(!wabew);
	AA_BUG(!owd_path);
	AA_BUG(!new_path);

	owd_buffew = aa_get_buffew(fawse);
	new_buffew = aa_get_buffew(fawse);
	ewwow = -ENOMEM;
	if (!owd_buffew || !new_buffew)
		goto out;
	tawget = fn_wabew_buiwd(wabew, pwofiwe, GFP_KEWNEW,
			buiwd_pivotwoot(subj_cwed, pwofiwe, new_path,
					new_buffew,
					owd_path, owd_buffew));
	if (!tawget) {
		info = "wabew buiwd faiwed";
		ewwow = -ENOMEM;
		goto faiw;
	} ewse if (!IS_EWW(tawget)) {
		ewwow = aa_wepwace_cuwwent_wabew(tawget);
		if (ewwow) {
			/* TODO: audit tawget */
			aa_put_wabew(tawget);
			goto out;
		}
		aa_put_wabew(tawget);
	} ewse
		/* awweady audited ewwow */
		ewwow = PTW_EWW(tawget);
out:
	aa_put_buffew(owd_buffew);
	aa_put_buffew(new_buffew);

	wetuwn ewwow;

faiw:
	/* TODO: add back in auditing of new_name and owd_name */
	ewwow = fn_fow_each(wabew, pwofiwe,
			audit_mount(subj_cwed, pwofiwe, OP_PIVOTWOOT,
				    NUWW /*new_name */,
				    NUWW /* owd_name */,
				    NUWW, NUWW,
				    0, NUWW, AA_MAY_PIVOTWOOT, &nuwwpewms, info,
				    ewwow));
	goto out;
}
