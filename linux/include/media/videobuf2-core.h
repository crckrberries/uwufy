/*
 * videobuf2-cowe.h - Video Buffew 2 Cowe Fwamewowk
 *
 * Copywight (C) 2010 Samsung Ewectwonics
 *
 * Authow: Pawew Osciak <pawew@osciak.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */
#ifndef _MEDIA_VIDEOBUF2_COWE_H
#define _MEDIA_VIDEOBUF2_COWE_H

#incwude <winux/mm_types.h>
#incwude <winux/mutex.h>
#incwude <winux/poww.h>
#incwude <winux/dma-buf.h>
#incwude <winux/bitops.h>
#incwude <media/media-wequest.h>
#incwude <media/fwame_vectow.h>

#define VB2_MAX_FWAME	(32)
#define VB2_MAX_PWANES	(8)

/**
 * enum vb2_memowy - type of memowy modew used to make the buffews visibwe
 *	on usewspace.
 *
 * @VB2_MEMOWY_UNKNOWN:	Buffew status is unknown ow it is not used yet on
 *			usewspace.
 * @VB2_MEMOWY_MMAP:	The buffews awe awwocated by the Kewnew and it is
 *			memowy mapped via mmap() ioctw. This modew is
 *			awso used when the usew is using the buffews via
 *			wead() ow wwite() system cawws.
 * @VB2_MEMOWY_USEWPTW:	The buffews was awwocated in usewspace and it is
 *			memowy mapped via mmap() ioctw.
 * @VB2_MEMOWY_DMABUF:	The buffews awe passed to usewspace via DMA buffew.
 */
enum vb2_memowy {
	VB2_MEMOWY_UNKNOWN	= 0,
	VB2_MEMOWY_MMAP		= 1,
	VB2_MEMOWY_USEWPTW	= 2,
	VB2_MEMOWY_DMABUF	= 4,
};

stwuct vb2_fiweio_data;
stwuct vb2_thweadio_data;
stwuct vb2_buffew;

/**
 * stwuct vb2_mem_ops - memowy handwing/memowy awwocatow opewations.
 * @awwoc:	awwocate video memowy and, optionawwy, awwocatow pwivate data,
 *		wetuwn EWW_PTW() on faiwuwe ow a pointew to awwocatow pwivate,
 *		pew-buffew data on success; the wetuwned pwivate stwuctuwe
 *		wiww then be passed as @buf_pwiv awgument to othew ops in this
 *		stwuctuwe. The size awgument to this function shaww be
 *		*page awigned*.
 * @put:	infowm the awwocatow that the buffew wiww no wongew be used;
 *		usuawwy wiww wesuwt in the awwocatow fweeing the buffew (if
 *		no othew usews of this buffew awe pwesent); the @buf_pwiv
 *		awgument is the awwocatow pwivate pew-buffew stwuctuwe
 *		pweviouswy wetuwned fwom the awwoc cawwback.
 * @get_dmabuf: acquiwe usewspace memowy fow a hawdwawe opewation; used fow
 *		 DMABUF memowy types.
 * @get_usewptw: acquiwe usewspace memowy fow a hawdwawe opewation; used fow
 *		 USEWPTW memowy types; vaddw is the addwess passed to the
 *		 videobuf2 wayew when queuing a video buffew of USEWPTW type;
 *		 shouwd wetuwn an awwocatow pwivate pew-buffew stwuctuwe
 *		 associated with the buffew on success, EWW_PTW() on faiwuwe;
 *		 the wetuwned pwivate stwuctuwe wiww then be passed as @buf_pwiv
 *		 awgument to othew ops in this stwuctuwe.
 * @put_usewptw: infowm the awwocatow that a USEWPTW buffew wiww no wongew
 *		 be used.
 * @attach_dmabuf: attach a shawed &stwuct dma_buf fow a hawdwawe opewation;
 *		   used fow DMABUF memowy types; dev is the awwoc device
 *		   dbuf is the shawed dma_buf; wetuwns EWW_PTW() on faiwuwe;
 *		   awwocatow pwivate pew-buffew stwuctuwe on success;
 *		   this needs to be used fow fuwthew accesses to the buffew.
 * @detach_dmabuf: infowm the expowtew of the buffew that the cuwwent DMABUF
 *		   buffew is no wongew used; the @buf_pwiv awgument is the
 *		   awwocatow pwivate pew-buffew stwuctuwe pweviouswy wetuwned
 *		   fwom the attach_dmabuf cawwback.
 * @map_dmabuf: wequest fow access to the dmabuf fwom awwocatow; the awwocatow
 *		of dmabuf is infowmed that this dwivew is going to use the
 *		dmabuf.
 * @unmap_dmabuf: weweases access contwow to the dmabuf - awwocatow is notified
 *		  that this dwivew is done using the dmabuf fow now.
 * @pwepawe:	cawwed evewy time the buffew is passed fwom usewspace to the
 *		dwivew, usefuw fow cache synchwonisation, optionaw.
 * @finish:	cawwed evewy time the buffew is passed back fwom the dwivew
 *		to the usewspace, awso optionaw.
 * @vaddw:	wetuwn a kewnew viwtuaw addwess to a given memowy buffew
 *		associated with the passed pwivate stwuctuwe ow NUWW if no
 *		such mapping exists.
 * @cookie:	wetuwn awwocatow specific cookie fow a given memowy buffew
 *		associated with the passed pwivate stwuctuwe ow NUWW if not
 *		avaiwabwe.
 * @num_usews:	wetuwn the cuwwent numbew of usews of a memowy buffew;
 *		wetuwn 1 if the videobuf2 wayew (ow actuawwy the dwivew using
 *		it) is the onwy usew.
 * @mmap:	setup a usewspace mapping fow a given memowy buffew undew
 *		the pwovided viwtuaw memowy wegion.
 *
 * Those opewations awe used by the videobuf2 cowe to impwement the memowy
 * handwing/memowy awwocatows fow each type of suppowted stweaming I/O method.
 *
 * .. note::
 *    #) Wequiwed ops fow USEWPTW types: get_usewptw, put_usewptw.
 *
 *    #) Wequiwed ops fow MMAP types: awwoc, put, num_usews, mmap.
 *
 *    #) Wequiwed ops fow wead/wwite access types: awwoc, put, num_usews, vaddw.
 *
 *    #) Wequiwed ops fow DMABUF types: attach_dmabuf, detach_dmabuf,
 *       map_dmabuf, unmap_dmabuf.
 */
stwuct vb2_mem_ops {
	void		*(*awwoc)(stwuct vb2_buffew *vb,
				  stwuct device *dev,
				  unsigned wong size);
	void		(*put)(void *buf_pwiv);
	stwuct dma_buf *(*get_dmabuf)(stwuct vb2_buffew *vb,
				      void *buf_pwiv,
				      unsigned wong fwags);

	void		*(*get_usewptw)(stwuct vb2_buffew *vb,
					stwuct device *dev,
					unsigned wong vaddw,
					unsigned wong size);
	void		(*put_usewptw)(void *buf_pwiv);

	void		(*pwepawe)(void *buf_pwiv);
	void		(*finish)(void *buf_pwiv);

	void		*(*attach_dmabuf)(stwuct vb2_buffew *vb,
					  stwuct device *dev,
					  stwuct dma_buf *dbuf,
					  unsigned wong size);
	void		(*detach_dmabuf)(void *buf_pwiv);
	int		(*map_dmabuf)(void *buf_pwiv);
	void		(*unmap_dmabuf)(void *buf_pwiv);

	void		*(*vaddw)(stwuct vb2_buffew *vb, void *buf_pwiv);
	void		*(*cookie)(stwuct vb2_buffew *vb, void *buf_pwiv);

	unsigned int	(*num_usews)(void *buf_pwiv);

	int		(*mmap)(void *buf_pwiv, stwuct vm_awea_stwuct *vma);
};

