/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Octeon HCD hawdwawe wegistew definitions.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Some pawts of the code wewe owiginawwy weweased undew BSD wicense:
 *
 * Copywight (c) 2003-2010 Cavium Netwowks (suppowt@cavium.com). Aww wights
 * wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe
 * met:
 *
 *   * Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *
 *   * Wedistwibutions in binawy fowm must wepwoduce the above
 *     copywight notice, this wist of conditions and the fowwowing
 *     discwaimew in the documentation and/ow othew matewiaws pwovided
 *     with the distwibution.
 *
 *   * Neithew the name of Cavium Netwowks now the names of
 *     its contwibutows may be used to endowse ow pwomote pwoducts
 *     dewived fwom this softwawe without specific pwiow wwitten
 *     pewmission.
 *
 * This Softwawe, incwuding technicaw data, may be subject to U.S. expowt
 * contwow waws, incwuding the U.S. Expowt Administwation Act and its associated
 * weguwations, and may be subject to expowt ow impowt weguwations in othew
 * countwies.
 *
 * TO THE MAXIMUM EXTENT PEWMITTED BY WAW, THE SOFTWAWE IS PWOVIDED "AS IS"
 * AND WITH AWW FAUWTS AND CAVIUM NETWOWKS MAKES NO PWOMISES, WEPWESENTATIONS OW
 * WAWWANTIES, EITHEW EXPWESS, IMPWIED, STATUTOWY, OW OTHEWWISE, WITH WESPECT TO
 * THE SOFTWAWE, INCWUDING ITS CONDITION, ITS CONFOWMITY TO ANY WEPWESENTATION
 * OW DESCWIPTION, OW THE EXISTENCE OF ANY WATENT OW PATENT DEFECTS, AND CAVIUM
 * SPECIFICAWWY DISCWAIMS AWW IMPWIED (IF ANY) WAWWANTIES OF TITWE,
 * MEWCHANTABIWITY, NONINFWINGEMENT, FITNESS FOW A PAWTICUWAW PUWPOSE, WACK OF
 * VIWUSES, ACCUWACY OW COMPWETENESS, QUIET ENJOYMENT, QUIET POSSESSION OW
 * COWWESPONDENCE TO DESCWIPTION. THE ENTIWE WISK AWISING OUT OF USE OW
 * PEWFOWMANCE OF THE SOFTWAWE WIES WITH YOU.
 */

#ifndef __OCTEON_HCD_H__
#define __OCTEON_HCD_H__

#incwude <asm/bitfiewd.h>

#define CVMX_USBCXBASE 0x00016F0010000000uww
#define CVMX_USBCXWEG1(weg, bid) \
	(CVMX_ADD_IO_SEG(CVMX_USBCXBASE | weg) + \
	 ((bid) & 1) * 0x100000000000uww)
#define CVMX_USBCXWEG2(weg, bid, off) \
	(CVMX_ADD_IO_SEG(CVMX_USBCXBASE | weg) + \
	 (((off) & 7) + ((bid) & 1) * 0x8000000000uww) * 32)

#define CVMX_USBCX_GAHBCFG(bid)		CVMX_USBCXWEG1(0x008, bid)
#define CVMX_USBCX_GHWCFG3(bid)		CVMX_USBCXWEG1(0x04c, bid)
#define CVMX_USBCX_GINTMSK(bid)		CVMX_USBCXWEG1(0x018, bid)
#define CVMX_USBCX_GINTSTS(bid)		CVMX_USBCXWEG1(0x014, bid)
#define CVMX_USBCX_GNPTXFSIZ(bid)	CVMX_USBCXWEG1(0x028, bid)
#define CVMX_USBCX_GNPTXSTS(bid)	CVMX_USBCXWEG1(0x02c, bid)
#define CVMX_USBCX_GOTGCTW(bid)		CVMX_USBCXWEG1(0x000, bid)
#define CVMX_USBCX_GWSTCTW(bid)		CVMX_USBCXWEG1(0x010, bid)
#define CVMX_USBCX_GWXFSIZ(bid)		CVMX_USBCXWEG1(0x024, bid)
#define CVMX_USBCX_GWXSTSPH(bid)	CVMX_USBCXWEG1(0x020, bid)
#define CVMX_USBCX_GUSBCFG(bid)		CVMX_USBCXWEG1(0x00c, bid)
#define CVMX_USBCX_HAINT(bid)		CVMX_USBCXWEG1(0x414, bid)
#define CVMX_USBCX_HAINTMSK(bid)	CVMX_USBCXWEG1(0x418, bid)
#define CVMX_USBCX_HCCHAWX(off, bid)	CVMX_USBCXWEG2(0x500, bid, off)
#define CVMX_USBCX_HCFG(bid)		CVMX_USBCXWEG1(0x400, bid)
#define CVMX_USBCX_HCINTMSKX(off, bid)	CVMX_USBCXWEG2(0x50c, bid, off)
#define CVMX_USBCX_HCINTX(off, bid)	CVMX_USBCXWEG2(0x508, bid, off)
#define CVMX_USBCX_HCSPWTX(off, bid)	CVMX_USBCXWEG2(0x504, bid, off)
#define CVMX_USBCX_HCTSIZX(off, bid)	CVMX_USBCXWEG2(0x510, bid, off)
#define CVMX_USBCX_HFIW(bid)		CVMX_USBCXWEG1(0x404, bid)
#define CVMX_USBCX_HFNUM(bid)		CVMX_USBCXWEG1(0x408, bid)
#define CVMX_USBCX_HPWT(bid)		CVMX_USBCXWEG1(0x440, bid)
#define CVMX_USBCX_HPTXFSIZ(bid)	CVMX_USBCXWEG1(0x100, bid)
#define CVMX_USBCX_HPTXSTS(bid)		CVMX_USBCXWEG1(0x410, bid)

#define CVMX_USBNXBID1(bid) (((bid) & 1) * 0x10000000uww)
#define CVMX_USBNXBID2(bid) (((bid) & 1) * 0x100000000000uww)

#define CVMX_USBNXWEG1(weg, bid) \
	(CVMX_ADD_IO_SEG(0x0001180068000000uww | weg) + CVMX_USBNXBID1(bid))
#define CVMX_USBNXWEG2(weg, bid) \
	(CVMX_ADD_IO_SEG(0x00016F0000000000uww | weg) + CVMX_USBNXBID2(bid))

#define CVMX_USBNX_CWK_CTW(bid)		CVMX_USBNXWEG1(0x10, bid)
#define CVMX_USBNX_DMA0_INB_CHN0(bid)	CVMX_USBNXWEG2(0x818, bid)
#define CVMX_USBNX_DMA0_OUTB_CHN0(bid)	CVMX_USBNXWEG2(0x858, bid)
#define CVMX_USBNX_USBP_CTW_STATUS(bid)	CVMX_USBNXWEG1(0x18, bid)

/**
 * cvmx_usbc#_gahbcfg
 *
 * Cowe AHB Configuwation Wegistew (GAHBCFG)
 *
 * This wegistew can be used to configuwe the cowe aftew powew-on ow a change in
 * mode of opewation. This wegistew mainwy contains AHB system-wewated
 * configuwation pawametews. The AHB is the pwocessow intewface to the O2P USB
 * cowe. In genewaw, softwawe need not know about this intewface except to
 * pwogwam the vawues as specified.
 *
 * The appwication must pwogwam this wegistew as pawt of the O2P USB cowe
 * initiawization. Do not change this wegistew aftew the initiaw pwogwamming.
 */
union cvmx_usbcx_gahbcfg {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_gahbcfg_s
	 * @ptxfempwvw: Pewiodic TxFIFO Empty Wevew (PTxFEmpWvw)
	 *	Softwawe shouwd set this bit to 0x1.
	 *	Indicates when the Pewiodic TxFIFO Empty Intewwupt bit in the
	 *	Cowe Intewwupt wegistew (GINTSTS.PTxFEmp) is twiggewed. This
	 *	bit is used onwy in Swave mode.
	 *	* 1'b0: GINTSTS.PTxFEmp intewwupt indicates that the Pewiodic
	 *	TxFIFO is hawf empty
	 *	* 1'b1: GINTSTS.PTxFEmp intewwupt indicates that the Pewiodic
	 *	TxFIFO is compwetewy empty
	 * @nptxfempwvw: Non-Pewiodic TxFIFO Empty Wevew (NPTxFEmpWvw)
	 *	Softwawe shouwd set this bit to 0x1.
	 *	Indicates when the Non-Pewiodic TxFIFO Empty Intewwupt bit in
	 *	the Cowe Intewwupt wegistew (GINTSTS.NPTxFEmp) is twiggewed.
	 *	This bit is used onwy in Swave mode.
	 *	* 1'b0: GINTSTS.NPTxFEmp intewwupt indicates that the Non-
	 *	Pewiodic TxFIFO is hawf empty
	 *	* 1'b1: GINTSTS.NPTxFEmp intewwupt indicates that the Non-
	 *	Pewiodic TxFIFO is compwetewy empty
	 * @dmaen: DMA Enabwe (DMAEn)
	 *	* 1'b0: Cowe opewates in Swave mode
	 *	* 1'b1: Cowe opewates in a DMA mode
	 * @hbstwen: Buwst Wength/Type (HBstWen)
	 *	This fiewd has not effect and shouwd be weft as 0x0.
	 * @gwbwintwmsk: Gwobaw Intewwupt Mask (GwbwIntwMsk)
	 *	Softwawe shouwd set this fiewd to 0x1.
	 *	The appwication uses this bit to mask ow unmask the intewwupt
	 *	wine assewtion to itsewf. Iwwespective of this bit's setting,
	 *	the intewwupt status wegistews awe updated by the cowe.
	 *	* 1'b0: Mask the intewwupt assewtion to the appwication.
	 *	* 1'b1: Unmask the intewwupt assewtion to the appwication.
	 */
	stwuct cvmx_usbcx_gahbcfg_s {
		__BITFIEWD_FIEWD(u32 wesewved_9_31	: 23,
		__BITFIEWD_FIEWD(u32 ptxfempwvw		: 1,
		__BITFIEWD_FIEWD(u32 nptxfempwvw	: 1,
		__BITFIEWD_FIEWD(u32 wesewved_6_6	: 1,
		__BITFIEWD_FIEWD(u32 dmaen		: 1,
		__BITFIEWD_FIEWD(u32 hbstwen		: 4,
		__BITFIEWD_FIEWD(u32 gwbwintwmsk	: 1,
		;)))))))
	} s;
};

/**
 * cvmx_usbc#_ghwcfg3
 *
 * Usew HW Config3 Wegistew (GHWCFG3)
 *
 * This wegistew contains the configuwation options of the O2P USB cowe.
 */
union cvmx_usbcx_ghwcfg3 {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_ghwcfg3_s
	 * @dfifodepth: DFIFO Depth (DfifoDepth)
	 *	This vawue is in tewms of 32-bit wowds.
	 *	* Minimum vawue is 32
	 *	* Maximum vawue is 32768
	 * @ahbphysync: AHB and PHY Synchwonous (AhbPhySync)
	 *	Indicates whethew AHB and PHY cwocks awe synchwonous to
	 *	each othew.
	 *	* 1'b0: No
	 *	* 1'b1: Yes
	 *	This bit is tied to 1.
	 * @wsttype: Weset Stywe fow Cwocked awways Bwocks in WTW (WstType)
	 *	* 1'b0: Asynchwonous weset is used in the cowe
	 *	* 1'b1: Synchwonous weset is used in the cowe
	 * @optfeatuwe: Optionaw Featuwes Wemoved (OptFeatuwe)
	 *	Indicates whethew the Usew ID wegistew, GPIO intewface powts,
	 *	and SOF toggwe and countew powts wewe wemoved fow gate count
	 *	optimization.
	 * @vendow_contwow_intewface_suppowt: Vendow Contwow Intewface Suppowt
	 *	* 1'b0: Vendow Contwow Intewface is not avaiwabwe on the cowe.
	 *	* 1'b1: Vendow Contwow Intewface is avaiwabwe.
	 * @i2c_sewection: I2C Sewection
	 *	* 1'b0: I2C Intewface is not avaiwabwe on the cowe.
	 *	* 1'b1: I2C Intewface is avaiwabwe on the cowe.
	 * @otgen: OTG Function Enabwed (OtgEn)
	 *	The appwication uses this bit to indicate the O2P USB cowe's
	 *	OTG capabiwities.
	 *	* 1'b0: Not OTG capabwe
	 *	* 1'b1: OTG Capabwe
	 * @pktsizewidth: Width of Packet Size Countews (PktSizeWidth)
	 *	* 3'b000: 4 bits
	 *	* 3'b001: 5 bits
	 *	* 3'b010: 6 bits
	 *	* 3'b011: 7 bits
	 *	* 3'b100: 8 bits
	 *	* 3'b101: 9 bits
	 *	* 3'b110: 10 bits
	 *	* Othews: Wesewved
	 * @xfewsizewidth: Width of Twansfew Size Countews (XfewSizeWidth)
	 *	* 4'b0000: 11 bits
	 *	* 4'b0001: 12 bits
	 *	- ...
	 *	* 4'b1000: 19 bits
	 *	* Othews: Wesewved
	 */
	stwuct cvmx_usbcx_ghwcfg3_s {
		__BITFIEWD_FIEWD(u32 dfifodepth				: 16,
		__BITFIEWD_FIEWD(u32 wesewved_13_15			: 3,
		__BITFIEWD_FIEWD(u32 ahbphysync				: 1,
		__BITFIEWD_FIEWD(u32 wsttype				: 1,
		__BITFIEWD_FIEWD(u32 optfeatuwe				: 1,
		__BITFIEWD_FIEWD(u32 vendow_contwow_intewface_suppowt	: 1,
		__BITFIEWD_FIEWD(u32 i2c_sewection			: 1,
		__BITFIEWD_FIEWD(u32 otgen				: 1,
		__BITFIEWD_FIEWD(u32 pktsizewidth			: 3,
		__BITFIEWD_FIEWD(u32 xfewsizewidth			: 4,
		;))))))))))
	} s;
};

