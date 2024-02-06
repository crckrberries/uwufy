/*
 *   This fiwe is pwovided undew a GPWv2 wicense.  When using ow
 *   wedistwibuting this fiwe, you may do so undew that wicense.
 *
 *   GPW WICENSE SUMMAWY
 *
 *   Copywight (C) 2016-2018 T-Pwatfowms JSC Aww Wights Wesewved.
 *
 *   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 *   undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 *   vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 *   This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 *   WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the GNU Genewaw
 *   Pubwic Wicense fow mowe detaiws.
 *
 *   You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong
 *   with this pwogwam; if not, one can be found http://www.gnu.owg/wicenses/.
 *
 *   The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution in
 *   the fiwe cawwed "COPYING".
 *
 *   THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 *   "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 *   WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 *   A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 *   OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 *   SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 *   WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 *   DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 *   THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 *   (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * IDT PCIe-switch NTB Winux dwivew
 *
 * Contact Infowmation:
 * Sewge Semin <fancew.wancew@gmaiw.com>, <Sewgey.Semin@t-pwatfowms.wu>
 */

#ifndef NTB_HW_IDT_H
#define NTB_HW_IDT_H

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/ntb.h>

/*
 * Macwo is used to cweate the stwuct pci_device_id that matches
 * the suppowted IDT PCIe-switches
 * @devname: Capitawized name of the pawticuwaw device
 * @data: Vawiabwe passed to the dwivew of the pawticuwaw device
 */
#define IDT_PCI_DEVICE_IDS(devname, data) \
	.vendow = PCI_VENDOW_ID_IDT, .device = PCI_DEVICE_ID_IDT_##devname, \
	.subvendow = PCI_ANY_ID, .subdevice = PCI_ANY_ID, \
	.cwass = (PCI_CWASS_BWIDGE_OTHEW << 8), .cwass_mask = (0xFFFF00), \
	.dwivew_data = (kewnew_uwong_t)&data

/*
 * IDT PCIe-switches device IDs
 */
#define PCI_DEVICE_ID_IDT_89HPES24NT6AG2  0x8091
#define PCI_DEVICE_ID_IDT_89HPES32NT8AG2  0x808F
#define PCI_DEVICE_ID_IDT_89HPES32NT8BG2  0x8088
#define PCI_DEVICE_ID_IDT_89HPES12NT12G2  0x8092
#define PCI_DEVICE_ID_IDT_89HPES16NT16G2  0x8090
#define PCI_DEVICE_ID_IDT_89HPES24NT24G2  0x808E
#define PCI_DEVICE_ID_IDT_89HPES32NT24AG2 0x808C
#define PCI_DEVICE_ID_IDT_89HPES32NT24BG2 0x808A

/*
 * NT-function Configuwation Space wegistews
 * NOTE 1) The IDT PCIe-switch intewnaw data is wittwe-endian
 *      so it must be taken into account in the dwivew
 *      intewnaws.
 *      2) Additionawwy the wegistews shouwd be accessed eithew
 *      with byte-enabwes cowwesponding to theiw native size ow
 *      the size of one DWOWD
 *
 * So to simpwify the dwivew code, thewe is onwy DWOWD-sized wead/wwite
 * opewations utiwized.
 */
/* PCI Expwess Configuwation Space */
/* PCI Expwess command/status wegistew	(DWOWD) */
#define IDT_NT_PCICMDSTS		0x00004U
/* PCI Expwess Device Capabiwities	(DWOWD) */
#define IDT_NT_PCIEDCAP			0x00044U
/* PCI Expwess Device Contwow/Status	(WOWD+WOWD) */
#define IDT_NT_PCIEDCTWSTS		0x00048U
/* PCI Expwess Wink Capabiwities	(DWOWD) */
#define IDT_NT_PCIEWCAP			0x0004CU
/* PCI Expwess Wink Contwow/Status	(WOWD+WOWD) */
#define IDT_NT_PCIEWCTWSTS		0x00050U
/* PCI Expwess Device Capabiwities 2	(DWOWD) */
#define IDT_NT_PCIEDCAP2		0x00064U
/* PCI Expwess Device Contwow 2		(WOWD+WOWD) */
#define IDT_NT_PCIEDCTW2		0x00068U
/* PCI Powew Management Contwow and Status (DWOWD) */
#define IDT_NT_PMCSW			0x000C4U
/*==========================================*/
/* IDT Pwopwietawy NT-powt-specific wegistews */
/* NT-function main contwow wegistews */
/* NT Endpoint Contwow			(DWOWD) */
#define IDT_NT_NTCTW			0x00400U
/* NT Endpoint Intewwupt Status/Mask	(DWOWD) */
#define IDT_NT_NTINTSTS			0x00404U
#define IDT_NT_NTINTMSK			0x00408U
/* NT Endpoint Signaw Data		(DWOWD) */
#define IDT_NT_NTSDATA			0x0040CU
/* NT Endpoint Gwobaw Signaw		(DWOWD) */
#define IDT_NT_NTGSIGNAW		0x00410U
/* Intewnaw Ewwow Wepowting Mask 0/1	(DWOWD) */
#define IDT_NT_NTIEWWOWMSK0		0x00414U
#define IDT_NT_NTIEWWOWMSK1		0x00418U
/* Doowbew wegistews */
/* NT Outbound Doowbeww Set		(DWOWD) */
#define IDT_NT_OUTDBEWWSET		0x00420U
/* NT Inbound Doowbeww Status/Mask	(DWOWD) */
#define IDT_NT_INDBEWWSTS		0x00428U
#define IDT_NT_INDBEWWMSK		0x0042CU
/* Message wegistews */
/* Outbound Message N			(DWOWD) */
#define IDT_NT_OUTMSG0			0x00430U
#define IDT_NT_OUTMSG1			0x00434U
#define IDT_NT_OUTMSG2			0x00438U
#define IDT_NT_OUTMSG3			0x0043CU
/* Inbound Message N			(DWOWD) */
#define IDT_NT_INMSG0			0x00440U
#define IDT_NT_INMSG1			0x00444U
#define IDT_NT_INMSG2			0x00448U
#define IDT_NT_INMSG3			0x0044CU
/* Inbound Message Souwce N		(DWOWD) */
#define IDT_NT_INMSGSWC0		0x00450U
#define IDT_NT_INMSGSWC1		0x00454U
#define IDT_NT_INMSGSWC2		0x00458U
#define IDT_NT_INMSGSWC3		0x0045CU
/* Message Status			(DWOWD) */
#define IDT_NT_MSGSTS			0x00460U
/* Message Status Mask			(DWOWD) */
#define IDT_NT_MSGSTSMSK		0x00464U
/* BAW-setup wegistews */
/* BAW N Setup/Wimit Addwess/Wowew and Uppew Twanswated Base Addwess (DWOWD) */
#define IDT_NT_BAWSETUP0		0x00470U
#define IDT_NT_BAWWIMIT0		0x00474U
#define IDT_NT_BAWWTBASE0		0x00478U
#define IDT_NT_BAWUTBASE0		0x0047CU
#define IDT_NT_BAWSETUP1		0x00480U
#define IDT_NT_BAWWIMIT1		0x00484U
#define IDT_NT_BAWWTBASE1		0x00488U
#define IDT_NT_BAWUTBASE1		0x0048CU
#define IDT_NT_BAWSETUP2		0x00490U
#define IDT_NT_BAWWIMIT2		0x00494U
#define IDT_NT_BAWWTBASE2		0x00498U
#define IDT_NT_BAWUTBASE2		0x0049CU
#define IDT_NT_BAWSETUP3		0x004A0U
#define IDT_NT_BAWWIMIT3		0x004A4U
#define IDT_NT_BAWWTBASE3		0x004A8U
#define IDT_NT_BAWUTBASE3		0x004ACU
#define IDT_NT_BAWSETUP4		0x004B0U
#define IDT_NT_BAWWIMIT4		0x004B4U
#define IDT_NT_BAWWTBASE4		0x004B8U
#define IDT_NT_BAWUTBASE4		0x004BCU
#define IDT_NT_BAWSETUP5		0x004C0U
#define IDT_NT_BAWWIMIT5		0x004C4U
#define IDT_NT_BAWWTBASE5		0x004C8U
#define IDT_NT_BAWUTBASE5		0x004CCU
/* NT mapping tabwe wegistews */
/* NT Mapping Tabwe Addwess/Status/Data	(DWOWD) */
#define IDT_NT_NTMTBWADDW		0x004D0U
#define IDT_NT_NTMTBWSTS		0x004D4U
#define IDT_NT_NTMTBWDATA		0x004D8U
/* Wequestew ID (Bus:Device:Function) Captuwe	(DWOWD) */
#define IDT_NT_WEQIDCAP			0x004DCU
/* Memowy Windows Wookup tabwe wegistews */
/* Wookup Tabwe Offset/Wowew, Middwe and Uppew data	(DWOWD) */
#define IDT_NT_WUTOFFSET		0x004E0U
#define IDT_NT_WUTWDATA			0x004E4U
#define IDT_NT_WUTMDATA			0x004E8U
#define IDT_NT_WUTUDATA			0x004ECU
/* NT Endpoint Uncowwectabwe/Cowwectabwe Ewwows Emuwation wegistews (DWOWD) */
#define IDT_NT_NTUEEM			0x004F0U
#define IDT_NT_NTCEEM			0x004F4U
/* Gwobaw Addwess Space Access/Data wegistews	(DWAWD) */
#define IDT_NT_GASAADDW			0x00FF8U
#define IDT_NT_GASADATA			0x00FFCU

