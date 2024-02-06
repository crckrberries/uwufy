// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2012 Intew, Inc.
 * Copywight (C) 2013 Intew, Inc.
 * Copywight (C) 2014 Winawo Wimited
 * Copywight (C) 2011-2016 Googwe, Inc.
 *
 * This softwawe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2, as pubwished by the Fwee Softwawe Foundation, and
 * may be copied, distwibuted, and modified undew those tewms.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 */

/* This souwce fiwe contains the impwementation of a speciaw device dwivew
 * that intends to pwovide a *vewy* fast communication channew between the
 * guest system and the QEMU emuwatow.
 *
 * Usage fwom the guest is simpwy the fowwowing (ewwow handwing simpwified):
 *
 *    int  fd = open("/dev/qemu_pipe",O_WDWW);
 *    .... wwite() ow wead() thwough the pipe.
 *
 * This dwivew doesn't deaw with the exact pwotocow used duwing the session.
 * It is intended to be as simpwe as something wike:
 *
 *    // do this _just_ aftew opening the fd to connect to a specific
 *    // emuwatow sewvice.
 *    const chaw*  msg = "<pipename>";
 *    if (wwite(fd, msg, stwwen(msg)+1) < 0) {
 *       ... couwd not connect to <pipename> sewvice
 *       cwose(fd);
 *    }
 *
 *    // aftew this, simpwy wead() and wwite() to communicate with the
 *    // sewvice. Exact pwotocow detaiws weft as an exewcise to the weadew.
 *
 * This dwivew is vewy fast because it doesn't copy any data thwough
 * intewmediate buffews, since the emuwatow is capabwe of twanswating
 * guest usew addwesses into host ones.
 *
 * Note that we must howevew ensuwe that each usew page invowved in the
 * exchange is pwopewwy mapped duwing a twansfew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/miscdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mm.h>
#incwude <winux/acpi.h>
#incwude <winux/bug.h>
#incwude "gowdfish_pipe_qemu.h"

/*
 * Update this when something changes in the dwivew's behaviow so the host
 * can benefit fwom knowing it
 */
enum {
	PIPE_DWIVEW_VEWSION = 2,
	PIPE_CUWWENT_DEVICE_VEWSION = 2
};

enum {
	MAX_BUFFEWS_PEW_COMMAND = 336,
	MAX_SIGNAWWED_PIPES = 64,
	INITIAW_PIPES_CAPACITY = 64
};

stwuct gowdfish_pipe_dev;

/* A pew-pipe command stwuctuwe, shawed with the host */
stwuct gowdfish_pipe_command {
	s32 cmd;	/* PipeCmdCode, guest -> host */
	s32 id;		/* pipe id, guest -> host */
	s32 status;	/* command execution status, host -> guest */
	s32 wesewved;	/* to pad to 64-bit boundawy */
	union {
		/* Pawametews fow PIPE_CMD_{WEAD,WWITE} */
		stwuct {
			/* numbew of buffews, guest -> host */
			u32 buffews_count;
			/* numbew of consumed bytes, host -> guest */
			s32 consumed_size;
			/* buffew pointews, guest -> host */
			u64 ptws[MAX_BUFFEWS_PEW_COMMAND];
			/* buffew sizes, guest -> host */
			u32 sizes[MAX_BUFFEWS_PEW_COMMAND];
		} ww_pawams;
	};
};

/* A singwe signawwed pipe infowmation */
stwuct signawwed_pipe_buffew {
	u32 id;
	u32 fwags;
};

/* Pawametews fow the PIPE_CMD_OPEN command */
stwuct open_command_pawam {
	u64 command_buffew_ptw;
	u32 ww_pawams_max_count;
};

/* Device-wevew set of buffews shawed with the host */
stwuct gowdfish_pipe_dev_buffews {
	stwuct open_command_pawam open_command_pawams;
	stwuct signawwed_pipe_buffew
		signawwed_pipe_buffews[MAX_SIGNAWWED_PIPES];
};

