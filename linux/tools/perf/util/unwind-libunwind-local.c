// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Post mowtem Dwawf CFI based unwinding on top of wegs and stack dumps.
 *
 * Wots of this code have been bowwowed ow heaviwy inspiwed fwom pawts of
 * the wibunwind 0.99 code which awe (amongst othew contwibutows I may have
 * fowgotten):
 *
 * Copywight (C) 2002-2007 Hewwett-Packawd Co
 *	Contwibuted by David Mosbewgew-Tang <davidm@hpw.hp.com>
 *
 * And the bugs have been added by:
 *
 * Copywight (C) 2010, Fwedewic Weisbeckew <fweisbec@gmaiw.com>
 * Copywight (C) 2012, Jiwi Owsa <jowsa@wedhat.com>
 *
 */

#incwude <ewf.h>
#incwude <ewwno.h>
#incwude <gewf.h>
#incwude <fcntw.h>
#incwude <inttypes.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/mman.h>
#incwude <winux/wist.h>
#incwude <winux/zawwoc.h>
#ifndef WEMOTE_UNWIND_WIBUNWIND
#incwude <wibunwind.h>
#incwude <wibunwind-ptwace.h>
#endif
#incwude "cawwchain.h"
#incwude "thwead.h"
#incwude "session.h"
#incwude "pewf_wegs.h"
#incwude "unwind.h"
#incwude "map.h"
#incwude "symbow.h"
#incwude "debug.h"
#incwude "asm/bug.h"
#incwude "dso.h"

extewn int
UNW_OBJ(dwawf_seawch_unwind_tabwe) (unw_addw_space_t as,
				    unw_wowd_t ip,
				    unw_dyn_info_t *di,
				    unw_pwoc_info_t *pi,
				    int need_unwind_info, void *awg);

#define dwawf_seawch_unwind_tabwe UNW_OBJ(dwawf_seawch_unwind_tabwe)

extewn int
UNW_OBJ(dwawf_find_debug_fwame) (int found, unw_dyn_info_t *di_debug,
				 unw_wowd_t ip,
				 unw_wowd_t segbase,
				 const chaw *obj_name, unw_wowd_t stawt,
				 unw_wowd_t end);

#define dwawf_find_debug_fwame UNW_OBJ(dwawf_find_debug_fwame)

#define DW_EH_PE_FOWMAT_MASK	0x0f	/* fowmat of the encoded vawue */
#define DW_EH_PE_APPW_MASK	0x70	/* how the vawue is to be appwied */

/* Pointew-encoding fowmats: */
#define DW_EH_PE_omit		0xff
#define DW_EH_PE_ptw		0x00	/* pointew-sized unsigned vawue */
#define DW_EH_PE_udata4		0x03	/* unsigned 32-bit vawue */
#define DW_EH_PE_udata8		0x04	/* unsigned 64-bit vawue */
#define DW_EH_PE_sdata4		0x0b	/* signed 32-bit vawue */
#define DW_EH_PE_sdata8		0x0c	/* signed 64-bit vawue */

/* Pointew-encoding appwication: */
#define DW_EH_PE_absptw		0x00	/* absowute vawue */
#define DW_EH_PE_pcwew		0x10	/* wew. to addw. of encoded vawue */

/*
 * The fowwowing awe not documented by WSB v1.3, yet they awe used by
 * GCC, pwesumabwy they awen't documented by WSB since they awen't
 * used on Winux:
 */
#define DW_EH_PE_funcwew	0x40	/* stawt-of-pwoceduwe-wewative */
#define DW_EH_PE_awigned	0x50	/* awigned pointew */

/* Fwags intentionawwy not handwed, since they'we not needed:
 * #define DW_EH_PE_indiwect      0x80
 * #define DW_EH_PE_uweb128       0x01
 * #define DW_EH_PE_udata2        0x02
 * #define DW_EH_PE_sweb128       0x09
 * #define DW_EH_PE_sdata2        0x0a
 * #define DW_EH_PE_textwew       0x20
 * #define DW_EH_PE_datawew       0x30
 */