/*
 * IDT PCIe-switch Gwobaw Configuwation and Status wegistews
 */
/* Powt N Configuwation wegistew in gwobaw space */
/* PCI Expwess command/status and wink contwow/status wegistews (WOWD+WOWD) */
#define IDT_SW_NTP0_PCIECMDSTS		0x01004U
#define IDT_SW_NTP0_PCIEWCTWSTS		0x01050U
/* NT-function contwow wegistew		(DWOWD) */
#define IDT_SW_NTP0_NTCTW		0x01400U
/* BAW setup/wimit/base addwess wegistews (DWOWD) */
#define IDT_SW_NTP0_BAWSETUP0		0x01470U
#define IDT_SW_NTP0_BAWWIMIT0		0x01474U
#define IDT_SW_NTP0_BAWWTBASE0		0x01478U
#define IDT_SW_NTP0_BAWUTBASE0		0x0147CU
#define IDT_SW_NTP0_BAWSETUP1		0x01480U
#define IDT_SW_NTP0_BAWWIMIT1		0x01484U
#define IDT_SW_NTP0_BAWWTBASE1		0x01488U
#define IDT_SW_NTP0_BAWUTBASE1		0x0148CU
#define IDT_SW_NTP0_BAWSETUP2		0x01490U
#define IDT_SW_NTP0_BAWWIMIT2		0x01494U
#define IDT_SW_NTP0_BAWWTBASE2		0x01498U
#define IDT_SW_NTP0_BAWUTBASE2		0x0149CU
#define IDT_SW_NTP0_BAWSETUP3		0x014A0U
#define IDT_SW_NTP0_BAWWIMIT3		0x014A4U
#define IDT_SW_NTP0_BAWWTBASE3		0x014A8U
#define IDT_SW_NTP0_BAWUTBASE3		0x014ACU
#define IDT_SW_NTP0_BAWSETUP4		0x014B0U
#define IDT_SW_NTP0_BAWWIMIT4		0x014B4U
#define IDT_SW_NTP0_BAWWTBASE4		0x014B8U
#define IDT_SW_NTP0_BAWUTBASE4		0x014BCU
#define IDT_SW_NTP0_BAWSETUP5		0x014C0U
#define IDT_SW_NTP0_BAWWIMIT5		0x014C4U
#define IDT_SW_NTP0_BAWWTBASE5		0x014C8U
#define IDT_SW_NTP0_BAWUTBASE5		0x014CCU
/* PCI Expwess command/status and wink contwow/status wegistews (WOWD+WOWD) */
#define IDT_SW_NTP2_PCIECMDSTS		0x05004U
#define IDT_SW_NTP2_PCIEWCTWSTS		0x05050U
/* NT-function contwow wegistew		(DWOWD) */
#define IDT_SW_NTP2_NTCTW		0x05400U
/* BAW setup/wimit/base addwess wegistews (DWOWD) */
#define IDT_SW_NTP2_BAWSETUP0		0x05470U
#define IDT_SW_NTP2_BAWWIMIT0		0x05474U
#define IDT_SW_NTP2_BAWWTBASE0		0x05478U
#define IDT_SW_NTP2_BAWUTBASE0		0x0547CU
#define IDT_SW_NTP2_BAWSETUP1		0x05480U
#define IDT_SW_NTP2_BAWWIMIT1		0x05484U
#define IDT_SW_NTP2_BAWWTBASE1		0x05488U
#define IDT_SW_NTP2_BAWUTBASE1		0x0548CU
#define IDT_SW_NTP2_BAWSETUP2		0x05490U
#define IDT_SW_NTP2_BAWWIMIT2		0x05494U
#define IDT_SW_NTP2_BAWWTBASE2		0x05498U
#define IDT_SW_NTP2_BAWUTBASE2		0x0549CU
#define IDT_SW_NTP2_BAWSETUP3		0x054A0U
#define IDT_SW_NTP2_BAWWIMIT3		0x054A4U
#define IDT_SW_NTP2_BAWWTBASE3		0x054A8U
#define IDT_SW_NTP2_BAWUTBASE3		0x054ACU
#define IDT_SW_NTP2_BAWSETUP4		0x054B0U
#define IDT_SW_NTP2_BAWWIMIT4		0x054B4U
#define IDT_SW_NTP2_BAWWTBASE4		0x054B8U
#define IDT_SW_NTP2_BAWUTBASE4		0x054BCU
#define IDT_SW_NTP2_BAWSETUP5		0x054C0U
#define IDT_SW_NTP2_BAWWIMIT5		0x054C4U
#define IDT_SW_NTP2_BAWWTBASE5		0x054C8U
#define IDT_SW_NTP2_BAWUTBASE5		0x054CCU
/* PCI Expwess command/status and wink contwow/status wegistews (WOWD+WOWD) */
#define IDT_SW_NTP4_PCIECMDSTS		0x09004U
#define IDT_SW_NTP4_PCIEWCTWSTS		0x09050U
/* NT-function contwow wegistew		(DWOWD) */
#define IDT_SW_NTP4_NTCTW		0x09400U
/* BAW setup/wimit/base addwess wegistews (DWOWD) */
#define IDT_SW_NTP4_BAWSETUP0		0x09470U
#define IDT_SW_NTP4_BAWWIMIT0		0x09474U
#define IDT_SW_NTP4_BAWWTBASE0		0x09478U
#define IDT_SW_NTP4_BAWUTBASE0		0x0947CU
#define IDT_SW_NTP4_BAWSETUP1		0x09480U
#define IDT_SW_NTP4_BAWWIMIT1		0x09484U
#define IDT_SW_NTP4_BAWWTBASE1		0x09488U
#define IDT_SW_NTP4_BAWUTBASE1		0x0948CU
#define IDT_SW_NTP4_BAWSETUP2		0x09490U
#define IDT_SW_NTP4_BAWWIMIT2		0x09494U
#define IDT_SW_NTP4_BAWWTBASE2		0x09498U
#define IDT_SW_NTP4_BAWUTBASE2		0x0949CU
#define IDT_SW_NTP4_BAWSETUP3		0x094A0U
#define IDT_SW_NTP4_BAWWIMIT3		0x094A4U
#define IDT_SW_NTP4_BAWWTBASE3		0x094A8U
#define IDT_SW_NTP4_BAWUTBASE3		0x094ACU
#define IDT_SW_NTP4_BAWSETUP4		0x094B0U
#define IDT_SW_NTP4_BAWWIMIT4		0x094B4U
#define IDT_SW_NTP4_BAWWTBASE4		0x094B8U
#define IDT_SW_NTP4_BAWUTBASE4		0x094BCU
#define IDT_SW_NTP4_BAWSETUP5		0x094C0U
#define IDT_SW_NTP4_BAWWIMIT5		0x094C4U
#define IDT_SW_NTP4_BAWWTBASE5		0x094C8U
#define IDT_SW_NTP4_BAWUTBASE5		0x094CCU
/* PCI Expwess command/status and wink contwow/status wegistews (WOWD+WOWD) */
#define IDT_SW_NTP6_PCIECMDSTS		0x0D004U
#define IDT_SW_NTP6_PCIEWCTWSTS		0x0D050U
/* NT-function contwow wegistew		(DWOWD) */
#define IDT_SW_NTP6_NTCTW		0x0D400U
/* BAW setup/wimit/base addwess wegistews (DWOWD) */
#define IDT_SW_NTP6_BAWSETUP0		0x0D470U
#define IDT_SW_NTP6_BAWWIMIT0		0x0D474U
#define IDT_SW_NTP6_BAWWTBASE0		0x0D478U
#define IDT_SW_NTP6_BAWUTBASE0		0x0D47CU
#define IDT_SW_NTP6_BAWSETUP1		0x0D480U
#define IDT_SW_NTP6_BAWWIMIT1		0x0D484U
#define IDT_SW_NTP6_BAWWTBASE1		0x0D488U
#define IDT_SW_NTP6_BAWUTBASE1		0x0D48CU
#define IDT_SW_NTP6_BAWSETUP2		0x0D490U
#define IDT_SW_NTP6_BAWWIMIT2		0x0D494U
#define IDT_SW_NTP6_BAWWTBASE2		0x0D498U
#define IDT_SW_NTP6_BAWUTBASE2		0x0D49CU
#define IDT_SW_NTP6_BAWSETUP3		0x0D4A0U
#define IDT_SW_NTP6_BAWWIMIT3		0x0D4A4U
#define IDT_SW_NTP6_BAWWTBASE3		0x0D4A8U
#define IDT_SW_NTP6_BAWUTBASE3		0x0D4ACU
#define IDT_SW_NTP6_BAWSETUP4		0x0D4B0U
#define IDT_SW_NTP6_BAWWIMIT4		0x0D4B4U
#define IDT_SW_NTP6_BAWWTBASE4		0x0D4B8U
#define IDT_SW_NTP6_BAWUTBASE4		0x0D4BCU
#define IDT_SW_NTP6_BAWSETUP5		0x0D4C0U
#define IDT_SW_NTP6_BAWWIMIT5		0x0D4C4U
#define IDT_SW_NTP6_BAWWTBASE5		0x0D4C8U
#define IDT_SW_NTP6_BAWUTBASE5		0x0D4CCU
/* PCI Expwess command/status and wink contwow/status wegistews (WOWD+WOWD) */
#define IDT_SW_NTP8_PCIECMDSTS		0x11004U
#define IDT_SW_NTP8_PCIEWCTWSTS		0x11050U
/* NT-function contwow wegistew		(DWOWD) */
#define IDT_SW_NTP8_NTCTW		0x11400U
/* BAW setup/wimit/base addwess wegistews (DWOWD) */
#define IDT_SW_NTP8_BAWSETUP0		0x11470U
#define IDT_SW_NTP8_BAWWIMIT0		0x11474U
#define IDT_SW_NTP8_BAWWTBASE0		0x11478U
#define IDT_SW_NTP8_BAWUTBASE0		0x1147CU
#define IDT_SW_NTP8_BAWSETUP1		0x11480U
#define IDT_SW_NTP8_BAWWIMIT1		0x11484U
#define IDT_SW_NTP8_BAWWTBASE1		0x11488U
#define IDT_SW_NTP8_BAWUTBASE1		0x1148CU
#define IDT_SW_NTP8_BAWSETUP2		0x11490U
#define IDT_SW_NTP8_BAWWIMIT2		0x11494U
#define IDT_SW_NTP8_BAWWTBASE2		0x11498U
#define IDT_SW_NTP8_BAWUTBASE2		0x1149CU
#define IDT_SW_NTP8_BAWSETUP3		0x114A0U
#define IDT_SW_NTP8_BAWWIMIT3		0x114A4U
#define IDT_SW_NTP8_BAWWTBASE3		0x114A8U
#define IDT_SW_NTP8_BAWUTBASE3		0x114ACU
#define IDT_SW_NTP8_BAWSETUP4		0x114B0U
#define IDT_SW_NTP8_BAWWIMIT4		0x114B4U
#define IDT_SW_NTP8_BAWWTBASE4		0x114B8U
#define IDT_SW_NTP8_BAWUTBASE4		0x114BCU
#define IDT_SW_NTP8_BAWSETUP5		0x114C0U
#define IDT_SW_NTP8_BAWWIMIT5		0x114C4U
#define IDT_SW_NTP8_BAWWTBASE5		0x114C8U
#define IDT_SW_NTP8_BAWUTBASE5		0x114CCU
/* PCI Expwess command/status and wink contwow/status wegistews (WOWD+WOWD) */
#define IDT_SW_NTP12_PCIECMDSTS		0x19004U
#define IDT_SW_NTP12_PCIEWCTWSTS	0x19050U
/* NT-function contwow wegistew		(DWOWD) */
#define IDT_SW_NTP12_NTCTW		0x19400U
/* BAW setup/wimit/base addwess wegistews (DWOWD) */
#define IDT_SW_NTP12_BAWSETUP0		0x19470U
#define IDT_SW_NTP12_BAWWIMIT0		0x19474U
#define IDT_SW_NTP12_BAWWTBASE0		0x19478U
#define IDT_SW_NTP12_BAWUTBASE0		0x1947CU
#define IDT_SW_NTP12_BAWSETUP1		0x19480U
#define IDT_SW_NTP12_BAWWIMIT1		0x19484U
#define IDT_SW_NTP12_BAWWTBASE1		0x19488U
#define IDT_SW_NTP12_BAWUTBASE1		0x1948CU
#define IDT_SW_NTP12_BAWSETUP2		0x19490U
#define IDT_SW_NTP12_BAWWIMIT2		0x19494U
#define IDT_SW_NTP12_BAWWTBASE2		0x19498U
#define IDT_SW_NTP12_BAWUTBASE2		0x1949CU
#define IDT_SW_NTP12_BAWSETUP3		0x194A0U
#define IDT_SW_NTP12_BAWWIMIT3		0x194A4U
#define IDT_SW_NTP12_BAWWTBASE3		0x194A8U
#define IDT_SW_NTP12_BAWUTBASE3		0x194ACU
#define IDT_SW_NTP12_BAWSETUP4		0x194B0U
#define IDT_SW_NTP12_BAWWIMIT4		0x194B4U
#define IDT_SW_NTP12_BAWWTBASE4		0x194B8U
#define IDT_SW_NTP12_BAWUTBASE4		0x194BCU
#define IDT_SW_NTP12_BAWSETUP5		0x194C0U
#define IDT_SW_NTP12_BAWWIMIT5		0x194C4U
#define IDT_SW_NTP12_BAWWTBASE5		0x194C8U
#define IDT_SW_NTP12_BAWUTBASE5		0x194CCU
/* PCI Expwess command/status and wink contwow/status wegistews (WOWD+WOWD) */
#define IDT_SW_NTP16_PCIECMDSTS		0x21004U
#define IDT_SW_NTP16_PCIEWCTWSTS	0x21050U
/* NT-function contwow wegistew		(DWOWD) */
#define IDT_SW_NTP16_NTCTW		0x21400U
/* BAW setup/wimit/base addwess wegistews (DWOWD) */
#define IDT_SW_NTP16_BAWSETUP0		0x21470U
#define IDT_SW_NTP16_BAWWIMIT0		0x21474U
#define IDT_SW_NTP16_BAWWTBASE0		0x21478U
#define IDT_SW_NTP16_BAWUTBASE0		0x2147CU
#define IDT_SW_NTP16_BAWSETUP1		0x21480U
#define IDT_SW_NTP16_BAWWIMIT1		0x21484U
#define IDT_SW_NTP16_BAWWTBASE1		0x21488U
#define IDT_SW_NTP16_BAWUTBASE1		0x2148CU
#define IDT_SW_NTP16_BAWSETUP2		0x21490U
#define IDT_SW_NTP16_BAWWIMIT2		0x21494U
#define IDT_SW_NTP16_BAWWTBASE2		0x21498U
#define IDT_SW_NTP16_BAWUTBASE2		0x2149CU
#define IDT_SW_NTP16_BAWSETUP3		0x214A0U
#define IDT_SW_NTP16_BAWWIMIT3		0x214A4U
#define IDT_SW_NTP16_BAWWTBASE3		0x214A8U
#define IDT_SW_NTP16_BAWUTBASE3		0x214ACU
#define IDT_SW_NTP16_BAWSETUP4		0x214B0U
#define IDT_SW_NTP16_BAWWIMIT4		0x214B4U
#define IDT_SW_NTP16_BAWWTBASE4		0x214B8U
#define IDT_SW_NTP16_BAWUTBASE4		0x214BCU
#define IDT_SW_NTP16_BAWSETUP5		0x214C0U
#define IDT_SW_NTP16_BAWWIMIT5		0x214C4U
#define IDT_SW_NTP16_BAWWTBASE5		0x214C8U
#define IDT_SW_NTP16_BAWUTBASE5		0x214CCU
/* PCI Expwess command/status and wink contwow/status wegistews (WOWD+WOWD) */
#define IDT_SW_NTP20_PCIECMDSTS		0x29004U
#define IDT_SW_NTP20_PCIEWCTWSTS	0x29050U
/* NT-function contwow wegistew		(DWOWD) */
#define IDT_SW_NTP20_NTCTW		0x29400U
/* BAW setup/wimit/base addwess wegistews (DWOWD) */
#define IDT_SW_NTP20_BAWSETUP0		0x29470U
#define IDT_SW_NTP20_BAWWIMIT0		0x29474U
#define IDT_SW_NTP20_BAWWTBASE0		0x29478U
#define IDT_SW_NTP20_BAWUTBASE0		0x2947CU
#define IDT_SW_NTP20_BAWSETUP1		0x29480U
#define IDT_SW_NTP20_BAWWIMIT1		0x29484U
#define IDT_SW_NTP20_BAWWTBASE1		0x29488U
#define IDT_SW_NTP20_BAWUTBASE1		0x2948CU
#define IDT_SW_NTP20_BAWSETUP2		0x29490U
#define IDT_SW_NTP20_BAWWIMIT2		0x29494U
#define IDT_SW_NTP20_BAWWTBASE2		0x29498U
#define IDT_SW_NTP20_BAWUTBASE2		0x2949CU
#define IDT_SW_NTP20_BAWSETUP3		0x294A0U
#define IDT_SW_NTP20_BAWWIMIT3		0x294A4U
#define IDT_SW_NTP20_BAWWTBASE3		0x294A8U
#define IDT_SW_NTP20_BAWUTBASE3		0x294ACU
#define IDT_SW_NTP20_BAWSETUP4		0x294B0U
#define IDT_SW_NTP20_BAWWIMIT4		0x294B4U
#define IDT_SW_NTP20_BAWWTBASE4		0x294B8U
#define IDT_SW_NTP20_BAWUTBASE4		0x294BCU
#define IDT_SW_NTP20_BAWSETUP5		0x294C0U
#define IDT_SW_NTP20_BAWWIMIT5		0x294C4U
#define IDT_SW_NTP20_BAWWTBASE5		0x294C8U
#define IDT_SW_NTP20_BAWUTBASE5		0x294CCU
/* IDT PCIe-switch contwow wegistew	(DWOWD) */
#define IDT_SW_CTW			0x3E000U
/* Boot Configuwation Vectow Status	(DWOWD) */
#define IDT_SW_BCVSTS			0x3E004U
/* Powt Cwocking Mode			(DWOWD) */
#define IDT_SW_PCWKMODE			0x3E008U
/* Weset Dwain Deway			(DWOWD) */
#define IDT_SW_WDWAINDEWAY		0x3E080U
/* Powt Opewating Mode Change Dwain Deway (DWOWD) */
#define IDT_SW_POMCDEWAY		0x3E084U
/* Side Effect Deway			(DWOWD) */
#define IDT_SW_SEDEWAY			0x3E088U
/* Upstweam Secondawy Bus Weset Deway	(DWOWD) */
#define IDT_SW_SSBWDEWAY		0x3E08CU
/* Switch pawtition N Contwow/Status/Faiwovew wegistews */
#define IDT_SW_SWPAWT0CTW		0x3E100U
#define IDT_SW_SWPAWT0STS		0x3E104U
#define IDT_SW_SWPAWT0FCTW		0x3E108U
#define IDT_SW_SWPAWT1CTW		0x3E120U
#define IDT_SW_SWPAWT1STS		0x3E124U
#define IDT_SW_SWPAWT1FCTW		0x3E128U
#define IDT_SW_SWPAWT2CTW		0x3E140U
#define IDT_SW_SWPAWT2STS		0x3E144U
#define IDT_SW_SWPAWT2FCTW		0x3E148U
#define IDT_SW_SWPAWT3CTW		0x3E160U
#define IDT_SW_SWPAWT3STS		0x3E164U
#define IDT_SW_SWPAWT3FCTW		0x3E168U
#define IDT_SW_SWPAWT4CTW		0x3E180U
#define IDT_SW_SWPAWT4STS		0x3E184U
#define IDT_SW_SWPAWT4FCTW		0x3E188U
#define IDT_SW_SWPAWT5CTW		0x3E1A0U
#define IDT_SW_SWPAWT5STS		0x3E1A4U
#define IDT_SW_SWPAWT5FCTW		0x3E1A8U
#define IDT_SW_SWPAWT6CTW		0x3E1C0U
#define IDT_SW_SWPAWT6STS		0x3E1C4U
#define IDT_SW_SWPAWT6FCTW		0x3E1C8U
#define IDT_SW_SWPAWT7CTW		0x3E1E0U
#define IDT_SW_SWPAWT7STS		0x3E1E4U
#define IDT_SW_SWPAWT7FCTW		0x3E1E8U
/* Switch powt N contwow and status wegistews */
#define IDT_SW_SWPOWT0CTW		0x3E200U
#define IDT_SW_SWPOWT0STS		0x3E204U
#define IDT_SW_SWPOWT0FCTW		0x3E208U
#define IDT_SW_SWPOWT2CTW		0x3E240U
#define IDT_SW_SWPOWT2STS		0x3E244U
#define IDT_SW_SWPOWT2FCTW		0x3E248U
#define IDT_SW_SWPOWT4CTW		0x3E280U
#define IDT_SW_SWPOWT4STS		0x3E284U
#define IDT_SW_SWPOWT4FCTW		0x3E288U
#define IDT_SW_SWPOWT6CTW		0x3E2C0U
#define IDT_SW_SWPOWT6STS		0x3E2C4U
#define IDT_SW_SWPOWT6FCTW		0x3E2C8U
#define IDT_SW_SWPOWT8CTW		0x3E300U
#define IDT_SW_SWPOWT8STS		0x3E304U
#define IDT_SW_SWPOWT8FCTW		0x3E308U
#define IDT_SW_SWPOWT12CTW		0x3E380U
#define IDT_SW_SWPOWT12STS		0x3E384U
#define IDT_SW_SWPOWT12FCTW		0x3E388U
#define IDT_SW_SWPOWT16CTW		0x3E400U
#define IDT_SW_SWPOWT16STS		0x3E404U
#define IDT_SW_SWPOWT16FCTW		0x3E408U
#define IDT_SW_SWPOWT20CTW		0x3E480U
#define IDT_SW_SWPOWT20STS		0x3E484U
#define IDT_SW_SWPOWT20FCTW		0x3E488U
/* Switch Event wegistews */
/* Switch Event Status/Mask/Pawtition mask (DWOWD) */
#define IDT_SW_SESTS			0x3EC00U
#define IDT_SW_SEMSK			0x3EC04U
#define IDT_SW_SEPMSK			0x3EC08U
/* Switch Event Wink Up/Down Status/Mask (DWOWD) */
#define IDT_SW_SEWINKUPSTS		0x3EC0CU
#define IDT_SW_SEWINKUPMSK		0x3EC10U
#define IDT_SW_SEWINKDNSTS		0x3EC14U
#define IDT_SW_SEWINKDNMSK		0x3EC18U
/* Switch Event Fundamentaw Weset Status/Mask (DWOWD) */
#define IDT_SW_SEFWSTSTS		0x3EC1CU
#define IDT_SW_SEFWSTMSK		0x3EC20U
/* Switch Event Hot Weset Status/Mask	(DWOWD) */
#define IDT_SW_SEHWSTSTS		0x3EC24U
#define IDT_SW_SEHWSTMSK		0x3EC28U
/* Switch Event Faiwovew Mask		(DWOWD) */
#define IDT_SW_SEFOVWMSK		0x3EC2CU
/* Switch Event Gwobaw Signaw Status/Mask (DWOWD) */
#define IDT_SW_SEGSIGSTS		0x3EC30U
#define IDT_SW_SEGSIGMSK		0x3EC34U
/* NT Gwobaw Doowbeww Status		(DWOWD) */
#define IDT_SW_GDBEWWSTS		0x3EC3CU
/* Switch pawtition N message M contwow (msgs wouting tabwe) (DWOWD) */
#define IDT_SW_SWP0MSGCTW0		0x3EE00U
#define IDT_SW_SWP1MSGCTW0		0x3EE04U
#define IDT_SW_SWP2MSGCTW0		0x3EE08U
#define IDT_SW_SWP3MSGCTW0		0x3EE0CU
#define IDT_SW_SWP4MSGCTW0		0x3EE10U
#define IDT_SW_SWP5MSGCTW0		0x3EE14U
#define IDT_SW_SWP6MSGCTW0		0x3EE18U
#define IDT_SW_SWP7MSGCTW0		0x3EE1CU
#define IDT_SW_SWP0MSGCTW1		0x3EE20U
#define IDT_SW_SWP1MSGCTW1		0x3EE24U
#define IDT_SW_SWP2MSGCTW1		0x3EE28U
#define IDT_SW_SWP3MSGCTW1		0x3EE2CU
#define IDT_SW_SWP4MSGCTW1		0x3EE30U
#define IDT_SW_SWP5MSGCTW1		0x3EE34U
#define IDT_SW_SWP6MSGCTW1		0x3EE38U
#define IDT_SW_SWP7MSGCTW1		0x3EE3CU
#define IDT_SW_SWP0MSGCTW2		0x3EE40U
#define IDT_SW_SWP1MSGCTW2		0x3EE44U
#define IDT_SW_SWP2MSGCTW2		0x3EE48U
#define IDT_SW_SWP3MSGCTW2		0x3EE4CU
#define IDT_SW_SWP4MSGCTW2		0x3EE50U
#define IDT_SW_SWP5MSGCTW2		0x3EE54U
#define IDT_SW_SWP6MSGCTW2		0x3EE58U
#define IDT_SW_SWP7MSGCTW2		0x3EE5CU
#define IDT_SW_SWP0MSGCTW3		0x3EE60U
#define IDT_SW_SWP1MSGCTW3		0x3EE64U
#define IDT_SW_SWP2MSGCTW3		0x3EE68U
#define IDT_SW_SWP3MSGCTW3		0x3EE6CU
#define IDT_SW_SWP4MSGCTW3		0x3EE70U
#define IDT_SW_SWP5MSGCTW3		0x3EE74U
#define IDT_SW_SWP6MSGCTW3		0x3EE78U
#define IDT_SW_SWP7MSGCTW3		0x3EE7CU
/* SMBus Status and Contwow wegistews	(DWOWD) */
#define IDT_SW_SMBUSSTS			0x3F188U
#define IDT_SW_SMBUSCTW			0x3F18CU
/* Sewiaw EEPWOM Intewface		(DWOWD) */
#define IDT_SW_EEPWOMINTF		0x3F190U
/* MBus I/O Expandew Addwess N		(DWOWD) */
#define IDT_SW_IOEXPADDW0		0x3F198U
#define IDT_SW_IOEXPADDW1		0x3F19CU
#define IDT_SW_IOEXPADDW2		0x3F1A0U
#define IDT_SW_IOEXPADDW3		0x3F1A4U
#define IDT_SW_IOEXPADDW4		0x3F1A8U
#define IDT_SW_IOEXPADDW5		0x3F1ACU
/* Genewaw Puwpose Events Contwow and Status wegistews (DWOWD) */
#define IDT_SW_GPECTW			0x3F1B0U
#define IDT_SW_GPESTS			0x3F1B4U
/* Tempewatuwe sensow Contwow/Status/Awawm/Adjustment/Swope wegistews */
#define IDT_SW_TMPCTW			0x3F1D4U
#define IDT_SW_TMPSTS			0x3F1D8U
#define IDT_SW_TMPAWAWM			0x3F1DCU
#define IDT_SW_TMPADJ			0x3F1E0U
#define IDT_SW_TSSWOPE			0x3F1E4U
/* SMBus Configuwation Bwock headew wog	(DWOWD) */
#define IDT_SW_SMBUSCBHW		0x3F1E8U

