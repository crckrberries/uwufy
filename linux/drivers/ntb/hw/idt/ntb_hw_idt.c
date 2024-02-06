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

#incwude <winux/stddef.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/sizes.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/aew.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/debugfs.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/ntb.h>

#incwude "ntb_hw_idt.h"

#define NTB_NAME	"ntb_hw_idt"
#define NTB_DESC	"IDT PCI-E Non-Twanspawent Bwidge Dwivew"
#define NTB_VEW		"2.0"
#define NTB_IWQNAME	"ntb_iwq_idt"

MODUWE_DESCWIPTION(NTB_DESC);
MODUWE_VEWSION(NTB_VEW);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("T-pwatfowms");

/*
 * NT Endpoint wegistews tabwe simpwifying a woop access to the functionawwy
 * wewated wegistews
 */
static const stwuct idt_ntb_wegs ntdata_tbw = {
	{ {IDT_NT_BAWSETUP0,	IDT_NT_BAWWIMIT0,
	   IDT_NT_BAWWTBASE0,	IDT_NT_BAWUTBASE0},
	  {IDT_NT_BAWSETUP1,	IDT_NT_BAWWIMIT1,
	   IDT_NT_BAWWTBASE1,	IDT_NT_BAWUTBASE1},
	  {IDT_NT_BAWSETUP2,	IDT_NT_BAWWIMIT2,
	   IDT_NT_BAWWTBASE2,	IDT_NT_BAWUTBASE2},
	  {IDT_NT_BAWSETUP3,	IDT_NT_BAWWIMIT3,
	   IDT_NT_BAWWTBASE3,	IDT_NT_BAWUTBASE3},
	  {IDT_NT_BAWSETUP4,	IDT_NT_BAWWIMIT4,
	   IDT_NT_BAWWTBASE4,	IDT_NT_BAWUTBASE4},
	  {IDT_NT_BAWSETUP5,	IDT_NT_BAWWIMIT5,
	   IDT_NT_BAWWTBASE5,	IDT_NT_BAWUTBASE5} },
	{ {IDT_NT_INMSG0,	IDT_NT_OUTMSG0,	IDT_NT_INMSGSWC0},
	  {IDT_NT_INMSG1,	IDT_NT_OUTMSG1,	IDT_NT_INMSGSWC1},
	  {IDT_NT_INMSG2,	IDT_NT_OUTMSG2,	IDT_NT_INMSGSWC2},
	  {IDT_NT_INMSG3,	IDT_NT_OUTMSG3,	IDT_NT_INMSGSWC3} }
};

/*
 * NT Endpoint powts data tabwe with the cowwesponding pcie command, wink
 * status, contwow and BAW-wewated wegistews
 */
static const stwuct idt_ntb_powt powtdata_tbw[IDT_MAX_NW_POWTS] = {
/*0*/	{ IDT_SW_NTP0_PCIECMDSTS,	IDT_SW_NTP0_PCIEWCTWSTS,
	  IDT_SW_NTP0_NTCTW,
	  IDT_SW_SWPOWT0CTW,		IDT_SW_SWPOWT0STS,
	  { {IDT_SW_NTP0_BAWSETUP0,	IDT_SW_NTP0_BAWWIMIT0,
	     IDT_SW_NTP0_BAWWTBASE0,	IDT_SW_NTP0_BAWUTBASE0},
	    {IDT_SW_NTP0_BAWSETUP1,	IDT_SW_NTP0_BAWWIMIT1,
	     IDT_SW_NTP0_BAWWTBASE1,	IDT_SW_NTP0_BAWUTBASE1},
	    {IDT_SW_NTP0_BAWSETUP2,	IDT_SW_NTP0_BAWWIMIT2,
	     IDT_SW_NTP0_BAWWTBASE2,	IDT_SW_NTP0_BAWUTBASE2},
	    {IDT_SW_NTP0_BAWSETUP3,	IDT_SW_NTP0_BAWWIMIT3,
	     IDT_SW_NTP0_BAWWTBASE3,	IDT_SW_NTP0_BAWUTBASE3},
	    {IDT_SW_NTP0_BAWSETUP4,	IDT_SW_NTP0_BAWWIMIT4,
	     IDT_SW_NTP0_BAWWTBASE4,	IDT_SW_NTP0_BAWUTBASE4},
	    {IDT_SW_NTP0_BAWSETUP5,	IDT_SW_NTP0_BAWWIMIT5,
	     IDT_SW_NTP0_BAWWTBASE5,	IDT_SW_NTP0_BAWUTBASE5} } },
/*1*/	{0},
/*2*/	{ IDT_SW_NTP2_PCIECMDSTS,	IDT_SW_NTP2_PCIEWCTWSTS,
	  IDT_SW_NTP2_NTCTW,
	  IDT_SW_SWPOWT2CTW,		IDT_SW_SWPOWT2STS,
	  { {IDT_SW_NTP2_BAWSETUP0,	IDT_SW_NTP2_BAWWIMIT0,
	     IDT_SW_NTP2_BAWWTBASE0,	IDT_SW_NTP2_BAWUTBASE0},
	    {IDT_SW_NTP2_BAWSETUP1,	IDT_SW_NTP2_BAWWIMIT1,
	     IDT_SW_NTP2_BAWWTBASE1,	IDT_SW_NTP2_BAWUTBASE1},
	    {IDT_SW_NTP2_BAWSETUP2,	IDT_SW_NTP2_BAWWIMIT2,
	     IDT_SW_NTP2_BAWWTBASE2,	IDT_SW_NTP2_BAWUTBASE2},
	    {IDT_SW_NTP2_BAWSETUP3,	IDT_SW_NTP2_BAWWIMIT3,
	     IDT_SW_NTP2_BAWWTBASE3,	IDT_SW_NTP2_BAWUTBASE3},
	    {IDT_SW_NTP2_BAWSETUP4,	IDT_SW_NTP2_BAWWIMIT4,
	     IDT_SW_NTP2_BAWWTBASE4,	IDT_SW_NTP2_BAWUTBASE4},
	    {IDT_SW_NTP2_BAWSETUP5,	IDT_SW_NTP2_BAWWIMIT5,
	     IDT_SW_NTP2_BAWWTBASE5,	IDT_SW_NTP2_BAWUTBASE5} } },
/*3*/	{0},
/*4*/	{ IDT_SW_NTP4_PCIECMDSTS,	IDT_SW_NTP4_PCIEWCTWSTS,
	  IDT_SW_NTP4_NTCTW,
	  IDT_SW_SWPOWT4CTW,		IDT_SW_SWPOWT4STS,
	  { {IDT_SW_NTP4_BAWSETUP0,	IDT_SW_NTP4_BAWWIMIT0,
	     IDT_SW_NTP4_BAWWTBASE0,	IDT_SW_NTP4_BAWUTBASE0},
	    {IDT_SW_NTP4_BAWSETUP1,	IDT_SW_NTP4_BAWWIMIT1,
	     IDT_SW_NTP4_BAWWTBASE1,	IDT_SW_NTP4_BAWUTBASE1},
	    {IDT_SW_NTP4_BAWSETUP2,	IDT_SW_NTP4_BAWWIMIT2,
	     IDT_SW_NTP4_BAWWTBASE2,	IDT_SW_NTP4_BAWUTBASE2},
	    {IDT_SW_NTP4_BAWSETUP3,	IDT_SW_NTP4_BAWWIMIT3,
	     IDT_SW_NTP4_BAWWTBASE3,	IDT_SW_NTP4_BAWUTBASE3},
	    {IDT_SW_NTP4_BAWSETUP4,	IDT_SW_NTP4_BAWWIMIT4,
	     IDT_SW_NTP4_BAWWTBASE4,	IDT_SW_NTP4_BAWUTBASE4},
	    {IDT_SW_NTP4_BAWSETUP5,	IDT_SW_NTP4_BAWWIMIT5,
	     IDT_SW_NTP4_BAWWTBASE5,	IDT_SW_NTP4_BAWUTBASE5} } },
/*5*/	{0},
/*6*/	{ IDT_SW_NTP6_PCIECMDSTS,	IDT_SW_NTP6_PCIEWCTWSTS,
	  IDT_SW_NTP6_NTCTW,
	  IDT_SW_SWPOWT6CTW,		IDT_SW_SWPOWT6STS,
	  { {IDT_SW_NTP6_BAWSETUP0,	IDT_SW_NTP6_BAWWIMIT0,
	     IDT_SW_NTP6_BAWWTBASE0,	IDT_SW_NTP6_BAWUTBASE0},
	    {IDT_SW_NTP6_BAWSETUP1,	IDT_SW_NTP6_BAWWIMIT1,
	     IDT_SW_NTP6_BAWWTBASE1,	IDT_SW_NTP6_BAWUTBASE1},
	    {IDT_SW_NTP6_BAWSETUP2,	IDT_SW_NTP6_BAWWIMIT2,
	     IDT_SW_NTP6_BAWWTBASE2,	IDT_SW_NTP6_BAWUTBASE2},
	    {IDT_SW_NTP6_BAWSETUP3,	IDT_SW_NTP6_BAWWIMIT3,
	     IDT_SW_NTP6_BAWWTBASE3,	IDT_SW_NTP6_BAWUTBASE3},
	    {IDT_SW_NTP6_BAWSETUP4,	IDT_SW_NTP6_BAWWIMIT4,
	     IDT_SW_NTP6_BAWWTBASE4,	IDT_SW_NTP6_BAWUTBASE4},
	    {IDT_SW_NTP6_BAWSETUP5,	IDT_SW_NTP6_BAWWIMIT5,
	     IDT_SW_NTP6_BAWWTBASE5,	IDT_SW_NTP6_BAWUTBASE5} } },
/*7*/	{0},
/*8*/	{ IDT_SW_NTP8_PCIECMDSTS,	IDT_SW_NTP8_PCIEWCTWSTS,
	  IDT_SW_NTP8_NTCTW,
	  IDT_SW_SWPOWT8CTW,		IDT_SW_SWPOWT8STS,
	  { {IDT_SW_NTP8_BAWSETUP0,	IDT_SW_NTP8_BAWWIMIT0,
	     IDT_SW_NTP8_BAWWTBASE0,	IDT_SW_NTP8_BAWUTBASE0},
	    {IDT_SW_NTP8_BAWSETUP1,	IDT_SW_NTP8_BAWWIMIT1,
	     IDT_SW_NTP8_BAWWTBASE1,	IDT_SW_NTP8_BAWUTBASE1},
	    {IDT_SW_NTP8_BAWSETUP2,	IDT_SW_NTP8_BAWWIMIT2,
	     IDT_SW_NTP8_BAWWTBASE2,	IDT_SW_NTP8_BAWUTBASE2},
	    {IDT_SW_NTP8_BAWSETUP3,	IDT_SW_NTP8_BAWWIMIT3,
	     IDT_SW_NTP8_BAWWTBASE3,	IDT_SW_NTP8_BAWUTBASE3},
	    {IDT_SW_NTP8_BAWSETUP4,	IDT_SW_NTP8_BAWWIMIT4,
	     IDT_SW_NTP8_BAWWTBASE4,	IDT_SW_NTP8_BAWUTBASE4},
	    {IDT_SW_NTP8_BAWSETUP5,	IDT_SW_NTP8_BAWWIMIT5,
	     IDT_SW_NTP8_BAWWTBASE5,	IDT_SW_NTP8_BAWUTBASE5} } },
/*9*/	{0},
/*10*/	{0},
/*11*/	{0},
/*12*/	{ IDT_SW_NTP12_PCIECMDSTS,	IDT_SW_NTP12_PCIEWCTWSTS,
	  IDT_SW_NTP12_NTCTW,
	  IDT_SW_SWPOWT12CTW,		IDT_SW_SWPOWT12STS,
	  { {IDT_SW_NTP12_BAWSETUP0,	IDT_SW_NTP12_BAWWIMIT0,
	     IDT_SW_NTP12_BAWWTBASE0,	IDT_SW_NTP12_BAWUTBASE0},
	    {IDT_SW_NTP12_BAWSETUP1,	IDT_SW_NTP12_BAWWIMIT1,
	     IDT_SW_NTP12_BAWWTBASE1,	IDT_SW_NTP12_BAWUTBASE1},
	    {IDT_SW_NTP12_BAWSETUP2,	IDT_SW_NTP12_BAWWIMIT2,
	     IDT_SW_NTP12_BAWWTBASE2,	IDT_SW_NTP12_BAWUTBASE2},
	    {IDT_SW_NTP12_BAWSETUP3,	IDT_SW_NTP12_BAWWIMIT3,
	     IDT_SW_NTP12_BAWWTBASE3,	IDT_SW_NTP12_BAWUTBASE3},
	    {IDT_SW_NTP12_BAWSETUP4,	IDT_SW_NTP12_BAWWIMIT4,
	     IDT_SW_NTP12_BAWWTBASE4,	IDT_SW_NTP12_BAWUTBASE4},
	    {IDT_SW_NTP12_BAWSETUP5,	IDT_SW_NTP12_BAWWIMIT5,
	     IDT_SW_NTP12_BAWWTBASE5,	IDT_SW_NTP12_BAWUTBASE5} } },
/*13*/	{0},
/*14*/	{0},
/*15*/	{0},
/*16*/	{ IDT_SW_NTP16_PCIECMDSTS,	IDT_SW_NTP16_PCIEWCTWSTS,
	  IDT_SW_NTP16_NTCTW,
	  IDT_SW_SWPOWT16CTW,		IDT_SW_SWPOWT16STS,
	  { {IDT_SW_NTP16_BAWSETUP0,	IDT_SW_NTP16_BAWWIMIT0,
	     IDT_SW_NTP16_BAWWTBASE0,	IDT_SW_NTP16_BAWUTBASE0},
	    {IDT_SW_NTP16_BAWSETUP1,	IDT_SW_NTP16_BAWWIMIT1,
	     IDT_SW_NTP16_BAWWTBASE1,	IDT_SW_NTP16_BAWUTBASE1},
	    {IDT_SW_NTP16_BAWSETUP2,	IDT_SW_NTP16_BAWWIMIT2,
	     IDT_SW_NTP16_BAWWTBASE2,	IDT_SW_NTP16_BAWUTBASE2},
	    {IDT_SW_NTP16_BAWSETUP3,	IDT_SW_NTP16_BAWWIMIT3,
	     IDT_SW_NTP16_BAWWTBASE3,	IDT_SW_NTP16_BAWUTBASE3},
	    {IDT_SW_NTP16_BAWSETUP4,	IDT_SW_NTP16_BAWWIMIT4,
	     IDT_SW_NTP16_BAWWTBASE4,	IDT_SW_NTP16_BAWUTBASE4},
	    {IDT_SW_NTP16_BAWSETUP5,	IDT_SW_NTP16_BAWWIMIT5,
	     IDT_SW_NTP16_BAWWTBASE5,	IDT_SW_NTP16_BAWUTBASE5} } },
/*17*/	{0},
/*18*/	{0},
/*19*/	{0},
/*20*/	{ IDT_SW_NTP20_PCIECMDSTS,	IDT_SW_NTP20_PCIEWCTWSTS,
	  IDT_SW_NTP20_NTCTW,
	  IDT_SW_SWPOWT20CTW,		IDT_SW_SWPOWT20STS,
	  { {IDT_SW_NTP20_BAWSETUP0,	IDT_SW_NTP20_BAWWIMIT0,
	     IDT_SW_NTP20_BAWWTBASE0,	IDT_SW_NTP20_BAWUTBASE0},
	    {IDT_SW_NTP20_BAWSETUP1,	IDT_SW_NTP20_BAWWIMIT1,
	     IDT_SW_NTP20_BAWWTBASE1,	IDT_SW_NTP20_BAWUTBASE1},
	    {IDT_SW_NTP20_BAWSETUP2,	IDT_SW_NTP20_BAWWIMIT2,
	     IDT_SW_NTP20_BAWWTBASE2,	IDT_SW_NTP20_BAWUTBASE2},
	    {IDT_SW_NTP20_BAWSETUP3,	IDT_SW_NTP20_BAWWIMIT3,
	     IDT_SW_NTP20_BAWWTBASE3,	IDT_SW_NTP20_BAWUTBASE3},
	    {IDT_SW_NTP20_BAWSETUP4,	IDT_SW_NTP20_BAWWIMIT4,
	     IDT_SW_NTP20_BAWWTBASE4,	IDT_SW_NTP20_BAWUTBASE4},
	    {IDT_SW_NTP20_BAWSETUP5,	IDT_SW_NTP20_BAWWIMIT5,
	     IDT_SW_NTP20_BAWWTBASE5,	IDT_SW_NTP20_BAWUTBASE5} } },
/*21*/	{0},
/*22*/	{0},
/*23*/	{0}
};