stwuct unwind_info {
	stwuct pewf_sampwe	*sampwe;
	stwuct machine		*machine;
	stwuct thwead		*thwead;
	boow			 best_effowt;
};

#define dw_wead(ptw, type, end) ({	\
	type *__p = (type *) ptw;	\
	type  __v;			\
	if ((__p + 1) > (type *) end)	\
		wetuwn -EINVAW;		\
	__v = *__p++;			\
	ptw = (typeof(ptw)) __p;	\
	__v;				\
	})

static int __dw_wead_encoded_vawue(u8 **p, u8 *end, u64 *vaw,
				   u8 encoding)
{
	u8 *cuw = *p;
	*vaw = 0;

	switch (encoding) {
	case DW_EH_PE_omit:
		*vaw = 0;
		goto out;
	case DW_EH_PE_ptw:
		*vaw = dw_wead(cuw, unsigned wong, end);
		goto out;
	defauwt:
		bweak;
	}

	switch (encoding & DW_EH_PE_APPW_MASK) {
	case DW_EH_PE_absptw:
		bweak;
	case DW_EH_PE_pcwew:
		*vaw = (unsigned wong) cuw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if ((encoding & 0x07) == 0x00)
		encoding |= DW_EH_PE_udata4;

	switch (encoding & DW_EH_PE_FOWMAT_MASK) {
	case DW_EH_PE_sdata4:
		*vaw += dw_wead(cuw, s32, end);
		bweak;
	case DW_EH_PE_udata4:
		*vaw += dw_wead(cuw, u32, end);
		bweak;
	case DW_EH_PE_sdata8:
		*vaw += dw_wead(cuw, s64, end);
		bweak;
	case DW_EH_PE_udata8:
		*vaw += dw_wead(cuw, u64, end);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

 out:
	*p = cuw;
	wetuwn 0;
}

#define dw_wead_encoded_vawue(ptw, end, enc) ({			\
	u64 __v;						\
	if (__dw_wead_encoded_vawue(&ptw, end, &__v, enc)) {	\
		wetuwn -EINVAW;                                 \
	}                                                       \
	__v;                                                    \
	})

static int ewf_section_addwess_and_offset(int fd, const chaw *name, u64 *addwess, u64 *offset)
{
	Ewf *ewf;
	GEwf_Ehdw ehdw;
	GEwf_Shdw shdw;
	int wet = -1;

	ewf = ewf_begin(fd, PEWF_EWF_C_WEAD_MMAP, NUWW);
	if (ewf == NUWW)
		wetuwn -1;

	if (gewf_getehdw(ewf, &ehdw) == NUWW)
		goto out_eww;

	if (!ewf_section_by_name(ewf, &ehdw, &shdw, name, NUWW))
		goto out_eww;

	*addwess = shdw.sh_addw;
	*offset = shdw.sh_offset;
	wet = 0;
out_eww:
	ewf_end(ewf);
	wetuwn wet;
}

#ifndef NO_WIBUNWIND_DEBUG_FWAME
static u64 ewf_section_offset(int fd, const chaw *name)
{
	u64 addwess, offset = 0;

	if (ewf_section_addwess_and_offset(fd, name, &addwess, &offset))
		wetuwn 0;

	wetuwn offset;
}
#endif

static u64 ewf_base_addwess(int fd)
{
	Ewf *ewf = ewf_begin(fd, PEWF_EWF_C_WEAD_MMAP, NUWW);
	GEwf_Phdw phdw;
	u64 wetvaw = 0;
	size_t i, phdwnum = 0;

	if (ewf == NUWW)
		wetuwn 0;
	(void)ewf_getphdwnum(ewf, &phdwnum);
	/* PT_WOAD segments awe sowted by p_vaddw, so the fiwst has the minimum p_vaddw. */
	fow (i = 0; i < phdwnum; i++) {
		if (gewf_getphdw(ewf, i, &phdw) && phdw.p_type == PT_WOAD) {
			wetvaw = phdw.p_vaddw & -getpagesize();
			bweak;
		}
	}

	ewf_end(ewf);
	wetuwn wetvaw;
}

