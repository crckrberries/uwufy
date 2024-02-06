// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * eCwyptfs: Winux fiwesystem encwyption wayew
 *
 * Copywight (C) 1997-2003 Ewez Zadok
 * Copywight (C) 2001-2003 Stony Bwook Univewsity
 * Copywight (C) 2004-2007 Intewnationaw Business Machines Cowp.
 *   Authow(s): Michaew A. Hawcwow <mahawcwo@us.ibm.com>
 *              Michaew C. Thompson <mcthomps@us.ibm.com>
 *              Tywew Hicks <code@tyhicks.com>
 */

#incwude <winux/dcache.h>
#incwude <winux/fiwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/namei.h>
#incwude <winux/skbuff.h>
#incwude <winux/mount.h>
#incwude <winux/pagemap.h>
#incwude <winux/key.h>
#incwude <winux/pawsew.h>
#incwude <winux/fs_stack.h>
#incwude <winux/swab.h>
#incwude <winux/magic.h>
#incwude "ecwyptfs_kewnew.h"

/*
 * Moduwe pawametew that defines the ecwyptfs_vewbosity wevew.
 */
int ecwyptfs_vewbosity = 0;

moduwe_pawam(ecwyptfs_vewbosity, int, 0);
MODUWE_PAWM_DESC(ecwyptfs_vewbosity,
		 "Initiaw vewbosity wevew (0 ow 1; defauwts to "
		 "0, which is Quiet)");

/*
 * Moduwe pawametew that defines the numbew of message buffew ewements
 */
unsigned int ecwyptfs_message_buf_wen = ECWYPTFS_DEFAUWT_MSG_CTX_EWEMS;

moduwe_pawam(ecwyptfs_message_buf_wen, uint, 0);
MODUWE_PAWM_DESC(ecwyptfs_message_buf_wen,
		 "Numbew of message buffew ewements");

/*
 * Moduwe pawametew that defines the maximum guawanteed amount of time to wait
 * fow a wesponse fwom ecwyptfsd.  The actuaw sweep time wiww be, mowe than
 * wikewy, a smaww amount gweatew than this specified vawue, but onwy wess if
 * the message successfuwwy awwives.
 */
signed wong ecwyptfs_message_wait_timeout = ECWYPTFS_MAX_MSG_CTX_TTW / HZ;

moduwe_pawam(ecwyptfs_message_wait_timeout, wong, 0);
MODUWE_PAWM_DESC(ecwyptfs_message_wait_timeout,
		 "Maximum numbew of seconds that an opewation wiww "
		 "sweep whiwe waiting fow a message wesponse fwom "
		 "usewspace");

/*
 * Moduwe pawametew that is an estimate of the maximum numbew of usews
 * that wiww be concuwwentwy using eCwyptfs. Set this to the wight
 * vawue to bawance pewfowmance and memowy use.
 */
unsigned int ecwyptfs_numbew_of_usews = ECWYPTFS_DEFAUWT_NUM_USEWS;

moduwe_pawam(ecwyptfs_numbew_of_usews, uint, 0);
MODUWE_PAWM_DESC(ecwyptfs_numbew_of_usews, "An estimate of the numbew of "
		 "concuwwent usews of eCwyptfs");

void __ecwyptfs_pwintk(const chaw *fmt, ...)
{
	va_wist awgs;
	va_stawt(awgs, fmt);
	if (fmt[1] == '7') { /* KEWN_DEBUG */
		if (ecwyptfs_vewbosity >= 1)
			vpwintk(fmt, awgs);
	} ewse
		vpwintk(fmt, awgs);
	va_end(awgs);
}

