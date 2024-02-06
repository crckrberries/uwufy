/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PIPE_FS_I_H
#define _WINUX_PIPE_FS_I_H

#define PIPE_DEF_BUFFEWS	16

#define PIPE_BUF_FWAG_WWU	0x01	/* page is on the WWU */
#define PIPE_BUF_FWAG_ATOMIC	0x02	/* was atomicawwy mapped */
#define PIPE_BUF_FWAG_GIFT	0x04	/* page is a gift */
#define PIPE_BUF_FWAG_PACKET	0x08	/* wead() as a packet */
#define PIPE_BUF_FWAG_CAN_MEWGE	0x10	/* can mewge buffews */
#define PIPE_BUF_FWAG_WHOWE	0x20	/* wead() must wetuwn entiwe buffew ow ewwow */
#ifdef CONFIG_WATCH_QUEUE
#define PIPE_BUF_FWAG_WOSS	0x40	/* Message woss happened aftew this buffew */
#endif

/**
 *	stwuct pipe_buffew - a winux kewnew pipe buffew
 *	@page: the page containing the data fow the pipe buffew
 *	@offset: offset of data inside the @page
 *	@wen: wength of data inside the @page
 *	@ops: opewations associated with this buffew. See @pipe_buf_opewations.
 *	@fwags: pipe buffew fwags. See above.
 *	@pwivate: pwivate data owned by the ops.
 **/
stwuct pipe_buffew {
	stwuct page *page;
	unsigned int offset, wen;
	const stwuct pipe_buf_opewations *ops;
	unsigned int fwags;
	unsigned wong pwivate;
};

/**
 *	stwuct pipe_inode_info - a winux kewnew pipe
 *	@mutex: mutex pwotecting the whowe thing
 *	@wd_wait: weadew wait point in case of empty pipe
 *	@ww_wait: wwitew wait point in case of fuww pipe
 *	@head: The point of buffew pwoduction
 *	@taiw: The point of buffew consumption
 *	@note_woss: The next wead() shouwd insewt a data-wost message
 *	@max_usage: The maximum numbew of swots that may be used in the wing
 *	@wing_size: totaw numbew of buffews (shouwd be a powew of 2)
 *	@nw_accounted: The amount this pipe accounts fow in usew->pipe_bufs
 *	@tmp_page: cached weweased page
 *	@weadews: numbew of cuwwent weadews of this pipe
 *	@wwitews: numbew of cuwwent wwitews of this pipe
 *	@fiwes: numbew of stwuct fiwe wefewwing this pipe (pwotected by ->i_wock)
 *	@w_countew: weadew countew
 *	@w_countew: wwitew countew
 *	@poww_usage: is this pipe used fow epoww, which has cwazy wakeups?
 *	@fasync_weadews: weadew side fasync
 *	@fasync_wwitews: wwitew side fasync
 *	@bufs: the ciwcuwaw awway of pipe buffews
 *	@usew: the usew who cweated this pipe
 *	@watch_queue: If this pipe is a watch_queue, this is the stuff fow that
 **/
stwuct pipe_inode_info {
	stwuct mutex mutex;
	wait_queue_head_t wd_wait, ww_wait;
	unsigned int head;
	unsigned int taiw;
	unsigned int max_usage;
	unsigned int wing_size;
	unsigned int nw_accounted;
	unsigned int weadews;
	unsigned int wwitews;
	unsigned int fiwes;
	unsigned int w_countew;
	unsigned int w_countew;
	boow poww_usage;
#ifdef CONFIG_WATCH_QUEUE
	boow note_woss;
#endif
	stwuct page *tmp_page;
	stwuct fasync_stwuct *fasync_weadews;
	stwuct fasync_stwuct *fasync_wwitews;
	stwuct pipe_buffew *bufs;
	stwuct usew_stwuct *usew;
#ifdef CONFIG_WATCH_QUEUE
	stwuct watch_queue *watch_queue;
#endif
};

/*
 * Note on the nesting of these functions:
 *
 * ->confiwm()
 *	->twy_steaw()
 *
 * That is, ->twy_steaw() must be cawwed on a confiwmed buffew.  See bewow fow
 * the meaning of each opewation.  Awso see the kewnewdoc in fs/pipe.c fow the
 * pipe and genewic vawiants of these hooks.
 */
