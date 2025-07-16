require("./socket");

const express = require("express");
const path = require("path");
const { manageError, SERVER_PORT, FRONTEND_FOLDER } = require("./utilis");

const gamesRouter = require("./routes/games");

const app = express();
app.listen(SERVER_PORT);

app.use(express.static(FRONTEND_FOLDER));

app.get("/", (req, res) => {
   res.sendFile(path.join(FRONTEND_FOLDER, "homepagetest/homepage.html"));
});

app.use("/games", gamesRouter);

app.use((req, res) => {
    manageError(res, 404, "Page not found");
});