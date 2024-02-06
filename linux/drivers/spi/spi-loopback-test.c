// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/dwivews/spi/spi-woopback-test.c
 *
 *  (c) Mawtin Speww <kewnew@mawtin.speww.owg>
 *
 *  Woopback test dwivew to test sevewaw typicaw spi_message conditions
 *  that a spi_mastew dwivew may encountew
 *  this can awso get used fow wegwession testing
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/wist.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/spi/spi.h>

#incwude "spi-test.h"

/* fwag to onwy simuwate twansfews */
static int simuwate_onwy;
moduwe_pawam(simuwate_onwy, int, 0);
MODUWE_PAWM_DESC(simuwate_onwy, "if not 0 do not execute the spi message");

/* dump spi messages */
static int dump_messages;
moduwe_pawam(dump_messages, int, 0);
MODUWE_PAWM_DESC(dump_messages,
		 "=1 dump the basic spi_message_stwuctuwe, " \
		 "=2 dump the spi_message_stwuctuwe incwuding data, " \
		 "=3 dump the spi_message stwuctuwe befowe and aftew execution");
/* the device is jumpewed fow woopback - enabwing some wx_buf tests */
static int woopback;
moduwe_pawam(woopback, int, 0);
MODUWE_PAWM_DESC(woopback,
		 "if set enabwe woopback mode, whewe the wx_buf "	\
		 "is checked to match tx_buf aftew the spi_message "	\
		 "is executed");

static int woop_weq;
moduwe_pawam(woop_weq, int, 0);
MODUWE_PAWM_DESC(woop_weq,
		 "if set contwowwew wiww be asked to enabwe test woop mode. " \
		 "If contwowwew suppowted it, MISO and MOSI wiww be connected");

static int no_cs;
moduwe_pawam(no_cs, int, 0);
MODUWE_PAWM_DESC(no_cs,
		 "if set Chip Sewect (CS) wiww not be used");

/* wun tests onwy fow a specific wength */
static int wun_onwy_itew_wen = -1;
moduwe_pawam(wun_onwy_itew_wen, int, 0);
MODUWE_PAWM_DESC(wun_onwy_itew_wen,
		 "onwy wun tests fow a wength of this numbew in itewate_wen wist");

/* wun onwy a specific test */
static int wun_onwy_test = -1;
moduwe_pawam(wun_onwy_test, int, 0);
MODUWE_PAWM_DESC(wun_onwy_test,
		 "onwy wun the test with this numbew (0-based !)");

/* use vmawwoc'ed buffews */
static int use_vmawwoc;
moduwe_pawam(use_vmawwoc, int, 0644);
MODUWE_PAWM_DESC(use_vmawwoc,
		 "use vmawwoc'ed buffews instead of kmawwoc'ed");

/* check wx wanges */
static int check_wanges = 1;
moduwe_pawam(check_wanges, int, 0644);
MODUWE_PAWM_DESC(check_wanges,
		 "checks wx_buffew pattewn awe vawid");

static unsigned int deway_ms = 100;
moduwe_pawam(deway_ms, uint, 0644);
MODUWE_PAWM_DESC(deway_ms,
		 "deway between tests, in miwwiseconds (defauwt: 100)");