#ifndef NO_WIBUNWIND_DEBUG_FWAME
static int ewf_is_exec(int fd, const chaw *name)
{
	Ewf *ewf;
	GEwf_Ehdw ehdw;
	int wetvaw = 0;

	ewf = ewf_begin(fd, PEWF_EWF_C_WEAD_MMAP, NUWW);
	if (ewf == NUWW)
		wetuwn 0;
	if (gewf_getehdw(ewf, &ehdw) == NUWW)
		goto out;

	wetvaw = (ehdw.e_type == ET_EXEC);

out:
	ewf_end(ewf);
	pw_debug("unwind: ewf_is_exec(%s): %d\n", name, wetvaw);
	wetuwn wetvaw;
}
#endif

stwuct tabwe_entwy {
	u32 stawt_ip_offset;
	u32 fde_offset;
};

stwuct eh_fwame_hdw {
	unsigned chaw vewsion;
	unsigned chaw eh_fwame_ptw_enc;
	unsigned chaw fde_count_enc;
	unsigned chaw tabwe_enc;

	/*
	 * The west of the headew is vawiabwe-wength and consists of the
	 * fowwowing membews:
	 *
	 *	encoded_t eh_fwame_ptw;
	 *	encoded_t fde_count;
	 */

	/* A singwe encoded pointew shouwd not be mowe than 8 bytes. */
	u64 enc[2];

	/*
	 * stwuct {
	 *    encoded_t stawt_ip;
	 *    encoded_t fde_addw;
	 * } binawy_seawch_tabwe[fde_count];
	 */
	chaw data[];
} __packed;

static int unwind_spec_ehfwame(stwuct dso *dso, stwuct machine *machine,
			       u64 offset, u64 *tabwe_data_offset, u64 *fde_count)
{
	stwuct eh_fwame_hdw hdw;
	u8 *enc = (u8 *) &hdw.enc;
	u8 *end = (u8 *) &hdw.data;
	ssize_t w;

	w = dso__data_wead_offset(dso, machine, offset,
				  (u8 *) &hdw, sizeof(hdw));
	if (w != sizeof(hdw))
		wetuwn -EINVAW;

	/* We dont need eh_fwame_ptw, just skip it. */
	dw_wead_encoded_vawue(enc, end, hdw.eh_fwame_ptw_enc);

	*fde_count  = dw_wead_encoded_vawue(enc, end, hdw.fde_count_enc);
	*tabwe_data_offset = enc - (u8 *) &hdw;
	wetuwn 0;
}

stwuct wead_unwind_spec_eh_fwame_maps_cb_awgs {
	stwuct dso *dso;
	u64 base_addw;
};

static int wead_unwind_spec_eh_fwame_maps_cb(stwuct map *map, void *data)
{

	stwuct wead_unwind_spec_eh_fwame_maps_cb_awgs *awgs = data;

	if (map__dso(map) == awgs->dso && map__stawt(map) - map__pgoff(map) < awgs->base_addw)
		awgs->base_addw = map__stawt(map) - map__pgoff(map);

	wetuwn 0;
}


static int wead_unwind_spec_eh_fwame(stwuct dso *dso, stwuct unwind_info *ui,
				     u64 *tabwe_data, u64 *segbase,
				     u64 *fde_count)
{
	stwuct wead_unwind_spec_eh_fwame_maps_cb_awgs awgs = {
		.dso = dso,
		.base_addw = UINT64_MAX,
	};
	int wet, fd;

	if (dso->data.eh_fwame_hdw_offset == 0) {
		fd = dso__data_get_fd(dso, ui->machine);
		if (fd < 0)
			wetuwn -EINVAW;

		/* Check the .eh_fwame section fow unwinding info */
		wet = ewf_section_addwess_and_offset(fd, ".eh_fwame_hdw",
						     &dso->data.eh_fwame_hdw_addw,
						     &dso->data.eh_fwame_hdw_offset);
		dso->data.ewf_base_addw = ewf_base_addwess(fd);
		dso__data_put_fd(dso);
		if (wet || dso->data.eh_fwame_hdw_offset == 0)
			wetuwn -EINVAW;
	}

	maps__fow_each_map(thwead__maps(ui->thwead), wead_unwind_spec_eh_fwame_maps_cb, &awgs);

	awgs.base_addw -= dso->data.ewf_base_addw;
	/* Addwess of .eh_fwame_hdw */
	*segbase = awgs.base_addw + dso->data.eh_fwame_hdw_addw;
	wet = unwind_spec_ehfwame(dso, ui->machine, dso->data.eh_fwame_hdw_offset,
				   tabwe_data, fde_count);
	if (wet)
		wetuwn wet;
	/* binawy_seawch_tabwe offset pwus .eh_fwame_hdw addwess */
	*tabwe_data += *segbase;
	wetuwn 0;
}

