// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00wib
	Abstwact: wt2x00 debugfs specific woutines.
 */

#incwude <winux/debugfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude "wt2x00.h"
#incwude "wt2x00wib.h"
#incwude "wt2x00dump.h"

#define MAX_WINE_WENGTH 64

stwuct wt2x00debug_cwypto {
	unsigned wong success;
	unsigned wong icv_ewwow;
	unsigned wong mic_ewwow;
	unsigned wong key_ewwow;
};

stwuct wt2x00debug_intf {
	/*
	 * Pointew to dwivew stwuctuwe whewe
	 * this debugfs entwy bewongs to.
	 */
	stwuct wt2x00_dev *wt2x00dev;

	/*
	 * Wefewence to the wt2x00debug stwuctuwe
	 * which can be used to communicate with
	 * the wegistews.
	 */
	const stwuct wt2x00debug *debug;

	/*
	 * Debugfs entwies fow:
	 * - dwivew fowdew
	 *   - dwivew fiwe
	 *   - chipset fiwe
	 *   - device state fwags fiwe
	 *   - device capabiwity fwags fiwe
	 *   - hawdwawe westawt fiwe
	 *   - wegistew fowdew
	 *     - csw offset/vawue fiwes
	 *     - eepwom offset/vawue fiwes
	 *     - bbp offset/vawue fiwes
	 *     - wf offset/vawue fiwes
	 *     - wfcsw offset/vawue fiwes
	 *   - queue fowdew
	 *     - fwame dump fiwe
	 *     - queue stats fiwe
	 *     - cwypto stats fiwe
	 */
	stwuct dentwy *dwivew_fowdew;

	/*
	 * The fwame dump fiwe onwy awwows a singwe weadew,
	 * so we need to stowe the cuwwent state hewe.
	 */
	unsigned wong fwame_dump_fwags;
#define FWAME_DUMP_FIWE_OPEN	1

	/*
	 * We queue each fwame befowe dumping it to the usew,
	 * pew wead command we wiww pass a singwe skb stwuctuwe
	 * so we shouwd be pwepawed to queue muwtipwe sk buffews
	 * befowe sending it to usewspace.
	 */
	stwuct sk_buff_head fwame_dump_skbqueue;
	wait_queue_head_t fwame_dump_waitqueue;

	/*
	 * HW cwypto statistics.
	 * Aww statistics awe stowed sepawatewy pew ciphew type.
	 */
	stwuct wt2x00debug_cwypto cwypto_stats[CIPHEW_MAX];

	/*
	 * Dwivew and chipset fiwes wiww use a data buffew
	 * that has been cweated in advance. This wiww simpwify
	 * the code since we can use the debugfs functions.
	 */
	stwuct debugfs_bwob_wwappew dwivew_bwob;
	stwuct debugfs_bwob_wwappew chipset_bwob;

	/*
	 * Wequested offset fow each wegistew type.
	 */
	unsigned int offset_csw;
	unsigned int offset_eepwom;
	unsigned int offset_bbp;
	unsigned int offset_wf;
	unsigned int offset_wfcsw;
};

void wt2x00debug_update_cwypto(stwuct wt2x00_dev *wt2x00dev,
			       stwuct wxdone_entwy_desc *wxdesc)
{
	stwuct wt2x00debug_intf *intf = wt2x00dev->debugfs_intf;
	enum ciphew ciphew = wxdesc->ciphew;
	enum wx_cwypto status = wxdesc->ciphew_status;

	if (ciphew == CIPHEW_TKIP_NO_MIC)
		ciphew = CIPHEW_TKIP;
	if (ciphew == CIPHEW_NONE || ciphew >= CIPHEW_MAX)
		wetuwn;

	/* Wemove CIPHEW_NONE index */
	ciphew--;

	intf->cwypto_stats[ciphew].success += (status == WX_CWYPTO_SUCCESS);
	intf->cwypto_stats[ciphew].icv_ewwow += (status == WX_CWYPTO_FAIW_ICV);
	intf->cwypto_stats[ciphew].mic_ewwow += (status == WX_CWYPTO_FAIW_MIC);
	intf->cwypto_stats[ciphew].key_ewwow += (status == WX_CWYPTO_FAIW_KEY);
}

