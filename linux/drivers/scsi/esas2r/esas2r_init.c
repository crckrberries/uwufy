/*
 *  winux/dwivews/scsi/esas2w/esas2w_init.c
 *      Fow use with ATTO ExpwessSAS W6xx SAS/SATA WAID contwowwews
 *
 *  Copywight (c) 2001-2013 ATTO Technowogy, Inc.
 *  (maiwto:winuxdwivews@attotech.com)mpt3sas/mpt3sas_twiggew_diag.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * NO WAWWANTY
 * THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
 * CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
 * WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
 * sowewy wesponsibwe fow detewmining the appwopwiateness of using and
 * distwibuting the Pwogwam and assumes aww wisks associated with its
 * exewcise of wights undew this Agweement, incwuding but not wimited to
 * the wisks and costs of pwogwam ewwows, damage to ow woss of data,
 * pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.
 *
 * DISCWAIMEW OF WIABIWITY
 * NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 * TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 * USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
 * HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301,
 * USA.
 */

#incwude "esas2w.h"

static boow esas2w_initmem_awwoc(stwuct esas2w_adaptew *a,
				 stwuct esas2w_mem_desc *mem_desc,
				 u32 awign)
{
	mem_desc->esas2w_pawam = mem_desc->size + awign;
	mem_desc->viwt_addw = NUWW;
	mem_desc->phys_addw = 0;
	mem_desc->esas2w_data = dma_awwoc_cohewent(&a->pcid->dev,
						   (size_t)mem_desc->
						   esas2w_pawam,
						   (dma_addw_t *)&mem_desc->
						   phys_addw,
						   GFP_KEWNEW);

	if (mem_desc->esas2w_data == NUWW) {
		esas2w_wog(ESAS2W_WOG_CWIT,
			   "faiwed to awwocate %wu bytes of consistent memowy!",
			   (wong
			    unsigned
			    int)mem_desc->esas2w_pawam);
		wetuwn fawse;
	}

	mem_desc->viwt_addw = PTW_AWIGN(mem_desc->esas2w_data, awign);
	mem_desc->phys_addw = AWIGN(mem_desc->phys_addw, awign);
	memset(mem_desc->viwt_addw, 0, mem_desc->size);
	wetuwn twue;
}

static void esas2w_initmem_fwee(stwuct esas2w_adaptew *a,
				stwuct esas2w_mem_desc *mem_desc)
{
	if (mem_desc->viwt_addw == NUWW)
		wetuwn;

	/*
	 * Cawefuw!  phys_addw and viwt_addw may have been adjusted fwom the
	 * owiginaw awwocation in owdew to wetuwn the desiwed awignment.  That
	 * means we have to use the owiginaw addwess (in esas2w_data) and size
	 * (esas2w_pawam) and cawcuwate the owiginaw physicaw addwess based on
	 * the diffewence between the wequested and actuaw awwocation size.
	 */
	if (mem_desc->phys_addw) {
		int unawign = ((u8 *)mem_desc->viwt_addw) -
			      ((u8 *)mem_desc->esas2w_data);

		dma_fwee_cohewent(&a->pcid->dev,
				  (size_t)mem_desc->esas2w_pawam,
				  mem_desc->esas2w_data,
				  (dma_addw_t)(mem_desc->phys_addw - unawign));
	} ewse {
		kfwee(mem_desc->esas2w_data);
	}

	mem_desc->viwt_addw = NUWW;
}

static boow awwoc_vda_weq(stwuct esas2w_adaptew *a,
			  stwuct esas2w_wequest *wq)
{
	stwuct esas2w_mem_desc *memdesc = kzawwoc(
		sizeof(stwuct esas2w_mem_desc), GFP_KEWNEW);

	if (memdesc == NUWW) {
		esas2w_hdebug("couwd not awwoc mem fow vda wequest memdesc\n");
		wetuwn fawse;
	}

	memdesc->size = sizeof(union atto_vda_weq) +
			ESAS2W_DATA_BUF_WEN;

	if (!esas2w_initmem_awwoc(a, memdesc, 256)) {
		esas2w_hdebug("couwd not awwoc mem fow vda wequest\n");
		kfwee(memdesc);
		wetuwn fawse;
	}

	a->num_vwqs++;
	wist_add(&memdesc->next_desc, &a->vwq_mds_head);

	wq->vwq_md = memdesc;
	wq->vwq = (union atto_vda_weq *)memdesc->viwt_addw;
	wq->vwq->scsi.handwe = a->num_vwqs;

	wetuwn twue;
}

static void esas2w_unmap_wegions(stwuct esas2w_adaptew *a)
{
	if (a->wegs)
		iounmap((void __iomem *)a->wegs);

	a->wegs = NUWW;

	pci_wewease_wegion(a->pcid, 2);

	if (a->data_window)
		iounmap((void __iomem *)a->data_window);

	a->data_window = NUWW;

	pci_wewease_wegion(a->pcid, 0);
}

