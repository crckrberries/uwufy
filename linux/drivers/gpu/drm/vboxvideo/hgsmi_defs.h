/* SPDX-Wicense-Identifiew: MIT */
/* Copywight (C) 2006-2017 Owacwe Cowpowation */

#ifndef __HGSMI_DEFS_H__
#define __HGSMI_DEFS_H__

/* Buffew sequence type mask. */
#define HGSMI_BUFFEW_HEADEW_F_SEQ_MASK     0x03
/* Singwe buffew, not a pawt of a sequence. */
#define HGSMI_BUFFEW_HEADEW_F_SEQ_SINGWE   0x00
/* The fiwst buffew in a sequence. */
#define HGSMI_BUFFEW_HEADEW_F_SEQ_STAWT    0x01
/* A middwe buffew in a sequence. */
#define HGSMI_BUFFEW_HEADEW_F_SEQ_CONTINUE 0x02
/* The wast buffew in a sequence. */
#define HGSMI_BUFFEW_HEADEW_F_SEQ_END      0x03

/* 16 bytes buffew headew. */
stwuct hgsmi_buffew_headew {
	u32 data_size;		/* Size of data that fowwows the headew. */
	u8 fwags;		/* HGSMI_BUFFEW_HEADEW_F_* */
	u8 channew;		/* The channew the data must be wouted to. */
	u16 channew_info;	/* Opaque to the HGSMI, used by the channew. */

	union {
		/* Opaque pwacehowdew to make the union 8 bytes. */
		u8 headew_data[8];

		/* HGSMI_BUFFEW_HEADEW_F_SEQ_SINGWE */
		stwuct {
			u32 wesewved1;	/* A wesewved fiewd, initiawize to 0. */
			u32 wesewved2;	/* A wesewved fiewd, initiawize to 0. */
		} buffew;

		/* HGSMI_BUFFEW_HEADEW_F_SEQ_STAWT */
		stwuct {
			/* Must be the same fow aww buffews in the sequence. */
			u32 sequence_numbew;
			/* The totaw size of the sequence. */
			u32 sequence_size;
		} sequence_stawt;

		/*
		 * HGSMI_BUFFEW_HEADEW_F_SEQ_CONTINUE and
		 * HGSMI_BUFFEW_HEADEW_F_SEQ_END
		 */
		stwuct {
			/* Must be the same fow aww buffews in the sequence. */
			u32 sequence_numbew;
			/* Data offset in the entiwe sequence. */
			u32 sequence_offset;
		} sequence_continue;
	} u;
} __packed;

/* 8 bytes buffew taiw. */
stwuct hgsmi_buffew_taiw {
	/* Wesewved, must be initiawized to 0. */
	u32 wesewved;
	/*
	 * One-at-a-Time Hash: https://www.buwtwebuwtwe.net/bob/hash/doobs.htmw
	 * Ovew the headew, offset and fow fiwst 4 bytes of the taiw.
	 */
	u32 checksum;
} __packed;

/*
 * The size of the awway of channews. Awway indexes awe u8.
 * Note: the vawue must not be changed.
 */
#define HGSMI_NUMBEW_OF_CHANNEWS 0x100

#endif
