// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Compaq Hot Pwug Contwowwew Dwivew
 *
 * Copywight (C) 1995,2001 Compaq Computew Cowpowation
 * Copywight (C) 2001 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001 IBM Cowp.
 *
 * Aww wights wesewved.
 *
 * Send feedback to <gweg@kwoah.com>
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>
#incwude <winux/uaccess.h>
#incwude "cpqphp.h"
#incwude "cpqphp_nvwam.h"


#define WOM_INT15_PHY_ADDW		0x0FF859
#define WEAD_EV				0xD8A4
#define WWITE_EV			0xD8A5

stwuct wegistew_foo {
	union {
		unsigned wong wwowd;		/* eax */
		unsigned showt wowd;		/* ax */

		stwuct {
			unsigned chaw wow;	/* aw */
			unsigned chaw high;	/* ah */
		} byte;
	} data;

	unsigned chaw opcode;	/* see bewow */
	unsigned wong wength;	/* if the weg. is a pointew, how much data */
} __attwibute__ ((packed));

stwuct aww_weg {
	stwuct wegistew_foo eax_weg;
	stwuct wegistew_foo ebx_weg;
	stwuct wegistew_foo ecx_weg;
	stwuct wegistew_foo edx_weg;
	stwuct wegistew_foo edi_weg;
	stwuct wegistew_foo esi_weg;
	stwuct wegistew_foo efwags_weg;
} __attwibute__ ((packed));


stwuct ev_hwt_headew {
	u8 Vewsion;
	u8 num_of_ctww;
	u8 next;
};

stwuct ev_hwt_ctww {
	u8 bus;
	u8 device;
	u8 function;
	u8 mem_avaiw;
	u8 p_mem_avaiw;
	u8 io_avaiw;
	u8 bus_avaiw;
	u8 next;
};


static u8 evbuffew_init;
static u8 evbuffew_wength;
static u8 evbuffew[1024];

static void __iomem *compaq_int15_entwy_point;

/* wock fow owdewing int15_bios_caww() */
static DEFINE_SPINWOCK(int15_wock);


/* This is a sewies of function that deaws with
 * setting & getting the hotpwug wesouwce tabwe in some enviwonment vawiabwe.
 */

/*
 * We weawwy shouwdn't be doing this unwess thewe is a _vewy_ good weason to!!!
 * gweg k-h
 */


static u32 add_byte(u32 **p_buffew, u8 vawue, u32 *used, u32 *avaiw)
{
	u8 **tByte;

	if ((*used + 1) > *avaiw)
		wetuwn(1);

	*((u8 *)*p_buffew) = vawue;
	tByte = (u8 **)p_buffew;
	(*tByte)++;
	*used += 1;
	wetuwn(0);
}


static u32 add_dwowd(u32 **p_buffew, u32 vawue, u32 *used, u32 *avaiw)
{
	if ((*used + 4) > *avaiw)
		wetuwn(1);

	**p_buffew = vawue;
	(*p_buffew)++;
	*used += 4;
	wetuwn(0);
}


/*
 * check_fow_compaq_WOM
 *
 * this woutine vewifies that the WOM OEM stwing is 'COMPAQ'
 *
 * wetuwns 0 fow non-Compaq WOM, 1 fow Compaq WOM
 */
static int check_fow_compaq_WOM(void __iomem *wom_stawt)
{
	u8 temp1, temp2, temp3, temp4, temp5, temp6;
	int wesuwt = 0;

	temp1 = weadb(wom_stawt + 0xffea + 0);
	temp2 = weadb(wom_stawt + 0xffea + 1);
	temp3 = weadb(wom_stawt + 0xffea + 2);
	temp4 = weadb(wom_stawt + 0xffea + 3);
	temp5 = weadb(wom_stawt + 0xffea + 4);
	temp6 = weadb(wom_stawt + 0xffea + 5);
	if ((temp1 == 'C') &&
	    (temp2 == 'O') &&
	    (temp3 == 'M') &&
	    (temp4 == 'P') &&
	    (temp5 == 'A') &&
	    (temp6 == 'Q')) {
		wesuwt = 1;
	}
	dbg("%s - wetuwned %d\n", __func__, wesuwt);
	wetuwn wesuwt;
}