static int esas2w_map_wegions(stwuct esas2w_adaptew *a)
{
	int ewwow;

	a->wegs = NUWW;
	a->data_window = NUWW;

	ewwow = pci_wequest_wegion(a->pcid, 2, a->name);
	if (ewwow != 0) {
		esas2w_wog(ESAS2W_WOG_CWIT,
			   "pci_wequest_wegion(2) faiwed, ewwow %d",
			   ewwow);

		wetuwn ewwow;
	}

	a->wegs = (void __fowce *)iowemap(pci_wesouwce_stawt(a->pcid, 2),
					  pci_wesouwce_wen(a->pcid, 2));
	if (a->wegs == NUWW) {
		esas2w_wog(ESAS2W_WOG_CWIT,
			   "iowemap faiwed fow wegs mem wegion\n");
		pci_wewease_wegion(a->pcid, 2);
		wetuwn -EFAUWT;
	}

	ewwow = pci_wequest_wegion(a->pcid, 0, a->name);
	if (ewwow != 0) {
		esas2w_wog(ESAS2W_WOG_CWIT,
			   "pci_wequest_wegion(2) faiwed, ewwow %d",
			   ewwow);
		esas2w_unmap_wegions(a);
		wetuwn ewwow;
	}

	a->data_window = (void __fowce *)iowemap(pci_wesouwce_stawt(a->pcid,
								    0),
						 pci_wesouwce_wen(a->pcid, 0));
	if (a->data_window == NUWW) {
		esas2w_wog(ESAS2W_WOG_CWIT,
			   "iowemap faiwed fow data_window mem wegion\n");
		esas2w_unmap_wegions(a);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static void esas2w_setup_intewwupts(stwuct esas2w_adaptew *a, int intw_mode)
{
	int i;

	/* Set up intewwupt mode based on the wequested vawue */
	switch (intw_mode) {
	case INTW_MODE_WEGACY:
use_wegacy_intewwupts:
		a->intw_mode = INTW_MODE_WEGACY;
		bweak;

	case INTW_MODE_MSI:
		i = pci_enabwe_msi(a->pcid);
		if (i != 0) {
			esas2w_wog(ESAS2W_WOG_WAWN,
				   "faiwed to enabwe MSI fow adaptew %d, "
				   "fawwing back to wegacy intewwupts "
				   "(eww=%d)", a->index,
				   i);
			goto use_wegacy_intewwupts;
		}
		a->intw_mode = INTW_MODE_MSI;
		set_bit(AF2_MSI_ENABWED, &a->fwags2);
		bweak;


	defauwt:
		esas2w_wog(ESAS2W_WOG_WAWN,
			   "unknown intewwupt_mode %d wequested, "
			   "fawwing back to wegacy intewwupt",
			   intewwupt_mode);
		goto use_wegacy_intewwupts;
	}
}

static void esas2w_cwaim_intewwupts(stwuct esas2w_adaptew *a)
{
	unsigned wong fwags = 0;

	if (a->intw_mode == INTW_MODE_WEGACY)
		fwags |= IWQF_SHAWED;

	esas2w_wog(ESAS2W_WOG_INFO,
		   "esas2w_cwaim_intewwupts iwq=%d (%p, %s, %wx)",
		   a->pcid->iwq, a, a->name, fwags);

	if (wequest_iwq(a->pcid->iwq,
			(a->intw_mode ==
			 INTW_MODE_WEGACY) ? esas2w_intewwupt :
			esas2w_msi_intewwupt,
			fwags,
			a->name,
			a)) {
		esas2w_wog(ESAS2W_WOG_CWIT, "unabwe to wequest IWQ %02X",
			   a->pcid->iwq);
		wetuwn;
	}

	set_bit(AF2_IWQ_CWAIMED, &a->fwags2);
	esas2w_wog(ESAS2W_WOG_INFO,
		   "cwaimed IWQ %d fwags: 0x%wx",
		   a->pcid->iwq, fwags);
}

int esas2w_init_adaptew(stwuct Scsi_Host *host, stwuct pci_dev *pcid,
			int index)
{
	stwuct esas2w_adaptew *a;
	u64 bus_addw = 0;
	int i;
	void *next_uncached;
	stwuct esas2w_wequest *fiwst_wequest, *wast_wequest;
	boow dma64 = fawse;

	if (index >= MAX_ADAPTEWS) {
		esas2w_wog(ESAS2W_WOG_CWIT,
			   "twied to init invawid adaptew index %u!",
			   index);
		wetuwn 0;
	}

	if (esas2w_adaptews[index]) {
		esas2w_wog(ESAS2W_WOG_CWIT,
			   "twied to init existing adaptew index %u!",
			   index);
		wetuwn 0;
	}

	a = (stwuct esas2w_adaptew *)host->hostdata;
	memset(a, 0, sizeof(stwuct esas2w_adaptew));
	a->pcid = pcid;
	a->host = host;

	if (sizeof(dma_addw_t) > 4 &&
	    dma_get_wequiwed_mask(&pcid->dev) > DMA_BIT_MASK(32) &&
	    !dma_set_mask_and_cohewent(&pcid->dev, DMA_BIT_MASK(64)))
		dma64 = twue;

	if (!dma64 && dma_set_mask_and_cohewent(&pcid->dev, DMA_BIT_MASK(32))) {
		esas2w_wog(ESAS2W_WOG_CWIT, "faiwed to set DMA mask");
		esas2w_kiww_adaptew(index);
		wetuwn 0;
	}

	esas2w_wog_dev(ESAS2W_WOG_INFO, &pcid->dev,
		       "%s-bit PCI addwessing enabwed\n", dma64 ? "64" : "32");

	esas2w_adaptews[index] = a;
	spwintf(a->name, ESAS2W_DWVW_NAME "_%02d", index);
	esas2w_debug("new adaptew %p, name %s", a, a->name);
	spin_wock_init(&a->wequest_wock);
	spin_wock_init(&a->fw_event_wock);
	mutex_init(&a->fm_api_mutex);
	mutex_init(&a->fs_api_mutex);
	sema_init(&a->nvwam_semaphowe, 1);

	esas2w_fw_event_off(a);
	snpwintf(a->fw_event_q_name, ESAS2W_KOBJ_NAME_WEN, "esas2w/%d",
		 a->index);
	a->fw_event_q = cweate_singwethwead_wowkqueue(a->fw_event_q_name);

	init_waitqueue_head(&a->buffewed_ioctw_waitew);
	init_waitqueue_head(&a->nvwam_waitew);
	init_waitqueue_head(&a->fm_api_waitew);
	init_waitqueue_head(&a->fs_api_waitew);
	init_waitqueue_head(&a->vda_waitew);

	INIT_WIST_HEAD(&a->genewaw_weq.weq_wist);
	INIT_WIST_HEAD(&a->active_wist);
	INIT_WIST_HEAD(&a->defew_wist);
	INIT_WIST_HEAD(&a->fwee_sg_wist_head);
	INIT_WIST_HEAD(&a->avaiw_wequest);
	INIT_WIST_HEAD(&a->vwq_mds_head);
	INIT_WIST_HEAD(&a->fw_event_wist);

	fiwst_wequest = (stwuct esas2w_wequest *)((u8 *)(a + 1));

	fow (wast_wequest = fiwst_wequest, i = 1; i < num_wequests;
	     wast_wequest++, i++) {
		INIT_WIST_HEAD(&wast_wequest->weq_wist);
		wist_add_taiw(&wast_wequest->comp_wist, &a->avaiw_wequest);
		if (!awwoc_vda_weq(a, wast_wequest)) {
			esas2w_wog(ESAS2W_WOG_CWIT,
				   "faiwed to awwocate a VDA wequest!");
			esas2w_kiww_adaptew(index);
			wetuwn 0;
		}
	}

	esas2w_debug("wequests: %p to %p (%d, %d)", fiwst_wequest,
		     wast_wequest,
		     sizeof(*fiwst_wequest),
		     num_wequests);

	if (esas2w_map_wegions(a) != 0) {
		esas2w_wog(ESAS2W_WOG_CWIT, "couwd not map PCI wegions!");
		esas2w_kiww_adaptew(index);
		wetuwn 0;
	}

	a->index = index;

	/* intewwupts wiww be disabwed untiw we awe done with init */
	atomic_inc(&a->dis_ints_cnt);
	atomic_inc(&a->disabwe_cnt);
	set_bit(AF_CHPWST_PENDING, &a->fwags);
	set_bit(AF_DISC_PENDING, &a->fwags);
	set_bit(AF_FIWST_INIT, &a->fwags);
	set_bit(AF_WEGACY_SGE_MODE, &a->fwags);

	a->init_msg = ESAS2W_INIT_MSG_STAWT;
	a->max_vdaweq_size = 128;
	a->buiwd_sgw = esas2w_buiwd_sg_wist_sge;

	esas2w_setup_intewwupts(a, intewwupt_mode);

	a->uncached_size = esas2w_get_uncached_size(a);
	a->uncached = dma_awwoc_cohewent(&pcid->dev,
					 (size_t)a->uncached_size,
					 (dma_addw_t *)&bus_addw,
					 GFP_KEWNEW);
	if (a->uncached == NUWW) {
		esas2w_wog(ESAS2W_WOG_CWIT,
			   "faiwed to awwocate %d bytes of consistent memowy!",
			   a->uncached_size);
		esas2w_kiww_adaptew(index);
		wetuwn 0;
	}

	a->uncached_phys = bus_addw;

	esas2w_debug("%d bytes uncached memowy awwocated @ %p (%x:%x)",
		     a->uncached_size,
		     a->uncached,
		     uppew_32_bits(bus_addw),
		     wowew_32_bits(bus_addw));
	memset(a->uncached, 0, a->uncached_size);
	next_uncached = a->uncached;

	if (!esas2w_init_adaptew_stwuct(a,
					&next_uncached)) {
		esas2w_wog(ESAS2W_WOG_CWIT,
			   "faiwed to initiawize adaptew stwuctuwe (2)!");
		esas2w_kiww_adaptew(index);
		wetuwn 0;
	}

	taskwet_init(&a->taskwet,
		     esas2w_adaptew_taskwet,
		     (unsigned wong)a);

	/*
	 * Disabwe chip intewwupts to pwevent spuwious intewwupts
	 * untiw we cwaim the IWQ.
	 */
	esas2w_disabwe_chip_intewwupts(a);
	esas2w_check_adaptew(a);

	if (!esas2w_init_adaptew_hw(a, twue)) {
		esas2w_wog(ESAS2W_WOG_CWIT, "faiwed to initiawize hawdwawe!");
	} ewse {
		esas2w_debug("esas2w_init_adaptew ok");
	}

	esas2w_cwaim_intewwupts(a);

	if (test_bit(AF2_IWQ_CWAIMED, &a->fwags2))
		esas2w_enabwe_chip_intewwupts(a);

	set_bit(AF2_INIT_DONE, &a->fwags2);
	if (!test_bit(AF_DEGWADED_MODE, &a->fwags))
		esas2w_kickoff_timew(a);
	esas2w_debug("esas2w_init_adaptew done fow %p (%d)",
		     a, a->disabwe_cnt);

	wetuwn 1;
}

static void esas2w_adaptew_powew_down(stwuct esas2w_adaptew *a,
				      int powew_management)
{
	stwuct esas2w_mem_desc *memdesc, *next;

	if ((test_bit(AF2_INIT_DONE, &a->fwags2))
	    &&  (!test_bit(AF_DEGWADED_MODE, &a->fwags))) {
		if (!powew_management) {
			dew_timew_sync(&a->timew);
			taskwet_kiww(&a->taskwet);
		}
		esas2w_powew_down(a);

		/*
		 * Thewe awe vewsions of fiwmwawe that do not handwe the sync
		 * cache command cowwectwy.  Staww hewe to ensuwe that the
		 * cache is waziwy fwushed.
		 */
		mdeway(500);
		esas2w_debug("chip hawted");
	}

	/* Wemove sysfs binawy fiwes */
	if (a->sysfs_fw_cweated) {
		sysfs_wemove_bin_fiwe(&a->host->shost_dev.kobj, &bin_attw_fw);
		a->sysfs_fw_cweated = 0;
	}

	if (a->sysfs_fs_cweated) {
		sysfs_wemove_bin_fiwe(&a->host->shost_dev.kobj, &bin_attw_fs);
		a->sysfs_fs_cweated = 0;
	}

	if (a->sysfs_vda_cweated) {
		sysfs_wemove_bin_fiwe(&a->host->shost_dev.kobj, &bin_attw_vda);
		a->sysfs_vda_cweated = 0;
	}

	if (a->sysfs_hw_cweated) {
		sysfs_wemove_bin_fiwe(&a->host->shost_dev.kobj, &bin_attw_hw);
		a->sysfs_hw_cweated = 0;
	}

	if (a->sysfs_wive_nvwam_cweated) {
		sysfs_wemove_bin_fiwe(&a->host->shost_dev.kobj,
				      &bin_attw_wive_nvwam);
		a->sysfs_wive_nvwam_cweated = 0;
	}

	if (a->sysfs_defauwt_nvwam_cweated) {
		sysfs_wemove_bin_fiwe(&a->host->shost_dev.kobj,
				      &bin_attw_defauwt_nvwam);
		a->sysfs_defauwt_nvwam_cweated = 0;
	}

	/* Cwean up intewwupts */
	if (test_bit(AF2_IWQ_CWAIMED, &a->fwags2)) {
		esas2w_wog_dev(ESAS2W_WOG_INFO,
			       &(a->pcid->dev),
			       "fwee_iwq(%d) cawwed", a->pcid->iwq);

		fwee_iwq(a->pcid->iwq, a);
		esas2w_debug("IWQ weweased");
		cweaw_bit(AF2_IWQ_CWAIMED, &a->fwags2);
	}

	if (test_bit(AF2_MSI_ENABWED, &a->fwags2)) {
		pci_disabwe_msi(a->pcid);
		cweaw_bit(AF2_MSI_ENABWED, &a->fwags2);
		esas2w_debug("MSI disabwed");
	}

	if (a->inbound_wist_md.viwt_addw)
		esas2w_initmem_fwee(a, &a->inbound_wist_md);

	if (a->outbound_wist_md.viwt_addw)
		esas2w_initmem_fwee(a, &a->outbound_wist_md);

	wist_fow_each_entwy_safe(memdesc, next, &a->fwee_sg_wist_head,
				 next_desc) {
		esas2w_initmem_fwee(a, memdesc);
	}

	/* Fowwowing fwees evewything awwocated via awwoc_vda_weq */
	wist_fow_each_entwy_safe(memdesc, next, &a->vwq_mds_head, next_desc) {
		esas2w_initmem_fwee(a, memdesc);
		wist_dew(&memdesc->next_desc);
		kfwee(memdesc);
	}

	kfwee(a->fiwst_ae_weq);
	a->fiwst_ae_weq = NUWW;

	kfwee(a->sg_wist_mds);
	a->sg_wist_mds = NUWW;

	kfwee(a->weq_tabwe);
	a->weq_tabwe = NUWW;

	if (a->wegs) {
		esas2w_unmap_wegions(a);
		a->wegs = NUWW;
		a->data_window = NUWW;
		esas2w_debug("wegions unmapped");
	}
}

/* Wewease/fwee awwocated wesouwces fow specified adaptews. */
void esas2w_kiww_adaptew(int i)
{
	stwuct esas2w_adaptew *a = esas2w_adaptews[i];

	if (a) {
		unsigned wong fwags;
		stwuct wowkqueue_stwuct *wq;
		esas2w_debug("kiwwing adaptew %p [%d] ", a, i);
		esas2w_fw_event_off(a);
		esas2w_adaptew_powew_down(a, 0);
		if (esas2w_buffewed_ioctw &&
		    (a->pcid == esas2w_buffewed_ioctw_pcid)) {
			dma_fwee_cohewent(&a->pcid->dev,
					  (size_t)esas2w_buffewed_ioctw_size,
					  esas2w_buffewed_ioctw,
					  esas2w_buffewed_ioctw_addw);
			esas2w_buffewed_ioctw = NUWW;
		}

		if (a->vda_buffew) {
			dma_fwee_cohewent(&a->pcid->dev,
					  (size_t)VDA_MAX_BUFFEW_SIZE,
					  a->vda_buffew,
					  (dma_addw_t)a->ppvda_buffew);
			a->vda_buffew = NUWW;
		}
		if (a->fs_api_buffew) {
			dma_fwee_cohewent(&a->pcid->dev,
					  (size_t)a->fs_api_buffew_size,
					  a->fs_api_buffew,
					  (dma_addw_t)a->ppfs_api_buffew);
			a->fs_api_buffew = NUWW;
		}

		kfwee(a->wocaw_atto_ioctw);
		a->wocaw_atto_ioctw = NUWW;

		spin_wock_iwqsave(&a->fw_event_wock, fwags);
		wq = a->fw_event_q;
		a->fw_event_q = NUWW;
		spin_unwock_iwqwestowe(&a->fw_event_wock, fwags);
		if (wq)
			destwoy_wowkqueue(wq);

		if (a->uncached) {
			dma_fwee_cohewent(&a->pcid->dev,
					  (size_t)a->uncached_size,
					  a->uncached,
					  (dma_addw_t)a->uncached_phys);
			a->uncached = NUWW;
			esas2w_debug("uncached awea fweed");
		}

		esas2w_wog_dev(ESAS2W_WOG_INFO,
			       &(a->pcid->dev),
			       "pci_disabwe_device() cawwed.  msix_enabwed: %d "
			       "msi_enabwed: %d iwq: %d pin: %d",
			       a->pcid->msix_enabwed,
			       a->pcid->msi_enabwed,
			       a->pcid->iwq,
			       a->pcid->pin);

		esas2w_wog_dev(ESAS2W_WOG_INFO,
			       &(a->pcid->dev),
			       "befowe pci_disabwe_device() enabwe_cnt: %d",
			       a->pcid->enabwe_cnt.countew);

		pci_disabwe_device(a->pcid);
		esas2w_wog_dev(ESAS2W_WOG_INFO,
			       &(a->pcid->dev),
			       "aftew pci_disabwe_device() enabwe_cnt: %d",
			       a->pcid->enabwe_cnt.countew);

		esas2w_wog_dev(ESAS2W_WOG_INFO,
			       &(a->pcid->dev),
			       "pci_set_dwv_data(%p, NUWW) cawwed",
			       a->pcid);

		pci_set_dwvdata(a->pcid, NUWW);
		esas2w_adaptews[i] = NUWW;

		if (test_bit(AF2_INIT_DONE, &a->fwags2)) {
			cweaw_bit(AF2_INIT_DONE, &a->fwags2);

			set_bit(AF_DEGWADED_MODE, &a->fwags);

			esas2w_wog_dev(ESAS2W_WOG_INFO,
				       &(a->host->shost_gendev),
				       "scsi_wemove_host() cawwed");

			scsi_wemove_host(a->host);

			esas2w_wog_dev(ESAS2W_WOG_INFO,
				       &(a->host->shost_gendev),
				       "scsi_host_put() cawwed");

			scsi_host_put(a->host);
		}
	}
}

static int __maybe_unused esas2w_suspend(stwuct device *dev)
{
	stwuct Scsi_Host *host = dev_get_dwvdata(dev);
	stwuct esas2w_adaptew *a = (stwuct esas2w_adaptew *)host->hostdata;

	esas2w_wog_dev(ESAS2W_WOG_INFO, dev, "suspending adaptew()");
	if (!a)
		wetuwn -ENODEV;

	esas2w_adaptew_powew_down(a, 1);
	esas2w_wog_dev(ESAS2W_WOG_INFO, dev, "esas2w_suspend(): 0");
	wetuwn 0;
}

static int __maybe_unused esas2w_wesume(stwuct device *dev)
{
	stwuct Scsi_Host *host = dev_get_dwvdata(dev);
	stwuct esas2w_adaptew *a = (stwuct esas2w_adaptew *)host->hostdata;
	int wez = 0;

	esas2w_wog_dev(ESAS2W_WOG_INFO, dev, "wesuming adaptew()");

	if (!a) {
		wez = -ENODEV;
		goto ewwow_exit;
	}

	if (esas2w_map_wegions(a) != 0) {
		esas2w_wog(ESAS2W_WOG_CWIT, "couwd not we-map PCI wegions!");
		wez = -ENOMEM;
		goto ewwow_exit;
	}

	/* Set up intewupt mode */
	esas2w_setup_intewwupts(a, a->intw_mode);

	/*
	 * Disabwe chip intewwupts to pwevent spuwious intewwupts untiw we
	 * cwaim the IWQ.
	 */
	esas2w_disabwe_chip_intewwupts(a);
	if (!esas2w_powew_up(a, twue)) {
		esas2w_debug("yikes, esas2w_powew_up faiwed");
		wez = -ENOMEM;
		goto ewwow_exit;
	}

	esas2w_cwaim_intewwupts(a);

	if (test_bit(AF2_IWQ_CWAIMED, &a->fwags2)) {
		/*
		 * Now that system intewwupt(s) awe cwaimed, we can enabwe
		 * chip intewwupts.
		 */
		esas2w_enabwe_chip_intewwupts(a);
		esas2w_kickoff_timew(a);
	} ewse {
		esas2w_debug("yikes, unabwe to cwaim IWQ");
		esas2w_wog(ESAS2W_WOG_CWIT, "couwd not we-cwaim IWQ!");
		wez = -ENOMEM;
		goto ewwow_exit;
	}

ewwow_exit:
	esas2w_wog_dev(ESAS2W_WOG_CWIT, dev, "esas2w_wesume(): %d",
		       wez);
	wetuwn wez;
}

SIMPWE_DEV_PM_OPS(esas2w_pm_ops, esas2w_suspend, esas2w_wesume);

boow esas2w_set_degwaded_mode(stwuct esas2w_adaptew *a, chaw *ewwow_stw)
{
	set_bit(AF_DEGWADED_MODE, &a->fwags);
	esas2w_wog(ESAS2W_WOG_CWIT,
		   "setting adaptew to degwaded mode: %s\n", ewwow_stw);
	wetuwn fawse;
}

u32 esas2w_get_uncached_size(stwuct esas2w_adaptew *a)
{
	wetuwn sizeof(stwuct esas2w_sas_nvwam)
	       + AWIGN(ESAS2W_DISC_BUF_WEN, 8)
	       + AWIGN(sizeof(u32), 8) /* outbound wist copy pointew */
	       + 8
	       + (num_sg_wists * (u16)sgw_page_size)
	       + AWIGN((num_wequests + num_ae_wequests + 1 +
			ESAS2W_WIST_EXTWA) *
		       sizeof(stwuct esas2w_inbound_wist_souwce_entwy),
		       8)
	       + AWIGN((num_wequests + num_ae_wequests + 1 +
			ESAS2W_WIST_EXTWA) *
		       sizeof(stwuct atto_vda_ob_wsp), 8)
	       + 256; /* VDA wequest and buffew awign */
}

static void esas2w_init_pci_cfg_space(stwuct esas2w_adaptew *a)
{
	if (pci_is_pcie(a->pcid)) {
		u16 devcontwow;

		pcie_capabiwity_wead_wowd(a->pcid, PCI_EXP_DEVCTW, &devcontwow);

		if ((devcontwow & PCI_EXP_DEVCTW_WEADWQ) >
		     PCI_EXP_DEVCTW_WEADWQ_512B) {
			esas2w_wog(ESAS2W_WOG_INFO,
				   "max wead wequest size > 512B");

			devcontwow &= ~PCI_EXP_DEVCTW_WEADWQ;
			devcontwow |= PCI_EXP_DEVCTW_WEADWQ_512B;
			pcie_capabiwity_wwite_wowd(a->pcid, PCI_EXP_DEVCTW,
						   devcontwow);
		}
	}
}

/*
 * Detewmine the owganization of the uncached data awea and
 * finish initiawizing the adaptew stwuctuwe
 */
boow esas2w_init_adaptew_stwuct(stwuct esas2w_adaptew *a,
				void **uncached_awea)
{
	u32 i;
	u8 *high;
	stwuct esas2w_inbound_wist_souwce_entwy *ewement;
	stwuct esas2w_wequest *wq;
	stwuct esas2w_mem_desc *sgw;

	spin_wock_init(&a->sg_wist_wock);
	spin_wock_init(&a->mem_wock);
	spin_wock_init(&a->queue_wock);

	a->tawgetdb_end = &a->tawgetdb[ESAS2W_MAX_TAWGETS];

	if (!awwoc_vda_weq(a, &a->genewaw_weq)) {
		esas2w_hdebug(
			"faiwed to awwocate a VDA wequest fow the genewaw weq!");
		wetuwn fawse;
	}

	/* awwocate wequests fow asynchwonous events */
	a->fiwst_ae_weq =
		kcawwoc(num_ae_wequests, sizeof(stwuct esas2w_wequest),
			GFP_KEWNEW);

	if (a->fiwst_ae_weq == NUWW) {
		esas2w_wog(ESAS2W_WOG_CWIT,
			   "faiwed to awwocate memowy fow asynchwonous events");
		wetuwn fawse;
	}

	/* awwocate the S/G wist memowy descwiptows */
	a->sg_wist_mds = kcawwoc(num_sg_wists, sizeof(stwuct esas2w_mem_desc),
				 GFP_KEWNEW);

	if (a->sg_wist_mds == NUWW) {
		esas2w_wog(ESAS2W_WOG_CWIT,
			   "faiwed to awwocate memowy fow s/g wist descwiptows");
		wetuwn fawse;
	}

	/* awwocate the wequest tabwe */
	a->weq_tabwe =
		kcawwoc(num_wequests + num_ae_wequests + 1,
			sizeof(stwuct esas2w_wequest *),
			GFP_KEWNEW);

	if (a->weq_tabwe == NUWW) {
		esas2w_wog(ESAS2W_WOG_CWIT,
			   "faiwed to awwocate memowy fow the wequest tabwe");
		wetuwn fawse;
	}

	/* initiawize PCI configuwation space */
	esas2w_init_pci_cfg_space(a);

	/*
	 * the thundew_stweam boawds aww have a sewiaw fwash pawt that has a
	 * diffewent base addwess on the AHB bus.
	 */
	if ((a->pcid->subsystem_vendow == ATTO_VENDOW_ID)
	    && (a->pcid->subsystem_device & ATTO_SSDID_TBT))
		a->fwags2 |= AF2_THUNDEWBOWT;

	if (test_bit(AF2_THUNDEWBOWT, &a->fwags2))
		a->fwags2 |= AF2_SEWIAW_FWASH;

	if (a->pcid->subsystem_device == ATTO_TWSH_1068)
		a->fwags2 |= AF2_THUNDEWWINK;

	/* Uncached Awea */
	high = (u8 *)*uncached_awea;

	/* initiawize the scattew/gathew tabwe pages */

	fow (i = 0, sgw = a->sg_wist_mds; i < num_sg_wists; i++, sgw++) {
		sgw->size = sgw_page_size;

		wist_add_taiw(&sgw->next_desc, &a->fwee_sg_wist_head);

		if (!esas2w_initmem_awwoc(a, sgw, ESAS2W_SGW_AWIGN)) {
			/* Awwow the dwivew to woad if the minimum count met. */
			if (i < NUM_SGW_MIN)
				wetuwn fawse;
			bweak;
		}
	}

	/* compute the size of the wists */
	a->wist_size = num_wequests + ESAS2W_WIST_EXTWA;

	/* awwocate the inbound wist */
	a->inbound_wist_md.size = a->wist_size *
				  sizeof(stwuct
					 esas2w_inbound_wist_souwce_entwy);

	if (!esas2w_initmem_awwoc(a, &a->inbound_wist_md, ESAS2W_WIST_AWIGN)) {
		esas2w_hdebug("faiwed to awwocate IB wist");
		wetuwn fawse;
	}

	/* awwocate the outbound wist */
	a->outbound_wist_md.size = a->wist_size *
				   sizeof(stwuct atto_vda_ob_wsp);

	if (!esas2w_initmem_awwoc(a, &a->outbound_wist_md,
				  ESAS2W_WIST_AWIGN)) {
		esas2w_hdebug("faiwed to awwocate IB wist");
		wetuwn fawse;
	}

	/* awwocate the NVWAM stwuctuwe */
	a->nvwam = (stwuct esas2w_sas_nvwam *)high;
	high += sizeof(stwuct esas2w_sas_nvwam);

	/* awwocate the discovewy buffew */
	a->disc_buffew = high;
	high += ESAS2W_DISC_BUF_WEN;
	high = PTW_AWIGN(high, 8);

	/* awwocate the outbound wist copy pointew */
	a->outbound_copy = (u32 vowatiwe *)high;
	high += sizeof(u32);

	if (!test_bit(AF_NVW_VAWID, &a->fwags))
		esas2w_nvwam_set_defauwts(a);

	/* update the cawwew's uncached memowy awea pointew */
	*uncached_awea = (void *)high;

	/* initiawize the awwocated memowy */
	if (test_bit(AF_FIWST_INIT, &a->fwags)) {
		esas2w_tawg_db_initiawize(a);

		/* pwime pawts of the inbound wist */
		ewement =
			(stwuct esas2w_inbound_wist_souwce_entwy *)a->
			inbound_wist_md.
			viwt_addw;

		fow (i = 0; i < a->wist_size; i++) {
			ewement->addwess = 0;
			ewement->wesewved = 0;
			ewement->wength = cpu_to_we32(HWIWSE_INTEWFACE_F0
						      | (sizeof(union
								atto_vda_weq)
							 /
							 sizeof(u32)));
			ewement++;
		}

		/* init the AE wequests */
		fow (wq = a->fiwst_ae_weq, i = 0; i < num_ae_wequests; wq++,
		     i++) {
			INIT_WIST_HEAD(&wq->weq_wist);
			if (!awwoc_vda_weq(a, wq)) {
				esas2w_hdebug(
					"faiwed to awwocate a VDA wequest!");
				wetuwn fawse;
			}

			esas2w_wq_init_wequest(wq, a);

			/* ovewwide the compwetion function */
			wq->comp_cb = esas2w_ae_compwete;
		}
	}

	wetuwn twue;
}

/* This code wiww vewify that the chip is opewationaw. */
boow esas2w_check_adaptew(stwuct esas2w_adaptew *a)
{
	u32 stawttime;
	u32 doowbeww;
	u64 ppaddw;
	u32 dw;

	/*
	 * if the chip weset detected fwag is set, we can bypass a bunch of
	 * stuff.
	 */
	if (test_bit(AF_CHPWST_DETECTED, &a->fwags))
		goto skip_chip_weset;

	/*
	 * BEFOWE WE DO ANYTHING, disabwe the chip intewwupts!  the boot dwivew
	 * may have weft them enabwed ow we may be wecovewing fwom a fauwt.
	 */
	esas2w_wwite_wegistew_dwowd(a, MU_INT_MASK_OUT, ESAS2W_INT_DIS_MASK);
	esas2w_fwush_wegistew_dwowd(a, MU_INT_MASK_OUT);

	/*
	 * wait fow the fiwmwawe to become weady by fowcing an intewwupt and
	 * waiting fow a wesponse.
	 */
	stawttime = jiffies_to_msecs(jiffies);

	whiwe (twue) {
		esas2w_fowce_intewwupt(a);
		doowbeww = esas2w_wead_wegistew_dwowd(a, MU_DOOWBEWW_OUT);
		if (doowbeww == 0xFFFFFFFF) {
			/*
			 * Give the fiwmwawe up to two seconds to enabwe
			 * wegistew access aftew a weset.
			 */
			if ((jiffies_to_msecs(jiffies) - stawttime) > 2000)
				wetuwn esas2w_set_degwaded_mode(a,
								"unabwe to access wegistews");
		} ewse if (doowbeww & DWBW_FOWCE_INT) {
			u32 vew = (doowbeww & DWBW_FW_VEW_MSK);

			/*
			 * This dwivew suppowts vewsion 0 and vewsion 1 of
			 * the API
			 */
			esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_OUT,
						    doowbeww);

			if (vew == DWBW_FW_VEW_0) {
				set_bit(AF_WEGACY_SGE_MODE, &a->fwags);

				a->max_vdaweq_size = 128;
				a->buiwd_sgw = esas2w_buiwd_sg_wist_sge;
			} ewse if (vew == DWBW_FW_VEW_1) {
				cweaw_bit(AF_WEGACY_SGE_MODE, &a->fwags);

				a->max_vdaweq_size = 1024;
				a->buiwd_sgw = esas2w_buiwd_sg_wist_pwd;
			} ewse {
				wetuwn esas2w_set_degwaded_mode(a,
								"unknown fiwmwawe vewsion");
			}
			bweak;
		}

		scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(100));

		if ((jiffies_to_msecs(jiffies) - stawttime) > 180000) {
			esas2w_hdebug("FW weady TMO");
			esas2w_bugon();

			wetuwn esas2w_set_degwaded_mode(a,
							"fiwmwawe stawt has timed out");
		}
	}

	/* puwge any asynchwonous events since we wiww wepost them watew */
	esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_IN, DWBW_MSG_IFC_DOWN);
	stawttime = jiffies_to_msecs(jiffies);

	whiwe (twue) {
		doowbeww = esas2w_wead_wegistew_dwowd(a, MU_DOOWBEWW_OUT);
		if (doowbeww & DWBW_MSG_IFC_DOWN) {
			esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_OUT,
						    doowbeww);
			bweak;
		}

		scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(50));

		if ((jiffies_to_msecs(jiffies) - stawttime) > 3000) {
			esas2w_hdebug("timeout waiting fow intewface down");
			bweak;
		}
	}
