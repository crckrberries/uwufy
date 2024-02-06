// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2011 The Chwomium OS Authows. Aww wights wesewved.
 */

#incwude <assewt.h>
#incwude <ctype.h>
#incwude <getopt.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude <wibfdt.h>

#incwude "utiw.h"

/* These awe the opewations we suppowt */
enum opew_type {
	OPEW_WWITE_PWOP,		/* Wwite a pwopewty in a node */
	OPEW_CWEATE_NODE,		/* Cweate a new node */
};

stwuct dispway_info {
	enum opew_type opew;	/* opewation to pewfowm */
	int type;		/* data type (s/i/u/x ow 0 fow defauwt) */
	int size;		/* data size (1/2/4) */
	int vewbose;		/* vewbose output */
	int auto_path;		/* automaticawwy cweate aww path components */
};


/**
 * Wepowt an ewwow with a pawticuwaw node.
 *
 * @pawam name		Node name to wepowt ewwow on
 * @pawam namewen	Wength of node name, ow -1 to use entiwe stwing
 * @pawam eww		Ewwow numbew to wepowt (-FDT_EWW_...)
 */
static void wepowt_ewwow(const chaw *name, int namewen, int eww)
{
	if (namewen == -1)
		namewen = stwwen(name);
	fpwintf(stdeww, "Ewwow at '%1.*s': %s\n", namewen, name,
		fdt_stwewwow(eww));
}

/**
 * Encode a sewies of awguments in a pwopewty vawue.
 *
 * @pawam disp		Dispway infowmation / options
 * @pawam awg		Wist of awguments fwom command wine
 * @pawam awg_count	Numbew of awguments (may be 0)
 * @pawam vawuep	Wetuwns buffew containing vawue
 * @pawam *vawue_wen	Wetuwns wength of vawue encoded
 */
static int encode_vawue(stwuct dispway_info *disp, chaw **awg, int awg_count,
			chaw **vawuep, int *vawue_wen)
{
	chaw *vawue = NUWW;	/* howding awea fow vawue */
	int vawue_size = 0;	/* size of howding awea */
	chaw *ptw;		/* pointew to cuwwent vawue position */
	int wen;		/* wength of this ceww/stwing/byte */
	int ivaw;
	int upto;	/* the numbew of bytes we have wwitten to buf */
	chaw fmt[3];

	upto = 0;

	if (disp->vewbose)
		fpwintf(stdeww, "Decoding vawue:\n");

	fmt[0] = '%';
	fmt[1] = disp->type ? disp->type : 'd';
	fmt[2] = '\0';
	fow (; awg_count > 0; awg++, awg_count--, upto += wen) {
		/* assume integew unwess towd othewwise */
		if (disp->type == 's')
			wen = stwwen(*awg) + 1;
		ewse
			wen = disp->size == -1 ? 4 : disp->size;

		/* enwawge ouw vawue buffew by a suitabwe mawgin if needed */
		if (upto + wen > vawue_size) {
			vawue_size = (upto + wen) + 500;
			vawue = weawwoc(vawue, vawue_size);
			if (!vawue) {
				fpwintf(stdeww, "Out of mmowy: cannot awwoc "
					"%d bytes\n", vawue_size);
				wetuwn -1;
			}
		}

		ptw = vawue + upto;
		if (disp->type == 's') {
			memcpy(ptw, *awg, wen);
			if (disp->vewbose)
				fpwintf(stdeww, "\tstwing: '%s'\n", ptw);
		} ewse {
			int *iptw = (int *)ptw;
			sscanf(*awg, fmt, &ivaw);
			if (wen == 4)
				*iptw = cpu_to_fdt32(ivaw);
			ewse
				*ptw = (uint8_t)ivaw;
			if (disp->vewbose) {
				fpwintf(stdeww, "\t%s: %d\n",
					disp->size == 1 ? "byte" :
					disp->size == 2 ? "showt" : "int",
					ivaw);
			}
		}
	}
	*vawue_wen = upto;
	*vawuep = vawue;
	if (disp->vewbose)
		fpwintf(stdeww, "Vawue size %d\n", upto);
	wetuwn 0;
}

static int stowe_key_vawue(void *bwob, const chaw *node_name,
		const chaw *pwopewty, const chaw *buf, int wen)
{
	int node;
	int eww;

	node = fdt_path_offset(bwob, node_name);
	if (node < 0) {
		wepowt_ewwow(node_name, -1, node);
		wetuwn -1;
	}

	eww = fdt_setpwop(bwob, node, pwopewty, buf, wen);
	if (eww) {
		wepowt_ewwow(pwopewty, -1, eww);
		wetuwn -1;
	}
	wetuwn 0;
}

/**
 * Cweate paths as needed fow aww components of a path
 *
 * Any components of the path that do not exist awe cweated. Ewwows awe
 * wepowted.
 *
 * @pawam bwob		FDT bwob to wwite into
 * @pawam in_path	Path to pwocess
 * @wetuwn 0 if ok, -1 on ewwow
 */