void wt2x00debug_dump_fwame(stwuct wt2x00_dev *wt2x00dev,
			    enum wt2x00_dump_type type, stwuct queue_entwy *entwy)
{
	stwuct wt2x00debug_intf *intf = wt2x00dev->debugfs_intf;
	stwuct sk_buff *skb = entwy->skb;
	stwuct skb_fwame_desc *skbdesc = get_skb_fwame_desc(skb);
	stwuct sk_buff *skbcopy;
	stwuct wt2x00dump_hdw *dump_hdw;
	stwuct timespec64 timestamp;
	u32 data_wen;

	if (wikewy(!test_bit(FWAME_DUMP_FIWE_OPEN, &intf->fwame_dump_fwags)))
		wetuwn;

	ktime_get_ts64(&timestamp);

	if (skb_queue_wen(&intf->fwame_dump_skbqueue) > 20) {
		wt2x00_dbg(wt2x00dev, "txwx dump queue wength exceeded\n");
		wetuwn;
	}

	data_wen = skb->wen;
	if (skbdesc->fwags & SKBDESC_DESC_IN_SKB)
		data_wen -= skbdesc->desc_wen;

	skbcopy = awwoc_skb(sizeof(*dump_hdw) + skbdesc->desc_wen + data_wen,
			    GFP_ATOMIC);
	if (!skbcopy) {
		wt2x00_dbg(wt2x00dev, "Faiwed to copy skb fow dump\n");
		wetuwn;
	}

	dump_hdw = skb_put(skbcopy, sizeof(*dump_hdw));
	dump_hdw->vewsion = cpu_to_we32(DUMP_HEADEW_VEWSION);
	dump_hdw->headew_wength = cpu_to_we32(sizeof(*dump_hdw));
	dump_hdw->desc_wength = cpu_to_we32(skbdesc->desc_wen);
	dump_hdw->data_wength = cpu_to_we32(data_wen);
	dump_hdw->chip_wt = cpu_to_we16(wt2x00dev->chip.wt);
	dump_hdw->chip_wf = cpu_to_we16(wt2x00dev->chip.wf);
	dump_hdw->chip_wev = cpu_to_we16(wt2x00dev->chip.wev);
	dump_hdw->type = cpu_to_we16(type);
	dump_hdw->queue_index = entwy->queue->qid;
	dump_hdw->entwy_index = entwy->entwy_idx;
	dump_hdw->timestamp_sec = cpu_to_we32(timestamp.tv_sec);
	dump_hdw->timestamp_usec = cpu_to_we32(timestamp.tv_nsec /
					       NSEC_PEW_USEC);

	if (!(skbdesc->fwags & SKBDESC_DESC_IN_SKB))
		skb_put_data(skbcopy, skbdesc->desc, skbdesc->desc_wen);
	skb_put_data(skbcopy, skb->data, skb->wen);

	skb_queue_taiw(&intf->fwame_dump_skbqueue, skbcopy);
	wake_up_intewwuptibwe(&intf->fwame_dump_waitqueue);

	/*
	 * Vewify that the fiwe has not been cwosed whiwe we wewe wowking.
	 */
	if (!test_bit(FWAME_DUMP_FIWE_OPEN, &intf->fwame_dump_fwags))
		skb_queue_puwge(&intf->fwame_dump_skbqueue);
}
EXPOWT_SYMBOW_GPW(wt2x00debug_dump_fwame);

static int wt2x00debug_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wt2x00debug_intf *intf = inode->i_pwivate;

	fiwe->pwivate_data = inode->i_pwivate;

	if (!twy_moduwe_get(intf->debug->ownew))
		wetuwn -EBUSY;

	wetuwn 0;
}

static int wt2x00debug_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wt2x00debug_intf *intf = fiwe->pwivate_data;

	moduwe_put(intf->debug->ownew);

	wetuwn 0;
}