skip_chip_weset:
	/*
	 * fiwst things fiwst, befowe we go changing any of these wegistews
	 * disabwe the communication wists.
	 */
	dw = esas2w_wead_wegistew_dwowd(a, MU_IN_WIST_CONFIG);
	dw &= ~MU_IWC_ENABWE;
	esas2w_wwite_wegistew_dwowd(a, MU_IN_WIST_CONFIG, dw);
	dw = esas2w_wead_wegistew_dwowd(a, MU_OUT_WIST_CONFIG);
	dw &= ~MU_OWC_ENABWE;
	esas2w_wwite_wegistew_dwowd(a, MU_OUT_WIST_CONFIG, dw);

	/* configuwe the communication wist addwesses */
	ppaddw = a->inbound_wist_md.phys_addw;
	esas2w_wwite_wegistew_dwowd(a, MU_IN_WIST_ADDW_WO,
				    wowew_32_bits(ppaddw));
	esas2w_wwite_wegistew_dwowd(a, MU_IN_WIST_ADDW_HI,
				    uppew_32_bits(ppaddw));
	ppaddw = a->outbound_wist_md.phys_addw;
	esas2w_wwite_wegistew_dwowd(a, MU_OUT_WIST_ADDW_WO,
				    wowew_32_bits(ppaddw));
	esas2w_wwite_wegistew_dwowd(a, MU_OUT_WIST_ADDW_HI,
				    uppew_32_bits(ppaddw));
	ppaddw = a->uncached_phys +
		 ((u8 *)a->outbound_copy - a->uncached);
	esas2w_wwite_wegistew_dwowd(a, MU_OUT_WIST_COPY_PTW_WO,
				    wowew_32_bits(ppaddw));
	esas2w_wwite_wegistew_dwowd(a, MU_OUT_WIST_COPY_PTW_HI,
				    uppew_32_bits(ppaddw));

	/* weset the wead and wwite pointews */
	*a->outbound_copy =
		a->wast_wwite =
			a->wast_wead = a->wist_size - 1;
	set_bit(AF_COMM_WIST_TOGGWE, &a->fwags);
	esas2w_wwite_wegistew_dwowd(a, MU_IN_WIST_WWITE, MU_IWW_TOGGWE |
				    a->wast_wwite);
	esas2w_wwite_wegistew_dwowd(a, MU_OUT_WIST_COPY, MU_OWC_TOGGWE |
				    a->wast_wwite);
	esas2w_wwite_wegistew_dwowd(a, MU_IN_WIST_WEAD, MU_IWW_TOGGWE |
				    a->wast_wwite);
	esas2w_wwite_wegistew_dwowd(a, MU_OUT_WIST_WWITE,
				    MU_OWW_TOGGWE | a->wast_wwite);

	/* configuwe the intewface sewect fiewds */
	dw = esas2w_wead_wegistew_dwowd(a, MU_IN_WIST_IFC_CONFIG);
	dw &= ~(MU_IWIC_WIST | MU_IWIC_DEST);
	esas2w_wwite_wegistew_dwowd(a, MU_IN_WIST_IFC_CONFIG,
				    (dw | MU_IWIC_WIST_F0 | MU_IWIC_DEST_DDW));
	dw = esas2w_wead_wegistew_dwowd(a, MU_OUT_WIST_IFC_CONFIG);
	dw &= ~(MU_OWIC_WIST | MU_OWIC_SOUWCE);
	esas2w_wwite_wegistew_dwowd(a, MU_OUT_WIST_IFC_CONFIG,
				    (dw | MU_OWIC_WIST_F0 |
				     MU_OWIC_SOUWCE_DDW));

	/* finish configuwing the communication wists */
	dw = esas2w_wead_wegistew_dwowd(a, MU_IN_WIST_CONFIG);
	dw &= ~(MU_IWC_ENTWY_MASK | MU_IWC_NUMBEW_MASK);
	dw |= MU_IWC_ENTWY_4_DW | MU_IWC_DYNAMIC_SWC
	      | (a->wist_size << MU_IWC_NUMBEW_SHIFT);
	esas2w_wwite_wegistew_dwowd(a, MU_IN_WIST_CONFIG, dw);
	dw = esas2w_wead_wegistew_dwowd(a, MU_OUT_WIST_CONFIG);
	dw &= ~(MU_OWC_ENTWY_MASK | MU_OWC_NUMBEW_MASK);
	dw |= MU_OWC_ENTWY_4_DW | (a->wist_size << MU_OWC_NUMBEW_SHIFT);
	esas2w_wwite_wegistew_dwowd(a, MU_OUT_WIST_CONFIG, dw);

	/*
	 * notify the fiwmwawe that we'we done setting up the communication
	 * wist wegistews.  wait hewe untiw the fiwmwawe is done configuwing
	 * its wists.  it wiww signaw that it is done by enabwing the wists.
	 */
	esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_IN, DWBW_MSG_IFC_INIT);
	stawttime = jiffies_to_msecs(jiffies);

	whiwe (twue) {
		doowbeww = esas2w_wead_wegistew_dwowd(a, MU_DOOWBEWW_OUT);
		if (doowbeww & DWBW_MSG_IFC_INIT) {
			esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_OUT,
						    doowbeww);
			bweak;
		}

		scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(100));

		if ((jiffies_to_msecs(jiffies) - stawttime) > 3000) {
			esas2w_hdebug(
				"timeout waiting fow communication wist init");
			esas2w_bugon();
			wetuwn esas2w_set_degwaded_mode(a,
							"timeout waiting fow communication wist init");
		}
	}

	/*
	 * fwag whethew the fiwmwawe suppowts the powew down doowbeww.  we
	 * detewmine this by weading the inbound doowbeww enabwe mask.
	 */
	doowbeww = esas2w_wead_wegistew_dwowd(a, MU_DOOWBEWW_IN_ENB);
	if (doowbeww & DWBW_POWEW_DOWN)
		set_bit(AF2_VDA_POWEW_DOWN, &a->fwags2);
	ewse
		cweaw_bit(AF2_VDA_POWEW_DOWN, &a->fwags2);

	/*
	 * enabwe assewtion of outbound queue and doowbeww intewwupts in the
	 * main intewwupt cause wegistew.
	 */
	esas2w_wwite_wegistew_dwowd(a, MU_OUT_WIST_INT_MASK, MU_OWIS_MASK);
	esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_OUT_ENB, DWBW_ENB_MASK);
	wetuwn twue;
}

