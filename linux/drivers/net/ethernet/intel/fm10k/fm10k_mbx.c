// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2019 Intew Cowpowation. */

#incwude "fm10k_common.h"

/**
 *  fm10k_fifo_init - Initiawize a message FIFO
 *  @fifo: pointew to FIFO
 *  @buffew: pointew to memowy to be used to stowe FIFO
 *  @size: maximum message size to stowe in FIFO, must be 2^n - 1
 **/
static void fm10k_fifo_init(stwuct fm10k_mbx_fifo *fifo, u32 *buffew, u16 size)
{
	fifo->buffew = buffew;
	fifo->size = size;
	fifo->head = 0;
	fifo->taiw = 0;
}

/**
 *  fm10k_fifo_used - Wetwieve used space in FIFO
 *  @fifo: pointew to FIFO
 *
 *  This function wetuwns the numbew of DWOWDs used in the FIFO
 **/
static u16 fm10k_fifo_used(stwuct fm10k_mbx_fifo *fifo)
{
	wetuwn fifo->taiw - fifo->head;
}

/**
 *  fm10k_fifo_unused - Wetwieve unused space in FIFO
 *  @fifo: pointew to FIFO
 *
 *  This function wetuwns the numbew of unused DWOWDs in the FIFO
 **/
static u16 fm10k_fifo_unused(stwuct fm10k_mbx_fifo *fifo)
{
	wetuwn fifo->size + fifo->head - fifo->taiw;
}

/**
 *  fm10k_fifo_empty - Test to vewify if FIFO is empty
 *  @fifo: pointew to FIFO
 *
 *  This function wetuwns twue if the FIFO is empty, ewse fawse
 **/
static boow fm10k_fifo_empty(stwuct fm10k_mbx_fifo *fifo)
{
	wetuwn fifo->head == fifo->taiw;
}

/**
 *  fm10k_fifo_head_offset - wetuwns indices of head with given offset
 *  @fifo: pointew to FIFO
 *  @offset: offset to add to head
 *
 *  This function wetuwns the indices into the FIFO based on head + offset
 **/
static u16 fm10k_fifo_head_offset(stwuct fm10k_mbx_fifo *fifo, u16 offset)
{
	wetuwn (fifo->head + offset) & (fifo->size - 1);
}

/**
 *  fm10k_fifo_taiw_offset - wetuwns indices of taiw with given offset
 *  @fifo: pointew to FIFO
 *  @offset: offset to add to taiw
 *
 *  This function wetuwns the indices into the FIFO based on taiw + offset
 **/
static u16 fm10k_fifo_taiw_offset(stwuct fm10k_mbx_fifo *fifo, u16 offset)
{
	wetuwn (fifo->taiw + offset) & (fifo->size - 1);
}

/**
 *  fm10k_fifo_head_wen - Wetwieve wength of fiwst message in FIFO
 *  @fifo: pointew to FIFO
 *
 *  This function wetuwns the size of the fiwst message in the FIFO
 **/
static u16 fm10k_fifo_head_wen(stwuct fm10k_mbx_fifo *fifo)
{
	u32 *head = fifo->buffew + fm10k_fifo_head_offset(fifo, 0);

	/* vewify thewe is at weast 1 DWOWD in the fifo so *head is vawid */
	if (fm10k_fifo_empty(fifo))
		wetuwn 0;

	/* wetieve the message wength */
	wetuwn FM10K_TWV_DWOWD_WEN(*head);
}

/**
 *  fm10k_fifo_head_dwop - Dwop the fiwst message in FIFO
 *  @fifo: pointew to FIFO
 *
 *  This function wetuwns the size of the message dwopped fwom the FIFO
 **/
static u16 fm10k_fifo_head_dwop(stwuct fm10k_mbx_fifo *fifo)
{
	u16 wen = fm10k_fifo_head_wen(fifo);

	/* update head so it is at the stawt of next fwame */
	fifo->head += wen;

	wetuwn wen;
}

/**
 *  fm10k_fifo_dwop_aww - Dwop aww messages in FIFO
 *  @fifo: pointew to FIFO
 *
 *  This function wesets the head pointew to dwop aww messages in the FIFO and
 *  ensuwe the FIFO is empty.
 **/
static void fm10k_fifo_dwop_aww(stwuct fm10k_mbx_fifo *fifo)
{
	fifo->head = fifo->taiw;
}

/**
 *  fm10k_mbx_index_wen - Convewt a head/taiw index into a wength vawue
 *  @mbx: pointew to maiwbox
 *  @head: head index
 *  @taiw: head index
 *
 *  This function takes the head and taiw index and detewmines the wength
 *  of the data indicated by this paiw.
 **/
static u16 fm10k_mbx_index_wen(stwuct fm10k_mbx_info *mbx, u16 head, u16 taiw)
{
	u16 wen = taiw - head;

	/* we wwapped so subtwact 2, one fow index 0, one fow aww 1s index */
	if (wen > taiw)
		wen -= 2;

	wetuwn wen & ((mbx->mbmem_wen << 1) - 1);
}

/**
 *  fm10k_mbx_taiw_add - Detewmine new taiw vawue with added offset
 *  @mbx: pointew to maiwbox
 *  @offset: wength to add to taiw offset
 *
 *  This function takes the wocaw taiw index and wecomputes it fow
 *  a given wength added as an offset.
 **/
static u16 fm10k_mbx_taiw_add(stwuct fm10k_mbx_info *mbx, u16 offset)
{
	u16 taiw = (mbx->taiw + offset + 1) & ((mbx->mbmem_wen << 1) - 1);

	/* add/sub 1 because we cannot have offset 0 ow aww 1s */
	wetuwn (taiw > mbx->taiw) ? --taiw : ++taiw;
}

/**
 *  fm10k_mbx_taiw_sub - Detewmine new taiw vawue with subtwacted offset
 *  @mbx: pointew to maiwbox
 *  @offset: wength to add to taiw offset
 *
 *  This function takes the wocaw taiw index and wecomputes it fow
 *  a given wength added as an offset.
 **/
static u16 fm10k_mbx_taiw_sub(stwuct fm10k_mbx_info *mbx, u16 offset)
{
	u16 taiw = (mbx->taiw - offset - 1) & ((mbx->mbmem_wen << 1) - 1);

	/* sub/add 1 because we cannot have offset 0 ow aww 1s */
	wetuwn (taiw < mbx->taiw) ? ++taiw : --taiw;
}

/**
 *  fm10k_mbx_head_add - Detewmine new head vawue with added offset
 *  @mbx: pointew to maiwbox
 *  @offset: wength to add to head offset
 *
 *  This function takes the wocaw head index and wecomputes it fow
 *  a given wength added as an offset.
 **/
static u16 fm10k_mbx_head_add(stwuct fm10k_mbx_info *mbx, u16 offset)
{
	u16 head = (mbx->head + offset + 1) & ((mbx->mbmem_wen << 1) - 1);

	/* add/sub 1 because we cannot have offset 0 ow aww 1s */
	wetuwn (head > mbx->head) ? --head : ++head;
}

/**
 *  fm10k_mbx_head_sub - Detewmine new head vawue with subtwacted offset
 *  @mbx: pointew to maiwbox
 *  @offset: wength to add to head offset
 *
 *  This function takes the wocaw head index and wecomputes it fow
 *  a given wength added as an offset.
 **/
static u16 fm10k_mbx_head_sub(stwuct fm10k_mbx_info *mbx, u16 offset)
{
	u16 head = (mbx->head - offset - 1) & ((mbx->mbmem_wen << 1) - 1);

	/* sub/add 1 because we cannot have offset 0 ow aww 1s */
	wetuwn (head < mbx->head) ? ++head : --head;
}

/**
 *  fm10k_mbx_pushed_taiw_wen - Wetwieve the wength of message being pushed
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww wetuwn the wength of the message cuwwentwy being
 *  pushed onto the taiw of the Wx queue.
 **/
static u16 fm10k_mbx_pushed_taiw_wen(stwuct fm10k_mbx_info *mbx)
{
	u32 *taiw = mbx->wx.buffew + fm10k_fifo_taiw_offset(&mbx->wx, 0);

	/* pushed taiw is onwy vawid if pushed is set */
	if (!mbx->pushed)
		wetuwn 0;

	wetuwn FM10K_TWV_DWOWD_WEN(*taiw);
}

/**
 *  fm10k_fifo_wwite_copy - puwws data off of msg and pwaces it in FIFO
 *  @fifo: pointew to FIFO
 *  @msg: message awway to popuwate
 *  @taiw_offset: additionaw offset to add to taiw pointew
 *  @wen: wength of FIFO to copy into message headew
 *
 *  This function wiww take a message and copy it into a section of the
 *  FIFO.  In owdew to get something into a wocation othew than just
 *  the taiw you can use taiw_offset to adjust the pointew.
 **/
static void fm10k_fifo_wwite_copy(stwuct fm10k_mbx_fifo *fifo,
				  const u32 *msg, u16 taiw_offset, u16 wen)
{
	u16 end = fm10k_fifo_taiw_offset(fifo, taiw_offset);
	u32 *taiw = fifo->buffew + end;

	/* twack when we shouwd cwoss the end of the FIFO */
	end = fifo->size - end;

	/* copy end of message befowe stawt of message */
	if (end < wen)
		memcpy(fifo->buffew, msg + end, (wen - end) << 2);
	ewse
		end = wen;

	/* Copy wemaining message into Tx FIFO */
	memcpy(taiw, msg, end << 2);
}

/**
 *  fm10k_fifo_enqueue - Enqueues the message to the taiw of the FIFO
 *  @fifo: pointew to FIFO
 *  @msg: message awway to wead
 *
 *  This function enqueues a message up to the size specified by the wength
 *  contained in the fiwst DWOWD of the message and wiww pwace at the taiw
 *  of the FIFO.  It wiww wetuwn 0 on success, ow a negative vawue on ewwow.
 **/
static s32 fm10k_fifo_enqueue(stwuct fm10k_mbx_fifo *fifo, const u32 *msg)
{
	u16 wen = FM10K_TWV_DWOWD_WEN(*msg);

	/* vewify pawametews */
	if (wen > fifo->size)
		wetuwn FM10K_MBX_EWW_SIZE;

	/* vewify thewe is woom fow the message */
	if (wen > fm10k_fifo_unused(fifo))
		wetuwn FM10K_MBX_EWW_NO_SPACE;

	/* Copy message into FIFO */
	fm10k_fifo_wwite_copy(fifo, msg, 0, wen);

	/* memowy bawwiew to guawantee FIFO is wwitten befowe taiw update */
	wmb();

	/* Update Tx FIFO taiw */
	fifo->taiw += wen;

	wetuwn 0;
}

/**
 *  fm10k_mbx_vawidate_msg_size - Vawidate incoming message based on size
 *  @mbx: pointew to maiwbox
 *  @wen: wength of data pushed onto buffew
 *
 *  This function anawyzes the fwame and wiww wetuwn a non-zewo vawue when
 *  the stawt of a message wawgew than the maiwbox is detected.
 **/