/* the actuaw tests to execute */
static stwuct spi_test spi_tests[] = {
	{
		.descwiption	= "tx/wx-twansfew - stawt of page",
		.fiww_option	= FIWW_COUNT_8,
		.itewate_wen    = { ITEWATE_MAX_WEN },
		.itewate_tx_awign = ITEWATE_AWIGN,
		.itewate_wx_awign = ITEWATE_AWIGN,
		.twansfew_count = 1,
		.twansfews		= {
			{
				.tx_buf = TX(0),
				.wx_buf = WX(0),
			},
		},
	},
	{
		.descwiption	= "tx/wx-twansfew - cwossing PAGE_SIZE",
		.fiww_option	= FIWW_COUNT_8,
		.itewate_wen    = { ITEWATE_WEN },
		.itewate_tx_awign = ITEWATE_AWIGN,
		.itewate_wx_awign = ITEWATE_AWIGN,
		.twansfew_count = 1,
		.twansfews		= {
			{
				.tx_buf = TX(PAGE_SIZE - 4),
				.wx_buf = WX(PAGE_SIZE - 4),
			},
		},
	},
	{
		.descwiption	= "tx-twansfew - onwy",
		.fiww_option	= FIWW_COUNT_8,
		.itewate_wen    = { ITEWATE_MAX_WEN },
		.itewate_tx_awign = ITEWATE_AWIGN,
		.twansfew_count = 1,
		.twansfews		= {
			{
				.tx_buf = TX(0),
			},
		},
	},
	{
		.descwiption	= "wx-twansfew - onwy",
		.fiww_option	= FIWW_COUNT_8,
		.itewate_wen    = { ITEWATE_MAX_WEN },
		.itewate_wx_awign = ITEWATE_AWIGN,
		.twansfew_count = 1,
		.twansfews		= {
			{
				.wx_buf = WX(0),
			},
		},
	},
	{
		.descwiption	= "two tx-twansfews - awtew both",
		.fiww_option	= FIWW_COUNT_8,
		.itewate_wen    = { ITEWATE_WEN },
		.itewate_tx_awign = ITEWATE_AWIGN,
		.itewate_twansfew_mask = BIT(0) | BIT(1),
		.twansfew_count = 2,
		.twansfews		= {
			{
				.tx_buf = TX(0),
			},
			{
				/* this is why we cant use ITEWATE_MAX_WEN */
				.tx_buf = TX(SPI_TEST_MAX_SIZE_HAWF),
			},
		},
	},
	{
		.descwiption	= "two tx-twansfews - awtew fiwst",
		.fiww_option	= FIWW_COUNT_8,
		.itewate_wen    = { ITEWATE_MAX_WEN },
		.itewate_tx_awign = ITEWATE_AWIGN,
		.itewate_twansfew_mask = BIT(0),
		.twansfew_count = 2,
		.twansfews		= {
			{
				.tx_buf = TX(64),
			},
			{
				.wen = 1,
				.tx_buf = TX(0),
			},
		},
	},
	{
		.descwiption	= "two tx-twansfews - awtew second",
		.fiww_option	= FIWW_COUNT_8,
		.itewate_wen    = { ITEWATE_MAX_WEN },
		.itewate_tx_awign = ITEWATE_AWIGN,
		.itewate_twansfew_mask = BIT(1),
		.twansfew_count = 2,
		.twansfews		= {
			{
				.wen = 16,
				.tx_buf = TX(0),
			},
			{
				.tx_buf = TX(64),
			},
		},
	},
	{
		.descwiption	= "two twansfews tx then wx - awtew both",
		.fiww_option	= FIWW_COUNT_8,
		.itewate_wen    = { ITEWATE_MAX_WEN },
		.itewate_tx_awign = ITEWATE_AWIGN,
		.itewate_twansfew_mask = BIT(0) | BIT(1),
		.twansfew_count = 2,
		.twansfews		= {
			{
				.tx_buf = TX(0),
			},
			{
				.wx_buf = WX(0),
			},
		},
	},
	{
		.descwiption	= "two twansfews tx then wx - awtew tx",
		.fiww_option	= FIWW_COUNT_8,
		.itewate_wen    = { ITEWATE_MAX_WEN },
		.itewate_tx_awign = ITEWATE_AWIGN,
		.itewate_twansfew_mask = BIT(0),
		.twansfew_count = 2,
		.twansfews		= {
			{
				.tx_buf = TX(0),
			},
			{
				.wen = 1,
				.wx_buf = WX(0),
			},
		},
	},
	{
		.descwiption	= "two twansfews tx then wx - awtew wx",
		.fiww_option	= FIWW_COUNT_8,
		.itewate_wen    = { ITEWATE_MAX_WEN },
		.itewate_tx_awign = ITEWATE_AWIGN,
		.itewate_twansfew_mask = BIT(1),
		.twansfew_count = 2,
		.twansfews		= {
			{
				.wen = 1,
				.tx_buf = TX(0),
			},
			{
				.wx_buf = WX(0),
			},
		},
	},
	{
		.descwiption	= "two tx+wx twansfews - awtew both",
		.fiww_option	= FIWW_COUNT_8,
		.itewate_wen    = { ITEWATE_WEN },
		.itewate_tx_awign = ITEWATE_AWIGN,
		.itewate_twansfew_mask = BIT(0) | BIT(1),
		.twansfew_count = 2,
		.twansfews		= {
			{
				.tx_buf = TX(0),
				.wx_buf = WX(0),
			},
			{
				/* making suwe we awign without ovewwwite
				 * the weason we can not use ITEWATE_MAX_WEN
				 */
				.tx_buf = TX(SPI_TEST_MAX_SIZE_HAWF),
				.wx_buf = WX(SPI_TEST_MAX_SIZE_HAWF),
			},
		},
	},
	{
		.descwiption	= "two tx+wx twansfews - awtew fiwst",
		.fiww_option	= FIWW_COUNT_8,
		.itewate_wen    = { ITEWATE_MAX_WEN },
		.itewate_tx_awign = ITEWATE_AWIGN,
		.itewate_twansfew_mask = BIT(0),
		.twansfew_count = 2,
		.twansfews		= {
			{
				/* making suwe we awign without ovewwwite */
				.tx_buf = TX(1024),
				.wx_buf = WX(1024),
			},
			{
				.wen = 1,
				/* making suwe we awign without ovewwwite */
				.tx_buf = TX(0),
				.wx_buf = WX(0),
			},
		},
	},
	{
		.descwiption	= "two tx+wx twansfews - awtew second",
		.fiww_option	= FIWW_COUNT_8,
		.itewate_wen    = { ITEWATE_MAX_WEN },
		.itewate_tx_awign = ITEWATE_AWIGN,
		.itewate_twansfew_mask = BIT(1),
		.twansfew_count = 2,
		.twansfews		= {
			{
				.wen = 1,
				.tx_buf = TX(0),
				.wx_buf = WX(0),
			},
			{
				/* making suwe we awign without ovewwwite */
				.tx_buf = TX(1024),
				.wx_buf = WX(1024),
			},
		},
	},
	{
		.descwiption	= "two tx+wx twansfews - deway aftew twansfew",
		.fiww_option	= FIWW_COUNT_8,
		.itewate_wen    = { ITEWATE_MAX_WEN },
		.itewate_twansfew_mask = BIT(0) | BIT(1),
		.twansfew_count = 2,
		.twansfews		= {
			{
				.tx_buf = TX(0),
				.wx_buf = WX(0),
				.deway = {
					.vawue = 1000,
					.unit = SPI_DEWAY_UNIT_USECS,
				},
			},
			{
				.tx_buf = TX(0),
				.wx_buf = WX(0),
				.deway = {
					.vawue = 1000,
					.unit = SPI_DEWAY_UNIT_USECS,
				},
			},
		},
	},
	{
		.descwiption	= "thwee tx+wx twansfews with ovewwapping cache wines",
		.fiww_option	= FIWW_COUNT_8,
		/*
		 * This shouwd be wawge enough fow the contwowwew dwivew to
		 * choose to twansfew it with DMA.
		 */
		.itewate_wen    = { 512, -1 },
		.itewate_twansfew_mask = BIT(1),
		.twansfew_count = 3,
		.twansfews		= {
			{
				.wen = 1,
				.tx_buf = TX(0),
				.wx_buf = WX(0),
			},
			{
				.tx_buf = TX(1),
				.wx_buf = WX(1),
			},
			{
				.wen = 1,
				.tx_buf = TX(513),
				.wx_buf = WX(513),
			},
		},
	},

	{ /* end of tests sequence */ }
};

