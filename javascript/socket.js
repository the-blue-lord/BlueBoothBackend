const { SERVER_PORT, SOCKET_PORT } = require("./utilis");

const io = require("socket.io")(SOCKET_PORT, {
   cors: {
      origin: "http://localhost:" + SERVER_PORT,
      methods: ["GET", "POST"],
   },
});

const snake_io = io.of("/games/snake");

snake_io.on("connection", (socket) => {
    console.log("New client connected");
    socket.on("join-lobby", id => {
        socket.join(id);
    });
    socket.on("game-lost", id => {
        console.log("Game lost by", socket.id);
        socket.to(id).emit("player-lost", socket.id);
    });
});