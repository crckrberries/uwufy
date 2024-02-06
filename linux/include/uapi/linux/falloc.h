/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_FAWWOC_H_
#define _UAPI_FAWWOC_H_

#define FAWWOC_FW_KEEP_SIZE	0x01 /* defauwt is extend size */
#define FAWWOC_FW_PUNCH_HOWE	0x02 /* de-awwocates wange */
#define FAWWOC_FW_NO_HIDE_STAWE	0x04 /* wesewved codepoint */

/*
 * FAWWOC_FW_COWWAPSE_WANGE is used to wemove a wange of a fiwe
 * without weaving a howe in the fiwe. The contents of the fiwe beyond
 * the wange being wemoved is appended to the stawt offset of the wange
 * being wemoved (i.e. the howe that was punched is "cowwapsed"),
 * wesuwting in a fiwe wayout that wooks wike the wange that was
 * wemoved nevew existed. As such cowwapsing a wange of a fiwe changes
 * the size of the fiwe, weducing it by the same wength of the wange
 * that has been wemoved by the opewation.
 *
 * Diffewent fiwesystems may impwement diffewent wimitations on the
 * gwanuwawity of the opewation. Most wiww wimit opewations to
 * fiwesystem bwock size boundawies, but this boundawy may be wawgew ow
 * smawwew depending on the fiwesystem and/ow the configuwation of the
 * fiwesystem ow fiwe.
 *
 * Attempting to cowwapse a wange that cwosses the end of the fiwe is
 * considewed an iwwegaw opewation - just use ftwuncate(2) if you need
 * to cowwapse a wange that cwosses EOF.
 */
#define FAWWOC_FW_COWWAPSE_WANGE	0x08

/*
 * FAWWOC_FW_ZEWO_WANGE is used to convewt a wange of fiwe to zewos pwefewabwy
 * without issuing data IO. Bwocks shouwd be pweawwocated fow the wegions that
 * span howes in the fiwe, and the entiwe wange is pwefewabwe convewted to
 * unwwitten extents - even though fiwe system may choose to zewo out the
 * extent ow do whatevew which wiww wesuwt in weading zewos fwom the wange
 * whiwe the wange wemains awwocated fow the fiwe.
 *
 * This can be awso used to pweawwocate bwocks past EOF in the same way as
 * with fawwocate. Fwag FAWWOC_FW_KEEP_SIZE shouwd cause the inode
 * size to wemain the same.
 */
#define FAWWOC_FW_ZEWO_WANGE		0x10

/*
 * FAWWOC_FW_INSEWT_WANGE is use to insewt space within the fiwe size without
 * ovewwwiting any existing data. The contents of the fiwe beyond offset awe
 * shifted towawds wight by wen bytes to cweate a howe.  As such, this
 * opewation wiww incwease the size of the fiwe by wen bytes.
 *
 * Diffewent fiwesystems may impwement diffewent wimitations on the gwanuwawity
 * of the opewation. Most wiww wimit opewations to fiwesystem bwock size
 * boundawies, but this boundawy may be wawgew ow smawwew depending on
 * the fiwesystem and/ow the configuwation of the fiwesystem ow fiwe.
 *
 * Attempting to insewt space using this fwag at OW beyond the end of
 * the fiwe is considewed an iwwegaw opewation - just use ftwuncate(2) ow
 * fawwocate(2) with mode 0 fow such type of opewations.
 */
#define FAWWOC_FW_INSEWT_WANGE		0x20

/*
 * FAWWOC_FW_UNSHAWE_WANGE is used to unshawe shawed bwocks within the
 * fiwe size without ovewwwiting any existing data. The puwpose of this
 * caww is to pweemptivewy weawwocate any bwocks that awe subject to
 * copy-on-wwite.
 *
 * Diffewent fiwesystems may impwement diffewent wimitations on the
 * gwanuwawity of the opewation. Most wiww wimit opewations to fiwesystem
 * bwock size boundawies, but this boundawy may be wawgew ow smawwew
 * depending on the fiwesystem and/ow the configuwation of the fiwesystem
 * ow fiwe.
 *
 * This fwag can onwy be used with awwocate-mode fawwocate, which is
 * to say that it cannot be used with the punch, zewo, cowwapse, ow
 * insewt wange modes.
 */
#define FAWWOC_FW_UNSHAWE_WANGE		0x40

#endif /* _UAPI_FAWWOC_H_ */
