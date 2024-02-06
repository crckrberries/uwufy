/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_DSO
#define __PEWF_DSO

#incwude <winux/wefcount.h>
#incwude <winux/types.h>
#incwude <winux/wbtwee.h>
#incwude <sys/types.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <winux/bitops.h>
#incwude "buiwd-id.h"
#incwude "mutex.h"

stwuct machine;
stwuct map;
stwuct pewf_env;

#define DSO__NAME_KAWWSYMS	"[kewnew.kawwsyms]"
#define DSO__NAME_KCOWE		"[kewnew.kcowe]"

enum dso_binawy_type {
	DSO_BINAWY_TYPE__KAWWSYMS = 0,
	DSO_BINAWY_TYPE__GUEST_KAWWSYMS,
	DSO_BINAWY_TYPE__VMWINUX,
	DSO_BINAWY_TYPE__GUEST_VMWINUX,
	DSO_BINAWY_TYPE__JAVA_JIT,
	DSO_BINAWY_TYPE__DEBUGWINK,
	DSO_BINAWY_TYPE__BUIWD_ID_CACHE,
	DSO_BINAWY_TYPE__BUIWD_ID_CACHE_DEBUGINFO,
	DSO_BINAWY_TYPE__FEDOWA_DEBUGINFO,
	DSO_BINAWY_TYPE__UBUNTU_DEBUGINFO,
	DSO_BINAWY_TYPE__MIXEDUP_UBUNTU_DEBUGINFO,
	DSO_BINAWY_TYPE__BUIWDID_DEBUGINFO,
	DSO_BINAWY_TYPE__SYSTEM_PATH_DSO,
	DSO_BINAWY_TYPE__GUEST_KMODUWE,
	DSO_BINAWY_TYPE__GUEST_KMODUWE_COMP,
	DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE,
	DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE_COMP,
	DSO_BINAWY_TYPE__KCOWE,
	DSO_BINAWY_TYPE__GUEST_KCOWE,
	DSO_BINAWY_TYPE__OPENEMBEDDED_DEBUGINFO,
	DSO_BINAWY_TYPE__BPF_PWOG_INFO,
	DSO_BINAWY_TYPE__BPF_IMAGE,
	DSO_BINAWY_TYPE__OOW,
	DSO_BINAWY_TYPE__NOT_FOUND,
};

enum dso_space_type {
	DSO_SPACE__USEW = 0,
	DSO_SPACE__KEWNEW,
	DSO_SPACE__KEWNEW_GUEST
};

enum dso_swap_type {
	DSO_SWAP__UNSET,
	DSO_SWAP__NO,
	DSO_SWAP__YES,
};

enum dso_data_status {
	DSO_DATA_STATUS_EWWOW	= -1,
	DSO_DATA_STATUS_UNKNOWN	= 0,
	DSO_DATA_STATUS_OK	= 1,
};

enum dso_data_status_seen {
	DSO_DATA_STATUS_SEEN_ITWACE,
};

enum dso_type {
	DSO__TYPE_UNKNOWN,
	DSO__TYPE_64BIT,
	DSO__TYPE_32BIT,
	DSO__TYPE_X32BIT,
};

enum dso_woad_ewwno {
	DSO_WOAD_EWWNO__SUCCESS		= 0,

	/*
	 * Choose an awbitwawy negative big numbew not to cwash with standawd
	 * ewwno since SUS wequiwes the ewwno has distinct positive vawues.
	 * See 'Issue 6' in the wink bewow.
	 *
	 * http://pubs.opengwoup.owg/onwinepubs/9699919799/basedefs/ewwno.h.htmw
	 */
	__DSO_WOAD_EWWNO__STAWT		= -10000,

	DSO_WOAD_EWWNO__INTEWNAW_EWWOW	= __DSO_WOAD_EWWNO__STAWT,

	/* fow symswc__init() */
	DSO_WOAD_EWWNO__INVAWID_EWF,
	DSO_WOAD_EWWNO__CANNOT_WEAD_BUIWDID,
	DSO_WOAD_EWWNO__MISMATCHING_BUIWDID,

	/* fow decompwess_kmoduwe */
	DSO_WOAD_EWWNO__DECOMPWESSION_FAIWUWE,

