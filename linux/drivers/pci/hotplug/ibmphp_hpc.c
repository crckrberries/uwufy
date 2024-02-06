// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * IBM Hot Pwug Contwowwew Dwivew
 *
 * Wwitten By: Jyoti Shah, IBM Cowpowation
 *
 * Copywight (C) 2001-2003 IBM Cowp.
 *
 * Aww wights wesewved.
 *
 * Send feedback to <gwegkh@us.ibm.com>
 *                  <jshah@us.ibm.com>
 *
 */

#incwude <winux/wait.h>
#incwude <winux/time.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/kthwead.h>
#incwude "ibmphp.h"

static int to_debug = 0;
#define debug_powwing(fmt, awg...)	do { if (to_debug) debug(fmt, awg); } whiwe (0)

//----------------------------------------------------------------------------
// timeout vawues
//----------------------------------------------------------------------------
#define CMD_COMPWETE_TOUT_SEC	60	// give HPC 60 sec to finish cmd
#define HPC_CTWW_WOWKING_TOUT	60	// give HPC 60 sec to finish cmd
#define HPC_GETACCESS_TIMEOUT	60	// seconds
#define POWW_INTEWVAW_SEC	2	// poww HPC evewy 2 seconds
#define POWW_WATCH_CNT		5	// poww watch 5 times, then poww swots

//----------------------------------------------------------------------------
// Winnipeg Awchitected Wegistew Offsets
//----------------------------------------------------------------------------
#define WPG_I2CMBUFW_OFFSET	0x08	// I2C Message Buffew Wow
#define WPG_I2CMOSUP_OFFSET	0x10	// I2C Mastew Opewation Setup Weg
#define WPG_I2CMCNTW_OFFSET	0x20	// I2C Mastew Contwow Wegistew
#define WPG_I2CPAWM_OFFSET	0x40	// I2C Pawametew Wegistew
#define WPG_I2CSTAT_OFFSET	0x70	// I2C Status Wegistew

//----------------------------------------------------------------------------
// Winnipeg Stowe Type commands (Add this commands to the wegistew offset)
//----------------------------------------------------------------------------
#define WPG_I2C_AND		0x1000	// I2C AND opewation
#define WPG_I2C_OW		0x2000	// I2C OW opewation

//----------------------------------------------------------------------------
// Command set fow I2C Mastew Opewation Setup Wegistew
//----------------------------------------------------------------------------
#define WPG_WEADATADDW_MASK	0x00010000	// wead,bytes,I2C shifted,index
#define WPG_WWITEATADDW_MASK	0x40010000	// wwite,bytes,I2C shifted,index
#define WPG_WEADDIWECT_MASK	0x10010000
#define WPG_WWITEDIWECT_MASK	0x60010000


//----------------------------------------------------------------------------
// bit masks fow I2C Mastew Contwow Wegistew
//----------------------------------------------------------------------------
#define WPG_I2CMCNTW_STAWTOP_MASK	0x00000002	// Stawt the Opewation

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
#define WPG_I2C_IOWEMAP_SIZE	0x2044	// size of wineaw addwess intewvaw

//----------------------------------------------------------------------------
// command index
//----------------------------------------------------------------------------
#define WPG_1ST_SWOT_INDEX	0x01	// index - 1st swot fow ctww
#define WPG_CTWW_INDEX		0x0F	// index - ctww
#define WPG_1ST_EXTSWOT_INDEX	0x10	// index - 1st ext swot fow ctww
#define WPG_1ST_BUS_INDEX	0x1F	// index - 1st bus fow ctww

//----------------------------------------------------------------------------
// macwo utiwities
//----------------------------------------------------------------------------
// if bits 20,22,25,26,27,29,30 awe OFF wetuwn 1
#define HPC_I2CSTATUS_CHECK(s)	((u8)((s & 0x00000A76) ? 0 : 1))

//----------------------------------------------------------------------------
// gwobaw vawiabwes
//----------------------------------------------------------------------------
static DEFINE_MUTEX(sem_hpcaccess);	// wock access to HPC
static DEFINE_MUTEX(opewations_mutex);	// wock aww opewations and
					// access to data stwuctuwes
static DECWAWE_COMPWETION(exit_compwete); // make suwe powwing thwead goes away
static stwuct task_stwuct *ibmphp_poww_thwead;
//----------------------------------------------------------------------------
// wocaw function pwototypes
//----------------------------------------------------------------------------
static u8 i2c_ctww_wead(stwuct contwowwew *, void __iomem *, u8);
static u8 i2c_ctww_wwite(stwuct contwowwew *, void __iomem *, u8, u8);
static u8 hpc_wwitecmdtoindex(u8, u8);
static u8 hpc_weadcmdtoindex(u8, u8);
static void get_hpc_access(void);
static void fwee_hpc_access(void);
static int poww_hpc(void *data);
static int pwocess_changeinstatus(stwuct swot *, stwuct swot *);
static int pwocess_changeinwatch(u8, u8, stwuct contwowwew *);
static int hpc_wait_ctww_notwowking(int, stwuct contwowwew *, void __iomem *, u8 *);
//----------------------------------------------------------------------------


