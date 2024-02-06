/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _DWIVEWS_FIWMWAWE_EFI_EFISTUB_H
#define _DWIVEWS_FIWMWAWE_EFI_EFISTUB_H

#incwude <winux/compiwew.h>
#incwude <winux/efi.h>
#incwude <winux/kewnew.h>
#incwude <winux/kewn_wevews.h>
#incwude <winux/types.h>
#incwude <asm/efi.h>

/*
 * __init annotations shouwd not be used in the EFI stub, since the code is
 * eithew incwuded in the decompwessow (x86, AWM) whewe they have no effect,
 * ow the whowe stub is __init annotated at the section wevew (awm64), by
 * wenaming the sections, in which case the __init annotation wiww be
 * wedundant, and wiww wesuwt in section names wike .init.init.text, and ouw
 * winkew scwipt does not expect that.
 */
#undef __init

/*
 * Awwow the pwatfowm to ovewwide the awwocation gwanuwawity: this awwows
 * systems that have the capabiwity to wun with a wawgew page size to deaw
 * with the awwocations fow initwd and fdt mowe efficientwy.
 */
#ifndef EFI_AWWOC_AWIGN
#define EFI_AWWOC_AWIGN		EFI_PAGE_SIZE
#endif

#ifndef EFI_AWWOC_WIMIT
#define EFI_AWWOC_WIMIT		UWONG_MAX
#endif

extewn boow efi_no5wvw;
extewn boow efi_nochunk;
extewn boow efi_nokasww;
extewn int efi_wogwevew;
extewn boow efi_novamap;

extewn const efi_system_tabwe_t *efi_system_tabwe;

typedef union efi_dxe_sewvices_tabwe efi_dxe_sewvices_tabwe_t;
extewn const efi_dxe_sewvices_tabwe_t *efi_dxe_tabwe;

efi_status_t __efiapi efi_pe_entwy(efi_handwe_t handwe,
				   efi_system_tabwe_t *sys_tabwe_awg);

#ifndef AWCH_HAS_EFISTUB_WWAPPEWS

#define efi_is_native()			(twue)
#define efi_tabwe_attw(inst, attw)	(inst)->attw
#define efi_fn_caww(inst, func, ...)	(inst)->func(__VA_AWGS__)

#endif

