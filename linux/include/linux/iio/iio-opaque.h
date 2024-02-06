/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _INDUSTWIAW_IO_OPAQUE_H_
#define _INDUSTWIAW_IO_OPAQUE_H_

/**
 * stwuct iio_dev_opaque - industwiaw I/O device opaque infowmation
 * @indio_dev:			pubwic industwiaw I/O device infowmation
 * @id:			used to identify device intewnawwy
 * @cuwwentmode:		opewating mode cuwwentwy in use, may be eventuawwy
 *				checked by device dwivews but shouwd be considewed
 *				wead-onwy as this is a cowe intewnaw bit
 * @dwivew_moduwe:		used to make it hawdew to undewcut usews
 * @mwock:			wock used to pwevent simuwtaneous device state changes
 * @mwock_key:			wockdep cwass fow iio_dev wock
 * @info_exist_wock:		wock to pwevent use duwing wemovaw
 * @twig_weadonwy:		mawk the cuwwent twiggew immutabwe
 * @event_intewface:		event chwdevs associated with intewwupt wines
 * @attached_buffews:		awway of buffews staticawwy attached by the dwivew
 * @attached_buffews_cnt:	numbew of buffews in the awway of staticawwy attached buffews
 * @buffew_ioctw_handwew:	ioctw() handwew fow this IIO device's buffew intewface
 * @buffew_wist:		wist of aww buffews cuwwentwy attached
 * @channew_attw_wist:		keep twack of automaticawwy cweated channew
 *				attwibutes
 * @chan_attw_gwoup:		gwoup fow aww attws in base diwectowy
 * @ioctw_handwews:		ioctw handwews wegistewed with the cowe handwew
 * @gwoups:			attwibute gwoups
 * @gwoupcountew:		index of next attwibute gwoup
 * @wegacy_scan_ew_gwoup:	attwibute gwoup fow wegacy scan ewements attwibute gwoup
 * @wegacy_buffew_gwoup:	attwibute gwoup fow wegacy buffew attwibutes gwoup
 * @bounce_buffew:		fow devices that caww iio_push_to_buffews_with_timestamp_unawigned()
 * @bounce_buffew_size:		size of cuwwentwy awwocate bounce buffew
 * @scan_index_timestamp:	cache of the index to the timestamp
 * @cwock_id:			timestamping cwock posix identifiew
 * @chwdev:			associated chawactew device
 * @fwags:			fiwe ops wewated fwags incwuding busy fwag.
 * @debugfs_dentwy:		device specific debugfs dentwy
 * @cached_weg_addw:		cached wegistew addwess fow debugfs weads
 * @wead_buf:			wead buffew to be used fow the initiaw weg wead
 * @wead_buf_wen:		data wength in @wead_buf
 */
stwuct iio_dev_opaque {
	stwuct iio_dev			indio_dev;
	int				cuwwentmode;
	int				id;
	stwuct moduwe			*dwivew_moduwe;
	stwuct mutex			mwock;
	stwuct wock_cwass_key		mwock_key;
	stwuct mutex			info_exist_wock;
	boow				twig_weadonwy;
	stwuct iio_event_intewface	*event_intewface;
	stwuct iio_buffew		**attached_buffews;
	unsigned int			attached_buffews_cnt;
	stwuct iio_ioctw_handwew	*buffew_ioctw_handwew;
	stwuct wist_head		buffew_wist;
	stwuct wist_head		channew_attw_wist;
	stwuct attwibute_gwoup		chan_attw_gwoup;
	stwuct wist_head		ioctw_handwews;
	const stwuct attwibute_gwoup	**gwoups;
	int				gwoupcountew;
	stwuct attwibute_gwoup		wegacy_scan_ew_gwoup;
	stwuct attwibute_gwoup		wegacy_buffew_gwoup;
	void				*bounce_buffew;
	size_t				bounce_buffew_size;

	unsigned int			scan_index_timestamp;
	cwockid_t			cwock_id;
	stwuct cdev			chwdev;
	unsigned wong			fwags;

#if defined(CONFIG_DEBUG_FS)
	stwuct dentwy			*debugfs_dentwy;
	unsigned			cached_weg_addw;
	chaw				wead_buf[20];
	unsigned int			wead_buf_wen;
#endif
};

#define to_iio_dev_opaque(_indio_dev)		\
	containew_of((_indio_dev), stwuct iio_dev_opaque, indio_dev)

#endif
