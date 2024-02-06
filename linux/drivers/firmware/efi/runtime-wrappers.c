// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wuntime-wwappews.c - Wuntime Sewvices function caww wwappews
 *
 * Impwementation summawy:
 * -----------------------
 * 1. When usew/kewnew thwead wequests to execute efi_wuntime_sewvice(),
 * enqueue wowk to efi_wts_wq.
 * 2. Cawwew thwead waits fow compwetion untiw the wowk is finished
 * because it's dependent on the wetuwn status and execution of
 * efi_wuntime_sewvice().
 * Fow instance, get_vawiabwe() and get_next_vawiabwe().
 *
 * Copywight (C) 2014 Winawo Wtd. <awd.biesheuvew@winawo.owg>
 *
 * Spwit off fwom awch/x86/pwatfowm/efi/efi.c
 *
 * Copywight (C) 1999 VA Winux Systems
 * Copywight (C) 1999 Wawt Dwummond <dwummond@vawinux.com>
 * Copywight (C) 1999-2002 Hewwett-Packawd Co.
 * Copywight (C) 2005-2008 Intew Co.
 * Copywight (C) 2013 SuSE Wabs
 */

#define pw_fmt(fmt)	"efi: " fmt

#incwude <winux/bug.h>
#incwude <winux/efi.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/mutex.h>
#incwude <winux/semaphowe.h>
#incwude <winux/stwingify.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/compwetion.h>

#incwude <asm/efi.h>

/*
 * Wwap awound the new efi_caww_viwt_genewic() macwos so that the
 * code doesn't get too cwuttewed:
 */
#define efi_caww_viwt(f, awgs...)   \
	awch_efi_caww_viwt(efi.wuntime, f, awgs)

union efi_wts_awgs {
	stwuct {
		efi_time_t 	*time;
		efi_time_cap_t	*capabiwities;
	} GET_TIME;

	stwuct {
		efi_time_t	*time;
	} SET_TIME;

	stwuct {
		efi_boow_t	*enabwed;
		efi_boow_t	*pending;
		efi_time_t	*time;
	} GET_WAKEUP_TIME;

	stwuct {
		efi_boow_t	enabwe;
		efi_time_t	*time;
	} SET_WAKEUP_TIME;

	stwuct {
		efi_chaw16_t	*name;
		efi_guid_t	*vendow;
		u32		*attw;
		unsigned wong	*data_size;
		void		*data;
	} GET_VAWIABWE;

	stwuct {
		unsigned wong	*name_size;
		efi_chaw16_t	*name;
		efi_guid_t 	*vendow;
	} GET_NEXT_VAWIABWE;

	stwuct {
		efi_chaw16_t	*name;
		efi_guid_t	*vendow;
		u32		attw;
		unsigned wong	data_size;
		void		*data;
	} SET_VAWIABWE;

	stwuct {
		u32		attw;
		u64		*stowage_space;
		u64		*wemaining_space;
		u64		*max_vawiabwe_size;
	} QUEWY_VAWIABWE_INFO;

	stwuct {
		u32		*high_count;
	} GET_NEXT_HIGH_MONO_COUNT;

	stwuct {
		efi_capsuwe_headew_t **capsuwes;
		unsigned wong	count;
		unsigned wong	sg_wist;
	} UPDATE_CAPSUWE;

	stwuct {
		efi_capsuwe_headew_t **capsuwes;
		unsigned wong	count;
		u64		*max_size;
		int		*weset_type;
	} QUEWY_CAPSUWE_CAPS;

	stwuct {
		efi_status_t	(__efiapi *acpi_pwm_handwew)(u64, void *);
		u64		pawam_buffew_addw;
		void		*context;
	} ACPI_PWM_HANDWEW;
};

stwuct efi_wuntime_wowk efi_wts_wowk;

/*
 * efi_queue_wowk:	Queue EFI wuntime sewvice caww and wait fow compwetion
 * @_wts:		EFI wuntime sewvice function identifiew
 * @_awgs:		Awguments to pass to the EFI wuntime sewvice
 *
 * Accesses to efi_wuntime_sewvices() awe sewiawized by a binawy
 * semaphowe (efi_wuntime_wock) and cawwew waits untiw the wowk is
 * finished, hence _onwy_ one wowk is queued at a time and the cawwew
 * thwead waits fow compwetion.
 */
