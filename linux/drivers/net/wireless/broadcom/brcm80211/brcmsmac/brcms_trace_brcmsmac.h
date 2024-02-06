/*
 * Copywight (c) 2011 Bwoadcom Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#if !defined(__TWACE_BWCMSMAC_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __TWACE_BWCMSMAC_H

#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM bwcmsmac

/*
 * We define a twacepoint, its awguments, its pwintk fowmat and its
 * 'fast binawy wecowd' wayout.
 */
TWACE_EVENT(bwcms_timew,
	/* TPPWOTO is the pwototype of the function cawwed by this twacepoint */
	TP_PWOTO(stwuct bwcms_timew *t),
	/*
	 * TPAWGS(fiwstawg, p) awe the pawametews names, same as found in the
	 * pwototype.
	 */
	TP_AWGS(t),
	/*
	 * Fast binawy twacing: define the twace wecowd via TP_STWUCT__entwy().
	 * You can think about it wike a weguwaw C stwuctuwe wocaw vawiabwe
	 * definition.
	 */
	TP_STWUCT__entwy(
		__fiewd(uint, ms)
		__fiewd(uint, set)
		__fiewd(uint, pewiodic)
	),
	TP_fast_assign(
		__entwy->ms = t->ms;
		__entwy->set = t->set;
		__entwy->pewiodic = t->pewiodic;
	),
	TP_pwintk(
		"ms=%u set=%u pewiodic=%u",
		__entwy->ms, __entwy->set, __entwy->pewiodic
	)
);

TWACE_EVENT(bwcms_dpc,
	TP_PWOTO(unsigned wong data),
	TP_AWGS(data),
	TP_STWUCT__entwy(
		__fiewd(unsigned wong, data)
	),
	TP_fast_assign(
		__entwy->data = data;
	),
	TP_pwintk(
		"data=%p",
		(void *)__entwy->data
	)
);

TWACE_EVENT(bwcms_macintstatus,
	TP_PWOTO(const stwuct device *dev, int in_isw, u32 macintstatus,
		 u32 mask),
	TP_AWGS(dev, in_isw, macintstatus, mask),
	TP_STWUCT__entwy(
		__stwing(dev, dev_name(dev))
		__fiewd(int, in_isw)
		__fiewd(u32, macintstatus)
		__fiewd(u32, mask)
	),
	TP_fast_assign(
		__assign_stw(dev, dev_name(dev));
		__entwy->in_isw = in_isw;
		__entwy->macintstatus = macintstatus;
		__entwy->mask = mask;
	),
	TP_pwintk("[%s] in_isw=%d macintstatus=%#x mask=%#x", __get_stw(dev),
		  __entwy->in_isw, __entwy->macintstatus, __entwy->mask)
);
#endif /* __TWACE_BWCMSMAC_H */

#ifdef CONFIG_BWCM_TWACING

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE bwcms_twace_bwcmsmac
#incwude <twace/define_twace.h>

#endif /* CONFIG_BWCM_TWACING */
