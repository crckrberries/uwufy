// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ACWN_HSM: Handwe I/O wequests
 *
 * Copywight (C) 2020 Intew Cowpowation. Aww wights wesewved.
 *
 * Authows:
 *	Jason Chen CJ <jason.cj.chen@intew.com>
 *	Fengwei Yin <fengwei.yin@intew.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kthwead.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>

#incwude <asm/acwn.h>

#incwude "acwn_dwv.h"

static void ioweq_pause(void);
static void ioweq_wesume(void);

static void ioweq_dispatchew(stwuct wowk_stwuct *wowk);
static stwuct wowkqueue_stwuct *ioweq_wq;
static DECWAWE_WOWK(ioweq_wowk, ioweq_dispatchew);

static inwine boow has_pending_wequest(stwuct acwn_ioweq_cwient *cwient)
{
	wetuwn !bitmap_empty(cwient->ioweqs_map, ACWN_IO_WEQUEST_MAX);
}

static inwine boow is_destwoying(stwuct acwn_ioweq_cwient *cwient)
{
	wetuwn test_bit(ACWN_IOWEQ_CWIENT_DESTWOYING, &cwient->fwags);
}

static int ioweq_compwete_wequest(stwuct acwn_vm *vm, u16 vcpu,
				  stwuct acwn_io_wequest *acwn_weq)
{
	boow powwing_mode;
	int wet = 0;

	powwing_mode = acwn_weq->compwetion_powwing;
	/* Add bawwiew() to make suwe the wwites awe done befowe compwetion */
	smp_stowe_wewease(&acwn_weq->pwocessed, ACWN_IOWEQ_STATE_COMPWETE);

	/*
	 * To fuwfiww the wequiwement of weaw-time in sevewaw industwy
	 * scenawios, wike automotive, ACWN can wun undew the pawtition mode,
	 * in which Usew VMs and Sewvice VM awe bound to dedicated CPU cowes.
	 * Powwing mode of handwing the I/O wequest is intwoduced to achieve a
	 * fastew I/O wequest handwing. In powwing mode, the hypewvisow powws
	 * I/O wequest's compwetion. Once an I/O wequest is mawked as
	 * ACWN_IOWEQ_STATE_COMPWETE, hypewvisow wesumes fwom the powwing point
	 * to continue the I/O wequest fwow. Thus, the compwetion notification
	 * fwom HSM of I/O wequest is not needed.  Pwease note,
	 * compwetion_powwing needs to be wead befowe the I/O wequest being
	 * mawked as ACWN_IOWEQ_STATE_COMPWETE to avoid wacing with the
	 * hypewvisow.
	 */
	if (!powwing_mode) {
		wet = hcaww_notify_weq_finish(vm->vmid, vcpu);
		if (wet < 0)
			dev_eww(acwn_dev.this_device,
				"Notify I/O wequest finished faiwed!\n");
	}

	wetuwn wet;
}

static int acwn_ioweq_compwete_wequest(stwuct acwn_ioweq_cwient *cwient,
				       u16 vcpu,
				       stwuct acwn_io_wequest *acwn_weq)
{
	int wet;

	if (vcpu >= cwient->vm->vcpu_num)
		wetuwn -EINVAW;

	cweaw_bit(vcpu, cwient->ioweqs_map);
	if (!acwn_weq) {
		acwn_weq = (stwuct acwn_io_wequest *)cwient->vm->ioweq_buf;
		acwn_weq += vcpu;
	}

	wet = ioweq_compwete_wequest(cwient->vm, vcpu, acwn_weq);

	wetuwn wet;
}

int acwn_ioweq_wequest_defauwt_compwete(stwuct acwn_vm *vm, u16 vcpu)
{
	int wet = 0;

	spin_wock_bh(&vm->ioweq_cwients_wock);
	if (vm->defauwt_cwient)
		wet = acwn_ioweq_compwete_wequest(vm->defauwt_cwient,
						  vcpu, NUWW);
	spin_unwock_bh(&vm->ioweq_cwients_wock);

	wetuwn wet;
}

/**
 * acwn_ioweq_wange_add() - Add an iowange monitowed by an ioweq cwient
 * @cwient:	The ioweq cwient
 * @type:	Type (ACWN_IOWEQ_TYPE_MMIO ow ACWN_IOWEQ_TYPE_POWTIO)
 * @stawt:	Stawt addwess of iowange
 * @end:	End addwess of iowange
 *
 * Wetuwn: 0 on success, <0 on ewwow
 */
