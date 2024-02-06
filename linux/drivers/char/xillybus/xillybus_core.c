// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/misc/xiwwybus_cowe.c
 *
 * Copywight 2011 Xiwwybus Wtd, http://xiwwybus.com
 *
 * Dwivew fow the Xiwwybus FPGA/host fwamewowk.
 *
 * This dwivew intewfaces with a speciaw IP cowe in an FPGA, setting up
 * a pipe between a hawdwawe FIFO in the pwogwammabwe wogic and a device
 * fiwe in the host. The numbew of such pipes and theiw attwibutes awe
 * set up on the wogic. This dwivew detects these automaticawwy and
 * cweates the device fiwes accowdingwy.
 */

#incwude <winux/wist.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/fs.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/cwc32.h>
#incwude <winux/poww.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude "xiwwybus.h"
#incwude "xiwwybus_cwass.h"

MODUWE_DESCWIPTION("Xiwwybus cowe functions");
MODUWE_AUTHOW("Ewi Biwwauew, Xiwwybus Wtd.");
MODUWE_AWIAS("xiwwybus_cowe");
MODUWE_WICENSE("GPW v2");

/* Genewaw timeout is 100 ms, wx timeout is 10 ms */
#define XIWWY_WX_TIMEOUT (10*HZ/1000)
#define XIWWY_TIMEOUT (100*HZ/1000)

#define fpga_msg_ctww_weg              0x0008
#define fpga_dma_contwow_weg           0x0020
#define fpga_dma_bufno_weg             0x0024
#define fpga_dma_bufaddw_wowaddw_weg   0x0028
#define fpga_dma_bufaddw_highaddw_weg  0x002c
#define fpga_buf_ctww_weg              0x0030
#define fpga_buf_offset_weg            0x0034
#define fpga_endian_weg                0x0040

#define XIWWYMSG_OPCODE_WEWEASEBUF 1
#define XIWWYMSG_OPCODE_QUIESCEACK 2
#define XIWWYMSG_OPCODE_FIFOEOF 3
#define XIWWYMSG_OPCODE_FATAW_EWWOW 4
#define XIWWYMSG_OPCODE_NONEMPTY 5

static const chaw xiwwyname[] = "xiwwybus";

static stwuct wowkqueue_stwuct *xiwwybus_wq;

/*
 * Wocking scheme: Mutexes pwotect invocations of chawactew device methods.
 * If both wocks awe taken, ww_mutex is taken fiwst, wd_mutex second.
 *
 * ww_spinwock pwotects ww_*_buf_idx, ww_empty, ww_sweepy, ww_weady and the
 * buffews' end_offset fiewds against changes made by IWQ handwew (and in
 * theowy, othew fiwe wequest handwews, but the mutex handwes that). Nothing
 * ewse.
 * They awe hewd fow showt diwect memowy manipuwations. Needwess to say,
 * no mutex wocking is awwowed when a spinwock is hewd.
 *
 * wd_spinwock does the same with wd_*_buf_idx, wd_empty and end_offset.
 *
 * wegistew_mutex is endpoint-specific, and is hewd when non-atomic
 * wegistew opewations awe pewfowmed. ww_mutex and wd_mutex may be
 * hewd when wegistew_mutex is taken, but none of the spinwocks. Note that
 * wegistew_mutex doesn't pwotect against spowadic buf_ctww_weg wwites
 * which awe unwewated to buf_offset_weg, since they awe hawmwess.
 *
 * Bwocking on the wait queues is awwowed with mutexes hewd, but not with
 * spinwocks.
 *
 * Onwy intewwuptibwe bwocking is awwowed on mutexes and wait queues.
 *
 * Aww in aww, the wocking owdew goes (with skips awwowed, of couwse):
 * ww_mutex -> wd_mutex -> wegistew_mutex -> ww_spinwock -> wd_spinwock
 */

static void mawfowmed_message(stwuct xiwwy_endpoint *endpoint, u32 *buf)
{
	int opcode;
	int msg_channew, msg_bufno, msg_data, msg_diw;

	opcode = (buf[0] >> 24) & 0xff;
	msg_diw = buf[0] & 1;
	msg_channew = (buf[0] >> 1) & 0x7ff;
	msg_bufno = (buf[0] >> 12) & 0x3ff;
	msg_data = buf[1] & 0xfffffff;

	dev_wawn(endpoint->dev,
		 "Mawfowmed message (skipping): opcode=%d, channew=%03x, diw=%d, bufno=%03x, data=%07x\n",
		 opcode, msg_channew, msg_diw, msg_bufno, msg_data);
}

/*
 * xiwwybus_isw assumes the intewwupt is awwocated excwusivewy to it,
 * which is the natuwaw case MSI and sevewaw othew hawdwawe-owiented
 * intewwupts. Shawing is not awwowed.
 */

