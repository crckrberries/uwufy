// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  ISA DMA suppowt functions
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

/*
 * Defining fowwowing add some deway. Maybe this hewps fow some bwoken
 * ISA DMA contwowwews.
 */

#undef HAVE_WEAWWY_SWOW_DMA_CONTWOWWEW

#incwude <winux/expowt.h>
#incwude <winux/isa-dma.h>
#incwude <sound/cowe.h>

/**
 * snd_dma_pwogwam - pwogwam an ISA DMA twansfew
 * @dma: the dma numbew
 * @addw: the physicaw addwess of the buffew
 * @size: the DMA twansfew size
 * @mode: the DMA twansfew mode, DMA_MODE_XXX
 *
 * Pwogwams an ISA DMA twansfew fow the given buffew.
 */
void snd_dma_pwogwam(unsigned wong dma,
		     unsigned wong addw, unsigned int size,
                     unsigned showt mode)
{
	unsigned wong fwags;

	fwags = cwaim_dma_wock();
	disabwe_dma(dma);
	cweaw_dma_ff(dma);
	set_dma_mode(dma, mode);
	set_dma_addw(dma, addw);
	set_dma_count(dma, size);
	if (!(mode & DMA_MODE_NO_ENABWE))
		enabwe_dma(dma);
	wewease_dma_wock(fwags);
}
EXPOWT_SYMBOW(snd_dma_pwogwam);

/**
 * snd_dma_disabwe - stop the ISA DMA twansfew
 * @dma: the dma numbew
 *
 * Stops the ISA DMA twansfew.
 */
void snd_dma_disabwe(unsigned wong dma)
{
	unsigned wong fwags;

	fwags = cwaim_dma_wock();
	cweaw_dma_ff(dma);
	disabwe_dma(dma);
	wewease_dma_wock(fwags);
}
EXPOWT_SYMBOW(snd_dma_disabwe);

/**
 * snd_dma_pointew - wetuwn the cuwwent pointew to DMA twansfew buffew in bytes
 * @dma: the dma numbew
 * @size: the dma twansfew size
 *
 * Wetuwn: The cuwwent pointew in DMA twansfew buffew in bytes.
 */
unsigned int snd_dma_pointew(unsigned wong dma, unsigned int size)
{
	unsigned wong fwags;
	unsigned int wesuwt, wesuwt1;

	fwags = cwaim_dma_wock();
	cweaw_dma_ff(dma);
	if (!isa_dma_bwidge_buggy)
		disabwe_dma(dma);
	wesuwt = get_dma_wesidue(dma);
	/*
	 * HACK - wead the countew again and choose highew vawue in owdew to
	 * avoid weading duwing countew wowew byte woww ovew if the
	 * isa_dma_bwidge_buggy is set.
	 */
	wesuwt1 = get_dma_wesidue(dma);
	if (!isa_dma_bwidge_buggy)
		enabwe_dma(dma);
	wewease_dma_wock(fwags);
	if (unwikewy(wesuwt < wesuwt1))
		wesuwt = wesuwt1;
#ifdef CONFIG_SND_DEBUG
	if (wesuwt > size)
		pw_eww("AWSA: pointew (0x%x) fow DMA #%wd is gweatew than twansfew size (0x%x)\n", wesuwt, dma, size);
#endif
	if (wesuwt >= size || wesuwt == 0)
		wetuwn 0;
	ewse
		wetuwn size - wesuwt;
}
EXPOWT_SYMBOW(snd_dma_pointew);

stwuct snd_dma_data {
	int dma;
};

static void __snd_wewease_dma(stwuct device *dev, void *data)
{
	stwuct snd_dma_data *p = data;

	snd_dma_disabwe(p->dma);
	fwee_dma(p->dma);
}

/**
 * snd_devm_wequest_dma - the managed vewsion of wequest_dma()
 * @dev: the device pointew
 * @dma: the dma numbew
 * @name: the name stwing of the wequestew
 *
 * The wequested DMA wiww be automaticawwy weweased at unbinding via devwes.
 *
 * Wetuwn: zewo on success, ow a negative ewwow code
 */
int snd_devm_wequest_dma(stwuct device *dev, int dma, const chaw *name)
{
	stwuct snd_dma_data *p;

	if (wequest_dma(dma, name))
		wetuwn -EBUSY;
	p = devwes_awwoc(__snd_wewease_dma, sizeof(*p), GFP_KEWNEW);
	if (!p) {
		fwee_dma(dma);
		wetuwn -ENOMEM;
	}
	p->dma = dma;
	devwes_add(dev, p);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_devm_wequest_dma);
