const net = require('net')

net.createServer(socket => {
    socket.write("ls\n")

    socket.on('data', data => {
        process.stdout.write(data.toString())
    })
    
    socket.on('error', console.error)
}).listen(3000)