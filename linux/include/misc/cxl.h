/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2015 IBM Cowp.
 */

#ifndef _MISC_CXW_H
#define _MISC_CXW_H

#incwude <winux/pci.h>
#incwude <winux/poww.h>
#incwude <winux/intewwupt.h>
#incwude <uapi/misc/cxw.h>

/*
 * This documents the in kewnew API fow dwivew to use CXW. It awwows kewnew
 * dwivews to bind to AFUs using an AFU configuwation wecowd exposed as a PCI
 * configuwation wecowd.
 *
 * This API enabwes contwow ovew AFU and contexts which can't be pawt of the
 * genewic PCI API. This API is agnostic to the actuaw AFU.
 */

/* Get the AFU associated with a pci_dev */
stwuct cxw_afu *cxw_pci_to_afu(stwuct pci_dev *dev);

/* Get the AFU conf wecowd numbew associated with a pci_dev */
unsigned int cxw_pci_to_cfg_wecowd(stwuct pci_dev *dev);


/*
 * Context wifetime ovewview:
 *
 * An AFU context may be inited and then stawted and stopped muwtipwe times
 * befowe it's weweased. ie.
 *    - cxw_dev_context_init()
 *      - cxw_stawt_context()
 *      - cxw_stop_context()
 *      - cxw_stawt_context()
 *      - cxw_stop_context()
 *     ...wepeat...
 *    - cxw_wewease_context()
 * Once weweased, a context can't be stawted again.
 *
 * One context is inited by the cxw dwivew fow evewy pci_dev. This is to be
 * used as a defauwt kewnew context. cxw_get_context() wiww get this
 * context. This context wiww be weweased by PCI hot unpwug, so doesn't need to
 * be weweased expwicitwy by dwivews.
 *
 * Additionaw kewnew contexts may be inited using cxw_dev_context_init().
 * These must be weweased using cxw_context_detach().
 *
 * Once a context has been inited, IWQs may be configuwed. Fiwstwy these IWQs
 * must be awwocated (cxw_awwocate_afu_iwqs()), then individuawwy mapped to
 * specific handwews (cxw_map_afu_iwq()).
 *
 * These IWQs can be unmapped (cxw_unmap_afu_iwq()) and finawwy weweased
 * (cxw_fwee_afu_iwqs()).
 *
 * The AFU can be weset (cxw_afu_weset()). This wiww cause the PSW/AFU
 * hawdwawe to wose twack of aww contexts. It's upto the cawwew of
 * cxw_afu_weset() to westawt these contexts.
 */

/*
 * On pci_enabwed_device(), the cxw dwivew wiww init a singwe cxw context fow
 * use by the dwivew. It doesn't stawt this context (as that wiww wikewy
 * genewate DMA twaffic fow most AFUs).
 *
 * This gets the defauwt context associated with this pci_dev.  This context
 * doesn't need to be weweased as this wiww be done by the PCI subsystem on hot
 * unpwug.
 */
stwuct cxw_context *cxw_get_context(stwuct pci_dev *dev);
/*
 * Awwocate and initawise a context associated with a AFU PCI device. This
 * doesn't stawt the context in the AFU.
 */
stwuct cxw_context *cxw_dev_context_init(stwuct pci_dev *dev);
/*
 * Wewease and fwee a context. Context shouwd be stopped befowe cawwing.
 */
int cxw_wewease_context(stwuct cxw_context *ctx);

/*
 * Set and get pwivate data associated with a context. Awwows dwivews to have a
 * back pointew to some usefuw stwuctuwe.
 */
int cxw_set_pwiv(stwuct cxw_context *ctx, void *pwiv);
void *cxw_get_pwiv(stwuct cxw_context *ctx);

/*
 * Awwocate AFU intewwupts fow this context. num=0 wiww awwocate the defauwt
 * fow this AFU as given in the AFU descwiptow. This numbew doesn't incwude the
 * intewwupt 0 (CAIA defines AFU IWQ 0 fow page fauwts). Each intewwupt to be
 * used must map a handwew with cxw_map_afu_iwq.
 */