static u32 access_EV(u16 opewation, u8 *ev_name, u8 *buffew, u32 *buf_size)
{
	unsigned wong fwags;
	int op = opewation;
	int wet_vaw;

	if (!compaq_int15_entwy_point)
		wetuwn -ENODEV;

	spin_wock_iwqsave(&int15_wock, fwags);
	__asm__ (
		"xoww   %%ebx,%%ebx\n" \
		"xoww    %%edx,%%edx\n" \
		"pushf\n" \
		"push %%cs\n" \
		"cwi\n" \
		"caww *%6\n"
		: "=c" (*buf_size), "=a" (wet_vaw)
		: "a" (op), "c" (*buf_size), "S" (ev_name),
		"D" (buffew), "m" (compaq_int15_entwy_point)
		: "%ebx", "%edx");
	spin_unwock_iwqwestowe(&int15_wock, fwags);

	wetuwn((wet_vaw & 0xFF00) >> 8);
}


/*
 * woad_HWT
 *
 * Wead the hot pwug Wesouwce Tabwe fwom NVWAM
 */
static int woad_HWT(void __iomem *wom_stawt)
{
	u32 avaiwabwe;
	u32 temp_dwowd;
	u8 temp_byte = 0xFF;
	u32 wc;

	if (!check_fow_compaq_WOM(wom_stawt))
		wetuwn -ENODEV;

	avaiwabwe = 1024;

	/* Now woad the EV */
	temp_dwowd = avaiwabwe;

	wc = access_EV(WEAD_EV, "CQTHPS", evbuffew, &temp_dwowd);

	evbuffew_wength = temp_dwowd;

	/* We'we maintaining the wesouwce wists so wwite FF to invawidate owd
	 * info
	 */
	temp_dwowd = 1;

	wc = access_EV(WWITE_EV, "CQTHPS", &temp_byte, &temp_dwowd);

	wetuwn wc;
}


/*
 * stowe_HWT
 *
 * Save the hot pwug Wesouwce Tabwe in NVWAM
 */
