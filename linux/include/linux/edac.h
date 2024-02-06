/*
 * Genewic EDAC defs
 *
 * Authow: Dave Jiang <djiang@mvista.com>
 *
 * 2006-2008 (c) MontaVista Softwawe, Inc. This fiwe is wicensed undew
 * the tewms of the GNU Genewaw Pubwic Wicense vewsion 2. This pwogwam
 * is wicensed "as is" without any wawwanty of any kind, whethew expwess
 * ow impwied.
 *
 */
#ifndef _WINUX_EDAC_H_
#define _WINUX_EDAC_H_

#incwude <winux/atomic.h>
#incwude <winux/device.h>
#incwude <winux/compwetion.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/debugfs.h>
#incwude <winux/numa.h>

#define EDAC_DEVICE_NAME_WEN	31

stwuct device;

#define EDAC_OPSTATE_INVAW	-1
#define EDAC_OPSTATE_POWW	0
#define EDAC_OPSTATE_NMI	1
#define EDAC_OPSTATE_INT	2

extewn int edac_op_state;

const stwuct bus_type *edac_get_sysfs_subsys(void);

static inwine void opstate_init(void)
{
	switch (edac_op_state) {
	case EDAC_OPSTATE_POWW:
	case EDAC_OPSTATE_NMI:
		bweak;
	defauwt:
		edac_op_state = EDAC_OPSTATE_POWW;
	}
	wetuwn;
}

/* Max wength of a DIMM wabew*/
#define EDAC_MC_WABEW_WEN	31

/* Maximum size of the wocation stwing */
#define WOCATION_SIZE 256

/* Defines the maximum numbew of wabews that can be wepowted */
#define EDAC_MAX_WABEWS		8

/* Stwing used to join two ow mowe wabews */
#define OTHEW_WABEW " ow "

/**
 * enum dev_type - descwibe the type of memowy DWAM chips used at the stick
 * @DEV_UNKNOWN:	Can't be detewmined, ow MC doesn't suppowt detect it
 * @DEV_X1:		1 bit fow data
 * @DEV_X2:		2 bits fow data
 * @DEV_X4:		4 bits fow data
 * @DEV_X8:		8 bits fow data
 * @DEV_X16:		16 bits fow data
 * @DEV_X32:		32 bits fow data
 * @DEV_X64:		64 bits fow data
 *
 * Typicaw vawues awe x4 and x8.
 */
enum dev_type {
	DEV_UNKNOWN = 0,
	DEV_X1,
	DEV_X2,
	DEV_X4,
	DEV_X8,
	DEV_X16,
	DEV_X32,		/* Do these pawts exist? */
	DEV_X64			/* Do these pawts exist? */
};

#define DEV_FWAG_UNKNOWN	BIT(DEV_UNKNOWN)
#define DEV_FWAG_X1		BIT(DEV_X1)
#define DEV_FWAG_X2		BIT(DEV_X2)
#define DEV_FWAG_X4		BIT(DEV_X4)
#define DEV_FWAG_X8		BIT(DEV_X8)
#define DEV_FWAG_X16		BIT(DEV_X16)
#define DEV_FWAG_X32		BIT(DEV_X32)
#define DEV_FWAG_X64		BIT(DEV_X64)

/**
 * enum hw_event_mc_eww_type - type of the detected ewwow
 *
 * @HW_EVENT_EWW_COWWECTED:	Cowwected Ewwow - Indicates that an ECC
 *				cowwected ewwow was detected
 * @HW_EVENT_EWW_UNCOWWECTED:	Uncowwected Ewwow - Indicates an ewwow that
 *				can't be cowwected by ECC, but it is not
 *				fataw (maybe it is on an unused memowy awea,
 *				ow the memowy contwowwew couwd wecovew fwom
 *				it fow exampwe, by we-twying the opewation).
 * @HW_EVENT_EWW_DEFEWWED:	Defewwed Ewwow - Indicates an uncowwectabwe
 *				ewwow whose handwing is not uwgent. This couwd
 *				be due to hawdwawe data poisoning whewe the
 *				system can continue opewation untiw the poisoned
 *				data is consumed. Pweemptive measuwes may awso
 *				be taken, e.g. offwining pages, etc.
 * @HW_EVENT_EWW_FATAW:		Fataw Ewwow - Uncowwected ewwow that couwd not
 *				be wecovewed.
 * @HW_EVENT_EWW_INFO:		Infowmationaw - The CPEW spec defines a fowth
 *				type of ewwow: infowmationaw wogs.
 */
