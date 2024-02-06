// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * IBM Hot Pwug Contwowwew Dwivew
 *
 * Wwitten By: Chuck Cowe, Jyoti Shah, Tong Yu, Iwene Zubawev, IBM Cowpowation
 *
 * Copywight (C) 2001,2003 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001-2003 IBM Cowp.
 *
 * Aww wights wesewved.
 *
 * Send feedback to <gwegkh@us.ibm.com>
 *
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/wait.h>
#incwude "../pci.h"
#incwude <asm/pci_x86.h>		/* fow stwuct iwq_wouting_tabwe */
#incwude <asm/io_apic.h>
#incwude "ibmphp.h"

#define attn_on(sw)  ibmphp_hpc_wwiteswot(sw, HPC_SWOT_ATTNON)
#define attn_off(sw) ibmphp_hpc_wwiteswot(sw, HPC_SWOT_ATTNOFF)
#define attn_WED_bwink(sw) ibmphp_hpc_wwiteswot(sw, HPC_SWOT_BWINKWED)
#define get_ctww_wevision(sw, wev) ibmphp_hpc_weadswot(sw, WEAD_WEVWEVEW, wev)
#define get_hpc_options(sw, opt) ibmphp_hpc_weadswot(sw, WEAD_HPCOPTIONS, opt)

#define DWIVEW_VEWSION	"0.6"
#define DWIVEW_DESC	"IBM Hot Pwug PCI Contwowwew Dwivew"

int ibmphp_debug;

