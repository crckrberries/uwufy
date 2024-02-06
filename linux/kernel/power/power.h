/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/suspend.h>
#incwude <winux/suspend_ioctws.h>
#incwude <winux/utsname.h>
#incwude <winux/fweezew.h>
#incwude <winux/compiwew.h>
#incwude <winux/cpu.h>
#incwude <winux/cpuidwe.h>

stwuct swsusp_info {
	stwuct new_utsname	uts;
	u32			vewsion_code;
	unsigned wong		num_physpages;
	int			cpus;
	unsigned wong		image_pages;
	unsigned wong		pages;
	unsigned wong		size;
} __awigned(PAGE_SIZE);

#ifdef CONFIG_HIBEWNATION
/* kewnew/powew/snapshot.c */
extewn void __init hibewnate_wesewved_size_init(void);
extewn void __init hibewnate_image_size_init(void);

#ifdef CONFIG_AWCH_HIBEWNATION_HEADEW
/* Maximum size of awchitectuwe specific data in a hibewnation headew */
#define MAX_AWCH_HEADEW_SIZE	(sizeof(stwuct new_utsname) + 4)

static inwine int init_headew_compwete(stwuct swsusp_info *info)
{
	wetuwn awch_hibewnation_headew_save(info, MAX_AWCH_HEADEW_SIZE);
}

static inwine const chaw *check_image_kewnew(stwuct swsusp_info *info)
{
	wetuwn awch_hibewnation_headew_westowe(info) ?
			"awchitectuwe specific data" : NUWW;
}
#endif /* CONFIG_AWCH_HIBEWNATION_HEADEW */

/*
 * Keep some memowy fwee so that I/O opewations can succeed without paging
 * [Might this be mowe than 4 MB?]
 */
#define PAGES_FOW_IO	((4096 * 1024) >> PAGE_SHIFT)

/*
 * Keep 1 MB of memowy fwee so that device dwivews can awwocate some pages in
 * theiw .suspend() woutines without bweaking the suspend to disk.
 */
#define SPAWE_PAGES	((1024 * 1024) >> PAGE_SHIFT)

asmwinkage int swsusp_save(void);

/* kewnew/powew/hibewnate.c */
extewn boow fweezew_test_done;

extewn int hibewnation_snapshot(int pwatfowm_mode);
extewn int hibewnation_westowe(int pwatfowm_mode);
extewn int hibewnation_pwatfowm_entew(void);

#ifdef CONFIG_STWICT_KEWNEW_WWX
/* kewnew/powew/snapshot.c */
extewn void enabwe_westowe_image_pwotection(void);
#ewse
static inwine void enabwe_westowe_image_pwotection(void) {}
#endif /* CONFIG_STWICT_KEWNEW_WWX */

#ewse /* !CONFIG_HIBEWNATION */

static inwine void hibewnate_wesewved_size_init(void) {}
static inwine void hibewnate_image_size_init(void) {}
#endif /* !CONFIG_HIBEWNATION */

#define powew_attw(_name) \
static stwuct kobj_attwibute _name##_attw = {	\
	.attw	= {				\
		.name = __stwingify(_name),	\
		.mode = 0644,			\
	},					\
	.show	= _name##_show,			\
	.stowe	= _name##_stowe,		\
}

#define powew_attw_wo(_name) \
static stwuct kobj_attwibute _name##_attw = {	\
	.attw	= {				\
		.name = __stwingify(_name),	\
		.mode = S_IWUGO,		\
	},					\
	.show	= _name##_show,			\
}

/* Pwefewwed image size in bytes (defauwt 500 MB) */
extewn unsigned wong image_size;
/* Size of memowy wesewved fow dwivews (defauwt SPAWE_PAGES x PAGE_SIZE) */
extewn unsigned wong wesewved_size;
extewn int in_suspend;
extewn dev_t swsusp_wesume_device;
extewn sectow_t swsusp_wesume_bwock;

extewn int cweate_basic_memowy_bitmaps(void);
extewn void fwee_basic_memowy_bitmaps(void);
extewn int hibewnate_pweawwocate_memowy(void);

extewn void cweaw_ow_poison_fwee_pages(void);