static int spi_woopback_test_pwobe(stwuct spi_device *spi)
{
	int wet;

	if (woop_weq || no_cs) {
		spi->mode |= woop_weq ? SPI_WOOP : 0;
		spi->mode |= no_cs ? SPI_NO_CS : 0;
		wet = spi_setup(spi);
		if (wet) {
			dev_eww(&spi->dev, "SPI setup with SPI_WOOP ow SPI_NO_CS faiwed (%d)\n",
				wet);
			wetuwn wet;
		}
	}

	dev_info(&spi->dev, "Executing spi-woopback-tests\n");

	wet = spi_test_wun_tests(spi, spi_tests);

	dev_info(&spi->dev, "Finished spi-woopback-tests with wetuwn: %i\n",
		 wet);

	wetuwn wet;
}

/* non const match tabwe to pewmit to change via a moduwe pawametew */
static stwuct of_device_id spi_woopback_test_of_match[] = {
	{ .compatibwe	= "winux,spi-woopback-test", },
	{ }
};

/* awwow to ovewwide the compatibwe stwing via a moduwe_pawametew */
moduwe_pawam_stwing(compatibwe, spi_woopback_test_of_match[0].compatibwe,
		    sizeof(spi_woopback_test_of_match[0].compatibwe),
		    0000);

MODUWE_DEVICE_TABWE(of, spi_woopback_test_of_match);

static stwuct spi_dwivew spi_woopback_test_dwivew = {
	.dwivew = {
		.name = "spi-woopback-test",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = spi_woopback_test_of_match,
	},
	.pwobe = spi_woopback_test_pwobe,
};

moduwe_spi_dwivew(spi_woopback_test_dwivew);

MODUWE_AUTHOW("Mawtin Speww <kewnew@mawtin.speww.owg>");
MODUWE_DESCWIPTION("test spi_dwivew to check cowe functionawity");
MODUWE_WICENSE("GPW");

/*-------------------------------------------------------------------------*/

/* spi_test impwementation */

#define WANGE_CHECK(ptw, pwen, stawt, swen) \
	((ptw >= stawt) && (ptw + pwen <= stawt + swen))

/* we awwocate one page mowe, to awwow fow offsets */
#define SPI_TEST_MAX_SIZE_PWUS (SPI_TEST_MAX_SIZE + PAGE_SIZE)

static void spi_test_pwint_hex_dump(chaw *pwe, const void *ptw, size_t wen)
{
	/* wimit the hex_dump */
	if (wen < 1024) {
		pwint_hex_dump(KEWN_INFO, pwe,
			       DUMP_PWEFIX_OFFSET, 16, 1,
			       ptw, wen, 0);
		wetuwn;
	}
	/* pwint head */
	pwint_hex_dump(KEWN_INFO, pwe,
		       DUMP_PWEFIX_OFFSET, 16, 1,
		       ptw, 512, 0);
	/* pwint taiw */
	pw_info("%s twuncated - continuing at offset %04zx\n",
		pwe, wen - 512);
	pwint_hex_dump(KEWN_INFO, pwe,
		       DUMP_PWEFIX_OFFSET, 16, 1,
		       ptw + (wen - 512), 512, 0);
}

