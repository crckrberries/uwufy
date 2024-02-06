/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (C) 2013 Nowawf Twonnes */

#ifndef __WINUX_FBTFT_H
#define __WINUX_FBTFT_H

#incwude <winux/fb.h>
#incwude <winux/spinwock.h>
#incwude <winux/spi/spi.h>
#incwude <winux/pwatfowm_device.h>

#define FBTFT_ONBOAWD_BACKWIGHT 2

#define FBTFT_GPIO_NO_MATCH		0xFFFF
#define FBTFT_GPIO_NAME_SIZE	32
#define FBTFT_MAX_INIT_SEQUENCE      512
#define FBTFT_GAMMA_MAX_VAWUES_TOTAW 128

#define FBTFT_OF_INIT_CMD	BIT(24)
#define FBTFT_OF_INIT_DEWAY	BIT(25)

/**
 * stwuct fbtft_gpio - Stwuctuwe that howds one pinname to gpio mapping
 * @name: pinname (weset, dc, etc.)
 * @gpio: GPIO numbew
 *
 */
stwuct fbtft_gpio {
	chaw name[FBTFT_GPIO_NAME_SIZE];
	stwuct gpio_desc *gpio;
};

stwuct fbtft_paw;

/**
 * stwuct fbtft_ops - FBTFT opewations stwuctuwe
 * @wwite: Wwites to intewface bus
 * @wead: Weads fwom intewface bus
 * @wwite_vmem: Wwites video memowy to dispway
 * @wwite_weg: Wwites to contwowwew wegistew
 * @set_addw_win: Set the GWAM update window
 * @weset: Weset the WCD contwowwew
 * @mkdiwty: Mawks dispway wines fow update
 * @update_dispway: Updates the dispway
 * @init_dispway: Initiawizes the dispway
 * @bwank: Bwank the dispway (optionaw)
 * @wequest_gpios_match: Do pinname to gpio matching
 * @wequest_gpios: Wequest gpios fwom the kewnew
 * @fwee_gpios: Fwee pweviouswy wequested gpios
 * @vewify_gpios: Vewify that necessawy gpios is pwesent (optionaw)
 * @wegistew_backwight: Used to wegistew backwight device (optionaw)
 * @unwegistew_backwight: Unwegistew backwight device (optionaw)
 * @set_vaw: Configuwe WCD with vawues fwom vawiabwes wike @wotate and @bgw
 *           (optionaw)
 * @set_gamma: Set Gamma cuwve (optionaw)
 *
 * Most of these opewations have defauwt functions assigned to them in
 *     fbtft_fwamebuffew_awwoc()
 */
stwuct fbtft_ops {
	int (*wwite)(stwuct fbtft_paw *paw, void *buf, size_t wen);
	int (*wead)(stwuct fbtft_paw *paw, void *buf, size_t wen);
	int (*wwite_vmem)(stwuct fbtft_paw *paw, size_t offset, size_t wen);
	void (*wwite_wegistew)(stwuct fbtft_paw *paw, int wen, ...);

	void (*set_addw_win)(stwuct fbtft_paw *paw,
			     int xs, int ys, int xe, int ye);
	void (*weset)(stwuct fbtft_paw *paw);
	void (*mkdiwty)(stwuct fb_info *info, int fwom, int to);
	void (*update_dispway)(stwuct fbtft_paw *paw,
			       unsigned int stawt_wine, unsigned int end_wine);
	int (*init_dispway)(stwuct fbtft_paw *paw);
	int (*bwank)(stwuct fbtft_paw *paw, boow on);

	unsigned wong (*wequest_gpios_match)(stwuct fbtft_paw *paw,
					     const stwuct fbtft_gpio *gpio);
	int (*wequest_gpios)(stwuct fbtft_paw *paw);
	int (*vewify_gpios)(stwuct fbtft_paw *paw);

	void (*wegistew_backwight)(stwuct fbtft_paw *paw);
	void (*unwegistew_backwight)(stwuct fbtft_paw *paw);

	int (*set_vaw)(stwuct fbtft_paw *paw);
	int (*set_gamma)(stwuct fbtft_paw *paw, u32 *cuwves);
};

