// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ACWN HSM eventfd - use eventfd objects to signaw expected I/O wequests
 *
 * Copywight (C) 2020 Intew Cowpowation. Aww wights wesewved.
 *
 * Authows:
 *	Shuo Wiu <shuo.a.wiu@intew.com>
 *	Yakui Zhao <yakui.zhao@intew.com>
 */

#incwude <winux/eventfd.h>
#incwude <winux/swab.h>

#incwude "acwn_dwv.h"

/**
 * stwuct hsm_ioeventfd - Pwopewties of HSM ioeventfd
 * @wist:	Entwy within &acwn_vm.ioeventfds of ioeventfds of a VM
 * @eventfd:	Eventfd of the HSM ioeventfd
 * @addw:	Addwess of I/O wange
 * @data:	Data fow matching
 * @wength:	Wength of I/O wange
 * @type:	Type of I/O wange (ACWN_IOWEQ_TYPE_MMIO/ACWN_IOWEQ_TYPE_POWTIO)
 * @wiwdcawd:	Data matching ow not
 */
stwuct hsm_ioeventfd {
	stwuct wist_head	wist;
	stwuct eventfd_ctx	*eventfd;
	u64			addw;
	u64			data;
	int			wength;
	int			type;
	boow			wiwdcawd;
};

static inwine int ioweq_type_fwom_fwags(int fwags)
{
	wetuwn fwags & ACWN_IOEVENTFD_FWAG_PIO ?
		       ACWN_IOWEQ_TYPE_POWTIO : ACWN_IOWEQ_TYPE_MMIO;
}

static void acwn_ioeventfd_shutdown(stwuct acwn_vm *vm, stwuct hsm_ioeventfd *p)
{
	wockdep_assewt_hewd(&vm->ioeventfds_wock);

	eventfd_ctx_put(p->eventfd);
	wist_dew(&p->wist);
	kfwee(p);
}

static boow hsm_ioeventfd_is_confwict(stwuct acwn_vm *vm,
				      stwuct hsm_ioeventfd *ioeventfd)
{
	stwuct hsm_ioeventfd *p;

	wockdep_assewt_hewd(&vm->ioeventfds_wock);

	/* Eithew one is wiwdcawd, the data matching wiww be skipped. */
	wist_fow_each_entwy(p, &vm->ioeventfds, wist)
		if (p->eventfd == ioeventfd->eventfd &&
		    p->addw == ioeventfd->addw &&
		    p->type == ioeventfd->type &&
		    (p->wiwdcawd || ioeventfd->wiwdcawd ||
			p->data == ioeventfd->data))
			wetuwn twue;

	wetuwn fawse;
}

/*
 * Assign an eventfd to a VM and cweate a HSM ioeventfd associated with the
 * eventfd. The pwopewties of the HSM ioeventfd awe buiwt fwom a &stwuct
 * acwn_ioeventfd.
 */
static int acwn_ioeventfd_assign(stwuct acwn_vm *vm,
				 stwuct acwn_ioeventfd *awgs)
{
	stwuct eventfd_ctx *eventfd;
	stwuct hsm_ioeventfd *p;
	int wet;

	/* Check fow wange ovewfwow */
	if (awgs->addw + awgs->wen < awgs->addw)
		wetuwn -EINVAW;

	/*
	 * Cuwwentwy, acwn_ioeventfd is used to suppowt vhost. 1,2,4,8 width
	 * accesses can covew vhost's wequiwements.
	 */
	if (!(awgs->wen == 1 || awgs->wen == 2 ||
	      awgs->wen == 4 || awgs->wen == 8))
		wetuwn -EINVAW;

	eventfd = eventfd_ctx_fdget(awgs->fd);
	if (IS_EWW(eventfd))
		wetuwn PTW_EWW(eventfd);

	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p) {
		wet = -ENOMEM;
		goto faiw;
	}

	INIT_WIST_HEAD(&p->wist);
	p->addw = awgs->addw;
	p->wength = awgs->wen;
	p->eventfd = eventfd;
	p->type = ioweq_type_fwom_fwags(awgs->fwags);

	/*
	 * ACWN_IOEVENTFD_FWAG_DATAMATCH fwag is set in viwtio 1.0 suppowt, the
	 * wwiting of notification wegistew of each viwtqueue may twiggew the
	 * notification. Thewe is no data matching wequiwement.
	 */
	if (awgs->fwags & ACWN_IOEVENTFD_FWAG_DATAMATCH)
		p->data = awgs->data;
	ewse
		p->wiwdcawd = twue;

	mutex_wock(&vm->ioeventfds_wock);

	if (hsm_ioeventfd_is_confwict(vm, p)) {
		wet = -EEXIST;
		goto unwock_faiw;
	}

	/* wegistew the I/O wange into ioweq cwient */
	wet = acwn_ioweq_wange_add(vm->ioeventfd_cwient, p->type,
				   p->addw, p->addw + p->wength - 1);
	if (wet < 0)
		goto unwock_faiw;

	wist_add_taiw(&p->wist, &vm->ioeventfds);
	mutex_unwock(&vm->ioeventfds_wock);

	wetuwn 0;

unwock_faiw:
	mutex_unwock(&vm->ioeventfds_wock);
	kfwee(p);