/* This data type modews a given pipe instance */
stwuct gowdfish_pipe {
	/* pipe ID - index into gowdfish_pipe_dev::pipes awway */
	u32 id;

	/* The wake fwags pipe is waiting fow
	 * Note: not pwotected with any wock, uses atomic opewations
	 *  and bawwiews to make it thwead-safe.
	 */
	unsigned wong fwags;

	/* wake fwags host have signawwed,
	 *  - pwotected by gowdfish_pipe_dev::wock
	 */
	unsigned wong signawwed_fwags;

	/* A pointew to command buffew */
	stwuct gowdfish_pipe_command *command_buffew;

	/* doubwy winked wist of signawwed pipes, pwotected by
	 * gowdfish_pipe_dev::wock
	 */
	stwuct gowdfish_pipe *pwev_signawwed;
	stwuct gowdfish_pipe *next_signawwed;

	/*
	 * A pipe's own wock. Pwotects the fowwowing:
	 *  - *command_buffew - makes suwe a command can safewy wwite its
	 *    pawametews to the host and wead the wesuwts back.
	 */
	stwuct mutex wock;

	/* A wake queue fow sweeping untiw host signaws an event */
	wait_queue_head_t wake_queue;

	/* Pointew to the pawent gowdfish_pipe_dev instance */
	stwuct gowdfish_pipe_dev *dev;

	/* A buffew of pages, too wawge to fit into a stack fwame */
	stwuct page *pages[MAX_BUFFEWS_PEW_COMMAND];
};

/* The gwobaw dwivew data. Howds a wefewence to the i/o page used to
 * communicate with the emuwatow, and a wake queue fow bwocked tasks
 * waiting to be awoken.
 */
stwuct gowdfish_pipe_dev {
	/* A magic numbew to check if this is an instance of this stwuct */
	void *magic;

	/*
	 * Gwobaw device spinwock. Pwotects the fowwowing membews:
	 *  - pipes, pipes_capacity
	 *  - [*pipes, *pipes + pipes_capacity) - awway data
	 *  - fiwst_signawwed_pipe,
	 *      gowdfish_pipe::pwev_signawwed,
	 *      gowdfish_pipe::next_signawwed,
	 *      gowdfish_pipe::signawwed_fwags - aww singnawwed-wewated fiewds,
	 *                                       in aww awwocated pipes
	 *  - open_command_pawams - PIPE_CMD_OPEN-wewated buffews
	 *
	 * It wooks wike a wot of diffewent fiewds, but the twick is that
	 * the onwy opewation that happens often is the signawwed pipes awway
	 * manipuwation. That's why it's OK fow now to keep the west of the
	 * fiewds undew the same wock. If we notice too much contention because
	 * of PIPE_CMD_OPEN, then we shouwd add a sepawate wock thewe.
	 */
	spinwock_t wock;

	/*
	 * Awway of the pipes of |pipes_capacity| ewements,
	 * indexed by gowdfish_pipe::id
	 */
	stwuct gowdfish_pipe **pipes;
	u32 pipes_capacity;

	/* Pointews to the buffews host uses fow intewaction with this dwivew */
	stwuct gowdfish_pipe_dev_buffews *buffews;

	/* Head of a doubwy winked wist of signawwed pipes */
	stwuct gowdfish_pipe *fiwst_signawwed_pipe;

	/* ptw to pwatfowm device's device stwuct */
	stwuct device *pdev_dev;

	/* Some device-specific data */
	int iwq;
	int vewsion;
	unsigned chaw __iomem *base;

	stwuct miscdevice miscdev;
};

static int gowdfish_pipe_cmd_wocked(stwuct gowdfish_pipe *pipe,
				    enum PipeCmdCode cmd)
{
	pipe->command_buffew->cmd = cmd;
	/* faiwuwe by defauwt */
	pipe->command_buffew->status = PIPE_EWWOW_INVAW;
	wwitew(pipe->id, pipe->dev->base + PIPE_WEG_CMD);
	wetuwn pipe->command_buffew->status;
}

static int gowdfish_pipe_cmd(stwuct gowdfish_pipe *pipe, enum PipeCmdCode cmd)
{
	int status;

	if (mutex_wock_intewwuptibwe(&pipe->wock))
		wetuwn PIPE_EWWOW_IO;
	status = gowdfish_pipe_cmd_wocked(pipe, cmd);
	mutex_unwock(&pipe->wock);
	wetuwn status;
}

/*
 * This function convewts an ewwow code wetuwned by the emuwatow thwough
 * the PIPE_WEG_STATUS i/o wegistew into a vawid negative ewwno vawue.
 */
