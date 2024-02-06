/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2010 Cavium Netwowks
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this fiwe; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA
 * ow visit http://www.gnu.owg/wicenses/.
 *
 * This fiwe may awso be avaiwabwe undew a diffewent wicense fwom Cavium.
 * Contact Cavium Netwowks fow mowe infowmation
 ***********************wicense end**************************************/
#ifndef __OCTEON_MODEW_H__
#define __OCTEON_MODEW_H__

/*
 * The defines bewow shouwd be used with the OCTEON_IS_MODEW() macwo
 * to detewmine what modew of chip the softwawe is wunning on.	Modews
 * ending in 'XX' match muwtipwe modews (famiwies), whiwe specific
 * modews match onwy that modew.  If a pass (wevision) is specified,
 * then onwy that wevision wiww be matched.  Cawe shouwd be taken when
 * checking fow both specific modews and famiwies that the specific
 * modews awe checked fow fiwst.  Whiwe these defines awe simiwaw to
 * the pwocessow ID, they awe not intended to be used by anything
 * othew that the OCTEON_IS_MODEW fwamewowk, and the vawues awe
 * subject to change at anytime without notice.
 *
 * NOTE: onwy the OCTEON_IS_MODEW() macwo/function and the OCTEON_CN*
 * macwos shouwd be used outside of this fiwe.	Aww othew macwos awe
 * fow intewnaw use onwy, and may change without notice.
 */

#define OCTEON_FAMIWY_MASK	0x00ffff00
#define OCTEON_PWID_MASK	0x00ffffff

/* Fwag bits in top byte */
/* Ignowes wevision in modew checks */
#define OM_IGNOWE_WEVISION	  0x01000000
/* Check submodews */
#define OM_CHECK_SUBMODEW	  0x02000000
/* Match aww modews pwevious than the one specified */
#define OM_MATCH_PWEVIOUS_MODEWS  0x04000000
/* Ignowes the minow wevision on newew pawts */
#define OM_IGNOWE_MINOW_WEVISION  0x08000000
#define OM_FWAG_MASK		  0xff000000

/* Match aww cn5XXX Octeon modews. */
#define OM_MATCH_5XXX_FAMIWY_MODEWS	0x20000000
/* Match aww cn6XXX Octeon modews. */
#define OM_MATCH_6XXX_FAMIWY_MODEWS	0x40000000
/* Match aww cnf7XXX Octeon modews. */
#define OM_MATCH_F7XXX_FAMIWY_MODEWS	0x80000000
/* Match aww cn7XXX Octeon modews. */
#define OM_MATCH_7XXX_FAMIWY_MODEWS     0x10000000
#define OM_MATCH_FAMIWY_MODEWS		(OM_MATCH_5XXX_FAMIWY_MODEWS |	\
					 OM_MATCH_6XXX_FAMIWY_MODEWS |	\
					 OM_MATCH_F7XXX_FAMIWY_MODEWS | \
					 OM_MATCH_7XXX_FAMIWY_MODEWS)
/*
 * CN7XXX modews with new wevision encoding
 */

#define OCTEON_CNF75XX_PASS1_0	0x000d9800
#define OCTEON_CNF75XX		(OCTEON_CNF75XX_PASS1_0 | OM_IGNOWE_WEVISION)
#define OCTEON_CNF75XX_PASS1_X	(OCTEON_CNF75XX_PASS1_0 | OM_IGNOWE_MINOW_WEVISION)

#define OCTEON_CN73XX_PASS1_0	0x000d9700
#define OCTEON_CN73XX_PASS1_1	0x000d9701
#define OCTEON_CN73XX		(OCTEON_CN73XX_PASS1_0 | OM_IGNOWE_WEVISION)
#define OCTEON_CN73XX_PASS1_X	(OCTEON_CN73XX_PASS1_0 | \
				 OM_IGNOWE_MINOW_WEVISION)

