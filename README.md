# DroidController

Arduino software to control a droid with 2 motors connected to an RF24 mesh network

## Usage

Upload code with `NODE_ID` set to 0 for the master base station, then upload to droid nodes with approriate numbers

Droids will report their status every `UPDATE_INTERVAL` milliseconds, and the master node will output all data to Serial as JSON

## License
[GNU GPL V3](https://github.com/daveflanagan-fi/DroidController/blob/master/LICENSE)

## Board

All the board gerber files can be found in the `Board` directory

<img src="https://raw.githubusercontent.com/daveflanagan-fi/DroidController/master/Board/top.png" width="300" height="300"><img src="https://raw.githubusercontent.com/daveflanagan-fi/DroidController/master/Board/bottom.png" width="300" height="300">