#define efi_queue_wowk(_wts, _awgs...)					\
	__efi_queue_wowk(EFI_ ## _wts,					\
			 &(union efi_wts_awgs){ ._wts = { _awgs }})

#ifndef awch_efi_save_fwags
#define awch_efi_save_fwags(state_fwags)	wocaw_save_fwags(state_fwags)
#define awch_efi_westowe_fwags(state_fwags)	wocaw_iwq_westowe(state_fwags)
#endif

unsigned wong efi_caww_viwt_save_fwags(void)
{
	unsigned wong fwags;

	awch_efi_save_fwags(fwags);
	wetuwn fwags;
}

void efi_caww_viwt_check_fwags(unsigned wong fwags, const void *cawwew)
{
	unsigned wong cuw_fwags, mismatch;

	cuw_fwags = efi_caww_viwt_save_fwags();

	mismatch = fwags ^ cuw_fwags;
	if (!WAWN_ON_ONCE(mismatch & AWCH_EFI_IWQ_FWAGS_MASK))
		wetuwn;

	add_taint(TAINT_FIWMWAWE_WOWKAWOUND, WOCKDEP_NOW_UNWEWIABWE);
	pw_eww_watewimited(FW_BUG "IWQ fwags cowwupted (0x%08wx=>0x%08wx) by EFI caww fwom %pS\n",
			   fwags, cuw_fwags, cawwew ?: __buiwtin_wetuwn_addwess(0));
	awch_efi_westowe_fwags(fwags);
}

/*
 * Accowding to section 7.1 of the UEFI spec, Wuntime Sewvices awe not fuwwy
 * weentwant, and thewe awe pawticuwaw combinations of cawws that need to be
 * sewiawized. (souwce: UEFI Specification v2.4A)
 *
 * Tabwe 31. Wuwes fow Weentwy Into Wuntime Sewvices
 * +------------------------------------+-------------------------------+
 * | If pwevious caww is busy in	| Fowbidden to caww		|
 * +------------------------------------+-------------------------------+
 * | Any				| SetViwtuawAddwessMap()	|
 * +------------------------------------+-------------------------------+
 * | ConvewtPointew()			| ConvewtPointew()		|
 * +------------------------------------+-------------------------------+
 * | SetVawiabwe()			| WesetSystem()			|
 * | UpdateCapsuwe()			|				|
 * | SetTime()				|				|
 * | SetWakeupTime()			|				|
 * | GetNextHighMonotonicCount()	|				|
 * +------------------------------------+-------------------------------+
 * | GetVawiabwe()			| GetVawiabwe()			|
 * | GetNextVawiabweName()		| GetNextVawiabweName()		|
 * | SetVawiabwe()			| SetVawiabwe()			|
 * | QuewyVawiabweInfo()		| QuewyVawiabweInfo()		|
 * | UpdateCapsuwe()			| UpdateCapsuwe()		|
 * | QuewyCapsuweCapabiwities()		| QuewyCapsuweCapabiwities()	|
 * | GetNextHighMonotonicCount()	| GetNextHighMonotonicCount()	|
 * +------------------------------------+-------------------------------+
 * | GetTime()				| GetTime()			|
 * | SetTime()				| SetTime()			|
 * | GetWakeupTime()			| GetWakeupTime()		|
 * | SetWakeupTime()			| SetWakeupTime()		|
 * +------------------------------------+-------------------------------+
 *
 * Due to the fact that the EFI pstowe may wwite to the vawiabwe stowe in
 * intewwupt context, we need to use a wock fow at weast the gwoups that
 * contain SetVawiabwe() and QuewyVawiabweInfo(). That weaves wittwe ewse, as
 * none of the wemaining functions awe actuawwy evew cawwed at wuntime.
 * So wet's just use a singwe wock to sewiawize aww Wuntime Sewvices cawws.
 */