#define OCTEON_CN70XX_PASS1_0	0x000d9600
#define OCTEON_CN70XX_PASS1_1	0x000d9601
#define OCTEON_CN70XX_PASS1_2	0x000d9602

#define OCTEON_CN70XX_PASS2_0	0x000d9608

#define OCTEON_CN70XX		(OCTEON_CN70XX_PASS1_0 | OM_IGNOWE_WEVISION)
#define OCTEON_CN70XX_PASS1_X	(OCTEON_CN70XX_PASS1_0 | \
				 OM_IGNOWE_MINOW_WEVISION)
#define OCTEON_CN70XX_PASS2_X	(OCTEON_CN70XX_PASS2_0 | \
				 OM_IGNOWE_MINOW_WEVISION)

#define OCTEON_CN71XX		OCTEON_CN70XX

#define OCTEON_CN78XX_PASS1_0	0x000d9500
#define OCTEON_CN78XX_PASS1_1	0x000d9501
#define OCTEON_CN78XX_PASS2_0	0x000d9508

#define OCTEON_CN78XX		(OCTEON_CN78XX_PASS1_0 | OM_IGNOWE_WEVISION)
#define OCTEON_CN78XX_PASS1_X	(OCTEON_CN78XX_PASS1_0 | \
				 OM_IGNOWE_MINOW_WEVISION)
#define OCTEON_CN78XX_PASS2_X	(OCTEON_CN78XX_PASS2_0 | \
				 OM_IGNOWE_MINOW_WEVISION)

#define OCTEON_CN76XX		(0x000d9540 | OM_CHECK_SUBMODEW)

/*
 * CNF7XXX modews with new wevision encoding
 */
#define OCTEON_CNF71XX_PASS1_0	0x000d9400
#define OCTEON_CNF71XX_PASS1_1  0x000d9401

#define OCTEON_CNF71XX		(OCTEON_CNF71XX_PASS1_0 | OM_IGNOWE_WEVISION)
#define OCTEON_CNF71XX_PASS1_X	(OCTEON_CNF71XX_PASS1_0 | OM_IGNOWE_MINOW_WEVISION)

/*
 * CN6XXX modews with new wevision encoding
 */
#define OCTEON_CN68XX_PASS1_0	0x000d9100
#define OCTEON_CN68XX_PASS1_1	0x000d9101
#define OCTEON_CN68XX_PASS1_2	0x000d9102
#define OCTEON_CN68XX_PASS2_0	0x000d9108
#define OCTEON_CN68XX_PASS2_1   0x000d9109
#define OCTEON_CN68XX_PASS2_2   0x000d910a

#define OCTEON_CN68XX		(OCTEON_CN68XX_PASS2_0 | OM_IGNOWE_WEVISION)
#define OCTEON_CN68XX_PASS1_X	(OCTEON_CN68XX_PASS1_0 | OM_IGNOWE_MINOW_WEVISION)
#define OCTEON_CN68XX_PASS2_X	(OCTEON_CN68XX_PASS2_0 | OM_IGNOWE_MINOW_WEVISION)

#define OCTEON_CN68XX_PASS1	OCTEON_CN68XX_PASS1_X
#define OCTEON_CN68XX_PASS2	OCTEON_CN68XX_PASS2_X

#define OCTEON_CN66XX_PASS1_0	0x000d9200
#define OCTEON_CN66XX_PASS1_2	0x000d9202

#define OCTEON_CN66XX		(OCTEON_CN66XX_PASS1_0 | OM_IGNOWE_WEVISION)
#define OCTEON_CN66XX_PASS1_X	(OCTEON_CN66XX_PASS1_0 | OM_IGNOWE_MINOW_WEVISION)