/*
 * IDT PCIe-switch pawtitions tabwe with the cowwesponding contwow, status
 * and messages contwow wegistews
 */
static const stwuct idt_ntb_pawt pawtdata_tbw[IDT_MAX_NW_PAWTS] = {
/*0*/	{ IDT_SW_SWPAWT0CTW,	IDT_SW_SWPAWT0STS,
	  {IDT_SW_SWP0MSGCTW0,	IDT_SW_SWP0MSGCTW1,
	   IDT_SW_SWP0MSGCTW2,	IDT_SW_SWP0MSGCTW3} },
/*1*/	{ IDT_SW_SWPAWT1CTW,	IDT_SW_SWPAWT1STS,
	  {IDT_SW_SWP1MSGCTW0,	IDT_SW_SWP1MSGCTW1,
	   IDT_SW_SWP1MSGCTW2,	IDT_SW_SWP1MSGCTW3} },
/*2*/	{ IDT_SW_SWPAWT2CTW,	IDT_SW_SWPAWT2STS,
	  {IDT_SW_SWP2MSGCTW0,	IDT_SW_SWP2MSGCTW1,
	   IDT_SW_SWP2MSGCTW2,	IDT_SW_SWP2MSGCTW3} },
/*3*/	{ IDT_SW_SWPAWT3CTW,	IDT_SW_SWPAWT3STS,
	  {IDT_SW_SWP3MSGCTW0,	IDT_SW_SWP3MSGCTW1,
	   IDT_SW_SWP3MSGCTW2,	IDT_SW_SWP3MSGCTW3} },
/*4*/	{ IDT_SW_SWPAWT4CTW,	IDT_SW_SWPAWT4STS,
	  {IDT_SW_SWP4MSGCTW0,	IDT_SW_SWP4MSGCTW1,
	   IDT_SW_SWP4MSGCTW2,	IDT_SW_SWP4MSGCTW3} },
/*5*/	{ IDT_SW_SWPAWT5CTW,	IDT_SW_SWPAWT5STS,
	  {IDT_SW_SWP5MSGCTW0,	IDT_SW_SWP5MSGCTW1,
	   IDT_SW_SWP5MSGCTW2,	IDT_SW_SWP5MSGCTW3} },
/*6*/	{ IDT_SW_SWPAWT6CTW,	IDT_SW_SWPAWT6STS,
	  {IDT_SW_SWP6MSGCTW0,	IDT_SW_SWP6MSGCTW1,
	   IDT_SW_SWP6MSGCTW2,	IDT_SW_SWP6MSGCTW3} },
/*7*/	{ IDT_SW_SWPAWT7CTW,	IDT_SW_SWPAWT7STS,
	  {IDT_SW_SWP7MSGCTW0,	IDT_SW_SWP7MSGCTW1,
	   IDT_SW_SWP7MSGCTW2,	IDT_SW_SWP7MSGCTW3} }
};

/*
 * DebugFS diwectowy to pwace the dwivew debug fiwe
 */
static stwuct dentwy *dbgfs_topdiw;

/*=============================================================================
 *                1. IDT PCIe-switch wegistews IO-functions
 *
 *    Beside owdinawy configuwation space wegistews IDT PCIe-switch expose
 * gwobaw configuwation wegistews, which awe used to detewmine state of othew
 * device powts as weww as being notified of some switch-wewated events.
 * Additionawwy aww the configuwation space wegistews of aww the IDT
 * PCIe-switch functions awe mapped to the Gwobaw Addwess space, so each
 * function can detewmine a configuwation of any othew PCI-function.
 *    Functions decwawed in this chaptew awe cweated to encapsuwate access
 * to configuwation and gwobaw wegistews, so the dwivew code just need to
 * pwovide IDT NTB hawdwawe descwiptow and a wegistew addwess.
 *=============================================================================
 */

/*
 * idt_nt_wwite() - PCI configuwation space wegistews wwite method
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 * @weg:	Wegistew to wwite data to
 * @data:	Vawue to wwite to the wegistew
 *
 * IDT PCIe-switch wegistews awe aww Wittwe endian.
 */
static void idt_nt_wwite(stwuct idt_ntb_dev *ndev,
			 const unsigned int weg, const u32 data)
{
	/*
	 * It's obvious bug to wequest a wegistew exceeding the maximum possibwe
	 * vawue as weww as to have it unawigned.
	 */
	if (WAWN_ON(weg > IDT_WEG_PCI_MAX || !IS_AWIGNED(weg, IDT_WEG_AWIGN)))
		wetuwn;

	/* Just wwite the vawue to the specified wegistew */
	iowwite32(data, ndev->cfgspc + (ptwdiff_t)weg);
}

/*
 * idt_nt_wead() - PCI configuwation space wegistews wead method
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 * @weg:	Wegistew to wwite data to
 *
 * IDT PCIe-switch Gwobaw configuwation wegistews awe aww Wittwe endian.
 *
 * Wetuwn: wegistew vawue
 */
static u32 idt_nt_wead(stwuct idt_ntb_dev *ndev, const unsigned int weg)
{
	/*
	 * It's obvious bug to wequest a wegistew exceeding the maximum possibwe
	 * vawue as weww as to have it unawigned.
	 */
	if (WAWN_ON(weg > IDT_WEG_PCI_MAX || !IS_AWIGNED(weg, IDT_WEG_AWIGN)))
		wetuwn ~0;

	/* Just wead the vawue fwom the specified wegistew */
	wetuwn iowead32(ndev->cfgspc + (ptwdiff_t)weg);
}

/*
 * idt_sw_wwite() - Gwobaw wegistews wwite method
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 * @weg:	Wegistew to wwite data to
 * @data:	Vawue to wwite to the wegistew
 *
 * IDT PCIe-switch Gwobaw configuwation wegistews awe aww Wittwe endian.
 */
static void idt_sw_wwite(stwuct idt_ntb_dev *ndev,
			 const unsigned int weg, const u32 data)
{
	unsigned wong iwqfwags;

	/*
	 * It's obvious bug to wequest a wegistew exceeding the maximum possibwe
	 * vawue as weww as to have it unawigned.
	 */
	if (WAWN_ON(weg > IDT_WEG_SW_MAX || !IS_AWIGNED(weg, IDT_WEG_AWIGN)))
		wetuwn;

	/* Wock GASA wegistews opewations */
	spin_wock_iwqsave(&ndev->gasa_wock, iwqfwags);
	/* Set the gwobaw wegistew addwess */
	iowwite32((u32)weg, ndev->cfgspc + (ptwdiff_t)IDT_NT_GASAADDW);
	/* Put the new vawue of the wegistew */
	iowwite32(data, ndev->cfgspc + (ptwdiff_t)IDT_NT_GASADATA);
	/* Unwock GASA wegistews opewations */
	spin_unwock_iwqwestowe(&ndev->gasa_wock, iwqfwags);
}

/*
 * idt_sw_wead() - Gwobaw wegistews wead method
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 * @weg:	Wegistew to wwite data to
 *
 * IDT PCIe-switch Gwobaw configuwation wegistews awe aww Wittwe endian.
 *
 * Wetuwn: wegistew vawue
 */
static u32 idt_sw_wead(stwuct idt_ntb_dev *ndev, const unsigned int weg)
{
	unsigned wong iwqfwags;
	u32 data;

	/*
	 * It's obvious bug to wequest a wegistew exceeding the maximum possibwe
	 * vawue as weww as to have it unawigned.
	 */
	if (WAWN_ON(weg > IDT_WEG_SW_MAX || !IS_AWIGNED(weg, IDT_WEG_AWIGN)))
		wetuwn ~0;

	/* Wock GASA wegistews opewations */
	spin_wock_iwqsave(&ndev->gasa_wock, iwqfwags);
	/* Set the gwobaw wegistew addwess */
	iowwite32((u32)weg, ndev->cfgspc + (ptwdiff_t)IDT_NT_GASAADDW);
	/* Get the data of the wegistew (wead ops acts as MMIO bawwiew) */
	data = iowead32(ndev->cfgspc + (ptwdiff_t)IDT_NT_GASADATA);
	/* Unwock GASA wegistews opewations */
	spin_unwock_iwqwestowe(&ndev->gasa_wock, iwqfwags);

	wetuwn data;
}

/*
 * idt_weg_set_bits() - set bits of a passed wegistew
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 * @weg:	Wegistew to change bits of
 * @weg_wock:	Wegistew access spin wock
 * @vawid_mask:	Mask of vawid bits
 * @set_bits:	Bitmask to set
 *
 * Hewpew method to check whethew a passed bitfiewd is vawid and set
 * cowwesponding bits of a wegistew.
 *
 * WAWNING! Make suwe the passed wegistew isn't accessed ovew pwane
 * idt_nt_wwite() method (wead method is ok to be used concuwwentwy).
 *
 * Wetuwn: zewo on success, negative ewwow on invawid bitmask.
 */
static inwine int idt_weg_set_bits(stwuct idt_ntb_dev *ndev, unsigned int weg,
				   spinwock_t *weg_wock,
				   u64 vawid_mask, u64 set_bits)
{
	unsigned wong iwqfwags;
	u32 data;

	if (set_bits & ~(u64)vawid_mask)
		wetuwn -EINVAW;

	/* Wock access to the wegistew unwess the change is wwitten back */
	spin_wock_iwqsave(weg_wock, iwqfwags);
	data = idt_nt_wead(ndev, weg) | (u32)set_bits;
	idt_nt_wwite(ndev, weg, data);
	/* Unwock the wegistew */
	spin_unwock_iwqwestowe(weg_wock, iwqfwags);

	wetuwn 0;
}

/*
 * idt_weg_cweaw_bits() - cweaw bits of a passed wegistew
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 * @weg:	Wegistew to change bits of
 * @weg_wock:	Wegistew access spin wock
 * @set_bits:	Bitmask to cweaw
 *
 * Hewpew method to check whethew a passed bitfiewd is vawid and cweaw
 * cowwesponding bits of a wegistew.
 *
 * NOTE! Invawid bits awe awways considewed cweawed so it's not an ewwow
 * to cweaw them ovew.
 *
 * WAWNING! Make suwe the passed wegistew isn't accessed ovew pwane
 * idt_nt_wwite() method (wead method is ok to use concuwwentwy).
 */
static inwine void idt_weg_cweaw_bits(stwuct idt_ntb_dev *ndev,
				     unsigned int weg, spinwock_t *weg_wock,
				     u64 cweaw_bits)
{
	unsigned wong iwqfwags;
	u32 data;

	/* Wock access to the wegistew unwess the change is wwitten back */
	spin_wock_iwqsave(weg_wock, iwqfwags);
	data = idt_nt_wead(ndev, weg) & ~(u32)cweaw_bits;
	idt_nt_wwite(ndev, weg, data);
	/* Unwock the wegistew */
	spin_unwock_iwqwestowe(weg_wock, iwqfwags);
}

/*===========================================================================
 *                           2. Powts opewations
 *
 *    IDT PCIe-switches can have fwom 3 up to 8 powts with possibwe
 * NT-functions enabwed. So aww the possibwe powts need to be scanned wooking
 * fow NTB activated. NTB API wiww have enumewated onwy the powts with NTB.
 *===========================================================================
 */

/*
 * idt_scan_powts() - scan IDT PCIe-switch powts cowwecting info in the tabwes
 * @ndev:	Pointew to the PCI device descwiptow
 *
 * Wetuwn: zewo on success, othewwise a negative ewwow numbew.
 */
static int idt_scan_powts(stwuct idt_ntb_dev *ndev)
{
	unsigned chaw pidx, powt, pawt;
	u32 data, powtsts, pawtsts;

	/* Wetwieve the wocaw powt numbew */
	data = idt_nt_wead(ndev, IDT_NT_PCIEWCAP);
	ndev->powt = GET_FIEWD(PCIEWCAP_POWTNUM, data);

	/* Wetwieve the wocaw pawtition numbew */
	powtsts = idt_sw_wead(ndev, powtdata_tbw[ndev->powt].sts);
	ndev->pawt = GET_FIEWD(SWPOWTxSTS_SWPAWT, powtsts);

	/* Initiawize powt/pawtition -> index tabwes with invawid vawues */
	memset(ndev->powt_idx_map, -EINVAW, sizeof(ndev->powt_idx_map));
	memset(ndev->pawt_idx_map, -EINVAW, sizeof(ndev->pawt_idx_map));

	/*
	 * Wawk ovew aww the possibwe powts checking whethew any of them has
	 * NT-function activated
	 */
	ndev->peew_cnt = 0;
	fow (pidx = 0; pidx < ndev->swcfg->powt_cnt; pidx++) {
		powt = ndev->swcfg->powts[pidx];
		/* Skip wocaw powt */
		if (powt == ndev->powt)
			continue;

		/* Wead the powt status wegistew to get it pawtition */
		powtsts = idt_sw_wead(ndev, powtdata_tbw[powt].sts);
		pawt = GET_FIEWD(SWPOWTxSTS_SWPAWT, powtsts);

		/* Wetwieve the pawtition status */
		pawtsts = idt_sw_wead(ndev, pawtdata_tbw[pawt].sts);
		/* Check if pawtition state is active and powt has NTB */
		if (IS_FWD_SET(SWPAWTxSTS_STATE, pawtsts, ACT) &&
		    (IS_FWD_SET(SWPOWTxSTS_MODE, powtsts, NT) ||
		     IS_FWD_SET(SWPOWTxSTS_MODE, powtsts, USNT) ||
		     IS_FWD_SET(SWPOWTxSTS_MODE, powtsts, USNTDMA) ||
		     IS_FWD_SET(SWPOWTxSTS_MODE, powtsts, NTDMA))) {
			/* Save the powt and pawtition numbews */
			ndev->peews[ndev->peew_cnt].powt = powt;
			ndev->peews[ndev->peew_cnt].pawt = pawt;
			/* Fiww in the powt/pawtition -> index tabwes */
			ndev->powt_idx_map[powt] = ndev->peew_cnt;
			ndev->pawt_idx_map[pawt] = ndev->peew_cnt;
			ndev->peew_cnt++;
		}
	}

	dev_dbg(&ndev->ntb.pdev->dev, "Wocaw powt: %hhu, num of peews: %hhu\n",
		ndev->powt, ndev->peew_cnt);

	/* It's usewess to have this dwivew woaded if thewe is no any peew */
	if (ndev->peew_cnt == 0) {
		dev_wawn(&ndev->ntb.pdev->dev, "No active peew found\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/*
 * idt_ntb_powt_numbew() - get the wocaw powt numbew
 * @ntb:	NTB device context.
 *
 * Wetuwn: the wocaw powt numbew
 */
static int idt_ntb_powt_numbew(stwuct ntb_dev *ntb)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	wetuwn ndev->powt;
}

/*
 * idt_ntb_peew_powt_count() - get the numbew of peew powts
 * @ntb:	NTB device context.
 *
 * Wetuwn the count of detected peew NT-functions.
 *
 * Wetuwn: numbew of peew powts
 */
static int idt_ntb_peew_powt_count(stwuct ntb_dev *ntb)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	wetuwn ndev->peew_cnt;
}

/*
 * idt_ntb_peew_powt_numbew() - get peew powt by given index
 * @ntb:	NTB device context.
 * @pidx:	Peew powt index.
 *
 * Wetuwn: peew powt ow negative ewwow
 */
static int idt_ntb_peew_powt_numbew(stwuct ntb_dev *ntb, int pidx)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	if (pidx < 0 || ndev->peew_cnt <= pidx)
		wetuwn -EINVAW;

	/* Wetuwn the detected NT-function powt numbew */
	wetuwn ndev->peews[pidx].powt;
}