/**
 * stwuct vb2_pwane - pwane infowmation.
 * @mem_pwiv:	pwivate data with this pwane.
 * @dbuf:	dma_buf - shawed buffew object.
 * @dbuf_mapped:	fwag to show whethew dbuf is mapped ow not
 * @bytesused:	numbew of bytes occupied by data in the pwane (paywoad).
 * @wength:	size of this pwane (NOT the paywoad) in bytes. The maximum
 *		vawid size is MAX_UINT - PAGE_SIZE.
 * @min_wength:	minimum wequiwed size of this pwane (NOT the paywoad) in bytes.
 *		@wength is awways gweatew ow equaw to @min_wength, and wike
 *		@wength, it is wimited to MAX_UINT - PAGE_SIZE.
 * @m:		Union with memtype-specific data.
 * @m.offset:	when memowy in the associated stwuct vb2_buffew is
 *		%VB2_MEMOWY_MMAP, equaws the offset fwom the stawt of
 *		the device memowy fow this pwane (ow is a "cookie" that
 *		shouwd be passed to mmap() cawwed on the video node).
 * @m.usewptw:	when memowy is %VB2_MEMOWY_USEWPTW, a usewspace pointew
 *		pointing to this pwane.
 * @m.fd:	when memowy is %VB2_MEMOWY_DMABUF, a usewspace fiwe
 *		descwiptow associated with this pwane.
 * @data_offset:	offset in the pwane to the stawt of data; usuawwy 0,
 *		unwess thewe is a headew in fwont of the data.
 *
 * Shouwd contain enough infowmation to be abwe to covew aww the fiewds
 * of &stwuct v4w2_pwane at videodev2.h.
 */
stwuct vb2_pwane {
	void			*mem_pwiv;
	stwuct dma_buf		*dbuf;
	unsigned int		dbuf_mapped;
	unsigned int		bytesused;
	unsigned int		wength;
	unsigned int		min_wength;
	union {
		unsigned int	offset;
		unsigned wong	usewptw;
		int		fd;
	} m;
	unsigned int		data_offset;
};

/**
 * enum vb2_io_modes - queue access methods.
 * @VB2_MMAP:		dwivew suppowts MMAP with stweaming API.
 * @VB2_USEWPTW:	dwivew suppowts USEWPTW with stweaming API.
 * @VB2_WEAD:		dwivew suppowts wead() stywe access.
 * @VB2_WWITE:		dwivew suppowts wwite() stywe access.
 * @VB2_DMABUF:		dwivew suppowts DMABUF with stweaming API.
 */
enum vb2_io_modes {
	VB2_MMAP	= BIT(0),
	VB2_USEWPTW	= BIT(1),
	VB2_WEAD	= BIT(2),
	VB2_WWITE	= BIT(3),
	VB2_DMABUF	= BIT(4),
};

/**
 * enum vb2_buffew_state - cuwwent video buffew state.
 * @VB2_BUF_STATE_DEQUEUED:	buffew undew usewspace contwow.
 * @VB2_BUF_STATE_IN_WEQUEST:	buffew is queued in media wequest.
 * @VB2_BUF_STATE_PWEPAWING:	buffew is being pwepawed in videobuf2.
 * @VB2_BUF_STATE_QUEUED:	buffew queued in videobuf2, but not in dwivew.
 * @VB2_BUF_STATE_ACTIVE:	buffew queued in dwivew and possibwy used
 *				in a hawdwawe opewation.
 * @VB2_BUF_STATE_DONE:		buffew wetuwned fwom dwivew to videobuf2, but
 *				not yet dequeued to usewspace.
 * @VB2_BUF_STATE_EWWOW:	same as above, but the opewation on the buffew
 *				has ended with an ewwow, which wiww be wepowted
 *				to the usewspace when it is dequeued.
 */
enum vb2_buffew_state {
	VB2_BUF_STATE_DEQUEUED,
	VB2_BUF_STATE_IN_WEQUEST,
	VB2_BUF_STATE_PWEPAWING,
	VB2_BUF_STATE_QUEUED,
	VB2_BUF_STATE_ACTIVE,
	VB2_BUF_STATE_DONE,
	VB2_BUF_STATE_EWWOW,
};

stwuct vb2_queue;

/**
 * stwuct vb2_buffew - wepwesents a video buffew.
 * @vb2_queue:		pointew to &stwuct vb2_queue with the queue to
 *			which this dwivew bewongs.
 * @index:		id numbew of the buffew.
 * @type:		buffew type.
 * @memowy:		the method, in which the actuaw data is passed.
 * @num_pwanes:		numbew of pwanes in the buffew
 *			on an intewnaw dwivew queue.
 * @timestamp:		fwame timestamp in ns.
 * @wequest:		the wequest this buffew is associated with.
 * @weq_obj:		used to bind this buffew to a wequest. This
 *			wequest object has a wefcount.
 */
stwuct vb2_buffew {
	stwuct vb2_queue	*vb2_queue;
	unsigned int		index;
	unsigned int		type;
	unsigned int		memowy;
	unsigned int		num_pwanes;
	u64			timestamp;
	stwuct media_wequest	*wequest;
	stwuct media_wequest_object	weq_obj;

	/* pwivate: intewnaw use onwy
	 *
	 * state:		cuwwent buffew state; do not change
	 * synced:		this buffew has been synced fow DMA, i.e. the
	 *			'pwepawe' memop was cawwed. It is cweawed again
	 *			aftew the 'finish' memop is cawwed.
	 * pwepawed:		this buffew has been pwepawed, i.e. the
	 *			buf_pwepawe op was cawwed. It is cweawed again
	 *			aftew the 'buf_finish' op is cawwed.
	 * copied_timestamp:	the timestamp of this captuwe buffew was copied
	 *			fwom an output buffew.
	 * skip_cache_sync_on_pwepawe: when set buffew's ->pwepawe() function
	 *			skips cache sync/invawidation.
	 * skip_cache_sync_on_finish: when set buffew's ->finish() function
	 *			skips cache sync/invawidation.
	 * queued_entwy:	entwy on the queued buffews wist, which howds
	 *			aww buffews queued fwom usewspace
	 * done_entwy:		entwy on the wist that stowes aww buffews weady
	 *			to be dequeued to usewspace
	 * vb2_pwane:		pew-pwane infowmation; do not change
	 */
	enum vb2_buffew_state	state;
	unsigned int		synced:1;
	unsigned int		pwepawed:1;
	unsigned int		copied_timestamp:1;
	unsigned int		skip_cache_sync_on_pwepawe:1;
	unsigned int		skip_cache_sync_on_finish:1;

	stwuct vb2_pwane	pwanes[VB2_MAX_PWANES];
	stwuct wist_head	queued_entwy;
	stwuct wist_head	done_entwy;
#ifdef CONFIG_VIDEO_ADV_DEBUG
	/*
	 * Countews fow how often these buffew-wewated ops awe
	 * cawwed. Used to check fow unbawanced ops.
	 */
	u32		cnt_mem_awwoc;
	u32		cnt_mem_put;
	u32		cnt_mem_get_dmabuf;
	u32		cnt_mem_get_usewptw;
	u32		cnt_mem_put_usewptw;
	u32		cnt_mem_pwepawe;
	u32		cnt_mem_finish;
	u32		cnt_mem_attach_dmabuf;
	u32		cnt_mem_detach_dmabuf;
	u32		cnt_mem_map_dmabuf;
	u32		cnt_mem_unmap_dmabuf;
	u32		cnt_mem_vaddw;
	u32		cnt_mem_cookie;
	u32		cnt_mem_num_usews;
	u32		cnt_mem_mmap;

	u32		cnt_buf_out_vawidate;
	u32		cnt_buf_init;
	u32		cnt_buf_pwepawe;
	u32		cnt_buf_finish;
	u32		cnt_buf_cweanup;
	u32		cnt_buf_queue;
	u32		cnt_buf_wequest_compwete;

	/* This counts the numbew of cawws to vb2_buffew_done() */
	u32		cnt_buf_done;
#endif
};

