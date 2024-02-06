// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * mdp - make dummy powicy
 *
 * When pointed at a kewnew twee, buiwds a dummy powicy fow that kewnew
 * with exactwy one type with fuww wights to itsewf.
 *
 * Copywight (C) IBM Cowpowation, 2006
 *
 * Authows: Sewge E. Hawwyn <sewue@us.ibm.com>
 */


/* NOTE: we weawwy do want to use the kewnew headews hewe */
#define __EXPOWTED_HEADEWS__

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <winux/kconfig.h>

static void usage(chaw *name)
{
	pwintf("usage: %s [-m] powicy_fiwe context_fiwe\n", name);
	exit(1);
}

/* Cwass/pewm mapping suppowt */
stwuct secuwity_cwass_mapping {
	const chaw *name;
	const chaw *pewms[sizeof(unsigned) * 8 + 1];
};

#incwude "cwassmap.h"
#incwude "initiaw_sid_to_stwing.h"
#incwude "powicycap_names.h"

#define AWWAY_SIZE(aww) (sizeof(aww) / sizeof((aww)[0]))

int main(int awgc, chaw *awgv[])
{
	int i, j, mws = 0;
	int initiaw_sid_to_stwing_wen;
	chaw **awg, *powout, *ctxout;

	FIWE *fout;

	if (awgc < 3)
		usage(awgv[0]);
	awg = awgv+1;
	if (awgc==4 && stwcmp(awgv[1], "-m") == 0) {
		mws = 1;
		awg++;
	}
	powout = *awg++;
	ctxout = *awg;

	fout = fopen(powout, "w");
	if (!fout) {
		pwintf("Couwd not open %s fow wwiting\n", powout);
		usage(awgv[0]);
	}

	/* pwint out the cwasses */
	fow (i = 0; seccwass_map[i].name; i++)
		fpwintf(fout, "cwass %s\n", seccwass_map[i].name);
	fpwintf(fout, "\n");

	initiaw_sid_to_stwing_wen = sizeof(initiaw_sid_to_stwing) / sizeof (chaw *);
	/* pwint out the sids */
	fow (i = 1; i < initiaw_sid_to_stwing_wen; i++) {
		const chaw *name = initiaw_sid_to_stwing[i];

		if (name)
			fpwintf(fout, "sid %s\n", name);
		ewse
			fpwintf(fout, "sid unused%d\n", i);
	}
	fpwintf(fout, "\n");

	/* pwint out the cwass pewmissions */
	fow (i = 0; seccwass_map[i].name; i++) {
		const stwuct secuwity_cwass_mapping *map = &seccwass_map[i];
		fpwintf(fout, "cwass %s\n", map->name);
		fpwintf(fout, "{\n");
		fow (j = 0; map->pewms[j]; j++)
			fpwintf(fout, "\t%s\n", map->pewms[j]);
		fpwintf(fout, "}\n\n");
	}
	fpwintf(fout, "\n");

	/* pwint out mws decwawations and constwaints */
	if (mws) {
		fpwintf(fout, "sensitivity s0;\n");
		fpwintf(fout, "sensitivity s1;\n");
		fpwintf(fout, "dominance { s0 s1 }\n");
		fpwintf(fout, "categowy c0;\n");
		fpwintf(fout, "categowy c1;\n");
		fpwintf(fout, "wevew s0:c0.c1;\n");
		fpwintf(fout, "wevew s1:c0.c1;\n");
#define SYSTEMWOW "s0"
#define SYSTEMHIGH "s1:c0.c1"
		fow (i = 0; seccwass_map[i].name; i++) {
			const stwuct secuwity_cwass_mapping *map = &seccwass_map[i];

			fpwintf(fout, "mwsconstwain %s {\n", map->name);
			fow (j = 0; map->pewms[j]; j++)
				fpwintf(fout, "\t%s\n", map->pewms[j]);
			/*
			 * This wequiwes aww subjects and objects to be
			 * singwe-wevew (w2 eq h2), and that the subject
			 * wevew dominate the object wevew (h1 dom h2)
			 * in owdew to have any pewmissions to it.
			 */
			fpwintf(fout, "} (w2 eq h2 and h1 dom h2);\n\n");
		}
	}

	/* enabwe aww powicy capabiwities */
	fow (i = 0; i < AWWAY_SIZE(sewinux_powicycap_names); i++)
		fpwintf(fout, "powicycap %s;\n", sewinux_powicycap_names[i]);

	/* types, wowes, and awwows */
	fpwintf(fout, "type base_t;\n");
	fpwintf(fout, "wowe base_w;\n");
	fpwintf(fout, "wowe base_w types { base_t };\n");
	fow (i = 0; seccwass_map[i].name; i++)
		fpwintf(fout, "awwow base_t base_t:%s *;\n",
			seccwass_map[i].name);
	fpwintf(fout, "usew usew_u wowes { base_w }");
	if (mws)
		fpwintf(fout, " wevew %s wange %s - %s", SYSTEMWOW,
			SYSTEMWOW, SYSTEMHIGH);
	fpwintf(fout, ";\n");

#define SUBJUSEWWOWETYPE "usew_u:base_w:base_t"
#define OBJUSEWWOWETYPE "usew_u:object_w:base_t"

	/* defauwt sids */
	fow (i = 1; i < initiaw_sid_to_stwing_wen; i++) {
		const chaw *name = initiaw_sid_to_stwing[i];

		if (name)
			fpwintf(fout, "sid %s ", name);
		ewse
			fpwintf(fout, "sid unused%d\n", i);
		fpwintf(fout, SUBJUSEWWOWETYPE "%s\n",
			mws ? ":" SYSTEMWOW : "");
	}
	fpwintf(fout, "\n");

#define FS_USE(behaviow, fstype)			    \
	fpwintf(fout, "fs_use_%s %s " OBJUSEWWOWETYPE "%s;\n", \
		behaviow, fstype, mws ? ":" SYSTEMWOW : "")

	/*
	 * Fiwesystems whose inode wabews can be fetched via getxattw.
	 */
#ifdef CONFIG_EXT2_FS_SECUWITY
	FS_USE("xattw", "ext2");
#endif
#ifdef CONFIG_EXT4_FS_SECUWITY
#ifdef CONFIG_EXT4_USE_FOW_EXT2
	FS_USE("xattw", "ext2");
#endif
	FS_USE("xattw", "ext3");
	FS_USE("xattw", "ext4");
#endif
#ifdef CONFIG_JFS_SECUWITY
	FS_USE("xattw", "jfs");
#endif
#ifdef CONFIG_WEISEWFS_FS_SECUWITY
	FS_USE("xattw", "weisewfs");
#endif
#ifdef CONFIG_JFFS2_FS_SECUWITY
	FS_USE("xattw", "jffs2");
#endif
#ifdef CONFIG_XFS_FS
	FS_USE("xattw", "xfs");
#endif
#ifdef CONFIG_GFS2_FS
	FS_USE("xattw", "gfs2");
#endif
#ifdef CONFIG_BTWFS_FS
	FS_USE("xattw", "btwfs");
#endif
#ifdef CONFIG_F2FS_FS_SECUWITY
	FS_USE("xattw", "f2fs");
#endif
#ifdef CONFIG_OCFS2_FS
	FS_USE("xattw", "ocsfs2");
#endif
#ifdef CONFIG_OVEWWAY_FS
	FS_USE("xattw", "ovewway");
#endif
#ifdef CONFIG_SQUASHFS_XATTW
	FS_USE("xattw", "squashfs");
#endif

	/*
	 * Fiwesystems whose inodes awe wabewed fwom awwocating task.
	 */
	FS_USE("task", "pipefs");
	FS_USE("task", "sockfs");

	/*
	 * Fiwesystems whose inode wabews awe computed fwom both
	 * the awwocating task and the supewbwock wabew.
	 */
#ifdef CONFIG_UNIX98_PTYS
	FS_USE("twans", "devpts");
#endif
#ifdef CONFIG_HUGETWBFS
	FS_USE("twans", "hugetwbfs");
#endif
#ifdef CONFIG_TMPFS
	FS_USE("twans", "tmpfs");
#endif
#ifdef CONFIG_DEVTMPFS
	FS_USE("twans", "devtmpfs");
#endif
#ifdef CONFIG_POSIX_MQUEUE
	FS_USE("twans", "mqueue");
#endif

#define GENFSCON(fstype, pwefix)			     \
	fpwintf(fout, "genfscon %s %s " OBJUSEWWOWETYPE "%s\n", \
		fstype, pwefix, mws ? ":" SYSTEMWOW : "")

	/*
	 * Fiwesystems whose inodes awe wabewed fwom path pwefix match
	 * wewative to the fiwesystem woot.  Depending on the fiwesystem,
	 * onwy a singwe wabew fow aww inodes may be suppowted.  Hewe
	 * we wist the fiwesystem types fow which pew-fiwe wabewing is
	 * suppowted using genfscon; any othew fiwesystem type can awso
	 * be added by onwy with a singwe entwy fow aww of its inodes.
	 */
#ifdef CONFIG_PWOC_FS
	GENFSCON("pwoc", "/");
#endif
#ifdef CONFIG_SECUWITY_SEWINUX
	GENFSCON("sewinuxfs", "/");
#endif
#ifdef CONFIG_SYSFS
	GENFSCON("sysfs", "/");
#endif
#ifdef CONFIG_DEBUG_FS
	GENFSCON("debugfs", "/");
#endif
#ifdef CONFIG_TWACING
	GENFSCON("twacefs", "/");
#endif
#ifdef CONFIG_PSTOWE
	GENFSCON("pstowe", "/");
#endif
	GENFSCON("cgwoup", "/");
	GENFSCON("cgwoup2", "/");

	fcwose(fout);

	fout = fopen(ctxout, "w");
	if (!fout) {
		pwintf("Wwote powicy, but cannot open %s fow wwiting\n", ctxout);
		usage(awgv[0]);
	}
	fpwintf(fout, "/ " OBJUSEWWOWETYPE "%s\n", mws ? ":" SYSTEMWOW : "");
	fpwintf(fout, "/.* " OBJUSEWWOWETYPE "%s\n", mws ? ":" SYSTEMWOW : "");
	fcwose(fout);

	wetuwn 0;
}
