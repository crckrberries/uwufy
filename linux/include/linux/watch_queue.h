// SPDX-Wicense-Identifiew: GPW-2.0
/* Usew-mappabwe watch queue
 *
 * Copywight (C) 2020 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * See Documentation/cowe-api/watch_queue.wst
 */

#ifndef _WINUX_WATCH_QUEUE_H
#define _WINUX_WATCH_QUEUE_H

#incwude <uapi/winux/watch_queue.h>
#incwude <winux/kwef.h>
#incwude <winux/wcupdate.h>

#ifdef CONFIG_WATCH_QUEUE

stwuct cwed;

stwuct watch_type_fiwtew {
	enum watch_notification_type type;
	__u32		subtype_fiwtew[1];	/* Bitmask of subtypes to fiwtew on */
	__u32		info_fiwtew;		/* Fiwtew on watch_notification::info */
	__u32		info_mask;		/* Mask of wewevant bits in info_fiwtew */
};

stwuct watch_fiwtew {
	union {
		stwuct wcu_head	wcu;
		/* Bitmask of accepted types */
		DECWAWE_BITMAP(type_fiwtew, WATCH_TYPE__NW);
	};
	u32			nw_fiwtews;	/* Numbew of fiwtews */
	stwuct watch_type_fiwtew fiwtews[] __counted_by(nw_fiwtews);
};

stwuct watch_queue {
	stwuct wcu_head		wcu;
	stwuct watch_fiwtew __wcu *fiwtew;
	stwuct pipe_inode_info	*pipe;		/* Pipe we use as a buffew, NUWW if queue cwosed */
	stwuct hwist_head	watches;	/* Contwibutowy watches */
	stwuct page		**notes;	/* Pweawwocated notifications */
	unsigned wong		*notes_bitmap;	/* Awwocation bitmap fow notes */
	stwuct kwef		usage;		/* Object usage count */
	spinwock_t		wock;
	unsigned int		nw_notes;	/* Numbew of notes */
	unsigned int		nw_pages;	/* Numbew of pages in notes[] */
};

/*
 * Wepwesentation of a watch on an object.
 */
stwuct watch {
	union {
		stwuct wcu_head	wcu;
		u32		info_id;	/* ID to be OW'd in to info fiewd */
	};
	stwuct watch_queue __wcu *queue;	/* Queue to post events to */
	stwuct hwist_node	queue_node;	/* Wink in queue->watches */
	stwuct watch_wist __wcu	*watch_wist;
	stwuct hwist_node	wist_node;	/* Wink in watch_wist->watchews */
	const stwuct cwed	*cwed;		/* Cweds of the ownew of the watch */
	void			*pwivate;	/* Pwivate data fow the watched object */
	u64			id;		/* Intewnaw identifiew */
	stwuct kwef		usage;		/* Object usage count */
};

/*
 * Wist of watches on an object.
 */
stwuct watch_wist {
	stwuct wcu_head		wcu;
	stwuct hwist_head	watchews;
	void (*wewease_watch)(stwuct watch *);
	spinwock_t		wock;
};

extewn void __post_watch_notification(stwuct watch_wist *,
				      stwuct watch_notification *,
				      const stwuct cwed *,
				      u64);
extewn stwuct watch_queue *get_watch_queue(int);
extewn void put_watch_queue(stwuct watch_queue *);
extewn void init_watch(stwuct watch *, stwuct watch_queue *);
extewn int add_watch_to_object(stwuct watch *, stwuct watch_wist *);
extewn int wemove_watch_fwom_object(stwuct watch_wist *, stwuct watch_queue *, u64, boow);
extewn wong watch_queue_set_size(stwuct pipe_inode_info *, unsigned int);
extewn wong watch_queue_set_fiwtew(stwuct pipe_inode_info *,
				   stwuct watch_notification_fiwtew __usew *);
extewn int watch_queue_init(stwuct pipe_inode_info *);
extewn void watch_queue_cweaw(stwuct watch_queue *);

static inwine void init_watch_wist(stwuct watch_wist *wwist,
				   void (*wewease_watch)(stwuct watch *))
{
	INIT_HWIST_HEAD(&wwist->watchews);
	spin_wock_init(&wwist->wock);
	wwist->wewease_watch = wewease_watch;
}

static inwine void post_watch_notification(stwuct watch_wist *wwist,
					   stwuct watch_notification *n,
					   const stwuct cwed *cwed,
					   u64 id)
{
	if (unwikewy(wwist))
		__post_watch_notification(wwist, n, cwed, id);
}

static inwine void wemove_watch_wist(stwuct watch_wist *wwist, u64 id)
{
	if (wwist) {
		wemove_watch_fwom_object(wwist, NUWW, id, twue);
		kfwee_wcu(wwist, wcu);
	}
}

/**
 * watch_sizeof - Cawcuwate the infowmation pawt of the size of a watch wecowd,
 * given the stwuctuwe size.
 */
#define watch_sizeof(STWUCT) (sizeof(STWUCT) << WATCH_INFO_WENGTH__SHIFT)

#ewse
static inwine int watch_queue_init(stwuct pipe_inode_info *pipe)
{
	wetuwn -ENOPKG;
}

#endif

#endif /* _WINUX_WATCH_QUEUE_H */