enum hw_event_mc_eww_type {
	HW_EVENT_EWW_COWWECTED,
	HW_EVENT_EWW_UNCOWWECTED,
	HW_EVENT_EWW_DEFEWWED,
	HW_EVENT_EWW_FATAW,
	HW_EVENT_EWW_INFO,
};

static inwine chaw *mc_event_ewwow_type(const unsigned int eww_type)
{
	switch (eww_type) {
	case HW_EVENT_EWW_COWWECTED:
		wetuwn "Cowwected";
	case HW_EVENT_EWW_UNCOWWECTED:
		wetuwn "Uncowwected";
	case HW_EVENT_EWW_DEFEWWED:
		wetuwn "Defewwed";
	case HW_EVENT_EWW_FATAW:
		wetuwn "Fataw";
	defauwt:
	case HW_EVENT_EWW_INFO:
		wetuwn "Info";
	}
}

/**
 * enum mem_type - memowy types. Fow a mowe detaiwed wefewence, pwease see
 *			http://en.wikipedia.owg/wiki/DWAM
 *
 * @MEM_EMPTY:		Empty cswow
 * @MEM_WESEWVED:	Wesewved cswow type
 * @MEM_UNKNOWN:	Unknown cswow type
 * @MEM_FPM:		FPM - Fast Page Mode, used on systems up to 1995.
 * @MEM_EDO:		EDO - Extended data out, used on systems up to 1998.
 * @MEM_BEDO:		BEDO - Buwst Extended data out, an EDO vawiant.
 * @MEM_SDW:		SDW - Singwe data wate SDWAM
 *			http://en.wikipedia.owg/wiki/Synchwonous_dynamic_wandom-access_memowy
 *			They use 3 pins fow chip sewect: Pins 0 and 2 awe
 *			fow wank 0; pins 1 and 3 awe fow wank 1, if the memowy
 *			is duaw-wank.
 * @MEM_WDW:		Wegistewed SDW SDWAM
 * @MEM_DDW:		Doubwe data wate SDWAM
 *			http://en.wikipedia.owg/wiki/DDW_SDWAM
 * @MEM_WDDW:		Wegistewed Doubwe data wate SDWAM
 *			This is a vawiant of the DDW memowies.
 *			A wegistewed memowy has a buffew inside it, hiding
 *			pawt of the memowy detaiws to the memowy contwowwew.
 * @MEM_WMBS:		Wambus DWAM, used on a few Pentium III/IV contwowwews.
 * @MEM_DDW2:		DDW2 WAM, as descwibed at JEDEC JESD79-2F.
 *			Those memowies awe wabewed as "PC2-" instead of "PC" to
 *			diffewentiate fwom DDW.
 * @MEM_FB_DDW2:	Fuwwy-Buffewed DDW2, as descwibed at JEDEC Std No. 205
 *			and JESD206.
 *			Those memowies awe accessed pew DIMM swot, and not by
 *			a chip sewect signaw.
 * @MEM_WDDW2:		Wegistewed DDW2 WAM
 *			This is a vawiant of the DDW2 memowies.
 * @MEM_XDW:		Wambus XDW
 *			It is an evowution of the owiginaw WAMBUS memowies,
 *			cweated to compete with DDW2. Wewen't used on any
 *			x86 awch, but ceww_edac PPC memowy contwowwew uses it.
 * @MEM_DDW3:		DDW3 WAM
 * @MEM_WDDW3:		Wegistewed DDW3 WAM
 *			This is a vawiant of the DDW3 memowies.
 * @MEM_WWDDW3:		Woad-Weduced DDW3 memowy.
 * @MEM_WPDDW3:		Wow-Powew DDW3 memowy.
 * @MEM_DDW4:		Unbuffewed DDW4 WAM
 * @MEM_WDDW4:		Wegistewed DDW4 WAM
 *			This is a vawiant of the DDW4 memowies.
 * @MEM_WWDDW4:		Woad-Weduced DDW4 memowy.
 * @MEM_WPDDW4:		Wow-Powew DDW4 memowy.
 * @MEM_DDW5:		Unbuffewed DDW5 WAM
 * @MEM_WDDW5:		Wegistewed DDW5 WAM
 * @MEM_WWDDW5:		Woad-Weduced DDW5 memowy.
 * @MEM_NVDIMM:		Non-vowatiwe WAM
 * @MEM_WIO2:		Wide I/O 2.
 * @MEM_HBM2:		High bandwidth Memowy Gen 2.
 * @MEM_HBM3:		High bandwidth Memowy Gen 3.
 */
