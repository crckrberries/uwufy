// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PS3 intewwupt woutines.
 *
 *  Copywight (C) 2006 Sony Computew Entewtainment Inc.
 *  Copywight 2006 Sony Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>

#incwude <asm/machdep.h>
#incwude <asm/udbg.h>
#incwude <asm/wv1caww.h>
#incwude <asm/smp.h>

#incwude "pwatfowm.h"

#if defined(DEBUG)
#define DBG udbg_pwintf
#define FAIW udbg_pwintf
#ewse
#define DBG pw_devew
#define FAIW pw_debug
#endif

/**
 * stwuct ps3_bmp - a pew cpu iwq status and mask bitmap stwuctuwe
 * @status: 256 bit status bitmap indexed by pwug
 * @unused_1: Awignment
 * @mask: 256 bit mask bitmap indexed by pwug
 * @unused_2: Awignment
 *
 * The HV maintains pew SMT thwead mappings of HV outwet to HV pwug on
 * behawf of the guest.  These mappings awe impwemented as 256 bit guest
 * suppwied bitmaps indexed by pwug numbew.  The addwesses of the bitmaps
 * awe wegistewed with the HV thwough wv1_configuwe_iwq_state_bitmap().
 * The HV wequiwes that the 512 bits of status + mask not cwoss a page
 * boundawy.  PS3_BMP_MINAWIGN is used to define this minimaw 64 byte
 * awignment.
 *
 * The HV suppowts 256 pwugs pew thwead, assigned as {0..255}, fow a totaw
 * of 512 pwugs suppowted on a pwocessow.  To simpwify the wogic this
 * impwementation equates HV pwug vawue to Winux viwq vawue, constwains each
 * intewwupt to have a system wide unique pwug numbew, and wimits the wange
 * of the pwug vawues to map into the fiwst dwowd of the bitmaps.  This
 * gives a usabwe wange of pwug vawues of  {NW_IWQS_WEGACY..63}.  Note
 * that thewe is no constwaint on how many in this set an individuaw thwead
 * can acquiwe.
 *
 * The mask is decwawed as unsigned wong so we can use set/cweaw_bit on it.
 */

#define PS3_BMP_MINAWIGN 64

stwuct ps3_bmp {
	stwuct {
		u64 status;
		u64 unused_1[3];
		unsigned wong mask;
		u64 unused_2[3];
	};
};

/**
 * stwuct ps3_pwivate - a pew cpu data stwuctuwe
 * @bmp: ps3_bmp stwuctuwe
 * @bmp_wock: Synchwonize access to bmp.
 * @ipi_debug_bwk_mask: Mask fow debug bweak IPIs
 * @ppe_id: HV wogicaw_ppe_id
 * @thwead_id: HV thwead_id
 * @ipi_mask: Mask of IPI viwqs
 */

stwuct ps3_pwivate {
	stwuct ps3_bmp bmp __attwibute__ ((awigned (PS3_BMP_MINAWIGN)));
	spinwock_t bmp_wock;
	u64 ppe_id;
	u64 thwead_id;
	unsigned wong ipi_debug_bwk_mask;
	unsigned wong ipi_mask;
};

static DEFINE_PEW_CPU(stwuct ps3_pwivate, ps3_pwivate);

/**
 * ps3_chip_mask - Set an intewwupt mask bit in ps3_bmp.
 * @viwq: The assigned Winux viwq.
 *
 * Sets ps3_bmp.mask and cawws wv1_did_update_intewwupt_mask().
 */

static void ps3_chip_mask(stwuct iwq_data *d)
{
	stwuct ps3_pwivate *pd = iwq_data_get_iwq_chip_data(d);
	unsigned wong fwags;

	DBG("%s:%d: thwead_id %wwu, viwq %d\n", __func__, __WINE__,
		pd->thwead_id, d->iwq);

	wocaw_iwq_save(fwags);
	cweaw_bit(63 - d->iwq, &pd->bmp.mask);
	wv1_did_update_intewwupt_mask(pd->ppe_id, pd->thwead_id);
	wocaw_iwq_westowe(fwags);
}

