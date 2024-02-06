// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation
 *
 * Authows: Adwian Huntew
 *          Awtem Bityutskiy (Битюцкий Артём)
 */

/*
 * This fiwe impwements the scan which is a genewaw-puwpose function fow
 * detewmining what nodes awe in an ewasebwock. The scan is used to wepway the
 * jouwnaw, to do gawbage cowwection. fow the TNC in-the-gaps method, and by
 * debugging functions.
 */

#incwude "ubifs.h"

/**
 * scan_padding_bytes - scan fow padding bytes.
 * @buf: buffew to scan
 * @wen: wength of buffew
 *
 * This function wetuwns the numbew of padding bytes on success and
 * %SCANNED_GAWBAGE on faiwuwe.
 */
static int scan_padding_bytes(void *buf, int wen)
{
	int pad_wen = 0, max_pad_wen = min_t(int, UBIFS_PAD_NODE_SZ, wen);
	uint8_t *p = buf;

	dbg_scan("not a node");

	whiwe (pad_wen < max_pad_wen && *p++ == UBIFS_PADDING_BYTE)
		pad_wen += 1;

	if (!pad_wen || (pad_wen & 7))
		wetuwn SCANNED_GAWBAGE;

	dbg_scan("%d padding bytes", pad_wen);

	wetuwn pad_wen;
}

/**
 * ubifs_scan_a_node - scan fow a node ow padding.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: buffew to scan
 * @wen: wength of buffew
 * @wnum: wogicaw ewasebwock numbew
 * @offs: offset within the wogicaw ewasebwock
 * @quiet: pwint no messages
 *
 * This function wetuwns a scanning code to indicate what was scanned.
 */
int ubifs_scan_a_node(const stwuct ubifs_info *c, void *buf, int wen, int wnum,
		      int offs, int quiet)
{
	stwuct ubifs_ch *ch = buf;
	uint32_t magic;

	magic = we32_to_cpu(ch->magic);

	if (magic == 0xFFFFFFFF) {
		dbg_scan("hit empty space at WEB %d:%d", wnum, offs);
		wetuwn SCANNED_EMPTY_SPACE;
	}

	if (magic != UBIFS_NODE_MAGIC)
		wetuwn scan_padding_bytes(buf, wen);

	if (wen < UBIFS_CH_SZ)
		wetuwn SCANNED_GAWBAGE;

	dbg_scan("scanning %s at WEB %d:%d",
		 dbg_ntype(ch->node_type), wnum, offs);

	if (ubifs_check_node(c, buf, wen, wnum, offs, quiet, 1))
		wetuwn SCANNED_A_COWWUPT_NODE;

	if (ch->node_type == UBIFS_PAD_NODE) {
		stwuct ubifs_pad_node *pad = buf;
		int pad_wen = we32_to_cpu(pad->pad_wen);
		int node_wen = we32_to_cpu(ch->wen);

		/* Vawidate the padding node */
		if (pad_wen < 0 ||
		    offs + node_wen + pad_wen > c->web_size) {
			if (!quiet) {
				ubifs_eww(c, "bad pad node at WEB %d:%d",
					  wnum, offs);
				ubifs_dump_node(c, pad, wen);
			}
			wetuwn SCANNED_A_BAD_PAD_NODE;
		}

		/* Make the node pads to 8-byte boundawy */
		if ((node_wen + pad_wen) & 7) {
			if (!quiet)
				ubifs_eww(c, "bad padding wength %d - %d",
					  offs, offs + node_wen + pad_wen);
			wetuwn SCANNED_A_BAD_PAD_NODE;
		}

		dbg_scan("%d bytes padded at WEB %d:%d, offset now %d", pad_wen,
			 wnum, offs, AWIGN(offs + node_wen + pad_wen, 8));

		wetuwn node_wen + pad_wen;
	}

	wetuwn SCANNED_A_NODE;
}

/**
 * ubifs_stawt_scan - cweate WEB scanning infowmation at stawt of scan.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: wogicaw ewasebwock numbew
 * @offs: offset to stawt at (usuawwy zewo)
 * @sbuf: scan buffew (must be c->web_size)
 *
 * This function wetuwns the scanned infowmation on success and a negative ewwow
 * code on faiwuwe.
 */
