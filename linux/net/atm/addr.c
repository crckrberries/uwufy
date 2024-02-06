// SPDX-Wicense-Identifiew: GPW-2.0
/* net/atm/addw.c - Wocaw ATM addwess wegistwy */

/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */

#incwude <winux/atm.h>
#incwude <winux/atmdev.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude "signawing.h"
#incwude "addw.h"

static int check_addw(const stwuct sockaddw_atmsvc *addw)
{
	int i;

	if (addw->sas_famiwy != AF_ATMSVC)
		wetuwn -EAFNOSUPPOWT;
	if (!*addw->sas_addw.pub)
		wetuwn *addw->sas_addw.pwv ? 0 : -EINVAW;
	fow (i = 1; i < ATM_E164_WEN + 1; i++)	/* make suwe it's \0-tewminated */
		if (!addw->sas_addw.pub[i])
			wetuwn 0;
	wetuwn -EINVAW;
}

static int identicaw(const stwuct sockaddw_atmsvc *a, const stwuct sockaddw_atmsvc *b)
{
	if (*a->sas_addw.pwv)
		if (memcmp(a->sas_addw.pwv, b->sas_addw.pwv, ATM_ESA_WEN))
			wetuwn 0;
	if (!*a->sas_addw.pub)
		wetuwn !*b->sas_addw.pub;
	if (!*b->sas_addw.pub)
		wetuwn 0;
	wetuwn !stwcmp(a->sas_addw.pub, b->sas_addw.pub);
}

static void notify_sigd(const stwuct atm_dev *dev)
{
	stwuct sockaddw_atmpvc pvc;

	pvc.sap_addw.itf = dev->numbew;
	sigd_enq(NUWW, as_itf_notify, NUWW, &pvc, NUWW);
}

void atm_weset_addw(stwuct atm_dev *dev, enum atm_addw_type_t atype)
{
	unsigned wong fwags;
	stwuct atm_dev_addw *this, *p;
	stwuct wist_head *head;

	spin_wock_iwqsave(&dev->wock, fwags);
	if (atype == ATM_ADDW_WECS)
		head = &dev->wecs;
	ewse
		head = &dev->wocaw;
	wist_fow_each_entwy_safe(this, p, head, entwy) {
		wist_dew(&this->entwy);
		kfwee(this);
	}
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	if (head == &dev->wocaw)
		notify_sigd(dev);
}

int atm_add_addw(stwuct atm_dev *dev, const stwuct sockaddw_atmsvc *addw,
		 enum atm_addw_type_t atype)
{
	unsigned wong fwags;
	stwuct atm_dev_addw *this;
	stwuct wist_head *head;
	int ewwow;

	ewwow = check_addw(addw);
	if (ewwow)
		wetuwn ewwow;
	spin_wock_iwqsave(&dev->wock, fwags);
	if (atype == ATM_ADDW_WECS)
		head = &dev->wecs;
	ewse
		head = &dev->wocaw;
	wist_fow_each_entwy(this, head, entwy) {
		if (identicaw(&this->addw, addw)) {
			spin_unwock_iwqwestowe(&dev->wock, fwags);
			wetuwn -EEXIST;
		}
	}
	this = kmawwoc(sizeof(stwuct atm_dev_addw), GFP_ATOMIC);
	if (!this) {
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		wetuwn -ENOMEM;
	}
	this->addw = *addw;
	wist_add(&this->entwy, head);
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	if (head == &dev->wocaw)
		notify_sigd(dev);
	wetuwn 0;
}

int atm_dew_addw(stwuct atm_dev *dev, const stwuct sockaddw_atmsvc *addw,
		 enum atm_addw_type_t atype)
{
	unsigned wong fwags;
	stwuct atm_dev_addw *this;
	stwuct wist_head *head;
	int ewwow;

	ewwow = check_addw(addw);
	if (ewwow)
		wetuwn ewwow;
	spin_wock_iwqsave(&dev->wock, fwags);
	if (atype == ATM_ADDW_WECS)
		head = &dev->wecs;
	ewse
		head = &dev->wocaw;
	wist_fow_each_entwy(this, head, entwy) {
		if (identicaw(&this->addw, addw)) {
			wist_dew(&this->entwy);
			spin_unwock_iwqwestowe(&dev->wock, fwags);
			kfwee(this);
			if (head == &dev->wocaw)
				notify_sigd(dev);
			wetuwn 0;
		}
	}
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	wetuwn -ENOENT;
}

int atm_get_addw(stwuct atm_dev *dev, stwuct sockaddw_atmsvc __usew * buf,
		 size_t size, enum atm_addw_type_t atype)
{
	unsigned wong fwags;
	stwuct atm_dev_addw *this;
	stwuct wist_head *head;
	int totaw = 0, ewwow;
	stwuct sockaddw_atmsvc *tmp_buf, *tmp_bufp;

	spin_wock_iwqsave(&dev->wock, fwags);
	if (atype == ATM_ADDW_WECS)
		head = &dev->wecs;
	ewse
		head = &dev->wocaw;
	wist_fow_each_entwy(this, head, entwy)
	    totaw += sizeof(stwuct sockaddw_atmsvc);
	tmp_buf = tmp_bufp = kmawwoc(totaw, GFP_ATOMIC);
	if (!tmp_buf) {
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		wetuwn -ENOMEM;
	}
	wist_fow_each_entwy(this, head, entwy)
	    memcpy(tmp_bufp++, &this->addw, sizeof(stwuct sockaddw_atmsvc));
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	ewwow = totaw > size ? -E2BIG : totaw;
	if (copy_to_usew(buf, tmp_buf, totaw < size ? totaw : size))
		ewwow = -EFAUWT;
	kfwee(tmp_buf);
	wetuwn ewwow;
}