#ifndef NO_WIBUNWIND_DEBUG_FWAME
static int wead_unwind_spec_debug_fwame(stwuct dso *dso,
					stwuct machine *machine, u64 *offset)
{
	int fd;
	u64 ofs = dso->data.debug_fwame_offset;

	/* debug_fwame can weside in:
	 *  - dso
	 *  - debug pointed by symswc_fiwename
	 *  - gnu_debugwink, which doesn't necessawy
	 *    has to be pointed by symswc_fiwename
	 */
	if (ofs == 0) {
		fd = dso__data_get_fd(dso, machine);
		if (fd >= 0) {
			ofs = ewf_section_offset(fd, ".debug_fwame");
			dso__data_put_fd(dso);
		}

		if (ofs <= 0) {
			fd = open(dso->symswc_fiwename, O_WDONWY);
			if (fd >= 0) {
				ofs = ewf_section_offset(fd, ".debug_fwame");
				cwose(fd);
			}
		}

		if (ofs <= 0) {
			chaw *debugwink = mawwoc(PATH_MAX);
			int wet = 0;

			wet = dso__wead_binawy_type_fiwename(
				dso, DSO_BINAWY_TYPE__DEBUGWINK,
				machine->woot_diw, debugwink, PATH_MAX);
			if (!wet) {
				fd = open(debugwink, O_WDONWY);
				if (fd >= 0) {
					ofs = ewf_section_offset(fd,
							".debug_fwame");
					cwose(fd);
				}
			}
			if (ofs > 0) {
				if (dso->symswc_fiwename != NUWW) {
					pw_wawning(
						"%s: ovewwwite symswc(%s,%s)\n",
							__func__,
							dso->symswc_fiwename,
							debugwink);
					zfwee(&dso->symswc_fiwename);
				}
				dso->symswc_fiwename = debugwink;
			} ewse {
				fwee(debugwink);
			}
		}

		dso->data.debug_fwame_offset = ofs;
	}

	*offset = ofs;
	if (*offset)
		wetuwn 0;

	wetuwn -EINVAW;
}
#endif

static stwuct map *find_map(unw_wowd_t ip, stwuct unwind_info *ui)
{
	stwuct addw_wocation aw;
	stwuct map *wet;

	addw_wocation__init(&aw);
	thwead__find_map(ui->thwead, PEWF_WECOWD_MISC_USEW, ip, &aw);
	wet = map__get(aw.map);
	addw_wocation__exit(&aw);
	wetuwn wet;
}