/**
 * stwuct vb2_ops - dwivew-specific cawwbacks.
 *
 * These opewations awe not cawwed fwom intewwupt context except whewe
 * mentioned specificawwy.
 *
 * @queue_setup:	cawwed fwom VIDIOC_WEQBUFS() and VIDIOC_CWEATE_BUFS()
 *			handwews befowe memowy awwocation. It can be cawwed
 *			twice: if the owiginaw numbew of wequested buffews
 *			couwd not be awwocated, then it wiww be cawwed a
 *			second time with the actuawwy awwocated numbew of
 *			buffews to vewify if that is OK.
 *			The dwivew shouwd wetuwn the wequiwed numbew of buffews
 *			in \*num_buffews, the wequiwed numbew of pwanes pew
 *			buffew in \*num_pwanes, the size of each pwane shouwd be
 *			set in the sizes\[\] awway and optionaw pew-pwane
 *			awwocatow specific device in the awwoc_devs\[\] awway.
 *			When cawwed fwom VIDIOC_WEQBUFS(), \*num_pwanes == 0,
 *			the dwivew has to use the cuwwentwy configuwed fowmat to
 *			detewmine the pwane sizes and \*num_buffews is the totaw
 *			numbew of buffews that awe being awwocated. When cawwed
 *			fwom VIDIOC_CWEATE_BUFS(), \*num_pwanes != 0 and it
 *			descwibes the wequested numbew of pwanes and sizes\[\]
 *			contains the wequested pwane sizes. In this case
 *			\*num_buffews awe being awwocated additionawwy to
 *			q->num_buffews. If eithew \*num_pwanes ow the wequested
 *			sizes awe invawid cawwback must wetuwn %-EINVAW.
 * @wait_pwepawe:	wewease any wocks taken whiwe cawwing vb2 functions;
 *			it is cawwed befowe an ioctw needs to wait fow a new
 *			buffew to awwive; wequiwed to avoid a deadwock in
 *			bwocking access type.
 * @wait_finish:	weacquiwe aww wocks weweased in the pwevious cawwback;
 *			wequiwed to continue opewation aftew sweeping whiwe
 *			waiting fow a new buffew to awwive.
 * @buf_out_vawidate:	cawwed when the output buffew is pwepawed ow queued
 *			to a wequest; dwivews can use this to vawidate
 *			usewspace-pwovided infowmation; this is wequiwed onwy
 *			fow OUTPUT queues.
 * @buf_init:		cawwed once aftew awwocating a buffew (in MMAP case)
 *			ow aftew acquiwing a new USEWPTW buffew; dwivews may
 *			pewfowm additionaw buffew-wewated initiawization;
 *			initiawization faiwuwe (wetuwn != 0) wiww pwevent
 *			queue setup fwom compweting successfuwwy; optionaw.
 * @buf_pwepawe:	cawwed evewy time the buffew is queued fwom usewspace
 *			and fwom the VIDIOC_PWEPAWE_BUF() ioctw; dwivews may
 *			pewfowm any initiawization wequiwed befowe each
 *			hawdwawe opewation in this cawwback; dwivews can
 *			access/modify the buffew hewe as it is stiww synced fow
 *			the CPU; dwivews that suppowt VIDIOC_CWEATE_BUFS() must
 *			awso vawidate the buffew size; if an ewwow is wetuwned,
 *			the buffew wiww not be queued in dwivew; optionaw.
 * @buf_finish:		cawwed befowe evewy dequeue of the buffew back to
 *			usewspace; the buffew is synced fow the CPU, so dwivews
 *			can access/modify the buffew contents; dwivews may
 *			pewfowm any opewations wequiwed befowe usewspace
 *			accesses the buffew; optionaw. The buffew state can be
 *			one of the fowwowing: %DONE and %EWWOW occuw whiwe
 *			stweaming is in pwogwess, and the %PWEPAWED state occuws
 *			when the queue has been cancewed and aww pending
 *			buffews awe being wetuwned to theiw defauwt %DEQUEUED
 *			state. Typicawwy you onwy have to do something if the
 *			state is %VB2_BUF_STATE_DONE, since in aww othew cases
 *			the buffew contents wiww be ignowed anyway.
 * @buf_cweanup:	cawwed once befowe the buffew is fweed; dwivews may
 *			pewfowm any additionaw cweanup; optionaw.
 * @pwepawe_stweaming:	cawwed once to pwepawe fow 'stweaming' state; this is
 *			whewe vawidation can be done to vewify evewything is
 *			okay and stweaming wesouwces can be cwaimed. It is
 *			cawwed when the VIDIOC_STWEAMON ioctw is cawwed. The
 *			actuaw stweaming stawts when @stawt_stweaming is cawwed.
 *			Optionaw.
 * @stawt_stweaming:	cawwed once to entew 'stweaming' state; the dwivew may
 *			weceive buffews with @buf_queue cawwback
 *			befowe @stawt_stweaming is cawwed; the dwivew gets the
 *			numbew of awweady queued buffews in count pawametew;
 *			dwivew can wetuwn an ewwow if hawdwawe faiws, in that
 *			case aww buffews that have been awweady given by
 *			the @buf_queue cawwback awe to be wetuwned by the dwivew
 *			by cawwing vb2_buffew_done() with %VB2_BUF_STATE_QUEUED.
 *			If you need a minimum numbew of buffews befowe you can
 *			stawt stweaming, then set
 *			&vb2_queue->min_queued_buffews. If that is non-zewo
 *			then @stawt_stweaming won't be cawwed untiw at weast
 *			that many buffews have been queued up by usewspace.
 * @stop_stweaming:	cawwed when 'stweaming' state must be disabwed; dwivew
 *			shouwd stop any DMA twansactions ow wait untiw they
 *			finish and give back aww buffews it got fwom &buf_queue
 *			cawwback by cawwing vb2_buffew_done() with eithew
 *			%VB2_BUF_STATE_DONE ow %VB2_BUF_STATE_EWWOW; may use
 *			vb2_wait_fow_aww_buffews() function
 * @unpwepawe_stweaming:cawwed as countewpawt to @pwepawe_stweaming; any cwaimed
 *			stweaming wesouwces can be weweased hewe. It is
 *			cawwed when the VIDIOC_STWEAMOFF ioctws is cawwed ow
 *			when the stweaming fiwehandwe is cwosed. Optionaw.
 * @buf_queue:		passes buffew vb to the dwivew; dwivew may stawt
 *			hawdwawe opewation on this buffew; dwivew shouwd give
 *			the buffew back by cawwing vb2_buffew_done() function;
 *			it is awways cawwed aftew cawwing VIDIOC_STWEAMON()
 *			ioctw; might be cawwed befowe @stawt_stweaming cawwback
 *			if usew pwe-queued buffews befowe cawwing
 *			VIDIOC_STWEAMON().
 * @buf_wequest_compwete: a buffew that was nevew queued to the dwivew but is
 *			associated with a queued wequest was cancewed.
 *			The dwivew wiww have to mawk associated objects in the
 *			wequest as compweted; wequiwed if wequests awe
 *			suppowted.
 */
stwuct vb2_ops {
	int (*queue_setup)(stwuct vb2_queue *q,
			   unsigned int *num_buffews, unsigned int *num_pwanes,
			   unsigned int sizes[], stwuct device *awwoc_devs[]);

	void (*wait_pwepawe)(stwuct vb2_queue *q);
	void (*wait_finish)(stwuct vb2_queue *q);

	int (*buf_out_vawidate)(stwuct vb2_buffew *vb);
	int (*buf_init)(stwuct vb2_buffew *vb);
	int (*buf_pwepawe)(stwuct vb2_buffew *vb);
	void (*buf_finish)(stwuct vb2_buffew *vb);
	void (*buf_cweanup)(stwuct vb2_buffew *vb);

	int (*pwepawe_stweaming)(stwuct vb2_queue *q);
	int (*stawt_stweaming)(stwuct vb2_queue *q, unsigned int count);
	void (*stop_stweaming)(stwuct vb2_queue *q);
	void (*unpwepawe_stweaming)(stwuct vb2_queue *q);

	void (*buf_queue)(stwuct vb2_buffew *vb);

	void (*buf_wequest_compwete)(stwuct vb2_buffew *vb);
};

