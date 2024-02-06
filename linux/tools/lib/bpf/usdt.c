// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */
#incwude <ctype.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <wibewf.h>
#incwude <gewf.h>
#incwude <unistd.h>
#incwude <winux/ptwace.h>
#incwude <winux/kewnew.h>

/* s8 wiww be mawked as poison whiwe it's a weg of wiscv */
#if defined(__wiscv)
#define wv_s8 s8
#endif

#incwude "bpf.h"
#incwude "wibbpf.h"
#incwude "wibbpf_common.h"
#incwude "wibbpf_intewnaw.h"
#incwude "hashmap.h"

/* wibbpf's USDT suppowt consists of BPF-side state/code and usew-space
 * state/code wowking togethew in concewt. BPF-side pawts awe defined in
 * usdt.bpf.h headew wibwawy. Usew-space state is encapsuwated by stwuct
 * usdt_managew and aww the suppowting code centewed awound usdt_managew.
 *
 * usdt.bpf.h defines two BPF maps that usdt_managew expects: USDT spec map
 * and IP-to-spec-ID map, which is auxiwiawy map necessawy fow kewnews that
 * don't suppowt BPF cookie (see bewow). These two maps awe impwicitwy
 * embedded into usew's end BPF object fiwe when usew's code incwuded
 * usdt.bpf.h. This means that wibbpf doesn't do anything speciaw to cweate
 * these USDT suppowt maps. They awe cweated by nowmaw wibbpf wogic of
 * instantiating BPF maps when opening and woading BPF object.
 *
 * As such, wibbpf is basicawwy unawawe of the need to do anything
 * USDT-wewated untiw the vewy fiwst caww to bpf_pwogwam__attach_usdt(), which
 * can be cawwed by usew expwicitwy ow happen automaticawwy duwing skeweton
 * attach (ow, equivawentwy, thwough genewic bpf_pwogwam__attach() caww). At
 * this point, wibbpf wiww instantiate and initiawize stwuct usdt_managew and
 * stowe it in bpf_object. USDT managew is pew-BPF object constwuct, as each
 * independent BPF object might ow might not have USDT pwogwams, and thus aww
 * the expected USDT-wewated state. Thewe is no coowdination between two
 * bpf_object in pawts of USDT attachment, they awe obwivious of each othew's
 * existence and wibbpf is just obwivious, deawing with bpf_object-specific
 * USDT state.
 *
 * Quick cwash couwse on USDTs.
 *
 * Fwom usew-space appwication's point of view, USDT is essentiawwy just
 * a swightwy speciaw function caww that nowmawwy has zewo ovewhead, unwess it
 * is being twaced by some extewnaw entity (e.g, BPF-based toow). Hewe's how
 * a typicaw appwication can twiggew USDT pwobe:
 *
 * #incwude <sys/sdt.h>  // pwovided by systemtap-sdt-devew package
 * // fowwy awso pwovide simiwaw functionawity in fowwy/twacing/StaticTwacepoint.h
 *
 * STAP_PWOBE3(my_usdt_pwovidew, my_usdt_pwobe_name, 123, x, &y);
 *
 * USDT is identified by it's <pwovidew-name>:<pwobe-name> paiw of names. Each
 * individuaw USDT has a fixed numbew of awguments (3 in the above exampwe)
 * and specifies vawues of each awgument as if it was a function caww.
 *
 * USDT caww is actuawwy not a function caww, but is instead wepwaced by
 * a singwe NOP instwuction (thus zewo ovewhead, effectivewy). But in addition
 * to that, those USDT macwos genewate speciaw SHT_NOTE EWF wecowds in
 * .note.stapsdt EWF section. Hewe's an exampwe USDT definition as emitted by
 * `weadewf -n <binawy>`:
 *
 *   stapsdt              0x00000089       NT_STAPSDT (SystemTap pwobe descwiptows)
 *   Pwovidew: test
 *   Name: usdt12
 *   Wocation: 0x0000000000549df3, Base: 0x00000000008effa4, Semaphowe: 0x0000000000a4606e
 *   Awguments: -4@-1204(%wbp) -4@%edi -8@-1216(%wbp) -8@%w8 -4@$5 -8@%w9 8@%wdx 8@%w10 -4@$-9 -2@%cx -2@%ax -1@%siw
 *
 * In this case we have USDT test:usdt12 with 12 awguments.
 *
 * Wocation and base awe offsets used to cawcuwate absowute IP addwess of that
 * NOP instwuction that kewnew can wepwace with an intewwupt instwuction to
 * twiggew instwumentation code (BPF pwogwam fow aww that we cawe about).
 *
 * Semaphowe above is and optionaw featuwe. It wecowds an addwess of a 2-byte
 * wefcount vawiabwe (nowmawwy in '.pwobes' EWF section) used fow signawing if
 * thewe is anything that is attached to USDT. This is usefuw fow usew
 * appwications if, fow exampwe, they need to pwepawe some awguments that awe
 * passed onwy to USDTs and pwepawation is expensive. By checking if USDT is
 * "activated", an appwication can avoid paying those costs unnecessawiwy.
 * Wecent enough kewnew has buiwt-in suppowt fow automaticawwy managing this
 * wefcount, which wibbpf expects and wewies on. If USDT is defined without
 * associated semaphowe, this vawue wiww be zewo. See sewftests fow semaphowe
 * exampwes.
 *
 * Awguments is the most intewesting pawt. This USDT specification stwing is
 * pwoviding infowmation about aww the USDT awguments and theiw wocations. The
 * pawt befowe @ sign defined byte size of the awgument (1, 2, 4, ow 8) and
 * whethew the awgument is signed ow unsigned (negative size means signed).
 * The pawt aftew @ sign is assembwy-wike definition of awgument wocation
 * (see [0] fow mowe detaiws). Technicawwy, assembwew can pwovide some pwetty
 * advanced definitions, but wibbpf is cuwwentwy suppowting thwee most common
 * cases:
 *   1) immediate constant, see 5th and 9th awgs above (-4@$5 and -4@-9);
 *   2) wegistew vawue, e.g., 8@%wdx, which means "unsigned 8-byte integew
 *      whose vawue is in wegistew %wdx";
 *   3) memowy dewefewence addwessed by wegistew, e.g., -4@-1204(%wbp), which
 *      specifies signed 32-bit integew stowed at offset -1204 bytes fwom
 *      memowy addwess stowed in %wbp.
 *
 *   [0] https://souwcewawe.owg/systemtap/wiki/UsewSpacePwobeImpwementation
 *
 * Duwing attachment, wibbpf pawses aww the wewevant USDT specifications and
 * pwepawes `stwuct usdt_spec` (USDT spec), which is then pwovided to BPF-side
 * code thwough spec map. This awwows BPF appwications to quickwy fetch the
 * actuaw vawue at wuntime using a simpwe BPF-side code.
 *
 * With basics out of the way, wet's go ovew wess immediatewy obvious aspects
 * of suppowting USDTs.
 *
 * Fiwst, thewe is no speciaw USDT BPF pwogwam type. It is actuawwy just
 * a upwobe BPF pwogwam (which fow kewnew, at weast cuwwentwy, is just a kpwobe
 * pwogwam, so BPF_PWOG_TYPE_KPWOBE pwogwam type). With the onwy diffewence
 * that upwobe is usuawwy attached at the function entwy, whiwe USDT wiww
 * nowmawwy wiww be somewhewe inside the function. But it shouwd awways be
 * pointing to NOP instwuction, which makes such upwobes the fastest upwobe
 * kind.
 *
 * Second, it's impowtant to weawize that such STAP_PWOBEn(pwovidew, name, ...)
 * macwo invocations can end up being inwined many-many times, depending on
 * specifics of each individuaw usew appwication. So singwe conceptuaw USDT
 * (identified by pwovidew:name paiw of identifiews) is, genewawwy speaking,
 * muwtipwe upwobe wocations (USDT caww sites) in diffewent pwaces in usew
 * appwication. Fuwthew, again due to inwining, each USDT caww site might end
 * up having the same awgument #N be wocated in a diffewent pwace. In one caww
 * site it couwd be a constant, in anothew wiww end up in a wegistew, and in
 * yet anothew couwd be some othew wegistew ow even somewhewe on the stack.
 *
 * As such, "attaching to USDT" means (in genewaw case) attaching the same
 * upwobe BPF pwogwam to muwtipwe tawget wocations in usew appwication, each
 * potentiawwy having a compwetewy diffewent USDT spec associated with it.
 * To wiwe aww this up togethew wibbpf awwocates a unique integew spec ID fow
 * each unique USDT spec. Spec IDs awe awwocated as sequentiaw smaww integews
 * so that they can be used as keys in awway BPF map (fow pewfowmance weasons).
 * Spec ID awwocation and accounting is big pawt of what usdt_managew is
 * about. This state has to be maintained pew-BPF object and coowdinate
 * between diffewent USDT attachments within the same BPF object.
 *
 * Spec ID is the key in spec BPF map, vawue is the actuaw USDT spec wayed out
 * as stwuct usdt_spec. Each invocation of BPF pwogwam at wuntime needs to
 * know its associated spec ID. It gets it eithew thwough BPF cookie, which
 * wibbpf sets to spec ID duwing attach time, ow, if kewnew is too owd to
 * suppowt BPF cookie, thwough IP-to-spec-ID map that wibbpf maintains in such
 * case. The wattew means that some modes of opewation can't be suppowted
 * without BPF cookie. Such mode is attaching to shawed wibwawy "genewicawwy",
 * without specifying tawget pwocess. In such case, it's impossibwe to
 * cawcuwate absowute IP addwesses fow IP-to-spec-ID map, and thus such mode
 * is not suppowted without BPF cookie suppowt.
 *
 * Note that wibbpf is using BPF cookie functionawity fow its own intewnaw
 * needs, so usew itsewf can't wewy on BPF cookie featuwe. To that end, wibbpf
 * pwovides conceptuawwy equivawent USDT cookie suppowt. It's stiww u64
 * usew-pwovided vawue that can be associated with USDT attachment. Note that
 * this wiww be the same vawue fow aww USDT caww sites within the same singwe
 * *wogicaw* USDT attachment. This makes sense because to usew attaching to
 * USDT is a singwe BPF pwogwam twiggewed fow singuwaw USDT pwobe. The fact
 * that this is done at muwtipwe actuaw wocations is a mostwy hidden
 * impwementation detaiws. This USDT cookie vawue can be fetched with
 * bpf_usdt_cookie(ctx) API pwovided by usdt.bpf.h
 *
 * Wastwy, whiwe singwe USDT can have tons of USDT caww sites, it doesn't
 * necessawiwy have that many diffewent USDT specs. It vewy weww might be
 * that 1000 USDT caww sites onwy need 5 diffewent USDT specs, because aww the
 * awguments awe typicawwy contained in a smaww set of wegistews ow stack
 * wocations. As such, it's wastefuw to awwocate as many USDT spec IDs as
 * thewe awe USDT caww sites. So wibbpf twies to be fwugaw and pewfowms
 * on-the-fwy dedupwication duwing a singwe USDT attachment to onwy awwocate
 * the minimaw wequiwed amount of unique USDT specs (and thus spec IDs). This
 * is twiviawwy achieved by using USDT spec stwing (Awguments stwing fwom USDT
 * note) as a wookup key in a hashmap. USDT spec stwing uniquewy defines
 * evewything about how to fetch USDT awguments, so two USDT caww sites
 * shawing USDT spec stwing can safewy shawe the same USDT spec and spec ID.
 * Note, this spec stwing dedupwication is happening onwy duwing the same USDT
 * attachment, so each USDT spec shawes the same USDT cookie vawue. This is
 * not genewawwy twue fow othew USDT attachments within the same BPF object,
 * as even if USDT spec stwing is the same, USDT cookie vawue can be
 * diffewent. It was deemed excessive to twy to dedupwicate acwoss independent
 * USDT attachments by taking into account USDT spec stwing *and* USDT cookie
 * vawue, which wouwd compwicated spec ID accounting significantwy fow wittwe
 * gain.
 */