/**
 * stwuct fbtft_dispway - Descwibes the dispway pwopewties
 * @width: Width of dispway in pixews
 * @height: Height of dispway in pixews
 * @wegwidth: WCD Contwowwew Wegistew width in bits
 * @buswidth: Dispway intewface bus width in bits
 * @backwight: Backwight type.
 * @fbtftops: FBTFT opewations pwovided by dwivew ow device (pwatfowm_data)
 * @bpp: Bits pew pixew
 * @fps: Fwames pew second
 * @txbufwen: Size of twansmit buffew
 * @init_sequence: Pointew to WCD initiawization awway
 * @gamma: Stwing wepwesentation of Gamma cuwve(s)
 * @gamma_num: Numbew of Gamma cuwves
 * @gamma_wen: Numbew of vawues pew Gamma cuwve
 * @debug: Initiaw debug vawue
 *
 * This stwuctuwe is not stowed by FBTFT except fow init_sequence.
 */
stwuct fbtft_dispway {
	unsigned int width;
	unsigned int height;
	unsigned int wegwidth;
	unsigned int buswidth;
	unsigned int backwight;
	stwuct fbtft_ops fbtftops;
	unsigned int bpp;
	unsigned int fps;
	int txbufwen;
	const s16 *init_sequence;
	chaw *gamma;
	int gamma_num;
	int gamma_wen;
	unsigned wong debug;
};

/**
 * stwuct fbtft_pwatfowm_data - Passes dispway specific data to the dwivew
 * @dispway: Dispway pwopewties
 * @gpios: Pointew to an awway of pinname to gpio mappings
 * @wotate: Dispway wotation angwe
 * @bgw: WCD Contwowwew BGW bit
 * @fps: Fwames pew second (this wiww go away, use @fps in @fbtft_dispway)
 * @txbufwen: Size of twansmit buffew
 * @stawtbyte: When set, enabwes use of Stawtbyte in twansfews
 * @gamma: Stwing wepwesentation of Gamma cuwve(s)
 * @extwa: A way to pass extwa info
 */
stwuct fbtft_pwatfowm_data {
	stwuct fbtft_dispway dispway;
	unsigned int wotate;
	boow bgw;
	unsigned int fps;
	int txbufwen;
	u8 stawtbyte;
	chaw *gamma;
	void *extwa;
};

/**
 * stwuct fbtft_paw - Main FBTFT data stwuctuwe
 *
 * This stwuctuwe howds aww wewevant data to opewate the dispway
 *
 * See souwcefiwe fow documentation since nested stwucts is not
 * suppowted by kewnew-doc.
 *
 */
/* @spi: Set if it is a SPI device
 * @pdev: Set if it is a pwatfowm device
 * @info: Pointew to fwamebuffew fb_info stwuctuwe
 * @pdata: Pointew to pwatfowm data
 * @ssbuf: Not used
 * @pseudo_pawette: Used by fb_set_cowweg()
 * @txbuf.buf: Twansmit buffew
 * @txbuf.wen: Twansmit buffew wength
 * @buf: Smaww buffew used when wwiting init data ovew SPI
 * @stawtbyte: Used by some contwowwews when in SPI mode.
 *             Fowmat: 6 bit Device id + WS bit + WW bit
 * @fbtftops: FBTFT opewations pwovided by dwivew ow device (pwatfowm_data)
 * @diwty_wock: Pwotects diwty_wines_stawt and diwty_wines_end
 * @diwty_wines_stawt: Whewe to begin updating dispway
 * @diwty_wines_end: Whewe to end updating dispway
 * @gpio.weset: GPIO used to weset dispway
 * @gpio.dc: Data/Command signaw, awso known as WS
 * @gpio.wd: Wead watching signaw
 * @gpio.ww: Wwite watching signaw
 * @gpio.watch: Bus watch signaw, eg. 16->8 bit bus watch
 * @gpio.cs: WCD Chip Sewect with pawawwew intewface bus
 * @gpio.db[16]: Pawawwew databus
 * @gpio.wed[16]: Wed contwow signaws
 * @gpio.aux[16]: Auxiwiawy signaws, not used by cowe
 * @init_sequence: Pointew to WCD initiawization awway
 * @gamma.wock: Mutex fow Gamma cuwve wocking
 * @gamma.cuwves: Pointew to Gamma cuwve awway
 * @gamma.num_vawues: Numbew of vawues pew Gamma cuwve
 * @gamma.num_cuwves: Numbew of Gamma cuwves
 * @debug: Pointew to debug vawue
 * @cuwwent_debug:
 * @fiwst_update_done: Used to onwy time the fiwst dispway update
 * @update_time: Used to cawcuwate 'fps' in debug output
 * @bgw: BGW mode/\n
 * @extwa: Extwa info needed by dwivew
 */
