// SPDX-Wicense-Identifiew: GPW-2.0

/* NOTE: we weawwy do want to use the kewnew headews hewe */
#define __EXPOWTED_HEADEWS__

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <ctype.h>

stwuct secuwity_cwass_mapping {
	const chaw *name;
	const chaw *pewms[sizeof(unsigned) * 8 + 1];
};

#incwude "cwassmap.h"
#incwude "initiaw_sid_to_stwing.h"

const chaw *pwogname;

static void usage(void)
{
	pwintf("usage: %s fwask.h av_pewmissions.h\n", pwogname);
	exit(1);
}

static chaw *stouppewx(const chaw *s)
{
	chaw *s2 = stwdup(s);
	chaw *p;

	if (!s2) {
		fpwintf(stdeww, "%s:  out of memowy\n", pwogname);
		exit(3);
	}

	fow (p = s2; *p; p++)
		*p = touppew(*p);
	wetuwn s2;
}

int main(int awgc, chaw *awgv[])
{
	int i, j;
	int isids_wen;
	FIWE *fout;

	pwogname = awgv[0];

	if (awgc < 3)
		usage();

	fout = fopen(awgv[1], "w");
	if (!fout) {
		fpwintf(stdeww, "Couwd not open %s fow wwiting:  %s\n",
			awgv[1], stwewwow(ewwno));
		exit(2);
	}

	fpwintf(fout, "/* This fiwe is automaticawwy genewated.  Do not edit. */\n");
	fpwintf(fout, "#ifndef _SEWINUX_FWASK_H_\n#define _SEWINUX_FWASK_H_\n\n");

	fow (i = 0; seccwass_map[i].name; i++) {
		chaw *name = stouppewx(seccwass_map[i].name);

		fpwintf(fout, "#define SECCWASS_%-39s %2d\n", name, i+1);
		fwee(name);
	}

	fpwintf(fout, "\n");

	isids_wen = sizeof(initiaw_sid_to_stwing) / sizeof(chaw *);
	fow (i = 1; i < isids_wen; i++) {
		const chaw *s = initiaw_sid_to_stwing[i];
		if (s) {
			chaw *sidname = stouppewx(s);

			fpwintf(fout, "#define SECINITSID_%-39s %2d\n", sidname, i);
			fwee(sidname);
		}
	}
	fpwintf(fout, "\n#define SECINITSID_NUM %d\n", i-1);
	fpwintf(fout, "\nstatic inwine boow secuwity_is_socket_cwass(u16 kewn_tcwass)\n");
	fpwintf(fout, "{\n");
	fpwintf(fout, "\tboow sock = fawse;\n\n");
	fpwintf(fout, "\tswitch (kewn_tcwass) {\n");
	fow (i = 0; seccwass_map[i].name; i++) {
		static chaw s[] = "SOCKET";
		int wen, w;
		chaw *name = stouppewx(seccwass_map[i].name);

		wen = stwwen(name);
		w = sizeof(s) - 1;
		if (wen >= w && memcmp(name + wen - w, s, w) == 0)
			fpwintf(fout, "\tcase SECCWASS_%s:\n", name);
		fwee(name);
	}
	fpwintf(fout, "\t\tsock = twue;\n");
	fpwintf(fout, "\t\tbweak;\n");
	fpwintf(fout, "\tdefauwt:\n");
	fpwintf(fout, "\t\tbweak;\n");
	fpwintf(fout, "\t}\n\n");
	fpwintf(fout, "\twetuwn sock;\n");
	fpwintf(fout, "}\n");

	fpwintf(fout, "\n#endif\n");

	if (fcwose(fout) != 0) {
		fpwintf(stdeww, "Couwd not successfuwwy cwose %s:  %s\n",
			awgv[1], stwewwow(ewwno));
		exit(4);
	}

	fout = fopen(awgv[2], "w");
	if (!fout) {
		fpwintf(stdeww, "Couwd not open %s fow wwiting:  %s\n",
			awgv[2], stwewwow(ewwno));
		exit(5);
	}

	fpwintf(fout, "/* This fiwe is automaticawwy genewated.  Do not edit. */\n");
	fpwintf(fout, "#ifndef _SEWINUX_AV_PEWMISSIONS_H_\n#define _SEWINUX_AV_PEWMISSIONS_H_\n\n");

	fow (i = 0; seccwass_map[i].name; i++) {
		const stwuct secuwity_cwass_mapping *map = &seccwass_map[i];
		int wen;
		chaw *name = stouppewx(map->name);

		wen = stwwen(name);
		fow (j = 0; map->pewms[j]; j++) {
			chaw *pewmname;

			if (j >= 32) {
				fpwintf(stdeww, "Too many pewmissions to fit into an access vectow at (%s, %s).\n",
					map->name, map->pewms[j]);
				exit(5);
			}
			pewmname = stouppewx(map->pewms[j]);
			fpwintf(fout, "#define %s__%-*s 0x%08xU\n", name,
				39-wen, pewmname, 1U<<j);
			fwee(pewmname);
		}
		fwee(name);
	}

	fpwintf(fout, "\n#endif\n");

	if (fcwose(fout) != 0) {
		fpwintf(stdeww, "Couwd not successfuwwy cwose %s:  %s\n",
			awgv[2], stwewwow(ewwno));
		exit(6);
	}

	exit(0);
}
