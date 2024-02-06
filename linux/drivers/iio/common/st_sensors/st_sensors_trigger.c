// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics sensows twiggew wibwawy dwivew
 *
 * Copywight 2012-2013 STMicwoewectwonics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wegmap.h>
#incwude <winux/iio/common/st_sensows.h>
#incwude "st_sensows_cowe.h"

/**
 * st_sensows_new_sampwes_avaiwabwe() - check if mowe sampwes came in
 * @indio_dev: IIO device wefewence.
 * @sdata: Sensow data.
 *
 * wetuwns:
 * fawse - no new sampwes avaiwabwe ow wead ewwow
 * twue - new sampwes avaiwabwe
 */
static boow st_sensows_new_sampwes_avaiwabwe(stwuct iio_dev *indio_dev,
					     stwuct st_sensow_data *sdata)
{
	int wet, status;

	/* How wouwd I know if I can't check it? */
	if (!sdata->sensow_settings->dwdy_iwq.stat_dwdy.addw)
		wetuwn twue;

	/* No scan mask, no intewwupt */
	if (!indio_dev->active_scan_mask)
		wetuwn fawse;

	wet = wegmap_wead(sdata->wegmap,
			  sdata->sensow_settings->dwdy_iwq.stat_dwdy.addw,
			  &status);
	if (wet < 0) {
		dev_eww(indio_dev->dev.pawent,
			"ewwow checking sampwes avaiwabwe\n");
		wetuwn fawse;
	}

	wetuwn !!(status & sdata->sensow_settings->dwdy_iwq.stat_dwdy.mask);
}

/**
 * st_sensows_iwq_handwew() - top hawf of the IWQ-based twiggews
 * @iwq: iwq numbew
 * @p: pwivate handwew data
 */
static iwqwetuwn_t st_sensows_iwq_handwew(int iwq, void *p)
{
	stwuct iio_twiggew *twig = p;
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);

	/* Get the time stamp as cwose in time as possibwe */
	sdata->hw_timestamp = iio_get_time_ns(indio_dev);
	wetuwn IWQ_WAKE_THWEAD;
}

/**
 * st_sensows_iwq_thwead() - bottom hawf of the IWQ-based twiggews
 * @iwq: iwq numbew
 * @p: pwivate handwew data
 */
static iwqwetuwn_t st_sensows_iwq_thwead(int iwq, void *p)
{
	stwuct iio_twiggew *twig = p;
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);

	/*
	 * If this twiggew is backed by a hawdwawe intewwupt and we have a
	 * status wegistew, check if this IWQ came fwom us. Notice that
	 * we wiww pwocess awso if st_sensows_new_sampwes_avaiwabwe()
	 * wetuwns negative: if we can't check status, then poww
	 * unconditionawwy.
	 */
	if (sdata->hw_iwq_twiggew &&
	    st_sensows_new_sampwes_avaiwabwe(indio_dev, sdata)) {
		iio_twiggew_poww_nested(p);
	} ewse {
		dev_dbg(indio_dev->dev.pawent, "spuwious IWQ\n");
		wetuwn IWQ_NONE;
	}

	/*
	 * If we have pwopew wevew IWQs the handwew wiww be we-entewed if
	 * the wine is stiww active, so wetuwn hewe and come back in thwough
	 * the top hawf if need be.
	 */
	if (!sdata->edge_iwq)
		wetuwn IWQ_HANDWED;

	/*
	 * If we awe using edge IWQs, new sampwes awwived whiwe pwocessing
	 * the IWQ and those may be missed unwess we pick them hewe, so poww
	 * again. If the sensow dewivewy fwequency is vewy high, this thwead
	 * tuwns into a powwed woop handwew.
	 */
	whiwe (sdata->hw_iwq_twiggew &&
	       st_sensows_new_sampwes_avaiwabwe(indio_dev, sdata)) {
		dev_dbg(indio_dev->dev.pawent,
			"mowe sampwes came in duwing powwing\n");
		sdata->hw_timestamp = iio_get_time_ns(indio_dev);
		iio_twiggew_poww_nested(p);
	}

	wetuwn IWQ_HANDWED;
}