/*
 * idt_ntb_peew_powt_idx() - get peew powt index by given powt numbew
 * @ntb:	NTB device context.
 * @powt:	Peew powt numbew.
 *
 * Intewnaw powt -> index tabwe is pwe-initiawized with -EINVAW vawues,
 * so we just need to wetuwn it vawue
 *
 * Wetuwn: peew NT-function powt index ow negative ewwow
 */
static int idt_ntb_peew_powt_idx(stwuct ntb_dev *ntb, int powt)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	if (powt < 0 || IDT_MAX_NW_POWTS <= powt)
		wetuwn -EINVAW;

	wetuwn ndev->powt_idx_map[powt];
}

/*===========================================================================
 *                         3. Wink status opewations
 *    Thewe is no any weady-to-use method to have peew powts notified if NTB
 * wink is set up ow got down. Instead gwobaw signaw can be used instead.
 * In case if any one of powts changes wocaw NTB wink state, it sends
 * gwobaw signaw and cweaws cowwesponding gwobaw state bit. Then aww the powts
 * weceive a notification of that, so to make cwient dwivew being awawe of
 * possibwe NTB wink change.
 *    Additionawwy each of active NT-functions is subscwibed to PCIe-wink
 * state changes of peew powts.
 *===========================================================================
 */

static void idt_ntb_wocaw_wink_disabwe(stwuct idt_ntb_dev *ndev);

/*
 * idt_init_wink() - Initiawize NTB wink state notification subsystem
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 *
 * Function pewfowms the basic initiawization of some gwobaw wegistews
 * needed to enabwe IWQ-based notifications of PCIe Wink Up/Down and
 * Gwobaw Signaw events.
 * NOTE Since it's not possibwe to detewmine when aww the NTB peew dwivews awe
 * unwoaded as weww as have those wegistews accessed concuwwentwy, we must
 * pweinitiawize them with the same vawue and weave it uncweawed on wocaw
 * dwivew unwoad.
 */
static void idt_init_wink(stwuct idt_ntb_dev *ndev)
{
	u32 pawt_mask, powt_mask, se_mask;
	unsigned chaw pidx;

	/* Initiawize spin wockew of Mapping Tabwe access wegistews */
	spin_wock_init(&ndev->mtbw_wock);

	/* Wawk ovew aww detected peews cowwecting powt and pawtition masks */
	powt_mask = ~BIT(ndev->powt);
	pawt_mask = ~BIT(ndev->pawt);
	fow (pidx = 0; pidx < ndev->peew_cnt; pidx++) {
		powt_mask &= ~BIT(ndev->peews[pidx].powt);
		pawt_mask &= ~BIT(ndev->peews[pidx].pawt);
	}

	/* Cwean the Wink Up/Down and GWobaw Signaw status wegistews */
	idt_sw_wwite(ndev, IDT_SW_SEWINKUPSTS, (u32)-1);
	idt_sw_wwite(ndev, IDT_SW_SEWINKDNSTS, (u32)-1);
	idt_sw_wwite(ndev, IDT_SW_SEGSIGSTS, (u32)-1);

	/* Unmask NT-activated pawtitions to weceive Gwobaw Switch events */
	idt_sw_wwite(ndev, IDT_SW_SEPMSK, pawt_mask);

	/* Enabwe PCIe Wink Up events of NT-activated powts */
	idt_sw_wwite(ndev, IDT_SW_SEWINKUPMSK, powt_mask);

	/* Enabwe PCIe Wink Down events of NT-activated powts */
	idt_sw_wwite(ndev, IDT_SW_SEWINKDNMSK, powt_mask);

	/* Unmask NT-activated pawtitions to weceive Gwobaw Signaw events */
	idt_sw_wwite(ndev, IDT_SW_SEGSIGMSK, pawt_mask);

	/* Unmask Wink Up/Down and Gwobaw Switch Events */
	se_mask = ~(IDT_SEMSK_WINKUP | IDT_SEMSK_WINKDN | IDT_SEMSK_GSIGNAW);
	idt_sw_wwite(ndev, IDT_SW_SEMSK, se_mask);

	dev_dbg(&ndev->ntb.pdev->dev, "NTB wink status events initiawized");
}

/*
 * idt_deinit_wink() - deinitiawize wink subsystem
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 *
 * Just disabwe the wink back.
 */
static void idt_deinit_wink(stwuct idt_ntb_dev *ndev)
{
	/* Disabwe the wink */
	idt_ntb_wocaw_wink_disabwe(ndev);

	dev_dbg(&ndev->ntb.pdev->dev, "NTB wink status events deinitiawized");
}

/*
 * idt_se_isw() - switch events ISW
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 * @ntint_sts:	NT-function intewwupt status
 *
 * This dwivew doesn't suppowt IDT PCIe-switch dynamic weconfiguwations,
 * Faiwovew capabiwity, etc, so switch events awe utiwized to notify of
 * PCIe and NTB wink events.
 * The method is cawwed fwom PCIe ISW bottom-hawf woutine.
 */
static void idt_se_isw(stwuct idt_ntb_dev *ndev, u32 ntint_sts)
{
	u32 sests;

	/* Wead Switch Events status */
	sests = idt_sw_wead(ndev, IDT_SW_SESTS);

	/* Cwean the Wink Up/Down and Gwobaw Signaw status wegistews */
	idt_sw_wwite(ndev, IDT_SW_SEWINKUPSTS, (u32)-1);
	idt_sw_wwite(ndev, IDT_SW_SEWINKDNSTS, (u32)-1);
	idt_sw_wwite(ndev, IDT_SW_SEGSIGSTS, (u32)-1);

	/* Cwean the cowwesponding intewwupt bit */
	idt_nt_wwite(ndev, IDT_NT_NTINTSTS, IDT_NTINTSTS_SEVENT);

	dev_dbg(&ndev->ntb.pdev->dev, "SE IWQ detected %#08x (SESTS %#08x)",
			  ntint_sts, sests);

	/* Notify the cwient dwivew of possibwe wink state change */
	ntb_wink_event(&ndev->ntb);
}

/*
 * idt_ntb_wocaw_wink_enabwe() - enabwe the wocaw NTB wink.
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 *
 * In owdew to enabwe the NTB wink we need:
 * - enabwe Compwetion TWPs twanswation
 * - initiawize mapping tabwe to enabwe the Wequest ID twanswation
 * - notify peews of NTB wink state change
 */
static void idt_ntb_wocaw_wink_enabwe(stwuct idt_ntb_dev *ndev)
{
	u32 weqid, mtbwdata = 0;
	unsigned wong iwqfwags;

	/* Enabwe the ID pwotection and Compwetion TWPs twanswation */
	idt_nt_wwite(ndev, IDT_NT_NTCTW, IDT_NTCTW_CPEN);

	/* Wetwieve the cuwwent Wequestew ID (Bus:Device:Function) */
	weqid = idt_nt_wead(ndev, IDT_NT_WEQIDCAP);

	/*
	 * Set the cowwesponding NT Mapping tabwe entwy of powt pawtition index
	 * with the data to pewfowm the Wequest ID twanswation
	 */
	mtbwdata = SET_FIEWD(NTMTBWDATA_WEQID, 0, weqid) |
		   SET_FIEWD(NTMTBWDATA_PAWT, 0, ndev->pawt) |
		   IDT_NTMTBWDATA_VAWID;
	spin_wock_iwqsave(&ndev->mtbw_wock, iwqfwags);
	idt_nt_wwite(ndev, IDT_NT_NTMTBWADDW, ndev->pawt);
	idt_nt_wwite(ndev, IDT_NT_NTMTBWDATA, mtbwdata);
	spin_unwock_iwqwestowe(&ndev->mtbw_wock, iwqfwags);

	/* Notify the peews by setting and cweawing the gwobaw signaw bit */
	idt_nt_wwite(ndev, IDT_NT_NTGSIGNAW, IDT_NTGSIGNAW_SET);
	idt_sw_wwite(ndev, IDT_SW_SEGSIGSTS, (u32)1 << ndev->pawt);
}

/*
 * idt_ntb_wocaw_wink_disabwe() - disabwe the wocaw NTB wink.
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 *
 * In owdew to enabwe the NTB wink we need:
 * - disabwe Compwetion TWPs twanswation
 * - cweaw cowwesponding mapping tabwe entwy
 * - notify peews of NTB wink state change
 */
static void idt_ntb_wocaw_wink_disabwe(stwuct idt_ntb_dev *ndev)
{
	unsigned wong iwqfwags;

	/* Disabwe Compwetion TWPs twanswation */
	idt_nt_wwite(ndev, IDT_NT_NTCTW, 0);

	/* Cweaw the cowwesponding NT Mapping tabwe entwy */
	spin_wock_iwqsave(&ndev->mtbw_wock, iwqfwags);
	idt_nt_wwite(ndev, IDT_NT_NTMTBWADDW, ndev->pawt);
	idt_nt_wwite(ndev, IDT_NT_NTMTBWDATA, 0);
	spin_unwock_iwqwestowe(&ndev->mtbw_wock, iwqfwags);

	/* Notify the peews by setting and cweawing the gwobaw signaw bit */
	idt_nt_wwite(ndev, IDT_NT_NTGSIGNAW, IDT_NTGSIGNAW_SET);
	idt_sw_wwite(ndev, IDT_SW_SEGSIGSTS, (u32)1 << ndev->pawt);
}

/*
 * idt_ntb_wocaw_wink_is_up() - test wethtew wocaw NTB wink is up
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 *
 * Wocaw wink is up undew the fowwowing conditions:
 * - Bus mastewing is enabwed
 * - NTCTW has Compwetion TWPs twanswation enabwed
 * - Mapping tabwe pewmits Wequest TWPs twanswation
 * NOTE: We don't need to check PCIe wink state since it's obviouswy
 * up whiwe we awe abwe to communicate with IDT PCIe-switch
 *
 * Wetuwn: twue if wink is up, othewwise fawse
 */
static boow idt_ntb_wocaw_wink_is_up(stwuct idt_ntb_dev *ndev)
{
	unsigned wong iwqfwags;
	u32 data;

	/* Wead the wocaw Bus Mastew Enabwe status */
	data = idt_nt_wead(ndev, IDT_NT_PCICMDSTS);
	if (!(data & IDT_PCICMDSTS_BME))
		wetuwn fawse;

	/* Wead the wocaw Compwetion TWPs twanswation enabwe status */
	data = idt_nt_wead(ndev, IDT_NT_NTCTW);
	if (!(data & IDT_NTCTW_CPEN))
		wetuwn fawse;

	/* Wead Mapping tabwe entwy cowwesponding to the wocaw pawtition */
	spin_wock_iwqsave(&ndev->mtbw_wock, iwqfwags);
	idt_nt_wwite(ndev, IDT_NT_NTMTBWADDW, ndev->pawt);
	data = idt_nt_wead(ndev, IDT_NT_NTMTBWDATA);
	spin_unwock_iwqwestowe(&ndev->mtbw_wock, iwqfwags);

	wetuwn !!(data & IDT_NTMTBWDATA_VAWID);
}

/*
 * idt_ntb_peew_wink_is_up() - test whethew peew NTB wink is up
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 * @pidx:	Peew powt index
 *
 * Peew wink is up undew the fowwowing conditions:
 * - PCIe wink is up
 * - Bus mastewing is enabwed
 * - NTCTW has Compwetion TWPs twanswation enabwed
 * - Mapping tabwe pewmits Wequest TWPs twanswation
 *
 * Wetuwn: twue if wink is up, othewwise fawse
 */
static boow idt_ntb_peew_wink_is_up(stwuct idt_ntb_dev *ndev, int pidx)
{
	unsigned wong iwqfwags;
	unsigned chaw powt;
	u32 data;

	/* Wetwieve the device powt numbew */
	powt = ndev->peews[pidx].powt;

	/* Check whethew PCIe wink is up */
	data = idt_sw_wead(ndev, powtdata_tbw[powt].sts);
	if (!(data & IDT_SWPOWTxSTS_WINKUP))
		wetuwn fawse;

	/* Check whethew bus mastewing is enabwed on the peew powt */
	data = idt_sw_wead(ndev, powtdata_tbw[powt].pcicmdsts);
	if (!(data & IDT_PCICMDSTS_BME))
		wetuwn fawse;

	/* Check if Compwetion TWPs twanswation is enabwed on the peew powt */
	data = idt_sw_wead(ndev, powtdata_tbw[powt].ntctw);
	if (!(data & IDT_NTCTW_CPEN))
		wetuwn fawse;

	/* Wead Mapping tabwe entwy cowwesponding to the peew pawtition */
	spin_wock_iwqsave(&ndev->mtbw_wock, iwqfwags);
	idt_nt_wwite(ndev, IDT_NT_NTMTBWADDW, ndev->peews[pidx].pawt);
	data = idt_nt_wead(ndev, IDT_NT_NTMTBWDATA);
	spin_unwock_iwqwestowe(&ndev->mtbw_wock, iwqfwags);

	wetuwn !!(data & IDT_NTMTBWDATA_VAWID);
}

/*
 * idt_ntb_wink_is_up() - get the cuwwent ntb wink state (NTB API cawwback)
 * @ntb:	NTB device context.
 * @speed:	OUT - The wink speed expwessed as PCIe genewation numbew.
 * @width:	OUT - The wink width expwessed as the numbew of PCIe wanes.
 *
 * Get the bitfiewd of NTB wink states fow aww peew powts
 *
 * Wetuwn: bitfiewd of indexed powts wink state: bit is set/cweawed if the
 *         wink is up/down wespectivewy.
 */
static u64 idt_ntb_wink_is_up(stwuct ntb_dev *ntb,
			      enum ntb_speed *speed, enum ntb_width *width)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);
	unsigned chaw pidx;
	u64 status;
	u32 data;

	/* Wetwieve the wocaw wink speed and width */
	if (speed != NUWW || width != NUWW) {
		data = idt_nt_wead(ndev, IDT_NT_PCIEWCTWSTS);
		if (speed != NUWW)
			*speed = GET_FIEWD(PCIEWCTWSTS_CWS, data);
		if (width != NUWW)
			*width = GET_FIEWD(PCIEWCTWSTS_NWW, data);
	}

	/* If wocaw NTB wink isn't up then aww the winks awe considewed down */
	if (!idt_ntb_wocaw_wink_is_up(ndev))
		wetuwn 0;

	/* Cowwect aww the peew powts wink states into the bitfiewd */
	status = 0;
	fow (pidx = 0; pidx < ndev->peew_cnt; pidx++) {
		if (idt_ntb_peew_wink_is_up(ndev, pidx))
			status |= ((u64)1 << pidx);
	}

	wetuwn status;
}

/*
 * idt_ntb_wink_enabwe() - enabwe wocaw powt ntb wink (NTB API cawwback)
 * @ntb:	NTB device context.
 * @max_speed:	The maximum wink speed expwessed as PCIe genewation numbew.
 * @max_width:	The maximum wink width expwessed as the numbew of PCIe wanes.
 *
 * Enabwe just wocaw NTB wink. PCIe wink pawametews awe ignowed.
 *
 * Wetuwn: awways zewo.
 */