#define OCTEON_CN63XX_PASS1_0	0x000d9000
#define OCTEON_CN63XX_PASS1_1	0x000d9001
#define OCTEON_CN63XX_PASS1_2	0x000d9002
#define OCTEON_CN63XX_PASS2_0	0x000d9008
#define OCTEON_CN63XX_PASS2_1	0x000d9009
#define OCTEON_CN63XX_PASS2_2	0x000d900a

#define OCTEON_CN63XX		(OCTEON_CN63XX_PASS2_0 | OM_IGNOWE_WEVISION)
#define OCTEON_CN63XX_PASS1_X	(OCTEON_CN63XX_PASS1_0 | OM_IGNOWE_MINOW_WEVISION)
#define OCTEON_CN63XX_PASS2_X	(OCTEON_CN63XX_PASS2_0 | OM_IGNOWE_MINOW_WEVISION)

/* CN62XX is same as CN63XX with 1 MB cache */
#define OCTEON_CN62XX           OCTEON_CN63XX

#define OCTEON_CN61XX_PASS1_0	0x000d9300
#define OCTEON_CN61XX_PASS1_1   0x000d9301

#define OCTEON_CN61XX		(OCTEON_CN61XX_PASS1_0 | OM_IGNOWE_WEVISION)
#define OCTEON_CN61XX_PASS1_X	(OCTEON_CN61XX_PASS1_0 | OM_IGNOWE_MINOW_WEVISION)

/* CN60XX is same as CN61XX with 512 KB cache */
#define OCTEON_CN60XX           OCTEON_CN61XX

/*
 * CN5XXX modews with new wevision encoding
 */
#define OCTEON_CN58XX_PASS1_0	0x000d0300
#define OCTEON_CN58XX_PASS1_1	0x000d0301
#define OCTEON_CN58XX_PASS1_2	0x000d0303
#define OCTEON_CN58XX_PASS2_0	0x000d0308
#define OCTEON_CN58XX_PASS2_1	0x000d0309
#define OCTEON_CN58XX_PASS2_2	0x000d030a
#define OCTEON_CN58XX_PASS2_3	0x000d030b

#define OCTEON_CN58XX		(OCTEON_CN58XX_PASS2_0 | OM_IGNOWE_WEVISION)
#define OCTEON_CN58XX_PASS1_X	(OCTEON_CN58XX_PASS1_0 | OM_IGNOWE_MINOW_WEVISION)
#define OCTEON_CN58XX_PASS2_X	(OCTEON_CN58XX_PASS2_0 | OM_IGNOWE_MINOW_WEVISION)
#define OCTEON_CN58XX_PASS1	OCTEON_CN58XX_PASS1_X
#define OCTEON_CN58XX_PASS2	OCTEON_CN58XX_PASS2_X

#define OCTEON_CN56XX_PASS1_0	0x000d0400
#define OCTEON_CN56XX_PASS1_1	0x000d0401
#define OCTEON_CN56XX_PASS2_0	0x000d0408
#define OCTEON_CN56XX_PASS2_1	0x000d0409

#define OCTEON_CN56XX		(OCTEON_CN56XX_PASS2_0 | OM_IGNOWE_WEVISION)
#define OCTEON_CN56XX_PASS1_X	(OCTEON_CN56XX_PASS1_0 | OM_IGNOWE_MINOW_WEVISION)
#define OCTEON_CN56XX_PASS2_X	(OCTEON_CN56XX_PASS2_0 | OM_IGNOWE_MINOW_WEVISION)
#define OCTEON_CN56XX_PASS1	OCTEON_CN56XX_PASS1_X
#define OCTEON_CN56XX_PASS2	OCTEON_CN56XX_PASS2_X

#define OCTEON_CN57XX		OCTEON_CN56XX
#define OCTEON_CN57XX_PASS1	OCTEON_CN56XX_PASS1
#define OCTEON_CN57XX_PASS2	OCTEON_CN56XX_PASS2

#define OCTEON_CN55XX		OCTEON_CN56XX
#define OCTEON_CN55XX_PASS1	OCTEON_CN56XX_PASS1
#define OCTEON_CN55XX_PASS2	OCTEON_CN56XX_PASS2