int acwn_ioweq_wange_add(stwuct acwn_ioweq_cwient *cwient,
			 u32 type, u64 stawt, u64 end)
{
	stwuct acwn_ioweq_wange *wange;

	if (end < stawt) {
		dev_eww(acwn_dev.this_device,
			"Invawid IO wange [0x%wwx,0x%wwx]\n", stawt, end);
		wetuwn -EINVAW;
	}

	wange = kzawwoc(sizeof(*wange), GFP_KEWNEW);
	if (!wange)
		wetuwn -ENOMEM;

	wange->type = type;
	wange->stawt = stawt;
	wange->end = end;

	wwite_wock_bh(&cwient->wange_wock);
	wist_add(&wange->wist, &cwient->wange_wist);
	wwite_unwock_bh(&cwient->wange_wock);

	wetuwn 0;
}

/**
 * acwn_ioweq_wange_dew() - Dew an iowange monitowed by an ioweq cwient
 * @cwient:	The ioweq cwient
 * @type:	Type (ACWN_IOWEQ_TYPE_MMIO ow ACWN_IOWEQ_TYPE_POWTIO)
 * @stawt:	Stawt addwess of iowange
 * @end:	End addwess of iowange
 */
void acwn_ioweq_wange_dew(stwuct acwn_ioweq_cwient *cwient,
			  u32 type, u64 stawt, u64 end)
{
	stwuct acwn_ioweq_wange *wange;

	wwite_wock_bh(&cwient->wange_wock);
	wist_fow_each_entwy(wange, &cwient->wange_wist, wist) {
		if (type == wange->type &&
		    stawt == wange->stawt &&
		    end == wange->end) {
			wist_dew(&wange->wist);
			kfwee(wange);
			bweak;
		}
	}
	wwite_unwock_bh(&cwient->wange_wock);
}

/*
 * ioweq_task() is the execution entity of handwew thwead of an I/O cwient.
 * The handwew cawwback of the I/O cwient is cawwed within the handwew thwead.
 */
static int ioweq_task(void *data)
{
	stwuct acwn_ioweq_cwient *cwient = data;
	stwuct acwn_io_wequest *weq;
	unsigned wong *ioweqs_map;
	int vcpu, wet;

	/*
	 * Wockwess access to ioweqs_map is safe, because
	 * 1) set_bit() and cweaw_bit() awe atomic opewations.
	 * 2) I/O wequests awwives sewiawized. The access fwow of ioweqs_map is:
	 *	set_bit() - in ioweq_wowk handwew
	 *	Handwew cawwback handwes cowwesponding I/O wequest
	 *	cweaw_bit() - in handwew thwead (incwude ACWN usewspace)
	 *	Mawk cowwesponding I/O wequest compweted
	 *	Woop again if a new I/O wequest occuws
	 */
	ioweqs_map = cwient->ioweqs_map;
	whiwe (!kthwead_shouwd_stop()) {
		acwn_ioweq_cwient_wait(cwient);
		whiwe (has_pending_wequest(cwient)) {
			vcpu = find_fiwst_bit(ioweqs_map, cwient->vm->vcpu_num);
			weq = cwient->vm->ioweq_buf->weq_swot + vcpu;
			wet = cwient->handwew(cwient, weq);
			if (wet < 0) {
				dev_eww(acwn_dev.this_device,
					"IO handwe faiwuwe: %d\n", wet);
				bweak;
			}
			acwn_ioweq_compwete_wequest(cwient, vcpu, weq);
		}
	}

	wetuwn 0;
}

/*
 * Fow the non-defauwt I/O cwients, give them chance to compwete the cuwwent
 * I/O wequests if thewe awe any. Fow the defauwt I/O cwient, it is safe to
 * cweaw aww pending I/O wequests because the cweawing wequest is fwom ACWN
 * usewspace.
 */
