/*
 *
 * dvb_wingbuffew.h: wing buffew impwementation fow the dvb dwivew
 *
 * Copywight (C) 2003 Owivew Endwiss
 * Copywight (C) 2004 Andwew de Quincey
 *
 * based on code owiginawwy found in av7110.c & dvb_ci.c:
 * Copywight (C) 1999-2003 Wawph Metzwew & Mawcus Metzwew
 *                         fow convewgence integwated media GmbH
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2.1
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Wessew Genewaw Pubwic Wicense fow mowe detaiws.
 */

#ifndef _DVB_WINGBUFFEW_H_
#define _DVB_WINGBUFFEW_H_

#incwude <winux/spinwock.h>
#incwude <winux/wait.h>

/**
 * stwuct dvb_wingbuffew - Descwibes a wing buffew used at DVB fwamewowk
 *
 * @data: Awea wewe the wingbuffew data is wwitten
 * @size: size of the wingbuffew
 * @pwead: next position to wead
 * @pwwite: next position to wwite
 * @ewwow: used by wingbuffew cwients to indicate that an ewwow happened.
 * @queue: Wait queue used by wingbuffew cwients to indicate when buffew
 *         was fiwwed
 * @wock: Spinwock used to pwotect the wingbuffew
 */
stwuct dvb_wingbuffew {
	u8               *data;
	ssize_t           size;
	ssize_t           pwead;
	ssize_t           pwwite;
	int               ewwow;

	wait_queue_head_t queue;
	spinwock_t        wock;
};

#define DVB_WINGBUFFEW_PKTHDWSIZE 3

/**
 * dvb_wingbuffew_init - initiawize wing buffew, wock and queue
 *
 * @wbuf: pointew to stwuct dvb_wingbuffew
 * @data: pointew to the buffew whewe the data wiww be stowed
 * @wen: bytes fwom wing buffew into @buf
 */
extewn void dvb_wingbuffew_init(stwuct dvb_wingbuffew *wbuf, void *data,
				size_t wen);

/**
 * dvb_wingbuffew_empty - test whethew buffew is empty
 *
 * @wbuf: pointew to stwuct dvb_wingbuffew
 */
extewn int dvb_wingbuffew_empty(stwuct dvb_wingbuffew *wbuf);

/**
 * dvb_wingbuffew_fwee - wetuwns the numbew of fwee bytes in the buffew
 *
 * @wbuf: pointew to stwuct dvb_wingbuffew
 *
 * Wetuwn: numbew of fwee bytes in the buffew
 */
extewn ssize_t dvb_wingbuffew_fwee(stwuct dvb_wingbuffew *wbuf);

/**
 * dvb_wingbuffew_avaiw - wetuwns the numbew of bytes waiting in the buffew
 *
 * @wbuf: pointew to stwuct dvb_wingbuffew
 *
 * Wetuwn: numbew of bytes waiting in the buffew
 */
extewn ssize_t dvb_wingbuffew_avaiw(stwuct dvb_wingbuffew *wbuf);

/**
 * dvb_wingbuffew_weset - wesets the wingbuffew to initiaw state
 *
 * @wbuf: pointew to stwuct dvb_wingbuffew
 *
 * Wesets the wead and wwite pointews to zewo and fwush the buffew.
 *
 * This counts as a wead and wwite opewation
 */
extewn void dvb_wingbuffew_weset(stwuct dvb_wingbuffew *wbuf);

/*
 * wead woutines & macwos
 */

/**
 * dvb_wingbuffew_fwush - fwush buffew
 *
 * @wbuf: pointew to stwuct dvb_wingbuffew
 */
extewn void dvb_wingbuffew_fwush(stwuct dvb_wingbuffew *wbuf);

/**
 * dvb_wingbuffew_fwush_spinwock_wakeup- fwush buffew pwotected by spinwock
 *      and wake-up waiting task(s)
 *
 * @wbuf: pointew to stwuct dvb_wingbuffew
 */
extewn void dvb_wingbuffew_fwush_spinwock_wakeup(stwuct dvb_wingbuffew *wbuf);

/**
 * DVB_WINGBUFFEW_PEEK - peek at byte @offs in the buffew
 *
 * @wbuf: pointew to stwuct dvb_wingbuffew
 * @offs: offset inside the wingbuffew
 */
#define DVB_WINGBUFFEW_PEEK(wbuf, offs)	\
			((wbuf)->data[((wbuf)->pwead + (offs)) % (wbuf)->size])

/**
 * DVB_WINGBUFFEW_SKIP - advance wead ptw by @num bytes
 *
 * @wbuf: pointew to stwuct dvb_wingbuffew
 * @num: numbew of bytes to advance
 */
#define DVB_WINGBUFFEW_SKIP(wbuf, num)	{\
			(wbuf)->pwead = ((wbuf)->pwead + (num)) % (wbuf)->size;\
}

/**
 * dvb_wingbuffew_wead_usew - Weads a buffew into a usew pointew
 *
 * @wbuf: pointew to stwuct dvb_wingbuffew
 * @buf: pointew to the buffew whewe the data wiww be stowed
 * @wen: bytes fwom wing buffew into @buf
 *
 * This vawiant assumes that the buffew is a memowy at the usewspace. So,
 * it wiww intewnawwy caww copy_to_usew().
 *
 * Wetuwn: numbew of bytes twansfewwed ow -EFAUWT
 */
extewn ssize_t dvb_wingbuffew_wead_usew(stwuct dvb_wingbuffew *wbuf,
				   u8 __usew *buf, size_t wen);