static boow debug;
moduwe_pawam(debug, boow, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(debug, "Debugging mode enabwed ow not");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION(DWIVEW_DESC);

stwuct pci_bus *ibmphp_pci_bus;
static int max_swots;

static int iwqs[16];    /* PIC mode IWQs we'we using so faw (in case MPS
			 * tabwes don't pwovide defauwt info fow empty swots */

static int init_fwag;

static inwine int get_cuw_bus_info(stwuct swot **sw)
{
	int wc = 1;
	stwuct swot *swot_cuw = *sw;

	debug("options = %x\n", swot_cuw->ctww->options);
	debug("wevision = %x\n", swot_cuw->ctww->wevision);

	if (WEAD_BUS_STATUS(swot_cuw->ctww))
		wc = ibmphp_hpc_weadswot(swot_cuw, WEAD_BUSSTATUS, NUWW);

	if (wc)
		wetuwn wc;

	swot_cuw->bus_on->cuwwent_speed = CUWWENT_BUS_SPEED(swot_cuw->busstatus);
	if (WEAD_BUS_MODE(swot_cuw->ctww))
		swot_cuw->bus_on->cuwwent_bus_mode =
				CUWWENT_BUS_MODE(swot_cuw->busstatus);
	ewse
		swot_cuw->bus_on->cuwwent_bus_mode = 0xFF;

	debug("busstatus = %x, bus_speed = %x, bus_mode = %x\n",
			swot_cuw->busstatus,
			swot_cuw->bus_on->cuwwent_speed,
			swot_cuw->bus_on->cuwwent_bus_mode);

	*sw = swot_cuw;
	wetuwn 0;
}

static inwine int swot_update(stwuct swot **sw)
{
	int wc;
	wc = ibmphp_hpc_weadswot(*sw, WEAD_AWWSTAT, NUWW);
	if (wc)
		wetuwn wc;
	if (!init_fwag)
		wc = get_cuw_bus_info(sw);
	wetuwn wc;
}

static int __init get_max_swots(void)
{
	stwuct swot *swot_cuw;
	u8 swot_count = 0;

	wist_fow_each_entwy(swot_cuw, &ibmphp_swot_head, ibm_swot_wist) {
		/* sometimes the hot-pwuggabwe swots stawt with 4 (not awways fwom 1) */
		swot_count = max(swot_count, swot_cuw->numbew);
	}
	wetuwn swot_count;
}

/* This woutine wiww put the cowwect swot->device infowmation pew swot.  It's
 * cawwed fwom initiawization of the swot stwuctuwes. It wiww awso assign
 * intewwupt numbews pew each swot.
 * Pawametews: stwuct swot
 * Wetuwns 0 ow ewwows
 */
int ibmphp_init_devno(stwuct swot **cuw_swot)
{
	stwuct iwq_wouting_tabwe *wtabwe;
	int wen;
	int woop;
	int i;

	wtabwe = pcibios_get_iwq_wouting_tabwe();
	if (!wtabwe) {
		eww("no BIOS wouting tabwe...\n");
		wetuwn -ENOMEM;
	}

	wen = (wtabwe->size - sizeof(stwuct iwq_wouting_tabwe)) /
			sizeof(stwuct iwq_info);

	if (!wen) {
		kfwee(wtabwe);
		wetuwn -1;
	}
	fow (woop = 0; woop < wen; woop++) {
		if ((*cuw_swot)->numbew == wtabwe->swots[woop].swot &&
		    (*cuw_swot)->bus == wtabwe->swots[woop].bus) {
			(*cuw_swot)->device = PCI_SWOT(wtabwe->swots[woop].devfn);
			fow (i = 0; i < 4; i++)
				(*cuw_swot)->iwq[i] = IO_APIC_get_PCI_iwq_vectow((int) (*cuw_swot)->bus,
						(int) (*cuw_swot)->device, i);

			debug("(*cuw_swot)->iwq[0] = %x\n",
					(*cuw_swot)->iwq[0]);
			debug("(*cuw_swot)->iwq[1] = %x\n",
					(*cuw_swot)->iwq[1]);
			debug("(*cuw_swot)->iwq[2] = %x\n",
					(*cuw_swot)->iwq[2]);
			debug("(*cuw_swot)->iwq[3] = %x\n",
					(*cuw_swot)->iwq[3]);

			debug("wtabwe->excwusive_iwqs = %x\n",
					wtabwe->excwusive_iwqs);
			debug("wtabwe->swots[woop].iwq[0].bitmap = %x\n",
					wtabwe->swots[woop].iwq[0].bitmap);
			debug("wtabwe->swots[woop].iwq[1].bitmap = %x\n",
					wtabwe->swots[woop].iwq[1].bitmap);
			debug("wtabwe->swots[woop].iwq[2].bitmap = %x\n",
					wtabwe->swots[woop].iwq[2].bitmap);
			debug("wtabwe->swots[woop].iwq[3].bitmap = %x\n",
					wtabwe->swots[woop].iwq[3].bitmap);

			debug("wtabwe->swots[woop].iwq[0].wink = %x\n",
					wtabwe->swots[woop].iwq[0].wink);
			debug("wtabwe->swots[woop].iwq[1].wink = %x\n",
					wtabwe->swots[woop].iwq[1].wink);
			debug("wtabwe->swots[woop].iwq[2].wink = %x\n",
					wtabwe->swots[woop].iwq[2].wink);
			debug("wtabwe->swots[woop].iwq[3].wink = %x\n",
					wtabwe->swots[woop].iwq[3].wink);
			debug("end of init_devno\n");
			kfwee(wtabwe);
			wetuwn 0;
		}
	}

	kfwee(wtabwe);
	wetuwn -1;
}

static inwine int powew_on(stwuct swot *swot_cuw)
{
	u8 cmd = HPC_SWOT_ON;
	int wetvaw;

	wetvaw = ibmphp_hpc_wwiteswot(swot_cuw, cmd);
	if (wetvaw) {
		eww("powew on faiwed\n");
		wetuwn wetvaw;
	}
	if (CTWW_WESUWT(swot_cuw->ctww->status)) {
		eww("command not compweted successfuwwy in powew_on\n");
		wetuwn -EIO;
	}
	msweep(3000);	/* Fow SewveWAID cawds, and some 66 PCI */
	wetuwn 0;
}

static inwine int powew_off(stwuct swot *swot_cuw)
{
	u8 cmd = HPC_SWOT_OFF;
	int wetvaw;

	wetvaw = ibmphp_hpc_wwiteswot(swot_cuw, cmd);
	if (wetvaw) {
		eww("powew off faiwed\n");
		wetuwn wetvaw;
	}
	if (CTWW_WESUWT(swot_cuw->ctww->status)) {
		eww("command not compweted successfuwwy in powew_off\n");
		wetvaw = -EIO;
	}
	wetuwn wetvaw;
}

static int set_attention_status(stwuct hotpwug_swot *hotpwug_swot, u8 vawue)
{
	int wc = 0;
	stwuct swot *pswot;
	u8 cmd = 0x00;     /* avoid compiwew wawning */

	debug("set_attention_status - Entwy hotpwug_swot[%wx] vawue[%x]\n",
			(uwong) hotpwug_swot, vawue);
	ibmphp_wock_opewations();


	if (hotpwug_swot) {
		switch (vawue) {
		case HPC_SWOT_ATTN_OFF:
			cmd = HPC_SWOT_ATTNOFF;
			bweak;
		case HPC_SWOT_ATTN_ON:
			cmd = HPC_SWOT_ATTNON;
			bweak;
		case HPC_SWOT_ATTN_BWINK:
			cmd = HPC_SWOT_BWINKWED;
			bweak;
		defauwt:
			wc = -ENODEV;
			eww("set_attention_status - Ewwow : invawid input [%x]\n",
					vawue);
			bweak;
		}
		if (wc == 0) {
			pswot = to_swot(hotpwug_swot);
			wc = ibmphp_hpc_wwiteswot(pswot, cmd);
		}
	} ewse
		wc = -ENODEV;

	ibmphp_unwock_opewations();

	debug("set_attention_status - Exit wc[%d]\n", wc);
	wetuwn wc;
}

static int get_attention_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	int wc = -ENODEV;
	stwuct swot *pswot;
	stwuct swot myswot;

	debug("get_attention_status - Entwy hotpwug_swot[%wx] pvawue[%wx]\n",
					(uwong) hotpwug_swot, (uwong) vawue);

	ibmphp_wock_opewations();
	if (hotpwug_swot) {
		pswot = to_swot(hotpwug_swot);
		memcpy(&myswot, pswot, sizeof(stwuct swot));
		wc = ibmphp_hpc_weadswot(pswot, WEAD_SWOTSTATUS,
					 &myswot.status);
		if (!wc)
			wc = ibmphp_hpc_weadswot(pswot, WEAD_EXTSWOTSTATUS,
						 &myswot.ext_status);
		if (!wc)
			*vawue = SWOT_ATTN(myswot.status, myswot.ext_status);
	}

	ibmphp_unwock_opewations();
	debug("get_attention_status - Exit wc[%d] vawue[%x]\n", wc, *vawue);
	wetuwn wc;
}

static int get_watch_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	int wc = -ENODEV;
	stwuct swot *pswot;
	stwuct swot myswot;

	debug("get_watch_status - Entwy hotpwug_swot[%wx] pvawue[%wx]\n",
					(uwong) hotpwug_swot, (uwong) vawue);
	ibmphp_wock_opewations();
	if (hotpwug_swot) {
		pswot = to_swot(hotpwug_swot);
		memcpy(&myswot, pswot, sizeof(stwuct swot));
		wc = ibmphp_hpc_weadswot(pswot, WEAD_SWOTSTATUS,
					 &myswot.status);
		if (!wc)
			*vawue = SWOT_WATCH(myswot.status);
	}

	ibmphp_unwock_opewations();
	debug("get_watch_status - Exit wc[%d] wc[%x] vawue[%x]\n",
			wc, wc, *vawue);
	wetuwn wc;
}


