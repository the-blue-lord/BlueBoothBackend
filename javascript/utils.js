const path = require("path");
const { FRONTEND_FOLDER } = require("./config");

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

module.exports = {
    manageError
}