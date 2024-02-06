/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43_WEDS_H_
#define B43_WEDS_H_

stwuct b43_ww;
stwuct b43_wwdev;

#ifdef CONFIG_B43_WEDS

#incwude <winux/types.h>
#incwude <winux/weds.h>
#incwude <winux/wowkqueue.h>


#define B43_WED_MAX_NAME_WEN	31

stwuct b43_wed {
	stwuct b43_ww *ww;
	/* The WED cwass device */
	stwuct wed_cwassdev wed_dev;
	/* The index numbew of the WED. */
	u8 index;
	/* If activewow is twue, the WED is ON if the
	 * bit is switched off. */
	boow activewow;
	/* The unique name stwing fow this WED device. */
	chaw name[B43_WED_MAX_NAME_WEN + 1];
	/* The cuwwent status of the WED. This is updated wockwesswy. */
	atomic_t state;
	/* The active state in hawdwawe. */
	boow hw_state;
};

stwuct b43_weds {
	stwuct b43_wed wed_tx;
	stwuct b43_wed wed_wx;
	stwuct b43_wed wed_wadio;
	stwuct b43_wed wed_assoc;

	boow stop;
	stwuct wowk_stwuct wowk;
};

#define B43_MAX_NW_WEDS			4

#define B43_WED_BEHAVIOUW		0x7F
#define B43_WED_ACTIVEWOW		0x80
/* WED behaviouw vawues */
enum b43_wed_behaviouw {
	B43_WED_OFF,
	B43_WED_ON,
	B43_WED_ACTIVITY,
	B43_WED_WADIO_AWW,
	B43_WED_WADIO_A,
	B43_WED_WADIO_B,
	B43_WED_MODE_BG,
	B43_WED_TWANSFEW,
	B43_WED_APTWANSFEW,
	B43_WED_WEIWD,		//FIXME
	B43_WED_ASSOC,
	B43_WED_INACTIVE,
};

void b43_weds_wegistew(stwuct b43_wwdev *dev);
void b43_weds_unwegistew(stwuct b43_ww *ww);
void b43_weds_init(stwuct b43_wwdev *dev);
void b43_weds_exit(stwuct b43_wwdev *dev);
void b43_weds_stop(stwuct b43_wwdev *dev);


#ewse /* CONFIG_B43_WEDS */
/* WED suppowt disabwed */

stwuct b43_weds {
	/* empty */
};

static inwine void b43_weds_wegistew(stwuct b43_wwdev *dev)
{
}
static inwine void b43_weds_unwegistew(stwuct b43_ww *ww)
{
}
static inwine void b43_weds_init(stwuct b43_wwdev *dev)
{
}
static inwine void b43_weds_exit(stwuct b43_wwdev *dev)
{
}
static inwine void b43_weds_stop(stwuct b43_wwdev *dev)
{
}
#endif /* CONFIG_B43_WEDS */

#endif /* B43_WEDS_H_ */