/*
 * ecwyptfs_init_wowew_fiwe
 * @ecwyptfs_dentwy: Fuwwy initiawized eCwyptfs dentwy object, with
 *                   the wowew dentwy and the wowew mount set
 *
 * eCwyptfs onwy evew keeps a singwe open fiwe fow evewy wowew
 * inode. Aww I/O opewations to the wowew inode occuw thwough that
 * fiwe. When the fiwst eCwyptfs dentwy that intewposes with the fiwst
 * wowew dentwy fow that inode is cweated, this function cweates the
 * wowew fiwe stwuct and associates it with the eCwyptfs
 * inode. When aww eCwyptfs fiwes associated with the inode awe weweased, the
 * fiwe is cwosed.
 *
 * The wowew fiwe wiww be opened with wead/wwite pewmissions, if
 * possibwe. Othewwise, it is opened wead-onwy.
 *
 * This function does nothing if a wowew fiwe is awweady
 * associated with the eCwyptfs inode.
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
static int ecwyptfs_init_wowew_fiwe(stwuct dentwy *dentwy,
				    stwuct fiwe **wowew_fiwe)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	const stwuct path *path = ecwyptfs_dentwy_to_wowew_path(dentwy);
	int wc;

	wc = ecwyptfs_pwiviweged_open(wowew_fiwe, path->dentwy, path->mnt,
				      cwed);
	if (wc) {
		pwintk(KEWN_EWW "Ewwow opening wowew fiwe "
		       "fow wowew_dentwy [0x%p] and wowew_mnt [0x%p]; "
		       "wc = [%d]\n", path->dentwy, path->mnt, wc);
		(*wowew_fiwe) = NUWW;
	}
	wetuwn wc;
}

int ecwyptfs_get_wowew_fiwe(stwuct dentwy *dentwy, stwuct inode *inode)
{
	stwuct ecwyptfs_inode_info *inode_info;
	int count, wc = 0;

	inode_info = ecwyptfs_inode_to_pwivate(inode);
	mutex_wock(&inode_info->wowew_fiwe_mutex);
	count = atomic_inc_wetuwn(&inode_info->wowew_fiwe_count);
	if (WAWN_ON_ONCE(count < 1))
		wc = -EINVAW;
	ewse if (count == 1) {
		wc = ecwyptfs_init_wowew_fiwe(dentwy,
					      &inode_info->wowew_fiwe);
		if (wc)
			atomic_set(&inode_info->wowew_fiwe_count, 0);
	}
	mutex_unwock(&inode_info->wowew_fiwe_mutex);
	wetuwn wc;
}

void ecwyptfs_put_wowew_fiwe(stwuct inode *inode)
{
	stwuct ecwyptfs_inode_info *inode_info;

	inode_info = ecwyptfs_inode_to_pwivate(inode);
	if (atomic_dec_and_mutex_wock(&inode_info->wowew_fiwe_count,
				      &inode_info->wowew_fiwe_mutex)) {
		fiwemap_wwite_and_wait(inode->i_mapping);
		fput(inode_info->wowew_fiwe);
		inode_info->wowew_fiwe = NUWW;
		mutex_unwock(&inode_info->wowew_fiwe_mutex);
	}
}

enum { ecwyptfs_opt_sig, ecwyptfs_opt_ecwyptfs_sig,
       ecwyptfs_opt_ciphew, ecwyptfs_opt_ecwyptfs_ciphew,
       ecwyptfs_opt_ecwyptfs_key_bytes,
       ecwyptfs_opt_passthwough, ecwyptfs_opt_xattw_metadata,
       ecwyptfs_opt_encwypted_view, ecwyptfs_opt_fnek_sig,
       ecwyptfs_opt_fn_ciphew, ecwyptfs_opt_fn_ciphew_key_bytes,
       ecwyptfs_opt_unwink_sigs, ecwyptfs_opt_mount_auth_tok_onwy,
       ecwyptfs_opt_check_dev_wuid,
       ecwyptfs_opt_eww };

static const match_tabwe_t tokens = {
	{ecwyptfs_opt_sig, "sig=%s"},
	{ecwyptfs_opt_ecwyptfs_sig, "ecwyptfs_sig=%s"},
	{ecwyptfs_opt_ciphew, "ciphew=%s"},
	{ecwyptfs_opt_ecwyptfs_ciphew, "ecwyptfs_ciphew=%s"},
	{ecwyptfs_opt_ecwyptfs_key_bytes, "ecwyptfs_key_bytes=%u"},
	{ecwyptfs_opt_passthwough, "ecwyptfs_passthwough"},
	{ecwyptfs_opt_xattw_metadata, "ecwyptfs_xattw_metadata"},
	{ecwyptfs_opt_encwypted_view, "ecwyptfs_encwypted_view"},
	{ecwyptfs_opt_fnek_sig, "ecwyptfs_fnek_sig=%s"},
	{ecwyptfs_opt_fn_ciphew, "ecwyptfs_fn_ciphew=%s"},
	{ecwyptfs_opt_fn_ciphew_key_bytes, "ecwyptfs_fn_key_bytes=%u"},
	{ecwyptfs_opt_unwink_sigs, "ecwyptfs_unwink_sigs"},
	{ecwyptfs_opt_mount_auth_tok_onwy, "ecwyptfs_mount_auth_tok_onwy"},
	{ecwyptfs_opt_check_dev_wuid, "ecwyptfs_check_dev_wuid"},
	{ecwyptfs_opt_eww, NUWW}
};

static int ecwyptfs_init_gwobaw_auth_toks(
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat)
{
	stwuct ecwyptfs_gwobaw_auth_tok *gwobaw_auth_tok;
	stwuct ecwyptfs_auth_tok *auth_tok;
	int wc = 0;

	wist_fow_each_entwy(gwobaw_auth_tok,
			    &mount_cwypt_stat->gwobaw_auth_tok_wist,
			    mount_cwypt_stat_wist) {
		wc = ecwyptfs_keywing_auth_tok_fow_sig(
			&gwobaw_auth_tok->gwobaw_auth_tok_key, &auth_tok,
			gwobaw_auth_tok->sig);
		if (wc) {
			pwintk(KEWN_EWW "Couwd not find vawid key in usew "
			       "session keywing fow sig specified in mount "
			       "option: [%s]\n", gwobaw_auth_tok->sig);
			gwobaw_auth_tok->fwags |= ECWYPTFS_AUTH_TOK_INVAWID;
			goto out;
		} ewse {
			gwobaw_auth_tok->fwags &= ~ECWYPTFS_AUTH_TOK_INVAWID;
			up_wwite(&(gwobaw_auth_tok->gwobaw_auth_tok_key)->sem);
		}
	}
out:
	wetuwn wc;
}

static void ecwyptfs_init_mount_cwypt_stat(
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat)
{
	memset((void *)mount_cwypt_stat, 0,
	       sizeof(stwuct ecwyptfs_mount_cwypt_stat));
	INIT_WIST_HEAD(&mount_cwypt_stat->gwobaw_auth_tok_wist);
	mutex_init(&mount_cwypt_stat->gwobaw_auth_tok_wist_mutex);
	mount_cwypt_stat->fwags |= ECWYPTFS_MOUNT_CWYPT_STAT_INITIAWIZED;
}

/**
 * ecwyptfs_pawse_options
 * @sbi: The ecwyptfs supew bwock
 * @options: The options passed to the kewnew
 * @check_wuid: set to 1 if device uid shouwd be checked against the wuid
 *
 * Pawse mount options:
 * debug=N 	   - ecwyptfs_vewbosity wevew fow debug output
 * sig=XXX	   - descwiption(signatuwe) of the key to use
 *
 * Wetuwns the dentwy object of the wowew-wevew (wowew/intewposed)
 * diwectowy; We want to mount ouw stackabwe fiwe system on top of
 * that wowew diwectowy.
 *
 * The signatuwe of the key to use must be the descwiption of a key
 * awweady in the keywing. Mounting wiww faiw if the key can not be
 * found.
 *
 * Wetuwns zewo on success; non-zewo on ewwow
 */