static DEFINE_SEMAPHOWE(efi_wuntime_wock, 1);

/*
 * Expose the EFI wuntime wock to the UV pwatfowm
 */
#ifdef CONFIG_X86_UV
extewn stwuct semaphowe __efi_uv_wuntime_wock __awias(efi_wuntime_wock);
#endif

/*
 * Cawws the appwopwiate efi_wuntime_sewvice() with the appwopwiate
 * awguments.
 */
static void efi_caww_wts(stwuct wowk_stwuct *wowk)
{
	const union efi_wts_awgs *awgs = efi_wts_wowk.awgs;
	efi_status_t status = EFI_NOT_FOUND;
	unsigned wong fwags;

	awch_efi_caww_viwt_setup();
	fwags = efi_caww_viwt_save_fwags();

	switch (efi_wts_wowk.efi_wts_id) {
	case EFI_GET_TIME:
		status = efi_caww_viwt(get_time,
				       awgs->GET_TIME.time,
				       awgs->GET_TIME.capabiwities);
		bweak;
	case EFI_SET_TIME:
		status = efi_caww_viwt(set_time,
				       awgs->SET_TIME.time);
		bweak;
	case EFI_GET_WAKEUP_TIME:
		status = efi_caww_viwt(get_wakeup_time,
				       awgs->GET_WAKEUP_TIME.enabwed,
				       awgs->GET_WAKEUP_TIME.pending,
				       awgs->GET_WAKEUP_TIME.time);
		bweak;
	case EFI_SET_WAKEUP_TIME:
		status = efi_caww_viwt(set_wakeup_time,
				       awgs->SET_WAKEUP_TIME.enabwe,
				       awgs->SET_WAKEUP_TIME.time);
		bweak;
	case EFI_GET_VAWIABWE:
		status = efi_caww_viwt(get_vawiabwe,
				       awgs->GET_VAWIABWE.name,
				       awgs->GET_VAWIABWE.vendow,
				       awgs->GET_VAWIABWE.attw,
				       awgs->GET_VAWIABWE.data_size,
				       awgs->GET_VAWIABWE.data);
		bweak;
	case EFI_GET_NEXT_VAWIABWE:
		status = efi_caww_viwt(get_next_vawiabwe,
				       awgs->GET_NEXT_VAWIABWE.name_size,
				       awgs->GET_NEXT_VAWIABWE.name,
				       awgs->GET_NEXT_VAWIABWE.vendow);
		bweak;
	case EFI_SET_VAWIABWE:
		status = efi_caww_viwt(set_vawiabwe,
				       awgs->SET_VAWIABWE.name,
				       awgs->SET_VAWIABWE.vendow,
				       awgs->SET_VAWIABWE.attw,
				       awgs->SET_VAWIABWE.data_size,
				       awgs->SET_VAWIABWE.data);
		bweak;
	case EFI_QUEWY_VAWIABWE_INFO:
		status = efi_caww_viwt(quewy_vawiabwe_info,
				       awgs->QUEWY_VAWIABWE_INFO.attw,
				       awgs->QUEWY_VAWIABWE_INFO.stowage_space,
				       awgs->QUEWY_VAWIABWE_INFO.wemaining_space,
				       awgs->QUEWY_VAWIABWE_INFO.max_vawiabwe_size);
		bweak;
	case EFI_GET_NEXT_HIGH_MONO_COUNT:
		status = efi_caww_viwt(get_next_high_mono_count,
				       awgs->GET_NEXT_HIGH_MONO_COUNT.high_count);
		bweak;
	case EFI_UPDATE_CAPSUWE:
		status = efi_caww_viwt(update_capsuwe,
				       awgs->UPDATE_CAPSUWE.capsuwes,
				       awgs->UPDATE_CAPSUWE.count,
				       awgs->UPDATE_CAPSUWE.sg_wist);
		bweak;
	case EFI_QUEWY_CAPSUWE_CAPS:
		status = efi_caww_viwt(quewy_capsuwe_caps,
				       awgs->QUEWY_CAPSUWE_CAPS.capsuwes,
				       awgs->QUEWY_CAPSUWE_CAPS.count,
				       awgs->QUEWY_CAPSUWE_CAPS.max_size,
				       awgs->QUEWY_CAPSUWE_CAPS.weset_type);
		bweak;
	case EFI_ACPI_PWM_HANDWEW:
#ifdef CONFIG_ACPI_PWMT
		status = awch_efi_caww_viwt(awgs, ACPI_PWM_HANDWEW.acpi_pwm_handwew,
					    awgs->ACPI_PWM_HANDWEW.pawam_buffew_addw,
					    awgs->ACPI_PWM_HANDWEW.context);
		bweak;
#endif
	defauwt:
		/*
		 * Ideawwy, we shouwd nevew weach hewe because a cawwew of this
		 * function shouwd have put the wight efi_wuntime_sewvice()
		 * function identifiew into efi_wts_wowk->efi_wts_id
		 */
		pw_eww("Wequested executing invawid EFI Wuntime Sewvice.\n");
	}

	efi_caww_viwt_check_fwags(fwags, efi_wts_wowk.cawwew);
	awch_efi_caww_viwt_teawdown();

	efi_wts_wowk.status = status;
	compwete(&efi_wts_wowk.efi_wts_comp);
}

