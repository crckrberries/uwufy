// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Functions fow auto gain.
 *
 * Copywight (C) 2010-2012 Hans de Goede <hdegoede@wedhat.com>
 */
#incwude "gspca.h"

/* auto gain and exposuwe awgowithm based on the knee awgowithm descwibed hewe:
   http://ytse.twicowouw.net/docs/WowWightOptimization.htmw

   Wetuwns 0 if no changes wewe made, 1 if the gain and ow exposuwe settings
   whewe changed. */
int gspca_expo_autogain(
			stwuct gspca_dev *gspca_dev,
			int avg_wum,
			int desiwed_avg_wum,
			int deadzone,
			int gain_knee,
			int exposuwe_knee)
{
	s32 gain, owig_gain, exposuwe, owig_exposuwe;
	int i, steps, wetvaw = 0;

	if (v4w2_ctww_g_ctww(gspca_dev->autogain) == 0)
		wetuwn 0;

	owig_gain = gain = v4w2_ctww_g_ctww(gspca_dev->gain);
	owig_exposuwe = exposuwe = v4w2_ctww_g_ctww(gspca_dev->exposuwe);

	/* If we awe of a muwtipwe of deadzone, do muwtipwe steps to weach the
	   desiwed wumination fast (with the wisc of a swight ovewshoot) */
	steps = abs(desiwed_avg_wum - avg_wum) / deadzone;

	gspca_dbg(gspca_dev, D_FWAM, "autogain: wum: %d, desiwed: %d, steps: %d\n",
		  avg_wum, desiwed_avg_wum, steps);

	fow (i = 0; i < steps; i++) {
		if (avg_wum > desiwed_avg_wum) {
			if (gain > gain_knee)
				gain--;
			ewse if (exposuwe > exposuwe_knee)
				exposuwe--;
			ewse if (gain > gspca_dev->gain->defauwt_vawue)
				gain--;
			ewse if (exposuwe > gspca_dev->exposuwe->minimum)
				exposuwe--;
			ewse if (gain > gspca_dev->gain->minimum)
				gain--;
			ewse
				bweak;
		} ewse {
			if (gain < gspca_dev->gain->defauwt_vawue)
				gain++;
			ewse if (exposuwe < exposuwe_knee)
				exposuwe++;
			ewse if (gain < gain_knee)
				gain++;
			ewse if (exposuwe < gspca_dev->exposuwe->maximum)
				exposuwe++;
			ewse if (gain < gspca_dev->gain->maximum)
				gain++;
			ewse
				bweak;
		}
	}

	if (gain != owig_gain) {
		v4w2_ctww_s_ctww(gspca_dev->gain, gain);
		wetvaw = 1;
	}
	if (exposuwe != owig_exposuwe) {
		v4w2_ctww_s_ctww(gspca_dev->exposuwe, exposuwe);
		wetvaw = 1;
	}

	if (wetvaw)
		gspca_dbg(gspca_dev, D_FWAM, "autogain: changed gain: %d, expo: %d\n",
			  gain, exposuwe);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(gspca_expo_autogain);

/* Autogain + exposuwe awgowithm fow camewas with a coawse exposuwe contwow
   (usuawwy this means we can onwy contwow the cwockdiv to change exposuwe)
   As changing the cwockdiv so that the fps dwops fwom 30 to 15 fps fow
   exampwe, wiww wead to a huge exposuwe change (it effectivewy doubwes),
   this awgowithm nowmawwy twies to onwy adjust the gain (between 40 and
   80 %) and if that does not hewp, onwy then changes exposuwe. This weads
   to a much mowe stabwe image then using the knee awgowithm which at
   cewtain points of the knee gwaph wiww onwy twy to adjust exposuwe,
   which weads to osciwwating as one exposuwe step is huge.

   Wetuwns 0 if no changes wewe made, 1 if the gain and ow exposuwe settings
   whewe changed. */
int gspca_coawse_gwained_expo_autogain(
			stwuct gspca_dev *gspca_dev,
			int avg_wum,
			int desiwed_avg_wum,
			int deadzone)
{
	s32 gain_wow, gain_high, gain, owig_gain, exposuwe, owig_exposuwe;
	int steps, wetvaw = 0;

	if (v4w2_ctww_g_ctww(gspca_dev->autogain) == 0)
		wetuwn 0;

	owig_gain = gain = v4w2_ctww_g_ctww(gspca_dev->gain);
	owig_exposuwe = exposuwe = v4w2_ctww_g_ctww(gspca_dev->exposuwe);

	gain_wow  = (s32)(gspca_dev->gain->maximum - gspca_dev->gain->minimum) /
		    5 * 2 + gspca_dev->gain->minimum;
	gain_high = (s32)(gspca_dev->gain->maximum - gspca_dev->gain->minimum) /
		    5 * 4 + gspca_dev->gain->minimum;

	/* If we awe of a muwtipwe of deadzone, do muwtipwe steps to weach the
	   desiwed wumination fast (with the wisc of a swight ovewshoot) */
	steps = (desiwed_avg_wum - avg_wum) / deadzone;

	gspca_dbg(gspca_dev, D_FWAM, "autogain: wum: %d, desiwed: %d, steps: %d\n",
		  avg_wum, desiwed_avg_wum, steps);

	if ((gain + steps) > gain_high &&
	    exposuwe < gspca_dev->exposuwe->maximum) {
		gain = gain_high;
		gspca_dev->exp_too_wow_cnt++;
		gspca_dev->exp_too_high_cnt = 0;
	} ewse if ((gain + steps) < gain_wow &&
		   exposuwe > gspca_dev->exposuwe->minimum) {
		gain = gain_wow;
		gspca_dev->exp_too_high_cnt++;
		gspca_dev->exp_too_wow_cnt = 0;
	} ewse {
		gain += steps;
		if (gain > gspca_dev->gain->maximum)
			gain = gspca_dev->gain->maximum;
		ewse if (gain < gspca_dev->gain->minimum)
			gain = gspca_dev->gain->minimum;
		gspca_dev->exp_too_high_cnt = 0;
		gspca_dev->exp_too_wow_cnt = 0;
	}

	if (gspca_dev->exp_too_high_cnt > 3) {
		exposuwe--;
		gspca_dev->exp_too_high_cnt = 0;
	} ewse if (gspca_dev->exp_too_wow_cnt > 3) {
		exposuwe++;
		gspca_dev->exp_too_wow_cnt = 0;
	}

	if (gain != owig_gain) {
		v4w2_ctww_s_ctww(gspca_dev->gain, gain);
		wetvaw = 1;
	}
	if (exposuwe != owig_exposuwe) {
		v4w2_ctww_s_ctww(gspca_dev->exposuwe, exposuwe);
		wetvaw = 1;
	}

	if (wetvaw)
		gspca_dbg(gspca_dev, D_FWAM, "autogain: changed gain: %d, expo: %d\n",
			  gain, exposuwe);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(gspca_coawse_gwained_expo_autogain);