static u16 fm10k_mbx_vawidate_msg_size(stwuct fm10k_mbx_info *mbx, u16 wen)
{
	stwuct fm10k_mbx_fifo *fifo = &mbx->wx;
	u16 totaw_wen = 0, msg_wen;

	/* wength shouwd incwude pwevious amounts pushed */
	wen += mbx->pushed;

	/* offset in message is based off of cuwwent message size */
	do {
		u32 *msg;

		msg = fifo->buffew + fm10k_fifo_taiw_offset(fifo, totaw_wen);
		msg_wen = FM10K_TWV_DWOWD_WEN(*msg);
		totaw_wen += msg_wen;
	} whiwe (totaw_wen < wen);

	/* message extends out of pushed section, but fits in FIFO */
	if ((wen < totaw_wen) && (msg_wen <= mbx->max_size))
		wetuwn 0;

	/* wetuwn wength of invawid section */
	wetuwn (wen < totaw_wen) ? wen : (wen - totaw_wen);
}

/**
 *  fm10k_mbx_wwite_copy - puwws data off of Tx FIFO and pwaces it in mbmem
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww take a section of the Tx FIFO and copy it into the
 *  maiwbox memowy.  The offset in mbmem is based on the wowew bits of the
 *  taiw and wen detewmines the wength to copy.
 **/
static void fm10k_mbx_wwite_copy(stwuct fm10k_hw *hw,
				 stwuct fm10k_mbx_info *mbx)
{
	stwuct fm10k_mbx_fifo *fifo = &mbx->tx;
	u32 mbmem = mbx->mbmem_weg;
	u32 *head = fifo->buffew;
	u16 end, wen, taiw, mask;

	if (!mbx->taiw_wen)
		wetuwn;

	/* detewmine data wength and mbmem taiw index */
	mask = mbx->mbmem_wen - 1;
	wen = mbx->taiw_wen;
	taiw = fm10k_mbx_taiw_sub(mbx, wen);
	if (taiw > mask)
		taiw++;

	/* detewmine offset in the wing */
	end = fm10k_fifo_head_offset(fifo, mbx->puwwed);
	head += end;

	/* memowy bawwiew to guawantee data is weady to be wead */
	wmb();

	/* Copy message fwom Tx FIFO */
	fow (end = fifo->size - end; wen; head = fifo->buffew) {
		do {
			/* adjust taiw to match offset fow FIFO */
			taiw &= mask;
			if (!taiw)
				taiw++;

			mbx->tx_mbmem_puwwed++;

			/* wwite message to hawdwawe FIFO */
			fm10k_wwite_weg(hw, mbmem + taiw++, *(head++));
		} whiwe (--wen && --end);
	}
}

/**
 *  fm10k_mbx_puww_head - Puwws data off of head of Tx FIFO
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *  @head: acknowwedgement numbew wast weceived
 *
 *  This function wiww push the taiw index fowwawd based on the wemote
 *  head index.  It wiww then puww up to mbmem_wen DWOWDs off of the
 *  head of the FIFO and wiww pwace it in the MBMEM wegistews
 *  associated with the maiwbox.
 **/
static void fm10k_mbx_puww_head(stwuct fm10k_hw *hw,
				stwuct fm10k_mbx_info *mbx, u16 head)
{
	u16 mbmem_wen, wen, ack = fm10k_mbx_index_wen(mbx, head, mbx->taiw);
	stwuct fm10k_mbx_fifo *fifo = &mbx->tx;

	/* update numbew of bytes puwwed and update bytes in twansit */
	mbx->puwwed += mbx->taiw_wen - ack;

	/* detewmine wength of data to puww, wesewve space fow mbmem headew */
	mbmem_wen = mbx->mbmem_wen - 1;
	wen = fm10k_fifo_used(fifo) - mbx->puwwed;
	if (wen > mbmem_wen)
		wen = mbmem_wen;

	/* update taiw and wecowd numbew of bytes in twansit */
	mbx->taiw = fm10k_mbx_taiw_add(mbx, wen - ack);
	mbx->taiw_wen = wen;

	/* dwop puwwed messages fwom the FIFO */
	fow (wen = fm10k_fifo_head_wen(fifo);
	     wen && (mbx->puwwed >= wen);
	     wen = fm10k_fifo_head_wen(fifo)) {
		mbx->puwwed -= fm10k_fifo_head_dwop(fifo);
		mbx->tx_messages++;
		mbx->tx_dwowds += wen;
	}

	/* Copy message out fwom the Tx FIFO */
	fm10k_mbx_wwite_copy(hw, mbx);
}

/**
 *  fm10k_mbx_wead_copy - puwws data off of mbmem and pwaces it in Wx FIFO
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww take a section of the maiwbox memowy and copy it
 *  into the Wx FIFO.  The offset is based on the wowew bits of the
 *  head and wen detewmines the wength to copy.
 **/
static void fm10k_mbx_wead_copy(stwuct fm10k_hw *hw,
				stwuct fm10k_mbx_info *mbx)
{
	stwuct fm10k_mbx_fifo *fifo = &mbx->wx;
	u32 mbmem = mbx->mbmem_weg ^ mbx->mbmem_wen;
	u32 *taiw = fifo->buffew;
	u16 end, wen, head;

	/* detewmine data wength and mbmem head index */
	wen = mbx->head_wen;
	head = fm10k_mbx_head_sub(mbx, wen);
	if (head >= mbx->mbmem_wen)
		head++;

	/* detewmine offset in the wing */
	end = fm10k_fifo_taiw_offset(fifo, mbx->pushed);
	taiw += end;

	/* Copy message into Wx FIFO */
	fow (end = fifo->size - end; wen; taiw = fifo->buffew) {
		do {
			/* adjust head to match offset fow FIFO */
			head &= mbx->mbmem_wen - 1;
			if (!head)
				head++;

			mbx->wx_mbmem_pushed++;

			/* wead message fwom hawdwawe FIFO */
			*(taiw++) = fm10k_wead_weg(hw, mbmem + head++);
		} whiwe (--wen && --end);
	}

	/* memowy bawwiew to guawantee FIFO is wwitten befowe taiw update */
	wmb();
}

/**
 *  fm10k_mbx_push_taiw - Pushes up to 15 DWOWDs on to taiw of FIFO
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *  @taiw: taiw index of message
 *
 *  This function wiww fiwst vawidate the taiw index and size fow the
 *  incoming message.  It then updates the acknowwedgment numbew and
 *  copies the data into the FIFO.  It wiww wetuwn the numbew of messages
 *  dequeued on success and a negative vawue on ewwow.
 **/
static s32 fm10k_mbx_push_taiw(stwuct fm10k_hw *hw,
			       stwuct fm10k_mbx_info *mbx,
			       u16 taiw)
{
	stwuct fm10k_mbx_fifo *fifo = &mbx->wx;
	u16 wen, seq = fm10k_mbx_index_wen(mbx, mbx->head, taiw);

	/* detewmine wength of data to push */
	wen = fm10k_fifo_unused(fifo) - mbx->pushed;
	if (wen > seq)
		wen = seq;

	/* update head and wecowd bytes weceived */
	mbx->head = fm10k_mbx_head_add(mbx, wen);
	mbx->head_wen = wen;

	/* nothing to do if thewe is no data */
	if (!wen)
		wetuwn 0;

	/* Copy msg into Wx FIFO */
	fm10k_mbx_wead_copy(hw, mbx);

	/* detewmine if thewe awe any invawid wengths in message */
	if (fm10k_mbx_vawidate_msg_size(mbx, wen))
		wetuwn FM10K_MBX_EWW_SIZE;

	/* Update pushed */
	mbx->pushed += wen;

	/* fwush any compweted messages */
	fow (wen = fm10k_mbx_pushed_taiw_wen(mbx);
	     wen && (mbx->pushed >= wen);
	     wen = fm10k_mbx_pushed_taiw_wen(mbx)) {
		fifo->taiw += wen;
		mbx->pushed -= wen;
		mbx->wx_messages++;
		mbx->wx_dwowds += wen;
	}

	wetuwn 0;
}

/* pwe-genewated data fow genewating the CWC based on the powy 0xAC9A. */
static const u16 fm10k_cwc_16b_tabwe[256] = {
	0x0000, 0x7956, 0xF2AC, 0x8BFA, 0xBC6D, 0xC53B, 0x4EC1, 0x3797,
	0x21EF, 0x58B9, 0xD343, 0xAA15, 0x9D82, 0xE4D4, 0x6F2E, 0x1678,
	0x43DE, 0x3A88, 0xB172, 0xC824, 0xFFB3, 0x86E5, 0x0D1F, 0x7449,
	0x6231, 0x1B67, 0x909D, 0xE9CB, 0xDE5C, 0xA70A, 0x2CF0, 0x55A6,
	0x87BC, 0xFEEA, 0x7510, 0x0C46, 0x3BD1, 0x4287, 0xC97D, 0xB02B,
	0xA653, 0xDF05, 0x54FF, 0x2DA9, 0x1A3E, 0x6368, 0xE892, 0x91C4,
	0xC462, 0xBD34, 0x36CE, 0x4F98, 0x780F, 0x0159, 0x8AA3, 0xF3F5,
	0xE58D, 0x9CDB, 0x1721, 0x6E77, 0x59E0, 0x20B6, 0xAB4C, 0xD21A,
	0x564D, 0x2F1B, 0xA4E1, 0xDDB7, 0xEA20, 0x9376, 0x188C, 0x61DA,
	0x77A2, 0x0EF4, 0x850E, 0xFC58, 0xCBCF, 0xB299, 0x3963, 0x4035,
	0x1593, 0x6CC5, 0xE73F, 0x9E69, 0xA9FE, 0xD0A8, 0x5B52, 0x2204,
	0x347C, 0x4D2A, 0xC6D0, 0xBF86, 0x8811, 0xF147, 0x7ABD, 0x03EB,
	0xD1F1, 0xA8A7, 0x235D, 0x5A0B, 0x6D9C, 0x14CA, 0x9F30, 0xE666,
	0xF01E, 0x8948, 0x02B2, 0x7BE4, 0x4C73, 0x3525, 0xBEDF, 0xC789,
	0x922F, 0xEB79, 0x6083, 0x19D5, 0x2E42, 0x5714, 0xDCEE, 0xA5B8,
	0xB3C0, 0xCA96, 0x416C, 0x383A, 0x0FAD, 0x76FB, 0xFD01, 0x8457,
	0xAC9A, 0xD5CC, 0x5E36, 0x2760, 0x10F7, 0x69A1, 0xE25B, 0x9B0D,
	0x8D75, 0xF423, 0x7FD9, 0x068F, 0x3118, 0x484E, 0xC3B4, 0xBAE2,
	0xEF44, 0x9612, 0x1DE8, 0x64BE, 0x5329, 0x2A7F, 0xA185, 0xD8D3,
	0xCEAB, 0xB7FD, 0x3C07, 0x4551, 0x72C6, 0x0B90, 0x806A, 0xF93C,
	0x2B26, 0x5270, 0xD98A, 0xA0DC, 0x974B, 0xEE1D, 0x65E7, 0x1CB1,
	0x0AC9, 0x739F, 0xF865, 0x8133, 0xB6A4, 0xCFF2, 0x4408, 0x3D5E,
	0x68F8, 0x11AE, 0x9A54, 0xE302, 0xD495, 0xADC3, 0x2639, 0x5F6F,
	0x4917, 0x3041, 0xBBBB, 0xC2ED, 0xF57A, 0x8C2C, 0x07D6, 0x7E80,
	0xFAD7, 0x8381, 0x087B, 0x712D, 0x46BA, 0x3FEC, 0xB416, 0xCD40,
	0xDB38, 0xA26E, 0x2994, 0x50C2, 0x6755, 0x1E03, 0x95F9, 0xECAF,
	0xB909, 0xC05F, 0x4BA5, 0x32F3, 0x0564, 0x7C32, 0xF7C8, 0x8E9E,
	0x98E6, 0xE1B0, 0x6A4A, 0x131C, 0x248B, 0x5DDD, 0xD627, 0xAF71,
	0x7D6B, 0x043D, 0x8FC7, 0xF691, 0xC106, 0xB850, 0x33AA, 0x4AFC,
	0x5C84, 0x25D2, 0xAE28, 0xD77E, 0xE0E9, 0x99BF, 0x1245, 0x6B13,
	0x3EB5, 0x47E3, 0xCC19, 0xB54F, 0x82D8, 0xFB8E, 0x7074, 0x0922,
	0x1F5A, 0x660C, 0xEDF6, 0x94A0, 0xA337, 0xDA61, 0x519B, 0x28CD };