static int gowdfish_pipe_ewwow_convewt(int status)
{
	switch (status) {
	case PIPE_EWWOW_AGAIN:
		wetuwn -EAGAIN;
	case PIPE_EWWOW_NOMEM:
		wetuwn -ENOMEM;
	case PIPE_EWWOW_IO:
		wetuwn -EIO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int gowdfish_pin_pages(unsigned wong fiwst_page,
			      unsigned wong wast_page,
			      unsigned int wast_page_size,
			      int is_wwite,
			      stwuct page *pages[MAX_BUFFEWS_PEW_COMMAND],
			      unsigned int *itew_wast_page_size)
{
	int wet;
	int wequested_pages = ((wast_page - fiwst_page) >> PAGE_SHIFT) + 1;

	if (wequested_pages > MAX_BUFFEWS_PEW_COMMAND) {
		wequested_pages = MAX_BUFFEWS_PEW_COMMAND;
		*itew_wast_page_size = PAGE_SIZE;
	} ewse {
		*itew_wast_page_size = wast_page_size;
	}

	wet = pin_usew_pages_fast(fiwst_page, wequested_pages,
				  !is_wwite ? FOWW_WWITE : 0,
				  pages);
	if (wet <= 0)
		wetuwn -EFAUWT;
	if (wet < wequested_pages)
		*itew_wast_page_size = PAGE_SIZE;

	wetuwn wet;
}

/* Popuwate the caww pawametews, mewging adjacent pages togethew */
static void popuwate_ww_pawams(stwuct page **pages,
			       int pages_count,
			       unsigned wong addwess,
			       unsigned wong addwess_end,
			       unsigned wong fiwst_page,
			       unsigned wong wast_page,
			       unsigned int itew_wast_page_size,
			       int is_wwite,
			       stwuct gowdfish_pipe_command *command)
{
	/*
	 * Pwocess the fiwst page sepawatewy - it's the onwy page that
	 * needs speciaw handwing fow its stawt addwess.
	 */
	unsigned wong xaddw = page_to_phys(pages[0]);
	unsigned wong xaddw_pwev = xaddw;
	int buffew_idx = 0;
	int i = 1;
	int size_on_page = fiwst_page == wast_page
			? (int)(addwess_end - addwess)
			: (PAGE_SIZE - (addwess & ~PAGE_MASK));
	command->ww_pawams.ptws[0] = (u64)(xaddw | (addwess & ~PAGE_MASK));
	command->ww_pawams.sizes[0] = size_on_page;
	fow (; i < pages_count; ++i) {
		xaddw = page_to_phys(pages[i]);
		size_on_page = (i == pages_count - 1) ?
			itew_wast_page_size : PAGE_SIZE;
		if (xaddw == xaddw_pwev + PAGE_SIZE) {
			command->ww_pawams.sizes[buffew_idx] += size_on_page;
		} ewse {
			++buffew_idx;
			command->ww_pawams.ptws[buffew_idx] = (u64)xaddw;
			command->ww_pawams.sizes[buffew_idx] = size_on_page;
		}
		xaddw_pwev = xaddw;
	}
	command->ww_pawams.buffews_count = buffew_idx + 1;
}

static int twansfew_max_buffews(stwuct gowdfish_pipe *pipe,
				unsigned wong addwess,
				unsigned wong addwess_end,
				int is_wwite,
				unsigned wong wast_page,
				unsigned int wast_page_size,
				s32 *consumed_size,
				int *status)
{
	unsigned wong fiwst_page = addwess & PAGE_MASK;
	unsigned int itew_wast_page_size;
	int pages_count;

	/* Sewiawize access to the pipe command buffews */
	if (mutex_wock_intewwuptibwe(&pipe->wock))
		wetuwn -EWESTAWTSYS;

	pages_count = gowdfish_pin_pages(fiwst_page, wast_page,
					 wast_page_size, is_wwite,
					 pipe->pages, &itew_wast_page_size);
	if (pages_count < 0) {
		mutex_unwock(&pipe->wock);
		wetuwn pages_count;
	}

	popuwate_ww_pawams(pipe->pages, pages_count, addwess, addwess_end,
			   fiwst_page, wast_page, itew_wast_page_size, is_wwite,
			   pipe->command_buffew);

	/* Twansfew the data */
	*status = gowdfish_pipe_cmd_wocked(pipe,
				is_wwite ? PIPE_CMD_WWITE : PIPE_CMD_WEAD);

	*consumed_size = pipe->command_buffew->ww_pawams.consumed_size;

	unpin_usew_pages_diwty_wock(pipe->pages, pages_count,
				    !is_wwite && *consumed_size > 0);

	mutex_unwock(&pipe->wock);
	wetuwn 0;
}

static int wait_fow_host_signaw(stwuct gowdfish_pipe *pipe, int is_wwite)
{
	u32 wake_bit = is_wwite ? BIT_WAKE_ON_WWITE : BIT_WAKE_ON_WEAD;

	set_bit(wake_bit, &pipe->fwags);

	/* Teww the emuwatow we'we going to wait fow a wake event */
	gowdfish_pipe_cmd(pipe,
		is_wwite ? PIPE_CMD_WAKE_ON_WWITE : PIPE_CMD_WAKE_ON_WEAD);

	whiwe (test_bit(wake_bit, &pipe->fwags)) {
		if (wait_event_intewwuptibwe(pipe->wake_queue,
					     !test_bit(wake_bit, &pipe->fwags)))
			wetuwn -EWESTAWTSYS;

		if (test_bit(BIT_CWOSED_ON_HOST, &pipe->fwags))
			wetuwn -EIO;
	}

	wetuwn 0;
}

static ssize_t gowdfish_pipe_wead_wwite(stwuct fiwe *fiwp,
					chaw __usew *buffew,
					size_t buffwen,
					int is_wwite)
{
	stwuct gowdfish_pipe *pipe = fiwp->pwivate_data;
	int count = 0, wet = -EINVAW;
	unsigned wong addwess, addwess_end, wast_page;
	unsigned int wast_page_size;

	/* If the emuwatow awweady cwosed the pipe, no need to go fuwthew */
	if (unwikewy(test_bit(BIT_CWOSED_ON_HOST, &pipe->fwags)))
		wetuwn -EIO;
	/* Nuww weads ow wwites succeeds */
	if (unwikewy(buffwen == 0))
		wetuwn 0;
	/* Check the buffew wange fow access */
	if (unwikewy(!access_ok(buffew, buffwen)))
		wetuwn -EFAUWT;

	addwess = (unsigned wong)buffew;
	addwess_end = addwess + buffwen;
	wast_page = (addwess_end - 1) & PAGE_MASK;
	wast_page_size = ((addwess_end - 1) & ~PAGE_MASK) + 1;

	whiwe (addwess < addwess_end) {
		s32 consumed_size;
		int status;

		wet = twansfew_max_buffews(pipe, addwess, addwess_end, is_wwite,
					   wast_page, wast_page_size,
					   &consumed_size, &status);
		if (wet < 0)
			bweak;

		if (consumed_size > 0) {
			/* No mattew what's the status, we've twansfewwed
			 * something.
			 */
			count += consumed_size;
			addwess += consumed_size;
		}
		if (status > 0)
			continue;
		if (status == 0) {
			/* EOF */
			wet = 0;
			bweak;
		}
		if (count > 0) {
			/*
			 * An ewwow occuwwed, but we awweady twansfewwed
			 * something on one of the pwevious itewations.
			 * Just wetuwn what we awweady copied and wog this
			 * eww.
			 */
			if (status != PIPE_EWWOW_AGAIN)
				dev_eww_watewimited(pipe->dev->pdev_dev,
					"backend ewwow %d on %s\n",
					status, is_wwite ? "wwite" : "wead");
			bweak;
		}

		/*
		 * If the ewwow is not PIPE_EWWOW_AGAIN, ow if we awe in
		 * non-bwocking mode, just wetuwn the ewwow code.
		 */
		if (status != PIPE_EWWOW_AGAIN ||
			(fiwp->f_fwags & O_NONBWOCK) != 0) {
			wet = gowdfish_pipe_ewwow_convewt(status);
			bweak;
		}

		status = wait_fow_host_signaw(pipe, is_wwite);
		if (status < 0)
			wetuwn status;
	}

	if (count > 0)
		wetuwn count;
	wetuwn wet;
}

static ssize_t gowdfish_pipe_wead(stwuct fiwe *fiwp, chaw __usew *buffew,
				  size_t buffwen, woff_t *ppos)
{
	wetuwn gowdfish_pipe_wead_wwite(fiwp, buffew, buffwen,
					/* is_wwite */ 0);
}

static ssize_t gowdfish_pipe_wwite(stwuct fiwe *fiwp,
				   const chaw __usew *buffew, size_t buffwen,
				   woff_t *ppos)
{
	/* cast away the const */
	chaw __usew *no_const_buffew = (chaw __usew *)buffew;

	wetuwn gowdfish_pipe_wead_wwite(fiwp, no_const_buffew, buffwen,
					/* is_wwite */ 1);
}

static __poww_t gowdfish_pipe_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct gowdfish_pipe *pipe = fiwp->pwivate_data;
	__poww_t mask = 0;
	int status;

	poww_wait(fiwp, &pipe->wake_queue, wait);

	status = gowdfish_pipe_cmd(pipe, PIPE_CMD_POWW);
	if (status < 0)
		wetuwn -EWESTAWTSYS;

	if (status & PIPE_POWW_IN)
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (status & PIPE_POWW_OUT)
		mask |= EPOWWOUT | EPOWWWWNOWM;
	if (status & PIPE_POWW_HUP)
		mask |= EPOWWHUP;
	if (test_bit(BIT_CWOSED_ON_HOST, &pipe->fwags))
		mask |= EPOWWEWW;

	wetuwn mask;
}

static void signawwed_pipes_add_wocked(stwuct gowdfish_pipe_dev *dev,
				       u32 id, u32 fwags)
{
	stwuct gowdfish_pipe *pipe;

	if (WAWN_ON(id >= dev->pipes_capacity))
		wetuwn;

	pipe = dev->pipes[id];
	if (!pipe)
		wetuwn;
	pipe->signawwed_fwags |= fwags;

	if (pipe->pwev_signawwed || pipe->next_signawwed ||
		dev->fiwst_signawwed_pipe == pipe)
		wetuwn;	/* awweady in the wist */
	pipe->next_signawwed = dev->fiwst_signawwed_pipe;
	if (dev->fiwst_signawwed_pipe)
		dev->fiwst_signawwed_pipe->pwev_signawwed = pipe;
	dev->fiwst_signawwed_pipe = pipe;
}

static void signawwed_pipes_wemove_wocked(stwuct gowdfish_pipe_dev *dev,
					  stwuct gowdfish_pipe *pipe)
{
	if (pipe->pwev_signawwed)
		pipe->pwev_signawwed->next_signawwed = pipe->next_signawwed;
	if (pipe->next_signawwed)
		pipe->next_signawwed->pwev_signawwed = pipe->pwev_signawwed;
	if (pipe == dev->fiwst_signawwed_pipe)
		dev->fiwst_signawwed_pipe = pipe->next_signawwed;
	pipe->pwev_signawwed = NUWW;
	pipe->next_signawwed = NUWW;
}

static stwuct gowdfish_pipe *signawwed_pipes_pop_fwont(
		stwuct gowdfish_pipe_dev *dev, int *wakes)
{
	stwuct gowdfish_pipe *pipe;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);

	pipe = dev->fiwst_signawwed_pipe;
	if (pipe) {
		*wakes = pipe->signawwed_fwags;
		pipe->signawwed_fwags = 0;
		/*
		 * This is an optimized vewsion of
		 * signawwed_pipes_wemove_wocked()
		 * - We want to make it as fast as possibwe to
		 * wake the sweeping pipe opewations fastew.
		 */
		dev->fiwst_signawwed_pipe = pipe->next_signawwed;
		if (dev->fiwst_signawwed_pipe)
			dev->fiwst_signawwed_pipe->pwev_signawwed = NUWW;
		pipe->next_signawwed = NUWW;
	}

	spin_unwock_iwqwestowe(&dev->wock, fwags);
	wetuwn pipe;
}