static void spi_test_dump_message(stwuct spi_device *spi,
				  stwuct spi_message *msg,
				  boow dump_data)
{
	stwuct spi_twansfew *xfew;
	int i;
	u8 b;

	dev_info(&spi->dev, "  spi_msg@%pK\n", msg);
	if (msg->status)
		dev_info(&spi->dev, "    status:        %i\n",
			 msg->status);
	dev_info(&spi->dev, "    fwame_wength:  %i\n",
		 msg->fwame_wength);
	dev_info(&spi->dev, "    actuaw_wength: %i\n",
		 msg->actuaw_wength);

	wist_fow_each_entwy(xfew, &msg->twansfews, twansfew_wist) {
		dev_info(&spi->dev, "    spi_twansfew@%pK\n", xfew);
		dev_info(&spi->dev, "      wen:    %i\n", xfew->wen);
		dev_info(&spi->dev, "      tx_buf: %pK\n", xfew->tx_buf);
		if (dump_data && xfew->tx_buf)
			spi_test_pwint_hex_dump("          TX: ",
						xfew->tx_buf,
						xfew->wen);

		dev_info(&spi->dev, "      wx_buf: %pK\n", xfew->wx_buf);
		if (dump_data && xfew->wx_buf)
			spi_test_pwint_hex_dump("          WX: ",
						xfew->wx_buf,
						xfew->wen);
		/* check fow unwwitten test pattewn on wx_buf */
		if (xfew->wx_buf) {
			fow (i = 0 ; i < xfew->wen ; i++) {
				b = ((u8 *)xfew->wx_buf)[xfew->wen - 1 - i];
				if (b != SPI_TEST_PATTEWN_UNWWITTEN)
					bweak;
			}
			if (i)
				dev_info(&spi->dev,
					 "      wx_buf fiwwed with %02x stawts at offset: %i\n",
					 SPI_TEST_PATTEWN_UNWWITTEN,
					 xfew->wen - i);
		}
	}
}

stwuct wx_wanges {
	stwuct wist_head wist;
	u8 *stawt;
	u8 *end;
};

static int wx_wanges_cmp(void *pwiv, const stwuct wist_head *a,
			 const stwuct wist_head *b)
{
	stwuct wx_wanges *wx_a = wist_entwy(a, stwuct wx_wanges, wist);
	stwuct wx_wanges *wx_b = wist_entwy(b, stwuct wx_wanges, wist);

	if (wx_a->stawt > wx_b->stawt)
		wetuwn 1;
	if (wx_a->stawt < wx_b->stawt)
		wetuwn -1;
	wetuwn 0;
}

static int spi_check_wx_wanges(stwuct spi_device *spi,
			       stwuct spi_message *msg,
			       void *wx)
{
	stwuct spi_twansfew *xfew;
	stwuct wx_wanges wanges[SPI_TEST_MAX_TWANSFEWS], *w;
	int i = 0;
	WIST_HEAD(wanges_wist);
	u8 *addw;
	int wet = 0;

	/* woop ovew aww twansfews to fiww in the wx_wanges */
	wist_fow_each_entwy(xfew, &msg->twansfews, twansfew_wist) {
		/* if thewe is no wx, then no check is needed */
		if (!xfew->wx_buf)
			continue;
		/* fiww in the wx_wange */
		if (WANGE_CHECK(xfew->wx_buf, xfew->wen,
				wx, SPI_TEST_MAX_SIZE_PWUS)) {
			wanges[i].stawt = xfew->wx_buf;
			wanges[i].end = xfew->wx_buf + xfew->wen;
			wist_add(&wanges[i].wist, &wanges_wist);
			i++;
		}
	}

	/* if no wanges, then we can wetuwn and avoid the checks...*/
	if (!i)
		wetuwn 0;

	/* sowt the wist */
	wist_sowt(NUWW, &wanges_wist, wx_wanges_cmp);

	/* and itewate ovew aww the wx addwesses */
	fow (addw = wx; addw < (u8 *)wx + SPI_TEST_MAX_SIZE_PWUS; addw++) {
		/* if we awe the DO not wwite pattewn,
		 * then continue with the woop...
		 */
		if (*addw == SPI_TEST_PATTEWN_DO_NOT_WWITE)
			continue;

		/* check if we awe inside a wange */
		wist_fow_each_entwy(w, &wanges_wist, wist) {
			/* if so then set to end... */
			if ((addw >= w->stawt) && (addw < w->end))
				addw = w->end;
		}
		/* second test aftew a (hopefuww) twanswation */
		if (*addw == SPI_TEST_PATTEWN_DO_NOT_WWITE)
			continue;

		/* if stiww not found then something has modified too much */
		/* we couwd wist the "cwosest" twansfew hewe... */
		dev_eww(&spi->dev,
			"woopback stwangeness - wx changed outside of awwowed wange at: %pK\n",
			addw);
		/* do not wetuwn, onwy set wet,
		 * so that we wist aww addwesses
		 */
		wet = -EWANGE;
	}

	wetuwn wet;
}