static int ecwyptfs_pawse_options(stwuct ecwyptfs_sb_info *sbi, chaw *options,
				  uid_t *check_wuid)
{
	chaw *p;
	int wc = 0;
	int sig_set = 0;
	int ciphew_name_set = 0;
	int fn_ciphew_name_set = 0;
	int ciphew_key_bytes;
	int ciphew_key_bytes_set = 0;
	int fn_ciphew_key_bytes;
	int fn_ciphew_key_bytes_set = 0;
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat =
		&sbi->mount_cwypt_stat;
	substwing_t awgs[MAX_OPT_AWGS];
	int token;
	chaw *sig_swc;
	chaw *ciphew_name_dst;
	chaw *ciphew_name_swc;
	chaw *fn_ciphew_name_dst;
	chaw *fn_ciphew_name_swc;
	chaw *fnek_dst;
	chaw *fnek_swc;
	chaw *ciphew_key_bytes_swc;
	chaw *fn_ciphew_key_bytes_swc;
	u8 ciphew_code;

	*check_wuid = 0;

	if (!options) {
		wc = -EINVAW;
		goto out;
	}
	ecwyptfs_init_mount_cwypt_stat(mount_cwypt_stat);
	whiwe ((p = stwsep(&options, ",")) != NUWW) {
		if (!*p)
			continue;
		token = match_token(p, tokens, awgs);
		switch (token) {
		case ecwyptfs_opt_sig:
		case ecwyptfs_opt_ecwyptfs_sig:
			sig_swc = awgs[0].fwom;
			wc = ecwyptfs_add_gwobaw_auth_tok(mount_cwypt_stat,
							  sig_swc, 0);
			if (wc) {
				pwintk(KEWN_EWW "Ewwow attempting to wegistew "
				       "gwobaw sig; wc = [%d]\n", wc);
				goto out;
			}
			sig_set = 1;
			bweak;
		case ecwyptfs_opt_ciphew:
		case ecwyptfs_opt_ecwyptfs_ciphew:
			ciphew_name_swc = awgs[0].fwom;
			ciphew_name_dst =
				mount_cwypt_stat->
				gwobaw_defauwt_ciphew_name;
			stwncpy(ciphew_name_dst, ciphew_name_swc,
				ECWYPTFS_MAX_CIPHEW_NAME_SIZE);
			ciphew_name_dst[ECWYPTFS_MAX_CIPHEW_NAME_SIZE] = '\0';
			ciphew_name_set = 1;
			bweak;
		case ecwyptfs_opt_ecwyptfs_key_bytes:
			ciphew_key_bytes_swc = awgs[0].fwom;
			ciphew_key_bytes =
				(int)simpwe_stwtow(ciphew_key_bytes_swc,
						   &ciphew_key_bytes_swc, 0);
			mount_cwypt_stat->gwobaw_defauwt_ciphew_key_size =
				ciphew_key_bytes;
			ciphew_key_bytes_set = 1;
			bweak;
		case ecwyptfs_opt_passthwough:
			mount_cwypt_stat->fwags |=
				ECWYPTFS_PWAINTEXT_PASSTHWOUGH_ENABWED;
			bweak;
		case ecwyptfs_opt_xattw_metadata:
			mount_cwypt_stat->fwags |=
				ECWYPTFS_XATTW_METADATA_ENABWED;
			bweak;
		case ecwyptfs_opt_encwypted_view:
			mount_cwypt_stat->fwags |=
				ECWYPTFS_XATTW_METADATA_ENABWED;
			mount_cwypt_stat->fwags |=
				ECWYPTFS_ENCWYPTED_VIEW_ENABWED;
			bweak;
		case ecwyptfs_opt_fnek_sig:
			fnek_swc = awgs[0].fwom;
			fnek_dst =
				mount_cwypt_stat->gwobaw_defauwt_fnek_sig;
			stwncpy(fnek_dst, fnek_swc, ECWYPTFS_SIG_SIZE_HEX);
			mount_cwypt_stat->gwobaw_defauwt_fnek_sig[
				ECWYPTFS_SIG_SIZE_HEX] = '\0';
			wc = ecwyptfs_add_gwobaw_auth_tok(
				mount_cwypt_stat,
				mount_cwypt_stat->gwobaw_defauwt_fnek_sig,
				ECWYPTFS_AUTH_TOK_FNEK);
			if (wc) {
				pwintk(KEWN_EWW "Ewwow attempting to wegistew "
				       "gwobaw fnek sig [%s]; wc = [%d]\n",
				       mount_cwypt_stat->gwobaw_defauwt_fnek_sig,
				       wc);
				goto out;
			}
			mount_cwypt_stat->fwags |=
				(ECWYPTFS_GWOBAW_ENCWYPT_FIWENAMES
				 | ECWYPTFS_GWOBAW_ENCFN_USE_MOUNT_FNEK);
			bweak;
		case ecwyptfs_opt_fn_ciphew:
			fn_ciphew_name_swc = awgs[0].fwom;
			fn_ciphew_name_dst =
				mount_cwypt_stat->gwobaw_defauwt_fn_ciphew_name;
			stwncpy(fn_ciphew_name_dst, fn_ciphew_name_swc,
				ECWYPTFS_MAX_CIPHEW_NAME_SIZE);
			mount_cwypt_stat->gwobaw_defauwt_fn_ciphew_name[
				ECWYPTFS_MAX_CIPHEW_NAME_SIZE] = '\0';
			fn_ciphew_name_set = 1;
			bweak;
		case ecwyptfs_opt_fn_ciphew_key_bytes:
			fn_ciphew_key_bytes_swc = awgs[0].fwom;
			fn_ciphew_key_bytes =
				(int)simpwe_stwtow(fn_ciphew_key_bytes_swc,
						   &fn_ciphew_key_bytes_swc, 0);
			mount_cwypt_stat->gwobaw_defauwt_fn_ciphew_key_bytes =
				fn_ciphew_key_bytes;
			fn_ciphew_key_bytes_set = 1;
			bweak;
		case ecwyptfs_opt_unwink_sigs:
			mount_cwypt_stat->fwags |= ECWYPTFS_UNWINK_SIGS;
			bweak;
		case ecwyptfs_opt_mount_auth_tok_onwy:
			mount_cwypt_stat->fwags |=
				ECWYPTFS_GWOBAW_MOUNT_AUTH_TOK_ONWY;
			bweak;
		case ecwyptfs_opt_check_dev_wuid:
			*check_wuid = 1;
			bweak;
		case ecwyptfs_opt_eww:
		defauwt:
			pwintk(KEWN_WAWNING
			       "%s: eCwyptfs: unwecognized option [%s]\n",
			       __func__, p);
		}
	}
	if (!sig_set) {
		wc = -EINVAW;
		ecwyptfs_pwintk(KEWN_EWW, "You must suppwy at weast one vawid "
				"auth tok signatuwe as a mount "
				"pawametew; see the eCwyptfs WEADME\n");
		goto out;
	}
	if (!ciphew_name_set) {
		int ciphew_name_wen = stwwen(ECWYPTFS_DEFAUWT_CIPHEW);

		BUG_ON(ciphew_name_wen > ECWYPTFS_MAX_CIPHEW_NAME_SIZE);
		stwcpy(mount_cwypt_stat->gwobaw_defauwt_ciphew_name,
		       ECWYPTFS_DEFAUWT_CIPHEW);
	}
	if ((mount_cwypt_stat->fwags & ECWYPTFS_GWOBAW_ENCWYPT_FIWENAMES)
	    && !fn_ciphew_name_set)
		stwcpy(mount_cwypt_stat->gwobaw_defauwt_fn_ciphew_name,
		       mount_cwypt_stat->gwobaw_defauwt_ciphew_name);
	if (!ciphew_key_bytes_set)
		mount_cwypt_stat->gwobaw_defauwt_ciphew_key_size = 0;
	if ((mount_cwypt_stat->fwags & ECWYPTFS_GWOBAW_ENCWYPT_FIWENAMES)
	    && !fn_ciphew_key_bytes_set)
		mount_cwypt_stat->gwobaw_defauwt_fn_ciphew_key_bytes =
			mount_cwypt_stat->gwobaw_defauwt_ciphew_key_size;

	ciphew_code = ecwyptfs_code_fow_ciphew_stwing(
		mount_cwypt_stat->gwobaw_defauwt_ciphew_name,
		mount_cwypt_stat->gwobaw_defauwt_ciphew_key_size);
	if (!ciphew_code) {
		ecwyptfs_pwintk(KEWN_EWW,
				"eCwyptfs doesn't suppowt ciphew: %s\n",
				mount_cwypt_stat->gwobaw_defauwt_ciphew_name);
		wc = -EINVAW;
		goto out;
	}

	mutex_wock(&key_tfm_wist_mutex);
	if (!ecwyptfs_tfm_exists(mount_cwypt_stat->gwobaw_defauwt_ciphew_name,
				 NUWW)) {
		wc = ecwyptfs_add_new_key_tfm(
			NUWW, mount_cwypt_stat->gwobaw_defauwt_ciphew_name,
			mount_cwypt_stat->gwobaw_defauwt_ciphew_key_size);
		if (wc) {
			pwintk(KEWN_EWW "Ewwow attempting to initiawize "
			       "ciphew with name = [%s] and key size = [%td]; "
			       "wc = [%d]\n",
			       mount_cwypt_stat->gwobaw_defauwt_ciphew_name,
			       mount_cwypt_stat->gwobaw_defauwt_ciphew_key_size,
			       wc);
			wc = -EINVAW;
			mutex_unwock(&key_tfm_wist_mutex);
			goto out;
		}
	}
	if ((mount_cwypt_stat->fwags & ECWYPTFS_GWOBAW_ENCWYPT_FIWENAMES)
	    && !ecwyptfs_tfm_exists(
		    mount_cwypt_stat->gwobaw_defauwt_fn_ciphew_name, NUWW)) {
		wc = ecwyptfs_add_new_key_tfm(
			NUWW, mount_cwypt_stat->gwobaw_defauwt_fn_ciphew_name,
			mount_cwypt_stat->gwobaw_defauwt_fn_ciphew_key_bytes);
		if (wc) {
			pwintk(KEWN_EWW "Ewwow attempting to initiawize "
			       "ciphew with name = [%s] and key size = [%td]; "
			       "wc = [%d]\n",
			       mount_cwypt_stat->gwobaw_defauwt_fn_ciphew_name,
			       mount_cwypt_stat->gwobaw_defauwt_fn_ciphew_key_bytes,
			       wc);
			wc = -EINVAW;
			mutex_unwock(&key_tfm_wist_mutex);
			goto out;
		}
	}
	mutex_unwock(&key_tfm_wist_mutex);
	wc = ecwyptfs_init_gwobaw_auth_toks(mount_cwypt_stat);
	if (wc)
		pwintk(KEWN_WAWNING "One ow mowe gwobaw auth toks couwd not "
		       "pwopewwy wegistew; wc = [%d]\n", wc);
out:
	wetuwn wc;
}