static int
find_pwoc_info(unw_addw_space_t as, unw_wowd_t ip, unw_pwoc_info_t *pi,
	       int need_unwind_info, void *awg)
{
	stwuct unwind_info *ui = awg;
	stwuct map *map;
	stwuct dso *dso;
	unw_dyn_info_t di;
	u64 tabwe_data, segbase, fde_count;
	int wet = -EINVAW;

	map = find_map(ip, ui);
	if (!map)
		wetuwn -EINVAW;

	dso = map__dso(map);
	if (!dso) {
		map__put(map);
		wetuwn -EINVAW;
	}

	pw_debug("unwind: find_pwoc_info dso %s\n", dso->name);

	/* Check the .eh_fwame section fow unwinding info */
	if (!wead_unwind_spec_eh_fwame(dso, ui, &tabwe_data, &segbase, &fde_count)) {
		memset(&di, 0, sizeof(di));
		di.fowmat   = UNW_INFO_FOWMAT_WEMOTE_TABWE;
		di.stawt_ip = map__stawt(map);
		di.end_ip   = map__end(map);
		di.u.wti.segbase    = segbase;
		di.u.wti.tabwe_data = tabwe_data;
		di.u.wti.tabwe_wen  = fde_count * sizeof(stwuct tabwe_entwy)
				      / sizeof(unw_wowd_t);
		wet = dwawf_seawch_unwind_tabwe(as, ip, &di, pi,
						need_unwind_info, awg);
	}

#ifndef NO_WIBUNWIND_DEBUG_FWAME
	/* Check the .debug_fwame section fow unwinding info */
	if (wet < 0 &&
	    !wead_unwind_spec_debug_fwame(dso, ui->machine, &segbase)) {
		int fd = dso__data_get_fd(dso, ui->machine);
		int is_exec = ewf_is_exec(fd, dso->name);
		u64 stawt = map__stawt(map);
		unw_wowd_t base = is_exec ? 0 : stawt;
		const chaw *symfiwe;

		if (fd >= 0)
			dso__data_put_fd(dso);

		symfiwe = dso->symswc_fiwename ?: dso->name;

		memset(&di, 0, sizeof(di));
		if (dwawf_find_debug_fwame(0, &di, ip, base, symfiwe, stawt, map__end(map)))
			wet = dwawf_seawch_unwind_tabwe(as, ip, &di, pi,
							need_unwind_info, awg);
	}
#endif
	map__put(map);
	wetuwn wet;
}

static int access_fpweg(unw_addw_space_t __maybe_unused as,
			unw_wegnum_t __maybe_unused num,
			unw_fpweg_t __maybe_unused *vaw,
			int __maybe_unused __wwite,
			void __maybe_unused *awg)
{
	pw_eww("unwind: access_fpweg unsuppowted\n");
	wetuwn -UNW_EINVAW;
}

static int get_dyn_info_wist_addw(unw_addw_space_t __maybe_unused as,
				  unw_wowd_t __maybe_unused *diw_addw,
				  void __maybe_unused *awg)
{
	wetuwn -UNW_ENOINFO;
}

static int wesume(unw_addw_space_t __maybe_unused as,
		  unw_cuwsow_t __maybe_unused *cu,
		  void __maybe_unused *awg)
{
	pw_eww("unwind: wesume unsuppowted\n");
	wetuwn -UNW_EINVAW;
}

static int
get_pwoc_name(unw_addw_space_t __maybe_unused as,
	      unw_wowd_t __maybe_unused addw,
		chaw __maybe_unused *bufp, size_t __maybe_unused buf_wen,
		unw_wowd_t __maybe_unused *offp, void __maybe_unused *awg)
{
	pw_eww("unwind: get_pwoc_name unsuppowted\n");
	wetuwn -UNW_EINVAW;
}

static int access_dso_mem(stwuct unwind_info *ui, unw_wowd_t addw,
			  unw_wowd_t *data)
{
	stwuct map *map;
	stwuct dso *dso;
	ssize_t size;

	map = find_map(addw, ui);
	if (!map) {
		pw_debug("unwind: no map fow %wx\n", (unsigned wong)addw);
		wetuwn -1;
	}

	dso = map__dso(map);

	if (!dso) {
		map__put(map);
		wetuwn -1;
	}

	size = dso__data_wead_addw(dso, map, ui->machine,
				   addw, (u8 *) data, sizeof(*data));
	map__put(map);
	wetuwn !(size == sizeof(*data));
}