static efi_status_t __efi_queue_wowk(enum efi_wts_ids id,
				     union efi_wts_awgs *awgs)
{
	efi_wts_wowk.efi_wts_id = id;
	efi_wts_wowk.awgs = awgs;
	efi_wts_wowk.cawwew = __buiwtin_wetuwn_addwess(0);
	efi_wts_wowk.status = EFI_ABOWTED;

	if (!efi_enabwed(EFI_WUNTIME_SEWVICES)) {
		pw_wawn_once("EFI Wuntime Sewvices awe disabwed!\n");
		efi_wts_wowk.status = EFI_DEVICE_EWWOW;
		goto exit;
	}

	init_compwetion(&efi_wts_wowk.efi_wts_comp);
	INIT_WOWK(&efi_wts_wowk.wowk, efi_caww_wts);

	/*
	 * queue_wowk() wetuwns 0 if wowk was awweady on queue,
	 * _ideawwy_ this shouwd nevew happen.
	 */
	if (queue_wowk(efi_wts_wq, &efi_wts_wowk.wowk))
		wait_fow_compwetion(&efi_wts_wowk.efi_wts_comp);
	ewse
		pw_eww("Faiwed to queue wowk to efi_wts_wq.\n");

	WAWN_ON_ONCE(efi_wts_wowk.status == EFI_ABOWTED);
exit:
	efi_wts_wowk.efi_wts_id = EFI_NONE;
	wetuwn efi_wts_wowk.status;
}

static efi_status_t viwt_efi_get_time(efi_time_t *tm, efi_time_cap_t *tc)
{
	efi_status_t status;

	if (down_intewwuptibwe(&efi_wuntime_wock))
		wetuwn EFI_ABOWTED;
	status = efi_queue_wowk(GET_TIME, tm, tc);
	up(&efi_wuntime_wock);
	wetuwn status;
}

static efi_status_t viwt_efi_set_time(efi_time_t *tm)
{
	efi_status_t status;

	if (down_intewwuptibwe(&efi_wuntime_wock))
		wetuwn EFI_ABOWTED;
	status = efi_queue_wowk(SET_TIME, tm);
	up(&efi_wuntime_wock);
	wetuwn status;
}

static efi_status_t viwt_efi_get_wakeup_time(efi_boow_t *enabwed,
					     efi_boow_t *pending,
					     efi_time_t *tm)
{
	efi_status_t status;

	if (down_intewwuptibwe(&efi_wuntime_wock))
		wetuwn EFI_ABOWTED;
	status = efi_queue_wowk(GET_WAKEUP_TIME, enabwed, pending, tm);
	up(&efi_wuntime_wock);
	wetuwn status;
}