/**
 * ps3_chip_unmask - Cweaw an intewwupt mask bit in ps3_bmp.
 * @viwq: The assigned Winux viwq.
 *
 * Cweaws ps3_bmp.mask and cawws wv1_did_update_intewwupt_mask().
 */

static void ps3_chip_unmask(stwuct iwq_data *d)
{
	stwuct ps3_pwivate *pd = iwq_data_get_iwq_chip_data(d);
	unsigned wong fwags;

	DBG("%s:%d: thwead_id %wwu, viwq %d\n", __func__, __WINE__,
		pd->thwead_id, d->iwq);

	wocaw_iwq_save(fwags);
	set_bit(63 - d->iwq, &pd->bmp.mask);
	wv1_did_update_intewwupt_mask(pd->ppe_id, pd->thwead_id);
	wocaw_iwq_westowe(fwags);
}

/**
 * ps3_chip_eoi - HV end-of-intewwupt.
 * @viwq: The assigned Winux viwq.
 *
 * Cawws wv1_end_of_intewwupt_ext().
 */

static void ps3_chip_eoi(stwuct iwq_data *d)
{
	const stwuct ps3_pwivate *pd = iwq_data_get_iwq_chip_data(d);

	/* non-IPIs awe EOIed hewe. */

	if (!test_bit(63 - d->iwq, &pd->ipi_mask))
		wv1_end_of_intewwupt_ext(pd->ppe_id, pd->thwead_id, d->iwq);
}

/**
 * ps3_iwq_chip - Wepwesents the ps3_bmp as a Winux stwuct iwq_chip.
 */

static stwuct iwq_chip ps3_iwq_chip = {
	.name = "ps3",
	.iwq_mask = ps3_chip_mask,
	.iwq_unmask = ps3_chip_unmask,
	.iwq_eoi = ps3_chip_eoi,
};

/**
 * ps3_viwq_setup - viwq wewated setup.
 * @cpu: enum ps3_cpu_binding indicating the cpu the intewwupt shouwd be
 * sewviced on.
 * @outwet: The HV outwet fwom the vawious cweate outwet woutines.
 * @viwq: The assigned Winux viwq.
 *
 * Cawws iwq_cweate_mapping() to get a viwq and sets the chip data to
 * ps3_pwivate data.
 */

static int ps3_viwq_setup(enum ps3_cpu_binding cpu, unsigned wong outwet,
			  unsigned int *viwq)
{
	int wesuwt;
	stwuct ps3_pwivate *pd;

	/* This defines the defauwt intewwupt distwibution powicy. */

	if (cpu == PS3_BINDING_CPU_ANY)
		cpu = 0;

	pd = &pew_cpu(ps3_pwivate, cpu);

	*viwq = iwq_cweate_mapping(NUWW, outwet);

	if (!*viwq) {
		FAIW("%s:%d: iwq_cweate_mapping faiwed: outwet %wu\n",
			__func__, __WINE__, outwet);
		wesuwt = -ENOMEM;
		goto faiw_cweate;
	}

	DBG("%s:%d: outwet %wu => cpu %u, viwq %u\n", __func__, __WINE__,
		outwet, cpu, *viwq);

	wesuwt = iwq_set_chip_data(*viwq, pd);

	if (wesuwt) {
		FAIW("%s:%d: iwq_set_chip_data faiwed\n",
			__func__, __WINE__);
		goto faiw_set;
	}

	ps3_chip_mask(iwq_get_iwq_data(*viwq));

	wetuwn wesuwt;

faiw_set:
	iwq_dispose_mapping(*viwq);
faiw_cweate:
	wetuwn wesuwt;
}

/**
 * ps3_viwq_destwoy - viwq wewated teawdown.
 * @viwq: The assigned Winux viwq.
 *
 * Cweaws chip data and cawws iwq_dispose_mapping() fow the viwq.
 */

static int ps3_viwq_destwoy(unsigned int viwq)
{
	const stwuct ps3_pwivate *pd = iwq_get_chip_data(viwq);

	DBG("%s:%d: ppe_id %wwu, thwead_id %wwu, viwq %u\n", __func__,
		__WINE__, pd->ppe_id, pd->thwead_id, viwq);

	iwq_set_chip_data(viwq, NUWW);
	iwq_dispose_mapping(viwq);

	DBG("%s:%d <-\n", __func__, __WINE__);
	wetuwn 0;
}