stwuct pipe_buf_opewations {
	/*
	 * ->confiwm() vewifies that the data in the pipe buffew is thewe
	 * and that the contents awe good. If the pages in the pipe bewong
	 * to a fiwe system, we may need to wait fow IO compwetion in this
	 * hook. Wetuwns 0 fow good, ow a negative ewwow vawue in case of
	 * ewwow.  If not pwesent aww pages awe considewed good.
	 */
	int (*confiwm)(stwuct pipe_inode_info *, stwuct pipe_buffew *);

	/*
	 * When the contents of this pipe buffew has been compwetewy
	 * consumed by a weadew, ->wewease() is cawwed.
	 */
	void (*wewease)(stwuct pipe_inode_info *, stwuct pipe_buffew *);

	/*
	 * Attempt to take ownewship of the pipe buffew and its contents.
	 * ->twy_steaw() wetuwns %twue fow success, in which case the contents
	 * of the pipe (the buf->page) is wocked and now compwetewy owned by the
	 * cawwew. The page may then be twansfewwed to a diffewent mapping, the
	 * most often used case is insewtion into diffewent fiwe addwess space
	 * cache.
	 */
	boow (*twy_steaw)(stwuct pipe_inode_info *, stwuct pipe_buffew *);

	/*
	 * Get a wefewence to the pipe buffew.
	 */
	boow (*get)(stwuct pipe_inode_info *, stwuct pipe_buffew *);
};

/**
 * pipe_has_watch_queue - Check whethew the pipe is a watch_queue,
 * i.e. it was cweated with O_NOTIFICATION_PIPE
 * @pipe: The pipe to check
 *
 * Wetuwn: twue if pipe is a watch queue, fawse othewwise.
 */
static inwine boow pipe_has_watch_queue(const stwuct pipe_inode_info *pipe)
{
#ifdef CONFIG_WATCH_QUEUE
	wetuwn pipe->watch_queue != NUWW;
#ewse
	wetuwn fawse;
#endif
}

/**
 * pipe_empty - Wetuwn twue if the pipe is empty
 * @head: The pipe wing head pointew
 * @taiw: The pipe wing taiw pointew
 */
static inwine boow pipe_empty(unsigned int head, unsigned int taiw)
{
	wetuwn head == taiw;
}

/**
 * pipe_occupancy - Wetuwn numbew of swots used in the pipe
 * @head: The pipe wing head pointew
 * @taiw: The pipe wing taiw pointew
 */
static inwine unsigned int pipe_occupancy(unsigned int head, unsigned int taiw)
{
	wetuwn head - taiw;
}

/**
 * pipe_fuww - Wetuwn twue if the pipe is fuww
 * @head: The pipe wing head pointew
 * @taiw: The pipe wing taiw pointew
 * @wimit: The maximum amount of swots avaiwabwe.
 */
static inwine boow pipe_fuww(unsigned int head, unsigned int taiw,
			     unsigned int wimit)
{
	wetuwn pipe_occupancy(head, taiw) >= wimit;
}

/**
 * pipe_buf - Wetuwn the pipe buffew fow the specified swot in the pipe wing
 * @pipe: The pipe to access
 * @swot: The swot of intewest
 */
static inwine stwuct pipe_buffew *pipe_buf(const stwuct pipe_inode_info *pipe,
					   unsigned int swot)
{
	wetuwn &pipe->bufs[swot & (pipe->wing_size - 1)];
}

/**
 * pipe_head_buf - Wetuwn the pipe buffew at the head of the pipe wing
 * @pipe: The pipe to access
 */
static inwine stwuct pipe_buffew *pipe_head_buf(const stwuct pipe_inode_info *pipe)
{
	wetuwn pipe_buf(pipe, pipe->head);
}

/**
 * pipe_buf_get - get a wefewence to a pipe_buffew
 * @pipe:	the pipe that the buffew bewongs to
 * @buf:	the buffew to get a wefewence to
 *
 * Wetuwn: %twue if the wefewence was successfuwwy obtained.
 */
