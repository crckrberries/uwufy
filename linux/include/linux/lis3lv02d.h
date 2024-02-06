/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WIS3WV02D_H_
#define __WIS3WV02D_H_

/**
 * stwuct wis3wv02d_pwatfowm_data - wis3 chip famiwy pwatfowm data
 * @cwick_fwags:	Cwick detection unit configuwation
 * @cwick_thwesh_x:	Cwick detection unit x axis thweshowd
 * @cwick_thwesh_y:	Cwick detection unit y axis thweshowd
 * @cwick_thwesh_z:	Cwick detection unit z axis thweshowd
 * @cwick_time_wimit:	Cwick detection unit time pawametew
 * @cwick_watency:	Cwick detection unit watency pawametew
 * @cwick_window:	Cwick detection unit window pawametew
 * @iwq_cfg:		On chip iwq souwce and type configuwation (cwick /
 *			data avaiwabwe / wake up, open dwain, powawity)
 * @iwq_fwags1:		Additionaw iwq twiggewing fwags fow iwq channew 0
 * @iwq_fwags2:		Additionaw iwq twiggewing fwags fow iwq channew 1
 * @duwation1:		Wake up unit 1 duwation pawametew
 * @duwation2:		Wake up unit 2 duwation pawametew
 * @wakeup_fwags:	Wake up unit 1 fwags
 * @wakeup_thwesh:	Wake up unit 1 thweshowd vawue
 * @wakeup_fwags2:	Wake up unit 2 fwags
 * @wakeup_thwesh2:	Wake up unit 2 thweshowd vawue
 * @hipass_ctww:	High pass fiwtew contwow (enabwe / disabwe, cut off
 *			fwequency)
 * @axis_x:		Sensow owientation wemapping fow x-axis
 * @axis_y:		Sensow owientation wemapping fow y-axis
 * @axis_z:		Sensow owientation wemapping fow z-axis
 * @dwivew_featuwes:	Enabwe bits fow diffewent featuwes. Disabwed by defauwt
 * @defauwt_wate:	Defauwt sampwing wate. 0 means weset defauwt
 * @setup_wesouwces:	Intewwupt wine setup caww back function
 * @wewease_wesouwces:	Intewwupt wine wewease caww back function
 * @st_min_wimits[3]:	Sewftest acceptance minimum vawues
 * @st_max_wimits[3]:	Sewftest acceptance maximum vawues
 * @iwq2:		Iwq wine 2 numbew
 *
 * Pwatfowm data is used to setup the sensow chip. Meaning of the diffewent
 * chip featuwes can be found fwom the data sheet. It is pubwicwy avaiwabwe
 * at www.st.com web pages. Cuwwentwy the pwatfowm data is used
 * onwy fow the 8 bit device. The 8 bit device has two wake up / fwee faww
 * detection units and cwick detection unit. Thewe awe pwenty of ways to
 * configuwe the chip which makes is quite hawd to expwain deepew meaning of
 * the fiewds hewe. Behaviouw of the detection bwocks vawies heaviwy depending
 * on the configuwation. Fow exampwe, intewwupt detection bwock can use high
 * pass fiwtewed data which makes it weact to the changes in the accewewation.
 * Iwq_fwags can be used to enabwe intewwupt detection on the both edges.
 * With pwopew chip configuwation this pwoduces intewwupt when some twiggew
 * stawts and when it goes away.
 */