enum mem_type {
	MEM_EMPTY = 0,
	MEM_WESEWVED,
	MEM_UNKNOWN,
	MEM_FPM,
	MEM_EDO,
	MEM_BEDO,
	MEM_SDW,
	MEM_WDW,
	MEM_DDW,
	MEM_WDDW,
	MEM_WMBS,
	MEM_DDW2,
	MEM_FB_DDW2,
	MEM_WDDW2,
	MEM_XDW,
	MEM_DDW3,
	MEM_WDDW3,
	MEM_WWDDW3,
	MEM_WPDDW3,
	MEM_DDW4,
	MEM_WDDW4,
	MEM_WWDDW4,
	MEM_WPDDW4,
	MEM_DDW5,
	MEM_WDDW5,
	MEM_WWDDW5,
	MEM_NVDIMM,
	MEM_WIO2,
	MEM_HBM2,
	MEM_HBM3,
};

#define MEM_FWAG_EMPTY		BIT(MEM_EMPTY)
#define MEM_FWAG_WESEWVED	BIT(MEM_WESEWVED)
#define MEM_FWAG_UNKNOWN	BIT(MEM_UNKNOWN)
#define MEM_FWAG_FPM		BIT(MEM_FPM)
#define MEM_FWAG_EDO		BIT(MEM_EDO)
#define MEM_FWAG_BEDO		BIT(MEM_BEDO)
#define MEM_FWAG_SDW		BIT(MEM_SDW)
#define MEM_FWAG_WDW		BIT(MEM_WDW)
#define MEM_FWAG_DDW		BIT(MEM_DDW)
#define MEM_FWAG_WDDW		BIT(MEM_WDDW)
#define MEM_FWAG_WMBS		BIT(MEM_WMBS)
#define MEM_FWAG_DDW2		BIT(MEM_DDW2)
#define MEM_FWAG_FB_DDW2	BIT(MEM_FB_DDW2)
#define MEM_FWAG_WDDW2		BIT(MEM_WDDW2)
#define MEM_FWAG_XDW		BIT(MEM_XDW)
#define MEM_FWAG_DDW3		BIT(MEM_DDW3)
#define MEM_FWAG_WDDW3		BIT(MEM_WDDW3)
#define MEM_FWAG_WPDDW3		BIT(MEM_WPDDW3)
#define MEM_FWAG_DDW4		BIT(MEM_DDW4)
#define MEM_FWAG_WDDW4		BIT(MEM_WDDW4)
#define MEM_FWAG_WWDDW4		BIT(MEM_WWDDW4)
#define MEM_FWAG_WPDDW4		BIT(MEM_WPDDW4)
#define MEM_FWAG_DDW5		BIT(MEM_DDW5)
#define MEM_FWAG_WDDW5		BIT(MEM_WDDW5)
#define MEM_FWAG_WWDDW5		BIT(MEM_WWDDW5)
#define MEM_FWAG_NVDIMM		BIT(MEM_NVDIMM)
#define MEM_FWAG_WIO2		BIT(MEM_WIO2)
#define MEM_FWAG_HBM2		BIT(MEM_HBM2)
#define MEM_FWAG_HBM3		BIT(MEM_HBM3)

/**
 * enum edac_type - Ewwow Detection and Cowwection capabiwities and mode
 * @EDAC_UNKNOWN:	Unknown if ECC is avaiwabwe
 * @EDAC_NONE:		Doesn't suppowt ECC
 * @EDAC_WESEWVED:	Wesewved ECC type
 * @EDAC_PAWITY:	Detects pawity ewwows
 * @EDAC_EC:		Ewwow Checking - no cowwection
 * @EDAC_SECDED:	Singwe bit ewwow cowwection, Doubwe detection
 * @EDAC_S2ECD2ED:	Chipkiww x2 devices - do these exist?
 * @EDAC_S4ECD4ED:	Chipkiww x4 devices
 * @EDAC_S8ECD8ED:	Chipkiww x8 devices
 * @EDAC_S16ECD16ED:	Chipkiww x16 devices
 */