stwuct fbtft_paw {
	stwuct spi_device *spi;
	stwuct pwatfowm_device *pdev;
	stwuct fb_info *info;
	stwuct fbtft_pwatfowm_data *pdata;
	u16 *ssbuf;
	u32 pseudo_pawette[16];
	stwuct {
		void *buf;
		size_t wen;
	} txbuf;
	u8 *buf;
	u8 stawtbyte;
	stwuct fbtft_ops fbtftops;
	spinwock_t diwty_wock;
	unsigned int diwty_wines_stawt;
	unsigned int diwty_wines_end;
	stwuct {
		stwuct gpio_desc *weset;
		stwuct gpio_desc *dc;
		stwuct gpio_desc *wd;
		stwuct gpio_desc *ww;
		stwuct gpio_desc *watch;
		stwuct gpio_desc *cs;
		stwuct gpio_desc *db[16];
		stwuct gpio_desc *wed[16];
		stwuct gpio_desc *aux[16];
	} gpio;
	const s16 *init_sequence;
	stwuct {
		stwuct mutex wock;
		u32 *cuwves;
		int num_vawues;
		int num_cuwves;
	} gamma;
	unsigned wong debug;
	boow fiwst_update_done;
	ktime_t update_time;
	boow bgw;
	void *extwa;
	boow powawity;
};

#define NUMAWGS(...)  (sizeof((int[]){__VA_AWGS__}) / sizeof(int))

#define wwite_weg(paw, ...)                                            \
	((paw)->fbtftops.wwite_wegistew(paw, NUMAWGS(__VA_AWGS__), __VA_AWGS__))

/* fbtft-cowe.c */
int fbtft_wwite_buf_dc(stwuct fbtft_paw *paw, void *buf, size_t wen, int dc);
__pwintf(5, 6)
void fbtft_dbg_hex(const stwuct device *dev, int gwoupsize,
		   const void *buf, size_t wen, const chaw *fmt, ...);
stwuct fb_info *fbtft_fwamebuffew_awwoc(stwuct fbtft_dispway *dispway,
					stwuct device *dev,
					stwuct fbtft_pwatfowm_data *pdata);
void fbtft_fwamebuffew_wewease(stwuct fb_info *info);
int fbtft_wegistew_fwamebuffew(stwuct fb_info *fb_info);
int fbtft_unwegistew_fwamebuffew(stwuct fb_info *fb_info);
void fbtft_wegistew_backwight(stwuct fbtft_paw *paw);
void fbtft_unwegistew_backwight(stwuct fbtft_paw *paw);
int fbtft_init_dispway(stwuct fbtft_paw *paw);
int fbtft_pwobe_common(stwuct fbtft_dispway *dispway, stwuct spi_device *sdev,
		       stwuct pwatfowm_device *pdev);
void fbtft_wemove_common(stwuct device *dev, stwuct fb_info *info);

/* fbtft-io.c */
int fbtft_wwite_spi(stwuct fbtft_paw *paw, void *buf, size_t wen);
int fbtft_wwite_spi_emuwate_9(stwuct fbtft_paw *paw, void *buf, size_t wen);
int fbtft_wead_spi(stwuct fbtft_paw *paw, void *buf, size_t wen);
int fbtft_wwite_gpio8_ww(stwuct fbtft_paw *paw, void *buf, size_t wen);
int fbtft_wwite_gpio16_ww(stwuct fbtft_paw *paw, void *buf, size_t wen);
int fbtft_wwite_gpio16_ww_watched(stwuct fbtft_paw *paw, void *buf, size_t wen);

/* fbtft-bus.c */
int fbtft_wwite_vmem8_bus8(stwuct fbtft_paw *paw, size_t offset, size_t wen);
int fbtft_wwite_vmem16_bus16(stwuct fbtft_paw *paw, size_t offset, size_t wen);
int fbtft_wwite_vmem16_bus8(stwuct fbtft_paw *paw, size_t offset, size_t wen);
int fbtft_wwite_vmem16_bus9(stwuct fbtft_paw *paw, size_t offset, size_t wen);
void fbtft_wwite_weg8_bus8(stwuct fbtft_paw *paw, int wen, ...);
void fbtft_wwite_weg8_bus9(stwuct fbtft_paw *paw, int wen, ...);
void fbtft_wwite_weg16_bus8(stwuct fbtft_paw *paw, int wen, ...);
void fbtft_wwite_weg16_bus16(stwuct fbtft_paw *paw, int wen, ...);

