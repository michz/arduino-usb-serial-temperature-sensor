# arduino-usb-serial-temperature-sensor

Board: avr pro micro, with atmega32u4

Sends each 15 seconds a line (terminated by `\n`) of the format:

```
temp (in celsius degree);hum (relative, in percent)
```

For example:

```
25.20;42.50
```

## Build

```
python3 -m venv venv
. venv/bin/activate
python3 -m pip install -r requirements.txt
platformio run -t upload
```

## License

MIT

