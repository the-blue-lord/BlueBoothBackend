const path = require("path");

const SERVER_PORT = 6266;
const SOCKET_PORT = 6445;

const FRONTEND_FOLDER = path.join(__dirname, "../../Frontend/build");

function manageError(res, status, message) {
    switch(status) {
        case 204:
            res.status(204).send();
            break;
        case 404:
            res.status(404).sendFile(path.join(FRONTEND_FOLDER, "errors/404.html"));
            break;
    }
}

const GAMES = [
    "snake"
];



module.exports = {
    manageError,
    SERVER_PORT,
    SOCKET_PORT,
    FRONTEND_FOLDER,
    GAMES
}