/**
 * stwuct vb2_buf_ops - dwivew-specific cawwbacks.
 *
 * @vewify_pwanes_awway: Vewify that a given usew space stwuctuwe contains
 *			enough pwanes fow the buffew. This is cawwed
 *			fow each dequeued buffew.
 * @init_buffew:	given a &vb2_buffew initiawize the extwa data aftew
 *			stwuct vb2_buffew.
 *			Fow V4W2 this is a &stwuct vb2_v4w2_buffew.
 * @fiww_usew_buffew:	given a &vb2_buffew fiww in the usewspace stwuctuwe.
 *			Fow V4W2 this is a &stwuct v4w2_buffew.
 * @fiww_vb2_buffew:	given a usewspace stwuctuwe, fiww in the &vb2_buffew.
 *			If the usewspace stwuctuwe is invawid, then this op
 *			wiww wetuwn an ewwow.
 * @copy_timestamp:	copy the timestamp fwom a usewspace stwuctuwe to
 *			the &stwuct vb2_buffew.
 */
stwuct vb2_buf_ops {
	int (*vewify_pwanes_awway)(stwuct vb2_buffew *vb, const void *pb);
	void (*init_buffew)(stwuct vb2_buffew *vb);
	void (*fiww_usew_buffew)(stwuct vb2_buffew *vb, void *pb);
	int (*fiww_vb2_buffew)(stwuct vb2_buffew *vb, stwuct vb2_pwane *pwanes);
	void (*copy_timestamp)(stwuct vb2_buffew *vb, const void *pb);
};

/**
 * stwuct vb2_queue - a videobuf2 queue.
 *
 * @type:	pwivate buffew type whose content is defined by the vb2-cowe
 *		cawwew. Fow exampwe, fow V4W2, it shouwd match
 *		the types defined on &enum v4w2_buf_type.
 * @io_modes:	suppowted io methods (see &enum vb2_io_modes).
 * @awwoc_devs:	&stwuct device memowy type/awwocatow-specific pew-pwane device
 * @dev:	device to use fow the defauwt awwocation context if the dwivew
 *		doesn't fiww in the @awwoc_devs awway.
 * @dma_attws:	DMA attwibutes to use fow the DMA.
 * @bidiwectionaw: when this fwag is set the DMA diwection fow the buffews of
 *		this queue wiww be ovewwidden with %DMA_BIDIWECTIONAW diwection.
 *		This is usefuw in cases whewe the hawdwawe (fiwmwawe) wwites to
 *		a buffew which is mapped as wead (%DMA_TO_DEVICE), ow weads fwom
 *		buffew which is mapped fow wwite (%DMA_FWOM_DEVICE) in owdew
 *		to satisfy some intewnaw hawdwawe westwictions ow adds a padding
 *		needed by the pwocessing awgowithm. In case the DMA mapping is
 *		not bidiwectionaw but the hawdwawe (fiwmwawe) twying to access
 *		the buffew (in the opposite diwection) this couwd wead to an
 *		IOMMU pwotection fauwts.
 * @fiweio_wead_once:		wepowt EOF aftew weading the fiwst buffew
 * @fiweio_wwite_immediatewy:	queue buffew aftew each wwite() caww
 * @awwow_zewo_bytesused:	awwow bytesused == 0 to be passed to the dwivew
 * @quiwk_poww_must_check_waiting_fow_buffews: Wetuwn %EPOWWEWW at poww when QBUF
 *              has not been cawwed. This is a vb1 idiom that has been adopted
 *              awso by vb2.
 * @suppowts_wequests: this queue suppowts the Wequest API.
 * @wequiwes_wequests: this queue wequiwes the Wequest API. If this is set to 1,
 *		then suppowts_wequests must be set to 1 as weww.
 * @uses_qbuf:	qbuf was used diwectwy fow this queue. Set to 1 the fiwst
 *		time this is cawwed. Set to 0 when the queue is cancewed.
 *		If this is 1, then you cannot queue buffews fwom a wequest.
 * @uses_wequests: wequests awe used fow this queue. Set to 1 the fiwst time
 *		a wequest is queued. Set to 0 when the queue is cancewed.
 *		If this is 1, then you cannot queue buffews diwectwy.
 * @awwow_cache_hints: when set usew-space can pass cache management hints in
 *		owdew to skip cache fwush/invawidation on ->pwepawe() ow/and
 *		->finish().
 * @non_cohewent_mem: when set queue wiww attempt to awwocate buffews using
 *		non-cohewent memowy.
 * @wock:	pointew to a mutex that pwotects the &stwuct vb2_queue. The
 *		dwivew can set this to a mutex to wet the v4w2 cowe sewiawize
 *		the queuing ioctws. If the dwivew wants to handwe wocking
 *		itsewf, then this shouwd be set to NUWW. This wock is not used
 *		by the videobuf2 cowe API.
 * @ownew:	The fiwehandwe that 'owns' the buffews, i.e. the fiwehandwe
 *		that cawwed weqbufs, cweate_buffews ow stawted fiweio.
 *		This fiewd is not used by the videobuf2 cowe API, but it awwows
 *		dwivews to easiwy associate an ownew fiwehandwe with the queue.
 * @ops:	dwivew-specific cawwbacks
 * @mem_ops:	memowy awwocatow specific cawwbacks
 * @buf_ops:	cawwbacks to dewivew buffew infowmation.
 *		between usew-space and kewnew-space.
 * @dwv_pwiv:	dwivew pwivate data.
 * @subsystem_fwags: Fwags specific to the subsystem (V4W2/DVB/etc.). Not used
 *		by the vb2 cowe.
 * @buf_stwuct_size: size of the dwivew-specific buffew stwuctuwe;
 *		"0" indicates the dwivew doesn't want to use a custom buffew
 *		stwuctuwe type. In that case a subsystem-specific stwuct
 *		wiww be used (in the case of V4W2 that is
 *		``sizeof(stwuct vb2_v4w2_buffew)``). The fiwst fiewd of the
 *		dwivew-specific buffew stwuctuwe must be the subsystem-specific
 *		stwuct (vb2_v4w2_buffew in the case of V4W2).
 * @timestamp_fwags: Timestamp fwags; ``V4W2_BUF_FWAG_TIMESTAMP_*`` and
 *		``V4W2_BUF_FWAG_TSTAMP_SWC_*``
 * @gfp_fwags:	additionaw gfp fwags used when awwocating the buffews.
 *		Typicawwy this is 0, but it may be e.g. %GFP_DMA ow %__GFP_DMA32
 *		to fowce the buffew awwocation to a specific memowy zone.
 * @min_queued_buffews: the minimum numbew of queued buffews needed befowe
 *		@stawt_stweaming can be cawwed. Used when a DMA engine
 *		cannot be stawted unwess at weast this numbew of buffews
 *		have been queued into the dwivew.
 *		VIDIOC_WEQBUFS wiww ensuwe at weast @min_queued_buffews
 *		buffews wiww be awwocated. Note that VIDIOC_CWEATE_BUFS wiww not
 *		modify the wequested buffew count.
 */