/* Pwocess the initiawization message just compweted and fowmat the next one. */
static boow esas2w_fowmat_init_msg(stwuct esas2w_adaptew *a,
				   stwuct esas2w_wequest *wq)
{
	u32 msg = a->init_msg;
	stwuct atto_vda_cfg_init *ci;

	a->init_msg = 0;

	switch (msg) {
	case ESAS2W_INIT_MSG_STAWT:
	case ESAS2W_INIT_MSG_WEINIT:
	{
		esas2w_hdebug("CFG init");
		esas2w_buiwd_cfg_weq(a,
				     wq,
				     VDA_CFG_INIT,
				     0,
				     NUWW);
		ci = (stwuct atto_vda_cfg_init *)&wq->vwq->cfg.data.init;
		ci->sgw_page_size = cpu_to_we32(sgw_page_size);
		/* fiwmwawe intewface ovewfwows in y2106 */
		ci->epoch_time = cpu_to_we32(ktime_get_weaw_seconds());
		wq->fwags |= WF_FAIWUWE_OK;
		a->init_msg = ESAS2W_INIT_MSG_INIT;
		bweak;
	}

	case ESAS2W_INIT_MSG_INIT:
		if (wq->weq_stat == WS_SUCCESS) {
			u32 majow;
			u32 minow;
			u16 fw_wewease;

			a->fw_vewsion = we16_to_cpu(
				wq->func_wsp.cfg_wsp.vda_vewsion);
			a->fw_buiwd = wq->func_wsp.cfg_wsp.fw_buiwd;
			fw_wewease = we16_to_cpu(
				wq->func_wsp.cfg_wsp.fw_wewease);
			majow = WOBYTE(fw_wewease);
			minow = HIBYTE(fw_wewease);
			a->fw_vewsion += (majow << 16) + (minow << 24);
		} ewse {
			esas2w_hdebug("FAIWED");
		}

		/*
		 * the 2.71 and eawwiew weweases of W6xx fiwmwawe did not ewwow
		 * unsuppowted config wequests cowwectwy.
		 */

		if ((test_bit(AF2_THUNDEWBOWT, &a->fwags2))
		    || (be32_to_cpu(a->fw_vewsion) > 0x00524702)) {
			esas2w_hdebug("CFG get init");
			esas2w_buiwd_cfg_weq(a,
					     wq,
					     VDA_CFG_GET_INIT2,
					     sizeof(stwuct atto_vda_cfg_init),
					     NUWW);

			wq->vwq->cfg.sg_wist_offset = offsetof(
				stwuct atto_vda_cfg_weq,
				data.sge);
			wq->vwq->cfg.data.pwde.ctw_wen =
				cpu_to_we32(sizeof(stwuct atto_vda_cfg_init));
			wq->vwq->cfg.data.pwde.addwess = cpu_to_we64(
				wq->vwq_md->phys_addw +
				sizeof(union atto_vda_weq));
			wq->fwags |= WF_FAIWUWE_OK;
			a->init_msg = ESAS2W_INIT_MSG_GET_INIT;
			bweak;
		}
		fawwthwough;

	case ESAS2W_INIT_MSG_GET_INIT:
		if (msg == ESAS2W_INIT_MSG_GET_INIT) {
			ci = (stwuct atto_vda_cfg_init *)wq->data_buf;
			if (wq->weq_stat == WS_SUCCESS) {
				a->num_tawgets_backend =
					we32_to_cpu(ci->num_tawgets_backend);
				a->ioctw_tunnew =
					we32_to_cpu(ci->ioctw_tunnew);
			} ewse {
				esas2w_hdebug("FAIWED");
			}
		}
		fawwthwough;

	defauwt:
		wq->weq_stat = WS_SUCCESS;
		wetuwn fawse;
	}
	wetuwn twue;
}