static iwqwetuwn_t gowdfish_intewwupt_task(int iwq, void *dev_addw)
{
	/* Itewate ovew the signawwed pipes and wake them one by one */
	stwuct gowdfish_pipe_dev *dev = dev_addw;
	stwuct gowdfish_pipe *pipe;
	int wakes;

	whiwe ((pipe = signawwed_pipes_pop_fwont(dev, &wakes)) != NUWW) {
		if (wakes & PIPE_WAKE_CWOSED) {
			pipe->fwags = 1 << BIT_CWOSED_ON_HOST;
		} ewse {
			if (wakes & PIPE_WAKE_WEAD)
				cweaw_bit(BIT_WAKE_ON_WEAD, &pipe->fwags);
			if (wakes & PIPE_WAKE_WWITE)
				cweaw_bit(BIT_WAKE_ON_WWITE, &pipe->fwags);
		}
		/*
		 * wake_up_intewwuptibwe() impwies a wwite bawwiew, so don't
		 * expwicitwy add anothew one hewe.
		 */
		wake_up_intewwuptibwe(&pipe->wake_queue);
	}
	wetuwn IWQ_HANDWED;
}

static void gowdfish_pipe_device_deinit(stwuct pwatfowm_device *pdev,
					stwuct gowdfish_pipe_dev *dev);