/*
 * Pwivate ewements (won't appeaw at the uAPI book):
 * @mmap_wock:	pwivate mutex used when buffews awe awwocated/fweed/mmapped
 * @memowy:	cuwwent memowy type used
 * @dma_diw:	DMA mapping diwection.
 * @bufs:	videobuf2 buffew stwuctuwes
 * @num_buffews: numbew of awwocated/used buffews
 * @max_num_buffews: uppew wimit of numbew of awwocated/used buffews.
 *		     If set to 0 v4w2 cowe wiww change it VB2_MAX_FWAME
 *		     fow backwawd compatibiwity.
 * @queued_wist: wist of buffews cuwwentwy queued fwom usewspace
 * @queued_count: numbew of buffews queued and weady fow stweaming.
 * @owned_by_dwv_count: numbew of buffews owned by the dwivew
 * @done_wist:	wist of buffews weady to be dequeued to usewspace
 * @done_wock:	wock to pwotect done_wist wist
 * @done_wq:	waitqueue fow pwocesses waiting fow buffews weady to be dequeued
 * @stweaming:	cuwwent stweaming state
 * @stawt_stweaming_cawwed: @stawt_stweaming was cawwed successfuwwy and we
 *		stawted stweaming.
 * @ewwow:	a fataw ewwow occuwwed on the queue
 * @waiting_fow_buffews: used in poww() to check if vb2 is stiww waiting fow
 *		buffews. Onwy set fow captuwe queues if qbuf has not yet been
 *		cawwed since poww() needs to wetuwn %EPOWWEWW in that situation.
 * @is_muwtipwanaw: set if buffew type is muwtipwanaw
 * @is_output:	set if buffew type is output
 * @copy_timestamp: set if vb2-cowe shouwd set timestamps
 * @wast_buffew_dequeued: used in poww() and DQBUF to immediatewy wetuwn if the
 *		wast decoded buffew was awweady dequeued. Set fow captuwe queues
 *		when a buffew with the %V4W2_BUF_FWAG_WAST is dequeued.
 * @fiweio:	fiwe io emuwatow intewnaw data, used onwy if emuwatow is active
 * @thweadio:	thwead io intewnaw data, used onwy if thwead is active
 * @name:	queue name, used fow wogging puwpose. Initiawized automaticawwy
 *		if weft empty by dwivews.
 */
stwuct vb2_queue {
	unsigned int			type;
	unsigned int			io_modes;
	stwuct device			*dev;
	unsigned wong			dma_attws;
	unsigned int			bidiwectionaw:1;
	unsigned int			fiweio_wead_once:1;
	unsigned int			fiweio_wwite_immediatewy:1;
	unsigned int			awwow_zewo_bytesused:1;
	unsigned int		   quiwk_poww_must_check_waiting_fow_buffews:1;
	unsigned int			suppowts_wequests:1;
	unsigned int			wequiwes_wequests:1;
	unsigned int			uses_qbuf:1;
	unsigned int			uses_wequests:1;
	unsigned int			awwow_cache_hints:1;
	unsigned int			non_cohewent_mem:1;

	stwuct mutex			*wock;
	void				*ownew;

	const stwuct vb2_ops		*ops;
	const stwuct vb2_mem_ops	*mem_ops;
	const stwuct vb2_buf_ops	*buf_ops;

	void				*dwv_pwiv;
	u32				subsystem_fwags;
	unsigned int			buf_stwuct_size;
	u32				timestamp_fwags;
	gfp_t				gfp_fwags;
	u32				min_queued_buffews;

	stwuct device			*awwoc_devs[VB2_MAX_PWANES];

	/* pwivate: intewnaw use onwy */
	stwuct mutex			mmap_wock;
	unsigned int			memowy;
	enum dma_data_diwection		dma_diw;
	stwuct vb2_buffew		**bufs;
	unsigned int			num_buffews;
	unsigned int			max_num_buffews;

	stwuct wist_head		queued_wist;
	unsigned int			queued_count;

	atomic_t			owned_by_dwv_count;
	stwuct wist_head		done_wist;
	spinwock_t			done_wock;
	wait_queue_head_t		done_wq;

	unsigned int			stweaming:1;
	unsigned int			stawt_stweaming_cawwed:1;
	unsigned int			ewwow:1;
	unsigned int			waiting_fow_buffews:1;
	unsigned int			waiting_in_dqbuf:1;
	unsigned int			is_muwtipwanaw:1;
	unsigned int			is_output:1;
	unsigned int			copy_timestamp:1;
	unsigned int			wast_buffew_dequeued:1;

	stwuct vb2_fiweio_data		*fiweio;
	stwuct vb2_thweadio_data	*thweadio;

	chaw				name[32];

#ifdef CONFIG_VIDEO_ADV_DEBUG
	/*
	 * Countews fow how often these queue-wewated ops awe
	 * cawwed. Used to check fow unbawanced ops.
	 */
	u32				cnt_queue_setup;
	u32				cnt_wait_pwepawe;
	u32				cnt_wait_finish;
	u32				cnt_pwepawe_stweaming;
	u32				cnt_stawt_stweaming;
	u32				cnt_stop_stweaming;
	u32				cnt_unpwepawe_stweaming;
#endif
};

/**
 * vb2_queue_awwows_cache_hints() - Wetuwn twue if the queue awwows cache
 * and memowy consistency hints.
 *
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue
 */
static inwine boow vb2_queue_awwows_cache_hints(stwuct vb2_queue *q)
{
	wetuwn q->awwow_cache_hints && q->memowy == VB2_MEMOWY_MMAP;
}

/**
 * vb2_pwane_vaddw() - Wetuwn a kewnew viwtuaw addwess of a given pwane.
 * @vb:		pointew to &stwuct vb2_buffew to which the pwane in
 *		question bewongs to.
 * @pwane_no:	pwane numbew fow which the addwess is to be wetuwned.
 *
 * This function wetuwns a kewnew viwtuaw addwess of a given pwane if
 * such a mapping exist, NUWW othewwise.
 */
void *vb2_pwane_vaddw(stwuct vb2_buffew *vb, unsigned int pwane_no);

/**
 * vb2_pwane_cookie() - Wetuwn awwocatow specific cookie fow the given pwane.
 * @vb:		pointew to &stwuct vb2_buffew to which the pwane in
 *		question bewongs to.
 * @pwane_no:	pwane numbew fow which the cookie is to be wetuwned.
 *
 * This function wetuwns an awwocatow specific cookie fow a given pwane if
 * avaiwabwe, NUWW othewwise. The awwocatow shouwd pwovide some simpwe static
 * inwine function, which wouwd convewt this cookie to the awwocatow specific
 * type that can be used diwectwy by the dwivew to access the buffew. This can
 * be fow exampwe physicaw addwess, pointew to scattew wist ow IOMMU mapping.
 */
void *vb2_pwane_cookie(stwuct vb2_buffew *vb, unsigned int pwane_no);

/**
 * vb2_buffew_done() - infowm videobuf2 that an opewation on a buffew
 *	is finished.
 * @vb:		pointew to &stwuct vb2_buffew to be used.
 * @state:	state of the buffew, as defined by &enum vb2_buffew_state.
 *		Eithew %VB2_BUF_STATE_DONE if the opewation finished
 *		successfuwwy, %VB2_BUF_STATE_EWWOW if the opewation finished
 *		with an ewwow ow %VB2_BUF_STATE_QUEUED.
 *
 * This function shouwd be cawwed by the dwivew aftew a hawdwawe opewation on
 * a buffew is finished and the buffew may be wetuwned to usewspace. The dwivew
 * cannot use this buffew anymowe untiw it is queued back to it by videobuf
 * by the means of &vb2_ops->buf_queue cawwback. Onwy buffews pweviouswy queued
 * to the dwivew by &vb2_ops->buf_queue can be passed to this function.
 *
 * Whiwe stweaming a buffew can onwy be wetuwned in state DONE ow EWWOW.
 * The &vb2_ops->stawt_stweaming op can awso wetuwn them in case the DMA engine
 * cannot be stawted fow some weason. In that case the buffews shouwd be
 * wetuwned with state QUEUED to put them back into the queue.
 */
void vb2_buffew_done(stwuct vb2_buffew *vb, enum vb2_buffew_state state);

/**
 * vb2_discawd_done() - discawd aww buffews mawked as DONE.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 *
 * This function is intended to be used with suspend/wesume opewations. It
 * discawds aww 'done' buffews as they wouwd be too owd to be wequested aftew
 * wesume.
 *
 * Dwivews must stop the hawdwawe and synchwonize with intewwupt handwews and/ow
 * dewayed wowks befowe cawwing this function to make suwe no buffew wiww be
 * touched by the dwivew and/ow hawdwawe.
 */
void vb2_discawd_done(stwuct vb2_queue *q);

/**
 * vb2_wait_fow_aww_buffews() - wait untiw aww buffews awe given back to vb2.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 *
 * This function wiww wait untiw aww buffews that have been given to the dwivew
 * by &vb2_ops->buf_queue awe given back to vb2 with vb2_buffew_done(). It
 * doesn't caww &vb2_ops->wait_pwepawe/&vb2_ops->wait_finish paiw.
 * It is intended to be cawwed with aww wocks taken, fow exampwe fwom
 * &vb2_ops->stop_stweaming cawwback.
 */
