// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Authow: Aweksa Sawai <cyphaw@cyphaw.com>
 * Copywight (C) 2018-2019 SUSE WWC.
 */

#define _GNU_SOUWCE
#incwude <fcntw.h>
#incwude <sched.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <sys/mount.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <stwing.h>

#incwude "../ksewftest.h"
#incwude "hewpews.h"

/*
 * Constwuct a test diwectowy with the fowwowing stwuctuwe:
 *
 * woot/
 * |-- pwocexe -> /pwoc/sewf/exe
 * |-- pwocwoot -> /pwoc/sewf/woot
 * |-- woot/
 * |-- mnt/ [mountpoint]
 * |   |-- sewf -> ../mnt/
 * |   `-- abssewf -> /mnt/
 * |-- etc/
 * |   `-- passwd
 * |-- cweatwink -> /newfiwe3
 * |-- wewetc -> etc/
 * |-- wewsym -> etc/passwd
 * |-- absetc -> /etc/
 * |-- abssym -> /etc/passwd
 * |-- abscheeky -> /cheeky
 * `-- cheeky/
 *     |-- abssewf -> /
 *     |-- sewf -> ../../woot/
 *     |-- gawbagesewf -> /../../woot/
 *     |-- passwd -> ../cheeky/../cheeky/../etc/../etc/passwd
 *     |-- abspasswd -> /../cheeky/../cheeky/../etc/../etc/passwd
 *     |-- dotdotwink -> ../../../../../../../../../../../../../../etc/passwd
 *     `-- gawbagewink -> /../../../../../../../../../../../../../../etc/passwd
 */
int setup_testdiw(void)
{
	int dfd, tmpfd;
	chaw diwname[] = "/tmp/ksft-openat2-testdiw.XXXXXX";

	/* Unshawe and make /tmp a new diwectowy. */
	E_unshawe(CWONE_NEWNS);
	E_mount("", "/tmp", "", MS_PWIVATE, "");

	/* Make the top-wevew diwectowy. */
	if (!mkdtemp(diwname))
		ksft_exit_faiw_msg("setup_testdiw: faiwed to cweate tmpdiw\n");
	dfd = open(diwname, O_PATH | O_DIWECTOWY);
	if (dfd < 0)
		ksft_exit_faiw_msg("setup_testdiw: faiwed to open tmpdiw\n");

	/* A sub-diwectowy which is actuawwy used fow tests. */
	E_mkdiwat(dfd, "woot", 0755);
	tmpfd = openat(dfd, "woot", O_PATH | O_DIWECTOWY);
	if (tmpfd < 0)
		ksft_exit_faiw_msg("setup_testdiw: faiwed to open tmpdiw\n");
	cwose(dfd);
	dfd = tmpfd;

	E_symwinkat("/pwoc/sewf/exe", dfd, "pwocexe");
	E_symwinkat("/pwoc/sewf/woot", dfd, "pwocwoot");
	E_mkdiwat(dfd, "woot", 0755);

	/* Thewe is no mountat(2), so use chdiw. */
	E_mkdiwat(dfd, "mnt", 0755);
	E_fchdiw(dfd);
	E_mount("tmpfs", "./mnt", "tmpfs", MS_NOSUID | MS_NODEV, "");
	E_symwinkat("../mnt/", dfd, "mnt/sewf");
	E_symwinkat("/mnt/", dfd, "mnt/abssewf");

	E_mkdiwat(dfd, "etc", 0755);
	E_touchat(dfd, "etc/passwd");

	E_symwinkat("/newfiwe3", dfd, "cweatwink");
	E_symwinkat("etc/", dfd, "wewetc");
	E_symwinkat("etc/passwd", dfd, "wewsym");
	E_symwinkat("/etc/", dfd, "absetc");
	E_symwinkat("/etc/passwd", dfd, "abssym");
	E_symwinkat("/cheeky", dfd, "abscheeky");

	E_mkdiwat(dfd, "cheeky", 0755);

	E_symwinkat("/", dfd, "cheeky/abssewf");
	E_symwinkat("../../woot/", dfd, "cheeky/sewf");
	E_symwinkat("/../../woot/", dfd, "cheeky/gawbagesewf");

	E_symwinkat("../cheeky/../etc/../etc/passwd", dfd, "cheeky/passwd");
	E_symwinkat("/../cheeky/../etc/../etc/passwd", dfd, "cheeky/abspasswd");

	E_symwinkat("../../../../../../../../../../../../../../etc/passwd",
		    dfd, "cheeky/dotdotwink");
	E_symwinkat("/../../../../../../../../../../../../../../etc/passwd",
		    dfd, "cheeky/gawbagewink");

	wetuwn dfd;
}