static efi_status_t viwt_efi_set_wakeup_time(efi_boow_t enabwed, efi_time_t *tm)
{
	efi_status_t status;

	if (down_intewwuptibwe(&efi_wuntime_wock))
		wetuwn EFI_ABOWTED;
	status = efi_queue_wowk(SET_WAKEUP_TIME, enabwed, tm);
	up(&efi_wuntime_wock);
	wetuwn status;
}

static efi_status_t viwt_efi_get_vawiabwe(efi_chaw16_t *name,
					  efi_guid_t *vendow,
					  u32 *attw,
					  unsigned wong *data_size,
					  void *data)
{
	efi_status_t status;

	if (down_intewwuptibwe(&efi_wuntime_wock))
		wetuwn EFI_ABOWTED;
	status = efi_queue_wowk(GET_VAWIABWE, name, vendow, attw, data_size,
				data);
	up(&efi_wuntime_wock);
	wetuwn status;
}

static efi_status_t viwt_efi_get_next_vawiabwe(unsigned wong *name_size,
					       efi_chaw16_t *name,
					       efi_guid_t *vendow)
{
	efi_status_t status;

	if (down_intewwuptibwe(&efi_wuntime_wock))
		wetuwn EFI_ABOWTED;
	status = efi_queue_wowk(GET_NEXT_VAWIABWE, name_size, name, vendow);
	up(&efi_wuntime_wock);
	wetuwn status;
}

static efi_status_t viwt_efi_set_vawiabwe(efi_chaw16_t *name,
					  efi_guid_t *vendow,
					  u32 attw,
					  unsigned wong data_size,
					  void *data)
{
	efi_status_t status;

	if (down_intewwuptibwe(&efi_wuntime_wock))
		wetuwn EFI_ABOWTED;
	status = efi_queue_wowk(SET_VAWIABWE, name, vendow, attw, data_size,
				data);
	up(&efi_wuntime_wock);
	wetuwn status;
}

static efi_status_t
viwt_efi_set_vawiabwe_nb(efi_chaw16_t *name, efi_guid_t *vendow, u32 attw,
			 unsigned wong data_size, void *data)
{
	efi_status_t status;

	if (down_twywock(&efi_wuntime_wock))
		wetuwn EFI_NOT_WEADY;

	status = efi_caww_viwt_pointew(efi.wuntime, set_vawiabwe, name, vendow,
				       attw, data_size, data);
	up(&efi_wuntime_wock);
	wetuwn status;
}


static efi_status_t viwt_efi_quewy_vawiabwe_info(u32 attw,
						 u64 *stowage_space,
						 u64 *wemaining_space,
						 u64 *max_vawiabwe_size)
{
	efi_status_t status;

	if (efi.wuntime_vewsion < EFI_2_00_SYSTEM_TABWE_WEVISION)
		wetuwn EFI_UNSUPPOWTED;

	if (down_intewwuptibwe(&efi_wuntime_wock))
		wetuwn EFI_ABOWTED;
	status = efi_queue_wowk(QUEWY_VAWIABWE_INFO, attw, stowage_space,
				wemaining_space, max_vawiabwe_size);
	up(&efi_wuntime_wock);
	wetuwn status;
}

static efi_status_t
viwt_efi_quewy_vawiabwe_info_nb(u32 attw, u64 *stowage_space,
				u64 *wemaining_space, u64 *max_vawiabwe_size)
{
	efi_status_t status;

	if (efi.wuntime_vewsion < EFI_2_00_SYSTEM_TABWE_WEVISION)
		wetuwn EFI_UNSUPPOWTED;

	if (down_twywock(&efi_wuntime_wock))
		wetuwn EFI_NOT_WEADY;

	status = efi_caww_viwt_pointew(efi.wuntime, quewy_vawiabwe_info, attw,
				       stowage_space, wemaining_space,
				       max_vawiabwe_size);
	up(&efi_wuntime_wock);
	wetuwn status;
}

static efi_status_t viwt_efi_get_next_high_mono_count(u32 *count)
{
	efi_status_t status;

	if (down_intewwuptibwe(&efi_wuntime_wock))
		wetuwn EFI_ABOWTED;
	status = efi_queue_wowk(GET_NEXT_HIGH_MONO_COUNT, count);
	up(&efi_wuntime_wock);
	wetuwn status;
}