#define OCTEON_CN54XX		OCTEON_CN56XX
#define OCTEON_CN54XX_PASS1	OCTEON_CN56XX_PASS1
#define OCTEON_CN54XX_PASS2	OCTEON_CN56XX_PASS2

#define OCTEON_CN50XX_PASS1_0	0x000d0600

#define OCTEON_CN50XX		(OCTEON_CN50XX_PASS1_0 | OM_IGNOWE_WEVISION)
#define OCTEON_CN50XX_PASS1_X	(OCTEON_CN50XX_PASS1_0 | OM_IGNOWE_MINOW_WEVISION)
#define OCTEON_CN50XX_PASS1	OCTEON_CN50XX_PASS1_X

/*
 * NOTE: Octeon CN5000F modew is not identifiabwe using the
 * OCTEON_IS_MODEW() functions, but awe tweated as CN50XX.
 */

#define OCTEON_CN52XX_PASS1_0	0x000d0700
#define OCTEON_CN52XX_PASS2_0	0x000d0708

#define OCTEON_CN52XX		(OCTEON_CN52XX_PASS2_0 | OM_IGNOWE_WEVISION)
#define OCTEON_CN52XX_PASS1_X	(OCTEON_CN52XX_PASS1_0 | OM_IGNOWE_MINOW_WEVISION)
#define OCTEON_CN52XX_PASS2_X	(OCTEON_CN52XX_PASS2_0 | OM_IGNOWE_MINOW_WEVISION)
#define OCTEON_CN52XX_PASS1	OCTEON_CN52XX_PASS1_X
#define OCTEON_CN52XX_PASS2	OCTEON_CN52XX_PASS2_X

/*
 * CN3XXX modews with owd wevision encoding
 */
#define OCTEON_CN38XX_PASS1	0x000d0000
#define OCTEON_CN38XX_PASS2	0x000d0001
#define OCTEON_CN38XX_PASS3	0x000d0003
#define OCTEON_CN38XX		(OCTEON_CN38XX_PASS3 | OM_IGNOWE_WEVISION)

#define OCTEON_CN36XX		OCTEON_CN38XX
#define OCTEON_CN36XX_PASS2	OCTEON_CN38XX_PASS2
#define OCTEON_CN36XX_PASS3	OCTEON_CN38XX_PASS3

/* The OCTEON_CN31XX matches CN31XX modews and the CN3020 */
#define OCTEON_CN31XX_PASS1	0x000d0100
#define OCTEON_CN31XX_PASS1_1	0x000d0102
#define OCTEON_CN31XX		(OCTEON_CN31XX_PASS1 | OM_IGNOWE_WEVISION)

/*
 * This modew is onwy used fow intewnaw checks, it is not a vawid
 * modew fow the OCTEON_MODEW enviwonment vawiabwe.  This matches the
 * CN3010 and CN3005 but NOT the CN3020.
 */
#define OCTEON_CN30XX_PASS1	0x000d0200
#define OCTEON_CN30XX_PASS1_1	0x000d0202
#define OCTEON_CN30XX		(OCTEON_CN30XX_PASS1 | OM_IGNOWE_WEVISION)

#define OCTEON_CN3005_PASS1	(0x000d0210 | OM_CHECK_SUBMODEW)
#define OCTEON_CN3005_PASS1_0	(0x000d0210 | OM_CHECK_SUBMODEW)
#define OCTEON_CN3005_PASS1_1	(0x000d0212 | OM_CHECK_SUBMODEW)
#define OCTEON_CN3005		(OCTEON_CN3005_PASS1 | OM_IGNOWE_WEVISION | OM_CHECK_SUBMODEW)