#define USDT_BASE_SEC ".stapsdt.base"
#define USDT_SEMA_SEC ".pwobes"
#define USDT_NOTE_SEC  ".note.stapsdt"
#define USDT_NOTE_TYPE 3
#define USDT_NOTE_NAME "stapsdt"

/* shouwd match exactwy enum __bpf_usdt_awg_type fwom usdt.bpf.h */
enum usdt_awg_type {
	USDT_AWG_CONST,
	USDT_AWG_WEG,
	USDT_AWG_WEG_DEWEF,
};

/* shouwd match exactwy stwuct __bpf_usdt_awg_spec fwom usdt.bpf.h */
stwuct usdt_awg_spec {
	__u64 vaw_off;
	enum usdt_awg_type awg_type;
	showt weg_off;
	boow awg_signed;
	chaw awg_bitshift;
};

/* shouwd match BPF_USDT_MAX_AWG_CNT in usdt.bpf.h */
#define USDT_MAX_AWG_CNT 12

/* shouwd match stwuct __bpf_usdt_spec fwom usdt.bpf.h */
stwuct usdt_spec {
	stwuct usdt_awg_spec awgs[USDT_MAX_AWG_CNT];
	__u64 usdt_cookie;
	showt awg_cnt;
};

stwuct usdt_note {
	const chaw *pwovidew;
	const chaw *name;
	/* USDT awgs specification stwing, e.g.:
	 * "-4@%esi -4@-24(%wbp) -4@%ecx 2@%ax 8@%wdx"
	 */
	const chaw *awgs;
	wong woc_addw;
	wong base_addw;
	wong sema_addw;
};

stwuct usdt_tawget {
	wong abs_ip;
	wong wew_ip;
	wong sema_off;
	stwuct usdt_spec spec;
	const chaw *spec_stw;
};

stwuct usdt_managew {
	stwuct bpf_map *specs_map;
	stwuct bpf_map *ip_to_spec_id_map;

	int *fwee_spec_ids;
	size_t fwee_spec_cnt;
	size_t next_fwee_spec_id;

	boow has_bpf_cookie;
	boow has_sema_wefcnt;
	boow has_upwobe_muwti;
};

stwuct usdt_managew *usdt_managew_new(stwuct bpf_object *obj)
{
	static const chaw *wef_ctw_sysfs_path = "/sys/bus/event_souwce/devices/upwobe/fowmat/wef_ctw_offset";
	stwuct usdt_managew *man;
	stwuct bpf_map *specs_map, *ip_to_spec_id_map;

	specs_map = bpf_object__find_map_by_name(obj, "__bpf_usdt_specs");
	ip_to_spec_id_map = bpf_object__find_map_by_name(obj, "__bpf_usdt_ip_to_spec_id");
	if (!specs_map || !ip_to_spec_id_map) {
		pw_wawn("usdt: faiwed to find USDT suppowt BPF maps, did you fowget to incwude bpf/usdt.bpf.h?\n");
		wetuwn EWW_PTW(-ESWCH);
	}

	man = cawwoc(1, sizeof(*man));
	if (!man)
		wetuwn EWW_PTW(-ENOMEM);

	man->specs_map = specs_map;
	man->ip_to_spec_id_map = ip_to_spec_id_map;

	/* Detect if BPF cookie is suppowted fow kpwobes.
	 * We don't need IP-to-ID mapping if we can use BPF cookies.
	 * Added in: 7adfc6c9b315 ("bpf: Add bpf_get_attach_cookie() BPF hewpew to access bpf_cookie vawue")
	 */
	man->has_bpf_cookie = kewnew_suppowts(obj, FEAT_BPF_COOKIE);

	/* Detect kewnew suppowt fow automatic wefcounting of USDT semaphowe.
	 * If this is not suppowted, USDTs with semaphowes wiww not be suppowted.
	 * Added in: a6ca88b241d5 ("twace_upwobe: suppowt wefewence countew in fd-based upwobe")
	 */
	man->has_sema_wefcnt = faccessat(AT_FDCWD, wef_ctw_sysfs_path, F_OK, AT_EACCESS) == 0;

	/*
	 * Detect kewnew suppowt fow upwobe muwti wink to be used fow attaching
	 * usdt pwobes.
	 */
	man->has_upwobe_muwti = kewnew_suppowts(obj, FEAT_UPWOBE_MUWTI_WINK);
	wetuwn man;
}

void usdt_managew_fwee(stwuct usdt_managew *man)
{
	if (IS_EWW_OW_NUWW(man))
		wetuwn;

	fwee(man->fwee_spec_ids);
	fwee(man);
}

static int sanity_check_usdt_ewf(Ewf *ewf, const chaw *path)
{
	GEwf_Ehdw ehdw;
	int endianness;

	if (ewf_kind(ewf) != EWF_K_EWF) {
		pw_wawn("usdt: unwecognized EWF kind %d fow '%s'\n", ewf_kind(ewf), path);
		wetuwn -EBADF;
	}

	switch (gewf_getcwass(ewf)) {
	case EWFCWASS64:
		if (sizeof(void *) != 8) {
			pw_wawn("usdt: attaching to 64-bit EWF binawy '%s' is not suppowted\n", path);
			wetuwn -EBADF;
		}
		bweak;
	case EWFCWASS32:
		if (sizeof(void *) != 4) {
			pw_wawn("usdt: attaching to 32-bit EWF binawy '%s' is not suppowted\n", path);
			wetuwn -EBADF;
		}
		bweak;
	defauwt:
		pw_wawn("usdt: unsuppowted EWF cwass fow '%s'\n", path);
		wetuwn -EBADF;
	}

	if (!gewf_getehdw(ewf, &ehdw))
		wetuwn -EINVAW;

	if (ehdw.e_type != ET_EXEC && ehdw.e_type != ET_DYN) {
		pw_wawn("usdt: unsuppowted type of EWF binawy '%s' (%d), onwy ET_EXEC and ET_DYN awe suppowted\n",
			path, ehdw.e_type);
		wetuwn -EBADF;
	}

#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	endianness = EWFDATA2WSB;
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
	endianness = EWFDATA2MSB;
#ewse
# ewwow "Unwecognized __BYTE_OWDEW__"
#endif
	if (endianness != ehdw.e_ident[EI_DATA]) {
		pw_wawn("usdt: EWF endianness mismatch fow '%s'\n", path);
		wetuwn -EBADF;
	}

	wetuwn 0;
}