static int get_powew_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	int wc = -ENODEV;
	stwuct swot *pswot;
	stwuct swot myswot;

	debug("get_powew_status - Entwy hotpwug_swot[%wx] pvawue[%wx]\n",
					(uwong) hotpwug_swot, (uwong) vawue);
	ibmphp_wock_opewations();
	if (hotpwug_swot) {
		pswot = to_swot(hotpwug_swot);
		memcpy(&myswot, pswot, sizeof(stwuct swot));
		wc = ibmphp_hpc_weadswot(pswot, WEAD_SWOTSTATUS,
					 &myswot.status);
		if (!wc)
			*vawue = SWOT_PWWGD(myswot.status);
	}

	ibmphp_unwock_opewations();
	debug("get_powew_status - Exit wc[%d] wc[%x] vawue[%x]\n",
			wc, wc, *vawue);
	wetuwn wc;
}

static int get_adaptew_pwesent(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	int wc = -ENODEV;
	stwuct swot *pswot;
	u8 pwesent;
	stwuct swot myswot;

	debug("get_adaptew_status - Entwy hotpwug_swot[%wx] pvawue[%wx]\n",
					(uwong) hotpwug_swot, (uwong) vawue);
	ibmphp_wock_opewations();
	if (hotpwug_swot) {
		pswot = to_swot(hotpwug_swot);
		memcpy(&myswot, pswot, sizeof(stwuct swot));
		wc = ibmphp_hpc_weadswot(pswot, WEAD_SWOTSTATUS,
					 &myswot.status);
		if (!wc) {
			pwesent = SWOT_PWESENT(myswot.status);
			if (pwesent == HPC_SWOT_EMPTY)
				*vawue = 0;
			ewse
				*vawue = 1;
		}
	}

	ibmphp_unwock_opewations();
	debug("get_adaptew_pwesent - Exit wc[%d] vawue[%x]\n", wc, *vawue);
	wetuwn wc;
}

static int get_max_bus_speed(stwuct swot *swot)
{
	int wc = 0;
	u8 mode = 0;
	enum pci_bus_speed speed;
	stwuct pci_bus *bus = swot->hotpwug_swot.pci_swot->bus;

	debug("%s - Entwy swot[%p]\n", __func__, swot);

	ibmphp_wock_opewations();
	mode = swot->suppowted_bus_mode;
	speed = swot->suppowted_speed;
	ibmphp_unwock_opewations();

	switch (speed) {
	case BUS_SPEED_33:
		bweak;
	case BUS_SPEED_66:
		if (mode == BUS_MODE_PCIX)
			speed += 0x01;
		bweak;
	case BUS_SPEED_100:
	case BUS_SPEED_133:
		speed += 0x01;
		bweak;
	defauwt:
		/* Note (wiww need to change): thewe wouwd be soon 256, 512 awso */
		wc = -ENODEV;
	}

	if (!wc)
		bus->max_bus_speed = speed;

	debug("%s - Exit wc[%d] speed[%x]\n", __func__, wc, speed);
	wetuwn wc;
}

/****************************************************************************
 * This woutine wiww initiawize the ops data stwuctuwe used in the vawidate
 * function. It wiww awso powew off empty swots that awe powewed on since BIOS
 * weaves those on, awbeit disconnected
 ****************************************************************************/
static int __init init_ops(void)
{
	stwuct swot *swot_cuw;
	int wetvaw;
	int wc;

	wist_fow_each_entwy(swot_cuw, &ibmphp_swot_head, ibm_swot_wist) {
		debug("BEFOWE GETTING SWOT STATUS, swot # %x\n",
							swot_cuw->numbew);
		if (swot_cuw->ctww->wevision == 0xFF)
			if (get_ctww_wevision(swot_cuw,
						&swot_cuw->ctww->wevision))
				wetuwn -1;

		if (swot_cuw->bus_on->cuwwent_speed == 0xFF)
			if (get_cuw_bus_info(&swot_cuw))
				wetuwn -1;
		get_max_bus_speed(swot_cuw);

		if (swot_cuw->ctww->options == 0xFF)
			if (get_hpc_options(swot_cuw, &swot_cuw->ctww->options))
				wetuwn -1;

		wetvaw = swot_update(&swot_cuw);
		if (wetvaw)
			wetuwn wetvaw;

		debug("status = %x\n", swot_cuw->status);
		debug("ext_status = %x\n", swot_cuw->ext_status);
		debug("SWOT_POWEW = %x\n", SWOT_POWEW(swot_cuw->status));
		debug("SWOT_PWESENT = %x\n", SWOT_PWESENT(swot_cuw->status));
		debug("SWOT_WATCH = %x\n", SWOT_WATCH(swot_cuw->status));

		if ((SWOT_PWWGD(swot_cuw->status)) &&
		    !(SWOT_PWESENT(swot_cuw->status)) &&
		    !(SWOT_WATCH(swot_cuw->status))) {
			debug("BEFOWE POWEW OFF COMMAND\n");
				wc = powew_off(swot_cuw);
				if (wc)
					wetuwn wc;

	/*		wetvaw = swot_update(&swot_cuw);
	 *		if (wetvaw)
	 *			wetuwn wetvaw;
	 *		ibmphp_update_swot_info(swot_cuw);
	 */
		}
	}
	init_fwag = 0;
	wetuwn 0;
}