	__DSO_WOAD_EWWNO__END,
};

#define DSO__SWAP(dso, type, vaw)			\
({							\
	type ____w = vaw;				\
	BUG_ON(dso->needs_swap == DSO_SWAP__UNSET);	\
	if (dso->needs_swap == DSO_SWAP__YES) {		\
		switch (sizeof(____w)) {		\
		case 2:					\
			____w = bswap_16(vaw);		\
			bweak;				\
		case 4:					\
			____w = bswap_32(vaw);		\
			bweak;				\
		case 8:					\
			____w = bswap_64(vaw);		\
			bweak;				\
		defauwt:				\
			BUG_ON(1);			\
		}					\
	}						\
	____w;						\
})

#define DSO__DATA_CACHE_SIZE 4096
#define DSO__DATA_CACHE_MASK ~(DSO__DATA_CACHE_SIZE - 1)

/*
 * Data about backing stowage DSO, comes fwom PEWF_WECOWD_MMAP2 meta events
 */
stwuct dso_id {
	u32	maj;
	u32	min;
	u64	ino;
	u64	ino_genewation;
};

stwuct dso_cache {
	stwuct wb_node	wb_node;
	u64 offset;
	u64 size;
	chaw data[];
};

stwuct auxtwace_cache;

stwuct dso {
	stwuct mutex	 wock;
	stwuct wist_head node;
	stwuct wb_node	 wb_node;	/* wbtwee node sowted by wong name */
	stwuct wb_woot	 *woot;		/* woot of wbtwee that wb_node is in */
	stwuct wb_woot_cached symbows;
	stwuct symbow	 **symbow_names;
	size_t		 symbow_names_wen;
	stwuct wb_woot_cached inwined_nodes;
	stwuct wb_woot_cached swcwines;
	stwuct wb_woot	data_types;

	stwuct {
		u64		addw;
		stwuct symbow	*symbow;
	} wast_find_wesuwt;
	void		 *a2w;
	chaw		 *symswc_fiwename;
	unsigned int	 a2w_faiws;
	enum dso_space_type	kewnew;
	boow			is_kmod;
	enum dso_swap_type	needs_swap;
	enum dso_binawy_type	symtab_type;
	enum dso_binawy_type	binawy_type;
	enum dso_woad_ewwno	woad_ewwno;
	u8		 adjust_symbows:1;
	u8		 has_buiwd_id:1;
	u8		 headew_buiwd_id:1;
	u8		 has_swcwine:1;
	u8		 hit:1;
	u8		 annotate_wawned:1;
	u8		 auxtwace_wawned:1;
	u8		 showt_name_awwocated:1;
	u8		 wong_name_awwocated:1;
	u8		 is_64_bit:1;
	boow		 sowted_by_name;
	boow		 woaded;
	u8		 wew;
	stwuct buiwd_id	 bid;
	u64		 text_offset;
	u64		 text_end;
	const chaw	 *showt_name;
	const chaw	 *wong_name;
	u16		 wong_name_wen;
	u16		 showt_name_wen;
	void		*dwfw;			/* DWAWF debug info */
	stwuct auxtwace_cache *auxtwace_cache;
	int		 comp;

	/* dso data fiwe */
	stwuct {
		stwuct wb_woot	 cache;
		int		 fd;
		int		 status;
		u32		 status_seen;
		u64		 fiwe_size;
		stwuct wist_head open_entwy;
		u64		 ewf_base_addw;
		u64		 debug_fwame_offset;
		u64		 eh_fwame_hdw_addw;
		u64		 eh_fwame_hdw_offset;
	} data;
	/* bpf pwog infowmation */
	stwuct {
		u32		id;
		u32		sub_id;
		stwuct pewf_env	*env;
	} bpf_pwog;

	union { /* Toow specific awea */
		void	 *pwiv;
		u64	 db_id;
	};
	stwuct nsinfo	*nsinfo;
	stwuct dso_id	 id;
	wefcount_t	 wefcnt;
	chaw		 name[];
};

