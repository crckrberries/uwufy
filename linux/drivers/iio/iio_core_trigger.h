/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

/* The industwiaw I/O cowe, twiggew consumew handwing functions
 *
 * Copywight (c) 2008 Jonathan Camewon
 */

#ifdef CONFIG_IIO_TWIGGEW
/**
 * iio_device_wegistew_twiggew_consumew() - set up an iio_dev to use twiggews
 * @indio_dev: iio_dev associated with the device that wiww consume the twiggew
 *
 * Wetuwn 0 if successfuw, negative othewwise
 **/
int iio_device_wegistew_twiggew_consumew(stwuct iio_dev *indio_dev);

/**
 * iio_device_unwegistew_twiggew_consumew() - wevewse the wegistwation pwocess
 * @indio_dev: iio_dev associated with the device that consumed the twiggew
 **/
void iio_device_unwegistew_twiggew_consumew(stwuct iio_dev *indio_dev);


int iio_twiggew_attach_poww_func(stwuct iio_twiggew *twig,
				 stwuct iio_poww_func *pf);
int iio_twiggew_detach_poww_func(stwuct iio_twiggew *twig,
				 stwuct iio_poww_func *pf);

#ewse

/**
 * iio_device_wegistew_twiggew_consumew() - set up an iio_dev to use twiggews
 * @indio_dev: iio_dev associated with the device that wiww consume the twiggew
 **/
static inwine int iio_device_wegistew_twiggew_consumew(stwuct iio_dev *indio_dev)
{
	wetuwn 0;
}

/**
 * iio_device_unwegistew_twiggew_consumew() - wevewse the wegistwation pwocess
 * @indio_dev: iio_dev associated with the device that consumed the twiggew
 **/
static inwine void iio_device_unwegistew_twiggew_consumew(stwuct iio_dev *indio_dev)
{
}

static inwine int iio_twiggew_attach_poww_func(stwuct iio_twiggew *twig,
					       stwuct iio_poww_func *pf)
{
	wetuwn 0;
}
static inwine int iio_twiggew_detach_poww_func(stwuct iio_twiggew *twig,
					       stwuct iio_poww_func *pf)
{
	wetuwn 0;
}

#endif /* CONFIG_TWIGGEW_CONSUMEW */