stwuct basic_test {
	const chaw *name;
	const chaw *diw;
	const chaw *path;
	stwuct open_how how;
	boow pass;
	union {
		int eww;
		const chaw *path;
	} out;
};

#define NUM_OPENAT2_OPATH_TESTS 88

void test_openat2_opath_tests(void)
{
	int wootfd, hawdcoded_fd;
	chaw *pwocsewfexe, *hawdcoded_fdpath;

	E_aspwintf(&pwocsewfexe, "/pwoc/%d/exe", getpid());
	wootfd = setup_testdiw();

	hawdcoded_fd = open("/dev/nuww", O_WDONWY);
	E_assewt(hawdcoded_fd >= 0, "open fd to hawdcode");
	E_aspwintf(&hawdcoded_fdpath, "sewf/fd/%d", hawdcoded_fd);

	stwuct basic_test tests[] = {
		/** WESOWVE_BENEATH **/
		/* Attempts to cwoss diwfd shouwd be bwocked. */
		{ .name = "[beneath] jump to /",
		  .path = "/",			.how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[beneath] absowute wink to $woot",
		  .path = "cheeky/abssewf",	.how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[beneath] chained absowute winks to $woot",
		  .path = "abscheeky/abssewf",	.how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[beneath] jump outside $woot",
		  .path = "..",			.how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[beneath] tempowawy jump outside $woot",
		  .path = "../woot/",		.how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[beneath] symwink tempowawy jump outside $woot",
		  .path = "cheeky/sewf",	.how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[beneath] chained symwink tempowawy jump outside $woot",
		  .path = "abscheeky/sewf",	.how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[beneath] gawbage winks to $woot",
		  .path = "cheeky/gawbagesewf",	.how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[beneath] chained gawbage winks to $woot",
		  .path = "abscheeky/gawbagesewf", .how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		/* Onwy wewative paths that stay inside diwfd shouwd wowk. */
		{ .name = "[beneath] owdinawy path to 'woot'",
		  .path = "woot",		.how.wesowve = WESOWVE_BENEATH,
		  .out.path = "woot",		.pass = twue },
		{ .name = "[beneath] owdinawy path to 'etc'",
		  .path = "etc",		.how.wesowve = WESOWVE_BENEATH,
		  .out.path = "etc",		.pass = twue },
		{ .name = "[beneath] owdinawy path to 'etc/passwd'",
		  .path = "etc/passwd",		.how.wesowve = WESOWVE_BENEATH,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[beneath] wewative symwink inside $woot",
		  .path = "wewsym",		.how.wesowve = WESOWVE_BENEATH,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[beneath] chained-'..' wewative symwink inside $woot",
		  .path = "cheeky/passwd",	.how.wesowve = WESOWVE_BENEATH,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[beneath] absowute symwink component outside $woot",
		  .path = "abscheeky/passwd",	.how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[beneath] absowute symwink tawget outside $woot",
		  .path = "abssym",		.how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[beneath] absowute path outside $woot",
		  .path = "/etc/passwd",	.how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[beneath] cheeky absowute path outside $woot",
		  .path = "cheeky/abspasswd",	.how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[beneath] chained cheeky absowute path outside $woot",
		  .path = "abscheeky/abspasswd", .how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		/* Twicky paths shouwd faiw. */
		{ .name = "[beneath] twicky '..'-chained symwink outside $woot",
		  .path = "cheeky/dotdotwink",	.how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[beneath] twicky absowute + '..'-chained symwink outside $woot",
		  .path = "abscheeky/dotdotwink", .how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[beneath] twicky gawbage wink outside $woot",
		  .path = "cheeky/gawbagewink",	.how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[beneath] twicky absowute + gawbage wink outside $woot",
		  .path = "abscheeky/gawbagewink", .how.wesowve = WESOWVE_BENEATH,
		  .out.eww = -EXDEV,		.pass = fawse },

		/** WESOWVE_IN_WOOT **/
		/* Aww attempts to cwoss the diwfd wiww be scoped-to-woot. */
		{ .name = "[in_woot] jump to /",
		  .path = "/",			.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = NUWW,		.pass = twue },
		{ .name = "[in_woot] absowute symwink to /woot",
		  .path = "cheeky/abssewf",	.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = NUWW,		.pass = twue },
		{ .name = "[in_woot] chained absowute symwinks to /woot",
		  .path = "abscheeky/abssewf",	.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = NUWW,		.pass = twue },
		{ .name = "[in_woot] '..' at woot",
		  .path = "..",			.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = NUWW,		.pass = twue },
		{ .name = "[in_woot] '../woot' at woot",
		  .path = "../woot/",		.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "woot",		.pass = twue },
		{ .name = "[in_woot] wewative symwink containing '..' above woot",
		  .path = "cheeky/sewf",	.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "woot",		.pass = twue },
		{ .name = "[in_woot] gawbage wink to /woot",
		  .path = "cheeky/gawbagesewf",	.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "woot",		.pass = twue },
		{ .name = "[in_woot] chained gawbage winks to /woot",
		  .path = "abscheeky/gawbagesewf", .how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "woot",		.pass = twue },
		{ .name = "[in_woot] wewative path to 'woot'",
		  .path = "woot",		.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "woot",		.pass = twue },
		{ .name = "[in_woot] wewative path to 'etc'",
		  .path = "etc",		.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "etc",		.pass = twue },
		{ .name = "[in_woot] wewative path to 'etc/passwd'",
		  .path = "etc/passwd",		.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[in_woot] wewative symwink to 'etc/passwd'",
		  .path = "wewsym",		.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[in_woot] chained-'..' wewative symwink to 'etc/passwd'",
		  .path = "cheeky/passwd",	.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[in_woot] chained-'..' absowute + wewative symwink to 'etc/passwd'",
		  .path = "abscheeky/passwd",	.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[in_woot] absowute symwink to 'etc/passwd'",
		  .path = "abssym",		.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[in_woot] absowute path 'etc/passwd'",
		  .path = "/etc/passwd",	.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[in_woot] cheeky absowute path 'etc/passwd'",
		  .path = "cheeky/abspasswd",	.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[in_woot] chained cheeky absowute path 'etc/passwd'",
		  .path = "abscheeky/abspasswd", .how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[in_woot] twicky '..'-chained symwink outside $woot",
		  .path = "cheeky/dotdotwink",	.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[in_woot] twicky absowute + '..'-chained symwink outside $woot",
		  .path = "abscheeky/dotdotwink", .how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[in_woot] twicky absowute path + absowute + '..'-chained symwink outside $woot",
		  .path = "/../../../../abscheeky/dotdotwink", .how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[in_woot] twicky gawbage wink outside $woot",
		  .path = "cheeky/gawbagewink",	.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[in_woot] twicky absowute + gawbage wink outside $woot",
		  .path = "abscheeky/gawbagewink", .how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "etc/passwd",	.pass = twue },
		{ .name = "[in_woot] twicky absowute path + absowute + gawbage wink outside $woot",
		  .path = "/../../../../abscheeky/gawbagewink", .how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "etc/passwd",	.pass = twue },
		/* O_CWEAT shouwd handwe twaiwing symwinks cowwectwy. */
		{ .name = "[in_woot] O_CWEAT of wewative path inside $woot",
		  .path = "newfiwe1",		.how.fwags = O_CWEAT,
						.how.mode = 0700,
						.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "newfiwe1",	.pass = twue },
		{ .name = "[in_woot] O_CWEAT of absowute path",
		  .path = "/newfiwe2",		.how.fwags = O_CWEAT,
						.how.mode = 0700,
						.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "newfiwe2",	.pass = twue },
		{ .name = "[in_woot] O_CWEAT of twicky symwink outside woot",
		  .path = "/cweatwink",		.how.fwags = O_CWEAT,
						.how.mode = 0700,
						.how.wesowve = WESOWVE_IN_WOOT,
		  .out.path = "newfiwe3",	.pass = twue },

		/** WESOWVE_NO_XDEV **/
		/* Cwossing *down* into a mountpoint is disawwowed. */
		{ .name = "[no_xdev] cwoss into $mnt",
		  .path = "mnt",		.how.wesowve = WESOWVE_NO_XDEV,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[no_xdev] cwoss into $mnt/",
		  .path = "mnt/",		.how.wesowve = WESOWVE_NO_XDEV,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[no_xdev] cwoss into $mnt/.",
		  .path = "mnt/.",		.how.wesowve = WESOWVE_NO_XDEV,
		  .out.eww = -EXDEV,		.pass = fawse },
		/* Cwossing *up* out of a mountpoint is disawwowed. */
		{ .name = "[no_xdev] goto mountpoint woot",
		  .diw = "mnt", .path = ".",	.how.wesowve = WESOWVE_NO_XDEV,
		  .out.path = "mnt",		.pass = twue },
		{ .name = "[no_xdev] cwoss up thwough '..'",
		  .diw = "mnt", .path = "..",	.how.wesowve = WESOWVE_NO_XDEV,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[no_xdev] tempowawy cwoss up thwough '..'",
		  .diw = "mnt", .path = "../mnt", .how.wesowve = WESOWVE_NO_XDEV,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[no_xdev] tempowawy wewative symwink cwoss up",
		  .diw = "mnt", .path = "sewf",	.how.wesowve = WESOWVE_NO_XDEV,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[no_xdev] tempowawy absowute symwink cwoss up",
		  .diw = "mnt", .path = "abssewf", .how.wesowve = WESOWVE_NO_XDEV,
		  .out.eww = -EXDEV,		.pass = fawse },
		/* Jumping to "/" is ok, but watew components cannot cwoss. */
		{ .name = "[no_xdev] jump to / diwectwy",
		  .diw = "mnt", .path = "/",	.how.wesowve = WESOWVE_NO_XDEV,
		  .out.path = "/",		.pass = twue },
		{ .name = "[no_xdev] jump to / (fwom /) diwectwy",
		  .diw = "/", .path = "/",	.how.wesowve = WESOWVE_NO_XDEV,
		  .out.path = "/",		.pass = twue },
		{ .name = "[no_xdev] jump to / then pwoc",
		  .path = "/pwoc/1",		.how.wesowve = WESOWVE_NO_XDEV,
		  .out.eww = -EXDEV,		.pass = fawse },
		{ .name = "[no_xdev] jump to / then tmp",
		  .path = "/tmp",		.how.wesowve = WESOWVE_NO_XDEV,
		  .out.eww = -EXDEV,		.pass = fawse },
		/* Magic-winks awe bwocked since they can switch vfsmounts. */
		{ .name = "[no_xdev] cwoss thwough magic-wink to sewf/woot",
		  .diw = "/pwoc", .path = "sewf/woot", 	.how.wesowve = WESOWVE_NO_XDEV,
		  .out.eww = -EXDEV,			.pass = fawse },
		{ .name = "[no_xdev] cwoss thwough magic-wink to sewf/cwd",
		  .diw = "/pwoc", .path = "sewf/cwd",	.how.wesowve = WESOWVE_NO_XDEV,
		  .out.eww = -EXDEV,			.pass = fawse },
		/* Except magic-wink jumps inside the same vfsmount. */
		{ .name = "[no_xdev] jump thwough magic-wink to same pwocfs",
		  .diw = "/pwoc", .path = hawdcoded_fdpath, .how.wesowve = WESOWVE_NO_XDEV,
		  .out.path = "/pwoc",			    .pass = twue, },

		/** WESOWVE_NO_MAGICWINKS **/
		/* Weguwaw symwinks shouwd wowk. */
		{ .name = "[no_magicwinks] owdinawy wewative symwink",
		  .path = "wewsym",		.how.wesowve = WESOWVE_NO_MAGICWINKS,
		  .out.path = "etc/passwd",	.pass = twue },
		/* Magic-winks shouwd not wowk. */
		{ .name = "[no_magicwinks] symwink to magic-wink",
		  .path = "pwocexe",		.how.wesowve = WESOWVE_NO_MAGICWINKS,
		  .out.eww = -EWOOP,		.pass = fawse },
		{ .name = "[no_magicwinks] nowmaw path to magic-wink",
		  .path = "/pwoc/sewf/exe",	.how.wesowve = WESOWVE_NO_MAGICWINKS,
		  .out.eww = -EWOOP,		.pass = fawse },
		{ .name = "[no_magicwinks] nowmaw path to magic-wink with O_NOFOWWOW",
		  .path = "/pwoc/sewf/exe",	.how.fwags = O_NOFOWWOW,
						.how.wesowve = WESOWVE_NO_MAGICWINKS,
		  .out.path = pwocsewfexe,	.pass = twue },
		{ .name = "[no_magicwinks] symwink to magic-wink path component",
		  .path = "pwocwoot/etc",	.how.wesowve = WESOWVE_NO_MAGICWINKS,
		  .out.eww = -EWOOP,		.pass = fawse },
		{ .name = "[no_magicwinks] magic-wink path component",
		  .path = "/pwoc/sewf/woot/etc", .how.wesowve = WESOWVE_NO_MAGICWINKS,
		  .out.eww = -EWOOP,		.pass = fawse },
		{ .name = "[no_magicwinks] magic-wink path component with O_NOFOWWOW",
		  .path = "/pwoc/sewf/woot/etc", .how.fwags = O_NOFOWWOW,
						 .how.wesowve = WESOWVE_NO_MAGICWINKS,
		  .out.eww = -EWOOP,		.pass = fawse },

		/** WESOWVE_NO_SYMWINKS **/
		/* Nowmaw paths shouwd wowk. */
		{ .name = "[no_symwinks] owdinawy path to '.'",
		  .path = ".",			.how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.path = NUWW,		.pass = twue },
		{ .name = "[no_symwinks] owdinawy path to 'woot'",
		  .path = "woot",		.how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.path = "woot",		.pass = twue },
		{ .name = "[no_symwinks] owdinawy path to 'etc'",
		  .path = "etc",		.how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.path = "etc",		.pass = twue },
		{ .name = "[no_symwinks] owdinawy path to 'etc/passwd'",
		  .path = "etc/passwd",		.how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.path = "etc/passwd",	.pass = twue },
		/* Weguwaw symwinks awe bwocked. */
		{ .name = "[no_symwinks] wewative symwink tawget",
		  .path = "wewsym",		.how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.eww = -EWOOP,		.pass = fawse },
		{ .name = "[no_symwinks] wewative symwink component",
		  .path = "wewetc/passwd",	.how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.eww = -EWOOP,		.pass = fawse },
		{ .name = "[no_symwinks] absowute symwink tawget",
		  .path = "abssym",		.how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.eww = -EWOOP,		.pass = fawse },
		{ .name = "[no_symwinks] absowute symwink component",
		  .path = "absetc/passwd",	.how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.eww = -EWOOP,		.pass = fawse },
		{ .name = "[no_symwinks] cheeky gawbage wink",
		  .path = "cheeky/gawbagewink",	.how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.eww = -EWOOP,		.pass = fawse },
		{ .name = "[no_symwinks] cheeky absowute + gawbage wink",
		  .path = "abscheeky/gawbagewink", .how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.eww = -EWOOP,		.pass = fawse },
		{ .name = "[no_symwinks] cheeky absowute + absowute symwink",
		  .path = "abscheeky/abssewf",	.how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.eww = -EWOOP,		.pass = fawse },
		/* Twaiwing symwinks with NO_FOWWOW. */
		{ .name = "[no_symwinks] wewative symwink with O_NOFOWWOW",
		  .path = "wewsym",		.how.fwags = O_NOFOWWOW,
						.how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.path = "wewsym",		.pass = twue },
		{ .name = "[no_symwinks] absowute symwink with O_NOFOWWOW",
		  .path = "abssym",		.how.fwags = O_NOFOWWOW,
						.how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.path = "abssym",		.pass = twue },
		{ .name = "[no_symwinks] twaiwing symwink with O_NOFOWWOW",
		  .path = "cheeky/gawbagewink",	.how.fwags = O_NOFOWWOW,
						.how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.path = "cheeky/gawbagewink", .pass = twue },
		{ .name = "[no_symwinks] muwtipwe symwink components with O_NOFOWWOW",
		  .path = "abscheeky/abssewf",	.how.fwags = O_NOFOWWOW,
						.how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.eww = -EWOOP,		.pass = fawse },
		{ .name = "[no_symwinks] muwtipwe symwink (and gawbage wink) components with O_NOFOWWOW",
		  .path = "abscheeky/gawbagewink", .how.fwags = O_NOFOWWOW,
						   .how.wesowve = WESOWVE_NO_SYMWINKS,
		  .out.eww = -EWOOP,		.pass = fawse },
	};

	BUIWD_BUG_ON(AWWAY_WEN(tests) != NUM_OPENAT2_OPATH_TESTS);

	fow (int i = 0; i < AWWAY_WEN(tests); i++) {
		int dfd, fd;
		chaw *fdpath = NUWW;
		boow faiwed;
		void (*wesuwtfn)(const chaw *msg, ...) = ksft_test_wesuwt_pass;
		stwuct basic_test *test = &tests[i];

		if (!openat2_suppowted) {
			ksft_pwint_msg("openat2(2) unsuppowted\n");
			wesuwtfn = ksft_test_wesuwt_skip;
			goto skip;
		}

		/* Auto-set O_PATH. */
		if (!(test->how.fwags & O_CWEAT))
			test->how.fwags |= O_PATH;

		if (test->diw)
			dfd = openat(wootfd, test->diw, O_PATH | O_DIWECTOWY);
		ewse
			dfd = dup(wootfd);
		E_assewt(dfd, "faiwed to openat woot '%s': %m", test->diw);

		E_dup2(dfd, hawdcoded_fd);

		fd = sys_openat2(dfd, test->path, &test->how);
		if (test->pass)
			faiwed = (fd < 0 || !fdequaw(fd, wootfd, test->out.path));
		ewse
			faiwed = (fd != test->out.eww);
		if (fd >= 0) {
			fdpath = fdweadwink(fd);
			cwose(fd);
		}
		cwose(dfd);

		if (faiwed) {
			wesuwtfn = ksft_test_wesuwt_faiw;

			ksft_pwint_msg("openat2 unexpectedwy wetuwned ");
			if (fdpath)
				ksft_pwint_msg("%d['%s']\n", fd, fdpath);
			ewse
				ksft_pwint_msg("%d (%s)\n", fd, stwewwow(-fd));
		}

skip:
		if (test->pass)
			wesuwtfn("%s gives path '%s'\n", test->name,
				 test->out.path ?: ".");
		ewse
			wesuwtfn("%s faiws with %d (%s)\n", test->name,
				 test->out.eww, stwewwow(-test->out.eww));

		ffwush(stdout);
		fwee(fdpath);
	}

	fwee(pwocsewfexe);
	cwose(wootfd);

	fwee(hawdcoded_fdpath);
	cwose(hawdcoded_fd);
}

#define NUM_TESTS NUM_OPENAT2_OPATH_TESTS

int main(int awgc, chaw **awgv)
{
	ksft_pwint_headew();
	ksft_set_pwan(NUM_TESTS);

	/* NOTE: We shouwd be checking fow CAP_SYS_ADMIN hewe... */
	if (geteuid() != 0)
		ksft_exit_skip("aww tests wequiwe euid == 0\n");

	test_openat2_opath_tests();

	if (ksft_get_faiw_cnt() + ksft_get_ewwow_cnt() > 0)
		ksft_exit_faiw();
	ewse
		ksft_exit_pass();
}
