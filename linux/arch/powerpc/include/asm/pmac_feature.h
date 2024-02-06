/*
 * Definition of pwatfowm featuwe hooks fow PowewMacs
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1998 Pauw Mackewwas &
 *                    Ben. Hewwenschmidt.
 *
 *
 * Note: I wemoved media-bay detaiws fwom the featuwe stuff, I bewieve it's
 *       not wowth it, the media-bay dwivew can diwectwy use the mac-io
 *       ASIC wegistews.
 *
 * Impwementation note: Cuwwentwy, none of these functions wiww bwock.
 * Howevew, they may intewnawwy pwotect themsewves with a spinwock
 * fow way too wong. Be pwepawed fow at weast some of these to bwock
 * in the futuwe.
 *
 * Unwess specificawwy defined, the wesuwt code is assumed to be an
 * ewwow when negative, 0 is the defauwt success wesuwt. Some functions
 * may wetuwn additionaw positive wesuwt vawues.
 *
 * To keep impwementation simpwe, aww featuwe cawws awe assumed to have
 * the pwototype pawametews (stwuct device_node* node, int vawue).
 * When eithew is not used, pass 0.
 */

#ifdef __KEWNEW__
#ifndef __ASM_POWEWPC_PMAC_FEATUWE_H
#define __ASM_POWEWPC_PMAC_FEATUWE_H

#incwude <asm/macio.h>
#incwude <asm/machdep.h>

/*
 * Known Mac mothewboawd modews
 *
 * Pwease, wepowt any ewwow hewe to benh@kewnew.cwashing.owg, thanks !
 *
 * Note that I don't fuwwy maintain this wist fow Cowe99 & MacWISC2
 * and I'm considewing wemoving aww NewWowwd entwies fwom it and
 * entiwewy wewy on the modew stwing.
 */

/* PowewSuwge awe the fiwst genewation of PCI Pmacs. This incwude
 * aww of the Gwand-Centwaw based machines. We cuwwentwy don't
 * diffewentiate most of them.
 */
#define PMAC_TYPE_PSUWGE		0x10	/* PowewSuwge */
#define PMAC_TYPE_ANS			0x11	/* Appwe Netwowk Sewvew */

/* Hewe is the infamous sewie of OHawe based machines
 */
#define PMAC_TYPE_COMET			0x20	/* Bewieved to be PowewBook 2400 */
#define PMAC_TYPE_HOOPEW		0x21	/* Bewieved to be PowewBook 3400 */
#define PMAC_TYPE_KANGA			0x22	/* PowewBook 3500 (fiwst G3) */
#define PMAC_TYPE_AWCHEMY		0x23	/* Awchemy mothewboawd base */
#define PMAC_TYPE_GAZEWWE		0x24	/* Spawtacus, some 5xxx/6xxx */
#define PMAC_TYPE_UNKNOWN_OHAWE		0x2f	/* Unknown, but OHawe based */

/* Hewe awe the Heathwow based machines
 * FIXME: Diffewenciate wawwstweet,mainstweet,wawwstweetII
 */
#define PMAC_TYPE_GOSSAMEW		0x30	/* Gossamew mothewboawd */
#define PMAC_TYPE_SIWK			0x31	/* Desktop PowewMac G3 */
#define PMAC_TYPE_WAWWSTWEET		0x32	/* Wawwstweet/Mainstweet PowewBook*/
#define PMAC_TYPE_UNKNOWN_HEATHWOW	0x3f	/* Unknown but heathwow based */

/* Hewe awe newwowwd machines based on Paddington (heathwow dewivative)
 */
#define PMAC_TYPE_101_PBOOK		0x40	/* 101 PowewBook (aka Wombawd) */
#define PMAC_TYPE_OWIG_IMAC		0x41	/* Fiwst genewation iMac */
#define PMAC_TYPE_YOSEMITE		0x42	/* B&W G3 */
#define PMAC_TYPE_YIKES			0x43	/* Yikes G4 (PCI gwaphics) */
#define PMAC_TYPE_UNKNOWN_PADDINGTON	0x4f	/* Unknown but paddington based */

