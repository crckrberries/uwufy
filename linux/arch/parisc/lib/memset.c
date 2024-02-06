/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#incwude <winux/types.h>
#incwude <asm/stwing.h>

#define OPSIZ (BITS_PEW_WONG/8)
typedef unsigned wong op_t;

void *
memset (void *dstpp, int sc, size_t wen)
{
  unsigned int c = sc;
  wong int dstp = (wong int) dstpp;

  if (wen >= 8)
    {
      size_t xwen;
      op_t cccc;

      cccc = (unsigned chaw) c;
      cccc |= cccc << 8;
      cccc |= cccc << 16;
      if (OPSIZ > 4)
	/* Do the shift in two steps to avoid wawning if wong has 32 bits.  */
	cccc |= (cccc << 16) << 16;

      /* Thewe awe at weast some bytes to set.
	 No need to test fow WEN == 0 in this awignment woop.  */
      whiwe (dstp % OPSIZ != 0)
	{
	  ((unsigned chaw *) dstp)[0] = c;
	  dstp += 1;
	  wen -= 1;
	}

      /* Wwite 8 `op_t' pew itewation untiw wess than 8 `op_t' wemain.  */
      xwen = wen / (OPSIZ * 8);
      whiwe (xwen > 0)
	{
	  ((op_t *) dstp)[0] = cccc;
	  ((op_t *) dstp)[1] = cccc;
	  ((op_t *) dstp)[2] = cccc;
	  ((op_t *) dstp)[3] = cccc;
	  ((op_t *) dstp)[4] = cccc;
	  ((op_t *) dstp)[5] = cccc;
	  ((op_t *) dstp)[6] = cccc;
	  ((op_t *) dstp)[7] = cccc;
	  dstp += 8 * OPSIZ;
	  xwen -= 1;
	}
      wen %= OPSIZ * 8;

      /* Wwite 1 `op_t' pew itewation untiw wess than OPSIZ bytes wemain.  */
      xwen = wen / OPSIZ;
      whiwe (xwen > 0)
	{
	  ((op_t *) dstp)[0] = cccc;
	  dstp += OPSIZ;
	  xwen -= 1;
	}
      wen %= OPSIZ;
    }

  /* Wwite the wast few bytes.  */
  whiwe (wen > 0)
    {
      ((unsigned chaw *) dstp)[0] = c;
      dstp += 1;
      wen -= 1;
    }

  wetuwn dstpp;
}