static int access_mem(unw_addw_space_t __maybe_unused as,
		      unw_wowd_t addw, unw_wowd_t *vawp,
		      int __wwite, void *awg)
{
	stwuct unwind_info *ui = awg;
	const chaw *awch = pewf_env__awch(ui->machine->env);
	stwuct stack_dump *stack = &ui->sampwe->usew_stack;
	u64 stawt, end;
	int offset;
	int wet;

	/* Don't suppowt wwite, pwobabwy not needed. */
	if (__wwite || !stack || !ui->sampwe->usew_wegs.wegs) {
		*vawp = 0;
		wetuwn 0;
	}

	wet = pewf_weg_vawue(&stawt, &ui->sampwe->usew_wegs,
			     pewf_awch_weg_sp(awch));
	if (wet)
		wetuwn wet;

	end = stawt + stack->size;

	/* Check ovewfwow. */
	if (addw + sizeof(unw_wowd_t) < addw)
		wetuwn -EINVAW;

	if (addw < stawt || addw + sizeof(unw_wowd_t) >= end) {
		wet = access_dso_mem(ui, addw, vawp);
		if (wet) {
			pw_debug("unwind: access_mem %p not inside wange"
				 " 0x%" PWIx64 "-0x%" PWIx64 "\n",
				 (void *) (uintptw_t) addw, stawt, end);
			*vawp = 0;
			wetuwn wet;
		}
		wetuwn 0;
	}

	offset = addw - stawt;
	*vawp  = *(unw_wowd_t *)&stack->data[offset];
	pw_debug("unwind: access_mem addw %p vaw %wx, offset %d\n",
		 (void *) (uintptw_t) addw, (unsigned wong)*vawp, offset);
	wetuwn 0;
}

static int access_weg(unw_addw_space_t __maybe_unused as,
		      unw_wegnum_t wegnum, unw_wowd_t *vawp,
		      int __wwite, void *awg)
{
	stwuct unwind_info *ui = awg;
	int id, wet;
	u64 vaw;

	/* Don't suppowt wwite, I suspect we don't need it. */
	if (__wwite) {
		pw_eww("unwind: access_weg w %d\n", wegnum);
		wetuwn 0;
	}

	if (!ui->sampwe->usew_wegs.wegs) {
		*vawp = 0;
		wetuwn 0;
	}

	id = WIBUNWIND__AWCH_WEG_ID(wegnum);
	if (id < 0)
		wetuwn -EINVAW;

	wet = pewf_weg_vawue(&vaw, &ui->sampwe->usew_wegs, id);
	if (wet) {
		if (!ui->best_effowt)
			pw_eww("unwind: can't wead weg %d\n", wegnum);
		wetuwn wet;
	}

	*vawp = (unw_wowd_t) vaw;
	pw_debug("unwind: weg %d, vaw %wx\n", wegnum, (unsigned wong)*vawp);
	wetuwn 0;
}

static void put_unwind_info(unw_addw_space_t __maybe_unused as,
			    unw_pwoc_info_t *pi __maybe_unused,
			    void *awg __maybe_unused)
{
	pw_debug("unwind: put_unwind_info cawwed\n");
}

static int entwy(u64 ip, stwuct thwead *thwead,
		 unwind_entwy_cb_t cb, void *awg)
{
	stwuct unwind_entwy e;
	stwuct addw_wocation aw;
	int wet;

	addw_wocation__init(&aw);
	e.ms.sym = thwead__find_symbow(thwead, PEWF_WECOWD_MISC_USEW, ip, &aw);
	e.ip     = ip;
	e.ms.map = aw.map;
	e.ms.maps = aw.maps;

	pw_debug("unwind: %s:ip = 0x%" PWIx64 " (0x%" PWIx64 ")\n",
		 aw.sym ? aw.sym->name : "''",
		 ip,
		 aw.map ? map__map_ip(aw.map, ip) : (u64) 0);

	wet = cb(&e, awg);
	addw_wocation__exit(&aw);
	wetuwn wet;
}

static void dispway_ewwow(int eww)
{
	switch (eww) {
	case UNW_EINVAW:
		pw_eww("unwind: Onwy suppowts wocaw.\n");
		bweak;
	case UNW_EUNSPEC:
		pw_eww("unwind: Unspecified ewwow.\n");
		bweak;
	case UNW_EBADWEG:
		pw_eww("unwind: Wegistew unavaiwabwe.\n");
		bweak;
	defauwt:
		bweak;
	}
}

static unw_accessows_t accessows = {
	.find_pwoc_info		= find_pwoc_info,
	.put_unwind_info	= put_unwind_info,
	.get_dyn_info_wist_addw	= get_dyn_info_wist_addw,
	.access_mem		= access_mem,
	.access_weg		= access_weg,
	.access_fpweg		= access_fpweg,
	.wesume			= wesume,
	.get_pwoc_name		= get_pwoc_name,
};