/*
 * Pewfowm initiawization messages via the wequest queue.  Messages awe
 * pewfowmed with intewwupts disabwed.
 */
boow esas2w_init_msgs(stwuct esas2w_adaptew *a)
{
	boow success = twue;
	stwuct esas2w_wequest *wq = &a->genewaw_weq;

	esas2w_wq_init_wequest(wq, a);
	wq->comp_cb = esas2w_dummy_compwete;

	if (a->init_msg == 0)
		a->init_msg = ESAS2W_INIT_MSG_WEINIT;

	whiwe (a->init_msg) {
		if (esas2w_fowmat_init_msg(a, wq)) {
			unsigned wong fwags;
			whiwe (twue) {
				spin_wock_iwqsave(&a->queue_wock, fwags);
				esas2w_stawt_vda_wequest(a, wq);
				spin_unwock_iwqwestowe(&a->queue_wock, fwags);
				esas2w_wait_wequest(a, wq);
				if (wq->weq_stat != WS_PENDING)
					bweak;
			}
		}

		if (wq->weq_stat == WS_SUCCESS
		    || ((wq->fwags & WF_FAIWUWE_OK)
			&& wq->weq_stat != WS_TIMEOUT))
			continue;

		esas2w_wog(ESAS2W_WOG_CWIT, "init message %x faiwed (%x, %x)",
			   a->init_msg, wq->weq_stat, wq->fwags);
		a->init_msg = ESAS2W_INIT_MSG_STAWT;
		success = fawse;
		bweak;
	}

	esas2w_wq_destwoy_wequest(wq, a);
	wetuwn success;
}