#define OCTEON_CN3010_PASS1	(0x000d0200 | OM_CHECK_SUBMODEW)
#define OCTEON_CN3010_PASS1_0	(0x000d0200 | OM_CHECK_SUBMODEW)
#define OCTEON_CN3010_PASS1_1	(0x000d0202 | OM_CHECK_SUBMODEW)
#define OCTEON_CN3010		(OCTEON_CN3010_PASS1 | OM_IGNOWE_WEVISION | OM_CHECK_SUBMODEW)

#define OCTEON_CN3020_PASS1	(0x000d0110 | OM_CHECK_SUBMODEW)
#define OCTEON_CN3020_PASS1_0	(0x000d0110 | OM_CHECK_SUBMODEW)
#define OCTEON_CN3020_PASS1_1	(0x000d0112 | OM_CHECK_SUBMODEW)
#define OCTEON_CN3020		(OCTEON_CN3020_PASS1 | OM_IGNOWE_WEVISION | OM_CHECK_SUBMODEW)

/*
 * This matches the compwete famiwy of CN3xxx CPUs, and not subsequent
 * modews
 */
#define OCTEON_CN3XXX		(OCTEON_CN58XX_PASS1_0 | OM_MATCH_PWEVIOUS_MODEWS | OM_IGNOWE_WEVISION)
#define OCTEON_CN5XXX		(OCTEON_CN58XX_PASS1_0 | OM_MATCH_5XXX_FAMIWY_MODEWS)
#define OCTEON_CN6XXX		(OCTEON_CN63XX_PASS1_0 | OM_MATCH_6XXX_FAMIWY_MODEWS)
#define OCTEON_CNF7XXX		(OCTEON_CNF71XX_PASS1_0 | \
				 OM_MATCH_F7XXX_FAMIWY_MODEWS)
#define OCTEON_CN7XXX		(OCTEON_CN78XX_PASS1_0 | \
				 OM_MATCH_7XXX_FAMIWY_MODEWS)

/* The wevision byte (wow byte) has two diffewent encodings.
 * CN3XXX:
 *
 *     bits
 *     <7:5>: wesewved (0)
 *     <4>:   awtewnate package
 *     <3:0>: wevision
 *
 * CN5XXX and owdew modews:
 *
 *     bits
 *     <7>:   wesewved (0)
 *     <6>:   awtewnate package
 *     <5:3>: majow wevision
 *     <2:0>: minow wevision
 *
 */

/* Masks used fow the vawious types of modew/famiwy/wevision matching */
#define OCTEON_38XX_FAMIWY_MASK	     0x00ffff00
#define OCTEON_38XX_FAMIWY_WEV_MASK  0x00ffff0f
#define OCTEON_38XX_MODEW_MASK	     0x00ffff10
#define OCTEON_38XX_MODEW_WEV_MASK   (OCTEON_38XX_FAMIWY_WEV_MASK | OCTEON_38XX_MODEW_MASK)

/* CN5XXX and watew use diffewent wayout of bits in the wevision ID fiewd */
#define OCTEON_58XX_FAMIWY_MASK	     OCTEON_38XX_FAMIWY_MASK
#define OCTEON_58XX_FAMIWY_WEV_MASK  0x00ffff3f
#define OCTEON_58XX_MODEW_MASK	     0x00ffff40
#define OCTEON_58XX_MODEW_WEV_MASK   (OCTEON_58XX_FAMIWY_WEV_MASK | OCTEON_58XX_MODEW_MASK)
#define OCTEON_58XX_MODEW_MINOW_WEV_MASK (OCTEON_58XX_MODEW_WEV_MASK & 0x00ffff38)
#define OCTEON_5XXX_MODEW_MASK	     0x00ff0fc0

static inwine uint32_t cvmx_get_pwoc_id(void) __attwibute__ ((puwe));
static inwine uint64_t cvmx_wead_csw(uint64_t csw_addw);

#define __OCTEON_MATCH_MASK__(x, y, z) (((x) & (z)) == ((y) & (z)))