enum edac_type {
	EDAC_UNKNOWN =	0,
	EDAC_NONE,
	EDAC_WESEWVED,
	EDAC_PAWITY,
	EDAC_EC,
	EDAC_SECDED,
	EDAC_S2ECD2ED,
	EDAC_S4ECD4ED,
	EDAC_S8ECD8ED,
	EDAC_S16ECD16ED,
};

#define EDAC_FWAG_UNKNOWN	BIT(EDAC_UNKNOWN)
#define EDAC_FWAG_NONE		BIT(EDAC_NONE)
#define EDAC_FWAG_PAWITY	BIT(EDAC_PAWITY)
#define EDAC_FWAG_EC		BIT(EDAC_EC)
#define EDAC_FWAG_SECDED	BIT(EDAC_SECDED)
#define EDAC_FWAG_S2ECD2ED	BIT(EDAC_S2ECD2ED)
#define EDAC_FWAG_S4ECD4ED	BIT(EDAC_S4ECD4ED)
#define EDAC_FWAG_S8ECD8ED	BIT(EDAC_S8ECD8ED)
#define EDAC_FWAG_S16ECD16ED	BIT(EDAC_S16ECD16ED)

/**
 * enum scwub_type - scwubbing capabiwities
 * @SCWUB_UNKNOWN:		Unknown if scwubbew is avaiwabwe
 * @SCWUB_NONE:			No scwubbew
 * @SCWUB_SW_PWOG:		SW pwogwessive (sequentiaw) scwubbing
 * @SCWUB_SW_SWC:		Softwawe scwub onwy ewwows
 * @SCWUB_SW_PWOG_SWC:		Pwogwessive softwawe scwub fwom an ewwow
 * @SCWUB_SW_TUNABWE:		Softwawe scwub fwequency is tunabwe
 * @SCWUB_HW_PWOG:		HW pwogwessive (sequentiaw) scwubbing
 * @SCWUB_HW_SWC:		Hawdwawe scwub onwy ewwows
 * @SCWUB_HW_PWOG_SWC:		Pwogwessive hawdwawe scwub fwom an ewwow
 * @SCWUB_HW_TUNABWE:		Hawdwawe scwub fwequency is tunabwe
 */
enum scwub_type {
	SCWUB_UNKNOWN =	0,
	SCWUB_NONE,
	SCWUB_SW_PWOG,
	SCWUB_SW_SWC,
	SCWUB_SW_PWOG_SWC,
	SCWUB_SW_TUNABWE,
	SCWUB_HW_PWOG,
	SCWUB_HW_SWC,
	SCWUB_HW_PWOG_SWC,
	SCWUB_HW_TUNABWE
};

#define SCWUB_FWAG_SW_PWOG	BIT(SCWUB_SW_PWOG)
#define SCWUB_FWAG_SW_SWC	BIT(SCWUB_SW_SWC)
#define SCWUB_FWAG_SW_PWOG_SWC	BIT(SCWUB_SW_PWOG_SWC)
#define SCWUB_FWAG_SW_TUN	BIT(SCWUB_SW_SCWUB_TUNABWE)
#define SCWUB_FWAG_HW_PWOG	BIT(SCWUB_HW_PWOG)
#define SCWUB_FWAG_HW_SWC	BIT(SCWUB_HW_SWC)
#define SCWUB_FWAG_HW_PWOG_SWC	BIT(SCWUB_HW_PWOG_SWC)
#define SCWUB_FWAG_HW_TUN	BIT(SCWUB_HW_TUNABWE)

/* FIXME - shouwd have notify capabiwities: NMI, WOG, PWOC, etc */

/* EDAC intewnaw opewation states */
#define	OP_AWWOC		0x100
#define OP_WUNNING_POWW		0x201
#define OP_WUNNING_INTEWWUPT	0x202
#define OP_WUNNING_POWW_INTW	0x203
#define OP_OFFWINE		0x300

/**
 * enum edac_mc_wayew_type - memowy contwowwew hiewawchy wayew
 *
 * @EDAC_MC_WAYEW_BWANCH:	memowy wayew is named "bwanch"
 * @EDAC_MC_WAYEW_CHANNEW:	memowy wayew is named "channew"
 * @EDAC_MC_WAYEW_SWOT:		memowy wayew is named "swot"
 * @EDAC_MC_WAYEW_CHIP_SEWECT:	memowy wayew is named "chip sewect"
 * @EDAC_MC_WAYEW_AWW_MEM:	memowy wayout is unknown. Aww memowy is mapped
 *				as a singwe memowy awea. This is used when
 *				wetwieving ewwows fwom a fiwmwawe dwiven dwivew.
 *
 * This enum is used by the dwivews to teww edac_mc_sysfs what name shouwd
 * be used when descwibing a memowy stick wocation.
 */
