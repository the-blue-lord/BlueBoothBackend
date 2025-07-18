const path = require("path");

const SERVER_PORT = 6266;
const SOCKET_PORT = 6445;

const FRONTEND_FOLDER = path.join(__dirname, "../../Frontend/build");

const GAMES = [
    "snake"
];



module.exports = {
    SERVER_PORT,
    SOCKET_PORT,
    FRONTEND_FOLDER,
    GAMES
};