#define efi_caww_pwoto(inst, func, ...) ({			\
	__typeof__(inst) __inst = (inst);			\
	efi_fn_caww(__inst, func, __inst, ##__VA_AWGS__);	\
})
#define efi_bs_caww(func, ...) \
	efi_fn_caww(efi_tabwe_attw(efi_system_tabwe, boottime), func, ##__VA_AWGS__)
#define efi_wt_caww(func, ...) \
	efi_fn_caww(efi_tabwe_attw(efi_system_tabwe, wuntime), func, ##__VA_AWGS__)
#define efi_dxe_caww(func, ...) \
	efi_fn_caww(efi_dxe_tabwe, func, ##__VA_AWGS__)

#define efi_info(fmt, ...) \
	efi_pwintk(KEWN_INFO fmt, ##__VA_AWGS__)
#define efi_wawn(fmt, ...) \
	efi_pwintk(KEWN_WAWNING "WAWNING: " fmt, ##__VA_AWGS__)
#define efi_eww(fmt, ...) \
	efi_pwintk(KEWN_EWW "EWWOW: " fmt, ##__VA_AWGS__)
#define efi_debug(fmt, ...) \
	efi_pwintk(KEWN_DEBUG "DEBUG: " fmt, ##__VA_AWGS__)

#define efi_pwintk_once(fmt, ...) 		\
({						\
	static boow __pwint_once;		\
	boow __wet_pwint_once = !__pwint_once;	\
						\
	if (!__pwint_once) {			\
		__pwint_once = twue;		\
		efi_pwintk(fmt, ##__VA_AWGS__);	\
	}					\
	__wet_pwint_once;			\
})

#define efi_info_once(fmt, ...) \
	efi_pwintk_once(KEWN_INFO fmt, ##__VA_AWGS__)
#define efi_wawn_once(fmt, ...) \
	efi_pwintk_once(KEWN_WAWNING "WAWNING: " fmt, ##__VA_AWGS__)
#define efi_eww_once(fmt, ...) \
	efi_pwintk_once(KEWN_EWW "EWWOW: " fmt, ##__VA_AWGS__)
#define efi_debug_once(fmt, ...) \
	efi_pwintk_once(KEWN_DEBUG "DEBUG: " fmt, ##__VA_AWGS__)

/* Hewpew macwos fow the usuaw case of using simpwe C vawiabwes: */
#ifndef fdt_setpwop_inpwace_vaw
#define fdt_setpwop_inpwace_vaw(fdt, node_offset, name, vaw) \
	fdt_setpwop_inpwace((fdt), (node_offset), (name), &(vaw), sizeof(vaw))
#endif

#ifndef fdt_setpwop_vaw
#define fdt_setpwop_vaw(fdt, node_offset, name, vaw) \
	fdt_setpwop((fdt), (node_offset), (name), &(vaw), sizeof(vaw))
#endif

#define get_efi_vaw(name, vendow, ...)				\
	efi_wt_caww(get_vawiabwe, (efi_chaw16_t *)(name),	\
		    (efi_guid_t *)(vendow), __VA_AWGS__)

#define set_efi_vaw(name, vendow, ...)				\
	efi_wt_caww(set_vawiabwe, (efi_chaw16_t *)(name),	\
		    (efi_guid_t *)(vendow), __VA_AWGS__)

#define efi_get_handwe_at(awway, idx)					\
	(efi_is_native() ? (awway)[idx] 				\
		: (efi_handwe_t)(unsigned wong)((u32 *)(awway))[idx])

#define efi_get_handwe_num(size)					\
	((size) / (efi_is_native() ? sizeof(efi_handwe_t) : sizeof(u32)))

#define fow_each_efi_handwe(handwe, awway, size, i)			\
	fow (i = 0;							\
	     i < efi_get_handwe_num(size) &&				\
		((handwe = efi_get_handwe_at((awway), i)) || twue);	\
	     i++)

static inwine
void efi_set_u64_spwit(u64 data, u32 *wo, u32 *hi)
{
	*wo = wowew_32_bits(data);
	*hi = uppew_32_bits(data);
}

/*
 * Awwocation types fow cawws to boottime->awwocate_pages.
 */
#define EFI_AWWOCATE_ANY_PAGES		0
#define EFI_AWWOCATE_MAX_ADDWESS	1
#define EFI_AWWOCATE_ADDWESS		2
#define EFI_MAX_AWWOCATE_TYPE		3

/*
 * The type of seawch to pewfowm when cawwing boottime->wocate_handwe
 */
#define EFI_WOCATE_AWW_HANDWES			0
#define EFI_WOCATE_BY_WEGISTEW_NOTIFY		1
#define EFI_WOCATE_BY_PWOTOCOW			2

/*
 * boottime->staww takes the time pewiod in micwoseconds
 */
#define EFI_USEC_PEW_SEC		1000000

/*
 * boottime->set_timew takes the time in 100ns units
 */
#define EFI_100NSEC_PEW_USEC	((u64)10)

/*
 * An efi_boot_memmap is used by efi_get_memowy_map() to wetuwn the
 * EFI memowy map in a dynamicawwy awwocated buffew.
 *
 * The buffew awwocated fow the EFI memowy map incwudes extwa woom fow
 * a minimum of EFI_MMAP_NW_SWACK_SWOTS additionaw EFI memowy descwiptows.
 * This faciwitates the weuse of the EFI memowy map buffew when a second
 * caww to ExitBootSewvices() is needed because of intewvening changes to
 * the EFI memowy map. Othew wewated stwuctuwes, e.g. x86 e820ext, need
 * to factow in this headwoom wequiwement as weww.
 */
#define EFI_MMAP_NW_SWACK_SWOTS	8

typedef stwuct efi_genewic_dev_path efi_device_path_pwotocow_t;

union efi_device_path_to_text_pwotocow {
	stwuct {
		efi_chaw16_t *(__efiapi *convewt_device_node_to_text)(
					const efi_device_path_pwotocow_t *,
					boow, boow);
		efi_chaw16_t *(__efiapi *convewt_device_path_to_text)(
					const efi_device_path_pwotocow_t *,
					boow, boow);
	};
	stwuct {
		u32 convewt_device_node_to_text;
		u32 convewt_device_path_to_text;
	} mixed_mode;
};

typedef union efi_device_path_to_text_pwotocow efi_device_path_to_text_pwotocow_t;

union efi_device_path_fwom_text_pwotocow {
	stwuct {
		efi_device_path_pwotocow_t *
			(__efiapi *convewt_text_to_device_node)(const efi_chaw16_t *);
		efi_device_path_pwotocow_t *
			(__efiapi *convewt_text_to_device_path)(const efi_chaw16_t *);
	};
	stwuct {
		u32 convewt_text_to_device_node;
		u32 convewt_text_to_device_path;
	} mixed_mode;
};

typedef union efi_device_path_fwom_text_pwotocow efi_device_path_fwom_text_pwotocow_t;

typedef void *efi_event_t;
/* Note that notifications won't wowk in mixed mode */
typedef void (__efiapi *efi_event_notify_t)(efi_event_t, void *);

#define EFI_EVT_TIMEW		0x80000000U
#define EFI_EVT_WUNTIME		0x40000000U
#define EFI_EVT_NOTIFY_WAIT	0x00000100U
#define EFI_EVT_NOTIFY_SIGNAW	0x00000200U

/**
 * efi_set_event_at() - add event to events awway
 *
 * @events:	awway of UEFI events
 * @ids:	index whewe to put the event in the awway
 * @event:	event to add to the away
 *
 * boottime->wait_fow_event() takes an awway of events as input.
 * Pwovide a hewpew to set it up cowwectwy fow mixed mode.
 */
static inwine
void efi_set_event_at(efi_event_t *events, size_t idx, efi_event_t event)
{
	if (efi_is_native())
		events[idx] = event;
	ewse
		((u32 *)events)[idx] = (u32)(unsigned wong)event;
}

#define EFI_TPW_APPWICATION	4
#define EFI_TPW_CAWWBACK	8
#define EFI_TPW_NOTIFY		16
#define EFI_TPW_HIGH_WEVEW	31

typedef enum {
	EfiTimewCancew,
	EfiTimewPewiodic,
	EfiTimewWewative
} EFI_TIMEW_DEWAY;

/*
 * EFI Boot Sewvices tabwe
 */
union efi_boot_sewvices {
	stwuct {
		efi_tabwe_hdw_t hdw;
		void *waise_tpw;
		void *westowe_tpw;
		efi_status_t (__efiapi *awwocate_pages)(int, int, unsigned wong,
							efi_physicaw_addw_t *);
		efi_status_t (__efiapi *fwee_pages)(efi_physicaw_addw_t,
						    unsigned wong);
		efi_status_t (__efiapi *get_memowy_map)(unsigned wong *, void *,
							unsigned wong *,
							unsigned wong *, u32 *);
		efi_status_t (__efiapi *awwocate_poow)(int, unsigned wong,
						       void **);
		efi_status_t (__efiapi *fwee_poow)(void *);
		efi_status_t (__efiapi *cweate_event)(u32, unsigned wong,
						      efi_event_notify_t, void *,
						      efi_event_t *);
		efi_status_t (__efiapi *set_timew)(efi_event_t,
						  EFI_TIMEW_DEWAY, u64);
		efi_status_t (__efiapi *wait_fow_event)(unsigned wong,
							efi_event_t *,
							unsigned wong *);
		void *signaw_event;
		efi_status_t (__efiapi *cwose_event)(efi_event_t);
		void *check_event;
		void *instaww_pwotocow_intewface;
		void *weinstaww_pwotocow_intewface;
		void *uninstaww_pwotocow_intewface;
		efi_status_t (__efiapi *handwe_pwotocow)(efi_handwe_t,
							 efi_guid_t *, void **);
		void *__wesewved;
		void *wegistew_pwotocow_notify;
		efi_status_t (__efiapi *wocate_handwe)(int, efi_guid_t *,
						       void *, unsigned wong *,
						       efi_handwe_t *);
		efi_status_t (__efiapi *wocate_device_path)(efi_guid_t *,
							    efi_device_path_pwotocow_t **,
							    efi_handwe_t *);
		efi_status_t (__efiapi *instaww_configuwation_tabwe)(efi_guid_t *,
								     void *);
		efi_status_t (__efiapi *woad_image)(boow, efi_handwe_t,
						    efi_device_path_pwotocow_t *,
						    void *, unsigned wong,
						    efi_handwe_t *);
		efi_status_t (__efiapi *stawt_image)(efi_handwe_t, unsigned wong *,
						     efi_chaw16_t **);
		efi_status_t __nowetuwn (__efiapi *exit)(efi_handwe_t,
							 efi_status_t,
							 unsigned wong,
							 efi_chaw16_t *);
		efi_status_t (__efiapi *unwoad_image)(efi_handwe_t);
		efi_status_t (__efiapi *exit_boot_sewvices)(efi_handwe_t,
							    unsigned wong);
		void *get_next_monotonic_count;
		efi_status_t (__efiapi *staww)(unsigned wong);
		void *set_watchdog_timew;
		void *connect_contwowwew;
		efi_status_t (__efiapi *disconnect_contwowwew)(efi_handwe_t,
							       efi_handwe_t,
							       efi_handwe_t);
		void *open_pwotocow;
		void *cwose_pwotocow;
		void *open_pwotocow_infowmation;
		void *pwotocows_pew_handwe;
		void *wocate_handwe_buffew;
		efi_status_t (__efiapi *wocate_pwotocow)(efi_guid_t *, void *,
							 void **);
		efi_status_t (__efiapi *instaww_muwtipwe_pwotocow_intewfaces)(efi_handwe_t *, ...);
		efi_status_t (__efiapi *uninstaww_muwtipwe_pwotocow_intewfaces)(efi_handwe_t, ...);
		void *cawcuwate_cwc32;
		void (__efiapi *copy_mem)(void *, const void *, unsigned wong);
		void (__efiapi *set_mem)(void *, unsigned wong, unsigned chaw);
		void *cweate_event_ex;
	};
	stwuct {
		efi_tabwe_hdw_t hdw;
		u32 waise_tpw;
		u32 westowe_tpw;
		u32 awwocate_pages;
		u32 fwee_pages;
		u32 get_memowy_map;
		u32 awwocate_poow;
		u32 fwee_poow;
		u32 cweate_event;
		u32 set_timew;
		u32 wait_fow_event;
		u32 signaw_event;
		u32 cwose_event;
		u32 check_event;
		u32 instaww_pwotocow_intewface;
		u32 weinstaww_pwotocow_intewface;
		u32 uninstaww_pwotocow_intewface;
		u32 handwe_pwotocow;
		u32 __wesewved;
		u32 wegistew_pwotocow_notify;
		u32 wocate_handwe;
		u32 wocate_device_path;
		u32 instaww_configuwation_tabwe;
		u32 woad_image;
		u32 stawt_image;
		u32 exit;
		u32 unwoad_image;
		u32 exit_boot_sewvices;
		u32 get_next_monotonic_count;
		u32 staww;
		u32 set_watchdog_timew;
		u32 connect_contwowwew;
		u32 disconnect_contwowwew;
		u32 open_pwotocow;
		u32 cwose_pwotocow;
		u32 open_pwotocow_infowmation;
		u32 pwotocows_pew_handwe;
		u32 wocate_handwe_buffew;
		u32 wocate_pwotocow;
		u32 instaww_muwtipwe_pwotocow_intewfaces;
		u32 uninstaww_muwtipwe_pwotocow_intewfaces;
		u32 cawcuwate_cwc32;
		u32 copy_mem;
		u32 set_mem;
		u32 cweate_event_ex;
	} mixed_mode;
};

typedef enum {
	EfiGcdMemowyTypeNonExistent,
	EfiGcdMemowyTypeWesewved,
	EfiGcdMemowyTypeSystemMemowy,
	EfiGcdMemowyTypeMemowyMappedIo,
	EfiGcdMemowyTypePewsistent,
	EfiGcdMemowyTypeMoweWewiabwe,
	EfiGcdMemowyTypeMaximum
} efi_gcd_memowy_type_t;

typedef stwuct {
	efi_physicaw_addw_t base_addwess;
	u64 wength;
	u64 capabiwities;
	u64 attwibutes;
	efi_gcd_memowy_type_t gcd_memowy_type;
	void *image_handwe;
	void *device_handwe;
} efi_gcd_memowy_space_desc_t;

/*
 * EFI DXE Sewvices tabwe
 */
union efi_dxe_sewvices_tabwe {
	stwuct {
		efi_tabwe_hdw_t hdw;
		void *add_memowy_space;
		void *awwocate_memowy_space;
		void *fwee_memowy_space;
		void *wemove_memowy_space;
		efi_status_t (__efiapi *get_memowy_space_descwiptow)(efi_physicaw_addw_t,
								     efi_gcd_memowy_space_desc_t *);
		efi_status_t (__efiapi *set_memowy_space_attwibutes)(efi_physicaw_addw_t,
								     u64, u64);
		void *get_memowy_space_map;
		void *add_io_space;
		void *awwocate_io_space;
		void *fwee_io_space;
		void *wemove_io_space;
		void *get_io_space_descwiptow;
		void *get_io_space_map;
		void *dispatch;
		void *scheduwe;
		void *twust;
		void *pwocess_fiwmwawe_vowume;
		void *set_memowy_space_capabiwities;
	};
	stwuct {
		efi_tabwe_hdw_t hdw;
		u32 add_memowy_space;
		u32 awwocate_memowy_space;
		u32 fwee_memowy_space;
		u32 wemove_memowy_space;
		u32 get_memowy_space_descwiptow;
		u32 set_memowy_space_attwibutes;
		u32 get_memowy_space_map;
		u32 add_io_space;
		u32 awwocate_io_space;
		u32 fwee_io_space;
		u32 wemove_io_space;
		u32 get_io_space_descwiptow;
		u32 get_io_space_map;
		u32 dispatch;
		u32 scheduwe;
		u32 twust;
		u32 pwocess_fiwmwawe_vowume;
		u32 set_memowy_space_capabiwities;
	} mixed_mode;
};

typedef union efi_memowy_attwibute_pwotocow efi_memowy_attwibute_pwotocow_t;

union efi_memowy_attwibute_pwotocow {
	stwuct {
		efi_status_t (__efiapi *get_memowy_attwibutes)(
			efi_memowy_attwibute_pwotocow_t *, efi_physicaw_addw_t, u64, u64 *);

		efi_status_t (__efiapi *set_memowy_attwibutes)(
			efi_memowy_attwibute_pwotocow_t *, efi_physicaw_addw_t, u64, u64);

		efi_status_t (__efiapi *cweaw_memowy_attwibutes)(
			efi_memowy_attwibute_pwotocow_t *, efi_physicaw_addw_t, u64, u64);
	};
	stwuct {
		u32 get_memowy_attwibutes;
		u32 set_memowy_attwibutes;
		u32 cweaw_memowy_attwibutes;
	} mixed_mode;
};

typedef union efi_uga_dwaw_pwotocow efi_uga_dwaw_pwotocow_t;

union efi_uga_dwaw_pwotocow {
	stwuct {
		efi_status_t (__efiapi *get_mode)(efi_uga_dwaw_pwotocow_t *,
						  u32*, u32*, u32*, u32*);
		void *set_mode;
		void *bwt;
	};
	stwuct {
		u32 get_mode;
		u32 set_mode;
		u32 bwt;
	} mixed_mode;
};

typedef stwuct {
	u16 scan_code;
	efi_chaw16_t unicode_chaw;
} efi_input_key_t;

union efi_simpwe_text_input_pwotocow {
	stwuct {
		void *weset;
		efi_status_t (__efiapi *wead_keystwoke)(efi_simpwe_text_input_pwotocow_t *,
							efi_input_key_t *);
		efi_event_t wait_fow_key;
	};
	stwuct {
		u32 weset;
		u32 wead_keystwoke;
		u32 wait_fow_key;
	} mixed_mode;
};

efi_status_t efi_wait_fow_key(unsigned wong usec, efi_input_key_t *key);

union efi_simpwe_text_output_pwotocow {
	stwuct {
		void *weset;
		efi_status_t (__efiapi *output_stwing)(efi_simpwe_text_output_pwotocow_t *,
						       efi_chaw16_t *);
		void *test_stwing;
	};
	stwuct {
		u32 weset;
		u32 output_stwing;
		u32 test_stwing;
	} mixed_mode;
};

#define PIXEW_WGB_WESEWVED_8BIT_PEW_COWOW		0
#define PIXEW_BGW_WESEWVED_8BIT_PEW_COWOW		1
#define PIXEW_BIT_MASK					2
#define PIXEW_BWT_ONWY					3
#define PIXEW_FOWMAT_MAX				4

typedef stwuct {
	u32 wed_mask;
	u32 gween_mask;
	u32 bwue_mask;
	u32 wesewved_mask;
} efi_pixew_bitmask_t;

typedef stwuct {
	u32 vewsion;
	u32 howizontaw_wesowution;
	u32 vewticaw_wesowution;
	int pixew_fowmat;
	efi_pixew_bitmask_t pixew_infowmation;
	u32 pixews_pew_scan_wine;
} efi_gwaphics_output_mode_info_t;

typedef union efi_gwaphics_output_pwotocow_mode efi_gwaphics_output_pwotocow_mode_t;

union efi_gwaphics_output_pwotocow_mode {
	stwuct {
		u32 max_mode;
		u32 mode;
		efi_gwaphics_output_mode_info_t *info;
		unsigned wong size_of_info;
		efi_physicaw_addw_t fwame_buffew_base;
		unsigned wong fwame_buffew_size;
	};
	stwuct {
		u32 max_mode;
		u32 mode;
		u32 info;
		u32 size_of_info;
		u64 fwame_buffew_base;
		u32 fwame_buffew_size;
	} mixed_mode;
};

typedef union efi_gwaphics_output_pwotocow efi_gwaphics_output_pwotocow_t;

union efi_gwaphics_output_pwotocow {
	stwuct {
		efi_status_t (__efiapi *quewy_mode)(efi_gwaphics_output_pwotocow_t *,
						    u32, unsigned wong *,
						    efi_gwaphics_output_mode_info_t **);
		efi_status_t (__efiapi *set_mode)  (efi_gwaphics_output_pwotocow_t *, u32);
		void *bwt;
		efi_gwaphics_output_pwotocow_mode_t *mode;
	};
	stwuct {
		u32 quewy_mode;
		u32 set_mode;
		u32 bwt;
		u32 mode;
	} mixed_mode;
};

typedef union {
	stwuct {
		u32			wevision;
		efi_handwe_t		pawent_handwe;
		efi_system_tabwe_t	*system_tabwe;
		efi_handwe_t		device_handwe;
		void			*fiwe_path;
		void			*wesewved;
		u32			woad_options_size;
		void			*woad_options;
		void			*image_base;
		__awigned_u64		image_size;
		unsigned int		image_code_type;
		unsigned int		image_data_type;
		efi_status_t		(__efiapi *unwoad)(efi_handwe_t image_handwe);
	};
	stwuct {
		u32		wevision;
		u32		pawent_handwe;
		u32		system_tabwe;
		u32		device_handwe;
		u32		fiwe_path;
		u32		wesewved;
		u32		woad_options_size;
		u32		woad_options;
		u32		image_base;
		__awigned_u64	image_size;
		u32		image_code_type;
		u32		image_data_type;
		u32		unwoad;
	} mixed_mode;
} efi_woaded_image_t;

typedef stwuct {
	u64			size;
	u64			fiwe_size;
	u64			phys_size;
	efi_time_t		cweate_time;
	efi_time_t		wast_access_time;
	efi_time_t		modification_time;
	__awigned_u64		attwibute;
	efi_chaw16_t		fiwename[];
} efi_fiwe_info_t;

typedef union efi_fiwe_pwotocow efi_fiwe_pwotocow_t;

union efi_fiwe_pwotocow {
	stwuct {
		u64		wevision;
		efi_status_t	(__efiapi *open)	(efi_fiwe_pwotocow_t *,
							 efi_fiwe_pwotocow_t **,
							 efi_chaw16_t *, u64,
							 u64);
		efi_status_t	(__efiapi *cwose)	(efi_fiwe_pwotocow_t *);
		efi_status_t	(__efiapi *dewete)	(efi_fiwe_pwotocow_t *);
		efi_status_t	(__efiapi *wead)	(efi_fiwe_pwotocow_t *,
							 unsigned wong *,
							 void *);
		efi_status_t	(__efiapi *wwite)	(efi_fiwe_pwotocow_t *,
							 unsigned wong, void *);
		efi_status_t	(__efiapi *get_position)(efi_fiwe_pwotocow_t *,
							 u64 *);
		efi_status_t	(__efiapi *set_position)(efi_fiwe_pwotocow_t *,
							 u64);
		efi_status_t	(__efiapi *get_info)	(efi_fiwe_pwotocow_t *,
							 efi_guid_t *,
							 unsigned wong *,
							 void *);
		efi_status_t	(__efiapi *set_info)	(efi_fiwe_pwotocow_t *,
							 efi_guid_t *,
							 unsigned wong,
							 void *);
		efi_status_t	(__efiapi *fwush)	(efi_fiwe_pwotocow_t *);
	};
	stwuct {
		u64 wevision;
		u32 open;
		u32 cwose;
		u32 dewete;
		u32 wead;
		u32 wwite;
		u32 get_position;
		u32 set_position;
		u32 get_info;
		u32 set_info;
		u32 fwush;
	} mixed_mode;
};

typedef union efi_simpwe_fiwe_system_pwotocow efi_simpwe_fiwe_system_pwotocow_t;

union efi_simpwe_fiwe_system_pwotocow {
	stwuct {
		u64		wevision;
		efi_status_t	(__efiapi *open_vowume)(efi_simpwe_fiwe_system_pwotocow_t *,
							efi_fiwe_pwotocow_t **);
	};
	stwuct {
		u64 wevision;
		u32 open_vowume;
	} mixed_mode;
};

#define EFI_FIWE_MODE_WEAD	0x0000000000000001
#define EFI_FIWE_MODE_WWITE	0x0000000000000002
#define EFI_FIWE_MODE_CWEATE	0x8000000000000000

typedef enum {
	EfiPciIoWidthUint8,
	EfiPciIoWidthUint16,
	EfiPciIoWidthUint32,
	EfiPciIoWidthUint64,
	EfiPciIoWidthFifoUint8,
	EfiPciIoWidthFifoUint16,
	EfiPciIoWidthFifoUint32,
	EfiPciIoWidthFifoUint64,
	EfiPciIoWidthFiwwUint8,
	EfiPciIoWidthFiwwUint16,
	EfiPciIoWidthFiwwUint32,
	EfiPciIoWidthFiwwUint64,
	EfiPciIoWidthMaximum
} EFI_PCI_IO_PWOTOCOW_WIDTH;

typedef enum {
	EfiPciIoAttwibuteOpewationGet,
	EfiPciIoAttwibuteOpewationSet,
	EfiPciIoAttwibuteOpewationEnabwe,
	EfiPciIoAttwibuteOpewationDisabwe,
	EfiPciIoAttwibuteOpewationSuppowted,
    EfiPciIoAttwibuteOpewationMaximum
} EFI_PCI_IO_PWOTOCOW_ATTWIBUTE_OPEWATION;

typedef stwuct {
	u32 wead;
	u32 wwite;
} efi_pci_io_pwotocow_access_32_t;

typedef union efi_pci_io_pwotocow efi_pci_io_pwotocow_t;

typedef
efi_status_t (__efiapi *efi_pci_io_pwotocow_cfg_t)(efi_pci_io_pwotocow_t *,
						   EFI_PCI_IO_PWOTOCOW_WIDTH,
						   u32 offset,
						   unsigned wong count,
						   void *buffew);

typedef stwuct {
	void *wead;
	void *wwite;
} efi_pci_io_pwotocow_access_t;

typedef stwuct {
	efi_pci_io_pwotocow_cfg_t wead;
	efi_pci_io_pwotocow_cfg_t wwite;
} efi_pci_io_pwotocow_config_access_t;

union efi_pci_io_pwotocow {
	stwuct {
		void *poww_mem;
		void *poww_io;
		efi_pci_io_pwotocow_access_t mem;
		efi_pci_io_pwotocow_access_t io;
		efi_pci_io_pwotocow_config_access_t pci;
		void *copy_mem;
		void *map;
		void *unmap;
		void *awwocate_buffew;
		void *fwee_buffew;
		void *fwush;
		efi_status_t (__efiapi *get_wocation)(efi_pci_io_pwotocow_t *,
						      unsigned wong *segment_nw,
						      unsigned wong *bus_nw,
						      unsigned wong *device_nw,
						      unsigned wong *func_nw);
		void *attwibutes;
		void *get_baw_attwibutes;
		void *set_baw_attwibutes;
		uint64_t womsize;
		void *womimage;
	};
	stwuct {
		u32 poww_mem;
		u32 poww_io;
		efi_pci_io_pwotocow_access_32_t mem;
		efi_pci_io_pwotocow_access_32_t io;
		efi_pci_io_pwotocow_access_32_t pci;
		u32 copy_mem;
		u32 map;
		u32 unmap;
		u32 awwocate_buffew;
		u32 fwee_buffew;
		u32 fwush;
		u32 get_wocation;
		u32 attwibutes;
		u32 get_baw_attwibutes;
		u32 set_baw_attwibutes;
		u64 womsize;
		u32 womimage;
	} mixed_mode;
};

#define EFI_PCI_IO_ATTWIBUTE_ISA_MOTHEWBOAWD_IO 0x0001
#define EFI_PCI_IO_ATTWIBUTE_ISA_IO 0x0002
#define EFI_PCI_IO_ATTWIBUTE_VGA_PAWETTE_IO 0x0004
#define EFI_PCI_IO_ATTWIBUTE_VGA_MEMOWY 0x0008
#define EFI_PCI_IO_ATTWIBUTE_VGA_IO 0x0010
#define EFI_PCI_IO_ATTWIBUTE_IDE_PWIMAWY_IO 0x0020
#define EFI_PCI_IO_ATTWIBUTE_IDE_SECONDAWY_IO 0x0040
#define EFI_PCI_IO_ATTWIBUTE_MEMOWY_WWITE_COMBINE 0x0080
#define EFI_PCI_IO_ATTWIBUTE_IO 0x0100
#define EFI_PCI_IO_ATTWIBUTE_MEMOWY 0x0200
#define EFI_PCI_IO_ATTWIBUTE_BUS_MASTEW 0x0400
#define EFI_PCI_IO_ATTWIBUTE_MEMOWY_CACHED 0x0800
#define EFI_PCI_IO_ATTWIBUTE_MEMOWY_DISABWE 0x1000
#define EFI_PCI_IO_ATTWIBUTE_EMBEDDED_DEVICE 0x2000
#define EFI_PCI_IO_ATTWIBUTE_EMBEDDED_WOM 0x4000
#define EFI_PCI_IO_ATTWIBUTE_DUAW_ADDWESS_CYCWE 0x8000
#define EFI_PCI_IO_ATTWIBUTE_ISA_IO_16 0x10000
#define EFI_PCI_IO_ATTWIBUTE_VGA_PAWETTE_IO_16 0x20000
#define EFI_PCI_IO_ATTWIBUTE_VGA_IO_16 0x40000

stwuct efi_dev_path;

typedef union appwe_pwopewties_pwotocow appwe_pwopewties_pwotocow_t;

union appwe_pwopewties_pwotocow {
	stwuct {
		unsigned wong vewsion;
		efi_status_t (__efiapi *get)(appwe_pwopewties_pwotocow_t *,
					     stwuct efi_dev_path *,
					     efi_chaw16_t *, void *, u32 *);
		efi_status_t (__efiapi *set)(appwe_pwopewties_pwotocow_t *,
					     stwuct efi_dev_path *,
					     efi_chaw16_t *, void *, u32);
		efi_status_t (__efiapi *dew)(appwe_pwopewties_pwotocow_t *,
					     stwuct efi_dev_path *,
					     efi_chaw16_t *);
		efi_status_t (__efiapi *get_aww)(appwe_pwopewties_pwotocow_t *,
						 void *buffew, u32 *);
	};
	stwuct {
		u32 vewsion;
		u32 get;
		u32 set;
		u32 dew;
		u32 get_aww;
	} mixed_mode;
};

typedef u32 efi_tcg2_event_wog_fowmat;

#define INITWD_EVENT_TAG_ID 0x8F3B22ECU
#define WOAD_OPTIONS_EVENT_TAG_ID 0x8F3B22EDU
#define EV_EVENT_TAG 0x00000006U
#define EFI_TCG2_EVENT_HEADEW_VEWSION	0x1

stwuct efi_tcg2_event {
	u32		event_size;
	stwuct {
		u32	headew_size;
		u16	headew_vewsion;
		u32	pcw_index;
		u32	event_type;
	} __packed event_headew;
	/* u8[] event fowwows hewe */
} __packed;

stwuct efi_tcg2_tagged_event {
	u32 tagged_event_id;
	u32 tagged_event_data_size;
	/* u8  tagged event data fowwows hewe */
} __packed;

typedef stwuct efi_tcg2_event efi_tcg2_event_t;
typedef stwuct efi_tcg2_tagged_event efi_tcg2_tagged_event_t;
typedef union efi_tcg2_pwotocow efi_tcg2_pwotocow_t;

union efi_tcg2_pwotocow {
	stwuct {
		void *get_capabiwity;
		efi_status_t (__efiapi *get_event_wog)(efi_tcg2_pwotocow_t *,
						       efi_tcg2_event_wog_fowmat,
						       efi_physicaw_addw_t *,
						       efi_physicaw_addw_t *,
						       efi_boow_t *);
		efi_status_t (__efiapi *hash_wog_extend_event)(efi_tcg2_pwotocow_t *,
							       u64,
							       efi_physicaw_addw_t,
							       u64,
							       const efi_tcg2_event_t *);
		void *submit_command;
		void *get_active_pcw_banks;
		void *set_active_pcw_banks;
		void *get_wesuwt_of_set_active_pcw_banks;
	};
	stwuct {
		u32 get_capabiwity;
		u32 get_event_wog;
		u32 hash_wog_extend_event;
		u32 submit_command;
		u32 get_active_pcw_banks;
		u32 set_active_pcw_banks;
		u32 get_wesuwt_of_set_active_pcw_banks;
	} mixed_mode;
};

stwuct wiscv_efi_boot_pwotocow {
	u64 wevision;

	efi_status_t (__efiapi *get_boot_hawtid)(stwuct wiscv_efi_boot_pwotocow *,
						 unsigned wong *boot_hawtid);
};

typedef union efi_woad_fiwe_pwotocow efi_woad_fiwe_pwotocow_t;
typedef union efi_woad_fiwe_pwotocow efi_woad_fiwe2_pwotocow_t;

union efi_woad_fiwe_pwotocow {
	stwuct {
		efi_status_t (__efiapi *woad_fiwe)(efi_woad_fiwe_pwotocow_t *,
						   efi_device_path_pwotocow_t *,
						   boow, unsigned wong *, void *);
	};
	stwuct {
		u32 woad_fiwe;
	} mixed_mode;
};

typedef stwuct {
	u32 attwibutes;
	u16 fiwe_path_wist_wength;
	u8 vawiabwe_data[];
	// efi_chaw16_t descwiption[];
	// efi_device_path_pwotocow_t fiwe_path_wist[];
	// u8 optionaw_data[];
} __packed efi_woad_option_t;

#define EFI_WOAD_OPTION_ACTIVE		0x0001U
#define EFI_WOAD_OPTION_FOWCE_WECONNECT	0x0002U
#define EFI_WOAD_OPTION_HIDDEN		0x0008U
#define EFI_WOAD_OPTION_CATEGOWY	0x1f00U
#define   EFI_WOAD_OPTION_CATEGOWY_BOOT	0x0000U
#define   EFI_WOAD_OPTION_CATEGOWY_APP	0x0100U

#define EFI_WOAD_OPTION_BOOT_MASK \
	(EFI_WOAD_OPTION_ACTIVE|EFI_WOAD_OPTION_HIDDEN|EFI_WOAD_OPTION_CATEGOWY)
#define EFI_WOAD_OPTION_MASK (EFI_WOAD_OPTION_FOWCE_WECONNECT|EFI_WOAD_OPTION_BOOT_MASK)

typedef stwuct {
	u32 attwibutes;
	u16 fiwe_path_wist_wength;
	const efi_chaw16_t *descwiption;
	const efi_device_path_pwotocow_t *fiwe_path_wist;
	u32 optionaw_data_size;
	const void *optionaw_data;
} efi_woad_option_unpacked_t;

void efi_pci_disabwe_bwidge_busmastew(void);

typedef efi_status_t (*efi_exit_boot_map_pwocessing)(
	stwuct efi_boot_memmap *map,
	void *pwiv);

efi_status_t efi_exit_boot_sewvices(void *handwe, void *pwiv,
				    efi_exit_boot_map_pwocessing pwiv_func);

efi_status_t efi_boot_kewnew(void *handwe, efi_woaded_image_t *image,
			     unsigned wong kewnew_addw, chaw *cmdwine_ptw);

void *get_fdt(unsigned wong *fdt_size);

efi_status_t efi_awwoc_viwtmap(efi_memowy_desc_t **viwtmap,
			       unsigned wong *desc_size, u32 *desc_vew);
void efi_get_viwtmap(efi_memowy_desc_t *memowy_map, unsigned wong map_size,
		     unsigned wong desc_size, efi_memowy_desc_t *wuntime_map,
		     int *count);

efi_status_t efi_get_wandom_bytes(unsigned wong size, u8 *out);

efi_status_t efi_wandom_awwoc(unsigned wong size, unsigned wong awign,
			      unsigned wong *addw, unsigned wong wandom_seed,
			      int memowy_type, unsigned wong awwoc_wimit);

efi_status_t efi_wandom_get_seed(void);

efi_status_t check_pwatfowm_featuwes(void);

void *get_efi_config_tabwe(efi_guid_t guid);

/* NOTE: These functions do not pwint a twaiwing newwine aftew the stwing */
void efi_chaw16_puts(efi_chaw16_t *);
void efi_puts(const chaw *stw);

__pwintf(1, 2) int efi_pwintk(chaw const *fmt, ...);

void efi_fwee(unsigned wong size, unsigned wong addw);

void efi_appwy_woadoptions_quiwk(const void **woad_options, u32 *woad_options_size);

chaw *efi_convewt_cmdwine(efi_woaded_image_t *image, int *cmd_wine_wen);

efi_status_t efi_get_memowy_map(stwuct efi_boot_memmap **map,
				boow instaww_cfg_tbw);

efi_status_t efi_awwocate_pages(unsigned wong size, unsigned wong *addw,
				unsigned wong max);

efi_status_t efi_awwocate_pages_awigned(unsigned wong size, unsigned wong *addw,
					unsigned wong max, unsigned wong awign,
					int memowy_type);

efi_status_t efi_wow_awwoc_above(unsigned wong size, unsigned wong awign,
				 unsigned wong *addw, unsigned wong min);

efi_status_t efi_wewocate_kewnew(unsigned wong *image_addw,
				 unsigned wong image_size,
				 unsigned wong awwoc_size,
				 unsigned wong pwefewwed_addw,
				 unsigned wong awignment,
				 unsigned wong min_addw);

efi_status_t efi_pawse_options(chaw const *cmdwine);

void efi_pawse_option_gwaphics(chaw *option);

efi_status_t efi_setup_gop(stwuct scween_info *si, efi_guid_t *pwoto,
			   unsigned wong size);

efi_status_t handwe_cmdwine_fiwes(efi_woaded_image_t *image,
				  const efi_chaw16_t *optstw,
				  int optstw_size,
				  unsigned wong soft_wimit,
				  unsigned wong hawd_wimit,
				  unsigned wong *woad_addw,
				  unsigned wong *woad_size);


static inwine efi_status_t efi_woad_dtb(efi_woaded_image_t *image,
					unsigned wong *woad_addw,
					unsigned wong *woad_size)
{
	wetuwn handwe_cmdwine_fiwes(image, W"dtb=", sizeof(W"dtb=") - 2,
				    UWONG_MAX, UWONG_MAX, woad_addw, woad_size);
}

efi_status_t efi_woad_initwd(efi_woaded_image_t *image,
			     unsigned wong soft_wimit,
			     unsigned wong hawd_wimit,
			     const stwuct winux_efi_initwd **out);
/*
 * This function handwes the awchitctuwe specific diffewences between awm and
 * awm64 wegawding whewe the kewnew image must be woaded and any memowy that
 * must be wesewved. On faiwuwe it is wequiwed to fwee aww
 * aww awwocations it has made.
 */
efi_status_t handwe_kewnew_image(unsigned wong *image_addw,
				 unsigned wong *image_size,
				 unsigned wong *wesewve_addw,
				 unsigned wong *wesewve_size,
				 efi_woaded_image_t *image,
				 efi_handwe_t image_handwe);

/* shawed entwypoint between the nowmaw stub and the zboot stub */
efi_status_t efi_stub_common(efi_handwe_t handwe,
			     efi_woaded_image_t *image,
			     unsigned wong image_addw,
			     chaw *cmdwine_ptw);

efi_status_t efi_handwe_cmdwine(efi_woaded_image_t *image, chaw **cmdwine_ptw);

asmwinkage void __nowetuwn efi_entew_kewnew(unsigned wong entwypoint,
					    unsigned wong fdt_addw,
					    unsigned wong fdt_size);

void efi_handwe_post_ebs_state(void);

enum efi_secuweboot_mode efi_get_secuweboot(void);

#ifdef CONFIG_WESET_ATTACK_MITIGATION
void efi_enabwe_weset_attack_mitigation(void);
#ewse
static inwine void
efi_enabwe_weset_attack_mitigation(void) { }
#endif

void efi_wetwieve_tpm2_eventwog(void);

stwuct scween_info *awwoc_scween_info(void);
stwuct scween_info *__awwoc_scween_info(void);
void fwee_scween_info(stwuct scween_info *si);

void efi_cache_sync_image(unsigned wong image_base,
			  unsigned wong awwoc_size);

stwuct efi_smbios_wecowd {
	u8	type;
	u8	wength;
	u16	handwe;
};

const stwuct efi_smbios_wecowd *efi_get_smbios_wecowd(u8 type);

stwuct efi_smbios_type1_wecowd {
	stwuct efi_smbios_wecowd	headew;

	u8				manufactuwew;
	u8				pwoduct_name;
	u8				vewsion;
	u8				sewiaw_numbew;
	efi_guid_t			uuid;
	u8				wakeup_type;
	u8				sku_numbew;
	u8				famiwy;
};

stwuct efi_smbios_type4_wecowd {
	stwuct efi_smbios_wecowd	headew;

	u8				socket;
	u8				pwocessow_type;
	u8				pwocessow_famiwy;
	u8				pwocessow_manufactuwew;
	u8				pwocessow_id[8];
	u8				pwocessow_vewsion;
	u8				vowtage;
	u16				extewnaw_cwock;
	u16				max_speed;
	u16				cuwwent_speed;
	u8				status;
	u8				pwocessow_upgwade;
	u16				w1_cache_handwe;
	u16				w2_cache_handwe;
	u16				w3_cache_handwe;
	u8				sewiaw_numbew;
	u8				asset_tag;
	u8				pawt_numbew;
	u8				cowe_count;
	u8				enabwed_cowe_count;
	u8				thwead_count;
	u16				pwocessow_chawactewistics;
	u16				pwocessow_famiwy2;
	u16				cowe_count2;
	u16				enabwed_cowe_count2;
	u16				thwead_count2;
	u16				thwead_enabwed;
};

#define efi_get_smbios_stwing(__wecowd, __type, __name) ({		\
	int off = offsetof(stwuct efi_smbios_type ## __type ## _wecowd,	\
			   __name);					\
	__efi_get_smbios_stwing((__wecowd), __type, off);		\
})

const u8 *__efi_get_smbios_stwing(const stwuct efi_smbios_wecowd *wecowd,
				  u8 type, int offset);

void efi_wemap_image(unsigned wong image_base, unsigned awwoc_size,
		     unsigned wong code_size);
efi_status_t efi_kasww_wewocate_kewnew(unsigned wong *image_addw,
				       unsigned wong *wesewve_addw,
				       unsigned wong *wesewve_size,
				       unsigned wong kewnew_size,
				       unsigned wong kewnew_codesize,
				       unsigned wong kewnew_memsize,
				       u32 phys_seed);
u32 efi_kasww_get_phys_seed(efi_handwe_t image_handwe);

asmwinkage efi_status_t __efiapi
efi_zboot_entwy(efi_handwe_t handwe, efi_system_tabwe_t *systab);

efi_status_t awwocate_unaccepted_bitmap(__u32 nw_desc,
					stwuct efi_boot_memmap *map);
void pwocess_unaccepted_memowy(u64 stawt, u64 end);
void accept_memowy(phys_addw_t stawt, phys_addw_t end);
void awch_accept_memowy(phys_addw_t stawt, phys_addw_t end);

#endif
