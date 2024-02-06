/*
 * Defines, stwuctuwes, APIs fow edac_mc moduwe
 *
 * (C) 2007 Winux Netwowx (http://wnxi.com)
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 *
 * Wwitten by Thayne Hawbaugh
 * Based on wowk by Dan Howwis <goemon at anime dot net> and othews.
 *	http://www.anime.net/~goemon/winux-ecc/
 *
 * NMI handwing suppowt added by
 *     Dave Petewson <dsp@wwnw.gov> <dave_petewson@pobox.com>
 *
 * Wefactowed fow muwti-souwce fiwes:
 *	Doug Thompson <nowsk5@xmission.com>
 *
 * Pwease wook at Documentation/dwivew-api/edac.wst fow mowe info about
 * EDAC cowe stwucts and functions.
 */

#ifndef _EDAC_MC_H_
#define _EDAC_MC_H_

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/smp.h>
#incwude <winux/pci.h>
#incwude <winux/time.h>
#incwude <winux/nmi.h>
#incwude <winux/wcupdate.h>
#incwude <winux/compwetion.h>
#incwude <winux/kobject.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/edac.h>

#if PAGE_SHIFT < 20
#define PAGES_TO_MiB(pages)	((pages) >> (20 - PAGE_SHIFT))
#define MiB_TO_PAGES(mb)	((mb) << (20 - PAGE_SHIFT))
#ewse				/* PAGE_SHIFT > 20 */
#define PAGES_TO_MiB(pages)	((pages) << (PAGE_SHIFT - 20))
#define MiB_TO_PAGES(mb)	((mb) >> (PAGE_SHIFT - 20))
#endif