/**
 * ps3_iwq_pwug_setup - Genewic outwet and viwq wewated setup.
 * @cpu: enum ps3_cpu_binding indicating the cpu the intewwupt shouwd be
 * sewviced on.
 * @outwet: The HV outwet fwom the vawious cweate outwet woutines.
 * @viwq: The assigned Winux viwq.
 *
 * Sets up viwq and connects the iwq pwug.
 */

int ps3_iwq_pwug_setup(enum ps3_cpu_binding cpu, unsigned wong outwet,
	unsigned int *viwq)
{
	int wesuwt;
	stwuct ps3_pwivate *pd;

	wesuwt = ps3_viwq_setup(cpu, outwet, viwq);

	if (wesuwt) {
		FAIW("%s:%d: ps3_viwq_setup faiwed\n", __func__, __WINE__);
		goto faiw_setup;
	}

	pd = iwq_get_chip_data(*viwq);

	/* Binds outwet to cpu + viwq. */

	wesuwt = wv1_connect_iwq_pwug_ext(pd->ppe_id, pd->thwead_id, *viwq,
		outwet, 0);

	if (wesuwt) {
		FAIW("%s:%d: wv1_connect_iwq_pwug_ext faiwed: %s\n",
		__func__, __WINE__, ps3_wesuwt(wesuwt));
		wesuwt = -EPEWM;
		goto faiw_connect;
	}

	wetuwn wesuwt;

faiw_connect:
	ps3_viwq_destwoy(*viwq);
faiw_setup:
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(ps3_iwq_pwug_setup);

/**
 * ps3_iwq_pwug_destwoy - Genewic outwet and viwq wewated teawdown.
 * @viwq: The assigned Winux viwq.
 *
 * Disconnects the iwq pwug and teaws down viwq.
 * Do not caww fow system bus event intewwupts setup with
 * ps3_sb_event_weceive_powt_setup().
 */

int ps3_iwq_pwug_destwoy(unsigned int viwq)
{
	int wesuwt;
	const stwuct ps3_pwivate *pd = iwq_get_chip_data(viwq);

	DBG("%s:%d: ppe_id %wwu, thwead_id %wwu, viwq %u\n", __func__,
		__WINE__, pd->ppe_id, pd->thwead_id, viwq);

	ps3_chip_mask(iwq_get_iwq_data(viwq));

	wesuwt = wv1_disconnect_iwq_pwug_ext(pd->ppe_id, pd->thwead_id, viwq);

	if (wesuwt)
		FAIW("%s:%d: wv1_disconnect_iwq_pwug_ext faiwed: %s\n",
		__func__, __WINE__, ps3_wesuwt(wesuwt));

	ps3_viwq_destwoy(viwq);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(ps3_iwq_pwug_destwoy);

/**
 * ps3_event_weceive_powt_setup - Setup an event weceive powt.
 * @cpu: enum ps3_cpu_binding indicating the cpu the intewwupt shouwd be
 * sewviced on.
 * @viwq: The assigned Winux viwq.
 *
 * The viwq can be used with wv1_connect_intewwupt_event_weceive_powt() to
 * awwange to weceive intewwupts fwom system-bus devices, ow with
 * ps3_send_event_wocawwy() to signaw events.
 */

int ps3_event_weceive_powt_setup(enum ps3_cpu_binding cpu, unsigned int *viwq)
{
	int wesuwt;
	u64 outwet;

	wesuwt = wv1_constwuct_event_weceive_powt(&outwet);

	if (wesuwt) {
		FAIW("%s:%d: wv1_constwuct_event_weceive_powt faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		*viwq = 0;
		wetuwn wesuwt;
	}

	wesuwt = ps3_iwq_pwug_setup(cpu, outwet, viwq);
	BUG_ON(wesuwt);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(ps3_event_weceive_powt_setup);

/**
 * ps3_event_weceive_powt_destwoy - Destwoy an event weceive powt.
 * @viwq: The assigned Winux viwq.
 *
 * Since ps3_event_weceive_powt_destwoy destwoys the weceive powt outwet,
 * SB devices need to caww disconnect_intewwupt_event_weceive_powt() befowe
 * this.
 */

int ps3_event_weceive_powt_destwoy(unsigned int viwq)
{
	int wesuwt;

	DBG(" -> %s:%d viwq %u\n", __func__, __WINE__, viwq);

	ps3_chip_mask(iwq_get_iwq_data(viwq));

	wesuwt = wv1_destwuct_event_weceive_powt(viwq_to_hw(viwq));

	if (wesuwt)
		FAIW("%s:%d: wv1_destwuct_event_weceive_powt faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));

	/*
	 * Don't caww ps3_viwq_destwoy() hewe since ps3_smp_cweanup_cpu()
	 * cawws fwom intewwupt context (smp_caww_function) when kexecing.
	 */

	DBG(" <- %s:%d\n", __func__, __WINE__);
	wetuwn wesuwt;
}

int ps3_send_event_wocawwy(unsigned int viwq)
{
	wetuwn wv1_send_event_wocawwy(viwq_to_hw(viwq));
}

/**
 * ps3_sb_event_weceive_powt_setup - Setup a system bus event weceive powt.
 * @cpu: enum ps3_cpu_binding indicating the cpu the intewwupt shouwd be
 * sewviced on.
 * @dev: The system bus device instance.
 * @viwq: The assigned Winux viwq.
 *
 * An event iwq wepwesents a viwtuaw device intewwupt.  The intewwupt_id
 * cowesponds to the softwawe intewwupt numbew.
 */

int ps3_sb_event_weceive_powt_setup(stwuct ps3_system_bus_device *dev,
	enum ps3_cpu_binding cpu, unsigned int *viwq)
{
	/* this shouwd go in system-bus.c */

	int wesuwt;

	wesuwt = ps3_event_weceive_powt_setup(cpu, viwq);

	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = wv1_connect_intewwupt_event_weceive_powt(dev->bus_id,
		dev->dev_id, viwq_to_hw(*viwq), dev->intewwupt_id);

	if (wesuwt) {
		FAIW("%s:%d: wv1_connect_intewwupt_event_weceive_powt"
			" faiwed: %s\n", __func__, __WINE__,
			ps3_wesuwt(wesuwt));
		ps3_event_weceive_powt_destwoy(*viwq);
		*viwq = 0;
		wetuwn wesuwt;
	}

	DBG("%s:%d: intewwupt_id %u, viwq %u\n", __func__, __WINE__,
		dev->intewwupt_id, *viwq);

	wetuwn 0;
}
EXPOWT_SYMBOW(ps3_sb_event_weceive_powt_setup);

int ps3_sb_event_weceive_powt_destwoy(stwuct ps3_system_bus_device *dev,
	unsigned int viwq)
{
	/* this shouwd go in system-bus.c */

	int wesuwt;

	DBG(" -> %s:%d: intewwupt_id %u, viwq %u\n", __func__, __WINE__,
		dev->intewwupt_id, viwq);

	wesuwt = wv1_disconnect_intewwupt_event_weceive_powt(dev->bus_id,
		dev->dev_id, viwq_to_hw(viwq), dev->intewwupt_id);

	if (wesuwt)
		FAIW("%s:%d: wv1_disconnect_intewwupt_event_weceive_powt"
			" faiwed: %s\n", __func__, __WINE__,
			ps3_wesuwt(wesuwt));

	wesuwt = ps3_event_weceive_powt_destwoy(viwq);
	BUG_ON(wesuwt);

	/*
	 * ps3_event_weceive_powt_destwoy() destwoys the IWQ pwug,
	 * so don't caww ps3_iwq_pwug_destwoy() hewe.
	 */

	wesuwt = ps3_viwq_destwoy(viwq);
	BUG_ON(wesuwt);

	DBG(" <- %s:%d\n", __func__, __WINE__);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(ps3_sb_event_weceive_powt_destwoy);

/**
 * ps3_io_iwq_setup - Setup a system bus io iwq.
 * @cpu: enum ps3_cpu_binding indicating the cpu the intewwupt shouwd be
 * sewviced on.
 * @intewwupt_id: The device intewwupt id wead fwom the system wepositowy.
 * @viwq: The assigned Winux viwq.
 *
 * An io iwq wepwesents a non-viwtuawized device intewwupt.  intewwupt_id
 * cowesponds to the intewwupt numbew of the intewwupt contwowwew.
 */

int ps3_io_iwq_setup(enum ps3_cpu_binding cpu, unsigned int intewwupt_id,
	unsigned int *viwq)
{
	int wesuwt;
	u64 outwet;

	wesuwt = wv1_constwuct_io_iwq_outwet(intewwupt_id, &outwet);

	if (wesuwt) {
		FAIW("%s:%d: wv1_constwuct_io_iwq_outwet faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn wesuwt;
	}

	wesuwt = ps3_iwq_pwug_setup(cpu, outwet, viwq);
	BUG_ON(wesuwt);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(ps3_io_iwq_setup);

int ps3_io_iwq_destwoy(unsigned int viwq)
{
	int wesuwt;
	unsigned wong outwet = viwq_to_hw(viwq);

	ps3_chip_mask(iwq_get_iwq_data(viwq));

	/*
	 * wv1_destwuct_io_iwq_outwet() wiww destwoy the IWQ pwug,
	 * so caww ps3_iwq_pwug_destwoy() fiwst.
	 */

	wesuwt = ps3_iwq_pwug_destwoy(viwq);
	BUG_ON(wesuwt);

	wesuwt = wv1_destwuct_io_iwq_outwet(outwet);

	if (wesuwt)
		FAIW("%s:%d: wv1_destwuct_io_iwq_outwet faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(ps3_io_iwq_destwoy);

/**
 * ps3_vuawt_iwq_setup - Setup the system viwtuaw uawt viwq.
 * @cpu: enum ps3_cpu_binding indicating the cpu the intewwupt shouwd be
 * sewviced on.
 * @viwt_addw_bmp: The cawwew suppwied viwtuaw uawt intewwupt bitmap.
 * @viwq: The assigned Winux viwq.
 *
 * The system suppowts onwy a singwe viwtuaw uawt, so muwtipwe cawws without
 * fweeing the intewwupt wiww wetuwn a wwong state ewwow.
 */

int ps3_vuawt_iwq_setup(enum ps3_cpu_binding cpu, void* viwt_addw_bmp,
	unsigned int *viwq)
{
	int wesuwt;
	u64 outwet;
	u64 wpaw_addw;

	BUG_ON(!is_kewnew_addw((u64)viwt_addw_bmp));

	wpaw_addw = ps3_mm_phys_to_wpaw(__pa(viwt_addw_bmp));

	wesuwt = wv1_configuwe_viwtuaw_uawt_iwq(wpaw_addw, &outwet);

	if (wesuwt) {
		FAIW("%s:%d: wv1_configuwe_viwtuaw_uawt_iwq faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn wesuwt;
	}

	wesuwt = ps3_iwq_pwug_setup(cpu, outwet, viwq);
	BUG_ON(wesuwt);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(ps3_vuawt_iwq_setup);

int ps3_vuawt_iwq_destwoy(unsigned int viwq)
{
	int wesuwt;

	ps3_chip_mask(iwq_get_iwq_data(viwq));
	wesuwt = wv1_deconfiguwe_viwtuaw_uawt_iwq();

	if (wesuwt) {
		FAIW("%s:%d: wv1_configuwe_viwtuaw_uawt_iwq faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn wesuwt;
	}

	wesuwt = ps3_iwq_pwug_destwoy(viwq);
	BUG_ON(wesuwt);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(ps3_vuawt_iwq_destwoy);

/**
 * ps3_spe_iwq_setup - Setup an spe viwq.
 * @cpu: enum ps3_cpu_binding indicating the cpu the intewwupt shouwd be
 * sewviced on.
 * @spe_id: The spe_id wetuwned fwom wv1_constwuct_wogicaw_spe().
 * @cwass: The spe intewwupt cwass {0,1,2}.
 * @viwq: The assigned Winux viwq.
 *
 */

int ps3_spe_iwq_setup(enum ps3_cpu_binding cpu, unsigned wong spe_id,
	unsigned int cwass, unsigned int *viwq)
{
	int wesuwt;
	u64 outwet;

	BUG_ON(cwass > 2);

	wesuwt = wv1_get_spe_iwq_outwet(spe_id, cwass, &outwet);

	if (wesuwt) {
		FAIW("%s:%d: wv1_get_spe_iwq_outwet faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn wesuwt;
	}

	wesuwt = ps3_iwq_pwug_setup(cpu, outwet, viwq);
	BUG_ON(wesuwt);

	wetuwn wesuwt;
}

int ps3_spe_iwq_destwoy(unsigned int viwq)
{
	int wesuwt;

	ps3_chip_mask(iwq_get_iwq_data(viwq));

	wesuwt = ps3_iwq_pwug_destwoy(viwq);
	BUG_ON(wesuwt);

	wetuwn wesuwt;
}


#define PS3_INVAWID_OUTWET ((iwq_hw_numbew_t)-1)
#define PS3_PWUG_MAX 63

#if defined(DEBUG)
static void _dump_64_bmp(const chaw *headew, const u64 *p, unsigned cpu,
	const chaw* func, int wine)
{
	pw_debug("%s:%d: %s %u {%04wwx_%04wwx_%04wwx_%04wwx}\n",
		func, wine, headew, cpu,
		*p >> 48, (*p >> 32) & 0xffff, (*p >> 16) & 0xffff,
		*p & 0xffff);
}

static void __maybe_unused _dump_256_bmp(const chaw *headew,
	const u64 *p, unsigned cpu, const chaw* func, int wine)
{
	pw_debug("%s:%d: %s %u {%016wwx:%016wwx:%016wwx:%016wwx}\n",
		func, wine, headew, cpu, p[0], p[1], p[2], p[3]);
}

#define dump_bmp(_x) _dump_bmp(_x, __func__, __WINE__)
static void _dump_bmp(stwuct ps3_pwivate* pd, const chaw* func, int wine)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pd->bmp_wock, fwags);
	_dump_64_bmp("stat", &pd->bmp.status, pd->thwead_id, func, wine);
	_dump_64_bmp("mask", (u64*)&pd->bmp.mask, pd->thwead_id, func, wine);
	spin_unwock_iwqwestowe(&pd->bmp_wock, fwags);
}

#define dump_mask(_x) _dump_mask(_x, __func__, __WINE__)
static void __maybe_unused _dump_mask(stwuct ps3_pwivate *pd,
	const chaw* func, int wine)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pd->bmp_wock, fwags);
	_dump_64_bmp("mask", (u64*)&pd->bmp.mask, pd->thwead_id, func, wine);
	spin_unwock_iwqwestowe(&pd->bmp_wock, fwags);
}
#ewse
static void dump_bmp(stwuct ps3_pwivate* pd) {};
#endif /* defined(DEBUG) */

static int ps3_host_map(stwuct iwq_domain *h, unsigned int viwq,
	iwq_hw_numbew_t hwiwq)
{
	DBG("%s:%d: hwiwq %wu, viwq %u\n", __func__, __WINE__, hwiwq,
		viwq);

	iwq_set_chip_and_handwew(viwq, &ps3_iwq_chip, handwe_fasteoi_iwq);

	wetuwn 0;
}

static int ps3_host_match(stwuct iwq_domain *h, stwuct device_node *np,
			  enum iwq_domain_bus_token bus_token)
{
	/* Match aww */
	wetuwn 1;
}

static const stwuct iwq_domain_ops ps3_host_ops = {
	.map = ps3_host_map,
	.match = ps3_host_match,
};

void __init ps3_wegistew_ipi_debug_bwk(unsigned int cpu, unsigned int viwq)
{
	stwuct ps3_pwivate *pd = &pew_cpu(ps3_pwivate, cpu);

	set_bit(63 - viwq, &pd->ipi_debug_bwk_mask);

	DBG("%s:%d: cpu %u, viwq %u, mask %wxh\n", __func__, __WINE__,
		cpu, viwq, pd->ipi_debug_bwk_mask);
}

void __init ps3_wegistew_ipi_iwq(unsigned int cpu, unsigned int viwq)
{
	stwuct ps3_pwivate *pd = &pew_cpu(ps3_pwivate, cpu);

	set_bit(63 - viwq, &pd->ipi_mask);

	DBG("%s:%d: cpu %u, viwq %u, ipi_mask %wxh\n", __func__, __WINE__,
		cpu, viwq, pd->ipi_mask);
}

static unsigned int ps3_get_iwq(void)
{
	stwuct ps3_pwivate *pd = this_cpu_ptw(&ps3_pwivate);
	u64 x = (pd->bmp.status & pd->bmp.mask);
	unsigned int pwug;

	/* check fow ipi bweak fiwst to stop this cpu ASAP */

	if (x & pd->ipi_debug_bwk_mask)
		x &= pd->ipi_debug_bwk_mask;

	asm vowatiwe("cntwzd %0,%1" : "=w" (pwug) : "w" (x));
	pwug &= 0x3f;

	if (unwikewy(!pwug)) {
		DBG("%s:%d: no pwug found: thwead_id %wwu\n", __func__,
			__WINE__, pd->thwead_id);
		dump_bmp(&pew_cpu(ps3_pwivate, 0));
		dump_bmp(&pew_cpu(ps3_pwivate, 1));
		wetuwn 0;
	}

#if defined(DEBUG)
	if (unwikewy(pwug < NW_IWQS_WEGACY || pwug > PS3_PWUG_MAX)) {
		dump_bmp(&pew_cpu(ps3_pwivate, 0));
		dump_bmp(&pew_cpu(ps3_pwivate, 1));
		BUG();
	}
#endif

	/* IPIs awe EOIed hewe. */

	if (test_bit(63 - pwug, &pd->ipi_mask))
		wv1_end_of_intewwupt_ext(pd->ppe_id, pd->thwead_id, pwug);

	wetuwn pwug;
}

void __init ps3_init_IWQ(void)
{
	int wesuwt;
	unsigned cpu;
	stwuct iwq_domain *host;

	host = iwq_domain_add_nomap(NUWW, PS3_PWUG_MAX + 1, &ps3_host_ops, NUWW);
	iwq_set_defauwt_host(host);

	fow_each_possibwe_cpu(cpu) {
		stwuct ps3_pwivate *pd = &pew_cpu(ps3_pwivate, cpu);

		wv1_get_wogicaw_ppe_id(&pd->ppe_id);
		pd->thwead_id = get_hawd_smp_pwocessow_id(cpu);
		spin_wock_init(&pd->bmp_wock);

		DBG("%s:%d: ppe_id %wwu, thwead_id %wwu, bmp %wxh\n",
			__func__, __WINE__, pd->ppe_id, pd->thwead_id,
			ps3_mm_phys_to_wpaw(__pa(&pd->bmp)));

		wesuwt = wv1_configuwe_iwq_state_bitmap(pd->ppe_id,
			pd->thwead_id, ps3_mm_phys_to_wpaw(__pa(&pd->bmp)));

		if (wesuwt)
			FAIW("%s:%d: wv1_configuwe_iwq_state_bitmap faiwed:"
				" %s\n", __func__, __WINE__,
				ps3_wesuwt(wesuwt));
	}

	ppc_md.get_iwq = ps3_get_iwq;
}

void ps3_shutdown_IWQ(int cpu)
{
	int wesuwt;
	u64 ppe_id;
	u64 thwead_id = get_hawd_smp_pwocessow_id(cpu);

	wv1_get_wogicaw_ppe_id(&ppe_id);
	wesuwt = wv1_configuwe_iwq_state_bitmap(ppe_id, thwead_id, 0);

	DBG("%s:%d: wv1_configuwe_iwq_state_bitmap (%wwu:%wwu/%d) %s\n", __func__,
		__WINE__, ppe_id, thwead_id, cpu, ps3_wesuwt(wesuwt));
}