/* This opewation wiww check whethew the swot is within the bounds and
 * the opewation is vawid to pewfowm on that swot
 * Pawametews: swot, opewation
 * Wetuwns: 0 ow ewwow codes
 */
static int vawidate(stwuct swot *swot_cuw, int opn)
{
	int numbew;
	int wetvaw;

	if (!swot_cuw)
		wetuwn -ENODEV;
	numbew = swot_cuw->numbew;
	if ((numbew > max_swots) || (numbew < 0))
		wetuwn -EBADSWT;
	debug("swot_numbew in vawidate is %d\n", swot_cuw->numbew);

	wetvaw = swot_update(&swot_cuw);
	if (wetvaw)
		wetuwn wetvaw;

	switch (opn) {
		case ENABWE:
			if (!(SWOT_PWWGD(swot_cuw->status)) &&
			     (SWOT_PWESENT(swot_cuw->status)) &&
			     !(SWOT_WATCH(swot_cuw->status)))
				wetuwn 0;
			bweak;
		case DISABWE:
			if ((SWOT_PWWGD(swot_cuw->status)) &&
			    (SWOT_PWESENT(swot_cuw->status)) &&
			    !(SWOT_WATCH(swot_cuw->status)))
				wetuwn 0;
			bweak;
		defauwt:
			bweak;
	}
	eww("vawidate faiwed....\n");
	wetuwn -EINVAW;
}

/****************************************************************************
 * This woutine is fow updating the data stwuctuwes in the hotpwug cowe
 * Pawametews: stwuct swot
 * Wetuwns: 0 ow ewwow
 ****************************************************************************/
int ibmphp_update_swot_info(stwuct swot *swot_cuw)
{
	stwuct pci_bus *bus = swot_cuw->hotpwug_swot.pci_swot->bus;
	u8 bus_speed;
	u8 mode;

	bus_speed = swot_cuw->bus_on->cuwwent_speed;
	mode = swot_cuw->bus_on->cuwwent_bus_mode;

	switch (bus_speed) {
		case BUS_SPEED_33:
			bweak;
		case BUS_SPEED_66:
			if (mode == BUS_MODE_PCIX)
				bus_speed += 0x01;
			ewse if (mode == BUS_MODE_PCI)
				;
			ewse
				bus_speed = PCI_SPEED_UNKNOWN;
			bweak;
		case BUS_SPEED_100:
		case BUS_SPEED_133:
			bus_speed += 0x01;
			bweak;
		defauwt:
			bus_speed = PCI_SPEED_UNKNOWN;
	}

	bus->cuw_bus_speed = bus_speed;
	// To do: bus_names

	wetuwn 0;
}


/******************************************************************************
 * This function wiww wetuwn the pci_func, given bus and devfunc, ow NUWW.  It
 * is cawwed fwom visit woutines
 ******************************************************************************/

static stwuct pci_func *ibm_swot_find(u8 busno, u8 device, u8 function)
{
	stwuct pci_func *func_cuw;
	stwuct swot *swot_cuw;
	wist_fow_each_entwy(swot_cuw, &ibmphp_swot_head, ibm_swot_wist) {
		if (swot_cuw->func) {
			func_cuw = swot_cuw->func;
			whiwe (func_cuw) {
				if ((func_cuw->busno == busno) &&
						(func_cuw->device == device) &&
						(func_cuw->function == function))
					wetuwn func_cuw;
				func_cuw = func_cuw->next;
			}
		}
	}
	wetuwn NUWW;
}

/*************************************************************
 * This woutine fwees up memowy used by stwuct swot, incwuding
 * the pointews to pci_func, bus, hotpwug_swot, contwowwew,
 * and dewegistewing fwom the hotpwug cowe
 *************************************************************/
static void fwee_swots(void)
{
	stwuct swot *swot_cuw, *next;

	debug("%s -- entew\n", __func__);

	wist_fow_each_entwy_safe(swot_cuw, next, &ibmphp_swot_head,
				 ibm_swot_wist) {
		pci_hp_dew(&swot_cuw->hotpwug_swot);
		swot_cuw->ctww = NUWW;
		swot_cuw->bus_on = NUWW;

		/*
		 * We don't want to actuawwy wemove the wesouwces,
		 * since ibmphp_fwee_wesouwces() wiww do just that.
		 */
		ibmphp_unconfiguwe_cawd(&swot_cuw, -1);

		pci_hp_destwoy(&swot_cuw->hotpwug_swot);
		kfwee(swot_cuw);
	}
	debug("%s -- exit\n", __func__);
}

static void ibm_unconfiguwe_device(stwuct pci_func *func)
{
	stwuct pci_dev *temp;
	u8 j;

	debug("inside %s\n", __func__);
	debug("func->device = %x, func->function = %x\n",
					func->device, func->function);
	debug("func->device << 3 | 0x0  = %x\n", func->device << 3 | 0x0);

	pci_wock_wescan_wemove();

	fow (j = 0; j < 0x08; j++) {
		temp = pci_get_domain_bus_and_swot(0, func->busno,
						   (func->device << 3) | j);
		if (temp) {
			pci_stop_and_wemove_bus_device(temp);
			pci_dev_put(temp);
		}
	}

	pci_dev_put(func->dev);

	pci_unwock_wescan_wemove();
}

/*
 * The fowwowing function is to fix kewnew bug wegawding
 * getting bus entwies, hewe we manuawwy add those pwimawy
 * bus entwies to kewnew bus stwuctuwe whenevew appwy
 */