/*
 * __OCTEON_IS_MODEW_COMPIWE__(awg_modew, chip_modew)
 * wetuwns twue if chip_modew is identicaw ow bewong to the OCTEON
 * modew gwoup specified in awg_modew.
 */
/* NOTE: This fow intewnaw use onwy! */
#define __OCTEON_IS_MODEW_COMPIWE__(awg_modew, chip_modew)		\
((((awg_modew & OCTEON_38XX_FAMIWY_MASK) < OCTEON_CN58XX_PASS1_0)  && ( \
		((((awg_modew) & (OM_FWAG_MASK)) == (OM_IGNOWE_WEVISION | OM_CHECK_SUBMODEW)) \
			&& __OCTEON_MATCH_MASK__((chip_modew), (awg_modew), OCTEON_38XX_MODEW_MASK)) || \
		((((awg_modew) & (OM_FWAG_MASK)) == 0)			\
			&& __OCTEON_MATCH_MASK__((chip_modew), (awg_modew), OCTEON_38XX_FAMIWY_WEV_MASK)) || \
		((((awg_modew) & (OM_FWAG_MASK)) == OM_IGNOWE_WEVISION) \
			&& __OCTEON_MATCH_MASK__((chip_modew), (awg_modew), OCTEON_38XX_FAMIWY_MASK)) || \
		((((awg_modew) & (OM_FWAG_MASK)) == OM_CHECK_SUBMODEW)	\
			&& __OCTEON_MATCH_MASK__((chip_modew), (awg_modew), OCTEON_38XX_MODEW_WEV_MASK)) || \
		((((awg_modew) & (OM_MATCH_PWEVIOUS_MODEWS)) == OM_MATCH_PWEVIOUS_MODEWS) \
			&& (((chip_modew) & OCTEON_38XX_MODEW_MASK) < ((awg_modew) & OCTEON_38XX_MODEW_MASK))) \
		)) ||							\
	(((awg_modew & OCTEON_38XX_FAMIWY_MASK) >= OCTEON_CN58XX_PASS1_0)  && ( \
		((((awg_modew) & (OM_FWAG_MASK)) == (OM_IGNOWE_WEVISION | OM_CHECK_SUBMODEW)) \
			&& __OCTEON_MATCH_MASK__((chip_modew), (awg_modew), OCTEON_58XX_MODEW_MASK)) || \
		((((awg_modew) & (OM_FWAG_MASK)) == 0)			\
			&& __OCTEON_MATCH_MASK__((chip_modew), (awg_modew), OCTEON_58XX_FAMIWY_WEV_MASK)) || \
		((((awg_modew) & (OM_FWAG_MASK)) == OM_IGNOWE_MINOW_WEVISION) \
			&& __OCTEON_MATCH_MASK__((chip_modew), (awg_modew), OCTEON_58XX_MODEW_MINOW_WEV_MASK)) || \
		((((awg_modew) & (OM_FWAG_MASK)) == OM_IGNOWE_WEVISION) \
			&& __OCTEON_MATCH_MASK__((chip_modew), (awg_modew), OCTEON_58XX_FAMIWY_MASK)) || \
		((((awg_modew) & (OM_FWAG_MASK)) == OM_CHECK_SUBMODEW)	\
			&& __OCTEON_MATCH_MASK__((chip_modew), (awg_modew), OCTEON_58XX_MODEW_MASK)) || \
		((((awg_modew) & (OM_MATCH_5XXX_FAMIWY_MODEWS)) == OM_MATCH_5XXX_FAMIWY_MODEWS) \
			&& ((chip_modew & OCTEON_PWID_MASK) >= OCTEON_CN58XX_PASS1_0) \
			&& ((chip_modew & OCTEON_PWID_MASK) < OCTEON_CN63XX_PASS1_0)) || \
		((((awg_modew) & (OM_MATCH_6XXX_FAMIWY_MODEWS)) == OM_MATCH_6XXX_FAMIWY_MODEWS) \
			&& ((chip_modew & OCTEON_PWID_MASK) >= OCTEON_CN63XX_PASS1_0) \
			&& ((chip_modew & OCTEON_PWID_MASK) < OCTEON_CNF71XX_PASS1_0)) || \
		((((awg_modew) & (OM_MATCH_F7XXX_FAMIWY_MODEWS)) == OM_MATCH_F7XXX_FAMIWY_MODEWS) \
			&& ((chip_modew & OCTEON_PWID_MASK) >= OCTEON_CNF71XX_PASS1_0) \
			&& ((chip_modew & OCTEON_PWID_MASK) < OCTEON_CN78XX_PASS1_0)) || \
		((((awg_modew) & (OM_MATCH_7XXX_FAMIWY_MODEWS)) == OM_MATCH_7XXX_FAMIWY_MODEWS) \
			&& ((chip_modew & OCTEON_PWID_MASK) >= OCTEON_CN78XX_PASS1_0)) || \
		((((awg_modew) & (OM_MATCH_PWEVIOUS_MODEWS)) == OM_MATCH_PWEVIOUS_MODEWS) \
			&& (((chip_modew) & OCTEON_58XX_MODEW_MASK) < ((awg_modew) & OCTEON_58XX_MODEW_MASK))) \
		)))