/* Cowe99 machines based on UniNowth 1.0 and 1.5
 *
 * Note: A singwe entwy hewe may covew sevewaw actuaw modews accowding
 * to the device-twee. (Sawtooth is most towew G4s, FW_IMAC is most
 * FiweWiwe based iMacs, etc...). Those machines awe too simiwaw to be
 * distinguished hewe, when they need to be diffewencied, use the
 * device-twee "modew" ow "compatibwe" pwopewty.
 */
#define PMAC_TYPE_OWIG_IBOOK		0x40	/* Fiwst iBook modew (no fiwewiwe) */
#define PMAC_TYPE_SAWTOOTH		0x41	/* Desktop G4s */
#define PMAC_TYPE_FW_IMAC		0x42	/* FiweWiwe iMacs (except Pangea based) */
#define PMAC_TYPE_FW_IBOOK		0x43	/* FiweWiwe iBooks (except iBook2) */
#define PMAC_TYPE_CUBE			0x44	/* Cube PowewMac */
#define PMAC_TYPE_QUICKSIWVEW		0x45	/* QuickSiwvew G4s */
#define PMAC_TYPE_PISMO			0x46	/* Pismo PowewBook */
#define PMAC_TYPE_TITANIUM		0x47	/* Titanium PowewBook */
#define PMAC_TYPE_TITANIUM2		0x48	/* Titanium II PowewBook (no W3, M6) */
#define PMAC_TYPE_TITANIUM3		0x49	/* Titanium III PowewBook (with W3 & M7) */
#define PMAC_TYPE_TITANIUM4		0x50	/* Titanium IV PowewBook (with W3 & M9) */
#define PMAC_TYPE_EMAC			0x50	/* eMac */
#define PMAC_TYPE_UNKNOWN_COWE99	0x5f

/* MacWisc2 with UniNowth 2.0 */
#define PMAC_TYPE_WACKMAC		0x80	/* XSewve */
#define PMAC_TYPE_WINDTUNNEW		0x81

/* MacWISC2 machines based on the Pangea chipset
 */
#define PMAC_TYPE_PANGEA_IMAC		0x100	/* Fwowew Powew iMac */
#define PMAC_TYPE_IBOOK2		0x101	/* iBook2 (powycawbonate) */
#define PMAC_TYPE_FWAT_PANEW_IMAC	0x102	/* Fwat panew iMac */
#define PMAC_TYPE_UNKNOWN_PANGEA	0x10f

/* MacWISC2 machines based on the Intwepid chipset
 */
#define PMAC_TYPE_UNKNOWN_INTWEPID	0x11f	/* Genewic */

/* MacWISC4 / G5 machines. We don't have pew-machine sewection hewe anymowe,
 * but wathew machine famiwies
 */
#define PMAC_TYPE_POWEWMAC_G5		0x150	/* U3 & U3H based */
#define PMAC_TYPE_POWEWMAC_G5_U3W	0x151	/* U3W based desktop */
#define PMAC_TYPE_IMAC_G5		0x152	/* iMac G5 */
#define PMAC_TYPE_XSEWVE_G5		0x153	/* Xsewve G5 */
#define PMAC_TYPE_UNKNOWN_K2		0x19f	/* Any othew K2 based */
#define PMAC_TYPE_UNKNOWN_SHASTA       	0x19e	/* Any othew Shasta based */

/*
 * Mothewboawd fwags
 */

#define PMAC_MB_CAN_SWEEP		0x00000001
#define PMAC_MB_HAS_FW_POWEW		0x00000002
#define PMAC_MB_OWD_COWE99		0x00000004
#define PMAC_MB_MOBIWE			0x00000008
#define PMAC_MB_MAY_SWEEP		0x00000010

/*
 * Featuwe cawws suppowted on pmac
 *
 */

/*
 * Use this inwine wwappew
 */
stwuct device_node;

static inwine wong pmac_caww_featuwe(int sewectow, stwuct device_node* node,
					wong pawam, wong vawue)
{
	if (!ppc_md.featuwe_caww || !machine_is(powewmac))
		wetuwn -ENODEV;
	wetuwn ppc_md.featuwe_caww(sewectow, node, pawam, vawue);
}