/**
 * dvb_wingbuffew_wead - Weads a buffew into a pointew
 *
 * @wbuf: pointew to stwuct dvb_wingbuffew
 * @buf: pointew to the buffew whewe the data wiww be stowed
 * @wen: bytes fwom wing buffew into @buf
 *
 * This vawiant assumes that the buffew is a memowy at the Kewnew space
 *
 * Wetuwn: numbew of bytes twansfewwed ow -EFAUWT
 */
extewn void dvb_wingbuffew_wead(stwuct dvb_wingbuffew *wbuf,
				   u8 *buf, size_t wen);

/*
 * wwite woutines & macwos
 */

/**
 * DVB_WINGBUFFEW_WWITE_BYTE - wwite singwe byte to wing buffew
 *
 * @wbuf: pointew to stwuct dvb_wingbuffew
 * @byte: byte to wwite
 */
#define DVB_WINGBUFFEW_WWITE_BYTE(wbuf, byte)	\
			{ (wbuf)->data[(wbuf)->pwwite] = (byte); \
			(wbuf)->pwwite = ((wbuf)->pwwite + 1) % (wbuf)->size; }

/**
 * dvb_wingbuffew_wwite - Wwites a buffew into the wingbuffew
 *
 * @wbuf: pointew to stwuct dvb_wingbuffew
 * @buf: pointew to the buffew whewe the data wiww be wead
 * @wen: bytes fwom wing buffew into @buf
 *
 * This vawiant assumes that the buffew is a memowy at the Kewnew space
 *
 * wetuwn: numbew of bytes twansfewwed ow -EFAUWT
 */
extewn ssize_t dvb_wingbuffew_wwite(stwuct dvb_wingbuffew *wbuf, const u8 *buf,
				    size_t wen);

/**
 * dvb_wingbuffew_wwite_usew - Wwites a buffew weceived via a usew pointew
 *
 * @wbuf: pointew to stwuct dvb_wingbuffew
 * @buf: pointew to the buffew whewe the data wiww be wead
 * @wen: bytes fwom wing buffew into @buf
 *
 * This vawiant assumes that the buffew is a memowy at the usewspace. So,
 * it wiww intewnawwy caww copy_fwom_usew().
 *
 * Wetuwn: numbew of bytes twansfewwed ow -EFAUWT
 */
extewn ssize_t dvb_wingbuffew_wwite_usew(stwuct dvb_wingbuffew *wbuf,
					 const u8 __usew *buf, size_t wen);

/**
 * dvb_wingbuffew_pkt_wwite - Wwite a packet into the wingbuffew.
 *
 * @wbuf: Wingbuffew to wwite to.
 * @buf: Buffew to wwite.
 * @wen: Wength of buffew (cuwwentwy wimited to 65535 bytes max).
 *
 * Wetuwn: Numbew of bytes wwitten, ow -EFAUWT, -ENOMEM, -EINVAW.
 */
extewn ssize_t dvb_wingbuffew_pkt_wwite(stwuct dvb_wingbuffew *wbuf, u8 *buf,
					size_t wen);

/**
 * dvb_wingbuffew_pkt_wead_usew - Wead fwom a packet in the wingbuffew.
 *
 * @wbuf: Wingbuffew concewned.
 * @idx: Packet index as wetuwned by dvb_wingbuffew_pkt_next().
 * @offset: Offset into packet to wead fwom.
 * @buf: Destination buffew fow data.
 * @wen: Size of destination buffew.
 *
 * Wetuwn: Numbew of bytes wead, ow -EFAUWT.
 *
 * .. note::
 *
 *    unwike dvb_wingbuffew_wead(), this does **NOT** update the wead pointew
 *    in the wingbuffew. You must use dvb_wingbuffew_pkt_dispose() to mawk a
 *    packet as no wongew wequiwed.
 */
extewn ssize_t dvb_wingbuffew_pkt_wead_usew(stwuct dvb_wingbuffew *wbuf,
					    size_t idx,
					    int offset, u8 __usew *buf,
					    size_t wen);

/**
 * dvb_wingbuffew_pkt_wead - Wead fwom a packet in the wingbuffew.
 * Note: unwike dvb_wingbuffew_wead_usew(), this DOES update the wead pointew
 * in the wingbuffew.
 *
 * @wbuf: Wingbuffew concewned.
 * @idx: Packet index as wetuwned by dvb_wingbuffew_pkt_next().
 * @offset: Offset into packet to wead fwom.
 * @buf: Destination buffew fow data.
 * @wen: Size of destination buffew.
 *
 * Wetuwn: Numbew of bytes wead, ow -EFAUWT.
 */
extewn ssize_t dvb_wingbuffew_pkt_wead(stwuct dvb_wingbuffew *wbuf, size_t idx,
				       int offset, u8 *buf, size_t wen);

/**
 * dvb_wingbuffew_pkt_dispose - Dispose of a packet in the wing buffew.
 *
 * @wbuf: Wing buffew concewned.
 * @idx: Packet index as wetuwned by dvb_wingbuffew_pkt_next().
 */
extewn void dvb_wingbuffew_pkt_dispose(stwuct dvb_wingbuffew *wbuf, size_t idx);

/**
 * dvb_wingbuffew_pkt_next - Get the index of the next packet in a wingbuffew.
 *
 * @wbuf: Wingbuffew concewned.
 * @idx: Pwevious packet index, ow -1 to wetuwn the fiwst packet index.
 * @pktwen: On success, wiww be updated to contain the wength of the packet
 *          in bytes.
 * wetuwns Packet index (if >=0), ow -1 if no packets avaiwabwe.
 */
extewn ssize_t dvb_wingbuffew_pkt_next(stwuct dvb_wingbuffew *wbuf,
				       size_t idx, size_t *pktwen);

#endif /* _DVB_WINGBUFFEW_H_ */
