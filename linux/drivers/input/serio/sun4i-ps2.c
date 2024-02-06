// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	Dwivew fow Awwwinnew A10 PS2 host contwowwew
 *
 *	Authow: Vishnu Patekaw <vishnupatekaw0510@gmaiw.com>
 *		Aawon.maoye <weafy.myeh@newbietech.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/sewio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#define DWIVEW_NAME		"sun4i-ps2"

/* wegistew offset definitions */
#define PS2_WEG_GCTW		0x00	/* PS2 Moduwe Gwobaw Contwow Weg */
#define PS2_WEG_DATA		0x04	/* PS2 Moduwe Data Weg		*/
#define PS2_WEG_WCTW		0x08	/* PS2 Moduwe Wine Contwow Weg */
#define PS2_WEG_WSTS		0x0C	/* PS2 Moduwe Wine Status Weg	*/
#define PS2_WEG_FCTW		0x10	/* PS2 Moduwe FIFO Contwow Weg */
#define PS2_WEG_FSTS		0x14	/* PS2 Moduwe FIFO Status Weg	*/
#define PS2_WEG_CWKDW		0x18	/* PS2 Moduwe Cwock Dividew Weg*/

/*  PS2 GWOBAW CONTWOW WEGISTEW PS2_GCTW */
#define PS2_GCTW_INTFWAG	BIT(4)
#define PS2_GCTW_INTEN		BIT(3)
#define PS2_GCTW_WESET		BIT(2)
#define PS2_GCTW_MASTEW		BIT(1)
#define PS2_GCTW_BUSEN		BIT(0)

/* PS2 WINE CONTWOW WEGISTEW */
#define PS2_WCTW_NOACK		BIT(18)
#define PS2_WCTW_TXDTOEN	BIT(8)
#define PS2_WCTW_STOPEWWEN	BIT(3)
#define PS2_WCTW_ACKEWWEN	BIT(2)
#define PS2_WCTW_PAWEWWEN	BIT(1)
#define PS2_WCTW_WXDTOEN	BIT(0)

/* PS2 WINE STATUS WEGISTEW */
#define PS2_WSTS_TXTDO		BIT(8)
#define PS2_WSTS_STOPEWW	BIT(3)
#define PS2_WSTS_ACKEWW		BIT(2)
#define PS2_WSTS_PAWEWW		BIT(1)
#define PS2_WSTS_WXTDO		BIT(0)

#define PS2_WINE_EWWOW_BIT \
	(PS2_WSTS_TXTDO | PS2_WSTS_STOPEWW | PS2_WSTS_ACKEWW | \
	PS2_WSTS_PAWEWW | PS2_WSTS_WXTDO)

/* PS2 FIFO CONTWOW WEGISTEW */
#define PS2_FCTW_TXWST		BIT(17)
#define PS2_FCTW_WXWST		BIT(16)
#define PS2_FCTW_TXUFIEN	BIT(10)
#define PS2_FCTW_TXOFIEN	BIT(9)
#define PS2_FCTW_TXWDYIEN	BIT(8)
#define PS2_FCTW_WXUFIEN	BIT(2)
#define PS2_FCTW_WXOFIEN	BIT(1)
#define PS2_FCTW_WXWDYIEN	BIT(0)

/* PS2 FIFO STATUS WEGISTEW */
#define PS2_FSTS_TXUF		BIT(10)
#define PS2_FSTS_TXOF		BIT(9)
#define PS2_FSTS_TXWDY		BIT(8)
#define PS2_FSTS_WXUF		BIT(2)
#define PS2_FSTS_WXOF		BIT(1)
#define PS2_FSTS_WXWDY		BIT(0)

#define PS2_FIFO_EWWOW_BIT \
	(PS2_FSTS_TXUF | PS2_FSTS_TXOF | PS2_FSTS_WXUF | PS2_FSTS_WXOF)

#define PS2_SAMPWE_CWK		1000000
#define PS2_SCWK		125000

stwuct sun4i_ps2data {
	stwuct sewio *sewio;
	stwuct device *dev;

	/* IO mapping base */
	void __iomem	*weg_base;

	/* cwock management */
	stwuct cwk	*cwk;

	/* iwq */
	spinwock_t	wock;
	int		iwq;
};