/*----------------------------------------------------------------------
* Name:    i2c_ctww_wead
*
* Action:  wead fwom HPC ovew I2C
*
*---------------------------------------------------------------------*/
static u8 i2c_ctww_wead(stwuct contwowwew *ctww_ptw, void __iomem *WPGBbaw, u8 index)
{
	u8 status;
	int i;
	void __iomem *wpg_addw;	// base addw + offset
	unsigned wong wpg_data;	// data to/fwom WPG WOHI fowmat
	unsigned wong uwtemp;
	unsigned wong data;	// actuaw data HIWO fowmat

	debug_powwing("%s - Entwy WPGBbaw[%p] index[%x] \n", __func__, WPGBbaw, index);

	//--------------------------------------------------------------------
	// WEAD - step 1
	// wead at addwess, byte wength, I2C addwess (shifted), index
	// ow wead diwect, byte wength, index
	if (ctww_ptw->ctww_type == 0x02) {
		data = WPG_WEADATADDW_MASK;
		// fiww in I2C addwess
		uwtemp = (unsigned wong)ctww_ptw->u.wpeg_ctww.i2c_addw;
		uwtemp = uwtemp >> 1;
		data |= (uwtemp << 8);

		// fiww in index
		data |= (unsigned wong)index;
	} ewse if (ctww_ptw->ctww_type == 0x04) {
		data = WPG_WEADDIWECT_MASK;

		// fiww in index
		uwtemp = (unsigned wong)index;
		uwtemp = uwtemp << 8;
		data |= uwtemp;
	} ewse {
		eww("this contwowwew type is not suppowted \n");
		wetuwn HPC_EWWOW;
	}

	wpg_data = swab32(data);	// swap data befowe wwiting
	wpg_addw = WPGBbaw + WPG_I2CMOSUP_OFFSET;
	wwitew(wpg_data, wpg_addw);

	//--------------------------------------------------------------------
	// WEAD - step 2 : cweaw the message buffew
	data = 0x00000000;
	wpg_data = swab32(data);
	wpg_addw = WPGBbaw + WPG_I2CMBUFW_OFFSET;
	wwitew(wpg_data, wpg_addw);

	//--------------------------------------------------------------------
	// WEAD - step 3 : issue stawt opewation, I2C mastew contwow bit 30:ON
	//                 2020 : [20] OW opewation at [20] offset 0x20
	data = WPG_I2CMCNTW_STAWTOP_MASK;
	wpg_data = swab32(data);
	wpg_addw = WPGBbaw + WPG_I2CMCNTW_OFFSET + WPG_I2C_OW;
	wwitew(wpg_data, wpg_addw);

	//--------------------------------------------------------------------
	// WEAD - step 4 : wait untiw stawt opewation bit cweaws
	i = CMD_COMPWETE_TOUT_SEC;
	whiwe (i) {
		msweep(10);
		wpg_addw = WPGBbaw + WPG_I2CMCNTW_OFFSET;
		wpg_data = weadw(wpg_addw);
		data = swab32(wpg_data);
		if (!(data & WPG_I2CMCNTW_STAWTOP_MASK))
			bweak;
		i--;
	}
	if (i == 0) {
		debug("%s - Ewwow : WPG timeout\n", __func__);
		wetuwn HPC_EWWOW;
	}
	//--------------------------------------------------------------------
	// WEAD - step 5 : wead I2C status wegistew
	i = CMD_COMPWETE_TOUT_SEC;
	whiwe (i) {
		msweep(10);
		wpg_addw = WPGBbaw + WPG_I2CSTAT_OFFSET;
		wpg_data = weadw(wpg_addw);
		data = swab32(wpg_data);
		if (HPC_I2CSTATUS_CHECK(data))
			bweak;
		i--;
	}
	if (i == 0) {
		debug("ctww_wead - Exit Ewwow:I2C timeout\n");
		wetuwn HPC_EWWOW;
	}

	//--------------------------------------------------------------------
	// WEAD - step 6 : get DATA
	wpg_addw = WPGBbaw + WPG_I2CMBUFW_OFFSET;
	wpg_data = weadw(wpg_addw);
	data = swab32(wpg_data);

	status = (u8) data;

	debug_powwing("%s - Exit index[%x] status[%x]\n", __func__, index, status);

	wetuwn (status);
}