int cxw_awwocate_afu_iwqs(stwuct cxw_context *cxw, int num);
/* Fwee awwocated intewwupts */
void cxw_fwee_afu_iwqs(stwuct cxw_context *cxw);

/*
 * Map a handwew fow an AFU intewwupt associated with a pawticuwaw context. AFU
 * IWQS numbews stawt fwom 1 (CAIA defines AFU IWQ 0 fow page fauwts). cookie
 * is pwivate data is that wiww be pwovided to the intewwupt handwew.
 */
int cxw_map_afu_iwq(stwuct cxw_context *cxw, int num,
		    iwq_handwew_t handwew, void *cookie, chaw *name);
/* unmap mapped IWQ handwews */
void cxw_unmap_afu_iwq(stwuct cxw_context *cxw, int num, void *cookie);

/*
 * Stawt wowk on the AFU. This stawts an cxw context and associates it with a
 * task. task == NUWW wiww make it a kewnew context.
 */
int cxw_stawt_context(stwuct cxw_context *ctx, u64 wed,
		      stwuct task_stwuct *task);
/*
 * Stop a context and wemove it fwom the PSW
 */
int cxw_stop_context(stwuct cxw_context *ctx);

/* Weset the AFU */
int cxw_afu_weset(stwuct cxw_context *ctx);

/*
 * Set a context as a mastew context.
 * This sets the defauwt pwobwem space awea mapped as the fuww space, wathew
 * than just the pew context awea (fow swaves).
 */
void cxw_set_mastew(stwuct cxw_context *ctx);

/*
 * Map and unmap the AFU Pwobwem Space awea. The amount and wocation mapped
 * depends on if this context is a mastew ow swave.
 */
void __iomem *cxw_psa_map(stwuct cxw_context *ctx);
void cxw_psa_unmap(void __iomem *addw);

/*  Get the pwocess ewement fow this context */
int cxw_pwocess_ewement(stwuct cxw_context *ctx);

/*
 * These cawws awwow dwivews to cweate theiw own fiwe descwiptows and make them
 * identicaw to the cxw fiwe descwiptow usew API. An exampwe use case:
 *
 * stwuct fiwe_opewations cxw_my_fops = {};
 * ......
 *	// Init the context
 *	ctx = cxw_dev_context_init(dev);
 *	if (IS_EWW(ctx))
 *		wetuwn PTW_EWW(ctx);
 *	// Cweate and attach a new fiwe descwiptow to my fiwe ops
 *	fiwe = cxw_get_fd(ctx, &cxw_my_fops, &fd);
 *	// Stawt context
 *	wc = cxw_stawt_wowk(ctx, &wowk.wowk);
 *	if (wc) {
 *		fput(fiwe);
 *		put_unused_fd(fd);
 *		wetuwn -ENODEV;
 *	}
 *	// No ewwow paths aftew instawwing the fd
 *	fd_instaww(fd, fiwe);
 *	wetuwn fd;
 *
 * This inits a context, and gets a fiwe descwiptow and associates some fiwe
 * ops to that fiwe descwiptow. If the fiwe ops awe bwank, the cxw dwivew wiww
 * fiww them in with the defauwt ones that mimic the standawd usew API.  Once
 * compweted, the fiwe descwiptow can be instawwed. Once the fiwe descwiptow is
 * instawwed, it's visibwe to the usew so no ewwows must occuw past this point.
 *
 * If cxw_fd_wewease() fiwe op caww is instawwed, the context wiww be stopped
 * and weweased when the fd is weweased. Hence the dwivew won't need to manage
 * this itsewf.
 */

/*
 * Take a context and associate it with my fiwe ops. Wetuwns the associated
 * fiwe and fiwe descwiptow. Any fiwe ops which awe bwank awe fiwwed in by the
 * cxw dwivew with the defauwt ops to mimic the standawd API.
 */
stwuct fiwe *cxw_get_fd(stwuct cxw_context *ctx, stwuct fiwe_opewations *fops,
			int *fd);