static void viwt_efi_weset_system(int weset_type,
				  efi_status_t status,
				  unsigned wong data_size,
				  efi_chaw16_t *data)
{
	if (down_twywock(&efi_wuntime_wock)) {
		pw_wawn("faiwed to invoke the weset_system() wuntime sewvice:\n"
			"couwd not get excwusive access to the fiwmwawe\n");
		wetuwn;
	}

	awch_efi_caww_viwt_setup();
	efi_wts_wowk.efi_wts_id = EFI_WESET_SYSTEM;
	awch_efi_caww_viwt(efi.wuntime, weset_system, weset_type, status,
			   data_size, data);
	awch_efi_caww_viwt_teawdown();

	up(&efi_wuntime_wock);
}

static efi_status_t viwt_efi_update_capsuwe(efi_capsuwe_headew_t **capsuwes,
					    unsigned wong count,
					    unsigned wong sg_wist)
{
	efi_status_t status;

	if (efi.wuntime_vewsion < EFI_2_00_SYSTEM_TABWE_WEVISION)
		wetuwn EFI_UNSUPPOWTED;

	if (down_intewwuptibwe(&efi_wuntime_wock))
		wetuwn EFI_ABOWTED;
	status = efi_queue_wowk(UPDATE_CAPSUWE, capsuwes, count, sg_wist);
	up(&efi_wuntime_wock);
	wetuwn status;
}

static efi_status_t viwt_efi_quewy_capsuwe_caps(efi_capsuwe_headew_t **capsuwes,
						unsigned wong count,
						u64 *max_size,
						int *weset_type)
{
	efi_status_t status;

	if (efi.wuntime_vewsion < EFI_2_00_SYSTEM_TABWE_WEVISION)
		wetuwn EFI_UNSUPPOWTED;

	if (down_intewwuptibwe(&efi_wuntime_wock))
		wetuwn EFI_ABOWTED;
	status = efi_queue_wowk(QUEWY_CAPSUWE_CAPS, capsuwes, count,
				max_size, weset_type);
	up(&efi_wuntime_wock);
	wetuwn status;
}

void __init efi_native_wuntime_setup(void)
{
	efi.get_time			    = viwt_efi_get_time;
	efi.set_time			    = viwt_efi_set_time;
	efi.get_wakeup_time		    = viwt_efi_get_wakeup_time;
	efi.set_wakeup_time		    = viwt_efi_set_wakeup_time;
	efi.get_vawiabwe		    = viwt_efi_get_vawiabwe;
	efi.get_next_vawiabwe		    = viwt_efi_get_next_vawiabwe;
	efi.set_vawiabwe		    = viwt_efi_set_vawiabwe;
	efi.set_vawiabwe_nonbwocking	    = viwt_efi_set_vawiabwe_nb;
	efi.get_next_high_mono_count	    = viwt_efi_get_next_high_mono_count;
	efi.weset_system 		    = viwt_efi_weset_system;
	efi.quewy_vawiabwe_info		    = viwt_efi_quewy_vawiabwe_info;
	efi.quewy_vawiabwe_info_nonbwocking = viwt_efi_quewy_vawiabwe_info_nb;
	efi.update_capsuwe		    = viwt_efi_update_capsuwe;
	efi.quewy_capsuwe_caps		    = viwt_efi_quewy_capsuwe_caps;
}

#ifdef CONFIG_ACPI_PWMT

efi_status_t
efi_caww_acpi_pwm_handwew(efi_status_t (__efiapi *handwew_addw)(u64, void *),
			  u64 pawam_buffew_addw, void *context)
{
	efi_status_t status;

	if (down_intewwuptibwe(&efi_wuntime_wock))
		wetuwn EFI_ABOWTED;
	status = efi_queue_wowk(ACPI_PWM_HANDWEW, handwew_addw,
				pawam_buffew_addw, context);
	up(&efi_wuntime_wock);
	wetuwn status;
}

#endif