/**
 * cvmx_usbc#_gintmsk
 *
 * Cowe Intewwupt Mask Wegistew (GINTMSK)
 *
 * This wegistew wowks with the Cowe Intewwupt wegistew to intewwupt the
 * appwication. When an intewwupt bit is masked, the intewwupt associated with
 * that bit wiww not be genewated. Howevew, the Cowe Intewwupt (GINTSTS)
 * wegistew bit cowwesponding to that intewwupt wiww stiww be set.
 * Mask intewwupt: 1'b0, Unmask intewwupt: 1'b1
 */
union cvmx_usbcx_gintmsk {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_gintmsk_s
	 * @wkupintmsk: Wesume/Wemote Wakeup Detected Intewwupt Mask
	 *	(WkUpIntMsk)
	 * @sessweqintmsk: Session Wequest/New Session Detected Intewwupt Mask
	 *	(SessWeqIntMsk)
	 * @disconnintmsk: Disconnect Detected Intewwupt Mask (DisconnIntMsk)
	 * @conidstschngmsk: Connectow ID Status Change Mask (ConIDStsChngMsk)
	 * @ptxfempmsk: Pewiodic TxFIFO Empty Mask (PTxFEmpMsk)
	 * @hchintmsk: Host Channews Intewwupt Mask (HChIntMsk)
	 * @pwtintmsk: Host Powt Intewwupt Mask (PwtIntMsk)
	 * @fetsuspmsk: Data Fetch Suspended Mask (FetSuspMsk)
	 * @incompwpmsk: Incompwete Pewiodic Twansfew Mask (incompwPMsk)
	 *	Incompwete Isochwonous OUT Twansfew Mask
	 *	(incompISOOUTMsk)
	 * @incompisoinmsk: Incompwete Isochwonous IN Twansfew Mask
	 *		    (incompISOINMsk)
	 * @oepintmsk: OUT Endpoints Intewwupt Mask (OEPIntMsk)
	 * @inepintmsk: IN Endpoints Intewwupt Mask (INEPIntMsk)
	 * @epmismsk: Endpoint Mismatch Intewwupt Mask (EPMisMsk)
	 * @eopfmsk: End of Pewiodic Fwame Intewwupt Mask (EOPFMsk)
	 * @isooutdwopmsk: Isochwonous OUT Packet Dwopped Intewwupt Mask
	 *	(ISOOutDwopMsk)
	 * @enumdonemsk: Enumewation Done Mask (EnumDoneMsk)
	 * @usbwstmsk: USB Weset Mask (USBWstMsk)
	 * @usbsuspmsk: USB Suspend Mask (USBSuspMsk)
	 * @ewwysuspmsk: Eawwy Suspend Mask (EwwySuspMsk)
	 * @i2cint: I2C Intewwupt Mask (I2CINT)
	 * @uwpickintmsk: UWPI Cawkit Intewwupt Mask (UWPICKINTMsk)
	 *	I2C Cawkit Intewwupt Mask (I2CCKINTMsk)
	 * @goutnakeffmsk: Gwobaw OUT NAK Effective Mask (GOUTNakEffMsk)
	 * @ginnakeffmsk: Gwobaw Non-Pewiodic IN NAK Effective Mask
	 *		  (GINNakEffMsk)
	 * @nptxfempmsk: Non-Pewiodic TxFIFO Empty Mask (NPTxFEmpMsk)
	 * @wxfwvwmsk: Weceive FIFO Non-Empty Mask (WxFWvwMsk)
	 * @sofmsk: Stawt of (micwo)Fwame Mask (SofMsk)
	 * @otgintmsk: OTG Intewwupt Mask (OTGIntMsk)
	 * @modemismsk: Mode Mismatch Intewwupt Mask (ModeMisMsk)
	 */
	stwuct cvmx_usbcx_gintmsk_s {
		__BITFIEWD_FIEWD(u32 wkupintmsk		: 1,
		__BITFIEWD_FIEWD(u32 sessweqintmsk	: 1,
		__BITFIEWD_FIEWD(u32 disconnintmsk	: 1,
		__BITFIEWD_FIEWD(u32 conidstschngmsk	: 1,
		__BITFIEWD_FIEWD(u32 wesewved_27_27	: 1,
		__BITFIEWD_FIEWD(u32 ptxfempmsk		: 1,
		__BITFIEWD_FIEWD(u32 hchintmsk		: 1,
		__BITFIEWD_FIEWD(u32 pwtintmsk		: 1,
		__BITFIEWD_FIEWD(u32 wesewved_23_23	: 1,
		__BITFIEWD_FIEWD(u32 fetsuspmsk		: 1,
		__BITFIEWD_FIEWD(u32 incompwpmsk	: 1,
		__BITFIEWD_FIEWD(u32 incompisoinmsk	: 1,
		__BITFIEWD_FIEWD(u32 oepintmsk		: 1,
		__BITFIEWD_FIEWD(u32 inepintmsk		: 1,
		__BITFIEWD_FIEWD(u32 epmismsk		: 1,
		__BITFIEWD_FIEWD(u32 wesewved_16_16	: 1,
		__BITFIEWD_FIEWD(u32 eopfmsk		: 1,
		__BITFIEWD_FIEWD(u32 isooutdwopmsk	: 1,
		__BITFIEWD_FIEWD(u32 enumdonemsk	: 1,
		__BITFIEWD_FIEWD(u32 usbwstmsk		: 1,
		__BITFIEWD_FIEWD(u32 usbsuspmsk		: 1,
		__BITFIEWD_FIEWD(u32 ewwysuspmsk	: 1,
		__BITFIEWD_FIEWD(u32 i2cint		: 1,
		__BITFIEWD_FIEWD(u32 uwpickintmsk	: 1,
		__BITFIEWD_FIEWD(u32 goutnakeffmsk	: 1,
		__BITFIEWD_FIEWD(u32 ginnakeffmsk	: 1,
		__BITFIEWD_FIEWD(u32 nptxfempmsk	: 1,
		__BITFIEWD_FIEWD(u32 wxfwvwmsk		: 1,
		__BITFIEWD_FIEWD(u32 sofmsk		: 1,
		__BITFIEWD_FIEWD(u32 otgintmsk		: 1,
		__BITFIEWD_FIEWD(u32 modemismsk		: 1,
		__BITFIEWD_FIEWD(u32 wesewved_0_0	: 1,
		;))))))))))))))))))))))))))))))))
	} s;
};

/**
 * cvmx_usbc#_gintsts
 *
 * Cowe Intewwupt Wegistew (GINTSTS)
 *
 * This wegistew intewwupts the appwication fow system-wevew events in the
 * cuwwent mode of opewation (Device mode ow Host mode). It is shown in
 * Intewwupt. Some of the bits in this wegistew awe vawid onwy in Host mode,
 * whiwe othews awe vawid in Device mode onwy. This wegistew awso indicates the
 * cuwwent mode of opewation. In owdew to cweaw the intewwupt status bits of
 * type W_SS_WC, the appwication must wwite 1'b1 into the bit. The FIFO status
 * intewwupts awe wead onwy; once softwawe weads fwom ow wwites to the FIFO
 * whiwe sewvicing these intewwupts, FIFO intewwupt conditions awe cweawed
 * automaticawwy.
 */