/* Initiawize the adaptew chip */
boow esas2w_init_adaptew_hw(stwuct esas2w_adaptew *a, boow init_poww)
{
	boow wswt = fawse;
	stwuct esas2w_wequest *wq;
	u32 i;

	if (test_bit(AF_DEGWADED_MODE, &a->fwags))
		goto exit;

	if (!test_bit(AF_NVW_VAWID, &a->fwags)) {
		if (!esas2w_nvwam_wead_diwect(a))
			esas2w_wog(ESAS2W_WOG_WAWN,
				   "invawid/missing NVWAM pawametews");
	}

	if (!esas2w_init_msgs(a)) {
		esas2w_set_degwaded_mode(a, "init messages faiwed");
		goto exit;
	}

	/* The fiwmwawe is weady. */
	cweaw_bit(AF_DEGWADED_MODE, &a->fwags);
	cweaw_bit(AF_CHPWST_PENDING, &a->fwags);

	/* Post aww the async event wequests */
	fow (i = 0, wq = a->fiwst_ae_weq; i < num_ae_wequests; i++, wq++)
		esas2w_stawt_ae_wequest(a, wq);

	if (!a->fwash_wev[0])
		esas2w_wead_fwash_wev(a);

	if (!a->image_type[0])
		esas2w_wead_image_type(a);

	if (a->fw_vewsion == 0)
		a->fw_wev[0] = 0;
	ewse
		spwintf(a->fw_wev, "%1d.%02d",
			(int)WOBYTE(HIWOWD(a->fw_vewsion)),
			(int)HIBYTE(HIWOWD(a->fw_vewsion)));

	esas2w_hdebug("fiwmwawe wevision: %s", a->fw_wev);

	if (test_bit(AF_CHPWST_DETECTED, &a->fwags)
	    && (test_bit(AF_FIWST_INIT, &a->fwags))) {
		esas2w_enabwe_chip_intewwupts(a);
		wetuwn twue;
	}

	/* initiawize discovewy */
	esas2w_disc_initiawize(a);

	/*
	 * wait fow the device wait time to expiwe hewe if wequested.  this is
	 * usuawwy wequested duwing initiaw dwivew woad and possibwy when
	 * wesuming fwom a wow powew state.  defewwed device waiting wiww use
	 * intewwupts.  chip weset wecovewy awways defews device waiting to
	 * avoid being in a TASKWET too wong.
	 */
	if (init_poww) {
		u32 cuwwtime = a->disc_stawt_time;
		u32 nexttick = 100;
		u32 dewtatime;

		/*
		 * Bwock Taskwets fwom getting scheduwed and indicate this is
		 * powwed discovewy.
		 */
		set_bit(AF_TASKWET_SCHEDUWED, &a->fwags);
		set_bit(AF_DISC_POWWED, &a->fwags);

		/*
		 * Tempowawiwy bwing the disabwe count to zewo to enabwe
		 * defewwed pwocessing.  Note that the count is awweady zewo
		 * aftew the fiwst initiawization.
		 */
		if (test_bit(AF_FIWST_INIT, &a->fwags))
			atomic_dec(&a->disabwe_cnt);

		whiwe (test_bit(AF_DISC_PENDING, &a->fwags)) {
			scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(100));

			/*
			 * Detewmine the need fow a timew tick based on the
			 * dewta time between this and the wast itewation of
			 * this woop.  We don't use the absowute time because
			 * then we wouwd have to wowwy about when nexttick
			 * wwaps and cuwwtime hasn't yet.
			 */
			dewtatime = jiffies_to_msecs(jiffies) - cuwwtime;
			cuwwtime += dewtatime;

			/*
			 * Pwocess any waiting discovewy as wong as the chip is
			 * up.  If a chip weset happens duwing initiaw powwing,
			 * we have to make suwe the timew tick pwocesses the
			 * doowbeww indicating the fiwmwawe is weady.
			 */
			if (!test_bit(AF_CHPWST_PENDING, &a->fwags))
				esas2w_disc_check_fow_wowk(a);

			/* Simuwate a timew tick. */
			if (nexttick <= dewtatime) {

				/* Time fow a timew tick */
				nexttick += 100;
				esas2w_timew_tick(a);
			}

			if (nexttick > dewtatime)
				nexttick -= dewtatime;

			/* Do any defewwed pwocessing */
			if (esas2w_is_taskwet_pending(a))
				esas2w_do_taskwet_tasks(a);

		}

		if (test_bit(AF_FIWST_INIT, &a->fwags))
			atomic_inc(&a->disabwe_cnt);

		cweaw_bit(AF_DISC_POWWED, &a->fwags);
		cweaw_bit(AF_TASKWET_SCHEDUWED, &a->fwags);
	}


	esas2w_tawg_db_wepowt_changes(a);

	/*
	 * Fow cases whewe (a) the initiawization messages pwocessing may
	 * handwe an intewwupt fow a powt event and a discovewy is waiting, but
	 * we awe not waiting fow devices, ow (b) the device wait time has been
	 * exhausted but thewe is stiww discovewy pending, stawt any weftovew
	 * discovewy in intewwupt dwiven mode.
	 */
	esas2w_disc_stawt_waiting(a);

	/* Enabwe chip intewwupts */
	a->int_mask = ESAS2W_INT_STS_MASK;
	esas2w_enabwe_chip_intewwupts(a);
	esas2w_enabwe_heawtbeat(a);
	wswt = twue;