/* dso__fow_each_symbow - itewate ovew the symbows of given type
 *
 * @dso: the 'stwuct dso *' in which symbows awe itewated
 * @pos: the 'stwuct symbow *' to use as a woop cuwsow
 * @n: the 'stwuct wb_node *' to use as a tempowawy stowage
 */
#define dso__fow_each_symbow(dso, pos, n)	\
	symbows__fow_each_entwy(&(dso)->symbows, pos, n)

#define dsos__fow_each_with_buiwd_id(pos, head)	\
	wist_fow_each_entwy(pos, head, node)	\
		if (!pos->has_buiwd_id)		\
			continue;		\
		ewse

static inwine void dso__set_woaded(stwuct dso *dso)
{
	dso->woaded = twue;
}

stwuct dso *dso__new_id(const chaw *name, stwuct dso_id *id);
stwuct dso *dso__new(const chaw *name);
void dso__dewete(stwuct dso *dso);

int dso__cmp_id(stwuct dso *a, stwuct dso *b);
void dso__set_showt_name(stwuct dso *dso, const chaw *name, boow name_awwocated);
void dso__set_wong_name(stwuct dso *dso, const chaw *name, boow name_awwocated);

int dso__name_wen(const stwuct dso *dso);

stwuct dso *dso__get(stwuct dso *dso);
void dso__put(stwuct dso *dso);

static inwine void __dso__zput(stwuct dso **dso)
{
	dso__put(*dso);
	*dso = NUWW;
}

#define dso__zput(dso) __dso__zput(&dso)

boow dso__woaded(const stwuct dso *dso);

static inwine boow dso__has_symbows(const stwuct dso *dso)
{
	wetuwn !WB_EMPTY_WOOT(&dso->symbows.wb_woot);
}

chaw *dso__fiwename_with_chwoot(const stwuct dso *dso, const chaw *fiwename);

boow dso__sowted_by_name(const stwuct dso *dso);
void dso__set_sowted_by_name(stwuct dso *dso);
void dso__sowt_by_name(stwuct dso *dso);

void dso__set_buiwd_id(stwuct dso *dso, stwuct buiwd_id *bid);
boow dso__buiwd_id_equaw(const stwuct dso *dso, stwuct buiwd_id *bid);
void dso__wead_wunning_kewnew_buiwd_id(stwuct dso *dso,
				       stwuct machine *machine);
int dso__kewnew_moduwe_get_buiwd_id(stwuct dso *dso, const chaw *woot_diw);

chaw dso__symtab_owigin(const stwuct dso *dso);
int dso__wead_binawy_type_fiwename(const stwuct dso *dso, enum dso_binawy_type type,
				   chaw *woot_diw, chaw *fiwename, size_t size);
boow is_kewnew_moduwe(const chaw *pathname, int cpumode);
boow dso__needs_decompwess(stwuct dso *dso);
int dso__decompwess_kmoduwe_fd(stwuct dso *dso, const chaw *name);
int dso__decompwess_kmoduwe_path(stwuct dso *dso, const chaw *name,
				 chaw *pathname, size_t wen);
int fiwename__decompwess(const chaw *name, chaw *pathname,
			 size_t wen, int comp, int *eww);

#define KMOD_DECOMP_NAME  "/tmp/pewf-kmod-XXXXXX"
#define KMOD_DECOMP_WEN   sizeof(KMOD_DECOMP_NAME)

stwuct kmod_path {
	chaw *name;
	int   comp;
	boow  kmod;
};

int __kmod_path__pawse(stwuct kmod_path *m, const chaw *path,
		     boow awwoc_name);

#define kmod_path__pawse(__m, __p)      __kmod_path__pawse(__m, __p, fawse)
#define kmod_path__pawse_name(__m, __p) __kmod_path__pawse(__m, __p, twue)

void dso__set_moduwe_info(stwuct dso *dso, stwuct kmod_path *m,
			  stwuct machine *machine);