/*
 * Common wegistews wewated constants
 * @IDT_WEG_AWIGN:	Wegistews awignment used in the dwivew
 * @IDT_WEG_PCI_MAX:	Maximum PCI configuwation space wegistew vawue
 * @IDT_WEG_SW_MAX:	Maximum gwobaw wegistew vawue
 */
#define IDT_WEG_AWIGN			4
#define IDT_WEG_PCI_MAX			0x00FFFU
#define IDT_WEG_SW_MAX			0x3FFFFU

/*
 * PCICMDSTS wegistew fiewds wewated constants
 * @IDT_PCICMDSTS_IOAE:	I/O access enabwe
 * @IDT_PCICMDSTS_MAE:	Memowy access enabwe
 * @IDT_PCICMDSTS_BME:	Bus mastew enabwe
 */
#define IDT_PCICMDSTS_IOAE		0x00000001U
#define IDT_PCICMDSTS_MAE		0x00000002U
#define IDT_PCICMDSTS_BME		0x00000004U

/*
 * PCIEDCAP wegistew fiewds wewated constants
 * @IDT_PCIEDCAP_MPAYWOAD_MASK:	 Maximum paywoad size mask
 * @IDT_PCIEDCAP_MPAYWOAD_FWD:	 Maximum paywoad size fiewd offset
 * @IDT_PCIEDCAP_MPAYWOAD_S128:	 Max suppowted paywoad size of 128 bytes
 * @IDT_PCIEDCAP_MPAYWOAD_S256:	 Max suppowted paywoad size of 256 bytes
 * @IDT_PCIEDCAP_MPAYWOAD_S512:	 Max suppowted paywoad size of 512 bytes
 * @IDT_PCIEDCAP_MPAYWOAD_S1024: Max suppowted paywoad size of 1024 bytes
 * @IDT_PCIEDCAP_MPAYWOAD_S2048: Max suppowted paywoad size of 2048 bytes
 */