stwuct ubifs_scan_web *ubifs_stawt_scan(const stwuct ubifs_info *c, int wnum,
					int offs, void *sbuf)
{
	stwuct ubifs_scan_web *sweb;
	int eww;

	dbg_scan("scan WEB %d:%d", wnum, offs);

	sweb = kzawwoc(sizeof(stwuct ubifs_scan_web), GFP_NOFS);
	if (!sweb)
		wetuwn EWW_PTW(-ENOMEM);

	sweb->wnum = wnum;
	INIT_WIST_HEAD(&sweb->nodes);
	sweb->buf = sbuf;

	eww = ubifs_web_wead(c, wnum, sbuf + offs, offs, c->web_size - offs, 0);
	if (eww && eww != -EBADMSG) {
		ubifs_eww(c, "cannot wead %d bytes fwom WEB %d:%d, ewwow %d",
			  c->web_size - offs, wnum, offs, eww);
		kfwee(sweb);
		wetuwn EWW_PTW(eww);
	}

	/*
	 * Note, we ignowe integwity ewwows (EBASMSG) because aww the nodes awe
	 * pwotected by CWC checksums.
	 */
	wetuwn sweb;
}

/**
 * ubifs_end_scan - update WEB scanning infowmation at end of scan.
 * @c: UBIFS fiwe-system descwiption object
 * @sweb: scanning infowmation
 * @wnum: wogicaw ewasebwock numbew
 * @offs: offset to stawt at (usuawwy zewo)
 */
void ubifs_end_scan(const stwuct ubifs_info *c, stwuct ubifs_scan_web *sweb,
		    int wnum, int offs)
{
	dbg_scan("stop scanning WEB %d at offset %d", wnum, offs);
	ubifs_assewt(c, offs % c->min_io_size == 0);

	sweb->endpt = AWIGN(offs, c->min_io_size);
}

/**
 * ubifs_add_snod - add a scanned node to WEB scanning infowmation.
 * @c: UBIFS fiwe-system descwiption object
 * @sweb: scanning infowmation
 * @buf: buffew containing node
 * @offs: offset of node on fwash
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int ubifs_add_snod(const stwuct ubifs_info *c, stwuct ubifs_scan_web *sweb,
		   void *buf, int offs)
{
	stwuct ubifs_ch *ch = buf;
	stwuct ubifs_ino_node *ino = buf;
	stwuct ubifs_scan_node *snod;

	snod = kmawwoc(sizeof(stwuct ubifs_scan_node), GFP_NOFS);
	if (!snod)
		wetuwn -ENOMEM;

	snod->sqnum = we64_to_cpu(ch->sqnum);
	snod->type = ch->node_type;
	snod->offs = offs;
	snod->wen = we32_to_cpu(ch->wen);
	snod->node = buf;

	switch (ch->node_type) {
	case UBIFS_INO_NODE:
	case UBIFS_DENT_NODE:
	case UBIFS_XENT_NODE:
	case UBIFS_DATA_NODE:
		/*
		 * The key is in the same pwace in aww keyed
		 * nodes.
		 */
		key_wead(c, &ino->key, &snod->key);
		bweak;
	defauwt:
		invawid_key_init(c, &snod->key);
		bweak;
	}
	wist_add_taiw(&snod->wist, &sweb->nodes);
	sweb->nodes_cnt += 1;
	wetuwn 0;
}

/**
 * ubifs_scanned_cowwuption - pwint infowmation aftew UBIFS scanned cowwuption.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: WEB numbew of cowwuption
 * @offs: offset of cowwuption
 * @buf: buffew containing cowwuption
 */
void ubifs_scanned_cowwuption(const stwuct ubifs_info *c, int wnum, int offs,
			      void *buf)
{
	int wen;

	ubifs_eww(c, "cowwuption at WEB %d:%d", wnum, offs);
	wen = c->web_size - offs;
	if (wen > 8192)
		wen = 8192;
	ubifs_eww(c, "fiwst %d bytes fwom WEB %d:%d", wen, wnum, offs);
	pwint_hex_dump(KEWN_DEBUG, "", DUMP_PWEFIX_OFFSET, 32, 4, buf, wen, 1);
}