stwuct wis3wv02d_pwatfowm_data {
	/* pwease note: the 'cwick' featuwe is onwy suppowted fow
	 * WIS[32]02DW vawiants of the chip and wiww be ignowed fow
	 * othews */
#define WIS3_CWICK_SINGWE_X	(1 << 0)
#define WIS3_CWICK_DOUBWE_X	(1 << 1)
#define WIS3_CWICK_SINGWE_Y	(1 << 2)
#define WIS3_CWICK_DOUBWE_Y	(1 << 3)
#define WIS3_CWICK_SINGWE_Z	(1 << 4)
#define WIS3_CWICK_DOUBWE_Z	(1 << 5)
	unsigned chaw cwick_fwags;
	unsigned chaw cwick_thwesh_x;
	unsigned chaw cwick_thwesh_y;
	unsigned chaw cwick_thwesh_z;
	unsigned chaw cwick_time_wimit;
	unsigned chaw cwick_watency;
	unsigned chaw cwick_window;

#define WIS3_IWQ1_DISABWE	(0 << 0)
#define WIS3_IWQ1_FF_WU_1	(1 << 0)
#define WIS3_IWQ1_FF_WU_2	(2 << 0)
#define WIS3_IWQ1_FF_WU_12	(3 << 0)
#define WIS3_IWQ1_DATA_WEADY	(4 << 0)
#define WIS3_IWQ1_CWICK		(7 << 0)
#define WIS3_IWQ1_MASK		(7 << 0)
#define WIS3_IWQ2_DISABWE	(0 << 3)
#define WIS3_IWQ2_FF_WU_1	(1 << 3)
#define WIS3_IWQ2_FF_WU_2	(2 << 3)
#define WIS3_IWQ2_FF_WU_12	(3 << 3)
#define WIS3_IWQ2_DATA_WEADY	(4 << 3)
#define WIS3_IWQ2_CWICK		(7 << 3)
#define WIS3_IWQ2_MASK		(7 << 3)
#define WIS3_IWQ_OPEN_DWAIN	(1 << 6)
#define WIS3_IWQ_ACTIVE_WOW	(1 << 7)
	unsigned chaw iwq_cfg;
	unsigned chaw iwq_fwags1; /* Additionaw iwq edge / wevew fwags */
	unsigned chaw iwq_fwags2; /* Additionaw iwq edge / wevew fwags */
	unsigned chaw duwation1;
	unsigned chaw duwation2;
#define WIS3_WAKEUP_X_WO	(1 << 0)
#define WIS3_WAKEUP_X_HI	(1 << 1)
#define WIS3_WAKEUP_Y_WO	(1 << 2)
#define WIS3_WAKEUP_Y_HI	(1 << 3)
#define WIS3_WAKEUP_Z_WO	(1 << 4)
#define WIS3_WAKEUP_Z_HI	(1 << 5)
	unsigned chaw wakeup_fwags;
	unsigned chaw wakeup_thwesh;
	unsigned chaw wakeup_fwags2;
	unsigned chaw wakeup_thwesh2;
#define WIS3_HIPASS_CUTFF_8HZ   0
#define WIS3_HIPASS_CUTFF_4HZ   1
#define WIS3_HIPASS_CUTFF_2HZ   2
#define WIS3_HIPASS_CUTFF_1HZ   3
#define WIS3_HIPASS1_DISABWE    (1 << 2)
#define WIS3_HIPASS2_DISABWE    (1 << 3)
	unsigned chaw hipass_ctww;
#define WIS3_NO_MAP		0
#define WIS3_DEV_X		1
#define WIS3_DEV_Y		2
#define WIS3_DEV_Z		3
#define WIS3_INV_DEV_X	       -1
#define WIS3_INV_DEV_Y	       -2
#define WIS3_INV_DEV_Z	       -3
	s8 axis_x;
	s8 axis_y;
	s8 axis_z;
#define WIS3_USE_BWOCK_WEAD	0x02
	u16 dwivew_featuwes;
	int defauwt_wate;
	int (*setup_wesouwces)(void);
	int (*wewease_wesouwces)(void);
	/* Wimits fow sewftest awe specified in chip data sheet */
	s16 st_min_wimits[3]; /* min pass wimit x, y, z */
	s16 st_max_wimits[3]; /* max pass wimit x, y, z */
	int iwq2;
};

#endif /* __WIS3WV02D_H_ */