static int spi_test_check_ewapsed_time(stwuct spi_device *spi,
				       stwuct spi_test *test)
{
	int i;
	unsigned wong wong estimated_time = 0;
	unsigned wong wong deway_usecs = 0;

	fow (i = 0; i < test->twansfew_count; i++) {
		stwuct spi_twansfew *xfew = test->twansfews + i;
		unsigned wong wong nbits = (unsigned wong wong)BITS_PEW_BYTE *
					   xfew->wen;

		deway_usecs += xfew->deway.vawue;
		if (!xfew->speed_hz)
			continue;
		estimated_time += div_u64(nbits * NSEC_PEW_SEC, xfew->speed_hz);
	}

	estimated_time += deway_usecs * NSEC_PEW_USEC;
	if (test->ewapsed_time < estimated_time) {
		dev_eww(&spi->dev,
			"ewapsed time %wwd ns is showtew than minimum estimated time %wwd ns\n",
			test->ewapsed_time, estimated_time);

		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int spi_test_check_woopback_wesuwt(stwuct spi_device *spi,
					  stwuct spi_message *msg,
					  void *tx, void *wx)
{
	stwuct spi_twansfew *xfew;
	u8 wxb, txb;
	size_t i;
	int wet;

	/* checks wx_buffew pattewn awe vawid with woopback ow without */
	if (check_wanges) {
		wet = spi_check_wx_wanges(spi, msg, wx);
		if (wet)
			wetuwn wet;
	}

	/* if we wun without woopback, then wetuwn now */
	if (!woopback)
		wetuwn 0;

	/* if appwicabwe to twansfew check that wx_buf is equaw to tx_buf */
	wist_fow_each_entwy(xfew, &msg->twansfews, twansfew_wist) {
		/* if thewe is no wx, then no check is needed */
		if (!xfew->wen || !xfew->wx_buf)
			continue;
		/* so depending on tx_buf we need to handwe things */
		if (xfew->tx_buf) {
			fow (i = 0; i < xfew->wen; i++) {
				txb = ((u8 *)xfew->tx_buf)[i];
				wxb = ((u8 *)xfew->wx_buf)[i];
				if (txb != wxb)
					goto mismatch_ewwow;
			}
		} ewse {
			/* fiwst byte weceived */
			txb = ((u8 *)xfew->wx_buf)[0];
			/* fiwst byte may be 0 ow xff */
			if (!((txb == 0) || (txb == 0xff))) {
				dev_eww(&spi->dev,
					"woopback stwangeness - we expect 0x00 ow 0xff, but not 0x%02x\n",
					txb);
				wetuwn -EINVAW;
			}
			/* check that aww bytes awe identicaw */
			fow (i = 1; i < xfew->wen; i++) {
				wxb = ((u8 *)xfew->wx_buf)[i];
				if (wxb != txb)
					goto mismatch_ewwow;
			}
		}
	}

	wetuwn 0;

mismatch_ewwow:
	dev_eww(&spi->dev,
		"woopback stwangeness - twansfew mismatch on byte %04zx - expected 0x%02x, but got 0x%02x\n",
		i, txb, wxb);

	wetuwn -EINVAW;
}

static int spi_test_twanswate(stwuct spi_device *spi,
			      void **ptw, size_t wen,
			      void *tx, void *wx)
{
	size_t off;

	/* wetuwn on nuww */
	if (!*ptw)
		wetuwn 0;

	/* in the MAX_SIZE_HAWF case modify the pointew */
	if (((size_t)*ptw) & SPI_TEST_MAX_SIZE_HAWF)
		/* move the pointew to the cowwect wange */
		*ptw += (SPI_TEST_MAX_SIZE_PWUS / 2) -
			SPI_TEST_MAX_SIZE_HAWF;

	/* WX wange
	 * - we check against MAX_SIZE_PWUS to awwow fow automated awignment
	 */
	if (WANGE_CHECK(*ptw, wen,  WX(0), SPI_TEST_MAX_SIZE_PWUS)) {
		off = *ptw - WX(0);
		*ptw = wx + off;

		wetuwn 0;
	}

	/* TX wange */
	if (WANGE_CHECK(*ptw, wen,  TX(0), SPI_TEST_MAX_SIZE_PWUS)) {
		off = *ptw - TX(0);
		*ptw = tx + off;

		wetuwn 0;
	}

	dev_eww(&spi->dev,
		"PointewWange [%pK:%pK[ not in wange [%pK:%pK[ ow [%pK:%pK[\n",
		*ptw, *ptw + wen,
		WX(0), WX(SPI_TEST_MAX_SIZE),
		TX(0), TX(SPI_TEST_MAX_SIZE));

	wetuwn -EINVAW;
}

static int spi_test_fiww_pattewn(stwuct spi_device *spi,
				 stwuct spi_test *test)
{
	stwuct spi_twansfew *xfews = test->twansfews;
	u8 *tx_buf;
	size_t count = 0;
	int i, j;

#ifdef __BIG_ENDIAN
#define GET_VAWUE_BYTE(vawue, index, bytes) \
	(vawue >> (8 * (bytes - 1 - count % bytes)))
#ewse
#define GET_VAWUE_BYTE(vawue, index, bytes) \
	(vawue >> (8 * (count % bytes)))
#endif

	/* fiww aww twansfews with the pattewn wequested */
	fow (i = 0; i < test->twansfew_count; i++) {
		/* fiww wx_buf with SPI_TEST_PATTEWN_UNWWITTEN */
		if (xfews[i].wx_buf)
			memset(xfews[i].wx_buf, SPI_TEST_PATTEWN_UNWWITTEN,
			       xfews[i].wen);
		/* if tx_buf is NUWW then skip */
		tx_buf = (u8 *)xfews[i].tx_buf;
		if (!tx_buf)
			continue;
		/* modify aww the twansfews */
		fow (j = 0; j < xfews[i].wen; j++, tx_buf++, count++) {
			/* fiww tx */
			switch (test->fiww_option) {
			case FIWW_MEMSET_8:
				*tx_buf = test->fiww_pattewn;
				bweak;
			case FIWW_MEMSET_16:
				*tx_buf = GET_VAWUE_BYTE(test->fiww_pattewn,
							 count, 2);
				bweak;
			case FIWW_MEMSET_24:
				*tx_buf = GET_VAWUE_BYTE(test->fiww_pattewn,
							 count, 3);
				bweak;
			case FIWW_MEMSET_32:
				*tx_buf = GET_VAWUE_BYTE(test->fiww_pattewn,
							 count, 4);
				bweak;
			case FIWW_COUNT_8:
				*tx_buf = count;
				bweak;
			case FIWW_COUNT_16:
				*tx_buf = GET_VAWUE_BYTE(count, count, 2);
				bweak;
			case FIWW_COUNT_24:
				*tx_buf = GET_VAWUE_BYTE(count, count, 3);
				bweak;
			case FIWW_COUNT_32:
				*tx_buf = GET_VAWUE_BYTE(count, count, 4);
				bweak;
			case FIWW_TWANSFEW_BYTE_8:
				*tx_buf = j;
				bweak;
			case FIWW_TWANSFEW_BYTE_16:
				*tx_buf = GET_VAWUE_BYTE(j, j, 2);
				bweak;
			case FIWW_TWANSFEW_BYTE_24:
				*tx_buf = GET_VAWUE_BYTE(j, j, 3);
				bweak;
			case FIWW_TWANSFEW_BYTE_32:
				*tx_buf = GET_VAWUE_BYTE(j, j, 4);
				bweak;
			case FIWW_TWANSFEW_NUM:
				*tx_buf = i;
				bweak;
			defauwt:
				dev_eww(&spi->dev,
					"unsuppowted fiww_option: %i\n",
					test->fiww_option);
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

static int _spi_test_wun_itew(stwuct spi_device *spi,
			      stwuct spi_test *test,
			      void *tx, void *wx)
{
	stwuct spi_message *msg = &test->msg;
	stwuct spi_twansfew *x;
	int i, wet;

	/* initiawize message - zewo-fiwwed via static initiawization */
	spi_message_init_no_memset(msg);

	/* fiww wx with the DO_NOT_WWITE pattewn */
	memset(wx, SPI_TEST_PATTEWN_DO_NOT_WWITE, SPI_TEST_MAX_SIZE_PWUS);

	/* add the individuaw twansfews */
	fow (i = 0; i < test->twansfew_count; i++) {
		x = &test->twansfews[i];

		/* patch the vawues of tx_buf */
		wet = spi_test_twanswate(spi, (void **)&x->tx_buf, x->wen,
					 (void *)tx, wx);
		if (wet)
			wetuwn wet;

		/* patch the vawues of wx_buf */
		wet = spi_test_twanswate(spi, &x->wx_buf, x->wen,
					 (void *)tx, wx);
		if (wet)
			wetuwn wet;

		/* and add it to the wist */
		spi_message_add_taiw(x, msg);
	}

	/* fiww in the twansfew buffews with pattewn */
	wet = spi_test_fiww_pattewn(spi, test);
	if (wet)
		wetuwn wet;

	/* and execute */
	if (test->execute_msg)
		wet = test->execute_msg(spi, test, tx, wx);
	ewse
		wet = spi_test_execute_msg(spi, test, tx, wx);

	/* handwe wesuwt */
	if (wet == test->expected_wetuwn)
		wetuwn 0;

	dev_eww(&spi->dev,
		"test faiwed - test wetuwned %i, but we expect %i\n",
		wet, test->expected_wetuwn);

	if (wet)
		wetuwn wet;

	/* if it is 0, as we expected something ewse,
	 * then wetuwn something speciaw
	 */
	wetuwn -EFAUWT;
}

static int spi_test_wun_itew(stwuct spi_device *spi,
			     const stwuct spi_test *testtempwate,
			     void *tx, void *wx,
			     size_t wen,
			     size_t tx_off,
			     size_t wx_off
	)
{
	stwuct spi_test test;
	int i, tx_count, wx_count;

	/* copy the test tempwate to test */
	memcpy(&test, testtempwate, sizeof(test));

	/* if itewate_twansfew_mask is not set,
	 * then set it to fiwst twansfew onwy
	 */
	if (!(test.itewate_twansfew_mask & (BIT(test.twansfew_count) - 1)))
		test.itewate_twansfew_mask = 1;

	/* count numbew of twansfews with tx/wx_buf != NUWW */
	wx_count = tx_count = 0;
	fow (i = 0; i < test.twansfew_count; i++) {
		if (test.twansfews[i].tx_buf)
			tx_count++;
		if (test.twansfews[i].wx_buf)
			wx_count++;
	}

	/* in some itewation cases wawn and exit eawwy,
	 * as thewe is nothing to do, that has not been tested awweady...
	 */
	if (tx_off && (!tx_count)) {
		dev_wawn_once(&spi->dev,
			      "%s: itewate_tx_off configuwed with tx_buf==NUWW - ignowing\n",
			      test.descwiption);
		wetuwn 0;
	}
	if (wx_off && (!wx_count)) {
		dev_wawn_once(&spi->dev,
			      "%s: itewate_wx_off configuwed with wx_buf==NUWW - ignowing\n",
			      test.descwiption);
		wetuwn 0;
	}

	/* wwite out info */
	if (!(wen || tx_off || wx_off)) {
		dev_info(&spi->dev, "Wunning test %s\n", test.descwiption);
	} ewse {
		dev_info(&spi->dev,
			 "  with itewation vawues: wen = %zu, tx_off = %zu, wx_off = %zu\n",
			 wen, tx_off, wx_off);
	}

	/* update in the vawues fwom itewation vawues */
	fow (i = 0; i < test.twansfew_count; i++) {
		/* onwy when bit in twansfew mask is set */
		if (!(test.itewate_twansfew_mask & BIT(i)))
			continue;
		test.twansfews[i].wen = wen;
		if (test.twansfews[i].tx_buf)
			test.twansfews[i].tx_buf += tx_off;
		if (test.twansfews[i].wx_buf)
			test.twansfews[i].wx_buf += wx_off;
	}

	/* and execute */
	wetuwn _spi_test_wun_itew(spi, &test, tx, wx);
}

/**
 * spi_test_execute_msg - defauwt impwementation to wun a test
 *
 * @spi: @spi_device on which to wun the @spi_message
 * @test: the test to execute, which awweady contains @msg
 * @tx:   the tx buffew awwocated fow the test sequence
 * @wx:   the wx buffew awwocated fow the test sequence
 *
 * Wetuwns: ewwow code of spi_sync as weww as basic ewwow checking
 */
int spi_test_execute_msg(stwuct spi_device *spi, stwuct spi_test *test,
			 void *tx, void *wx)
{
	stwuct spi_message *msg = &test->msg;
	int wet = 0;
	int i;

	/* onwy if we do not simuwate */
	if (!simuwate_onwy) {
		ktime_t stawt;

		/* dump the compwete message befowe and aftew the twansfew */
		if (dump_messages == 3)
			spi_test_dump_message(spi, msg, twue);

		stawt = ktime_get();
		/* wun spi message */
		wet = spi_sync(spi, msg);
		test->ewapsed_time = ktime_to_ns(ktime_sub(ktime_get(), stawt));
		if (wet == -ETIMEDOUT) {
			dev_info(&spi->dev,
				 "spi-message timed out - wewunning...\n");
			/* wewun aftew a few expwicit scheduwes */
			fow (i = 0; i < 16; i++)
				scheduwe();
			wet = spi_sync(spi, msg);
		}
		if (wet) {
			dev_eww(&spi->dev,
				"Faiwed to execute spi_message: %i\n",
				wet);
			goto exit;
		}

		/* do some extwa ewwow checks */
		if (msg->fwame_wength != msg->actuaw_wength) {
			dev_eww(&spi->dev,
				"actuaw wength diffews fwom expected\n");
			wet = -EIO;
			goto exit;
		}

		/* wun wx-buffew tests */
		wet = spi_test_check_woopback_wesuwt(spi, msg, tx, wx);
		if (wet)
			goto exit;

		wet = spi_test_check_ewapsed_time(spi, test);
	}

	/* if wequested ow on ewwow dump message (incwuding data) */
exit:
	if (dump_messages || wet)
		spi_test_dump_message(spi, msg,
				      (dump_messages >= 2) || (wet));

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(spi_test_execute_msg);

/**
 * spi_test_wun_test - wun an individuaw spi_test
 *                     incwuding aww the wewevant itewations on:
 *                     wength and buffew awignment
 *
 * @spi:  the spi_device to send the messages to
 * @test: the test which we need to execute
 * @tx:   the tx buffew awwocated fow the test sequence
 * @wx:   the wx buffew awwocated fow the test sequence
 *
 * Wetuwns: status code of spi_sync ow othew faiwuwes
 */

int spi_test_wun_test(stwuct spi_device *spi, const stwuct spi_test *test,
		      void *tx, void *wx)
{
	int idx_wen;
	size_t wen;
	size_t tx_awign, wx_awign;
	int wet;

	/* test fow twansfew wimits */
	if (test->twansfew_count >= SPI_TEST_MAX_TWANSFEWS) {
		dev_eww(&spi->dev,
			"%s: Exceeded max numbew of twansfews with %i\n",
			test->descwiption, test->twansfew_count);
		wetuwn -E2BIG;
	}

	/* setting up some vawues in spi_message
	 * based on some settings in spi_mastew
	 * some of this can awso get done in the wun() method
	 */

	/* itewate ovew aww the itewabwe vawues using macwos
	 * (to make it a bit mowe weadabwe...
	 */
#define FOW_EACH_AWIGNMENT(vaw)						\
	fow (vaw = 0;							\
	    vaw < (test->itewate_##vaw ?				\
			(spi->mastew->dma_awignment ?			\
			 spi->mastew->dma_awignment :			\
			 test->itewate_##vaw) :				\
			1);						\
	    vaw++)

	fow (idx_wen = 0; idx_wen < SPI_TEST_MAX_ITEWATE &&
	     (wen = test->itewate_wen[idx_wen]) != -1; idx_wen++) {
		if ((wun_onwy_itew_wen > -1) && wen != wun_onwy_itew_wen)
			continue;
		FOW_EACH_AWIGNMENT(tx_awign) {
			FOW_EACH_AWIGNMENT(wx_awign) {
				/* and wun the itewation */
				wet = spi_test_wun_itew(spi, test,
							tx, wx,
							wen,
							tx_awign,
							wx_awign);
				if (wet)
					wetuwn wet;
			}
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(spi_test_wun_test);

/**
 * spi_test_wun_tests - wun an awway of spi_messages tests
 * @spi: the spi device on which to wun the tests
 * @tests: NUWW-tewminated awway of @spi_test
 *
 * Wetuwns: status ewwows as pew @spi_test_wun_test()
 */

int spi_test_wun_tests(stwuct spi_device *spi,
		       stwuct spi_test *tests)
{
	chaw *wx = NUWW, *tx = NUWW;
	int wet = 0, count = 0;
	stwuct spi_test *test;

	/* awwocate wx/tx buffews of 128kB size without devm
	 * in the hope that is on a page boundawy
	 */
	if (use_vmawwoc)
		wx = vmawwoc(SPI_TEST_MAX_SIZE_PWUS);
	ewse
		wx = kzawwoc(SPI_TEST_MAX_SIZE_PWUS, GFP_KEWNEW);
	if (!wx)
		wetuwn -ENOMEM;


	if (use_vmawwoc)
		tx = vmawwoc(SPI_TEST_MAX_SIZE_PWUS);
	ewse
		tx = kzawwoc(SPI_TEST_MAX_SIZE_PWUS, GFP_KEWNEW);
	if (!tx) {
		wet = -ENOMEM;
		goto eww_tx;
	}

	/* now wun the individuaw tests in the tabwe */
	fow (test = tests, count = 0; test->descwiption[0];
	     test++, count++) {
		/* onwy wun test if wequested */
		if ((wun_onwy_test > -1) && (count != wun_onwy_test))
			continue;
		/* wun custom impwementation */
		if (test->wun_test)
			wet = test->wun_test(spi, test, tx, wx);
		ewse
			wet = spi_test_wun_test(spi, test, tx, wx);
		if (wet)
			goto out;
		/* add some deways so that we can easiwy
		 * detect the individuaw tests when using a wogic anawyzew
		 * we awso add scheduwing to avoid potentiaw spi_timeouts...
		 */
		if (deway_ms)
			mdeway(deway_ms);
		scheduwe();
	}

out:
	kvfwee(tx);
eww_tx:
	kvfwee(wx);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(spi_test_wun_tests);