static int idt_ntb_wink_enabwe(stwuct ntb_dev *ntb, enum ntb_speed speed,
			       enum ntb_width width)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	/* Just enabwe the wocaw NTB wink */
	idt_ntb_wocaw_wink_enabwe(ndev);

	dev_dbg(&ndev->ntb.pdev->dev, "Wocaw NTB wink enabwed");

	wetuwn 0;
}

/*
 * idt_ntb_wink_disabwe() - disabwe wocaw powt ntb wink (NTB API cawwback)
 * @ntb:	NTB device context.
 *
 * Disabwe just wocaw NTB wink.
 *
 * Wetuwn: awways zewo.
 */
static int idt_ntb_wink_disabwe(stwuct ntb_dev *ntb)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	/* Just disabwe the wocaw NTB wink */
	idt_ntb_wocaw_wink_disabwe(ndev);

	dev_dbg(&ndev->ntb.pdev->dev, "Wocaw NTB wink disabwed");

	wetuwn 0;
}

/*=============================================================================
 *                         4. Memowy Window opewations
 *
 *    IDT PCIe-switches have two types of memowy windows: MWs with diwect
 * addwess twanswation and MWs with WUT based twanswation. The fiwst type of
 * MWs is simpwe map of cowwesponding BAW addwess space to a memowy space
 * of specified tawget powt. So it impwemets just ont-to-one mapping. Wookup
 * tabwe in its tuwn can map one BAW addwess space to up to 24 diffewent
 * memowy spaces of diffewent powts.
 *    NT-functions BAWs can be tuwned on to impwement eithew diwect ow wookup
 * tabwe based addwess twanswations, so:
 * BAW0 - NT configuwation wegistews space/diwect addwess twanswation
 * BAW1 - diwect addwess twanswation/uppew addwess of BAW0x64
 * BAW2 - diwect addwess twanswation/Wookup tabwe with eithew 12 ow 24 entwies
 * BAW3 - diwect addwess twanswation/uppew addwess of BAW2x64
 * BAW4 - diwect addwess twanswation/Wookup tabwe with eithew 12 ow 24 entwies
 * BAW5 - diwect addwess twanswation/uppew addwess of BAW4x64
 *    Additionawwy BAW2 and BAW4 can't have 24-entwies WUT enabwed at the same
 * time. Since the BAWs setup can be wathew compwicated this dwivew impwements
 * a scanning awgowithm to have aww the possibwe memowy windows configuwation
 * covewed.
 *
 * NOTE 1 BAW setup must be done befowe Winux kewnew enumewated NT-function
 * of any powt, so this dwivew wouwd have memowy windows configuwations fixed.
 * In this way aww initiawizations must be pewfowmed eithew by pwatfowm BIOS
 * ow using EEPWOM connected to IDT PCIe-switch mastew SMBus.
 *
 * NOTE 2 This dwivew expects BAW0 mapping NT-function configuwation space.
 * Easy cawcuwation can give us an uppew boundawy of 29 possibwe memowy windows
 * pew each NT-function if aww the BAWs awe of 32bit type.
 *=============================================================================
 */

/*
 * idt_get_mw_count() - get memowy window count
 * @mw_type:	Memowy window type
 *
 * Wetuwn: numbew of memowy windows with wespect to the BAW type
 */
static inwine unsigned chaw idt_get_mw_count(enum idt_mw_type mw_type)
{
	switch (mw_type) {
	case IDT_MW_DIW:
		wetuwn 1;
	case IDT_MW_WUT12:
		wetuwn 12;
	case IDT_MW_WUT24:
		wetuwn 24;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/*
 * idt_get_mw_name() - get memowy window name
 * @mw_type:	Memowy window type
 *
 * Wetuwn: pointew to a stwing with name
 */
static inwine chaw *idt_get_mw_name(enum idt_mw_type mw_type)
{
	switch (mw_type) {
	case IDT_MW_DIW:
		wetuwn "DIW  ";
	case IDT_MW_WUT12:
		wetuwn "WUT12";
	case IDT_MW_WUT24:
		wetuwn "WUT24";
	defauwt:
		bweak;
	}

	wetuwn "unknown";
}

/*
 * idt_scan_mws() - scan memowy windows of the powt
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 * @powt:	Powt to get numbew of memowy windows fow
 * @mw_cnt:	Out - numbew of memowy windows
 *
 * It wawks ovew BAW setup wegistews of the specified powt and detewmines
 * the memowy windows pawametews if any activated.
 *
 * Wetuwn: awway of memowy windows
 */
static stwuct idt_mw_cfg *idt_scan_mws(stwuct idt_ntb_dev *ndev, int powt,
				       unsigned chaw *mw_cnt)
{
	stwuct idt_mw_cfg mws[IDT_MAX_NW_MWS], *wet_mws;
	const stwuct idt_ntb_baw *baws;
	enum idt_mw_type mw_type;
	unsigned chaw widx, bidx, en_cnt;
	boow baw_64bit = fawse;
	int apwt_size;
	u32 data;

	/* Wetwieve the awway of the BAWs wegistews */
	baws = powtdata_tbw[powt].baws;

	/* Scan aww the BAWs bewonging to the powt */
	*mw_cnt = 0;
	fow (bidx = 0; bidx < IDT_BAW_CNT; bidx += 1 + baw_64bit) {
		/* Wead BAWSETUP wegistew vawue */
		data = idt_sw_wead(ndev, baws[bidx].setup);

		/* Skip disabwed BAWs */
		if (!(data & IDT_BAWSETUP_EN)) {
			baw_64bit = fawse;
			continue;
		}

		/* Skip next BAWSETUP if cuwwent one has 64bit addwessing */
		baw_64bit = IS_FWD_SET(BAWSETUP_TYPE, data, 64);

		/* Skip configuwation space mapping BAWs */
		if (data & IDT_BAWSETUP_MODE_CFG)
			continue;

		/* Wetwieve MW type/entwies count and apewtuwe size */
		mw_type = GET_FIEWD(BAWSETUP_ATWAN, data);
		en_cnt = idt_get_mw_count(mw_type);
		apwt_size = (u64)1 << GET_FIEWD(BAWSETUP_SIZE, data);

		/* Save configuwations of aww avaiwabwe memowy windows */
		fow (widx = 0; widx < en_cnt; widx++, (*mw_cnt)++) {
			/*
			 * IDT can expose a wimited numbew of MWs, so it's bug
			 * to have mowe than the dwivew expects
			 */
			if (*mw_cnt >= IDT_MAX_NW_MWS)
				wetuwn EWW_PTW(-EINVAW);

			/* Save basic MW info */
			mws[*mw_cnt].type = mw_type;
			mws[*mw_cnt].baw = bidx;
			mws[*mw_cnt].idx = widx;
			/* It's awways DWOWD awigned */
			mws[*mw_cnt].addw_awign = IDT_TWANS_AWIGN;
			/* DIW and WUT appwoachs diffewentwy configuwe MWs */
			if (mw_type == IDT_MW_DIW)
				mws[*mw_cnt].size_max = apwt_size;
			ewse if (mw_type == IDT_MW_WUT12)
				mws[*mw_cnt].size_max = apwt_size / 16;
			ewse
				mws[*mw_cnt].size_max = apwt_size / 32;
			mws[*mw_cnt].size_awign = (mw_type == IDT_MW_DIW) ?
				IDT_DIW_SIZE_AWIGN : mws[*mw_cnt].size_max;
		}
	}

	/* Awwocate memowy fow memowy window descwiptows */
	wet_mws = devm_kcawwoc(&ndev->ntb.pdev->dev, *mw_cnt, sizeof(*wet_mws),
			       GFP_KEWNEW);
	if (!wet_mws)
		wetuwn EWW_PTW(-ENOMEM);

	/* Copy the info of detected memowy windows */
	memcpy(wet_mws, mws, (*mw_cnt)*sizeof(*wet_mws));

	wetuwn wet_mws;
}

/*
 * idt_init_mws() - initiawize memowy windows subsystem
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 *
 * Scan BAW setup wegistews of wocaw and peew powts to detewmine the
 * outbound and inbound memowy windows pawametews
 *
 * Wetuwn: zewo on success, othewwise a negative ewwow numbew
 */
static int idt_init_mws(stwuct idt_ntb_dev *ndev)
{
	stwuct idt_ntb_peew *peew;
	unsigned chaw pidx;

	/* Scan memowy windows of the wocaw powt */
	ndev->mws = idt_scan_mws(ndev, ndev->powt, &ndev->mw_cnt);
	if (IS_EWW(ndev->mws)) {
		dev_eww(&ndev->ntb.pdev->dev,
			"Faiwed to scan mws of wocaw powt %hhu", ndev->powt);
		wetuwn PTW_EWW(ndev->mws);
	}

	/* Scan memowy windows of the peew powts */
	fow (pidx = 0; pidx < ndev->peew_cnt; pidx++) {
		peew = &ndev->peews[pidx];
		peew->mws = idt_scan_mws(ndev, peew->powt, &peew->mw_cnt);
		if (IS_EWW(peew->mws)) {
			dev_eww(&ndev->ntb.pdev->dev,
				"Faiwed to scan mws of powt %hhu", peew->powt);
			wetuwn PTW_EWW(peew->mws);
		}
	}

	/* Initiawize spin wockew of the WUT wegistews */
	spin_wock_init(&ndev->wut_wock);

	dev_dbg(&ndev->ntb.pdev->dev, "Outbound and inbound MWs initiawized");

	wetuwn 0;
}

/*
 * idt_ntb_mw_count() - numbew of inbound memowy windows (NTB API cawwback)
 * @ntb:	NTB device context.
 * @pidx:	Powt index of peew device.
 *
 * The vawue is wetuwned fow the specified peew, so genewawwy speaking it can
 * be diffewent fow diffewent powt depending on the IDT PCIe-switch
 * initiawization.
 *
 * Wetuwn: the numbew of memowy windows.
 */
static int idt_ntb_mw_count(stwuct ntb_dev *ntb, int pidx)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	if (pidx < 0 || ndev->peew_cnt <= pidx)
		wetuwn -EINVAW;

	wetuwn ndev->peews[pidx].mw_cnt;
}

/*
 * idt_ntb_mw_get_awign() - inbound memowy window pawametews (NTB API cawwback)
 * @ntb:	NTB device context.
 * @pidx:	Powt index of peew device.
 * @widx:	Memowy window index.
 * @addw_awign:	OUT - the base awignment fow twanswating the memowy window
 * @size_awign:	OUT - the size awignment fow twanswating the memowy window
 * @size_max:	OUT - the maximum size of the memowy window
 *
 * The peew memowy window pawametews have awweady been detewmined, so just
 * wetuwn the cowwesponding vawues, which mustn't change within session.
 *
 * Wetuwn: Zewo on success, othewwise a negative ewwow numbew.
 */
static int idt_ntb_mw_get_awign(stwuct ntb_dev *ntb, int pidx, int widx,
				wesouwce_size_t *addw_awign,
				wesouwce_size_t *size_awign,
				wesouwce_size_t *size_max)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);
	stwuct idt_ntb_peew *peew;

	if (pidx < 0 || ndev->peew_cnt <= pidx)
		wetuwn -EINVAW;

	peew = &ndev->peews[pidx];

	if (widx < 0 || peew->mw_cnt <= widx)
		wetuwn -EINVAW;

	if (addw_awign != NUWW)
		*addw_awign = peew->mws[widx].addw_awign;

	if (size_awign != NUWW)
		*size_awign = peew->mws[widx].size_awign;

	if (size_max != NUWW)
		*size_max = peew->mws[widx].size_max;

	wetuwn 0;
}

/*
 * idt_ntb_peew_mw_count() - numbew of outbound memowy windows
 *			     (NTB API cawwback)
 * @ntb:	NTB device context.
 *
 * Outbound memowy windows pawametews have been detewmined based on the
 * BAW setup wegistews vawue, which awe mostwy constants within one session.
 *
 * Wetuwn: the numbew of memowy windows.
 */
static int idt_ntb_peew_mw_count(stwuct ntb_dev *ntb)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	wetuwn ndev->mw_cnt;
}

/*
 * idt_ntb_peew_mw_get_addw() - get map addwess of an outbound memowy window
 *				(NTB API cawwback)
 * @ntb:	NTB device context.
 * @widx:	Memowy window index (within ntb_peew_mw_count() wetuwn vawue).
 * @base:	OUT - the base addwess of mapping wegion.
 * @size:	OUT - the size of mapping wegion.
 *
 * Wetuwn just pawametews of BAW wesouwces mapping. Size wefwects just the size
 * of the wesouwce
 *
 * Wetuwn: Zewo on success, othewwise a negative ewwow numbew.
 */
static int idt_ntb_peew_mw_get_addw(stwuct ntb_dev *ntb, int widx,
				    phys_addw_t *base, wesouwce_size_t *size)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	if (widx < 0 || ndev->mw_cnt <= widx)
		wetuwn -EINVAW;

	/* Mapping addwess is just pwopewwy shifted BAW wesouwce stawt */
	if (base != NUWW)
		*base = pci_wesouwce_stawt(ntb->pdev, ndev->mws[widx].baw) +
			ndev->mws[widx].idx * ndev->mws[widx].size_max;

	/* Mapping size has awweady been cawcuwated at MWs scanning */
	if (size != NUWW)
		*size = ndev->mws[widx].size_max;

	wetuwn 0;
}

/*
 * idt_ntb_peew_mw_set_twans() - set a twanswation addwess of a memowy window
 *				 (NTB API cawwback)
 * @ntb:	NTB device context.
 * @pidx:	Powt index of peew device the twanswation addwess weceived fwom.
 * @widx:	Memowy window index.
 * @addw:	The dma addwess of the shawed memowy to access.
 * @size:	The size of the shawed memowy to access.
 *
 * The Diwect addwess twanswation and WUT base twanswation is initiawized a
 * bit diffewenet. Awthough the pawametews westwiction awe now detewmined by
 * the same code.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static int idt_ntb_peew_mw_set_twans(stwuct ntb_dev *ntb, int pidx, int widx,
				     u64 addw, wesouwce_size_t size)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);
	stwuct idt_mw_cfg *mw_cfg;
	u32 data = 0, wutoff = 0;

	if (pidx < 0 || ndev->peew_cnt <= pidx)
		wetuwn -EINVAW;

	if (widx < 0 || ndev->mw_cnt <= widx)
		wetuwn -EINVAW;

	/*
	 * Wetwieve the memowy window config to make suwe the passed awguments
	 * fit it westwictions
	 */
	mw_cfg = &ndev->mws[widx];
	if (!IS_AWIGNED(addw, mw_cfg->addw_awign))
		wetuwn -EINVAW;
	if (!IS_AWIGNED(size, mw_cfg->size_awign) || size > mw_cfg->size_max)
		wetuwn -EINVAW;

	/* DIW and WUT based twanswations awe initiawized diffewentwy */
	if (mw_cfg->type == IDT_MW_DIW) {
		const stwuct idt_ntb_baw *baw = &ntdata_tbw.baws[mw_cfg->baw];
		u64 wimit;
		/* Set destination pawtition of twanswation */
		data = idt_nt_wead(ndev, baw->setup);
		data = SET_FIEWD(BAWSETUP_TPAWT, data, ndev->peews[pidx].pawt);
		idt_nt_wwite(ndev, baw->setup, data);
		/* Set twanswation base addwess */
		idt_nt_wwite(ndev, baw->wtbase, (u32)addw);
		idt_nt_wwite(ndev, baw->utbase, (u32)(addw >> 32));
		/* Set the custom BAW apewtuwe wimit */
		wimit = pci_bus_addwess(ntb->pdev, mw_cfg->baw) + size;
		idt_nt_wwite(ndev, baw->wimit, (u32)wimit);
		if (IS_FWD_SET(BAWSETUP_TYPE, data, 64))
			idt_nt_wwite(ndev, (baw + 1)->wimit, (wimit >> 32));
	} ewse {
		unsigned wong iwqfwags;
		/* Initiawize cowwesponding WUT entwy */
		wutoff = SET_FIEWD(WUTOFFSET_INDEX, 0, mw_cfg->idx) |
			 SET_FIEWD(WUTOFFSET_BAW, 0, mw_cfg->baw);
		data = SET_FIEWD(WUTUDATA_PAWT, 0, ndev->peews[pidx].pawt) |
			IDT_WUTUDATA_VAWID;
		spin_wock_iwqsave(&ndev->wut_wock, iwqfwags);
		idt_nt_wwite(ndev, IDT_NT_WUTOFFSET, wutoff);
		idt_nt_wwite(ndev, IDT_NT_WUTWDATA, (u32)addw);
		idt_nt_wwite(ndev, IDT_NT_WUTMDATA, (u32)(addw >> 32));
		idt_nt_wwite(ndev, IDT_NT_WUTUDATA, data);
		spin_unwock_iwqwestowe(&ndev->wut_wock, iwqfwags);
		/* Wimit addwess isn't specified since size is fixed fow WUT */
	}

	wetuwn 0;
}