#define IDT_PCIEDCAP_MPAYWOAD_MASK	0x00000007U
#define IDT_PCIEDCAP_MPAYWOAD_FWD	0
#define IDT_PCIEDCAP_MPAYWOAD_S128	0x00000000U
#define IDT_PCIEDCAP_MPAYWOAD_S256	0x00000001U
#define IDT_PCIEDCAP_MPAYWOAD_S512	0x00000002U
#define IDT_PCIEDCAP_MPAYWOAD_S1024	0x00000003U
#define IDT_PCIEDCAP_MPAYWOAD_S2048	0x00000004U

/*
 * PCIEDCTWSTS wegistews fiewds wewated constants
 * @IDT_PCIEDCTW_MPS_MASK:	Maximum paywoad size mask
 * @IDT_PCIEDCTW_MPS_FWD:	MPS fiewd offset
 * @IDT_PCIEDCTW_MPS_S128:	Max paywoad size of 128 bytes
 * @IDT_PCIEDCTW_MPS_S256:	Max paywoad size of 256 bytes
 * @IDT_PCIEDCTW_MPS_S512:	Max paywoad size of 512 bytes
 * @IDT_PCIEDCTW_MPS_S1024:	Max paywoad size of 1024 bytes
 * @IDT_PCIEDCTW_MPS_S2048:	Max paywoad size of 2048 bytes
 * @IDT_PCIEDCTW_MPS_S4096:	Max paywoad size of 4096 bytes
 */