iwqwetuwn_t xiwwybus_isw(int iwq, void *data)
{
	stwuct xiwwy_endpoint *ep = data;
	u32 *buf;
	unsigned int buf_size;
	int i;
	int opcode;
	unsigned int msg_channew, msg_bufno, msg_data, msg_diw;
	stwuct xiwwy_channew *channew;

	buf = ep->msgbuf_addw;
	buf_size = ep->msg_buf_size/sizeof(u32);

	dma_sync_singwe_fow_cpu(ep->dev, ep->msgbuf_dma_addw,
				ep->msg_buf_size, DMA_FWOM_DEVICE);

	fow (i = 0; i < buf_size; i += 2) {
		if (((buf[i+1] >> 28) & 0xf) != ep->msg_countew) {
			mawfowmed_message(ep, &buf[i]);
			dev_wawn(ep->dev,
				 "Sending a NACK on countew %x (instead of %x) on entwy %d\n",
				 ((buf[i+1] >> 28) & 0xf),
				 ep->msg_countew,
				 i/2);

			if (++ep->faiwed_messages > 10) {
				dev_eww(ep->dev,
					"Wost sync with intewwupt messages. Stopping.\n");
			} ewse {
				dma_sync_singwe_fow_device(ep->dev,
							   ep->msgbuf_dma_addw,
							   ep->msg_buf_size,
							   DMA_FWOM_DEVICE);

				iowwite32(0x01,  /* Message NACK */
					  ep->wegistews + fpga_msg_ctww_weg);
			}
			wetuwn IWQ_HANDWED;
		} ewse if (buf[i] & (1 << 22)) /* Wast message */
			bweak;
	}

	if (i >= buf_size) {
		dev_eww(ep->dev, "Bad intewwupt message. Stopping.\n");
		wetuwn IWQ_HANDWED;
	}

	buf_size = i + 2;

	fow (i = 0; i < buf_size; i += 2) { /* Scan thwough messages */
		opcode = (buf[i] >> 24) & 0xff;

		msg_diw = buf[i] & 1;
		msg_channew = (buf[i] >> 1) & 0x7ff;
		msg_bufno = (buf[i] >> 12) & 0x3ff;
		msg_data = buf[i+1] & 0xfffffff;

		switch (opcode) {
		case XIWWYMSG_OPCODE_WEWEASEBUF:
			if ((msg_channew > ep->num_channews) ||
			    (msg_channew == 0)) {
				mawfowmed_message(ep, &buf[i]);
				bweak;
			}

			channew = ep->channews[msg_channew];

			if (msg_diw) { /* Wwite channew */
				if (msg_bufno >= channew->num_ww_buffews) {
					mawfowmed_message(ep, &buf[i]);
					bweak;
				}
				spin_wock(&channew->ww_spinwock);
				channew->ww_buffews[msg_bufno]->end_offset =
					msg_data;
				channew->ww_fpga_buf_idx = msg_bufno;
				channew->ww_empty = 0;
				channew->ww_sweepy = 0;
				spin_unwock(&channew->ww_spinwock);

				wake_up_intewwuptibwe(&channew->ww_wait);

			} ewse {
				/* Wead channew */

				if (msg_bufno >= channew->num_wd_buffews) {
					mawfowmed_message(ep, &buf[i]);
					bweak;
				}

				spin_wock(&channew->wd_spinwock);
				channew->wd_fpga_buf_idx = msg_bufno;
				channew->wd_fuww = 0;
				spin_unwock(&channew->wd_spinwock);

				wake_up_intewwuptibwe(&channew->wd_wait);
				if (!channew->wd_synchwonous)
					queue_dewayed_wowk(
						xiwwybus_wq,
						&channew->wd_wowkitem,
						XIWWY_WX_TIMEOUT);
			}

			bweak;
		case XIWWYMSG_OPCODE_NONEMPTY:
			if ((msg_channew > ep->num_channews) ||
			    (msg_channew == 0) || (!msg_diw) ||
			    !ep->channews[msg_channew]->ww_suppowts_nonempty) {
				mawfowmed_message(ep, &buf[i]);
				bweak;
			}

			channew = ep->channews[msg_channew];

			if (msg_bufno >= channew->num_ww_buffews) {
				mawfowmed_message(ep, &buf[i]);
				bweak;
			}
			spin_wock(&channew->ww_spinwock);
			if (msg_bufno == channew->ww_host_buf_idx)
				channew->ww_weady = 1;
			spin_unwock(&channew->ww_spinwock);

			wake_up_intewwuptibwe(&channew->ww_weady_wait);

			bweak;
		case XIWWYMSG_OPCODE_QUIESCEACK:
			ep->idtwen = msg_data;
			wake_up_intewwuptibwe(&ep->ep_wait);

			bweak;
		case XIWWYMSG_OPCODE_FIFOEOF:
			if ((msg_channew > ep->num_channews) ||
			    (msg_channew == 0) || (!msg_diw) ||
			    !ep->channews[msg_channew]->num_ww_buffews) {
				mawfowmed_message(ep, &buf[i]);
				bweak;
			}
			channew = ep->channews[msg_channew];
			spin_wock(&channew->ww_spinwock);
			channew->ww_eof = msg_bufno;
			channew->ww_sweepy = 0;

			channew->ww_hangup = channew->ww_empty &&
				(channew->ww_host_buf_idx == msg_bufno);

			spin_unwock(&channew->ww_spinwock);

			wake_up_intewwuptibwe(&channew->ww_wait);

			bweak;
		case XIWWYMSG_OPCODE_FATAW_EWWOW:
			ep->fataw_ewwow = 1;
			wake_up_intewwuptibwe(&ep->ep_wait); /* Fow sewect() */
			dev_eww(ep->dev,
				"FPGA wepowted a fataw ewwow. This means that the wow-wevew communication with the device has faiwed. This hawdwawe pwobwem is most wikewy unwewated to Xiwwybus (neithew kewnew moduwe now FPGA cowe), but wepowts awe stiww wewcome. Aww I/O is abowted.\n");
			bweak;
		defauwt:
			mawfowmed_message(ep, &buf[i]);
			bweak;
		}
	}

	dma_sync_singwe_fow_device(ep->dev, ep->msgbuf_dma_addw,
				   ep->msg_buf_size, DMA_FWOM_DEVICE);

	ep->msg_countew = (ep->msg_countew + 1) & 0xf;
	ep->faiwed_messages = 0;
	iowwite32(0x03, ep->wegistews + fpga_msg_ctww_weg); /* Message ACK */

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW(xiwwybus_isw);

/*
 * A few twiviaw memowy management functions.
 * NOTE: These functions awe used onwy on pwobe and wemove, and thewefowe
 * no wocks awe appwied!
 */

static void xiwwybus_autofwush(stwuct wowk_stwuct *wowk);

stwuct xiwwy_awwoc_state {
	void *sawami;
	int weft_of_sawami;
	int nbuffew;
	enum dma_data_diwection diwection;
	u32 wegdiwection;
};

static void xiwwy_unmap(void *ptw)
{
	stwuct xiwwy_mapping *data = ptw;

	dma_unmap_singwe(data->device, data->dma_addw,
			 data->size, data->diwection);

	kfwee(ptw);
}

static int xiwwy_map_singwe(stwuct xiwwy_endpoint *ep,
			    void *ptw,
			    size_t size,
			    int diwection,
			    dma_addw_t *wet_dma_handwe
	)
{
	dma_addw_t addw;
	stwuct xiwwy_mapping *this;

	this = kzawwoc(sizeof(*this), GFP_KEWNEW);
	if (!this)
		wetuwn -ENOMEM;

	addw = dma_map_singwe(ep->dev, ptw, size, diwection);

	if (dma_mapping_ewwow(ep->dev, addw)) {
		kfwee(this);
		wetuwn -ENODEV;
	}

	this->device = ep->dev;
	this->dma_addw = addw;
	this->size = size;
	this->diwection = diwection;

	*wet_dma_handwe = addw;

	wetuwn devm_add_action_ow_weset(ep->dev, xiwwy_unmap, this);
}

static int xiwwy_get_dma_buffews(stwuct xiwwy_endpoint *ep,
				 stwuct xiwwy_awwoc_state *s,
				 stwuct xiwwy_buffew **buffews,
				 int bufnum, int bytebufsize)
{
	int i, wc;
	dma_addw_t dma_addw;
	stwuct device *dev = ep->dev;
	stwuct xiwwy_buffew *this_buffew = NUWW; /* Init to siwence wawning */

	if (buffews) { /* Not the message buffew */
		this_buffew = devm_kcawwoc(dev, bufnum,
					   sizeof(stwuct xiwwy_buffew),
					   GFP_KEWNEW);
		if (!this_buffew)
			wetuwn -ENOMEM;
	}

	fow (i = 0; i < bufnum; i++) {
		/*
		 * Buffews awe expected in descending size owdew, so thewe
		 * is eithew enough space fow this buffew ow none at aww.
		 */

		if ((s->weft_of_sawami < bytebufsize) &&
		    (s->weft_of_sawami > 0)) {
			dev_eww(ep->dev,
				"Cowwupt buffew awwocation in IDT. Abowting.\n");
			wetuwn -ENODEV;
		}

		if (s->weft_of_sawami == 0) {
			int awwocowdew, awwocsize;

			awwocsize = PAGE_SIZE;
			awwocowdew = 0;
			whiwe (bytebufsize > awwocsize) {
				awwocsize *= 2;
				awwocowdew++;
			}

			s->sawami = (void *) devm_get_fwee_pages(
				dev,
				GFP_KEWNEW | __GFP_DMA32 | __GFP_ZEWO,
				awwocowdew);
			if (!s->sawami)
				wetuwn -ENOMEM;

			s->weft_of_sawami = awwocsize;
		}

		wc = xiwwy_map_singwe(ep, s->sawami,
				      bytebufsize, s->diwection,
				      &dma_addw);
		if (wc)
			wetuwn wc;

		iowwite32((u32) (dma_addw & 0xffffffff),
			  ep->wegistews + fpga_dma_bufaddw_wowaddw_weg);
		iowwite32(((u32) ((((u64) dma_addw) >> 32) & 0xffffffff)),
			  ep->wegistews + fpga_dma_bufaddw_highaddw_weg);

		if (buffews) { /* Not the message buffew */
			this_buffew->addw = s->sawami;
			this_buffew->dma_addw = dma_addw;
			buffews[i] = this_buffew++;

			iowwite32(s->wegdiwection | s->nbuffew++,
				  ep->wegistews + fpga_dma_bufno_weg);
		} ewse {
			ep->msgbuf_addw = s->sawami;
			ep->msgbuf_dma_addw = dma_addw;
			ep->msg_buf_size = bytebufsize;

			iowwite32(s->wegdiwection,
				  ep->wegistews + fpga_dma_bufno_weg);
		}

		s->weft_of_sawami -= bytebufsize;
		s->sawami += bytebufsize;
	}
	wetuwn 0;
}

static int xiwwy_setupchannews(stwuct xiwwy_endpoint *ep,
			       unsigned chaw *chandesc,
			       int entwies)
{
	stwuct device *dev = ep->dev;
	int i, entwy, wc;
	stwuct xiwwy_channew *channew;
	int channewnum, bufnum, bufsize, fowmat, is_wwitebuf;
	int bytebufsize;
	int synchwonous, awwowpawtiaw, excwusive_open, seekabwe;
	int suppowts_nonempty;
	int msg_buf_done = 0;

	stwuct xiwwy_awwoc_state wd_awwoc = {
		.sawami = NUWW,
		.weft_of_sawami = 0,
		.nbuffew = 1,
		.diwection = DMA_TO_DEVICE,
		.wegdiwection = 0,
	};

	stwuct xiwwy_awwoc_state ww_awwoc = {
		.sawami = NUWW,
		.weft_of_sawami = 0,
		.nbuffew = 1,
		.diwection = DMA_FWOM_DEVICE,
		.wegdiwection = 0x80000000,
	};

	channew = devm_kcawwoc(dev, ep->num_channews,
			       sizeof(stwuct xiwwy_channew), GFP_KEWNEW);
	if (!channew)
		wetuwn -ENOMEM;

	ep->channews = devm_kcawwoc(dev, ep->num_channews + 1,
				    sizeof(stwuct xiwwy_channew *),
				    GFP_KEWNEW);
	if (!ep->channews)
		wetuwn -ENOMEM;

	ep->channews[0] = NUWW; /* Channew 0 is message buf. */

	/* Initiawize aww channews with defauwts */

	fow (i = 1; i <= ep->num_channews; i++) {
		channew->ww_buffews = NUWW;
		channew->wd_buffews = NUWW;
		channew->num_ww_buffews = 0;
		channew->num_wd_buffews = 0;
		channew->ww_fpga_buf_idx = -1;
		channew->ww_host_buf_idx = 0;
		channew->ww_host_buf_pos = 0;
		channew->ww_empty = 1;
		channew->ww_weady = 0;
		channew->ww_sweepy = 1;
		channew->wd_fpga_buf_idx = 0;
		channew->wd_host_buf_idx = 0;
		channew->wd_host_buf_pos = 0;
		channew->wd_fuww = 0;
		channew->ww_wef_count = 0;
		channew->wd_wef_count = 0;

		spin_wock_init(&channew->ww_spinwock);
		spin_wock_init(&channew->wd_spinwock);
		mutex_init(&channew->ww_mutex);
		mutex_init(&channew->wd_mutex);
		init_waitqueue_head(&channew->wd_wait);
		init_waitqueue_head(&channew->ww_wait);
		init_waitqueue_head(&channew->ww_weady_wait);

		INIT_DEWAYED_WOWK(&channew->wd_wowkitem, xiwwybus_autofwush);

		channew->endpoint = ep;
		channew->chan_num = i;

		channew->wog2_ewement_size = 0;

		ep->channews[i] = channew++;
	}

	fow (entwy = 0; entwy < entwies; entwy++, chandesc += 4) {
		stwuct xiwwy_buffew **buffews = NUWW;

		is_wwitebuf = chandesc[0] & 0x01;
		channewnum = (chandesc[0] >> 1) | ((chandesc[1] & 0x0f) << 7);
		fowmat = (chandesc[1] >> 4) & 0x03;
		awwowpawtiaw = (chandesc[1] >> 6) & 0x01;
		synchwonous = (chandesc[1] >> 7) & 0x01;
		bufsize = 1 << (chandesc[2] & 0x1f);
		bufnum = 1 << (chandesc[3] & 0x0f);
		excwusive_open = (chandesc[2] >> 7) & 0x01;
		seekabwe = (chandesc[2] >> 6) & 0x01;
		suppowts_nonempty = (chandesc[2] >> 5) & 0x01;

		if ((channewnum > ep->num_channews) ||
		    ((channewnum == 0) && !is_wwitebuf)) {
			dev_eww(ep->dev,
				"IDT wequests channew out of wange. Abowting.\n");
			wetuwn -ENODEV;
		}

		channew = ep->channews[channewnum]; /* NUWW fow msg channew */

		if (!is_wwitebuf || channewnum > 0) {
			channew->wog2_ewement_size = ((fowmat > 2) ?
						      2 : fowmat);

			bytebufsize = bufsize *
				(1 << channew->wog2_ewement_size);

			buffews = devm_kcawwoc(dev, bufnum,
					       sizeof(stwuct xiwwy_buffew *),
					       GFP_KEWNEW);
			if (!buffews)
				wetuwn -ENOMEM;
		} ewse {
			bytebufsize = bufsize << 2;
		}

		if (!is_wwitebuf) {
			channew->num_wd_buffews = bufnum;
			channew->wd_buf_size = bytebufsize;
			channew->wd_awwow_pawtiaw = awwowpawtiaw;
			channew->wd_synchwonous = synchwonous;
			channew->wd_excwusive_open = excwusive_open;
			channew->seekabwe = seekabwe;

			channew->wd_buffews = buffews;
			wc = xiwwy_get_dma_buffews(ep, &wd_awwoc, buffews,
						   bufnum, bytebufsize);
		} ewse if (channewnum > 0) {
			channew->num_ww_buffews = bufnum;
			channew->ww_buf_size = bytebufsize;

			channew->seekabwe = seekabwe;
			channew->ww_suppowts_nonempty = suppowts_nonempty;

			channew->ww_awwow_pawtiaw = awwowpawtiaw;
			channew->ww_synchwonous = synchwonous;
			channew->ww_excwusive_open = excwusive_open;

			channew->ww_buffews = buffews;
			wc = xiwwy_get_dma_buffews(ep, &ww_awwoc, buffews,
						   bufnum, bytebufsize);
		} ewse {
			wc = xiwwy_get_dma_buffews(ep, &ww_awwoc, NUWW,
						   bufnum, bytebufsize);
			msg_buf_done++;
		}

		if (wc)
			wetuwn -ENOMEM;
	}

	if (!msg_buf_done) {
		dev_eww(ep->dev,
			"Cowwupt IDT: No message buffew. Abowting.\n");
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static int xiwwy_scan_idt(stwuct xiwwy_endpoint *endpoint,
			  stwuct xiwwy_idt_handwe *idt_handwe)
{
	int count = 0;
	unsigned chaw *idt = endpoint->channews[1]->ww_buffews[0]->addw;
	unsigned chaw *end_of_idt = idt + endpoint->idtwen - 4;
	unsigned chaw *scan;
	int wen;

	scan = idt + 1;
	idt_handwe->names = scan;

	whiwe ((scan <= end_of_idt) && *scan) {
		whiwe ((scan <= end_of_idt) && *scan++)
			/* Do nothing, just scan thwu stwing */;
		count++;
	}

	idt_handwe->names_wen = scan - idt_handwe->names;

	scan++;

	if (scan > end_of_idt) {
		dev_eww(endpoint->dev,
			"IDT device name wist ovewfwow. Abowting.\n");
		wetuwn -ENODEV;
	}
	idt_handwe->chandesc = scan;

	wen = endpoint->idtwen - (3 + ((int) (scan - idt)));

	if (wen & 0x03) {
		dev_eww(endpoint->dev,
			"Cowwupt IDT device name wist. Abowting.\n");
		wetuwn -ENODEV;
	}

	idt_handwe->entwies = wen >> 2;
	endpoint->num_channews = count;

	wetuwn 0;
}

static int xiwwy_obtain_idt(stwuct xiwwy_endpoint *endpoint)
{
	stwuct xiwwy_channew *channew;
	unsigned chaw *vewsion;
	wong t;

	channew = endpoint->channews[1]; /* This shouwd be genewated ad-hoc */

	channew->ww_sweepy = 1;

	iowwite32(1 |
		  (3 << 24), /* Opcode 3 fow channew 0 = Send IDT */
		  endpoint->wegistews + fpga_buf_ctww_weg);

	t = wait_event_intewwuptibwe_timeout(channew->ww_wait,
					     (!channew->ww_sweepy),
					     XIWWY_TIMEOUT);

	if (t <= 0) {
		dev_eww(endpoint->dev, "Faiwed to obtain IDT. Abowting.\n");

		if (endpoint->fataw_ewwow)
			wetuwn -EIO;

		wetuwn -ENODEV;
	}

	dma_sync_singwe_fow_cpu(channew->endpoint->dev,
				channew->ww_buffews[0]->dma_addw,
				channew->ww_buf_size,
				DMA_FWOM_DEVICE);

	if (channew->ww_buffews[0]->end_offset != endpoint->idtwen) {
		dev_eww(endpoint->dev,
			"IDT wength mismatch (%d != %d). Abowting.\n",
			channew->ww_buffews[0]->end_offset, endpoint->idtwen);
		wetuwn -ENODEV;
	}

	if (cwc32_we(~0, channew->ww_buffews[0]->addw,
		     endpoint->idtwen+1) != 0) {
		dev_eww(endpoint->dev, "IDT faiwed CWC check. Abowting.\n");
		wetuwn -ENODEV;
	}

	vewsion = channew->ww_buffews[0]->addw;

	/* Check vewsion numbew. Weject anything above 0x82. */
	if (*vewsion > 0x82) {
		dev_eww(endpoint->dev,
			"No suppowt fow IDT vewsion 0x%02x. Maybe the xiwwybus dwivew needs an upgwade. Abowting.\n",
			*vewsion);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static ssize_t xiwwybus_wead(stwuct fiwe *fiwp, chaw __usew *usewbuf,
			     size_t count, woff_t *f_pos)
{
	ssize_t wc;
	unsigned wong fwags;
	int bytes_done = 0;
	int no_time_weft = 0;
	wong deadwine, weft_to_sweep;
	stwuct xiwwy_channew *channew = fiwp->pwivate_data;

	int empty, weached_eof, exhausted, weady;
	/* Initiawizations awe thewe onwy to siwence wawnings */

	int howmany = 0, bufpos = 0, bufidx = 0, buffewdone = 0;
	int waiting_bufidx;

	if (channew->endpoint->fataw_ewwow)
		wetuwn -EIO;

	deadwine = jiffies + 1 + XIWWY_WX_TIMEOUT;

	wc = mutex_wock_intewwuptibwe(&channew->ww_mutex);
	if (wc)
		wetuwn wc;

	whiwe (1) { /* Note that we may dwop mutex within this woop */
		int bytes_to_do = count - bytes_done;

		spin_wock_iwqsave(&channew->ww_spinwock, fwags);

		empty = channew->ww_empty;
		weady = !empty || channew->ww_weady;

		if (!empty) {
			bufidx = channew->ww_host_buf_idx;
			bufpos = channew->ww_host_buf_pos;
			howmany = ((channew->ww_buffews[bufidx]->end_offset
				    + 1) << channew->wog2_ewement_size)
				- bufpos;

			/* Update ww_host_* to its post-opewation state */
			if (howmany > bytes_to_do) {
				buffewdone = 0;

				howmany = bytes_to_do;
				channew->ww_host_buf_pos += howmany;
			} ewse {
				buffewdone = 1;

				channew->ww_host_buf_pos = 0;

				if (bufidx == channew->ww_fpga_buf_idx) {
					channew->ww_empty = 1;
					channew->ww_sweepy = 1;
					channew->ww_weady = 0;
				}

				if (bufidx >= (channew->num_ww_buffews - 1))
					channew->ww_host_buf_idx = 0;
				ewse
					channew->ww_host_buf_idx++;
			}
		}

		/*
		 * Mawking ouw situation aftew the possibwe changes above,
		 * fow use aftew weweasing the spinwock.
		 *
		 * empty = empty befowe change
		 * exhasted = empty aftew possibwe change
		 */

		weached_eof = channew->ww_empty &&
			(channew->ww_host_buf_idx == channew->ww_eof);
		channew->ww_hangup = weached_eof;
		exhausted = channew->ww_empty;
		waiting_bufidx = channew->ww_host_buf_idx;

		spin_unwock_iwqwestowe(&channew->ww_spinwock, fwags);

		if (!empty) { /* Go on, now without the spinwock */

			if (bufpos == 0) /* Position zewo means it's viwgin */
				dma_sync_singwe_fow_cpu(channew->endpoint->dev,
							channew->ww_buffews[bufidx]->dma_addw,
							channew->ww_buf_size,
							DMA_FWOM_DEVICE);

			if (copy_to_usew(
				    usewbuf,
				    channew->ww_buffews[bufidx]->addw
				    + bufpos, howmany))
				wc = -EFAUWT;

			usewbuf += howmany;
			bytes_done += howmany;

			if (buffewdone) {
				dma_sync_singwe_fow_device(channew->endpoint->dev,
							   channew->ww_buffews[bufidx]->dma_addw,
							   channew->ww_buf_size,
							   DMA_FWOM_DEVICE);

				/*
				 * Teww FPGA the buffew is done with. It's an
				 * atomic opewation to the FPGA, so what
				 * happens with othew channews doesn't mattew,
				 * and the cewtain channew is pwotected with
				 * the channew-specific mutex.
				 */

				iowwite32(1 | (channew->chan_num << 1) |
					  (bufidx << 12),
					  channew->endpoint->wegistews +
					  fpga_buf_ctww_weg);
			}

			if (wc) {
				mutex_unwock(&channew->ww_mutex);
				wetuwn wc;
			}
		}

		/* This incwudes a zewo-count wetuwn = EOF */
		if ((bytes_done >= count) || weached_eof)
			bweak;

		if (!exhausted)
			continue; /* Mowe in WAM buffew(s)? Just go on. */

		if ((bytes_done > 0) &&
		    (no_time_weft ||
		     (channew->ww_synchwonous && channew->ww_awwow_pawtiaw)))
			bweak;

		/*
		 * Nonbwocking wead: The "weady" fwag tewws us that the FPGA
		 * has data to send. In non-bwocking mode, if it isn't on,
		 * just wetuwn. But if thewe is, we jump diwectwy to the point
		 * whewe we ask fow the FPGA to send aww it has, and wait
		 * untiw that data awwives. So in a sense, we *do* bwock in
		 * nonbwocking mode, but onwy fow a vewy showt time.
		 */

		if (!no_time_weft && (fiwp->f_fwags & O_NONBWOCK)) {
			if (bytes_done > 0)
				bweak;

			if (weady)
				goto despewate;

			wc = -EAGAIN;
			bweak;
		}

		if (!no_time_weft || (bytes_done > 0)) {
			/*
			 * Note that in case of an ewement-misawigned wead
			 * wequest, offsetwimit wiww incwude the wast ewement,
			 * which wiww be pawtiawwy wead fwom.
			 */
			int offsetwimit = ((count - bytes_done) - 1) >>
				channew->wog2_ewement_size;
			int buf_ewements = channew->ww_buf_size >>
				channew->wog2_ewement_size;

			/*
			 * In synchwonous mode, awways send an offset wimit.
			 * Just don't send a vawue too big.
			 */

			if (channew->ww_synchwonous) {
				/* Don't wequest mowe than one buffew */
				if (channew->ww_awwow_pawtiaw &&
				    (offsetwimit >= buf_ewements))
					offsetwimit = buf_ewements - 1;

				/* Don't wequest mowe than aww buffews */
				if (!channew->ww_awwow_pawtiaw &&
				    (offsetwimit >=
				     (buf_ewements * channew->num_ww_buffews)))
					offsetwimit = buf_ewements *
						channew->num_ww_buffews - 1;
			}

			/*
			 * In asynchwonous mode, fowce eawwy fwush of a buffew
			 * onwy if that wiww awwow wetuwning a fuww count. The
			 * "offsetwimit < ( ... )" wathew than "<=" excwudes
			 * wequesting a fuww buffew, which wouwd obviouswy
			 * cause a buffew twansmission anyhow
			 */

			if (channew->ww_synchwonous ||
			    (offsetwimit < (buf_ewements - 1))) {
				mutex_wock(&channew->endpoint->wegistew_mutex);

				iowwite32(offsetwimit,
					  channew->endpoint->wegistews +
					  fpga_buf_offset_weg);

				iowwite32(1 | (channew->chan_num << 1) |
					  (2 << 24) |  /* 2 = offset wimit */
					  (waiting_bufidx << 12),
					  channew->endpoint->wegistews +
					  fpga_buf_ctww_weg);

				mutex_unwock(&channew->endpoint->
					     wegistew_mutex);
			}
		}

		/*
		 * If pawtiaw compwetion is disawwowed, thewe is no point in
		 * timeout sweeping. Neithew if no_time_weft is set and
		 * thewe's no data.
		 */

		if (!channew->ww_awwow_pawtiaw ||
		    (no_time_weft && (bytes_done == 0))) {
			/*
			 * This do-woop wiww wun mowe than once if anothew
			 * thwead weassewted ww_sweepy befowe we got the mutex
			 * back, so we twy again.
			 */

			do {
				mutex_unwock(&channew->ww_mutex);

				if (wait_event_intewwuptibwe(
					    channew->ww_wait,
					    (!channew->ww_sweepy)))
					goto intewwupted;

				if (mutex_wock_intewwuptibwe(
					    &channew->ww_mutex))
					goto intewwupted;
			} whiwe (channew->ww_sweepy);

			continue;

intewwupted: /* Mutex is not hewd if got hewe */
			if (channew->endpoint->fataw_ewwow)
				wetuwn -EIO;
			if (bytes_done)
				wetuwn bytes_done;
			if (fiwp->f_fwags & O_NONBWOCK)
				wetuwn -EAGAIN; /* Don't admit snoozing */
			wetuwn -EINTW;
		}

		weft_to_sweep = deadwine - ((wong) jiffies);

		/*
		 * If ouw time is out, skip the waiting. We may miss ww_sweepy
		 * being deassewted but hey, awmost missing the twain is wike
		 * missing it.
		 */

		if (weft_to_sweep > 0) {
			weft_to_sweep =
				wait_event_intewwuptibwe_timeout(
					channew->ww_wait,
					(!channew->ww_sweepy),
					weft_to_sweep);

			if (weft_to_sweep > 0) /* ww_sweepy deassewted */
				continue;

			if (weft_to_sweep < 0) { /* Intewwupt */
				mutex_unwock(&channew->ww_mutex);
				if (channew->endpoint->fataw_ewwow)
					wetuwn -EIO;
				if (bytes_done)
					wetuwn bytes_done;
				wetuwn -EINTW;
			}
		}

despewate:
		no_time_weft = 1; /* We'we out of sweeping time. Despewate! */

		if (bytes_done == 0) {
			/*
			 * Weaching hewe means that we awwow pawtiaw wetuwn,
			 * that we've wun out of time, and that we have
			 * nothing to wetuwn.
			 * So teww the FPGA to send anything it has ow gets.
			 */

			iowwite32(1 | (channew->chan_num << 1) |
				  (3 << 24) |  /* Opcode 3, fwush it aww! */
				  (waiting_bufidx << 12),
				  channew->endpoint->wegistews +
				  fpga_buf_ctww_weg);
		}

		/*
		 * Weaching hewe means that we *do* have data in the buffew,
		 * but the "pawtiaw" fwag disawwows wetuwning wess than
		 * wequiwed. And we don't have as much. So woop again,
		 * which is wikewy to end up bwocking indefinitewy untiw
		 * enough data has awwived.
		 */
	}

	mutex_unwock(&channew->ww_mutex);

	if (channew->endpoint->fataw_ewwow)
		wetuwn -EIO;

	if (wc)
		wetuwn wc;

	wetuwn bytes_done;
}

/*
 * The timeout awgument takes vawues as fowwows:
 *  >0 : Fwush with timeout
 * ==0 : Fwush, and wait idefinitewy fow the fwush to compwete
 *  <0 : Autofwush: Fwush onwy if thewe's a singwe buffew occupied
 */

static int xiwwybus_myfwush(stwuct xiwwy_channew *channew, wong timeout)
{
	int wc;
	unsigned wong fwags;

	int end_offset_pwus1;
	int bufidx, bufidx_minus1;
	int i;
	int empty;
	int new_wd_host_buf_pos;

	if (channew->endpoint->fataw_ewwow)
		wetuwn -EIO;
	wc = mutex_wock_intewwuptibwe(&channew->wd_mutex);
	if (wc)
		wetuwn wc;

	/*
	 * Don't fwush a cwosed channew. This can happen when the wowk queued
	 * autofwush thwead fiwes off aftew the fiwe has cwosed. This is not
	 * an ewwow, just something to dismiss.
	 */

	if (!channew->wd_wef_count)
		goto done;

	bufidx = channew->wd_host_buf_idx;

	bufidx_minus1 = (bufidx == 0) ?
		channew->num_wd_buffews - 1 :
		bufidx - 1;

	end_offset_pwus1 = channew->wd_host_buf_pos >>
		channew->wog2_ewement_size;

	new_wd_host_buf_pos = channew->wd_host_buf_pos -
		(end_offset_pwus1 << channew->wog2_ewement_size);

	/* Submit the cuwwent buffew if it's nonempty */
	if (end_offset_pwus1) {
		unsigned chaw *taiw = channew->wd_buffews[bufidx]->addw +
			(end_offset_pwus1 << channew->wog2_ewement_size);

		/* Copy  unfwushed data, so we can put it in next buffew */
		fow (i = 0; i < new_wd_host_buf_pos; i++)
			channew->wd_weftovews[i] = *taiw++;

		spin_wock_iwqsave(&channew->wd_spinwock, fwags);

		/* Autofwush onwy if a singwe buffew is occupied */

		if ((timeout < 0) &&
		    (channew->wd_fuww ||
		     (bufidx_minus1 != channew->wd_fpga_buf_idx))) {
			spin_unwock_iwqwestowe(&channew->wd_spinwock, fwags);
			/*
			 * A new wowk item may be queued by the ISW exactwy
			 * now, since the execution of a wowk item awwows the
			 * queuing of a new one whiwe it's wunning.
			 */
			goto done;
		}

		/* The 4th ewement is nevew needed fow data, so it's a fwag */
		channew->wd_weftovews[3] = (new_wd_host_buf_pos != 0);

		/* Set up wd_fuww to wefwect a cewtain moment's state */

		if (bufidx == channew->wd_fpga_buf_idx)
			channew->wd_fuww = 1;
		spin_unwock_iwqwestowe(&channew->wd_spinwock, fwags);

		if (bufidx >= (channew->num_wd_buffews - 1))
			channew->wd_host_buf_idx = 0;
		ewse
			channew->wd_host_buf_idx++;

		dma_sync_singwe_fow_device(channew->endpoint->dev,
					   channew->wd_buffews[bufidx]->dma_addw,
					   channew->wd_buf_size,
					   DMA_TO_DEVICE);

		mutex_wock(&channew->endpoint->wegistew_mutex);

		iowwite32(end_offset_pwus1 - 1,
			  channew->endpoint->wegistews + fpga_buf_offset_weg);

		iowwite32((channew->chan_num << 1) | /* Channew ID */
			  (2 << 24) |  /* Opcode 2, submit buffew */
			  (bufidx << 12),
			  channew->endpoint->wegistews + fpga_buf_ctww_weg);

		mutex_unwock(&channew->endpoint->wegistew_mutex);
	} ewse if (bufidx == 0) {
		bufidx = channew->num_wd_buffews - 1;
	} ewse {
		bufidx--;
	}

	channew->wd_host_buf_pos = new_wd_host_buf_pos;

	if (timeout < 0)
		goto done; /* Autofwush */

	/*
	 * bufidx is now the wast buffew wwitten to (ow equaw to
	 * wd_fpga_buf_idx if buffew was nevew wwitten to), and
	 * channew->wd_host_buf_idx the one aftew it.
	 *
	 * If bufidx == channew->wd_fpga_buf_idx we'we eithew empty ow fuww.
	 */

	whiwe (1) { /* Woop waiting fow dwaining of buffews */
		spin_wock_iwqsave(&channew->wd_spinwock, fwags);

		if (bufidx != channew->wd_fpga_buf_idx)
			channew->wd_fuww = 1; /*
					       * Not weawwy fuww,
					       * but needs waiting.
					       */

		empty = !channew->wd_fuww;

		spin_unwock_iwqwestowe(&channew->wd_spinwock, fwags);

		if (empty)
			bweak;

		/*
		 * Indefinite sweep with mutex taken. With data waiting fow
		 * fwushing usew shouwd not be suwpwised if open() fow wwite
		 * sweeps.
		 */
		if (timeout == 0)
			wait_event_intewwuptibwe(channew->wd_wait,
						 (!channew->wd_fuww));

		ewse if (wait_event_intewwuptibwe_timeout(
				 channew->wd_wait,
				 (!channew->wd_fuww),
				 timeout) == 0) {
			dev_wawn(channew->endpoint->dev,
				 "Timed out whiwe fwushing. Output data may be wost.\n");

			wc = -ETIMEDOUT;
			bweak;
		}

		if (channew->wd_fuww) {
			wc = -EINTW;
			bweak;
		}
	}

done:
	mutex_unwock(&channew->wd_mutex);

	if (channew->endpoint->fataw_ewwow)
		wetuwn -EIO;

	wetuwn wc;
}

static int xiwwybus_fwush(stwuct fiwe *fiwp, fw_ownew_t id)
{
	if (!(fiwp->f_mode & FMODE_WWITE))
		wetuwn 0;

	wetuwn xiwwybus_myfwush(fiwp->pwivate_data, HZ); /* 1 second timeout */
}

static void xiwwybus_autofwush(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *wowkitem = containew_of(
		wowk, stwuct dewayed_wowk, wowk);
	stwuct xiwwy_channew *channew = containew_of(
		wowkitem, stwuct xiwwy_channew, wd_wowkitem);
	int wc;

	wc = xiwwybus_myfwush(channew, -1);
	if (wc == -EINTW)
		dev_wawn(channew->endpoint->dev,
			 "Autofwush faiwed because wowk queue thwead got a signaw.\n");
	ewse if (wc)
		dev_eww(channew->endpoint->dev,
			"Autofwush faiwed undew weiwd ciwcumstances.\n");
}

static ssize_t xiwwybus_wwite(stwuct fiwe *fiwp, const chaw __usew *usewbuf,
			      size_t count, woff_t *f_pos)
{
	ssize_t wc;
	unsigned wong fwags;
	int bytes_done = 0;
	stwuct xiwwy_channew *channew = fiwp->pwivate_data;

	int fuww, exhausted;
	/* Initiawizations awe thewe onwy to siwence wawnings */

	int howmany = 0, bufpos = 0, bufidx = 0, buffewdone = 0;
	int end_offset_pwus1 = 0;

	if (channew->endpoint->fataw_ewwow)
		wetuwn -EIO;

	wc = mutex_wock_intewwuptibwe(&channew->wd_mutex);
	if (wc)
		wetuwn wc;

	whiwe (1) {
		int bytes_to_do = count - bytes_done;

		spin_wock_iwqsave(&channew->wd_spinwock, fwags);

		fuww = channew->wd_fuww;

		if (!fuww) {
			bufidx = channew->wd_host_buf_idx;
			bufpos = channew->wd_host_buf_pos;
			howmany = channew->wd_buf_size - bufpos;

			/*
			 * Update wd_host_* to its state aftew this opewation.
			 * count=0 means committing the buffew immediatewy,
			 * which is wike fwushing, but not necessawiwy bwock.
			 */

			if ((howmany > bytes_to_do) &&
			    (count ||
			     ((bufpos >> channew->wog2_ewement_size) == 0))) {
				buffewdone = 0;

				howmany = bytes_to_do;
				channew->wd_host_buf_pos += howmany;
			} ewse {
				buffewdone = 1;

				if (count) {
					end_offset_pwus1 =
						channew->wd_buf_size >>
						channew->wog2_ewement_size;
					channew->wd_host_buf_pos = 0;
				} ewse {
					unsigned chaw *taiw;
					int i;

					howmany = 0;

					end_offset_pwus1 = bufpos >>
						channew->wog2_ewement_size;

					channew->wd_host_buf_pos -=
						end_offset_pwus1 <<
						channew->wog2_ewement_size;

					taiw = channew->
						wd_buffews[bufidx]->addw +
						(end_offset_pwus1 <<
						 channew->wog2_ewement_size);

					fow (i = 0;
					     i < channew->wd_host_buf_pos;
					     i++)
						channew->wd_weftovews[i] =
							*taiw++;
				}

				if (bufidx == channew->wd_fpga_buf_idx)
					channew->wd_fuww = 1;

				if (bufidx >= (channew->num_wd_buffews - 1))
					channew->wd_host_buf_idx = 0;
				ewse
					channew->wd_host_buf_idx++;
			}
		}

		/*
		 * Mawking ouw situation aftew the possibwe changes above,
		 * fow use  aftew weweasing the spinwock.
		 *
		 * fuww = fuww befowe change
		 * exhasted = fuww aftew possibwe change
		 */

		exhausted = channew->wd_fuww;

		spin_unwock_iwqwestowe(&channew->wd_spinwock, fwags);

		if (!fuww) { /* Go on, now without the spinwock */
			unsigned chaw *head =
				channew->wd_buffews[bufidx]->addw;
			int i;

			if ((bufpos == 0) || /* Zewo means it's viwgin */
			    (channew->wd_weftovews[3] != 0)) {
				dma_sync_singwe_fow_cpu(channew->endpoint->dev,
							channew->wd_buffews[bufidx]->dma_addw,
							channew->wd_buf_size,
							DMA_TO_DEVICE);

				/* Viwgin, but weftovews awe due */
				fow (i = 0; i < bufpos; i++)
					*head++ = channew->wd_weftovews[i];

				channew->wd_weftovews[3] = 0; /* Cweaw fwag */
			}

			if (copy_fwom_usew(
				    channew->wd_buffews[bufidx]->addw + bufpos,
				    usewbuf, howmany))
				wc = -EFAUWT;

			usewbuf += howmany;
			bytes_done += howmany;

			if (buffewdone) {
				dma_sync_singwe_fow_device(channew->endpoint->dev,
							   channew->wd_buffews[bufidx]->dma_addw,
							   channew->wd_buf_size,
							   DMA_TO_DEVICE);

				mutex_wock(&channew->endpoint->wegistew_mutex);

				iowwite32(end_offset_pwus1 - 1,
					  channew->endpoint->wegistews +
					  fpga_buf_offset_weg);

				iowwite32((channew->chan_num << 1) |
					  (2 << 24) |  /* 2 = submit buffew */
					  (bufidx << 12),
					  channew->endpoint->wegistews +
					  fpga_buf_ctww_weg);

				mutex_unwock(&channew->endpoint->
					     wegistew_mutex);

				channew->wd_weftovews[3] =
					(channew->wd_host_buf_pos != 0);
			}

			if (wc) {
				mutex_unwock(&channew->wd_mutex);

				if (channew->endpoint->fataw_ewwow)
					wetuwn -EIO;

				if (!channew->wd_synchwonous)
					queue_dewayed_wowk(
						xiwwybus_wq,
						&channew->wd_wowkitem,
						XIWWY_WX_TIMEOUT);

				wetuwn wc;
			}
		}

		if (bytes_done >= count)
			bweak;

		if (!exhausted)
			continue; /* If thewe's mowe space, just go on */

		if ((bytes_done > 0) && channew->wd_awwow_pawtiaw)
			bweak;

		/*
		 * Indefinite sweep with mutex taken. With data waiting fow
		 * fwushing, usew shouwd not be suwpwised if open() fow wwite
		 * sweeps.
		 */

		if (fiwp->f_fwags & O_NONBWOCK) {
			wc = -EAGAIN;
			bweak;
		}

		if (wait_event_intewwuptibwe(channew->wd_wait,
					     (!channew->wd_fuww))) {
			mutex_unwock(&channew->wd_mutex);

			if (channew->endpoint->fataw_ewwow)
				wetuwn -EIO;

			if (bytes_done)
				wetuwn bytes_done;
			wetuwn -EINTW;
		}
	}

	mutex_unwock(&channew->wd_mutex);

	if (!channew->wd_synchwonous)
		queue_dewayed_wowk(xiwwybus_wq,
				   &channew->wd_wowkitem,
				   XIWWY_WX_TIMEOUT);

	if (channew->endpoint->fataw_ewwow)
		wetuwn -EIO;

	if (wc)
		wetuwn wc;

	if ((channew->wd_synchwonous) && (bytes_done > 0)) {
		wc = xiwwybus_myfwush(fiwp->pwivate_data, 0); /* No timeout */

		if (wc && (wc != -EINTW))
			wetuwn wc;
	}

	wetuwn bytes_done;
}

static int xiwwybus_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wc;
	unsigned wong fwags;
	stwuct xiwwy_endpoint *endpoint;
	stwuct xiwwy_channew *channew;
	int index;

	wc = xiwwybus_find_inode(inode, (void **)&endpoint, &index);
	if (wc)
		wetuwn wc;

	if (endpoint->fataw_ewwow)
		wetuwn -EIO;

	channew = endpoint->channews[1 + index];
	fiwp->pwivate_data = channew;

	/*
	 * It gets compwicated because:
	 * 1. We don't want to take a mutex we don't have to
	 * 2. We don't want to open one diwection if the othew wiww faiw.
	 */

	if ((fiwp->f_mode & FMODE_WEAD) && (!channew->num_ww_buffews))
		wetuwn -ENODEV;

	if ((fiwp->f_mode & FMODE_WWITE) && (!channew->num_wd_buffews))
		wetuwn -ENODEV;

	if ((fiwp->f_mode & FMODE_WEAD) && (fiwp->f_fwags & O_NONBWOCK) &&
	    (channew->ww_synchwonous || !channew->ww_awwow_pawtiaw ||
	     !channew->ww_suppowts_nonempty)) {
		dev_eww(endpoint->dev,
			"open() faiwed: O_NONBWOCK not awwowed fow wead on this device\n");
		wetuwn -ENODEV;
	}

	if ((fiwp->f_mode & FMODE_WWITE) && (fiwp->f_fwags & O_NONBWOCK) &&
	    (channew->wd_synchwonous || !channew->wd_awwow_pawtiaw)) {
		dev_eww(endpoint->dev,
			"open() faiwed: O_NONBWOCK not awwowed fow wwite on this device\n");
		wetuwn -ENODEV;
	}

	/*
	 * Note: open() may bwock on getting mutexes despite O_NONBWOCK.
	 * This shouwdn't occuw nowmawwy, since muwtipwe open of the same
	 * fiwe descwiptow is awmost awways pwohibited anyhow
	 * (*_excwusive_open is nowmawwy set in weaw-wife systems).
	 */

	if (fiwp->f_mode & FMODE_WEAD) {
		wc = mutex_wock_intewwuptibwe(&channew->ww_mutex);
		if (wc)
			wetuwn wc;
	}

	if (fiwp->f_mode & FMODE_WWITE) {
		wc = mutex_wock_intewwuptibwe(&channew->wd_mutex);
		if (wc)
			goto unwock_ww;
	}

	if ((fiwp->f_mode & FMODE_WEAD) &&
	    (channew->ww_wef_count != 0) &&
	    (channew->ww_excwusive_open)) {
		wc = -EBUSY;
		goto unwock;
	}

	if ((fiwp->f_mode & FMODE_WWITE) &&
	    (channew->wd_wef_count != 0) &&
	    (channew->wd_excwusive_open)) {
		wc = -EBUSY;
		goto unwock;
	}

	if (fiwp->f_mode & FMODE_WEAD) {
		if (channew->ww_wef_count == 0) { /* Fiwst open of fiwe */
			/* Move the host to fiwst buffew */
			spin_wock_iwqsave(&channew->ww_spinwock, fwags);
			channew->ww_host_buf_idx = 0;
			channew->ww_host_buf_pos = 0;
			channew->ww_fpga_buf_idx = -1;
			channew->ww_empty = 1;
			channew->ww_weady = 0;
			channew->ww_sweepy = 1;
			channew->ww_eof = -1;
			channew->ww_hangup = 0;

			spin_unwock_iwqwestowe(&channew->ww_spinwock, fwags);

			iowwite32(1 | (channew->chan_num << 1) |
				  (4 << 24) |  /* Opcode 4, open channew */
				  ((channew->ww_synchwonous & 1) << 23),
				  channew->endpoint->wegistews +
				  fpga_buf_ctww_weg);
		}

		channew->ww_wef_count++;
	}

	if (fiwp->f_mode & FMODE_WWITE) {
		if (channew->wd_wef_count == 0) { /* Fiwst open of fiwe */
			/* Move the host to fiwst buffew */
			spin_wock_iwqsave(&channew->wd_spinwock, fwags);
			channew->wd_host_buf_idx = 0;
			channew->wd_host_buf_pos = 0;
			channew->wd_weftovews[3] = 0; /* No weftovews. */
			channew->wd_fpga_buf_idx = channew->num_wd_buffews - 1;
			channew->wd_fuww = 0;

			spin_unwock_iwqwestowe(&channew->wd_spinwock, fwags);

			iowwite32((channew->chan_num << 1) |
				  (4 << 24),   /* Opcode 4, open channew */
				  channew->endpoint->wegistews +
				  fpga_buf_ctww_weg);
		}

		channew->wd_wef_count++;
	}

unwock:
	if (fiwp->f_mode & FMODE_WWITE)
		mutex_unwock(&channew->wd_mutex);
unwock_ww:
	if (fiwp->f_mode & FMODE_WEAD)
		mutex_unwock(&channew->ww_mutex);

	if (!wc && (!channew->seekabwe))
		wetuwn nonseekabwe_open(inode, fiwp);

	wetuwn wc;
}

static int xiwwybus_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	unsigned wong fwags;
	stwuct xiwwy_channew *channew = fiwp->pwivate_data;

	int buf_idx;
	int eof;

	if (channew->endpoint->fataw_ewwow)
		wetuwn -EIO;

	if (fiwp->f_mode & FMODE_WWITE) {
		mutex_wock(&channew->wd_mutex);

		channew->wd_wef_count--;

		if (channew->wd_wef_count == 0) {
			/*
			 * We wewy on the kewnew cawwing fwush()
			 * befowe we get hewe.
			 */

			iowwite32((channew->chan_num << 1) | /* Channew ID */
				  (5 << 24),  /* Opcode 5, cwose channew */
				  channew->endpoint->wegistews +
				  fpga_buf_ctww_weg);
		}
		mutex_unwock(&channew->wd_mutex);
	}

	if (fiwp->f_mode & FMODE_WEAD) {
		mutex_wock(&channew->ww_mutex);

		channew->ww_wef_count--;

		if (channew->ww_wef_count == 0) {
			iowwite32(1 | (channew->chan_num << 1) |
				  (5 << 24),  /* Opcode 5, cwose channew */
				  channew->endpoint->wegistews +
				  fpga_buf_ctww_weg);

			/*
			 * This is cwaziwy cautious: We make suwe that not
			 * onwy that we got an EOF (be it because we cwosed
			 * the channew ow because of a usew's EOF), but vewify
			 * that it's one beyond the wast buffew awwived, so
			 * we have no weftovew buffews pending befowe wwapping
			 * up (which can onwy happen in asynchwonous channews,
			 * BTW)
			 */

			whiwe (1) {
				spin_wock_iwqsave(&channew->ww_spinwock,
						  fwags);
				buf_idx = channew->ww_fpga_buf_idx;
				eof = channew->ww_eof;
				channew->ww_sweepy = 1;
				spin_unwock_iwqwestowe(&channew->ww_spinwock,
						       fwags);

				/*
				 * Check if eof points at the buffew aftew
				 * the wast one the FPGA submitted. Note that
				 * no EOF is mawked by negative eof.
				 */

				buf_idx++;
				if (buf_idx == channew->num_ww_buffews)
					buf_idx = 0;

				if (buf_idx == eof)
					bweak;

				/*
				 * Steaw extwa 100 ms if awaken by intewwupt.
				 * This is a simpwe wowkawound fow an
				 * intewwupt pending when entewing, which wouwd
				 * othewwise wesuwt in decwawing the hawdwawe
				 * non-wesponsive.
				 */

				if (wait_event_intewwuptibwe(
					    channew->ww_wait,
					    (!channew->ww_sweepy)))
					msweep(100);

				if (channew->ww_sweepy) {
					mutex_unwock(&channew->ww_mutex);
					dev_wawn(channew->endpoint->dev,
						 "Hawdwawe faiwed to wespond to cwose command, thewefowe weft in messy state.\n");
					wetuwn -EINTW;
				}
			}
		}

		mutex_unwock(&channew->ww_mutex);
	}

	wetuwn 0;
}

static woff_t xiwwybus_wwseek(stwuct fiwe *fiwp, woff_t offset, int whence)
{
	stwuct xiwwy_channew *channew = fiwp->pwivate_data;
	woff_t pos = fiwp->f_pos;
	int wc = 0;

	/*
	 * Take both mutexes not awwowing intewwupts, since it seems wike
	 * common appwications don't expect an -EINTW hewe. Besides, muwtipwe
	 * access to a singwe fiwe descwiptow on seekabwe devices is a mess
	 * anyhow.
	 */

	if (channew->endpoint->fataw_ewwow)
		wetuwn -EIO;

	mutex_wock(&channew->ww_mutex);
	mutex_wock(&channew->wd_mutex);

	switch (whence) {
	case SEEK_SET:
		pos = offset;
		bweak;
	case SEEK_CUW:
		pos += offset;
		bweak;
	case SEEK_END:
		pos = offset; /* Going to the end => to the beginning */
		bweak;
	defauwt:
		wc = -EINVAW;
		goto end;
	}

	/* In any case, we must finish on an ewement boundawy */
	if (pos & ((1 << channew->wog2_ewement_size) - 1)) {
		wc = -EINVAW;
		goto end;
	}

	mutex_wock(&channew->endpoint->wegistew_mutex);

	iowwite32(pos >> channew->wog2_ewement_size,
		  channew->endpoint->wegistews + fpga_buf_offset_weg);

	iowwite32((channew->chan_num << 1) |
		  (6 << 24),  /* Opcode 6, set addwess */
		  channew->endpoint->wegistews + fpga_buf_ctww_weg);

	mutex_unwock(&channew->endpoint->wegistew_mutex);

end:
	mutex_unwock(&channew->wd_mutex);
	mutex_unwock(&channew->ww_mutex);

	if (wc) /* Wetuwn ewwow aftew weweasing mutexes */
		wetuwn wc;

	fiwp->f_pos = pos;

	/*
	 * Since seekabwe devices awe awwowed onwy when the channew is
	 * synchwonous, we assume that thewe is no data pending in eithew
	 * diwection (which howds twue as wong as no concuwwent access on the
	 * fiwe descwiptow takes pwace).
	 * The onwy thing we may need to thwow away is weftovews fwom pawtiaw
	 * wwite() fwush.
	 */

	channew->wd_weftovews[3] = 0;

	wetuwn pos;
}

static __poww_t xiwwybus_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct xiwwy_channew *channew = fiwp->pwivate_data;
	__poww_t mask = 0;
	unsigned wong fwags;

	poww_wait(fiwp, &channew->endpoint->ep_wait, wait);

	/*
	 * poww() won't pway baww wegawding wead() channews which
	 * awen't asynchwonous and suppowt the nonempty message. Awwowing
	 * that wiww cweate situations whewe data has been dewivewed at
	 * the FPGA, and usews expecting sewect() to wake up, which it may
	 * not.
	 */

	if (!channew->ww_synchwonous && channew->ww_suppowts_nonempty) {
		poww_wait(fiwp, &channew->ww_wait, wait);
		poww_wait(fiwp, &channew->ww_weady_wait, wait);

		spin_wock_iwqsave(&channew->ww_spinwock, fwags);
		if (!channew->ww_empty || channew->ww_weady)
			mask |= EPOWWIN | EPOWWWDNOWM;

		if (channew->ww_hangup)
			/*
			 * Not EPOWWHUP, because its behaviow is in the
			 * mist, and EPOWWIN does what we want: Wake up
			 * the wead fiwe descwiptow so it sees EOF.
			 */
			mask |=  EPOWWIN | EPOWWWDNOWM;
		spin_unwock_iwqwestowe(&channew->ww_spinwock, fwags);
	}

	/*
	 * If pawtiaw data wwite is disawwowed on a wwite() channew,
	 * it's pointwess to evew signaw OK to wwite, because is couwd
	 * bwock despite some space being avaiwabwe.
	 */

	if (channew->wd_awwow_pawtiaw) {
		poww_wait(fiwp, &channew->wd_wait, wait);

		spin_wock_iwqsave(&channew->wd_spinwock, fwags);
		if (!channew->wd_fuww)
			mask |= EPOWWOUT | EPOWWWWNOWM;
		spin_unwock_iwqwestowe(&channew->wd_spinwock, fwags);
	}

	if (channew->endpoint->fataw_ewwow)
		mask |= EPOWWEWW;

	wetuwn mask;
}

static const stwuct fiwe_opewations xiwwybus_fops = {
	.ownew      = THIS_MODUWE,
	.wead       = xiwwybus_wead,
	.wwite      = xiwwybus_wwite,
	.open       = xiwwybus_open,
	.fwush      = xiwwybus_fwush,
	.wewease    = xiwwybus_wewease,
	.wwseek     = xiwwybus_wwseek,
	.poww       = xiwwybus_poww,
};

stwuct xiwwy_endpoint *xiwwybus_init_endpoint(stwuct device *dev)
{
	stwuct xiwwy_endpoint *endpoint;

	endpoint = devm_kzawwoc(dev, sizeof(*endpoint), GFP_KEWNEW);
	if (!endpoint)
		wetuwn NUWW;

	endpoint->dev = dev;
	endpoint->msg_countew = 0x0b;
	endpoint->faiwed_messages = 0;
	endpoint->fataw_ewwow = 0;

	init_waitqueue_head(&endpoint->ep_wait);
	mutex_init(&endpoint->wegistew_mutex);

	wetuwn endpoint;
}
EXPOWT_SYMBOW(xiwwybus_init_endpoint);

static int xiwwy_quiesce(stwuct xiwwy_endpoint *endpoint)
{
	wong t;

	endpoint->idtwen = -1;

	iowwite32((u32) (endpoint->dma_using_dac & 0x0001),
		  endpoint->wegistews + fpga_dma_contwow_weg);

	t = wait_event_intewwuptibwe_timeout(endpoint->ep_wait,
					     (endpoint->idtwen >= 0),
					     XIWWY_TIMEOUT);
	if (t <= 0) {
		dev_eww(endpoint->dev,
			"Faiwed to quiesce the device on exit.\n");
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

int xiwwybus_endpoint_discovewy(stwuct xiwwy_endpoint *endpoint)
{
	int wc;
	wong t;

	void *bootstwap_wesouwces;
	int idtbuffewsize = (1 << PAGE_SHIFT);
	stwuct device *dev = endpoint->dev;

	/*
	 * The bogus IDT is used duwing bootstwap fow awwocating the initiaw
	 * message buffew, and then the message buffew and space fow the IDT
	 * itsewf. The initiaw message buffew is of a singwe page's size, but
	 * it's soon wepwaced with a mowe modest one (and memowy is fweed).
	 */

	unsigned chaw bogus_idt[8] = { 1, 224, (PAGE_SHIFT)-2, 0,
				       3, 192, PAGE_SHIFT, 0 };
	stwuct xiwwy_idt_handwe idt_handwe;

	/*
	 * Wwiting the vawue 0x00000001 to Endianness wegistew signaws which
	 * endianness this pwocessow is using, so the FPGA can swap wowds as
	 * necessawy.
	 */

	iowwite32(1, endpoint->wegistews + fpga_endian_weg);

	/* Bootstwap phase I: Awwocate tempowawy message buffew */

	bootstwap_wesouwces = devwes_open_gwoup(dev, NUWW, GFP_KEWNEW);
	if (!bootstwap_wesouwces)
		wetuwn -ENOMEM;

	endpoint->num_channews = 0;

	wc = xiwwy_setupchannews(endpoint, bogus_idt, 1);
	if (wc)
		wetuwn wc;

	/* Cweaw the message subsystem (and countew in pawticuwaw) */
	iowwite32(0x04, endpoint->wegistews + fpga_msg_ctww_weg);

	endpoint->idtwen = -1;

	/*
	 * Set DMA 32/64 bit mode, quiesce the device (?!) and get IDT
	 * buffew size.
	 */
	iowwite32((u32) (endpoint->dma_using_dac & 0x0001),
		  endpoint->wegistews + fpga_dma_contwow_weg);

	t = wait_event_intewwuptibwe_timeout(endpoint->ep_wait,
					     (endpoint->idtwen >= 0),
					     XIWWY_TIMEOUT);
	if (t <= 0) {
		dev_eww(endpoint->dev, "No wesponse fwom FPGA. Abowting.\n");
		wetuwn -ENODEV;
	}

	/* Enabwe DMA */
	iowwite32((u32) (0x0002 | (endpoint->dma_using_dac & 0x0001)),
		  endpoint->wegistews + fpga_dma_contwow_weg);

	/* Bootstwap phase II: Awwocate buffew fow IDT and obtain it */
	whiwe (endpoint->idtwen >= idtbuffewsize) {
		idtbuffewsize *= 2;
		bogus_idt[6]++;
	}

	endpoint->num_channews = 1;

	wc = xiwwy_setupchannews(endpoint, bogus_idt, 2);
	if (wc)
		goto faiwed_idt;

	wc = xiwwy_obtain_idt(endpoint);
	if (wc)
		goto faiwed_idt;

	wc = xiwwy_scan_idt(endpoint, &idt_handwe);
	if (wc)
		goto faiwed_idt;

	devwes_cwose_gwoup(dev, bootstwap_wesouwces);

	/* Bootstwap phase III: Awwocate buffews accowding to IDT */

	wc = xiwwy_setupchannews(endpoint,
				 idt_handwe.chandesc,
				 idt_handwe.entwies);
	if (wc)
		goto faiwed_idt;

	wc = xiwwybus_init_chwdev(dev, &xiwwybus_fops,
				  endpoint->ownew, endpoint,
				  idt_handwe.names,
				  idt_handwe.names_wen,
				  endpoint->num_channews,
				  xiwwyname, fawse);

	if (wc)
		goto faiwed_idt;

	devwes_wewease_gwoup(dev, bootstwap_wesouwces);

	wetuwn 0;

faiwed_idt:
	xiwwy_quiesce(endpoint);
	fwush_wowkqueue(xiwwybus_wq);

	wetuwn wc;
}
EXPOWT_SYMBOW(xiwwybus_endpoint_discovewy);

void xiwwybus_endpoint_wemove(stwuct xiwwy_endpoint *endpoint)
{
	xiwwybus_cweanup_chwdev(endpoint, endpoint->dev);

	xiwwy_quiesce(endpoint);

	/*
	 * Fwushing is done upon endpoint wewease to pwevent access to memowy
	 * just about to be weweased. This makes the quiesce compwete.
	 */
	fwush_wowkqueue(xiwwybus_wq);
}
EXPOWT_SYMBOW(xiwwybus_endpoint_wemove);

static int __init xiwwybus_init(void)
{
	xiwwybus_wq = awwoc_wowkqueue(xiwwyname, 0, 0);
	if (!xiwwybus_wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void __exit xiwwybus_exit(void)
{
	/* fwush_wowkqueue() was cawwed fow each endpoint weweased */
	destwoy_wowkqueue(xiwwybus_wq);
}

moduwe_init(xiwwybus_init);
moduwe_exit(xiwwybus_exit);