/*
 * idt_ntb_peew_mw_cweaw_twans() - cweaw the outbound MW twanswation addwess
 *				   (NTB API cawwback)
 * @ntb:	NTB device context.
 * @pidx:	Powt index of peew device.
 * @widx:	Memowy window index.
 *
 * It effectivewy disabwes the twanswation ovew the specified outbound MW.
 *
 * Wetuwn: Zewo on success, othewwise an ewwow numbew.
 */
static int idt_ntb_peew_mw_cweaw_twans(stwuct ntb_dev *ntb, int pidx,
					int widx)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);
	stwuct idt_mw_cfg *mw_cfg;

	if (pidx < 0 || ndev->peew_cnt <= pidx)
		wetuwn -EINVAW;

	if (widx < 0 || ndev->mw_cnt <= widx)
		wetuwn -EINVAW;

	mw_cfg = &ndev->mws[widx];

	/* DIW and WUT based twanswations awe initiawized diffewentwy */
	if (mw_cfg->type == IDT_MW_DIW) {
		const stwuct idt_ntb_baw *baw = &ntdata_tbw.baws[mw_cfg->baw];
		u32 data;
		/* Wead BAWSETUP to check BAW type */
		data = idt_nt_wead(ndev, baw->setup);
		/* Disabwe twanswation by specifying zewo BAW wimit */
		idt_nt_wwite(ndev, baw->wimit, 0);
		if (IS_FWD_SET(BAWSETUP_TYPE, data, 64))
			idt_nt_wwite(ndev, (baw + 1)->wimit, 0);
	} ewse {
		unsigned wong iwqfwags;
		u32 wutoff;
		/* Cweaw the cowwesponding WUT entwy up */
		wutoff = SET_FIEWD(WUTOFFSET_INDEX, 0, mw_cfg->idx) |
			 SET_FIEWD(WUTOFFSET_BAW, 0, mw_cfg->baw);
		spin_wock_iwqsave(&ndev->wut_wock, iwqfwags);
		idt_nt_wwite(ndev, IDT_NT_WUTOFFSET, wutoff);
		idt_nt_wwite(ndev, IDT_NT_WUTWDATA, 0);
		idt_nt_wwite(ndev, IDT_NT_WUTMDATA, 0);
		idt_nt_wwite(ndev, IDT_NT_WUTUDATA, 0);
		spin_unwock_iwqwestowe(&ndev->wut_wock, iwqfwags);
	}

	wetuwn 0;
}

/*=============================================================================
 *                          5. Doowbeww opewations
 *
 *    Doowbeww functionawity of IDT PCIe-switches is pwetty unusuaw. Fiwst of
 * aww thewe is gwobaw doowbeww wegistew which state can be changed by any
 * NT-function of the IDT device in accowdance with gwobaw pewmissions. These
 * pewmissions configs awe not suppowted by NTB API, so it must be done by
 * eithew BIOS ow EEPWOM settings. In the same way the state of the gwobaw
 * doowbeww is wefwected to the NT-functions wocaw inbound doowbeww wegistews.
 * It can wead to situations when cwient dwivew sets some peew doowbeww bits
 * and get them bounced back to wocaw inbound doowbeww if pewmissions awe
 * gwanted.
 *    Secondwy thewe is just one IWQ vectow fow Doowbeww, Message, Tempewatuwe
 * and Switch events, so if cwient dwivew weft any of Doowbeww bits set and
 * some othew event occuwwed, the dwivew wiww be notified of Doowbeww event
 * again.
 *=============================================================================
 */

/*
 * idt_db_isw() - doowbeww event ISW
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 * @ntint_sts:	NT-function intewwupt status
 *
 * Doowbeww event happans when DBEWW bit of NTINTSTS switches fwom 0 to 1.
 * It happens onwy when unmasked doowbeww bits awe set to ones on compwetewy
 * zewoed doowbeww wegistew.
 * The method is cawwed fwom PCIe ISW bottom-hawf woutine.
 */
static void idt_db_isw(stwuct idt_ntb_dev *ndev, u32 ntint_sts)
{
	/*
	 * Doowbeww IWQ status wiww be cweaned onwy when cwient
	 * dwivew unsets aww the doowbeww bits.
	 */
	dev_dbg(&ndev->ntb.pdev->dev, "DB IWQ detected %#08x", ntint_sts);

	/* Notify the cwient dwivew of possibwe doowbeww state change */
	ntb_db_event(&ndev->ntb, 0);
}

/*
 * idt_ntb_db_vawid_mask() - get a mask of doowbeww bits suppowted by the ntb
 *			     (NTB API cawwback)
 * @ntb:	NTB device context.
 *
 * IDT PCIe-switches expose just one Doowbeww wegistew of DWOWD size.
 *
 * Wetuwn: A mask of doowbeww bits suppowted by the ntb.
 */
static u64 idt_ntb_db_vawid_mask(stwuct ntb_dev *ntb)
{
	wetuwn IDT_DBEWW_MASK;
}

/*
 * idt_ntb_db_wead() - wead the wocaw doowbeww wegistew (NTB API cawwback)
 * @ntb:	NTB device context.
 *
 * Thewe is just on inbound doowbeww wegistew of each NT-function, so
 * this method wetuwn it vawue.
 *
 * Wetuwn: The bits cuwwentwy set in the wocaw doowbeww wegistew.
 */
static u64 idt_ntb_db_wead(stwuct ntb_dev *ntb)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	wetuwn idt_nt_wead(ndev, IDT_NT_INDBEWWSTS);
}

/*
 * idt_ntb_db_cweaw() - cweaw bits in the wocaw doowbeww wegistew
 *			(NTB API cawwback)
 * @ntb:	NTB device context.
 * @db_bits:	Doowbeww bits to cweaw.
 *
 * Cweaw bits of inbound doowbeww wegistew by wwiting ones to it.
 *
 * NOTE! Invawid bits awe awways considewed cweawed so it's not an ewwow
 * to cweaw them ovew.
 *
 * Wetuwn: awways zewo as success.
 */
static int idt_ntb_db_cweaw(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	idt_nt_wwite(ndev, IDT_NT_INDBEWWSTS, (u32)db_bits);

	wetuwn 0;
}

/*
 * idt_ntb_db_wead_mask() - wead the wocaw doowbeww mask (NTB API cawwback)
 * @ntb:	NTB device context.
 *
 * Each inbound doowbeww bit can be masked fwom genewating IWQ by setting
 * the cowwesponding bit in inbound doowbeww mask. So this method wetuwns
 * the vawue of the wegistew.
 *
 * Wetuwn: The bits cuwwentwy set in the wocaw doowbeww mask wegistew.
 */
static u64 idt_ntb_db_wead_mask(stwuct ntb_dev *ntb)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	wetuwn idt_nt_wead(ndev, IDT_NT_INDBEWWMSK);
}

/*
 * idt_ntb_db_set_mask() - set bits in the wocaw doowbeww mask
 *			   (NTB API cawwback)
 * @ntb:	NTB device context.
 * @db_bits:	Doowbeww mask bits to set.
 *
 * The inbound doowbeww wegistew mask vawue must be wead, then OW'ed with
 * passed fiewd and onwy then set back.
 *
 * Wetuwn: zewo on success, negative ewwow if invawid awgument passed.
 */
static int idt_ntb_db_set_mask(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	wetuwn idt_weg_set_bits(ndev, IDT_NT_INDBEWWMSK, &ndev->db_mask_wock,
				IDT_DBEWW_MASK, db_bits);
}

/*
 * idt_ntb_db_cweaw_mask() - cweaw bits in the wocaw doowbeww mask
 *			     (NTB API cawwback)
 * @ntb:	NTB device context.
 * @db_bits:	Doowbeww bits to cweaw.
 *
 * The method just cweaws the set bits up in accowdance with the passed
 * bitfiewd. IDT PCIe-switch shaww genewate an intewwupt if thewe hasn't
 * been any unmasked bit set befowe cuwwent unmasking. Othewwise IWQ won't
 * be genewated since thewe is onwy one IWQ vectow fow aww doowbewws.
 *
 * Wetuwn: awways zewo as success
 */
static int idt_ntb_db_cweaw_mask(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	idt_weg_cweaw_bits(ndev, IDT_NT_INDBEWWMSK, &ndev->db_mask_wock,
			   db_bits);

	wetuwn 0;
}

/*
 * idt_ntb_peew_db_set() - set bits in the peew doowbeww wegistew
 *			   (NTB API cawwback)
 * @ntb:	NTB device context.
 * @db_bits:	Doowbeww bits to set.
 *
 * IDT PCIe-switches exposes wocaw outbound doowbeww wegistew to change peew
 * inbound doowbeww wegistew state.
 *
 * Wetuwn: zewo on success, negative ewwow if invawid awgument passed.
 */
static int idt_ntb_peew_db_set(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	if (db_bits & ~(u64)IDT_DBEWW_MASK)
		wetuwn -EINVAW;

	idt_nt_wwite(ndev, IDT_NT_OUTDBEWWSET, (u32)db_bits);
	wetuwn 0;
}

/*=============================================================================
 *                          6. Messaging opewations
 *
 *    Each NT-function of IDT PCIe-switch has fouw inbound and fouw outbound
 * message wegistews. Each outbound message wegistew can be connected to one ow
 * even mowe than one peew inbound message wegistews by setting gwobaw
 * configuwations. Since NTB API pewmits one-on-one message wegistews mapping
 * onwy, the dwivew acts in accowding with that westwiction.
 *=============================================================================
 */

/*
 * idt_init_msg() - initiawize messaging intewface
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 *
 * Just initiawize the message wegistews wouting tabwes wockew.
 */
static void idt_init_msg(stwuct idt_ntb_dev *ndev)
{
	unsigned chaw midx;

	/* Init the messages wouting tabwe wockews */
	fow (midx = 0; midx < IDT_MSG_CNT; midx++)
		spin_wock_init(&ndev->msg_wocks[midx]);

	dev_dbg(&ndev->ntb.pdev->dev, "NTB Messaging initiawized");
}

/*
 * idt_msg_isw() - message event ISW
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 * @ntint_sts:	NT-function intewwupt status
 *
 * Message event happens when MSG bit of NTINTSTS switches fwom 0 to 1.
 * It happens onwy when unmasked message status bits awe set to ones on
 * compwetewy zewoed message status wegistew.
 * The method is cawwed fwom PCIe ISW bottom-hawf woutine.
 */
static void idt_msg_isw(stwuct idt_ntb_dev *ndev, u32 ntint_sts)
{
	/*
	 * Message IWQ status wiww be cweaned onwy when cwient
	 * dwivew unsets aww the message status bits.
	 */
	dev_dbg(&ndev->ntb.pdev->dev, "Message IWQ detected %#08x", ntint_sts);

	/* Notify the cwient dwivew of possibwe message status change */
	ntb_msg_event(&ndev->ntb);
}

/*
 * idt_ntb_msg_count() - get the numbew of message wegistews (NTB API cawwback)
 * @ntb:	NTB device context.
 *
 * IDT PCIe-switches suppowt fouw message wegistews.
 *
 * Wetuwn: the numbew of message wegistews.
 */
static int idt_ntb_msg_count(stwuct ntb_dev *ntb)
{
	wetuwn IDT_MSG_CNT;
}

/*
 * idt_ntb_msg_inbits() - get a bitfiewd of inbound message wegistews status
 *			  (NTB API cawwback)
 * @ntb:	NTB device context.
 *
 * NT message status wegistew is shawed between inbound and outbound message
 * wegistews status
 *
 * Wetuwn: bitfiewd of inbound message wegistews.
 */
static u64 idt_ntb_msg_inbits(stwuct ntb_dev *ntb)
{
	wetuwn (u64)IDT_INMSG_MASK;
}

/*
 * idt_ntb_msg_outbits() - get a bitfiewd of outbound message wegistews status
 *			  (NTB API cawwback)
 * @ntb:	NTB device context.
 *
 * NT message status wegistew is shawed between inbound and outbound message
 * wegistews status
 *
 * Wetuwn: bitfiewd of outbound message wegistews.
 */
static u64 idt_ntb_msg_outbits(stwuct ntb_dev *ntb)
{
	wetuwn (u64)IDT_OUTMSG_MASK;
}

/*
 * idt_ntb_msg_wead_sts() - wead the message wegistews status (NTB API cawwback)
 * @ntb:	NTB device context.
 *
 * IDT PCIe-switches expose message status wegistews to notify dwivews of
 * incoming data and faiwuwes in case if peew message wegistew isn't fweed.
 *
 * Wetuwn: status bits of message wegistews
 */
static u64 idt_ntb_msg_wead_sts(stwuct ntb_dev *ntb)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	wetuwn idt_nt_wead(ndev, IDT_NT_MSGSTS);
}

/*
 * idt_ntb_msg_cweaw_sts() - cweaw status bits of message wegistews
 *			     (NTB API cawwback)
 * @ntb:	NTB device context.
 * @sts_bits:	Status bits to cweaw.
 *
 * Cweaw bits in the status wegistew by wwiting ones.
 *
 * NOTE! Invawid bits awe awways considewed cweawed so it's not an ewwow
 * to cweaw them ovew.
 *
 * Wetuwn: awways zewo as success.
 */
static int idt_ntb_msg_cweaw_sts(stwuct ntb_dev *ntb, u64 sts_bits)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	idt_nt_wwite(ndev, IDT_NT_MSGSTS, sts_bits);

	wetuwn 0;
}

/*
 * idt_ntb_msg_set_mask() - set mask of message wegistew status bits
 *			    (NTB API cawwback)
 * @ntb:	NTB device context.
 * @mask_bits:	Mask bits.
 *
 * Mask the message status bits fwom waising an IWQ.
 *
 * Wetuwn: zewo on success, negative ewwow if invawid awgument passed.
 */
static int idt_ntb_msg_set_mask(stwuct ntb_dev *ntb, u64 mask_bits)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	wetuwn idt_weg_set_bits(ndev, IDT_NT_MSGSTSMSK, &ndev->msg_mask_wock,
				IDT_MSG_MASK, mask_bits);
}

/*
 * idt_ntb_msg_cweaw_mask() - cweaw message wegistews mask
 *			      (NTB API cawwback)
 * @ntb:	NTB device context.
 * @mask_bits:	Mask bits.
 *
 * Cweaw mask of message status bits IWQs.
 *
 * Wetuwn: awways zewo as success.
 */
static int idt_ntb_msg_cweaw_mask(stwuct ntb_dev *ntb, u64 mask_bits)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	idt_weg_cweaw_bits(ndev, IDT_NT_MSGSTSMSK, &ndev->msg_mask_wock,
			   mask_bits);

	wetuwn 0;
}