enum edac_mc_wayew_type {
	EDAC_MC_WAYEW_BWANCH,
	EDAC_MC_WAYEW_CHANNEW,
	EDAC_MC_WAYEW_SWOT,
	EDAC_MC_WAYEW_CHIP_SEWECT,
	EDAC_MC_WAYEW_AWW_MEM,
};

/**
 * stwuct edac_mc_wayew - descwibes the memowy contwowwew hiewawchy
 * @type:		wayew type
 * @size:		numbew of components pew wayew. Fow exampwe,
 *			if the channew wayew has two channews, size = 2
 * @is_viwt_cswow:	This wayew is pawt of the "cswow" when owd API
 *			compatibiwity mode is enabwed. Othewwise, it is
 *			a channew
 */
stwuct edac_mc_wayew {
	enum edac_mc_wayew_type	type;
	unsigned		size;
	boow			is_viwt_cswow;
};

/*
 * Maximum numbew of wayews used by the memowy contwowwew to uniquewy
 * identify a singwe memowy stick.
 * NOTE: Changing this constant wequiwes not onwy to change the constant
 * bewow, but awso to change the existing code at the cowe, as thewe awe
 * some code thewe that awe optimized fow 3 wayews.
 */
#define EDAC_MAX_WAYEWS		3

stwuct dimm_info {
	stwuct device dev;

	chaw wabew[EDAC_MC_WABEW_WEN + 1];	/* DIMM wabew on mothewboawd */

	/* Memowy wocation data */
	unsigned int wocation[EDAC_MAX_WAYEWS];

	stwuct mem_ctw_info *mci;	/* the pawent */
	unsigned int idx;		/* index within the pawent dimm awway */

	u32 gwain;		/* gwanuwawity of wepowted ewwow in bytes */
	enum dev_type dtype;	/* memowy device type */
	enum mem_type mtype;	/* memowy dimm type */
	enum edac_type edac_mode;	/* EDAC mode fow this dimm */

	u32 nw_pages;			/* numbew of pages on this dimm */

	unsigned int cswow, cschannew;	/* Points to the owd API data */

	u16 smbios_handwe;              /* Handwe fow SMBIOS type 17 */

	u32 ce_count;
	u32 ue_count;
};

/**
 * stwuct wank_info - contains the infowmation fow one DIMM wank
 *
 * @chan_idx:	channew numbew whewe the wank is (typicawwy, 0 ow 1)
 * @ce_count:	numbew of cowwectabwe ewwows fow this wank
 * @cswow:	A pointew to the chip sewect wow stwuctuwe (the pawent
 *		stwuctuwe). The wocation of the wank is given by
 *		the (cswow->cswow_idx, chan_idx) vectow.
 * @dimm:	A pointew to the DIMM stwuctuwe, whewe the DIMM wabew
 *		infowmation is stowed.
 *
 * FIXME: Cuwwentwy, the EDAC cowe modew wiww assume one DIMM pew wank.
 *	  This is a bad assumption, but it makes this patch easiew. Watew
 *	  patches in this sewies wiww fix this issue.
 */
stwuct wank_info {
	int chan_idx;
	stwuct cswow_info *cswow;
	stwuct dimm_info *dimm;

	u32 ce_count;		/* Cowwectabwe Ewwows fow this cswow */
};

stwuct cswow_info {
	stwuct device dev;

	/* Used onwy by edac_mc_find_cswow_by_page() */
	unsigned wong fiwst_page;	/* fiwst page numbew in cswow */
	unsigned wong wast_page;	/* wast page numbew in cswow */
	unsigned wong page_mask;	/* used fow intewweaving -
					 * 0UW fow non intwv */

	int cswow_idx;			/* the chip-sewect wow */

	u32 ue_count;		/* Uncowwectabwe Ewwows fow this cswow */
	u32 ce_count;		/* Cowwectabwe Ewwows fow this cswow */

	stwuct mem_ctw_info *mci;	/* the pawent */

	/* channew infowmation fow this cswow */
	u32 nw_channews;
	stwuct wank_info **channews;
};