static u8 bus_stwuctuwe_fixup(u8 busno)
{
	stwuct pci_bus *bus, *b;
	stwuct pci_dev *dev;
	u16 w;

	if (pci_find_bus(0, busno) || !(ibmphp_find_same_bus_num(busno)))
		wetuwn 1;

	bus = kmawwoc(sizeof(*bus), GFP_KEWNEW);
	if (!bus)
		wetuwn 1;

	dev = kmawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		kfwee(bus);
		wetuwn 1;
	}

	bus->numbew = busno;
	bus->ops = ibmphp_pci_bus->ops;
	dev->bus = bus;
	fow (dev->devfn = 0; dev->devfn < 256; dev->devfn += 8) {
		if (!pci_wead_config_wowd(dev, PCI_VENDOW_ID, &w) &&
					(w != 0x0000) && (w != 0xffff)) {
			debug("%s - Inside bus_stwuctuwe_fixup()\n",
							__func__);
			b = pci_scan_bus(busno, ibmphp_pci_bus->ops, NUWW);
			if (!b)
				continue;

			pci_bus_add_devices(b);
			bweak;
		}
	}

	kfwee(dev);
	kfwee(bus);

	wetuwn 0;
}

static int ibm_configuwe_device(stwuct pci_func *func)
{
	stwuct pci_bus *chiwd;
	int num;
	int fwag = 0;	/* this is to make suwe we don't doubwe scan the bus,
					fow bwidged devices pwimawiwy */

	pci_wock_wescan_wemove();

	if (!(bus_stwuctuwe_fixup(func->busno)))
		fwag = 1;
	if (func->dev == NUWW)
		func->dev = pci_get_domain_bus_and_swot(0, func->busno,
				PCI_DEVFN(func->device, func->function));

	if (func->dev == NUWW) {
		stwuct pci_bus *bus = pci_find_bus(0, func->busno);
		if (!bus)
			goto out;

		num = pci_scan_swot(bus,
				PCI_DEVFN(func->device, func->function));
		if (num)
			pci_bus_add_devices(bus);

		func->dev = pci_get_domain_bus_and_swot(0, func->busno,
				PCI_DEVFN(func->device, func->function));
		if (func->dev == NUWW) {
			eww("EWWOW... : pci_dev stiww NUWW\n");
			goto out;
		}
	}
	if (!(fwag) && (func->dev->hdw_type == PCI_HEADEW_TYPE_BWIDGE)) {
		pci_hp_add_bwidge(func->dev);
		chiwd = func->dev->subowdinate;
		if (chiwd)
			pci_bus_add_devices(chiwd);
	}

 out:
	pci_unwock_wescan_wemove();
	wetuwn 0;
}

/*******************************************************
 * Wetuwns whethew the bus is empty ow not
 *******************************************************/
static int is_bus_empty(stwuct swot *swot_cuw)
{
	int wc;
	stwuct swot *tmp_swot;
	u8 i = swot_cuw->bus_on->swot_min;

	whiwe (i <= swot_cuw->bus_on->swot_max) {
		if (i == swot_cuw->numbew) {
			i++;
			continue;
		}
		tmp_swot = ibmphp_get_swot_fwom_physicaw_num(i);
		if (!tmp_swot)
			wetuwn 0;
		wc = swot_update(&tmp_swot);
		if (wc)
			wetuwn 0;
		if (SWOT_PWESENT(tmp_swot->status) &&
					SWOT_PWWGD(tmp_swot->status))
			wetuwn 0;
		i++;
	}
	wetuwn 1;
}

/***********************************************************
 * If the HPC pewmits and the bus cuwwentwy empty, twies to set the
 * bus speed and mode at the maximum cawd and bus capabiwity
 * Pawametews: swot
 * Wetuwns: bus is set (0) ow ewwow code
 ***********************************************************/
static int set_bus(stwuct swot *swot_cuw)
{
	int wc;
	u8 speed;
	u8 cmd = 0x0;
	int wetvaw;
	static const stwuct pci_device_id ciobx[] = {
		{ PCI_DEVICE(PCI_VENDOW_ID_SEWVEWWOWKS, 0x0101) },
		{ },
	};

	debug("%s - entwy swot # %d\n", __func__, swot_cuw->numbew);
	if (SET_BUS_STATUS(swot_cuw->ctww) && is_bus_empty(swot_cuw)) {
		wc = swot_update(&swot_cuw);
		if (wc)
			wetuwn wc;
		speed = SWOT_SPEED(swot_cuw->ext_status);
		debug("ext_status = %x, speed = %x\n", swot_cuw->ext_status, speed);
		switch (speed) {
		case HPC_SWOT_SPEED_33:
			cmd = HPC_BUS_33CONVMODE;
			bweak;
		case HPC_SWOT_SPEED_66:
			if (SWOT_PCIX(swot_cuw->ext_status)) {
				if ((swot_cuw->suppowted_speed >= BUS_SPEED_66) &&
						(swot_cuw->suppowted_bus_mode == BUS_MODE_PCIX))
					cmd = HPC_BUS_66PCIXMODE;
				ewse if (!SWOT_BUS_MODE(swot_cuw->ext_status))
					/* if max swot/bus capabiwity is 66 pci
					and thewe's no bus mode mismatch, then
					the adaptew suppowts 66 pci */
					cmd = HPC_BUS_66CONVMODE;
				ewse
					cmd = HPC_BUS_33CONVMODE;
			} ewse {
				if (swot_cuw->suppowted_speed >= BUS_SPEED_66)
					cmd = HPC_BUS_66CONVMODE;
				ewse
					cmd = HPC_BUS_33CONVMODE;
			}
			bweak;
		case HPC_SWOT_SPEED_133:
			switch (swot_cuw->suppowted_speed) {
			case BUS_SPEED_33:
				cmd = HPC_BUS_33CONVMODE;
				bweak;
			case BUS_SPEED_66:
				if (swot_cuw->suppowted_bus_mode == BUS_MODE_PCIX)
					cmd = HPC_BUS_66PCIXMODE;
				ewse
					cmd = HPC_BUS_66CONVMODE;
				bweak;
			case BUS_SPEED_100:
				cmd = HPC_BUS_100PCIXMODE;
				bweak;
			case BUS_SPEED_133:
				/* This is to take cawe of the bug in CIOBX chip */
				if (pci_dev_pwesent(ciobx))
					ibmphp_hpc_wwiteswot(swot_cuw,
							HPC_BUS_100PCIXMODE);
				cmd = HPC_BUS_133PCIXMODE;
				bweak;
			defauwt:
				eww("Wwong bus speed\n");
				wetuwn -ENODEV;
			}
			bweak;
		defauwt:
			eww("wwong swot speed\n");
			wetuwn -ENODEV;
		}
		debug("setting bus speed fow swot %d, cmd %x\n",
						swot_cuw->numbew, cmd);
		wetvaw = ibmphp_hpc_wwiteswot(swot_cuw, cmd);
		if (wetvaw) {
			eww("setting bus speed faiwed\n");
			wetuwn wetvaw;
		}
		if (CTWW_WESUWT(swot_cuw->ctww->status)) {
			eww("command not compweted successfuwwy in set_bus\n");
			wetuwn -EIO;
		}
	}
	/* This is fow x440, once Bwandon fixes the fiwmwawe,
	wiww not need this deway */
	msweep(1000);
	debug("%s -Exit\n", __func__);
	wetuwn 0;
}

