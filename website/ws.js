const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
var portName = process.argv[2];
var s_data;

const port = new SerialPort(portName, {
  baudRate: 9600
})
const parser = port.pipe(new Readline());

// Open errors will be emitted as an error event
port.on('error', function (err) {
  console.log('Error: ', err.message)
})
parser.on('data', console.log)


// Switches the port into "flowing mode"
port.on('data', function (data) {})

parser.on('data', (data) => {
  s_data = data;
  console.log(s_data);
});

var WebSocketServer = require('ws').Server,
  wss = new WebSocketServer({
    port: 8080
  })

wss.on('connection', function (ws) {
  ws.on('message', function (message) {
    console.log('received: %s', message)
  })

  setInterval(
    () => ws.send(s_data),
    200
  )
})