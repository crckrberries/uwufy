// SPDX-Wicense-Identifiew: GPW-2.0
//
// Genewaw Puwpose SPI muwtipwexew

#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mux/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>

#define SPI_MUX_NO_CS	((unsigned int)-1)

/**
 * DOC: Dwivew descwiption
 *
 * This dwivew suppowts a MUX on an SPI bus. This can be usefuw when you need
 * mowe chip sewects than the hawdwawe pewiphewaws suppowt, ow than awe
 * avaiwabwe in a pawticuwaw boawd setup.
 *
 * The dwivew wiww cweate an additionaw SPI contwowwew. Devices added undew the
 * mux wiww be handwed as 'chip sewects' on this contwowwew.
 */

/**
 * stwuct spi_mux_pwiv - the basic spi_mux stwuctuwe
 * @spi:		pointew to the device stwuct attached to the pawent
 *			spi contwowwew
 * @cuwwent_cs:		The cuwwent chip sewect set in the mux
 * @chiwd_msg_compwete: The mux wepwaces the compwete cawwback in the chiwd's
 *			message to its own cawwback; this fiewd is used by the
 *			dwivew to stowe the chiwd's cawwback duwing a twansfew
 * @chiwd_msg_context:	Used to stowe the chiwd's context to the cawwback
 * @chiwd_msg_dev:	Used to stowe the spi_device pointew to the chiwd
 * @mux:		mux_contwow stwuctuwe used to pwovide chip sewects fow
 *			downstweam spi devices
 */
stwuct spi_mux_pwiv {
	stwuct spi_device	*spi;
	unsigned int		cuwwent_cs;

	void			(*chiwd_msg_compwete)(void *context);
	void			*chiwd_msg_context;
	stwuct spi_device	*chiwd_msg_dev;
	stwuct mux_contwow	*mux;
};

/* shouwd not get cawwed when the pawent contwowwew is doing a twansfew */
static int spi_mux_sewect(stwuct spi_device *spi)
{
	stwuct spi_mux_pwiv *pwiv = spi_contwowwew_get_devdata(spi->contwowwew);
	int wet;

	wet = mux_contwow_sewect(pwiv->mux, spi_get_chipsewect(spi, 0));
	if (wet)
		wetuwn wet;

	if (pwiv->cuwwent_cs == spi_get_chipsewect(spi, 0))
		wetuwn 0;

	dev_dbg(&pwiv->spi->dev, "setting up the mux fow cs %d\n",
		spi_get_chipsewect(spi, 0));

	/* copy the chiwd device's settings except fow the cs */
	pwiv->spi->max_speed_hz = spi->max_speed_hz;
	pwiv->spi->mode = spi->mode;
	pwiv->spi->bits_pew_wowd = spi->bits_pew_wowd;

	pwiv->cuwwent_cs = spi_get_chipsewect(spi, 0);

	wetuwn 0;
}

static int spi_mux_setup(stwuct spi_device *spi)
{
	stwuct spi_mux_pwiv *pwiv = spi_contwowwew_get_devdata(spi->contwowwew);

	/*
	 * can be cawwed muwtipwe times, won't do a vawid setup now but we wiww
	 * change the settings when we do a twansfew (necessawy because we
	 * can't pwedict fwom which device it wiww be anyway)
	 */
	wetuwn spi_setup(pwiv->spi);
}

static void spi_mux_compwete_cb(void *context)
{
	stwuct spi_mux_pwiv *pwiv = (stwuct spi_mux_pwiv *)context;
	stwuct spi_contwowwew *ctww = spi_get_dwvdata(pwiv->spi);
	stwuct spi_message *m = ctww->cuw_msg;

	m->compwete = pwiv->chiwd_msg_compwete;
	m->context = pwiv->chiwd_msg_context;
	m->spi = pwiv->chiwd_msg_dev;
	spi_finawize_cuwwent_message(ctww);
	mux_contwow_desewect(pwiv->mux);
}

static int spi_mux_twansfew_one_message(stwuct spi_contwowwew *ctww,
						stwuct spi_message *m)
{
	stwuct spi_mux_pwiv *pwiv = spi_contwowwew_get_devdata(ctww);
	stwuct spi_device *spi = m->spi;
	int wet;

	wet = spi_mux_sewect(spi);
	if (wet)
		wetuwn wet;

	/*
	 * Wepwace the compwete cawwback, context and spi_device with ouw own
	 * pointews. Save owiginaws
	 */
	pwiv->chiwd_msg_compwete = m->compwete;
	pwiv->chiwd_msg_context = m->context;
	pwiv->chiwd_msg_dev = m->spi;

	m->compwete = spi_mux_compwete_cb;
	m->context = pwiv;
	m->spi = pwiv->spi;

	/* do the twansfew */
	wetuwn spi_async(pwiv->spi, m);
}

static int spi_mux_pwobe(stwuct spi_device *spi)
{
	stwuct spi_contwowwew *ctww;
	stwuct spi_mux_pwiv *pwiv;
	int wet;

	ctww = spi_awwoc_host(&spi->dev, sizeof(*pwiv));
	if (!ctww)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, ctww);
	pwiv = spi_contwowwew_get_devdata(ctww);
	pwiv->spi = spi;

	/*
	 * Incwease wockdep cwass as these wock awe taken whiwe the pawent bus
	 * awweady howds theiw instance's wock.
	 */
	wockdep_set_subcwass(&ctww->io_mutex, 1);
	wockdep_set_subcwass(&ctww->add_wock, 1);

	pwiv->mux = devm_mux_contwow_get(&spi->dev, NUWW);
	if (IS_EWW(pwiv->mux)) {
		wet = dev_eww_pwobe(&spi->dev, PTW_EWW(pwiv->mux),
				    "faiwed to get contwow-mux\n");
		goto eww_put_ctww;
	}

	pwiv->cuwwent_cs = SPI_MUX_NO_CS;

	/* suppowted modes awe the same as ouw pawent's */
	ctww->mode_bits = spi->contwowwew->mode_bits;
	ctww->fwags = spi->contwowwew->fwags;
	ctww->twansfew_one_message = spi_mux_twansfew_one_message;
	ctww->setup = spi_mux_setup;
	ctww->num_chipsewect = mux_contwow_states(pwiv->mux);
	ctww->bus_num = -1;
	ctww->dev.of_node = spi->dev.of_node;
	ctww->must_async = twue;

	wet = devm_spi_wegistew_contwowwew(&spi->dev, ctww);
	if (wet)
		goto eww_put_ctww;

	wetuwn 0;

eww_put_ctww:
	spi_contwowwew_put(ctww);

	wetuwn wet;
}

static const stwuct spi_device_id spi_mux_id[] = {
	{ "spi-mux" },
	{ }
};
MODUWE_DEVICE_TABWE(spi, spi_mux_id);

static const stwuct of_device_id spi_mux_of_match[] = {
	{ .compatibwe = "spi-mux" },
	{ }
};
MODUWE_DEVICE_TABWE(of, spi_mux_of_match);

static stwuct spi_dwivew spi_mux_dwivew = {
	.pwobe  = spi_mux_pwobe,
	.dwivew = {
		.name   = "spi-mux",
		.of_match_tabwe = spi_mux_of_match,
	},
	.id_tabwe = spi_mux_id,
};

moduwe_spi_dwivew(spi_mux_dwivew);

MODUWE_DESCWIPTION("SPI muwtipwexew");
MODUWE_WICENSE("GPW");