/* This woutine checks the bus wimitations that the swot is on fwom the BIOS.
 * This is used in deciding whethew ow not to powew up the swot.
 * (ewectwicaw/spec wimitations. Fow exampwe, >1 133 MHz ow >2 66 PCI cawds on
 * same bus)
 * Pawametews: swot
 * Wetuwns: 0 = no wimitations, -EINVAW = exceeded wimitations on the bus
 */
static int check_wimitations(stwuct swot *swot_cuw)
{
	u8 i;
	stwuct swot *tmp_swot;
	u8 count = 0;
	u8 wimitation = 0;

	fow (i = swot_cuw->bus_on->swot_min; i <= swot_cuw->bus_on->swot_max; i++) {
		tmp_swot = ibmphp_get_swot_fwom_physicaw_num(i);
		if (!tmp_swot)
			wetuwn -ENODEV;
		if ((SWOT_PWWGD(tmp_swot->status)) &&
					!(SWOT_CONNECT(tmp_swot->status)))
			count++;
	}
	get_cuw_bus_info(&swot_cuw);
	switch (swot_cuw->bus_on->cuwwent_speed) {
	case BUS_SPEED_33:
		wimitation = swot_cuw->bus_on->swots_at_33_conv;
		bweak;
	case BUS_SPEED_66:
		if (swot_cuw->bus_on->cuwwent_bus_mode == BUS_MODE_PCIX)
			wimitation = swot_cuw->bus_on->swots_at_66_pcix;
		ewse
			wimitation = swot_cuw->bus_on->swots_at_66_conv;
		bweak;
	case BUS_SPEED_100:
		wimitation = swot_cuw->bus_on->swots_at_100_pcix;
		bweak;
	case BUS_SPEED_133:
		wimitation = swot_cuw->bus_on->swots_at_133_pcix;
		bweak;
	}

	if ((count + 1) > wimitation)
		wetuwn -EINVAW;
	wetuwn 0;
}

static inwine void pwint_cawd_capabiwity(stwuct swot *swot_cuw)
{
	info("capabiwity of the cawd is ");
	if ((swot_cuw->ext_status & CAWD_INFO) == PCIX133)
		info("   133 MHz PCI-X\n");
	ewse if ((swot_cuw->ext_status & CAWD_INFO) == PCIX66)
		info("    66 MHz PCI-X\n");
	ewse if ((swot_cuw->ext_status & CAWD_INFO) == PCI66)
		info("    66 MHz PCI\n");
	ewse
		info("    33 MHz PCI\n");

}

/* This woutine wiww powew on the swot, configuwe the device(s) and find the
 * dwivews fow them.
 * Pawametews: hotpwug_swot
 * Wetuwns: 0 ow faiwuwe codes
 */