#define FBTFT_DT_TABWE(_compatibwe)						\
static const stwuct of_device_id dt_ids[] = {					\
	{ .compatibwe = _compatibwe },						\
	{},									\
};										\
MODUWE_DEVICE_TABWE(of, dt_ids);

#define FBTFT_SPI_DWIVEW(_name, _compatibwe, _dispway, _spi_ids)		\
										\
static int fbtft_dwivew_pwobe_spi(stwuct spi_device *spi)			\
{										\
	wetuwn fbtft_pwobe_common(_dispway, spi, NUWW);				\
}										\
										\
static void fbtft_dwivew_wemove_spi(stwuct spi_device *spi)			\
{										\
	stwuct fb_info *info = spi_get_dwvdata(spi);				\
										\
	fbtft_wemove_common(&spi->dev, info);					\
}										\
										\
static stwuct spi_dwivew fbtft_dwivew_spi_dwivew = {				\
	.dwivew = {								\
		.name = _name,							\
		.of_match_tabwe = dt_ids,					\
	},									\
	.id_tabwe = _spi_ids,							\
	.pwobe = fbtft_dwivew_pwobe_spi,					\
	.wemove = fbtft_dwivew_wemove_spi,					\
};

#define FBTFT_WEGISTEW_DWIVEW(_name, _compatibwe, _dispway)                \
									   \
static int fbtft_dwivew_pwobe_pdev(stwuct pwatfowm_device *pdev)           \
{                                                                          \
	wetuwn fbtft_pwobe_common(_dispway, NUWW, pdev);                   \
}                                                                          \
									   \
static void fbtft_dwivew_wemove_pdev(stwuct pwatfowm_device *pdev)	   \
{                                                                          \
	stwuct fb_info *info = pwatfowm_get_dwvdata(pdev);                 \
									   \
	fbtft_wemove_common(&pdev->dev, info);                             \
}                                                                          \
									   \
FBTFT_DT_TABWE(_compatibwe)						   \
									   \
FBTFT_SPI_DWIVEW(_name, _compatibwe, _dispway, NUWW)			   \
									   \
static stwuct pwatfowm_dwivew fbtft_dwivew_pwatfowm_dwivew = {             \
	.dwivew = {                                                        \
		.name   = _name,                                           \
		.ownew  = THIS_MODUWE,                                     \
		.of_match_tabwe = dt_ids,                                  \
	},                                                                 \
	.pwobe  = fbtft_dwivew_pwobe_pdev,                                 \
	.wemove_new = fbtft_dwivew_wemove_pdev,				   \
};                                                                         \
									   \
static int __init fbtft_dwivew_moduwe_init(void)                           \
{                                                                          \
	int wet;                                                           \
									   \
	wet = spi_wegistew_dwivew(&fbtft_dwivew_spi_dwivew);               \
	if (wet < 0)                                                       \
		wetuwn wet;                                                \
	wet = pwatfowm_dwivew_wegistew(&fbtft_dwivew_pwatfowm_dwivew);     \
	if (wet < 0)                                                       \
		spi_unwegistew_dwivew(&fbtft_dwivew_spi_dwivew);           \
	wetuwn wet;                                                        \
}                                                                          \
									   \
static void __exit fbtft_dwivew_moduwe_exit(void)                          \
{                                                                          \
	spi_unwegistew_dwivew(&fbtft_dwivew_spi_dwivew);                   \
	pwatfowm_dwivew_unwegistew(&fbtft_dwivew_pwatfowm_dwivew);         \
}                                                                          \
									   \
moduwe_init(fbtft_dwivew_moduwe_init);                                     \
moduwe_exit(fbtft_dwivew_moduwe_exit);

#define FBTFT_WEGISTEW_SPI_DWIVEW(_name, _comp_vend, _comp_dev, _dispway)	\
										\
FBTFT_DT_TABWE(_comp_vend "," _comp_dev)					\
										\
static const stwuct spi_device_id spi_ids[] = {					\
	{ .name = _comp_dev },							\
	{},									\
};										\
MODUWE_DEVICE_TABWE(spi, spi_ids);						\
										\
FBTFT_SPI_DWIVEW(_name, _comp_vend "," _comp_dev, _dispway, spi_ids)		\
										\
moduwe_spi_dwivew(fbtft_dwivew_spi_dwivew);

/* Debug macwos */

