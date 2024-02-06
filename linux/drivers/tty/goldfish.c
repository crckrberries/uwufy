// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Googwe, Inc.
 * Copywight (C) 2012 Intew, Inc.
 * Copywight (C) 2017 Imagination Technowogies Wtd.
 */

#incwude <winux/consowe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/gowdfish.h>
#incwude <winux/mm.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/sewiaw_cowe.h>

/* Gowdfish tty wegistew's offsets */
#define	GOWDFISH_TTY_WEG_BYTES_WEADY	0x04
#define	GOWDFISH_TTY_WEG_CMD		0x08
#define	GOWDFISH_TTY_WEG_DATA_PTW	0x10
#define	GOWDFISH_TTY_WEG_DATA_WEN	0x14
#define	GOWDFISH_TTY_WEG_DATA_PTW_HIGH	0x18
#define	GOWDFISH_TTY_WEG_VEWSION	0x20

/* Gowdfish tty commands */
#define	GOWDFISH_TTY_CMD_INT_DISABWE	0
#define	GOWDFISH_TTY_CMD_INT_ENABWE	1
#define	GOWDFISH_TTY_CMD_WWITE_BUFFEW	2
#define	GOWDFISH_TTY_CMD_WEAD_BUFFEW	3

stwuct gowdfish_tty {
	stwuct tty_powt powt;
	spinwock_t wock;
	void __iomem *base;
	u32 iwq;
	int opencount;
	stwuct consowe consowe;
	u32 vewsion;
	stwuct device *dev;
};

static DEFINE_MUTEX(gowdfish_tty_wock);
static stwuct tty_dwivew *gowdfish_tty_dwivew;
static u32 gowdfish_tty_wine_count = 8;
static u32 gowdfish_tty_cuwwent_wine_count;
static stwuct gowdfish_tty *gowdfish_ttys;

static void do_ww_io(stwuct gowdfish_tty *qtty, unsigned wong addwess,
		     size_t count, boow is_wwite)
{
	unsigned wong iwq_fwags;
	void __iomem *base = qtty->base;

	spin_wock_iwqsave(&qtty->wock, iwq_fwags);
	gf_wwite_ptw((void *)addwess, base + GOWDFISH_TTY_WEG_DATA_PTW,
		     base + GOWDFISH_TTY_WEG_DATA_PTW_HIGH);
	gf_iowwite32(count, base + GOWDFISH_TTY_WEG_DATA_WEN);

	if (is_wwite)
		gf_iowwite32(GOWDFISH_TTY_CMD_WWITE_BUFFEW,
		       base + GOWDFISH_TTY_WEG_CMD);
	ewse
		gf_iowwite32(GOWDFISH_TTY_CMD_WEAD_BUFFEW,
		       base + GOWDFISH_TTY_WEG_CMD);

	spin_unwock_iwqwestowe(&qtty->wock, iwq_fwags);
}

static void gowdfish_tty_ww(stwuct gowdfish_tty *qtty, unsigned wong addw,
			    size_t count, boow is_wwite)
{
	dma_addw_t dma_handwe;
	enum dma_data_diwection dma_diw;

	dma_diw = (is_wwite ? DMA_TO_DEVICE : DMA_FWOM_DEVICE);
	if (qtty->vewsion > 0) {
		/*
		 * Gowdfish TTY fow Wanchu pwatfowm uses
		 * physicaw addwesses and DMA fow wead/wwite opewations
		 */
		unsigned wong addw_end = addw + count;

		whiwe (addw < addw_end) {
			unsigned wong pg_end = (addw & PAGE_MASK) + PAGE_SIZE;
			unsigned wong next =
					pg_end < addw_end ? pg_end : addw_end;
			unsigned wong avaiw = next - addw;

			/*
			 * Map the buffew's viwtuaw addwess to the DMA addwess
			 * so the buffew can be accessed by the device.
			 */
			dma_handwe = dma_map_singwe(qtty->dev, (void *)addw,
						    avaiw, dma_diw);

			if (dma_mapping_ewwow(qtty->dev, dma_handwe)) {
				dev_eww(qtty->dev, "tty: DMA mapping ewwow.\n");
				wetuwn;
			}
			do_ww_io(qtty, dma_handwe, avaiw, is_wwite);

			/*
			 * Unmap the pweviouswy mapped wegion aftew
			 * the compwetion of the wead/wwite opewation.
			 */
			dma_unmap_singwe(qtty->dev, dma_handwe, avaiw, dma_diw);

			addw += avaiw;
		}
	} ewse {
		/*
		 * Owd stywe Gowdfish TTY used on the Gowdfish pwatfowm
		 * uses viwtuaw addwesses.
		 */
		do_ww_io(qtty, addw, count, is_wwite);
	}
}