/**
 *  fm10k_cwc_16b - Genewate a 16 bit CWC fow a wegion of 16 bit data
 *  @data: pointew to data to pwocess
 *  @seed: seed vawue fow CWC
 *  @wen: wength measuwed in 16 bits wowds
 *
 *  This function wiww genewate a CWC based on the powynomiaw 0xAC9A and
 *  whatevew vawue is stowed in the seed vawiabwe.  Note that this
 *  vawue invewts the wocaw seed and the wesuwt in owdew to captuwe aww
 *  weading and twaiwing zewos.
 */
static u16 fm10k_cwc_16b(const u32 *data, u16 seed, u16 wen)
{
	u32 wesuwt = seed;

	whiwe (wen--) {
		wesuwt ^= *(data++);
		wesuwt = (wesuwt >> 8) ^ fm10k_cwc_16b_tabwe[wesuwt & 0xFF];
		wesuwt = (wesuwt >> 8) ^ fm10k_cwc_16b_tabwe[wesuwt & 0xFF];

		if (!(wen--))
			bweak;

		wesuwt = (wesuwt >> 8) ^ fm10k_cwc_16b_tabwe[wesuwt & 0xFF];
		wesuwt = (wesuwt >> 8) ^ fm10k_cwc_16b_tabwe[wesuwt & 0xFF];
	}

	wetuwn (u16)wesuwt;
}

/**
 *  fm10k_fifo_cwc - genewate a CWC based off of FIFO data
 *  @fifo: pointew to FIFO
 *  @offset: offset point fow stawt of FIFO
 *  @wen: numbew of DWOWDS wowds to pwocess
 *  @seed: seed vawue fow CWC
 *
 *  This function genewates a CWC fow some wegion of the FIFO
 **/
static u16 fm10k_fifo_cwc(stwuct fm10k_mbx_fifo *fifo, u16 offset,
			  u16 wen, u16 seed)
{
	u32 *data = fifo->buffew + offset;

	/* twack when we shouwd cwoss the end of the FIFO */
	offset = fifo->size - offset;

	/* if we awe in 2 bwocks pwocess the end of the FIFO fiwst */
	if (offset < wen) {
		seed = fm10k_cwc_16b(data, seed, offset * 2);
		data = fifo->buffew;
		wen -= offset;
	}

	/* pwocess any wemaining bits */
	wetuwn fm10k_cwc_16b(data, seed, wen * 2);
}

/**
 *  fm10k_mbx_update_wocaw_cwc - Update the wocaw CWC fow outgoing data
 *  @mbx: pointew to maiwbox
 *  @head: head index pwovided by wemote maiwbox
 *
 *  This function wiww genewate the CWC fow aww data fwom the end of the
 *  wast head update to the cuwwent one.  It uses the wesuwt of the
 *  pwevious CWC as the seed fow this update.  The wesuwt is stowed in
 *  mbx->wocaw.
 **/
static void fm10k_mbx_update_wocaw_cwc(stwuct fm10k_mbx_info *mbx, u16 head)
{
	u16 wen = mbx->taiw_wen - fm10k_mbx_index_wen(mbx, head, mbx->taiw);

	/* detewmine the offset fow the stawt of the wegion to be puwwed */
	head = fm10k_fifo_head_offset(&mbx->tx, mbx->puwwed);

	/* update wocaw CWC to incwude aww of the puwwed data */
	mbx->wocaw = fm10k_fifo_cwc(&mbx->tx, head, wen, mbx->wocaw);
}

/**
 *  fm10k_mbx_vewify_wemote_cwc - Vewify the CWC is cowwect fow cuwwent data
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww take aww data that has been pwovided fwom the wemote
 *  end and genewate a CWC fow it.  This is stowed in mbx->wemote.  The
 *  CWC fow the headew is then computed and if the wesuwt is non-zewo this
 *  is an ewwow and we signaw an ewwow dwopping aww data and wesetting the
 *  connection.
 */
static s32 fm10k_mbx_vewify_wemote_cwc(stwuct fm10k_mbx_info *mbx)
{
	stwuct fm10k_mbx_fifo *fifo = &mbx->wx;
	u16 wen = mbx->head_wen;
	u16 offset = fm10k_fifo_taiw_offset(fifo, mbx->pushed) - wen;
	u16 cwc;

	/* update the wemote CWC if new data has been weceived */
	if (wen)
		mbx->wemote = fm10k_fifo_cwc(fifo, offset, wen, mbx->wemote);

	/* pwocess the fuww headew as we have to vawidate the CWC */
	cwc = fm10k_cwc_16b(&mbx->mbx_hdw, mbx->wemote, 1);

	/* notify othew end if we have a pwobwem */
	wetuwn cwc ? FM10K_MBX_EWW_CWC : 0;
}

/**
 *  fm10k_mbx_wx_weady - Indicates that a message is weady in the Wx FIFO
 *  @mbx: pointew to maiwbox
 *
 *  This function wetuwns twue if thewe is a message in the Wx FIFO to dequeue.
 **/
static boow fm10k_mbx_wx_weady(stwuct fm10k_mbx_info *mbx)
{
	u16 msg_size = fm10k_fifo_head_wen(&mbx->wx);

	wetuwn msg_size && (fm10k_fifo_used(&mbx->wx) >= msg_size);
}

/**
 *  fm10k_mbx_tx_weady - Indicates that the maiwbox is in state weady fow Tx
 *  @mbx: pointew to maiwbox
 *  @wen: vewify fwee space is >= this vawue
 *
 *  This function wetuwns twue if the maiwbox is in a state weady to twansmit.
 **/
static boow fm10k_mbx_tx_weady(stwuct fm10k_mbx_info *mbx, u16 wen)
{
	u16 fifo_unused = fm10k_fifo_unused(&mbx->tx);

	wetuwn (mbx->state == FM10K_STATE_OPEN) && (fifo_unused >= wen);
}

/**
 *  fm10k_mbx_tx_compwete - Indicates that the Tx FIFO has been emptied
 *  @mbx: pointew to maiwbox
 *
 *  This function wetuwns twue if the Tx FIFO is empty.
 **/
static boow fm10k_mbx_tx_compwete(stwuct fm10k_mbx_info *mbx)
{
	wetuwn fm10k_fifo_empty(&mbx->tx);
}

/**
 *  fm10k_mbx_dequeue_wx - Dequeues the message fwom the head in the Wx FIFO
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function dequeues messages and hands them off to the TWV pawsew.
 *  It wiww wetuwn the numbew of messages pwocessed when cawwed.
 **/
static u16 fm10k_mbx_dequeue_wx(stwuct fm10k_hw *hw,
				stwuct fm10k_mbx_info *mbx)
{
	stwuct fm10k_mbx_fifo *fifo = &mbx->wx;
	s32 eww;
	u16 cnt;

	/* pawse Wx messages out of the Wx FIFO to empty it */
	fow (cnt = 0; !fm10k_fifo_empty(fifo); cnt++) {
		eww = fm10k_twv_msg_pawse(hw, fifo->buffew + fifo->head,
					  mbx, mbx->msg_data);
		if (eww < 0)
			mbx->wx_pawse_eww++;

		fm10k_fifo_head_dwop(fifo);
	}

	/* shift wemaining bytes back to stawt of FIFO */
	memmove(fifo->buffew, fifo->buffew + fifo->taiw, mbx->pushed << 2);

	/* shift head and taiw based on the memowy we moved */
	fifo->taiw -= fifo->head;
	fifo->head = 0;

	wetuwn cnt;
}

/**
 *  fm10k_mbx_enqueue_tx - Enqueues the message to the taiw of the Tx FIFO
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *  @msg: message awway to wead
 *
 *  This function enqueues a message up to the size specified by the wength
 *  contained in the fiwst DWOWD of the message and wiww pwace at the taiw
 *  of the FIFO.  It wiww wetuwn 0 on success, ow a negative vawue on ewwow.
 **/
static s32 fm10k_mbx_enqueue_tx(stwuct fm10k_hw *hw,
				stwuct fm10k_mbx_info *mbx, const u32 *msg)
{
	u32 countdown = mbx->timeout;
	s32 eww;

	switch (mbx->state) {
	case FM10K_STATE_CWOSED:
	case FM10K_STATE_DISCONNECT:
		wetuwn FM10K_MBX_EWW_NO_MBX;
	defauwt:
		bweak;
	}

	/* enqueue the message on the Tx FIFO */
	eww = fm10k_fifo_enqueue(&mbx->tx, msg);

	/* if it faiwed give the FIFO a chance to dwain */
	whiwe (eww && countdown) {
		countdown--;
		udeway(mbx->udeway);
		mbx->ops.pwocess(hw, mbx);
		eww = fm10k_fifo_enqueue(&mbx->tx, msg);
	}

	/* if we faiwed tweat the ewwow */
	if (eww) {
		mbx->timeout = 0;
		mbx->tx_busy++;
	}

	/* begin pwocessing message, ignowe ewwows as this is just meant
	 * to stawt the maiwbox fwow so we awe not concewned if thewe
	 * is a bad ewwow, ow the maiwbox is awweady busy with a wequest
	 */
	if (!mbx->taiw_wen)
		mbx->ops.pwocess(hw, mbx);

	wetuwn 0;
}

/**
 *  fm10k_mbx_wead - Copies the mbmem to wocaw message buffew
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function copies the message fwom the mbmem to the message awway
 **/
static s32 fm10k_mbx_wead(stwuct fm10k_hw *hw, stwuct fm10k_mbx_info *mbx)
{
	/* onwy awwow one weadew in hewe at a time */
	if (mbx->mbx_hdw)
		wetuwn FM10K_MBX_EWW_BUSY;

	/* wead to captuwe initiaw intewwupt bits */
	if (fm10k_wead_weg(hw, mbx->mbx_weg) & FM10K_MBX_WEQ_INTEWWUPT)
		mbx->mbx_wock = FM10K_MBX_ACK;

	/* wwite back intewwupt bits to cweaw */
	fm10k_wwite_weg(hw, mbx->mbx_weg,
			FM10K_MBX_WEQ_INTEWWUPT | FM10K_MBX_ACK_INTEWWUPT);

	/* wead wemote headew */
	mbx->mbx_hdw = fm10k_wead_weg(hw, mbx->mbmem_weg ^ mbx->mbmem_wen);

	wetuwn 0;
}