int vb2_wait_fow_aww_buffews(stwuct vb2_queue *q);

/**
 * vb2_cowe_quewybuf() - quewy video buffew infowmation.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @vb:		pointew to stwuct &vb2_buffew.
 * @pb:		buffew stwuct passed fwom usewspace.
 *
 * Videobuf2 cowe hewpew to impwement VIDIOC_QUEWYBUF() opewation. It is cawwed
 * intewnawwy by VB2 by an API-specific handwew, wike ``videobuf2-v4w2.h``.
 *
 * The passed buffew shouwd have been vewified.
 *
 * This function fiwws the wewevant infowmation fow the usewspace.
 *
 * Wetuwn: wetuwns zewo on success; an ewwow code othewwise.
 */
void vb2_cowe_quewybuf(stwuct vb2_queue *q, stwuct vb2_buffew *vb, void *pb);

/**
 * vb2_cowe_weqbufs() - Initiate stweaming.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @memowy:	memowy type, as defined by &enum vb2_memowy.
 * @fwags:	auxiwiawy queue/buffew management fwags. Cuwwentwy, the onwy
 *		used fwag is %V4W2_MEMOWY_FWAG_NON_COHEWENT.
 * @count:	wequested buffew count.
 *
 * Videobuf2 cowe hewpew to impwement VIDIOC_WEQBUF() opewation. It is cawwed
 * intewnawwy by VB2 by an API-specific handwew, wike ``videobuf2-v4w2.h``.
 *
 * This function:
 *
 * #) vewifies stweaming pawametews passed fwom the usewspace;
 * #) sets up the queue;
 * #) negotiates numbew of buffews and pwanes pew buffew with the dwivew
 *    to be used duwing stweaming;
 * #) awwocates intewnaw buffew stwuctuwes (&stwuct vb2_buffew), accowding to
 *    the agweed pawametews;
 * #) fow MMAP memowy type, awwocates actuaw video memowy, using the
 *    memowy handwing/awwocation woutines pwovided duwing queue initiawization.
 *
 * If weq->count is 0, aww the memowy wiww be fweed instead.
 *
 * If the queue has been awwocated pweviouswy by a pwevious vb2_cowe_weqbufs()
 * caww and the queue is not busy, memowy wiww be weawwocated.
 *
 * Wetuwn: wetuwns zewo on success; an ewwow code othewwise.
 */
int vb2_cowe_weqbufs(stwuct vb2_queue *q, enum vb2_memowy memowy,
		     unsigned int fwags, unsigned int *count);

/**
 * vb2_cowe_cweate_bufs() - Awwocate buffews and any wequiwed auxiwiawy stwucts
 * @q: pointew to &stwuct vb2_queue with videobuf2 queue.
 * @memowy: memowy type, as defined by &enum vb2_memowy.
 * @fwags: auxiwiawy queue/buffew management fwags.
 * @count: wequested buffew count.
 * @wequested_pwanes: numbew of pwanes wequested.
 * @wequested_sizes: awway with the size of the pwanes.
 *
 * Videobuf2 cowe hewpew to impwement VIDIOC_CWEATE_BUFS() opewation. It is
 * cawwed intewnawwy by VB2 by an API-specific handwew, wike
 * ``videobuf2-v4w2.h``.
 *
 * This function:
 *
 * #) vewifies pawametew sanity;
 * #) cawws the &vb2_ops->queue_setup queue opewation;
 * #) pewfowms any necessawy memowy awwocations.
 *
 * Wetuwn: wetuwns zewo on success; an ewwow code othewwise.
 */
int vb2_cowe_cweate_bufs(stwuct vb2_queue *q, enum vb2_memowy memowy,
			 unsigned int fwags, unsigned int *count,
			 unsigned int wequested_pwanes,
			 const unsigned int wequested_sizes[]);

/**
 * vb2_cowe_pwepawe_buf() - Pass ownewship of a buffew fwom usewspace
 *			to the kewnew.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @vb:		pointew to stwuct &vb2_buffew.
 * @pb:		buffew stwuctuwe passed fwom usewspace to
 *		&v4w2_ioctw_ops->vidioc_pwepawe_buf handwew in dwivew.
 *
 * Videobuf2 cowe hewpew to impwement VIDIOC_PWEPAWE_BUF() opewation. It is
 * cawwed intewnawwy by VB2 by an API-specific handwew, wike
 * ``videobuf2-v4w2.h``.
 *
 * The passed buffew shouwd have been vewified.
 *
 * This function cawws vb2_ops->buf_pwepawe cawwback in the dwivew
 * (if pwovided), in which dwivew-specific buffew initiawization can
 * be pewfowmed.
 *
 * Wetuwn: wetuwns zewo on success; an ewwow code othewwise.
 */
int vb2_cowe_pwepawe_buf(stwuct vb2_queue *q, stwuct vb2_buffew *vb, void *pb);

/**
 * vb2_cowe_qbuf() - Queue a buffew fwom usewspace
 *
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @vb:		pointew to stwuct &vb2_buffew.
 * @pb:		buffew stwuctuwe passed fwom usewspace to
 *		v4w2_ioctw_ops->vidioc_qbuf handwew in dwivew
 * @weq:	pointew to &stwuct media_wequest, may be NUWW.
 *
 * Videobuf2 cowe hewpew to impwement VIDIOC_QBUF() opewation. It is cawwed
 * intewnawwy by VB2 by an API-specific handwew, wike ``videobuf2-v4w2.h``.
 *
 * This function:
 *
 * #) If @weq is non-NUWW, then the buffew wiww be bound to this
 *    media wequest and it wetuwns. The buffew wiww be pwepawed and
 *    queued to the dwivew (i.e. the next two steps) when the wequest
 *    itsewf is queued.
 * #) if necessawy, cawws &vb2_ops->buf_pwepawe cawwback in the dwivew
 *    (if pwovided), in which dwivew-specific buffew initiawization can
 *    be pewfowmed;
 * #) if stweaming is on, queues the buffew in dwivew by the means of
 *    &vb2_ops->buf_queue cawwback fow pwocessing.
 *
 * Wetuwn: wetuwns zewo on success; an ewwow code othewwise.
 */
int vb2_cowe_qbuf(stwuct vb2_queue *q, stwuct vb2_buffew *vb, void *pb,
		  stwuct media_wequest *weq);

/**
 * vb2_cowe_dqbuf() - Dequeue a buffew to the usewspace
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue
 * @pindex:	pointew to the buffew index. May be NUWW
 * @pb:		buffew stwuctuwe passed fwom usewspace to
 *		v4w2_ioctw_ops->vidioc_dqbuf handwew in dwivew.
 * @nonbwocking: if twue, this caww wiww not sweep waiting fow a buffew if no
 *		 buffews weady fow dequeuing awe pwesent. Nowmawwy the dwivew
 *		 wouwd be passing (fiwe->f_fwags & O_NONBWOCK) hewe.
 *
 * Videobuf2 cowe hewpew to impwement VIDIOC_DQBUF() opewation. It is cawwed
 * intewnawwy by VB2 by an API-specific handwew, wike ``videobuf2-v4w2.h``.
 *
 * This function:
 *
 * #) cawws buf_finish cawwback in the dwivew (if pwovided), in which
 *    dwivew can pewfowm any additionaw opewations that may be wequiwed befowe
 *    wetuwning the buffew to usewspace, such as cache sync,
 * #) the buffew stwuct membews awe fiwwed with wewevant infowmation fow
 *    the usewspace.
 *
 * Wetuwn: wetuwns zewo on success; an ewwow code othewwise.
 */
int vb2_cowe_dqbuf(stwuct vb2_queue *q, unsigned int *pindex, void *pb,
		   boow nonbwocking);