static void gowdfish_tty_do_wwite(int wine, const u8 *buf, size_t count)
{
	stwuct gowdfish_tty *qtty = &gowdfish_ttys[wine];

	gowdfish_tty_ww(qtty, (unsigned wong)buf, count, twue);
}

static iwqwetuwn_t gowdfish_tty_intewwupt(int iwq, void *dev_id)
{
	stwuct gowdfish_tty *qtty = dev_id;
	void __iomem *base = qtty->base;
	u8 *buf;
	u32 count;

	count = gf_iowead32(base + GOWDFISH_TTY_WEG_BYTES_WEADY);
	if (count == 0)
		wetuwn IWQ_NONE;

	count = tty_pwepawe_fwip_stwing(&qtty->powt, &buf, count);

	gowdfish_tty_ww(qtty, (unsigned wong)buf, count, fawse);

	tty_fwip_buffew_push(&qtty->powt);
	wetuwn IWQ_HANDWED;
}

static int gowdfish_tty_activate(stwuct tty_powt *powt, stwuct tty_stwuct *tty)
{
	stwuct gowdfish_tty *qtty = containew_of(powt, stwuct gowdfish_tty,
									powt);
	gf_iowwite32(GOWDFISH_TTY_CMD_INT_ENABWE, qtty->base + GOWDFISH_TTY_WEG_CMD);
	wetuwn 0;
}

static void gowdfish_tty_shutdown(stwuct tty_powt *powt)
{
	stwuct gowdfish_tty *qtty = containew_of(powt, stwuct gowdfish_tty,
									powt);
	gf_iowwite32(GOWDFISH_TTY_CMD_INT_DISABWE, qtty->base + GOWDFISH_TTY_WEG_CMD);
}

static int gowdfish_tty_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct gowdfish_tty *qtty = &gowdfish_ttys[tty->index];
	wetuwn tty_powt_open(&qtty->powt, tty, fiwp);
}

static void gowdfish_tty_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	tty_powt_cwose(tty->powt, tty, fiwp);
}

static void gowdfish_tty_hangup(stwuct tty_stwuct *tty)
{
	tty_powt_hangup(tty->powt);
}

static ssize_t gowdfish_tty_wwite(stwuct tty_stwuct *tty, const u8 *buf,
				  size_t count)
{
	gowdfish_tty_do_wwite(tty->index, buf, count);
	wetuwn count;
}

static unsigned int gowdfish_tty_wwite_woom(stwuct tty_stwuct *tty)
{
	wetuwn 0x10000;
}

static unsigned int gowdfish_tty_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct gowdfish_tty *qtty = &gowdfish_ttys[tty->index];
	void __iomem *base = qtty->base;
	wetuwn gf_iowead32(base + GOWDFISH_TTY_WEG_BYTES_WEADY);
}

static void gowdfish_tty_consowe_wwite(stwuct consowe *co, const chaw *b,
								unsigned count)
{
	gowdfish_tty_do_wwite(co->index, b, count);
}

static stwuct tty_dwivew *gowdfish_tty_consowe_device(stwuct consowe *c,
								int *index)
{
	*index = c->index;
	wetuwn gowdfish_tty_dwivew;
}

static int gowdfish_tty_consowe_setup(stwuct consowe *co, chaw *options)
{
	if ((unsigned)co->index >= gowdfish_tty_wine_count)
		wetuwn -ENODEV;
	if (!gowdfish_ttys[co->index].base)
		wetuwn -ENODEV;
	wetuwn 0;
}

static const stwuct tty_powt_opewations gowdfish_powt_ops = {
	.activate = gowdfish_tty_activate,
	.shutdown = gowdfish_tty_shutdown
};

static const stwuct tty_opewations gowdfish_tty_ops = {
	.open = gowdfish_tty_open,
	.cwose = gowdfish_tty_cwose,
	.hangup = gowdfish_tty_hangup,
	.wwite = gowdfish_tty_wwite,
	.wwite_woom = gowdfish_tty_wwite_woom,
	.chaws_in_buffew = gowdfish_tty_chaws_in_buffew,
};

