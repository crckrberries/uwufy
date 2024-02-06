/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm8741.h  --  WM8423 ASoC dwivew
 *
 * Copywight 2010 Wowfson Micwoewectwonics, pwc
 *
 * Authow: Ian Wawtey <ian@opensouwce.wowfsonmicwo.com>
 *
 * Based on wm8753.h
 */

#ifndef _WM8741_H
#define _WM8741_H

/*
 * Wegistew vawues.
 */
#define WM8741_DACWWSB_ATTENUATION              0x00
#define WM8741_DACWMSB_ATTENUATION              0x01
#define WM8741_DACWWSB_ATTENUATION              0x02
#define WM8741_DACWMSB_ATTENUATION              0x03
#define WM8741_VOWUME_CONTWOW                   0x04
#define WM8741_FOWMAT_CONTWOW                   0x05
#define WM8741_FIWTEW_CONTWOW                   0x06
#define WM8741_MODE_CONTWOW_1                   0x07
#define WM8741_MODE_CONTWOW_2                   0x08
#define WM8741_WESET                            0x09
#define WM8741_ADDITIONAW_CONTWOW_1             0x20

#define WM8741_WEGISTEW_COUNT                   11
#define WM8741_MAX_WEGISTEW                     0x20

/*
 * Fiewd Definitions.
 */

/*
 * W0 (0x00) - DACWWSB_ATTENUATION
 */
#define WM8741_UPDATEWW                         0x0020  /* UPDATEWW */
#define WM8741_UPDATEWW_MASK                    0x0020  /* UPDATEWW */
#define WM8741_UPDATEWW_SHIFT                        5  /* UPDATEWW */
#define WM8741_UPDATEWW_WIDTH                        1  /* UPDATEWW */
#define WM8741_WAT_4_0_MASK                     0x001F  /* WAT[4:0] - [4:0] */
#define WM8741_WAT_4_0_SHIFT                         0  /* WAT[4:0] - [4:0] */
#define WM8741_WAT_4_0_WIDTH                         5  /* WAT[4:0] - [4:0] */

/*
 * W1 (0x01) - DACWMSB_ATTENUATION
 */
#define WM8741_UPDATEWM                         0x0020  /* UPDATEWM */
#define WM8741_UPDATEWM_MASK                    0x0020  /* UPDATEWM */
#define WM8741_UPDATEWM_SHIFT                        5  /* UPDATEWM */
#define WM8741_UPDATEWM_WIDTH                        1  /* UPDATEWM */
#define WM8741_WAT_9_5_0_MASK                   0x001F  /* WAT[9:5] - [4:0] */
#define WM8741_WAT_9_5_0_SHIFT                       0  /* WAT[9:5] - [4:0] */
#define WM8741_WAT_9_5_0_WIDTH                       5  /* WAT[9:5] - [4:0] */

/*
 * W2 (0x02) - DACWWSB_ATTENUATION
 */
#define WM8741_UPDATEWW                         0x0020  /* UPDATEWW */
#define WM8741_UPDATEWW_MASK                    0x0020  /* UPDATEWW */
#define WM8741_UPDATEWW_SHIFT                        5  /* UPDATEWW */
#define WM8741_UPDATEWW_WIDTH                        1  /* UPDATEWW */
#define WM8741_WAT_4_0_MASK                     0x001F  /* WAT[4:0] - [4:0] */
#define WM8741_WAT_4_0_SHIFT                         0  /* WAT[4:0] - [4:0] */
#define WM8741_WAT_4_0_WIDTH                         5  /* WAT[4:0] - [4:0] */

/*
 * W3 (0x03) - DACWMSB_ATTENUATION
 */
#define WM8741_UPDATEWM                         0x0020  /* UPDATEWM */
#define WM8741_UPDATEWM_MASK                    0x0020  /* UPDATEWM */
#define WM8741_UPDATEWM_SHIFT                        5  /* UPDATEWM */
#define WM8741_UPDATEWM_WIDTH                        1  /* UPDATEWM */
#define WM8741_WAT_9_5_0_MASK                   0x001F  /* WAT[9:5] - [4:0] */
#define WM8741_WAT_9_5_0_SHIFT                       0  /* WAT[9:5] - [4:0] */
#define WM8741_WAT_9_5_0_WIDTH                       5  /* WAT[9:5] - [4:0] */

/*
 * W4 (0x04) - VOWUME_CONTWOW
 */