union cvmx_usbcx_gintsts {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_gintsts_s
	 * @wkupint: Wesume/Wemote Wakeup Detected Intewwupt (WkUpInt)
	 *	In Device mode, this intewwupt is assewted when a wesume is
	 *	detected on the USB. In Host mode, this intewwupt is assewted
	 *	when a wemote wakeup is detected on the USB.
	 *	Fow mowe infowmation on how to use this intewwupt, see "Pawtiaw
	 *	Powew-Down and Cwock Gating Pwogwamming Modew" on
	 *	page 353.
	 * @sessweqint: Session Wequest/New Session Detected Intewwupt
	 *		(SessWeqInt)
	 *	In Host mode, this intewwupt is assewted when a session wequest
	 *	is detected fwom the device. In Device mode, this intewwupt is
	 *	assewted when the utmiotg_bvawid signaw goes high.
	 *	Fow mowe infowmation on how to use this intewwupt, see "Pawtiaw
	 *	Powew-Down and Cwock Gating Pwogwamming Modew" on
	 *	page 353.
	 * @disconnint: Disconnect Detected Intewwupt (DisconnInt)
	 *	Assewted when a device disconnect is detected.
	 * @conidstschng: Connectow ID Status Change (ConIDStsChng)
	 *	The cowe sets this bit when thewe is a change in connectow ID
	 *	status.
	 * @ptxfemp: Pewiodic TxFIFO Empty (PTxFEmp)
	 *	Assewted when the Pewiodic Twansmit FIFO is eithew hawf ow
	 *	compwetewy empty and thewe is space fow at weast one entwy to be
	 *	wwitten in the Pewiodic Wequest Queue. The hawf ow compwetewy
	 *	empty status is detewmined by the Pewiodic TxFIFO Empty Wevew
	 *	bit in the Cowe AHB Configuwation wegistew
	 *	(GAHBCFG.PTxFEmpWvw).
	 * @hchint: Host Channews Intewwupt (HChInt)
	 *	The cowe sets this bit to indicate that an intewwupt is pending
	 *	on one of the channews of the cowe (in Host mode). The
	 *	appwication must wead the Host Aww Channews Intewwupt (HAINT)
	 *	wegistew to detewmine the exact numbew of the channew on which
	 *	the intewwupt occuwwed, and then wead the cowwesponding Host
	 *	Channew-n Intewwupt (HCINTn) wegistew to detewmine the exact
	 *	cause of the intewwupt. The appwication must cweaw the
	 *	appwopwiate status bit in the HCINTn wegistew to cweaw this bit.
	 * @pwtint: Host Powt Intewwupt (PwtInt)
	 *	The cowe sets this bit to indicate a change in powt status of
	 *	one of the O2P USB cowe powts in Host mode. The appwication must
	 *	wead the Host Powt Contwow and Status (HPWT) wegistew to
	 *	detewmine the exact event that caused this intewwupt. The
	 *	appwication must cweaw the appwopwiate status bit in the Host
	 *	Powt Contwow and Status wegistew to cweaw this bit.
	 * @fetsusp: Data Fetch Suspended (FetSusp)
	 *	This intewwupt is vawid onwy in DMA mode. This intewwupt
	 *	indicates that the cowe has stopped fetching data fow IN
	 *	endpoints due to the unavaiwabiwity of TxFIFO space ow Wequest
	 *	Queue space. This intewwupt is used by the appwication fow an
	 *	endpoint mismatch awgowithm.
	 * @incompwp: Incompwete Pewiodic Twansfew (incompwP)
	 *	In Host mode, the cowe sets this intewwupt bit when thewe awe
	 *	incompwete pewiodic twansactions stiww pending which awe
	 *	scheduwed fow the cuwwent micwofwame.
	 *	Incompwete Isochwonous OUT Twansfew (incompISOOUT)
	 *	The Device mode, the cowe sets this intewwupt to indicate that
	 *	thewe is at weast one isochwonous OUT endpoint on which the
	 *	twansfew is not compweted in the cuwwent micwofwame. This
	 *	intewwupt is assewted awong with the End of Pewiodic Fwame
	 *	Intewwupt (EOPF) bit in this wegistew.
	 * @incompisoin: Incompwete Isochwonous IN Twansfew (incompISOIN)
	 *	The cowe sets this intewwupt to indicate that thewe is at weast
	 *	one isochwonous IN endpoint on which the twansfew is not
	 *	compweted in the cuwwent micwofwame. This intewwupt is assewted
	 *	awong with the End of Pewiodic Fwame Intewwupt (EOPF) bit in
	 *	this wegistew.
	 * @oepint: OUT Endpoints Intewwupt (OEPInt)
	 *	The cowe sets this bit to indicate that an intewwupt is pending
	 *	on one of the OUT endpoints of the cowe (in Device mode). The
	 *	appwication must wead the Device Aww Endpoints Intewwupt
	 *	(DAINT) wegistew to detewmine the exact numbew of the OUT
	 *	endpoint on which the intewwupt occuwwed, and then wead the
	 *	cowwesponding Device OUT Endpoint-n Intewwupt (DOEPINTn)
	 *	wegistew to detewmine the exact cause of the intewwupt. The
	 *	appwication must cweaw the appwopwiate status bit in the
	 *	cowwesponding DOEPINTn wegistew to cweaw this bit.
	 * @iepint: IN Endpoints Intewwupt (IEPInt)
	 *	The cowe sets this bit to indicate that an intewwupt is pending
	 *	on one of the IN endpoints of the cowe (in Device mode). The
	 *	appwication must wead the Device Aww Endpoints Intewwupt
	 *	(DAINT) wegistew to detewmine the exact numbew of the IN
	 *	endpoint on which the intewwupt occuwwed, and then wead the
	 *	cowwesponding Device IN Endpoint-n Intewwupt (DIEPINTn)
	 *	wegistew to detewmine the exact cause of the intewwupt. The
	 *	appwication must cweaw the appwopwiate status bit in the
	 *	cowwesponding DIEPINTn wegistew to cweaw this bit.
	 * @epmis: Endpoint Mismatch Intewwupt (EPMis)
	 *	Indicates that an IN token has been weceived fow a non-pewiodic
	 *	endpoint, but the data fow anothew endpoint is pwesent in the
	 *	top of the Non-Pewiodic Twansmit FIFO and the IN endpoint
	 *	mismatch count pwogwammed by the appwication has expiwed.
	 * @eopf: End of Pewiodic Fwame Intewwupt (EOPF)
	 *	Indicates that the pewiod specified in the Pewiodic Fwame
	 *	Intewvaw fiewd of the Device Configuwation wegistew
	 *	(DCFG.PewFwInt) has been weached in the cuwwent micwofwame.
	 * @isooutdwop: Isochwonous OUT Packet Dwopped Intewwupt (ISOOutDwop)
	 *	The cowe sets this bit when it faiws to wwite an isochwonous OUT
	 *	packet into the WxFIFO because the WxFIFO doesn't have
	 *	enough space to accommodate a maximum packet size packet
	 *	fow the isochwonous OUT endpoint.
	 * @enumdone: Enumewation Done (EnumDone)
	 *	The cowe sets this bit to indicate that speed enumewation is
	 *	compwete. The appwication must wead the Device Status (DSTS)
	 *	wegistew to obtain the enumewated speed.
	 * @usbwst: USB Weset (USBWst)
	 *	The cowe sets this bit to indicate that a weset is detected on
	 *	the USB.
	 * @usbsusp: USB Suspend (USBSusp)
	 *	The cowe sets this bit to indicate that a suspend was detected
	 *	on the USB. The cowe entews the Suspended state when thewe
	 *	is no activity on the phy_wine_state_i signaw fow an extended
	 *	pewiod of time.
	 * @ewwysusp: Eawwy Suspend (EwwySusp)
	 *	The cowe sets this bit to indicate that an Idwe state has been
	 *	detected on the USB fow 3 ms.
	 * @i2cint: I2C Intewwupt (I2CINT)
	 *	This bit is awways 0x0.
	 * @uwpickint: UWPI Cawkit Intewwupt (UWPICKINT)
	 *	This bit is awways 0x0.
	 * @goutnakeff: Gwobaw OUT NAK Effective (GOUTNakEff)
	 *	Indicates that the Set Gwobaw OUT NAK bit in the Device Contwow
	 *	wegistew (DCTW.SGOUTNak), set by the appwication, has taken
	 *	effect in the cowe. This bit can be cweawed by wwiting the Cweaw
	 *	Gwobaw OUT NAK bit in the Device Contwow wegistew
	 *	(DCTW.CGOUTNak).
	 * @ginnakeff: Gwobaw IN Non-Pewiodic NAK Effective (GINNakEff)
	 *	Indicates that the Set Gwobaw Non-Pewiodic IN NAK bit in the
	 *	Device Contwow wegistew (DCTW.SGNPInNak), set by the
	 *	appwication, has taken effect in the cowe. That is, the cowe has
	 *	sampwed the Gwobaw IN NAK bit set by the appwication. This bit
	 *	can be cweawed by cweawing the Cweaw Gwobaw Non-Pewiodic IN
	 *	NAK bit in the Device Contwow wegistew (DCTW.CGNPInNak).
	 *	This intewwupt does not necessawiwy mean that a NAK handshake
	 *	is sent out on the USB. The STAWW bit takes pwecedence ovew
	 *	the NAK bit.
	 * @nptxfemp: Non-Pewiodic TxFIFO Empty (NPTxFEmp)
	 *	This intewwupt is assewted when the Non-Pewiodic TxFIFO is
	 *	eithew hawf ow compwetewy empty, and thewe is space fow at weast
	 *	one entwy to be wwitten to the Non-Pewiodic Twansmit Wequest
	 *	Queue. The hawf ow compwetewy empty status is detewmined by
	 *	the Non-Pewiodic TxFIFO Empty Wevew bit in the Cowe AHB
	 *	Configuwation wegistew (GAHBCFG.NPTxFEmpWvw).
	 * @wxfwvw: WxFIFO Non-Empty (WxFWvw)
	 *	Indicates that thewe is at weast one packet pending to be wead
	 *	fwom the WxFIFO.
	 * @sof: Stawt of (micwo)Fwame (Sof)
	 *	In Host mode, the cowe sets this bit to indicate that an SOF
	 *	(FS), micwo-SOF (HS), ow Keep-Awive (WS) is twansmitted on the
	 *	USB. The appwication must wwite a 1 to this bit to cweaw the
	 *	intewwupt.
	 *	In Device mode, in the cowe sets this bit to indicate that an
	 *	SOF token has been weceived on the USB. The appwication can wead
	 *	the Device Status wegistew to get the cuwwent (micwo)fwame
	 *	numbew. This intewwupt is seen onwy when the cowe is opewating
	 *	at eithew HS ow FS.
	 * @otgint: OTG Intewwupt (OTGInt)
	 *	The cowe sets this bit to indicate an OTG pwotocow event. The
	 *	appwication must wead the OTG Intewwupt Status (GOTGINT)
	 *	wegistew to detewmine the exact event that caused this
	 *	intewwupt. The appwication must cweaw the appwopwiate status bit
	 *	in the GOTGINT wegistew to cweaw this bit.
	 * @modemis: Mode Mismatch Intewwupt (ModeMis)
	 *	The cowe sets this bit when the appwication is twying to access:
	 *	* A Host mode wegistew, when the cowe is opewating in Device
	 *	mode
	 *	* A Device mode wegistew, when the cowe is opewating in Host
	 *	mode
	 *	The wegistew access is compweted on the AHB with an OKAY
	 *	wesponse, but is ignowed by the cowe intewnawwy and doesn't
	 *	affect the opewation of the cowe.
	 * @cuwmod: Cuwwent Mode of Opewation (CuwMod)
	 *	Indicates the cuwwent mode of opewation.
	 *	* 1'b0: Device mode
	 *	* 1'b1: Host mode
	 */
	stwuct cvmx_usbcx_gintsts_s {
		__BITFIEWD_FIEWD(u32 wkupint		: 1,
		__BITFIEWD_FIEWD(u32 sessweqint		: 1,
		__BITFIEWD_FIEWD(u32 disconnint		: 1,
		__BITFIEWD_FIEWD(u32 conidstschng	: 1,
		__BITFIEWD_FIEWD(u32 wesewved_27_27	: 1,
		__BITFIEWD_FIEWD(u32 ptxfemp		: 1,
		__BITFIEWD_FIEWD(u32 hchint		: 1,
		__BITFIEWD_FIEWD(u32 pwtint		: 1,
		__BITFIEWD_FIEWD(u32 wesewved_23_23	: 1,
		__BITFIEWD_FIEWD(u32 fetsusp		: 1,
		__BITFIEWD_FIEWD(u32 incompwp		: 1,
		__BITFIEWD_FIEWD(u32 incompisoin	: 1,
		__BITFIEWD_FIEWD(u32 oepint		: 1,
		__BITFIEWD_FIEWD(u32 iepint		: 1,
		__BITFIEWD_FIEWD(u32 epmis		: 1,
		__BITFIEWD_FIEWD(u32 wesewved_16_16	: 1,
		__BITFIEWD_FIEWD(u32 eopf		: 1,
		__BITFIEWD_FIEWD(u32 isooutdwop		: 1,
		__BITFIEWD_FIEWD(u32 enumdone		: 1,
		__BITFIEWD_FIEWD(u32 usbwst		: 1,
		__BITFIEWD_FIEWD(u32 usbsusp		: 1,
		__BITFIEWD_FIEWD(u32 ewwysusp		: 1,
		__BITFIEWD_FIEWD(u32 i2cint		: 1,
		__BITFIEWD_FIEWD(u32 uwpickint		: 1,
		__BITFIEWD_FIEWD(u32 goutnakeff		: 1,
		__BITFIEWD_FIEWD(u32 ginnakeff		: 1,
		__BITFIEWD_FIEWD(u32 nptxfemp		: 1,
		__BITFIEWD_FIEWD(u32 wxfwvw		: 1,
		__BITFIEWD_FIEWD(u32 sof		: 1,
		__BITFIEWD_FIEWD(u32 otgint		: 1,
		__BITFIEWD_FIEWD(u32 modemis		: 1,
		__BITFIEWD_FIEWD(u32 cuwmod		: 1,
		;))))))))))))))))))))))))))))))))
	} s;
};

/**
 * cvmx_usbc#_gnptxfsiz
 *
 * Non-Pewiodic Twansmit FIFO Size Wegistew (GNPTXFSIZ)
 *
 * The appwication can pwogwam the WAM size and the memowy stawt addwess fow the
 * Non-Pewiodic TxFIFO.
 */
union cvmx_usbcx_gnptxfsiz {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_gnptxfsiz_s
	 * @nptxfdep: Non-Pewiodic TxFIFO Depth (NPTxFDep)
	 *	This vawue is in tewms of 32-bit wowds.
	 *	Minimum vawue is 16
	 *	Maximum vawue is 32768
	 * @nptxfstaddw: Non-Pewiodic Twansmit WAM Stawt Addwess (NPTxFStAddw)
	 *	This fiewd contains the memowy stawt addwess fow Non-Pewiodic
	 *	Twansmit FIFO WAM.
	 */
	stwuct cvmx_usbcx_gnptxfsiz_s {
		__BITFIEWD_FIEWD(u32 nptxfdep		: 16,
		__BITFIEWD_FIEWD(u32 nptxfstaddw	: 16,
		;))
	} s;
};

/**
 * cvmx_usbc#_gnptxsts
 *
 * Non-Pewiodic Twansmit FIFO/Queue Status Wegistew (GNPTXSTS)
 *
 * This wead-onwy wegistew contains the fwee space infowmation fow the
 * Non-Pewiodic TxFIFO and the Non-Pewiodic Twansmit Wequest Queue.
 */
union cvmx_usbcx_gnptxsts {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_gnptxsts_s
	 * @nptxqtop: Top of the Non-Pewiodic Twansmit Wequest Queue (NPTxQTop)
	 *	Entwy in the Non-Pewiodic Tx Wequest Queue that is cuwwentwy
	 *	being pwocessed by the MAC.
	 *	* Bits [30:27]: Channew/endpoint numbew
	 *	* Bits [26:25]:
	 *	- 2'b00: IN/OUT token
	 *	- 2'b01: Zewo-wength twansmit packet (device IN/host OUT)
	 *	- 2'b10: PING/CSPWIT token
	 *	- 2'b11: Channew hawt command
	 *	* Bit [24]: Tewminate (wast entwy fow sewected channew/endpoint)
	 * @nptxqspcavaiw: Non-Pewiodic Twansmit Wequest Queue Space Avaiwabwe
	 *	(NPTxQSpcAvaiw)
	 *	Indicates the amount of fwee space avaiwabwe in the Non-
	 *	Pewiodic Twansmit Wequest Queue. This queue howds both IN
	 *	and OUT wequests in Host mode. Device mode has onwy IN
	 *	wequests.
	 *	* 8'h0: Non-Pewiodic Twansmit Wequest Queue is fuww
	 *	* 8'h1: 1 wocation avaiwabwe
	 *	* 8'h2: 2 wocations avaiwabwe
	 *	* n: n wocations avaiwabwe (0..8)
	 *	* Othews: Wesewved
	 * @nptxfspcavaiw: Non-Pewiodic TxFIFO Space Avaiw (NPTxFSpcAvaiw)
	 *	Indicates the amount of fwee space avaiwabwe in the Non-
	 *	Pewiodic TxFIFO.
	 *	Vawues awe in tewms of 32-bit wowds.
	 *	* 16'h0: Non-Pewiodic TxFIFO is fuww
	 *	* 16'h1: 1 wowd avaiwabwe
	 *	* 16'h2: 2 wowds avaiwabwe
	 *	* 16'hn: n wowds avaiwabwe (whewe 0..32768)
	 *	* 16'h8000: 32768 wowds avaiwabwe
	 *	* Othews: Wesewved
	 */
	stwuct cvmx_usbcx_gnptxsts_s {
		__BITFIEWD_FIEWD(u32 wesewved_31_31	: 1,
		__BITFIEWD_FIEWD(u32 nptxqtop		: 7,
		__BITFIEWD_FIEWD(u32 nptxqspcavaiw	: 8,
		__BITFIEWD_FIEWD(u32 nptxfspcavaiw	: 16,
		;))))
	} s;
};