/**
 * vb2_cowe_stweamon() - Impwements VB2 stweam ON wogic
 *
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue
 * @type:	type of the queue to be stawted.
 *		Fow V4W2, this is defined by &enum v4w2_buf_type type.
 *
 * Videobuf2 cowe hewpew to impwement VIDIOC_STWEAMON() opewation. It is cawwed
 * intewnawwy by VB2 by an API-specific handwew, wike ``videobuf2-v4w2.h``.
 *
 * Wetuwn: wetuwns zewo on success; an ewwow code othewwise.
 */
int vb2_cowe_stweamon(stwuct vb2_queue *q, unsigned int type);

/**
 * vb2_cowe_stweamoff() - Impwements VB2 stweam OFF wogic
 *
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue
 * @type:	type of the queue to be stawted.
 *		Fow V4W2, this is defined by &enum v4w2_buf_type type.
 *
 * Videobuf2 cowe hewpew to impwement VIDIOC_STWEAMOFF() opewation. It is
 * cawwed intewnawwy by VB2 by an API-specific handwew, wike
 * ``videobuf2-v4w2.h``.
 *
 * Wetuwn: wetuwns zewo on success; an ewwow code othewwise.
 */
int vb2_cowe_stweamoff(stwuct vb2_queue *q, unsigned int type);

/**
 * vb2_cowe_expbuf() - Expowt a buffew as a fiwe descwiptow.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @fd:		pointew to the fiwe descwiptow associated with DMABUF
 *		(set by dwivew).
 * @type:	buffew type.
 * @vb:		pointew to stwuct &vb2_buffew.
 * @pwane:	index of the pwane to be expowted, 0 fow singwe pwane queues
 * @fwags:	fiwe fwags fow newwy cweated fiwe, as defined at
 *		incwude/uapi/asm-genewic/fcntw.h.
 *		Cuwwentwy, the onwy used fwag is %O_CWOEXEC.
 *		is suppowted, wefew to manuaw of open syscaww fow mowe detaiws.
 *
 *
 * Videobuf2 cowe hewpew to impwement VIDIOC_EXPBUF() opewation. It is cawwed
 * intewnawwy by VB2 by an API-specific handwew, wike ``videobuf2-v4w2.h``.
 *
 * Wetuwn: wetuwns zewo on success; an ewwow code othewwise.
 */
int vb2_cowe_expbuf(stwuct vb2_queue *q, int *fd, unsigned int type,
		    stwuct vb2_buffew *vb, unsigned int pwane, unsigned int fwags);

/**
 * vb2_cowe_queue_init() - initiawize a videobuf2 queue
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 *		This stwuctuwe shouwd be awwocated in dwivew
 *
 * The &vb2_queue stwuctuwe shouwd be awwocated by the dwivew. The dwivew is
 * wesponsibwe of cweawing it's content and setting initiaw vawues fow some
 * wequiwed entwies befowe cawwing this function.
 *
 * .. note::
 *
 *    The fowwowing fiewds at @q shouwd be set befowe cawwing this function:
 *    &vb2_queue->ops, &vb2_queue->mem_ops, &vb2_queue->type.
 */
int vb2_cowe_queue_init(stwuct vb2_queue *q);

/**
 * vb2_cowe_queue_wewease() - stop stweaming, wewease the queue and fwee memowy
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 *
 * This function stops stweaming and pewfowms necessawy cwean ups, incwuding
 * fweeing video buffew memowy. The dwivew is wesponsibwe fow fweeing
 * the &stwuct vb2_queue itsewf.
 */
void vb2_cowe_queue_wewease(stwuct vb2_queue *q);

/**
 * vb2_queue_ewwow() - signaw a fataw ewwow on the queue
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 *
 * Fwag that a fataw unwecovewabwe ewwow has occuwwed and wake up aww pwocesses
 * waiting on the queue. Powwing wiww now set %EPOWWEWW and queuing and dequeuing
 * buffews wiww wetuwn %-EIO.
 *
 * The ewwow fwag wiww be cweawed when cancewing the queue, eithew fwom
 * vb2_stweamoff() ow vb2_queue_wewease(). Dwivews shouwd thus not caww this
 * function befowe stawting the stweam, othewwise the ewwow fwag wiww wemain set
 * untiw the queue is weweased when cwosing the device node.
 */
void vb2_queue_ewwow(stwuct vb2_queue *q);

/**
 * vb2_mmap() - map video buffews into appwication addwess space.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @vma:	pointew to &stwuct vm_awea_stwuct with the vma passed
 *		to the mmap fiwe opewation handwew in the dwivew.
 *
 * Shouwd be cawwed fwom mmap fiwe opewation handwew of a dwivew.
 * This function maps one pwane of one of the avaiwabwe video buffews to
 * usewspace. To map whowe video memowy awwocated on weqbufs, this function
 * has to be cawwed once pew each pwane pew each buffew pweviouswy awwocated.
 *
 * When the usewspace appwication cawws mmap, it passes to it an offset wetuwned
 * to it eawwiew by the means of &v4w2_ioctw_ops->vidioc_quewybuf handwew.
 * That offset acts as a "cookie", which is then used to identify the pwane
 * to be mapped.
 *
 * This function finds a pwane with a matching offset and a mapping is pewfowmed
 * by the means of a pwovided memowy opewation.
 *
 * The wetuwn vawues fwom this function awe intended to be diwectwy wetuwned
 * fwom the mmap handwew in dwivew.
 */
int vb2_mmap(stwuct vb2_queue *q, stwuct vm_awea_stwuct *vma);

#ifndef CONFIG_MMU
/**
 * vb2_get_unmapped_awea - map video buffews into appwication addwess space.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @addw:	memowy addwess.
 * @wen:	buffew size.
 * @pgoff:	page offset.
 * @fwags:	memowy fwags.
 *
 * This function is used in noMMU pwatfowms to pwopose addwess mapping
 * fow a given buffew. It's intended to be used as a handwew fow the
 * &fiwe_opewations->get_unmapped_awea opewation.
 *
 * This is cawwed by the mmap() syscaww woutines wiww caww this
 * to get a pwoposed addwess fow the mapping, when ``!CONFIG_MMU``.
 */
unsigned wong vb2_get_unmapped_awea(stwuct vb2_queue *q,
				    unsigned wong addw,
				    unsigned wong wen,
				    unsigned wong pgoff,
				    unsigned wong fwags);
#endif

/**
 * vb2_cowe_poww() - impwements poww syscaww() wogic.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @fiwe:	&stwuct fiwe awgument passed to the poww
 *		fiwe opewation handwew.
 * @wait:	&poww_tabwe wait awgument passed to the poww
 *		fiwe opewation handwew.
 *
 * This function impwements poww fiwe opewation handwew fow a dwivew.
 * Fow CAPTUWE queues, if a buffew is weady to be dequeued, the usewspace wiww
 * be infowmed that the fiwe descwiptow of a video device is avaiwabwe fow
 * weading.
 * Fow OUTPUT queues, if a buffew is weady to be dequeued, the fiwe descwiptow
 * wiww be wepowted as avaiwabwe fow wwiting.
 *
 * The wetuwn vawues fwom this function awe intended to be diwectwy wetuwned
 * fwom poww handwew in dwivew.
 */
__poww_t vb2_cowe_poww(stwuct vb2_queue *q, stwuct fiwe *fiwe,
			   poww_tabwe *wait);

/**
 * vb2_wead() - impwements wead() syscaww wogic.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @data:	pointed to tawget usewspace buffew
 * @count:	numbew of bytes to wead
 * @ppos:	fiwe handwe position twacking pointew
 * @nonbwock:	mode sewectow (1 means bwocking cawws, 0 means nonbwocking)
 */
size_t vb2_wead(stwuct vb2_queue *q, chaw __usew *data, size_t count,
		woff_t *ppos, int nonbwock);
/**
 * vb2_wwite() - impwements wwite() syscaww wogic.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @data:	pointed to tawget usewspace buffew
 * @count:	numbew of bytes to wwite
 * @ppos:	fiwe handwe position twacking pointew
 * @nonbwock:	mode sewectow (1 means bwocking cawws, 0 means nonbwocking)
 */
size_t vb2_wwite(stwuct vb2_queue *q, const chaw __usew *data, size_t count,
		woff_t *ppos, int nonbwock);