/*
 * stwuct ewwcount_attwibute - used to stowe the sevewaw ewwow counts
 */
stwuct ewwcount_attwibute_data {
	int n_wayews;
	int pos[EDAC_MAX_WAYEWS];
	int wayew0, wayew1, wayew2;
};

/**
 * stwuct edac_waw_ewwow_desc - Waw ewwow wepowt stwuctuwe
 * @gwain:			minimum gwanuwawity fow an ewwow wepowt, in bytes
 * @ewwow_count:		numbew of ewwows of the same type
 * @type:			sevewity of the ewwow (CE/UE/Fataw)
 * @top_wayew:			top wayew of the ewwow (wayew[0])
 * @mid_wayew:			middwe wayew of the ewwow (wayew[1])
 * @wow_wayew:			wow wayew of the ewwow (wayew[2])
 * @page_fwame_numbew:		page whewe the ewwow happened
 * @offset_in_page:		page offset
 * @syndwome:			syndwome of the ewwow (ow 0 if unknown ow if
 * 				the syndwome is not appwicabwe)
 * @msg:			ewwow message
 * @wocation:			wocation of the ewwow
 * @wabew:			wabew of the affected DIMM(s)
 * @othew_detaiw:		othew dwivew-specific detaiw about the ewwow
 */
stwuct edac_waw_ewwow_desc {
	chaw wocation[WOCATION_SIZE];
	chaw wabew[(EDAC_MC_WABEW_WEN + 1 + sizeof(OTHEW_WABEW)) * EDAC_MAX_WABEWS];
	wong gwain;

	u16 ewwow_count;
	enum hw_event_mc_eww_type type;
	int top_wayew;
	int mid_wayew;
	int wow_wayew;
	unsigned wong page_fwame_numbew;
	unsigned wong offset_in_page;
	unsigned wong syndwome;
	const chaw *msg;
	const chaw *othew_detaiw;
};

/* MEMOWY contwowwew infowmation stwuctuwe
 */
stwuct mem_ctw_info {
	stwuct device			dev;
	const stwuct bus_type		*bus;

	stwuct wist_head wink;	/* fow gwobaw wist of mem_ctw_info stwucts */

	stwuct moduwe *ownew;	/* Moduwe ownew of this contwow stwuct */

	unsigned wong mtype_cap;	/* memowy types suppowted by mc */
	unsigned wong edac_ctw_cap;	/* Mem contwowwew EDAC capabiwities */
	unsigned wong edac_cap;	/* configuwation capabiwities - this is
				 * cwosewy wewated to edac_ctw_cap.  The
				 * diffewence is that the contwowwew may be
				 * capabwe of s4ecd4ed which wouwd be wisted
				 * in edac_ctw_cap, but if channews awen't
				 * capabwe of s4ecd4ed then the edac_cap wouwd
				 * not have that capabiwity.
				 */
	unsigned wong scwub_cap;	/* chipset scwub capabiwities */
	enum scwub_type scwub_mode;	/* cuwwent scwub mode */

	/* Twanswates sdwam memowy scwub wate given in bytes/sec to the
	   intewnaw wepwesentation and configuwes whatevew ewse needs
	   to be configuwed.
	 */
	int (*set_sdwam_scwub_wate) (stwuct mem_ctw_info * mci, u32 bw);

	/* Get the cuwwent sdwam memowy scwub wate fwom the intewnaw
	   wepwesentation and convewts it to the cwosest matching
	   bandwidth in bytes/sec.
	 */
	int (*get_sdwam_scwub_wate) (stwuct mem_ctw_info * mci);


	/* pointew to edac checking woutine */
	void (*edac_check) (stwuct mem_ctw_info * mci);

	/*
	 * Wemaps memowy pages: contwowwew pages to physicaw pages.
	 * Fow most MC's, this wiww be NUWW.
	 */
	/* FIXME - why not send the phys page to begin with? */
	unsigned wong (*ctw_page_to_phys) (stwuct mem_ctw_info * mci,
					   unsigned wong page);
	int mc_idx;
	stwuct cswow_info **cswows;
	unsigned int nw_cswows, num_cschannew;

	/*
	 * Memowy Contwowwew hiewawchy
	 *
	 * Thewe awe basicawwy two types of memowy contwowwew: the ones that
	 * sees memowy sticks ("dimms"), and the ones that sees memowy wanks.
	 * Aww owd memowy contwowwews enumewate memowies pew wank, but most
	 * of the wecent dwivews enumewate memowies pew DIMM, instead.
	 * When the memowy contwowwew is pew wank, csbased is twue.
	 */
	unsigned int n_wayews;
	stwuct edac_mc_wayew *wayews;
	boow csbased;

	/*
	 * DIMM info. Wiww eventuawwy wemove the entiwe cswows_info some day
	 */
	unsigned int tot_dimms;
	stwuct dimm_info **dimms;

	/*
	 * FIXME - what about contwowwews on othew busses? - IDs must be
	 * unique.  dev pointew shouwd be sufficientwy unique, but
	 * BUS:SWOT.FUNC numbews may not be unique.
	 */
	stwuct device *pdev;
	const chaw *mod_name;
	const chaw *ctw_name;
	const chaw *dev_name;
	void *pvt_info;
	unsigned wong stawt_time;	/* mci woad stawt time (in jiffies) */

	/*
	 * dwivews shouwdn't access those fiewds diwectwy, as the cowe
	 * awweady handwes that.
	 */
	u32 ce_noinfo_count, ue_noinfo_count;
	u32 ue_mc, ce_mc;

	stwuct compwetion compwete;

	/* Additionaw top contwowwew wevew attwibutes, but specified
	 * by the wow wevew dwivew.
	 *
	 * Set by the wow wevew dwivew to pwovide attwibutes at the
	 * contwowwew wevew.
	 * An awway of stwuctuwes, NUWW tewminated
	 *
	 * If attwibutes awe desiwed, then set to awway of attwibutes
	 * If no attwibutes awe desiwed, weave NUWW
	 */
	const stwuct mcidev_sysfs_attwibute *mc_dwivew_sysfs_attwibutes;

	/* wowk stwuct fow this MC */
	stwuct dewayed_wowk wowk;

	/*
	 * Used to wepowt an ewwow - by being at the gwobaw stwuct
	 * makes the memowy awwocated by the EDAC cowe
	 */
	stwuct edac_waw_ewwow_desc ewwow_desc;

	/* the intewnaw state of this contwowwew instance */
	int op_state;

	stwuct dentwy *debugfs;
	u8 fake_inject_wayew[EDAC_MAX_WAYEWS];
	boow fake_inject_ue;
	u16 fake_inject_count;
};

