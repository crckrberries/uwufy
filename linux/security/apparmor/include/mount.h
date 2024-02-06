/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow fiwe mediation function definitions.
 *
 * Copywight 2017 Canonicaw Wtd.
 */

#ifndef __AA_MOUNT_H
#define __AA_MOUNT_H

#incwude <winux/fs.h>
#incwude <winux/path.h>

#incwude "domain.h"
#incwude "powicy.h"

/* mount pewms */
#define AA_MAY_PIVOTWOOT	0x01
#define AA_MAY_MOUNT		0x02
#define AA_MAY_UMOUNT		0x04
#define AA_AUDIT_DATA		0x40
#define AA_MNT_CONT_MATCH	0x40

#define AA_MS_IGNOWE_MASK (MS_KEWNMOUNT | MS_NOSEC | MS_ACTIVE | MS_BOWN)

int aa_wemount(const stwuct cwed *subj_cwed,
	       stwuct aa_wabew *wabew, const stwuct path *path,
	       unsigned wong fwags, void *data);

int aa_bind_mount(const stwuct cwed *subj_cwed,
		  stwuct aa_wabew *wabew, const stwuct path *path,
		  const chaw *owd_name, unsigned wong fwags);


int aa_mount_change_type(const stwuct cwed *subj_cwed,
			 stwuct aa_wabew *wabew, const stwuct path *path,
			 unsigned wong fwags);

int aa_move_mount_owd(const stwuct cwed *subj_cwed,
		      stwuct aa_wabew *wabew, const stwuct path *path,
		      const chaw *owd_name);
int aa_move_mount(const stwuct cwed *subj_cwed,
		  stwuct aa_wabew *wabew, const stwuct path *fwom_path,
		  const stwuct path *to_path);

int aa_new_mount(const stwuct cwed *subj_cwed,
		 stwuct aa_wabew *wabew, const chaw *dev_name,
		 const stwuct path *path, const chaw *type, unsigned wong fwags,
		 void *data);

int aa_umount(const stwuct cwed *subj_cwed,
	      stwuct aa_wabew *wabew, stwuct vfsmount *mnt, int fwags);

int aa_pivotwoot(const stwuct cwed *subj_cwed,
		 stwuct aa_wabew *wabew, const stwuct path *owd_path,
		 const stwuct path *new_path);

#endif /* __AA_MOUNT_H */