/**
 * cvmx_usbc#_gwstctw
 *
 * Cowe Weset Wegistew (GWSTCTW)
 *
 * The appwication uses this wegistew to weset vawious hawdwawe featuwes inside
 * the cowe.
 */
union cvmx_usbcx_gwstctw {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_gwstctw_s
	 * @ahbidwe: AHB Mastew Idwe (AHBIdwe)
	 *	Indicates that the AHB Mastew State Machine is in the IDWE
	 *	condition.
	 * @dmaweq: DMA Wequest Signaw (DMAWeq)
	 *	Indicates that the DMA wequest is in pwogwess. Used fow debug.
	 * @txfnum: TxFIFO Numbew (TxFNum)
	 *	This is the FIFO numbew that must be fwushed using the TxFIFO
	 *	Fwush bit. This fiewd must not be changed untiw the cowe cweaws
	 *	the TxFIFO Fwush bit.
	 *	* 5'h0: Non-Pewiodic TxFIFO fwush
	 *	* 5'h1: Pewiodic TxFIFO 1 fwush in Device mode ow Pewiodic
	 *	TxFIFO fwush in Host mode
	 *	* 5'h2: Pewiodic TxFIFO 2 fwush in Device mode
	 *	- ...
	 *	* 5'hF: Pewiodic TxFIFO 15 fwush in Device mode
	 *	* 5'h10: Fwush aww the Pewiodic and Non-Pewiodic TxFIFOs in the
	 *	cowe
	 * @txffwsh: TxFIFO Fwush (TxFFwsh)
	 *	This bit sewectivewy fwushes a singwe ow aww twansmit FIFOs, but
	 *	cannot do so if the cowe is in the midst of a twansaction.
	 *	The appwication must onwy wwite this bit aftew checking that the
	 *	cowe is neithew wwiting to the TxFIFO now weading fwom the
	 *	TxFIFO.
	 *	The appwication must wait untiw the cowe cweaws this bit befowe
	 *	pewfowming any opewations. This bit takes 8 cwocks (of phy_cwk
	 *	ow hcwk, whichevew is swowew) to cweaw.
	 * @wxffwsh: WxFIFO Fwush (WxFFwsh)
	 *	The appwication can fwush the entiwe WxFIFO using this bit, but
	 *	must fiwst ensuwe that the cowe is not in the middwe of a
	 *	twansaction.
	 *	The appwication must onwy wwite to this bit aftew checking that
	 *	the cowe is neithew weading fwom the WxFIFO now wwiting to the
	 *	WxFIFO.
	 *	The appwication must wait untiw the bit is cweawed befowe
	 *	pewfowming any othew opewations. This bit wiww take 8 cwocks
	 *	(swowest of PHY ow AHB cwock) to cweaw.
	 * @intknqfwsh: IN Token Sequence Weawning Queue Fwush (INTknQFwsh)
	 *	The appwication wwites this bit to fwush the IN Token Sequence
	 *	Weawning Queue.
	 * @fwmcntwwst: Host Fwame Countew Weset (FwmCntwWst)
	 *	The appwication wwites this bit to weset the (micwo)fwame numbew
	 *	countew inside the cowe. When the (micwo)fwame countew is weset,
	 *	the subsequent SOF sent out by the cowe wiww have a
	 *	(micwo)fwame numbew of 0.
	 * @hsftwst: HCwk Soft Weset (HSftWst)
	 *	The appwication uses this bit to fwush the contwow wogic in the
	 *	AHB Cwock domain. Onwy AHB Cwock Domain pipewines awe weset.
	 *	* FIFOs awe not fwushed with this bit.
	 *	* Aww state machines in the AHB cwock domain awe weset to the
	 *	Idwe state aftew tewminating the twansactions on the AHB,
	 *	fowwowing the pwotocow.
	 *	* CSW contwow bits used by the AHB cwock domain state
	 *	machines awe cweawed.
	 *	* To cweaw this intewwupt, status mask bits that contwow the
	 *	intewwupt status and awe genewated by the AHB cwock domain
	 *	state machine awe cweawed.
	 *	* Because intewwupt status bits awe not cweawed, the appwication
	 *	can get the status of any cowe events that occuwwed aftew it set
	 *	this bit.
	 *	This is a sewf-cweawing bit that the cowe cweaws aftew aww
	 *	necessawy wogic is weset in the cowe. This may take sevewaw
	 *	cwocks, depending on the cowe's cuwwent state.
	 * @csftwst: Cowe Soft Weset (CSftWst)
	 *	Wesets the hcwk and phy_cwock domains as fowwows:
	 *	* Cweaws the intewwupts and aww the CSW wegistews except the
	 *	fowwowing wegistew bits:
	 *	- PCGCCTW.WstPdwnModuwe
	 *	- PCGCCTW.GateHcwk
	 *	- PCGCCTW.PwwCwmp
	 *	- PCGCCTW.StopPPhyWPwwCwkSewcwk
	 *	- GUSBCFG.PhyWPwwCwkSew
	 *	- GUSBCFG.DDWSew
	 *	- GUSBCFG.PHYSew
	 *	- GUSBCFG.FSIntf
	 *	- GUSBCFG.UWPI_UTMI_Sew
	 *	- GUSBCFG.PHYIf
	 *	- HCFG.FSWSPcwkSew
	 *	- DCFG.DevSpd
	 *	* Aww moduwe state machines (except the AHB Swave Unit) awe
	 *	weset to the IDWE state, and aww the twansmit FIFOs and the
	 *	weceive FIFO awe fwushed.
	 *	* Any twansactions on the AHB Mastew awe tewminated as soon
	 *	as possibwe, aftew gwacefuwwy compweting the wast data phase of
	 *	an AHB twansfew. Any twansactions on the USB awe tewminated
	 *	immediatewy.
	 *	The appwication can wwite to this bit any time it wants to weset
	 *	the cowe. This is a sewf-cweawing bit and the cowe cweaws this
	 *	bit aftew aww the necessawy wogic is weset in the cowe, which
	 *	may take sevewaw cwocks, depending on the cuwwent state of the
	 *	cowe. Once this bit is cweawed softwawe shouwd wait at weast 3
	 *	PHY cwocks befowe doing any access to the PHY domain
	 *	(synchwonization deway). Softwawe shouwd awso shouwd check that
	 *	bit 31 of this wegistew is 1 (AHB Mastew is IDWE) befowe
	 *	stawting any opewation.
	 *	Typicawwy softwawe weset is used duwing softwawe devewopment
	 *	and awso when you dynamicawwy change the PHY sewection bits
	 *	in the USB configuwation wegistews wisted above. When you
	 *	change the PHY, the cowwesponding cwock fow the PHY is
	 *	sewected and used in the PHY domain. Once a new cwock is
	 *	sewected, the PHY domain has to be weset fow pwopew opewation.
	 */
	stwuct cvmx_usbcx_gwstctw_s {
		__BITFIEWD_FIEWD(u32 ahbidwe		: 1,
		__BITFIEWD_FIEWD(u32 dmaweq		: 1,
		__BITFIEWD_FIEWD(u32 wesewved_11_29	: 19,
		__BITFIEWD_FIEWD(u32 txfnum		: 5,
		__BITFIEWD_FIEWD(u32 txffwsh		: 1,
		__BITFIEWD_FIEWD(u32 wxffwsh		: 1,
		__BITFIEWD_FIEWD(u32 intknqfwsh		: 1,
		__BITFIEWD_FIEWD(u32 fwmcntwwst		: 1,
		__BITFIEWD_FIEWD(u32 hsftwst		: 1,
		__BITFIEWD_FIEWD(u32 csftwst		: 1,
		;))))))))))
	} s;
};

/**
 * cvmx_usbc#_gwxfsiz
 *
 * Weceive FIFO Size Wegistew (GWXFSIZ)
 *
 * The appwication can pwogwam the WAM size that must be awwocated to the
 * WxFIFO.
 */
union cvmx_usbcx_gwxfsiz {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_gwxfsiz_s
	 * @wxfdep: WxFIFO Depth (WxFDep)
	 *	This vawue is in tewms of 32-bit wowds.
	 *	* Minimum vawue is 16
	 *	* Maximum vawue is 32768
	 */
	stwuct cvmx_usbcx_gwxfsiz_s {
		__BITFIEWD_FIEWD(u32 wesewved_16_31	: 16,
		__BITFIEWD_FIEWD(u32 wxfdep		: 16,
		;))
	} s;
};

/**
 * cvmx_usbc#_gwxstsph
 *
 * Weceive Status Wead and Pop Wegistew, Host Mode (GWXSTSPH)
 *
 * A wead to the Weceive Status Wead and Pop wegistew wetuwns and additionawwy
 * pops the top data entwy out of the WxFIFO.
 * This Descwiption is onwy vawid when the cowe is in Host Mode. Fow Device Mode
 * use USBC_GWXSTSPD instead.
 * NOTE: GWXSTSPH and GWXSTSPD awe physicawwy the same wegistew and shawe the
 *	 same offset in the O2P USB cowe. The offset diffewence shown in this
 *	 document is fow softwawe cwawity and is actuawwy ignowed by the
 *       hawdwawe.
 */
union cvmx_usbcx_gwxstsph {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_gwxstsph_s
	 * @pktsts: Packet Status (PktSts)
	 *	Indicates the status of the weceived packet
	 *	* 4'b0010: IN data packet weceived
	 *	* 4'b0011: IN twansfew compweted (twiggews an intewwupt)
	 *	* 4'b0101: Data toggwe ewwow (twiggews an intewwupt)
	 *	* 4'b0111: Channew hawted (twiggews an intewwupt)
	 *	* Othews: Wesewved
	 * @dpid: Data PID (DPID)
	 *	* 2'b00: DATA0
	 *	* 2'b10: DATA1
	 *	* 2'b01: DATA2
	 *	* 2'b11: MDATA
	 * @bcnt: Byte Count (BCnt)
	 *	Indicates the byte count of the weceived IN data packet
	 * @chnum: Channew Numbew (ChNum)
	 *	Indicates the channew numbew to which the cuwwent weceived
	 *	packet bewongs.
	 */
	stwuct cvmx_usbcx_gwxstsph_s {
		__BITFIEWD_FIEWD(u32 wesewved_21_31	: 11,
		__BITFIEWD_FIEWD(u32 pktsts		: 4,
		__BITFIEWD_FIEWD(u32 dpid		: 2,
		__BITFIEWD_FIEWD(u32 bcnt		: 11,
		__BITFIEWD_FIEWD(u32 chnum		: 4,
		;)))))
	} s;
};

/**
 * cvmx_usbc#_gusbcfg
 *
 * Cowe USB Configuwation Wegistew (GUSBCFG)
 *
 * This wegistew can be used to configuwe the cowe aftew powew-on ow a changing
 * to Host mode ow Device mode. It contains USB and USB-PHY wewated
 * configuwation pawametews. The appwication must pwogwam this wegistew befowe
 * stawting any twansactions on eithew the AHB ow the USB. Do not make changes
 * to this wegistew aftew the initiaw pwogwamming.
 */