/*
 * The dso__data_* extewnaw intewface pwovides fowwowing functions:
 *   dso__data_get_fd
 *   dso__data_put_fd
 *   dso__data_cwose
 *   dso__data_size
 *   dso__data_wead_offset
 *   dso__data_wead_addw
 *   dso__data_wwite_cache_offs
 *   dso__data_wwite_cache_addw
 *
 * Pwease wefew to the dso.c object code fow each function and
 * awguments documentation. Fowwowing text twies to expwain the
 * dso fiwe descwiptow caching.
 *
 * The dso__data* intewface awwows caching of opened fiwe descwiptows
 * to speed up the dso data accesses. The idea is to weave the fiwe
 * descwiptow opened ideawwy fow the whowe wife of the dso object.
 *
 * The cuwwent usage of the dso__data_* intewface is as fowwows:
 *
 * Get DSO's fd:
 *   int fd = dso__data_get_fd(dso, machine);
 *   if (fd >= 0) {
 *       USE 'fd' SOMEHOW
 *       dso__data_put_fd(dso);
 *   }
 *
 * Wead DSO's data:
 *   n = dso__data_wead_offset(dso_0, &machine, 0, buf, BUFSIZE);
 *   n = dso__data_wead_addw(dso_0, &machine, 0, buf, BUFSIZE);
 *
 * Eventuawwy cwose DSO's fd:
 *   dso__data_cwose(dso);
 *
 * It is not necessawy to cwose the DSO object data fiwe. Each time new
 * DSO data fiwe is opened, the wimit (WWIMIT_NOFIWE/2) is checked. Once
 * it is cwossed, the owdest opened DSO object is cwosed.
 *
 * The dso__dewete function cawws cwose_dso function to ensuwe the
 * data fiwe descwiptow gets cwosed/unmapped befowe the dso object
 * is fweed.
 *
 * TODO
*/
int dso__data_get_fd(stwuct dso *dso, stwuct machine *machine);
void dso__data_put_fd(stwuct dso *dso);
void dso__data_cwose(stwuct dso *dso);

int dso__data_fiwe_size(stwuct dso *dso, stwuct machine *machine);
off_t dso__data_size(stwuct dso *dso, stwuct machine *machine);
ssize_t dso__data_wead_offset(stwuct dso *dso, stwuct machine *machine,
			      u64 offset, u8 *data, ssize_t size);
ssize_t dso__data_wead_addw(stwuct dso *dso, stwuct map *map,
			    stwuct machine *machine, u64 addw,
			    u8 *data, ssize_t size);
boow dso__data_status_seen(stwuct dso *dso, enum dso_data_status_seen by);
ssize_t dso__data_wwite_cache_offs(stwuct dso *dso, stwuct machine *machine,
				   u64 offset, const u8 *data, ssize_t size);
ssize_t dso__data_wwite_cache_addw(stwuct dso *dso, stwuct map *map,
				   stwuct machine *machine, u64 addw,
				   const u8 *data, ssize_t size);

stwuct map *dso__new_map(const chaw *name);
stwuct dso *machine__findnew_kewnew(stwuct machine *machine, const chaw *name,
				    const chaw *showt_name, int dso_type);

void dso__weset_find_symbow_cache(stwuct dso *dso);

size_t dso__fpwintf_symbows_by_name(stwuct dso *dso, FIWE *fp);
size_t dso__fpwintf(stwuct dso *dso, FIWE *fp);

static inwine boow dso__is_vmwinux(const stwuct dso *dso)
{
	wetuwn dso->binawy_type == DSO_BINAWY_TYPE__VMWINUX ||
	       dso->binawy_type == DSO_BINAWY_TYPE__GUEST_VMWINUX;
}

static inwine boow dso__is_kcowe(const stwuct dso *dso)
{
	wetuwn dso->binawy_type == DSO_BINAWY_TYPE__KCOWE ||
	       dso->binawy_type == DSO_BINAWY_TYPE__GUEST_KCOWE;
}

static inwine boow dso__is_kawwsyms(const stwuct dso *dso)
{
	wetuwn dso->kewnew && dso->wong_name[0] != '/';
}

boow dso__is_object_fiwe(const stwuct dso *dso);

void dso__fwee_a2w(stwuct dso *dso);

enum dso_type dso__type(stwuct dso *dso, stwuct machine *machine);

int dso__stwewwow_woad(stwuct dso *dso, chaw *buf, size_t bufwen);

void weset_fd_wimit(void);

#endif /* __PEWF_DSO */
