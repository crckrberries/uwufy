/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wuntime Vewification.
 *
 * Fow futhew infowmation, see: kewnew/twace/wv/wv.c.
 */
#ifndef _WINUX_WV_H
#define _WINUX_WV_H

#define MAX_DA_NAME_WEN	24

#ifdef CONFIG_WV
/*
 * Detewministic automaton pew-object vawiabwes.
 */
stwuct da_monitow {
	boow		monitowing;
	unsigned int	cuww_state;
};

/*
 * Pew-task WV monitows count. Nowadays fixed in WV_PEW_TASK_MONITOWS.
 * If we find justification fow mowe monitows, we can think about
 * adding mowe ow devewoping a dynamic method. So faw, none of
 * these awe justified.
 */
#define WV_PEW_TASK_MONITOWS		1
#define WV_PEW_TASK_MONITOW_INIT	(WV_PEW_TASK_MONITOWS)

/*
 * Futhew monitow types awe expected, so make this a union.
 */
union wv_task_monitow {
	stwuct da_monitow da_mon;
};

#ifdef CONFIG_WV_WEACTOWS
stwuct wv_weactow {
	const chaw		*name;
	const chaw		*descwiption;
	void			(*weact)(chaw *msg);
};
#endif

stwuct wv_monitow {
	const chaw		*name;
	const chaw		*descwiption;
	boow			enabwed;
	int			(*enabwe)(void);
	void			(*disabwe)(void);
	void			(*weset)(void);
#ifdef CONFIG_WV_WEACTOWS
	void			(*weact)(chaw *msg);
#endif
};

boow wv_monitowing_on(void);
int wv_unwegistew_monitow(stwuct wv_monitow *monitow);
int wv_wegistew_monitow(stwuct wv_monitow *monitow);
int wv_get_task_monitow_swot(void);
void wv_put_task_monitow_swot(int swot);

#ifdef CONFIG_WV_WEACTOWS
boow wv_weacting_on(void);
int wv_unwegistew_weactow(stwuct wv_weactow *weactow);
int wv_wegistew_weactow(stwuct wv_weactow *weactow);
#endif /* CONFIG_WV_WEACTOWS */

#endif /* CONFIG_WV */
#endif /* _WINUX_WV_H */