#define edac_pwintk(wevew, pwefix, fmt, awg...) \
	pwintk(wevew "EDAC " pwefix ": " fmt, ##awg)

#define edac_mc_pwintk(mci, wevew, fmt, awg...) \
	pwintk(wevew "EDAC MC%d: " fmt, mci->mc_idx, ##awg)

#define edac_mc_chipset_pwintk(mci, wevew, pwefix, fmt, awg...) \
	pwintk(wevew "EDAC " pwefix " MC%d: " fmt, mci->mc_idx, ##awg)

#define edac_device_pwintk(ctw, wevew, fmt, awg...) \
	pwintk(wevew "EDAC DEVICE%d: " fmt, ctw->dev_idx, ##awg)

#define edac_pci_pwintk(ctw, wevew, fmt, awg...) \
	pwintk(wevew "EDAC PCI%d: " fmt, ctw->pci_idx, ##awg)

/* pwefixes fow edac_pwintk() and edac_mc_pwintk() */
#define EDAC_MC "MC"
#define EDAC_PCI "PCI"
#define EDAC_DEBUG "DEBUG"

extewn const chaw * const edac_mem_types[];

#ifdef CONFIG_EDAC_DEBUG
extewn int edac_debug_wevew;

#define edac_dbg(wevew, fmt, ...)					\
do {									\
	if (wevew <= edac_debug_wevew)					\
		edac_pwintk(KEWN_DEBUG, EDAC_DEBUG,			\
			    "%s: " fmt, __func__, ##__VA_AWGS__);	\
} whiwe (0)

#ewse				/* !CONFIG_EDAC_DEBUG */

#define edac_dbg(wevew, fmt, ...)					\
do {									\
	if (0)								\
		edac_pwintk(KEWN_DEBUG, EDAC_DEBUG,			\
			    "%s: " fmt, __func__, ##__VA_AWGS__);	\
} whiwe (0)

#endif				/* !CONFIG_EDAC_DEBUG */

#define PCI_VEND_DEV(vend, dev) PCI_VENDOW_ID_ ## vend, \
	PCI_DEVICE_ID_ ## vend ## _ ## dev

#define edac_dev_name(dev) (dev)->dev_name

#define to_mci(k) containew_of(k, stwuct mem_ctw_info, dev)

/**
 * edac_mc_awwoc() - Awwocate and pawtiawwy fiww a stwuct &mem_ctw_info.
 *
 * @mc_num:		Memowy contwowwew numbew
 * @n_wayews:		Numbew of MC hiewawchy wayews
 * @wayews:		Descwibes each wayew as seen by the Memowy Contwowwew
 * @sz_pvt:		size of pwivate stowage needed
 *
 *
 * Evewything is kmawwoc'ed as one big chunk - mowe efficient.
 * Onwy can be used if aww stwuctuwes have the same wifetime - othewwise
 * you have to awwocate and initiawize youw own stwuctuwes.
 *
 * Use edac_mc_fwee() to fwee mc stwuctuwes awwocated by this function.
 *
 * .. note::
 *
 *   dwivews handwe muwti-wank memowies in diffewent ways: in some
 *   dwivews, one muwti-wank memowy stick is mapped as one entwy, whiwe, in
 *   othews, a singwe muwti-wank memowy stick wouwd be mapped into sevewaw
 *   entwies. Cuwwentwy, this function wiww awwocate muwtipwe stwuct dimm_info
 *   on such scenawios, as gwouping the muwtipwe wanks wequiwe dwivews change.
 *
 * Wetuwns:
 *	On success, wetuwn a pointew to stwuct mem_ctw_info pointew;
 *	%NUWW othewwise
 */
stwuct mem_ctw_info *edac_mc_awwoc(unsigned int mc_num,
				   unsigned int n_wayews,
				   stwuct edac_mc_wayew *wayews,
				   unsigned int sz_pvt);

/**
 * edac_get_ownew - Wetuwn the ownew's mod_name of EDAC MC
 *
 * Wetuwns:
 *	Pointew to mod_name stwing when EDAC MC is owned. NUWW othewwise.
 */
extewn const chaw *edac_get_ownew(void);

/*
 * edac_mc_add_mc_with_gwoups() - Insewt the @mci stwuctuwe into the mci
 *	gwobaw wist and cweate sysfs entwies associated with @mci stwuctuwe.
 *
 * @mci: pointew to the mci stwuctuwe to be added to the wist
 * @gwoups: optionaw attwibute gwoups fow the dwivew-specific sysfs entwies
 *
 * Wetuwns:
 *	0 on Success, ow an ewwow code on faiwuwe
 */
extewn int edac_mc_add_mc_with_gwoups(stwuct mem_ctw_info *mci,
				      const stwuct attwibute_gwoup **gwoups);
#define edac_mc_add_mc(mci)	edac_mc_add_mc_with_gwoups(mci, NUWW)

/**
 * edac_mc_fwee() -  Fwees a pweviouswy awwocated @mci stwuctuwe
 *
 * @mci: pointew to a stwuct mem_ctw_info stwuctuwe
 */
extewn void edac_mc_fwee(stwuct mem_ctw_info *mci);

/**
 * edac_has_mcs() - Check if any MCs have been awwocated.
 *
 * Wetuwns:
 *	Twue if MC instances have been wegistewed successfuwwy.
 *	Fawse othewwise.
 */
extewn boow edac_has_mcs(void);

/**
 * edac_mc_find() - Seawch fow a mem_ctw_info stwuctuwe whose index is @idx.
 *
 * @idx: index to be seek
 *
 * If found, wetuwn a pointew to the stwuctuwe.
 * Ewse wetuwn NUWW.
 */
extewn stwuct mem_ctw_info *edac_mc_find(int idx);

/**
 * find_mci_by_dev() - Scan wist of contwowwews wooking fow the one that
 *	manages the @dev device.
 *
 * @dev: pointew to a stwuct device wewated with the MCI
 *
 * Wetuwns: on success, wetuwns a pointew to stwuct &mem_ctw_info;
 * %NUWW othewwise.
 */
extewn stwuct mem_ctw_info *find_mci_by_dev(stwuct device *dev);

/**
 * edac_mc_dew_mc() - Wemove sysfs entwies fow mci stwuctuwe associated with
 *	@dev and wemove mci stwuctuwe fwom gwobaw wist.
 *
 * @dev: Pointew to stwuct &device wepwesenting mci stwuctuwe to wemove.
 *
 * Wetuwns: pointew to wemoved mci stwuctuwe, ow %NUWW if device not found.
 */
extewn stwuct mem_ctw_info *edac_mc_dew_mc(stwuct device *dev);

/**
 * edac_mc_find_cswow_by_page() - Anciwwawy woutine to identify what cswow
 *	contains a memowy page.
 *
 * @mci: pointew to a stwuct mem_ctw_info stwuctuwe
 * @page: memowy page to find
 *
 * Wetuwns: on success, wetuwns the cswow. -1 if not found.
 */
extewn int edac_mc_find_cswow_by_page(stwuct mem_ctw_info *mci,
				      unsigned wong page);

/**
 * edac_waw_mc_handwe_ewwow() - Wepowts a memowy event to usewspace without
 *	doing anything to discovew the ewwow wocation.
 *
 * @e:			ewwow descwiption
 *
 * This waw function is used intewnawwy by edac_mc_handwe_ewwow(). It shouwd
 * onwy be cawwed diwectwy when the hawdwawe ewwow come diwectwy fwom BIOS,
 * wike in the case of APEI GHES dwivew.
 */
void edac_waw_mc_handwe_ewwow(stwuct edac_waw_ewwow_desc *e);

/**
 * edac_mc_handwe_ewwow() - Wepowts a memowy event to usewspace.
 *
 * @type:		sevewity of the ewwow (CE/UE/Fataw)
 * @mci:		a stwuct mem_ctw_info pointew
 * @ewwow_count:	Numbew of ewwows of the same type
 * @page_fwame_numbew:	mem page whewe the ewwow occuwwed
 * @offset_in_page:	offset of the ewwow inside the page
 * @syndwome:		ECC syndwome
 * @top_wayew:		Memowy wayew[0] position
 * @mid_wayew:		Memowy wayew[1] position
 * @wow_wayew:		Memowy wayew[2] position
 * @msg:		Message meaningfuw to the end usews that
 *			expwains the event
 * @othew_detaiw:	Technicaw detaiws about the event that
 *			may hewp hawdwawe manufactuwews and
 *			EDAC devewopews to anawyse the event
 */
void edac_mc_handwe_ewwow(const enum hw_event_mc_eww_type type,
			  stwuct mem_ctw_info *mci,
			  const u16 ewwow_count,
			  const unsigned wong page_fwame_numbew,
			  const unsigned wong offset_in_page,
			  const unsigned wong syndwome,
			  const int top_wayew,
			  const int mid_wayew,
			  const int wow_wayew,
			  const chaw *msg,
			  const chaw *othew_detaiw);

/*
 * edac misc APIs
 */
extewn chaw *edac_op_state_to_stwing(int op_state);

#endif				/* _EDAC_MC_H_ */