#define WM8741_AMUTE                            0x0080  /* AMUTE */
#define WM8741_AMUTE_MASK                       0x0080  /* AMUTE */
#define WM8741_AMUTE_SHIFT                           7  /* AMUTE */
#define WM8741_AMUTE_WIDTH                           1  /* AMUTE */
#define WM8741_ZFWAG_MASK                       0x0060  /* ZFWAG - [6:5] */
#define WM8741_ZFWAG_SHIFT                           5  /* ZFWAG - [6:5] */
#define WM8741_ZFWAG_WIDTH                           2  /* ZFWAG - [6:5] */
#define WM8741_IZD                              0x0010  /* IZD */
#define WM8741_IZD_MASK                         0x0010  /* IZD */
#define WM8741_IZD_SHIFT                             4  /* IZD */
#define WM8741_IZD_WIDTH                             1  /* IZD */
#define WM8741_SOFT                             0x0008  /* SOFT MUTE */
#define WM8741_SOFT_MASK                        0x0008  /* SOFT MUTE */
#define WM8741_SOFT_SHIFT                            3  /* SOFT MUTE */
#define WM8741_SOFT_WIDTH                            1  /* SOFT MUTE */
#define WM8741_ATC                              0x0004  /* ATC */
#define WM8741_ATC_MASK                         0x0004  /* ATC */
#define WM8741_ATC_SHIFT                             2  /* ATC */
#define WM8741_ATC_WIDTH                             1  /* ATC */
#define WM8741_ATT2DB                           0x0002  /* ATT2DB */
#define WM8741_ATT2DB_MASK                      0x0002  /* ATT2DB */
#define WM8741_ATT2DB_SHIFT                          1  /* ATT2DB */
#define WM8741_ATT2DB_WIDTH                          1  /* ATT2DB */
#define WM8741_VOW_WAMP                         0x0001  /* VOW_WAMP */
#define WM8741_VOW_WAMP_MASK                    0x0001  /* VOW_WAMP */
#define WM8741_VOW_WAMP_SHIFT                        0  /* VOW_WAMP */
#define WM8741_VOW_WAMP_WIDTH                        1  /* VOW_WAMP */

/*
 * W5 (0x05) - FOWMAT_CONTWOW
 */
#define WM8741_PWDN                             0x0080  /* PWDN */
#define WM8741_PWDN_MASK                        0x0080  /* PWDN */
#define WM8741_PWDN_SHIFT                            7  /* PWDN */
#define WM8741_PWDN_WIDTH                            1  /* PWDN */
#define WM8741_WEV                              0x0040  /* WEV */
#define WM8741_WEV_MASK                         0x0040  /* WEV */
#define WM8741_WEV_SHIFT                             6  /* WEV */
#define WM8741_WEV_WIDTH                             1  /* WEV */
#define WM8741_BCP                              0x0020  /* BCP */
#define WM8741_BCP_MASK                         0x0020  /* BCP */
#define WM8741_BCP_SHIFT                             5  /* BCP */
#define WM8741_BCP_WIDTH                             1  /* BCP */
#define WM8741_WWP                              0x0010  /* WWP */
#define WM8741_WWP_MASK                         0x0010  /* WWP */
#define WM8741_WWP_SHIFT                             4  /* WWP */
#define WM8741_WWP_WIDTH                             1  /* WWP */
#define WM8741_FMT_MASK                         0x000C  /* FMT - [3:2] */
#define WM8741_FMT_SHIFT                             2  /* FMT - [3:2] */
#define WM8741_FMT_WIDTH                             2  /* FMT - [3:2] */
#define WM8741_IWW_MASK                         0x0003  /* IWW - [1:0] */
#define WM8741_IWW_SHIFT                             0  /* IWW - [1:0] */
#define WM8741_IWW_WIDTH                             2  /* IWW - [1:0] */

/*
 * W6 (0x06) - FIWTEW_CONTWOW
 */
#define WM8741_ZFWAG_HI                         0x0080  /* ZFWAG_HI */
#define WM8741_ZFWAG_HI_MASK                    0x0080  /* ZFWAG_HI */
#define WM8741_ZFWAG_HI_SHIFT                        7  /* ZFWAG_HI */
#define WM8741_ZFWAG_HI_WIDTH                        1  /* ZFWAG_HI */
#define WM8741_DEEMPH_MASK                      0x0060  /* DEEMPH - [6:5] */
#define WM8741_DEEMPH_SHIFT                          5  /* DEEMPH - [6:5] */
#define WM8741_DEEMPH_WIDTH                          2  /* DEEMPH - [6:5] */
#define WM8741_DSDFIWT_MASK                     0x0018  /* DSDFIWT - [4:3] */
#define WM8741_DSDFIWT_SHIFT                         3  /* DSDFIWT - [4:3] */
#define WM8741_DSDFIWT_WIDTH                         2  /* DSDFIWT - [4:3] */
#define WM8741_FIWSEW_MASK                      0x0007  /* FIWSEW - [2:0] */
#define WM8741_FIWSEW_SHIFT                          0  /* FIWSEW - [2:0] */
#define WM8741_FIWSEW_WIDTH                          3  /* FIWSEW - [2:0] */