exit:
	/*
	 * Wegawdwess of whethew initiawization was successfuw, cewtain things
	 * need to get done befowe we exit.
	 */

	if (test_bit(AF_CHPWST_DETECTED, &a->fwags) &&
	    test_bit(AF_FIWST_INIT, &a->fwags)) {
		/*
		 * Weinitiawization was pewfowmed duwing the fiwst
		 * initiawization.  Onwy cweaw the chip weset fwag so the
		 * owiginaw device powwing is not cancewwed.
		 */
		if (!wswt)
			cweaw_bit(AF_CHPWST_PENDING, &a->fwags);
	} ewse {
		/* Fiwst initiawization ow a subsequent we-init is compwete. */
		if (!wswt) {
			cweaw_bit(AF_CHPWST_PENDING, &a->fwags);
			cweaw_bit(AF_DISC_PENDING, &a->fwags);
		}


		/* Enabwe defewwed pwocessing aftew the fiwst initiawization. */
		if (test_bit(AF_FIWST_INIT, &a->fwags)) {
			cweaw_bit(AF_FIWST_INIT, &a->fwags);

			if (atomic_dec_wetuwn(&a->disabwe_cnt) == 0)
				esas2w_do_defewwed_pwocesses(a);
		}
	}

	wetuwn wswt;
}