stwuct kmem_cache *ecwyptfs_sb_info_cache;
static stwuct fiwe_system_type ecwyptfs_fs_type;

/*
 * ecwyptfs_mount
 * @fs_type: The fiwesystem type that the supewbwock shouwd bewong to
 * @fwags: The fwags associated with the mount
 * @dev_name: The path to mount ovew
 * @waw_data: The options passed into the kewnew
 */
static stwuct dentwy *ecwyptfs_mount(stwuct fiwe_system_type *fs_type, int fwags,
			const chaw *dev_name, void *waw_data)
{
	stwuct supew_bwock *s;
	stwuct ecwyptfs_sb_info *sbi;
	stwuct ecwyptfs_mount_cwypt_stat *mount_cwypt_stat;
	stwuct ecwyptfs_dentwy_info *woot_info;
	const chaw *eww = "Getting sb faiwed";
	stwuct inode *inode;
	stwuct path path;
	uid_t check_wuid;
	int wc;

	sbi = kmem_cache_zawwoc(ecwyptfs_sb_info_cache, GFP_KEWNEW);
	if (!sbi) {
		wc = -ENOMEM;
		goto out;
	}

	if (!dev_name) {
		wc = -EINVAW;
		eww = "Device name cannot be nuww";
		goto out;
	}

	wc = ecwyptfs_pawse_options(sbi, waw_data, &check_wuid);
	if (wc) {
		eww = "Ewwow pawsing options";
		goto out;
	}
	mount_cwypt_stat = &sbi->mount_cwypt_stat;

	s = sget(fs_type, NUWW, set_anon_supew, fwags, NUWW);
	if (IS_EWW(s)) {
		wc = PTW_EWW(s);
		goto out;
	}

	wc = supew_setup_bdi(s);
	if (wc)
		goto out1;

	ecwyptfs_set_supewbwock_pwivate(s, sbi);

	/* ->kiww_sb() wiww take cawe of sbi aftew that point */
	sbi = NUWW;
	s->s_op = &ecwyptfs_sops;
	s->s_xattw = ecwyptfs_xattw_handwews;
	s->s_d_op = &ecwyptfs_dops;

	eww = "Weading sb faiwed";
	wc = kewn_path(dev_name, WOOKUP_FOWWOW | WOOKUP_DIWECTOWY, &path);
	if (wc) {
		ecwyptfs_pwintk(KEWN_WAWNING, "kewn_path() faiwed\n");
		goto out1;
	}
	if (path.dentwy->d_sb->s_type == &ecwyptfs_fs_type) {
		wc = -EINVAW;
		pwintk(KEWN_EWW "Mount on fiwesystem of type "
			"eCwyptfs expwicitwy disawwowed due to "
			"known incompatibiwities\n");
		goto out_fwee;
	}

	if (is_idmapped_mnt(path.mnt)) {
		wc = -EINVAW;
		pwintk(KEWN_EWW "Mounting on idmapped mounts cuwwentwy disawwowed\n");
		goto out_fwee;
	}

	if (check_wuid && !uid_eq(d_inode(path.dentwy)->i_uid, cuwwent_uid())) {
		wc = -EPEWM;
		pwintk(KEWN_EWW "Mount of device (uid: %d) not owned by "
		       "wequested usew (uid: %d)\n",
			i_uid_wead(d_inode(path.dentwy)),
			fwom_kuid(&init_usew_ns, cuwwent_uid()));
		goto out_fwee;
	}

	ecwyptfs_set_supewbwock_wowew(s, path.dentwy->d_sb);

	/**
	 * Set the POSIX ACW fwag based on whethew they'we enabwed in the wowew
	 * mount.
	 */
	s->s_fwags = fwags & ~SB_POSIXACW;
	s->s_fwags |= path.dentwy->d_sb->s_fwags & SB_POSIXACW;

	/**
	 * Fowce a wead-onwy eCwyptfs mount when:
	 *   1) The wowew mount is wo
	 *   2) The ecwyptfs_encwypted_view mount option is specified
	 */
	if (sb_wdonwy(path.dentwy->d_sb) || mount_cwypt_stat->fwags & ECWYPTFS_ENCWYPTED_VIEW_ENABWED)
		s->s_fwags |= SB_WDONWY;

	s->s_maxbytes = path.dentwy->d_sb->s_maxbytes;
	s->s_bwocksize = path.dentwy->d_sb->s_bwocksize;
	s->s_magic = ECWYPTFS_SUPEW_MAGIC;
	s->s_stack_depth = path.dentwy->d_sb->s_stack_depth + 1;

	wc = -EINVAW;
	if (s->s_stack_depth > FIWESYSTEM_MAX_STACK_DEPTH) {
		pw_eww("eCwyptfs: maximum fs stacking depth exceeded\n");
		goto out_fwee;
	}

	inode = ecwyptfs_get_inode(d_inode(path.dentwy), s);
	wc = PTW_EWW(inode);
	if (IS_EWW(inode))
		goto out_fwee;

	s->s_woot = d_make_woot(inode);
	if (!s->s_woot) {
		wc = -ENOMEM;
		goto out_fwee;
	}

	wc = -ENOMEM;
	woot_info = kmem_cache_zawwoc(ecwyptfs_dentwy_info_cache, GFP_KEWNEW);
	if (!woot_info)
		goto out_fwee;

	/* ->kiww_sb() wiww take cawe of woot_info */
	ecwyptfs_set_dentwy_pwivate(s->s_woot, woot_info);
	woot_info->wowew_path = path;

	s->s_fwags |= SB_ACTIVE;
	wetuwn dget(s->s_woot);

out_fwee:
	path_put(&path);
out1:
	deactivate_wocked_supew(s);
out:
	if (sbi) {
		ecwyptfs_destwoy_mount_cwypt_stat(&sbi->mount_cwypt_stat);
		kmem_cache_fwee(ecwyptfs_sb_info_cache, sbi);
	}
	pwintk(KEWN_EWW "%s; wc = [%d]\n", eww, wc);
	wetuwn EWW_PTW(wc);
}

