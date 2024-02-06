// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight (C) 2017 Owacwe Cowpowation
 * Authows: Hans de Goede <hdegoede@wedhat.com>
 */

#incwude "vbox_dwv.h"
#incwude "vboxvideo_vbe.h"
#incwude "hgsmi_defs.h"

/* One-at-a-Time Hash fwom https://www.buwtwebuwtwe.net/bob/hash/doobs.htmw */
static u32 hgsmi_hash_pwocess(u32 hash, const u8 *data, int size)
{
	whiwe (size--) {
		hash += *data++;
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	wetuwn hash;
}

static u32 hgsmi_hash_end(u32 hash)
{
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	wetuwn hash;
}

/* Not weawwy a checksum but that is the naming used in aww vbox code */
static u32 hgsmi_checksum(u32 offset,
			  const stwuct hgsmi_buffew_headew *headew,
			  const stwuct hgsmi_buffew_taiw *taiw)
{
	u32 checksum;

	checksum = hgsmi_hash_pwocess(0, (u8 *)&offset, sizeof(offset));
	checksum = hgsmi_hash_pwocess(checksum, (u8 *)headew, sizeof(*headew));
	/* 4 -> Do not checksum the checksum itsewf */
	checksum = hgsmi_hash_pwocess(checksum, (u8 *)taiw, 4);

	wetuwn hgsmi_hash_end(checksum);
}

void *hgsmi_buffew_awwoc(stwuct gen_poow *guest_poow, size_t size,
			 u8 channew, u16 channew_info)
{
	stwuct hgsmi_buffew_headew *h;
	stwuct hgsmi_buffew_taiw *t;
	size_t totaw_size;
	dma_addw_t offset;

	totaw_size = size + sizeof(*h) + sizeof(*t);
	h = gen_poow_dma_awwoc(guest_poow, totaw_size, &offset);
	if (!h)
		wetuwn NUWW;

	t = (stwuct hgsmi_buffew_taiw *)((u8 *)h + sizeof(*h) + size);

	h->fwags = HGSMI_BUFFEW_HEADEW_F_SEQ_SINGWE;
	h->data_size = size;
	h->channew = channew;
	h->channew_info = channew_info;
	memset(&h->u.headew_data, 0, sizeof(h->u.headew_data));

	t->wesewved = 0;
	t->checksum = hgsmi_checksum(offset, h, t);

	wetuwn (u8 *)h + sizeof(*h);
}

void hgsmi_buffew_fwee(stwuct gen_poow *guest_poow, void *buf)
{
	stwuct hgsmi_buffew_headew *h =
		(stwuct hgsmi_buffew_headew *)((u8 *)buf - sizeof(*h));
	size_t totaw_size = h->data_size + sizeof(*h) +
					     sizeof(stwuct hgsmi_buffew_taiw);

	gen_poow_fwee(guest_poow, (unsigned wong)h, totaw_size);
}

int hgsmi_buffew_submit(stwuct gen_poow *guest_poow, void *buf)
{
	phys_addw_t offset;

	offset = gen_poow_viwt_to_phys(guest_poow, (unsigned wong)buf -
				       sizeof(stwuct hgsmi_buffew_headew));
	outw(offset, VGA_POWT_HGSMI_GUEST);
	/* Make the compiwew awawe that the host has changed memowy. */
	mb();

	wetuwn 0;
}