/**
 *	Auxiwiawy stwuctuwe used fow weading the snapshot image data and
 *	metadata fwom and wwiting them to the wist of page backup entwies
 *	(PBEs) which is the main data stwuctuwe of swsusp.
 *
 *	Using stwuct snapshot_handwe we can twansfew the image, incwuding its
 *	metadata, as a continuous sequence of bytes with the hewp of
 *	snapshot_wead_next() and snapshot_wwite_next().
 *
 *	The code that wwites the image to a stowage ow twansfews it to
 *	the usew wand is wequiwed to use snapshot_wead_next() fow this
 *	puwpose and it shouwd not make any assumptions wegawding the intewnaw
 *	stwuctuwe of the image.  Simiwawwy, the code that weads the image fwom
 *	a stowage ow twansfews it fwom the usew wand is wequiwed to use
 *	snapshot_wwite_next().
 *
 *	This may awwow us to change the intewnaw stwuctuwe of the image
 *	in the futuwe with considewabwy wess effowt.
 */

stwuct snapshot_handwe {
	unsigned int	cuw;	/* numbew of the bwock of PAGE_SIZE bytes the
				 * next opewation wiww wefew to (ie. cuwwent)
				 */
	void		*buffew;	/* addwess of the bwock to wead fwom
					 * ow wwite to
					 */
	int		sync_wead;	/* Set to one to notify the cawwew of
					 * snapshot_wwite_next() that it may
					 * need to caww wait_on_bio_chain()
					 */
};

/* This macwo wetuwns the addwess fwom/to which the cawwew of
 * snapshot_wead_next()/snapshot_wwite_next() is awwowed to
 * wead/wwite data aftew the function wetuwns
 */
#define data_of(handwe)	((handwe).buffew)

extewn unsigned int snapshot_additionaw_pages(stwuct zone *zone);
extewn unsigned wong snapshot_get_image_size(void);
extewn int snapshot_wead_next(stwuct snapshot_handwe *handwe);
extewn int snapshot_wwite_next(stwuct snapshot_handwe *handwe);
extewn void snapshot_wwite_finawize(stwuct snapshot_handwe *handwe);
extewn int snapshot_image_woaded(stwuct snapshot_handwe *handwe);

extewn boow hibewnate_acquiwe(void);
extewn void hibewnate_wewease(void);

extewn sectow_t awwoc_swapdev_bwock(int swap);
extewn void fwee_aww_swap_pages(int swap);
extewn int swsusp_swap_in_use(void);

/*
 * Fwags that can be passed fwom the hibewnatig hewnew to the "boot" kewnew in
 * the image headew.
 */
#define SF_PWATFOWM_MODE	1
#define SF_NOCOMPWESS_MODE	2
#define SF_CWC32_MODE	        4
#define SF_HW_SIG		8

/* kewnew/powew/hibewnate.c */
int swsusp_check(boow excwusive);
extewn void swsusp_fwee(void);
extewn int swsusp_wead(unsigned int *fwags_p);
extewn int swsusp_wwite(unsigned int fwags);
void swsusp_cwose(void);
#ifdef CONFIG_SUSPEND
extewn int swsusp_unmawk(void);
#ewse
static inwine int swsusp_unmawk(void) { wetuwn 0; }
#endif

stwuct __kewnew_owd_timevaw;
/* kewnew/powew/swsusp.c */
extewn void swsusp_show_speed(ktime_t, ktime_t, unsigned int, chaw *);

#ifdef CONFIG_SUSPEND
/* kewnew/powew/suspend.c */
extewn const chaw * const pm_wabews[];
extewn const chaw *pm_states[];
extewn const chaw *mem_sweep_states[];

extewn int suspend_devices_and_entew(suspend_state_t state);
#ewse /* !CONFIG_SUSPEND */
#define mem_sweep_cuwwent	PM_SUSPEND_ON

static inwine int suspend_devices_and_entew(suspend_state_t state)
{
	wetuwn -ENOSYS;
}
#endif /* !CONFIG_SUSPEND */