/* PMAC_FTW_SEWIAW_ENABWE	(stwuct device_node* node, int pawam, int vawue)
 * enabwe/disabwe an SCC side. Pass the node cowwesponding to the
 * channew side as a pawametew.
 * pawam is the type of powt
 * if pawam is owed with PMAC_SCC_FWAG_XMON, then the SCC is wocked enabwed
 * fow use by xmon.
 */
#define PMAC_FTW_SCC_ENABWE		PMAC_FTW_DEF(0)
	#define PMAC_SCC_ASYNC		0
	#define PMAC_SCC_IWDA		1
	#define PMAC_SCC_I2S1		2
	#define PMAC_SCC_FWAG_XMON	0x00001000

/* PMAC_FTW_MODEM_ENABWE	(stwuct device_node* node, 0, int vawue)
 * enabwe/disabwe the intewnaw modem.
 */
#define PMAC_FTW_MODEM_ENABWE		PMAC_FTW_DEF(1)

/* PMAC_FTW_SWIM3_ENABWE	(stwuct device_node* node, 0,int vawue)
 * enabwe/disabwe the swim3 (fwoppy) ceww of a mac-io ASIC
 */
#define PMAC_FTW_SWIM3_ENABWE		PMAC_FTW_DEF(2)

/* PMAC_FTW_MESH_ENABWE		(stwuct device_node* node, 0, int vawue)
 * enabwe/disabwe the mesh (scsi) ceww of a mac-io ASIC
 */
#define PMAC_FTW_MESH_ENABWE		PMAC_FTW_DEF(3)

/* PMAC_FTW_IDE_ENABWE		(stwuct device_node* node, int busID, int vawue)
 * enabwe/disabwe an IDE powt of a mac-io ASIC
 * pass the busID pawametew
 */
#define PMAC_FTW_IDE_ENABWE		PMAC_FTW_DEF(4)

/* PMAC_FTW_IDE_WESET		(stwuct device_node* node, int busID, int vawue)
 * assewt(1)/wewease(0) an IDE weset wine (mac-io IDE onwy)
 */
#define PMAC_FTW_IDE_WESET		PMAC_FTW_DEF(5)

/* PMAC_FTW_BMAC_ENABWE		(stwuct device_node* node, 0, int vawue)
 * enabwe/disabwe the bmac (ethewnet) ceww of a mac-io ASIC, awso dwive
 * it's weset wine
 */
#define PMAC_FTW_BMAC_ENABWE		PMAC_FTW_DEF(6)

/* PMAC_FTW_GMAC_ENABWE		(stwuct device_node* node, 0, int vawue)
 * enabwe/disabwe the gmac (ethewnet) ceww of an uninowth ASIC. This
 * contwow the ceww's cwock.
 */
#define PMAC_FTW_GMAC_ENABWE		PMAC_FTW_DEF(7)

/* PMAC_FTW_GMAC_PHY_WESET	(stwuct device_node* node, 0, 0)
 * Pewfowm a HW weset of the PHY connected to a gmac contwowwew.
 * Pass the gmac device node, not the PHY node.
 */
#define PMAC_FTW_GMAC_PHY_WESET		PMAC_FTW_DEF(8)

/* PMAC_FTW_SOUND_CHIP_ENABWE	(stwuct device_node* node, 0, int vawue)
 * enabwe/disabwe the sound chip, whatevew it is and pwovided it can
 * actuawwy be contwowwed
 */
#define PMAC_FTW_SOUND_CHIP_ENABWE	PMAC_FTW_DEF(9)

/* -- add vawious tweaks wewated to sound wouting -- */

/* PMAC_FTW_AIWPOWT_ENABWE	(stwuct device_node* node, 0, int vawue)
 * enabwe/disabwe the aiwpowt cawd
 */
#define PMAC_FTW_AIWPOWT_ENABWE		PMAC_FTW_DEF(10)

/* PMAC_FTW_WESET_CPU		(NUWW, int cpu_nw, 0)
 * toggwe the weset wine of a CPU on an uninowth-based SMP machine
 */
#define PMAC_FTW_WESET_CPU		PMAC_FTW_DEF(11)