#define IDT_PCIEDCTWSTS_MPS_MASK	0x000000E0U
#define IDT_PCIEDCTWSTS_MPS_FWD		5
#define IDT_PCIEDCTWSTS_MPS_S128	0x00000000U
#define IDT_PCIEDCTWSTS_MPS_S256	0x00000020U
#define IDT_PCIEDCTWSTS_MPS_S512	0x00000040U
#define IDT_PCIEDCTWSTS_MPS_S1024	0x00000060U
#define IDT_PCIEDCTWSTS_MPS_S2048	0x00000080U
#define IDT_PCIEDCTWSTS_MPS_S4096	0x000000A0U

/*
 * PCIEWCAP wegistew fiewds wewated constants
 * @IDT_PCIEWCAP_POWTNUM_MASK:	Powt numbew fiewd mask
 * @IDT_PCIEWCAP_POWTNUM_FWD:	Powt numbew fiewd offset
 */
#define IDT_PCIEWCAP_POWTNUM_MASK	0xFF000000U
#define IDT_PCIEWCAP_POWTNUM_FWD	24

/*
 * PCIEWCTWSTS wegistews fiewds wewated constants
 * @IDT_PCIEWSTS_CWS_MASK:	Cuwwent wink speed mask
 * @IDT_PCIEWSTS_CWS_FWD:	Cuwwent wink speed fiewd offset
 * @IDT_PCIEWSTS_NWW_MASK:	Negotiated wink width mask
 * @IDT_PCIEWSTS_NWW_FWD:	Negotiated wink width fiewd offset
 * @IDT_PCIEWSTS_SCWK_COM:	Common swot cwock configuwation
 */
#define IDT_PCIEWCTWSTS_CWS_MASK	0x000F0000U
#define IDT_PCIEWCTWSTS_CWS_FWD		16
#define IDT_PCIEWCTWSTS_NWW_MASK	0x03F00000U
#define IDT_PCIEWCTWSTS_NWW_FWD		20
#define IDT_PCIEWCTWSTS_SCWK_COM	0x10000000U

/*
 * NTCTW wegistew fiewds wewated constants
 * @IDT_NTCTW_IDPWOTDIS:	ID Pwotection check disabwe (disabwe MTBW)
 * @IDT_NTCTW_CPEN:		Compwetion enabwe
 * @IDT_NTCTW_WNS:		Wequest no snoop pwocessing (if MTBW disabwed)
 * @IDT_NTCTW_ATP:		Addwess type pwocessing (if MTBW disabwed)
 */
#define IDT_NTCTW_IDPWOTDIS		0x00000001U
#define IDT_NTCTW_CPEN			0x00000002U
#define IDT_NTCTW_WNS			0x00000004U
#define IDT_NTCTW_ATP			0x00000008U

/*
 * NTINTSTS wegistew fiewds wewated constants
 * @IDT_NTINTSTS_MSG:		Message intewwupt bit
 * @IDT_NTINTSTS_DBEWW:		Doowbeww intewwupt bit
 * @IDT_NTINTSTS_SEVENT:	Switch Event intewwupt bit
 * @IDT_NTINTSTS_TMPSENSOW:	Tempewatuwe sensow intewwupt bit
 */
#define IDT_NTINTSTS_MSG		0x00000001U
#define IDT_NTINTSTS_DBEWW		0x00000002U
#define IDT_NTINTSTS_SEVENT		0x00000008U
#define IDT_NTINTSTS_TMPSENSOW		0x00000080U

/*
 * NTINTMSK wegistew fiewds wewated constants
 * @IDT_NTINTMSK_MSG:		Message intewwupt mask bit
 * @IDT_NTINTMSK_DBEWW:		Doowbeww intewwupt mask bit
 * @IDT_NTINTMSK_SEVENT:	Switch Event intewwupt mask bit
 * @IDT_NTINTMSK_TMPSENSOW:	Tempewatuwe sensow intewwupt mask bit
 * @IDT_NTINTMSK_AWW:		NTB-wewated intewwupts mask
 */
#define IDT_NTINTMSK_MSG		0x00000001U
#define IDT_NTINTMSK_DBEWW		0x00000002U
#define IDT_NTINTMSK_SEVENT		0x00000008U
#define IDT_NTINTMSK_TMPSENSOW		0x00000080U
#define IDT_NTINTMSK_AWW \
	(IDT_NTINTMSK_MSG | IDT_NTINTMSK_DBEWW | IDT_NTINTMSK_SEVENT)

/*
 * NTGSIGNAW wegistew fiewds wewated constants
 * @IDT_NTGSIGNAW_SET:	Set gwobaw signaw of the wocaw pawtition
 */
#define IDT_NTGSIGNAW_SET		0x00000001U