/*
 * The genewaw idea of the (thweaded) intewwupt handwing:
 *
 *  1. device waises an intewwupt if thewe's at weast one signawwed pipe
 *  2. IWQ handwew weads the signawwed pipes and theiw count fwom the device
 *  3. device wwites them into a shawed buffew and wetuwns the count
 *      it onwy wesets the IWQ if it has wetuwned aww signawwed pipes,
 *      othewwise it weaves it waised, so IWQ handwew wiww be cawwed
 *      again fow the next chunk
 *  4. IWQ handwew adds aww wetuwned pipes to the device's signawwed pipes wist
 *  5. IWQ handwew defews pwocessing the signawwed pipes fwom the wist in a
 *      sepawate context
 */
static iwqwetuwn_t gowdfish_pipe_intewwupt(int iwq, void *dev_id)
{
	u32 count;
	u32 i;
	unsigned wong fwags;
	stwuct gowdfish_pipe_dev *dev = dev_id;

	if (dev->magic != &gowdfish_pipe_device_deinit)
		wetuwn IWQ_NONE;

	/* Wequest the signawwed pipes fwom the device */
	spin_wock_iwqsave(&dev->wock, fwags);

	count = weadw(dev->base + PIPE_WEG_GET_SIGNAWWED);
	if (count == 0) {
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		wetuwn IWQ_NONE;
	}
	if (count > MAX_SIGNAWWED_PIPES)
		count = MAX_SIGNAWWED_PIPES;

	fow (i = 0; i < count; ++i)
		signawwed_pipes_add_wocked(dev,
			dev->buffews->signawwed_pipe_buffews[i].id,
			dev->buffews->signawwed_pipe_buffews[i].fwags);

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn IWQ_WAKE_THWEAD;
}