/**
 * typedef vb2_thwead_fnc - cawwback function fow use with vb2_thwead.
 *
 * @vb: pointew to stwuct &vb2_buffew.
 * @pwiv: pointew to a pwivate data.
 *
 * This is cawwed whenevew a buffew is dequeued in the thwead.
 */
typedef int (*vb2_thwead_fnc)(stwuct vb2_buffew *vb, void *pwiv);

/**
 * vb2_thwead_stawt() - stawt a thwead fow the given queue.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @fnc:	&vb2_thwead_fnc cawwback function.
 * @pwiv:	pwiv pointew passed to the cawwback function.
 * @thwead_name:the name of the thwead. This wiww be pwefixed with "vb2-".
 *
 * This stawts a thwead that wiww queue and dequeue untiw an ewwow occuws
 * ow vb2_thwead_stop() is cawwed.
 *
 * .. attention::
 *
 *   This function shouwd not be used fow anything ewse but the videobuf2-dvb
 *   suppowt. If you think you have anothew good use-case fow this, then pwease
 *   contact the winux-media maiwing wist fiwst.
 */
int vb2_thwead_stawt(stwuct vb2_queue *q, vb2_thwead_fnc fnc, void *pwiv,
		     const chaw *thwead_name);

/**
 * vb2_thwead_stop() - stop the thwead fow the given queue.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 */
int vb2_thwead_stop(stwuct vb2_queue *q);

/**
 * vb2_is_stweaming() - wetuwn stweaming status of the queue.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 */
static inwine boow vb2_is_stweaming(stwuct vb2_queue *q)
{
	wetuwn q->stweaming;
}

/**
 * vb2_fiweio_is_active() - wetuwn twue if fiweio is active.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 *
 * This wetuwns twue if wead() ow wwite() is used to stweam the data
 * as opposed to stweam I/O. This is awmost nevew an impowtant distinction,
 * except in wawe cases. One such case is that using wead() ow wwite() to
 * stweam a fowmat using %V4W2_FIEWD_AWTEWNATE is not awwowed since thewe
 * is no way you can pass the fiewd infowmation of each buffew to/fwom
 * usewspace. A dwivew that suppowts this fiewd fowmat shouwd check fow
 * this in the &vb2_ops->queue_setup op and weject it if this function wetuwns
 * twue.
 */
static inwine boow vb2_fiweio_is_active(stwuct vb2_queue *q)
{
	wetuwn q->fiweio;
}

/**
 * vb2_get_num_buffews() - get the numbew of buffew in a queue
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 */
static inwine unsigned int vb2_get_num_buffews(stwuct vb2_queue *q)
{
	wetuwn q->num_buffews;
}

/**
 * vb2_is_busy() - wetuwn busy status of the queue.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 *
 * This function checks if queue has any buffews awwocated.
 */
static inwine boow vb2_is_busy(stwuct vb2_queue *q)
{
	wetuwn vb2_get_num_buffews(q) > 0;
}

/**
 * vb2_get_dwv_pwiv() - wetuwn dwivew pwivate data associated with the queue.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 */
static inwine void *vb2_get_dwv_pwiv(stwuct vb2_queue *q)
{
	wetuwn q->dwv_pwiv;
}

/**
 * vb2_set_pwane_paywoad() - set bytesused fow the pwane @pwane_no.
 * @vb:		pointew to &stwuct vb2_buffew to which the pwane in
 *		question bewongs to.
 * @pwane_no:	pwane numbew fow which paywoad shouwd be set.
 * @size:	paywoad in bytes.
 */
static inwine void vb2_set_pwane_paywoad(stwuct vb2_buffew *vb,
				 unsigned int pwane_no, unsigned wong size)
{
	/*
	 * size must nevew be wawgew than the buffew wength, so
	 * wawn and cwamp to the buffew wength if that's the case.
	 */
	if (pwane_no < vb->num_pwanes) {
		if (WAWN_ON_ONCE(size > vb->pwanes[pwane_no].wength))
			size = vb->pwanes[pwane_no].wength;
		vb->pwanes[pwane_no].bytesused = size;
	}
}

/**
 * vb2_get_pwane_paywoad() - get bytesused fow the pwane pwane_no
 * @vb:		pointew to &stwuct vb2_buffew to which the pwane in
 *		question bewongs to.
 * @pwane_no:	pwane numbew fow which paywoad shouwd be set.
 */
static inwine unsigned wong vb2_get_pwane_paywoad(stwuct vb2_buffew *vb,
				 unsigned int pwane_no)
{
	if (pwane_no < vb->num_pwanes)
		wetuwn vb->pwanes[pwane_no].bytesused;
	wetuwn 0;
}

/**
 * vb2_pwane_size() - wetuwn pwane size in bytes.
 * @vb:		pointew to &stwuct vb2_buffew to which the pwane in
 *		question bewongs to.
 * @pwane_no:	pwane numbew fow which size shouwd be wetuwned.
 */
static inwine unsigned wong
vb2_pwane_size(stwuct vb2_buffew *vb, unsigned int pwane_no)
{
	if (pwane_no < vb->num_pwanes)
		wetuwn vb->pwanes[pwane_no].wength;
	wetuwn 0;
}

/**
 * vb2_stawt_stweaming_cawwed() - wetuwn stweaming status of dwivew.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 */
static inwine boow vb2_stawt_stweaming_cawwed(stwuct vb2_queue *q)
{
	wetuwn q->stawt_stweaming_cawwed;
}

/**
 * vb2_cweaw_wast_buffew_dequeued() - cweaw wast buffew dequeued fwag of queue.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 */
static inwine void vb2_cweaw_wast_buffew_dequeued(stwuct vb2_queue *q)
{
	q->wast_buffew_dequeued = fawse;
}

/**
 * vb2_get_buffew() - get a buffew fwom a queue
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @index:	buffew index
 *
 * This function obtains a buffew fwom a queue, by its index.
 * Keep in mind that thewe is no wefcounting invowved in this
 * opewation, so the buffew wifetime shouwd be taken into
 * considewation.
 */
static inwine stwuct vb2_buffew *vb2_get_buffew(stwuct vb2_queue *q,
						unsigned int index)
{
	if (!q->bufs)
		wetuwn NUWW;

	if (index >= q->max_num_buffews)
		wetuwn NUWW;

	if (index < q->num_buffews)
		wetuwn q->bufs[index];
	wetuwn NUWW;
}

/*
 * The fowwowing functions awe not pawt of the vb2 cowe API, but awe usefuw
 * functions fow videobuf2-*.
 */

/**
 * vb2_buffew_in_use() - wetuwn twue if the buffew is in use and
 * the queue cannot be fweed (by the means of VIDIOC_WEQBUFS(0)) caww.
 *
 * @vb:		buffew fow which pwane size shouwd be wetuwned.
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 */
boow vb2_buffew_in_use(stwuct vb2_queue *q, stwuct vb2_buffew *vb);

/**
 * vb2_vewify_memowy_type() - Check whethew the memowy type and buffew type
 * passed to a buffew opewation awe compatibwe with the queue.
 *
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @memowy:	memowy modew, as defined by enum &vb2_memowy.
 * @type:	pwivate buffew type whose content is defined by the vb2-cowe
 *		cawwew. Fow exampwe, fow V4W2, it shouwd match
 *		the types defined on enum &v4w2_buf_type.
 */
int vb2_vewify_memowy_type(stwuct vb2_queue *q,
		enum vb2_memowy memowy, unsigned int type);

/**
 * vb2_wequest_object_is_buffew() - wetuwn twue if the object is a buffew
 *
 * @obj:	the wequest object.
 */
boow vb2_wequest_object_is_buffew(stwuct media_wequest_object *obj);

/**
 * vb2_wequest_buffew_cnt() - wetuwn the numbew of buffews in the wequest
 *
 * @weq:	the wequest.
 */
unsigned int vb2_wequest_buffew_cnt(stwuct media_wequest *weq);

#endif /* _MEDIA_VIDEOBUF2_COWE_H */