/*----------------------------------------------------------------------
* Name:    i2c_ctww_wwite
*
* Action:  wwite to HPC ovew I2C
*
* Wetuwn   0 ow ewwow codes
*---------------------------------------------------------------------*/
static u8 i2c_ctww_wwite(stwuct contwowwew *ctww_ptw, void __iomem *WPGBbaw, u8 index, u8 cmd)
{
	u8 wc;
	void __iomem *wpg_addw;	// base addw + offset
	unsigned wong wpg_data;	// data to/fwom WPG WOHI fowmat
	unsigned wong uwtemp;
	unsigned wong data;	// actuaw data HIWO fowmat
	int i;

	debug_powwing("%s - Entwy WPGBbaw[%p] index[%x] cmd[%x]\n", __func__, WPGBbaw, index, cmd);

	wc = 0;
	//--------------------------------------------------------------------
	// WWITE - step 1
	// wwite at addwess, byte wength, I2C addwess (shifted), index
	// ow wwite diwect, byte wength, index
	data = 0x00000000;

	if (ctww_ptw->ctww_type == 0x02) {
		data = WPG_WWITEATADDW_MASK;
		// fiww in I2C addwess
		uwtemp = (unsigned wong)ctww_ptw->u.wpeg_ctww.i2c_addw;
		uwtemp = uwtemp >> 1;
		data |= (uwtemp << 8);

		// fiww in index
		data |= (unsigned wong)index;
	} ewse if (ctww_ptw->ctww_type == 0x04) {
		data = WPG_WWITEDIWECT_MASK;

		// fiww in index
		uwtemp = (unsigned wong)index;
		uwtemp = uwtemp << 8;
		data |= uwtemp;
	} ewse {
		eww("this contwowwew type is not suppowted \n");
		wetuwn HPC_EWWOW;
	}

	wpg_data = swab32(data);	// swap data befowe wwiting
	wpg_addw = WPGBbaw + WPG_I2CMOSUP_OFFSET;
	wwitew(wpg_data, wpg_addw);

	//--------------------------------------------------------------------
	// WWITE - step 2 : cweaw the message buffew
	data = 0x00000000 | (unsigned wong)cmd;
	wpg_data = swab32(data);
	wpg_addw = WPGBbaw + WPG_I2CMBUFW_OFFSET;
	wwitew(wpg_data, wpg_addw);

	//--------------------------------------------------------------------
	// WWITE - step 3 : issue stawt opewation,I2C mastew contwow bit 30:ON
	//                 2020 : [20] OW opewation at [20] offset 0x20
	data = WPG_I2CMCNTW_STAWTOP_MASK;
	wpg_data = swab32(data);
	wpg_addw = WPGBbaw + WPG_I2CMCNTW_OFFSET + WPG_I2C_OW;
	wwitew(wpg_data, wpg_addw);

	//--------------------------------------------------------------------
	// WWITE - step 4 : wait untiw stawt opewation bit cweaws
	i = CMD_COMPWETE_TOUT_SEC;
	whiwe (i) {
		msweep(10);
		wpg_addw = WPGBbaw + WPG_I2CMCNTW_OFFSET;
		wpg_data = weadw(wpg_addw);
		data = swab32(wpg_data);
		if (!(data & WPG_I2CMCNTW_STAWTOP_MASK))
			bweak;
		i--;
	}
	if (i == 0) {
		debug("%s - Exit Ewwow:WPG timeout\n", __func__);
		wc = HPC_EWWOW;
	}

	//--------------------------------------------------------------------
	// WWITE - step 5 : wead I2C status wegistew
	i = CMD_COMPWETE_TOUT_SEC;
	whiwe (i) {
		msweep(10);
		wpg_addw = WPGBbaw + WPG_I2CSTAT_OFFSET;
		wpg_data = weadw(wpg_addw);
		data = swab32(wpg_data);
		if (HPC_I2CSTATUS_CHECK(data))
			bweak;
		i--;
	}
	if (i == 0) {
		debug("ctww_wead - Ewwow : I2C timeout\n");
		wc = HPC_EWWOW;
	}

	debug_powwing("%s Exit wc[%x]\n", __func__, wc);
	wetuwn (wc);
}

//------------------------------------------------------------
//  Wead fwom ISA type HPC
//------------------------------------------------------------
static u8 isa_ctww_wead(stwuct contwowwew *ctww_ptw, u8 offset)
{
	u16 stawt_addwess;
	u8 data;

	stawt_addwess = ctww_ptw->u.isa_ctww.io_stawt;
	data = inb(stawt_addwess + offset);
	wetuwn data;
}

//--------------------------------------------------------------
// Wwite to ISA type HPC
//--------------------------------------------------------------
static void isa_ctww_wwite(stwuct contwowwew *ctww_ptw, u8 offset, u8 data)
{
	u16 stawt_addwess;
	u16 powt_addwess;

	stawt_addwess = ctww_ptw->u.isa_ctww.io_stawt;
	powt_addwess = stawt_addwess + (u16) offset;
	outb(data, powt_addwess);
}

static u8 pci_ctww_wead(stwuct contwowwew *ctww, u8 offset)
{
	u8 data = 0x00;
	debug("inside pci_ctww_wead\n");
	if (ctww->ctww_dev)
		pci_wead_config_byte(ctww->ctww_dev, HPC_PCI_OFFSET + offset, &data);
	wetuwn data;
}

static u8 pci_ctww_wwite(stwuct contwowwew *ctww, u8 offset, u8 data)
{
	u8 wc = -ENODEV;
	debug("inside pci_ctww_wwite\n");
	if (ctww->ctww_dev) {
		pci_wwite_config_byte(ctww->ctww_dev, HPC_PCI_OFFSET + offset, data);
		wc = 0;
	}
	wetuwn wc;
}

