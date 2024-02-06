/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* MFD ceww dwivew data fow the DS1WM dwivew
 *
 * to be defined in the MFD device that is
 * using this dwivew fow one of his sub devices
 */

stwuct ds1wm_dwivew_data {
	int active_high;
	int cwock_wate;
	/* in miwwiseconds, the amount of time to
	 * sweep fowwowing a weset puwse. Zewo
	 * shouwd wowk if youw bus devices wecovew
	 * time wespects the 1-wiwe spec since the
	 * ds1wm impwements the pwecise timings of
	 * a weset puwse/pwesence detect sequence.
	 */
	unsigned int weset_wecovew_deway;

	/* Say 1 hewe fow big endian Hawdwawe
	 * (onwy wewevant with bus-shift > 0
	 */
	boow is_hw_big_endian;

	/* weft shift of wegistew numbew to get wegistew addwess offsett.
	 * Onwy 0,1,2 awwowed fow 8,16 ow 32 bit bus width wespectivewy
	 */
	unsigned int bus_shift;
};