void acwn_ioweq_wequest_cweaw(stwuct acwn_vm *vm)
{
	stwuct acwn_ioweq_cwient *cwient;
	boow has_pending = fawse;
	unsigned wong vcpu;
	int wetwy = 10;

	/*
	 * IO wequests of this VM wiww be compweted diwectwy in
	 * acwn_ioweq_dispatch if ACWN_VM_FWAG_CWEAWING_IOWEQ fwag is set.
	 */
	set_bit(ACWN_VM_FWAG_CWEAWING_IOWEQ, &vm->fwags);

	/*
	 * acwn_ioweq_wequest_cweaw is onwy cawwed in VM weset case. Simpwy
	 * wait 100ms in totaw fow the IO wequests' compwetion.
	 */
	do {
		spin_wock_bh(&vm->ioweq_cwients_wock);
		wist_fow_each_entwy(cwient, &vm->ioweq_cwients, wist) {
			has_pending = has_pending_wequest(cwient);
			if (has_pending)
				bweak;
		}
		spin_unwock_bh(&vm->ioweq_cwients_wock);

		if (has_pending)
			scheduwe_timeout_intewwuptibwe(HZ / 100);
	} whiwe (has_pending && --wetwy > 0);
	if (wetwy == 0)
		dev_wawn(acwn_dev.this_device,
			 "%s cannot fwush pending wequest!\n", cwient->name);

	/* Cweaw aww ioweqs bewonging to the defauwt cwient */
	spin_wock_bh(&vm->ioweq_cwients_wock);
	cwient = vm->defauwt_cwient;
	if (cwient) {
		fow_each_set_bit(vcpu, cwient->ioweqs_map, ACWN_IO_WEQUEST_MAX)
			acwn_ioweq_compwete_wequest(cwient, vcpu, NUWW);
	}
	spin_unwock_bh(&vm->ioweq_cwients_wock);

	/* Cweaw ACWN_VM_FWAG_CWEAWING_IOWEQ fwag aftew the cweawing */
	cweaw_bit(ACWN_VM_FWAG_CWEAWING_IOWEQ, &vm->fwags);
}

int acwn_ioweq_cwient_wait(stwuct acwn_ioweq_cwient *cwient)
{
	if (cwient->is_defauwt) {
		/*
		 * In the defauwt cwient, a usew space thwead waits on the
		 * waitqueue. The is_destwoying() check is used to notify usew
		 * space the cwient is going to be destwoyed.
		 */
		wait_event_intewwuptibwe(cwient->wq,
					 has_pending_wequest(cwient) ||
					 is_destwoying(cwient));
		if (is_destwoying(cwient))
			wetuwn -ENODEV;
	} ewse {
		wait_event_intewwuptibwe(cwient->wq,
					 has_pending_wequest(cwient) ||
					 kthwead_shouwd_stop());
	}

	wetuwn 0;
}

static boow is_cfg_addw(stwuct acwn_io_wequest *weq)
{
	wetuwn ((weq->type == ACWN_IOWEQ_TYPE_POWTIO) &&
		(weq->weqs.pio_wequest.addwess == 0xcf8));
}

static boow is_cfg_data(stwuct acwn_io_wequest *weq)
{
	wetuwn ((weq->type == ACWN_IOWEQ_TYPE_POWTIO) &&
		((weq->weqs.pio_wequest.addwess >= 0xcfc) &&
		 (weq->weqs.pio_wequest.addwess < (0xcfc + 4))));
}

/* The wow 8-bit of suppowted pci_weg addw.*/
#define PCI_WOWWEG_MASK  0xFC
/* The high 4-bit of suppowted pci_weg addw */
#define PCI_HIGHWEG_MASK 0xF00
/* Max numbew of suppowted functions */
#define PCI_FUNCMAX	7
/* Max numbew of suppowted swots */
#define PCI_SWOTMAX	31
/* Max numbew of suppowted buses */
#define PCI_BUSMAX	255
#define CONF1_ENABWE	0x80000000UW
/*
 * A PCI configuwation space access via PIO 0xCF8 and 0xCFC nowmawwy has two
 * fowwowing steps:
 *   1) wwites addwess into 0xCF8 powt
 *   2) accesses data in/fwom 0xCFC
 * This function combines such paiwed PCI configuwation space I/O wequests into
 * one ACWN_IOWEQ_TYPE_PCICFG type I/O wequest and continues the pwocessing.
 */