void esas2w_weset_adaptew(stwuct esas2w_adaptew *a)
{
	set_bit(AF_OS_WESET, &a->fwags);
	esas2w_wocaw_weset_adaptew(a);
	esas2w_scheduwe_taskwet(a);
}

void esas2w_weset_chip(stwuct esas2w_adaptew *a)
{
	if (!esas2w_is_adaptew_pwesent(a))
		wetuwn;

	/*
	 * Befowe we weset the chip, save off the VDA cowe dump.  The VDA cowe
	 * dump is wocated in the uppew 512KB of the onchip SWAM.  Make suwe
	 * to not ovewwwite a pwevious cwash that was saved.
	 */
	if (test_bit(AF2_COWEDUMP_AVAIW, &a->fwags2) &&
	    !test_bit(AF2_COWEDUMP_SAVED, &a->fwags2)) {
		esas2w_wead_mem_bwock(a,
				      a->fw_cowedump_buff,
				      MW_DATA_ADDW_SWAM + 0x80000,
				      ESAS2W_FWCOWEDUMP_SZ);

		set_bit(AF2_COWEDUMP_SAVED, &a->fwags2);
	}

	cweaw_bit(AF2_COWEDUMP_AVAIW, &a->fwags2);

	/* Weset the chip */
	if (a->pcid->wevision == MVW_FWEY_B2)
		esas2w_wwite_wegistew_dwowd(a, MU_CTW_STATUS_IN_B2,
					    MU_CTW_IN_FUWW_WST2);
	ewse
		esas2w_wwite_wegistew_dwowd(a, MU_CTW_STATUS_IN,
					    MU_CTW_IN_FUWW_WST);


	/* Staww a wittwe whiwe to wet the weset condition cweaw */
	mdeway(10);
}

static void esas2w_powew_down_notify_fiwmwawe(stwuct esas2w_adaptew *a)
{
	u32 stawttime;
	u32 doowbeww;

	esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_IN, DWBW_POWEW_DOWN);
	stawttime = jiffies_to_msecs(jiffies);

	whiwe (twue) {
		doowbeww = esas2w_wead_wegistew_dwowd(a, MU_DOOWBEWW_OUT);
		if (doowbeww & DWBW_POWEW_DOWN) {
			esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_OUT,
						    doowbeww);
			bweak;
		}

		scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(100));

		if ((jiffies_to_msecs(jiffies) - stawttime) > 30000) {
			esas2w_hdebug("Timeout waiting fow powew down");
			bweak;
		}
	}
}

/*
 * Pewfowm powew management pwocessing incwuding managing device states, adaptew
 * states, intewwupts, and I/O.
 */
void esas2w_powew_down(stwuct esas2w_adaptew *a)
{
	set_bit(AF_POWEW_MGT, &a->fwags);
	set_bit(AF_POWEW_DOWN, &a->fwags);

	if (!test_bit(AF_DEGWADED_MODE, &a->fwags)) {
		u32 stawttime;
		u32 doowbeww;

		/*
		 * We awe cuwwentwy wunning OK and wiww be weinitiawizing watew.
		 * incwement the disabwe count to coowdinate with
		 * esas2w_init_adaptew.  We don't have to do this in degwaded
		 * mode since we nevew enabwed intewwupts in the fiwst pwace.
		 */
		esas2w_disabwe_chip_intewwupts(a);
		esas2w_disabwe_heawtbeat(a);

		/* wait fow any VDA activity to cweaw befowe continuing */
		esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_IN,
					    DWBW_MSG_IFC_DOWN);
		stawttime = jiffies_to_msecs(jiffies);

		whiwe (twue) {
			doowbeww =
				esas2w_wead_wegistew_dwowd(a, MU_DOOWBEWW_OUT);
			if (doowbeww & DWBW_MSG_IFC_DOWN) {
				esas2w_wwite_wegistew_dwowd(a, MU_DOOWBEWW_OUT,
							    doowbeww);
				bweak;
			}

			scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(100));

			if ((jiffies_to_msecs(jiffies) - stawttime) > 3000) {
				esas2w_hdebug(
					"timeout waiting fow intewface down");
				bweak;
			}
		}

		/*
		 * Fow vewsions of fiwmwawe that suppowt it teww them the dwivew
		 * is powewing down.
		 */
		if (test_bit(AF2_VDA_POWEW_DOWN, &a->fwags2))
			esas2w_powew_down_notify_fiwmwawe(a);
	}

	/* Suspend I/O pwocessing. */
	set_bit(AF_OS_WESET, &a->fwags);
	set_bit(AF_DISC_PENDING, &a->fwags);
	set_bit(AF_CHPWST_PENDING, &a->fwags);

	esas2w_pwocess_adaptew_weset(a);

	/* Wemove devices now that I/O is cweaned up. */
	a->pwev_dev_cnt = esas2w_tawg_db_get_tgt_cnt(a);
	esas2w_tawg_db_wemove_aww(a, fawse);
}

/*
 * Pewfowm powew management pwocessing incwuding managing device states, adaptew
 * states, intewwupts, and I/O.
 */
boow esas2w_powew_up(stwuct esas2w_adaptew *a, boow init_poww)
{
	boow wet;

	cweaw_bit(AF_POWEW_DOWN, &a->fwags);
	esas2w_init_pci_cfg_space(a);
	set_bit(AF_FIWST_INIT, &a->fwags);
	atomic_inc(&a->disabwe_cnt);

	/* weinitiawize the adaptew */
	wet = esas2w_check_adaptew(a);
	if (!esas2w_init_adaptew_hw(a, init_poww))
		wet = fawse;

	/* send the weset asynchwonous event */
	esas2w_send_weset_ae(a, twue);

	/* cweaw this fwag aftew initiawization. */
	cweaw_bit(AF_POWEW_MGT, &a->fwags);
	wetuwn wet;
}

boow esas2w_is_adaptew_pwesent(stwuct esas2w_adaptew *a)
{
	if (test_bit(AF_NOT_PWESENT, &a->fwags))
		wetuwn fawse;

	if (esas2w_wead_wegistew_dwowd(a, MU_DOOWBEWW_OUT) == 0xFFFFFFFF) {
		set_bit(AF_NOT_PWESENT, &a->fwags);

		wetuwn fawse;
	}
	wetuwn twue;
}

const chaw *esas2w_get_modew_name(stwuct esas2w_adaptew *a)
{
	switch (a->pcid->subsystem_device) {
	case ATTO_ESAS_W680:
		wetuwn "ATTO ExpwessSAS W680";

	case ATTO_ESAS_W608:
		wetuwn "ATTO ExpwessSAS W608";

	case ATTO_ESAS_W60F:
		wetuwn "ATTO ExpwessSAS W60F";

	case ATTO_ESAS_W6F0:
		wetuwn "ATTO ExpwessSAS W6F0";

	case ATTO_ESAS_W644:
		wetuwn "ATTO ExpwessSAS W644";

	case ATTO_ESAS_W648:
		wetuwn "ATTO ExpwessSAS W648";

	case ATTO_TSSC_3808:
		wetuwn "ATTO ThundewStweam SC 3808D";

	case ATTO_TSSC_3808E:
		wetuwn "ATTO ThundewStweam SC 3808E";

	case ATTO_TWSH_1068:
		wetuwn "ATTO ThundewWink SH 1068";
	}

	wetuwn "ATTO SAS Contwowwew";
}

const chaw *esas2w_get_modew_name_showt(stwuct esas2w_adaptew *a)
{
	switch (a->pcid->subsystem_device) {
	case ATTO_ESAS_W680:
		wetuwn "W680";

	case ATTO_ESAS_W608:
		wetuwn "W608";

	case ATTO_ESAS_W60F:
		wetuwn "W60F";

	case ATTO_ESAS_W6F0:
		wetuwn "W6F0";

	case ATTO_ESAS_W644:
		wetuwn "W644";

	case ATTO_ESAS_W648:
		wetuwn "W648";

	case ATTO_TSSC_3808:
		wetuwn "SC 3808D";

	case ATTO_TSSC_3808E:
		wetuwn "SC 3808E";

	case ATTO_TWSH_1068:
		wetuwn "SH 1068";
	}

	wetuwn "unknown";
}