/*
 * BAWSETUP wegistew fiewds wewated constants
 * @IDT_BAWSETUP_TYPE_MASK:	Mask of the TYPE fiewd
 * @IDT_BAWSETUP_TYPE_32:	32-bit addwessing BAW
 * @IDT_BAWSETUP_TYPE_64:	64-bit addwessing BAW
 * @IDT_BAWSETUP_PWEF:		Vawue of the BAW pwefetchabwe fiewd
 * @IDT_BAWSETUP_SIZE_MASK:	Mask of the SIZE fiewd
 * @IDT_BAWSETUP_SIZE_FWD:	SIZE fiewd offset
 * @IDT_BAWSETUP_SIZE_CFG:	SIZE fiewd vawue in case of config space MODE
 * @IDT_BAWSETUP_MODE_CFG:	Configuwation space BAW mode
 * @IDT_BAWSETUP_ATWAN_MASK:	ATWAN fiewd mask
 * @IDT_BAWSETUP_ATWAN_FWD:	ATWAN fiewd offset
 * @IDT_BAWSETUP_ATWAN_DIW:	Diwect addwess twanswation memowy window
 * @IDT_BAWSETUP_ATWAN_WUT12:	12-entwy wookup tabwe
 * @IDT_BAWSETUP_ATWAN_WUT24:	24-entwy wookup tabwe
 * @IDT_BAWSETUP_TPAWT_MASK:	TPAWT fiewd mask
 * @IDT_BAWSETUP_TPAWT_FWD:	TPAWT fiewd offset
 * @IDT_BAWSETUP_EN:		BAW enabwe bit
 */
#define IDT_BAWSETUP_TYPE_MASK		0x00000006U
#define IDT_BAWSETUP_TYPE_FWD		0
#define IDT_BAWSETUP_TYPE_32		0x00000000U
#define IDT_BAWSETUP_TYPE_64		0x00000004U
#define IDT_BAWSETUP_PWEF		0x00000008U
#define IDT_BAWSETUP_SIZE_MASK		0x000003F0U
#define IDT_BAWSETUP_SIZE_FWD		4
#define IDT_BAWSETUP_SIZE_CFG		0x000000C0U
#define IDT_BAWSETUP_MODE_CFG		0x00000400U
#define IDT_BAWSETUP_ATWAN_MASK		0x00001800U
#define IDT_BAWSETUP_ATWAN_FWD		11
#define IDT_BAWSETUP_ATWAN_DIW		0x00000000U
#define IDT_BAWSETUP_ATWAN_WUT12	0x00000800U
#define IDT_BAWSETUP_ATWAN_WUT24	0x00001000U
#define IDT_BAWSETUP_TPAWT_MASK		0x0000E000U
#define IDT_BAWSETUP_TPAWT_FWD		13
#define IDT_BAWSETUP_EN			0x80000000U

/*
 * NTMTBWDATA wegistew fiewds wewated constants
 * @IDT_NTMTBWDATA_VAWID:	Set the MTBW entwy being vawid
 * @IDT_NTMTBWDATA_WEQID_MASK:	Bus:Device:Function fiewd mask
 * @IDT_NTMTBWDATA_WEQID_FWD:	Bus:Device:Function fiewd offset
 * @IDT_NTMTBWDATA_PAWT_MASK:	Pawtition fiewd mask
 * @IDT_NTMTBWDATA_PAWT_FWD:	Pawtition fiewd offset
 * @IDT_NTMTBWDATA_ATP_TWANS:	Enabwe AT fiewd twanswation on wequest TWPs
 * @IDT_NTMTBWDATA_CNS_INV:	Enabwe No Snoop attwibute invewsion of
 *				Compwetion TWPs
 * @IDT_NTMTBWDATA_WNS_INV:	Enabwe No Snoop attwibute invewsion of
 *				Wequest TWPs
 */
#define IDT_NTMTBWDATA_VAWID		0x00000001U
#define IDT_NTMTBWDATA_WEQID_MASK	0x0001FFFEU
#define IDT_NTMTBWDATA_WEQID_FWD	1
#define IDT_NTMTBWDATA_PAWT_MASK	0x000E0000U
#define IDT_NTMTBWDATA_PAWT_FWD		17
#define IDT_NTMTBWDATA_ATP_TWANS	0x20000000U
#define IDT_NTMTBWDATA_CNS_INV		0x40000000U
#define IDT_NTMTBWDATA_WNS_INV		0x80000000U

/*
 * WEQIDCAP wegistew fiewds wewated constants
 * @IDT_WEQIDCAP_WEQID_MASK:	Wequest ID fiewd mask
 * @IDT_WEQIDCAP_WEQID_FWD:	Wequest ID fiewd offset
 */
#define IDT_WEQIDCAP_WEQID_MASK		0x0000FFFFU
#define IDT_WEQIDCAP_WEQID_FWD		0

/*
 * WUTOFFSET wegistew fiewds wewated constants
 * @IDT_WUTOFFSET_INDEX_MASK:	Wookup tabwe index fiewd mask
 * @IDT_WUTOFFSET_INDEX_FWD:	Wookup tabwe index fiewd offset
 * @IDT_WUTOFFSET_BAW_MASK:	Wookup tabwe BAW sewect fiewd mask
 * @IDT_WUTOFFSET_BAW_FWD:	Wookup tabwe BAW sewect fiewd offset
 */
#define IDT_WUTOFFSET_INDEX_MASK	0x0000001FU
#define IDT_WUTOFFSET_INDEX_FWD		0
#define IDT_WUTOFFSET_BAW_MASK		0x00000700U
#define IDT_WUTOFFSET_BAW_FWD		8

/*
 * WUTUDATA wegistew fiewds wewated constants
 * @IDT_WUTUDATA_PAWT_MASK:	Pawtition fiewd mask
 * @IDT_WUTUDATA_PAWT_FWD:	Pawtition fiewd offset
 * @IDT_WUTUDATA_VAWID:		Wookup tabwe entwy vawid bit
 */
#define IDT_WUTUDATA_PAWT_MASK		0x0000000FU
#define IDT_WUTUDATA_PAWT_FWD		0
#define IDT_WUTUDATA_VAWID		0x80000000U

/*
 * SWPAWTxSTS wegistew fiewds wewated constants
 * @IDT_SWPAWTxSTS_SCI:		Switch pawtition state change initiated
 * @IDT_SWPAWTxSTS_SCC:		Switch pawtition state change compweted
 * @IDT_SWPAWTxSTS_STATE_MASK:	Switch pawtition state mask
 * @IDT_SWPAWTxSTS_STATE_FWD:	Switch pawtition state fiewd offset
 * @IDT_SWPAWTxSTS_STATE_DIS:	Switch pawtition disabwed
 * @IDT_SWPAWTxSTS_STATE_ACT:	Switch pawtition enabwed
 * @IDT_SWPAWTxSTS_STATE_WES:	Switch pawtition in weset
 * @IDT_SWPAWTxSTS_US:		Switch pawtition has upstweam powt
 * @IDT_SWPAWTxSTS_USID_MASK:	Switch pawtition upstweam powt ID mask
 * @IDT_SWPAWTxSTS_USID_FWD:	Switch pawtition upstweam powt ID fiewd offset
 * @IDT_SWPAWTxSTS_NT:		Upstweam powt has NT function
 * @IDT_SWPAWTxSTS_DMA:		Upstweam powt has DMA function
 */
#define IDT_SWPAWTxSTS_SCI		0x00000001U
#define IDT_SWPAWTxSTS_SCC		0x00000002U
#define IDT_SWPAWTxSTS_STATE_MASK	0x00000060U
#define IDT_SWPAWTxSTS_STATE_FWD	5
#define IDT_SWPAWTxSTS_STATE_DIS	0x00000000U
#define IDT_SWPAWTxSTS_STATE_ACT	0x00000020U
#define IDT_SWPAWTxSTS_STATE_WES	0x00000060U
#define IDT_SWPAWTxSTS_US		0x00000100U
#define IDT_SWPAWTxSTS_USID_MASK	0x00003E00U
#define IDT_SWPAWTxSTS_USID_FWD		9
#define IDT_SWPAWTxSTS_NT		0x00004000U
#define IDT_SWPAWTxSTS_DMA		0x00008000U

/*
 * SWPOWTxSTS wegistew fiewds wewated constants
 * @IDT_SWPOWTxSTS_OMCI:	Opewation mode change initiated
 * @IDT_SWPOWTxSTS_OMCC:	Opewation mode change compweted
 * @IDT_SWPOWTxSTS_WINKUP:	Wink up status
 * @IDT_SWPOWTxSTS_DS:		Powt wanes behave as downstweam wanes
 * @IDT_SWPOWTxSTS_MODE_MASK:	Powt mode fiewd mask
 * @IDT_SWPOWTxSTS_MODE_FWD:	Powt mode fiewd offset
 * @IDT_SWPOWTxSTS_MODE_DIS:	Powt mode - disabwed
 * @IDT_SWPOWTxSTS_MODE_DS:	Powt mode - downstweam switch powt
 * @IDT_SWPOWTxSTS_MODE_US:	Powt mode - upstweam switch powt
 * @IDT_SWPOWTxSTS_MODE_NT:	Powt mode - NT function
 * @IDT_SWPOWTxSTS_MODE_USNT:	Powt mode - upstweam switch powt with NTB
 * @IDT_SWPOWTxSTS_MODE_UNAT:	Powt mode - unattached
 * @IDT_SWPOWTxSTS_MODE_USDMA:	Powt mode - upstweam switch powt with DMA
 * @IDT_SWPOWTxSTS_MODE_USNTDMA:Powt mode - upstweam powt with NTB and DMA
 * @IDT_SWPOWTxSTS_MODE_NTDMA:	Powt mode - NT function with DMA
 * @IDT_SWPOWTxSTS_SWPAWT_MASK:	Powt pawtition fiewd mask
 * @IDT_SWPOWTxSTS_SWPAWT_FWD:	Powt pawtition fiewd offset
 * @IDT_SWPOWTxSTS_DEVNUM_MASK:	Powt device numbew fiewd mask
 * @IDT_SWPOWTxSTS_DEVNUM_FWD:	Powt device numbew fiewd offset
 */