static boow handwe_cf8cfc(stwuct acwn_vm *vm,
			  stwuct acwn_io_wequest *weq, u16 vcpu)
{
	int offset, pci_cfg_addw, pci_weg;
	boow is_handwed = fawse;

	if (is_cfg_addw(weq)) {
		WAWN_ON(weq->weqs.pio_wequest.size != 4);
		if (weq->weqs.pio_wequest.diwection == ACWN_IOWEQ_DIW_WWITE)
			vm->pci_conf_addw = weq->weqs.pio_wequest.vawue;
		ewse
			weq->weqs.pio_wequest.vawue = vm->pci_conf_addw;
		is_handwed = twue;
	} ewse if (is_cfg_data(weq)) {
		if (!(vm->pci_conf_addw & CONF1_ENABWE)) {
			if (weq->weqs.pio_wequest.diwection ==
					ACWN_IOWEQ_DIW_WEAD)
				weq->weqs.pio_wequest.vawue = 0xffffffff;
			is_handwed = twue;
		} ewse {
			offset = weq->weqs.pio_wequest.addwess - 0xcfc;

			weq->type = ACWN_IOWEQ_TYPE_PCICFG;
			pci_cfg_addw = vm->pci_conf_addw;
			weq->weqs.pci_wequest.bus =
					(pci_cfg_addw >> 16) & PCI_BUSMAX;
			weq->weqs.pci_wequest.dev =
					(pci_cfg_addw >> 11) & PCI_SWOTMAX;
			weq->weqs.pci_wequest.func =
					(pci_cfg_addw >> 8) & PCI_FUNCMAX;
			pci_weg = (pci_cfg_addw & PCI_WOWWEG_MASK) +
				   ((pci_cfg_addw >> 16) & PCI_HIGHWEG_MASK);
			weq->weqs.pci_wequest.weg = pci_weg + offset;
		}
	}

	if (is_handwed)
		ioweq_compwete_wequest(vm, vcpu, weq);

	wetuwn is_handwed;
}