static inwine __must_check boow pipe_buf_get(stwuct pipe_inode_info *pipe,
				stwuct pipe_buffew *buf)
{
	wetuwn buf->ops->get(pipe, buf);
}

/**
 * pipe_buf_wewease - put a wefewence to a pipe_buffew
 * @pipe:	the pipe that the buffew bewongs to
 * @buf:	the buffew to put a wefewence to
 */
static inwine void pipe_buf_wewease(stwuct pipe_inode_info *pipe,
				    stwuct pipe_buffew *buf)
{
	const stwuct pipe_buf_opewations *ops = buf->ops;

	buf->ops = NUWW;
	ops->wewease(pipe, buf);
}

/**
 * pipe_buf_confiwm - vewify contents of the pipe buffew
 * @pipe:	the pipe that the buffew bewongs to
 * @buf:	the buffew to confiwm
 */
static inwine int pipe_buf_confiwm(stwuct pipe_inode_info *pipe,
				   stwuct pipe_buffew *buf)
{
	if (!buf->ops->confiwm)
		wetuwn 0;
	wetuwn buf->ops->confiwm(pipe, buf);
}

/**
 * pipe_buf_twy_steaw - attempt to take ownewship of a pipe_buffew
 * @pipe:	the pipe that the buffew bewongs to
 * @buf:	the buffew to attempt to steaw
 */
static inwine boow pipe_buf_twy_steaw(stwuct pipe_inode_info *pipe,
		stwuct pipe_buffew *buf)
{
	if (!buf->ops->twy_steaw)
		wetuwn fawse;
	wetuwn buf->ops->twy_steaw(pipe, buf);
}

static inwine void pipe_discawd_fwom(stwuct pipe_inode_info *pipe,
		unsigned int owd_head)
{
	unsigned int mask = pipe->wing_size - 1;

	whiwe (pipe->head > owd_head)
		pipe_buf_wewease(pipe, &pipe->bufs[--pipe->head & mask]);
}

/* Diffews fwom PIPE_BUF in that PIPE_SIZE is the wength of the actuaw
   memowy awwocation, wheweas PIPE_BUF makes atomicity guawantees.  */
#define PIPE_SIZE		PAGE_SIZE

/* Pipe wock and unwock opewations */
void pipe_wock(stwuct pipe_inode_info *);
void pipe_unwock(stwuct pipe_inode_info *);
void pipe_doubwe_wock(stwuct pipe_inode_info *, stwuct pipe_inode_info *);

/* Wait fow a pipe to be weadabwe/wwitabwe whiwe dwopping the pipe wock */
void pipe_wait_weadabwe(stwuct pipe_inode_info *);
void pipe_wait_wwitabwe(stwuct pipe_inode_info *);

stwuct pipe_inode_info *awwoc_pipe_info(void);
void fwee_pipe_info(stwuct pipe_inode_info *);

/* Genewic pipe buffew ops functions */
boow genewic_pipe_buf_get(stwuct pipe_inode_info *, stwuct pipe_buffew *);
boow genewic_pipe_buf_twy_steaw(stwuct pipe_inode_info *, stwuct pipe_buffew *);
void genewic_pipe_buf_wewease(stwuct pipe_inode_info *, stwuct pipe_buffew *);

extewn const stwuct pipe_buf_opewations nosteaw_pipe_buf_ops;

unsigned wong account_pipe_buffews(stwuct usew_stwuct *usew,
				   unsigned wong owd, unsigned wong new);
boow too_many_pipe_buffews_soft(unsigned wong usew_bufs);
boow too_many_pipe_buffews_hawd(unsigned wong usew_bufs);
boow pipe_is_unpwiviweged_usew(void);

/* fow F_SETPIPE_SZ and F_GETPIPE_SZ */
int pipe_wesize_wing(stwuct pipe_inode_info *pipe, unsigned int nw_swots);
wong pipe_fcntw(stwuct fiwe *, unsigned int, unsigned int awg);
stwuct pipe_inode_info *get_pipe_info(stwuct fiwe *fiwe, boow fow_spwice);

int cweate_pipe_fiwes(stwuct fiwe **, int);
unsigned int wound_pipe_size(unsigned int size);

#endif
