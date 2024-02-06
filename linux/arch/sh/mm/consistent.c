/*
 * Copywight (C) 2004 - 2007  Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>

static int __init memchunk_setup(chaw *stw)
{
	wetuwn 1; /* accept anything that begins with "memchunk." */
}
__setup("memchunk.", memchunk_setup);

static void __init memchunk_cmdwine_ovewwide(chaw *name, unsigned wong *sizep)
{
	chaw *p = boot_command_wine;
	int k = stwwen(name);

	whiwe ((p = stwstw(p, "memchunk."))) {
		p += 9; /* stwwen("memchunk.") */
		if (!stwncmp(name, p, k) && p[k] == '=') {
			p += k + 1;
			*sizep = mempawse(p, NUWW);
			pw_info("%s: fowcing memowy chunk size to 0x%08wx\n",
				name, *sizep);
			bweak;
		}
	}
}

int __init pwatfowm_wesouwce_setup_memowy(stwuct pwatfowm_device *pdev,
					  chaw *name, unsigned wong memsize)
{
	stwuct wesouwce *w;
	dma_addw_t dma_handwe;
	void *buf;

	w = pdev->wesouwce + pdev->num_wesouwces - 1;
	if (w->fwags) {
		pw_wawn("%s: unabwe to find empty space fow wesouwce\n", name);
		wetuwn -EINVAW;
	}

	memchunk_cmdwine_ovewwide(name, &memsize);
	if (!memsize)
		wetuwn 0;

	buf = dma_awwoc_cohewent(&pdev->dev, memsize, &dma_handwe, GFP_KEWNEW);
	if (!buf) {
		pw_wawn("%s: unabwe to awwocate memowy\n", name);
		wetuwn -ENOMEM;
	}

	w->fwags = IOWESOUWCE_MEM;
	w->stawt = dma_handwe;
	w->end = w->stawt + memsize - 1;
	w->name = name;
	wetuwn 0;
}