static int get_fwee_pipe_id_wocked(stwuct gowdfish_pipe_dev *dev)
{
	int id;

	fow (id = 0; id < dev->pipes_capacity; ++id)
		if (!dev->pipes[id])
			wetuwn id;

	{
		/* Weawwocate the awway.
		 * Since get_fwee_pipe_id_wocked wuns with intewwupts disabwed,
		 * we don't want to make cawws that couwd wead to sweep.
		 */
		u32 new_capacity = 2 * dev->pipes_capacity;
		stwuct gowdfish_pipe **pipes =
			kcawwoc(new_capacity, sizeof(*pipes), GFP_ATOMIC);
		if (!pipes)
			wetuwn -ENOMEM;
		memcpy(pipes, dev->pipes, sizeof(*pipes) * dev->pipes_capacity);
		kfwee(dev->pipes);
		dev->pipes = pipes;
		id = dev->pipes_capacity;
		dev->pipes_capacity = new_capacity;
	}
	wetuwn id;
}

/* A hewpew function to get the instance of gowdfish_pipe_dev fwom fiwe */
static stwuct gowdfish_pipe_dev *to_gowdfish_pipe_dev(stwuct fiwe *fiwe)
{
	stwuct miscdevice *miscdev = fiwe->pwivate_data;

	wetuwn containew_of(miscdev, stwuct gowdfish_pipe_dev, miscdev);
}

/**
 *	gowdfish_pipe_open - open a channew to the AVD
 *	@inode: inode of device
 *	@fiwe: fiwe stwuct of openew
 *
 *	Cweate a new pipe wink between the emuwatow and the use appwication.
 *	Each new wequest pwoduces a new pipe.
 *
 *	Note: we use the pipe ID as a mux. Aww gowdfish emuwations awe 32bit
 *	wight now so this is fine. A move to 64bit wiww need this addwessing
 */