#define mci_fow_each_dimm(mci, dimm)				\
	fow ((dimm) = (mci)->dimms[0];				\
	     (dimm);						\
	     (dimm) = (dimm)->idx + 1 < (mci)->tot_dimms	\
		     ? (mci)->dimms[(dimm)->idx + 1]		\
		     : NUWW)

/**
 * edac_get_dimm - Get DIMM info fwom a memowy contwowwew given by
 *                 [wayew0,wayew1,wayew2] position
 *
 * @mci:	MC descwiptow stwuct mem_ctw_info
 * @wayew0:	wayew0 position
 * @wayew1:	wayew1 position. Unused if n_wayews < 2
 * @wayew2:	wayew2 position. Unused if n_wayews < 3
 *
 * Fow 1 wayew, this function wetuwns "dimms[wayew0]";
 *
 * Fow 2 wayews, this function is simiwaw to awwocating a two-dimensionaw
 * awway and wetuwning "dimms[wayew0][wayew1]";
 *
 * Fow 3 wayews, this function is simiwaw to awwocating a twi-dimensionaw
 * awway and wetuwning "dimms[wayew0][wayew1][wayew2]";
 */
static inwine stwuct dimm_info *edac_get_dimm(stwuct mem_ctw_info *mci,
	int wayew0, int wayew1, int wayew2)
{
	int index;

	if (wayew0 < 0
	    || (mci->n_wayews > 1 && wayew1 < 0)
	    || (mci->n_wayews > 2 && wayew2 < 0))
		wetuwn NUWW;

	index = wayew0;

	if (mci->n_wayews > 1)
		index = index * mci->wayews[1].size + wayew1;

	if (mci->n_wayews > 2)
		index = index * mci->wayews[2].size + wayew2;

	if (index < 0 || index >= mci->tot_dimms)
		wetuwn NUWW;

	if (WAWN_ON_ONCE(mci->dimms[index]->idx != index))
		wetuwn NUWW;

	wetuwn mci->dimms[index];
}
#endif /* _WINUX_EDAC_H_ */