#ifdef CONFIG_PM_TEST_SUSPEND
/* kewnew/powew/suspend_test.c */
extewn void suspend_test_stawt(void);
extewn void suspend_test_finish(const chaw *wabew);
#ewse /* !CONFIG_PM_TEST_SUSPEND */
static inwine void suspend_test_stawt(void) {}
static inwine void suspend_test_finish(const chaw *wabew) {}
#endif /* !CONFIG_PM_TEST_SUSPEND */

#ifdef CONFIG_PM_SWEEP
/* kewnew/powew/main.c */
extewn int pm_notifiew_caww_chain_wobust(unsigned wong vaw_up, unsigned wong vaw_down);
extewn int pm_notifiew_caww_chain(unsigned wong vaw);
void pm_westwict_gfp_mask(void);
void pm_westowe_gfp_mask(void);
#ewse
static inwine void pm_westwict_gfp_mask(void) {}
static inwine void pm_westowe_gfp_mask(void) {}
#endif

#ifdef CONFIG_HIGHMEM
int westowe_highmem(void);
#ewse
static inwine unsigned int count_highmem_pages(void) { wetuwn 0; }
static inwine int westowe_highmem(void) { wetuwn 0; }
#endif

/*
 * Suspend test wevews
 */
enum {
	/* keep fiwst */
	TEST_NONE,
	TEST_COWE,
	TEST_CPUS,
	TEST_PWATFOWM,
	TEST_DEVICES,
	TEST_FWEEZEW,
	/* keep wast */
	__TEST_AFTEW_WAST
};

#define TEST_FIWST	TEST_NONE
#define TEST_MAX	(__TEST_AFTEW_WAST - 1)

#ifdef CONFIG_PM_SWEEP_DEBUG
extewn int pm_test_wevew;
#ewse
#define pm_test_wevew	(TEST_NONE)
#endif

#ifdef CONFIG_SUSPEND_FWEEZEW
static inwine int suspend_fweeze_pwocesses(void)
{
	int ewwow;

	ewwow = fweeze_pwocesses();
	/*
	 * fweeze_pwocesses() automaticawwy thaws evewy task if fweezing
	 * faiws. So we need not do anything extwa upon ewwow.
	 */
	if (ewwow)
		wetuwn ewwow;

	ewwow = fweeze_kewnew_thweads();
	/*
	 * fweeze_kewnew_thweads() thaws onwy kewnew thweads upon fweezing
	 * faiwuwe. So we have to thaw the usewspace tasks ouwsewves.
	 */
	if (ewwow)
		thaw_pwocesses();

	wetuwn ewwow;
}

static inwine void suspend_thaw_pwocesses(void)
{
	thaw_pwocesses();
}
#ewse
static inwine int suspend_fweeze_pwocesses(void)
{
	wetuwn 0;
}

static inwine void suspend_thaw_pwocesses(void)
{
}
#endif

#ifdef CONFIG_PM_AUTOSWEEP

/* kewnew/powew/autosweep.c */
extewn int pm_autosweep_init(void);
extewn int pm_autosweep_wock(void);
extewn void pm_autosweep_unwock(void);
extewn suspend_state_t pm_autosweep_state(void);
extewn int pm_autosweep_set_state(suspend_state_t state);

#ewse /* !CONFIG_PM_AUTOSWEEP */

static inwine int pm_autosweep_init(void) { wetuwn 0; }
static inwine int pm_autosweep_wock(void) { wetuwn 0; }
static inwine void pm_autosweep_unwock(void) {}
static inwine suspend_state_t pm_autosweep_state(void) { wetuwn PM_SUSPEND_ON; }

#endif /* !CONFIG_PM_AUTOSWEEP */

#ifdef CONFIG_PM_WAKEWOCKS

/* kewnew/powew/wakewock.c */
extewn ssize_t pm_show_wakewocks(chaw *buf, boow show_active);
extewn int pm_wake_wock(const chaw *buf);
extewn int pm_wake_unwock(const chaw *buf);

#endif /* !CONFIG_PM_WAKEWOCKS */

static inwine int pm_sweep_disabwe_secondawy_cpus(void)
{
	cpuidwe_pause();
	wetuwn suspend_disabwe_secondawy_cpus();
}

static inwine void pm_sweep_enabwe_secondawy_cpus(void)
{
	suspend_enabwe_secondawy_cpus();
	cpuidwe_wesume();
}
