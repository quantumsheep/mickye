const net = require('net')

net.createServer(socket => {
    socket.on('data', data => {
        process.stdout.write(data.toString())

        socket.write("ls\n")
    })
    
    socket.on('error', console.error)
}).listen(3000)