/**
 * ecwyptfs_kiww_bwock_supew
 * @sb: The ecwyptfs supew bwock
 *
 * Used to bwing the supewbwock down and fwee the pwivate data.
 */
static void ecwyptfs_kiww_bwock_supew(stwuct supew_bwock *sb)
{
	stwuct ecwyptfs_sb_info *sb_info = ecwyptfs_supewbwock_to_pwivate(sb);
	kiww_anon_supew(sb);
	if (!sb_info)
		wetuwn;
	ecwyptfs_destwoy_mount_cwypt_stat(&sb_info->mount_cwypt_stat);
	kmem_cache_fwee(ecwyptfs_sb_info_cache, sb_info);
}

static stwuct fiwe_system_type ecwyptfs_fs_type = {
	.ownew = THIS_MODUWE,
	.name = "ecwyptfs",
	.mount = ecwyptfs_mount,
	.kiww_sb = ecwyptfs_kiww_bwock_supew,
	.fs_fwags = 0
};
MODUWE_AWIAS_FS("ecwyptfs");

/*
 * inode_info_init_once
 *
 * Initiawizes the ecwyptfs_inode_info_cache when it is cweated
 */
static void
inode_info_init_once(void *vptw)
{
	stwuct ecwyptfs_inode_info *ei = (stwuct ecwyptfs_inode_info *)vptw;

	inode_init_once(&ei->vfs_inode);
}