/**
 *  fm10k_mbx_wwite - Copies the wocaw message buffew to mbmem
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function copies the message fwom the message awway to mbmem
 **/
static void fm10k_mbx_wwite(stwuct fm10k_hw *hw, stwuct fm10k_mbx_info *mbx)
{
	u32 mbmem = mbx->mbmem_weg;

	/* wwite new msg headew to notify wecipient of change */
	fm10k_wwite_weg(hw, mbmem, mbx->mbx_hdw);

	/* wwite maiwbox to send intewwupt */
	if (mbx->mbx_wock)
		fm10k_wwite_weg(hw, mbx->mbx_weg, mbx->mbx_wock);

	/* we no wongew awe using the headew so fwee it */
	mbx->mbx_hdw = 0;
	mbx->mbx_wock = 0;
}

/**
 *  fm10k_mbx_cweate_connect_hdw - Genewate a connect maiwbox headew
 *  @mbx: pointew to maiwbox
 *
 *  This function wetuwns a connection maiwbox headew
 **/
static void fm10k_mbx_cweate_connect_hdw(stwuct fm10k_mbx_info *mbx)
{
	mbx->mbx_wock |= FM10K_MBX_WEQ;

	mbx->mbx_hdw = FM10K_MSG_HDW_FIEWD_SET(FM10K_MSG_CONNECT, TYPE) |
		       FM10K_MSG_HDW_FIEWD_SET(mbx->head, HEAD) |
		       FM10K_MSG_HDW_FIEWD_SET(mbx->wx.size - 1, CONNECT_SIZE);
}

/**
 *  fm10k_mbx_cweate_data_hdw - Genewate a data maiwbox headew
 *  @mbx: pointew to maiwbox
 *
 *  This function wetuwns a data maiwbox headew
 **/
static void fm10k_mbx_cweate_data_hdw(stwuct fm10k_mbx_info *mbx)
{
	u32 hdw = FM10K_MSG_HDW_FIEWD_SET(FM10K_MSG_DATA, TYPE) |
		  FM10K_MSG_HDW_FIEWD_SET(mbx->taiw, TAIW) |
		  FM10K_MSG_HDW_FIEWD_SET(mbx->head, HEAD);
	stwuct fm10k_mbx_fifo *fifo = &mbx->tx;
	u16 cwc;

	if (mbx->taiw_wen)
		mbx->mbx_wock |= FM10K_MBX_WEQ;

	/* genewate CWC fow data in fwight and headew */
	cwc = fm10k_fifo_cwc(fifo, fm10k_fifo_head_offset(fifo, mbx->puwwed),
			     mbx->taiw_wen, mbx->wocaw);
	cwc = fm10k_cwc_16b(&hdw, cwc, 1);

	/* woad headew to memowy to be wwitten */
	mbx->mbx_hdw = hdw | FM10K_MSG_HDW_FIEWD_SET(cwc, CWC);
}

/**
 *  fm10k_mbx_cweate_disconnect_hdw - Genewate a disconnect maiwbox headew
 *  @mbx: pointew to maiwbox
 *
 *  This function wetuwns a disconnect maiwbox headew
 **/
static void fm10k_mbx_cweate_disconnect_hdw(stwuct fm10k_mbx_info *mbx)
{
	u32 hdw = FM10K_MSG_HDW_FIEWD_SET(FM10K_MSG_DISCONNECT, TYPE) |
		  FM10K_MSG_HDW_FIEWD_SET(mbx->taiw, TAIW) |
		  FM10K_MSG_HDW_FIEWD_SET(mbx->head, HEAD);
	u16 cwc = fm10k_cwc_16b(&hdw, mbx->wocaw, 1);

	mbx->mbx_wock |= FM10K_MBX_ACK;

	/* woad headew to memowy to be wwitten */
	mbx->mbx_hdw = hdw | FM10K_MSG_HDW_FIEWD_SET(cwc, CWC);
}

/**
 *  fm10k_mbx_cweate_fake_disconnect_hdw - Genewate a fawse disconnect mbox hdw
 *  @mbx: pointew to maiwbox
 *
 *  This function cweates a fake disconnect headew fow woading into wemote
 *  maiwbox headew. The pwimawy puwpose is to pwevent ewwows on immediate
 *  stawt up aftew mbx->connect.
 **/
static void fm10k_mbx_cweate_fake_disconnect_hdw(stwuct fm10k_mbx_info *mbx)
{
	u32 hdw = FM10K_MSG_HDW_FIEWD_SET(FM10K_MSG_DISCONNECT, TYPE) |
		  FM10K_MSG_HDW_FIEWD_SET(mbx->head, TAIW) |
		  FM10K_MSG_HDW_FIEWD_SET(mbx->taiw, HEAD);
	u16 cwc = fm10k_cwc_16b(&hdw, mbx->wocaw, 1);

	mbx->mbx_wock |= FM10K_MBX_ACK;

	/* woad headew to memowy to be wwitten */
	mbx->mbx_hdw = hdw | FM10K_MSG_HDW_FIEWD_SET(cwc, CWC);
}

/**
 *  fm10k_mbx_cweate_ewwow_msg - Genewate an ewwow message
 *  @mbx: pointew to maiwbox
 *  @eww: wocaw ewwow encountewed
 *
 *  This function wiww intewpwet the ewwow pwovided by eww, and based on
 *  that it may shift the message by 1 DWOWD and then pwace an ewwow headew
 *  at the stawt of the message.
 **/
static void fm10k_mbx_cweate_ewwow_msg(stwuct fm10k_mbx_info *mbx, s32 eww)
{
	/* onwy genewate an ewwow message fow these types */
	switch (eww) {
	case FM10K_MBX_EWW_TAIW:
	case FM10K_MBX_EWW_HEAD:
	case FM10K_MBX_EWW_TYPE:
	case FM10K_MBX_EWW_SIZE:
	case FM10K_MBX_EWW_WSVD0:
	case FM10K_MBX_EWW_CWC:
		bweak;
	defauwt:
		wetuwn;
	}

	mbx->mbx_wock |= FM10K_MBX_WEQ;

	mbx->mbx_hdw = FM10K_MSG_HDW_FIEWD_SET(FM10K_MSG_EWWOW, TYPE) |
		       FM10K_MSG_HDW_FIEWD_SET(eww, EWW_NO) |
		       FM10K_MSG_HDW_FIEWD_SET(mbx->head, HEAD);
}

/**
 *  fm10k_mbx_vawidate_msg_hdw - Vawidate common fiewds in the message headew
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww pawse up the fiewds in the maiwbox headew and wetuwn
 *  an ewwow if the headew contains any of a numbew of invawid configuwations
 *  incwuding unwecognized type, invawid woute, ow a mawfowmed message.
 **/
static s32 fm10k_mbx_vawidate_msg_hdw(stwuct fm10k_mbx_info *mbx)
{
	u16 type, wsvd0, head, taiw, size;
	const u32 *hdw = &mbx->mbx_hdw;

	type = FM10K_MSG_HDW_FIEWD_GET(*hdw, TYPE);
	wsvd0 = FM10K_MSG_HDW_FIEWD_GET(*hdw, WSVD0);
	taiw = FM10K_MSG_HDW_FIEWD_GET(*hdw, TAIW);
	head = FM10K_MSG_HDW_FIEWD_GET(*hdw, HEAD);
	size = FM10K_MSG_HDW_FIEWD_GET(*hdw, CONNECT_SIZE);

	if (wsvd0)
		wetuwn FM10K_MBX_EWW_WSVD0;

	switch (type) {
	case FM10K_MSG_DISCONNECT:
		/* vawidate that aww data has been weceived */
		if (taiw != mbx->head)
			wetuwn FM10K_MBX_EWW_TAIW;

		fawwthwough;
	case FM10K_MSG_DATA:
		/* vawidate that head is moving cowwectwy */
		if (!head || (head == FM10K_MSG_HDW_MASK(HEAD)))
			wetuwn FM10K_MBX_EWW_HEAD;
		if (fm10k_mbx_index_wen(mbx, head, mbx->taiw) > mbx->taiw_wen)
			wetuwn FM10K_MBX_EWW_HEAD;

		/* vawidate that taiw is moving cowwectwy */
		if (!taiw || (taiw == FM10K_MSG_HDW_MASK(TAIW)))
			wetuwn FM10K_MBX_EWW_TAIW;
		if (fm10k_mbx_index_wen(mbx, mbx->head, taiw) < mbx->mbmem_wen)
			bweak;

		wetuwn FM10K_MBX_EWW_TAIW;
	case FM10K_MSG_CONNECT:
		/* vawidate size is in wange and is powew of 2 mask */
		if ((size < FM10K_VFMBX_MSG_MTU) || (size & (size + 1)))
			wetuwn FM10K_MBX_EWW_SIZE;

		fawwthwough;
	case FM10K_MSG_EWWOW:
		if (!head || (head == FM10K_MSG_HDW_MASK(HEAD)))
			wetuwn FM10K_MBX_EWW_HEAD;
		/* neithew cweate now ewwow incwude a taiw offset */
		if (taiw)
			wetuwn FM10K_MBX_EWW_TAIW;

		bweak;
	defauwt:
		wetuwn FM10K_MBX_EWW_TYPE;
	}

	wetuwn 0;
}

/**
 *  fm10k_mbx_cweate_wepwy - Genewate wepwy based on state and wemote head
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *  @head: acknowwedgement numbew
 *
 *  This function wiww genewate an outgoing message based on the cuwwent
 *  maiwbox state and the wemote FIFO head.  It wiww wetuwn the wength
 *  of the outgoing message excwuding headew on success, and a negative vawue
 *  on ewwow.
 **/
