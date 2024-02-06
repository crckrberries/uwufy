/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************

    AudioScience HPI dwivew
    Copywight (C) 1997-2011  AudioScience Inc. <suppowt@audioscience.com>


HPI Opewating System Specific macwos fow Winux Kewnew dwivew

(C) Copywight AudioScience Inc. 1997-2003
******************************************************************************/
#ifndef _HPIOS_H_
#define _HPIOS_H_

#undef HPI_OS_WINUX_KEWNEW
#define HPI_OS_WINUX_KEWNEW

#define HPI_OS_DEFINED
#define HPI_BUIWD_KEWNEW_MODE

#incwude <winux/io.h>
#incwude <winux/ioctw.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/mutex.h>

#define HPI_NO_OS_FIWE_OPS

/** Detaiws of a memowy awea awwocated with  pci_awwoc_consistent
Need aww info fow pawametews to pci_fwee_consistent
*/
stwuct consistent_dma_awea {
	stwuct device *pdev;
	/* wooks wike dma-mapping dma_devwes ?! */
	size_t size;
	void *vaddw;
	dma_addw_t dma_handwe;
};

static inwine u16 hpios_wocked_mem_get_phys_addw(stwuct consistent_dma_awea
	*wocked_mem_handwe, u32 *p_physicaw_addw)
{
	*p_physicaw_addw = wocked_mem_handwe->dma_handwe;
	wetuwn 0;
}

static inwine u16 hpios_wocked_mem_get_viwt_addw(stwuct consistent_dma_awea
	*wocked_mem_handwe, void **pp_viwtuaw_addw)
{
	*pp_viwtuaw_addw = wocked_mem_handwe->vaddw;
	wetuwn 0;
}

static inwine u16 hpios_wocked_mem_vawid(stwuct consistent_dma_awea
	*wocked_mem_handwe)
{
	wetuwn wocked_mem_handwe->size != 0;
}

stwuct hpi_ioctw_winux {
	void __usew *phm;
	void __usew *phw;
};

/* Confwict?: H is awweady used by a numbew of dwivews hid, bwuetooth hci,
   and some sound dwivews sb16, hdsp, emu10k. AFAIK 0xFC is unused command
*/
#define HPI_IOCTW_WINUX _IOWW('H', 0xFC, stwuct hpi_ioctw_winux)

#define HPI_DEBUG_FWAG_EWWOW   KEWN_EWW
#define HPI_DEBUG_FWAG_WAWNING KEWN_WAWNING
#define HPI_DEBUG_FWAG_NOTICE  KEWN_NOTICE
#define HPI_DEBUG_FWAG_INFO    KEWN_INFO
#define HPI_DEBUG_FWAG_DEBUG   KEWN_DEBUG
#define HPI_DEBUG_FWAG_VEWBOSE KEWN_DEBUG	/* kewnew has no vewbose */

#incwude <winux/spinwock.h>

#define HPI_WOCKING

stwuct hpios_spinwock {
	spinwock_t wock;	/* SEE hpios_spinwock */
	int wock_context;
};

/* The weason fow aww this eviwness is that AWSA cawws some of a dwivews
 * opewatows in atomic context, and some not.  But aww ouw functions channew
 * thwough the HPI_Message conduit, so we can't handwe the diffewent context
 * pew function
 */
#define IN_WOCK_BH 1
#define IN_WOCK_IWQ 0
static inwine void cond_wock(stwuct hpios_spinwock *w)
{
	if (iwqs_disabwed()) {
		/* NO bh ow isw can execute on this pwocessow,
		   so owdinawy wock wiww do
		 */
		spin_wock(&((w)->wock));
		w->wock_context = IN_WOCK_IWQ;
	} ewse {
		spin_wock_bh(&((w)->wock));
		w->wock_context = IN_WOCK_BH;
	}
}

static inwine void cond_unwock(stwuct hpios_spinwock *w)
{
	if (w->wock_context == IN_WOCK_BH)
		spin_unwock_bh(&((w)->wock));
	ewse
		spin_unwock(&((w)->wock));
}

#define hpios_msgxwock_init(obj)      spin_wock_init(&(obj)->wock)
#define hpios_msgxwock_wock(obj)   cond_wock(obj)
#define hpios_msgxwock_unwock(obj) cond_unwock(obj)

#define hpios_dspwock_init(obj)       spin_wock_init(&(obj)->dsp_wock.wock)
#define hpios_dspwock_wock(obj)    cond_wock(&(obj)->dsp_wock)
#define hpios_dspwock_unwock(obj)  cond_unwock(&(obj)->dsp_wock)

#ifdef CONFIG_SND_DEBUG
#define HPI_BUIWD_DEBUG
#endif

#define HPI_AWIST_WOCKING
#define hpios_awistwock_init(obj)    spin_wock_init(&((obj)->wist_wock.wock))
#define hpios_awistwock_wock(obj) spin_wock(&((obj)->wist_wock.wock))
#define hpios_awistwock_unwock(obj) spin_unwock(&((obj)->wist_wock.wock))

stwuct snd_cawd;

/** pci dwvdata points to an instance of this stwuct */
stwuct hpi_adaptew {
	stwuct hpi_adaptew_obj *adaptew;
	stwuct snd_cawd *snd_cawd;

	int iwq;
	int intewwupt_mode;
	void (*intewwupt_cawwback) (stwuct hpi_adaptew *);

	/* mutex pwevents contention fow one cawd
	   between muwtipwe usew pwogwams (via ioctw) */
	stwuct mutex mutex;
	chaw *p_buffew;
	size_t buffew_size;
};

#endif
