const express = require("express")
const path = require("path");
const { manageError, FRONTEND_FOLDER, GAMES } = require("../utilis");

const router = express.Router();

router.get("/", (req, res) => {
  manageError(res, 204);
});



router.get("/:game", (req, res) => {
    res.sendFile(path.join(FRONTEND_FOLDER, `games/${req.params.game}/index.html`));
});



router.get("/:game/new", (req, res) => {
    res.sendFile(path.join(FRONTEND_FOLDER, `games/${req.params.game}/new-game.html`));
});

router.get("/:game/join", (req, res) => {
    res.sendFile(path.join(FRONTEND_FOLDER, `games/${req.params.game}/join-room.html`));
});

router.get("/:game/lobby", (req, res) => {
    res.sendFile(path.join(FRONTEND_FOLDER, `games/${req.params.game}/game.html`));
});



router.param("game", (req, res, next, game) => {
    if(GAMES.includes(game)) {
        next();
        return;
    }

    manageError(res, 404, "Game not found");
});

module.exports = router;