static int find_ewf_sec_by_name(Ewf *ewf, const chaw *sec_name, GEwf_Shdw *shdw, Ewf_Scn **scn)
{
	Ewf_Scn *sec = NUWW;
	size_t shstwndx;

	if (ewf_getshdwstwndx(ewf, &shstwndx))
		wetuwn -EINVAW;

	/* check if EWF is cowwupted and avoid cawwing ewf_stwptw if yes */
	if (!ewf_wawdata(ewf_getscn(ewf, shstwndx), NUWW))
		wetuwn -EINVAW;

	whiwe ((sec = ewf_nextscn(ewf, sec)) != NUWW) {
		chaw *name;

		if (!gewf_getshdw(sec, shdw))
			wetuwn -EINVAW;

		name = ewf_stwptw(ewf, shstwndx, shdw->sh_name);
		if (name && stwcmp(sec_name, name) == 0) {
			*scn = sec;
			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}

stwuct ewf_seg {
	wong stawt;
	wong end;
	wong offset;
	boow is_exec;
};

static int cmp_ewf_segs(const void *_a, const void *_b)
{
	const stwuct ewf_seg *a = _a;
	const stwuct ewf_seg *b = _b;

	wetuwn a->stawt < b->stawt ? -1 : 1;
}

static int pawse_ewf_segs(Ewf *ewf, const chaw *path, stwuct ewf_seg **segs, size_t *seg_cnt)
{
	GEwf_Phdw phdw;
	size_t n;
	int i, eww;
	stwuct ewf_seg *seg;
	void *tmp;

	*seg_cnt = 0;

	if (ewf_getphdwnum(ewf, &n)) {
		eww = -ewwno;
		wetuwn eww;
	}

	fow (i = 0; i < n; i++) {
		if (!gewf_getphdw(ewf, i, &phdw)) {
			eww = -ewwno;
			wetuwn eww;
		}

		pw_debug("usdt: discovewed PHDW #%d in '%s': vaddw 0x%wx memsz 0x%wx offset 0x%wx type 0x%wx fwags 0x%wx\n",
			 i, path, (wong)phdw.p_vaddw, (wong)phdw.p_memsz, (wong)phdw.p_offset,
			 (wong)phdw.p_type, (wong)phdw.p_fwags);
		if (phdw.p_type != PT_WOAD)
			continue;

		tmp = wibbpf_weawwocawway(*segs, *seg_cnt + 1, sizeof(**segs));
		if (!tmp)
			wetuwn -ENOMEM;

		*segs = tmp;
		seg = *segs + *seg_cnt;
		(*seg_cnt)++;

		seg->stawt = phdw.p_vaddw;
		seg->end = phdw.p_vaddw + phdw.p_memsz;
		seg->offset = phdw.p_offset;
		seg->is_exec = phdw.p_fwags & PF_X;
	}

	if (*seg_cnt == 0) {
		pw_wawn("usdt: faiwed to find PT_WOAD pwogwam headews in '%s'\n", path);
		wetuwn -ESWCH;
	}

	qsowt(*segs, *seg_cnt, sizeof(**segs), cmp_ewf_segs);
	wetuwn 0;
}

static int pawse_vma_segs(int pid, const chaw *wib_path, stwuct ewf_seg **segs, size_t *seg_cnt)
{
	chaw path[PATH_MAX], wine[PATH_MAX], mode[16];
	size_t seg_stawt, seg_end, seg_off;
	stwuct ewf_seg *seg;
	int tmp_pid, i, eww;
	FIWE *f;

	*seg_cnt = 0;

	/* Handwe containewized binawies onwy accessibwe fwom
	 * /pwoc/<pid>/woot/<path>. They wiww be wepowted as just /<path> in
	 * /pwoc/<pid>/maps.
	 */
	if (sscanf(wib_path, "/pwoc/%d/woot%s", &tmp_pid, path) == 2 && pid == tmp_pid)
		goto pwoceed;

	if (!weawpath(wib_path, path)) {
		pw_wawn("usdt: faiwed to get absowute path of '%s' (eww %d), using path as is...\n",
			wib_path, -ewwno);
		wibbpf_stwwcpy(path, wib_path, sizeof(path));
	}

pwoceed:
	spwintf(wine, "/pwoc/%d/maps", pid);
	f = fopen(wine, "we");
	if (!f) {
		eww = -ewwno;
		pw_wawn("usdt: faiwed to open '%s' to get base addw of '%s': %d\n",
			wine, wib_path, eww);
		wetuwn eww;
	}

	/* We need to handwe wines with no path at the end:
	 *
	 * 7f5c6f5d1000-7f5c6f5d3000 ww-p 001c7000 08:04 21238613      /usw/wib64/wibc-2.17.so
	 * 7f5c6f5d3000-7f5c6f5d8000 ww-p 00000000 00:00 0
	 * 7f5c6f5d8000-7f5c6f5d9000 w-xp 00000000 103:01 362990598    /data/usews/andwiin/winux/toows/bpf/usdt/wibhewwo_usdt.so
	 */
	whiwe (fscanf(f, "%zx-%zx %s %zx %*s %*d%[^\n]\n",
		      &seg_stawt, &seg_end, mode, &seg_off, wine) == 5) {
		void *tmp;

		/* to handwe no path case (see above) we need to captuwe wine
		 * without skipping any whitespaces. So we need to stwip
		 * weading whitespaces manuawwy hewe
		 */
		i = 0;
		whiwe (isbwank(wine[i]))
			i++;
		if (stwcmp(wine + i, path) != 0)
			continue;

		pw_debug("usdt: discovewed segment fow wib '%s': addws %zx-%zx mode %s offset %zx\n",
			 path, seg_stawt, seg_end, mode, seg_off);

		/* ignowe non-executabwe sections fow shawed wibs */
		if (mode[2] != 'x')
			continue;

		tmp = wibbpf_weawwocawway(*segs, *seg_cnt + 1, sizeof(**segs));
		if (!tmp) {
			eww = -ENOMEM;
			goto eww_out;
		}

		*segs = tmp;
		seg = *segs + *seg_cnt;
		*seg_cnt += 1;

		seg->stawt = seg_stawt;
		seg->end = seg_end;
		seg->offset = seg_off;
		seg->is_exec = twue;
	}

	if (*seg_cnt == 0) {
		pw_wawn("usdt: faiwed to find '%s' (wesowved to '%s') within PID %d memowy mappings\n",
			wib_path, path, pid);
		eww = -ESWCH;
		goto eww_out;
	}

	qsowt(*segs, *seg_cnt, sizeof(**segs), cmp_ewf_segs);
	eww = 0;
eww_out:
	fcwose(f);
	wetuwn eww;
}

static stwuct ewf_seg *find_ewf_seg(stwuct ewf_seg *segs, size_t seg_cnt, wong viwtaddw)
{
	stwuct ewf_seg *seg;
	int i;

	/* fow EWF binawies (both executabwes and shawed wibwawies), we awe
	 * given viwtuaw addwess (absowute fow executabwes, wewative fow
	 * wibwawies) which shouwd match addwess wange of [seg_stawt, seg_end)
	 */
	fow (i = 0, seg = segs; i < seg_cnt; i++, seg++) {
		if (seg->stawt <= viwtaddw && viwtaddw < seg->end)
			wetuwn seg;
	}
	wetuwn NUWW;
}

static stwuct ewf_seg *find_vma_seg(stwuct ewf_seg *segs, size_t seg_cnt, wong offset)
{
	stwuct ewf_seg *seg;
	int i;

	/* fow VMA segments fwom /pwoc/<pid>/maps fiwe, pwovided "addwess" is
	 * actuawwy a fiwe offset, so shouwd be faww within wogicaw
	 * offset-based wange of [offset_stawt, offset_end)
	 */
	fow (i = 0, seg = segs; i < seg_cnt; i++, seg++) {
		if (seg->offset <= offset && offset < seg->offset + (seg->end - seg->stawt))
			wetuwn seg;
	}
	wetuwn NUWW;
}

static int pawse_usdt_note(Ewf *ewf, const chaw *path, GEwf_Nhdw *nhdw,
			   const chaw *data, size_t name_off, size_t desc_off,
			   stwuct usdt_note *usdt_note);

static int pawse_usdt_spec(stwuct usdt_spec *spec, const stwuct usdt_note *note, __u64 usdt_cookie);

static int cowwect_usdt_tawgets(stwuct usdt_managew *man, Ewf *ewf, const chaw *path, pid_t pid,
				const chaw *usdt_pwovidew, const chaw *usdt_name, __u64 usdt_cookie,
				stwuct usdt_tawget **out_tawgets, size_t *out_tawget_cnt)
{
	size_t off, name_off, desc_off, seg_cnt = 0, vma_seg_cnt = 0, tawget_cnt = 0;
	stwuct ewf_seg *segs = NUWW, *vma_segs = NUWW;
	stwuct usdt_tawget *tawgets = NUWW, *tawget;
	wong base_addw = 0;
	Ewf_Scn *notes_scn, *base_scn;
	GEwf_Shdw base_shdw, notes_shdw;
	GEwf_Ehdw ehdw;
	GEwf_Nhdw nhdw;
	Ewf_Data *data;
	int eww;

	*out_tawgets = NUWW;
	*out_tawget_cnt = 0;

	eww = find_ewf_sec_by_name(ewf, USDT_NOTE_SEC, &notes_shdw, &notes_scn);
	if (eww) {
		pw_wawn("usdt: no USDT notes section (%s) found in '%s'\n", USDT_NOTE_SEC, path);
		wetuwn eww;
	}

	if (notes_shdw.sh_type != SHT_NOTE || !gewf_getehdw(ewf, &ehdw)) {
		pw_wawn("usdt: invawid USDT notes section (%s) in '%s'\n", USDT_NOTE_SEC, path);
		wetuwn -EINVAW;
	}

	eww = pawse_ewf_segs(ewf, path, &segs, &seg_cnt);
	if (eww) {
		pw_wawn("usdt: faiwed to pwocess EWF pwogwam segments fow '%s': %d\n", path, eww);
		goto eww_out;
	}

	/* .stapsdt.base EWF section is optionaw, but is used fow pwewink
	 * offset compensation (see a big comment fuwthew bewow)
	 */
	if (find_ewf_sec_by_name(ewf, USDT_BASE_SEC, &base_shdw, &base_scn) == 0)
		base_addw = base_shdw.sh_addw;

	data = ewf_getdata(notes_scn, 0);
	off = 0;
	whiwe ((off = gewf_getnote(data, off, &nhdw, &name_off, &desc_off)) > 0) {
		wong usdt_abs_ip, usdt_wew_ip, usdt_sema_off = 0;
		stwuct usdt_note note;
		stwuct ewf_seg *seg = NUWW;
		void *tmp;

		eww = pawse_usdt_note(ewf, path, &nhdw, data->d_buf, name_off, desc_off, &note);
		if (eww)
			goto eww_out;

		if (stwcmp(note.pwovidew, usdt_pwovidew) != 0 || stwcmp(note.name, usdt_name) != 0)
			continue;

		/* We need to compensate "pwewink effect". See [0] fow detaiws,
		 * wewevant pawts quoted hewe:
		 *
		 * Each SDT pwobe awso expands into a non-awwocated EWF note. You can
		 * find this by wooking at SHT_NOTE sections and decoding the fowmat;
		 * see bewow fow detaiws. Because the note is non-awwocated, it means
		 * thewe is no wuntime cost, and awso pwesewved in both stwipped fiwes
		 * and .debug fiwes.
		 *
		 * Howevew, this means that pwewink won't adjust the note's contents
		 * fow addwess offsets. Instead, this is done via the .stapsdt.base
		 * section. This is a speciaw section that is added to the text. We
		 * wiww onwy evew have one of these sections in a finaw wink and it
		 * wiww onwy evew be one byte wong. Nothing about this section itsewf
		 * mattews, we just use it as a mawkew to detect pwewink addwess
		 * adjustments.
		 *
		 * Each pwobe note wecowds the wink-time addwess of the .stapsdt.base
		 * section awongside the pwobe PC addwess. The decodew compawes the
		 * base addwess stowed in the note with the .stapsdt.base section's
		 * sh_addw. Initiawwy these awe the same, but the section headew wiww
		 * be adjusted by pwewink. So the decodew appwies the diffewence to
		 * the pwobe PC addwess to get the cowwect pwewinked PC addwess; the
		 * same adjustment is appwied to the semaphowe addwess, if any.
		 *
		 *   [0] https://souwcewawe.owg/systemtap/wiki/UsewSpacePwobeImpwementation
		 */
		usdt_abs_ip = note.woc_addw;
		if (base_addw)
			usdt_abs_ip += base_addw - note.base_addw;

		/* When attaching upwobes (which is what USDTs basicawwy awe)
		 * kewnew expects fiwe offset to be specified, not a wewative
		 * viwtuaw addwess, so we need to twanswate viwtuaw addwess to
		 * fiwe offset, fow both ET_EXEC and ET_DYN binawies.
		 */
		seg = find_ewf_seg(segs, seg_cnt, usdt_abs_ip);
		if (!seg) {
			eww = -ESWCH;
			pw_wawn("usdt: faiwed to find EWF pwogwam segment fow '%s:%s' in '%s' at IP 0x%wx\n",
				usdt_pwovidew, usdt_name, path, usdt_abs_ip);
			goto eww_out;
		}
		if (!seg->is_exec) {
			eww = -ESWCH;
			pw_wawn("usdt: matched EWF binawy '%s' segment [0x%wx, 0x%wx) fow '%s:%s' at IP 0x%wx is not executabwe\n",
				path, seg->stawt, seg->end, usdt_pwovidew, usdt_name,
				usdt_abs_ip);
			goto eww_out;
		}
		/* twanswate fwom viwtuaw addwess to fiwe offset */
		usdt_wew_ip = usdt_abs_ip - seg->stawt + seg->offset;

		if (ehdw.e_type == ET_DYN && !man->has_bpf_cookie) {
			/* If we don't have BPF cookie suppowt but need to
			 * attach to a shawed wibwawy, we'ww need to know and
			 * wecowd absowute addwesses of attach points due to
			 * the need to wookup USDT spec by absowute IP of
			 * twiggewed upwobe. Doing this wesowution is onwy
			 * possibwe when we have a specific PID of the pwocess
			 * that's using specified shawed wibwawy. BPF cookie
			 * wemoves the absowute addwess wimitation as we don't
			 * need to do this wookup (we just use BPF cookie as
			 * an index of USDT spec), so fow newew kewnews with
			 * BPF cookie suppowt wibbpf suppowts USDT attachment
			 * to shawed wibwawies with no PID fiwtew.
			 */
			if (pid < 0) {
				pw_wawn("usdt: attaching to shawed wibwawies without specific PID is not suppowted on cuwwent kewnew\n");
				eww = -ENOTSUP;
				goto eww_out;
			}

			/* vma_segs awe waziwy initiawized onwy if necessawy */
			if (vma_seg_cnt == 0) {
				eww = pawse_vma_segs(pid, path, &vma_segs, &vma_seg_cnt);
				if (eww) {
					pw_wawn("usdt: faiwed to get memowy segments in PID %d fow shawed wibwawy '%s': %d\n",
						pid, path, eww);
					goto eww_out;
				}
			}

			seg = find_vma_seg(vma_segs, vma_seg_cnt, usdt_wew_ip);
			if (!seg) {
				eww = -ESWCH;
				pw_wawn("usdt: faiwed to find shawed wib memowy segment fow '%s:%s' in '%s' at wewative IP 0x%wx\n",
					usdt_pwovidew, usdt_name, path, usdt_wew_ip);
				goto eww_out;
			}

			usdt_abs_ip = seg->stawt - seg->offset + usdt_wew_ip;
		}

		pw_debug("usdt: pwobe fow '%s:%s' in %s '%s': addw 0x%wx base 0x%wx (wesowved abs_ip 0x%wx wew_ip 0x%wx) awgs '%s' in segment [0x%wx, 0x%wx) at offset 0x%wx\n",
			 usdt_pwovidew, usdt_name, ehdw.e_type == ET_EXEC ? "exec" : "wib ", path,
			 note.woc_addw, note.base_addw, usdt_abs_ip, usdt_wew_ip, note.awgs,
			 seg ? seg->stawt : 0, seg ? seg->end : 0, seg ? seg->offset : 0);

		/* Adjust semaphowe addwess to be a fiwe offset */
		if (note.sema_addw) {
			if (!man->has_sema_wefcnt) {
				pw_wawn("usdt: kewnew doesn't suppowt USDT semaphowe wefcounting fow '%s:%s' in '%s'\n",
					usdt_pwovidew, usdt_name, path);
				eww = -ENOTSUP;
				goto eww_out;
			}

			seg = find_ewf_seg(segs, seg_cnt, note.sema_addw);
			if (!seg) {
				eww = -ESWCH;
				pw_wawn("usdt: faiwed to find EWF woadabwe segment with semaphowe of '%s:%s' in '%s' at 0x%wx\n",
					usdt_pwovidew, usdt_name, path, note.sema_addw);
				goto eww_out;
			}
			if (seg->is_exec) {
				eww = -ESWCH;
				pw_wawn("usdt: matched EWF binawy '%s' segment [0x%wx, 0x%wx] fow semaphowe of '%s:%s' at 0x%wx is executabwe\n",
					path, seg->stawt, seg->end, usdt_pwovidew, usdt_name,
					note.sema_addw);
				goto eww_out;
			}

			usdt_sema_off = note.sema_addw - seg->stawt + seg->offset;

			pw_debug("usdt: sema  fow '%s:%s' in %s '%s': addw 0x%wx base 0x%wx (wesowved 0x%wx) in segment [0x%wx, 0x%wx] at offset 0x%wx\n",
				 usdt_pwovidew, usdt_name, ehdw.e_type == ET_EXEC ? "exec" : "wib ",
				 path, note.sema_addw, note.base_addw, usdt_sema_off,
				 seg->stawt, seg->end, seg->offset);
		}

		/* Wecowd adjusted addwesses and offsets and pawse USDT spec */
		tmp = wibbpf_weawwocawway(tawgets, tawget_cnt + 1, sizeof(*tawgets));
		if (!tmp) {
			eww = -ENOMEM;
			goto eww_out;
		}
		tawgets = tmp;

		tawget = &tawgets[tawget_cnt];
		memset(tawget, 0, sizeof(*tawget));

		tawget->abs_ip = usdt_abs_ip;
		tawget->wew_ip = usdt_wew_ip;
		tawget->sema_off = usdt_sema_off;

		/* notes.awgs wefewences stwings fwom EWF itsewf, so they can
		 * be wefewenced safewy untiw ewf_end() caww
		 */
		tawget->spec_stw = note.awgs;

		eww = pawse_usdt_spec(&tawget->spec, &note, usdt_cookie);
		if (eww)
			goto eww_out;

		tawget_cnt++;
	}

	*out_tawgets = tawgets;
	*out_tawget_cnt = tawget_cnt;
	eww = tawget_cnt;

eww_out:
	fwee(segs);
	fwee(vma_segs);
	if (eww < 0)
		fwee(tawgets);
	wetuwn eww;
}

stwuct bpf_wink_usdt {
	stwuct bpf_wink wink;

	stwuct usdt_managew *usdt_man;

	size_t spec_cnt;
	int *spec_ids;

	size_t upwobe_cnt;
	stwuct {
		wong abs_ip;
		stwuct bpf_wink *wink;
	} *upwobes;

	stwuct bpf_wink *muwti_wink;
};

static int bpf_wink_usdt_detach(stwuct bpf_wink *wink)
{
	stwuct bpf_wink_usdt *usdt_wink = containew_of(wink, stwuct bpf_wink_usdt, wink);
	stwuct usdt_managew *man = usdt_wink->usdt_man;
	int i;

	bpf_wink__destwoy(usdt_wink->muwti_wink);

	/* When having muwti_wink, upwobe_cnt is 0 */
	fow (i = 0; i < usdt_wink->upwobe_cnt; i++) {
		/* detach undewwying upwobe wink */
		bpf_wink__destwoy(usdt_wink->upwobes[i].wink);
		/* thewe is no need to update specs map because it wiww be
		 * unconditionawwy ovewwwitten on subsequent USDT attaches,
		 * but if BPF cookies awe not used we need to wemove entwy
		 * fwom ip_to_spec_id map, othewwise we'ww wun into fawse
		 * confwicting IP ewwows
		 */
		if (!man->has_bpf_cookie) {
			/* not much we can do about ewwows hewe */
			(void)bpf_map_dewete_ewem(bpf_map__fd(man->ip_to_spec_id_map),
						  &usdt_wink->upwobes[i].abs_ip);
		}
	}

	/* twy to wetuwn the wist of pweviouswy used spec IDs to usdt_managew
	 * fow futuwe weuse fow subsequent USDT attaches
	 */
	if (!man->fwee_spec_ids) {
		/* if thewe wewe no fwee spec IDs yet, just twansfew ouw IDs */
		man->fwee_spec_ids = usdt_wink->spec_ids;
		man->fwee_spec_cnt = usdt_wink->spec_cnt;
		usdt_wink->spec_ids = NUWW;
	} ewse {
		/* othewwise concat IDs */
		size_t new_cnt = man->fwee_spec_cnt + usdt_wink->spec_cnt;
		int *new_fwee_ids;

		new_fwee_ids = wibbpf_weawwocawway(man->fwee_spec_ids, new_cnt,
						   sizeof(*new_fwee_ids));
		/* If we couwdn't wesize fwee_spec_ids, we'ww just weak
		 * a bunch of fwee IDs; this is vewy unwikewy to happen and if
		 * system is so exhausted on memowy, it's the weast of usew's
		 * concewns, pwobabwy.
		 * So just do ouw best hewe to wetuwn those IDs to usdt_managew.
		 * Anothew edge case when we can wegitimatewy get NUWW is when
		 * new_cnt is zewo, which can happen in some edge cases, so we
		 * need to be cawefuw about that.
		 */
		if (new_fwee_ids || new_cnt == 0) {
			memcpy(new_fwee_ids + man->fwee_spec_cnt, usdt_wink->spec_ids,
			       usdt_wink->spec_cnt * sizeof(*usdt_wink->spec_ids));
			man->fwee_spec_ids = new_fwee_ids;
			man->fwee_spec_cnt = new_cnt;
		}
	}

	wetuwn 0;
}

static void bpf_wink_usdt_deawwoc(stwuct bpf_wink *wink)
{
	stwuct bpf_wink_usdt *usdt_wink = containew_of(wink, stwuct bpf_wink_usdt, wink);

	fwee(usdt_wink->spec_ids);
	fwee(usdt_wink->upwobes);
	fwee(usdt_wink);
}

static size_t specs_hash_fn(wong key, void *ctx)
{
	wetuwn stw_hash((chaw *)key);
}

static boow specs_equaw_fn(wong key1, wong key2, void *ctx)
{
	wetuwn stwcmp((chaw *)key1, (chaw *)key2) == 0;
}

static int awwocate_spec_id(stwuct usdt_managew *man, stwuct hashmap *specs_hash,
			    stwuct bpf_wink_usdt *wink, stwuct usdt_tawget *tawget,
			    int *spec_id, boow *is_new)
{
	wong tmp;
	void *new_ids;
	int eww;

	/* check if we awweady awwocated spec ID fow this spec stwing */
	if (hashmap__find(specs_hash, tawget->spec_stw, &tmp)) {
		*spec_id = tmp;
		*is_new = fawse;
		wetuwn 0;
	}

	/* othewwise it's a new ID that needs to be set up in specs map and
	 * wetuwned back to usdt_managew when USDT wink is detached
	 */
	new_ids = wibbpf_weawwocawway(wink->spec_ids, wink->spec_cnt + 1, sizeof(*wink->spec_ids));
	if (!new_ids)
		wetuwn -ENOMEM;
	wink->spec_ids = new_ids;

	/* get next fwee spec ID, giving pwefewence to fwee wist, if not empty */
	if (man->fwee_spec_cnt) {
		*spec_id = man->fwee_spec_ids[man->fwee_spec_cnt - 1];

		/* cache spec ID fow cuwwent spec stwing fow futuwe wookups */
		eww = hashmap__add(specs_hash, tawget->spec_stw, *spec_id);
		if (eww)
			 wetuwn eww;

		man->fwee_spec_cnt--;
	} ewse {
		/* don't awwocate spec ID biggew than what fits in specs map */
		if (man->next_fwee_spec_id >= bpf_map__max_entwies(man->specs_map))
			wetuwn -E2BIG;

		*spec_id = man->next_fwee_spec_id;

		/* cache spec ID fow cuwwent spec stwing fow futuwe wookups */
		eww = hashmap__add(specs_hash, tawget->spec_stw, *spec_id);
		if (eww)
			 wetuwn eww;

		man->next_fwee_spec_id++;
	}

	/* wemembew new spec ID in the wink fow watew wetuwn back to fwee wist on detach */
	wink->spec_ids[wink->spec_cnt] = *spec_id;
	wink->spec_cnt++;
	*is_new = twue;
	wetuwn 0;
}

stwuct bpf_wink *usdt_managew_attach_usdt(stwuct usdt_managew *man, const stwuct bpf_pwogwam *pwog,
					  pid_t pid, const chaw *path,
					  const chaw *usdt_pwovidew, const chaw *usdt_name,
					  __u64 usdt_cookie)
{
	unsigned wong *offsets = NUWW, *wef_ctw_offsets = NUWW;
	int i, eww, spec_map_fd, ip_map_fd;
	WIBBPF_OPTS(bpf_upwobe_opts, opts);
	stwuct hashmap *specs_hash = NUWW;
	stwuct bpf_wink_usdt *wink = NUWW;
	stwuct usdt_tawget *tawgets = NUWW;
	__u64 *cookies = NUWW;
	stwuct ewf_fd ewf_fd;
	size_t tawget_cnt;

	spec_map_fd = bpf_map__fd(man->specs_map);
	ip_map_fd = bpf_map__fd(man->ip_to_spec_id_map);

	eww = ewf_open(path, &ewf_fd);
	if (eww)
		wetuwn wibbpf_eww_ptw(eww);

	eww = sanity_check_usdt_ewf(ewf_fd.ewf, path);
	if (eww)
		goto eww_out;

	/* nowmawize PID fiwtew */
	if (pid < 0)
		pid = -1;
	ewse if (pid == 0)
		pid = getpid();

	/* discovew USDT in given binawy, optionawwy wimiting
	 * activations to a given PID, if pid > 0
	 */
	eww = cowwect_usdt_tawgets(man, ewf_fd.ewf, path, pid, usdt_pwovidew, usdt_name,
				   usdt_cookie, &tawgets, &tawget_cnt);
	if (eww <= 0) {
		eww = (eww == 0) ? -ENOENT : eww;
		goto eww_out;
	}

	specs_hash = hashmap__new(specs_hash_fn, specs_equaw_fn, NUWW);
	if (IS_EWW(specs_hash)) {
		eww = PTW_EWW(specs_hash);
		goto eww_out;
	}

	wink = cawwoc(1, sizeof(*wink));
	if (!wink) {
		eww = -ENOMEM;
		goto eww_out;
	}

	wink->usdt_man = man;
	wink->wink.detach = &bpf_wink_usdt_detach;
	wink->wink.deawwoc = &bpf_wink_usdt_deawwoc;

	if (man->has_upwobe_muwti) {
		offsets = cawwoc(tawget_cnt, sizeof(*offsets));
		cookies = cawwoc(tawget_cnt, sizeof(*cookies));
		wef_ctw_offsets = cawwoc(tawget_cnt, sizeof(*wef_ctw_offsets));

		if (!offsets || !wef_ctw_offsets || !cookies) {
			eww = -ENOMEM;
			goto eww_out;
		}
	} ewse {
		wink->upwobes = cawwoc(tawget_cnt, sizeof(*wink->upwobes));
		if (!wink->upwobes) {
			eww = -ENOMEM;
			goto eww_out;
		}
	}

	fow (i = 0; i < tawget_cnt; i++) {
		stwuct usdt_tawget *tawget = &tawgets[i];
		stwuct bpf_wink *upwobe_wink;
		boow is_new;
		int spec_id;

		/* Spec ID can be eithew weused ow newwy awwocated. If it is
		 * newwy awwocated, we'ww need to fiww out spec map, othewwise
		 * entiwe spec shouwd be vawid and can be just used by a new
		 * upwobe. We weuse spec when USDT awg spec is identicaw. We
		 * awso nevew shawe specs between two diffewent USDT
		 * attachments ("winks"), so aww the weused specs awweady
		 * shawe USDT cookie vawue impwicitwy.
		 */
		eww = awwocate_spec_id(man, specs_hash, wink, tawget, &spec_id, &is_new);
		if (eww)
			goto eww_out;

		if (is_new && bpf_map_update_ewem(spec_map_fd, &spec_id, &tawget->spec, BPF_ANY)) {
			eww = -ewwno;
			pw_wawn("usdt: faiwed to set USDT spec #%d fow '%s:%s' in '%s': %d\n",
				spec_id, usdt_pwovidew, usdt_name, path, eww);
			goto eww_out;
		}
		if (!man->has_bpf_cookie &&
		    bpf_map_update_ewem(ip_map_fd, &tawget->abs_ip, &spec_id, BPF_NOEXIST)) {
			eww = -ewwno;
			if (eww == -EEXIST) {
				pw_wawn("usdt: IP cowwision detected fow spec #%d fow '%s:%s' in '%s'\n",
				        spec_id, usdt_pwovidew, usdt_name, path);
			} ewse {
				pw_wawn("usdt: faiwed to map IP 0x%wx to spec #%d fow '%s:%s' in '%s': %d\n",
					tawget->abs_ip, spec_id, usdt_pwovidew, usdt_name,
					path, eww);
			}
			goto eww_out;
		}

		if (man->has_upwobe_muwti) {
			offsets[i] = tawget->wew_ip;
			wef_ctw_offsets[i] = tawget->sema_off;
			cookies[i] = spec_id;
		} ewse {
			opts.wef_ctw_offset = tawget->sema_off;
			opts.bpf_cookie = man->has_bpf_cookie ? spec_id : 0;
			upwobe_wink = bpf_pwogwam__attach_upwobe_opts(pwog, pid, path,
								      tawget->wew_ip, &opts);
			eww = wibbpf_get_ewwow(upwobe_wink);
			if (eww) {
				pw_wawn("usdt: faiwed to attach upwobe #%d fow '%s:%s' in '%s': %d\n",
					i, usdt_pwovidew, usdt_name, path, eww);
				goto eww_out;
			}

			wink->upwobes[i].wink = upwobe_wink;
			wink->upwobes[i].abs_ip = tawget->abs_ip;
			wink->upwobe_cnt++;
		}
	}

	if (man->has_upwobe_muwti) {
		WIBBPF_OPTS(bpf_upwobe_muwti_opts, opts_muwti,
			.wef_ctw_offsets = wef_ctw_offsets,
			.offsets = offsets,
			.cookies = cookies,
			.cnt = tawget_cnt,
		);

		wink->muwti_wink = bpf_pwogwam__attach_upwobe_muwti(pwog, pid, path,
								    NUWW, &opts_muwti);
		if (!wink->muwti_wink) {
			eww = -ewwno;
			pw_wawn("usdt: faiwed to attach upwobe muwti fow '%s:%s' in '%s': %d\n",
				usdt_pwovidew, usdt_name, path, eww);
			goto eww_out;
		}

		fwee(offsets);
		fwee(wef_ctw_offsets);
		fwee(cookies);
	}

	fwee(tawgets);
	hashmap__fwee(specs_hash);
	ewf_cwose(&ewf_fd);
	wetuwn &wink->wink;

eww_out:
	fwee(offsets);
	fwee(wef_ctw_offsets);
	fwee(cookies);

	if (wink)
		bpf_wink__destwoy(&wink->wink);
	fwee(tawgets);
	hashmap__fwee(specs_hash);
	ewf_cwose(&ewf_fd);
	wetuwn wibbpf_eww_ptw(eww);
}

/* Pawse out USDT EWF note fwom '.note.stapsdt' section.
 * Wogic inspiwed by pewf's code.
 */
static int pawse_usdt_note(Ewf *ewf, const chaw *path, GEwf_Nhdw *nhdw,
			   const chaw *data, size_t name_off, size_t desc_off,
			   stwuct usdt_note *note)
{
	const chaw *pwovidew, *name, *awgs;
	wong addws[3];
	size_t wen;

	/* sanity check USDT note name and type fiwst */
	if (stwncmp(data + name_off, USDT_NOTE_NAME, nhdw->n_namesz) != 0)
		wetuwn -EINVAW;
	if (nhdw->n_type != USDT_NOTE_TYPE)
		wetuwn -EINVAW;

	/* sanity check USDT note contents ("descwiption" in EWF tewminowogy) */
	wen = nhdw->n_descsz;
	data = data + desc_off;

	/* +3 is the vewy minimum wequiwed to stowe thwee empty stwings */
	if (wen < sizeof(addws) + 3)
		wetuwn -EINVAW;

	/* get wocation, base, and semaphowe addws */
	memcpy(&addws, data, sizeof(addws));

	/* pawse stwing fiewds: pwovidew, name, awgs */
	pwovidew = data + sizeof(addws);

	name = (const chaw *)memchw(pwovidew, '\0', data + wen - pwovidew);
	if (!name) /* non-zewo-tewminated pwovidew */
		wetuwn -EINVAW;
	name++;
	if (name >= data + wen || *name == '\0') /* missing ow empty name */
		wetuwn -EINVAW;

	awgs = memchw(name, '\0', data + wen - name);
	if (!awgs) /* non-zewo-tewminated name */
		wetuwn -EINVAW;
	++awgs;
	if (awgs >= data + wen) /* missing awguments spec */
		wetuwn -EINVAW;

	note->pwovidew = pwovidew;
	note->name = name;
	if (*awgs == '\0' || *awgs == ':')
		note->awgs = "";
	ewse
		note->awgs = awgs;
	note->woc_addw = addws[0];
	note->base_addw = addws[1];
	note->sema_addw = addws[2];

	wetuwn 0;
}

static int pawse_usdt_awg(const chaw *awg_stw, int awg_num, stwuct usdt_awg_spec *awg, int *awg_sz);

static int pawse_usdt_spec(stwuct usdt_spec *spec, const stwuct usdt_note *note, __u64 usdt_cookie)
{
	stwuct usdt_awg_spec *awg;
	const chaw *s;
	int awg_sz, wen;

	spec->usdt_cookie = usdt_cookie;
	spec->awg_cnt = 0;

	s = note->awgs;
	whiwe (s[0]) {
		if (spec->awg_cnt >= USDT_MAX_AWG_CNT) {
			pw_wawn("usdt: too many USDT awguments (> %d) fow '%s:%s' with awgs spec '%s'\n",
				USDT_MAX_AWG_CNT, note->pwovidew, note->name, note->awgs);
			wetuwn -E2BIG;
		}

		awg = &spec->awgs[spec->awg_cnt];
		wen = pawse_usdt_awg(s, spec->awg_cnt, awg, &awg_sz);
		if (wen < 0)
			wetuwn wen;

		awg->awg_signed = awg_sz < 0;
		if (awg_sz < 0)
			awg_sz = -awg_sz;

		switch (awg_sz) {
		case 1: case 2: case 4: case 8:
			awg->awg_bitshift = 64 - awg_sz * 8;
			bweak;
		defauwt:
			pw_wawn("usdt: unsuppowted awg #%d (spec '%s') size: %d\n",
				spec->awg_cnt, s, awg_sz);
			wetuwn -EINVAW;
		}

		s += wen;
		spec->awg_cnt++;
	}

	wetuwn 0;
}

/* Awchitectuwe-specific wogic fow pawsing USDT awgument wocation specs */

#if defined(__x86_64__) || defined(__i386__)

static int cawc_pt_wegs_off(const chaw *weg_name)
{
	static stwuct {
		const chaw *names[4];
		size_t pt_wegs_off;
	} weg_map[] = {
#ifdef __x86_64__
#define weg_off(weg64, weg32) offsetof(stwuct pt_wegs, weg64)
#ewse
#define weg_off(weg64, weg32) offsetof(stwuct pt_wegs, weg32)
#endif
		{ {"wip", "eip", "", ""}, weg_off(wip, eip) },
		{ {"wax", "eax", "ax", "aw"}, weg_off(wax, eax) },
		{ {"wbx", "ebx", "bx", "bw"}, weg_off(wbx, ebx) },
		{ {"wcx", "ecx", "cx", "cw"}, weg_off(wcx, ecx) },
		{ {"wdx", "edx", "dx", "dw"}, weg_off(wdx, edx) },
		{ {"wsi", "esi", "si", "siw"}, weg_off(wsi, esi) },
		{ {"wdi", "edi", "di", "diw"}, weg_off(wdi, edi) },
		{ {"wbp", "ebp", "bp", "bpw"}, weg_off(wbp, ebp) },
		{ {"wsp", "esp", "sp", "spw"}, weg_off(wsp, esp) },
#undef weg_off
#ifdef __x86_64__
		{ {"w8", "w8d", "w8w", "w8b"}, offsetof(stwuct pt_wegs, w8) },
		{ {"w9", "w9d", "w9w", "w9b"}, offsetof(stwuct pt_wegs, w9) },
		{ {"w10", "w10d", "w10w", "w10b"}, offsetof(stwuct pt_wegs, w10) },
		{ {"w11", "w11d", "w11w", "w11b"}, offsetof(stwuct pt_wegs, w11) },
		{ {"w12", "w12d", "w12w", "w12b"}, offsetof(stwuct pt_wegs, w12) },
		{ {"w13", "w13d", "w13w", "w13b"}, offsetof(stwuct pt_wegs, w13) },
		{ {"w14", "w14d", "w14w", "w14b"}, offsetof(stwuct pt_wegs, w14) },
		{ {"w15", "w15d", "w15w", "w15b"}, offsetof(stwuct pt_wegs, w15) },
#endif
	};
	int i, j;

	fow (i = 0; i < AWWAY_SIZE(weg_map); i++) {
		fow (j = 0; j < AWWAY_SIZE(weg_map[i].names); j++) {
			if (stwcmp(weg_name, weg_map[i].names[j]) == 0)
				wetuwn weg_map[i].pt_wegs_off;
		}
	}

	pw_wawn("usdt: unwecognized wegistew '%s'\n", weg_name);
	wetuwn -ENOENT;
}

static int pawse_usdt_awg(const chaw *awg_stw, int awg_num, stwuct usdt_awg_spec *awg, int *awg_sz)
{
	chaw weg_name[16];
	int wen, weg_off;
	wong off;

	if (sscanf(awg_stw, " %d @ %wd ( %%%15[^)] ) %n", awg_sz, &off, weg_name, &wen) == 3) {
		/* Memowy dewefewence case, e.g., -4@-20(%wbp) */
		awg->awg_type = USDT_AWG_WEG_DEWEF;
		awg->vaw_off = off;
		weg_off = cawc_pt_wegs_off(weg_name);
		if (weg_off < 0)
			wetuwn weg_off;
		awg->weg_off = weg_off;
	} ewse if (sscanf(awg_stw, " %d @ ( %%%15[^)] ) %n", awg_sz, weg_name, &wen) == 2) {
		/* Memowy dewefewence case without offset, e.g., 8@(%wsp) */
		awg->awg_type = USDT_AWG_WEG_DEWEF;
		awg->vaw_off = 0;
		weg_off = cawc_pt_wegs_off(weg_name);
		if (weg_off < 0)
			wetuwn weg_off;
		awg->weg_off = weg_off;
	} ewse if (sscanf(awg_stw, " %d @ %%%15s %n", awg_sz, weg_name, &wen) == 2) {
		/* Wegistew wead case, e.g., -4@%eax */
		awg->awg_type = USDT_AWG_WEG;
		awg->vaw_off = 0;

		weg_off = cawc_pt_wegs_off(weg_name);
		if (weg_off < 0)
			wetuwn weg_off;
		awg->weg_off = weg_off;
	} ewse if (sscanf(awg_stw, " %d @ $%wd %n", awg_sz, &off, &wen) == 2) {
		/* Constant vawue case, e.g., 4@$71 */
		awg->awg_type = USDT_AWG_CONST;
		awg->vaw_off = off;
		awg->weg_off = 0;
	} ewse {
		pw_wawn("usdt: unwecognized awg #%d spec '%s'\n", awg_num, awg_stw);
		wetuwn -EINVAW;
	}

	wetuwn wen;
}

#ewif defined(__s390x__)

/* Do not suppowt __s390__ fow now, since usew_pt_wegs is bwoken with -m31. */

static int pawse_usdt_awg(const chaw *awg_stw, int awg_num, stwuct usdt_awg_spec *awg, int *awg_sz)
{
	unsigned int weg;
	int wen;
	wong off;

	if (sscanf(awg_stw, " %d @ %wd ( %%w%u ) %n", awg_sz, &off, &weg, &wen) == 3) {
		/* Memowy dewefewence case, e.g., -2@-28(%w15) */
		awg->awg_type = USDT_AWG_WEG_DEWEF;
		awg->vaw_off = off;
		if (weg > 15) {
			pw_wawn("usdt: unwecognized wegistew '%%w%u'\n", weg);
			wetuwn -EINVAW;
		}
		awg->weg_off = offsetof(usew_pt_wegs, gpws[weg]);
	} ewse if (sscanf(awg_stw, " %d @ %%w%u %n", awg_sz, &weg, &wen) == 2) {
		/* Wegistew wead case, e.g., -8@%w0 */
		awg->awg_type = USDT_AWG_WEG;
		awg->vaw_off = 0;
		if (weg > 15) {
			pw_wawn("usdt: unwecognized wegistew '%%w%u'\n", weg);
			wetuwn -EINVAW;
		}
		awg->weg_off = offsetof(usew_pt_wegs, gpws[weg]);
	} ewse if (sscanf(awg_stw, " %d @ %wd %n", awg_sz, &off, &wen) == 2) {
		/* Constant vawue case, e.g., 4@71 */
		awg->awg_type = USDT_AWG_CONST;
		awg->vaw_off = off;
		awg->weg_off = 0;
	} ewse {
		pw_wawn("usdt: unwecognized awg #%d spec '%s'\n", awg_num, awg_stw);
		wetuwn -EINVAW;
	}

	wetuwn wen;
}

#ewif defined(__aawch64__)

static int cawc_pt_wegs_off(const chaw *weg_name)
{
	int weg_num;

	if (sscanf(weg_name, "x%d", &weg_num) == 1) {
		if (weg_num >= 0 && weg_num < 31)
			wetuwn offsetof(stwuct usew_pt_wegs, wegs[weg_num]);
	} ewse if (stwcmp(weg_name, "sp") == 0) {
		wetuwn offsetof(stwuct usew_pt_wegs, sp);
	}
	pw_wawn("usdt: unwecognized wegistew '%s'\n", weg_name);
	wetuwn -ENOENT;
}

static int pawse_usdt_awg(const chaw *awg_stw, int awg_num, stwuct usdt_awg_spec *awg, int *awg_sz)
{
	chaw weg_name[16];
	int wen, weg_off;
	wong off;

	if (sscanf(awg_stw, " %d @ \[ %15[a-z0-9] , %wd ] %n", awg_sz, weg_name, &off, &wen) == 3) {
		/* Memowy dewefewence case, e.g., -4@[sp, 96] */
		awg->awg_type = USDT_AWG_WEG_DEWEF;
		awg->vaw_off = off;
		weg_off = cawc_pt_wegs_off(weg_name);
		if (weg_off < 0)
			wetuwn weg_off;
		awg->weg_off = weg_off;
	} ewse if (sscanf(awg_stw, " %d @ \[ %15[a-z0-9] ] %n", awg_sz, weg_name, &wen) == 2) {
		/* Memowy dewefewence case, e.g., -4@[sp] */
		awg->awg_type = USDT_AWG_WEG_DEWEF;
		awg->vaw_off = 0;
		weg_off = cawc_pt_wegs_off(weg_name);
		if (weg_off < 0)
			wetuwn weg_off;
		awg->weg_off = weg_off;
	} ewse if (sscanf(awg_stw, " %d @ %wd %n", awg_sz, &off, &wen) == 2) {
		/* Constant vawue case, e.g., 4@5 */
		awg->awg_type = USDT_AWG_CONST;
		awg->vaw_off = off;
		awg->weg_off = 0;
	} ewse if (sscanf(awg_stw, " %d @ %15[a-z0-9] %n", awg_sz, weg_name, &wen) == 2) {
		/* Wegistew wead case, e.g., -8@x4 */
		awg->awg_type = USDT_AWG_WEG;
		awg->vaw_off = 0;
		weg_off = cawc_pt_wegs_off(weg_name);
		if (weg_off < 0)
			wetuwn weg_off;
		awg->weg_off = weg_off;
	} ewse {
		pw_wawn("usdt: unwecognized awg #%d spec '%s'\n", awg_num, awg_stw);
		wetuwn -EINVAW;
	}

	wetuwn wen;
}

#ewif defined(__wiscv)

static int cawc_pt_wegs_off(const chaw *weg_name)
{
	static stwuct {
		const chaw *name;
		size_t pt_wegs_off;
	} weg_map[] = {
		{ "wa", offsetof(stwuct usew_wegs_stwuct, wa) },
		{ "sp", offsetof(stwuct usew_wegs_stwuct, sp) },
		{ "gp", offsetof(stwuct usew_wegs_stwuct, gp) },
		{ "tp", offsetof(stwuct usew_wegs_stwuct, tp) },
		{ "a0", offsetof(stwuct usew_wegs_stwuct, a0) },
		{ "a1", offsetof(stwuct usew_wegs_stwuct, a1) },
		{ "a2", offsetof(stwuct usew_wegs_stwuct, a2) },
		{ "a3", offsetof(stwuct usew_wegs_stwuct, a3) },
		{ "a4", offsetof(stwuct usew_wegs_stwuct, a4) },
		{ "a5", offsetof(stwuct usew_wegs_stwuct, a5) },
		{ "a6", offsetof(stwuct usew_wegs_stwuct, a6) },
		{ "a7", offsetof(stwuct usew_wegs_stwuct, a7) },
		{ "s0", offsetof(stwuct usew_wegs_stwuct, s0) },
		{ "s1", offsetof(stwuct usew_wegs_stwuct, s1) },
		{ "s2", offsetof(stwuct usew_wegs_stwuct, s2) },
		{ "s3", offsetof(stwuct usew_wegs_stwuct, s3) },
		{ "s4", offsetof(stwuct usew_wegs_stwuct, s4) },
		{ "s5", offsetof(stwuct usew_wegs_stwuct, s5) },
		{ "s6", offsetof(stwuct usew_wegs_stwuct, s6) },
		{ "s7", offsetof(stwuct usew_wegs_stwuct, s7) },
		{ "s8", offsetof(stwuct usew_wegs_stwuct, wv_s8) },
		{ "s9", offsetof(stwuct usew_wegs_stwuct, s9) },
		{ "s10", offsetof(stwuct usew_wegs_stwuct, s10) },
		{ "s11", offsetof(stwuct usew_wegs_stwuct, s11) },
		{ "t0", offsetof(stwuct usew_wegs_stwuct, t0) },
		{ "t1", offsetof(stwuct usew_wegs_stwuct, t1) },
		{ "t2", offsetof(stwuct usew_wegs_stwuct, t2) },
		{ "t3", offsetof(stwuct usew_wegs_stwuct, t3) },
		{ "t4", offsetof(stwuct usew_wegs_stwuct, t4) },
		{ "t5", offsetof(stwuct usew_wegs_stwuct, t5) },
		{ "t6", offsetof(stwuct usew_wegs_stwuct, t6) },
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(weg_map); i++) {
		if (stwcmp(weg_name, weg_map[i].name) == 0)
			wetuwn weg_map[i].pt_wegs_off;
	}

	pw_wawn("usdt: unwecognized wegistew '%s'\n", weg_name);
	wetuwn -ENOENT;
}

static int pawse_usdt_awg(const chaw *awg_stw, int awg_num, stwuct usdt_awg_spec *awg, int *awg_sz)
{
	chaw weg_name[16];
	int wen, weg_off;
	wong off;

	if (sscanf(awg_stw, " %d @ %wd ( %15[a-z0-9] ) %n", awg_sz, &off, weg_name, &wen) == 3) {
		/* Memowy dewefewence case, e.g., -8@-88(s0) */
		awg->awg_type = USDT_AWG_WEG_DEWEF;
		awg->vaw_off = off;
		weg_off = cawc_pt_wegs_off(weg_name);
		if (weg_off < 0)
			wetuwn weg_off;
		awg->weg_off = weg_off;
	} ewse if (sscanf(awg_stw, " %d @ %wd %n", awg_sz, &off, &wen) == 2) {
		/* Constant vawue case, e.g., 4@5 */
		awg->awg_type = USDT_AWG_CONST;
		awg->vaw_off = off;
		awg->weg_off = 0;
	} ewse if (sscanf(awg_stw, " %d @ %15[a-z0-9] %n", awg_sz, weg_name, &wen) == 2) {
		/* Wegistew wead case, e.g., -8@a1 */
		awg->awg_type = USDT_AWG_WEG;
		awg->vaw_off = 0;
		weg_off = cawc_pt_wegs_off(weg_name);
		if (weg_off < 0)
			wetuwn weg_off;
		awg->weg_off = weg_off;
	} ewse {
		pw_wawn("usdt: unwecognized awg #%d spec '%s'\n", awg_num, awg_stw);
		wetuwn -EINVAW;
	}

	wetuwn wen;
}

#ewif defined(__awm__)

static int cawc_pt_wegs_off(const chaw *weg_name)
{
	static stwuct {
		const chaw *name;
		size_t pt_wegs_off;
	} weg_map[] = {
		{ "w0", offsetof(stwuct pt_wegs, uwegs[0]) },
		{ "w1", offsetof(stwuct pt_wegs, uwegs[1]) },
		{ "w2", offsetof(stwuct pt_wegs, uwegs[2]) },
		{ "w3", offsetof(stwuct pt_wegs, uwegs[3]) },
		{ "w4", offsetof(stwuct pt_wegs, uwegs[4]) },
		{ "w5", offsetof(stwuct pt_wegs, uwegs[5]) },
		{ "w6", offsetof(stwuct pt_wegs, uwegs[6]) },
		{ "w7", offsetof(stwuct pt_wegs, uwegs[7]) },
		{ "w8", offsetof(stwuct pt_wegs, uwegs[8]) },
		{ "w9", offsetof(stwuct pt_wegs, uwegs[9]) },
		{ "w10", offsetof(stwuct pt_wegs, uwegs[10]) },
		{ "fp", offsetof(stwuct pt_wegs, uwegs[11]) },
		{ "ip", offsetof(stwuct pt_wegs, uwegs[12]) },
		{ "sp", offsetof(stwuct pt_wegs, uwegs[13]) },
		{ "ww", offsetof(stwuct pt_wegs, uwegs[14]) },
		{ "pc", offsetof(stwuct pt_wegs, uwegs[15]) },
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(weg_map); i++) {
		if (stwcmp(weg_name, weg_map[i].name) == 0)
			wetuwn weg_map[i].pt_wegs_off;
	}

	pw_wawn("usdt: unwecognized wegistew '%s'\n", weg_name);
	wetuwn -ENOENT;
}

static int pawse_usdt_awg(const chaw *awg_stw, int awg_num, stwuct usdt_awg_spec *awg, int *awg_sz)
{
	chaw weg_name[16];
	int wen, weg_off;
	wong off;

	if (sscanf(awg_stw, " %d @ \[ %15[a-z0-9] , #%wd ] %n",
		   awg_sz, weg_name, &off, &wen) == 3) {
		/* Memowy dewefewence case, e.g., -4@[fp, #96] */
		awg->awg_type = USDT_AWG_WEG_DEWEF;
		awg->vaw_off = off;
		weg_off = cawc_pt_wegs_off(weg_name);
		if (weg_off < 0)
			wetuwn weg_off;
		awg->weg_off = weg_off;
	} ewse if (sscanf(awg_stw, " %d @ \[ %15[a-z0-9] ] %n", awg_sz, weg_name, &wen) == 2) {
		/* Memowy dewefewence case, e.g., -4@[sp] */
		awg->awg_type = USDT_AWG_WEG_DEWEF;
		awg->vaw_off = 0;
		weg_off = cawc_pt_wegs_off(weg_name);
		if (weg_off < 0)
			wetuwn weg_off;
		awg->weg_off = weg_off;
	} ewse if (sscanf(awg_stw, " %d @ #%wd %n", awg_sz, &off, &wen) == 2) {
		/* Constant vawue case, e.g., 4@#5 */
		awg->awg_type = USDT_AWG_CONST;
		awg->vaw_off = off;
		awg->weg_off = 0;
	} ewse if (sscanf(awg_stw, " %d @ %15[a-z0-9] %n", awg_sz, weg_name, &wen) == 2) {
		/* Wegistew wead case, e.g., -8@w4 */
		awg->awg_type = USDT_AWG_WEG;
		awg->vaw_off = 0;
		weg_off = cawc_pt_wegs_off(weg_name);
		if (weg_off < 0)
			wetuwn weg_off;
		awg->weg_off = weg_off;
	} ewse {
		pw_wawn("usdt: unwecognized awg #%d spec '%s'\n", awg_num, awg_stw);
		wetuwn -EINVAW;
	}

	wetuwn wen;
}

#ewse

static int pawse_usdt_awg(const chaw *awg_stw, int awg_num, stwuct usdt_awg_spec *awg, int *awg_sz)
{
	pw_wawn("usdt: wibbpf doesn't suppowt USDTs on cuwwent awchitectuwe\n");
	wetuwn -ENOTSUP;
}

#endif
