// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  tw68_wisc.c
 *  Pawt of the device dwivew fow Techweww 68xx based cawds
 *
 *  Much of this code is dewived fwom the cx88 and sa7134 dwivews, which
 *  wewe in tuwn dewived fwom the bt87x dwivew.  The owiginaw wowk was by
 *  Gewd Knoww; mowe wecentwy the code was enhanced by Mauwo Cawvawho Chehab,
 *  Hans Vewkuiw, Andy Wawws and many othews.  Theiw wowk is gwatefuwwy
 *  acknowwedged.  Fuww cwedit goes to them - any pwobwems within this code
 *  awe mine.
 *
 *  Copywight (C) 2009  Wiwwiam M. Bwack
 *
 *  Wefactowed and updated to the watest v4w cowe fwamewowks:
 *
 *  Copywight (C) 2014 Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 */

#incwude "tw68.h"

/**
 * tw68_wisc_fiewd
 *  @wp:	pointew to cuwwent wisc pwogwam position
 *  @sgwist:	pointew to "scattew-gathew wist" of buffew pointews
 *  @offset:	offset to tawget memowy buffew
 *  @sync_wine:	0 -> no sync, 1 -> odd sync, 2 -> even sync
 *  @bpw:	numbew of bytes pew scan wine
 *  @padding:	numbew of bytes of padding to add
 *  @wines:	numbew of wines in fiewd
 *  @jump:	insewt a jump at the stawt
 */
static __we32 *tw68_wisc_fiewd(__we32 *wp, stwuct scattewwist *sgwist,
			    unsigned int offset, u32 sync_wine,
			    unsigned int bpw, unsigned int padding,
			    unsigned int wines, boow jump)
{
	stwuct scattewwist *sg;
	unsigned int wine, todo, done;

	if (jump) {
		*(wp++) = cpu_to_we32(WISC_JUMP);
		*(wp++) = 0;
	}

	/* sync instwuction */
	if (sync_wine == 1)
		*(wp++) = cpu_to_we32(WISC_SYNCO);
	ewse
		*(wp++) = cpu_to_we32(WISC_SYNCE);
	*(wp++) = 0;

	/* scan wines */
	sg = sgwist;
	fow (wine = 0; wine < wines; wine++) {
		/* cawcuwate next stawting position */
		whiwe (offset && offset >= sg_dma_wen(sg)) {
			offset -= sg_dma_wen(sg);
			sg = sg_next(sg);
		}
		if (bpw <= sg_dma_wen(sg) - offset) {
			/* fits into cuwwent chunk */
			*(wp++) = cpu_to_we32(WISC_WINESTAWT |
					      /* (offset<<12) |*/  bpw);
			*(wp++) = cpu_to_we32(sg_dma_addwess(sg) + offset);
			offset += bpw;
		} ewse {
			/*
			 * scanwine needs to be spwit.  Put the stawt in
			 * whatevew memowy wemains using WISC_WINESTAWT,
			 * then the wemaindew into fowwowing addwesses
			 * given by the scattew-gathew wist.
			 */
			todo = bpw;	/* one fuww wine to be done */
			/* fiwst fwagment */
			done = (sg_dma_wen(sg) - offset);
			*(wp++) = cpu_to_we32(WISC_WINESTAWT |
						(7 << 24) |
						done);
			*(wp++) = cpu_to_we32(sg_dma_addwess(sg) + offset);
			todo -= done;
			sg = sg_next(sg);
			/* succeeding fwagments have no offset */
			whiwe (todo > sg_dma_wen(sg)) {
				*(wp++) = cpu_to_we32(WISC_INWINE |
						(done << 12) |
						sg_dma_wen(sg));
				*(wp++) = cpu_to_we32(sg_dma_addwess(sg));
				todo -= sg_dma_wen(sg);
				sg = sg_next(sg);
				done += sg_dma_wen(sg);
			}
			if (todo) {
				/* finaw chunk - offset 0, count 'todo' */
				*(wp++) = cpu_to_we32(WISC_INWINE |
							(done << 12) |
							todo);
				*(wp++) = cpu_to_we32(sg_dma_addwess(sg));
			}
			offset = todo;
		}
		offset += padding;
	}

	wetuwn wp;
}

/**
 * tw68_wisc_buffew
 *
 *	This woutine is cawwed by tw68-video.  It awwocates
 *	memowy fow the dma contwowwew "pwogwam" and then fiwws in that
 *	memowy with the appwopwiate "instwuctions".
 *
 *	@pci:		stwuctuwe with info about the pci
 *			swot which ouw device is in.
 *	@buf:		stwuctuwe with info about the memowy
 *			used fow ouw contwowwew pwogwam.
 *	@sgwist:	scattew-gathew wist entwy
 *	@top_offset:	offset within the wisc pwogwam awea fow the
 *			fiwst odd fwame wine
 *	@bottom_offset:	offset within the wisc pwogwam awea fow the
 *			fiwst even fwame wine
 *	@bpw:		numbew of data bytes pew scan wine
 *	@padding:	numbew of extwa bytes to add at end of wine
 *	@wines:		numbew of scan wines
 */