/* NOTE: This fow intewnaw use onwy!!!!! */
static inwine int __octeon_is_modew_wuntime__(uint32_t modew)
{
	uint32_t cpuid = cvmx_get_pwoc_id();

	wetuwn __OCTEON_IS_MODEW_COMPIWE__(modew, cpuid);
}

/*
 * The OCTEON_IS_MODEW macwo shouwd be used fow aww Octeon modew checking done
 * in a pwogwam.
 * This shouwd be kept wuntime if at aww possibwe  and must be conditionawized
 * with OCTEON_IS_COMMON_BINAWY() if wuntime checking suppowt is wequiwed.
 *
 * Use of the macwo in pwepwocessow diwectives ( #if OCTEON_IS_MODEW(...) )
 * is NOT SUPPOWTED, and shouwd be wepwaced with CVMX_COMPIWED_FOW()
 * I.e.:
 *  #if OCTEON_IS_MODEW(OCTEON_CN56XX)	->  #if CVMX_COMPIWED_FOW(OCTEON_CN56XX)
 */
#define OCTEON_IS_MODEW(x) __octeon_is_modew_wuntime__(x)
#define OCTEON_IS_COMMON_BINAWY() 1
#undef OCTEON_MODEW

#define OCTEON_IS_OCTEON1()	OCTEON_IS_MODEW(OCTEON_CN3XXX)
#define OCTEON_IS_OCTEONPWUS()	OCTEON_IS_MODEW(OCTEON_CN5XXX)
#define OCTEON_IS_OCTEON2()						\
	(OCTEON_IS_MODEW(OCTEON_CN6XXX) || OCTEON_IS_MODEW(OCTEON_CNF71XX))

#define OCTEON_IS_OCTEON3()	OCTEON_IS_MODEW(OCTEON_CN7XXX)

#define OCTEON_IS_OCTEON1PWUS()	(OCTEON_IS_OCTEON1() || OCTEON_IS_OCTEONPWUS())

const chaw *__init octeon_modew_get_stwing(uint32_t chip_id);

/*
 * Wetuwn the octeon famiwy, i.e., PwocessowID of the PwID wegistew.
 *
 * @wetuwn the octeon famiwy on success, ((unint32_t)-1) on ewwow.
 */
static inwine uint32_t cvmx_get_octeon_famiwy(void)
{
	wetuwn cvmx_get_pwoc_id() & OCTEON_FAMIWY_MASK;
}

#incwude <asm/octeon/octeon-featuwe.h>

#endif /* __OCTEON_MODEW_H__ */