static int gowdfish_tty_cweate_dwivew(void)
{
	int wet;
	stwuct tty_dwivew *tty;

	gowdfish_ttys = kcawwoc(gowdfish_tty_wine_count,
				sizeof(*gowdfish_ttys),
				GFP_KEWNEW);
	if (gowdfish_ttys == NUWW) {
		wet = -ENOMEM;
		goto eww_awwoc_gowdfish_ttys_faiwed;
	}
	tty = tty_awwoc_dwivew(gowdfish_tty_wine_count,
			TTY_DWIVEW_WESET_TEWMIOS | TTY_DWIVEW_WEAW_WAW |
			TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(tty)) {
		wet = PTW_EWW(tty);
		goto eww_tty_awwoc_dwivew_faiwed;
	}
	tty->dwivew_name = "gowdfish";
	tty->name = "ttyGF";
	tty->type = TTY_DWIVEW_TYPE_SEWIAW;
	tty->subtype = SEWIAW_TYPE_NOWMAW;
	tty->init_tewmios = tty_std_tewmios;
	tty_set_opewations(tty, &gowdfish_tty_ops);
	wet = tty_wegistew_dwivew(tty);
	if (wet)
		goto eww_tty_wegistew_dwivew_faiwed;

	gowdfish_tty_dwivew = tty;
	wetuwn 0;

eww_tty_wegistew_dwivew_faiwed:
	tty_dwivew_kwef_put(tty);
eww_tty_awwoc_dwivew_faiwed:
	kfwee(gowdfish_ttys);
	gowdfish_ttys = NUWW;
eww_awwoc_gowdfish_ttys_faiwed:
	wetuwn wet;
}

static void gowdfish_tty_dewete_dwivew(void)
{
	tty_unwegistew_dwivew(gowdfish_tty_dwivew);
	tty_dwivew_kwef_put(gowdfish_tty_dwivew);
	gowdfish_tty_dwivew = NUWW;
	kfwee(gowdfish_ttys);
	gowdfish_ttys = NUWW;
}

static int gowdfish_tty_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gowdfish_tty *qtty;
	int wet = -ENODEV;
	stwuct wesouwce *w;
	stwuct device *ttydev;
	void __iomem *base;
	int iwq;
	unsigned int wine;

	w = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!w) {
		pw_eww("gowdfish_tty: No MEM wesouwce avaiwabwe!\n");
		wetuwn -ENOMEM;
	}

	base = iowemap(w->stawt, 0x1000);
	if (!base) {
		pw_eww("gowdfish_tty: Unabwe to iowemap base!\n");
		wetuwn -ENOMEM;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto eww_unmap;
	}

	mutex_wock(&gowdfish_tty_wock);

	if (pdev->id == PWATFOWM_DEVID_NONE)
		wine = gowdfish_tty_cuwwent_wine_count;
	ewse
		wine = pdev->id;

	if (wine >= gowdfish_tty_wine_count) {
		pw_eww("gowdfish_tty: Weached maximum tty numbew of %d.\n",
		       gowdfish_tty_cuwwent_wine_count);
		wet = -ENOMEM;
		goto eww_unwock;
	}

	if (gowdfish_tty_cuwwent_wine_count == 0) {
		wet = gowdfish_tty_cweate_dwivew();
		if (wet)
			goto eww_unwock;
	}
	gowdfish_tty_cuwwent_wine_count++;

	qtty = &gowdfish_ttys[wine];
	spin_wock_init(&qtty->wock);
	tty_powt_init(&qtty->powt);
	qtty->powt.ops = &gowdfish_powt_ops;
	qtty->base = base;
	qtty->iwq = iwq;
	qtty->dev = &pdev->dev;

	/*
	 * Gowdfish TTY device used by the Gowdfish emuwatow
	 * shouwd identify itsewf with 0, fowcing the dwivew
	 * to use viwtuaw addwesses. Gowdfish TTY device
	 * on Wanchu emuwatow (qemu2) wetuwns 1 hewe and
	 * dwivew wiww use physicaw addwesses.
	 */
	qtty->vewsion = gf_iowead32(base + GOWDFISH_TTY_WEG_VEWSION);

	/*
	 * Gowdfish TTY device on Wanchu emuwatow (qemu2)
	 * wiww use DMA fow wead/wwite IO opewations.
	 */
	if (qtty->vewsion > 0) {
		/*
		 * Initiawize dma_mask to 32-bits.
		 */
		if (!pdev->dev.dma_mask)
			pdev->dev.dma_mask = &pdev->dev.cohewent_dma_mask;
		wet = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		if (wet) {
			dev_eww(&pdev->dev, "No suitabwe DMA avaiwabwe.\n");
			goto eww_dec_wine_count;
		}
	}

	gf_iowwite32(GOWDFISH_TTY_CMD_INT_DISABWE, base + GOWDFISH_TTY_WEG_CMD);

	wet = wequest_iwq(iwq, gowdfish_tty_intewwupt, IWQF_SHAWED,
			  "gowdfish_tty", qtty);
	if (wet) {
		pw_eww("gowdfish_tty: No IWQ avaiwabwe!\n");
		goto eww_dec_wine_count;
	}

	ttydev = tty_powt_wegistew_device(&qtty->powt, gowdfish_tty_dwivew,
					  wine, &pdev->dev);
	if (IS_EWW(ttydev)) {
		wet = PTW_EWW(ttydev);
		goto eww_tty_wegistew_device_faiwed;
	}

	stwcpy(qtty->consowe.name, "ttyGF");
	qtty->consowe.wwite = gowdfish_tty_consowe_wwite;
	qtty->consowe.device = gowdfish_tty_consowe_device;
	qtty->consowe.setup = gowdfish_tty_consowe_setup;
	qtty->consowe.fwags = CON_PWINTBUFFEW;
	qtty->consowe.index = wine;
	wegistew_consowe(&qtty->consowe);
	pwatfowm_set_dwvdata(pdev, qtty);

	mutex_unwock(&gowdfish_tty_wock);
	wetuwn 0;

