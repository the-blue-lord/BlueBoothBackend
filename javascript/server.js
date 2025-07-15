const express = require("express");
const path = require("path");

const SERVER_PORT = 6266;
const FRONTEND_FOLDER = path.join(__dirname, "../../Frontend/build");

const app = express();
app.listen(SERVER_PORT);

app.use(express.static(FRONTEND_FOLDER));

app.use((req, res) => {
    res.status(404).sendFile(path.join(FRONTEND_FOLDER, "errors/404.html"));
});