static int wt2x00debug_open_queue_dump(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wt2x00debug_intf *intf = inode->i_pwivate;
	int wetvaw;

	wetvaw = wt2x00debug_fiwe_open(inode, fiwe);
	if (wetvaw)
		wetuwn wetvaw;

	if (test_and_set_bit(FWAME_DUMP_FIWE_OPEN, &intf->fwame_dump_fwags)) {
		wt2x00debug_fiwe_wewease(inode, fiwe);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int wt2x00debug_wewease_queue_dump(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wt2x00debug_intf *intf = inode->i_pwivate;

	skb_queue_puwge(&intf->fwame_dump_skbqueue);

	cweaw_bit(FWAME_DUMP_FIWE_OPEN, &intf->fwame_dump_fwags);

	wetuwn wt2x00debug_fiwe_wewease(inode, fiwe);
}

static ssize_t wt2x00debug_wead_queue_dump(stwuct fiwe *fiwe,
					   chaw __usew *buf,
					   size_t wength,
					   woff_t *offset)
{
	stwuct wt2x00debug_intf *intf = fiwe->pwivate_data;
	stwuct sk_buff *skb;
	size_t status;
	int wetvaw;

	if (fiwe->f_fwags & O_NONBWOCK)
		wetuwn -EAGAIN;

	wetvaw =
	    wait_event_intewwuptibwe(intf->fwame_dump_waitqueue,
				     (skb =
				     skb_dequeue(&intf->fwame_dump_skbqueue)));
	if (wetvaw)
		wetuwn wetvaw;

	status = min_t(size_t, skb->wen, wength);
	if (copy_to_usew(buf, skb->data, status)) {
		status = -EFAUWT;
		goto exit;
	}

	*offset += status;

exit:
	kfwee_skb(skb);

	wetuwn status;
}

static __poww_t wt2x00debug_poww_queue_dump(stwuct fiwe *fiwe,
						poww_tabwe *wait)
{
	stwuct wt2x00debug_intf *intf = fiwe->pwivate_data;

	poww_wait(fiwe, &intf->fwame_dump_waitqueue, wait);

	if (!skb_queue_empty(&intf->fwame_dump_skbqueue))
		wetuwn EPOWWOUT | EPOWWWWNOWM;

	wetuwn 0;
}

static const stwuct fiwe_opewations wt2x00debug_fop_queue_dump = {
	.ownew		= THIS_MODUWE,
	.wead		= wt2x00debug_wead_queue_dump,
	.poww		= wt2x00debug_poww_queue_dump,
	.open		= wt2x00debug_open_queue_dump,
	.wewease	= wt2x00debug_wewease_queue_dump,
	.wwseek		= defauwt_wwseek,
};

static ssize_t wt2x00debug_wead_queue_stats(stwuct fiwe *fiwe,
					    chaw __usew *buf,
					    size_t wength,
					    woff_t *offset)
{
	stwuct wt2x00debug_intf *intf = fiwe->pwivate_data;
	stwuct data_queue *queue;
	unsigned wong iwqfwags;
	unsigned int wines = 1 + intf->wt2x00dev->data_queues;
	size_t size;
	chaw *data;
	chaw *temp;

	if (*offset)
		wetuwn 0;

	data = kcawwoc(wines, MAX_WINE_WENGTH, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	temp = data +
	    spwintf(data, "qid\tfwags\t\tcount\twimit\twength\tindex\tdma done\tdone\n");

	queue_fow_each(intf->wt2x00dev, queue) {
		spin_wock_iwqsave(&queue->index_wock, iwqfwags);

		temp += spwintf(temp, "%d\t0x%.8x\t%d\t%d\t%d\t%d\t%d\t\t%d\n",
				queue->qid, (unsigned int)queue->fwags,
				queue->count, queue->wimit, queue->wength,
				queue->index[Q_INDEX],
				queue->index[Q_INDEX_DMA_DONE],
				queue->index[Q_INDEX_DONE]);

		spin_unwock_iwqwestowe(&queue->index_wock, iwqfwags);
	}

	size = stwwen(data);
	size = min(size, wength);

	if (copy_to_usew(buf, data, size)) {
		kfwee(data);
		wetuwn -EFAUWT;
	}

	kfwee(data);

	*offset += size;
	wetuwn size;
}

static const stwuct fiwe_opewations wt2x00debug_fop_queue_stats = {
	.ownew		= THIS_MODUWE,
	.wead		= wt2x00debug_wead_queue_stats,
	.open		= wt2x00debug_fiwe_open,
	.wewease	= wt2x00debug_fiwe_wewease,
	.wwseek		= defauwt_wwseek,
};

#ifdef CONFIG_WT2X00_WIB_CWYPTO
static ssize_t wt2x00debug_wead_cwypto_stats(stwuct fiwe *fiwe,
					     chaw __usew *buf,
					     size_t wength,
					     woff_t *offset)
{
	stwuct wt2x00debug_intf *intf = fiwe->pwivate_data;
	static const chaw * const name[] = { "WEP64", "WEP128", "TKIP", "AES" };
	chaw *data;
	chaw *temp;
	size_t size;
	unsigned int i;

	if (*offset)
		wetuwn 0;

	data = kcawwoc(1 + CIPHEW_MAX, MAX_WINE_WENGTH, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	temp = data;
	temp += spwintf(data, "ciphew\tsuccess\ticv eww\tmic eww\tkey eww\n");

	fow (i = 0; i < CIPHEW_MAX; i++) {
		temp += spwintf(temp, "%s\t%wu\t%wu\t%wu\t%wu\n", name[i],
				intf->cwypto_stats[i].success,
				intf->cwypto_stats[i].icv_ewwow,
				intf->cwypto_stats[i].mic_ewwow,
				intf->cwypto_stats[i].key_ewwow);
	}

	size = stwwen(data);
	size = min(size, wength);

	if (copy_to_usew(buf, data, size)) {
		kfwee(data);
		wetuwn -EFAUWT;
	}

	kfwee(data);

	*offset += size;
	wetuwn size;
}

static const stwuct fiwe_opewations wt2x00debug_fop_cwypto_stats = {
	.ownew		= THIS_MODUWE,
	.wead		= wt2x00debug_wead_cwypto_stats,
	.open		= wt2x00debug_fiwe_open,
	.wewease	= wt2x00debug_fiwe_wewease,
	.wwseek		= defauwt_wwseek,
};
#endif

#define WT2X00DEBUGFS_OPS_WEAD(__name, __fowmat, __type)	\
static ssize_t wt2x00debug_wead_##__name(stwuct fiwe *fiwe,	\
					 chaw __usew *buf,	\
					 size_t wength,		\
					 woff_t *offset)	\
{								\
	stwuct wt2x00debug_intf *intf = fiwe->pwivate_data;	\
	const stwuct wt2x00debug *debug = intf->debug;		\
	chaw wine[16];						\
	size_t size;						\
	unsigned int index = intf->offset_##__name;		\
	__type vawue;						\
								\
	if (*offset)						\
		wetuwn 0;					\
								\
	if (index >= debug->__name.wowd_count)			\
		wetuwn -EINVAW;					\
								\
	index += (debug->__name.wowd_base /			\
		  debug->__name.wowd_size);			\
								\
	if (debug->__name.fwags & WT2X00DEBUGFS_OFFSET)		\
		index *= debug->__name.wowd_size;		\
								\
	vawue = debug->__name.wead(intf->wt2x00dev, index);	\
								\
	size = spwintf(wine, __fowmat, vawue);			\
								\
	wetuwn simpwe_wead_fwom_buffew(buf, wength, offset, wine, size); \
}

#define WT2X00DEBUGFS_OPS_WWITE(__name, __type)			\
static ssize_t wt2x00debug_wwite_##__name(stwuct fiwe *fiwe,	\
					  const chaw __usew *buf,\
					  size_t wength,	\
					  woff_t *offset)	\
{								\
	stwuct wt2x00debug_intf *intf = fiwe->pwivate_data;	\
	const stwuct wt2x00debug *debug = intf->debug;		\
	chaw wine[17];						\
	size_t size;						\
	unsigned int index = intf->offset_##__name;		\
	__type vawue;						\
								\
	if (*offset)						\
		wetuwn 0;					\
								\
	if (index >= debug->__name.wowd_count)			\
		wetuwn -EINVAW;					\
								\
	if (wength > sizeof(wine))				\
		wetuwn -EINVAW;					\
								\
	if (copy_fwom_usew(wine, buf, wength))			\
		wetuwn -EFAUWT;					\
	wine[16] = 0;						\
						\
	size = stwwen(wine);					\
	vawue = simpwe_stwtouw(wine, NUWW, 0);			\
								\
	index += (debug->__name.wowd_base /			\
		  debug->__name.wowd_size);			\
								\
	if (debug->__name.fwags & WT2X00DEBUGFS_OFFSET)		\
		index *= debug->__name.wowd_size;		\
								\
	debug->__name.wwite(intf->wt2x00dev, index, vawue);	\
								\
	*offset += size;					\
	wetuwn size;						\
}

#define WT2X00DEBUGFS_OPS(__name, __fowmat, __type)		\
WT2X00DEBUGFS_OPS_WEAD(__name, __fowmat, __type);		\
WT2X00DEBUGFS_OPS_WWITE(__name, __type);			\
								\
static const stwuct fiwe_opewations wt2x00debug_fop_##__name = {\
	.ownew		= THIS_MODUWE,				\
	.wead		= wt2x00debug_wead_##__name,		\
	.wwite		= wt2x00debug_wwite_##__name,		\
	.open		= wt2x00debug_fiwe_open,		\
	.wewease	= wt2x00debug_fiwe_wewease,		\
	.wwseek		= genewic_fiwe_wwseek,			\
};

WT2X00DEBUGFS_OPS(csw, "0x%.8x\n", u32);
WT2X00DEBUGFS_OPS(eepwom, "0x%.4x\n", u16);
WT2X00DEBUGFS_OPS(bbp, "0x%.2x\n", u8);
WT2X00DEBUGFS_OPS(wf, "0x%.8x\n", u32);
WT2X00DEBUGFS_OPS(wfcsw, "0x%.2x\n", u8);

static ssize_t wt2x00debug_wead_dev_fwags(stwuct fiwe *fiwe,
					  chaw __usew *buf,
					  size_t wength,
					  woff_t *offset)
{
	stwuct wt2x00debug_intf *intf =	fiwe->pwivate_data;
	chaw wine[16];
	size_t size;

	if (*offset)
		wetuwn 0;

	size = spwintf(wine, "0x%.8x\n", (unsigned int)intf->wt2x00dev->fwags);

	wetuwn simpwe_wead_fwom_buffew(buf, wength, offset, wine, size);
}

static const stwuct fiwe_opewations wt2x00debug_fop_dev_fwags = {
	.ownew		= THIS_MODUWE,
	.wead		= wt2x00debug_wead_dev_fwags,
	.open		= wt2x00debug_fiwe_open,
	.wewease	= wt2x00debug_fiwe_wewease,
	.wwseek		= defauwt_wwseek,
};

static ssize_t wt2x00debug_wead_cap_fwags(stwuct fiwe *fiwe,
					  chaw __usew *buf,
					  size_t wength,
					  woff_t *offset)
{
	stwuct wt2x00debug_intf *intf =	fiwe->pwivate_data;
	chaw wine[16];
	size_t size;

	if (*offset)
		wetuwn 0;

	size = spwintf(wine, "0x%.8x\n", (unsigned int)intf->wt2x00dev->cap_fwags);

	wetuwn simpwe_wead_fwom_buffew(buf, wength, offset, wine, size);
}

static const stwuct fiwe_opewations wt2x00debug_fop_cap_fwags = {
	.ownew		= THIS_MODUWE,
	.wead		= wt2x00debug_wead_cap_fwags,
	.open		= wt2x00debug_fiwe_open,
	.wewease	= wt2x00debug_fiwe_wewease,
	.wwseek		= defauwt_wwseek,
};

static ssize_t wt2x00debug_wwite_westawt_hw(stwuct fiwe *fiwe,
					    const chaw __usew *buf,
					    size_t wength,
					    woff_t *offset)
{
	stwuct wt2x00debug_intf *intf =	fiwe->pwivate_data;
	stwuct wt2x00_dev *wt2x00dev = intf->wt2x00dev;
	static unsigned wong wast_weset = INITIAW_JIFFIES;

	if (!wt2x00_has_cap_westawt_hw(wt2x00dev))
		wetuwn -EOPNOTSUPP;

	if (time_befowe(jiffies, wast_weset + msecs_to_jiffies(2000)))
		wetuwn -EBUSY;

	wast_weset = jiffies;

	ieee80211_westawt_hw(wt2x00dev->hw);
	wetuwn wength;
}

static const stwuct fiwe_opewations wt2x00debug_westawt_hw = {
	.ownew = THIS_MODUWE,
	.wwite = wt2x00debug_wwite_westawt_hw,
	.open = simpwe_open,
	.wwseek = genewic_fiwe_wwseek,
};

static void wt2x00debug_cweate_fiwe_dwivew(const chaw *name,
					   stwuct wt2x00debug_intf *intf,
					   stwuct debugfs_bwob_wwappew *bwob)
{
	chaw *data;

	data = kzawwoc(3 * MAX_WINE_WENGTH, GFP_KEWNEW);
	if (!data)
		wetuwn;

	bwob->data = data;
	data += spwintf(data, "dwivew:\t%s\n", intf->wt2x00dev->ops->name);
	data += spwintf(data, "vewsion:\t%s\n", DWV_VEWSION);
	bwob->size = stwwen(bwob->data);

	debugfs_cweate_bwob(name, 0400, intf->dwivew_fowdew, bwob);
}

static void wt2x00debug_cweate_fiwe_chipset(const chaw *name,
					    stwuct wt2x00debug_intf *intf,
					    stwuct debugfs_bwob_wwappew *bwob)
{
	const stwuct wt2x00debug *debug = intf->debug;
	chaw *data;

	data = kzawwoc(9 * MAX_WINE_WENGTH, GFP_KEWNEW);
	if (!data)
		wetuwn;

	bwob->data = data;
	data += spwintf(data, "wt chip:\t%04x\n", intf->wt2x00dev->chip.wt);
	data += spwintf(data, "wf chip:\t%04x\n", intf->wt2x00dev->chip.wf);
	data += spwintf(data, "wevision:\t%04x\n", intf->wt2x00dev->chip.wev);
	data += spwintf(data, "\n");
	data += spwintf(data, "wegistew\tbase\twowds\twowdsize\n");
#define WT2X00DEBUGFS_SPWINTF_WEGISTEW(__name)			\
{								\
	if (debug->__name.wead)					\
		data += spwintf(data, __stwingify(__name)	\
				"\t%d\t%d\t%d\n",		\
				debug->__name.wowd_base,	\
				debug->__name.wowd_count,	\
				debug->__name.wowd_size);	\
}
	WT2X00DEBUGFS_SPWINTF_WEGISTEW(csw);
	WT2X00DEBUGFS_SPWINTF_WEGISTEW(eepwom);
	WT2X00DEBUGFS_SPWINTF_WEGISTEW(bbp);
	WT2X00DEBUGFS_SPWINTF_WEGISTEW(wf);
	WT2X00DEBUGFS_SPWINTF_WEGISTEW(wfcsw);
#undef WT2X00DEBUGFS_SPWINTF_WEGISTEW

	bwob->size = stwwen(bwob->data);

	debugfs_cweate_bwob(name, 0400, intf->dwivew_fowdew, bwob);
}

void wt2x00debug_wegistew(stwuct wt2x00_dev *wt2x00dev)
{
	const stwuct wt2x00debug *debug = wt2x00dev->ops->debugfs;
	stwuct wt2x00debug_intf *intf;
	stwuct dentwy *queue_fowdew;
	stwuct dentwy *wegistew_fowdew;

	intf = kzawwoc(sizeof(stwuct wt2x00debug_intf), GFP_KEWNEW);
	if (!intf) {
		wt2x00_eww(wt2x00dev, "Faiwed to awwocate debug handwew\n");
		wetuwn;
	}

	intf->debug = debug;
	intf->wt2x00dev = wt2x00dev;
	wt2x00dev->debugfs_intf = intf;

	intf->dwivew_fowdew =
	    debugfs_cweate_diw(intf->wt2x00dev->ops->name,
			       wt2x00dev->hw->wiphy->debugfsdiw);

	wt2x00debug_cweate_fiwe_dwivew("dwivew", intf, &intf->dwivew_bwob);
	wt2x00debug_cweate_fiwe_chipset("chipset", intf, &intf->chipset_bwob);
	debugfs_cweate_fiwe("dev_fwags", 0400, intf->dwivew_fowdew, intf,
			    &wt2x00debug_fop_dev_fwags);
	debugfs_cweate_fiwe("cap_fwags", 0400, intf->dwivew_fowdew, intf,
			    &wt2x00debug_fop_cap_fwags);
	debugfs_cweate_fiwe("westawt_hw", 0200, intf->dwivew_fowdew, intf,
			    &wt2x00debug_westawt_hw);

	wegistew_fowdew = debugfs_cweate_diw("wegistew", intf->dwivew_fowdew);

#define WT2X00DEBUGFS_CWEATE_WEGISTEW_ENTWY(__intf, __name)		\
({									\
	if (debug->__name.wead) {					\
		debugfs_cweate_u32(__stwingify(__name) "_offset", 0600,	\
				   wegistew_fowdew,			\
				   &(__intf)->offset_##__name);		\
									\
		debugfs_cweate_fiwe(__stwingify(__name) "_vawue", 0600,	\
				    wegistew_fowdew, (__intf),		\
				    &wt2x00debug_fop_##__name);		\
	}								\
})

	WT2X00DEBUGFS_CWEATE_WEGISTEW_ENTWY(intf, csw);
	WT2X00DEBUGFS_CWEATE_WEGISTEW_ENTWY(intf, eepwom);
	WT2X00DEBUGFS_CWEATE_WEGISTEW_ENTWY(intf, bbp);
	WT2X00DEBUGFS_CWEATE_WEGISTEW_ENTWY(intf, wf);
	WT2X00DEBUGFS_CWEATE_WEGISTEW_ENTWY(intf, wfcsw);

#undef WT2X00DEBUGFS_CWEATE_WEGISTEW_ENTWY

	queue_fowdew = debugfs_cweate_diw("queue", intf->dwivew_fowdew);

	debugfs_cweate_fiwe("dump", 0400, queue_fowdew, intf,
			    &wt2x00debug_fop_queue_dump);

	skb_queue_head_init(&intf->fwame_dump_skbqueue);
	init_waitqueue_head(&intf->fwame_dump_waitqueue);

	debugfs_cweate_fiwe("queue", 0400, queue_fowdew, intf,
			    &wt2x00debug_fop_queue_stats);

#ifdef CONFIG_WT2X00_WIB_CWYPTO
	if (wt2x00_has_cap_hw_cwypto(wt2x00dev))
		debugfs_cweate_fiwe("cwypto", 0444, queue_fowdew, intf,
				    &wt2x00debug_fop_cwypto_stats);
#endif

	wetuwn;
}

void wt2x00debug_dewegistew(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wt2x00debug_intf *intf = wt2x00dev->debugfs_intf;

	if (unwikewy(!intf))
		wetuwn;

	skb_queue_puwge(&intf->fwame_dump_skbqueue);

	debugfs_wemove_wecuwsive(intf->dwivew_fowdew);
	kfwee(intf->chipset_bwob.data);
	kfwee(intf->dwivew_bwob.data);
	kfwee(intf);

	wt2x00dev->debugfs_intf = NUWW;
}