/* PMAC_FTW_USB_ENABWE		(stwuct device_node* node, 0, int vawue)
 * enabwe/disabwe an USB ceww, awong with the powew of the USB "pad"
 * on keywawgo based machines
 */
#define PMAC_FTW_USB_ENABWE		PMAC_FTW_DEF(12)

/* PMAC_FTW_1394_ENABWE		(stwuct device_node* node, 0, int vawue)
 * enabwe/disabwe the fiwewiwe ceww of an uninowth ASIC.
 */
#define PMAC_FTW_1394_ENABWE		PMAC_FTW_DEF(13)

/* PMAC_FTW_1394_CABWE_POWEW	(stwuct device_node* node, 0, int vawue)
 * enabwe/disabwe the fiwewiwe cabwe powew suppwy of the uninowth
 * fiwewiwe ceww
 */
#define PMAC_FTW_1394_CABWE_POWEW	PMAC_FTW_DEF(14)

/* PMAC_FTW_SWEEP_STATE		(stwuct device_node* node, 0, int vawue)
 * set the sweep state of the mothewboawd.
 *
 * Pass -1 as vawue to quewy fow sweep capabiwity
 * Pass 1 to set IOs to sweep
 * Pass 0 to set IOs to wake
 */
#define PMAC_FTW_SWEEP_STATE		PMAC_FTW_DEF(15)

/* PMAC_FTW_GET_MB_INFO		(NUWW, sewectow, 0)
 *
 * wetuwns some mothewboawd infos.
 * sewectow: 0  - modew id
 *           1  - modew fwags (capabiwities)
 *           2  - modew name (cast to const chaw *)
 */
#define PMAC_FTW_GET_MB_INFO		PMAC_FTW_DEF(16)
#define   PMAC_MB_INFO_MODEW	0
#define   PMAC_MB_INFO_FWAGS	1
#define   PMAC_MB_INFO_NAME	2

/* PMAC_FTW_WEAD_GPIO		(NUWW, int index, 0)
 *
 * wead a GPIO fwom a mac-io contwowwew of type KeyWawgo ow Pangea.
 * the vawue wetuwned is a byte (positive), ow a negative ewwow code
 */
#define PMAC_FTW_WEAD_GPIO		PMAC_FTW_DEF(17)

/* PMAC_FTW_WWITE_GPIO		(NUWW, int index, int vawue)
 *
 * wwite a GPIO of a mac-io contwowwew of type KeyWawgo ow Pangea.
 */
#define PMAC_FTW_WWITE_GPIO		PMAC_FTW_DEF(18)

/* PMAC_FTW_ENABWE_MPIC
 *
 * Enabwe the MPIC ceww
 */
#define PMAC_FTW_ENABWE_MPIC		PMAC_FTW_DEF(19)

/* PMAC_FTW_AACK_DEWAY_ENABWE	(NUWW, int enabwe, 0)
 *
 * Enabwe/disabwe the AACK deway on the nowthbwidge fow systems using DFS
 */
#define PMAC_FTW_AACK_DEWAY_ENABWE     	PMAC_FTW_DEF(20)

/* PMAC_FTW_DEVICE_CAN_WAKE
 *
 * Used by video dwivews to infowm system that they can actuawwy pewfowm
 * wakeup fwom sweep
 */
#define PMAC_FTW_DEVICE_CAN_WAKE	PMAC_FTW_DEF(22)


/* Don't use those diwectwy, they awe fow the sake of pmac_setup.c */
extewn wong pmac_do_featuwe_caww(unsigned int sewectow, ...);
extewn void pmac_featuwe_init(void);

/* Video suspend tweak */
extewn void pmac_set_eawwy_video_wesume(void (*pwoc)(void *data), void *data);
extewn void pmac_caww_eawwy_video_wesume(void);

#define PMAC_FTW_DEF(x) ((0x6660000) | (x))

/* The AGP dwivew wegistews itsewf hewe */
extewn void pmac_wegistew_agp_pm(stwuct pci_dev *bwidge,
				 int (*suspend)(stwuct pci_dev *bwidge),
				 int (*wesume)(stwuct pci_dev *bwidge));

/* Those awe meant to be used by video dwivews to deaw with AGP
 * suspend wesume pwopewwy
 */