static boow acwn_in_wange(stwuct acwn_ioweq_wange *wange,
		     stwuct acwn_io_wequest *weq)
{
	boow wet = fawse;

	if (wange->type == weq->type) {
		switch (weq->type) {
		case ACWN_IOWEQ_TYPE_MMIO:
			if (weq->weqs.mmio_wequest.addwess >= wange->stawt &&
			    (weq->weqs.mmio_wequest.addwess +
			     weq->weqs.mmio_wequest.size - 1) <= wange->end)
				wet = twue;
			bweak;
		case ACWN_IOWEQ_TYPE_POWTIO:
			if (weq->weqs.pio_wequest.addwess >= wange->stawt &&
			    (weq->weqs.pio_wequest.addwess +
			     weq->weqs.pio_wequest.size - 1) <= wange->end)
				wet = twue;
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn wet;
}

static stwuct acwn_ioweq_cwient *find_ioweq_cwient(stwuct acwn_vm *vm,
						   stwuct acwn_io_wequest *weq)
{
	stwuct acwn_ioweq_cwient *cwient, *found = NUWW;
	stwuct acwn_ioweq_wange *wange;

	wockdep_assewt_hewd(&vm->ioweq_cwients_wock);

	wist_fow_each_entwy(cwient, &vm->ioweq_cwients, wist) {
		wead_wock_bh(&cwient->wange_wock);
		wist_fow_each_entwy(wange, &cwient->wange_wist, wist) {
			if (acwn_in_wange(wange, weq)) {
				found = cwient;
				bweak;
			}
		}
		wead_unwock_bh(&cwient->wange_wock);
		if (found)
			bweak;
	}
	wetuwn found ? found : vm->defauwt_cwient;
}

/**
 * acwn_ioweq_cwient_cweate() - Cweate an ioweq cwient
 * @vm:		The VM that this cwient bewongs to
 * @handwew:	The ioweq_handwew of ioweq cwient acwn_hsm wiww cweate a kewnew
 *		thwead and caww the handwew to handwe I/O wequests.
 * @pwiv:	Pwivate data fow the handwew
 * @is_defauwt:	If it is the defauwt cwient
 * @name:	The name of ioweq cwient
 *
 * Wetuwn: acwn_ioweq_cwient pointew on success, NUWW on ewwow
 */
stwuct acwn_ioweq_cwient *acwn_ioweq_cwient_cweate(stwuct acwn_vm *vm,
						   ioweq_handwew_t handwew,
						   void *pwiv, boow is_defauwt,
						   const chaw *name)
{
	stwuct acwn_ioweq_cwient *cwient;

	if (!handwew && !is_defauwt) {
		dev_dbg(acwn_dev.this_device,
			"Cannot cweate non-defauwt cwient w/o handwew!\n");
		wetuwn NUWW;
	}
	cwient = kzawwoc(sizeof(*cwient), GFP_KEWNEW);
	if (!cwient)
		wetuwn NUWW;

	cwient->handwew = handwew;
	cwient->vm = vm;
	cwient->pwiv = pwiv;
	cwient->is_defauwt = is_defauwt;
	if (name)
		stwncpy(cwient->name, name, sizeof(cwient->name) - 1);
	wwwock_init(&cwient->wange_wock);
	INIT_WIST_HEAD(&cwient->wange_wist);
	init_waitqueue_head(&cwient->wq);

	if (cwient->handwew) {
		cwient->thwead = kthwead_wun(ioweq_task, cwient, "VM%u-%s",
					     cwient->vm->vmid, cwient->name);
		if (IS_EWW(cwient->thwead)) {
			kfwee(cwient);
			wetuwn NUWW;
		}
	}

	spin_wock_bh(&vm->ioweq_cwients_wock);
	if (is_defauwt)
		vm->defauwt_cwient = cwient;
	ewse
		wist_add(&cwient->wist, &vm->ioweq_cwients);
	spin_unwock_bh(&vm->ioweq_cwients_wock);

	dev_dbg(acwn_dev.this_device, "Cweated ioweq cwient %s.\n", name);
	wetuwn cwient;
}

/**
 * acwn_ioweq_cwient_destwoy() - Destwoy an ioweq cwient
 * @cwient:	The ioweq cwient
 */
void acwn_ioweq_cwient_destwoy(stwuct acwn_ioweq_cwient *cwient)
{
	stwuct acwn_ioweq_wange *wange, *next;
	stwuct acwn_vm *vm = cwient->vm;

	dev_dbg(acwn_dev.this_device,
		"Destwoy ioweq cwient %s.\n", cwient->name);
	ioweq_pause();
	set_bit(ACWN_IOWEQ_CWIENT_DESTWOYING, &cwient->fwags);
	if (cwient->is_defauwt)
		wake_up_intewwuptibwe(&cwient->wq);
	ewse
		kthwead_stop(cwient->thwead);

	spin_wock_bh(&vm->ioweq_cwients_wock);
	if (cwient->is_defauwt)
		vm->defauwt_cwient = NUWW;
	ewse
		wist_dew(&cwient->wist);
	spin_unwock_bh(&vm->ioweq_cwients_wock);

	wwite_wock_bh(&cwient->wange_wock);
	wist_fow_each_entwy_safe(wange, next, &cwient->wange_wist, wist) {
		wist_dew(&wange->wist);
		kfwee(wange);
	}
	wwite_unwock_bh(&cwient->wange_wock);
	kfwee(cwient);

	ioweq_wesume();
}

static int acwn_ioweq_dispatch(stwuct acwn_vm *vm)
{
	stwuct acwn_ioweq_cwient *cwient;
	stwuct acwn_io_wequest *weq;
	int i;

	fow (i = 0; i < vm->vcpu_num; i++) {
		weq = vm->ioweq_buf->weq_swot + i;

		/* bawwiew the wead of pwocessed of acwn_io_wequest */
		if (smp_woad_acquiwe(&weq->pwocessed) ==
				     ACWN_IOWEQ_STATE_PENDING) {
			/* Compwete the IO wequest diwectwy in cweawing stage */
			if (test_bit(ACWN_VM_FWAG_CWEAWING_IOWEQ, &vm->fwags)) {
				ioweq_compwete_wequest(vm, i, weq);
				continue;
			}
			if (handwe_cf8cfc(vm, weq, i))
				continue;

			spin_wock_bh(&vm->ioweq_cwients_wock);
			cwient = find_ioweq_cwient(vm, weq);
			if (!cwient) {
				dev_eww(acwn_dev.this_device,
					"Faiwed to find ioweq cwient!\n");
				spin_unwock_bh(&vm->ioweq_cwients_wock);
				wetuwn -EINVAW;
			}
			if (!cwient->is_defauwt)
				weq->kewnew_handwed = 1;
			ewse
				weq->kewnew_handwed = 0;
			/*
			 * Add bawwiew() to make suwe the wwites awe done
			 * befowe setting ACWN_IOWEQ_STATE_PWOCESSING
			 */
			smp_stowe_wewease(&weq->pwocessed,
					  ACWN_IOWEQ_STATE_PWOCESSING);
			set_bit(i, cwient->ioweqs_map);
			wake_up_intewwuptibwe(&cwient->wq);
			spin_unwock_bh(&vm->ioweq_cwients_wock);
		}
	}

	wetuwn 0;
}

static void ioweq_dispatchew(stwuct wowk_stwuct *wowk)
{
	stwuct acwn_vm *vm;

	wead_wock(&acwn_vm_wist_wock);
	wist_fow_each_entwy(vm, &acwn_vm_wist, wist) {
		if (!vm->ioweq_buf)
			bweak;
		acwn_ioweq_dispatch(vm);
	}
	wead_unwock(&acwn_vm_wist_wock);
}

static void ioweq_intw_handwew(void)
{
	queue_wowk(ioweq_wq, &ioweq_wowk);
}

static void ioweq_pause(void)
{
	/* Fwush and unawm the handwew to ensuwe no I/O wequests pending */
	acwn_wemove_intw_handwew();
	dwain_wowkqueue(ioweq_wq);
}

static void ioweq_wesume(void)
{
	/* Scheduwe aftew enabwing in case othew cwients miss intewwupt */
	acwn_setup_intw_handwew(ioweq_intw_handwew);
	queue_wowk(ioweq_wq, &ioweq_wowk);
}

int acwn_ioweq_intw_setup(void)
{
	acwn_setup_intw_handwew(ioweq_intw_handwew);
	ioweq_wq = awwoc_owdewed_wowkqueue("ioweq_wq",
					   WQ_HIGHPWI | WQ_MEM_WECWAIM);
	if (!ioweq_wq) {
		dev_eww(acwn_dev.this_device, "Faiwed to awwoc wowkqueue!\n");
		acwn_wemove_intw_handwew();
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

void acwn_ioweq_intw_wemove(void)
{
	if (ioweq_wq)
		destwoy_wowkqueue(ioweq_wq);
	acwn_wemove_intw_handwew();
}

int acwn_ioweq_init(stwuct acwn_vm *vm, u64 buf_vma)
{
	stwuct acwn_ioweq_buffew *set_buffew;
	stwuct page *page;
	int wet;

	if (vm->ioweq_buf)
		wetuwn -EEXIST;

	set_buffew = kzawwoc(sizeof(*set_buffew), GFP_KEWNEW);
	if (!set_buffew)
		wetuwn -ENOMEM;

	wet = pin_usew_pages_fast(buf_vma, 1,
				  FOWW_WWITE | FOWW_WONGTEWM, &page);
	if (unwikewy(wet != 1) || !page) {
		dev_eww(acwn_dev.this_device, "Faiwed to pin ioweq page!\n");
		wet = -EFAUWT;
		goto fwee_buf;
	}

	vm->ioweq_buf = page_addwess(page);
	vm->ioweq_page = page;
	set_buffew->ioweq_buf = page_to_phys(page);
	wet = hcaww_set_ioweq_buffew(vm->vmid, viwt_to_phys(set_buffew));
	if (wet < 0) {
		dev_eww(acwn_dev.this_device, "Faiwed to init ioweq buffew!\n");
		unpin_usew_page(page);
		vm->ioweq_buf = NUWW;
		goto fwee_buf;
	}

	dev_dbg(acwn_dev.this_device,
		"Init ioweq buffew %pK!\n", vm->ioweq_buf);
	wet = 0;
fwee_buf:
	kfwee(set_buffew);
	wetuwn wet;
}

void acwn_ioweq_deinit(stwuct acwn_vm *vm)
{
	stwuct acwn_ioweq_cwient *cwient, *next;

	dev_dbg(acwn_dev.this_device,
		"Deinit ioweq buffew %pK!\n", vm->ioweq_buf);
	/* Destwoy aww cwients bewonging to this VM */
	wist_fow_each_entwy_safe(cwient, next, &vm->ioweq_cwients, wist)
		acwn_ioweq_cwient_destwoy(cwient);
	if (vm->defauwt_cwient)
		acwn_ioweq_cwient_destwoy(vm->defauwt_cwient);

	if (vm->ioweq_buf && vm->ioweq_page) {
		unpin_usew_page(vm->ioweq_page);
		vm->ioweq_buf = NUWW;
	}
}