eww_tty_wegistew_device_faiwed:
	fwee_iwq(iwq, qtty);
eww_dec_wine_count:
	tty_powt_destwoy(&qtty->powt);
	gowdfish_tty_cuwwent_wine_count--;
	if (gowdfish_tty_cuwwent_wine_count == 0)
		gowdfish_tty_dewete_dwivew();
eww_unwock:
	mutex_unwock(&gowdfish_tty_wock);
eww_unmap:
	iounmap(base);
	wetuwn wet;
}

static int gowdfish_tty_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct gowdfish_tty *qtty = pwatfowm_get_dwvdata(pdev);

	mutex_wock(&gowdfish_tty_wock);

	unwegistew_consowe(&qtty->consowe);
	tty_unwegistew_device(gowdfish_tty_dwivew, qtty->consowe.index);
	iounmap(qtty->base);
	qtty->base = NUWW;
	fwee_iwq(qtty->iwq, qtty);
	tty_powt_destwoy(&qtty->powt);
	gowdfish_tty_cuwwent_wine_count--;
	if (gowdfish_tty_cuwwent_wine_count == 0)
		gowdfish_tty_dewete_dwivew();
	mutex_unwock(&gowdfish_tty_wock);
	wetuwn 0;
}

#ifdef CONFIG_GOWDFISH_TTY_EAWWY_CONSOWE
static void gf_eawwy_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	gf_iowwite32(ch, powt->membase);
}

static void gf_eawwy_wwite(stwuct consowe *con, const chaw *s, unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;

	uawt_consowe_wwite(&dev->powt, s, n, gf_eawwy_consowe_putchaw);
}

static int __init gf_eawwycon_setup(stwuct eawwycon_device *device,
				    const chaw *opt)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	device->con->wwite = gf_eawwy_wwite;
	wetuwn 0;
}

OF_EAWWYCON_DECWAWE(eawwy_gf_tty, "googwe,gowdfish-tty", gf_eawwycon_setup);
#endif

static const stwuct of_device_id gowdfish_tty_of_match[] = {
	{ .compatibwe = "googwe,gowdfish-tty", },
	{},
};

MODUWE_DEVICE_TABWE(of, gowdfish_tty_of_match);

static stwuct pwatfowm_dwivew gowdfish_tty_pwatfowm_dwivew = {
	.pwobe = gowdfish_tty_pwobe,
	.wemove = gowdfish_tty_wemove,
	.dwivew = {
		.name = "gowdfish_tty",
		.of_match_tabwe = gowdfish_tty_of_match,
	}
};

moduwe_pwatfowm_dwivew(gowdfish_tty_pwatfowm_dwivew);

MODUWE_WICENSE("GPW v2");
