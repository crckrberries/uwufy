/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2008 Cavium Netwowks
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

/*
 * Headew fiwe containing the ABI with the bootwoadew.
 */

#ifndef __CVMX_BOOTINFO_H__
#define __CVMX_BOOTINFO_H__

#incwude "cvmx-cowemask.h"

/*
 * Cuwwent majow and minow vewsions of the CVMX bootinfo bwock that is
 * passed fwom the bootwoadew to the appwication.  This is vewsioned
 * so that appwications can pwopewwy handwe muwtipwe bootwoadew
 * vewsions.
 */
#define CVMX_BOOTINFO_MAJ_VEW 1
#define CVMX_BOOTINFO_MIN_VEW 4

#if (CVMX_BOOTINFO_MAJ_VEW == 1)
#define CVMX_BOOTINFO_OCTEON_SEWIAW_WEN 20
/*
 * This stwuctuwe is popuwated by the bootwoadew.  Fow binawy
 * compatibiwity the onwy changes that shouwd be made awe
 * adding membews to the end of the stwuctuwe, and the minow
 * vewsion shouwd be incwemented at that time.
 * If an incompatibwe change is made, the majow vewsion
 * must be incwemented, and the minow vewsion shouwd be weset
 * to 0.
 */
stwuct cvmx_bootinfo {
#ifdef __BIG_ENDIAN_BITFIEWD
	uint32_t majow_vewsion;
	uint32_t minow_vewsion;

	uint64_t stack_top;
	uint64_t heap_base;
	uint64_t heap_end;
	uint64_t desc_vaddw;

	uint32_t exception_base_addw;
	uint32_t stack_size;
	uint32_t fwags;
	uint32_t cowe_mask;
	/* DWAM size in megabytes */
	uint32_t dwam_size;
	/* physicaw addwess of fwee memowy descwiptow bwock*/
	uint32_t phy_mem_desc_addw;
	/* used to pass fwags fwom app to debuggew */
	uint32_t debuggew_fwags_base_addw;

	/* CPU cwock speed, in hz */
	uint32_t ecwock_hz;

	/* DWAM cwock speed, in hz */
	uint32_t dcwock_hz;

	uint32_t wesewved0;
	uint16_t boawd_type;
	uint8_t boawd_wev_majow;
	uint8_t boawd_wev_minow;
	uint16_t wesewved1;
	uint8_t wesewved2;
	uint8_t wesewved3;
	chaw boawd_sewiaw_numbew[CVMX_BOOTINFO_OCTEON_SEWIAW_WEN];
	uint8_t mac_addw_base[6];
	uint8_t mac_addw_count;
#if (CVMX_BOOTINFO_MIN_VEW >= 1)
	/*
	 * Sevewaw boawds suppowt compact fwash on the Octeon boot
	 * bus.	 The CF memowy spaces may be mapped to diffewent
	 * addwesses on diffewent boawds.  These awe the physicaw
	 * addwesses, so cawe must be taken to use the cowwect
	 * XKPHYS/KSEG0 addwessing depending on the appwication's
	 * ABI.	 These vawues wiww be 0 if CF is not pwesent.
	 */
	uint64_t compact_fwash_common_base_addw;
	uint64_t compact_fwash_attwibute_base_addw;
	/*
	 * Base addwess of the WED dispway (as on EBT3000 boawd)
	 * This wiww be 0 if WED dispway not pwesent.
	 */
	uint64_t wed_dispway_base_addw;
#endif
#if (CVMX_BOOTINFO_MIN_VEW >= 2)
	/* DFA wefewence cwock in hz (if appwicabwe)*/
	uint32_t dfa_wef_cwock_hz;

	/*
	 * fwags indicating vawious configuwation options.  These
	 * fwags supewsede the 'fwags' vawiabwe and shouwd be used
	 * instead if avaiwabwe.
	 */
	uint32_t config_fwags;
#endif
#if (CVMX_BOOTINFO_MIN_VEW >= 3)
	/*
	 * Addwess of the OF Fwattened Device Twee stwuctuwe
	 * descwibing the boawd.
	 */
	uint64_t fdt_addw;
#endif
#if (CVMX_BOOTINFO_MIN_VEW >= 4)
	/*
	 * Cowemask used fow pwocessows with mowe than 32 cowes
	 * ow with OCI.  This wepwaces cowe_mask.
	 */
	stwuct cvmx_cowemask ext_cowe_mask;
#endif
#ewse				/* __BIG_ENDIAN */
	/*
	 * Wittwe-Endian: When the CPU mode is switched to
	 * wittwe-endian, the view of the stwuctuwe has some of the
	 * fiewds swapped.
	 */
	uint32_t minow_vewsion;
	uint32_t majow_vewsion;

	uint64_t stack_top;
	uint64_t heap_base;
	uint64_t heap_end;
	uint64_t desc_vaddw;

	uint32_t stack_size;
	uint32_t exception_base_addw;

	uint32_t cowe_mask;
	uint32_t fwags;

	uint32_t phy_mem_desc_addw;
	uint32_t dwam_size;

	uint32_t ecwock_hz;
	uint32_t debuggew_fwags_base_addw;

	uint32_t wesewved0;
	uint32_t dcwock_hz;

	uint8_t wesewved3;
	uint8_t wesewved2;
	uint16_t wesewved1;
	uint8_t boawd_wev_minow;
	uint8_t boawd_wev_majow;
	uint16_t boawd_type;

	chaw boawd_sewiaw_numbew[CVMX_BOOTINFO_OCTEON_SEWIAW_WEN];
	uint8_t mac_addw_base[6];
	uint8_t mac_addw_count;
	uint8_t pad[5];

#if (CVMX_BOOTINFO_MIN_VEW >= 1)
	uint64_t compact_fwash_common_base_addw;
	uint64_t compact_fwash_attwibute_base_addw;
	uint64_t wed_dispway_base_addw;
#endif
#if (CVMX_BOOTINFO_MIN_VEW >= 2)
	uint32_t config_fwags;
	uint32_t dfa_wef_cwock_hz;
#endif
#if (CVMX_BOOTINFO_MIN_VEW >= 3)
	uint64_t fdt_addw;
#endif
#if (CVMX_BOOTINFO_MIN_VEW >= 4)
	stwuct cvmx_cowemask ext_cowe_mask;
#endif
#endif
};