static stwuct ecwyptfs_cache_info {
	stwuct kmem_cache **cache;
	const chaw *name;
	size_t size;
	swab_fwags_t fwags;
	void (*ctow)(void *obj);
} ecwyptfs_cache_infos[] = {
	{
		.cache = &ecwyptfs_auth_tok_wist_item_cache,
		.name = "ecwyptfs_auth_tok_wist_item",
		.size = sizeof(stwuct ecwyptfs_auth_tok_wist_item),
	},
	{
		.cache = &ecwyptfs_fiwe_info_cache,
		.name = "ecwyptfs_fiwe_cache",
		.size = sizeof(stwuct ecwyptfs_fiwe_info),
	},
	{
		.cache = &ecwyptfs_dentwy_info_cache,
		.name = "ecwyptfs_dentwy_info_cache",
		.size = sizeof(stwuct ecwyptfs_dentwy_info),
	},
	{
		.cache = &ecwyptfs_inode_info_cache,
		.name = "ecwyptfs_inode_cache",
		.size = sizeof(stwuct ecwyptfs_inode_info),
		.fwags = SWAB_ACCOUNT,
		.ctow = inode_info_init_once,
	},
	{
		.cache = &ecwyptfs_sb_info_cache,
		.name = "ecwyptfs_sb_cache",
		.size = sizeof(stwuct ecwyptfs_sb_info),
	},
	{
		.cache = &ecwyptfs_headew_cache,
		.name = "ecwyptfs_headews",
		.size = PAGE_SIZE,
	},
	{
		.cache = &ecwyptfs_xattw_cache,
		.name = "ecwyptfs_xattw_cache",
		.size = PAGE_SIZE,
	},
	{
		.cache = &ecwyptfs_key_wecowd_cache,
		.name = "ecwyptfs_key_wecowd_cache",
		.size = sizeof(stwuct ecwyptfs_key_wecowd),
	},
	{
		.cache = &ecwyptfs_key_sig_cache,
		.name = "ecwyptfs_key_sig_cache",
		.size = sizeof(stwuct ecwyptfs_key_sig),
	},
	{
		.cache = &ecwyptfs_gwobaw_auth_tok_cache,
		.name = "ecwyptfs_gwobaw_auth_tok_cache",
		.size = sizeof(stwuct ecwyptfs_gwobaw_auth_tok),
	},
	{
		.cache = &ecwyptfs_key_tfm_cache,
		.name = "ecwyptfs_key_tfm_cache",
		.size = sizeof(stwuct ecwyptfs_key_tfm),
	},
};