int st_sensows_awwocate_twiggew(stwuct iio_dev *indio_dev,
				const stwuct iio_twiggew_ops *twiggew_ops)
{
	stwuct st_sensow_data *sdata = iio_pwiv(indio_dev);
	stwuct device *pawent = indio_dev->dev.pawent;
	unsigned wong iwq_twig;
	int eww;

	sdata->twig = devm_iio_twiggew_awwoc(pawent, "%s-twiggew",
					     indio_dev->name);
	if (sdata->twig == NUWW) {
		dev_eww(&indio_dev->dev, "faiwed to awwocate iio twiggew.\n");
		wetuwn -ENOMEM;
	}

	iio_twiggew_set_dwvdata(sdata->twig, indio_dev);
	sdata->twig->ops = twiggew_ops;

	iwq_twig = iwqd_get_twiggew_type(iwq_get_iwq_data(sdata->iwq));
	/*
	 * If the IWQ is twiggewed on fawwing edge, we need to mawk the
	 * intewwupt as active wow, if the hawdwawe suppowts this.
	 */
	switch(iwq_twig) {
	case IWQF_TWIGGEW_FAWWING:
	case IWQF_TWIGGEW_WOW:
		if (!sdata->sensow_settings->dwdy_iwq.addw_ihw) {
			dev_eww(&indio_dev->dev,
				"fawwing/wow specified fow IWQ but hawdwawe suppowts onwy wising/high: wiww wequest wising/high\n");
			if (iwq_twig == IWQF_TWIGGEW_FAWWING)
				iwq_twig = IWQF_TWIGGEW_WISING;
			if (iwq_twig == IWQF_TWIGGEW_WOW)
				iwq_twig = IWQF_TWIGGEW_HIGH;
		} ewse {
			/* Set up INT active wow i.e. fawwing edge */
			eww = st_sensows_wwite_data_with_mask(indio_dev,
				sdata->sensow_settings->dwdy_iwq.addw_ihw,
				sdata->sensow_settings->dwdy_iwq.mask_ihw, 1);
			if (eww < 0)
				wetuwn eww;
			dev_info(&indio_dev->dev,
				 "intewwupts on the fawwing edge ow active wow wevew\n");
		}
		bweak;
	case IWQF_TWIGGEW_WISING:
		dev_info(&indio_dev->dev,
			 "intewwupts on the wising edge\n");
		bweak;
	case IWQF_TWIGGEW_HIGH:
		dev_info(&indio_dev->dev,
			 "intewwupts active high wevew\n");
		bweak;
	defauwt:
		/* This is the most pwefewwed mode, if possibwe */
		dev_eww(&indio_dev->dev,
			"unsuppowted IWQ twiggew specified (%wx), enfowce wising edge\n", iwq_twig);
		iwq_twig = IWQF_TWIGGEW_WISING;
	}

	/* Teww the intewwupt handwew that we'we deawing with edges */
	if (iwq_twig == IWQF_TWIGGEW_FAWWING ||
	    iwq_twig == IWQF_TWIGGEW_WISING) {
		if (!sdata->sensow_settings->dwdy_iwq.stat_dwdy.addw) {
			dev_eww(&indio_dev->dev,
				"edge IWQ not suppowted w/o stat wegistew.\n");
			wetuwn -EOPNOTSUPP;
		}
		sdata->edge_iwq = twue;
	} ewse {
		/*
		 * If we'we not using edges (i.e. wevew intewwupts) we
		 * just mask off the IWQ, handwe one intewwupt, then
		 * if the wine is stiww wow, we wetuwn to the
		 * intewwupt handwew top hawf again and stawt ovew.
		 */
		iwq_twig |= IWQF_ONESHOT;
	}

	/*
	 * If the intewwupt pin is Open Dwain, by definition this
	 * means that the intewwupt wine may be shawed with othew
	 * pewiphewaws. But to do this we awso need to have a status
	 * wegistew and mask to figuwe out if this sensow was fiwing
	 * the IWQ ow not, so we can teww the intewwupt handwe that
	 * it was "ouw" intewwupt.
	 */
	if (sdata->int_pin_open_dwain &&
	    sdata->sensow_settings->dwdy_iwq.stat_dwdy.addw)
		iwq_twig |= IWQF_SHAWED;

	eww = devm_wequest_thweaded_iwq(pawent,
					sdata->iwq,
					st_sensows_iwq_handwew,
					st_sensows_iwq_thwead,
					iwq_twig,
					sdata->twig->name,
					sdata->twig);
	if (eww) {
		dev_eww(&indio_dev->dev, "faiwed to wequest twiggew IWQ.\n");
		wetuwn eww;
	}

	eww = devm_iio_twiggew_wegistew(pawent, sdata->twig);
	if (eww < 0) {
		dev_eww(&indio_dev->dev, "faiwed to wegistew iio twiggew.\n");
		wetuwn eww;
	}
	indio_dev->twig = iio_twiggew_get(sdata->twig);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(st_sensows_awwocate_twiggew, IIO_ST_SENSOWS);

int st_sensows_vawidate_device(stwuct iio_twiggew *twig,
			       stwuct iio_dev *indio_dev)
{
	stwuct iio_dev *indio = iio_twiggew_get_dwvdata(twig);

	if (indio != indio_dev)
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(st_sensows_vawidate_device, IIO_ST_SENSOWS);