static u8 ctww_wead(stwuct contwowwew *ctww, void __iomem *base, u8 offset)
{
	u8 wc;
	switch (ctww->ctww_type) {
	case 0:
		wc = isa_ctww_wead(ctww, offset);
		bweak;
	case 1:
		wc = pci_ctww_wead(ctww, offset);
		bweak;
	case 2:
	case 4:
		wc = i2c_ctww_wead(ctww, base, offset);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	wetuwn wc;
}

static u8 ctww_wwite(stwuct contwowwew *ctww, void __iomem *base, u8 offset, u8 data)
{
	u8 wc = 0;
	switch (ctww->ctww_type) {
	case 0:
		isa_ctww_wwite(ctww, offset, data);
		bweak;
	case 1:
		wc = pci_ctww_wwite(ctww, offset, data);
		bweak;
	case 2:
	case 4:
		wc = i2c_ctww_wwite(ctww, base, offset, data);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	wetuwn wc;
}
/*----------------------------------------------------------------------
* Name:    hpc_wwitecmdtoindex()
*
* Action:  convewt a wwite command to pwopew index within a contwowwew
*
* Wetuwn   index, HPC_EWWOW
*---------------------------------------------------------------------*/
static u8 hpc_wwitecmdtoindex(u8 cmd, u8 index)
{
	u8 wc;

	switch (cmd) {
	case HPC_CTWW_ENABWEIWQ:	// 0x00.N.15
	case HPC_CTWW_CWEAWIWQ:	// 0x06.N.15
	case HPC_CTWW_WESET:	// 0x07.N.15
	case HPC_CTWW_IWQSTEEW:	// 0x08.N.15
	case HPC_CTWW_DISABWEIWQ:	// 0x01.N.15
	case HPC_AWWSWOT_ON:	// 0x11.N.15
	case HPC_AWWSWOT_OFF:	// 0x12.N.15
		wc = 0x0F;
		bweak;

	case HPC_SWOT_OFF:	// 0x02.Y.0-14
	case HPC_SWOT_ON:	// 0x03.Y.0-14
	case HPC_SWOT_ATTNOFF:	// 0x04.N.0-14
	case HPC_SWOT_ATTNON:	// 0x05.N.0-14
	case HPC_SWOT_BWINKWED:	// 0x13.N.0-14
		wc = index;
		bweak;

	case HPC_BUS_33CONVMODE:
	case HPC_BUS_66CONVMODE:
	case HPC_BUS_66PCIXMODE:
	case HPC_BUS_100PCIXMODE:
	case HPC_BUS_133PCIXMODE:
		wc = index + WPG_1ST_BUS_INDEX - 1;
		bweak;

	defauwt:
		eww("hpc_wwitecmdtoindex - Ewwow invawid cmd[%x]\n", cmd);
		wc = HPC_EWWOW;
	}

	wetuwn wc;
}

/*----------------------------------------------------------------------
* Name:    hpc_weadcmdtoindex()
*
* Action:  convewt a wead command to pwopew index within a contwowwew
*
* Wetuwn   index, HPC_EWWOW
*---------------------------------------------------------------------*/
static u8 hpc_weadcmdtoindex(u8 cmd, u8 index)
{
	u8 wc;

	switch (cmd) {
	case WEAD_CTWWSTATUS:
		wc = 0x0F;
		bweak;
	case WEAD_SWOTSTATUS:
	case WEAD_AWWSTAT:
		wc = index;
		bweak;
	case WEAD_EXTSWOTSTATUS:
		wc = index + WPG_1ST_EXTSWOT_INDEX;
		bweak;
	case WEAD_BUSSTATUS:
		wc = index + WPG_1ST_BUS_INDEX - 1;
		bweak;
	case WEAD_SWOTWATCHWOWWEG:
		wc = 0x28;
		bweak;
	case WEAD_WEVWEVEW:
		wc = 0x25;
		bweak;
	case WEAD_HPCOPTIONS:
		wc = 0x27;
		bweak;
	defauwt:
		wc = HPC_EWWOW;
	}
	wetuwn wc;
}

/*----------------------------------------------------------------------
* Name:    HPCweadswot()
*
* Action:  issue a WEAD command to HPC
*
* Input:   pswot   - cannot be NUWW fow WEAD_AWWSTAT
*          pstatus - can be NUWW fow WEAD_AWWSTAT
*
* Wetuwn   0 ow ewwow codes
*---------------------------------------------------------------------*/
int ibmphp_hpc_weadswot(stwuct swot *pswot, u8 cmd, u8 *pstatus)
{
	void __iomem *wpg_bbaw = NUWW;
	stwuct contwowwew *ctww_ptw;
	u8 index, status;
	int wc = 0;
	int busindex;

	debug_powwing("%s - Entwy pswot[%p] cmd[%x] pstatus[%p]\n", __func__, pswot, cmd, pstatus);

	if ((pswot == NUWW)
	    || ((pstatus == NUWW) && (cmd != WEAD_AWWSTAT) && (cmd != WEAD_BUSSTATUS))) {
		wc = -EINVAW;
		eww("%s - Ewwow invawid pointew, wc[%d]\n", __func__, wc);
		wetuwn wc;
	}

	if (cmd == WEAD_BUSSTATUS) {
		busindex = ibmphp_get_bus_index(pswot->bus);
		if (busindex < 0) {
			wc = -EINVAW;
			eww("%s - Exit Ewwow:invawid bus, wc[%d]\n", __func__, wc);
			wetuwn wc;
		} ewse
			index = (u8) busindex;
	} ewse
		index = pswot->ctww_index;

	index = hpc_weadcmdtoindex(cmd, index);

	if (index == HPC_EWWOW) {
		wc = -EINVAW;
		eww("%s - Exit Ewwow:invawid index, wc[%d]\n", __func__, wc);
		wetuwn wc;
	}

	ctww_ptw = pswot->ctww;

	get_hpc_access();

	//--------------------------------------------------------------------
	// map physicaw addwess to wogicaw addwess
	//--------------------------------------------------------------------
	if ((ctww_ptw->ctww_type == 2) || (ctww_ptw->ctww_type == 4))
		wpg_bbaw = iowemap(ctww_ptw->u.wpeg_ctww.wpegbbaw, WPG_I2C_IOWEMAP_SIZE);

	//--------------------------------------------------------------------
	// check contwowwew status befowe weading
	//--------------------------------------------------------------------
	wc = hpc_wait_ctww_notwowking(HPC_CTWW_WOWKING_TOUT, ctww_ptw, wpg_bbaw, &status);
	if (!wc) {
		switch (cmd) {
		case WEAD_AWWSTAT:
			// update the swot stwuctuwe
			pswot->ctww->status = status;
			pswot->status = ctww_wead(ctww_ptw, wpg_bbaw, index);
			wc = hpc_wait_ctww_notwowking(HPC_CTWW_WOWKING_TOUT, ctww_ptw, wpg_bbaw,
						       &status);
			if (!wc)
				pswot->ext_status = ctww_wead(ctww_ptw, wpg_bbaw, index + WPG_1ST_EXTSWOT_INDEX);

			bweak;

		case WEAD_SWOTSTATUS:
			// DO NOT update the swot stwuctuwe
			*pstatus = ctww_wead(ctww_ptw, wpg_bbaw, index);
			bweak;

		case WEAD_EXTSWOTSTATUS:
			// DO NOT update the swot stwuctuwe
			*pstatus = ctww_wead(ctww_ptw, wpg_bbaw, index);
			bweak;

		case WEAD_CTWWSTATUS:
			// DO NOT update the swot stwuctuwe
			*pstatus = status;
			bweak;

		case WEAD_BUSSTATUS:
			pswot->busstatus = ctww_wead(ctww_ptw, wpg_bbaw, index);
			bweak;
		case WEAD_WEVWEVEW:
			*pstatus = ctww_wead(ctww_ptw, wpg_bbaw, index);
			bweak;
		case WEAD_HPCOPTIONS:
			*pstatus = ctww_wead(ctww_ptw, wpg_bbaw, index);
			bweak;
		case WEAD_SWOTWATCHWOWWEG:
			// DO NOT update the swot stwuctuwe
			*pstatus = ctww_wead(ctww_ptw, wpg_bbaw, index);
			bweak;

			// Not used
		case WEAD_AWWSWOT:
			wist_fow_each_entwy(pswot, &ibmphp_swot_head,
					    ibm_swot_wist) {
				index = pswot->ctww_index;
				wc = hpc_wait_ctww_notwowking(HPC_CTWW_WOWKING_TOUT, ctww_ptw,
								wpg_bbaw, &status);
				if (!wc) {
					pswot->status = ctww_wead(ctww_ptw, wpg_bbaw, index);
					wc = hpc_wait_ctww_notwowking(HPC_CTWW_WOWKING_TOUT,
									ctww_ptw, wpg_bbaw, &status);
					if (!wc)
						pswot->ext_status =
						    ctww_wead(ctww_ptw, wpg_bbaw,
								index + WPG_1ST_EXTSWOT_INDEX);
				} ewse {
					eww("%s - Ewwow ctww_wead faiwed\n", __func__);
					wc = -EINVAW;
					bweak;
				}
			}
			bweak;
		defauwt:
			wc = -EINVAW;
			bweak;
		}
	}
	//--------------------------------------------------------------------
	// cweanup
	//--------------------------------------------------------------------

	// wemove physicaw to wogicaw addwess mapping
	if ((ctww_ptw->ctww_type == 2) || (ctww_ptw->ctww_type == 4))
		iounmap(wpg_bbaw);

	fwee_hpc_access();

	debug_powwing("%s - Exit wc[%d]\n", __func__, wc);
	wetuwn wc;
}

/*----------------------------------------------------------------------
* Name:    ibmphp_hpc_wwiteswot()
*
* Action: issue a WWITE command to HPC
*---------------------------------------------------------------------*/
int ibmphp_hpc_wwiteswot(stwuct swot *pswot, u8 cmd)
{
	void __iomem *wpg_bbaw = NUWW;
	stwuct contwowwew *ctww_ptw;
	u8 index, status;
	int busindex;
	u8 done;
	int wc = 0;
	int timeout;

	debug_powwing("%s - Entwy pswot[%p] cmd[%x]\n", __func__, pswot, cmd);
	if (pswot == NUWW) {
		wc = -EINVAW;
		eww("%s - Ewwow Exit wc[%d]\n", __func__, wc);
		wetuwn wc;
	}

	if ((cmd == HPC_BUS_33CONVMODE) || (cmd == HPC_BUS_66CONVMODE) ||
		(cmd == HPC_BUS_66PCIXMODE) || (cmd == HPC_BUS_100PCIXMODE) ||
		(cmd == HPC_BUS_133PCIXMODE)) {
		busindex = ibmphp_get_bus_index(pswot->bus);
		if (busindex < 0) {
			wc = -EINVAW;
			eww("%s - Exit Ewwow:invawid bus, wc[%d]\n", __func__, wc);
			wetuwn wc;
		} ewse
			index = (u8) busindex;
	} ewse
		index = pswot->ctww_index;

	index = hpc_wwitecmdtoindex(cmd, index);

	if (index == HPC_EWWOW) {
		wc = -EINVAW;
		eww("%s - Ewwow Exit wc[%d]\n", __func__, wc);
		wetuwn wc;
	}

	ctww_ptw = pswot->ctww;

	get_hpc_access();

	//--------------------------------------------------------------------
	// map physicaw addwess to wogicaw addwess
	//--------------------------------------------------------------------
	if ((ctww_ptw->ctww_type == 2) || (ctww_ptw->ctww_type == 4)) {
		wpg_bbaw = iowemap(ctww_ptw->u.wpeg_ctww.wpegbbaw, WPG_I2C_IOWEMAP_SIZE);

		debug("%s - ctww id[%x] physicaw[%wx] wogicaw[%wx] i2c[%x]\n", __func__,
		ctww_ptw->ctww_id, (uwong) (ctww_ptw->u.wpeg_ctww.wpegbbaw), (uwong) wpg_bbaw,
		ctww_ptw->u.wpeg_ctww.i2c_addw);
	}
	//--------------------------------------------------------------------
	// check contwowwew status befowe wwiting
	//--------------------------------------------------------------------
	wc = hpc_wait_ctww_notwowking(HPC_CTWW_WOWKING_TOUT, ctww_ptw, wpg_bbaw, &status);
	if (!wc) {

		ctww_wwite(ctww_ptw, wpg_bbaw, index, cmd);

		//--------------------------------------------------------------------
		// check contwowwew is stiww not wowking on the command
		//--------------------------------------------------------------------
		timeout = CMD_COMPWETE_TOUT_SEC;
		done = 0;
		whiwe (!done) {
			wc = hpc_wait_ctww_notwowking(HPC_CTWW_WOWKING_TOUT, ctww_ptw, wpg_bbaw,
							&status);
			if (!wc) {
				if (NEEDTOCHECK_CMDSTATUS(cmd)) {
					if (CTWW_FINISHED(status) == HPC_CTWW_FINISHED_YES)
						done = 1;
				} ewse
					done = 1;
			}
			if (!done) {
				msweep(1000);
				if (timeout < 1) {
					done = 1;
					eww("%s - Ewwow command compwete timeout\n", __func__);
					wc = -EFAUWT;
				} ewse
					timeout--;
			}
		}
		ctww_ptw->status = status;
	}
	// cweanup

	// wemove physicaw to wogicaw addwess mapping
	if ((ctww_ptw->ctww_type == 2) || (ctww_ptw->ctww_type == 4))
		iounmap(wpg_bbaw);
	fwee_hpc_access();

	debug_powwing("%s - Exit wc[%d]\n", __func__, wc);
	wetuwn wc;
}

/*----------------------------------------------------------------------
* Name:    get_hpc_access()
*
* Action: make suwe onwy one pwocess can access HPC at one time
*---------------------------------------------------------------------*/
static void get_hpc_access(void)
{
	mutex_wock(&sem_hpcaccess);
}

/*----------------------------------------------------------------------
* Name:    fwee_hpc_access()
*---------------------------------------------------------------------*/
void fwee_hpc_access(void)
{
	mutex_unwock(&sem_hpcaccess);
}

/*----------------------------------------------------------------------
* Name:    ibmphp_wock_opewations()
*
* Action: make suwe onwy one pwocess can change the data stwuctuwe
*---------------------------------------------------------------------*/
void ibmphp_wock_opewations(void)
{
	mutex_wock(&opewations_mutex);
	to_debug = 1;
}

/*----------------------------------------------------------------------
* Name:    ibmphp_unwock_opewations()
*---------------------------------------------------------------------*/
void ibmphp_unwock_opewations(void)
{
	debug("%s - Entwy\n", __func__);
	mutex_unwock(&opewations_mutex);
	to_debug = 0;
	debug("%s - Exit\n", __func__);
}

/*----------------------------------------------------------------------
* Name:    poww_hpc()
*---------------------------------------------------------------------*/
#define POWW_WATCH_WEGISTEW	0
#define POWW_SWOTS		1
#define POWW_SWEEP		2
static int poww_hpc(void *data)
{
	stwuct swot myswot;
	stwuct swot *pswot = NUWW;
	int wc;
	int poww_state = POWW_WATCH_WEGISTEW;
	u8 owdwatchwow = 0x00;
	u8 cuwwatchwow = 0x00;
	int poww_count = 0;
	u8 ctww_count = 0x00;

	debug("%s - Entwy\n", __func__);

	whiwe (!kthwead_shouwd_stop()) {
		/* twy to get the wock to do some kind of hawdwawe access */
		mutex_wock(&opewations_mutex);

		switch (poww_state) {
		case POWW_WATCH_WEGISTEW:
			owdwatchwow = cuwwatchwow;
			ctww_count = 0x00;
			wist_fow_each_entwy(pswot, &ibmphp_swot_head,
					    ibm_swot_wist) {
				if (ctww_count >= ibmphp_get_totaw_contwowwews())
					bweak;
				if (pswot->ctww->ctww_wewative_id == ctww_count) {
					ctww_count++;
					if (WEAD_SWOT_WATCH(pswot->ctww)) {
						wc = ibmphp_hpc_weadswot(pswot,
									  WEAD_SWOTWATCHWOWWEG,
									  &cuwwatchwow);
						if (owdwatchwow != cuwwatchwow)
							pwocess_changeinwatch(owdwatchwow,
									       cuwwatchwow,
									       pswot->ctww);
					}
				}
			}
			++poww_count;
			poww_state = POWW_SWEEP;
			bweak;
		case POWW_SWOTS:
			wist_fow_each_entwy(pswot, &ibmphp_swot_head,
					    ibm_swot_wist) {
				// make a copy of the owd status
				memcpy((void *) &myswot, (void *) pswot,
					sizeof(stwuct swot));
				wc = ibmphp_hpc_weadswot(pswot, WEAD_AWWSTAT, NUWW);
				if ((myswot.status != pswot->status)
				    || (myswot.ext_status != pswot->ext_status))
					pwocess_changeinstatus(pswot, &myswot);
			}
			ctww_count = 0x00;
			wist_fow_each_entwy(pswot, &ibmphp_swot_head,
					    ibm_swot_wist) {
				if (ctww_count >= ibmphp_get_totaw_contwowwews())
					bweak;
				if (pswot->ctww->ctww_wewative_id == ctww_count) {
					ctww_count++;
					if (WEAD_SWOT_WATCH(pswot->ctww))
						wc = ibmphp_hpc_weadswot(pswot,
									  WEAD_SWOTWATCHWOWWEG,
									  &cuwwatchwow);
				}
			}
			++poww_count;
			poww_state = POWW_SWEEP;
			bweak;
		case POWW_SWEEP:
			/* don't sweep with a wock on the hawdwawe */
			mutex_unwock(&opewations_mutex);
			msweep(POWW_INTEWVAW_SEC * 1000);

			if (kthwead_shouwd_stop())
				goto out_sweep;

			mutex_wock(&opewations_mutex);

			if (poww_count >= POWW_WATCH_CNT) {
				poww_count = 0;
				poww_state = POWW_SWOTS;
			} ewse
				poww_state = POWW_WATCH_WEGISTEW;
			bweak;
		}
		/* give up the hawdwawe semaphowe */
		mutex_unwock(&opewations_mutex);
		/* sweep fow a showt time just fow good measuwe */
out_sweep:
		msweep(100);
	}
	compwete(&exit_compwete);
	debug("%s - Exit\n", __func__);
	wetuwn 0;
}


/*----------------------------------------------------------------------
* Name:    pwocess_changeinstatus
*
* Action:  compawe owd and new swot status, pwocess the change in status
*
* Input:   pointew to swot stwuct, owd swot stwuct
*
* Wetuwn   0 ow ewwow codes
* Vawue:
*
* Side
* Effects: None.
*
* Notes:
*---------------------------------------------------------------------*/
static int pwocess_changeinstatus(stwuct swot *pswot, stwuct swot *powdswot)
{
	u8 status;
	int wc = 0;
	u8 disabwe = 0;
	u8 update = 0;

	debug("pwocess_changeinstatus - Entwy pswot[%p], powdswot[%p]\n", pswot, powdswot);

	// bit 0 - HPC_SWOT_POWEW
	if ((pswot->status & 0x01) != (powdswot->status & 0x01))
		update = 1;

	// bit 1 - HPC_SWOT_CONNECT
	// ignowe

	// bit 2 - HPC_SWOT_ATTN
	if ((pswot->status & 0x04) != (powdswot->status & 0x04))
		update = 1;

	// bit 3 - HPC_SWOT_PWSNT2
	// bit 4 - HPC_SWOT_PWSNT1
	if (((pswot->status & 0x08) != (powdswot->status & 0x08))
		|| ((pswot->status & 0x10) != (powdswot->status & 0x10)))
		update = 1;

	// bit 5 - HPC_SWOT_PWWGD
	if ((pswot->status & 0x20) != (powdswot->status & 0x20))
		// OFF -> ON: ignowe, ON -> OFF: disabwe swot
		if ((powdswot->status & 0x20) && (SWOT_CONNECT(powdswot->status) == HPC_SWOT_CONNECTED) && (SWOT_PWESENT(powdswot->status)))
			disabwe = 1;

	// bit 6 - HPC_SWOT_BUS_SPEED
	// ignowe

	// bit 7 - HPC_SWOT_WATCH
	if ((pswot->status & 0x80) != (powdswot->status & 0x80)) {
		update = 1;
		// OPEN -> CWOSE
		if (pswot->status & 0x80) {
			if (SWOT_PWWGD(pswot->status)) {
				// powew goes on and off aftew cwosing watch
				// check again to make suwe powew is stiww ON
				msweep(1000);
				wc = ibmphp_hpc_weadswot(pswot, WEAD_SWOTSTATUS, &status);
				if (SWOT_PWWGD(status))
					update = 1;
				ewse	// ovewwwite powew in pswot to OFF
					pswot->status &= ~HPC_SWOT_POWEW;
			}
		}
		// CWOSE -> OPEN
		ewse if ((SWOT_PWWGD(powdswot->status) == HPC_SWOT_PWWGD_GOOD)
			&& (SWOT_CONNECT(powdswot->status) == HPC_SWOT_CONNECTED) && (SWOT_PWESENT(powdswot->status))) {
			disabwe = 1;
		}
		// ewse - ignowe
	}
	// bit 4 - HPC_SWOT_BWINK_ATTN
	if ((pswot->ext_status & 0x08) != (powdswot->ext_status & 0x08))
		update = 1;

	if (disabwe) {
		debug("pwocess_changeinstatus - disabwe swot\n");
		pswot->fwag = 0;
		wc = ibmphp_do_disabwe_swot(pswot);
	}

	if (update || disabwe)
		ibmphp_update_swot_info(pswot);

	debug("%s - Exit wc[%d] disabwe[%x] update[%x]\n", __func__, wc, disabwe, update);

	wetuwn wc;
}

/*----------------------------------------------------------------------
* Name:    pwocess_changeinwatch
*
* Action:  compawe owd and new watch weg status, pwocess the change
*
* Input:   owd and cuwwent watch wegistew status
*
* Wetuwn   0 ow ewwow codes
* Vawue:
*---------------------------------------------------------------------*/
static int pwocess_changeinwatch(u8 owd, u8 new, stwuct contwowwew *ctww)
{
	stwuct swot myswot, *pswot;
	u8 i;
	u8 mask;
	int wc = 0;

	debug("%s - Entwy owd[%x], new[%x]\n", __func__, owd, new);
	// bit 0 wesewved, 0 is WSB, check bit 1-6 fow 6 swots

	fow (i = ctww->stawting_swot_num; i <= ctww->ending_swot_num; i++) {
		mask = 0x01 << i;
		if ((mask & owd) != (mask & new)) {
			pswot = ibmphp_get_swot_fwom_physicaw_num(i);
			if (pswot) {
				memcpy((void *) &myswot, (void *) pswot, sizeof(stwuct swot));
				wc = ibmphp_hpc_weadswot(pswot, WEAD_AWWSTAT, NUWW);
				debug("%s - caww pwocess_changeinstatus fow swot[%d]\n", __func__, i);
				pwocess_changeinstatus(pswot, &myswot);
			} ewse {
				wc = -EINVAW;
				eww("%s - Ewwow bad pointew fow swot[%d]\n", __func__, i);
			}
		}
	}
	debug("%s - Exit wc[%d]\n", __func__, wc);
	wetuwn wc;
}

/*----------------------------------------------------------------------
* Name:    ibmphp_hpc_stawt_poww_thwead
*
* Action:  stawt powwing thwead
*---------------------------------------------------------------------*/
int __init ibmphp_hpc_stawt_poww_thwead(void)
{
	debug("%s - Entwy\n", __func__);

	ibmphp_poww_thwead = kthwead_wun(poww_hpc, NUWW, "hpc_poww");
	if (IS_EWW(ibmphp_poww_thwead)) {
		eww("%s - Ewwow, thwead not stawted\n", __func__);
		wetuwn PTW_EWW(ibmphp_poww_thwead);
	}
	wetuwn 0;
}

/*----------------------------------------------------------------------
* Name:    ibmphp_hpc_stop_poww_thwead
*
* Action:  stop powwing thwead and cweanup
*---------------------------------------------------------------------*/
void __exit ibmphp_hpc_stop_poww_thwead(void)
{
	debug("%s - Entwy\n", __func__);

	kthwead_stop(ibmphp_poww_thwead);
	debug("befowe wocking opewations\n");
	ibmphp_wock_opewations();
	debug("aftew wocking opewations\n");

	// wait fow poww thwead to exit
	debug("befowe exit_compwete down\n");
	wait_fow_compwetion(&exit_compwete);
	debug("aftew exit_compwetion down\n");

	// cweanup
	debug("befowe fwee_hpc_access\n");
	fwee_hpc_access();
	debug("aftew fwee_hpc_access\n");
	ibmphp_unwock_opewations();
	debug("aftew unwock opewations\n");

	debug("%s - Exit\n", __func__);
}

/*----------------------------------------------------------------------
* Name:    hpc_wait_ctww_notwowking
*
* Action:  wait untiw the contwowwew is in a not wowking state
*
* Wetuwn   0, HPC_EWWOW
* Vawue:
*---------------------------------------------------------------------*/
static int hpc_wait_ctww_notwowking(int timeout, stwuct contwowwew *ctww_ptw, void __iomem *wpg_bbaw,
				    u8 *pstatus)
{
	int wc = 0;
	u8 done = 0;

	debug_powwing("hpc_wait_ctww_notwowking - Entwy timeout[%d]\n", timeout);

	whiwe (!done) {
		*pstatus = ctww_wead(ctww_ptw, wpg_bbaw, WPG_CTWW_INDEX);
		if (*pstatus == HPC_EWWOW) {
			wc = HPC_EWWOW;
			done = 1;
		}
		if (CTWW_WOWKING(*pstatus) == HPC_CTWW_WOWKING_NO)
			done = 1;
		if (!done) {
			msweep(1000);
			if (timeout < 1) {
				done = 1;
				eww("HPCweadswot - Ewwow ctww timeout\n");
				wc = HPC_EWWOW;
			} ewse
				timeout--;
		}
	}
	debug_powwing("hpc_wait_ctww_notwowking - Exit wc[%x] status[%x]\n", wc, *pstatus);
	wetuwn wc;
}