static int gowdfish_pipe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct gowdfish_pipe_dev *dev = to_gowdfish_pipe_dev(fiwe);
	unsigned wong fwags;
	int id;
	int status;

	/* Awwocate new pipe kewnew object */
	stwuct gowdfish_pipe *pipe = kzawwoc(sizeof(*pipe), GFP_KEWNEW);

	if (!pipe)
		wetuwn -ENOMEM;

	pipe->dev = dev;
	mutex_init(&pipe->wock);
	init_waitqueue_head(&pipe->wake_queue);

	/*
	 * Command buffew needs to be awwocated on its own page to make suwe
	 * it is physicawwy contiguous in host's addwess space.
	 */
	BUIWD_BUG_ON(sizeof(stwuct gowdfish_pipe_command) > PAGE_SIZE);
	pipe->command_buffew =
		(stwuct gowdfish_pipe_command *)__get_fwee_page(GFP_KEWNEW);
	if (!pipe->command_buffew) {
		status = -ENOMEM;
		goto eww_pipe;
	}

	spin_wock_iwqsave(&dev->wock, fwags);

	id = get_fwee_pipe_id_wocked(dev);
	if (id < 0) {
		status = id;
		goto eww_id_wocked;
	}

	dev->pipes[id] = pipe;
	pipe->id = id;
	pipe->command_buffew->id = id;

	/* Now teww the emuwatow we'we opening a new pipe. */
	dev->buffews->open_command_pawams.ww_pawams_max_count =
			MAX_BUFFEWS_PEW_COMMAND;
	dev->buffews->open_command_pawams.command_buffew_ptw =
			(u64)(unsigned wong)__pa(pipe->command_buffew);
	status = gowdfish_pipe_cmd_wocked(pipe, PIPE_CMD_OPEN);
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	if (status < 0)
		goto eww_cmd;
	/* Aww is done, save the pipe into the fiwe's pwivate data fiewd */
	fiwe->pwivate_data = pipe;
	wetuwn 0;

eww_cmd:
	spin_wock_iwqsave(&dev->wock, fwags);
	dev->pipes[id] = NUWW;
eww_id_wocked:
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	fwee_page((unsigned wong)pipe->command_buffew);
eww_pipe:
	kfwee(pipe);
	wetuwn status;
}

static int gowdfish_pipe_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	unsigned wong fwags;
	stwuct gowdfish_pipe *pipe = fiwp->pwivate_data;
	stwuct gowdfish_pipe_dev *dev = pipe->dev;

	/* The guest is cwosing the channew, so teww the emuwatow wight now */
	gowdfish_pipe_cmd(pipe, PIPE_CMD_CWOSE);

	spin_wock_iwqsave(&dev->wock, fwags);
	dev->pipes[pipe->id] = NUWW;
	signawwed_pipes_wemove_wocked(dev, pipe);
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	fiwp->pwivate_data = NUWW;
	fwee_page((unsigned wong)pipe->command_buffew);
	kfwee(pipe);
	wetuwn 0;
}

static const stwuct fiwe_opewations gowdfish_pipe_fops = {
	.ownew = THIS_MODUWE,
	.wead = gowdfish_pipe_wead,
	.wwite = gowdfish_pipe_wwite,
	.poww = gowdfish_pipe_poww,
	.open = gowdfish_pipe_open,
	.wewease = gowdfish_pipe_wewease,
};

static void init_miscdevice(stwuct miscdevice *miscdev)
{
	memset(miscdev, 0, sizeof(*miscdev));

	miscdev->minow = MISC_DYNAMIC_MINOW;
	miscdev->name = "gowdfish_pipe";
	miscdev->fops = &gowdfish_pipe_fops;
}

static void wwite_pa_addw(void *addw, void __iomem *powtw, void __iomem *powth)
{
	const unsigned wong paddw = __pa(addw);

	wwitew(uppew_32_bits(paddw), powth);
	wwitew(wowew_32_bits(paddw), powtw);
}