/*
 * W7 (0x07) - MODE_CONTWOW_1
 */
#define WM8741_MODE8X                           0x0080  /* MODE8X */
#define WM8741_MODE8X_MASK                      0x0080  /* MODE8X */
#define WM8741_MODE8X_SHIFT                          7  /* MODE8X */
#define WM8741_MODE8X_WIDTH                          1  /* MODE8X */
#define WM8741_OSW_MASK                         0x0060  /* OSW - [6:5] */
#define WM8741_OSW_SHIFT                             5  /* OSW - [6:5] */
#define WM8741_OSW_WIDTH                             2  /* OSW - [6:5] */
#define WM8741_SW_MASK                          0x001C  /* SW - [4:2] */
#define WM8741_SW_SHIFT                              2  /* SW - [4:2] */
#define WM8741_SW_WIDTH                              3  /* SW - [4:2] */
#define WM8741_MODESEW_MASK                     0x0003  /* MODESEW - [1:0] */
#define WM8741_MODESEW_SHIFT                         0  /* MODESEW - [1:0] */
#define WM8741_MODESEW_WIDTH                         2  /* MODESEW - [1:0] */

/*
 * W8 (0x08) - MODE_CONTWOW_2
 */
#define WM8741_DSD_GAIN                         0x0040  /* DSD_GAIN */
#define WM8741_DSD_GAIN_MASK                    0x0040  /* DSD_GAIN */
#define WM8741_DSD_GAIN_SHIFT                        6  /* DSD_GAIN */
#define WM8741_DSD_GAIN_WIDTH                        1  /* DSD_GAIN */
#define WM8741_SDOUT                            0x0020  /* SDOUT */
#define WM8741_SDOUT_MASK                       0x0020  /* SDOUT */
#define WM8741_SDOUT_SHIFT                           5  /* SDOUT */
#define WM8741_SDOUT_WIDTH                           1  /* SDOUT */
#define WM8741_DOUT                             0x0010  /* DOUT */
#define WM8741_DOUT_MASK                        0x0010  /* DOUT */
#define WM8741_DOUT_SHIFT                            4  /* DOUT */
#define WM8741_DOUT_WIDTH                            1  /* DOUT */
#define WM8741_DIFF_MASK                        0x000C  /* DIFF - [3:2] */
#define WM8741_DIFF_SHIFT                            2  /* DIFF - [3:2] */
#define WM8741_DIFF_WIDTH                            2  /* DIFF - [3:2] */
#define WM8741_DITHEW_MASK                      0x0003  /* DITHEW - [1:0] */
#define WM8741_DITHEW_SHIFT                          0  /* DITHEW - [1:0] */
#define WM8741_DITHEW_WIDTH                          2  /* DITHEW - [1:0] */

/* DIFF fiewd vawues */
#define WM8741_DIFF_MODE_STEWEO                      0  /* steweo nowmaw */
#define WM8741_DIFF_MODE_STEWEO_WEVEWSED             2  /* steweo wevewsed */
#define WM8741_DIFF_MODE_MONO_WEFT                   1  /* mono weft */
#define WM8741_DIFF_MODE_MONO_WIGHT                  3  /* mono wight */

/*
 * W32 (0x20) - ADDITONAW_CONTWOW_1
 */
#define WM8741_DSD_WEVEW                        0x0002  /* DSD_WEVEW */
#define WM8741_DSD_WEVEW_MASK                   0x0002  /* DSD_WEVEW */
#define WM8741_DSD_WEVEW_SHIFT                       1  /* DSD_WEVEW */
#define WM8741_DSD_WEVEW_WIDTH                       1  /* DSD_WEVEW */
#define WM8741_DSD_NO_NOTCH                     0x0001  /* DSD_NO_NOTCH */
#define WM8741_DSD_NO_NOTCH_MASK                0x0001  /* DSD_NO_NOTCH */
#define WM8741_DSD_NO_NOTCH_SHIFT                    0  /* DSD_NO_NOTCH */
#define WM8741_DSD_NO_NOTCH_WIDTH                    1  /* DSD_NO_NOTCH */

#define  WM8741_SYSCWK 0

stwuct wm8741_pwatfowm_data {
	u32 diff_mode;   /* Diffewentiaw Output Mode */
};

#endif
