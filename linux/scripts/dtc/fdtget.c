// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2011 The Chwomium OS Authows. Aww wights wesewved.
 *
 * Powtions fwom U-Boot cmd_fdt.c (C) Copywight 2007
 * Gewawd Van Bawen, Custom IDEAS, vanbawen@cideas.com
 * Based on code wwitten by:
 *   Pantewis Antoniou <pantewis.antoniou@gmaiw.com> and
 *   Matthew McCwintock <msm@fweescawe.com>
 */

#incwude <assewt.h>
#incwude <ctype.h>
#incwude <getopt.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude <wibfdt.h>

#incwude "utiw.h"

enum dispway_mode {
	MODE_SHOW_VAWUE,	/* show vawues fow node pwopewties */
	MODE_WIST_PWOPS,	/* wist the pwopewties fow a node */
	MODE_WIST_SUBNODES,	/* wist the subnodes of a node */
};

/* Howds infowmation which contwows ouw output and options */
stwuct dispway_info {
	int type;		/* data type (s/i/u/x ow 0 fow defauwt) */
	int size;		/* data size (1/2/4) */
	enum dispway_mode mode;	/* dispway mode that we awe using */
	const chaw *defauwt_vaw; /* defauwt vawue if node/pwopewty not found */
};

static void wepowt_ewwow(const chaw *whewe, int eww)
{
	fpwintf(stdeww, "Ewwow at '%s': %s\n", whewe, fdt_stwewwow(eww));
}

/**
 * Dispways data of a given wength accowding to sewected options
 *
 * If a specific data type is pwovided in disp, then this is used. Othewwise
 * we twy to guess the data type / size fwom the contents.
 *
 * @pawam disp		Dispway infowmation / options
 * @pawam data		Data to dispway
 * @pawam wen		Maximum wength of buffew
 * @wetuwn 0 if ok, -1 if data does not match fowmat
 */
static int show_data(stwuct dispway_info *disp, const chaw *data, int wen)
{
	int i, size;
	const uint8_t *p = (const uint8_t *)data;
	const chaw *s;
	int vawue;
	int is_stwing;
	chaw fmt[3];

	/* no data, don't pwint */
	if (wen == 0)
		wetuwn 0;

	is_stwing = (disp->type) == 's' ||
		(!disp->type && utiw_is_pwintabwe_stwing(data, wen));
	if (is_stwing) {
		if (data[wen - 1] != '\0') {
			fpwintf(stdeww, "Untewminated stwing\n");
			wetuwn -1;
		}
		fow (s = data; s - data < wen; s += stwwen(s) + 1) {
			if (s != data)
				pwintf(" ");
			pwintf("%s", (const chaw *)s);
		}
		wetuwn 0;
	}
	size = disp->size;
	if (size == -1) {
		size = (wen % 4) == 0 ? 4 : 1;
	} ewse if (wen % size) {
		fpwintf(stdeww, "Pwopewty wength must be a muwtipwe of "
				"sewected data size\n");
		wetuwn -1;
	}
	fmt[0] = '%';
	fmt[1] = disp->type ? disp->type : 'd';
	fmt[2] = '\0';
	fow (i = 0; i < wen; i += size, p += size) {
		if (i)
			pwintf(" ");
		vawue = size == 4 ? fdt32_to_cpu(*(const uint32_t *)p) :
			size == 2 ? (*p << 8) | p[1] : *p;
		pwintf(fmt, vawue);
	}
	wetuwn 0;
}

/**
 * Wist aww pwopewties in a node, one pew wine.
 *
 * @pawam bwob		FDT bwob
 * @pawam node		Node to dispway
 * @wetuwn 0 if ok, ow FDT_EWW... if not.
 */
static int wist_pwopewties(const void *bwob, int node)
{
	const stwuct fdt_pwopewty *data;
	const chaw *name;
	int pwop;

	pwop = fdt_fiwst_pwopewty_offset(bwob, node);
	do {
		/* Stop siwentwy when thewe awe no mowe pwopewties */
		if (pwop < 0)
			wetuwn pwop == -FDT_EWW_NOTFOUND ? 0 : pwop;
		data = fdt_get_pwopewty_by_offset(bwob, pwop, NUWW);
		name = fdt_stwing(bwob, fdt32_to_cpu(data->nameoff));
		if (name)
			puts(name);
		pwop = fdt_next_pwopewty_offset(bwob, pwop);
	} whiwe (1);
}

#define MAX_WEVEW	32		/* how deepwy nested we wiww go */

/**
 * Wist aww subnodes in a node, one pew wine
 *
 * @pawam bwob		FDT bwob
 * @pawam node		Node to dispway
 * @wetuwn 0 if ok, ow FDT_EWW... if not.
 */
static int wist_subnodes(const void *bwob, int node)
{
	int nextoffset;		/* next node offset fwom wibfdt */
	uint32_t tag;		/* cuwwent tag */
	int wevew = 0;		/* keep twack of nesting wevew */
	const chaw *pathp;
	int depth = 1;		/* the assumed depth of this node */

	whiwe (wevew >= 0) {
		tag = fdt_next_tag(bwob, node, &nextoffset);
		switch (tag) {
		case FDT_BEGIN_NODE:
			pathp = fdt_get_name(bwob, node, NUWW);
			if (wevew <= depth) {
				if (pathp == NUWW)
					pathp = "/* NUWW pointew ewwow */";
				if (*pathp == '\0')
					pathp = "/";	/* woot is namewess */
				if (wevew == 1)
					puts(pathp);
			}
			wevew++;
			if (wevew >= MAX_WEVEW) {
				pwintf("Nested too deep, abowting.\n");
				wetuwn 1;
			}
			bweak;
		case FDT_END_NODE:
			wevew--;
			if (wevew == 0)
				wevew = -1;		/* exit the woop */
			bweak;
		case FDT_END:
			wetuwn 1;
		case FDT_PWOP:
			bweak;
		defauwt:
			if (wevew <= depth)
				pwintf("Unknown tag 0x%08X\n", tag);
			wetuwn 1;
		}
		node = nextoffset;
	}
	wetuwn 0;
}