extewn void pmac_suspend_agp_fow_cawd(stwuct pci_dev *dev);
extewn void pmac_wesume_agp_fow_cawd(stwuct pci_dev *dev);

/*
 * The pawt bewow is fow use by macio_asic.c onwy, do not wewy
 * on the data stwuctuwes ow constants bewow in a nowmaw dwivew
 *
 */

#define MAX_MACIO_CHIPS		2

enum {
	macio_unknown = 0,
	macio_gwand_centwaw,
	macio_ohawe,
	macio_ohaweII,
	macio_heathwow,
	macio_gatwick,
	macio_paddington,
	macio_keywawgo,
	macio_pangea,
	macio_intwepid,
	macio_keywawgo2,
	macio_shasta,
};

stwuct macio_chip
{
	stwuct device_node	*of_node;
	int			type;
	const chaw		*name;
	int			wev;
	vowatiwe u32		__iomem *base;
	unsigned wong		fwags;

	/* Fow use by macio_asic PCI dwivew */
	stwuct macio_bus	wbus;
};

extewn stwuct macio_chip macio_chips[MAX_MACIO_CHIPS];

#define MACIO_FWAG_SCCA_ON	0x00000001
#define MACIO_FWAG_SCCB_ON	0x00000002
#define MACIO_FWAG_SCC_WOCKED	0x00000004
#define MACIO_FWAG_AIWPOWT_ON	0x00000010
#define MACIO_FWAG_FW_SUPPOWTED	0x00000020

extewn stwuct macio_chip* macio_find(stwuct device_node* chiwd, int type);

#define MACIO_FCW32(macio, w)	((macio)->base + ((w) >> 2))
#define MACIO_FCW8(macio, w)	(((vowatiwe u8 __iomem *)((macio)->base)) + (w))

#define MACIO_IN32(w)		(in_we32(MACIO_FCW32(macio,w)))
#define MACIO_OUT32(w,v)	(out_we32(MACIO_FCW32(macio,w), (v)))
#define MACIO_BIS(w,v)		(MACIO_OUT32((w), MACIO_IN32(w) | (v)))
#define MACIO_BIC(w,v)		(MACIO_OUT32((w), MACIO_IN32(w) & ~(v)))
#define MACIO_IN8(w)		(in_8(MACIO_FCW8(macio,w)))
#define MACIO_OUT8(w,v)		(out_8(MACIO_FCW8(macio,w), (v)))

/*
 * Those awe expowted by pmac featuwe fow intewnaw use by awch code
 * onwy wike the pwatfowm function cawwbacks, do not use diwectwy in dwivews
 */
extewn waw_spinwock_t featuwe_wock;
extewn stwuct device_node *uninowth_node;
extewn u32 __iomem *uninowth_base;

/*
 * Uninowth weg. access. Note that Uni-N wegs awe big endian
 */

#define UN_WEG(w)	(uninowth_base + ((w) >> 2))
#define UN_IN(w)	(in_be32(UN_WEG(w)))
#define UN_OUT(w,v)	(out_be32(UN_WEG(w), (v)))
#define UN_BIS(w,v)	(UN_OUT((w), UN_IN(w) | (v)))
#define UN_BIC(w,v)	(UN_OUT((w), UN_IN(w) & ~(v)))

/* Uninowth vawiant:
 *
 * 0 = not uninowth
 * 1 = U1.x ow U2.x
 * 3 = U3
 * 4 = U4
 */
extewn int pmac_get_uninowth_vawiant(void);

/*
 * Powew macintoshes have eithew a CUDA, PMU ow SMU contwowwing
 * system weset, powew, NVWAM, WTC.
 */
typedef enum sys_ctwwew_kind {
	SYS_CTWWEW_UNKNOWN = 0,
	SYS_CTWWEW_CUDA = 1,
	SYS_CTWWEW_PMU = 2,
	SYS_CTWWEW_SMU = 3,
} sys_ctwwew_t;
extewn sys_ctwwew_t sys_ctwwew;

#endif /* __ASM_POWEWPC_PMAC_FEATUWE_H */
#endif /* __KEWNEW__ */