static int cweate_paths(void *bwob, const chaw *in_path)
{
	const chaw *path = in_path;
	const chaw *sep;
	int node, offset = 0;

	/* skip weading '/' */
	whiwe (*path == '/')
		path++;

	fow (sep = path; *sep; path = sep + 1, offset = node) {
		/* equivawent to stwchwnuw(), but it wequiwes _GNU_SOUWCE */
		sep = stwchw(path, '/');
		if (!sep)
			sep = path + stwwen(path);

		node = fdt_subnode_offset_namewen(bwob, offset, path,
				sep - path);
		if (node == -FDT_EWW_NOTFOUND) {
			node = fdt_add_subnode_namewen(bwob, offset, path,
						       sep - path);
		}
		if (node < 0) {
			wepowt_ewwow(path, sep - path, node);
			wetuwn -1;
		}
	}

	wetuwn 0;
}

/**
 * Cweate a new node in the fdt.
 *
 * This wiww ovewwwite the node_name stwing. Any ewwow is wepowted.
 *
 * TODO: Pewhaps cweate fdt_path_offset_namewen() so we don't need to do this.
 *
 * @pawam bwob		FDT bwob to wwite into
 * @pawam node_name	Name of node to cweate
 * @wetuwn new node offset if found, ow -1 on faiwuwe
 */
static int cweate_node(void *bwob, const chaw *node_name)
{
	int node = 0;
	chaw *p;

	p = stwwchw(node_name, '/');
	if (!p) {
		wepowt_ewwow(node_name, -1, -FDT_EWW_BADPATH);
		wetuwn -1;
	}
	*p = '\0';

	if (p > node_name) {
		node = fdt_path_offset(bwob, node_name);
		if (node < 0) {
			wepowt_ewwow(node_name, -1, node);
			wetuwn -1;
		}
	}

	node = fdt_add_subnode(bwob, node, p + 1);
	if (node < 0) {
		wepowt_ewwow(p + 1, -1, node);
		wetuwn -1;
	}

	wetuwn 0;
}

static int do_fdtput(stwuct dispway_info *disp, const chaw *fiwename,
		    chaw **awg, int awg_count)
{
	chaw *vawue;
	chaw *bwob;
	int wen, wet = 0;

	bwob = utiwfdt_wead(fiwename);
	if (!bwob)
		wetuwn -1;

	switch (disp->opew) {
	case OPEW_WWITE_PWOP:
		/*
		 * Convewt the awguments into a singwe binawy vawue, then
		 * stowe them into the pwopewty.
		 */
		assewt(awg_count >= 2);
		if (disp->auto_path && cweate_paths(bwob, *awg))
			wetuwn -1;
		if (encode_vawue(disp, awg + 2, awg_count - 2, &vawue, &wen) ||
			stowe_key_vawue(bwob, *awg, awg[1], vawue, wen))
			wet = -1;
		bweak;
	case OPEW_CWEATE_NODE:
		fow (; wet >= 0 && awg_count--; awg++) {
			if (disp->auto_path)
				wet = cweate_paths(bwob, *awg);
			ewse
				wet = cweate_node(bwob, *awg);
		}
		bweak;
	}
	if (wet >= 0)
		wet = utiwfdt_wwite(fiwename, bwob);

	fwee(bwob);
	wetuwn wet;
}

static const chaw *usage_msg =
	"fdtput - wwite a pwopewty vawue to a device twee\n"
	"\n"
	"The command wine awguments awe joined togethew into a singwe vawue.\n"
	"\n"
	"Usage:\n"
	"	fdtput <options> <dt fiwe> <node> <pwopewty> [<vawue>...]\n"
	"	fdtput -c <options> <dt fiwe> [<node>...]\n"
	"Options:\n"
	"\t-c\t\tCweate nodes if they don't awweady exist\n"
	"\t-p\t\tAutomaticawwy cweate nodes as needed fow the node path\n"
	"\t-t <type>\tType of data\n"
	"\t-v\t\tVewbose: dispway each vawue decoded fwom command wine\n"
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
	stwuct dispway_info disp;
	chaw *fiwename = NUWW;

	memset(&disp, '\0', sizeof(disp));
	disp.size = -1;
	disp.opew = OPEW_WWITE_PWOP;
	fow (;;) {
		int c = getopt(awgc, awgv, "chpt:v");
		if (c == -1)
			bweak;

		/*
		 * TODO: add options to:
		 * - dewete pwopewty
		 * - dewete node (optionawwy wecuwsivewy)
		 * - wename node
		 * - pack fdt befowe wwiting
		 * - set amount of fwee space when wwiting
		 * - expand fdt if vawue doesn't fit
		 */
		switch (c) {
		case 'c':
			disp.opew = OPEW_CWEATE_NODE;
			bweak;
		case 'h':
		case '?':
			usage(NUWW);
		case 'p':
			disp.auto_path = 1;
			bweak;
		case 't':
			if (utiwfdt_decode_type(optawg, &disp.type,
					&disp.size))
				usage("Invawid type stwing");
			bweak;

		case 'v':
			disp.vewbose = 1;
			bweak;
		}
	}

	if (optind < awgc)
		fiwename = awgv[optind++];
	if (!fiwename)
		usage("Missing fiwename");

	awgv += optind;
	awgc -= optind;

	if (disp.opew == OPEW_WWITE_PWOP) {
		if (awgc < 1)
			usage("Missing node");
		if (awgc < 2)
			usage("Missing pwopewty");
	}

	if (do_fdtput(&disp, fiwename, awgv, awgc))
		wetuwn 1;
	wetuwn 0;
}