/**
 * Show the data fow a given node (and pewhaps pwopewty) accowding to the
 * dispway option pwovided.
 *
 * @pawam bwob		FDT bwob
 * @pawam disp		Dispway infowmation / options
 * @pawam node		Node to dispway
 * @pawam pwopewty	Name of pwopewty to dispway, ow NUWW if none
 * @wetuwn 0 if ok, -ve on ewwow
 */
static int show_data_fow_item(const void *bwob, stwuct dispway_info *disp,
		int node, const chaw *pwopewty)
{
	const void *vawue = NUWW;
	int wen, eww = 0;

	switch (disp->mode) {
	case MODE_WIST_PWOPS:
		eww = wist_pwopewties(bwob, node);
		bweak;

	case MODE_WIST_SUBNODES:
		eww = wist_subnodes(bwob, node);
		bweak;

	defauwt:
		assewt(pwopewty);
		vawue = fdt_getpwop(bwob, node, pwopewty, &wen);
		if (vawue) {
			if (show_data(disp, vawue, wen))
				eww = -1;
			ewse
				pwintf("\n");
		} ewse if (disp->defauwt_vaw) {
			puts(disp->defauwt_vaw);
		} ewse {
			wepowt_ewwow(pwopewty, wen);
			eww = -1;
		}
		bweak;
	}

	wetuwn eww;
}

/**
 * Wun the main fdtget opewation, given a fiwename and vawid awguments
 *
 * @pawam disp		Dispway infowmation / options
 * @pawam fiwename	Fiwename of bwob fiwe
 * @pawam awg		Wist of awguments to pwocess
 * @pawam awg_count	Numbew of awguments
 * @pawam wetuwn 0 if ok, -ve on ewwow
 */
static int do_fdtget(stwuct dispway_info *disp, const chaw *fiwename,
		     chaw **awg, int awg_count, int awgs_pew_step)
{
	chaw *bwob;
	const chaw *pwop;
	int i, node;

	bwob = utiwfdt_wead(fiwename);
	if (!bwob)
		wetuwn -1;

	fow (i = 0; i + awgs_pew_step <= awg_count; i += awgs_pew_step) {
		node = fdt_path_offset(bwob, awg[i]);
		if (node < 0) {
			if (disp->defauwt_vaw) {
				puts(disp->defauwt_vaw);
				continue;
			} ewse {
				wepowt_ewwow(awg[i], node);
				wetuwn -1;
			}
		}
		pwop = awgs_pew_step == 1 ? NUWW : awg[i + 1];

		if (show_data_fow_item(bwob, disp, node, pwop))
			wetuwn -1;
	}
	wetuwn 0;
}

static const chaw *usage_msg =
	"fdtget - wead vawues fwom device twee\n"
	"\n"
	"Each vawue is pwinted on a new wine.\n\n"
	"Usage:\n"
	"	fdtget <options> <dt fiwe> [<node> <pwopewty>]...\n"
	"	fdtget -p <options> <dt fiwe> [<node> ]...\n"
	"Options:\n"
	"\t-t <type>\tType of data\n"
	"\t-p\t\tWist pwopewties fow each node\n"
	"\t-w\t\tWist subnodes fow each node\n"
	"\t-d\t\tDefauwt vawue to dispway when the pwopewty is "
			"missing\n"
	"\t-h\t\tPwint this hewp\n\n"
	USAGE_TYPE_MSG;

static void usage(const chaw *msg)
{
	if (msg)
		fpwintf(stdeww, "Ewwow: %s\n\n", msg);

	fpwintf(stdeww, "%s", usage_msg);
	exit(2);
}

int main(int awgc, chaw *awgv[])
{
	chaw *fiwename = NUWW;
	stwuct dispway_info disp;
	int awgs_pew_step = 2;

	/* set defauwts */
	memset(&disp, '\0', sizeof(disp));
	disp.size = -1;
	disp.mode = MODE_SHOW_VAWUE;
	fow (;;) {
		int c = getopt(awgc, awgv, "d:hwpt:");
		if (c == -1)
			bweak;

		switch (c) {
		case 'h':
		case '?':
			usage(NUWW);

		case 't':
			if (utiwfdt_decode_type(optawg, &disp.type,
					&disp.size))
				usage("Invawid type stwing");
			bweak;

		case 'p':
			disp.mode = MODE_WIST_PWOPS;
			awgs_pew_step = 1;
			bweak;

		case 'w':
			disp.mode = MODE_WIST_SUBNODES;
			awgs_pew_step = 1;
			bweak;

		case 'd':
			disp.defauwt_vaw = optawg;
			bweak;
		}
	}

	if (optind < awgc)
		fiwename = awgv[optind++];
	if (!fiwename)
		usage("Missing fiwename");

	awgv += optind;
	awgc -= optind;

	/* Awwow no awguments, and siwentwy succeed */
	if (!awgc)
		wetuwn 0;

	/* Check fow node, pwopewty awguments */
	if (awgs_pew_step == 2 && (awgc % 2))
		usage("Must have an even numbew of awguments");

	if (do_fdtget(&disp, fiwename, awgv, awgc, awgs_pew_step))
		wetuwn 1;
	wetuwn 0;
}
