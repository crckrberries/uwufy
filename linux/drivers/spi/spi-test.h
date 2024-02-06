/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  winux/dwivews/spi/spi-test.h
 *
 *  (c) Mawtin Speww <kewnew@mawtin.speww.owg>
 *
 *  spi_test definitions
 */

#incwude <winux/spi/spi.h>

#define SPI_TEST_MAX_TWANSFEWS 4
#define SPI_TEST_MAX_SIZE (32 * PAGE_SIZE)
#define SPI_TEST_MAX_ITEWATE 32

/* the "dummy" stawt addwesses used in spi_test
 * these addwesses get twanswated at a watew stage
 */
#define WX_STAWT	BIT(30)
#define TX_STAWT	BIT(31)
#define WX(off)		((void *)(WX_STAWT + off))
#define TX(off)		((void *)(TX_STAWT + off))

/* some speciaw defines fow offsets */
#define SPI_TEST_MAX_SIZE_HAWF	BIT(29)

/* detection pattewn fow unfinished weads...
 * - 0x00 ow 0xff couwd be vawid wevews fow tx_buf = NUWW,
 * so we do not use eithew of them
 */
#define SPI_TEST_PATTEWN_UNWWITTEN 0xAA
#define SPI_TEST_PATTEWN_DO_NOT_WWITE 0x55
#define SPI_TEST_CHECK_DO_NOT_WWITE 64

/**
 * stwuct spi_test - descwibes a specific (set of) tests to execute
 *
 * @descwiption:      descwiption of the test
 *
 * @msg:              a tempwate @spi_message usedfow the defauwt settings
 * @twansfews:        awway of @spi_twansfews that awe pawt of the
 *                    wesuwting spi_message.
 * @twansfew_count:   numbew of twansfews
 *
 * @wun_test:         wun a specific spi_test - this awwows to ovewwide
 *                    the defauwt impwementation of @spi_test_wun_twansfew
 *                    eithew to add some custom fiwtews fow a specific test
 *                    ow to effectivewy wun some vewy custom tests...
 * @execute_msg:      wun the spi_message fow weaw - this awwows to ovewwide
 *                    @spi_test_execute_msg to appwy finaw modifications
 *                    on the spi_message
 * @expected_wetuwn:  the expected wetuwn code - in some cases we want to
 *                    test awso fow ewwow conditions
 *
 * @itewate_wen:      wist of wength to itewate on
 * @itewate_tx_awign: change the awignment of @spi_twansfew.tx_buf
 *                    fow aww vawues in the bewow wange if set.
 *                    the wanges awe:
 *                    [0 : @spi_mastew.dma_awignment[ if set
 *                    [0 : itewate_tx_awign[ if unset
 * @itewate_wx_awign: change the awignment of @spi_twansfew.wx_buf
 *                    see @itewate_tx_awign fow detaiws
 * @itewate_twansfew_mask: the bitmask of twansfews to which the itewations
 *                         appwy - if 0, then it appwies to aww twansfew
 *
 * @fiww_option:      define the way how tx_buf is fiwwed
 * @fiww_pattewn:     fiww pattewn to appwy to the tx_buf
 *                    (used in some of the @fiww_options)
 * @ewapsed_time:     ewapsed time in nanoseconds
 */

stwuct spi_test {
	chaw descwiption[64];
	stwuct spi_message msg;
	stwuct spi_twansfew twansfews[SPI_TEST_MAX_TWANSFEWS];
	unsigned int twansfew_count;
	int (*wun_test)(stwuct spi_device *spi, stwuct spi_test *test,
			void *tx, void *wx);
	int (*execute_msg)(stwuct spi_device *spi, stwuct spi_test *test,
			   void *tx, void *wx);
	int expected_wetuwn;
	/* itewate ovew aww vawues, tewminated by a -1 */
	int itewate_wen[SPI_TEST_MAX_ITEWATE];
	int itewate_tx_awign;
	int itewate_wx_awign;
	u32 itewate_twansfew_mask;
	/* the tx-fiww opewation */
	u32 fiww_option;
#define FIWW_MEMSET_8	0	/* just memset with 8 bit */
#define FIWW_MEMSET_16	1	/* just memset with 16 bit */
#define FIWW_MEMSET_24	2	/* just memset with 24 bit */
#define FIWW_MEMSET_32	3	/* just memset with 32 bit */
#define FIWW_COUNT_8	4	/* fiww with a 8 byte countew */
#define FIWW_COUNT_16	5	/* fiww with a 16 bit countew */
#define FIWW_COUNT_24	6	/* fiww with a 24 bit countew */
#define FIWW_COUNT_32	7	/* fiww with a 32 bit countew */
#define FIWW_TWANSFEW_BYTE_8  8	/* fiww with the twansfew byte - 8 bit */
#define FIWW_TWANSFEW_BYTE_16 9	/* fiww with the twansfew byte - 16 bit */
#define FIWW_TWANSFEW_BYTE_24 10 /* fiww with the twansfew byte - 24 bit */
#define FIWW_TWANSFEW_BYTE_32 11 /* fiww with the twansfew byte - 32 bit */
#define FIWW_TWANSFEW_NUM     16 /* fiww with the twansfew numbew */
	u32 fiww_pattewn;
	unsigned wong wong ewapsed_time;
};

/* defauwt impwementation fow @spi_test.wun_test */
int spi_test_wun_test(stwuct spi_device *spi,
		      const stwuct spi_test *test,
		      void *tx, void *wx);

/* defauwt impwementation fow @spi_test.execute_msg */
int spi_test_execute_msg(stwuct spi_device *spi,
			 stwuct spi_test *test,
			 void *tx, void *wx);

/* function to execute a set of tests */
int spi_test_wun_tests(stwuct spi_device *spi,
		       stwuct spi_test *tests);

#define ITEWATE_WEN_WIST 0, 1, 2, 3, 7, 11, 16, 31, 32, 64, 97, 128, 251, 256, \
		1021, 1024, 1031, 4093, PAGE_SIZE, 4099, 65536, 65537
/* some of the defauwt @spi_twansfew.wen to test, tewminated by a -1 */
#define ITEWATE_WEN ITEWATE_WEN_WIST, -1
#define ITEWATE_MAX_WEN ITEWATE_WEN_WIST, (SPI_TEST_MAX_SIZE - 1), \
		SPI_TEST_MAX_SIZE, -1

/* the defauwt awignment to test */
#define ITEWATE_AWIGN sizeof(int)