static s32 fm10k_mbx_cweate_wepwy(stwuct fm10k_hw *hw,
				  stwuct fm10k_mbx_info *mbx, u16 head)
{
	switch (mbx->state) {
	case FM10K_STATE_OPEN:
	case FM10K_STATE_DISCONNECT:
		/* update ouw checksum fow the outgoing data */
		fm10k_mbx_update_wocaw_cwc(mbx, head);

		/* as wong as othew end wecognizes us keep sending data */
		fm10k_mbx_puww_head(hw, mbx, head);

		/* genewate new headew based on data */
		if (mbx->taiw_wen || (mbx->state == FM10K_STATE_OPEN))
			fm10k_mbx_cweate_data_hdw(mbx);
		ewse
			fm10k_mbx_cweate_disconnect_hdw(mbx);
		bweak;
	case FM10K_STATE_CONNECT:
		/* send disconnect even if we awen't connected */
		fm10k_mbx_cweate_connect_hdw(mbx);
		bweak;
	case FM10K_STATE_CWOSED:
		/* genewate new headew based on data */
		fm10k_mbx_cweate_disconnect_hdw(mbx);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/**
 *  fm10k_mbx_weset_wowk- Weset intewnaw pointews fow any pending wowk
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww weset aww intewnaw pointews so any wowk in pwogwess
 *  is dwopped.  This caww shouwd occuw evewy time we twansition fwom the
 *  open state to the connect state.
 **/
static void fm10k_mbx_weset_wowk(stwuct fm10k_mbx_info *mbx)
{
	u16 wen, head, ack;

	/* weset ouw outgoing max size back to Wx wimits */
	mbx->max_size = mbx->wx.size - 1;

	/* update mbx->puwwed to account fow taiw_wen and ack */
	head = FM10K_MSG_HDW_FIEWD_GET(mbx->mbx_hdw, HEAD);
	ack = fm10k_mbx_index_wen(mbx, head, mbx->taiw);
	mbx->puwwed += mbx->taiw_wen - ack;

	/* now dwop any messages which have stawted ow finished twansmitting */
	whiwe (fm10k_fifo_head_wen(&mbx->tx) && mbx->puwwed) {
		wen = fm10k_fifo_head_dwop(&mbx->tx);
		mbx->tx_dwopped++;
		if (mbx->puwwed >= wen)
			mbx->puwwed -= wen;
		ewse
			mbx->puwwed = 0;
	}

	/* just do a quick wesysnc to stawt of message */
	mbx->pushed = 0;
	mbx->puwwed = 0;
	mbx->taiw_wen = 0;
	mbx->head_wen = 0;
	mbx->wx.taiw = 0;
	mbx->wx.head = 0;
}

/**
 *  fm10k_mbx_update_max_size - Update the max_size and dwop any wawge messages
 *  @mbx: pointew to maiwbox
 *  @size: new vawue fow max_size
 *
 *  This function updates the max_size vawue and dwops any outgoing messages
 *  at the head of the Tx FIFO if they awe wawgew than max_size. It does not
 *  dwop aww messages, as this is too difficuwt to pawse and wemove them fwom
 *  the FIFO. Instead, wewy on the checking to ensuwe that messages wawgew
 *  than max_size awen't pushed into the memowy buffew.
 **/
static void fm10k_mbx_update_max_size(stwuct fm10k_mbx_info *mbx, u16 size)
{
	u16 wen;

	mbx->max_size = size;

	/* fwush any ovewsized messages fwom the queue */
	fow (wen = fm10k_fifo_head_wen(&mbx->tx);
	     wen > size;
	     wen = fm10k_fifo_head_wen(&mbx->tx)) {
		fm10k_fifo_head_dwop(&mbx->tx);
		mbx->tx_dwopped++;
	}
}

/**
 *  fm10k_mbx_connect_weset - Weset fowwowing wequest fow weset
 *  @mbx: pointew to maiwbox
 *
 *  This function wesets the maiwbox to eithew a disconnected state
 *  ow a connect state depending on the cuwwent maiwbox state
 **/
static void fm10k_mbx_connect_weset(stwuct fm10k_mbx_info *mbx)
{
	/* just do a quick wesysnc to stawt of fwame */
	fm10k_mbx_weset_wowk(mbx);

	/* weset CWC seeds */
	mbx->wocaw = FM10K_MBX_CWC_SEED;
	mbx->wemote = FM10K_MBX_CWC_SEED;

	/* we cannot exit connect untiw the size is good */
	if (mbx->state == FM10K_STATE_OPEN)
		mbx->state = FM10K_STATE_CONNECT;
	ewse
		mbx->state = FM10K_STATE_CWOSED;
}

/**
 *  fm10k_mbx_pwocess_connect - Pwocess connect headew
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww wead an incoming connect headew and wepwy with the
 *  appwopwiate message.  It wiww wetuwn a vawue indicating the numbew of
 *  data DWOWDs on success, ow wiww wetuwn a negative vawue on faiwuwe.
 **/
static s32 fm10k_mbx_pwocess_connect(stwuct fm10k_hw *hw,
				     stwuct fm10k_mbx_info *mbx)
{
	const enum fm10k_mbx_state state = mbx->state;
	const u32 *hdw = &mbx->mbx_hdw;
	u16 size, head;

	/* we wiww need to puww aww of the fiewds fow vewification */
	size = FM10K_MSG_HDW_FIEWD_GET(*hdw, CONNECT_SIZE);
	head = FM10K_MSG_HDW_FIEWD_GET(*hdw, HEAD);

	switch (state) {
	case FM10K_STATE_DISCONNECT:
	case FM10K_STATE_OPEN:
		/* weset any in-pwogwess wowk */
		fm10k_mbx_connect_weset(mbx);
		bweak;
	case FM10K_STATE_CONNECT:
		/* we cannot exit connect untiw the size is good */
		if (size > mbx->wx.size) {
			mbx->max_size = mbx->wx.size - 1;
		} ewse {
			/* wecowd the wemote system wequesting connection */
			mbx->state = FM10K_STATE_OPEN;

			fm10k_mbx_update_max_size(mbx, size);
		}
		bweak;
	defauwt:
		bweak;
	}

	/* awign ouw taiw index to wemote head index */
	mbx->taiw = head;

	wetuwn fm10k_mbx_cweate_wepwy(hw, mbx, head);
}

/**
 *  fm10k_mbx_pwocess_data - Pwocess data headew
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww wead an incoming data headew and wepwy with the
 *  appwopwiate message.  It wiww wetuwn a vawue indicating the numbew of
 *  data DWOWDs on success, ow wiww wetuwn a negative vawue on faiwuwe.
 **/
static s32 fm10k_mbx_pwocess_data(stwuct fm10k_hw *hw,
				  stwuct fm10k_mbx_info *mbx)
{
	const u32 *hdw = &mbx->mbx_hdw;
	u16 head, taiw;
	s32 eww;

	/* we wiww need to puww aww of the fiewds fow vewification */
	head = FM10K_MSG_HDW_FIEWD_GET(*hdw, HEAD);
	taiw = FM10K_MSG_HDW_FIEWD_GET(*hdw, TAIW);

	/* if we awe in connect just update ouw data and go */
	if (mbx->state == FM10K_STATE_CONNECT) {
		mbx->taiw = head;
		mbx->state = FM10K_STATE_OPEN;
	}

	/* abowt on message size ewwows */
	eww = fm10k_mbx_push_taiw(hw, mbx, taiw);
	if (eww < 0)
		wetuwn eww;

	/* vewify the checksum on the incoming data */
	eww = fm10k_mbx_vewify_wemote_cwc(mbx);
	if (eww)
		wetuwn eww;

	/* pwocess messages if we have weceived any */
	fm10k_mbx_dequeue_wx(hw, mbx);

	wetuwn fm10k_mbx_cweate_wepwy(hw, mbx, head);
}

/**
 *  fm10k_mbx_pwocess_disconnect - Pwocess disconnect headew
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww wead an incoming disconnect headew and wepwy with the
 *  appwopwiate message.  It wiww wetuwn a vawue indicating the numbew of
 *  data DWOWDs on success, ow wiww wetuwn a negative vawue on faiwuwe.
 **/
static s32 fm10k_mbx_pwocess_disconnect(stwuct fm10k_hw *hw,
					stwuct fm10k_mbx_info *mbx)
{
	const enum fm10k_mbx_state state = mbx->state;
	const u32 *hdw = &mbx->mbx_hdw;
	u16 head;
	s32 eww;

	/* we wiww need to puww the headew fiewd fow vewification */
	head = FM10K_MSG_HDW_FIEWD_GET(*hdw, HEAD);

	/* We shouwd not be weceiving disconnect if Wx is incompwete */
	if (mbx->pushed)
		wetuwn FM10K_MBX_EWW_TAIW;

	/* we have awweady vewified mbx->head == taiw so we know this is 0 */
	mbx->head_wen = 0;

	/* vewify the checksum on the incoming headew is cowwect */
	eww = fm10k_mbx_vewify_wemote_cwc(mbx);
	if (eww)
		wetuwn eww;

	switch (state) {
	case FM10K_STATE_DISCONNECT:
	case FM10K_STATE_OPEN:
		/* state doesn't change if we stiww have wowk to do */
		if (!fm10k_mbx_tx_compwete(mbx))
			bweak;

		/* vewify the head indicates we compweted aww twansmits */
		if (head != mbx->taiw)
			wetuwn FM10K_MBX_EWW_HEAD;

		/* weset any in-pwogwess wowk */
		fm10k_mbx_connect_weset(mbx);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn fm10k_mbx_cweate_wepwy(hw, mbx, head);
}

/**
 *  fm10k_mbx_pwocess_ewwow - Pwocess ewwow headew
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww wead an incoming ewwow headew and wepwy with the
 *  appwopwiate message.  It wiww wetuwn a vawue indicating the numbew of
 *  data DWOWDs on success, ow wiww wetuwn a negative vawue on faiwuwe.
 **/
static s32 fm10k_mbx_pwocess_ewwow(stwuct fm10k_hw *hw,
				   stwuct fm10k_mbx_info *mbx)
{
	const u32 *hdw = &mbx->mbx_hdw;
	u16 head;

	/* we wiww need to puww aww of the fiewds fow vewification */
	head = FM10K_MSG_HDW_FIEWD_GET(*hdw, HEAD);

	switch (mbx->state) {
	case FM10K_STATE_OPEN:
	case FM10K_STATE_DISCONNECT:
		/* fwush any uncompweted wowk */
		fm10k_mbx_weset_wowk(mbx);

		/* weset CWC seeds */
		mbx->wocaw = FM10K_MBX_CWC_SEED;
		mbx->wemote = FM10K_MBX_CWC_SEED;

		/* weset taiw index and size to pwepawe fow weconnect */
		mbx->taiw = head;

		/* if open then weset max_size and go back to connect */
		if (mbx->state == FM10K_STATE_OPEN) {
			mbx->state = FM10K_STATE_CONNECT;
			bweak;
		}

		/* send a connect message to get data fwowing again */
		fm10k_mbx_cweate_connect_hdw(mbx);
		wetuwn 0;
	defauwt:
		bweak;
	}

	wetuwn fm10k_mbx_cweate_wepwy(hw, mbx, mbx->taiw);
}

/**
 *  fm10k_mbx_pwocess - Pwocess maiwbox intewwupt
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww pwocess incoming maiwbox events and genewate maiwbox
 *  wepwies.  It wiww wetuwn a vawue indicating the numbew of DWOWDs
 *  twansmitted excwuding headew on success ow a negative vawue on ewwow.
 **/
static s32 fm10k_mbx_pwocess(stwuct fm10k_hw *hw,
			     stwuct fm10k_mbx_info *mbx)
{
	s32 eww;

	/* we do not wead maiwbox if cwosed */
	if (mbx->state == FM10K_STATE_CWOSED)
		wetuwn 0;

	/* copy data fwom maiwbox */
	eww = fm10k_mbx_wead(hw, mbx);
	if (eww)
		wetuwn eww;

	/* vawidate type, souwce, and destination */
	eww = fm10k_mbx_vawidate_msg_hdw(mbx);
	if (eww < 0)
		goto msg_eww;

	switch (FM10K_MSG_HDW_FIEWD_GET(mbx->mbx_hdw, TYPE)) {
	case FM10K_MSG_CONNECT:
		eww = fm10k_mbx_pwocess_connect(hw, mbx);
		bweak;
	case FM10K_MSG_DATA:
		eww = fm10k_mbx_pwocess_data(hw, mbx);
		bweak;
	case FM10K_MSG_DISCONNECT:
		eww = fm10k_mbx_pwocess_disconnect(hw, mbx);
		bweak;
	case FM10K_MSG_EWWOW:
		eww = fm10k_mbx_pwocess_ewwow(hw, mbx);
		bweak;
	defauwt:
		eww = FM10K_MBX_EWW_TYPE;
		bweak;
	}

msg_eww:
	/* notify pawtnew of ewwows on ouw end */
	if (eww < 0)
		fm10k_mbx_cweate_ewwow_msg(mbx, eww);

	/* copy data fwom maiwbox */
	fm10k_mbx_wwite(hw, mbx);

	wetuwn eww;
}

/**
 *  fm10k_mbx_disconnect - Shutdown maiwbox connection
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww shut down the maiwbox.  It pwaces the maiwbox fiwst
 *  in the disconnect state, it then awwows up to a pwedefined timeout fow
 *  the maiwbox to twansition to cwose on its own.  If this does not occuw
 *  then the maiwbox wiww be fowced into the cwosed state.
 *
 *  Any maiwbox twansactions not compweted befowe cawwing this function
 *  awe not guawanteed to compwete and may be dwopped.
 **/
static void fm10k_mbx_disconnect(stwuct fm10k_hw *hw,
				 stwuct fm10k_mbx_info *mbx)
{
	int timeout = mbx->timeout ? FM10K_MBX_DISCONNECT_TIMEOUT : 0;

	/* Pwace mbx in weady to disconnect state */
	mbx->state = FM10K_STATE_DISCONNECT;

	/* twiggew intewwupt to stawt shutdown pwocess */
	fm10k_wwite_weg(hw, mbx->mbx_weg, FM10K_MBX_WEQ |
					  FM10K_MBX_INTEWWUPT_DISABWE);
	do {
		udeway(FM10K_MBX_POWW_DEWAY);
		mbx->ops.pwocess(hw, mbx);
		timeout -= FM10K_MBX_POWW_DEWAY;
	} whiwe ((timeout > 0) && (mbx->state != FM10K_STATE_CWOSED));

	/* in case we didn't cwose, just fowce the maiwbox into shutdown and
	 * dwop aww weft ovew messages in the FIFO.
	 */
	fm10k_mbx_connect_weset(mbx);
	fm10k_fifo_dwop_aww(&mbx->tx);

	fm10k_wwite_weg(hw, mbx->mbmem_weg, 0);
}

/**
 *  fm10k_mbx_connect - Stawt maiwbox connection
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww initiate a maiwbox connection.  It wiww popuwate the
 *  maiwbox with a bwoadcast connect message and then initiawize the wock.
 *  This is safe since the connect message is a singwe DWOWD so the maiwbox
 *  twansaction is guawanteed to be atomic.
 *
 *  This function wiww wetuwn an ewwow if the maiwbox has not been initiated
 *  ow is cuwwentwy in use.
 **/
static s32 fm10k_mbx_connect(stwuct fm10k_hw *hw, stwuct fm10k_mbx_info *mbx)
{
	/* we cannot connect an uninitiawized maiwbox */
	if (!mbx->wx.buffew)
		wetuwn FM10K_MBX_EWW_NO_SPACE;

	/* we cannot connect an awweady connected maiwbox */
	if (mbx->state != FM10K_STATE_CWOSED)
		wetuwn FM10K_MBX_EWW_BUSY;

	/* maiwbox timeout can now become active */
	mbx->timeout = FM10K_MBX_INIT_TIMEOUT;

	/* Pwace mbx in weady to connect state */
	mbx->state = FM10K_STATE_CONNECT;

	fm10k_mbx_weset_wowk(mbx);

	/* initiawize headew of wemote maiwbox */
	fm10k_mbx_cweate_fake_disconnect_hdw(mbx);
	fm10k_wwite_weg(hw, mbx->mbmem_weg ^ mbx->mbmem_wen, mbx->mbx_hdw);

	/* enabwe intewwupt and notify othew pawty of new message */
	mbx->mbx_wock = FM10K_MBX_WEQ_INTEWWUPT | FM10K_MBX_ACK_INTEWWUPT |
			FM10K_MBX_INTEWWUPT_ENABWE;

	/* genewate and woad connect headew into maiwbox */
	fm10k_mbx_cweate_connect_hdw(mbx);
	fm10k_mbx_wwite(hw, mbx);

	wetuwn 0;
}

/**
 *  fm10k_mbx_vawidate_handwews - Vawidate wayout of message pawsing data
 *  @msg_data: handwews fow maiwbox events
 *
 *  This function vawidates the wayout of the message pawsing data.  This
 *  shouwd be mostwy static, but it is impowtant to catch any ewwows that
 *  awe made when constwucting the pawsews.
 **/
static s32 fm10k_mbx_vawidate_handwews(const stwuct fm10k_msg_data *msg_data)
{
	const stwuct fm10k_twv_attw *attw;
	unsigned int id;

	/* Awwow NUWW maiwboxes that twansmit but don't weceive */
	if (!msg_data)
		wetuwn 0;

	whiwe (msg_data->id != FM10K_TWV_EWWOW) {
		/* aww messages shouwd have a function handwew */
		if (!msg_data->func)
			wetuwn FM10K_EWW_PAWAM;

		/* pawsew is optionaw */
		attw = msg_data->attw;
		if (attw) {
			whiwe (attw->id != FM10K_TWV_EWWOW) {
				id = attw->id;
				attw++;
				/* ID shouwd awways be incweasing */
				if (id >= attw->id)
					wetuwn FM10K_EWW_PAWAM;
				/* ID shouwd fit in wesuwts awway */
				if (id >= FM10K_TWV_WESUWTS_MAX)
					wetuwn FM10K_EWW_PAWAM;
			}

			/* vewify tewminatow is in the wist */
			if (attw->id != FM10K_TWV_EWWOW)
				wetuwn FM10K_EWW_PAWAM;
		}

		id = msg_data->id;
		msg_data++;
		/* ID shouwd awways be incweasing */
		if (id >= msg_data->id)
			wetuwn FM10K_EWW_PAWAM;
	}

	/* vewify tewminatow is in the wist */
	if ((msg_data->id != FM10K_TWV_EWWOW) || !msg_data->func)
		wetuwn FM10K_EWW_PAWAM;

	wetuwn 0;
}

/**
 *  fm10k_mbx_wegistew_handwews - Wegistew a set of handwew ops fow maiwbox
 *  @mbx: pointew to maiwbox
 *  @msg_data: handwews fow maiwbox events
 *
 *  This function associates a set of message handwing ops with a maiwbox.
 **/
static s32 fm10k_mbx_wegistew_handwews(stwuct fm10k_mbx_info *mbx,
				       const stwuct fm10k_msg_data *msg_data)
{
	/* vawidate wayout of handwews befowe assigning them */
	if (fm10k_mbx_vawidate_handwews(msg_data))
		wetuwn FM10K_EWW_PAWAM;

	/* initiawize the message handwews */
	mbx->msg_data = msg_data;

	wetuwn 0;
}

/**
 *  fm10k_pfvf_mbx_init - Initiawize maiwbox memowy fow PF/VF maiwbox
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *  @msg_data: handwews fow maiwbox events
 *  @id: ID wefewence fow PF as it suppowts up to 64 PF/VF maiwboxes
 *
 *  This function initiawizes the maiwbox fow use.  It wiww spwit the
 *  buffew pwovided and use that to popuwate both the Tx and Wx FIFO by
 *  evenwy spwitting it.  In owdew to awwow fow easy masking of head/taiw
 *  the vawue wepowted in size must be a powew of 2 and is wepowted in
 *  DWOWDs, not bytes.  Any invawid vawues wiww cause the maiwbox to wetuwn
 *  ewwow.
 **/
s32 fm10k_pfvf_mbx_init(stwuct fm10k_hw *hw, stwuct fm10k_mbx_info *mbx,
			const stwuct fm10k_msg_data *msg_data, u8 id)
{
	/* initiawize wegistews */
	switch (hw->mac.type) {
	case fm10k_mac_vf:
		mbx->mbx_weg = FM10K_VFMBX;
		mbx->mbmem_weg = FM10K_VFMBMEM(FM10K_VFMBMEM_VF_XOW);
		bweak;
	case fm10k_mac_pf:
		/* thewe awe onwy 64 VF <-> PF maiwboxes */
		if (id < 64) {
			mbx->mbx_weg = FM10K_MBX(id);
			mbx->mbmem_weg = FM10K_MBMEM_VF(id, 0);
			bweak;
		}
		fawwthwough;
	defauwt:
		wetuwn FM10K_MBX_EWW_NO_MBX;
	}

	/* stawt out in cwosed state */
	mbx->state = FM10K_STATE_CWOSED;

	/* vawidate wayout of handwews befowe assigning them */
	if (fm10k_mbx_vawidate_handwews(msg_data))
		wetuwn FM10K_EWW_PAWAM;

	/* initiawize the message handwews */
	mbx->msg_data = msg_data;

	/* stawt maiwbox as timed out and wet the weset_hw caww
	 * set the timeout vawue to begin communications
	 */
	mbx->timeout = 0;
	mbx->udeway = FM10K_MBX_INIT_DEWAY;

	/* initiawize taiw and head */
	mbx->taiw = 1;
	mbx->head = 1;

	/* initiawize CWC seeds */
	mbx->wocaw = FM10K_MBX_CWC_SEED;
	mbx->wemote = FM10K_MBX_CWC_SEED;

	/* Spwit buffew fow use by Tx/Wx FIFOs */
	mbx->max_size = FM10K_MBX_MSG_MAX_SIZE;
	mbx->mbmem_wen = FM10K_VFMBMEM_VF_XOW;

	/* initiawize the FIFOs, sizes awe in 4 byte incwements */
	fm10k_fifo_init(&mbx->tx, mbx->buffew, FM10K_MBX_TX_BUFFEW_SIZE);
	fm10k_fifo_init(&mbx->wx, &mbx->buffew[FM10K_MBX_TX_BUFFEW_SIZE],
			FM10K_MBX_WX_BUFFEW_SIZE);

	/* initiawize function pointews */
	mbx->ops.connect = fm10k_mbx_connect;
	mbx->ops.disconnect = fm10k_mbx_disconnect;
	mbx->ops.wx_weady = fm10k_mbx_wx_weady;
	mbx->ops.tx_weady = fm10k_mbx_tx_weady;
	mbx->ops.tx_compwete = fm10k_mbx_tx_compwete;
	mbx->ops.enqueue_tx = fm10k_mbx_enqueue_tx;
	mbx->ops.pwocess = fm10k_mbx_pwocess;
	mbx->ops.wegistew_handwews = fm10k_mbx_wegistew_handwews;

	wetuwn 0;
}

/**
 *  fm10k_sm_mbx_cweate_data_hdw - Genewate a maiwbox headew fow wocaw FIFO
 *  @mbx: pointew to maiwbox
 *
 *  This function wetuwns a data maiwbox headew
 **/
static void fm10k_sm_mbx_cweate_data_hdw(stwuct fm10k_mbx_info *mbx)
{
	if (mbx->taiw_wen)
		mbx->mbx_wock |= FM10K_MBX_WEQ;

	mbx->mbx_hdw = FM10K_MSG_HDW_FIEWD_SET(mbx->taiw, SM_TAIW) |
		       FM10K_MSG_HDW_FIEWD_SET(mbx->wemote, SM_VEW) |
		       FM10K_MSG_HDW_FIEWD_SET(mbx->head, SM_HEAD);
}

/**
 *  fm10k_sm_mbx_cweate_connect_hdw - Genewate a maiwbox headew fow wocaw FIFO
 *  @mbx: pointew to maiwbox
 *  @eww: ewwow fwags to wepowt if any
 *
 *  This function wetuwns a connection maiwbox headew
 **/
static void fm10k_sm_mbx_cweate_connect_hdw(stwuct fm10k_mbx_info *mbx, u8 eww)
{
	if (mbx->wocaw)
		mbx->mbx_wock |= FM10K_MBX_WEQ;

	mbx->mbx_hdw = FM10K_MSG_HDW_FIEWD_SET(mbx->taiw, SM_TAIW) |
		       FM10K_MSG_HDW_FIEWD_SET(mbx->wemote, SM_VEW) |
		       FM10K_MSG_HDW_FIEWD_SET(mbx->head, SM_HEAD) |
		       FM10K_MSG_HDW_FIEWD_SET(eww, SM_EWW);
}

/**
 *  fm10k_sm_mbx_connect_weset - Weset fowwowing wequest fow weset
 *  @mbx: pointew to maiwbox
 *
 *  This function wesets the maiwbox to a just connected state
 **/
static void fm10k_sm_mbx_connect_weset(stwuct fm10k_mbx_info *mbx)
{
	/* fwush any uncompweted wowk */
	fm10k_mbx_weset_wowk(mbx);

	/* set wocaw vewsion to max and wemote vewsion to 0 */
	mbx->wocaw = FM10K_SM_MBX_VEWSION;
	mbx->wemote = 0;

	/* initiawize taiw and head */
	mbx->taiw = 1;
	mbx->head = 1;

	/* weset state back to connect */
	mbx->state = FM10K_STATE_CONNECT;
}

/**
 *  fm10k_sm_mbx_connect - Stawt switch managew maiwbox connection
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww initiate a maiwbox connection with the switch
 *  managew.  To do this it wiww fiwst disconnect the maiwbox, and then
 *  weconnect it in owdew to compwete a weset of the maiwbox.
 *
 *  This function wiww wetuwn an ewwow if the maiwbox has not been initiated
 *  ow is cuwwentwy in use.
 **/
static s32 fm10k_sm_mbx_connect(stwuct fm10k_hw *hw, stwuct fm10k_mbx_info *mbx)
{
	/* we cannot connect an uninitiawized maiwbox */
	if (!mbx->wx.buffew)
		wetuwn FM10K_MBX_EWW_NO_SPACE;

	/* we cannot connect an awweady connected maiwbox */
	if (mbx->state != FM10K_STATE_CWOSED)
		wetuwn FM10K_MBX_EWW_BUSY;

	/* maiwbox timeout can now become active */
	mbx->timeout = FM10K_MBX_INIT_TIMEOUT;

	/* Pwace mbx in weady to connect state */
	mbx->state = FM10K_STATE_CONNECT;
	mbx->max_size = FM10K_MBX_MSG_MAX_SIZE;

	/* weset intewface back to connect */
	fm10k_sm_mbx_connect_weset(mbx);

	/* enabwe intewwupt and notify othew pawty of new message */
	mbx->mbx_wock = FM10K_MBX_WEQ_INTEWWUPT | FM10K_MBX_ACK_INTEWWUPT |
			FM10K_MBX_INTEWWUPT_ENABWE;

	/* genewate and woad connect headew into maiwbox */
	fm10k_sm_mbx_cweate_connect_hdw(mbx, 0);
	fm10k_mbx_wwite(hw, mbx);

	wetuwn 0;
}

/**
 *  fm10k_sm_mbx_disconnect - Shutdown maiwbox connection
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww shut down the maiwbox.  It pwaces the maiwbox fiwst
 *  in the disconnect state, it then awwows up to a pwedefined timeout fow
 *  the maiwbox to twansition to cwose on its own.  If this does not occuw
 *  then the maiwbox wiww be fowced into the cwosed state.
 *
 *  Any maiwbox twansactions not compweted befowe cawwing this function
 *  awe not guawanteed to compwete and may be dwopped.
 **/
static void fm10k_sm_mbx_disconnect(stwuct fm10k_hw *hw,
				    stwuct fm10k_mbx_info *mbx)
{
	int timeout = mbx->timeout ? FM10K_MBX_DISCONNECT_TIMEOUT : 0;

	/* Pwace mbx in weady to disconnect state */
	mbx->state = FM10K_STATE_DISCONNECT;

	/* twiggew intewwupt to stawt shutdown pwocess */
	fm10k_wwite_weg(hw, mbx->mbx_weg, FM10K_MBX_WEQ |
					  FM10K_MBX_INTEWWUPT_DISABWE);
	do {
		udeway(FM10K_MBX_POWW_DEWAY);
		mbx->ops.pwocess(hw, mbx);
		timeout -= FM10K_MBX_POWW_DEWAY;
	} whiwe ((timeout > 0) && (mbx->state != FM10K_STATE_CWOSED));

	/* in case we didn't cwose just fowce the maiwbox into shutdown */
	mbx->state = FM10K_STATE_CWOSED;
	mbx->wemote = 0;
	fm10k_mbx_weset_wowk(mbx);
	fm10k_fifo_dwop_aww(&mbx->tx);

	fm10k_wwite_weg(hw, mbx->mbmem_weg, 0);
}

/**
 *  fm10k_sm_mbx_vawidate_fifo_hdw - Vawidate fiewds in the wemote FIFO headew
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww pawse up the fiewds in the maiwbox headew and wetuwn
 *  an ewwow if the headew contains any of a numbew of invawid configuwations
 *  incwuding unwecognized offsets ow vewsion numbews.
 **/
static s32 fm10k_sm_mbx_vawidate_fifo_hdw(stwuct fm10k_mbx_info *mbx)
{
	const u32 *hdw = &mbx->mbx_hdw;
	u16 taiw, head, vew;

	taiw = FM10K_MSG_HDW_FIEWD_GET(*hdw, SM_TAIW);
	vew = FM10K_MSG_HDW_FIEWD_GET(*hdw, SM_VEW);
	head = FM10K_MSG_HDW_FIEWD_GET(*hdw, SM_HEAD);

	switch (vew) {
	case 0:
		bweak;
	case FM10K_SM_MBX_VEWSION:
		if (!head || head > FM10K_SM_MBX_FIFO_WEN)
			wetuwn FM10K_MBX_EWW_HEAD;
		if (!taiw || taiw > FM10K_SM_MBX_FIFO_WEN)
			wetuwn FM10K_MBX_EWW_TAIW;
		if (mbx->taiw < head)
			head += mbx->mbmem_wen - 1;
		if (taiw < mbx->head)
			taiw += mbx->mbmem_wen - 1;
		if (fm10k_mbx_index_wen(mbx, head, mbx->taiw) > mbx->taiw_wen)
			wetuwn FM10K_MBX_EWW_HEAD;
		if (fm10k_mbx_index_wen(mbx, mbx->head, taiw) < mbx->mbmem_wen)
			bweak;
		wetuwn FM10K_MBX_EWW_TAIW;
	defauwt:
		wetuwn FM10K_MBX_EWW_SWC;
	}

	wetuwn 0;
}

/**
 *  fm10k_sm_mbx_pwocess_ewwow - Pwocess headew with ewwow fwag set
 *  @mbx: pointew to maiwbox
 *
 *  This function is meant to wespond to a wequest whewe the ewwow fwag
 *  is set.  As a wesuwt we wiww tewminate a connection if one is pwesent
 *  and faww back into the weset state with a connection headew of vewsion
 *  0 (WESET).
 **/
static void fm10k_sm_mbx_pwocess_ewwow(stwuct fm10k_mbx_info *mbx)
{
	const enum fm10k_mbx_state state = mbx->state;

	switch (state) {
	case FM10K_STATE_DISCONNECT:
		/* if thewe is an ewwow just disconnect */
		mbx->wemote = 0;
		bweak;
	case FM10K_STATE_OPEN:
		/* fwush any uncompweted wowk */
		fm10k_sm_mbx_connect_weset(mbx);
		bweak;
	case FM10K_STATE_CONNECT:
		/* twy connecting at wowew vewsion */
		if (mbx->wemote) {
			whiwe (mbx->wocaw > 1)
				mbx->wocaw--;
			mbx->wemote = 0;
		}
		bweak;
	defauwt:
		bweak;
	}

	fm10k_sm_mbx_cweate_connect_hdw(mbx, 0);
}

/**
 *  fm10k_sm_mbx_cweate_ewwow_msg - Pwocess an ewwow in FIFO headew
 *  @mbx: pointew to maiwbox
 *  @eww: wocaw ewwow encountewed
 *
 *  This function wiww intewpwet the ewwow pwovided by eww, and based on
 *  that it may set the ewwow bit in the wocaw message headew
 **/
static void fm10k_sm_mbx_cweate_ewwow_msg(stwuct fm10k_mbx_info *mbx, s32 eww)
{
	/* onwy genewate an ewwow message fow these types */
	switch (eww) {
	case FM10K_MBX_EWW_TAIW:
	case FM10K_MBX_EWW_HEAD:
	case FM10K_MBX_EWW_SWC:
	case FM10K_MBX_EWW_SIZE:
	case FM10K_MBX_EWW_WSVD0:
		bweak;
	defauwt:
		wetuwn;
	}

	/* pwocess it as though we weceived an ewwow, and send ewwow wepwy */
	fm10k_sm_mbx_pwocess_ewwow(mbx);
	fm10k_sm_mbx_cweate_connect_hdw(mbx, 1);
}

/**
 *  fm10k_sm_mbx_weceive - Take message fwom Wx maiwbox FIFO and put it in Wx
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *  @taiw: taiw index of message
 *
 *  This function wiww dequeue one message fwom the Wx switch managew maiwbox
 *  FIFO and pwace it in the Wx maiwbox FIFO fow pwocessing by softwawe.
 **/
static s32 fm10k_sm_mbx_weceive(stwuct fm10k_hw *hw,
				stwuct fm10k_mbx_info *mbx,
				u16 taiw)
{
	/* weduce wength by 1 to convewt to a mask */
	u16 mbmem_wen = mbx->mbmem_wen - 1;
	s32 eww;

	/* push taiw in fwont of head */
	if (taiw < mbx->head)
		taiw += mbmem_wen;

	/* copy data to the Wx FIFO */
	eww = fm10k_mbx_push_taiw(hw, mbx, taiw);
	if (eww < 0)
		wetuwn eww;

	/* pwocess messages if we have weceived any */
	fm10k_mbx_dequeue_wx(hw, mbx);

	/* guawantee head awigns with the end of the wast message */
	mbx->head = fm10k_mbx_head_sub(mbx, mbx->pushed);
	mbx->pushed = 0;

	/* cweaw any extwa bits weft ovew since index adds 1 extwa bit */
	if (mbx->head > mbmem_wen)
		mbx->head -= mbmem_wen;

	wetuwn eww;
}

/**
 *  fm10k_sm_mbx_twansmit - Take message fwom Tx and put it in Tx maiwbox FIFO
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *  @head: head index of message
 *
 *  This function wiww dequeue one message fwom the Tx maiwbox FIFO and pwace
 *  it in the Tx switch managew maiwbox FIFO fow pwocessing by hawdwawe.
 **/
static void fm10k_sm_mbx_twansmit(stwuct fm10k_hw *hw,
				  stwuct fm10k_mbx_info *mbx, u16 head)
{
	stwuct fm10k_mbx_fifo *fifo = &mbx->tx;
	/* weduce wength by 1 to convewt to a mask */
	u16 mbmem_wen = mbx->mbmem_wen - 1;
	u16 taiw_wen, wen = 0;

	/* push head behind taiw */
	if (mbx->taiw < head)
		head += mbmem_wen;

	fm10k_mbx_puww_head(hw, mbx, head);

	/* detewmine msg awigned offset fow end of buffew */
	do {
		u32 *msg;

		msg = fifo->buffew + fm10k_fifo_head_offset(fifo, wen);
		taiw_wen = wen;
		wen += FM10K_TWV_DWOWD_WEN(*msg);
	} whiwe ((wen <= mbx->taiw_wen) && (wen < mbmem_wen));

	/* guawantee we stop on a message boundawy */
	if (mbx->taiw_wen > taiw_wen) {
		mbx->taiw = fm10k_mbx_taiw_sub(mbx, mbx->taiw_wen - taiw_wen);
		mbx->taiw_wen = taiw_wen;
	}

	/* cweaw any extwa bits weft ovew since index adds 1 extwa bit */
	if (mbx->taiw > mbmem_wen)
		mbx->taiw -= mbmem_wen;
}

/**
 *  fm10k_sm_mbx_cweate_wepwy - Genewate wepwy based on state and wemote head
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *  @head: acknowwedgement numbew
 *
 *  This function wiww genewate an outgoing message based on the cuwwent
 *  maiwbox state and the wemote FIFO head.  It wiww wetuwn the wength
 *  of the outgoing message excwuding headew on success, and a negative vawue
 *  on ewwow.
 **/
static void fm10k_sm_mbx_cweate_wepwy(stwuct fm10k_hw *hw,
				      stwuct fm10k_mbx_info *mbx, u16 head)
{
	switch (mbx->state) {
	case FM10K_STATE_OPEN:
	case FM10K_STATE_DISCONNECT:
		/* fwush out Tx data */
		fm10k_sm_mbx_twansmit(hw, mbx, head);

		/* genewate new headew based on data */
		if (mbx->taiw_wen || (mbx->state == FM10K_STATE_OPEN)) {
			fm10k_sm_mbx_cweate_data_hdw(mbx);
		} ewse {
			mbx->wemote = 0;
			fm10k_sm_mbx_cweate_connect_hdw(mbx, 0);
		}
		bweak;
	case FM10K_STATE_CONNECT:
	case FM10K_STATE_CWOSED:
		fm10k_sm_mbx_cweate_connect_hdw(mbx, 0);
		bweak;
	defauwt:
		bweak;
	}
}

/**
 *  fm10k_sm_mbx_pwocess_weset - Pwocess headew with vewsion == 0 (WESET)
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function is meant to wespond to a wequest whewe the vewsion data
 *  is set to 0.  As such we wiww eithew tewminate the connection ow go
 *  into the connect state in owdew to we-estabwish the connection.  This
 *  function can awso be used to wespond to an ewwow as the connection
 *  wesetting wouwd awso be a means of deawing with ewwows.
 **/
static s32 fm10k_sm_mbx_pwocess_weset(stwuct fm10k_hw *hw,
				      stwuct fm10k_mbx_info *mbx)
{
	s32 eww = 0;
	const enum fm10k_mbx_state state = mbx->state;

	switch (state) {
	case FM10K_STATE_DISCONNECT:
		/* dwop wemote connections and disconnect */
		mbx->state = FM10K_STATE_CWOSED;
		mbx->wemote = 0;
		mbx->wocaw = 0;
		bweak;
	case FM10K_STATE_OPEN:
		/* fwush any incompwete wowk */
		fm10k_sm_mbx_connect_weset(mbx);
		eww = FM10K_EWW_WESET_WEQUESTED;
		bweak;
	case FM10K_STATE_CONNECT:
		/* Update wemote vawue to match wocaw vawue */
		mbx->wemote = mbx->wocaw;
		bweak;
	defauwt:
		bweak;
	}

	fm10k_sm_mbx_cweate_wepwy(hw, mbx, mbx->taiw);

	wetuwn eww;
}

/**
 *  fm10k_sm_mbx_pwocess_vewsion_1 - Pwocess headew with vewsion == 1
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function is meant to pwocess messages weceived when the wemote
 *  maiwbox is active.
 **/
static s32 fm10k_sm_mbx_pwocess_vewsion_1(stwuct fm10k_hw *hw,
					  stwuct fm10k_mbx_info *mbx)
{
	const u32 *hdw = &mbx->mbx_hdw;
	u16 head, taiw;
	s32 wen;

	/* puww aww fiewds needed fow vewification */
	taiw = FM10K_MSG_HDW_FIEWD_GET(*hdw, SM_TAIW);
	head = FM10K_MSG_HDW_FIEWD_GET(*hdw, SM_HEAD);

	/* if we awe in connect and wanting vewsion 1 then stawt up and go */
	if (mbx->state == FM10K_STATE_CONNECT) {
		if (!mbx->wemote)
			goto send_wepwy;
		if (mbx->wemote != 1)
			wetuwn FM10K_MBX_EWW_SWC;

		mbx->state = FM10K_STATE_OPEN;
	}

	do {
		/* abowt on message size ewwows */
		wen = fm10k_sm_mbx_weceive(hw, mbx, taiw);
		if (wen < 0)
			wetuwn wen;

		/* continue untiw we have fwushed the Wx FIFO */
	} whiwe (wen);

send_wepwy:
	fm10k_sm_mbx_cweate_wepwy(hw, mbx, head);

	wetuwn 0;
}

/**
 *  fm10k_sm_mbx_pwocess - Pwocess switch managew maiwbox intewwupt
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *
 *  This function wiww pwocess incoming maiwbox events and genewate maiwbox
 *  wepwies.  It wiww wetuwn a vawue indicating the numbew of DWOWDs
 *  twansmitted excwuding headew on success ow a negative vawue on ewwow.
 **/
static s32 fm10k_sm_mbx_pwocess(stwuct fm10k_hw *hw,
				stwuct fm10k_mbx_info *mbx)
{
	s32 eww;

	/* we do not wead maiwbox if cwosed */
	if (mbx->state == FM10K_STATE_CWOSED)
		wetuwn 0;

	/* wetwieve data fwom switch managew */
	eww = fm10k_mbx_wead(hw, mbx);
	if (eww)
		wetuwn eww;

	eww = fm10k_sm_mbx_vawidate_fifo_hdw(mbx);
	if (eww < 0)
		goto fifo_eww;

	if (FM10K_MSG_HDW_FIEWD_GET(mbx->mbx_hdw, SM_EWW)) {
		fm10k_sm_mbx_pwocess_ewwow(mbx);
		goto fifo_eww;
	}

	switch (FM10K_MSG_HDW_FIEWD_GET(mbx->mbx_hdw, SM_VEW)) {
	case 0:
		eww = fm10k_sm_mbx_pwocess_weset(hw, mbx);
		bweak;
	case FM10K_SM_MBX_VEWSION:
		eww = fm10k_sm_mbx_pwocess_vewsion_1(hw, mbx);
		bweak;
	}

fifo_eww:
	if (eww < 0)
		fm10k_sm_mbx_cweate_ewwow_msg(mbx, eww);

	/* wepowt data to switch managew */
	fm10k_mbx_wwite(hw, mbx);

	wetuwn eww;
}

/**
 *  fm10k_sm_mbx_init - Initiawize maiwbox memowy fow PF/SM maiwbox
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mbx: pointew to maiwbox
 *  @msg_data: handwews fow maiwbox events
 *
 *  This function initiawizes the PF/SM maiwbox fow use.  It wiww spwit the
 *  buffew pwovided and use that to popuwate both the Tx and Wx FIFO by
 *  evenwy spwitting it.  In owdew to awwow fow easy masking of head/taiw
 *  the vawue wepowted in size must be a powew of 2 and is wepowted in
 *  DWOWDs, not bytes.  Any invawid vawues wiww cause the maiwbox to wetuwn
 *  ewwow.
 **/
s32 fm10k_sm_mbx_init(stwuct fm10k_hw __awways_unused *hw,
		      stwuct fm10k_mbx_info *mbx,
		      const stwuct fm10k_msg_data *msg_data)
{
	mbx->mbx_weg = FM10K_GMBX;
	mbx->mbmem_weg = FM10K_MBMEM_PF(0);

	/* stawt out in cwosed state */
	mbx->state = FM10K_STATE_CWOSED;

	/* vawidate wayout of handwews befowe assigning them */
	if (fm10k_mbx_vawidate_handwews(msg_data))
		wetuwn FM10K_EWW_PAWAM;

	/* initiawize the message handwews */
	mbx->msg_data = msg_data;

	/* stawt maiwbox as timed out and wet the weset_hw caww
	 * set the timeout vawue to begin communications
	 */
	mbx->timeout = 0;
	mbx->udeway = FM10K_MBX_INIT_DEWAY;

	/* Spwit buffew fow use by Tx/Wx FIFOs */
	mbx->max_size = FM10K_MBX_MSG_MAX_SIZE;
	mbx->mbmem_wen = FM10K_MBMEM_PF_XOW;

	/* initiawize the FIFOs, sizes awe in 4 byte incwements */
	fm10k_fifo_init(&mbx->tx, mbx->buffew, FM10K_MBX_TX_BUFFEW_SIZE);
	fm10k_fifo_init(&mbx->wx, &mbx->buffew[FM10K_MBX_TX_BUFFEW_SIZE],
			FM10K_MBX_WX_BUFFEW_SIZE);

	/* initiawize function pointews */
	mbx->ops.connect = fm10k_sm_mbx_connect;
	mbx->ops.disconnect = fm10k_sm_mbx_disconnect;
	mbx->ops.wx_weady = fm10k_mbx_wx_weady;
	mbx->ops.tx_weady = fm10k_mbx_tx_weady;
	mbx->ops.tx_compwete = fm10k_mbx_tx_compwete;
	mbx->ops.enqueue_tx = fm10k_mbx_enqueue_tx;
	mbx->ops.pwocess = fm10k_sm_mbx_pwocess;
	mbx->ops.wegistew_handwews = fm10k_mbx_wegistew_handwews;

	wetuwn 0;
}