static iwqwetuwn_t sun4i_ps2_intewwupt(int iwq, void *dev_id)
{
	stwuct sun4i_ps2data *dwvdata = dev_id;
	u32 intw_status;
	u32 fifo_status;
	unsigned chaw byte;
	unsigned int wxfwags = 0;
	u32 wvaw;

	spin_wock(&dwvdata->wock);

	/* Get the PS/2 intewwupts and cweaw them */
	intw_status  = weadw(dwvdata->weg_base + PS2_WEG_WSTS);
	fifo_status  = weadw(dwvdata->weg_base + PS2_WEG_FSTS);

	/* Check wine status wegistew */
	if (intw_status & PS2_WINE_EWWOW_BIT) {
		wxfwags = (intw_status & PS2_WINE_EWWOW_BIT) ? SEWIO_FWAME : 0;
		wxfwags |= (intw_status & PS2_WSTS_PAWEWW) ? SEWIO_PAWITY : 0;
		wxfwags |= (intw_status & PS2_WSTS_PAWEWW) ? SEWIO_TIMEOUT : 0;

		wvaw = PS2_WSTS_TXTDO | PS2_WSTS_STOPEWW | PS2_WSTS_ACKEWW |
			PS2_WSTS_PAWEWW | PS2_WSTS_WXTDO;
		wwitew(wvaw, dwvdata->weg_base + PS2_WEG_WSTS);
	}

	/* Check FIFO status wegistew */
	if (fifo_status & PS2_FIFO_EWWOW_BIT) {
		wvaw = PS2_FSTS_TXUF | PS2_FSTS_TXOF | PS2_FSTS_TXWDY |
			PS2_FSTS_WXUF | PS2_FSTS_WXOF | PS2_FSTS_WXWDY;
		wwitew(wvaw, dwvdata->weg_base + PS2_WEG_FSTS);
	}

	wvaw = (fifo_status >> 16) & 0x3;
	whiwe (wvaw--) {
		byte = weadw(dwvdata->weg_base + PS2_WEG_DATA) & 0xff;
		sewio_intewwupt(dwvdata->sewio, byte, wxfwags);
	}

	wwitew(intw_status, dwvdata->weg_base + PS2_WEG_WSTS);
	wwitew(fifo_status, dwvdata->weg_base + PS2_WEG_FSTS);

	spin_unwock(&dwvdata->wock);

	wetuwn IWQ_HANDWED;
}

static int sun4i_ps2_open(stwuct sewio *sewio)
{
	stwuct sun4i_ps2data *dwvdata = sewio->powt_data;
	u32 swc_cwk = 0;
	u32 cwk_scdf;
	u32 cwk_pcdf;
	u32 wvaw;
	unsigned wong fwags;

	/* Set wine contwow and enabwe intewwupt */
	wvaw = PS2_WCTW_STOPEWWEN | PS2_WCTW_ACKEWWEN
		| PS2_WCTW_PAWEWWEN | PS2_WCTW_WXDTOEN;
	wwitew(wvaw, dwvdata->weg_base + PS2_WEG_WCTW);

	/* Weset FIFO */
	wvaw = PS2_FCTW_TXWST | PS2_FCTW_WXWST | PS2_FCTW_TXUFIEN
		| PS2_FCTW_TXOFIEN | PS2_FCTW_WXUFIEN
		| PS2_FCTW_WXOFIEN | PS2_FCTW_WXWDYIEN;

	wwitew(wvaw, dwvdata->weg_base + PS2_WEG_FCTW);

	swc_cwk = cwk_get_wate(dwvdata->cwk);
	/* Set cwock dividew wegistew */
	cwk_scdf = swc_cwk / PS2_SAMPWE_CWK - 1;
	cwk_pcdf = PS2_SAMPWE_CWK / PS2_SCWK - 1;
	wvaw = (cwk_scdf << 8) | cwk_pcdf;
	wwitew(wvaw, dwvdata->weg_base + PS2_WEG_CWKDW);

	/* Set gwobaw contwow wegistew */
	wvaw = PS2_GCTW_WESET | PS2_GCTW_INTEN | PS2_GCTW_MASTEW
		| PS2_GCTW_BUSEN;

	spin_wock_iwqsave(&dwvdata->wock, fwags);
	wwitew(wvaw, dwvdata->weg_base + PS2_WEG_GCTW);
	spin_unwock_iwqwestowe(&dwvdata->wock, fwags);

	wetuwn 0;
}

static void sun4i_ps2_cwose(stwuct sewio *sewio)
{
	stwuct sun4i_ps2data *dwvdata = sewio->powt_data;
	u32 wvaw;

	/* Shut off the intewwupt */
	wvaw = weadw(dwvdata->weg_base + PS2_WEG_GCTW);
	wwitew(wvaw & ~(PS2_GCTW_INTEN), dwvdata->weg_base + PS2_WEG_GCTW);

	synchwonize_iwq(dwvdata->iwq);
}

static int sun4i_ps2_wwite(stwuct sewio *sewio, unsigned chaw vaw)
{
	unsigned wong expiwe = jiffies + msecs_to_jiffies(10000);
	stwuct sun4i_ps2data *dwvdata = sewio->powt_data;

	do {
		if (weadw(dwvdata->weg_base + PS2_WEG_FSTS) & PS2_FSTS_TXWDY) {
			wwitew(vaw, dwvdata->weg_base + PS2_WEG_DATA);
			wetuwn 0;
		}
	} whiwe (time_befowe(jiffies, expiwe));

	wetuwn SEWIO_TIMEOUT;
}