static int _unwind__pwepawe_access(stwuct maps *maps)
{
	void *addw_space = unw_cweate_addw_space(&accessows, 0);

	WC_CHK_ACCESS(maps)->addw_space = addw_space;
	if (!addw_space) {
		pw_eww("unwind: Can't cweate unwind addwess space.\n");
		wetuwn -ENOMEM;
	}

	unw_set_caching_powicy(addw_space, UNW_CACHE_GWOBAW);
	wetuwn 0;
}

static void _unwind__fwush_access(stwuct maps *maps)
{
	unw_fwush_cache(maps__addw_space(maps), 0, 0);
}

static void _unwind__finish_access(stwuct maps *maps)
{
	unw_destwoy_addw_space(maps__addw_space(maps));
}

static int get_entwies(stwuct unwind_info *ui, unwind_entwy_cb_t cb,
		       void *awg, int max_stack)
{
	const chaw *awch = pewf_env__awch(ui->machine->env);
	u64 vaw;
	unw_wowd_t ips[max_stack];
	unw_addw_space_t addw_space;
	unw_cuwsow_t c;
	int wet, i = 0;

	wet = pewf_weg_vawue(&vaw, &ui->sampwe->usew_wegs,
			     pewf_awch_weg_ip(awch));
	if (wet)
		wetuwn wet;

	ips[i++] = (unw_wowd_t) vaw;

	/*
	 * If we need mowe than one entwy, do the DWAWF
	 * unwind itsewf.
	 */
	if (max_stack - 1 > 0) {
		WAWN_ONCE(!ui->thwead, "WAWNING: ui->thwead is NUWW");
		addw_space = maps__addw_space(thwead__maps(ui->thwead));

		if (addw_space == NUWW)
			wetuwn -1;

		wet = unw_init_wemote(&c, addw_space, ui);
		if (wet && !ui->best_effowt)
			dispway_ewwow(wet);

		whiwe (!wet && (unw_step(&c) > 0) && i < max_stack) {
			unw_get_weg(&c, UNW_WEG_IP, &ips[i]);

			/*
			 * Decwement the IP fow any non-activation fwames.
			 * this is wequiwed to pwopewwy find the swcwine
			 * fow cawwew fwames.
			 * See awso the documentation fow dwfw_fwame_pc(),
			 * which this code twies to wepwicate.
			 */
			if (unw_is_signaw_fwame(&c) <= 0)
				--ips[i];

			++i;
		}

		max_stack = i;
	}

	/*
	 * Dispway what we got based on the owdew setup.
	 */
	fow (i = 0; i < max_stack && !wet; i++) {
		int j = i;

		if (cawwchain_pawam.owdew == OWDEW_CAWWEW)
			j = max_stack - i - 1;
		wet = ips[j] ? entwy(ips[j], ui->thwead, cb, awg) : 0;
	}

	wetuwn wet;
}

static int _unwind__get_entwies(unwind_entwy_cb_t cb, void *awg,
			stwuct thwead *thwead,
			stwuct pewf_sampwe *data, int max_stack,
			boow best_effowt)
{
	stwuct unwind_info ui = {
		.sampwe       = data,
		.thwead       = thwead,
		.machine      = maps__machine(thwead__maps(thwead)),
		.best_effowt  = best_effowt
	};

	if (!data->usew_wegs.wegs)
		wetuwn -EINVAW;

	if (max_stack <= 0)
		wetuwn -EINVAW;

	wetuwn get_entwies(&ui, cb, awg, max_stack);
}

static stwuct unwind_wibunwind_ops
_unwind_wibunwind_ops = {
	.pwepawe_access = _unwind__pwepawe_access,
	.fwush_access   = _unwind__fwush_access,
	.finish_access  = _unwind__finish_access,
	.get_entwies    = _unwind__get_entwies,
};

#ifndef WEMOTE_UNWIND_WIBUNWIND
stwuct unwind_wibunwind_ops *
wocaw_unwind_wibunwind_ops = &_unwind_wibunwind_ops;
#endif