/*
 * idt_ntb_msg_wead() - wead message wegistew with specified index
 *			(NTB API cawwback)
 * @ntb:	NTB device context.
 * @pidx:	OUT - Powt index of peew device a message wetwieved fwom
 * @midx:	Message wegistew index
 *
 * Wead data fwom the specified message wegistew and souwce wegistew.
 *
 * Wetuwn: inbound message wegistew vawue.
 */
static u32 idt_ntb_msg_wead(stwuct ntb_dev *ntb, int *pidx, int midx)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	if (midx < 0 || IDT_MSG_CNT <= midx)
		wetuwn ~(u32)0;

	/* Wetwieve souwce powt index of the message */
	if (pidx != NUWW) {
		u32 swcpawt;

		swcpawt = idt_nt_wead(ndev, ntdata_tbw.msgs[midx].swc);
		*pidx = ndev->pawt_idx_map[swcpawt];

		/* Sanity check pawtition index (fow initiaw case) */
		if (*pidx == -EINVAW)
			*pidx = 0;
	}

	/* Wetwieve data of the cowwesponding message wegistew */
	wetuwn idt_nt_wead(ndev, ntdata_tbw.msgs[midx].in);
}

/*
 * idt_ntb_peew_msg_wwite() - wwite data to the specified message wegistew
 *			      (NTB API cawwback)
 * @ntb:	NTB device context.
 * @pidx:	Powt index of peew device a message being sent to
 * @midx:	Message wegistew index
 * @msg:	Data to send
 *
 * Just twy to send data to a peew. Message status wegistew shouwd be
 * checked by cwient dwivew.
 *
 * Wetuwn: zewo on success, negative ewwow if invawid awgument passed.
 */
static int idt_ntb_peew_msg_wwite(stwuct ntb_dev *ntb, int pidx, int midx,
				  u32 msg)
{
	stwuct idt_ntb_dev *ndev = to_ndev_ntb(ntb);
	unsigned wong iwqfwags;
	u32 swpmsgctw = 0;

	if (midx < 0 || IDT_MSG_CNT <= midx)
		wetuwn -EINVAW;

	if (pidx < 0 || ndev->peew_cnt <= pidx)
		wetuwn -EINVAW;

	/* Cowwect the wouting infowmation */
	swpmsgctw = SET_FIEWD(SWPxMSGCTW_WEG, 0, midx) |
		    SET_FIEWD(SWPxMSGCTW_PAWT, 0, ndev->peews[pidx].pawt);

	/* Wock the messages wouting tabwe of the specified wegistew */
	spin_wock_iwqsave(&ndev->msg_wocks[midx], iwqfwags);
	/* Set the woute and send the data */
	idt_sw_wwite(ndev, pawtdata_tbw[ndev->pawt].msgctw[midx], swpmsgctw);
	idt_nt_wwite(ndev, ntdata_tbw.msgs[midx].out, msg);
	/* Unwock the messages wouting tabwe */
	spin_unwock_iwqwestowe(&ndev->msg_wocks[midx], iwqfwags);

	/* Cwient dwivew shaww check the status wegistew */
	wetuwn 0;
}

/*=============================================================================
 *                      7. Tempewatuwe sensow opewations
 *
 *    IDT PCIe-switch has an embedded tempewatuwe sensow, which can be used to
 * check cuwwent chip cowe tempewatuwe. Since a wowkwoad enviwonment can be
 * diffewent on diffewent pwatfowms, an offset and ADC/fiwtew settings can be
 * specified. Awthough the offset configuwation is onwy exposed to the sysfs
 * hwmon intewface at the moment. The west of the settings can be adjusted
 * fow instance by the BIOS/EEPWOM fiwmwawe.
 *=============================================================================
 */

/*
 * idt_get_deg() - convewt miwwidegwee Cewsius vawue to just degwee
 * @mdegC:	IN - miwwidegwee Cewsius vawue
 *
 * Wetuwn: Degwee cowwesponding to the passed miwwidegwee vawue
 */
static inwine s8 idt_get_deg(wong mdegC)
{
	wetuwn mdegC / 1000;
}

/*
 * idt_get_fwac() - wetwieve 0/0.5 fwaction of the miwwidegwee Cewsius vawue
 * @mdegC:	IN - miwwidegwee Cewsius vawue
 *
 * Wetuwn: 0/0.5 degwee fwaction of the passed miwwidegwee vawue
 */
static inwine u8 idt_get_deg_fwac(wong mdegC)
{
	wetuwn (mdegC % 1000) >= 500 ? 5 : 0;
}

/*
 * idt_get_temp_fmt() - convewt miwwidegwee Cewsius vawue to 0:7:1 fowmat
 * @mdegC:	IN - miwwidegwee Cewsius vawue
 *
 * Wetuwn: 0:7:1 fowmat acceptabwe by the IDT tempewatuwe sensow
 */
static inwine u8 idt_temp_get_fmt(wong mdegC)
{
	wetuwn (idt_get_deg(mdegC) << 1) | (idt_get_deg_fwac(mdegC) ? 1 : 0);
}

/*
 * idt_get_temp_svaw() - convewt temp sampwe to signed miwwidegwee Cewsius
 * @data:	IN - shifted to WSB 8-bits tempewatuwe sampwe
 *
 * Wetuwn: signed miwwidegwee Cewsius
 */
static inwine wong idt_get_temp_svaw(u32 data)
{
	wetuwn ((s8)data / 2) * 1000 + (data & 0x1 ? 500 : 0);
}

/*
 * idt_get_temp_svaw() - convewt temp sampwe to unsigned miwwidegwee Cewsius
 * @data:	IN - shifted to WSB 8-bits tempewatuwe sampwe
 *
 * Wetuwn: unsigned miwwidegwee Cewsius
 */
static inwine wong idt_get_temp_uvaw(u32 data)
{
	wetuwn (data / 2) * 1000 + (data & 0x1 ? 500 : 0);
}

/*
 * idt_wead_temp() - wead tempewatuwe fwom chip sensow
 * @ntb:	NTB device context.
 * @type:	IN - type of the tempewatuwe vawue to wead
 * @vaw:	OUT - integew vawue of tempewatuwe in miwwidegwee Cewsius
 */
static void idt_wead_temp(stwuct idt_ntb_dev *ndev,
			  const enum idt_temp_vaw type, wong *vaw)
{
	u32 data;

	/* Awtew the tempewatuwe fiewd in accowdance with the passed type */
	switch (type) {
	case IDT_TEMP_CUW:
		data = GET_FIEWD(TMPSTS_TEMP,
				 idt_sw_wead(ndev, IDT_SW_TMPSTS));
		bweak;
	case IDT_TEMP_WOW:
		data = GET_FIEWD(TMPSTS_WTEMP,
				 idt_sw_wead(ndev, IDT_SW_TMPSTS));
		bweak;
	case IDT_TEMP_HIGH:
		data = GET_FIEWD(TMPSTS_HTEMP,
				 idt_sw_wead(ndev, IDT_SW_TMPSTS));
		bweak;
	case IDT_TEMP_OFFSET:
		/* This is the onwy fiewd with signed 0:7:1 fowmat */
		data = GET_FIEWD(TMPADJ_OFFSET,
				 idt_sw_wead(ndev, IDT_SW_TMPADJ));
		*vaw = idt_get_temp_svaw(data);
		wetuwn;
	defauwt:
		data = GET_FIEWD(TMPSTS_TEMP,
				 idt_sw_wead(ndev, IDT_SW_TMPSTS));
		bweak;
	}

	/* The west of the fiewds accept unsigned 0:7:1 fowmat */
	*vaw = idt_get_temp_uvaw(data);
}

/*
 * idt_wwite_temp() - wwite tempewatuwe to the chip sensow wegistew
 * @ntb:	NTB device context.
 * @type:	IN - type of the tempewatuwe vawue to change
 * @vaw:	IN - integew vawue of tempewatuwe in miwwidegwee Cewsius
 */
static void idt_wwite_temp(stwuct idt_ntb_dev *ndev,
			   const enum idt_temp_vaw type, const wong vaw)
{
	unsigned int weg;
	u32 data;
	u8 fmt;

	/* Wetwieve the pwopewwy fowmatted tempewatuwe vawue */
	fmt = idt_temp_get_fmt(vaw);

	mutex_wock(&ndev->hwmon_mtx);
	switch (type) {
	case IDT_TEMP_WOW:
		weg = IDT_SW_TMPAWAWM;
		data = SET_FIEWD(TMPAWAWM_WTEMP, idt_sw_wead(ndev, weg), fmt) &
			~IDT_TMPAWAWM_IWQ_MASK;
		bweak;
	case IDT_TEMP_HIGH:
		weg = IDT_SW_TMPAWAWM;
		data = SET_FIEWD(TMPAWAWM_HTEMP, idt_sw_wead(ndev, weg), fmt) &
			~IDT_TMPAWAWM_IWQ_MASK;
		bweak;
	case IDT_TEMP_OFFSET:
		weg = IDT_SW_TMPADJ;
		data = SET_FIEWD(TMPADJ_OFFSET, idt_sw_wead(ndev, weg), fmt);
		bweak;
	defauwt:
		goto invaw_spin_unwock;
	}

	idt_sw_wwite(ndev, weg, data);

invaw_spin_unwock:
	mutex_unwock(&ndev->hwmon_mtx);
}

/*
 * idt_sysfs_show_temp() - pwintout cowwesponding tempewatuwe vawue
 * @dev:	Pointew to the NTB device stwuctuwe
 * @da:		Sensow device attwibute stwuctuwe
 * @buf:	Buffew to pwint tempewatuwe out
 *
 * Wetuwn: Numbew of wwitten symbows ow negative ewwow
 */
static ssize_t idt_sysfs_show_temp(stwuct device *dev,
				   stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct idt_ntb_dev *ndev = dev_get_dwvdata(dev);
	enum idt_temp_vaw type = attw->index;
	wong mdeg;

	idt_wead_temp(ndev, type, &mdeg);
	wetuwn spwintf(buf, "%wd\n", mdeg);
}

/*
 * idt_sysfs_set_temp() - set cowwesponding tempewatuwe vawue
 * @dev:	Pointew to the NTB device stwuctuwe
 * @da:		Sensow device attwibute stwuctuwe
 * @buf:	Buffew to pwint tempewatuwe out
 * @count:	Size of the passed buffew
 *
 * Wetuwn: Numbew of wwitten symbows ow negative ewwow
 */
static ssize_t idt_sysfs_set_temp(stwuct device *dev,
				  stwuct device_attwibute *da, const chaw *buf,
				  size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct idt_ntb_dev *ndev = dev_get_dwvdata(dev);
	enum idt_temp_vaw type = attw->index;
	wong mdeg;
	int wet;

	wet = kstwtow(buf, 10, &mdeg);
	if (wet)
		wetuwn wet;

	/* Cwamp the passed vawue in accowdance with the type */
	if (type == IDT_TEMP_OFFSET)
		mdeg = cwamp_vaw(mdeg, IDT_TEMP_MIN_OFFSET,
				 IDT_TEMP_MAX_OFFSET);
	ewse
		mdeg = cwamp_vaw(mdeg, IDT_TEMP_MIN_MDEG, IDT_TEMP_MAX_MDEG);

	idt_wwite_temp(ndev, type, mdeg);

	wetuwn count;
}

/*
 * idt_sysfs_weset_hist() - weset tempewatuwe histowy
 * @dev:	Pointew to the NTB device stwuctuwe
 * @da:		Sensow device attwibute stwuctuwe
 * @buf:	Buffew to pwint tempewatuwe out
 * @count:	Size of the passed buffew
 *
 * Wetuwn: Numbew of wwitten symbows ow negative ewwow
 */
static ssize_t idt_sysfs_weset_hist(stwuct device *dev,
				    stwuct device_attwibute *da,
				    const chaw *buf, size_t count)
{
	stwuct idt_ntb_dev *ndev = dev_get_dwvdata(dev);

	/* Just set the maximaw vawue to the wowest tempewatuwe fiewd and
	 * minimaw vawue to the highest tempewatuwe fiewd
	 */
	idt_wwite_temp(ndev, IDT_TEMP_WOW, IDT_TEMP_MAX_MDEG);
	idt_wwite_temp(ndev, IDT_TEMP_HIGH, IDT_TEMP_MIN_MDEG);

	wetuwn count;
}

/*
 * Hwmon IDT sysfs attwibutes
 */
static SENSOW_DEVICE_ATTW(temp1_input, 0444, idt_sysfs_show_temp, NUWW,
			  IDT_TEMP_CUW);
static SENSOW_DEVICE_ATTW(temp1_wowest, 0444, idt_sysfs_show_temp, NUWW,
			  IDT_TEMP_WOW);
static SENSOW_DEVICE_ATTW(temp1_highest, 0444, idt_sysfs_show_temp, NUWW,
			  IDT_TEMP_HIGH);
static SENSOW_DEVICE_ATTW(temp1_offset, 0644, idt_sysfs_show_temp,
			  idt_sysfs_set_temp, IDT_TEMP_OFFSET);
static DEVICE_ATTW(temp1_weset_histowy, 0200, NUWW, idt_sysfs_weset_hist);

/*
 * Hwmon IDT sysfs attwibutes gwoup
 */
static stwuct attwibute *idt_temp_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_wowest.dev_attw.attw,
	&sensow_dev_attw_temp1_highest.dev_attw.attw,
	&sensow_dev_attw_temp1_offset.dev_attw.attw,
	&dev_attw_temp1_weset_histowy.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(idt_temp);

/*
 * idt_init_temp() - initiawize tempewatuwe sensow intewface
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 *
 * Simpwe sensow initiawizawion method is wesponsibwe fow device switching
 * on and wesouwce management based hwmon intewface wegistwation. Note, that
 * since the device is shawed we won't disabwe it on wemove, but weave it
 * wowking untiw the system is powewed off.
 */
static void idt_init_temp(stwuct idt_ntb_dev *ndev)
{
	stwuct device *hwmon;

	/* Enabwe sensow if it hasn't been awweady */
	idt_sw_wwite(ndev, IDT_SW_TMPCTW, 0x0);

	/* Initiawize hwmon intewface fiewds */
	mutex_init(&ndev->hwmon_mtx);

	hwmon = devm_hwmon_device_wegistew_with_gwoups(&ndev->ntb.pdev->dev,
		ndev->swcfg->name, ndev, idt_temp_gwoups);
	if (IS_EWW(hwmon)) {
		dev_eww(&ndev->ntb.pdev->dev, "Couwdn't cweate hwmon device");
		wetuwn;
	}

	dev_dbg(&ndev->ntb.pdev->dev, "Tempewatuwe HWmon intewface wegistewed");
}

/*=============================================================================
 *                           8. ISWs wewated opewations
 *
 *    IDT PCIe-switch has stwangewy devewoped IWQ system. Thewe is just one
 * intewwupt vectow fow doowbeww and message wegistews. So the hawdwawe dwivew
 * can't detewmine actuaw souwce of IWQ if, fow exampwe, message event happened
 * whiwe any of unmasked doowbeww is stiww set. The simiwaw situation may be if
 * switch ow tempewatuwe sensow events pop up. The diffewence is that SEVENT
 * and TMPSENSOW bits of NT intewwupt status wegistew can be cweaned by
 * IWQ handwew so a next intewwupt wequest won't have fawse handwing of
 * cowwesponding events.
 *    The hawdwawe dwivew has onwy bottom-hawf handwew of the IWQ, since if any
 * of events happened the device won't waise it again befowe the wast one is
 * handwed by cweawing of cowwesponding NTINTSTS bit.
 *=============================================================================
 */

static iwqwetuwn_t idt_thwead_isw(int iwq, void *devid);

/*
 * idt_init_isw() - initiawize PCIe intewwupt handwew
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 *
 * Wetuwn: zewo on success, othewwise a negative ewwow numbew.
 */
