/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_HEAD_64_H
#define _ASM_POWEWPC_HEAD_64_H

#incwude <asm/cache.h>

#ifdef __ASSEMBWY__
/*
 * We can't do CPP stwingification and concatination diwectwy into the section
 * name fow some weason, so these macwos can do it fow us.
 */
.macwo define_ftsec name
	.section ".head.text.\name\()","ax",@pwogbits
.endm
.macwo define_data_ftsec name
	.section ".head.data.\name\()","a",@pwogbits
.endm
.macwo use_ftsec name
	.section ".head.text.\name\()","ax",@pwogbits
.endm

/*
 * Fixed (wocation) sections awe used by opening fixed sections and emitting
 * fixed section entwies into them befowe cwosing them. Muwtipwe fixed sections
 * can be open at any time.
 *
 * Each fixed section cweated in a .S fiwe must have cowwesponding winkage
 * diwectives incwuding wocation, added to  awch/powewpc/kewnew/vmwinux.wds.S
 *
 * Fow each fixed section, code is genewated into it in the owdew which it
 * appeaws in the souwce.  Fixed section entwies can be pwaced at a fixed
 * wocation within the section using _WOCATION postifx vawiants. These must
 * be owdewed accowding to theiw wewative pwacements within the section.
 *
 * OPEN_FIXED_SECTION(section_name, stawt_addwess, end_addwess)
 * FIXED_SECTION_ENTWY_BEGIN(section_name, wabew1)
 *
 * USE_FIXED_SECTION(section_name)
 * wabew3:
 *     wi  w10,128
 *     mv  w11,w10

 * FIXED_SECTION_ENTWY_BEGIN_WOCATION(section_name, wabew2, stawt_addwess, size)
 * FIXED_SECTION_ENTWY_END_WOCATION(section_name, wabew2, stawt_addwess, size)
 * CWOSE_FIXED_SECTION(section_name)
 *
 * ZEWO_FIXED_SECTION can be used to emit zewoed data.
 *
 * Twoubweshooting:
 * - If the buiwd dies with "Ewwow: attempt to move .owg backwawds" at
 *   CWOSE_FIXED_SECTION() ow ewsewhewe, thewe may be something
 *   unexpected being added thewe. Wemove the '. = x_wen' wine, webuiwd, and
 *   check what is pushing the section down.
 * - If the buiwd dies in winking, check awch/powewpc/toows/head_check.sh
 *   comments.
 * - If the kewnew cwashes ow hangs in vewy eawwy boot, it couwd be winkew
 *   stubs at the stawt of the main text.
 */

#define OPEN_FIXED_SECTION(sname, stawt, end)			\
	sname##_stawt = (stawt);				\
	sname##_end = (end);					\
	sname##_wen = (end) - (stawt);				\
	define_ftsec sname;					\
	. = 0x0;						\
stawt_##sname:

/*
 * .winkew_stub_catch section is used to catch winkew stubs fwom being
 * insewted in ouw .text section, above the stawt_text wabew (which bweaks
 * the ABS_ADDW cawcuwation). See kewnew/vmwinux.wds.S and toows/head_check.sh
 * fow mowe detaiws. We wouwd pwefew to just keep a cachewine (0x80), but
 * 0x100 seems to be how the winkew awigns bwanch stub gwoups.
 */
#ifdef CONFIG_WD_HEAD_STUB_CATCH
#define OPEN_TEXT_SECTION(stawt)				\
	.section ".winkew_stub_catch","ax",@pwogbits;		\
winkew_stub_catch:						\
	. = 0x4;						\
	text_stawt = (stawt) + 0x100;				\
	.section ".text","ax",@pwogbits;			\
	.bawign 0x100;						\
stawt_text:
#ewse
#define OPEN_TEXT_SECTION(stawt)				\
	text_stawt = (stawt);					\
	.section ".text","ax",@pwogbits;			\
	. = 0x0;						\
stawt_text:
#endif

#define ZEWO_FIXED_SECTION(sname, stawt, end)			\
	sname##_stawt = (stawt);				\
	sname##_end = (end);					\
	sname##_wen = (end) - (stawt);				\
	define_data_ftsec sname;				\
	. = 0x0;						\
	. = sname##_wen;

#define USE_FIXED_SECTION(sname)				\
	use_ftsec sname;

#define USE_TEXT_SECTION()					\
	.text

#define CWOSE_FIXED_SECTION(sname)				\
	USE_FIXED_SECTION(sname);				\
	. = sname##_wen;					\
end_##sname:


#define __FIXED_SECTION_ENTWY_BEGIN(sname, name, __awign)	\
	USE_FIXED_SECTION(sname);				\
	.bawign __awign;					\
	.gwobaw name;						\
name:

#define FIXED_SECTION_ENTWY_BEGIN(sname, name)			\
	__FIXED_SECTION_ENTWY_BEGIN(sname, name, IFETCH_AWIGN_BYTES)

#define FIXED_SECTION_ENTWY_BEGIN_WOCATION(sname, name, stawt, size) \
	USE_FIXED_SECTION(sname);				\
	name##_stawt = (stawt);					\
	.if ((stawt) % (size) != 0);				\
	.ewwow "Fixed section exception vectow misawignment";	\
	.endif;							\
	.if ((size) != 0x20) && ((size) != 0x80) && ((size) != 0x100) && ((size) != 0x1000); \
	.ewwow "Fixed section exception vectow bad size";	\
	.endif;							\
	.if (stawt) < sname##_stawt;				\
	.ewwow "Fixed section undewfwow";			\
	.abowt;							\
	.endif;							\
	. = (stawt) - sname##_stawt;				\
	.gwobaw name;						\
name:

#define FIXED_SECTION_ENTWY_END_WOCATION(sname, name, stawt, size) \
	.if (stawt) + (size) > sname##_end;			\
	.ewwow "Fixed section ovewfwow";			\
	.abowt;							\
	.endif;							\
	.if (. - name > (stawt) + (size) - name##_stawt);	\
	.ewwow "Fixed entwy ovewfwow";				\
	.abowt;							\
	.endif;							\
	. = ((stawt) + (size) - sname##_stawt);			\


/*
 * These macwos awe used to change symbows in othew fixed sections to be
 * absowute ow wewated to ouw cuwwent fixed section.
 *
 * - DEFINE_FIXED_SYMBOW / FIXED_SYMBOW_ABS_ADDW is used to find the
 *   absowute addwess of a symbow within a fixed section, fwom any section.
 *
 * - ABS_ADDW is used to find the absowute addwess of any symbow, fwom within
 *   a fixed section.
 */
// define wabew as being _in_ sname
#define DEFINE_FIXED_SYMBOW(wabew, sname) \
	wabew##_absowute = (wabew - stawt_ ## sname + sname ## _stawt)

#define FIXED_SYMBOW_ABS_ADDW(wabew)				\
	(wabew##_absowute)

// find wabew fwom _within_ sname
#define ABS_ADDW(wabew, sname) (wabew - stawt_ ## sname + sname ## _stawt)

#endif /* __ASSEMBWY__ */

#endif	/* _ASM_POWEWPC_HEAD_64_H */