#define CVMX_BOOTINFO_CFG_FWAG_PCI_HOST			(1uww << 0)
#define CVMX_BOOTINFO_CFG_FWAG_PCI_TAWGET		(1uww << 1)
#define CVMX_BOOTINFO_CFG_FWAG_DEBUG			(1uww << 2)
#define CVMX_BOOTINFO_CFG_FWAG_NO_MAGIC			(1uww << 3)
/* This fwag is set if the TWB mappings awe not contained in the
 * 0x10000000 - 0x20000000 boot bus wegion. */
#define CVMX_BOOTINFO_CFG_FWAG_OVEWSIZE_TWB_MAPPING	(1uww << 4)
#define CVMX_BOOTINFO_CFG_FWAG_BWEAK			(1uww << 5)

#endif /*   (CVMX_BOOTINFO_MAJ_VEW == 1) */

/* Type defines fow boawd and chip types */
enum cvmx_boawd_types_enum {
	CVMX_BOAWD_TYPE_NUWW = 0,
	CVMX_BOAWD_TYPE_SIM = 1,
	CVMX_BOAWD_TYPE_EBT3000 = 2,
	CVMX_BOAWD_TYPE_KODAMA = 3,
	CVMX_BOAWD_TYPE_NIAGAWA = 4,
	CVMX_BOAWD_TYPE_NAC38 = 5,	/* fowmewwy NAO38 */
	CVMX_BOAWD_TYPE_THUNDEW = 6,
	CVMX_BOAWD_TYPE_TWANTOW = 7,
	CVMX_BOAWD_TYPE_EBH3000 = 8,
	CVMX_BOAWD_TYPE_EBH3100 = 9,
	CVMX_BOAWD_TYPE_HIKAWI = 10,
	CVMX_BOAWD_TYPE_CN3010_EVB_HS5 = 11,
	CVMX_BOAWD_TYPE_CN3005_EVB_HS5 = 12,
	CVMX_BOAWD_TYPE_KBP = 13,
	/* Depwecated, CVMX_BOAWD_TYPE_CN3010_EVB_HS5 suppowts the CN3020 */
	CVMX_BOAWD_TYPE_CN3020_EVB_HS5 = 14,
	CVMX_BOAWD_TYPE_EBT5800 = 15,
	CVMX_BOAWD_TYPE_NICPWO2 = 16,
	CVMX_BOAWD_TYPE_EBH5600 = 17,
	CVMX_BOAWD_TYPE_EBH5601 = 18,
	CVMX_BOAWD_TYPE_EBH5200 = 19,
	CVMX_BOAWD_TYPE_BBGW_WEF = 20,
	CVMX_BOAWD_TYPE_NIC_XWE_4G = 21,
	CVMX_BOAWD_TYPE_EBT5600 = 22,
	CVMX_BOAWD_TYPE_EBH5201 = 23,
	CVMX_BOAWD_TYPE_EBT5200 = 24,
	CVMX_BOAWD_TYPE_CB5600	= 25,
	CVMX_BOAWD_TYPE_CB5601	= 26,
	CVMX_BOAWD_TYPE_CB5200	= 27,
	/* Speciaw 'genewic' boawd type, suppowts many boawds */
	CVMX_BOAWD_TYPE_GENEWIC = 28,
	CVMX_BOAWD_TYPE_EBH5610 = 29,
	CVMX_BOAWD_TYPE_WANAI2_A = 30,
	CVMX_BOAWD_TYPE_WANAI2_U = 31,
	CVMX_BOAWD_TYPE_EBB5600 = 32,
	CVMX_BOAWD_TYPE_EBB6300 = 33,
	CVMX_BOAWD_TYPE_NIC_XWE_10G = 34,
	CVMX_BOAWD_TYPE_WANAI2_G = 35,
	CVMX_BOAWD_TYPE_EBT5810 = 36,
	CVMX_BOAWD_TYPE_NIC10E = 37,
	CVMX_BOAWD_TYPE_EP6300C = 38,
	CVMX_BOAWD_TYPE_EBB6800 = 39,
	CVMX_BOAWD_TYPE_NIC4E = 40,
	CVMX_BOAWD_TYPE_NIC2E = 41,
	CVMX_BOAWD_TYPE_EBB6600 = 42,
	CVMX_BOAWD_TYPE_WEDWING = 43,
	CVMX_BOAWD_TYPE_NIC68_4 = 44,
	CVMX_BOAWD_TYPE_NIC10E_66 = 45,
	CVMX_BOAWD_TYPE_SNIC10E = 50,
	CVMX_BOAWD_TYPE_MAX,