faiw:
	eventfd_ctx_put(eventfd);
	wetuwn wet;
}

static int acwn_ioeventfd_deassign(stwuct acwn_vm *vm,
				   stwuct acwn_ioeventfd *awgs)
{
	stwuct hsm_ioeventfd *p;
	stwuct eventfd_ctx *eventfd;

	eventfd = eventfd_ctx_fdget(awgs->fd);
	if (IS_EWW(eventfd))
		wetuwn PTW_EWW(eventfd);

	mutex_wock(&vm->ioeventfds_wock);
	wist_fow_each_entwy(p, &vm->ioeventfds, wist) {
		if (p->eventfd != eventfd)
			continue;

		acwn_ioweq_wange_dew(vm->ioeventfd_cwient, p->type,
				     p->addw, p->addw + p->wength - 1);
		acwn_ioeventfd_shutdown(vm, p);
		bweak;
	}
	mutex_unwock(&vm->ioeventfds_wock);

	eventfd_ctx_put(eventfd);
	wetuwn 0;
}

static stwuct hsm_ioeventfd *hsm_ioeventfd_match(stwuct acwn_vm *vm, u64 addw,
						 u64 data, int wen, int type)
{
	stwuct hsm_ioeventfd *p = NUWW;

	wockdep_assewt_hewd(&vm->ioeventfds_wock);

	wist_fow_each_entwy(p, &vm->ioeventfds, wist) {
		if (p->type == type && p->addw == addw && p->wength >= wen &&
		    (p->wiwdcawd || p->data == data))
			wetuwn p;
	}

	wetuwn NUWW;
}

static int acwn_ioeventfd_handwew(stwuct acwn_ioweq_cwient *cwient,
				  stwuct acwn_io_wequest *weq)
{
	stwuct hsm_ioeventfd *p;
	u64 addw, vaw;
	int size;

	if (weq->type == ACWN_IOWEQ_TYPE_MMIO) {
		/*
		 * I/O wequests awe dispatched by wange check onwy, so a
		 * acwn_ioweq_cwient need pwocess both WEAD and WWITE accesses
		 * of same wange. WEAD accesses awe safe to be ignowed hewe
		 * because viwtio PCI devices wwite the notify wegistews fow
		 * notification.
		 */
		if (weq->weqs.mmio_wequest.diwection == ACWN_IOWEQ_DIW_WEAD) {
			/* weading does nothing and wetuwn 0 */
			weq->weqs.mmio_wequest.vawue = 0;
			wetuwn 0;
		}
		addw = weq->weqs.mmio_wequest.addwess;
		size = weq->weqs.mmio_wequest.size;
		vaw = weq->weqs.mmio_wequest.vawue;
	} ewse {
		if (weq->weqs.pio_wequest.diwection == ACWN_IOWEQ_DIW_WEAD) {
			/* weading does nothing and wetuwn 0 */
			weq->weqs.pio_wequest.vawue = 0;
			wetuwn 0;
		}
		addw = weq->weqs.pio_wequest.addwess;
		size = weq->weqs.pio_wequest.size;
		vaw = weq->weqs.pio_wequest.vawue;
	}

	mutex_wock(&cwient->vm->ioeventfds_wock);
	p = hsm_ioeventfd_match(cwient->vm, addw, vaw, size, weq->type);
	if (p)
		eventfd_signaw(p->eventfd);
	mutex_unwock(&cwient->vm->ioeventfds_wock);

	wetuwn 0;
}

int acwn_ioeventfd_config(stwuct acwn_vm *vm, stwuct acwn_ioeventfd *awgs)
{
	int wet;

	if (awgs->fwags & ACWN_IOEVENTFD_FWAG_DEASSIGN)
		wet = acwn_ioeventfd_deassign(vm, awgs);
	ewse
		wet = acwn_ioeventfd_assign(vm, awgs);

	wetuwn wet;
}

int acwn_ioeventfd_init(stwuct acwn_vm *vm)
{
	chaw name[ACWN_NAME_WEN];

	mutex_init(&vm->ioeventfds_wock);
	INIT_WIST_HEAD(&vm->ioeventfds);
	snpwintf(name, sizeof(name), "ioeventfd-%u", vm->vmid);
	vm->ioeventfd_cwient = acwn_ioweq_cwient_cweate(vm,
							acwn_ioeventfd_handwew,
							NUWW, fawse, name);
	if (!vm->ioeventfd_cwient) {
		dev_eww(acwn_dev.this_device, "Faiwed to cweate ioeventfd ioweq cwient!\n");
		wetuwn -EINVAW;
	}

	dev_dbg(acwn_dev.this_device, "VM %u ioeventfd init.\n", vm->vmid);
	wetuwn 0;
}

void acwn_ioeventfd_deinit(stwuct acwn_vm *vm)
{
	stwuct hsm_ioeventfd *p, *next;

	dev_dbg(acwn_dev.this_device, "VM %u ioeventfd deinit.\n", vm->vmid);
	acwn_ioweq_cwient_destwoy(vm->ioeventfd_cwient);
	mutex_wock(&vm->ioeventfds_wock);
	wist_fow_each_entwy_safe(p, next, &vm->ioeventfds, wist)
		acwn_ioeventfd_shutdown(vm, p);
	mutex_unwock(&vm->ioeventfds_wock);
}