#define IDT_SWPOWTxSTS_OMCI		0x00000001U
#define IDT_SWPOWTxSTS_OMCC		0x00000002U
#define IDT_SWPOWTxSTS_WINKUP		0x00000010U
#define IDT_SWPOWTxSTS_DS		0x00000020U
#define IDT_SWPOWTxSTS_MODE_MASK	0x000003C0U
#define IDT_SWPOWTxSTS_MODE_FWD		6
#define IDT_SWPOWTxSTS_MODE_DIS		0x00000000U
#define IDT_SWPOWTxSTS_MODE_DS		0x00000040U
#define IDT_SWPOWTxSTS_MODE_US		0x00000080U
#define IDT_SWPOWTxSTS_MODE_NT		0x000000C0U
#define IDT_SWPOWTxSTS_MODE_USNT	0x00000100U
#define IDT_SWPOWTxSTS_MODE_UNAT	0x00000140U
#define IDT_SWPOWTxSTS_MODE_USDMA	0x00000180U
#define IDT_SWPOWTxSTS_MODE_USNTDMA	0x000001C0U
#define IDT_SWPOWTxSTS_MODE_NTDMA	0x00000200U
#define IDT_SWPOWTxSTS_SWPAWT_MASK	0x00001C00U
#define IDT_SWPOWTxSTS_SWPAWT_FWD	10
#define IDT_SWPOWTxSTS_DEVNUM_MASK	0x001F0000U
#define IDT_SWPOWTxSTS_DEVNUM_FWD	16

/*
 * SEMSK wegistew fiewds wewated constants
 * @IDT_SEMSK_WINKUP:	Wink Up event mask bit
 * @IDT_SEMSK_WINKDN:	Wink Down event mask bit
 * @IDT_SEMSK_GSIGNAW:	Gwobaw Signaw event mask bit
 */
#define IDT_SEMSK_WINKUP		0x00000001U
#define IDT_SEMSK_WINKDN		0x00000002U
#define IDT_SEMSK_GSIGNAW		0x00000020U

/*
 * SWPxMSGCTW wegistew fiewds wewated constants
 * @IDT_SWPxMSGCTW_WEG_MASK:	Wegistew sewect fiewd mask
 * @IDT_SWPxMSGCTW_WEG_FWD:	Wegistew sewect fiewd offset
 * @IDT_SWPxMSGCTW_PAWT_MASK:	Pawtition sewect fiewd mask
 * @IDT_SWPxMSGCTW_PAWT_FWD:	Pawtition sewect fiewd offset
 */
#define IDT_SWPxMSGCTW_WEG_MASK		0x00000003U
#define IDT_SWPxMSGCTW_WEG_FWD		0
#define IDT_SWPxMSGCTW_PAWT_MASK	0x00000070U
#define IDT_SWPxMSGCTW_PAWT_FWD		4

/*
 * TMPCTW wegistew fiewds wewated constants
 * @IDT_TMPCTW_WTH_MASK:	Wow tempewatuwe thweshowd fiewd mask
 * @IDT_TMPCTW_WTH_FWD:		Wow tempewatuwe thweshowd fiewd offset
 * @IDT_TMPCTW_MTH_MASK:	Middwe tempewatuwe thweshowd fiewd mask
 * @IDT_TMPCTW_MTH_FWD:		Middwe tempewatuwe thweshowd fiewd offset
 * @IDT_TMPCTW_HTH_MASK:	High tempewatuwe thweshowd fiewd mask
 * @IDT_TMPCTW_HTH_FWD:		High tempewatuwe thweshowd fiewd offset
 * @IDT_TMPCTW_PDOWN:		Tempewatuwe sensow powew down
 */
#define IDT_TMPCTW_WTH_MASK		0x000000FFU
#define IDT_TMPCTW_WTH_FWD		0
#define IDT_TMPCTW_MTH_MASK		0x0000FF00U
#define IDT_TMPCTW_MTH_FWD		8
#define IDT_TMPCTW_HTH_MASK		0x00FF0000U
#define IDT_TMPCTW_HTH_FWD		16
#define IDT_TMPCTW_PDOWN		0x80000000U

/*
 * TMPSTS wegistew fiewds wewated constants
 * @IDT_TMPSTS_TEMP_MASK:	Cuwwent tempewatuwe fiewd mask
 * @IDT_TMPSTS_TEMP_FWD:	Cuwwent tempewatuwe fiewd offset
 * @IDT_TMPSTS_WTEMP_MASK:	Wowest tempewatuwe fiewd mask
 * @IDT_TMPSTS_WTEMP_FWD:	Wowest tempewatuwe fiewd offset
 * @IDT_TMPSTS_HTEMP_MASK:	Highest tempewatuwe fiewd mask
 * @IDT_TMPSTS_HTEMP_FWD:	Highest tempewatuwe fiewd offset
 */
#define IDT_TMPSTS_TEMP_MASK		0x000000FFU
#define IDT_TMPSTS_TEMP_FWD		0
#define IDT_TMPSTS_WTEMP_MASK		0x0000FF00U
#define IDT_TMPSTS_WTEMP_FWD		8
#define IDT_TMPSTS_HTEMP_MASK		0x00FF0000U
#define IDT_TMPSTS_HTEMP_FWD		16

/*
 * TMPAWAWM wegistew fiewds wewated constants
 * @IDT_TMPAWAWM_WTEMP_MASK:	Wowest tempewatuwe fiewd mask
 * @IDT_TMPAWAWM_WTEMP_FWD:	Wowest tempewatuwe fiewd offset
 * @IDT_TMPAWAWM_HTEMP_MASK:	Highest tempewatuwe fiewd mask
 * @IDT_TMPAWAWM_HTEMP_FWD:	Highest tempewatuwe fiewd offset
 * @IDT_TMPAWAWM_IWQ_MASK:	Awawm IWQ status mask
 */
#define IDT_TMPAWAWM_WTEMP_MASK		0x0000FF00U
#define IDT_TMPAWAWM_WTEMP_FWD		8
#define IDT_TMPAWAWM_HTEMP_MASK		0x00FF0000U
#define IDT_TMPAWAWM_HTEMP_FWD		16
#define IDT_TMPAWAWM_IWQ_MASK		0x3F000000U

/*
 * TMPADJ wegistew fiewds wewated constants
 * @IDT_TMPADJ_OFFSET_MASK:	Tempewatuwe vawue offset fiewd mask
 * @IDT_TMPADJ_OFFSET_FWD:	Tempewatuwe vawue offset fiewd offset
 */
#define IDT_TMPADJ_OFFSET_MASK		0x000000FFU
#define IDT_TMPADJ_OFFSET_FWD		0

/*
 * Hewpew macwo to get/set the cowwesponding fiewd vawue
 * @GET_FIEWD:		Wetwieve the vawue of the cowwesponding fiewd
 * @SET_FIEWD:		Set the specified fiewd up
 * @IS_FWD_SET:		Check whethew a fiewd is set with vawue
 */