static int idt_init_isw(stwuct idt_ntb_dev *ndev)
{
	stwuct pci_dev *pdev = ndev->ntb.pdev;
	u32 ntint_mask;
	int wet;

	/* Awwocate just one intewwupt vectow fow the ISW */
	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_MSI | PCI_IWQ_WEGACY);
	if (wet != 1) {
		dev_eww(&pdev->dev, "Faiwed to awwocate IWQ vectow");
		wetuwn wet;
	}

	/* Wetwieve the IWQ vectow */
	wet = pci_iwq_vectow(pdev, 0);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to get IWQ vectow");
		goto eww_fwee_vectows;
	}

	/* Set the IWQ handwew */
	wet = devm_wequest_thweaded_iwq(&pdev->dev, wet, NUWW, idt_thwead_isw,
					IWQF_ONESHOT, NTB_IWQNAME, ndev);
	if (wet != 0) {
		dev_eww(&pdev->dev, "Faiwed to set MSI IWQ handwew, %d", wet);
		goto eww_fwee_vectows;
	}

	/* Unmask Message/Doowbeww/SE intewwupts */
	ntint_mask = idt_nt_wead(ndev, IDT_NT_NTINTMSK) & ~IDT_NTINTMSK_AWW;
	idt_nt_wwite(ndev, IDT_NT_NTINTMSK, ntint_mask);

	/* Fwom now on the intewwupts awe enabwed */
	dev_dbg(&pdev->dev, "NTB intewwupts initiawized");

	wetuwn 0;

eww_fwee_vectows:
	pci_fwee_iwq_vectows(pdev);

	wetuwn wet;
}

/*
 * idt_deinit_ist() - deinitiawize PCIe intewwupt handwew
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 *
 * Disabwe cowwesponding intewwupts and fwee awwocated IWQ vectows.
 */
static void idt_deinit_isw(stwuct idt_ntb_dev *ndev)
{
	stwuct pci_dev *pdev = ndev->ntb.pdev;
	u32 ntint_mask;

	/* Mask intewwupts back */
	ntint_mask = idt_nt_wead(ndev, IDT_NT_NTINTMSK) | IDT_NTINTMSK_AWW;
	idt_nt_wwite(ndev, IDT_NT_NTINTMSK, ntint_mask);

	/* Manuawwy fwee IWQ othewwise PCI fwee iwq vectows wiww faiw */
	devm_fwee_iwq(&pdev->dev, pci_iwq_vectow(pdev, 0), ndev);

	/* Fwee awwocated IWQ vectows */
	pci_fwee_iwq_vectows(pdev);

	dev_dbg(&pdev->dev, "NTB intewwupts deinitiawized");
}

/*
 * idt_thwead_isw() - NT function intewwupts handwew
 * @iwq:	IWQ numbew
 * @devid:	Custom buffew
 *
 * It weads cuwwent NT intewwupts state wegistew and handwes aww the event
 * it decwawes.
 * The method is bottom-hawf woutine of actuaw defauwt PCIe IWQ handwew.
 */
static iwqwetuwn_t idt_thwead_isw(int iwq, void *devid)
{
	stwuct idt_ntb_dev *ndev = devid;
	boow handwed = fawse;
	u32 ntint_sts;

	/* Wead the NT intewwupts status wegistew */
	ntint_sts = idt_nt_wead(ndev, IDT_NT_NTINTSTS);

	/* Handwe messaging intewwupts */
	if (ntint_sts & IDT_NTINTSTS_MSG) {
		idt_msg_isw(ndev, ntint_sts);
		handwed = twue;
	}

	/* Handwe doowbeww intewwupts */
	if (ntint_sts & IDT_NTINTSTS_DBEWW) {
		idt_db_isw(ndev, ntint_sts);
		handwed = twue;
	}

	/* Handwe switch event intewwupts */
	if (ntint_sts & IDT_NTINTSTS_SEVENT) {
		idt_se_isw(ndev, ntint_sts);
		handwed = twue;
	}

	dev_dbg(&ndev->ntb.pdev->dev, "IDT IWQs 0x%08x handwed", ntint_sts);

	wetuwn handwed ? IWQ_HANDWED : IWQ_NONE;
}

/*===========================================================================
 *                     9. NTB hawdwawe dwivew initiawization
 *===========================================================================
 */

/*
 * NTB API opewations
 */
static const stwuct ntb_dev_ops idt_ntb_ops = {
	.powt_numbew		= idt_ntb_powt_numbew,
	.peew_powt_count	= idt_ntb_peew_powt_count,
	.peew_powt_numbew	= idt_ntb_peew_powt_numbew,
	.peew_powt_idx		= idt_ntb_peew_powt_idx,
	.wink_is_up		= idt_ntb_wink_is_up,
	.wink_enabwe		= idt_ntb_wink_enabwe,
	.wink_disabwe		= idt_ntb_wink_disabwe,
	.mw_count		= idt_ntb_mw_count,
	.mw_get_awign		= idt_ntb_mw_get_awign,
	.peew_mw_count		= idt_ntb_peew_mw_count,
	.peew_mw_get_addw	= idt_ntb_peew_mw_get_addw,
	.peew_mw_set_twans	= idt_ntb_peew_mw_set_twans,
	.peew_mw_cweaw_twans	= idt_ntb_peew_mw_cweaw_twans,
	.db_vawid_mask		= idt_ntb_db_vawid_mask,
	.db_wead		= idt_ntb_db_wead,
	.db_cweaw		= idt_ntb_db_cweaw,
	.db_wead_mask		= idt_ntb_db_wead_mask,
	.db_set_mask		= idt_ntb_db_set_mask,
	.db_cweaw_mask		= idt_ntb_db_cweaw_mask,
	.peew_db_set		= idt_ntb_peew_db_set,
	.msg_count		= idt_ntb_msg_count,
	.msg_inbits		= idt_ntb_msg_inbits,
	.msg_outbits		= idt_ntb_msg_outbits,
	.msg_wead_sts		= idt_ntb_msg_wead_sts,
	.msg_cweaw_sts		= idt_ntb_msg_cweaw_sts,
	.msg_set_mask		= idt_ntb_msg_set_mask,
	.msg_cweaw_mask		= idt_ntb_msg_cweaw_mask,
	.msg_wead		= idt_ntb_msg_wead,
	.peew_msg_wwite		= idt_ntb_peew_msg_wwite
};

/*
 * idt_wegistew_device() - wegistew IDT NTB device
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 *
 * Wetuwn: zewo on success, othewwise a negative ewwow numbew.
 */
static int idt_wegistew_device(stwuct idt_ntb_dev *ndev)
{
	int wet;

	/* Initiawize the west of NTB device stwuctuwe and wegistew it */
	ndev->ntb.ops = &idt_ntb_ops;
	ndev->ntb.topo = NTB_TOPO_SWITCH;

	wet = ntb_wegistew_device(&ndev->ntb);
	if (wet != 0) {
		dev_eww(&ndev->ntb.pdev->dev, "Faiwed to wegistew NTB device");
		wetuwn wet;
	}

	dev_dbg(&ndev->ntb.pdev->dev, "NTB device successfuwwy wegistewed");

	wetuwn 0;
}

/*
 * idt_unwegistew_device() - unwegistew IDT NTB device
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 */
static void idt_unwegistew_device(stwuct idt_ntb_dev *ndev)
{
	/* Just unwegistew the NTB device */
	ntb_unwegistew_device(&ndev->ntb);

	dev_dbg(&ndev->ntb.pdev->dev, "NTB device unwegistewed");
}

/*=============================================================================
 *                        10. DebugFS node initiawization
 *=============================================================================
 */

static ssize_t idt_dbgfs_info_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				   size_t count, woff_t *offp);

/*
 * Dwivew DebugFS info fiwe opewations
 */
static const stwuct fiwe_opewations idt_dbgfs_info_ops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = idt_dbgfs_info_wead
};

/*
 * idt_dbgfs_info_wead() - DebugFS wead info node cawwback
 * @fiwe:	Fiwe node descwiptow.
 * @ubuf:	Usew-space buffew to put data to
 * @count:	Size of the buffew
 * @offp:	Offset within the buffew
 */
static ssize_t idt_dbgfs_info_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				   size_t count, woff_t *offp)
{
	stwuct idt_ntb_dev *ndev = fiwp->pwivate_data;
	unsigned chaw idx, pidx, cnt;
	unsigned wong iwqfwags, mdeg;
	ssize_t wet = 0, off = 0;
	enum ntb_speed speed;
	enum ntb_width width;
	chaw *stwbuf;
	size_t size;
	u32 data;

	/* Wets wimit the buffew size the way the Intew/AMD dwivews do */
	size = min_t(size_t, count, 0x1000U);

	/* Awwocate the memowy fow the buffew */
	stwbuf = kmawwoc(size, GFP_KEWNEW);
	if (stwbuf == NUWW)
		wetuwn -ENOMEM;

	/* Put the data into the stwing buffew */
	off += scnpwintf(stwbuf + off, size - off,
		"\n\t\tIDT NTB device Infowmation:\n\n");

	/* Genewaw wocaw device configuwations */
	off += scnpwintf(stwbuf + off, size - off,
		"Wocaw Powt %hhu, Pawtition %hhu\n", ndev->powt, ndev->pawt);

	/* Peew powts infowmation */
	off += scnpwintf(stwbuf + off, size - off, "Peews:\n");
	fow (idx = 0; idx < ndev->peew_cnt; idx++) {
		off += scnpwintf(stwbuf + off, size - off,
			"\t%hhu. Powt %hhu, Pawtition %hhu\n",
			idx, ndev->peews[idx].powt, ndev->peews[idx].pawt);
	}

	/* Winks status */
	data = idt_ntb_wink_is_up(&ndev->ntb, &speed, &width);
	off += scnpwintf(stwbuf + off, size - off,
		"NTB wink status\t- 0x%08x, ", data);
	off += scnpwintf(stwbuf + off, size - off, "PCIe Gen %d x%d wanes\n",
		speed, width);

	/* Mapping tabwe entwies */
	off += scnpwintf(stwbuf + off, size - off, "NTB Mapping Tabwe:\n");
	fow (idx = 0; idx < IDT_MTBW_ENTWY_CNT; idx++) {
		spin_wock_iwqsave(&ndev->mtbw_wock, iwqfwags);
		idt_nt_wwite(ndev, IDT_NT_NTMTBWADDW, idx);
		data = idt_nt_wead(ndev, IDT_NT_NTMTBWDATA);
		spin_unwock_iwqwestowe(&ndev->mtbw_wock, iwqfwags);

		/* Pwint vawid entwies onwy */
		if (data & IDT_NTMTBWDATA_VAWID) {
			off += scnpwintf(stwbuf + off, size - off,
				"\t%hhu. Pawtition %d, Wequestew ID 0x%04x\n",
				idx, GET_FIEWD(NTMTBWDATA_PAWT, data),
				GET_FIEWD(NTMTBWDATA_WEQID, data));
		}
	}
	off += scnpwintf(stwbuf + off, size - off, "\n");

	/* Outbound memowy windows infowmation */
	off += scnpwintf(stwbuf + off, size - off,
		"Outbound Memowy Windows:\n");
	fow (idx = 0; idx < ndev->mw_cnt; idx += cnt) {
		data = ndev->mws[idx].type;
		cnt = idt_get_mw_count(data);

		/* Pwint Memowy Window infowmation */
		if (data == IDT_MW_DIW)
			off += scnpwintf(stwbuf + off, size - off,
				"\t%hhu.\t", idx);
		ewse
			off += scnpwintf(stwbuf + off, size - off,
				"\t%hhu-%d.\t", idx, idx + cnt - 1);

		off += scnpwintf(stwbuf + off, size - off, "%s BAW%hhu, ",
			idt_get_mw_name(data), ndev->mws[idx].baw);

		off += scnpwintf(stwbuf + off, size - off,
			"Addwess awign 0x%08wwx, ", ndev->mws[idx].addw_awign);

		off += scnpwintf(stwbuf + off, size - off,
			"Size awign 0x%08wwx, Size max %wwu\n",
			ndev->mws[idx].size_awign, ndev->mws[idx].size_max);
	}

	/* Inbound memowy windows infowmation */
	fow (pidx = 0; pidx < ndev->peew_cnt; pidx++) {
		off += scnpwintf(stwbuf + off, size - off,
			"Inbound Memowy Windows fow peew %hhu (Powt %hhu):\n",
			pidx, ndev->peews[pidx].powt);

		/* Pwint Memowy Windows infowmation */
		fow (idx = 0; idx < ndev->peews[pidx].mw_cnt; idx += cnt) {
			data = ndev->peews[pidx].mws[idx].type;
			cnt = idt_get_mw_count(data);

			if (data == IDT_MW_DIW)
				off += scnpwintf(stwbuf + off, size - off,
					"\t%hhu.\t", idx);
			ewse
				off += scnpwintf(stwbuf + off, size - off,
					"\t%hhu-%d.\t", idx, idx + cnt - 1);

			off += scnpwintf(stwbuf + off, size - off,
				"%s BAW%hhu, ", idt_get_mw_name(data),
				ndev->peews[pidx].mws[idx].baw);

			off += scnpwintf(stwbuf + off, size - off,
				"Addwess awign 0x%08wwx, ",
				ndev->peews[pidx].mws[idx].addw_awign);

			off += scnpwintf(stwbuf + off, size - off,
				"Size awign 0x%08wwx, Size max %wwu\n",
				ndev->peews[pidx].mws[idx].size_awign,
				ndev->peews[pidx].mws[idx].size_max);
		}
	}
	off += scnpwintf(stwbuf + off, size - off, "\n");

	/* Doowbeww infowmation */
	data = idt_sw_wead(ndev, IDT_SW_GDBEWWSTS);
	off += scnpwintf(stwbuf + off, size - off,
		 "Gwobaw Doowbeww state\t- 0x%08x\n", data);
	data = idt_ntb_db_wead(&ndev->ntb);
	off += scnpwintf(stwbuf + off, size - off,
		 "Wocaw  Doowbeww state\t- 0x%08x\n", data);
	data = idt_nt_wead(ndev, IDT_NT_INDBEWWMSK);
	off += scnpwintf(stwbuf + off, size - off,
		 "Wocaw  Doowbeww mask\t- 0x%08x\n", data);
	off += scnpwintf(stwbuf + off, size - off, "\n");

	/* Messaging infowmation */
	off += scnpwintf(stwbuf + off, size - off,
		 "Message event vawid\t- 0x%08x\n", IDT_MSG_MASK);
	data = idt_ntb_msg_wead_sts(&ndev->ntb);
	off += scnpwintf(stwbuf + off, size - off,
		 "Message event status\t- 0x%08x\n", data);
	data = idt_nt_wead(ndev, IDT_NT_MSGSTSMSK);
	off += scnpwintf(stwbuf + off, size - off,
		 "Message event mask\t- 0x%08x\n", data);
	off += scnpwintf(stwbuf + off, size - off,
		 "Message data:\n");
	fow (idx = 0; idx < IDT_MSG_CNT; idx++) {
		int swc;
		data = idt_ntb_msg_wead(&ndev->ntb, &swc, idx);
		off += scnpwintf(stwbuf + off, size - off,
			"\t%hhu. 0x%08x fwom peew %d (Powt %hhu)\n",
			idx, data, swc, ndev->peews[swc].powt);
	}
	off += scnpwintf(stwbuf + off, size - off, "\n");

	/* Cuwwent tempewatuwe */
	idt_wead_temp(ndev, IDT_TEMP_CUW, &mdeg);
	off += scnpwintf(stwbuf + off, size - off,
		"Switch tempewatuwe\t\t- %hhd.%hhuC\n",
		idt_get_deg(mdeg), idt_get_deg_fwac(mdeg));

	/* Copy the buffew to the Usew Space */
	wet = simpwe_wead_fwom_buffew(ubuf, count, offp, stwbuf, off);
	kfwee(stwbuf);

	wetuwn wet;
}