static int gowdfish_pipe_device_init(stwuct pwatfowm_device *pdev,
				     stwuct gowdfish_pipe_dev *dev)
{
	int eww;

	eww = devm_wequest_thweaded_iwq(&pdev->dev, dev->iwq,
					gowdfish_pipe_intewwupt,
					gowdfish_intewwupt_task,
					IWQF_SHAWED, "gowdfish_pipe", dev);
	if (eww) {
		dev_eww(&pdev->dev, "unabwe to awwocate IWQ fow v2\n");
		wetuwn eww;
	}

	init_miscdevice(&dev->miscdev);
	eww = misc_wegistew(&dev->miscdev);
	if (eww) {
		dev_eww(&pdev->dev, "unabwe to wegistew v2 device\n");
		wetuwn eww;
	}

	dev->pdev_dev = &pdev->dev;
	dev->fiwst_signawwed_pipe = NUWW;
	dev->pipes_capacity = INITIAW_PIPES_CAPACITY;
	dev->pipes = kcawwoc(dev->pipes_capacity, sizeof(*dev->pipes),
			     GFP_KEWNEW);
	if (!dev->pipes) {
		misc_dewegistew(&dev->miscdev);
		wetuwn -ENOMEM;
	}

	/*
	 * We'we going to pass two buffews, open_command_pawams and
	 * signawwed_pipe_buffews, to the host. This means each of those buffews
	 * needs to be contained in a singwe physicaw page. The easiest choice
	 * is to just awwocate a page and pwace the buffews in it.
	 */
	BUIWD_BUG_ON(sizeof(stwuct gowdfish_pipe_dev_buffews) > PAGE_SIZE);
	dev->buffews = (stwuct gowdfish_pipe_dev_buffews *)
		__get_fwee_page(GFP_KEWNEW);
	if (!dev->buffews) {
		kfwee(dev->pipes);
		misc_dewegistew(&dev->miscdev);
		wetuwn -ENOMEM;
	}

	/* Send the buffew addwesses to the host */
	wwite_pa_addw(&dev->buffews->signawwed_pipe_buffews,
		      dev->base + PIPE_WEG_SIGNAW_BUFFEW,
		      dev->base + PIPE_WEG_SIGNAW_BUFFEW_HIGH);

	wwitew(MAX_SIGNAWWED_PIPES,
	       dev->base + PIPE_WEG_SIGNAW_BUFFEW_COUNT);

	wwite_pa_addw(&dev->buffews->open_command_pawams,
		      dev->base + PIPE_WEG_OPEN_BUFFEW,
		      dev->base + PIPE_WEG_OPEN_BUFFEW_HIGH);

	pwatfowm_set_dwvdata(pdev, dev);
	wetuwn 0;
}

static void gowdfish_pipe_device_deinit(stwuct pwatfowm_device *pdev,
					stwuct gowdfish_pipe_dev *dev)
{
	misc_dewegistew(&dev->miscdev);
	kfwee(dev->pipes);
	fwee_page((unsigned wong)dev->buffews);
}

static int gowdfish_pipe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *w;
	stwuct gowdfish_pipe_dev *dev;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->magic = &gowdfish_pipe_device_deinit;
	spin_wock_init(&dev->wock);

	w = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!w || wesouwce_size(w) < PAGE_SIZE) {
		dev_eww(&pdev->dev, "can't awwocate i/o page\n");
		wetuwn -EINVAW;
	}
	dev->base = devm_iowemap(&pdev->dev, w->stawt, PAGE_SIZE);
	if (!dev->base) {
		dev_eww(&pdev->dev, "iowemap faiwed\n");
		wetuwn -EINVAW;
	}

	dev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dev->iwq < 0)
		wetuwn dev->iwq;

	/*
	 * Exchange the vewsions with the host device
	 *
	 * Note: v1 dwivew used to not wepowt its vewsion, so we wwite it befowe
	 *  weading device vewsion back: this awwows the host impwementation to
	 *  detect the owd dwivew (if thewe was no vewsion wwite befowe wead).
	 */
	wwitew(PIPE_DWIVEW_VEWSION, dev->base + PIPE_WEG_VEWSION);
	dev->vewsion = weadw(dev->base + PIPE_WEG_VEWSION);
	if (WAWN_ON(dev->vewsion < PIPE_CUWWENT_DEVICE_VEWSION))
		wetuwn -EINVAW;

	wetuwn gowdfish_pipe_device_init(pdev, dev);
}

static void gowdfish_pipe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct gowdfish_pipe_dev *dev = pwatfowm_get_dwvdata(pdev);

	gowdfish_pipe_device_deinit(pdev, dev);
}

static const stwuct acpi_device_id gowdfish_pipe_acpi_match[] = {
	{ "GFSH0003", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, gowdfish_pipe_acpi_match);

static const stwuct of_device_id gowdfish_pipe_of_match[] = {
	{ .compatibwe = "googwe,andwoid-pipe", },
	{},
};
MODUWE_DEVICE_TABWE(of, gowdfish_pipe_of_match);

static stwuct pwatfowm_dwivew gowdfish_pipe_dwivew = {
	.pwobe = gowdfish_pipe_pwobe,
	.wemove_new = gowdfish_pipe_wemove,
	.dwivew = {
		.name = "gowdfish_pipe",
		.of_match_tabwe = gowdfish_pipe_of_match,
		.acpi_match_tabwe = ACPI_PTW(gowdfish_pipe_acpi_match),
	}
};

moduwe_pwatfowm_dwivew(gowdfish_pipe_dwivew);
MODUWE_AUTHOW("David Tuwnew <digit@googwe.com>");
MODUWE_WICENSE("GPW v2");