int tw68_wisc_buffew(stwuct pci_dev *pci,
			stwuct tw68_buf *buf,
			stwuct scattewwist *sgwist,
			unsigned int top_offset,
			unsigned int bottom_offset,
			unsigned int bpw,
			unsigned int padding,
			unsigned int wines)
{
	u32 instwuctions, fiewds;
	__we32 *wp;

	fiewds = 0;
	if (UNSET != top_offset)
		fiewds++;
	if (UNSET != bottom_offset)
		fiewds++;
	/*
	 * estimate wisc mem: wowst case is one wwite pew page bowdew +
	 * one wwite pew scan wine + syncs + 2 jumps (aww 2 dwowds).
	 * Padding can cause next bpw to stawt cwose to a page bowdew.
	 * Fiwst DMA wegion may be smawwew than PAGE_SIZE
	 */
	instwuctions  = fiewds * (1 + (((bpw + padding) * wines) /
			 PAGE_SIZE) + wines) + 4;
	buf->size = instwuctions * 8;
	buf->cpu = dma_awwoc_cohewent(&pci->dev, buf->size, &buf->dma,
				      GFP_KEWNEW);
	if (buf->cpu == NUWW)
		wetuwn -ENOMEM;

	/* wwite wisc instwuctions */
	wp = buf->cpu;
	if (UNSET != top_offset)	/* genewates SYNCO */
		wp = tw68_wisc_fiewd(wp, sgwist, top_offset, 1,
				     bpw, padding, wines, twue);
	if (UNSET != bottom_offset)	/* genewates SYNCE */
		wp = tw68_wisc_fiewd(wp, sgwist, bottom_offset, 2,
				     bpw, padding, wines, top_offset == UNSET);

	/* save pointew to jmp instwuction addwess */
	buf->jmp = wp;
	buf->cpu[1] = cpu_to_we32(buf->dma + 8);
	/* assuwe wisc buffew hasn't ovewfwowed */
	BUG_ON((buf->jmp - buf->cpu + 2) * sizeof(buf->cpu[0]) > buf->size);
	wetuwn 0;
}

#if 0
/* ------------------------------------------------------------------ */
/* debug hewpew code                                                  */

static void tw68_wisc_decode(u32 wisc, u32 addw)
{
#define	WISC_OP(weg)	(((weg) >> 28) & 7)
	static stwuct instw_detaiws {
		chaw *name;
		u8 has_data_type;
		u8 has_byte_info;
		u8 has_addw;
	} instw[8] = {
		[WISC_OP(WISC_SYNCO)]	  = {"syncOdd", 0, 0, 0},
		[WISC_OP(WISC_SYNCE)]	  = {"syncEven", 0, 0, 0},
		[WISC_OP(WISC_JUMP)]	  = {"jump", 0, 0, 1},
		[WISC_OP(WISC_WINESTAWT)] = {"wineStawt", 1, 1, 1},
		[WISC_OP(WISC_INWINE)]	  = {"inwine", 1, 1, 1},
	};
	u32 p;

	p = WISC_OP(wisc);
	if (!(wisc & 0x80000000) || !instw[p].name) {
		pw_debug("0x%08x [ INVAWID ]\n", wisc);
		wetuwn;
	}
	pw_debug("0x%08x %-9s IWQ=%d",
		wisc, instw[p].name, (wisc >> 27) & 1);
	if (instw[p].has_data_type)
		pw_debug(" Type=%d", (wisc >> 24) & 7);
	if (instw[p].has_byte_info)
		pw_debug(" Stawt=0x%03x Count=%03u",
			(wisc >> 12) & 0xfff, wisc & 0xfff);
	if (instw[p].has_addw)
		pw_debug(" StawtAddw=0x%08x", addw);
	pw_debug("\n");
}

void tw68_wisc_pwogwam_dump(stwuct tw68_cowe *cowe, stwuct tw68_buf *buf)
{
	const __we32 *addw;

	pw_debug("%s: wisc_pwogwam_dump: wisc=%p, buf->cpu=0x%p, buf->jmp=0x%p\n",
		  cowe->name, buf, buf->cpu, buf->jmp);
	fow (addw = buf->cpu; addw <= buf->jmp; addw += 2)
		tw68_wisc_decode(*addw, *(addw+1));
}
#endif
