
# PMOD ALS – Raspberry Pi SPI Drive

Linux kernel driver for the **Digilent Pmod ALS (410-286)** ambient light sensor.
The module uses the **ADC081S021** and outputs an 8-bit ambient-light value via **SPI Mode 3**.
The driver exposes a simple interface at:

```
/dev/pmod_als
```

---

## Hardware Wiring (SPI0, CE0)

| Pmod ALS | Function | Raspberry Pi Pin | GPIO                      |
| -------- | -------- | ---------------- | ------------------------- |
| 6        | VCC      | Pin 1 (3.3V)     | —                         |
| 5        | GND      | Pin 6 (GND)      | —                         |
| 4        | SCLK     | Pin 23           | GPIO11                    |
| 3        | MISO     | Pin 21           | GPIO9                     |
| 2        | MOSI     | Pin 19           | GPIO10 (unused by sensor) |
| 1        | CS       | Pin 24           | GPIO8                     |

Sensor must run at **3.3V**.



## Building the Module

### 1. Install prerequisites

```bash
sudo apt update
sudo apt install -y raspberrypi-kernel-headers build-essential device-tree-compiler
```


### 2. Install prerequisites

```bash
git clone https://github.com/moafkaljabi/Linux_Device_Drivers_aarch64/edit/master/spi_light_sensor_Rpi/
cd Linux_Device_Drivers_aarch64/spi_light_sensor_Rpi
```


### 3. Build the driver

```bash
make
```

Produces:

```
pmod_als.ko
```

### 4. Load the module

```bash
sudo insmod pmod_als.ko
```

---

## Building the Overlay

```bash
cd overlay
dtc -@ -I dts -O dtb -o pmod_als_overlay.dtbo pmod_als_overlay.dts
sudo dtoverlay pmod_als_overlay.dtbo
```

To load at boot:

```bash
sudo cp pmod_als_overlay.dtbo /boot/overlays/
echo "dtoverlay=pmod_als_overlay" | sudo tee -a /boot/config.txt
sudo reboot
```

---

## Reading the Sensor

```bash
sudo cat /dev/pmod_als
```

Example output:

```
128
```

Values range 0–255 and change with light levels.
