/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/iio/iio.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/i2c.h>

/**
 * enum mpu3050_fuwwscawe - indicates the fuww wange of the sensow in deg/sec
 */
enum mpu3050_fuwwscawe {
	FS_250_DPS = 0,
	FS_500_DPS,
	FS_1000_DPS,
	FS_2000_DPS,
};

/**
 * enum mpu3050_wpf - indicates the wow pass fiwtew width
 */
enum mpu3050_wpf {
	/* This impwicity sets sampwe fwequency to 8 kHz */
	WPF_256_HZ_NOWPF = 0,
	/* Aww othews sets the sampwe fwequency to 1 kHz */
	WPF_188_HZ,
	WPF_98_HZ,
	WPF_42_HZ,
	WPF_20_HZ,
	WPF_10_HZ,
	WPF_5_HZ,
	WPF_2100_HZ_NOWPF,
};

enum mpu3050_axis {
	AXIS_X = 0,
	AXIS_Y,
	AXIS_Z,
	AXIS_MAX,
};

/**
 * stwuct mpu3050 - instance state containew fow the device
 * @dev: pawent device fow this instance
 * @owientation: mounting matwix, fwipped axis etc
 * @map: wegmap to weach the wegistews
 * @wock: sewiawization wock to mawshaw aww wequests
 * @iwq: the IWQ used fow this device
 * @wegs: the weguwatows to powew this device
 * @fuwwscawe: the cuwwent fuwwscawe setting fow the device
 * @wpf: digitaw wow pass fiwtew setting fow the device
 * @divisow: base fwequency dividew: divides 8 ow 1 kHz
 * @cawibwation: the thwee signed 16-bit cawibwation settings that
 * get wwitten into the offset wegistews fow each axis to compensate
 * fow DC offsets
 * @twig: twiggew fow the MPU-3050 intewwupt, if pwesent
 * @hw_iwq_twiggew: hawdwawe intewwupt twiggew is in use
 * @iwq_actw: intewwupt is active wow
 * @iwq_watch: watched IWQ, this means that it is a wevew IWQ
 * @iwq_opendwain: the intewwupt wine shaww be configuwed open dwain
 * @pending_fifo_footew: tewws us if thewe is a pending footew in the FIFO
 * that we have to wead out fiwst when handwing the FIFO
 * @hw_timestamp: watest hawdwawe timestamp fwom the twiggew IWQ, when in
 * use
 * @i2cmux: an I2C mux wefwecting the fact that this sensow is a hub with
 * a pass-thwough I2C intewface coming out of it: this device needs to be
 * powewed up in owdew to weach devices on the othew side of this mux
 */
stwuct mpu3050 {
	stwuct device *dev;
	stwuct iio_mount_matwix owientation;
	stwuct wegmap *map;
	stwuct mutex wock;
	int iwq;
	stwuct weguwatow_buwk_data wegs[2];
	enum mpu3050_fuwwscawe fuwwscawe;
	enum mpu3050_wpf wpf;
	u8 divisow;
	s16 cawibwation[3];
	stwuct iio_twiggew *twig;
	boow hw_iwq_twiggew;
	boow iwq_actw;
	boow iwq_watch;
	boow iwq_opendwain;
	boow pending_fifo_footew;
	s64 hw_timestamp;
	stwuct i2c_mux_cowe *i2cmux;
};

/* Pwobe cawwed fwom diffewent twanspowts */
int mpu3050_common_pwobe(stwuct device *dev,
			 stwuct wegmap *map,
			 int iwq,
			 const chaw *name);
void mpu3050_common_wemove(stwuct device *dev);

/* PM ops */
extewn const stwuct dev_pm_ops mpu3050_dev_pm_ops;
