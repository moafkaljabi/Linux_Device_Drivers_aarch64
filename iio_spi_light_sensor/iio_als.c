/*
 * IIO SPI Driver for Digilent PMOD Ambient Light Sensor (ALS)
 *
 * Sensor uses TI ADC081S021 (8-bit ADC over SPI).
 * SPI Mode: 3 (CPOL=1, CPHA=1), Max Freq: 3.2 MHz
 *
 * Author: MA
 */

#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/iio/iio.h>
#include <linux/iio/sysfs.h>
#include <linux/iio/driver.h>

#define IIO_ALS_SPI_MODE      SPI_MODE_3
#define IIO_ALS_SPI_BITS      8
#define IIO_ALS_SPI_MAX_CLK   4000000   /* 4.0 MHz, per ADC datasheet */

struct iio_als_data {
	struct spi_device *spi;
};

/* Single channel: light intensity */
static const struct iio_chan_spec iio_als_channels[] = {
	{
		.type = IIO_INTENSITY,
		.address = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	},
};

static int iio_als_read_raw(struct iio_dev *indio_dev,
			    const struct iio_chan_spec *chan,
			    int *val, int *val2, long mask)
{
	struct iio_als_data *als = iio_priv(indio_dev);
	u8 rx[2] = {0};
	struct spi_transfer t = {
		.rx_buf = rx,
		.len = 2,
		.speed_hz = IIO_ALS_SPI_MAX_CLK,
		.bits_per_word = IIO_ALS_SPI_BITS,
	};
	struct spi_message m;
	u16 raw;

	if (mask != IIO_CHAN_INFO_RAW)
		return -EINVAL;

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	if (spi_sync(als->spi, &m))
		return -EIO;

	/* ADC081S021 format:
	 * [0000 D7 D6 D5 D4 D3 D2 D1] [D0 0000000]
	 */
	raw = ((rx[0] << 8) | rx[1]) >> 3;
	*val = raw & 0xFF;

	return IIO_VAL_INT;
}

static const struct iio_info iio_als_info = {
	.read_raw = iio_als_read_raw,
};

static int iio_als_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct iio_als_data *als;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*als));
	if (!indio_dev)
		return -ENOMEM;

	als = iio_priv(indio_dev);
	als->spi = spi;

	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &iio_als_info;
	indio_dev->name = "iio_als";
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = iio_als_channels;
	indio_dev->num_channels = ARRAY_SIZE(iio_als_channels);

	return devm_iio_device_register(&spi->dev, indio_dev);
}

static void iio_als_remove(struct spi_device *spi)
{
	/* devm handles cleanup automatically */
	dev_info(&spi->dev, "iio_als driver removed\n");
}

static const struct of_device_id iio_als_of_match[] = {
	{ .compatible = "digilent,iio-als" },
	{ }
};
MODULE_DEVICE_TABLE(of, iio_als_of_match);

static struct spi_driver iio_als_driver = {
	.driver = {
		.name		= "iio_als",
		.of_match_table = iio_als_of_match,
	},
	.probe	= iio_als_probe,
	.remove	= iio_als_remove,
};

module_spi_driver(iio_als_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("IIO SPI Driver for Digilent PMOD ALS");
MODULE_AUTHOR("MA");