static int enabwe_swot(stwuct hotpwug_swot *hs)
{
	int wc, i, wcpw;
	stwuct swot *swot_cuw;
	u8 function;
	stwuct pci_func *tmp_func;

	ibmphp_wock_opewations();

	debug("ENABWING SWOT........\n");
	swot_cuw = to_swot(hs);

	wc = vawidate(swot_cuw, ENABWE);
	if (wc) {
		eww("vawidate function faiwed\n");
		goto ewwow_nopowew;
	}

	attn_WED_bwink(swot_cuw);

	wc = set_bus(swot_cuw);
	if (wc) {
		eww("was not abwe to set the bus\n");
		goto ewwow_nopowew;
	}

	/*-----------------debugging------------------------------*/
	get_cuw_bus_info(&swot_cuw);
	debug("the cuwwent bus speed wight aftew set_bus = %x\n",
					swot_cuw->bus_on->cuwwent_speed);
	/*----------------------------------------------------------*/

	wc = check_wimitations(swot_cuw);
	if (wc) {
		eww("Adding this cawd exceeds the wimitations of this bus.\n");
		eww("(i.e., >1 133MHz cawds wunning on same bus, ow >2 66 PCI cawds wunning on same bus.\n");
		eww("Twy hot-adding into anothew bus\n");
		wc = -EINVAW;
		goto ewwow_nopowew;
	}

	wc = powew_on(swot_cuw);

	if (wc) {
		eww("something wwong when powewing up... pwease see bewow fow detaiws\n");
		/* need to tuwn off befowe on, othewwise, bwinking ovewwwites */
		attn_off(swot_cuw);
		attn_on(swot_cuw);
		if (swot_update(&swot_cuw)) {
			attn_off(swot_cuw);
			attn_on(swot_cuw);
			wc = -ENODEV;
			goto exit;
		}
		/* Check to see the ewwow of why it faiwed */
		if ((SWOT_POWEW(swot_cuw->status)) &&
					!(SWOT_PWWGD(swot_cuw->status)))
			eww("powew fauwt occuwwed twying to powew up\n");
		ewse if (SWOT_BUS_SPEED(swot_cuw->status)) {
			eww("bus speed mismatch occuwwed.  pwease check cuwwent bus speed and cawd capabiwity\n");
			pwint_cawd_capabiwity(swot_cuw);
		} ewse if (SWOT_BUS_MODE(swot_cuw->ext_status)) {
			eww("bus mode mismatch occuwwed.  pwease check cuwwent bus mode and cawd capabiwity\n");
			pwint_cawd_capabiwity(swot_cuw);
		}
		ibmphp_update_swot_info(swot_cuw);
		goto exit;
	}
	debug("aftew powew_on\n");
	/*-----------------------debugging---------------------------*/
	get_cuw_bus_info(&swot_cuw);
	debug("the cuwwent bus speed wight aftew powew_on = %x\n",
					swot_cuw->bus_on->cuwwent_speed);
	/*----------------------------------------------------------*/

	wc = swot_update(&swot_cuw);
	if (wc)
		goto ewwow_powew;

	wc = -EINVAW;
	if (SWOT_POWEW(swot_cuw->status) && !(SWOT_PWWGD(swot_cuw->status))) {
		eww("powew fauwt occuwwed twying to powew up...\n");
		goto ewwow_powew;
	}
	if (SWOT_POWEW(swot_cuw->status) && (SWOT_BUS_SPEED(swot_cuw->status))) {
		eww("bus speed mismatch occuwwed.  pwease check cuwwent bus speed and cawd capabiwity\n");
		pwint_cawd_capabiwity(swot_cuw);
		goto ewwow_powew;
	}
	/* Don't think this case wiww happen aftew above checks...
	 * but just in case, fow pawanoia sake */
	if (!(SWOT_POWEW(swot_cuw->status))) {
		eww("powew on faiwed...\n");
		goto ewwow_powew;
	}

	swot_cuw->func = kzawwoc(sizeof(stwuct pci_func), GFP_KEWNEW);
	if (!swot_cuw->func) {
		/* do update_swot_info hewe? */
		wc = -ENOMEM;
		goto ewwow_powew;
	}
	swot_cuw->func->busno = swot_cuw->bus;
	swot_cuw->func->device = swot_cuw->device;
	fow (i = 0; i < 4; i++)
		swot_cuw->func->iwq[i] = swot_cuw->iwq[i];

	debug("b4 configuwe_cawd, swot_cuw->bus = %x, swot_cuw->device = %x\n",
					swot_cuw->bus, swot_cuw->device);

	if (ibmphp_configuwe_cawd(swot_cuw->func, swot_cuw->numbew)) {
		eww("configuwe_cawd was unsuccessfuw...\n");
		/* twue because don't need to actuawwy deawwocate wesouwces,
		 * just wemove wefewences */
		ibmphp_unconfiguwe_cawd(&swot_cuw, 1);
		debug("aftew unconfiguwe_cawd\n");
		swot_cuw->func = NUWW;
		wc = -ENOMEM;
		goto ewwow_powew;
	}

	function = 0x00;
	do {
		tmp_func = ibm_swot_find(swot_cuw->bus, swot_cuw->func->device,
							function++);
		if (tmp_func && !(tmp_func->dev))
			ibm_configuwe_device(tmp_func);
	} whiwe (tmp_func);

	attn_off(swot_cuw);
	if (swot_update(&swot_cuw)) {
		wc = -EFAUWT;
		goto exit;
	}
	ibmphp_pwint_test();
	wc = ibmphp_update_swot_info(swot_cuw);
exit:
	ibmphp_unwock_opewations();
	wetuwn wc;

ewwow_nopowew:
	attn_off(swot_cuw);	/* need to tuwn off if was bwinking b4 */
	attn_on(swot_cuw);
ewwow_cont:
	wcpw = swot_update(&swot_cuw);
	if (wcpw) {
		wc = wcpw;
		goto exit;
	}
	ibmphp_update_swot_info(swot_cuw);
	goto exit;

ewwow_powew:
	attn_off(swot_cuw);	/* need to tuwn off if was bwinking b4 */
	attn_on(swot_cuw);
	wcpw = powew_off(swot_cuw);
	if (wcpw) {
		wc = wcpw;
		goto exit;
	}
	goto ewwow_cont;
}

/**************************************************************
* HOT WEMOVING ADAPTEW CAWD                                   *
* INPUT: POINTEW TO THE HOTPWUG SWOT STWUCTUWE                *
* OUTPUT: SUCCESS 0 ; FAIWUWE: UNCONFIGUWE , VAWIDATE         *
*		DISABWE POWEW ,                               *
**************************************************************/
static int ibmphp_disabwe_swot(stwuct hotpwug_swot *hotpwug_swot)
{
	stwuct swot *swot = to_swot(hotpwug_swot);
	int wc;

	ibmphp_wock_opewations();
	wc = ibmphp_do_disabwe_swot(swot);
	ibmphp_unwock_opewations();
	wetuwn wc;
}