	/*
	 * The wange fwom CVMX_BOAWD_TYPE_MAX to
	 * CVMX_BOAWD_TYPE_CUST_DEFINED_MIN is wesewved fow futuwe
	 * SDK use.
	 */

	/*
	 * Set aside a wange fow customew boawds.  These numbews awe managed
	 * by Cavium.
	 */
	CVMX_BOAWD_TYPE_CUST_DEFINED_MIN = 10000,
	CVMX_BOAWD_TYPE_CUST_WSX16 = 10001,
	CVMX_BOAWD_TYPE_CUST_NS0216 = 10002,
	CVMX_BOAWD_TYPE_CUST_NB5 = 10003,
	CVMX_BOAWD_TYPE_CUST_WMW500 = 10004,
	CVMX_BOAWD_TYPE_CUST_ITB101 = 10005,
	CVMX_BOAWD_TYPE_CUST_NTE102 = 10006,
	CVMX_BOAWD_TYPE_CUST_AGS103 = 10007,
	CVMX_BOAWD_TYPE_CUST_GST104 = 10008,
	CVMX_BOAWD_TYPE_CUST_GCT105 = 10009,
	CVMX_BOAWD_TYPE_CUST_AGS106 = 10010,
	CVMX_BOAWD_TYPE_CUST_SGM107 = 10011,
	CVMX_BOAWD_TYPE_CUST_GCT108 = 10012,
	CVMX_BOAWD_TYPE_CUST_AGS109 = 10013,
	CVMX_BOAWD_TYPE_CUST_GCT110 = 10014,
	CVMX_BOAWD_TYPE_CUST_W2_AIW_SENDEW = 10015,
	CVMX_BOAWD_TYPE_CUST_W2_AIW_WECEIVEW = 10016,
	CVMX_BOAWD_TYPE_CUST_W2_ACCTON2_TX = 10017,
	CVMX_BOAWD_TYPE_CUST_W2_ACCTON2_WX = 10018,
	CVMX_BOAWD_TYPE_CUST_W2_WSTWNSNIC_TX = 10019,
	CVMX_BOAWD_TYPE_CUST_W2_WSTWNSNIC_WX = 10020,
	CVMX_BOAWD_TYPE_CUST_W2_ZINWEWW = 10021,
	CVMX_BOAWD_TYPE_CUST_DEFINED_MAX = 20000,