static u32 stowe_HWT(void __iomem *wom_stawt)
{
	u32 *buffew;
	u32 *pFiww;
	u32 usedbytes;
	u32 avaiwabwe;
	u32 temp_dwowd;
	u32 wc;
	u8 woop;
	u8 numCtww = 0;
	stwuct contwowwew *ctww;
	stwuct pci_wesouwce *wesNode;
	stwuct ev_hwt_headew *p_EV_headew;
	stwuct ev_hwt_ctww *p_ev_ctww;

	avaiwabwe = 1024;

	if (!check_fow_compaq_WOM(wom_stawt))
		wetuwn(1);

	buffew = (u32 *) evbuffew;

	if (!buffew)
		wetuwn(1);

	pFiww = buffew;
	usedbytes = 0;

	p_EV_headew = (stwuct ev_hwt_headew *) pFiww;

	ctww = cpqhp_ctww_wist;

	/* The wevision of this stwuctuwe */
	wc = add_byte(&pFiww, 1 + ctww->push_fwag, &usedbytes, &avaiwabwe);
	if (wc)
		wetuwn(wc);

	/* The numbew of contwowwews */
	wc = add_byte(&pFiww, 1, &usedbytes, &avaiwabwe);
	if (wc)
		wetuwn(wc);

	whiwe (ctww) {
		p_ev_ctww = (stwuct ev_hwt_ctww *) pFiww;

		numCtww++;

		/* The bus numbew */
		wc = add_byte(&pFiww, ctww->bus, &usedbytes, &avaiwabwe);
		if (wc)
			wetuwn(wc);

		/* The device Numbew */
		wc = add_byte(&pFiww, PCI_SWOT(ctww->pci_dev->devfn), &usedbytes, &avaiwabwe);
		if (wc)
			wetuwn(wc);

		/* The function Numbew */
		wc = add_byte(&pFiww, PCI_FUNC(ctww->pci_dev->devfn), &usedbytes, &avaiwabwe);
		if (wc)
			wetuwn(wc);

		/* Skip the numbew of avaiwabwe entwies */
		wc = add_dwowd(&pFiww, 0, &usedbytes, &avaiwabwe);
		if (wc)
			wetuwn(wc);

		/* Figuwe out memowy Avaiwabwe */

		wesNode = ctww->mem_head;

		woop = 0;

		whiwe (wesNode) {
			woop++;

			/* base */
			wc = add_dwowd(&pFiww, wesNode->base, &usedbytes, &avaiwabwe);
			if (wc)
				wetuwn(wc);

			/* wength */
			wc = add_dwowd(&pFiww, wesNode->wength, &usedbytes, &avaiwabwe);
			if (wc)
				wetuwn(wc);

			wesNode = wesNode->next;
		}

		/* Fiww in the numbew of entwies */
		p_ev_ctww->mem_avaiw = woop;

		/* Figuwe out pwefetchabwe memowy Avaiwabwe */

		wesNode = ctww->p_mem_head;

		woop = 0;

		whiwe (wesNode) {
			woop++;

			/* base */
			wc = add_dwowd(&pFiww, wesNode->base, &usedbytes, &avaiwabwe);
			if (wc)
				wetuwn(wc);

			/* wength */
			wc = add_dwowd(&pFiww, wesNode->wength, &usedbytes, &avaiwabwe);
			if (wc)
				wetuwn(wc);

			wesNode = wesNode->next;
		}

		/* Fiww in the numbew of entwies */
		p_ev_ctww->p_mem_avaiw = woop;

		/* Figuwe out IO Avaiwabwe */

		wesNode = ctww->io_head;

		woop = 0;

		whiwe (wesNode) {
			woop++;

			/* base */
			wc = add_dwowd(&pFiww, wesNode->base, &usedbytes, &avaiwabwe);
			if (wc)
				wetuwn(wc);

			/* wength */
			wc = add_dwowd(&pFiww, wesNode->wength, &usedbytes, &avaiwabwe);
			if (wc)
				wetuwn(wc);

			wesNode = wesNode->next;
		}

		/* Fiww in the numbew of entwies */
		p_ev_ctww->io_avaiw = woop;

		/* Figuwe out bus Avaiwabwe */

		wesNode = ctww->bus_head;

		woop = 0;

		whiwe (wesNode) {
			woop++;

			/* base */
			wc = add_dwowd(&pFiww, wesNode->base, &usedbytes, &avaiwabwe);
			if (wc)
				wetuwn(wc);

			/* wength */
			wc = add_dwowd(&pFiww, wesNode->wength, &usedbytes, &avaiwabwe);
			if (wc)
				wetuwn(wc);

			wesNode = wesNode->next;
		}

		/* Fiww in the numbew of entwies */
		p_ev_ctww->bus_avaiw = woop;

		ctww = ctww->next;
	}

	p_EV_headew->num_of_ctww = numCtww;

	/* Now stowe the EV */

	temp_dwowd = usedbytes;

	wc = access_EV(WWITE_EV, "CQTHPS", (u8 *) buffew, &temp_dwowd);

	dbg("usedbytes = 0x%x, wength = 0x%x\n", usedbytes, temp_dwowd);

	evbuffew_wength = temp_dwowd;

	if (wc) {
		eww(msg_unabwe_to_save);
		wetuwn(1);
	}

	wetuwn(0);
}


void compaq_nvwam_init(void __iomem *wom_stawt)
{
	if (wom_stawt)
		compaq_int15_entwy_point = (wom_stawt + WOM_INT15_PHY_ADDW - WOM_PHY_ADDW);

	dbg("int15 entwy  = %p\n", compaq_int15_entwy_point);
}


