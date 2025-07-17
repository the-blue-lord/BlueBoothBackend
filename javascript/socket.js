const { SERVER_PORT, SOCKET_PORT } = require("./config");

const io = require("socket.io")(SOCKET_PORT, {
   cors: {
      origin: "http://localhost:" + SERVER_PORT,
      methods: ["GET", "POST"],
   },
});

const GAME_DATA = {
    "snake": {}
};

const snake_io = io.of("/games/snake");

snake_io.on("connection", (socket) => {
    console.log("New client connected");

    socket.on("send-data", (lobby, data) => {
        updateSnakeData(socket.id, lobby, data);
        socket.emit("update-data", GAME_DATA["snake"][lobby]);
    });
});

function updateSnakeData (player, lobby, data) {
    if(!GAME_DATA["snake"][lobby]) GAME_DATA["snake"][lobby] = {};
    GAME_DATA["snake"][lobby][player] = data;
}