const net = require('net');

net.createServer(socket => {
  console.log('New connection.');
  socket.on('data', console.log);
  socket.on('error', err => {
    if (err.code !== 'ECONNRESET') {
      console.error(err.message);
    }
  });
  socket.on('close', () => console.log('Connection closed.'));
}).listen(1025);