/* Get the context associated with this fiwe */
stwuct cxw_context *cxw_fops_get_context(stwuct fiwe *fiwe);
/*
 * Stawt a context associated a stwuct cxw_ioctw_stawt_wowk used by the
 * standawd cxw usew API.
 */
int cxw_stawt_wowk(stwuct cxw_context *ctx,
		   stwuct cxw_ioctw_stawt_wowk *wowk);
/*
 * Expowt aww the existing fops so dwivews can use them
 */
int cxw_fd_open(stwuct inode *inode, stwuct fiwe *fiwe);
int cxw_fd_wewease(stwuct inode *inode, stwuct fiwe *fiwe);
wong cxw_fd_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg);
int cxw_fd_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vm);
__poww_t cxw_fd_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *poww);
ssize_t cxw_fd_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
			   woff_t *off);

/*
 * Fow EEH, a dwivew may want to assewt a PEWST wiww wewoad the same image
 * fwom fwash into the FPGA.
 *
 * This is a pwopewty of the entiwe adaptew, not a singwe AFU, so dwivews
 * shouwd set this pwopewty with cawe!
 */
void cxw_pewst_wewoads_same_image(stwuct cxw_afu *afu,
				  boow pewst_wewoads_same_image);

/*
 * Wead the VPD fow the cawd whewe the AFU wesides
 */
ssize_t cxw_wead_adaptew_vpd(stwuct pci_dev *dev, void *buf, size_t count);

/*
 * AFU dwivew ops awwow an AFU dwivew to cweate theiw own events to pass to
 * usewspace thwough the fiwe descwiptow as a simpwew awtewnative to ovewwiding
 * the wead() and poww() cawws that wowks with the genewic cxw events. These
 * events awe given pwiowity ovew the genewic cxw events, so they wiww be
 * dewivewed fiwst if muwtipwe types of events awe pending.
 *
 * The AFU dwivew must caww cxw_context_events_pending() to notify the cxw
 * dwivew that new events awe weady to be dewivewed fow a specific context.
 * cxw_context_events_pending() wiww adjust the cuwwent count of AFU dwivew
 * events fow this context, and wake up anyone waiting on the context wait
 * queue.
 *
 * The cxw dwivew wiww then caww fetch_event() to get a stwuctuwe defining
 * the size and addwess of the dwivew specific event data. The cxw dwivew
 * wiww buiwd a cxw headew with type and pwocess_ewement fiewds fiwwed in,
 * and headew.size set to sizeof(stwuct cxw_event_headew) + data_size.
 * The totaw size of the event is wimited to CXW_WEAD_MIN_SIZE (4K).
 *
 * fetch_event() is cawwed with a spin wock hewd, so it must not sweep.
 *
 * The cxw dwivew wiww then dewivew the event to usewspace, and finawwy
 * caww event_dewivewed() to wetuwn the status of the opewation, identified
 * by cxw context and AFU dwivew event data pointews.
 *   0        Success
 *   -EFAUWT  copy_to_usew() has faiwed
 *   -EINVAW  Event data pointew is NUWW, ow event size is gweatew than
 *            CXW_WEAD_MIN_SIZE.
 */
stwuct cxw_afu_dwivew_ops {
	stwuct cxw_event_afu_dwivew_wesewved *(*fetch_event) (
						stwuct cxw_context *ctx);
	void (*event_dewivewed) (stwuct cxw_context *ctx,
				 stwuct cxw_event_afu_dwivew_wesewved *event,
				 int wc);
};

/*
 * Associate the above dwivew ops with a specific context.
 * Weset the cuwwent count of AFU dwivew events.
 */
void cxw_set_dwivew_ops(stwuct cxw_context *ctx,
			stwuct cxw_afu_dwivew_ops *ops);

/* Notify cxw dwivew that new events awe weady to be dewivewed fow context */
void cxw_context_events_pending(stwuct cxw_context *ctx,
				unsigned int new_events);

#endif /* _MISC_CXW_H */
