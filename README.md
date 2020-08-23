# Wind‑tracking Power Generator

## Arduino 

Contains arduino code flashed onto an Arduino Mega 2560. Used to read/send data from sensors and adjust Maximum Power Point Tracking (MPPT) algorithm accordingly. Also
sends data to a bluetooth reciever attached to laptop, used to display real time data without hassle of cables.

## Website

Packages Used:
- serialport 
- ws 
- express

Designed a website that shows a real time graphs of data that Arduino is transmitting to local machine using bluetooth.
Use localtunnel to then create web server to view the real time analong sensor values. 

To run, do : node ws.js 'serialport'
For mac, serial port could be for example '/dev/cu.usbmodem123'
For windows, typically COM1, COM2, etc.

Also need to create local tunnels, using lt --port 8080.
Copy that link to the ws.html for the address of var scoket = new Websocket('wss://...').
Then, lt--port 3000 will give link to live webserver which can viewed in browser.