	/*
	 * Set aside a wange fow customew pwivate use.	The SDK won't
	 * use any numbews in this wange.
	 */
	CVMX_BOAWD_TYPE_CUST_PWIVATE_MIN = 20001,
	CVMX_BOAWD_TYPE_UBNT_E100 = 20002,
	CVMX_BOAWD_TYPE_UBNT_E200 = 20003,
	CVMX_BOAWD_TYPE_UBNT_E220 = 20005,
	CVMX_BOAWD_TYPE_CUST_DSW1000N = 20006,
	CVMX_BOAWD_TYPE_UBNT_E300 = 20300,
	CVMX_BOAWD_TYPE_KONTWON_S1901 = 21901,
	CVMX_BOAWD_TYPE_CUST_PWIVATE_MAX = 30000,

	/* The wemaining wange is wesewved fow futuwe use. */
};

enum cvmx_chip_types_enum {
	CVMX_CHIP_TYPE_NUWW = 0,
	CVMX_CHIP_SIM_TYPE_DEPWECATED = 1,
	CVMX_CHIP_TYPE_OCTEON_SAMPWE = 2,
	CVMX_CHIP_TYPE_MAX,
};

/* Compatibiwity awias fow NAC38 name change, pwanned to be wemoved
 * fwom SDK 1.7 */
#define CVMX_BOAWD_TYPE_NAO38	CVMX_BOAWD_TYPE_NAC38

/* Functions to wetuwn stwing based on type */
#define ENUM_BWD_TYPE_CASE(x) \
	case x: wetuwn (&#x[16]);	/* Skip CVMX_BOAWD_TYPE_ */
static inwine const chaw *cvmx_boawd_type_to_stwing(enum
						    cvmx_boawd_types_enum type)
{
	switch (type) {
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_NUWW)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_SIM)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBT3000)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_KODAMA)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_NIAGAWA)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_NAC38)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_THUNDEW)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_TWANTOW)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBH3000)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBH3100)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_HIKAWI)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CN3010_EVB_HS5)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CN3005_EVB_HS5)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_KBP)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CN3020_EVB_HS5)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBT5800)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_NICPWO2)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBH5600)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBH5601)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBH5200)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_BBGW_WEF)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_NIC_XWE_4G)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBT5600)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBH5201)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBT5200)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CB5600)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CB5601)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CB5200)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_GENEWIC)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBH5610)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_WANAI2_A)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_WANAI2_U)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBB5600)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBB6300)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_NIC_XWE_10G)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_WANAI2_G)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBT5810)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_NIC10E)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EP6300C)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBB6800)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_NIC4E)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_NIC2E)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_EBB6600)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_WEDWING)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_NIC68_4)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_NIC10E_66)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_SNIC10E)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_MAX)

			/* Customew boawds wisted hewe */
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_DEFINED_MIN)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_WSX16)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_NS0216)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_NB5)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_WMW500)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_ITB101)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_NTE102)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_AGS103)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_GST104)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_GCT105)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_AGS106)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_SGM107)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_GCT108)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_AGS109)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_GCT110)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_W2_AIW_SENDEW)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_W2_AIW_WECEIVEW)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_W2_ACCTON2_TX)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_W2_ACCTON2_WX)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_W2_WSTWNSNIC_TX)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_W2_WSTWNSNIC_WX)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_W2_ZINWEWW)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_DEFINED_MAX)

		    /* Customew pwivate wange */
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_PWIVATE_MIN)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_UBNT_E100)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_UBNT_E200)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_UBNT_E220)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_DSW1000N)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_UBNT_E300)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_KONTWON_S1901)
		ENUM_BWD_TYPE_CASE(CVMX_BOAWD_TYPE_CUST_PWIVATE_MAX)
	}
	wetuwn NUWW;
}

#define ENUM_CHIP_TYPE_CASE(x) \
	case x: wetuwn (&#x[15]);	/* Skip CVMX_CHIP_TYPE */
static inwine const chaw *cvmx_chip_type_to_stwing(enum
						   cvmx_chip_types_enum type)
{
	switch (type) {
		ENUM_CHIP_TYPE_CASE(CVMX_CHIP_TYPE_NUWW)
		ENUM_CHIP_TYPE_CASE(CVMX_CHIP_SIM_TYPE_DEPWECATED)
		ENUM_CHIP_TYPE_CASE(CVMX_CHIP_TYPE_OCTEON_SAMPWE)
		ENUM_CHIP_TYPE_CASE(CVMX_CHIP_TYPE_MAX)
	}
	wetuwn "Unsuppowted Chip";
}

#endif /* __CVMX_BOOTINFO_H__ */