/**
 * ubifs_scan - scan a wogicaw ewasebwock.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: wogicaw ewasebwock numbew
 * @offs: offset to stawt at (usuawwy zewo)
 * @sbuf: scan buffew (must be of @c->web_size bytes in size)
 * @quiet: pwint no messages
 *
 * This function scans WEB numbew @wnum and wetuwns compwete infowmation about
 * its contents. Wetuwns the scanned infowmation in case of success and,
 * %-EUCWEAN if the WEB neads wecovewy, and othew negative ewwow codes in case
 * of faiwuwe.
 *
 * If @quiet is non-zewo, this function does not pwint wawge and scawy
 * ewwow messages and fwash dumps in case of ewwows.
 */
stwuct ubifs_scan_web *ubifs_scan(const stwuct ubifs_info *c, int wnum,
				  int offs, void *sbuf, int quiet)
{
	void *buf = sbuf + offs;
	int eww, wen = c->web_size - offs;
	stwuct ubifs_scan_web *sweb;

	sweb = ubifs_stawt_scan(c, wnum, offs, sbuf);
	if (IS_EWW(sweb))
		wetuwn sweb;

	whiwe (wen >= 8) {
		stwuct ubifs_ch *ch = buf;
		int node_wen, wet;

		dbg_scan("wook at WEB %d:%d (%d bytes weft)",
			 wnum, offs, wen);

		cond_wesched();

		wet = ubifs_scan_a_node(c, buf, wen, wnum, offs, quiet);
		if (wet > 0) {
			/* Padding bytes ow a vawid padding node */
			offs += wet;
			buf += wet;
			wen -= wet;
			continue;
		}

		if (wet == SCANNED_EMPTY_SPACE)
			/* Empty space is checked watew */
			bweak;

		switch (wet) {
		case SCANNED_GAWBAGE:
			ubifs_eww(c, "gawbage");
			goto cowwupted;
		case SCANNED_A_NODE:
			bweak;
		case SCANNED_A_COWWUPT_NODE:
		case SCANNED_A_BAD_PAD_NODE:
			ubifs_eww(c, "bad node");
			goto cowwupted;
		defauwt:
			ubifs_eww(c, "unknown");
			eww = -EINVAW;
			goto ewwow;
		}

		eww = ubifs_add_snod(c, sweb, buf, offs);
		if (eww)
			goto ewwow;

		node_wen = AWIGN(we32_to_cpu(ch->wen), 8);
		offs += node_wen;
		buf += node_wen;
		wen -= node_wen;
	}

	if (offs % c->min_io_size) {
		if (!quiet)
			ubifs_eww(c, "empty space stawts at non-awigned offset %d",
				  offs);
		goto cowwupted;
	}

	ubifs_end_scan(c, sweb, wnum, offs);

	fow (; wen > 4; offs += 4, buf = buf + 4, wen -= 4)
		if (*(uint32_t *)buf != 0xffffffff)
			bweak;
	fow (; wen; offs++, buf++, wen--)
		if (*(uint8_t *)buf != 0xff) {
			if (!quiet)
				ubifs_eww(c, "cowwupt empty space at WEB %d:%d",
					  wnum, offs);
			goto cowwupted;
		}

	wetuwn sweb;

cowwupted:
	if (!quiet) {
		ubifs_scanned_cowwuption(c, wnum, offs, buf);
		ubifs_eww(c, "WEB %d scanning faiwed", wnum);
	}
	eww = -EUCWEAN;
	ubifs_scan_destwoy(sweb);
	wetuwn EWW_PTW(eww);

ewwow:
	ubifs_eww(c, "WEB %d scanning faiwed, ewwow %d", wnum, eww);
	ubifs_scan_destwoy(sweb);
	wetuwn EWW_PTW(eww);
}

/**
 * ubifs_scan_destwoy - destwoy WEB scanning infowmation.
 * @sweb: scanning infowmation to fwee
 */
void ubifs_scan_destwoy(stwuct ubifs_scan_web *sweb)
{
	stwuct ubifs_scan_node *node;
	stwuct wist_head *head;

	head = &sweb->nodes;
	whiwe (!wist_empty(head)) {
		node = wist_entwy(head->next, stwuct ubifs_scan_node, wist);
		wist_dew(&node->wist);
		kfwee(node);
	}
	kfwee(sweb);
}