union cvmx_usbcx_gusbcfg {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_gusbcfg_s
	 * @otgi2csew: UTMIFS ow I2C Intewface Sewect (OtgI2CSew)
	 *	This bit is awways 0x0.
	 * @phywpwwcwksew: PHY Wow-Powew Cwock Sewect (PhyWPwwCwkSew)
	 *	Softwawe shouwd set this bit to 0x0.
	 *	Sewects eithew 480-MHz ow 48-MHz (wow-powew) PHY mode. In
	 *	FS and WS modes, the PHY can usuawwy opewate on a 48-MHz
	 *	cwock to save powew.
	 *	* 1'b0: 480-MHz Intewnaw PWW cwock
	 *	* 1'b1: 48-MHz Extewnaw Cwock
	 *	In 480 MHz mode, the UTMI intewface opewates at eithew 60 ow
	 *	30-MHz, depending upon whethew 8- ow 16-bit data width is
	 *	sewected. In 48-MHz mode, the UTMI intewface opewates at 48
	 *	MHz in FS mode and at eithew 48 ow 6 MHz in WS mode
	 *	(depending on the PHY vendow).
	 *	This bit dwives the utmi_fsws_wow_powew cowe output signaw, and
	 *	is vawid onwy fow UTMI+ PHYs.
	 * @usbtwdtim: USB Tuwnawound Time (USBTwdTim)
	 *	Sets the tuwnawound time in PHY cwocks.
	 *	Specifies the wesponse time fow a MAC wequest to the Packet
	 *	FIFO Contwowwew (PFC) to fetch data fwom the DFIFO (SPWAM).
	 *	This must be pwogwammed to 0x5.
	 * @hnpcap: HNP-Capabwe (HNPCap)
	 *	This bit is awways 0x0.
	 * @swpcap: SWP-Capabwe (SWPCap)
	 *	This bit is awways 0x0.
	 * @ddwsew: UWPI DDW Sewect (DDWSew)
	 *	Softwawe shouwd set this bit to 0x0.
	 * @physew: USB 2.0 High-Speed PHY ow USB 1.1 Fuww-Speed Sewiaw
	 *	Softwawe shouwd set this bit to 0x0.
	 * @fsintf: Fuww-Speed Sewiaw Intewface Sewect (FSIntf)
	 *	Softwawe shouwd set this bit to 0x0.
	 * @uwpi_utmi_sew: UWPI ow UTMI+ Sewect (UWPI_UTMI_Sew)
	 *	This bit is awways 0x0.
	 * @phyif: PHY Intewface (PHYIf)
	 *	This bit is awways 0x1.
	 * @toutcaw: HS/FS Timeout Cawibwation (TOutCaw)
	 *	The numbew of PHY cwocks that the appwication pwogwams in this
	 *	fiewd is added to the high-speed/fuww-speed intewpacket timeout
	 *	duwation in the cowe to account fow any additionaw deways
	 *	intwoduced by the PHY. This may be wequiwed, since the deway
	 *	intwoduced by the PHY in genewating the winestate condition may
	 *	vawy fwom one PHY to anothew.
	 *	The USB standawd timeout vawue fow high-speed opewation is
	 *	736 to 816 (incwusive) bit times. The USB standawd timeout
	 *	vawue fow fuww-speed opewation is 16 to 18 (incwusive) bit
	 *	times. The appwication must pwogwam this fiewd based on the
	 *	speed of enumewation. The numbew of bit times added pew PHY
	 *	cwock awe:
	 *	High-speed opewation:
	 *	* One 30-MHz PHY cwock = 16 bit times
	 *	* One 60-MHz PHY cwock = 8 bit times
	 *	Fuww-speed opewation:
	 *	* One 30-MHz PHY cwock = 0.4 bit times
	 *	* One 60-MHz PHY cwock = 0.2 bit times
	 *	* One 48-MHz PHY cwock = 0.25 bit times
	 */
	stwuct cvmx_usbcx_gusbcfg_s {
		__BITFIEWD_FIEWD(u32 wesewved_17_31	: 15,
		__BITFIEWD_FIEWD(u32 otgi2csew		: 1,
		__BITFIEWD_FIEWD(u32 phywpwwcwksew	: 1,
		__BITFIEWD_FIEWD(u32 wesewved_14_14	: 1,
		__BITFIEWD_FIEWD(u32 usbtwdtim		: 4,
		__BITFIEWD_FIEWD(u32 hnpcap		: 1,
		__BITFIEWD_FIEWD(u32 swpcap		: 1,
		__BITFIEWD_FIEWD(u32 ddwsew		: 1,
		__BITFIEWD_FIEWD(u32 physew		: 1,
		__BITFIEWD_FIEWD(u32 fsintf		: 1,
		__BITFIEWD_FIEWD(u32 uwpi_utmi_sew	: 1,
		__BITFIEWD_FIEWD(u32 phyif		: 1,
		__BITFIEWD_FIEWD(u32 toutcaw		: 3,
		;)))))))))))))
	} s;
};

/**
 * cvmx_usbc#_haint
 *
 * Host Aww Channews Intewwupt Wegistew (HAINT)
 *
 * When a significant event occuws on a channew, the Host Aww Channews Intewwupt
 * wegistew intewwupts the appwication using the Host Channews Intewwupt bit of
 * the Cowe Intewwupt wegistew (GINTSTS.HChInt). This is shown in Intewwupt.
 * Thewe is one intewwupt bit pew channew, up to a maximum of 16 bits. Bits in
 * this wegistew awe set and cweawed when the appwication sets and cweaws bits
 * in the cowwesponding Host Channew-n Intewwupt wegistew.
 */
union cvmx_usbcx_haint {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_haint_s
	 * @haint: Channew Intewwupts (HAINT)
	 *	One bit pew channew: Bit 0 fow Channew 0, bit 15 fow Channew 15
	 */
	stwuct cvmx_usbcx_haint_s {
		__BITFIEWD_FIEWD(u32 wesewved_16_31	: 16,
		__BITFIEWD_FIEWD(u32 haint		: 16,
		;))
	} s;
};

/**
 * cvmx_usbc#_haintmsk
 *
 * Host Aww Channews Intewwupt Mask Wegistew (HAINTMSK)
 *
 * The Host Aww Channew Intewwupt Mask wegistew wowks with the Host Aww Channew
 * Intewwupt wegistew to intewwupt the appwication when an event occuws on a
 * channew. Thewe is one intewwupt mask bit pew channew, up to a maximum of 16
 * bits.
 * Mask intewwupt: 1'b0 Unmask intewwupt: 1'b1
 */
union cvmx_usbcx_haintmsk {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_haintmsk_s
	 * @haintmsk: Channew Intewwupt Mask (HAINTMsk)
	 *	One bit pew channew: Bit 0 fow channew 0, bit 15 fow channew 15
	 */
	stwuct cvmx_usbcx_haintmsk_s {
		__BITFIEWD_FIEWD(u32 wesewved_16_31	: 16,
		__BITFIEWD_FIEWD(u32 haintmsk		: 16,
		;))
	} s;
};

/**
 * cvmx_usbc#_hcchaw#
 *
 * Host Channew-n Chawactewistics Wegistew (HCCHAW)
 *
 */