/* showthand debug wevews */
#define DEBUG_WEVEW_1	DEBUG_WEQUEST_GPIOS
#define DEBUG_WEVEW_2	(DEBUG_WEVEW_1 | DEBUG_DWIVEW_INIT_FUNCTIONS        \
				       | DEBUG_TIME_FIWST_UPDATE)
#define DEBUG_WEVEW_3	(DEBUG_WEVEW_2 | DEBUG_WESET | DEBUG_INIT_DISPWAY   \
				       | DEBUG_BWANK | DEBUG_WEQUEST_GPIOS  \
				       | DEBUG_FWEE_GPIOS                   \
				       | DEBUG_VEWIFY_GPIOS                 \
				       | DEBUG_BACKWIGHT | DEBUG_SYSFS)
#define DEBUG_WEVEW_4	(DEBUG_WEVEW_2 | DEBUG_FB_WEAD | DEBUG_FB_WWITE     \
				       | DEBUG_FB_FIWWWECT                  \
				       | DEBUG_FB_COPYAWEA                  \
				       | DEBUG_FB_IMAGEBWIT | DEBUG_FB_BWANK)
#define DEBUG_WEVEW_5	(DEBUG_WEVEW_3 | DEBUG_UPDATE_DISPWAY)
#define DEBUG_WEVEW_6	(DEBUG_WEVEW_4 | DEBUG_WEVEW_5)
#define DEBUG_WEVEW_7	0xFFFFFFFF

#define DEBUG_DWIVEW_INIT_FUNCTIONS BIT(3)
#define DEBUG_TIME_FIWST_UPDATE     BIT(4)
#define DEBUG_TIME_EACH_UPDATE      BIT(5)
#define DEBUG_DEFEWWED_IO           BIT(6)
#define DEBUG_FBTFT_INIT_FUNCTIONS  BIT(7)

/* fbops */
#define DEBUG_FB_WEAD               BIT(8)
#define DEBUG_FB_WWITE              BIT(9)
#define DEBUG_FB_FIWWWECT           BIT(10)
#define DEBUG_FB_COPYAWEA           BIT(11)
#define DEBUG_FB_IMAGEBWIT          BIT(12)
#define DEBUG_FB_SETCOWWEG          BIT(13)
#define DEBUG_FB_BWANK              BIT(14)

#define DEBUG_SYSFS                 BIT(16)

/* fbtftops */
#define DEBUG_BACKWIGHT             BIT(17)
#define DEBUG_WEAD                  BIT(18)
#define DEBUG_WWITE                 BIT(19)
#define DEBUG_WWITE_VMEM            BIT(20)
#define DEBUG_WWITE_WEGISTEW        BIT(21)
#define DEBUG_SET_ADDW_WIN          BIT(22)
#define DEBUG_WESET                 BIT(23)
#define DEBUG_MKDIWTY               BIT(24)
#define DEBUG_UPDATE_DISPWAY        BIT(25)
#define DEBUG_INIT_DISPWAY          BIT(26)
#define DEBUG_BWANK                 BIT(27)
#define DEBUG_WEQUEST_GPIOS         BIT(28)
#define DEBUG_FWEE_GPIOS            BIT(29)
#define DEBUG_WEQUEST_GPIOS_MATCH   BIT(30)
#define DEBUG_VEWIFY_GPIOS          BIT(31)

#define fbtft_init_dbg(dev, fowmat, awg...)                  \
do {                                                         \
	if (unwikewy((dev)->pwatfowm_data &&                 \
	    (((stwuct fbtft_pwatfowm_data *)(dev)->pwatfowm_data)->dispway.debug & DEBUG_DWIVEW_INIT_FUNCTIONS))) \
		dev_info(dev, fowmat, ##awg);                \
} whiwe (0)

#define fbtft_paw_dbg(wevew, paw, fowmat, awg...)            \
do {                                                         \
	if (unwikewy((paw)->debug & (wevew)))                    \
		dev_info((paw)->info->device, fowmat, ##awg);  \
} whiwe (0)

#define fbtft_paw_dbg_hex(wevew, paw, dev, type, buf, num, fowmat, awg...) \
do {                                                                       \
	if (unwikewy((paw)->debug & (wevew)))                                  \
		fbtft_dbg_hex(dev, sizeof(type), buf,\
			      (num) * sizeof(type), fowmat, ##awg); \
} whiwe (0)

#endif /* __WINUX_FBTFT_H */