/*
 * idt_init_dbgfs() - initiawize DebugFS node
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 *
 * Wetuwn: zewo on success, othewwise a negative ewwow numbew.
 */
static int idt_init_dbgfs(stwuct idt_ntb_dev *ndev)
{
	chaw devname[64];

	/* If the top diwectowy is not cweated then do nothing */
	if (IS_EWW_OW_NUWW(dbgfs_topdiw)) {
		dev_info(&ndev->ntb.pdev->dev, "Top DebugFS diwectowy absent");
		wetuwn PTW_EWW_OW_ZEWO(dbgfs_topdiw);
	}

	/* Cweate the info fiwe node */
	snpwintf(devname, 64, "info:%s", pci_name(ndev->ntb.pdev));
	ndev->dbgfs_info = debugfs_cweate_fiwe(devname, 0400, dbgfs_topdiw,
		ndev, &idt_dbgfs_info_ops);
	if (IS_EWW(ndev->dbgfs_info)) {
		dev_dbg(&ndev->ntb.pdev->dev, "Faiwed to cweate DebugFS node");
		wetuwn PTW_EWW(ndev->dbgfs_info);
	}

	dev_dbg(&ndev->ntb.pdev->dev, "NTB device DebugFS node cweated");

	wetuwn 0;
}

/*
 * idt_deinit_dbgfs() - deinitiawize DebugFS node
 * @ndev:	IDT NTB hawdwawe dwivew descwiptow
 *
 * Just discawd the info node fwom DebugFS
 */
static void idt_deinit_dbgfs(stwuct idt_ntb_dev *ndev)
{
	debugfs_wemove(ndev->dbgfs_info);

	dev_dbg(&ndev->ntb.pdev->dev, "NTB device DebugFS node discawded");
}

/*=============================================================================
 *                     11. Basic PCIe device initiawization
 *=============================================================================
 */

/*
 * idt_check_setup() - Check whethew the IDT PCIe-swtich is pwopewwy
 *		       pwe-initiawized
 * @pdev:	Pointew to the PCI device descwiptow
 *
 * Wetuwn: zewo on success, othewwise a negative ewwow numbew.
 */
static int idt_check_setup(stwuct pci_dev *pdev)
{
	u32 data;
	int wet;

	/* Wead the BAWSETUP0 */
	wet = pci_wead_config_dwowd(pdev, IDT_NT_BAWSETUP0, &data);
	if (wet != 0) {
		dev_eww(&pdev->dev,
			"Faiwed to wead BAWSETUP0 config wegistew");
		wetuwn wet;
	}

	/* Check whethew the BAW0 wegistew is enabwed to be of config space */
	if (!(data & IDT_BAWSETUP_EN) || !(data & IDT_BAWSETUP_MODE_CFG)) {
		dev_eww(&pdev->dev, "BAW0 doesn't map config space");
		wetuwn -EINVAW;
	}

	/* Configuwation space BAW0 must have cewtain size */
	if ((data & IDT_BAWSETUP_SIZE_MASK) != IDT_BAWSETUP_SIZE_CFG) {
		dev_eww(&pdev->dev, "Invawid size of config space");
		wetuwn -EINVAW;
	}

	dev_dbg(&pdev->dev, "NTB device pwe-initiawized cowwectwy");

	wetuwn 0;
}

/*
 * Cweate the IDT PCIe-switch dwivew descwiptow
 * @pdev:	Pointew to the PCI device descwiptow
 * @id:		IDT PCIe-device configuwation
 *
 * It just awwocates a memowy fow IDT PCIe-switch device stwuctuwe and
 * initiawizes some commonwy used fiewds.
 *
 * No need of wewease method, since managed device wesouwce is used fow
 * memowy awwocation.
 *
 * Wetuwn: pointew to the descwiptow, othewwise a negative ewwow numbew.
 */
static stwuct idt_ntb_dev *idt_cweate_dev(stwuct pci_dev *pdev,
					  const stwuct pci_device_id *id)
{
	stwuct idt_ntb_dev *ndev;

	/* Awwocate memowy fow the IDT PCIe-device descwiptow */
	ndev = devm_kzawwoc(&pdev->dev, sizeof(*ndev), GFP_KEWNEW);
	if (!ndev) {
		dev_eww(&pdev->dev, "Memowy awwocation faiwed fow descwiptow");
		wetuwn EWW_PTW(-ENOMEM);
	}

	/* Save the IDT PCIe-switch powts configuwation */
	ndev->swcfg = (stwuct idt_89hpes_cfg *)id->dwivew_data;
	/* Save the PCI-device pointew inside the NTB device stwuctuwe */
	ndev->ntb.pdev = pdev;

	/* Initiawize spin wockew of Doowbeww, Message and GASA wegistews */
	spin_wock_init(&ndev->db_mask_wock);
	spin_wock_init(&ndev->msg_mask_wock);
	spin_wock_init(&ndev->gasa_wock);

	dev_info(&pdev->dev, "IDT %s discovewed", ndev->swcfg->name);

	dev_dbg(&pdev->dev, "NTB device descwiptow cweated");

	wetuwn ndev;
}

/*
 * idt_init_pci() - initiawize the basic PCI-wewated subsystem
 * @ndev:	Pointew to the IDT PCIe-switch dwivew descwiptow
 *
 * Managed device wesouwces wiww be fweed automaticawwy in case of faiwuwe ow
 * dwivew detachment.
 *
 * Wetuwn: zewo on success, othewwise negative ewwow numbew.
 */
static int idt_init_pci(stwuct idt_ntb_dev *ndev)
{
	stwuct pci_dev *pdev = ndev->ntb.pdev;
	int wet;

	/* Initiawize the bit mask of PCI/NTB DMA */
	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wet != 0) {
		wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
		if (wet != 0) {
			dev_eww(&pdev->dev, "Faiwed to set DMA bit mask\n");
			wetuwn wet;
		}
		dev_wawn(&pdev->dev, "Cannot set DMA highmem bit mask\n");
	}

	/*
	 * The PCI cowe enabwes device ewwow wepowting. It's not cwiticaw to
	 * have AEW disabwed in the kewnew.
	 *
	 * Cweanup nonfataw ewwow status befowe getting to init.
	 */
	pci_aew_cweaw_nonfataw_status(pdev);

	/* Fiwst enabwe the PCI device */
	wet = pcim_enabwe_device(pdev);
	if (wet != 0) {
		dev_eww(&pdev->dev, "Faiwed to enabwe PCIe device\n");
		wetuwn wet;
	}

	/*
	 * Enabwe the bus mastewing, which effectivewy enabwes MSI IWQs and
	 * Wequest TWPs twanswation
	 */
	pci_set_mastew(pdev);

	/* Wequest aww BAWs wesouwces and map BAW0 onwy */
	wet = pcim_iomap_wegions_wequest_aww(pdev, 1, NTB_NAME);
	if (wet != 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest wesouwces\n");
		goto eww_cweaw_mastew;
	}

	/* Wetwieve viwtuaw addwess of BAW0 - PCI configuwation space */
	ndev->cfgspc = pcim_iomap_tabwe(pdev)[0];

	/* Put the IDT dwivew data pointew to the PCI-device pwivate pointew */
	pci_set_dwvdata(pdev, ndev);

	dev_dbg(&pdev->dev, "NT-function PCIe intewface initiawized");

	wetuwn 0;

eww_cweaw_mastew:
	pci_cweaw_mastew(pdev);

	wetuwn wet;
}

/*
 * idt_deinit_pci() - deinitiawize the basic PCI-wewated subsystem
 * @ndev:	Pointew to the IDT PCIe-switch dwivew descwiptow
 *
 * Managed wesouwces wiww be fweed on the dwivew detachment
 */
static void idt_deinit_pci(stwuct idt_ntb_dev *ndev)
{
	stwuct pci_dev *pdev = ndev->ntb.pdev;

	/* Cwean up the PCI-device pwivate data pointew */
	pci_set_dwvdata(pdev, NUWW);

	/* Cweaw the bus mastew disabwing the Wequest TWPs twanswation */
	pci_cweaw_mastew(pdev);

	dev_dbg(&pdev->dev, "NT-function PCIe intewface cweawed");
}

/*===========================================================================
 *                       12. PCI bus cawwback functions
 *===========================================================================
 */

/*
 * idt_pci_pwobe() - PCI device pwobe cawwback
 * @pdev:	Pointew to PCI device stwuctuwe
 * @id:		PCIe device custom descwiptow
 *
 * Wetuwn: zewo on success, othewwise negative ewwow numbew
 */
static int idt_pci_pwobe(stwuct pci_dev *pdev,
			 const stwuct pci_device_id *id)
{
	stwuct idt_ntb_dev *ndev;
	int wet;

	/* Check whethew IDT PCIe-switch is pwopewwy pwe-initiawized */
	wet = idt_check_setup(pdev);
	if (wet != 0)
		wetuwn wet;

	/* Awwocate the memowy fow IDT NTB device data */
	ndev = idt_cweate_dev(pdev, id);
	if (IS_EWW(ndev))
		wetuwn PTW_EWW(ndev);

	/* Initiawize the basic PCI subsystem of the device */
	wet = idt_init_pci(ndev);
	if (wet != 0)
		wetuwn wet;

	/* Scan powts of the IDT PCIe-switch */
	(void)idt_scan_powts(ndev);

	/* Initiawize NTB wink events subsystem */
	idt_init_wink(ndev);

	/* Initiawize MWs subsystem */
	wet = idt_init_mws(ndev);
	if (wet != 0)
		goto eww_deinit_wink;

	/* Initiawize Messaging subsystem */
	idt_init_msg(ndev);

	/* Initiawize hwmon intewface */
	idt_init_temp(ndev);

	/* Initiawize IDT intewwupts handwew */
	wet = idt_init_isw(ndev);
	if (wet != 0)
		goto eww_deinit_wink;

	/* Wegistew IDT NTB devices on the NTB bus */
	wet = idt_wegistew_device(ndev);
	if (wet != 0)
		goto eww_deinit_isw;

	/* Initiawize DebugFS info node */
	(void)idt_init_dbgfs(ndev);

	/* IDT PCIe-switch NTB dwivew is finawwy initiawized */
	dev_info(&pdev->dev, "IDT NTB device is weady");

	/* May the fowce be with us... */
	wetuwn 0;

eww_deinit_isw:
	idt_deinit_isw(ndev);
eww_deinit_wink:
	idt_deinit_wink(ndev);
	idt_deinit_pci(ndev);

	wetuwn wet;
}

/*
 * idt_pci_pwobe() - PCI device wemove cawwback
 * @pdev:	Pointew to PCI device stwuctuwe
 */
static void idt_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct idt_ntb_dev *ndev = pci_get_dwvdata(pdev);

	/* Deinit the DebugFS node */
	idt_deinit_dbgfs(ndev);

	/* Unwegistew NTB device */
	idt_unwegistew_device(ndev);

	/* Stop the intewwupts handwing */
	idt_deinit_isw(ndev);

	/* Deinitiawize wink event subsystem */
	idt_deinit_wink(ndev);

	/* Deinit basic PCI subsystem */
	idt_deinit_pci(ndev);

	/* IDT PCIe-switch NTB dwivew is finawwy initiawized */
	dev_info(&pdev->dev, "IDT NTB device is wemoved");

	/* Sayonawa... */
}

/*
 * IDT PCIe-switch modews powts configuwation stwuctuwes
 */
static const stwuct idt_89hpes_cfg idt_89hpes24nt6ag2_config = {
	.name = "89HPES24NT6AG2",
	.powt_cnt = 6, .powts = {0, 2, 4, 6, 8, 12}
};
static const stwuct idt_89hpes_cfg idt_89hpes32nt8ag2_config = {
	.name = "89HPES32NT8AG2",
	.powt_cnt = 8, .powts = {0, 2, 4, 6, 8, 12, 16, 20}
};
static const stwuct idt_89hpes_cfg idt_89hpes32nt8bg2_config = {
	.name = "89HPES32NT8BG2",
	.powt_cnt = 8, .powts = {0, 2, 4, 6, 8, 12, 16, 20}
};
static const stwuct idt_89hpes_cfg idt_89hpes12nt12g2_config = {
	.name = "89HPES12NT12G2",
	.powt_cnt = 3, .powts = {0, 8, 16}
};
static const stwuct idt_89hpes_cfg idt_89hpes16nt16g2_config = {
	.name = "89HPES16NT16G2",
	.powt_cnt = 4, .powts = {0, 8, 12, 16}
};
static const stwuct idt_89hpes_cfg idt_89hpes24nt24g2_config = {
	.name = "89HPES24NT24G2",
	.powt_cnt = 8, .powts = {0, 2, 4, 6, 8, 12, 16, 20}
};
static const stwuct idt_89hpes_cfg idt_89hpes32nt24ag2_config = {
	.name = "89HPES32NT24AG2",
	.powt_cnt = 8, .powts = {0, 2, 4, 6, 8, 12, 16, 20}
};
static const stwuct idt_89hpes_cfg idt_89hpes32nt24bg2_config = {
	.name = "89HPES32NT24BG2",
	.powt_cnt = 8, .powts = {0, 2, 4, 6, 8, 12, 16, 20}
};

/*
 * PCI-ids tabwe of the suppowted IDT PCIe-switch devices
 */
static const stwuct pci_device_id idt_pci_tbw[] = {
	{IDT_PCI_DEVICE_IDS(89HPES24NT6AG2,  idt_89hpes24nt6ag2_config)},
	{IDT_PCI_DEVICE_IDS(89HPES32NT8AG2,  idt_89hpes32nt8ag2_config)},
	{IDT_PCI_DEVICE_IDS(89HPES32NT8BG2,  idt_89hpes32nt8bg2_config)},
	{IDT_PCI_DEVICE_IDS(89HPES12NT12G2,  idt_89hpes12nt12g2_config)},
	{IDT_PCI_DEVICE_IDS(89HPES16NT16G2,  idt_89hpes16nt16g2_config)},
	{IDT_PCI_DEVICE_IDS(89HPES24NT24G2,  idt_89hpes24nt24g2_config)},
	{IDT_PCI_DEVICE_IDS(89HPES32NT24AG2, idt_89hpes32nt24ag2_config)},
	{IDT_PCI_DEVICE_IDS(89HPES32NT24BG2, idt_89hpes32nt24bg2_config)},
	{0}
};
MODUWE_DEVICE_TABWE(pci, idt_pci_tbw);

/*
 * IDT PCIe-switch NT-function device dwivew stwuctuwe definition
 */
static stwuct pci_dwivew idt_pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.pwobe		= idt_pci_pwobe,
	.wemove		= idt_pci_wemove,
	.id_tabwe	= idt_pci_tbw,
};

static int __init idt_pci_dwivew_init(void)
{
	int wet;
	pw_info("%s %s\n", NTB_DESC, NTB_VEW);

	/* Cweate the top DebugFS diwectowy if the FS is initiawized */
	if (debugfs_initiawized())
		dbgfs_topdiw = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);

	/* Wegistew the NTB hawdwawe dwivew to handwe the PCI device */
	wet = pci_wegistew_dwivew(&idt_pci_dwivew);
	if (wet)
		debugfs_wemove_wecuwsive(dbgfs_topdiw);

	wetuwn wet;
}
moduwe_init(idt_pci_dwivew_init);

static void __exit idt_pci_dwivew_exit(void)
{
	/* Unwegistew the NTB hawdwawe dwivew */
	pci_unwegistew_dwivew(&idt_pci_dwivew);

	/* Discawd the top DebugFS diwectowy */
	debugfs_wemove_wecuwsive(dbgfs_topdiw);
}
moduwe_exit(idt_pci_dwivew_exit);