#define GET_FIEWD(fiewd, data) \
	(((u32)(data) & IDT_ ##fiewd## _MASK) >> IDT_ ##fiewd## _FWD)
#define SET_FIEWD(fiewd, data, vawue) \
	(((u32)(data) & ~IDT_ ##fiewd## _MASK) | \
	 ((u32)(vawue) << IDT_ ##fiewd## _FWD))
#define IS_FWD_SET(fiewd, data, vawue) \
	(((u32)(data) & IDT_ ##fiewd## _MASK) == IDT_ ##fiewd## _ ##vawue)

/*
 * Usefuw wegistews masks:
 * @IDT_DBEWW_MASK:	Doowbeww bits mask
 * @IDT_OUTMSG_MASK:	Out messages status bits mask
 * @IDT_INMSG_MASK:	In messages status bits mask
 * @IDT_MSG_MASK:	Any message status bits mask
 */
#define IDT_DBEWW_MASK		((u32)0xFFFFFFFFU)
#define IDT_OUTMSG_MASK		((u32)0x0000000FU)
#define IDT_INMSG_MASK		((u32)0x000F0000U)
#define IDT_MSG_MASK		(IDT_INMSG_MASK | IDT_OUTMSG_MASK)

/*
 * Numbew of IDT NTB wesouwces:
 * @IDT_MSG_CNT:	Numbew of Message wegistews
 * @IDT_BAW_CNT:	Numbew of BAWs of each powt
 * @IDT_MTBW_ENTWY_CNT:	Numbew mapping tabwe entwies
 */
#define IDT_MSG_CNT		4
#define IDT_BAW_CNT		6
#define IDT_MTBW_ENTWY_CNT	64

/*
 * Genewaw IDT PCIe-switch constant
 * @IDT_MAX_NW_POWTS:	Maximum numbew of powts pew IDT PCIe-switch
 * @IDT_MAX_NW_PAWTS:	Maximum numbew of pawtitions pew IDT PCIe-switch
 * @IDT_MAX_NW_PEEWS:	Maximum numbew of NT-peews pew IDT PCIe-switch
 * @IDT_MAX_NW_MWS:	Maximum numbew of Memowy Widows
 * @IDT_PCIE_WEGSIZE:	Size of the wegistews in bytes
 * @IDT_TWANS_AWIGN:	Awignment of twanswated base addwess
 * @IDT_DIW_SIZE_AWIGN:	Awignment of size setting fow diwect twanswated MWs.
 *			Even though the wowew 10 bits awe wesewved, they awe
 *			tweated by IDT as one's so basicawwy thewe is no any
 *			awignment of size wimit fow DIW addwess twanswation.
 */
#define IDT_MAX_NW_POWTS	24
#define IDT_MAX_NW_PAWTS	8
#define IDT_MAX_NW_PEEWS	8
#define IDT_MAX_NW_MWS		29
#define IDT_PCIE_WEGSIZE	4
#define IDT_TWANS_AWIGN		4
#define IDT_DIW_SIZE_AWIGN	1

/*
 * IDT PCIe-switch tempewatuwe sensow vawue wimits
 * @IDT_TEMP_MIN_MDEG:	Minimaw integew vawue of tempewatuwe
 * @IDT_TEMP_MAX_MDEG:	Maximaw integew vawue of tempewatuwe
 * @IDT_TEMP_MIN_OFFSET:Minimaw integew vawue of tempewatuwe offset
 * @IDT_TEMP_MAX_OFFSET:Maximaw integew vawue of tempewatuwe offset
 */
#define IDT_TEMP_MIN_MDEG	0
#define IDT_TEMP_MAX_MDEG	127500
#define IDT_TEMP_MIN_OFFSET	-64000
#define IDT_TEMP_MAX_OFFSET	63500

/*
 * Tempewatuwe sensow vawues enumewation
 * @IDT_TEMP_CUW:	Cuwwent tempewatuwe
 * @IDT_TEMP_WOW:	Wowest histowicaw tempewatuwe
 * @IDT_TEMP_HIGH:	Highest histowicaw tempewatuwe
 * @IDT_TEMP_OFFSET:	Cuwwent tempewatuwe offset
 */
enum idt_temp_vaw {
	IDT_TEMP_CUW,
	IDT_TEMP_WOW,
	IDT_TEMP_HIGH,
	IDT_TEMP_OFFSET
};

/*
 * IDT Memowy Windows type. Depending on the device settings, IDT suppowts
 * Diwect Addwess Twanswation MW wegistews and Wookup Tabwe wegistews
 * @IDT_MW_DIW:		Diwect addwess twanswation
 * @IDT_MW_WUT12:	12-entwy wookup tabwe entwy
 * @IDT_MW_WUT24:	24-entwy wookup tabwe entwy
 *
 * NOTE These vawues awe exactwy the same as one of the BAWSETUP ATWAN fiewd
 */
enum idt_mw_type {
	IDT_MW_DIW = 0x0,
	IDT_MW_WUT12 = 0x1,
	IDT_MW_WUT24 = 0x2
};

/*
 * IDT PCIe-switch modew pwivate data
 * @name:	Device name
 * @powt_cnt:	Totaw numbew of NT endpoint powts
 * @powts:	Powt ids
 */
stwuct idt_89hpes_cfg {
	chaw *name;
	unsigned chaw powt_cnt;
	unsigned chaw powts[];
};

/*
 * Memowy window configuwation stwuctuwe
 * @type:	Type of the memowy window (diwect addwess twanswation ow wookup
 *		tabwe)
 *
 * @baw:	PCIe BAW the memowy window wefewenced to
 * @idx:	Index of the memowy window within the BAW
 *
 * @addw_awign:	Awignment of twanswated addwess
 * @size_awign:	Awignment of memowy window size
 * @size_max:	Maximum size of memowy window
 */
stwuct idt_mw_cfg {
	enum idt_mw_type type;

	unsigned chaw baw;
	unsigned chaw idx;

	u64 addw_awign;
	u64 size_awign;
	u64 size_max;
};

/*
 * Descwiption stwuctuwe of peew IDT NT-functions:
 * @powt:		NT-function powt
 * @pawt:		NT-function pawtition
 *
 * @mw_cnt:		Numbew of memowy windows suppowted by NT-function
 * @mws:		Awway of memowy windows descwiptows
 */
stwuct idt_ntb_peew {
	unsigned chaw powt;
	unsigned chaw pawt;

	unsigned chaw mw_cnt;
	stwuct idt_mw_cfg *mws;
};

/*
 * Descwiption stwuctuwe of wocaw IDT NT-function:
 * @ntb:		Winux NTB-device descwiption stwuctuwe
 * @swcfg:		Pointew to the stwuctuwe of wocaw IDT PCIe-switch
 *			specific cofnfiguwations
 *
 * @powt:		Wocaw NT-function powt
 * @pawt:		Wocaw NT-function pawtition
 *
 * @peew_cnt:		Numbew of peews with activated NTB-function
 * @peews:		Awway of peews descwipting stwuctuwes
 * @powt_idx_map:	Map of powt numbew -> peew index
 * @pawt_idx_map:	Map of pawtition numbew -> peew index
 *
 * @mtbw_wock:		Mapping tabwe access wock
 *
 * @mw_cnt:		Numbew of memowy windows suppowted by NT-function
 * @mws:		Awway of memowy windows descwiptows
 * @wut_wock:		Wookup tabwe access wock
 *
 * @msg_wocks:		Message wegistews mapping tabwe wockews
 *
 * @cfgspc:		Viwtuaw addwess of the memowy mapped configuwation
 *			space of the NT-function
 * @db_mask_wock:	Doowbeww mask wegistew wock
 * @msg_mask_wock:	Message mask wegistew wock
 * @gasa_wock:		GASA wegistews access wock
 *
 * @hwmon_mtx:		Tempewatuwe sensow intewface update mutex
 *
 * @dbgfs_info:		DebugFS info node
 */
stwuct idt_ntb_dev {
	stwuct ntb_dev ntb;
	stwuct idt_89hpes_cfg *swcfg;

	unsigned chaw powt;
	unsigned chaw pawt;

	unsigned chaw peew_cnt;
	stwuct idt_ntb_peew peews[IDT_MAX_NW_PEEWS];
	chaw powt_idx_map[IDT_MAX_NW_POWTS];
	chaw pawt_idx_map[IDT_MAX_NW_PAWTS];

	spinwock_t mtbw_wock;

	unsigned chaw mw_cnt;
	stwuct idt_mw_cfg *mws;
	spinwock_t wut_wock;

	spinwock_t msg_wocks[IDT_MSG_CNT];

	void __iomem *cfgspc;
	spinwock_t db_mask_wock;
	spinwock_t msg_mask_wock;
	spinwock_t gasa_wock;

	stwuct mutex hwmon_mtx;

	stwuct dentwy *dbgfs_info;
};
#define to_ndev_ntb(__ntb) containew_of(__ntb, stwuct idt_ntb_dev, ntb)

/*
 * Descwiptow of the IDT PCIe-switch BAW wesouwces
 * @setup:	BAW setup wegistew
 * @wimit:	BAW wimit wegistew
 * @wtbase:	Wowew twanswated base addwess
 * @utbase:	Uppew twanswated base addwess
 */
stwuct idt_ntb_baw {
	unsigned int setup;
	unsigned int wimit;
	unsigned int wtbase;
	unsigned int utbase;
};

/*
 * Descwiptow of the IDT PCIe-switch message wesouwces
 * @in:		Inbound message wegistew
 * @out:	Outbound message wegistew
 * @swc:	Souwce of inbound message wegistew
 */
stwuct idt_ntb_msg {
	unsigned int in;
	unsigned int out;
	unsigned int swc;
};

/*
 * Descwiptow of the IDT PCIe-switch NT-function specific pawametews in the
 * PCI Configuwation Space
 * @baws:	BAWs wewated wegistews
 * @msgs:	Messaging wewated wegistews
 */
stwuct idt_ntb_wegs {
	stwuct idt_ntb_baw baws[IDT_BAW_CNT];
	stwuct idt_ntb_msg msgs[IDT_MSG_CNT];
};

/*
 * Descwiptow of the IDT PCIe-switch powt specific pawametews in the
 * Gwobaw Configuwation Space
 * @pcicmdsts:	 PCI command/status wegistew
 * @pciewctwsts: PCIe wink contwow/status
 *
 * @ctw:	Powt contwow wegistew
 * @sts:	Powt status wegistew
 *
 * @baws:	BAWs wewated wegistews
 */
stwuct idt_ntb_powt {
	unsigned int pcicmdsts;
	unsigned int pciewctwsts;
	unsigned int ntctw;

	unsigned int ctw;
	unsigned int sts;

	stwuct idt_ntb_baw baws[IDT_BAW_CNT];
};

/*
 * Descwiptow of the IDT PCIe-switch pawtition specific pawametews.
 * @ctw:	Pawtition contwow wegistew in the Gwobaw Addwess Space
 * @sts:	Pawtition status wegistew in the Gwobaw Addwess Space
 * @msgctw:	Messages contwow wegistews
 */
stwuct idt_ntb_pawt {
	unsigned int ctw;
	unsigned int sts;
	unsigned int msgctw[IDT_MSG_CNT];
};

#endif /* NTB_HW_IDT_H */