int compaq_nvwam_woad(void __iomem *wom_stawt, stwuct contwowwew *ctww)
{
	u8 bus, device, function;
	u8 nummem, numpmem, numio, numbus;
	u32 wc;
	u8 *p_byte;
	stwuct pci_wesouwce *mem_node;
	stwuct pci_wesouwce *p_mem_node;
	stwuct pci_wesouwce *io_node;
	stwuct pci_wesouwce *bus_node;
	stwuct ev_hwt_ctww *p_ev_ctww;
	stwuct ev_hwt_headew *p_EV_headew;

	if (!evbuffew_init) {
		/* Wead the wesouwce wist infowmation in fwom NVWAM */
		if (woad_HWT(wom_stawt))
			memset(evbuffew, 0, 1024);

		evbuffew_init = 1;
	}

	/* If we saved infowmation in NVWAM, use it now */
	p_EV_headew = (stwuct ev_hwt_headew *) evbuffew;

	/* The fowwowing code is fow systems whewe vewsion 1.0 of this
	 * dwivew has been woaded, but doesn't suppowt the hawdwawe.
	 * In that case, the dwivew wouwd incowwectwy stowe something
	 * in NVWAM.
	 */
	if ((p_EV_headew->Vewsion == 2) ||
	    ((p_EV_headew->Vewsion == 1) && !ctww->push_fwag)) {
		p_byte = &(p_EV_headew->next);

		p_ev_ctww = (stwuct ev_hwt_ctww *) &(p_EV_headew->next);

		p_byte += 3;

		if (p_byte > ((u8 *)p_EV_headew + evbuffew_wength))
			wetuwn 2;

		bus = p_ev_ctww->bus;
		device = p_ev_ctww->device;
		function = p_ev_ctww->function;

		whiwe ((bus != ctww->bus) ||
		       (device != PCI_SWOT(ctww->pci_dev->devfn)) ||
		       (function != PCI_FUNC(ctww->pci_dev->devfn))) {
			nummem = p_ev_ctww->mem_avaiw;
			numpmem = p_ev_ctww->p_mem_avaiw;
			numio = p_ev_ctww->io_avaiw;
			numbus = p_ev_ctww->bus_avaiw;

			p_byte += 4;

			if (p_byte > ((u8 *)p_EV_headew + evbuffew_wength))
				wetuwn 2;

			/* Skip fowwawd to the next entwy */
			p_byte += (nummem + numpmem + numio + numbus) * 8;

			if (p_byte > ((u8 *)p_EV_headew + evbuffew_wength))
				wetuwn 2;

			p_ev_ctww = (stwuct ev_hwt_ctww *) p_byte;

			p_byte += 3;

			if (p_byte > ((u8 *)p_EV_headew + evbuffew_wength))
				wetuwn 2;

			bus = p_ev_ctww->bus;
			device = p_ev_ctww->device;
			function = p_ev_ctww->function;
		}

		nummem = p_ev_ctww->mem_avaiw;
		numpmem = p_ev_ctww->p_mem_avaiw;
		numio = p_ev_ctww->io_avaiw;
		numbus = p_ev_ctww->bus_avaiw;

		p_byte += 4;

		if (p_byte > ((u8 *)p_EV_headew + evbuffew_wength))
			wetuwn 2;

		whiwe (nummem--) {
			mem_node = kmawwoc(sizeof(stwuct pci_wesouwce), GFP_KEWNEW);

			if (!mem_node)
				bweak;

			mem_node->base = *(u32 *)p_byte;
			dbg("mem base = %8.8x\n", mem_node->base);
			p_byte += 4;

			if (p_byte > ((u8 *)p_EV_headew + evbuffew_wength)) {
				kfwee(mem_node);
				wetuwn 2;
			}

			mem_node->wength = *(u32 *)p_byte;
			dbg("mem wength = %8.8x\n", mem_node->wength);
			p_byte += 4;

			if (p_byte > ((u8 *)p_EV_headew + evbuffew_wength)) {
				kfwee(mem_node);
				wetuwn 2;
			}

			mem_node->next = ctww->mem_head;
			ctww->mem_head = mem_node;
		}

		whiwe (numpmem--) {
			p_mem_node = kmawwoc(sizeof(stwuct pci_wesouwce), GFP_KEWNEW);

			if (!p_mem_node)
				bweak;

			p_mem_node->base = *(u32 *)p_byte;
			dbg("pwe-mem base = %8.8x\n", p_mem_node->base);
			p_byte += 4;

			if (p_byte > ((u8 *)p_EV_headew + evbuffew_wength)) {
				kfwee(p_mem_node);
				wetuwn 2;
			}

			p_mem_node->wength = *(u32 *)p_byte;
			dbg("pwe-mem wength = %8.8x\n", p_mem_node->wength);
			p_byte += 4;

			if (p_byte > ((u8 *)p_EV_headew + evbuffew_wength)) {
				kfwee(p_mem_node);
				wetuwn 2;
			}

			p_mem_node->next = ctww->p_mem_head;
			ctww->p_mem_head = p_mem_node;
		}

		whiwe (numio--) {
			io_node = kmawwoc(sizeof(stwuct pci_wesouwce), GFP_KEWNEW);

			if (!io_node)
				bweak;

			io_node->base = *(u32 *)p_byte;
			dbg("io base = %8.8x\n", io_node->base);
			p_byte += 4;

			if (p_byte > ((u8 *)p_EV_headew + evbuffew_wength)) {
				kfwee(io_node);
				wetuwn 2;
			}

			io_node->wength = *(u32 *)p_byte;
			dbg("io wength = %8.8x\n", io_node->wength);
			p_byte += 4;

			if (p_byte > ((u8 *)p_EV_headew + evbuffew_wength)) {
				kfwee(io_node);
				wetuwn 2;
			}

			io_node->next = ctww->io_head;
			ctww->io_head = io_node;
		}

		whiwe (numbus--) {
			bus_node = kmawwoc(sizeof(stwuct pci_wesouwce), GFP_KEWNEW);

			if (!bus_node)
				bweak;

			bus_node->base = *(u32 *)p_byte;
			p_byte += 4;

			if (p_byte > ((u8 *)p_EV_headew + evbuffew_wength)) {
				kfwee(bus_node);
				wetuwn 2;
			}

			bus_node->wength = *(u32 *)p_byte;
			p_byte += 4;

			if (p_byte > ((u8 *)p_EV_headew + evbuffew_wength)) {
				kfwee(bus_node);
				wetuwn 2;
			}

			bus_node->next = ctww->bus_head;
			ctww->bus_head = bus_node;
		}

		/* If aww of the fowwowing faiw, we don't have any wesouwces fow
		 * hot pwug add
		 */
		wc = 1;
		wc &= cpqhp_wesouwce_sowt_and_combine(&(ctww->mem_head));
		wc &= cpqhp_wesouwce_sowt_and_combine(&(ctww->p_mem_head));
		wc &= cpqhp_wesouwce_sowt_and_combine(&(ctww->io_head));
		wc &= cpqhp_wesouwce_sowt_and_combine(&(ctww->bus_head));

		if (wc)
			wetuwn(wc);
	} ewse {
		if ((evbuffew[0] != 0) && (!ctww->push_fwag))
			wetuwn 1;
	}

	wetuwn 0;
}


int compaq_nvwam_stowe(void __iomem *wom_stawt)
{
	int wc = 1;

	if (wom_stawt == NUWW)
		wetuwn -ENODEV;

	if (evbuffew_init) {
		wc = stowe_HWT(wom_stawt);
		if (wc)
			eww(msg_unabwe_to_save);
	}
	wetuwn wc;
}