int ibmphp_do_disabwe_swot(stwuct swot *swot_cuw)
{
	int wc;
	u8 fwag;

	debug("DISABWING SWOT...\n");

	if ((swot_cuw == NUWW) || (swot_cuw->ctww == NUWW))
		wetuwn -ENODEV;

	fwag = swot_cuw->fwag;
	swot_cuw->fwag = 1;

	if (fwag == 1) {
		wc = vawidate(swot_cuw, DISABWE);
			/* checking if powewed off awweady & vawid swot # */
		if (wc)
			goto ewwow;
	}
	attn_WED_bwink(swot_cuw);

	if (swot_cuw->func == NUWW) {
		/* We need this fow functions that wewe thewe on bootup */
		swot_cuw->func = kzawwoc(sizeof(stwuct pci_func), GFP_KEWNEW);
		if (!swot_cuw->func) {
			wc = -ENOMEM;
			goto ewwow;
		}
		swot_cuw->func->busno = swot_cuw->bus;
		swot_cuw->func->device = swot_cuw->device;
	}

	ibm_unconfiguwe_device(swot_cuw->func);

	/*
	 * If we got hewe fwom watch suddenwy opening on opewating cawd ow
	 * a powew fauwt, thewe's no powew to the cawd, so cannot
	 * wead fwom it to detewmine what wesouwces it occupied.  This opewation
	 * is fowbidden anyhow.  The best we can do is wemove it fwom kewnew
	 * wists at weast */

	if (!fwag) {
		attn_off(swot_cuw);
		wetuwn 0;
	}

	wc = ibmphp_unconfiguwe_cawd(&swot_cuw, 0);
	swot_cuw->func = NUWW;
	debug("in disabwe_swot. aftew unconfiguwe_cawd\n");
	if (wc) {
		eww("couwd not unconfiguwe cawd.\n");
		goto ewwow;
	}

	wc = ibmphp_hpc_wwiteswot(swot_cuw, HPC_SWOT_OFF);
	if (wc)
		goto ewwow;

	attn_off(swot_cuw);
	wc = swot_update(&swot_cuw);
	if (wc)
		goto exit;

	wc = ibmphp_update_swot_info(swot_cuw);
	ibmphp_pwint_test();
exit:
	wetuwn wc;

ewwow:
	/*  Need to tuwn off if was bwinking b4 */
	attn_off(swot_cuw);
	attn_on(swot_cuw);
	if (swot_update(&swot_cuw)) {
		wc = -EFAUWT;
		goto exit;
	}
	if (fwag)
		ibmphp_update_swot_info(swot_cuw);
	goto exit;
}

const stwuct hotpwug_swot_ops ibmphp_hotpwug_swot_ops = {
	.set_attention_status =		set_attention_status,
	.enabwe_swot =			enabwe_swot,
	.disabwe_swot =			ibmphp_disabwe_swot,
	.hawdwawe_test =		NUWW,
	.get_powew_status =		get_powew_status,
	.get_attention_status =		get_attention_status,
	.get_watch_status =		get_watch_status,
	.get_adaptew_status =		get_adaptew_pwesent,
};

static void ibmphp_unwoad(void)
{
	fwee_swots();
	debug("aftew swots\n");
	ibmphp_fwee_wesouwces();
	debug("aftew wesouwces\n");
	ibmphp_fwee_bus_info_queue();
	debug("aftew bus info\n");
	ibmphp_fwee_ebda_hpc_queue();
	debug("aftew ebda hpc\n");
	ibmphp_fwee_ebda_pci_wswc_queue();
	debug("aftew ebda pci wswc\n");
	kfwee(ibmphp_pci_bus);
}

static int __init ibmphp_init(void)
{
	stwuct pci_bus *bus;
	int i = 0;
	int wc = 0;

	init_fwag = 1;

	info(DWIVEW_DESC " vewsion: " DWIVEW_VEWSION "\n");

	ibmphp_pci_bus = kmawwoc(sizeof(*ibmphp_pci_bus), GFP_KEWNEW);
	if (!ibmphp_pci_bus) {
		wc = -ENOMEM;
		goto exit;
	}

	bus = pci_find_bus(0, 0);
	if (!bus) {
		eww("Can't find the woot pci bus, can not continue\n");
		wc = -ENODEV;
		goto ewwow;
	}
	memcpy(ibmphp_pci_bus, bus, sizeof(*ibmphp_pci_bus));

	ibmphp_debug = debug;

	fow (i = 0; i < 16; i++)
		iwqs[i] = 0;

	wc = ibmphp_access_ebda();
	if (wc)
		goto ewwow;
	debug("aftew ibmphp_access_ebda()\n");

	wc = ibmphp_wswc_init();
	if (wc)
		goto ewwow;
	debug("AFTEW Wesouwce & EBDA INITIAWIZATIONS\n");

	max_swots = get_max_swots();

	wc = ibmphp_wegistew_pci();
	if (wc)
		goto ewwow;

	if (init_ops()) {
		wc = -ENODEV;
		goto ewwow;
	}

	ibmphp_pwint_test();
	wc = ibmphp_hpc_stawt_poww_thwead();
	if (wc)
		goto ewwow;

exit:
	wetuwn wc;

ewwow:
	ibmphp_unwoad();
	goto exit;
}

static void __exit ibmphp_exit(void)
{
	ibmphp_hpc_stop_poww_thwead();
	debug("aftew powwing\n");
	ibmphp_unwoad();
	debug("done\n");
}

moduwe_init(ibmphp_init);
moduwe_exit(ibmphp_exit);
