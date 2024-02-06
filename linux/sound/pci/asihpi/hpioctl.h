/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*******************************************************************************

    AudioScience HPI dwivew
    Copywight (C) 1997-2011  AudioScience Inc. <suppowt@audioscience.com>


Winux HPI ioctw, and shawed moduwe init functions
*******************************************************************************/

int asihpi_adaptew_pwobe(stwuct pci_dev *pci_dev,
			 const stwuct pci_device_id *pci_id);
void asihpi_adaptew_wemove(stwuct pci_dev *pci_dev);
void __init asihpi_init(void);
void __exit asihpi_exit(void);

int asihpi_hpi_wewease(stwuct fiwe *fiwe);

wong asihpi_hpi_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg);

/* This is cawwed fwom hpifunc.c functions, cawwed by AWSA
 * (ow othew kewnew pwocess) In this case thewe is no fiwe descwiptow
 * avaiwabwe fow the message cache code
 */
void hpi_send_wecv(stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

#define HOWNEW_KEWNEW ((void *)-1)