union cvmx_usbcx_hcchawx {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_hcchawx_s
	 * @chena: Channew Enabwe (ChEna)
	 *	This fiewd is set by the appwication and cweawed by the OTG
	 *	host.
	 *	* 1'b0: Channew disabwed
	 *	* 1'b1: Channew enabwed
	 * @chdis: Channew Disabwe (ChDis)
	 *	The appwication sets this bit to stop twansmitting/weceiving
	 *	data on a channew, even befowe the twansfew fow that channew is
	 *	compwete. The appwication must wait fow the Channew Disabwed
	 *	intewwupt befowe tweating the channew as disabwed.
	 * @oddfwm: Odd Fwame (OddFwm)
	 *	This fiewd is set (weset) by the appwication to indicate that
	 *	the OTG host must pewfowm a twansfew in an odd (micwo)fwame.
	 *	This fiewd is appwicabwe fow onwy pewiodic (isochwonous and
	 *	intewwupt) twansactions.
	 *	* 1'b0: Even (micwo)fwame
	 *	* 1'b1: Odd (micwo)fwame
	 * @devaddw: Device Addwess (DevAddw)
	 *	This fiewd sewects the specific device sewving as the data
	 *	souwce ow sink.
	 * @ec: Muwti Count (MC) / Ewwow Count (EC)
	 *	When the Spwit Enabwe bit of the Host Channew-n Spwit Contwow
	 *	wegistew (HCSPWTn.SpwtEna) is weset (1'b0), this fiewd indicates
	 *	to the host the numbew of twansactions that shouwd be executed
	 *	pew micwofwame fow this endpoint.
	 *	* 2'b00: Wesewved. This fiewd yiewds undefined wesuwts.
	 *	* 2'b01: 1 twansaction
	 *	* 2'b10: 2 twansactions to be issued fow this endpoint pew
	 *	micwofwame
	 *	* 2'b11: 3 twansactions to be issued fow this endpoint pew
	 *	micwofwame
	 *	When HCSPWTn.SpwtEna is set (1'b1), this fiewd indicates the
	 *	numbew of immediate wetwies to be pewfowmed fow a pewiodic spwit
	 *	twansactions on twansaction ewwows. This fiewd must be set to at
	 *	weast 2'b01.
	 * @eptype: Endpoint Type (EPType)
	 *	Indicates the twansfew type sewected.
	 *	* 2'b00: Contwow
	 *	* 2'b01: Isochwonous
	 *	* 2'b10: Buwk
	 *	* 2'b11: Intewwupt
	 * @wspddev: Wow-Speed Device (WSpdDev)
	 *	This fiewd is set by the appwication to indicate that this
	 *	channew is communicating to a wow-speed device.
	 * @epdiw: Endpoint Diwection (EPDiw)
	 *	Indicates whethew the twansaction is IN ow OUT.
	 *	* 1'b0: OUT
	 *	* 1'b1: IN
	 * @epnum: Endpoint Numbew (EPNum)
	 *	Indicates the endpoint numbew on the device sewving as the
	 *	data souwce ow sink.
	 * @mps: Maximum Packet Size (MPS)
	 *	Indicates the maximum packet size of the associated endpoint.
	 */
	stwuct cvmx_usbcx_hcchawx_s {
		__BITFIEWD_FIEWD(u32 chena		: 1,
		__BITFIEWD_FIEWD(u32 chdis		: 1,
		__BITFIEWD_FIEWD(u32 oddfwm		: 1,
		__BITFIEWD_FIEWD(u32 devaddw		: 7,
		__BITFIEWD_FIEWD(u32 ec			: 2,
		__BITFIEWD_FIEWD(u32 eptype		: 2,
		__BITFIEWD_FIEWD(u32 wspddev		: 1,
		__BITFIEWD_FIEWD(u32 wesewved_16_16	: 1,
		__BITFIEWD_FIEWD(u32 epdiw		: 1,
		__BITFIEWD_FIEWD(u32 epnum		: 4,
		__BITFIEWD_FIEWD(u32 mps		: 11,
		;)))))))))))
	} s;
};

/**
 * cvmx_usbc#_hcfg
 *
 * Host Configuwation Wegistew (HCFG)
 *
 * This wegistew configuwes the cowe aftew powew-on. Do not make changes to this
 * wegistew aftew initiawizing the host.
 */
union cvmx_usbcx_hcfg {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_hcfg_s
	 * @fswssupp: FS- and WS-Onwy Suppowt (FSWSSupp)
	 *	The appwication uses this bit to contwow the cowe's enumewation
	 *	speed. Using this bit, the appwication can make the cowe
	 *	enumewate as a FS host, even if the connected device suppowts
	 *	HS twaffic. Do not make changes to this fiewd aftew initiaw
	 *	pwogwamming.
	 *	* 1'b0: HS/FS/WS, based on the maximum speed suppowted by
	 *	the connected device
	 *	* 1'b1: FS/WS-onwy, even if the connected device can suppowt HS
	 * @fswspcwksew: FS/WS PHY Cwock Sewect (FSWSPcwkSew)
	 *	When the cowe is in FS Host mode
	 *	* 2'b00: PHY cwock is wunning at 30/60 MHz
	 *	* 2'b01: PHY cwock is wunning at 48 MHz
	 *	* Othews: Wesewved
	 *	When the cowe is in WS Host mode
	 *	* 2'b00: PHY cwock is wunning at 30/60 MHz. When the
	 *	UTMI+/UWPI PHY Wow Powew mode is not sewected, use
	 *	30/60 MHz.
	 *	* 2'b01: PHY cwock is wunning at 48 MHz. When the UTMI+
	 *	PHY Wow Powew mode is sewected, use 48MHz if the PHY
	 *	suppwies a 48 MHz cwock duwing WS mode.
	 *	* 2'b10: PHY cwock is wunning at 6 MHz. In USB 1.1 FS mode,
	 *	use 6 MHz when the UTMI+ PHY Wow Powew mode is
	 *	sewected and the PHY suppwies a 6 MHz cwock duwing WS
	 *	mode. If you sewect a 6 MHz cwock duwing WS mode, you must
	 *	do a soft weset.
	 *	* 2'b11: Wesewved
	 */
	stwuct cvmx_usbcx_hcfg_s {
		__BITFIEWD_FIEWD(u32 wesewved_3_31	: 29,
		__BITFIEWD_FIEWD(u32 fswssupp		: 1,
		__BITFIEWD_FIEWD(u32 fswspcwksew	: 2,
		;)))
	} s;
};

/**
 * cvmx_usbc#_hcint#
 *
 * Host Channew-n Intewwupt Wegistew (HCINT)
 *
 * This wegistew indicates the status of a channew with wespect to USB- and
 * AHB-wewated events. The appwication must wead this wegistew when the Host
 * Channews Intewwupt bit of the Cowe Intewwupt wegistew (GINTSTS.HChInt) is
 * set. Befowe the appwication can wead this wegistew, it must fiwst wead
 * the Host Aww Channews Intewwupt (HAINT) wegistew to get the exact channew
 * numbew fow the Host Channew-n Intewwupt wegistew. The appwication must cweaw
 * the appwopwiate bit in this wegistew to cweaw the cowwesponding bits in the
 * HAINT and GINTSTS wegistews.
 */
union cvmx_usbcx_hcintx {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_hcintx_s
	 * @datatgweww: Data Toggwe Ewwow (DataTgwEww)
	 * @fwmovwun: Fwame Ovewwun (FwmOvwun)
	 * @bbweww: Babbwe Ewwow (BbwEww)
	 * @xacteww: Twansaction Ewwow (XactEww)
	 * @nyet: NYET Wesponse Weceived Intewwupt (NYET)
	 * @ack: ACK Wesponse Weceived Intewwupt (ACK)
	 * @nak: NAK Wesponse Weceived Intewwupt (NAK)
	 * @staww: STAWW Wesponse Weceived Intewwupt (STAWW)
	 * @ahbeww: This bit is awways 0x0.
	 * @chhwtd: Channew Hawted (ChHwtd)
	 *	Indicates the twansfew compweted abnowmawwy eithew because of
	 *	any USB twansaction ewwow ow in wesponse to disabwe wequest by
	 *	the appwication.
	 * @xfewcompw: Twansfew Compweted (XfewCompw)
	 *	Twansfew compweted nowmawwy without any ewwows.
	 */
	stwuct cvmx_usbcx_hcintx_s {
		__BITFIEWD_FIEWD(u32 wesewved_11_31	: 21,
		__BITFIEWD_FIEWD(u32 datatgweww		: 1,
		__BITFIEWD_FIEWD(u32 fwmovwun		: 1,
		__BITFIEWD_FIEWD(u32 bbweww		: 1,
		__BITFIEWD_FIEWD(u32 xacteww		: 1,
		__BITFIEWD_FIEWD(u32 nyet		: 1,
		__BITFIEWD_FIEWD(u32 ack		: 1,
		__BITFIEWD_FIEWD(u32 nak		: 1,
		__BITFIEWD_FIEWD(u32 staww		: 1,
		__BITFIEWD_FIEWD(u32 ahbeww		: 1,
		__BITFIEWD_FIEWD(u32 chhwtd		: 1,
		__BITFIEWD_FIEWD(u32 xfewcompw		: 1,
		;))))))))))))
	} s;
};

/**
 * cvmx_usbc#_hcintmsk#
 *
 * Host Channew-n Intewwupt Mask Wegistew (HCINTMSKn)
 *
 * This wegistew wefwects the mask fow each channew status descwibed in the
 * pwevious section.
 * Mask intewwupt: 1'b0 Unmask intewwupt: 1'b1
 */
union cvmx_usbcx_hcintmskx {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_hcintmskx_s
	 * @datatgwewwmsk: Data Toggwe Ewwow Mask (DataTgwEwwMsk)
	 * @fwmovwunmsk: Fwame Ovewwun Mask (FwmOvwunMsk)
	 * @bbwewwmsk: Babbwe Ewwow Mask (BbwEwwMsk)
	 * @xactewwmsk: Twansaction Ewwow Mask (XactEwwMsk)
	 * @nyetmsk: NYET Wesponse Weceived Intewwupt Mask (NyetMsk)
	 * @ackmsk: ACK Wesponse Weceived Intewwupt Mask (AckMsk)
	 * @nakmsk: NAK Wesponse Weceived Intewwupt Mask (NakMsk)
	 * @stawwmsk: STAWW Wesponse Weceived Intewwupt Mask (StawwMsk)
	 * @ahbewwmsk: AHB Ewwow Mask (AHBEwwMsk)
	 * @chhwtdmsk: Channew Hawted Mask (ChHwtdMsk)
	 * @xfewcompwmsk: Twansfew Compweted Mask (XfewCompwMsk)
	 */
	stwuct cvmx_usbcx_hcintmskx_s {
		__BITFIEWD_FIEWD(u32 wesewved_11_31		: 21,
		__BITFIEWD_FIEWD(u32 datatgwewwmsk		: 1,
		__BITFIEWD_FIEWD(u32 fwmovwunmsk		: 1,
		__BITFIEWD_FIEWD(u32 bbwewwmsk			: 1,
		__BITFIEWD_FIEWD(u32 xactewwmsk			: 1,
		__BITFIEWD_FIEWD(u32 nyetmsk			: 1,
		__BITFIEWD_FIEWD(u32 ackmsk			: 1,
		__BITFIEWD_FIEWD(u32 nakmsk			: 1,
		__BITFIEWD_FIEWD(u32 stawwmsk			: 1,
		__BITFIEWD_FIEWD(u32 ahbewwmsk			: 1,
		__BITFIEWD_FIEWD(u32 chhwtdmsk			: 1,
		__BITFIEWD_FIEWD(u32 xfewcompwmsk		: 1,
		;))))))))))))
	} s;
};

/**
 * cvmx_usbc#_hcspwt#
 *
 * Host Channew-n Spwit Contwow Wegistew (HCSPWT)
 *
 */
union cvmx_usbcx_hcspwtx {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_hcspwtx_s
	 * @spwtena: Spwit Enabwe (SpwtEna)
	 *	The appwication sets this fiewd to indicate that this channew is
	 *	enabwed to pewfowm spwit twansactions.
	 * @compspwt: Do Compwete Spwit (CompSpwt)
	 *	The appwication sets this fiewd to wequest the OTG host to
	 *	pewfowm a compwete spwit twansaction.
	 * @xactpos: Twansaction Position (XactPos)
	 *	This fiewd is used to detewmine whethew to send aww, fiwst,
	 *	middwe, ow wast paywoads with each OUT twansaction.
	 *	* 2'b11: Aww. This is the entiwe data paywoad is of this
	 *	twansaction (which is wess than ow equaw to 188 bytes).
	 *	* 2'b10: Begin. This is the fiwst data paywoad of this
	 *	twansaction (which is wawgew than 188 bytes).
	 *	* 2'b00: Mid. This is the middwe paywoad of this twansaction
	 *	(which is wawgew than 188 bytes).
	 *	* 2'b01: End. This is the wast paywoad of this twansaction
	 *	(which is wawgew than 188 bytes).
	 * @hubaddw: Hub Addwess (HubAddw)
	 *	This fiewd howds the device addwess of the twansaction
	 *	twanswatow's hub.
	 * @pwtaddw: Powt Addwess (PwtAddw)
	 *	This fiewd is the powt numbew of the wecipient twansaction
	 *	twanswatow.
	 */
	stwuct cvmx_usbcx_hcspwtx_s {
		__BITFIEWD_FIEWD(u32 spwtena			: 1,
		__BITFIEWD_FIEWD(u32 wesewved_17_30		: 14,
		__BITFIEWD_FIEWD(u32 compspwt			: 1,
		__BITFIEWD_FIEWD(u32 xactpos			: 2,
		__BITFIEWD_FIEWD(u32 hubaddw			: 7,
		__BITFIEWD_FIEWD(u32 pwtaddw			: 7,
		;))))))
	} s;
};

/**
 * cvmx_usbc#_hctsiz#
 *
 * Host Channew-n Twansfew Size Wegistew (HCTSIZ)
 *
 */
union cvmx_usbcx_hctsizx {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_hctsizx_s
	 * @dopng: Do Ping (DoPng)
	 *	Setting this fiewd to 1 diwects the host to do PING pwotocow.
	 * @pid: PID (Pid)
	 *	The appwication pwogwams this fiewd with the type of PID to use
	 *	fow the initiaw twansaction. The host wiww maintain this fiewd
	 *	fow the west of the twansfew.
	 *	* 2'b00: DATA0
	 *	* 2'b01: DATA2
	 *	* 2'b10: DATA1
	 *	* 2'b11: MDATA (non-contwow)/SETUP (contwow)
	 * @pktcnt: Packet Count (PktCnt)
	 *	This fiewd is pwogwammed by the appwication with the expected
	 *	numbew of packets to be twansmitted (OUT) ow weceived (IN).
	 *	The host decwements this count on evewy successfuw
	 *	twansmission ow weception of an OUT/IN packet. Once this count
	 *	weaches zewo, the appwication is intewwupted to indicate nowmaw
	 *	compwetion.
	 * @xfewsize: Twansfew Size (XfewSize)
	 *	Fow an OUT, this fiewd is the numbew of data bytes the host wiww
	 *	send duwing the twansfew.
	 *	Fow an IN, this fiewd is the buffew size that the appwication
	 *	has wesewved fow the twansfew. The appwication is expected to
	 *	pwogwam this fiewd as an integew muwtipwe of the maximum packet
	 *	size fow IN twansactions (pewiodic and non-pewiodic).
	 */
	stwuct cvmx_usbcx_hctsizx_s {
		__BITFIEWD_FIEWD(u32 dopng		: 1,
		__BITFIEWD_FIEWD(u32 pid		: 2,
		__BITFIEWD_FIEWD(u32 pktcnt		: 10,
		__BITFIEWD_FIEWD(u32 xfewsize		: 19,
		;))))
	} s;
};

/**
 * cvmx_usbc#_hfiw
 *
 * Host Fwame Intewvaw Wegistew (HFIW)
 *
 * This wegistew stowes the fwame intewvaw infowmation fow the cuwwent speed to
 * which the O2P USB cowe has enumewated.
 */
union cvmx_usbcx_hfiw {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_hfiw_s
	 * @fwint: Fwame Intewvaw (FwInt)
	 *	The vawue that the appwication pwogwams to this fiewd specifies
	 *	the intewvaw between two consecutive SOFs (FS) ow micwo-
	 *	SOFs (HS) ow Keep-Awive tokens (HS). This fiewd contains the
	 *	numbew of PHY cwocks that constitute the wequiwed fwame
	 *	intewvaw. The defauwt vawue set in this fiewd fow a FS opewation
	 *	when the PHY cwock fwequency is 60 MHz. The appwication can
	 *	wwite a vawue to this wegistew onwy aftew the Powt Enabwe bit of
	 *	the Host Powt Contwow and Status wegistew (HPWT.PwtEnaPowt)
	 *	has been set. If no vawue is pwogwammed, the cowe cawcuwates
	 *	the vawue based on the PHY cwock specified in the FS/WS PHY
	 *	Cwock Sewect fiewd of the Host Configuwation wegistew
	 *	(HCFG.FSWSPcwkSew). Do not change the vawue of this fiewd
	 *	aftew the initiaw configuwation.
	 *	* 125 us (PHY cwock fwequency fow HS)
	 *	* 1 ms (PHY cwock fwequency fow FS/WS)
	 */
	stwuct cvmx_usbcx_hfiw_s {
		__BITFIEWD_FIEWD(u32 wesewved_16_31		: 16,
		__BITFIEWD_FIEWD(u32 fwint			: 16,
		;))
	} s;
};

/**
 * cvmx_usbc#_hfnum
 *
 * Host Fwame Numbew/Fwame Time Wemaining Wegistew (HFNUM)
 *
 * This wegistew indicates the cuwwent fwame numbew.
 * It awso indicates the time wemaining (in tewms of the numbew of PHY cwocks)
 * in the cuwwent (micwo)fwame.
 */
union cvmx_usbcx_hfnum {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_hfnum_s
	 * @fwwem: Fwame Time Wemaining (FwWem)
	 *	Indicates the amount of time wemaining in the cuwwent
	 *	micwofwame (HS) ow fwame (FS/WS), in tewms of PHY cwocks.
	 *	This fiewd decwements on each PHY cwock. When it weaches
	 *	zewo, this fiewd is wewoaded with the vawue in the Fwame
	 *	Intewvaw wegistew and a new SOF is twansmitted on the USB.
	 * @fwnum: Fwame Numbew (FwNum)
	 *	This fiewd incwements when a new SOF is twansmitted on the
	 *	USB, and is weset to 0 when it weaches 16'h3FFF.
	 */
	stwuct cvmx_usbcx_hfnum_s {
		__BITFIEWD_FIEWD(u32 fwwem		: 16,
		__BITFIEWD_FIEWD(u32 fwnum		: 16,
		;))
	} s;
};

/**
 * cvmx_usbc#_hpwt
 *
 * Host Powt Contwow and Status Wegistew (HPWT)
 *
 * This wegistew is avaiwabwe in both Host and Device modes.
 * Cuwwentwy, the OTG Host suppowts onwy one powt.
 * A singwe wegistew howds USB powt-wewated infowmation such as USB weset,
 * enabwe, suspend, wesume, connect status, and test mode fow each powt. The
 * W_SS_WC bits in this wegistew can twiggew an intewwupt to the appwication
 * thwough the Host Powt Intewwupt bit of the Cowe Intewwupt wegistew
 * (GINTSTS.PwtInt). On a Powt Intewwupt, the appwication must wead this
 * wegistew and cweaw the bit that caused the intewwupt. Fow the W_SS_WC bits,
 * the appwication must wwite a 1 to the bit to cweaw the intewwupt.
 */
union cvmx_usbcx_hpwt {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_hpwt_s
	 * @pwtspd: Powt Speed (PwtSpd)
	 *	Indicates the speed of the device attached to this powt.
	 *	* 2'b00: High speed
	 *	* 2'b01: Fuww speed
	 *	* 2'b10: Wow speed
	 *	* 2'b11: Wesewved
	 * @pwttstctw: Powt Test Contwow (PwtTstCtw)
	 *	The appwication wwites a nonzewo vawue to this fiewd to put
	 *	the powt into a Test mode, and the cowwesponding pattewn is
	 *	signawed on the powt.
	 *	* 4'b0000: Test mode disabwed
	 *	* 4'b0001: Test_J mode
	 *	* 4'b0010: Test_K mode
	 *	* 4'b0011: Test_SE0_NAK mode
	 *	* 4'b0100: Test_Packet mode
	 *	* 4'b0101: Test_Fowce_Enabwe
	 *	* Othews: Wesewved
	 *	PwtSpd must be zewo (i.e. the intewface must be in high-speed
	 *	mode) to use the PwtTstCtw test modes.
	 * @pwtpww: Powt Powew (PwtPww)
	 *	The appwication uses this fiewd to contwow powew to this powt,
	 *	and the cowe cweaws this bit on an ovewcuwwent condition.
	 *	* 1'b0: Powew off
	 *	* 1'b1: Powew on
	 * @pwtwnsts: Powt Wine Status (PwtWnSts)
	 *	Indicates the cuwwent wogic wevew USB data wines
	 *	* Bit [10]: Wogic wevew of D-
	 *	* Bit [11]: Wogic wevew of D+
	 * @pwtwst: Powt Weset (PwtWst)
	 *	When the appwication sets this bit, a weset sequence is
	 *	stawted on this powt. The appwication must time the weset
	 *	pewiod and cweaw this bit aftew the weset sequence is
	 *	compwete.
	 *	* 1'b0: Powt not in weset
	 *	* 1'b1: Powt in weset
	 *	The appwication must weave this bit set fow at weast a
	 *	minimum duwation mentioned bewow to stawt a weset on the
	 *	powt. The appwication can weave it set fow anothew 10 ms in
	 *	addition to the wequiwed minimum duwation, befowe cweawing
	 *	the bit, even though thewe is no maximum wimit set by the
	 *	USB standawd.
	 *	* High speed: 50 ms
	 *	* Fuww speed/Wow speed: 10 ms
	 * @pwtsusp: Powt Suspend (PwtSusp)
	 *	The appwication sets this bit to put this powt in Suspend
	 *	mode. The cowe onwy stops sending SOFs when this is set.
	 *	To stop the PHY cwock, the appwication must set the Powt
	 *	Cwock Stop bit, which wiww assewt the suspend input pin of
	 *	the PHY.
	 *	The wead vawue of this bit wefwects the cuwwent suspend
	 *	status of the powt. This bit is cweawed by the cowe aftew a
	 *	wemote wakeup signaw is detected ow the appwication sets
	 *	the Powt Weset bit ow Powt Wesume bit in this wegistew ow the
	 *	Wesume/Wemote Wakeup Detected Intewwupt bit ow
	 *	Disconnect Detected Intewwupt bit in the Cowe Intewwupt
	 *	wegistew (GINTSTS.WkUpInt ow GINTSTS.DisconnInt,
	 *	wespectivewy).
	 *	* 1'b0: Powt not in Suspend mode
	 *	* 1'b1: Powt in Suspend mode
	 * @pwtwes: Powt Wesume (PwtWes)
	 *	The appwication sets this bit to dwive wesume signawing on
	 *	the powt. The cowe continues to dwive the wesume signaw
	 *	untiw the appwication cweaws this bit.
	 *	If the cowe detects a USB wemote wakeup sequence, as
	 *	indicated by the Powt Wesume/Wemote Wakeup Detected
	 *	Intewwupt bit of the Cowe Intewwupt wegistew
	 *	(GINTSTS.WkUpInt), the cowe stawts dwiving wesume
	 *	signawing without appwication intewvention and cweaws this bit
	 *	when it detects a disconnect condition. The wead vawue of
	 *	this bit indicates whethew the cowe is cuwwentwy dwiving
	 *	wesume signawing.
	 *	* 1'b0: No wesume dwiven
	 *	* 1'b1: Wesume dwiven
	 * @pwtovwcuwwchng: Powt Ovewcuwwent Change (PwtOvwCuwwChng)
	 *	The cowe sets this bit when the status of the Powt
	 *	Ovewcuwwent Active bit (bit 4) in this wegistew changes.
	 * @pwtovwcuwwact: Powt Ovewcuwwent Active (PwtOvwCuwwAct)
	 *	Indicates the ovewcuwwent condition of the powt.
	 *	* 1'b0: No ovewcuwwent condition
	 *	* 1'b1: Ovewcuwwent condition
	 * @pwtenchng: Powt Enabwe/Disabwe Change (PwtEnChng)
	 *	The cowe sets this bit when the status of the Powt Enabwe bit
	 *	[2] of this wegistew changes.
	 * @pwtena: Powt Enabwe (PwtEna)
	 *	A powt is enabwed onwy by the cowe aftew a weset sequence,
	 *	and is disabwed by an ovewcuwwent condition, a disconnect
	 *	condition, ow by the appwication cweawing this bit. The
	 *	appwication cannot set this bit by a wegistew wwite. It can onwy
	 *	cweaw it to disabwe the powt. This bit does not twiggew any
	 *	intewwupt to the appwication.
	 *	* 1'b0: Powt disabwed
	 *	* 1'b1: Powt enabwed
	 * @pwtconndet: Powt Connect Detected (PwtConnDet)
	 *	The cowe sets this bit when a device connection is detected
	 *	to twiggew an intewwupt to the appwication using the Host Powt
	 *	Intewwupt bit of the Cowe Intewwupt wegistew (GINTSTS.PwtInt).
	 *	The appwication must wwite a 1 to this bit to cweaw the
	 *	intewwupt.
	 * @pwtconnsts: Powt Connect Status (PwtConnSts)
	 *	* 0: No device is attached to the powt.
	 *	* 1: A device is attached to the powt.
	 */
	stwuct cvmx_usbcx_hpwt_s {
		__BITFIEWD_FIEWD(u32 wesewved_19_31	: 13,
		__BITFIEWD_FIEWD(u32 pwtspd		: 2,
		__BITFIEWD_FIEWD(u32 pwttstctw		: 4,
		__BITFIEWD_FIEWD(u32 pwtpww		: 1,
		__BITFIEWD_FIEWD(u32 pwtwnsts		: 2,
		__BITFIEWD_FIEWD(u32 wesewved_9_9	: 1,
		__BITFIEWD_FIEWD(u32 pwtwst		: 1,
		__BITFIEWD_FIEWD(u32 pwtsusp		: 1,
		__BITFIEWD_FIEWD(u32 pwtwes		: 1,
		__BITFIEWD_FIEWD(u32 pwtovwcuwwchng	: 1,
		__BITFIEWD_FIEWD(u32 pwtovwcuwwact	: 1,
		__BITFIEWD_FIEWD(u32 pwtenchng		: 1,
		__BITFIEWD_FIEWD(u32 pwtena		: 1,
		__BITFIEWD_FIEWD(u32 pwtconndet		: 1,
		__BITFIEWD_FIEWD(u32 pwtconnsts		: 1,
		;)))))))))))))))
	} s;
};

/**
 * cvmx_usbc#_hptxfsiz
 *
 * Host Pewiodic Twansmit FIFO Size Wegistew (HPTXFSIZ)
 *
 * This wegistew howds the size and the memowy stawt addwess of the Pewiodic
 * TxFIFO, as shown in Figuwes 310 and 311.
 */
union cvmx_usbcx_hptxfsiz {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_hptxfsiz_s
	 * @ptxfsize: Host Pewiodic TxFIFO Depth (PTxFSize)
	 *	This vawue is in tewms of 32-bit wowds.
	 *	* Minimum vawue is 16
	 *	* Maximum vawue is 32768
	 * @ptxfstaddw: Host Pewiodic TxFIFO Stawt Addwess (PTxFStAddw)
	 */
	stwuct cvmx_usbcx_hptxfsiz_s {
		__BITFIEWD_FIEWD(u32 ptxfsize	: 16,
		__BITFIEWD_FIEWD(u32 ptxfstaddw	: 16,
		;))
	} s;
};

/**
 * cvmx_usbc#_hptxsts
 *
 * Host Pewiodic Twansmit FIFO/Queue Status Wegistew (HPTXSTS)
 *
 * This wead-onwy wegistew contains the fwee space infowmation fow the Pewiodic
 * TxFIFO and the Pewiodic Twansmit Wequest Queue
 */
union cvmx_usbcx_hptxsts {
	u32 u32;
	/**
	 * stwuct cvmx_usbcx_hptxsts_s
	 * @ptxqtop: Top of the Pewiodic Twansmit Wequest Queue (PTxQTop)
	 *	This indicates the entwy in the Pewiodic Tx Wequest Queue that
	 *	is cuwwentwy being pwocesses by the MAC.
	 *	This wegistew is used fow debugging.
	 *	* Bit [31]: Odd/Even (micwo)fwame
	 *	- 1'b0: send in even (micwo)fwame
	 *	- 1'b1: send in odd (micwo)fwame
	 *	* Bits [30:27]: Channew/endpoint numbew
	 *	* Bits [26:25]: Type
	 *	- 2'b00: IN/OUT
	 *	- 2'b01: Zewo-wength packet
	 *	- 2'b10: CSPWIT
	 *	- 2'b11: Disabwe channew command
	 *	* Bit [24]: Tewminate (wast entwy fow the sewected
	 *	channew/endpoint)
	 * @ptxqspcavaiw: Pewiodic Twansmit Wequest Queue Space Avaiwabwe
	 *	(PTxQSpcAvaiw)
	 *	Indicates the numbew of fwee wocations avaiwabwe to be wwitten
	 *	in the Pewiodic Twansmit Wequest Queue. This queue howds both
	 *	IN and OUT wequests.
	 *	* 8'h0: Pewiodic Twansmit Wequest Queue is fuww
	 *	* 8'h1: 1 wocation avaiwabwe
	 *	* 8'h2: 2 wocations avaiwabwe
	 *	* n: n wocations avaiwabwe (0..8)
	 *	* Othews: Wesewved
	 * @ptxfspcavaiw: Pewiodic Twansmit Data FIFO Space Avaiwabwe
	 *		  (PTxFSpcAvaiw)
	 *	Indicates the numbew of fwee wocations avaiwabwe to be wwitten
	 *	to in the Pewiodic TxFIFO.
	 *	Vawues awe in tewms of 32-bit wowds
	 *	* 16'h0: Pewiodic TxFIFO is fuww
	 *	* 16'h1: 1 wowd avaiwabwe
	 *	* 16'h2: 2 wowds avaiwabwe
	 *	* 16'hn: n wowds avaiwabwe (whewe 0..32768)
	 *	* 16'h8000: 32768 wowds avaiwabwe
	 *	* Othews: Wesewved
	 */
	stwuct cvmx_usbcx_hptxsts_s {
		__BITFIEWD_FIEWD(u32 ptxqtop		: 8,
		__BITFIEWD_FIEWD(u32 ptxqspcavaiw	: 8,
		__BITFIEWD_FIEWD(u32 ptxfspcavaiw	: 16,
		;)))
	} s;
};

/**
 * cvmx_usbn#_cwk_ctw
 *
 * USBN_CWK_CTW = USBN's Cwock Contwow
 *
 * This wegistew is used to contwow the fwequency of the hcwk and the
 * hweset and phy_wst signaws.
 */
union cvmx_usbnx_cwk_ctw {
	u64 u64;
	/**
	 * stwuct cvmx_usbnx_cwk_ctw_s
	 * @divide2: The 'hcwk' used by the USB subsystem is dewived
	 *	fwom the ecwk.
	 *	Awso see the fiewd DIVIDE. DIVIDE2<1> must cuwwentwy
	 *	be zewo because it is not impwemented, so the maximum
	 *	watio of ecwk/hcwk is cuwwentwy 16.
	 *	The actuaw divide numbew fow hcwk is:
	 *	(DIVIDE2 + 1) * (DIVIDE + 1)
	 * @hcwk_wst: When this fiewd is '0' the HCWK-DIVIDEW used to
	 *	genewate the hcwk in the USB Subsystem is hewd
	 *	in weset. This bit must be set to '0' befowe
	 *	changing the vawue os DIVIDE in this wegistew.
	 *	The weset to the HCWK_DIVIDEWis awso assewted
	 *	when cowe weset is assewted.
	 * @p_x_on: Fowce USB-PHY on duwing suspend.
	 *	'1' USB-PHY XO bwock is powewed-down duwing
	 *	suspend.
	 *	'0' USB-PHY XO bwock is powewed-up duwing
	 *	suspend.
	 *	The vawue of this fiewd must be set whiwe POW is
	 *	active.
	 * @p_wtype: PHY wefewence cwock type
	 *	On CN50XX/CN52XX/CN56XX the vawues awe:
	 *		'0' The USB-PHY uses a 12MHz cwystaw as a cwock souwce
	 *		    at the USB_XO and USB_XI pins.
	 *		'1' Wesewved.
	 *		'2' The USB_PHY uses 12/24/48MHz 2.5V boawd cwock at the
	 *		    USB_XO pin. USB_XI shouwd be tied to gwound in this
	 *		    case.
	 *		'3' Wesewved.
	 *	On CN3xxx bits 14 and 15 awe p_xenbn and p_wcwk and vawues awe:
	 *		'0' Wesewved.
	 *		'1' Wesewved.
	 *		'2' The PHY PWW uses the XO bwock output as a wefewence.
	 *		    The XO bwock uses an extewnaw cwock suppwied on the
	 *		    XO pin. USB_XI shouwd be tied to gwound fow this
	 *		    usage.
	 *		'3' The XO bwock uses the cwock fwom a cwystaw.
	 * @p_com_on: '0' Fowce USB-PHY XO Bias, Bandgap and PWW to
	 *	wemain powewed in Suspend Mode.
	 *	'1' The USB-PHY XO Bias, Bandgap and PWW awe
	 *	powewed down in suspend mode.
	 *	The vawue of this fiewd must be set whiwe POW is
	 *	active.
	 * @p_c_sew: Phy cwock speed sewect.
	 *	Sewects the wefewence cwock / cwystaw fwequency.
	 *	'11': Wesewved
	 *	'10': 48 MHz (wesewved when a cwystaw is used)
	 *	'01': 24 MHz (wesewved when a cwystaw is used)
	 *	'00': 12 MHz
	 *	The vawue of this fiewd must be set whiwe POW is
	 *	active.
	 *	NOTE: if a cwystaw is used as a wefewence cwock,
	 *	this fiewd must be set to 12 MHz.
	 * @cdiv_byp: Used to enabwe the bypass input to the USB_CWK_DIV.
	 * @sd_mode: Scawedown mode fow the USBC. Contwow timing events
	 *	in the USBC, fow nowmaw opewation this must be '0'.
	 * @s_bist: Stawts bist on the hcwk memowies, duwing the '0'
	 *	to '1' twansition.
	 * @pow: Powew On Weset fow the PHY.
	 *	Wesets aww the PHYS wegistews and state machines.
	 * @enabwe: When '1' awwows the genewation of the hcwk. When
	 *	'0' the hcwk wiww not be genewated. SEE DIVIDE
	 *	fiewd of this wegistew.
	 * @pwst: When this fiewd is '0' the weset associated with
	 *	the phy_cwk functionawity in the USB Subsystem is
	 *	hewp in weset. This bit shouwd not be set to '1'
	 *	untiw the time it takes 6 cwocks (hcwk ow phy_cwk,
	 *	whichevew is swowew) has passed. Undew nowmaw
	 *	opewation once this bit is set to '1' it shouwd not
	 *	be set to '0'.
	 * @hwst: When this fiewd is '0' the weset associated with
	 *	the hcwk functioanwity in the USB Subsystem is
	 *	hewd in weset.This bit shouwd not be set to '1'
	 *	untiw 12ms aftew phy_cwk is stabwe. Undew nowmaw
	 *	opewation, once this bit is set to '1' it shouwd
	 *	not be set to '0'.
	 * @divide: The fwequency of 'hcwk' used by the USB subsystem
	 *	is the ecwk fwequency divided by the vawue of
	 *	(DIVIDE2 + 1) * (DIVIDE + 1), awso see the fiewd
	 *	DIVIDE2 of this wegistew.
	 *	The hcwk fwequency shouwd be wess than 125Mhz.
	 *	Aftew wwiting a vawue to this fiewd the SW shouwd
	 *	wead the fiewd fow the vawue wwitten.
	 *	The ENABWE fiewd of this wegistew shouwd not be set
	 *	untiw AFTEW this fiewd is set and then wead.
	 */
	stwuct cvmx_usbnx_cwk_ctw_s {
		__BITFIEWD_FIEWD(u64 wesewved_20_63	: 44,
		__BITFIEWD_FIEWD(u64 divide2		: 2,
		__BITFIEWD_FIEWD(u64 hcwk_wst		: 1,
		__BITFIEWD_FIEWD(u64 p_x_on		: 1,
		__BITFIEWD_FIEWD(u64 p_wtype		: 2,
		__BITFIEWD_FIEWD(u64 p_com_on		: 1,
		__BITFIEWD_FIEWD(u64 p_c_sew		: 2,
		__BITFIEWD_FIEWD(u64 cdiv_byp		: 1,
		__BITFIEWD_FIEWD(u64 sd_mode		: 2,
		__BITFIEWD_FIEWD(u64 s_bist		: 1,
		__BITFIEWD_FIEWD(u64 pow		: 1,
		__BITFIEWD_FIEWD(u64 enabwe		: 1,
		__BITFIEWD_FIEWD(u64 pwst		: 1,
		__BITFIEWD_FIEWD(u64 hwst		: 1,
		__BITFIEWD_FIEWD(u64 divide		: 3,
		;)))))))))))))))
	} s;
};

/**
 * cvmx_usbn#_usbp_ctw_status
 *
 * USBN_USBP_CTW_STATUS = USBP Contwow And Status Wegistew
 *
 * Contains genewaw contwow and status infowmation fow the USBN bwock.
 */
union cvmx_usbnx_usbp_ctw_status {
	u64 u64;
	/**
	 * stwuct cvmx_usbnx_usbp_ctw_status_s
	 * @txwisetune: HS Twansmittew Wise/Faww Time Adjustment
	 * @txvweftune: HS DC Vowtage Wevew Adjustment
	 * @txfswstune: FS/WS Souwce Impedance Adjustment
	 * @txhsxvtune: Twansmittew High-Speed Cwossovew Adjustment
	 * @sqwxtune: Squewch Thweshowd Adjustment
	 * @compdistune: Disconnect Thweshowd Adjustment
	 * @otgtune: VBUS Vawid Thweshowd Adjustment
	 * @otgdisabwe: OTG Bwock Disabwe
	 * @powtweset: Pew_Powt Weset
	 * @dwvvbus: Dwive VBUS
	 * @wsbist: Wow-Speed BIST Enabwe.
	 * @fsbist: Fuww-Speed BIST Enabwe.
	 * @hsbist: High-Speed BIST Enabwe.
	 * @bist_done: PHY Bist Done.
	 *	Assewted at the end of the PHY BIST sequence.
	 * @bist_eww: PHY Bist Ewwow.
	 *	Indicates an intewnaw ewwow was detected duwing
	 *	the BIST sequence.
	 * @tdata_out: PHY Test Data Out.
	 *	Pwesents eithew intewnawwy genewated signaws ow
	 *	test wegistew contents, based upon the vawue of
	 *	test_data_out_sew.
	 * @siddq: Dwives the USBP (USB-PHY) SIDDQ input.
	 *	Nowmawwy shouwd be set to zewo.
	 *	When customews have no intent to use USB PHY
	 *	intewface, they shouwd:
	 *	- stiww pwovide 3.3V to USB_VDD33, and
	 *	- tie USB_WEXT to 3.3V suppwy, and
	 *	- set USBN*_USBP_CTW_STATUS[SIDDQ]=1
	 * @txpweemphasistune: HS Twansmittew Pwe-Emphasis Enabwe
	 * @dma_bmode: When set to 1 the W2C DMA addwess wiww be updated
	 *	with byte-counts between packets. When set to 0
	 *	the W2C DMA addwess is incwemented to the next
	 *	4-byte awigned addwess aftew adding byte-count.
	 * @usbc_end: Bigendian input to the USB Cowe. This shouwd be
	 *	set to '0' fow opewation.
	 * @usbp_bist: PHY, This is cweawed '0' to wun BIST on the USBP.
	 * @tcwk: PHY Test Cwock, used to woad TDATA_IN to the USBP.
	 * @dp_puwwd: PHY DP_PUWWDOWN input to the USB-PHY.
	 *	This signaw enabwes the puww-down wesistance on
	 *	the D+ wine. '1' puww down-wesistance is connected
	 *	to D+/ '0' puww down wesistance is not connected
	 *	to D+. When an A/B device is acting as a host
	 *	(downstweam-facing powt), dp_puwwdown and
	 *	dm_puwwdown awe enabwed. This must not toggwe
	 *	duwing nowmaw opewation.
	 * @dm_puwwd: PHY DM_PUWWDOWN input to the USB-PHY.
	 *	This signaw enabwes the puww-down wesistance on
	 *	the D- wine. '1' puww down-wesistance is connected
	 *	to D-. '0' puww down wesistance is not connected
	 *	to D-. When an A/B device is acting as a host
	 *	(downstweam-facing powt), dp_puwwdown and
	 *	dm_puwwdown awe enabwed. This must not toggwe
	 *	duwing nowmaw opewation.
	 * @hst_mode: When '0' the USB is acting as HOST, when '1'
	 *	USB is acting as device. This fiewd needs to be
	 *	set whiwe the USB is in weset.
	 * @tuning: Twansmittew Tuning fow High-Speed Opewation.
	 *	Tunes the cuwwent suppwy and wise/faww output
	 *	times fow high-speed opewation.
	 *	[20:19] == 11: Cuwwent suppwy incweased
	 *	appwoximatewy 9%
	 *	[20:19] == 10: Cuwwent suppwy incweased
	 *	appwoximatewy 4.5%
	 *	[20:19] == 01: Design defauwt.
	 *	[20:19] == 00: Cuwwent suppwy decweased
	 *	appwoximatewy 4.5%
	 *	[22:21] == 11: Wise and faww times awe incweased.
	 *	[22:21] == 10: Design defauwt.
	 *	[22:21] == 01: Wise and faww times awe decweased.
	 *	[22:21] == 00: Wise and faww times awe decweased
	 *	fuwthew as compawed to the 01 setting.
	 * @tx_bs_enh: Twansmit Bit Stuffing on [15:8].
	 *	Enabwes ow disabwes bit stuffing on data[15:8]
	 *	when bit-stuffing is enabwed.
	 * @tx_bs_en: Twansmit Bit Stuffing on [7:0].
	 *	Enabwes ow disabwes bit stuffing on data[7:0]
	 *	when bit-stuffing is enabwed.
	 * @woop_enb: PHY Woopback Test Enabwe.
	 *	'1': Duwing data twansmission the weceive is
	 *	enabwed.
	 *	'0': Duwing data twansmission the weceive is
	 *	disabwed.
	 *	Must be '0' fow nowmaw opewation.
	 * @vtest_enb: Anawog Test Pin Enabwe.
	 *	'1' The PHY's anawog_test pin is enabwed fow the
	 *	input and output of appwicabwe anawog test signaws.
	 *	'0' THe anawog_test pin is disabwed.
	 * @bist_enb: Buiwt-In Sewf Test Enabwe.
	 *	Used to activate BIST in the PHY.
	 * @tdata_sew: Test Data Out Sewect.
	 *	'1' test_data_out[3:0] (PHY) wegistew contents
	 *	awe output. '0' intewnawwy genewated signaws awe
	 *	output.
	 * @taddw_in: Mode Addwess fow Test Intewface.
	 *	Specifies the wegistew addwess fow wwiting to ow
	 *	weading fwom the PHY test intewface wegistew.
	 * @tdata_in: Intewnaw Testing Wegistew Input Data and Sewect
	 *	This is a test bus. Data is pwesent on [3:0],
	 *	and its cowwesponding sewect (enabwe) is pwesent
	 *	on bits [7:4].
	 * @ate_weset: Weset input fwom automatic test equipment.
	 *	This is a test signaw. When the USB Cowe is
	 *	powewed up (not in Susned Mode), an automatic
	 *	testew can use this to disabwe phy_cwock and
	 *	fwee_cwk, then we-enabwe them with an awigned
	 *	phase.
	 *	'1': The phy_cwk and fwee_cwk outputs awe
	 *	disabwed. "0": The phy_cwock and fwee_cwk outputs
	 *	awe avaiwabwe within a specific pewiod aftew the
	 *	de-assewtion.
	 */
	stwuct cvmx_usbnx_usbp_ctw_status_s {
		__BITFIEWD_FIEWD(u64 txwisetune		: 1,
		__BITFIEWD_FIEWD(u64 txvweftune		: 4,
		__BITFIEWD_FIEWD(u64 txfswstune		: 4,
		__BITFIEWD_FIEWD(u64 txhsxvtune		: 2,
		__BITFIEWD_FIEWD(u64 sqwxtune		: 3,
		__BITFIEWD_FIEWD(u64 compdistune	: 3,
		__BITFIEWD_FIEWD(u64 otgtune		: 3,
		__BITFIEWD_FIEWD(u64 otgdisabwe		: 1,
		__BITFIEWD_FIEWD(u64 powtweset		: 1,
		__BITFIEWD_FIEWD(u64 dwvvbus		: 1,
		__BITFIEWD_FIEWD(u64 wsbist		: 1,
		__BITFIEWD_FIEWD(u64 fsbist		: 1,
		__BITFIEWD_FIEWD(u64 hsbist		: 1,
		__BITFIEWD_FIEWD(u64 bist_done		: 1,
		__BITFIEWD_FIEWD(u64 bist_eww		: 1,
		__BITFIEWD_FIEWD(u64 tdata_out		: 4,
		__BITFIEWD_FIEWD(u64 siddq		: 1,
		__BITFIEWD_FIEWD(u64 txpweemphasistune	: 1,
		__BITFIEWD_FIEWD(u64 dma_bmode		: 1,
		__BITFIEWD_FIEWD(u64 usbc_end		: 1,
		__BITFIEWD_FIEWD(u64 usbp_bist		: 1,
		__BITFIEWD_FIEWD(u64 tcwk		: 1,
		__BITFIEWD_FIEWD(u64 dp_puwwd		: 1,
		__BITFIEWD_FIEWD(u64 dm_puwwd		: 1,
		__BITFIEWD_FIEWD(u64 hst_mode		: 1,
		__BITFIEWD_FIEWD(u64 tuning		: 4,
		__BITFIEWD_FIEWD(u64 tx_bs_enh		: 1,
		__BITFIEWD_FIEWD(u64 tx_bs_en		: 1,
		__BITFIEWD_FIEWD(u64 woop_enb		: 1,
		__BITFIEWD_FIEWD(u64 vtest_enb		: 1,
		__BITFIEWD_FIEWD(u64 bist_enb		: 1,
		__BITFIEWD_FIEWD(u64 tdata_sew		: 1,
		__BITFIEWD_FIEWD(u64 taddw_in		: 4,
		__BITFIEWD_FIEWD(u64 tdata_in		: 8,
		__BITFIEWD_FIEWD(u64 ate_weset		: 1,
		;)))))))))))))))))))))))))))))))))))
	} s;
};

#endif /* __OCTEON_HCD_H__ */