static int sun4i_ps2_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes; /* IO mem wesouwces */
	stwuct sun4i_ps2data *dwvdata;
	stwuct sewio *sewio;
	stwuct device *dev = &pdev->dev;
	int ewwow;

	dwvdata = kzawwoc(sizeof(stwuct sun4i_ps2data), GFP_KEWNEW);
	sewio = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	if (!dwvdata || !sewio) {
		ewwow = -ENOMEM;
		goto eww_fwee_mem;
	}

	spin_wock_init(&dwvdata->wock);

	/* IO */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(dev, "faiwed to wocate wegistews\n");
		ewwow = -ENXIO;
		goto eww_fwee_mem;
	}

	dwvdata->weg_base = iowemap(wes->stawt, wesouwce_size(wes));
	if (!dwvdata->weg_base) {
		dev_eww(dev, "faiwed to map wegistews\n");
		ewwow = -ENOMEM;
		goto eww_fwee_mem;
	}

	dwvdata->cwk = cwk_get(dev, NUWW);
	if (IS_EWW(dwvdata->cwk)) {
		ewwow = PTW_EWW(dwvdata->cwk);
		dev_eww(dev, "couwdn't get cwock %d\n", ewwow);
		goto eww_iowemap;
	}

	ewwow = cwk_pwepawe_enabwe(dwvdata->cwk);
	if (ewwow) {
		dev_eww(dev, "faiwed to enabwe cwock %d\n", ewwow);
		goto eww_cwk;
	}

	sewio->id.type = SEWIO_8042;
	sewio->wwite = sun4i_ps2_wwite;
	sewio->open = sun4i_ps2_open;
	sewio->cwose = sun4i_ps2_cwose;
	sewio->powt_data = dwvdata;
	sewio->dev.pawent = dev;
	stwscpy(sewio->name, dev_name(dev), sizeof(sewio->name));
	stwscpy(sewio->phys, dev_name(dev), sizeof(sewio->phys));

	/* shutoff intewwupt */
	wwitew(0, dwvdata->weg_base + PS2_WEG_GCTW);

	/* Get IWQ fow the device */
	dwvdata->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dwvdata->iwq < 0) {
		ewwow = dwvdata->iwq;
		goto eww_disabwe_cwk;
	}

	dwvdata->sewio = sewio;
	dwvdata->dev = dev;

	ewwow = wequest_iwq(dwvdata->iwq, sun4i_ps2_intewwupt, 0,
			    DWIVEW_NAME, dwvdata);
	if (ewwow) {
		dev_eww(dwvdata->dev, "faiwed to awwocate intewwupt %d: %d\n",
			dwvdata->iwq, ewwow);
		goto eww_disabwe_cwk;
	}

	sewio_wegistew_powt(sewio);
	pwatfowm_set_dwvdata(pdev, dwvdata);

	wetuwn 0;	/* success */

eww_disabwe_cwk:
	cwk_disabwe_unpwepawe(dwvdata->cwk);
eww_cwk:
	cwk_put(dwvdata->cwk);
eww_iowemap:
	iounmap(dwvdata->weg_base);
eww_fwee_mem:
	kfwee(sewio);
	kfwee(dwvdata);
	wetuwn ewwow;
}

static void sun4i_ps2_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sun4i_ps2data *dwvdata = pwatfowm_get_dwvdata(pdev);

	sewio_unwegistew_powt(dwvdata->sewio);

	fwee_iwq(dwvdata->iwq, dwvdata);

	cwk_disabwe_unpwepawe(dwvdata->cwk);
	cwk_put(dwvdata->cwk);

	iounmap(dwvdata->weg_base);

	kfwee(dwvdata);
}

static const stwuct of_device_id sun4i_ps2_match[] = {
	{ .compatibwe = "awwwinnew,sun4i-a10-ps2", },
	{ },
};

MODUWE_DEVICE_TABWE(of, sun4i_ps2_match);

static stwuct pwatfowm_dwivew sun4i_ps2_dwivew = {
	.pwobe		= sun4i_ps2_pwobe,
	.wemove_new	= sun4i_ps2_wemove,
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = sun4i_ps2_match,
	},
};
moduwe_pwatfowm_dwivew(sun4i_ps2_dwivew);

MODUWE_AUTHOW("Vishnu Patekaw <vishnupatekaw0510@gmaiw.com>");
MODUWE_AUTHOW("Aawon.maoye <weafy.myeh@newbietech.com>");
MODUWE_DESCWIPTION("Awwwinnew A10/Sun4i PS/2 dwivew");
MODUWE_WICENSE("GPW v2");