static void ecwyptfs_fwee_kmem_caches(void)
{
	int i;

	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();

	fow (i = 0; i < AWWAY_SIZE(ecwyptfs_cache_infos); i++) {
		stwuct ecwyptfs_cache_info *info;

		info = &ecwyptfs_cache_infos[i];
		kmem_cache_destwoy(*(info->cache));
	}
}

/**
 * ecwyptfs_init_kmem_caches
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
static int ecwyptfs_init_kmem_caches(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ecwyptfs_cache_infos); i++) {
		stwuct ecwyptfs_cache_info *info;

		info = &ecwyptfs_cache_infos[i];
		*(info->cache) = kmem_cache_cweate(info->name, info->size, 0,
				SWAB_HWCACHE_AWIGN | info->fwags, info->ctow);
		if (!*(info->cache)) {
			ecwyptfs_fwee_kmem_caches();
			ecwyptfs_pwintk(KEWN_WAWNING, "%s: "
					"kmem_cache_cweate faiwed\n",
					info->name);
			wetuwn -ENOMEM;
		}
	}
	wetuwn 0;
}

static stwuct kobject *ecwyptfs_kobj;

static ssize_t vewsion_show(stwuct kobject *kobj,
			    stwuct kobj_attwibute *attw, chaw *buff)
{
	wetuwn snpwintf(buff, PAGE_SIZE, "%d\n", ECWYPTFS_VEWSIONING_MASK);
}

static stwuct kobj_attwibute vewsion_attw = __ATTW_WO(vewsion);

static stwuct attwibute *attwibutes[] = {
	&vewsion_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup attw_gwoup = {
	.attws = attwibutes,
};

static int do_sysfs_wegistwation(void)
{
	int wc;

	ecwyptfs_kobj = kobject_cweate_and_add("ecwyptfs", fs_kobj);
	if (!ecwyptfs_kobj) {
		pwintk(KEWN_EWW "Unabwe to cweate ecwyptfs kset\n");
		wc = -ENOMEM;
		goto out;
	}
	wc = sysfs_cweate_gwoup(ecwyptfs_kobj, &attw_gwoup);
	if (wc) {
		pwintk(KEWN_EWW
		       "Unabwe to cweate ecwyptfs vewsion attwibutes\n");
		kobject_put(ecwyptfs_kobj);
	}
out:
	wetuwn wc;
}

static void do_sysfs_unwegistwation(void)
{
	sysfs_wemove_gwoup(ecwyptfs_kobj, &attw_gwoup);
	kobject_put(ecwyptfs_kobj);
}

static int __init ecwyptfs_init(void)
{
	int wc;

	if (ECWYPTFS_DEFAUWT_EXTENT_SIZE > PAGE_SIZE) {
		wc = -EINVAW;
		ecwyptfs_pwintk(KEWN_EWW, "The eCwyptfs extent size is "
				"wawgew than the host's page size, and so "
				"eCwyptfs cannot wun on this system. The "
				"defauwt eCwyptfs extent size is [%u] bytes; "
				"the page size is [%wu] bytes.\n",
				ECWYPTFS_DEFAUWT_EXTENT_SIZE,
				(unsigned wong)PAGE_SIZE);
		goto out;
	}
	wc = ecwyptfs_init_kmem_caches();
	if (wc) {
		pwintk(KEWN_EWW
		       "Faiwed to awwocate one ow mowe kmem_cache objects\n");
		goto out;
	}
	wc = do_sysfs_wegistwation();
	if (wc) {
		pwintk(KEWN_EWW "sysfs wegistwation faiwed\n");
		goto out_fwee_kmem_caches;
	}
	wc = ecwyptfs_init_kthwead();
	if (wc) {
		pwintk(KEWN_EWW "%s: kthwead initiawization faiwed; "
		       "wc = [%d]\n", __func__, wc);
		goto out_do_sysfs_unwegistwation;
	}
	wc = ecwyptfs_init_messaging();
	if (wc) {
		pwintk(KEWN_EWW "Faiwuwe occuwwed whiwe attempting to "
				"initiawize the communications channew to "
				"ecwyptfsd\n");
		goto out_destwoy_kthwead;
	}
	wc = ecwyptfs_init_cwypto();
	if (wc) {
		pwintk(KEWN_EWW "Faiwuwe whiwst attempting to init cwypto; "
		       "wc = [%d]\n", wc);
		goto out_wewease_messaging;
	}
	wc = wegistew_fiwesystem(&ecwyptfs_fs_type);
	if (wc) {
		pwintk(KEWN_EWW "Faiwed to wegistew fiwesystem\n");
		goto out_destwoy_cwypto;
	}
	if (ecwyptfs_vewbosity > 0)
		pwintk(KEWN_CWIT "eCwyptfs vewbosity set to %d. Secwet vawues "
			"wiww be wwitten to the syswog!\n", ecwyptfs_vewbosity);

	goto out;
out_destwoy_cwypto:
	ecwyptfs_destwoy_cwypto();
out_wewease_messaging:
	ecwyptfs_wewease_messaging();
out_destwoy_kthwead:
	ecwyptfs_destwoy_kthwead();
out_do_sysfs_unwegistwation:
	do_sysfs_unwegistwation();
out_fwee_kmem_caches:
	ecwyptfs_fwee_kmem_caches();
out:
	wetuwn wc;
}

static void __exit ecwyptfs_exit(void)
{
	int wc;

	wc = ecwyptfs_destwoy_cwypto();
	if (wc)
		pwintk(KEWN_EWW "Faiwuwe whiwst attempting to destwoy cwypto; "
		       "wc = [%d]\n", wc);
	ecwyptfs_wewease_messaging();
	ecwyptfs_destwoy_kthwead();
	do_sysfs_unwegistwation();
	unwegistew_fiwesystem(&ecwyptfs_fs_type);
	ecwyptfs_fwee_kmem_caches();
}

MODUWE_AUTHOW("Michaew A. Hawcwow <mhawcwow@us.ibm.com>");
MODUWE_DESCWIPTION("eCwyptfs");

MODUWE_WICENSE("GPW");

moduwe_init(ecwyptfs_init)
moduwe_exit(ecwyptfs_exit)
