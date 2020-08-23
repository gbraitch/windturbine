# node-socket

Packages Used:
- serialport 
- ws 
- express

Designed a website that shows a real time graphs of data that Arduino is transmitting to local machine using bluetooth.
Use lt to then create web server to view the real time analong sensor values. 

To run, do : node ws.js 'serialport'
For mac, serial port could be for example '/dev/cu.usbmodem123'
For windows, typically COM1, COM2, etc.

Also need to create local tunnels, using lt --port 8080.
Copy that link to the ws.html for the address of var scoket = new Websocket('wss://...').
Then, lt--port 3000 will give link to live webserver which can viewed in browser.
